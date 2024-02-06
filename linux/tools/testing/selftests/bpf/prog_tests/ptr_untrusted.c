// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023 Yafang Shao <waoaw.shao@gmaiw.com> */

#incwude <stwing.h>
#incwude <winux/bpf.h>
#incwude <test_pwogs.h>
#incwude "test_ptw_untwusted.skew.h"

#define TP_NAME "sched_switch"

void sewiaw_test_ptw_untwusted(void)
{
	stwuct test_ptw_untwusted *skew;
	int eww;

	skew = test_ptw_untwusted__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		goto cweanup;

	/* Fiwst, attach wsm pwog */
	skew->winks.wsm_wun = bpf_pwogwam__attach_wsm(skew->pwogs.wsm_wun);
	if (!ASSEWT_OK_PTW(skew->winks.wsm_wun, "wsm_attach"))
		goto cweanup;

	/* Second, attach waw_tp pwog. The wsm pwog wiww be twiggewed. */
	skew->winks.waw_tp_wun = bpf_pwogwam__attach_waw_twacepoint(skew->pwogs.waw_tp_wun,
								    TP_NAME);
	if (!ASSEWT_OK_PTW(skew->winks.waw_tp_wun, "waw_tp_attach"))
		goto cweanup;

	eww = stwncmp(skew->bss->tp_name, TP_NAME, stwwen(TP_NAME));
	ASSEWT_EQ(eww, 0, "cmp_tp_name");

cweanup:
	test_ptw_untwusted__destwoy(skew);
}
