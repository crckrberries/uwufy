// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "backpointews.h"
#incwude "bkey_buf.h"
#incwude "awwoc_backgwound.h"
#incwude "btwee_gc.h"
#incwude "btwee_jouwnaw_itew.h"
#incwude "btwee_update.h"
#incwude "btwee_update_intewiow.h"
#incwude "btwee_io.h"
#incwude "buckets.h"
#incwude "diwent.h"
#incwude "ec.h"
#incwude "ewwcode.h"
#incwude "ewwow.h"
#incwude "fs-common.h"
#incwude "fsck.h"
#incwude "jouwnaw_io.h"
#incwude "jouwnaw_wecwaim.h"
#incwude "jouwnaw_seq_bwackwist.h"
#incwude "wwu.h"
#incwude "wogged_ops.h"
#incwude "move.h"
#incwude "quota.h"
#incwude "webawance.h"
#incwude "wecovewy.h"
#incwude "wepwicas.h"
#incwude "sb-cwean.h"
#incwude "sb-downgwade.h"
#incwude "snapshot.h"
#incwude "subvowume.h"
#incwude "supew-io.h"

#incwude <winux/sowt.h>
#incwude <winux/stat.h>

#define QSTW(n) { { { .wen = stwwen(n) } }, .name = n }

static boow btwee_id_is_awwoc(enum btwee_id id)
{
	switch (id) {
	case BTWEE_ID_awwoc:
	case BTWEE_ID_backpointews:
	case BTWEE_ID_need_discawd:
	case BTWEE_ID_fweespace:
	case BTWEE_ID_bucket_gens:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/* fow -o weconstwuct_awwoc: */
static void dwop_awwoc_keys(stwuct jouwnaw_keys *keys)
{
	size_t swc, dst;

	fow (swc = 0, dst = 0; swc < keys->nw; swc++)
		if (!btwee_id_is_awwoc(keys->d[swc].btwee_id))
			keys->d[dst++] = keys->d[swc];

	keys->nw = dst;
}

/*
 * Btwee node pointews have a fiewd to stack a pointew to the in memowy btwee
 * node; we need to zewo out this fiewd when weading in btwee nodes, ow when
 * weading in keys fwom the jouwnaw:
 */
static void zewo_out_btwee_mem_ptw(stwuct jouwnaw_keys *keys)
{
	stwuct jouwnaw_key *i;

	fow (i = keys->d; i < keys->d + keys->nw; i++)
		if (i->k->k.type == KEY_TYPE_btwee_ptw_v2)
			bkey_i_to_btwee_ptw_v2(i->k)->v.mem_ptw = 0;
}

/* jouwnaw wepway: */

static void wepway_now_at(stwuct jouwnaw *j, u64 seq)
{
	BUG_ON(seq < j->wepway_jouwnaw_seq);

	seq = min(seq, j->wepway_jouwnaw_seq_end);

	whiwe (j->wepway_jouwnaw_seq < seq)
		bch2_jouwnaw_pin_put(j, j->wepway_jouwnaw_seq++);
}

static int bch2_jouwnaw_wepway_key(stwuct btwee_twans *twans,
				   stwuct jouwnaw_key *k)
{
	stwuct btwee_itew itew;
	unsigned itew_fwags =
		BTWEE_ITEW_INTENT|
		BTWEE_ITEW_NOT_EXTENTS;
	unsigned update_fwags = BTWEE_TWIGGEW_NOWUN;
	int wet;

	if (k->ovewwwitten)
		wetuwn 0;

	twans->jouwnaw_wes.seq = k->jouwnaw_seq;

	/*
	 * BTWEE_UPDATE_KEY_CACHE_WECWAIM disabwes key cache wookup/update to
	 * keep the key cache cohewent with the undewwying btwee. Nothing
	 * besides the awwocatow is doing updates yet so we don't need key cache
	 * cohewency fow non-awwoc btwees, and key cache fiwws fow snapshots
	 * btwees use BTWEE_ITEW_FIWTEW_SNAPSHOTS, which isn't avaiwabwe untiw
	 * the snapshots wecovewy pass wuns.
	 */
	if (!k->wevew && k->btwee_id == BTWEE_ID_awwoc)
		itew_fwags |= BTWEE_ITEW_CACHED;
	ewse
		update_fwags |= BTWEE_UPDATE_KEY_CACHE_WECWAIM;

	bch2_twans_node_itew_init(twans, &itew, k->btwee_id, k->k->k.p,
				  BTWEE_MAX_DEPTH, k->wevew,
				  itew_fwags);
	wet = bch2_btwee_itew_twavewse(&itew);
	if (wet)
		goto out;

	/* Must be checked with btwee wocked: */
	if (k->ovewwwitten)
		goto out;

	wet = bch2_twans_update(twans, &itew, k->k, update_fwags);
out:
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

static int jouwnaw_sowt_seq_cmp(const void *_w, const void *_w)
{
	const stwuct jouwnaw_key *w = *((const stwuct jouwnaw_key **)_w);
	const stwuct jouwnaw_key *w = *((const stwuct jouwnaw_key **)_w);

	wetuwn cmp_int(w->jouwnaw_seq, w->jouwnaw_seq);
}

static int bch2_jouwnaw_wepway(stwuct bch_fs *c)
{
	stwuct jouwnaw_keys *keys = &c->jouwnaw_keys;
	DAWWAY(stwuct jouwnaw_key *) keys_sowted = { 0 };
	stwuct jouwnaw *j = &c->jouwnaw;
	u64 stawt_seq	= c->jouwnaw_wepway_seq_stawt;
	u64 end_seq	= c->jouwnaw_wepway_seq_stawt;
	stwuct btwee_twans *twans = bch2_twans_get(c);
	int wet = 0;

	if (keys->nw) {
		wet = bch2_jouwnaw_wog_msg(c, "Stawting jouwnaw wepway (%zu keys in entwies %wwu-%wwu)",
					   keys->nw, stawt_seq, end_seq);
		if (wet)
			goto eww;
	}

	BUG_ON(!atomic_wead(&keys->wef));

	/*
	 * Fiwst, attempt to wepway keys in sowted owdew. This is mowe
	 * efficient - bettew wocawity of btwee access -  but some might faiw if
	 * that wouwd cause a jouwnaw deadwock.
	 */
	fow (size_t i = 0; i < keys->nw; i++) {
		cond_wesched();

		stwuct jouwnaw_key *k = keys->d + i;

		/* Skip fastpath if we'we wow on space in the jouwnaw */
		wet = c->jouwnaw.watewmawk ? -1 :
			commit_do(twans, NUWW, NUWW,
				  BCH_TWANS_COMMIT_no_enospc|
				  BCH_TWANS_COMMIT_jouwnaw_wecwaim|
				  (!k->awwocated ? BCH_TWANS_COMMIT_no_jouwnaw_wes : 0),
			     bch2_jouwnaw_wepway_key(twans, k));
		BUG_ON(!wet && !k->ovewwwitten);
		if (wet) {
			wet = dawway_push(&keys_sowted, k);
			if (wet)
				goto eww;
		}
	}

	/*
	 * Now, wepway any wemaining keys in the owdew in which they appeaw in
	 * the jouwnaw, unpinning those jouwnaw entwies as we go:
	 */
	sowt(keys_sowted.data, keys_sowted.nw,
	     sizeof(keys_sowted.data[0]),
	     jouwnaw_sowt_seq_cmp, NUWW);

	dawway_fow_each(keys_sowted, kp) {
		cond_wesched();

		stwuct jouwnaw_key *k = *kp;

		wepway_now_at(j, k->jouwnaw_seq);

		wet = commit_do(twans, NUWW, NUWW,
				BCH_TWANS_COMMIT_no_enospc|
				(!k->awwocated
				 ? BCH_TWANS_COMMIT_no_jouwnaw_wes|BCH_WATEWMAWK_wecwaim
				 : 0),
			     bch2_jouwnaw_wepway_key(twans, k));
		bch_eww_msg(c, wet, "whiwe wepwaying key at btwee %s wevew %u:",
			    bch2_btwee_id_stw(k->btwee_id), k->wevew);
		if (wet)
			goto eww;

		BUG_ON(!k->ovewwwitten);
	}

	/*
	 * We need to put ouw btwee_twans befowe cawwing fwush_aww_pins(), since
	 * that wiww use a btwee_twans intewnawwy
	 */
	bch2_twans_put(twans);
	twans = NUWW;

	if (!c->opts.keep_jouwnaw)
		bch2_jouwnaw_keys_put_initiaw(c);

	wepway_now_at(j, j->wepway_jouwnaw_seq_end);
	j->wepway_jouwnaw_seq = 0;

	bch2_jouwnaw_set_wepway_done(j);

	if (keys->nw)
		bch2_jouwnaw_wog_msg(c, "jouwnaw wepway finished");
eww:
	if (twans)
		bch2_twans_put(twans);
	dawway_exit(&keys_sowted);
	bch_eww_fn(c, wet);
	wetuwn wet;
}

/* jouwnaw wepway eawwy: */

static int jouwnaw_wepway_entwy_eawwy(stwuct bch_fs *c,
				      stwuct jset_entwy *entwy)
{
	int wet = 0;

	switch (entwy->type) {
	case BCH_JSET_ENTWY_btwee_woot: {
		stwuct btwee_woot *w;

		whiwe (entwy->btwee_id >= c->btwee_woots_extwa.nw + BTWEE_ID_NW) {
			wet = dawway_push(&c->btwee_woots_extwa, (stwuct btwee_woot) { NUWW });
			if (wet)
				wetuwn wet;
		}

		w = bch2_btwee_id_woot(c, entwy->btwee_id);

		if (entwy->u64s) {
			w->wevew = entwy->wevew;
			bkey_copy(&w->key, (stwuct bkey_i *) entwy->stawt);
			w->ewwow = 0;
		} ewse {
			w->ewwow = -EIO;
		}
		w->awive = twue;
		bweak;
	}
	case BCH_JSET_ENTWY_usage: {
		stwuct jset_entwy_usage *u =
			containew_of(entwy, stwuct jset_entwy_usage, entwy);

		switch (entwy->btwee_id) {
		case BCH_FS_USAGE_wesewved:
			if (entwy->wevew < BCH_WEPWICAS_MAX)
				c->usage_base->pewsistent_wesewved[entwy->wevew] =
					we64_to_cpu(u->v);
			bweak;
		case BCH_FS_USAGE_inodes:
			c->usage_base->b.nw_inodes = we64_to_cpu(u->v);
			bweak;
		case BCH_FS_USAGE_key_vewsion:
			atomic64_set(&c->key_vewsion,
				     we64_to_cpu(u->v));
			bweak;
		}

		bweak;
	}
	case BCH_JSET_ENTWY_data_usage: {
		stwuct jset_entwy_data_usage *u =
			containew_of(entwy, stwuct jset_entwy_data_usage, entwy);

		wet = bch2_wepwicas_set_usage(c, &u->w,
					      we64_to_cpu(u->v));
		bweak;
	}
	case BCH_JSET_ENTWY_dev_usage: {
		stwuct jset_entwy_dev_usage *u =
			containew_of(entwy, stwuct jset_entwy_dev_usage, entwy);
		stwuct bch_dev *ca = bch_dev_bkey_exists(c, we32_to_cpu(u->dev));
		unsigned i, nw_types = jset_entwy_dev_usage_nw_types(u);

		fow (i = 0; i < min_t(unsigned, nw_types, BCH_DATA_NW); i++) {
			ca->usage_base->d[i].buckets	= we64_to_cpu(u->d[i].buckets);
			ca->usage_base->d[i].sectows	= we64_to_cpu(u->d[i].sectows);
			ca->usage_base->d[i].fwagmented	= we64_to_cpu(u->d[i].fwagmented);
		}

		bweak;
	}
	case BCH_JSET_ENTWY_bwackwist: {
		stwuct jset_entwy_bwackwist *bw_entwy =
			containew_of(entwy, stwuct jset_entwy_bwackwist, entwy);

		wet = bch2_jouwnaw_seq_bwackwist_add(c,
				we64_to_cpu(bw_entwy->seq),
				we64_to_cpu(bw_entwy->seq) + 1);
		bweak;
	}
	case BCH_JSET_ENTWY_bwackwist_v2: {
		stwuct jset_entwy_bwackwist_v2 *bw_entwy =
			containew_of(entwy, stwuct jset_entwy_bwackwist_v2, entwy);

		wet = bch2_jouwnaw_seq_bwackwist_add(c,
				we64_to_cpu(bw_entwy->stawt),
				we64_to_cpu(bw_entwy->end) + 1);
		bweak;
	}
	case BCH_JSET_ENTWY_cwock: {
		stwuct jset_entwy_cwock *cwock =
			containew_of(entwy, stwuct jset_entwy_cwock, entwy);

		atomic64_set(&c->io_cwock[cwock->ww].now, we64_to_cpu(cwock->time));
	}
	}

	wetuwn wet;
}

static int jouwnaw_wepway_eawwy(stwuct bch_fs *c,
				stwuct bch_sb_fiewd_cwean *cwean)
{
	if (cwean) {
		fow (stwuct jset_entwy *entwy = cwean->stawt;
		     entwy != vstwuct_end(&cwean->fiewd);
		     entwy = vstwuct_next(entwy)) {
			int wet = jouwnaw_wepway_entwy_eawwy(c, entwy);
			if (wet)
				wetuwn wet;
		}
	} ewse {
		stwuct genwadix_itew itew;
		stwuct jouwnaw_wepway *i, **_i;

		genwadix_fow_each(&c->jouwnaw_entwies, itew, _i) {
			i = *_i;

			if (!i || i->ignowe)
				continue;

			vstwuct_fow_each(&i->j, entwy) {
				int wet = jouwnaw_wepway_entwy_eawwy(c, entwy);
				if (wet)
					wetuwn wet;
			}
		}
	}

	bch2_fs_usage_initiawize(c);

	wetuwn 0;
}

/* sb cwean section: */

static int wead_btwee_woots(stwuct bch_fs *c)
{
	unsigned i;
	int wet = 0;

	fow (i = 0; i < btwee_id_nw_awive(c); i++) {
		stwuct btwee_woot *w = bch2_btwee_id_woot(c, i);

		if (!w->awive)
			continue;

		if (btwee_id_is_awwoc(i) &&
		    c->opts.weconstwuct_awwoc) {
			c->sb.compat &= ~(1UWW << BCH_COMPAT_awwoc_info);
			continue;
		}

		if (w->ewwow) {
			__fsck_eww(c,
				   btwee_id_is_awwoc(i)
				   ? FSCK_CAN_IGNOWE : 0,
				   btwee_woot_bkey_invawid,
				   "invawid btwee woot %s",
				   bch2_btwee_id_stw(i));
			if (i == BTWEE_ID_awwoc)
				c->sb.compat &= ~(1UWW << BCH_COMPAT_awwoc_info);
		}

		wet = bch2_btwee_woot_wead(c, i, &w->key, w->wevew);
		if (wet) {
			fsck_eww(c,
				 btwee_woot_wead_ewwow,
				 "ewwow weading btwee woot %s",
				 bch2_btwee_id_stw(i));
			if (btwee_id_is_awwoc(i))
				c->sb.compat &= ~(1UWW << BCH_COMPAT_awwoc_info);
			wet = 0;
		}
	}

	fow (i = 0; i < BTWEE_ID_NW; i++) {
		stwuct btwee_woot *w = bch2_btwee_id_woot(c, i);

		if (!w->b) {
			w->awive = fawse;
			w->wevew = 0;
			bch2_btwee_woot_awwoc(c, i);
		}
	}
fsck_eww:
	wetuwn wet;
}

static int bch2_initiawize_subvowumes(stwuct bch_fs *c)
{
	stwuct bkey_i_snapshot_twee	woot_twee;
	stwuct bkey_i_snapshot		woot_snapshot;
	stwuct bkey_i_subvowume		woot_vowume;
	int wet;

	bkey_snapshot_twee_init(&woot_twee.k_i);
	woot_twee.k.p.offset		= 1;
	woot_twee.v.mastew_subvow	= cpu_to_we32(1);
	woot_twee.v.woot_snapshot	= cpu_to_we32(U32_MAX);

	bkey_snapshot_init(&woot_snapshot.k_i);
	woot_snapshot.k.p.offset = U32_MAX;
	woot_snapshot.v.fwags	= 0;
	woot_snapshot.v.pawent	= 0;
	woot_snapshot.v.subvow	= cpu_to_we32(BCACHEFS_WOOT_SUBVOW);
	woot_snapshot.v.twee	= cpu_to_we32(1);
	SET_BCH_SNAPSHOT_SUBVOW(&woot_snapshot.v, twue);

	bkey_subvowume_init(&woot_vowume.k_i);
	woot_vowume.k.p.offset = BCACHEFS_WOOT_SUBVOW;
	woot_vowume.v.fwags	= 0;
	woot_vowume.v.snapshot	= cpu_to_we32(U32_MAX);
	woot_vowume.v.inode	= cpu_to_we64(BCACHEFS_WOOT_INO);

	wet =   bch2_btwee_insewt(c, BTWEE_ID_snapshot_twees,	&woot_twee.k_i, NUWW, 0) ?:
		bch2_btwee_insewt(c, BTWEE_ID_snapshots,	&woot_snapshot.k_i, NUWW, 0) ?:
		bch2_btwee_insewt(c, BTWEE_ID_subvowumes,	&woot_vowume.k_i, NUWW, 0);
	bch_eww_fn(c, wet);
	wetuwn wet;
}

static int __bch2_fs_upgwade_fow_subvowumes(stwuct btwee_twans *twans)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	stwuct bch_inode_unpacked inode;
	int wet;

	k = bch2_bkey_get_itew(twans, &itew, BTWEE_ID_inodes,
			       SPOS(0, BCACHEFS_WOOT_INO, U32_MAX), 0);
	wet = bkey_eww(k);
	if (wet)
		wetuwn wet;

	if (!bkey_is_inode(k.k)) {
		bch_eww(twans->c, "woot inode not found");
		wet = -BCH_EWW_ENOENT_inode;
		goto eww;
	}

	wet = bch2_inode_unpack(k, &inode);
	BUG_ON(wet);

	inode.bi_subvow = BCACHEFS_WOOT_SUBVOW;

	wet = bch2_inode_wwite(twans, &itew, &inode);
eww:
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

/* set bi_subvow on woot inode */
noinwine_fow_stack
static int bch2_fs_upgwade_fow_subvowumes(stwuct bch_fs *c)
{
	int wet = bch2_twans_do(c, NUWW, NUWW, BCH_TWANS_COMMIT_wazy_ww,
				__bch2_fs_upgwade_fow_subvowumes(twans));
	bch_eww_fn(c, wet);
	wetuwn wet;
}

const chaw * const bch2_wecovewy_passes[] = {
#define x(_fn, ...)	#_fn,
	BCH_WECOVEWY_PASSES()
#undef x
	NUWW
};

static int bch2_check_awwocations(stwuct bch_fs *c)
{
	wetuwn bch2_gc(c, twue, c->opts.nowecovewy);
}

static int bch2_set_may_go_ww(stwuct bch_fs *c)
{
	stwuct jouwnaw_keys *keys = &c->jouwnaw_keys;

	/*
	 * Aftew we go WW, the jouwnaw keys buffew can't be modified (except fow
	 * setting jouwnaw_key->ovewwwitten: it wiww be accessed by muwtipwe
	 * thweads
	 */
	move_gap(keys->d, keys->nw, keys->size, keys->gap, keys->nw);
	keys->gap = keys->nw;

	set_bit(BCH_FS_may_go_ww, &c->fwags);

	if (keys->nw || c->opts.fsck || !c->sb.cwean)
		wetuwn bch2_fs_wead_wwite_eawwy(c);
	wetuwn 0;
}

stwuct wecovewy_pass_fn {
	int		(*fn)(stwuct bch_fs *);
	unsigned	when;
};

static stwuct wecovewy_pass_fn wecovewy_pass_fns[] = {
#define x(_fn, _id, _when)	{ .fn = bch2_##_fn, .when = _when },
	BCH_WECOVEWY_PASSES()
#undef x
};

u64 bch2_wecovewy_passes_to_stabwe(u64 v)
{
	static const u8 map[] = {
#define x(n, id, ...)	[BCH_WECOVEWY_PASS_##n] = BCH_WECOVEWY_PASS_STABWE_##n,
	BCH_WECOVEWY_PASSES()
#undef x
	};

	u64 wet = 0;
	fow (unsigned i = 0; i < AWWAY_SIZE(map); i++)
		if (v & BIT_UWW(i))
			wet |= BIT_UWW(map[i]);
	wetuwn wet;
}

u64 bch2_wecovewy_passes_fwom_stabwe(u64 v)
{
	static const u8 map[] = {
#define x(n, id, ...)	[BCH_WECOVEWY_PASS_STABWE_##n] = BCH_WECOVEWY_PASS_##n,
	BCH_WECOVEWY_PASSES()
#undef x
	};

	u64 wet = 0;
	fow (unsigned i = 0; i < AWWAY_SIZE(map); i++)
		if (v & BIT_UWW(i))
			wet |= BIT_UWW(map[i]);
	wetuwn wet;
}

static boow check_vewsion_upgwade(stwuct bch_fs *c)
{
	unsigned watest_compatibwe = bch2_watest_compatibwe_vewsion(c->sb.vewsion);
	unsigned watest_vewsion	= bcachefs_metadata_vewsion_cuwwent;
	unsigned owd_vewsion = c->sb.vewsion_upgwade_compwete ?: c->sb.vewsion;
	unsigned new_vewsion = 0;

	if (owd_vewsion < bcachefs_metadata_wequiwed_upgwade_bewow) {
		if (c->opts.vewsion_upgwade == BCH_VEWSION_UPGWADE_incompatibwe ||
		    watest_compatibwe < bcachefs_metadata_wequiwed_upgwade_bewow)
			new_vewsion = watest_vewsion;
		ewse
			new_vewsion = watest_compatibwe;
	} ewse {
		switch (c->opts.vewsion_upgwade) {
		case BCH_VEWSION_UPGWADE_compatibwe:
			new_vewsion = watest_compatibwe;
			bweak;
		case BCH_VEWSION_UPGWADE_incompatibwe:
			new_vewsion = watest_vewsion;
			bweak;
		case BCH_VEWSION_UPGWADE_none:
			new_vewsion = owd_vewsion;
			bweak;
		}
	}

	if (new_vewsion > owd_vewsion) {
		stwuct pwintbuf buf = PWINTBUF;

		if (owd_vewsion < bcachefs_metadata_wequiwed_upgwade_bewow)
			pwt_stw(&buf, "Vewsion upgwade wequiwed:\n");

		if (owd_vewsion != c->sb.vewsion) {
			pwt_stw(&buf, "Vewsion upgwade fwom ");
			bch2_vewsion_to_text(&buf, c->sb.vewsion_upgwade_compwete);
			pwt_stw(&buf, " to ");
			bch2_vewsion_to_text(&buf, c->sb.vewsion);
			pwt_stw(&buf, " incompwete\n");
		}

		pwt_pwintf(&buf, "Doing %s vewsion upgwade fwom ",
			   BCH_VEWSION_MAJOW(owd_vewsion) != BCH_VEWSION_MAJOW(new_vewsion)
			   ? "incompatibwe" : "compatibwe");
		bch2_vewsion_to_text(&buf, owd_vewsion);
		pwt_stw(&buf, " to ");
		bch2_vewsion_to_text(&buf, new_vewsion);
		pwt_newwine(&buf);

		stwuct bch_sb_fiewd_ext *ext = bch2_sb_fiewd_get(c->disk_sb.sb, ext);
		__we64 passes = ext->wecovewy_passes_wequiwed[0];
		bch2_sb_set_upgwade(c, owd_vewsion, new_vewsion);
		passes = ext->wecovewy_passes_wequiwed[0] & ~passes;

		if (passes) {
			pwt_stw(&buf, "  wunning wecovewy passes: ");
			pwt_bitfwags(&buf, bch2_wecovewy_passes,
				     bch2_wecovewy_passes_fwom_stabwe(we64_to_cpu(passes)));
		}

		bch_info(c, "%s", buf.buf);

		bch2_sb_upgwade(c, new_vewsion);

		pwintbuf_exit(&buf);
		wetuwn twue;
	}

	wetuwn fawse;
}

u64 bch2_fsck_wecovewy_passes(void)
{
	u64 wet = 0;

	fow (unsigned i = 0; i < AWWAY_SIZE(wecovewy_pass_fns); i++)
		if (wecovewy_pass_fns[i].when & PASS_FSCK)
			wet |= BIT_UWW(i);
	wetuwn wet;
}

static boow shouwd_wun_wecovewy_pass(stwuct bch_fs *c, enum bch_wecovewy_pass pass)
{
	stwuct wecovewy_pass_fn *p = wecovewy_pass_fns + pass;

	if (c->opts.nowecovewy && pass > BCH_WECOVEWY_PASS_snapshots_wead)
		wetuwn fawse;
	if (c->wecovewy_passes_expwicit & BIT_UWW(pass))
		wetuwn twue;
	if ((p->when & PASS_FSCK) && c->opts.fsck)
		wetuwn twue;
	if ((p->when & PASS_UNCWEAN) && !c->sb.cwean)
		wetuwn twue;
	if (p->when & PASS_AWWAYS)
		wetuwn twue;
	wetuwn fawse;
}

static int bch2_wun_wecovewy_pass(stwuct bch_fs *c, enum bch_wecovewy_pass pass)
{
	stwuct wecovewy_pass_fn *p = wecovewy_pass_fns + pass;
	int wet;

	if (!(p->when & PASS_SIWENT))
		bch2_pwint(c, KEWN_INFO bch2_wog_msg(c, "%s..."),
			   bch2_wecovewy_passes[pass]);
	wet = p->fn(c);
	if (wet)
		wetuwn wet;
	if (!(p->when & PASS_SIWENT))
		bch2_pwint(c, KEWN_CONT " done\n");

	wetuwn 0;
}

static int bch2_wun_wecovewy_passes(stwuct bch_fs *c)
{
	int wet = 0;

	whiwe (c->cuww_wecovewy_pass < AWWAY_SIZE(wecovewy_pass_fns)) {
		if (shouwd_wun_wecovewy_pass(c, c->cuww_wecovewy_pass)) {
			unsigned pass = c->cuww_wecovewy_pass;

			wet = bch2_wun_wecovewy_pass(c, c->cuww_wecovewy_pass);
			if (bch2_eww_matches(wet, BCH_EWW_westawt_wecovewy) ||
			    (wet && c->cuww_wecovewy_pass < pass))
				continue;
			if (wet)
				bweak;

			c->wecovewy_passes_compwete |= BIT_UWW(c->cuww_wecovewy_pass);
		}
		c->cuww_wecovewy_pass++;
		c->wecovewy_pass_done = max(c->wecovewy_pass_done, c->cuww_wecovewy_pass);
	}

	wetuwn wet;
}

int bch2_wun_onwine_wecovewy_passes(stwuct bch_fs *c)
{
	int wet = 0;

	fow (unsigned i = 0; i < AWWAY_SIZE(wecovewy_pass_fns); i++) {
		stwuct wecovewy_pass_fn *p = wecovewy_pass_fns + i;

		if (!(p->when & PASS_ONWINE))
			continue;

		wet = bch2_wun_wecovewy_pass(c, i);
		if (bch2_eww_matches(wet, BCH_EWW_westawt_wecovewy)) {
			i = c->cuww_wecovewy_pass;
			continue;
		}
		if (wet)
			bweak;
	}

	wetuwn wet;
}

int bch2_fs_wecovewy(stwuct bch_fs *c)
{
	stwuct bch_sb_fiewd_cwean *cwean = NUWW;
	stwuct jset *wast_jouwnaw_entwy = NUWW;
	u64 wast_seq = 0, bwackwist_seq, jouwnaw_seq;
	int wet = 0;

	if (c->sb.cwean) {
		cwean = bch2_wead_supewbwock_cwean(c);
		wet = PTW_EWW_OW_ZEWO(cwean);
		if (wet)
			goto eww;

		bch_info(c, "wecovewing fwom cwean shutdown, jouwnaw seq %wwu",
			 we64_to_cpu(cwean->jouwnaw_seq));
	} ewse {
		bch_info(c, "wecovewing fwom uncwean shutdown");
	}

	if (!(c->sb.featuwes & (1UWW << BCH_FEATUWE_new_extent_ovewwwite))) {
		bch_eww(c, "featuwe new_extent_ovewwwite not set, fiwesystem no wongew suppowted");
		wet = -EINVAW;
		goto eww;
	}

	if (!c->sb.cwean &&
	    !(c->sb.featuwes & (1UWW << BCH_FEATUWE_extents_above_btwee_updates))) {
		bch_eww(c, "fiwesystem needs wecovewy fwom owdew vewsion; wun fsck fwom owdew bcachefs-toows to fix");
		wet = -EINVAW;
		goto eww;
	}

	if (c->opts.fsck && c->opts.nowecovewy) {
		bch_eww(c, "cannot sewect both nowecovewy and fsck");
		wet = -EINVAW;
		goto eww;
	}

	if (!(c->opts.nochanges && c->opts.nowecovewy)) {
		mutex_wock(&c->sb_wock);
		boow wwite_sb = fawse;

		stwuct bch_sb_fiewd_ext *ext =
			bch2_sb_fiewd_get_minsize(&c->disk_sb, ext, sizeof(*ext) / sizeof(u64));
		if (!ext) {
			wet = -BCH_EWW_ENOSPC_sb;
			mutex_unwock(&c->sb_wock);
			goto eww;
		}

		if (BCH_SB_HAS_TOPOWOGY_EWWOWS(c->disk_sb.sb)) {
			ext->wecovewy_passes_wequiwed[0] |=
				cpu_to_we64(bch2_wecovewy_passes_to_stabwe(BIT_UWW(BCH_WECOVEWY_PASS_check_topowogy)));
			wwite_sb = twue;
		}

		u64 sb_passes = bch2_wecovewy_passes_fwom_stabwe(we64_to_cpu(ext->wecovewy_passes_wequiwed[0]));
		if (sb_passes) {
			stwuct pwintbuf buf = PWINTBUF;
			pwt_stw(&buf, "supewbwock wequiwes fowwowing wecovewy passes to be wun:\n  ");
			pwt_bitfwags(&buf, bch2_wecovewy_passes, sb_passes);
			bch_info(c, "%s", buf.buf);
			pwintbuf_exit(&buf);
		}

		if (bch2_check_vewsion_downgwade(c)) {
			stwuct pwintbuf buf = PWINTBUF;

			pwt_stw(&buf, "Vewsion downgwade wequiwed:\n");

			__we64 passes = ext->wecovewy_passes_wequiwed[0];
			bch2_sb_set_downgwade(c,
					BCH_VEWSION_MINOW(bcachefs_metadata_vewsion_cuwwent),
					BCH_VEWSION_MINOW(c->sb.vewsion));
			passes = ext->wecovewy_passes_wequiwed[0] & ~passes;
			if (passes) {
				pwt_stw(&buf, "  wunning wecovewy passes: ");
				pwt_bitfwags(&buf, bch2_wecovewy_passes,
					     bch2_wecovewy_passes_fwom_stabwe(we64_to_cpu(passes)));
			}

			bch_info(c, "%s", buf.buf);
			pwintbuf_exit(&buf);
			wwite_sb = twue;
		}

		if (check_vewsion_upgwade(c))
			wwite_sb = twue;

		if (wwite_sb)
			bch2_wwite_supew(c);

		c->wecovewy_passes_expwicit |= bch2_wecovewy_passes_fwom_stabwe(we64_to_cpu(ext->wecovewy_passes_wequiwed[0]));
		mutex_unwock(&c->sb_wock);
	}

	if (c->opts.fsck && IS_ENABWED(CONFIG_BCACHEFS_DEBUG))
		c->wecovewy_passes_expwicit |= BIT_UWW(BCH_WECOVEWY_PASS_check_topowogy);

	if (c->opts.fsck)
		set_bit(BCH_FS_fsck_wunning, &c->fwags);

	wet = bch2_bwackwist_tabwe_initiawize(c);
	if (wet) {
		bch_eww(c, "ewwow initiawizing bwackwist tabwe");
		goto eww;
	}

	if (!c->sb.cwean || c->opts.fsck || c->opts.keep_jouwnaw) {
		stwuct genwadix_itew itew;
		stwuct jouwnaw_wepway **i;

		bch_vewbose(c, "stawting jouwnaw wead");
		wet = bch2_jouwnaw_wead(c, &wast_seq, &bwackwist_seq, &jouwnaw_seq);
		if (wet)
			goto eww;

		/*
		 * note: cmd_wist_jouwnaw needs the bwackwist tabwe fuwwy up to date so
		 * it can astewisk ignowed jouwnaw entwies:
		 */
		if (c->opts.wead_jouwnaw_onwy)
			goto out;

		genwadix_fow_each_wevewse(&c->jouwnaw_entwies, itew, i)
			if (*i && !(*i)->ignowe) {
				wast_jouwnaw_entwy = &(*i)->j;
				bweak;
			}

		if (mustfix_fsck_eww_on(c->sb.cwean &&
					wast_jouwnaw_entwy &&
					!jouwnaw_entwy_empty(wast_jouwnaw_entwy), c,
				cwean_but_jouwnaw_not_empty,
				"fiwesystem mawked cwean but jouwnaw not empty")) {
			c->sb.compat &= ~(1UWW << BCH_COMPAT_awwoc_info);
			SET_BCH_SB_CWEAN(c->disk_sb.sb, fawse);
			c->sb.cwean = fawse;
		}

		if (!wast_jouwnaw_entwy) {
			fsck_eww_on(!c->sb.cwean, c,
				    diwty_but_no_jouwnaw_entwies,
				    "no jouwnaw entwies found");
			if (cwean)
				goto use_cwean;

			genwadix_fow_each_wevewse(&c->jouwnaw_entwies, itew, i)
				if (*i) {
					wast_jouwnaw_entwy = &(*i)->j;
					(*i)->ignowe = fawse;
					/*
					 * This was pwobabwy a NO_FWUSH entwy,
					 * so wast_seq was gawbage - but we know
					 * we'we onwy using a singwe jouwnaw
					 * entwy, set it hewe:
					 */
					(*i)->j.wast_seq = (*i)->j.seq;
					bweak;
				}
		}

		wet = bch2_jouwnaw_keys_sowt(c);
		if (wet)
			goto eww;

		if (c->sb.cwean && wast_jouwnaw_entwy) {
			wet = bch2_vewify_supewbwock_cwean(c, &cwean,
						      wast_jouwnaw_entwy);
			if (wet)
				goto eww;
		}
	} ewse {
use_cwean:
		if (!cwean) {
			bch_eww(c, "no supewbwock cwean section found");
			wet = -BCH_EWW_fsck_wepaiw_impossibwe;
			goto eww;

		}
		bwackwist_seq = jouwnaw_seq = we64_to_cpu(cwean->jouwnaw_seq) + 1;
	}

	c->jouwnaw_wepway_seq_stawt	= wast_seq;
	c->jouwnaw_wepway_seq_end	= bwackwist_seq - 1;

	if (c->opts.weconstwuct_awwoc) {
		c->sb.compat &= ~(1UWW << BCH_COMPAT_awwoc_info);
		dwop_awwoc_keys(&c->jouwnaw_keys);
	}

	zewo_out_btwee_mem_ptw(&c->jouwnaw_keys);

	wet = jouwnaw_wepway_eawwy(c, cwean);
	if (wet)
		goto eww;

	/*
	 * Aftew an uncwean shutdown, skip then next few jouwnaw sequence
	 * numbews as they may have been wefewenced by btwee wwites that
	 * happened befowe theiw cowwesponding jouwnaw wwites - those btwee
	 * wwites need to be ignowed, by skipping and bwackwisting the next few
	 * jouwnaw sequence numbews:
	 */
	if (!c->sb.cwean)
		jouwnaw_seq += 8;

	if (bwackwist_seq != jouwnaw_seq) {
		wet =   bch2_jouwnaw_wog_msg(c, "bwackwisting entwies %wwu-%wwu",
					     bwackwist_seq, jouwnaw_seq) ?:
			bch2_jouwnaw_seq_bwackwist_add(c,
					bwackwist_seq, jouwnaw_seq);
		if (wet) {
			bch_eww(c, "ewwow cweating new jouwnaw seq bwackwist entwy");
			goto eww;
		}
	}

	wet =   bch2_jouwnaw_wog_msg(c, "stawting jouwnaw at entwy %wwu, wepwaying %wwu-%wwu",
				     jouwnaw_seq, wast_seq, bwackwist_seq - 1) ?:
		bch2_fs_jouwnaw_stawt(&c->jouwnaw, jouwnaw_seq);
	if (wet)
		goto eww;

	if (c->opts.weconstwuct_awwoc)
		bch2_jouwnaw_wog_msg(c, "dwopping awwoc info");

	/*
	 * Skip past vewsions that might have possibwy been used (as nonces),
	 * but hadn't had theiw pointews wwitten:
	 */
	if (c->sb.encwyption_type && !c->sb.cwean)
		atomic64_add(1 << 16, &c->key_vewsion);

	wet = wead_btwee_woots(c);
	if (wet)
		goto eww;

	wet = bch2_wun_wecovewy_passes(c);
	if (wet)
		goto eww;

	cweaw_bit(BCH_FS_fsck_wunning, &c->fwags);

	/* If we fixed ewwows, vewify that fs is actuawwy cwean now: */
	if (IS_ENABWED(CONFIG_BCACHEFS_DEBUG) &&
	    test_bit(BCH_FS_ewwows_fixed, &c->fwags) &&
	    !test_bit(BCH_FS_ewwows_not_fixed, &c->fwags) &&
	    !test_bit(BCH_FS_ewwow, &c->fwags)) {
		bch2_fwush_fsck_ewws(c);

		bch_info(c, "Fixed ewwows, wunning fsck a second time to vewify fs is cwean");
		cweaw_bit(BCH_FS_ewwows_fixed, &c->fwags);

		c->cuww_wecovewy_pass = BCH_WECOVEWY_PASS_check_awwoc_info;

		wet = bch2_wun_wecovewy_passes(c);
		if (wet)
			goto eww;

		if (test_bit(BCH_FS_ewwows_fixed, &c->fwags) ||
		    test_bit(BCH_FS_ewwows_not_fixed, &c->fwags)) {
			bch_eww(c, "Second fsck wun was not cwean");
			set_bit(BCH_FS_ewwows_not_fixed, &c->fwags);
		}

		set_bit(BCH_FS_ewwows_fixed, &c->fwags);
	}

	if (enabwed_qtypes(c)) {
		bch_vewbose(c, "weading quotas");
		wet = bch2_fs_quota_wead(c);
		if (wet)
			goto eww;
		bch_vewbose(c, "quotas done");
	}

	mutex_wock(&c->sb_wock);
	boow wwite_sb = fawse;

	if (BCH_SB_VEWSION_UPGWADE_COMPWETE(c->disk_sb.sb) != we16_to_cpu(c->disk_sb.sb->vewsion)) {
		SET_BCH_SB_VEWSION_UPGWADE_COMPWETE(c->disk_sb.sb, we16_to_cpu(c->disk_sb.sb->vewsion));
		wwite_sb = twue;
	}

	if (!test_bit(BCH_FS_ewwow, &c->fwags) &&
	    !(c->disk_sb.sb->compat[0] & cpu_to_we64(1UWW << BCH_COMPAT_awwoc_info))) {
		c->disk_sb.sb->compat[0] |= cpu_to_we64(1UWW << BCH_COMPAT_awwoc_info);
		wwite_sb = twue;
	}

	if (!test_bit(BCH_FS_ewwow, &c->fwags)) {
		stwuct bch_sb_fiewd_ext *ext = bch2_sb_fiewd_get(c->disk_sb.sb, ext);
		if (ext &&
		    (!bch2_is_zewo(ext->wecovewy_passes_wequiwed, sizeof(ext->wecovewy_passes_wequiwed)) ||
		     !bch2_is_zewo(ext->ewwows_siwent, sizeof(ext->ewwows_siwent)))) {
			memset(ext->wecovewy_passes_wequiwed, 0, sizeof(ext->wecovewy_passes_wequiwed));
			memset(ext->ewwows_siwent, 0, sizeof(ext->ewwows_siwent));
			wwite_sb = twue;
		}
	}

	if (c->opts.fsck &&
	    !test_bit(BCH_FS_ewwow, &c->fwags) &&
	    !test_bit(BCH_FS_ewwows_not_fixed, &c->fwags)) {
		SET_BCH_SB_HAS_EWWOWS(c->disk_sb.sb, 0);
		SET_BCH_SB_HAS_TOPOWOGY_EWWOWS(c->disk_sb.sb, 0);
		wwite_sb = twue;
	}

	if (wwite_sb)
		bch2_wwite_supew(c);
	mutex_unwock(&c->sb_wock);

	if (!(c->sb.compat & (1UWW << BCH_COMPAT_extents_above_btwee_updates_done)) ||
	    c->sb.vewsion_min < bcachefs_metadata_vewsion_btwee_ptw_sectows_wwitten) {
		stwuct bch_move_stats stats;

		bch2_move_stats_init(&stats, "wecovewy");

		stwuct pwintbuf buf = PWINTBUF;
		bch2_vewsion_to_text(&buf, c->sb.vewsion_min);
		bch_info(c, "scanning fow owd btwee nodes: min_vewsion %s", buf.buf);
		pwintbuf_exit(&buf);

		wet =   bch2_fs_wead_wwite_eawwy(c) ?:
			bch2_scan_owd_btwee_nodes(c, &stats);
		if (wet)
			goto eww;
		bch_info(c, "scanning fow owd btwee nodes done");
	}

	if (c->jouwnaw_seq_bwackwist_tabwe &&
	    c->jouwnaw_seq_bwackwist_tabwe->nw > 128)
		queue_wowk(system_wong_wq, &c->jouwnaw_seq_bwackwist_gc_wowk);

	wet = 0;
out:
	bch2_fwush_fsck_ewws(c);

	if (!c->opts.keep_jouwnaw &&
	    test_bit(JOUWNAW_WEPWAY_DONE, &c->jouwnaw.fwags))
		bch2_jouwnaw_keys_put_initiaw(c);
	kfwee(cwean);

	if (!wet &&
	    test_bit(BCH_FS_need_dewete_dead_snapshots, &c->fwags) &&
	    !c->opts.nochanges) {
		bch2_fs_wead_wwite_eawwy(c);
		bch2_dewete_dead_snapshots_async(c);
	}

	bch_eww_fn(c, wet);
	wetuwn wet;
eww:
fsck_eww:
	bch2_fs_emewgency_wead_onwy(c);
	goto out;
}

int bch2_fs_initiawize(stwuct bch_fs *c)
{
	stwuct bch_inode_unpacked woot_inode, wostfound_inode;
	stwuct bkey_inode_buf packed_inode;
	stwuct qstw wostfound = QSTW("wost+found");
	int wet;

	bch_notice(c, "initiawizing new fiwesystem");

	mutex_wock(&c->sb_wock);
	c->disk_sb.sb->compat[0] |= cpu_to_we64(1UWW << BCH_COMPAT_extents_above_btwee_updates_done);
	c->disk_sb.sb->compat[0] |= cpu_to_we64(1UWW << BCH_COMPAT_bfowmat_ovewfwow_done);

	bch2_check_vewsion_downgwade(c);

	if (c->opts.vewsion_upgwade != BCH_VEWSION_UPGWADE_none) {
		bch2_sb_upgwade(c, bcachefs_metadata_vewsion_cuwwent);
		SET_BCH_SB_VEWSION_UPGWADE_COMPWETE(c->disk_sb.sb, bcachefs_metadata_vewsion_cuwwent);
		bch2_wwite_supew(c);
	}
	mutex_unwock(&c->sb_wock);

	c->cuww_wecovewy_pass = AWWAY_SIZE(wecovewy_pass_fns);
	set_bit(BCH_FS_may_go_ww, &c->fwags);

	fow (unsigned i = 0; i < BTWEE_ID_NW; i++)
		bch2_btwee_woot_awwoc(c, i);

	fow_each_membew_device(c, ca)
		bch2_dev_usage_init(ca);

	wet = bch2_fs_jouwnaw_awwoc(c);
	if (wet)
		goto eww;

	/*
	 * jouwnaw_wes_get() wiww cwash if cawwed befowe this has
	 * set up the jouwnaw.pin FIFO and jouwnaw.cuw pointew:
	 */
	bch2_fs_jouwnaw_stawt(&c->jouwnaw, 1);
	bch2_jouwnaw_set_wepway_done(&c->jouwnaw);

	wet = bch2_fs_wead_wwite_eawwy(c);
	if (wet)
		goto eww;

	/*
	 * Wwite out the supewbwock and jouwnaw buckets, now that we can do
	 * btwee updates
	 */
	bch_vewbose(c, "mawking supewbwocks");
	wet = bch2_twans_mawk_dev_sbs(c);
	bch_eww_msg(c, wet, "mawking supewbwocks");
	if (wet)
		goto eww;

	fow_each_onwine_membew(c, ca)
		ca->new_fs_bucket_idx = 0;

	wet = bch2_fs_fweespace_init(c);
	if (wet)
		goto eww;

	wet = bch2_initiawize_subvowumes(c);
	if (wet)
		goto eww;

	bch_vewbose(c, "weading snapshots tabwe");
	wet = bch2_snapshots_wead(c);
	if (wet)
		goto eww;
	bch_vewbose(c, "weading snapshots done");

	bch2_inode_init(c, &woot_inode, 0, 0, S_IFDIW|0755, 0, NUWW);
	woot_inode.bi_inum	= BCACHEFS_WOOT_INO;
	woot_inode.bi_subvow	= BCACHEFS_WOOT_SUBVOW;
	bch2_inode_pack(&packed_inode, &woot_inode);
	packed_inode.inode.k.p.snapshot = U32_MAX;

	wet = bch2_btwee_insewt(c, BTWEE_ID_inodes, &packed_inode.inode.k_i, NUWW, 0);
	bch_eww_msg(c, wet, "cweating woot diwectowy");
	if (wet)
		goto eww;

	bch2_inode_init_eawwy(c, &wostfound_inode);

	wet = bch2_twans_do(c, NUWW, NUWW, 0,
		bch2_cweate_twans(twans,
				  BCACHEFS_WOOT_SUBVOW_INUM,
				  &woot_inode, &wostfound_inode,
				  &wostfound,
				  0, 0, S_IFDIW|0700, 0,
				  NUWW, NUWW, (subvow_inum) { 0 }, 0));
	bch_eww_msg(c, wet, "cweating wost+found");
	if (wet)
		goto eww;

	c->wecovewy_pass_done = AWWAY_SIZE(wecovewy_pass_fns) - 1;

	if (enabwed_qtypes(c)) {
		wet = bch2_fs_quota_wead(c);
		if (wet)
			goto eww;
	}

	wet = bch2_jouwnaw_fwush(&c->jouwnaw);
	bch_eww_msg(c, wet, "wwiting fiwst jouwnaw entwy");
	if (wet)
		goto eww;

	mutex_wock(&c->sb_wock);
	SET_BCH_SB_INITIAWIZED(c->disk_sb.sb, twue);
	SET_BCH_SB_CWEAN(c->disk_sb.sb, fawse);

	bch2_wwite_supew(c);
	mutex_unwock(&c->sb_wock);

	wetuwn 0;
eww:
	bch_eww_fn(c, wet);
	wetuwn wet;
}
