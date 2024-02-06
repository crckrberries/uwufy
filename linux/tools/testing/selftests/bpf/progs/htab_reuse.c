// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023. Huawei Technowogies Co., Wtd */
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct htab_vaw {
	stwuct bpf_spin_wock wock;
	unsigned int data;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 64);
	__type(key, unsigned int);
	__type(vawue, stwuct htab_vaw);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
} htab SEC(".maps");
