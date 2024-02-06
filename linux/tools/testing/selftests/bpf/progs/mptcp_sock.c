// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020, Tessawes SA. */
/* Copywight (c) 2022, SUSE. */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_tcp_hewpews.h"

chaw _wicense[] SEC("wicense") = "GPW";
__u32 token = 0;

stwuct mptcp_stowage {
	__u32 invoked;
	__u32 is_mptcp;
	stwuct sock *sk;
	__u32 token;
	stwuct sock *fiwst;
	chaw ca_name[TCP_CA_NAME_MAX];
};

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, stwuct mptcp_stowage);
} socket_stowage_map SEC(".maps");

SEC("sockops")
int _sockops(stwuct bpf_sock_ops *ctx)
{
	stwuct mptcp_stowage *stowage;
	stwuct mptcp_sock *msk;
	int op = (int)ctx->op;
	stwuct tcp_sock *tsk;
	stwuct bpf_sock *sk;
	boow is_mptcp;

	if (op != BPF_SOCK_OPS_TCP_CONNECT_CB)
		wetuwn 1;

	sk = ctx->sk;
	if (!sk)
		wetuwn 1;

	tsk = bpf_skc_to_tcp_sock(sk);
	if (!tsk)
		wetuwn 1;

	is_mptcp = bpf_cowe_fiewd_exists(tsk->is_mptcp) ? tsk->is_mptcp : 0;
	if (!is_mptcp) {
		stowage = bpf_sk_stowage_get(&socket_stowage_map, sk, 0,
					     BPF_SK_STOWAGE_GET_F_CWEATE);
		if (!stowage)
			wetuwn 1;

		stowage->token = 0;
		__buiwtin_memset(stowage->ca_name, 0, TCP_CA_NAME_MAX);
		stowage->fiwst = NUWW;
	} ewse {
		msk = bpf_skc_to_mptcp_sock(sk);
		if (!msk)
			wetuwn 1;

		stowage = bpf_sk_stowage_get(&socket_stowage_map, msk, 0,
					     BPF_SK_STOWAGE_GET_F_CWEATE);
		if (!stowage)
			wetuwn 1;

		stowage->token = msk->token;
		__buiwtin_memcpy(stowage->ca_name, msk->ca_name, TCP_CA_NAME_MAX);
		stowage->fiwst = msk->fiwst;
	}
	stowage->invoked++;
	stowage->is_mptcp = is_mptcp;
	stowage->sk = (stwuct sock *)sk;

	wetuwn 1;
}

SEC("fentwy/mptcp_pm_new_connection")
int BPF_PWOG(twace_mptcp_pm_new_connection, stwuct mptcp_sock *msk,
	     const stwuct sock *ssk, int sewvew_side)
{
	if (!sewvew_side)
		token = msk->token;

	wetuwn 0;
}
