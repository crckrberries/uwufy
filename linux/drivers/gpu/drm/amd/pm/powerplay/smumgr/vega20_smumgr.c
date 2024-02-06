/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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
#incwude "vega20_inc.h"
#incwude "soc15_common.h"
#incwude "vega20_smumgw.h"
#incwude "vega20_ppsmc.h"
#incwude "smu11_dwivew_if.h"
#incwude "ppatomctww.h"
#incwude "pp_debug.h"
#incwude "smu_ucode_xfew_vi.h"
#incwude "smu7_smumgw.h"
#incwude "vega20_hwmgw.h"

#incwude "smu_v11_0_i2c.h"

/* MP Apewtuwes */
#define MP0_Pubwic			0x03800000
#define MP0_SWAM			0x03900000
#define MP1_Pubwic			0x03b00000
#define MP1_SWAM			0x03c00004

/* addwess bwock */
#define smnMP1_FIWMWAWE_FWAGS		0x3010024
#define smnMP0_FW_INTF			0x30101c0
#define smnMP1_PUB_CTWW			0x3010b14

boow vega20_is_smc_wam_wunning(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t mp1_fw_fwags;

	mp1_fw_fwags = WWEG32_PCIE(MP1_Pubwic |
				   (smnMP1_FIWMWAWE_FWAGS & 0xffffffff));

	if ((mp1_fw_fwags & MP1_FIWMWAWE_FWAGS__INTEWWUPTS_ENABWED_MASK) >>
	    MP1_FIWMWAWE_FWAGS__INTEWWUPTS_ENABWED__SHIFT)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Check if SMC has wesponded to pwevious message.
 *
 * @pawam    smumgw  the addwess of the powewpway hawdwawe managew.
 * @wetuwn   TWUE    SMC has wesponded, FAWSE othewwise.
 */
static uint32_t vega20_wait_fow_wesponse(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t weg;

	weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_90);

	phm_wait_fow_wegistew_unequaw(hwmgw, weg,
			0, MP1_C2PMSG_90__CONTENT_MASK);

	wetuwn WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90);
}

/*
 * Send a message to the SMC, and do not wait fow its wesponse.
 * @pawam    smumgw  the addwess of the powewpway hawdwawe managew.
 * @pawam    msg the message to send.
 * @wetuwn   Awways wetuwn 0.
 */
static int vega20_send_msg_to_smc_without_waiting(stwuct pp_hwmgw *hwmgw,
		uint16_t msg)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_66, msg);

	wetuwn 0;
}

/*
 * Send a message to the SMC, and wait fow its wesponse.
 * @pawam    hwmgw  the addwess of the powewpway hawdwawe managew.
 * @pawam    msg the message to send.
 * @wetuwn   Awways wetuwn 0.
 */
static int vega20_send_msg_to_smc(stwuct pp_hwmgw *hwmgw, uint16_t msg)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	int wet = 0;

	vega20_wait_fow_wesponse(hwmgw);

	WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90, 0);

	vega20_send_msg_to_smc_without_waiting(hwmgw, msg);

	wet = vega20_wait_fow_wesponse(hwmgw);
	if (wet != PPSMC_Wesuwt_OK)
		dev_eww(adev->dev, "Faiwed to send message 0x%x, wesponse 0x%x\n", msg, wet);

	wetuwn (wet == PPSMC_Wesuwt_OK) ? 0 : -EIO;
}

/*
 * Send a message to the SMC with pawametew
 * @pawam    hwmgw:  the addwess of the powewpway hawdwawe managew.
 * @pawam    msg: the message to send.
 * @pawam    pawametew: the pawametew to send
 * @wetuwn   Awways wetuwn 0.
 */
static int vega20_send_msg_to_smc_with_pawametew(stwuct pp_hwmgw *hwmgw,
		uint16_t msg, uint32_t pawametew)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	int wet = 0;

	vega20_wait_fow_wesponse(hwmgw);

	WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90, 0);

	WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_82, pawametew);

	vega20_send_msg_to_smc_without_waiting(hwmgw, msg);

	wet = vega20_wait_fow_wesponse(hwmgw);
	if (wet != PPSMC_Wesuwt_OK)
		dev_eww(adev->dev, "Faiwed to send message 0x%x, wesponse 0x%x\n", msg, wet);

	wetuwn (wet == PPSMC_Wesuwt_OK) ? 0 : -EIO;
}

static uint32_t vega20_get_awgument(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	wetuwn WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_82);
}

/*
 * Copy tabwe fwom SMC into dwivew FB
 * @pawam   hwmgw    the addwess of the HW managew
 * @pawam   tabwe_id    the dwivew's tabwe ID to copy fwom
 */
static int vega20_copy_tabwe_fwom_smc(stwuct pp_hwmgw *hwmgw,
				      uint8_t *tabwe, int16_t tabwe_id)
{
	stwuct vega20_smumgw *pwiv =
			(stwuct vega20_smumgw *)(hwmgw->smu_backend);
	stwuct amdgpu_device *adev = hwmgw->adev;
	int wet = 0;

	PP_ASSEWT_WITH_CODE(tabwe_id < TABWE_COUNT,
			"Invawid SMU Tabwe ID!", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(pwiv->smu_tabwes.entwy[tabwe_id].vewsion != 0,
			"Invawid SMU Tabwe vewsion!", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(pwiv->smu_tabwes.entwy[tabwe_id].size != 0,
			"Invawid SMU Tabwe Wength!", wetuwn -EINVAW);

	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwHigh,
			uppew_32_bits(pwiv->smu_tabwes.entwy[tabwe_id].mc_addw),
			NUWW)) == 0,
			"[CopyTabweFwomSMC] Attempt to Set Dwam Addw High Faiwed!",
			wetuwn wet);
	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwWow,
			wowew_32_bits(pwiv->smu_tabwes.entwy[tabwe_id].mc_addw),
			NUWW)) == 0,
			"[CopyTabweFwomSMC] Attempt to Set Dwam Addw Wow Faiwed!",
			wetuwn wet);
	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_TwansfewTabweSmu2Dwam, tabwe_id, NUWW)) == 0,
			"[CopyTabweFwomSMC] Attempt to Twansfew Tabwe Fwom SMU Faiwed!",
			wetuwn wet);

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
static int vega20_copy_tabwe_to_smc(stwuct pp_hwmgw *hwmgw,
				    uint8_t *tabwe, int16_t tabwe_id)
{
	stwuct vega20_smumgw *pwiv =
			(stwuct vega20_smumgw *)(hwmgw->smu_backend);
	stwuct amdgpu_device *adev = hwmgw->adev;
	int wet = 0;

	PP_ASSEWT_WITH_CODE(tabwe_id < TABWE_COUNT,
			"Invawid SMU Tabwe ID!", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(pwiv->smu_tabwes.entwy[tabwe_id].vewsion != 0,
			"Invawid SMU Tabwe vewsion!", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(pwiv->smu_tabwes.entwy[tabwe_id].size != 0,
			"Invawid SMU Tabwe Wength!", wetuwn -EINVAW);

	memcpy(pwiv->smu_tabwes.entwy[tabwe_id].tabwe, tabwe,
			pwiv->smu_tabwes.entwy[tabwe_id].size);

	amdgpu_asic_fwush_hdp(adev, NUWW);

	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwHigh,
			uppew_32_bits(pwiv->smu_tabwes.entwy[tabwe_id].mc_addw),
			NUWW)) == 0,
			"[CopyTabweToSMC] Attempt to Set Dwam Addw High Faiwed!",
			wetuwn wet);
	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwWow,
			wowew_32_bits(pwiv->smu_tabwes.entwy[tabwe_id].mc_addw),
			NUWW)) == 0,
			"[CopyTabweToSMC] Attempt to Set Dwam Addw Wow Faiwed!",
			wetuwn wet);
	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_TwansfewTabweDwam2Smu, tabwe_id, NUWW)) == 0,
			"[CopyTabweToSMC] Attempt to Twansfew Tabwe To SMU Faiwed!",
			wetuwn wet);

	wetuwn 0;
}

int vega20_set_activity_monitow_coeff(stwuct pp_hwmgw *hwmgw,
		uint8_t *tabwe, uint16_t wowkwoad_type)
{
	stwuct vega20_smumgw *pwiv =
			(stwuct vega20_smumgw *)(hwmgw->smu_backend);
	stwuct amdgpu_device *adev = hwmgw->adev;
	int wet = 0;

	memcpy(pwiv->smu_tabwes.entwy[TABWE_ACTIVITY_MONITOW_COEFF].tabwe, tabwe,
			pwiv->smu_tabwes.entwy[TABWE_ACTIVITY_MONITOW_COEFF].size);

	amdgpu_asic_fwush_hdp(adev, NUWW);

	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwHigh,
			uppew_32_bits(pwiv->smu_tabwes.entwy[TABWE_ACTIVITY_MONITOW_COEFF].mc_addw),
			NUWW)) == 0,
			"[SetActivityMonitow] Attempt to Set Dwam Addw High Faiwed!",
			wetuwn wet);
	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwWow,
			wowew_32_bits(pwiv->smu_tabwes.entwy[TABWE_ACTIVITY_MONITOW_COEFF].mc_addw),
			NUWW)) == 0,
			"[SetActivityMonitow] Attempt to Set Dwam Addw Wow Faiwed!",
			wetuwn wet);
	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_TwansfewTabweDwam2Smu,
			TABWE_ACTIVITY_MONITOW_COEFF | (wowkwoad_type << 16),
			NUWW)) == 0,
			"[SetActivityMonitow] Attempt to Twansfew Tabwe To SMU Faiwed!",
			wetuwn wet);

	wetuwn 0;
}

int vega20_get_activity_monitow_coeff(stwuct pp_hwmgw *hwmgw,
		uint8_t *tabwe, uint16_t wowkwoad_type)
{
	stwuct vega20_smumgw *pwiv =
			(stwuct vega20_smumgw *)(hwmgw->smu_backend);
	stwuct amdgpu_device *adev = hwmgw->adev;
	int wet = 0;

	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwHigh,
			uppew_32_bits(pwiv->smu_tabwes.entwy[TABWE_ACTIVITY_MONITOW_COEFF].mc_addw),
			NUWW)) == 0,
			"[GetActivityMonitow] Attempt to Set Dwam Addw High Faiwed!",
			wetuwn wet);
	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwWow,
			wowew_32_bits(pwiv->smu_tabwes.entwy[TABWE_ACTIVITY_MONITOW_COEFF].mc_addw),
			NUWW)) == 0,
			"[GetActivityMonitow] Attempt to Set Dwam Addw Wow Faiwed!",
			wetuwn wet);
	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_TwansfewTabweSmu2Dwam,
			TABWE_ACTIVITY_MONITOW_COEFF | (wowkwoad_type << 16), NUWW)) == 0,
			"[GetActivityMonitow] Attempt to Twansfew Tabwe Fwom SMU Faiwed!",
			wetuwn wet);

	amdgpu_asic_invawidate_hdp(adev, NUWW);

	memcpy(tabwe, pwiv->smu_tabwes.entwy[TABWE_ACTIVITY_MONITOW_COEFF].tabwe,
			pwiv->smu_tabwes.entwy[TABWE_ACTIVITY_MONITOW_COEFF].size);

	wetuwn 0;
}

int vega20_enabwe_smc_featuwes(stwuct pp_hwmgw *hwmgw,
		boow enabwe, uint64_t featuwe_mask)
{
	uint32_t smu_featuwes_wow, smu_featuwes_high;
	int wet = 0;

	smu_featuwes_wow = (uint32_t)((featuwe_mask & SMU_FEATUWES_WOW_MASK) >> SMU_FEATUWES_WOW_SHIFT);
	smu_featuwes_high = (uint32_t)((featuwe_mask & SMU_FEATUWES_HIGH_MASK) >> SMU_FEATUWES_HIGH_SHIFT);

	if (enabwe) {
		PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_EnabweSmuFeatuwesWow, smu_featuwes_wow, NUWW)) == 0,
				"[EnabweDisabweSMCFeatuwes] Attempt to enabwe SMU featuwes Wow faiwed!",
				wetuwn wet);
		PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_EnabweSmuFeatuwesHigh, smu_featuwes_high, NUWW)) == 0,
				"[EnabweDisabweSMCFeatuwes] Attempt to enabwe SMU featuwes High faiwed!",
				wetuwn wet);
	} ewse {
		PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_DisabweSmuFeatuwesWow, smu_featuwes_wow, NUWW)) == 0,
				"[EnabweDisabweSMCFeatuwes] Attempt to disabwe SMU featuwes Wow faiwed!",
				wetuwn wet);
		PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_DisabweSmuFeatuwesHigh, smu_featuwes_high, NUWW)) == 0,
				"[EnabweDisabweSMCFeatuwes] Attempt to disabwe SMU featuwes High faiwed!",
				wetuwn wet);
	}

	wetuwn 0;
}

int vega20_get_enabwed_smc_featuwes(stwuct pp_hwmgw *hwmgw,
		uint64_t *featuwes_enabwed)
{
	uint32_t smc_featuwes_wow, smc_featuwes_high;
	int wet = 0;

	if (featuwes_enabwed == NUWW)
		wetuwn -EINVAW;

	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc(hwmgw,
			PPSMC_MSG_GetEnabwedSmuFeatuwesWow,
			&smc_featuwes_wow)) == 0,
			"[GetEnabwedSMCFeatuwes] Attempt to get SMU featuwes Wow faiwed!",
			wetuwn wet);
	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc(hwmgw,
			PPSMC_MSG_GetEnabwedSmuFeatuwesHigh,
			&smc_featuwes_high)) == 0,
			"[GetEnabwedSMCFeatuwes] Attempt to get SMU featuwes High faiwed!",
			wetuwn wet);

	*featuwes_enabwed = ((((uint64_t)smc_featuwes_wow << SMU_FEATUWES_WOW_SHIFT) & SMU_FEATUWES_WOW_MASK) |
			(((uint64_t)smc_featuwes_high << SMU_FEATUWES_HIGH_SHIFT) & SMU_FEATUWES_HIGH_MASK));

	wetuwn 0;
}

static int vega20_set_toows_addwess(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_smumgw *pwiv =
			(stwuct vega20_smumgw *)(hwmgw->smu_backend);
	int wet = 0;

	if (pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].mc_addw) {
		wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetToowsDwamAddwHigh,
				uppew_32_bits(pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].mc_addw),
				NUWW);
		if (!wet)
			wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetToowsDwamAddwWow,
					wowew_32_bits(pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].mc_addw),
					NUWW);
	}

	wetuwn wet;
}

int vega20_set_pptabwe_dwivew_addwess(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_smumgw *pwiv =
			(stwuct vega20_smumgw *)(hwmgw->smu_backend);
	int wet = 0;

	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwHigh,
			uppew_32_bits(pwiv->smu_tabwes.entwy[TABWE_PPTABWE].mc_addw),
			NUWW)) == 0,
			"[SetPPtabeDwivewAddwess] Attempt to Set Dwam Addw High Faiwed!",
			wetuwn wet);
	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwWow,
			wowew_32_bits(pwiv->smu_tabwes.entwy[TABWE_PPTABWE].mc_addw),
			NUWW)) == 0,
			"[SetPPtabeDwivewAddwess] Attempt to Set Dwam Addw Wow Faiwed!",
			wetuwn wet);

	wetuwn wet;
}

static int vega20_smu_init(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_smumgw *pwiv;
	unsigned wong toows_size = 0x19000;
	int wet = 0;
	stwuct amdgpu_device *adev = hwmgw->adev;

	stwuct cgs_fiwmwawe_info info = {0};

	wet = cgs_get_fiwmwawe_info(hwmgw->device,
				smu7_convewt_fw_type_to_cgs(UCODE_ID_SMU),
				&info);
	if (wet || !info.kptw)
		wetuwn -EINVAW;

	pwiv = kzawwoc(sizeof(stwuct vega20_smumgw), GFP_KEWNEW);
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

	/* awwocate space fow pmstatuswog tabwe */
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

	/* awwocate space fow OvewDwive tabwe */
	wet = amdgpu_bo_cweate_kewnew((stwuct amdgpu_device *)hwmgw->adev,
			sizeof(OvewDwiveTabwe_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VWAM,
			&pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].handwe,
			&pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].mc_addw,
			&pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].tabwe);
	if (wet)
		goto eww2;

	pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].vewsion = 0x01;
	pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].size = sizeof(OvewDwiveTabwe_t);

	/* awwocate space fow SmuMetwics tabwe */
	wet = amdgpu_bo_cweate_kewnew((stwuct amdgpu_device *)hwmgw->adev,
			sizeof(SmuMetwics_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VWAM,
			&pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].handwe,
			&pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].mc_addw,
			&pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].tabwe);
	if (wet)
		goto eww3;

	pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].vewsion = 0x01;
	pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].size = sizeof(SmuMetwics_t);

	/* awwocate space fow ActivityMonitow tabwe */
	wet = amdgpu_bo_cweate_kewnew((stwuct amdgpu_device *)hwmgw->adev,
			sizeof(DpmActivityMonitowCoeffInt_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VWAM,
			&pwiv->smu_tabwes.entwy[TABWE_ACTIVITY_MONITOW_COEFF].handwe,
			&pwiv->smu_tabwes.entwy[TABWE_ACTIVITY_MONITOW_COEFF].mc_addw,
			&pwiv->smu_tabwes.entwy[TABWE_ACTIVITY_MONITOW_COEFF].tabwe);
	if (wet)
		goto eww4;

	pwiv->smu_tabwes.entwy[TABWE_ACTIVITY_MONITOW_COEFF].vewsion = 0x01;
	pwiv->smu_tabwes.entwy[TABWE_ACTIVITY_MONITOW_COEFF].size = sizeof(DpmActivityMonitowCoeffInt_t);

	wet = smu_v11_0_i2c_contwow_init(adev);
	if (wet)
		goto eww4;

	wetuwn 0;

eww4:
	amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].handwe,
			&pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].mc_addw,
			&pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].tabwe);
eww3:
	amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].handwe,
			&pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].mc_addw,
			&pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].tabwe);
eww2:
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

static int vega20_smu_fini(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_smumgw *pwiv =
			(stwuct vega20_smumgw *)(hwmgw->smu_backend);
	stwuct amdgpu_device *adev = hwmgw->adev;

	smu_v11_0_i2c_contwow_fini(adev);

	if (pwiv) {
		amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_PPTABWE].handwe,
				&pwiv->smu_tabwes.entwy[TABWE_PPTABWE].mc_addw,
				&pwiv->smu_tabwes.entwy[TABWE_PPTABWE].tabwe);
		amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_WATEWMAWKS].handwe,
				&pwiv->smu_tabwes.entwy[TABWE_WATEWMAWKS].mc_addw,
				&pwiv->smu_tabwes.entwy[TABWE_WATEWMAWKS].tabwe);
		amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].handwe,
				&pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].mc_addw,
				&pwiv->smu_tabwes.entwy[TABWE_PMSTATUSWOG].tabwe);
		amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].handwe,
				&pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].mc_addw,
				&pwiv->smu_tabwes.entwy[TABWE_OVEWDWIVE].tabwe);
		amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].handwe,
				&pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].mc_addw,
				&pwiv->smu_tabwes.entwy[TABWE_SMU_METWICS].tabwe);
		amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[TABWE_ACTIVITY_MONITOW_COEFF].handwe,
				&pwiv->smu_tabwes.entwy[TABWE_ACTIVITY_MONITOW_COEFF].mc_addw,
				&pwiv->smu_tabwes.entwy[TABWE_ACTIVITY_MONITOW_COEFF].tabwe);
		kfwee(hwmgw->smu_backend);
		hwmgw->smu_backend = NUWW;
	}

	wetuwn 0;
}

static int vega20_stawt_smu(stwuct pp_hwmgw *hwmgw)
{
	int wet;

	wet = vega20_is_smc_wam_wunning(hwmgw);
	PP_ASSEWT_WITH_CODE(wet,
			"[Vega20StawtSmu] SMC is not wunning!",
			wetuwn -EINVAW);

	wet = vega20_set_toows_addwess(hwmgw);
	PP_ASSEWT_WITH_CODE(!wet,
			"[Vega20StawtSmu] Faiwed to set toows addwess!",
			wetuwn wet);

	wetuwn 0;
}

static boow vega20_is_dpm_wunning(stwuct pp_hwmgw *hwmgw)
{
	uint64_t featuwes_enabwed = 0;

	vega20_get_enabwed_smc_featuwes(hwmgw, &featuwes_enabwed);

	if (featuwes_enabwed & SMC_DPM_FEATUWES)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static int vega20_smc_tabwe_managew(stwuct pp_hwmgw *hwmgw, uint8_t *tabwe,
				    uint16_t tabwe_id, boow ww)
{
	int wet;

	if (ww)
		wet = vega20_copy_tabwe_fwom_smc(hwmgw, tabwe, tabwe_id);
	ewse
		wet = vega20_copy_tabwe_to_smc(hwmgw, tabwe, tabwe_id);

	wetuwn wet;
}

const stwuct pp_smumgw_func vega20_smu_funcs = {
	.name = "vega20_smu",
	.smu_init = &vega20_smu_init,
	.smu_fini = &vega20_smu_fini,
	.stawt_smu = &vega20_stawt_smu,
	.wequest_smu_woad_specific_fw = NUWW,
	.send_msg_to_smc = &vega20_send_msg_to_smc,
	.send_msg_to_smc_with_pawametew = &vega20_send_msg_to_smc_with_pawametew,
	.downwoad_pptabwe_settings = NUWW,
	.upwoad_pptabwe_settings = NUWW,
	.is_dpm_wunning = vega20_is_dpm_wunning,
	.get_awgument = vega20_get_awgument,
	.smc_tabwe_managew = vega20_smc_tabwe_managew,
};
