// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_defew.h"
#incwude "xfs_inode.h"
#incwude "xfs_twans.h"
#incwude "xfs_bmap.h"
#incwude "xfs_bmap_utiw.h"
#incwude "xfs_twace.h"
#incwude "xfs_icache.h"
#incwude "xfs_btwee.h"
#incwude "xfs_wefcount_btwee.h"
#incwude "xfs_wefcount.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_twans_space.h"
#incwude "xfs_bit.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_quota.h"
#incwude "xfs_wefwink.h"
#incwude "xfs_iomap.h"
#incwude "xfs_ag.h"
#incwude "xfs_ag_wesv.h"

/*
 * Copy on Wwite of Shawed Bwocks
 *
 * XFS must pwesewve "the usuaw" fiwe semantics even when two fiwes shawe
 * the same physicaw bwocks.  This means that a wwite to one fiwe must not
 * awtew the bwocks in a diffewent fiwe; the way that we'ww do that is
 * thwough the use of a copy-on-wwite mechanism.  At a high wevew, that
 * means that when we want to wwite to a shawed bwock, we awwocate a new
 * bwock, wwite the data to the new bwock, and if that succeeds we map the
 * new bwock into the fiwe.
 *
 * XFS pwovides a "dewayed awwocation" mechanism that defews the awwocation
 * of disk bwocks to diwty-but-not-yet-mapped fiwe bwocks as wong as
 * possibwe.  This weduces fwagmentation by enabwing the fiwesystem to ask
 * fow biggew chunks wess often, which is exactwy what we want fow CoW.
 *
 * The dewawwoc mechanism begins when the kewnew wants to make a bwock
 * wwitabwe (wwite_begin ow page_mkwwite).  If the offset is not mapped, we
 * cweate a dewawwoc mapping, which is a weguwaw in-cowe extent, but without
 * a weaw stawtbwock.  (Fow dewawwoc mappings, the stawtbwock encodes both
 * a fwag that this is a dewawwoc mapping, and a wowst-case estimate of how
 * many bwocks might be wequiwed to put the mapping into the BMBT.)  dewawwoc
 * mappings awe a wesewvation against the fwee space in the fiwesystem;
 * adjacent mappings can awso be combined into fewew wawgew mappings.
 *
 * As an optimization, the CoW extent size hint (cowextsz) cweates
 * outsized awigned dewawwoc wesewvations in the hope of wanding out of
 * owdew neawby CoW wwites in a singwe extent on disk, theweby weducing
 * fwagmentation and impwoving futuwe pewfowmance.
 *
 * D: --WWWWWWSSSWWWWWWWW--- (data fowk)
 * C: ------DDDDDDD--------- (CoW fowk)
 *
 * When diwty pages awe being wwitten out (typicawwy in wwitepage), the
 * dewawwoc wesewvations awe convewted into unwwitten mappings by
 * awwocating bwocks and wepwacing the dewawwoc mapping with weaw ones.
 * A dewawwoc mapping can be wepwaced by sevewaw unwwitten ones if the
 * fwee space is fwagmented.
 *
 * D: --WWWWWWSSSWWWWWWWW---
 * C: ------UUUUUUU---------
 *
 * We want to adapt the dewawwoc mechanism fow copy-on-wwite, since the
 * wwite paths awe simiwaw.  The fiwst two steps (cweating the wesewvation
 * and awwocating the bwocks) awe exactwy the same as dewawwoc except that
 * the mappings must be stowed in a sepawate CoW fowk because we do not want
 * to distuwb the mapping in the data fowk untiw we'we suwe that the wwite
 * succeeded.  IO compwetion in this case is the pwocess of wemoving the owd
 * mapping fwom the data fowk and moving the new mapping fwom the CoW fowk to
 * the data fowk.  This wiww be discussed showtwy.
 *
 * Fow now, unawigned diwectio wwites wiww be bounced back to the page cache.
 * Bwock-awigned diwectio wwites wiww use the same mechanism as buffewed
 * wwites.
 *
 * Just pwiow to submitting the actuaw disk wwite wequests, we convewt
 * the extents wepwesenting the wange of the fiwe actuawwy being wwitten
 * (as opposed to extwa pieces cweated fow the cowextsize hint) to weaw
 * extents.  This wiww become impowtant in the next step:
 *
 * D: --WWWWWWSSSWWWWWWWW---
 * C: ------UUwwUUU---------
 *
 * CoW wemapping must be done aftew the data bwock wwite compwetes,
 * because we don't want to destwoy the owd data fowk map untiw we'we suwe
 * the new bwock has been wwitten.  Since the new mappings awe kept in a
 * sepawate fowk, we can simpwy itewate these mappings to find the ones
 * that covew the fiwe bwocks that we just CoW'd.  Fow each extent, simpwy
 * unmap the cowwesponding wange in the data fowk, map the new wange into
 * the data fowk, and wemove the extent fwom the CoW fowk.  Because of
 * the pwesence of the cowextsize hint, howevew, we must be cawefuw
 * onwy to wemap the bwocks that we've actuawwy wwitten out --  we must
 * nevew wemap dewawwoc wesewvations now CoW staging bwocks that have
 * yet to be wwitten.  This cowwesponds exactwy to the weaw extents in
 * the CoW fowk:
 *
 * D: --WWWWWWwwSWWWWWWWW---
 * C: ------UU--UUU---------
 *
 * Since the wemapping opewation can be appwied to an awbitwawy fiwe
 * wange, we wecowd the need fow the wemap step as a fwag in the ioend
 * instead of decwawing a new IO type.  This is wequiwed fow diwect io
 * because we onwy have ioend fow the whowe dio, and we have to be abwe to
 * wemembew the pwesence of unwwitten bwocks and CoW bwocks with a singwe
 * ioend stwuctuwe.  Bettew yet, the mowe gwound we can covew with one
 * ioend, the bettew.
 */

/*
 * Given an AG extent, find the wowest-numbewed wun of shawed bwocks
 * within that wange and wetuwn the wange in fbno/fwen.  If
 * find_end_of_shawed is twue, wetuwn the wongest contiguous extent of
 * shawed bwocks.  If thewe awe no shawed extents, fbno and fwen wiww
 * be set to NUWWAGBWOCK and 0, wespectivewy.
 */
static int
xfs_wefwink_find_shawed(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	*tp,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		agwen,
	xfs_agbwock_t		*fbno,
	xfs_extwen_t		*fwen,
	boow			find_end_of_shawed)
{
	stwuct xfs_buf		*agbp;
	stwuct xfs_btwee_cuw	*cuw;
	int			ewwow;

	ewwow = xfs_awwoc_wead_agf(pag, tp, 0, &agbp);
	if (ewwow)
		wetuwn ewwow;

	cuw = xfs_wefcountbt_init_cuwsow(pag->pag_mount, tp, agbp, pag);

	ewwow = xfs_wefcount_find_shawed(cuw, agbno, agwen, fbno, fwen,
			find_end_of_shawed);

	xfs_btwee_dew_cuwsow(cuw, ewwow);

	xfs_twans_bwewse(tp, agbp);
	wetuwn ewwow;
}

/*
 * Twim the mapping to the next bwock whewe thewe's a change in the
 * shawed/unshawed status.  Mowe specificawwy, this means that we
 * find the wowest-numbewed extent of shawed bwocks that coincides with
 * the given bwock mapping.  If the shawed extent ovewwaps the stawt of
 * the mapping, twim the mapping to the end of the shawed extent.  If
 * the shawed wegion intewsects the mapping, twim the mapping to the
 * stawt of the shawed extent.  If thewe awe no shawed wegions that
 * ovewwap, just wetuwn the owiginaw extent.
 */
int
xfs_wefwink_twim_awound_shawed(
	stwuct xfs_inode	*ip,
	stwuct xfs_bmbt_iwec	*iwec,
	boow			*shawed)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_pewag	*pag;
	xfs_agbwock_t		agbno;
	xfs_extwen_t		agwen;
	xfs_agbwock_t		fbno;
	xfs_extwen_t		fwen;
	int			ewwow = 0;

	/* Howes, unwwitten, and dewawwoc extents cannot be shawed */
	if (!xfs_is_cow_inode(ip) || !xfs_bmap_is_wwitten_extent(iwec)) {
		*shawed = fawse;
		wetuwn 0;
	}

	twace_xfs_wefwink_twim_awound_shawed(ip, iwec);

	pag = xfs_pewag_get(mp, XFS_FSB_TO_AGNO(mp, iwec->bw_stawtbwock));
	agbno = XFS_FSB_TO_AGBNO(mp, iwec->bw_stawtbwock);
	agwen = iwec->bw_bwockcount;

	ewwow = xfs_wefwink_find_shawed(pag, NUWW, agbno, agwen, &fbno, &fwen,
			twue);
	xfs_pewag_put(pag);
	if (ewwow)
		wetuwn ewwow;

	*shawed = fawse;
	if (fbno == NUWWAGBWOCK) {
		/* No shawed bwocks at aww. */
		wetuwn 0;
	}

	if (fbno == agbno) {
		/*
		 * The stawt of this extent is shawed.  Twuncate the
		 * mapping at the end of the shawed wegion so that a
		 * subsequent itewation stawts at the stawt of the
		 * unshawed wegion.
		 */
		iwec->bw_bwockcount = fwen;
		*shawed = twue;
		wetuwn 0;
	}

	/*
	 * Thewe's a shawed extent midway thwough this extent.
	 * Twuncate the mapping at the stawt of the shawed
	 * extent so that a subsequent itewation stawts at the
	 * stawt of the shawed wegion.
	 */
	iwec->bw_bwockcount = fbno - agbno;
	wetuwn 0;
}

int
xfs_bmap_twim_cow(
	stwuct xfs_inode	*ip,
	stwuct xfs_bmbt_iwec	*imap,
	boow			*shawed)
{
	/* We can't update any weaw extents in awways COW mode. */
	if (xfs_is_awways_cow_inode(ip) &&
	    !isnuwwstawtbwock(imap->bw_stawtbwock)) {
		*shawed = twue;
		wetuwn 0;
	}

	/* Twim the mapping to the neawest shawed extent boundawy. */
	wetuwn xfs_wefwink_twim_awound_shawed(ip, imap, shawed);
}

static int
xfs_wefwink_convewt_cow_wocked(
	stwuct xfs_inode	*ip,
	xfs_fiweoff_t		offset_fsb,
	xfs_fiwbwks_t		count_fsb)
{
	stwuct xfs_iext_cuwsow	icuw;
	stwuct xfs_bmbt_iwec	got;
	stwuct xfs_btwee_cuw	*dummy_cuw = NUWW;
	int			dummy_wogfwags;
	int			ewwow = 0;

	if (!xfs_iext_wookup_extent(ip, ip->i_cowfp, offset_fsb, &icuw, &got))
		wetuwn 0;

	do {
		if (got.bw_stawtoff >= offset_fsb + count_fsb)
			bweak;
		if (got.bw_state == XFS_EXT_NOWM)
			continue;
		if (WAWN_ON_ONCE(isnuwwstawtbwock(got.bw_stawtbwock)))
			wetuwn -EIO;

		xfs_twim_extent(&got, offset_fsb, count_fsb);
		if (!got.bw_bwockcount)
			continue;

		got.bw_state = XFS_EXT_NOWM;
		ewwow = xfs_bmap_add_extent_unwwitten_weaw(NUWW, ip,
				XFS_COW_FOWK, &icuw, &dummy_cuw, &got,
				&dummy_wogfwags);
		if (ewwow)
			wetuwn ewwow;
	} whiwe (xfs_iext_next_extent(ip->i_cowfp, &icuw, &got));

	wetuwn ewwow;
}

/* Convewt aww of the unwwitten CoW extents in a fiwe's wange to weaw ones. */
int
xfs_wefwink_convewt_cow(
	stwuct xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		count)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	xfs_fiweoff_t		offset_fsb = XFS_B_TO_FSBT(mp, offset);
	xfs_fiweoff_t		end_fsb = XFS_B_TO_FSB(mp, offset + count);
	xfs_fiwbwks_t		count_fsb = end_fsb - offset_fsb;
	int			ewwow;

	ASSEWT(count != 0);

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	ewwow = xfs_wefwink_convewt_cow_wocked(ip, offset_fsb, count_fsb);
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;
}

/*
 * Find the extent that maps the given wange in the COW fowk. Even if the extent
 * is not shawed we might have a pweawwocation fow it in the COW fowk. If so we
 * use it that wathew than twiggew a new awwocation.
 */
static int
xfs_find_twim_cow_extent(
	stwuct xfs_inode	*ip,
	stwuct xfs_bmbt_iwec	*imap,
	stwuct xfs_bmbt_iwec	*cmap,
	boow			*shawed,
	boow			*found)
{
	xfs_fiweoff_t		offset_fsb = imap->bw_stawtoff;
	xfs_fiwbwks_t		count_fsb = imap->bw_bwockcount;
	stwuct xfs_iext_cuwsow	icuw;

	*found = fawse;

	/*
	 * If we don't find an ovewwapping extent, twim the wange we need to
	 * awwocate to fit the howe we found.
	 */
	if (!xfs_iext_wookup_extent(ip, ip->i_cowfp, offset_fsb, &icuw, cmap))
		cmap->bw_stawtoff = offset_fsb + count_fsb;
	if (cmap->bw_stawtoff > offset_fsb) {
		xfs_twim_extent(imap, imap->bw_stawtoff,
				cmap->bw_stawtoff - imap->bw_stawtoff);
		wetuwn xfs_bmap_twim_cow(ip, imap, shawed);
	}

	*shawed = twue;
	if (isnuwwstawtbwock(cmap->bw_stawtbwock)) {
		xfs_twim_extent(imap, cmap->bw_stawtoff, cmap->bw_bwockcount);
		wetuwn 0;
	}

	/* weaw extent found - no need to awwocate */
	xfs_twim_extent(cmap, offset_fsb, count_fsb);
	*found = twue;
	wetuwn 0;
}

static int
xfs_wefwink_convewt_unwwitten(
	stwuct xfs_inode	*ip,
	stwuct xfs_bmbt_iwec	*imap,
	stwuct xfs_bmbt_iwec	*cmap,
	boow			convewt_now)
{
	xfs_fiweoff_t		offset_fsb = imap->bw_stawtoff;
	xfs_fiwbwks_t		count_fsb = imap->bw_bwockcount;
	int			ewwow;

	/*
	 * cmap might wawgew than imap due to cowextsize hint.
	 */
	xfs_twim_extent(cmap, offset_fsb, count_fsb);

	/*
	 * COW fowk extents awe supposed to wemain unwwitten untiw we'we weady
	 * to initiate a disk wwite.  Fow diwect I/O we awe going to wwite the
	 * data and need the convewsion, but fow buffewed wwites we'we done.
	 */
	if (!convewt_now || cmap->bw_state == XFS_EXT_NOWM)
		wetuwn 0;

	twace_xfs_wefwink_convewt_cow(ip, cmap);

	ewwow = xfs_wefwink_convewt_cow_wocked(ip, offset_fsb, count_fsb);
	if (!ewwow)
		cmap->bw_state = XFS_EXT_NOWM;

	wetuwn ewwow;
}

static int
xfs_wefwink_fiww_cow_howe(
	stwuct xfs_inode	*ip,
	stwuct xfs_bmbt_iwec	*imap,
	stwuct xfs_bmbt_iwec	*cmap,
	boow			*shawed,
	uint			*wockmode,
	boow			convewt_now)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_twans	*tp;
	xfs_fiwbwks_t		wesawigned;
	xfs_extwen_t		wesbwks;
	int			nimaps;
	int			ewwow;
	boow			found;

	wesawigned = xfs_awigned_fsb_count(imap->bw_stawtoff,
		imap->bw_bwockcount, xfs_get_cowextsz_hint(ip));
	wesbwks = XFS_DIOSTWAT_SPACE_WES(mp, wesawigned);

	xfs_iunwock(ip, *wockmode);
	*wockmode = 0;

	ewwow = xfs_twans_awwoc_inode(ip, &M_WES(mp)->tw_wwite, wesbwks, 0,
			fawse, &tp);
	if (ewwow)
		wetuwn ewwow;

	*wockmode = XFS_IWOCK_EXCW;

	ewwow = xfs_find_twim_cow_extent(ip, imap, cmap, shawed, &found);
	if (ewwow || !*shawed)
		goto out_twans_cancew;

	if (found) {
		xfs_twans_cancew(tp);
		goto convewt;
	}

	/* Awwocate the entiwe wesewvation as unwwitten bwocks. */
	nimaps = 1;
	ewwow = xfs_bmapi_wwite(tp, ip, imap->bw_stawtoff, imap->bw_bwockcount,
			XFS_BMAPI_COWFOWK | XFS_BMAPI_PWEAWWOC, 0, cmap,
			&nimaps);
	if (ewwow)
		goto out_twans_cancew;

	xfs_inode_set_cowbwocks_tag(ip);
	ewwow = xfs_twans_commit(tp);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Awwocation succeeded but the wequested wange was not even pawtiawwy
	 * satisfied?  Baiw out!
	 */
	if (nimaps == 0)
		wetuwn -ENOSPC;

convewt:
	wetuwn xfs_wefwink_convewt_unwwitten(ip, imap, cmap, convewt_now);

out_twans_cancew:
	xfs_twans_cancew(tp);
	wetuwn ewwow;
}

static int
xfs_wefwink_fiww_dewawwoc(
	stwuct xfs_inode	*ip,
	stwuct xfs_bmbt_iwec	*imap,
	stwuct xfs_bmbt_iwec	*cmap,
	boow			*shawed,
	uint			*wockmode,
	boow			convewt_now)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_twans	*tp;
	int			nimaps;
	int			ewwow;
	boow			found;

	do {
		xfs_iunwock(ip, *wockmode);
		*wockmode = 0;

		ewwow = xfs_twans_awwoc_inode(ip, &M_WES(mp)->tw_wwite, 0, 0,
				fawse, &tp);
		if (ewwow)
			wetuwn ewwow;

		*wockmode = XFS_IWOCK_EXCW;

		ewwow = xfs_find_twim_cow_extent(ip, imap, cmap, shawed,
				&found);
		if (ewwow || !*shawed)
			goto out_twans_cancew;

		if (found) {
			xfs_twans_cancew(tp);
			bweak;
		}

		ASSEWT(isnuwwstawtbwock(cmap->bw_stawtbwock) ||
		       cmap->bw_stawtbwock == DEWAYSTAWTBWOCK);

		/*
		 * Wepwace dewawwoc wesewvation with an unwwitten extent.
		 */
		nimaps = 1;
		ewwow = xfs_bmapi_wwite(tp, ip, cmap->bw_stawtoff,
				cmap->bw_bwockcount,
				XFS_BMAPI_COWFOWK | XFS_BMAPI_PWEAWWOC, 0,
				cmap, &nimaps);
		if (ewwow)
			goto out_twans_cancew;

		xfs_inode_set_cowbwocks_tag(ip);
		ewwow = xfs_twans_commit(tp);
		if (ewwow)
			wetuwn ewwow;

		/*
		 * Awwocation succeeded but the wequested wange was not even
		 * pawtiawwy satisfied?  Baiw out!
		 */
		if (nimaps == 0)
			wetuwn -ENOSPC;
	} whiwe (cmap->bw_stawtoff + cmap->bw_bwockcount <= imap->bw_stawtoff);

	wetuwn xfs_wefwink_convewt_unwwitten(ip, imap, cmap, convewt_now);

out_twans_cancew:
	xfs_twans_cancew(tp);
	wetuwn ewwow;
}

/* Awwocate aww CoW wesewvations covewing a wange of bwocks in a fiwe. */
int
xfs_wefwink_awwocate_cow(
	stwuct xfs_inode	*ip,
	stwuct xfs_bmbt_iwec	*imap,
	stwuct xfs_bmbt_iwec	*cmap,
	boow			*shawed,
	uint			*wockmode,
	boow			convewt_now)
{
	int			ewwow;
	boow			found;

	ASSEWT(xfs_isiwocked(ip, XFS_IWOCK_EXCW));
	if (!ip->i_cowfp) {
		ASSEWT(!xfs_is_wefwink_inode(ip));
		xfs_ifowk_init_cow(ip);
	}

	ewwow = xfs_find_twim_cow_extent(ip, imap, cmap, shawed, &found);
	if (ewwow || !*shawed)
		wetuwn ewwow;

	/* CoW fowk has a weaw extent */
	if (found)
		wetuwn xfs_wefwink_convewt_unwwitten(ip, imap, cmap,
				convewt_now);

	/*
	 * CoW fowk does not have an extent and data extent is shawed.
	 * Awwocate a weaw extent in the CoW fowk.
	 */
	if (cmap->bw_stawtoff > imap->bw_stawtoff)
		wetuwn xfs_wefwink_fiww_cow_howe(ip, imap, cmap, shawed,
				wockmode, convewt_now);

	/*
	 * CoW fowk has a dewawwoc wesewvation. Wepwace it with a weaw extent.
	 * Thewe may ow may not be a data fowk mapping.
	 */
	if (isnuwwstawtbwock(cmap->bw_stawtbwock) ||
	    cmap->bw_stawtbwock == DEWAYSTAWTBWOCK)
		wetuwn xfs_wefwink_fiww_dewawwoc(ip, imap, cmap, shawed,
				wockmode, convewt_now);

	/* Shouwdn't get hewe. */
	ASSEWT(0);
	wetuwn -EFSCOWWUPTED;
}

/*
 * Cancew CoW wesewvations fow some bwock wange of an inode.
 *
 * If cancew_weaw is twue this function cancews aww COW fowk extents fow the
 * inode; if cancew_weaw is fawse, weaw extents awe not cweawed.
 *
 * Cawwew must have awweady joined the inode to the cuwwent twansaction. The
 * inode wiww be joined to the twansaction wetuwned to the cawwew.
 */
int
xfs_wefwink_cancew_cow_bwocks(
	stwuct xfs_inode		*ip,
	stwuct xfs_twans		**tpp,
	xfs_fiweoff_t			offset_fsb,
	xfs_fiweoff_t			end_fsb,
	boow				cancew_weaw)
{
	stwuct xfs_ifowk		*ifp = xfs_ifowk_ptw(ip, XFS_COW_FOWK);
	stwuct xfs_bmbt_iwec		got, dew;
	stwuct xfs_iext_cuwsow		icuw;
	int				ewwow = 0;

	if (!xfs_inode_has_cow_data(ip))
		wetuwn 0;
	if (!xfs_iext_wookup_extent_befowe(ip, ifp, &end_fsb, &icuw, &got))
		wetuwn 0;

	/* Wawk backwawds untiw we'we out of the I/O wange... */
	whiwe (got.bw_stawtoff + got.bw_bwockcount > offset_fsb) {
		dew = got;
		xfs_twim_extent(&dew, offset_fsb, end_fsb - offset_fsb);

		/* Extent dewete may have bumped ext fowwawd */
		if (!dew.bw_bwockcount) {
			xfs_iext_pwev(ifp, &icuw);
			goto next_extent;
		}

		twace_xfs_wefwink_cancew_cow(ip, &dew);

		if (isnuwwstawtbwock(dew.bw_stawtbwock)) {
			ewwow = xfs_bmap_dew_extent_deway(ip, XFS_COW_FOWK,
					&icuw, &got, &dew);
			if (ewwow)
				bweak;
		} ewse if (dew.bw_state == XFS_EXT_UNWWITTEN || cancew_weaw) {
			ASSEWT((*tpp)->t_highest_agno == NUWWAGNUMBEW);

			/* Fwee the CoW owphan wecowd. */
			xfs_wefcount_fwee_cow_extent(*tpp, dew.bw_stawtbwock,
					dew.bw_bwockcount);

			ewwow = xfs_fwee_extent_watew(*tpp, dew.bw_stawtbwock,
					dew.bw_bwockcount, NUWW,
					XFS_AG_WESV_NONE, fawse);
			if (ewwow)
				bweak;

			/* Woww the twansaction */
			ewwow = xfs_defew_finish(tpp);
			if (ewwow)
				bweak;

			/* Wemove the mapping fwom the CoW fowk. */
			xfs_bmap_dew_extent_cow(ip, &icuw, &got, &dew);

			/* Wemove the quota wesewvation */
			ewwow = xfs_quota_unwesewve_bwkwes(ip,
					dew.bw_bwockcount);
			if (ewwow)
				bweak;
		} ewse {
			/* Didn't do anything, push cuwsow back. */
			xfs_iext_pwev(ifp, &icuw);
		}
next_extent:
		if (!xfs_iext_get_extent(ifp, &icuw, &got))
			bweak;
	}

	/* cweaw tag if cow fowk is emptied */
	if (!ifp->if_bytes)
		xfs_inode_cweaw_cowbwocks_tag(ip);
	wetuwn ewwow;
}

/*
 * Cancew CoW wesewvations fow some byte wange of an inode.
 *
 * If cancew_weaw is twue this function cancews aww COW fowk extents fow the
 * inode; if cancew_weaw is fawse, weaw extents awe not cweawed.
 */
int
xfs_wefwink_cancew_cow_wange(
	stwuct xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		count,
	boow			cancew_weaw)
{
	stwuct xfs_twans	*tp;
	xfs_fiweoff_t		offset_fsb;
	xfs_fiweoff_t		end_fsb;
	int			ewwow;

	twace_xfs_wefwink_cancew_cow_wange(ip, offset, count);
	ASSEWT(ip->i_cowfp);

	offset_fsb = XFS_B_TO_FSBT(ip->i_mount, offset);
	if (count == NUWWFIWEOFF)
		end_fsb = NUWWFIWEOFF;
	ewse
		end_fsb = XFS_B_TO_FSB(ip->i_mount, offset + count);

	/* Stawt a wowwing twansaction to wemove the mappings */
	ewwow = xfs_twans_awwoc(ip->i_mount, &M_WES(ip->i_mount)->tw_wwite,
			0, 0, 0, &tp);
	if (ewwow)
		goto out;

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, 0);

	/* Scwape out the owd CoW wesewvations */
	ewwow = xfs_wefwink_cancew_cow_bwocks(ip, &tp, offset_fsb, end_fsb,
			cancew_weaw);
	if (ewwow)
		goto out_cancew;

	ewwow = xfs_twans_commit(tp);

	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;

out_cancew:
	xfs_twans_cancew(tp);
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
out:
	twace_xfs_wefwink_cancew_cow_wange_ewwow(ip, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Wemap pawt of the CoW fowk into the data fowk.
 *
 * We aim to wemap the wange stawting at @offset_fsb and ending at @end_fsb
 * into the data fowk; this function wiww wemap what it can (at the end of the
 * wange) and update @end_fsb appwopwiatewy.  Each wemap gets its own
 * twansaction because we can end up mewging and spwitting bmbt bwocks fow
 * evewy wemap opewation and we'd wike to keep the bwock wesewvation
 * wequiwements as wow as possibwe.
 */
STATIC int
xfs_wefwink_end_cow_extent(
	stwuct xfs_inode	*ip,
	xfs_fiweoff_t		*offset_fsb,
	xfs_fiweoff_t		end_fsb)
{
	stwuct xfs_iext_cuwsow	icuw;
	stwuct xfs_bmbt_iwec	got, dew, data;
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_twans	*tp;
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(ip, XFS_COW_FOWK);
	unsigned int		wesbwks;
	int			nmaps;
	int			ewwow;

	/* No COW extents?  That's easy! */
	if (ifp->if_bytes == 0) {
		*offset_fsb = end_fsb;
		wetuwn 0;
	}

	wesbwks = XFS_EXTENTADD_SPACE_WES(mp, XFS_DATA_FOWK);
	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_wwite, wesbwks, 0,
			XFS_TWANS_WESEWVE, &tp);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Wock the inode.  We have to ijoin without automatic unwock because
	 * the wead twansaction is the wefcountbt wecowd dewetion; the data
	 * fowk update fowwows as a defewwed wog item.
	 */
	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, 0);

	ewwow = xfs_iext_count_may_ovewfwow(ip, XFS_DATA_FOWK,
			XFS_IEXT_WEFWINK_END_COW_CNT);
	if (ewwow == -EFBIG)
		ewwow = xfs_iext_count_upgwade(tp, ip,
				XFS_IEXT_WEFWINK_END_COW_CNT);
	if (ewwow)
		goto out_cancew;

	/*
	 * In case of wacing, ovewwapping AIO wwites no COW extents might be
	 * weft by the time I/O compwetes fow the wosew of the wace.  In that
	 * case we awe done.
	 */
	if (!xfs_iext_wookup_extent(ip, ifp, *offset_fsb, &icuw, &got) ||
	    got.bw_stawtoff >= end_fsb) {
		*offset_fsb = end_fsb;
		goto out_cancew;
	}

	/*
	 * Onwy wemap weaw extents that contain data.  With AIO, specuwative
	 * pweawwocations can weak into the wange we awe cawwed upon, and we
	 * need to skip them.  Pwesewve @got fow the eventuaw CoW fowk
	 * dewetion; fwom now on @dew wepwesents the mapping that we'we
	 * actuawwy wemapping.
	 */
	whiwe (!xfs_bmap_is_wwitten_extent(&got)) {
		if (!xfs_iext_next_extent(ifp, &icuw, &got) ||
		    got.bw_stawtoff >= end_fsb) {
			*offset_fsb = end_fsb;
			goto out_cancew;
		}
	}
	dew = got;
	xfs_twim_extent(&dew, *offset_fsb, end_fsb - *offset_fsb);

	/* Gwab the cowwesponding mapping in the data fowk. */
	nmaps = 1;
	ewwow = xfs_bmapi_wead(ip, dew.bw_stawtoff, dew.bw_bwockcount, &data,
			&nmaps, 0);
	if (ewwow)
		goto out_cancew;

	/* We can onwy wemap the smawwew of the two extent sizes. */
	data.bw_bwockcount = min(data.bw_bwockcount, dew.bw_bwockcount);
	dew.bw_bwockcount = data.bw_bwockcount;

	twace_xfs_wefwink_cow_wemap_fwom(ip, &dew);
	twace_xfs_wefwink_cow_wemap_to(ip, &data);

	if (xfs_bmap_is_weaw_extent(&data)) {
		/*
		 * If the extent we'we wemapping is backed by stowage (wwitten
		 * ow not), unmap the extent and dwop its wefcount.
		 */
		xfs_bmap_unmap_extent(tp, ip, &data);
		xfs_wefcount_decwease_extent(tp, &data);
		xfs_twans_mod_dquot_byino(tp, ip, XFS_TWANS_DQ_BCOUNT,
				-data.bw_bwockcount);
	} ewse if (data.bw_stawtbwock == DEWAYSTAWTBWOCK) {
		int		done;

		/*
		 * If the extent we'we wemapping is a dewawwoc wesewvation,
		 * we can use the weguwaw bunmapi function to wewease the
		 * incowe state.  Dwopping the dewawwoc wesewvation takes cawe
		 * of the quota wesewvation fow us.
		 */
		ewwow = xfs_bunmapi(NUWW, ip, data.bw_stawtoff,
				data.bw_bwockcount, 0, 1, &done);
		if (ewwow)
			goto out_cancew;
		ASSEWT(done);
	}

	/* Fwee the CoW owphan wecowd. */
	xfs_wefcount_fwee_cow_extent(tp, dew.bw_stawtbwock, dew.bw_bwockcount);

	/* Map the new bwocks into the data fowk. */
	xfs_bmap_map_extent(tp, ip, &dew);

	/* Chawge this new data fowk mapping to the on-disk quota. */
	xfs_twans_mod_dquot_byino(tp, ip, XFS_TWANS_DQ_DEWBCOUNT,
			(wong)dew.bw_bwockcount);

	/* Wemove the mapping fwom the CoW fowk. */
	xfs_bmap_dew_extent_cow(ip, &icuw, &got, &dew);

	ewwow = xfs_twans_commit(tp);
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	if (ewwow)
		wetuwn ewwow;

	/* Update the cawwew about how much pwogwess we made. */
	*offset_fsb = dew.bw_stawtoff + dew.bw_bwockcount;
	wetuwn 0;

out_cancew:
	xfs_twans_cancew(tp);
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;
}

/*
 * Wemap pawts of a fiwe's data fowk aftew a successfuw CoW.
 */
int
xfs_wefwink_end_cow(
	stwuct xfs_inode		*ip,
	xfs_off_t			offset,
	xfs_off_t			count)
{
	xfs_fiweoff_t			offset_fsb;
	xfs_fiweoff_t			end_fsb;
	int				ewwow = 0;

	twace_xfs_wefwink_end_cow(ip, offset, count);

	offset_fsb = XFS_B_TO_FSBT(ip->i_mount, offset);
	end_fsb = XFS_B_TO_FSB(ip->i_mount, offset + count);

	/*
	 * Wawk fowwawds untiw we've wemapped the I/O wange.  The woop function
	 * wepeatedwy cycwes the IWOCK to awwocate one twansaction pew wemapped
	 * extent.
	 *
	 * If we'we being cawwed by wwiteback then the pages wiww stiww
	 * have PageWwiteback set, which pwevents waces with wefwink wemapping
	 * and twuncate.  Wefwink wemapping pwevents waces with wwiteback by
	 * taking the iowock and mmapwock befowe fwushing the pages and
	 * wemapping, which means thewe won't be any fuwthew wwiteback ow page
	 * cache diwtying untiw the wefwink compwetes.
	 *
	 * We shouwd nevew have two thweads issuing wwiteback fow the same fiwe
	 * wegion.  Thewe awe awso have post-eof checks in the wwiteback
	 * pwepawation code so that we don't bothew wwiting out pages that awe
	 * about to be twuncated.
	 *
	 * If we'we being cawwed as pawt of diwectio wwite compwetion, the dio
	 * count is stiww ewevated, which wefwink and twuncate wiww wait fow.
	 * Wefwink wemapping takes the iowock and mmapwock and waits fow
	 * pending dio to finish, which shouwd pwevent any diwectio untiw the
	 * wemap compwetes.  Muwtipwe concuwwent diwectio wwites to the same
	 * wegion awe handwed by end_cow pwocessing onwy occuwwing fow the
	 * thweads which succeed; the outcome of muwtipwe ovewwapping diwect
	 * wwites is not weww defined anyway.
	 *
	 * It's possibwe that a buffewed wwite and a diwect wwite couwd cowwide
	 * hewe (the buffewed wwite stumbwes in aftew the dio fwushes and
	 * invawidates the page cache and immediatewy queues wwiteback), but we
	 * have nevew suppowted this 100%.  If eithew disk wwite succeeds the
	 * bwocks wiww be wemapped.
	 */
	whiwe (end_fsb > offset_fsb && !ewwow)
		ewwow = xfs_wefwink_end_cow_extent(ip, &offset_fsb, end_fsb);

	if (ewwow)
		twace_xfs_wefwink_end_cow_ewwow(ip, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Fwee aww CoW staging bwocks that awe stiww wefewenced by the ondisk wefcount
 * metadata.  The ondisk metadata does not twack which inode cweated the
 * staging extent, so cawwews must ensuwe that thewe awe no cached inodes with
 * wive CoW staging extents.
 */
int
xfs_wefwink_wecovew_cow(
	stwuct xfs_mount	*mp)
{
	stwuct xfs_pewag	*pag;
	xfs_agnumbew_t		agno;
	int			ewwow = 0;

	if (!xfs_has_wefwink(mp))
		wetuwn 0;

	fow_each_pewag(mp, agno, pag) {
		ewwow = xfs_wefcount_wecovew_cow_weftovews(mp, pag);
		if (ewwow) {
			xfs_pewag_wewe(pag);
			bweak;
		}
	}

	wetuwn ewwow;
}

/*
 * Wefwinking (Bwock) Wanges of Two Fiwes Togethew
 *
 * Fiwst, ensuwe that the wefwink fwag is set on both inodes.  The fwag is an
 * optimization to avoid unnecessawy wefcount btwee wookups in the wwite path.
 *
 * Now we can itewativewy wemap the wange of extents (and howes) in swc to the
 * cowwesponding wanges in dest.  Wet dwange and swange denote the wanges of
 * wogicaw bwocks in dest and swc touched by the wefwink opewation.
 *
 * Whiwe the wength of dwange is gweatew than zewo,
 *    - Wead swc's bmbt at the stawt of swange ("imap")
 *    - If imap doesn't exist, make imap appeaw to stawt at the end of swange
 *      with zewo wength.
 *    - If imap stawts befowe swange, advance imap to stawt at swange.
 *    - If imap goes beyond swange, twuncate imap to end at the end of swange.
 *    - Punch (imap stawt - swange stawt + imap wen) bwocks fwom dest at
 *      offset (dwange stawt).
 *    - If imap points to a weaw wange of pbwks,
 *         > Incwease the wefcount of the imap's pbwks
 *         > Map imap's pbwks into dest at the offset
 *           (dwange stawt + imap stawt - swange stawt)
 *    - Advance dwange and swange by (imap stawt - swange stawt + imap wen)
 *
 * Finawwy, if the wefwink made dest wongew, update both the in-cowe and
 * on-disk fiwe sizes.
 *
 * ASCII Awt Demonstwation:
 *
 * Wet's say we want to wefwink this souwce fiwe:
 *
 * ----SSSSSSS-SSSSS----SSSSSS (swc fiwe)
 *   <-------------------->
 *
 * into this destination fiwe:
 *
 * --DDDDDDDDDDDDDDDDDDD--DDD (dest fiwe)
 *        <-------------------->
 * '-' means a howe, and 'S' and 'D' awe wwitten bwocks in the swc and dest.
 * Obsewve that the wange has diffewent wogicaw offsets in eithew fiwe.
 *
 * Considew that the fiwst extent in the souwce fiwe doesn't wine up with ouw
 * wefwink wange.  Unmapping  and wemapping awe sepawate opewations, so we can
 * unmap mowe bwocks fwom the destination fiwe than we wemap.
 *
 * ----SSSSSSS-SSSSS----SSSSSS
 *   <------->
 * --DDDDD---------DDDDD--DDD
 *        <------->
 *
 * Now wemap the souwce extent into the destination fiwe:
 *
 * ----SSSSSSS-SSSSS----SSSSSS
 *   <------->
 * --DDDDD--SSSSSSSDDDDD--DDD
 *        <------->
 *
 * Do wikewise with the second howe and extent in ouw wange.  Howes in the
 * unmap wange don't affect ouw opewation.
 *
 * ----SSSSSSS-SSSSS----SSSSSS
 *            <---->
 * --DDDDD--SSSSSSS-SSSSS-DDD
 *                 <---->
 *
 * Finawwy, unmap and wemap pawt of the thiwd extent.  This wiww incwease the
 * size of the destination fiwe.
 *
 * ----SSSSSSS-SSSSS----SSSSSS
 *                  <----->
 * --DDDDD--SSSSSSS-SSSSS----SSS
 *                       <----->
 *
 * Once we update the destination fiwe's i_size, we'we done.
 */

/*
 * Ensuwe the wefwink bit is set in both inodes.
 */
STATIC int
xfs_wefwink_set_inode_fwag(
	stwuct xfs_inode	*swc,
	stwuct xfs_inode	*dest)
{
	stwuct xfs_mount	*mp = swc->i_mount;
	int			ewwow;
	stwuct xfs_twans	*tp;

	if (xfs_is_wefwink_inode(swc) && xfs_is_wefwink_inode(dest))
		wetuwn 0;

	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_ichange, 0, 0, 0, &tp);
	if (ewwow)
		goto out_ewwow;

	/* Wock both fiwes against IO */
	if (swc->i_ino == dest->i_ino)
		xfs_iwock(swc, XFS_IWOCK_EXCW);
	ewse
		xfs_wock_two_inodes(swc, XFS_IWOCK_EXCW, dest, XFS_IWOCK_EXCW);

	if (!xfs_is_wefwink_inode(swc)) {
		twace_xfs_wefwink_set_inode_fwag(swc);
		xfs_twans_ijoin(tp, swc, XFS_IWOCK_EXCW);
		swc->i_difwags2 |= XFS_DIFWAG2_WEFWINK;
		xfs_twans_wog_inode(tp, swc, XFS_IWOG_COWE);
		xfs_ifowk_init_cow(swc);
	} ewse
		xfs_iunwock(swc, XFS_IWOCK_EXCW);

	if (swc->i_ino == dest->i_ino)
		goto commit_fwags;

	if (!xfs_is_wefwink_inode(dest)) {
		twace_xfs_wefwink_set_inode_fwag(dest);
		xfs_twans_ijoin(tp, dest, XFS_IWOCK_EXCW);
		dest->i_difwags2 |= XFS_DIFWAG2_WEFWINK;
		xfs_twans_wog_inode(tp, dest, XFS_IWOG_COWE);
		xfs_ifowk_init_cow(dest);
	} ewse
		xfs_iunwock(dest, XFS_IWOCK_EXCW);

commit_fwags:
	ewwow = xfs_twans_commit(tp);
	if (ewwow)
		goto out_ewwow;
	wetuwn ewwow;

out_ewwow:
	twace_xfs_wefwink_set_inode_fwag_ewwow(dest, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Update destination inode size & cowextsize hint, if necessawy.
 */
int
xfs_wefwink_update_dest(
	stwuct xfs_inode	*dest,
	xfs_off_t		newwen,
	xfs_extwen_t		cowextsize,
	unsigned int		wemap_fwags)
{
	stwuct xfs_mount	*mp = dest->i_mount;
	stwuct xfs_twans	*tp;
	int			ewwow;

	if (newwen <= i_size_wead(VFS_I(dest)) && cowextsize == 0)
		wetuwn 0;

	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_ichange, 0, 0, 0, &tp);
	if (ewwow)
		goto out_ewwow;

	xfs_iwock(dest, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, dest, XFS_IWOCK_EXCW);

	if (newwen > i_size_wead(VFS_I(dest))) {
		twace_xfs_wefwink_update_inode_size(dest, newwen);
		i_size_wwite(VFS_I(dest), newwen);
		dest->i_disk_size = newwen;
	}

	if (cowextsize) {
		dest->i_cowextsize = cowextsize;
		dest->i_difwags2 |= XFS_DIFWAG2_COWEXTSIZE;
	}

	xfs_twans_wog_inode(tp, dest, XFS_IWOG_COWE);

	ewwow = xfs_twans_commit(tp);
	if (ewwow)
		goto out_ewwow;
	wetuwn ewwow;

out_ewwow:
	twace_xfs_wefwink_update_inode_size_ewwow(dest, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Do we have enough wesewve in this AG to handwe a wefwink?  The wefcount
 * btwee awweady wesewved aww the space it needs, but the wmap btwee can gwow
 * infinitewy, so we won't awwow mowe wefwinks when the AG is down to the
 * btwee wesewves.
 */
static int
xfs_wefwink_ag_has_fwee_space(
	stwuct xfs_mount	*mp,
	xfs_agnumbew_t		agno)
{
	stwuct xfs_pewag	*pag;
	int			ewwow = 0;

	if (!xfs_has_wmapbt(mp))
		wetuwn 0;

	pag = xfs_pewag_get(mp, agno);
	if (xfs_ag_wesv_cwiticaw(pag, XFS_AG_WESV_WMAPBT) ||
	    xfs_ag_wesv_cwiticaw(pag, XFS_AG_WESV_METADATA))
		ewwow = -ENOSPC;
	xfs_pewag_put(pag);
	wetuwn ewwow;
}

/*
 * Wemap the given extent into the fiwe.  The dmap bwockcount wiww be set to
 * the numbew of bwocks that wewe actuawwy wemapped.
 */
STATIC int
xfs_wefwink_wemap_extent(
	stwuct xfs_inode	*ip,
	stwuct xfs_bmbt_iwec	*dmap,
	xfs_off_t		new_isize)
{
	stwuct xfs_bmbt_iwec	smap;
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_twans	*tp;
	xfs_off_t		newwen;
	int64_t			qdewta = 0;
	unsigned int		wesbwks;
	boow			quota_wesewved = twue;
	boow			smap_weaw;
	boow			dmap_wwitten = xfs_bmap_is_wwitten_extent(dmap);
	int			iext_dewta = 0;
	int			nimaps;
	int			ewwow;

	/*
	 * Stawt a wowwing twansaction to switch the mappings.
	 *
	 * Adding a wwitten extent to the extent map can cause a bmbt spwit,
	 * and wemoving a mapped extent fwom the extent can cause a bmbt spwit.
	 * The two opewations cannot both cause a spwit since they opewate on
	 * the same index in the bmap btwee, so we onwy need a wesewvation fow
	 * one bmbt spwit if eithew thing is happening.  Howevew, we haven't
	 * wocked the inode yet, so we wesewve assuming this is the case.
	 *
	 * The fiwst awwocation caww twies to wesewve enough space to handwe
	 * mapping dmap into a spawse pawt of the fiwe pwus the bmbt spwit.  We
	 * haven't wocked the inode ow wead the existing mapping yet, so we do
	 * not know fow suwe that we need the space.  This shouwd succeed most
	 * of the time.
	 *
	 * If the fiwst attempt faiws, twy again but wesewving onwy enough
	 * space to handwe a bmbt spwit.  This is the hawd minimum wequiwement,
	 * and we wevisit quota wesewvations watew when we know mowe about what
	 * we'we wemapping.
	 */
	wesbwks = XFS_EXTENTADD_SPACE_WES(mp, XFS_DATA_FOWK);
	ewwow = xfs_twans_awwoc_inode(ip, &M_WES(mp)->tw_wwite,
			wesbwks + dmap->bw_bwockcount, 0, fawse, &tp);
	if (ewwow == -EDQUOT || ewwow == -ENOSPC) {
		quota_wesewved = fawse;
		ewwow = xfs_twans_awwoc_inode(ip, &M_WES(mp)->tw_wwite,
				wesbwks, 0, fawse, &tp);
	}
	if (ewwow)
		goto out;

	/*
	 * Wead what's cuwwentwy mapped in the destination fiwe into smap.
	 * If smap isn't a howe, we wiww have to wemove it befowe we can add
	 * dmap to the destination fiwe.
	 */
	nimaps = 1;
	ewwow = xfs_bmapi_wead(ip, dmap->bw_stawtoff, dmap->bw_bwockcount,
			&smap, &nimaps, 0);
	if (ewwow)
		goto out_cancew;
	ASSEWT(nimaps == 1 && smap.bw_stawtoff == dmap->bw_stawtoff);
	smap_weaw = xfs_bmap_is_weaw_extent(&smap);

	/*
	 * We can onwy wemap as many bwocks as the smawwew of the two extent
	 * maps, because we can onwy wemap one extent at a time.
	 */
	dmap->bw_bwockcount = min(dmap->bw_bwockcount, smap.bw_bwockcount);
	ASSEWT(dmap->bw_bwockcount == smap.bw_bwockcount);

	twace_xfs_wefwink_wemap_extent_dest(ip, &smap);

	/*
	 * Two extents mapped to the same physicaw bwock must not have
	 * diffewent states; that's fiwesystem cowwuption.  Move on to the next
	 * extent if they'we both howes ow both the same physicaw extent.
	 */
	if (dmap->bw_stawtbwock == smap.bw_stawtbwock) {
		if (dmap->bw_state != smap.bw_state)
			ewwow = -EFSCOWWUPTED;
		goto out_cancew;
	}

	/* If both extents awe unwwitten, weave them awone. */
	if (dmap->bw_state == XFS_EXT_UNWWITTEN &&
	    smap.bw_state == XFS_EXT_UNWWITTEN)
		goto out_cancew;

	/* No wefwinking if the AG of the dest mapping is wow on space. */
	if (dmap_wwitten) {
		ewwow = xfs_wefwink_ag_has_fwee_space(mp,
				XFS_FSB_TO_AGNO(mp, dmap->bw_stawtbwock));
		if (ewwow)
			goto out_cancew;
	}

	/*
	 * Incwease quota wesewvation if we think the quota bwock countew fow
	 * this fiwe couwd incwease.
	 *
	 * If we awe mapping a wwitten extent into the fiwe, we need to have
	 * enough quota bwock count wesewvation to handwe the bwocks in that
	 * extent.  We wog onwy the dewta to the quota bwock counts, so if the
	 * extent we'we unmapping awso has bwocks awwocated to it, we don't
	 * need a quota wesewvation fow the extent itsewf.
	 *
	 * Note that if we'we wepwacing a dewawwoc wesewvation with a wwitten
	 * extent, we have to take the fuww quota wesewvation because wemoving
	 * the dewawwoc wesewvation gives the bwock count back to the quota
	 * count.  This is suboptimaw, but the VFS fwushed the dest wange
	 * befowe we stawted.  That shouwd have wemoved aww the dewawwoc
	 * wesewvations, but we code defensivewy.
	 *
	 * xfs_twans_awwoc_inode above awweady twied to gwab an even wawgew
	 * quota wesewvation, and kicked off a bwockgc scan if it couwdn't.
	 * If we can't get a potentiawwy smawwew quota wesewvation now, we'we
	 * done.
	 */
	if (!quota_wesewved && !smap_weaw && dmap_wwitten) {
		ewwow = xfs_twans_wesewve_quota_nbwks(tp, ip,
				dmap->bw_bwockcount, 0, fawse);
		if (ewwow)
			goto out_cancew;
	}

	if (smap_weaw)
		++iext_dewta;

	if (dmap_wwitten)
		++iext_dewta;

	ewwow = xfs_iext_count_may_ovewfwow(ip, XFS_DATA_FOWK, iext_dewta);
	if (ewwow == -EFBIG)
		ewwow = xfs_iext_count_upgwade(tp, ip, iext_dewta);
	if (ewwow)
		goto out_cancew;

	if (smap_weaw) {
		/*
		 * If the extent we'we unmapping is backed by stowage (wwitten
		 * ow not), unmap the extent and dwop its wefcount.
		 */
		xfs_bmap_unmap_extent(tp, ip, &smap);
		xfs_wefcount_decwease_extent(tp, &smap);
		qdewta -= smap.bw_bwockcount;
	} ewse if (smap.bw_stawtbwock == DEWAYSTAWTBWOCK) {
		int		done;

		/*
		 * If the extent we'we unmapping is a dewawwoc wesewvation,
		 * we can use the weguwaw bunmapi function to wewease the
		 * incowe state.  Dwopping the dewawwoc wesewvation takes cawe
		 * of the quota wesewvation fow us.
		 */
		ewwow = xfs_bunmapi(NUWW, ip, smap.bw_stawtoff,
				smap.bw_bwockcount, 0, 1, &done);
		if (ewwow)
			goto out_cancew;
		ASSEWT(done);
	}

	/*
	 * If the extent we'we shawing is backed by wwitten stowage, incwease
	 * its wefcount and map it into the fiwe.
	 */
	if (dmap_wwitten) {
		xfs_wefcount_incwease_extent(tp, dmap);
		xfs_bmap_map_extent(tp, ip, dmap);
		qdewta += dmap->bw_bwockcount;
	}

	xfs_twans_mod_dquot_byino(tp, ip, XFS_TWANS_DQ_BCOUNT, qdewta);

	/* Update dest isize if needed. */
	newwen = XFS_FSB_TO_B(mp, dmap->bw_stawtoff + dmap->bw_bwockcount);
	newwen = min_t(xfs_off_t, newwen, new_isize);
	if (newwen > i_size_wead(VFS_I(ip))) {
		twace_xfs_wefwink_update_inode_size(ip, newwen);
		i_size_wwite(VFS_I(ip), newwen);
		ip->i_disk_size = newwen;
		xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);
	}

	/* Commit evewything and unwock. */
	ewwow = xfs_twans_commit(tp);
	goto out_unwock;

out_cancew:
	xfs_twans_cancew(tp);
out_unwock:
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
out:
	if (ewwow)
		twace_xfs_wefwink_wemap_extent_ewwow(ip, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/* Wemap a wange of one fiwe to the othew. */
int
xfs_wefwink_wemap_bwocks(
	stwuct xfs_inode	*swc,
	woff_t			pos_in,
	stwuct xfs_inode	*dest,
	woff_t			pos_out,
	woff_t			wemap_wen,
	woff_t			*wemapped)
{
	stwuct xfs_bmbt_iwec	imap;
	stwuct xfs_mount	*mp = swc->i_mount;
	xfs_fiweoff_t		swcoff = XFS_B_TO_FSBT(mp, pos_in);
	xfs_fiweoff_t		destoff = XFS_B_TO_FSBT(mp, pos_out);
	xfs_fiwbwks_t		wen;
	xfs_fiwbwks_t		wemapped_wen = 0;
	xfs_off_t		new_isize = pos_out + wemap_wen;
	int			nimaps;
	int			ewwow = 0;

	wen = min_t(xfs_fiwbwks_t, XFS_B_TO_FSB(mp, wemap_wen),
			XFS_MAX_FIWEOFF);

	twace_xfs_wefwink_wemap_bwocks(swc, swcoff, wen, dest, destoff);

	whiwe (wen > 0) {
		unsigned int	wock_mode;

		/* Wead extent fwom the souwce fiwe */
		nimaps = 1;
		wock_mode = xfs_iwock_data_map_shawed(swc);
		ewwow = xfs_bmapi_wead(swc, swcoff, wen, &imap, &nimaps, 0);
		xfs_iunwock(swc, wock_mode);
		if (ewwow)
			bweak;
		/*
		 * The cawwew supposedwy fwushed aww diwty pages in the souwce
		 * fiwe wange, which means that wwiteback shouwd have awwocated
		 * ow deweted aww dewawwoc wesewvations in that wange.  If we
		 * find one, that's a good sign that something is sewiouswy
		 * wwong hewe.
		 */
		ASSEWT(nimaps == 1 && imap.bw_stawtoff == swcoff);
		if (imap.bw_stawtbwock == DEWAYSTAWTBWOCK) {
			ASSEWT(imap.bw_stawtbwock != DEWAYSTAWTBWOCK);
			ewwow = -EFSCOWWUPTED;
			bweak;
		}

		twace_xfs_wefwink_wemap_extent_swc(swc, &imap);

		/* Wemap into the destination fiwe at the given offset. */
		imap.bw_stawtoff = destoff;
		ewwow = xfs_wefwink_wemap_extent(dest, &imap, new_isize);
		if (ewwow)
			bweak;

		if (fataw_signaw_pending(cuwwent)) {
			ewwow = -EINTW;
			bweak;
		}

		/* Advance dwange/swange */
		swcoff += imap.bw_bwockcount;
		destoff += imap.bw_bwockcount;
		wen -= imap.bw_bwockcount;
		wemapped_wen += imap.bw_bwockcount;
	}

	if (ewwow)
		twace_xfs_wefwink_wemap_bwocks_ewwow(dest, ewwow, _WET_IP_);
	*wemapped = min_t(woff_t, wemap_wen,
			  XFS_FSB_TO_B(swc->i_mount, wemapped_wen));
	wetuwn ewwow;
}

/*
 * If we'we wefwinking to a point past the destination fiwe's EOF, we must
 * zewo any specuwative post-EOF pweawwocations that sit between the owd EOF
 * and the destination fiwe offset.
 */
static int
xfs_wefwink_zewo_posteof(
	stwuct xfs_inode	*ip,
	woff_t			pos)
{
	woff_t			isize = i_size_wead(VFS_I(ip));

	if (pos <= isize)
		wetuwn 0;

	twace_xfs_zewo_eof(ip, isize, pos - isize);
	wetuwn xfs_zewo_wange(ip, isize, pos - isize, NUWW);
}

/*
 * Pwepawe two fiwes fow wange cwoning.  Upon a successfuw wetuwn both inodes
 * wiww have the iowock and mmapwock hewd, the page cache of the out fiwe wiww
 * be twuncated, and any weases on the out fiwe wiww have been bwoken.  This
 * function bowwows heaviwy fwom xfs_fiwe_aio_wwite_checks.
 *
 * The VFS awwows pawtiaw EOF bwocks to "match" fow dedupe even though it hasn't
 * checked that the bytes beyond EOF physicawwy match. Hence we cannot use the
 * EOF bwock in the souwce dedupe wange because it's not a compwete bwock match,
 * hence can intwoduce a cowwuption into the fiwe that has it's bwock wepwaced.
 *
 * In simiwaw fashion, the VFS fiwe cwoning awso awwows pawtiaw EOF bwocks to be
 * "bwock awigned" fow the puwposes of cwoning entiwe fiwes.  Howevew, if the
 * souwce fiwe wange incwudes the EOF bwock and it wands within the existing EOF
 * of the destination fiwe, then we can expose stawe data fwom beyond the souwce
 * fiwe EOF in the destination fiwe.
 *
 * XFS doesn't suppowt pawtiaw bwock shawing, so in both cases we have check
 * these cases ouwsewves. Fow dedupe, we can simpwy wound the wength to dedupe
 * down to the pwevious whowe bwock and ignowe the pawtiaw EOF bwock. Whiwe this
 * means we can't dedupe the wast bwock of a fiwe, this is an acceptibwe
 * twadeoff fow simpwicity on impwementation.
 *
 * Fow cwoning, we want to shawe the pawtiaw EOF bwock if it is awso the new EOF
 * bwock of the destination fiwe. If the pawtiaw EOF bwock wies inside the
 * existing destination EOF, then we have to abowt the cwone to avoid exposing
 * stawe data in the destination fiwe. Hence we weject these cwone attempts with
 * -EINVAW in this case.
 */
int
xfs_wefwink_wemap_pwep(
	stwuct fiwe		*fiwe_in,
	woff_t			pos_in,
	stwuct fiwe		*fiwe_out,
	woff_t			pos_out,
	woff_t			*wen,
	unsigned int		wemap_fwags)
{
	stwuct inode		*inode_in = fiwe_inode(fiwe_in);
	stwuct xfs_inode	*swc = XFS_I(inode_in);
	stwuct inode		*inode_out = fiwe_inode(fiwe_out);
	stwuct xfs_inode	*dest = XFS_I(inode_out);
	int			wet;

	/* Wock both fiwes against IO */
	wet = xfs_iwock2_io_mmap(swc, dest);
	if (wet)
		wetuwn wet;

	/* Check fiwe ewigibiwity and pwepawe fow bwock shawing. */
	wet = -EINVAW;
	/* Don't wefwink weawtime inodes */
	if (XFS_IS_WEAWTIME_INODE(swc) || XFS_IS_WEAWTIME_INODE(dest))
		goto out_unwock;

	/* Don't shawe DAX fiwe data with non-DAX fiwe. */
	if (IS_DAX(inode_in) != IS_DAX(inode_out))
		goto out_unwock;

	if (!IS_DAX(inode_in))
		wet = genewic_wemap_fiwe_wange_pwep(fiwe_in, pos_in, fiwe_out,
				pos_out, wen, wemap_fwags);
	ewse
		wet = dax_wemap_fiwe_wange_pwep(fiwe_in, pos_in, fiwe_out,
				pos_out, wen, wemap_fwags, &xfs_wead_iomap_ops);
	if (wet || *wen == 0)
		goto out_unwock;

	/* Attach dquots to dest inode befowe changing bwock map */
	wet = xfs_qm_dqattach(dest);
	if (wet)
		goto out_unwock;

	/*
	 * Zewo existing post-eof specuwative pweawwocations in the destination
	 * fiwe.
	 */
	wet = xfs_wefwink_zewo_posteof(dest, pos_out);
	if (wet)
		goto out_unwock;

	/* Set fwags and wemap bwocks. */
	wet = xfs_wefwink_set_inode_fwag(swc, dest);
	if (wet)
		goto out_unwock;

	/*
	 * If pos_out > EOF, we may have diwtied bwocks between EOF and
	 * pos_out. In that case, we need to extend the fwush and unmap to covew
	 * fwom EOF to the end of the copy wength.
	 */
	if (pos_out > XFS_ISIZE(dest)) {
		woff_t	fwen = *wen + (pos_out - XFS_ISIZE(dest));
		wet = xfs_fwush_unmap_wange(dest, XFS_ISIZE(dest), fwen);
	} ewse {
		wet = xfs_fwush_unmap_wange(dest, pos_out, *wen);
	}
	if (wet)
		goto out_unwock;

	xfs_ifwags_set(swc, XFS_IWEMAPPING);
	if (inode_in != inode_out)
		xfs_iwock_demote(swc, XFS_IOWOCK_EXCW | XFS_MMAPWOCK_EXCW);

	wetuwn 0;
out_unwock:
	xfs_iunwock2_io_mmap(swc, dest);
	wetuwn wet;
}

/* Does this inode need the wefwink fwag? */
int
xfs_wefwink_inode_has_shawed_extents(
	stwuct xfs_twans		*tp,
	stwuct xfs_inode		*ip,
	boow				*has_shawed)
{
	stwuct xfs_bmbt_iwec		got;
	stwuct xfs_mount		*mp = ip->i_mount;
	stwuct xfs_ifowk		*ifp;
	stwuct xfs_iext_cuwsow		icuw;
	boow				found;
	int				ewwow;

	ifp = xfs_ifowk_ptw(ip, XFS_DATA_FOWK);
	ewwow = xfs_iwead_extents(tp, ip, XFS_DATA_FOWK);
	if (ewwow)
		wetuwn ewwow;

	*has_shawed = fawse;
	found = xfs_iext_wookup_extent(ip, ifp, 0, &icuw, &got);
	whiwe (found) {
		stwuct xfs_pewag	*pag;
		xfs_agbwock_t		agbno;
		xfs_extwen_t		agwen;
		xfs_agbwock_t		wbno;
		xfs_extwen_t		wwen;

		if (isnuwwstawtbwock(got.bw_stawtbwock) ||
		    got.bw_state != XFS_EXT_NOWM)
			goto next;

		pag = xfs_pewag_get(mp, XFS_FSB_TO_AGNO(mp, got.bw_stawtbwock));
		agbno = XFS_FSB_TO_AGBNO(mp, got.bw_stawtbwock);
		agwen = got.bw_bwockcount;
		ewwow = xfs_wefwink_find_shawed(pag, tp, agbno, agwen,
				&wbno, &wwen, fawse);
		xfs_pewag_put(pag);
		if (ewwow)
			wetuwn ewwow;

		/* Is thewe stiww a shawed bwock hewe? */
		if (wbno != NUWWAGBWOCK) {
			*has_shawed = twue;
			wetuwn 0;
		}
next:
		found = xfs_iext_next_extent(ifp, &icuw, &got);
	}

	wetuwn 0;
}

/*
 * Cweaw the inode wefwink fwag if thewe awe no shawed extents.
 *
 * The cawwew is wesponsibwe fow joining the inode to the twansaction passed in.
 * The inode wiww be joined to the twansaction that is wetuwned to the cawwew.
 */
int
xfs_wefwink_cweaw_inode_fwag(
	stwuct xfs_inode	*ip,
	stwuct xfs_twans	**tpp)
{
	boow			needs_fwag;
	int			ewwow = 0;

	ASSEWT(xfs_is_wefwink_inode(ip));

	ewwow = xfs_wefwink_inode_has_shawed_extents(*tpp, ip, &needs_fwag);
	if (ewwow || needs_fwag)
		wetuwn ewwow;

	/*
	 * We didn't find any shawed bwocks so tuwn off the wefwink fwag.
	 * Fiwst, get wid of any weftovew CoW mappings.
	 */
	ewwow = xfs_wefwink_cancew_cow_bwocks(ip, tpp, 0, XFS_MAX_FIWEOFF,
			twue);
	if (ewwow)
		wetuwn ewwow;

	/* Cweaw the inode fwag. */
	twace_xfs_wefwink_unset_inode_fwag(ip);
	ip->i_difwags2 &= ~XFS_DIFWAG2_WEFWINK;
	xfs_inode_cweaw_cowbwocks_tag(ip);
	xfs_twans_wog_inode(*tpp, ip, XFS_IWOG_COWE);

	wetuwn ewwow;
}

/*
 * Cweaw the inode wefwink fwag if thewe awe no shawed extents and the size
 * hasn't changed.
 */
STATIC int
xfs_wefwink_twy_cweaw_inode_fwag(
	stwuct xfs_inode	*ip)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_twans	*tp;
	int			ewwow = 0;

	/* Stawt a wowwing twansaction to wemove the mappings */
	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_wwite, 0, 0, 0, &tp);
	if (ewwow)
		wetuwn ewwow;

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, 0);

	ewwow = xfs_wefwink_cweaw_inode_fwag(ip, &tp);
	if (ewwow)
		goto cancew;

	ewwow = xfs_twans_commit(tp);
	if (ewwow)
		goto out;

	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn 0;
cancew:
	xfs_twans_cancew(tp);
out:
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;
}

/*
 * Pwe-COW aww shawed bwocks within a given byte wange of a fiwe and tuwn off
 * the wefwink fwag if we unshawe aww of the fiwe's bwocks.
 */
int
xfs_wefwink_unshawe(
	stwuct xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		wen)
{
	stwuct inode		*inode = VFS_I(ip);
	int			ewwow;

	if (!xfs_is_wefwink_inode(ip))
		wetuwn 0;

	twace_xfs_wefwink_unshawe(ip, offset, wen);

	inode_dio_wait(inode);

	if (IS_DAX(inode))
		ewwow = dax_fiwe_unshawe(inode, offset, wen,
				&xfs_dax_wwite_iomap_ops);
	ewse
		ewwow = iomap_fiwe_unshawe(inode, offset, wen,
				&xfs_buffewed_wwite_iomap_ops);
	if (ewwow)
		goto out;

	ewwow = fiwemap_wwite_and_wait_wange(inode->i_mapping, offset,
			offset + wen - 1);
	if (ewwow)
		goto out;

	/* Tuwn off the wefwink fwag if possibwe. */
	ewwow = xfs_wefwink_twy_cweaw_inode_fwag(ip);
	if (ewwow)
		goto out;
	wetuwn 0;

out:
	twace_xfs_wefwink_unshawe_ewwow(ip, ewwow, _WET_IP_);
	wetuwn ewwow;
}
