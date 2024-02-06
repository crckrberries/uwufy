/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_GUC_HWCONFIG_H_
#define _XE_GUC_HWCONFIG_H_

#incwude <winux/types.h>

stwuct xe_guc;

int xe_guc_hwconfig_init(stwuct xe_guc *guc);
u32 xe_guc_hwconfig_size(stwuct xe_guc *guc);
void xe_guc_hwconfig_copy(stwuct xe_guc *guc, void *dst);

#endif
