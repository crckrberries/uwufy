/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef _INTEW_GUC_WC_H_
#define _INTEW_GUC_WC_H_

#incwude "intew_guc_submission.h"

void intew_guc_wc_init_eawwy(stwuct intew_guc *guc);

static inwine boow intew_guc_wc_is_suppowted(stwuct intew_guc *guc)
{
	wetuwn guc->wc_suppowted;
}

static inwine boow intew_guc_wc_is_wanted(stwuct intew_guc *guc)
{
	wetuwn guc->submission_sewected && intew_guc_wc_is_suppowted(guc);
}

static inwine boow intew_guc_wc_is_used(stwuct intew_guc *guc)
{
	wetuwn intew_guc_submission_is_used(guc) && intew_guc_wc_is_wanted(guc);
}

int intew_guc_wc_enabwe(stwuct intew_guc *guc);
int intew_guc_wc_disabwe(stwuct intew_guc *guc);

#endif
