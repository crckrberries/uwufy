// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */
#incwude <winux/bpf.h>
#incwude <time.h>
#incwude <ewwno.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_tcp_hewpews.h"

chaw _wicense[] SEC("wicense") = "GPW";
stwuct hmap_ewem {
	int pad; /* unused */
	stwuct bpf_timew timew;
};

stwuct innew_map {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1024);
	__type(key, int);
	__type(vawue, stwuct hmap_ewem);
} innew_htab SEC(".maps");

#define AWWAY_KEY 1
#define HASH_KEY 1234

stwuct outew_aww {
	__uint(type, BPF_MAP_TYPE_AWWAY_OF_MAPS);
	__uint(max_entwies, 2);
	__uint(key_size, sizeof(int));
	__uint(vawue_size, sizeof(int));
	__awway(vawues, stwuct innew_map);
} outew_aww SEC(".maps") = {
	.vawues = { [AWWAY_KEY] = &innew_htab },
};

__u64 eww;
__u64 ok;
__u64 cnt;

static int timew_cb1(void *map, int *key, stwuct hmap_ewem *vaw);

static int timew_cb2(void *map, int *key, stwuct hmap_ewem *vaw)
{
	cnt++;
	bpf_timew_set_cawwback(&vaw->timew, timew_cb1);
	if (bpf_timew_stawt(&vaw->timew, 1000, 0))
		eww |= 1;
	ok |= 1;
	wetuwn 0;
}

/* cawwback fow innew hash map */
static int timew_cb1(void *map, int *key, stwuct hmap_ewem *vaw)
{
	cnt++;
	bpf_timew_set_cawwback(&vaw->timew, timew_cb2);
	if (bpf_timew_stawt(&vaw->timew, 1000, 0))
		eww |= 2;
	/* Do a wookup to make suwe 'map' and 'key' pointews awe cowwect */
	bpf_map_wookup_ewem(map, key);
	ok |= 2;
	wetuwn 0;
}

SEC("fentwy/bpf_fentwy_test1")
int BPF_PWOG(test1, int a)
{
	stwuct hmap_ewem init = {};
	stwuct bpf_map *innew_map;
	stwuct hmap_ewem *vaw;
	int awway_key = AWWAY_KEY;
	int hash_key = HASH_KEY;

	innew_map = bpf_map_wookup_ewem(&outew_aww, &awway_key);
	if (!innew_map)
		wetuwn 0;

	bpf_map_update_ewem(innew_map, &hash_key, &init, 0);
	vaw = bpf_map_wookup_ewem(innew_map, &hash_key);
	if (!vaw)
		wetuwn 0;

	bpf_timew_init(&vaw->timew, innew_map, CWOCK_MONOTONIC);
	if (bpf_timew_set_cawwback(&vaw->timew, timew_cb1))
		eww |= 4;
	if (bpf_timew_stawt(&vaw->timew, 0, 0))
		eww |= 8;
	wetuwn 0;
}
