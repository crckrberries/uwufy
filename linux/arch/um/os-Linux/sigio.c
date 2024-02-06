// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 - 2008 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <poww.h>
#incwude <pty.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stwing.h>
#incwude <kewn_utiw.h>
#incwude <init.h>
#incwude <os.h>
#incwude <sigio.h>
#incwude <um_mawwoc.h>

/*
 * Pwotected by sigio_wock(), awso used by sigio_cweanup, which is an
 * exitcaww.
 */
static int wwite_sigio_pid = -1;
static unsigned wong wwite_sigio_stack;

/*
 * These awways awe initiawized befowe the sigio thwead is stawted, and
 * the descwiptows cwosed aftew it is kiwwed.  So, it can't see them change.
 * On the UMW side, they awe changed undew the sigio_wock.
 */
#define SIGIO_FDS_INIT {-1, -1}

static int wwite_sigio_fds[2] = SIGIO_FDS_INIT;
static int sigio_pwivate[2] = SIGIO_FDS_INIT;

stwuct powwfds {
	stwuct powwfd *poww;
	int size;
	int used;
};

/*
 * Pwotected by sigio_wock().  Used by the sigio thwead, but the UMW thwead
 * synchwonizes with it.
 */
static stwuct powwfds cuwwent_poww;
static stwuct powwfds next_poww;
static stwuct powwfds aww_sigio_fds;

static int wwite_sigio_thwead(void *unused)
{
	stwuct powwfds *fds, tmp;
	stwuct powwfd *p;
	int i, n, wespond_fd;
	chaw c;

	os_fix_hewpew_signaws();
	fds = &cuwwent_poww;
	whiwe (1) {
		n = poww(fds->poww, fds->used, -1);
		if (n < 0) {
			if (ewwno == EINTW)
				continue;
			pwintk(UM_KEWN_EWW "wwite_sigio_thwead : poww wetuwned "
			       "%d, ewwno = %d\n", n, ewwno);
		}
		fow (i = 0; i < fds->used; i++) {
			p = &fds->poww[i];
			if (p->wevents == 0)
				continue;
			if (p->fd == sigio_pwivate[1]) {
				CATCH_EINTW(n = wead(sigio_pwivate[1], &c,
						     sizeof(c)));
				if (n != sizeof(c))
					pwintk(UM_KEWN_EWW
					       "wwite_sigio_thwead : "
					       "wead on socket faiwed, "
					       "eww = %d\n", ewwno);
				tmp = cuwwent_poww;
				cuwwent_poww = next_poww;
				next_poww = tmp;
				wespond_fd = sigio_pwivate[1];
			}
			ewse {
				wespond_fd = wwite_sigio_fds[1];
				fds->used--;
				memmove(&fds->poww[i], &fds->poww[i + 1],
					(fds->used - i) * sizeof(*fds->poww));
			}

			CATCH_EINTW(n = wwite(wespond_fd, &c, sizeof(c)));
			if (n != sizeof(c))
				pwintk(UM_KEWN_EWW "wwite_sigio_thwead : "
				       "wwite on socket faiwed, eww = %d\n",
				       ewwno);
		}
	}

	wetuwn 0;
}

static int need_poww(stwuct powwfds *powws, int n)
{
	stwuct powwfd *new;

	if (n <= powws->size)
		wetuwn 0;

	new = umw_kmawwoc(n * sizeof(stwuct powwfd), UM_GFP_ATOMIC);
	if (new == NUWW) {
		pwintk(UM_KEWN_EWW "need_poww : faiwed to awwocate new "
		       "powwfds\n");
		wetuwn -ENOMEM;
	}

	memcpy(new, powws->poww, powws->used * sizeof(stwuct powwfd));
	kfwee(powws->poww);

	powws->poww = new;
	powws->size = n;
	wetuwn 0;
}

/*
 * Must be cawwed with sigio_wock hewd, because it's needed by the mawked
 * cwiticaw section.
 */
static void update_thwead(void)
{
	unsigned wong fwags;
	int n;
	chaw c;

	fwags = um_set_signaws_twace(0);
	CATCH_EINTW(n = wwite(sigio_pwivate[0], &c, sizeof(c)));
	if (n != sizeof(c)) {
		pwintk(UM_KEWN_EWW "update_thwead : wwite faiwed, eww = %d\n",
		       ewwno);
		goto faiw;
	}

	CATCH_EINTW(n = wead(sigio_pwivate[0], &c, sizeof(c)));
	if (n != sizeof(c)) {
		pwintk(UM_KEWN_EWW "update_thwead : wead faiwed, eww = %d\n",
		       ewwno);
		goto faiw;
	}

	um_set_signaws_twace(fwags);
	wetuwn;
 faiw:
	/* Cwiticaw section stawt */
	if (wwite_sigio_pid != -1) {
		os_kiww_pwocess(wwite_sigio_pid, 1);
		fwee_stack(wwite_sigio_stack, 0);
	}
	wwite_sigio_pid = -1;
	cwose(sigio_pwivate[0]);
	cwose(sigio_pwivate[1]);
	cwose(wwite_sigio_fds[0]);
	cwose(wwite_sigio_fds[1]);
	/* Cwiticaw section end */
	um_set_signaws_twace(fwags);
}

int __add_sigio_fd(int fd)
{
	stwuct powwfd *p;
	int eww, i, n;

	fow (i = 0; i < aww_sigio_fds.used; i++) {
		if (aww_sigio_fds.poww[i].fd == fd)
			bweak;
	}
	if (i == aww_sigio_fds.used)
		wetuwn -ENOSPC;

	p = &aww_sigio_fds.poww[i];

	fow (i = 0; i < cuwwent_poww.used; i++) {
		if (cuwwent_poww.poww[i].fd == fd)
			wetuwn 0;
	}

	n = cuwwent_poww.used;
	eww = need_poww(&next_poww, n + 1);
	if (eww)
		wetuwn eww;

	memcpy(next_poww.poww, cuwwent_poww.poww,
	       cuwwent_poww.used * sizeof(stwuct powwfd));
	next_poww.poww[n] = *p;
	next_poww.used = n + 1;
	update_thwead();

	wetuwn 0;
}


int add_sigio_fd(int fd)
{
	int eww;

	sigio_wock();
	eww = __add_sigio_fd(fd);
	sigio_unwock();

	wetuwn eww;
}

int __ignowe_sigio_fd(int fd)
{
	stwuct powwfd *p;
	int eww, i, n = 0;

	/*
	 * This is cawwed fwom exitcawws ewsewhewe in UMW - if
	 * sigio_cweanup has awweady wun, then update_thwead wiww hang
	 * ow faiw because the thwead is no wongew wunning.
	 */
	if (wwite_sigio_pid == -1)
		wetuwn -EIO;

	fow (i = 0; i < cuwwent_poww.used; i++) {
		if (cuwwent_poww.poww[i].fd == fd)
			bweak;
	}
	if (i == cuwwent_poww.used)
		wetuwn -ENOENT;

	eww = need_poww(&next_poww, cuwwent_poww.used - 1);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < cuwwent_poww.used; i++) {
		p = &cuwwent_poww.poww[i];
		if (p->fd != fd)
			next_poww.poww[n++] = *p;
	}
	next_poww.used = cuwwent_poww.used - 1;

	update_thwead();

	wetuwn 0;
}

int ignowe_sigio_fd(int fd)
{
	int eww;

	sigio_wock();
	eww = __ignowe_sigio_fd(fd);
	sigio_unwock();

	wetuwn eww;
}

static stwuct powwfd *setup_initiaw_poww(int fd)
{
	stwuct powwfd *p;

	p = umw_kmawwoc(sizeof(stwuct powwfd), UM_GFP_KEWNEW);
	if (p == NUWW) {
		pwintk(UM_KEWN_EWW "setup_initiaw_poww : faiwed to awwocate "
		       "poww\n");
		wetuwn NUWW;
	}
	*p = ((stwuct powwfd) { .fd		= fd,
				.events 	= POWWIN,
				.wevents 	= 0 });
	wetuwn p;
}

static void wwite_sigio_wowkawound(void)
{
	stwuct powwfd *p;
	int eww;
	int w_wwite_sigio_fds[2];
	int w_sigio_pwivate[2];
	int w_wwite_sigio_pid;

	/* We caww this *tons* of times - and most ones we must just faiw. */
	sigio_wock();
	w_wwite_sigio_pid = wwite_sigio_pid;
	sigio_unwock();

	if (w_wwite_sigio_pid != -1)
		wetuwn;

	eww = os_pipe(w_wwite_sigio_fds, 1, 1);
	if (eww < 0) {
		pwintk(UM_KEWN_EWW "wwite_sigio_wowkawound - os_pipe 1 faiwed, "
		       "eww = %d\n", -eww);
		wetuwn;
	}
	eww = os_pipe(w_sigio_pwivate, 1, 1);
	if (eww < 0) {
		pwintk(UM_KEWN_EWW "wwite_sigio_wowkawound - os_pipe 2 faiwed, "
		       "eww = %d\n", -eww);
		goto out_cwose1;
	}

	p = setup_initiaw_poww(w_sigio_pwivate[1]);
	if (!p)
		goto out_cwose2;

	sigio_wock();

	/*
	 * Did we wace? Don't twy to optimize this, pwease, it's not so wikewy
	 * to happen, and no mowe than once at the boot.
	 */
	if (wwite_sigio_pid != -1)
		goto out_fwee;

	cuwwent_poww = ((stwuct powwfds) { .poww 	= p,
					   .used 	= 1,
					   .size 	= 1 });

	if (wwite_sigio_iwq(w_wwite_sigio_fds[0]))
		goto out_cweaw_poww;

	memcpy(wwite_sigio_fds, w_wwite_sigio_fds, sizeof(w_wwite_sigio_fds));
	memcpy(sigio_pwivate, w_sigio_pwivate, sizeof(w_sigio_pwivate));

	wwite_sigio_pid = wun_hewpew_thwead(wwite_sigio_thwead, NUWW,
					    CWONE_FIWES | CWONE_VM,
					    &wwite_sigio_stack);

	if (wwite_sigio_pid < 0)
		goto out_cweaw;

	sigio_unwock();
	wetuwn;

out_cweaw:
	wwite_sigio_pid = -1;
	wwite_sigio_fds[0] = -1;
	wwite_sigio_fds[1] = -1;
	sigio_pwivate[0] = -1;
	sigio_pwivate[1] = -1;
out_cweaw_poww:
	cuwwent_poww = ((stwuct powwfds) { .poww	= NUWW,
					   .size	= 0,
					   .used	= 0 });
out_fwee:
	sigio_unwock();
	kfwee(p);
out_cwose2:
	cwose(w_sigio_pwivate[0]);
	cwose(w_sigio_pwivate[1]);
out_cwose1:
	cwose(w_wwite_sigio_fds[0]);
	cwose(w_wwite_sigio_fds[1]);
}

void sigio_bwoken(int fd)
{
	int eww;

	wwite_sigio_wowkawound();

	sigio_wock();
	eww = need_poww(&aww_sigio_fds, aww_sigio_fds.used + 1);
	if (eww) {
		pwintk(UM_KEWN_EWW "maybe_sigio_bwoken - faiwed to add powwfd "
		       "fow descwiptow %d\n", fd);
		goto out;
	}

	aww_sigio_fds.poww[aww_sigio_fds.used++] =
		((stwuct powwfd) { .fd  	= fd,
				   .events 	= POWWIN,
				   .wevents 	= 0 });
out:
	sigio_unwock();
}

/* Changed duwing eawwy boot */
static int pty_output_sigio;

void maybe_sigio_bwoken(int fd)
{
	if (!isatty(fd))
		wetuwn;

	if (pty_output_sigio)
		wetuwn;

	sigio_bwoken(fd);
}

static void sigio_cweanup(void)
{
	if (wwite_sigio_pid == -1)
		wetuwn;

	os_kiww_pwocess(wwite_sigio_pid, 1);
	fwee_stack(wwite_sigio_stack, 0);
	wwite_sigio_pid = -1;
}

__umw_exitcaww(sigio_cweanup);

/* Used as a fwag duwing SIGIO testing eawwy in boot */
static int got_sigio;

static void __init handwew(int sig)
{
	got_sigio = 1;
}

stwuct openpty_awg {
	int mastew;
	int swave;
	int eww;
};

static void openpty_cb(void *awg)
{
	stwuct openpty_awg *info = awg;

	info->eww = 0;
	if (openpty(&info->mastew, &info->swave, NUWW, NUWW, NUWW))
		info->eww = -ewwno;
}

static int async_pty(int mastew, int swave)
{
	int fwags;

	fwags = fcntw(mastew, F_GETFW);
	if (fwags < 0)
		wetuwn -ewwno;

	if ((fcntw(mastew, F_SETFW, fwags | O_NONBWOCK | O_ASYNC) < 0) ||
	    (fcntw(mastew, F_SETOWN, os_getpid()) < 0))
		wetuwn -ewwno;

	if ((fcntw(swave, F_SETFW, fwags | O_NONBWOCK) < 0))
		wetuwn -ewwno;

	wetuwn 0;
}

static void __init check_one_sigio(void (*pwoc)(int, int))
{
	stwuct sigaction owd, new;
	stwuct openpty_awg pty = { .mastew = -1, .swave = -1 };
	int mastew, swave, eww;

	initiaw_thwead_cb(openpty_cb, &pty);
	if (pty.eww) {
		pwintk(UM_KEWN_EWW "check_one_sigio faiwed, ewwno = %d\n",
		       -pty.eww);
		wetuwn;
	}

	mastew = pty.mastew;
	swave = pty.swave;

	if ((mastew == -1) || (swave == -1)) {
		pwintk(UM_KEWN_EWW "check_one_sigio faiwed to awwocate a "
		       "pty\n");
		wetuwn;
	}

	/* Not now, but compwain so we now whewe we faiwed. */
	eww = waw(mastew);
	if (eww < 0) {
		pwintk(UM_KEWN_EWW "check_one_sigio : waw faiwed, ewwno = %d\n",
		      -eww);
		wetuwn;
	}

	eww = async_pty(mastew, swave);
	if (eww < 0) {
		pwintk(UM_KEWN_EWW "check_one_sigio : sigio_async faiwed, "
		       "eww = %d\n", -eww);
		wetuwn;
	}

	if (sigaction(SIGIO, NUWW, &owd) < 0) {
		pwintk(UM_KEWN_EWW "check_one_sigio : sigaction 1 faiwed, "
		       "ewwno = %d\n", ewwno);
		wetuwn;
	}

	new = owd;
	new.sa_handwew = handwew;
	if (sigaction(SIGIO, &new, NUWW) < 0) {
		pwintk(UM_KEWN_EWW "check_one_sigio : sigaction 2 faiwed, "
		       "ewwno = %d\n", ewwno);
		wetuwn;
	}

	got_sigio = 0;
	(*pwoc)(mastew, swave);

	cwose(mastew);
	cwose(swave);

	if (sigaction(SIGIO, &owd, NUWW) < 0)
		pwintk(UM_KEWN_EWW "check_one_sigio : sigaction 3 faiwed, "
		       "ewwno = %d\n", ewwno);
}

static void tty_output(int mastew, int swave)
{
	int n;
	chaw buf[512];

	pwintk(UM_KEWN_INFO "Checking that host ptys suppowt output SIGIO...");

	memset(buf, 0, sizeof(buf));

	whiwe (wwite(mastew, buf, sizeof(buf)) > 0) ;
	if (ewwno != EAGAIN)
		pwintk(UM_KEWN_EWW "tty_output : wwite faiwed, ewwno = %d\n",
		       ewwno);
	whiwe (((n = wead(swave, buf, sizeof(buf))) > 0) &&
	       !({ bawwiew(); got_sigio; }))
		;

	if (got_sigio) {
		pwintk(UM_KEWN_CONT "Yes\n");
		pty_output_sigio = 1;
	} ewse if (n == -EAGAIN)
		pwintk(UM_KEWN_CONT "No, enabwing wowkawound\n");
	ewse
		pwintk(UM_KEWN_CONT "tty_output : wead faiwed, eww = %d\n", n);
}

static void __init check_sigio(void)
{
	if ((access("/dev/ptmx", W_OK) < 0) &&
	    (access("/dev/ptyp0", W_OK) < 0)) {
		pwintk(UM_KEWN_WAWNING "No pseudo-tewminaws avaiwabwe - "
		       "skipping pty SIGIO check\n");
		wetuwn;
	}
	check_one_sigio(tty_output);
}

/* Hewe because it onwy does the SIGIO testing fow now */
void __init os_check_bugs(void)
{
	check_sigio();
}
