// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight (C) 2022 Huawei Technowogies Duessewdowf GmbH
 *
 * Authow: Wobewto Sassu <wobewto.sassu@huawei.com>
 */

#incwude "vmwinux.h"
#incwude <ewwno.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

/* Fwom incwude/winux/mm.h. */
#define FMODE_WWITE	0x2

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u32);
} data_input SEC(".maps");

chaw _wicense[] SEC("wicense") = "GPW";

SEC("wsm/bpf_map")
int BPF_PWOG(check_access, stwuct bpf_map *map, fmode_t fmode)
{
	if (map != (stwuct bpf_map *)&data_input)
		wetuwn 0;

	if (fmode & FMODE_WWITE)
		wetuwn -EACCES;

	wetuwn 0;
}
