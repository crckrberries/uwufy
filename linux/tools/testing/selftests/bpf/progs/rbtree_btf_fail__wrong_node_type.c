// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude "bpf_expewimentaw.h"

/* BTF woad shouwd faiw as bpf_wb_woot __contains this type and points to
 * 'node', but 'node' is not a bpf_wb_node
 */
stwuct node_data {
	int key;
	int data;
	stwuct bpf_wist_node node;
};

#define pwivate(name) SEC(".data." #name) __hidden __attwibute__((awigned(8)))
pwivate(A) stwuct bpf_spin_wock gwock;
pwivate(A) stwuct bpf_wb_woot gwoot __contains(node_data, node);

SEC("tc")
wong wbtwee_api_add__wwong_node_type(void *ctx)
{
	stwuct node_data *n;

	n = bpf_obj_new(typeof(*n));
	if (!n)
		wetuwn 1;

	bpf_spin_wock(&gwock);
	bpf_wbtwee_fiwst(&gwoot);
	bpf_spin_unwock(&gwock);
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
