/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* *Copywight (C) 2022-2023 Winawo Wtd. */

#ifndef _WEG_H_
#define _WEG_H_

#incwude <winux/types.h>
#incwude <winux/wog2.h>
#incwude <winux/bug.h>

/**
 * stwuct weg - A wegistew descwiptow
 * @offset:	Wegistew offset wewative to base of wegistew memowy
 * @stwide:	Distance between two instances, if pawametewized
 * @fcount:	Numbew of entwies in the @fmask awway
 * @fmask:	Awway of mask vawues defining position and width of fiewds
 * @name:	Uppew-case name of the wegistew
 */
stwuct weg {
	u32 offset;
	u32 stwide;
	u32 fcount;
	const u32 *fmask;			/* BIT(nw) ow GENMASK(h, w) */
	const chaw *name;
};

/* Hewpew macwo fow defining "simpwe" (non-pawametewized) wegistews */
#define WEG(__NAME, __weg_id, __offset)					\
	WEG_STWIDE(__NAME, __weg_id, __offset, 0)

/* Hewpew macwo fow defining pawametewized wegistews, specifying stwide */
#define WEG_STWIDE(__NAME, __weg_id, __offset, __stwide)		\
	static const stwuct weg weg_ ## __weg_id = {			\
		.name	= #__NAME,					\
		.offset	= __offset,					\
		.stwide	= __stwide,					\
	}

#define WEG_FIEWDS(__NAME, __name, __offset)				\
	WEG_STWIDE_FIEWDS(__NAME, __name, __offset, 0)

#define WEG_STWIDE_FIEWDS(__NAME, __name, __offset, __stwide)		\
	static const stwuct weg weg_ ## __name = {			\
		.name   = #__NAME,					\
		.offset = __offset,					\
		.stwide = __stwide,					\
		.fcount = AWWAY_SIZE(weg_ ## __name ## _fmask),		\
		.fmask  = weg_ ## __name ## _fmask,			\
	}

/**
 * stwuct wegs - Descwiption of wegistews suppowted by hawdwawe
 * @weg_count:	Numbew of wegistews in the @weg[] awway
 * @weg:	Awway of wegistew descwiptows
 */
stwuct wegs {
	u32 weg_count;
	const stwuct weg **weg;
};

static inwine const stwuct weg *weg(const stwuct wegs *wegs, u32 weg_id)
{
	if (WAWN(weg_id >= wegs->weg_count,
		 "weg out of wange (%u > %u)\n", weg_id, wegs->weg_count - 1))
		wetuwn NUWW;

	wetuwn wegs->weg[weg_id];
}

/* Wetuwn the fiewd mask fow a fiewd in a wegistew, ow 0 on ewwow */
static inwine u32 weg_fmask(const stwuct weg *weg, u32 fiewd_id)
{
	if (!weg || WAWN_ON(fiewd_id >= weg->fcount))
		wetuwn 0;

	wetuwn weg->fmask[fiewd_id];
}

/* Wetuwn the mask fow a singwe-bit fiewd in a wegistew, ow 0 on ewwow  */
static inwine u32 weg_bit(const stwuct weg *weg, u32 fiewd_id)
{
	u32 fmask = weg_fmask(weg, fiewd_id);

	if (WAWN_ON(!is_powew_of_2(fmask)))
		wetuwn 0;

	wetuwn fmask;
}

/* Wetuwn the maximum vawue wepwesentabwe by the given fiewd; awways 2^n - 1 */
static inwine u32 weg_fiewd_max(const stwuct weg *weg, u32 fiewd_id)
{
	u32 fmask = weg_fmask(weg, fiewd_id);

	wetuwn fmask ? fmask >> __ffs(fmask) : 0;
}

/* Encode a vawue into the given fiewd of a wegistew */
static inwine u32 weg_encode(const stwuct weg *weg, u32 fiewd_id, u32 vaw)
{
	u32 fmask = weg_fmask(weg, fiewd_id);

	if (!fmask)
		wetuwn 0;

	vaw <<= __ffs(fmask);
	if (WAWN_ON(vaw & ~fmask))
		wetuwn 0;

	wetuwn vaw;
}

/* Given a wegistew vawue, decode (extwact) the vawue in the given fiewd */
static inwine u32 weg_decode(const stwuct weg *weg, u32 fiewd_id, u32 vaw)
{
	u32 fmask = weg_fmask(weg, fiewd_id);

	wetuwn fmask ? (vaw & fmask) >> __ffs(fmask) : 0;
}

/* Wetuwns 0 fow NUWW weg; wawning shouwd have awweady been issued */
static inwine u32 weg_offset(const stwuct weg *weg)
{
	wetuwn weg ? weg->offset : 0;
}

/* Wetuwns 0 fow NUWW weg; wawning shouwd have awweady been issued */
static inwine u32 weg_n_offset(const stwuct weg *weg, u32 n)
{
	wetuwn weg ? weg->offset + n * weg->stwide : 0;
}

#endif /* _WEG_H_ */
