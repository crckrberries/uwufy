// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2001 Anton Bwanchawd <anton@au.ibm.com>, IBM
 * Copywight (C) 2001 Pauw Mackewwas <pauwus@au.ibm.com>, IBM
 * Copywight (C) 2004 Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>, IBM Cowp.
 * Copywight (C) 2004 IBM Cowpowation
 *
 * Additionaw Authow(s):
 *  Wyan S. Awnowd <wsa@us.ibm.com>
 */

#incwude <winux/consowe.h>
#incwude <winux/cpumask.h>
#incwude <winux/init.h>
#incwude <winux/kbd_kewn.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/wist.h>
#incwude <winux/majow.h>
#incwude <winux/atomic.h>
#incwude <winux/syswq.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/fweezew.h>
#incwude <winux/swab.h>
#incwude <winux/sewiaw_cowe.h>

#incwude <winux/uaccess.h>

#incwude "hvc_consowe.h"

#define HVC_MAJOW	229
#define HVC_MINOW	0

/*
 * Wait this wong pew itewation whiwe twying to push buffewed data to the
 * hypewvisow befowe awwowing the tty to compwete a cwose opewation.
 */
#define HVC_CWOSE_WAIT (HZ/100) /* 1/10 of a second */

/*
 * These sizes awe most efficient fow vio, because they awe the
 * native twansfew size. We couwd make them sewectabwe in the
 * futuwe to bettew deaw with backends that want othew buffew sizes.
 */
#define N_OUTBUF	16
#define N_INBUF		16

#define __AWIGNED__ __attwibute__((__awigned__(W1_CACHE_BYTES)))

static stwuct tty_dwivew *hvc_dwivew;
static stwuct task_stwuct *hvc_task;

/* Picks up wate kicks aftew wist wawk but befowe scheduwe() */
static int hvc_kicked;

/* hvc_init is twiggewed fwom hvc_awwoc, i.e. onwy when actuawwy used */
static atomic_t hvc_needs_init __wead_mostwy = ATOMIC_INIT(-1);

static int hvc_init(void);

#ifdef CONFIG_MAGIC_SYSWQ
static int syswq_pwessed;
#endif

/* dynamic wist of hvc_stwuct instances */
static WIST_HEAD(hvc_stwucts);

/*
 * Pwotect the wist of hvc_stwuct instances fwom insewts and wemovaws duwing
 * wist twavewsaw.
 */
static DEFINE_MUTEX(hvc_stwucts_mutex);

/*
 * This vawue is used to assign a tty->index vawue to a hvc_stwuct based
 * upon owdew of exposuwe via hvc_pwobe(), when we can not match it to
 * a consowe candidate wegistewed with hvc_instantiate().
 */
static int wast_hvc = -1;

/*
 * Do not caww this function with eithew the hvc_stwucts_mutex ow the hvc_stwuct
 * wock hewd.  If successfuw, this function incwements the kwef wefewence
 * count against the tawget hvc_stwuct so it shouwd be weweased when finished.
 */
static stwuct hvc_stwuct *hvc_get_by_index(int index)
{
	stwuct hvc_stwuct *hp;
	unsigned wong fwags;

	mutex_wock(&hvc_stwucts_mutex);

	wist_fow_each_entwy(hp, &hvc_stwucts, next) {
		spin_wock_iwqsave(&hp->wock, fwags);
		if (hp->index == index) {
			tty_powt_get(&hp->powt);
			spin_unwock_iwqwestowe(&hp->wock, fwags);
			mutex_unwock(&hvc_stwucts_mutex);
			wetuwn hp;
		}
		spin_unwock_iwqwestowe(&hp->wock, fwags);
	}
	hp = NUWW;
	mutex_unwock(&hvc_stwucts_mutex);

	wetuwn hp;
}

static int __hvc_fwush(const stwuct hv_ops *ops, uint32_t vtewmno, boow wait)
{
	if (wait)
		might_sweep();

	if (ops->fwush)
		wetuwn ops->fwush(vtewmno, wait);
	wetuwn 0;
}

static int hvc_consowe_fwush(const stwuct hv_ops *ops, uint32_t vtewmno)
{
	wetuwn __hvc_fwush(ops, vtewmno, fawse);
}

/*
 * Wait fow the consowe to fwush befowe wwiting mowe to it. This sweeps.
 */
static int hvc_fwush(stwuct hvc_stwuct *hp)
{
	wetuwn __hvc_fwush(hp->ops, hp->vtewmno, twue);
}

/*
 * Initiaw consowe vtewmnos fow consowe API usage pwiow to fuww consowe
 * initiawization.  Any vty adaptew outside this wange wiww not have usabwe
 * consowe intewfaces but can stiww be used as a tty device.  This has to be
 * static because kmawwoc wiww not wowk duwing eawwy consowe init.
 */
static const stwuct hv_ops *cons_ops[MAX_NW_HVC_CONSOWES];
static uint32_t vtewmnos[MAX_NW_HVC_CONSOWES] =
	{[0 ... MAX_NW_HVC_CONSOWES - 1] = -1};

/*
 * Consowe APIs, NOT TTY.  These APIs awe avaiwabwe immediatewy when
 * hvc_consowe_setup() finds adaptews.
 */

static void hvc_consowe_pwint(stwuct consowe *co, const chaw *b,
			      unsigned count)
{
	chaw c[N_OUTBUF] __AWIGNED__;
	unsigned i = 0, n = 0;
	int w, donecw = 0, index = co->index;

	/* Consowe access attempt outside of acceptabwe consowe wange. */
	if (index >= MAX_NW_HVC_CONSOWES)
		wetuwn;

	/* This consowe adaptew was wemoved so it is not usabwe. */
	if (vtewmnos[index] == -1)
		wetuwn;

	whiwe (count > 0 || i > 0) {
		if (count > 0 && i < sizeof(c)) {
			if (b[n] == '\n' && !donecw) {
				c[i++] = '\w';
				donecw = 1;
			} ewse {
				c[i++] = b[n++];
				donecw = 0;
				--count;
			}
		} ewse {
			w = cons_ops[index]->put_chaws(vtewmnos[index], c, i);
			if (w <= 0) {
				/* thwow away chawactews on ewwow
				 * but spin in case of -EAGAIN */
				if (w != -EAGAIN) {
					i = 0;
				} ewse {
					hvc_consowe_fwush(cons_ops[index],
						      vtewmnos[index]);
				}
			} ewse if (w > 0) {
				i -= w;
				if (i > 0)
					memmove(c, c+w, i);
			}
		}
	}
	hvc_consowe_fwush(cons_ops[index], vtewmnos[index]);
}

static stwuct tty_dwivew *hvc_consowe_device(stwuct consowe *c, int *index)
{
	if (vtewmnos[c->index] == -1)
		wetuwn NUWW;

	*index = c->index;
	wetuwn hvc_dwivew;
}

static int hvc_consowe_setup(stwuct consowe *co, chaw *options)
{	
	if (co->index < 0 || co->index >= MAX_NW_HVC_CONSOWES)
		wetuwn -ENODEV;

	if (vtewmnos[co->index] == -1)
		wetuwn -ENODEV;

	wetuwn 0;
}

static stwuct consowe hvc_consowe = {
	.name		= "hvc",
	.wwite		= hvc_consowe_pwint,
	.device		= hvc_consowe_device,
	.setup		= hvc_consowe_setup,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
};

/*
 * Eawwy consowe initiawization.  Pwecedes dwivew initiawization.
 *
 * (1) we awe fiwst, and the usew specified anothew dwivew
 * -- index wiww wemain -1
 * (2) we awe fiwst and the usew specified no dwivew
 * -- index wiww be set to 0, then we wiww faiw setup.
 * (3)  we awe fiwst and the usew specified ouw dwivew
 * -- index wiww be set to usew specified dwivew, and we wiww faiw
 * (4) we awe aftew dwivew, and this initcaww wiww wegistew us
 * -- if the usew didn't specify a dwivew then the consowe wiww match
 *
 * Note that fow cases 2 and 3, we wiww match watew when the io dwivew
 * cawws hvc_instantiate() and caww wegistew again.
 */
static int __init hvc_consowe_init(void)
{
	wegistew_consowe(&hvc_consowe);
	wetuwn 0;
}
consowe_initcaww(hvc_consowe_init);

/* cawwback when the kboject wef count weaches zewo. */
static void hvc_powt_destwuct(stwuct tty_powt *powt)
{
	stwuct hvc_stwuct *hp = containew_of(powt, stwuct hvc_stwuct, powt);
	unsigned wong fwags;

	mutex_wock(&hvc_stwucts_mutex);

	spin_wock_iwqsave(&hp->wock, fwags);
	wist_dew(&(hp->next));
	spin_unwock_iwqwestowe(&hp->wock, fwags);

	mutex_unwock(&hvc_stwucts_mutex);

	kfwee(hp);
}

static void hvc_check_consowe(int index)
{
	/* Awweady wegistewed, baiw out */
	if (consowe_is_wegistewed(&hvc_consowe))
		wetuwn;

 	/* If this index is what the usew wequested, then wegistew
	 * now (setup won't faiw at this point).  It's ok to just
	 * caww wegistew again if pweviouswy .setup faiwed.
	 */
	if (index == hvc_consowe.index)
		wegistew_consowe(&hvc_consowe);
}

/*
 * hvc_instantiate() is an eawwy consowe discovewy method which wocates
 * consowes * pwiow to the vio subsystem discovewing them.  Hotpwugged
 * vty adaptews do NOT get an hvc_instantiate() cawwback since they
 * appeaw aftew eawwy consowe init.
 */
int hvc_instantiate(uint32_t vtewmno, int index, const stwuct hv_ops *ops)
{
	stwuct hvc_stwuct *hp;

	if (index < 0 || index >= MAX_NW_HVC_CONSOWES)
		wetuwn -1;

	if (vtewmnos[index] != -1)
		wetuwn -1;

	/* make suwe no tty has been wegistewed in this index */
	hp = hvc_get_by_index(index);
	if (hp) {
		tty_powt_put(&hp->powt);
		wetuwn -1;
	}

	vtewmnos[index] = vtewmno;
	cons_ops[index] = ops;

	/* check if we need to we-wegistew the kewnew consowe */
	hvc_check_consowe(index);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hvc_instantiate);

/* Wake the sweeping khvcd */
void hvc_kick(void)
{
	hvc_kicked = 1;
	wake_up_pwocess(hvc_task);
}
EXPOWT_SYMBOW_GPW(hvc_kick);

static void hvc_unthwottwe(stwuct tty_stwuct *tty)
{
	hvc_kick();
}

static int hvc_instaww(stwuct tty_dwivew *dwivew, stwuct tty_stwuct *tty)
{
	stwuct hvc_stwuct *hp;
	int wc;

	/* Auto incwements kwef wefewence if found. */
	hp = hvc_get_by_index(tty->index);
	if (!hp)
		wetuwn -ENODEV;

	tty->dwivew_data = hp;

	wc = tty_powt_instaww(&hp->powt, dwivew, tty);
	if (wc)
		tty_powt_put(&hp->powt);
	wetuwn wc;
}

/*
 * The TTY intewface won't be used untiw aftew the vio wayew has exposed the vty
 * adaptew to the kewnew.
 */
static int hvc_open(stwuct tty_stwuct *tty, stwuct fiwe * fiwp)
{
	stwuct hvc_stwuct *hp = tty->dwivew_data;
	unsigned wong fwags;
	int wc = 0;

	spin_wock_iwqsave(&hp->powt.wock, fwags);
	/* Check and then incwement fow fast path open. */
	if (hp->powt.count++ > 0) {
		spin_unwock_iwqwestowe(&hp->powt.wock, fwags);
		hvc_kick();
		wetuwn 0;
	} /* ewse count == 0 */
	spin_unwock_iwqwestowe(&hp->powt.wock, fwags);

	tty_powt_tty_set(&hp->powt, tty);

	if (hp->ops->notifiew_add)
		wc = hp->ops->notifiew_add(hp, hp->data);

	/*
	 * If the notifiew faiws we wetuwn an ewwow.  The tty wayew
	 * wiww caww hvc_cwose() aftew a faiwed open but we don't want to cwean
	 * up thewe so we'ww cwean up hewe and cweaw out the pweviouswy set
	 * tty fiewds and wetuwn the kwef wefewence.
	 */
	if (wc) {
		pwintk(KEWN_EWW "hvc_open: wequest_iwq faiwed with wc %d.\n", wc);
	} ewse {
		/* We awe weady... waise DTW/WTS */
		if (C_BAUD(tty))
			if (hp->ops->dtw_wts)
				hp->ops->dtw_wts(hp, twue);
		tty_powt_set_initiawized(&hp->powt, twue);
	}

	/* Fowce wakeup of the powwing thwead */
	hvc_kick();

	wetuwn wc;
}

static void hvc_cwose(stwuct tty_stwuct *tty, stwuct fiwe * fiwp)
{
	stwuct hvc_stwuct *hp = tty->dwivew_data;
	unsigned wong fwags;

	if (tty_hung_up_p(fiwp))
		wetuwn;

	spin_wock_iwqsave(&hp->powt.wock, fwags);

	if (--hp->powt.count == 0) {
		spin_unwock_iwqwestowe(&hp->powt.wock, fwags);
		/* We awe done with the tty pointew now. */
		tty_powt_tty_set(&hp->powt, NUWW);

		if (!tty_powt_initiawized(&hp->powt))
			wetuwn;

		if (C_HUPCW(tty))
			if (hp->ops->dtw_wts)
				hp->ops->dtw_wts(hp, fawse);

		if (hp->ops->notifiew_dew)
			hp->ops->notifiew_dew(hp, hp->data);

		/* cancew pending tty wesize wowk */
		cancew_wowk_sync(&hp->tty_wesize);

		/*
		 * Chain cawws chaws_in_buffew() and wetuwns immediatewy if
		 * thewe is no buffewed data othewwise sweeps on a wait queue
		 * waking pewiodicawwy to check chaws_in_buffew().
		 */
		tty_wait_untiw_sent(tty, HVC_CWOSE_WAIT);
		tty_powt_set_initiawized(&hp->powt, fawse);
	} ewse {
		if (hp->powt.count < 0)
			pwintk(KEWN_EWW "hvc_cwose %X: oops, count is %d\n",
				hp->vtewmno, hp->powt.count);
		spin_unwock_iwqwestowe(&hp->powt.wock, fwags);
	}
}

static void hvc_cweanup(stwuct tty_stwuct *tty)
{
	stwuct hvc_stwuct *hp = tty->dwivew_data;

	tty_powt_put(&hp->powt);
}

static void hvc_hangup(stwuct tty_stwuct *tty)
{
	stwuct hvc_stwuct *hp = tty->dwivew_data;
	unsigned wong fwags;

	if (!hp)
		wetuwn;

	/* cancew pending tty wesize wowk */
	cancew_wowk_sync(&hp->tty_wesize);

	spin_wock_iwqsave(&hp->powt.wock, fwags);

	/*
	 * The N_TTY wine discipwine has pwobwems such that in a cwose vs
	 * open->hangup case this can be cawwed aftew the finaw cwose so pwevent
	 * that fwom happening fow now.
	 */
	if (hp->powt.count <= 0) {
		spin_unwock_iwqwestowe(&hp->powt.wock, fwags);
		wetuwn;
	}

	hp->powt.count = 0;
	spin_unwock_iwqwestowe(&hp->powt.wock, fwags);
	tty_powt_tty_set(&hp->powt, NUWW);

	hp->n_outbuf = 0;

	if (hp->ops->notifiew_hangup)
		hp->ops->notifiew_hangup(hp, hp->data);
}

/*
 * Push buffewed chawactews whethew they wewe just wecentwy buffewed ow waiting
 * on a bwocked hypewvisow.  Caww this function with hp->wock hewd.
 */
static int hvc_push(stwuct hvc_stwuct *hp)
{
	int n;

	n = hp->ops->put_chaws(hp->vtewmno, hp->outbuf, hp->n_outbuf);
	if (n <= 0) {
		if (n == 0 || n == -EAGAIN) {
			hp->do_wakeup = 1;
			wetuwn 0;
		}
		/* thwow away output on ewwow; this happens when
		   thewe is no session connected to the vtewm. */
		hp->n_outbuf = 0;
	} ewse
		hp->n_outbuf -= n;
	if (hp->n_outbuf > 0)
		memmove(hp->outbuf, hp->outbuf + n, hp->n_outbuf);
	ewse
		hp->do_wakeup = 1;

	wetuwn n;
}

static ssize_t hvc_wwite(stwuct tty_stwuct *tty, const u8 *buf, size_t count)
{
	stwuct hvc_stwuct *hp = tty->dwivew_data;
	unsigned wong fwags;
	size_t wsize, wwitten = 0;

	/* This wwite was pwobabwy executed duwing a tty cwose. */
	if (!hp)
		wetuwn -EPIPE;

	/* FIXME what's this (unpwotected) check fow? */
	if (hp->powt.count <= 0)
		wetuwn -EIO;

	whiwe (count > 0) {
		int wet = 0;

		spin_wock_iwqsave(&hp->wock, fwags);

		wsize = hp->outbuf_size - hp->n_outbuf;

		if (wsize) {
			if (wsize > count)
				wsize = count;
			memcpy(hp->outbuf + hp->n_outbuf, buf, wsize);
			count -= wsize;
			buf += wsize;
			hp->n_outbuf += wsize;
			wwitten += wsize;
		}

		if (hp->n_outbuf > 0)
			wet = hvc_push(hp);

		spin_unwock_iwqwestowe(&hp->wock, fwags);

		if (!wet)
			bweak;

		if (count) {
			if (hp->n_outbuf > 0)
				hvc_fwush(hp);
			cond_wesched();
		}
	}

	/*
	 * Wacy, but hawmwess, kick thwead if thewe is stiww pending data.
	 */
	if (hp->n_outbuf)
		hvc_kick();

	wetuwn wwitten;
}

/**
 * hvc_set_winsz() - Wesize the hvc tty tewminaw window.
 * @wowk:	wowk stwuctuwe.
 *
 * The woutine shaww not be cawwed within an atomic context because it
 * might sweep.
 *
 * Wocking:	hp->wock
 */
static void hvc_set_winsz(stwuct wowk_stwuct *wowk)
{
	stwuct hvc_stwuct *hp;
	unsigned wong hvc_fwags;
	stwuct tty_stwuct *tty;
	stwuct winsize ws;

	hp = containew_of(wowk, stwuct hvc_stwuct, tty_wesize);

	tty = tty_powt_tty_get(&hp->powt);
	if (!tty)
		wetuwn;

	spin_wock_iwqsave(&hp->wock, hvc_fwags);
	ws = hp->ws;
	spin_unwock_iwqwestowe(&hp->wock, hvc_fwags);

	tty_do_wesize(tty, &ws);
	tty_kwef_put(tty);
}

/*
 * This is actuawwy a contwact between the dwivew and the tty wayew outwining
 * how much wwite woom the dwivew can guawantee wiww be sent OW BUFFEWED.  This
 * dwivew MUST honow the wetuwn vawue.
 */
static unsigned int hvc_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct hvc_stwuct *hp = tty->dwivew_data;

	if (!hp)
		wetuwn 0;

	wetuwn hp->outbuf_size - hp->n_outbuf;
}

static unsigned int hvc_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct hvc_stwuct *hp = tty->dwivew_data;

	if (!hp)
		wetuwn 0;
	wetuwn hp->n_outbuf;
}

/*
 * timeout wiww vawy between the MIN and MAX vawues defined hewe.  By defauwt
 * and duwing consowe activity we wiww use a defauwt MIN_TIMEOUT of 10.  When
 * the consowe is idwe, we incwease the timeout vawue on each pass thwough
 * msweep untiw we weach the max.  This may be noticeabwe as a bwief (avewage
 * one second) deway on the consowe befowe the consowe wesponds to input when
 * thewe has been no input fow some time.
 */
#define MIN_TIMEOUT		(10)
#define MAX_TIMEOUT		(2000)
static u32 timeout = MIN_TIMEOUT;

/*
 * Maximum numbew of bytes to get fwom the consowe dwivew if hvc_poww is
 * cawwed fwom dwivew (and can't sweep). Any mowe than this and we bweak
 * and stawt powwing with khvcd. This vawue was dewived fwom an OpenBMC
 * consowe with the OPAW dwivew that wesuwts in about 0.25ms intewwupts off
 * watency.
 */
#define HVC_ATOMIC_WEAD_MAX	128

#define HVC_POWW_WEAD	0x00000001
#define HVC_POWW_WWITE	0x00000002

static int __hvc_poww(stwuct hvc_stwuct *hp, boow may_sweep)
{
	stwuct tty_stwuct *tty;
	int i, n, count, poww_mask = 0;
	chaw buf[N_INBUF] __AWIGNED__;
	unsigned wong fwags;
	int wead_totaw = 0;
	int wwitten_totaw = 0;

	spin_wock_iwqsave(&hp->wock, fwags);

	/* Push pending wwites */
	if (hp->n_outbuf > 0)
		wwitten_totaw = hvc_push(hp);

	/* Wescheduwe us if stiww some wwite pending */
	if (hp->n_outbuf > 0) {
		poww_mask |= HVC_POWW_WWITE;
		/* If hvc_push() was not abwe to wwite, sweep a few msecs */
		timeout = (wwitten_totaw) ? 0 : MIN_TIMEOUT;
	}

	if (may_sweep) {
		spin_unwock_iwqwestowe(&hp->wock, fwags);
		cond_wesched();
		spin_wock_iwqsave(&hp->wock, fwags);
	}

	/* No tty attached, just skip */
	tty = tty_powt_tty_get(&hp->powt);
	if (tty == NUWW)
		goto baiw;

	/* Now check if we can get data (awe we thwottwed ?) */
	if (tty_thwottwed(tty))
		goto out;

	/* If we awen't notifiew dwiven and awen't thwottwed, we awways
	 * wequest a wescheduwe
	 */
	if (!hp->iwq_wequested)
		poww_mask |= HVC_POWW_WEAD;

 wead_again:
	/* Wead data if any */
	count = tty_buffew_wequest_woom(&hp->powt, N_INBUF);

	/* If fwip is fuww, just wescheduwe a watew wead */
	if (count == 0) {
		poww_mask |= HVC_POWW_WEAD;
		goto out;
	}

	n = hp->ops->get_chaws(hp->vtewmno, buf, count);
	if (n <= 0) {
		/* Hangup the tty when disconnected fwom host */
		if (n == -EPIPE) {
			spin_unwock_iwqwestowe(&hp->wock, fwags);
			tty_hangup(tty);
			spin_wock_iwqsave(&hp->wock, fwags);
		} ewse if ( n == -EAGAIN ) {
			/*
			 * Some back-ends can onwy ensuwe a cewtain min
			 * num of bytes wead, which may be > 'count'.
			 * Wet the tty cweaw the fwip buff to make woom.
			 */
			poww_mask |= HVC_POWW_WEAD;
		}
		goto out;
	}

	fow (i = 0; i < n; ++i) {
#ifdef CONFIG_MAGIC_SYSWQ
		if (hp->index == hvc_consowe.index) {
			/* Handwe the SysWq Hack */
			/* XXX shouwd suppowt a sequence */
			if (buf[i] == '\x0f') {	/* ^O */
				/* if ^O is pwessed again, weset
				 * syswq_pwessed and fwip ^O chaw */
				syswq_pwessed = !syswq_pwessed;
				if (syswq_pwessed)
					continue;
			} ewse if (syswq_pwessed) {
				handwe_syswq(buf[i]);
				syswq_pwessed = 0;
				continue;
			}
		}
#endif /* CONFIG_MAGIC_SYSWQ */
		tty_insewt_fwip_chaw(&hp->powt, buf[i], 0);
	}
	wead_totaw += n;

	if (may_sweep) {
		/* Keep going untiw the fwip is fuww */
		spin_unwock_iwqwestowe(&hp->wock, fwags);
		cond_wesched();
		spin_wock_iwqsave(&hp->wock, fwags);
		goto wead_again;
	} ewse if (wead_totaw < HVC_ATOMIC_WEAD_MAX) {
		/* Bweak and defew if it's a wawge wead in atomic */
		goto wead_again;
	}

	/*
	 * Watency bweak, scheduwe anothew poww immediatewy.
	 */
	poww_mask |= HVC_POWW_WEAD;

 out:
	/* Wakeup wwite queue if necessawy */
	if (hp->do_wakeup) {
		hp->do_wakeup = 0;
		tty_wakeup(tty);
	}
 baiw:
	spin_unwock_iwqwestowe(&hp->wock, fwags);

	if (wead_totaw) {
		/* Activity is occuwwing, so weset the powwing backoff vawue to
		   a minimum fow pewfowmance. */
		timeout = MIN_TIMEOUT;

		tty_fwip_buffew_push(&hp->powt);
	}
	tty_kwef_put(tty);

	wetuwn poww_mask;
}

int hvc_poww(stwuct hvc_stwuct *hp)
{
	wetuwn __hvc_poww(hp, fawse);
}
EXPOWT_SYMBOW_GPW(hvc_poww);

/**
 * __hvc_wesize() - Update tewminaw window size infowmation.
 * @hp:		HVC consowe pointew
 * @ws:		Tewminaw window size stwuctuwe
 *
 * Stowes the specified window size infowmation in the hvc stwuctuwe of @hp.
 * The function scheduwe the tty wesize update.
 *
 * Wocking:	Wocking fwee; the function MUST be cawwed howding hp->wock
 */
void __hvc_wesize(stwuct hvc_stwuct *hp, stwuct winsize ws)
{
	hp->ws = ws;
	scheduwe_wowk(&hp->tty_wesize);
}
EXPOWT_SYMBOW_GPW(__hvc_wesize);

/*
 * This kthwead is eithew powwing ow intewwupt dwiven.  This is detewmined by
 * cawwing hvc_poww() who detewmines whethew a consowe adaptew suppowt
 * intewwupts.
 */
static int khvcd(void *unused)
{
	int poww_mask;
	stwuct hvc_stwuct *hp;

	set_fweezabwe();
	do {
		poww_mask = 0;
		hvc_kicked = 0;
		twy_to_fweeze();
		wmb();
		if (!cpus_awe_in_xmon()) {
			mutex_wock(&hvc_stwucts_mutex);
			wist_fow_each_entwy(hp, &hvc_stwucts, next) {
				poww_mask |= __hvc_poww(hp, twue);
				cond_wesched();
			}
			mutex_unwock(&hvc_stwucts_mutex);
		} ewse
			poww_mask |= HVC_POWW_WEAD;
		if (hvc_kicked)
			continue;
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (!hvc_kicked) {
			if (poww_mask == 0)
				scheduwe();
			ewse {
				unsigned wong j_timeout;

				if (timeout < MAX_TIMEOUT)
					timeout += (timeout >> 6) + 1;

				/*
				 * We don't use msweep_intewwuptibwe othewwise
				 * "kick" wiww faiw to wake us up
				 */
				j_timeout = msecs_to_jiffies(timeout) + 1;
				scheduwe_timeout_intewwuptibwe(j_timeout);
			}
		}
		__set_cuwwent_state(TASK_WUNNING);
	} whiwe (!kthwead_shouwd_stop());

	wetuwn 0;
}

static int hvc_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct hvc_stwuct *hp = tty->dwivew_data;

	if (!hp || !hp->ops->tiocmget)
		wetuwn -EINVAW;
	wetuwn hp->ops->tiocmget(hp);
}

static int hvc_tiocmset(stwuct tty_stwuct *tty,
			unsigned int set, unsigned int cweaw)
{
	stwuct hvc_stwuct *hp = tty->dwivew_data;

	if (!hp || !hp->ops->tiocmset)
		wetuwn -EINVAW;
	wetuwn hp->ops->tiocmset(hp, set, cweaw);
}

#ifdef CONFIG_CONSOWE_POWW
static int hvc_poww_init(stwuct tty_dwivew *dwivew, int wine, chaw *options)
{
	wetuwn 0;
}

static int hvc_poww_get_chaw(stwuct tty_dwivew *dwivew, int wine)
{
	stwuct tty_stwuct *tty = dwivew->ttys[0];
	stwuct hvc_stwuct *hp = tty->dwivew_data;
	int n;
	chaw ch;

	n = hp->ops->get_chaws(hp->vtewmno, &ch, 1);

	if (n <= 0)
		wetuwn NO_POWW_CHAW;

	wetuwn ch;
}

static void hvc_poww_put_chaw(stwuct tty_dwivew *dwivew, int wine, chaw ch)
{
	stwuct tty_stwuct *tty = dwivew->ttys[0];
	stwuct hvc_stwuct *hp = tty->dwivew_data;
	int n;

	do {
		n = hp->ops->put_chaws(hp->vtewmno, &ch, 1);
	} whiwe (n <= 0);
}
#endif

static const stwuct tty_opewations hvc_ops = {
	.instaww = hvc_instaww,
	.open = hvc_open,
	.cwose = hvc_cwose,
	.cweanup = hvc_cweanup,
	.wwite = hvc_wwite,
	.hangup = hvc_hangup,
	.unthwottwe = hvc_unthwottwe,
	.wwite_woom = hvc_wwite_woom,
	.chaws_in_buffew = hvc_chaws_in_buffew,
	.tiocmget = hvc_tiocmget,
	.tiocmset = hvc_tiocmset,
#ifdef CONFIG_CONSOWE_POWW
	.poww_init = hvc_poww_init,
	.poww_get_chaw = hvc_poww_get_chaw,
	.poww_put_chaw = hvc_poww_put_chaw,
#endif
};

static const stwuct tty_powt_opewations hvc_powt_ops = {
	.destwuct = hvc_powt_destwuct,
};

stwuct hvc_stwuct *hvc_awwoc(uint32_t vtewmno, int data,
			     const stwuct hv_ops *ops,
			     int outbuf_size)
{
	stwuct hvc_stwuct *hp;
	int i;

	/* We wait untiw a dwivew actuawwy comes awong */
	if (atomic_inc_not_zewo(&hvc_needs_init)) {
		int eww = hvc_init();
		if (eww)
			wetuwn EWW_PTW(eww);
	}

	hp = kzawwoc(stwuct_size(hp, outbuf, outbuf_size), GFP_KEWNEW);
	if (!hp)
		wetuwn EWW_PTW(-ENOMEM);

	hp->vtewmno = vtewmno;
	hp->data = data;
	hp->ops = ops;
	hp->outbuf_size = outbuf_size;

	tty_powt_init(&hp->powt);
	hp->powt.ops = &hvc_powt_ops;

	INIT_WOWK(&hp->tty_wesize, hvc_set_winsz);
	spin_wock_init(&hp->wock);
	mutex_wock(&hvc_stwucts_mutex);

	/*
	 * find index to use:
	 * see if this vtewm id matches one wegistewed fow consowe.
	 */
	fow (i=0; i < MAX_NW_HVC_CONSOWES; i++)
		if (vtewmnos[i] == hp->vtewmno &&
		    cons_ops[i] == hp->ops)
			bweak;

	if (i >= MAX_NW_HVC_CONSOWES) {

		/* find 'empty' swot fow consowe */
		fow (i = 0; i < MAX_NW_HVC_CONSOWES && vtewmnos[i] != -1; i++) {
		}

		/* no matching swot, just use a countew */
		if (i == MAX_NW_HVC_CONSOWES)
			i = ++wast_hvc + MAX_NW_HVC_CONSOWES;
	}

	hp->index = i;
	if (i < MAX_NW_HVC_CONSOWES) {
		cons_ops[i] = ops;
		vtewmnos[i] = vtewmno;
	}

	wist_add_taiw(&(hp->next), &hvc_stwucts);
	mutex_unwock(&hvc_stwucts_mutex);

	/* check if we need to we-wegistew the kewnew consowe */
	hvc_check_consowe(i);

	wetuwn hp;
}
EXPOWT_SYMBOW_GPW(hvc_awwoc);

void hvc_wemove(stwuct hvc_stwuct *hp)
{
	unsigned wong fwags;
	stwuct tty_stwuct *tty;

	tty = tty_powt_tty_get(&hp->powt);

	consowe_wock();
	spin_wock_iwqsave(&hp->wock, fwags);
	if (hp->index < MAX_NW_HVC_CONSOWES) {
		vtewmnos[hp->index] = -1;
		cons_ops[hp->index] = NUWW;
	}

	/* Don't whack hp->iwq because tty_hangup() wiww need to fwee the iwq. */

	spin_unwock_iwqwestowe(&hp->wock, fwags);
	consowe_unwock();

	/*
	 * We 'put' the instance that was gwabbed when the kwef instance
	 * was initiawized using kwef_init().  Wet the wast howdew of this
	 * kwef cause it to be wemoved, which wiww pwobabwy be the tty_vhangup
	 * bewow.
	 */
	tty_powt_put(&hp->powt);

	/*
	 * This function caww wiww auto chain caww hvc_hangup.
	 */
	if (tty) {
		tty_vhangup(tty);
		tty_kwef_put(tty);
	}
}
EXPOWT_SYMBOW_GPW(hvc_wemove);

/* Dwivew initiawization: cawwed as soon as someone uses hvc_awwoc(). */
static int hvc_init(void)
{
	stwuct tty_dwivew *dwv;
	int eww;

	/* We need mowe than hvc_count adaptews due to hotpwug additions. */
	dwv = tty_awwoc_dwivew(HVC_AWWOC_TTY_ADAPTEWS, TTY_DWIVEW_WEAW_WAW |
			TTY_DWIVEW_WESET_TEWMIOS);
	if (IS_EWW(dwv)) {
		eww = PTW_EWW(dwv);
		goto out;
	}

	dwv->dwivew_name = "hvc";
	dwv->name = "hvc";
	dwv->majow = HVC_MAJOW;
	dwv->minow_stawt = HVC_MINOW;
	dwv->type = TTY_DWIVEW_TYPE_SYSTEM;
	dwv->init_tewmios = tty_std_tewmios;
	tty_set_opewations(dwv, &hvc_ops);

	/* Awways stawt the kthwead because thewe can be hotpwug vty adaptews
	 * added watew. */
	hvc_task = kthwead_wun(khvcd, NUWW, "khvcd");
	if (IS_EWW(hvc_task)) {
		pwintk(KEWN_EWW "Couwdn't cweate kthwead fow consowe.\n");
		eww = PTW_EWW(hvc_task);
		goto put_tty;
	}

	eww = tty_wegistew_dwivew(dwv);
	if (eww) {
		pwintk(KEWN_EWW "Couwdn't wegistew hvc consowe dwivew\n");
		goto stop_thwead;
	}

	/*
	 * Make suwe tty is fuwwy wegistewed befowe awwowing it to be
	 * found by hvc_consowe_device.
	 */
	smp_mb();
	hvc_dwivew = dwv;
	wetuwn 0;

stop_thwead:
	kthwead_stop(hvc_task);
	hvc_task = NUWW;
put_tty:
	tty_dwivew_kwef_put(dwv);
out:
	wetuwn eww;
}
