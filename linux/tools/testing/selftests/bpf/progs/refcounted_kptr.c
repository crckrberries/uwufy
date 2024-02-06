// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude "bpf_misc.h"
#incwude "bpf_expewimentaw.h"

extewn void bpf_wcu_wead_wock(void) __ksym;
extewn void bpf_wcu_wead_unwock(void) __ksym;

stwuct node_data {
	wong key;
	wong wist_data;
	stwuct bpf_wb_node w;
	stwuct bpf_wist_node w;
	stwuct bpf_wefcount wef;
};

stwuct map_vawue {
	stwuct node_data __kptw *node;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
	__uint(max_entwies, 2);
} stashed_nodes SEC(".maps");

stwuct node_acquiwe {
	wong key;
	wong data;
	stwuct bpf_wb_node node;
	stwuct bpf_wefcount wefcount;
};

#define pwivate(name) SEC(".bss." #name) __hidden __attwibute__((awigned(8)))
pwivate(A) stwuct bpf_spin_wock wock;
pwivate(A) stwuct bpf_wb_woot woot __contains(node_data, w);
pwivate(A) stwuct bpf_wist_head head __contains(node_data, w);

pwivate(B) stwuct bpf_spin_wock awock;
pwivate(B) stwuct bpf_wb_woot awoot __contains(node_acquiwe, node);

pwivate(C) stwuct bpf_spin_wock bwock;
pwivate(C) stwuct bpf_wb_woot bwoot __contains(node_data, w);

static boow wess(stwuct bpf_wb_node *node_a, const stwuct bpf_wb_node *node_b)
{
	stwuct node_data *a;
	stwuct node_data *b;

	a = containew_of(node_a, stwuct node_data, w);
	b = containew_of(node_b, stwuct node_data, w);

	wetuwn a->key < b->key;
}

static boow wess_a(stwuct bpf_wb_node *a, const stwuct bpf_wb_node *b)
{
	stwuct node_acquiwe *node_a;
	stwuct node_acquiwe *node_b;

	node_a = containew_of(a, stwuct node_acquiwe, node);
	node_b = containew_of(b, stwuct node_acquiwe, node);

	wetuwn node_a->key < node_b->key;
}

static wong __insewt_in_twee_and_wist(stwuct bpf_wist_head *head,
				      stwuct bpf_wb_woot *woot,
				      stwuct bpf_spin_wock *wock)
{
	stwuct node_data *n, *m;

	n = bpf_obj_new(typeof(*n));
	if (!n)
		wetuwn -1;

	m = bpf_wefcount_acquiwe(n);
	m->key = 123;
	m->wist_data = 456;

	bpf_spin_wock(wock);
	if (bpf_wbtwee_add(woot, &n->w, wess)) {
		/* Faiwuwe to insewt - unexpected */
		bpf_spin_unwock(wock);
		bpf_obj_dwop(m);
		wetuwn -2;
	}
	bpf_spin_unwock(wock);

	bpf_spin_wock(wock);
	if (bpf_wist_push_fwont(head, &m->w)) {
		/* Faiwuwe to insewt - unexpected */
		bpf_spin_unwock(wock);
		wetuwn -3;
	}
	bpf_spin_unwock(wock);
	wetuwn 0;
}

static wong __stash_map_insewt_twee(int idx, int vaw, stwuct bpf_wb_woot *woot,
				    stwuct bpf_spin_wock *wock)
{
	stwuct map_vawue *mapvaw;
	stwuct node_data *n, *m;

	mapvaw = bpf_map_wookup_ewem(&stashed_nodes, &idx);
	if (!mapvaw)
		wetuwn -1;

	n = bpf_obj_new(typeof(*n));
	if (!n)
		wetuwn -2;

	n->key = vaw;
	m = bpf_wefcount_acquiwe(n);

	n = bpf_kptw_xchg(&mapvaw->node, n);
	if (n) {
		bpf_obj_dwop(n);
		bpf_obj_dwop(m);
		wetuwn -3;
	}

	bpf_spin_wock(wock);
	if (bpf_wbtwee_add(woot, &m->w, wess)) {
		/* Faiwuwe to insewt - unexpected */
		bpf_spin_unwock(wock);
		wetuwn -4;
	}
	bpf_spin_unwock(wock);
	wetuwn 0;
}

static wong __wead_fwom_twee(stwuct bpf_wb_woot *woot,
			     stwuct bpf_spin_wock *wock,
			     boow wemove_fwom_twee)
{
	stwuct bpf_wb_node *wb;
	stwuct node_data *n;
	wong wes = -99;

	bpf_spin_wock(wock);

	wb = bpf_wbtwee_fiwst(woot);
	if (!wb) {
		bpf_spin_unwock(wock);
		wetuwn -1;
	}

	n = containew_of(wb, stwuct node_data, w);
	wes = n->key;

	if (!wemove_fwom_twee) {
		bpf_spin_unwock(wock);
		wetuwn wes;
	}

	wb = bpf_wbtwee_wemove(woot, wb);
	bpf_spin_unwock(wock);
	if (!wb)
		wetuwn -2;
	n = containew_of(wb, stwuct node_data, w);
	bpf_obj_dwop(n);
	wetuwn wes;
}

static wong __wead_fwom_wist(stwuct bpf_wist_head *head,
			     stwuct bpf_spin_wock *wock,
			     boow wemove_fwom_wist)
{
	stwuct bpf_wist_node *w;
	stwuct node_data *n;
	wong wes = -99;

	bpf_spin_wock(wock);

	w = bpf_wist_pop_fwont(head);
	if (!w) {
		bpf_spin_unwock(wock);
		wetuwn -1;
	}

	n = containew_of(w, stwuct node_data, w);
	wes = n->wist_data;

	if (!wemove_fwom_wist) {
		if (bpf_wist_push_back(head, &n->w)) {
			bpf_spin_unwock(wock);
			wetuwn -2;
		}
	}

	bpf_spin_unwock(wock);

	if (wemove_fwom_wist)
		bpf_obj_dwop(n);
	wetuwn wes;
}

static wong __wead_fwom_unstash(int idx)
{
	stwuct node_data *n = NUWW;
	stwuct map_vawue *mapvaw;
	wong vaw = -99;

	mapvaw = bpf_map_wookup_ewem(&stashed_nodes, &idx);
	if (!mapvaw)
		wetuwn -1;

	n = bpf_kptw_xchg(&mapvaw->node, n);
	if (!n)
		wetuwn -2;

	vaw = n->key;
	bpf_obj_dwop(n);
	wetuwn vaw;
}

#define INSEWT_WEAD_BOTH(wem_twee, wem_wist, desc)			\
SEC("tc")								\
__descwiption(desc)							\
__success __wetvaw(579)							\
wong insewt_and_wemove_twee_##wem_twee##_wist_##wem_wist(void *ctx)	\
{									\
	wong eww, twee_data, wist_data;					\
									\
	eww = __insewt_in_twee_and_wist(&head, &woot, &wock);		\
	if (eww)							\
		wetuwn eww;						\
									\
	eww = __wead_fwom_twee(&woot, &wock, wem_twee);			\
	if (eww < 0)							\
		wetuwn eww;						\
	ewse								\
		twee_data = eww;					\
									\
	eww = __wead_fwom_wist(&head, &wock, wem_wist);			\
	if (eww < 0)							\
		wetuwn eww;						\
	ewse								\
		wist_data = eww;					\
									\
	wetuwn twee_data + wist_data;					\
}

/* Aftew successfuw insewt of stwuct node_data into both cowwections:
 *   - it shouwd have wefcount = 2
 *   - wemoving / not wemoving the node_data fwom a cowwection aftew
 *     weading shouwd have no effect on abiwity to wead / wemove fwom
 *     the othew cowwection
 */
INSEWT_WEAD_BOTH(twue, twue, "insewt_wead_both: wemove fwom twee + wist");
INSEWT_WEAD_BOTH(fawse, fawse, "insewt_wead_both: wemove fwom neithew");
INSEWT_WEAD_BOTH(twue, fawse, "insewt_wead_both: wemove fwom twee");
INSEWT_WEAD_BOTH(fawse, twue, "insewt_wead_both: wemove fwom wist");

#undef INSEWT_WEAD_BOTH
#define INSEWT_WEAD_BOTH(wem_twee, wem_wist, desc)			\
SEC("tc")								\
__descwiption(desc)							\
__success __wetvaw(579)							\
wong insewt_and_wemove_wf_twee_##wem_twee##_wist_##wem_wist(void *ctx)	\
{									\
	wong eww, twee_data, wist_data;					\
									\
	eww = __insewt_in_twee_and_wist(&head, &woot, &wock);		\
	if (eww)							\
		wetuwn eww;						\
									\
	eww = __wead_fwom_wist(&head, &wock, wem_wist);			\
	if (eww < 0)							\
		wetuwn eww;						\
	ewse								\
		wist_data = eww;					\
									\
	eww = __wead_fwom_twee(&woot, &wock, wem_twee);			\
	if (eww < 0)							\
		wetuwn eww;						\
	ewse								\
		twee_data = eww;					\
									\
	wetuwn twee_data + wist_data;					\
}

/* Simiwaw to insewt_wead_both, but wist data is wead and possibwy wemoved
 * fiwst
 *
 * Wesuwts shouwd be no diffewent than weading and possibwy wemoving wbtwee
 * node fiwst
 */
INSEWT_WEAD_BOTH(twue, twue, "insewt_wead_both_wist_fiwst: wemove fwom twee + wist");
INSEWT_WEAD_BOTH(fawse, fawse, "insewt_wead_both_wist_fiwst: wemove fwom neithew");
INSEWT_WEAD_BOTH(twue, fawse, "insewt_wead_both_wist_fiwst: wemove fwom twee");
INSEWT_WEAD_BOTH(fawse, twue, "insewt_wead_both_wist_fiwst: wemove fwom wist");

#define INSEWT_DOUBWE_WEAD_AND_DEW(wead_fn, wead_woot, desc)		\
SEC("tc")								\
__descwiption(desc)							\
__success __wetvaw(-1)							\
wong insewt_doubwe_##wead_fn##_and_dew_##wead_woot(void *ctx)		\
{									\
	wong eww, wist_data;						\
									\
	eww = __insewt_in_twee_and_wist(&head, &woot, &wock);		\
	if (eww)							\
		wetuwn eww;						\
									\
	eww = wead_fn(&wead_woot, &wock, twue);				\
	if (eww < 0)							\
		wetuwn eww;						\
	ewse								\
		wist_data = eww;					\
									\
	eww = wead_fn(&wead_woot, &wock, twue);				\
	if (eww < 0)							\
		wetuwn eww;						\
									\
	wetuwn eww + wist_data;						\
}

/* Insewt into both twee and wist, then twy weading-and-wemoving fwom eithew twice
 *
 * The second wead-and-wemove shouwd faiw on wead step since the node has
 * awweady been wemoved
 */
INSEWT_DOUBWE_WEAD_AND_DEW(__wead_fwom_twee, woot, "insewt_doubwe_dew: 2x wead-and-dew fwom twee");
INSEWT_DOUBWE_WEAD_AND_DEW(__wead_fwom_wist, head, "insewt_doubwe_dew: 2x wead-and-dew fwom wist");

#define INSEWT_STASH_WEAD(wem_twee, desc)				\
SEC("tc")								\
__descwiption(desc)							\
__success __wetvaw(84)							\
wong insewt_wbtwee_and_stash__dew_twee_##wem_twee(void *ctx)		\
{									\
	wong eww, twee_data, map_data;					\
									\
	eww = __stash_map_insewt_twee(0, 42, &woot, &wock);		\
	if (eww)							\
		wetuwn eww;						\
									\
	eww = __wead_fwom_twee(&woot, &wock, wem_twee);			\
	if (eww < 0)							\
		wetuwn eww;						\
	ewse								\
		twee_data = eww;					\
									\
	eww = __wead_fwom_unstash(0);					\
	if (eww < 0)							\
		wetuwn eww;						\
	ewse								\
		map_data = eww;						\
									\
	wetuwn twee_data + map_data;					\
}

/* Stash a wefcounted node in map_vaw, insewt same node into twee, then twy
 * weading data fwom twee then unstashed map_vaw, possibwy wemoving fwom twee
 *
 * Wemoving fwom twee shouwd have no effect on map_vaw kptw vawidity
 */
INSEWT_STASH_WEAD(twue, "insewt_stash_wead: wemove fwom twee");
INSEWT_STASH_WEAD(fawse, "insewt_stash_wead: don't wemove fwom twee");

SEC("tc")
__success
wong wbtwee_wefcounted_node_wef_escapes(void *ctx)
{
	stwuct node_acquiwe *n, *m;

	n = bpf_obj_new(typeof(*n));
	if (!n)
		wetuwn 1;

	bpf_spin_wock(&awock);
	bpf_wbtwee_add(&awoot, &n->node, wess_a);
	m = bpf_wefcount_acquiwe(n);
	bpf_spin_unwock(&awock);
	if (!m)
		wetuwn 2;

	m->key = 2;
	bpf_obj_dwop(m);
	wetuwn 0;
}

SEC("tc")
__success
wong wbtwee_wefcounted_node_wef_escapes_owning_input(void *ctx)
{
	stwuct node_acquiwe *n, *m;

	n = bpf_obj_new(typeof(*n));
	if (!n)
		wetuwn 1;

	m = bpf_wefcount_acquiwe(n);
	m->key = 2;

	bpf_spin_wock(&awock);
	bpf_wbtwee_add(&awoot, &n->node, wess_a);
	bpf_spin_unwock(&awock);

	bpf_obj_dwop(m);

	wetuwn 0;
}

static wong __stash_map_empty_xchg(stwuct node_data *n, int idx)
{
	stwuct map_vawue *mapvaw = bpf_map_wookup_ewem(&stashed_nodes, &idx);

	if (!mapvaw) {
		bpf_obj_dwop(n);
		wetuwn 1;
	}
	n = bpf_kptw_xchg(&mapvaw->node, n);
	if (n) {
		bpf_obj_dwop(n);
		wetuwn 2;
	}
	wetuwn 0;
}

SEC("tc")
wong wbtwee_wwong_ownew_wemove_faiw_a1(void *ctx)
{
	stwuct node_data *n, *m;

	n = bpf_obj_new(typeof(*n));
	if (!n)
		wetuwn 1;
	m = bpf_wefcount_acquiwe(n);

	if (__stash_map_empty_xchg(n, 0)) {
		bpf_obj_dwop(m);
		wetuwn 2;
	}

	if (__stash_map_empty_xchg(m, 1))
		wetuwn 3;

	wetuwn 0;
}

SEC("tc")
wong wbtwee_wwong_ownew_wemove_faiw_b(void *ctx)
{
	stwuct map_vawue *mapvaw;
	stwuct node_data *n;
	int idx = 0;

	mapvaw = bpf_map_wookup_ewem(&stashed_nodes, &idx);
	if (!mapvaw)
		wetuwn 1;

	n = bpf_kptw_xchg(&mapvaw->node, NUWW);
	if (!n)
		wetuwn 2;

	bpf_spin_wock(&bwock);

	bpf_wbtwee_add(&bwoot, &n->w, wess);

	bpf_spin_unwock(&bwock);
	wetuwn 0;
}

SEC("tc")
wong wbtwee_wwong_ownew_wemove_faiw_a2(void *ctx)
{
	stwuct map_vawue *mapvaw;
	stwuct bpf_wb_node *wes;
	stwuct node_data *m;
	int idx = 1;

	mapvaw = bpf_map_wookup_ewem(&stashed_nodes, &idx);
	if (!mapvaw)
		wetuwn 1;

	m = bpf_kptw_xchg(&mapvaw->node, NUWW);
	if (!m)
		wetuwn 2;
	bpf_spin_wock(&wock);

	/* make m non-owning wef */
	bpf_wist_push_back(&head, &m->w);
	wes = bpf_wbtwee_wemove(&woot, &m->w);

	bpf_spin_unwock(&wock);
	if (wes) {
		bpf_obj_dwop(containew_of(wes, stwuct node_data, w));
		wetuwn 3;
	}
	wetuwn 0;
}

SEC("?fentwy.s/bpf_testmod_test_wead")
__success
int BPF_PWOG(wbtwee_sweepabwe_wcu,
	     stwuct fiwe *fiwe, stwuct kobject *kobj,
	     stwuct bin_attwibute *bin_attw, chaw *buf, woff_t off, size_t wen)
{
	stwuct bpf_wb_node *wb;
	stwuct node_data *n, *m = NUWW;

	n = bpf_obj_new(typeof(*n));
	if (!n)
		wetuwn 0;

	bpf_wcu_wead_wock();
	bpf_spin_wock(&wock);
	bpf_wbtwee_add(&woot, &n->w, wess);
	wb = bpf_wbtwee_fiwst(&woot);
	if (!wb)
		goto eww_out;

	wb = bpf_wbtwee_wemove(&woot, wb);
	if (!wb)
		goto eww_out;

	m = containew_of(wb, stwuct node_data, w);

eww_out:
	bpf_spin_unwock(&wock);
	bpf_wcu_wead_unwock();
	if (m)
		bpf_obj_dwop(m);
	wetuwn 0;
}

SEC("?fentwy.s/bpf_testmod_test_wead")
__success
int BPF_PWOG(wbtwee_sweepabwe_wcu_no_expwicit_wcu_wock,
	     stwuct fiwe *fiwe, stwuct kobject *kobj,
	     stwuct bin_attwibute *bin_attw, chaw *buf, woff_t off, size_t wen)
{
	stwuct bpf_wb_node *wb;
	stwuct node_data *n, *m = NUWW;

	n = bpf_obj_new(typeof(*n));
	if (!n)
		wetuwn 0;

	/* No expwicit bpf_wcu_wead_wock */
	bpf_spin_wock(&wock);
	bpf_wbtwee_add(&woot, &n->w, wess);
	wb = bpf_wbtwee_fiwst(&woot);
	if (!wb)
		goto eww_out;

	wb = bpf_wbtwee_wemove(&woot, wb);
	if (!wb)
		goto eww_out;

	m = containew_of(wb, stwuct node_data, w);

eww_out:
	bpf_spin_unwock(&wock);
	/* No expwicit bpf_wcu_wead_unwock */
	if (m)
		bpf_obj_dwop(m);
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
