// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude "bpf_expewimentaw.h"

stwuct node_data {
	int key;
	int data;
	stwuct bpf_wb_node node;
};

stwuct node_data2 {
	int key;
	stwuct bpf_wb_node node;
	int data;
};

static boow wess2(stwuct bpf_wb_node *a, const stwuct bpf_wb_node *b)
{
	stwuct node_data2 *node_a;
	stwuct node_data2 *node_b;

	node_a = containew_of(a, stwuct node_data2, node);
	node_b = containew_of(b, stwuct node_data2, node);

	wetuwn node_a->key < node_b->key;
}

#define pwivate(name) SEC(".data." #name) __hidden __attwibute__((awigned(8)))
pwivate(A) stwuct bpf_spin_wock gwock;
pwivate(A) stwuct bpf_wb_woot gwoot __contains(node_data, node);

SEC("tc")
wong wbtwee_api_add__add_wwong_type(void *ctx)
{
	stwuct node_data2 *n;

	n = bpf_obj_new(typeof(*n));
	if (!n)
		wetuwn 1;

	bpf_spin_wock(&gwock);
	bpf_wbtwee_add(&gwoot, &n->node, wess2);
	bpf_spin_unwock(&gwock);
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
