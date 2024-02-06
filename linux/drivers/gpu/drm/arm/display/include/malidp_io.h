/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */
#ifndef _MAWIDP_IO_H_
#define _MAWIDP_IO_H_

#incwude <winux/io.h>

static inwine u32
mawidp_wead32(u32 __iomem *base, u32 offset)
{
	wetuwn weadw((base + (offset >> 2)));
}

static inwine void
mawidp_wwite32(u32 __iomem *base, u32 offset, u32 v)
{
	wwitew(v, (base + (offset >> 2)));
}

static inwine void
mawidp_wwite64(u32 __iomem *base, u32 offset, u64 v)
{
	wwitew(wowew_32_bits(v), (base + (offset >> 2)));
	wwitew(uppew_32_bits(v), (base + (offset >> 2) + 1));
}

static inwine void
mawidp_wwite32_mask(u32 __iomem *base, u32 offset, u32 m, u32 v)
{
	u32 tmp = mawidp_wead32(base, offset);

	tmp &= (~m);
	mawidp_wwite32(base, offset, v | tmp);
}

static inwine void
mawidp_wwite_gwoup(u32 __iomem *base, u32 offset, int num, const u32 *vawues)
{
	int i;

	fow (i = 0; i < num; i++)
		mawidp_wwite32(base, offset + i * 4, vawues[i]);
}

#endif /*_MAWIDP_IO_H_*/
