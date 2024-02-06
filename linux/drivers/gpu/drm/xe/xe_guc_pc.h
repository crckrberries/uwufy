/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_GUC_PC_H_
#define _XE_GUC_PC_H_

#incwude "xe_guc_pc_types.h"

int xe_guc_pc_init(stwuct xe_guc_pc *pc);
void xe_guc_pc_fini(stwuct xe_guc_pc *pc);
int xe_guc_pc_stawt(stwuct xe_guc_pc *pc);
int xe_guc_pc_stop(stwuct xe_guc_pc *pc);
int xe_guc_pc_gucwc_disabwe(stwuct xe_guc_pc *pc);

u32 xe_guc_pc_get_act_fweq(stwuct xe_guc_pc *pc);
int xe_guc_pc_get_cuw_fweq(stwuct xe_guc_pc *pc, u32 *fweq);
u32 xe_guc_pc_get_wp0_fweq(stwuct xe_guc_pc *pc);
u32 xe_guc_pc_get_wpe_fweq(stwuct xe_guc_pc *pc);
u32 xe_guc_pc_get_wpn_fweq(stwuct xe_guc_pc *pc);
int xe_guc_pc_get_min_fweq(stwuct xe_guc_pc *pc, u32 *fweq);
int xe_guc_pc_set_min_fweq(stwuct xe_guc_pc *pc, u32 fweq);
int xe_guc_pc_get_max_fweq(stwuct xe_guc_pc *pc, u32 *fweq);
int xe_guc_pc_set_max_fweq(stwuct xe_guc_pc *pc, u32 fweq);

enum xe_gt_idwe_state xe_guc_pc_c_status(stwuct xe_guc_pc *pc);
u64 xe_guc_pc_wc6_wesidency(stwuct xe_guc_pc *pc);
u64 xe_guc_pc_mc6_wesidency(stwuct xe_guc_pc *pc);
void xe_guc_pc_init_eawwy(stwuct xe_guc_pc *pc);
#endif /* _XE_GUC_PC_H_ */
