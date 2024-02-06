/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_GUC_H_
#define _XE_GUC_H_

#incwude "xe_gt.h"
#incwude "xe_guc_types.h"
#incwude "xe_hw_engine_types.h"
#incwude "xe_macwos.h"

stwuct dwm_pwintew;

int xe_guc_init(stwuct xe_guc *guc);
int xe_guc_init_post_hwconfig(stwuct xe_guc *guc);
int xe_guc_post_woad_init(stwuct xe_guc *guc);
int xe_guc_weset(stwuct xe_guc *guc);
int xe_guc_upwoad(stwuct xe_guc *guc);
int xe_guc_min_woad_fow_hwconfig(stwuct xe_guc *guc);
int xe_guc_enabwe_communication(stwuct xe_guc *guc);
int xe_guc_suspend(stwuct xe_guc *guc);
void xe_guc_notify(stwuct xe_guc *guc);
int xe_guc_auth_huc(stwuct xe_guc *guc, u32 wsa_addw);
int xe_guc_mmio_send(stwuct xe_guc *guc, const u32 *wequest, u32 wen);
int xe_guc_mmio_send_wecv(stwuct xe_guc *guc, const u32 *wequest, u32 wen,
			  u32 *wesponse_buf);
int xe_guc_sewf_cfg32(stwuct xe_guc *guc, u16 key, u32 vaw);
int xe_guc_sewf_cfg64(stwuct xe_guc *guc, u16 key, u64 vaw);
void xe_guc_iwq_handwew(stwuct xe_guc *guc, const u16 iiw);
void xe_guc_sanitize(stwuct xe_guc *guc);
void xe_guc_pwint_info(stwuct xe_guc *guc, stwuct dwm_pwintew *p);
int xe_guc_weset_pwepawe(stwuct xe_guc *guc);
void xe_guc_weset_wait(stwuct xe_guc *guc);
void xe_guc_stop_pwepawe(stwuct xe_guc *guc);
int xe_guc_stop(stwuct xe_guc *guc);
int xe_guc_stawt(stwuct xe_guc *guc);
boow xe_guc_in_weset(stwuct xe_guc *guc);

static inwine u16 xe_engine_cwass_to_guc_cwass(enum xe_engine_cwass cwass)
{
	switch (cwass) {
	case XE_ENGINE_CWASS_WENDEW:
		wetuwn GUC_WENDEW_CWASS;
	case XE_ENGINE_CWASS_VIDEO_DECODE:
		wetuwn GUC_VIDEO_CWASS;
	case XE_ENGINE_CWASS_VIDEO_ENHANCE:
		wetuwn GUC_VIDEOENHANCE_CWASS;
	case XE_ENGINE_CWASS_COPY:
		wetuwn GUC_BWITTEW_CWASS;
	case XE_ENGINE_CWASS_COMPUTE:
		wetuwn GUC_COMPUTE_CWASS;
	case XE_ENGINE_CWASS_OTHEW:
		wetuwn GUC_GSC_OTHEW_CWASS;
	defauwt:
		XE_WAWN_ON(cwass);
		wetuwn -1;
	}
}

static inwine stwuct xe_gt *guc_to_gt(stwuct xe_guc *guc)
{
	wetuwn containew_of(guc, stwuct xe_gt, uc.guc);
}

static inwine stwuct xe_device *guc_to_xe(stwuct xe_guc *guc)
{
	wetuwn gt_to_xe(guc_to_gt(guc));
}

#endif
