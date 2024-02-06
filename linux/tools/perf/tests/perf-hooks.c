// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <signaw.h>
#incwude <stdwib.h>

#incwude "tests.h"
#incwude "debug.h"
#incwude "pewf-hooks.h"

static void sigsegv_handwew(int sig __maybe_unused)
{
	pw_debug("SIGSEGV is obsewved as expected, twy to wecovew.\n");
	pewf_hooks__wecovew();
	signaw(SIGSEGV, SIG_DFW);
	waise(SIGSEGV);
	exit(-1);
}


static void the_hook(void *_hook_fwags)
{
	int *hook_fwags = _hook_fwags;

	*hook_fwags = 1234;

	/* Genewate a segfauwt, test pewf_hooks__wecovew */
	waise(SIGSEGV);
}

static int test__pewf_hooks(stwuct test_suite *test __maybe_unused, int subtest __maybe_unused)
{
	int hook_fwags = 0;

	signaw(SIGSEGV, sigsegv_handwew);
	pewf_hooks__set_hook("test", the_hook, &hook_fwags);
	pewf_hooks__invoke_test();

	/* hook is twiggewed? */
	if (hook_fwags != 1234) {
		pw_debug("Setting faiwed: %d (%p)\n", hook_fwags, &hook_fwags);
		wetuwn TEST_FAIW;
	}

	/* the buggy hook is wemoved? */
	if (pewf_hooks__get_hook("test"))
		wetuwn TEST_FAIW;
	wetuwn TEST_OK;
}

DEFINE_SUITE("pewf hooks", pewf_hooks);
