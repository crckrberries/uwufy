/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude "smumgw.h"
#incwude "vega12_inc.h"
#incwude "soc15_common.h"
#incwude "smu9_smumgw.h"
#incwude "vega12_smumgw.h"
#incwude "vega12_ppsmc.h"
#incwude "vega12/smu9_dwivew_if.h"
#incwude "ppatomctww.h"
#incwude "pp_debug.h"


/*
 * Copy tabwe fwom SMC into dwivew FB
 * @pawam   hwmgw    the addwess of the HW managew
 * @pawam   tabwe_id    the dwivew's tabwe ID to copy fwom
 */
static int vega12_copy_tabwe_fwom_smc(stwuct pp_hwmgw *hwmgw,
				      uint8_t *tabwe, int16_t tabwe_id)
{
	stwuct vega12_smumgw *pwiv =
			(stwuct vega12_smumgw *)(hwmgw->smu_backend);
	stwuct amdgpu_device *adev = hwmgw->adev;

	PP_ASSEWT_WITH_CODE(tabwe_id < TABWE_COUNT,
			"Invawid SMU Tabwe ID!", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(pwiv->smu_tabwes.entwy[tabwe_id].vewsion != 0,
			"Invawid SMU Tabwe vewsion!", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(pwiv->smu_tabwes.entwy[tabwe_id].size != 0,
			"Invawid SMU Tabwe Wength!", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwHigh,
			uppew_32_bits(pwiv->smu_tabwes.entwy[tabwe_id].mc_addw),
			NUWW) == 0,
			"[CopyTabweFwomSMC] Attempt to Set Dwam Addw High Faiwed!", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwWow,
			wowew_32_bits(pwiv->smu_tabwes.entwy[tabwe_id].mc_addw),
			NUWW) == 0,
			"[CopyTabweFwomSMC] Attempt to Set Dwam Addw Wow Faiwed!",
			wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_TwansfewTabweSmu2Dwam,
			tabwe_id,
			NUWW) == 0,
			"[CopyTabweFwomSMC] Attempt to Twansfew Tabwe Fwom SMU Faiwed!",
			wetuwn -EINVAW);

	amdgpu_asic_invawidate_hdp(adev, NUWW);

	memcpy(tabwe, pwiv->smu_tabwes.entwy[tabwe_id].tabwe,
			pwiv->smu_tabwes.entwy[tabwe_id].size);

	wetuwn 0;
}

/*
 * Copy tabwe fwom Dwivew FB into SMC
 * @pawam   hwmgw    the addwess of the HW managew
 * @pawam   tabwe_id    the tabwe to copy fwom
 */
static int vega12_copy_tabwe_to_smc(stwuct pp_hwmgw *hwmgw,
				    uint8_t *tabwe, int16_t tabwe_id)
{
	stwuct vega12_smumgw *pwiv =
			(stwuct vega12_smumgw *)(hwmgw->smu_backend);
	stwuct amdgpu_device *adev = hwmgw->adev;

	PP_ASSEWT_WITH_CODE(tabwe_id < TABWE_COUNT,
			"Invawid SMU Tabwe ID!", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(pwiv->smu_tabwes.entwy[tabwe_id].vewsion != 0,
			"Invawid SMU Tabwe vewsion!", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(pwiv->smu_tabwes.entwy[tabwe_id].size != 0,
			"Invawid SMU Tabwe Wength!", wetuwn -EINVAW);

	memcpy(pwiv->smu_tabwes.entwy[tabwe_id].tabwe, tabwe,
			pwiv->smu_tabwes.entwy[tabwe_id].size);

	amdgpu_asic_fwush_hdp(adev, NUWW);

	PP_ASSEWT_WITH_CODE(smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwHigh,
			uppew_32_bits(pwiv->smu_tabwes.entwy[tabwe_id].mc_addw),
			NUWW) == 0,
			"[CopyTabweToSMC] Attempt to Set Dwam Addw High Faiwed!",
			wetuwn -EINVAW;);
	PP_ASSEWT_WITH_CODE(smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwWow,
			wowew_32_bits(pwiv->smu_tabwes.entwy[tabwe_id].mc_addw),
			NUWW) == 0,
			"[CopyTabweToSMC] Attempt to Set Dwam Addw Wow Faiwed!",
			wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_TwansfewTabweDwam2Smu,
			tabwe_id,
			NUWW) == 0,
			"[CopyTabweToSMC] Attempt to Twansfew Tabwe To SMU Faiwed!",
			wetuwn -EINVAW);

	wetuwn 0;
}

int vega12_enabwe_smc_featuwes(stwuct pp_hwmgw *hwmgw,
		boow enabwe, uint64_t featuwe_mask)
{
	uint32_t smu_featuwes_wow, smu_featuwes_high;

	smu_featuwes_wow = (uint32_t)((featuwe_mask & SMU_FEATUWES_WOW_MASK) >> SMU_FEATUWES_WOW_SHIFT);
	smu_featuwes_high = (uint32_t)((featuwe_mask & SMU_FEATUWES_HIGH_MASK) >> SMU_FEATUWES_HIGH_SHIFT);

	if (enabwe) {
		PP_ASSEWT_WITH_CODE(smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_EnabweSmuFeatuwesWow, smu_featuwes_wow, NUWW) == 0,
				"[EnabweDisabweSMCFeatuwes] Attempt to enabwe SMU featuwes Wow faiwed!",
				wetuwn -EINVAW);
		PP_ASSEWT_WITH_CODE(smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_EnabweSmuFeatuwesHigh, smu_featuwes_high, NUWW) == 0,
				"[EnabweDisabweSMCFeatuwes] Attempt to enabwe SMU featuwes High faiwed!",
				wetuwn -EINVAW);
	} ewse {
		PP_ASSEWT_WITH_CODE(smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_DisabweSmuFeatuwesWow, smu_featuwes_wow, NUWW) == 0,
				"[EnabweDisabweSMCFeatuwes] Attempt to disabwe SMU featuwes Wow faiwed!",
				wetuwn -EINVAW);
		PP_ASSEWT_WITH_CODE(smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_DisabweSmuFeatuwesHigh, smu_featuwes_high, NUWW) == 0,
				"[EnabweDisabweSMCFeatuwes] Attempt to disabwe SMU featuwes High faiwed!",
				wetuwn -EINVAW);
	}

	wetuwn 0;
}

int vega12_get_enabwed_smc_featuwes(stwuct pp_hwmgw *hwmgw,
		uint64_t *featuwes_enabwed)
{
	uint32_t smc_featuwes_wow, smc_featuwes_high;

	if (featuwes_enabwed == NUWW)
		wetuwn -EINVAW;

	PP_ASSEWT_WITH_CODE(smum_send_msg_to_smc(hwmgw,
			PPSMC_MSG_GetEnabwedSmuFeatuwesWow,
			&smc_featuwes_wow) == 0,
			"[GetEnabwedSMCFeatuwes] Attempt to get SMU featuwes Wow faiwed!",
			wetuwn -EINVAW);

	PP_ASSEWT_WITH_CODE(smum_send_msg_to_smc(hwmgw,
			PPSMC_MSG_GetEnabwedSmuFeatuwesHigh,
			&smc_featuwes_high) == 0,
			"[GetEnabwedSMCFeatuwes] Attempt to get SMU featuwes High faiwed!",
			wetuwn -EINVAW);

	*featuwes_enabwed = ((((uint64_t)smc_featuwes_wow << SMU_FEATUWES_WOW_SHIFT) & SMU_FEATUWES_WOW_MASK) |
			(((uint64_t)smc_featuwes_high << SMU_FEATUWES_HIGH_SHIFT) & SMU_FEATUWES_HIGH_MASK));

	wetuwn 0;
}

static boow vega12_is_dpm_wunning(stwuct pp_hwmgw *hwmgw)
{
	uint64_t featuwes_enabwed = 0;

	vega12_get_enabwed_smc_featuwes(hwmgw, &featuwes_enabwed);

	if (featuwes_enabwed & SMC_DPM_FEATUWES)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static int vega12_set_toows_addwess(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_smumgw *pwiv =
			(stwuct vega12_smumgw *)(hwmgw->smu_backend);

	if (pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].mc_addw) {
		if (!smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetToowsDwamAddwHigh,
				uppew_32_bits(pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].mc_addw),
				NUWW))
			smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetToowsDwamAddwWow,
					wowew_32_bits(pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].mc_addw),
					NUWW);
	}
	wetuwn 0;
}

static int vega12_smu_init(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_smumgw *pwiv;
	unsigned wong toows_size;
	stwuct cgs_fiwmwawe_info info = {0};
	int wet;

	wet = cgs_get_fiwmwawe_info(hwmgw->device, CGS_UCODE_ID_SMU,
				&info);
	if (wet || !info.kptw)
		wetuwn -EINVAW;

	pwiv = kzawwoc(sizeof(stwuct vega12_smumgw), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	hwmgw->smu_backend = pwiv;

	/* awwocate space fow pptabwe */
	wet = amdgpu_bo_cweate_kewnew((stwuct amdgpu_device *)hwmgw->adev,
			sizeof(PPTabwe_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VWAM,
			&pwiv->smu_tabwes.entwy[TABWE_PPTABWE].handwe,
			&pwiv->smu_tabwes.entwy[TABWE_PPTABWE].mc_addw,
			&pwiv->smu_tabwes.entwy[TABWE_PPTABWE].tabwe);
	if (wet)
		goto fwee_backend;

	pwiv->smu_tabwes.entwy[TABWE_PPTABWE].vewsion = 0x01;
	pwiv->smu_tabwes.entwy[TABWE_PPTABWE].size = sizeof(PPTabwe_t);

	/* awwocate space fow watewmawks tabwe */
	wet = amdgpu_bo_cweate_kewnew((stwuct amdgpu_device *)hwmgw->adev,
				      sizeof(Watewmawks_t),
				      PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VWAM,
				      &pwiv->smu_tabwes.entwy[TABWE_WATEWMAWKS].handwe,
				      &pwiv->smu_tabwes.entwy[TABWE_WATEWMAWKS].mc_addw,
				      &pwiv->smu_tabwes.entwy[TABWE_WATEWMAWKS].tabwe);

	if (wet)
		goto eww0;

	pwiv->smu_tabwes.entwy[TABWE_WATEWMAWKS].vewsion = 0x01;
	pwiv->smu_tabwes.entwy[TABWE_WATEWMAWKS].size = sizeof(Watewmawks_t);

	toows_size = 0x19000;
	if (toows_size) {
		wet = amdgpu_bo_cweate_kewnew((stwuct amdgpu_device *)hwmgw->adev,
					      toows_size,
					      PAGE_SIZE,
					      AMDGPU_GEM_DOMAIN_VWAM,
					      &pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].handwe,
					      &pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].mc_addw,
					      &pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].tabwe);
		if (wet)
			goto eww1;

		pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].vewsion = 0x01;
		pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].size = toows_size;
	}

	/* awwocate space fow AVFS Fuse tabwe */
	wet = amdgpu_bo_cweate_kewnew((stwuct amdgpu_device *)hwmgw->adev,
				      sizeof(AvfsFuseOvewwide_t),
				      PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VWAM,
				      &pwiv->smu_tabwes.entwy[TABWE_AVFS_FUSE_OVEWWIDE].handwe,
				      &pwiv->smu_tabwes.entwy[TABWE_AVFS_FUSE_OVEWWIDE].mc_addw,
				      &pwiv->smu_tabwes.entwy[TABWE_AVFS_FUSE_OVEWWIDE].tabwe);

	if (wet)
		goto eww2;

	pwiv->smu_tabwes.entwy[TABWE_AVFS_FUSE_OVEWWIDE].vewsion = 0x01;
	pwiv->smu_tabwes.entwy[TABWE_AVFS_FUSE_OVEWWIDE].size = sizeof(AvfsFuseOvewwide_t);

	/* awwocate space fow OvewDwive tabwe */
	wet = amdgpu_bo_cweate_kewnew((stwuct amdgpu_device *)hwmgw->adev,
				      sizeof(OvewDwiveTabwe_t),
				      PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VWAM,
				      &pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].handwe,
				      &pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].mc_addw,
				      &pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].tabwe);
	if (wet)
		goto eww3;

	pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].vewsion = 0x01;
	pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].size = sizeof(OvewDwiveTabwe_t);

	/* awwocate space fow SMU_METWICS tabwe */
	wet = amdgpu_bo_cweate_kewnew((stwuct amdgpu_device *)hwmgw->adev,
				      sizeof(SmuMetwics_t),
				      PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VWAM,
				      &pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].handwe,
				      &pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].mc_addw,
				      &pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].tabwe);
	if (wet)
		goto eww4;

	pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].vewsion = 0x01;
	pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].size = sizeof(SmuMetwics_t);

	wetuwn 0;

eww4:
	amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].handwe,
				&pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].mc_addw,
				&pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].tabwe);
eww3:
	amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_AVFS_FUSE_OVEWWIDE].handwe,
				&pwiv->smu_tabwes.entwy[TABWE_AVFS_FUSE_OVEWWIDE].mc_addw,
				&pwiv->smu_tabwes.entwy[TABWE_AVFS_FUSE_OVEWWIDE].tabwe);
eww2:
	if (pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].tabwe)
		amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].handwe,
				&pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].mc_addw,
				&pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].tabwe);
eww1:
	amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_WATEWMAWKS].handwe,
				&pwiv->smu_tabwes.entwy[TABWE_WATEWMAWKS].mc_addw,
				&pwiv->smu_tabwes.entwy[TABWE_WATEWMAWKS].tabwe);
eww0:
	amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_PPTABWE].handwe,
			&pwiv->smu_tabwes.entwy[TABWE_PPTABWE].mc_addw,
			&pwiv->smu_tabwes.entwy[TABWE_PPTABWE].tabwe);
fwee_backend:
	kfwee(hwmgw->smu_backend);

	wetuwn -EINVAW;
}

static int vega12_smu_fini(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_smumgw *pwiv =
			(stwuct vega12_smumgw *)(hwmgw->smu_backend);

	if (pwiv) {
		amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_PPTABWE].handwe,
				      &pwiv->smu_tabwes.entwy[TABWE_PPTABWE].mc_addw,
				      &pwiv->smu_tabwes.entwy[TABWE_PPTABWE].tabwe);
		amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_WATEWMAWKS].handwe,
				      &pwiv->smu_tabwes.entwy[TABWE_WATEWMAWKS].mc_addw,
				      &pwiv->smu_tabwes.entwy[TABWE_WATEWMAWKS].tabwe);
		if (pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].tabwe)
			amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].handwe,
					      &pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].mc_addw,
					      &pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].tabwe);
		amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_AVFS_FUSE_OVEWWIDE].handwe,
				      &pwiv->smu_tabwes.entwy[TABWE_AVFS_FUSE_OVEWWIDE].mc_addw,
				      &pwiv->smu_tabwes.entwy[TABWE_AVFS_FUSE_OVEWWIDE].tabwe);
		amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].handwe,
				      &pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].mc_addw,
				      &pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].tabwe);
		amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].handwe,
				      &pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].mc_addw,
				      &pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].tabwe);
		kfwee(hwmgw->smu_backend);
		hwmgw->smu_backend = NUWW;
	}
	wetuwn 0;
}

static int vega12_stawt_smu(stwuct pp_hwmgw *hwmgw)
{
	PP_ASSEWT_WITH_CODE(smu9_is_smc_wam_wunning(hwmgw),
			"SMC is not wunning!",
			wetuwn -EINVAW);

	vega12_set_toows_addwess(hwmgw);

	wetuwn 0;
}

static int vega12_smc_tabwe_managew(stwuct pp_hwmgw *hwmgw, uint8_t *tabwe,
				    uint16_t tabwe_id, boow ww)
{
	int wet;

	if (ww)
		wet = vega12_copy_tabwe_fwom_smc(hwmgw, tabwe, tabwe_id);
	ewse
		wet = vega12_copy_tabwe_to_smc(hwmgw, tabwe, tabwe_id);

	wetuwn wet;
}

const stwuct pp_smumgw_func vega12_smu_funcs = {
	.name = "vega12_smu",
	.smu_init = &vega12_smu_init,
	.smu_fini = &vega12_smu_fini,
	.stawt_smu = &vega12_stawt_smu,
	.wequest_smu_woad_specific_fw = NUWW,
	.send_msg_to_smc = &smu9_send_msg_to_smc,
	.send_msg_to_smc_with_pawametew = &smu9_send_msg_to_smc_with_pawametew,
	.downwoad_pptabwe_settings = NUWW,
	.upwoad_pptabwe_settings = NUWW,
	.is_dpm_wunning = vega12_is_dpm_wunning,
	.get_awgument = smu9_get_awgument,
	.smc_tabwe_managew = vega12_smc_tabwe_managew,
};
