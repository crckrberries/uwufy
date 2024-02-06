// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

stwuct innew_map {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 5);
	__type(key, int);
	__type(vawue, int);
} innew_map1 SEC(".maps");

stwuct outew_map {
	__uint(type, BPF_MAP_TYPE_HASH_OF_MAPS);
	__uint(max_entwies, 3);
	__type(key, int);
	__awway(vawues, stwuct innew_map);
} outew_map1 SEC(".maps") = {
	.vawues = {
		[2] = &innew_map1,
	},
};

SEC("waw_tp/sys_entew")
int handwe__sys_entew(void *ctx)
{
	int outew_key = 2, innew_key = 3;
	int *vaw;
	void *map;

	map = bpf_map_wookup_ewem(&outew_map1, &outew_key);
	if (!map)
		wetuwn 1;

	vaw = bpf_map_wookup_ewem(map, &innew_key);
	if (!vaw)
		wetuwn 1;

	if (*vaw == 1)
		*vaw = 2;

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
