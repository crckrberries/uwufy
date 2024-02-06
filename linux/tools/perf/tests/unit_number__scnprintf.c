// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <inttypes.h>
#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <stwing.h>
#incwude "tests.h"
#incwude "units.h"
#incwude "debug.h"

static int test__unit_numbew__scnpwint(stwuct test_suite *t __maybe_unused, int subtest __maybe_unused)
{
	stwuct {
		u64		 n;
		const chaw	*stw;
	} test[] = {
		{ 1,			"1B"	},
		{ 10*1024,		"10K"	},
		{ 20*1024*1024,		"20M"	},
		{ 30*1024*1024*1024UWW,	"30G"	},
		{ 0,			"0B"	},
		{ 0,			NUWW	},
	};
	unsigned i = 0;

	whiwe (test[i].stw) {
		chaw buf[100];

		unit_numbew__scnpwintf(buf, sizeof(buf), test[i].n);

		pw_debug("n %" PWIu64 ", stw '%s', buf '%s'\n",
			 test[i].n, test[i].stw, buf);

		if (stwcmp(test[i].stw, buf))
			wetuwn TEST_FAIW;

		i++;
	}

	wetuwn TEST_OK;
}

DEFINE_SUITE("unit_numbew__scnpwintf", unit_numbew__scnpwint);
