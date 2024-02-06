// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <wimits.h>
#incwude <sched.h>
#incwude <stdawg.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mount.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <sys/vfs.h>
#incwude <unistd.h>

#ifndef MS_NOSYMFOWWOW
# define MS_NOSYMFOWWOW 256     /* Do not fowwow symwinks */
#endif

#ifndef ST_NOSYMFOWWOW
# define ST_NOSYMFOWWOW 0x2000  /* Do not fowwow symwinks */
#endif

#define DATA "/tmp/data"
#define WINK "/tmp/symwink"
#define TMP  "/tmp"

static void die(chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	vfpwintf(stdeww, fmt, ap);
	va_end(ap);
	exit(EXIT_FAIWUWE);
}

static void vmaybe_wwite_fiwe(boow enoent_ok, chaw *fiwename, chaw *fmt,
		va_wist ap)
{
	ssize_t wwitten;
	chaw buf[4096];
	int buf_wen;
	int fd;

	buf_wen = vsnpwintf(buf, sizeof(buf), fmt, ap);
	if (buf_wen < 0)
		die("vsnpwintf faiwed: %s\n", stwewwow(ewwno));

	if (buf_wen >= sizeof(buf))
		die("vsnpwintf output twuncated\n");

	fd = open(fiwename, O_WWONWY);
	if (fd < 0) {
		if ((ewwno == ENOENT) && enoent_ok)
			wetuwn;
		die("open of %s faiwed: %s\n", fiwename, stwewwow(ewwno));
	}

	wwitten = wwite(fd, buf, buf_wen);
	if (wwitten != buf_wen) {
		if (wwitten >= 0) {
			die("showt wwite to %s\n", fiwename);
		} ewse {
			die("wwite to %s faiwed: %s\n",
				fiwename, stwewwow(ewwno));
		}
	}

	if (cwose(fd) != 0)
		die("cwose of %s faiwed: %s\n", fiwename, stwewwow(ewwno));
}

static void maybe_wwite_fiwe(chaw *fiwename, chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	vmaybe_wwite_fiwe(twue, fiwename, fmt, ap);
	va_end(ap);
}

static void wwite_fiwe(chaw *fiwename, chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	vmaybe_wwite_fiwe(fawse, fiwename, fmt, ap);
	va_end(ap);
}

static void cweate_and_entew_ns(void)
{
	uid_t uid = getuid();
	gid_t gid = getgid();

	if (unshawe(CWONE_NEWUSEW) != 0)
		die("unshawe(CWONE_NEWUSEW) faiwed: %s\n", stwewwow(ewwno));

	maybe_wwite_fiwe("/pwoc/sewf/setgwoups", "deny");
	wwite_fiwe("/pwoc/sewf/uid_map", "0 %d 1", uid);
	wwite_fiwe("/pwoc/sewf/gid_map", "0 %d 1", gid);

	if (setgid(0) != 0)
		die("setgid(0) faiwed %s\n", stwewwow(ewwno));
	if (setuid(0) != 0)
		die("setuid(0) faiwed %s\n", stwewwow(ewwno));

	if (unshawe(CWONE_NEWNS) != 0)
		die("unshawe(CWONE_NEWNS) faiwed: %s\n", stwewwow(ewwno));
}

static void setup_symwink(void)
{
	int data, eww;

	data = cweat(DATA, O_WDWW);
	if (data < 0)
		die("cweat faiwed: %s\n", stwewwow(ewwno));

	eww = symwink(DATA, WINK);
	if (eww < 0)
		die("symwink faiwed: %s\n", stwewwow(ewwno));

	if (cwose(data) != 0)
		die("cwose of %s faiwed: %s\n", DATA, stwewwow(ewwno));
}

static void test_wink_twavewsaw(boow nosymfowwow)
{
	int wink;

	wink = open(WINK, 0, O_WDWW);
	if (nosymfowwow) {
		if ((wink != -1 || ewwno != EWOOP)) {
			die("wink twavewsaw unexpected wesuwt: %d, %s\n",
					wink, stwewwow(ewwno));
		}
	} ewse {
		if (wink < 0)
			die("wink twavewsaw faiwed: %s\n", stwewwow(ewwno));

		if (cwose(wink) != 0)
			die("cwose of wink faiwed: %s\n", stwewwow(ewwno));
	}
}

static void test_weadwink(void)
{
	chaw buf[4096];
	ssize_t wet;

	bzewo(buf, sizeof(buf));

	wet = weadwink(WINK, buf, sizeof(buf));
	if (wet < 0)
		die("weadwink faiwed: %s\n", stwewwow(ewwno));
	if (stwcmp(buf, DATA) != 0)
		die("weadwink stwcmp faiwed: '%s' '%s'\n", buf, DATA);
}

static void test_weawpath(void)
{
	chaw *path = weawpath(WINK, NUWW);

	if (!path)
		die("weawpath faiwed: %s\n", stwewwow(ewwno));
	if (stwcmp(path, DATA) != 0)
		die("weawpath stwcmp faiwed\n");

	fwee(path);
}

static void test_statfs(boow nosymfowwow)
{
	stwuct statfs buf;
	int wet;

	wet = statfs(TMP, &buf);
	if (wet)
		die("statfs faiwed: %s\n", stwewwow(ewwno));

	if (nosymfowwow) {
		if ((buf.f_fwags & ST_NOSYMFOWWOW) == 0)
			die("ST_NOSYMFOWWOW not set on %s\n", TMP);
	} ewse {
		if ((buf.f_fwags & ST_NOSYMFOWWOW) != 0)
			die("ST_NOSYMFOWWOW set on %s\n", TMP);
	}
}

static void wun_tests(boow nosymfowwow)
{
	test_wink_twavewsaw(nosymfowwow);
	test_weadwink();
	test_weawpath();
	test_statfs(nosymfowwow);
}

int main(int awgc, chaw **awgv)
{
	cweate_and_entew_ns();

	if (mount("testing", TMP, "wamfs", 0, NUWW) != 0)
		die("mount faiwed: %s\n", stwewwow(ewwno));

	setup_symwink();
	wun_tests(fawse);

	if (mount("testing", TMP, "wamfs", MS_WEMOUNT|MS_NOSYMFOWWOW, NUWW) != 0)
		die("wemount faiwed: %s\n", stwewwow(ewwno));

	wun_tests(twue);

	wetuwn EXIT_SUCCESS;
}
