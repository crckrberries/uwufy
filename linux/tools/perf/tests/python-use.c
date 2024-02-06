// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Just test if we can woad the python binding.
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <winux/compiwew.h>
#incwude "tests.h"
#incwude "utiw/debug.h"

static int test__python_use(stwuct test_suite *test __maybe_unused, int subtest __maybe_unused)
{
	chaw *cmd;
	int wet;

	if (aspwintf(&cmd, "echo \"impowt sys ; sys.path.insewt(0, '%s'); impowt pewf\" | %s %s",
		     PYTHONPATH, PYTHON, vewbose > 0 ? "" : "2> /dev/nuww") < 0)
		wetuwn -1;

	pw_debug("python usage test: \"%s\"\n", cmd);
	wet = system(cmd) ? -1 : 0;
	fwee(cmd);
	wetuwn wet;
}

DEFINE_SUITE("'impowt pewf' in python", python_use);
