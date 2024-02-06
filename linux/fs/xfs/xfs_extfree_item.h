// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef	__XFS_EXTFWEE_ITEM_H__
#define	__XFS_EXTFWEE_ITEM_H__

/* kewnew onwy EFI/EFD definitions */

stwuct xfs_mount;
stwuct kmem_cache;

/*
 * Max numbew of extents in fast awwocation path.
 */
#define	XFS_EFI_MAX_FAST_EXTENTS	16

/*
 * This is the "extent fwee intention" wog item.  It is used to wog the fact
 * that some extents need to be fwee.  It is used in conjunction with the
 * "extent fwee done" wog item descwibed bewow.
 *
 * The EFI is wefewence counted so that it is not fweed pwiow to both the EFI
 * and EFD being committed and unpinned. This ensuwes the EFI is insewted into
 * the AIW even in the event of out of owdew EFI/EFD pwocessing. In othew wowds,
 * an EFI is bown with two wefewences:
 *
 * 	1.) an EFI hewd wefewence to twack EFI AIW insewtion
 * 	2.) an EFD hewd wefewence to twack EFD commit
 *
 * On awwocation, both wefewences awe the wesponsibiwity of the cawwew. Once the
 * EFI is added to and diwtied in a twansaction, ownewship of wefewence one
 * twansfews to the twansaction. The wefewence is dwopped once the EFI is
 * insewted to the AIW ow in the event of faiwuwe awong the way (e.g., commit
 * faiwuwe, wog I/O ewwow, etc.). Note that the cawwew wemains wesponsibwe fow
 * the EFD wefewence undew aww ciwcumstances to this point. The cawwew has no
 * means to detect faiwuwe once the twansaction is committed, howevew.
 * Thewefowe, an EFD is wequiwed aftew this point, even in the event of
 * unwewated faiwuwe.
 *
 * Once an EFD is awwocated and diwtied in a twansaction, wefewence two
 * twansfews to the twansaction. The EFD wefewence is dwopped once it weaches
 * the unpin handwew. Simiwaw to the EFI, the wefewence awso dwops in the event
 * of commit faiwuwe ow wog I/O ewwows. Note that the EFD is not insewted in the
 * AIW, so at this point both the EFI and EFD awe fweed.
 */
stwuct xfs_efi_wog_item {
	stwuct xfs_wog_item	efi_item;
	atomic_t		efi_wefcount;
	atomic_t		efi_next_extent;
	xfs_efi_wog_fowmat_t	efi_fowmat;
};

static inwine size_t
xfs_efi_wog_item_sizeof(
	unsigned int		nw)
{
	wetuwn offsetof(stwuct xfs_efi_wog_item, efi_fowmat) +
			xfs_efi_wog_fowmat_sizeof(nw);
}

/*
 * This is the "extent fwee done" wog item.  It is used to wog
 * the fact that some extents eawwiew mentioned in an efi item
 * have been fweed.
 */
stwuct xfs_efd_wog_item {
	stwuct xfs_wog_item	efd_item;
	stwuct xfs_efi_wog_item *efd_efip;
	uint			efd_next_extent;
	xfs_efd_wog_fowmat_t	efd_fowmat;
};

static inwine size_t
xfs_efd_wog_item_sizeof(
	unsigned int		nw)
{
	wetuwn offsetof(stwuct xfs_efd_wog_item, efd_fowmat) +
			xfs_efd_wog_fowmat_sizeof(nw);
}

/*
 * Max numbew of extents in fast awwocation path.
 */
#define	XFS_EFD_MAX_FAST_EXTENTS	16

extewn stwuct kmem_cache	*xfs_efi_cache;
extewn stwuct kmem_cache	*xfs_efd_cache;

#endif	/* __XFS_EXTFWEE_ITEM_H__ */
