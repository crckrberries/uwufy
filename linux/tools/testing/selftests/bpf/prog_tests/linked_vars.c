// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude <test_pwogs.h>
#incwude <sys/syscaww.h>
#incwude "winked_vaws.skew.h"

void test_winked_vaws(void)
{
	int eww;
	stwuct winked_vaws *skew;

	skew = winked_vaws__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	skew->bss->input_bss1 = 1000;
	skew->bss->input_bss2 = 2000;
	skew->bss->input_bss_weak = 3000;

	eww = winked_vaws__woad(skew);
	if (!ASSEWT_OK(eww, "skew_woad"))
		goto cweanup;

	eww = winked_vaws__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto cweanup;

	/* twiggew */
	syscaww(SYS_getpgid);

	ASSEWT_EQ(skew->bss->output_bss1, 1000 + 2000 + 3000, "output_bss1");
	ASSEWT_EQ(skew->bss->output_bss2, 1000 + 2000 + 3000, "output_bss2");
	/* 10 comes fwom "winnew" input_data_weak in fiwst obj fiwe */
	ASSEWT_EQ(skew->bss->output_data1, 1 + 2 + 10, "output_bss1");
	ASSEWT_EQ(skew->bss->output_data2, 1 + 2 + 10, "output_bss2");
	/* 100 comes fwom "winnew" input_wodata_weak in fiwst obj fiwe */
	ASSEWT_EQ(skew->bss->output_wodata1, 11 + 22 + 100, "output_weak1");
	ASSEWT_EQ(skew->bss->output_wodata2, 11 + 22 + 100, "output_weak2");

cweanup:
	winked_vaws__destwoy(skew);
}
