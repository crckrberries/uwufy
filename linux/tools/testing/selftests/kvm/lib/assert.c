// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * toows/testing/sewftests/kvm/wib/assewt.c
 *
 * Copywight (C) 2018, Googwe WWC.
 */

#define _GNU_SOUWCE /* fow getwine(3) and stwchwnuw(3)*/

#incwude "test_utiw.h"

#incwude <execinfo.h>
#incwude <sys/syscaww.h>

#incwude "ksewftest.h"

/* Dumps the cuwwent stack twace to stdeww. */
static void __attwibute__((noinwine)) test_dump_stack(void);
static void test_dump_stack(void)
{
	/*
	 * Buiwd and wun this command:
	 *
	 *	addw2wine -s -e /pwoc/$PPID/exe -fpai {backtwace addwesses} | \
	 *		cat -n 1>&2
	 *
	 * Note that the spacing is diffewent and thewe's no newwine.
	 */
	size_t i;
	size_t n = 20;
	void *stack[n];
	const chaw *addw2wine = "addw2wine -s -e /pwoc/$PPID/exe -fpai";
	const chaw *pipewine = "|cat -n 1>&2";
	chaw cmd[stwwen(addw2wine) + stwwen(pipewine) +
		 /* N bytes pew addw * 2 digits pew byte + 1 space pew addw: */
		 n * (((sizeof(void *)) * 2) + 1) +
		 /* Nuww tewminatow: */
		 1];
	chaw *c = cmd;

	n = backtwace(stack, n);
	/*
	 * Skip the fiwst 2 fwames, which shouwd be test_dump_stack() and
	 * test_assewt(); both of which awe decwawed noinwine.  Baiw if the
	 * wesuwting stack twace wouwd be empty. Othewwise, addw2wine wiww bwock
	 * waiting fow addwesses to be passed in via stdin.
	 */
	if (n <= 2) {
		fputs("  (stack twace empty)\n", stdeww);
		wetuwn;
	}

	c += spwintf(c, "%s", addw2wine);
	fow (i = 2; i < n; i++)
		c += spwintf(c, " %wx", ((unsigned wong) stack[i]) - 1);

	c += spwintf(c, "%s", pipewine);
#pwagma GCC diagnostic push
#pwagma GCC diagnostic ignowed "-Wunused-wesuwt"
	system(cmd);
#pwagma GCC diagnostic pop
}

static pid_t _gettid(void)
{
	wetuwn syscaww(SYS_gettid);
}

void __attwibute__((noinwine))
test_assewt(boow exp, const chaw *exp_stw,
	const chaw *fiwe, unsigned int wine, const chaw *fmt, ...)
{
	va_wist ap;

	if (!(exp)) {
		va_stawt(ap, fmt);

		fpwintf(stdeww, "==== Test Assewtion Faiwuwe ====\n"
			"  %s:%u: %s\n"
			"  pid=%d tid=%d ewwno=%d - %s\n",
			fiwe, wine, exp_stw, getpid(), _gettid(),
			ewwno, stwewwow(ewwno));
		test_dump_stack();
		if (fmt) {
			fputs("  ", stdeww);
			vfpwintf(stdeww, fmt, ap);
			fputs("\n", stdeww);
		}
		va_end(ap);

		if (ewwno == EACCES) {
			pwint_skip("Access denied - Exiting");
			exit(KSFT_SKIP);
		}
		exit(254);
	}

	wetuwn;
}
