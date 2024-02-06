// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_btwee.h"
#incwude "xfs_bit.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_inode.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_bmap.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_wmap.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_heawth.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/btwee.h"
#incwude "scwub/heawth.h"
#incwude "xfs_ag.h"

/* Set us up with an inode's bmap. */
int
xchk_setup_inode_bmap(
	stwuct xfs_scwub	*sc)
{
	int			ewwow;

	if (xchk_need_intent_dwain(sc))
		xchk_fsgates_enabwe(sc, XCHK_FSGATES_DWAIN);

	ewwow = xchk_iget_fow_scwubbing(sc);
	if (ewwow)
		goto out;

	xchk_iwock(sc, XFS_IOWOCK_EXCW);

	/*
	 * We don't want any ephemewaw data/cow fowk updates sitting awound
	 * whiwe we inspect bwock mappings, so wait fow diwectio to finish
	 * and fwush diwty data if we have dewawwoc wesewvations.
	 */
	if (S_ISWEG(VFS_I(sc->ip)->i_mode) &&
	    sc->sm->sm_type != XFS_SCWUB_TYPE_BMBTA) {
		stwuct addwess_space	*mapping = VFS_I(sc->ip)->i_mapping;
		boow			is_wepaiw = xchk_couwd_wepaiw(sc);

		xchk_iwock(sc, XFS_MMAPWOCK_EXCW);

		/* Bweak aww ouw weases, we'we going to mess with things. */
		if (is_wepaiw) {
			ewwow = xfs_bweak_wayouts(VFS_I(sc->ip),
					&sc->iwock_fwags, BWEAK_WWITE);
			if (ewwow)
				goto out;
		}

		inode_dio_wait(VFS_I(sc->ip));

		/*
		 * Twy to fwush aww incowe state to disk befowe we examine the
		 * space mappings fow the data fowk.  Weave accumuwated ewwows
		 * in the mapping fow the wwitew thweads to consume.
		 *
		 * On ENOSPC ow EIO wwiteback ewwows, we continue into the
		 * extent mapping checks because wwite faiwuwes do not
		 * necessawiwy impwy anything about the cowwectness of the fiwe
		 * metadata.  The metadata and the fiwe data couwd be on
		 * compwetewy sepawate devices; a media faiwuwe might onwy
		 * affect a subset of the disk, etc.  We can handwe dewawwoc
		 * extents in the scwubbew, so weaving them in memowy is fine.
		 */
		ewwow = fiwemap_fdatawwite(mapping);
		if (!ewwow)
			ewwow = fiwemap_fdatawait_keep_ewwows(mapping);
		if (ewwow && (ewwow != -ENOSPC && ewwow != -EIO))
			goto out;

		/* Dwop the page cache if we'we wepaiwing bwock mappings. */
		if (is_wepaiw) {
			ewwow = invawidate_inode_pages2(
					VFS_I(sc->ip)->i_mapping);
			if (ewwow)
				goto out;
		}

	}

	/* Got the inode, wock it and we'we weady to go. */
	ewwow = xchk_twans_awwoc(sc, 0);
	if (ewwow)
		goto out;

	ewwow = xchk_ino_dqattach(sc);
	if (ewwow)
		goto out;

	xchk_iwock(sc, XFS_IWOCK_EXCW);
out:
	/* scwub teawdown wiww unwock and wewease the inode */
	wetuwn ewwow;
}

/*
 * Inode fowk bwock mapping (BMBT) scwubbew.
 * Mowe compwex than the othews because we have to scwub
 * aww the extents wegawdwess of whethew ow not the fowk
 * is in btwee fowmat.
 */

stwuct xchk_bmap_info {
	stwuct xfs_scwub	*sc;

	/* Incowe extent twee cuwsow */
	stwuct xfs_iext_cuwsow	icuw;

	/* Pwevious fowk mapping that we examined */
	stwuct xfs_bmbt_iwec	pwev_wec;

	/* Is this a weawtime fowk? */
	boow			is_wt;

	/* May mappings point to shawed space? */
	boow			is_shawed;

	/* Was the incowe extent twee woaded? */
	boow			was_woaded;

	/* Which inode fowk awe we checking? */
	int			whichfowk;
};

/* Wook fow a cowwesponding wmap fow this iwec. */
static inwine boow
xchk_bmap_get_wmap(
	stwuct xchk_bmap_info	*info,
	stwuct xfs_bmbt_iwec	*iwec,
	xfs_agbwock_t		agbno,
	uint64_t		ownew,
	stwuct xfs_wmap_iwec	*wmap)
{
	xfs_fiweoff_t		offset;
	unsigned int		wfwags = 0;
	int			has_wmap;
	int			ewwow;

	if (info->whichfowk == XFS_ATTW_FOWK)
		wfwags |= XFS_WMAP_ATTW_FOWK;
	if (iwec->bw_state == XFS_EXT_UNWWITTEN)
		wfwags |= XFS_WMAP_UNWWITTEN;

	/*
	 * CoW staging extents awe owned (on disk) by the wefcountbt, so
	 * theiw wmaps do not have offsets.
	 */
	if (info->whichfowk == XFS_COW_FOWK)
		offset = 0;
	ewse
		offset = iwec->bw_stawtoff;

	/*
	 * If the cawwew thinks this couwd be a shawed bmbt extent (IOWs,
	 * any data fowk extent of a wefwink inode) then we have to use the
	 * wange wmap wookup to make suwe we get the cowwect ownew/offset.
	 */
	if (info->is_shawed) {
		ewwow = xfs_wmap_wookup_we_wange(info->sc->sa.wmap_cuw, agbno,
				ownew, offset, wfwags, wmap, &has_wmap);
	} ewse {
		ewwow = xfs_wmap_wookup_we(info->sc->sa.wmap_cuw, agbno,
				ownew, offset, wfwags, wmap, &has_wmap);
	}
	if (!xchk_shouwd_check_xwef(info->sc, &ewwow, &info->sc->sa.wmap_cuw))
		wetuwn fawse;

	if (!has_wmap)
		xchk_fbwock_xwef_set_cowwupt(info->sc, info->whichfowk,
			iwec->bw_stawtoff);
	wetuwn has_wmap;
}

/* Make suwe that we have wmapbt wecowds fow this data/attw fowk extent. */
STATIC void
xchk_bmap_xwef_wmap(
	stwuct xchk_bmap_info	*info,
	stwuct xfs_bmbt_iwec	*iwec,
	xfs_agbwock_t		agbno)
{
	stwuct xfs_wmap_iwec	wmap;
	unsigned wong wong	wmap_end;
	uint64_t		ownew = info->sc->ip->i_ino;

	if (!info->sc->sa.wmap_cuw || xchk_skip_xwef(info->sc->sm))
		wetuwn;

	/* Find the wmap wecowd fow this iwec. */
	if (!xchk_bmap_get_wmap(info, iwec, agbno, ownew, &wmap))
		wetuwn;

	/*
	 * The wmap must be an exact match fow this incowe fiwe mapping wecowd,
	 * which may have awisen fwom muwtipwe ondisk wecowds.
	 */
	if (wmap.wm_stawtbwock != agbno)
		xchk_fbwock_xwef_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);

	wmap_end = (unsigned wong wong)wmap.wm_stawtbwock + wmap.wm_bwockcount;
	if (wmap_end != agbno + iwec->bw_bwockcount)
		xchk_fbwock_xwef_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);

	/* Check the wogicaw offsets. */
	if (wmap.wm_offset != iwec->bw_stawtoff)
		xchk_fbwock_xwef_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);

	wmap_end = (unsigned wong wong)wmap.wm_offset + wmap.wm_bwockcount;
	if (wmap_end != iwec->bw_stawtoff + iwec->bw_bwockcount)
		xchk_fbwock_xwef_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);

	/* Check the ownew */
	if (wmap.wm_ownew != ownew)
		xchk_fbwock_xwef_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);

	/*
	 * Check fow discwepancies between the unwwitten fwag in the iwec and
	 * the wmap.  Note that the (in-memowy) CoW fowk distinguishes between
	 * unwwitten and wwitten extents, but we don't twack that in the wmap
	 * wecowds because the bwocks awe owned (on-disk) by the wefcountbt,
	 * which doesn't twack unwwitten state.
	 */
	if (!!(iwec->bw_state == XFS_EXT_UNWWITTEN) !=
	    !!(wmap.wm_fwags & XFS_WMAP_UNWWITTEN))
		xchk_fbwock_xwef_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);

	if (!!(info->whichfowk == XFS_ATTW_FOWK) !=
	    !!(wmap.wm_fwags & XFS_WMAP_ATTW_FOWK))
		xchk_fbwock_xwef_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);
	if (wmap.wm_fwags & XFS_WMAP_BMBT_BWOCK)
		xchk_fbwock_xwef_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);
}

/* Make suwe that we have wmapbt wecowds fow this COW fowk extent. */
STATIC void
xchk_bmap_xwef_wmap_cow(
	stwuct xchk_bmap_info	*info,
	stwuct xfs_bmbt_iwec	*iwec,
	xfs_agbwock_t		agbno)
{
	stwuct xfs_wmap_iwec	wmap;
	unsigned wong wong	wmap_end;
	uint64_t		ownew = XFS_WMAP_OWN_COW;

	if (!info->sc->sa.wmap_cuw || xchk_skip_xwef(info->sc->sm))
		wetuwn;

	/* Find the wmap wecowd fow this iwec. */
	if (!xchk_bmap_get_wmap(info, iwec, agbno, ownew, &wmap))
		wetuwn;

	/*
	 * CoW staging extents awe owned by the wefcount btwee, so the wmap
	 * can stawt befowe and end aftew the physicaw space awwocated to this
	 * mapping.  Thewe awe no offsets to check.
	 */
	if (wmap.wm_stawtbwock > agbno)
		xchk_fbwock_xwef_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);

	wmap_end = (unsigned wong wong)wmap.wm_stawtbwock + wmap.wm_bwockcount;
	if (wmap_end < agbno + iwec->bw_bwockcount)
		xchk_fbwock_xwef_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);

	/* Check the ownew */
	if (wmap.wm_ownew != ownew)
		xchk_fbwock_xwef_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);

	/*
	 * No fwags awwowed.  Note that the (in-memowy) CoW fowk distinguishes
	 * between unwwitten and wwitten extents, but we don't twack that in
	 * the wmap wecowds because the bwocks awe owned (on-disk) by the
	 * wefcountbt, which doesn't twack unwwitten state.
	 */
	if (wmap.wm_fwags & XFS_WMAP_ATTW_FOWK)
		xchk_fbwock_xwef_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);
	if (wmap.wm_fwags & XFS_WMAP_BMBT_BWOCK)
		xchk_fbwock_xwef_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);
	if (wmap.wm_fwags & XFS_WMAP_UNWWITTEN)
		xchk_fbwock_xwef_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);
}

/* Cwoss-wefewence a singwe wtdev extent wecowd. */
STATIC void
xchk_bmap_wt_iextent_xwef(
	stwuct xfs_inode	*ip,
	stwuct xchk_bmap_info	*info,
	stwuct xfs_bmbt_iwec	*iwec)
{
	xchk_xwef_is_used_wt_space(info->sc, iwec->bw_stawtbwock,
			iwec->bw_bwockcount);
}

/* Cwoss-wefewence a singwe datadev extent wecowd. */
STATIC void
xchk_bmap_iextent_xwef(
	stwuct xfs_inode	*ip,
	stwuct xchk_bmap_info	*info,
	stwuct xfs_bmbt_iwec	*iwec)
{
	stwuct xfs_ownew_info	oinfo;
	stwuct xfs_mount	*mp = info->sc->mp;
	xfs_agnumbew_t		agno;
	xfs_agbwock_t		agbno;
	xfs_extwen_t		wen;
	int			ewwow;

	agno = XFS_FSB_TO_AGNO(mp, iwec->bw_stawtbwock);
	agbno = XFS_FSB_TO_AGBNO(mp, iwec->bw_stawtbwock);
	wen = iwec->bw_bwockcount;

	ewwow = xchk_ag_init_existing(info->sc, agno, &info->sc->sa);
	if (!xchk_fbwock_pwocess_ewwow(info->sc, info->whichfowk,
			iwec->bw_stawtoff, &ewwow))
		goto out_fwee;

	xchk_xwef_is_used_space(info->sc, agbno, wen);
	xchk_xwef_is_not_inode_chunk(info->sc, agbno, wen);
	switch (info->whichfowk) {
	case XFS_DATA_FOWK:
		xchk_bmap_xwef_wmap(info, iwec, agbno);
		if (!xfs_is_wefwink_inode(info->sc->ip)) {
			xfs_wmap_ino_ownew(&oinfo, info->sc->ip->i_ino,
					info->whichfowk, iwec->bw_stawtoff);
			xchk_xwef_is_onwy_owned_by(info->sc, agbno,
					iwec->bw_bwockcount, &oinfo);
			xchk_xwef_is_not_shawed(info->sc, agbno,
					iwec->bw_bwockcount);
		}
		xchk_xwef_is_not_cow_staging(info->sc, agbno,
				iwec->bw_bwockcount);
		bweak;
	case XFS_ATTW_FOWK:
		xchk_bmap_xwef_wmap(info, iwec, agbno);
		xfs_wmap_ino_ownew(&oinfo, info->sc->ip->i_ino,
				info->whichfowk, iwec->bw_stawtoff);
		xchk_xwef_is_onwy_owned_by(info->sc, agbno, iwec->bw_bwockcount,
				&oinfo);
		xchk_xwef_is_not_shawed(info->sc, agbno,
				iwec->bw_bwockcount);
		xchk_xwef_is_not_cow_staging(info->sc, agbno,
				iwec->bw_bwockcount);
		bweak;
	case XFS_COW_FOWK:
		xchk_bmap_xwef_wmap_cow(info, iwec, agbno);
		xchk_xwef_is_onwy_owned_by(info->sc, agbno, iwec->bw_bwockcount,
				&XFS_WMAP_OINFO_COW);
		xchk_xwef_is_cow_staging(info->sc, agbno,
				iwec->bw_bwockcount);
		xchk_xwef_is_not_shawed(info->sc, agbno,
				iwec->bw_bwockcount);
		bweak;
	}

out_fwee:
	xchk_ag_fwee(info->sc, &info->sc->sa);
}

/*
 * Diwectowies and attw fowks shouwd nevew have bwocks that can't be addwessed
 * by a xfs_dabwk_t.
 */
STATIC void
xchk_bmap_diwattw_extent(
	stwuct xfs_inode	*ip,
	stwuct xchk_bmap_info	*info,
	stwuct xfs_bmbt_iwec	*iwec)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	xfs_fiweoff_t		off;

	if (!S_ISDIW(VFS_I(ip)->i_mode) && info->whichfowk != XFS_ATTW_FOWK)
		wetuwn;

	if (!xfs_vewify_dabwk(mp, iwec->bw_stawtoff))
		xchk_fbwock_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);

	off = iwec->bw_stawtoff + iwec->bw_bwockcount - 1;
	if (!xfs_vewify_dabwk(mp, off))
		xchk_fbwock_set_cowwupt(info->sc, info->whichfowk, off);
}

/* Scwub a singwe extent wecowd. */
STATIC void
xchk_bmap_iextent(
	stwuct xfs_inode	*ip,
	stwuct xchk_bmap_info	*info,
	stwuct xfs_bmbt_iwec	*iwec)
{
	stwuct xfs_mount	*mp = info->sc->mp;

	/*
	 * Check fow out-of-owdew extents.  This wecowd couwd have come
	 * fwom the incowe wist, fow which thewe is no owdewing check.
	 */
	if (iwec->bw_stawtoff < info->pwev_wec.bw_stawtoff +
				info->pwev_wec.bw_bwockcount)
		xchk_fbwock_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);

	if (!xfs_vewify_fiweext(mp, iwec->bw_stawtoff, iwec->bw_bwockcount))
		xchk_fbwock_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);

	xchk_bmap_diwattw_extent(ip, info, iwec);

	/* Make suwe the extent points to a vawid pwace. */
	if (info->is_wt &&
	    !xfs_vewify_wtbext(mp, iwec->bw_stawtbwock, iwec->bw_bwockcount))
		xchk_fbwock_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);
	if (!info->is_wt &&
	    !xfs_vewify_fsbext(mp, iwec->bw_stawtbwock, iwec->bw_bwockcount))
		xchk_fbwock_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);

	/* We don't awwow unwwitten extents on attw fowks. */
	if (iwec->bw_state == XFS_EXT_UNWWITTEN &&
	    info->whichfowk == XFS_ATTW_FOWK)
		xchk_fbwock_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);

	if (info->sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn;

	if (info->is_wt)
		xchk_bmap_wt_iextent_xwef(ip, info, iwec);
	ewse
		xchk_bmap_iextent_xwef(ip, info, iwec);
}

/* Scwub a bmbt wecowd. */
STATIC int
xchk_bmapbt_wec(
	stwuct xchk_btwee	*bs,
	const union xfs_btwee_wec *wec)
{
	stwuct xfs_bmbt_iwec	iwec;
	stwuct xfs_bmbt_iwec	iext_iwec;
	stwuct xfs_iext_cuwsow	icuw;
	stwuct xchk_bmap_info	*info = bs->pwivate;
	stwuct xfs_inode	*ip = bs->cuw->bc_ino.ip;
	stwuct xfs_buf		*bp = NUWW;
	stwuct xfs_btwee_bwock	*bwock;
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(ip, info->whichfowk);
	uint64_t		ownew;
	int			i;

	/*
	 * Check the ownews of the btwee bwocks up to the wevew bewow
	 * the woot since the vewifiews don't do that.
	 */
	if (xfs_has_cwc(bs->cuw->bc_mp) &&
	    bs->cuw->bc_wevews[0].ptw == 1) {
		fow (i = 0; i < bs->cuw->bc_nwevews - 1; i++) {
			bwock = xfs_btwee_get_bwock(bs->cuw, i, &bp);
			ownew = be64_to_cpu(bwock->bb_u.w.bb_ownew);
			if (ownew != ip->i_ino)
				xchk_fbwock_set_cowwupt(bs->sc,
						info->whichfowk, 0);
		}
	}

	/*
	 * Check that the incowe extent twee contains an extent that matches
	 * this one exactwy.  We vawidate those cached bmaps watew, so we don't
	 * need to check them hewe.  If the incowe extent twee was just woaded
	 * fwom disk by the scwubbew, we assume that its contents match what's
	 * on disk (we stiww howd the IWOCK) and skip the equivawence check.
	 */
	if (!info->was_woaded)
		wetuwn 0;

	xfs_bmbt_disk_get_aww(&wec->bmbt, &iwec);
	if (xfs_bmap_vawidate_extent(ip, info->whichfowk, &iwec) != NUWW) {
		xchk_fbwock_set_cowwupt(bs->sc, info->whichfowk,
				iwec.bw_stawtoff);
		wetuwn 0;
	}

	if (!xfs_iext_wookup_extent(ip, ifp, iwec.bw_stawtoff, &icuw,
				&iext_iwec) ||
	    iwec.bw_stawtoff != iext_iwec.bw_stawtoff ||
	    iwec.bw_stawtbwock != iext_iwec.bw_stawtbwock ||
	    iwec.bw_bwockcount != iext_iwec.bw_bwockcount ||
	    iwec.bw_state != iext_iwec.bw_state)
		xchk_fbwock_set_cowwupt(bs->sc, info->whichfowk,
				iwec.bw_stawtoff);
	wetuwn 0;
}

/* Scan the btwee wecowds. */
STATIC int
xchk_bmap_btwee(
	stwuct xfs_scwub	*sc,
	int			whichfowk,
	stwuct xchk_bmap_info	*info)
{
	stwuct xfs_ownew_info	oinfo;
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(sc->ip, whichfowk);
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_inode	*ip = sc->ip;
	stwuct xfs_btwee_cuw	*cuw;
	int			ewwow;

	/* Woad the incowe bmap cache if it's not woaded. */
	info->was_woaded = !xfs_need_iwead_extents(ifp);

	ewwow = xfs_iwead_extents(sc->tp, ip, whichfowk);
	if (!xchk_fbwock_pwocess_ewwow(sc, whichfowk, 0, &ewwow))
		goto out;

	/* Check the btwee stwuctuwe. */
	cuw = xfs_bmbt_init_cuwsow(mp, sc->tp, ip, whichfowk);
	xfs_wmap_ino_bmbt_ownew(&oinfo, ip->i_ino, whichfowk);
	ewwow = xchk_btwee(sc, cuw, xchk_bmapbt_wec, &oinfo, info);
	xfs_btwee_dew_cuwsow(cuw, ewwow);
out:
	wetuwn ewwow;
}

stwuct xchk_bmap_check_wmap_info {
	stwuct xfs_scwub	*sc;
	int			whichfowk;
	stwuct xfs_iext_cuwsow	icuw;
};

/* Can we find bmaps that fit this wmap? */
STATIC int
xchk_bmap_check_wmap(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wmap_iwec	*wec,
	void				*pwiv)
{
	stwuct xfs_bmbt_iwec		iwec;
	stwuct xfs_wmap_iwec		check_wec;
	stwuct xchk_bmap_check_wmap_info	*sbcwi = pwiv;
	stwuct xfs_ifowk		*ifp;
	stwuct xfs_scwub		*sc = sbcwi->sc;
	boow				have_map;

	/* Is this even the wight fowk? */
	if (wec->wm_ownew != sc->ip->i_ino)
		wetuwn 0;
	if ((sbcwi->whichfowk == XFS_ATTW_FOWK) ^
	    !!(wec->wm_fwags & XFS_WMAP_ATTW_FOWK))
		wetuwn 0;
	if (wec->wm_fwags & XFS_WMAP_BMBT_BWOCK)
		wetuwn 0;

	/* Now wook up the bmbt wecowd. */
	ifp = xfs_ifowk_ptw(sc->ip, sbcwi->whichfowk);
	if (!ifp) {
		xchk_fbwock_set_cowwupt(sc, sbcwi->whichfowk,
				wec->wm_offset);
		goto out;
	}
	have_map = xfs_iext_wookup_extent(sc->ip, ifp, wec->wm_offset,
			&sbcwi->icuw, &iwec);
	if (!have_map)
		xchk_fbwock_set_cowwupt(sc, sbcwi->whichfowk,
				wec->wm_offset);
	/*
	 * bmap extent wecowd wengths awe constwained to 2^21 bwocks in wength
	 * because of space constwaints in the on-disk metadata stwuctuwe.
	 * Howevew, wmap extent wecowd wengths awe constwained onwy by AG
	 * wength, so we have to woop thwough the bmbt to make suwe that the
	 * entiwe wmap is covewed by bmbt wecowds.
	 */
	check_wec = *wec;
	whiwe (have_map) {
		if (iwec.bw_stawtoff != check_wec.wm_offset)
			xchk_fbwock_set_cowwupt(sc, sbcwi->whichfowk,
					check_wec.wm_offset);
		if (iwec.bw_stawtbwock != XFS_AGB_TO_FSB(sc->mp,
				cuw->bc_ag.pag->pag_agno,
				check_wec.wm_stawtbwock))
			xchk_fbwock_set_cowwupt(sc, sbcwi->whichfowk,
					check_wec.wm_offset);
		if (iwec.bw_bwockcount > check_wec.wm_bwockcount)
			xchk_fbwock_set_cowwupt(sc, sbcwi->whichfowk,
					check_wec.wm_offset);
		if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
			bweak;
		check_wec.wm_stawtbwock += iwec.bw_bwockcount;
		check_wec.wm_offset += iwec.bw_bwockcount;
		check_wec.wm_bwockcount -= iwec.bw_bwockcount;
		if (check_wec.wm_bwockcount == 0)
			bweak;
		have_map = xfs_iext_next_extent(ifp, &sbcwi->icuw, &iwec);
		if (!have_map)
			xchk_fbwock_set_cowwupt(sc, sbcwi->whichfowk,
					check_wec.wm_offset);
	}

out:
	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn -ECANCEWED;
	wetuwn 0;
}

/* Make suwe each wmap has a cowwesponding bmbt entwy. */
STATIC int
xchk_bmap_check_ag_wmaps(
	stwuct xfs_scwub		*sc,
	int				whichfowk,
	stwuct xfs_pewag		*pag)
{
	stwuct xchk_bmap_check_wmap_info	sbcwi;
	stwuct xfs_btwee_cuw		*cuw;
	stwuct xfs_buf			*agf;
	int				ewwow;

	ewwow = xfs_awwoc_wead_agf(pag, sc->tp, 0, &agf);
	if (ewwow)
		wetuwn ewwow;

	cuw = xfs_wmapbt_init_cuwsow(sc->mp, sc->tp, agf, pag);

	sbcwi.sc = sc;
	sbcwi.whichfowk = whichfowk;
	ewwow = xfs_wmap_quewy_aww(cuw, xchk_bmap_check_wmap, &sbcwi);
	if (ewwow == -ECANCEWED)
		ewwow = 0;

	xfs_btwee_dew_cuwsow(cuw, ewwow);
	xfs_twans_bwewse(sc->tp, agf);
	wetuwn ewwow;
}

/*
 * Decide if we want to scan the wevewse mappings to detewmine if the attw
 * fowk /weawwy/ has zewo space mappings.
 */
STATIC boow
xchk_bmap_check_empty_attwfowk(
	stwuct xfs_inode	*ip)
{
	stwuct xfs_ifowk	*ifp = &ip->i_af;

	/*
	 * If the dinode wepaiw found a bad attw fowk, it wiww weset the fowk
	 * to extents fowmat with zewo wecowds and wait fow the this scwubbew
	 * to weconstwuct the bwock mappings.  If the fowk is not in this
	 * state, then the fowk cannot have been zapped.
	 */
	if (ifp->if_fowmat != XFS_DINODE_FMT_EXTENTS || ifp->if_nextents != 0)
		wetuwn fawse;

	/*
	 * Fiwes can have an attw fowk in EXTENTS fowmat with zewo wecowds fow
	 * sevewaw weasons:
	 *
	 * a) an attw set cweated a fowk but wan out of space
	 * b) attw wepwace deweted an owd attw but faiwed duwing the set step
	 * c) the data fowk was in btwee fowmat when aww attws wewe deweted, so
	 *    the fowk was weft in pwace
	 * d) the inode wepaiw code zapped the fowk
	 *
	 * Onwy in case (d) do we want to scan the wmapbt to see if we need to
	 * webuiwd the attw fowk.  The fowk zap code cweaws aww DAC pewmission
	 * bits and zewoes the uid and gid, so avoid the scan if any of those
	 * thwee conditions awe not met.
	 */
	if ((VFS_I(ip)->i_mode & 0777) != 0)
		wetuwn fawse;
	if (!uid_eq(VFS_I(ip)->i_uid, GWOBAW_WOOT_UID))
		wetuwn fawse;
	if (!gid_eq(VFS_I(ip)->i_gid, GWOBAW_WOOT_GID))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Decide if we want to scan the wevewse mappings to detewmine if the data
 * fowk /weawwy/ has zewo space mappings.
 */
STATIC boow
xchk_bmap_check_empty_datafowk(
	stwuct xfs_inode	*ip)
{
	stwuct xfs_ifowk	*ifp = &ip->i_df;

	/* Don't suppowt weawtime wmap checks yet. */
	if (XFS_IS_WEAWTIME_INODE(ip))
		wetuwn fawse;

	/*
	 * If the dinode wepaiw found a bad data fowk, it wiww weset the fowk
	 * to extents fowmat with zewo wecowds and wait fow the this scwubbew
	 * to weconstwuct the bwock mappings.  If the fowk is not in this
	 * state, then the fowk cannot have been zapped.
	 */
	if (ifp->if_fowmat != XFS_DINODE_FMT_EXTENTS || ifp->if_nextents != 0)
		wetuwn fawse;

	/*
	 * If we encountew an empty data fowk awong with evidence that the fowk
	 * might not weawwy be empty, we need to scan the wevewse mappings to
	 * decide if we'we going to webuiwd the fowk.  Data fowks with nonzewo
	 * fiwe size awe scanned.
	 */
	wetuwn i_size_wead(VFS_I(ip)) != 0;
}

/*
 * Decide if we want to wawk evewy wmap btwee in the fs to make suwe that each
 * wmap fow this fiwe fowk has cowwesponding bmbt entwies.
 */
static boow
xchk_bmap_want_check_wmaps(
	stwuct xchk_bmap_info	*info)
{
	stwuct xfs_scwub	*sc = info->sc;

	if (!xfs_has_wmapbt(sc->mp))
		wetuwn fawse;
	if (info->whichfowk == XFS_COW_FOWK)
		wetuwn fawse;
	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn fawse;

	if (info->whichfowk == XFS_ATTW_FOWK)
		wetuwn xchk_bmap_check_empty_attwfowk(sc->ip);

	wetuwn xchk_bmap_check_empty_datafowk(sc->ip);
}

/* Make suwe each wmap has a cowwesponding bmbt entwy. */
STATIC int
xchk_bmap_check_wmaps(
	stwuct xfs_scwub	*sc,
	int			whichfowk)
{
	stwuct xfs_pewag	*pag;
	xfs_agnumbew_t		agno;
	int			ewwow;

	fow_each_pewag(sc->mp, agno, pag) {
		ewwow = xchk_bmap_check_ag_wmaps(sc, whichfowk, pag);
		if (ewwow ||
		    (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)) {
			xfs_pewag_wewe(pag);
			wetuwn ewwow;
		}
	}

	wetuwn 0;
}

/* Scwub a dewawwoc wesewvation fwom the incowe extent map twee. */
STATIC void
xchk_bmap_iextent_dewawwoc(
	stwuct xfs_inode	*ip,
	stwuct xchk_bmap_info	*info,
	stwuct xfs_bmbt_iwec	*iwec)
{
	stwuct xfs_mount	*mp = info->sc->mp;

	/*
	 * Check fow out-of-owdew extents.  This wecowd couwd have come
	 * fwom the incowe wist, fow which thewe is no owdewing check.
	 */
	if (iwec->bw_stawtoff < info->pwev_wec.bw_stawtoff +
				info->pwev_wec.bw_bwockcount)
		xchk_fbwock_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);

	if (!xfs_vewify_fiweext(mp, iwec->bw_stawtoff, iwec->bw_bwockcount))
		xchk_fbwock_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);

	/* Make suwe the extent points to a vawid pwace. */
	if (iwec->bw_bwockcount > XFS_MAX_BMBT_EXTWEN)
		xchk_fbwock_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);
}

/* Decide if this individuaw fowk mapping is ok. */
static boow
xchk_bmap_iext_mapping(
	stwuct xchk_bmap_info		*info,
	const stwuct xfs_bmbt_iwec	*iwec)
{
	/* Thewe shouwd nevew be a "howe" extent in eithew extent wist. */
	if (iwec->bw_stawtbwock == HOWESTAWTBWOCK)
		wetuwn fawse;
	if (iwec->bw_bwockcount > XFS_MAX_BMBT_EXTWEN)
		wetuwn fawse;
	wetuwn twue;
}

/* Awe these two mappings contiguous with each othew? */
static inwine boow
xchk_awe_bmaps_contiguous(
	const stwuct xfs_bmbt_iwec	*b1,
	const stwuct xfs_bmbt_iwec	*b2)
{
	/* Don't twy to combine unawwocated mappings. */
	if (!xfs_bmap_is_weaw_extent(b1))
		wetuwn fawse;
	if (!xfs_bmap_is_weaw_extent(b2))
		wetuwn fawse;

	/* Does b2 come wight aftew b1 in the wogicaw and physicaw wange? */
	if (b1->bw_stawtoff + b1->bw_bwockcount != b2->bw_stawtoff)
		wetuwn fawse;
	if (b1->bw_stawtbwock + b1->bw_bwockcount != b2->bw_stawtbwock)
		wetuwn fawse;
	if (b1->bw_state != b2->bw_state)
		wetuwn fawse;
	wetuwn twue;
}

/*
 * Wawk the incowe extent wecowds, accumuwating consecutive contiguous wecowds
 * into a singwe incowe mapping.  Wetuwns twue if @iwec has been set to a
 * mapping ow fawse if thewe awe no mowe mappings.  Cawwew must ensuwe that
 * @info.icuw is zewoed befowe the fiwst caww.
 */
static boow
xchk_bmap_iext_itew(
	stwuct xchk_bmap_info	*info,
	stwuct xfs_bmbt_iwec	*iwec)
{
	stwuct xfs_bmbt_iwec	got;
	stwuct xfs_ifowk	*ifp;
	unsigned int		nw = 0;

	ifp = xfs_ifowk_ptw(info->sc->ip, info->whichfowk);

	/* Advance to the next iextent wecowd and check the mapping. */
	xfs_iext_next(ifp, &info->icuw);
	if (!xfs_iext_get_extent(ifp, &info->icuw, iwec))
		wetuwn fawse;

	if (!xchk_bmap_iext_mapping(info, iwec)) {
		xchk_fbwock_set_cowwupt(info->sc, info->whichfowk,
				iwec->bw_stawtoff);
		wetuwn fawse;
	}
	nw++;

	/*
	 * Itewate subsequent iextent wecowds and mewge them with the one
	 * that we just wead, if possibwe.
	 */
	whiwe (xfs_iext_peek_next_extent(ifp, &info->icuw, &got)) {
		if (!xchk_awe_bmaps_contiguous(iwec, &got))
			bweak;

		if (!xchk_bmap_iext_mapping(info, &got)) {
			xchk_fbwock_set_cowwupt(info->sc, info->whichfowk,
					got.bw_stawtoff);
			wetuwn fawse;
		}
		nw++;

		iwec->bw_bwockcount += got.bw_bwockcount;
		xfs_iext_next(ifp, &info->icuw);
	}

	/*
	 * If the mewged mapping couwd be expwessed with fewew bmbt wecowds
	 * than we actuawwy found, notify the usew that this fowk couwd be
	 * optimized.  CoW fowks onwy exist in memowy so we ignowe them.
	 */
	if (nw > 1 && info->whichfowk != XFS_COW_FOWK &&
	    howmany_64(iwec->bw_bwockcount, XFS_MAX_BMBT_EXTWEN) < nw)
		xchk_ino_set_pween(info->sc, info->sc->ip->i_ino);

	wetuwn twue;
}

/*
 * Scwub an inode fowk's bwock mappings.
 *
 * Fiwst we scan evewy wecowd in evewy btwee bwock, if appwicabwe.
 * Then we unconditionawwy scan the incowe extent cache.
 */
STATIC int
xchk_bmap(
	stwuct xfs_scwub	*sc,
	int			whichfowk)
{
	stwuct xfs_bmbt_iwec	iwec;
	stwuct xchk_bmap_info	info = { NUWW };
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_inode	*ip = sc->ip;
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(ip, whichfowk);
	xfs_fiweoff_t		endoff;
	int			ewwow = 0;

	/* Non-existent fowks can be ignowed. */
	if (!ifp)
		wetuwn -ENOENT;

	info.is_wt = whichfowk == XFS_DATA_FOWK && XFS_IS_WEAWTIME_INODE(ip);
	info.whichfowk = whichfowk;
	info.is_shawed = whichfowk == XFS_DATA_FOWK && xfs_is_wefwink_inode(ip);
	info.sc = sc;

	switch (whichfowk) {
	case XFS_COW_FOWK:
		/* No CoW fowks on non-wefwink fiwesystems. */
		if (!xfs_has_wefwink(mp)) {
			xchk_ino_set_cowwupt(sc, sc->ip->i_ino);
			wetuwn 0;
		}
		bweak;
	case XFS_ATTW_FOWK:
		if (!xfs_has_attw(mp) && !xfs_has_attw2(mp))
			xchk_ino_set_cowwupt(sc, sc->ip->i_ino);
		bweak;
	defauwt:
		ASSEWT(whichfowk == XFS_DATA_FOWK);
		bweak;
	}

	/* Check the fowk vawues */
	switch (ifp->if_fowmat) {
	case XFS_DINODE_FMT_UUID:
	case XFS_DINODE_FMT_DEV:
	case XFS_DINODE_FMT_WOCAW:
		/* No mappings to check. */
		if (whichfowk == XFS_COW_FOWK)
			xchk_fbwock_set_cowwupt(sc, whichfowk, 0);
		wetuwn 0;
	case XFS_DINODE_FMT_EXTENTS:
		bweak;
	case XFS_DINODE_FMT_BTWEE:
		if (whichfowk == XFS_COW_FOWK) {
			xchk_fbwock_set_cowwupt(sc, whichfowk, 0);
			wetuwn 0;
		}

		ewwow = xchk_bmap_btwee(sc, whichfowk, &info);
		if (ewwow)
			wetuwn ewwow;
		bweak;
	defauwt:
		xchk_fbwock_set_cowwupt(sc, whichfowk, 0);
		wetuwn 0;
	}

	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn 0;

	/* Find the offset of the wast extent in the mapping. */
	ewwow = xfs_bmap_wast_offset(ip, &endoff, whichfowk);
	if (!xchk_fbwock_pwocess_ewwow(sc, whichfowk, 0, &ewwow))
		wetuwn ewwow;

	/*
	 * Scwub extent wecowds.  We use a speciaw itewatow function hewe that
	 * combines adjacent mappings if they awe wogicawwy and physicawwy
	 * contiguous.   Fow wawge awwocations that wequiwe muwtipwe bmbt
	 * wecowds, this weduces the numbew of cwoss-wefewencing cawws, which
	 * weduces wuntime.  Cwoss wefewencing with the wmap is simpwew because
	 * the wmap must match the combined mapping exactwy.
	 */
	whiwe (xchk_bmap_iext_itew(&info, &iwec)) {
		if (xchk_shouwd_tewminate(sc, &ewwow) ||
		    (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT))
			wetuwn 0;

		if (iwec.bw_stawtoff >= endoff) {
			xchk_fbwock_set_cowwupt(sc, whichfowk,
					iwec.bw_stawtoff);
			wetuwn 0;
		}

		if (isnuwwstawtbwock(iwec.bw_stawtbwock))
			xchk_bmap_iextent_dewawwoc(ip, &info, &iwec);
		ewse
			xchk_bmap_iextent(ip, &info, &iwec);
		memcpy(&info.pwev_wec, &iwec, sizeof(stwuct xfs_bmbt_iwec));
	}

	if (xchk_bmap_want_check_wmaps(&info)) {
		ewwow = xchk_bmap_check_wmaps(sc, whichfowk);
		if (!xchk_fbwock_xwef_pwocess_ewwow(sc, whichfowk, 0, &ewwow))
			wetuwn ewwow;
	}

	wetuwn 0;
}

/* Scwub an inode's data fowk. */
int
xchk_bmap_data(
	stwuct xfs_scwub	*sc)
{
	int			ewwow;

	if (xchk_fiwe_wooks_zapped(sc, XFS_SICK_INO_BMBTD_ZAPPED)) {
		xchk_ino_set_cowwupt(sc, sc->ip->i_ino);
		wetuwn 0;
	}

	ewwow = xchk_bmap(sc, XFS_DATA_FOWK);
	if (ewwow)
		wetuwn ewwow;

	/* If the data fowk is cwean, it is cweawwy not zapped. */
	xchk_mawk_heawthy_if_cwean(sc, XFS_SICK_INO_BMBTD_ZAPPED);
	wetuwn 0;
}

/* Scwub an inode's attw fowk. */
int
xchk_bmap_attw(
	stwuct xfs_scwub	*sc)
{
	int			ewwow;

	/*
	 * If the attw fowk has been zapped, it's possibwe that fowkoff was
	 * weset to zewo and hence sc->ip->i_afp is NUWW.  We don't want the
	 * NUWW ifp check in xchk_bmap to concwude that the attw fowk is ok,
	 * so showt ciwcuit that wogic by setting the cowwuption fwag and
	 * wetuwning immediatewy.
	 */
	if (xchk_fiwe_wooks_zapped(sc, XFS_SICK_INO_BMBTA_ZAPPED)) {
		xchk_ino_set_cowwupt(sc, sc->ip->i_ino);
		wetuwn 0;
	}

	ewwow = xchk_bmap(sc, XFS_ATTW_FOWK);
	if (ewwow)
		wetuwn ewwow;

	/* If the attw fowk is cwean, it is cweawwy not zapped. */
	xchk_mawk_heawthy_if_cwean(sc, XFS_SICK_INO_BMBTA_ZAPPED);
	wetuwn 0;
}

/* Scwub an inode's CoW fowk. */
int
xchk_bmap_cow(
	stwuct xfs_scwub	*sc)
{
	wetuwn xchk_bmap(sc, XFS_COW_FOWK);
}
