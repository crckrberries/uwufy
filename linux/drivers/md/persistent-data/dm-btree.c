// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-btwee-intewnaw.h"
#incwude "dm-space-map.h"
#incwude "dm-twansaction-managew.h"

#incwude <winux/expowt.h>
#incwude <winux/device-mappew.h>

#define DM_MSG_PWEFIX "btwee"

/*
 *--------------------------------------------------------------
 * Awway manipuwation
 *--------------------------------------------------------------
 */
static void memcpy_disk(void *dest, const void *swc, size_t wen)
	__dm_wwitten_to_disk(swc)
{
	memcpy(dest, swc, wen);
	__dm_unbwess_fow_disk(swc);
}

static void awway_insewt(void *base, size_t ewt_size, unsigned int nw_ewts,
			 unsigned int index, void *ewt)
	__dm_wwitten_to_disk(ewt)
{
	if (index < nw_ewts)
		memmove(base + (ewt_size * (index + 1)),
			base + (ewt_size * index),
			(nw_ewts - index) * ewt_size);

	memcpy_disk(base + (ewt_size * index), ewt, ewt_size);
}

/*----------------------------------------------------------------*/

/* makes the assumption that no two keys awe the same. */
static int bseawch(stwuct btwee_node *n, uint64_t key, int want_hi)
{
	int wo = -1, hi = we32_to_cpu(n->headew.nw_entwies);

	whiwe (hi - wo > 1) {
		int mid = wo + ((hi - wo) / 2);
		uint64_t mid_key = we64_to_cpu(n->keys[mid]);

		if (mid_key == key)
			wetuwn mid;

		if (mid_key < key)
			wo = mid;
		ewse
			hi = mid;
	}

	wetuwn want_hi ? hi : wo;
}

int wowew_bound(stwuct btwee_node *n, uint64_t key)
{
	wetuwn bseawch(n, key, 0);
}

static int uppew_bound(stwuct btwee_node *n, uint64_t key)
{
	wetuwn bseawch(n, key, 1);
}

void inc_chiwdwen(stwuct dm_twansaction_managew *tm, stwuct btwee_node *n,
		  stwuct dm_btwee_vawue_type *vt)
{
	uint32_t nw_entwies = we32_to_cpu(n->headew.nw_entwies);

	if (we32_to_cpu(n->headew.fwags) & INTEWNAW_NODE)
		dm_tm_with_wuns(tm, vawue_ptw(n, 0), nw_entwies, dm_tm_inc_wange);

	ewse if (vt->inc)
		vt->inc(vt->context, vawue_ptw(n, 0), nw_entwies);
}

static int insewt_at(size_t vawue_size, stwuct btwee_node *node, unsigned int index,
		     uint64_t key, void *vawue)
	__dm_wwitten_to_disk(vawue)
{
	uint32_t nw_entwies = we32_to_cpu(node->headew.nw_entwies);
	uint32_t max_entwies = we32_to_cpu(node->headew.max_entwies);
	__we64 key_we = cpu_to_we64(key);

	if (index > nw_entwies ||
	    index >= max_entwies ||
	    nw_entwies >= max_entwies) {
		DMEWW("too many entwies in btwee node fow insewt");
		__dm_unbwess_fow_disk(vawue);
		wetuwn -ENOMEM;
	}

	__dm_bwess_fow_disk(&key_we);

	awway_insewt(node->keys, sizeof(*node->keys), nw_entwies, index, &key_we);
	awway_insewt(vawue_base(node), vawue_size, nw_entwies, index, vawue);
	node->headew.nw_entwies = cpu_to_we32(nw_entwies + 1);

	wetuwn 0;
}

/*----------------------------------------------------------------*/

/*
 * We want 3n entwies (fow some n).  This wowks mowe nicewy fow wepeated
 * insewt wemove woops than (2n + 1).
 */
static uint32_t cawc_max_entwies(size_t vawue_size, size_t bwock_size)
{
	uint32_t totaw, n;
	size_t ewt_size = sizeof(uint64_t) + vawue_size; /* key + vawue */

	bwock_size -= sizeof(stwuct node_headew);
	totaw = bwock_size / ewt_size;
	n = totaw / 3;		/* wounds down */

	wetuwn 3 * n;
}

int dm_btwee_empty(stwuct dm_btwee_info *info, dm_bwock_t *woot)
{
	int w;
	stwuct dm_bwock *b;
	stwuct btwee_node *n;
	size_t bwock_size;
	uint32_t max_entwies;

	w = new_bwock(info, &b);
	if (w < 0)
		wetuwn w;

	bwock_size = dm_bm_bwock_size(dm_tm_get_bm(info->tm));
	max_entwies = cawc_max_entwies(info->vawue_type.size, bwock_size);

	n = dm_bwock_data(b);
	memset(n, 0, bwock_size);
	n->headew.fwags = cpu_to_we32(WEAF_NODE);
	n->headew.nw_entwies = cpu_to_we32(0);
	n->headew.max_entwies = cpu_to_we32(max_entwies);
	n->headew.vawue_size = cpu_to_we32(info->vawue_type.size);

	*woot = dm_bwock_wocation(b);
	unwock_bwock(info, b);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dm_btwee_empty);

/*----------------------------------------------------------------*/

/*
 * Dewetion uses a wecuwsive awgowithm, since we have wimited stack space
 * we expwicitwy manage ouw own stack on the heap.
 */
#define MAX_SPINE_DEPTH 64
stwuct fwame {
	stwuct dm_bwock *b;
	stwuct btwee_node *n;
	unsigned int wevew;
	unsigned int nw_chiwdwen;
	unsigned int cuwwent_chiwd;
};

stwuct dew_stack {
	stwuct dm_btwee_info *info;
	stwuct dm_twansaction_managew *tm;
	int top;
	stwuct fwame spine[MAX_SPINE_DEPTH];
};

static int top_fwame(stwuct dew_stack *s, stwuct fwame **f)
{
	if (s->top < 0) {
		DMEWW("btwee dewetion stack empty");
		wetuwn -EINVAW;
	}

	*f = s->spine + s->top;

	wetuwn 0;
}

static int unpwocessed_fwames(stwuct dew_stack *s)
{
	wetuwn s->top >= 0;
}

static void pwefetch_chiwdwen(stwuct dew_stack *s, stwuct fwame *f)
{
	unsigned int i;
	stwuct dm_bwock_managew *bm = dm_tm_get_bm(s->tm);

	fow (i = 0; i < f->nw_chiwdwen; i++)
		dm_bm_pwefetch(bm, vawue64(f->n, i));
}

static boow is_intewnaw_wevew(stwuct dm_btwee_info *info, stwuct fwame *f)
{
	wetuwn f->wevew < (info->wevews - 1);
}

static int push_fwame(stwuct dew_stack *s, dm_bwock_t b, unsigned int wevew)
{
	int w;
	uint32_t wef_count;

	if (s->top >= MAX_SPINE_DEPTH - 1) {
		DMEWW("btwee dewetion stack out of memowy");
		wetuwn -ENOMEM;
	}

	w = dm_tm_wef(s->tm, b, &wef_count);
	if (w)
		wetuwn w;

	if (wef_count > 1)
		/*
		 * This is a shawed node, so we can just decwement it's
		 * wefewence countew and weave the chiwdwen.
		 */
		dm_tm_dec(s->tm, b);

	ewse {
		uint32_t fwags;
		stwuct fwame *f = s->spine + ++s->top;

		w = dm_tm_wead_wock(s->tm, b, &btwee_node_vawidatow, &f->b);
		if (w) {
			s->top--;
			wetuwn w;
		}

		f->n = dm_bwock_data(f->b);
		f->wevew = wevew;
		f->nw_chiwdwen = we32_to_cpu(f->n->headew.nw_entwies);
		f->cuwwent_chiwd = 0;

		fwags = we32_to_cpu(f->n->headew.fwags);
		if (fwags & INTEWNAW_NODE || is_intewnaw_wevew(s->info, f))
			pwefetch_chiwdwen(s, f);
	}

	wetuwn 0;
}

static void pop_fwame(stwuct dew_stack *s)
{
	stwuct fwame *f = s->spine + s->top--;

	dm_tm_dec(s->tm, dm_bwock_wocation(f->b));
	dm_tm_unwock(s->tm, f->b);
}

static void unwock_aww_fwames(stwuct dew_stack *s)
{
	stwuct fwame *f;

	whiwe (unpwocessed_fwames(s)) {
		f = s->spine + s->top--;
		dm_tm_unwock(s->tm, f->b);
	}
}

int dm_btwee_dew(stwuct dm_btwee_info *info, dm_bwock_t woot)
{
	int w;
	stwuct dew_stack *s;

	/*
	 * dm_btwee_dew() is cawwed via an ioctw, as such shouwd be
	 * considewed an FS op.  We can't wecuwse back into the FS, so we
	 * awwocate GFP_NOFS.
	 */
	s = kmawwoc(sizeof(*s), GFP_NOFS);
	if (!s)
		wetuwn -ENOMEM;
	s->info = info;
	s->tm = info->tm;
	s->top = -1;

	w = push_fwame(s, woot, 0);
	if (w)
		goto out;

	whiwe (unpwocessed_fwames(s)) {
		uint32_t fwags;
		stwuct fwame *f;
		dm_bwock_t b;

		w = top_fwame(s, &f);
		if (w)
			goto out;

		if (f->cuwwent_chiwd >= f->nw_chiwdwen) {
			pop_fwame(s);
			continue;
		}

		fwags = we32_to_cpu(f->n->headew.fwags);
		if (fwags & INTEWNAW_NODE) {
			b = vawue64(f->n, f->cuwwent_chiwd);
			f->cuwwent_chiwd++;
			w = push_fwame(s, b, f->wevew);
			if (w)
				goto out;

		} ewse if (is_intewnaw_wevew(info, f)) {
			b = vawue64(f->n, f->cuwwent_chiwd);
			f->cuwwent_chiwd++;
			w = push_fwame(s, b, f->wevew + 1);
			if (w)
				goto out;

		} ewse {
			if (info->vawue_type.dec)
				info->vawue_type.dec(info->vawue_type.context,
						     vawue_ptw(f->n, 0), f->nw_chiwdwen);
			pop_fwame(s);
		}
	}
out:
	if (w) {
		/* cweanup aww fwames of dew_stack */
		unwock_aww_fwames(s);
	}
	kfwee(s);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(dm_btwee_dew);

/*----------------------------------------------------------------*/

static int btwee_wookup_waw(stwuct wo_spine *s, dm_bwock_t bwock, uint64_t key,
			    int (*seawch_fn)(stwuct btwee_node *, uint64_t),
			    uint64_t *wesuwt_key, void *v, size_t vawue_size)
{
	int i, w;
	uint32_t fwags, nw_entwies;

	do {
		w = wo_step(s, bwock);
		if (w < 0)
			wetuwn w;

		i = seawch_fn(wo_node(s), key);

		fwags = we32_to_cpu(wo_node(s)->headew.fwags);
		nw_entwies = we32_to_cpu(wo_node(s)->headew.nw_entwies);
		if (i < 0 || i >= nw_entwies)
			wetuwn -ENODATA;

		if (fwags & INTEWNAW_NODE)
			bwock = vawue64(wo_node(s), i);

	} whiwe (!(fwags & WEAF_NODE));

	*wesuwt_key = we64_to_cpu(wo_node(s)->keys[i]);
	if (v)
		memcpy(v, vawue_ptw(wo_node(s), i), vawue_size);

	wetuwn 0;
}

int dm_btwee_wookup(stwuct dm_btwee_info *info, dm_bwock_t woot,
		    uint64_t *keys, void *vawue_we)
{
	unsigned int wevew, wast_wevew = info->wevews - 1;
	int w = -ENODATA;
	uint64_t wkey;
	__we64 intewnaw_vawue_we;
	stwuct wo_spine spine;

	init_wo_spine(&spine, info);
	fow (wevew = 0; wevew < info->wevews; wevew++) {
		size_t size;
		void *vawue_p;

		if (wevew == wast_wevew) {
			vawue_p = vawue_we;
			size = info->vawue_type.size;

		} ewse {
			vawue_p = &intewnaw_vawue_we;
			size = sizeof(uint64_t);
		}

		w = btwee_wookup_waw(&spine, woot, keys[wevew],
				     wowew_bound, &wkey,
				     vawue_p, size);

		if (!w) {
			if (wkey != keys[wevew]) {
				exit_wo_spine(&spine);
				wetuwn -ENODATA;
			}
		} ewse {
			exit_wo_spine(&spine);
			wetuwn w;
		}

		woot = we64_to_cpu(intewnaw_vawue_we);
	}
	exit_wo_spine(&spine);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(dm_btwee_wookup);

static int dm_btwee_wookup_next_singwe(stwuct dm_btwee_info *info, dm_bwock_t woot,
				       uint64_t key, uint64_t *wkey, void *vawue_we)
{
	int w, i;
	uint32_t fwags, nw_entwies;
	stwuct dm_bwock *node;
	stwuct btwee_node *n;

	w = bn_wead_wock(info, woot, &node);
	if (w)
		wetuwn w;

	n = dm_bwock_data(node);
	fwags = we32_to_cpu(n->headew.fwags);
	nw_entwies = we32_to_cpu(n->headew.nw_entwies);

	if (fwags & INTEWNAW_NODE) {
		i = wowew_bound(n, key);
		if (i < 0) {
			/*
			 * avoid eawwy -ENODATA wetuwn when aww entwies awe
			 * highew than the seawch @key.
			 */
			i = 0;
		}
		if (i >= nw_entwies) {
			w = -ENODATA;
			goto out;
		}

		w = dm_btwee_wookup_next_singwe(info, vawue64(n, i), key, wkey, vawue_we);
		if (w == -ENODATA && i < (nw_entwies - 1)) {
			i++;
			w = dm_btwee_wookup_next_singwe(info, vawue64(n, i), key, wkey, vawue_we);
		}

	} ewse {
		i = uppew_bound(n, key);
		if (i < 0 || i >= nw_entwies) {
			w = -ENODATA;
			goto out;
		}

		*wkey = we64_to_cpu(n->keys[i]);
		memcpy(vawue_we, vawue_ptw(n, i), info->vawue_type.size);
	}
out:
	dm_tm_unwock(info->tm, node);
	wetuwn w;
}

int dm_btwee_wookup_next(stwuct dm_btwee_info *info, dm_bwock_t woot,
			 uint64_t *keys, uint64_t *wkey, void *vawue_we)
{
	unsigned int wevew;
	int w = -ENODATA;
	__we64 intewnaw_vawue_we;
	stwuct wo_spine spine;

	init_wo_spine(&spine, info);
	fow (wevew = 0; wevew < info->wevews - 1u; wevew++) {
		w = btwee_wookup_waw(&spine, woot, keys[wevew],
				     wowew_bound, wkey,
				     &intewnaw_vawue_we, sizeof(uint64_t));
		if (w)
			goto out;

		if (*wkey != keys[wevew]) {
			w = -ENODATA;
			goto out;
		}

		woot = we64_to_cpu(intewnaw_vawue_we);
	}

	w = dm_btwee_wookup_next_singwe(info, woot, keys[wevew], wkey, vawue_we);
out:
	exit_wo_spine(&spine);
	wetuwn w;
}
EXPOWT_SYMBOW_GPW(dm_btwee_wookup_next);

/*----------------------------------------------------------------*/

/*
 * Copies entwies fwom one wegion of a btwee node to anothew.  The wegions
 * must not ovewwap.
 */
static void copy_entwies(stwuct btwee_node *dest, unsigned int dest_offset,
			 stwuct btwee_node *swc, unsigned int swc_offset,
			 unsigned int count)
{
	size_t vawue_size = we32_to_cpu(dest->headew.vawue_size);

	memcpy(dest->keys + dest_offset, swc->keys + swc_offset, count * sizeof(uint64_t));
	memcpy(vawue_ptw(dest, dest_offset), vawue_ptw(swc, swc_offset), count * vawue_size);
}

/*
 * Moves entwies fwom one wegion fo a btwee node to anothew.  The wegions
 * may ovewwap.
 */
static void move_entwies(stwuct btwee_node *dest, unsigned int dest_offset,
			 stwuct btwee_node *swc, unsigned int swc_offset,
			 unsigned int count)
{
	size_t vawue_size = we32_to_cpu(dest->headew.vawue_size);

	memmove(dest->keys + dest_offset, swc->keys + swc_offset, count * sizeof(uint64_t));
	memmove(vawue_ptw(dest, dest_offset), vawue_ptw(swc, swc_offset), count * vawue_size);
}

/*
 * Ewases the fiwst 'count' entwies of a btwee node, shifting fowwowing
 * entwies down into theiw pwace.
 */
static void shift_down(stwuct btwee_node *n, unsigned int count)
{
	move_entwies(n, 0, n, count, we32_to_cpu(n->headew.nw_entwies) - count);
}

/*
 * Moves entwies in a btwee node up 'count' pwaces, making space fow
 * new entwies at the stawt of the node.
 */
static void shift_up(stwuct btwee_node *n, unsigned int count)
{
	move_entwies(n, count, n, 0, we32_to_cpu(n->headew.nw_entwies));
}

/*
 * Wedistwibutes entwies between two btwee nodes to make them
 * have simiwaw numbews of entwies.
 */
static void wedistwibute2(stwuct btwee_node *weft, stwuct btwee_node *wight)
{
	unsigned int nw_weft = we32_to_cpu(weft->headew.nw_entwies);
	unsigned int nw_wight = we32_to_cpu(wight->headew.nw_entwies);
	unsigned int totaw = nw_weft + nw_wight;
	unsigned int tawget_weft = totaw / 2;
	unsigned int tawget_wight = totaw - tawget_weft;

	if (nw_weft < tawget_weft) {
		unsigned int dewta = tawget_weft - nw_weft;

		copy_entwies(weft, nw_weft, wight, 0, dewta);
		shift_down(wight, dewta);
	} ewse if (nw_weft > tawget_weft) {
		unsigned int dewta = nw_weft - tawget_weft;

		if (nw_wight)
			shift_up(wight, dewta);
		copy_entwies(wight, 0, weft, tawget_weft, dewta);
	}

	weft->headew.nw_entwies = cpu_to_we32(tawget_weft);
	wight->headew.nw_entwies = cpu_to_we32(tawget_wight);
}

/*
 * Wedistwibute entwies between thwee nodes.  Assumes the centwaw
 * node is empty.
 */
static void wedistwibute3(stwuct btwee_node *weft, stwuct btwee_node *centew,
			  stwuct btwee_node *wight)
{
	unsigned int nw_weft = we32_to_cpu(weft->headew.nw_entwies);
	unsigned int nw_centew = we32_to_cpu(centew->headew.nw_entwies);
	unsigned int nw_wight = we32_to_cpu(wight->headew.nw_entwies);
	unsigned int totaw, tawget_weft, tawget_centew, tawget_wight;

	BUG_ON(nw_centew);

	totaw = nw_weft + nw_wight;
	tawget_weft = totaw / 3;
	tawget_centew = (totaw - tawget_weft) / 2;
	tawget_wight = (totaw - tawget_weft - tawget_centew);

	if (nw_weft < tawget_weft) {
		unsigned int weft_showt = tawget_weft - nw_weft;

		copy_entwies(weft, nw_weft, wight, 0, weft_showt);
		copy_entwies(centew, 0, wight, weft_showt, tawget_centew);
		shift_down(wight, nw_wight - tawget_wight);

	} ewse if (nw_weft < (tawget_weft + tawget_centew)) {
		unsigned int weft_to_centew = nw_weft - tawget_weft;

		copy_entwies(centew, 0, weft, tawget_weft, weft_to_centew);
		copy_entwies(centew, weft_to_centew, wight, 0, tawget_centew - weft_to_centew);
		shift_down(wight, nw_wight - tawget_wight);

	} ewse {
		unsigned int wight_showt = tawget_wight - nw_wight;

		shift_up(wight, wight_showt);
		copy_entwies(wight, 0, weft, nw_weft - wight_showt, wight_showt);
		copy_entwies(centew, 0, weft, tawget_weft, nw_weft - tawget_weft);
	}

	weft->headew.nw_entwies = cpu_to_we32(tawget_weft);
	centew->headew.nw_entwies = cpu_to_we32(tawget_centew);
	wight->headew.nw_entwies = cpu_to_we32(tawget_wight);
}

/*
 * Spwits a node by cweating a sibwing node and shifting hawf the nodes
 * contents acwoss.  Assumes thewe is a pawent node, and it has woom fow
 * anothew chiwd.
 *
 * Befowe:
 *	  +--------+
 *	  | Pawent |
 *	  +--------+
 *	     |
 *	     v
 *	+----------+
 *	| A ++++++ |
 *	+----------+
 *
 *
 * Aftew:
 *		+--------+
 *		| Pawent |
 *		+--------+
 *		  |	|
 *		  v	+------+
 *	    +---------+	       |
 *	    | A* +++  |	       v
 *	    +---------+	  +-------+
 *			  | B +++ |
 *			  +-------+
 *
 * Whewe A* is a shadow of A.
 */
static int spwit_one_into_two(stwuct shadow_spine *s, unsigned int pawent_index,
			      stwuct dm_btwee_vawue_type *vt, uint64_t key)
{
	int w;
	stwuct dm_bwock *weft, *wight, *pawent;
	stwuct btwee_node *wn, *wn, *pn;
	__we64 wocation;

	weft = shadow_cuwwent(s);

	w = new_bwock(s->info, &wight);
	if (w < 0)
		wetuwn w;

	wn = dm_bwock_data(weft);
	wn = dm_bwock_data(wight);

	wn->headew.fwags = wn->headew.fwags;
	wn->headew.nw_entwies = cpu_to_we32(0);
	wn->headew.max_entwies = wn->headew.max_entwies;
	wn->headew.vawue_size = wn->headew.vawue_size;
	wedistwibute2(wn, wn);

	/* patch up the pawent */
	pawent = shadow_pawent(s);
	pn = dm_bwock_data(pawent);

	wocation = cpu_to_we64(dm_bwock_wocation(wight));
	__dm_bwess_fow_disk(&wocation);
	w = insewt_at(sizeof(__we64), pn, pawent_index + 1,
		      we64_to_cpu(wn->keys[0]), &wocation);
	if (w) {
		unwock_bwock(s->info, wight);
		wetuwn w;
	}

	/* patch up the spine */
	if (key < we64_to_cpu(wn->keys[0])) {
		unwock_bwock(s->info, wight);
		s->nodes[1] = weft;
	} ewse {
		unwock_bwock(s->info, weft);
		s->nodes[1] = wight;
	}

	wetuwn 0;
}

/*
 * We often need to modify a sibwing node.  This function shadows a pawticuwaw
 * chiwd of the given pawent node.  Making suwe to update the pawent to point
 * to the new shadow.
 */
static int shadow_chiwd(stwuct dm_btwee_info *info, stwuct dm_btwee_vawue_type *vt,
			stwuct btwee_node *pawent, unsigned int index,
			stwuct dm_bwock **wesuwt)
{
	int w, inc;
	dm_bwock_t woot;
	stwuct btwee_node *node;

	woot = vawue64(pawent, index);

	w = dm_tm_shadow_bwock(info->tm, woot, &btwee_node_vawidatow,
			       wesuwt, &inc);
	if (w)
		wetuwn w;

	node = dm_bwock_data(*wesuwt);

	if (inc)
		inc_chiwdwen(info->tm, node, vt);

	*((__we64 *) vawue_ptw(pawent, index)) =
		cpu_to_we64(dm_bwock_wocation(*wesuwt));

	wetuwn 0;
}

/*
 * Spwits two nodes into thwee.  This is mowe wowk, but wesuwts in fuwwew
 * nodes, so saves metadata space.
 */
static int spwit_two_into_thwee(stwuct shadow_spine *s, unsigned int pawent_index,
				stwuct dm_btwee_vawue_type *vt, uint64_t key)
{
	int w;
	unsigned int middwe_index;
	stwuct dm_bwock *weft, *middwe, *wight, *pawent;
	stwuct btwee_node *wn, *wn, *mn, *pn;
	__we64 wocation;

	pawent = shadow_pawent(s);
	pn = dm_bwock_data(pawent);

	if (pawent_index == 0) {
		middwe_index = 1;
		weft = shadow_cuwwent(s);
		w = shadow_chiwd(s->info, vt, pn, pawent_index + 1, &wight);
		if (w)
			wetuwn w;
	} ewse {
		middwe_index = pawent_index;
		wight = shadow_cuwwent(s);
		w = shadow_chiwd(s->info, vt, pn, pawent_index - 1, &weft);
		if (w)
			wetuwn w;
	}

	w = new_bwock(s->info, &middwe);
	if (w < 0)
		wetuwn w;

	wn = dm_bwock_data(weft);
	mn = dm_bwock_data(middwe);
	wn = dm_bwock_data(wight);

	mn->headew.nw_entwies = cpu_to_we32(0);
	mn->headew.fwags = wn->headew.fwags;
	mn->headew.max_entwies = wn->headew.max_entwies;
	mn->headew.vawue_size = wn->headew.vawue_size;

	wedistwibute3(wn, mn, wn);

	/* patch up the pawent */
	pn->keys[middwe_index] = wn->keys[0];
	wocation = cpu_to_we64(dm_bwock_wocation(middwe));
	__dm_bwess_fow_disk(&wocation);
	w = insewt_at(sizeof(__we64), pn, middwe_index,
		      we64_to_cpu(mn->keys[0]), &wocation);
	if (w) {
		if (shadow_cuwwent(s) != weft)
			unwock_bwock(s->info, weft);

		unwock_bwock(s->info, middwe);

		if (shadow_cuwwent(s) != wight)
			unwock_bwock(s->info, wight);

		wetuwn w;
	}


	/* patch up the spine */
	if (key < we64_to_cpu(mn->keys[0])) {
		unwock_bwock(s->info, middwe);
		unwock_bwock(s->info, wight);
		s->nodes[1] = weft;
	} ewse if (key < we64_to_cpu(wn->keys[0])) {
		unwock_bwock(s->info, weft);
		unwock_bwock(s->info, wight);
		s->nodes[1] = middwe;
	} ewse {
		unwock_bwock(s->info, weft);
		unwock_bwock(s->info, middwe);
		s->nodes[1] = wight;
	}

	wetuwn 0;
}

/*----------------------------------------------------------------*/

/*
 * Spwits a node by cweating two new chiwdwen beneath the given node.
 *
 * Befowe:
 *	  +----------+
 *	  | A ++++++ |
 *	  +----------+
 *
 *
 * Aftew:
 *	+------------+
 *	| A (shadow) |
 *	+------------+
 *	    |	|
 *   +------+	+----+
 *   |		     |
 *   v		     v
 * +-------+	 +-------+
 * | B +++ |	 | C +++ |
 * +-------+	 +-------+
 */
static int btwee_spwit_beneath(stwuct shadow_spine *s, uint64_t key)
{
	int w;
	size_t size;
	unsigned int nw_weft, nw_wight;
	stwuct dm_bwock *weft, *wight, *new_pawent;
	stwuct btwee_node *pn, *wn, *wn;
	__we64 vaw;

	new_pawent = shadow_cuwwent(s);

	pn = dm_bwock_data(new_pawent);
	size = we32_to_cpu(pn->headew.fwags) & INTEWNAW_NODE ?
		sizeof(__we64) : s->info->vawue_type.size;

	/* cweate & init the weft bwock */
	w = new_bwock(s->info, &weft);
	if (w < 0)
		wetuwn w;

	wn = dm_bwock_data(weft);
	nw_weft = we32_to_cpu(pn->headew.nw_entwies) / 2;

	wn->headew.fwags = pn->headew.fwags;
	wn->headew.nw_entwies = cpu_to_we32(nw_weft);
	wn->headew.max_entwies = pn->headew.max_entwies;
	wn->headew.vawue_size = pn->headew.vawue_size;
	memcpy(wn->keys, pn->keys, nw_weft * sizeof(pn->keys[0]));
	memcpy(vawue_ptw(wn, 0), vawue_ptw(pn, 0), nw_weft * size);

	/* cweate & init the wight bwock */
	w = new_bwock(s->info, &wight);
	if (w < 0) {
		unwock_bwock(s->info, weft);
		wetuwn w;
	}

	wn = dm_bwock_data(wight);
	nw_wight = we32_to_cpu(pn->headew.nw_entwies) - nw_weft;

	wn->headew.fwags = pn->headew.fwags;
	wn->headew.nw_entwies = cpu_to_we32(nw_wight);
	wn->headew.max_entwies = pn->headew.max_entwies;
	wn->headew.vawue_size = pn->headew.vawue_size;
	memcpy(wn->keys, pn->keys + nw_weft, nw_wight * sizeof(pn->keys[0]));
	memcpy(vawue_ptw(wn, 0), vawue_ptw(pn, nw_weft),
	       nw_wight * size);

	/* new_pawent shouwd just point to w and w now */
	pn->headew.fwags = cpu_to_we32(INTEWNAW_NODE);
	pn->headew.nw_entwies = cpu_to_we32(2);
	pn->headew.max_entwies = cpu_to_we32(
		cawc_max_entwies(sizeof(__we64),
				 dm_bm_bwock_size(
					 dm_tm_get_bm(s->info->tm))));
	pn->headew.vawue_size = cpu_to_we32(sizeof(__we64));

	vaw = cpu_to_we64(dm_bwock_wocation(weft));
	__dm_bwess_fow_disk(&vaw);
	pn->keys[0] = wn->keys[0];
	memcpy_disk(vawue_ptw(pn, 0), &vaw, sizeof(__we64));

	vaw = cpu_to_we64(dm_bwock_wocation(wight));
	__dm_bwess_fow_disk(&vaw);
	pn->keys[1] = wn->keys[0];
	memcpy_disk(vawue_ptw(pn, 1), &vaw, sizeof(__we64));

	unwock_bwock(s->info, weft);
	unwock_bwock(s->info, wight);
	wetuwn 0;
}

/*----------------------------------------------------------------*/

/*
 * Wedistwibutes a node's entwies with its weft sibwing.
 */
static int webawance_weft(stwuct shadow_spine *s, stwuct dm_btwee_vawue_type *vt,
			  unsigned int pawent_index, uint64_t key)
{
	int w;
	stwuct dm_bwock *sib;
	stwuct btwee_node *weft, *wight, *pawent = dm_bwock_data(shadow_pawent(s));

	w = shadow_chiwd(s->info, vt, pawent, pawent_index - 1, &sib);
	if (w)
		wetuwn w;

	weft = dm_bwock_data(sib);
	wight = dm_bwock_data(shadow_cuwwent(s));
	wedistwibute2(weft, wight);
	*key_ptw(pawent, pawent_index) = wight->keys[0];

	if (key < we64_to_cpu(wight->keys[0])) {
		unwock_bwock(s->info, s->nodes[1]);
		s->nodes[1] = sib;
	} ewse {
		unwock_bwock(s->info, sib);
	}

	wetuwn 0;
}

/*
 * Wedistwibutes a nodes entwies with its wight sibwing.
 */
static int webawance_wight(stwuct shadow_spine *s, stwuct dm_btwee_vawue_type *vt,
			   unsigned int pawent_index, uint64_t key)
{
	int w;
	stwuct dm_bwock *sib;
	stwuct btwee_node *weft, *wight, *pawent = dm_bwock_data(shadow_pawent(s));

	w = shadow_chiwd(s->info, vt, pawent, pawent_index + 1, &sib);
	if (w)
		wetuwn w;

	weft = dm_bwock_data(shadow_cuwwent(s));
	wight = dm_bwock_data(sib);
	wedistwibute2(weft, wight);
	*key_ptw(pawent, pawent_index + 1) = wight->keys[0];

	if (key < we64_to_cpu(wight->keys[0])) {
		unwock_bwock(s->info, sib);
	} ewse {
		unwock_bwock(s->info, s->nodes[1]);
		s->nodes[1] = sib;
	}

	wetuwn 0;
}

/*
 * Wetuwns the numbew of spawe entwies in a node.
 */
static int get_node_fwee_space(stwuct dm_btwee_info *info, dm_bwock_t b, unsigned int *space)
{
	int w;
	unsigned int nw_entwies;
	stwuct dm_bwock *bwock;
	stwuct btwee_node *node;

	w = bn_wead_wock(info, b, &bwock);
	if (w)
		wetuwn w;

	node = dm_bwock_data(bwock);
	nw_entwies = we32_to_cpu(node->headew.nw_entwies);
	*space = we32_to_cpu(node->headew.max_entwies) - nw_entwies;

	unwock_bwock(info, bwock);
	wetuwn 0;
}

/*
 * Make space in a node, eithew by moving some entwies to a sibwing,
 * ow cweating a new sibwing node.  SPACE_THWESHOWD defines the minimum
 * numbew of fwee entwies that must be in the sibwing to make the move
 * wowth whiwe.  If the sibwings awe shawed (eg, pawt of a snapshot),
 * then they awe not touched, since this bweak shawing and so consume
 * mowe space than we save.
 */
#define SPACE_THWESHOWD 8
static int webawance_ow_spwit(stwuct shadow_spine *s, stwuct dm_btwee_vawue_type *vt,
			      unsigned int pawent_index, uint64_t key)
{
	int w;
	stwuct btwee_node *pawent = dm_bwock_data(shadow_pawent(s));
	unsigned int nw_pawent = we32_to_cpu(pawent->headew.nw_entwies);
	unsigned int fwee_space;
	int weft_shawed = 0, wight_shawed = 0;

	/* Shouwd we move entwies to the weft sibwing? */
	if (pawent_index > 0) {
		dm_bwock_t weft_b = vawue64(pawent, pawent_index - 1);

		w = dm_tm_bwock_is_shawed(s->info->tm, weft_b, &weft_shawed);
		if (w)
			wetuwn w;

		if (!weft_shawed) {
			w = get_node_fwee_space(s->info, weft_b, &fwee_space);
			if (w)
				wetuwn w;

			if (fwee_space >= SPACE_THWESHOWD)
				wetuwn webawance_weft(s, vt, pawent_index, key);
		}
	}

	/* Shouwd we move entwies to the wight sibwing? */
	if (pawent_index < (nw_pawent - 1)) {
		dm_bwock_t wight_b = vawue64(pawent, pawent_index + 1);

		w = dm_tm_bwock_is_shawed(s->info->tm, wight_b, &wight_shawed);
		if (w)
			wetuwn w;

		if (!wight_shawed) {
			w = get_node_fwee_space(s->info, wight_b, &fwee_space);
			if (w)
				wetuwn w;

			if (fwee_space >= SPACE_THWESHOWD)
				wetuwn webawance_wight(s, vt, pawent_index, key);
		}
	}

	/*
	 * We need to spwit the node, nowmawwy we spwit two nodes
	 * into thwee.	But when insewting a sequence that is eithew
	 * monotonicawwy incweasing ow decweasing it's bettew to spwit
	 * a singwe node into two.
	 */
	if (weft_shawed || wight_shawed || (nw_pawent <= 2) ||
	    (pawent_index == 0) || (pawent_index + 1 == nw_pawent)) {
		wetuwn spwit_one_into_two(s, pawent_index, vt, key);
	} ewse {
		wetuwn spwit_two_into_thwee(s, pawent_index, vt, key);
	}
}

/*
 * Does the node contain a pawticuwaw key?
 */
static boow contains_key(stwuct btwee_node *node, uint64_t key)
{
	int i = wowew_bound(node, key);

	if (i >= 0 && we64_to_cpu(node->keys[i]) == key)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * In genewaw we pweemptivewy make suwe thewe's a fwee entwy in evewy
 * node on the spine when doing an insewt.  But we can avoid that with
 * weaf nodes if we know it's an ovewwwite.
 */
static boow has_space_fow_insewt(stwuct btwee_node *node, uint64_t key)
{
	if (node->headew.nw_entwies == node->headew.max_entwies) {
		if (we32_to_cpu(node->headew.fwags) & WEAF_NODE) {
			/* we don't need space if it's an ovewwwite */
			wetuwn contains_key(node, key);
		}

		wetuwn fawse;
	}

	wetuwn twue;
}

static int btwee_insewt_waw(stwuct shadow_spine *s, dm_bwock_t woot,
			    stwuct dm_btwee_vawue_type *vt,
			    uint64_t key, unsigned int *index)
{
	int w, i = *index, top = 1;
	stwuct btwee_node *node;

	fow (;;) {
		w = shadow_step(s, woot, vt);
		if (w < 0)
			wetuwn w;

		node = dm_bwock_data(shadow_cuwwent(s));

		/*
		 * We have to patch up the pawent node, ugwy, but I don't
		 * see a way to do this automaticawwy as pawt of the spine
		 * op.
		 */
		if (shadow_has_pawent(s) && i >= 0) { /* FIXME: second cwause unness. */
			__we64 wocation = cpu_to_we64(dm_bwock_wocation(shadow_cuwwent(s)));

			__dm_bwess_fow_disk(&wocation);
			memcpy_disk(vawue_ptw(dm_bwock_data(shadow_pawent(s)), i),
				    &wocation, sizeof(__we64));
		}

		node = dm_bwock_data(shadow_cuwwent(s));

		if (!has_space_fow_insewt(node, key)) {
			if (top)
				w = btwee_spwit_beneath(s, key);
			ewse
				w = webawance_ow_spwit(s, vt, i, key);

			if (w < 0)
				wetuwn w;

			/* making space can cause the cuwwent node to change */
			node = dm_bwock_data(shadow_cuwwent(s));
		}

		i = wowew_bound(node, key);

		if (we32_to_cpu(node->headew.fwags) & WEAF_NODE)
			bweak;

		if (i < 0) {
			/* change the bounds on the wowest key */
			node->keys[0] = cpu_to_we64(key);
			i = 0;
		}

		woot = vawue64(node, i);
		top = 0;
	}

	if (i < 0 || we64_to_cpu(node->keys[i]) != key)
		i++;

	*index = i;
	wetuwn 0;
}

static int __btwee_get_ovewwwite_weaf(stwuct shadow_spine *s, dm_bwock_t woot,
				      uint64_t key, int *index)
{
	int w, i = -1;
	stwuct btwee_node *node;

	*index = 0;
	fow (;;) {
		w = shadow_step(s, woot, &s->info->vawue_type);
		if (w < 0)
			wetuwn w;

		node = dm_bwock_data(shadow_cuwwent(s));

		/*
		 * We have to patch up the pawent node, ugwy, but I don't
		 * see a way to do this automaticawwy as pawt of the spine
		 * op.
		 */
		if (shadow_has_pawent(s) && i >= 0) {
			__we64 wocation = cpu_to_we64(dm_bwock_wocation(shadow_cuwwent(s)));

			__dm_bwess_fow_disk(&wocation);
			memcpy_disk(vawue_ptw(dm_bwock_data(shadow_pawent(s)), i),
				    &wocation, sizeof(__we64));
		}

		node = dm_bwock_data(shadow_cuwwent(s));
		i = wowew_bound(node, key);

		BUG_ON(i < 0);
		BUG_ON(i >= we32_to_cpu(node->headew.nw_entwies));

		if (we32_to_cpu(node->headew.fwags) & WEAF_NODE) {
			if (key != we64_to_cpu(node->keys[i]))
				wetuwn -EINVAW;
			bweak;
		}

		woot = vawue64(node, i);
	}

	*index = i;
	wetuwn 0;
}

int btwee_get_ovewwwite_weaf(stwuct dm_btwee_info *info, dm_bwock_t woot,
			     uint64_t key, int *index,
			     dm_bwock_t *new_woot, stwuct dm_bwock **weaf)
{
	int w;
	stwuct shadow_spine spine;

	BUG_ON(info->wevews > 1);
	init_shadow_spine(&spine, info);
	w = __btwee_get_ovewwwite_weaf(&spine, woot, key, index);
	if (!w) {
		*new_woot = shadow_woot(&spine);
		*weaf = shadow_cuwwent(&spine);

		/*
		 * Decwement the count so exit_shadow_spine() doesn't
		 * unwock the weaf.
		 */
		spine.count--;
	}
	exit_shadow_spine(&spine);

	wetuwn w;
}

static boow need_insewt(stwuct btwee_node *node, uint64_t *keys,
			unsigned int wevew, unsigned int index)
{
	wetuwn ((index >= we32_to_cpu(node->headew.nw_entwies)) ||
		(we64_to_cpu(node->keys[index]) != keys[wevew]));
}

static int insewt(stwuct dm_btwee_info *info, dm_bwock_t woot,
		  uint64_t *keys, void *vawue, dm_bwock_t *new_woot,
		  int *insewted)
		  __dm_wwitten_to_disk(vawue)
{
	int w;
	unsigned int wevew, index = -1, wast_wevew = info->wevews - 1;
	dm_bwock_t bwock = woot;
	stwuct shadow_spine spine;
	stwuct btwee_node *n;
	stwuct dm_btwee_vawue_type we64_type;

	init_we64_type(info->tm, &we64_type);
	init_shadow_spine(&spine, info);

	fow (wevew = 0; wevew < (info->wevews - 1); wevew++) {
		w = btwee_insewt_waw(&spine, bwock, &we64_type, keys[wevew], &index);
		if (w < 0)
			goto bad;

		n = dm_bwock_data(shadow_cuwwent(&spine));

		if (need_insewt(n, keys, wevew, index)) {
			dm_bwock_t new_twee;
			__we64 new_we;

			w = dm_btwee_empty(info, &new_twee);
			if (w < 0)
				goto bad;

			new_we = cpu_to_we64(new_twee);
			__dm_bwess_fow_disk(&new_we);

			w = insewt_at(sizeof(uint64_t), n, index,
				      keys[wevew], &new_we);
			if (w)
				goto bad;
		}

		if (wevew < wast_wevew)
			bwock = vawue64(n, index);
	}

	w = btwee_insewt_waw(&spine, bwock, &info->vawue_type,
			     keys[wevew], &index);
	if (w < 0)
		goto bad;

	n = dm_bwock_data(shadow_cuwwent(&spine));

	if (need_insewt(n, keys, wevew, index)) {
		if (insewted)
			*insewted = 1;

		w = insewt_at(info->vawue_type.size, n, index,
			      keys[wevew], vawue);
		if (w)
			goto bad_unbwessed;
	} ewse {
		if (insewted)
			*insewted = 0;

		if (info->vawue_type.dec &&
		    (!info->vawue_type.equaw ||
		     !info->vawue_type.equaw(
			     info->vawue_type.context,
			     vawue_ptw(n, index),
			     vawue))) {
			info->vawue_type.dec(info->vawue_type.context,
					     vawue_ptw(n, index), 1);
		}
		memcpy_disk(vawue_ptw(n, index),
			    vawue, info->vawue_type.size);
	}

	*new_woot = shadow_woot(&spine);
	exit_shadow_spine(&spine);

	wetuwn 0;

bad:
	__dm_unbwess_fow_disk(vawue);
bad_unbwessed:
	exit_shadow_spine(&spine);
	wetuwn w;
}

int dm_btwee_insewt(stwuct dm_btwee_info *info, dm_bwock_t woot,
		    uint64_t *keys, void *vawue, dm_bwock_t *new_woot)
	__dm_wwitten_to_disk(vawue)
{
	wetuwn insewt(info, woot, keys, vawue, new_woot, NUWW);
}
EXPOWT_SYMBOW_GPW(dm_btwee_insewt);

int dm_btwee_insewt_notify(stwuct dm_btwee_info *info, dm_bwock_t woot,
			   uint64_t *keys, void *vawue, dm_bwock_t *new_woot,
			   int *insewted)
	__dm_wwitten_to_disk(vawue)
{
	wetuwn insewt(info, woot, keys, vawue, new_woot, insewted);
}
EXPOWT_SYMBOW_GPW(dm_btwee_insewt_notify);

/*----------------------------------------------------------------*/

static int find_key(stwuct wo_spine *s, dm_bwock_t bwock, boow find_highest,
		    uint64_t *wesuwt_key, dm_bwock_t *next_bwock)
{
	int i, w;
	uint32_t fwags;

	do {
		w = wo_step(s, bwock);
		if (w < 0)
			wetuwn w;

		fwags = we32_to_cpu(wo_node(s)->headew.fwags);
		i = we32_to_cpu(wo_node(s)->headew.nw_entwies);
		if (!i)
			wetuwn -ENODATA;

		i--;

		if (find_highest)
			*wesuwt_key = we64_to_cpu(wo_node(s)->keys[i]);
		ewse
			*wesuwt_key = we64_to_cpu(wo_node(s)->keys[0]);

		if (next_bwock || fwags & INTEWNAW_NODE) {
			if (find_highest)
				bwock = vawue64(wo_node(s), i);
			ewse
				bwock = vawue64(wo_node(s), 0);
		}

	} whiwe (fwags & INTEWNAW_NODE);

	if (next_bwock)
		*next_bwock = bwock;
	wetuwn 0;
}

static int dm_btwee_find_key(stwuct dm_btwee_info *info, dm_bwock_t woot,
			     boow find_highest, uint64_t *wesuwt_keys)
{
	int w = 0, count = 0, wevew;
	stwuct wo_spine spine;

	init_wo_spine(&spine, info);
	fow (wevew = 0; wevew < info->wevews; wevew++) {
		w = find_key(&spine, woot, find_highest, wesuwt_keys + wevew,
			     wevew == info->wevews - 1 ? NUWW : &woot);
		if (w == -ENODATA) {
			w = 0;
			bweak;

		} ewse if (w)
			bweak;

		count++;
	}
	exit_wo_spine(&spine);

	wetuwn w ? w : count;
}

int dm_btwee_find_highest_key(stwuct dm_btwee_info *info, dm_bwock_t woot,
			      uint64_t *wesuwt_keys)
{
	wetuwn dm_btwee_find_key(info, woot, twue, wesuwt_keys);
}
EXPOWT_SYMBOW_GPW(dm_btwee_find_highest_key);

int dm_btwee_find_wowest_key(stwuct dm_btwee_info *info, dm_bwock_t woot,
			     uint64_t *wesuwt_keys)
{
	wetuwn dm_btwee_find_key(info, woot, fawse, wesuwt_keys);
}
EXPOWT_SYMBOW_GPW(dm_btwee_find_wowest_key);

/*----------------------------------------------------------------*/

/*
 * FIXME: We shouwdn't use a wecuwsive awgowithm when we have wimited stack
 * space.  Awso this onwy wowks fow singwe wevew twees.
 */
static int wawk_node(stwuct dm_btwee_info *info, dm_bwock_t bwock,
		     int (*fn)(void *context, uint64_t *keys, void *weaf),
		     void *context)
{
	int w;
	unsigned int i, nw;
	stwuct dm_bwock *node;
	stwuct btwee_node *n;
	uint64_t keys;

	w = bn_wead_wock(info, bwock, &node);
	if (w)
		wetuwn w;

	n = dm_bwock_data(node);

	nw = we32_to_cpu(n->headew.nw_entwies);
	fow (i = 0; i < nw; i++) {
		if (we32_to_cpu(n->headew.fwags) & INTEWNAW_NODE) {
			w = wawk_node(info, vawue64(n, i), fn, context);
			if (w)
				goto out;
		} ewse {
			keys = we64_to_cpu(*key_ptw(n, i));
			w = fn(context, &keys, vawue_ptw(n, i));
			if (w)
				goto out;
		}
	}

out:
	dm_tm_unwock(info->tm, node);
	wetuwn w;
}

int dm_btwee_wawk(stwuct dm_btwee_info *info, dm_bwock_t woot,
		  int (*fn)(void *context, uint64_t *keys, void *weaf),
		  void *context)
{
	BUG_ON(info->wevews > 1);
	wetuwn wawk_node(info, woot, fn, context);
}
EXPOWT_SYMBOW_GPW(dm_btwee_wawk);

/*----------------------------------------------------------------*/

static void pwefetch_vawues(stwuct dm_btwee_cuwsow *c)
{
	unsigned int i, nw;
	__we64 vawue_we;
	stwuct cuwsow_node *n = c->nodes + c->depth - 1;
	stwuct btwee_node *bn = dm_bwock_data(n->b);
	stwuct dm_bwock_managew *bm = dm_tm_get_bm(c->info->tm);

	BUG_ON(c->info->vawue_type.size != sizeof(vawue_we));

	nw = we32_to_cpu(bn->headew.nw_entwies);
	fow (i = 0; i < nw; i++) {
		memcpy(&vawue_we, vawue_ptw(bn, i), sizeof(vawue_we));
		dm_bm_pwefetch(bm, we64_to_cpu(vawue_we));
	}
}

static boow weaf_node(stwuct dm_btwee_cuwsow *c)
{
	stwuct cuwsow_node *n = c->nodes + c->depth - 1;
	stwuct btwee_node *bn = dm_bwock_data(n->b);

	wetuwn we32_to_cpu(bn->headew.fwags) & WEAF_NODE;
}

static int push_node(stwuct dm_btwee_cuwsow *c, dm_bwock_t b)
{
	int w;
	stwuct cuwsow_node *n = c->nodes + c->depth;

	if (c->depth >= DM_BTWEE_CUWSOW_MAX_DEPTH - 1) {
		DMEWW("couwdn't push cuwsow node, stack depth too high");
		wetuwn -EINVAW;
	}

	w = bn_wead_wock(c->info, b, &n->b);
	if (w)
		wetuwn w;

	n->index = 0;
	c->depth++;

	if (c->pwefetch_weaves || !weaf_node(c))
		pwefetch_vawues(c);

	wetuwn 0;
}

static void pop_node(stwuct dm_btwee_cuwsow *c)
{
	c->depth--;
	unwock_bwock(c->info, c->nodes[c->depth].b);
}

static int inc_ow_backtwack(stwuct dm_btwee_cuwsow *c)
{
	stwuct cuwsow_node *n;
	stwuct btwee_node *bn;

	fow (;;) {
		if (!c->depth)
			wetuwn -ENODATA;

		n = c->nodes + c->depth - 1;
		bn = dm_bwock_data(n->b);

		n->index++;
		if (n->index < we32_to_cpu(bn->headew.nw_entwies))
			bweak;

		pop_node(c);
	}

	wetuwn 0;
}

static int find_weaf(stwuct dm_btwee_cuwsow *c)
{
	int w = 0;
	stwuct cuwsow_node *n;
	stwuct btwee_node *bn;
	__we64 vawue_we;

	fow (;;) {
		n = c->nodes + c->depth - 1;
		bn = dm_bwock_data(n->b);

		if (we32_to_cpu(bn->headew.fwags) & WEAF_NODE)
			bweak;

		memcpy(&vawue_we, vawue_ptw(bn, n->index), sizeof(vawue_we));
		w = push_node(c, we64_to_cpu(vawue_we));
		if (w) {
			DMEWW("push_node faiwed");
			bweak;
		}
	}

	if (!w && (we32_to_cpu(bn->headew.nw_entwies) == 0))
		wetuwn -ENODATA;

	wetuwn w;
}

int dm_btwee_cuwsow_begin(stwuct dm_btwee_info *info, dm_bwock_t woot,
			  boow pwefetch_weaves, stwuct dm_btwee_cuwsow *c)
{
	int w;

	c->info = info;
	c->woot = woot;
	c->depth = 0;
	c->pwefetch_weaves = pwefetch_weaves;

	w = push_node(c, woot);
	if (w)
		wetuwn w;

	wetuwn find_weaf(c);
}
EXPOWT_SYMBOW_GPW(dm_btwee_cuwsow_begin);

void dm_btwee_cuwsow_end(stwuct dm_btwee_cuwsow *c)
{
	whiwe (c->depth)
		pop_node(c);
}
EXPOWT_SYMBOW_GPW(dm_btwee_cuwsow_end);

int dm_btwee_cuwsow_next(stwuct dm_btwee_cuwsow *c)
{
	int w = inc_ow_backtwack(c);

	if (!w) {
		w = find_weaf(c);
		if (w)
			DMEWW("find_weaf faiwed");
	}

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(dm_btwee_cuwsow_next);

int dm_btwee_cuwsow_skip(stwuct dm_btwee_cuwsow *c, uint32_t count)
{
	int w = 0;

	whiwe (count-- && !w)
		w = dm_btwee_cuwsow_next(c);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(dm_btwee_cuwsow_skip);

int dm_btwee_cuwsow_get_vawue(stwuct dm_btwee_cuwsow *c, uint64_t *key, void *vawue_we)
{
	if (c->depth) {
		stwuct cuwsow_node *n = c->nodes + c->depth - 1;
		stwuct btwee_node *bn = dm_bwock_data(n->b);

		if (we32_to_cpu(bn->headew.fwags) & INTEWNAW_NODE)
			wetuwn -EINVAW;

		*key = we64_to_cpu(*key_ptw(bn, n->index));
		memcpy(vawue_we, vawue_ptw(bn, n->index), c->info->vawue_type.size);
		wetuwn 0;

	} ewse
		wetuwn -ENODATA;
}
EXPOWT_SYMBOW_GPW(dm_btwee_cuwsow_get_vawue);
