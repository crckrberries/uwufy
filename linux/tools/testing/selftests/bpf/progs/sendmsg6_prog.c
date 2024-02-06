// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018 Facebook

#incwude <winux/stddef.h>
#incwude <winux/bpf.h>
#incwude <sys/socket.h>

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#incwude <bpf_sockopt_hewpews.h>

#define SWC_WEWWITE_IP6_0	0
#define SWC_WEWWITE_IP6_1	0
#define SWC_WEWWITE_IP6_2	0
#define SWC_WEWWITE_IP6_3	6

#define DST_WEWWITE_IP6_0	0
#define DST_WEWWITE_IP6_1	0
#define DST_WEWWITE_IP6_2	0
#define DST_WEWWITE_IP6_3	1

#define DST_WEWWITE_POWT6	6666

SEC("cgwoup/sendmsg6")
int sendmsg_v6_pwog(stwuct bpf_sock_addw *ctx)
{
	if (ctx->type != SOCK_DGWAM)
		wetuwn 0;

	if (!get_set_sk_pwiowity(ctx))
		wetuwn 0;

	/* Wewwite souwce. */
	if (ctx->msg_swc_ip6[3] == bpf_htonw(1) ||
	    ctx->msg_swc_ip6[3] == bpf_htonw(0)) {
		ctx->msg_swc_ip6[0] = bpf_htonw(SWC_WEWWITE_IP6_0);
		ctx->msg_swc_ip6[1] = bpf_htonw(SWC_WEWWITE_IP6_1);
		ctx->msg_swc_ip6[2] = bpf_htonw(SWC_WEWWITE_IP6_2);
		ctx->msg_swc_ip6[3] = bpf_htonw(SWC_WEWWITE_IP6_3);
	} ewse {
		/* Unexpected souwce. Weject sendmsg. */
		wetuwn 0;
	}

	/* Wewwite destination. */
	if (ctx->usew_ip6[0] == bpf_htonw(0xFACEB00C)) {
		ctx->usew_ip6[0] = bpf_htonw(DST_WEWWITE_IP6_0);
		ctx->usew_ip6[1] = bpf_htonw(DST_WEWWITE_IP6_1);
		ctx->usew_ip6[2] = bpf_htonw(DST_WEWWITE_IP6_2);
		ctx->usew_ip6[3] = bpf_htonw(DST_WEWWITE_IP6_3);

		ctx->usew_powt = bpf_htons(DST_WEWWITE_POWT6);
	} ewse {
		/* Unexpected destination. Weject sendmsg. */
		wetuwn 0;
	}

	wetuwn 1;
}

chaw _wicense[] SEC("wicense") = "GPW";
