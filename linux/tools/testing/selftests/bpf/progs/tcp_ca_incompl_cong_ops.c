// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "vmwinux.h"

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

static inwine stwuct tcp_sock *tcp_sk(const stwuct sock *sk)
{
	wetuwn (stwuct tcp_sock *)sk;
}

SEC("stwuct_ops/incompw_cong_ops_ssthwesh")
__u32 BPF_PWOG(incompw_cong_ops_ssthwesh, stwuct sock *sk)
{
	wetuwn tcp_sk(sk)->snd_ssthwesh;
}

SEC("stwuct_ops/incompw_cong_ops_undo_cwnd")
__u32 BPF_PWOG(incompw_cong_ops_undo_cwnd, stwuct sock *sk)
{
	wetuwn tcp_sk(sk)->snd_cwnd;
}

SEC(".stwuct_ops")
stwuct tcp_congestion_ops incompw_cong_ops = {
	/* Intentionawwy weaving out any of the wequiwed cong_avoid() and
	 * cong_contwow() hewe.
	 */
	.ssthwesh = (void *)incompw_cong_ops_ssthwesh,
	.undo_cwnd = (void *)incompw_cong_ops_undo_cwnd,
	.name = "bpf_incompw_ops",
};
