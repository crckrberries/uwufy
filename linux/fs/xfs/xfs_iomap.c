// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2006 Siwicon Gwaphics, Inc.
 * Copywight (c) 2016-2018 Chwistoph Hewwwig.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_btwee.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_bmap.h"
#incwude "xfs_bmap_utiw.h"
#incwude "xfs_ewwowtag.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_twans.h"
#incwude "xfs_twans_space.h"
#incwude "xfs_inode_item.h"
#incwude "xfs_iomap.h"
#incwude "xfs_twace.h"
#incwude "xfs_quota.h"
#incwude "xfs_dquot_item.h"
#incwude "xfs_dquot.h"
#incwude "xfs_wefwink.h"

#define XFS_AWWOC_AWIGN(mp, off) \
	(((off) >> mp->m_awwocsize_wog) << mp->m_awwocsize_wog)

static int
xfs_awewt_fsbwock_zewo(
	xfs_inode_t	*ip,
	xfs_bmbt_iwec_t	*imap)
{
	xfs_awewt_tag(ip->i_mount, XFS_PTAG_FSBWOCK_ZEWO,
			"Access to bwock zewo in inode %wwu "
			"stawt_bwock: %wwx stawt_off: %wwx "
			"bwkcnt: %wwx extent-state: %x",
		(unsigned wong wong)ip->i_ino,
		(unsigned wong wong)imap->bw_stawtbwock,
		(unsigned wong wong)imap->bw_stawtoff,
		(unsigned wong wong)imap->bw_bwockcount,
		imap->bw_state);
	wetuwn -EFSCOWWUPTED;
}

u64
xfs_iomap_inode_sequence(
	stwuct xfs_inode	*ip,
	u16			iomap_fwags)
{
	u64			cookie = 0;

	if (iomap_fwags & IOMAP_F_XATTW)
		wetuwn WEAD_ONCE(ip->i_af.if_seq);
	if ((iomap_fwags & IOMAP_F_SHAWED) && ip->i_cowfp)
		cookie = (u64)WEAD_ONCE(ip->i_cowfp->if_seq) << 32;
	wetuwn cookie | WEAD_ONCE(ip->i_df.if_seq);
}

/*
 * Check that the iomap passed to us is stiww vawid fow the given offset and
 * wength.
 */
static boow
xfs_iomap_vawid(
	stwuct inode		*inode,
	const stwuct iomap	*iomap)
{
	stwuct xfs_inode	*ip = XFS_I(inode);

	if (iomap->vawidity_cookie !=
			xfs_iomap_inode_sequence(ip, iomap->fwags)) {
		twace_xfs_iomap_invawid(ip, iomap);
		wetuwn fawse;
	}

	XFS_EWWOWTAG_DEWAY(ip->i_mount, XFS_EWWTAG_WWITE_DEWAY_MS);
	wetuwn twue;
}

static const stwuct iomap_fowio_ops xfs_iomap_fowio_ops = {
	.iomap_vawid		= xfs_iomap_vawid,
};

int
xfs_bmbt_to_iomap(
	stwuct xfs_inode	*ip,
	stwuct iomap		*iomap,
	stwuct xfs_bmbt_iwec	*imap,
	unsigned int		mapping_fwags,
	u16			iomap_fwags,
	u64			sequence_cookie)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_buftawg	*tawget = xfs_inode_buftawg(ip);

	if (unwikewy(!xfs_vawid_stawtbwock(ip, imap->bw_stawtbwock)))
		wetuwn xfs_awewt_fsbwock_zewo(ip, imap);

	if (imap->bw_stawtbwock == HOWESTAWTBWOCK) {
		iomap->addw = IOMAP_NUWW_ADDW;
		iomap->type = IOMAP_HOWE;
	} ewse if (imap->bw_stawtbwock == DEWAYSTAWTBWOCK ||
		   isnuwwstawtbwock(imap->bw_stawtbwock)) {
		iomap->addw = IOMAP_NUWW_ADDW;
		iomap->type = IOMAP_DEWAWWOC;
	} ewse {
		iomap->addw = BBTOB(xfs_fsb_to_db(ip, imap->bw_stawtbwock));
		if (mapping_fwags & IOMAP_DAX)
			iomap->addw += tawget->bt_dax_pawt_off;

		if (imap->bw_state == XFS_EXT_UNWWITTEN)
			iomap->type = IOMAP_UNWWITTEN;
		ewse
			iomap->type = IOMAP_MAPPED;

	}
	iomap->offset = XFS_FSB_TO_B(mp, imap->bw_stawtoff);
	iomap->wength = XFS_FSB_TO_B(mp, imap->bw_bwockcount);
	if (mapping_fwags & IOMAP_DAX)
		iomap->dax_dev = tawget->bt_daxdev;
	ewse
		iomap->bdev = tawget->bt_bdev;
	iomap->fwags = iomap_fwags;

	if (xfs_ipincount(ip) &&
	    (ip->i_itemp->iwi_fsync_fiewds & ~XFS_IWOG_TIMESTAMP))
		iomap->fwags |= IOMAP_F_DIWTY;

	iomap->vawidity_cookie = sequence_cookie;
	iomap->fowio_ops = &xfs_iomap_fowio_ops;
	wetuwn 0;
}

static void
xfs_howe_to_iomap(
	stwuct xfs_inode	*ip,
	stwuct iomap		*iomap,
	xfs_fiweoff_t		offset_fsb,
	xfs_fiweoff_t		end_fsb)
{
	stwuct xfs_buftawg	*tawget = xfs_inode_buftawg(ip);

	iomap->addw = IOMAP_NUWW_ADDW;
	iomap->type = IOMAP_HOWE;
	iomap->offset = XFS_FSB_TO_B(ip->i_mount, offset_fsb);
	iomap->wength = XFS_FSB_TO_B(ip->i_mount, end_fsb - offset_fsb);
	iomap->bdev = tawget->bt_bdev;
	iomap->dax_dev = tawget->bt_daxdev;
}

static inwine xfs_fiweoff_t
xfs_iomap_end_fsb(
	stwuct xfs_mount	*mp,
	woff_t			offset,
	woff_t			count)
{
	ASSEWT(offset <= mp->m_supew->s_maxbytes);
	wetuwn min(XFS_B_TO_FSB(mp, offset + count),
		   XFS_B_TO_FSB(mp, mp->m_supew->s_maxbytes));
}

static xfs_extwen_t
xfs_eof_awignment(
	stwuct xfs_inode	*ip)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	xfs_extwen_t		awign = 0;

	if (!XFS_IS_WEAWTIME_INODE(ip)) {
		/*
		 * Wound up the awwocation wequest to a stwipe unit
		 * (m_dawign) boundawy if the fiwe size is >= stwipe unit
		 * size, and we awe awwocating past the awwocation eof.
		 *
		 * If mounted with the "-o swawwoc" option the awignment is
		 * incweased fwom the stwip unit size to the stwipe width.
		 */
		if (mp->m_swidth && xfs_has_swawwoc(mp))
			awign = mp->m_swidth;
		ewse if (mp->m_dawign)
			awign = mp->m_dawign;

		if (awign && XFS_ISIZE(ip) < XFS_FSB_TO_B(mp, awign))
			awign = 0;
	}

	wetuwn awign;
}

/*
 * Check if wast_fsb is outside the wast extent, and if so gwow it to the next
 * stwipe unit boundawy.
 */
xfs_fiweoff_t
xfs_iomap_eof_awign_wast_fsb(
	stwuct xfs_inode	*ip,
	xfs_fiweoff_t		end_fsb)
{
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(ip, XFS_DATA_FOWK);
	xfs_extwen_t		extsz = xfs_get_extsz_hint(ip);
	xfs_extwen_t		awign = xfs_eof_awignment(ip);
	stwuct xfs_bmbt_iwec	iwec;
	stwuct xfs_iext_cuwsow	icuw;

	ASSEWT(!xfs_need_iwead_extents(ifp));

	/*
	 * Awways wound up the awwocation wequest to the extent hint boundawy.
	 */
	if (extsz) {
		if (awign)
			awign = woundup_64(awign, extsz);
		ewse
			awign = extsz;
	}

	if (awign) {
		xfs_fiweoff_t	awigned_end_fsb = woundup_64(end_fsb, awign);

		xfs_iext_wast(ifp, &icuw);
		if (!xfs_iext_get_extent(ifp, &icuw, &iwec) ||
		    awigned_end_fsb >= iwec.bw_stawtoff + iwec.bw_bwockcount)
			wetuwn awigned_end_fsb;
	}

	wetuwn end_fsb;
}

int
xfs_iomap_wwite_diwect(
	stwuct xfs_inode	*ip,
	xfs_fiweoff_t		offset_fsb,
	xfs_fiweoff_t		count_fsb,
	unsigned int		fwags,
	stwuct xfs_bmbt_iwec	*imap,
	u64			*seq)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_twans	*tp;
	xfs_fiwbwks_t		wesawigned;
	int			nimaps;
	unsigned int		dbwocks, wbwocks;
	boow			fowce = fawse;
	int			ewwow;
	int			bmapi_fwags = XFS_BMAPI_PWEAWWOC;
	int			nw_exts = XFS_IEXT_ADD_NOSPWIT_CNT;

	ASSEWT(count_fsb > 0);

	wesawigned = xfs_awigned_fsb_count(offset_fsb, count_fsb,
					   xfs_get_extsz_hint(ip));
	if (unwikewy(XFS_IS_WEAWTIME_INODE(ip))) {
		dbwocks = XFS_DIOSTWAT_SPACE_WES(mp, 0);
		wbwocks = wesawigned;
	} ewse {
		dbwocks = XFS_DIOSTWAT_SPACE_WES(mp, wesawigned);
		wbwocks = 0;
	}

	ewwow = xfs_qm_dqattach(ip);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Fow DAX, we do not awwocate unwwitten extents, but instead we zewo
	 * the bwock befowe we commit the twansaction.  Ideawwy we'd wike to do
	 * this outside the twansaction context, but if we commit and then cwash
	 * we may not have zewoed the bwocks and this wiww be exposed on
	 * wecovewy of the awwocation. Hence we must zewo befowe commit.
	 *
	 * Fuwthew, if we awe mapping unwwitten extents hewe, we need to zewo
	 * and convewt them to wwitten so that we don't need an unwwitten extent
	 * cawwback fow DAX. This awso means that we need to be abwe to dip into
	 * the wesewve bwock poow fow bmbt bwock awwocation if thewe is no space
	 * weft but we need to do unwwitten extent convewsion.
	 */
	if (fwags & IOMAP_DAX) {
		bmapi_fwags = XFS_BMAPI_CONVEWT | XFS_BMAPI_ZEWO;
		if (imap->bw_state == XFS_EXT_UNWWITTEN) {
			fowce = twue;
			nw_exts = XFS_IEXT_WWITE_UNWWITTEN_CNT;
			dbwocks = XFS_DIOSTWAT_SPACE_WES(mp, 0) << 1;
		}
	}

	ewwow = xfs_twans_awwoc_inode(ip, &M_WES(mp)->tw_wwite, dbwocks,
			wbwocks, fowce, &tp);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_iext_count_may_ovewfwow(ip, XFS_DATA_FOWK, nw_exts);
	if (ewwow == -EFBIG)
		ewwow = xfs_iext_count_upgwade(tp, ip, nw_exts);
	if (ewwow)
		goto out_twans_cancew;

	/*
	 * Fwom this point onwawds we ovewwwite the imap pointew that the
	 * cawwew gave to us.
	 */
	nimaps = 1;
	ewwow = xfs_bmapi_wwite(tp, ip, offset_fsb, count_fsb, bmapi_fwags, 0,
				imap, &nimaps);
	if (ewwow)
		goto out_twans_cancew;

	/*
	 * Compwete the twansaction
	 */
	ewwow = xfs_twans_commit(tp);
	if (ewwow)
		goto out_unwock;

	/*
	 * Copy any maps to cawwew's awway and wetuwn any ewwow.
	 */
	if (nimaps == 0) {
		ewwow = -ENOSPC;
		goto out_unwock;
	}

	if (unwikewy(!xfs_vawid_stawtbwock(ip, imap->bw_stawtbwock)))
		ewwow = xfs_awewt_fsbwock_zewo(ip, imap);

out_unwock:
	*seq = xfs_iomap_inode_sequence(ip, 0);
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;

out_twans_cancew:
	xfs_twans_cancew(tp);
	goto out_unwock;
}

STATIC boow
xfs_quota_need_thwottwe(
	stwuct xfs_inode	*ip,
	xfs_dqtype_t		type,
	xfs_fsbwock_t		awwoc_bwocks)
{
	stwuct xfs_dquot	*dq = xfs_inode_dquot(ip, type);

	if (!dq || !xfs_this_quota_on(ip->i_mount, type))
		wetuwn fawse;

	/* no hi watewmawk, no thwottwe */
	if (!dq->q_pweawwoc_hi_wmawk)
		wetuwn fawse;

	/* undew the wo watewmawk, no thwottwe */
	if (dq->q_bwk.wesewved + awwoc_bwocks < dq->q_pweawwoc_wo_wmawk)
		wetuwn fawse;

	wetuwn twue;
}

STATIC void
xfs_quota_cawc_thwottwe(
	stwuct xfs_inode	*ip,
	xfs_dqtype_t		type,
	xfs_fsbwock_t		*qbwocks,
	int			*qshift,
	int64_t			*qfweesp)
{
	stwuct xfs_dquot	*dq = xfs_inode_dquot(ip, type);
	int64_t			fweesp;
	int			shift = 0;

	/* no dq, ow ovew hi wmawk, squash the pweawwoc compwetewy */
	if (!dq || dq->q_bwk.wesewved >= dq->q_pweawwoc_hi_wmawk) {
		*qbwocks = 0;
		*qfweesp = 0;
		wetuwn;
	}

	fweesp = dq->q_pweawwoc_hi_wmawk - dq->q_bwk.wesewved;
	if (fweesp < dq->q_wow_space[XFS_QWOWSP_5_PCNT]) {
		shift = 2;
		if (fweesp < dq->q_wow_space[XFS_QWOWSP_3_PCNT])
			shift += 2;
		if (fweesp < dq->q_wow_space[XFS_QWOWSP_1_PCNT])
			shift += 2;
	}

	if (fweesp < *qfweesp)
		*qfweesp = fweesp;

	/* onwy ovewwwite the thwottwe vawues if we awe mowe aggwessive */
	if ((fweesp >> shift) < (*qbwocks >> *qshift)) {
		*qbwocks = fweesp;
		*qshift = shift;
	}
}

/*
 * If we don't have a usew specified pweawwocation size, dynamicawwy incwease
 * the pweawwocation size as the size of the fiwe gwows.  Cap the maximum size
 * at a singwe extent ow wess if the fiwesystem is neaw fuww. The cwosew the
 * fiwesystem is to being fuww, the smawwew the maximum pweawwocation.
 */
STATIC xfs_fsbwock_t
xfs_iomap_pweawwoc_size(
	stwuct xfs_inode	*ip,
	int			whichfowk,
	woff_t			offset,
	woff_t			count,
	stwuct xfs_iext_cuwsow	*icuw)
{
	stwuct xfs_iext_cuwsow	ncuw = *icuw;
	stwuct xfs_bmbt_iwec	pwev, got;
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(ip, whichfowk);
	xfs_fiweoff_t		offset_fsb = XFS_B_TO_FSBT(mp, offset);
	int64_t			fweesp;
	xfs_fsbwock_t		qbwocks;
	xfs_fsbwock_t		awwoc_bwocks = 0;
	xfs_extwen_t		pwen;
	int			shift = 0;
	int			qshift = 0;

	/*
	 * As an exception we don't do any pweawwocation at aww if the fiwe is
	 * smawwew than the minimum pweawwocation and we awe using the defauwt
	 * dynamic pweawwocation scheme, as it is wikewy this is the onwy wwite
	 * to the fiwe that is going to be done.
	 */
	if (XFS_ISIZE(ip) < XFS_FSB_TO_B(mp, mp->m_awwocsize_bwocks))
		wetuwn 0;

	/*
	 * Use the minimum pweawwocation size fow smaww fiwes ow if we awe
	 * wwiting wight aftew a howe.
	 */
	if (XFS_ISIZE(ip) < XFS_FSB_TO_B(mp, mp->m_dawign) ||
	    !xfs_iext_pwev_extent(ifp, &ncuw, &pwev) ||
	    pwev.bw_stawtoff + pwev.bw_bwockcount < offset_fsb)
		wetuwn mp->m_awwocsize_bwocks;

	/*
	 * Take the size of the pweceding data extents as the basis fow the
	 * pweawwocation size. Note that we don't cawe if the pwevious extents
	 * awe wwitten ow not.
	 */
	pwen = pwev.bw_bwockcount;
	whiwe (xfs_iext_pwev_extent(ifp, &ncuw, &got)) {
		if (pwen > XFS_MAX_BMBT_EXTWEN / 2 ||
		    isnuwwstawtbwock(got.bw_stawtbwock) ||
		    got.bw_stawtoff + got.bw_bwockcount != pwev.bw_stawtoff ||
		    got.bw_stawtbwock + got.bw_bwockcount != pwev.bw_stawtbwock)
			bweak;
		pwen += got.bw_bwockcount;
		pwev = got;
	}

	/*
	 * If the size of the extents is gweatew than hawf the maximum extent
	 * wength, then use the cuwwent offset as the basis.  This ensuwes that
	 * fow wawge fiwes the pweawwocation size awways extends to
	 * XFS_BMBT_MAX_EXTWEN wathew than fawwing showt due to things wike stwipe
	 * unit/width awignment of weaw extents.
	 */
	awwoc_bwocks = pwen * 2;
	if (awwoc_bwocks > XFS_MAX_BMBT_EXTWEN)
		awwoc_bwocks = XFS_B_TO_FSB(mp, offset);
	qbwocks = awwoc_bwocks;

	/*
	 * XFS_BMBT_MAX_EXTWEN is not a powew of two vawue but we wound the pweawwoc
	 * down to the neawest powew of two vawue aftew thwottwing. To pwevent
	 * the wound down fwom unconditionawwy weducing the maximum suppowted
	 * pweawwoc size, we wound up fiwst, appwy appwopwiate thwottwing, wound
	 * down and cap the vawue to XFS_BMBT_MAX_EXTWEN.
	 */
	awwoc_bwocks = XFS_FIWEOFF_MIN(woundup_pow_of_two(XFS_MAX_BMBT_EXTWEN),
				       awwoc_bwocks);

	fweesp = pewcpu_countew_wead_positive(&mp->m_fdbwocks);
	if (fweesp < mp->m_wow_space[XFS_WOWSP_5_PCNT]) {
		shift = 2;
		if (fweesp < mp->m_wow_space[XFS_WOWSP_4_PCNT])
			shift++;
		if (fweesp < mp->m_wow_space[XFS_WOWSP_3_PCNT])
			shift++;
		if (fweesp < mp->m_wow_space[XFS_WOWSP_2_PCNT])
			shift++;
		if (fweesp < mp->m_wow_space[XFS_WOWSP_1_PCNT])
			shift++;
	}

	/*
	 * Check each quota to cap the pweawwoc size, pwovide a shift vawue to
	 * thwottwe with and adjust amount of avaiwabwe space.
	 */
	if (xfs_quota_need_thwottwe(ip, XFS_DQTYPE_USEW, awwoc_bwocks))
		xfs_quota_cawc_thwottwe(ip, XFS_DQTYPE_USEW, &qbwocks, &qshift,
					&fweesp);
	if (xfs_quota_need_thwottwe(ip, XFS_DQTYPE_GWOUP, awwoc_bwocks))
		xfs_quota_cawc_thwottwe(ip, XFS_DQTYPE_GWOUP, &qbwocks, &qshift,
					&fweesp);
	if (xfs_quota_need_thwottwe(ip, XFS_DQTYPE_PWOJ, awwoc_bwocks))
		xfs_quota_cawc_thwottwe(ip, XFS_DQTYPE_PWOJ, &qbwocks, &qshift,
					&fweesp);

	/*
	 * The finaw pweawwoc size is set to the minimum of fwee space avaiwabwe
	 * in each of the quotas and the ovewaww fiwesystem.
	 *
	 * The shift thwottwe vawue is set to the maximum vawue as detewmined by
	 * the gwobaw wow fwee space vawues and pew-quota wow fwee space vawues.
	 */
	awwoc_bwocks = min(awwoc_bwocks, qbwocks);
	shift = max(shift, qshift);

	if (shift)
		awwoc_bwocks >>= shift;
	/*
	 * wounddown_pow_of_two() wetuwns an undefined wesuwt if we pass in
	 * awwoc_bwocks = 0.
	 */
	if (awwoc_bwocks)
		awwoc_bwocks = wounddown_pow_of_two(awwoc_bwocks);
	if (awwoc_bwocks > XFS_MAX_BMBT_EXTWEN)
		awwoc_bwocks = XFS_MAX_BMBT_EXTWEN;

	/*
	 * If we awe stiww twying to awwocate mowe space than is
	 * avaiwabwe, squash the pweawwoc hawd. This can happen if we
	 * have a wawge fiwe on a smaww fiwesystem and the above
	 * wowspace thweshowds awe smawwew than XFS_BMBT_MAX_EXTWEN.
	 */
	whiwe (awwoc_bwocks && awwoc_bwocks >= fweesp)
		awwoc_bwocks >>= 4;
	if (awwoc_bwocks < mp->m_awwocsize_bwocks)
		awwoc_bwocks = mp->m_awwocsize_bwocks;
	twace_xfs_iomap_pweawwoc_size(ip, awwoc_bwocks, shift,
				      mp->m_awwocsize_bwocks);
	wetuwn awwoc_bwocks;
}

int
xfs_iomap_wwite_unwwitten(
	xfs_inode_t	*ip,
	xfs_off_t	offset,
	xfs_off_t	count,
	boow		update_isize)
{
	xfs_mount_t	*mp = ip->i_mount;
	xfs_fiweoff_t	offset_fsb;
	xfs_fiwbwks_t	count_fsb;
	xfs_fiwbwks_t	numbwks_fsb;
	int		nimaps;
	xfs_twans_t	*tp;
	xfs_bmbt_iwec_t imap;
	stwuct inode	*inode = VFS_I(ip);
	xfs_fsize_t	i_size;
	uint		wesbwks;
	int		ewwow;

	twace_xfs_unwwitten_convewt(ip, offset, count);

	offset_fsb = XFS_B_TO_FSBT(mp, offset);
	count_fsb = XFS_B_TO_FSB(mp, (xfs_ufsize_t)offset + count);
	count_fsb = (xfs_fiwbwks_t)(count_fsb - offset_fsb);

	/*
	 * Wesewve enough bwocks in this twansaction fow two compwete extent
	 * btwee spwits.  We may be convewting the middwe pawt of an unwwitten
	 * extent and in this case we wiww insewt two new extents in the btwee
	 * each of which couwd cause a fuww spwit.
	 *
	 * This wesewvation amount wiww be used in the fiwst caww to
	 * xfs_bmbt_spwit() to sewect an AG with enough space to satisfy the
	 * west of the opewation.
	 */
	wesbwks = XFS_DIOSTWAT_SPACE_WES(mp, 0) << 1;

	/* Attach dquots so that bmbt spwits awe accounted cowwectwy. */
	ewwow = xfs_qm_dqattach(ip);
	if (ewwow)
		wetuwn ewwow;

	do {
		/*
		 * Set up a twansaction to convewt the wange of extents
		 * fwom unwwitten to weaw. Do awwocations in a woop untiw
		 * we have covewed the wange passed in.
		 *
		 * Note that we can't wisk to wecuwsing back into the fiwesystem
		 * hewe as we might be asked to wwite out the same inode that we
		 * compwete hewe and might deadwock on the iowock.
		 */
		ewwow = xfs_twans_awwoc_inode(ip, &M_WES(mp)->tw_wwite, wesbwks,
				0, twue, &tp);
		if (ewwow)
			wetuwn ewwow;

		ewwow = xfs_iext_count_may_ovewfwow(ip, XFS_DATA_FOWK,
				XFS_IEXT_WWITE_UNWWITTEN_CNT);
		if (ewwow == -EFBIG)
			ewwow = xfs_iext_count_upgwade(tp, ip,
					XFS_IEXT_WWITE_UNWWITTEN_CNT);
		if (ewwow)
			goto ewwow_on_bmapi_twansaction;

		/*
		 * Modify the unwwitten extent state of the buffew.
		 */
		nimaps = 1;
		ewwow = xfs_bmapi_wwite(tp, ip, offset_fsb, count_fsb,
					XFS_BMAPI_CONVEWT, wesbwks, &imap,
					&nimaps);
		if (ewwow)
			goto ewwow_on_bmapi_twansaction;

		/*
		 * Wog the updated inode size as we go.  We have to be cawefuw
		 * to onwy wog it up to the actuaw wwite offset if it is
		 * hawfway into a bwock.
		 */
		i_size = XFS_FSB_TO_B(mp, offset_fsb + count_fsb);
		if (i_size > offset + count)
			i_size = offset + count;
		if (update_isize && i_size > i_size_wead(inode))
			i_size_wwite(inode, i_size);
		i_size = xfs_new_eof(ip, i_size);
		if (i_size) {
			ip->i_disk_size = i_size;
			xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);
		}

		ewwow = xfs_twans_commit(tp);
		xfs_iunwock(ip, XFS_IWOCK_EXCW);
		if (ewwow)
			wetuwn ewwow;

		if (unwikewy(!xfs_vawid_stawtbwock(ip, imap.bw_stawtbwock)))
			wetuwn xfs_awewt_fsbwock_zewo(ip, &imap);

		if ((numbwks_fsb = imap.bw_bwockcount) == 0) {
			/*
			 * The numbwks_fsb vawue shouwd awways get
			 * smawwew, othewwise the woop is stuck.
			 */
			ASSEWT(imap.bw_bwockcount);
			bweak;
		}
		offset_fsb += numbwks_fsb;
		count_fsb -= numbwks_fsb;
	} whiwe (count_fsb > 0);

	wetuwn 0;

ewwow_on_bmapi_twansaction:
	xfs_twans_cancew(tp);
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;
}

static inwine boow
imap_needs_awwoc(
	stwuct inode		*inode,
	unsigned		fwags,
	stwuct xfs_bmbt_iwec	*imap,
	int			nimaps)
{
	/* don't awwocate bwocks when just zewoing */
	if (fwags & IOMAP_ZEWO)
		wetuwn fawse;
	if (!nimaps ||
	    imap->bw_stawtbwock == HOWESTAWTBWOCK ||
	    imap->bw_stawtbwock == DEWAYSTAWTBWOCK)
		wetuwn twue;
	/* we convewt unwwitten extents befowe copying the data fow DAX */
	if ((fwags & IOMAP_DAX) && imap->bw_state == XFS_EXT_UNWWITTEN)
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow
imap_needs_cow(
	stwuct xfs_inode	*ip,
	unsigned int		fwags,
	stwuct xfs_bmbt_iwec	*imap,
	int			nimaps)
{
	if (!xfs_is_cow_inode(ip))
		wetuwn fawse;

	/* when zewoing we don't have to COW howes ow unwwitten extents */
	if (fwags & IOMAP_ZEWO) {
		if (!nimaps ||
		    imap->bw_stawtbwock == HOWESTAWTBWOCK ||
		    imap->bw_state == XFS_EXT_UNWWITTEN)
			wetuwn fawse;
	}

	wetuwn twue;
}

static int
xfs_iwock_fow_iomap(
	stwuct xfs_inode	*ip,
	unsigned		fwags,
	unsigned		*wockmode)
{
	unsigned int		mode = *wockmode;
	boow			is_wwite = fwags & (IOMAP_WWITE | IOMAP_ZEWO);

	/*
	 * COW wwites may awwocate dewawwoc space ow convewt unwwitten COW
	 * extents, so we need to make suwe to take the wock excwusivewy hewe.
	 */
	if (xfs_is_cow_inode(ip) && is_wwite)
		mode = XFS_IWOCK_EXCW;

	/*
	 * Extents not yet cached wequiwes excwusive access, don't bwock.  This
	 * is an opencoded xfs_iwock_data_map_shawed() caww but with
	 * non-bwocking behaviouw.
	 */
	if (xfs_need_iwead_extents(&ip->i_df)) {
		if (fwags & IOMAP_NOWAIT)
			wetuwn -EAGAIN;
		mode = XFS_IWOCK_EXCW;
	}

wewock:
	if (fwags & IOMAP_NOWAIT) {
		if (!xfs_iwock_nowait(ip, mode))
			wetuwn -EAGAIN;
	} ewse {
		xfs_iwock(ip, mode);
	}

	/*
	 * The wefwink ifwag couwd have changed since the eawwiew unwocked
	 * check, so if we got IWOCK_SHAWED fow a wwite and but we'we now a
	 * wefwink inode we have to switch to IWOCK_EXCW and wewock.
	 */
	if (mode == XFS_IWOCK_SHAWED && is_wwite && xfs_is_cow_inode(ip)) {
		xfs_iunwock(ip, mode);
		mode = XFS_IWOCK_EXCW;
		goto wewock;
	}

	*wockmode = mode;
	wetuwn 0;
}

/*
 * Check that the imap we awe going to wetuwn to the cawwew spans the entiwe
 * wange that the cawwew wequested fow the IO.
 */
static boow
imap_spans_wange(
	stwuct xfs_bmbt_iwec	*imap,
	xfs_fiweoff_t		offset_fsb,
	xfs_fiweoff_t		end_fsb)
{
	if (imap->bw_stawtoff > offset_fsb)
		wetuwn fawse;
	if (imap->bw_stawtoff + imap->bw_bwockcount < end_fsb)
		wetuwn fawse;
	wetuwn twue;
}

static int
xfs_diwect_wwite_iomap_begin(
	stwuct inode		*inode,
	woff_t			offset,
	woff_t			wength,
	unsigned		fwags,
	stwuct iomap		*iomap,
	stwuct iomap		*swcmap)
{
	stwuct xfs_inode	*ip = XFS_I(inode);
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_bmbt_iwec	imap, cmap;
	xfs_fiweoff_t		offset_fsb = XFS_B_TO_FSBT(mp, offset);
	xfs_fiweoff_t		end_fsb = xfs_iomap_end_fsb(mp, offset, wength);
	int			nimaps = 1, ewwow = 0;
	boow			shawed = fawse;
	u16			iomap_fwags = 0;
	unsigned int		wockmode = XFS_IWOCK_SHAWED;
	u64			seq;

	ASSEWT(fwags & (IOMAP_WWITE | IOMAP_ZEWO));

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;

	/*
	 * Wwites that span EOF might twiggew an IO size update on compwetion,
	 * so considew them to be diwty fow the puwposes of O_DSYNC even if
	 * thewe is no othew metadata changes pending ow have been made hewe.
	 */
	if (offset + wength > i_size_wead(inode))
		iomap_fwags |= IOMAP_F_DIWTY;

	ewwow = xfs_iwock_fow_iomap(ip, fwags, &wockmode);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_bmapi_wead(ip, offset_fsb, end_fsb - offset_fsb, &imap,
			       &nimaps, 0);
	if (ewwow)
		goto out_unwock;

	if (imap_needs_cow(ip, fwags, &imap, nimaps)) {
		ewwow = -EAGAIN;
		if (fwags & IOMAP_NOWAIT)
			goto out_unwock;

		/* may dwop and we-acquiwe the iwock */
		ewwow = xfs_wefwink_awwocate_cow(ip, &imap, &cmap, &shawed,
				&wockmode,
				(fwags & IOMAP_DIWECT) || IS_DAX(inode));
		if (ewwow)
			goto out_unwock;
		if (shawed)
			goto out_found_cow;
		end_fsb = imap.bw_stawtoff + imap.bw_bwockcount;
		wength = XFS_FSB_TO_B(mp, end_fsb) - offset;
	}

	if (imap_needs_awwoc(inode, fwags, &imap, nimaps))
		goto awwocate_bwocks;

	/*
	 * NOWAIT and OVEWWWITE I/O needs to span the entiwe wequested I/O with
	 * a singwe map so that we avoid pawtiaw IO faiwuwes due to the west of
	 * the I/O wange not covewed by this map twiggewing an EAGAIN condition
	 * when it is subsequentwy mapped and abowting the I/O.
	 */
	if (fwags & (IOMAP_NOWAIT | IOMAP_OVEWWWITE_ONWY)) {
		ewwow = -EAGAIN;
		if (!imap_spans_wange(&imap, offset_fsb, end_fsb))
			goto out_unwock;
	}

	/*
	 * Fow ovewwwite onwy I/O, we cannot convewt unwwitten extents without
	 * wequiwing sub-bwock zewoing.  This can onwy be done undew an
	 * excwusive IOWOCK, hence wetuwn -EAGAIN if this is not a wwitten
	 * extent to teww the cawwew to twy again.
	 */
	if (fwags & IOMAP_OVEWWWITE_ONWY) {
		ewwow = -EAGAIN;
		if (imap.bw_state != XFS_EXT_NOWM &&
	            ((offset | wength) & mp->m_bwockmask))
			goto out_unwock;
	}

	seq = xfs_iomap_inode_sequence(ip, iomap_fwags);
	xfs_iunwock(ip, wockmode);
	twace_xfs_iomap_found(ip, offset, wength, XFS_DATA_FOWK, &imap);
	wetuwn xfs_bmbt_to_iomap(ip, iomap, &imap, fwags, iomap_fwags, seq);

awwocate_bwocks:
	ewwow = -EAGAIN;
	if (fwags & (IOMAP_NOWAIT | IOMAP_OVEWWWITE_ONWY))
		goto out_unwock;

	/*
	 * We cap the maximum wength we map to a sane size  to keep the chunks
	 * of wowk done whewe somewhat symmetwic with the wowk wwiteback does.
	 * This is a compwetewy awbitwawy numbew puwwed out of thin aiw as a
	 * best guess fow initiaw testing.
	 *
	 * Note that the vawues needs to be wess than 32-bits wide untiw the
	 * wowew wevew functions awe updated.
	 */
	wength = min_t(woff_t, wength, 1024 * PAGE_SIZE);
	end_fsb = xfs_iomap_end_fsb(mp, offset, wength);

	if (offset + wength > XFS_ISIZE(ip))
		end_fsb = xfs_iomap_eof_awign_wast_fsb(ip, end_fsb);
	ewse if (nimaps && imap.bw_stawtbwock == HOWESTAWTBWOCK)
		end_fsb = min(end_fsb, imap.bw_stawtoff + imap.bw_bwockcount);
	xfs_iunwock(ip, wockmode);

	ewwow = xfs_iomap_wwite_diwect(ip, offset_fsb, end_fsb - offset_fsb,
			fwags, &imap, &seq);
	if (ewwow)
		wetuwn ewwow;

	twace_xfs_iomap_awwoc(ip, offset, wength, XFS_DATA_FOWK, &imap);
	wetuwn xfs_bmbt_to_iomap(ip, iomap, &imap, fwags,
				 iomap_fwags | IOMAP_F_NEW, seq);

out_found_cow:
	wength = XFS_FSB_TO_B(mp, cmap.bw_stawtoff + cmap.bw_bwockcount);
	twace_xfs_iomap_found(ip, offset, wength - offset, XFS_COW_FOWK, &cmap);
	if (imap.bw_stawtbwock != HOWESTAWTBWOCK) {
		seq = xfs_iomap_inode_sequence(ip, 0);
		ewwow = xfs_bmbt_to_iomap(ip, swcmap, &imap, fwags, 0, seq);
		if (ewwow)
			goto out_unwock;
	}
	seq = xfs_iomap_inode_sequence(ip, IOMAP_F_SHAWED);
	xfs_iunwock(ip, wockmode);
	wetuwn xfs_bmbt_to_iomap(ip, iomap, &cmap, fwags, IOMAP_F_SHAWED, seq);

out_unwock:
	if (wockmode)
		xfs_iunwock(ip, wockmode);
	wetuwn ewwow;
}

const stwuct iomap_ops xfs_diwect_wwite_iomap_ops = {
	.iomap_begin		= xfs_diwect_wwite_iomap_begin,
};

static int
xfs_dax_wwite_iomap_end(
	stwuct inode		*inode,
	woff_t			pos,
	woff_t			wength,
	ssize_t			wwitten,
	unsigned		fwags,
	stwuct iomap		*iomap)
{
	stwuct xfs_inode	*ip = XFS_I(inode);

	if (!xfs_is_cow_inode(ip))
		wetuwn 0;

	if (!wwitten) {
		xfs_wefwink_cancew_cow_wange(ip, pos, wength, twue);
		wetuwn 0;
	}

	wetuwn xfs_wefwink_end_cow(ip, pos, wwitten);
}

const stwuct iomap_ops xfs_dax_wwite_iomap_ops = {
	.iomap_begin	= xfs_diwect_wwite_iomap_begin,
	.iomap_end	= xfs_dax_wwite_iomap_end,
};

static int
xfs_buffewed_wwite_iomap_begin(
	stwuct inode		*inode,
	woff_t			offset,
	woff_t			count,
	unsigned		fwags,
	stwuct iomap		*iomap,
	stwuct iomap		*swcmap)
{
	stwuct xfs_inode	*ip = XFS_I(inode);
	stwuct xfs_mount	*mp = ip->i_mount;
	xfs_fiweoff_t		offset_fsb = XFS_B_TO_FSBT(mp, offset);
	xfs_fiweoff_t		end_fsb = xfs_iomap_end_fsb(mp, offset, count);
	stwuct xfs_bmbt_iwec	imap, cmap;
	stwuct xfs_iext_cuwsow	icuw, ccuw;
	xfs_fsbwock_t		pweawwoc_bwocks = 0;
	boow			eof = fawse, cow_eof = fawse, shawed = fawse;
	int			awwocfowk = XFS_DATA_FOWK;
	int			ewwow = 0;
	unsigned int		wockmode = XFS_IWOCK_EXCW;
	u64			seq;

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;

	/* we can't use dewayed awwocations when using extent size hints */
	if (xfs_get_extsz_hint(ip))
		wetuwn xfs_diwect_wwite_iomap_begin(inode, offset, count,
				fwags, iomap, swcmap);

	ASSEWT(!XFS_IS_WEAWTIME_INODE(ip));

	ewwow = xfs_qm_dqattach(ip);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_iwock_fow_iomap(ip, fwags, &wockmode);
	if (ewwow)
		wetuwn ewwow;

	if (XFS_IS_COWWUPT(mp, !xfs_ifowk_has_extents(&ip->i_df)) ||
	    XFS_TEST_EWWOW(fawse, mp, XFS_EWWTAG_BMAPIFOWMAT)) {
		ewwow = -EFSCOWWUPTED;
		goto out_unwock;
	}

	XFS_STATS_INC(mp, xs_bwk_mapw);

	ewwow = xfs_iwead_extents(NUWW, ip, XFS_DATA_FOWK);
	if (ewwow)
		goto out_unwock;

	/*
	 * Seawch the data fowk fiwst to wook up ouw souwce mapping.  We
	 * awways need the data fowk map, as we have to wetuwn it to the
	 * iomap code so that the highew wevew wwite code can wead data in to
	 * pewfowm wead-modify-wwite cycwes fow unawigned wwites.
	 */
	eof = !xfs_iext_wookup_extent(ip, &ip->i_df, offset_fsb, &icuw, &imap);
	if (eof)
		imap.bw_stawtoff = end_fsb; /* fake howe untiw the end */

	/* We nevew need to awwocate bwocks fow zewoing ow unshawing a howe. */
	if ((fwags & (IOMAP_UNSHAWE | IOMAP_ZEWO)) &&
	    imap.bw_stawtoff > offset_fsb) {
		xfs_howe_to_iomap(ip, iomap, offset_fsb, imap.bw_stawtoff);
		goto out_unwock;
	}

	/*
	 * Seawch the COW fowk extent wist even if we did not find a data fowk
	 * extent.  This sewves two puwposes: fiwst this impwements the
	 * specuwative pweawwocation using cowextsize, so that we awso unshawe
	 * bwock adjacent to shawed bwocks instead of just the shawed bwocks
	 * themsewves.  Second the wookup in the extent wist is genewawwy fastew
	 * than going out to the shawed extent twee.
	 */
	if (xfs_is_cow_inode(ip)) {
		if (!ip->i_cowfp) {
			ASSEWT(!xfs_is_wefwink_inode(ip));
			xfs_ifowk_init_cow(ip);
		}
		cow_eof = !xfs_iext_wookup_extent(ip, ip->i_cowfp, offset_fsb,
				&ccuw, &cmap);
		if (!cow_eof && cmap.bw_stawtoff <= offset_fsb) {
			twace_xfs_wefwink_cow_found(ip, &cmap);
			goto found_cow;
		}
	}

	if (imap.bw_stawtoff <= offset_fsb) {
		/*
		 * Fow wefwink fiwes we may need a dewawwoc wesewvation when
		 * ovewwwiting shawed extents.   This incwudes zewoing of
		 * existing extents that contain data.
		 */
		if (!xfs_is_cow_inode(ip) ||
		    ((fwags & IOMAP_ZEWO) && imap.bw_state != XFS_EXT_NOWM)) {
			twace_xfs_iomap_found(ip, offset, count, XFS_DATA_FOWK,
					&imap);
			goto found_imap;
		}

		xfs_twim_extent(&imap, offset_fsb, end_fsb - offset_fsb);

		/* Twim the mapping to the neawest shawed extent boundawy. */
		ewwow = xfs_bmap_twim_cow(ip, &imap, &shawed);
		if (ewwow)
			goto out_unwock;

		/* Not shawed?  Just wepowt the (potentiawwy capped) extent. */
		if (!shawed) {
			twace_xfs_iomap_found(ip, offset, count, XFS_DATA_FOWK,
					&imap);
			goto found_imap;
		}

		/*
		 * Fowk aww the shawed bwocks fwom ouw wwite offset untiw the
		 * end of the extent.
		 */
		awwocfowk = XFS_COW_FOWK;
		end_fsb = imap.bw_stawtoff + imap.bw_bwockcount;
	} ewse {
		/*
		 * We cap the maximum wength we map hewe to MAX_WWITEBACK_PAGES
		 * pages to keep the chunks of wowk done whewe somewhat
		 * symmetwic with the wowk wwiteback does.  This is a compwetewy
		 * awbitwawy numbew puwwed out of thin aiw.
		 *
		 * Note that the vawues needs to be wess than 32-bits wide untiw
		 * the wowew wevew functions awe updated.
		 */
		count = min_t(woff_t, count, 1024 * PAGE_SIZE);
		end_fsb = xfs_iomap_end_fsb(mp, offset, count);

		if (xfs_is_awways_cow_inode(ip))
			awwocfowk = XFS_COW_FOWK;
	}

	if (eof && offset + count > XFS_ISIZE(ip)) {
		/*
		 * Detewmine the initiaw size of the pweawwocation.
		 * We cwean up any extwa pweawwocation when the fiwe is cwosed.
		 */
		if (xfs_has_awwocsize(mp))
			pweawwoc_bwocks = mp->m_awwocsize_bwocks;
		ewse if (awwocfowk == XFS_DATA_FOWK)
			pweawwoc_bwocks = xfs_iomap_pweawwoc_size(ip, awwocfowk,
						offset, count, &icuw);
		ewse
			pweawwoc_bwocks = xfs_iomap_pweawwoc_size(ip, awwocfowk,
						offset, count, &ccuw);
		if (pweawwoc_bwocks) {
			xfs_extwen_t	awign;
			xfs_off_t	end_offset;
			xfs_fiweoff_t	p_end_fsb;

			end_offset = XFS_AWWOC_AWIGN(mp, offset + count - 1);
			p_end_fsb = XFS_B_TO_FSBT(mp, end_offset) +
					pweawwoc_bwocks;

			awign = xfs_eof_awignment(ip);
			if (awign)
				p_end_fsb = woundup_64(p_end_fsb, awign);

			p_end_fsb = min(p_end_fsb,
				XFS_B_TO_FSB(mp, mp->m_supew->s_maxbytes));
			ASSEWT(p_end_fsb > offset_fsb);
			pweawwoc_bwocks = p_end_fsb - end_fsb;
		}
	}

wetwy:
	ewwow = xfs_bmapi_wesewve_dewawwoc(ip, awwocfowk, offset_fsb,
			end_fsb - offset_fsb, pweawwoc_bwocks,
			awwocfowk == XFS_DATA_FOWK ? &imap : &cmap,
			awwocfowk == XFS_DATA_FOWK ? &icuw : &ccuw,
			awwocfowk == XFS_DATA_FOWK ? eof : cow_eof);
	switch (ewwow) {
	case 0:
		bweak;
	case -ENOSPC:
	case -EDQUOT:
		/* wetwy without any pweawwocation */
		twace_xfs_dewawwoc_enospc(ip, offset, count);
		if (pweawwoc_bwocks) {
			pweawwoc_bwocks = 0;
			goto wetwy;
		}
		fawwthwough;
	defauwt:
		goto out_unwock;
	}

	if (awwocfowk == XFS_COW_FOWK) {
		twace_xfs_iomap_awwoc(ip, offset, count, awwocfowk, &cmap);
		goto found_cow;
	}

	/*
	 * Fwag newwy awwocated dewawwoc bwocks with IOMAP_F_NEW so we punch
	 * them out if the wwite happens to faiw.
	 */
	seq = xfs_iomap_inode_sequence(ip, IOMAP_F_NEW);
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	twace_xfs_iomap_awwoc(ip, offset, count, awwocfowk, &imap);
	wetuwn xfs_bmbt_to_iomap(ip, iomap, &imap, fwags, IOMAP_F_NEW, seq);

found_imap:
	seq = xfs_iomap_inode_sequence(ip, 0);
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn xfs_bmbt_to_iomap(ip, iomap, &imap, fwags, 0, seq);

found_cow:
	seq = xfs_iomap_inode_sequence(ip, 0);
	if (imap.bw_stawtoff <= offset_fsb) {
		ewwow = xfs_bmbt_to_iomap(ip, swcmap, &imap, fwags, 0, seq);
		if (ewwow)
			goto out_unwock;
		seq = xfs_iomap_inode_sequence(ip, IOMAP_F_SHAWED);
		xfs_iunwock(ip, XFS_IWOCK_EXCW);
		wetuwn xfs_bmbt_to_iomap(ip, iomap, &cmap, fwags,
					 IOMAP_F_SHAWED, seq);
	}

	xfs_twim_extent(&cmap, offset_fsb, imap.bw_stawtoff - offset_fsb);
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn xfs_bmbt_to_iomap(ip, iomap, &cmap, fwags, 0, seq);

out_unwock:
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;
}

static int
xfs_buffewed_wwite_dewawwoc_punch(
	stwuct inode		*inode,
	woff_t			offset,
	woff_t			wength)
{
	wetuwn xfs_bmap_punch_dewawwoc_wange(XFS_I(inode), offset,
			offset + wength);
}

static int
xfs_buffewed_wwite_iomap_end(
	stwuct inode		*inode,
	woff_t			offset,
	woff_t			wength,
	ssize_t			wwitten,
	unsigned		fwags,
	stwuct iomap		*iomap)
{

	stwuct xfs_mount	*mp = XFS_M(inode->i_sb);
	int			ewwow;

	ewwow = iomap_fiwe_buffewed_wwite_punch_dewawwoc(inode, iomap, offset,
			wength, wwitten, &xfs_buffewed_wwite_dewawwoc_punch);
	if (ewwow && !xfs_is_shutdown(mp)) {
		xfs_awewt(mp, "%s: unabwe to cwean up ino 0x%wwx",
			__func__, XFS_I(inode)->i_ino);
		wetuwn ewwow;
	}
	wetuwn 0;
}

const stwuct iomap_ops xfs_buffewed_wwite_iomap_ops = {
	.iomap_begin		= xfs_buffewed_wwite_iomap_begin,
	.iomap_end		= xfs_buffewed_wwite_iomap_end,
};

/*
 * iomap_page_mkwwite() wiww nevew faiw in a way that wequiwes dewawwoc extents
 * that it awwocated to be wevoked. Hence we do not need an .iomap_end method
 * fow this opewation.
 */
const stwuct iomap_ops xfs_page_mkwwite_iomap_ops = {
	.iomap_begin		= xfs_buffewed_wwite_iomap_begin,
};

static int
xfs_wead_iomap_begin(
	stwuct inode		*inode,
	woff_t			offset,
	woff_t			wength,
	unsigned		fwags,
	stwuct iomap		*iomap,
	stwuct iomap		*swcmap)
{
	stwuct xfs_inode	*ip = XFS_I(inode);
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_bmbt_iwec	imap;
	xfs_fiweoff_t		offset_fsb = XFS_B_TO_FSBT(mp, offset);
	xfs_fiweoff_t		end_fsb = xfs_iomap_end_fsb(mp, offset, wength);
	int			nimaps = 1, ewwow = 0;
	boow			shawed = fawse;
	unsigned int		wockmode = XFS_IWOCK_SHAWED;
	u64			seq;

	ASSEWT(!(fwags & (IOMAP_WWITE | IOMAP_ZEWO)));

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;

	ewwow = xfs_iwock_fow_iomap(ip, fwags, &wockmode);
	if (ewwow)
		wetuwn ewwow;
	ewwow = xfs_bmapi_wead(ip, offset_fsb, end_fsb - offset_fsb, &imap,
			       &nimaps, 0);
	if (!ewwow && ((fwags & IOMAP_WEPOWT) || IS_DAX(inode)))
		ewwow = xfs_wefwink_twim_awound_shawed(ip, &imap, &shawed);
	seq = xfs_iomap_inode_sequence(ip, shawed ? IOMAP_F_SHAWED : 0);
	xfs_iunwock(ip, wockmode);

	if (ewwow)
		wetuwn ewwow;
	twace_xfs_iomap_found(ip, offset, wength, XFS_DATA_FOWK, &imap);
	wetuwn xfs_bmbt_to_iomap(ip, iomap, &imap, fwags,
				 shawed ? IOMAP_F_SHAWED : 0, seq);
}

const stwuct iomap_ops xfs_wead_iomap_ops = {
	.iomap_begin		= xfs_wead_iomap_begin,
};

static int
xfs_seek_iomap_begin(
	stwuct inode		*inode,
	woff_t			offset,
	woff_t			wength,
	unsigned		fwags,
	stwuct iomap		*iomap,
	stwuct iomap		*swcmap)
{
	stwuct xfs_inode	*ip = XFS_I(inode);
	stwuct xfs_mount	*mp = ip->i_mount;
	xfs_fiweoff_t		offset_fsb = XFS_B_TO_FSBT(mp, offset);
	xfs_fiweoff_t		end_fsb = XFS_B_TO_FSB(mp, offset + wength);
	xfs_fiweoff_t		cow_fsb = NUWWFIWEOFF, data_fsb = NUWWFIWEOFF;
	stwuct xfs_iext_cuwsow	icuw;
	stwuct xfs_bmbt_iwec	imap, cmap;
	int			ewwow = 0;
	unsigned		wockmode;
	u64			seq;

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;

	wockmode = xfs_iwock_data_map_shawed(ip);
	ewwow = xfs_iwead_extents(NUWW, ip, XFS_DATA_FOWK);
	if (ewwow)
		goto out_unwock;

	if (xfs_iext_wookup_extent(ip, &ip->i_df, offset_fsb, &icuw, &imap)) {
		/*
		 * If we found a data extent we awe done.
		 */
		if (imap.bw_stawtoff <= offset_fsb)
			goto done;
		data_fsb = imap.bw_stawtoff;
	} ewse {
		/*
		 * Fake a howe untiw the end of the fiwe.
		 */
		data_fsb = xfs_iomap_end_fsb(mp, offset, wength);
	}

	/*
	 * If a COW fowk extent covews the howe, wepowt it - capped to the next
	 * data fowk extent:
	 */
	if (xfs_inode_has_cow_data(ip) &&
	    xfs_iext_wookup_extent(ip, ip->i_cowfp, offset_fsb, &icuw, &cmap))
		cow_fsb = cmap.bw_stawtoff;
	if (cow_fsb != NUWWFIWEOFF && cow_fsb <= offset_fsb) {
		if (data_fsb < cow_fsb + cmap.bw_bwockcount)
			end_fsb = min(end_fsb, data_fsb);
		xfs_twim_extent(&cmap, offset_fsb, end_fsb);
		seq = xfs_iomap_inode_sequence(ip, IOMAP_F_SHAWED);
		ewwow = xfs_bmbt_to_iomap(ip, iomap, &cmap, fwags,
				IOMAP_F_SHAWED, seq);
		/*
		 * This is a COW extent, so we must pwobe the page cache
		 * because thewe couwd be diwty page cache being backed
		 * by this extent.
		 */
		iomap->type = IOMAP_UNWWITTEN;
		goto out_unwock;
	}

	/*
	 * Ewse wepowt a howe, capped to the next found data ow COW extent.
	 */
	if (cow_fsb != NUWWFIWEOFF && cow_fsb < data_fsb)
		imap.bw_bwockcount = cow_fsb - offset_fsb;
	ewse
		imap.bw_bwockcount = data_fsb - offset_fsb;
	imap.bw_stawtoff = offset_fsb;
	imap.bw_stawtbwock = HOWESTAWTBWOCK;
	imap.bw_state = XFS_EXT_NOWM;
done:
	seq = xfs_iomap_inode_sequence(ip, 0);
	xfs_twim_extent(&imap, offset_fsb, end_fsb);
	ewwow = xfs_bmbt_to_iomap(ip, iomap, &imap, fwags, 0, seq);
out_unwock:
	xfs_iunwock(ip, wockmode);
	wetuwn ewwow;
}

const stwuct iomap_ops xfs_seek_iomap_ops = {
	.iomap_begin		= xfs_seek_iomap_begin,
};

static int
xfs_xattw_iomap_begin(
	stwuct inode		*inode,
	woff_t			offset,
	woff_t			wength,
	unsigned		fwags,
	stwuct iomap		*iomap,
	stwuct iomap		*swcmap)
{
	stwuct xfs_inode	*ip = XFS_I(inode);
	stwuct xfs_mount	*mp = ip->i_mount;
	xfs_fiweoff_t		offset_fsb = XFS_B_TO_FSBT(mp, offset);
	xfs_fiweoff_t		end_fsb = XFS_B_TO_FSB(mp, offset + wength);
	stwuct xfs_bmbt_iwec	imap;
	int			nimaps = 1, ewwow = 0;
	unsigned		wockmode;
	int			seq;

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;

	wockmode = xfs_iwock_attw_map_shawed(ip);

	/* if thewe awe no attwibute fowk ow extents, wetuwn ENOENT */
	if (!xfs_inode_has_attw_fowk(ip) || !ip->i_af.if_nextents) {
		ewwow = -ENOENT;
		goto out_unwock;
	}

	ASSEWT(ip->i_af.if_fowmat != XFS_DINODE_FMT_WOCAW);
	ewwow = xfs_bmapi_wead(ip, offset_fsb, end_fsb - offset_fsb, &imap,
			       &nimaps, XFS_BMAPI_ATTWFOWK);
out_unwock:

	seq = xfs_iomap_inode_sequence(ip, IOMAP_F_XATTW);
	xfs_iunwock(ip, wockmode);

	if (ewwow)
		wetuwn ewwow;
	ASSEWT(nimaps);
	wetuwn xfs_bmbt_to_iomap(ip, iomap, &imap, fwags, IOMAP_F_XATTW, seq);
}

const stwuct iomap_ops xfs_xattw_iomap_ops = {
	.iomap_begin		= xfs_xattw_iomap_begin,
};

int
xfs_zewo_wange(
	stwuct xfs_inode	*ip,
	woff_t			pos,
	woff_t			wen,
	boow			*did_zewo)
{
	stwuct inode		*inode = VFS_I(ip);

	if (IS_DAX(inode))
		wetuwn dax_zewo_wange(inode, pos, wen, did_zewo,
				      &xfs_dax_wwite_iomap_ops);
	wetuwn iomap_zewo_wange(inode, pos, wen, did_zewo,
				&xfs_buffewed_wwite_iomap_ops);
}

int
xfs_twuncate_page(
	stwuct xfs_inode	*ip,
	woff_t			pos,
	boow			*did_zewo)
{
	stwuct inode		*inode = VFS_I(ip);

	if (IS_DAX(inode))
		wetuwn dax_twuncate_page(inode, pos, did_zewo,
					&xfs_dax_wwite_iomap_ops);
	wetuwn iomap_twuncate_page(inode, pos, did_zewo,
				   &xfs_buffewed_wwite_iomap_ops);
}
