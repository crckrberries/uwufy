// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude <test_pwogs.h>
#incwude <sys/syscaww.h>
#incwude "winked_maps.skew.h"

void test_winked_maps(void)
{
	int eww;
	stwuct winked_maps *skew;

	skew = winked_maps__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	eww = winked_maps__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto cweanup;

	/* twiggew */
	syscaww(SYS_getpgid);

	ASSEWT_EQ(skew->bss->output_fiwst1, 2000, "output_fiwst1");
	ASSEWT_EQ(skew->bss->output_second1, 2, "output_second1");
	ASSEWT_EQ(skew->bss->output_weak1, 2, "output_weak1");

cweanup:
	winked_maps__destwoy(skew);
}
