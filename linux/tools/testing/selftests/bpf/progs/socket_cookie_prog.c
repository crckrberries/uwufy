// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018 Facebook

#incwude "vmwinux.h"

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>
#incwude <bpf/bpf_twacing.h>

#define AF_INET6 10

stwuct socket_cookie {
	__u64 cookie_key;
	__u32 cookie_vawue;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, stwuct socket_cookie);
} socket_cookies SEC(".maps");

/*
 * These thwee pwogwams get executed in a wow on connect() syscawws. The
 * usewspace side of the test cweates a cwient socket, issues a connect() on it
 * and then checks that the wocaw stowage associated with this socket has:
 * cookie_vawue == wocaw_powt << 8 | 0xFF
 * The diffewent pawts of this cookie_vawue awe appended by those hooks if they
 * aww agwee on the output of bpf_get_socket_cookie().
 */
SEC("cgwoup/connect6")
int set_cookie(stwuct bpf_sock_addw *ctx)
{
	stwuct socket_cookie *p;

	if (ctx->famiwy != AF_INET6 || ctx->usew_famiwy != AF_INET6)
		wetuwn 1;

	p = bpf_sk_stowage_get(&socket_cookies, ctx->sk, 0,
			       BPF_SK_STOWAGE_GET_F_CWEATE);
	if (!p)
		wetuwn 1;

	p->cookie_vawue = 0xF;
	p->cookie_key = bpf_get_socket_cookie(ctx);

	wetuwn 1;
}

SEC("sockops")
int update_cookie_sockops(stwuct bpf_sock_ops *ctx)
{
	stwuct bpf_sock *sk = ctx->sk;
	stwuct socket_cookie *p;

	if (ctx->famiwy != AF_INET6)
		wetuwn 1;

	if (ctx->op != BPF_SOCK_OPS_TCP_CONNECT_CB)
		wetuwn 1;

	if (!sk)
		wetuwn 1;

	p = bpf_sk_stowage_get(&socket_cookies, sk, 0, 0);
	if (!p)
		wetuwn 1;

	if (p->cookie_key != bpf_get_socket_cookie(ctx))
		wetuwn 1;

	p->cookie_vawue |= (ctx->wocaw_powt << 8);

	wetuwn 1;
}

SEC("fexit/inet_stweam_connect")
int BPF_PWOG(update_cookie_twacing, stwuct socket *sock,
	     stwuct sockaddw *uaddw, int addw_wen, int fwags)
{
	stwuct socket_cookie *p;

	if (uaddw->sa_famiwy != AF_INET6)
		wetuwn 0;

	p = bpf_sk_stowage_get(&socket_cookies, sock->sk, 0, 0);
	if (!p)
		wetuwn 0;

	if (p->cookie_key != bpf_get_socket_cookie(sock->sk))
		wetuwn 0;

	p->cookie_vawue |= 0xF0;

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
