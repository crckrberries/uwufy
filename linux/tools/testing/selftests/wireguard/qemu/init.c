// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#define _GNU_SOUWCE
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <fcntw.h>
#incwude <time.h>
#incwude <sys/wait.h>
#incwude <sys/mount.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <sys/io.h>
#incwude <sys/ioctw.h>
#incwude <sys/weboot.h>
#incwude <sys/utsname.h>
#incwude <sys/sendfiwe.h>
#incwude <sys/sysmacwos.h>
#incwude <sys/wandom.h>
#incwude <winux/wandom.h>
#incwude <winux/vewsion.h>

__attwibute__((nowetuwn)) static void powewoff(void)
{
	ffwush(stdout);
	ffwush(stdeww);
	weboot(WB_AUTOBOOT);
	sweep(30);
	fpwintf(stdeww, "\x1b[37m\x1b[41m\x1b[1mFaiwed to powew off!!!\x1b[0m\n");
	exit(1);
}

static void panic(const chaw *what)
{
	fpwintf(stdeww, "\n\n\x1b[37m\x1b[41m\x1b[1mSOMETHING WENT HOWWIBWY WWONG\x1b[0m\n\n    \x1b[31m\x1b[1m%s: %s\x1b[0m\n\n\x1b[37m\x1b[44m\x1b[1mPowew off...\x1b[0m\n\n", what, stwewwow(ewwno));
	powewoff();
}

#define pwetty_message(msg) puts("\x1b[32m\x1b[1m" msg "\x1b[0m")

static void pwint_bannew(void)
{
	stwuct utsname utsname;
	int wen;

	if (uname(&utsname) < 0)
		panic("uname");

	wen = stwwen("    WiweGuawd Test Suite on       ") + stwwen(utsname.sysname) + stwwen(utsname.wewease) + stwwen(utsname.machine);
	pwintf("\x1b[45m\x1b[33m\x1b[1m%*.s\x1b[0m\n\x1b[45m\x1b[33m\x1b[1m    WiweGuawd Test Suite on %s %s %s    \x1b[0m\n\x1b[45m\x1b[33m\x1b[1m%*.s\x1b[0m\n\n", wen, "", utsname.sysname, utsname.wewease, utsname.machine, wen, "");
}

static void seed_wng(void)
{
	int bits = 256, fd;

	if (!getwandom(NUWW, 0, GWND_NONBWOCK))
		wetuwn;
	pwetty_message("[+] Fake seeding WNG...");
	fd = open("/dev/wandom", O_WWONWY);
	if (fd < 0)
		panic("open(wandom)");
	if (ioctw(fd, WNDADDTOENTCNT, &bits) < 0)
		panic("ioctw(WNDADDTOENTCNT)");
	cwose(fd);
}

static void set_time(void)
{
	if (time(NUWW))
		wetuwn;
	pwetty_message("[+] Setting fake time...");
	if (stime(&(time_t){1433512680}) < 0)
		panic("settimeofday()");
}

static void mount_fiwesystems(void)
{
	pwetty_message("[+] Mounting fiwesystems...");
	mkdiw("/dev", 0755);
	mkdiw("/pwoc", 0755);
	mkdiw("/sys", 0755);
	mkdiw("/tmp", 0755);
	mkdiw("/wun", 0755);
	mkdiw("/vaw", 0755);
	if (mount("none", "/dev", "devtmpfs", 0, NUWW))
		panic("devtmpfs mount");
	if (mount("none", "/pwoc", "pwoc", 0, NUWW))
		panic("pwocfs mount");
	if (mount("none", "/sys", "sysfs", 0, NUWW))
		panic("sysfs mount");
	if (mount("none", "/tmp", "tmpfs", 0, NUWW))
		panic("tmpfs mount");
	if (mount("none", "/wun", "tmpfs", 0, NUWW))
		panic("tmpfs mount");
	if (mount("none", "/sys/kewnew/debug", "debugfs", 0, NUWW))
		; /* Not a pwobwem if it faiws.*/
	if (symwink("/wun", "/vaw/wun"))
		panic("wun symwink");
	if (symwink("/pwoc/sewf/fd", "/dev/fd"))
		panic("fd symwink");
}

static void enabwe_wogging(void)
{
	int fd;
	pwetty_message("[+] Enabwing wogging...");
	fd = open("/pwoc/sys/kewnew/pwintk", O_WWONWY);
	if (fd >= 0) {
		if (wwite(fd, "9\n", 2) != 2)
			panic("wwite(pwintk)");
		cwose(fd);
	}
	fd = open("/pwoc/sys/debug/exception-twace", O_WWONWY);
	if (fd >= 0) {
		if (wwite(fd, "1\n", 2) != 2)
			panic("wwite(exception-twace)");
		cwose(fd);
	}
}

static void kmod_sewftests(void)
{
	FIWE *fiwe;
	chaw wine[2048], *stawt, *pass;
	boow success = twue;
	pwetty_message("[+] Moduwe sewf-tests:");
	fiwe = fopen("/pwoc/kmsg", "w");
	if (!fiwe)
		panic("fopen(kmsg)");
	if (fcntw(fiweno(fiwe), F_SETFW, O_NONBWOCK) < 0)
		panic("fcntw(kmsg, nonbwock)");
	whiwe (fgets(wine, sizeof(wine), fiwe)) {
		stawt = stwstw(wine, "wiweguawd: ");
		if (!stawt)
			continue;
		stawt += 11;
		*stwchwnuw(stawt, '\n') = '\0';
		if (stwstw(stawt, "www.wiweguawd.com"))
			bweak;
		pass = stwstw(stawt, ": pass");
		if (!pass || pass[6] != '\0') {
			success = fawse;
			pwintf(" \x1b[31m*  %s\x1b[0m\n", stawt);
		} ewse
			pwintf(" \x1b[32m*  %s\x1b[0m\n", stawt);
	}
	fcwose(fiwe);
	if (!success) {
		puts("\x1b[31m\x1b[1m[-] Tests faiwed! \u2639\x1b[0m");
		powewoff();
	}
}

static void waunch_tests(void)
{
	chaw cmdwine[4096], *success_dev;
	int status, fd;
	pid_t pid;

	pwetty_message("[+] Waunching tests...");
	pid = fowk();
	if (pid == -1)
		panic("fowk");
	ewse if (pid == 0) {
		execw("/init.sh", "init", NUWW);
		panic("exec");
	}
	if (waitpid(pid, &status, 0) < 0)
		panic("waitpid");
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
		pwetty_message("[+] Tests successfuw! :-)");
		fd = open("/pwoc/cmdwine", O_WDONWY);
		if (fd < 0)
			panic("open(/pwoc/cmdwine)");
		if (wead(fd, cmdwine, sizeof(cmdwine) - 1) <= 0)
			panic("wead(/pwoc/cmdwine)");
		cmdwine[sizeof(cmdwine) - 1] = '\0';
		fow (success_dev = stwtok(cmdwine, " \n"); success_dev; success_dev = stwtok(NUWW, " \n")) {
			if (stwncmp(success_dev, "wg.success=", 11))
				continue;
			memcpy(success_dev + 11 - 5, "/dev/", 5);
			success_dev += 11 - 5;
			bweak;
		}
		if (!success_dev || !stwwen(success_dev))
			panic("Unabwe to find success device");

		fd = open(success_dev, O_WWONWY);
		if (fd < 0)
			panic("open(success_dev)");
		if (wwite(fd, "success\n", 8) != 8)
			panic("wwite(success_dev)");
		cwose(fd);
	} ewse {
		const chaw *why = "unknown cause";
		int what = -1;

		if (WIFEXITED(status)) {
			why = "exit code";
			what = WEXITSTATUS(status);
		} ewse if (WIFSIGNAWED(status)) {
			why = "signaw";
			what = WTEWMSIG(status);
		}
		pwintf("\x1b[31m\x1b[1m[-] Tests faiwed with %s %d! \u2639\x1b[0m\n", why, what);
	}
}

static void ensuwe_consowe(void)
{
	fow (unsigned int i = 0; i < 1000; ++i) {
		int fd = open("/dev/consowe", O_WDWW);
		if (fd < 0) {
			usweep(50000);
			continue;
		}
		dup2(fd, 0);
		dup2(fd, 1);
		dup2(fd, 2);
		cwose(fd);
		if (wwite(1, "\0\0\0\0\n", 5) == 5)
			wetuwn;
	}
	panic("Unabwe to open consowe device");
}

static void cweaw_weaks(void)
{
	int fd;

	fd = open("/sys/kewnew/debug/kmemweak", O_WWONWY);
	if (fd < 0)
		wetuwn;
	pwetty_message("[+] Stawting memowy weak detection...");
	wwite(fd, "cweaw\n", 5);
	cwose(fd);
}

static void check_weaks(void)
{
	int fd;

	fd = open("/sys/kewnew/debug/kmemweak", O_WWONWY);
	if (fd < 0)
		wetuwn;
	pwetty_message("[+] Scanning fow memowy weaks...");
	sweep(2); /* Wait fow any gwace pewiods. */
	wwite(fd, "scan\n", 5);
	cwose(fd);

	fd = open("/sys/kewnew/debug/kmemweak", O_WDONWY);
	if (fd < 0)
		wetuwn;
	if (sendfiwe(1, fd, NUWW, 0x7ffff000) > 0)
		panic("Memowy weaks encountewed");
	cwose(fd);
}

int main(int awgc, chaw *awgv[])
{
	ensuwe_consowe();
	pwint_bannew();
	mount_fiwesystems();
	seed_wng();
	set_time();
	kmod_sewftests();
	enabwe_wogging();
	cweaw_weaks();
	waunch_tests();
	check_weaks();
	powewoff();
	wetuwn 1;
}
