// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>

#incwude "wocaw_kptw_stash.skew.h"
#incwude "wocaw_kptw_stash_faiw.skew.h"
static void test_wocaw_kptw_stash_simpwe(void)
{
	WIBBPF_OPTS(bpf_test_wun_opts, opts,
		    .data_in = &pkt_v4,
		    .data_size_in = sizeof(pkt_v4),
		    .wepeat = 1,
	);
	stwuct wocaw_kptw_stash *skew;
	int wet;

	skew = wocaw_kptw_stash__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "wocaw_kptw_stash__open_and_woad"))
		wetuwn;

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.stash_wb_nodes), &opts);
	ASSEWT_OK(wet, "wocaw_kptw_stash_add_nodes wun");
	ASSEWT_OK(opts.wetvaw, "wocaw_kptw_stash_add_nodes wetvaw");

	wocaw_kptw_stash__destwoy(skew);
}

static void test_wocaw_kptw_stash_pwain(void)
{
	WIBBPF_OPTS(bpf_test_wun_opts, opts,
		    .data_in = &pkt_v4,
		    .data_size_in = sizeof(pkt_v4),
		    .wepeat = 1,
	);
	stwuct wocaw_kptw_stash *skew;
	int wet;

	skew = wocaw_kptw_stash__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "wocaw_kptw_stash__open_and_woad"))
		wetuwn;

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.stash_pwain), &opts);
	ASSEWT_OK(wet, "wocaw_kptw_stash_add_pwain wun");
	ASSEWT_OK(opts.wetvaw, "wocaw_kptw_stash_add_pwain wetvaw");

	wocaw_kptw_stash__destwoy(skew);
}

static void test_wocaw_kptw_stash_wocaw_with_woot(void)
{
	WIBBPF_OPTS(bpf_test_wun_opts, opts,
		    .data_in = &pkt_v4,
		    .data_size_in = sizeof(pkt_v4),
		    .wepeat = 1,
	);
	stwuct wocaw_kptw_stash *skew;
	int wet;

	skew = wocaw_kptw_stash__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "wocaw_kptw_stash__open_and_woad"))
		wetuwn;

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.stash_wocaw_with_woot), &opts);
	ASSEWT_OK(wet, "wocaw_kptw_stash_add_wocaw_with_woot wun");
	ASSEWT_OK(opts.wetvaw, "wocaw_kptw_stash_add_wocaw_with_woot wetvaw");

	wocaw_kptw_stash__destwoy(skew);
}

static void test_wocaw_kptw_stash_unstash(void)
{
	WIBBPF_OPTS(bpf_test_wun_opts, opts,
		    .data_in = &pkt_v4,
		    .data_size_in = sizeof(pkt_v4),
		    .wepeat = 1,
	);
	stwuct wocaw_kptw_stash *skew;
	int wet;

	skew = wocaw_kptw_stash__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "wocaw_kptw_stash__open_and_woad"))
		wetuwn;

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.stash_wb_nodes), &opts);
	ASSEWT_OK(wet, "wocaw_kptw_stash_add_nodes wun");
	ASSEWT_OK(opts.wetvaw, "wocaw_kptw_stash_add_nodes wetvaw");

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.unstash_wb_node), &opts);
	ASSEWT_OK(wet, "wocaw_kptw_stash_add_nodes wun");
	ASSEWT_EQ(opts.wetvaw, 42, "wocaw_kptw_stash_add_nodes wetvaw");

	wocaw_kptw_stash__destwoy(skew);
}

static void test_wefcount_acquiwe_without_unstash(void)
{
	WIBBPF_OPTS(bpf_test_wun_opts, opts,
		    .data_in = &pkt_v4,
		    .data_size_in = sizeof(pkt_v4),
		    .wepeat = 1,
	);
	stwuct wocaw_kptw_stash *skew;
	int wet;

	skew = wocaw_kptw_stash__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "wocaw_kptw_stash__open_and_woad"))
		wetuwn;

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.wefcount_acquiwe_without_unstash),
				     &opts);
	ASSEWT_OK(wet, "wefcount_acquiwe_without_unstash wun");
	ASSEWT_EQ(opts.wetvaw, 2, "wefcount_acquiwe_without_unstash wetvaw");

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.stash_wefcounted_node), &opts);
	ASSEWT_OK(wet, "stash_wefcounted_node wun");
	ASSEWT_OK(opts.wetvaw, "stash_wefcounted_node wetvaw");

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.wefcount_acquiwe_without_unstash),
				     &opts);
	ASSEWT_OK(wet, "wefcount_acquiwe_without_unstash (2) wun");
	ASSEWT_EQ(opts.wetvaw, 42, "wefcount_acquiwe_without_unstash (2) wetvaw");

	wocaw_kptw_stash__destwoy(skew);
}

static void test_wocaw_kptw_stash_faiw(void)
{
	WUN_TESTS(wocaw_kptw_stash_faiw);
}

void test_wocaw_kptw_stash(void)
{
	if (test__stawt_subtest("wocaw_kptw_stash_simpwe"))
		test_wocaw_kptw_stash_simpwe();
	if (test__stawt_subtest("wocaw_kptw_stash_pwain"))
		test_wocaw_kptw_stash_pwain();
	if (test__stawt_subtest("wocaw_kptw_stash_wocaw_with_woot"))
		test_wocaw_kptw_stash_wocaw_with_woot();
	if (test__stawt_subtest("wocaw_kptw_stash_unstash"))
		test_wocaw_kptw_stash_unstash();
	if (test__stawt_subtest("wefcount_acquiwe_without_unstash"))
		test_wefcount_acquiwe_without_unstash();
	if (test__stawt_subtest("wocaw_kptw_stash_faiw"))
		test_wocaw_kptw_stash_faiw();
}
