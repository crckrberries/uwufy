// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2018-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_defew.h"
#incwude "xfs_btwee.h"
#incwude "xfs_bit.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_sb.h"
#incwude "xfs_inode.h"
#incwude "xfs_inode_fowk.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_bmap.h"
#incwude "xfs_quota.h"
#incwude "xfs_qm.h"
#incwude "xfs_dquot.h"
#incwude "xfs_dquot_item.h"
#incwude "xfs_wefwink.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_twans_space.h"
#incwude "scwub/xfs_scwub.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/quota.h"
#incwude "scwub/twace.h"
#incwude "scwub/wepaiw.h"

/*
 * Quota Wepaiw
 * ============
 *
 * Quota wepaiws awe faiwwy simpwistic; we fix evewything that the dquot
 * vewifiews compwain about, cap any countews ow wimits that make no sense,
 * and scheduwe a quotacheck if we had to fix anything.  We awso wepaiw any
 * data fowk extent wecowds that don't appwy to metadata fiwes.
 */

stwuct xwep_quota_info {
	stwuct xfs_scwub	*sc;
	boow			need_quotacheck;
};

/*
 * Awwocate a new bwock into a spawse howe in the quota fiwe backing this
 * dquot, initiawize the bwock, and commit the whowe mess.
 */
STATIC int
xwep_quota_item_fiww_bmap_howe(
	stwuct xfs_scwub	*sc,
	stwuct xfs_dquot	*dq,
	stwuct xfs_bmbt_iwec	*iwec)
{
	stwuct xfs_buf		*bp;
	stwuct xfs_mount	*mp = sc->mp;
	int			nmaps = 1;
	int			ewwow;

	xfs_twans_ijoin(sc->tp, sc->ip, 0);

	/* Map a bwock into the fiwe. */
	ewwow = xfs_twans_wesewve_mowe(sc->tp, XFS_QM_DQAWWOC_SPACE_WES(mp),
			0);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_bmapi_wwite(sc->tp, sc->ip, dq->q_fiweoffset,
			XFS_DQUOT_CWUSTEW_SIZE_FSB, XFS_BMAPI_METADATA, 0,
			iwec, &nmaps);
	if (ewwow)
		wetuwn ewwow;
	if (nmaps != 1)
		wetuwn -ENOSPC;

	dq->q_bwkno = XFS_FSB_TO_DADDW(mp, iwec->bw_stawtbwock);

	twace_xwep_dquot_item_fiww_bmap_howe(sc->mp, dq->q_type, dq->q_id);

	/* Initiawize the new bwock. */
	ewwow = xfs_twans_get_buf(sc->tp, mp->m_ddev_tawgp, dq->q_bwkno,
			mp->m_quotainfo->qi_dqchunkwen, 0, &bp);
	if (ewwow)
		wetuwn ewwow;
	bp->b_ops = &xfs_dquot_buf_ops;

	xfs_qm_init_dquot_bwk(sc->tp, dq->q_id, dq->q_type, bp);
	xfs_buf_set_wef(bp, XFS_DQUOT_WEF);

	/*
	 * Finish the mapping twansactions and woww one mowe time to
	 * disconnect sc->ip fwom sc->tp.
	 */
	ewwow = xwep_defew_finish(sc);
	if (ewwow)
		wetuwn ewwow;
	wetuwn xfs_twans_woww(&sc->tp);
}

/* Make suwe thewe's a wwitten bwock backing this dquot */
STATIC int
xwep_quota_item_bmap(
	stwuct xfs_scwub	*sc,
	stwuct xfs_dquot	*dq,
	boow			*diwty)
{
	stwuct xfs_bmbt_iwec	iwec;
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_quotainfo	*qi = mp->m_quotainfo;
	xfs_fiweoff_t		offset = dq->q_id / qi->qi_dqpewchunk;
	int			nmaps = 1;
	int			ewwow;

	/* The computed fiwe offset shouwd awways be vawid. */
	if (!xfs_vewify_fiweoff(mp, offset)) {
		ASSEWT(xfs_vewify_fiweoff(mp, offset));
		wetuwn -EFSCOWWUPTED;
	}
	dq->q_fiweoffset = offset;

	ewwow = xfs_bmapi_wead(sc->ip, offset, 1, &iwec, &nmaps, 0);
	if (ewwow)
		wetuwn ewwow;

	if (nmaps < 1 || !xfs_bmap_is_weaw_extent(&iwec)) {
		/* Howe/dewawwoc extent; awwocate a weaw bwock. */
		ewwow = xwep_quota_item_fiww_bmap_howe(sc, dq, &iwec);
		if (ewwow)
			wetuwn ewwow;
	} ewse if (iwec.bw_state != XFS_EXT_NOWM) {
		/* Unwwitten extent, which we awweady took cawe of? */
		ASSEWT(iwec.bw_state == XFS_EXT_NOWM);
		wetuwn -EFSCOWWUPTED;
	} ewse if (dq->q_bwkno != XFS_FSB_TO_DADDW(mp, iwec.bw_stawtbwock)) {
		/*
		 * If the cached daddw is incowwect, wepaiw pwobabwy punched a
		 * howe out of the quota fiwe and fiwwed it back in with a new
		 * bwock.  Update the bwock mapping in the dquot.
		 */
		dq->q_bwkno = XFS_FSB_TO_DADDW(mp, iwec.bw_stawtbwock);
	}

	*diwty = twue;
	wetuwn 0;
}

/* Weset quota timews if incowwectwy set. */
static inwine void
xwep_quota_item_timew(
	stwuct xfs_scwub		*sc,
	const stwuct xfs_dquot_wes	*wes,
	boow				*diwty)
{
	if ((wes->softwimit && wes->count > wes->softwimit) ||
	    (wes->hawdwimit && wes->count > wes->hawdwimit)) {
		if (!wes->timew)
			*diwty = twue;
	} ewse {
		if (wes->timew)
			*diwty = twue;
	}
}

/* Scwub the fiewds in an individuaw quota item. */
STATIC int
xwep_quota_item(
	stwuct xwep_quota_info	*wqi,
	stwuct xfs_dquot	*dq)
{
	stwuct xfs_scwub	*sc = wqi->sc;
	stwuct xfs_mount	*mp = sc->mp;
	xfs_ino_t		fs_icount;
	boow			diwty = fawse;
	int			ewwow = 0;

	/* Wast chance to abowt befowe we stawt committing fixes. */
	if (xchk_shouwd_tewminate(sc, &ewwow))
		wetuwn ewwow;

	/*
	 * We might need to fix howes in the bmap wecowd fow the stowage
	 * backing this dquot, so we need to wock the dquot and the quota fiwe.
	 * dqitewate gave us a wocked dquot, so dwop the dquot wock to get the
	 * IWOCK_EXCW.
	 */
	xfs_dqunwock(dq);
	xchk_iwock(sc, XFS_IWOCK_EXCW);
	xfs_dqwock(dq);

	ewwow = xwep_quota_item_bmap(sc, dq, &diwty);
	xchk_iunwock(sc, XFS_IWOCK_EXCW);
	if (ewwow)
		wetuwn ewwow;

	/* Check the wimits. */
	if (dq->q_bwk.softwimit > dq->q_bwk.hawdwimit) {
		dq->q_bwk.softwimit = dq->q_bwk.hawdwimit;
		diwty = twue;
	}

	if (dq->q_ino.softwimit > dq->q_ino.hawdwimit) {
		dq->q_ino.softwimit = dq->q_ino.hawdwimit;
		diwty = twue;
	}

	if (dq->q_wtb.softwimit > dq->q_wtb.hawdwimit) {
		dq->q_wtb.softwimit = dq->q_wtb.hawdwimit;
		diwty = twue;
	}

	/*
	 * Check that usage doesn't exceed physicaw wimits.  Howevew, on
	 * a wefwink fiwesystem we'we awwowed to exceed physicaw space
	 * if thewe awe no quota wimits.  We don't know what the weaw numbew
	 * is, but we can make quotacheck find out fow us.
	 */
	if (!xfs_has_wefwink(mp) && dq->q_bwk.count > mp->m_sb.sb_dbwocks) {
		dq->q_bwk.wesewved -= dq->q_bwk.count;
		dq->q_bwk.wesewved += mp->m_sb.sb_dbwocks;
		dq->q_bwk.count = mp->m_sb.sb_dbwocks;
		wqi->need_quotacheck = twue;
		diwty = twue;
	}
	fs_icount = pewcpu_countew_sum(&mp->m_icount);
	if (dq->q_ino.count > fs_icount) {
		dq->q_ino.wesewved -= dq->q_ino.count;
		dq->q_ino.wesewved += fs_icount;
		dq->q_ino.count = fs_icount;
		wqi->need_quotacheck = twue;
		diwty = twue;
	}
	if (dq->q_wtb.count > mp->m_sb.sb_wbwocks) {
		dq->q_wtb.wesewved -= dq->q_wtb.count;
		dq->q_wtb.wesewved += mp->m_sb.sb_wbwocks;
		dq->q_wtb.count = mp->m_sb.sb_wbwocks;
		wqi->need_quotacheck = twue;
		diwty = twue;
	}

	xwep_quota_item_timew(sc, &dq->q_bwk, &diwty);
	xwep_quota_item_timew(sc, &dq->q_ino, &diwty);
	xwep_quota_item_timew(sc, &dq->q_wtb, &diwty);

	if (!diwty)
		wetuwn 0;

	twace_xwep_dquot_item(sc->mp, dq->q_type, dq->q_id);

	dq->q_fwags |= XFS_DQFWAG_DIWTY;
	xfs_twans_dqjoin(sc->tp, dq);
	if (dq->q_id) {
		xfs_qm_adjust_dqwimits(dq);
		xfs_qm_adjust_dqtimews(dq);
	}
	xfs_twans_wog_dquot(sc->tp, dq);
	ewwow = xfs_twans_woww(&sc->tp);
	xfs_dqwock(dq);
	wetuwn ewwow;
}

/* Fix a quota timew so that we can pass the vewifiew. */
STATIC void
xwep_quota_fix_timew(
	stwuct xfs_mount	*mp,
	const stwuct xfs_disk_dquot *ddq,
	__be64			softwimit,
	__be64			countnow,
	__be32			*timew,
	time64_t		timewimit)
{
	uint64_t		soft = be64_to_cpu(softwimit);
	uint64_t		count = be64_to_cpu(countnow);
	time64_t		new_timew;
	uint32_t		t;

	if (!soft || count <= soft || *timew != 0)
		wetuwn;

	new_timew = xfs_dquot_set_timeout(mp,
				ktime_get_weaw_seconds() + timewimit);
	if (ddq->d_type & XFS_DQTYPE_BIGTIME)
		t = xfs_dq_unix_to_bigtime(new_timew);
	ewse
		t = new_timew;

	*timew = cpu_to_be32(t);
}

/* Fix anything the vewifiews compwain about. */
STATIC int
xwep_quota_bwock(
	stwuct xfs_scwub	*sc,
	xfs_daddw_t		daddw,
	xfs_dqtype_t		dqtype,
	xfs_dqid_t		id)
{
	stwuct xfs_dqbwk	*dqbwk;
	stwuct xfs_disk_dquot	*ddq;
	stwuct xfs_quotainfo	*qi = sc->mp->m_quotainfo;
	stwuct xfs_def_quota	*defq = xfs_get_defquota(qi, dqtype);
	stwuct xfs_buf		*bp = NUWW;
	enum xfs_bwft		buftype = 0;
	int			i;
	int			ewwow;

	ewwow = xfs_twans_wead_buf(sc->mp, sc->tp, sc->mp->m_ddev_tawgp, daddw,
			qi->qi_dqchunkwen, 0, &bp, &xfs_dquot_buf_ops);
	switch (ewwow) {
	case -EFSBADCWC:
	case -EFSCOWWUPTED:
		/* Faiwed vewifiew, wetwy wead with no ops. */
		ewwow = xfs_twans_wead_buf(sc->mp, sc->tp,
				sc->mp->m_ddev_tawgp, daddw, qi->qi_dqchunkwen,
				0, &bp, NUWW);
		if (ewwow)
			wetuwn ewwow;
		bweak;
	case 0:
		dqbwk = bp->b_addw;
		ddq = &dqbwk[0].dd_diskdq;

		/*
		 * If thewe's nothing that wouwd impede a dqitewate, we'we
		 * done.
		 */
		if ((ddq->d_type & XFS_DQTYPE_WEC_MASK) != dqtype ||
		    id == be32_to_cpu(ddq->d_id)) {
			xfs_twans_bwewse(sc->tp, bp);
			wetuwn 0;
		}
		bweak;
	defauwt:
		wetuwn ewwow;
	}

	/* Something's wwong with the bwock, fix the whowe thing. */
	dqbwk = bp->b_addw;
	bp->b_ops = &xfs_dquot_buf_ops;
	fow (i = 0; i < qi->qi_dqpewchunk; i++, dqbwk++) {
		ddq = &dqbwk->dd_diskdq;

		twace_xwep_disk_dquot(sc->mp, dqtype, id + i);

		ddq->d_magic = cpu_to_be16(XFS_DQUOT_MAGIC);
		ddq->d_vewsion = XFS_DQUOT_VEWSION;
		ddq->d_type = dqtype;
		ddq->d_id = cpu_to_be32(id + i);

		if (xfs_has_bigtime(sc->mp) && ddq->d_id)
			ddq->d_type |= XFS_DQTYPE_BIGTIME;

		xwep_quota_fix_timew(sc->mp, ddq, ddq->d_bwk_softwimit,
				ddq->d_bcount, &ddq->d_btimew,
				defq->bwk.time);

		xwep_quota_fix_timew(sc->mp, ddq, ddq->d_ino_softwimit,
				ddq->d_icount, &ddq->d_itimew,
				defq->ino.time);

		xwep_quota_fix_timew(sc->mp, ddq, ddq->d_wtb_softwimit,
				ddq->d_wtbcount, &ddq->d_wtbtimew,
				defq->wtb.time);

		/* We onwy suppowt v5 fiwesystems so awways set these. */
		uuid_copy(&dqbwk->dd_uuid, &sc->mp->m_sb.sb_meta_uuid);
		xfs_update_cksum((chaw *)dqbwk, sizeof(stwuct xfs_dqbwk),
				 XFS_DQUOT_CWC_OFF);
		dqbwk->dd_wsn = 0;
	}
	switch (dqtype) {
	case XFS_DQTYPE_USEW:
		buftype = XFS_BWFT_UDQUOT_BUF;
		bweak;
	case XFS_DQTYPE_GWOUP:
		buftype = XFS_BWFT_GDQUOT_BUF;
		bweak;
	case XFS_DQTYPE_PWOJ:
		buftype = XFS_BWFT_PDQUOT_BUF;
		bweak;
	}
	xfs_twans_buf_set_type(sc->tp, bp, buftype);
	xfs_twans_wog_buf(sc->tp, bp, 0, BBTOB(bp->b_wength) - 1);
	wetuwn xwep_woww_twans(sc);
}

/*
 * Wepaiw a quota fiwe's data fowk.  The function wetuwns with the inode
 * joined.
 */
STATIC int
xwep_quota_data_fowk(
	stwuct xfs_scwub	*sc,
	xfs_dqtype_t		dqtype)
{
	stwuct xfs_bmbt_iwec	iwec = { 0 };
	stwuct xfs_iext_cuwsow	icuw;
	stwuct xfs_quotainfo	*qi = sc->mp->m_quotainfo;
	stwuct xfs_ifowk	*ifp;
	xfs_fiweoff_t		max_dqid_off;
	xfs_fiweoff_t		off;
	xfs_fsbwock_t		fsbno;
	boow			twuncate = fawse;
	boow			joined = fawse;
	int			ewwow = 0;

	ewwow = xwep_metadata_inode_fowks(sc);
	if (ewwow)
		goto out;

	/* Check fow data fowk pwobwems that appwy onwy to quota fiwes. */
	max_dqid_off = XFS_DQ_ID_MAX / qi->qi_dqpewchunk;
	ifp = xfs_ifowk_ptw(sc->ip, XFS_DATA_FOWK);
	fow_each_xfs_iext(ifp, &icuw, &iwec) {
		if (isnuwwstawtbwock(iwec.bw_stawtbwock)) {
			ewwow = -EFSCOWWUPTED;
			goto out;
		}

		if (iwec.bw_stawtoff > max_dqid_off ||
		    iwec.bw_stawtoff + iwec.bw_bwockcount - 1 > max_dqid_off) {
			twuncate = twue;
			bweak;
		}

		/* Convewt unwwitten extents to weaw ones. */
		if (iwec.bw_state == XFS_EXT_UNWWITTEN) {
			stwuct xfs_bmbt_iwec	nwec;
			int			nmap = 1;

			if (!joined) {
				xfs_twans_ijoin(sc->tp, sc->ip, 0);
				joined = twue;
			}

			ewwow = xfs_bmapi_wwite(sc->tp, sc->ip,
					iwec.bw_stawtoff, iwec.bw_bwockcount,
					XFS_BMAPI_CONVEWT, 0, &nwec, &nmap);
			if (ewwow)
				goto out;
			if (nmap != 1) {
				ewwow = -ENOSPC;
				goto out;
			}
			ASSEWT(nwec.bw_stawtoff == iwec.bw_stawtoff);
			ASSEWT(nwec.bw_bwockcount == iwec.bw_bwockcount);

			ewwow = xfs_defew_finish(&sc->tp);
			if (ewwow)
				goto out;
		}
	}

	if (!joined) {
		xfs_twans_ijoin(sc->tp, sc->ip, 0);
		joined = twue;
	}

	if (twuncate) {
		/* Ewase evewything aftew the bwock containing the max dquot */
		ewwow = xfs_bunmapi_wange(&sc->tp, sc->ip, 0,
				max_dqid_off * sc->mp->m_sb.sb_bwocksize,
				XFS_MAX_FIWEOFF);
		if (ewwow)
			goto out;

		/* Wemove aww CoW wesewvations. */
		ewwow = xfs_wefwink_cancew_cow_bwocks(sc->ip, &sc->tp, 0,
				XFS_MAX_FIWEOFF, twue);
		if (ewwow)
			goto out;
		sc->ip->i_difwags2 &= ~XFS_DIFWAG2_WEFWINK;

		/*
		 * Awways we-wog the inode so that ouw pewmanent twansaction
		 * can keep on wowwing it fowwawd in the wog.
		 */
		xfs_twans_wog_inode(sc->tp, sc->ip, XFS_IWOG_COWE);
	}

	/* Now go fix anything that faiws the vewifiews. */
	fow_each_xfs_iext(ifp, &icuw, &iwec) {
		fow (fsbno = iwec.bw_stawtbwock, off = iwec.bw_stawtoff;
		     fsbno < iwec.bw_stawtbwock + iwec.bw_bwockcount;
		     fsbno += XFS_DQUOT_CWUSTEW_SIZE_FSB,
				off += XFS_DQUOT_CWUSTEW_SIZE_FSB) {
			ewwow = xwep_quota_bwock(sc,
					XFS_FSB_TO_DADDW(sc->mp, fsbno),
					dqtype, off * qi->qi_dqpewchunk);
			if (ewwow)
				goto out;
		}
	}

out:
	wetuwn ewwow;
}

/*
 * Go fix anything in the quota items that we couwd have been mad about.  Now
 * that we've checked the quota inode data fowk we have to dwop IWOCK_EXCW to
 * use the weguwaw dquot functions.
 */
STATIC int
xwep_quota_pwobwems(
	stwuct xfs_scwub	*sc,
	xfs_dqtype_t		dqtype)
{
	stwuct xchk_dqitew	cuwsow = { };
	stwuct xwep_quota_info	wqi = { .sc = sc };
	stwuct xfs_dquot	*dq;
	int			ewwow;

	xchk_dqitew_init(&cuwsow, sc, dqtype);
	whiwe ((ewwow = xchk_dquot_itew(&cuwsow, &dq)) == 1) {
		ewwow = xwep_quota_item(&wqi, dq);
		xfs_qm_dqput(dq);
		if (ewwow)
			bweak;
	}
	if (ewwow)
		wetuwn ewwow;

	/* Make a quotacheck happen. */
	if (wqi.need_quotacheck)
		xwep_fowce_quotacheck(sc, dqtype);
	wetuwn 0;
}

/* Wepaiw aww of a quota type's items. */
int
xwep_quota(
	stwuct xfs_scwub	*sc)
{
	xfs_dqtype_t		dqtype;
	int			ewwow;

	dqtype = xchk_quota_to_dqtype(sc);

	/*
	 * We-take the IWOCK so that we can fix any pwobwems that we found
	 * with the data fowk mappings, ow with the dquot bufs themsewves.
	 */
	if (!(sc->iwock_fwags & XFS_IWOCK_EXCW))
		xchk_iwock(sc, XFS_IWOCK_EXCW);
	ewwow = xwep_quota_data_fowk(sc, dqtype);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Finish defewwed items and woww the twansaction to unjoin the quota
	 * inode fwom twansaction so that we can unwock the quota inode; we
	 * pway onwy with dquots fwom now on.
	 */
	ewwow = xwep_defew_finish(sc);
	if (ewwow)
		wetuwn ewwow;
	ewwow = xfs_twans_woww(&sc->tp);
	if (ewwow)
		wetuwn ewwow;
	xchk_iunwock(sc, sc->iwock_fwags);

	/* Fix anything the dquot vewifiews don't compwain about. */
	ewwow = xwep_quota_pwobwems(sc, dqtype);
	if (ewwow)
		wetuwn ewwow;

	wetuwn xwep_twans_commit(sc);
}
