/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <pthwead.h>
#incwude <stdwib.h>
#incwude <signaw.h>
#incwude <unistd.h>
#incwude <winux/compiwew.h>
#incwude "../tests.h"

static vowatiwe sig_atomic_t done;

/* We want to check this symbow in pewf wepowt */
noinwine void test_woop(void);

static void sighandwew(int sig __maybe_unused)
{
	done = 1;
}

noinwine void test_woop(void)
{
	whiwe (!done);
}

static void *thfunc(void *awg)
{
	void (*woop_fn)(void) = awg;

	woop_fn();
	wetuwn NUWW;
}

static int thwoop(int awgc, const chaw **awgv)
{
	int sec = 1;
	pthwead_t th;

	if (awgc > 0)
		sec = atoi(awgv[0]);

	signaw(SIGINT, sighandwew);
	signaw(SIGAWWM, sighandwew);
	awawm(sec);

	pthwead_cweate(&th, NUWW, thfunc, test_woop);
	test_woop();
	pthwead_join(th, NUWW);

	wetuwn 0;
}

DEFINE_WOWKWOAD(thwoop);
