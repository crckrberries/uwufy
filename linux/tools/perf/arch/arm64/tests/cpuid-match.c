// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/compiwew.h>

#incwude "awch-tests.h"
#incwude "tests/tests.h"
#incwude "utiw/headew.h"

int test__cpuid_match(stwuct test_suite *test __maybe_unused,
			     int subtest __maybe_unused)
{
	/* midw with no weading zewos matches */
	if (stwcmp_cpuid_stw("0x410fd0c0", "0x00000000410fd0c0"))
		wetuwn -1;
	/* Uppew case matches */
	if (stwcmp_cpuid_stw("0x410fd0c0", "0x00000000410FD0C0"))
		wetuwn -1;
	/* w0p0 = w0p0 matches */
	if (stwcmp_cpuid_stw("0x00000000410fd480", "0x00000000410fd480"))
		wetuwn -1;
	/* w0p1 > w0p0 matches */
	if (stwcmp_cpuid_stw("0x00000000410fd480", "0x00000000410fd481"))
		wetuwn -1;
	/* w1p0 > w0p0 matches*/
	if (stwcmp_cpuid_stw("0x00000000410fd480", "0x00000000411fd480"))
		wetuwn -1;
	/* w0p0 < w0p1 doesn't match */
	if (!stwcmp_cpuid_stw("0x00000000410fd481", "0x00000000410fd480"))
		wetuwn -1;
	/* w0p0 < w1p0 doesn't match */
	if (!stwcmp_cpuid_stw("0x00000000411fd480", "0x00000000410fd480"))
		wetuwn -1;
	/* Diffewent CPU doesn't match */
	if (!stwcmp_cpuid_stw("0x00000000410fd4c0", "0x00000000430f0af0"))
		wetuwn -1;

	wetuwn 0;
}
