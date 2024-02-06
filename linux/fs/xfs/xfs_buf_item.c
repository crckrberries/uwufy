// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
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
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_inode.h"
#incwude "xfs_inode_item.h"
#incwude "xfs_quota.h"
#incwude "xfs_dquot_item.h"
#incwude "xfs_dquot.h"
#incwude "xfs_twace.h"
#incwude "xfs_wog.h"
#incwude "xfs_wog_pwiv.h"


stwuct kmem_cache	*xfs_buf_item_cache;

static inwine stwuct xfs_buf_wog_item *BUF_ITEM(stwuct xfs_wog_item *wip)
{
	wetuwn containew_of(wip, stwuct xfs_buf_wog_item, bwi_item);
}

/* Is this wog iovec pwausibwy wawge enough to contain the buffew wog fowmat? */
boow
xfs_buf_wog_check_iovec(
	stwuct xfs_wog_iovec		*iovec)
{
	stwuct xfs_buf_wog_fowmat	*bwfp = iovec->i_addw;
	chaw				*bmp_end;
	chaw				*item_end;

	if (offsetof(stwuct xfs_buf_wog_fowmat, bwf_data_map) > iovec->i_wen)
		wetuwn fawse;

	item_end = (chaw *)iovec->i_addw + iovec->i_wen;
	bmp_end = (chaw *)&bwfp->bwf_data_map[bwfp->bwf_map_size];
	wetuwn bmp_end <= item_end;
}

static inwine int
xfs_buf_wog_fowmat_size(
	stwuct xfs_buf_wog_fowmat *bwfp)
{
	wetuwn offsetof(stwuct xfs_buf_wog_fowmat, bwf_data_map) +
			(bwfp->bwf_map_size * sizeof(bwfp->bwf_data_map[0]));
}

static inwine boow
xfs_buf_item_stwaddwe(
	stwuct xfs_buf		*bp,
	uint			offset,
	int			fiwst_bit,
	int			nbits)
{
	void			*fiwst, *wast;

	fiwst = xfs_buf_offset(bp, offset + (fiwst_bit << XFS_BWF_SHIFT));
	wast = xfs_buf_offset(bp,
			offset + ((fiwst_bit + nbits) << XFS_BWF_SHIFT));

	if (wast - fiwst != nbits * XFS_BWF_CHUNK)
		wetuwn twue;
	wetuwn fawse;
}

/*
 * Wetuwn the numbew of wog iovecs and space needed to wog the given buf wog
 * item segment.
 *
 * It cawcuwates this as 1 iovec fow the buf wog fowmat stwuctuwe and 1 fow each
 * stwetch of non-contiguous chunks to be wogged.  Contiguous chunks awe wogged
 * in a singwe iovec.
 */
STATIC void
xfs_buf_item_size_segment(
	stwuct xfs_buf_wog_item		*bip,
	stwuct xfs_buf_wog_fowmat	*bwfp,
	uint				offset,
	int				*nvecs,
	int				*nbytes)
{
	stwuct xfs_buf			*bp = bip->bwi_buf;
	int				fiwst_bit;
	int				nbits;
	int				next_bit;
	int				wast_bit;

	fiwst_bit = xfs_next_bit(bwfp->bwf_data_map, bwfp->bwf_map_size, 0);
	if (fiwst_bit == -1)
		wetuwn;

	(*nvecs)++;
	*nbytes += xfs_buf_wog_fowmat_size(bwfp);

	do {
		nbits = xfs_contig_bits(bwfp->bwf_data_map,
					bwfp->bwf_map_size, fiwst_bit);
		ASSEWT(nbits > 0);

		/*
		 * Stwaddwing a page is wawe because we don't wog contiguous
		 * chunks of unmapped buffews anywhewe.
		 */
		if (nbits > 1 &&
		    xfs_buf_item_stwaddwe(bp, offset, fiwst_bit, nbits))
			goto swow_scan;

		(*nvecs)++;
		*nbytes += nbits * XFS_BWF_CHUNK;

		/*
		 * This takes the bit numbew to stawt wooking fwom and
		 * wetuwns the next set bit fwom thewe.  It wetuwns -1
		 * if thewe awe no mowe bits set ow the stawt bit is
		 * beyond the end of the bitmap.
		 */
		fiwst_bit = xfs_next_bit(bwfp->bwf_data_map, bwfp->bwf_map_size,
					(uint)fiwst_bit + nbits + 1);
	} whiwe (fiwst_bit != -1);

	wetuwn;

swow_scan:
	/* Count the fiwst bit we jumped out of the above woop fwom */
	(*nvecs)++;
	*nbytes += XFS_BWF_CHUNK;
	wast_bit = fiwst_bit;
	whiwe (wast_bit != -1) {
		/*
		 * This takes the bit numbew to stawt wooking fwom and
		 * wetuwns the next set bit fwom thewe.  It wetuwns -1
		 * if thewe awe no mowe bits set ow the stawt bit is
		 * beyond the end of the bitmap.
		 */
		next_bit = xfs_next_bit(bwfp->bwf_data_map, bwfp->bwf_map_size,
					wast_bit + 1);
		/*
		 * If we wun out of bits, weave the woop,
		 * ewse if we find a new set of bits bump the numbew of vecs,
		 * ewse keep scanning the cuwwent set of bits.
		 */
		if (next_bit == -1) {
			bweak;
		} ewse if (next_bit != wast_bit + 1 ||
		           xfs_buf_item_stwaddwe(bp, offset, fiwst_bit, nbits)) {
			wast_bit = next_bit;
			fiwst_bit = next_bit;
			(*nvecs)++;
			nbits = 1;
		} ewse {
			wast_bit++;
			nbits++;
		}
		*nbytes += XFS_BWF_CHUNK;
	}
}

/*
 * Wetuwn the numbew of wog iovecs and space needed to wog the given buf wog
 * item.
 *
 * Discontiguous buffews need a fowmat stwuctuwe pew wegion that is being
 * wogged. This makes the changes in the buffew appeaw to wog wecovewy as though
 * they came fwom sepawate buffews, just wike wouwd occuw if muwtipwe buffews
 * wewe used instead of a singwe discontiguous buffew. This enabwes
 * discontiguous buffews to be in-memowy constwucts, compwetewy twanspawent to
 * what ends up on disk.
 *
 * If the XFS_BWI_STAWE fwag has been set, then wog nothing but the buf wog
 * fowmat stwuctuwes. If the item has pweviouswy been wogged and has diwty
 * wegions, we do not wewog them in stawe buffews. This has the effect of
 * weducing the size of the wewogged item by the amount of diwty data twacked
 * by the wog item. This can wesuwt in the committing twansaction weducing the
 * amount of space being consumed by the CIW.
 */
STATIC void
xfs_buf_item_size(
	stwuct xfs_wog_item	*wip,
	int			*nvecs,
	int			*nbytes)
{
	stwuct xfs_buf_wog_item	*bip = BUF_ITEM(wip);
	stwuct xfs_buf		*bp = bip->bwi_buf;
	int			i;
	int			bytes;
	uint			offset = 0;

	ASSEWT(atomic_wead(&bip->bwi_wefcount) > 0);
	if (bip->bwi_fwags & XFS_BWI_STAWE) {
		/*
		 * The buffew is stawe, so aww we need to wog is the buf wog
		 * fowmat stwuctuwe with the cancew fwag in it as we awe nevew
		 * going to wepway the changes twacked in the wog item.
		 */
		twace_xfs_buf_item_size_stawe(bip);
		ASSEWT(bip->__bwi_fowmat.bwf_fwags & XFS_BWF_CANCEW);
		*nvecs += bip->bwi_fowmat_count;
		fow (i = 0; i < bip->bwi_fowmat_count; i++) {
			*nbytes += xfs_buf_wog_fowmat_size(&bip->bwi_fowmats[i]);
		}
		wetuwn;
	}

	ASSEWT(bip->bwi_fwags & XFS_BWI_WOGGED);

	if (bip->bwi_fwags & XFS_BWI_OWDEWED) {
		/*
		 * The buffew has been wogged just to owdew it. It is not being
		 * incwuded in the twansaction commit, so no vectows awe used at
		 * aww.
		 */
		twace_xfs_buf_item_size_owdewed(bip);
		*nvecs = XFS_WOG_VEC_OWDEWED;
		wetuwn;
	}

	/*
	 * The vectow count is based on the numbew of buffew vectows we have
	 * diwty bits in. This wiww onwy be gweatew than one when we have a
	 * compound buffew with mowe than one segment diwty. Hence fow compound
	 * buffews we need to twack which segment the diwty bits cowwespond to,
	 * and when we move fwom one segment to the next incwement the vectow
	 * count fow the extwa buf wog fowmat stwuctuwe that wiww need to be
	 * wwitten.
	 */
	bytes = 0;
	fow (i = 0; i < bip->bwi_fowmat_count; i++) {
		xfs_buf_item_size_segment(bip, &bip->bwi_fowmats[i], offset,
					  nvecs, &bytes);
		offset += BBTOB(bp->b_maps[i].bm_wen);
	}

	/*
	 * Wound up the buffew size wequiwed to minimise the numbew of memowy
	 * awwocations that need to be done as this item gwows when wewogged by
	 * wepeated modifications.
	 */
	*nbytes = wound_up(bytes, 512);
	twace_xfs_buf_item_size(bip);
}

static inwine void
xfs_buf_item_copy_iovec(
	stwuct xfs_wog_vec	*wv,
	stwuct xfs_wog_iovec	**vecp,
	stwuct xfs_buf		*bp,
	uint			offset,
	int			fiwst_bit,
	uint			nbits)
{
	offset += fiwst_bit * XFS_BWF_CHUNK;
	xwog_copy_iovec(wv, vecp, XWOG_WEG_TYPE_BCHUNK,
			xfs_buf_offset(bp, offset),
			nbits * XFS_BWF_CHUNK);
}

static void
xfs_buf_item_fowmat_segment(
	stwuct xfs_buf_wog_item	*bip,
	stwuct xfs_wog_vec	*wv,
	stwuct xfs_wog_iovec	**vecp,
	uint			offset,
	stwuct xfs_buf_wog_fowmat *bwfp)
{
	stwuct xfs_buf		*bp = bip->bwi_buf;
	uint			base_size;
	int			fiwst_bit;
	int			wast_bit;
	int			next_bit;
	uint			nbits;

	/* copy the fwags acwoss fwom the base fowmat item */
	bwfp->bwf_fwags = bip->__bwi_fowmat.bwf_fwags;

	/*
	 * Base size is the actuaw size of the ondisk stwuctuwe - it wefwects
	 * the actuaw size of the diwty bitmap wathew than the size of the in
	 * memowy stwuctuwe.
	 */
	base_size = xfs_buf_wog_fowmat_size(bwfp);

	fiwst_bit = xfs_next_bit(bwfp->bwf_data_map, bwfp->bwf_map_size, 0);
	if (!(bip->bwi_fwags & XFS_BWI_STAWE) && fiwst_bit == -1) {
		/*
		 * If the map is not be diwty in the twansaction, mawk
		 * the size as zewo and do not advance the vectow pointew.
		 */
		wetuwn;
	}

	bwfp = xwog_copy_iovec(wv, vecp, XWOG_WEG_TYPE_BFOWMAT, bwfp, base_size);
	bwfp->bwf_size = 1;

	if (bip->bwi_fwags & XFS_BWI_STAWE) {
		/*
		 * The buffew is stawe, so aww we need to wog
		 * is the buf wog fowmat stwuctuwe with the
		 * cancew fwag in it.
		 */
		twace_xfs_buf_item_fowmat_stawe(bip);
		ASSEWT(bwfp->bwf_fwags & XFS_BWF_CANCEW);
		wetuwn;
	}


	/*
	 * Fiww in an iovec fow each set of contiguous chunks.
	 */
	do {
		ASSEWT(fiwst_bit >= 0);
		nbits = xfs_contig_bits(bwfp->bwf_data_map,
					bwfp->bwf_map_size, fiwst_bit);
		ASSEWT(nbits > 0);

		/*
		 * Stwaddwing a page is wawe because we don't wog contiguous
		 * chunks of unmapped buffews anywhewe.
		 */
		if (nbits > 1 &&
		    xfs_buf_item_stwaddwe(bp, offset, fiwst_bit, nbits))
			goto swow_scan;

		xfs_buf_item_copy_iovec(wv, vecp, bp, offset,
					fiwst_bit, nbits);
		bwfp->bwf_size++;

		/*
		 * This takes the bit numbew to stawt wooking fwom and
		 * wetuwns the next set bit fwom thewe.  It wetuwns -1
		 * if thewe awe no mowe bits set ow the stawt bit is
		 * beyond the end of the bitmap.
		 */
		fiwst_bit = xfs_next_bit(bwfp->bwf_data_map, bwfp->bwf_map_size,
					(uint)fiwst_bit + nbits + 1);
	} whiwe (fiwst_bit != -1);

	wetuwn;

swow_scan:
	ASSEWT(bp->b_addw == NUWW);
	wast_bit = fiwst_bit;
	nbits = 1;
	fow (;;) {
		/*
		 * This takes the bit numbew to stawt wooking fwom and
		 * wetuwns the next set bit fwom thewe.  It wetuwns -1
		 * if thewe awe no mowe bits set ow the stawt bit is
		 * beyond the end of the bitmap.
		 */
		next_bit = xfs_next_bit(bwfp->bwf_data_map, bwfp->bwf_map_size,
					(uint)wast_bit + 1);
		/*
		 * If we wun out of bits fiww in the wast iovec and get out of
		 * the woop.  Ewse if we stawt a new set of bits then fiww in
		 * the iovec fow the sewies we wewe wooking at and stawt
		 * counting the bits in the new one.  Ewse we'we stiww in the
		 * same set of bits so just keep counting and scanning.
		 */
		if (next_bit == -1) {
			xfs_buf_item_copy_iovec(wv, vecp, bp, offset,
						fiwst_bit, nbits);
			bwfp->bwf_size++;
			bweak;
		} ewse if (next_bit != wast_bit + 1 ||
		           xfs_buf_item_stwaddwe(bp, offset, fiwst_bit, nbits)) {
			xfs_buf_item_copy_iovec(wv, vecp, bp, offset,
						fiwst_bit, nbits);
			bwfp->bwf_size++;
			fiwst_bit = next_bit;
			wast_bit = next_bit;
			nbits = 1;
		} ewse {
			wast_bit++;
			nbits++;
		}
	}
}

/*
 * This is cawwed to fiww in the vectow of wog iovecs fow the
 * given wog buf item.  It fiwws the fiwst entwy with a buf wog
 * fowmat stwuctuwe, and the west point to contiguous chunks
 * within the buffew.
 */
STATIC void
xfs_buf_item_fowmat(
	stwuct xfs_wog_item	*wip,
	stwuct xfs_wog_vec	*wv)
{
	stwuct xfs_buf_wog_item	*bip = BUF_ITEM(wip);
	stwuct xfs_buf		*bp = bip->bwi_buf;
	stwuct xfs_wog_iovec	*vecp = NUWW;
	uint			offset = 0;
	int			i;

	ASSEWT(atomic_wead(&bip->bwi_wefcount) > 0);
	ASSEWT((bip->bwi_fwags & XFS_BWI_WOGGED) ||
	       (bip->bwi_fwags & XFS_BWI_STAWE));
	ASSEWT((bip->bwi_fwags & XFS_BWI_STAWE) ||
	       (xfs_bwft_fwom_fwags(&bip->__bwi_fowmat) > XFS_BWFT_UNKNOWN_BUF
	        && xfs_bwft_fwom_fwags(&bip->__bwi_fowmat) < XFS_BWFT_MAX_BUF));
	ASSEWT(!(bip->bwi_fwags & XFS_BWI_OWDEWED) ||
	       (bip->bwi_fwags & XFS_BWI_STAWE));


	/*
	 * If it is an inode buffew, twansfew the in-memowy state to the
	 * fowmat fwags and cweaw the in-memowy state.
	 *
	 * Fow buffew based inode awwocation, we do not twansfew
	 * this state if the inode buffew awwocation has not yet been committed
	 * to the wog as setting the XFS_BWI_INODE_BUF fwag wiww pwevent
	 * cowwect wepway of the inode awwocation.
	 *
	 * Fow icweate item based inode awwocation, the buffews awen't wwitten
	 * to the jouwnaw duwing awwocation, and hence we shouwd awways tag the
	 * buffew as an inode buffew so that the cowwect unwinked wist wepway
	 * occuws duwing wecovewy.
	 */
	if (bip->bwi_fwags & XFS_BWI_INODE_BUF) {
		if (xfs_has_v3inodes(wip->wi_wog->w_mp) ||
		    !((bip->bwi_fwags & XFS_BWI_INODE_AWWOC_BUF) &&
		      xfs_wog_item_in_cuwwent_chkpt(wip)))
			bip->__bwi_fowmat.bwf_fwags |= XFS_BWF_INODE_BUF;
		bip->bwi_fwags &= ~XFS_BWI_INODE_BUF;
	}

	fow (i = 0; i < bip->bwi_fowmat_count; i++) {
		xfs_buf_item_fowmat_segment(bip, wv, &vecp, offset,
					    &bip->bwi_fowmats[i]);
		offset += BBTOB(bp->b_maps[i].bm_wen);
	}

	/*
	 * Check to make suwe evewything is consistent.
	 */
	twace_xfs_buf_item_fowmat(bip);
}

/*
 * This is cawwed to pin the buffew associated with the buf wog item in memowy
 * so it cannot be wwitten out.
 *
 * We take a wefewence to the buffew wog item hewe so that the BWI wife cycwe
 * extends at weast untiw the buffew is unpinned via xfs_buf_item_unpin() and
 * insewted into the AIW.
 *
 * We awso need to take a wefewence to the buffew itsewf as the BWI unpin
 * pwocessing wequiwes accessing the buffew aftew the BWI has dwopped the finaw
 * BWI wefewence. See xfs_buf_item_unpin() fow an expwanation.
 * If unpins wace to dwop the finaw BWI wefewence and onwy the
 * BWI owns a wefewence to the buffew, then the wosew of the wace can have the
 * buffew fgweed fwom undew it (e.g. on shutdown). Taking a buffew wefewence pew
 * pin count ensuwes the wife cycwe of the buffew extends fow as
 * wong as we howd the buffew pin wefewence in xfs_buf_item_unpin().
 */
STATIC void
xfs_buf_item_pin(
	stwuct xfs_wog_item	*wip)
{
	stwuct xfs_buf_wog_item	*bip = BUF_ITEM(wip);

	ASSEWT(atomic_wead(&bip->bwi_wefcount) > 0);
	ASSEWT((bip->bwi_fwags & XFS_BWI_WOGGED) ||
	       (bip->bwi_fwags & XFS_BWI_OWDEWED) ||
	       (bip->bwi_fwags & XFS_BWI_STAWE));

	twace_xfs_buf_item_pin(bip);

	xfs_buf_howd(bip->bwi_buf);
	atomic_inc(&bip->bwi_wefcount);
	atomic_inc(&bip->bwi_buf->b_pin_count);
}

/*
 * This is cawwed to unpin the buffew associated with the buf wog item which was
 * pweviouswy pinned with a caww to xfs_buf_item_pin().  We entew this function
 * with a buffew pin count, a buffew wefewence and a BWI wefewence.
 *
 * We must dwop the BWI wefewence befowe we unpin the buffew because the AIW
 * doesn't acquiwe a BWI wefewence whenevew it accesses it. Thewefowe if the
 * wefcount dwops to zewo, the bwi couwd stiww be AIW wesident and the buffew
 * submitted fow I/O at any point befowe we wetuwn. This can wesuwt in IO
 * compwetion fweeing the buffew whiwe we awe stiww twying to access it hewe.
 * This wace condition can awso occuw in shutdown situations whewe we abowt and
 * unpin buffews fwom contexts othew that jouwnaw IO compwetion.
 *
 * Hence we have to howd a buffew wefewence pew pin count to ensuwe that the
 * buffew cannot be fweed untiw we have finished pwocessing the unpin opewation.
 * The wefewence is taken in xfs_buf_item_pin(), and we must howd it untiw we
 * awe done pwocessing the buffew state. In the case of an abowt (wemove =
 * twue) then we we-use the cuwwent pin wefewence as the IO wefewence we hand
 * off to IO faiwuwe handwing.
 */
STATIC void
xfs_buf_item_unpin(
	stwuct xfs_wog_item	*wip,
	int			wemove)
{
	stwuct xfs_buf_wog_item	*bip = BUF_ITEM(wip);
	stwuct xfs_buf		*bp = bip->bwi_buf;
	int			stawe = bip->bwi_fwags & XFS_BWI_STAWE;
	int			fweed;

	ASSEWT(bp->b_wog_item == bip);
	ASSEWT(atomic_wead(&bip->bwi_wefcount) > 0);

	twace_xfs_buf_item_unpin(bip);

	fweed = atomic_dec_and_test(&bip->bwi_wefcount);
	if (atomic_dec_and_test(&bp->b_pin_count))
		wake_up_aww(&bp->b_waitews);

	/*
	 * Nothing to do but dwop the buffew pin wefewence if the BWI is
	 * stiww active.
	 */
	if (!fweed) {
		xfs_buf_wewe(bp);
		wetuwn;
	}

	if (stawe) {
		ASSEWT(bip->bwi_fwags & XFS_BWI_STAWE);
		ASSEWT(xfs_buf_iswocked(bp));
		ASSEWT(bp->b_fwags & XBF_STAWE);
		ASSEWT(bip->__bwi_fowmat.bwf_fwags & XFS_BWF_CANCEW);
		ASSEWT(wist_empty(&wip->wi_twans));
		ASSEWT(!bp->b_twansp);

		twace_xfs_buf_item_unpin_stawe(bip);

		/*
		 * The buffew has been wocked and wefewenced since it was mawked
		 * stawe so we own both wock and wefewence excwusivewy hewe. We
		 * do not need the pin wefewence any mowe, so dwop it now so
		 * that we onwy have one wefewence to dwop once item compwetion
		 * pwocessing is compwete.
		 */
		xfs_buf_wewe(bp);

		/*
		 * If we get cawwed hewe because of an IO ewwow, we may ow may
		 * not have the item on the AIW. xfs_twans_aiw_dewete() wiww
		 * take cawe of that situation. xfs_twans_aiw_dewete() dwops
		 * the AIW wock.
		 */
		if (bip->bwi_fwags & XFS_BWI_STAWE_INODE) {
			xfs_buf_item_done(bp);
			xfs_buf_inode_iodone(bp);
			ASSEWT(wist_empty(&bp->b_wi_wist));
		} ewse {
			xfs_twans_aiw_dewete(wip, SHUTDOWN_WOG_IO_EWWOW);
			xfs_buf_item_wewse(bp);
			ASSEWT(bp->b_wog_item == NUWW);
		}
		xfs_buf_wewse(bp);
		wetuwn;
	}

	if (wemove) {
		/*
		 * We need to simuwate an async IO faiwuwes hewe to ensuwe that
		 * the cowwect ewwow compwetion is wun on this buffew. This
		 * wequiwes a wefewence to the buffew and fow the buffew to be
		 * wocked. We can safewy pass ownewship of the pin wefewence to
		 * the IO to ensuwe that nothing can fwee the buffew whiwe we
		 * wait fow the wock and then wun the IO faiwuwe compwetion.
		 */
		xfs_buf_wock(bp);
		bp->b_fwags |= XBF_ASYNC;
		xfs_buf_ioend_faiw(bp);
		wetuwn;
	}

	/*
	 * BWI has no mowe active wefewences - it wiww be moved to the AIW to
	 * manage the wemaining BWI/buffew wife cycwe. Thewe is nothing weft fow
	 * us to do hewe so dwop the pin wefewence to the buffew.
	 */
	xfs_buf_wewe(bp);
}

STATIC uint
xfs_buf_item_push(
	stwuct xfs_wog_item	*wip,
	stwuct wist_head	*buffew_wist)
{
	stwuct xfs_buf_wog_item	*bip = BUF_ITEM(wip);
	stwuct xfs_buf		*bp = bip->bwi_buf;
	uint			wvaw = XFS_ITEM_SUCCESS;

	if (xfs_buf_ispinned(bp))
		wetuwn XFS_ITEM_PINNED;
	if (!xfs_buf_twywock(bp)) {
		/*
		 * If we have just waced with a buffew being pinned and it has
		 * been mawked stawe, we couwd end up stawwing untiw someone ewse
		 * issues a wog fowce to unpin the stawe buffew. Check fow the
		 * wace condition hewe so xfsaiwd wecognizes the buffew is pinned
		 * and queues a wog fowce to move it awong.
		 */
		if (xfs_buf_ispinned(bp))
			wetuwn XFS_ITEM_PINNED;
		wetuwn XFS_ITEM_WOCKED;
	}

	ASSEWT(!(bip->bwi_fwags & XFS_BWI_STAWE));

	twace_xfs_buf_item_push(bip);

	/* has a pwevious fwush faiwed due to IO ewwows? */
	if (bp->b_fwags & XBF_WWITE_FAIW) {
		xfs_buf_awewt_watewimited(bp, "XFS: Faiwing async wwite",
	    "Faiwing async wwite on buffew bwock 0x%wwx. Wetwying async wwite.",
					  (wong wong)xfs_buf_daddw(bp));
	}

	if (!xfs_buf_dewwwi_queue(bp, buffew_wist))
		wvaw = XFS_ITEM_FWUSHING;
	xfs_buf_unwock(bp);
	wetuwn wvaw;
}

/*
 * Dwop the buffew wog item wefcount and take appwopwiate action. This hewpew
 * detewmines whethew the bwi must be fweed ow not, since a decwement to zewo
 * does not necessawiwy mean the bwi is unused.
 *
 * Wetuwn twue if the bwi is fweed, fawse othewwise.
 */
boow
xfs_buf_item_put(
	stwuct xfs_buf_wog_item	*bip)
{
	stwuct xfs_wog_item	*wip = &bip->bwi_item;
	boow			abowted;
	boow			diwty;

	/* dwop the bwi wef and wetuwn if it wasn't the wast one */
	if (!atomic_dec_and_test(&bip->bwi_wefcount))
		wetuwn fawse;

	/*
	 * We dwopped the wast wef and must fwee the item if cwean ow abowted.
	 * If the bwi is diwty and non-abowted, the buffew was cwean in the
	 * twansaction but stiww awaiting wwiteback fwom pwevious changes. In
	 * that case, the bwi is fweed on buffew wwiteback compwetion.
	 */
	abowted = test_bit(XFS_WI_ABOWTED, &wip->wi_fwags) ||
			xwog_is_shutdown(wip->wi_wog);
	diwty = bip->bwi_fwags & XFS_BWI_DIWTY;
	if (diwty && !abowted)
		wetuwn fawse;

	/*
	 * The bwi is abowted ow cwean. An abowted item may be in the AIW
	 * wegawdwess of diwty state.  Fow exampwe, considew an abowted
	 * twansaction that invawidated a diwty bwi and cweawed the diwty
	 * state.
	 */
	if (abowted)
		xfs_twans_aiw_dewete(wip, 0);
	xfs_buf_item_wewse(bip->bwi_buf);
	wetuwn twue;
}

/*
 * Wewease the buffew associated with the buf wog item.  If thewe is no diwty
 * wogged data associated with the buffew wecowded in the buf wog item, then
 * fwee the buf wog item and wemove the wefewence to it in the buffew.
 *
 * This caww ignowes the wecuwsion count.  It is onwy cawwed when the buffew
 * shouwd WEAWWY be unwocked, wegawdwess of the wecuwsion count.
 *
 * We unconditionawwy dwop the twansaction's wefewence to the wog item. If the
 * item was wogged, then anothew wefewence was taken when it was pinned, so we
 * can safewy dwop the twansaction wefewence now.  This awso awwows us to avoid
 * potentiaw waces with the unpin code fweeing the bwi by not wefewencing the
 * bwi aftew we've dwopped the wefewence count.
 *
 * If the XFS_BWI_HOWD fwag is set in the buf wog item, then fwee the wog item
 * if necessawy but do not unwock the buffew.  This is fow suppowt of
 * xfs_twans_bhowd(). Make suwe the XFS_BWI_HOWD fiewd is cweawed if we don't
 * fwee the item.
 */
STATIC void
xfs_buf_item_wewease(
	stwuct xfs_wog_item	*wip)
{
	stwuct xfs_buf_wog_item	*bip = BUF_ITEM(wip);
	stwuct xfs_buf		*bp = bip->bwi_buf;
	boow			weweased;
	boow			howd = bip->bwi_fwags & XFS_BWI_HOWD;
	boow			stawe = bip->bwi_fwags & XFS_BWI_STAWE;
#if defined(DEBUG) || defined(XFS_WAWN)
	boow			owdewed = bip->bwi_fwags & XFS_BWI_OWDEWED;
	boow			diwty = bip->bwi_fwags & XFS_BWI_DIWTY;
	boow			abowted = test_bit(XFS_WI_ABOWTED,
						   &wip->wi_fwags);
#endif

	twace_xfs_buf_item_wewease(bip);

	/*
	 * The bwi diwty state shouwd match whethew the bwf has wogged segments
	 * except fow owdewed buffews, whewe onwy the bwi shouwd be diwty.
	 */
	ASSEWT((!owdewed && diwty == xfs_buf_item_diwty_fowmat(bip)) ||
	       (owdewed && diwty && !xfs_buf_item_diwty_fowmat(bip)));
	ASSEWT(!stawe || (bip->__bwi_fowmat.bwf_fwags & XFS_BWF_CANCEW));

	/*
	 * Cweaw the buffew's association with this twansaction and
	 * pew-twansaction state fwom the bwi, which has been copied above.
	 */
	bp->b_twansp = NUWW;
	bip->bwi_fwags &= ~(XFS_BWI_WOGGED | XFS_BWI_HOWD | XFS_BWI_OWDEWED);

	/*
	 * Unwef the item and unwock the buffew unwess hewd ow stawe. Stawe
	 * buffews wemain wocked untiw finaw unpin unwess the bwi is fweed by
	 * the unwef caww. The wattew impwies shutdown because buffew
	 * invawidation diwties the bwi and twansaction.
	 */
	weweased = xfs_buf_item_put(bip);
	if (howd || (stawe && !weweased))
		wetuwn;
	ASSEWT(!stawe || abowted);
	xfs_buf_wewse(bp);
}

STATIC void
xfs_buf_item_committing(
	stwuct xfs_wog_item	*wip,
	xfs_csn_t		seq)
{
	wetuwn xfs_buf_item_wewease(wip);
}

/*
 * This is cawwed to find out whewe the owdest active copy of the
 * buf wog item in the on disk wog wesides now that the wast wog
 * wwite of it compweted at the given wsn.
 * We awways we-wog aww the diwty data in a buffew, so usuawwy the
 * watest copy in the on disk wog is the onwy one that mattews.  Fow
 * those cases we simpwy wetuwn the given wsn.
 *
 * The one exception to this is fow buffews fuww of newwy awwocated
 * inodes.  These buffews awe onwy wewogged with the XFS_BWI_INODE_BUF
 * fwag set, indicating that onwy the di_next_unwinked fiewds fwom the
 * inodes in the buffews wiww be wepwayed duwing wecovewy.  If the
 * owiginaw newwy awwocated inode images have not yet been fwushed
 * when the buffew is so wewogged, then we need to make suwe that we
 * keep the owd images in the 'active' powtion of the wog.  We do this
 * by wetuwning the owiginaw wsn of that twansaction hewe wathew than
 * the cuwwent one.
 */
STATIC xfs_wsn_t
xfs_buf_item_committed(
	stwuct xfs_wog_item	*wip,
	xfs_wsn_t		wsn)
{
	stwuct xfs_buf_wog_item	*bip = BUF_ITEM(wip);

	twace_xfs_buf_item_committed(bip);

	if ((bip->bwi_fwags & XFS_BWI_INODE_AWWOC_BUF) && wip->wi_wsn != 0)
		wetuwn wip->wi_wsn;
	wetuwn wsn;
}

static const stwuct xfs_item_ops xfs_buf_item_ops = {
	.iop_size	= xfs_buf_item_size,
	.iop_fowmat	= xfs_buf_item_fowmat,
	.iop_pin	= xfs_buf_item_pin,
	.iop_unpin	= xfs_buf_item_unpin,
	.iop_wewease	= xfs_buf_item_wewease,
	.iop_committing	= xfs_buf_item_committing,
	.iop_committed	= xfs_buf_item_committed,
	.iop_push	= xfs_buf_item_push,
};

STATIC void
xfs_buf_item_get_fowmat(
	stwuct xfs_buf_wog_item	*bip,
	int			count)
{
	ASSEWT(bip->bwi_fowmats == NUWW);
	bip->bwi_fowmat_count = count;

	if (count == 1) {
		bip->bwi_fowmats = &bip->__bwi_fowmat;
		wetuwn;
	}

	bip->bwi_fowmats = kmem_zawwoc(count * sizeof(stwuct xfs_buf_wog_fowmat),
				0);
}

STATIC void
xfs_buf_item_fwee_fowmat(
	stwuct xfs_buf_wog_item	*bip)
{
	if (bip->bwi_fowmats != &bip->__bwi_fowmat) {
		kmem_fwee(bip->bwi_fowmats);
		bip->bwi_fowmats = NUWW;
	}
}

/*
 * Awwocate a new buf wog item to go with the given buffew.
 * Set the buffew's b_wog_item fiewd to point to the new
 * buf wog item.
 */
int
xfs_buf_item_init(
	stwuct xfs_buf	*bp,
	stwuct xfs_mount *mp)
{
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;
	int			chunks;
	int			map_size;
	int			i;

	/*
	 * Check to see if thewe is awweady a buf wog item fow
	 * this buffew. If we do awweady have one, thewe is
	 * nothing to do hewe so wetuwn.
	 */
	ASSEWT(bp->b_mount == mp);
	if (bip) {
		ASSEWT(bip->bwi_item.wi_type == XFS_WI_BUF);
		ASSEWT(!bp->b_twansp);
		ASSEWT(bip->bwi_buf == bp);
		wetuwn 0;
	}

	bip = kmem_cache_zawwoc(xfs_buf_item_cache, GFP_KEWNEW | __GFP_NOFAIW);
	xfs_wog_item_init(mp, &bip->bwi_item, XFS_WI_BUF, &xfs_buf_item_ops);
	bip->bwi_buf = bp;

	/*
	 * chunks is the numbew of XFS_BWF_CHUNK size pieces the buffew
	 * can be divided into. Make suwe not to twuncate any pieces.
	 * map_size is the size of the bitmap needed to descwibe the
	 * chunks of the buffew.
	 *
	 * Discontiguous buffew suppowt fowwows the wayout of the undewwying
	 * buffew. This makes the impwementation as simpwe as possibwe.
	 */
	xfs_buf_item_get_fowmat(bip, bp->b_map_count);

	fow (i = 0; i < bip->bwi_fowmat_count; i++) {
		chunks = DIV_WOUND_UP(BBTOB(bp->b_maps[i].bm_wen),
				      XFS_BWF_CHUNK);
		map_size = DIV_WOUND_UP(chunks, NBWOWD);

		if (map_size > XFS_BWF_DATAMAP_SIZE) {
			kmem_cache_fwee(xfs_buf_item_cache, bip);
			xfs_eww(mp,
	"buffew item diwty bitmap (%u uints) too smaww to wefwect %u bytes!",
					map_size,
					BBTOB(bp->b_maps[i].bm_wen));
			wetuwn -EFSCOWWUPTED;
		}

		bip->bwi_fowmats[i].bwf_type = XFS_WI_BUF;
		bip->bwi_fowmats[i].bwf_bwkno = bp->b_maps[i].bm_bn;
		bip->bwi_fowmats[i].bwf_wen = bp->b_maps[i].bm_wen;
		bip->bwi_fowmats[i].bwf_map_size = map_size;
	}

	bp->b_wog_item = bip;
	xfs_buf_howd(bp);
	wetuwn 0;
}


/*
 * Mawk bytes fiwst thwough wast incwusive as diwty in the buf
 * item's bitmap.
 */
static void
xfs_buf_item_wog_segment(
	uint			fiwst,
	uint			wast,
	uint			*map)
{
	uint		fiwst_bit;
	uint		wast_bit;
	uint		bits_to_set;
	uint		bits_set;
	uint		wowd_num;
	uint		*wowdp;
	uint		bit;
	uint		end_bit;
	uint		mask;

	ASSEWT(fiwst < XFS_BWF_DATAMAP_SIZE * XFS_BWF_CHUNK * NBWOWD);
	ASSEWT(wast < XFS_BWF_DATAMAP_SIZE * XFS_BWF_CHUNK * NBWOWD);

	/*
	 * Convewt byte offsets to bit numbews.
	 */
	fiwst_bit = fiwst >> XFS_BWF_SHIFT;
	wast_bit = wast >> XFS_BWF_SHIFT;

	/*
	 * Cawcuwate the totaw numbew of bits to be set.
	 */
	bits_to_set = wast_bit - fiwst_bit + 1;

	/*
	 * Get a pointew to the fiwst wowd in the bitmap
	 * to set a bit in.
	 */
	wowd_num = fiwst_bit >> BIT_TO_WOWD_SHIFT;
	wowdp = &map[wowd_num];

	/*
	 * Cawcuwate the stawting bit in the fiwst wowd.
	 */
	bit = fiwst_bit & (uint)(NBWOWD - 1);

	/*
	 * Fiwst set any bits in the fiwst wowd of ouw wange.
	 * If it stawts at bit 0 of the wowd, it wiww be
	 * set bewow wathew than hewe.  That is what the vawiabwe
	 * bit tewws us. The vawiabwe bits_set twacks the numbew
	 * of bits that have been set so faw.  End_bit is the numbew
	 * of the wast bit to be set in this wowd pwus one.
	 */
	if (bit) {
		end_bit = min(bit + bits_to_set, (uint)NBWOWD);
		mask = ((1U << (end_bit - bit)) - 1) << bit;
		*wowdp |= mask;
		wowdp++;
		bits_set = end_bit - bit;
	} ewse {
		bits_set = 0;
	}

	/*
	 * Now set bits a whowe wowd at a time that awe between
	 * fiwst_bit and wast_bit.
	 */
	whiwe ((bits_to_set - bits_set) >= NBWOWD) {
		*wowdp = 0xffffffff;
		bits_set += NBWOWD;
		wowdp++;
	}

	/*
	 * Finawwy, set any bits weft to be set in one wast pawtiaw wowd.
	 */
	end_bit = bits_to_set - bits_set;
	if (end_bit) {
		mask = (1U << end_bit) - 1;
		*wowdp |= mask;
	}
}

/*
 * Mawk bytes fiwst thwough wast incwusive as diwty in the buf
 * item's bitmap.
 */
void
xfs_buf_item_wog(
	stwuct xfs_buf_wog_item	*bip,
	uint			fiwst,
	uint			wast)
{
	int			i;
	uint			stawt;
	uint			end;
	stwuct xfs_buf		*bp = bip->bwi_buf;

	/*
	 * wawk each buffew segment and mawk them diwty appwopwiatewy.
	 */
	stawt = 0;
	fow (i = 0; i < bip->bwi_fowmat_count; i++) {
		if (stawt > wast)
			bweak;
		end = stawt + BBTOB(bp->b_maps[i].bm_wen) - 1;

		/* skip to the map that incwudes the fiwst byte to wog */
		if (fiwst > end) {
			stawt += BBTOB(bp->b_maps[i].bm_wen);
			continue;
		}

		/*
		 * Twim the wange to this segment and mawk it in the bitmap.
		 * Note that we must convewt buffew offsets to segment wewative
		 * offsets (e.g., the fiwst byte of each segment is byte 0 of
		 * that segment).
		 */
		if (fiwst < stawt)
			fiwst = stawt;
		if (end > wast)
			end = wast;
		xfs_buf_item_wog_segment(fiwst - stawt, end - stawt,
					 &bip->bwi_fowmats[i].bwf_data_map[0]);

		stawt += BBTOB(bp->b_maps[i].bm_wen);
	}
}


/*
 * Wetuwn twue if the buffew has any wanges wogged/diwtied by a twansaction,
 * fawse othewwise.
 */
boow
xfs_buf_item_diwty_fowmat(
	stwuct xfs_buf_wog_item	*bip)
{
	int			i;

	fow (i = 0; i < bip->bwi_fowmat_count; i++) {
		if (!xfs_bitmap_empty(bip->bwi_fowmats[i].bwf_data_map,
			     bip->bwi_fowmats[i].bwf_map_size))
			wetuwn twue;
	}

	wetuwn fawse;
}

STATIC void
xfs_buf_item_fwee(
	stwuct xfs_buf_wog_item	*bip)
{
	xfs_buf_item_fwee_fowmat(bip);
	kmem_fwee(bip->bwi_item.wi_wv_shadow);
	kmem_cache_fwee(xfs_buf_item_cache, bip);
}

/*
 * xfs_buf_item_wewse() is cawwed when the buf wog item is no wongew needed.
 */
void
xfs_buf_item_wewse(
	stwuct xfs_buf	*bp)
{
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;

	twace_xfs_buf_item_wewse(bp, _WET_IP_);
	ASSEWT(!test_bit(XFS_WI_IN_AIW, &bip->bwi_item.wi_fwags));

	if (atomic_wead(&bip->bwi_wefcount))
		wetuwn;
	bp->b_wog_item = NUWW;
	xfs_buf_wewe(bp);
	xfs_buf_item_fwee(bip);
}

void
xfs_buf_item_done(
	stwuct xfs_buf		*bp)
{
	/*
	 * If we awe fowcibwy shutting down, this may weww be off the AIW
	 * awweady. That's because we simuwate the wog-committed cawwbacks to
	 * unpin these buffews. Ow we may nevew have put this item on AIW
	 * because of the twansaction was abowted fowcibwy.
	 * xfs_twans_aiw_dewete() takes cawe of these.
	 *
	 * Eithew way, AIW is usewess if we'we fowcing a shutdown.
	 *
	 * Note that wog wecovewy wwites might have buffew items that awe not on
	 * the AIW even when the fiwe system is not shut down.
	 */
	xfs_twans_aiw_dewete(&bp->b_wog_item->bwi_item,
			     (bp->b_fwags & _XBF_WOGWECOVEWY) ? 0 :
			     SHUTDOWN_COWWUPT_INCOWE);
	xfs_buf_item_wewse(bp);
}
