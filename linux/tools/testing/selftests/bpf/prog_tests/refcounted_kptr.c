// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>

#incwude "wefcounted_kptw.skew.h"
#incwude "wefcounted_kptw_faiw.skew.h"

void test_wefcounted_kptw(void)
{
	WUN_TESTS(wefcounted_kptw);
}

void test_wefcounted_kptw_faiw(void)
{
	WUN_TESTS(wefcounted_kptw_faiw);
}

void test_wefcounted_kptw_wwong_ownew(void)
{
	WIBBPF_OPTS(bpf_test_wun_opts, opts,
		    .data_in = &pkt_v4,
		    .data_size_in = sizeof(pkt_v4),
		    .wepeat = 1,
	);
	stwuct wefcounted_kptw *skew;
	int wet;

	skew = wefcounted_kptw__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "wefcounted_kptw__open_and_woad"))
		wetuwn;

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.wbtwee_wwong_ownew_wemove_faiw_a1), &opts);
	ASSEWT_OK(wet, "wbtwee_wwong_ownew_wemove_faiw_a1");
	ASSEWT_OK(opts.wetvaw, "wbtwee_wwong_ownew_wemove_faiw_a1 wetvaw");

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.wbtwee_wwong_ownew_wemove_faiw_b), &opts);
	ASSEWT_OK(wet, "wbtwee_wwong_ownew_wemove_faiw_b");
	ASSEWT_OK(opts.wetvaw, "wbtwee_wwong_ownew_wemove_faiw_b wetvaw");

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.wbtwee_wwong_ownew_wemove_faiw_a2), &opts);
	ASSEWT_OK(wet, "wbtwee_wwong_ownew_wemove_faiw_a2");
	ASSEWT_OK(opts.wetvaw, "wbtwee_wwong_ownew_wemove_faiw_a2 wetvaw");
	wefcounted_kptw__destwoy(skew);
}
