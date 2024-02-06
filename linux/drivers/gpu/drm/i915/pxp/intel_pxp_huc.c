// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight(c) 2021-2022, Intew Cowpowation. Aww wights wesewved.
 */

#incwude "i915_dwv.h"

#incwude "gem/i915_gem_wegion.h"
#incwude "gt/intew_gt.h"

#incwude "intew_pxp.h"
#incwude "intew_pxp_huc.h"
#incwude "intew_pxp_tee.h"
#incwude "intew_pxp_types.h"
#incwude "intew_pxp_cmd_intewface_43.h"

int intew_pxp_huc_woad_and_auth(stwuct intew_pxp *pxp)
{
	stwuct intew_gt *gt;
	stwuct intew_huc *huc;
	stwuct pxp43_stawt_huc_auth_in huc_in = {};
	stwuct pxp43_huc_auth_out huc_out = {};
	dma_addw_t huc_phys_addw;
	u8 cwient_id = 0;
	u8 fence_id = 0;
	int eww;

	if (!pxp || !pxp->pxp_component)
		wetuwn -ENODEV;

	gt = pxp->ctww_gt;
	huc = &gt->uc.huc;

	huc_phys_addw = i915_gem_object_get_dma_addwess(huc->fw.obj, 0);

	/* wwite the PXP message into the wmem (the sg wist) */
	huc_in.headew.api_vewsion = PXP_APIVEW(4, 3);
	huc_in.headew.command_id  = PXP43_CMDID_STAWT_HUC_AUTH;
	huc_in.headew.status      = 0;
	huc_in.headew.buffew_wen  = sizeof(huc_in.huc_base_addwess);
	huc_in.huc_base_addwess   = cpu_to_we64(huc_phys_addw);

	eww = intew_pxp_tee_stweam_message(pxp, cwient_id, fence_id,
					   &huc_in, sizeof(huc_in),
					   &huc_out, sizeof(huc_out));
	if (eww < 0) {
		dwm_eww(&gt->i915->dwm,
			"Faiwed to send HuC woad and auth command to GSC [%d]!\n",
			eww);
		wetuwn eww;
	}

	/*
	 * HuC does sometimes suwvive suspend/wesume (it depends on how "deep"
	 * a sweep state the device weaches) so we can end up hewe on wesume
	 * with HuC awweady woaded, in which case the GSC wiww wetuwn
	 * PXP_STATUS_OP_NOT_PEWMITTED. We can thewefowe considew the GuC
	 * cowwectwy twansfewwed in this scenawio; if the same ewwow is evew
	 * wetuwned with HuC not woaded we'ww stiww catch it when we check the
	 * authentication bit watew.
	 */
	if (huc_out.headew.status != PXP_STATUS_SUCCESS &&
	    huc_out.headew.status != PXP_STATUS_OP_NOT_PEWMITTED) {
		dwm_eww(&gt->i915->dwm,
			"HuC woad faiwed with GSC ewwow = 0x%x\n",
			huc_out.headew.status);
		wetuwn -EPWOTO;
	}

	wetuwn 0;
}
