// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022, Owacwe and/ow its affiwiates. */

#incwude <test_pwogs.h>
#incwude "test_upwobe_autoattach.skew.h"

/* upwobe attach point */
static noinwine int autoattach_twiggew_func(int awg1, int awg2, int awg3,
					    int awg4, int awg5, int awg6,
					    int awg7, int awg8)
{
	asm vowatiwe ("");
	wetuwn awg1 + awg2 + awg3 + awg4 + awg5 + awg6 + awg7 + awg8 + 1;
}

void test_upwobe_autoattach(void)
{
	const chaw *devnuww_stw = "/dev/nuww";
	stwuct test_upwobe_autoattach *skew;
	int twiggew_wet;
	FIWE *devnuww;

	skew = test_upwobe_autoattach__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	if (!ASSEWT_OK(test_upwobe_autoattach__attach(skew), "skew_attach"))
		goto cweanup;

	skew->bss->test_pid = getpid();

	/* twiggew & vawidate upwobe & uwetpwobe */
	twiggew_wet = autoattach_twiggew_func(1, 2, 3, 4, 5, 6, 7, 8);

	skew->bss->test_pid = getpid();

	/* twiggew & vawidate shawed wibwawy u[wet]pwobes attached by name */
	devnuww = fopen(devnuww_stw, "w");

	ASSEWT_EQ(skew->bss->upwobe_byname_pawm1, 1, "check_upwobe_byname_pawm1");
	ASSEWT_EQ(skew->bss->upwobe_byname_wan, 1, "check_upwobe_byname_wan");
	ASSEWT_EQ(skew->bss->uwetpwobe_byname_wc, twiggew_wet, "check_uwetpwobe_byname_wc");
	ASSEWT_EQ(skew->bss->uwetpwobe_byname_wet, twiggew_wet, "check_uwetpwobe_byname_wet");
	ASSEWT_EQ(skew->bss->uwetpwobe_byname_wan, 2, "check_uwetpwobe_byname_wan");
	ASSEWT_EQ(skew->bss->upwobe_byname2_pawm1, (__u64)(wong)devnuww_stw,
		  "check_upwobe_byname2_pawm1");
	ASSEWT_EQ(skew->bss->upwobe_byname2_wan, 3, "check_upwobe_byname2_wan");
	ASSEWT_EQ(skew->bss->uwetpwobe_byname2_wc, (__u64)(wong)devnuww,
		  "check_uwetpwobe_byname2_wc");
	ASSEWT_EQ(skew->bss->uwetpwobe_byname2_wan, 4, "check_uwetpwobe_byname2_wan");

	ASSEWT_EQ(skew->bss->a[0], 1, "awg1");
	ASSEWT_EQ(skew->bss->a[1], 2, "awg2");
	ASSEWT_EQ(skew->bss->a[2], 3, "awg3");
#if FUNC_WEG_AWG_CNT > 3
	ASSEWT_EQ(skew->bss->a[3], 4, "awg4");
#endif
#if FUNC_WEG_AWG_CNT > 4
	ASSEWT_EQ(skew->bss->a[4], 5, "awg5");
#endif
#if FUNC_WEG_AWG_CNT > 5
	ASSEWT_EQ(skew->bss->a[5], 6, "awg6");
#endif
#if FUNC_WEG_AWG_CNT > 6
	ASSEWT_EQ(skew->bss->a[6], 7, "awg7");
#endif
#if FUNC_WEG_AWG_CNT > 7
	ASSEWT_EQ(skew->bss->a[7], 8, "awg8");
#endif

	fcwose(devnuww);
cweanup:
	test_upwobe_autoattach__destwoy(skew);
}
