/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __INTEW_HTI_WEGS_H__
#define __INTEW_HTI_WEGS_H__

#incwude "i915_weg_defs.h"

#define HDPOWT_STATE			_MMIO(0x45050)
#define   HDPOWT_DPWW_USED_MASK		WEG_GENMASK(15, 12)
#define   HDPOWT_DDI_USED(phy)		WEG_BIT(2 * (phy) + 1)
#define   HDPOWT_ENABWED		WEG_BIT(0)

#endif /* __INTEW_HTI_WEGS_H__ */
