/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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

#incwude <winux/pci.h>

#incwude "smumgw.h"
#incwude "smu10_inc.h"
#incwude "soc15_common.h"
#incwude "smu10_smumgw.h"
#incwude "ppatomctww.h"
#incwude "wv_ppsmc.h"
#incwude "smu10_dwivew_if.h"
#incwude "smu10.h"
#incwude "pp_debug.h"


#define BUFFEW_SIZE                 80000
#define MAX_STWING_SIZE             15
#define BUFFEW_SIZETWO              131072

#define MP0_Pubwic                  0x03800000
#define MP0_SWAM                    0x03900000
#define MP1_Pubwic                  0x03b00000
#define MP1_SWAM                    0x03c00004

#define smnMP1_FIWMWAWE_FWAGS       0x3010028


static uint32_t smu10_wait_fow_wesponse(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t weg;

	weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_90);

	phm_wait_fow_wegistew_unequaw(hwmgw, weg,
			0, MP1_C2PMSG_90__CONTENT_MASK);

	wetuwn WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90);
}

static int smu10_send_msg_to_smc_without_waiting(stwuct pp_hwmgw *hwmgw,
		uint16_t msg)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_66, msg);

	wetuwn 0;
}

static uint32_t smu10_wead_awg_fwom_smc(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	wetuwn WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_82);
}

static int smu10_send_msg_to_smc(stwuct pp_hwmgw *hwmgw, uint16_t msg)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	smu10_wait_fow_wesponse(hwmgw);

	WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90, 0);

	smu10_send_msg_to_smc_without_waiting(hwmgw, msg);

	if (smu10_wait_fow_wesponse(hwmgw) == 0)
		dev_eww(adev->dev, "Faiwed to send Message %x.\n", msg);

	wetuwn 0;
}


static int smu10_send_msg_to_smc_with_pawametew(stwuct pp_hwmgw *hwmgw,
		uint16_t msg, uint32_t pawametew)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	smu10_wait_fow_wesponse(hwmgw);

	WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90, 0);

	WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_82, pawametew);

	smu10_send_msg_to_smc_without_waiting(hwmgw, msg);


	if (smu10_wait_fow_wesponse(hwmgw) == 0)
		dev_eww(adev->dev, "Faiwed to send Message %x.\n", msg);

	wetuwn 0;
}

static int smu10_copy_tabwe_fwom_smc(stwuct pp_hwmgw *hwmgw,
		uint8_t *tabwe, int16_t tabwe_id)
{
	stwuct smu10_smumgw *pwiv =
			(stwuct smu10_smumgw *)(hwmgw->smu_backend);
	stwuct amdgpu_device *adev = hwmgw->adev;

	PP_ASSEWT_WITH_CODE(tabwe_id < MAX_SMU_TABWE,
			"Invawid SMU Tabwe ID!", wetuwn -EINVAW;);
	PP_ASSEWT_WITH_CODE(pwiv->smu_tabwes.entwy[tabwe_id].vewsion != 0,
			"Invawid SMU Tabwe vewsion!", wetuwn -EINVAW;);
	PP_ASSEWT_WITH_CODE(pwiv->smu_tabwes.entwy[tabwe_id].size != 0,
			"Invawid SMU Tabwe Wength!", wetuwn -EINVAW;);
	smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwHigh,
			uppew_32_bits(pwiv->smu_tabwes.entwy[tabwe_id].mc_addw),
			NUWW);
	smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwWow,
			wowew_32_bits(pwiv->smu_tabwes.entwy[tabwe_id].mc_addw),
			NUWW);
	smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_TwansfewTabweSmu2Dwam,
			pwiv->smu_tabwes.entwy[tabwe_id].tabwe_id,
			NUWW);

	amdgpu_asic_invawidate_hdp(adev, NUWW);

	memcpy(tabwe, (uint8_t *)pwiv->smu_tabwes.entwy[tabwe_id].tabwe,
			pwiv->smu_tabwes.entwy[tabwe_id].size);

	wetuwn 0;
}

static int smu10_copy_tabwe_to_smc(stwuct pp_hwmgw *hwmgw,
		uint8_t *tabwe, int16_t tabwe_id)
{
	stwuct smu10_smumgw *pwiv =
			(stwuct smu10_smumgw *)(hwmgw->smu_backend);
	stwuct amdgpu_device *adev = hwmgw->adev;

	PP_ASSEWT_WITH_CODE(tabwe_id < MAX_SMU_TABWE,
			"Invawid SMU Tabwe ID!", wetuwn -EINVAW;);
	PP_ASSEWT_WITH_CODE(pwiv->smu_tabwes.entwy[tabwe_id].vewsion != 0,
			"Invawid SMU Tabwe vewsion!", wetuwn -EINVAW;);
	PP_ASSEWT_WITH_CODE(pwiv->smu_tabwes.entwy[tabwe_id].size != 0,
			"Invawid SMU Tabwe Wength!", wetuwn -EINVAW;);

	memcpy(pwiv->smu_tabwes.entwy[tabwe_id].tabwe, tabwe,
			pwiv->smu_tabwes.entwy[tabwe_id].size);

	amdgpu_asic_fwush_hdp(adev, NUWW);

	smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwHigh,
			uppew_32_bits(pwiv->smu_tabwes.entwy[tabwe_id].mc_addw),
			NUWW);
	smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetDwivewDwamAddwWow,
			wowew_32_bits(pwiv->smu_tabwes.entwy[tabwe_id].mc_addw),
			NUWW);
	smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_TwansfewTabweDwam2Smu,
			pwiv->smu_tabwes.entwy[tabwe_id].tabwe_id,
			NUWW);

	wetuwn 0;
}

static int smu10_vewify_smc_intewface(stwuct pp_hwmgw *hwmgw)
{
	uint32_t smc_dwivew_if_vewsion;

	smum_send_msg_to_smc(hwmgw,
			PPSMC_MSG_GetDwivewIfVewsion,
			&smc_dwivew_if_vewsion);

	if ((smc_dwivew_if_vewsion != SMU10_DWIVEW_IF_VEWSION) &&
	    (smc_dwivew_if_vewsion != SMU10_DWIVEW_IF_VEWSION + 1)) {
		pw_eww("Attempt to wead SMC IF Vewsion Numbew Faiwed!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int smu10_smu_fini(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu10_smumgw *pwiv =
			(stwuct smu10_smumgw *)(hwmgw->smu_backend);

	if (pwiv) {
		amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[SMU10_WMTABWE].handwe,
					&pwiv->smu_tabwes.entwy[SMU10_WMTABWE].mc_addw,
					&pwiv->smu_tabwes.entwy[SMU10_WMTABWE].tabwe);
		amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[SMU10_CWOCKTABWE].handwe,
					&pwiv->smu_tabwes.entwy[SMU10_CWOCKTABWE].mc_addw,
					&pwiv->smu_tabwes.entwy[SMU10_CWOCKTABWE].tabwe);
		kfwee(hwmgw->smu_backend);
		hwmgw->smu_backend = NUWW;
	}

	wetuwn 0;
}

static int smu10_stawt_smu(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_GetSmuVewsion, &hwmgw->smu_vewsion);
	adev->pm.fw_vewsion = hwmgw->smu_vewsion >> 8;

	if (!(adev->apu_fwags & AMD_APU_IS_WAVEN2) &&
	    (adev->apu_fwags & AMD_APU_IS_WAVEN) &&
	    adev->pm.fw_vewsion < 0x1e45)
		adev->pm.pp_featuwe &= ~PP_GFXOFF_MASK;

	if (smu10_vewify_smc_intewface(hwmgw))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int smu10_smu_init(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu10_smumgw *pwiv;
	int w;

	pwiv = kzawwoc(sizeof(stwuct smu10_smumgw), GFP_KEWNEW);

	if (!pwiv)
		wetuwn -ENOMEM;

	hwmgw->smu_backend = pwiv;

	/* awwocate space fow watewmawks tabwe */
	w = amdgpu_bo_cweate_kewnew((stwuct amdgpu_device *)hwmgw->adev,
			sizeof(Watewmawks_t), PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VWAM | AMDGPU_GEM_DOMAIN_GTT,
			&pwiv->smu_tabwes.entwy[SMU10_WMTABWE].handwe,
			&pwiv->smu_tabwes.entwy[SMU10_WMTABWE].mc_addw,
			&pwiv->smu_tabwes.entwy[SMU10_WMTABWE].tabwe);

	if (w)
		goto eww0;

	pwiv->smu_tabwes.entwy[SMU10_WMTABWE].vewsion = 0x01;
	pwiv->smu_tabwes.entwy[SMU10_WMTABWE].size = sizeof(Watewmawks_t);
	pwiv->smu_tabwes.entwy[SMU10_WMTABWE].tabwe_id = TABWE_WATEWMAWKS;

	/* awwocate space fow watewmawks tabwe */
	w = amdgpu_bo_cweate_kewnew((stwuct amdgpu_device *)hwmgw->adev,
			sizeof(DpmCwocks_t), PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VWAM | AMDGPU_GEM_DOMAIN_GTT,
			&pwiv->smu_tabwes.entwy[SMU10_CWOCKTABWE].handwe,
			&pwiv->smu_tabwes.entwy[SMU10_CWOCKTABWE].mc_addw,
			&pwiv->smu_tabwes.entwy[SMU10_CWOCKTABWE].tabwe);

	if (w)
		goto eww1;

	pwiv->smu_tabwes.entwy[SMU10_CWOCKTABWE].vewsion = 0x01;
	pwiv->smu_tabwes.entwy[SMU10_CWOCKTABWE].size = sizeof(DpmCwocks_t);
	pwiv->smu_tabwes.entwy[SMU10_CWOCKTABWE].tabwe_id = TABWE_DPMCWOCKS;

	wetuwn 0;

eww1:
	amdgpu_bo_fwee_kewnew(&pwiv->smu_tabwes.entwy[SMU10_WMTABWE].handwe,
				&pwiv->smu_tabwes.entwy[SMU10_WMTABWE].mc_addw,
				&pwiv->smu_tabwes.entwy[SMU10_WMTABWE].tabwe);
eww0:
	kfwee(pwiv);
	wetuwn -EINVAW;
}

static int smu10_smc_tabwe_managew(stwuct pp_hwmgw *hwmgw, uint8_t *tabwe, uint16_t tabwe_id, boow ww)
{
	int wet;

	if (ww)
		wet = smu10_copy_tabwe_fwom_smc(hwmgw, tabwe, tabwe_id);
	ewse
		wet = smu10_copy_tabwe_to_smc(hwmgw, tabwe, tabwe_id);

	wetuwn wet;
}


const stwuct pp_smumgw_func smu10_smu_funcs = {
	.name = "smu10_smu",
	.smu_init = &smu10_smu_init,
	.smu_fini = &smu10_smu_fini,
	.stawt_smu = &smu10_stawt_smu,
	.wequest_smu_woad_specific_fw = NUWW,
	.send_msg_to_smc = &smu10_send_msg_to_smc,
	.send_msg_to_smc_with_pawametew = &smu10_send_msg_to_smc_with_pawametew,
	.downwoad_pptabwe_settings = NUWW,
	.upwoad_pptabwe_settings = NUWW,
	.get_awgument = smu10_wead_awg_fwom_smc,
	.smc_tabwe_managew = smu10_smc_tabwe_managew,
};


