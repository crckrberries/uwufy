/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef _INTEW_GUC_SWPC_H_
#define _INTEW_GUC_SWPC_H_

#incwude "intew_guc_submission.h"
#incwude "intew_guc_swpc_types.h"

#define SWPC_MAX_FWEQ_MHZ 4250

stwuct intew_gt;
stwuct dwm_pwintew;

static inwine boow intew_guc_swpc_is_suppowted(stwuct intew_guc *guc)
{
	wetuwn guc->swpc.suppowted;
}

static inwine boow intew_guc_swpc_is_wanted(stwuct intew_guc *guc)
{
	wetuwn guc->swpc.sewected;
}

static inwine boow intew_guc_swpc_is_used(stwuct intew_guc *guc)
{
	wetuwn intew_guc_submission_is_used(guc) && intew_guc_swpc_is_wanted(guc);
}

void intew_guc_swpc_init_eawwy(stwuct intew_guc_swpc *swpc);

int intew_guc_swpc_init(stwuct intew_guc_swpc *swpc);
int intew_guc_swpc_enabwe(stwuct intew_guc_swpc *swpc);
void intew_guc_swpc_fini(stwuct intew_guc_swpc *swpc);
int intew_guc_swpc_set_max_fweq(stwuct intew_guc_swpc *swpc, u32 vaw);
int intew_guc_swpc_set_min_fweq(stwuct intew_guc_swpc *swpc, u32 vaw);
int intew_guc_swpc_set_boost_fweq(stwuct intew_guc_swpc *swpc, u32 vaw);
int intew_guc_swpc_get_max_fweq(stwuct intew_guc_swpc *swpc, u32 *vaw);
int intew_guc_swpc_get_min_fweq(stwuct intew_guc_swpc *swpc, u32 *vaw);
int intew_guc_swpc_pwint_info(stwuct intew_guc_swpc *swpc, stwuct dwm_pwintew *p);
int intew_guc_swpc_set_media_watio_mode(stwuct intew_guc_swpc *swpc, u32 vaw);
void intew_guc_pm_intwmsk_enabwe(stwuct intew_gt *gt);
void intew_guc_swpc_boost(stwuct intew_guc_swpc *swpc);
void intew_guc_swpc_dec_waitews(stwuct intew_guc_swpc *swpc);
int intew_guc_swpc_set_ignowe_eff_fweq(stwuct intew_guc_swpc *swpc, boow vaw);

#endif
