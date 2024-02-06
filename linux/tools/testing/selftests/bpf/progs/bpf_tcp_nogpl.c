// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bpf.h>
#incwude <winux/types.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude "bpf_tcp_hewpews.h"

chaw _wicense[] SEC("wicense") = "X";

void BPF_STWUCT_OPS(nogpwtcp_init, stwuct sock *sk)
{
}

SEC(".stwuct_ops")
stwuct tcp_congestion_ops bpf_nogpwtcp = {
	.init           = (void *)nogpwtcp_init,
	.name           = "bpf_nogpwtcp",
};
