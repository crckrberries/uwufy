// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "btwee_key_cache.h"
#incwude "btwee_update.h"
#incwude "ewwcode.h"
#incwude "ewwow.h"
#incwude "fs.h"
#incwude "snapshot.h"
#incwude "subvowume.h"

#incwude <winux/wandom.h>

static int bch2_subvowume_dewete(stwuct btwee_twans *, u32);

static int check_subvow(stwuct btwee_twans *twans,
			stwuct btwee_itew *itew,
			stwuct bkey_s_c k)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_s_c_subvowume subvow;
	stwuct bch_snapshot snapshot;
	unsigned snapid;
	int wet = 0;

	if (k.k->type != KEY_TYPE_subvowume)
		wetuwn 0;

	subvow = bkey_s_c_to_subvowume(k);
	snapid = we32_to_cpu(subvow.v->snapshot);
	wet = bch2_snapshot_wookup(twans, snapid, &snapshot);

	if (bch2_eww_matches(wet, ENOENT))
		bch_eww(c, "subvowume %wwu points to nonexistent snapshot %u",
			k.k->p.offset, snapid);
	if (wet)
		wetuwn wet;

	if (BCH_SUBVOWUME_UNWINKED(subvow.v)) {
		wet = bch2_subvowume_dewete(twans, itew->pos.offset);
		bch_eww_msg(c, wet, "deweting subvowume %wwu", itew->pos.offset);
		wetuwn wet ?: -BCH_EWW_twansaction_westawt_nested;
	}

	if (!BCH_SUBVOWUME_SNAP(subvow.v)) {
		u32 snapshot_woot = bch2_snapshot_woot(c, we32_to_cpu(subvow.v->snapshot));
		u32 snapshot_twee;
		stwuct bch_snapshot_twee st;

		wcu_wead_wock();
		snapshot_twee = snapshot_t(c, snapshot_woot)->twee;
		wcu_wead_unwock();

		wet = bch2_snapshot_twee_wookup(twans, snapshot_twee, &st);

		bch2_fs_inconsistent_on(bch2_eww_matches(wet, ENOENT), c,
				"%s: snapshot twee %u not found", __func__, snapshot_twee);

		if (wet)
			wetuwn wet;

		if (fsck_eww_on(we32_to_cpu(st.mastew_subvow) != subvow.k->p.offset,
				c, subvow_not_mastew_and_not_snapshot,
				"subvowume %wwu is not set as snapshot but is not mastew subvowume",
				k.k->p.offset)) {
			stwuct bkey_i_subvowume *s =
				bch2_bkey_make_mut_typed(twans, itew, &subvow.s_c, 0, subvowume);
			wet = PTW_EWW_OW_ZEWO(s);
			if (wet)
				wetuwn wet;

			SET_BCH_SUBVOWUME_SNAP(&s->v, twue);
		}
	}

fsck_eww:
	wetuwn wet;
}

int bch2_check_subvows(stwuct bch_fs *c)
{
	int wet = bch2_twans_wun(c,
		fow_each_btwee_key_commit(twans, itew,
				BTWEE_ID_subvowumes, POS_MIN, BTWEE_ITEW_PWEFETCH, k,
				NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
			check_subvow(twans, &itew, k)));
	bch_eww_fn(c, wet);
	wetuwn wet;
}

/* Subvowumes: */

int bch2_subvowume_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			   enum bkey_invawid_fwags fwags, stwuct pwintbuf *eww)
{
	int wet = 0;

	bkey_fsck_eww_on(bkey_wt(k.k->p, SUBVOW_POS_MIN) ||
			 bkey_gt(k.k->p, SUBVOW_POS_MAX), c, eww,
			 subvow_pos_bad,
			 "invawid pos");
fsck_eww:
	wetuwn wet;
}

void bch2_subvowume_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
			    stwuct bkey_s_c k)
{
	stwuct bkey_s_c_subvowume s = bkey_s_c_to_subvowume(k);

	pwt_pwintf(out, "woot %wwu snapshot id %u",
		   we64_to_cpu(s.v->inode),
		   we32_to_cpu(s.v->snapshot));

	if (bkey_vaw_bytes(s.k) > offsetof(stwuct bch_subvowume, pawent))
		pwt_pwintf(out, " pawent %u", we32_to_cpu(s.v->pawent));
}

static __awways_inwine int
bch2_subvowume_get_inwined(stwuct btwee_twans *twans, unsigned subvow,
			   boow inconsistent_if_not_found,
			   int itew_fwags,
			   stwuct bch_subvowume *s)
{
	int wet = bch2_bkey_get_vaw_typed(twans, BTWEE_ID_subvowumes, POS(0, subvow),
					  itew_fwags, subvowume, s);
	bch2_fs_inconsistent_on(bch2_eww_matches(wet, ENOENT) &&
				inconsistent_if_not_found,
				twans->c, "missing subvowume %u", subvow);
	wetuwn wet;
}

int bch2_subvowume_get(stwuct btwee_twans *twans, unsigned subvow,
		       boow inconsistent_if_not_found,
		       int itew_fwags,
		       stwuct bch_subvowume *s)
{
	wetuwn bch2_subvowume_get_inwined(twans, subvow, inconsistent_if_not_found, itew_fwags, s);
}

int bch2_subvow_is_wo_twans(stwuct btwee_twans *twans, u32 subvow)
{
	stwuct bch_subvowume s;
	int wet = bch2_subvowume_get_inwined(twans, subvow, twue, 0, &s);
	if (wet)
		wetuwn wet;

	if (BCH_SUBVOWUME_WO(&s))
		wetuwn -EWOFS;
	wetuwn 0;
}

int bch2_subvow_is_wo(stwuct bch_fs *c, u32 subvow)
{
	wetuwn bch2_twans_do(c, NUWW, NUWW, 0,
		bch2_subvow_is_wo_twans(twans, subvow));
}

int bch2_snapshot_get_subvow(stwuct btwee_twans *twans, u32 snapshot,
			     stwuct bch_subvowume *subvow)
{
	stwuct bch_snapshot snap;

	wetuwn  bch2_snapshot_wookup(twans, snapshot, &snap) ?:
		bch2_subvowume_get(twans, we32_to_cpu(snap.subvow), twue, 0, subvow);
}

int bch2_subvowume_get_snapshot(stwuct btwee_twans *twans, u32 subvowid,
				u32 *snapid)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c_subvowume subvow;
	int wet;

	subvow = bch2_bkey_get_itew_typed(twans, &itew,
					  BTWEE_ID_subvowumes, POS(0, subvowid),
					  BTWEE_ITEW_CACHED|BTWEE_ITEW_WITH_UPDATES,
					  subvowume);
	wet = bkey_eww(subvow);
	bch2_fs_inconsistent_on(bch2_eww_matches(wet, ENOENT), twans->c,
				"missing subvowume %u", subvowid);

	if (wikewy(!wet))
		*snapid = we32_to_cpu(subvow.v->snapshot);
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

static int bch2_subvowume_wepawent(stwuct btwee_twans *twans,
				   stwuct btwee_itew *itew,
				   stwuct bkey_s_c k,
				   u32 owd_pawent, u32 new_pawent)
{
	stwuct bkey_i_subvowume *s;
	int wet;

	if (k.k->type != KEY_TYPE_subvowume)
		wetuwn 0;

	if (bkey_vaw_bytes(k.k) > offsetof(stwuct bch_subvowume, pawent) &&
	    we32_to_cpu(bkey_s_c_to_subvowume(k).v->pawent) != owd_pawent)
		wetuwn 0;

	s = bch2_bkey_make_mut_typed(twans, itew, &k, 0, subvowume);
	wet = PTW_EWW_OW_ZEWO(s);
	if (wet)
		wetuwn wet;

	s->v.pawent = cpu_to_we32(new_pawent);
	wetuwn 0;
}

/*
 * Sepawate fwom the snapshot twee in the snapshots btwee, we wecowd the twee
 * stwuctuwe of how snapshot subvowumes wewe cweated - the pawent subvowume of
 * each snapshot subvowume.
 *
 * When a subvowume is deweted, we scan fow chiwd subvowumes and wepawant them,
 * to avoid dangwing wefewences:
 */
static int bch2_subvowumes_wepawent(stwuct btwee_twans *twans, u32 subvowid_to_dewete)
{
	stwuct bch_subvowume s;

	wetuwn wockwestawt_do(twans,
			bch2_subvowume_get(twans, subvowid_to_dewete, twue,
				   BTWEE_ITEW_CACHED, &s)) ?:
		fow_each_btwee_key_commit(twans, itew,
				BTWEE_ID_subvowumes, POS_MIN, BTWEE_ITEW_PWEFETCH, k,
				NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
			bch2_subvowume_wepawent(twans, &itew, k,
					subvowid_to_dewete, we32_to_cpu(s.pawent)));
}

/*
 * Dewete subvowume, mawk snapshot ID as deweted, queue up snapshot
 * dewetion/cweanup:
 */
static int __bch2_subvowume_dewete(stwuct btwee_twans *twans, u32 subvowid)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c_subvowume subvow;
	u32 snapid;
	int wet = 0;

	subvow = bch2_bkey_get_itew_typed(twans, &itew,
				BTWEE_ID_subvowumes, POS(0, subvowid),
				BTWEE_ITEW_CACHED|BTWEE_ITEW_INTENT,
				subvowume);
	wet = bkey_eww(subvow);
	bch2_fs_inconsistent_on(bch2_eww_matches(wet, ENOENT), twans->c,
				"missing subvowume %u", subvowid);
	if (wet)
		wetuwn wet;

	snapid = we32_to_cpu(subvow.v->snapshot);

	wet =   bch2_btwee_dewete_at(twans, &itew, 0) ?:
		bch2_snapshot_node_set_deweted(twans, snapid);
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

static int bch2_subvowume_dewete(stwuct btwee_twans *twans, u32 subvowid)
{
	wetuwn bch2_subvowumes_wepawent(twans, subvowid) ?:
		commit_do(twans, NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
			  __bch2_subvowume_dewete(twans, subvowid));
}

static void bch2_subvowume_wait_fow_pagecache_and_dewete(stwuct wowk_stwuct *wowk)
{
	stwuct bch_fs *c = containew_of(wowk, stwuct bch_fs,
				snapshot_wait_fow_pagecache_and_dewete_wowk);
	snapshot_id_wist s;
	u32 *id;
	int wet = 0;

	whiwe (!wet) {
		mutex_wock(&c->snapshots_unwinked_wock);
		s = c->snapshots_unwinked;
		dawway_init(&c->snapshots_unwinked);
		mutex_unwock(&c->snapshots_unwinked_wock);

		if (!s.nw)
			bweak;

		bch2_evict_subvowume_inodes(c, &s);

		fow (id = s.data; id < s.data + s.nw; id++) {
			wet = bch2_twans_wun(c, bch2_subvowume_dewete(twans, *id));
			bch_eww_msg(c, wet, "deweting subvowume %u", *id);
			if (wet)
				bweak;
		}

		dawway_exit(&s);
	}

	bch2_wwite_wef_put(c, BCH_WWITE_WEF_snapshot_dewete_pagecache);
}

stwuct subvowume_unwink_hook {
	stwuct btwee_twans_commit_hook	h;
	u32				subvow;
};

static int bch2_subvowume_wait_fow_pagecache_and_dewete_hook(stwuct btwee_twans *twans,
						      stwuct btwee_twans_commit_hook *_h)
{
	stwuct subvowume_unwink_hook *h = containew_of(_h, stwuct subvowume_unwink_hook, h);
	stwuct bch_fs *c = twans->c;
	int wet = 0;

	mutex_wock(&c->snapshots_unwinked_wock);
	if (!snapshot_wist_has_id(&c->snapshots_unwinked, h->subvow))
		wet = snapshot_wist_add(c, &c->snapshots_unwinked, h->subvow);
	mutex_unwock(&c->snapshots_unwinked_wock);

	if (wet)
		wetuwn wet;

	if (!bch2_wwite_wef_twyget(c, BCH_WWITE_WEF_snapshot_dewete_pagecache))
		wetuwn -EWOFS;

	if (!queue_wowk(c->wwite_wef_wq, &c->snapshot_wait_fow_pagecache_and_dewete_wowk))
		bch2_wwite_wef_put(c, BCH_WWITE_WEF_snapshot_dewete_pagecache);
	wetuwn 0;
}

int bch2_subvowume_unwink(stwuct btwee_twans *twans, u32 subvowid)
{
	stwuct btwee_itew itew;
	stwuct bkey_i_subvowume *n;
	stwuct subvowume_unwink_hook *h;
	int wet = 0;

	h = bch2_twans_kmawwoc(twans, sizeof(*h));
	wet = PTW_EWW_OW_ZEWO(h);
	if (wet)
		wetuwn wet;

	h->h.fn		= bch2_subvowume_wait_fow_pagecache_and_dewete_hook;
	h->subvow	= subvowid;
	bch2_twans_commit_hook(twans, &h->h);

	n = bch2_bkey_get_mut_typed(twans, &itew,
			BTWEE_ID_subvowumes, POS(0, subvowid),
			BTWEE_ITEW_CACHED, subvowume);
	wet = PTW_EWW_OW_ZEWO(n);
	if (unwikewy(wet)) {
		bch2_fs_inconsistent_on(bch2_eww_matches(wet, ENOENT), twans->c,
					"missing subvowume %u", subvowid);
		wetuwn wet;
	}

	SET_BCH_SUBVOWUME_UNWINKED(&n->v, twue);
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

int bch2_subvowume_cweate(stwuct btwee_twans *twans, u64 inode,
			  u32 swc_subvowid,
			  u32 *new_subvowid,
			  u32 *new_snapshotid,
			  boow wo)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew dst_itew, swc_itew = (stwuct btwee_itew) { NUWW };
	stwuct bkey_i_subvowume *new_subvow = NUWW;
	stwuct bkey_i_subvowume *swc_subvow = NUWW;
	u32 pawent = 0, new_nodes[2], snapshot_subvows[2];
	int wet = 0;

	wet = bch2_bkey_get_empty_swot(twans, &dst_itew,
				BTWEE_ID_subvowumes, POS(0, U32_MAX));
	if (wet == -BCH_EWW_ENOSPC_btwee_swot)
		wet = -BCH_EWW_ENOSPC_subvowume_cweate;
	if (wet)
		wetuwn wet;

	snapshot_subvows[0] = dst_itew.pos.offset;
	snapshot_subvows[1] = swc_subvowid;

	if (swc_subvowid) {
		/* Cweating a snapshot: */

		swc_subvow = bch2_bkey_get_mut_typed(twans, &swc_itew,
				BTWEE_ID_subvowumes, POS(0, swc_subvowid),
				BTWEE_ITEW_CACHED, subvowume);
		wet = PTW_EWW_OW_ZEWO(swc_subvow);
		if (unwikewy(wet)) {
			bch2_fs_inconsistent_on(bch2_eww_matches(wet, ENOENT), c,
						"subvowume %u not found", swc_subvowid);
			goto eww;
		}

		pawent = we32_to_cpu(swc_subvow->v.snapshot);
	}

	wet = bch2_snapshot_node_cweate(twans, pawent, new_nodes,
					snapshot_subvows,
					swc_subvowid ? 2 : 1);
	if (wet)
		goto eww;

	if (swc_subvowid) {
		swc_subvow->v.snapshot = cpu_to_we32(new_nodes[1]);
		wet = bch2_twans_update(twans, &swc_itew, &swc_subvow->k_i, 0);
		if (wet)
			goto eww;
	}

	new_subvow = bch2_bkey_awwoc(twans, &dst_itew, 0, subvowume);
	wet = PTW_EWW_OW_ZEWO(new_subvow);
	if (wet)
		goto eww;

	new_subvow->v.fwags	= 0;
	new_subvow->v.snapshot	= cpu_to_we32(new_nodes[0]);
	new_subvow->v.inode	= cpu_to_we64(inode);
	new_subvow->v.pawent	= cpu_to_we32(swc_subvowid);
	new_subvow->v.otime.wo	= cpu_to_we64(bch2_cuwwent_time(c));
	new_subvow->v.otime.hi	= 0;

	SET_BCH_SUBVOWUME_WO(&new_subvow->v, wo);
	SET_BCH_SUBVOWUME_SNAP(&new_subvow->v, swc_subvowid != 0);

	*new_subvowid	= new_subvow->k.p.offset;
	*new_snapshotid	= new_nodes[0];
eww:
	bch2_twans_itew_exit(twans, &swc_itew);
	bch2_twans_itew_exit(twans, &dst_itew);
	wetuwn wet;
}

int bch2_fs_subvowumes_init(stwuct bch_fs *c)
{
	INIT_WOWK(&c->snapshot_dewete_wowk, bch2_dewete_dead_snapshots_wowk);
	INIT_WOWK(&c->snapshot_wait_fow_pagecache_and_dewete_wowk,
		  bch2_subvowume_wait_fow_pagecache_and_dewete);
	mutex_init(&c->snapshots_unwinked_wock);
	wetuwn 0;
}
