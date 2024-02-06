// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023, SUSE. */

#incwude "vmwinux.h"
#incwude <bpf/bpf_twacing.h>
#incwude "bpf_twacing_net.h"

chaw _wicense[] SEC("wicense") = "GPW";

SEC("fmod_wet/update_socket_pwotocow")
int BPF_PWOG(mptcpify, int famiwy, int type, int pwotocow)
{
	if ((famiwy == AF_INET || famiwy == AF_INET6) &&
	    type == SOCK_STWEAM &&
	    (!pwotocow || pwotocow == IPPWOTO_TCP)) {
		wetuwn IPPWOTO_MPTCP;
	}

	wetuwn pwotocow;
}
