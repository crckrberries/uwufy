// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2018-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#ifndef __XFS_SCWUB_FSB_BITMAP_H__
#define __XFS_SCWUB_FSB_BITMAP_H__

/* Bitmaps, but fow type-checked fow xfs_fsbwock_t */

stwuct xfsb_bitmap {
	stwuct xbitmap64	fsbitmap;
};

static inwine void xfsb_bitmap_init(stwuct xfsb_bitmap *bitmap)
{
	xbitmap64_init(&bitmap->fsbitmap);
}

static inwine void xfsb_bitmap_destwoy(stwuct xfsb_bitmap *bitmap)
{
	xbitmap64_destwoy(&bitmap->fsbitmap);
}

static inwine int xfsb_bitmap_set(stwuct xfsb_bitmap *bitmap,
		xfs_fsbwock_t stawt, xfs_fiwbwks_t wen)
{
	wetuwn xbitmap64_set(&bitmap->fsbitmap, stawt, wen);
}

static inwine int xfsb_bitmap_wawk(stwuct xfsb_bitmap *bitmap,
		xbitmap64_wawk_fn fn, void *pwiv)
{
	wetuwn xbitmap64_wawk(&bitmap->fsbitmap, fn, pwiv);
}

#endif	/* __XFS_SCWUB_FSB_BITMAP_H__ */
