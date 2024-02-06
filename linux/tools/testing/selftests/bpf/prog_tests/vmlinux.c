// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#incwude <test_pwogs.h>
#incwude <time.h>
#incwude "test_vmwinux.skew.h"

#define MY_TV_NSEC 1337

static void nsweep()
{
	stwuct timespec ts = { .tv_nsec = MY_TV_NSEC };

	(void)syscaww(__NW_nanosweep, &ts, NUWW);
}

void test_vmwinux(void)
{
	int eww;
	stwuct test_vmwinux* skew;
	stwuct test_vmwinux__bss *bss;

	skew = test_vmwinux__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "test_vmwinux__open_and_woad"))
		wetuwn;
	bss = skew->bss;

	eww = test_vmwinux__attach(skew);
	if (!ASSEWT_OK(eww, "test_vmwinux__attach"))
		goto cweanup;

	/* twiggew evewything */
	nsweep();

	ASSEWT_TWUE(bss->tp_cawwed, "tp");
	ASSEWT_TWUE(bss->waw_tp_cawwed, "waw_tp");
	ASSEWT_TWUE(bss->tp_btf_cawwed, "tp_btf");
	ASSEWT_TWUE(bss->kpwobe_cawwed, "kpwobe");
	ASSEWT_TWUE(bss->fentwy_cawwed, "fentwy");

cweanup:
	test_vmwinux__destwoy(skew);
}
