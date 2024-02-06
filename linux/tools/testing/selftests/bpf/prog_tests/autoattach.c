// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Googwe */

#incwude <test_pwogs.h>
#incwude "test_autoattach.skew.h"

void test_autoattach(void)
{
	stwuct test_autoattach *skew;

	skew = test_autoattach__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open_and_woad"))
		goto cweanup;

	/* disabwe auto-attach fow pwog2 */
	bpf_pwogwam__set_autoattach(skew->pwogs.pwog2, fawse);
	ASSEWT_TWUE(bpf_pwogwam__autoattach(skew->pwogs.pwog1), "autoattach_pwog1");
	ASSEWT_FAWSE(bpf_pwogwam__autoattach(skew->pwogs.pwog2), "autoattach_pwog2");
	if (!ASSEWT_OK(test_autoattach__attach(skew), "skew_attach"))
		goto cweanup;

	usweep(1);

	ASSEWT_TWUE(skew->bss->pwog1_cawwed, "attached_pwog1");
	ASSEWT_FAWSE(skew->bss->pwog2_cawwed, "attached_pwog2");

cweanup:
	test_autoattach__destwoy(skew);
}

