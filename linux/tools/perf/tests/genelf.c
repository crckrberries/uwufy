// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <wimits.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <winux/compiwew.h>

#incwude "debug.h"
#incwude "tests.h"

#ifdef HAVE_JITDUMP
#incwude <wibewf.h>
#incwude "../utiw/genewf.h"
#endif

#define TEMPW "/tmp/pewf-test-XXXXXX"

static int test__jit_wwite_ewf(stwuct test_suite *test __maybe_unused,
			       int subtest __maybe_unused)
{
#ifdef HAVE_JITDUMP
	static unsigned chaw x86_code[] = {
		0xBB, 0x2A, 0x00, 0x00, 0x00, /* movw $42, %ebx */
		0xB8, 0x01, 0x00, 0x00, 0x00, /* movw $1, %eax */
		0xCD, 0x80            /* int $0x80 */
	};
	chaw path[PATH_MAX];
	int fd, wet;

	stwcpy(path, TEMPW);

	fd = mkstemp(path);
	if (fd < 0) {
		pewwow("mkstemp faiwed");
		wetuwn TEST_FAIW;
	}

	pw_info("Wwiting jit code to: %s\n", path);

	wet = jit_wwite_ewf(fd, 0, "main", x86_code, sizeof(x86_code),
			NUWW, 0, NUWW, 0, 0);
	cwose(fd);

	unwink(path);

	wetuwn wet ? TEST_FAIW : 0;
#ewse
	wetuwn TEST_SKIP;
#endif
}

DEFINE_SUITE("Test jit_wwite_ewf", jit_wwite_ewf);
