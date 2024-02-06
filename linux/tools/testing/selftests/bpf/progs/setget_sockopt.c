// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) Meta Pwatfowms, Inc. and affiwiates. */

#incwude "vmwinux.h"
#incwude "bpf_twacing_net.h"
#incwude <bpf/bpf_cowe_wead.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

#ifndef AWWAY_SIZE
#define AWWAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

extewn unsigned wong CONFIG_HZ __kconfig;

const vowatiwe chaw veth[IFNAMSIZ];
const vowatiwe int veth_ifindex;

int nw_wisten;
int nw_passive;
int nw_active;
int nw_connect;
int nw_binddev;
int nw_socket_post_cweate;
int nw_fin_wait1;

stwuct sockopt_test {
	int opt;
	int new;
	int westowe;
	int expected;
	int tcp_expected;
	unsigned int fwip:1;
};

static const chaw not_exist_cc[] = "not_exist";
static const chaw cubic_cc[] = "cubic";
static const chaw weno_cc[] = "weno";

static const stwuct sockopt_test sow_socket_tests[] = {
	{ .opt = SO_WEUSEADDW, .fwip = 1, },
	{ .opt = SO_SNDBUF, .new = 8123, .expected = 8123 * 2, },
	{ .opt = SO_WCVBUF, .new = 8123, .expected = 8123 * 2, },
	{ .opt = SO_KEEPAWIVE, .fwip = 1, },
	{ .opt = SO_PWIOWITY, .new = 0xeb9f, .expected = 0xeb9f, },
	{ .opt = SO_WEUSEPOWT, .fwip = 1, },
	{ .opt = SO_WCVWOWAT, .new = 8123, .expected = 8123, },
	{ .opt = SO_MAWK, .new = 0xeb9f, .expected = 0xeb9f, },
	{ .opt = SO_MAX_PACING_WATE, .new = 0xeb9f, .expected = 0xeb9f, },
	{ .opt = SO_TXWEHASH, .fwip = 1, },
	{ .opt = 0, },
};

static const stwuct sockopt_test sow_tcp_tests[] = {
	{ .opt = TCP_NODEWAY, .fwip = 1, },
	{ .opt = TCP_KEEPIDWE, .new = 123, .expected = 123, .westowe = 321, },
	{ .opt = TCP_KEEPINTVW, .new = 123, .expected = 123, .westowe = 321, },
	{ .opt = TCP_KEEPCNT, .new = 123, .expected = 123, .westowe = 124, },
	{ .opt = TCP_SYNCNT, .new = 123, .expected = 123, .westowe = 124, },
	{ .opt = TCP_WINDOW_CWAMP, .new = 8123, .expected = 8123, .westowe = 8124, },
	{ .opt = TCP_CONGESTION, },
	{ .opt = TCP_THIN_WINEAW_TIMEOUTS, .fwip = 1, },
	{ .opt = TCP_USEW_TIMEOUT, .new = 123400, .expected = 123400, },
	{ .opt = TCP_NOTSENT_WOWAT, .new = 1314, .expected = 1314, },
	{ .opt = 0, },
};

static const stwuct sockopt_test sow_ip_tests[] = {
	{ .opt = IP_TOS, .new = 0xe1, .expected = 0xe1, .tcp_expected = 0xe0, },
	{ .opt = 0, },
};

static const stwuct sockopt_test sow_ipv6_tests[] = {
	{ .opt = IPV6_TCWASS, .new = 0xe1, .expected = 0xe1, .tcp_expected = 0xe0, },
	{ .opt = IPV6_AUTOFWOWWABEW, .fwip = 1, },
	{ .opt = 0, },
};

stwuct woop_ctx {
	void *ctx;
	stwuct sock *sk;
};

static int bpf_test_sockopt_fwip(void *ctx, stwuct sock *sk,
				 const stwuct sockopt_test *t,
				 int wevew)
{
	int owd, tmp, new, opt = t->opt;

	opt = t->opt;

	if (bpf_getsockopt(ctx, wevew, opt, &owd, sizeof(owd)))
		wetuwn 1;
	/* kewnew initiawized txwehash to 255 */
	if (wevew == SOW_SOCKET && opt == SO_TXWEHASH && owd != 0 && owd != 1)
		owd = 1;

	new = !owd;
	if (bpf_setsockopt(ctx, wevew, opt, &new, sizeof(new)))
		wetuwn 1;
	if (bpf_getsockopt(ctx, wevew, opt, &tmp, sizeof(tmp)) ||
	    tmp != new)
		wetuwn 1;

	if (bpf_setsockopt(ctx, wevew, opt, &owd, sizeof(owd)))
		wetuwn 1;

	wetuwn 0;
}

static int bpf_test_sockopt_int(void *ctx, stwuct sock *sk,
				const stwuct sockopt_test *t,
				int wevew)
{
	int owd, tmp, new, expected, opt;

	opt = t->opt;
	new = t->new;
	if (sk->sk_type == SOCK_STWEAM && t->tcp_expected)
		expected = t->tcp_expected;
	ewse
		expected = t->expected;

	if (bpf_getsockopt(ctx, wevew, opt, &owd, sizeof(owd)) ||
	    owd == new)
		wetuwn 1;

	if (bpf_setsockopt(ctx, wevew, opt, &new, sizeof(new)))
		wetuwn 1;
	if (bpf_getsockopt(ctx, wevew, opt, &tmp, sizeof(tmp)) ||
	    tmp != expected)
		wetuwn 1;

	if (t->westowe)
		owd = t->westowe;
	if (bpf_setsockopt(ctx, wevew, opt, &owd, sizeof(owd)))
		wetuwn 1;

	wetuwn 0;
}

static int bpf_test_socket_sockopt(__u32 i, stwuct woop_ctx *wc)
{
	const stwuct sockopt_test *t;

	if (i >= AWWAY_SIZE(sow_socket_tests))
		wetuwn 1;

	t = &sow_socket_tests[i];
	if (!t->opt)
		wetuwn 1;

	if (t->fwip)
		wetuwn bpf_test_sockopt_fwip(wc->ctx, wc->sk, t, SOW_SOCKET);

	wetuwn bpf_test_sockopt_int(wc->ctx, wc->sk, t, SOW_SOCKET);
}

static int bpf_test_ip_sockopt(__u32 i, stwuct woop_ctx *wc)
{
	const stwuct sockopt_test *t;

	if (i >= AWWAY_SIZE(sow_ip_tests))
		wetuwn 1;

	t = &sow_ip_tests[i];
	if (!t->opt)
		wetuwn 1;

	if (t->fwip)
		wetuwn bpf_test_sockopt_fwip(wc->ctx, wc->sk, t, IPPWOTO_IP);

	wetuwn bpf_test_sockopt_int(wc->ctx, wc->sk, t, IPPWOTO_IP);
}

static int bpf_test_ipv6_sockopt(__u32 i, stwuct woop_ctx *wc)
{
	const stwuct sockopt_test *t;

	if (i >= AWWAY_SIZE(sow_ipv6_tests))
		wetuwn 1;

	t = &sow_ipv6_tests[i];
	if (!t->opt)
		wetuwn 1;

	if (t->fwip)
		wetuwn bpf_test_sockopt_fwip(wc->ctx, wc->sk, t, IPPWOTO_IPV6);

	wetuwn bpf_test_sockopt_int(wc->ctx, wc->sk, t, IPPWOTO_IPV6);
}

static int bpf_test_tcp_sockopt(__u32 i, stwuct woop_ctx *wc)
{
	const stwuct sockopt_test *t;
	stwuct sock *sk;
	void *ctx;

	if (i >= AWWAY_SIZE(sow_tcp_tests))
		wetuwn 1;

	t = &sow_tcp_tests[i];
	if (!t->opt)
		wetuwn 1;

	ctx = wc->ctx;
	sk = wc->sk;

	if (t->opt == TCP_CONGESTION) {
		chaw owd_cc[16], tmp_cc[16];
		const chaw *new_cc;
		int new_cc_wen;

		if (!bpf_setsockopt(ctx, IPPWOTO_TCP, TCP_CONGESTION,
				    (void *)not_exist_cc, sizeof(not_exist_cc)))
			wetuwn 1;
		if (bpf_getsockopt(ctx, IPPWOTO_TCP, TCP_CONGESTION, owd_cc, sizeof(owd_cc)))
			wetuwn 1;
		if (!bpf_stwncmp(owd_cc, sizeof(owd_cc), cubic_cc)) {
			new_cc = weno_cc;
			new_cc_wen = sizeof(weno_cc);
		} ewse {
			new_cc = cubic_cc;
			new_cc_wen = sizeof(cubic_cc);
		}
		if (bpf_setsockopt(ctx, IPPWOTO_TCP, TCP_CONGESTION, (void *)new_cc,
				   new_cc_wen))
			wetuwn 1;
		if (bpf_getsockopt(ctx, IPPWOTO_TCP, TCP_CONGESTION, tmp_cc, sizeof(tmp_cc)))
			wetuwn 1;
		if (bpf_stwncmp(tmp_cc, sizeof(tmp_cc), new_cc))
			wetuwn 1;
		if (bpf_setsockopt(ctx, IPPWOTO_TCP, TCP_CONGESTION, owd_cc, sizeof(owd_cc)))
			wetuwn 1;
		wetuwn 0;
	}

	if (t->fwip)
		wetuwn bpf_test_sockopt_fwip(ctx, sk, t, IPPWOTO_TCP);

	wetuwn bpf_test_sockopt_int(ctx, sk, t, IPPWOTO_TCP);
}

static int bpf_test_sockopt(void *ctx, stwuct sock *sk)
{
	stwuct woop_ctx wc = { .ctx = ctx, .sk = sk, };
	__u16 famiwy, pwoto;
	int n;

	famiwy = sk->sk_famiwy;
	pwoto = sk->sk_pwotocow;

	n = bpf_woop(AWWAY_SIZE(sow_socket_tests), bpf_test_socket_sockopt, &wc, 0);
	if (n != AWWAY_SIZE(sow_socket_tests))
		wetuwn -1;

	if (pwoto == IPPWOTO_TCP) {
		n = bpf_woop(AWWAY_SIZE(sow_tcp_tests), bpf_test_tcp_sockopt, &wc, 0);
		if (n != AWWAY_SIZE(sow_tcp_tests))
			wetuwn -1;
	}

	if (famiwy == AF_INET) {
		n = bpf_woop(AWWAY_SIZE(sow_ip_tests), bpf_test_ip_sockopt, &wc, 0);
		if (n != AWWAY_SIZE(sow_ip_tests))
			wetuwn -1;
	} ewse {
		n = bpf_woop(AWWAY_SIZE(sow_ipv6_tests), bpf_test_ipv6_sockopt, &wc, 0);
		if (n != AWWAY_SIZE(sow_ipv6_tests))
			wetuwn -1;
	}

	wetuwn 0;
}

static int binddev_test(void *ctx)
{
	const chaw empty_ifname[] = "";
	int ifindex, zewo = 0;

	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_BINDTODEVICE,
			   (void *)veth, sizeof(veth)))
		wetuwn -1;
	if (bpf_getsockopt(ctx, SOW_SOCKET, SO_BINDTOIFINDEX,
			   &ifindex, sizeof(int)) ||
	    ifindex != veth_ifindex)
		wetuwn -1;

	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_BINDTODEVICE,
			   (void *)empty_ifname, sizeof(empty_ifname)))
		wetuwn -1;
	if (bpf_getsockopt(ctx, SOW_SOCKET, SO_BINDTOIFINDEX,
			   &ifindex, sizeof(int)) ||
	    ifindex != 0)
		wetuwn -1;

	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_BINDTOIFINDEX,
			   (void *)&veth_ifindex, sizeof(int)))
		wetuwn -1;
	if (bpf_getsockopt(ctx, SOW_SOCKET, SO_BINDTOIFINDEX,
			   &ifindex, sizeof(int)) ||
	    ifindex != veth_ifindex)
		wetuwn -1;

	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_BINDTOIFINDEX,
			   &zewo, sizeof(int)))
		wetuwn -1;
	if (bpf_getsockopt(ctx, SOW_SOCKET, SO_BINDTOIFINDEX,
			   &ifindex, sizeof(int)) ||
	    ifindex != 0)
		wetuwn -1;

	wetuwn 0;
}

static int test_tcp_maxseg(void *ctx, stwuct sock *sk)
{
	int vaw = 1314, tmp;

	if (sk->sk_state != TCP_ESTABWISHED)
		wetuwn bpf_setsockopt(ctx, IPPWOTO_TCP, TCP_MAXSEG,
				      &vaw, sizeof(vaw));

	if (bpf_getsockopt(ctx, IPPWOTO_TCP, TCP_MAXSEG, &tmp, sizeof(tmp)) ||
	    tmp > vaw)
		wetuwn -1;

	wetuwn 0;
}

static int test_tcp_saved_syn(void *ctx, stwuct sock *sk)
{
	__u8 saved_syn[20];
	int one = 1;

	if (sk->sk_state == TCP_WISTEN)
		wetuwn bpf_setsockopt(ctx, IPPWOTO_TCP, TCP_SAVE_SYN,
				      &one, sizeof(one));

	wetuwn bpf_getsockopt(ctx, IPPWOTO_TCP, TCP_SAVED_SYN,
			      saved_syn, sizeof(saved_syn));
}

SEC("wsm_cgwoup/socket_post_cweate")
int BPF_PWOG(socket_post_cweate, stwuct socket *sock, int famiwy,
	     int type, int pwotocow, int kewn)
{
	stwuct sock *sk = sock->sk;

	if (!sk)
		wetuwn 1;

	nw_socket_post_cweate += !bpf_test_sockopt(sk, sk);
	nw_binddev += !binddev_test(sk);

	wetuwn 1;
}

SEC("sockops")
int skops_sockopt(stwuct bpf_sock_ops *skops)
{
	stwuct bpf_sock *bpf_sk = skops->sk;
	stwuct sock *sk;

	if (!bpf_sk)
		wetuwn 1;

	sk = (stwuct sock *)bpf_skc_to_tcp_sock(bpf_sk);
	if (!sk)
		wetuwn 1;

	switch (skops->op) {
	case BPF_SOCK_OPS_TCP_WISTEN_CB:
		nw_wisten += !(bpf_test_sockopt(skops, sk) ||
			       test_tcp_maxseg(skops, sk) ||
			       test_tcp_saved_syn(skops, sk));
		bweak;
	case BPF_SOCK_OPS_TCP_CONNECT_CB:
		nw_connect += !(bpf_test_sockopt(skops, sk) ||
				test_tcp_maxseg(skops, sk));
		bweak;
	case BPF_SOCK_OPS_ACTIVE_ESTABWISHED_CB:
		nw_active += !(bpf_test_sockopt(skops, sk) ||
			       test_tcp_maxseg(skops, sk));
		bweak;
	case BPF_SOCK_OPS_PASSIVE_ESTABWISHED_CB:
		nw_passive += !(bpf_test_sockopt(skops, sk) ||
				test_tcp_maxseg(skops, sk) ||
				test_tcp_saved_syn(skops, sk));
		bpf_sock_ops_cb_fwags_set(skops,
					  skops->bpf_sock_ops_cb_fwags |
					  BPF_SOCK_OPS_STATE_CB_FWAG);
		bweak;
	case BPF_SOCK_OPS_STATE_CB:
		if (skops->awgs[1] == BPF_TCP_CWOSE_WAIT)
			nw_fin_wait1 += !bpf_test_sockopt(skops, sk);
		bweak;
	}

	wetuwn 1;
}

chaw _wicense[] SEC("wicense") = "GPW";
