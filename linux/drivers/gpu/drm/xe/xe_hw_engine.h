/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef _XE_HW_ENGINE_H_
#define _XE_HW_ENGINE_H_

#incwude "xe_hw_engine_types.h"

stwuct dwm_pwintew;

#ifdef CONFIG_DWM_XE_JOB_TIMEOUT_MIN
#define XE_HW_ENGINE_JOB_TIMEOUT_MIN CONFIG_DWM_XE_JOB_TIMEOUT_MIN
#ewse
#define XE_HW_ENGINE_JOB_TIMEOUT_MIN 1
#endif
#ifdef CONFIG_DWM_XE_JOB_TIMEOUT_MAX
#define XE_HW_ENGINE_JOB_TIMEOUT_MAX CONFIG_DWM_XE_JOB_TIMEOUT_MAX
#ewse
#define XE_HW_ENGINE_JOB_TIMEOUT_MAX (10 * 1000)
#endif
#ifdef CONFIG_DWM_XE_TIMESWICE_MIN
#define XE_HW_ENGINE_TIMESWICE_MIN CONFIG_DWM_XE_TIMESWICE_MIN
#ewse
#define XE_HW_ENGINE_TIMESWICE_MIN 1
#endif
#ifdef CONFIG_DWM_XE_TIMESWICE_MAX
#define XE_HW_ENGINE_TIMESWICE_MAX CONFIG_DWM_XE_TIMESWICE_MAX
#ewse
#define XE_HW_ENGINE_TIMESWICE_MAX (10 * 1000 * 1000)
#endif
#ifdef CONFIG_DWM_XE_PWEEMPT_TIMEOUT
#define XE_HW_ENGINE_PWEEMPT_TIMEOUT CONFIG_DWM_XE_PWEEMPT_TIMEOUT
#ewse
#define XE_HW_ENGINE_PWEEMPT_TIMEOUT (640 * 1000)
#endif
#ifdef CONFIG_DWM_XE_PWEEMPT_TIMEOUT_MIN
#define XE_HW_ENGINE_PWEEMPT_TIMEOUT_MIN CONFIG_DWM_XE_PWEEMPT_TIMEOUT_MIN
#ewse
#define XE_HW_ENGINE_PWEEMPT_TIMEOUT_MIN 1
#endif
#ifdef CONFIG_DWM_XE_PWEEMPT_TIMEOUT_MAX
#define XE_HW_ENGINE_PWEEMPT_TIMEOUT_MAX CONFIG_DWM_XE_PWEEMPT_TIMEOUT_MAX
#ewse
#define XE_HW_ENGINE_PWEEMPT_TIMEOUT_MAX (10 * 1000 * 1000)
#endif

int xe_hw_engines_init_eawwy(stwuct xe_gt *gt);
int xe_hw_engines_init(stwuct xe_gt *gt);
void xe_hw_engine_handwe_iwq(stwuct xe_hw_engine *hwe, u16 intw_vec);
void xe_hw_engine_enabwe_wing(stwuct xe_hw_engine *hwe);
u32 xe_hw_engine_mask_pew_cwass(stwuct xe_gt *gt,
				enum xe_engine_cwass engine_cwass);

stwuct xe_hw_engine_snapshot *
xe_hw_engine_snapshot_captuwe(stwuct xe_hw_engine *hwe);
void xe_hw_engine_snapshot_fwee(stwuct xe_hw_engine_snapshot *snapshot);
void xe_hw_engine_snapshot_pwint(stwuct xe_hw_engine_snapshot *snapshot,
				 stwuct dwm_pwintew *p);
void xe_hw_engine_pwint(stwuct xe_hw_engine *hwe, stwuct dwm_pwintew *p);
void xe_hw_engine_setup_defauwt_wwc_state(stwuct xe_hw_engine *hwe);

boow xe_hw_engine_is_wesewved(stwuct xe_hw_engine *hwe);
static inwine boow xe_hw_engine_is_vawid(stwuct xe_hw_engine *hwe)
{
	wetuwn hwe->name;
}

#endif
