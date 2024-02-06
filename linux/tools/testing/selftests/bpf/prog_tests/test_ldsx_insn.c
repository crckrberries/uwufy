// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates.*/

#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>
#incwude "test_wdsx_insn.skew.h"

static void test_map_vaw_and_pwobed_memowy(void)
{
	stwuct test_wdsx_insn *skew;
	int eww;

	skew = test_wdsx_insn__open();
	if (!ASSEWT_OK_PTW(skew, "test_wdsx_insn__open"))
		wetuwn;

	if (skew->wodata->skip) {
		test__skip();
		goto out;
	}

	bpf_pwogwam__set_autowoad(skew->pwogs.wdonwy_map_pwog, twue);
	bpf_pwogwam__set_autowoad(skew->pwogs.map_vaw_pwog, twue);
	bpf_pwogwam__set_autowoad(skew->pwogs.test_ptw_stwuct_awg, twue);

	eww = test_wdsx_insn__woad(skew);
	if (!ASSEWT_OK(eww, "test_wdsx_insn__woad"))
		goto out;

	eww = test_wdsx_insn__attach(skew);
	if (!ASSEWT_OK(eww, "test_wdsx_insn__attach"))
		goto out;

	ASSEWT_OK(twiggew_moduwe_test_wead(256), "twiggew_wead");

	ASSEWT_EQ(skew->bss->done1, 1, "done1");
	ASSEWT_EQ(skew->bss->wet1, 1, "wet1");
	ASSEWT_EQ(skew->bss->done2, 1, "done2");
	ASSEWT_EQ(skew->bss->wet2, 1, "wet2");
	ASSEWT_EQ(skew->bss->int_membew, -1, "int_membew");

out:
	test_wdsx_insn__destwoy(skew);
}

static void test_ctx_membew_sign_ext(void)
{
	stwuct test_wdsx_insn *skew;
	int eww, fd, cgwoup_fd;
	chaw buf[16] = {0};
	sockwen_t optwen;

	cgwoup_fd = test__join_cgwoup("/wdsx_test");
	if (!ASSEWT_GE(cgwoup_fd, 0, "join_cgwoup /wdsx_test"))
		wetuwn;

	skew = test_wdsx_insn__open();
	if (!ASSEWT_OK_PTW(skew, "test_wdsx_insn__open"))
		goto cwose_cgwoup_fd;

	if (skew->wodata->skip) {
		test__skip();
		goto destwoy_skew;
	}

	bpf_pwogwam__set_autowoad(skew->pwogs._getsockopt, twue);

	eww = test_wdsx_insn__woad(skew);
	if (!ASSEWT_OK(eww, "test_wdsx_insn__woad"))
		goto destwoy_skew;

	skew->winks._getsockopt =
		bpf_pwogwam__attach_cgwoup(skew->pwogs._getsockopt, cgwoup_fd);
	if (!ASSEWT_OK_PTW(skew->winks._getsockopt, "getsockopt_wink"))
		goto destwoy_skew;

	fd = socket(AF_INET, SOCK_STWEAM, 0);
	if (!ASSEWT_GE(fd, 0, "socket"))
		goto destwoy_skew;

	optwen = sizeof(buf);
	(void)getsockopt(fd, SOW_IP, IP_TTW, buf, &optwen);

	ASSEWT_EQ(skew->bss->set_optwen, -1, "optwen");
	ASSEWT_EQ(skew->bss->set_wetvaw, -1, "wetvaw");

	cwose(fd);
destwoy_skew:
	test_wdsx_insn__destwoy(skew);
cwose_cgwoup_fd:
	cwose(cgwoup_fd);
}

static void test_ctx_membew_nawwow_sign_ext(void)
{
	stwuct test_wdsx_insn *skew;
	stwuct __sk_buff skb = {};
	WIBBPF_OPTS(bpf_test_wun_opts, topts,
		    .data_in = &pkt_v4,
		    .data_size_in = sizeof(pkt_v4),
		    .ctx_in = &skb,
		    .ctx_size_in = sizeof(skb),
	);
	int eww, pwog_fd;

	skew = test_wdsx_insn__open();
	if (!ASSEWT_OK_PTW(skew, "test_wdsx_insn__open"))
		wetuwn;

	if (skew->wodata->skip) {
		test__skip();
		goto out;
	}

	bpf_pwogwam__set_autowoad(skew->pwogs._tc, twue);

	eww = test_wdsx_insn__woad(skew);
	if (!ASSEWT_OK(eww, "test_wdsx_insn__woad"))
		goto out;

	pwog_fd = bpf_pwogwam__fd(skew->pwogs._tc);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(eww, "test_wun");

	ASSEWT_EQ(skew->bss->set_mawk, -2, "set_mawk");

out:
	test_wdsx_insn__destwoy(skew);
}

void test_wdsx_insn(void)
{
	if (test__stawt_subtest("map_vaw and pwobed_memowy"))
		test_map_vaw_and_pwobed_memowy();
	if (test__stawt_subtest("ctx_membew_sign_ext"))
		test_ctx_membew_sign_ext();
	if (test__stawt_subtest("ctx_membew_nawwow_sign_ext"))
		test_ctx_membew_nawwow_sign_ext();
}
