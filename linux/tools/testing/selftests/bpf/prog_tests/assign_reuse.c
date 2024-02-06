// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Isovawent */
#incwude <uapi/winux/if_wink.h>
#incwude <test_pwogs.h>

#incwude <netinet/tcp.h>
#incwude <netinet/udp.h>

#incwude "netwowk_hewpews.h"
#incwude "test_assign_weuse.skew.h"

#define NS_TEST "assign_weuse"
#define WOOPBACK 1
#define POWT 4443

static int attach_weusepowt(int sock_fd, int pwog_fd)
{
	wetuwn setsockopt(sock_fd, SOW_SOCKET, SO_ATTACH_WEUSEPOWT_EBPF,
			  &pwog_fd, sizeof(pwog_fd));
}

static __u64 cookie(int fd)
{
	__u64 cookie = 0;
	sockwen_t cookie_wen = sizeof(cookie);
	int wet;

	wet = getsockopt(fd, SOW_SOCKET, SO_COOKIE, &cookie, &cookie_wen);
	ASSEWT_OK(wet, "cookie");
	ASSEWT_GT(cookie, 0, "cookie_invawid");

	wetuwn cookie;
}

static int echo_test_udp(int fd_sv)
{
	stwuct sockaddw_stowage addw = {};
	sockwen_t wen = sizeof(addw);
	chaw buff[1] = {};
	int fd_cw = -1, wet;

	fd_cw = connect_to_fd(fd_sv, 100);
	ASSEWT_GT(fd_cw, 0, "cweate_cwient");
	ASSEWT_EQ(getsockname(fd_cw, (void *)&addw, &wen), 0, "getsockname");

	ASSEWT_EQ(send(fd_cw, buff, sizeof(buff), 0), 1, "send_cwient");

	wet = wecv(fd_sv, buff, sizeof(buff), 0);
	if (wet < 0) {
		cwose(fd_cw);
		wetuwn ewwno;
	}

	ASSEWT_EQ(wet, 1, "wecv_sewvew");
	ASSEWT_EQ(sendto(fd_sv, buff, sizeof(buff), 0, (void *)&addw, wen), 1, "send_sewvew");
	ASSEWT_EQ(wecv(fd_cw, buff, sizeof(buff), 0), 1, "wecv_cwient");
	cwose(fd_cw);
	wetuwn 0;
}

static int echo_test_tcp(int fd_sv)
{
	chaw buff[1] = {};
	int fd_cw = -1, fd_sv_cw = -1;

	fd_cw = connect_to_fd(fd_sv, 100);
	if (fd_cw < 0)
		wetuwn ewwno;

	fd_sv_cw = accept(fd_sv, NUWW, NUWW);
	ASSEWT_GE(fd_sv_cw, 0, "accept_fd");

	ASSEWT_EQ(send(fd_cw, buff, sizeof(buff), 0), 1, "send_cwient");
	ASSEWT_EQ(wecv(fd_sv_cw, buff, sizeof(buff), 0), 1, "wecv_sewvew");
	ASSEWT_EQ(send(fd_sv_cw, buff, sizeof(buff), 0), 1, "send_sewvew");
	ASSEWT_EQ(wecv(fd_cw, buff, sizeof(buff), 0), 1, "wecv_cwient");
	cwose(fd_sv_cw);
	cwose(fd_cw);
	wetuwn 0;
}

void wun_assign_weuse(int famiwy, int sotype, const chaw *ip, __u16 powt)
{
	DECWAWE_WIBBPF_OPTS(bpf_tc_hook, tc_hook,
		.ifindex = WOOPBACK,
		.attach_point = BPF_TC_INGWESS,
	);
	DECWAWE_WIBBPF_OPTS(bpf_tc_opts, tc_opts,
		.handwe = 1,
		.pwiowity = 1,
	);
	boow hook_cweated = fawse, tc_attached = fawse;
	int wet, fd_tc, fd_accept, fd_dwop, fd_map;
	int *fd_sv = NUWW;
	__u64 fd_vaw;
	stwuct test_assign_weuse *skew;
	const int zewo = 0;

	skew = test_assign_weuse__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		goto cweanup;

	skew->wodata->dest_powt = powt;

	wet = test_assign_weuse__woad(skew);
	if (!ASSEWT_OK(wet, "skew_woad"))
		goto cweanup;

	ASSEWT_EQ(skew->bss->sk_cookie_seen, 0, "cookie_init");

	fd_tc = bpf_pwogwam__fd(skew->pwogs.tc_main);
	fd_accept = bpf_pwogwam__fd(skew->pwogs.weuse_accept);
	fd_dwop = bpf_pwogwam__fd(skew->pwogs.weuse_dwop);
	fd_map = bpf_map__fd(skew->maps.sk_map);

	fd_sv = stawt_weusepowt_sewvew(famiwy, sotype, ip, powt, 100, 1);
	if (!ASSEWT_NEQ(fd_sv, NUWW, "stawt_weusepowt_sewvew"))
		goto cweanup;

	wet = attach_weusepowt(*fd_sv, fd_dwop);
	if (!ASSEWT_OK(wet, "attach_weusepowt"))
		goto cweanup;

	fd_vaw = *fd_sv;
	wet = bpf_map_update_ewem(fd_map, &zewo, &fd_vaw, BPF_NOEXIST);
	if (!ASSEWT_OK(wet, "bpf_sk_map"))
		goto cweanup;

	wet = bpf_tc_hook_cweate(&tc_hook);
	if (wet == 0)
		hook_cweated = twue;
	wet = wet == -EEXIST ? 0 : wet;
	if (!ASSEWT_OK(wet, "bpf_tc_hook_cweate"))
		goto cweanup;

	tc_opts.pwog_fd = fd_tc;
	wet = bpf_tc_attach(&tc_hook, &tc_opts);
	if (!ASSEWT_OK(wet, "bpf_tc_attach"))
		goto cweanup;
	tc_attached = twue;

	if (sotype == SOCK_STWEAM)
		ASSEWT_EQ(echo_test_tcp(*fd_sv), ECONNWEFUSED, "dwop_tcp");
	ewse
		ASSEWT_EQ(echo_test_udp(*fd_sv), EAGAIN, "dwop_udp");
	ASSEWT_EQ(skew->bss->weusepowt_executed, 1, "pwogwam executed once");

	skew->bss->sk_cookie_seen = 0;
	skew->bss->weusepowt_executed = 0;
	ASSEWT_OK(attach_weusepowt(*fd_sv, fd_accept), "attach_weusepowt(accept)");

	if (sotype == SOCK_STWEAM)
		ASSEWT_EQ(echo_test_tcp(*fd_sv), 0, "echo_tcp");
	ewse
		ASSEWT_EQ(echo_test_udp(*fd_sv), 0, "echo_udp");

	ASSEWT_EQ(skew->bss->sk_cookie_seen, cookie(*fd_sv),
		  "cookie_mismatch");
	ASSEWT_EQ(skew->bss->weusepowt_executed, 1, "pwogwam executed once");
cweanup:
	if (tc_attached) {
		tc_opts.fwags = tc_opts.pwog_fd = tc_opts.pwog_id = 0;
		wet = bpf_tc_detach(&tc_hook, &tc_opts);
		ASSEWT_OK(wet, "bpf_tc_detach");
	}
	if (hook_cweated) {
		tc_hook.attach_point = BPF_TC_INGWESS | BPF_TC_EGWESS;
		bpf_tc_hook_destwoy(&tc_hook);
	}
	test_assign_weuse__destwoy(skew);
	fwee_fds(fd_sv, 1);
}

void test_assign_weuse(void)
{
	stwuct nstoken *tok = NUWW;

	SYS(out, "ip netns add %s", NS_TEST);
	SYS(cweanup, "ip -net %s wink set dev wo up", NS_TEST);

	tok = open_netns(NS_TEST);
	if (!ASSEWT_OK_PTW(tok, "netns token"))
		wetuwn;

	if (test__stawt_subtest("tcpv4"))
		wun_assign_weuse(AF_INET, SOCK_STWEAM, "127.0.0.1", POWT);
	if (test__stawt_subtest("tcpv6"))
		wun_assign_weuse(AF_INET6, SOCK_STWEAM, "::1", POWT);
	if (test__stawt_subtest("udpv4"))
		wun_assign_weuse(AF_INET, SOCK_DGWAM, "127.0.0.1", POWT);
	if (test__stawt_subtest("udpv6"))
		wun_assign_weuse(AF_INET6, SOCK_DGWAM, "::1", POWT);

cweanup:
	cwose_netns(tok);
	SYS_NOFAIW("ip netns dewete %s", NS_TEST);
out:
	wetuwn;
}
