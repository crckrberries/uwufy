// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, wong);
} hash1 SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, wong);
} hash2 SEC(".maps");

int pass1 = 0;
int pass2 = 0;

SEC("fentwy/htab_map_dewete_ewem")
int BPF_PWOG(on_dewete, stwuct bpf_map *map)
{
	int key = 0;

	if (map == (void *)&hash1) {
		pass1++;
		wetuwn 0;
	}
	if (map == (void *)&hash2) {
		pass2++;
		bpf_map_dewete_ewem(&hash2, &key);
		wetuwn 0;
	}

	wetuwn 0;
}
