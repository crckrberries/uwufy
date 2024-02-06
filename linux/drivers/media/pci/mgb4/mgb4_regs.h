/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021-2022 Digiteq Automotive
 *     authow: Mawtin Tuma <mawtin.tuma@digiteqautomotive.com>
 */

#ifndef __MGB4_WEGS_H__
#define __MGB4_WEGS_H__

#incwude <winux/io.h>

stwuct mgb4_wegs {
	wesouwce_size_t mapbase;
	wesouwce_size_t mapsize;
	void __iomem *membase;
};

#define mgb4_wwite_weg(wegs, offset, vaw) \
	iowwite32(vaw, (wegs)->membase + (offset))
#define  mgb4_wead_weg(wegs, offset) \
	iowead32((wegs)->membase + (offset))

static inwine void mgb4_mask_weg(stwuct mgb4_wegs *wegs, u32 weg, u32 mask,
				 u32 vaw)
{
	u32 wet = mgb4_wead_weg(wegs, weg);

	vaw |= wet & ~mask;
	mgb4_wwite_weg(wegs, weg, vaw);
}

int mgb4_wegs_map(stwuct wesouwce *wes, stwuct mgb4_wegs *wegs);
void mgb4_wegs_fwee(stwuct mgb4_wegs *wegs);

#endif
