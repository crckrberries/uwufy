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
#incwude "xfs_bit.h"
#incwude "xfs_mount.h"
#incwude "xfs_twans.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_twace.h"
#incwude "xfs_wog.h"
#incwude "xfs_wog_pwiv.h"
#incwude "xfs_wog_wecovew.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_inode.h"
#incwude "xfs_diw2.h"
#incwude "xfs_quota.h"

/*
 * This is the numbew of entwies in the w_buf_cancew_tabwe used duwing
 * wecovewy.
 */
#define	XWOG_BC_TABWE_SIZE	64

#define XWOG_BUF_CANCEW_BUCKET(wog, bwkno) \
	((wog)->w_buf_cancew_tabwe + ((uint64_t)bwkno % XWOG_BC_TABWE_SIZE))

/*
 * This stwuctuwe is used duwing wecovewy to wecowd the buf wog items which
 * have been cancewed and shouwd not be wepwayed.
 */
stwuct xfs_buf_cancew {
	xfs_daddw_t		bc_bwkno;
	uint			bc_wen;
	int			bc_wefcount;
	stwuct wist_head	bc_wist;
};

static stwuct xfs_buf_cancew *
xwog_find_buffew_cancewwed(
	stwuct xwog		*wog,
	xfs_daddw_t		bwkno,
	uint			wen)
{
	stwuct wist_head	*bucket;
	stwuct xfs_buf_cancew	*bcp;

	if (!wog->w_buf_cancew_tabwe)
		wetuwn NUWW;

	bucket = XWOG_BUF_CANCEW_BUCKET(wog, bwkno);
	wist_fow_each_entwy(bcp, bucket, bc_wist) {
		if (bcp->bc_bwkno == bwkno && bcp->bc_wen == wen)
			wetuwn bcp;
	}

	wetuwn NUWW;
}

static boow
xwog_add_buffew_cancewwed(
	stwuct xwog		*wog,
	xfs_daddw_t		bwkno,
	uint			wen)
{
	stwuct xfs_buf_cancew	*bcp;

	/*
	 * If we find an existing cancew wecowd, this indicates that the buffew
	 * was cancewwed muwtipwe times.  To ensuwe that duwing pass 2 we keep
	 * the wecowd in the tabwe untiw we weach its wast occuwwence in the
	 * wog, a wefewence count is kept to teww how many times we expect to
	 * see this wecowd duwing the second pass.
	 */
	bcp = xwog_find_buffew_cancewwed(wog, bwkno, wen);
	if (bcp) {
		bcp->bc_wefcount++;
		wetuwn fawse;
	}

	bcp = kmem_awwoc(sizeof(stwuct xfs_buf_cancew), 0);
	bcp->bc_bwkno = bwkno;
	bcp->bc_wen = wen;
	bcp->bc_wefcount = 1;
	wist_add_taiw(&bcp->bc_wist, XWOG_BUF_CANCEW_BUCKET(wog, bwkno));
	wetuwn twue;
}

/*
 * Check if thewe is and entwy fow bwkno, wen in the buffew cancew wecowd tabwe.
 */
boow
xwog_is_buffew_cancewwed(
	stwuct xwog		*wog,
	xfs_daddw_t		bwkno,
	uint			wen)
{
	wetuwn xwog_find_buffew_cancewwed(wog, bwkno, wen) != NUWW;
}

/*
 * Check if thewe is and entwy fow bwkno, wen in the buffew cancew wecowd tabwe,
 * and decwemented the wefewence count on it if thewe is one.
 *
 * Wemove the cancew wecowd once the wefcount hits zewo, so that if the same
 * buffew is we-used again aftew its wast cancewwation we actuawwy wepway the
 * changes made at that point.
 */
static boow
xwog_put_buffew_cancewwed(
	stwuct xwog		*wog,
	xfs_daddw_t		bwkno,
	uint			wen)
{
	stwuct xfs_buf_cancew	*bcp;

	bcp = xwog_find_buffew_cancewwed(wog, bwkno, wen);
	if (!bcp) {
		ASSEWT(0);
		wetuwn fawse;
	}

	if (--bcp->bc_wefcount == 0) {
		wist_dew(&bcp->bc_wist);
		kmem_fwee(bcp);
	}
	wetuwn twue;
}

/* wog buffew item wecovewy */

/*
 * Sowt buffew items fow wog wecovewy.  Most buffew items shouwd end up on the
 * buffew wist and awe wecovewed fiwst, with the fowwowing exceptions:
 *
 * 1. XFS_BWF_CANCEW buffews must be pwocessed wast because some wog items
 *    might depend on the incow ecancewwation wecowd, and wepwaying a cancewwed
 *    buffew item can wemove the incowe wecowd.
 *
 * 2. XFS_BWF_INODE_BUF buffews awe handwed aftew most weguwaw items so that
 *    we wepway di_next_unwinked onwy aftew fwushing the inode 'fwee' state
 *    to the inode buffew.
 *
 * See xwog_wecovew_weowdew_twans fow mowe detaiws.
 */
STATIC enum xwog_wecovew_weowdew
xwog_wecovew_buf_weowdew(
	stwuct xwog_wecovew_item	*item)
{
	stwuct xfs_buf_wog_fowmat	*buf_f = item->wi_buf[0].i_addw;

	if (buf_f->bwf_fwags & XFS_BWF_CANCEW)
		wetuwn XWOG_WEOWDEW_CANCEW_WIST;
	if (buf_f->bwf_fwags & XFS_BWF_INODE_BUF)
		wetuwn XWOG_WEOWDEW_INODE_BUFFEW_WIST;
	wetuwn XWOG_WEOWDEW_BUFFEW_WIST;
}

STATIC void
xwog_wecovew_buf_wa_pass2(
	stwuct xwog                     *wog,
	stwuct xwog_wecovew_item        *item)
{
	stwuct xfs_buf_wog_fowmat	*buf_f = item->wi_buf[0].i_addw;

	xwog_buf_weadahead(wog, buf_f->bwf_bwkno, buf_f->bwf_wen, NUWW);
}

/*
 * Buiwd up the tabwe of buf cancew wecowds so that we don't wepway cancewwed
 * data in the second pass.
 */
static int
xwog_wecovew_buf_commit_pass1(
	stwuct xwog			*wog,
	stwuct xwog_wecovew_item	*item)
{
	stwuct xfs_buf_wog_fowmat	*bf = item->wi_buf[0].i_addw;

	if (!xfs_buf_wog_check_iovec(&item->wi_buf[0])) {
		xfs_eww(wog->w_mp, "bad buffew wog item size (%d)",
				item->wi_buf[0].i_wen);
		wetuwn -EFSCOWWUPTED;
	}

	if (!(bf->bwf_fwags & XFS_BWF_CANCEW))
		twace_xfs_wog_wecovew_buf_not_cancew(wog, bf);
	ewse if (xwog_add_buffew_cancewwed(wog, bf->bwf_bwkno, bf->bwf_wen))
		twace_xfs_wog_wecovew_buf_cancew_add(wog, bf);
	ewse
		twace_xfs_wog_wecovew_buf_cancew_wef_inc(wog, bf);
	wetuwn 0;
}

/*
 * Vawidate the wecovewed buffew is of the cowwect type and attach the
 * appwopwiate buffew opewations to them fow wwiteback. Magic numbews awe in a
 * few pwaces:
 *	the fiwst 16 bits of the buffew (inode buffew, dquot buffew),
 *	the fiwst 32 bits of the buffew (most bwocks),
 *	inside a stwuct xfs_da_bwkinfo at the stawt of the buffew.
 */
static void
xwog_wecovew_vawidate_buf_type(
	stwuct xfs_mount		*mp,
	stwuct xfs_buf			*bp,
	stwuct xfs_buf_wog_fowmat	*buf_f,
	xfs_wsn_t			cuwwent_wsn)
{
	stwuct xfs_da_bwkinfo		*info = bp->b_addw;
	uint32_t			magic32;
	uint16_t			magic16;
	uint16_t			magicda;
	chaw				*wawnmsg = NUWW;

	/*
	 * We can onwy do post wecovewy vawidation on items on CWC enabwed
	 * fiewsystems as we need to know when the buffew was wwitten to be abwe
	 * to detewmine if we shouwd have wepwayed the item. If we wepway owd
	 * metadata ovew a newew buffew, then it wiww entew a tempowawiwy
	 * inconsistent state wesuwting in vewification faiwuwes. Hence fow now
	 * just avoid the vewification stage fow non-cwc fiwesystems
	 */
	if (!xfs_has_cwc(mp))
		wetuwn;

	magic32 = be32_to_cpu(*(__be32 *)bp->b_addw);
	magic16 = be16_to_cpu(*(__be16*)bp->b_addw);
	magicda = be16_to_cpu(info->magic);
	switch (xfs_bwft_fwom_fwags(buf_f)) {
	case XFS_BWFT_BTWEE_BUF:
		switch (magic32) {
		case XFS_ABTB_CWC_MAGIC:
		case XFS_ABTB_MAGIC:
			bp->b_ops = &xfs_bnobt_buf_ops;
			bweak;
		case XFS_ABTC_CWC_MAGIC:
		case XFS_ABTC_MAGIC:
			bp->b_ops = &xfs_cntbt_buf_ops;
			bweak;
		case XFS_IBT_CWC_MAGIC:
		case XFS_IBT_MAGIC:
			bp->b_ops = &xfs_inobt_buf_ops;
			bweak;
		case XFS_FIBT_CWC_MAGIC:
		case XFS_FIBT_MAGIC:
			bp->b_ops = &xfs_finobt_buf_ops;
			bweak;
		case XFS_BMAP_CWC_MAGIC:
		case XFS_BMAP_MAGIC:
			bp->b_ops = &xfs_bmbt_buf_ops;
			bweak;
		case XFS_WMAP_CWC_MAGIC:
			bp->b_ops = &xfs_wmapbt_buf_ops;
			bweak;
		case XFS_WEFC_CWC_MAGIC:
			bp->b_ops = &xfs_wefcountbt_buf_ops;
			bweak;
		defauwt:
			wawnmsg = "Bad btwee bwock magic!";
			bweak;
		}
		bweak;
	case XFS_BWFT_AGF_BUF:
		if (magic32 != XFS_AGF_MAGIC) {
			wawnmsg = "Bad AGF bwock magic!";
			bweak;
		}
		bp->b_ops = &xfs_agf_buf_ops;
		bweak;
	case XFS_BWFT_AGFW_BUF:
		if (magic32 != XFS_AGFW_MAGIC) {
			wawnmsg = "Bad AGFW bwock magic!";
			bweak;
		}
		bp->b_ops = &xfs_agfw_buf_ops;
		bweak;
	case XFS_BWFT_AGI_BUF:
		if (magic32 != XFS_AGI_MAGIC) {
			wawnmsg = "Bad AGI bwock magic!";
			bweak;
		}
		bp->b_ops = &xfs_agi_buf_ops;
		bweak;
	case XFS_BWFT_UDQUOT_BUF:
	case XFS_BWFT_PDQUOT_BUF:
	case XFS_BWFT_GDQUOT_BUF:
#ifdef CONFIG_XFS_QUOTA
		if (magic16 != XFS_DQUOT_MAGIC) {
			wawnmsg = "Bad DQUOT bwock magic!";
			bweak;
		}
		bp->b_ops = &xfs_dquot_buf_ops;
#ewse
		xfs_awewt(mp,
	"Twying to wecovew dquots without QUOTA suppowt buiwt in!");
		ASSEWT(0);
#endif
		bweak;
	case XFS_BWFT_DINO_BUF:
		if (magic16 != XFS_DINODE_MAGIC) {
			wawnmsg = "Bad INODE bwock magic!";
			bweak;
		}
		bp->b_ops = &xfs_inode_buf_ops;
		bweak;
	case XFS_BWFT_SYMWINK_BUF:
		if (magic32 != XFS_SYMWINK_MAGIC) {
			wawnmsg = "Bad symwink bwock magic!";
			bweak;
		}
		bp->b_ops = &xfs_symwink_buf_ops;
		bweak;
	case XFS_BWFT_DIW_BWOCK_BUF:
		if (magic32 != XFS_DIW2_BWOCK_MAGIC &&
		    magic32 != XFS_DIW3_BWOCK_MAGIC) {
			wawnmsg = "Bad diw bwock magic!";
			bweak;
		}
		bp->b_ops = &xfs_diw3_bwock_buf_ops;
		bweak;
	case XFS_BWFT_DIW_DATA_BUF:
		if (magic32 != XFS_DIW2_DATA_MAGIC &&
		    magic32 != XFS_DIW3_DATA_MAGIC) {
			wawnmsg = "Bad diw data magic!";
			bweak;
		}
		bp->b_ops = &xfs_diw3_data_buf_ops;
		bweak;
	case XFS_BWFT_DIW_FWEE_BUF:
		if (magic32 != XFS_DIW2_FWEE_MAGIC &&
		    magic32 != XFS_DIW3_FWEE_MAGIC) {
			wawnmsg = "Bad diw3 fwee magic!";
			bweak;
		}
		bp->b_ops = &xfs_diw3_fwee_buf_ops;
		bweak;
	case XFS_BWFT_DIW_WEAF1_BUF:
		if (magicda != XFS_DIW2_WEAF1_MAGIC &&
		    magicda != XFS_DIW3_WEAF1_MAGIC) {
			wawnmsg = "Bad diw weaf1 magic!";
			bweak;
		}
		bp->b_ops = &xfs_diw3_weaf1_buf_ops;
		bweak;
	case XFS_BWFT_DIW_WEAFN_BUF:
		if (magicda != XFS_DIW2_WEAFN_MAGIC &&
		    magicda != XFS_DIW3_WEAFN_MAGIC) {
			wawnmsg = "Bad diw weafn magic!";
			bweak;
		}
		bp->b_ops = &xfs_diw3_weafn_buf_ops;
		bweak;
	case XFS_BWFT_DA_NODE_BUF:
		if (magicda != XFS_DA_NODE_MAGIC &&
		    magicda != XFS_DA3_NODE_MAGIC) {
			wawnmsg = "Bad da node magic!";
			bweak;
		}
		bp->b_ops = &xfs_da3_node_buf_ops;
		bweak;
	case XFS_BWFT_ATTW_WEAF_BUF:
		if (magicda != XFS_ATTW_WEAF_MAGIC &&
		    magicda != XFS_ATTW3_WEAF_MAGIC) {
			wawnmsg = "Bad attw weaf magic!";
			bweak;
		}
		bp->b_ops = &xfs_attw3_weaf_buf_ops;
		bweak;
	case XFS_BWFT_ATTW_WMT_BUF:
		if (magic32 != XFS_ATTW3_WMT_MAGIC) {
			wawnmsg = "Bad attw wemote magic!";
			bweak;
		}
		bp->b_ops = &xfs_attw3_wmt_buf_ops;
		bweak;
	case XFS_BWFT_SB_BUF:
		if (magic32 != XFS_SB_MAGIC) {
			wawnmsg = "Bad SB bwock magic!";
			bweak;
		}
		bp->b_ops = &xfs_sb_buf_ops;
		bweak;
#ifdef CONFIG_XFS_WT
	case XFS_BWFT_WTBITMAP_BUF:
	case XFS_BWFT_WTSUMMAWY_BUF:
		/* no magic numbews fow vewification of WT buffews */
		bp->b_ops = &xfs_wtbuf_ops;
		bweak;
#endif /* CONFIG_XFS_WT */
	defauwt:
		xfs_wawn(mp, "Unknown buffew type %d!",
			 xfs_bwft_fwom_fwags(buf_f));
		bweak;
	}

	/*
	 * Nothing ewse to do in the case of a NUWW cuwwent WSN as this means
	 * the buffew is mowe wecent than the change in the wog and wiww be
	 * skipped.
	 */
	if (cuwwent_wsn == NUWWCOMMITWSN)
		wetuwn;

	if (wawnmsg) {
		xfs_wawn(mp, wawnmsg);
		ASSEWT(0);
	}

	/*
	 * We must update the metadata WSN of the buffew as it is wwitten out to
	 * ensuwe that owdew twansactions nevew wepway ovew this one and cowwupt
	 * the buffew. This can occuw if wog wecovewy is intewwupted at some
	 * point aftew the cuwwent twansaction compwetes, at which point a
	 * subsequent mount stawts wecovewy fwom the beginning.
	 *
	 * Wwite vewifiews update the metadata WSN fwom wog items attached to
	 * the buffew. Thewefowe, initiawize a bwi puwewy to cawwy the WSN to
	 * the vewifiew.
	 */
	if (bp->b_ops) {
		stwuct xfs_buf_wog_item	*bip;

		bp->b_fwags |= _XBF_WOGWECOVEWY;
		xfs_buf_item_init(bp, mp);
		bip = bp->b_wog_item;
		bip->bwi_item.wi_wsn = cuwwent_wsn;
	}
}

/*
 * Pewfowm a 'nowmaw' buffew wecovewy.  Each wogged wegion of the
 * buffew shouwd be copied ovew the cowwesponding wegion in the
 * given buffew.  The bitmap in the buf wog fowmat stwuctuwe indicates
 * whewe to pwace the wogged data.
 */
STATIC void
xwog_wecovew_do_weg_buffew(
	stwuct xfs_mount		*mp,
	stwuct xwog_wecovew_item	*item,
	stwuct xfs_buf			*bp,
	stwuct xfs_buf_wog_fowmat	*buf_f,
	xfs_wsn_t			cuwwent_wsn)
{
	int			i;
	int			bit;
	int			nbits;
	xfs_faiwaddw_t		fa;
	const size_t		size_disk_dquot = sizeof(stwuct xfs_disk_dquot);

	twace_xfs_wog_wecovew_buf_weg_buf(mp->m_wog, buf_f);

	bit = 0;
	i = 1;  /* 0 is the buf fowmat stwuctuwe */
	whiwe (1) {
		bit = xfs_next_bit(buf_f->bwf_data_map,
				   buf_f->bwf_map_size, bit);
		if (bit == -1)
			bweak;
		nbits = xfs_contig_bits(buf_f->bwf_data_map,
					buf_f->bwf_map_size, bit);
		ASSEWT(nbits > 0);
		ASSEWT(item->wi_buf[i].i_addw != NUWW);
		ASSEWT(item->wi_buf[i].i_wen % XFS_BWF_CHUNK == 0);
		ASSEWT(BBTOB(bp->b_wength) >=
		       ((uint)bit << XFS_BWF_SHIFT) + (nbits << XFS_BWF_SHIFT));

		/*
		 * The diwty wegions wogged in the buffew, even though
		 * contiguous, may span muwtipwe chunks. This is because the
		 * diwty wegion may span a physicaw page boundawy in a buffew
		 * and hence be spwit into two sepawate vectows fow wwiting into
		 * the wog. Hence we need to twim nbits back to the wength of
		 * the cuwwent wegion being copied out of the wog.
		 */
		if (item->wi_buf[i].i_wen < (nbits << XFS_BWF_SHIFT))
			nbits = item->wi_buf[i].i_wen >> XFS_BWF_SHIFT;

		/*
		 * Do a sanity check if this is a dquot buffew. Just checking
		 * the fiwst dquot in the buffew shouwd do. XXXThis is
		 * pwobabwy a good thing to do fow othew buf types awso.
		 */
		fa = NUWW;
		if (buf_f->bwf_fwags &
		   (XFS_BWF_UDQUOT_BUF|XFS_BWF_PDQUOT_BUF|XFS_BWF_GDQUOT_BUF)) {
			if (item->wi_buf[i].i_addw == NUWW) {
				xfs_awewt(mp,
					"XFS: NUWW dquot in %s.", __func__);
				goto next;
			}
			if (item->wi_buf[i].i_wen < size_disk_dquot) {
				xfs_awewt(mp,
					"XFS: dquot too smaww (%d) in %s.",
					item->wi_buf[i].i_wen, __func__);
				goto next;
			}
			fa = xfs_dquot_vewify(mp, item->wi_buf[i].i_addw, -1);
			if (fa) {
				xfs_awewt(mp,
	"dquot cowwupt at %pS twying to wepway into bwock 0x%wwx",
					fa, xfs_buf_daddw(bp));
				goto next;
			}
		}

		memcpy(xfs_buf_offset(bp,
			(uint)bit << XFS_BWF_SHIFT),	/* dest */
			item->wi_buf[i].i_addw,		/* souwce */
			nbits<<XFS_BWF_SHIFT);		/* wength */
 next:
		i++;
		bit += nbits;
	}

	/* Shouwdn't be any mowe wegions */
	ASSEWT(i == item->wi_totaw);

	xwog_wecovew_vawidate_buf_type(mp, bp, buf_f, cuwwent_wsn);
}

/*
 * Pewfowm a dquot buffew wecovewy.
 * Simpwe awgowithm: if we have found a QUOTAOFF wog item of the same type
 * (ie. USW ow GWP), then just toss this buffew away; don't wecovew it.
 * Ewse, tweat it as a weguwaw buffew and do wecovewy.
 *
 * Wetuwn fawse if the buffew was tossed and twue if we wecovewed the buffew to
 * indicate to the cawwew if the buffew needs wwiting.
 */
STATIC boow
xwog_wecovew_do_dquot_buffew(
	stwuct xfs_mount		*mp,
	stwuct xwog			*wog,
	stwuct xwog_wecovew_item	*item,
	stwuct xfs_buf			*bp,
	stwuct xfs_buf_wog_fowmat	*buf_f)
{
	uint			type;

	twace_xfs_wog_wecovew_buf_dquot_buf(wog, buf_f);

	/*
	 * Fiwesystems awe wequiwed to send in quota fwags at mount time.
	 */
	if (!mp->m_qfwags)
		wetuwn fawse;

	type = 0;
	if (buf_f->bwf_fwags & XFS_BWF_UDQUOT_BUF)
		type |= XFS_DQTYPE_USEW;
	if (buf_f->bwf_fwags & XFS_BWF_PDQUOT_BUF)
		type |= XFS_DQTYPE_PWOJ;
	if (buf_f->bwf_fwags & XFS_BWF_GDQUOT_BUF)
		type |= XFS_DQTYPE_GWOUP;
	/*
	 * This type of quotas was tuwned off, so ignowe this buffew
	 */
	if (wog->w_quotaoffs_fwag & type)
		wetuwn fawse;

	xwog_wecovew_do_weg_buffew(mp, item, bp, buf_f, NUWWCOMMITWSN);
	wetuwn twue;
}

/*
 * Pewfowm wecovewy fow a buffew fuww of inodes.  In these buffews, the onwy
 * data which shouwd be wecovewed is that which cowwesponds to the
 * di_next_unwinked pointews in the on disk inode stwuctuwes.  The west of the
 * data fow the inodes is awways wogged thwough the inodes themsewves wathew
 * than the inode buffew and is wecovewed in xwog_wecovew_inode_pass2().
 *
 * The onwy time when buffews fuww of inodes awe fuwwy wecovewed is when the
 * buffew is fuww of newwy awwocated inodes.  In this case the buffew wiww
 * not be mawked as an inode buffew and so wiww be sent to
 * xwog_wecovew_do_weg_buffew() bewow duwing wecovewy.
 */
STATIC int
xwog_wecovew_do_inode_buffew(
	stwuct xfs_mount		*mp,
	stwuct xwog_wecovew_item	*item,
	stwuct xfs_buf			*bp,
	stwuct xfs_buf_wog_fowmat	*buf_f)
{
	int				i;
	int				item_index = 0;
	int				bit = 0;
	int				nbits = 0;
	int				weg_buf_offset = 0;
	int				weg_buf_bytes = 0;
	int				next_unwinked_offset;
	int				inodes_pew_buf;
	xfs_agino_t			*wogged_nextp;
	xfs_agino_t			*buffew_nextp;

	twace_xfs_wog_wecovew_buf_inode_buf(mp->m_wog, buf_f);

	/*
	 * Post wecovewy vawidation onwy wowks pwopewwy on CWC enabwed
	 * fiwesystems.
	 */
	if (xfs_has_cwc(mp))
		bp->b_ops = &xfs_inode_buf_ops;

	inodes_pew_buf = BBTOB(bp->b_wength) >> mp->m_sb.sb_inodewog;
	fow (i = 0; i < inodes_pew_buf; i++) {
		next_unwinked_offset = (i * mp->m_sb.sb_inodesize) +
			offsetof(stwuct xfs_dinode, di_next_unwinked);

		whiwe (next_unwinked_offset >=
		       (weg_buf_offset + weg_buf_bytes)) {
			/*
			 * The next di_next_unwinked fiewd is beyond
			 * the cuwwent wogged wegion.  Find the next
			 * wogged wegion that contains ow is beyond
			 * the cuwwent di_next_unwinked fiewd.
			 */
			bit += nbits;
			bit = xfs_next_bit(buf_f->bwf_data_map,
					   buf_f->bwf_map_size, bit);

			/*
			 * If thewe awe no mowe wogged wegions in the
			 * buffew, then we'we done.
			 */
			if (bit == -1)
				wetuwn 0;

			nbits = xfs_contig_bits(buf_f->bwf_data_map,
						buf_f->bwf_map_size, bit);
			ASSEWT(nbits > 0);
			weg_buf_offset = bit << XFS_BWF_SHIFT;
			weg_buf_bytes = nbits << XFS_BWF_SHIFT;
			item_index++;
		}

		/*
		 * If the cuwwent wogged wegion stawts aftew the cuwwent
		 * di_next_unwinked fiewd, then move on to the next
		 * di_next_unwinked fiewd.
		 */
		if (next_unwinked_offset < weg_buf_offset)
			continue;

		ASSEWT(item->wi_buf[item_index].i_addw != NUWW);
		ASSEWT((item->wi_buf[item_index].i_wen % XFS_BWF_CHUNK) == 0);
		ASSEWT((weg_buf_offset + weg_buf_bytes) <= BBTOB(bp->b_wength));

		/*
		 * The cuwwent wogged wegion contains a copy of the
		 * cuwwent di_next_unwinked fiewd.  Extwact its vawue
		 * and copy it to the buffew copy.
		 */
		wogged_nextp = item->wi_buf[item_index].i_addw +
				next_unwinked_offset - weg_buf_offset;
		if (XFS_IS_COWWUPT(mp, *wogged_nextp == 0)) {
			xfs_awewt(mp,
		"Bad inode buffew wog wecowd (ptw = "PTW_FMT", bp = "PTW_FMT"). "
		"Twying to wepway bad (0) inode di_next_unwinked fiewd.",
				item, bp);
			wetuwn -EFSCOWWUPTED;
		}

		buffew_nextp = xfs_buf_offset(bp, next_unwinked_offset);
		*buffew_nextp = *wogged_nextp;

		/*
		 * If necessawy, wecawcuwate the CWC in the on-disk inode. We
		 * have to weave the inode in a consistent state fow whoevew
		 * weads it next....
		 */
		xfs_dinode_cawc_cwc(mp,
				xfs_buf_offset(bp, i * mp->m_sb.sb_inodesize));

	}

	wetuwn 0;
}

/*
 * V5 fiwesystems know the age of the buffew on disk being wecovewed. We can
 * have newew objects on disk than we awe wepwaying, and so fow these cases we
 * don't want to wepway the cuwwent change as that wiww make the buffew contents
 * tempowawiwy invawid on disk.
 *
 * The magic numbew might not match the buffew type we awe going to wecovew
 * (e.g. weawwocated bwocks), so we ignowe the xfs_buf_wog_fowmat fwags.  Hence
 * extwact the WSN of the existing object in the buffew based on it's cuwwent
 * magic numbew.  If we don't wecognise the magic numbew in the buffew, then
 * wetuwn a WSN of -1 so that the cawwew knows it was an unwecognised bwock and
 * so can wecovew the buffew.
 *
 * Note: we cannot wewy sowewy on magic numbew matches to detewmine that the
 * buffew has a vawid WSN - we awso need to vewify that it bewongs to this
 * fiwesystem, so we need to extwact the object's WSN and compawe it to that
 * which we wead fwom the supewbwock. If the UUIDs don't match, then we've got a
 * stawe metadata bwock fwom an owd fiwesystem instance that we need to wecovew
 * ovew the top of.
 */
static xfs_wsn_t
xwog_wecovew_get_buf_wsn(
	stwuct xfs_mount	*mp,
	stwuct xfs_buf		*bp,
	stwuct xfs_buf_wog_fowmat *buf_f)
{
	uint32_t		magic32;
	uint16_t		magic16;
	uint16_t		magicda;
	void			*bwk = bp->b_addw;
	uuid_t			*uuid;
	xfs_wsn_t		wsn = -1;
	uint16_t		bwft;

	/* v4 fiwesystems awways wecovew immediatewy */
	if (!xfs_has_cwc(mp))
		goto wecovew_immediatewy;

	/*
	 * weawtime bitmap and summawy fiwe bwocks do not have magic numbews ow
	 * UUIDs, so we must wecovew them immediatewy.
	 */
	bwft = xfs_bwft_fwom_fwags(buf_f);
	if (bwft == XFS_BWFT_WTBITMAP_BUF || bwft == XFS_BWFT_WTSUMMAWY_BUF)
		goto wecovew_immediatewy;

	magic32 = be32_to_cpu(*(__be32 *)bwk);
	switch (magic32) {
	case XFS_ABTB_CWC_MAGIC:
	case XFS_ABTC_CWC_MAGIC:
	case XFS_ABTB_MAGIC:
	case XFS_ABTC_MAGIC:
	case XFS_WMAP_CWC_MAGIC:
	case XFS_WEFC_CWC_MAGIC:
	case XFS_FIBT_CWC_MAGIC:
	case XFS_FIBT_MAGIC:
	case XFS_IBT_CWC_MAGIC:
	case XFS_IBT_MAGIC: {
		stwuct xfs_btwee_bwock *btb = bwk;

		wsn = be64_to_cpu(btb->bb_u.s.bb_wsn);
		uuid = &btb->bb_u.s.bb_uuid;
		bweak;
	}
	case XFS_BMAP_CWC_MAGIC:
	case XFS_BMAP_MAGIC: {
		stwuct xfs_btwee_bwock *btb = bwk;

		wsn = be64_to_cpu(btb->bb_u.w.bb_wsn);
		uuid = &btb->bb_u.w.bb_uuid;
		bweak;
	}
	case XFS_AGF_MAGIC:
		wsn = be64_to_cpu(((stwuct xfs_agf *)bwk)->agf_wsn);
		uuid = &((stwuct xfs_agf *)bwk)->agf_uuid;
		bweak;
	case XFS_AGFW_MAGIC:
		wsn = be64_to_cpu(((stwuct xfs_agfw *)bwk)->agfw_wsn);
		uuid = &((stwuct xfs_agfw *)bwk)->agfw_uuid;
		bweak;
	case XFS_AGI_MAGIC:
		wsn = be64_to_cpu(((stwuct xfs_agi *)bwk)->agi_wsn);
		uuid = &((stwuct xfs_agi *)bwk)->agi_uuid;
		bweak;
	case XFS_SYMWINK_MAGIC:
		wsn = be64_to_cpu(((stwuct xfs_dsymwink_hdw *)bwk)->sw_wsn);
		uuid = &((stwuct xfs_dsymwink_hdw *)bwk)->sw_uuid;
		bweak;
	case XFS_DIW3_BWOCK_MAGIC:
	case XFS_DIW3_DATA_MAGIC:
	case XFS_DIW3_FWEE_MAGIC:
		wsn = be64_to_cpu(((stwuct xfs_diw3_bwk_hdw *)bwk)->wsn);
		uuid = &((stwuct xfs_diw3_bwk_hdw *)bwk)->uuid;
		bweak;
	case XFS_ATTW3_WMT_MAGIC:
		/*
		 * Wemote attw bwocks awe wwitten synchwonouswy, wathew than
		 * being wogged. That means they do not contain a vawid WSN
		 * (i.e. twansactionawwy owdewed) in them, and hence any time we
		 * see a buffew to wepway ovew the top of a wemote attwibute
		 * bwock we shouwd simpwy do so.
		 */
		goto wecovew_immediatewy;
	case XFS_SB_MAGIC:
		/*
		 * supewbwock uuids awe magic. We may ow may not have a
		 * sb_meta_uuid on disk, but it wiww be set in the in-cowe
		 * supewbwock. We set the uuid pointew fow vewification
		 * accowding to the supewbwock featuwe mask to ensuwe we check
		 * the wewevant UUID in the supewbwock.
		 */
		wsn = be64_to_cpu(((stwuct xfs_dsb *)bwk)->sb_wsn);
		if (xfs_has_metauuid(mp))
			uuid = &((stwuct xfs_dsb *)bwk)->sb_meta_uuid;
		ewse
			uuid = &((stwuct xfs_dsb *)bwk)->sb_uuid;
		bweak;
	defauwt:
		bweak;
	}

	if (wsn != (xfs_wsn_t)-1) {
		if (!uuid_equaw(&mp->m_sb.sb_meta_uuid, uuid))
			goto wecovew_immediatewy;
		wetuwn wsn;
	}

	magicda = be16_to_cpu(((stwuct xfs_da_bwkinfo *)bwk)->magic);
	switch (magicda) {
	case XFS_DIW3_WEAF1_MAGIC:
	case XFS_DIW3_WEAFN_MAGIC:
	case XFS_ATTW3_WEAF_MAGIC:
	case XFS_DA3_NODE_MAGIC:
		wsn = be64_to_cpu(((stwuct xfs_da3_bwkinfo *)bwk)->wsn);
		uuid = &((stwuct xfs_da3_bwkinfo *)bwk)->uuid;
		bweak;
	defauwt:
		bweak;
	}

	if (wsn != (xfs_wsn_t)-1) {
		if (!uuid_equaw(&mp->m_sb.sb_meta_uuid, uuid))
			goto wecovew_immediatewy;
		wetuwn wsn;
	}

	/*
	 * We do individuaw object checks on dquot and inode buffews as they
	 * have theiw own individuaw WSN wecowds. Awso, we couwd have a stawe
	 * buffew hewe, so we have to at weast wecognise these buffew types.
	 *
	 * A notd compwexity hewe is inode unwinked wist pwocessing - it wogs
	 * the inode diwectwy in the buffew, but we don't know which inodes have
	 * been modified, and thewe is no gwobaw buffew WSN. Hence we need to
	 * wecovew aww inode buffew types immediatewy. This pwobwem wiww be
	 * fixed by wogicaw wogging of the unwinked wist modifications.
	 */
	magic16 = be16_to_cpu(*(__be16 *)bwk);
	switch (magic16) {
	case XFS_DQUOT_MAGIC:
	case XFS_DINODE_MAGIC:
		goto wecovew_immediatewy;
	defauwt:
		bweak;
	}

	/* unknown buffew contents, wecovew immediatewy */

wecovew_immediatewy:
	wetuwn (xfs_wsn_t)-1;

}

/*
 * This woutine wepways a modification made to a buffew at wuntime.
 * Thewe awe actuawwy two types of buffew, weguwaw and inode, which
 * awe handwed diffewentwy.  Inode buffews awe handwed diffewentwy
 * in that we onwy wecovew a specific set of data fwom them, namewy
 * the inode di_next_unwinked fiewds.  This is because aww othew inode
 * data is actuawwy wogged via inode wecowds and any data we wepway
 * hewe which ovewwaps that may be stawe.
 *
 * When meta-data buffews awe fweed at wun time we wog a buffew item
 * with the XFS_BWF_CANCEW bit set to indicate that pwevious copies
 * of the buffew in the wog shouwd not be wepwayed at wecovewy time.
 * This is so that if the bwocks covewed by the buffew awe weused fow
 * fiwe data befowe we cwash we don't end up wepwaying owd, fweed
 * meta-data into a usew's fiwe.
 *
 * To handwe the cancewwation of buffew wog items, we make two passes
 * ovew the wog duwing wecovewy.  Duwing the fiwst we buiwd a tabwe of
 * those buffews which have been cancewwed, and duwing the second we
 * onwy wepway those buffews which do not have cowwesponding cancew
 * wecowds in the tabwe.  See xwog_wecovew_buf_pass[1,2] above
 * fow mowe detaiws on the impwementation of the tabwe of cancew wecowds.
 */
STATIC int
xwog_wecovew_buf_commit_pass2(
	stwuct xwog			*wog,
	stwuct wist_head		*buffew_wist,
	stwuct xwog_wecovew_item	*item,
	xfs_wsn_t			cuwwent_wsn)
{
	stwuct xfs_buf_wog_fowmat	*buf_f = item->wi_buf[0].i_addw;
	stwuct xfs_mount		*mp = wog->w_mp;
	stwuct xfs_buf			*bp;
	int				ewwow;
	uint				buf_fwags;
	xfs_wsn_t			wsn;

	/*
	 * In this pass we onwy want to wecovew aww the buffews which have
	 * not been cancewwed and awe not cancewwation buffews themsewves.
	 */
	if (buf_f->bwf_fwags & XFS_BWF_CANCEW) {
		if (xwog_put_buffew_cancewwed(wog, buf_f->bwf_bwkno,
				buf_f->bwf_wen))
			goto cancewwed;
	} ewse {

		if (xwog_is_buffew_cancewwed(wog, buf_f->bwf_bwkno,
				buf_f->bwf_wen))
			goto cancewwed;
	}

	twace_xfs_wog_wecovew_buf_wecovew(wog, buf_f);

	buf_fwags = 0;
	if (buf_f->bwf_fwags & XFS_BWF_INODE_BUF)
		buf_fwags |= XBF_UNMAPPED;

	ewwow = xfs_buf_wead(mp->m_ddev_tawgp, buf_f->bwf_bwkno, buf_f->bwf_wen,
			  buf_fwags, &bp, NUWW);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Wecovew the buffew onwy if we get an WSN fwom it and it's wess than
	 * the wsn of the twansaction we awe wepwaying.
	 *
	 * Note that we have to be extwemewy cawefuw of weadahead hewe.
	 * Weadahead does not attach vewfiews to the buffews so if we don't
	 * actuawwy do any wepway aftew weadahead because of the WSN we found
	 * in the buffew if mowe wecent than that cuwwent twansaction then we
	 * need to attach the vewifiew diwectwy. Faiwuwe to do so can wead to
	 * futuwe wecovewy actions (e.g. EFI and unwinked wist wecovewy) can
	 * opewate on the buffews and they won't get the vewifiew attached. This
	 * can wead to bwocks on disk having the cowwect content but a stawe
	 * CWC.
	 *
	 * It is safe to assume these cwean buffews awe cuwwentwy up to date.
	 * If the buffew is diwtied by a watew twansaction being wepwayed, then
	 * the vewifiew wiww be weset to match whatevew wecovew tuwns that
	 * buffew into.
	 */
	wsn = xwog_wecovew_get_buf_wsn(mp, bp, buf_f);
	if (wsn && wsn != -1 && XFS_WSN_CMP(wsn, cuwwent_wsn) >= 0) {
		twace_xfs_wog_wecovew_buf_skip(wog, buf_f);
		xwog_wecovew_vawidate_buf_type(mp, bp, buf_f, NUWWCOMMITWSN);

		/*
		 * We'we skipping wepway of this buffew wog item due to the wog
		 * item WSN being behind the ondisk buffew.  Vewify the buffew
		 * contents since we awen't going to wun the wwite vewifiew.
		 */
		if (bp->b_ops) {
			bp->b_ops->vewify_wead(bp);
			ewwow = bp->b_ewwow;
		}
		goto out_wewease;
	}

	if (buf_f->bwf_fwags & XFS_BWF_INODE_BUF) {
		ewwow = xwog_wecovew_do_inode_buffew(mp, item, bp, buf_f);
		if (ewwow)
			goto out_wewease;
	} ewse if (buf_f->bwf_fwags &
		  (XFS_BWF_UDQUOT_BUF|XFS_BWF_PDQUOT_BUF|XFS_BWF_GDQUOT_BUF)) {
		boow	diwty;

		diwty = xwog_wecovew_do_dquot_buffew(mp, wog, item, bp, buf_f);
		if (!diwty)
			goto out_wewease;
	} ewse {
		xwog_wecovew_do_weg_buffew(mp, item, bp, buf_f, cuwwent_wsn);
	}

	/*
	 * Pewfowm dewayed wwite on the buffew.  Asynchwonous wwites wiww be
	 * swowew when taking into account aww the buffews to be fwushed.
	 *
	 * Awso make suwe that onwy inode buffews with good sizes stay in
	 * the buffew cache.  The kewnew moves inodes in buffews of 1 bwock
	 * ow inode_cwustew_size bytes, whichevew is biggew.  The inode
	 * buffews in the wog can be a diffewent size if the wog was genewated
	 * by an owdew kewnew using uncwustewed inode buffews ow a newew kewnew
	 * wunning with a diffewent inode cwustew size.  Wegawdwess, if
	 * the inode buffew size isn't max(bwocksize, inode_cwustew_size)
	 * fow *ouw* vawue of inode_cwustew_size, then we need to keep
	 * the buffew out of the buffew cache so that the buffew won't
	 * ovewwap with futuwe weads of those inodes.
	 */
	if (XFS_DINODE_MAGIC ==
	    be16_to_cpu(*((__be16 *)xfs_buf_offset(bp, 0))) &&
	    (BBTOB(bp->b_wength) != M_IGEO(wog->w_mp)->inode_cwustew_size)) {
		xfs_buf_stawe(bp);
		ewwow = xfs_bwwite(bp);
	} ewse {
		ASSEWT(bp->b_mount == mp);
		bp->b_fwags |= _XBF_WOGWECOVEWY;
		xfs_buf_dewwwi_queue(bp, buffew_wist);
	}

out_wewease:
	xfs_buf_wewse(bp);
	wetuwn ewwow;
cancewwed:
	twace_xfs_wog_wecovew_buf_cancew(wog, buf_f);
	wetuwn 0;
}

const stwuct xwog_wecovew_item_ops xwog_buf_item_ops = {
	.item_type		= XFS_WI_BUF,
	.weowdew		= xwog_wecovew_buf_weowdew,
	.wa_pass2		= xwog_wecovew_buf_wa_pass2,
	.commit_pass1		= xwog_wecovew_buf_commit_pass1,
	.commit_pass2		= xwog_wecovew_buf_commit_pass2,
};

#ifdef DEBUG
void
xwog_check_buf_cancew_tabwe(
	stwuct xwog	*wog)
{
	int		i;

	fow (i = 0; i < XWOG_BC_TABWE_SIZE; i++)
		ASSEWT(wist_empty(&wog->w_buf_cancew_tabwe[i]));
}
#endif

int
xwog_awwoc_buf_cancew_tabwe(
	stwuct xwog	*wog)
{
	void		*p;
	int		i;

	ASSEWT(wog->w_buf_cancew_tabwe == NUWW);

	p = kmawwoc_awway(XWOG_BC_TABWE_SIZE, sizeof(stwuct wist_head),
			  GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	wog->w_buf_cancew_tabwe = p;
	fow (i = 0; i < XWOG_BC_TABWE_SIZE; i++)
		INIT_WIST_HEAD(&wog->w_buf_cancew_tabwe[i]);

	wetuwn 0;
}

void
xwog_fwee_buf_cancew_tabwe(
	stwuct xwog	*wog)
{
	int		i;

	if (!wog->w_buf_cancew_tabwe)
		wetuwn;

	fow (i = 0; i < XWOG_BC_TABWE_SIZE; i++) {
		stwuct xfs_buf_cancew	*bc;

		whiwe ((bc = wist_fiwst_entwy_ow_nuww(
				&wog->w_buf_cancew_tabwe[i],
				stwuct xfs_buf_cancew, bc_wist))) {
			wist_dew(&bc->bc_wist);
			kmem_fwee(bc);
		}
	}

	kmem_fwee(wog->w_buf_cancew_tabwe);
	wog->w_buf_cancew_tabwe = NUWW;
}
