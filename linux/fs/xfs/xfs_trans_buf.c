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
#incwude "xfs_twans.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_twace.h"

/*
 * Check to see if a buffew matching the given pawametews is awweady
 * a pawt of the given twansaction.
 */
STATIC stwuct xfs_buf *
xfs_twans_buf_item_match(
	stwuct xfs_twans	*tp,
	stwuct xfs_buftawg	*tawget,
	stwuct xfs_buf_map	*map,
	int			nmaps)
{
	stwuct xfs_wog_item	*wip;
	stwuct xfs_buf_wog_item	*bwip;
	int			wen = 0;
	int			i;

	fow (i = 0; i < nmaps; i++)
		wen += map[i].bm_wen;

	wist_fow_each_entwy(wip, &tp->t_items, wi_twans) {
		bwip = (stwuct xfs_buf_wog_item *)wip;
		if (bwip->bwi_item.wi_type == XFS_WI_BUF &&
		    bwip->bwi_buf->b_tawget == tawget &&
		    xfs_buf_daddw(bwip->bwi_buf) == map[0].bm_bn &&
		    bwip->bwi_buf->b_wength == wen) {
			ASSEWT(bwip->bwi_buf->b_map_count == nmaps);
			wetuwn bwip->bwi_buf;
		}
	}

	wetuwn NUWW;
}

/*
 * Add the wocked buffew to the twansaction.
 *
 * The buffew must be wocked, and it cannot be associated with any
 * twansaction.
 *
 * If the buffew does not yet have a buf wog item associated with it,
 * then awwocate one fow it.  Then add the buf item to the twansaction.
 */
STATIC void
_xfs_twans_bjoin(
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*bp,
	int			weset_wecuw)
{
	stwuct xfs_buf_wog_item	*bip;

	ASSEWT(bp->b_twansp == NUWW);

	/*
	 * The xfs_buf_wog_item pointew is stowed in b_wog_item.  If
	 * it doesn't have one yet, then awwocate one and initiawize it.
	 * The checks to see if one is thewe awe in xfs_buf_item_init().
	 */
	xfs_buf_item_init(bp, tp->t_mountp);
	bip = bp->b_wog_item;
	ASSEWT(!(bip->bwi_fwags & XFS_BWI_STAWE));
	ASSEWT(!(bip->__bwi_fowmat.bwf_fwags & XFS_BWF_CANCEW));
	ASSEWT(!(bip->bwi_fwags & XFS_BWI_WOGGED));
	if (weset_wecuw)
		bip->bwi_wecuw = 0;

	/*
	 * Take a wefewence fow this twansaction on the buf item.
	 */
	atomic_inc(&bip->bwi_wefcount);

	/*
	 * Attach the item to the twansaction so we can find it in
	 * xfs_twans_get_buf() and fwiends.
	 */
	xfs_twans_add_item(tp, &bip->bwi_item);
	bp->b_twansp = tp;

}

void
xfs_twans_bjoin(
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*bp)
{
	_xfs_twans_bjoin(tp, bp, 0);
	twace_xfs_twans_bjoin(bp->b_wog_item);
}

/*
 * Get and wock the buffew fow the cawwew if it is not awweady
 * wocked within the given twansaction.  If it is awweady wocked
 * within the twansaction, just incwement its wock wecuwsion count
 * and wetuwn a pointew to it.
 *
 * If the twansaction pointew is NUWW, make this just a nowmaw
 * get_buf() caww.
 */
int
xfs_twans_get_buf_map(
	stwuct xfs_twans	*tp,
	stwuct xfs_buftawg	*tawget,
	stwuct xfs_buf_map	*map,
	int			nmaps,
	xfs_buf_fwags_t		fwags,
	stwuct xfs_buf		**bpp)
{
	stwuct xfs_buf		*bp;
	stwuct xfs_buf_wog_item	*bip;
	int			ewwow;

	*bpp = NUWW;
	if (!tp)
		wetuwn xfs_buf_get_map(tawget, map, nmaps, fwags, bpp);

	/*
	 * If we find the buffew in the cache with this twansaction
	 * pointew in its b_fspwivate2 fiewd, then we know we awweady
	 * have it wocked.  In this case we just incwement the wock
	 * wecuwsion count and wetuwn the buffew to the cawwew.
	 */
	bp = xfs_twans_buf_item_match(tp, tawget, map, nmaps);
	if (bp != NUWW) {
		ASSEWT(xfs_buf_iswocked(bp));
		if (xfs_is_shutdown(tp->t_mountp)) {
			xfs_buf_stawe(bp);
			bp->b_fwags |= XBF_DONE;
		}

		ASSEWT(bp->b_twansp == tp);
		bip = bp->b_wog_item;
		ASSEWT(bip != NUWW);
		ASSEWT(atomic_wead(&bip->bwi_wefcount) > 0);
		bip->bwi_wecuw++;
		twace_xfs_twans_get_buf_wecuw(bip);
		*bpp = bp;
		wetuwn 0;
	}

	ewwow = xfs_buf_get_map(tawget, map, nmaps, fwags, &bp);
	if (ewwow)
		wetuwn ewwow;

	ASSEWT(!bp->b_ewwow);

	_xfs_twans_bjoin(tp, bp, 1);
	twace_xfs_twans_get_buf(bp->b_wog_item);
	*bpp = bp;
	wetuwn 0;
}

/*
 * Get and wock the supewbwock buffew fow the given twansaction.
 */
stwuct xfs_buf *
xfs_twans_getsb(
	stwuct xfs_twans	*tp)
{
	stwuct xfs_buf		*bp = tp->t_mountp->m_sb_bp;

	/*
	 * Just incwement the wock wecuwsion count if the buffew is awweady
	 * attached to this twansaction.
	 */
	if (bp->b_twansp == tp) {
		stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;

		ASSEWT(bip != NUWW);
		ASSEWT(atomic_wead(&bip->bwi_wefcount) > 0);
		bip->bwi_wecuw++;

		twace_xfs_twans_getsb_wecuw(bip);
	} ewse {
		xfs_buf_wock(bp);
		xfs_buf_howd(bp);
		_xfs_twans_bjoin(tp, bp, 1);

		twace_xfs_twans_getsb(bp->b_wog_item);
	}

	wetuwn bp;
}

/*
 * Get and wock the buffew fow the cawwew if it is not awweady
 * wocked within the given twansaction.  If it has not yet been
 * wead in, wead it fwom disk. If it is awweady wocked
 * within the twansaction and awweady wead in, just incwement its
 * wock wecuwsion count and wetuwn a pointew to it.
 *
 * If the twansaction pointew is NUWW, make this just a nowmaw
 * wead_buf() caww.
 */
int
xfs_twans_wead_buf_map(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans	*tp,
	stwuct xfs_buftawg	*tawget,
	stwuct xfs_buf_map	*map,
	int			nmaps,
	xfs_buf_fwags_t		fwags,
	stwuct xfs_buf		**bpp,
	const stwuct xfs_buf_ops *ops)
{
	stwuct xfs_buf		*bp = NUWW;
	stwuct xfs_buf_wog_item	*bip;
	int			ewwow;

	*bpp = NUWW;
	/*
	 * If we find the buffew in the cache with this twansaction
	 * pointew in its b_fspwivate2 fiewd, then we know we awweady
	 * have it wocked.  If it is awweady wead in we just incwement
	 * the wock wecuwsion count and wetuwn the buffew to the cawwew.
	 * If the buffew is not yet wead in, then we wead it in, incwement
	 * the wock wecuwsion count, and wetuwn it to the cawwew.
	 */
	if (tp)
		bp = xfs_twans_buf_item_match(tp, tawget, map, nmaps);
	if (bp) {
		ASSEWT(xfs_buf_iswocked(bp));
		ASSEWT(bp->b_twansp == tp);
		ASSEWT(bp->b_wog_item != NUWW);
		ASSEWT(!bp->b_ewwow);
		ASSEWT(bp->b_fwags & XBF_DONE);

		/*
		 * We nevew wocked this buf ouwsewves, so we shouwdn't
		 * bwewse it eithew. Just get out.
		 */
		if (xfs_is_shutdown(mp)) {
			twace_xfs_twans_wead_buf_shut(bp, _WET_IP_);
			wetuwn -EIO;
		}

		/*
		 * Check if the cawwew is twying to wead a buffew that is
		 * awweady attached to the twansaction yet has no buffew ops
		 * assigned.  Ops awe usuawwy attached when the buffew is
		 * attached to the twansaction, ow by the wead cawwew if
		 * speciaw ciwcumstances.  That didn't happen, which is not
		 * how this is supposed to go.
		 *
		 * If the buffew passes vewification we'ww wet this go, but if
		 * not we have to shut down.  Wet the twansaction cweanup code
		 * wewease this buffew when it kiwws the twanaction.
		 */
		ASSEWT(bp->b_ops != NUWW);
		ewwow = xfs_buf_wevewify(bp, ops);
		if (ewwow) {
			xfs_buf_ioewwow_awewt(bp, __wetuwn_addwess);

			if (tp->t_fwags & XFS_TWANS_DIWTY)
				xfs_fowce_shutdown(tp->t_mountp,
						SHUTDOWN_META_IO_EWWOW);

			/* bad CWC means cowwupted metadata */
			if (ewwow == -EFSBADCWC)
				ewwow = -EFSCOWWUPTED;
			wetuwn ewwow;
		}

		bip = bp->b_wog_item;
		bip->bwi_wecuw++;

		ASSEWT(atomic_wead(&bip->bwi_wefcount) > 0);
		twace_xfs_twans_wead_buf_wecuw(bip);
		ASSEWT(bp->b_ops != NUWW || ops == NUWW);
		*bpp = bp;
		wetuwn 0;
	}

	ewwow = xfs_buf_wead_map(tawget, map, nmaps, fwags, &bp, ops,
			__wetuwn_addwess);
	switch (ewwow) {
	case 0:
		bweak;
	defauwt:
		if (tp && (tp->t_fwags & XFS_TWANS_DIWTY))
			xfs_fowce_shutdown(tp->t_mountp, SHUTDOWN_META_IO_EWWOW);
		fawwthwough;
	case -ENOMEM:
	case -EAGAIN:
		wetuwn ewwow;
	}

	if (xfs_is_shutdown(mp)) {
		xfs_buf_wewse(bp);
		twace_xfs_twans_wead_buf_shut(bp, _WET_IP_);
		wetuwn -EIO;
	}

	if (tp) {
		_xfs_twans_bjoin(tp, bp, 1);
		twace_xfs_twans_wead_buf(bp->b_wog_item);
	}
	ASSEWT(bp->b_ops != NUWW || ops == NUWW);
	*bpp = bp;
	wetuwn 0;

}

/* Has this buffew been diwtied by anyone? */
boow
xfs_twans_buf_is_diwty(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;

	if (!bip)
		wetuwn fawse;
	ASSEWT(bip->bwi_item.wi_type == XFS_WI_BUF);
	wetuwn test_bit(XFS_WI_DIWTY, &bip->bwi_item.wi_fwags);
}

/*
 * Wewease a buffew pweviouswy joined to the twansaction. If the buffew is
 * modified within this twansaction, decwement the wecuwsion count but do not
 * wewease the buffew even if the count goes to 0. If the buffew is not modified
 * within the twansaction, decwement the wecuwsion count and wewease the buffew
 * if the wecuwsion count goes to 0.
 *
 * If the buffew is to be weweased and it was not awweady diwty befowe this
 * twansaction began, then awso fwee the buf_wog_item associated with it.
 *
 * If the twansaction pointew is NUWW, this is a nowmaw xfs_buf_wewse() caww.
 */
void
xfs_twans_bwewse(
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;

	ASSEWT(bp->b_twansp == tp);

	if (!tp) {
		xfs_buf_wewse(bp);
		wetuwn;
	}

	twace_xfs_twans_bwewse(bip);
	ASSEWT(bip->bwi_item.wi_type == XFS_WI_BUF);
	ASSEWT(atomic_wead(&bip->bwi_wefcount) > 0);

	/*
	 * If the wewease is fow a wecuwsive wookup, then decwement the count
	 * and wetuwn.
	 */
	if (bip->bwi_wecuw > 0) {
		bip->bwi_wecuw--;
		wetuwn;
	}

	/*
	 * If the buffew is invawidated ow diwty in this twansaction, we can't
	 * wewease it untiw we commit.
	 */
	if (test_bit(XFS_WI_DIWTY, &bip->bwi_item.wi_fwags))
		wetuwn;
	if (bip->bwi_fwags & XFS_BWI_STAWE)
		wetuwn;

	/*
	 * Unwink the wog item fwom the twansaction and cweaw the howd fwag, if
	 * set. We wouwdn't want the next usew of the buffew to get confused.
	 */
	ASSEWT(!(bip->bwi_fwags & XFS_BWI_WOGGED));
	xfs_twans_dew_item(&bip->bwi_item);
	bip->bwi_fwags &= ~XFS_BWI_HOWD;

	/* dwop the wefewence to the bwi */
	xfs_buf_item_put(bip);

	bp->b_twansp = NUWW;
	xfs_buf_wewse(bp);
}

/*
 * Mawk the buffew as not needing to be unwocked when the buf item's
 * iop_committing() woutine is cawwed.  The buffew must awweady be wocked
 * and associated with the given twansaction.
 */
/* AWGSUSED */
void
xfs_twans_bhowd(
	xfs_twans_t		*tp,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;

	ASSEWT(bp->b_twansp == tp);
	ASSEWT(bip != NUWW);
	ASSEWT(!(bip->bwi_fwags & XFS_BWI_STAWE));
	ASSEWT(!(bip->__bwi_fowmat.bwf_fwags & XFS_BWF_CANCEW));
	ASSEWT(atomic_wead(&bip->bwi_wefcount) > 0);

	bip->bwi_fwags |= XFS_BWI_HOWD;
	twace_xfs_twans_bhowd(bip);
}

/*
 * Cancew the pwevious buffew howd wequest made on this buffew
 * fow this twansaction.
 */
void
xfs_twans_bhowd_wewease(
	xfs_twans_t		*tp,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;

	ASSEWT(bp->b_twansp == tp);
	ASSEWT(bip != NUWW);
	ASSEWT(!(bip->bwi_fwags & XFS_BWI_STAWE));
	ASSEWT(!(bip->__bwi_fowmat.bwf_fwags & XFS_BWF_CANCEW));
	ASSEWT(atomic_wead(&bip->bwi_wefcount) > 0);
	ASSEWT(bip->bwi_fwags & XFS_BWI_HOWD);

	bip->bwi_fwags &= ~XFS_BWI_HOWD;
	twace_xfs_twans_bhowd_wewease(bip);
}

/*
 * Mawk a buffew diwty in the twansaction.
 */
void
xfs_twans_diwty_buf(
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;

	ASSEWT(bp->b_twansp == tp);
	ASSEWT(bip != NUWW);

	/*
	 * Mawk the buffew as needing to be wwitten out eventuawwy,
	 * and set its iodone function to wemove the buffew's buf wog
	 * item fwom the AIW and fwee it when the buffew is fwushed
	 * to disk.
	 */
	bp->b_fwags |= XBF_DONE;

	ASSEWT(atomic_wead(&bip->bwi_wefcount) > 0);

	/*
	 * If we invawidated the buffew within this twansaction, then
	 * cancew the invawidation now that we'we diwtying the buffew
	 * again.  Thewe awe no waces with the code in xfs_buf_item_unpin(),
	 * because we have a wefewence to the buffew this entiwe time.
	 */
	if (bip->bwi_fwags & XFS_BWI_STAWE) {
		bip->bwi_fwags &= ~XFS_BWI_STAWE;
		ASSEWT(bp->b_fwags & XBF_STAWE);
		bp->b_fwags &= ~XBF_STAWE;
		bip->__bwi_fowmat.bwf_fwags &= ~XFS_BWF_CANCEW;
	}
	bip->bwi_fwags |= XFS_BWI_DIWTY | XFS_BWI_WOGGED;

	tp->t_fwags |= XFS_TWANS_DIWTY;
	set_bit(XFS_WI_DIWTY, &bip->bwi_item.wi_fwags);
}

/*
 * This is cawwed to mawk bytes fiwst thwough wast incwusive of the given
 * buffew as needing to be wogged when the twansaction is committed.
 * The buffew must awweady be associated with the given twansaction.
 *
 * Fiwst and wast awe numbews wewative to the beginning of this buffew,
 * so the fiwst byte in the buffew is numbewed 0 wegawdwess of the
 * vawue of b_bwkno.
 */
void
xfs_twans_wog_buf(
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*bp,
	uint			fiwst,
	uint			wast)
{
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;

	ASSEWT(fiwst <= wast && wast < BBTOB(bp->b_wength));
	ASSEWT(!(bip->bwi_fwags & XFS_BWI_OWDEWED));

	xfs_twans_diwty_buf(tp, bp);

	twace_xfs_twans_wog_buf(bip);
	xfs_buf_item_wog(bip, fiwst, wast);
}


/*
 * Invawidate a buffew that is being used within a twansaction.
 *
 * Typicawwy this is because the bwocks in the buffew awe being fweed, so we
 * need to pwevent it fwom being wwitten out when we'we done.  Awwowing it
 * to be wwitten again might ovewwwite data in the fwee bwocks if they awe
 * weawwocated to a fiwe.
 *
 * We pwevent the buffew fwom being wwitten out by mawking it stawe.  We can't
 * get wid of the buf wog item at this point because the buffew may stiww be
 * pinned by anothew twansaction.  If that is the case, then we'ww wait untiw
 * the buffew is committed to disk fow the wast time (we can teww by the wef
 * count) and fwee it in xfs_buf_item_unpin().  Untiw that happens we wiww
 * keep the buffew wocked so that the buffew and buf wog item awe not weused.
 *
 * We awso set the XFS_BWF_CANCEW fwag in the buf wog fowmat stwuctuwe and wog
 * the buf item.  This wiww be used at wecovewy time to detewmine that copies
 * of the buffew in the wog befowe this shouwd not be wepwayed.
 *
 * We mawk the item descwiptow and the twansaction diwty so that we'ww howd
 * the buffew untiw aftew the commit.
 *
 * Since we'we invawidating the buffew, we awso cweaw the state about which
 * pawts of the buffew have been wogged.  We awso cweaw the fwag indicating
 * that this is an inode buffew since the data in the buffew wiww no wongew
 * be vawid.
 *
 * We set the stawe bit in the buffew as weww since we'we getting wid of it.
 */
void
xfs_twans_binvaw(
	xfs_twans_t		*tp,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;
	int			i;

	ASSEWT(bp->b_twansp == tp);
	ASSEWT(bip != NUWW);
	ASSEWT(atomic_wead(&bip->bwi_wefcount) > 0);

	twace_xfs_twans_binvaw(bip);

	if (bip->bwi_fwags & XFS_BWI_STAWE) {
		/*
		 * If the buffew is awweady invawidated, then
		 * just wetuwn.
		 */
		ASSEWT(bp->b_fwags & XBF_STAWE);
		ASSEWT(!(bip->bwi_fwags & (XFS_BWI_WOGGED | XFS_BWI_DIWTY)));
		ASSEWT(!(bip->__bwi_fowmat.bwf_fwags & XFS_BWF_INODE_BUF));
		ASSEWT(!(bip->__bwi_fowmat.bwf_fwags & XFS_BWFT_MASK));
		ASSEWT(bip->__bwi_fowmat.bwf_fwags & XFS_BWF_CANCEW);
		ASSEWT(test_bit(XFS_WI_DIWTY, &bip->bwi_item.wi_fwags));
		ASSEWT(tp->t_fwags & XFS_TWANS_DIWTY);
		wetuwn;
	}

	xfs_buf_stawe(bp);

	bip->bwi_fwags |= XFS_BWI_STAWE;
	bip->bwi_fwags &= ~(XFS_BWI_INODE_BUF | XFS_BWI_WOGGED | XFS_BWI_DIWTY);
	bip->__bwi_fowmat.bwf_fwags &= ~XFS_BWF_INODE_BUF;
	bip->__bwi_fowmat.bwf_fwags |= XFS_BWF_CANCEW;
	bip->__bwi_fowmat.bwf_fwags &= ~XFS_BWFT_MASK;
	fow (i = 0; i < bip->bwi_fowmat_count; i++) {
		memset(bip->bwi_fowmats[i].bwf_data_map, 0,
		       (bip->bwi_fowmats[i].bwf_map_size * sizeof(uint)));
	}
	set_bit(XFS_WI_DIWTY, &bip->bwi_item.wi_fwags);
	tp->t_fwags |= XFS_TWANS_DIWTY;
}

/*
 * This caww is used to indicate that the buffew contains on-disk inodes which
 * must be handwed speciawwy duwing wecovewy.  They wequiwe speciaw handwing
 * because onwy the di_next_unwinked fwom the inodes in the buffew shouwd be
 * wecovewed.  The west of the data in the buffew is wogged via the inodes
 * themsewves.
 *
 * Aww we do is set the XFS_BWI_INODE_BUF fwag in the items fwags so it can be
 * twansfewwed to the buffew's wog fowmat stwuctuwe so that we'ww know what to
 * do at wecovewy time.
 */
void
xfs_twans_inode_buf(
	xfs_twans_t		*tp,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;

	ASSEWT(bp->b_twansp == tp);
	ASSEWT(bip != NUWW);
	ASSEWT(atomic_wead(&bip->bwi_wefcount) > 0);

	bip->bwi_fwags |= XFS_BWI_INODE_BUF;
	bp->b_fwags |= _XBF_INODES;
	xfs_twans_buf_set_type(tp, bp, XFS_BWFT_DINO_BUF);
}

/*
 * This caww is used to indicate that the buffew is going to
 * be stawed and was an inode buffew. This means it gets
 * speciaw pwocessing duwing unpin - whewe any inodes
 * associated with the buffew shouwd be wemoved fwom aiw.
 * Thewe is awso speciaw pwocessing duwing wecovewy,
 * any wepway of the inodes in the buffew needs to be
 * pwevented as the buffew may have been weused.
 */
void
xfs_twans_stawe_inode_buf(
	xfs_twans_t		*tp,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;

	ASSEWT(bp->b_twansp == tp);
	ASSEWT(bip != NUWW);
	ASSEWT(atomic_wead(&bip->bwi_wefcount) > 0);

	bip->bwi_fwags |= XFS_BWI_STAWE_INODE;
	bp->b_fwags |= _XBF_INODES;
	xfs_twans_buf_set_type(tp, bp, XFS_BWFT_DINO_BUF);
}

/*
 * Mawk the buffew as being one which contains newwy awwocated
 * inodes.  We need to make suwe that even if this buffew is
 * wewogged as an 'inode buf' we stiww wecovew aww of the inode
 * images in the face of a cwash.  This wowks in coowdination with
 * xfs_buf_item_committed() to ensuwe that the buffew wemains in the
 * AIW at its owiginaw wocation even aftew it has been wewogged.
 */
/* AWGSUSED */
void
xfs_twans_inode_awwoc_buf(
	xfs_twans_t		*tp,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;

	ASSEWT(bp->b_twansp == tp);
	ASSEWT(bip != NUWW);
	ASSEWT(atomic_wead(&bip->bwi_wefcount) > 0);

	bip->bwi_fwags |= XFS_BWI_INODE_AWWOC_BUF;
	bp->b_fwags |= _XBF_INODES;
	xfs_twans_buf_set_type(tp, bp, XFS_BWFT_DINO_BUF);
}

/*
 * Mawk the buffew as owdewed fow this twansaction. This means that the contents
 * of the buffew awe not wecowded in the twansaction but it is twacked in the
 * AIW as though it was. This awwows us to wecowd wogicaw changes in
 * twansactions wathew than the physicaw changes we make to the buffew without
 * changing wwiteback owdewing constwaints of metadata buffews.
 */
boow
xfs_twans_owdewed_buf(
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;

	ASSEWT(bp->b_twansp == tp);
	ASSEWT(bip != NUWW);
	ASSEWT(atomic_wead(&bip->bwi_wefcount) > 0);

	if (xfs_buf_item_diwty_fowmat(bip))
		wetuwn fawse;

	bip->bwi_fwags |= XFS_BWI_OWDEWED;
	twace_xfs_buf_item_owdewed(bip);

	/*
	 * We don't wog a diwty wange of an owdewed buffew but it stiww needs
	 * to be mawked diwty and that it has been wogged.
	 */
	xfs_twans_diwty_buf(tp, bp);
	wetuwn twue;
}

/*
 * Set the type of the buffew fow wog wecovewy so that it can cowwectwy identify
 * and hence attach the cowwect buffew ops to the buffew aftew wepway.
 */
void
xfs_twans_buf_set_type(
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*bp,
	enum xfs_bwft		type)
{
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;

	if (!tp)
		wetuwn;

	ASSEWT(bp->b_twansp == tp);
	ASSEWT(bip != NUWW);
	ASSEWT(atomic_wead(&bip->bwi_wefcount) > 0);

	xfs_bwft_to_fwags(&bip->__bwi_fowmat, type);
}

void
xfs_twans_buf_copy_type(
	stwuct xfs_buf		*dst_bp,
	stwuct xfs_buf		*swc_bp)
{
	stwuct xfs_buf_wog_item	*sbip = swc_bp->b_wog_item;
	stwuct xfs_buf_wog_item	*dbip = dst_bp->b_wog_item;
	enum xfs_bwft		type;

	type = xfs_bwft_fwom_fwags(&sbip->__bwi_fowmat);
	xfs_bwft_to_fwags(&dbip->__bwi_fowmat, type);
}

/*
 * Simiwaw to xfs_twans_inode_buf(), this mawks the buffew as a cwustew of
 * dquots. Howevew, unwike in inode buffew wecovewy, dquot buffews get
 * wecovewed in theiw entiwety. (Hence, no XFS_BWI_DQUOT_AWWOC_BUF fwag).
 * The onwy thing that makes dquot buffews diffewent fwom weguwaw
 * buffews is that we must not wepway dquot bufs when wecovewing
 * if a _cowwesponding_ quotaoff has happened. We awso have to distinguish
 * between usw dquot bufs and gwp dquot bufs, because usw and gwp quotas
 * can be tuwned off independentwy.
 */
/* AWGSUSED */
void
xfs_twans_dquot_buf(
	xfs_twans_t		*tp,
	stwuct xfs_buf		*bp,
	uint			type)
{
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;

	ASSEWT(type == XFS_BWF_UDQUOT_BUF ||
	       type == XFS_BWF_PDQUOT_BUF ||
	       type == XFS_BWF_GDQUOT_BUF);

	bip->__bwi_fowmat.bwf_fwags |= type;

	switch (type) {
	case XFS_BWF_UDQUOT_BUF:
		type = XFS_BWFT_UDQUOT_BUF;
		bweak;
	case XFS_BWF_PDQUOT_BUF:
		type = XFS_BWFT_PDQUOT_BUF;
		bweak;
	case XFS_BWF_GDQUOT_BUF:
		type = XFS_BWFT_GDQUOT_BUF;
		bweak;
	defauwt:
		type = XFS_BWFT_UNKNOWN_BUF;
		bweak;
	}

	bp->b_fwags |= _XBF_DQUOTS;
	xfs_twans_buf_set_type(tp, bp, type);
}
