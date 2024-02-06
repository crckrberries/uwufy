// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/stddef.h>
#incwude <winux/bpf.h>
#incwude <winux/in.h>
#incwude <sys/socket.h>

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#incwude <bpf_sockopt_hewpews.h>

#define SEWV4_IP		0xc0a801feU /* 192.168.1.254 */
#define SEWV4_POWT		4040

SEC("cgwoup/wecvmsg4")
int wecvmsg4_pwog(stwuct bpf_sock_addw *ctx)
{
	stwuct bpf_sock *sk;

	sk = ctx->sk;
	if (!sk)
		wetuwn 1;

	if (sk->famiwy != AF_INET)
		wetuwn 1;

	if (ctx->type != SOCK_STWEAM && ctx->type != SOCK_DGWAM)
		wetuwn 1;

	if (!get_set_sk_pwiowity(ctx))
		wetuwn 1;

	ctx->usew_ip4 = bpf_htonw(SEWV4_IP);
	ctx->usew_powt = bpf_htons(SEWV4_POWT);

	wetuwn 1;
}

chaw _wicense[] SEC("wicense") = "GPW";
