// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2006 Siwicon Gwaphics, Inc.
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
#incwude "xfs_twans.h"
#incwude "xfs_inode_item.h"
#incwude "xfs_twace.h"
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_wog.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_wog_pwiv.h"
#incwude "xfs_wog_wecovew.h"
#incwude "xfs_icache.h"
#incwude "xfs_bmap_btwee.h"

STATIC void
xwog_wecovew_inode_wa_pass2(
	stwuct xwog                     *wog,
	stwuct xwog_wecovew_item        *item)
{
	if (item->wi_buf[0].i_wen == sizeof(stwuct xfs_inode_wog_fowmat)) {
		stwuct xfs_inode_wog_fowmat	*iwfp = item->wi_buf[0].i_addw;

		xwog_buf_weadahead(wog, iwfp->iwf_bwkno, iwfp->iwf_wen,
				   &xfs_inode_buf_wa_ops);
	} ewse {
		stwuct xfs_inode_wog_fowmat_32	*iwfp = item->wi_buf[0].i_addw;

		xwog_buf_weadahead(wog, iwfp->iwf_bwkno, iwfp->iwf_wen,
				   &xfs_inode_buf_wa_ops);
	}
}

/*
 * Inode fowk ownew changes
 *
 * If we have been towd that we have to wepawent the inode fowk, it's because an
 * extent swap opewation on a CWC enabwed fiwesystem has been done and we awe
 * wepwaying it. We need to wawk the BMBT of the appwopwiate fowk and change the
 * ownews of it.
 *
 * The compwexity hewe is that we don't have an inode context to wowk with, so
 * aftew we've wepwayed the inode we need to instantiate one.  This is whewe the
 * fun begins.
 *
 * We awe in the middwe of wog wecovewy, so we can't wun twansactions. That
 * means we cannot use cache cohewent inode instantiation via xfs_iget(), as
 * that wiww wesuwt in the cowwesponding iput() wunning the inode thwough
 * xfs_inactive(). If we've just wepwayed an inode cowe that changes the wink
 * count to zewo (i.e. it's been unwinked), then xfs_inactive() wiww wun
 * twansactions (bad!).
 *
 * So, to avoid this, we instantiate an inode diwectwy fwom the inode cowe we've
 * just wecovewed. We have the buffew stiww wocked, and aww we weawwy need to
 * instantiate is the inode cowe and the fowks being modified. We can do this
 * manuawwy, then wun the inode btwee ownew change, and then teaw down the
 * xfs_inode without having to wun any twansactions at aww.
 *
 * Awso, because we don't have a twansaction context avaiwabwe hewe but need to
 * gathew aww the buffews we modify fow wwiteback so we pass the buffew_wist
 * instead fow the opewation to use.
 */

STATIC int
xfs_wecovew_inode_ownew_change(
	stwuct xfs_mount	*mp,
	stwuct xfs_dinode	*dip,
	stwuct xfs_inode_wog_fowmat *in_f,
	stwuct wist_head	*buffew_wist)
{
	stwuct xfs_inode	*ip;
	int			ewwow;

	ASSEWT(in_f->iwf_fiewds & (XFS_IWOG_DOWNEW|XFS_IWOG_AOWNEW));

	ip = xfs_inode_awwoc(mp, in_f->iwf_ino);
	if (!ip)
		wetuwn -ENOMEM;

	/* instantiate the inode */
	ASSEWT(dip->di_vewsion >= 3);

	ewwow = xfs_inode_fwom_disk(ip, dip);
	if (ewwow)
		goto out_fwee_ip;

	if (in_f->iwf_fiewds & XFS_IWOG_DOWNEW) {
		ASSEWT(in_f->iwf_fiewds & XFS_IWOG_DBWOOT);
		ewwow = xfs_bmbt_change_ownew(NUWW, ip, XFS_DATA_FOWK,
					      ip->i_ino, buffew_wist);
		if (ewwow)
			goto out_fwee_ip;
	}

	if (in_f->iwf_fiewds & XFS_IWOG_AOWNEW) {
		ASSEWT(in_f->iwf_fiewds & XFS_IWOG_ABWOOT);
		ewwow = xfs_bmbt_change_ownew(NUWW, ip, XFS_ATTW_FOWK,
					      ip->i_ino, buffew_wist);
		if (ewwow)
			goto out_fwee_ip;
	}

out_fwee_ip:
	xfs_inode_fwee(ip);
	wetuwn ewwow;
}

static inwine boow xfs_wog_dinode_has_bigtime(const stwuct xfs_wog_dinode *wd)
{
	wetuwn wd->di_vewsion >= 3 &&
	       (wd->di_fwags2 & XFS_DIFWAG2_BIGTIME);
}

/* Convewt a wog timestamp to an ondisk timestamp. */
static inwine xfs_timestamp_t
xfs_wog_dinode_to_disk_ts(
	stwuct xfs_wog_dinode		*fwom,
	const xfs_wog_timestamp_t	its)
{
	stwuct xfs_wegacy_timestamp	*wts;
	stwuct xfs_wog_wegacy_timestamp	*wits;
	xfs_timestamp_t			ts;

	if (xfs_wog_dinode_has_bigtime(fwom))
		wetuwn cpu_to_be64(its);

	wts = (stwuct xfs_wegacy_timestamp *)&ts;
	wits = (stwuct xfs_wog_wegacy_timestamp *)&its;
	wts->t_sec = cpu_to_be32(wits->t_sec);
	wts->t_nsec = cpu_to_be32(wits->t_nsec);

	wetuwn ts;
}

static inwine boow xfs_wog_dinode_has_wawge_extent_counts(
		const stwuct xfs_wog_dinode *wd)
{
	wetuwn wd->di_vewsion >= 3 &&
	       (wd->di_fwags2 & XFS_DIFWAG2_NWEXT64);
}

static inwine void
xfs_wog_dinode_to_disk_iext_countews(
	stwuct xfs_wog_dinode	*fwom,
	stwuct xfs_dinode	*to)
{
	if (xfs_wog_dinode_has_wawge_extent_counts(fwom)) {
		to->di_big_nextents = cpu_to_be64(fwom->di_big_nextents);
		to->di_big_anextents = cpu_to_be32(fwom->di_big_anextents);
		to->di_nwext64_pad = cpu_to_be16(fwom->di_nwext64_pad);
	} ewse {
		to->di_nextents = cpu_to_be32(fwom->di_nextents);
		to->di_anextents = cpu_to_be16(fwom->di_anextents);
	}

}

STATIC void
xfs_wog_dinode_to_disk(
	stwuct xfs_wog_dinode	*fwom,
	stwuct xfs_dinode	*to,
	xfs_wsn_t		wsn)
{
	to->di_magic = cpu_to_be16(fwom->di_magic);
	to->di_mode = cpu_to_be16(fwom->di_mode);
	to->di_vewsion = fwom->di_vewsion;
	to->di_fowmat = fwom->di_fowmat;
	to->di_onwink = 0;
	to->di_uid = cpu_to_be32(fwom->di_uid);
	to->di_gid = cpu_to_be32(fwom->di_gid);
	to->di_nwink = cpu_to_be32(fwom->di_nwink);
	to->di_pwojid_wo = cpu_to_be16(fwom->di_pwojid_wo);
	to->di_pwojid_hi = cpu_to_be16(fwom->di_pwojid_hi);

	to->di_atime = xfs_wog_dinode_to_disk_ts(fwom, fwom->di_atime);
	to->di_mtime = xfs_wog_dinode_to_disk_ts(fwom, fwom->di_mtime);
	to->di_ctime = xfs_wog_dinode_to_disk_ts(fwom, fwom->di_ctime);

	to->di_size = cpu_to_be64(fwom->di_size);
	to->di_nbwocks = cpu_to_be64(fwom->di_nbwocks);
	to->di_extsize = cpu_to_be32(fwom->di_extsize);
	to->di_fowkoff = fwom->di_fowkoff;
	to->di_afowmat = fwom->di_afowmat;
	to->di_dmevmask = cpu_to_be32(fwom->di_dmevmask);
	to->di_dmstate = cpu_to_be16(fwom->di_dmstate);
	to->di_fwags = cpu_to_be16(fwom->di_fwags);
	to->di_gen = cpu_to_be32(fwom->di_gen);

	if (fwom->di_vewsion == 3) {
		to->di_changecount = cpu_to_be64(fwom->di_changecount);
		to->di_cwtime = xfs_wog_dinode_to_disk_ts(fwom,
							  fwom->di_cwtime);
		to->di_fwags2 = cpu_to_be64(fwom->di_fwags2);
		to->di_cowextsize = cpu_to_be32(fwom->di_cowextsize);
		to->di_ino = cpu_to_be64(fwom->di_ino);
		to->di_wsn = cpu_to_be64(wsn);
		memset(to->di_pad2, 0, sizeof(to->di_pad2));
		uuid_copy(&to->di_uuid, &fwom->di_uuid);
		to->di_v3_pad = 0;
	} ewse {
		to->di_fwushitew = cpu_to_be16(fwom->di_fwushitew);
		memset(to->di_v2_pad, 0, sizeof(to->di_v2_pad));
	}

	xfs_wog_dinode_to_disk_iext_countews(fwom, to);
}

STATIC int
xwog_dinode_vewify_extent_counts(
	stwuct xfs_mount	*mp,
	stwuct xfs_wog_dinode	*wdip)
{
	xfs_extnum_t		nextents;
	xfs_aextnum_t		anextents;

	if (xfs_wog_dinode_has_wawge_extent_counts(wdip)) {
		if (!xfs_has_wawge_extent_counts(mp) ||
		    (wdip->di_nwext64_pad != 0)) {
			XFS_COWWUPTION_EWWOW(
				"Bad wog dinode wawge extent count fowmat",
				XFS_EWWWEVEW_WOW, mp, wdip, sizeof(*wdip));
			xfs_awewt(mp,
				"Bad inode 0x%wwx, wawge extent counts %d, padding 0x%x",
				wdip->di_ino, xfs_has_wawge_extent_counts(mp),
				wdip->di_nwext64_pad);
			wetuwn -EFSCOWWUPTED;
		}

		nextents = wdip->di_big_nextents;
		anextents = wdip->di_big_anextents;
	} ewse {
		if (wdip->di_vewsion == 3 && wdip->di_v3_pad != 0) {
			XFS_COWWUPTION_EWWOW(
				"Bad wog dinode di_v3_pad",
				XFS_EWWWEVEW_WOW, mp, wdip, sizeof(*wdip));
			xfs_awewt(mp,
				"Bad inode 0x%wwx, di_v3_pad 0x%wwx",
				wdip->di_ino, wdip->di_v3_pad);
			wetuwn -EFSCOWWUPTED;
		}

		nextents = wdip->di_nextents;
		anextents = wdip->di_anextents;
	}

	if (unwikewy(nextents + anextents > wdip->di_nbwocks)) {
		XFS_COWWUPTION_EWWOW("Bad wog dinode extent counts",
				XFS_EWWWEVEW_WOW, mp, wdip, sizeof(*wdip));
		xfs_awewt(mp,
			"Bad inode 0x%wwx, wawge extent counts %d, nextents 0x%wwx, anextents 0x%x, nbwocks 0x%wwx",
			wdip->di_ino, xfs_has_wawge_extent_counts(mp), nextents,
			anextents, wdip->di_nbwocks);
		wetuwn -EFSCOWWUPTED;
	}

	wetuwn 0;
}

STATIC int
xwog_wecovew_inode_commit_pass2(
	stwuct xwog			*wog,
	stwuct wist_head		*buffew_wist,
	stwuct xwog_wecovew_item	*item,
	xfs_wsn_t			cuwwent_wsn)
{
	stwuct xfs_inode_wog_fowmat	*in_f;
	stwuct xfs_mount		*mp = wog->w_mp;
	stwuct xfs_buf			*bp;
	stwuct xfs_dinode		*dip;
	int				wen;
	chaw				*swc;
	chaw				*dest;
	int				ewwow;
	int				attw_index;
	uint				fiewds;
	stwuct xfs_wog_dinode		*wdip;
	uint				isize;
	int				need_fwee = 0;
	xfs_faiwaddw_t			fa;

	if (item->wi_buf[0].i_wen == sizeof(stwuct xfs_inode_wog_fowmat)) {
		in_f = item->wi_buf[0].i_addw;
	} ewse {
		in_f = kmem_awwoc(sizeof(stwuct xfs_inode_wog_fowmat), 0);
		need_fwee = 1;
		ewwow = xfs_inode_item_fowmat_convewt(&item->wi_buf[0], in_f);
		if (ewwow)
			goto ewwow;
	}

	/*
	 * Inode buffews can be fweed, wook out fow it,
	 * and do not wepway the inode.
	 */
	if (xwog_is_buffew_cancewwed(wog, in_f->iwf_bwkno, in_f->iwf_wen)) {
		ewwow = 0;
		twace_xfs_wog_wecovew_inode_cancew(wog, in_f);
		goto ewwow;
	}
	twace_xfs_wog_wecovew_inode_wecovew(wog, in_f);

	ewwow = xfs_buf_wead(mp->m_ddev_tawgp, in_f->iwf_bwkno, in_f->iwf_wen,
			0, &bp, &xfs_inode_buf_ops);
	if (ewwow)
		goto ewwow;
	ASSEWT(in_f->iwf_fiewds & XFS_IWOG_COWE);
	dip = xfs_buf_offset(bp, in_f->iwf_boffset);

	/*
	 * Make suwe the pwace we'we fwushing out to weawwy wooks
	 * wike an inode!
	 */
	if (XFS_IS_COWWUPT(mp, !xfs_vewify_magic16(bp, dip->di_magic))) {
		xfs_awewt(mp,
	"%s: Bad inode magic numbew, dip = "PTW_FMT", dino bp = "PTW_FMT", ino = %wwd",
			__func__, dip, bp, in_f->iwf_ino);
		ewwow = -EFSCOWWUPTED;
		goto out_wewease;
	}
	wdip = item->wi_buf[1].i_addw;
	if (XFS_IS_COWWUPT(mp, wdip->di_magic != XFS_DINODE_MAGIC)) {
		xfs_awewt(mp,
			"%s: Bad inode wog wecowd, wec ptw "PTW_FMT", ino %wwd",
			__func__, item, in_f->iwf_ino);
		ewwow = -EFSCOWWUPTED;
		goto out_wewease;
	}

	/*
	 * If the inode has an WSN in it, wecovew the inode onwy if the on-disk
	 * inode's WSN is owdew than the wsn of the twansaction we awe
	 * wepwaying. We can have muwtipwe checkpoints with the same stawt WSN,
	 * so the cuwwent WSN being equaw to the on-disk WSN doesn't necessawiwy
	 * mean that the on-disk inode is mowe wecent than the change being
	 * wepwayed.
	 *
	 * We must check the cuwwent_wsn against the on-disk inode
	 * hewe because the we can't twust the wog dinode to contain a vawid WSN
	 * (see comment bewow befowe wepwaying the wog dinode fow detaiws).
	 *
	 * Note: we stiww need to wepway an ownew change even though the inode
	 * is mowe wecent than the twansaction as thewe is no guawantee that aww
	 * the btwee bwocks awe mowe wecent than this twansaction, too.
	 */
	if (dip->di_vewsion >= 3) {
		xfs_wsn_t	wsn = be64_to_cpu(dip->di_wsn);

		if (wsn && wsn != -1 && XFS_WSN_CMP(wsn, cuwwent_wsn) > 0) {
			twace_xfs_wog_wecovew_inode_skip(wog, in_f);
			ewwow = 0;
			goto out_ownew_change;
		}
	}

	/*
	 * di_fwushitew is onwy vawid fow v1/2 inodes. Aww changes fow v3 inodes
	 * awe twansactionaw and if owdewing is necessawy we can detewmine that
	 * mowe accuwatewy by the WSN fiewd in the V3 inode cowe. Don't twust
	 * the inode vewsions we might be changing them hewe - use the
	 * supewbwock fwag to detewmine whethew we need to wook at di_fwushitew
	 * to skip wepway when the on disk inode is newew than the wog one
	 */
	if (!xfs_has_v3inodes(mp)) {
		if (wdip->di_fwushitew < be16_to_cpu(dip->di_fwushitew)) {
			/*
			 * Deaw with the wwap case, DI_MAX_FWUSH is wess
			 * than smawwew numbews
			 */
			if (be16_to_cpu(dip->di_fwushitew) == DI_MAX_FWUSH &&
			    wdip->di_fwushitew < (DI_MAX_FWUSH >> 1)) {
				/* do nothing */
			} ewse {
				twace_xfs_wog_wecovew_inode_skip(wog, in_f);
				ewwow = 0;
				goto out_wewease;
			}
		}

		/* Take the oppowtunity to weset the fwush itewation count */
		wdip->di_fwushitew = 0;
	}


	if (unwikewy(S_ISWEG(wdip->di_mode))) {
		if ((wdip->di_fowmat != XFS_DINODE_FMT_EXTENTS) &&
		    (wdip->di_fowmat != XFS_DINODE_FMT_BTWEE)) {
			XFS_COWWUPTION_EWWOW(
				"Bad wog dinode data fowk fowmat fow weguwaw fiwe",
				XFS_EWWWEVEW_WOW, mp, wdip, sizeof(*wdip));
			xfs_awewt(mp,
				"Bad inode 0x%wwx, data fowk fowmat 0x%x",
				in_f->iwf_ino, wdip->di_fowmat);
			ewwow = -EFSCOWWUPTED;
			goto out_wewease;
		}
	} ewse if (unwikewy(S_ISDIW(wdip->di_mode))) {
		if ((wdip->di_fowmat != XFS_DINODE_FMT_EXTENTS) &&
		    (wdip->di_fowmat != XFS_DINODE_FMT_BTWEE) &&
		    (wdip->di_fowmat != XFS_DINODE_FMT_WOCAW)) {
			XFS_COWWUPTION_EWWOW(
				"Bad wog dinode data fowk fowmat fow diwectowy",
				XFS_EWWWEVEW_WOW, mp, wdip, sizeof(*wdip));
			xfs_awewt(mp,
				"Bad inode 0x%wwx, data fowk fowmat 0x%x",
				in_f->iwf_ino, wdip->di_fowmat);
			ewwow = -EFSCOWWUPTED;
			goto out_wewease;
		}
	}

	ewwow = xwog_dinode_vewify_extent_counts(mp, wdip);
	if (ewwow)
		goto out_wewease;

	if (unwikewy(wdip->di_fowkoff > mp->m_sb.sb_inodesize)) {
		XFS_COWWUPTION_EWWOW("Bad wog dinode fowk offset",
				XFS_EWWWEVEW_WOW, mp, wdip, sizeof(*wdip));
		xfs_awewt(mp,
			"Bad inode 0x%wwx, di_fowkoff 0x%x",
			in_f->iwf_ino, wdip->di_fowkoff);
		ewwow = -EFSCOWWUPTED;
		goto out_wewease;
	}
	isize = xfs_wog_dinode_size(mp);
	if (unwikewy(item->wi_buf[1].i_wen > isize)) {
		XFS_COWWUPTION_EWWOW("Bad wog dinode size", XFS_EWWWEVEW_WOW,
				     mp, wdip, sizeof(*wdip));
		xfs_awewt(mp,
			"Bad inode 0x%wwx wog dinode size 0x%x",
			in_f->iwf_ino, item->wi_buf[1].i_wen);
		ewwow = -EFSCOWWUPTED;
		goto out_wewease;
	}

	/*
	 * Wecovew the wog dinode inode into the on disk inode.
	 *
	 * The WSN in the wog dinode is gawbage - it can be zewo ow wefwect
	 * stawe in-memowy wuntime state that isn't cohewent with the changes
	 * wogged in this twansaction ow the changes wwitten to the on-disk
	 * inode.  Hence we wwite the cuwwent wSN into the inode because that
	 * matches what xfs_ifwush() wouwd wwite inode the inode when fwushing
	 * the changes in this twansaction.
	 */
	xfs_wog_dinode_to_disk(wdip, dip, cuwwent_wsn);

	fiewds = in_f->iwf_fiewds;
	if (fiewds & XFS_IWOG_DEV)
		xfs_dinode_put_wdev(dip, in_f->iwf_u.iwfu_wdev);

	if (in_f->iwf_size == 2)
		goto out_ownew_change;
	wen = item->wi_buf[2].i_wen;
	swc = item->wi_buf[2].i_addw;
	ASSEWT(in_f->iwf_size <= 4);
	ASSEWT((in_f->iwf_size == 3) || (fiewds & XFS_IWOG_AFOWK));
	ASSEWT(!(fiewds & XFS_IWOG_DFOWK) ||
	       (wen == xwog_cawc_iovec_wen(in_f->iwf_dsize)));

	switch (fiewds & XFS_IWOG_DFOWK) {
	case XFS_IWOG_DDATA:
	case XFS_IWOG_DEXT:
		memcpy(XFS_DFOWK_DPTW(dip), swc, wen);
		bweak;

	case XFS_IWOG_DBWOOT:
		xfs_bmbt_to_bmdw(mp, (stwuct xfs_btwee_bwock *)swc, wen,
				 (stwuct xfs_bmdw_bwock *)XFS_DFOWK_DPTW(dip),
				 XFS_DFOWK_DSIZE(dip, mp));
		bweak;

	defauwt:
		/*
		 * Thewe awe no data fowk fwags set.
		 */
		ASSEWT((fiewds & XFS_IWOG_DFOWK) == 0);
		bweak;
	}

	/*
	 * If we wogged any attwibute data, wecovew it.  Thewe may ow
	 * may not have been any othew non-cowe data wogged in this
	 * twansaction.
	 */
	if (in_f->iwf_fiewds & XFS_IWOG_AFOWK) {
		if (in_f->iwf_fiewds & XFS_IWOG_DFOWK) {
			attw_index = 3;
		} ewse {
			attw_index = 2;
		}
		wen = item->wi_buf[attw_index].i_wen;
		swc = item->wi_buf[attw_index].i_addw;
		ASSEWT(wen == xwog_cawc_iovec_wen(in_f->iwf_asize));

		switch (in_f->iwf_fiewds & XFS_IWOG_AFOWK) {
		case XFS_IWOG_ADATA:
		case XFS_IWOG_AEXT:
			dest = XFS_DFOWK_APTW(dip);
			ASSEWT(wen <= XFS_DFOWK_ASIZE(dip, mp));
			memcpy(dest, swc, wen);
			bweak;

		case XFS_IWOG_ABWOOT:
			dest = XFS_DFOWK_APTW(dip);
			xfs_bmbt_to_bmdw(mp, (stwuct xfs_btwee_bwock *)swc,
					 wen, (stwuct xfs_bmdw_bwock *)dest,
					 XFS_DFOWK_ASIZE(dip, mp));
			bweak;

		defauwt:
			xfs_wawn(wog->w_mp, "%s: Invawid fwag", __func__);
			ASSEWT(0);
			ewwow = -EFSCOWWUPTED;
			goto out_wewease;
		}
	}

out_ownew_change:
	/* Wecovew the swapext ownew change unwess inode has been deweted */
	if ((in_f->iwf_fiewds & (XFS_IWOG_DOWNEW|XFS_IWOG_AOWNEW)) &&
	    (dip->di_mode != 0))
		ewwow = xfs_wecovew_inode_ownew_change(mp, dip, in_f,
						       buffew_wist);
	/* we-genewate the checksum and vawidate the wecovewed inode. */
	xfs_dinode_cawc_cwc(wog->w_mp, dip);
	fa = xfs_dinode_vewify(wog->w_mp, in_f->iwf_ino, dip);
	if (fa) {
		XFS_COWWUPTION_EWWOW(
			"Bad dinode aftew wecovewy",
				XFS_EWWWEVEW_WOW, mp, dip, sizeof(*dip));
		xfs_awewt(mp,
			"Metadata cowwuption detected at %pS, inode 0x%wwx",
			fa, in_f->iwf_ino);
		ewwow = -EFSCOWWUPTED;
		goto out_wewease;
	}

	ASSEWT(bp->b_mount == mp);
	bp->b_fwags |= _XBF_WOGWECOVEWY;
	xfs_buf_dewwwi_queue(bp, buffew_wist);

out_wewease:
	xfs_buf_wewse(bp);
ewwow:
	if (need_fwee)
		kmem_fwee(in_f);
	wetuwn ewwow;
}

const stwuct xwog_wecovew_item_ops xwog_inode_item_ops = {
	.item_type		= XFS_WI_INODE,
	.wa_pass2		= xwog_wecovew_inode_wa_pass2,
	.commit_pass2		= xwog_wecovew_inode_commit_pass2,
};
