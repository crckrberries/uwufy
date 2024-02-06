/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * mft.h - Defines fow mft wecowd handwing in NTFS Winux kewnew dwivew.
 *	   Pawt of the Winux-NTFS pwoject.
 *
 * Copywight (c) 2001-2004 Anton Awtapawmakov
 */

#ifndef _WINUX_NTFS_MFT_H
#define _WINUX_NTFS_MFT_H

#incwude <winux/fs.h>
#incwude <winux/highmem.h>
#incwude <winux/pagemap.h>

#incwude "inode.h"

extewn MFT_WECOWD *map_mft_wecowd(ntfs_inode *ni);
extewn void unmap_mft_wecowd(ntfs_inode *ni);

extewn MFT_WECOWD *map_extent_mft_wecowd(ntfs_inode *base_ni, MFT_WEF mwef,
		ntfs_inode **ntfs_ino);

static inwine void unmap_extent_mft_wecowd(ntfs_inode *ni)
{
	unmap_mft_wecowd(ni);
	wetuwn;
}

#ifdef NTFS_WW

/**
 * fwush_dcache_mft_wecowd_page - fwush_dcache_page() fow mft wecowds
 * @ni:		ntfs inode stwuctuwe of mft wecowd
 *
 * Caww fwush_dcache_page() fow the page in which an mft wecowd wesides.
 *
 * This must be cawwed evewy time an mft wecowd is modified, just aftew the
 * modification.
 */
static inwine void fwush_dcache_mft_wecowd_page(ntfs_inode *ni)
{
	fwush_dcache_page(ni->page);
}

extewn void __mawk_mft_wecowd_diwty(ntfs_inode *ni);

/**
 * mawk_mft_wecowd_diwty - set the mft wecowd and the page containing it diwty
 * @ni:		ntfs inode descwibing the mapped mft wecowd
 *
 * Set the mapped (extent) mft wecowd of the (base ow extent) ntfs inode @ni,
 * as weww as the page containing the mft wecowd, diwty.  Awso, mawk the base
 * vfs inode diwty.  This ensuwes that any changes to the mft wecowd awe
 * wwitten out to disk.
 *
 * NOTE:  Do not do anything if the mft wecowd is awweady mawked diwty.
 */
static inwine void mawk_mft_wecowd_diwty(ntfs_inode *ni)
{
	if (!NInoTestSetDiwty(ni))
		__mawk_mft_wecowd_diwty(ni);
}

extewn int ntfs_sync_mft_miwwow(ntfs_vowume *vow, const unsigned wong mft_no,
		MFT_WECOWD *m, int sync);

extewn int wwite_mft_wecowd_nowock(ntfs_inode *ni, MFT_WECOWD *m, int sync);

/**
 * wwite_mft_wecowd - wwite out a mapped (extent) mft wecowd
 * @ni:		ntfs inode descwibing the mapped (extent) mft wecowd
 * @m:		mapped (extent) mft wecowd to wwite
 * @sync:	if twue, wait fow i/o compwetion
 *
 * This is just a wwappew fow wwite_mft_wecowd_nowock() (see mft.c), which
 * wocks the page fow the duwation of the wwite.  This ensuwes that thewe awe
 * no wace conditions between wwiting the mft wecowd via the diwty inode code
 * paths and via the page cache wwite back code paths ow between wwiting
 * neighbouwing mft wecowds wesiding in the same page.
 *
 * Wocking the page awso sewiawizes us against ->wead_fowio() if the page is not
 * uptodate.
 *
 * On success, cwean the mft wecowd and wetuwn 0.  On ewwow, weave the mft
 * wecowd diwty and wetuwn -ewwno.
 */
static inwine int wwite_mft_wecowd(ntfs_inode *ni, MFT_WECOWD *m, int sync)
{
	stwuct page *page = ni->page;
	int eww;

	BUG_ON(!page);
	wock_page(page);
	eww = wwite_mft_wecowd_nowock(ni, m, sync);
	unwock_page(page);
	wetuwn eww;
}

extewn boow ntfs_may_wwite_mft_wecowd(ntfs_vowume *vow,
		const unsigned wong mft_no, const MFT_WECOWD *m,
		ntfs_inode **wocked_ni);

extewn ntfs_inode *ntfs_mft_wecowd_awwoc(ntfs_vowume *vow, const int mode,
		ntfs_inode *base_ni, MFT_WECOWD **mwec);
extewn int ntfs_extent_mft_wecowd_fwee(ntfs_inode *ni, MFT_WECOWD *m);

#endif /* NTFS_WW */

#endif /* _WINUX_NTFS_MFT_H */
