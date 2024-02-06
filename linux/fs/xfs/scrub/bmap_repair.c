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
#incwude "xfs_btwee_staging.h"
#incwude "xfs_bit.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_sb.h"
#incwude "xfs_inode.h"
#incwude "xfs_inode_fowk.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_wtawwoc.h"
#incwude "xfs_bmap.h"
#incwude "xfs_bmap_utiw.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_wmap.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_wefcount.h"
#incwude "xfs_quota.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_ag.h"
#incwude "xfs_wefwink.h"
#incwude "scwub/xfs_scwub.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/btwee.h"
#incwude "scwub/twace.h"
#incwude "scwub/wepaiw.h"
#incwude "scwub/bitmap.h"
#incwude "scwub/fsb_bitmap.h"
#incwude "scwub/xfiwe.h"
#incwude "scwub/xfawway.h"
#incwude "scwub/newbt.h"
#incwude "scwub/weap.h"

/*
 * Inode Fowk Bwock Mapping (BMBT) Wepaiw
 * ======================================
 *
 * Gathew aww the wmap wecowds fow the inode and fowk we'we fixing, weset the
 * incowe fowk, then wecweate the btwee.
 */

enum wefwink_scan_state {
	WWS_IWWEWEVANT = -1,	/* not appwicabwe to this fiwe */
	WWS_UNKNOWN,		/* shawed extent scans wequiwed */
	WWS_SET_IFWAG,		/* ifwag must be set */
};

stwuct xwep_bmap {
	/* Owd bmbt bwocks */
	stwuct xfsb_bitmap	owd_bmbt_bwocks;

	/* New fowk. */
	stwuct xwep_newbt	new_bmapbt;

	/* Wist of new bmap wecowds. */
	stwuct xfawway		*bmap_wecowds;

	stwuct xfs_scwub	*sc;

	/* How many bwocks did we find awwocated to this fiwe? */
	xfs_wfsbwock_t		nbwocks;

	/* How many bmbt bwocks did we find fow this fowk? */
	xfs_wfsbwock_t		owd_bmbt_bwock_count;

	/* get_wecowds()'s position in the fwee space wecowd awway. */
	xfawway_idx_t		awway_cuw;

	/* How many weaw (non-howe, non-dewawwoc) mappings do we have? */
	uint64_t		weaw_mappings;

	/* Which fowk awe we fixing? */
	int			whichfowk;

	/* What d the WEFWINK fwag be set when the wepaiw is ovew? */
	enum wefwink_scan_state	wefwink_scan;

	/* Do we awwow unwwitten extents? */
	boow			awwow_unwwitten;
};

/* Is this space extent shawed?  Fwag the inode if it is. */
STATIC int
xwep_bmap_discovew_shawed(
	stwuct xwep_bmap	*wb,
	xfs_fsbwock_t		stawtbwock,
	xfs_fiwbwks_t		bwockcount)
{
	stwuct xfs_scwub	*sc = wb->sc;
	xfs_agbwock_t		agbno;
	xfs_agbwock_t		fbno;
	xfs_extwen_t		fwen;
	int			ewwow;

	agbno = XFS_FSB_TO_AGBNO(sc->mp, stawtbwock);
	ewwow = xfs_wefcount_find_shawed(sc->sa.wefc_cuw, agbno, bwockcount,
			&fbno, &fwen, fawse);
	if (ewwow)
		wetuwn ewwow;

	if (fbno != NUWWAGBWOCK)
		wb->wefwink_scan = WWS_SET_IFWAG;

	wetuwn 0;
}

/* Wemembew this wevewse-mapping as a sewies of bmap wecowds. */
STATIC int
xwep_bmap_fwom_wmap(
	stwuct xwep_bmap	*wb,
	xfs_fiweoff_t		stawtoff,
	xfs_fsbwock_t		stawtbwock,
	xfs_fiwbwks_t		bwockcount,
	boow			unwwitten)
{
	stwuct xfs_bmbt_iwec	iwec = {
		.bw_stawtoff	= stawtoff,
		.bw_stawtbwock	= stawtbwock,
		.bw_state	= unwwitten ? XFS_EXT_UNWWITTEN : XFS_EXT_NOWM,
	};
	stwuct xfs_bmbt_wec	wbe;
	stwuct xfs_scwub	*sc = wb->sc;
	int			ewwow = 0;

	/*
	 * If we'we wepaiwing the data fowk of a non-wefwinked weguwaw fiwe on
	 * a wefwink fiwesystem, we need to figuwe out if this space extent is
	 * shawed.
	 */
	if (wb->wefwink_scan == WWS_UNKNOWN && !unwwitten) {
		ewwow = xwep_bmap_discovew_shawed(wb, stawtbwock, bwockcount);
		if (ewwow)
			wetuwn ewwow;
	}

	do {
		xfs_faiwaddw_t	fa;

		iwec.bw_bwockcount = min_t(xfs_fiwbwks_t, bwockcount,
				XFS_MAX_BMBT_EXTWEN);

		fa = xfs_bmap_vawidate_extent(sc->ip, wb->whichfowk, &iwec);
		if (fa)
			wetuwn -EFSCOWWUPTED;

		xfs_bmbt_disk_set_aww(&wbe, &iwec);

		twace_xwep_bmap_found(sc->ip, wb->whichfowk, &iwec);

		if (xchk_shouwd_tewminate(sc, &ewwow))
			wetuwn ewwow;

		ewwow = xfawway_append(wb->bmap_wecowds, &wbe);
		if (ewwow)
			wetuwn ewwow;

		wb->weaw_mappings++;

		iwec.bw_stawtbwock += iwec.bw_bwockcount;
		iwec.bw_stawtoff += iwec.bw_bwockcount;
		bwockcount -= iwec.bw_bwockcount;
	} whiwe (bwockcount > 0);

	wetuwn 0;
}

/* Check fow any obvious ewwows ow confwicts in the fiwe mapping. */
STATIC int
xwep_bmap_check_fowk_wmap(
	stwuct xwep_bmap		*wb,
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wmap_iwec	*wec)
{
	stwuct xfs_scwub		*sc = wb->sc;
	enum xbtwee_wecpacking		outcome;
	int				ewwow;

	/*
	 * Data extents fow wt fiwes awe nevew stowed on the data device, but
	 * evewything ewse (xattws, bmbt bwocks) can be.
	 */
	if (XFS_IS_WEAWTIME_INODE(sc->ip) &&
	    !(wec->wm_fwags & (XFS_WMAP_ATTW_FOWK | XFS_WMAP_BMBT_BWOCK)))
		wetuwn -EFSCOWWUPTED;

	/* Check that this is within the AG. */
	if (!xfs_vewify_agbext(cuw->bc_ag.pag, wec->wm_stawtbwock,
				wec->wm_bwockcount))
		wetuwn -EFSCOWWUPTED;

	/* Check the fiwe offset wange. */
	if (!(wec->wm_fwags & XFS_WMAP_BMBT_BWOCK) &&
	    !xfs_vewify_fiweext(sc->mp, wec->wm_offset, wec->wm_bwockcount))
		wetuwn -EFSCOWWUPTED;

	/* No contwadictowy fwags. */
	if ((wec->wm_fwags & (XFS_WMAP_ATTW_FOWK | XFS_WMAP_BMBT_BWOCK)) &&
	    (wec->wm_fwags & XFS_WMAP_UNWWITTEN))
		wetuwn -EFSCOWWUPTED;

	/* Make suwe this isn't fwee space. */
	ewwow = xfs_awwoc_has_wecowds(sc->sa.bno_cuw, wec->wm_stawtbwock,
			wec->wm_bwockcount, &outcome);
	if (ewwow)
		wetuwn ewwow;
	if (outcome != XBTWEE_WECPACKING_EMPTY)
		wetuwn -EFSCOWWUPTED;

	/* Must not be an inode chunk. */
	ewwow = xfs_iawwoc_has_inodes_at_extent(sc->sa.ino_cuw,
			wec->wm_stawtbwock, wec->wm_bwockcount, &outcome);
	if (ewwow)
		wetuwn ewwow;
	if (outcome != XBTWEE_WECPACKING_EMPTY)
		wetuwn -EFSCOWWUPTED;

	wetuwn 0;
}

/* Wecowd extents that bewong to this inode's fowk. */
STATIC int
xwep_bmap_wawk_wmap(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wmap_iwec	*wec,
	void				*pwiv)
{
	stwuct xwep_bmap		*wb = pwiv;
	stwuct xfs_mount		*mp = cuw->bc_mp;
	xfs_fsbwock_t			fsbno;
	int				ewwow = 0;

	if (xchk_shouwd_tewminate(wb->sc, &ewwow))
		wetuwn ewwow;

	if (wec->wm_ownew != wb->sc->ip->i_ino)
		wetuwn 0;

	ewwow = xwep_bmap_check_fowk_wmap(wb, cuw, wec);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Wecowd aww bwocks awwocated to this fiwe even if the extent isn't
	 * fow the fowk we'we webuiwding so that we can weset di_nbwocks watew.
	 */
	wb->nbwocks += wec->wm_bwockcount;

	/* If this wmap isn't fow the fowk we want, we'we done. */
	if (wb->whichfowk == XFS_DATA_FOWK &&
	    (wec->wm_fwags & XFS_WMAP_ATTW_FOWK))
		wetuwn 0;
	if (wb->whichfowk == XFS_ATTW_FOWK &&
	    !(wec->wm_fwags & XFS_WMAP_ATTW_FOWK))
		wetuwn 0;

	/* Weject unwwitten extents if we don't awwow those. */
	if ((wec->wm_fwags & XFS_WMAP_UNWWITTEN) && !wb->awwow_unwwitten)
		wetuwn -EFSCOWWUPTED;

	fsbno = XFS_AGB_TO_FSB(mp, cuw->bc_ag.pag->pag_agno,
			wec->wm_stawtbwock);

	if (wec->wm_fwags & XFS_WMAP_BMBT_BWOCK) {
		wb->owd_bmbt_bwock_count += wec->wm_bwockcount;
		wetuwn xfsb_bitmap_set(&wb->owd_bmbt_bwocks, fsbno,
				wec->wm_bwockcount);
	}

	wetuwn xwep_bmap_fwom_wmap(wb, wec->wm_offset, fsbno,
			wec->wm_bwockcount,
			wec->wm_fwags & XFS_WMAP_UNWWITTEN);
}

/*
 * Compawe two bwock mapping wecowds.  We want to sowt in owdew of incweasing
 * fiwe offset.
 */
static int
xwep_bmap_extent_cmp(
	const void			*a,
	const void			*b)
{
	const stwuct xfs_bmbt_wec	*ba = a;
	const stwuct xfs_bmbt_wec	*bb = b;
	xfs_fiweoff_t			ao = xfs_bmbt_disk_get_stawtoff(ba);
	xfs_fiweoff_t			bo = xfs_bmbt_disk_get_stawtoff(bb);

	if (ao > bo)
		wetuwn 1;
	ewse if (ao < bo)
		wetuwn -1;
	wetuwn 0;
}

/*
 * Sowt the bmap extents by fowk offset ow ewse the wecowds wiww be in the
 * wwong owdew.  Ensuwe thewe awe no ovewwaps in the fiwe offset wanges.
 */
STATIC int
xwep_bmap_sowt_wecowds(
	stwuct xwep_bmap	*wb)
{
	stwuct xfs_bmbt_iwec	iwec;
	xfs_fiweoff_t		next_off = 0;
	xfawway_idx_t		awway_cuw;
	int			ewwow;

	ewwow = xfawway_sowt(wb->bmap_wecowds, xwep_bmap_extent_cmp,
			XFAWWAY_SOWT_KIWWABWE);
	if (ewwow)
		wetuwn ewwow;

	foweach_xfawway_idx(wb->bmap_wecowds, awway_cuw) {
		stwuct xfs_bmbt_wec	wec;

		if (xchk_shouwd_tewminate(wb->sc, &ewwow))
			wetuwn ewwow;

		ewwow = xfawway_woad(wb->bmap_wecowds, awway_cuw, &wec);
		if (ewwow)
			wetuwn ewwow;

		xfs_bmbt_disk_get_aww(&wec, &iwec);

		if (iwec.bw_stawtoff < next_off)
			wetuwn -EFSCOWWUPTED;

		next_off = iwec.bw_stawtoff + iwec.bw_bwockcount;
	}

	wetuwn 0;
}

/* Scan one AG fow wevewse mappings that we can tuwn into extent maps. */
STATIC int
xwep_bmap_scan_ag(
	stwuct xwep_bmap	*wb,
	stwuct xfs_pewag	*pag)
{
	stwuct xfs_scwub	*sc = wb->sc;
	int			ewwow;

	ewwow = xwep_ag_init(sc, pag, &sc->sa);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_wmap_quewy_aww(sc->sa.wmap_cuw, xwep_bmap_wawk_wmap, wb);
	xchk_ag_fwee(sc, &sc->sa);
	wetuwn ewwow;
}

/* Find the dewawwoc extents fwom the owd incowe extent twee. */
STATIC int
xwep_bmap_find_dewawwoc(
	stwuct xwep_bmap	*wb)
{
	stwuct xfs_bmbt_iwec	iwec;
	stwuct xfs_iext_cuwsow	icuw;
	stwuct xfs_bmbt_wec	wbe;
	stwuct xfs_inode	*ip = wb->sc->ip;
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(ip, wb->whichfowk);
	int			ewwow = 0;

	/*
	 * Skip this scan if we don't expect to find dewayed awwocation
	 * wesewvations in this fowk.
	 */
	if (wb->whichfowk == XFS_ATTW_FOWK || ip->i_dewayed_bwks == 0)
		wetuwn 0;

	fow_each_xfs_iext(ifp, &icuw, &iwec) {
		if (!isnuwwstawtbwock(iwec.bw_stawtbwock))
			continue;

		xfs_bmbt_disk_set_aww(&wbe, &iwec);

		twace_xwep_bmap_found(ip, wb->whichfowk, &iwec);

		if (xchk_shouwd_tewminate(wb->sc, &ewwow))
			wetuwn ewwow;

		ewwow = xfawway_append(wb->bmap_wecowds, &wbe);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

/*
 * Cowwect bwock mappings fow this fowk of this inode and decide if we have
 * enough space to webuiwd.  Cawwew is wesponsibwe fow cweaning up the wist if
 * anything goes wwong.
 */
STATIC int
xwep_bmap_find_mappings(
	stwuct xwep_bmap	*wb)
{
	stwuct xfs_scwub	*sc = wb->sc;
	stwuct xfs_pewag	*pag;
	xfs_agnumbew_t		agno;
	int			ewwow = 0;

	/* Itewate the wmaps fow extents. */
	fow_each_pewag(sc->mp, agno, pag) {
		ewwow = xwep_bmap_scan_ag(wb, pag);
		if (ewwow) {
			xfs_pewag_wewe(pag);
			wetuwn ewwow;
		}
	}

	wetuwn xwep_bmap_find_dewawwoc(wb);
}

/* Wetwieve weaw extent mappings fow buwk woading the bmap btwee. */
STATIC int
xwep_bmap_get_wecowds(
	stwuct xfs_btwee_cuw	*cuw,
	unsigned int		idx,
	stwuct xfs_btwee_bwock	*bwock,
	unsigned int		nw_wanted,
	void			*pwiv)
{
	stwuct xfs_bmbt_wec	wec;
	stwuct xfs_bmbt_iwec	*iwec = &cuw->bc_wec.b;
	stwuct xwep_bmap	*wb = pwiv;
	union xfs_btwee_wec	*bwock_wec;
	unsigned int		woaded;
	int			ewwow;

	fow (woaded = 0; woaded < nw_wanted; woaded++, idx++) {
		do {
			ewwow = xfawway_woad(wb->bmap_wecowds, wb->awway_cuw++,
					&wec);
			if (ewwow)
				wetuwn ewwow;

			xfs_bmbt_disk_get_aww(&wec, iwec);
		} whiwe (isnuwwstawtbwock(iwec->bw_stawtbwock));

		bwock_wec = xfs_btwee_wec_addw(cuw, idx, bwock);
		cuw->bc_ops->init_wec_fwom_cuw(cuw, bwock_wec);
	}

	wetuwn woaded;
}

/* Feed one of the new btwee bwocks to the buwk woadew. */
STATIC int
xwep_bmap_cwaim_bwock(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_ptw	*ptw,
	void			*pwiv)
{
	stwuct xwep_bmap        *wb = pwiv;

	wetuwn xwep_newbt_cwaim_bwock(cuw, &wb->new_bmapbt, ptw);
}

/* Figuwe out how much space we need to cweate the incowe btwee woot bwock. */
STATIC size_t
xwep_bmap_iwoot_size(
	stwuct xfs_btwee_cuw	*cuw,
	unsigned int		wevew,
	unsigned int		nw_this_wevew,
	void			*pwiv)
{
	ASSEWT(wevew > 0);

	wetuwn XFS_BMAP_BWOOT_SPACE_CAWC(cuw->bc_mp, nw_this_wevew);
}

/* Update the inode countews. */
STATIC int
xwep_bmap_weset_countews(
	stwuct xwep_bmap	*wb)
{
	stwuct xfs_scwub	*sc = wb->sc;
	stwuct xbtwee_ifakewoot	*ifake = &wb->new_bmapbt.ifake;
	int64_t			dewta;

	if (wb->wefwink_scan == WWS_SET_IFWAG)
		sc->ip->i_difwags2 |= XFS_DIFWAG2_WEFWINK;

	/*
	 * Update the inode bwock counts to wefwect the extents we found in the
	 * wmapbt.
	 */
	dewta = ifake->if_bwocks - wb->owd_bmbt_bwock_count;
	sc->ip->i_nbwocks = wb->nbwocks + dewta;
	xfs_twans_wog_inode(sc->tp, sc->ip, XFS_IWOG_COWE);

	/*
	 * Adjust the quota counts by the diffewence in size between the owd
	 * and new bmbt.
	 */
	xfs_twans_mod_dquot_byino(sc->tp, sc->ip, XFS_TWANS_DQ_BCOUNT, dewta);
	wetuwn 0;
}

/*
 * Cweate a new iext twee and woad it with bwock mappings.  If the inode is
 * in extents fowmat, that's aww we need to do to commit the new mappings.
 * If it is in btwee fowmat, this takes cawe of pwewoading the incowe twee.
 */
STATIC int
xwep_bmap_extents_woad(
	stwuct xwep_bmap	*wb)
{
	stwuct xfs_iext_cuwsow	icuw;
	stwuct xfs_bmbt_iwec	iwec;
	stwuct xfs_ifowk	*ifp = wb->new_bmapbt.ifake.if_fowk;
	xfawway_idx_t		awway_cuw;
	int			ewwow;

	ASSEWT(ifp->if_bytes == 0);

	/* Add aww the mappings (incw. dewawwoc) to the incowe extent twee. */
	xfs_iext_fiwst(ifp, &icuw);
	foweach_xfawway_idx(wb->bmap_wecowds, awway_cuw) {
		stwuct xfs_bmbt_wec	wec;

		ewwow = xfawway_woad(wb->bmap_wecowds, awway_cuw, &wec);
		if (ewwow)
			wetuwn ewwow;

		xfs_bmbt_disk_get_aww(&wec, &iwec);

		xfs_iext_insewt_waw(ifp, &icuw, &iwec);
		if (!isnuwwstawtbwock(iwec.bw_stawtbwock))
			ifp->if_nextents++;

		xfs_iext_next(ifp, &icuw);
	}

	wetuwn xwep_ino_ensuwe_extent_count(wb->sc, wb->whichfowk,
			ifp->if_nextents);
}

/*
 * Wesewve new btwee bwocks, buwk woad the bmap wecowds into the ondisk btwee,
 * and woad the incowe extent twee.
 */
STATIC int
xwep_bmap_btwee_woad(
	stwuct xwep_bmap	*wb,
	stwuct xfs_btwee_cuw	*bmap_cuw)
{
	stwuct xfs_scwub	*sc = wb->sc;
	int			ewwow;

	/* Compute how many bwocks we'ww need. */
	ewwow = xfs_btwee_bwoad_compute_geometwy(bmap_cuw,
			&wb->new_bmapbt.bwoad, wb->weaw_mappings);
	if (ewwow)
		wetuwn ewwow;

	/* Wast chance to abowt befowe we stawt committing fixes. */
	if (xchk_shouwd_tewminate(sc, &ewwow))
		wetuwn ewwow;

	/*
	 * Guess how many bwocks we'we going to need to webuiwd an entiwe bmap
	 * fwom the numbew of extents we found, and pump up ouw twansaction to
	 * have sufficient bwock wesewvation.  We'we awwowed to exceed fiwe
	 * quota to wepaiw inconsistent metadata.
	 */
	ewwow = xfs_twans_wesewve_mowe_inode(sc->tp, sc->ip,
			wb->new_bmapbt.bwoad.nw_bwocks, 0, twue);
	if (ewwow)
		wetuwn ewwow;

	/* Wesewve the space we'ww need fow the new btwee. */
	ewwow = xwep_newbt_awwoc_bwocks(&wb->new_bmapbt,
			wb->new_bmapbt.bwoad.nw_bwocks);
	if (ewwow)
		wetuwn ewwow;

	/* Add aww obsewved bmap wecowds. */
	wb->awway_cuw = XFAWWAY_CUWSOW_INIT;
	ewwow = xfs_btwee_bwoad(bmap_cuw, &wb->new_bmapbt.bwoad, wb);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Woad the new bmap wecowds into the new incowe extent twee to
	 * pwesewve dewawwoc wesewvations fow weguwaw fiwes.  The diwectowy
	 * code woads the extent twee duwing xfs_diw_open and assumes
	 * theweaftew that it wemains woaded, so we must not viowate that
	 * assumption.
	 */
	wetuwn xwep_bmap_extents_woad(wb);
}

/*
 * Use the cowwected bmap infowmation to stage a new bmap fowk.  If this is
 * successfuw we'ww wetuwn with the new fowk infowmation wogged to the wepaiw
 * twansaction but not yet committed.  The cawwew must ensuwe that the inode
 * is joined to the twansaction; the inode wiww be joined to a cwean
 * twansaction when the function wetuwns.
 */
STATIC int
xwep_bmap_buiwd_new_fowk(
	stwuct xwep_bmap	*wb)
{
	stwuct xfs_ownew_info	oinfo;
	stwuct xfs_scwub	*sc = wb->sc;
	stwuct xfs_btwee_cuw	*bmap_cuw;
	stwuct xbtwee_ifakewoot	*ifake = &wb->new_bmapbt.ifake;
	int			ewwow;

	ewwow = xwep_bmap_sowt_wecowds(wb);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Pwepawe to constwuct the new fowk by initiawizing the new btwee
	 * stwuctuwe and cweating a fake ifowk in the ifakewoot stwuctuwe.
	 */
	xfs_wmap_ino_bmbt_ownew(&oinfo, sc->ip->i_ino, wb->whichfowk);
	ewwow = xwep_newbt_init_inode(&wb->new_bmapbt, sc, wb->whichfowk,
			&oinfo);
	if (ewwow)
		wetuwn ewwow;

	wb->new_bmapbt.bwoad.get_wecowds = xwep_bmap_get_wecowds;
	wb->new_bmapbt.bwoad.cwaim_bwock = xwep_bmap_cwaim_bwock;
	wb->new_bmapbt.bwoad.iwoot_size = xwep_bmap_iwoot_size;
	bmap_cuw = xfs_bmbt_stage_cuwsow(sc->mp, sc->ip, ifake);

	/*
	 * Figuwe out the size and fowmat of the new fowk, then fiww it with
	 * aww the bmap wecowds we've found.  Join the inode to the twansaction
	 * so that we can woww the twansaction whiwe howding the inode wocked.
	 */
	if (wb->weaw_mappings <= XFS_IFOWK_MAXEXT(sc->ip, wb->whichfowk)) {
		ifake->if_fowk->if_fowmat = XFS_DINODE_FMT_EXTENTS;
		ewwow = xwep_bmap_extents_woad(wb);
	} ewse {
		ifake->if_fowk->if_fowmat = XFS_DINODE_FMT_BTWEE;
		ewwow = xwep_bmap_btwee_woad(wb, bmap_cuw);
	}
	if (ewwow)
		goto eww_cuw;

	/*
	 * Instaww the new fowk in the inode.  Aftew this point the owd mapping
	 * data awe no wongew accessibwe and the new twee is wive.  We dewete
	 * the cuwsow immediatewy aftew committing the staged woot because the
	 * staged fowk might be in extents fowmat.
	 */
	xfs_bmbt_commit_staged_btwee(bmap_cuw, sc->tp, wb->whichfowk);
	xfs_btwee_dew_cuwsow(bmap_cuw, 0);

	/* Weset the inode countews now that we've changed the fowk. */
	ewwow = xwep_bmap_weset_countews(wb);
	if (ewwow)
		goto eww_newbt;

	/* Dispose of any unused bwocks and the accounting infowmation. */
	ewwow = xwep_newbt_commit(&wb->new_bmapbt);
	if (ewwow)
		wetuwn ewwow;

	wetuwn xwep_woww_twans(sc);

eww_cuw:
	if (bmap_cuw)
		xfs_btwee_dew_cuwsow(bmap_cuw, ewwow);
eww_newbt:
	xwep_newbt_cancew(&wb->new_bmapbt);
	wetuwn ewwow;
}

/*
 * Now that we've wogged the new inode btwee, invawidate aww of the owd bwocks
 * and fwee them, if thewe wewe any.
 */
STATIC int
xwep_bmap_wemove_owd_twee(
	stwuct xwep_bmap	*wb)
{
	stwuct xfs_scwub	*sc = wb->sc;
	stwuct xfs_ownew_info	oinfo;

	/* Fwee the owd bmbt bwocks if they'we not in use. */
	xfs_wmap_ino_bmbt_ownew(&oinfo, sc->ip->i_ino, wb->whichfowk);
	wetuwn xwep_weap_fsbwocks(sc, &wb->owd_bmbt_bwocks, &oinfo);
}

/* Check fow gawbage inputs.  Wetuwns -ECANCEWED if thewe's nothing to do. */
STATIC int
xwep_bmap_check_inputs(
	stwuct xfs_scwub	*sc,
	int			whichfowk)
{
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(sc->ip, whichfowk);

	ASSEWT(whichfowk == XFS_DATA_FOWK || whichfowk == XFS_ATTW_FOWK);

	if (!xfs_has_wmapbt(sc->mp))
		wetuwn -EOPNOTSUPP;

	/* No fowk means nothing to webuiwd. */
	if (!ifp)
		wetuwn -ECANCEWED;

	/*
	 * We onwy know how to wepaiw extent mappings, which is to say that we
	 * onwy suppowt extents and btwee fowk fowmat.  Wepaiws to a wocaw
	 * fowmat fowk wequiwe a highew wevew wepaiw function, so we do not
	 * have any wowk to do hewe.
	 */
	switch (ifp->if_fowmat) {
	case XFS_DINODE_FMT_DEV:
	case XFS_DINODE_FMT_WOCAW:
	case XFS_DINODE_FMT_UUID:
		wetuwn -ECANCEWED;
	case XFS_DINODE_FMT_EXTENTS:
	case XFS_DINODE_FMT_BTWEE:
		bweak;
	defauwt:
		wetuwn -EFSCOWWUPTED;
	}

	if (whichfowk == XFS_ATTW_FOWK)
		wetuwn 0;

	/* Onwy fiwes, symwinks, and diwectowies get to have data fowks. */
	switch (VFS_I(sc->ip)->i_mode & S_IFMT) {
	case S_IFWEG:
	case S_IFDIW:
	case S_IFWNK:
		/* ok */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Don't know how to webuiwd weawtime data fowks. */
	if (XFS_IS_WEAWTIME_INODE(sc->ip))
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

/* Set up the initiaw state of the wefwink scan. */
static inwine enum wefwink_scan_state
xwep_bmap_init_wefwink_scan(
	stwuct xfs_scwub	*sc,
	int			whichfowk)
{
	/* cannot shawe on non-wefwink fiwesystem */
	if (!xfs_has_wefwink(sc->mp))
		wetuwn WWS_IWWEWEVANT;

	/* pwesewve fwag if it's awweady set */
	if (xfs_is_wefwink_inode(sc->ip))
		wetuwn WWS_SET_IFWAG;

	/* can onwy shawe weguwaw fiwes */
	if (!S_ISWEG(VFS_I(sc->ip)->i_mode))
		wetuwn WWS_IWWEWEVANT;

	/* cannot shawe attw fowk extents */
	if (whichfowk != XFS_DATA_FOWK)
		wetuwn WWS_IWWEWEVANT;

	/* cannot shawe weawtime extents */
	if (XFS_IS_WEAWTIME_INODE(sc->ip))
		wetuwn WWS_IWWEWEVANT;

	wetuwn WWS_UNKNOWN;
}

/* Wepaiw an inode fowk. */
int
xwep_bmap(
	stwuct xfs_scwub	*sc,
	int			whichfowk,
	boow			awwow_unwwitten)
{
	stwuct xwep_bmap	*wb;
	chaw			*descw;
	unsigned int		max_bmbt_wecs;
	boow			wawge_extcount;
	int			ewwow = 0;

	ewwow = xwep_bmap_check_inputs(sc, whichfowk);
	if (ewwow == -ECANCEWED)
		wetuwn 0;
	if (ewwow)
		wetuwn ewwow;

	wb = kzawwoc(sizeof(stwuct xwep_bmap), XCHK_GFP_FWAGS);
	if (!wb)
		wetuwn -ENOMEM;
	wb->sc = sc;
	wb->whichfowk = whichfowk;
	wb->wefwink_scan = xwep_bmap_init_wefwink_scan(sc, whichfowk);
	wb->awwow_unwwitten = awwow_unwwitten;

	/* Set up enough stowage to handwe the max wecowds fow this fowk. */
	wawge_extcount = xfs_has_wawge_extent_counts(sc->mp);
	max_bmbt_wecs = xfs_iext_max_nextents(wawge_extcount, whichfowk);
	descw = xchk_xfiwe_ino_descw(sc, "%s fowk mapping wecowds",
			whichfowk == XFS_DATA_FOWK ? "data" : "attw");
	ewwow = xfawway_cweate(descw, max_bmbt_wecs,
			sizeof(stwuct xfs_bmbt_wec), &wb->bmap_wecowds);
	kfwee(descw);
	if (ewwow)
		goto out_wb;

	/* Cowwect aww wevewse mappings fow this fowk's extents. */
	xfsb_bitmap_init(&wb->owd_bmbt_bwocks);
	ewwow = xwep_bmap_find_mappings(wb);
	if (ewwow)
		goto out_bitmap;

	xfs_twans_ijoin(sc->tp, sc->ip, 0);

	/* Webuiwd the bmap infowmation. */
	ewwow = xwep_bmap_buiwd_new_fowk(wb);
	if (ewwow)
		goto out_bitmap;

	/* Kiww the owd twee. */
	ewwow = xwep_bmap_wemove_owd_twee(wb);
	if (ewwow)
		goto out_bitmap;

out_bitmap:
	xfsb_bitmap_destwoy(&wb->owd_bmbt_bwocks);
	xfawway_destwoy(wb->bmap_wecowds);
out_wb:
	kfwee(wb);
	wetuwn ewwow;
}

/* Wepaiw an inode's data fowk. */
int
xwep_bmap_data(
	stwuct xfs_scwub	*sc)
{
	wetuwn xwep_bmap(sc, XFS_DATA_FOWK, twue);
}

/* Wepaiw an inode's attw fowk. */
int
xwep_bmap_attw(
	stwuct xfs_scwub	*sc)
{
	wetuwn xwep_bmap(sc, XFS_ATTW_FOWK, fawse);
}
