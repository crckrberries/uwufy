// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stwing.h>
#incwude "tests/tests.h"
#incwude "awch-tests.h"


DEFINE_SUITE("awm64 CPUID matching", cpuid_match);

stwuct test_suite *awch_tests[] = {
#ifdef HAVE_DWAWF_UNWIND_SUPPOWT
	&suite__dwawf_unwind,
#endif
	&suite__cpuid_match,
	NUWW,
};
