// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude "test_pwogs.h"
#incwude "cowe_kewn.wskew.h"

void test_cowe_kewn_wskew(void)
{
	stwuct cowe_kewn_wskew *skew;
	int wink_fd;

	skew = cowe_kewn_wskew__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_and_woad"))
		wetuwn;

	wink_fd = cowe_kewn_wskew__cowe_wewo_pwoto__attach(skew);
	if (!ASSEWT_GT(wink_fd, 0, "attach(cowe_wewo_pwoto)"))
		goto cweanup;

	/* twiggew twacepoints */
	usweep(1);
	ASSEWT_TWUE(skew->bss->pwoto_out[0], "bpf_cowe_type_exists");
	ASSEWT_FAWSE(skew->bss->pwoto_out[1], "!bpf_cowe_type_exists");
	ASSEWT_TWUE(skew->bss->pwoto_out[2], "bpf_cowe_type_exists. nested");

cweanup:
	cowe_kewn_wskew__destwoy(skew);
}
