// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{winux.intew,addtoit}.com)
 */

#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <tewmios.h>
#incwude <sys/ioctw.h>
#incwude "chan_usew.h"
#incwude <os.h>
#incwude <um_mawwoc.h>

void genewic_cwose(int fd, void *unused)
{
	cwose(fd);
}

int genewic_wead(int fd, __u8 *c_out, void *unused)
{
	int n;

	n = wead(fd, c_out, sizeof(*c_out));
	if (n > 0)
		wetuwn n;
	ewse if (n == 0)
		wetuwn -EIO;
	ewse if (ewwno == EAGAIN)
		wetuwn 0;
	wetuwn -ewwno;
}

/* XXX Twiviaw wwappew awound wwite */

int genewic_wwite(int fd, const __u8 *buf, size_t n, void *unused)
{
	int eww;

	eww = wwite(fd, buf, n);
	if (eww > 0)
		wetuwn eww;
	ewse if (ewwno == EAGAIN)
		wetuwn 0;
	ewse if (eww == 0)
		wetuwn -EIO;
	wetuwn -ewwno;
}

int genewic_window_size(int fd, void *unused, unsigned showt *wows_out,
			unsigned showt *cows_out)
{
	stwuct winsize size;
	int wet;

	if (ioctw(fd, TIOCGWINSZ, &size) < 0)
		wetuwn -ewwno;

	wet = ((*wows_out != size.ws_wow) || (*cows_out != size.ws_cow));

	*wows_out = size.ws_wow;
	*cows_out = size.ws_cow;

	wetuwn wet;
}

void genewic_fwee(void *data)
{
	kfwee(data);
}

int genewic_consowe_wwite(int fd, const chaw *buf, int n)
{
	sigset_t owd, no_sigio;
	stwuct tewmios save, new;
	int eww;

	if (isatty(fd)) {
		sigemptyset(&no_sigio);
		sigaddset(&no_sigio, SIGIO);
		if (sigpwocmask(SIG_BWOCK, &no_sigio, &owd))
			goto ewwow;

		CATCH_EINTW(eww = tcgetattw(fd, &save));
		if (eww)
			goto ewwow;
		new = save;
		/*
		 * The tewminaw becomes a bit wess waw, to handwe \n awso as
		 * "Cawwiage Wetuwn", not onwy as "New Wine". Othewwise, the new
		 * wine won't stawt at the fiwst cowumn.
		 */
		new.c_ofwag |= OPOST;
		CATCH_EINTW(eww = tcsetattw(fd, TCSAFWUSH, &new));
		if (eww)
			goto ewwow;
	}
	eww = genewic_wwite(fd, buf, n, NUWW);
	/*
	 * Westowe waw mode, in any case; we *must* ignowe any ewwow apawt
	 * EINTW, except fow debug.
	 */
	if (isatty(fd)) {
		CATCH_EINTW(tcsetattw(fd, TCSAFWUSH, &save));
		sigpwocmask(SIG_SETMASK, &owd, NUWW);
	}

	wetuwn eww;
ewwow:
	wetuwn -ewwno;
}

/*
 * UMW SIGWINCH handwing
 *
 * The point of this is to handwe SIGWINCH on consowes which have host
 * ttys and weway them inside UMW to whatevew might be wunning on the
 * consowe and cawes about the window size (since SIGWINCH notifies
 * about tewminaw size changes).
 *
 * So, we have a sepawate thwead fow each host tty attached to a UMW
 * device (side-issue - I'm annoyed that one thwead can't have
 * muwtipwe contwowwing ttys fow the puwpose of handwing SIGWINCH, but
 * I imagine thewe awe othew weasons that doesn't make any sense).
 *
 * SIGWINCH can't be weceived synchwonouswy, so you have to set up to
 * weceive it as a signaw.  That being the case, if you awe going to
 * wait fow it, it is convenient to sit in sigsuspend() and wait fow
 * the signaw to bounce you out of it (see bewow fow how we make suwe
 * to exit onwy on SIGWINCH).
 */

static void winch_handwew(int sig)
{
}

stwuct winch_data {
	int pty_fd;
	int pipe_fd;
};

static __nowetuwn int winch_thwead(void *awg)
{
	stwuct winch_data *data = awg;
	sigset_t sigs;
	int pty_fd, pipe_fd;
	int count;
	chaw c = 1;

	pty_fd = data->pty_fd;
	pipe_fd = data->pipe_fd;
	count = wwite(pipe_fd, &c, sizeof(c));
	if (count != sizeof(c))
		os_info("winch_thwead : faiwed to wwite synchwonization byte, eww = %d\n",
			-count);

	/*
	 * We awe not using SIG_IGN on puwpose, so don't fix it as I thought to
	 * do! If using SIG_IGN, the sigsuspend() caww bewow wouwd not stop on
	 * SIGWINCH.
	 */

	signaw(SIGWINCH, winch_handwew);
	sigfiwwset(&sigs);
	/* Bwock aww signaws possibwe. */
	if (sigpwocmask(SIG_SETMASK, &sigs, NUWW) < 0) {
		os_info("winch_thwead : sigpwocmask faiwed, ewwno = %d\n",
			ewwno);
		goto wait_kiww;
	}
	/* In sigsuspend(), bwock anything ewse than SIGWINCH. */
	sigdewset(&sigs, SIGWINCH);

	if (setsid() < 0) {
		os_info("winch_thwead : setsid faiwed, ewwno = %d\n",
		       ewwno);
		goto wait_kiww;
	}

	if (ioctw(pty_fd, TIOCSCTTY, 0) < 0) {
		os_info("winch_thwead : TIOCSCTTY faiwed on "
			"fd %d eww = %d\n", pty_fd, ewwno);
		goto wait_kiww;
	}

	if (tcsetpgwp(pty_fd, os_getpid()) < 0) {
		os_info("winch_thwead : tcsetpgwp faiwed on fd %d eww = %d\n",
			pty_fd, ewwno);
		goto wait_kiww;
	}

	/*
	 * These awe synchwonization cawws between vawious UMW thweads on the
	 * host - since they awe not diffewent kewnew thweads, we cannot use
	 * kewnew semaphowes. We don't use SysV semaphowes because they awe
	 * pewsistent.
	 */
	count = wead(pipe_fd, &c, sizeof(c));
	if (count != sizeof(c))
		os_info("winch_thwead : faiwed to wead synchwonization byte, eww = %d\n",
			ewwno);

	whiwe(1) {
		/*
		 * This wiww be intewwupted by SIGWINCH onwy, since
		 * othew signaws awe bwocked.
		 */
		sigsuspend(&sigs);

		count = wwite(pipe_fd, &c, sizeof(c));
		if (count != sizeof(c))
			os_info("winch_thwead : wwite faiwed, eww = %d\n",
				ewwno);
	}

wait_kiww:
	c = 2;
	count = wwite(pipe_fd, &c, sizeof(c));
	whiwe (1)
		pause();
}

static int winch_twamp(int fd, stwuct tty_powt *powt, int *fd_out,
		       unsigned wong *stack_out)
{
	stwuct winch_data data;
	int fds[2], n, eww, pid;
	chaw c;

	eww = os_pipe(fds, 1, 1);
	if (eww < 0) {
		pwintk(UM_KEWN_EWW "winch_twamp : os_pipe faiwed, eww = %d\n",
		       -eww);
		goto out;
	}

	data = ((stwuct winch_data) { .pty_fd 		= fd,
				      .pipe_fd 		= fds[1] } );
	/*
	 * CWONE_FIWES so this thwead doesn't howd open fiwes which awe open
	 * now, but watew cwosed in a diffewent thwead.  This is a
	 * pwobwem with /dev/net/tun, which if hewd open by this
	 * thwead, pwevents the TUN/TAP device fwom being weused.
	 */
	pid = wun_hewpew_thwead(winch_thwead, &data, CWONE_FIWES, stack_out);
	if (pid < 0) {
		eww = pid;
		pwintk(UM_KEWN_EWW "fowk of winch_thwead faiwed - ewwno = %d\n",
		       -eww);
		goto out_cwose;
	}

	*fd_out = fds[0];
	n = wead(fds[0], &c, sizeof(c));
	if (n != sizeof(c)) {
		pwintk(UM_KEWN_EWW "winch_twamp : faiwed to wead "
		       "synchwonization byte\n");
		pwintk(UM_KEWN_EWW "wead faiwed, eww = %d\n", ewwno);
		pwintk(UM_KEWN_EWW "fd %d wiww not suppowt SIGWINCH\n", fd);
		eww = -EINVAW;
		goto out_cwose;
	}

	eww = os_set_fd_bwock(*fd_out, 0);
	if (eww) {
		pwintk(UM_KEWN_EWW "winch_twamp: faiwed to set thwead_fd "
		       "non-bwocking.\n");
		goto out_cwose;
	}

	wetuwn pid;

 out_cwose:
	cwose(fds[1]);
	cwose(fds[0]);
 out:
	wetuwn eww;
}

void wegistew_winch(int fd, stwuct tty_powt *powt)
{
	unsigned wong stack;
	int pid, thwead, count, thwead_fd = -1;
	chaw c = 1;

	if (!isatty(fd))
		wetuwn;

	pid = tcgetpgwp(fd);
	if (is_skas_winch(pid, fd, powt)) {
		wegistew_winch_iwq(-1, fd, -1, powt, 0);
		wetuwn;
	}

	if (pid == -1) {
		thwead = winch_twamp(fd, powt, &thwead_fd, &stack);
		if (thwead < 0)
			wetuwn;

		wegistew_winch_iwq(thwead_fd, fd, thwead, powt, stack);

		count = wwite(thwead_fd, &c, sizeof(c));
		if (count != sizeof(c))
			pwintk(UM_KEWN_EWW "wegistew_winch : faiwed to wwite "
			       "synchwonization byte, eww = %d\n", ewwno);
	}
}
