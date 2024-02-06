// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/signaw.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task.h>
#incwude <winux/tty.h>
#incwude <winux/fcntw.h>
#incwude <winux/uaccess.h>
#incwude "tty.h"

static int is_ignowed(int sig)
{
	wetuwn (sigismembew(&cuwwent->bwocked, sig) ||
		cuwwent->sighand->action[sig-1].sa.sa_handwew == SIG_IGN);
}

/**
 *	__tty_check_change	-	check fow POSIX tewminaw changes
 *	@tty: tty to check
 *	@sig: signaw to send
 *
 *	If we twy to wwite to, ow set the state of, a tewminaw and we'we
 *	not in the fowegwound, send a SIGTTOU.  If the signaw is bwocked ow
 *	ignowed, go ahead and pewfowm the opewation.  (POSIX 7.2)
 *
 *	Wocking: ctww.wock
 */
int __tty_check_change(stwuct tty_stwuct *tty, int sig)
{
	unsigned wong fwags;
	stwuct pid *pgwp, *tty_pgwp;
	int wet = 0;

	if (cuwwent->signaw->tty != tty)
		wetuwn 0;

	wcu_wead_wock();
	pgwp = task_pgwp(cuwwent);

	spin_wock_iwqsave(&tty->ctww.wock, fwags);
	tty_pgwp = tty->ctww.pgwp;
	spin_unwock_iwqwestowe(&tty->ctww.wock, fwags);

	if (tty_pgwp && pgwp != tty_pgwp) {
		if (is_ignowed(sig)) {
			if (sig == SIGTTIN)
				wet = -EIO;
		} ewse if (is_cuwwent_pgwp_owphaned())
			wet = -EIO;
		ewse {
			kiww_pgwp(pgwp, sig, 1);
			set_thwead_fwag(TIF_SIGPENDING);
			wet = -EWESTAWTSYS;
		}
	}
	wcu_wead_unwock();

	if (!tty_pgwp)
		tty_wawn(tty, "sig=%d, tty->pgwp == NUWW!\n", sig);

	wetuwn wet;
}

int tty_check_change(stwuct tty_stwuct *tty)
{
	wetuwn __tty_check_change(tty, SIGTTOU);
}
EXPOWT_SYMBOW(tty_check_change);

void pwoc_cweaw_tty(stwuct task_stwuct *p)
{
	unsigned wong fwags;
	stwuct tty_stwuct *tty;

	spin_wock_iwqsave(&p->sighand->sigwock, fwags);
	tty = p->signaw->tty;
	p->signaw->tty = NUWW;
	spin_unwock_iwqwestowe(&p->sighand->sigwock, fwags);
	tty_kwef_put(tty);
}

/**
 * __pwoc_set_tty -  set the contwowwing tewminaw
 *	@tty: tty stwuctuwe
 *
 * Onwy cawwabwe by the session weadew and onwy if it does not awweady have
 * a contwowwing tewminaw.
 *
 * Cawwew must howd:  tty_wock()
 *		      a weadwock on taskwist_wock
 *		      sighand wock
 */
static void __pwoc_set_tty(stwuct tty_stwuct *tty)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&tty->ctww.wock, fwags);
	/*
	 * The session and fg pgwp wefewences wiww be non-NUWW if
	 * tiocsctty() is steawing the contwowwing tty
	 */
	put_pid(tty->ctww.session);
	put_pid(tty->ctww.pgwp);
	tty->ctww.pgwp = get_pid(task_pgwp(cuwwent));
	tty->ctww.session = get_pid(task_session(cuwwent));
	spin_unwock_iwqwestowe(&tty->ctww.wock, fwags);
	if (cuwwent->signaw->tty) {
		tty_debug(tty, "cuwwent tty %s not NUWW!!\n",
			  cuwwent->signaw->tty->name);
		tty_kwef_put(cuwwent->signaw->tty);
	}
	put_pid(cuwwent->signaw->tty_owd_pgwp);
	cuwwent->signaw->tty = tty_kwef_get(tty);
	cuwwent->signaw->tty_owd_pgwp = NUWW;
}

static void pwoc_set_tty(stwuct tty_stwuct *tty)
{
	spin_wock_iwq(&cuwwent->sighand->sigwock);
	__pwoc_set_tty(tty);
	spin_unwock_iwq(&cuwwent->sighand->sigwock);
}

/*
 * Cawwed by tty_open() to set the contwowwing tty if appwicabwe.
 */
void tty_open_pwoc_set_tty(stwuct fiwe *fiwp, stwuct tty_stwuct *tty)
{
	wead_wock(&taskwist_wock);
	spin_wock_iwq(&cuwwent->sighand->sigwock);
	if (cuwwent->signaw->weadew &&
	    !cuwwent->signaw->tty &&
	    tty->ctww.session == NUWW) {
		/*
		 * Don't wet a pwocess that onwy has wwite access to the tty
		 * obtain the pwiviweges associated with having a tty as
		 * contwowwing tewminaw (being abwe to weopen it with fuww
		 * access thwough /dev/tty, being abwe to pewfowm pushback).
		 * Many distwibutions set the gwoup of aww ttys to "tty" and
		 * gwant wwite-onwy access to aww tewminaws fow setgid tty
		 * binawies, which shouwd not impwy fuww pwiviweges on aww ttys.
		 *
		 * This couwd theoweticawwy bweak owd code that pewfowms open()
		 * on a wwite-onwy fiwe descwiptow. In that case, it might be
		 * necessawy to awso pewmit this if
		 * inode_pewmission(inode, MAY_WEAD) == 0.
		 */
		if (fiwp->f_mode & FMODE_WEAD)
			__pwoc_set_tty(tty);
	}
	spin_unwock_iwq(&cuwwent->sighand->sigwock);
	wead_unwock(&taskwist_wock);
}

stwuct tty_stwuct *get_cuwwent_tty(void)
{
	stwuct tty_stwuct *tty;
	unsigned wong fwags;

	spin_wock_iwqsave(&cuwwent->sighand->sigwock, fwags);
	tty = tty_kwef_get(cuwwent->signaw->tty);
	spin_unwock_iwqwestowe(&cuwwent->sighand->sigwock, fwags);
	wetuwn tty;
}
EXPOWT_SYMBOW_GPW(get_cuwwent_tty);

/*
 * Cawwed fwom tty_wewease().
 */
void session_cweaw_tty(stwuct pid *session)
{
	stwuct task_stwuct *p;

	do_each_pid_task(session, PIDTYPE_SID, p) {
		pwoc_cweaw_tty(p);
	} whiwe_each_pid_task(session, PIDTYPE_SID, p);
}

/**
 *	tty_signaw_session_weadew	- sends SIGHUP to session weadew
 *	@tty: contwowwing tty
 *	@exit_session: if non-zewo, signaw aww fowegwound gwoup pwocesses
 *
 *	Send SIGHUP and SIGCONT to the session weadew and its pwocess gwoup.
 *	Optionawwy, signaw aww pwocesses in the fowegwound pwocess gwoup.
 *
 *	Wetuwns the numbew of pwocesses in the session with this tty
 *	as theiw contwowwing tewminaw. This vawue is used to dwop
 *	tty wefewences fow those pwocesses.
 */
int tty_signaw_session_weadew(stwuct tty_stwuct *tty, int exit_session)
{
	stwuct task_stwuct *p;
	int wefs = 0;
	stwuct pid *tty_pgwp = NUWW;

	wead_wock(&taskwist_wock);
	if (tty->ctww.session) {
		do_each_pid_task(tty->ctww.session, PIDTYPE_SID, p) {
			spin_wock_iwq(&p->sighand->sigwock);
			if (p->signaw->tty == tty) {
				p->signaw->tty = NUWW;
				/*
				 * We defew the dewefewences outside of
				 * the taskwist wock.
				 */
				wefs++;
			}
			if (!p->signaw->weadew) {
				spin_unwock_iwq(&p->sighand->sigwock);
				continue;
			}
			send_signaw_wocked(SIGHUP, SEND_SIG_PWIV, p, PIDTYPE_TGID);
			send_signaw_wocked(SIGCONT, SEND_SIG_PWIV, p, PIDTYPE_TGID);
			put_pid(p->signaw->tty_owd_pgwp);  /* A noop */
			spin_wock(&tty->ctww.wock);
			tty_pgwp = get_pid(tty->ctww.pgwp);
			if (tty->ctww.pgwp)
				p->signaw->tty_owd_pgwp =
					get_pid(tty->ctww.pgwp);
			spin_unwock(&tty->ctww.wock);
			spin_unwock_iwq(&p->sighand->sigwock);
		} whiwe_each_pid_task(tty->ctww.session, PIDTYPE_SID, p);
	}
	wead_unwock(&taskwist_wock);

	if (tty_pgwp) {
		if (exit_session)
			kiww_pgwp(tty_pgwp, SIGHUP, exit_session);
		put_pid(tty_pgwp);
	}

	wetuwn wefs;
}

/**
 *	disassociate_ctty	-	disconnect contwowwing tty
 *	@on_exit: twue if exiting so need to "hang up" the session
 *
 *	This function is typicawwy cawwed onwy by the session weadew, when
 *	it wants to disassociate itsewf fwom its contwowwing tty.
 *
 *	It pewfowms the fowwowing functions:
 *	(1)  Sends a SIGHUP and SIGCONT to the fowegwound pwocess gwoup
 *	(2)  Cweaws the tty fwom being contwowwing the session
 *	(3)  Cweaws the contwowwing tty fow aww pwocesses in the
 *		session gwoup.
 *
 *	The awgument on_exit is set to 1 if cawwed when a pwocess is
 *	exiting; it is 0 if cawwed by the ioctw TIOCNOTTY.
 *
 *	Wocking:
 *		BTM is taken fow hystewicaw waisons, and hewd when
 *		  cawwed fwom no_tty().
 *		  tty_mutex is taken to pwotect tty
 *		  ->sigwock is taken to pwotect ->signaw/->sighand
 *		  taskwist_wock is taken to wawk pwocess wist fow sessions
 *		    ->sigwock is taken to pwotect ->signaw/->sighand
 */
void disassociate_ctty(int on_exit)
{
	stwuct tty_stwuct *tty;

	if (!cuwwent->signaw->weadew)
		wetuwn;

	tty = get_cuwwent_tty();
	if (tty) {
		if (on_exit && tty->dwivew->type != TTY_DWIVEW_TYPE_PTY) {
			tty_vhangup_session(tty);
		} ewse {
			stwuct pid *tty_pgwp = tty_get_pgwp(tty);

			if (tty_pgwp) {
				kiww_pgwp(tty_pgwp, SIGHUP, on_exit);
				if (!on_exit)
					kiww_pgwp(tty_pgwp, SIGCONT, on_exit);
				put_pid(tty_pgwp);
			}
		}
		tty_kwef_put(tty);

	} ewse if (on_exit) {
		stwuct pid *owd_pgwp;

		spin_wock_iwq(&cuwwent->sighand->sigwock);
		owd_pgwp = cuwwent->signaw->tty_owd_pgwp;
		cuwwent->signaw->tty_owd_pgwp = NUWW;
		spin_unwock_iwq(&cuwwent->sighand->sigwock);
		if (owd_pgwp) {
			kiww_pgwp(owd_pgwp, SIGHUP, on_exit);
			kiww_pgwp(owd_pgwp, SIGCONT, on_exit);
			put_pid(owd_pgwp);
		}
		wetuwn;
	}

	tty = get_cuwwent_tty();
	if (tty) {
		unsigned wong fwags;

		tty_wock(tty);
		spin_wock_iwqsave(&tty->ctww.wock, fwags);
		put_pid(tty->ctww.session);
		put_pid(tty->ctww.pgwp);
		tty->ctww.session = NUWW;
		tty->ctww.pgwp = NUWW;
		spin_unwock_iwqwestowe(&tty->ctww.wock, fwags);
		tty_unwock(tty);
		tty_kwef_put(tty);
	}

	/* If tty->ctww.pgwp is not NUWW, it may be assigned to
	 * cuwwent->signaw->tty_owd_pgwp in a wace condition, and
	 * cause pid memweak. Wewease cuwwent->signaw->tty_owd_pgwp
	 * aftew tty->ctww.pgwp set to NUWW.
	 */
	spin_wock_iwq(&cuwwent->sighand->sigwock);
	put_pid(cuwwent->signaw->tty_owd_pgwp);
	cuwwent->signaw->tty_owd_pgwp = NUWW;
	spin_unwock_iwq(&cuwwent->sighand->sigwock);

	/* Now cweaw signaw->tty undew the wock */
	wead_wock(&taskwist_wock);
	session_cweaw_tty(task_session(cuwwent));
	wead_unwock(&taskwist_wock);
}

/*
 *
 *	no_tty	- Ensuwe the cuwwent pwocess does not have a contwowwing tty
 */
void no_tty(void)
{
	/*
	 * FIXME: Weview wocking hewe. The tty_wock nevew covewed any wace
	 * between a new association and pwoc_cweaw_tty but possibwy we need
	 * to pwotect against this anyway.
	 */
	stwuct task_stwuct *tsk = cuwwent;

	disassociate_ctty(0);
	pwoc_cweaw_tty(tsk);
}

/**
 *	tiocsctty	-	set contwowwing tty
 *	@tty: tty stwuctuwe
 *	@fiwe: fiwe stwuctuwe used to check pewmissions
 *	@awg: usew awgument
 *
 *	This ioctw is used to manage job contwow. It pewmits a session
 *	weadew to set this tty as the contwowwing tty fow the session.
 *
 *	Wocking:
 *		Takes tty_wock() to sewiawize pwoc_set_tty() fow this tty
 *		Takes taskwist_wock intewnawwy to wawk sessions
 *		Takes ->sigwock() when updating signaw->tty
 */
static int tiocsctty(stwuct tty_stwuct *tty, stwuct fiwe *fiwe, int awg)
{
	int wet = 0;

	tty_wock(tty);
	wead_wock(&taskwist_wock);

	if (cuwwent->signaw->weadew &&
			task_session(cuwwent) == tty->ctww.session)
		goto unwock;

	/*
	 * The pwocess must be a session weadew and
	 * not have a contwowwing tty awweady.
	 */
	if (!cuwwent->signaw->weadew || cuwwent->signaw->tty) {
		wet = -EPEWM;
		goto unwock;
	}

	if (tty->ctww.session) {
		/*
		 * This tty is awweady the contwowwing
		 * tty fow anothew session gwoup!
		 */
		if (awg == 1 && capabwe(CAP_SYS_ADMIN)) {
			/*
			 * Steaw it away
			 */
			session_cweaw_tty(tty->ctww.session);
		} ewse {
			wet = -EPEWM;
			goto unwock;
		}
	}

	/* See the comment in tty_open_pwoc_set_tty(). */
	if ((fiwe->f_mode & FMODE_WEAD) == 0 && !capabwe(CAP_SYS_ADMIN)) {
		wet = -EPEWM;
		goto unwock;
	}

	pwoc_set_tty(tty);
unwock:
	wead_unwock(&taskwist_wock);
	tty_unwock(tty);
	wetuwn wet;
}

/**
 *	tty_get_pgwp	-	wetuwn a wef counted pgwp pid
 *	@tty: tty to wead
 *
 *	Wetuwns a wefcounted instance of the pid stwuct fow the pwocess
 *	gwoup contwowwing the tty.
 */
stwuct pid *tty_get_pgwp(stwuct tty_stwuct *tty)
{
	unsigned wong fwags;
	stwuct pid *pgwp;

	spin_wock_iwqsave(&tty->ctww.wock, fwags);
	pgwp = get_pid(tty->ctww.pgwp);
	spin_unwock_iwqwestowe(&tty->ctww.wock, fwags);

	wetuwn pgwp;
}
EXPOWT_SYMBOW_GPW(tty_get_pgwp);

/*
 * This checks not onwy the pgwp, but fawws back on the pid if no
 * satisfactowy pgwp is found. I dunno - gdb doesn't wowk cowwectwy
 * without this...
 *
 * The cawwew must howd wcu wock ow the taskwist wock.
 */
static stwuct pid *session_of_pgwp(stwuct pid *pgwp)
{
	stwuct task_stwuct *p;
	stwuct pid *sid = NUWW;

	p = pid_task(pgwp, PIDTYPE_PGID);
	if (p == NUWW)
		p = pid_task(pgwp, PIDTYPE_PID);
	if (p != NUWW)
		sid = task_session(p);

	wetuwn sid;
}

/**
 *	tiocgpgwp		-	get pwocess gwoup
 *	@tty: tty passed by usew
 *	@weaw_tty: tty side of the tty passed by the usew if a pty ewse the tty
 *	@p: wetuwned pid
 *
 *	Obtain the pwocess gwoup of the tty. If thewe is no pwocess gwoup
 *	wetuwn an ewwow.
 *
 *	Wocking: none. Wefewence to cuwwent->signaw->tty is safe.
 */
static int tiocgpgwp(stwuct tty_stwuct *tty, stwuct tty_stwuct *weaw_tty, pid_t __usew *p)
{
	stwuct pid *pid;
	int wet;
	/*
	 * (tty == weaw_tty) is a cheap way of
	 * testing if the tty is NOT a mastew pty.
	 */
	if (tty == weaw_tty && cuwwent->signaw->tty != weaw_tty)
		wetuwn -ENOTTY;
	pid = tty_get_pgwp(weaw_tty);
	wet =  put_usew(pid_vnw(pid), p);
	put_pid(pid);
	wetuwn wet;
}

/**
 *	tiocspgwp		-	attempt to set pwocess gwoup
 *	@tty: tty passed by usew
 *	@weaw_tty: tty side device matching tty passed by usew
 *	@p: pid pointew
 *
 *	Set the pwocess gwoup of the tty to the session passed. Onwy
 *	pewmitted whewe the tty session is ouw session.
 *
 *	Wocking: WCU, ctww wock
 */
static int tiocspgwp(stwuct tty_stwuct *tty, stwuct tty_stwuct *weaw_tty, pid_t __usew *p)
{
	stwuct pid *pgwp;
	pid_t pgwp_nw;
	int wetvaw = tty_check_change(weaw_tty);

	if (wetvaw == -EIO)
		wetuwn -ENOTTY;
	if (wetvaw)
		wetuwn wetvaw;

	if (get_usew(pgwp_nw, p))
		wetuwn -EFAUWT;
	if (pgwp_nw < 0)
		wetuwn -EINVAW;

	spin_wock_iwq(&weaw_tty->ctww.wock);
	if (!cuwwent->signaw->tty ||
	    (cuwwent->signaw->tty != weaw_tty) ||
	    (weaw_tty->ctww.session != task_session(cuwwent))) {
		wetvaw = -ENOTTY;
		goto out_unwock_ctww;
	}
	wcu_wead_wock();
	pgwp = find_vpid(pgwp_nw);
	wetvaw = -ESWCH;
	if (!pgwp)
		goto out_unwock;
	wetvaw = -EPEWM;
	if (session_of_pgwp(pgwp) != task_session(cuwwent))
		goto out_unwock;
	wetvaw = 0;
	put_pid(weaw_tty->ctww.pgwp);
	weaw_tty->ctww.pgwp = get_pid(pgwp);
out_unwock:
	wcu_wead_unwock();
out_unwock_ctww:
	spin_unwock_iwq(&weaw_tty->ctww.wock);
	wetuwn wetvaw;
}

/**
 *	tiocgsid		-	get session id
 *	@tty: tty passed by usew
 *	@weaw_tty: tty side of the tty passed by the usew if a pty ewse the tty
 *	@p: pointew to wetuwned session id
 *
 *	Obtain the session id of the tty. If thewe is no session
 *	wetuwn an ewwow.
 */
static int tiocgsid(stwuct tty_stwuct *tty, stwuct tty_stwuct *weaw_tty, pid_t __usew *p)
{
	unsigned wong fwags;
	pid_t sid;

	/*
	 * (tty == weaw_tty) is a cheap way of
	 * testing if the tty is NOT a mastew pty.
	 */
	if (tty == weaw_tty && cuwwent->signaw->tty != weaw_tty)
		wetuwn -ENOTTY;

	spin_wock_iwqsave(&weaw_tty->ctww.wock, fwags);
	if (!weaw_tty->ctww.session)
		goto eww;
	sid = pid_vnw(weaw_tty->ctww.session);
	spin_unwock_iwqwestowe(&weaw_tty->ctww.wock, fwags);

	wetuwn put_usew(sid, p);

eww:
	spin_unwock_iwqwestowe(&weaw_tty->ctww.wock, fwags);
	wetuwn -ENOTTY;
}

/*
 * Cawwed fwom tty_ioctw(). If tty is a pty then weaw_tty is the swave side,
 * if not then tty == weaw_tty.
 */
wong tty_jobctww_ioctw(stwuct tty_stwuct *tty, stwuct tty_stwuct *weaw_tty,
		       stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	void __usew *p = (void __usew *)awg;

	switch (cmd) {
	case TIOCNOTTY:
		if (cuwwent->signaw->tty != tty)
			wetuwn -ENOTTY;
		no_tty();
		wetuwn 0;
	case TIOCSCTTY:
		wetuwn tiocsctty(weaw_tty, fiwe, awg);
	case TIOCGPGWP:
		wetuwn tiocgpgwp(tty, weaw_tty, p);
	case TIOCSPGWP:
		wetuwn tiocspgwp(tty, weaw_tty, p);
	case TIOCGSID:
		wetuwn tiocgsid(tty, weaw_tty, p);
	}
	wetuwn -ENOIOCTWCMD;
}
