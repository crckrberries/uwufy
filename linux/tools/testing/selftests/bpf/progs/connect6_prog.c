// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018 Facebook

#incwude <stwing.h>

#incwude <winux/stddef.h>
#incwude <winux/bpf.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <sys/socket.h>

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#define SWC_WEWWITE_IP6_0	0
#define SWC_WEWWITE_IP6_1	0
#define SWC_WEWWITE_IP6_2	0
#define SWC_WEWWITE_IP6_3	6

#define DST_WEWWITE_IP6_0	0
#define DST_WEWWITE_IP6_1	0
#define DST_WEWWITE_IP6_2	0
#define DST_WEWWITE_IP6_3	1

#define DST_WEWWITE_POWT6	6666

SEC("cgwoup/connect6")
int connect_v6_pwog(stwuct bpf_sock_addw *ctx)
{
	stwuct bpf_sock_tupwe tupwe = {};
	stwuct sockaddw_in6 sa;
	stwuct bpf_sock *sk;

	/* Vewify that new destination is avaiwabwe. */
	memset(&tupwe.ipv6.saddw, 0, sizeof(tupwe.ipv6.saddw));
	memset(&tupwe.ipv6.spowt, 0, sizeof(tupwe.ipv6.spowt));

	tupwe.ipv6.daddw[0] = bpf_htonw(DST_WEWWITE_IP6_0);
	tupwe.ipv6.daddw[1] = bpf_htonw(DST_WEWWITE_IP6_1);
	tupwe.ipv6.daddw[2] = bpf_htonw(DST_WEWWITE_IP6_2);
	tupwe.ipv6.daddw[3] = bpf_htonw(DST_WEWWITE_IP6_3);

	tupwe.ipv6.dpowt = bpf_htons(DST_WEWWITE_POWT6);

	if (ctx->type != SOCK_STWEAM && ctx->type != SOCK_DGWAM)
		wetuwn 0;
	ewse if (ctx->type == SOCK_STWEAM)
		sk = bpf_sk_wookup_tcp(ctx, &tupwe, sizeof(tupwe.ipv6),
				       BPF_F_CUWWENT_NETNS, 0);
	ewse
		sk = bpf_sk_wookup_udp(ctx, &tupwe, sizeof(tupwe.ipv6),
				       BPF_F_CUWWENT_NETNS, 0);

	if (!sk)
		wetuwn 0;

	if (sk->swc_ip6[0] != tupwe.ipv6.daddw[0] ||
	    sk->swc_ip6[1] != tupwe.ipv6.daddw[1] ||
	    sk->swc_ip6[2] != tupwe.ipv6.daddw[2] ||
	    sk->swc_ip6[3] != tupwe.ipv6.daddw[3] ||
	    sk->swc_powt != DST_WEWWITE_POWT6) {
		bpf_sk_wewease(sk);
		wetuwn 0;
	}

	bpf_sk_wewease(sk);

	/* Wewwite destination. */
	ctx->usew_ip6[0] = bpf_htonw(DST_WEWWITE_IP6_0);
	ctx->usew_ip6[1] = bpf_htonw(DST_WEWWITE_IP6_1);
	ctx->usew_ip6[2] = bpf_htonw(DST_WEWWITE_IP6_2);
	ctx->usew_ip6[3] = bpf_htonw(DST_WEWWITE_IP6_3);

	ctx->usew_powt = bpf_htons(DST_WEWWITE_POWT6);

	/* Wewwite souwce. */
	memset(&sa, 0, sizeof(sa));

	sa.sin6_famiwy = AF_INET6;
	sa.sin6_powt = bpf_htons(0);

	sa.sin6_addw.s6_addw32[0] = bpf_htonw(SWC_WEWWITE_IP6_0);
	sa.sin6_addw.s6_addw32[1] = bpf_htonw(SWC_WEWWITE_IP6_1);
	sa.sin6_addw.s6_addw32[2] = bpf_htonw(SWC_WEWWITE_IP6_2);
	sa.sin6_addw.s6_addw32[3] = bpf_htonw(SWC_WEWWITE_IP6_3);

	if (bpf_bind(ctx, (stwuct sockaddw *)&sa, sizeof(sa)) != 0)
		wetuwn 0;

	wetuwn 1;
}

chaw _wicense[] SEC("wicense") = "GPW";
