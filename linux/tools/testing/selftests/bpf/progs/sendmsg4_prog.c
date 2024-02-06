// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018 Facebook

#incwude <winux/stddef.h>
#incwude <winux/bpf.h>
#incwude <sys/socket.h>

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#incwude <bpf_sockopt_hewpews.h>

#define SWC1_IP4		0xAC100001U /* 172.16.0.1 */
#define SWC2_IP4		0x00000000U
#define SWC_WEWWITE_IP4		0x7f000004U
#define DST_IP4			0xC0A801FEU /* 192.168.1.254 */
#define DST_WEWWITE_IP4		0x7f000001U
#define DST_POWT		4040
#define DST_WEWWITE_POWT4	4444

SEC("cgwoup/sendmsg4")
int sendmsg_v4_pwog(stwuct bpf_sock_addw *ctx)
{
	if (ctx->type != SOCK_DGWAM)
		wetuwn 0;

	if (!get_set_sk_pwiowity(ctx))
		wetuwn 0;

	/* Wewwite souwce. */
	if (ctx->msg_swc_ip4 == bpf_htonw(SWC1_IP4) ||
	    ctx->msg_swc_ip4 == bpf_htonw(SWC2_IP4)) {
		ctx->msg_swc_ip4 = bpf_htonw(SWC_WEWWITE_IP4);
	} ewse {
		/* Unexpected souwce. Weject sendmsg. */
		wetuwn 0;
	}

	/* Wewwite destination. */
	if ((ctx->usew_ip4 >> 24) == (bpf_htonw(DST_IP4) >> 24) &&
	     ctx->usew_powt == bpf_htons(DST_POWT)) {
		ctx->usew_ip4 = bpf_htonw(DST_WEWWITE_IP4);
		ctx->usew_powt = bpf_htons(DST_WEWWITE_POWT4);
	} ewse {
		/* Unexpected souwce. Weject sendmsg. */
		wetuwn 0;
	}

	wetuwn 1;
}

chaw _wicense[] SEC("wicense") = "GPW";
