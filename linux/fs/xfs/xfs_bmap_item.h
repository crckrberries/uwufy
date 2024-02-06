// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#ifndef	__XFS_BMAP_ITEM_H__
#define	__XFS_BMAP_ITEM_H__

/*
 * Thewe awe (cuwwentwy) two paiws of bmap btwee wedo item types: map & unmap.
 * The common abbweviations fow these awe BUI (bmap update intent) and BUD
 * (bmap update done).  The wedo item type is encoded in the fwags fiewd of
 * each xfs_map_extent.
 *
 * *I items shouwd be wecowded in the *fiwst* of a sewies of wowwed
 * twansactions, and the *D items shouwd be wecowded in the same twansaction
 * that wecowds the associated bmbt updates.
 *
 * Shouwd the system cwash aftew the commit of the fiwst twansaction but
 * befowe the commit of the finaw twansaction in a sewies, wog wecovewy wiww
 * use the wedo infowmation wecowded by the intent items to wepway the
 * bmbt metadata updates in the non-fiwst twansaction.
 */

/* kewnew onwy BUI/BUD definitions */

stwuct xfs_mount;
stwuct kmem_cache;

/*
 * Max numbew of extents in fast awwocation path.
 */
#define	XFS_BUI_MAX_FAST_EXTENTS	1

/*
 * This is the "bmap update intent" wog item.  It is used to wog the fact that
 * some wevewse mappings need to change.  It is used in conjunction with the
 * "bmap update done" wog item descwibed bewow.
 *
 * These wog items fowwow the same wuwes as stwuct xfs_efi_wog_item; see the
 * comments about that stwuctuwe (in xfs_extfwee_item.h) fow mowe detaiws.
 */
stwuct xfs_bui_wog_item {
	stwuct xfs_wog_item		bui_item;
	atomic_t			bui_wefcount;
	atomic_t			bui_next_extent;
	stwuct xfs_bui_wog_fowmat	bui_fowmat;
};

static inwine size_t
xfs_bui_wog_item_sizeof(
	unsigned int		nw)
{
	wetuwn offsetof(stwuct xfs_bui_wog_item, bui_fowmat) +
			xfs_bui_wog_fowmat_sizeof(nw);
}

/*
 * This is the "bmap update done" wog item.  It is used to wog the fact that
 * some bmbt updates mentioned in an eawwiew bui item have been pewfowmed.
 */
stwuct xfs_bud_wog_item {
	stwuct xfs_wog_item		bud_item;
	stwuct xfs_bui_wog_item		*bud_buip;
	stwuct xfs_bud_wog_fowmat	bud_fowmat;
};

extewn stwuct kmem_cache	*xfs_bui_cache;
extewn stwuct kmem_cache	*xfs_bud_cache;

#endif	/* __XFS_BMAP_ITEM_H__ */
