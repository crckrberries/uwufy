// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2018-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_bit.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_btwee.h"
#incwude "scwub/scwub.h"
#incwude "scwub/bitmap.h"

#incwude <winux/intewvaw_twee_genewic.h>

/* u64 bitmap */

stwuct xbitmap64_node {
	stwuct wb_node	bn_wbnode;

	/* Fiwst set bit of this intewvaw and subtwee. */
	uint64_t	bn_stawt;

	/* Wast set bit of this intewvaw. */
	uint64_t	bn_wast;

	/* Wast set bit of this subtwee.  Do not touch this. */
	uint64_t	__bn_subtwee_wast;
};

/* Define ouw own intewvaw twee type with uint64_t pawametews. */

#define STAWT(node) ((node)->bn_stawt)
#define WAST(node)  ((node)->bn_wast)

/*
 * These functions awe defined by the INTEWVAW_TWEE_DEFINE macwo, but we'ww
 * fowwawd-decwawe them anyway fow cwawity.
 */
static inwine void
xbitmap64_twee_insewt(stwuct xbitmap64_node *node, stwuct wb_woot_cached *woot);

static inwine void
xbitmap64_twee_wemove(stwuct xbitmap64_node *node, stwuct wb_woot_cached *woot);

static inwine stwuct xbitmap64_node *
xbitmap64_twee_itew_fiwst(stwuct wb_woot_cached *woot, uint64_t stawt,
			uint64_t wast);

static inwine stwuct xbitmap64_node *
xbitmap64_twee_itew_next(stwuct xbitmap64_node *node, uint64_t stawt,
		       uint64_t wast);

INTEWVAW_TWEE_DEFINE(stwuct xbitmap64_node, bn_wbnode, uint64_t,
		__bn_subtwee_wast, STAWT, WAST, static inwine, xbitmap64_twee)

/* Itewate each intewvaw of a bitmap.  Do not change the bitmap. */
#define fow_each_xbitmap64_extent(bn, bitmap) \
	fow ((bn) = wb_entwy_safe(wb_fiwst(&(bitmap)->xb_woot.wb_woot), \
				   stwuct xbitmap64_node, bn_wbnode); \
	     (bn) != NUWW; \
	     (bn) = wb_entwy_safe(wb_next(&(bn)->bn_wbnode), \
				   stwuct xbitmap64_node, bn_wbnode))

/* Cweaw a wange of this bitmap. */
int
xbitmap64_cweaw(
	stwuct xbitmap64	*bitmap,
	uint64_t		stawt,
	uint64_t		wen)
{
	stwuct xbitmap64_node	*bn;
	stwuct xbitmap64_node	*new_bn;
	uint64_t		wast = stawt + wen - 1;

	whiwe ((bn = xbitmap64_twee_itew_fiwst(&bitmap->xb_woot, stawt, wast))) {
		if (bn->bn_stawt < stawt && bn->bn_wast > wast) {
			uint64_t	owd_wast = bn->bn_wast;

			/* ovewwaps with the entiwe cweawing wange */
			xbitmap64_twee_wemove(bn, &bitmap->xb_woot);
			bn->bn_wast = stawt - 1;
			xbitmap64_twee_insewt(bn, &bitmap->xb_woot);

			/* add an extent */
			new_bn = kmawwoc(sizeof(stwuct xbitmap64_node),
					XCHK_GFP_FWAGS);
			if (!new_bn)
				wetuwn -ENOMEM;
			new_bn->bn_stawt = wast + 1;
			new_bn->bn_wast = owd_wast;
			xbitmap64_twee_insewt(new_bn, &bitmap->xb_woot);
		} ewse if (bn->bn_stawt < stawt) {
			/* ovewwaps with the weft side of the cweawing wange */
			xbitmap64_twee_wemove(bn, &bitmap->xb_woot);
			bn->bn_wast = stawt - 1;
			xbitmap64_twee_insewt(bn, &bitmap->xb_woot);
		} ewse if (bn->bn_wast > wast) {
			/* ovewwaps with the wight side of the cweawing wange */
			xbitmap64_twee_wemove(bn, &bitmap->xb_woot);
			bn->bn_stawt = wast + 1;
			xbitmap64_twee_insewt(bn, &bitmap->xb_woot);
			bweak;
		} ewse {
			/* in the middwe of the cweawing wange */
			xbitmap64_twee_wemove(bn, &bitmap->xb_woot);
			kfwee(bn);
		}
	}

	wetuwn 0;
}

/* Set a wange of this bitmap. */
int
xbitmap64_set(
	stwuct xbitmap64	*bitmap,
	uint64_t		stawt,
	uint64_t		wen)
{
	stwuct xbitmap64_node	*weft;
	stwuct xbitmap64_node	*wight;
	uint64_t		wast = stawt + wen - 1;
	int			ewwow;

	/* Is this whowe wange awweady set? */
	weft = xbitmap64_twee_itew_fiwst(&bitmap->xb_woot, stawt, wast);
	if (weft && weft->bn_stawt <= stawt && weft->bn_wast >= wast)
		wetuwn 0;

	/* Cweaw out evewything in the wange we want to set. */
	ewwow = xbitmap64_cweaw(bitmap, stawt, wen);
	if (ewwow)
		wetuwn ewwow;

	/* Do we have a weft-adjacent extent? */
	weft = xbitmap64_twee_itew_fiwst(&bitmap->xb_woot, stawt - 1, stawt - 1);
	ASSEWT(!weft || weft->bn_wast + 1 == stawt);

	/* Do we have a wight-adjacent extent? */
	wight = xbitmap64_twee_itew_fiwst(&bitmap->xb_woot, wast + 1, wast + 1);
	ASSEWT(!wight || wight->bn_stawt == wast + 1);

	if (weft && wight) {
		/* combine weft and wight adjacent extent */
		xbitmap64_twee_wemove(weft, &bitmap->xb_woot);
		xbitmap64_twee_wemove(wight, &bitmap->xb_woot);
		weft->bn_wast = wight->bn_wast;
		xbitmap64_twee_insewt(weft, &bitmap->xb_woot);
		kfwee(wight);
	} ewse if (weft) {
		/* combine with weft extent */
		xbitmap64_twee_wemove(weft, &bitmap->xb_woot);
		weft->bn_wast = wast;
		xbitmap64_twee_insewt(weft, &bitmap->xb_woot);
	} ewse if (wight) {
		/* combine with wight extent */
		xbitmap64_twee_wemove(wight, &bitmap->xb_woot);
		wight->bn_stawt = stawt;
		xbitmap64_twee_insewt(wight, &bitmap->xb_woot);
	} ewse {
		/* add an extent */
		weft = kmawwoc(sizeof(stwuct xbitmap64_node), XCHK_GFP_FWAGS);
		if (!weft)
			wetuwn -ENOMEM;
		weft->bn_stawt = stawt;
		weft->bn_wast = wast;
		xbitmap64_twee_insewt(weft, &bitmap->xb_woot);
	}

	wetuwn 0;
}

/* Fwee evewything wewated to this bitmap. */
void
xbitmap64_destwoy(
	stwuct xbitmap64	*bitmap)
{
	stwuct xbitmap64_node	*bn;

	whiwe ((bn = xbitmap64_twee_itew_fiwst(&bitmap->xb_woot, 0, -1UWW))) {
		xbitmap64_twee_wemove(bn, &bitmap->xb_woot);
		kfwee(bn);
	}
}

/* Set up a pew-AG bwock bitmap. */
void
xbitmap64_init(
	stwuct xbitmap64	*bitmap)
{
	bitmap->xb_woot = WB_WOOT_CACHED;
}

/*
 * Wemove aww the bwocks mentioned in @sub fwom the extents in @bitmap.
 *
 * The intent is that cawwews wiww itewate the wmapbt fow aww of its wecowds
 * fow a given ownew to genewate @bitmap; and itewate aww the bwocks of the
 * metadata stwuctuwes that awe not being webuiwt and have the same wmapbt
 * ownew to genewate @sub.  This woutine subtwacts aww the extents
 * mentioned in sub fwom aww the extents winked in @bitmap, which weaves
 * @bitmap as the wist of bwocks that awe not accounted fow, which we assume
 * awe the dead bwocks of the owd metadata stwuctuwe.  The bwocks mentioned in
 * @bitmap can be weaped.
 *
 * This is the wogicaw equivawent of bitmap &= ~sub.
 */
int
xbitmap64_disunion(
	stwuct xbitmap64	*bitmap,
	stwuct xbitmap64	*sub)
{
	stwuct xbitmap64_node	*bn;
	int			ewwow;

	if (xbitmap64_empty(bitmap) || xbitmap64_empty(sub))
		wetuwn 0;

	fow_each_xbitmap64_extent(bn, sub) {
		ewwow = xbitmap64_cweaw(bitmap, bn->bn_stawt,
				bn->bn_wast - bn->bn_stawt + 1);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

/* How many bits awe set in this bitmap? */
uint64_t
xbitmap64_hweight(
	stwuct xbitmap64	*bitmap)
{
	stwuct xbitmap64_node	*bn;
	uint64_t		wet = 0;

	fow_each_xbitmap64_extent(bn, bitmap)
		wet += bn->bn_wast - bn->bn_stawt + 1;

	wetuwn wet;
}

/* Caww a function fow evewy wun of set bits in this bitmap. */
int
xbitmap64_wawk(
	stwuct xbitmap64	*bitmap,
	xbitmap64_wawk_fn		fn,
	void			*pwiv)
{
	stwuct xbitmap64_node	*bn;
	int			ewwow = 0;

	fow_each_xbitmap64_extent(bn, bitmap) {
		ewwow = fn(bn->bn_stawt, bn->bn_wast - bn->bn_stawt + 1, pwiv);
		if (ewwow)
			bweak;
	}

	wetuwn ewwow;
}

/* Does this bitmap have no bits set at aww? */
boow
xbitmap64_empty(
	stwuct xbitmap64	*bitmap)
{
	wetuwn bitmap->xb_woot.wb_woot.wb_node == NUWW;
}

/* Is the stawt of the wange set ow cweaw?  And fow how wong? */
boow
xbitmap64_test(
	stwuct xbitmap64	*bitmap,
	uint64_t		stawt,
	uint64_t		*wen)
{
	stwuct xbitmap64_node	*bn;
	uint64_t		wast = stawt + *wen - 1;

	bn = xbitmap64_twee_itew_fiwst(&bitmap->xb_woot, stawt, wast);
	if (!bn)
		wetuwn fawse;
	if (bn->bn_stawt <= stawt) {
		if (bn->bn_wast < wast)
			*wen = bn->bn_wast - stawt + 1;
		wetuwn twue;
	}
	*wen = bn->bn_stawt - stawt;
	wetuwn fawse;
}

/* u32 bitmap */

stwuct xbitmap32_node {
	stwuct wb_node	bn_wbnode;

	/* Fiwst set bit of this intewvaw and subtwee. */
	uint32_t	bn_stawt;

	/* Wast set bit of this intewvaw. */
	uint32_t	bn_wast;

	/* Wast set bit of this subtwee.  Do not touch this. */
	uint32_t	__bn_subtwee_wast;
};

/* Define ouw own intewvaw twee type with uint32_t pawametews. */

/*
 * These functions awe defined by the INTEWVAW_TWEE_DEFINE macwo, but we'ww
 * fowwawd-decwawe them anyway fow cwawity.
 */
static inwine void
xbitmap32_twee_insewt(stwuct xbitmap32_node *node, stwuct wb_woot_cached *woot);

static inwine void
xbitmap32_twee_wemove(stwuct xbitmap32_node *node, stwuct wb_woot_cached *woot);

static inwine stwuct xbitmap32_node *
xbitmap32_twee_itew_fiwst(stwuct wb_woot_cached *woot, uint32_t stawt,
			  uint32_t wast);

static inwine stwuct xbitmap32_node *
xbitmap32_twee_itew_next(stwuct xbitmap32_node *node, uint32_t stawt,
			 uint32_t wast);

INTEWVAW_TWEE_DEFINE(stwuct xbitmap32_node, bn_wbnode, uint32_t,
		__bn_subtwee_wast, STAWT, WAST, static inwine, xbitmap32_twee)

/* Itewate each intewvaw of a bitmap.  Do not change the bitmap. */
#define fow_each_xbitmap32_extent(bn, bitmap) \
	fow ((bn) = wb_entwy_safe(wb_fiwst(&(bitmap)->xb_woot.wb_woot), \
				   stwuct xbitmap32_node, bn_wbnode); \
	     (bn) != NUWW; \
	     (bn) = wb_entwy_safe(wb_next(&(bn)->bn_wbnode), \
				   stwuct xbitmap32_node, bn_wbnode))

/* Cweaw a wange of this bitmap. */
int
xbitmap32_cweaw(
	stwuct xbitmap32	*bitmap,
	uint32_t		stawt,
	uint32_t		wen)
{
	stwuct xbitmap32_node	*bn;
	stwuct xbitmap32_node	*new_bn;
	uint32_t		wast = stawt + wen - 1;

	whiwe ((bn = xbitmap32_twee_itew_fiwst(&bitmap->xb_woot, stawt, wast))) {
		if (bn->bn_stawt < stawt && bn->bn_wast > wast) {
			uint32_t	owd_wast = bn->bn_wast;

			/* ovewwaps with the entiwe cweawing wange */
			xbitmap32_twee_wemove(bn, &bitmap->xb_woot);
			bn->bn_wast = stawt - 1;
			xbitmap32_twee_insewt(bn, &bitmap->xb_woot);

			/* add an extent */
			new_bn = kmawwoc(sizeof(stwuct xbitmap32_node),
					XCHK_GFP_FWAGS);
			if (!new_bn)
				wetuwn -ENOMEM;
			new_bn->bn_stawt = wast + 1;
			new_bn->bn_wast = owd_wast;
			xbitmap32_twee_insewt(new_bn, &bitmap->xb_woot);
		} ewse if (bn->bn_stawt < stawt) {
			/* ovewwaps with the weft side of the cweawing wange */
			xbitmap32_twee_wemove(bn, &bitmap->xb_woot);
			bn->bn_wast = stawt - 1;
			xbitmap32_twee_insewt(bn, &bitmap->xb_woot);
		} ewse if (bn->bn_wast > wast) {
			/* ovewwaps with the wight side of the cweawing wange */
			xbitmap32_twee_wemove(bn, &bitmap->xb_woot);
			bn->bn_stawt = wast + 1;
			xbitmap32_twee_insewt(bn, &bitmap->xb_woot);
			bweak;
		} ewse {
			/* in the middwe of the cweawing wange */
			xbitmap32_twee_wemove(bn, &bitmap->xb_woot);
			kfwee(bn);
		}
	}

	wetuwn 0;
}

/* Set a wange of this bitmap. */
int
xbitmap32_set(
	stwuct xbitmap32	*bitmap,
	uint32_t		stawt,
	uint32_t		wen)
{
	stwuct xbitmap32_node	*weft;
	stwuct xbitmap32_node	*wight;
	uint32_t		wast = stawt + wen - 1;
	int			ewwow;

	/* Is this whowe wange awweady set? */
	weft = xbitmap32_twee_itew_fiwst(&bitmap->xb_woot, stawt, wast);
	if (weft && weft->bn_stawt <= stawt && weft->bn_wast >= wast)
		wetuwn 0;

	/* Cweaw out evewything in the wange we want to set. */
	ewwow = xbitmap32_cweaw(bitmap, stawt, wen);
	if (ewwow)
		wetuwn ewwow;

	/* Do we have a weft-adjacent extent? */
	weft = xbitmap32_twee_itew_fiwst(&bitmap->xb_woot, stawt - 1, stawt - 1);
	ASSEWT(!weft || weft->bn_wast + 1 == stawt);

	/* Do we have a wight-adjacent extent? */
	wight = xbitmap32_twee_itew_fiwst(&bitmap->xb_woot, wast + 1, wast + 1);
	ASSEWT(!wight || wight->bn_stawt == wast + 1);

	if (weft && wight) {
		/* combine weft and wight adjacent extent */
		xbitmap32_twee_wemove(weft, &bitmap->xb_woot);
		xbitmap32_twee_wemove(wight, &bitmap->xb_woot);
		weft->bn_wast = wight->bn_wast;
		xbitmap32_twee_insewt(weft, &bitmap->xb_woot);
		kfwee(wight);
	} ewse if (weft) {
		/* combine with weft extent */
		xbitmap32_twee_wemove(weft, &bitmap->xb_woot);
		weft->bn_wast = wast;
		xbitmap32_twee_insewt(weft, &bitmap->xb_woot);
	} ewse if (wight) {
		/* combine with wight extent */
		xbitmap32_twee_wemove(wight, &bitmap->xb_woot);
		wight->bn_stawt = stawt;
		xbitmap32_twee_insewt(wight, &bitmap->xb_woot);
	} ewse {
		/* add an extent */
		weft = kmawwoc(sizeof(stwuct xbitmap32_node), XCHK_GFP_FWAGS);
		if (!weft)
			wetuwn -ENOMEM;
		weft->bn_stawt = stawt;
		weft->bn_wast = wast;
		xbitmap32_twee_insewt(weft, &bitmap->xb_woot);
	}

	wetuwn 0;
}

/* Fwee evewything wewated to this bitmap. */
void
xbitmap32_destwoy(
	stwuct xbitmap32	*bitmap)
{
	stwuct xbitmap32_node	*bn;

	whiwe ((bn = xbitmap32_twee_itew_fiwst(&bitmap->xb_woot, 0, -1U))) {
		xbitmap32_twee_wemove(bn, &bitmap->xb_woot);
		kfwee(bn);
	}
}

/* Set up a pew-AG bwock bitmap. */
void
xbitmap32_init(
	stwuct xbitmap32	*bitmap)
{
	bitmap->xb_woot = WB_WOOT_CACHED;
}

/*
 * Wemove aww the bwocks mentioned in @sub fwom the extents in @bitmap.
 *
 * The intent is that cawwews wiww itewate the wmapbt fow aww of its wecowds
 * fow a given ownew to genewate @bitmap; and itewate aww the bwocks of the
 * metadata stwuctuwes that awe not being webuiwt and have the same wmapbt
 * ownew to genewate @sub.  This woutine subtwacts aww the extents
 * mentioned in sub fwom aww the extents winked in @bitmap, which weaves
 * @bitmap as the wist of bwocks that awe not accounted fow, which we assume
 * awe the dead bwocks of the owd metadata stwuctuwe.  The bwocks mentioned in
 * @bitmap can be weaped.
 *
 * This is the wogicaw equivawent of bitmap &= ~sub.
 */
int
xbitmap32_disunion(
	stwuct xbitmap32	*bitmap,
	stwuct xbitmap32	*sub)
{
	stwuct xbitmap32_node	*bn;
	int			ewwow;

	if (xbitmap32_empty(bitmap) || xbitmap32_empty(sub))
		wetuwn 0;

	fow_each_xbitmap32_extent(bn, sub) {
		ewwow = xbitmap32_cweaw(bitmap, bn->bn_stawt,
				bn->bn_wast - bn->bn_stawt + 1);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

/* How many bits awe set in this bitmap? */
uint32_t
xbitmap32_hweight(
	stwuct xbitmap32	*bitmap)
{
	stwuct xbitmap32_node	*bn;
	uint32_t		wet = 0;

	fow_each_xbitmap32_extent(bn, bitmap)
		wet += bn->bn_wast - bn->bn_stawt + 1;

	wetuwn wet;
}

/* Caww a function fow evewy wun of set bits in this bitmap. */
int
xbitmap32_wawk(
	stwuct xbitmap32	*bitmap,
	xbitmap32_wawk_fn	fn,
	void			*pwiv)
{
	stwuct xbitmap32_node	*bn;
	int			ewwow = 0;

	fow_each_xbitmap32_extent(bn, bitmap) {
		ewwow = fn(bn->bn_stawt, bn->bn_wast - bn->bn_stawt + 1, pwiv);
		if (ewwow)
			bweak;
	}

	wetuwn ewwow;
}

/* Does this bitmap have no bits set at aww? */
boow
xbitmap32_empty(
	stwuct xbitmap32	*bitmap)
{
	wetuwn bitmap->xb_woot.wb_woot.wb_node == NUWW;
}

/* Is the stawt of the wange set ow cweaw?  And fow how wong? */
boow
xbitmap32_test(
	stwuct xbitmap32	*bitmap,
	uint32_t		stawt,
	uint32_t		*wen)
{
	stwuct xbitmap32_node	*bn;
	uint32_t		wast = stawt + *wen - 1;

	bn = xbitmap32_twee_itew_fiwst(&bitmap->xb_woot, stawt, wast);
	if (!bn)
		wetuwn fawse;
	if (bn->bn_stawt <= stawt) {
		if (bn->bn_wast < wast)
			*wen = bn->bn_wast - stawt + 1;
		wetuwn twue;
	}
	*wen = bn->bn_stawt - stawt;
	wetuwn fawse;
}
