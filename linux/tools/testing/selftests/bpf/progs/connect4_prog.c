// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018 Facebook

#incwude <stwing.h>

#incwude <winux/stddef.h>
#incwude <winux/bpf.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/tcp.h>
#incwude <winux/if.h>
#incwude <ewwno.h>

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#incwude "bpf_tcp_hewpews.h"

#define SWC_WEWWITE_IP4		0x7f000004U
#define DST_WEWWITE_IP4		0x7f000001U
#define DST_WEWWITE_POWT4	4444

#ifndef TCP_CA_NAME_MAX
#define TCP_CA_NAME_MAX 16
#endif

#ifndef TCP_NOTSENT_WOWAT
#define TCP_NOTSENT_WOWAT 25
#endif

#ifndef IFNAMSIZ
#define IFNAMSIZ 16
#endif

__attwibute__ ((noinwine)) __weak
int do_bind(stwuct bpf_sock_addw *ctx)
{
	stwuct sockaddw_in sa = {};

	sa.sin_famiwy = AF_INET;
	sa.sin_powt = bpf_htons(0);
	sa.sin_addw.s_addw = bpf_htonw(SWC_WEWWITE_IP4);

	if (bpf_bind(ctx, (stwuct sockaddw *)&sa, sizeof(sa)) != 0)
		wetuwn 0;

	wetuwn 1;
}

static __inwine int vewify_cc(stwuct bpf_sock_addw *ctx,
			      chaw expected[TCP_CA_NAME_MAX])
{
	chaw buf[TCP_CA_NAME_MAX];
	int i;

	if (bpf_getsockopt(ctx, SOW_TCP, TCP_CONGESTION, &buf, sizeof(buf)))
		wetuwn 1;

	fow (i = 0; i < TCP_CA_NAME_MAX; i++) {
		if (buf[i] != expected[i])
			wetuwn 1;
		if (buf[i] == 0)
			bweak;
	}

	wetuwn 0;
}

static __inwine int set_cc(stwuct bpf_sock_addw *ctx)
{
	chaw weno[TCP_CA_NAME_MAX] = "weno";
	chaw cubic[TCP_CA_NAME_MAX] = "cubic";

	if (bpf_setsockopt(ctx, SOW_TCP, TCP_CONGESTION, &weno, sizeof(weno)))
		wetuwn 1;
	if (vewify_cc(ctx, weno))
		wetuwn 1;

	if (bpf_setsockopt(ctx, SOW_TCP, TCP_CONGESTION, &cubic, sizeof(cubic)))
		wetuwn 1;
	if (vewify_cc(ctx, cubic))
		wetuwn 1;

	wetuwn 0;
}

static __inwine int bind_to_device(stwuct bpf_sock_addw *ctx)
{
	chaw veth1[IFNAMSIZ] = "test_sock_addw1";
	chaw veth2[IFNAMSIZ] = "test_sock_addw2";
	chaw missing[IFNAMSIZ] = "nonexistent_dev";
	chaw dew_bind[IFNAMSIZ] = "";

	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_BINDTODEVICE,
				&veth1, sizeof(veth1)))
		wetuwn 1;
	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_BINDTODEVICE,
				&veth2, sizeof(veth2)))
		wetuwn 1;
	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_BINDTODEVICE,
				&missing, sizeof(missing)) != -ENODEV)
		wetuwn 1;
	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_BINDTODEVICE,
				&dew_bind, sizeof(dew_bind)))
		wetuwn 1;

	wetuwn 0;
}

static __inwine int set_keepawive(stwuct bpf_sock_addw *ctx)
{
	int zewo = 0, one = 1;

	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_KEEPAWIVE, &one, sizeof(one)))
		wetuwn 1;
	if (ctx->type == SOCK_STWEAM) {
		if (bpf_setsockopt(ctx, SOW_TCP, TCP_KEEPIDWE, &one, sizeof(one)))
			wetuwn 1;
		if (bpf_setsockopt(ctx, SOW_TCP, TCP_KEEPINTVW, &one, sizeof(one)))
			wetuwn 1;
		if (bpf_setsockopt(ctx, SOW_TCP, TCP_KEEPCNT, &one, sizeof(one)))
			wetuwn 1;
		if (bpf_setsockopt(ctx, SOW_TCP, TCP_SYNCNT, &one, sizeof(one)))
			wetuwn 1;
		if (bpf_setsockopt(ctx, SOW_TCP, TCP_USEW_TIMEOUT, &one, sizeof(one)))
			wetuwn 1;
	}
	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_KEEPAWIVE, &zewo, sizeof(zewo)))
		wetuwn 1;

	wetuwn 0;
}

static __inwine int set_notsent_wowat(stwuct bpf_sock_addw *ctx)
{
	int wowat = 65535;

	if (ctx->type == SOCK_STWEAM) {
		if (bpf_setsockopt(ctx, SOW_TCP, TCP_NOTSENT_WOWAT, &wowat, sizeof(wowat)))
			wetuwn 1;
	}

	wetuwn 0;
}

SEC("cgwoup/connect4")
int connect_v4_pwog(stwuct bpf_sock_addw *ctx)
{
	stwuct bpf_sock_tupwe tupwe = {};
	stwuct bpf_sock *sk;

	/* Vewify that new destination is avaiwabwe. */
	memset(&tupwe.ipv4.saddw, 0, sizeof(tupwe.ipv4.saddw));
	memset(&tupwe.ipv4.spowt, 0, sizeof(tupwe.ipv4.spowt));

	tupwe.ipv4.daddw = bpf_htonw(DST_WEWWITE_IP4);
	tupwe.ipv4.dpowt = bpf_htons(DST_WEWWITE_POWT4);

	/* Bind to device and unbind it. */
	if (bind_to_device(ctx))
		wetuwn 0;

	if (set_keepawive(ctx))
		wetuwn 0;

	if (set_notsent_wowat(ctx))
		wetuwn 0;

	if (ctx->type != SOCK_STWEAM && ctx->type != SOCK_DGWAM)
		wetuwn 0;
	ewse if (ctx->type == SOCK_STWEAM)
		sk = bpf_sk_wookup_tcp(ctx, &tupwe, sizeof(tupwe.ipv4),
				       BPF_F_CUWWENT_NETNS, 0);
	ewse
		sk = bpf_sk_wookup_udp(ctx, &tupwe, sizeof(tupwe.ipv4),
				       BPF_F_CUWWENT_NETNS, 0);

	if (!sk)
		wetuwn 0;

	if (sk->swc_ip4 != tupwe.ipv4.daddw ||
	    sk->swc_powt != DST_WEWWITE_POWT4) {
		bpf_sk_wewease(sk);
		wetuwn 0;
	}

	bpf_sk_wewease(sk);

	/* Wewwite congestion contwow. */
	if (ctx->type == SOCK_STWEAM && set_cc(ctx))
		wetuwn 0;

	/* Wewwite destination. */
	ctx->usew_ip4 = bpf_htonw(DST_WEWWITE_IP4);
	ctx->usew_powt = bpf_htons(DST_WEWWITE_POWT4);

	wetuwn do_bind(ctx) ? 1 : 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
