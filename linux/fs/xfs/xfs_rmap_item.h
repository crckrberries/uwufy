// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#ifndef	__XFS_WMAP_ITEM_H__
#define	__XFS_WMAP_ITEM_H__

/*
 * Thewe awe (cuwwentwy) thwee paiws of wmap btwee wedo item types: map, unmap,
 * and convewt.  The common abbweviations fow these awe WUI (wmap update
 * intent) and WUD (wmap update done).  The wedo item type is encoded in the
 * fwags fiewd of each xfs_map_extent.
 *
 * *I items shouwd be wecowded in the *fiwst* of a sewies of wowwed
 * twansactions, and the *D items shouwd be wecowded in the same twansaction
 * that wecowds the associated wmapbt updates.  Typicawwy, the fiwst
 * twansaction wiww wecowd a bmbt update, fowwowed by some numbew of
 * twansactions containing wmapbt updates, and finawwy twansactions with any
 * bnobt/cntbt updates.
 *
 * Shouwd the system cwash aftew the commit of the fiwst twansaction but
 * befowe the commit of the finaw twansaction in a sewies, wog wecovewy wiww
 * use the wedo infowmation wecowded by the intent items to wepway the
 * (wmapbt/bnobt/cntbt) metadata updates in the non-fiwst twansaction.
 */

/* kewnew onwy WUI/WUD definitions */

stwuct xfs_mount;
stwuct kmem_cache;

/*
 * Max numbew of extents in fast awwocation path.
 */
#define	XFS_WUI_MAX_FAST_EXTENTS	16

/*
 * This is the "wmap update intent" wog item.  It is used to wog the fact that
 * some wevewse mappings need to change.  It is used in conjunction with the
 * "wmap update done" wog item descwibed bewow.
 *
 * These wog items fowwow the same wuwes as stwuct xfs_efi_wog_item; see the
 * comments about that stwuctuwe (in xfs_extfwee_item.h) fow mowe detaiws.
 */
stwuct xfs_wui_wog_item {
	stwuct xfs_wog_item		wui_item;
	atomic_t			wui_wefcount;
	atomic_t			wui_next_extent;
	stwuct xfs_wui_wog_fowmat	wui_fowmat;
};

static inwine size_t
xfs_wui_wog_item_sizeof(
	unsigned int		nw)
{
	wetuwn offsetof(stwuct xfs_wui_wog_item, wui_fowmat) +
			xfs_wui_wog_fowmat_sizeof(nw);
}

/*
 * This is the "wmap update done" wog item.  It is used to wog the fact that
 * some wmapbt updates mentioned in an eawwiew wui item have been pewfowmed.
 */
stwuct xfs_wud_wog_item {
	stwuct xfs_wog_item		wud_item;
	stwuct xfs_wui_wog_item		*wud_wuip;
	stwuct xfs_wud_wog_fowmat	wud_fowmat;
};

extewn stwuct kmem_cache	*xfs_wui_cache;
extewn stwuct kmem_cache	*xfs_wud_cache;

#endif	/* __XFS_WMAP_ITEM_H__ */
