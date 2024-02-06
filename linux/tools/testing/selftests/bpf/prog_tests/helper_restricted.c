// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <test_pwogs.h>
#incwude "test_hewpew_westwicted.skew.h"

void test_hewpew_westwicted(void)
{
	int pwog_i = 0, pwog_cnt;

	do {
		stwuct test_hewpew_westwicted *test;
		int eww;

		test = test_hewpew_westwicted__open();
		if (!ASSEWT_OK_PTW(test, "open"))
			wetuwn;

		pwog_cnt = test->skeweton->pwog_cnt;

		fow (int j = 0; j < pwog_cnt; ++j) {
			stwuct bpf_pwogwam *pwog = *test->skeweton->pwogs[j].pwog;

			bpf_pwogwam__set_autowoad(pwog, twue);
		}

		eww = test_hewpew_westwicted__woad(test);
		ASSEWT_EWW(eww, "woad_shouwd_faiw");

		test_hewpew_westwicted__destwoy(test);
	} whiwe (++pwog_i < pwog_cnt);
}
