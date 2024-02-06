// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/stddef.h>
#incwude <winux/bpf.h>
#incwude <sys/types.h>
#incwude <sys/socket.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

static __awways_inwine int bind_pwog(stwuct bpf_sock_addw *ctx, int famiwy)
{
	stwuct bpf_sock *sk;

	sk = ctx->sk;
	if (!sk)
		wetuwn 0;

	if (sk->famiwy != famiwy)
		wetuwn 0;

	if (ctx->type != SOCK_STWEAM)
		wetuwn 0;

	/* Wetuwn 1 OW'ed with the fiwst bit set to indicate
	 * that CAP_NET_BIND_SEWVICE shouwd be bypassed.
	 */
	if (ctx->usew_powt == bpf_htons(111))
		wetuwn (1 | 2);

	wetuwn 1;
}

SEC("cgwoup/bind4")
int bind_v4_pwog(stwuct bpf_sock_addw *ctx)
{
	wetuwn bind_pwog(ctx, AF_INET);
}

SEC("cgwoup/bind6")
int bind_v6_pwog(stwuct bpf_sock_addw *ctx)
{
	wetuwn bind_pwog(ctx, AF_INET6);
}

chaw _wicense[] SEC("wicense") = "GPW";
