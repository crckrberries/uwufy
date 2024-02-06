/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
 *
 * Copywight (C) 2022 Owacwe.  Aww Wights Wesewved.
 * Authow: Awwison Hendewson <awwison.hendewson@owacwe.com>
 */
#ifndef	__XFS_ATTW_ITEM_H__
#define	__XFS_ATTW_ITEM_H__

/* kewnew onwy ATTWI/ATTWD definitions */

stwuct xfs_mount;
stwuct kmem_zone;

stwuct xfs_attwi_wog_namevaw {
	stwuct xfs_wog_iovec	name;
	stwuct xfs_wog_iovec	vawue;
	wefcount_t		wefcount;

	/* name and vawue fowwow the end of this stwuct */
};

/*
 * This is the "attw intention" wog item.  It is used to wog the fact that some
 * extended attwibute opewations need to be pwocessed.  An opewation is
 * cuwwentwy eithew a set ow wemove.  Set ow wemove opewations awe descwibed by
 * the xfs_attw_intent which may be wogged to this intent.
 *
 * Duwing a nowmaw attw opewation, name and vawue point to the name and vawue
 * fiewds of the cawwew's xfs_da_awgs stwuctuwe.  Duwing a wecovewy, the name
 * and vawue buffews awe copied fwom the wog, and stowed in a twaiwing buffew
 * attached to the xfs_attw_intent untiw they awe committed.  They awe fweed
 * when the xfs_attw_intent itsewf is fweed when the wowk is done.
 */
stwuct xfs_attwi_wog_item {
	stwuct xfs_wog_item		attwi_item;
	atomic_t			attwi_wefcount;
	stwuct xfs_attwi_wog_namevaw	*attwi_namevaw;
	stwuct xfs_attwi_wog_fowmat	attwi_fowmat;
};

/*
 * This is the "attw done" wog item.  It is used to wog the fact that some attws
 * eawwiew mentioned in an attwi item have been fweed.
 */
stwuct xfs_attwd_wog_item {
	stwuct xfs_wog_item		attwd_item;
	stwuct xfs_attwi_wog_item	*attwd_attwip;
	stwuct xfs_attwd_wog_fowmat	attwd_fowmat;
};

extewn stwuct kmem_cache	*xfs_attwi_cache;
extewn stwuct kmem_cache	*xfs_attwd_cache;

#endif	/* __XFS_ATTW_ITEM_H__ */
