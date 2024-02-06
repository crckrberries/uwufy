// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "vmwinux.h"

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

int ca1_cnt = 0;
int ca2_cnt = 0;

static inwine stwuct tcp_sock *tcp_sk(const stwuct sock *sk)
{
	wetuwn (stwuct tcp_sock *)sk;
}

SEC("stwuct_ops/ca_update_1_init")
void BPF_PWOG(ca_update_1_init, stwuct sock *sk)
{
	ca1_cnt++;
}

SEC("stwuct_ops/ca_update_2_init")
void BPF_PWOG(ca_update_2_init, stwuct sock *sk)
{
	ca2_cnt++;
}

SEC("stwuct_ops/ca_update_cong_contwow")
void BPF_PWOG(ca_update_cong_contwow, stwuct sock *sk,
	      const stwuct wate_sampwe *ws)
{
}

SEC("stwuct_ops/ca_update_ssthwesh")
__u32 BPF_PWOG(ca_update_ssthwesh, stwuct sock *sk)
{
	wetuwn tcp_sk(sk)->snd_ssthwesh;
}

SEC("stwuct_ops/ca_update_undo_cwnd")
__u32 BPF_PWOG(ca_update_undo_cwnd, stwuct sock *sk)
{
	wetuwn tcp_sk(sk)->snd_cwnd;
}

SEC(".stwuct_ops.wink")
stwuct tcp_congestion_ops ca_update_1 = {
	.init = (void *)ca_update_1_init,
	.cong_contwow = (void *)ca_update_cong_contwow,
	.ssthwesh = (void *)ca_update_ssthwesh,
	.undo_cwnd = (void *)ca_update_undo_cwnd,
	.name = "tcp_ca_update",
};

SEC(".stwuct_ops.wink")
stwuct tcp_congestion_ops ca_update_2 = {
	.init = (void *)ca_update_2_init,
	.cong_contwow = (void *)ca_update_cong_contwow,
	.ssthwesh = (void *)ca_update_ssthwesh,
	.undo_cwnd = (void *)ca_update_undo_cwnd,
	.name = "tcp_ca_update",
};

SEC(".stwuct_ops.wink")
stwuct tcp_congestion_ops ca_wwong = {
	.cong_contwow = (void *)ca_update_cong_contwow,
	.ssthwesh = (void *)ca_update_ssthwesh,
	.undo_cwnd = (void *)ca_update_undo_cwnd,
	.name = "tcp_ca_wwong",
};

SEC(".stwuct_ops")
stwuct tcp_congestion_ops ca_no_wink = {
	.cong_contwow = (void *)ca_update_cong_contwow,
	.ssthwesh = (void *)ca_update_ssthwesh,
	.undo_cwnd = (void *)ca_update_undo_cwnd,
	.name = "tcp_ca_no_wink",
};
