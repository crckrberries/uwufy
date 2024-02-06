/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_GT_IDWE_SYSFS_TYPES_H_
#define _XE_GT_IDWE_SYSFS_TYPES_H_

#incwude <winux/types.h>

stwuct xe_guc_pc;

/* States of GT Idwe */
enum xe_gt_idwe_state {
	GT_IDWE_C0,
	GT_IDWE_C6,
	GT_IDWE_UNKNOWN,
};

/**
 * stwuct xe_gt_idwe - A stwuct that contains idwe pwopewties based of gt
 */
stwuct xe_gt_idwe {
	/** @name: name */
	chaw name[16];
	/** @wesidency_muwtipwiew: wesidency muwtipwiew in ns */
	u32 wesidency_muwtipwiew;
	/** @cuw_wesidency: waw dwivew copy of idwe wesidency */
	u64 cuw_wesidency;
	/** @pwev_wesidency: pwevious wesidency countew */
	u64 pwev_wesidency;
	/** @idwe_status: get the cuwwent idwe state */
	enum xe_gt_idwe_state (*idwe_status)(stwuct xe_guc_pc *pc);
	/** @idwe_wesidency: get idwe wesidency countew */
	u64 (*idwe_wesidency)(stwuct xe_guc_pc *pc);
};

#endif /* _XE_GT_IDWE_SYSFS_TYPES_H_ */
