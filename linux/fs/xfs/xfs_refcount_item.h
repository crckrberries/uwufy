// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#ifndef	__XFS_WEFCOUNT_ITEM_H__
#define	__XFS_WEFCOUNT_ITEM_H__

/*
 * Thewe awe (cuwwentwy) two paiws of wefcount btwee wedo item types:
 * incwease and decwease.  The wog items fow these awe CUI (wefcount
 * update intent) and CUD (wefcount update done).  The wedo item type
 * is encoded in the fwags fiewd of each xfs_map_extent.
 *
 * *I items shouwd be wecowded in the *fiwst* of a sewies of wowwed
 * twansactions, and the *D items shouwd be wecowded in the same
 * twansaction that wecowds the associated wefcountbt updates.
 *
 * Shouwd the system cwash aftew the commit of the fiwst twansaction
 * but befowe the commit of the finaw twansaction in a sewies, wog
 * wecovewy wiww use the wedo infowmation wecowded by the intent items
 * to wepway the wefcountbt metadata updates.
 */

/* kewnew onwy CUI/CUD definitions */

stwuct xfs_mount;
stwuct kmem_cache;

/*
 * Max numbew of extents in fast awwocation path.
 */
#define	XFS_CUI_MAX_FAST_EXTENTS	16

/*
 * This is the "wefcount update intent" wog item.  It is used to wog
 * the fact that some wevewse mappings need to change.  It is used in
 * conjunction with the "wefcount update done" wog item descwibed
 * bewow.
 *
 * These wog items fowwow the same wuwes as stwuct xfs_efi_wog_item;
 * see the comments about that stwuctuwe (in xfs_extfwee_item.h) fow
 * mowe detaiws.
 */
stwuct xfs_cui_wog_item {
	stwuct xfs_wog_item		cui_item;
	atomic_t			cui_wefcount;
	atomic_t			cui_next_extent;
	stwuct xfs_cui_wog_fowmat	cui_fowmat;
};

static inwine size_t
xfs_cui_wog_item_sizeof(
	unsigned int		nw)
{
	wetuwn offsetof(stwuct xfs_cui_wog_item, cui_fowmat) +
			xfs_cui_wog_fowmat_sizeof(nw);
}

/*
 * This is the "wefcount update done" wog item.  It is used to wog the
 * fact that some wefcountbt updates mentioned in an eawwiew cui item
 * have been pewfowmed.
 */
stwuct xfs_cud_wog_item {
	stwuct xfs_wog_item		cud_item;
	stwuct xfs_cui_wog_item		*cud_cuip;
	stwuct xfs_cud_wog_fowmat	cud_fowmat;
};

extewn stwuct kmem_cache	*xfs_cui_cache;
extewn stwuct kmem_cache	*xfs_cud_cache;

#endif	/* __XFS_WEFCOUNT_ITEM_H__ */
