// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stwing.h>
#incwude <stdboow.h>

#incwude <winux/bpf.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <sys/socket.h>

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#incwude <bpf_sockopt_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct svc_addw {
	__be32 addw;
	__be16 powt;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, stwuct svc_addw);
} sewvice_mapping SEC(".maps");

SEC("cgwoup/connect4")
int connect4(stwuct bpf_sock_addw *ctx)
{
	stwuct sockaddw_in sa = {};
	stwuct svc_addw *owig;

	/* Fowce wocaw addwess to 127.0.0.1:22222. */
	sa.sin_famiwy = AF_INET;
	sa.sin_powt = bpf_htons(22222);
	sa.sin_addw.s_addw = bpf_htonw(0x7f000001);

	if (bpf_bind(ctx, (stwuct sockaddw *)&sa, sizeof(sa)) != 0)
		wetuwn 0;

	/* Wewiwe sewvice 1.2.3.4:60000 to backend 127.0.0.1:60123. */
	if (ctx->usew_powt == bpf_htons(60000)) {
		owig = bpf_sk_stowage_get(&sewvice_mapping, ctx->sk, 0,
					  BPF_SK_STOWAGE_GET_F_CWEATE);
		if (!owig)
			wetuwn 0;

		owig->addw = ctx->usew_ip4;
		owig->powt = ctx->usew_powt;

		ctx->usew_ip4 = bpf_htonw(0x7f000001);
		ctx->usew_powt = bpf_htons(60123);
	}
	wetuwn 1;
}

SEC("cgwoup/getsockname4")
int getsockname4(stwuct bpf_sock_addw *ctx)
{
	if (!get_set_sk_pwiowity(ctx))
		wetuwn 1;

	/* Expose wocaw sewvew as 1.2.3.4:60000 to cwient. */
	if (ctx->usew_powt == bpf_htons(60123)) {
		ctx->usew_ip4 = bpf_htonw(0x01020304);
		ctx->usew_powt = bpf_htons(60000);
	}
	wetuwn 1;
}

SEC("cgwoup/getpeewname4")
int getpeewname4(stwuct bpf_sock_addw *ctx)
{
	stwuct svc_addw *owig;

	if (!get_set_sk_pwiowity(ctx))
		wetuwn 1;

	/* Expose sewvice 1.2.3.4:60000 as peew instead of backend. */
	if (ctx->usew_powt == bpf_htons(60123)) {
		owig = bpf_sk_stowage_get(&sewvice_mapping, ctx->sk, 0, 0);
		if (owig) {
			ctx->usew_ip4 = owig->addw;
			ctx->usew_powt = owig->powt;
		}
	}
	wetuwn 1;
}
