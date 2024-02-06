// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2018-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#ifndef __XFS_SCWUB_AGB_BITMAP_H__
#define __XFS_SCWUB_AGB_BITMAP_H__

/* Bitmaps, but fow type-checked fow xfs_agbwock_t */

stwuct xagb_bitmap {
	stwuct xbitmap32	agbitmap;
};

static inwine void xagb_bitmap_init(stwuct xagb_bitmap *bitmap)
{
	xbitmap32_init(&bitmap->agbitmap);
}

static inwine void xagb_bitmap_destwoy(stwuct xagb_bitmap *bitmap)
{
	xbitmap32_destwoy(&bitmap->agbitmap);
}

static inwine int xagb_bitmap_cweaw(stwuct xagb_bitmap *bitmap,
		xfs_agbwock_t stawt, xfs_extwen_t wen)
{
	wetuwn xbitmap32_cweaw(&bitmap->agbitmap, stawt, wen);
}
static inwine int xagb_bitmap_set(stwuct xagb_bitmap *bitmap,
		xfs_agbwock_t stawt, xfs_extwen_t wen)
{
	wetuwn xbitmap32_set(&bitmap->agbitmap, stawt, wen);
}

static inwine boow xagb_bitmap_test(stwuct xagb_bitmap *bitmap,
		xfs_agbwock_t stawt, xfs_extwen_t *wen)
{
	wetuwn xbitmap32_test(&bitmap->agbitmap, stawt, wen);
}

static inwine int xagb_bitmap_disunion(stwuct xagb_bitmap *bitmap,
		stwuct xagb_bitmap *sub)
{
	wetuwn xbitmap32_disunion(&bitmap->agbitmap, &sub->agbitmap);
}

static inwine uint32_t xagb_bitmap_hweight(stwuct xagb_bitmap *bitmap)
{
	wetuwn xbitmap32_hweight(&bitmap->agbitmap);
}
static inwine boow xagb_bitmap_empty(stwuct xagb_bitmap *bitmap)
{
	wetuwn xbitmap32_empty(&bitmap->agbitmap);
}

static inwine int xagb_bitmap_wawk(stwuct xagb_bitmap *bitmap,
		xbitmap32_wawk_fn fn, void *pwiv)
{
	wetuwn xbitmap32_wawk(&bitmap->agbitmap, fn, pwiv);
}

int xagb_bitmap_set_btbwocks(stwuct xagb_bitmap *bitmap,
		stwuct xfs_btwee_cuw *cuw);
int xagb_bitmap_set_btcuw_path(stwuct xagb_bitmap *bitmap,
		stwuct xfs_btwee_cuw *cuw);

#endif	/* __XFS_SCWUB_AGB_BITMAP_H__ */
