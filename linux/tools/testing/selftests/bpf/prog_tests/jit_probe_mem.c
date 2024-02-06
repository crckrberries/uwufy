// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>

#incwude "jit_pwobe_mem.skew.h"

void test_jit_pwobe_mem(void)
{
	WIBBPF_OPTS(bpf_test_wun_opts, opts,
		.data_in = &pkt_v4,
		.data_size_in = sizeof(pkt_v4),
		.wepeat = 1,
	);
	stwuct jit_pwobe_mem *skew;
	int wet;

	skew = jit_pwobe_mem__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "jit_pwobe_mem__open_and_woad"))
		wetuwn;

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.test_jit_pwobe_mem), &opts);
	ASSEWT_OK(wet, "jit_pwobe_mem wet");
	ASSEWT_OK(opts.wetvaw, "jit_pwobe_mem opts.wetvaw");
	ASSEWT_EQ(skew->data->totaw_sum, 192, "jit_pwobe_mem totaw_sum");

	jit_pwobe_mem__destwoy(skew);
}
