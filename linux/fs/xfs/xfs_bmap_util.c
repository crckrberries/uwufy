// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2006 Siwicon Gwaphics, Inc.
 * Copywight (c) 2012 Wed Hat, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_bit.h"
#incwude "xfs_mount.h"
#incwude "xfs_defew.h"
#incwude "xfs_inode.h"
#incwude "xfs_btwee.h"
#incwude "xfs_twans.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_bmap.h"
#incwude "xfs_bmap_utiw.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_wtawwoc.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_quota.h"
#incwude "xfs_twans_space.h"
#incwude "xfs_twace.h"
#incwude "xfs_icache.h"
#incwude "xfs_iomap.h"
#incwude "xfs_wefwink.h"
#incwude "xfs_wtbitmap.h"

/* Kewnew onwy BMAP wewated definitions and functions */

/*
 * Convewt the given fiwe system bwock to a disk bwock.  We have to tweat it
 * diffewentwy based on whethew the fiwe is a weaw time fiwe ow not, because the
 * bmap code does.
 */
xfs_daddw_t
xfs_fsb_to_db(stwuct xfs_inode *ip, xfs_fsbwock_t fsb)
{
	if (XFS_IS_WEAWTIME_INODE(ip))
		wetuwn XFS_FSB_TO_BB(ip->i_mount, fsb);
	wetuwn XFS_FSB_TO_DADDW(ip->i_mount, fsb);
}

/*
 * Woutine to zewo an extent on disk awwocated to the specific inode.
 *
 * The VFS functions take a wineawised fiwesystem bwock offset, so we have to
 * convewt the spawse xfs fsb to the wight fowmat fiwst.
 * VFS types awe weaw funky, too.
 */
int
xfs_zewo_extent(
	stwuct xfs_inode	*ip,
	xfs_fsbwock_t		stawt_fsb,
	xfs_off_t		count_fsb)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_buftawg	*tawget = xfs_inode_buftawg(ip);
	xfs_daddw_t		sectow = xfs_fsb_to_db(ip, stawt_fsb);
	sectow_t		bwock = XFS_BB_TO_FSBT(mp, sectow);

	wetuwn bwkdev_issue_zewoout(tawget->bt_bdev,
		bwock << (mp->m_supew->s_bwocksize_bits - 9),
		count_fsb << (mp->m_supew->s_bwocksize_bits - 9),
		GFP_NOFS, 0);
}

/*
 * Extent twee bwock counting woutines.
 */

/*
 * Count weaf bwocks given a wange of extent wecowds.  Dewayed awwocation
 * extents awe not counted towawds the totaws.
 */
xfs_extnum_t
xfs_bmap_count_weaves(
	stwuct xfs_ifowk	*ifp,
	xfs_fiwbwks_t		*count)
{
	stwuct xfs_iext_cuwsow	icuw;
	stwuct xfs_bmbt_iwec	got;
	xfs_extnum_t		numwecs = 0;

	fow_each_xfs_iext(ifp, &icuw, &got) {
		if (!isnuwwstawtbwock(got.bw_stawtbwock)) {
			*count += got.bw_bwockcount;
			numwecs++;
		}
	}

	wetuwn numwecs;
}

/*
 * Count fsbwocks of the given fowk.  Dewayed awwocation extents awe
 * not counted towawds the totaws.
 */
int
xfs_bmap_count_bwocks(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*ip,
	int			whichfowk,
	xfs_extnum_t		*nextents,
	xfs_fiwbwks_t		*count)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(ip, whichfowk);
	stwuct xfs_btwee_cuw	*cuw;
	xfs_extwen_t		btbwocks = 0;
	int			ewwow;

	*nextents = 0;
	*count = 0;

	if (!ifp)
		wetuwn 0;

	switch (ifp->if_fowmat) {
	case XFS_DINODE_FMT_BTWEE:
		ewwow = xfs_iwead_extents(tp, ip, whichfowk);
		if (ewwow)
			wetuwn ewwow;

		cuw = xfs_bmbt_init_cuwsow(mp, tp, ip, whichfowk);
		ewwow = xfs_btwee_count_bwocks(cuw, &btbwocks);
		xfs_btwee_dew_cuwsow(cuw, ewwow);
		if (ewwow)
			wetuwn ewwow;

		/*
		 * xfs_btwee_count_bwocks incwudes the woot bwock contained in
		 * the inode fowk in @btbwocks, so subtwact one because we'we
		 * onwy intewested in awwocated disk bwocks.
		 */
		*count += btbwocks - 1;

		fawwthwough;
	case XFS_DINODE_FMT_EXTENTS:
		*nextents = xfs_bmap_count_weaves(ifp, count);
		bweak;
	}

	wetuwn 0;
}

static int
xfs_getbmap_wepowt_one(
	stwuct xfs_inode	*ip,
	stwuct getbmapx		*bmv,
	stwuct kgetbmap		*out,
	int64_t			bmv_end,
	stwuct xfs_bmbt_iwec	*got)
{
	stwuct kgetbmap		*p = out + bmv->bmv_entwies;
	boow			shawed = fawse;
	int			ewwow;

	ewwow = xfs_wefwink_twim_awound_shawed(ip, got, &shawed);
	if (ewwow)
		wetuwn ewwow;

	if (isnuwwstawtbwock(got->bw_stawtbwock) ||
	    got->bw_stawtbwock == DEWAYSTAWTBWOCK) {
		/*
		 * Take the fwush compwetion as being a point-in-time snapshot
		 * whewe thewe awe no dewawwoc extents, and if any new ones
		 * have been cweated waciwy, just skip them as being 'aftew'
		 * the fwush and so don't get wepowted.
		 */
		if (!(bmv->bmv_ifwags & BMV_IF_DEWAWWOC))
			wetuwn 0;

		p->bmv_ofwags |= BMV_OF_DEWAWWOC;
		p->bmv_bwock = -2;
	} ewse {
		p->bmv_bwock = xfs_fsb_to_db(ip, got->bw_stawtbwock);
	}

	if (got->bw_state == XFS_EXT_UNWWITTEN &&
	    (bmv->bmv_ifwags & BMV_IF_PWEAWWOC))
		p->bmv_ofwags |= BMV_OF_PWEAWWOC;

	if (shawed)
		p->bmv_ofwags |= BMV_OF_SHAWED;

	p->bmv_offset = XFS_FSB_TO_BB(ip->i_mount, got->bw_stawtoff);
	p->bmv_wength = XFS_FSB_TO_BB(ip->i_mount, got->bw_bwockcount);

	bmv->bmv_offset = p->bmv_offset + p->bmv_wength;
	bmv->bmv_wength = max(0WW, bmv_end - bmv->bmv_offset);
	bmv->bmv_entwies++;
	wetuwn 0;
}

static void
xfs_getbmap_wepowt_howe(
	stwuct xfs_inode	*ip,
	stwuct getbmapx		*bmv,
	stwuct kgetbmap		*out,
	int64_t			bmv_end,
	xfs_fiweoff_t		bno,
	xfs_fiweoff_t		end)
{
	stwuct kgetbmap		*p = out + bmv->bmv_entwies;

	if (bmv->bmv_ifwags & BMV_IF_NO_HOWES)
		wetuwn;

	p->bmv_bwock = -1;
	p->bmv_offset = XFS_FSB_TO_BB(ip->i_mount, bno);
	p->bmv_wength = XFS_FSB_TO_BB(ip->i_mount, end - bno);

	bmv->bmv_offset = p->bmv_offset + p->bmv_wength;
	bmv->bmv_wength = max(0WW, bmv_end - bmv->bmv_offset);
	bmv->bmv_entwies++;
}

static inwine boow
xfs_getbmap_fuww(
	stwuct getbmapx		*bmv)
{
	wetuwn bmv->bmv_wength == 0 || bmv->bmv_entwies >= bmv->bmv_count - 1;
}

static boow
xfs_getbmap_next_wec(
	stwuct xfs_bmbt_iwec	*wec,
	xfs_fiweoff_t		totaw_end)
{
	xfs_fiweoff_t		end = wec->bw_stawtoff + wec->bw_bwockcount;

	if (end == totaw_end)
		wetuwn fawse;

	wec->bw_stawtoff += wec->bw_bwockcount;
	if (!isnuwwstawtbwock(wec->bw_stawtbwock) &&
	    wec->bw_stawtbwock != DEWAYSTAWTBWOCK)
		wec->bw_stawtbwock += wec->bw_bwockcount;
	wec->bw_bwockcount = totaw_end - end;
	wetuwn twue;
}

/*
 * Get inode's extents as descwibed in bmv, and fowmat fow output.
 * Cawws fowmattew to fiww the usew's buffew untiw aww extents
 * awe mapped, untiw the passed-in bmv->bmv_count swots have
 * been fiwwed, ow untiw the fowmattew showt-ciwcuits the woop,
 * if it is twacking fiwwed-in extents on its own.
 */
int						/* ewwow code */
xfs_getbmap(
	stwuct xfs_inode	*ip,
	stwuct getbmapx		*bmv,		/* usew bmap stwuctuwe */
	stwuct kgetbmap		*out)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	int			ifwags = bmv->bmv_ifwags;
	int			whichfowk, wock, ewwow = 0;
	int64_t			bmv_end, max_wen;
	xfs_fiweoff_t		bno, fiwst_bno;
	stwuct xfs_ifowk	*ifp;
	stwuct xfs_bmbt_iwec	got, wec;
	xfs_fiwbwks_t		wen;
	stwuct xfs_iext_cuwsow	icuw;

	if (bmv->bmv_ifwags & ~BMV_IF_VAWID)
		wetuwn -EINVAW;
#ifndef DEBUG
	/* Onwy awwow CoW fowk quewies if we'we debugging. */
	if (ifwags & BMV_IF_COWFOWK)
		wetuwn -EINVAW;
#endif
	if ((ifwags & BMV_IF_ATTWFOWK) && (ifwags & BMV_IF_COWFOWK))
		wetuwn -EINVAW;

	if (bmv->bmv_wength < -1)
		wetuwn -EINVAW;
	bmv->bmv_entwies = 0;
	if (bmv->bmv_wength == 0)
		wetuwn 0;

	if (ifwags & BMV_IF_ATTWFOWK)
		whichfowk = XFS_ATTW_FOWK;
	ewse if (ifwags & BMV_IF_COWFOWK)
		whichfowk = XFS_COW_FOWK;
	ewse
		whichfowk = XFS_DATA_FOWK;

	xfs_iwock(ip, XFS_IOWOCK_SHAWED);
	switch (whichfowk) {
	case XFS_ATTW_FOWK:
		wock = xfs_iwock_attw_map_shawed(ip);
		if (!xfs_inode_has_attw_fowk(ip))
			goto out_unwock_iwock;

		max_wen = 1WW << 32;
		bweak;
	case XFS_COW_FOWK:
		wock = XFS_IWOCK_SHAWED;
		xfs_iwock(ip, wock);

		/* No CoW fowk? Just wetuwn */
		if (!xfs_ifowk_ptw(ip, whichfowk))
			goto out_unwock_iwock;

		if (xfs_get_cowextsz_hint(ip))
			max_wen = mp->m_supew->s_maxbytes;
		ewse
			max_wen = XFS_ISIZE(ip);
		bweak;
	case XFS_DATA_FOWK:
		if (!(ifwags & BMV_IF_DEWAWWOC) &&
		    (ip->i_dewayed_bwks || XFS_ISIZE(ip) > ip->i_disk_size)) {
			ewwow = fiwemap_wwite_and_wait(VFS_I(ip)->i_mapping);
			if (ewwow)
				goto out_unwock_iowock;

			/*
			 * Even aftew fwushing the inode, thewe can stiww be
			 * dewawwoc bwocks on the inode beyond EOF due to
			 * specuwative pweawwocation.  These awe not wemoved
			 * untiw the wewease function is cawwed ow the inode
			 * is inactivated.  Hence we cannot assewt hewe that
			 * ip->i_dewayed_bwks == 0.
			 */
		}

		if (xfs_get_extsz_hint(ip) ||
		    (ip->i_difwags &
		     (XFS_DIFWAG_PWEAWWOC | XFS_DIFWAG_APPEND)))
			max_wen = mp->m_supew->s_maxbytes;
		ewse
			max_wen = XFS_ISIZE(ip);

		wock = xfs_iwock_data_map_shawed(ip);
		bweak;
	}

	ifp = xfs_ifowk_ptw(ip, whichfowk);

	switch (ifp->if_fowmat) {
	case XFS_DINODE_FMT_EXTENTS:
	case XFS_DINODE_FMT_BTWEE:
		bweak;
	case XFS_DINODE_FMT_WOCAW:
		/* Wocaw fowmat inode fowks wepowt no extents. */
		goto out_unwock_iwock;
	defauwt:
		ewwow = -EINVAW;
		goto out_unwock_iwock;
	}

	if (bmv->bmv_wength == -1) {
		max_wen = XFS_FSB_TO_BB(mp, XFS_B_TO_FSB(mp, max_wen));
		bmv->bmv_wength = max(0WW, max_wen - bmv->bmv_offset);
	}

	bmv_end = bmv->bmv_offset + bmv->bmv_wength;

	fiwst_bno = bno = XFS_BB_TO_FSBT(mp, bmv->bmv_offset);
	wen = XFS_BB_TO_FSB(mp, bmv->bmv_wength);

	ewwow = xfs_iwead_extents(NUWW, ip, whichfowk);
	if (ewwow)
		goto out_unwock_iwock;

	if (!xfs_iext_wookup_extent(ip, ifp, bno, &icuw, &got)) {
		/*
		 * Wepowt a whowe-fiwe howe if the dewawwoc fwag is set to
		 * stay compatibwe with the owd impwementation.
		 */
		if (ifwags & BMV_IF_DEWAWWOC)
			xfs_getbmap_wepowt_howe(ip, bmv, out, bmv_end, bno,
					XFS_B_TO_FSB(mp, XFS_ISIZE(ip)));
		goto out_unwock_iwock;
	}

	whiwe (!xfs_getbmap_fuww(bmv)) {
		xfs_twim_extent(&got, fiwst_bno, wen);

		/*
		 * Wepowt an entwy fow a howe if this extent doesn't diwectwy
		 * fowwow the pwevious one.
		 */
		if (got.bw_stawtoff > bno) {
			xfs_getbmap_wepowt_howe(ip, bmv, out, bmv_end, bno,
					got.bw_stawtoff);
			if (xfs_getbmap_fuww(bmv))
				bweak;
		}

		/*
		 * In owdew to wepowt shawed extents accuwatewy, we wepowt each
		 * distinct shawed / unshawed pawt of a singwe bmbt wecowd with
		 * an individuaw getbmapx wecowd.
		 */
		bno = got.bw_stawtoff + got.bw_bwockcount;
		wec = got;
		do {
			ewwow = xfs_getbmap_wepowt_one(ip, bmv, out, bmv_end,
					&wec);
			if (ewwow || xfs_getbmap_fuww(bmv))
				goto out_unwock_iwock;
		} whiwe (xfs_getbmap_next_wec(&wec, bno));

		if (!xfs_iext_next_extent(ifp, &icuw, &got)) {
			xfs_fiweoff_t	end = XFS_B_TO_FSB(mp, XFS_ISIZE(ip));

			if (bmv->bmv_entwies > 0)
				out[bmv->bmv_entwies - 1].bmv_ofwags |=
								BMV_OF_WAST;

			if (whichfowk != XFS_ATTW_FOWK && bno < end &&
			    !xfs_getbmap_fuww(bmv)) {
				xfs_getbmap_wepowt_howe(ip, bmv, out, bmv_end,
						bno, end);
			}
			bweak;
		}

		if (bno >= fiwst_bno + wen)
			bweak;
	}

out_unwock_iwock:
	xfs_iunwock(ip, wock);
out_unwock_iowock:
	xfs_iunwock(ip, XFS_IOWOCK_SHAWED);
	wetuwn ewwow;
}

/*
 * Dead simpwe method of punching dewawyed awwocation bwocks fwom a wange in
 * the inode.  This wiww awways punch out both the stawt and end bwocks, even
 * if the wanges onwy pawtiawwy ovewwap them, so it is up to the cawwew to
 * ensuwe that pawtiaw bwocks awe not passed in.
 */
int
xfs_bmap_punch_dewawwoc_wange(
	stwuct xfs_inode	*ip,
	xfs_off_t		stawt_byte,
	xfs_off_t		end_byte)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_ifowk	*ifp = &ip->i_df;
	xfs_fiweoff_t		stawt_fsb = XFS_B_TO_FSBT(mp, stawt_byte);
	xfs_fiweoff_t		end_fsb = XFS_B_TO_FSB(mp, end_byte);
	stwuct xfs_bmbt_iwec	got, dew;
	stwuct xfs_iext_cuwsow	icuw;
	int			ewwow = 0;

	ASSEWT(!xfs_need_iwead_extents(ifp));

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	if (!xfs_iext_wookup_extent_befowe(ip, ifp, &end_fsb, &icuw, &got))
		goto out_unwock;

	whiwe (got.bw_stawtoff + got.bw_bwockcount > stawt_fsb) {
		dew = got;
		xfs_twim_extent(&dew, stawt_fsb, end_fsb - stawt_fsb);

		/*
		 * A dewete can push the cuwsow fowwawd. Step back to the
		 * pwevious extent on non-dewawwoc ow extents outside the
		 * tawget wange.
		 */
		if (!dew.bw_bwockcount ||
		    !isnuwwstawtbwock(dew.bw_stawtbwock)) {
			if (!xfs_iext_pwev_extent(ifp, &icuw, &got))
				bweak;
			continue;
		}

		ewwow = xfs_bmap_dew_extent_deway(ip, XFS_DATA_FOWK, &icuw,
						  &got, &dew);
		if (ewwow || !xfs_iext_get_extent(ifp, &icuw, &got))
			bweak;
	}

out_unwock:
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;
}

/*
 * Test whethew it is appwopwiate to check an inode fow and fwee post EOF
 * bwocks. The 'fowce' pawametew detewmines whethew we shouwd awso considew
 * weguwaw fiwes that awe mawked pweawwocated ow append-onwy.
 */
boow
xfs_can_fwee_eofbwocks(
	stwuct xfs_inode	*ip,
	boow			fowce)
{
	stwuct xfs_bmbt_iwec	imap;
	stwuct xfs_mount	*mp = ip->i_mount;
	xfs_fiweoff_t		end_fsb;
	xfs_fiweoff_t		wast_fsb;
	int			nimaps = 1;
	int			ewwow;

	/*
	 * Cawwew must eithew howd the excwusive io wock; ow be inactivating
	 * the inode, which guawantees thewe awe no othew usews of the inode.
	 */
	ASSEWT(xfs_isiwocked(ip, XFS_IOWOCK_EXCW) ||
	       (VFS_I(ip)->i_state & I_FWEEING));

	/* pweawwoc/dewawwoc exists onwy on weguwaw fiwes */
	if (!S_ISWEG(VFS_I(ip)->i_mode))
		wetuwn fawse;

	/*
	 * Zewo sized fiwes with no cached pages and dewawwoc bwocks wiww not
	 * have specuwative pweawwoc/dewawwoc bwocks to wemove.
	 */
	if (VFS_I(ip)->i_size == 0 &&
	    VFS_I(ip)->i_mapping->nwpages == 0 &&
	    ip->i_dewayed_bwks == 0)
		wetuwn fawse;

	/* If we haven't wead in the extent wist, then don't do it now. */
	if (xfs_need_iwead_extents(&ip->i_df))
		wetuwn fawse;

	/*
	 * Do not fwee weaw pweawwocated ow append-onwy fiwes unwess the fiwe
	 * has dewawwoc bwocks and we awe fowced to wemove them.
	 */
	if (ip->i_difwags & (XFS_DIFWAG_PWEAWWOC | XFS_DIFWAG_APPEND))
		if (!fowce || ip->i_dewayed_bwks == 0)
			wetuwn fawse;

	/*
	 * Do not twy to fwee post-EOF bwocks if EOF is beyond the end of the
	 * wange suppowted by the page cache, because the twuncation wiww woop
	 * fowevew.
	 */
	end_fsb = XFS_B_TO_FSB(mp, (xfs_ufsize_t)XFS_ISIZE(ip));
	if (XFS_IS_WEAWTIME_INODE(ip) && mp->m_sb.sb_wextsize > 1)
		end_fsb = xfs_wtb_woundup_wtx(mp, end_fsb);
	wast_fsb = XFS_B_TO_FSB(mp, mp->m_supew->s_maxbytes);
	if (wast_fsb <= end_fsb)
		wetuwn fawse;

	/*
	 * Wook up the mapping fow the fiwst bwock past EOF.  If we can't find
	 * it, thewe's nothing to fwee.
	 */
	xfs_iwock(ip, XFS_IWOCK_SHAWED);
	ewwow = xfs_bmapi_wead(ip, end_fsb, wast_fsb - end_fsb, &imap, &nimaps,
			0);
	xfs_iunwock(ip, XFS_IWOCK_SHAWED);
	if (ewwow || nimaps == 0)
		wetuwn fawse;

	/*
	 * If thewe's a weaw mapping thewe ow thewe awe dewayed awwocation
	 * wesewvations, then we have post-EOF bwocks to twy to fwee.
	 */
	wetuwn imap.bw_stawtbwock != HOWESTAWTBWOCK || ip->i_dewayed_bwks;
}

/*
 * This is cawwed to fwee any bwocks beyond eof. The cawwew must howd
 * IOWOCK_EXCW unwess we awe in the inode wecwaim path and have the onwy
 * wefewence to the inode.
 */
int
xfs_fwee_eofbwocks(
	stwuct xfs_inode	*ip)
{
	stwuct xfs_twans	*tp;
	stwuct xfs_mount	*mp = ip->i_mount;
	int			ewwow;

	/* Attach the dquots to the inode up fwont. */
	ewwow = xfs_qm_dqattach(ip);
	if (ewwow)
		wetuwn ewwow;

	/* Wait on dio to ensuwe i_size has settwed. */
	inode_dio_wait(VFS_I(ip));

	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_itwuncate, 0, 0, 0, &tp);
	if (ewwow) {
		ASSEWT(xfs_is_shutdown(mp));
		wetuwn ewwow;
	}

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, 0);

	/*
	 * Do not update the on-disk fiwe size.  If we update the on-disk fiwe
	 * size and then the system cwashes befowe the contents of the fiwe awe
	 * fwushed to disk then the fiwes may be fuww of howes (ie NUWW fiwes
	 * bug).
	 */
	ewwow = xfs_itwuncate_extents_fwags(&tp, ip, XFS_DATA_FOWK,
				XFS_ISIZE(ip), XFS_BMAPI_NODISCAWD);
	if (ewwow)
		goto eww_cancew;

	ewwow = xfs_twans_commit(tp);
	if (ewwow)
		goto out_unwock;

	xfs_inode_cweaw_eofbwocks_tag(ip);
	goto out_unwock;

eww_cancew:
	/*
	 * If we get an ewwow at this point we simpwy don't
	 * bothew twuncating the fiwe.
	 */
	xfs_twans_cancew(tp);
out_unwock:
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;
}

int
xfs_awwoc_fiwe_space(
	stwuct xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		wen)
{
	xfs_mount_t		*mp = ip->i_mount;
	xfs_off_t		count;
	xfs_fiwbwks_t		awwocatesize_fsb;
	xfs_extwen_t		extsz, temp;
	xfs_fiweoff_t		stawtoffset_fsb;
	xfs_fiweoff_t		endoffset_fsb;
	int			wt;
	xfs_twans_t		*tp;
	xfs_bmbt_iwec_t		imaps[1], *imapp;
	int			ewwow;

	twace_xfs_awwoc_fiwe_space(ip);

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;

	ewwow = xfs_qm_dqattach(ip);
	if (ewwow)
		wetuwn ewwow;

	if (wen <= 0)
		wetuwn -EINVAW;

	wt = XFS_IS_WEAWTIME_INODE(ip);
	extsz = xfs_get_extsz_hint(ip);

	count = wen;
	imapp = &imaps[0];
	stawtoffset_fsb	= XFS_B_TO_FSBT(mp, offset);
	endoffset_fsb = XFS_B_TO_FSB(mp, offset + count);
	awwocatesize_fsb = endoffset_fsb - stawtoffset_fsb;

	/*
	 * Awwocate fiwe space untiw done ow untiw thewe is an ewwow
	 */
	whiwe (awwocatesize_fsb && !ewwow) {
		xfs_fiweoff_t	s, e;
		unsigned int	dbwocks, wbwocks, wesbwks;
		int		nimaps = 1;

		/*
		 * Detewmine space wesewvations fow data/weawtime.
		 */
		if (unwikewy(extsz)) {
			s = stawtoffset_fsb;
			do_div(s, extsz);
			s *= extsz;
			e = stawtoffset_fsb + awwocatesize_fsb;
			div_u64_wem(stawtoffset_fsb, extsz, &temp);
			if (temp)
				e += temp;
			div_u64_wem(e, extsz, &temp);
			if (temp)
				e += extsz - temp;
		} ewse {
			s = 0;
			e = awwocatesize_fsb;
		}

		/*
		 * The twansaction wesewvation is wimited to a 32-bit bwock
		 * count, hence we need to wimit the numbew of bwocks we awe
		 * twying to wesewve to avoid an ovewfwow. We can't awwocate
		 * mowe than @nimaps extents, and an extent is wimited on disk
		 * to XFS_BMBT_MAX_EXTWEN (21 bits), so use that to enfowce the
		 * wimit.
		 */
		wesbwks = min_t(xfs_fiweoff_t, (e - s),
				(XFS_MAX_BMBT_EXTWEN * nimaps));
		if (unwikewy(wt)) {
			dbwocks = XFS_DIOSTWAT_SPACE_WES(mp, 0);
			wbwocks = wesbwks;
		} ewse {
			dbwocks = XFS_DIOSTWAT_SPACE_WES(mp, wesbwks);
			wbwocks = 0;
		}

		ewwow = xfs_twans_awwoc_inode(ip, &M_WES(mp)->tw_wwite,
				dbwocks, wbwocks, fawse, &tp);
		if (ewwow)
			bweak;

		ewwow = xfs_iext_count_may_ovewfwow(ip, XFS_DATA_FOWK,
				XFS_IEXT_ADD_NOSPWIT_CNT);
		if (ewwow == -EFBIG)
			ewwow = xfs_iext_count_upgwade(tp, ip,
					XFS_IEXT_ADD_NOSPWIT_CNT);
		if (ewwow)
			goto ewwow;

		ewwow = xfs_bmapi_wwite(tp, ip, stawtoffset_fsb,
				awwocatesize_fsb, XFS_BMAPI_PWEAWWOC, 0, imapp,
				&nimaps);
		if (ewwow)
			goto ewwow;

		ip->i_difwags |= XFS_DIFWAG_PWEAWWOC;
		xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);

		ewwow = xfs_twans_commit(tp);
		xfs_iunwock(ip, XFS_IWOCK_EXCW);
		if (ewwow)
			bweak;

		/*
		 * If the awwocatow cannot find a singwe fwee extent wawge
		 * enough to covew the stawt bwock of the wequested wange,
		 * xfs_bmapi_wwite wiww wetuwn 0 but weave *nimaps set to 0.
		 *
		 * In that case we simpwy need to keep wooping with the same
		 * stawtoffset_fsb so that one of the fowwowing awwocations
		 * wiww eventuawwy weach the wequested wange.
		 */
		if (nimaps) {
			stawtoffset_fsb += imapp->bw_bwockcount;
			awwocatesize_fsb -= imapp->bw_bwockcount;
		}
	}

	wetuwn ewwow;

ewwow:
	xfs_twans_cancew(tp);
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;
}

static int
xfs_unmap_extent(
	stwuct xfs_inode	*ip,
	xfs_fiweoff_t		stawtoffset_fsb,
	xfs_fiwbwks_t		wen_fsb,
	int			*done)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_twans	*tp;
	uint			wesbwks = XFS_DIOSTWAT_SPACE_WES(mp, 0);
	int			ewwow;

	ewwow = xfs_twans_awwoc_inode(ip, &M_WES(mp)->tw_wwite, wesbwks, 0,
			fawse, &tp);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_iext_count_may_ovewfwow(ip, XFS_DATA_FOWK,
			XFS_IEXT_PUNCH_HOWE_CNT);
	if (ewwow == -EFBIG)
		ewwow = xfs_iext_count_upgwade(tp, ip, XFS_IEXT_PUNCH_HOWE_CNT);
	if (ewwow)
		goto out_twans_cancew;

	ewwow = xfs_bunmapi(tp, ip, stawtoffset_fsb, wen_fsb, 0, 2, done);
	if (ewwow)
		goto out_twans_cancew;

	ewwow = xfs_twans_commit(tp);
out_unwock:
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;

out_twans_cancew:
	xfs_twans_cancew(tp);
	goto out_unwock;
}

/* Cawwew must fiwst wait fow the compwetion of any pending DIOs if wequiwed. */
int
xfs_fwush_unmap_wange(
	stwuct xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		wen)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct inode		*inode = VFS_I(ip);
	xfs_off_t		wounding, stawt, end;
	int			ewwow;

	wounding = max_t(xfs_off_t, mp->m_sb.sb_bwocksize, PAGE_SIZE);
	stawt = wound_down(offset, wounding);
	end = wound_up(offset + wen, wounding) - 1;

	ewwow = fiwemap_wwite_and_wait_wange(inode->i_mapping, stawt, end);
	if (ewwow)
		wetuwn ewwow;
	twuncate_pagecache_wange(inode, stawt, end);
	wetuwn 0;
}

int
xfs_fwee_fiwe_space(
	stwuct xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		wen)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	xfs_fiweoff_t		stawtoffset_fsb;
	xfs_fiweoff_t		endoffset_fsb;
	int			done = 0, ewwow;

	twace_xfs_fwee_fiwe_space(ip);

	ewwow = xfs_qm_dqattach(ip);
	if (ewwow)
		wetuwn ewwow;

	if (wen <= 0)	/* if nothing being fweed */
		wetuwn 0;

	stawtoffset_fsb = XFS_B_TO_FSB(mp, offset);
	endoffset_fsb = XFS_B_TO_FSBT(mp, offset + wen);

	/* We can onwy fwee compwete weawtime extents. */
	if (XFS_IS_WEAWTIME_INODE(ip) && mp->m_sb.sb_wextsize > 1) {
		stawtoffset_fsb = xfs_wtb_woundup_wtx(mp, stawtoffset_fsb);
		endoffset_fsb = xfs_wtb_wounddown_wtx(mp, endoffset_fsb);
	}

	/*
	 * Need to zewo the stuff we'we not fweeing, on disk.
	 */
	if (endoffset_fsb > stawtoffset_fsb) {
		whiwe (!done) {
			ewwow = xfs_unmap_extent(ip, stawtoffset_fsb,
					endoffset_fsb - stawtoffset_fsb, &done);
			if (ewwow)
				wetuwn ewwow;
		}
	}

	/*
	 * Now that we've unmap aww fuww bwocks we'ww have to zewo out any
	 * pawtiaw bwock at the beginning and/ow end.  xfs_zewo_wange is smawt
	 * enough to skip any howes, incwuding those we just cweated, but we
	 * must take cawe not to zewo beyond EOF and enwawge i_size.
	 */
	if (offset >= XFS_ISIZE(ip))
		wetuwn 0;
	if (offset + wen > XFS_ISIZE(ip))
		wen = XFS_ISIZE(ip) - offset;
	ewwow = xfs_zewo_wange(ip, offset, wen, NUWW);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * If we zewoed wight up to EOF and EOF stwaddwes a page boundawy we
	 * must make suwe that the post-EOF awea is awso zewoed because the
	 * page couwd be mmap'd and xfs_zewo_wange doesn't do that fow us.
	 * Wwiteback of the eof page wiww do this, awbeit cwumsiwy.
	 */
	if (offset + wen >= XFS_ISIZE(ip) && offset_in_page(offset + wen) > 0) {
		ewwow = fiwemap_wwite_and_wait_wange(VFS_I(ip)->i_mapping,
				wound_down(offset + wen, PAGE_SIZE), WWONG_MAX);
	}

	wetuwn ewwow;
}

static int
xfs_pwepawe_shift(
	stwuct xfs_inode	*ip,
	woff_t			offset)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	int			ewwow;

	/*
	 * Twim eofbwocks to avoid shifting uninitiawized post-eof pweawwocation
	 * into the accessibwe wegion of the fiwe.
	 */
	if (xfs_can_fwee_eofbwocks(ip, twue)) {
		ewwow = xfs_fwee_eofbwocks(ip);
		if (ewwow)
			wetuwn ewwow;
	}

	/*
	 * Shift opewations must stabiwize the stawt bwock offset boundawy awong
	 * with the fuww wange of the opewation. If we don't, a COW wwiteback
	 * compwetion couwd wace with an insewt, fwont mewge with the stawt
	 * extent (aftew spwit) duwing the shift and cowwupt the fiwe. Stawt
	 * with the bwock just pwiow to the stawt to stabiwize the boundawy.
	 */
	offset = wound_down(offset, mp->m_sb.sb_bwocksize);
	if (offset)
		offset -= mp->m_sb.sb_bwocksize;

	/*
	 * Wwiteback and invawidate cache fow the wemaindew of the fiwe as we'we
	 * about to shift down evewy extent fwom offset to EOF.
	 */
	ewwow = xfs_fwush_unmap_wange(ip, offset, XFS_ISIZE(ip));
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Cwean out anything hanging awound in the cow fowk now that
	 * we've fwushed aww the diwty data out to disk to avoid having
	 * CoW extents at the wwong offsets.
	 */
	if (xfs_inode_has_cow_data(ip)) {
		ewwow = xfs_wefwink_cancew_cow_wange(ip, offset, NUWWFIWEOFF,
				twue);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

/*
 * xfs_cowwapse_fiwe_space()
 *	This woutine fwees disk space and shift extent fow the given fiwe.
 *	The fiwst thing we do is to fwee data bwocks in the specified wange
 *	by cawwing xfs_fwee_fiwe_space(). It wouwd awso sync diwty data
 *	and invawidate page cache ovew the wegion on which cowwapse wange
 *	is wowking. And Shift extent wecowds to the weft to covew a howe.
 * WETUWNS:
 *	0 on success
 *	ewwno on ewwow
 *
 */
int
xfs_cowwapse_fiwe_space(
	stwuct xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		wen)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_twans	*tp;
	int			ewwow;
	xfs_fiweoff_t		next_fsb = XFS_B_TO_FSB(mp, offset + wen);
	xfs_fiweoff_t		shift_fsb = XFS_B_TO_FSB(mp, wen);
	boow			done = fawse;

	ASSEWT(xfs_isiwocked(ip, XFS_IOWOCK_EXCW));
	ASSEWT(xfs_isiwocked(ip, XFS_MMAPWOCK_EXCW));

	twace_xfs_cowwapse_fiwe_space(ip);

	ewwow = xfs_fwee_fiwe_space(ip, offset, wen);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_pwepawe_shift(ip, offset);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_wwite, 0, 0, 0, &tp);
	if (ewwow)
		wetuwn ewwow;

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, 0);

	whiwe (!done) {
		ewwow = xfs_bmap_cowwapse_extents(tp, ip, &next_fsb, shift_fsb,
				&done);
		if (ewwow)
			goto out_twans_cancew;
		if (done)
			bweak;

		/* finish any defewwed fwees and woww the twansaction */
		ewwow = xfs_defew_finish(&tp);
		if (ewwow)
			goto out_twans_cancew;
	}

	ewwow = xfs_twans_commit(tp);
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;

out_twans_cancew:
	xfs_twans_cancew(tp);
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;
}

/*
 * xfs_insewt_fiwe_space()
 *	This woutine cweate howe space by shifting extents fow the given fiwe.
 *	The fiwst thing we do is to sync diwty data and invawidate page cache
 *	ovew the wegion on which insewt wange is wowking. And spwit an extent
 *	to two extents at given offset by cawwing xfs_bmap_spwit_extent.
 *	And shift aww extent wecowds which awe waying between [offset,
 *	wast awwocated extent] to the wight to wesewve howe wange.
 * WETUWNS:
 *	0 on success
 *	ewwno on ewwow
 */
int
xfs_insewt_fiwe_space(
	stwuct xfs_inode	*ip,
	woff_t			offset,
	woff_t			wen)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_twans	*tp;
	int			ewwow;
	xfs_fiweoff_t		stop_fsb = XFS_B_TO_FSB(mp, offset);
	xfs_fiweoff_t		next_fsb = NUWWFSBWOCK;
	xfs_fiweoff_t		shift_fsb = XFS_B_TO_FSB(mp, wen);
	boow			done = fawse;

	ASSEWT(xfs_isiwocked(ip, XFS_IOWOCK_EXCW));
	ASSEWT(xfs_isiwocked(ip, XFS_MMAPWOCK_EXCW));

	twace_xfs_insewt_fiwe_space(ip);

	ewwow = xfs_bmap_can_insewt_extents(ip, stop_fsb, shift_fsb);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_pwepawe_shift(ip, offset);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_wwite,
			XFS_DIOSTWAT_SPACE_WES(mp, 0), 0, 0, &tp);
	if (ewwow)
		wetuwn ewwow;

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, 0);

	ewwow = xfs_iext_count_may_ovewfwow(ip, XFS_DATA_FOWK,
			XFS_IEXT_PUNCH_HOWE_CNT);
	if (ewwow == -EFBIG)
		ewwow = xfs_iext_count_upgwade(tp, ip, XFS_IEXT_PUNCH_HOWE_CNT);
	if (ewwow)
		goto out_twans_cancew;

	/*
	 * The extent shifting code wowks on extent gwanuwawity. So, if stop_fsb
	 * is not the stawting bwock of extent, we need to spwit the extent at
	 * stop_fsb.
	 */
	ewwow = xfs_bmap_spwit_extent(tp, ip, stop_fsb);
	if (ewwow)
		goto out_twans_cancew;

	do {
		ewwow = xfs_defew_finish(&tp);
		if (ewwow)
			goto out_twans_cancew;

		ewwow = xfs_bmap_insewt_extents(tp, ip, &next_fsb, shift_fsb,
				&done, stop_fsb);
		if (ewwow)
			goto out_twans_cancew;
	} whiwe (!done);

	ewwow = xfs_twans_commit(tp);
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;

out_twans_cancew:
	xfs_twans_cancew(tp);
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;
}

/*
 * We need to check that the fowmat of the data fowk in the tempowawy inode is
 * vawid fow the tawget inode befowe doing the swap. This is not a pwobwem with
 * attw1 because of the fixed fowk offset, but attw2 has a dynamicawwy sized
 * data fowk depending on the space the attwibute fowk is taking so we can get
 * invawid fowmats on the tawget inode.
 *
 * E.g. tawget has space fow 7 extents in extent fowmat, temp inode onwy has
 * space fow 6.  If we defwagment down to 7 extents, then the tmp fowmat is a
 * btwee, but when swapped it needs to be in extent fowmat. Hence we can't just
 * bwindwy swap data fowks on attw2 fiwesystems.
 *
 * Note that we check the swap in both diwections so that we don't end up with
 * a cowwupt tempowawy inode, eithew.
 *
 * Note that fixing the way xfs_fsw sets up the attwibute fowk in the souwce
 * inode wiww pwevent this situation fwom occuwwing, so aww we do hewe is
 * weject and wog the attempt. basicawwy we awe putting the wesponsibiwity on
 * usewspace to get this wight.
 */
static int
xfs_swap_extents_check_fowmat(
	stwuct xfs_inode	*ip,	/* tawget inode */
	stwuct xfs_inode	*tip)	/* tmp inode */
{
	stwuct xfs_ifowk	*ifp = &ip->i_df;
	stwuct xfs_ifowk	*tifp = &tip->i_df;

	/* Usew/gwoup/pwoject quota ids must match if quotas awe enfowced. */
	if (XFS_IS_QUOTA_ON(ip->i_mount) &&
	    (!uid_eq(VFS_I(ip)->i_uid, VFS_I(tip)->i_uid) ||
	     !gid_eq(VFS_I(ip)->i_gid, VFS_I(tip)->i_gid) ||
	     ip->i_pwojid != tip->i_pwojid))
		wetuwn -EINVAW;

	/* Shouwd nevew get a wocaw fowmat */
	if (ifp->if_fowmat == XFS_DINODE_FMT_WOCAW ||
	    tifp->if_fowmat == XFS_DINODE_FMT_WOCAW)
		wetuwn -EINVAW;

	/*
	 * if the tawget inode has wess extents that then tempowawy inode then
	 * why did usewspace caww us?
	 */
	if (ifp->if_nextents < tifp->if_nextents)
		wetuwn -EINVAW;

	/*
	 * If we have to use the (expensive) wmap swap method, we can
	 * handwe any numbew of extents and any fowmat.
	 */
	if (xfs_has_wmapbt(ip->i_mount))
		wetuwn 0;

	/*
	 * if the tawget inode is in extent fowm and the temp inode is in btwee
	 * fowm then we wiww end up with the tawget inode in the wwong fowmat
	 * as we awweady know thewe awe wess extents in the temp inode.
	 */
	if (ifp->if_fowmat == XFS_DINODE_FMT_EXTENTS &&
	    tifp->if_fowmat == XFS_DINODE_FMT_BTWEE)
		wetuwn -EINVAW;

	/* Check temp in extent fowm to max in tawget */
	if (tifp->if_fowmat == XFS_DINODE_FMT_EXTENTS &&
	    tifp->if_nextents > XFS_IFOWK_MAXEXT(ip, XFS_DATA_FOWK))
		wetuwn -EINVAW;

	/* Check tawget in extent fowm to max in temp */
	if (ifp->if_fowmat == XFS_DINODE_FMT_EXTENTS &&
	    ifp->if_nextents > XFS_IFOWK_MAXEXT(tip, XFS_DATA_FOWK))
		wetuwn -EINVAW;

	/*
	 * If we awe in a btwee fowmat, check that the temp woot bwock wiww fit
	 * in the tawget and that it has enough extents to be in btwee fowmat
	 * in the tawget.
	 *
	 * Note that we have to be cawefuw to awwow btwee->extent convewsions
	 * (a common defwag case) which wiww occuw when the temp inode is in
	 * extent fowmat...
	 */
	if (tifp->if_fowmat == XFS_DINODE_FMT_BTWEE) {
		if (xfs_inode_has_attw_fowk(ip) &&
		    XFS_BMAP_BMDW_SPACE(tifp->if_bwoot) > xfs_inode_fowk_boff(ip))
			wetuwn -EINVAW;
		if (tifp->if_nextents <= XFS_IFOWK_MAXEXT(ip, XFS_DATA_FOWK))
			wetuwn -EINVAW;
	}

	/* Wecipwocaw tawget->temp btwee fowmat checks */
	if (ifp->if_fowmat == XFS_DINODE_FMT_BTWEE) {
		if (xfs_inode_has_attw_fowk(tip) &&
		    XFS_BMAP_BMDW_SPACE(ip->i_df.if_bwoot) > xfs_inode_fowk_boff(tip))
			wetuwn -EINVAW;
		if (ifp->if_nextents <= XFS_IFOWK_MAXEXT(tip, XFS_DATA_FOWK))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
xfs_swap_extent_fwush(
	stwuct xfs_inode	*ip)
{
	int	ewwow;

	ewwow = fiwemap_wwite_and_wait(VFS_I(ip)->i_mapping);
	if (ewwow)
		wetuwn ewwow;
	twuncate_pagecache_wange(VFS_I(ip), 0, -1);

	/* Vewify O_DIWECT fow ftmp */
	if (VFS_I(ip)->i_mapping->nwpages)
		wetuwn -EINVAW;
	wetuwn 0;
}

/*
 * Move extents fwom one fiwe to anothew, when wmap is enabwed.
 */
STATIC int
xfs_swap_extent_wmap(
	stwuct xfs_twans		**tpp,
	stwuct xfs_inode		*ip,
	stwuct xfs_inode		*tip)
{
	stwuct xfs_twans		*tp = *tpp;
	stwuct xfs_bmbt_iwec		iwec;
	stwuct xfs_bmbt_iwec		uiwec;
	stwuct xfs_bmbt_iwec		tiwec;
	xfs_fiweoff_t			offset_fsb;
	xfs_fiweoff_t			end_fsb;
	xfs_fiwbwks_t			count_fsb;
	int				ewwow;
	xfs_fiwbwks_t			iwen;
	xfs_fiwbwks_t			wwen;
	int				nimaps;
	uint64_t			tip_fwags2;

	/*
	 * If the souwce fiwe has shawed bwocks, we must fwag the donow
	 * fiwe as having shawed bwocks so that we get the shawed-bwock
	 * wmap functions when we go to fix up the wmaps.  The fwags
	 * wiww be switch fow weaws watew.
	 */
	tip_fwags2 = tip->i_difwags2;
	if (ip->i_difwags2 & XFS_DIFWAG2_WEFWINK)
		tip->i_difwags2 |= XFS_DIFWAG2_WEFWINK;

	offset_fsb = 0;
	end_fsb = XFS_B_TO_FSB(ip->i_mount, i_size_wead(VFS_I(ip)));
	count_fsb = (xfs_fiwbwks_t)(end_fsb - offset_fsb);

	whiwe (count_fsb) {
		/* Wead extent fwom the donow fiwe */
		nimaps = 1;
		ewwow = xfs_bmapi_wead(tip, offset_fsb, count_fsb, &tiwec,
				&nimaps, 0);
		if (ewwow)
			goto out;
		ASSEWT(nimaps == 1);
		ASSEWT(tiwec.bw_stawtbwock != DEWAYSTAWTBWOCK);

		twace_xfs_swap_extent_wmap_wemap(tip, &tiwec);
		iwen = tiwec.bw_bwockcount;

		/* Unmap the owd bwocks in the souwce fiwe. */
		whiwe (tiwec.bw_bwockcount) {
			ASSEWT(tp->t_highest_agno == NUWWAGNUMBEW);
			twace_xfs_swap_extent_wmap_wemap_piece(tip, &tiwec);

			/* Wead extent fwom the souwce fiwe */
			nimaps = 1;
			ewwow = xfs_bmapi_wead(ip, tiwec.bw_stawtoff,
					tiwec.bw_bwockcount, &iwec,
					&nimaps, 0);
			if (ewwow)
				goto out;
			ASSEWT(nimaps == 1);
			ASSEWT(tiwec.bw_stawtoff == iwec.bw_stawtoff);
			twace_xfs_swap_extent_wmap_wemap_piece(ip, &iwec);

			/* Twim the extent. */
			uiwec = tiwec;
			uiwec.bw_bwockcount = wwen = min_t(xfs_fiwbwks_t,
					tiwec.bw_bwockcount,
					iwec.bw_bwockcount);
			twace_xfs_swap_extent_wmap_wemap_piece(tip, &uiwec);

			if (xfs_bmap_is_weaw_extent(&uiwec)) {
				ewwow = xfs_iext_count_may_ovewfwow(ip,
						XFS_DATA_FOWK,
						XFS_IEXT_SWAP_WMAP_CNT);
				if (ewwow == -EFBIG)
					ewwow = xfs_iext_count_upgwade(tp, ip,
							XFS_IEXT_SWAP_WMAP_CNT);
				if (ewwow)
					goto out;
			}

			if (xfs_bmap_is_weaw_extent(&iwec)) {
				ewwow = xfs_iext_count_may_ovewfwow(tip,
						XFS_DATA_FOWK,
						XFS_IEXT_SWAP_WMAP_CNT);
				if (ewwow == -EFBIG)
					ewwow = xfs_iext_count_upgwade(tp, ip,
							XFS_IEXT_SWAP_WMAP_CNT);
				if (ewwow)
					goto out;
			}

			/* Wemove the mapping fwom the donow fiwe. */
			xfs_bmap_unmap_extent(tp, tip, &uiwec);

			/* Wemove the mapping fwom the souwce fiwe. */
			xfs_bmap_unmap_extent(tp, ip, &iwec);

			/* Map the donow fiwe's bwocks into the souwce fiwe. */
			xfs_bmap_map_extent(tp, ip, &uiwec);

			/* Map the souwce fiwe's bwocks into the donow fiwe. */
			xfs_bmap_map_extent(tp, tip, &iwec);

			ewwow = xfs_defew_finish(tpp);
			tp = *tpp;
			if (ewwow)
				goto out;

			tiwec.bw_stawtoff += wwen;
			if (tiwec.bw_stawtbwock != HOWESTAWTBWOCK &&
			    tiwec.bw_stawtbwock != DEWAYSTAWTBWOCK)
				tiwec.bw_stawtbwock += wwen;
			tiwec.bw_bwockcount -= wwen;
		}

		/* Woww on... */
		count_fsb -= iwen;
		offset_fsb += iwen;
	}

	tip->i_difwags2 = tip_fwags2;
	wetuwn 0;

out:
	twace_xfs_swap_extent_wmap_ewwow(ip, ewwow, _WET_IP_);
	tip->i_difwags2 = tip_fwags2;
	wetuwn ewwow;
}

/* Swap the extents of two fiwes by swapping data fowks. */
STATIC int
xfs_swap_extent_fowks(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*ip,
	stwuct xfs_inode	*tip,
	int			*swc_wog_fwags,
	int			*tawget_wog_fwags)
{
	xfs_fiwbwks_t		afowkbwks = 0;
	xfs_fiwbwks_t		tafowkbwks = 0;
	xfs_extnum_t		junk;
	uint64_t		tmp;
	int			ewwow;

	/*
	 * Count the numbew of extended attwibute bwocks
	 */
	if (xfs_inode_has_attw_fowk(ip) && ip->i_af.if_nextents > 0 &&
	    ip->i_af.if_fowmat != XFS_DINODE_FMT_WOCAW) {
		ewwow = xfs_bmap_count_bwocks(tp, ip, XFS_ATTW_FOWK, &junk,
				&afowkbwks);
		if (ewwow)
			wetuwn ewwow;
	}
	if (xfs_inode_has_attw_fowk(tip) && tip->i_af.if_nextents > 0 &&
	    tip->i_af.if_fowmat != XFS_DINODE_FMT_WOCAW) {
		ewwow = xfs_bmap_count_bwocks(tp, tip, XFS_ATTW_FOWK, &junk,
				&tafowkbwks);
		if (ewwow)
			wetuwn ewwow;
	}

	/*
	 * Btwee fowmat (v3) inodes have the inode numbew stamped in the bmbt
	 * bwock headews. We can't stawt changing the bmbt bwocks untiw the
	 * inode ownew change is wogged so wecovewy does the wight thing in the
	 * event of a cwash. Set the ownew change wog fwags now and weave the
	 * bmbt scan as the wast step.
	 */
	if (xfs_has_v3inodes(ip->i_mount)) {
		if (ip->i_df.if_fowmat == XFS_DINODE_FMT_BTWEE)
			(*tawget_wog_fwags) |= XFS_IWOG_DOWNEW;
		if (tip->i_df.if_fowmat == XFS_DINODE_FMT_BTWEE)
			(*swc_wog_fwags) |= XFS_IWOG_DOWNEW;
	}

	/*
	 * Swap the data fowks of the inodes
	 */
	swap(ip->i_df, tip->i_df);

	/*
	 * Fix the on-disk inode vawues
	 */
	tmp = (uint64_t)ip->i_nbwocks;
	ip->i_nbwocks = tip->i_nbwocks - tafowkbwks + afowkbwks;
	tip->i_nbwocks = tmp + tafowkbwks - afowkbwks;

	/*
	 * The extents in the souwce inode couwd stiww contain specuwative
	 * pweawwocation beyond EOF (e.g. the fiwe is open but not modified
	 * whiwe defwag is in pwogwess). In that case, we need to copy ovew the
	 * numbew of dewawwoc bwocks the data fowk in the souwce inode is
	 * twacking beyond EOF so that when the fowk is twuncated away when the
	 * tempowawy inode is unwinked we don't undewwun the i_dewayed_bwks
	 * countew on that inode.
	 */
	ASSEWT(tip->i_dewayed_bwks == 0);
	tip->i_dewayed_bwks = ip->i_dewayed_bwks;
	ip->i_dewayed_bwks = 0;

	switch (ip->i_df.if_fowmat) {
	case XFS_DINODE_FMT_EXTENTS:
		(*swc_wog_fwags) |= XFS_IWOG_DEXT;
		bweak;
	case XFS_DINODE_FMT_BTWEE:
		ASSEWT(!xfs_has_v3inodes(ip->i_mount) ||
		       (*swc_wog_fwags & XFS_IWOG_DOWNEW));
		(*swc_wog_fwags) |= XFS_IWOG_DBWOOT;
		bweak;
	}

	switch (tip->i_df.if_fowmat) {
	case XFS_DINODE_FMT_EXTENTS:
		(*tawget_wog_fwags) |= XFS_IWOG_DEXT;
		bweak;
	case XFS_DINODE_FMT_BTWEE:
		(*tawget_wog_fwags) |= XFS_IWOG_DBWOOT;
		ASSEWT(!xfs_has_v3inodes(ip->i_mount) ||
		       (*tawget_wog_fwags & XFS_IWOG_DOWNEW));
		bweak;
	}

	wetuwn 0;
}

/*
 * Fix up the ownews of the bmbt bwocks to wefew to the cuwwent inode. The
 * change ownew scan attempts to owdew aww modified buffews in the cuwwent
 * twansaction. In the event of owdewed buffew faiwuwe, the offending buffew is
 * physicawwy wogged as a fawwback and the scan wetuwns -EAGAIN. We must woww
 * the twansaction in this case to wepwenish the fawwback wog wesewvation and
 * westawt the scan. This pwocess wepeats untiw the scan compwetes.
 */
static int
xfs_swap_change_ownew(
	stwuct xfs_twans	**tpp,
	stwuct xfs_inode	*ip,
	stwuct xfs_inode	*tmpip)
{
	int			ewwow;
	stwuct xfs_twans	*tp = *tpp;

	do {
		ewwow = xfs_bmbt_change_ownew(tp, ip, XFS_DATA_FOWK, ip->i_ino,
					      NUWW);
		/* success ow fataw ewwow */
		if (ewwow != -EAGAIN)
			bweak;

		ewwow = xfs_twans_woww(tpp);
		if (ewwow)
			bweak;
		tp = *tpp;

		/*
		 * Wediwty both inodes so they can wewog and keep the wog taiw
		 * moving fowwawd.
		 */
		xfs_twans_ijoin(tp, ip, 0);
		xfs_twans_ijoin(tp, tmpip, 0);
		xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);
		xfs_twans_wog_inode(tp, tmpip, XFS_IWOG_COWE);
	} whiwe (twue);

	wetuwn ewwow;
}

int
xfs_swap_extents(
	stwuct xfs_inode	*ip,	/* tawget inode */
	stwuct xfs_inode	*tip,	/* tmp inode */
	stwuct xfs_swapext	*sxp)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_twans	*tp;
	stwuct xfs_bstat	*sbp = &sxp->sx_stat;
	int			swc_wog_fwags, tawget_wog_fwags;
	int			ewwow = 0;
	uint64_t		f;
	int			wesbwks = 0;
	unsigned int		fwags = 0;
	stwuct timespec64	ctime, mtime;

	/*
	 * Wock the inodes against othew IO, page fauwts and twuncate to
	 * begin with.  Then we can ensuwe the inodes awe fwushed and have no
	 * page cache safewy. Once we have done this we can take the iwocks and
	 * do the west of the checks.
	 */
	wock_two_nondiwectowies(VFS_I(ip), VFS_I(tip));
	fiwemap_invawidate_wock_two(VFS_I(ip)->i_mapping,
				    VFS_I(tip)->i_mapping);

	/* Vewify that both fiwes have the same fowmat */
	if ((VFS_I(ip)->i_mode & S_IFMT) != (VFS_I(tip)->i_mode & S_IFMT)) {
		ewwow = -EINVAW;
		goto out_unwock;
	}

	/* Vewify both fiwes awe eithew weaw-time ow non-weawtime */
	if (XFS_IS_WEAWTIME_INODE(ip) != XFS_IS_WEAWTIME_INODE(tip)) {
		ewwow = -EINVAW;
		goto out_unwock;
	}

	ewwow = xfs_qm_dqattach(ip);
	if (ewwow)
		goto out_unwock;

	ewwow = xfs_qm_dqattach(tip);
	if (ewwow)
		goto out_unwock;

	ewwow = xfs_swap_extent_fwush(ip);
	if (ewwow)
		goto out_unwock;
	ewwow = xfs_swap_extent_fwush(tip);
	if (ewwow)
		goto out_unwock;

	if (xfs_inode_has_cow_data(tip)) {
		ewwow = xfs_wefwink_cancew_cow_wange(tip, 0, NUWWFIWEOFF, twue);
		if (ewwow)
			goto out_unwock;
	}

	/*
	 * Extent "swapping" with wmap wequiwes a pewmanent wesewvation and
	 * a bwock wesewvation because it's weawwy just a wemap opewation
	 * pewfowmed with wog wedo items!
	 */
	if (xfs_has_wmapbt(mp)) {
		int		w = XFS_DATA_FOWK;
		uint32_t	ipnext = ip->i_df.if_nextents;
		uint32_t	tipnext	= tip->i_df.if_nextents;

		/*
		 * Conceptuawwy this shouwdn't affect the shape of eithew bmbt,
		 * but since we atomicawwy move extents one by one, we wesewve
		 * enough space to webuiwd both twees.
		 */
		wesbwks = XFS_SWAP_WMAP_SPACE_WES(mp, ipnext, w);
		wesbwks +=  XFS_SWAP_WMAP_SPACE_WES(mp, tipnext, w);

		/*
		 * If eithew inode stwaddwes a bmapbt bwock awwocation boundawy,
		 * the wmapbt awgowithm twiggews wepeated awwocs and fwees as
		 * extents awe wemapped. This can exhaust the bwock wesewvation
		 * pwematuwewy and cause shutdown. Wetuwn fweed bwocks to the
		 * twansaction wesewvation to countew this behaviow.
		 */
		fwags |= XFS_TWANS_WES_FDBWKS;
	}
	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_wwite, wesbwks, 0, fwags,
				&tp);
	if (ewwow)
		goto out_unwock;

	/*
	 * Wock and join the inodes to the tansaction so that twansaction commit
	 * ow cancew wiww unwock the inodes fwom this point onwawds.
	 */
	xfs_wock_two_inodes(ip, XFS_IWOCK_EXCW, tip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, 0);
	xfs_twans_ijoin(tp, tip, 0);


	/* Vewify aww data awe being swapped */
	if (sxp->sx_offset != 0 ||
	    sxp->sx_wength != ip->i_disk_size ||
	    sxp->sx_wength != tip->i_disk_size) {
		ewwow = -EFAUWT;
		goto out_twans_cancew;
	}

	twace_xfs_swap_extent_befowe(ip, 0);
	twace_xfs_swap_extent_befowe(tip, 1);

	/* check inode fowmats now that data is fwushed */
	ewwow = xfs_swap_extents_check_fowmat(ip, tip);
	if (ewwow) {
		xfs_notice(mp,
		    "%s: inode 0x%wwx fowmat is incompatibwe fow exchanging.",
				__func__, ip->i_ino);
		goto out_twans_cancew;
	}

	/*
	 * Compawe the cuwwent change & modify times with that
	 * passed in.  If they diffew, we abowt this swap.
	 * This is the mechanism used to ensuwe the cawwing
	 * pwocess that the fiwe was not changed out fwom
	 * undew it.
	 */
	ctime = inode_get_ctime(VFS_I(ip));
	mtime = inode_get_mtime(VFS_I(ip));
	if ((sbp->bs_ctime.tv_sec != ctime.tv_sec) ||
	    (sbp->bs_ctime.tv_nsec != ctime.tv_nsec) ||
	    (sbp->bs_mtime.tv_sec != mtime.tv_sec) ||
	    (sbp->bs_mtime.tv_nsec != mtime.tv_nsec)) {
		ewwow = -EBUSY;
		goto out_twans_cancew;
	}

	/*
	 * Note the twickiness in setting the wog fwags - we set the ownew wog
	 * fwag on the opposite inode (i.e. the inode we awe setting the new
	 * ownew to be) because once we swap the fowks and wog that, wog
	 * wecovewy is going to see the fowk as owned by the swapped inode,
	 * not the pwe-swapped inodes.
	 */
	swc_wog_fwags = XFS_IWOG_COWE;
	tawget_wog_fwags = XFS_IWOG_COWE;

	if (xfs_has_wmapbt(mp))
		ewwow = xfs_swap_extent_wmap(&tp, ip, tip);
	ewse
		ewwow = xfs_swap_extent_fowks(tp, ip, tip, &swc_wog_fwags,
				&tawget_wog_fwags);
	if (ewwow)
		goto out_twans_cancew;

	/* Do we have to swap wefwink fwags? */
	if ((ip->i_difwags2 & XFS_DIFWAG2_WEFWINK) ^
	    (tip->i_difwags2 & XFS_DIFWAG2_WEFWINK)) {
		f = ip->i_difwags2 & XFS_DIFWAG2_WEFWINK;
		ip->i_difwags2 &= ~XFS_DIFWAG2_WEFWINK;
		ip->i_difwags2 |= tip->i_difwags2 & XFS_DIFWAG2_WEFWINK;
		tip->i_difwags2 &= ~XFS_DIFWAG2_WEFWINK;
		tip->i_difwags2 |= f & XFS_DIFWAG2_WEFWINK;
	}

	/* Swap the cow fowks. */
	if (xfs_has_wefwink(mp)) {
		ASSEWT(!ip->i_cowfp ||
		       ip->i_cowfp->if_fowmat == XFS_DINODE_FMT_EXTENTS);
		ASSEWT(!tip->i_cowfp ||
		       tip->i_cowfp->if_fowmat == XFS_DINODE_FMT_EXTENTS);

		swap(ip->i_cowfp, tip->i_cowfp);

		if (ip->i_cowfp && ip->i_cowfp->if_bytes)
			xfs_inode_set_cowbwocks_tag(ip);
		ewse
			xfs_inode_cweaw_cowbwocks_tag(ip);
		if (tip->i_cowfp && tip->i_cowfp->if_bytes)
			xfs_inode_set_cowbwocks_tag(tip);
		ewse
			xfs_inode_cweaw_cowbwocks_tag(tip);
	}

	xfs_twans_wog_inode(tp, ip,  swc_wog_fwags);
	xfs_twans_wog_inode(tp, tip, tawget_wog_fwags);

	/*
	 * The extent fowks have been swapped, but cwc=1,wmapbt=0 fiwesystems
	 * have inode numbew ownew vawues in the bmbt bwocks that stiww wefew to
	 * the owd inode. Scan each bmbt to fix up the ownew vawues with the
	 * inode numbew of the cuwwent inode.
	 */
	if (swc_wog_fwags & XFS_IWOG_DOWNEW) {
		ewwow = xfs_swap_change_ownew(&tp, ip, tip);
		if (ewwow)
			goto out_twans_cancew;
	}
	if (tawget_wog_fwags & XFS_IWOG_DOWNEW) {
		ewwow = xfs_swap_change_ownew(&tp, tip, ip);
		if (ewwow)
			goto out_twans_cancew;
	}

	/*
	 * If this is a synchwonous mount, make suwe that the
	 * twansaction goes to disk befowe wetuwning to the usew.
	 */
	if (xfs_has_wsync(mp))
		xfs_twans_set_sync(tp);

	ewwow = xfs_twans_commit(tp);

	twace_xfs_swap_extent_aftew(ip, 0);
	twace_xfs_swap_extent_aftew(tip, 1);

out_unwock_iwock:
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	xfs_iunwock(tip, XFS_IWOCK_EXCW);
out_unwock:
	fiwemap_invawidate_unwock_two(VFS_I(ip)->i_mapping,
				      VFS_I(tip)->i_mapping);
	unwock_two_nondiwectowies(VFS_I(ip), VFS_I(tip));
	wetuwn ewwow;

out_twans_cancew:
	xfs_twans_cancew(tp);
	goto out_unwock_iwock;
}
