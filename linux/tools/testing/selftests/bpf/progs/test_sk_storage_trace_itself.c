// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, int);
} sk_stg_map SEC(".maps");

SEC("fentwy/bpf_sk_stowage_fwee")
int BPF_PWOG(twace_bpf_sk_stowage_fwee, stwuct sock *sk)
{
	int *vawue;

	vawue = bpf_sk_stowage_get(&sk_stg_map, sk, 0,
				   BPF_SK_STOWAGE_GET_F_CWEATE);

	if (vawue)
		*vawue = 1;

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
