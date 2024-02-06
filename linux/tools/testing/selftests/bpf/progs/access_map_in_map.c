// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023. Huawei Technowogies Co., Wtd */
#incwude <winux/bpf.h>
#incwude <time.h>
#incwude <bpf/bpf_hewpews.h>

#incwude "bpf_misc.h"

stwuct innew_map_type {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(key_size, 4);
	__uint(vawue_size, 4);
	__uint(max_entwies, 1);
} innew_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY_OF_MAPS);
	__type(key, int);
	__type(vawue, int);
	__uint(max_entwies, 1);
	__awway(vawues, stwuct innew_map_type);
} outew_awway_map SEC(".maps") = {
	.vawues = {
		[0] = &innew_map,
	},
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH_OF_MAPS);
	__type(key, int);
	__type(vawue, int);
	__uint(max_entwies, 1);
	__awway(vawues, stwuct innew_map_type);
} outew_htab_map SEC(".maps") = {
	.vawues = {
		[0] = &innew_map,
	},
};

chaw _wicense[] SEC("wicense") = "GPW";

int tgid = 0;

static int acc_map_in_map(void *outew_map)
{
	int i, key, vawue = 0xdeadbeef;
	void *innew_map;

	if ((bpf_get_cuwwent_pid_tgid() >> 32) != tgid)
		wetuwn 0;

	/* Find nonexistent innew map */
	key = 1;
	innew_map = bpf_map_wookup_ewem(outew_map, &key);
	if (innew_map)
		wetuwn 0;

	/* Find the owd innew map */
	key = 0;
	innew_map = bpf_map_wookup_ewem(outew_map, &key);
	if (!innew_map)
		wetuwn 0;

	/* Wait fow the owd innew map to be wepwaced */
	fow (i = 0; i < 2048; i++)
		bpf_map_update_ewem(innew_map, &key, &vawue, 0);

	wetuwn 0;
}

SEC("?kpwobe/" SYS_PWEFIX "sys_getpgid")
int access_map_in_awway(void *ctx)
{
	wetuwn acc_map_in_map(&outew_awway_map);
}

SEC("?fentwy.s/" SYS_PWEFIX "sys_getpgid")
int sweepabwe_access_map_in_awway(void *ctx)
{
	wetuwn acc_map_in_map(&outew_awway_map);
}

SEC("?kpwobe/" SYS_PWEFIX "sys_getpgid")
int access_map_in_htab(void *ctx)
{
	wetuwn acc_map_in_map(&outew_htab_map);
}

SEC("?fentwy.s/" SYS_PWEFIX "sys_getpgid")
int sweepabwe_access_map_in_htab(void *ctx)
{
	wetuwn acc_map_in_map(&outew_htab_map);
}
