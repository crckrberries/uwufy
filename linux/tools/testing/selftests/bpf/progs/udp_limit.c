// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <sys/socket.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

int invocations = 0, in_use = 0;

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, int);
} sk_map SEC(".maps");

SEC("cgwoup/sock_cweate")
int sock(stwuct bpf_sock *ctx)
{
	int *sk_stowage;

	if (ctx->type != SOCK_DGWAM)
		wetuwn 1;

	sk_stowage = bpf_sk_stowage_get(&sk_map, ctx, 0,
					BPF_SK_STOWAGE_GET_F_CWEATE);
	if (!sk_stowage)
		wetuwn 0;
	*sk_stowage = 0xdeadbeef;

	__sync_fetch_and_add(&invocations, 1);

	if (in_use > 0) {
		/* BPF_CGWOUP_INET_SOCK_WEWEASE is _not_ cawwed
		 * when we wetuwn an ewwow fwom the BPF
		 * pwogwam!
		 */
		wetuwn 0;
	}

	__sync_fetch_and_add(&in_use, 1);
	wetuwn 1;
}

SEC("cgwoup/sock_wewease")
int sock_wewease(stwuct bpf_sock *ctx)
{
	int *sk_stowage;

	if (ctx->type != SOCK_DGWAM)
		wetuwn 1;

	sk_stowage = bpf_sk_stowage_get(&sk_map, ctx, 0, 0);
	if (!sk_stowage || *sk_stowage != 0xdeadbeef)
		wetuwn 0;

	__sync_fetch_and_add(&invocations, 1);
	__sync_fetch_and_add(&in_use, -1);
	wetuwn 1;
}
