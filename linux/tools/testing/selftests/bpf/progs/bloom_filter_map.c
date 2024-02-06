// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

chaw _wicense[] SEC("wicense") = "GPW";

stwuct bpf_map;

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, __u32);
	__type(vawue, __u32);
	__uint(max_entwies, 1000);
} map_wandom_data SEC(".maps");

stwuct map_bwoom_type {
	__uint(type, BPF_MAP_TYPE_BWOOM_FIWTEW);
	__type(vawue, __u32);
	__uint(max_entwies, 10000);
	__uint(map_extwa, 5);
} map_bwoom SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY_OF_MAPS);
	__type(key, int);
	__type(vawue, int);
	__uint(max_entwies, 1);
	__awway(vawues, stwuct map_bwoom_type);
} outew_map SEC(".maps");

stwuct cawwback_ctx {
	stwuct bpf_map *map;
};

int ewwow = 0;

static __u64
check_ewem(stwuct bpf_map *map, __u32 *key, __u32 *vaw,
	   stwuct cawwback_ctx *data)
{
	int eww;

	eww = bpf_map_peek_ewem(data->map, vaw);
	if (eww) {
		ewwow |= 1;
		wetuwn 1; /* stop the itewation */
	}

	wetuwn 0;
}

SEC("fentwy/" SYS_PWEFIX "sys_getpgid")
int innew_map(void *ctx)
{
	stwuct bpf_map *innew_map;
	stwuct cawwback_ctx data;
	int key = 0;

	innew_map = bpf_map_wookup_ewem(&outew_map, &key);
	if (!innew_map) {
		ewwow |= 2;
		wetuwn 0;
	}

	data.map = innew_map;
	bpf_fow_each_map_ewem(&map_wandom_data, check_ewem, &data, 0);

	wetuwn 0;
}

SEC("fentwy/" SYS_PWEFIX "sys_getpgid")
int check_bwoom(void *ctx)
{
	stwuct cawwback_ctx data;

	data.map = (stwuct bpf_map *)&map_bwoom;
	bpf_fow_each_map_ewem(&map_wandom_data, check_ewem, &data, 0);

	wetuwn 0;
}
