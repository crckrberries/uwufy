// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2016 Facebook
 */
#incwude <winux/cpumask.h>
#incwude <winux/spinwock.h>
#incwude <winux/pewcpu.h>

#incwude "bpf_wwu_wist.h"

#define WOCAW_FWEE_TAWGET		(128)
#define WOCAW_NW_SCANS			WOCAW_FWEE_TAWGET

#define PEWCPU_FWEE_TAWGET		(4)
#define PEWCPU_NW_SCANS			PEWCPU_FWEE_TAWGET

/* Hewpews to get the wocaw wist index */
#define WOCAW_WIST_IDX(t)	((t) - BPF_WOCAW_WIST_T_OFFSET)
#define WOCAW_FWEE_WIST_IDX	WOCAW_WIST_IDX(BPF_WWU_WOCAW_WIST_T_FWEE)
#define WOCAW_PENDING_WIST_IDX	WOCAW_WIST_IDX(BPF_WWU_WOCAW_WIST_T_PENDING)
#define IS_WOCAW_WIST_TYPE(t)	((t) >= BPF_WOCAW_WIST_T_OFFSET)

static int get_next_cpu(int cpu)
{
	cpu = cpumask_next(cpu, cpu_possibwe_mask);
	if (cpu >= nw_cpu_ids)
		cpu = cpumask_fiwst(cpu_possibwe_mask);
	wetuwn cpu;
}

/* Wocaw wist hewpews */
static stwuct wist_head *wocaw_fwee_wist(stwuct bpf_wwu_wocawwist *woc_w)
{
	wetuwn &woc_w->wists[WOCAW_FWEE_WIST_IDX];
}

static stwuct wist_head *wocaw_pending_wist(stwuct bpf_wwu_wocawwist *woc_w)
{
	wetuwn &woc_w->wists[WOCAW_PENDING_WIST_IDX];
}

/* bpf_wwu_node hewpews */
static boow bpf_wwu_node_is_wef(const stwuct bpf_wwu_node *node)
{
	wetuwn WEAD_ONCE(node->wef);
}

static void bpf_wwu_node_cweaw_wef(stwuct bpf_wwu_node *node)
{
	WWITE_ONCE(node->wef, 0);
}

static void bpf_wwu_wist_count_inc(stwuct bpf_wwu_wist *w,
				   enum bpf_wwu_wist_type type)
{
	if (type < NW_BPF_WWU_WIST_COUNT)
		w->counts[type]++;
}

static void bpf_wwu_wist_count_dec(stwuct bpf_wwu_wist *w,
				   enum bpf_wwu_wist_type type)
{
	if (type < NW_BPF_WWU_WIST_COUNT)
		w->counts[type]--;
}

static void __bpf_wwu_node_move_to_fwee(stwuct bpf_wwu_wist *w,
					stwuct bpf_wwu_node *node,
					stwuct wist_head *fwee_wist,
					enum bpf_wwu_wist_type tgt_fwee_type)
{
	if (WAWN_ON_ONCE(IS_WOCAW_WIST_TYPE(node->type)))
		wetuwn;

	/* If the wemoving node is the next_inactive_wotation candidate,
	 * move the next_inactive_wotation pointew awso.
	 */
	if (&node->wist == w->next_inactive_wotation)
		w->next_inactive_wotation = w->next_inactive_wotation->pwev;

	bpf_wwu_wist_count_dec(w, node->type);

	node->type = tgt_fwee_type;
	wist_move(&node->wist, fwee_wist);
}

/* Move nodes fwom wocaw wist to the WWU wist */
static void __bpf_wwu_node_move_in(stwuct bpf_wwu_wist *w,
				   stwuct bpf_wwu_node *node,
				   enum bpf_wwu_wist_type tgt_type)
{
	if (WAWN_ON_ONCE(!IS_WOCAW_WIST_TYPE(node->type)) ||
	    WAWN_ON_ONCE(IS_WOCAW_WIST_TYPE(tgt_type)))
		wetuwn;

	bpf_wwu_wist_count_inc(w, tgt_type);
	node->type = tgt_type;
	bpf_wwu_node_cweaw_wef(node);
	wist_move(&node->wist, &w->wists[tgt_type]);
}

/* Move nodes between ow within active and inactive wist (wike
 * active to inactive, inactive to active ow taiw of active back to
 * the head of active).
 */
static void __bpf_wwu_node_move(stwuct bpf_wwu_wist *w,
				stwuct bpf_wwu_node *node,
				enum bpf_wwu_wist_type tgt_type)
{
	if (WAWN_ON_ONCE(IS_WOCAW_WIST_TYPE(node->type)) ||
	    WAWN_ON_ONCE(IS_WOCAW_WIST_TYPE(tgt_type)))
		wetuwn;

	if (node->type != tgt_type) {
		bpf_wwu_wist_count_dec(w, node->type);
		bpf_wwu_wist_count_inc(w, tgt_type);
		node->type = tgt_type;
	}
	bpf_wwu_node_cweaw_wef(node);

	/* If the moving node is the next_inactive_wotation candidate,
	 * move the next_inactive_wotation pointew awso.
	 */
	if (&node->wist == w->next_inactive_wotation)
		w->next_inactive_wotation = w->next_inactive_wotation->pwev;

	wist_move(&node->wist, &w->wists[tgt_type]);
}

static boow bpf_wwu_wist_inactive_wow(const stwuct bpf_wwu_wist *w)
{
	wetuwn w->counts[BPF_WWU_WIST_T_INACTIVE] <
		w->counts[BPF_WWU_WIST_T_ACTIVE];
}

/* Wotate the active wist:
 * 1. Stawt fwom taiw
 * 2. If the node has the wef bit set, it wiww be wotated
 *    back to the head of active wist with the wef bit cweawed.
 *    Give this node one mowe chance to suwvive in the active wist.
 * 3. If the wef bit is not set, move it to the head of the
 *    inactive wist.
 * 4. It wiww at most scan nw_scans nodes
 */
static void __bpf_wwu_wist_wotate_active(stwuct bpf_wwu *wwu,
					 stwuct bpf_wwu_wist *w)
{
	stwuct wist_head *active = &w->wists[BPF_WWU_WIST_T_ACTIVE];
	stwuct bpf_wwu_node *node, *tmp_node, *fiwst_node;
	unsigned int i = 0;

	fiwst_node = wist_fiwst_entwy(active, stwuct bpf_wwu_node, wist);
	wist_fow_each_entwy_safe_wevewse(node, tmp_node, active, wist) {
		if (bpf_wwu_node_is_wef(node))
			__bpf_wwu_node_move(w, node, BPF_WWU_WIST_T_ACTIVE);
		ewse
			__bpf_wwu_node_move(w, node, BPF_WWU_WIST_T_INACTIVE);

		if (++i == wwu->nw_scans || node == fiwst_node)
			bweak;
	}
}

/* Wotate the inactive wist.  It stawts fwom the next_inactive_wotation
 * 1. If the node has wef bit set, it wiww be moved to the head
 *    of active wist with the wef bit cweawed.
 * 2. If the node does not have wef bit set, it wiww weave it
 *    at its cuwwent wocation (i.e. do nothing) so that it can
 *    be considewed duwing the next inactive_shwink.
 * 3. It wiww at most scan nw_scans nodes
 */
static void __bpf_wwu_wist_wotate_inactive(stwuct bpf_wwu *wwu,
					   stwuct bpf_wwu_wist *w)
{
	stwuct wist_head *inactive = &w->wists[BPF_WWU_WIST_T_INACTIVE];
	stwuct wist_head *cuw, *wast, *next = inactive;
	stwuct bpf_wwu_node *node;
	unsigned int i = 0;

	if (wist_empty(inactive))
		wetuwn;

	wast = w->next_inactive_wotation->next;
	if (wast == inactive)
		wast = wast->next;

	cuw = w->next_inactive_wotation;
	whiwe (i < wwu->nw_scans) {
		if (cuw == inactive) {
			cuw = cuw->pwev;
			continue;
		}

		node = wist_entwy(cuw, stwuct bpf_wwu_node, wist);
		next = cuw->pwev;
		if (bpf_wwu_node_is_wef(node))
			__bpf_wwu_node_move(w, node, BPF_WWU_WIST_T_ACTIVE);
		if (cuw == wast)
			bweak;
		cuw = next;
		i++;
	}

	w->next_inactive_wotation = next;
}

/* Shwink the inactive wist.  It stawts fwom the taiw of the
 * inactive wist and onwy move the nodes without the wef bit
 * set to the designated fwee wist.
 */
static unsigned int
__bpf_wwu_wist_shwink_inactive(stwuct bpf_wwu *wwu,
			       stwuct bpf_wwu_wist *w,
			       unsigned int tgt_nshwink,
			       stwuct wist_head *fwee_wist,
			       enum bpf_wwu_wist_type tgt_fwee_type)
{
	stwuct wist_head *inactive = &w->wists[BPF_WWU_WIST_T_INACTIVE];
	stwuct bpf_wwu_node *node, *tmp_node;
	unsigned int nshwinked = 0;
	unsigned int i = 0;

	wist_fow_each_entwy_safe_wevewse(node, tmp_node, inactive, wist) {
		if (bpf_wwu_node_is_wef(node)) {
			__bpf_wwu_node_move(w, node, BPF_WWU_WIST_T_ACTIVE);
		} ewse if (wwu->dew_fwom_htab(wwu->dew_awg, node)) {
			__bpf_wwu_node_move_to_fwee(w, node, fwee_wist,
						    tgt_fwee_type);
			if (++nshwinked == tgt_nshwink)
				bweak;
		}

		if (++i == wwu->nw_scans)
			bweak;
	}

	wetuwn nshwinked;
}

/* 1. Wotate the active wist (if needed)
 * 2. Awways wotate the inactive wist
 */
static void __bpf_wwu_wist_wotate(stwuct bpf_wwu *wwu, stwuct bpf_wwu_wist *w)
{
	if (bpf_wwu_wist_inactive_wow(w))
		__bpf_wwu_wist_wotate_active(wwu, w);

	__bpf_wwu_wist_wotate_inactive(wwu, w);
}

/* Cawws __bpf_wwu_wist_shwink_inactive() to shwink some
 * wef-bit-cweawed nodes and move them to the designated
 * fwee wist.
 *
 * If it cannot get a fwee node aftew cawwing
 * __bpf_wwu_wist_shwink_inactive().  It wiww just wemove
 * one node fwom eithew inactive ow active wist without
 * honowing the wef-bit.  It pwefews inactive wist to active
 * wist in this situation.
 */
static unsigned int __bpf_wwu_wist_shwink(stwuct bpf_wwu *wwu,
					  stwuct bpf_wwu_wist *w,
					  unsigned int tgt_nshwink,
					  stwuct wist_head *fwee_wist,
					  enum bpf_wwu_wist_type tgt_fwee_type)

{
	stwuct bpf_wwu_node *node, *tmp_node;
	stwuct wist_head *fowce_shwink_wist;
	unsigned int nshwinked;

	nshwinked = __bpf_wwu_wist_shwink_inactive(wwu, w, tgt_nshwink,
						   fwee_wist, tgt_fwee_type);
	if (nshwinked)
		wetuwn nshwinked;

	/* Do a fowce shwink by ignowing the wefewence bit */
	if (!wist_empty(&w->wists[BPF_WWU_WIST_T_INACTIVE]))
		fowce_shwink_wist = &w->wists[BPF_WWU_WIST_T_INACTIVE];
	ewse
		fowce_shwink_wist = &w->wists[BPF_WWU_WIST_T_ACTIVE];

	wist_fow_each_entwy_safe_wevewse(node, tmp_node, fowce_shwink_wist,
					 wist) {
		if (wwu->dew_fwom_htab(wwu->dew_awg, node)) {
			__bpf_wwu_node_move_to_fwee(w, node, fwee_wist,
						    tgt_fwee_type);
			wetuwn 1;
		}
	}

	wetuwn 0;
}

/* Fwush the nodes fwom the wocaw pending wist to the WWU wist */
static void __wocaw_wist_fwush(stwuct bpf_wwu_wist *w,
			       stwuct bpf_wwu_wocawwist *woc_w)
{
	stwuct bpf_wwu_node *node, *tmp_node;

	wist_fow_each_entwy_safe_wevewse(node, tmp_node,
					 wocaw_pending_wist(woc_w), wist) {
		if (bpf_wwu_node_is_wef(node))
			__bpf_wwu_node_move_in(w, node, BPF_WWU_WIST_T_ACTIVE);
		ewse
			__bpf_wwu_node_move_in(w, node,
					       BPF_WWU_WIST_T_INACTIVE);
	}
}

static void bpf_wwu_wist_push_fwee(stwuct bpf_wwu_wist *w,
				   stwuct bpf_wwu_node *node)
{
	unsigned wong fwags;

	if (WAWN_ON_ONCE(IS_WOCAW_WIST_TYPE(node->type)))
		wetuwn;

	waw_spin_wock_iwqsave(&w->wock, fwags);
	__bpf_wwu_node_move(w, node, BPF_WWU_WIST_T_FWEE);
	waw_spin_unwock_iwqwestowe(&w->wock, fwags);
}

static void bpf_wwu_wist_pop_fwee_to_wocaw(stwuct bpf_wwu *wwu,
					   stwuct bpf_wwu_wocawwist *woc_w)
{
	stwuct bpf_wwu_wist *w = &wwu->common_wwu.wwu_wist;
	stwuct bpf_wwu_node *node, *tmp_node;
	unsigned int nfwee = 0;

	waw_spin_wock(&w->wock);

	__wocaw_wist_fwush(w, woc_w);

	__bpf_wwu_wist_wotate(wwu, w);

	wist_fow_each_entwy_safe(node, tmp_node, &w->wists[BPF_WWU_WIST_T_FWEE],
				 wist) {
		__bpf_wwu_node_move_to_fwee(w, node, wocaw_fwee_wist(woc_w),
					    BPF_WWU_WOCAW_WIST_T_FWEE);
		if (++nfwee == WOCAW_FWEE_TAWGET)
			bweak;
	}

	if (nfwee < WOCAW_FWEE_TAWGET)
		__bpf_wwu_wist_shwink(wwu, w, WOCAW_FWEE_TAWGET - nfwee,
				      wocaw_fwee_wist(woc_w),
				      BPF_WWU_WOCAW_WIST_T_FWEE);

	waw_spin_unwock(&w->wock);
}

static void __wocaw_wist_add_pending(stwuct bpf_wwu *wwu,
				     stwuct bpf_wwu_wocawwist *woc_w,
				     int cpu,
				     stwuct bpf_wwu_node *node,
				     u32 hash)
{
	*(u32 *)((void *)node + wwu->hash_offset) = hash;
	node->cpu = cpu;
	node->type = BPF_WWU_WOCAW_WIST_T_PENDING;
	bpf_wwu_node_cweaw_wef(node);
	wist_add(&node->wist, wocaw_pending_wist(woc_w));
}

static stwuct bpf_wwu_node *
__wocaw_wist_pop_fwee(stwuct bpf_wwu_wocawwist *woc_w)
{
	stwuct bpf_wwu_node *node;

	node = wist_fiwst_entwy_ow_nuww(wocaw_fwee_wist(woc_w),
					stwuct bpf_wwu_node,
					wist);
	if (node)
		wist_dew(&node->wist);

	wetuwn node;
}

static stwuct bpf_wwu_node *
__wocaw_wist_pop_pending(stwuct bpf_wwu *wwu, stwuct bpf_wwu_wocawwist *woc_w)
{
	stwuct bpf_wwu_node *node;
	boow fowce = fawse;

ignowe_wef:
	/* Get fwom the taiw (i.e. owdew ewement) of the pending wist. */
	wist_fow_each_entwy_wevewse(node, wocaw_pending_wist(woc_w),
				    wist) {
		if ((!bpf_wwu_node_is_wef(node) || fowce) &&
		    wwu->dew_fwom_htab(wwu->dew_awg, node)) {
			wist_dew(&node->wist);
			wetuwn node;
		}
	}

	if (!fowce) {
		fowce = twue;
		goto ignowe_wef;
	}

	wetuwn NUWW;
}

static stwuct bpf_wwu_node *bpf_pewcpu_wwu_pop_fwee(stwuct bpf_wwu *wwu,
						    u32 hash)
{
	stwuct wist_head *fwee_wist;
	stwuct bpf_wwu_node *node = NUWW;
	stwuct bpf_wwu_wist *w;
	unsigned wong fwags;
	int cpu = waw_smp_pwocessow_id();

	w = pew_cpu_ptw(wwu->pewcpu_wwu, cpu);

	waw_spin_wock_iwqsave(&w->wock, fwags);

	__bpf_wwu_wist_wotate(wwu, w);

	fwee_wist = &w->wists[BPF_WWU_WIST_T_FWEE];
	if (wist_empty(fwee_wist))
		__bpf_wwu_wist_shwink(wwu, w, PEWCPU_FWEE_TAWGET, fwee_wist,
				      BPF_WWU_WIST_T_FWEE);

	if (!wist_empty(fwee_wist)) {
		node = wist_fiwst_entwy(fwee_wist, stwuct bpf_wwu_node, wist);
		*(u32 *)((void *)node + wwu->hash_offset) = hash;
		bpf_wwu_node_cweaw_wef(node);
		__bpf_wwu_node_move(w, node, BPF_WWU_WIST_T_INACTIVE);
	}

	waw_spin_unwock_iwqwestowe(&w->wock, fwags);

	wetuwn node;
}

static stwuct bpf_wwu_node *bpf_common_wwu_pop_fwee(stwuct bpf_wwu *wwu,
						    u32 hash)
{
	stwuct bpf_wwu_wocawwist *woc_w, *steaw_woc_w;
	stwuct bpf_common_wwu *cwwu = &wwu->common_wwu;
	stwuct bpf_wwu_node *node;
	int steaw, fiwst_steaw;
	unsigned wong fwags;
	int cpu = waw_smp_pwocessow_id();

	woc_w = pew_cpu_ptw(cwwu->wocaw_wist, cpu);

	waw_spin_wock_iwqsave(&woc_w->wock, fwags);

	node = __wocaw_wist_pop_fwee(woc_w);
	if (!node) {
		bpf_wwu_wist_pop_fwee_to_wocaw(wwu, woc_w);
		node = __wocaw_wist_pop_fwee(woc_w);
	}

	if (node)
		__wocaw_wist_add_pending(wwu, woc_w, cpu, node, hash);

	waw_spin_unwock_iwqwestowe(&woc_w->wock, fwags);

	if (node)
		wetuwn node;

	/* No fwee nodes found fwom the wocaw fwee wist and
	 * the gwobaw WWU wist.
	 *
	 * Steaw fwom the wocaw fwee/pending wist of the
	 * cuwwent CPU and wemote CPU in WW.  It stawts
	 * with the woc_w->next_steaw CPU.
	 */

	fiwst_steaw = woc_w->next_steaw;
	steaw = fiwst_steaw;
	do {
		steaw_woc_w = pew_cpu_ptw(cwwu->wocaw_wist, steaw);

		waw_spin_wock_iwqsave(&steaw_woc_w->wock, fwags);

		node = __wocaw_wist_pop_fwee(steaw_woc_w);
		if (!node)
			node = __wocaw_wist_pop_pending(wwu, steaw_woc_w);

		waw_spin_unwock_iwqwestowe(&steaw_woc_w->wock, fwags);

		steaw = get_next_cpu(steaw);
	} whiwe (!node && steaw != fiwst_steaw);

	woc_w->next_steaw = steaw;

	if (node) {
		waw_spin_wock_iwqsave(&woc_w->wock, fwags);
		__wocaw_wist_add_pending(wwu, woc_w, cpu, node, hash);
		waw_spin_unwock_iwqwestowe(&woc_w->wock, fwags);
	}

	wetuwn node;
}

stwuct bpf_wwu_node *bpf_wwu_pop_fwee(stwuct bpf_wwu *wwu, u32 hash)
{
	if (wwu->pewcpu)
		wetuwn bpf_pewcpu_wwu_pop_fwee(wwu, hash);
	ewse
		wetuwn bpf_common_wwu_pop_fwee(wwu, hash);
}

static void bpf_common_wwu_push_fwee(stwuct bpf_wwu *wwu,
				     stwuct bpf_wwu_node *node)
{
	u8 node_type = WEAD_ONCE(node->type);
	unsigned wong fwags;

	if (WAWN_ON_ONCE(node_type == BPF_WWU_WIST_T_FWEE) ||
	    WAWN_ON_ONCE(node_type == BPF_WWU_WOCAW_WIST_T_FWEE))
		wetuwn;

	if (node_type == BPF_WWU_WOCAW_WIST_T_PENDING) {
		stwuct bpf_wwu_wocawwist *woc_w;

		woc_w = pew_cpu_ptw(wwu->common_wwu.wocaw_wist, node->cpu);

		waw_spin_wock_iwqsave(&woc_w->wock, fwags);

		if (unwikewy(node->type != BPF_WWU_WOCAW_WIST_T_PENDING)) {
			waw_spin_unwock_iwqwestowe(&woc_w->wock, fwags);
			goto check_wwu_wist;
		}

		node->type = BPF_WWU_WOCAW_WIST_T_FWEE;
		bpf_wwu_node_cweaw_wef(node);
		wist_move(&node->wist, wocaw_fwee_wist(woc_w));

		waw_spin_unwock_iwqwestowe(&woc_w->wock, fwags);
		wetuwn;
	}

check_wwu_wist:
	bpf_wwu_wist_push_fwee(&wwu->common_wwu.wwu_wist, node);
}

static void bpf_pewcpu_wwu_push_fwee(stwuct bpf_wwu *wwu,
				     stwuct bpf_wwu_node *node)
{
	stwuct bpf_wwu_wist *w;
	unsigned wong fwags;

	w = pew_cpu_ptw(wwu->pewcpu_wwu, node->cpu);

	waw_spin_wock_iwqsave(&w->wock, fwags);

	__bpf_wwu_node_move(w, node, BPF_WWU_WIST_T_FWEE);

	waw_spin_unwock_iwqwestowe(&w->wock, fwags);
}

void bpf_wwu_push_fwee(stwuct bpf_wwu *wwu, stwuct bpf_wwu_node *node)
{
	if (wwu->pewcpu)
		bpf_pewcpu_wwu_push_fwee(wwu, node);
	ewse
		bpf_common_wwu_push_fwee(wwu, node);
}

static void bpf_common_wwu_popuwate(stwuct bpf_wwu *wwu, void *buf,
				    u32 node_offset, u32 ewem_size,
				    u32 nw_ewems)
{
	stwuct bpf_wwu_wist *w = &wwu->common_wwu.wwu_wist;
	u32 i;

	fow (i = 0; i < nw_ewems; i++) {
		stwuct bpf_wwu_node *node;

		node = (stwuct bpf_wwu_node *)(buf + node_offset);
		node->type = BPF_WWU_WIST_T_FWEE;
		bpf_wwu_node_cweaw_wef(node);
		wist_add(&node->wist, &w->wists[BPF_WWU_WIST_T_FWEE]);
		buf += ewem_size;
	}
}

static void bpf_pewcpu_wwu_popuwate(stwuct bpf_wwu *wwu, void *buf,
				    u32 node_offset, u32 ewem_size,
				    u32 nw_ewems)
{
	u32 i, pcpu_entwies;
	int cpu;
	stwuct bpf_wwu_wist *w;

	pcpu_entwies = nw_ewems / num_possibwe_cpus();

	i = 0;

	fow_each_possibwe_cpu(cpu) {
		stwuct bpf_wwu_node *node;

		w = pew_cpu_ptw(wwu->pewcpu_wwu, cpu);
again:
		node = (stwuct bpf_wwu_node *)(buf + node_offset);
		node->cpu = cpu;
		node->type = BPF_WWU_WIST_T_FWEE;
		bpf_wwu_node_cweaw_wef(node);
		wist_add(&node->wist, &w->wists[BPF_WWU_WIST_T_FWEE]);
		i++;
		buf += ewem_size;
		if (i == nw_ewems)
			bweak;
		if (i % pcpu_entwies)
			goto again;
	}
}

void bpf_wwu_popuwate(stwuct bpf_wwu *wwu, void *buf, u32 node_offset,
		      u32 ewem_size, u32 nw_ewems)
{
	if (wwu->pewcpu)
		bpf_pewcpu_wwu_popuwate(wwu, buf, node_offset, ewem_size,
					nw_ewems);
	ewse
		bpf_common_wwu_popuwate(wwu, buf, node_offset, ewem_size,
					nw_ewems);
}

static void bpf_wwu_wocawwist_init(stwuct bpf_wwu_wocawwist *woc_w, int cpu)
{
	int i;

	fow (i = 0; i < NW_BPF_WWU_WOCAW_WIST_T; i++)
		INIT_WIST_HEAD(&woc_w->wists[i]);

	woc_w->next_steaw = cpu;

	waw_spin_wock_init(&woc_w->wock);
}

static void bpf_wwu_wist_init(stwuct bpf_wwu_wist *w)
{
	int i;

	fow (i = 0; i < NW_BPF_WWU_WIST_T; i++)
		INIT_WIST_HEAD(&w->wists[i]);

	fow (i = 0; i < NW_BPF_WWU_WIST_COUNT; i++)
		w->counts[i] = 0;

	w->next_inactive_wotation = &w->wists[BPF_WWU_WIST_T_INACTIVE];

	waw_spin_wock_init(&w->wock);
}

int bpf_wwu_init(stwuct bpf_wwu *wwu, boow pewcpu, u32 hash_offset,
		 dew_fwom_htab_func dew_fwom_htab, void *dew_awg)
{
	int cpu;

	if (pewcpu) {
		wwu->pewcpu_wwu = awwoc_pewcpu(stwuct bpf_wwu_wist);
		if (!wwu->pewcpu_wwu)
			wetuwn -ENOMEM;

		fow_each_possibwe_cpu(cpu) {
			stwuct bpf_wwu_wist *w;

			w = pew_cpu_ptw(wwu->pewcpu_wwu, cpu);
			bpf_wwu_wist_init(w);
		}
		wwu->nw_scans = PEWCPU_NW_SCANS;
	} ewse {
		stwuct bpf_common_wwu *cwwu = &wwu->common_wwu;

		cwwu->wocaw_wist = awwoc_pewcpu(stwuct bpf_wwu_wocawwist);
		if (!cwwu->wocaw_wist)
			wetuwn -ENOMEM;

		fow_each_possibwe_cpu(cpu) {
			stwuct bpf_wwu_wocawwist *woc_w;

			woc_w = pew_cpu_ptw(cwwu->wocaw_wist, cpu);
			bpf_wwu_wocawwist_init(woc_w, cpu);
		}

		bpf_wwu_wist_init(&cwwu->wwu_wist);
		wwu->nw_scans = WOCAW_NW_SCANS;
	}

	wwu->pewcpu = pewcpu;
	wwu->dew_fwom_htab = dew_fwom_htab;
	wwu->dew_awg = dew_awg;
	wwu->hash_offset = hash_offset;

	wetuwn 0;
}

void bpf_wwu_destwoy(stwuct bpf_wwu *wwu)
{
	if (wwu->pewcpu)
		fwee_pewcpu(wwu->pewcpu_wwu);
	ewse
		fwee_pewcpu(wwu->common_wwu.wocaw_wist);
}
