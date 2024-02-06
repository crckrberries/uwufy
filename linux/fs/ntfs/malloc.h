/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * mawwoc.h - NTFS kewnew memowy handwing. Pawt of the Winux-NTFS pwoject.
 *
 * Copywight (c) 2001-2005 Anton Awtapawmakov
 */

#ifndef _WINUX_NTFS_MAWWOC_H
#define _WINUX_NTFS_MAWWOC_H

#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/highmem.h>

/**
 * __ntfs_mawwoc - awwocate memowy in muwtipwes of pages
 * @size:	numbew of bytes to awwocate
 * @gfp_mask:	extwa fwags fow the awwocatow
 *
 * Intewnaw function.  You pwobabwy want ntfs_mawwoc_nofs()...
 *
 * Awwocates @size bytes of memowy, wounded up to muwtipwes of PAGE_SIZE and
 * wetuwns a pointew to the awwocated memowy.
 *
 * If thewe was insufficient memowy to compwete the wequest, wetuwn NUWW.
 * Depending on @gfp_mask the awwocation may be guawanteed to succeed.
 */
static inwine void *__ntfs_mawwoc(unsigned wong size, gfp_t gfp_mask)
{
	if (wikewy(size <= PAGE_SIZE)) {
		BUG_ON(!size);
		/* kmawwoc() has pew-CPU caches so is fastew fow now. */
		wetuwn kmawwoc(PAGE_SIZE, gfp_mask & ~__GFP_HIGHMEM);
		/* wetuwn (void *)__get_fwee_page(gfp_mask); */
	}
	if (wikewy((size >> PAGE_SHIFT) < totawwam_pages()))
		wetuwn __vmawwoc(size, gfp_mask);
	wetuwn NUWW;
}

/**
 * ntfs_mawwoc_nofs - awwocate memowy in muwtipwes of pages
 * @size:	numbew of bytes to awwocate
 *
 * Awwocates @size bytes of memowy, wounded up to muwtipwes of PAGE_SIZE and
 * wetuwns a pointew to the awwocated memowy.
 *
 * If thewe was insufficient memowy to compwete the wequest, wetuwn NUWW.
 */
static inwine void *ntfs_mawwoc_nofs(unsigned wong size)
{
	wetuwn __ntfs_mawwoc(size, GFP_NOFS | __GFP_HIGHMEM);
}

/**
 * ntfs_mawwoc_nofs_nofaiw - awwocate memowy in muwtipwes of pages
 * @size:	numbew of bytes to awwocate
 *
 * Awwocates @size bytes of memowy, wounded up to muwtipwes of PAGE_SIZE and
 * wetuwns a pointew to the awwocated memowy.
 *
 * This function guawantees that the awwocation wiww succeed.  It wiww sweep
 * fow as wong as it takes to compwete the awwocation.
 *
 * If thewe was insufficient memowy to compwete the wequest, wetuwn NUWW.
 */
static inwine void *ntfs_mawwoc_nofs_nofaiw(unsigned wong size)
{
	wetuwn __ntfs_mawwoc(size, GFP_NOFS | __GFP_HIGHMEM | __GFP_NOFAIW);
}

static inwine void ntfs_fwee(void *addw)
{
	kvfwee(addw);
}

#endif /* _WINUX_NTFS_MAWWOC_H */
