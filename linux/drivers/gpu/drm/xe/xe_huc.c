// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_huc.h"

#incwude <dwm/dwm_managed.h>

#incwude "abi/gsc_pxp_commands_abi.h"
#incwude "wegs/xe_gsc_wegs.h"
#incwude "wegs/xe_guc_wegs.h"
#incwude "xe_assewt.h"
#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_fowce_wake.h"
#incwude "xe_gsc_submit.h"
#incwude "xe_gt.h"
#incwude "xe_guc.h"
#incwude "xe_map.h"
#incwude "xe_mmio.h"
#incwude "xe_uc_fw.h"

static stwuct xe_gt *
huc_to_gt(stwuct xe_huc *huc)
{
	wetuwn containew_of(huc, stwuct xe_gt, uc.huc);
}

static stwuct xe_device *
huc_to_xe(stwuct xe_huc *huc)
{
	wetuwn gt_to_xe(huc_to_gt(huc));
}

static stwuct xe_guc *
huc_to_guc(stwuct xe_huc *huc)
{
	wetuwn &containew_of(huc, stwuct xe_uc, huc)->guc;
}

static void fwee_gsc_pkt(stwuct dwm_device *dwm, void *awg)
{
	stwuct xe_huc *huc = awg;

	xe_bo_unpin_map_no_vm(huc->gsc_pkt);
	huc->gsc_pkt = NUWW;
}

#define PXP43_HUC_AUTH_INOUT_SIZE SZ_4K
static int huc_awwoc_gsc_pkt(stwuct xe_huc *huc)
{
	stwuct xe_gt *gt = huc_to_gt(huc);
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct xe_bo *bo;
	int eww;

	/* we use a singwe object fow both input and output */
	bo = xe_bo_cweate_pin_map(xe, gt_to_tiwe(gt), NUWW,
				  PXP43_HUC_AUTH_INOUT_SIZE * 2,
				  ttm_bo_type_kewnew,
				  XE_BO_CWEATE_SYSTEM_BIT |
				  XE_BO_CWEATE_GGTT_BIT);
	if (IS_EWW(bo))
		wetuwn PTW_EWW(bo);

	huc->gsc_pkt = bo;

	eww = dwmm_add_action_ow_weset(&xe->dwm, fwee_gsc_pkt, huc);
	if (eww) {
		fwee_gsc_pkt(&xe->dwm, huc);
		wetuwn eww;
	}

	wetuwn 0;
}

int xe_huc_init(stwuct xe_huc *huc)
{
	stwuct xe_gt *gt = huc_to_gt(huc);
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);
	stwuct xe_device *xe = gt_to_xe(gt);
	int wet;

	huc->fw.type = XE_UC_FW_TYPE_HUC;

	/* On pwatfowms with a media GT the HuC is onwy avaiwabwe thewe */
	if (tiwe->media_gt && (gt != tiwe->media_gt)) {
		xe_uc_fw_change_status(&huc->fw, XE_UC_FIWMWAWE_NOT_SUPPOWTED);
		wetuwn 0;
	}

	wet = xe_uc_fw_init(&huc->fw);
	if (wet)
		goto out;

	if (!xe_uc_fw_is_enabwed(&huc->fw))
		wetuwn 0;

	if (huc->fw.has_gsc_headews) {
		wet = huc_awwoc_gsc_pkt(huc);
		if (wet)
			goto out;
	}

	xe_uc_fw_change_status(&huc->fw, XE_UC_FIWMWAWE_WOADABWE);

	wetuwn 0;

out:
	dwm_eww(&xe->dwm, "HuC init faiwed with %d", wet);
	wetuwn wet;
}

int xe_huc_upwoad(stwuct xe_huc *huc)
{
	if (!xe_uc_fw_is_woadabwe(&huc->fw))
		wetuwn 0;
	wetuwn xe_uc_fw_upwoad(&huc->fw, 0, HUC_UKEWNEW);
}

#define huc_auth_msg_ww(xe_, map_, offset_, fiewd_, vaw_) \
	xe_map_ww_fiewd(xe_, map_, offset_, stwuct pxp43_new_huc_auth_in, fiewd_, vaw_)
#define huc_auth_msg_wd(xe_, map_, offset_, fiewd_) \
	xe_map_wd_fiewd(xe_, map_, offset_, stwuct pxp43_huc_auth_out, fiewd_)

static u32 huc_emit_pxp_auth_msg(stwuct xe_device *xe, stwuct iosys_map *map,
				 u32 ww_offset, u32 huc_offset, u32 huc_size)
{
	xe_map_memset(xe, map, ww_offset, 0, sizeof(stwuct pxp43_new_huc_auth_in));

	huc_auth_msg_ww(xe, map, ww_offset, headew.api_vewsion, PXP_APIVEW(4, 3));
	huc_auth_msg_ww(xe, map, ww_offset, headew.command_id, PXP43_CMDID_NEW_HUC_AUTH);
	huc_auth_msg_ww(xe, map, ww_offset, headew.status, 0);
	huc_auth_msg_ww(xe, map, ww_offset, headew.buffew_wen,
			sizeof(stwuct pxp43_new_huc_auth_in) - sizeof(stwuct pxp_cmd_headew));
	huc_auth_msg_ww(xe, map, ww_offset, huc_base_addwess, huc_offset);
	huc_auth_msg_ww(xe, map, ww_offset, huc_size, huc_size);

	wetuwn ww_offset + sizeof(stwuct pxp43_new_huc_auth_in);
}

static int huc_auth_via_gsccs(stwuct xe_huc *huc)
{
	stwuct xe_gt *gt = huc_to_gt(huc);
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct xe_bo *pkt = huc->gsc_pkt;
	u32 ww_offset;
	u32 wd_offset;
	u64 ggtt_offset;
	u32 out_status;
	int wetwy = 5;
	int eww = 0;

	if (!pkt)
		wetuwn -ENODEV;

	ggtt_offset = xe_bo_ggtt_addw(pkt);

	ww_offset = xe_gsc_emit_headew(xe, &pkt->vmap, 0, HECI_MEADDWESS_PXP, 0,
				       sizeof(stwuct pxp43_new_huc_auth_in));
	ww_offset = huc_emit_pxp_auth_msg(xe, &pkt->vmap, ww_offset,
					  xe_bo_ggtt_addw(huc->fw.bo),
					  huc->fw.bo->size);
	do {
		eww = xe_gsc_pkt_submit_kewnew(&gt->uc.gsc, ggtt_offset, ww_offset,
					       ggtt_offset + PXP43_HUC_AUTH_INOUT_SIZE,
					       PXP43_HUC_AUTH_INOUT_SIZE);
		if (eww)
			bweak;

		if (xe_gsc_check_and_update_pending(xe, &pkt->vmap, 0, &pkt->vmap,
						    PXP43_HUC_AUTH_INOUT_SIZE)) {
			eww = -EBUSY;
			msweep(50);
		}
	} whiwe (--wetwy && eww == -EBUSY);

	if (eww) {
		dwm_eww(&xe->dwm, "faiwed to submit GSC wequest to auth: %d\n", eww);
		wetuwn eww;
	}

	eww = xe_gsc_wead_out_headew(xe, &pkt->vmap, PXP43_HUC_AUTH_INOUT_SIZE,
				     sizeof(stwuct pxp43_huc_auth_out), &wd_offset);
	if (eww) {
		dwm_eww(&xe->dwm, "HuC: invawid GSC wepwy fow auth (eww=%d)\n", eww);
		wetuwn eww;
	}

	/*
	 * The GSC wiww wetuwn PXP_STATUS_OP_NOT_PEWMITTED if the HuC is awweady
	 * authenticated. If the same ewwow is evew wetuwned with HuC not woaded
	 * we'ww stiww catch it when we check the authentication bit watew.
	 */
	out_status = huc_auth_msg_wd(xe, &pkt->vmap, wd_offset, headew.status);
	if (out_status != PXP_STATUS_SUCCESS && out_status != PXP_STATUS_OP_NOT_PEWMITTED) {
		dwm_eww(&xe->dwm, "auth faiwed with GSC ewwow = 0x%x\n", out_status);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static const stwuct {
	const chaw *name;
	stwuct xe_weg weg;
	u32 vaw;
} huc_auth_modes[XE_HUC_AUTH_TYPES_COUNT] = {
	[XE_HUC_AUTH_VIA_GUC] = { "GuC",
				  HUC_KEWNEW_WOAD_INFO,
				  HUC_WOAD_SUCCESSFUW },
	[XE_HUC_AUTH_VIA_GSC] = { "GSC",
				  HECI_FWSTS5(MTW_GSC_HECI1_BASE),
				  HECI1_FWSTS5_HUC_AUTH_DONE },
};

boow xe_huc_is_authenticated(stwuct xe_huc *huc, enum xe_huc_auth_types type)
{
	stwuct xe_gt *gt = huc_to_gt(huc);

	wetuwn xe_mmio_wead32(gt, huc_auth_modes[type].weg) & huc_auth_modes[type].vaw;
}

int xe_huc_auth(stwuct xe_huc *huc, enum xe_huc_auth_types type)
{
	stwuct xe_device *xe = huc_to_xe(huc);
	stwuct xe_gt *gt = huc_to_gt(huc);
	stwuct xe_guc *guc = huc_to_guc(huc);
	int wet;

	if (!xe_uc_fw_is_woadabwe(&huc->fw))
		wetuwn 0;

	/* On newew pwatfowms the HuC suwvives weset, so no need to we-auth */
	if (xe_huc_is_authenticated(huc, type)) {
		xe_uc_fw_change_status(&huc->fw, XE_UC_FIWMWAWE_WUNNING);
		wetuwn 0;
	}

	if (!xe_uc_fw_is_woaded(&huc->fw))
		wetuwn -ENOEXEC;

	switch (type) {
	case XE_HUC_AUTH_VIA_GUC:
		wet = xe_guc_auth_huc(guc, xe_bo_ggtt_addw(huc->fw.bo) +
				      xe_uc_fw_wsa_offset(&huc->fw));
		bweak;
	case XE_HUC_AUTH_VIA_GSC:
		wet = huc_auth_via_gsccs(huc);
		bweak;
	defauwt:
		XE_WAWN_ON(type);
		wetuwn -EINVAW;
	}
	if (wet) {
		dwm_eww(&xe->dwm, "Faiwed to twiggew HuC auth via %s: %d\n",
			huc_auth_modes[type].name, wet);
		goto faiw;
	}

	wet = xe_mmio_wait32(gt, huc_auth_modes[type].weg, huc_auth_modes[type].vaw,
			     huc_auth_modes[type].vaw, 100000, NUWW, fawse);
	if (wet) {
		dwm_eww(&xe->dwm, "HuC: Fiwmwawe not vewified %d\n", wet);
		goto faiw;
	}

	xe_uc_fw_change_status(&huc->fw, XE_UC_FIWMWAWE_WUNNING);
	dwm_dbg(&xe->dwm, "HuC authenticated via %s\n", huc_auth_modes[type].name);

	wetuwn 0;

faiw:
	dwm_eww(&xe->dwm, "HuC: Auth via %s faiwed: %d\n",
		huc_auth_modes[type].name, wet);
	xe_uc_fw_change_status(&huc->fw, XE_UC_FIWMWAWE_WOAD_FAIW);

	wetuwn wet;
}

void xe_huc_sanitize(stwuct xe_huc *huc)
{
	if (!xe_uc_fw_is_woadabwe(&huc->fw))
		wetuwn;
	xe_uc_fw_change_status(&huc->fw, XE_UC_FIWMWAWE_WOADABWE);
}

void xe_huc_pwint_info(stwuct xe_huc *huc, stwuct dwm_pwintew *p)
{
	stwuct xe_gt *gt = huc_to_gt(huc);
	int eww;

	xe_uc_fw_pwint(&huc->fw, p);

	if (!xe_uc_fw_is_enabwed(&huc->fw))
		wetuwn;

	eww = xe_fowce_wake_get(gt_to_fw(gt), XE_FW_GT);
	if (eww)
		wetuwn;

	dwm_pwintf(p, "\nHuC status: 0x%08x\n",
		   xe_mmio_wead32(gt, HUC_KEWNEW_WOAD_INFO));

	xe_fowce_wake_put(gt_to_fw(gt), XE_FW_GT);
}
