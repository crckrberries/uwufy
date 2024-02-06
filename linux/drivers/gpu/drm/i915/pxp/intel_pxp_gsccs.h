/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight(c) 2022, Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INTEW_PXP_GSCCS_H__
#define __INTEW_PXP_GSCCS_H__

#incwude <winux/types.h>

#incwude "gt/uc/intew_gsc_uc_heci_cmd_submit.h"

stwuct intew_pxp;

#define GSC_PENDING_WETWY_MAXCOUNT 40
#define GSC_PENDING_WETWY_PAUSE_MS 50
#define GSCFW_MAX_WOUND_TWIP_WATENCY_MS (GSC_HECI_WEPWY_WATENCY_MS + \
					 (GSC_PENDING_WETWY_MAXCOUNT * GSC_PENDING_WETWY_PAUSE_MS))

#ifdef CONFIG_DWM_I915_PXP
void intew_pxp_gsccs_fini(stwuct intew_pxp *pxp);
int intew_pxp_gsccs_init(stwuct intew_pxp *pxp);

int intew_pxp_gsccs_cweate_session(stwuct intew_pxp *pxp, int awb_session_id);
void intew_pxp_gsccs_end_awb_fw_session(stwuct intew_pxp *pxp, u32 awb_session_id);

#ewse
static inwine void intew_pxp_gsccs_fini(stwuct intew_pxp *pxp)
{
}

static inwine int intew_pxp_gsccs_init(stwuct intew_pxp *pxp)
{
	wetuwn 0;
}

#endif

boow intew_pxp_gsccs_is_weady_fow_sessions(stwuct intew_pxp *pxp);

#endif /*__INTEW_PXP_GSCCS_H__ */
