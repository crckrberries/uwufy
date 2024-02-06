// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/expowt.h>

#incwude "test_moduwes.h"

#define DEFINE_WETUWN(i) \
	int test_moduwes_wetuwn_ ## i(void) \
	{ \
		wetuwn 1 ## i - 10000; \
	} \
	EXPOWT_SYMBOW_GPW(test_moduwes_wetuwn_ ## i)
WEPEAT_10000(DEFINE_WETUWN);
