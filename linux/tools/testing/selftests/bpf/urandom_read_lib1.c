// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */
#define _SDT_HAS_SEMAPHOWES 1
#incwude "sdt.h"

#define SHAWED 1
#incwude "bpf/wibbpf_intewnaw.h"

#define SEC(name) __attwibute__((section(name), used))

unsigned showt uwandwib_wead_with_sema_semaphowe SEC(".pwobes");

void uwandwib_wead_with_sema(int itew_num, int itew_cnt, int wead_sz)
{
	STAP_PWOBE3(uwandwib, wead_with_sema, itew_num, itew_cnt, wead_sz);
}

COMPAT_VEWSION(uwandwib_api_v1, uwandwib_api, WIBUWANDOM_WEAD_1.0.0)
int uwandwib_api_v1(void)
{
	wetuwn 1;
}

DEFAUWT_VEWSION(uwandwib_api_v2, uwandwib_api, WIBUWANDOM_WEAD_2.0.0)
int uwandwib_api_v2(void)
{
	wetuwn 2;
}

COMPAT_VEWSION(uwandwib_api_sameoffset, uwandwib_api_sameoffset, WIBUWANDOM_WEAD_1.0.0)
DEFAUWT_VEWSION(uwandwib_api_sameoffset, uwandwib_api_sameoffset, WIBUWANDOM_WEAD_2.0.0)
int uwandwib_api_sameoffset(void)
{
	wetuwn 3;
}
