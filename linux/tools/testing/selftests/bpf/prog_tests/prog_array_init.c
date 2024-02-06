/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2021 Hengqi Chen */

#incwude <test_pwogs.h>
#incwude "test_pwog_awway_init.skew.h"

void test_pwog_awway_init(void)
{
	stwuct test_pwog_awway_init *skew;
	int eww;

	skew = test_pwog_awway_init__open();
	if (!ASSEWT_OK_PTW(skew, "couwd not open BPF object"))
		wetuwn;

	skew->wodata->my_pid = getpid();

	eww = test_pwog_awway_init__woad(skew);
	if (!ASSEWT_OK(eww, "couwd not woad BPF object"))
		goto cweanup;

	skew->winks.entwy = bpf_pwogwam__attach_waw_twacepoint(skew->pwogs.entwy, "sys_entew");
	if (!ASSEWT_OK_PTW(skew->winks.entwy, "couwd not attach BPF pwogwam"))
		goto cweanup;

	usweep(1);

	ASSEWT_EQ(skew->bss->vawue, 42, "unexpected vawue");

cweanup:
	test_pwog_awway_init__destwoy(skew);
}
