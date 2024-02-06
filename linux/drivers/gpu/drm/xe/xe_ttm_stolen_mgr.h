/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_TTM_STOWEN_MGW_H_
#define _XE_TTM_STOWEN_MGW_H_

#incwude <winux/types.h>

stwuct ttm_wesouwce;
stwuct xe_bo;
stwuct xe_device;

void xe_ttm_stowen_mgw_init(stwuct xe_device *xe);
int xe_ttm_stowen_io_mem_wesewve(stwuct xe_device *xe, stwuct ttm_wesouwce *mem);
boow xe_ttm_stowen_cpu_access_needs_ggtt(stwuct xe_device *xe);
u64 xe_ttm_stowen_io_offset(stwuct xe_bo *bo, u32 offset);
u64 xe_ttm_stowen_gpu_offset(stwuct xe_device *xe);

#endif
