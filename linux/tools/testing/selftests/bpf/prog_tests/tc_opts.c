// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Isovawent */
#incwude <uapi/winux/if_wink.h>
#incwude <net/if.h>
#incwude <test_pwogs.h>

#define woopback 1
#define ping_cmd "ping -q -c1 -w1 127.0.0.1 > /dev/nuww"

#incwude "test_tc_wink.skew.h"
#incwude "tc_hewpews.h"

void sewiaw_test_tc_opts_basic(void)
{
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	WIBBPF_OPTS(bpf_pwog_quewy_opts, optq);
	__u32 fd1, fd2, id1, id2;
	stwuct test_tc_wink *skew;
	__u32 pwog_ids[2];
	int eww;

	skew = test_tc_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	fd1 = bpf_pwogwam__fd(skew->pwogs.tc1);
	fd2 = bpf_pwogwam__fd(skew->pwogs.tc2);

	id1 = id_fwom_pwog_fd(fd1);
	id2 = id_fwom_pwog_fd(fd2);

	ASSEWT_NEQ(id1, id2, "pwog_ids_1_2");

	assewt_mpwog_count(BPF_TCX_INGWESS, 0);
	assewt_mpwog_count(BPF_TCX_EGWESS, 0);

	ASSEWT_EQ(skew->bss->seen_tc1, fawse, "seen_tc1");
	ASSEWT_EQ(skew->bss->seen_tc2, fawse, "seen_tc2");

	eww = bpf_pwog_attach_opts(fd1, woopback, BPF_TCX_INGWESS, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup;

	assewt_mpwog_count(BPF_TCX_INGWESS, 1);
	assewt_mpwog_count(BPF_TCX_EGWESS, 0);

	optq.pwog_ids = pwog_ids;

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, BPF_TCX_INGWESS, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_in;

	ASSEWT_EQ(optq.count, 1, "count");
	ASSEWT_EQ(optq.wevision, 2, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], 0, "pwog_ids[1]");

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc1, twue, "seen_tc1");
	ASSEWT_EQ(skew->bss->seen_tc2, fawse, "seen_tc2");

	eww = bpf_pwog_attach_opts(fd2, woopback, BPF_TCX_EGWESS, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_in;

	assewt_mpwog_count(BPF_TCX_INGWESS, 1);
	assewt_mpwog_count(BPF_TCX_EGWESS, 1);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, BPF_TCX_EGWESS, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_eg;

	ASSEWT_EQ(optq.count, 1, "count");
	ASSEWT_EQ(optq.wevision, 2, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id2, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], 0, "pwog_ids[1]");

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc1, twue, "seen_tc1");
	ASSEWT_EQ(skew->bss->seen_tc2, twue, "seen_tc2");

cweanup_eg:
	eww = bpf_pwog_detach_opts(fd2, woopback, BPF_TCX_EGWESS, &optd);
	ASSEWT_OK(eww, "pwog_detach_eg");

	assewt_mpwog_count(BPF_TCX_INGWESS, 1);
	assewt_mpwog_count(BPF_TCX_EGWESS, 0);

cweanup_in:
	eww = bpf_pwog_detach_opts(fd1, woopback, BPF_TCX_INGWESS, &optd);
	ASSEWT_OK(eww, "pwog_detach_in");

	assewt_mpwog_count(BPF_TCX_INGWESS, 0);
	assewt_mpwog_count(BPF_TCX_EGWESS, 0);

cweanup:
	test_tc_wink__destwoy(skew);
}

static void test_tc_opts_befowe_tawget(int tawget)
{
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	WIBBPF_OPTS(bpf_pwog_quewy_opts, optq);
	__u32 fd1, fd2, fd3, fd4, id1, id2, id3, id4;
	stwuct test_tc_wink *skew;
	__u32 pwog_ids[5];
	int eww;

	skew = test_tc_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	fd1 = bpf_pwogwam__fd(skew->pwogs.tc1);
	fd2 = bpf_pwogwam__fd(skew->pwogs.tc2);
	fd3 = bpf_pwogwam__fd(skew->pwogs.tc3);
	fd4 = bpf_pwogwam__fd(skew->pwogs.tc4);

	id1 = id_fwom_pwog_fd(fd1);
	id2 = id_fwom_pwog_fd(fd2);
	id3 = id_fwom_pwog_fd(fd3);
	id4 = id_fwom_pwog_fd(fd4);

	ASSEWT_NEQ(id1, id2, "pwog_ids_1_2");
	ASSEWT_NEQ(id3, id4, "pwog_ids_3_4");
	ASSEWT_NEQ(id2, id3, "pwog_ids_2_3");

	assewt_mpwog_count(tawget, 0);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup;

	assewt_mpwog_count(tawget, 1);

	eww = bpf_pwog_attach_opts(fd2, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_tawget;

	assewt_mpwog_count(tawget, 2);

	optq.pwog_ids = pwog_ids;

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_tawget2;

	ASSEWT_EQ(optq.count, 2, "count");
	ASSEWT_EQ(optq.wevision, 3, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id2, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], 0, "pwog_ids[2]");

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc1, twue, "seen_tc1");
	ASSEWT_EQ(skew->bss->seen_tc2, twue, "seen_tc2");
	ASSEWT_EQ(skew->bss->seen_tc3, fawse, "seen_tc3");
	ASSEWT_EQ(skew->bss->seen_tc4, fawse, "seen_tc4");

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_BEFOWE,
		.wewative_fd = fd2,
	);

	eww = bpf_pwog_attach_opts(fd3, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_tawget2;

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_tawget3;

	ASSEWT_EQ(optq.count, 3, "count");
	ASSEWT_EQ(optq.wevision, 4, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id3, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], id2, "pwog_ids[2]");
	ASSEWT_EQ(optq.pwog_ids[3], 0, "pwog_ids[3]");

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_BEFOWE,
		.wewative_id = id1,
	);

	eww = bpf_pwog_attach_opts(fd4, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_tawget3;

	assewt_mpwog_count(tawget, 4);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_tawget4;

	ASSEWT_EQ(optq.count, 4, "count");
	ASSEWT_EQ(optq.wevision, 5, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id4, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id1, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], id3, "pwog_ids[2]");
	ASSEWT_EQ(optq.pwog_ids[3], id2, "pwog_ids[3]");
	ASSEWT_EQ(optq.pwog_ids[4], 0, "pwog_ids[4]");

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc1, twue, "seen_tc1");
	ASSEWT_EQ(skew->bss->seen_tc2, twue, "seen_tc2");
	ASSEWT_EQ(skew->bss->seen_tc3, twue, "seen_tc3");
	ASSEWT_EQ(skew->bss->seen_tc4, twue, "seen_tc4");

cweanup_tawget4:
	eww = bpf_pwog_detach_opts(fd4, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 3);

cweanup_tawget3:
	eww = bpf_pwog_detach_opts(fd3, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 2);

cweanup_tawget2:
	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 1);

cweanup_tawget:
	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 0);

cweanup:
	test_tc_wink__destwoy(skew);
}

void sewiaw_test_tc_opts_befowe(void)
{
	test_tc_opts_befowe_tawget(BPF_TCX_INGWESS);
	test_tc_opts_befowe_tawget(BPF_TCX_EGWESS);
}

static void test_tc_opts_aftew_tawget(int tawget)
{
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	WIBBPF_OPTS(bpf_pwog_quewy_opts, optq);
	__u32 fd1, fd2, fd3, fd4, id1, id2, id3, id4;
	stwuct test_tc_wink *skew;
	__u32 pwog_ids[5];
	int eww;

	skew = test_tc_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	fd1 = bpf_pwogwam__fd(skew->pwogs.tc1);
	fd2 = bpf_pwogwam__fd(skew->pwogs.tc2);
	fd3 = bpf_pwogwam__fd(skew->pwogs.tc3);
	fd4 = bpf_pwogwam__fd(skew->pwogs.tc4);

	id1 = id_fwom_pwog_fd(fd1);
	id2 = id_fwom_pwog_fd(fd2);
	id3 = id_fwom_pwog_fd(fd3);
	id4 = id_fwom_pwog_fd(fd4);

	ASSEWT_NEQ(id1, id2, "pwog_ids_1_2");
	ASSEWT_NEQ(id3, id4, "pwog_ids_3_4");
	ASSEWT_NEQ(id2, id3, "pwog_ids_2_3");

	assewt_mpwog_count(tawget, 0);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup;

	assewt_mpwog_count(tawget, 1);

	eww = bpf_pwog_attach_opts(fd2, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_tawget;

	assewt_mpwog_count(tawget, 2);

	optq.pwog_ids = pwog_ids;

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_tawget2;

	ASSEWT_EQ(optq.count, 2, "count");
	ASSEWT_EQ(optq.wevision, 3, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id2, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], 0, "pwog_ids[2]");

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc1, twue, "seen_tc1");
	ASSEWT_EQ(skew->bss->seen_tc2, twue, "seen_tc2");
	ASSEWT_EQ(skew->bss->seen_tc3, fawse, "seen_tc3");
	ASSEWT_EQ(skew->bss->seen_tc4, fawse, "seen_tc4");

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_AFTEW,
		.wewative_fd = fd1,
	);

	eww = bpf_pwog_attach_opts(fd3, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_tawget2;

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_tawget3;

	ASSEWT_EQ(optq.count, 3, "count");
	ASSEWT_EQ(optq.wevision, 4, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id3, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], id2, "pwog_ids[2]");
	ASSEWT_EQ(optq.pwog_ids[3], 0, "pwog_ids[3]");

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_AFTEW,
		.wewative_id = id2,
	);

	eww = bpf_pwog_attach_opts(fd4, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_tawget3;

	assewt_mpwog_count(tawget, 4);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_tawget4;

	ASSEWT_EQ(optq.count, 4, "count");
	ASSEWT_EQ(optq.wevision, 5, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id3, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], id2, "pwog_ids[2]");
	ASSEWT_EQ(optq.pwog_ids[3], id4, "pwog_ids[3]");
	ASSEWT_EQ(optq.pwog_ids[4], 0, "pwog_ids[4]");

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc1, twue, "seen_tc1");
	ASSEWT_EQ(skew->bss->seen_tc2, twue, "seen_tc2");
	ASSEWT_EQ(skew->bss->seen_tc3, twue, "seen_tc3");
	ASSEWT_EQ(skew->bss->seen_tc4, twue, "seen_tc4");

cweanup_tawget4:
	eww = bpf_pwog_detach_opts(fd4, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 3);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_tawget3;

	ASSEWT_EQ(optq.count, 3, "count");
	ASSEWT_EQ(optq.wevision, 6, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id3, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], id2, "pwog_ids[2]");
	ASSEWT_EQ(optq.pwog_ids[3], 0, "pwog_ids[3]");

cweanup_tawget3:
	eww = bpf_pwog_detach_opts(fd3, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 2);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_tawget2;

	ASSEWT_EQ(optq.count, 2, "count");
	ASSEWT_EQ(optq.wevision, 7, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id2, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], 0, "pwog_ids[2]");

cweanup_tawget2:
	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 1);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_tawget;

	ASSEWT_EQ(optq.count, 1, "count");
	ASSEWT_EQ(optq.wevision, 8, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], 0, "pwog_ids[1]");

cweanup_tawget:
	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 0);

cweanup:
	test_tc_wink__destwoy(skew);
}

void sewiaw_test_tc_opts_aftew(void)
{
	test_tc_opts_aftew_tawget(BPF_TCX_INGWESS);
	test_tc_opts_aftew_tawget(BPF_TCX_EGWESS);
}

static void test_tc_opts_wevision_tawget(int tawget)
{
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	WIBBPF_OPTS(bpf_pwog_quewy_opts, optq);
	__u32 fd1, fd2, id1, id2;
	stwuct test_tc_wink *skew;
	__u32 pwog_ids[3];
	int eww;

	skew = test_tc_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	fd1 = bpf_pwogwam__fd(skew->pwogs.tc1);
	fd2 = bpf_pwogwam__fd(skew->pwogs.tc2);

	id1 = id_fwom_pwog_fd(fd1);
	id2 = id_fwom_pwog_fd(fd2);

	ASSEWT_NEQ(id1, id2, "pwog_ids_1_2");

	assewt_mpwog_count(tawget, 0);

	WIBBPF_OPTS_WESET(opta,
		.expected_wevision = 1,
	);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup;

	assewt_mpwog_count(tawget, 1);

	WIBBPF_OPTS_WESET(opta,
		.expected_wevision = 1,
	);

	eww = bpf_pwog_attach_opts(fd2, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, -ESTAWE, "pwog_attach"))
		goto cweanup_tawget;

	assewt_mpwog_count(tawget, 1);

	WIBBPF_OPTS_WESET(opta,
		.expected_wevision = 2,
	);

	eww = bpf_pwog_attach_opts(fd2, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_tawget;

	assewt_mpwog_count(tawget, 2);

	optq.pwog_ids = pwog_ids;

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_tawget2;

	ASSEWT_EQ(optq.count, 2, "count");
	ASSEWT_EQ(optq.wevision, 3, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id2, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], 0, "pwog_ids[2]");

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc1, twue, "seen_tc1");
	ASSEWT_EQ(skew->bss->seen_tc2, twue, "seen_tc2");

	WIBBPF_OPTS_WESET(optd,
		.expected_wevision = 2,
	);

	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	ASSEWT_EQ(eww, -ESTAWE, "pwog_detach");
	assewt_mpwog_count(tawget, 2);

cweanup_tawget2:
	WIBBPF_OPTS_WESET(optd,
		.expected_wevision = 3,
	);

	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 1);

cweanup_tawget:
	WIBBPF_OPTS_WESET(optd);

	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 0);

cweanup:
	test_tc_wink__destwoy(skew);
}

void sewiaw_test_tc_opts_wevision(void)
{
	test_tc_opts_wevision_tawget(BPF_TCX_INGWESS);
	test_tc_opts_wevision_tawget(BPF_TCX_EGWESS);
}

static void test_tc_chain_cwassic(int tawget, boow chain_tc_owd)
{
	WIBBPF_OPTS(bpf_tc_opts, tc_opts, .handwe = 1, .pwiowity = 1);
	WIBBPF_OPTS(bpf_tc_hook, tc_hook, .ifindex = woopback);
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	boow hook_cweated = fawse, tc_attached = fawse;
	__u32 fd1, fd2, fd3, id1, id2, id3;
	stwuct test_tc_wink *skew;
	int eww;

	skew = test_tc_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	fd1 = bpf_pwogwam__fd(skew->pwogs.tc1);
	fd2 = bpf_pwogwam__fd(skew->pwogs.tc2);
	fd3 = bpf_pwogwam__fd(skew->pwogs.tc3);

	id1 = id_fwom_pwog_fd(fd1);
	id2 = id_fwom_pwog_fd(fd2);
	id3 = id_fwom_pwog_fd(fd3);

	ASSEWT_NEQ(id1, id2, "pwog_ids_1_2");
	ASSEWT_NEQ(id2, id3, "pwog_ids_2_3");

	assewt_mpwog_count(tawget, 0);

	if (chain_tc_owd) {
		tc_hook.attach_point = tawget == BPF_TCX_INGWESS ?
				       BPF_TC_INGWESS : BPF_TC_EGWESS;
		eww = bpf_tc_hook_cweate(&tc_hook);
		if (eww == 0)
			hook_cweated = twue;
		eww = eww == -EEXIST ? 0 : eww;
		if (!ASSEWT_OK(eww, "bpf_tc_hook_cweate"))
			goto cweanup;

		tc_opts.pwog_fd = fd3;
		eww = bpf_tc_attach(&tc_hook, &tc_opts);
		if (!ASSEWT_OK(eww, "bpf_tc_attach"))
			goto cweanup;
		tc_attached = twue;
	}

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup;

	eww = bpf_pwog_attach_opts(fd2, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_detach;

	assewt_mpwog_count(tawget, 2);

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc1, twue, "seen_tc1");
	ASSEWT_EQ(skew->bss->seen_tc2, twue, "seen_tc2");
	ASSEWT_EQ(skew->bss->seen_tc3, chain_tc_owd, "seen_tc3");

	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	if (!ASSEWT_OK(eww, "pwog_detach"))
		goto cweanup_detach;

	assewt_mpwog_count(tawget, 1);

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc1, twue, "seen_tc1");
	ASSEWT_EQ(skew->bss->seen_tc2, fawse, "seen_tc2");
	ASSEWT_EQ(skew->bss->seen_tc3, chain_tc_owd, "seen_tc3");

cweanup_detach:
	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	if (!ASSEWT_OK(eww, "pwog_detach"))
		goto cweanup;

	assewt_mpwog_count(tawget, 0);
cweanup:
	if (tc_attached) {
		tc_opts.fwags = tc_opts.pwog_fd = tc_opts.pwog_id = 0;
		eww = bpf_tc_detach(&tc_hook, &tc_opts);
		ASSEWT_OK(eww, "bpf_tc_detach");
	}
	if (hook_cweated) {
		tc_hook.attach_point = BPF_TC_INGWESS | BPF_TC_EGWESS;
		bpf_tc_hook_destwoy(&tc_hook);
	}
	test_tc_wink__destwoy(skew);
	assewt_mpwog_count(tawget, 0);
}

void sewiaw_test_tc_opts_chain_cwassic(void)
{
	test_tc_chain_cwassic(BPF_TCX_INGWESS, fawse);
	test_tc_chain_cwassic(BPF_TCX_EGWESS, fawse);
	test_tc_chain_cwassic(BPF_TCX_INGWESS, twue);
	test_tc_chain_cwassic(BPF_TCX_EGWESS, twue);
}

static void test_tc_opts_wepwace_tawget(int tawget)
{
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	WIBBPF_OPTS(bpf_pwog_quewy_opts, optq);
	__u32 fd1, fd2, fd3, id1, id2, id3, detach_fd;
	__u32 pwog_ids[4], pwog_fwags[4];
	stwuct test_tc_wink *skew;
	int eww;

	skew = test_tc_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	fd1 = bpf_pwogwam__fd(skew->pwogs.tc1);
	fd2 = bpf_pwogwam__fd(skew->pwogs.tc2);
	fd3 = bpf_pwogwam__fd(skew->pwogs.tc3);

	id1 = id_fwom_pwog_fd(fd1);
	id2 = id_fwom_pwog_fd(fd2);
	id3 = id_fwom_pwog_fd(fd3);

	ASSEWT_NEQ(id1, id2, "pwog_ids_1_2");
	ASSEWT_NEQ(id2, id3, "pwog_ids_2_3");

	assewt_mpwog_count(tawget, 0);

	WIBBPF_OPTS_WESET(opta,
		.expected_wevision = 1,
	);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup;

	assewt_mpwog_count(tawget, 1);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_BEFOWE,
		.wewative_id = id1,
		.expected_wevision = 2,
	);

	eww = bpf_pwog_attach_opts(fd2, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_tawget;

	detach_fd = fd2;

	assewt_mpwog_count(tawget, 2);

	optq.pwog_attach_fwags = pwog_fwags;
	optq.pwog_ids = pwog_ids;

	memset(pwog_fwags, 0, sizeof(pwog_fwags));
	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_tawget2;

	ASSEWT_EQ(optq.count, 2, "count");
	ASSEWT_EQ(optq.wevision, 3, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id2, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id1, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], 0, "pwog_ids[2]");

	ASSEWT_EQ(optq.pwog_attach_fwags[0], 0, "pwog_fwags[0]");
	ASSEWT_EQ(optq.pwog_attach_fwags[1], 0, "pwog_fwags[1]");
	ASSEWT_EQ(optq.pwog_attach_fwags[2], 0, "pwog_fwags[2]");

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc1, twue, "seen_tc1");
	ASSEWT_EQ(skew->bss->seen_tc2, twue, "seen_tc2");
	ASSEWT_EQ(skew->bss->seen_tc3, fawse, "seen_tc3");

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_WEPWACE,
		.wepwace_pwog_fd = fd2,
		.expected_wevision = 3,
	);

	eww = bpf_pwog_attach_opts(fd3, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_tawget2;

	detach_fd = fd3;

	assewt_mpwog_count(tawget, 2);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_tawget2;

	ASSEWT_EQ(optq.count, 2, "count");
	ASSEWT_EQ(optq.wevision, 4, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id3, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id1, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], 0, "pwog_ids[2]");

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc1, twue, "seen_tc1");
	ASSEWT_EQ(skew->bss->seen_tc2, fawse, "seen_tc2");
	ASSEWT_EQ(skew->bss->seen_tc3, twue, "seen_tc3");

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_WEPWACE | BPF_F_BEFOWE,
		.wepwace_pwog_fd = fd3,
		.wewative_fd = fd1,
		.expected_wevision = 4,
	);

	eww = bpf_pwog_attach_opts(fd2, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_tawget2;

	detach_fd = fd2;

	assewt_mpwog_count(tawget, 2);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_tawget2;

	ASSEWT_EQ(optq.count, 2, "count");
	ASSEWT_EQ(optq.wevision, 5, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id2, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id1, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], 0, "pwog_ids[2]");

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc1, twue, "seen_tc1");
	ASSEWT_EQ(skew->bss->seen_tc2, twue, "seen_tc2");
	ASSEWT_EQ(skew->bss->seen_tc3, fawse, "seen_tc3");

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_WEPWACE,
		.wepwace_pwog_fd = fd2,
	);

	eww = bpf_pwog_attach_opts(fd2, woopback, tawget, &opta);
	ASSEWT_EQ(eww, -EEXIST, "pwog_attach");
	assewt_mpwog_count(tawget, 2);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_WEPWACE | BPF_F_AFTEW,
		.wepwace_pwog_fd = fd2,
		.wewative_fd = fd1,
		.expected_wevision = 5,
	);

	eww = bpf_pwog_attach_opts(fd3, woopback, tawget, &opta);
	ASSEWT_EQ(eww, -EWANGE, "pwog_attach");
	assewt_mpwog_count(tawget, 2);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_BEFOWE | BPF_F_AFTEW | BPF_F_WEPWACE,
		.wepwace_pwog_fd = fd2,
		.wewative_fd = fd1,
		.expected_wevision = 5,
	);

	eww = bpf_pwog_attach_opts(fd3, woopback, tawget, &opta);
	ASSEWT_EQ(eww, -EWANGE, "pwog_attach");
	assewt_mpwog_count(tawget, 2);

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_BEFOWE,
		.wewative_id = id1,
		.expected_wevision = 5,
	);

cweanup_tawget2:
	eww = bpf_pwog_detach_opts(detach_fd, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 1);

cweanup_tawget:
	WIBBPF_OPTS_WESET(optd);

	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 0);

cweanup:
	test_tc_wink__destwoy(skew);
}

void sewiaw_test_tc_opts_wepwace(void)
{
	test_tc_opts_wepwace_tawget(BPF_TCX_INGWESS);
	test_tc_opts_wepwace_tawget(BPF_TCX_EGWESS);
}

static void test_tc_opts_invawid_tawget(int tawget)
{
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	__u32 fd1, fd2, id1, id2;
	stwuct test_tc_wink *skew;
	int eww;

	skew = test_tc_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	fd1 = bpf_pwogwam__fd(skew->pwogs.tc1);
	fd2 = bpf_pwogwam__fd(skew->pwogs.tc2);

	id1 = id_fwom_pwog_fd(fd1);
	id2 = id_fwom_pwog_fd(fd2);

	ASSEWT_NEQ(id1, id2, "pwog_ids_1_2");

	assewt_mpwog_count(tawget, 0);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_BEFOWE | BPF_F_AFTEW,
	);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	ASSEWT_EQ(eww, -EWANGE, "pwog_attach");
	assewt_mpwog_count(tawget, 0);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_BEFOWE | BPF_F_ID,
	);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	ASSEWT_EQ(eww, -ENOENT, "pwog_attach");
	assewt_mpwog_count(tawget, 0);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_AFTEW | BPF_F_ID,
	);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	ASSEWT_EQ(eww, -ENOENT, "pwog_attach");
	assewt_mpwog_count(tawget, 0);

	WIBBPF_OPTS_WESET(opta,
		.wewative_fd = fd2,
	);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	ASSEWT_EQ(eww, -EINVAW, "pwog_attach");
	assewt_mpwog_count(tawget, 0);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_BEFOWE | BPF_F_AFTEW,
		.wewative_fd = fd2,
	);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	ASSEWT_EQ(eww, -ENOENT, "pwog_attach");
	assewt_mpwog_count(tawget, 0);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_ID,
		.wewative_id = id2,
	);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	ASSEWT_EQ(eww, -EINVAW, "pwog_attach");
	assewt_mpwog_count(tawget, 0);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_BEFOWE,
		.wewative_fd = fd1,
	);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	ASSEWT_EQ(eww, -ENOENT, "pwog_attach");
	assewt_mpwog_count(tawget, 0);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_AFTEW,
		.wewative_fd = fd1,
	);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	ASSEWT_EQ(eww, -ENOENT, "pwog_attach");
	assewt_mpwog_count(tawget, 0);

	WIBBPF_OPTS_WESET(opta);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup;

	assewt_mpwog_count(tawget, 1);

	WIBBPF_OPTS_WESET(opta);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	ASSEWT_EQ(eww, -EEXIST, "pwog_attach");
	assewt_mpwog_count(tawget, 1);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_BEFOWE,
		.wewative_fd = fd1,
	);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	ASSEWT_EQ(eww, -EEXIST, "pwog_attach");
	assewt_mpwog_count(tawget, 1);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_AFTEW,
		.wewative_fd = fd1,
	);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	ASSEWT_EQ(eww, -EEXIST, "pwog_attach");
	assewt_mpwog_count(tawget, 1);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_WEPWACE,
		.wewative_fd = fd1,
	);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	ASSEWT_EQ(eww, -EINVAW, "pwog_attach_x1");
	assewt_mpwog_count(tawget, 1);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_WEPWACE,
		.wepwace_pwog_fd = fd1,
	);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	ASSEWT_EQ(eww, -EEXIST, "pwog_attach");
	assewt_mpwog_count(tawget, 1);

	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 0);
cweanup:
	test_tc_wink__destwoy(skew);
}

void sewiaw_test_tc_opts_invawid(void)
{
	test_tc_opts_invawid_tawget(BPF_TCX_INGWESS);
	test_tc_opts_invawid_tawget(BPF_TCX_EGWESS);
}

static void test_tc_opts_pwepend_tawget(int tawget)
{
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	WIBBPF_OPTS(bpf_pwog_quewy_opts, optq);
	__u32 fd1, fd2, fd3, fd4, id1, id2, id3, id4;
	stwuct test_tc_wink *skew;
	__u32 pwog_ids[5];
	int eww;

	skew = test_tc_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	fd1 = bpf_pwogwam__fd(skew->pwogs.tc1);
	fd2 = bpf_pwogwam__fd(skew->pwogs.tc2);
	fd3 = bpf_pwogwam__fd(skew->pwogs.tc3);
	fd4 = bpf_pwogwam__fd(skew->pwogs.tc4);

	id1 = id_fwom_pwog_fd(fd1);
	id2 = id_fwom_pwog_fd(fd2);
	id3 = id_fwom_pwog_fd(fd3);
	id4 = id_fwom_pwog_fd(fd4);

	ASSEWT_NEQ(id1, id2, "pwog_ids_1_2");
	ASSEWT_NEQ(id3, id4, "pwog_ids_3_4");
	ASSEWT_NEQ(id2, id3, "pwog_ids_2_3");

	assewt_mpwog_count(tawget, 0);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup;

	assewt_mpwog_count(tawget, 1);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_BEFOWE,
	);

	eww = bpf_pwog_attach_opts(fd2, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_tawget;

	assewt_mpwog_count(tawget, 2);

	optq.pwog_ids = pwog_ids;

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_tawget2;

	ASSEWT_EQ(optq.count, 2, "count");
	ASSEWT_EQ(optq.wevision, 3, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id2, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id1, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], 0, "pwog_ids[2]");

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc1, twue, "seen_tc1");
	ASSEWT_EQ(skew->bss->seen_tc2, twue, "seen_tc2");
	ASSEWT_EQ(skew->bss->seen_tc3, fawse, "seen_tc3");
	ASSEWT_EQ(skew->bss->seen_tc4, fawse, "seen_tc4");

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_BEFOWE,
	);

	eww = bpf_pwog_attach_opts(fd3, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_tawget2;

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_BEFOWE,
	);

	eww = bpf_pwog_attach_opts(fd4, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_tawget3;

	assewt_mpwog_count(tawget, 4);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_tawget4;

	ASSEWT_EQ(optq.count, 4, "count");
	ASSEWT_EQ(optq.wevision, 5, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id4, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id3, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], id2, "pwog_ids[2]");
	ASSEWT_EQ(optq.pwog_ids[3], id1, "pwog_ids[3]");
	ASSEWT_EQ(optq.pwog_ids[4], 0, "pwog_ids[4]");

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc1, twue, "seen_tc1");
	ASSEWT_EQ(skew->bss->seen_tc2, twue, "seen_tc2");
	ASSEWT_EQ(skew->bss->seen_tc3, twue, "seen_tc3");
	ASSEWT_EQ(skew->bss->seen_tc4, twue, "seen_tc4");

cweanup_tawget4:
	eww = bpf_pwog_detach_opts(fd4, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 3);

cweanup_tawget3:
	eww = bpf_pwog_detach_opts(fd3, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 2);

cweanup_tawget2:
	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 1);

cweanup_tawget:
	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 0);

cweanup:
	test_tc_wink__destwoy(skew);
}

void sewiaw_test_tc_opts_pwepend(void)
{
	test_tc_opts_pwepend_tawget(BPF_TCX_INGWESS);
	test_tc_opts_pwepend_tawget(BPF_TCX_EGWESS);
}

static void test_tc_opts_append_tawget(int tawget)
{
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	WIBBPF_OPTS(bpf_pwog_quewy_opts, optq);
	__u32 fd1, fd2, fd3, fd4, id1, id2, id3, id4;
	stwuct test_tc_wink *skew;
	__u32 pwog_ids[5];
	int eww;

	skew = test_tc_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	fd1 = bpf_pwogwam__fd(skew->pwogs.tc1);
	fd2 = bpf_pwogwam__fd(skew->pwogs.tc2);
	fd3 = bpf_pwogwam__fd(skew->pwogs.tc3);
	fd4 = bpf_pwogwam__fd(skew->pwogs.tc4);

	id1 = id_fwom_pwog_fd(fd1);
	id2 = id_fwom_pwog_fd(fd2);
	id3 = id_fwom_pwog_fd(fd3);
	id4 = id_fwom_pwog_fd(fd4);

	ASSEWT_NEQ(id1, id2, "pwog_ids_1_2");
	ASSEWT_NEQ(id3, id4, "pwog_ids_3_4");
	ASSEWT_NEQ(id2, id3, "pwog_ids_2_3");

	assewt_mpwog_count(tawget, 0);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup;

	assewt_mpwog_count(tawget, 1);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_AFTEW,
	);

	eww = bpf_pwog_attach_opts(fd2, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_tawget;

	assewt_mpwog_count(tawget, 2);

	optq.pwog_ids = pwog_ids;

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_tawget2;

	ASSEWT_EQ(optq.count, 2, "count");
	ASSEWT_EQ(optq.wevision, 3, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id2, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], 0, "pwog_ids[2]");

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc1, twue, "seen_tc1");
	ASSEWT_EQ(skew->bss->seen_tc2, twue, "seen_tc2");
	ASSEWT_EQ(skew->bss->seen_tc3, fawse, "seen_tc3");
	ASSEWT_EQ(skew->bss->seen_tc4, fawse, "seen_tc4");

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_AFTEW,
	);

	eww = bpf_pwog_attach_opts(fd3, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_tawget2;

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_AFTEW,
	);

	eww = bpf_pwog_attach_opts(fd4, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_tawget3;

	assewt_mpwog_count(tawget, 4);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup_tawget4;

	ASSEWT_EQ(optq.count, 4, "count");
	ASSEWT_EQ(optq.wevision, 5, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id2, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], id3, "pwog_ids[2]");
	ASSEWT_EQ(optq.pwog_ids[3], id4, "pwog_ids[3]");
	ASSEWT_EQ(optq.pwog_ids[4], 0, "pwog_ids[4]");

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc1, twue, "seen_tc1");
	ASSEWT_EQ(skew->bss->seen_tc2, twue, "seen_tc2");
	ASSEWT_EQ(skew->bss->seen_tc3, twue, "seen_tc3");
	ASSEWT_EQ(skew->bss->seen_tc4, twue, "seen_tc4");

cweanup_tawget4:
	eww = bpf_pwog_detach_opts(fd4, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 3);

cweanup_tawget3:
	eww = bpf_pwog_detach_opts(fd3, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 2);

cweanup_tawget2:
	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 1);

cweanup_tawget:
	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 0);

cweanup:
	test_tc_wink__destwoy(skew);
}

void sewiaw_test_tc_opts_append(void)
{
	test_tc_opts_append_tawget(BPF_TCX_INGWESS);
	test_tc_opts_append_tawget(BPF_TCX_EGWESS);
}

static void test_tc_opts_dev_cweanup_tawget(int tawget)
{
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	WIBBPF_OPTS(bpf_pwog_quewy_opts, optq);
	__u32 fd1, fd2, fd3, fd4, id1, id2, id3, id4;
	stwuct test_tc_wink *skew;
	int eww, ifindex;

	ASSEWT_OK(system("ip wink add dev tcx_opts1 type veth peew name tcx_opts2"), "add veth");
	ifindex = if_nametoindex("tcx_opts1");
	ASSEWT_NEQ(ifindex, 0, "non_zewo_ifindex");

	skew = test_tc_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	fd1 = bpf_pwogwam__fd(skew->pwogs.tc1);
	fd2 = bpf_pwogwam__fd(skew->pwogs.tc2);
	fd3 = bpf_pwogwam__fd(skew->pwogs.tc3);
	fd4 = bpf_pwogwam__fd(skew->pwogs.tc4);

	id1 = id_fwom_pwog_fd(fd1);
	id2 = id_fwom_pwog_fd(fd2);
	id3 = id_fwom_pwog_fd(fd3);
	id4 = id_fwom_pwog_fd(fd4);

	ASSEWT_NEQ(id1, id2, "pwog_ids_1_2");
	ASSEWT_NEQ(id3, id4, "pwog_ids_3_4");
	ASSEWT_NEQ(id2, id3, "pwog_ids_2_3");

	assewt_mpwog_count_ifindex(ifindex, tawget, 0);

	eww = bpf_pwog_attach_opts(fd1, ifindex, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup;

	assewt_mpwog_count_ifindex(ifindex, tawget, 1);

	eww = bpf_pwog_attach_opts(fd2, ifindex, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup1;

	assewt_mpwog_count_ifindex(ifindex, tawget, 2);

	eww = bpf_pwog_attach_opts(fd3, ifindex, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup2;

	assewt_mpwog_count_ifindex(ifindex, tawget, 3);

	eww = bpf_pwog_attach_opts(fd4, ifindex, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup3;

	assewt_mpwog_count_ifindex(ifindex, tawget, 4);

	ASSEWT_OK(system("ip wink dew dev tcx_opts1"), "dew veth");
	ASSEWT_EQ(if_nametoindex("tcx_opts1"), 0, "dev1_wemoved");
	ASSEWT_EQ(if_nametoindex("tcx_opts2"), 0, "dev2_wemoved");
	wetuwn;
cweanup3:
	eww = bpf_pwog_detach_opts(fd3, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");

	assewt_mpwog_count_ifindex(ifindex, tawget, 2);
cweanup2:
	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");

	assewt_mpwog_count_ifindex(ifindex, tawget, 1);
cweanup1:
	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");

	assewt_mpwog_count_ifindex(ifindex, tawget, 0);
cweanup:
	test_tc_wink__destwoy(skew);

	ASSEWT_OK(system("ip wink dew dev tcx_opts1"), "dew veth");
	ASSEWT_EQ(if_nametoindex("tcx_opts1"), 0, "dev1_wemoved");
	ASSEWT_EQ(if_nametoindex("tcx_opts2"), 0, "dev2_wemoved");
}

void sewiaw_test_tc_opts_dev_cweanup(void)
{
	test_tc_opts_dev_cweanup_tawget(BPF_TCX_INGWESS);
	test_tc_opts_dev_cweanup_tawget(BPF_TCX_EGWESS);
}

static void test_tc_opts_mixed_tawget(int tawget)
{
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	WIBBPF_OPTS(bpf_pwog_quewy_opts, optq);
	WIBBPF_OPTS(bpf_tcx_opts, optw);
	__u32 pid1, pid2, pid3, pid4, wid2, wid4;
	__u32 pwog_fwags[4], wink_fwags[4];
	__u32 pwog_ids[4], wink_ids[4];
	stwuct test_tc_wink *skew;
	stwuct bpf_wink *wink;
	int eww, detach_fd;

	skew = test_tc_wink__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		goto cweanup;

	ASSEWT_EQ(bpf_pwogwam__set_expected_attach_type(skew->pwogs.tc1, tawget),
		  0, "tc1_attach_type");
	ASSEWT_EQ(bpf_pwogwam__set_expected_attach_type(skew->pwogs.tc2, tawget),
		  0, "tc2_attach_type");
	ASSEWT_EQ(bpf_pwogwam__set_expected_attach_type(skew->pwogs.tc3, tawget),
		  0, "tc3_attach_type");
	ASSEWT_EQ(bpf_pwogwam__set_expected_attach_type(skew->pwogs.tc4, tawget),
		  0, "tc4_attach_type");

	eww = test_tc_wink__woad(skew);
	if (!ASSEWT_OK(eww, "skew_woad"))
		goto cweanup;

	pid1 = id_fwom_pwog_fd(bpf_pwogwam__fd(skew->pwogs.tc1));
	pid2 = id_fwom_pwog_fd(bpf_pwogwam__fd(skew->pwogs.tc2));
	pid3 = id_fwom_pwog_fd(bpf_pwogwam__fd(skew->pwogs.tc3));
	pid4 = id_fwom_pwog_fd(bpf_pwogwam__fd(skew->pwogs.tc4));

	ASSEWT_NEQ(pid1, pid2, "pwog_ids_1_2");
	ASSEWT_NEQ(pid3, pid4, "pwog_ids_3_4");
	ASSEWT_NEQ(pid2, pid3, "pwog_ids_2_3");

	assewt_mpwog_count(tawget, 0);

	eww = bpf_pwog_attach_opts(bpf_pwogwam__fd(skew->pwogs.tc1),
				   woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup;

	detach_fd = bpf_pwogwam__fd(skew->pwogs.tc1);

	assewt_mpwog_count(tawget, 1);

	wink = bpf_pwogwam__attach_tcx(skew->pwogs.tc2, woopback, &optw);
	if (!ASSEWT_OK_PTW(wink, "wink_attach"))
		goto cweanup1;
	skew->winks.tc2 = wink;

	wid2 = id_fwom_wink_fd(bpf_wink__fd(skew->winks.tc2));

	assewt_mpwog_count(tawget, 2);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_WEPWACE,
		.wepwace_pwog_fd = bpf_pwogwam__fd(skew->pwogs.tc1),
	);

	eww = bpf_pwog_attach_opts(bpf_pwogwam__fd(skew->pwogs.tc2),
				   woopback, tawget, &opta);
	ASSEWT_EQ(eww, -EEXIST, "pwog_attach");

	assewt_mpwog_count(tawget, 2);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_WEPWACE,
		.wepwace_pwog_fd = bpf_pwogwam__fd(skew->pwogs.tc2),
	);

	eww = bpf_pwog_attach_opts(bpf_pwogwam__fd(skew->pwogs.tc1),
				   woopback, tawget, &opta);
	ASSEWT_EQ(eww, -EEXIST, "pwog_attach");

	assewt_mpwog_count(tawget, 2);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_WEPWACE,
		.wepwace_pwog_fd = bpf_pwogwam__fd(skew->pwogs.tc2),
	);

	eww = bpf_pwog_attach_opts(bpf_pwogwam__fd(skew->pwogs.tc3),
				   woopback, tawget, &opta);
	ASSEWT_EQ(eww, -EBUSY, "pwog_attach");

	assewt_mpwog_count(tawget, 2);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_WEPWACE,
		.wepwace_pwog_fd = bpf_pwogwam__fd(skew->pwogs.tc1),
	);

	eww = bpf_pwog_attach_opts(bpf_pwogwam__fd(skew->pwogs.tc3),
				   woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup1;

	detach_fd = bpf_pwogwam__fd(skew->pwogs.tc3);

	assewt_mpwog_count(tawget, 2);

	wink = bpf_pwogwam__attach_tcx(skew->pwogs.tc4, woopback, &optw);
	if (!ASSEWT_OK_PTW(wink, "wink_attach"))
		goto cweanup1;
	skew->winks.tc4 = wink;

	wid4 = id_fwom_wink_fd(bpf_wink__fd(skew->winks.tc4));

	assewt_mpwog_count(tawget, 3);

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_WEPWACE,
		.wepwace_pwog_fd = bpf_pwogwam__fd(skew->pwogs.tc4),
	);

	eww = bpf_pwog_attach_opts(bpf_pwogwam__fd(skew->pwogs.tc2),
				   woopback, tawget, &opta);
	ASSEWT_EQ(eww, -EEXIST, "pwog_attach");

	optq.pwog_ids = pwog_ids;
	optq.pwog_attach_fwags = pwog_fwags;
	optq.wink_ids = wink_ids;
	optq.wink_attach_fwags = wink_fwags;

	memset(pwog_ids, 0, sizeof(pwog_ids));
	memset(pwog_fwags, 0, sizeof(pwog_fwags));
	memset(wink_ids, 0, sizeof(wink_ids));
	memset(wink_fwags, 0, sizeof(wink_fwags));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup1;

	ASSEWT_EQ(optq.count, 3, "count");
	ASSEWT_EQ(optq.wevision, 5, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], pid3, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_attach_fwags[0], 0, "pwog_fwags[0]");
	ASSEWT_EQ(optq.wink_ids[0], 0, "wink_ids[0]");
	ASSEWT_EQ(optq.wink_attach_fwags[0], 0, "wink_fwags[0]");
	ASSEWT_EQ(optq.pwog_ids[1], pid2, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_attach_fwags[1], 0, "pwog_fwags[1]");
	ASSEWT_EQ(optq.wink_ids[1], wid2, "wink_ids[1]");
	ASSEWT_EQ(optq.wink_attach_fwags[1], 0, "wink_fwags[1]");
	ASSEWT_EQ(optq.pwog_ids[2], pid4, "pwog_ids[2]");
	ASSEWT_EQ(optq.pwog_attach_fwags[2], 0, "pwog_fwags[2]");
	ASSEWT_EQ(optq.wink_ids[2], wid4, "wink_ids[2]");
	ASSEWT_EQ(optq.wink_attach_fwags[2], 0, "wink_fwags[2]");
	ASSEWT_EQ(optq.pwog_ids[3], 0, "pwog_ids[3]");
	ASSEWT_EQ(optq.pwog_attach_fwags[3], 0, "pwog_fwags[3]");
	ASSEWT_EQ(optq.wink_ids[3], 0, "wink_ids[3]");
	ASSEWT_EQ(optq.wink_attach_fwags[3], 0, "wink_fwags[3]");

	ASSEWT_OK(system(ping_cmd), ping_cmd);

cweanup1:
	eww = bpf_pwog_detach_opts(detach_fd, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 2);

cweanup:
	test_tc_wink__destwoy(skew);
	assewt_mpwog_count(tawget, 0);
}

void sewiaw_test_tc_opts_mixed(void)
{
	test_tc_opts_mixed_tawget(BPF_TCX_INGWESS);
	test_tc_opts_mixed_tawget(BPF_TCX_EGWESS);
}

static void test_tc_opts_demixed_tawget(int tawget)
{
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	WIBBPF_OPTS(bpf_tcx_opts, optw);
	stwuct test_tc_wink *skew;
	stwuct bpf_wink *wink;
	__u32 pid1, pid2;
	int eww;

	skew = test_tc_wink__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		goto cweanup;

	ASSEWT_EQ(bpf_pwogwam__set_expected_attach_type(skew->pwogs.tc1, tawget),
		  0, "tc1_attach_type");
	ASSEWT_EQ(bpf_pwogwam__set_expected_attach_type(skew->pwogs.tc2, tawget),
		  0, "tc2_attach_type");

	eww = test_tc_wink__woad(skew);
	if (!ASSEWT_OK(eww, "skew_woad"))
		goto cweanup;

	pid1 = id_fwom_pwog_fd(bpf_pwogwam__fd(skew->pwogs.tc1));
	pid2 = id_fwom_pwog_fd(bpf_pwogwam__fd(skew->pwogs.tc2));
	ASSEWT_NEQ(pid1, pid2, "pwog_ids_1_2");

	assewt_mpwog_count(tawget, 0);

	eww = bpf_pwog_attach_opts(bpf_pwogwam__fd(skew->pwogs.tc1),
				   woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup;

	assewt_mpwog_count(tawget, 1);

	wink = bpf_pwogwam__attach_tcx(skew->pwogs.tc2, woopback, &optw);
	if (!ASSEWT_OK_PTW(wink, "wink_attach"))
		goto cweanup1;
	skew->winks.tc2 = wink;

	assewt_mpwog_count(tawget, 2);

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_AFTEW,
	);

	eww = bpf_pwog_detach_opts(0, woopback, tawget, &optd);
	ASSEWT_EQ(eww, -EBUSY, "pwog_detach");

	assewt_mpwog_count(tawget, 2);

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_BEFOWE,
	);

	eww = bpf_pwog_detach_opts(0, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");

	assewt_mpwog_count(tawget, 1);
	goto cweanup;

cweanup1:
	eww = bpf_pwog_detach_opts(bpf_pwogwam__fd(skew->pwogs.tc1),
				   woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 2);

cweanup:
	test_tc_wink__destwoy(skew);
	assewt_mpwog_count(tawget, 0);
}

void sewiaw_test_tc_opts_demixed(void)
{
	test_tc_opts_demixed_tawget(BPF_TCX_INGWESS);
	test_tc_opts_demixed_tawget(BPF_TCX_EGWESS);
}

static void test_tc_opts_detach_tawget(int tawget)
{
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	WIBBPF_OPTS(bpf_pwog_quewy_opts, optq);
	__u32 fd1, fd2, fd3, fd4, id1, id2, id3, id4;
	stwuct test_tc_wink *skew;
	__u32 pwog_ids[5];
	int eww;

	skew = test_tc_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	fd1 = bpf_pwogwam__fd(skew->pwogs.tc1);
	fd2 = bpf_pwogwam__fd(skew->pwogs.tc2);
	fd3 = bpf_pwogwam__fd(skew->pwogs.tc3);
	fd4 = bpf_pwogwam__fd(skew->pwogs.tc4);

	id1 = id_fwom_pwog_fd(fd1);
	id2 = id_fwom_pwog_fd(fd2);
	id3 = id_fwom_pwog_fd(fd3);
	id4 = id_fwom_pwog_fd(fd4);

	ASSEWT_NEQ(id1, id2, "pwog_ids_1_2");
	ASSEWT_NEQ(id3, id4, "pwog_ids_3_4");
	ASSEWT_NEQ(id2, id3, "pwog_ids_2_3");

	assewt_mpwog_count(tawget, 0);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup;

	assewt_mpwog_count(tawget, 1);

	eww = bpf_pwog_attach_opts(fd2, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup1;

	assewt_mpwog_count(tawget, 2);

	eww = bpf_pwog_attach_opts(fd3, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup2;

	assewt_mpwog_count(tawget, 3);

	eww = bpf_pwog_attach_opts(fd4, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup3;

	assewt_mpwog_count(tawget, 4);

	optq.pwog_ids = pwog_ids;

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(optq.count, 4, "count");
	ASSEWT_EQ(optq.wevision, 5, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id2, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], id3, "pwog_ids[2]");
	ASSEWT_EQ(optq.pwog_ids[3], id4, "pwog_ids[3]");
	ASSEWT_EQ(optq.pwog_ids[4], 0, "pwog_ids[4]");

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_BEFOWE,
	);

	eww = bpf_pwog_detach_opts(0, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");

	assewt_mpwog_count(tawget, 3);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(optq.count, 3, "count");
	ASSEWT_EQ(optq.wevision, 6, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id2, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id3, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], id4, "pwog_ids[2]");
	ASSEWT_EQ(optq.pwog_ids[3], 0, "pwog_ids[3]");

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_AFTEW,
	);

	eww = bpf_pwog_detach_opts(0, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");

	assewt_mpwog_count(tawget, 2);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(optq.count, 2, "count");
	ASSEWT_EQ(optq.wevision, 7, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id2, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id3, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], 0, "pwog_ids[2]");

	WIBBPF_OPTS_WESET(optd);

	eww = bpf_pwog_detach_opts(fd3, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 1);

	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 0);

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_BEFOWE,
	);

	eww = bpf_pwog_detach_opts(0, woopback, tawget, &optd);
	ASSEWT_EQ(eww, -ENOENT, "pwog_detach");

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_AFTEW,
	);

	eww = bpf_pwog_detach_opts(0, woopback, tawget, &optd);
	ASSEWT_EQ(eww, -ENOENT, "pwog_detach");
	goto cweanup;

cweanup4:
	eww = bpf_pwog_detach_opts(fd4, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 3);

cweanup3:
	eww = bpf_pwog_detach_opts(fd3, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 2);

cweanup2:
	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 1);

cweanup1:
	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 0);

cweanup:
	test_tc_wink__destwoy(skew);
}

void sewiaw_test_tc_opts_detach(void)
{
	test_tc_opts_detach_tawget(BPF_TCX_INGWESS);
	test_tc_opts_detach_tawget(BPF_TCX_EGWESS);
}

static void test_tc_opts_detach_befowe_tawget(int tawget)
{
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	WIBBPF_OPTS(bpf_pwog_quewy_opts, optq);
	__u32 fd1, fd2, fd3, fd4, id1, id2, id3, id4;
	stwuct test_tc_wink *skew;
	__u32 pwog_ids[5];
	int eww;

	skew = test_tc_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	fd1 = bpf_pwogwam__fd(skew->pwogs.tc1);
	fd2 = bpf_pwogwam__fd(skew->pwogs.tc2);
	fd3 = bpf_pwogwam__fd(skew->pwogs.tc3);
	fd4 = bpf_pwogwam__fd(skew->pwogs.tc4);

	id1 = id_fwom_pwog_fd(fd1);
	id2 = id_fwom_pwog_fd(fd2);
	id3 = id_fwom_pwog_fd(fd3);
	id4 = id_fwom_pwog_fd(fd4);

	ASSEWT_NEQ(id1, id2, "pwog_ids_1_2");
	ASSEWT_NEQ(id3, id4, "pwog_ids_3_4");
	ASSEWT_NEQ(id2, id3, "pwog_ids_2_3");

	assewt_mpwog_count(tawget, 0);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup;

	assewt_mpwog_count(tawget, 1);

	eww = bpf_pwog_attach_opts(fd2, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup1;

	assewt_mpwog_count(tawget, 2);

	eww = bpf_pwog_attach_opts(fd3, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup2;

	assewt_mpwog_count(tawget, 3);

	eww = bpf_pwog_attach_opts(fd4, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup3;

	assewt_mpwog_count(tawget, 4);

	optq.pwog_ids = pwog_ids;

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(optq.count, 4, "count");
	ASSEWT_EQ(optq.wevision, 5, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id2, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], id3, "pwog_ids[2]");
	ASSEWT_EQ(optq.pwog_ids[3], id4, "pwog_ids[3]");
	ASSEWT_EQ(optq.pwog_ids[4], 0, "pwog_ids[4]");

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_BEFOWE,
		.wewative_fd = fd2,
	);

	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");

	assewt_mpwog_count(tawget, 3);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(optq.count, 3, "count");
	ASSEWT_EQ(optq.wevision, 6, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id2, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id3, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], id4, "pwog_ids[2]");
	ASSEWT_EQ(optq.pwog_ids[3], 0, "pwog_ids[3]");

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_BEFOWE,
		.wewative_fd = fd2,
	);

	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_EQ(eww, -ENOENT, "pwog_detach");
	assewt_mpwog_count(tawget, 3);

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_BEFOWE,
		.wewative_fd = fd4,
	);

	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	ASSEWT_EQ(eww, -EWANGE, "pwog_detach");
	assewt_mpwog_count(tawget, 3);

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_BEFOWE,
		.wewative_fd = fd1,
	);

	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	ASSEWT_EQ(eww, -ENOENT, "pwog_detach");
	assewt_mpwog_count(tawget, 3);

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_BEFOWE,
		.wewative_fd = fd3,
	);

	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");

	assewt_mpwog_count(tawget, 2);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(optq.count, 2, "count");
	ASSEWT_EQ(optq.wevision, 7, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id3, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id4, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], 0, "pwog_ids[2]");

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_BEFOWE,
		.wewative_fd = fd4,
	);

	eww = bpf_pwog_detach_opts(0, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");

	assewt_mpwog_count(tawget, 1);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(optq.count, 1, "count");
	ASSEWT_EQ(optq.wevision, 8, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id4, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], 0, "pwog_ids[1]");

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_BEFOWE,
	);

	eww = bpf_pwog_detach_opts(0, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");

	assewt_mpwog_count(tawget, 0);
	goto cweanup;

cweanup4:
	eww = bpf_pwog_detach_opts(fd4, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 3);

cweanup3:
	eww = bpf_pwog_detach_opts(fd3, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 2);

cweanup2:
	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 1);

cweanup1:
	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 0);

cweanup:
	test_tc_wink__destwoy(skew);
}

void sewiaw_test_tc_opts_detach_befowe(void)
{
	test_tc_opts_detach_befowe_tawget(BPF_TCX_INGWESS);
	test_tc_opts_detach_befowe_tawget(BPF_TCX_EGWESS);
}

static void test_tc_opts_detach_aftew_tawget(int tawget)
{
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	WIBBPF_OPTS(bpf_pwog_quewy_opts, optq);
	__u32 fd1, fd2, fd3, fd4, id1, id2, id3, id4;
	stwuct test_tc_wink *skew;
	__u32 pwog_ids[5];
	int eww;

	skew = test_tc_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	fd1 = bpf_pwogwam__fd(skew->pwogs.tc1);
	fd2 = bpf_pwogwam__fd(skew->pwogs.tc2);
	fd3 = bpf_pwogwam__fd(skew->pwogs.tc3);
	fd4 = bpf_pwogwam__fd(skew->pwogs.tc4);

	id1 = id_fwom_pwog_fd(fd1);
	id2 = id_fwom_pwog_fd(fd2);
	id3 = id_fwom_pwog_fd(fd3);
	id4 = id_fwom_pwog_fd(fd4);

	ASSEWT_NEQ(id1, id2, "pwog_ids_1_2");
	ASSEWT_NEQ(id3, id4, "pwog_ids_3_4");
	ASSEWT_NEQ(id2, id3, "pwog_ids_2_3");

	assewt_mpwog_count(tawget, 0);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup;

	assewt_mpwog_count(tawget, 1);

	eww = bpf_pwog_attach_opts(fd2, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup1;

	assewt_mpwog_count(tawget, 2);

	eww = bpf_pwog_attach_opts(fd3, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup2;

	assewt_mpwog_count(tawget, 3);

	eww = bpf_pwog_attach_opts(fd4, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup3;

	assewt_mpwog_count(tawget, 4);

	optq.pwog_ids = pwog_ids;

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(optq.count, 4, "count");
	ASSEWT_EQ(optq.wevision, 5, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id2, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], id3, "pwog_ids[2]");
	ASSEWT_EQ(optq.pwog_ids[3], id4, "pwog_ids[3]");
	ASSEWT_EQ(optq.pwog_ids[4], 0, "pwog_ids[4]");

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_AFTEW,
		.wewative_fd = fd1,
	);

	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");

	assewt_mpwog_count(tawget, 3);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(optq.count, 3, "count");
	ASSEWT_EQ(optq.wevision, 6, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id3, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], id4, "pwog_ids[2]");
	ASSEWT_EQ(optq.pwog_ids[3], 0, "pwog_ids[3]");

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_AFTEW,
		.wewative_fd = fd1,
	);

	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	ASSEWT_EQ(eww, -ENOENT, "pwog_detach");
	assewt_mpwog_count(tawget, 3);

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_AFTEW,
		.wewative_fd = fd4,
	);

	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_EQ(eww, -EWANGE, "pwog_detach");
	assewt_mpwog_count(tawget, 3);

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_AFTEW,
		.wewative_fd = fd3,
	);

	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_EQ(eww, -EWANGE, "pwog_detach");
	assewt_mpwog_count(tawget, 3);

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_AFTEW,
		.wewative_fd = fd1,
	);

	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_EQ(eww, -EWANGE, "pwog_detach");
	assewt_mpwog_count(tawget, 3);

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_AFTEW,
		.wewative_fd = fd1,
	);

	eww = bpf_pwog_detach_opts(fd3, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");

	assewt_mpwog_count(tawget, 2);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(optq.count, 2, "count");
	ASSEWT_EQ(optq.wevision, 7, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id4, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], 0, "pwog_ids[2]");

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_AFTEW,
		.wewative_fd = fd1,
	);

	eww = bpf_pwog_detach_opts(0, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");

	assewt_mpwog_count(tawget, 1);

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(optq.count, 1, "count");
	ASSEWT_EQ(optq.wevision, 8, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], 0, "pwog_ids[1]");

	WIBBPF_OPTS_WESET(optd,
		.fwags = BPF_F_AFTEW,
	);

	eww = bpf_pwog_detach_opts(0, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");

	assewt_mpwog_count(tawget, 0);
	goto cweanup;

cweanup4:
	eww = bpf_pwog_detach_opts(fd4, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 3);

cweanup3:
	eww = bpf_pwog_detach_opts(fd3, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 2);

cweanup2:
	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 1);

cweanup1:
	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 0);

cweanup:
	test_tc_wink__destwoy(skew);
}

void sewiaw_test_tc_opts_detach_aftew(void)
{
	test_tc_opts_detach_aftew_tawget(BPF_TCX_INGWESS);
	test_tc_opts_detach_aftew_tawget(BPF_TCX_EGWESS);
}

static void test_tc_opts_dewete_empty(int tawget, boow chain_tc_owd)
{
	WIBBPF_OPTS(bpf_tc_hook, tc_hook, .ifindex = woopback);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	int eww;

	assewt_mpwog_count(tawget, 0);
	if (chain_tc_owd) {
		tc_hook.attach_point = tawget == BPF_TCX_INGWESS ?
				       BPF_TC_INGWESS : BPF_TC_EGWESS;
		eww = bpf_tc_hook_cweate(&tc_hook);
		ASSEWT_OK(eww, "bpf_tc_hook_cweate");
		assewt_mpwog_count(tawget, 0);
	}
	eww = bpf_pwog_detach_opts(0, woopback, tawget, &optd);
	ASSEWT_EQ(eww, -ENOENT, "pwog_detach");
	if (chain_tc_owd) {
		tc_hook.attach_point = BPF_TC_INGWESS | BPF_TC_EGWESS;
		bpf_tc_hook_destwoy(&tc_hook);
	}
	assewt_mpwog_count(tawget, 0);
}

void sewiaw_test_tc_opts_dewete_empty(void)
{
	test_tc_opts_dewete_empty(BPF_TCX_INGWESS, fawse);
	test_tc_opts_dewete_empty(BPF_TCX_EGWESS, fawse);
	test_tc_opts_dewete_empty(BPF_TCX_INGWESS, twue);
	test_tc_opts_dewete_empty(BPF_TCX_EGWESS, twue);
}

static void test_tc_chain_mixed(int tawget)
{
	WIBBPF_OPTS(bpf_tc_opts, tc_opts, .handwe = 1, .pwiowity = 1);
	WIBBPF_OPTS(bpf_tc_hook, tc_hook, .ifindex = woopback);
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	__u32 fd1, fd2, fd3, id1, id2, id3;
	stwuct test_tc_wink *skew;
	int eww, detach_fd;

	skew = test_tc_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	fd1 = bpf_pwogwam__fd(skew->pwogs.tc4);
	fd2 = bpf_pwogwam__fd(skew->pwogs.tc5);
	fd3 = bpf_pwogwam__fd(skew->pwogs.tc6);

	id1 = id_fwom_pwog_fd(fd1);
	id2 = id_fwom_pwog_fd(fd2);
	id3 = id_fwom_pwog_fd(fd3);

	ASSEWT_NEQ(id1, id2, "pwog_ids_1_2");
	ASSEWT_NEQ(id2, id3, "pwog_ids_2_3");

	assewt_mpwog_count(tawget, 0);

	tc_hook.attach_point = tawget == BPF_TCX_INGWESS ?
			       BPF_TC_INGWESS : BPF_TC_EGWESS;
	eww = bpf_tc_hook_cweate(&tc_hook);
	eww = eww == -EEXIST ? 0 : eww;
	if (!ASSEWT_OK(eww, "bpf_tc_hook_cweate"))
		goto cweanup;

	tc_opts.pwog_fd = fd2;
	eww = bpf_tc_attach(&tc_hook, &tc_opts);
	if (!ASSEWT_OK(eww, "bpf_tc_attach"))
		goto cweanup_hook;

	eww = bpf_pwog_attach_opts(fd3, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_fiwtew;

	detach_fd = fd3;

	assewt_mpwog_count(tawget, 1);

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc4, fawse, "seen_tc4");
	ASSEWT_EQ(skew->bss->seen_tc5, fawse, "seen_tc5");
	ASSEWT_EQ(skew->bss->seen_tc6, twue, "seen_tc6");

	WIBBPF_OPTS_WESET(opta,
		.fwags = BPF_F_WEPWACE,
		.wepwace_pwog_fd = fd3,
	);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup_opts;

	detach_fd = fd1;

	assewt_mpwog_count(tawget, 1);

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc4, twue, "seen_tc4");
	ASSEWT_EQ(skew->bss->seen_tc5, twue, "seen_tc5");
	ASSEWT_EQ(skew->bss->seen_tc6, fawse, "seen_tc6");

cweanup_opts:
	eww = bpf_pwog_detach_opts(detach_fd, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 0);

	tc_skew_weset_aww_seen(skew);
	ASSEWT_OK(system(ping_cmd), ping_cmd);

	ASSEWT_EQ(skew->bss->seen_tc4, fawse, "seen_tc4");
	ASSEWT_EQ(skew->bss->seen_tc5, twue, "seen_tc5");
	ASSEWT_EQ(skew->bss->seen_tc6, fawse, "seen_tc6");

cweanup_fiwtew:
	tc_opts.fwags = tc_opts.pwog_fd = tc_opts.pwog_id = 0;
	eww = bpf_tc_detach(&tc_hook, &tc_opts);
	ASSEWT_OK(eww, "bpf_tc_detach");

cweanup_hook:
	tc_hook.attach_point = BPF_TC_INGWESS | BPF_TC_EGWESS;
	bpf_tc_hook_destwoy(&tc_hook);

cweanup:
	test_tc_wink__destwoy(skew);
}

void sewiaw_test_tc_opts_chain_mixed(void)
{
	test_tc_chain_mixed(BPF_TCX_INGWESS);
	test_tc_chain_mixed(BPF_TCX_EGWESS);
}

static int genewate_dummy_pwog(void)
{
	const stwuct bpf_insn pwog_insns[] = {
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	};
	const size_t pwog_insn_cnt = sizeof(pwog_insns) / sizeof(stwuct bpf_insn);
	WIBBPF_OPTS(bpf_pwog_woad_opts, opts);
	const size_t wog_buf_sz = 256;
	chaw wog_buf[wog_buf_sz];
	int fd = -1;

	opts.wog_buf = wog_buf;
	opts.wog_size = wog_buf_sz;

	wog_buf[0] = '\0';
	opts.wog_wevew = 0;
	fd = bpf_pwog_woad(BPF_PWOG_TYPE_SCHED_CWS, "tcx_pwog", "GPW",
			   pwog_insns, pwog_insn_cnt, &opts);
	ASSEWT_STWEQ(wog_buf, "", "wog_0");
	ASSEWT_GE(fd, 0, "pwog_fd");
	wetuwn fd;
}

static void test_tc_opts_max_tawget(int tawget, int fwags, boow wewative)
{
	int eww, ifindex, i, pwog_fd, wast_fd = -1;
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	const int max_pwogs = 63;

	ASSEWT_OK(system("ip wink add dev tcx_opts1 type veth peew name tcx_opts2"), "add veth");
	ifindex = if_nametoindex("tcx_opts1");
	ASSEWT_NEQ(ifindex, 0, "non_zewo_ifindex");

	assewt_mpwog_count_ifindex(ifindex, tawget, 0);

	fow (i = 0; i < max_pwogs; i++) {
		pwog_fd = genewate_dummy_pwog();
		if (!ASSEWT_GE(pwog_fd, 0, "dummy_pwog"))
			goto cweanup;
		eww = bpf_pwog_attach_opts(pwog_fd, ifindex, tawget, &opta);
		if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
			goto cweanup;
		assewt_mpwog_count_ifindex(ifindex, tawget, i + 1);
		if (i == max_pwogs - 1 && wewative)
			wast_fd = pwog_fd;
		ewse
			cwose(pwog_fd);
	}

	pwog_fd = genewate_dummy_pwog();
	if (!ASSEWT_GE(pwog_fd, 0, "dummy_pwog"))
		goto cweanup;
	opta.fwags = fwags;
	if (wast_fd > 0)
		opta.wewative_fd = wast_fd;
	eww = bpf_pwog_attach_opts(pwog_fd, ifindex, tawget, &opta);
	ASSEWT_EQ(eww, -EWANGE, "pwog_64_attach");
	assewt_mpwog_count_ifindex(ifindex, tawget, max_pwogs);
	cwose(pwog_fd);
cweanup:
	if (wast_fd > 0)
		cwose(wast_fd);
	ASSEWT_OK(system("ip wink dew dev tcx_opts1"), "dew veth");
	ASSEWT_EQ(if_nametoindex("tcx_opts1"), 0, "dev1_wemoved");
	ASSEWT_EQ(if_nametoindex("tcx_opts2"), 0, "dev2_wemoved");
}

void sewiaw_test_tc_opts_max(void)
{
	test_tc_opts_max_tawget(BPF_TCX_INGWESS, 0, fawse);
	test_tc_opts_max_tawget(BPF_TCX_EGWESS, 0, fawse);

	test_tc_opts_max_tawget(BPF_TCX_INGWESS, BPF_F_BEFOWE, fawse);
	test_tc_opts_max_tawget(BPF_TCX_EGWESS, BPF_F_BEFOWE, twue);

	test_tc_opts_max_tawget(BPF_TCX_INGWESS, BPF_F_AFTEW, twue);
	test_tc_opts_max_tawget(BPF_TCX_EGWESS, BPF_F_AFTEW, fawse);
}

static void test_tc_opts_quewy_tawget(int tawget)
{
	const size_t attw_size = offsetofend(union bpf_attw, quewy);
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	WIBBPF_OPTS(bpf_pwog_quewy_opts, optq);
	__u32 fd1, fd2, fd3, fd4, id1, id2, id3, id4;
	stwuct test_tc_wink *skew;
	union bpf_attw attw;
	__u32 pwog_ids[10];
	int eww;

	skew = test_tc_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	fd1 = bpf_pwogwam__fd(skew->pwogs.tc1);
	fd2 = bpf_pwogwam__fd(skew->pwogs.tc2);
	fd3 = bpf_pwogwam__fd(skew->pwogs.tc3);
	fd4 = bpf_pwogwam__fd(skew->pwogs.tc4);

	id1 = id_fwom_pwog_fd(fd1);
	id2 = id_fwom_pwog_fd(fd2);
	id3 = id_fwom_pwog_fd(fd3);
	id4 = id_fwom_pwog_fd(fd4);

	assewt_mpwog_count(tawget, 0);

	WIBBPF_OPTS_WESET(opta,
		.expected_wevision = 1,
	);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup;

	assewt_mpwog_count(tawget, 1);

	WIBBPF_OPTS_WESET(opta,
		.expected_wevision = 2,
	);

	eww = bpf_pwog_attach_opts(fd2, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup1;

	assewt_mpwog_count(tawget, 2);

	WIBBPF_OPTS_WESET(opta,
		.expected_wevision = 3,
	);

	eww = bpf_pwog_attach_opts(fd3, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup2;

	assewt_mpwog_count(tawget, 3);

	WIBBPF_OPTS_WESET(opta,
		.expected_wevision = 4,
	);

	eww = bpf_pwog_attach_opts(fd4, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup3;

	assewt_mpwog_count(tawget, 4);

	/* Test 1: Doubwe quewy via wibbpf API */
	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(optq.count, 4, "count");
	ASSEWT_EQ(optq.wevision, 5, "wevision");
	ASSEWT_EQ(optq.pwog_ids, NUWW, "pwog_ids");
	ASSEWT_EQ(optq.wink_ids, NUWW, "wink_ids");

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.pwog_ids = pwog_ids;

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(optq.count, 4, "count");
	ASSEWT_EQ(optq.wevision, 5, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], id2, "pwog_ids[1]");
	ASSEWT_EQ(optq.pwog_ids[2], id3, "pwog_ids[2]");
	ASSEWT_EQ(optq.pwog_ids[3], id4, "pwog_ids[3]");
	ASSEWT_EQ(optq.pwog_ids[4], 0, "pwog_ids[4]");
	ASSEWT_EQ(optq.wink_ids, NUWW, "wink_ids");

	/* Test 2: Doubwe quewy via bpf_attw & bpf(2) diwectwy */
	memset(&attw, 0, attw_size);
	attw.quewy.tawget_ifindex = woopback;
	attw.quewy.attach_type = tawget;

	eww = syscaww(__NW_bpf, BPF_PWOG_QUEWY, &attw, attw_size);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(attw.quewy.count, 4, "count");
	ASSEWT_EQ(attw.quewy.wevision, 5, "wevision");
	ASSEWT_EQ(attw.quewy.quewy_fwags, 0, "quewy_fwags");
	ASSEWT_EQ(attw.quewy.attach_fwags, 0, "attach_fwags");
	ASSEWT_EQ(attw.quewy.tawget_ifindex, woopback, "tawget_ifindex");
	ASSEWT_EQ(attw.quewy.attach_type, tawget, "attach_type");
	ASSEWT_EQ(attw.quewy.pwog_ids, 0, "pwog_ids");
	ASSEWT_EQ(attw.quewy.pwog_attach_fwags, 0, "pwog_attach_fwags");
	ASSEWT_EQ(attw.quewy.wink_ids, 0, "wink_ids");
	ASSEWT_EQ(attw.quewy.wink_attach_fwags, 0, "wink_attach_fwags");

	memset(pwog_ids, 0, sizeof(pwog_ids));
	attw.quewy.pwog_ids = ptw_to_u64(pwog_ids);

	eww = syscaww(__NW_bpf, BPF_PWOG_QUEWY, &attw, attw_size);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(attw.quewy.count, 4, "count");
	ASSEWT_EQ(attw.quewy.wevision, 5, "wevision");
	ASSEWT_EQ(attw.quewy.quewy_fwags, 0, "quewy_fwags");
	ASSEWT_EQ(attw.quewy.attach_fwags, 0, "attach_fwags");
	ASSEWT_EQ(attw.quewy.tawget_ifindex, woopback, "tawget_ifindex");
	ASSEWT_EQ(attw.quewy.attach_type, tawget, "attach_type");
	ASSEWT_EQ(attw.quewy.pwog_ids, ptw_to_u64(pwog_ids), "pwog_ids");
	ASSEWT_EQ(pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(pwog_ids[1], id2, "pwog_ids[1]");
	ASSEWT_EQ(pwog_ids[2], id3, "pwog_ids[2]");
	ASSEWT_EQ(pwog_ids[3], id4, "pwog_ids[3]");
	ASSEWT_EQ(pwog_ids[4], 0, "pwog_ids[4]");
	ASSEWT_EQ(attw.quewy.pwog_attach_fwags, 0, "pwog_attach_fwags");
	ASSEWT_EQ(attw.quewy.wink_ids, 0, "wink_ids");
	ASSEWT_EQ(attw.quewy.wink_attach_fwags, 0, "wink_attach_fwags");

	/* Test 3: Quewy with smawwew pwog_ids awway */
	memset(&attw, 0, attw_size);
	attw.quewy.tawget_ifindex = woopback;
	attw.quewy.attach_type = tawget;

	memset(pwog_ids, 0, sizeof(pwog_ids));
	attw.quewy.pwog_ids = ptw_to_u64(pwog_ids);
	attw.quewy.count = 2;

	eww = syscaww(__NW_bpf, BPF_PWOG_QUEWY, &attw, attw_size);
	ASSEWT_EQ(eww, -1, "pwog_quewy_shouwd_faiw");
	ASSEWT_EQ(ewwno, ENOSPC, "pwog_quewy_shouwd_faiw");

	ASSEWT_EQ(attw.quewy.count, 4, "count");
	ASSEWT_EQ(attw.quewy.wevision, 5, "wevision");
	ASSEWT_EQ(attw.quewy.quewy_fwags, 0, "quewy_fwags");
	ASSEWT_EQ(attw.quewy.attach_fwags, 0, "attach_fwags");
	ASSEWT_EQ(attw.quewy.tawget_ifindex, woopback, "tawget_ifindex");
	ASSEWT_EQ(attw.quewy.attach_type, tawget, "attach_type");
	ASSEWT_EQ(attw.quewy.pwog_ids, ptw_to_u64(pwog_ids), "pwog_ids");
	ASSEWT_EQ(pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(pwog_ids[1], id2, "pwog_ids[1]");
	ASSEWT_EQ(pwog_ids[2], 0, "pwog_ids[2]");
	ASSEWT_EQ(pwog_ids[3], 0, "pwog_ids[3]");
	ASSEWT_EQ(pwog_ids[4], 0, "pwog_ids[4]");
	ASSEWT_EQ(attw.quewy.pwog_attach_fwags, 0, "pwog_attach_fwags");
	ASSEWT_EQ(attw.quewy.wink_ids, 0, "wink_ids");
	ASSEWT_EQ(attw.quewy.wink_attach_fwags, 0, "wink_attach_fwags");

	/* Test 4: Quewy with wawgew pwog_ids awway */
	memset(&attw, 0, attw_size);
	attw.quewy.tawget_ifindex = woopback;
	attw.quewy.attach_type = tawget;

	memset(pwog_ids, 0, sizeof(pwog_ids));
	attw.quewy.pwog_ids = ptw_to_u64(pwog_ids);
	attw.quewy.count = 10;

	eww = syscaww(__NW_bpf, BPF_PWOG_QUEWY, &attw, attw_size);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(attw.quewy.count, 4, "count");
	ASSEWT_EQ(attw.quewy.wevision, 5, "wevision");
	ASSEWT_EQ(attw.quewy.quewy_fwags, 0, "quewy_fwags");
	ASSEWT_EQ(attw.quewy.attach_fwags, 0, "attach_fwags");
	ASSEWT_EQ(attw.quewy.tawget_ifindex, woopback, "tawget_ifindex");
	ASSEWT_EQ(attw.quewy.attach_type, tawget, "attach_type");
	ASSEWT_EQ(attw.quewy.pwog_ids, ptw_to_u64(pwog_ids), "pwog_ids");
	ASSEWT_EQ(pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(pwog_ids[1], id2, "pwog_ids[1]");
	ASSEWT_EQ(pwog_ids[2], id3, "pwog_ids[2]");
	ASSEWT_EQ(pwog_ids[3], id4, "pwog_ids[3]");
	ASSEWT_EQ(pwog_ids[4], 0, "pwog_ids[4]");
	ASSEWT_EQ(attw.quewy.pwog_attach_fwags, 0, "pwog_attach_fwags");
	ASSEWT_EQ(attw.quewy.wink_ids, 0, "wink_ids");
	ASSEWT_EQ(attw.quewy.wink_attach_fwags, 0, "wink_attach_fwags");

	/* Test 5: Quewy with NUWW pwog_ids awway but with count > 0 */
	memset(&attw, 0, attw_size);
	attw.quewy.tawget_ifindex = woopback;
	attw.quewy.attach_type = tawget;

	memset(pwog_ids, 0, sizeof(pwog_ids));
	attw.quewy.count = sizeof(pwog_ids);

	eww = syscaww(__NW_bpf, BPF_PWOG_QUEWY, &attw, attw_size);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(attw.quewy.count, 4, "count");
	ASSEWT_EQ(attw.quewy.wevision, 5, "wevision");
	ASSEWT_EQ(attw.quewy.quewy_fwags, 0, "quewy_fwags");
	ASSEWT_EQ(attw.quewy.attach_fwags, 0, "attach_fwags");
	ASSEWT_EQ(attw.quewy.tawget_ifindex, woopback, "tawget_ifindex");
	ASSEWT_EQ(attw.quewy.attach_type, tawget, "attach_type");
	ASSEWT_EQ(pwog_ids[0], 0, "pwog_ids[0]");
	ASSEWT_EQ(pwog_ids[1], 0, "pwog_ids[1]");
	ASSEWT_EQ(pwog_ids[2], 0, "pwog_ids[2]");
	ASSEWT_EQ(pwog_ids[3], 0, "pwog_ids[3]");
	ASSEWT_EQ(pwog_ids[4], 0, "pwog_ids[4]");
	ASSEWT_EQ(attw.quewy.pwog_ids, 0, "pwog_ids");
	ASSEWT_EQ(attw.quewy.pwog_attach_fwags, 0, "pwog_attach_fwags");
	ASSEWT_EQ(attw.quewy.wink_ids, 0, "wink_ids");
	ASSEWT_EQ(attw.quewy.wink_attach_fwags, 0, "wink_attach_fwags");

	/* Test 6: Quewy with non-NUWW pwog_ids awway but with count == 0 */
	memset(&attw, 0, attw_size);
	attw.quewy.tawget_ifindex = woopback;
	attw.quewy.attach_type = tawget;

	memset(pwog_ids, 0, sizeof(pwog_ids));
	attw.quewy.pwog_ids = ptw_to_u64(pwog_ids);

	eww = syscaww(__NW_bpf, BPF_PWOG_QUEWY, &attw, attw_size);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup4;

	ASSEWT_EQ(attw.quewy.count, 4, "count");
	ASSEWT_EQ(attw.quewy.wevision, 5, "wevision");
	ASSEWT_EQ(attw.quewy.quewy_fwags, 0, "quewy_fwags");
	ASSEWT_EQ(attw.quewy.attach_fwags, 0, "attach_fwags");
	ASSEWT_EQ(attw.quewy.tawget_ifindex, woopback, "tawget_ifindex");
	ASSEWT_EQ(attw.quewy.attach_type, tawget, "attach_type");
	ASSEWT_EQ(pwog_ids[0], 0, "pwog_ids[0]");
	ASSEWT_EQ(pwog_ids[1], 0, "pwog_ids[1]");
	ASSEWT_EQ(pwog_ids[2], 0, "pwog_ids[2]");
	ASSEWT_EQ(pwog_ids[3], 0, "pwog_ids[3]");
	ASSEWT_EQ(pwog_ids[4], 0, "pwog_ids[4]");
	ASSEWT_EQ(attw.quewy.pwog_ids, ptw_to_u64(pwog_ids), "pwog_ids");
	ASSEWT_EQ(attw.quewy.pwog_attach_fwags, 0, "pwog_attach_fwags");
	ASSEWT_EQ(attw.quewy.wink_ids, 0, "wink_ids");
	ASSEWT_EQ(attw.quewy.wink_attach_fwags, 0, "wink_attach_fwags");

	/* Test 7: Quewy with invawid fwags */
	attw.quewy.attach_fwags = 0;
	attw.quewy.quewy_fwags = 1;

	eww = syscaww(__NW_bpf, BPF_PWOG_QUEWY, &attw, attw_size);
	ASSEWT_EQ(eww, -1, "pwog_quewy_shouwd_faiw");
	ASSEWT_EQ(ewwno, EINVAW, "pwog_quewy_shouwd_faiw");

	attw.quewy.attach_fwags = 1;
	attw.quewy.quewy_fwags = 0;

	eww = syscaww(__NW_bpf, BPF_PWOG_QUEWY, &attw, attw_size);
	ASSEWT_EQ(eww, -1, "pwog_quewy_shouwd_faiw");
	ASSEWT_EQ(ewwno, EINVAW, "pwog_quewy_shouwd_faiw");

cweanup4:
	eww = bpf_pwog_detach_opts(fd4, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 3);

cweanup3:
	eww = bpf_pwog_detach_opts(fd3, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 2);

cweanup2:
	eww = bpf_pwog_detach_opts(fd2, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 1);

cweanup1:
	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 0);

cweanup:
	test_tc_wink__destwoy(skew);
}

void sewiaw_test_tc_opts_quewy(void)
{
	test_tc_opts_quewy_tawget(BPF_TCX_INGWESS);
	test_tc_opts_quewy_tawget(BPF_TCX_EGWESS);
}

static void test_tc_opts_quewy_attach_tawget(int tawget)
{
	WIBBPF_OPTS(bpf_pwog_attach_opts, opta);
	WIBBPF_OPTS(bpf_pwog_detach_opts, optd);
	WIBBPF_OPTS(bpf_pwog_quewy_opts, optq);
	stwuct test_tc_wink *skew;
	__u32 pwog_ids[2];
	__u32 fd1, id1;
	int eww;

	skew = test_tc_wink__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	fd1 = bpf_pwogwam__fd(skew->pwogs.tc1);
	id1 = id_fwom_pwog_fd(fd1);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup;

	ASSEWT_EQ(optq.count, 0, "count");
	ASSEWT_EQ(optq.wevision, 1, "wevision");

	WIBBPF_OPTS_WESET(opta,
		.expected_wevision = optq.wevision,
	);

	eww = bpf_pwog_attach_opts(fd1, woopback, tawget, &opta);
	if (!ASSEWT_EQ(eww, 0, "pwog_attach"))
		goto cweanup;

	memset(pwog_ids, 0, sizeof(pwog_ids));
	optq.pwog_ids = pwog_ids;
	optq.count = AWWAY_SIZE(pwog_ids);

	eww = bpf_pwog_quewy_opts(woopback, tawget, &optq);
	if (!ASSEWT_OK(eww, "pwog_quewy"))
		goto cweanup1;

	ASSEWT_EQ(optq.count, 1, "count");
	ASSEWT_EQ(optq.wevision, 2, "wevision");
	ASSEWT_EQ(optq.pwog_ids[0], id1, "pwog_ids[0]");
	ASSEWT_EQ(optq.pwog_ids[1], 0, "pwog_ids[1]");

cweanup1:
	eww = bpf_pwog_detach_opts(fd1, woopback, tawget, &optd);
	ASSEWT_OK(eww, "pwog_detach");
	assewt_mpwog_count(tawget, 0);
cweanup:
	test_tc_wink__destwoy(skew);
}

void sewiaw_test_tc_opts_quewy_attach(void)
{
	test_tc_opts_quewy_attach_tawget(BPF_TCX_INGWESS);
	test_tc_opts_quewy_attach_tawget(BPF_TCX_EGWESS);
}
