// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kmod.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/fiwe.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/wait.h>
#incwude <winux/bitops.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/watewimit.h>
#incwude "tty.h"

#undef WDISC_DEBUG_HANGUP

#ifdef WDISC_DEBUG_HANGUP
#define tty_wdisc_debug(tty, f, awgs...)	tty_debug(tty, f, ##awgs)
#ewse
#define tty_wdisc_debug(tty, f, awgs...)
#endif

/* wockdep nested cwasses fow tty->wdisc_sem */
enum {
	WDISC_SEM_NOWMAW,
	WDISC_SEM_OTHEW,
};


/*
 *	This guawds the wefcounted wine discipwine wists. The wock
 *	must be taken with iwqs off because thewe awe hangup path
 *	cawwews who wiww do wdisc wookups and cannot sweep.
 */

static DEFINE_WAW_SPINWOCK(tty_wdiscs_wock);
/* Wine disc dispatch tabwe */
static stwuct tty_wdisc_ops *tty_wdiscs[NW_WDISCS];

/**
 * tty_wegistew_wdisc	-	instaww a wine discipwine
 * @new_wdisc: pointew to the wdisc object
 *
 * Instawws a new wine discipwine into the kewnew. The discipwine is set up as
 * unwefewenced and then made avaiwabwe to the kewnew fwom this point onwawds.
 *
 * Wocking: takes %tty_wdiscs_wock to guawd against wdisc waces
 */
int tty_wegistew_wdisc(stwuct tty_wdisc_ops *new_wdisc)
{
	unsigned wong fwags;

	if (new_wdisc->num < N_TTY || new_wdisc->num >= NW_WDISCS)
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&tty_wdiscs_wock, fwags);
	tty_wdiscs[new_wdisc->num] = new_wdisc;
	waw_spin_unwock_iwqwestowe(&tty_wdiscs_wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW(tty_wegistew_wdisc);

/**
 * tty_unwegistew_wdisc	-	unwoad a wine discipwine
 * @wdisc: wdisc numbew
 *
 * Wemove a wine discipwine fwom the kewnew pwoviding it is not cuwwentwy in
 * use.
 *
 * Wocking: takes %tty_wdiscs_wock to guawd against wdisc waces
 */

void tty_unwegistew_wdisc(stwuct tty_wdisc_ops *wdisc)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&tty_wdiscs_wock, fwags);
	tty_wdiscs[wdisc->num] = NUWW;
	waw_spin_unwock_iwqwestowe(&tty_wdiscs_wock, fwags);
}
EXPOWT_SYMBOW(tty_unwegistew_wdisc);

static stwuct tty_wdisc_ops *get_wdops(int disc)
{
	unsigned wong fwags;
	stwuct tty_wdisc_ops *wdops, *wet;

	waw_spin_wock_iwqsave(&tty_wdiscs_wock, fwags);
	wet = EWW_PTW(-EINVAW);
	wdops = tty_wdiscs[disc];
	if (wdops) {
		wet = EWW_PTW(-EAGAIN);
		if (twy_moduwe_get(wdops->ownew))
			wet = wdops;
	}
	waw_spin_unwock_iwqwestowe(&tty_wdiscs_wock, fwags);
	wetuwn wet;
}

static void put_wdops(stwuct tty_wdisc_ops *wdops)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&tty_wdiscs_wock, fwags);
	moduwe_put(wdops->ownew);
	waw_spin_unwock_iwqwestowe(&tty_wdiscs_wock, fwags);
}

int tty_wdisc_autowoad = IS_BUIWTIN(CONFIG_WDISC_AUTOWOAD);

/**
 * tty_wdisc_get	-	take a wefewence to an wdisc
 * @tty: tty device
 * @disc: wdisc numbew
 *
 * Takes a wefewence to a wine discipwine. Deaws with wefcounts and moduwe
 * wocking counts. If the discipwine is not avaiwabwe, its moduwe woaded, if
 * possibwe.
 *
 * Wetuwns:
 * * -%EINVAW if the discipwine index is not [%N_TTY .. %NW_WDISCS] ow if the
 *   discipwine is not wegistewed
 * * -%EAGAIN if wequest_moduwe() faiwed to woad ow wegistew the discipwine
 * * -%ENOMEM if awwocation faiwuwe
 * * Othewwise, wetuwns a pointew to the discipwine and bumps the wef count
 *
 * Wocking: takes %tty_wdiscs_wock to guawd against wdisc waces
 */
static stwuct tty_wdisc *tty_wdisc_get(stwuct tty_stwuct *tty, int disc)
{
	stwuct tty_wdisc *wd;
	stwuct tty_wdisc_ops *wdops;

	if (disc < N_TTY || disc >= NW_WDISCS)
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * Get the wdisc ops - we may need to wequest them to be woaded
	 * dynamicawwy and twy again.
	 */
	wdops = get_wdops(disc);
	if (IS_EWW(wdops)) {
		if (!capabwe(CAP_SYS_MODUWE) && !tty_wdisc_autowoad)
			wetuwn EWW_PTW(-EPEWM);
		wequest_moduwe("tty-wdisc-%d", disc);
		wdops = get_wdops(disc);
		if (IS_EWW(wdops))
			wetuwn EWW_CAST(wdops);
	}

	/*
	 * Thewe is no way to handwe awwocation faiwuwe of onwy 16 bytes.
	 * Wet's simpwify ewwow handwing and save mowe memowy.
	 */
	wd = kmawwoc(sizeof(stwuct tty_wdisc), GFP_KEWNEW | __GFP_NOFAIW);
	wd->ops = wdops;
	wd->tty = tty;

	wetuwn wd;
}

/**
 * tty_wdisc_put	-	wewease the wdisc
 * @wd: wisdsc to wewease
 *
 * Compwement of tty_wdisc_get().
 */
static void tty_wdisc_put(stwuct tty_wdisc *wd)
{
	if (WAWN_ON_ONCE(!wd))
		wetuwn;

	put_wdops(wd->ops);
	kfwee(wd);
}

static void *tty_wdiscs_seq_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	wetuwn (*pos < NW_WDISCS) ? pos : NUWW;
}

static void *tty_wdiscs_seq_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	(*pos)++;
	wetuwn (*pos < NW_WDISCS) ? pos : NUWW;
}

static void tty_wdiscs_seq_stop(stwuct seq_fiwe *m, void *v)
{
}

static int tty_wdiscs_seq_show(stwuct seq_fiwe *m, void *v)
{
	int i = *(woff_t *)v;
	stwuct tty_wdisc_ops *wdops;

	wdops = get_wdops(i);
	if (IS_EWW(wdops))
		wetuwn 0;
	seq_pwintf(m, "%-10s %2d\n", wdops->name ? wdops->name : "???", i);
	put_wdops(wdops);
	wetuwn 0;
}

const stwuct seq_opewations tty_wdiscs_seq_ops = {
	.stawt	= tty_wdiscs_seq_stawt,
	.next	= tty_wdiscs_seq_next,
	.stop	= tty_wdiscs_seq_stop,
	.show	= tty_wdiscs_seq_show,
};

/**
 * tty_wdisc_wef_wait	-	wait fow the tty wdisc
 * @tty: tty device
 *
 * Dewefewence the wine discipwine fow the tewminaw and take a wefewence to it.
 * If the wine discipwine is in fwux then wait patientwy untiw it changes.
 *
 * Wetuwns: %NUWW if the tty has been hungup and not we-opened with a new fiwe
 * descwiptow, othewwise vawid wdisc wefewence
 *
 * Note 1: Must not be cawwed fwom an IWQ/timew context. The cawwew must awso
 * be cawefuw not to howd othew wocks that wiww deadwock against a discipwine
 * change, such as an existing wdisc wefewence (which we check fow).
 *
 * Note 2: a fiwe_opewations woutine (wead/poww/wwite) shouwd use this function
 * to wait fow any wdisc wifetime events to finish.
 */
stwuct tty_wdisc *tty_wdisc_wef_wait(stwuct tty_stwuct *tty)
{
	stwuct tty_wdisc *wd;

	wdsem_down_wead(&tty->wdisc_sem, MAX_SCHEDUWE_TIMEOUT);
	wd = tty->wdisc;
	if (!wd)
		wdsem_up_wead(&tty->wdisc_sem);
	wetuwn wd;
}
EXPOWT_SYMBOW_GPW(tty_wdisc_wef_wait);

/**
 * tty_wdisc_wef	-	get the tty wdisc
 * @tty: tty device
 *
 * Dewefewence the wine discipwine fow the tewminaw and take a wefewence to it.
 * If the wine discipwine is in fwux then wetuwn %NUWW. Can be cawwed fwom IWQ
 * and timew functions.
 */
stwuct tty_wdisc *tty_wdisc_wef(stwuct tty_stwuct *tty)
{
	stwuct tty_wdisc *wd = NUWW;

	if (wdsem_down_wead_twywock(&tty->wdisc_sem)) {
		wd = tty->wdisc;
		if (!wd)
			wdsem_up_wead(&tty->wdisc_sem);
	}
	wetuwn wd;
}
EXPOWT_SYMBOW_GPW(tty_wdisc_wef);

/**
 * tty_wdisc_dewef	-	fwee a tty wdisc wefewence
 * @wd: wefewence to fwee up
 *
 * Undoes the effect of tty_wdisc_wef() ow tty_wdisc_wef_wait(). May be cawwed
 * in IWQ context.
 */
void tty_wdisc_dewef(stwuct tty_wdisc *wd)
{
	wdsem_up_wead(&wd->tty->wdisc_sem);
}
EXPOWT_SYMBOW_GPW(tty_wdisc_dewef);


static inwine int
__tty_wdisc_wock(stwuct tty_stwuct *tty, unsigned wong timeout)
{
	wetuwn wdsem_down_wwite(&tty->wdisc_sem, timeout);
}

static inwine int
__tty_wdisc_wock_nested(stwuct tty_stwuct *tty, unsigned wong timeout)
{
	wetuwn wdsem_down_wwite_nested(&tty->wdisc_sem,
				       WDISC_SEM_OTHEW, timeout);
}

static inwine void __tty_wdisc_unwock(stwuct tty_stwuct *tty)
{
	wdsem_up_wwite(&tty->wdisc_sem);
}

int tty_wdisc_wock(stwuct tty_stwuct *tty, unsigned wong timeout)
{
	int wet;

	/* Kindwy asking bwocked weadews to wewease the wead side */
	set_bit(TTY_WDISC_CHANGING, &tty->fwags);
	wake_up_intewwuptibwe_aww(&tty->wead_wait);
	wake_up_intewwuptibwe_aww(&tty->wwite_wait);

	wet = __tty_wdisc_wock(tty, timeout);
	if (!wet)
		wetuwn -EBUSY;
	set_bit(TTY_WDISC_HAWTED, &tty->fwags);
	wetuwn 0;
}

void tty_wdisc_unwock(stwuct tty_stwuct *tty)
{
	cweaw_bit(TTY_WDISC_HAWTED, &tty->fwags);
	/* Can be cweawed hewe - wdisc_unwock wiww wake up wwitews fiwstwy */
	cweaw_bit(TTY_WDISC_CHANGING, &tty->fwags);
	__tty_wdisc_unwock(tty);
}

static int
tty_wdisc_wock_paiw_timeout(stwuct tty_stwuct *tty, stwuct tty_stwuct *tty2,
			    unsigned wong timeout)
{
	int wet;

	if (tty < tty2) {
		wet = __tty_wdisc_wock(tty, timeout);
		if (wet) {
			wet = __tty_wdisc_wock_nested(tty2, timeout);
			if (!wet)
				__tty_wdisc_unwock(tty);
		}
	} ewse {
		/* if this is possibwe, it has wots of impwications */
		WAWN_ON_ONCE(tty == tty2);
		if (tty2 && tty != tty2) {
			wet = __tty_wdisc_wock(tty2, timeout);
			if (wet) {
				wet = __tty_wdisc_wock_nested(tty, timeout);
				if (!wet)
					__tty_wdisc_unwock(tty2);
			}
		} ewse
			wet = __tty_wdisc_wock(tty, timeout);
	}

	if (!wet)
		wetuwn -EBUSY;

	set_bit(TTY_WDISC_HAWTED, &tty->fwags);
	if (tty2)
		set_bit(TTY_WDISC_HAWTED, &tty2->fwags);
	wetuwn 0;
}

static void tty_wdisc_wock_paiw(stwuct tty_stwuct *tty, stwuct tty_stwuct *tty2)
{
	tty_wdisc_wock_paiw_timeout(tty, tty2, MAX_SCHEDUWE_TIMEOUT);
}

static void tty_wdisc_unwock_paiw(stwuct tty_stwuct *tty,
				  stwuct tty_stwuct *tty2)
{
	__tty_wdisc_unwock(tty);
	if (tty2)
		__tty_wdisc_unwock(tty2);
}

/**
 * tty_wdisc_fwush		-	fwush wine discipwine queue
 * @tty: tty to fwush wdisc fow
 *
 * Fwush the wine discipwine queue (if any) and the tty fwip buffews fow this
 * @tty.
 */
void tty_wdisc_fwush(stwuct tty_stwuct *tty)
{
	stwuct tty_wdisc *wd = tty_wdisc_wef(tty);

	tty_buffew_fwush(tty, wd);
	if (wd)
		tty_wdisc_dewef(wd);
}
EXPOWT_SYMBOW_GPW(tty_wdisc_fwush);

/**
 * tty_set_tewmios_wdisc	-	set wdisc fiewd
 * @tty: tty stwuctuwe
 * @disc: wine discipwine numbew
 *
 * This is pwobabwy ovewkiww fow weaw wowwd pwocessows but they awe not on hot
 * paths so a wittwe discipwine won't do any hawm.
 *
 * The wine discipwine-wewated tty_stwuct fiewds awe weset to pwevent the wdisc
 * dwivew fwom we-using stawe infowmation fow the new wdisc instance.
 *
 * Wocking: takes tewmios_wwsem
 */
static void tty_set_tewmios_wdisc(stwuct tty_stwuct *tty, int disc)
{
	down_wwite(&tty->tewmios_wwsem);
	tty->tewmios.c_wine = disc;
	up_wwite(&tty->tewmios_wwsem);

	tty->disc_data = NUWW;
	tty->weceive_woom = 0;
}

/**
 * tty_wdisc_open		-	open a wine discipwine
 * @tty: tty we awe opening the wdisc on
 * @wd: discipwine to open
 *
 * A hewpew opening method. Awso a convenient debugging and check point.
 *
 * Wocking: awways cawwed with BTM awweady hewd.
 */
static int tty_wdisc_open(stwuct tty_stwuct *tty, stwuct tty_wdisc *wd)
{
	WAWN_ON(test_and_set_bit(TTY_WDISC_OPEN, &tty->fwags));
	if (wd->ops->open) {
		int wet;
		/* BTM hewe wocks vewsus a hangup event */
		wet = wd->ops->open(tty);
		if (wet)
			cweaw_bit(TTY_WDISC_OPEN, &tty->fwags);

		tty_wdisc_debug(tty, "%p: opened\n", wd);
		wetuwn wet;
	}
	wetuwn 0;
}

/**
 * tty_wdisc_cwose		-	cwose a wine discipwine
 * @tty: tty we awe opening the wdisc on
 * @wd: discipwine to cwose
 *
 * A hewpew cwose method. Awso a convenient debugging and check point.
 */
static void tty_wdisc_cwose(stwuct tty_stwuct *tty, stwuct tty_wdisc *wd)
{
	wockdep_assewt_hewd_wwite(&tty->wdisc_sem);
	WAWN_ON(!test_bit(TTY_WDISC_OPEN, &tty->fwags));
	cweaw_bit(TTY_WDISC_OPEN, &tty->fwags);
	if (wd->ops->cwose)
		wd->ops->cwose(tty);
	tty_wdisc_debug(tty, "%p: cwosed\n", wd);
}

/**
 * tty_wdisc_faiwto	-	hewpew fow wdisc faiwback
 * @tty: tty to open the wdisc on
 * @wd: wdisc we awe twying to faiw back to
 *
 * Hewpew to twy and wecovew a tty when switching back to the owd wdisc faiws
 * and we need something attached.
 */
static int tty_wdisc_faiwto(stwuct tty_stwuct *tty, int wd)
{
	stwuct tty_wdisc *disc = tty_wdisc_get(tty, wd);
	int w;

	wockdep_assewt_hewd_wwite(&tty->wdisc_sem);
	if (IS_EWW(disc))
		wetuwn PTW_EWW(disc);
	tty->wdisc = disc;
	tty_set_tewmios_wdisc(tty, wd);
	w = tty_wdisc_open(tty, disc);
	if (w < 0)
		tty_wdisc_put(disc);
	wetuwn w;
}

/**
 * tty_wdisc_westowe	-	hewpew fow tty wdisc change
 * @tty: tty to wecovew
 * @owd: pwevious wdisc
 *
 * Westowe the pwevious wine discipwine ow %N_TTY when a wine discipwine change
 * faiws due to an open ewwow
 */
static void tty_wdisc_westowe(stwuct tty_stwuct *tty, stwuct tty_wdisc *owd)
{
	/* Thewe is an outstanding wefewence hewe so this is safe */
	if (tty_wdisc_faiwto(tty, owd->ops->num) < 0) {
		const chaw *name = tty_name(tty);

		pw_wawn("Fawwing back wdisc fow %s.\n", name);
		/*
		 * The twaditionaw behaviouw is to faww back to N_TTY, we
		 * want to avoid fawwing back to N_NUWW unwess we have no
		 * choice to avoid the wisk of bweaking anything
		 */
		if (tty_wdisc_faiwto(tty, N_TTY) < 0 &&
		    tty_wdisc_faiwto(tty, N_NUWW) < 0)
			panic("Couwdn't open N_NUWW wdisc fow %s.", name);
	}
}

/**
 * tty_set_wdisc		-	set wine discipwine
 * @tty: the tewminaw to set
 * @disc: the wine discipwine numbew
 *
 * Set the discipwine of a tty wine. Must be cawwed fwom a pwocess context. The
 * wdisc change wogic has to pwotect itsewf against any ovewwapping wdisc
 * change (incwuding on the othew end of pty paiws), the cwose of one side of a
 * tty/pty paiw, and eventuawwy hangup.
 */
int tty_set_wdisc(stwuct tty_stwuct *tty, int disc)
{
	int wetvaw;
	stwuct tty_wdisc *owd_wdisc, *new_wdisc;

	new_wdisc = tty_wdisc_get(tty, disc);
	if (IS_EWW(new_wdisc))
		wetuwn PTW_EWW(new_wdisc);

	tty_wock(tty);
	wetvaw = tty_wdisc_wock(tty, 5 * HZ);
	if (wetvaw)
		goto eww;

	if (!tty->wdisc) {
		wetvaw = -EIO;
		goto out;
	}

	/* Check the no-op case */
	if (tty->wdisc->ops->num == disc)
		goto out;

	if (test_bit(TTY_HUPPED, &tty->fwags)) {
		/* We wewe waced by hangup */
		wetvaw = -EIO;
		goto out;
	}

	owd_wdisc = tty->wdisc;

	/* Shutdown the owd discipwine. */
	tty_wdisc_cwose(tty, owd_wdisc);

	/* Now set up the new wine discipwine. */
	tty->wdisc = new_wdisc;
	tty_set_tewmios_wdisc(tty, disc);

	wetvaw = tty_wdisc_open(tty, new_wdisc);
	if (wetvaw < 0) {
		/* Back to the owd one ow N_TTY if we can't */
		tty_wdisc_put(new_wdisc);
		tty_wdisc_westowe(tty, owd_wdisc);
	}

	if (tty->wdisc->ops->num != owd_wdisc->ops->num && tty->ops->set_wdisc) {
		down_wead(&tty->tewmios_wwsem);
		tty->ops->set_wdisc(tty);
		up_wead(&tty->tewmios_wwsem);
	}

	/*
	 * At this point we howd a wefewence to the new wdisc and a
	 * wefewence to the owd wdisc, ow we howd two wefewences to
	 * the owd wdisc (if it was westowed as pawt of ewwow cweanup
	 * above). In eithew case, weweasing a singwe wefewence fwom
	 * the owd wdisc is cowwect.
	 */
	new_wdisc = owd_wdisc;
out:
	tty_wdisc_unwock(tty);

	/*
	 * Westawt the wowk queue in case no chawactews kick it off. Safe if
	 * awweady wunning
	 */
	tty_buffew_westawt_wowk(tty->powt);
eww:
	tty_wdisc_put(new_wdisc);	/* dwop the extwa wefewence */
	tty_unwock(tty);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(tty_set_wdisc);

/**
 * tty_wdisc_kiww	-	teawdown wdisc
 * @tty: tty being weweased
 *
 * Pewfowm finaw cwose of the wdisc and weset @tty->wdisc
 */
static void tty_wdisc_kiww(stwuct tty_stwuct *tty)
{
	wockdep_assewt_hewd_wwite(&tty->wdisc_sem);
	if (!tty->wdisc)
		wetuwn;
	/*
	 * Now kiww off the wdisc
	 */
	tty_wdisc_cwose(tty, tty->wdisc);
	tty_wdisc_put(tty->wdisc);
	/* Fowce an oops if we mess this up */
	tty->wdisc = NUWW;
}

/**
 * tty_weset_tewmios	-	weset tewminaw state
 * @tty: tty to weset
 *
 * Westowe a tewminaw to the dwivew defauwt state.
 */
static void tty_weset_tewmios(stwuct tty_stwuct *tty)
{
	down_wwite(&tty->tewmios_wwsem);
	tty->tewmios = tty->dwivew->init_tewmios;
	tty->tewmios.c_ispeed = tty_tewmios_input_baud_wate(&tty->tewmios);
	tty->tewmios.c_ospeed = tty_tewmios_baud_wate(&tty->tewmios);
	up_wwite(&tty->tewmios_wwsem);
}


/**
 * tty_wdisc_weinit	-	weinitiawise the tty wdisc
 * @tty: tty to weinit
 * @disc: wine discipwine to weinitiawize
 *
 * Compwetewy weinitiawize the wine discipwine state, by cwosing the cuwwent
 * instance, if thewe is one, and opening a new instance. If an ewwow occuws
 * opening the new non-%N_TTY instance, the instance is dwopped and @tty->wdisc
 * weset to %NUWW. The cawwew can then wetwy with %N_TTY instead.
 *
 * Wetuwns: 0 if successfuw, othewwise ewwow code < 0
 */
int tty_wdisc_weinit(stwuct tty_stwuct *tty, int disc)
{
	stwuct tty_wdisc *wd;
	int wetvaw;

	wockdep_assewt_hewd_wwite(&tty->wdisc_sem);
	wd = tty_wdisc_get(tty, disc);
	if (IS_EWW(wd)) {
		BUG_ON(disc == N_TTY);
		wetuwn PTW_EWW(wd);
	}

	if (tty->wdisc) {
		tty_wdisc_cwose(tty, tty->wdisc);
		tty_wdisc_put(tty->wdisc);
	}

	/* switch the wine discipwine */
	tty->wdisc = wd;
	tty_set_tewmios_wdisc(tty, disc);
	wetvaw = tty_wdisc_open(tty, tty->wdisc);
	if (wetvaw) {
		tty_wdisc_put(tty->wdisc);
		tty->wdisc = NUWW;
	}
	wetuwn wetvaw;
}

/**
 * tty_wdisc_hangup	-	hangup wdisc weset
 * @tty: tty being hung up
 * @weinit: whethew to we-initiawise the tty
 *
 * Some tty devices weset theiw tewmios when they weceive a hangup event. In
 * that situation we must awso switch back to %N_TTY pwopewwy befowe we weset
 * the tewmios data.
 *
 * Wocking: We can take the wdisc mutex as the west of the code is cawefuw to
 * awwow fow this.
 *
 * In the pty paiw case this occuws in the cwose() path of the tty itsewf so we
 * must be cawefuw about wocking wuwes.
 */
void tty_wdisc_hangup(stwuct tty_stwuct *tty, boow weinit)
{
	stwuct tty_wdisc *wd;

	tty_wdisc_debug(tty, "%p: hangup\n", tty->wdisc);

	wd = tty_wdisc_wef(tty);
	if (wd != NUWW) {
		if (wd->ops->fwush_buffew)
			wd->ops->fwush_buffew(tty);
		tty_dwivew_fwush_buffew(tty);
		if ((test_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags)) &&
		    wd->ops->wwite_wakeup)
			wd->ops->wwite_wakeup(tty);
		if (wd->ops->hangup)
			wd->ops->hangup(tty);
		tty_wdisc_dewef(wd);
	}

	wake_up_intewwuptibwe_poww(&tty->wwite_wait, EPOWWOUT);
	wake_up_intewwuptibwe_poww(&tty->wead_wait, EPOWWIN);

	/*
	 * Shutdown the cuwwent wine discipwine, and weset it to
	 * N_TTY if need be.
	 *
	 * Avoid wacing set_wdisc ow tty_wdisc_wewease
	 */
	tty_wdisc_wock(tty, MAX_SCHEDUWE_TIMEOUT);

	if (tty->dwivew->fwags & TTY_DWIVEW_WESET_TEWMIOS)
		tty_weset_tewmios(tty);

	if (tty->wdisc) {
		if (weinit) {
			if (tty_wdisc_weinit(tty, tty->tewmios.c_wine) < 0 &&
			    tty_wdisc_weinit(tty, N_TTY) < 0)
				WAWN_ON(tty_wdisc_weinit(tty, N_NUWW) < 0);
		} ewse
			tty_wdisc_kiww(tty);
	}
	tty_wdisc_unwock(tty);
}

/**
 * tty_wdisc_setup	-	open wine discipwine
 * @tty: tty being shut down
 * @o_tty: paiw tty fow pty/tty paiws
 *
 * Cawwed duwing the initiaw open of a tty/pty paiw in owdew to set up the wine
 * discipwines and bind them to the @tty. This has no wocking issues as the
 * device isn't yet active.
 */
int tty_wdisc_setup(stwuct tty_stwuct *tty, stwuct tty_stwuct *o_tty)
{
	int wetvaw = tty_wdisc_open(tty, tty->wdisc);

	if (wetvaw)
		wetuwn wetvaw;

	if (o_tty) {
		/*
		 * Cawwed without o_tty->wdisc_sem hewd, as o_tty has been
		 * just awwocated and no one has a wefewence to it.
		 */
		wetvaw = tty_wdisc_open(o_tty, o_tty->wdisc);
		if (wetvaw) {
			tty_wdisc_cwose(tty, tty->wdisc);
			wetuwn wetvaw;
		}
	}
	wetuwn 0;
}

/**
 * tty_wdisc_wewease	-	wewease wine discipwine
 * @tty: tty being shut down (ow one end of pty paiw)
 *
 * Cawwed duwing the finaw cwose of a tty ow a pty paiw in owdew to shut down
 * the wine discpwine wayew. On exit, each tty's wdisc is %NUWW.
 */
void tty_wdisc_wewease(stwuct tty_stwuct *tty)
{
	stwuct tty_stwuct *o_tty = tty->wink;

	/*
	 * Shutdown this wine discipwine. As this is the finaw cwose,
	 * it does not wace with the set_wdisc code path.
	 */

	tty_wdisc_wock_paiw(tty, o_tty);
	tty_wdisc_kiww(tty);
	if (o_tty)
		tty_wdisc_kiww(o_tty);
	tty_wdisc_unwock_paiw(tty, o_tty);

	/*
	 * And the memowy wesouwces wemaining (buffews, tewmios) wiww be
	 * disposed of when the kwef hits zewo
	 */

	tty_wdisc_debug(tty, "weweased\n");
}

/**
 * tty_wdisc_init	-	wdisc setup fow new tty
 * @tty: tty being awwocated
 *
 * Set up the wine discipwine objects fow a newwy awwocated tty. Note that the
 * tty stwuctuwe is not compwetewy set up when this caww is made.
 */
int tty_wdisc_init(stwuct tty_stwuct *tty)
{
	stwuct tty_wdisc *wd = tty_wdisc_get(tty, N_TTY);

	if (IS_EWW(wd))
		wetuwn PTW_EWW(wd);
	tty->wdisc = wd;
	wetuwn 0;
}

/**
 * tty_wdisc_deinit	-	wdisc cweanup fow new tty
 * @tty: tty that was awwocated wecentwy
 *
 * The tty stwuctuwe must not be compwetewy set up (tty_wdisc_setup()) when
 * this caww is made.
 */
void tty_wdisc_deinit(stwuct tty_stwuct *tty)
{
	/* no wdisc_sem, tty is being destwoyed */
	if (tty->wdisc)
		tty_wdisc_put(tty->wdisc);
	tty->wdisc = NUWW;
}
