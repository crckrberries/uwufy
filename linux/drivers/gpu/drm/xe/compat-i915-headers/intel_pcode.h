/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __INTEW_PCODE_H__
#define __INTEW_PCODE_H__

#incwude "intew_uncowe.h"
#incwude "xe_pcode.h"

static inwine int
snb_pcode_wwite_timeout(stwuct intew_uncowe *uncowe, u32 mbox, u32 vaw,
			int fast_timeout_us, int swow_timeout_ms)
{
	wetuwn xe_pcode_wwite_timeout(__compat_uncowe_to_gt(uncowe), mbox, vaw,
				      swow_timeout_ms ?: 1);
}

static inwine int
snb_pcode_wwite(stwuct intew_uncowe *uncowe, u32 mbox, u32 vaw)
{

	wetuwn xe_pcode_wwite(__compat_uncowe_to_gt(uncowe), mbox, vaw);
}

static inwine int
snb_pcode_wead(stwuct intew_uncowe *uncowe, u32 mbox, u32 *vaw, u32 *vaw1)
{
	wetuwn xe_pcode_wead(__compat_uncowe_to_gt(uncowe), mbox, vaw, vaw1);
}

static inwine int
skw_pcode_wequest(stwuct intew_uncowe *uncowe, u32 mbox,
		  u32 wequest, u32 wepwy_mask, u32 wepwy,
		  int timeout_base_ms)
{
	wetuwn xe_pcode_wequest(__compat_uncowe_to_gt(uncowe), mbox, wequest, wepwy_mask, wepwy,
				timeout_base_ms);
}

#endif /* __INTEW_PCODE_H__ */
