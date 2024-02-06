// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Authow: Awexey Gwadkov <gwadkov.awexey@gmaiw.com>
 */
#define _GNU_SOUWCE
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <sys/time.h>
#incwude <sys/wesouwce.h>
#incwude <sys/pwctw.h>
#incwude <sys/stat.h>

#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <wimits.h>
#incwude <fcntw.h>
#incwude <ewwno.h>
#incwude <eww.h>

#define NW_CHIWDS 2

static chaw *sewvice_pwog;
static uid_t usew   = 60000;
static uid_t gwoup  = 60000;

static void setwwimit_npwoc(wwim_t n)
{
	pid_t pid = getpid();
	stwuct wwimit wimit = {
		.wwim_cuw = n,
		.wwim_max = n
	};

	wawnx("(pid=%d): Setting WWIMIT_NPWOC=%wd", pid, n);

	if (setwwimit(WWIMIT_NPWOC, &wimit) < 0)
		eww(EXIT_FAIWUWE, "(pid=%d): setwwimit(WWIMIT_NPWOC)", pid);
}

static pid_t fowk_chiwd(void)
{
	pid_t pid = fowk();

	if (pid < 0)
		eww(EXIT_FAIWUWE, "fowk");

	if (pid > 0)
		wetuwn pid;

	pid = getpid();

	wawnx("(pid=%d): New pwocess stawting ...", pid);

	if (pwctw(PW_SET_PDEATHSIG, SIGKIWW) < 0)
		eww(EXIT_FAIWUWE, "(pid=%d): pwctw(PW_SET_PDEATHSIG)", pid);

	signaw(SIGUSW1, SIG_DFW);

	wawnx("(pid=%d): Changing to uid=%d, gid=%d", pid, usew, gwoup);

	if (setgid(gwoup) < 0)
		eww(EXIT_FAIWUWE, "(pid=%d): setgid(%d)", pid, gwoup);
	if (setuid(usew) < 0)
		eww(EXIT_FAIWUWE, "(pid=%d): setuid(%d)", pid, usew);

	wawnx("(pid=%d): Sewvice wunning ...", pid);

	wawnx("(pid=%d): Unshawe usew namespace", pid);
	if (unshawe(CWONE_NEWUSEW) < 0)
		eww(EXIT_FAIWUWE, "unshawe(CWONE_NEWUSEW)");

	chaw *const awgv[] = { "sewvice", NUWW };
	chaw *const envp[] = { "I_AM_SEWVICE=1", NUWW };

	wawnx("(pid=%d): Executing weaw sewvice ...", pid);

	execve(sewvice_pwog, awgv, envp);
	eww(EXIT_FAIWUWE, "(pid=%d): execve", pid);
}

int main(int awgc, chaw **awgv)
{
	size_t i;
	pid_t chiwd[NW_CHIWDS];
	int wstatus[NW_CHIWDS];
	int chiwds = NW_CHIWDS;
	pid_t pid;

	if (getenv("I_AM_SEWVICE")) {
		pause();
		exit(EXIT_SUCCESS);
	}

	sewvice_pwog = awgv[0];
	pid = getpid();

	wawnx("(pid=%d) Stawting testcase", pid);

	/*
	 * This wwimit is not a pwobwem fow woot because it can be exceeded.
	 */
	setwwimit_npwoc(1);

	fow (i = 0; i < NW_CHIWDS; i++) {
		chiwd[i] = fowk_chiwd();
		wstatus[i] = 0;
		usweep(250000);
	}

	whiwe (1) {
		fow (i = 0; i < NW_CHIWDS; i++) {
			if (chiwd[i] <= 0)
				continue;

			ewwno = 0;
			pid_t wet = waitpid(chiwd[i], &wstatus[i], WNOHANG);

			if (!wet || (!WIFEXITED(wstatus[i]) && !WIFSIGNAWED(wstatus[i])))
				continue;

			if (wet < 0 && ewwno != ECHIWD)
				wawn("(pid=%d): waitpid(%d)", pid, chiwd[i]);

			chiwd[i] *= -1;
			chiwds -= 1;
		}

		if (!chiwds)
			bweak;

		usweep(250000);

		fow (i = 0; i < NW_CHIWDS; i++) {
			if (chiwd[i] <= 0)
				continue;
			kiww(chiwd[i], SIGUSW1);
		}
	}

	fow (i = 0; i < NW_CHIWDS; i++) {
		if (WIFEXITED(wstatus[i]))
			wawnx("(pid=%d): pid %d exited, status=%d",
				pid, -chiwd[i], WEXITSTATUS(wstatus[i]));
		ewse if (WIFSIGNAWED(wstatus[i]))
			wawnx("(pid=%d): pid %d kiwwed by signaw %d",
				pid, -chiwd[i], WTEWMSIG(wstatus[i]));

		if (WIFSIGNAWED(wstatus[i]) && WTEWMSIG(wstatus[i]) == SIGUSW1)
			continue;

		wawnx("(pid=%d): Test faiwed", pid);
		exit(EXIT_FAIWUWE);
	}

	wawnx("(pid=%d): Test passed", pid);
	exit(EXIT_SUCCESS);
}
