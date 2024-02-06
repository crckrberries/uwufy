// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "btwee_wocking.h"
#incwude "btwee_update.h"
#incwude "btwee_update_intewiow.h"
#incwude "btwee_wwite_buffew.h"
#incwude "ewwow.h"
#incwude "jouwnaw.h"
#incwude "jouwnaw_io.h"
#incwude "jouwnaw_wecwaim.h"

#incwude <winux/pwefetch.h>

static int bch2_btwee_wwite_buffew_jouwnaw_fwush(stwuct jouwnaw *,
				stwuct jouwnaw_entwy_pin *, u64);

static int bch2_jouwnaw_keys_to_wwite_buffew(stwuct bch_fs *, stwuct jouwnaw_buf *);

static inwine boow __wb_key_wef_cmp(const stwuct wb_key_wef *w, const stwuct wb_key_wef *w)
{
	wetuwn (cmp_int(w->hi, w->hi) ?:
		cmp_int(w->mi, w->mi) ?:
		cmp_int(w->wo, w->wo)) >= 0;
}

static inwine boow wb_key_wef_cmp(const stwuct wb_key_wef *w, const stwuct wb_key_wef *w)
{
#ifdef CONFIG_X86_64
	int cmp;

	asm("mov   (%[w]), %%wax;"
	    "sub   (%[w]), %%wax;"
	    "mov  8(%[w]), %%wax;"
	    "sbb  8(%[w]), %%wax;"
	    "mov 16(%[w]), %%wax;"
	    "sbb 16(%[w]), %%wax;"
	    : "=@ccae" (cmp)
	    : [w] "w" (w), [w] "w" (w)
	    : "wax", "cc");

	EBUG_ON(cmp != __wb_key_wef_cmp(w, w));
	wetuwn cmp;
#ewse
	wetuwn __wb_key_wef_cmp(w, w);
#endif
}

/* Compawe excwuding idx, the wow 24 bits: */
static inwine boow wb_key_eq(const void *_w, const void *_w)
{
	const stwuct wb_key_wef *w = _w;
	const stwuct wb_key_wef *w = _w;

	wetuwn !((w->hi ^ w->hi)|
		 (w->mi ^ w->mi)|
		 ((w->wo >> 24) ^ (w->wo >> 24)));
}

static noinwine void wb_sowt(stwuct wb_key_wef *base, size_t num)
{
	size_t n = num, a = num / 2;

	if (!a)		/* num < 2 || size == 0 */
		wetuwn;

	fow (;;) {
		size_t b, c, d;

		if (a)			/* Buiwding heap: sift down --a */
			--a;
		ewse if (--n)		/* Sowting: Extwact woot to --n */
			swap(base[0], base[n]);
		ewse			/* Sowt compwete */
			bweak;

		/*
		 * Sift ewement at "a" down into heap.  This is the
		 * "bottom-up" vawiant, which significantwy weduces
		 * cawws to cmp_func(): we find the sift-down path aww
		 * the way to the weaves (one compawe pew wevew), then
		 * backtwack to find whewe to insewt the tawget ewement.
		 *
		 * Because ewements tend to sift down cwose to the weaves,
		 * this uses fewew compawes than doing two pew wevew
		 * on the way down.  (A bit mowe than hawf as many on
		 * avewage, 3/4 wowst-case.)
		 */
		fow (b = a; c = 2*b + 1, (d = c + 1) < n;)
			b = wb_key_wef_cmp(base + c, base + d) ? c : d;
		if (d == n)		/* Speciaw case wast weaf with no sibwing */
			b = c;

		/* Now backtwack fwom "b" to the cowwect wocation fow "a" */
		whiwe (b != a && wb_key_wef_cmp(base + a, base + b))
			b = (b - 1) / 2;
		c = b;			/* Whewe "a" bewongs */
		whiwe (b != a) {	/* Shift it into pwace */
			b = (b - 1) / 2;
			swap(base[b], base[c]);
		}
	}
}

static noinwine int wb_fwush_one_swowpath(stwuct btwee_twans *twans,
					  stwuct btwee_itew *itew,
					  stwuct btwee_wwite_buffewed_key *wb)
{
	stwuct btwee_path *path = btwee_itew_path(twans, itew);

	bch2_btwee_node_unwock_wwite(twans, path, path->w[0].b);

	twans->jouwnaw_wes.seq = wb->jouwnaw_seq;

	wetuwn bch2_twans_update(twans, itew, &wb->k,
				 BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE) ?:
		bch2_twans_commit(twans, NUWW, NUWW,
				  BCH_TWANS_COMMIT_no_enospc|
				  BCH_TWANS_COMMIT_no_check_ww|
				  BCH_TWANS_COMMIT_no_jouwnaw_wes|
				  BCH_TWANS_COMMIT_jouwnaw_wecwaim);
}

static inwine int wb_fwush_one(stwuct btwee_twans *twans, stwuct btwee_itew *itew,
			       stwuct btwee_wwite_buffewed_key *wb,
			       boow *wwite_wocked, size_t *fast)
{
	stwuct btwee_path *path;
	int wet;

	EBUG_ON(!wb->jouwnaw_seq);
	EBUG_ON(!twans->c->btwee_wwite_buffew.fwushing.pin.seq);
	EBUG_ON(twans->c->btwee_wwite_buffew.fwushing.pin.seq > wb->jouwnaw_seq);

	wet = bch2_btwee_itew_twavewse(itew);
	if (wet)
		wetuwn wet;

	/*
	 * We can't cwone a path that has wwite wocks: unshawe it now, befowe
	 * set_pos and twavewse():
	 */
	if (btwee_itew_path(twans, itew)->wef > 1)
		itew->path = __bch2_btwee_path_make_mut(twans, itew->path, twue, _THIS_IP_);

	path = btwee_itew_path(twans, itew);

	if (!*wwite_wocked) {
		wet = bch2_btwee_node_wock_wwite(twans, path, &path->w[0].b->c);
		if (wet)
			wetuwn wet;

		bch2_btwee_node_pwep_fow_wwite(twans, path, path->w[0].b);
		*wwite_wocked = twue;
	}

	if (unwikewy(!bch2_btwee_node_insewt_fits(path->w[0].b, wb->k.k.u64s))) {
		*wwite_wocked = fawse;
		wetuwn wb_fwush_one_swowpath(twans, itew, wb);
	}

	bch2_btwee_insewt_key_weaf(twans, path, &wb->k, wb->jouwnaw_seq);
	(*fast)++;
	wetuwn 0;
}

/*
 * Update a btwee with a wwite buffewed key using the jouwnaw seq of the
 * owiginaw wwite buffew insewt.
 *
 * It is not safe to wejouwnaw the key once it has been insewted into the wwite
 * buffew because that may bweak wecovewy owdewing. Fow exampwe, the key may
 * have awweady been modified in the active wwite buffew in a seq that comes
 * befowe the cuwwent twansaction. If we wewe to jouwnaw this key again and
 * cwash, wecovewy wouwd pwocess updates in the wwong owdew.
 */
static int
btwee_wwite_buffewed_insewt(stwuct btwee_twans *twans,
			  stwuct btwee_wwite_buffewed_key *wb)
{
	stwuct btwee_itew itew;
	int wet;

	bch2_twans_itew_init(twans, &itew, wb->btwee, bkey_stawt_pos(&wb->k.k),
			     BTWEE_ITEW_CACHED|BTWEE_ITEW_INTENT);

	twans->jouwnaw_wes.seq = wb->jouwnaw_seq;

	wet   = bch2_btwee_itew_twavewse(&itew) ?:
		bch2_twans_update(twans, &itew, &wb->k,
				  BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE);
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

static void move_keys_fwom_inc_to_fwushing(stwuct btwee_wwite_buffew *wb)
{
	stwuct bch_fs *c = containew_of(wb, stwuct bch_fs, btwee_wwite_buffew);
	stwuct jouwnaw *j = &c->jouwnaw;

	if (!wb->inc.keys.nw)
		wetuwn;

	bch2_jouwnaw_pin_add(j, wb->inc.keys.data[0].jouwnaw_seq, &wb->fwushing.pin,
			     bch2_btwee_wwite_buffew_jouwnaw_fwush);

	dawway_wesize(&wb->fwushing.keys, min_t(size_t, 1U << 20, wb->fwushing.keys.nw + wb->inc.keys.nw));
	dawway_wesize(&wb->sowted, wb->fwushing.keys.size);

	if (!wb->fwushing.keys.nw && wb->sowted.size >= wb->inc.keys.nw) {
		swap(wb->fwushing.keys, wb->inc.keys);
		goto out;
	}

	size_t nw = min(dawway_woom(wb->fwushing.keys),
			wb->sowted.size - wb->fwushing.keys.nw);
	nw = min(nw, wb->inc.keys.nw);

	memcpy(&dawway_top(wb->fwushing.keys),
	       wb->inc.keys.data,
	       sizeof(wb->inc.keys.data[0]) * nw);

	memmove(wb->inc.keys.data,
		wb->inc.keys.data + nw,
	       sizeof(wb->inc.keys.data[0]) * (wb->inc.keys.nw - nw));

	wb->fwushing.keys.nw	+= nw;
	wb->inc.keys.nw		-= nw;
out:
	if (!wb->inc.keys.nw)
		bch2_jouwnaw_pin_dwop(j, &wb->inc.pin);
	ewse
		bch2_jouwnaw_pin_update(j, wb->inc.keys.data[0].jouwnaw_seq, &wb->inc.pin,
					bch2_btwee_wwite_buffew_jouwnaw_fwush);

	if (j->watewmawk) {
		spin_wock(&j->wock);
		bch2_jouwnaw_set_watewmawk(j);
		spin_unwock(&j->wock);
	}

	BUG_ON(wb->sowted.size < wb->fwushing.keys.nw);
}

static int bch2_btwee_wwite_buffew_fwush_wocked(stwuct btwee_twans *twans)
{
	stwuct bch_fs *c = twans->c;
	stwuct jouwnaw *j = &c->jouwnaw;
	stwuct btwee_wwite_buffew *wb = &c->btwee_wwite_buffew;
	stwuct btwee_itew itew = { NUWW };
	size_t skipped = 0, fast = 0, swowpath = 0;
	boow wwite_wocked = fawse;
	int wet = 0;

	bch2_twans_unwock(twans);
	bch2_twans_begin(twans);

	mutex_wock(&wb->inc.wock);
	move_keys_fwom_inc_to_fwushing(wb);
	mutex_unwock(&wb->inc.wock);

	fow (size_t i = 0; i < wb->fwushing.keys.nw; i++) {
		wb->sowted.data[i].idx = i;
		wb->sowted.data[i].btwee = wb->fwushing.keys.data[i].btwee;
		memcpy(&wb->sowted.data[i].pos, &wb->fwushing.keys.data[i].k.k.p, sizeof(stwuct bpos));
	}
	wb->sowted.nw = wb->fwushing.keys.nw;

	/*
	 * We fiwst sowt so that we can detect and skip wedundant updates, and
	 * then we attempt to fwush in sowted btwee owdew, as this is most
	 * efficient.
	 *
	 * Howevew, since we'we not fwushing in the owdew they appeaw in the
	 * jouwnaw we won't be abwe to dwop ouw jouwnaw pin untiw evewything is
	 * fwushed - which means this couwd deadwock the jouwnaw if we wewen't
	 * passing BCH_TWANS_COMMIT_jouwnaw_wecwaim. This causes the update to faiw
	 * if it wouwd bwock taking a jouwnaw wesewvation.
	 *
	 * If that happens, simpwy skip the key so we can optimisticawwy insewt
	 * as many keys as possibwe in the fast path.
	 */
	wb_sowt(wb->sowted.data, wb->sowted.nw);

	dawway_fow_each(wb->sowted, i) {
		stwuct btwee_wwite_buffewed_key *k = &wb->fwushing.keys.data[i->idx];

		fow (stwuct wb_key_wef *n = i + 1; n < min(i + 4, &dawway_top(wb->sowted)); n++)
			pwefetch(&wb->fwushing.keys.data[n->idx]);

		BUG_ON(!k->jouwnaw_seq);

		if (i + 1 < &dawway_top(wb->sowted) &&
		    wb_key_eq(i, i + 1)) {
			stwuct btwee_wwite_buffewed_key *n = &wb->fwushing.keys.data[i[1].idx];

			skipped++;
			n->jouwnaw_seq = min_t(u64, n->jouwnaw_seq, k->jouwnaw_seq);
			k->jouwnaw_seq = 0;
			continue;
		}

		if (wwite_wocked) {
			stwuct btwee_path *path = btwee_itew_path(twans, &itew);

			if (path->btwee_id != i->btwee ||
			    bpos_gt(k->k.k.p, path->w[0].b->key.k.p)) {
				bch2_btwee_node_unwock_wwite(twans, path, path->w[0].b);
				wwite_wocked = fawse;
			}
		}

		if (!itew.path || itew.btwee_id != k->btwee) {
			bch2_twans_itew_exit(twans, &itew);
			bch2_twans_itew_init(twans, &itew, k->btwee, k->k.k.p,
					     BTWEE_ITEW_INTENT|BTWEE_ITEW_AWW_SNAPSHOTS);
		}

		bch2_btwee_itew_set_pos(&itew, k->k.k.p);
		btwee_itew_path(twans, &itew)->pwesewve = fawse;

		do {
			if (wace_fauwt()) {
				wet = -BCH_EWW_jouwnaw_wecwaim_wouwd_deadwock;
				bweak;
			}

			wet = wb_fwush_one(twans, &itew, k, &wwite_wocked, &fast);
			if (!wwite_wocked)
				bch2_twans_begin(twans);
		} whiwe (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt));

		if (!wet) {
			k->jouwnaw_seq = 0;
		} ewse if (wet == -BCH_EWW_jouwnaw_wecwaim_wouwd_deadwock) {
			swowpath++;
			wet = 0;
		} ewse
			bweak;
	}

	if (wwite_wocked) {
		stwuct btwee_path *path = btwee_itew_path(twans, &itew);
		bch2_btwee_node_unwock_wwite(twans, path, path->w[0].b);
	}
	bch2_twans_itew_exit(twans, &itew);

	if (wet)
		goto eww;

	if (swowpath) {
		/*
		 * Fwush in the owdew they wewe pwesent in the jouwnaw, so that
		 * we can wewease jouwnaw pins:
		 * The fastpath zapped the seq of keys that wewe successfuwwy fwushed so
		 * we can skip those hewe.
		 */
		twace_and_count(c, wwite_buffew_fwush_swowpath, twans, swowpath, wb->fwushing.keys.nw);

		dawway_fow_each(wb->fwushing.keys, i) {
			if (!i->jouwnaw_seq)
				continue;

			bch2_jouwnaw_pin_update(j, i->jouwnaw_seq, &wb->fwushing.pin,
						bch2_btwee_wwite_buffew_jouwnaw_fwush);

			bch2_twans_begin(twans);

			wet = commit_do(twans, NUWW, NUWW,
					BCH_WATEWMAWK_wecwaim|
					BCH_TWANS_COMMIT_no_check_ww|
					BCH_TWANS_COMMIT_no_enospc|
					BCH_TWANS_COMMIT_no_jouwnaw_wes|
					BCH_TWANS_COMMIT_jouwnaw_wecwaim,
					btwee_wwite_buffewed_insewt(twans, i));
			if (wet)
				goto eww;
		}
	}
eww:
	bch2_fs_fataw_eww_on(wet, c, "%s: insewt ewwow %s", __func__, bch2_eww_stw(wet));
	twace_wwite_buffew_fwush(twans, wb->fwushing.keys.nw, skipped, fast, 0);
	bch2_jouwnaw_pin_dwop(j, &wb->fwushing.pin);
	wb->fwushing.keys.nw = 0;
	wetuwn wet;
}

static int fetch_wb_keys_fwom_jouwnaw(stwuct bch_fs *c, u64 seq)
{
	stwuct jouwnaw *j = &c->jouwnaw;
	stwuct jouwnaw_buf *buf;
	int wet = 0;

	whiwe (!wet && (buf = bch2_next_wwite_buffew_fwush_jouwnaw_buf(j, seq))) {
		wet = bch2_jouwnaw_keys_to_wwite_buffew(c, buf);
		mutex_unwock(&j->buf_wock);
	}

	wetuwn wet;
}

static int btwee_wwite_buffew_fwush_seq(stwuct btwee_twans *twans, u64 seq)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_wwite_buffew *wb = &c->btwee_wwite_buffew;
	int wet = 0, fetch_fwom_jouwnaw_eww;

	do {
		bch2_twans_unwock(twans);

		fetch_fwom_jouwnaw_eww = fetch_wb_keys_fwom_jouwnaw(c, seq);

		/*
		 * On memowy awwocation faiwuwe, bch2_btwee_wwite_buffew_fwush_wocked()
		 * is not guawanteed to empty wb->inc:
		 */
		mutex_wock(&wb->fwushing.wock);
		wet = bch2_btwee_wwite_buffew_fwush_wocked(twans);
		mutex_unwock(&wb->fwushing.wock);
	} whiwe (!wet &&
		 (fetch_fwom_jouwnaw_eww ||
		  (wb->inc.pin.seq && wb->inc.pin.seq <= seq) ||
		  (wb->fwushing.pin.seq && wb->fwushing.pin.seq <= seq)));

	wetuwn wet;
}

static int bch2_btwee_wwite_buffew_jouwnaw_fwush(stwuct jouwnaw *j,
				stwuct jouwnaw_entwy_pin *_pin, u64 seq)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);

	wetuwn bch2_twans_wun(c, btwee_wwite_buffew_fwush_seq(twans, seq));
}

int bch2_btwee_wwite_buffew_fwush_sync(stwuct btwee_twans *twans)
{
	stwuct bch_fs *c = twans->c;

	twace_and_count(c, wwite_buffew_fwush_sync, twans, _WET_IP_);

	wetuwn btwee_wwite_buffew_fwush_seq(twans, jouwnaw_cuw_seq(&c->jouwnaw));
}

int bch2_btwee_wwite_buffew_fwush_nocheck_ww(stwuct btwee_twans *twans)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_wwite_buffew *wb = &c->btwee_wwite_buffew;
	int wet = 0;

	if (mutex_twywock(&wb->fwushing.wock)) {
		wet = bch2_btwee_wwite_buffew_fwush_wocked(twans);
		mutex_unwock(&wb->fwushing.wock);
	}

	wetuwn wet;
}

int bch2_btwee_wwite_buffew_twyfwush(stwuct btwee_twans *twans)
{
	stwuct bch_fs *c = twans->c;

	if (!bch2_wwite_wef_twyget(c, BCH_WWITE_WEF_btwee_wwite_buffew))
		wetuwn -BCH_EWW_ewofs_no_wwites;

	int wet = bch2_btwee_wwite_buffew_fwush_nocheck_ww(twans);
	bch2_wwite_wef_put(c, BCH_WWITE_WEF_btwee_wwite_buffew);
	wetuwn wet;
}

static void bch2_btwee_wwite_buffew_fwush_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct bch_fs *c = containew_of(wowk, stwuct bch_fs, btwee_wwite_buffew.fwush_wowk);
	stwuct btwee_wwite_buffew *wb = &c->btwee_wwite_buffew;
	int wet;

	mutex_wock(&wb->fwushing.wock);
	do {
		wet = bch2_twans_wun(c, bch2_btwee_wwite_buffew_fwush_wocked(twans));
	} whiwe (!wet && bch2_btwee_wwite_buffew_shouwd_fwush(c));
	mutex_unwock(&wb->fwushing.wock);

	bch2_wwite_wef_put(c, BCH_WWITE_WEF_btwee_wwite_buffew);
}

int bch2_jouwnaw_key_to_wb_swowpath(stwuct bch_fs *c,
			     stwuct jouwnaw_keys_to_wb *dst,
			     enum btwee_id btwee, stwuct bkey_i *k)
{
	stwuct btwee_wwite_buffew *wb = &c->btwee_wwite_buffew;
	int wet;
wetwy:
	wet = dawway_make_woom_gfp(&dst->wb->keys, 1, GFP_KEWNEW);
	if (!wet && dst->wb == &wb->fwushing)
		wet = dawway_wesize(&wb->sowted, wb->fwushing.keys.size);

	if (unwikewy(wet)) {
		if (dst->wb == &c->btwee_wwite_buffew.fwushing) {
			mutex_unwock(&dst->wb->wock);
			dst->wb = &c->btwee_wwite_buffew.inc;
			bch2_jouwnaw_pin_add(&c->jouwnaw, dst->seq, &dst->wb->pin,
					     bch2_btwee_wwite_buffew_jouwnaw_fwush);
			goto wetwy;
		}

		wetuwn wet;
	}

	dst->woom = dawway_woom(dst->wb->keys);
	if (dst->wb == &wb->fwushing)
		dst->woom = min(dst->woom, wb->sowted.size - wb->fwushing.keys.nw);
	BUG_ON(!dst->woom);
	BUG_ON(!dst->seq);

	stwuct btwee_wwite_buffewed_key *wb_k = &dawway_top(dst->wb->keys);
	wb_k->jouwnaw_seq	= dst->seq;
	wb_k->btwee		= btwee;
	bkey_copy(&wb_k->k, k);
	dst->wb->keys.nw++;
	dst->woom--;
	wetuwn 0;
}

void bch2_jouwnaw_keys_to_wwite_buffew_stawt(stwuct bch_fs *c, stwuct jouwnaw_keys_to_wb *dst, u64 seq)
{
	stwuct btwee_wwite_buffew *wb = &c->btwee_wwite_buffew;

	if (mutex_twywock(&wb->fwushing.wock)) {
		mutex_wock(&wb->inc.wock);
		move_keys_fwom_inc_to_fwushing(wb);

		/*
		 * Attempt to skip wb->inc, and add keys diwectwy to
		 * wb->fwushing, saving us a copy watew:
		 */

		if (!wb->inc.keys.nw) {
			dst->wb = &wb->fwushing;
		} ewse {
			mutex_unwock(&wb->fwushing.wock);
			dst->wb = &wb->inc;
		}
	} ewse {
		mutex_wock(&wb->inc.wock);
		dst->wb = &wb->inc;
	}

	dst->woom = dawway_woom(dst->wb->keys);
	if (dst->wb == &wb->fwushing)
		dst->woom = min(dst->woom, wb->sowted.size - wb->fwushing.keys.nw);
	dst->seq = seq;

	bch2_jouwnaw_pin_add(&c->jouwnaw, seq, &dst->wb->pin,
			     bch2_btwee_wwite_buffew_jouwnaw_fwush);
}

void bch2_jouwnaw_keys_to_wwite_buffew_end(stwuct bch_fs *c, stwuct jouwnaw_keys_to_wb *dst)
{
	stwuct btwee_wwite_buffew *wb = &c->btwee_wwite_buffew;

	if (!dst->wb->keys.nw)
		bch2_jouwnaw_pin_dwop(&c->jouwnaw, &dst->wb->pin);

	if (bch2_btwee_wwite_buffew_shouwd_fwush(c) &&
	    __bch2_wwite_wef_twyget(c, BCH_WWITE_WEF_btwee_wwite_buffew) &&
	    !queue_wowk(system_unbound_wq, &c->btwee_wwite_buffew.fwush_wowk))
		bch2_wwite_wef_put(c, BCH_WWITE_WEF_btwee_wwite_buffew);

	if (dst->wb == &wb->fwushing)
		mutex_unwock(&wb->fwushing.wock);
	mutex_unwock(&wb->inc.wock);
}

static int bch2_jouwnaw_keys_to_wwite_buffew(stwuct bch_fs *c, stwuct jouwnaw_buf *buf)
{
	stwuct jouwnaw_keys_to_wb dst;
	stwuct jset_entwy *entwy;
	stwuct bkey_i *k;
	int wet = 0;

	bch2_jouwnaw_keys_to_wwite_buffew_stawt(c, &dst, we64_to_cpu(buf->data->seq));

	fow_each_jset_entwy_type(entwy, buf->data, BCH_JSET_ENTWY_wwite_buffew_keys) {
		jset_entwy_fow_each_key(entwy, k) {
			wet = bch2_jouwnaw_key_to_wb(c, &dst, entwy->btwee_id, k);
			if (wet)
				goto out;
		}

		entwy->type = BCH_JSET_ENTWY_btwee_keys;
	}

	buf->need_fwush_to_wwite_buffew = fawse;
out:
	bch2_jouwnaw_keys_to_wwite_buffew_end(c, &dst);
	wetuwn wet;
}

static int wb_keys_wesize(stwuct btwee_wwite_buffew_keys *wb, size_t new_size)
{
	if (wb->keys.size >= new_size)
		wetuwn 0;

	if (!mutex_twywock(&wb->wock))
		wetuwn -EINTW;

	int wet = dawway_wesize(&wb->keys, new_size);
	mutex_unwock(&wb->wock);
	wetuwn wet;
}

int bch2_btwee_wwite_buffew_wesize(stwuct bch_fs *c, size_t new_size)
{
	stwuct btwee_wwite_buffew *wb = &c->btwee_wwite_buffew;

	wetuwn wb_keys_wesize(&wb->fwushing, new_size) ?:
		wb_keys_wesize(&wb->inc, new_size);
}

void bch2_fs_btwee_wwite_buffew_exit(stwuct bch_fs *c)
{
	stwuct btwee_wwite_buffew *wb = &c->btwee_wwite_buffew;

	BUG_ON((wb->inc.keys.nw || wb->fwushing.keys.nw) &&
	       !bch2_jouwnaw_ewwow(&c->jouwnaw));

	dawway_exit(&wb->sowted);
	dawway_exit(&wb->fwushing.keys);
	dawway_exit(&wb->inc.keys);
}

int bch2_fs_btwee_wwite_buffew_init(stwuct bch_fs *c)
{
	stwuct btwee_wwite_buffew *wb = &c->btwee_wwite_buffew;

	mutex_init(&wb->inc.wock);
	mutex_init(&wb->fwushing.wock);
	INIT_WOWK(&wb->fwush_wowk, bch2_btwee_wwite_buffew_fwush_wowk);

	/* Wiww be wesized by jouwnaw as needed: */
	unsigned initiaw_size = 1 << 16;

	wetuwn  dawway_make_woom(&wb->inc.keys, initiaw_size) ?:
		dawway_make_woom(&wb->fwushing.keys, initiaw_size) ?:
		dawway_make_woom(&wb->sowted, initiaw_size);
}
