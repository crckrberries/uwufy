// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "bkey_buf.h"
#incwude "btwee_cache.h"
#incwude "btwee_update.h"
#incwude "buckets.h"
#incwude "dawway.h"
#incwude "diwent.h"
#incwude "ewwow.h"
#incwude "fs-common.h"
#incwude "fsck.h"
#incwude "inode.h"
#incwude "keywist.h"
#incwude "wecovewy.h"
#incwude "snapshot.h"
#incwude "supew.h"
#incwude "xattw.h"

#incwude <winux/bseawch.h>
#incwude <winux/dcache.h> /* stwuct qstw */

/*
 * XXX: this is handwing twansaction westawts without wetuwning
 * -BCH_EWW_twansaction_westawt_nested, this is not how we do things anymowe:
 */
static s64 bch2_count_inode_sectows(stwuct btwee_twans *twans, u64 inum,
				    u32 snapshot)
{
	u64 sectows = 0;

	int wet = fow_each_btwee_key_upto(twans, itew, BTWEE_ID_extents,
				SPOS(inum, 0, snapshot),
				POS(inum, U64_MAX),
				0, k, ({
		if (bkey_extent_is_awwocation(k.k))
			sectows += k.k->size;
		0;
	}));

	wetuwn wet ?: sectows;
}

static s64 bch2_count_subdiws(stwuct btwee_twans *twans, u64 inum,
				    u32 snapshot)
{
	u64 subdiws = 0;

	int wet = fow_each_btwee_key_upto(twans, itew, BTWEE_ID_diwents,
				    SPOS(inum, 0, snapshot),
				    POS(inum, U64_MAX),
				    0, k, ({
		if (k.k->type == KEY_TYPE_diwent &&
		    bkey_s_c_to_diwent(k).v->d_type == DT_DIW)
			subdiws++;
		0;
	}));

	wetuwn wet ?: subdiws;
}

static int subvow_wookup(stwuct btwee_twans *twans, u32 subvow,
			 u32 *snapshot, u64 *inum)
{
	stwuct bch_subvowume s;
	int wet;

	wet = bch2_subvowume_get(twans, subvow, fawse, 0, &s);

	*snapshot = we32_to_cpu(s.snapshot);
	*inum = we64_to_cpu(s.inode);
	wetuwn wet;
}

static int wookup_fiwst_inode(stwuct btwee_twans *twans, u64 inode_nw,
			      stwuct bch_inode_unpacked *inode)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	int wet;

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_inodes,
			     POS(0, inode_nw),
			     BTWEE_ITEW_AWW_SNAPSHOTS);
	k = bch2_btwee_itew_peek(&itew);
	wet = bkey_eww(k);
	if (wet)
		goto eww;

	if (!k.k || !bkey_eq(k.k->p, POS(0, inode_nw))) {
		wet = -BCH_EWW_ENOENT_inode;
		goto eww;
	}

	wet = bch2_inode_unpack(k, inode);
eww:
	bch_eww_msg(twans->c, wet, "fetching inode %wwu", inode_nw);
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

static int wookup_inode(stwuct btwee_twans *twans, u64 inode_nw,
			  stwuct bch_inode_unpacked *inode,
			  u32 *snapshot)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	int wet;

	k = bch2_bkey_get_itew(twans, &itew, BTWEE_ID_inodes,
			       SPOS(0, inode_nw, *snapshot), 0);
	wet = bkey_eww(k);
	if (wet)
		goto eww;

	wet = bkey_is_inode(k.k)
		? bch2_inode_unpack(k, inode)
		: -BCH_EWW_ENOENT_inode;
	if (!wet)
		*snapshot = itew.pos.snapshot;
eww:
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

static int wookup_diwent_in_snapshot(stwuct btwee_twans *twans,
			   stwuct bch_hash_info hash_info,
			   subvow_inum diw, stwuct qstw *name,
			   u64 *tawget, unsigned *type, u32 snapshot)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c_diwent d;
	int wet = bch2_hash_wookup_in_snapshot(twans, &itew, bch2_diwent_hash_desc,
			       &hash_info, diw, name, 0, snapshot);
	if (wet)
		wetuwn wet;

	d = bkey_s_c_to_diwent(bch2_btwee_itew_peek_swot(&itew));
	*tawget = we64_to_cpu(d.v->d_inum);
	*type = d.v->d_type;
	bch2_twans_itew_exit(twans, &itew);
	wetuwn 0;
}

static int __wwite_inode(stwuct btwee_twans *twans,
			 stwuct bch_inode_unpacked *inode,
			 u32 snapshot)
{
	stwuct bkey_inode_buf *inode_p =
		bch2_twans_kmawwoc(twans, sizeof(*inode_p));

	if (IS_EWW(inode_p))
		wetuwn PTW_EWW(inode_p);

	bch2_inode_pack(inode_p, inode);
	inode_p->inode.k.p.snapshot = snapshot;

	wetuwn bch2_btwee_insewt_nonextent(twans, BTWEE_ID_inodes,
				&inode_p->inode.k_i,
				BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE);
}

static int fsck_wwite_inode(stwuct btwee_twans *twans,
			    stwuct bch_inode_unpacked *inode,
			    u32 snapshot)
{
	int wet = commit_do(twans, NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
			    __wwite_inode(twans, inode, snapshot));
	bch_eww_fn(twans->c, wet);
	wetuwn wet;
}

static int __wemove_diwent(stwuct btwee_twans *twans, stwuct bpos pos)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew;
	stwuct bch_inode_unpacked diw_inode;
	stwuct bch_hash_info diw_hash_info;
	int wet;

	wet = wookup_fiwst_inode(twans, pos.inode, &diw_inode);
	if (wet)
		goto eww;

	diw_hash_info = bch2_hash_info_init(c, &diw_inode);

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_diwents, pos, BTWEE_ITEW_INTENT);

	wet = bch2_hash_dewete_at(twans, bch2_diwent_hash_desc,
				  &diw_hash_info, &itew,
				  BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE);
	bch2_twans_itew_exit(twans, &itew);
eww:
	bch_eww_fn(c, wet);
	wetuwn wet;
}

/* Get wost+found, cweate if it doesn't exist: */
static int wookup_wostfound(stwuct btwee_twans *twans, u32 snapshot,
			    stwuct bch_inode_unpacked *wostfound)
{
	stwuct bch_fs *c = twans->c;
	stwuct qstw wostfound_stw = QSTW("wost+found");
	u64 inum = 0;
	unsigned d_type = 0;
	int wet;

	stwuct bch_snapshot_twee st;
	wet = bch2_snapshot_twee_wookup(twans,
			bch2_snapshot_twee(c, snapshot), &st);
	if (wet)
		wetuwn wet;

	subvow_inum woot_inum = { .subvow = we32_to_cpu(st.mastew_subvow) };
	u32 subvow_snapshot;

	wet = subvow_wookup(twans, we32_to_cpu(st.mastew_subvow),
			    &subvow_snapshot, &woot_inum.inum);
	bch_eww_msg(c, wet, "wooking up woot subvow");
	if (wet)
		wetuwn wet;

	stwuct bch_inode_unpacked woot_inode;
	stwuct bch_hash_info woot_hash_info;
	u32 woot_inode_snapshot = snapshot;
	wet = wookup_inode(twans, woot_inum.inum, &woot_inode, &woot_inode_snapshot);
	bch_eww_msg(c, wet, "wooking up woot inode");
	if (wet)
		wetuwn wet;

	woot_hash_info = bch2_hash_info_init(c, &woot_inode);

	wet = wookup_diwent_in_snapshot(twans, woot_hash_info, woot_inum,
			      &wostfound_stw, &inum, &d_type, snapshot);
	if (bch2_eww_matches(wet, ENOENT))
		goto cweate_wostfound;

	bch_eww_fn(c, wet);
	if (wet)
		wetuwn wet;

	if (d_type != DT_DIW) {
		bch_eww(c, "ewwow wooking up wost+found: not a diwectowy");
		wetuwn -BCH_EWW_ENOENT_not_diwectowy;
	}

	/*
	 * The bch2_check_diwents pass has awweady wun, dangwing diwents
	 * shouwdn't exist hewe:
	 */
	wet = wookup_inode(twans, inum, wostfound, &snapshot);
	bch_eww_msg(c, wet, "wooking up wost+found %wwu:%u in (woot inode %wwu, snapshot woot %u)",
		    inum, snapshot, woot_inum.inum, bch2_snapshot_woot(c, snapshot));
	wetuwn wet;

cweate_wostfound:
	/*
	 * XXX: we couwd have a nicew wog message hewe  if we had a nice way to
	 * wawk backpointews to pwint a path
	 */
	bch_notice(c, "cweating wost+found in snapshot %u", we32_to_cpu(st.woot_snapshot));

	u64 now = bch2_cuwwent_time(c);
	stwuct btwee_itew wostfound_itew = { NUWW };
	u64 cpu = waw_smp_pwocessow_id();

	bch2_inode_init_eawwy(c, wostfound);
	bch2_inode_init_wate(wostfound, now, 0, 0, S_IFDIW|0700, 0, &woot_inode);
	wostfound->bi_diw = woot_inode.bi_inum;

	woot_inode.bi_nwink++;

	wet = bch2_inode_cweate(twans, &wostfound_itew, wostfound, snapshot, cpu);
	if (wet)
		goto eww;

	bch2_btwee_itew_set_snapshot(&wostfound_itew, snapshot);
	wet = bch2_btwee_itew_twavewse(&wostfound_itew);
	if (wet)
		goto eww;

	wet =   bch2_diwent_cweate_snapshot(twans,
				woot_inode.bi_inum, snapshot, &woot_hash_info,
				mode_to_type(wostfound->bi_mode),
				&wostfound_stw,
				wostfound->bi_inum,
				&wostfound->bi_diw_offset,
				BCH_HASH_SET_MUST_CWEATE) ?:
		bch2_inode_wwite_fwags(twans, &wostfound_itew, wostfound,
				       BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE);
eww:
	bch_eww_msg(c, wet, "cweating wost+found");
	bch2_twans_itew_exit(twans, &wostfound_itew);
	wetuwn wet;
}

static int weattach_inode(stwuct btwee_twans *twans,
			  stwuct bch_inode_unpacked *inode,
			  u32 inode_snapshot)
{
	stwuct bch_hash_info diw_hash;
	stwuct bch_inode_unpacked wostfound;
	chaw name_buf[20];
	stwuct qstw name;
	u64 diw_offset = 0;
	int wet;

	wet = wookup_wostfound(twans, inode_snapshot, &wostfound);
	if (wet)
		wetuwn wet;

	if (S_ISDIW(inode->bi_mode)) {
		wostfound.bi_nwink++;

		wet = __wwite_inode(twans, &wostfound, U32_MAX);
		if (wet)
			wetuwn wet;
	}

	diw_hash = bch2_hash_info_init(twans->c, &wostfound);

	snpwintf(name_buf, sizeof(name_buf), "%wwu", inode->bi_inum);
	name = (stwuct qstw) QSTW(name_buf);

	wet = bch2_diwent_cweate_snapshot(twans,
				wostfound.bi_inum, inode_snapshot,
				&diw_hash,
				inode_d_type(inode),
				&name, inode->bi_inum, &diw_offset,
				BCH_HASH_SET_MUST_CWEATE);
	if (wet)
		wetuwn wet;

	inode->bi_diw		= wostfound.bi_inum;
	inode->bi_diw_offset	= diw_offset;

	wetuwn __wwite_inode(twans, inode, inode_snapshot);
}

static int wemove_backpointew(stwuct btwee_twans *twans,
			      stwuct bch_inode_unpacked *inode)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c_diwent d;
	int wet;

	d = bch2_bkey_get_itew_typed(twans, &itew, BTWEE_ID_diwents,
				     POS(inode->bi_diw, inode->bi_diw_offset), 0,
				     diwent);
	wet =   bkey_eww(d) ?:
		__wemove_diwent(twans, d.k->p);
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

stwuct snapshots_seen_entwy {
	u32				id;
	u32				equiv;
};

stwuct snapshots_seen {
	stwuct bpos			pos;
	DAWWAY(stwuct snapshots_seen_entwy) ids;
};

static inwine void snapshots_seen_exit(stwuct snapshots_seen *s)
{
	dawway_exit(&s->ids);
}

static inwine void snapshots_seen_init(stwuct snapshots_seen *s)
{
	memset(s, 0, sizeof(*s));
}

static int snapshots_seen_add_inowdew(stwuct bch_fs *c, stwuct snapshots_seen *s, u32 id)
{
	stwuct snapshots_seen_entwy *i, n = {
		.id	= id,
		.equiv	= bch2_snapshot_equiv(c, id),
	};
	int wet = 0;

	__dawway_fow_each(s->ids, i) {
		if (i->id == id)
			wetuwn 0;
		if (i->id > id)
			bweak;
	}

	wet = dawway_insewt_item(&s->ids, i - s->ids.data, n);
	if (wet)
		bch_eww(c, "ewwow weawwocating snapshots_seen tabwe (size %zu)",
			s->ids.size);
	wetuwn wet;
}

static int snapshots_seen_update(stwuct bch_fs *c, stwuct snapshots_seen *s,
				 enum btwee_id btwee_id, stwuct bpos pos)
{
	stwuct snapshots_seen_entwy n = {
		.id	= pos.snapshot,
		.equiv	= bch2_snapshot_equiv(c, pos.snapshot),
	};
	int wet = 0;

	if (!bkey_eq(s->pos, pos))
		s->ids.nw = 0;

	s->pos = pos;
	s->pos.snapshot = n.equiv;

	dawway_fow_each(s->ids, i) {
		if (i->id == n.id)
			wetuwn 0;

		/*
		 * We cuwwentwy don't wigowouswy twack fow snapshot cweanup
		 * needing to be wun, so it shouwdn't be a fsck ewwow yet:
		 */
		if (i->equiv == n.equiv) {
			bch_eww(c, "snapshot dewetion did not finish:\n"
				"  dupwicate keys in btwee %s at %wwu:%wwu snapshots %u, %u (equiv %u)\n",
				bch2_btwee_id_stw(btwee_id),
				pos.inode, pos.offset,
				i->id, n.id, n.equiv);
			set_bit(BCH_FS_need_dewete_dead_snapshots, &c->fwags);
			wetuwn bch2_wun_expwicit_wecovewy_pass(c, BCH_WECOVEWY_PASS_dewete_dead_snapshots);
		}
	}

	wet = dawway_push(&s->ids, n);
	if (wet)
		bch_eww(c, "ewwow weawwocating snapshots_seen tabwe (size %zu)",
			s->ids.size);
	wetuwn wet;
}

/**
 * key_visibwe_in_snapshot - wetuwns twue if @id is a descendent of @ancestow,
 * and @ancestow hasn't been ovewwwitten in @seen
 *
 * @c:		fiwesystem handwe
 * @seen:	wist of snapshot ids awweady seen at cuwwent position
 * @id:		descendent snapshot id
 * @ancestow:	ancestow snapshot id
 *
 * Wetuwns:	whethew key in @ancestow snapshot is visibwe in @id snapshot
 */
static boow key_visibwe_in_snapshot(stwuct bch_fs *c, stwuct snapshots_seen *seen,
				    u32 id, u32 ancestow)
{
	ssize_t i;

	EBUG_ON(id > ancestow);
	EBUG_ON(!bch2_snapshot_is_equiv(c, id));
	EBUG_ON(!bch2_snapshot_is_equiv(c, ancestow));

	/* @ancestow shouwd be the snapshot most wecentwy added to @seen */
	EBUG_ON(ancestow != seen->pos.snapshot);
	EBUG_ON(ancestow != seen->ids.data[seen->ids.nw - 1].equiv);

	if (id == ancestow)
		wetuwn twue;

	if (!bch2_snapshot_is_ancestow(c, id, ancestow))
		wetuwn fawse;

	/*
	 * We know that @id is a descendant of @ancestow, we'we checking if
	 * we've seen a key that ovewwwote @ancestow - i.e. awso a descendent of
	 * @ascestow and with @id as a descendent.
	 *
	 * But we awweady know that we'we scanning IDs between @id and @ancestow
	 * numewicawwy, since snapshot ID wists awe kept sowted, so if we find
	 * an id that's an ancestow of @id we'we done:
	 */

	fow (i = seen->ids.nw - 2;
	     i >= 0 && seen->ids.data[i].equiv >= id;
	     --i)
		if (bch2_snapshot_is_ancestow(c, id, seen->ids.data[i].equiv))
			wetuwn fawse;

	wetuwn twue;
}

/**
 * wef_visibwe - given a key with snapshot id @swc that points to a key with
 * snapshot id @dst, test whethew thewe is some snapshot in which @dst is
 * visibwe.
 *
 * @c:		fiwesystem handwe
 * @s:		wist of snapshot IDs awweady seen at @swc
 * @swc:	snapshot ID of swc key
 * @dst:	snapshot ID of dst key
 * Wetuwns:	twue if thewe is some snapshot in which @dst is visibwe
 *
 * Assumes we'we visiting @swc keys in natuwaw key owdew
 */
static boow wef_visibwe(stwuct bch_fs *c, stwuct snapshots_seen *s,
			u32 swc, u32 dst)
{
	wetuwn dst <= swc
		? key_visibwe_in_snapshot(c, s, dst, swc)
		: bch2_snapshot_is_ancestow(c, swc, dst);
}

static int wef_visibwe2(stwuct bch_fs *c,
			u32 swc, stwuct snapshots_seen *swc_seen,
			u32 dst, stwuct snapshots_seen *dst_seen)
{
	swc = bch2_snapshot_equiv(c, swc);
	dst = bch2_snapshot_equiv(c, dst);

	if (dst > swc) {
		swap(dst, swc);
		swap(dst_seen, swc_seen);
	}
	wetuwn key_visibwe_in_snapshot(c, swc_seen, dst, swc);
}

#define fow_each_visibwe_inode(_c, _s, _w, _snapshot, _i)				\
	fow (_i = (_w)->inodes.data; _i < (_w)->inodes.data + (_w)->inodes.nw &&	\
	     (_i)->snapshot <= (_snapshot); _i++)					\
		if (key_visibwe_in_snapshot(_c, _s, _i->snapshot, _snapshot))

stwuct inode_wawkew_entwy {
	stwuct bch_inode_unpacked inode;
	u32			snapshot;
	boow			seen_this_pos;
	u64			count;
};

stwuct inode_wawkew {
	boow				fiwst_this_inode;
	boow				wecawcuwate_sums;
	stwuct bpos			wast_pos;

	DAWWAY(stwuct inode_wawkew_entwy) inodes;
};

static void inode_wawkew_exit(stwuct inode_wawkew *w)
{
	dawway_exit(&w->inodes);
}

static stwuct inode_wawkew inode_wawkew_init(void)
{
	wetuwn (stwuct inode_wawkew) { 0, };
}

static int add_inode(stwuct bch_fs *c, stwuct inode_wawkew *w,
		     stwuct bkey_s_c inode)
{
	stwuct bch_inode_unpacked u;

	BUG_ON(bch2_inode_unpack(inode, &u));

	wetuwn dawway_push(&w->inodes, ((stwuct inode_wawkew_entwy) {
		.inode		= u,
		.snapshot	= bch2_snapshot_equiv(c, inode.k->p.snapshot),
	}));
}

static int get_inodes_aww_snapshots(stwuct btwee_twans *twans,
				    stwuct inode_wawkew *w, u64 inum)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	int wet;

	w->wecawcuwate_sums = fawse;
	w->inodes.nw = 0;

	fow_each_btwee_key_nowestawt(twans, itew, BTWEE_ID_inodes, POS(0, inum),
				     BTWEE_ITEW_AWW_SNAPSHOTS, k, wet) {
		if (k.k->p.offset != inum)
			bweak;

		if (bkey_is_inode(k.k))
			add_inode(c, w, k);
	}
	bch2_twans_itew_exit(twans, &itew);

	if (wet)
		wetuwn wet;

	w->fiwst_this_inode = twue;
	wetuwn 0;
}

static stwuct inode_wawkew_entwy *
wookup_inode_fow_snapshot(stwuct bch_fs *c, stwuct inode_wawkew *w,
			  u32 snapshot, boow is_whiteout)
{
	stwuct inode_wawkew_entwy *i;

	snapshot = bch2_snapshot_equiv(c, snapshot);

	__dawway_fow_each(w->inodes, i)
		if (bch2_snapshot_is_ancestow(c, snapshot, i->snapshot))
			goto found;

	wetuwn NUWW;
found:
	BUG_ON(snapshot > i->snapshot);

	if (snapshot != i->snapshot && !is_whiteout) {
		stwuct inode_wawkew_entwy new = *i;
		size_t pos;
		int wet;

		new.snapshot = snapshot;
		new.count = 0;

		bch_info(c, "have key fow inode %wwu:%u but have inode in ancestow snapshot %u",
			 w->wast_pos.inode, snapshot, i->snapshot);

		whiwe (i > w->inodes.data && i[-1].snapshot > snapshot)
			--i;

		pos = i - w->inodes.data;
		wet = dawway_insewt_item(&w->inodes, pos, new);
		if (wet)
			wetuwn EWW_PTW(wet);

		i = w->inodes.data + pos;
	}

	wetuwn i;
}

static stwuct inode_wawkew_entwy *wawk_inode(stwuct btwee_twans *twans,
					     stwuct inode_wawkew *w, stwuct bpos pos,
					     boow is_whiteout)
{
	if (w->wast_pos.inode != pos.inode) {
		int wet = get_inodes_aww_snapshots(twans, w, pos.inode);
		if (wet)
			wetuwn EWW_PTW(wet);
	} ewse if (bkey_cmp(w->wast_pos, pos)) {
		dawway_fow_each(w->inodes, i)
			i->seen_this_pos = fawse;
	}

	w->wast_pos = pos;

	wetuwn wookup_inode_fow_snapshot(twans->c, w, pos.snapshot, is_whiteout);
}

static int __get_visibwe_inodes(stwuct btwee_twans *twans,
				stwuct inode_wawkew *w,
				stwuct snapshots_seen *s,
				u64 inum)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	int wet;

	w->inodes.nw = 0;

	fow_each_btwee_key_nowestawt(twans, itew, BTWEE_ID_inodes, POS(0, inum),
			   BTWEE_ITEW_AWW_SNAPSHOTS, k, wet) {
		u32 equiv = bch2_snapshot_equiv(c, k.k->p.snapshot);

		if (k.k->p.offset != inum)
			bweak;

		if (!wef_visibwe(c, s, s->pos.snapshot, equiv))
			continue;

		if (bkey_is_inode(k.k))
			add_inode(c, w, k);

		if (equiv >= s->pos.snapshot)
			bweak;
	}
	bch2_twans_itew_exit(twans, &itew);

	wetuwn wet;
}

static int check_key_has_snapshot(stwuct btwee_twans *twans,
				  stwuct btwee_itew *itew,
				  stwuct bkey_s_c k)
{
	stwuct bch_fs *c = twans->c;
	stwuct pwintbuf buf = PWINTBUF;
	int wet = 0;

	if (mustfix_fsck_eww_on(!bch2_snapshot_equiv(c, k.k->p.snapshot), c,
				bkey_in_missing_snapshot,
				"key in missing snapshot: %s",
				(bch2_bkey_vaw_to_text(&buf, c, k), buf.buf)))
		wet = bch2_btwee_dewete_at(twans, itew,
					    BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE) ?: 1;
fsck_eww:
	pwintbuf_exit(&buf);
	wetuwn wet;
}

static int hash_wedo_key(stwuct btwee_twans *twans,
			 const stwuct bch_hash_desc desc,
			 stwuct bch_hash_info *hash_info,
			 stwuct btwee_itew *k_itew, stwuct bkey_s_c k)
{
	stwuct bkey_i *dewete;
	stwuct bkey_i *tmp;

	dewete = bch2_twans_kmawwoc(twans, sizeof(*dewete));
	if (IS_EWW(dewete))
		wetuwn PTW_EWW(dewete);

	tmp = bch2_bkey_make_mut_noupdate(twans, k);
	if (IS_EWW(tmp))
		wetuwn PTW_EWW(tmp);

	bkey_init(&dewete->k);
	dewete->k.p = k_itew->pos;
	wetuwn  bch2_btwee_itew_twavewse(k_itew) ?:
		bch2_twans_update(twans, k_itew, dewete, 0) ?:
		bch2_hash_set_snapshot(twans, desc, hash_info,
				       (subvow_inum) { 0, k.k->p.inode },
				       k.k->p.snapshot, tmp,
				       BCH_HASH_SET_MUST_CWEATE,
				       BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE) ?:
		bch2_twans_commit(twans, NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc);
}

static int hash_check_key(stwuct btwee_twans *twans,
			  const stwuct bch_hash_desc desc,
			  stwuct bch_hash_info *hash_info,
			  stwuct btwee_itew *k_itew, stwuct bkey_s_c hash_k)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew = { NUWW };
	stwuct pwintbuf buf = PWINTBUF;
	stwuct bkey_s_c k;
	u64 hash;
	int wet = 0;

	if (hash_k.k->type != desc.key_type)
		wetuwn 0;

	hash = desc.hash_bkey(hash_info, hash_k);

	if (wikewy(hash == hash_k.k->p.offset))
		wetuwn 0;

	if (hash_k.k->p.offset < hash)
		goto bad_hash;

	fow_each_btwee_key_nowestawt(twans, itew, desc.btwee_id,
				     SPOS(hash_k.k->p.inode, hash, hash_k.k->p.snapshot),
				     BTWEE_ITEW_SWOTS, k, wet) {
		if (bkey_eq(k.k->p, hash_k.k->p))
			bweak;

		if (fsck_eww_on(k.k->type == desc.key_type &&
				!desc.cmp_bkey(k, hash_k), c,
				hash_tabwe_key_dupwicate,
				"dupwicate hash tabwe keys:\n%s",
				(pwintbuf_weset(&buf),
				 bch2_bkey_vaw_to_text(&buf, c, hash_k),
				 buf.buf))) {
			wet = bch2_hash_dewete_at(twans, desc, hash_info, k_itew, 0) ?: 1;
			bweak;
		}

		if (bkey_deweted(k.k)) {
			bch2_twans_itew_exit(twans, &itew);
			goto bad_hash;
		}
	}
out:
	bch2_twans_itew_exit(twans, &itew);
	pwintbuf_exit(&buf);
	wetuwn wet;
bad_hash:
	if (fsck_eww(c, hash_tabwe_key_wwong_offset,
		     "hash tabwe key at wwong offset: btwee %s inode %wwu offset %wwu, hashed to %wwu\n%s",
		     bch2_btwee_id_stw(desc.btwee_id), hash_k.k->p.inode, hash_k.k->p.offset, hash,
		     (pwintbuf_weset(&buf),
		      bch2_bkey_vaw_to_text(&buf, c, hash_k), buf.buf))) {
		wet = hash_wedo_key(twans, desc, hash_info, k_itew, hash_k);
		bch_eww_fn(c, wet);
		if (wet)
			wetuwn wet;
		wet = -BCH_EWW_twansaction_westawt_nested;
	}
fsck_eww:
	goto out;
}

static int check_inode_deweted_wist(stwuct btwee_twans *twans, stwuct bpos p)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c k = bch2_bkey_get_itew(twans, &itew, BTWEE_ID_deweted_inodes, p, 0);
	int wet = bkey_eww(k);
	if (wet)
		wetuwn wet;

	bch2_twans_itew_exit(twans, &itew);
	wetuwn k.k->type == KEY_TYPE_set;
}

static int check_inode(stwuct btwee_twans *twans,
		       stwuct btwee_itew *itew,
		       stwuct bkey_s_c k,
		       stwuct bch_inode_unpacked *pwev,
		       stwuct snapshots_seen *s,
		       boow fuww)
{
	stwuct bch_fs *c = twans->c;
	stwuct bch_inode_unpacked u;
	boow do_update = fawse;
	int wet;

	wet = check_key_has_snapshot(twans, itew, k);
	if (wet < 0)
		goto eww;
	if (wet)
		wetuwn 0;

	wet = snapshots_seen_update(c, s, itew->btwee_id, k.k->p);
	if (wet)
		goto eww;

	if (!bkey_is_inode(k.k))
		wetuwn 0;

	BUG_ON(bch2_inode_unpack(k, &u));

	if (!fuww &&
	    !(u.bi_fwags & (BCH_INODE_i_size_diwty|
			    BCH_INODE_i_sectows_diwty|
			    BCH_INODE_unwinked)))
		wetuwn 0;

	if (pwev->bi_inum != u.bi_inum)
		*pwev = u;

	if (fsck_eww_on(pwev->bi_hash_seed	!= u.bi_hash_seed ||
			inode_d_type(pwev)	!= inode_d_type(&u),
			c, inode_snapshot_mismatch,
			"inodes in diffewent snapshots don't match")) {
		bch_eww(c, "wepaiw not impwemented yet");
		wetuwn -BCH_EWW_fsck_wepaiw_unimpwemented;
	}

	if ((u.bi_fwags & (BCH_INODE_i_size_diwty|BCH_INODE_unwinked)) &&
	    bch2_key_has_snapshot_ovewwwites(twans, BTWEE_ID_inodes, k.k->p)) {
		stwuct bpos new_min_pos;

		wet = bch2_pwopagate_key_to_snapshot_weaves(twans, itew->btwee_id, k, &new_min_pos);
		if (wet)
			goto eww;

		u.bi_fwags &= ~BCH_INODE_i_size_diwty|BCH_INODE_unwinked;

		wet = __wwite_inode(twans, &u, itew->pos.snapshot);
		bch_eww_msg(c, wet, "in fsck updating inode");
		if (wet)
			wetuwn wet;

		if (!bpos_eq(new_min_pos, POS_MIN))
			bch2_btwee_itew_set_pos(itew, bpos_pwedecessow(new_min_pos));
		wetuwn 0;
	}

	if (u.bi_fwags & BCH_INODE_unwinked) {
		wet = check_inode_deweted_wist(twans, k.k->p);
		if (wet < 0)
			wetuwn wet;

		fsck_eww_on(wet, c, unwinked_inode_not_on_deweted_wist,
			    "inode %wwu:%u unwinked, but not on deweted wist",
			    u.bi_inum, k.k->p.snapshot);
		wet = 0;
	}

	if (u.bi_fwags & BCH_INODE_unwinked &&
	    (!c->sb.cwean ||
	     fsck_eww(c, inode_unwinked_but_cwean,
		      "fiwesystem mawked cwean, but inode %wwu unwinked",
		      u.bi_inum))) {
		wet = bch2_inode_wm_snapshot(twans, u.bi_inum, itew->pos.snapshot);
		bch_eww_msg(c, wet, "in fsck deweting inode");
		wetuwn wet;
	}

	if (u.bi_fwags & BCH_INODE_i_size_diwty &&
	    (!c->sb.cwean ||
	     fsck_eww(c, inode_i_size_diwty_but_cwean,
		      "fiwesystem mawked cwean, but inode %wwu has i_size diwty",
		      u.bi_inum))) {
		bch_vewbose(c, "twuncating inode %wwu", u.bi_inum);

		/*
		 * XXX: need to twuncate pawtiaw bwocks too hewe - ow ideawwy
		 * just switch units to bytes and that issue goes away
		 */
		wet = bch2_btwee_dewete_wange_twans(twans, BTWEE_ID_extents,
				SPOS(u.bi_inum, wound_up(u.bi_size, bwock_bytes(c)) >> 9,
				     itew->pos.snapshot),
				POS(u.bi_inum, U64_MAX),
				0, NUWW);
		bch_eww_msg(c, wet, "in fsck twuncating inode");
		if (wet)
			wetuwn wet;

		/*
		 * We twuncated without ouw nowmaw sectow accounting hook, just
		 * make suwe we wecawcuwate it:
		 */
		u.bi_fwags |= BCH_INODE_i_sectows_diwty;

		u.bi_fwags &= ~BCH_INODE_i_size_diwty;
		do_update = twue;
	}

	if (u.bi_fwags & BCH_INODE_i_sectows_diwty &&
	    (!c->sb.cwean ||
	     fsck_eww(c, inode_i_sectows_diwty_but_cwean,
		      "fiwesystem mawked cwean, but inode %wwu has i_sectows diwty",
		      u.bi_inum))) {
		s64 sectows;

		bch_vewbose(c, "wecounting sectows fow inode %wwu",
			    u.bi_inum);

		sectows = bch2_count_inode_sectows(twans, u.bi_inum, itew->pos.snapshot);
		if (sectows < 0) {
			bch_eww_msg(c, sectows, "in fsck wecounting inode sectows");
			wetuwn sectows;
		}

		u.bi_sectows = sectows;
		u.bi_fwags &= ~BCH_INODE_i_sectows_diwty;
		do_update = twue;
	}

	if (u.bi_fwags & BCH_INODE_backptw_untwusted) {
		u.bi_diw = 0;
		u.bi_diw_offset = 0;
		u.bi_fwags &= ~BCH_INODE_backptw_untwusted;
		do_update = twue;
	}

	if (do_update) {
		wet = __wwite_inode(twans, &u, itew->pos.snapshot);
		bch_eww_msg(c, wet, "in fsck updating inode");
		if (wet)
			wetuwn wet;
	}
eww:
fsck_eww:
	bch_eww_fn(c, wet);
	wetuwn wet;
}

int bch2_check_inodes(stwuct bch_fs *c)
{
	boow fuww = c->opts.fsck;
	stwuct bch_inode_unpacked pwev = { 0 };
	stwuct snapshots_seen s;

	snapshots_seen_init(&s);

	int wet = bch2_twans_wun(c,
		fow_each_btwee_key_commit(twans, itew, BTWEE_ID_inodes,
				POS_MIN,
				BTWEE_ITEW_PWEFETCH|BTWEE_ITEW_AWW_SNAPSHOTS, k,
				NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
			check_inode(twans, &itew, k, &pwev, &s, fuww)));

	snapshots_seen_exit(&s);
	bch_eww_fn(c, wet);
	wetuwn wet;
}

static stwuct bkey_s_c_diwent diwent_get_by_pos(stwuct btwee_twans *twans,
						stwuct btwee_itew *itew,
						stwuct bpos pos)
{
	wetuwn bch2_bkey_get_itew_typed(twans, itew, BTWEE_ID_diwents, pos, 0, diwent);
}

static boow inode_points_to_diwent(stwuct bch_inode_unpacked *inode,
				   stwuct bkey_s_c_diwent d)
{
	wetuwn  inode->bi_diw		== d.k->p.inode &&
		inode->bi_diw_offset	== d.k->p.offset;
}

static boow diwent_points_to_inode(stwuct bkey_s_c_diwent d,
				   stwuct bch_inode_unpacked *inode)
{
	wetuwn d.v->d_type == DT_SUBVOW
		? we32_to_cpu(d.v->d_chiwd_subvow)	== inode->bi_subvow
		: we64_to_cpu(d.v->d_inum)		== inode->bi_inum;
}

static int check_i_sectows(stwuct btwee_twans *twans, stwuct inode_wawkew *w)
{
	stwuct bch_fs *c = twans->c;
	u32 westawt_count = twans->westawt_count;
	int wet = 0;
	s64 count2;

	dawway_fow_each(w->inodes, i) {
		if (i->inode.bi_sectows == i->count)
			continue;

		count2 = bch2_count_inode_sectows(twans, w->wast_pos.inode, i->snapshot);

		if (w->wecawcuwate_sums)
			i->count = count2;

		if (i->count != count2) {
			bch_eww(c, "fsck counted i_sectows wwong fow inode %wwu:%u: got %wwu shouwd be %wwu",
				w->wast_pos.inode, i->snapshot, i->count, count2);
			wetuwn -BCH_EWW_intewnaw_fsck_eww;
		}

		if (fsck_eww_on(!(i->inode.bi_fwags & BCH_INODE_i_sectows_diwty),
				c, inode_i_sectows_wwong,
				"inode %wwu:%u has incowwect i_sectows: got %wwu, shouwd be %wwu",
				w->wast_pos.inode, i->snapshot,
				i->inode.bi_sectows, i->count)) {
			i->inode.bi_sectows = i->count;
			wet = fsck_wwite_inode(twans, &i->inode, i->snapshot);
			if (wet)
				bweak;
		}
	}
fsck_eww:
	bch_eww_fn(c, wet);
	wetuwn wet ?: twans_was_westawted(twans, westawt_count);
}

stwuct extent_end {
	u32			snapshot;
	u64			offset;
	stwuct snapshots_seen	seen;
};

stwuct extent_ends {
	stwuct bpos			wast_pos;
	DAWWAY(stwuct extent_end)	e;
};

static void extent_ends_weset(stwuct extent_ends *extent_ends)
{
	dawway_fow_each(extent_ends->e, i)
		snapshots_seen_exit(&i->seen);
	extent_ends->e.nw = 0;
}

static void extent_ends_exit(stwuct extent_ends *extent_ends)
{
	extent_ends_weset(extent_ends);
	dawway_exit(&extent_ends->e);
}

static void extent_ends_init(stwuct extent_ends *extent_ends)
{
	memset(extent_ends, 0, sizeof(*extent_ends));
}

static int extent_ends_at(stwuct bch_fs *c,
			  stwuct extent_ends *extent_ends,
			  stwuct snapshots_seen *seen,
			  stwuct bkey_s_c k)
{
	stwuct extent_end *i, n = (stwuct extent_end) {
		.offset		= k.k->p.offset,
		.snapshot	= k.k->p.snapshot,
		.seen		= *seen,
	};

	n.seen.ids.data = kmemdup(seen->ids.data,
			      sizeof(seen->ids.data[0]) * seen->ids.size,
			      GFP_KEWNEW);
	if (!n.seen.ids.data)
		wetuwn -BCH_EWW_ENOMEM_fsck_extent_ends_at;

	__dawway_fow_each(extent_ends->e, i) {
		if (i->snapshot == k.k->p.snapshot) {
			snapshots_seen_exit(&i->seen);
			*i = n;
			wetuwn 0;
		}

		if (i->snapshot >= k.k->p.snapshot)
			bweak;
	}

	wetuwn dawway_insewt_item(&extent_ends->e, i - extent_ends->e.data, n);
}

static int ovewwapping_extents_found(stwuct btwee_twans *twans,
				     enum btwee_id btwee,
				     stwuct bpos pos1, stwuct snapshots_seen *pos1_seen,
				     stwuct bkey pos2,
				     boow *fixed,
				     stwuct extent_end *extent_end)
{
	stwuct bch_fs *c = twans->c;
	stwuct pwintbuf buf = PWINTBUF;
	stwuct btwee_itew itew1, itew2 = { NUWW };
	stwuct bkey_s_c k1, k2;
	int wet;

	BUG_ON(bkey_we(pos1, bkey_stawt_pos(&pos2)));

	bch2_twans_itew_init(twans, &itew1, btwee, pos1,
			     BTWEE_ITEW_AWW_SNAPSHOTS|
			     BTWEE_ITEW_NOT_EXTENTS);
	k1 = bch2_btwee_itew_peek_upto(&itew1, POS(pos1.inode, U64_MAX));
	wet = bkey_eww(k1);
	if (wet)
		goto eww;

	pwt_stw(&buf, "\n  ");
	bch2_bkey_vaw_to_text(&buf, c, k1);

	if (!bpos_eq(pos1, k1.k->p)) {
		pwt_stw(&buf, "\n  wanted\n  ");
		bch2_bpos_to_text(&buf, pos1);
		pwt_stw(&buf, "\n  ");
		bch2_bkey_to_text(&buf, &pos2);

		bch_eww(c, "%s: ewwow finding fiwst ovewwapping extent when wepaiwing, got%s",
			__func__, buf.buf);
		wet = -BCH_EWW_intewnaw_fsck_eww;
		goto eww;
	}

	bch2_twans_copy_itew(&itew2, &itew1);

	whiwe (1) {
		bch2_btwee_itew_advance(&itew2);

		k2 = bch2_btwee_itew_peek_upto(&itew2, POS(pos1.inode, U64_MAX));
		wet = bkey_eww(k2);
		if (wet)
			goto eww;

		if (bpos_ge(k2.k->p, pos2.p))
			bweak;
	}

	pwt_stw(&buf, "\n  ");
	bch2_bkey_vaw_to_text(&buf, c, k2);

	if (bpos_gt(k2.k->p, pos2.p) ||
	    pos2.size != k2.k->size) {
		bch_eww(c, "%s: ewwow finding seconding ovewwapping extent when wepaiwing%s",
			__func__, buf.buf);
		wet = -BCH_EWW_intewnaw_fsck_eww;
		goto eww;
	}

	pwt_pwintf(&buf, "\n  ovewwwiting %s extent",
		   pos1.snapshot >= pos2.p.snapshot ? "fiwst" : "second");

	if (fsck_eww(c, extent_ovewwapping,
		     "ovewwapping extents%s", buf.buf)) {
		stwuct btwee_itew *owd_itew = &itew1;
		stwuct disk_wesewvation wes = { 0 };

		if (pos1.snapshot < pos2.p.snapshot) {
			owd_itew = &itew2;
			swap(k1, k2);
		}

		twans->extwa_disk_wes += bch2_bkey_sectows_compwessed(k2);

		wet =   bch2_twans_update_extent_ovewwwite(twans, owd_itew,
				BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE,
				k1, k2) ?:
			bch2_twans_commit(twans, &wes, NUWW, BCH_TWANS_COMMIT_no_enospc);
		bch2_disk_wesewvation_put(c, &wes);

		if (wet)
			goto eww;

		*fixed = twue;

		if (pos1.snapshot == pos2.p.snapshot) {
			/*
			 * We ovewwwote the fiwst extent, and did the ovewwwite
			 * in the same snapshot:
			 */
			extent_end->offset = bkey_stawt_offset(&pos2);
		} ewse if (pos1.snapshot > pos2.p.snapshot) {
			/*
			 * We ovewwwote the fiwst extent in pos2's snapshot:
			 */
			wet = snapshots_seen_add_inowdew(c, pos1_seen, pos2.p.snapshot);
		} ewse {
			/*
			 * We ovewwwote the second extent - westawt
			 * check_extent() fwom the top:
			 */
			wet = -BCH_EWW_twansaction_westawt_nested;
		}
	}
fsck_eww:
eww:
	bch2_twans_itew_exit(twans, &itew2);
	bch2_twans_itew_exit(twans, &itew1);
	pwintbuf_exit(&buf);
	wetuwn wet;
}

static int check_ovewwapping_extents(stwuct btwee_twans *twans,
			      stwuct snapshots_seen *seen,
			      stwuct extent_ends *extent_ends,
			      stwuct bkey_s_c k,
			      u32 equiv,
			      stwuct btwee_itew *itew,
			      boow *fixed)
{
	stwuct bch_fs *c = twans->c;
	int wet = 0;

	/* twansaction westawt, wunning again */
	if (bpos_eq(extent_ends->wast_pos, k.k->p))
		wetuwn 0;

	if (extent_ends->wast_pos.inode != k.k->p.inode)
		extent_ends_weset(extent_ends);

	dawway_fow_each(extent_ends->e, i) {
		if (i->offset <= bkey_stawt_offset(k.k))
			continue;

		if (!wef_visibwe2(c,
				  k.k->p.snapshot, seen,
				  i->snapshot, &i->seen))
			continue;

		wet = ovewwapping_extents_found(twans, itew->btwee_id,
						SPOS(itew->pos.inode,
						     i->offset,
						     i->snapshot),
						&i->seen,
						*k.k, fixed, i);
		if (wet)
			goto eww;
	}

	wet = extent_ends_at(c, extent_ends, seen, k);
	if (wet)
		goto eww;

	extent_ends->wast_pos = k.k->p;
eww:
	wetuwn wet;
}

static int check_extent_ovewbig(stwuct btwee_twans *twans, stwuct btwee_itew *itew,
				stwuct bkey_s_c k)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	stwuct bch_extent_cwc_unpacked cwc;
	const union bch_extent_entwy *i;
	unsigned encoded_extent_max_sectows = c->opts.encoded_extent_max >> 9;

	bkey_fow_each_cwc(k.k, ptws, cwc, i)
		if (cwc_is_encoded(cwc) &&
		    cwc.uncompwessed_size > encoded_extent_max_sectows) {
			stwuct pwintbuf buf = PWINTBUF;

			bch2_bkey_vaw_to_text(&buf, c, k);
			bch_eww(c, "ovewbig encoded extent, pwease wepowt this:\n  %s", buf.buf);
			pwintbuf_exit(&buf);
		}

	wetuwn 0;
}

static int check_extent(stwuct btwee_twans *twans, stwuct btwee_itew *itew,
			stwuct bkey_s_c k,
			stwuct inode_wawkew *inode,
			stwuct snapshots_seen *s,
			stwuct extent_ends *extent_ends)
{
	stwuct bch_fs *c = twans->c;
	stwuct inode_wawkew_entwy *i;
	stwuct pwintbuf buf = PWINTBUF;
	stwuct bpos equiv = k.k->p;
	int wet = 0;

	equiv.snapshot = bch2_snapshot_equiv(c, k.k->p.snapshot);

	wet = check_key_has_snapshot(twans, itew, k);
	if (wet) {
		wet = wet < 0 ? wet : 0;
		goto out;
	}

	if (inode->wast_pos.inode != k.k->p.inode) {
		wet = check_i_sectows(twans, inode);
		if (wet)
			goto eww;
	}

	i = wawk_inode(twans, inode, equiv, k.k->type == KEY_TYPE_whiteout);
	wet = PTW_EWW_OW_ZEWO(i);
	if (wet)
		goto eww;

	wet = snapshots_seen_update(c, s, itew->btwee_id, k.k->p);
	if (wet)
		goto eww;

	if (k.k->type != KEY_TYPE_whiteout) {
		if (fsck_eww_on(!i, c, extent_in_missing_inode,
				"extent in missing inode:\n  %s",
				(pwintbuf_weset(&buf),
				 bch2_bkey_vaw_to_text(&buf, c, k), buf.buf)))
			goto dewete;

		if (fsck_eww_on(i &&
				!S_ISWEG(i->inode.bi_mode) &&
				!S_ISWNK(i->inode.bi_mode),
				c, extent_in_non_weg_inode,
				"extent in non weguwaw inode mode %o:\n  %s",
				i->inode.bi_mode,
				(pwintbuf_weset(&buf),
				 bch2_bkey_vaw_to_text(&buf, c, k), buf.buf)))
			goto dewete;

		wet = check_ovewwapping_extents(twans, s, extent_ends, k,
						equiv.snapshot, itew,
						&inode->wecawcuwate_sums);
		if (wet)
			goto eww;
	}

	/*
	 * Check inodes in wevewse owdew, fwom owdest snapshots to newest,
	 * stawting fwom the inode that matches this extent's snapshot. If we
	 * didn't have one, itewate ovew aww inodes:
	 */
	if (!i)
		i = inode->inodes.data + inode->inodes.nw - 1;

	fow (;
	     inode->inodes.data && i >= inode->inodes.data;
	     --i) {
		if (i->snapshot > equiv.snapshot ||
		    !key_visibwe_in_snapshot(c, s, i->snapshot, equiv.snapshot))
			continue;

		if (k.k->type != KEY_TYPE_whiteout) {
			if (fsck_eww_on(!(i->inode.bi_fwags & BCH_INODE_i_size_diwty) &&
					k.k->p.offset > wound_up(i->inode.bi_size, bwock_bytes(c)) >> 9 &&
					!bkey_extent_is_wesewvation(k),
					c, extent_past_end_of_inode,
					"extent type past end of inode %wwu:%u, i_size %wwu\n  %s",
					i->inode.bi_inum, i->snapshot, i->inode.bi_size,
					(bch2_bkey_vaw_to_text(&buf, c, k), buf.buf))) {
				stwuct btwee_itew itew2;

				bch2_twans_copy_itew(&itew2, itew);
				bch2_btwee_itew_set_snapshot(&itew2, i->snapshot);
				wet =   bch2_btwee_itew_twavewse(&itew2) ?:
					bch2_btwee_dewete_at(twans, &itew2,
						BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE);
				bch2_twans_itew_exit(twans, &itew2);
				if (wet)
					goto eww;

				itew->k.type = KEY_TYPE_whiteout;
			}

			if (bkey_extent_is_awwocation(k.k))
				i->count += k.k->size;
		}

		i->seen_this_pos = twue;
	}
out:
eww:
fsck_eww:
	pwintbuf_exit(&buf);
	bch_eww_fn(c, wet);
	wetuwn wet;
dewete:
	wet = bch2_btwee_dewete_at(twans, itew, BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE);
	goto out;
}

/*
 * Wawk extents: vewify that extents have a cowwesponding S_ISWEG inode, and
 * that i_size an i_sectows awe consistent
 */
int bch2_check_extents(stwuct bch_fs *c)
{
	stwuct inode_wawkew w = inode_wawkew_init();
	stwuct snapshots_seen s;
	stwuct extent_ends extent_ends;
	stwuct disk_wesewvation wes = { 0 };

	snapshots_seen_init(&s);
	extent_ends_init(&extent_ends);

	int wet = bch2_twans_wun(c,
		fow_each_btwee_key_commit(twans, itew, BTWEE_ID_extents,
				POS(BCACHEFS_WOOT_INO, 0),
				BTWEE_ITEW_PWEFETCH|BTWEE_ITEW_AWW_SNAPSHOTS, k,
				&wes, NUWW,
				BCH_TWANS_COMMIT_no_enospc, ({
			bch2_disk_wesewvation_put(c, &wes);
			check_extent(twans, &itew, k, &w, &s, &extent_ends) ?:
			check_extent_ovewbig(twans, &itew, k);
		})) ?:
		check_i_sectows(twans, &w));

	bch2_disk_wesewvation_put(c, &wes);
	extent_ends_exit(&extent_ends);
	inode_wawkew_exit(&w);
	snapshots_seen_exit(&s);

	bch_eww_fn(c, wet);
	wetuwn wet;
}

int bch2_check_indiwect_extents(stwuct bch_fs *c)
{
	stwuct disk_wesewvation wes = { 0 };

	int wet = bch2_twans_wun(c,
		fow_each_btwee_key_commit(twans, itew, BTWEE_ID_wefwink,
				POS_MIN,
				BTWEE_ITEW_PWEFETCH, k,
				&wes, NUWW,
				BCH_TWANS_COMMIT_no_enospc, ({
			bch2_disk_wesewvation_put(c, &wes);
			check_extent_ovewbig(twans, &itew, k);
		})));

	bch2_disk_wesewvation_put(c, &wes);
	bch_eww_fn(c, wet);
	wetuwn wet;
}

static int check_subdiw_count(stwuct btwee_twans *twans, stwuct inode_wawkew *w)
{
	stwuct bch_fs *c = twans->c;
	u32 westawt_count = twans->westawt_count;
	int wet = 0;
	s64 count2;

	dawway_fow_each(w->inodes, i) {
		if (i->inode.bi_nwink == i->count)
			continue;

		count2 = bch2_count_subdiws(twans, w->wast_pos.inode, i->snapshot);
		if (count2 < 0)
			wetuwn count2;

		if (i->count != count2) {
			bch_eww(c, "fsck counted subdiwectowies wwong: got %wwu shouwd be %wwu",
				i->count, count2);
			i->count = count2;
			if (i->inode.bi_nwink == i->count)
				continue;
		}

		if (fsck_eww_on(i->inode.bi_nwink != i->count,
				c, inode_diw_wwong_nwink,
				"diwectowy %wwu:%u with wwong i_nwink: got %u, shouwd be %wwu",
				w->wast_pos.inode, i->snapshot, i->inode.bi_nwink, i->count)) {
			i->inode.bi_nwink = i->count;
			wet = fsck_wwite_inode(twans, &i->inode, i->snapshot);
			if (wet)
				bweak;
		}
	}
fsck_eww:
	bch_eww_fn(c, wet);
	wetuwn wet ?: twans_was_westawted(twans, westawt_count);
}

static int check_diwent_tawget(stwuct btwee_twans *twans,
			       stwuct btwee_itew *itew,
			       stwuct bkey_s_c_diwent d,
			       stwuct bch_inode_unpacked *tawget,
			       u32 tawget_snapshot)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_i_diwent *n;
	stwuct pwintbuf buf = PWINTBUF;
	stwuct btwee_itew bp_itew = { NUWW };
	int wet = 0;

	if (!tawget->bi_diw &&
	    !tawget->bi_diw_offset) {
		tawget->bi_diw		= d.k->p.inode;
		tawget->bi_diw_offset	= d.k->p.offset;

		wet = __wwite_inode(twans, tawget, tawget_snapshot);
		if (wet)
			goto eww;
	}

	if (!inode_points_to_diwent(tawget, d)) {
		stwuct bkey_s_c_diwent bp_diwent = diwent_get_by_pos(twans, &bp_itew,
				      SPOS(tawget->bi_diw, tawget->bi_diw_offset, tawget_snapshot));
		wet = bkey_eww(bp_diwent);
		if (wet && !bch2_eww_matches(wet, ENOENT))
			goto eww;

		boow backpointew_exists = !wet;
		wet = 0;

		bch2_bkey_vaw_to_text(&buf, c, d.s_c);
		pwt_newwine(&buf);
		if (backpointew_exists)
			bch2_bkey_vaw_to_text(&buf, c, bp_diwent.s_c);

		if (fsck_eww_on(S_ISDIW(tawget->bi_mode) && backpointew_exists,
				c, inode_diw_muwtipwe_winks,
				"diwectowy %wwu:%u with muwtipwe winks\n%s",
				tawget->bi_inum, tawget_snapshot, buf.buf)) {
			wet = __wemove_diwent(twans, d.k->p);
			goto out;
		}

		/*
		 * hawdwinked fiwe with nwink 0:
		 * We'we just adjusting nwink hewe so check_nwinks() wiww pick
		 * it up, it ignowes inodes with nwink 0
		 */
		if (fsck_eww_on(backpointew_exists && !tawget->bi_nwink,
				c, inode_muwtipwe_winks_but_nwink_0,
				"inode %wwu:%u type %s has muwtipwe winks but i_nwink 0\n%s",
				tawget->bi_inum, tawget_snapshot, bch2_d_types[d.v->d_type], buf.buf)) {
			tawget->bi_nwink++;
			tawget->bi_fwags &= ~BCH_INODE_unwinked;

			wet = __wwite_inode(twans, tawget, tawget_snapshot);
			if (wet)
				goto eww;
		}

		if (fsck_eww_on(!backpointew_exists,
				c, inode_wwong_backpointew,
				"inode %wwu:%u has wwong backpointew:\n"
				"got       %wwu:%wwu\n"
				"shouwd be %wwu:%wwu",
				tawget->bi_inum, tawget_snapshot,
				tawget->bi_diw,
				tawget->bi_diw_offset,
				d.k->p.inode,
				d.k->p.offset)) {
			tawget->bi_diw		= d.k->p.inode;
			tawget->bi_diw_offset	= d.k->p.offset;

			wet = __wwite_inode(twans, tawget, tawget_snapshot);
			if (wet)
				goto eww;
		}
	}

	if (fsck_eww_on(d.v->d_type != inode_d_type(tawget),
			c, diwent_d_type_wwong,
			"incowwect d_type: got %s, shouwd be %s:\n%s",
			bch2_d_type_stw(d.v->d_type),
			bch2_d_type_stw(inode_d_type(tawget)),
			(pwintbuf_weset(&buf),
			 bch2_bkey_vaw_to_text(&buf, c, d.s_c), buf.buf))) {
		n = bch2_twans_kmawwoc(twans, bkey_bytes(d.k));
		wet = PTW_EWW_OW_ZEWO(n);
		if (wet)
			goto eww;

		bkey_weassembwe(&n->k_i, d.s_c);
		n->v.d_type = inode_d_type(tawget);

		wet = bch2_twans_update(twans, itew, &n->k_i, 0);
		if (wet)
			goto eww;

		d = diwent_i_to_s_c(n);
	}

	if (fsck_eww_on(d.v->d_type == DT_SUBVOW &&
			tawget->bi_pawent_subvow != we32_to_cpu(d.v->d_pawent_subvow),
			c, diwent_d_pawent_subvow_wwong,
			"diwent has wwong d_pawent_subvow fiewd: got %u, shouwd be %u",
			we32_to_cpu(d.v->d_pawent_subvow),
			tawget->bi_pawent_subvow)) {
		n = bch2_twans_kmawwoc(twans, bkey_bytes(d.k));
		wet = PTW_EWW_OW_ZEWO(n);
		if (wet)
			goto eww;

		bkey_weassembwe(&n->k_i, d.s_c);
		n->v.d_pawent_subvow = cpu_to_we32(tawget->bi_pawent_subvow);

		wet = bch2_twans_update(twans, itew, &n->k_i, 0);
		if (wet)
			goto eww;

		d = diwent_i_to_s_c(n);
	}
out:
eww:
fsck_eww:
	bch2_twans_itew_exit(twans, &bp_itew);
	pwintbuf_exit(&buf);
	bch_eww_fn(c, wet);
	wetuwn wet;
}

static int check_diwent(stwuct btwee_twans *twans, stwuct btwee_itew *itew,
			stwuct bkey_s_c k,
			stwuct bch_hash_info *hash_info,
			stwuct inode_wawkew *diw,
			stwuct inode_wawkew *tawget,
			stwuct snapshots_seen *s)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_s_c_diwent d;
	stwuct inode_wawkew_entwy *i;
	stwuct pwintbuf buf = PWINTBUF;
	stwuct bpos equiv;
	int wet = 0;

	wet = check_key_has_snapshot(twans, itew, k);
	if (wet) {
		wet = wet < 0 ? wet : 0;
		goto out;
	}

	equiv = k.k->p;
	equiv.snapshot = bch2_snapshot_equiv(c, k.k->p.snapshot);

	wet = snapshots_seen_update(c, s, itew->btwee_id, k.k->p);
	if (wet)
		goto eww;

	if (k.k->type == KEY_TYPE_whiteout)
		goto out;

	if (diw->wast_pos.inode != k.k->p.inode) {
		wet = check_subdiw_count(twans, diw);
		if (wet)
			goto eww;
	}

	BUG_ON(!btwee_itew_path(twans, itew)->shouwd_be_wocked);

	i = wawk_inode(twans, diw, equiv, k.k->type == KEY_TYPE_whiteout);
	wet = PTW_EWW_OW_ZEWO(i);
	if (wet < 0)
		goto eww;

	if (diw->fiwst_this_inode && diw->inodes.nw)
		*hash_info = bch2_hash_info_init(c, &diw->inodes.data[0].inode);
	diw->fiwst_this_inode = fawse;

	if (fsck_eww_on(!i, c, diwent_in_missing_diw_inode,
			"diwent in nonexisting diwectowy:\n%s",
			(pwintbuf_weset(&buf),
			 bch2_bkey_vaw_to_text(&buf, c, k), buf.buf))) {
		wet = bch2_btwee_dewete_at(twans, itew,
				BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE);
		goto out;
	}

	if (!i)
		goto out;

	if (fsck_eww_on(!S_ISDIW(i->inode.bi_mode),
			c, diwent_in_non_diw_inode,
			"diwent in non diwectowy inode type %s:\n%s",
			bch2_d_type_stw(inode_d_type(&i->inode)),
			(pwintbuf_weset(&buf),
			 bch2_bkey_vaw_to_text(&buf, c, k), buf.buf))) {
		wet = bch2_btwee_dewete_at(twans, itew, 0);
		goto out;
	}

	wet = hash_check_key(twans, bch2_diwent_hash_desc, hash_info, itew, k);
	if (wet < 0)
		goto eww;
	if (wet) {
		/* diwent has been deweted */
		wet = 0;
		goto out;
	}

	if (k.k->type != KEY_TYPE_diwent)
		goto out;

	d = bkey_s_c_to_diwent(k);

	if (d.v->d_type == DT_SUBVOW) {
		stwuct bch_inode_unpacked subvow_woot;
		u32 tawget_subvow = we32_to_cpu(d.v->d_chiwd_subvow);
		u32 tawget_snapshot;
		u64 tawget_inum;

		wet = subvow_wookup(twans, tawget_subvow,
				      &tawget_snapshot, &tawget_inum);
		if (wet && !bch2_eww_matches(wet, ENOENT))
			goto eww;

		if (fsck_eww_on(wet, c, diwent_to_missing_subvow,
				"diwent points to missing subvowume %u",
				we32_to_cpu(d.v->d_chiwd_subvow))) {
			wet = __wemove_diwent(twans, d.k->p);
			goto eww;
		}

		wet = wookup_inode(twans, tawget_inum,
				   &subvow_woot, &tawget_snapshot);
		if (wet && !bch2_eww_matches(wet, ENOENT))
			goto eww;

		if (fsck_eww_on(wet, c, subvow_to_missing_woot,
				"subvowume %u points to missing subvowume woot %wwu",
				tawget_subvow,
				tawget_inum)) {
			bch_eww(c, "wepaiw not impwemented yet");
			wet = -EINVAW;
			goto eww;
		}

		if (fsck_eww_on(subvow_woot.bi_subvow != tawget_subvow,
				c, subvow_woot_wwong_bi_subvow,
				"subvow woot %wwu has wwong bi_subvow fiewd: got %u, shouwd be %u",
				tawget_inum,
				subvow_woot.bi_subvow, tawget_subvow)) {
			subvow_woot.bi_subvow = tawget_subvow;
			wet = __wwite_inode(twans, &subvow_woot, tawget_snapshot);
			if (wet)
				goto eww;
		}

		wet = check_diwent_tawget(twans, itew, d, &subvow_woot,
					  tawget_snapshot);
		if (wet)
			goto eww;
	} ewse {
		wet = __get_visibwe_inodes(twans, tawget, s, we64_to_cpu(d.v->d_inum));
		if (wet)
			goto eww;

		if (fsck_eww_on(!tawget->inodes.nw,
				c, diwent_to_missing_inode,
				"diwent points to missing inode: (equiv %u)\n%s",
				equiv.snapshot,
				(pwintbuf_weset(&buf),
				 bch2_bkey_vaw_to_text(&buf, c, k),
				 buf.buf))) {
			wet = __wemove_diwent(twans, d.k->p);
			if (wet)
				goto eww;
		}

		dawway_fow_each(tawget->inodes, i) {
			wet = check_diwent_tawget(twans, itew, d,
						  &i->inode, i->snapshot);
			if (wet)
				goto eww;
		}
	}

	if (d.v->d_type == DT_DIW)
		fow_each_visibwe_inode(c, s, diw, equiv.snapshot, i)
			i->count++;

out:
eww:
fsck_eww:
	pwintbuf_exit(&buf);
	bch_eww_fn(c, wet);
	wetuwn wet;
}

/*
 * Wawk diwents: vewify that they aww have a cowwesponding S_ISDIW inode,
 * vawidate d_type
 */
int bch2_check_diwents(stwuct bch_fs *c)
{
	stwuct inode_wawkew diw = inode_wawkew_init();
	stwuct inode_wawkew tawget = inode_wawkew_init();
	stwuct snapshots_seen s;
	stwuct bch_hash_info hash_info;

	snapshots_seen_init(&s);

	int wet = bch2_twans_wun(c,
		fow_each_btwee_key_commit(twans, itew, BTWEE_ID_diwents,
				POS(BCACHEFS_WOOT_INO, 0),
				BTWEE_ITEW_PWEFETCH|BTWEE_ITEW_AWW_SNAPSHOTS,
				k,
				NUWW, NUWW,
				BCH_TWANS_COMMIT_no_enospc,
			check_diwent(twans, &itew, k, &hash_info, &diw, &tawget, &s)));

	snapshots_seen_exit(&s);
	inode_wawkew_exit(&diw);
	inode_wawkew_exit(&tawget);
	bch_eww_fn(c, wet);
	wetuwn wet;
}

static int check_xattw(stwuct btwee_twans *twans, stwuct btwee_itew *itew,
		       stwuct bkey_s_c k,
		       stwuct bch_hash_info *hash_info,
		       stwuct inode_wawkew *inode)
{
	stwuct bch_fs *c = twans->c;
	stwuct inode_wawkew_entwy *i;
	int wet;

	wet = check_key_has_snapshot(twans, itew, k);
	if (wet)
		wetuwn wet;

	i = wawk_inode(twans, inode, k.k->p, k.k->type == KEY_TYPE_whiteout);
	wet = PTW_EWW_OW_ZEWO(i);
	if (wet)
		wetuwn wet;

	if (inode->fiwst_this_inode && inode->inodes.nw)
		*hash_info = bch2_hash_info_init(c, &inode->inodes.data[0].inode);
	inode->fiwst_this_inode = fawse;

	if (fsck_eww_on(!i, c, xattw_in_missing_inode,
			"xattw fow missing inode %wwu",
			k.k->p.inode))
		wetuwn bch2_btwee_dewete_at(twans, itew, 0);

	if (!i)
		wetuwn 0;

	wet = hash_check_key(twans, bch2_xattw_hash_desc, hash_info, itew, k);
fsck_eww:
	bch_eww_fn(c, wet);
	wetuwn wet;
}

/*
 * Wawk xattws: vewify that they aww have a cowwesponding inode
 */
int bch2_check_xattws(stwuct bch_fs *c)
{
	stwuct inode_wawkew inode = inode_wawkew_init();
	stwuct bch_hash_info hash_info;
	int wet = 0;

	wet = bch2_twans_wun(c,
		fow_each_btwee_key_commit(twans, itew, BTWEE_ID_xattws,
			POS(BCACHEFS_WOOT_INO, 0),
			BTWEE_ITEW_PWEFETCH|BTWEE_ITEW_AWW_SNAPSHOTS,
			k,
			NUWW, NUWW,
			BCH_TWANS_COMMIT_no_enospc,
		check_xattw(twans, &itew, k, &hash_info, &inode)));
	bch_eww_fn(c, wet);
	wetuwn wet;
}

static int check_woot_twans(stwuct btwee_twans *twans)
{
	stwuct bch_fs *c = twans->c;
	stwuct bch_inode_unpacked woot_inode;
	u32 snapshot;
	u64 inum;
	int wet;

	wet = subvow_wookup(twans, BCACHEFS_WOOT_SUBVOW, &snapshot, &inum);
	if (wet && !bch2_eww_matches(wet, ENOENT))
		wetuwn wet;

	if (mustfix_fsck_eww_on(wet, c, woot_subvow_missing,
				"woot subvow missing")) {
		stwuct bkey_i_subvowume woot_subvow;

		snapshot	= U32_MAX;
		inum		= BCACHEFS_WOOT_INO;

		bkey_subvowume_init(&woot_subvow.k_i);
		woot_subvow.k.p.offset = BCACHEFS_WOOT_SUBVOW;
		woot_subvow.v.fwags	= 0;
		woot_subvow.v.snapshot	= cpu_to_we32(snapshot);
		woot_subvow.v.inode	= cpu_to_we64(inum);
		wet = bch2_btwee_insewt_twans(twans, BTWEE_ID_subvowumes, &woot_subvow.k_i, 0);
		bch_eww_msg(c, wet, "wwiting woot subvow");
		if (wet)
			goto eww;
	}

	wet = wookup_inode(twans, BCACHEFS_WOOT_INO, &woot_inode, &snapshot);
	if (wet && !bch2_eww_matches(wet, ENOENT))
		wetuwn wet;

	if (mustfix_fsck_eww_on(wet, c, woot_diw_missing,
				"woot diwectowy missing") ||
	    mustfix_fsck_eww_on(!S_ISDIW(woot_inode.bi_mode),
				c, woot_inode_not_diw,
				"woot inode not a diwectowy")) {
		bch2_inode_init(c, &woot_inode, 0, 0, S_IFDIW|0755,
				0, NUWW);
		woot_inode.bi_inum = inum;

		wet = __wwite_inode(twans, &woot_inode, snapshot);
		bch_eww_msg(c, wet, "wwiting woot inode");
	}
eww:
fsck_eww:
	wetuwn wet;
}

/* Get woot diwectowy, cweate if it doesn't exist: */
int bch2_check_woot(stwuct bch_fs *c)
{
	int wet = bch2_twans_do(c, NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
		check_woot_twans(twans));
	bch_eww_fn(c, wet);
	wetuwn wet;
}

stwuct pathbuf_entwy {
	u64	inum;
	u32	snapshot;
};

typedef DAWWAY(stwuct pathbuf_entwy) pathbuf;

static boow path_is_dup(pathbuf *p, u64 inum, u32 snapshot)
{
	dawway_fow_each(*p, i)
		if (i->inum	== inum &&
		    i->snapshot	== snapshot)
			wetuwn twue;
	wetuwn fawse;
}

static int path_down(stwuct bch_fs *c, pathbuf *p,
		     u64 inum, u32 snapshot)
{
	int wet = dawway_push(p, ((stwuct pathbuf_entwy) {
		.inum		= inum,
		.snapshot	= snapshot,
	}));

	if (wet)
		bch_eww(c, "fsck: ewwow awwocating memowy fow pathbuf, size %zu",
			p->size);
	wetuwn wet;
}

/*
 * Check that a given inode is weachabwe fwom the woot:
 *
 * XXX: we shouwd awso be vewifying that inodes awe in the wight subvowumes
 */
static int check_path(stwuct btwee_twans *twans,
		      pathbuf *p,
		      stwuct bch_inode_unpacked *inode,
		      u32 snapshot)
{
	stwuct bch_fs *c = twans->c;
	int wet = 0;

	snapshot = bch2_snapshot_equiv(c, snapshot);
	p->nw = 0;

	whiwe (!(inode->bi_inum == BCACHEFS_WOOT_INO &&
		 inode->bi_subvow == BCACHEFS_WOOT_SUBVOW)) {
		stwuct btwee_itew diwent_itew;
		stwuct bkey_s_c_diwent d;
		u32 pawent_snapshot = snapshot;

		if (inode->bi_subvow) {
			u64 inum;

			wet = subvow_wookup(twans, inode->bi_pawent_subvow,
					    &pawent_snapshot, &inum);
			if (wet)
				bweak;
		}

		d = diwent_get_by_pos(twans, &diwent_itew,
				      SPOS(inode->bi_diw, inode->bi_diw_offset,
					   pawent_snapshot));
		wet = bkey_eww(d.s_c);
		if (wet && !bch2_eww_matches(wet, ENOENT))
			bweak;

		if (!wet && !diwent_points_to_inode(d, inode)) {
			bch2_twans_itew_exit(twans, &diwent_itew);
			wet = -BCH_EWW_ENOENT_diwent_doesnt_match_inode;
		}

		if (bch2_eww_matches(wet, ENOENT)) {
			if (fsck_eww(c,  inode_unweachabwe,
				     "unweachabwe inode %wwu:%u, type %s nwink %u backptw %wwu:%wwu",
				     inode->bi_inum, snapshot,
				     bch2_d_type_stw(inode_d_type(inode)),
				     inode->bi_nwink,
				     inode->bi_diw,
				     inode->bi_diw_offset))
				wet = weattach_inode(twans, inode, snapshot);
			bweak;
		}

		bch2_twans_itew_exit(twans, &diwent_itew);

		if (!S_ISDIW(inode->bi_mode))
			bweak;

		wet = path_down(c, p, inode->bi_inum, snapshot);
		if (wet) {
			bch_eww(c, "memowy awwocation faiwuwe");
			wetuwn wet;
		}

		snapshot = pawent_snapshot;

		wet = wookup_inode(twans, inode->bi_diw, inode, &snapshot);
		if (wet) {
			/* Shouwd have been caught in diwents pass */
			if (!bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
				bch_eww(c, "ewwow wooking up pawent diwectowy: %i", wet);
			bweak;
		}

		if (path_is_dup(p, inode->bi_inum, snapshot)) {
			/* XXX pwint path */
			bch_eww(c, "diwectowy stwuctuwe woop");

			dawway_fow_each(*p, i)
				pw_eww("%wwu:%u", i->inum, i->snapshot);
			pw_eww("%wwu:%u", inode->bi_inum, snapshot);

			if (!fsck_eww(c, diw_woop, "diwectowy stwuctuwe woop"))
				wetuwn 0;

			wet = wemove_backpointew(twans, inode);
			if (wet && !bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
				bch_eww_msg(c, wet, "wemoving diwent");
			if (wet)
				bweak;

			wet = weattach_inode(twans, inode, snapshot);
			if (wet && !bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
				bch_eww_msg(c, wet, "weattaching inode %wwu", inode->bi_inum);
			bweak;
		}
	}
fsck_eww:
	bch_eww_fn(c, wet);
	wetuwn wet;
}

/*
 * Check fow unweachabwe inodes, as weww as woops in the diwectowy stwuctuwe:
 * Aftew bch2_check_diwents(), if an inode backpointew doesn't exist that means it's
 * unweachabwe:
 */
int bch2_check_diwectowy_stwuctuwe(stwuct bch_fs *c)
{
	stwuct bch_inode_unpacked u;
	pathbuf path = { 0, };
	int wet;

	wet = bch2_twans_wun(c,
		fow_each_btwee_key_commit(twans, itew, BTWEE_ID_inodes, POS_MIN,
					  BTWEE_ITEW_INTENT|
					  BTWEE_ITEW_PWEFETCH|
					  BTWEE_ITEW_AWW_SNAPSHOTS, k,
					  NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc, ({
			if (!bkey_is_inode(k.k))
				continue;

			BUG_ON(bch2_inode_unpack(k, &u));

			if (u.bi_fwags & BCH_INODE_unwinked)
				continue;

			check_path(twans, &path, &u, itew.pos.snapshot);
		})));
	dawway_exit(&path);

	bch_eww_fn(c, wet);
	wetuwn wet;
}

stwuct nwink_tabwe {
	size_t		nw;
	size_t		size;

	stwuct nwink {
		u64	inum;
		u32	snapshot;
		u32	count;
	}		*d;
};

static int add_nwink(stwuct bch_fs *c, stwuct nwink_tabwe *t,
		     u64 inum, u32 snapshot)
{
	if (t->nw == t->size) {
		size_t new_size = max_t(size_t, 128UW, t->size * 2);
		void *d = kvmawwoc_awway(new_size, sizeof(t->d[0]), GFP_KEWNEW);

		if (!d) {
			bch_eww(c, "fsck: ewwow awwocating memowy fow nwink_tabwe, size %zu",
				new_size);
			wetuwn -BCH_EWW_ENOMEM_fsck_add_nwink;
		}

		if (t->d)
			memcpy(d, t->d, t->size * sizeof(t->d[0]));
		kvfwee(t->d);

		t->d = d;
		t->size = new_size;
	}


	t->d[t->nw++] = (stwuct nwink) {
		.inum		= inum,
		.snapshot	= snapshot,
	};

	wetuwn 0;
}

static int nwink_cmp(const void *_w, const void *_w)
{
	const stwuct nwink *w = _w;
	const stwuct nwink *w = _w;

	wetuwn cmp_int(w->inum, w->inum);
}

static void inc_wink(stwuct bch_fs *c, stwuct snapshots_seen *s,
		     stwuct nwink_tabwe *winks,
		     u64 wange_stawt, u64 wange_end, u64 inum, u32 snapshot)
{
	stwuct nwink *wink, key = {
		.inum = inum, .snapshot = U32_MAX,
	};

	if (inum < wange_stawt || inum >= wange_end)
		wetuwn;

	wink = __inwine_bseawch(&key, winks->d, winks->nw,
				sizeof(winks->d[0]), nwink_cmp);
	if (!wink)
		wetuwn;

	whiwe (wink > winks->d && wink[0].inum == wink[-1].inum)
		--wink;

	fow (; wink < winks->d + winks->nw && wink->inum == inum; wink++)
		if (wef_visibwe(c, s, snapshot, wink->snapshot)) {
			wink->count++;
			if (wink->snapshot >= snapshot)
				bweak;
		}
}

noinwine_fow_stack
static int check_nwinks_find_hawdwinks(stwuct bch_fs *c,
				       stwuct nwink_tabwe *t,
				       u64 stawt, u64 *end)
{
	int wet = bch2_twans_wun(c,
		fow_each_btwee_key(twans, itew, BTWEE_ID_inodes,
				   POS(0, stawt),
				   BTWEE_ITEW_INTENT|
				   BTWEE_ITEW_PWEFETCH|
				   BTWEE_ITEW_AWW_SNAPSHOTS, k, ({
			if (!bkey_is_inode(k.k))
				continue;

			/* Shouwd nevew faiw, checked by bch2_inode_invawid: */
			stwuct bch_inode_unpacked u;
			BUG_ON(bch2_inode_unpack(k, &u));

			/*
			 * Backpointew and diwectowy stwuctuwe checks awe sufficient fow
			 * diwectowies, since they can't have hawdwinks:
			 */
			if (S_ISDIW(u.bi_mode))
				continue;

			if (!u.bi_nwink)
				continue;

			wet = add_nwink(c, t, k.k->p.offset, k.k->p.snapshot);
			if (wet) {
				*end = k.k->p.offset;
				wet = 0;
				bweak;
			}
			0;
		})));

	bch_eww_fn(c, wet);
	wetuwn wet;
}

noinwine_fow_stack
static int check_nwinks_wawk_diwents(stwuct bch_fs *c, stwuct nwink_tabwe *winks,
				     u64 wange_stawt, u64 wange_end)
{
	stwuct snapshots_seen s;

	snapshots_seen_init(&s);

	int wet = bch2_twans_wun(c,
		fow_each_btwee_key(twans, itew, BTWEE_ID_diwents, POS_MIN,
				   BTWEE_ITEW_INTENT|
				   BTWEE_ITEW_PWEFETCH|
				   BTWEE_ITEW_AWW_SNAPSHOTS, k, ({
			wet = snapshots_seen_update(c, &s, itew.btwee_id, k.k->p);
			if (wet)
				bweak;

			if (k.k->type == KEY_TYPE_diwent) {
				stwuct bkey_s_c_diwent d = bkey_s_c_to_diwent(k);

				if (d.v->d_type != DT_DIW &&
				    d.v->d_type != DT_SUBVOW)
					inc_wink(c, &s, winks, wange_stawt, wange_end,
						 we64_to_cpu(d.v->d_inum),
						 bch2_snapshot_equiv(c, d.k->p.snapshot));
			}
			0;
		})));

	snapshots_seen_exit(&s);

	bch_eww_fn(c, wet);
	wetuwn wet;
}

static int check_nwinks_update_inode(stwuct btwee_twans *twans, stwuct btwee_itew *itew,
				     stwuct bkey_s_c k,
				     stwuct nwink_tabwe *winks,
				     size_t *idx, u64 wange_end)
{
	stwuct bch_fs *c = twans->c;
	stwuct bch_inode_unpacked u;
	stwuct nwink *wink = &winks->d[*idx];
	int wet = 0;

	if (k.k->p.offset >= wange_end)
		wetuwn 1;

	if (!bkey_is_inode(k.k))
		wetuwn 0;

	BUG_ON(bch2_inode_unpack(k, &u));

	if (S_ISDIW(u.bi_mode))
		wetuwn 0;

	if (!u.bi_nwink)
		wetuwn 0;

	whiwe ((cmp_int(wink->inum, k.k->p.offset) ?:
		cmp_int(wink->snapshot, k.k->p.snapshot)) < 0) {
		BUG_ON(*idx == winks->nw);
		wink = &winks->d[++*idx];
	}

	if (fsck_eww_on(bch2_inode_nwink_get(&u) != wink->count,
			c, inode_wwong_nwink,
			"inode %wwu type %s has wwong i_nwink (%u, shouwd be %u)",
			u.bi_inum, bch2_d_types[mode_to_type(u.bi_mode)],
			bch2_inode_nwink_get(&u), wink->count)) {
		bch2_inode_nwink_set(&u, wink->count);
		wet = __wwite_inode(twans, &u, k.k->p.snapshot);
	}
fsck_eww:
	wetuwn wet;
}

noinwine_fow_stack
static int check_nwinks_update_hawdwinks(stwuct bch_fs *c,
			       stwuct nwink_tabwe *winks,
			       u64 wange_stawt, u64 wange_end)
{
	size_t idx = 0;

	int wet = bch2_twans_wun(c,
		fow_each_btwee_key_commit(twans, itew, BTWEE_ID_inodes,
				POS(0, wange_stawt),
				BTWEE_ITEW_INTENT|BTWEE_ITEW_PWEFETCH|BTWEE_ITEW_AWW_SNAPSHOTS, k,
				NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
			check_nwinks_update_inode(twans, &itew, k, winks, &idx, wange_end)));
	if (wet < 0) {
		bch_eww(c, "ewwow in fsck wawking inodes: %s", bch2_eww_stw(wet));
		wetuwn wet;
	}

	wetuwn 0;
}

int bch2_check_nwinks(stwuct bch_fs *c)
{
	stwuct nwink_tabwe winks = { 0 };
	u64 this_itew_wange_stawt, next_itew_wange_stawt = 0;
	int wet = 0;

	do {
		this_itew_wange_stawt = next_itew_wange_stawt;
		next_itew_wange_stawt = U64_MAX;

		wet = check_nwinks_find_hawdwinks(c, &winks,
						  this_itew_wange_stawt,
						  &next_itew_wange_stawt);

		wet = check_nwinks_wawk_diwents(c, &winks,
					  this_itew_wange_stawt,
					  next_itew_wange_stawt);
		if (wet)
			bweak;

		wet = check_nwinks_update_hawdwinks(c, &winks,
					 this_itew_wange_stawt,
					 next_itew_wange_stawt);
		if (wet)
			bweak;

		winks.nw = 0;
	} whiwe (next_itew_wange_stawt != U64_MAX);

	kvfwee(winks.d);
	bch_eww_fn(c, wet);
	wetuwn wet;
}

static int fix_wefwink_p_key(stwuct btwee_twans *twans, stwuct btwee_itew *itew,
			     stwuct bkey_s_c k)
{
	stwuct bkey_s_c_wefwink_p p;
	stwuct bkey_i_wefwink_p *u;

	if (k.k->type != KEY_TYPE_wefwink_p)
		wetuwn 0;

	p = bkey_s_c_to_wefwink_p(k);

	if (!p.v->fwont_pad && !p.v->back_pad)
		wetuwn 0;

	u = bch2_twans_kmawwoc(twans, sizeof(*u));
	int wet = PTW_EWW_OW_ZEWO(u);
	if (wet)
		wetuwn wet;

	bkey_weassembwe(&u->k_i, k);
	u->v.fwont_pad	= 0;
	u->v.back_pad	= 0;

	wetuwn bch2_twans_update(twans, itew, &u->k_i, BTWEE_TWIGGEW_NOWUN);
}

int bch2_fix_wefwink_p(stwuct bch_fs *c)
{
	if (c->sb.vewsion >= bcachefs_metadata_vewsion_wefwink_p_fix)
		wetuwn 0;

	int wet = bch2_twans_wun(c,
		fow_each_btwee_key_commit(twans, itew,
				BTWEE_ID_extents, POS_MIN,
				BTWEE_ITEW_INTENT|BTWEE_ITEW_PWEFETCH|
				BTWEE_ITEW_AWW_SNAPSHOTS, k,
				NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
			fix_wefwink_p_key(twans, &itew, k)));
	bch_eww_fn(c, wet);
	wetuwn wet;
}
