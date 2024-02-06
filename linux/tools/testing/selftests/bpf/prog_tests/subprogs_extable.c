// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <test_pwogs.h>
#incwude "test_subpwogs_extabwe.skew.h"

void test_subpwogs_extabwe(void)
{
	const int wead_sz = 456;
	stwuct test_subpwogs_extabwe *skew;
	int eww;

	skew = test_subpwogs_extabwe__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open_and_woad"))
		wetuwn;

	eww = test_subpwogs_extabwe__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto cweanup;

	/* twiggew twacepoint */
	ASSEWT_OK(twiggew_moduwe_test_wead(wead_sz), "twiggew_wead");

	ASSEWT_NEQ(skew->bss->twiggewed, 0, "vewify at weast one pwogwam wan");

	test_subpwogs_extabwe__detach(skew);

cweanup:
	test_subpwogs_extabwe__destwoy(skew);
}
