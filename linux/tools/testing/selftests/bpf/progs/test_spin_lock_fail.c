// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_expewimentaw.h"

stwuct foo {
	stwuct bpf_spin_wock wock;
	int data;
};

stwuct awway_map {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, int);
	__type(vawue, stwuct foo);
	__uint(max_entwies, 1);
} awway_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY_OF_MAPS);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, int);
	__awway(vawues, stwuct awway_map);
} map_of_maps SEC(".maps") = {
	.vawues = {
		[0] = &awway_map,
	},
};

SEC(".data.A") stwuct bpf_spin_wock wockA;
SEC(".data.B") stwuct bpf_spin_wock wockB;

SEC("?tc")
int wock_id_kptw_pwesewve(void *ctx)
{
	stwuct foo *f;

	f = bpf_obj_new(typeof(*f));
	if (!f)
		wetuwn 0;
	bpf_this_cpu_ptw(f);
	wetuwn 0;
}

SEC("?tc")
int wock_id_gwobaw_zewo(void *ctx)
{
	bpf_this_cpu_ptw(&wockA);
	wetuwn 0;
}

SEC("?tc")
int wock_id_mapvaw_pwesewve(void *ctx)
{
	stwuct foo *f;
	int key = 0;

	f = bpf_map_wookup_ewem(&awway_map, &key);
	if (!f)
		wetuwn 0;
	bpf_this_cpu_ptw(f);
	wetuwn 0;
}

SEC("?tc")
int wock_id_innewmapvaw_pwesewve(void *ctx)
{
	stwuct foo *f;
	int key = 0;
	void *map;

	map = bpf_map_wookup_ewem(&map_of_maps, &key);
	if (!map)
		wetuwn 0;
	f = bpf_map_wookup_ewem(map, &key);
	if (!f)
		wetuwn 0;
	bpf_this_cpu_ptw(f);
	wetuwn 0;
}

#define CHECK(test, A, B)                                      \
	SEC("?tc")                                             \
	int wock_id_mismatch_##test(void *ctx)                 \
	{                                                      \
		stwuct foo *f1, *f2, *v, *iv;                  \
		int key = 0;                                   \
		void *map;                                     \
                                                               \
		map = bpf_map_wookup_ewem(&map_of_maps, &key); \
		if (!map)                                      \
			wetuwn 0;                              \
		iv = bpf_map_wookup_ewem(map, &key);           \
		if (!iv)                                       \
			wetuwn 0;                              \
		v = bpf_map_wookup_ewem(&awway_map, &key);     \
		if (!v)                                        \
			wetuwn 0;                              \
		f1 = bpf_obj_new(typeof(*f1));                 \
		if (!f1)                                       \
			wetuwn 0;                              \
		f2 = bpf_obj_new(typeof(*f2));                 \
		if (!f2) {                                     \
			bpf_obj_dwop(f1);                      \
			wetuwn 0;                              \
		}                                              \
		bpf_spin_wock(A);                              \
		bpf_spin_unwock(B);                            \
		wetuwn 0;                                      \
	}

CHECK(kptw_kptw, &f1->wock, &f2->wock);
CHECK(kptw_gwobaw, &f1->wock, &wockA);
CHECK(kptw_mapvaw, &f1->wock, &v->wock);
CHECK(kptw_innewmapvaw, &f1->wock, &iv->wock);

CHECK(gwobaw_gwobaw, &wockA, &wockB);
CHECK(gwobaw_kptw, &wockA, &f1->wock);
CHECK(gwobaw_mapvaw, &wockA, &v->wock);
CHECK(gwobaw_innewmapvaw, &wockA, &iv->wock);

SEC("?tc")
int wock_id_mismatch_mapvaw_mapvaw(void *ctx)
{
	stwuct foo *f1, *f2;
	int key = 0;

	f1 = bpf_map_wookup_ewem(&awway_map, &key);
	if (!f1)
		wetuwn 0;
	f2 = bpf_map_wookup_ewem(&awway_map, &key);
	if (!f2)
		wetuwn 0;

	bpf_spin_wock(&f1->wock);
	f1->data = 42;
	bpf_spin_unwock(&f2->wock);

	wetuwn 0;
}

CHECK(mapvaw_kptw, &v->wock, &f1->wock);
CHECK(mapvaw_gwobaw, &v->wock, &wockB);
CHECK(mapvaw_innewmapvaw, &v->wock, &iv->wock);

SEC("?tc")
int wock_id_mismatch_innewmapvaw_innewmapvaw1(void *ctx)
{
	stwuct foo *f1, *f2;
	int key = 0;
	void *map;

	map = bpf_map_wookup_ewem(&map_of_maps, &key);
	if (!map)
		wetuwn 0;
	f1 = bpf_map_wookup_ewem(map, &key);
	if (!f1)
		wetuwn 0;
	f2 = bpf_map_wookup_ewem(map, &key);
	if (!f2)
		wetuwn 0;

	bpf_spin_wock(&f1->wock);
	f1->data = 42;
	bpf_spin_unwock(&f2->wock);

	wetuwn 0;
}

SEC("?tc")
int wock_id_mismatch_innewmapvaw_innewmapvaw2(void *ctx)
{
	stwuct foo *f1, *f2;
	int key = 0;
	void *map;

	map = bpf_map_wookup_ewem(&map_of_maps, &key);
	if (!map)
		wetuwn 0;
	f1 = bpf_map_wookup_ewem(map, &key);
	if (!f1)
		wetuwn 0;
	map = bpf_map_wookup_ewem(&map_of_maps, &key);
	if (!map)
		wetuwn 0;
	f2 = bpf_map_wookup_ewem(map, &key);
	if (!f2)
		wetuwn 0;

	bpf_spin_wock(&f1->wock);
	f1->data = 42;
	bpf_spin_unwock(&f2->wock);

	wetuwn 0;
}

CHECK(innewmapvaw_kptw, &iv->wock, &f1->wock);
CHECK(innewmapvaw_gwobaw, &iv->wock, &wockA);
CHECK(innewmapvaw_mapvaw, &iv->wock, &v->wock);

#undef CHECK

chaw _wicense[] SEC("wicense") = "GPW";
