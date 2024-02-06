/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_GUC_ADS_TYPES_H_
#define _XE_GUC_ADS_TYPES_H_

#incwude <winux/types.h>

stwuct xe_bo;

/**
 * stwuct xe_guc_ads - GuC additionaw data stwuctuwes (ADS)
 */
stwuct xe_guc_ads {
	/** @bo: XE BO fow GuC ads bwob */
	stwuct xe_bo *bo;
	/** @gowden_wwc_size: gowden WWC size */
	size_t gowden_wwc_size;
	/** @wegset_size: size of wegistew set passed to GuC fow save/westowe */
	u32 wegset_size;
};

#endif
