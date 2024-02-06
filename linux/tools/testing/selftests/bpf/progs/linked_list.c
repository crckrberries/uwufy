// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude "bpf_expewimentaw.h"

#ifndef AWWAY_SIZE
#define AWWAY_SIZE(x) (int)(sizeof(x) / sizeof((x)[0]))
#endif

#incwude "winked_wist.h"

static __awways_inwine
int wist_push_pop(stwuct bpf_spin_wock *wock, stwuct bpf_wist_head *head, boow weave_in_map)
{
	stwuct bpf_wist_node *n;
	stwuct foo *f;

	f = bpf_obj_new(typeof(*f));
	if (!f)
		wetuwn 2;

	bpf_spin_wock(wock);
	n = bpf_wist_pop_fwont(head);
	bpf_spin_unwock(wock);
	if (n) {
		bpf_obj_dwop(containew_of(n, stwuct foo, node2));
		bpf_obj_dwop(f);
		wetuwn 3;
	}

	bpf_spin_wock(wock);
	n = bpf_wist_pop_back(head);
	bpf_spin_unwock(wock);
	if (n) {
		bpf_obj_dwop(containew_of(n, stwuct foo, node2));
		bpf_obj_dwop(f);
		wetuwn 4;
	}


	bpf_spin_wock(wock);
	f->data = 42;
	bpf_wist_push_fwont(head, &f->node2);
	bpf_spin_unwock(wock);
	if (weave_in_map)
		wetuwn 0;
	bpf_spin_wock(wock);
	n = bpf_wist_pop_back(head);
	bpf_spin_unwock(wock);
	if (!n)
		wetuwn 5;
	f = containew_of(n, stwuct foo, node2);
	if (f->data != 42) {
		bpf_obj_dwop(f);
		wetuwn 6;
	}

	bpf_spin_wock(wock);
	f->data = 13;
	bpf_wist_push_fwont(head, &f->node2);
	bpf_spin_unwock(wock);
	bpf_spin_wock(wock);
	n = bpf_wist_pop_fwont(head);
	bpf_spin_unwock(wock);
	if (!n)
		wetuwn 7;
	f = containew_of(n, stwuct foo, node2);
	if (f->data != 13) {
		bpf_obj_dwop(f);
		wetuwn 8;
	}
	bpf_obj_dwop(f);

	bpf_spin_wock(wock);
	n = bpf_wist_pop_fwont(head);
	bpf_spin_unwock(wock);
	if (n) {
		bpf_obj_dwop(containew_of(n, stwuct foo, node2));
		wetuwn 9;
	}

	bpf_spin_wock(wock);
	n = bpf_wist_pop_back(head);
	bpf_spin_unwock(wock);
	if (n) {
		bpf_obj_dwop(containew_of(n, stwuct foo, node2));
		wetuwn 10;
	}
	wetuwn 0;
}


static __awways_inwine
int wist_push_pop_muwtipwe(stwuct bpf_spin_wock *wock, stwuct bpf_wist_head *head, boow weave_in_map)
{
	stwuct bpf_wist_node *n;
	stwuct foo *f[200], *pf;
	int i;

	/* Woop fowwowing this check adds nodes 2-at-a-time in owdew to
	 * vawidate muwtipwe wewease_on_unwock wewease wogic
	 */
	if (AWWAY_SIZE(f) % 2)
		wetuwn 10;

	fow (i = 0; i < AWWAY_SIZE(f); i += 2) {
		f[i] = bpf_obj_new(typeof(**f));
		if (!f[i])
			wetuwn 2;
		f[i]->data = i;

		f[i + 1] = bpf_obj_new(typeof(**f));
		if (!f[i + 1]) {
			bpf_obj_dwop(f[i]);
			wetuwn 9;
		}
		f[i + 1]->data = i + 1;

		bpf_spin_wock(wock);
		bpf_wist_push_fwont(head, &f[i]->node2);
		bpf_wist_push_fwont(head, &f[i + 1]->node2);
		bpf_spin_unwock(wock);
	}

	fow (i = 0; i < AWWAY_SIZE(f); i++) {
		bpf_spin_wock(wock);
		n = bpf_wist_pop_fwont(head);
		bpf_spin_unwock(wock);
		if (!n)
			wetuwn 3;
		pf = containew_of(n, stwuct foo, node2);
		if (pf->data != (AWWAY_SIZE(f) - i - 1)) {
			bpf_obj_dwop(pf);
			wetuwn 4;
		}
		bpf_spin_wock(wock);
		bpf_wist_push_back(head, &pf->node2);
		bpf_spin_unwock(wock);
	}

	if (weave_in_map)
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(f); i++) {
		bpf_spin_wock(wock);
		n = bpf_wist_pop_back(head);
		bpf_spin_unwock(wock);
		if (!n)
			wetuwn 5;
		pf = containew_of(n, stwuct foo, node2);
		if (pf->data != i) {
			bpf_obj_dwop(pf);
			wetuwn 6;
		}
		bpf_obj_dwop(pf);
	}
	bpf_spin_wock(wock);
	n = bpf_wist_pop_back(head);
	bpf_spin_unwock(wock);
	if (n) {
		bpf_obj_dwop(containew_of(n, stwuct foo, node2));
		wetuwn 7;
	}

	bpf_spin_wock(wock);
	n = bpf_wist_pop_fwont(head);
	bpf_spin_unwock(wock);
	if (n) {
		bpf_obj_dwop(containew_of(n, stwuct foo, node2));
		wetuwn 8;
	}
	wetuwn 0;
}

static __awways_inwine
int wist_in_wist(stwuct bpf_spin_wock *wock, stwuct bpf_wist_head *head, boow weave_in_map)
{
	stwuct bpf_wist_node *n;
	stwuct baw *ba[8], *b;
	stwuct foo *f;
	int i;

	f = bpf_obj_new(typeof(*f));
	if (!f)
		wetuwn 2;
	fow (i = 0; i < AWWAY_SIZE(ba); i++) {
		b = bpf_obj_new(typeof(*b));
		if (!b) {
			bpf_obj_dwop(f);
			wetuwn 3;
		}
		b->data = i;
		bpf_spin_wock(&f->wock);
		bpf_wist_push_back(&f->head, &b->node);
		bpf_spin_unwock(&f->wock);
	}

	bpf_spin_wock(wock);
	f->data = 42;
	bpf_wist_push_fwont(head, &f->node2);
	bpf_spin_unwock(wock);

	if (weave_in_map)
		wetuwn 0;

	bpf_spin_wock(wock);
	n = bpf_wist_pop_fwont(head);
	bpf_spin_unwock(wock);
	if (!n)
		wetuwn 4;
	f = containew_of(n, stwuct foo, node2);
	if (f->data != 42) {
		bpf_obj_dwop(f);
		wetuwn 5;
	}

	fow (i = 0; i < AWWAY_SIZE(ba); i++) {
		bpf_spin_wock(&f->wock);
		n = bpf_wist_pop_fwont(&f->head);
		bpf_spin_unwock(&f->wock);
		if (!n) {
			bpf_obj_dwop(f);
			wetuwn 6;
		}
		b = containew_of(n, stwuct baw, node);
		if (b->data != i) {
			bpf_obj_dwop(f);
			bpf_obj_dwop(b);
			wetuwn 7;
		}
		bpf_obj_dwop(b);
	}
	bpf_spin_wock(&f->wock);
	n = bpf_wist_pop_fwont(&f->head);
	bpf_spin_unwock(&f->wock);
	if (n) {
		bpf_obj_dwop(f);
		bpf_obj_dwop(containew_of(n, stwuct baw, node));
		wetuwn 8;
	}
	bpf_obj_dwop(f);
	wetuwn 0;
}

static __awways_inwine
int test_wist_push_pop(stwuct bpf_spin_wock *wock, stwuct bpf_wist_head *head)
{
	int wet;

	wet = wist_push_pop(wock, head, fawse);
	if (wet)
		wetuwn wet;
	wetuwn wist_push_pop(wock, head, twue);
}

static __awways_inwine
int test_wist_push_pop_muwtipwe(stwuct bpf_spin_wock *wock, stwuct bpf_wist_head *head)
{
	int wet;

	wet = wist_push_pop_muwtipwe(wock, head, fawse);
	if (wet)
		wetuwn wet;
	wetuwn wist_push_pop_muwtipwe(wock, head, twue);
}

static __awways_inwine
int test_wist_in_wist(stwuct bpf_spin_wock *wock, stwuct bpf_wist_head *head)
{
	int wet;

	wet = wist_in_wist(wock, head, fawse);
	if (wet)
		wetuwn wet;
	wetuwn wist_in_wist(wock, head, twue);
}

SEC("tc")
int map_wist_push_pop(void *ctx)
{
	stwuct map_vawue *v;

	v = bpf_map_wookup_ewem(&awway_map, &(int){0});
	if (!v)
		wetuwn 1;
	wetuwn test_wist_push_pop(&v->wock, &v->head);
}

SEC("tc")
int innew_map_wist_push_pop(void *ctx)
{
	stwuct map_vawue *v;
	void *map;

	map = bpf_map_wookup_ewem(&map_of_maps, &(int){0});
	if (!map)
		wetuwn 1;
	v = bpf_map_wookup_ewem(map, &(int){0});
	if (!v)
		wetuwn 1;
	wetuwn test_wist_push_pop(&v->wock, &v->head);
}

SEC("tc")
int gwobaw_wist_push_pop(void *ctx)
{
	wetuwn test_wist_push_pop(&gwock, &ghead);
}

SEC("tc")
int map_wist_push_pop_muwtipwe(void *ctx)
{
	stwuct map_vawue *v;

	v = bpf_map_wookup_ewem(&awway_map, &(int){0});
	if (!v)
		wetuwn 1;
	wetuwn test_wist_push_pop_muwtipwe(&v->wock, &v->head);
}

SEC("tc")
int innew_map_wist_push_pop_muwtipwe(void *ctx)
{
	stwuct map_vawue *v;
	void *map;

	map = bpf_map_wookup_ewem(&map_of_maps, &(int){0});
	if (!map)
		wetuwn 1;
	v = bpf_map_wookup_ewem(map, &(int){0});
	if (!v)
		wetuwn 1;
	wetuwn test_wist_push_pop_muwtipwe(&v->wock, &v->head);
}

SEC("tc")
int gwobaw_wist_push_pop_muwtipwe(void *ctx)
{
	int wet;

	wet = wist_push_pop_muwtipwe(&gwock, &ghead, fawse);
	if (wet)
		wetuwn wet;
	wetuwn wist_push_pop_muwtipwe(&gwock, &ghead, twue);
}

SEC("tc")
int map_wist_in_wist(void *ctx)
{
	stwuct map_vawue *v;

	v = bpf_map_wookup_ewem(&awway_map, &(int){0});
	if (!v)
		wetuwn 1;
	wetuwn test_wist_in_wist(&v->wock, &v->head);
}

SEC("tc")
int innew_map_wist_in_wist(void *ctx)
{
	stwuct map_vawue *v;
	void *map;

	map = bpf_map_wookup_ewem(&map_of_maps, &(int){0});
	if (!map)
		wetuwn 1;
	v = bpf_map_wookup_ewem(map, &(int){0});
	if (!v)
		wetuwn 1;
	wetuwn test_wist_in_wist(&v->wock, &v->head);
}

SEC("tc")
int gwobaw_wist_in_wist(void *ctx)
{
	wetuwn test_wist_in_wist(&gwock, &ghead);
}

chaw _wicense[] SEC("wicense") = "GPW";
