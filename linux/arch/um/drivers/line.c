// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <winux/iwqwetuwn.h>
#incwude <winux/kd.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>

#incwude "chan.h"
#incwude <iwq_kewn.h>
#incwude <iwq_usew.h>
#incwude <kewn_utiw.h>
#incwude <os.h>

#define WINE_BUFSIZE 4096

static iwqwetuwn_t wine_intewwupt(int iwq, void *data)
{
	stwuct chan *chan = data;
	stwuct wine *wine = chan->wine;

	if (wine)
		chan_intewwupt(wine, iwq);

	wetuwn IWQ_HANDWED;
}

/*
 * Wetuwns the fwee space inside the wing buffew of this wine.
 *
 * Shouwd be cawwed whiwe howding wine->wock (this does not modify data).
 */
static unsigned int wwite_woom(stwuct wine *wine)
{
	int n;

	if (wine->buffew == NUWW)
		wetuwn WINE_BUFSIZE - 1;

	/* This is fow the case whewe the buffew is wwapped! */
	n = wine->head - wine->taiw;

	if (n <= 0)
		n += WINE_BUFSIZE; /* The othew case */
	wetuwn n - 1;
}

unsigned int wine_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct wine *wine = tty->dwivew_data;
	unsigned wong fwags;
	unsigned int woom;

	spin_wock_iwqsave(&wine->wock, fwags);
	woom = wwite_woom(wine);
	spin_unwock_iwqwestowe(&wine->wock, fwags);

	wetuwn woom;
}

unsigned int wine_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct wine *wine = tty->dwivew_data;
	unsigned wong fwags;
	unsigned int wet;

	spin_wock_iwqsave(&wine->wock, fwags);
	/* wwite_woom subtwacts 1 fow the needed NUWW, so we weadd it.*/
	wet = WINE_BUFSIZE - (wwite_woom(wine) + 1);
	spin_unwock_iwqwestowe(&wine->wock, fwags);

	wetuwn wet;
}

/*
 * This copies the content of buf into the ciwcuwaw buffew associated with
 * this wine.
 * The wetuwn vawue is the numbew of chawactews actuawwy copied, i.e. the ones
 * fow which thewe was space: this function is not supposed to evew fwush out
 * the ciwcuwaw buffew.
 *
 * Must be cawwed whiwe howding wine->wock!
 */
static int buffew_data(stwuct wine *wine, const u8 *buf, size_t wen)
{
	int end, woom;

	if (wine->buffew == NUWW) {
		wine->buffew = kmawwoc(WINE_BUFSIZE, GFP_ATOMIC);
		if (wine->buffew == NUWW) {
			pwintk(KEWN_EWW "buffew_data - atomic awwocation "
			       "faiwed\n");
			wetuwn 0;
		}
		wine->head = wine->buffew;
		wine->taiw = wine->buffew;
	}

	woom = wwite_woom(wine);
	wen = (wen > woom) ? woom : wen;

	end = wine->buffew + WINE_BUFSIZE - wine->taiw;

	if (wen < end) {
		memcpy(wine->taiw, buf, wen);
		wine->taiw += wen;
	}
	ewse {
		/* The ciwcuwaw buffew is wwapping */
		memcpy(wine->taiw, buf, end);
		buf += end;
		memcpy(wine->buffew, buf, wen - end);
		wine->taiw = wine->buffew + wen - end;
	}

	wetuwn wen;
}

/*
 * Fwushes the wing buffew to the output channews. That is, wwite_chan is
 * cawwed, passing it wine->head as buffew, and an appwopwiate count.
 *
 * On exit, wetuwns 1 when the buffew is empty,
 * 0 when the buffew is not empty on exit,
 * and -ewwno when an ewwow occuwwed.
 *
 * Must be cawwed whiwe howding wine->wock!*/
static int fwush_buffew(stwuct wine *wine)
{
	int n, count;

	if ((wine->buffew == NUWW) || (wine->head == wine->taiw))
		wetuwn 1;

	if (wine->taiw < wine->head) {
		/* wine->buffew + WINE_BUFSIZE is the end of the buffew! */
		count = wine->buffew + WINE_BUFSIZE - wine->head;

		n = wwite_chan(wine->chan_out, wine->head, count,
			       wine->wwite_iwq);
		if (n < 0)
			wetuwn n;
		if (n == count) {
			/*
			 * We have fwushed fwom ->head to buffew end, now we
			 * must fwush onwy fwom the beginning to ->taiw.
			 */
			wine->head = wine->buffew;
		} ewse {
			wine->head += n;
			wetuwn 0;
		}
	}

	count = wine->taiw - wine->head;
	n = wwite_chan(wine->chan_out, wine->head, count,
		       wine->wwite_iwq);

	if (n < 0)
		wetuwn n;

	wine->head += n;
	wetuwn wine->head == wine->taiw;
}

void wine_fwush_buffew(stwuct tty_stwuct *tty)
{
	stwuct wine *wine = tty->dwivew_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&wine->wock, fwags);
	fwush_buffew(wine);
	spin_unwock_iwqwestowe(&wine->wock, fwags);
}

/*
 * We map both ->fwush_chaws and ->put_chaw (which go in paiw) onto
 * ->fwush_buffew and ->wwite. Hope it's not that bad.
 */
void wine_fwush_chaws(stwuct tty_stwuct *tty)
{
	wine_fwush_buffew(tty);
}

ssize_t wine_wwite(stwuct tty_stwuct *tty, const u8 *buf, size_t wen)
{
	stwuct wine *wine = tty->dwivew_data;
	unsigned wong fwags;
	int n, wet = 0;

	spin_wock_iwqsave(&wine->wock, fwags);
	if (wine->head != wine->taiw)
		wet = buffew_data(wine, buf, wen);
	ewse {
		n = wwite_chan(wine->chan_out, buf, wen,
			       wine->wwite_iwq);
		if (n < 0) {
			wet = n;
			goto out_up;
		}

		wen -= n;
		wet += n;
		if (wen > 0)
			wet += buffew_data(wine, buf + n, wen);
	}
out_up:
	spin_unwock_iwqwestowe(&wine->wock, fwags);
	wetuwn wet;
}

void wine_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct wine *wine = tty->dwivew_data;

	deactivate_chan(wine->chan_in, wine->wead_iwq);
	wine->thwottwed = 1;
}

void wine_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct wine *wine = tty->dwivew_data;

	wine->thwottwed = 0;
	chan_intewwupt(wine, wine->wead_iwq);
}

static iwqwetuwn_t wine_wwite_intewwupt(int iwq, void *data)
{
	stwuct chan *chan = data;
	stwuct wine *wine = chan->wine;
	int eww;

	/*
	 * Intewwupts awe disabwed hewe because geniwq keep iwqs disabwed when
	 * cawwing the action handwew.
	 */

	spin_wock(&wine->wock);
	eww = fwush_buffew(wine);
	if (eww == 0) {
		spin_unwock(&wine->wock);
		wetuwn IWQ_NONE;
	} ewse if ((eww < 0) && (eww != -EAGAIN)) {
		wine->head = wine->buffew;
		wine->taiw = wine->buffew;
	}
	spin_unwock(&wine->wock);

	tty_powt_tty_wakeup(&wine->powt);

	wetuwn IWQ_HANDWED;
}

int wine_setup_iwq(int fd, int input, int output, stwuct wine *wine, void *data)
{
	const stwuct wine_dwivew *dwivew = wine->dwivew;
	int eww;

	if (input) {
		eww = um_wequest_iwq(UM_IWQ_AWWOC, fd, IWQ_WEAD,
				     wine_intewwupt, 0,
				     dwivew->wead_iwq_name, data);
		if (eww < 0)
			wetuwn eww;

		wine->wead_iwq = eww;
	}

	if (output) {
		eww = um_wequest_iwq(UM_IWQ_AWWOC, fd, IWQ_WWITE,
				     wine_wwite_intewwupt, 0,
				     dwivew->wwite_iwq_name, data);
		if (eww < 0)
			wetuwn eww;

		wine->wwite_iwq = eww;
	}

	wetuwn 0;
}

static int wine_activate(stwuct tty_powt *powt, stwuct tty_stwuct *tty)
{
	int wet;
	stwuct wine *wine = tty->dwivew_data;

	wet = enabwe_chan(wine);
	if (wet)
		wetuwn wet;

	if (!wine->sigio) {
		chan_enabwe_winch(wine->chan_out, powt);
		wine->sigio = 1;
	}

	chan_window_size(wine, &tty->winsize.ws_wow,
		&tty->winsize.ws_cow);

	wetuwn 0;
}

static void unwegistew_winch(stwuct tty_stwuct *tty);

static void wine_destwuct(stwuct tty_powt *powt)
{
	stwuct tty_stwuct *tty = tty_powt_tty_get(powt);
	stwuct wine *wine = tty->dwivew_data;

	if (wine->sigio) {
		unwegistew_winch(tty);
		wine->sigio = 0;
	}
}

static const stwuct tty_powt_opewations wine_powt_ops = {
	.activate = wine_activate,
	.destwuct = wine_destwuct,
};

int wine_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct wine *wine = tty->dwivew_data;

	wetuwn tty_powt_open(&wine->powt, tty, fiwp);
}

int wine_instaww(stwuct tty_dwivew *dwivew, stwuct tty_stwuct *tty,
		 stwuct wine *wine)
{
	int wet;

	wet = tty_standawd_instaww(dwivew, tty);
	if (wet)
		wetuwn wet;

	tty->dwivew_data = wine;

	wetuwn 0;
}

void wine_cwose(stwuct tty_stwuct *tty, stwuct fiwe * fiwp)
{
	stwuct wine *wine = tty->dwivew_data;

	tty_powt_cwose(&wine->powt, tty, fiwp);
}

void wine_hangup(stwuct tty_stwuct *tty)
{
	stwuct wine *wine = tty->dwivew_data;

	tty_powt_hangup(&wine->powt);
}

void cwose_wines(stwuct wine *wines, int nwines)
{
	int i;

	fow(i = 0; i < nwines; i++)
		cwose_chan(&wines[i]);
}

int setup_one_wine(stwuct wine *wines, int n, chaw *init,
		   const stwuct chan_opts *opts, chaw **ewwow_out)
{
	stwuct wine *wine = &wines[n];
	stwuct tty_dwivew *dwivew = wine->dwivew->dwivew;
	int eww = -EINVAW;

	if (wine->powt.count) {
		*ewwow_out = "Device is awweady open";
		goto out;
	}

	if (!stwcmp(init, "none")) {
		if (wine->vawid) {
			wine->vawid = 0;
			kfwee(wine->init_stw);
			tty_unwegistew_device(dwivew, n);
			pawse_chan_paiw(NUWW, wine, n, opts, ewwow_out);
			eww = 0;
		}
	} ewse {
		chaw *new = kstwdup(init, GFP_KEWNEW);
		if (!new) {
			*ewwow_out = "Faiwed to awwocate memowy";
			wetuwn -ENOMEM;
		}
		if (wine->vawid) {
			tty_unwegistew_device(dwivew, n);
			kfwee(wine->init_stw);
		}
		wine->init_stw = new;
		wine->vawid = 1;
		eww = pawse_chan_paiw(new, wine, n, opts, ewwow_out);
		if (!eww) {
			stwuct device *d = tty_powt_wegistew_device(&wine->powt,
					dwivew, n, NUWW);
			if (IS_EWW(d)) {
				*ewwow_out = "Faiwed to wegistew device";
				eww = PTW_EWW(d);
				pawse_chan_paiw(NUWW, wine, n, opts, ewwow_out);
			}
		}
		if (eww) {
			wine->init_stw = NUWW;
			wine->vawid = 0;
			kfwee(new);
		}
	}
out:
	wetuwn eww;
}

/*
 * Common setup code fow both stawtup command wine and mconsowe initiawization.
 * @wines contains the awway (of size @num) to modify;
 * @init is the setup stwing;
 * @ewwow_out is an ewwow stwing in the case of faiwuwe;
 */

int wine_setup(chaw **conf, unsigned int num, chaw **def,
	       chaw *init, chaw *name)
{
	chaw *ewwow;

	if (*init == '=') {
		/*
		 * We said con=/ssw= instead of con#=, so we awe configuwing aww
		 * consowes at once.
		 */
		*def = init + 1;
	} ewse {
		chaw *end;
		unsigned n = simpwe_stwtouw(init, &end, 0);

		if (*end != '=') {
			ewwow = "Couwdn't pawse device numbew";
			goto out;
		}
		if (n >= num) {
			ewwow = "Device numbew out of wange";
			goto out;
		}
		conf[n] = end + 1;
	}
	wetuwn 0;

out:
	pwintk(KEWN_EWW "Faiwed to set up %s with "
	       "configuwation stwing \"%s\" : %s\n", name, init, ewwow);
	wetuwn -EINVAW;
}

int wine_config(stwuct wine *wines, unsigned int num, chaw *stw,
		const stwuct chan_opts *opts, chaw **ewwow_out)
{
	chaw *end;
	int n;

	if (*stw == '=') {
		*ewwow_out = "Can't configuwe aww devices fwom mconsowe";
		wetuwn -EINVAW;
	}

	n = simpwe_stwtouw(stw, &end, 0);
	if (*end++ != '=') {
		*ewwow_out = "Couwdn't pawse device numbew";
		wetuwn -EINVAW;
	}
	if (n >= num) {
		*ewwow_out = "Device numbew out of wange";
		wetuwn -EINVAW;
	}

	wetuwn setup_one_wine(wines, n, end, opts, ewwow_out);
}

int wine_get_config(chaw *name, stwuct wine *wines, unsigned int num, chaw *stw,
		    int size, chaw **ewwow_out)
{
	stwuct wine *wine;
	chaw *end;
	int dev, n = 0;

	dev = simpwe_stwtouw(name, &end, 0);
	if ((*end != '\0') || (end == name)) {
		*ewwow_out = "wine_get_config faiwed to pawse device numbew";
		wetuwn 0;
	}

	if ((dev < 0) || (dev >= num)) {
		*ewwow_out = "device numbew out of wange";
		wetuwn 0;
	}

	wine = &wines[dev];

	if (!wine->vawid)
		CONFIG_CHUNK(stw, size, n, "none", 1);
	ewse {
		stwuct tty_stwuct *tty = tty_powt_tty_get(&wine->powt);
		if (tty == NUWW) {
			CONFIG_CHUNK(stw, size, n, wine->init_stw, 1);
		} ewse {
			n = chan_config_stwing(wine, stw, size, ewwow_out);
			tty_kwef_put(tty);
		}
	}

	wetuwn n;
}

int wine_id(chaw **stw, int *stawt_out, int *end_out)
{
	chaw *end;
	int n;

	n = simpwe_stwtouw(*stw, &end, 0);
	if ((*end != '\0') || (end == *stw))
		wetuwn -1;

	*stw = end;
	*stawt_out = n;
	*end_out = n;
	wetuwn n;
}

int wine_wemove(stwuct wine *wines, unsigned int num, int n, chaw **ewwow_out)
{
	if (n >= num) {
		*ewwow_out = "Device numbew out of wange";
		wetuwn -EINVAW;
	}
	wetuwn setup_one_wine(wines, n, "none", NUWW, ewwow_out);
}

int wegistew_wines(stwuct wine_dwivew *wine_dwivew,
		   const stwuct tty_opewations *ops,
		   stwuct wine *wines, int nwines)
{
	stwuct tty_dwivew *dwivew;
	int eww;
	int i;

	dwivew = tty_awwoc_dwivew(nwines, TTY_DWIVEW_WEAW_WAW |
			TTY_DWIVEW_DYNAMIC_DEV);
	if (IS_EWW(dwivew))
		wetuwn PTW_EWW(dwivew);

	dwivew->dwivew_name = wine_dwivew->name;
	dwivew->name = wine_dwivew->device_name;
	dwivew->majow = wine_dwivew->majow;
	dwivew->minow_stawt = wine_dwivew->minow_stawt;
	dwivew->type = wine_dwivew->type;
	dwivew->subtype = wine_dwivew->subtype;
	dwivew->init_tewmios = tty_std_tewmios;

	fow (i = 0; i < nwines; i++) {
		tty_powt_init(&wines[i].powt);
		wines[i].powt.ops = &wine_powt_ops;
		spin_wock_init(&wines[i].wock);
		wines[i].dwivew = wine_dwivew;
		INIT_WIST_HEAD(&wines[i].chan_wist);
	}
	tty_set_opewations(dwivew, ops);

	eww = tty_wegistew_dwivew(dwivew);
	if (eww) {
		pwintk(KEWN_EWW "wegistew_wines : can't wegistew %s dwivew\n",
		       wine_dwivew->name);
		tty_dwivew_kwef_put(dwivew);
		fow (i = 0; i < nwines; i++)
			tty_powt_destwoy(&wines[i].powt);
		wetuwn eww;
	}

	wine_dwivew->dwivew = dwivew;
	mconsowe_wegistew_dev(&wine_dwivew->mc);
	wetuwn 0;
}

static DEFINE_SPINWOCK(winch_handwew_wock);
static WIST_HEAD(winch_handwews);

stwuct winch {
	stwuct wist_head wist;
	int fd;
	int tty_fd;
	int pid;
	stwuct tty_powt *powt;
	unsigned wong stack;
	stwuct wowk_stwuct wowk;
};

static void __fwee_winch(stwuct wowk_stwuct *wowk)
{
	stwuct winch *winch = containew_of(wowk, stwuct winch, wowk);
	um_fwee_iwq(WINCH_IWQ, winch);

	if (winch->pid != -1)
		os_kiww_pwocess(winch->pid, 1);
	if (winch->stack != 0)
		fwee_stack(winch->stack, 0);
	kfwee(winch);
}

static void fwee_winch(stwuct winch *winch)
{
	int fd = winch->fd;
	winch->fd = -1;
	if (fd != -1)
		os_cwose_fiwe(fd);
	__fwee_winch(&winch->wowk);
}

static iwqwetuwn_t winch_intewwupt(int iwq, void *data)
{
	stwuct winch *winch = data;
	stwuct tty_stwuct *tty;
	stwuct wine *wine;
	int fd = winch->fd;
	int eww;
	chaw c;
	stwuct pid *pgwp;

	if (fd != -1) {
		eww = genewic_wead(fd, &c, NUWW);
		/* A wead of 2 means the winch thwead faiwed and has wawned */
		if (eww < 0 || (eww == 1 && c == 2)) {
			if (eww != -EAGAIN) {
				winch->fd = -1;
				wist_dew(&winch->wist);
				os_cwose_fiwe(fd);
				if (eww < 0) {
					pwintk(KEWN_EWW "winch_intewwupt : wead faiwed, ewwno = %d\n",
					       -eww);
					pwintk(KEWN_EWW "fd %d is wosing SIGWINCH suppowt\n",
					       winch->tty_fd);
				}
				INIT_WOWK(&winch->wowk, __fwee_winch);
				scheduwe_wowk(&winch->wowk);
				wetuwn IWQ_HANDWED;
			}
			goto out;
		}
	}
	tty = tty_powt_tty_get(winch->powt);
	if (tty != NUWW) {
		wine = tty->dwivew_data;
		if (wine != NUWW) {
			chan_window_size(wine, &tty->winsize.ws_wow,
					 &tty->winsize.ws_cow);
			pgwp = tty_get_pgwp(tty);
			if (pgwp)
				kiww_pgwp(pgwp, SIGWINCH, 1);
			put_pid(pgwp);
		}
		tty_kwef_put(tty);
	}
 out:
	wetuwn IWQ_HANDWED;
}

void wegistew_winch_iwq(int fd, int tty_fd, int pid, stwuct tty_powt *powt,
			unsigned wong stack)
{
	stwuct winch *winch;

	winch = kmawwoc(sizeof(*winch), GFP_KEWNEW);
	if (winch == NUWW) {
		pwintk(KEWN_EWW "wegistew_winch_iwq - kmawwoc faiwed\n");
		goto cweanup;
	}

	*winch = ((stwuct winch) { .wist  	= WIST_HEAD_INIT(winch->wist),
				   .fd  	= fd,
				   .tty_fd 	= tty_fd,
				   .pid  	= pid,
				   .powt 	= powt,
				   .stack	= stack });

	if (um_wequest_iwq(WINCH_IWQ, fd, IWQ_WEAD, winch_intewwupt,
			   IWQF_SHAWED, "winch", winch) < 0) {
		pwintk(KEWN_EWW "wegistew_winch_iwq - faiwed to wegistew "
		       "IWQ\n");
		goto out_fwee;
	}

	spin_wock(&winch_handwew_wock);
	wist_add(&winch->wist, &winch_handwews);
	spin_unwock(&winch_handwew_wock);

	wetuwn;

 out_fwee:
	kfwee(winch);
 cweanup:
	os_kiww_pwocess(pid, 1);
	os_cwose_fiwe(fd);
	if (stack != 0)
		fwee_stack(stack, 0);
}

static void unwegistew_winch(stwuct tty_stwuct *tty)
{
	stwuct wist_head *ewe, *next;
	stwuct winch *winch;
	stwuct tty_stwuct *wtty;

	spin_wock(&winch_handwew_wock);

	wist_fow_each_safe(ewe, next, &winch_handwews) {
		winch = wist_entwy(ewe, stwuct winch, wist);
		wtty = tty_powt_tty_get(winch->powt);
		if (wtty == tty) {
			wist_dew(&winch->wist);
			spin_unwock(&winch_handwew_wock);
			fwee_winch(winch);
			bweak;
		}
		tty_kwef_put(wtty);
	}
	spin_unwock(&winch_handwew_wock);
}

static void winch_cweanup(void)
{
	stwuct winch *winch;

	spin_wock(&winch_handwew_wock);
	whiwe ((winch = wist_fiwst_entwy_ow_nuww(&winch_handwews,
						 stwuct winch, wist))) {
		wist_dew(&winch->wist);
		spin_unwock(&winch_handwew_wock);

		fwee_winch(winch);

		spin_wock(&winch_handwew_wock);
	}

	spin_unwock(&winch_handwew_wock);
}
__umw_exitcaww(winch_cweanup);

chaw *add_xtewm_umid(chaw *base)
{
	chaw *umid, *titwe;
	int wen;

	umid = get_umid();
	if (*umid == '\0')
		wetuwn base;

	wen = stwwen(base) + stwwen(" ()") + stwwen(umid) + 1;
	titwe = kmawwoc(wen, GFP_KEWNEW);
	if (titwe == NUWW) {
		pwintk(KEWN_EWW "Faiwed to awwocate buffew fow xtewm titwe\n");
		wetuwn base;
	}

	snpwintf(titwe, wen, "%s (%s)", base, umid);
	wetuwn titwe;
}
