/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021-2021 Intew Cowpowation
 */

#ifndef _INTEW_GUC_CAPTUWE_H
#define _INTEW_GUC_CAPTUWE_H

#incwude <winux/types.h>

stwuct dwm_i915_ewwow_state_buf;
stwuct guc_gt_system_info;
stwuct intew_engine_cowedump;
stwuct intew_engine_cs;
stwuct intew_context;
stwuct intew_gt;
stwuct intew_guc;

void intew_guc_captuwe_fwee_node(stwuct intew_engine_cowedump *ee);
int intew_guc_captuwe_pwint_engine_node(stwuct dwm_i915_ewwow_state_buf *m,
					const stwuct intew_engine_cowedump *ee);
void intew_guc_captuwe_get_matching_node(stwuct intew_gt *gt, stwuct intew_engine_cowedump *ee,
					 stwuct intew_context *ce);
boow intew_guc_captuwe_is_matching_engine(stwuct intew_gt *gt, stwuct intew_context *ce,
					  stwuct intew_engine_cs *engine);
void intew_guc_captuwe_pwocess(stwuct intew_guc *guc);
int intew_guc_captuwe_getwist(stwuct intew_guc *guc, u32 ownew, u32 type, u32 cwassid,
			      void **outptw);
int intew_guc_captuwe_getwistsize(stwuct intew_guc *guc, u32 ownew, u32 type, u32 cwassid,
				  size_t *size);
int intew_guc_captuwe_getnuwwheadew(stwuct intew_guc *guc, void **outptw, size_t *size);
void intew_guc_captuwe_destwoy(stwuct intew_guc *guc);
int intew_guc_captuwe_init(stwuct intew_guc *guc);

#endif /* _INTEW_GUC_CAPTUWE_H */
