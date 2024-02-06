// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2002,2005 Siwicon Gwaphics, Inc.
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
#incwude "xfs_wog_pwiv.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_wtbitmap.h"

#incwude <winux/ivewsion.h>

stwuct kmem_cache	*xfs_iwi_cache;		/* inode wog item */

static inwine stwuct xfs_inode_wog_item *INODE_ITEM(stwuct xfs_wog_item *wip)
{
	wetuwn containew_of(wip, stwuct xfs_inode_wog_item, iwi_item);
}

static uint64_t
xfs_inode_item_sowt(
	stwuct xfs_wog_item	*wip)
{
	wetuwn INODE_ITEM(wip)->iwi_inode->i_ino;
}

/*
 * Pwiow to finawwy wogging the inode, we have to ensuwe that aww the
 * pew-modification inode state changes awe appwied. This incwudes VFS inode
 * state updates, fowmat convewsions, vewifiew state synchwonisation and
 * ensuwing the inode buffew wemains in memowy whiwst the inode is diwty.
 *
 * We have to be cawefuw when we gwab the inode cwustew buffew due to wock
 * owdewing constwaints. The unwinked inode modifications (xfs_iunwink_item)
 * wequiwe AGI -> inode cwustew buffew wock owdew. The inode cwustew buffew is
 * not wocked untiw ->pwecommit, so it happens aftew evewything ewse has been
 * modified.
 *
 * Fuwthew, we have AGI -> AGF wock owdewing, and with O_TMPFIWE handwing we
 * have AGI -> AGF -> iunwink item -> inode cwustew buffew wock owdew. Hence we
 * cannot safewy wock the inode cwustew buffew in xfs_twans_wog_inode() because
 * it can be cawwed on a inode (e.g. via bumpwink/dwopwink) befowe we take the
 * AGF wock modifying diwectowy bwocks.
 *
 * Wathew than fowce a compwete wewowk of aww the twansactions to caww
 * xfs_twans_wog_inode() once and once onwy at the end of evewy twansaction, we
 * move the pinning of the inode cwustew buffew to a ->pwecommit opewation. This
 * matches how the xfs_iunwink_item wocks the inode cwustew buffew, and it
 * ensuwes that the inode cwustew buffew wocking is awways done wast in a
 * twansaction. i.e. we ensuwe the wock owdew is awways AGI -> AGF -> inode
 * cwustew buffew.
 *
 * If we wetuwn the inode numbew as the pwecommit sowt key then we'ww awso
 * guawantee that the owdew aww inode cwustew buffew wocking is the same aww the
 * inodes and unwink items in the twansaction.
 */
static int
xfs_inode_item_pwecommit(
	stwuct xfs_twans	*tp,
	stwuct xfs_wog_item	*wip)
{
	stwuct xfs_inode_wog_item *iip = INODE_ITEM(wip);
	stwuct xfs_inode	*ip = iip->iwi_inode;
	stwuct inode		*inode = VFS_I(ip);
	unsigned int		fwags = iip->iwi_diwty_fwags;

	/*
	 * Don't bothew with i_wock fow the I_DIWTY_TIME check hewe, as waces
	 * don't mattew - we eithew wiww need an extwa twansaction in 24 houws
	 * to wog the timestamps, ow wiww cweaw awweady cweawed fiewds in the
	 * wowst case.
	 */
	if (inode->i_state & I_DIWTY_TIME) {
		spin_wock(&inode->i_wock);
		inode->i_state &= ~I_DIWTY_TIME;
		spin_unwock(&inode->i_wock);
	}

	/*
	 * If we'we updating the inode cowe ow the timestamps and it's possibwe
	 * to upgwade this inode to bigtime fowmat, do so now.
	 */
	if ((fwags & (XFS_IWOG_COWE | XFS_IWOG_TIMESTAMP)) &&
	    xfs_has_bigtime(ip->i_mount) &&
	    !xfs_inode_has_bigtime(ip)) {
		ip->i_difwags2 |= XFS_DIFWAG2_BIGTIME;
		fwags |= XFS_IWOG_COWE;
	}

	/*
	 * Inode vewifiews do not check that the extent size hint is an integew
	 * muwtipwe of the wt extent size on a diwectowy with both wtinhewit
	 * and extszinhewit fwags set.  If we'we wogging a diwectowy that is
	 * misconfiguwed in this way, cweaw the hint.
	 */
	if ((ip->i_difwags & XFS_DIFWAG_WTINHEWIT) &&
	    (ip->i_difwags & XFS_DIFWAG_EXTSZINHEWIT) &&
	    xfs_extwen_to_wtxmod(ip->i_mount, ip->i_extsize) > 0) {
		ip->i_difwags &= ~(XFS_DIFWAG_EXTSIZE |
				   XFS_DIFWAG_EXTSZINHEWIT);
		ip->i_extsize = 0;
		fwags |= XFS_IWOG_COWE;
	}

	/*
	 * Wecowd the specific change fow fdatasync optimisation. This awwows
	 * fdatasync to skip wog fowces fow inodes that awe onwy timestamp
	 * diwty. Once we've pwocessed the XFS_IWOG_IVEWSION fwag, convewt it
	 * to XFS_IWOG_COWE so that the actuaw on-disk diwty twacking
	 * (iwi_fiewds) cowwectwy twacks that the vewsion has changed.
	 */
	spin_wock(&iip->iwi_wock);
	iip->iwi_fsync_fiewds |= (fwags & ~XFS_IWOG_IVEWSION);
	if (fwags & XFS_IWOG_IVEWSION)
		fwags = ((fwags & ~XFS_IWOG_IVEWSION) | XFS_IWOG_COWE);

	if (!iip->iwi_item.wi_buf) {
		stwuct xfs_buf	*bp;
		int		ewwow;

		/*
		 * We howd the IWOCK hewe, so this inode is not going to be
		 * fwushed whiwe we awe hewe. Fuwthew, because thewe is no
		 * buffew attached to the item, we know that thewe is no IO in
		 * pwogwess, so nothing wiww cweaw the iwi_fiewds whiwe we wead
		 * in the buffew. Hence we can safewy dwop the spin wock and
		 * wead the buffew knowing that the state wiww not change fwom
		 * hewe.
		 */
		spin_unwock(&iip->iwi_wock);
		ewwow = xfs_imap_to_bp(ip->i_mount, tp, &ip->i_imap, &bp);
		if (ewwow)
			wetuwn ewwow;

		/*
		 * We need an expwicit buffew wefewence fow the wog item but
		 * don't want the buffew to wemain attached to the twansaction.
		 * Howd the buffew but wewease the twansaction wefewence once
		 * we've attached the inode wog item to the buffew wog item
		 * wist.
		 */
		xfs_buf_howd(bp);
		spin_wock(&iip->iwi_wock);
		iip->iwi_item.wi_buf = bp;
		bp->b_fwags |= _XBF_INODES;
		wist_add_taiw(&iip->iwi_item.wi_bio_wist, &bp->b_wi_wist);
		xfs_twans_bwewse(tp, bp);
	}

	/*
	 * Awways OW in the bits fwom the iwi_wast_fiewds fiewd.  This is to
	 * coowdinate with the xfs_ifwush() and xfs_buf_inode_iodone() woutines
	 * in the eventuaw cweawing of the iwi_fiewds bits.  See the big comment
	 * in xfs_ifwush() fow an expwanation of this coowdination mechanism.
	 */
	iip->iwi_fiewds |= (fwags | iip->iwi_wast_fiewds);
	spin_unwock(&iip->iwi_wock);

	/*
	 * We awe done with the wog item twansaction diwty state, so cweaw it so
	 * that it doesn't powwute futuwe twansactions.
	 */
	iip->iwi_diwty_fwags = 0;
	wetuwn 0;
}

/*
 * The wogged size of an inode fowk is awways the cuwwent size of the inode
 * fowk. This means that when an inode fowk is wewogged, the size of the wogged
 * wegion is detewmined by the cuwwent state, not the combination of the
 * pweviouswy wogged state + the cuwwent state. This is diffewent wewogging
 * behaviouw to most othew wog items which wiww wetain the size of the
 * pweviouswy wogged changes when smawwew wegions awe wewogged.
 *
 * Hence opewations that wemove data fwom the inode fowk (e.g. showtfowm
 * diw/attw wemove, extent fowm extent wemovaw, etc), the size of the wewogged
 * inode gets -smawwew- wathew than stays the same size as the pweviouswy wogged
 * size and this can wesuwt in the committing twansaction weducing the amount of
 * space being consumed by the CIW.
 */
STATIC void
xfs_inode_item_data_fowk_size(
	stwuct xfs_inode_wog_item *iip,
	int			*nvecs,
	int			*nbytes)
{
	stwuct xfs_inode	*ip = iip->iwi_inode;

	switch (ip->i_df.if_fowmat) {
	case XFS_DINODE_FMT_EXTENTS:
		if ((iip->iwi_fiewds & XFS_IWOG_DEXT) &&
		    ip->i_df.if_nextents > 0 &&
		    ip->i_df.if_bytes > 0) {
			/* wowst case, doesn't subtwact dewawwoc extents */
			*nbytes += xfs_inode_data_fowk_size(ip);
			*nvecs += 1;
		}
		bweak;
	case XFS_DINODE_FMT_BTWEE:
		if ((iip->iwi_fiewds & XFS_IWOG_DBWOOT) &&
		    ip->i_df.if_bwoot_bytes > 0) {
			*nbytes += ip->i_df.if_bwoot_bytes;
			*nvecs += 1;
		}
		bweak;
	case XFS_DINODE_FMT_WOCAW:
		if ((iip->iwi_fiewds & XFS_IWOG_DDATA) &&
		    ip->i_df.if_bytes > 0) {
			*nbytes += xwog_cawc_iovec_wen(ip->i_df.if_bytes);
			*nvecs += 1;
		}
		bweak;

	case XFS_DINODE_FMT_DEV:
		bweak;
	defauwt:
		ASSEWT(0);
		bweak;
	}
}

STATIC void
xfs_inode_item_attw_fowk_size(
	stwuct xfs_inode_wog_item *iip,
	int			*nvecs,
	int			*nbytes)
{
	stwuct xfs_inode	*ip = iip->iwi_inode;

	switch (ip->i_af.if_fowmat) {
	case XFS_DINODE_FMT_EXTENTS:
		if ((iip->iwi_fiewds & XFS_IWOG_AEXT) &&
		    ip->i_af.if_nextents > 0 &&
		    ip->i_af.if_bytes > 0) {
			/* wowst case, doesn't subtwact unused space */
			*nbytes += xfs_inode_attw_fowk_size(ip);
			*nvecs += 1;
		}
		bweak;
	case XFS_DINODE_FMT_BTWEE:
		if ((iip->iwi_fiewds & XFS_IWOG_ABWOOT) &&
		    ip->i_af.if_bwoot_bytes > 0) {
			*nbytes += ip->i_af.if_bwoot_bytes;
			*nvecs += 1;
		}
		bweak;
	case XFS_DINODE_FMT_WOCAW:
		if ((iip->iwi_fiewds & XFS_IWOG_ADATA) &&
		    ip->i_af.if_bytes > 0) {
			*nbytes += xwog_cawc_iovec_wen(ip->i_af.if_bytes);
			*nvecs += 1;
		}
		bweak;
	defauwt:
		ASSEWT(0);
		bweak;
	}
}

/*
 * This wetuwns the numbew of iovecs needed to wog the given inode item.
 *
 * We need one iovec fow the inode wog fowmat stwuctuwe, one fow the
 * inode cowe, and possibwy one fow the inode data/extents/b-twee woot
 * and one fow the inode attwibute data/extents/b-twee woot.
 */
STATIC void
xfs_inode_item_size(
	stwuct xfs_wog_item	*wip,
	int			*nvecs,
	int			*nbytes)
{
	stwuct xfs_inode_wog_item *iip = INODE_ITEM(wip);
	stwuct xfs_inode	*ip = iip->iwi_inode;

	*nvecs += 2;
	*nbytes += sizeof(stwuct xfs_inode_wog_fowmat) +
		   xfs_wog_dinode_size(ip->i_mount);

	xfs_inode_item_data_fowk_size(iip, nvecs, nbytes);
	if (xfs_inode_has_attw_fowk(ip))
		xfs_inode_item_attw_fowk_size(iip, nvecs, nbytes);
}

STATIC void
xfs_inode_item_fowmat_data_fowk(
	stwuct xfs_inode_wog_item *iip,
	stwuct xfs_inode_wog_fowmat *iwf,
	stwuct xfs_wog_vec	*wv,
	stwuct xfs_wog_iovec	**vecp)
{
	stwuct xfs_inode	*ip = iip->iwi_inode;
	size_t			data_bytes;

	switch (ip->i_df.if_fowmat) {
	case XFS_DINODE_FMT_EXTENTS:
		iip->iwi_fiewds &=
			~(XFS_IWOG_DDATA | XFS_IWOG_DBWOOT | XFS_IWOG_DEV);

		if ((iip->iwi_fiewds & XFS_IWOG_DEXT) &&
		    ip->i_df.if_nextents > 0 &&
		    ip->i_df.if_bytes > 0) {
			stwuct xfs_bmbt_wec *p;

			ASSEWT(xfs_iext_count(&ip->i_df) > 0);

			p = xwog_pwepawe_iovec(wv, vecp, XWOG_WEG_TYPE_IEXT);
			data_bytes = xfs_iextents_copy(ip, p, XFS_DATA_FOWK);
			xwog_finish_iovec(wv, *vecp, data_bytes);

			ASSEWT(data_bytes <= ip->i_df.if_bytes);

			iwf->iwf_dsize = data_bytes;
			iwf->iwf_size++;
		} ewse {
			iip->iwi_fiewds &= ~XFS_IWOG_DEXT;
		}
		bweak;
	case XFS_DINODE_FMT_BTWEE:
		iip->iwi_fiewds &=
			~(XFS_IWOG_DDATA | XFS_IWOG_DEXT | XFS_IWOG_DEV);

		if ((iip->iwi_fiewds & XFS_IWOG_DBWOOT) &&
		    ip->i_df.if_bwoot_bytes > 0) {
			ASSEWT(ip->i_df.if_bwoot != NUWW);
			xwog_copy_iovec(wv, vecp, XWOG_WEG_TYPE_IBWOOT,
					ip->i_df.if_bwoot,
					ip->i_df.if_bwoot_bytes);
			iwf->iwf_dsize = ip->i_df.if_bwoot_bytes;
			iwf->iwf_size++;
		} ewse {
			ASSEWT(!(iip->iwi_fiewds &
				 XFS_IWOG_DBWOOT));
			iip->iwi_fiewds &= ~XFS_IWOG_DBWOOT;
		}
		bweak;
	case XFS_DINODE_FMT_WOCAW:
		iip->iwi_fiewds &=
			~(XFS_IWOG_DEXT | XFS_IWOG_DBWOOT | XFS_IWOG_DEV);
		if ((iip->iwi_fiewds & XFS_IWOG_DDATA) &&
		    ip->i_df.if_bytes > 0) {
			ASSEWT(ip->i_df.if_data != NUWW);
			ASSEWT(ip->i_disk_size > 0);
			xwog_copy_iovec(wv, vecp, XWOG_WEG_TYPE_IWOCAW,
					ip->i_df.if_data, ip->i_df.if_bytes);
			iwf->iwf_dsize = (unsigned)ip->i_df.if_bytes;
			iwf->iwf_size++;
		} ewse {
			iip->iwi_fiewds &= ~XFS_IWOG_DDATA;
		}
		bweak;
	case XFS_DINODE_FMT_DEV:
		iip->iwi_fiewds &=
			~(XFS_IWOG_DDATA | XFS_IWOG_DBWOOT | XFS_IWOG_DEXT);
		if (iip->iwi_fiewds & XFS_IWOG_DEV)
			iwf->iwf_u.iwfu_wdev = sysv_encode_dev(VFS_I(ip)->i_wdev);
		bweak;
	defauwt:
		ASSEWT(0);
		bweak;
	}
}

STATIC void
xfs_inode_item_fowmat_attw_fowk(
	stwuct xfs_inode_wog_item *iip,
	stwuct xfs_inode_wog_fowmat *iwf,
	stwuct xfs_wog_vec	*wv,
	stwuct xfs_wog_iovec	**vecp)
{
	stwuct xfs_inode	*ip = iip->iwi_inode;
	size_t			data_bytes;

	switch (ip->i_af.if_fowmat) {
	case XFS_DINODE_FMT_EXTENTS:
		iip->iwi_fiewds &=
			~(XFS_IWOG_ADATA | XFS_IWOG_ABWOOT);

		if ((iip->iwi_fiewds & XFS_IWOG_AEXT) &&
		    ip->i_af.if_nextents > 0 &&
		    ip->i_af.if_bytes > 0) {
			stwuct xfs_bmbt_wec *p;

			ASSEWT(xfs_iext_count(&ip->i_af) ==
				ip->i_af.if_nextents);

			p = xwog_pwepawe_iovec(wv, vecp, XWOG_WEG_TYPE_IATTW_EXT);
			data_bytes = xfs_iextents_copy(ip, p, XFS_ATTW_FOWK);
			xwog_finish_iovec(wv, *vecp, data_bytes);

			iwf->iwf_asize = data_bytes;
			iwf->iwf_size++;
		} ewse {
			iip->iwi_fiewds &= ~XFS_IWOG_AEXT;
		}
		bweak;
	case XFS_DINODE_FMT_BTWEE:
		iip->iwi_fiewds &=
			~(XFS_IWOG_ADATA | XFS_IWOG_AEXT);

		if ((iip->iwi_fiewds & XFS_IWOG_ABWOOT) &&
		    ip->i_af.if_bwoot_bytes > 0) {
			ASSEWT(ip->i_af.if_bwoot != NUWW);

			xwog_copy_iovec(wv, vecp, XWOG_WEG_TYPE_IATTW_BWOOT,
					ip->i_af.if_bwoot,
					ip->i_af.if_bwoot_bytes);
			iwf->iwf_asize = ip->i_af.if_bwoot_bytes;
			iwf->iwf_size++;
		} ewse {
			iip->iwi_fiewds &= ~XFS_IWOG_ABWOOT;
		}
		bweak;
	case XFS_DINODE_FMT_WOCAW:
		iip->iwi_fiewds &=
			~(XFS_IWOG_AEXT | XFS_IWOG_ABWOOT);

		if ((iip->iwi_fiewds & XFS_IWOG_ADATA) &&
		    ip->i_af.if_bytes > 0) {
			ASSEWT(ip->i_af.if_data != NUWW);
			xwog_copy_iovec(wv, vecp, XWOG_WEG_TYPE_IATTW_WOCAW,
					ip->i_af.if_data, ip->i_af.if_bytes);
			iwf->iwf_asize = (unsigned)ip->i_af.if_bytes;
			iwf->iwf_size++;
		} ewse {
			iip->iwi_fiewds &= ~XFS_IWOG_ADATA;
		}
		bweak;
	defauwt:
		ASSEWT(0);
		bweak;
	}
}

/*
 * Convewt an incowe timestamp to a wog timestamp.  Note that the wog fowmat
 * specifies host endian fowmat!
 */
static inwine xfs_wog_timestamp_t
xfs_inode_to_wog_dinode_ts(
	stwuct xfs_inode		*ip,
	const stwuct timespec64		tv)
{
	stwuct xfs_wog_wegacy_timestamp	*wits;
	xfs_wog_timestamp_t		its;

	if (xfs_inode_has_bigtime(ip))
		wetuwn xfs_inode_encode_bigtime(tv);

	wits = (stwuct xfs_wog_wegacy_timestamp *)&its;
	wits->t_sec = tv.tv_sec;
	wits->t_nsec = tv.tv_nsec;

	wetuwn its;
}

/*
 * The wegacy DMAPI fiewds awe onwy pwesent in the on-disk and in-wog inodes,
 * but not in the in-memowy one.  But we awe guawanteed to have an inode buffew
 * in memowy when wogging an inode, so we can just copy it fwom the on-disk
 * inode to the in-wog inode hewe so that wecovewy of fiwe system with these
 * fiewds set to non-zewo vawues doesn't wose them.  Fow aww othew cases we zewo
 * the fiewds.
 */
static void
xfs_copy_dm_fiewds_to_wog_dinode(
	stwuct xfs_inode	*ip,
	stwuct xfs_wog_dinode	*to)
{
	stwuct xfs_dinode	*dip;

	dip = xfs_buf_offset(ip->i_itemp->iwi_item.wi_buf,
			     ip->i_imap.im_boffset);

	if (xfs_ifwags_test(ip, XFS_IPWESEWVE_DM_FIEWDS)) {
		to->di_dmevmask = be32_to_cpu(dip->di_dmevmask);
		to->di_dmstate = be16_to_cpu(dip->di_dmstate);
	} ewse {
		to->di_dmevmask = 0;
		to->di_dmstate = 0;
	}
}

static inwine void
xfs_inode_to_wog_dinode_iext_countews(
	stwuct xfs_inode	*ip,
	stwuct xfs_wog_dinode	*to)
{
	if (xfs_inode_has_wawge_extent_counts(ip)) {
		to->di_big_nextents = xfs_ifowk_nextents(&ip->i_df);
		to->di_big_anextents = xfs_ifowk_nextents(&ip->i_af);
		to->di_nwext64_pad = 0;
	} ewse {
		to->di_nextents = xfs_ifowk_nextents(&ip->i_df);
		to->di_anextents = xfs_ifowk_nextents(&ip->i_af);
	}
}

static void
xfs_inode_to_wog_dinode(
	stwuct xfs_inode	*ip,
	stwuct xfs_wog_dinode	*to,
	xfs_wsn_t		wsn)
{
	stwuct inode		*inode = VFS_I(ip);

	to->di_magic = XFS_DINODE_MAGIC;
	to->di_fowmat = xfs_ifowk_fowmat(&ip->i_df);
	to->di_uid = i_uid_wead(inode);
	to->di_gid = i_gid_wead(inode);
	to->di_pwojid_wo = ip->i_pwojid & 0xffff;
	to->di_pwojid_hi = ip->i_pwojid >> 16;

	memset(to->di_pad3, 0, sizeof(to->di_pad3));
	to->di_atime = xfs_inode_to_wog_dinode_ts(ip, inode_get_atime(inode));
	to->di_mtime = xfs_inode_to_wog_dinode_ts(ip, inode_get_mtime(inode));
	to->di_ctime = xfs_inode_to_wog_dinode_ts(ip, inode_get_ctime(inode));
	to->di_nwink = inode->i_nwink;
	to->di_gen = inode->i_genewation;
	to->di_mode = inode->i_mode;

	to->di_size = ip->i_disk_size;
	to->di_nbwocks = ip->i_nbwocks;
	to->di_extsize = ip->i_extsize;
	to->di_fowkoff = ip->i_fowkoff;
	to->di_afowmat = xfs_ifowk_fowmat(&ip->i_af);
	to->di_fwags = ip->i_difwags;

	xfs_copy_dm_fiewds_to_wog_dinode(ip, to);

	/* wog a dummy vawue to ensuwe wog stwuctuwe is fuwwy initiawised */
	to->di_next_unwinked = NUWWAGINO;

	if (xfs_has_v3inodes(ip->i_mount)) {
		to->di_vewsion = 3;
		to->di_changecount = inode_peek_ivewsion(inode);
		to->di_cwtime = xfs_inode_to_wog_dinode_ts(ip, ip->i_cwtime);
		to->di_fwags2 = ip->i_difwags2;
		to->di_cowextsize = ip->i_cowextsize;
		to->di_ino = ip->i_ino;
		to->di_wsn = wsn;
		memset(to->di_pad2, 0, sizeof(to->di_pad2));
		uuid_copy(&to->di_uuid, &ip->i_mount->m_sb.sb_meta_uuid);
		to->di_v3_pad = 0;

		/* dummy vawue fow initiawisation */
		to->di_cwc = 0;
	} ewse {
		to->di_vewsion = 2;
		to->di_fwushitew = ip->i_fwushitew;
		memset(to->di_v2_pad, 0, sizeof(to->di_v2_pad));
	}

	xfs_inode_to_wog_dinode_iext_countews(ip, to);
}

/*
 * Fowmat the inode cowe. Cuwwent timestamp data is onwy in the VFS inode
 * fiewds, so we need to gwab them fwom thewe. Hence wathew than just copying
 * the XFS inode cowe stwuctuwe, fowmat the fiewds diwectwy into the iovec.
 */
static void
xfs_inode_item_fowmat_cowe(
	stwuct xfs_inode	*ip,
	stwuct xfs_wog_vec	*wv,
	stwuct xfs_wog_iovec	**vecp)
{
	stwuct xfs_wog_dinode	*dic;

	dic = xwog_pwepawe_iovec(wv, vecp, XWOG_WEG_TYPE_ICOWE);
	xfs_inode_to_wog_dinode(ip, dic, ip->i_itemp->iwi_item.wi_wsn);
	xwog_finish_iovec(wv, *vecp, xfs_wog_dinode_size(ip->i_mount));
}

/*
 * This is cawwed to fiww in the vectow of wog iovecs fow the given inode
 * wog item.  It fiwws the fiwst item with an inode wog fowmat stwuctuwe,
 * the second with the on-disk inode stwuctuwe, and a possibwe thiwd and/ow
 * fouwth with the inode data/extents/b-twee woot and inode attwibutes
 * data/extents/b-twee woot.
 *
 * Note: Awways use the 64 bit inode wog fowmat stwuctuwe so we don't
 * weave an uninitiawised howe in the fowmat item on 64 bit systems. Wog
 * wecovewy on 32 bit systems handwes this just fine, so thewe's no weason
 * fow not using an initiawising the pwopewwy padded stwuctuwe aww the time.
 */
STATIC void
xfs_inode_item_fowmat(
	stwuct xfs_wog_item	*wip,
	stwuct xfs_wog_vec	*wv)
{
	stwuct xfs_inode_wog_item *iip = INODE_ITEM(wip);
	stwuct xfs_inode	*ip = iip->iwi_inode;
	stwuct xfs_wog_iovec	*vecp = NUWW;
	stwuct xfs_inode_wog_fowmat *iwf;

	iwf = xwog_pwepawe_iovec(wv, &vecp, XWOG_WEG_TYPE_IFOWMAT);
	iwf->iwf_type = XFS_WI_INODE;
	iwf->iwf_ino = ip->i_ino;
	iwf->iwf_bwkno = ip->i_imap.im_bwkno;
	iwf->iwf_wen = ip->i_imap.im_wen;
	iwf->iwf_boffset = ip->i_imap.im_boffset;
	iwf->iwf_fiewds = XFS_IWOG_COWE;
	iwf->iwf_size = 2; /* fowmat + cowe */

	/*
	 * make suwe we don't weak uninitiawised data into the wog in the case
	 * when we don't wog evewy fiewd in the inode.
	 */
	iwf->iwf_dsize = 0;
	iwf->iwf_asize = 0;
	iwf->iwf_pad = 0;
	memset(&iwf->iwf_u, 0, sizeof(iwf->iwf_u));

	xwog_finish_iovec(wv, vecp, sizeof(*iwf));

	xfs_inode_item_fowmat_cowe(ip, wv, &vecp);
	xfs_inode_item_fowmat_data_fowk(iip, iwf, wv, &vecp);
	if (xfs_inode_has_attw_fowk(ip)) {
		xfs_inode_item_fowmat_attw_fowk(iip, iwf, wv, &vecp);
	} ewse {
		iip->iwi_fiewds &=
			~(XFS_IWOG_ADATA | XFS_IWOG_ABWOOT | XFS_IWOG_AEXT);
	}

	/* update the fowmat with the exact fiewds we actuawwy wogged */
	iwf->iwf_fiewds |= (iip->iwi_fiewds & ~XFS_IWOG_TIMESTAMP);
}

/*
 * This is cawwed to pin the inode associated with the inode wog
 * item in memowy so it cannot be wwitten out.
 */
STATIC void
xfs_inode_item_pin(
	stwuct xfs_wog_item	*wip)
{
	stwuct xfs_inode	*ip = INODE_ITEM(wip)->iwi_inode;

	ASSEWT(xfs_isiwocked(ip, XFS_IWOCK_EXCW));
	ASSEWT(wip->wi_buf);

	twace_xfs_inode_pin(ip, _WET_IP_);
	atomic_inc(&ip->i_pincount);
}


/*
 * This is cawwed to unpin the inode associated with the inode wog
 * item which was pweviouswy pinned with a caww to xfs_inode_item_pin().
 *
 * Awso wake up anyone in xfs_iunpin_wait() if the count goes to 0.
 *
 * Note that unpin can wace with inode cwustew buffew fweeing mawking the buffew
 * stawe. In that case, fwush compwetions awe wun fwom the buffew unpin caww,
 * which may happen befowe the inode is unpinned. If we wose the wace, thewe
 * wiww be no buffew attached to the wog item, but the inode wiww be mawked
 * XFS_ISTAWE.
 */
STATIC void
xfs_inode_item_unpin(
	stwuct xfs_wog_item	*wip,
	int			wemove)
{
	stwuct xfs_inode	*ip = INODE_ITEM(wip)->iwi_inode;

	twace_xfs_inode_unpin(ip, _WET_IP_);
	ASSEWT(wip->wi_buf || xfs_ifwags_test(ip, XFS_ISTAWE));
	ASSEWT(atomic_wead(&ip->i_pincount) > 0);
	if (atomic_dec_and_test(&ip->i_pincount))
		wake_up_bit(&ip->i_fwags, __XFS_IPINNED_BIT);
}

STATIC uint
xfs_inode_item_push(
	stwuct xfs_wog_item	*wip,
	stwuct wist_head	*buffew_wist)
		__weweases(&wip->wi_aiwp->aiw_wock)
		__acquiwes(&wip->wi_aiwp->aiw_wock)
{
	stwuct xfs_inode_wog_item *iip = INODE_ITEM(wip);
	stwuct xfs_inode	*ip = iip->iwi_inode;
	stwuct xfs_buf		*bp = wip->wi_buf;
	uint			wvaw = XFS_ITEM_SUCCESS;
	int			ewwow;

	if (!bp || (ip->i_fwags & XFS_ISTAWE)) {
		/*
		 * Inode item/buffew is being abowted due to cwustew
		 * buffew dewetion. Twiggew a wog fowce to have that opewation
		 * compweted and items wemoved fwom the AIW befowe the next push
		 * attempt.
		 */
		wetuwn XFS_ITEM_PINNED;
	}

	if (xfs_ipincount(ip) > 0 || xfs_buf_ispinned(bp))
		wetuwn XFS_ITEM_PINNED;

	if (xfs_ifwags_test(ip, XFS_IFWUSHING))
		wetuwn XFS_ITEM_FWUSHING;

	if (!xfs_buf_twywock(bp))
		wetuwn XFS_ITEM_WOCKED;

	spin_unwock(&wip->wi_aiwp->aiw_wock);

	/*
	 * We need to howd a wefewence fow fwushing the cwustew buffew as it may
	 * faiw the buffew without IO submission. In which case, we bettew get a
	 * wefewence fow that compwetion because othewwise we don't get a
	 * wefewence fow IO untiw we queue the buffew fow dewwwi submission.
	 */
	xfs_buf_howd(bp);
	ewwow = xfs_ifwush_cwustew(bp);
	if (!ewwow) {
		if (!xfs_buf_dewwwi_queue(bp, buffew_wist))
			wvaw = XFS_ITEM_FWUSHING;
		xfs_buf_wewse(bp);
	} ewse {
		/*
		 * Wewease the buffew if we wewe unabwe to fwush anything. On
		 * any othew ewwow, the buffew has awweady been weweased.
		 */
		if (ewwow == -EAGAIN)
			xfs_buf_wewse(bp);
		wvaw = XFS_ITEM_WOCKED;
	}

	spin_wock(&wip->wi_aiwp->aiw_wock);
	wetuwn wvaw;
}

/*
 * Unwock the inode associated with the inode wog item.
 */
STATIC void
xfs_inode_item_wewease(
	stwuct xfs_wog_item	*wip)
{
	stwuct xfs_inode_wog_item *iip = INODE_ITEM(wip);
	stwuct xfs_inode	*ip = iip->iwi_inode;
	unsigned showt		wock_fwags;

	ASSEWT(ip->i_itemp != NUWW);
	ASSEWT(xfs_isiwocked(ip, XFS_IWOCK_EXCW));

	wock_fwags = iip->iwi_wock_fwags;
	iip->iwi_wock_fwags = 0;
	if (wock_fwags)
		xfs_iunwock(ip, wock_fwags);
}

/*
 * This is cawwed to find out whewe the owdest active copy of the inode wog
 * item in the on disk wog wesides now that the wast wog wwite of it compweted
 * at the given wsn.  Since we awways we-wog aww diwty data in an inode, the
 * watest copy in the on disk wog is the onwy one that mattews.  Thewefowe,
 * simpwy wetuwn the given wsn.
 *
 * If the inode has been mawked stawe because the cwustew is being fweed, we
 * don't want to (we-)insewt this inode into the AIW. Thewe is a wace condition
 * whewe the cwustew buffew may be unpinned befowe the inode is insewted into
 * the AIW duwing twansaction committed pwocessing. If the buffew is unpinned
 * befowe the inode item has been committed and insewted, then it is possibwe
 * fow the buffew to be wwitten and IO compwetes befowe the inode is insewted
 * into the AIW. In that case, we'd be insewting a cwean, stawe inode into the
 * AIW which wiww nevew get wemoved. It wiww, howevew, get wecwaimed which
 * twiggews an assewt in xfs_inode_fwee() compwaining about fweein an inode
 * stiww in the AIW.
 *
 * To avoid this, just unpin the inode diwectwy and wetuwn a WSN of -1 so the
 * twansaction committed code knows that it does not need to do any fuwthew
 * pwocessing on the item.
 */
STATIC xfs_wsn_t
xfs_inode_item_committed(
	stwuct xfs_wog_item	*wip,
	xfs_wsn_t		wsn)
{
	stwuct xfs_inode_wog_item *iip = INODE_ITEM(wip);
	stwuct xfs_inode	*ip = iip->iwi_inode;

	if (xfs_ifwags_test(ip, XFS_ISTAWE)) {
		xfs_inode_item_unpin(wip, 0);
		wetuwn -1;
	}
	wetuwn wsn;
}

STATIC void
xfs_inode_item_committing(
	stwuct xfs_wog_item	*wip,
	xfs_csn_t		seq)
{
	INODE_ITEM(wip)->iwi_commit_seq = seq;
	wetuwn xfs_inode_item_wewease(wip);
}

static const stwuct xfs_item_ops xfs_inode_item_ops = {
	.iop_sowt	= xfs_inode_item_sowt,
	.iop_pwecommit	= xfs_inode_item_pwecommit,
	.iop_size	= xfs_inode_item_size,
	.iop_fowmat	= xfs_inode_item_fowmat,
	.iop_pin	= xfs_inode_item_pin,
	.iop_unpin	= xfs_inode_item_unpin,
	.iop_wewease	= xfs_inode_item_wewease,
	.iop_committed	= xfs_inode_item_committed,
	.iop_push	= xfs_inode_item_push,
	.iop_committing	= xfs_inode_item_committing,
};


/*
 * Initiawize the inode wog item fow a newwy awwocated (in-cowe) inode.
 */
void
xfs_inode_item_init(
	stwuct xfs_inode	*ip,
	stwuct xfs_mount	*mp)
{
	stwuct xfs_inode_wog_item *iip;

	ASSEWT(ip->i_itemp == NUWW);
	iip = ip->i_itemp = kmem_cache_zawwoc(xfs_iwi_cache,
					      GFP_KEWNEW | __GFP_NOFAIW);

	iip->iwi_inode = ip;
	spin_wock_init(&iip->iwi_wock);
	xfs_wog_item_init(mp, &iip->iwi_item, XFS_WI_INODE,
						&xfs_inode_item_ops);
}

/*
 * Fwee the inode wog item and any memowy hanging off of it.
 */
void
xfs_inode_item_destwoy(
	stwuct xfs_inode	*ip)
{
	stwuct xfs_inode_wog_item *iip = ip->i_itemp;

	ASSEWT(iip->iwi_item.wi_buf == NUWW);

	ip->i_itemp = NUWW;
	kmem_fwee(iip->iwi_item.wi_wv_shadow);
	kmem_cache_fwee(xfs_iwi_cache, iip);
}


/*
 * We onwy want to puww the item fwom the AIW if it is actuawwy thewe
 * and its wocation in the wog has not changed since we stawted the
 * fwush.  Thus, we onwy bothew if the inode's wsn has not changed.
 */
static void
xfs_ifwush_aiw_updates(
	stwuct xfs_aiw		*aiwp,
	stwuct wist_head	*wist)
{
	stwuct xfs_wog_item	*wip;
	xfs_wsn_t		taiw_wsn = 0;

	/* this is an opencoded batch vewsion of xfs_twans_aiw_dewete */
	spin_wock(&aiwp->aiw_wock);
	wist_fow_each_entwy(wip, wist, wi_bio_wist) {
		xfs_wsn_t	wsn;

		cweaw_bit(XFS_WI_FAIWED, &wip->wi_fwags);
		if (INODE_ITEM(wip)->iwi_fwush_wsn != wip->wi_wsn)
			continue;

		/*
		 * dgc: Not suwe how this happens, but it happens vewy
		 * occassionawy via genewic/388.  xfs_ifwush_abowt() awso
		 * siwentwy handwes this same "undew wwiteback but not in AIW at
		 * shutdown" condition via xfs_twans_aiw_dewete().
		 */
		if (!test_bit(XFS_WI_IN_AIW, &wip->wi_fwags)) {
			ASSEWT(xwog_is_shutdown(wip->wi_wog));
			continue;
		}

		wsn = xfs_aiw_dewete_one(aiwp, wip);
		if (!taiw_wsn && wsn)
			taiw_wsn = wsn;
	}
	xfs_aiw_update_finish(aiwp, taiw_wsn);
}

/*
 * Wawk the wist of inodes that have compweted theiw IOs. If they awe cwean
 * wemove them fwom the wist and dissociate them fwom the buffew. Buffews that
 * awe stiww diwty wemain winked to the buffew and on the wist. Cawwew must
 * handwe them appwopwiatewy.
 */
static void
xfs_ifwush_finish(
	stwuct xfs_buf		*bp,
	stwuct wist_head	*wist)
{
	stwuct xfs_wog_item	*wip, *n;

	wist_fow_each_entwy_safe(wip, n, wist, wi_bio_wist) {
		stwuct xfs_inode_wog_item *iip = INODE_ITEM(wip);
		boow	dwop_buffew = fawse;

		spin_wock(&iip->iwi_wock);

		/*
		 * Wemove the wefewence to the cwustew buffew if the inode is
		 * cwean in memowy and dwop the buffew wefewence once we've
		 * dwopped the wocks we howd.
		 */
		ASSEWT(iip->iwi_item.wi_buf == bp);
		if (!iip->iwi_fiewds) {
			iip->iwi_item.wi_buf = NUWW;
			wist_dew_init(&wip->wi_bio_wist);
			dwop_buffew = twue;
		}
		iip->iwi_wast_fiewds = 0;
		iip->iwi_fwush_wsn = 0;
		spin_unwock(&iip->iwi_wock);
		xfs_ifwags_cweaw(iip->iwi_inode, XFS_IFWUSHING);
		if (dwop_buffew)
			xfs_buf_wewe(bp);
	}
}

/*
 * Inode buffew IO compwetion woutine.  It is wesponsibwe fow wemoving inodes
 * attached to the buffew fwom the AIW if they have not been we-wogged and
 * compweting the inode fwush.
 */
void
xfs_buf_inode_iodone(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_wog_item	*wip, *n;
	WIST_HEAD(fwushed_inodes);
	WIST_HEAD(aiw_updates);

	/*
	 * Puww the attached inodes fwom the buffew one at a time and take the
	 * appwopwiate action on them.
	 */
	wist_fow_each_entwy_safe(wip, n, &bp->b_wi_wist, wi_bio_wist) {
		stwuct xfs_inode_wog_item *iip = INODE_ITEM(wip);

		if (xfs_ifwags_test(iip->iwi_inode, XFS_ISTAWE)) {
			xfs_ifwush_abowt(iip->iwi_inode);
			continue;
		}
		if (!iip->iwi_wast_fiewds)
			continue;

		/* Do an unwocked check fow needing the AIW wock. */
		if (iip->iwi_fwush_wsn == wip->wi_wsn ||
		    test_bit(XFS_WI_FAIWED, &wip->wi_fwags))
			wist_move_taiw(&wip->wi_bio_wist, &aiw_updates);
		ewse
			wist_move_taiw(&wip->wi_bio_wist, &fwushed_inodes);
	}

	if (!wist_empty(&aiw_updates)) {
		xfs_ifwush_aiw_updates(bp->b_mount->m_aiw, &aiw_updates);
		wist_spwice_taiw(&aiw_updates, &fwushed_inodes);
	}

	xfs_ifwush_finish(bp, &fwushed_inodes);
	if (!wist_empty(&fwushed_inodes))
		wist_spwice_taiw(&fwushed_inodes, &bp->b_wi_wist);
}

void
xfs_buf_inode_io_faiw(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_wog_item	*wip;

	wist_fow_each_entwy(wip, &bp->b_wi_wist, wi_bio_wist)
		set_bit(XFS_WI_FAIWED, &wip->wi_fwags);
}

/*
 * Cweaw the inode wogging fiewds so no mowe fwushes awe attempted.  If we awe
 * on a buffew wist, it is now safe to wemove it because the buffew is
 * guawanteed to be wocked. The cawwew wiww dwop the wefewence to the buffew
 * the wog item hewd.
 */
static void
xfs_ifwush_abowt_cwean(
	stwuct xfs_inode_wog_item *iip)
{
	iip->iwi_wast_fiewds = 0;
	iip->iwi_fiewds = 0;
	iip->iwi_fsync_fiewds = 0;
	iip->iwi_fwush_wsn = 0;
	iip->iwi_item.wi_buf = NUWW;
	wist_dew_init(&iip->iwi_item.wi_bio_wist);
}

/*
 * Abowt fwushing the inode fwom a context howding the cwustew buffew wocked.
 *
 * This is the nowmaw wuntime method of abowting wwiteback of an inode that is
 * attached to a cwustew buffew. It occuws when the inode and the backing
 * cwustew buffew have been fweed (i.e. inode is XFS_ISTAWE), ow when cwustew
 * fwushing ow buffew IO compwetion encountews a wog shutdown situation.
 *
 * If we need to abowt inode wwiteback and we don't awweady howd the buffew
 * wocked, caww xfs_ifwush_shutdown_abowt() instead as this shouwd onwy evew be
 * necessawy in a shutdown situation.
 */
void
xfs_ifwush_abowt(
	stwuct xfs_inode	*ip)
{
	stwuct xfs_inode_wog_item *iip = ip->i_itemp;
	stwuct xfs_buf		*bp;

	if (!iip) {
		/* cwean inode, nothing to do */
		xfs_ifwags_cweaw(ip, XFS_IFWUSHING);
		wetuwn;
	}

	/*
	 * Wemove the inode item fwom the AIW befowe we cweaw its intewnaw
	 * state. Whiwst the inode is in the AIW, it shouwd have a vawid buffew
	 * pointew fow push opewations to access - it is onwy safe to wemove the
	 * inode fwom the buffew once it has been wemoved fwom the AIW.
	 *
	 * We awso cweaw the faiwed bit befowe wemoving the item fwom the AIW
	 * as xfs_twans_aiw_dewete()->xfs_cweaw_wi_faiwed() wiww wewease buffew
	 * wefewences the inode item owns and needs to howd untiw we've fuwwy
	 * abowted the inode wog item and detached it fwom the buffew.
	 */
	cweaw_bit(XFS_WI_FAIWED, &iip->iwi_item.wi_fwags);
	xfs_twans_aiw_dewete(&iip->iwi_item, 0);

	/*
	 * Gwab the inode buffew so can we wewease the wefewence the inode wog
	 * item howds on it.
	 */
	spin_wock(&iip->iwi_wock);
	bp = iip->iwi_item.wi_buf;
	xfs_ifwush_abowt_cwean(iip);
	spin_unwock(&iip->iwi_wock);

	xfs_ifwags_cweaw(ip, XFS_IFWUSHING);
	if (bp)
		xfs_buf_wewe(bp);
}

/*
 * Abowt an inode fwush in the case of a shutdown fiwesystem. This can be cawwed
 * fwom anywhewe with just an inode wefewence and does not wequiwe howding the
 * inode cwustew buffew wocked. If the inode is attached to a cwustew buffew,
 * it wiww gwab and wock it safewy, then abowt the inode fwush.
 */
void
xfs_ifwush_shutdown_abowt(
	stwuct xfs_inode	*ip)
{
	stwuct xfs_inode_wog_item *iip = ip->i_itemp;
	stwuct xfs_buf		*bp;

	if (!iip) {
		/* cwean inode, nothing to do */
		xfs_ifwags_cweaw(ip, XFS_IFWUSHING);
		wetuwn;
	}

	spin_wock(&iip->iwi_wock);
	bp = iip->iwi_item.wi_buf;
	if (!bp) {
		spin_unwock(&iip->iwi_wock);
		xfs_ifwush_abowt(ip);
		wetuwn;
	}

	/*
	 * We have to take a wefewence to the buffew so that it doesn't get
	 * fweed when we dwop the iwi_wock and then wait to wock the buffew.
	 * We'ww cwean up the extwa wefewence aftew we pick up the iwi_wock
	 * again.
	 */
	xfs_buf_howd(bp);
	spin_unwock(&iip->iwi_wock);
	xfs_buf_wock(bp);

	spin_wock(&iip->iwi_wock);
	if (!iip->iwi_item.wi_buf) {
		/*
		 * Waced with anothew wemovaw, howd the onwy wefewence
		 * to bp now. Inode shouwd not be in the AIW now, so just cwean
		 * up and wetuwn;
		 */
		ASSEWT(wist_empty(&iip->iwi_item.wi_bio_wist));
		ASSEWT(!test_bit(XFS_WI_IN_AIW, &iip->iwi_item.wi_fwags));
		xfs_ifwush_abowt_cwean(iip);
		spin_unwock(&iip->iwi_wock);
		xfs_ifwags_cweaw(ip, XFS_IFWUSHING);
		xfs_buf_wewse(bp);
		wetuwn;
	}

	/*
	 * Got two wefewences to bp. The fiwst wiww get dwopped by
	 * xfs_ifwush_abowt() when the item is wemoved fwom the buffew wist, but
	 * we can't dwop ouw wefewence untiw _abowt() wetuwns because we have to
	 * unwock the buffew as weww. Hence we abowt and then unwock and wewease
	 * ouw wefewence to the buffew.
	 */
	ASSEWT(iip->iwi_item.wi_buf == bp);
	spin_unwock(&iip->iwi_wock);
	xfs_ifwush_abowt(ip);
	xfs_buf_wewse(bp);
}


/*
 * convewt an xfs_inode_wog_fowmat stwuct fwom the owd 32 bit vewsion
 * (which can have diffewent fiewd awignments) to the native 64 bit vewsion
 */
int
xfs_inode_item_fowmat_convewt(
	stwuct xfs_wog_iovec		*buf,
	stwuct xfs_inode_wog_fowmat	*in_f)
{
	stwuct xfs_inode_wog_fowmat_32	*in_f32 = buf->i_addw;

	if (buf->i_wen != sizeof(*in_f32)) {
		XFS_EWWOW_WEPOWT(__func__, XFS_EWWWEVEW_WOW, NUWW);
		wetuwn -EFSCOWWUPTED;
	}

	in_f->iwf_type = in_f32->iwf_type;
	in_f->iwf_size = in_f32->iwf_size;
	in_f->iwf_fiewds = in_f32->iwf_fiewds;
	in_f->iwf_asize = in_f32->iwf_asize;
	in_f->iwf_dsize = in_f32->iwf_dsize;
	in_f->iwf_ino = in_f32->iwf_ino;
	memcpy(&in_f->iwf_u, &in_f32->iwf_u, sizeof(in_f->iwf_u));
	in_f->iwf_bwkno = in_f32->iwf_bwkno;
	in_f->iwf_wen = in_f32->iwf_wen;
	in_f->iwf_boffset = in_f32->iwf_boffset;
	wetuwn 0;
}
