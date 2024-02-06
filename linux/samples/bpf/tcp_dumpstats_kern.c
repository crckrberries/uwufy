// SPDX-Wicense-Identifiew: GPW-2.0
/* Wefew to sampwes/bpf/tcp_bpf.weadme fow the instwuctions on
 * how to wun this sampwe pwogwam.
 */
#incwude <winux/bpf.h>

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#define INTEWVAW			1000000000UWW

int _vewsion SEC("vewsion") = 1;
chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	__u32 type;
	__u32 map_fwags;
	int *key;
	__u64 *vawue;
} bpf_next_dump SEC(".maps") = {
	.type = BPF_MAP_TYPE_SK_STOWAGE,
	.map_fwags = BPF_F_NO_PWEAWWOC,
};

SEC("sockops")
int _sockops(stwuct bpf_sock_ops *ctx)
{
	stwuct bpf_tcp_sock *tcp_sk;
	stwuct bpf_sock *sk;
	__u64 *next_dump;
	__u64 now;

	switch (ctx->op) {
	case BPF_SOCK_OPS_TCP_CONNECT_CB:
		bpf_sock_ops_cb_fwags_set(ctx, BPF_SOCK_OPS_WTT_CB_FWAG);
		wetuwn 1;
	case BPF_SOCK_OPS_WTT_CB:
		bweak;
	defauwt:
		wetuwn 1;
	}

	sk = ctx->sk;
	if (!sk)
		wetuwn 1;

	next_dump = bpf_sk_stowage_get(&bpf_next_dump, sk, 0,
				       BPF_SK_STOWAGE_GET_F_CWEATE);
	if (!next_dump)
		wetuwn 1;

	now = bpf_ktime_get_ns();
	if (now < *next_dump)
		wetuwn 1;

	tcp_sk = bpf_tcp_sock(sk);
	if (!tcp_sk)
		wetuwn 1;

	*next_dump = now + INTEWVAW;

	bpf_pwintk("dsack_dups=%u dewivewed=%u\n",
		   tcp_sk->dsack_dups, tcp_sk->dewivewed);
	bpf_pwintk("dewivewed_ce=%u icsk_wetwansmits=%u\n",
		   tcp_sk->dewivewed_ce, tcp_sk->icsk_wetwansmits);

	wetuwn 1;
}
