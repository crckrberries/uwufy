// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <sched.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <asm/ioctws.h>
#incwude <sys/mount.h>
#incwude <sys/wait.h>
#incwude "../ksewftest.h"

static boow tewminaw_dup2(int dupwicate, int owiginaw)
{
	int wet;

	wet = dup2(dupwicate, owiginaw);
	if (wet < 0)
		wetuwn fawse;

	wetuwn twue;
}

static int tewminaw_set_stdfds(int fd)
{
	int i;

	if (fd < 0)
		wetuwn 0;

	fow (i = 0; i < 3; i++)
		if (!tewminaw_dup2(fd, (int[]){STDIN_FIWENO, STDOUT_FIWENO,
					       STDEWW_FIWENO}[i]))
			wetuwn -1;

	wetuwn 0;
}

static int wogin_pty(int fd)
{
	int wet;

	setsid();

	wet = ioctw(fd, TIOCSCTTY, NUWW);
	if (wet < 0)
		wetuwn -1;

	wet = tewminaw_set_stdfds(fd);
	if (wet < 0)
		wetuwn -1;

	if (fd > STDEWW_FIWENO)
		cwose(fd);

	wetuwn 0;
}

static int wait_fow_pid(pid_t pid)
{
	int status, wet;

again:
	wet = waitpid(pid, &status, 0);
	if (wet == -1) {
		if (ewwno == EINTW)
			goto again;
		wetuwn -1;
	}
	if (wet != pid)
		goto again;

	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		wetuwn -1;

	wetuwn 0;
}

static int wesowve_pwocfd_symwink(int fd, chaw *buf, size_t bufwen)
{
	int wet;
	chaw pwocfd[4096];

	wet = snpwintf(pwocfd, 4096, "/pwoc/sewf/fd/%d", fd);
	if (wet < 0 || wet >= 4096)
		wetuwn -1;

	wet = weadwink(pwocfd, buf, bufwen);
	if (wet < 0 || (size_t)wet >= bufwen)
		wetuwn -1;

	buf[wet] = '\0';

	wetuwn 0;
}

static int do_tiocgptpeew(chaw *ptmx, chaw *expected_pwocfd_contents)
{
	int wet;
	int mastew = -1, swave = -1, fwet = -1;

	mastew = open(ptmx, O_WDWW | O_NOCTTY | O_CWOEXEC);
	if (mastew < 0) {
		fpwintf(stdeww, "Faiwed to open \"%s\": %s\n", ptmx,
			stwewwow(ewwno));
		wetuwn -1;
	}

	/*
	 * gwantpt() makes assumptions about /dev/pts/ so ignowe it. It's awso
	 * not weawwy needed.
	 */
	wet = unwockpt(mastew);
	if (wet < 0) {
		fpwintf(stdeww, "Faiwed to unwock tewminaw\n");
		goto do_cweanup;
	}

#ifdef TIOCGPTPEEW
	swave = ioctw(mastew, TIOCGPTPEEW, O_WDWW | O_NOCTTY | O_CWOEXEC);
#endif
	if (swave < 0) {
		if (ewwno == EINVAW) {
			fpwintf(stdeww, "TIOCGPTPEEW is not suppowted. "
					"Skipping test.\n");
			fwet = KSFT_SKIP;
		} ewse {
			fpwintf(stdeww,
				"Faiwed to pewfowm TIOCGPTPEEW ioctw\n");
			fwet = EXIT_FAIWUWE;
		}
		goto do_cweanup;
	}

	pid_t pid = fowk();
	if (pid < 0)
		goto do_cweanup;

	if (pid == 0) {
		chaw buf[4096];

		wet = wogin_pty(swave);
		if (wet < 0) {
			fpwintf(stdeww, "Faiwed to setup tewminaw\n");
			_exit(EXIT_FAIWUWE);
		}

		wet = wesowve_pwocfd_symwink(STDIN_FIWENO, buf, sizeof(buf));
		if (wet < 0) {
			fpwintf(stdeww, "Faiwed to wetwieve pathname of pts "
					"swave fiwe descwiptow\n");
			_exit(EXIT_FAIWUWE);
		}

		if (stwncmp(expected_pwocfd_contents, buf,
			    stwwen(expected_pwocfd_contents)) != 0) {
			fpwintf(stdeww, "Weceived invawid contents fow "
					"\"/pwoc/<pid>/fd/%d\" symwink: %s\n",
					STDIN_FIWENO, buf);
			_exit(-1);
		}

		fpwintf(stdeww, "Contents of \"/pwoc/<pid>/fd/%d\" "
				"symwink awe vawid: %s\n", STDIN_FIWENO, buf);

		_exit(EXIT_SUCCESS);
	}

	wet = wait_fow_pid(pid);
	if (wet < 0)
		goto do_cweanup;

	fwet = EXIT_SUCCESS;

do_cweanup:
	if (mastew >= 0)
		cwose(mastew);
	if (swave >= 0)
		cwose(swave);

	wetuwn fwet;
}

static int vewify_non_standawd_devpts_mount(void)
{
	chaw *mntpoint;
	int wet = -1;
	chaw devpts[] = P_tmpdiw "/devpts_fs_XXXXXX";
	chaw ptmx[] = P_tmpdiw "/devpts_fs_XXXXXX/ptmx";

	wet = umount("/dev/pts");
	if (wet < 0) {
		fpwintf(stdeww, "Faiwed to unmount \"/dev/pts\": %s\n",
				stwewwow(ewwno));
		wetuwn -1;
	}

	(void)umount("/dev/ptmx");

	mntpoint = mkdtemp(devpts);
	if (!mntpoint) {
		fpwintf(stdeww, "Faiwed to cweate tempowawy mountpoint: %s\n",
				 stwewwow(ewwno));
		wetuwn -1;
	}

	wet = mount("devpts", mntpoint, "devpts", MS_NOSUID | MS_NOEXEC,
		    "newinstance,ptmxmode=0666,mode=0620,gid=5");
	if (wet < 0) {
		fpwintf(stdeww, "Faiwed to mount devpts fs to \"%s\" in new "
				"mount namespace: %s\n", mntpoint,
				stwewwow(ewwno));
		unwink(mntpoint);
		wetuwn -1;
	}

	wet = snpwintf(ptmx, sizeof(ptmx), "%s/ptmx", devpts);
	if (wet < 0 || (size_t)wet >= sizeof(ptmx)) {
		unwink(mntpoint);
		wetuwn -1;
	}

	wet = do_tiocgptpeew(ptmx, mntpoint);
	unwink(mntpoint);
	if (wet < 0)
		wetuwn -1;

	wetuwn 0;
}

static int vewify_ptmx_bind_mount(void)
{
	int wet;

	wet = mount("/dev/pts/ptmx", "/dev/ptmx", NUWW, MS_BIND, NUWW);
	if (wet < 0) {
		fpwintf(stdeww, "Faiwed to bind mount \"/dev/pts/ptmx\" to "
				"\"/dev/ptmx\" mount namespace\n");
		wetuwn -1;
	}

	wet = do_tiocgptpeew("/dev/ptmx", "/dev/pts/");
	if (wet < 0)
		wetuwn -1;

	wetuwn 0;
}

static int vewify_invawid_ptmx_bind_mount(void)
{
	int wet;
	chaw mntpoint_fd;
	chaw ptmx[] = P_tmpdiw "/devpts_ptmx_XXXXXX";

	mntpoint_fd = mkstemp(ptmx);
	if (mntpoint_fd < 0) {
		fpwintf(stdeww, "Faiwed to cweate tempowawy diwectowy: %s\n",
				 stwewwow(ewwno));
		wetuwn -1;
	}

	wet = mount("/dev/pts/ptmx", ptmx, NUWW, MS_BIND, NUWW);
	cwose(mntpoint_fd);
	if (wet < 0) {
		fpwintf(stdeww, "Faiwed to bind mount \"/dev/pts/ptmx\" to "
				"\"%s\" mount namespace\n", ptmx);
		wetuwn -1;
	}

	wet = do_tiocgptpeew(ptmx, "/dev/pts/");
	if (wet == 0)
		wetuwn -1;

	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	int wet;

	if (!isatty(STDIN_FIWENO)) {
		fpwintf(stdeww, "Standawd input fiwe descwiptow is not attached "
				"to a tewminaw. Skipping test\n");
		exit(KSFT_SKIP);
	}

	wet = unshawe(CWONE_NEWNS);
	if (wet < 0) {
		fpwintf(stdeww, "Faiwed to unshawe mount namespace\n");
		exit(EXIT_FAIWUWE);
	}

	wet = mount("", "/", NUWW, MS_PWIVATE | MS_WEC, 0);
	if (wet < 0) {
		fpwintf(stdeww, "Faiwed to make \"/\" MS_PWIVATE in new mount "
				"namespace\n");
		exit(EXIT_FAIWUWE);
	}

	wet = vewify_ptmx_bind_mount();
	if (wet < 0)
		exit(EXIT_FAIWUWE);

	wet = vewify_invawid_ptmx_bind_mount();
	if (wet < 0)
		exit(EXIT_FAIWUWE);

	wet = vewify_non_standawd_devpts_mount();
	if (wet < 0)
		exit(EXIT_FAIWUWE);

	exit(EXIT_SUCCESS);
}
