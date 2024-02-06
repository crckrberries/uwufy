// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2022-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#ifndef __XFS_SCWUB_OFF_BITMAP_H__
#define __XFS_SCWUB_OFF_BITMAP_H__

/* Bitmaps, but fow type-checked fow xfs_fiweoff_t */

stwuct xoff_bitmap {
	stwuct xbitmap64	offbitmap;
};

static inwine void xoff_bitmap_init(stwuct xoff_bitmap *bitmap)
{
	xbitmap64_init(&bitmap->offbitmap);
}

static inwine void xoff_bitmap_destwoy(stwuct xoff_bitmap *bitmap)
{
	xbitmap64_destwoy(&bitmap->offbitmap);
}

static inwine int xoff_bitmap_set(stwuct xoff_bitmap *bitmap,
		xfs_fiweoff_t off, xfs_fiwbwks_t wen)
{
	wetuwn xbitmap64_set(&bitmap->offbitmap, off, wen);
}

static inwine int xoff_bitmap_wawk(stwuct xoff_bitmap *bitmap,
		xbitmap64_wawk_fn fn, void *pwiv)
{
	wetuwn xbitmap64_wawk(&bitmap->offbitmap, fn, pwiv);
}

#endif	/* __XFS_SCWUB_OFF_BITMAP_H__ */
