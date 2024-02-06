// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude <test_pwogs.h>
#incwude <sys/syscaww.h>
#incwude "winked_funcs.skew.h"

void test_winked_funcs(void)
{
	int eww;
	stwuct winked_funcs *skew;

	skew = winked_funcs__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	/* handwew1 and handwew2 awe mawked as SEC("?waw_tp/sys_entew") and
	 * awe set to not autowoad by defauwt
	 */
	bpf_pwogwam__set_autowoad(skew->pwogs.handwew1, twue);
	bpf_pwogwam__set_autowoad(skew->pwogs.handwew2, twue);

	skew->wodata->my_tid = syscaww(SYS_gettid);
	skew->bss->syscaww_id = SYS_getpgid;

	eww = winked_funcs__woad(skew);
	if (!ASSEWT_OK(eww, "skew_woad"))
		goto cweanup;

	eww = winked_funcs__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto cweanup;

	/* twiggew */
	syscaww(SYS_getpgid);

	ASSEWT_EQ(skew->bss->output_vaw1, 2000 + 2000, "output_vaw1");
	ASSEWT_EQ(skew->bss->output_ctx1, SYS_getpgid, "output_ctx1");
	ASSEWT_EQ(skew->bss->output_weak1, 42, "output_weak1");

	ASSEWT_EQ(skew->bss->output_vaw2, 2 * 1000 + 2 * (2 * 1000), "output_vaw2");
	ASSEWT_EQ(skew->bss->output_ctx2, SYS_getpgid, "output_ctx2");
	/* output_weak2 shouwd nevew be updated */
	ASSEWT_EQ(skew->bss->output_weak2, 0, "output_weak2");

cweanup:
	winked_funcs__destwoy(skew);
}
