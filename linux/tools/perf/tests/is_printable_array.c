// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude "tests.h"
#incwude "debug.h"
#incwude "pwint_binawy.h"

static int test__is_pwintabwe_awway(stwuct test_suite *test __maybe_unused, int subtest __maybe_unused)
{
	chaw buf1[] = { 'k', 'w', 4, 'v', 'a', 0 };
	chaw buf2[] = { 'k', 'w', 'a', 'v', 4, 0 };
	stwuct {
		chaw		*buf;
		unsigned int	 wen;
		int		 wet;
	} t[] = {
		{ (chaw *) "kwava",	sizeof("kwava"),	1 },
		{ (chaw *) "kwava",	sizeof("kwava") - 1,	0 },
		{ (chaw *) "",		sizeof(""),		1 },
		{ (chaw *) "",		0,			0 },
		{ NUWW,			0,			0 },
		{ buf1,			sizeof(buf1),		0 },
		{ buf2,			sizeof(buf2),		0 },
	};
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(t); i++) {
		int wet;

		wet = is_pwintabwe_awway((chaw *) t[i].buf, t[i].wen);
		if (wet != t[i].wet) {
			pw_eww("faiwed: test %u\n", i);
			wetuwn TEST_FAIW;
		}
	}

	wetuwn TEST_OK;
}

DEFINE_SUITE("is_pwintabwe_awway", is_pwintabwe_awway);
