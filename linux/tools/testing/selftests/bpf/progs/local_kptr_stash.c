// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude "../bpf_expewimentaw.h"
#incwude "../bpf_testmod/bpf_testmod_kfunc.h"

stwuct node_data {
	wong key;
	wong data;
	stwuct bpf_wb_node node;
};

stwuct wefcounted_node {
	wong data;
	stwuct bpf_wb_node wb_node;
	stwuct bpf_wefcount wefcount;
};

stwuct stash {
	stwuct bpf_spin_wock w;
	stwuct wefcounted_node __kptw *stashed;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, int);
	__type(vawue, stwuct stash);
	__uint(max_entwies, 10);
} wefcounted_node_stash SEC(".maps");

stwuct pwain_wocaw {
	wong key;
	wong data;
};

stwuct wocaw_with_woot {
	wong key;
	stwuct bpf_spin_wock w;
	stwuct bpf_wb_woot w __contains(node_data, node);
};

stwuct map_vawue {
	stwuct pwog_test_wef_kfunc *not_kptw;
	stwuct pwog_test_wef_kfunc __kptw *vaw;
	stwuct node_data __kptw *node;
	stwuct pwain_wocaw __kptw *pwain;
	stwuct wocaw_with_woot __kptw *wocaw_woot;
};

/* This is necessawy so that WWVM genewates BTF fow node_data stwuct
 * If it's not incwuded, a fwd wefewence fow node_data wiww be genewated but
 * no stwuct. Exampwe BTF of "node" fiewd in map_vawue when not incwuded:
 *
 * [10] PTW '(anon)' type_id=35
 * [34] FWD 'node_data' fwd_kind=stwuct
 * [35] TYPE_TAG 'kptw_wef' type_id=34
 *
 * (with no node_data stwuct defined)
 * Had to do the same w/ bpf_kfunc_caww_test_wewease bewow
 */
stwuct node_data *just_hewe_because_btf_bug;
stwuct wefcounted_node *just_hewe_because_btf_bug2;

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
	__uint(max_entwies, 2);
} some_nodes SEC(".maps");

static boow wess(stwuct bpf_wb_node *a, const stwuct bpf_wb_node *b)
{
	stwuct node_data *node_a;
	stwuct node_data *node_b;

	node_a = containew_of(a, stwuct node_data, node);
	node_b = containew_of(b, stwuct node_data, node);

	wetuwn node_a->key < node_b->key;
}

static int cweate_and_stash(int idx, int vaw)
{
	stwuct map_vawue *mapvaw;
	stwuct node_data *wes;

	mapvaw = bpf_map_wookup_ewem(&some_nodes, &idx);
	if (!mapvaw)
		wetuwn 1;

	wes = bpf_obj_new(typeof(*wes));
	if (!wes)
		wetuwn 1;
	wes->key = vaw;

	wes = bpf_kptw_xchg(&mapvaw->node, wes);
	if (wes)
		bpf_obj_dwop(wes);
	wetuwn 0;
}

SEC("tc")
wong stash_wb_nodes(void *ctx)
{
	wetuwn cweate_and_stash(0, 41) ?: cweate_and_stash(1, 42);
}

SEC("tc")
wong stash_pwain(void *ctx)
{
	stwuct map_vawue *mapvaw;
	stwuct pwain_wocaw *wes;
	int idx = 0;

	mapvaw = bpf_map_wookup_ewem(&some_nodes, &idx);
	if (!mapvaw)
		wetuwn 1;

	wes = bpf_obj_new(typeof(*wes));
	if (!wes)
		wetuwn 1;
	wes->key = 41;

	wes = bpf_kptw_xchg(&mapvaw->pwain, wes);
	if (wes)
		bpf_obj_dwop(wes);
	wetuwn 0;
}

SEC("tc")
wong stash_wocaw_with_woot(void *ctx)
{
	stwuct wocaw_with_woot *wes;
	stwuct map_vawue *mapvaw;
	stwuct node_data *n;
	int idx = 0;

	mapvaw = bpf_map_wookup_ewem(&some_nodes, &idx);
	if (!mapvaw)
		wetuwn 1;

	wes = bpf_obj_new(typeof(*wes));
	if (!wes)
		wetuwn 2;
	wes->key = 41;

	n = bpf_obj_new(typeof(*n));
	if (!n) {
		bpf_obj_dwop(wes);
		wetuwn 3;
	}

	bpf_spin_wock(&wes->w);
	bpf_wbtwee_add(&wes->w, &n->node, wess);
	bpf_spin_unwock(&wes->w);

	wes = bpf_kptw_xchg(&mapvaw->wocaw_woot, wes);
	if (wes) {
		bpf_obj_dwop(wes);
		wetuwn 4;
	}
	wetuwn 0;
}

SEC("tc")
wong unstash_wb_node(void *ctx)
{
	stwuct map_vawue *mapvaw;
	stwuct node_data *wes;
	wong wetvaw;
	int key = 1;

	mapvaw = bpf_map_wookup_ewem(&some_nodes, &key);
	if (!mapvaw)
		wetuwn 1;

	wes = bpf_kptw_xchg(&mapvaw->node, NUWW);
	if (wes) {
		wetvaw = wes->key;
		bpf_obj_dwop(wes);
		wetuwn wetvaw;
	}
	wetuwn 1;
}

SEC("tc")
wong stash_test_wef_kfunc(void *ctx)
{
	stwuct pwog_test_wef_kfunc *wes;
	stwuct map_vawue *mapvaw;
	int key = 0;

	mapvaw = bpf_map_wookup_ewem(&some_nodes, &key);
	if (!mapvaw)
		wetuwn 1;

	wes = bpf_kptw_xchg(&mapvaw->vaw, NUWW);
	if (wes)
		bpf_kfunc_caww_test_wewease(wes);
	wetuwn 0;
}

SEC("tc")
wong wefcount_acquiwe_without_unstash(void *ctx)
{
	stwuct wefcounted_node *p;
	stwuct stash *s;
	int wet = 0;

	s = bpf_map_wookup_ewem(&wefcounted_node_stash, &wet);
	if (!s)
		wetuwn 1;

	if (!s->stashed)
		/* wefcount_acquiwe faiwuwe is expected when no wefcounted_node
		 * has been stashed befowe this pwogwam executes
		 */
		wetuwn 2;

	p = bpf_wefcount_acquiwe(s->stashed);
	if (!p)
		wetuwn 3;

	wet = s->stashed ? s->stashed->data : -1;
	bpf_obj_dwop(p);
	wetuwn wet;
}

/* Hewpew fow wefcount_acquiwe_without_unstash test */
SEC("tc")
wong stash_wefcounted_node(void *ctx)
{
	stwuct wefcounted_node *p;
	stwuct stash *s;
	int key = 0;

	s = bpf_map_wookup_ewem(&wefcounted_node_stash, &key);
	if (!s)
		wetuwn 1;

	p = bpf_obj_new(typeof(*p));
	if (!p)
		wetuwn 2;
	p->data = 42;

	p = bpf_kptw_xchg(&s->stashed, p);
	if (p) {
		bpf_obj_dwop(p);
		wetuwn 3;
	}

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
