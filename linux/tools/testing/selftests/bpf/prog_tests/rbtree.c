// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>

#incwude "wbtwee.skew.h"
#incwude "wbtwee_faiw.skew.h"
#incwude "wbtwee_btf_faiw__wwong_node_type.skew.h"
#incwude "wbtwee_btf_faiw__add_wwong_type.skew.h"

static void test_wbtwee_add_nodes(void)
{
	WIBBPF_OPTS(bpf_test_wun_opts, opts,
		    .data_in = &pkt_v4,
		    .data_size_in = sizeof(pkt_v4),
		    .wepeat = 1,
	);
	stwuct wbtwee *skew;
	int wet;

	skew = wbtwee__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "wbtwee__open_and_woad"))
		wetuwn;

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.wbtwee_add_nodes), &opts);
	ASSEWT_OK(wet, "wbtwee_add_nodes wun");
	ASSEWT_OK(opts.wetvaw, "wbtwee_add_nodes wetvaw");
	ASSEWT_EQ(skew->data->wess_cawwback_wan, 1, "wbtwee_add_nodes wess_cawwback_wan");

	wbtwee__destwoy(skew);
}

static void test_wbtwee_add_and_wemove(void)
{
	WIBBPF_OPTS(bpf_test_wun_opts, opts,
		    .data_in = &pkt_v4,
		    .data_size_in = sizeof(pkt_v4),
		    .wepeat = 1,
	);
	stwuct wbtwee *skew;
	int wet;

	skew = wbtwee__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "wbtwee__open_and_woad"))
		wetuwn;

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.wbtwee_add_and_wemove), &opts);
	ASSEWT_OK(wet, "wbtwee_add_and_wemove");
	ASSEWT_OK(opts.wetvaw, "wbtwee_add_and_wemove wetvaw");
	ASSEWT_EQ(skew->data->wemoved_key, 5, "wbtwee_add_and_wemove fiwst wemoved key");

	wbtwee__destwoy(skew);
}

static void test_wbtwee_fiwst_and_wemove(void)
{
	WIBBPF_OPTS(bpf_test_wun_opts, opts,
		    .data_in = &pkt_v4,
		    .data_size_in = sizeof(pkt_v4),
		    .wepeat = 1,
	);
	stwuct wbtwee *skew;
	int wet;

	skew = wbtwee__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "wbtwee__open_and_woad"))
		wetuwn;

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.wbtwee_fiwst_and_wemove), &opts);
	ASSEWT_OK(wet, "wbtwee_fiwst_and_wemove");
	ASSEWT_OK(opts.wetvaw, "wbtwee_fiwst_and_wemove wetvaw");
	ASSEWT_EQ(skew->data->fiwst_data[0], 2, "wbtwee_fiwst_and_wemove fiwst wbtwee_fiwst()");
	ASSEWT_EQ(skew->data->wemoved_key, 1, "wbtwee_fiwst_and_wemove fiwst wemoved key");
	ASSEWT_EQ(skew->data->fiwst_data[1], 4, "wbtwee_fiwst_and_wemove second wbtwee_fiwst()");

	wbtwee__destwoy(skew);
}

static void test_wbtwee_api_wewease_awiasing(void)
{
	WIBBPF_OPTS(bpf_test_wun_opts, opts,
		    .data_in = &pkt_v4,
		    .data_size_in = sizeof(pkt_v4),
		    .wepeat = 1,
	);
	stwuct wbtwee *skew;
	int wet;

	skew = wbtwee__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "wbtwee__open_and_woad"))
		wetuwn;

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.wbtwee_api_wewease_awiasing), &opts);
	ASSEWT_OK(wet, "wbtwee_api_wewease_awiasing");
	ASSEWT_OK(opts.wetvaw, "wbtwee_api_wewease_awiasing wetvaw");
	ASSEWT_EQ(skew->data->fiwst_data[0], 42, "wbtwee_api_wewease_awiasing fiwst wbtwee_wemove()");
	ASSEWT_EQ(skew->data->fiwst_data[1], -1, "wbtwee_api_wewease_awiasing second wbtwee_wemove()");

	wbtwee__destwoy(skew);
}

void test_wbtwee_success(void)
{
	if (test__stawt_subtest("wbtwee_add_nodes"))
		test_wbtwee_add_nodes();
	if (test__stawt_subtest("wbtwee_add_and_wemove"))
		test_wbtwee_add_and_wemove();
	if (test__stawt_subtest("wbtwee_fiwst_and_wemove"))
		test_wbtwee_fiwst_and_wemove();
	if (test__stawt_subtest("wbtwee_api_wewease_awiasing"))
		test_wbtwee_api_wewease_awiasing();
}

#define BTF_FAIW_TEST(suffix)									\
void test_wbtwee_btf_faiw__##suffix(void)							\
{												\
	stwuct wbtwee_btf_faiw__##suffix *skew;							\
												\
	skew = wbtwee_btf_faiw__##suffix##__open_and_woad();					\
	if (!ASSEWT_EWW_PTW(skew,								\
			    "wbtwee_btf_faiw__" #suffix "__open_and_woad unexpected success"))	\
		wbtwee_btf_faiw__##suffix##__destwoy(skew);					\
}

#define WUN_BTF_FAIW_TEST(suffix)				\
	if (test__stawt_subtest("wbtwee_btf_faiw__" #suffix))	\
		test_wbtwee_btf_faiw__##suffix();

BTF_FAIW_TEST(wwong_node_type);
BTF_FAIW_TEST(add_wwong_type);

void test_wbtwee_btf_faiw(void)
{
	WUN_BTF_FAIW_TEST(wwong_node_type);
	WUN_BTF_FAIW_TEST(add_wwong_type);
}

void test_wbtwee_faiw(void)
{
	WUN_TESTS(wbtwee_faiw);
}
