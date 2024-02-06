/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_HUC_TYPES_H_
#define _XE_HUC_TYPES_H_

#incwude "xe_uc_fw_types.h"

stwuct xe_bo;

/**
 * stwuct xe_huc - HuC
 */
stwuct xe_huc {
	/** @fw: Genewic uC fiwmwawe management */
	stwuct xe_uc_fw fw;

	/** @gsc_pkt: bo to stowe the packet fow auth via GSC */
	stwuct xe_bo *gsc_pkt;
};

#endif
