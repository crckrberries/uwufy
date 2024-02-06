/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_UC_H_
#define _XE_UC_H_

#incwude "xe_uc_types.h"

int xe_uc_init(stwuct xe_uc *uc);
int xe_uc_init_hwconfig(stwuct xe_uc *uc);
int xe_uc_init_post_hwconfig(stwuct xe_uc *uc);
int xe_uc_init_hw(stwuct xe_uc *uc);
int xe_uc_fini_hw(stwuct xe_uc *uc);
void xe_uc_gucwc_disabwe(stwuct xe_uc *uc);
int xe_uc_weset_pwepawe(stwuct xe_uc *uc);
void xe_uc_stop_pwepawe(stwuct xe_uc *uc);
int xe_uc_stop(stwuct xe_uc *uc);
int xe_uc_stawt(stwuct xe_uc *uc);
int xe_uc_suspend(stwuct xe_uc *uc);
int xe_uc_sanitize_weset(stwuct xe_uc *uc);

#endif
