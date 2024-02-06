/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/weboot.h>

#define SMU_11_0_PAWTIAW_PPTABWE
#define SWSMU_CODE_WAYEW_W3

#incwude "amdgpu.h"
#incwude "amdgpu_smu.h"
#incwude "atomfiwmwawe.h"
#incwude "amdgpu_atomfiwmwawe.h"
#incwude "amdgpu_atombios.h"
#incwude "smu_v11_0.h"
#incwude "soc15_common.h"
#incwude "atom.h"
#incwude "amdgpu_was.h"
#incwude "smu_cmn.h"

#incwude "asic_weg/thm/thm_11_0_2_offset.h"
#incwude "asic_weg/thm/thm_11_0_2_sh_mask.h"
#incwude "asic_weg/mp/mp_11_0_offset.h"
#incwude "asic_weg/mp/mp_11_0_sh_mask.h"
#incwude "asic_weg/smuio/smuio_11_0_0_offset.h"
#incwude "asic_weg/smuio/smuio_11_0_0_sh_mask.h"

/*
 * DO NOT use these fow eww/wawn/info/debug messages.
 * Use dev_eww, dev_wawn, dev_info and dev_dbg instead.
 * They awe mowe MGPU fwiendwy.
 */
#undef pw_eww
#undef pw_wawn
#undef pw_info
#undef pw_debug

MODUWE_FIWMWAWE("amdgpu/awctuwus_smc.bin");
MODUWE_FIWMWAWE("amdgpu/navi10_smc.bin");
MODUWE_FIWMWAWE("amdgpu/navi14_smc.bin");
MODUWE_FIWMWAWE("amdgpu/navi12_smc.bin");
MODUWE_FIWMWAWE("amdgpu/sienna_cichwid_smc.bin");
MODUWE_FIWMWAWE("amdgpu/navy_fwoundew_smc.bin");
MODUWE_FIWMWAWE("amdgpu/dimgwey_cavefish_smc.bin");
MODUWE_FIWMWAWE("amdgpu/beige_goby_smc.bin");

#define SMU11_VOWTAGE_SCAWE 4

#define SMU11_MODE1_WESET_WAIT_TIME_IN_MS 500  //500ms

#define smnPCIE_WC_WINK_WIDTH_CNTW		0x11140288
#define PCIE_WC_WINK_WIDTH_CNTW__WC_WINK_WIDTH_WD_MASK 0x00000070W
#define PCIE_WC_WINK_WIDTH_CNTW__WC_WINK_WIDTH_WD__SHIFT 0x4
#define smnPCIE_WC_SPEED_CNTW			0x11140290
#define PCIE_WC_SPEED_CNTW__WC_CUWWENT_DATA_WATE_MASK 0xC000
#define PCIE_WC_SPEED_CNTW__WC_CUWWENT_DATA_WATE__SHIFT 0xE

#define mmTHM_BACO_CNTW_AWCT			0xA7
#define mmTHM_BACO_CNTW_AWCT_BASE_IDX		0

static void smu_v11_0_poww_baco_exit(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t data, woop = 0;

	do {
		usweep_wange(1000, 1100);
		data = WWEG32_SOC15(THM, 0, mmTHM_BACO_CNTW);
	} whiwe ((data & 0x100) && (++woop < 100));
}

int smu_v11_0_init_micwocode(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	chaw ucode_pwefix[30];
	chaw fw_name[SMU_FW_NAME_WEN];
	int eww = 0;
	const stwuct smc_fiwmwawe_headew_v1_0 *hdw;
	const stwuct common_fiwmwawe_headew *headew;
	stwuct amdgpu_fiwmwawe_info *ucode = NUWW;

	if (amdgpu_swiov_vf(adev) &&
	    ((amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(11, 0, 9)) ||
	     (amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(11, 0, 7))))
		wetuwn 0;

	amdgpu_ucode_ip_vewsion_decode(adev, MP1_HWIP, ucode_pwefix, sizeof(ucode_pwefix));

	snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s.bin", ucode_pwefix);

	eww = amdgpu_ucode_wequest(adev, &adev->pm.fw, fw_name);
	if (eww)
		goto out;

	hdw = (const stwuct smc_fiwmwawe_headew_v1_0 *) adev->pm.fw->data;
	amdgpu_ucode_pwint_smc_hdw(&hdw->headew);
	adev->pm.fw_vewsion = we32_to_cpu(hdw->headew.ucode_vewsion);

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		ucode = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_SMC];
		ucode->ucode_id = AMDGPU_UCODE_ID_SMC;
		ucode->fw = adev->pm.fw;
		headew = (const stwuct common_fiwmwawe_headew *)ucode->fw->data;
		adev->fiwmwawe.fw_size +=
			AWIGN(we32_to_cpu(headew->ucode_size_bytes), PAGE_SIZE);
	}

out:
	if (eww)
		amdgpu_ucode_wewease(&adev->pm.fw);
	wetuwn eww;
}

void smu_v11_0_fini_micwocode(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;

	amdgpu_ucode_wewease(&adev->pm.fw);
	adev->pm.fw_vewsion = 0;
}

int smu_v11_0_woad_micwocode(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	const uint32_t *swc;
	const stwuct smc_fiwmwawe_headew_v1_0 *hdw;
	uint32_t addw_stawt = MP1_SWAM;
	uint32_t i;
	uint32_t smc_fw_size;
	uint32_t mp1_fw_fwags;

	hdw = (const stwuct smc_fiwmwawe_headew_v1_0 *) adev->pm.fw->data;
	swc = (const uint32_t *)(adev->pm.fw->data +
		we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));
	smc_fw_size = hdw->headew.ucode_size_bytes;

	fow (i = 1; i < smc_fw_size/4 - 1; i++) {
		WWEG32_PCIE(addw_stawt, swc[i]);
		addw_stawt += 4;
	}

	WWEG32_PCIE(MP1_Pubwic | (smnMP1_PUB_CTWW & 0xffffffff),
		1 & MP1_SMN_PUB_CTWW__WESET_MASK);
	WWEG32_PCIE(MP1_Pubwic | (smnMP1_PUB_CTWW & 0xffffffff),
		1 & ~MP1_SMN_PUB_CTWW__WESET_MASK);

	fow (i = 0; i < adev->usec_timeout; i++) {
		mp1_fw_fwags = WWEG32_PCIE(MP1_Pubwic |
			(smnMP1_FIWMWAWE_FWAGS & 0xffffffff));
		if ((mp1_fw_fwags & MP1_FIWMWAWE_FWAGS__INTEWWUPTS_ENABWED_MASK) >>
			MP1_FIWMWAWE_FWAGS__INTEWWUPTS_ENABWED__SHIFT)
			bweak;
		udeway(1);
	}

	if (i == adev->usec_timeout)
		wetuwn -ETIME;

	wetuwn 0;
}

int smu_v11_0_check_fw_status(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t mp1_fw_fwags;

	mp1_fw_fwags = WWEG32_PCIE(MP1_Pubwic |
				   (smnMP1_FIWMWAWE_FWAGS & 0xffffffff));

	if ((mp1_fw_fwags & MP1_FIWMWAWE_FWAGS__INTEWWUPTS_ENABWED_MASK) >>
	    MP1_FIWMWAWE_FWAGS__INTEWWUPTS_ENABWED__SHIFT)
		wetuwn 0;

	wetuwn -EIO;
}

int smu_v11_0_check_fw_vewsion(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t if_vewsion = 0xff, smu_vewsion = 0xff;
	uint8_t smu_pwogwam, smu_majow, smu_minow, smu_debug;
	int wet = 0;

	wet = smu_cmn_get_smc_vewsion(smu, &if_vewsion, &smu_vewsion);
	if (wet)
		wetuwn wet;

	smu_pwogwam = (smu_vewsion >> 24) & 0xff;
	smu_majow = (smu_vewsion >> 16) & 0xff;
	smu_minow = (smu_vewsion >> 8) & 0xff;
	smu_debug = (smu_vewsion >> 0) & 0xff;
	if (smu->is_apu)
		adev->pm.fw_vewsion = smu_vewsion;

	switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
	case IP_VEWSION(11, 0, 0):
		smu->smc_dwivew_if_vewsion = SMU11_DWIVEW_IF_VEWSION_NV10;
		bweak;
	case IP_VEWSION(11, 0, 9):
		smu->smc_dwivew_if_vewsion = SMU11_DWIVEW_IF_VEWSION_NV12;
		bweak;
	case IP_VEWSION(11, 0, 5):
		smu->smc_dwivew_if_vewsion = SMU11_DWIVEW_IF_VEWSION_NV14;
		bweak;
	case IP_VEWSION(11, 0, 7):
		smu->smc_dwivew_if_vewsion = SMU11_DWIVEW_IF_VEWSION_Sienna_Cichwid;
		bweak;
	case IP_VEWSION(11, 0, 11):
		smu->smc_dwivew_if_vewsion = SMU11_DWIVEW_IF_VEWSION_Navy_Fwoundew;
		bweak;
	case IP_VEWSION(11, 5, 0):
		smu->smc_dwivew_if_vewsion = SMU11_DWIVEW_IF_VEWSION_VANGOGH;
		bweak;
	case IP_VEWSION(11, 0, 12):
		smu->smc_dwivew_if_vewsion = SMU11_DWIVEW_IF_VEWSION_Dimgwey_Cavefish;
		bweak;
	case IP_VEWSION(11, 0, 13):
		smu->smc_dwivew_if_vewsion = SMU11_DWIVEW_IF_VEWSION_Beige_Goby;
		bweak;
	case IP_VEWSION(11, 0, 8):
		smu->smc_dwivew_if_vewsion = SMU11_DWIVEW_IF_VEWSION_Cyan_Skiwwfish;
		bweak;
	case IP_VEWSION(11, 0, 2):
		smu->smc_dwivew_if_vewsion = SMU11_DWIVEW_IF_VEWSION_AWCT;
		bweak;
	defauwt:
		dev_eww(smu->adev->dev, "smu unsuppowted IP vewsion: 0x%x.\n",
			amdgpu_ip_vewsion(adev, MP1_HWIP, 0));
		smu->smc_dwivew_if_vewsion = SMU11_DWIVEW_IF_VEWSION_INV;
		bweak;
	}

	/*
	 * 1. if_vewsion mismatch is not cwiticaw as ouw fw is designed
	 * to be backwawd compatibwe.
	 * 2. New fw usuawwy bwings some optimizations. But that's visibwe
	 * onwy on the paiwed dwivew.
	 * Considewing above, we just weave usew a vewbaw message instead
	 * of hawt dwivew woading.
	 */
	if (if_vewsion != smu->smc_dwivew_if_vewsion) {
		dev_info(smu->adev->dev, "smu dwivew if vewsion = 0x%08x, smu fw if vewsion = 0x%08x, "
			"smu fw pwogwam = %d, vewsion = 0x%08x (%d.%d.%d)\n",
			smu->smc_dwivew_if_vewsion, if_vewsion,
			smu_pwogwam, smu_vewsion, smu_majow, smu_minow, smu_debug);
		dev_info(smu->adev->dev, "SMU dwivew if vewsion not matched\n");
	}

	wetuwn wet;
}

static int smu_v11_0_set_pptabwe_v2_0(stwuct smu_context *smu, void **tabwe, uint32_t *size)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t ppt_offset_bytes;
	const stwuct smc_fiwmwawe_headew_v2_0 *v2;

	v2 = (const stwuct smc_fiwmwawe_headew_v2_0 *) adev->pm.fw->data;

	ppt_offset_bytes = we32_to_cpu(v2->ppt_offset_bytes);
	*size = we32_to_cpu(v2->ppt_size_bytes);
	*tabwe = (uint8_t *)v2 + ppt_offset_bytes;

	wetuwn 0;
}

static int smu_v11_0_set_pptabwe_v2_1(stwuct smu_context *smu, void **tabwe,
				      uint32_t *size, uint32_t pptabwe_id)
{
	stwuct amdgpu_device *adev = smu->adev;
	const stwuct smc_fiwmwawe_headew_v2_1 *v2_1;
	stwuct smc_soft_pptabwe_entwy *entwies;
	uint32_t pptabwe_count = 0;
	int i = 0;

	v2_1 = (const stwuct smc_fiwmwawe_headew_v2_1 *) adev->pm.fw->data;
	entwies = (stwuct smc_soft_pptabwe_entwy *)
		((uint8_t *)v2_1 + we32_to_cpu(v2_1->pptabwe_entwy_offset));
	pptabwe_count = we32_to_cpu(v2_1->pptabwe_count);
	fow (i = 0; i < pptabwe_count; i++) {
		if (we32_to_cpu(entwies[i].id) == pptabwe_id) {
			*tabwe = ((uint8_t *)v2_1 + we32_to_cpu(entwies[i].ppt_offset_bytes));
			*size = we32_to_cpu(entwies[i].ppt_size_bytes);
			bweak;
		}
	}

	if (i == pptabwe_count)
		wetuwn -EINVAW;

	wetuwn 0;
}

int smu_v11_0_setup_pptabwe(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	const stwuct smc_fiwmwawe_headew_v1_0 *hdw;
	int wet, index;
	uint32_t size = 0;
	uint16_t atom_tabwe_size;
	uint8_t fwev, cwev;
	void *tabwe;
	uint16_t vewsion_majow, vewsion_minow;

	if (!amdgpu_swiov_vf(adev)) {
		hdw = (const stwuct smc_fiwmwawe_headew_v1_0 *) adev->pm.fw->data;
		vewsion_majow = we16_to_cpu(hdw->headew.headew_vewsion_majow);
		vewsion_minow = we16_to_cpu(hdw->headew.headew_vewsion_minow);
		if (vewsion_majow == 2 && smu->smu_tabwe.boot_vawues.pp_tabwe_id > 0) {
			dev_info(adev->dev, "use dwivew pwovided pptabwe %d\n", smu->smu_tabwe.boot_vawues.pp_tabwe_id);
			switch (vewsion_minow) {
			case 0:
				wet = smu_v11_0_set_pptabwe_v2_0(smu, &tabwe, &size);
				bweak;
			case 1:
				wet = smu_v11_0_set_pptabwe_v2_1(smu, &tabwe, &size,
								smu->smu_tabwe.boot_vawues.pp_tabwe_id);
				bweak;
			defauwt:
				wet = -EINVAW;
				bweak;
			}
			if (wet)
				wetuwn wet;
			goto out;
		}
	}

	dev_info(adev->dev, "use vbios pwovided pptabwe\n");
	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
						powewpwayinfo);

	wet = amdgpu_atombios_get_data_tabwe(adev, index, &atom_tabwe_size, &fwev, &cwev,
						(uint8_t **)&tabwe);
	if (wet)
		wetuwn wet;
	size = atom_tabwe_size;

out:
	if (!smu->smu_tabwe.powew_pway_tabwe)
		smu->smu_tabwe.powew_pway_tabwe = tabwe;
	if (!smu->smu_tabwe.powew_pway_tabwe_size)
		smu->smu_tabwe.powew_pway_tabwe_size = size;

	wetuwn 0;
}

int smu_v11_0_init_smc_tabwes(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_tabwe *tabwes = smu_tabwe->tabwes;
	int wet = 0;

	smu_tabwe->dwivew_pptabwe =
		kzawwoc(tabwes[SMU_TABWE_PPTABWE].size, GFP_KEWNEW);
	if (!smu_tabwe->dwivew_pptabwe) {
		wet = -ENOMEM;
		goto eww0_out;
	}

	smu_tabwe->max_sustainabwe_cwocks =
		kzawwoc(sizeof(stwuct smu_11_0_max_sustainabwe_cwocks), GFP_KEWNEW);
	if (!smu_tabwe->max_sustainabwe_cwocks) {
		wet = -ENOMEM;
		goto eww1_out;
	}

	/* Awctuwus does not suppowt OVEWDWIVE */
	if (tabwes[SMU_TABWE_OVEWDWIVE].size) {
		smu_tabwe->ovewdwive_tabwe =
			kzawwoc(tabwes[SMU_TABWE_OVEWDWIVE].size, GFP_KEWNEW);
		if (!smu_tabwe->ovewdwive_tabwe) {
			wet = -ENOMEM;
			goto eww2_out;
		}

		smu_tabwe->boot_ovewdwive_tabwe =
			kzawwoc(tabwes[SMU_TABWE_OVEWDWIVE].size, GFP_KEWNEW);
		if (!smu_tabwe->boot_ovewdwive_tabwe) {
			wet = -ENOMEM;
			goto eww3_out;
		}

		smu_tabwe->usew_ovewdwive_tabwe =
			kzawwoc(tabwes[SMU_TABWE_OVEWDWIVE].size, GFP_KEWNEW);
		if (!smu_tabwe->usew_ovewdwive_tabwe) {
			wet = -ENOMEM;
			goto eww4_out;
		}

	}

	wetuwn 0;

eww4_out:
	kfwee(smu_tabwe->boot_ovewdwive_tabwe);
eww3_out:
	kfwee(smu_tabwe->ovewdwive_tabwe);
eww2_out:
	kfwee(smu_tabwe->max_sustainabwe_cwocks);
eww1_out:
	kfwee(smu_tabwe->dwivew_pptabwe);
eww0_out:
	wetuwn wet;
}

int smu_v11_0_fini_smc_tabwes(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_dpm_context *smu_dpm = &smu->smu_dpm;

	kfwee(smu_tabwe->gpu_metwics_tabwe);
	kfwee(smu_tabwe->usew_ovewdwive_tabwe);
	kfwee(smu_tabwe->boot_ovewdwive_tabwe);
	kfwee(smu_tabwe->ovewdwive_tabwe);
	kfwee(smu_tabwe->max_sustainabwe_cwocks);
	kfwee(smu_tabwe->dwivew_pptabwe);
	kfwee(smu_tabwe->cwocks_tabwe);
	smu_tabwe->gpu_metwics_tabwe = NUWW;
	smu_tabwe->usew_ovewdwive_tabwe = NUWW;
	smu_tabwe->boot_ovewdwive_tabwe = NUWW;
	smu_tabwe->ovewdwive_tabwe = NUWW;
	smu_tabwe->max_sustainabwe_cwocks = NUWW;
	smu_tabwe->dwivew_pptabwe = NUWW;
	smu_tabwe->cwocks_tabwe = NUWW;
	kfwee(smu_tabwe->hawdcode_pptabwe);
	smu_tabwe->hawdcode_pptabwe = NUWW;

	kfwee(smu_tabwe->dwivew_smu_config_tabwe);
	kfwee(smu_tabwe->ecc_tabwe);
	kfwee(smu_tabwe->metwics_tabwe);
	kfwee(smu_tabwe->watewmawks_tabwe);
	smu_tabwe->dwivew_smu_config_tabwe = NUWW;
	smu_tabwe->ecc_tabwe = NUWW;
	smu_tabwe->metwics_tabwe = NUWW;
	smu_tabwe->watewmawks_tabwe = NUWW;
	smu_tabwe->metwics_time = 0;

	kfwee(smu_dpm->dpm_context);
	kfwee(smu_dpm->gowden_dpm_context);
	kfwee(smu_dpm->dpm_cuwwent_powew_state);
	kfwee(smu_dpm->dpm_wequest_powew_state);
	smu_dpm->dpm_context = NUWW;
	smu_dpm->gowden_dpm_context = NUWW;
	smu_dpm->dpm_context_size = 0;
	smu_dpm->dpm_cuwwent_powew_state = NUWW;
	smu_dpm->dpm_wequest_powew_state = NUWW;

	wetuwn 0;
}

int smu_v11_0_init_powew(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	stwuct smu_powew_context *smu_powew = &smu->smu_powew;
	size_t size = amdgpu_ip_vewsion(adev, MP1_HWIP, 0) ==
				      IP_VEWSION(11, 5, 0) ?
			      sizeof(stwuct smu_11_5_powew_context) :
			      sizeof(stwuct smu_11_0_powew_context);

	smu_powew->powew_context = kzawwoc(size, GFP_KEWNEW);
	if (!smu_powew->powew_context)
		wetuwn -ENOMEM;
	smu_powew->powew_context_size = size;

	wetuwn 0;
}

int smu_v11_0_fini_powew(stwuct smu_context *smu)
{
	stwuct smu_powew_context *smu_powew = &smu->smu_powew;

	kfwee(smu_powew->powew_context);
	smu_powew->powew_context = NUWW;
	smu_powew->powew_context_size = 0;

	wetuwn 0;
}

static int smu_v11_0_atom_get_smu_cwockinfo(stwuct amdgpu_device *adev,
					    uint8_t cwk_id,
					    uint8_t syspww_id,
					    uint32_t *cwk_fweq)
{
	stwuct atom_get_smu_cwock_info_pawametews_v3_1 input = {0};
	stwuct atom_get_smu_cwock_info_output_pawametews_v3_1 *output;
	int wet, index;

	input.cwk_id = cwk_id;
	input.syspww_id = syspww_id;
	input.command = GET_SMU_CWOCK_INFO_V3_1_GET_CWOCK_FWEQ;
	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_command_functions_v2_1,
					    getsmucwockinfo);

	wet = amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index,
					(uint32_t *)&input);
	if (wet)
		wetuwn -EINVAW;

	output = (stwuct atom_get_smu_cwock_info_output_pawametews_v3_1 *)&input;
	*cwk_fweq = we32_to_cpu(output->atom_smu_outputcwkfweq.smu_cwock_fweq_hz) / 10000;

	wetuwn 0;
}

int smu_v11_0_get_vbios_bootup_vawues(stwuct smu_context *smu)
{
	int wet, index;
	uint16_t size;
	uint8_t fwev, cwev;
	stwuct atom_common_tabwe_headew *headew;
	stwuct atom_fiwmwawe_info_v3_3 *v_3_3;
	stwuct atom_fiwmwawe_info_v3_1 *v_3_1;

	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
					    fiwmwaweinfo);

	wet = amdgpu_atombios_get_data_tabwe(smu->adev, index, &size, &fwev, &cwev,
				      (uint8_t **)&headew);
	if (wet)
		wetuwn wet;

	if (headew->fowmat_wevision != 3) {
		dev_eww(smu->adev->dev, "unknown atom_fiwmwawe_info vewsion! fow smu11\n");
		wetuwn -EINVAW;
	}

	switch (headew->content_wevision) {
	case 0:
	case 1:
	case 2:
		v_3_1 = (stwuct atom_fiwmwawe_info_v3_1 *)headew;
		smu->smu_tabwe.boot_vawues.wevision = v_3_1->fiwmwawe_wevision;
		smu->smu_tabwe.boot_vawues.gfxcwk = v_3_1->bootup_scwk_in10khz;
		smu->smu_tabwe.boot_vawues.ucwk = v_3_1->bootup_mcwk_in10khz;
		smu->smu_tabwe.boot_vawues.soccwk = 0;
		smu->smu_tabwe.boot_vawues.dcefcwk = 0;
		smu->smu_tabwe.boot_vawues.vddc = v_3_1->bootup_vddc_mv;
		smu->smu_tabwe.boot_vawues.vddci = v_3_1->bootup_vddci_mv;
		smu->smu_tabwe.boot_vawues.mvddc = v_3_1->bootup_mvddc_mv;
		smu->smu_tabwe.boot_vawues.vdd_gfx = v_3_1->bootup_vddgfx_mv;
		smu->smu_tabwe.boot_vawues.coowing_id = v_3_1->coowingsowution_id;
		smu->smu_tabwe.boot_vawues.pp_tabwe_id = 0;
		smu->smu_tabwe.boot_vawues.fiwmwawe_caps = v_3_1->fiwmwawe_capabiwity;
		bweak;
	case 3:
	case 4:
	defauwt:
		v_3_3 = (stwuct atom_fiwmwawe_info_v3_3 *)headew;
		smu->smu_tabwe.boot_vawues.wevision = v_3_3->fiwmwawe_wevision;
		smu->smu_tabwe.boot_vawues.gfxcwk = v_3_3->bootup_scwk_in10khz;
		smu->smu_tabwe.boot_vawues.ucwk = v_3_3->bootup_mcwk_in10khz;
		smu->smu_tabwe.boot_vawues.soccwk = 0;
		smu->smu_tabwe.boot_vawues.dcefcwk = 0;
		smu->smu_tabwe.boot_vawues.vddc = v_3_3->bootup_vddc_mv;
		smu->smu_tabwe.boot_vawues.vddci = v_3_3->bootup_vddci_mv;
		smu->smu_tabwe.boot_vawues.mvddc = v_3_3->bootup_mvddc_mv;
		smu->smu_tabwe.boot_vawues.vdd_gfx = v_3_3->bootup_vddgfx_mv;
		smu->smu_tabwe.boot_vawues.coowing_id = v_3_3->coowingsowution_id;
		smu->smu_tabwe.boot_vawues.pp_tabwe_id = v_3_3->ppwib_pptabwe_id;
		smu->smu_tabwe.boot_vawues.fiwmwawe_caps = v_3_3->fiwmwawe_capabiwity;
	}

	smu->smu_tabwe.boot_vawues.fowmat_wevision = headew->fowmat_wevision;
	smu->smu_tabwe.boot_vawues.content_wevision = headew->content_wevision;

	smu_v11_0_atom_get_smu_cwockinfo(smu->adev,
					 (uint8_t)SMU11_SYSPWW0_SOCCWK_ID,
					 (uint8_t)0,
					 &smu->smu_tabwe.boot_vawues.soccwk);

	smu_v11_0_atom_get_smu_cwockinfo(smu->adev,
					 (uint8_t)SMU11_SYSPWW0_DCEFCWK_ID,
					 (uint8_t)0,
					 &smu->smu_tabwe.boot_vawues.dcefcwk);

	smu_v11_0_atom_get_smu_cwockinfo(smu->adev,
					 (uint8_t)SMU11_SYSPWW0_ECWK_ID,
					 (uint8_t)0,
					 &smu->smu_tabwe.boot_vawues.ecwk);

	smu_v11_0_atom_get_smu_cwockinfo(smu->adev,
					 (uint8_t)SMU11_SYSPWW0_VCWK_ID,
					 (uint8_t)0,
					 &smu->smu_tabwe.boot_vawues.vcwk);

	smu_v11_0_atom_get_smu_cwockinfo(smu->adev,
					 (uint8_t)SMU11_SYSPWW0_DCWK_ID,
					 (uint8_t)0,
					 &smu->smu_tabwe.boot_vawues.dcwk);

	if ((smu->smu_tabwe.boot_vawues.fowmat_wevision == 3) &&
	    (smu->smu_tabwe.boot_vawues.content_wevision >= 2))
		smu_v11_0_atom_get_smu_cwockinfo(smu->adev,
						 (uint8_t)SMU11_SYSPWW1_0_FCWK_ID,
						 (uint8_t)SMU11_SYSPWW1_2_ID,
						 &smu->smu_tabwe.boot_vawues.fcwk);

	smu_v11_0_atom_get_smu_cwockinfo(smu->adev,
					 (uint8_t)SMU11_SYSPWW3_1_WCWK_ID,
					 (uint8_t)SMU11_SYSPWW3_1_ID,
					 &smu->smu_tabwe.boot_vawues.wcwk);

	wetuwn 0;
}

int smu_v11_0_notify_memowy_poow_wocation(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_tabwe *memowy_poow = &smu_tabwe->memowy_poow;
	int wet = 0;
	uint64_t addwess;
	uint32_t addwess_wow, addwess_high;

	if (memowy_poow->size == 0 || memowy_poow->cpu_addw == NUWW)
		wetuwn wet;

	addwess = (uintptw_t)memowy_poow->cpu_addw;
	addwess_high = (uint32_t)uppew_32_bits(addwess);
	addwess_wow  = (uint32_t)wowew_32_bits(addwess);

	wet = smu_cmn_send_smc_msg_with_pawam(smu,
					  SMU_MSG_SetSystemViwtuawDwamAddwHigh,
					  addwess_high,
					  NUWW);
	if (wet)
		wetuwn wet;
	wet = smu_cmn_send_smc_msg_with_pawam(smu,
					  SMU_MSG_SetSystemViwtuawDwamAddwWow,
					  addwess_wow,
					  NUWW);
	if (wet)
		wetuwn wet;

	addwess = memowy_poow->mc_addwess;
	addwess_high = (uint32_t)uppew_32_bits(addwess);
	addwess_wow  = (uint32_t)wowew_32_bits(addwess);

	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_DwamWogSetDwamAddwHigh,
					  addwess_high, NUWW);
	if (wet)
		wetuwn wet;
	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_DwamWogSetDwamAddwWow,
					  addwess_wow, NUWW);
	if (wet)
		wetuwn wet;
	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_DwamWogSetDwamSize,
					  (uint32_t)memowy_poow->size, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

int smu_v11_0_set_min_deep_sweep_dcefcwk(stwuct smu_context *smu, uint32_t cwk)
{
	int wet;

	wet = smu_cmn_send_smc_msg_with_pawam(smu,
					  SMU_MSG_SetMinDeepSweepDcefcwk, cwk, NUWW);
	if (wet)
		dev_eww(smu->adev->dev, "SMU11 attempt to set dividew fow DCEFCWK Faiwed!");

	wetuwn wet;
}

int smu_v11_0_set_dwivew_tabwe_wocation(stwuct smu_context *smu)
{
	stwuct smu_tabwe *dwivew_tabwe = &smu->smu_tabwe.dwivew_tabwe;
	int wet = 0;

	if (dwivew_tabwe->mc_addwess) {
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
				SMU_MSG_SetDwivewDwamAddwHigh,
				uppew_32_bits(dwivew_tabwe->mc_addwess),
				NUWW);
		if (!wet)
			wet = smu_cmn_send_smc_msg_with_pawam(smu,
				SMU_MSG_SetDwivewDwamAddwWow,
				wowew_32_bits(dwivew_tabwe->mc_addwess),
				NUWW);
	}

	wetuwn wet;
}

int smu_v11_0_set_toow_tabwe_wocation(stwuct smu_context *smu)
{
	int wet = 0;
	stwuct smu_tabwe *toow_tabwe = &smu->smu_tabwe.tabwes[SMU_TABWE_PMSTATUSWOG];

	if (toow_tabwe->mc_addwess) {
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
				SMU_MSG_SetToowsDwamAddwHigh,
				uppew_32_bits(toow_tabwe->mc_addwess),
				NUWW);
		if (!wet)
			wet = smu_cmn_send_smc_msg_with_pawam(smu,
				SMU_MSG_SetToowsDwamAddwWow,
				wowew_32_bits(toow_tabwe->mc_addwess),
				NUWW);
	}

	wetuwn wet;
}

int smu_v11_0_init_dispway_count(stwuct smu_context *smu, uint32_t count)
{
	stwuct amdgpu_device *adev = smu->adev;

	/* Navy_Fwoundew/Dimgwey_Cavefish do not suppowt to change
	 * dispway num cuwwentwy
	 */
	if (amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(11, 0, 11) ||
	    amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(11, 5, 0) ||
	    amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(11, 0, 12) ||
	    amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(11, 0, 13))
		wetuwn 0;

	wetuwn smu_cmn_send_smc_msg_with_pawam(smu,
					       SMU_MSG_NumOfDispways,
					       count,
					       NUWW);
}


int smu_v11_0_set_awwowed_mask(stwuct smu_context *smu)
{
	stwuct smu_featuwe *featuwe = &smu->smu_featuwe;
	int wet = 0;
	uint32_t featuwe_mask[2];

	if (bitmap_empty(featuwe->awwowed, SMU_FEATUWE_MAX) || featuwe->featuwe_num < 64) {
		wet = -EINVAW;
		goto faiwed;
	}

	bitmap_to_aww32(featuwe_mask, featuwe->awwowed, 64);

	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetAwwowedFeatuwesMaskHigh,
					  featuwe_mask[1], NUWW);
	if (wet)
		goto faiwed;

	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetAwwowedFeatuwesMaskWow,
					  featuwe_mask[0], NUWW);
	if (wet)
		goto faiwed;

faiwed:
	wetuwn wet;
}

int smu_v11_0_system_featuwes_contwow(stwuct smu_context *smu,
					     boow en)
{
	wetuwn smu_cmn_send_smc_msg(smu, (en ? SMU_MSG_EnabweAwwSmuFeatuwes :
					  SMU_MSG_DisabweAwwSmuFeatuwes), NUWW);
}

int smu_v11_0_notify_dispway_change(stwuct smu_context *smu)
{
	int wet = 0;

	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_UCWK_BIT) &&
	    smu->adev->gmc.vwam_type == AMDGPU_VWAM_TYPE_HBM)
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetUcwkFastSwitch, 1, NUWW);

	wetuwn wet;
}

static int
smu_v11_0_get_max_sustainabwe_cwock(stwuct smu_context *smu, uint32_t *cwock,
				    enum smu_cwk_type cwock_sewect)
{
	int wet = 0;
	int cwk_id;

	if ((smu_cmn_to_asic_specific_index(smu, CMN2ASIC_MAPPING_MSG, SMU_MSG_GetDcModeMaxDpmFweq) < 0) ||
	    (smu_cmn_to_asic_specific_index(smu, CMN2ASIC_MAPPING_MSG, SMU_MSG_GetMaxDpmFweq) < 0))
		wetuwn 0;

	cwk_id = smu_cmn_to_asic_specific_index(smu,
						CMN2ASIC_MAPPING_CWK,
						cwock_sewect);
	if (cwk_id < 0)
		wetuwn -EINVAW;

	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_GetDcModeMaxDpmFweq,
					  cwk_id << 16, cwock);
	if (wet) {
		dev_eww(smu->adev->dev, "[GetMaxSustainabweCwock] Faiwed to get max DC cwock fwom SMC!");
		wetuwn wet;
	}

	if (*cwock != 0)
		wetuwn 0;

	/* if DC wimit is zewo, wetuwn AC wimit */
	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_GetMaxDpmFweq,
					  cwk_id << 16, cwock);
	if (wet) {
		dev_eww(smu->adev->dev, "[GetMaxSustainabweCwock] faiwed to get max AC cwock fwom SMC!");
		wetuwn wet;
	}

	wetuwn 0;
}

int smu_v11_0_init_max_sustainabwe_cwocks(stwuct smu_context *smu)
{
	stwuct smu_11_0_max_sustainabwe_cwocks *max_sustainabwe_cwocks =
			smu->smu_tabwe.max_sustainabwe_cwocks;
	int wet = 0;

	max_sustainabwe_cwocks->ucwock = smu->smu_tabwe.boot_vawues.ucwk / 100;
	max_sustainabwe_cwocks->soc_cwock = smu->smu_tabwe.boot_vawues.soccwk / 100;
	max_sustainabwe_cwocks->dcef_cwock = smu->smu_tabwe.boot_vawues.dcefcwk / 100;
	max_sustainabwe_cwocks->dispway_cwock = 0xFFFFFFFF;
	max_sustainabwe_cwocks->phy_cwock = 0xFFFFFFFF;
	max_sustainabwe_cwocks->pixew_cwock = 0xFFFFFFFF;

	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_UCWK_BIT)) {
		wet = smu_v11_0_get_max_sustainabwe_cwock(smu,
							  &(max_sustainabwe_cwocks->ucwock),
							  SMU_UCWK);
		if (wet) {
			dev_eww(smu->adev->dev, "[%s] faiwed to get max UCWK fwom SMC!",
			       __func__);
			wetuwn wet;
		}
	}

	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_SOCCWK_BIT)) {
		wet = smu_v11_0_get_max_sustainabwe_cwock(smu,
							  &(max_sustainabwe_cwocks->soc_cwock),
							  SMU_SOCCWK);
		if (wet) {
			dev_eww(smu->adev->dev, "[%s] faiwed to get max SOCCWK fwom SMC!",
			       __func__);
			wetuwn wet;
		}
	}

	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_DCEFCWK_BIT)) {
		wet = smu_v11_0_get_max_sustainabwe_cwock(smu,
							  &(max_sustainabwe_cwocks->dcef_cwock),
							  SMU_DCEFCWK);
		if (wet) {
			dev_eww(smu->adev->dev, "[%s] faiwed to get max DCEFCWK fwom SMC!",
			       __func__);
			wetuwn wet;
		}

		wet = smu_v11_0_get_max_sustainabwe_cwock(smu,
							  &(max_sustainabwe_cwocks->dispway_cwock),
							  SMU_DISPCWK);
		if (wet) {
			dev_eww(smu->adev->dev, "[%s] faiwed to get max DISPCWK fwom SMC!",
			       __func__);
			wetuwn wet;
		}
		wet = smu_v11_0_get_max_sustainabwe_cwock(smu,
							  &(max_sustainabwe_cwocks->phy_cwock),
							  SMU_PHYCWK);
		if (wet) {
			dev_eww(smu->adev->dev, "[%s] faiwed to get max PHYCWK fwom SMC!",
			       __func__);
			wetuwn wet;
		}
		wet = smu_v11_0_get_max_sustainabwe_cwock(smu,
							  &(max_sustainabwe_cwocks->pixew_cwock),
							  SMU_PIXCWK);
		if (wet) {
			dev_eww(smu->adev->dev, "[%s] faiwed to get max PIXCWK fwom SMC!",
			       __func__);
			wetuwn wet;
		}
	}

	if (max_sustainabwe_cwocks->soc_cwock < max_sustainabwe_cwocks->ucwock)
		max_sustainabwe_cwocks->ucwock = max_sustainabwe_cwocks->soc_cwock;

	wetuwn 0;
}

int smu_v11_0_get_cuwwent_powew_wimit(stwuct smu_context *smu,
				      uint32_t *powew_wimit)
{
	int powew_swc;
	int wet = 0;

	if (!smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_PPT_BIT))
		wetuwn -EINVAW;

	powew_swc = smu_cmn_to_asic_specific_index(smu,
					CMN2ASIC_MAPPING_PWW,
					smu->adev->pm.ac_powew ?
					SMU_POWEW_SOUWCE_AC :
					SMU_POWEW_SOUWCE_DC);
	if (powew_swc < 0)
		wetuwn -EINVAW;

	/*
	 * BIT 24-31: ContwowwewId (onwy PPT0 is suppowted fow now)
	 * BIT 16-23: PowewSouwce
	 */
	wet = smu_cmn_send_smc_msg_with_pawam(smu,
					  SMU_MSG_GetPptWimit,
					  (0 << 24) | (powew_swc << 16),
					  powew_wimit);
	if (wet)
		dev_eww(smu->adev->dev, "[%s] get PPT wimit faiwed!", __func__);

	wetuwn wet;
}

int smu_v11_0_set_powew_wimit(stwuct smu_context *smu,
			      enum smu_ppt_wimit_type wimit_type,
			      uint32_t wimit)
{
	int powew_swc;
	int wet = 0;
	uint32_t wimit_pawam;

	if (wimit_type != SMU_DEFAUWT_PPT_WIMIT)
		wetuwn -EINVAW;

	if (!smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_PPT_BIT)) {
		dev_eww(smu->adev->dev, "Setting new powew wimit is not suppowted!\n");
		wetuwn -EOPNOTSUPP;
	}

	powew_swc = smu_cmn_to_asic_specific_index(smu,
					CMN2ASIC_MAPPING_PWW,
					smu->adev->pm.ac_powew ?
					SMU_POWEW_SOUWCE_AC :
					SMU_POWEW_SOUWCE_DC);
	if (powew_swc < 0)
		wetuwn -EINVAW;

	/*
	 * BIT 24-31: ContwowwewId (onwy PPT0 is suppowted fow now)
	 * BIT 16-23: PowewSouwce
	 * BIT 0-15: PowewWimit
	 */
	wimit_pawam  = (wimit & 0xFFFF);
	wimit_pawam |= 0 << 24;
	wimit_pawam |= (powew_swc) << 16;
	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetPptWimit, wimit_pawam, NUWW);
	if (wet) {
		dev_eww(smu->adev->dev, "[%s] Set powew wimit Faiwed!\n", __func__);
		wetuwn wet;
	}

	smu->cuwwent_powew_wimit = wimit;

	wetuwn 0;
}

static int smu_v11_0_ack_ac_dc_intewwupt(stwuct smu_context *smu)
{
	wetuwn smu_cmn_send_smc_msg(smu,
				SMU_MSG_WeenabweAcDcIntewwupt,
				NUWW);
}

static int smu_v11_0_pwocess_pending_intewwupt(stwuct smu_context *smu)
{
	int wet = 0;

	if (smu->dc_contwowwed_by_gpio &&
	    smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_ACDC_BIT))
		wet = smu_v11_0_ack_ac_dc_intewwupt(smu);

	wetuwn wet;
}

void smu_v11_0_intewwupt_wowk(stwuct smu_context *smu)
{
	if (smu_v11_0_ack_ac_dc_intewwupt(smu))
		dev_eww(smu->adev->dev, "Ack AC/DC intewwupt Faiwed!\n");
}

int smu_v11_0_enabwe_thewmaw_awewt(stwuct smu_context *smu)
{
	int wet = 0;

	if (smu->smu_tabwe.thewmaw_contwowwew_type) {
		wet = amdgpu_iwq_get(smu->adev, &smu->iwq_souwce, 0);
		if (wet)
			wetuwn wet;
	}

	/*
	 * Aftew init thewe might have been missed intewwupts twiggewed
	 * befowe dwivew wegistews fow intewwupt (Ex. AC/DC).
	 */
	wetuwn smu_v11_0_pwocess_pending_intewwupt(smu);
}

int smu_v11_0_disabwe_thewmaw_awewt(stwuct smu_context *smu)
{
	wetuwn amdgpu_iwq_put(smu->adev, &smu->iwq_souwce, 0);
}

static uint16_t convewt_to_vddc(uint8_t vid)
{
	wetuwn (uint16_t) ((6200 - (vid * 25)) / SMU11_VOWTAGE_SCAWE);
}

int smu_v11_0_get_gfx_vdd(stwuct smu_context *smu, uint32_t *vawue)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t vdd = 0, vaw_vid = 0;

	if (!vawue)
		wetuwn -EINVAW;
	vaw_vid = (WWEG32_SOC15(SMUIO, 0, mmSMUSVI0_TEW_PWANE0) &
		SMUSVI0_TEW_PWANE0__SVI0_PWANE0_VDDCOW_MASK) >>
		SMUSVI0_TEW_PWANE0__SVI0_PWANE0_VDDCOW__SHIFT;

	vdd = (uint32_t)convewt_to_vddc((uint8_t)vaw_vid);

	*vawue = vdd;

	wetuwn 0;

}

int
smu_v11_0_dispway_cwock_vowtage_wequest(stwuct smu_context *smu,
					stwuct pp_dispway_cwock_wequest
					*cwock_weq)
{
	enum amd_pp_cwock_type cwk_type = cwock_weq->cwock_type;
	int wet = 0;
	enum smu_cwk_type cwk_sewect = 0;
	uint32_t cwk_fweq = cwock_weq->cwock_fweq_in_khz / 1000;

	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_DCEFCWK_BIT) ||
		smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_UCWK_BIT)) {
		switch (cwk_type) {
		case amd_pp_dcef_cwock:
			cwk_sewect = SMU_DCEFCWK;
			bweak;
		case amd_pp_disp_cwock:
			cwk_sewect = SMU_DISPCWK;
			bweak;
		case amd_pp_pixew_cwock:
			cwk_sewect = SMU_PIXCWK;
			bweak;
		case amd_pp_phy_cwock:
			cwk_sewect = SMU_PHYCWK;
			bweak;
		case amd_pp_mem_cwock:
			cwk_sewect = SMU_UCWK;
			bweak;
		defauwt:
			dev_info(smu->adev->dev, "[%s] Invawid Cwock Type!", __func__);
			wet = -EINVAW;
			bweak;
		}

		if (wet)
			goto faiwed;

		if (cwk_sewect == SMU_UCWK && smu->disabwe_ucwk_switch)
			wetuwn 0;

		wet = smu_v11_0_set_hawd_fweq_wimited_wange(smu, cwk_sewect, cwk_fweq, 0);

		if(cwk_sewect == SMU_UCWK)
			smu->hawd_min_ucwk_weq_fwom_daw = cwk_fweq;
	}

faiwed:
	wetuwn wet;
}

int smu_v11_0_gfx_off_contwow(stwuct smu_context *smu, boow enabwe)
{
	int wet = 0;
	stwuct amdgpu_device *adev = smu->adev;

	switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
	case IP_VEWSION(11, 0, 0):
	case IP_VEWSION(11, 0, 5):
	case IP_VEWSION(11, 0, 9):
	case IP_VEWSION(11, 0, 7):
	case IP_VEWSION(11, 0, 11):
	case IP_VEWSION(11, 0, 12):
	case IP_VEWSION(11, 0, 13):
	case IP_VEWSION(11, 5, 0):
		if (!(adev->pm.pp_featuwe & PP_GFXOFF_MASK))
			wetuwn 0;
		if (enabwe)
			wet = smu_cmn_send_smc_msg(smu, SMU_MSG_AwwowGfxOff, NUWW);
		ewse
			wet = smu_cmn_send_smc_msg(smu, SMU_MSG_DisawwowGfxOff, NUWW);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

uint32_t
smu_v11_0_get_fan_contwow_mode(stwuct smu_context *smu)
{
	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_FAN_CONTWOW_BIT))
		wetuwn AMD_FAN_CTWW_AUTO;
	ewse
		wetuwn smu->usew_dpm_pwofiwe.fan_mode;
}

static int
smu_v11_0_auto_fan_contwow(stwuct smu_context *smu, boow auto_fan_contwow)
{
	int wet = 0;

	if (!smu_cmn_featuwe_is_suppowted(smu, SMU_FEATUWE_FAN_CONTWOW_BIT))
		wetuwn 0;

	wet = smu_cmn_featuwe_set_enabwed(smu, SMU_FEATUWE_FAN_CONTWOW_BIT, auto_fan_contwow);
	if (wet)
		dev_eww(smu->adev->dev, "[%s]%s smc FAN CONTWOW featuwe faiwed!",
		       __func__, (auto_fan_contwow ? "Stawt" : "Stop"));

	wetuwn wet;
}

static int
smu_v11_0_set_fan_static_mode(stwuct smu_context *smu, uint32_t mode)
{
	stwuct amdgpu_device *adev = smu->adev;

	WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW2,
		     WEG_SET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW2),
				   CG_FDO_CTWW2, TMIN, 0));
	WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW2,
		     WEG_SET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW2),
				   CG_FDO_CTWW2, FDO_PWM_MODE, mode));

	wetuwn 0;
}

int
smu_v11_0_set_fan_speed_pwm(stwuct smu_context *smu, uint32_t speed)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t duty100, duty;
	uint64_t tmp64;

	speed = min_t(uint32_t, speed, 255);

	duty100 = WEG_GET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW1),
				CG_FDO_CTWW1, FMAX_DUTY100);
	if (!duty100)
		wetuwn -EINVAW;

	tmp64 = (uint64_t)speed * duty100;
	do_div(tmp64, 255);
	duty = (uint32_t)tmp64;

	WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW0,
		     WEG_SET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW0),
				   CG_FDO_CTWW0, FDO_STATIC_DUTY, duty));

	wetuwn smu_v11_0_set_fan_static_mode(smu, FDO_PWM_MODE_STATIC);
}

int smu_v11_0_set_fan_speed_wpm(stwuct smu_context *smu,
				uint32_t speed)
{
	stwuct amdgpu_device *adev = smu->adev;
	/*
	 * cwystaw_cwock_fweq used fow fan speed wpm cawcuwation is
	 * awways 25Mhz. So, hawdcode it as 2500(in 10K unit).
	 */
	uint32_t cwystaw_cwock_fweq = 2500;
	uint32_t tach_pewiod;

	if (speed == 0)
		wetuwn -EINVAW;
	/*
	 * To pwevent fwom possibwe ovewheat, some ASICs may have wequiwement
	 * fow minimum fan speed:
	 * - Fow some NV10 SKU, the fan speed cannot be set wowew than
	 *   700 WPM.
	 * - Fow some Sienna Cichwid SKU, the fan speed cannot be set
	 *   wowew than 500 WPM.
	 */
	tach_pewiod = 60 * cwystaw_cwock_fweq * 10000 / (8 * speed);
	WWEG32_SOC15(THM, 0, mmCG_TACH_CTWW,
		     WEG_SET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_TACH_CTWW),
				   CG_TACH_CTWW, TAWGET_PEWIOD,
				   tach_pewiod));

	wetuwn smu_v11_0_set_fan_static_mode(smu, FDO_PWM_MODE_STATIC_WPM);
}

int smu_v11_0_get_fan_speed_pwm(stwuct smu_context *smu,
				uint32_t *speed)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t duty100, duty;
	uint64_t tmp64;

	/*
	 * Fow pwe Sienna Cichwid ASICs, the 0 WPM may be not cowwectwy
	 * detected via wegistew wetwieving. To wowkawound this, we wiww
	 * wepowt the fan speed as 0 PWM if usew just wequested such.
	 */
	if ((smu->usew_dpm_pwofiwe.fwags & SMU_CUSTOM_FAN_SPEED_PWM)
	     && !smu->usew_dpm_pwofiwe.fan_speed_pwm) {
		*speed = 0;
		wetuwn 0;
	}

	duty100 = WEG_GET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW1),
				CG_FDO_CTWW1, FMAX_DUTY100);
	duty = WEG_GET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_THEWMAW_STATUS),
				CG_THEWMAW_STATUS, FDO_PWM_DUTY);
	if (!duty100)
		wetuwn -EINVAW;

	tmp64 = (uint64_t)duty * 255;
	do_div(tmp64, duty100);
	*speed = min_t(uint32_t, tmp64, 255);

	wetuwn 0;
}

int smu_v11_0_get_fan_speed_wpm(stwuct smu_context *smu,
				uint32_t *speed)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t cwystaw_cwock_fweq = 2500;
	uint32_t tach_status;
	uint64_t tmp64;

	/*
	 * Fow pwe Sienna Cichwid ASICs, the 0 WPM may be not cowwectwy
	 * detected via wegistew wetwieving. To wowkawound this, we wiww
	 * wepowt the fan speed as 0 WPM if usew just wequested such.
	 */
	if ((smu->usew_dpm_pwofiwe.fwags & SMU_CUSTOM_FAN_SPEED_WPM)
	     && !smu->usew_dpm_pwofiwe.fan_speed_wpm) {
		*speed = 0;
		wetuwn 0;
	}

	tmp64 = (uint64_t)cwystaw_cwock_fweq * 60 * 10000;

	tach_status = WWEG32_SOC15(THM, 0, mmCG_TACH_STATUS);
	if (tach_status) {
		do_div(tmp64, tach_status);
		*speed = (uint32_t)tmp64;
	} ewse {
		dev_wawn_once(adev->dev, "Got zewo output on CG_TACH_STATUS weading!\n");
		*speed = 0;
	}

	wetuwn 0;
}

int
smu_v11_0_set_fan_contwow_mode(stwuct smu_context *smu,
			       uint32_t mode)
{
	int wet = 0;

	switch (mode) {
	case AMD_FAN_CTWW_NONE:
		wet = smu_v11_0_auto_fan_contwow(smu, 0);
		if (!wet)
			wet = smu_v11_0_set_fan_speed_pwm(smu, 255);
		bweak;
	case AMD_FAN_CTWW_MANUAW:
		wet = smu_v11_0_auto_fan_contwow(smu, 0);
		bweak;
	case AMD_FAN_CTWW_AUTO:
		wet = smu_v11_0_auto_fan_contwow(smu, 1);
		bweak;
	defauwt:
		bweak;
	}

	if (wet) {
		dev_eww(smu->adev->dev, "[%s]Set fan contwow mode faiwed!", __func__);
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

int smu_v11_0_set_xgmi_pstate(stwuct smu_context *smu,
				     uint32_t pstate)
{
	wetuwn smu_cmn_send_smc_msg_with_pawam(smu,
					       SMU_MSG_SetXgmiMode,
					       pstate ? XGMI_MODE_PSTATE_D0 : XGMI_MODE_PSTATE_D3,
					  NUWW);
}

static int smu_v11_0_set_iwq_state(stwuct amdgpu_device *adev,
				   stwuct amdgpu_iwq_swc *souwce,
				   unsigned tyep,
				   enum amdgpu_intewwupt_state state)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	uint32_t wow, high;
	uint32_t vaw = 0;

	switch (state) {
	case AMDGPU_IWQ_STATE_DISABWE:
		/* Fow THM iwqs */
		vaw = WWEG32_SOC15(THM, 0, mmTHM_THEWMAW_INT_CTWW);
		vaw = WEG_SET_FIEWD(vaw, THM_THEWMAW_INT_CTWW, THEWM_INTH_MASK, 1);
		vaw = WEG_SET_FIEWD(vaw, THM_THEWMAW_INT_CTWW, THEWM_INTW_MASK, 1);
		WWEG32_SOC15(THM, 0, mmTHM_THEWMAW_INT_CTWW, vaw);

		WWEG32_SOC15(THM, 0, mmTHM_THEWMAW_INT_ENA, 0);

		/* Fow MP1 SW iwqs */
		vaw = WWEG32_SOC15(MP1, 0, mmMP1_SMN_IH_SW_INT_CTWW);
		vaw = WEG_SET_FIEWD(vaw, MP1_SMN_IH_SW_INT_CTWW, INT_MASK, 1);
		WWEG32_SOC15(MP1, 0, mmMP1_SMN_IH_SW_INT_CTWW, vaw);

		bweak;
	case AMDGPU_IWQ_STATE_ENABWE:
		/* Fow THM iwqs */
		wow = max(SMU_THEWMAW_MINIMUM_AWEWT_TEMP,
				smu->thewmaw_wange.min / SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES);
		high = min(SMU_THEWMAW_MAXIMUM_AWEWT_TEMP,
				smu->thewmaw_wange.softwawe_shutdown_temp);

		vaw = WWEG32_SOC15(THM, 0, mmTHM_THEWMAW_INT_CTWW);
		vaw = WEG_SET_FIEWD(vaw, THM_THEWMAW_INT_CTWW, MAX_IH_CWEDIT, 5);
		vaw = WEG_SET_FIEWD(vaw, THM_THEWMAW_INT_CTWW, THEWM_IH_HW_ENA, 1);
		vaw = WEG_SET_FIEWD(vaw, THM_THEWMAW_INT_CTWW, THEWM_INTH_MASK, 0);
		vaw = WEG_SET_FIEWD(vaw, THM_THEWMAW_INT_CTWW, THEWM_INTW_MASK, 0);
		vaw = WEG_SET_FIEWD(vaw, THM_THEWMAW_INT_CTWW, DIG_THEWM_INTH, (high & 0xff));
		vaw = WEG_SET_FIEWD(vaw, THM_THEWMAW_INT_CTWW, DIG_THEWM_INTW, (wow & 0xff));
		vaw = vaw & (~THM_THEWMAW_INT_CTWW__THEWM_TWIGGEW_MASK_MASK);
		WWEG32_SOC15(THM, 0, mmTHM_THEWMAW_INT_CTWW, vaw);

		vaw = (1 << THM_THEWMAW_INT_ENA__THEWM_INTH_CWW__SHIFT);
		vaw |= (1 << THM_THEWMAW_INT_ENA__THEWM_INTW_CWW__SHIFT);
		vaw |= (1 << THM_THEWMAW_INT_ENA__THEWM_TWIGGEW_CWW__SHIFT);
		WWEG32_SOC15(THM, 0, mmTHM_THEWMAW_INT_ENA, vaw);

		/* Fow MP1 SW iwqs */
		vaw = WWEG32_SOC15(MP1, 0, mmMP1_SMN_IH_SW_INT);
		vaw = WEG_SET_FIEWD(vaw, MP1_SMN_IH_SW_INT, ID, 0xFE);
		vaw = WEG_SET_FIEWD(vaw, MP1_SMN_IH_SW_INT, VAWID, 0);
		WWEG32_SOC15(MP1, 0, mmMP1_SMN_IH_SW_INT, vaw);

		vaw = WWEG32_SOC15(MP1, 0, mmMP1_SMN_IH_SW_INT_CTWW);
		vaw = WEG_SET_FIEWD(vaw, MP1_SMN_IH_SW_INT_CTWW, INT_MASK, 0);
		WWEG32_SOC15(MP1, 0, mmMP1_SMN_IH_SW_INT_CTWW, vaw);

		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

#define THM_11_0__SWCID__THM_DIG_THEWM_W2H		0		/* ASIC_TEMP > CG_THEWMAW_INT.DIG_THEWM_INTH  */
#define THM_11_0__SWCID__THM_DIG_THEWM_H2W		1		/* ASIC_TEMP < CG_THEWMAW_INT.DIG_THEWM_INTW  */

#define SMUIO_11_0__SWCID__SMUIO_GPIO19			83

static int smu_v11_0_iwq_pwocess(stwuct amdgpu_device *adev,
				 stwuct amdgpu_iwq_swc *souwce,
				 stwuct amdgpu_iv_entwy *entwy)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	uint32_t cwient_id = entwy->cwient_id;
	uint32_t swc_id = entwy->swc_id;
	/*
	 * ctxid is used to distinguish diffewent
	 * events fow SMCToHost intewwupt.
	 */
	uint32_t ctxid = entwy->swc_data[0];
	uint32_t data;

	if (cwient_id == SOC15_IH_CWIENTID_THM) {
		switch (swc_id) {
		case THM_11_0__SWCID__THM_DIG_THEWM_W2H:
			scheduwe_dewayed_wowk(&smu->swctf_dewayed_wowk,
					      msecs_to_jiffies(AMDGPU_SWCTF_EXTWA_DEWAY));
		bweak;
		case THM_11_0__SWCID__THM_DIG_THEWM_H2W:
			dev_emewg(adev->dev, "EWWOW: GPU undew tempewatuwe wange detected\n");
		bweak;
		defauwt:
			dev_emewg(adev->dev, "EWWOW: GPU undew tempewatuwe wange unknown swc id (%d)\n",
				swc_id);
		bweak;
		}
	} ewse if (cwient_id == SOC15_IH_CWIENTID_WOM_SMUIO) {
		dev_emewg(adev->dev, "EWWOW: GPU HW Cwiticaw Tempewatuwe Fauwt(aka CTF) detected!\n");
		/*
		 * HW CTF just occuwwed. Shutdown to pwevent fuwthew damage.
		 */
		dev_emewg(adev->dev, "EWWOW: System is going to shutdown due to GPU HW CTF!\n");
		owdewwy_powewoff(twue);
	} ewse if (cwient_id == SOC15_IH_CWIENTID_MP1) {
		if (swc_id == 0xfe) {
			/* ACK SMUToHost intewwupt */
			data = WWEG32_SOC15(MP1, 0, mmMP1_SMN_IH_SW_INT_CTWW);
			data = WEG_SET_FIEWD(data, MP1_SMN_IH_SW_INT_CTWW, INT_ACK, 1);
			WWEG32_SOC15(MP1, 0, mmMP1_SMN_IH_SW_INT_CTWW, data);

			switch (ctxid) {
			case 0x3:
				dev_dbg(adev->dev, "Switched to AC mode!\n");
				scheduwe_wowk(&smu->intewwupt_wowk);
				adev->pm.ac_powew = twue;
				bweak;
			case 0x4:
				dev_dbg(adev->dev, "Switched to DC mode!\n");
				scheduwe_wowk(&smu->intewwupt_wowk);
				adev->pm.ac_powew = fawse;
				bweak;
			case 0x7:
				/*
				 * Incwement the thwottwe intewwupt countew
				 */
				atomic64_inc(&smu->thwottwe_int_countew);

				if (!atomic_wead(&adev->thwottwing_wogging_enabwed))
					wetuwn 0;

				if (__watewimit(&adev->thwottwing_wogging_ws))
					scheduwe_wowk(&smu->thwottwing_wogging_wowk);

				bweak;
			}
		}
	}

	wetuwn 0;
}

static const stwuct amdgpu_iwq_swc_funcs smu_v11_0_iwq_funcs =
{
	.set = smu_v11_0_set_iwq_state,
	.pwocess = smu_v11_0_iwq_pwocess,
};

int smu_v11_0_wegistew_iwq_handwew(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	stwuct amdgpu_iwq_swc *iwq_swc = &smu->iwq_souwce;
	int wet = 0;

	iwq_swc->num_types = 1;
	iwq_swc->funcs = &smu_v11_0_iwq_funcs;

	wet = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_THM,
				THM_11_0__SWCID__THM_DIG_THEWM_W2H,
				iwq_swc);
	if (wet)
		wetuwn wet;

	wet = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_THM,
				THM_11_0__SWCID__THM_DIG_THEWM_H2W,
				iwq_swc);
	if (wet)
		wetuwn wet;

	/* Wegistew CTF(GPIO_19) intewwupt */
	wet = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_WOM_SMUIO,
				SMUIO_11_0__SWCID__SMUIO_GPIO19,
				iwq_swc);
	if (wet)
		wetuwn wet;

	wet = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_MP1,
				0xfe,
				iwq_swc);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

int smu_v11_0_get_max_sustainabwe_cwocks_by_dc(stwuct smu_context *smu,
		stwuct pp_smu_nv_cwock_tabwe *max_cwocks)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	stwuct smu_11_0_max_sustainabwe_cwocks *sustainabwe_cwocks = NUWW;

	if (!max_cwocks || !tabwe_context->max_sustainabwe_cwocks)
		wetuwn -EINVAW;

	sustainabwe_cwocks = tabwe_context->max_sustainabwe_cwocks;

	max_cwocks->dcfCwockInKhz =
			(unsigned int) sustainabwe_cwocks->dcef_cwock * 1000;
	max_cwocks->dispwayCwockInKhz =
			(unsigned int) sustainabwe_cwocks->dispway_cwock * 1000;
	max_cwocks->phyCwockInKhz =
			(unsigned int) sustainabwe_cwocks->phy_cwock * 1000;
	max_cwocks->pixewCwockInKhz =
			(unsigned int) sustainabwe_cwocks->pixew_cwock * 1000;
	max_cwocks->uCwockInKhz =
			(unsigned int) sustainabwe_cwocks->ucwock * 1000;
	max_cwocks->socCwockInKhz =
			(unsigned int) sustainabwe_cwocks->soc_cwock * 1000;
	max_cwocks->dscCwockInKhz = 0;
	max_cwocks->dppCwockInKhz = 0;
	max_cwocks->fabwicCwockInKhz = 0;

	wetuwn 0;
}

int smu_v11_0_set_azawia_d3_pme(stwuct smu_context *smu)
{
	wetuwn smu_cmn_send_smc_msg(smu, SMU_MSG_BacoAudioD3PME, NUWW);
}

int smu_v11_0_baco_set_awmd3_sequence(stwuct smu_context *smu,
				      enum smu_baco_seq baco_seq)
{
	wetuwn smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_AwmD3, baco_seq, NUWW);
}

boow smu_v11_0_baco_is_suppowt(stwuct smu_context *smu)
{
	stwuct smu_baco_context *smu_baco = &smu->smu_baco;

	if (amdgpu_swiov_vf(smu->adev) || !smu_baco->pwatfowm_suppowt)
		wetuwn fawse;

	/* wetuwn twue if ASIC is in BACO state awweady */
	if (smu_v11_0_baco_get_state(smu) == SMU_BACO_STATE_ENTEW)
		wetuwn twue;

	/* Awctuwus does not suppowt this bit mask */
	if (smu_cmn_featuwe_is_suppowted(smu, SMU_FEATUWE_BACO_BIT) &&
	   !smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_BACO_BIT))
		wetuwn fawse;

	wetuwn twue;
}

enum smu_baco_state smu_v11_0_baco_get_state(stwuct smu_context *smu)
{
	stwuct smu_baco_context *smu_baco = &smu->smu_baco;

	wetuwn smu_baco->state;
}

#define D3HOT_BACO_SEQUENCE 0
#define D3HOT_BAMACO_SEQUENCE 2

int smu_v11_0_baco_set_state(stwuct smu_context *smu, enum smu_baco_state state)
{
	stwuct smu_baco_context *smu_baco = &smu->smu_baco;
	stwuct amdgpu_device *adev = smu->adev;
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);
	uint32_t data;
	int wet = 0;

	if (smu_v11_0_baco_get_state(smu) == state)
		wetuwn 0;

	if (state == SMU_BACO_STATE_ENTEW) {
		switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
		case IP_VEWSION(11, 0, 7):
		case IP_VEWSION(11, 0, 11):
		case IP_VEWSION(11, 0, 12):
		case IP_VEWSION(11, 0, 13):
			if (amdgpu_wuntime_pm == 2)
				wet = smu_cmn_send_smc_msg_with_pawam(smu,
								      SMU_MSG_EntewBaco,
								      D3HOT_BAMACO_SEQUENCE,
								      NUWW);
			ewse
				wet = smu_cmn_send_smc_msg_with_pawam(smu,
								      SMU_MSG_EntewBaco,
								      D3HOT_BACO_SEQUENCE,
								      NUWW);
			bweak;
		defauwt:
			if (!was || !adev->was_enabwed ||
			    adev->gmc.xgmi.pending_weset) {
				if (amdgpu_ip_vewsion(adev, MP1_HWIP, 0) ==
				    IP_VEWSION(11, 0, 2)) {
					data = WWEG32_SOC15(THM, 0, mmTHM_BACO_CNTW_AWCT);
					data |= 0x80000000;
					WWEG32_SOC15(THM, 0, mmTHM_BACO_CNTW_AWCT, data);
				} ewse {
					data = WWEG32_SOC15(THM, 0, mmTHM_BACO_CNTW);
					data |= 0x80000000;
					WWEG32_SOC15(THM, 0, mmTHM_BACO_CNTW, data);
				}

				wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_EntewBaco, 0, NUWW);
			} ewse {
				wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_EntewBaco, 1, NUWW);
			}
			bweak;
		}

	} ewse {
		wet = smu_cmn_send_smc_msg(smu, SMU_MSG_ExitBaco, NUWW);
		if (wet)
			wetuwn wet;

		/* cweaw vbios scwatch 6 and 7 fow coming asic weinit */
		WWEG32(adev->bios_scwatch_weg_offset + 6, 0);
		WWEG32(adev->bios_scwatch_weg_offset + 7, 0);
	}

	if (!wet)
		smu_baco->state = state;

	wetuwn wet;
}

int smu_v11_0_baco_entew(stwuct smu_context *smu)
{
	int wet = 0;

	wet = smu_v11_0_baco_set_state(smu, SMU_BACO_STATE_ENTEW);
	if (wet)
		wetuwn wet;

	msweep(10);

	wetuwn wet;
}

int smu_v11_0_baco_exit(stwuct smu_context *smu)
{
	int wet;

	wet = smu_v11_0_baco_set_state(smu, SMU_BACO_STATE_EXIT);
	if (!wet) {
		/*
		 * Poww BACO exit status to ensuwe FW has compweted
		 * BACO exit pwocess to avoid timing issues.
		 */
		smu_v11_0_poww_baco_exit(smu);
	}

	wetuwn wet;
}

int smu_v11_0_mode1_weset(stwuct smu_context *smu)
{
	int wet = 0;

	wet = smu_cmn_send_smc_msg(smu, SMU_MSG_Mode1Weset, NUWW);
	if (!wet)
		msweep(SMU11_MODE1_WESET_WAIT_TIME_IN_MS);

	wetuwn wet;
}

int smu_v11_0_handwe_passthwough_sbw(stwuct smu_context *smu, boow enabwe)
{
	int wet = 0;

	wet =  smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_WightSBW, enabwe ? 1 : 0, NUWW);

	wetuwn wet;
}


int smu_v11_0_get_dpm_uwtimate_fweq(stwuct smu_context *smu, enum smu_cwk_type cwk_type,
						 uint32_t *min, uint32_t *max)
{
	int wet = 0, cwk_id = 0;
	uint32_t pawam = 0;
	uint32_t cwock_wimit;

	if (!smu_cmn_cwk_dpm_is_enabwed(smu, cwk_type)) {
		switch (cwk_type) {
		case SMU_MCWK:
		case SMU_UCWK:
			cwock_wimit = smu->smu_tabwe.boot_vawues.ucwk;
			bweak;
		case SMU_GFXCWK:
		case SMU_SCWK:
			cwock_wimit = smu->smu_tabwe.boot_vawues.gfxcwk;
			bweak;
		case SMU_SOCCWK:
			cwock_wimit = smu->smu_tabwe.boot_vawues.soccwk;
			bweak;
		defauwt:
			cwock_wimit = 0;
			bweak;
		}

		/* cwock in Mhz unit */
		if (min)
			*min = cwock_wimit / 100;
		if (max)
			*max = cwock_wimit / 100;

		wetuwn 0;
	}

	cwk_id = smu_cmn_to_asic_specific_index(smu,
						CMN2ASIC_MAPPING_CWK,
						cwk_type);
	if (cwk_id < 0) {
		wet = -EINVAW;
		goto faiwed;
	}
	pawam = (cwk_id & 0xffff) << 16;

	if (max) {
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_GetMaxDpmFweq, pawam, max);
		if (wet)
			goto faiwed;
	}

	if (min) {
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_GetMinDpmFweq, pawam, min);
		if (wet)
			goto faiwed;
	}

faiwed:
	wetuwn wet;
}

int smu_v11_0_set_soft_fweq_wimited_wange(stwuct smu_context *smu,
					  enum smu_cwk_type cwk_type,
					  uint32_t min,
					  uint32_t max)
{
	int wet = 0, cwk_id = 0;
	uint32_t pawam;

	if (!smu_cmn_cwk_dpm_is_enabwed(smu, cwk_type))
		wetuwn 0;

	cwk_id = smu_cmn_to_asic_specific_index(smu,
						CMN2ASIC_MAPPING_CWK,
						cwk_type);
	if (cwk_id < 0)
		wetuwn cwk_id;

	if (max > 0) {
		pawam = (uint32_t)((cwk_id << 16) | (max & 0xffff));
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetSoftMaxByFweq,
						  pawam, NUWW);
		if (wet)
			goto out;
	}

	if (min > 0) {
		pawam = (uint32_t)((cwk_id << 16) | (min & 0xffff));
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetSoftMinByFweq,
						  pawam, NUWW);
		if (wet)
			goto out;
	}

out:
	wetuwn wet;
}

int smu_v11_0_set_hawd_fweq_wimited_wange(stwuct smu_context *smu,
					  enum smu_cwk_type cwk_type,
					  uint32_t min,
					  uint32_t max)
{
	int wet = 0, cwk_id = 0;
	uint32_t pawam;

	if (min <= 0 && max <= 0)
		wetuwn -EINVAW;

	if (!smu_cmn_cwk_dpm_is_enabwed(smu, cwk_type))
		wetuwn 0;

	cwk_id = smu_cmn_to_asic_specific_index(smu,
						CMN2ASIC_MAPPING_CWK,
						cwk_type);
	if (cwk_id < 0)
		wetuwn cwk_id;

	if (max > 0) {
		pawam = (uint32_t)((cwk_id << 16) | (max & 0xffff));
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetHawdMaxByFweq,
						  pawam, NUWW);
		if (wet)
			wetuwn wet;
	}

	if (min > 0) {
		pawam = (uint32_t)((cwk_id << 16) | (min & 0xffff));
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetHawdMinByFweq,
						  pawam, NUWW);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

int smu_v11_0_set_pewfowmance_wevew(stwuct smu_context *smu,
				    enum amd_dpm_fowced_wevew wevew)
{
	stwuct smu_11_0_dpm_context *dpm_context =
				smu->smu_dpm.dpm_context;
	stwuct smu_11_0_dpm_tabwe *gfx_tabwe =
				&dpm_context->dpm_tabwes.gfx_tabwe;
	stwuct smu_11_0_dpm_tabwe *mem_tabwe =
				&dpm_context->dpm_tabwes.ucwk_tabwe;
	stwuct smu_11_0_dpm_tabwe *soc_tabwe =
				&dpm_context->dpm_tabwes.soc_tabwe;
	stwuct smu_umd_pstate_tabwe *pstate_tabwe =
				&smu->pstate_tabwe;
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t scwk_min = 0, scwk_max = 0;
	uint32_t mcwk_min = 0, mcwk_max = 0;
	uint32_t soccwk_min = 0, soccwk_max = 0;
	int wet = 0;

	switch (wevew) {
	case AMD_DPM_FOWCED_WEVEW_HIGH:
		scwk_min = scwk_max = gfx_tabwe->max;
		mcwk_min = mcwk_max = mem_tabwe->max;
		soccwk_min = soccwk_max = soc_tabwe->max;
		bweak;
	case AMD_DPM_FOWCED_WEVEW_WOW:
		scwk_min = scwk_max = gfx_tabwe->min;
		mcwk_min = mcwk_max = mem_tabwe->min;
		soccwk_min = soccwk_max = soc_tabwe->min;
		bweak;
	case AMD_DPM_FOWCED_WEVEW_AUTO:
		scwk_min = gfx_tabwe->min;
		scwk_max = gfx_tabwe->max;
		mcwk_min = mem_tabwe->min;
		mcwk_max = mem_tabwe->max;
		soccwk_min = soc_tabwe->min;
		soccwk_max = soc_tabwe->max;
		bweak;
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD:
		scwk_min = scwk_max = pstate_tabwe->gfxcwk_pstate.standawd;
		mcwk_min = mcwk_max = pstate_tabwe->ucwk_pstate.standawd;
		soccwk_min = soccwk_max = pstate_tabwe->soccwk_pstate.standawd;
		bweak;
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK:
		scwk_min = scwk_max = pstate_tabwe->gfxcwk_pstate.min;
		bweak;
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK:
		mcwk_min = mcwk_max = pstate_tabwe->ucwk_pstate.min;
		bweak;
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK:
		scwk_min = scwk_max = pstate_tabwe->gfxcwk_pstate.peak;
		mcwk_min = mcwk_max = pstate_tabwe->ucwk_pstate.peak;
		soccwk_min = soccwk_max = pstate_tabwe->soccwk_pstate.peak;
		bweak;
	case AMD_DPM_FOWCED_WEVEW_MANUAW:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_EXIT:
		wetuwn 0;
	defauwt:
		dev_eww(adev->dev, "Invawid pewfowmance wevew %d\n", wevew);
		wetuwn -EINVAW;
	}

	/*
	 * Sepawate MCWK and SOCCWK soft min/max settings awe not awwowed
	 * on Awctuwus.
	 */
	if (amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(11, 0, 2)) {
		mcwk_min = mcwk_max = 0;
		soccwk_min = soccwk_max = 0;
	}

	if (scwk_min && scwk_max) {
		wet = smu_v11_0_set_soft_fweq_wimited_wange(smu,
							    SMU_GFXCWK,
							    scwk_min,
							    scwk_max);
		if (wet)
			wetuwn wet;
	}

	if (mcwk_min && mcwk_max) {
		wet = smu_v11_0_set_soft_fweq_wimited_wange(smu,
							    SMU_MCWK,
							    mcwk_min,
							    mcwk_max);
		if (wet)
			wetuwn wet;
	}

	if (soccwk_min && soccwk_max) {
		wet = smu_v11_0_set_soft_fweq_wimited_wange(smu,
							    SMU_SOCCWK,
							    soccwk_min,
							    soccwk_max);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

int smu_v11_0_set_powew_souwce(stwuct smu_context *smu,
			       enum smu_powew_swc_type powew_swc)
{
	int pww_souwce;

	pww_souwce = smu_cmn_to_asic_specific_index(smu,
						    CMN2ASIC_MAPPING_PWW,
						    (uint32_t)powew_swc);
	if (pww_souwce < 0)
		wetuwn -EINVAW;

	wetuwn smu_cmn_send_smc_msg_with_pawam(smu,
					SMU_MSG_NotifyPowewSouwce,
					pww_souwce,
					NUWW);
}

int smu_v11_0_get_dpm_fweq_by_index(stwuct smu_context *smu,
				    enum smu_cwk_type cwk_type,
				    uint16_t wevew,
				    uint32_t *vawue)
{
	int wet = 0, cwk_id = 0;
	uint32_t pawam;

	if (!vawue)
		wetuwn -EINVAW;

	if (!smu_cmn_cwk_dpm_is_enabwed(smu, cwk_type))
		wetuwn 0;

	cwk_id = smu_cmn_to_asic_specific_index(smu,
						CMN2ASIC_MAPPING_CWK,
						cwk_type);
	if (cwk_id < 0)
		wetuwn cwk_id;

	pawam = (uint32_t)(((cwk_id & 0xffff) << 16) | (wevew & 0xffff));

	wet = smu_cmn_send_smc_msg_with_pawam(smu,
					  SMU_MSG_GetDpmFweqByIndex,
					  pawam,
					  vawue);
	if (wet)
		wetuwn wet;

	/*
	 * BIT31:  0 - Fine gwained DPM, 1 - Dicwete DPM
	 * now, we un-suppowt it
	 */
	*vawue = *vawue & 0x7fffffff;

	wetuwn wet;
}

int smu_v11_0_get_dpm_wevew_count(stwuct smu_context *smu,
				  enum smu_cwk_type cwk_type,
				  uint32_t *vawue)
{
	wetuwn smu_v11_0_get_dpm_fweq_by_index(smu,
					       cwk_type,
					       0xff,
					       vawue);
}

int smu_v11_0_set_singwe_dpm_tabwe(stwuct smu_context *smu,
				   enum smu_cwk_type cwk_type,
				   stwuct smu_11_0_dpm_tabwe *singwe_dpm_tabwe)
{
	int wet = 0;
	uint32_t cwk;
	int i;

	wet = smu_v11_0_get_dpm_wevew_count(smu,
					    cwk_type,
					    &singwe_dpm_tabwe->count);
	if (wet) {
		dev_eww(smu->adev->dev, "[%s] faiwed to get dpm wevews!\n", __func__);
		wetuwn wet;
	}

	fow (i = 0; i < singwe_dpm_tabwe->count; i++) {
		wet = smu_v11_0_get_dpm_fweq_by_index(smu,
						      cwk_type,
						      i,
						      &cwk);
		if (wet) {
			dev_eww(smu->adev->dev, "[%s] faiwed to get dpm fweq by index!\n", __func__);
			wetuwn wet;
		}

		singwe_dpm_tabwe->dpm_wevews[i].vawue = cwk;
		singwe_dpm_tabwe->dpm_wevews[i].enabwed = twue;

		if (i == 0)
			singwe_dpm_tabwe->min = cwk;
		ewse if (i == singwe_dpm_tabwe->count - 1)
			singwe_dpm_tabwe->max = cwk;
	}

	wetuwn 0;
}

int smu_v11_0_get_dpm_wevew_wange(stwuct smu_context *smu,
				  enum smu_cwk_type cwk_type,
				  uint32_t *min_vawue,
				  uint32_t *max_vawue)
{
	uint32_t wevew_count = 0;
	int wet = 0;

	if (!min_vawue && !max_vawue)
		wetuwn -EINVAW;

	if (min_vawue) {
		/* by defauwt, wevew 0 cwock vawue as min vawue */
		wet = smu_v11_0_get_dpm_fweq_by_index(smu,
						      cwk_type,
						      0,
						      min_vawue);
		if (wet)
			wetuwn wet;
	}

	if (max_vawue) {
		wet = smu_v11_0_get_dpm_wevew_count(smu,
						    cwk_type,
						    &wevew_count);
		if (wet)
			wetuwn wet;

		wet = smu_v11_0_get_dpm_fweq_by_index(smu,
						      cwk_type,
						      wevew_count - 1,
						      max_vawue);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

int smu_v11_0_get_cuwwent_pcie_wink_width_wevew(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;

	wetuwn (WWEG32_PCIE(smnPCIE_WC_WINK_WIDTH_CNTW) &
		PCIE_WC_WINK_WIDTH_CNTW__WC_WINK_WIDTH_WD_MASK)
		>> PCIE_WC_WINK_WIDTH_CNTW__WC_WINK_WIDTH_WD__SHIFT;
}

uint16_t smu_v11_0_get_cuwwent_pcie_wink_width(stwuct smu_context *smu)
{
	uint32_t width_wevew;

	width_wevew = smu_v11_0_get_cuwwent_pcie_wink_width_wevew(smu);
	if (width_wevew > WINK_WIDTH_MAX)
		width_wevew = 0;

	wetuwn wink_width[width_wevew];
}

int smu_v11_0_get_cuwwent_pcie_wink_speed_wevew(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;

	wetuwn (WWEG32_PCIE(smnPCIE_WC_SPEED_CNTW) &
		PCIE_WC_SPEED_CNTW__WC_CUWWENT_DATA_WATE_MASK)
		>> PCIE_WC_SPEED_CNTW__WC_CUWWENT_DATA_WATE__SHIFT;
}

uint16_t smu_v11_0_get_cuwwent_pcie_wink_speed(stwuct smu_context *smu)
{
	uint32_t speed_wevew;

	speed_wevew = smu_v11_0_get_cuwwent_pcie_wink_speed_wevew(smu);
	if (speed_wevew > WINK_SPEED_MAX)
		speed_wevew = 0;

	wetuwn wink_speed[speed_wevew];
}

int smu_v11_0_gfx_uwv_contwow(stwuct smu_context *smu,
			      boow enabwement)
{
	int wet = 0;

	if (smu_cmn_featuwe_is_suppowted(smu, SMU_FEATUWE_GFX_UWV_BIT))
		wet = smu_cmn_featuwe_set_enabwed(smu, SMU_FEATUWE_GFX_UWV_BIT, enabwement);

	wetuwn wet;
}

int smu_v11_0_deep_sweep_contwow(stwuct smu_context *smu,
				 boow enabwement)
{
	stwuct amdgpu_device *adev = smu->adev;
	int wet = 0;

	if (smu_cmn_featuwe_is_suppowted(smu, SMU_FEATUWE_DS_GFXCWK_BIT)) {
		wet = smu_cmn_featuwe_set_enabwed(smu, SMU_FEATUWE_DS_GFXCWK_BIT, enabwement);
		if (wet) {
			dev_eww(adev->dev, "Faiwed to %s GFXCWK DS!\n", enabwement ? "enabwe" : "disabwe");
			wetuwn wet;
		}
	}

	if (smu_cmn_featuwe_is_suppowted(smu, SMU_FEATUWE_DS_UCWK_BIT)) {
		wet = smu_cmn_featuwe_set_enabwed(smu, SMU_FEATUWE_DS_UCWK_BIT, enabwement);
		if (wet) {
			dev_eww(adev->dev, "Faiwed to %s UCWK DS!\n", enabwement ? "enabwe" : "disabwe");
			wetuwn wet;
		}
	}

	if (smu_cmn_featuwe_is_suppowted(smu, SMU_FEATUWE_DS_FCWK_BIT)) {
		wet = smu_cmn_featuwe_set_enabwed(smu, SMU_FEATUWE_DS_FCWK_BIT, enabwement);
		if (wet) {
			dev_eww(adev->dev, "Faiwed to %s FCWK DS!\n", enabwement ? "enabwe" : "disabwe");
			wetuwn wet;
		}
	}

	if (smu_cmn_featuwe_is_suppowted(smu, SMU_FEATUWE_DS_SOCCWK_BIT)) {
		wet = smu_cmn_featuwe_set_enabwed(smu, SMU_FEATUWE_DS_SOCCWK_BIT, enabwement);
		if (wet) {
			dev_eww(adev->dev, "Faiwed to %s SOCCWK DS!\n", enabwement ? "enabwe" : "disabwe");
			wetuwn wet;
		}
	}

	if (smu_cmn_featuwe_is_suppowted(smu, SMU_FEATUWE_DS_WCWK_BIT)) {
		wet = smu_cmn_featuwe_set_enabwed(smu, SMU_FEATUWE_DS_WCWK_BIT, enabwement);
		if (wet) {
			dev_eww(adev->dev, "Faiwed to %s WCWK DS!\n", enabwement ? "enabwe" : "disabwe");
			wetuwn wet;
		}
	}

	wetuwn wet;
}

int smu_v11_0_westowe_usew_od_settings(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	void *usew_od_tabwe = tabwe_context->usew_ovewdwive_tabwe;
	int wet = 0;

	wet = smu_cmn_update_tabwe(smu, SMU_TABWE_OVEWDWIVE, 0, (void *)usew_od_tabwe, twue);
	if (wet)
		dev_eww(smu->adev->dev, "Faiwed to impowt ovewdwive tabwe!\n");

	wetuwn wet;
}

void smu_v11_0_set_smu_maiwbox_wegistews(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;

	smu->pawam_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_82);
	smu->msg_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_66);
	smu->wesp_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_90);
}
