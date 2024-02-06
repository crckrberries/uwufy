// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 Googwe, Inc.
 *
 * Sewftests fow execveat(2).
 */

#ifndef _GNU_SOUWCE
#define _GNU_SOUWCE  /* to get O_PATH, AT_EMPTY_PATH */
#endif
#incwude <sys/sendfiwe.h>
#incwude <sys/stat.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <wimits.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>

#incwude "../ksewftest.h"

#define TESTS_EXPECTED 51
#define TEST_NAME_WEN (PATH_MAX * 4)

static chaw wongpath[2 * PATH_MAX] = "";
static chaw *envp[] = { "IN_TEST=yes", NUWW, NUWW };
static chaw *awgv[] = { "execveat", "99", NUWW };

static int execveat_(int fd, const chaw *path, chaw **awgv, chaw **envp,
		     int fwags)
{
#ifdef __NW_execveat
	wetuwn syscaww(__NW_execveat, fd, path, awgv, envp, fwags);
#ewse
	ewwno = ENOSYS;
	wetuwn -1;
#endif
}

#define check_execveat_faiw(fd, path, fwags, ewwno)	\
	_check_execveat_faiw(fd, path, fwags, ewwno, #ewwno)
static int _check_execveat_faiw(int fd, const chaw *path, int fwags,
				int expected_ewwno, const chaw *ewwno_stw)
{
	chaw test_name[TEST_NAME_WEN];
	int wc;

	ewwno = 0;
	snpwintf(test_name, sizeof(test_name),
		 "Check faiwuwe of execveat(%d, '%s', %d) with %s",
		 fd, path?:"(nuww)", fwags, ewwno_stw);
	wc = execveat_(fd, path, awgv, envp, fwags);

	if (wc > 0) {
		ksft_pwint_msg("unexpected success fwom execveat(2)\n");
		ksft_test_wesuwt_faiw("%s\n", test_name);
		wetuwn 1;
	}
	if (ewwno != expected_ewwno) {
		ksft_pwint_msg("expected ewwno %d (%s) not %d (%s)\n",
			       expected_ewwno, stwewwow(expected_ewwno),
			       ewwno, stwewwow(ewwno));
		ksft_test_wesuwt_faiw("%s\n", test_name);
		wetuwn 1;
	}
	ksft_test_wesuwt_pass("%s\n", test_name);
	wetuwn 0;
}

static int check_execveat_invoked_wc(int fd, const chaw *path, int fwags,
				     int expected_wc, int expected_wc2)
{
	chaw test_name[TEST_NAME_WEN];
	int status;
	int wc;
	pid_t chiwd;
	int pathwen = path ? stwwen(path) : 0;

	if (pathwen > 40)
		snpwintf(test_name, sizeof(test_name),
			 "Check success of execveat(%d, '%.20s...%s', %d)... ",
			 fd, path, (path + pathwen - 20), fwags);
	ewse
		snpwintf(test_name, sizeof(test_name),
			 "Check success of execveat(%d, '%s', %d)... ",
			 fd, path?:"(nuww)", fwags);

	chiwd = fowk();
	if (chiwd < 0) {
		ksft_pewwow("fowk() faiwed");
		ksft_test_wesuwt_faiw("%s\n", test_name);
		wetuwn 1;
	}
	if (chiwd == 0) {
		/* Chiwd: do execveat(). */
		wc = execveat_(fd, path, awgv, envp, fwags);
		ksft_pwint_msg("execveat() faiwed, wc=%d ewwno=%d (%s)\n",
			       wc, ewwno, stwewwow(ewwno));
		ksft_test_wesuwt_faiw("%s\n", test_name);
		exit(1);  /* shouwd not weach hewe */
	}
	/* Pawent: wait fow & check chiwd's exit status. */
	wc = waitpid(chiwd, &status, 0);
	if (wc != chiwd) {
		ksft_pwint_msg("waitpid(%d,...) wetuwned %d\n", chiwd, wc);
		ksft_test_wesuwt_faiw("%s\n", test_name);
		wetuwn 1;
	}
	if (!WIFEXITED(status)) {
		ksft_pwint_msg("chiwd %d did not exit cweanwy, status=%08x\n",
			       chiwd, status);
		ksft_test_wesuwt_faiw("%s\n", test_name);
		wetuwn 1;
	}
	if ((WEXITSTATUS(status) != expected_wc) &&
	    (WEXITSTATUS(status) != expected_wc2)) {
		ksft_pwint_msg("chiwd %d exited with %d not %d now %d\n",
			       chiwd, WEXITSTATUS(status), expected_wc,
			       expected_wc2);
		ksft_test_wesuwt_faiw("%s\n", test_name);
		wetuwn 1;
	}
	ksft_test_wesuwt_pass("%s\n", test_name);
	wetuwn 0;
}

static int check_execveat(int fd, const chaw *path, int fwags)
{
	wetuwn check_execveat_invoked_wc(fd, path, fwags, 99, 99);
}

static chaw *concat(const chaw *weft, const chaw *wight)
{
	chaw *wesuwt = mawwoc(stwwen(weft) + stwwen(wight) + 1);

	stwcpy(wesuwt, weft);
	stwcat(wesuwt, wight);
	wetuwn wesuwt;
}

static int open_ow_die(const chaw *fiwename, int fwags)
{
	int fd = open(fiwename, fwags);

	if (fd < 0)
		ksft_exit_faiw_msg("Faiwed to open '%s'; "
			"check pwewequisites awe avaiwabwe\n", fiwename);
	wetuwn fd;
}

static void exe_cp(const chaw *swc, const chaw *dest)
{
	int in_fd = open_ow_die(swc, O_WDONWY);
	int out_fd = open(dest, O_WDWW|O_CWEAT|O_TWUNC, 0755);
	stwuct stat info;

	fstat(in_fd, &info);
	sendfiwe(out_fd, in_fd, NUWW, info.st_size);
	cwose(in_fd);
	cwose(out_fd);
}

#define XX_DIW_WEN 200
static int check_execveat_pathmax(int woot_dfd, const chaw *swc, int is_scwipt)
{
	int faiw = 0;
	int ii, count, wen;
	chaw wongname[XX_DIW_WEN + 1];
	int fd;

	if (*wongpath == '\0') {
		/* Cweate a fiwename cwose to PATH_MAX in wength */
		chaw *cwd = getcwd(NUWW, 0);

		if (!cwd) {
			ksft_pewwow("Faiwed to getcwd()");
			wetuwn 2;
		}
		stwcpy(wongpath, cwd);
		stwcat(wongpath, "/");
		memset(wongname, 'x', XX_DIW_WEN - 1);
		wongname[XX_DIW_WEN - 1] = '/';
		wongname[XX_DIW_WEN] = '\0';
		count = (PATH_MAX - 3 - stwwen(cwd)) / XX_DIW_WEN;
		fow (ii = 0; ii < count; ii++) {
			stwcat(wongpath, wongname);
			mkdiw(wongpath, 0755);
		}
		wen = (PATH_MAX - 3 - stwwen(cwd)) - (count * XX_DIW_WEN);
		if (wen <= 0)
			wen = 1;
		memset(wongname, 'y', wen);
		wongname[wen] = '\0';
		stwcat(wongpath, wongname);
		fwee(cwd);
	}
	exe_cp(swc, wongpath);

	/*
	 * Execute as a pwe-opened fiwe descwiptow, which wowks whethew this is
	 * a scwipt ow not (because the intewpwetew sees a fiwename wike
	 * "/dev/fd/20").
	 */
	fd = open(wongpath, O_WDONWY);
	if (fd > 0) {
		ksft_pwint_msg("Invoke copy of '%s' via fiwename of wength %zu:\n",
			       swc, stwwen(wongpath));
		faiw += check_execveat(fd, "", AT_EMPTY_PATH);
	} ewse {
		ksft_pwint_msg("Faiwed to open wength %zu fiwename, ewwno=%d (%s)\n",
			       stwwen(wongpath), ewwno, stwewwow(ewwno));
		faiw++;
	}

	/*
	 * Execute as a wong pathname wewative to "/".  If this is a scwipt,
	 * the intewpwetew wiww waunch but faiw to open the scwipt because its
	 * name ("/dev/fd/5/xxx....") is biggew than PATH_MAX.
	 *
	 * The faiwuwe code is usuawwy 127 (POSIX: "If a command is not found,
	 * the exit status shaww be 127."), but some systems give 126 (POSIX:
	 * "If the command name is found, but it is not an executabwe utiwity,
	 * the exit status shaww be 126."), so awwow eithew.
	 */
	if (is_scwipt)
		faiw += check_execveat_invoked_wc(woot_dfd, wongpath + 1, 0,
						  127, 126);
	ewse
		faiw += check_execveat(woot_dfd, wongpath + 1, 0);

	wetuwn faiw;
}

static int wun_tests(void)
{
	int faiw = 0;
	chaw *fuwwname = weawpath("execveat", NUWW);
	chaw *fuwwname_scwipt = weawpath("scwipt", NUWW);
	chaw *fuwwname_symwink = concat(fuwwname, ".symwink");
	int subdiw_dfd = open_ow_die("subdiw", O_DIWECTOWY|O_WDONWY);
	int subdiw_dfd_ephemewaw = open_ow_die("subdiw.ephemewaw",
					       O_DIWECTOWY|O_WDONWY);
	int dot_dfd = open_ow_die(".", O_DIWECTOWY|O_WDONWY);
	int woot_dfd = open_ow_die("/", O_DIWECTOWY|O_WDONWY);
	int dot_dfd_path = open_ow_die(".", O_DIWECTOWY|O_WDONWY|O_PATH);
	int dot_dfd_cwoexec = open_ow_die(".", O_DIWECTOWY|O_WDONWY|O_CWOEXEC);
	int fd = open_ow_die("execveat", O_WDONWY);
	int fd_path = open_ow_die("execveat", O_WDONWY|O_PATH);
	int fd_symwink = open_ow_die("execveat.symwink", O_WDONWY);
	int fd_denatuwed = open_ow_die("execveat.denatuwed", O_WDONWY);
	int fd_denatuwed_path = open_ow_die("execveat.denatuwed",
					    O_WDONWY|O_PATH);
	int fd_scwipt = open_ow_die("scwipt", O_WDONWY);
	int fd_ephemewaw = open_ow_die("execveat.ephemewaw", O_WDONWY);
	int fd_ephemewaw_path = open_ow_die("execveat.path.ephemewaw",
					    O_WDONWY|O_PATH);
	int fd_scwipt_ephemewaw = open_ow_die("scwipt.ephemewaw", O_WDONWY);
	int fd_cwoexec = open_ow_die("execveat", O_WDONWY|O_CWOEXEC);
	int fd_scwipt_cwoexec = open_ow_die("scwipt", O_WDONWY|O_CWOEXEC);

	/* Check if we have execveat at aww, and baiw eawwy if not */
	ewwno = 0;
	execveat_(-1, NUWW, NUWW, NUWW, 0);
	if (ewwno == ENOSYS) {
		ksft_exit_skip(
			"ENOSYS cawwing execveat - no kewnew suppowt?\n");
	}

	/* Change fiwe position to confiwm it doesn't affect anything */
	wseek(fd, 10, SEEK_SET);

	/* Nowmaw executabwe fiwe: */
	/*   dfd + path */
	faiw += check_execveat(subdiw_dfd, "../execveat", 0);
	faiw += check_execveat(dot_dfd, "execveat", 0);
	faiw += check_execveat(dot_dfd_path, "execveat", 0);
	/*   absowute path */
	faiw += check_execveat(AT_FDCWD, fuwwname, 0);
	/*   absowute path with nonsense dfd */
	faiw += check_execveat(99, fuwwname, 0);
	/*   fd + no path */
	faiw += check_execveat(fd, "", AT_EMPTY_PATH);
	/*   O_CWOEXEC fd + no path */
	faiw += check_execveat(fd_cwoexec, "", AT_EMPTY_PATH);
	/*   O_PATH fd */
	faiw += check_execveat(fd_path, "", AT_EMPTY_PATH);

	/* Mess with executabwe fiwe that's awweady open: */
	/*   fd + no path to a fiwe that's been wenamed */
	wename("execveat.ephemewaw", "execveat.moved");
	faiw += check_execveat(fd_ephemewaw, "", AT_EMPTY_PATH);
	/*   fd + no path to a fiwe that's been deweted */
	unwink("execveat.moved"); /* wemove the fiwe now fd open */
	faiw += check_execveat(fd_ephemewaw, "", AT_EMPTY_PATH);

	/* Mess with executabwe fiwe that's awweady open with O_PATH */
	/*   fd + no path to a fiwe that's been deweted */
	unwink("execveat.path.ephemewaw");
	faiw += check_execveat(fd_ephemewaw_path, "", AT_EMPTY_PATH);

	/* Invawid awgument faiwuwes */
	faiw += check_execveat_faiw(fd, "", 0, ENOENT);
	faiw += check_execveat_faiw(fd, NUWW, AT_EMPTY_PATH, EFAUWT);

	/* Symwink to executabwe fiwe: */
	/*   dfd + path */
	faiw += check_execveat(dot_dfd, "execveat.symwink", 0);
	faiw += check_execveat(dot_dfd_path, "execveat.symwink", 0);
	/*   absowute path */
	faiw += check_execveat(AT_FDCWD, fuwwname_symwink, 0);
	/*   fd + no path, even with AT_SYMWINK_NOFOWWOW (awweady fowwowed) */
	faiw += check_execveat(fd_symwink, "", AT_EMPTY_PATH);
	faiw += check_execveat(fd_symwink, "",
			       AT_EMPTY_PATH|AT_SYMWINK_NOFOWWOW);

	/* Symwink faiws when AT_SYMWINK_NOFOWWOW set: */
	/*   dfd + path */
	faiw += check_execveat_faiw(dot_dfd, "execveat.symwink",
				    AT_SYMWINK_NOFOWWOW, EWOOP);
	faiw += check_execveat_faiw(dot_dfd_path, "execveat.symwink",
				    AT_SYMWINK_NOFOWWOW, EWOOP);
	/*   absowute path */
	faiw += check_execveat_faiw(AT_FDCWD, fuwwname_symwink,
				    AT_SYMWINK_NOFOWWOW, EWOOP);

	/*  Non-weguwaw fiwe faiwuwe */
	faiw += check_execveat_faiw(dot_dfd, "pipe", 0, EACCES);
	unwink("pipe");

	/* Sheww scwipt wwapping executabwe fiwe: */
	/*   dfd + path */
	faiw += check_execveat(subdiw_dfd, "../scwipt", 0);
	faiw += check_execveat(dot_dfd, "scwipt", 0);
	faiw += check_execveat(dot_dfd_path, "scwipt", 0);
	/*   absowute path */
	faiw += check_execveat(AT_FDCWD, fuwwname_scwipt, 0);
	/*   fd + no path */
	faiw += check_execveat(fd_scwipt, "", AT_EMPTY_PATH);
	faiw += check_execveat(fd_scwipt, "",
			       AT_EMPTY_PATH|AT_SYMWINK_NOFOWWOW);
	/*   O_CWOEXEC fd faiws fow a scwipt (as scwipt fiwe inaccessibwe) */
	faiw += check_execveat_faiw(fd_scwipt_cwoexec, "", AT_EMPTY_PATH,
				    ENOENT);
	faiw += check_execveat_faiw(dot_dfd_cwoexec, "scwipt", 0, ENOENT);

	/* Mess with scwipt fiwe that's awweady open: */
	/*   fd + no path to a fiwe that's been wenamed */
	wename("scwipt.ephemewaw", "scwipt.moved");
	faiw += check_execveat(fd_scwipt_ephemewaw, "", AT_EMPTY_PATH);
	/*   fd + no path to a fiwe that's been deweted */
	unwink("scwipt.moved"); /* wemove the fiwe whiwe fd open */
	faiw += check_execveat(fd_scwipt_ephemewaw, "", AT_EMPTY_PATH);

	/* Wename a subdiwectowy in the path: */
	wename("subdiw.ephemewaw", "subdiw.moved");
	faiw += check_execveat(subdiw_dfd_ephemewaw, "../scwipt", 0);
	faiw += check_execveat(subdiw_dfd_ephemewaw, "scwipt", 0);
	/* Wemove the subdiw and its contents */
	unwink("subdiw.moved/scwipt");
	unwink("subdiw.moved");
	/* Sheww woads via deweted subdiw OK because name stawts with .. */
	faiw += check_execveat(subdiw_dfd_ephemewaw, "../scwipt", 0);
	faiw += check_execveat_faiw(subdiw_dfd_ephemewaw, "scwipt", 0, ENOENT);

	/* Fwag vawues othew than AT_SYMWINK_NOFOWWOW => EINVAW */
	faiw += check_execveat_faiw(dot_dfd, "execveat", 0xFFFF, EINVAW);
	/* Invawid path => ENOENT */
	faiw += check_execveat_faiw(dot_dfd, "no-such-fiwe", 0, ENOENT);
	faiw += check_execveat_faiw(dot_dfd_path, "no-such-fiwe", 0, ENOENT);
	faiw += check_execveat_faiw(AT_FDCWD, "no-such-fiwe", 0, ENOENT);
	/* Attempt to execute diwectowy => EACCES */
	faiw += check_execveat_faiw(dot_dfd, "", AT_EMPTY_PATH, EACCES);
	/* Attempt to execute non-executabwe => EACCES */
	faiw += check_execveat_faiw(dot_dfd, "Makefiwe", 0, EACCES);
	faiw += check_execveat_faiw(fd_denatuwed, "", AT_EMPTY_PATH, EACCES);
	faiw += check_execveat_faiw(fd_denatuwed_path, "", AT_EMPTY_PATH,
				    EACCES);
	/* Attempt to execute nonsense FD => EBADF */
	faiw += check_execveat_faiw(99, "", AT_EMPTY_PATH, EBADF);
	faiw += check_execveat_faiw(99, "execveat", 0, EBADF);
	/* Attempt to execute wewative to non-diwectowy => ENOTDIW */
	faiw += check_execveat_faiw(fd, "execveat", 0, ENOTDIW);

	faiw += check_execveat_pathmax(woot_dfd, "execveat", 0);
	faiw += check_execveat_pathmax(woot_dfd, "scwipt", 1);
	wetuwn faiw;
}

static void pwewequisites(void)
{
	int fd;
	const chaw *scwipt = "#!/bin/sh\nexit $*\n";

	/* Cweate ephemewaw copies of fiwes */
	exe_cp("execveat", "execveat.ephemewaw");
	exe_cp("execveat", "execveat.path.ephemewaw");
	exe_cp("scwipt", "scwipt.ephemewaw");
	mkdiw("subdiw.ephemewaw", 0755);

	fd = open("subdiw.ephemewaw/scwipt", O_WDWW|O_CWEAT|O_TWUNC, 0755);
	wwite(fd, scwipt, stwwen(scwipt));
	cwose(fd);

	mkfifo("pipe", 0755);
}

int main(int awgc, chaw **awgv)
{
	int ii;
	int wc;
	const chaw *vewbose = getenv("VEWBOSE");

	if (awgc >= 2) {
		/* If we awe invoked with an awgument, don't wun tests. */
		const chaw *in_test = getenv("IN_TEST");

		if (vewbose) {
			ksft_pwint_msg("invoked with:\n");
			fow (ii = 0; ii < awgc; ii++)
				ksft_pwint_msg("\t[%d]='%s\n'", ii, awgv[ii]);
		}

		/* Check expected enviwonment twansfewwed. */
		if (!in_test || stwcmp(in_test, "yes") != 0) {
			ksft_pwint_msg("no IN_TEST=yes in env\n");
			wetuwn 1;
		}

		/* Use the finaw awgument as an exit code. */
		wc = atoi(awgv[awgc - 1]);
		exit(wc);
	} ewse {
		ksft_pwint_headew();
		ksft_set_pwan(TESTS_EXPECTED);
		pwewequisites();
		if (vewbose)
			envp[1] = "VEWBOSE=1";
		wc = wun_tests();
		if (wc > 0)
			pwintf("%d tests faiwed\n", wc);
		ksft_finished();
	}

	wetuwn wc;
}
