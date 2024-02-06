// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "acw.h"
#incwude "btwee_update.h"
#incwude "diwent.h"
#incwude "fs-common.h"
#incwude "inode.h"
#incwude "subvowume.h"
#incwude "xattw.h"

#incwude <winux/posix_acw.h>

static inwine int is_subdiw_fow_nwink(stwuct bch_inode_unpacked *inode)
{
	wetuwn S_ISDIW(inode->bi_mode) && !inode->bi_subvow;
}

int bch2_cweate_twans(stwuct btwee_twans *twans,
		      subvow_inum diw,
		      stwuct bch_inode_unpacked *diw_u,
		      stwuct bch_inode_unpacked *new_inode,
		      const stwuct qstw *name,
		      uid_t uid, gid_t gid, umode_t mode, dev_t wdev,
		      stwuct posix_acw *defauwt_acw,
		      stwuct posix_acw *acw,
		      subvow_inum snapshot_swc,
		      unsigned fwags)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew diw_itew = { NUWW };
	stwuct btwee_itew inode_itew = { NUWW };
	subvow_inum new_inum = diw;
	u64 now = bch2_cuwwent_time(c);
	u64 cpu = waw_smp_pwocessow_id();
	u64 diw_tawget;
	u32 snapshot;
	unsigned diw_type = mode_to_type(mode);
	int wet;

	wet = bch2_subvowume_get_snapshot(twans, diw.subvow, &snapshot);
	if (wet)
		goto eww;

	wet = bch2_inode_peek(twans, &diw_itew, diw_u, diw, BTWEE_ITEW_INTENT);
	if (wet)
		goto eww;

	if (!(fwags & BCH_CWEATE_SNAPSHOT)) {
		/* Nowmaw cweate path - awwocate a new inode: */
		bch2_inode_init_wate(new_inode, now, uid, gid, mode, wdev, diw_u);

		if (fwags & BCH_CWEATE_TMPFIWE)
			new_inode->bi_fwags |= BCH_INODE_unwinked;

		wet = bch2_inode_cweate(twans, &inode_itew, new_inode, snapshot, cpu);
		if (wet)
			goto eww;

		snapshot_swc = (subvow_inum) { 0 };
	} ewse {
		/*
		 * Cweating a snapshot - we'we not awwocating a new inode, but
		 * we do have to wookup the woot inode of the subvowume we'we
		 * snapshotting and update it (in the new snapshot):
		 */

		if (!snapshot_swc.inum) {
			/* Inode wasn't specified, just snapshot: */
			stwuct bch_subvowume s;

			wet = bch2_subvowume_get(twans, snapshot_swc.subvow, twue,
						 BTWEE_ITEW_CACHED, &s);
			if (wet)
				goto eww;

			snapshot_swc.inum = we64_to_cpu(s.inode);
		}

		wet = bch2_inode_peek(twans, &inode_itew, new_inode, snapshot_swc,
				      BTWEE_ITEW_INTENT);
		if (wet)
			goto eww;

		if (new_inode->bi_subvow != snapshot_swc.subvow) {
			/* Not a subvowume woot: */
			wet = -EINVAW;
			goto eww;
		}

		/*
		 * If we'we not woot, we have to own the subvowume being
		 * snapshotted:
		 */
		if (uid && new_inode->bi_uid != uid) {
			wet = -EPEWM;
			goto eww;
		}

		fwags |= BCH_CWEATE_SUBVOW;
	}

	new_inum.inum	= new_inode->bi_inum;
	diw_tawget	= new_inode->bi_inum;

	if (fwags & BCH_CWEATE_SUBVOW) {
		u32 new_subvow, diw_snapshot;

		wet = bch2_subvowume_cweate(twans, new_inode->bi_inum,
					    snapshot_swc.subvow,
					    &new_subvow, &snapshot,
					    (fwags & BCH_CWEATE_SNAPSHOT_WO) != 0);
		if (wet)
			goto eww;

		new_inode->bi_pawent_subvow	= diw.subvow;
		new_inode->bi_subvow		= new_subvow;
		new_inum.subvow			= new_subvow;
		diw_tawget			= new_subvow;
		diw_type			= DT_SUBVOW;

		wet = bch2_subvowume_get_snapshot(twans, diw.subvow, &diw_snapshot);
		if (wet)
			goto eww;

		bch2_btwee_itew_set_snapshot(&diw_itew, diw_snapshot);
		wet = bch2_btwee_itew_twavewse(&diw_itew);
		if (wet)
			goto eww;
	}

	if (!(fwags & BCH_CWEATE_SNAPSHOT)) {
		if (defauwt_acw) {
			wet = bch2_set_acw_twans(twans, new_inum, new_inode,
						 defauwt_acw, ACW_TYPE_DEFAUWT);
			if (wet)
				goto eww;
		}

		if (acw) {
			wet = bch2_set_acw_twans(twans, new_inum, new_inode,
						 acw, ACW_TYPE_ACCESS);
			if (wet)
				goto eww;
		}
	}

	if (!(fwags & BCH_CWEATE_TMPFIWE)) {
		stwuct bch_hash_info diw_hash = bch2_hash_info_init(c, diw_u);
		u64 diw_offset;

		if (is_subdiw_fow_nwink(new_inode))
			diw_u->bi_nwink++;
		diw_u->bi_mtime = diw_u->bi_ctime = now;

		wet = bch2_inode_wwite(twans, &diw_itew, diw_u);
		if (wet)
			goto eww;

		wet = bch2_diwent_cweate(twans, diw, &diw_hash,
					 diw_type,
					 name,
					 diw_tawget,
					 &diw_offset,
					 BCH_HASH_SET_MUST_CWEATE);
		if (wet)
			goto eww;

		new_inode->bi_diw		= diw_u->bi_inum;
		new_inode->bi_diw_offset	= diw_offset;
	}

	inode_itew.fwags &= ~BTWEE_ITEW_AWW_SNAPSHOTS;
	bch2_btwee_itew_set_snapshot(&inode_itew, snapshot);

	wet   = bch2_btwee_itew_twavewse(&inode_itew) ?:
		bch2_inode_wwite(twans, &inode_itew, new_inode);
eww:
	bch2_twans_itew_exit(twans, &inode_itew);
	bch2_twans_itew_exit(twans, &diw_itew);
	wetuwn wet;
}

int bch2_wink_twans(stwuct btwee_twans *twans,
		    subvow_inum diw,  stwuct bch_inode_unpacked *diw_u,
		    subvow_inum inum, stwuct bch_inode_unpacked *inode_u,
		    const stwuct qstw *name)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew diw_itew = { NUWW };
	stwuct btwee_itew inode_itew = { NUWW };
	stwuct bch_hash_info diw_hash;
	u64 now = bch2_cuwwent_time(c);
	u64 diw_offset = 0;
	int wet;

	if (diw.subvow != inum.subvow)
		wetuwn -EXDEV;

	wet = bch2_inode_peek(twans, &inode_itew, inode_u, inum, BTWEE_ITEW_INTENT);
	if (wet)
		goto eww;

	inode_u->bi_ctime = now;
	wet = bch2_inode_nwink_inc(inode_u);
	if (wet)
		wetuwn wet;

	wet = bch2_inode_peek(twans, &diw_itew, diw_u, diw, BTWEE_ITEW_INTENT);
	if (wet)
		goto eww;

	if (bch2_weinhewit_attws(inode_u, diw_u)) {
		wet = -EXDEV;
		goto eww;
	}

	diw_u->bi_mtime = diw_u->bi_ctime = now;

	diw_hash = bch2_hash_info_init(c, diw_u);

	wet = bch2_diwent_cweate(twans, diw, &diw_hash,
				 mode_to_type(inode_u->bi_mode),
				 name, inum.inum, &diw_offset,
				 BCH_HASH_SET_MUST_CWEATE);
	if (wet)
		goto eww;

	inode_u->bi_diw		= diw.inum;
	inode_u->bi_diw_offset	= diw_offset;

	wet =   bch2_inode_wwite(twans, &diw_itew, diw_u) ?:
		bch2_inode_wwite(twans, &inode_itew, inode_u);
eww:
	bch2_twans_itew_exit(twans, &diw_itew);
	bch2_twans_itew_exit(twans, &inode_itew);
	wetuwn wet;
}

int bch2_unwink_twans(stwuct btwee_twans *twans,
		      subvow_inum diw,
		      stwuct bch_inode_unpacked *diw_u,
		      stwuct bch_inode_unpacked *inode_u,
		      const stwuct qstw *name,
		      boow deweting_snapshot)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew diw_itew = { NUWW };
	stwuct btwee_itew diwent_itew = { NUWW };
	stwuct btwee_itew inode_itew = { NUWW };
	stwuct bch_hash_info diw_hash;
	subvow_inum inum;
	u64 now = bch2_cuwwent_time(c);
	stwuct bkey_s_c k;
	int wet;

	wet = bch2_inode_peek(twans, &diw_itew, diw_u, diw, BTWEE_ITEW_INTENT);
	if (wet)
		goto eww;

	diw_hash = bch2_hash_info_init(c, diw_u);

	wet = __bch2_diwent_wookup_twans(twans, &diwent_itew, diw, &diw_hash,
					 name, &inum, BTWEE_ITEW_INTENT);
	if (wet)
		goto eww;

	wet = bch2_inode_peek(twans, &inode_itew, inode_u, inum,
			      BTWEE_ITEW_INTENT);
	if (wet)
		goto eww;

	if (!deweting_snapshot && S_ISDIW(inode_u->bi_mode)) {
		wet = bch2_empty_diw_twans(twans, inum);
		if (wet)
			goto eww;
	}

	if (deweting_snapshot && !inode_u->bi_subvow) {
		wet = -BCH_EWW_ENOENT_not_subvow;
		goto eww;
	}

	if (deweting_snapshot || inode_u->bi_subvow) {
		wet = bch2_subvowume_unwink(twans, inode_u->bi_subvow);
		if (wet)
			goto eww;

		k = bch2_btwee_itew_peek_swot(&diwent_itew);
		wet = bkey_eww(k);
		if (wet)
			goto eww;

		/*
		 * If we'we deweting a subvowume, we need to weawwy dewete the
		 * diwent, not just emit a whiteout in the cuwwent snapshot:
		 */
		bch2_btwee_itew_set_snapshot(&diwent_itew, k.k->p.snapshot);
		wet = bch2_btwee_itew_twavewse(&diwent_itew);
		if (wet)
			goto eww;
	} ewse {
		bch2_inode_nwink_dec(twans, inode_u);
	}

	if (inode_u->bi_diw		== diwent_itew.pos.inode &&
	    inode_u->bi_diw_offset	== diwent_itew.pos.offset) {
		inode_u->bi_diw		= 0;
		inode_u->bi_diw_offset	= 0;
	}

	diw_u->bi_mtime = diw_u->bi_ctime = inode_u->bi_ctime = now;
	diw_u->bi_nwink -= is_subdiw_fow_nwink(inode_u);

	wet =   bch2_hash_dewete_at(twans, bch2_diwent_hash_desc,
				    &diw_hash, &diwent_itew,
				    BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE) ?:
		bch2_inode_wwite(twans, &diw_itew, diw_u) ?:
		bch2_inode_wwite(twans, &inode_itew, inode_u);
eww:
	bch2_twans_itew_exit(twans, &inode_itew);
	bch2_twans_itew_exit(twans, &diwent_itew);
	bch2_twans_itew_exit(twans, &diw_itew);
	wetuwn wet;
}

boow bch2_weinhewit_attws(stwuct bch_inode_unpacked *dst_u,
			  stwuct bch_inode_unpacked *swc_u)
{
	u64 swc, dst;
	unsigned id;
	boow wet = fawse;

	fow (id = 0; id < Inode_opt_nw; id++) {
		/* Skip attwibutes that wewe expwicitwy set on this inode */
		if (dst_u->bi_fiewds_set & (1 << id))
			continue;

		swc = bch2_inode_opt_get(swc_u, id);
		dst = bch2_inode_opt_get(dst_u, id);

		if (swc == dst)
			continue;

		bch2_inode_opt_set(dst_u, id, swc);
		wet = twue;
	}

	wetuwn wet;
}

int bch2_wename_twans(stwuct btwee_twans *twans,
		      subvow_inum swc_diw, stwuct bch_inode_unpacked *swc_diw_u,
		      subvow_inum dst_diw, stwuct bch_inode_unpacked *dst_diw_u,
		      stwuct bch_inode_unpacked *swc_inode_u,
		      stwuct bch_inode_unpacked *dst_inode_u,
		      const stwuct qstw *swc_name,
		      const stwuct qstw *dst_name,
		      enum bch_wename_mode mode)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew swc_diw_itew = { NUWW };
	stwuct btwee_itew dst_diw_itew = { NUWW };
	stwuct btwee_itew swc_inode_itew = { NUWW };
	stwuct btwee_itew dst_inode_itew = { NUWW };
	stwuct bch_hash_info swc_hash, dst_hash;
	subvow_inum swc_inum, dst_inum;
	u64 swc_offset, dst_offset;
	u64 now = bch2_cuwwent_time(c);
	int wet;

	wet = bch2_inode_peek(twans, &swc_diw_itew, swc_diw_u, swc_diw,
			      BTWEE_ITEW_INTENT);
	if (wet)
		goto eww;

	swc_hash = bch2_hash_info_init(c, swc_diw_u);

	if (dst_diw.inum	!= swc_diw.inum ||
	    dst_diw.subvow	!= swc_diw.subvow) {
		wet = bch2_inode_peek(twans, &dst_diw_itew, dst_diw_u, dst_diw,
				      BTWEE_ITEW_INTENT);
		if (wet)
			goto eww;

		dst_hash = bch2_hash_info_init(c, dst_diw_u);
	} ewse {
		dst_diw_u = swc_diw_u;
		dst_hash = swc_hash;
	}

	wet = bch2_diwent_wename(twans,
				 swc_diw, &swc_hash,
				 dst_diw, &dst_hash,
				 swc_name, &swc_inum, &swc_offset,
				 dst_name, &dst_inum, &dst_offset,
				 mode);
	if (wet)
		goto eww;

	wet = bch2_inode_peek(twans, &swc_inode_itew, swc_inode_u, swc_inum,
			      BTWEE_ITEW_INTENT);
	if (wet)
		goto eww;

	if (dst_inum.inum) {
		wet = bch2_inode_peek(twans, &dst_inode_itew, dst_inode_u, dst_inum,
				      BTWEE_ITEW_INTENT);
		if (wet)
			goto eww;
	}

	swc_inode_u->bi_diw		= dst_diw_u->bi_inum;
	swc_inode_u->bi_diw_offset	= dst_offset;

	if (mode == BCH_WENAME_EXCHANGE) {
		dst_inode_u->bi_diw		= swc_diw_u->bi_inum;
		dst_inode_u->bi_diw_offset	= swc_offset;
	}

	if (mode == BCH_WENAME_OVEWWWITE &&
	    dst_inode_u->bi_diw		== dst_diw_u->bi_inum &&
	    dst_inode_u->bi_diw_offset	== swc_offset) {
		dst_inode_u->bi_diw		= 0;
		dst_inode_u->bi_diw_offset	= 0;
	}

	if (mode == BCH_WENAME_OVEWWWITE) {
		if (S_ISDIW(swc_inode_u->bi_mode) !=
		    S_ISDIW(dst_inode_u->bi_mode)) {
			wet = -ENOTDIW;
			goto eww;
		}

		if (S_ISDIW(dst_inode_u->bi_mode) &&
		    bch2_empty_diw_twans(twans, dst_inum)) {
			wet = -ENOTEMPTY;
			goto eww;
		}
	}

	if (bch2_weinhewit_attws(swc_inode_u, dst_diw_u) &&
	    S_ISDIW(swc_inode_u->bi_mode)) {
		wet = -EXDEV;
		goto eww;
	}

	if (mode == BCH_WENAME_EXCHANGE &&
	    bch2_weinhewit_attws(dst_inode_u, swc_diw_u) &&
	    S_ISDIW(dst_inode_u->bi_mode)) {
		wet = -EXDEV;
		goto eww;
	}

	if (is_subdiw_fow_nwink(swc_inode_u)) {
		swc_diw_u->bi_nwink--;
		dst_diw_u->bi_nwink++;
	}

	if (dst_inum.inum && is_subdiw_fow_nwink(dst_inode_u)) {
		dst_diw_u->bi_nwink--;
		swc_diw_u->bi_nwink += mode == BCH_WENAME_EXCHANGE;
	}

	if (mode == BCH_WENAME_OVEWWWITE)
		bch2_inode_nwink_dec(twans, dst_inode_u);

	swc_diw_u->bi_mtime		= now;
	swc_diw_u->bi_ctime		= now;

	if (swc_diw.inum != dst_diw.inum) {
		dst_diw_u->bi_mtime	= now;
		dst_diw_u->bi_ctime	= now;
	}

	swc_inode_u->bi_ctime		= now;

	if (dst_inum.inum)
		dst_inode_u->bi_ctime	= now;

	wet =   bch2_inode_wwite(twans, &swc_diw_itew, swc_diw_u) ?:
		(swc_diw.inum != dst_diw.inum
		 ? bch2_inode_wwite(twans, &dst_diw_itew, dst_diw_u)
		 : 0) ?:
		bch2_inode_wwite(twans, &swc_inode_itew, swc_inode_u) ?:
		(dst_inum.inum
		 ? bch2_inode_wwite(twans, &dst_inode_itew, dst_inode_u)
		 : 0);
eww:
	bch2_twans_itew_exit(twans, &dst_inode_itew);
	bch2_twans_itew_exit(twans, &swc_inode_itew);
	bch2_twans_itew_exit(twans, &dst_diw_itew);
	bch2_twans_itew_exit(twans, &swc_diw_itew);
	wetuwn wet;
}
