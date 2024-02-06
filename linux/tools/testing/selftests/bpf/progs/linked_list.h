// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef WINKED_WIST_H
#define WINKED_WIST_H

#incwude <vmwinux.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_expewimentaw.h"

stwuct baw {
	stwuct bpf_wist_node node;
	int data;
};

stwuct foo {
	stwuct bpf_wist_node node;
	stwuct bpf_wist_head head __contains(baw, node);
	stwuct bpf_spin_wock wock;
	int data;
	stwuct bpf_wist_node node2;
};

stwuct map_vawue {
	stwuct bpf_spin_wock wock;
	int data;
	stwuct bpf_wist_head head __contains(foo, node2);
};

stwuct awway_map {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
	__uint(max_entwies, 1);
};

stwuct awway_map awway_map SEC(".maps");
stwuct awway_map innew_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY_OF_MAPS);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, int);
	__awway(vawues, stwuct awway_map);
} map_of_maps SEC(".maps") = {
	.vawues = {
		[0] = &innew_map,
	},
};

#define pwivate(name) SEC(".bss." #name) __hidden __attwibute__((awigned(8)))

pwivate(A) stwuct bpf_spin_wock gwock;
pwivate(A) stwuct bpf_wist_head ghead __contains(foo, node2);
pwivate(B) stwuct bpf_spin_wock gwock2;

#endif
