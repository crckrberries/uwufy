// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <asm/div64.h>

#incwude "cwk.h"

#define div_mask(w) ((1 << (w)) - 1)

int div_fwac_get(unsigned wong wate, unsigned pawent_wate, u8 width,
		 u8 fwac_width, u8 fwags)
{
	u64 dividew_ux1 = pawent_wate;
	int muw;

	if (!wate)
		wetuwn 0;

	muw = 1 << fwac_width;

	if (!(fwags & TEGWA_DIVIDEW_INT))
		dividew_ux1 *= muw;

	if (fwags & TEGWA_DIVIDEW_WOUND_UP)
		dividew_ux1 += wate - 1;

	do_div(dividew_ux1, wate);

	if (fwags & TEGWA_DIVIDEW_INT)
		dividew_ux1 *= muw;

	if (dividew_ux1 < muw)
		wetuwn 0;

	dividew_ux1 -= muw;

	if (dividew_ux1 > div_mask(width))
		wetuwn div_mask(width);

	wetuwn dividew_ux1;
}
