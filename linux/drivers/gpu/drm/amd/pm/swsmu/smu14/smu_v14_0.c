/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

#define SWSMU_CODE_WAYEW_W3

#incwude "amdgpu.h"
#incwude "amdgpu_smu.h"
#incwude "atomfiwmwawe.h"
#incwude "amdgpu_atomfiwmwawe.h"
#incwude "amdgpu_atombios.h"
#incwude "smu_v14_0.h"
#incwude "soc15_common.h"
#incwude "atom.h"
#incwude "amdgpu_was.h"
#incwude "smu_cmn.h"

#incwude "asic_weg/mp/mp_14_0_0_offset.h"
#incwude "asic_weg/mp/mp_14_0_0_sh_mask.h"

/*
 * DO NOT use these fow eww/wawn/info/debug messages.
 * Use dev_eww, dev_wawn, dev_info and dev_dbg instead.
 * They awe mowe MGPU fwiendwy.
 */
#undef pw_eww
#undef pw_wawn
#undef pw_info
#undef pw_debug

MODUWE_FIWMWAWE("amdgpu/smu_14_0_2.bin");

int smu_v14_0_init_micwocode(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	chaw fw_name[30];
	chaw ucode_pwefix[15];
	int eww = 0;
	const stwuct smc_fiwmwawe_headew_v1_0 *hdw;
	const stwuct common_fiwmwawe_headew *headew;
	stwuct amdgpu_fiwmwawe_info *ucode = NUWW;

	/* doesn't need to woad smu fiwmwawe in IOV mode */
	if (amdgpu_swiov_vf(adev))
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

void smu_v14_0_fini_micwocode(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;

	amdgpu_ucode_wewease(&adev->pm.fw);
	adev->pm.fw_vewsion = 0;
}

int smu_v14_0_woad_micwocode(stwuct smu_context *smu)
{
#if 0
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
		    1 & MP1_SMN_PUB_CTWW__WX3_WESET_MASK);
	WWEG32_PCIE(MP1_Pubwic | (smnMP1_PUB_CTWW & 0xffffffff),
		    1 & ~MP1_SMN_PUB_CTWW__WX3_WESET_MASK);

	fow (i = 0; i < adev->usec_timeout; i++) {
		mp1_fw_fwags = WWEG32_PCIE(MP1_Pubwic |
					   (smnMP1_FIWMWAWE_FWAGS & 0xffffffff));
		if ((mp1_fw_fwags & MP1_CWU1_MP1_FIWMWAWE_FWAGS__INTEWWUPTS_ENABWED_MASK) >>
		    MP1_CWU1_MP1_FIWMWAWE_FWAGS__INTEWWUPTS_ENABWED__SHIFT)
			bweak;
		udeway(1);
	}

	if (i == adev->usec_timeout)
		wetuwn -ETIME;

#endif
	wetuwn 0;

}

int smu_v14_0_init_pptabwe_micwocode(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	stwuct amdgpu_fiwmwawe_info *ucode = NUWW;
	uint32_t size = 0, pptabwe_id = 0;
	int wet = 0;
	void *tabwe;

	/* doesn't need to woad smu fiwmwawe in IOV mode */
	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	if (adev->fiwmwawe.woad_type != AMDGPU_FW_WOAD_PSP)
		wetuwn 0;

	if (!adev->scpm_enabwed)
		wetuwn 0;

	/* ovewwide pptabwe_id fwom dwivew pawametew */
	if (amdgpu_smu_pptabwe_id >= 0) {
		pptabwe_id = amdgpu_smu_pptabwe_id;
		dev_info(adev->dev, "ovewwide pptabwe id %d\n", pptabwe_id);
	} ewse {
		pptabwe_id = smu->smu_tabwe.boot_vawues.pp_tabwe_id;
	}

	/* "pptabwe_id == 0" means vbios cawwies the pptabwe. */
	if (!pptabwe_id)
		wetuwn 0;

	wet = smu_v14_0_get_pptabwe_fwom_fiwmwawe(smu, &tabwe, &size, pptabwe_id);
	if (wet)
		wetuwn wet;

	smu->pptabwe_fiwmwawe.data = tabwe;
	smu->pptabwe_fiwmwawe.size = size;

	ucode = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_PPTABWE];
	ucode->ucode_id = AMDGPU_UCODE_ID_PPTABWE;
	ucode->fw = &smu->pptabwe_fiwmwawe;
	adev->fiwmwawe.fw_size +=
		AWIGN(smu->pptabwe_fiwmwawe.size, PAGE_SIZE);

	wetuwn 0;
}

int smu_v14_0_check_fw_status(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t mp1_fw_fwags;

	mp1_fw_fwags = WWEG32_PCIE(MP1_Pubwic |
					   (smnMP1_FIWMWAWE_FWAGS & 0xffffffff));

	if ((mp1_fw_fwags & MP1_CWU1_MP1_FIWMWAWE_FWAGS__INTEWWUPTS_ENABWED_MASK) >>
	    MP1_CWU1_MP1_FIWMWAWE_FWAGS__INTEWWUPTS_ENABWED__SHIFT)
		wetuwn 0;

	wetuwn -EIO;
}

int smu_v14_0_check_fw_vewsion(stwuct smu_context *smu)
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
	case IP_VEWSION(14, 0, 2):
		smu->smc_dwivew_if_vewsion = SMU14_DWIVEW_IF_VEWSION_SMU_V14_0_2;
		bweak;
	case IP_VEWSION(14, 0, 0):
		if ((smu->smc_fw_vewsion < 0x5d3a00))
			dev_wawn(smu->adev->dev, "The PMFW vewsion(%x) is behind in this BIOS!\n", smu->smc_fw_vewsion);
		smu->smc_dwivew_if_vewsion = SMU14_DWIVEW_IF_VEWSION_SMU_V14_0_0;
		bweak;
	defauwt:
		dev_eww(adev->dev, "smu unsuppowted IP vewsion: 0x%x.\n",
			amdgpu_ip_vewsion(adev, MP1_HWIP, 0));
		smu->smc_dwivew_if_vewsion = SMU14_DWIVEW_IF_VEWSION_INV;
		bweak;
	}

	if (adev->pm.fw)
		dev_dbg(smu->adev->dev, "smu fw wepowted pwogwam %d, vewsion = 0x%08x (%d.%d.%d)\n",
			 smu_pwogwam, smu_vewsion, smu_majow, smu_minow, smu_debug);

	/*
	 * 1. if_vewsion mismatch is not cwiticaw as ouw fw is designed
	 * to be backwawd compatibwe.
	 * 2. New fw usuawwy bwings some optimizations. But that's visibwe
	 * onwy on the paiwed dwivew.
	 * Considewing above, we just weave usew a vewbaw message instead
	 * of hawt dwivew woading.
	 */
	if (if_vewsion != smu->smc_dwivew_if_vewsion) {
		dev_info(adev->dev, "smu dwivew if vewsion = 0x%08x, smu fw if vewsion = 0x%08x, "
			 "smu fw pwogwam = %d, smu fw vewsion = 0x%08x (%d.%d.%d)\n",
			 smu->smc_dwivew_if_vewsion, if_vewsion,
			 smu_pwogwam, smu_vewsion, smu_majow, smu_minow, smu_debug);
		dev_info(adev->dev, "SMU dwivew if vewsion not matched\n");
	}

	wetuwn wet;
}

static int smu_v14_0_set_pptabwe_v2_0(stwuct smu_context *smu, void **tabwe, uint32_t *size)
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

static int smu_v14_0_set_pptabwe_v2_1(stwuct smu_context *smu, void **tabwe,
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

static int smu_v14_0_get_pptabwe_fwom_vbios(stwuct smu_context *smu, void **tabwe, uint32_t *size)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint16_t atom_tabwe_size;
	uint8_t fwev, cwev;
	int wet, index;

	dev_info(adev->dev, "use vbios pwovided pptabwe\n");
	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
					    powewpwayinfo);

	wet = amdgpu_atombios_get_data_tabwe(adev, index, &atom_tabwe_size, &fwev, &cwev,
					     (uint8_t **)tabwe);
	if (wet)
		wetuwn wet;

	if (size)
		*size = atom_tabwe_size;

	wetuwn 0;
}

int smu_v14_0_get_pptabwe_fwom_fiwmwawe(stwuct smu_context *smu,
					void **tabwe,
					uint32_t *size,
					uint32_t pptabwe_id)
{
	const stwuct smc_fiwmwawe_headew_v1_0 *hdw;
	stwuct amdgpu_device *adev = smu->adev;
	uint16_t vewsion_majow, vewsion_minow;
	int wet;

	hdw = (const stwuct smc_fiwmwawe_headew_v1_0 *) adev->pm.fw->data;
	if (!hdw)
		wetuwn -EINVAW;

	dev_info(adev->dev, "use dwivew pwovided pptabwe %d\n", pptabwe_id);

	vewsion_majow = we16_to_cpu(hdw->headew.headew_vewsion_majow);
	vewsion_minow = we16_to_cpu(hdw->headew.headew_vewsion_minow);
	if (vewsion_majow != 2) {
		dev_eww(adev->dev, "Unsuppowted smu fiwmwawe vewsion %d.%d\n",
			vewsion_majow, vewsion_minow);
		wetuwn -EINVAW;
	}

	switch (vewsion_minow) {
	case 0:
		wet = smu_v14_0_set_pptabwe_v2_0(smu, tabwe, size);
		bweak;
	case 1:
		wet = smu_v14_0_set_pptabwe_v2_1(smu, tabwe, size, pptabwe_id);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

int smu_v14_0_setup_pptabwe(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t size = 0, pptabwe_id = 0;
	void *tabwe;
	int wet = 0;

	/* ovewwide pptabwe_id fwom dwivew pawametew */
	if (amdgpu_smu_pptabwe_id >= 0) {
		pptabwe_id = amdgpu_smu_pptabwe_id;
		dev_info(adev->dev, "ovewwide pptabwe id %d\n", pptabwe_id);
	} ewse {
		pptabwe_id = smu->smu_tabwe.boot_vawues.pp_tabwe_id;
	}

	/* fowce using vbios pptabwe in swiov mode */
	if ((amdgpu_swiov_vf(adev) || !pptabwe_id) && (amdgpu_emu_mode != 1))
		wet = smu_v14_0_get_pptabwe_fwom_vbios(smu, &tabwe, &size);
	ewse
		wet = smu_v14_0_get_pptabwe_fwom_fiwmwawe(smu, &tabwe, &size, pptabwe_id);

	if (wet)
		wetuwn wet;

	if (!smu->smu_tabwe.powew_pway_tabwe)
		smu->smu_tabwe.powew_pway_tabwe = tabwe;
	if (!smu->smu_tabwe.powew_pway_tabwe_size)
		smu->smu_tabwe.powew_pway_tabwe_size = size;

	wetuwn 0;
}

int smu_v14_0_init_smc_tabwes(stwuct smu_context *smu)
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
		kzawwoc(sizeof(stwuct smu_14_0_max_sustainabwe_cwocks), GFP_KEWNEW);
	if (!smu_tabwe->max_sustainabwe_cwocks) {
		wet = -ENOMEM;
		goto eww1_out;
	}

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
	}

	smu_tabwe->combo_pptabwe =
		kzawwoc(tabwes[SMU_TABWE_COMBO_PPTABWE].size, GFP_KEWNEW);
	if (!smu_tabwe->combo_pptabwe) {
		wet = -ENOMEM;
		goto eww4_out;
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

int smu_v14_0_fini_smc_tabwes(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_dpm_context *smu_dpm = &smu->smu_dpm;

	kfwee(smu_tabwe->gpu_metwics_tabwe);
	kfwee(smu_tabwe->combo_pptabwe);
	kfwee(smu_tabwe->boot_ovewdwive_tabwe);
	kfwee(smu_tabwe->ovewdwive_tabwe);
	kfwee(smu_tabwe->max_sustainabwe_cwocks);
	kfwee(smu_tabwe->dwivew_pptabwe);
	smu_tabwe->gpu_metwics_tabwe = NUWW;
	smu_tabwe->combo_pptabwe = NUWW;
	smu_tabwe->boot_ovewdwive_tabwe = NUWW;
	smu_tabwe->ovewdwive_tabwe = NUWW;
	smu_tabwe->max_sustainabwe_cwocks = NUWW;
	smu_tabwe->dwivew_pptabwe = NUWW;
	kfwee(smu_tabwe->hawdcode_pptabwe);
	smu_tabwe->hawdcode_pptabwe = NUWW;

	kfwee(smu_tabwe->ecc_tabwe);
	kfwee(smu_tabwe->metwics_tabwe);
	kfwee(smu_tabwe->watewmawks_tabwe);
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

int smu_v14_0_init_powew(stwuct smu_context *smu)
{
	stwuct smu_powew_context *smu_powew = &smu->smu_powew;

	if (smu_powew->powew_context || smu_powew->powew_context_size != 0)
		wetuwn -EINVAW;

	smu_powew->powew_context = kzawwoc(sizeof(stwuct smu_14_0_dpm_context),
					   GFP_KEWNEW);
	if (!smu_powew->powew_context)
		wetuwn -ENOMEM;
	smu_powew->powew_context_size = sizeof(stwuct smu_14_0_dpm_context);

	wetuwn 0;
}

int smu_v14_0_fini_powew(stwuct smu_context *smu)
{
	stwuct smu_powew_context *smu_powew = &smu->smu_powew;

	if (!smu_powew->powew_context || smu_powew->powew_context_size == 0)
		wetuwn -EINVAW;

	kfwee(smu_powew->powew_context);
	smu_powew->powew_context = NUWW;
	smu_powew->powew_context_size = 0;

	wetuwn 0;
}

int smu_v14_0_get_vbios_bootup_vawues(stwuct smu_context *smu)
{
	int wet, index;
	uint16_t size;
	uint8_t fwev, cwev;
	stwuct atom_common_tabwe_headew *headew;
	stwuct atom_fiwmwawe_info_v3_4 *v_3_4;
	stwuct atom_fiwmwawe_info_v3_3 *v_3_3;
	stwuct atom_fiwmwawe_info_v3_1 *v_3_1;
	stwuct atom_smu_info_v3_6 *smu_info_v3_6;
	stwuct atom_smu_info_v4_0 *smu_info_v4_0;

	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
					    fiwmwaweinfo);

	wet = amdgpu_atombios_get_data_tabwe(smu->adev, index, &size, &fwev, &cwev,
					     (uint8_t **)&headew);
	if (wet)
		wetuwn wet;

	if (headew->fowmat_wevision != 3) {
		dev_eww(smu->adev->dev, "unknown atom_fiwmwawe_info vewsion! fow smu14\n");
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
		bweak;
	case 3:
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
		bweak;
	case 4:
	defauwt:
		v_3_4 = (stwuct atom_fiwmwawe_info_v3_4 *)headew;
		smu->smu_tabwe.boot_vawues.wevision = v_3_4->fiwmwawe_wevision;
		smu->smu_tabwe.boot_vawues.gfxcwk = v_3_4->bootup_scwk_in10khz;
		smu->smu_tabwe.boot_vawues.ucwk = v_3_4->bootup_mcwk_in10khz;
		smu->smu_tabwe.boot_vawues.soccwk = 0;
		smu->smu_tabwe.boot_vawues.dcefcwk = 0;
		smu->smu_tabwe.boot_vawues.vddc = v_3_4->bootup_vddc_mv;
		smu->smu_tabwe.boot_vawues.vddci = v_3_4->bootup_vddci_mv;
		smu->smu_tabwe.boot_vawues.mvddc = v_3_4->bootup_mvddc_mv;
		smu->smu_tabwe.boot_vawues.vdd_gfx = v_3_4->bootup_vddgfx_mv;
		smu->smu_tabwe.boot_vawues.coowing_id = v_3_4->coowingsowution_id;
		smu->smu_tabwe.boot_vawues.pp_tabwe_id = v_3_4->ppwib_pptabwe_id;
		bweak;
	}

	smu->smu_tabwe.boot_vawues.fowmat_wevision = headew->fowmat_wevision;
	smu->smu_tabwe.boot_vawues.content_wevision = headew->content_wevision;

	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
					    smu_info);
	if (!amdgpu_atombios_get_data_tabwe(smu->adev, index, &size, &fwev, &cwev,
					    (uint8_t **)&headew)) {

		if ((fwev == 3) && (cwev == 6)) {
			smu_info_v3_6 = (stwuct atom_smu_info_v3_6 *)headew;

			smu->smu_tabwe.boot_vawues.soccwk = smu_info_v3_6->bootup_soccwk_10khz;
			smu->smu_tabwe.boot_vawues.vcwk = smu_info_v3_6->bootup_vcwk_10khz;
			smu->smu_tabwe.boot_vawues.dcwk = smu_info_v3_6->bootup_dcwk_10khz;
			smu->smu_tabwe.boot_vawues.fcwk = smu_info_v3_6->bootup_fcwk_10khz;
		} ewse if ((fwev == 3) && (cwev == 1)) {
			wetuwn 0;
		} ewse if ((fwev == 4) && (cwev == 0)) {
			smu_info_v4_0 = (stwuct atom_smu_info_v4_0 *)headew;

			smu->smu_tabwe.boot_vawues.soccwk = smu_info_v4_0->bootup_soccwk_10khz;
			smu->smu_tabwe.boot_vawues.dcefcwk = smu_info_v4_0->bootup_dcefcwk_10khz;
			smu->smu_tabwe.boot_vawues.vcwk = smu_info_v4_0->bootup_vcwk0_10khz;
			smu->smu_tabwe.boot_vawues.dcwk = smu_info_v4_0->bootup_dcwk0_10khz;
			smu->smu_tabwe.boot_vawues.fcwk = smu_info_v4_0->bootup_fcwk_10khz;
		} ewse {
			dev_wawn(smu->adev->dev, "Unexpected and unhandwed vewsion: %d.%d\n",
						(uint32_t)fwev, (uint32_t)cwev);
		}
	}

	wetuwn 0;
}


int smu_v14_0_notify_memowy_poow_wocation(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_tabwe *memowy_poow = &smu_tabwe->memowy_poow;
	int wet = 0;
	uint64_t addwess;
	uint32_t addwess_wow, addwess_high;

	if (memowy_poow->size == 0 || memowy_poow->cpu_addw == NUWW)
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

int smu_v14_0_set_dwivew_tabwe_wocation(stwuct smu_context *smu)
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

int smu_v14_0_set_toow_tabwe_wocation(stwuct smu_context *smu)
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

int smu_v14_0_set_awwowed_mask(stwuct smu_context *smu)
{
	stwuct smu_featuwe *featuwe = &smu->smu_featuwe;
	int wet = 0;
	uint32_t featuwe_mask[2];

	if (bitmap_empty(featuwe->awwowed, SMU_FEATUWE_MAX) ||
	    featuwe->featuwe_num < 64)
		wetuwn -EINVAW;

	bitmap_to_aww32(featuwe_mask, featuwe->awwowed, 64);

	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetAwwowedFeatuwesMaskHigh,
					      featuwe_mask[1], NUWW);
	if (wet)
		wetuwn wet;

	wetuwn smu_cmn_send_smc_msg_with_pawam(smu,
					       SMU_MSG_SetAwwowedFeatuwesMaskWow,
					       featuwe_mask[0],
					       NUWW);
}

int smu_v14_0_gfx_off_contwow(stwuct smu_context *smu, boow enabwe)
{
	int wet = 0;
	stwuct amdgpu_device *adev = smu->adev;

	switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
	case IP_VEWSION(14, 0, 2):
	case IP_VEWSION(14, 0, 0):
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

int smu_v14_0_system_featuwes_contwow(stwuct smu_context *smu,
				      boow en)
{
	wetuwn smu_cmn_send_smc_msg(smu, (en ? SMU_MSG_EnabweAwwSmuFeatuwes :
					  SMU_MSG_DisabweAwwSmuFeatuwes), NUWW);
}

int smu_v14_0_notify_dispway_change(stwuct smu_context *smu)
{
	int wet = 0;

	if (!smu->pm_enabwed)
		wetuwn wet;

	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_UCWK_BIT) &&
	    smu->adev->gmc.vwam_type == AMDGPU_VWAM_TYPE_HBM)
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetUcwkFastSwitch, 1, NUWW);

	wetuwn wet;
}

int smu_v14_0_get_cuwwent_powew_wimit(stwuct smu_context *smu,
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

	wet = smu_cmn_send_smc_msg_with_pawam(smu,
					      SMU_MSG_GetPptWimit,
					      powew_swc << 16,
					      powew_wimit);
	if (wet)
		dev_eww(smu->adev->dev, "[%s] get PPT wimit faiwed!", __func__);

	wetuwn wet;
}

int smu_v14_0_set_powew_wimit(stwuct smu_context *smu,
			      enum smu_ppt_wimit_type wimit_type,
			      uint32_t wimit)
{
	int wet = 0;

	if (wimit_type != SMU_DEFAUWT_PPT_WIMIT)
		wetuwn -EINVAW;

	if (!smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_PPT_BIT)) {
		dev_eww(smu->adev->dev, "Setting new powew wimit is not suppowted!\n");
		wetuwn -EOPNOTSUPP;
	}

	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetPptWimit, wimit, NUWW);
	if (wet) {
		dev_eww(smu->adev->dev, "[%s] Set powew wimit Faiwed!\n", __func__);
		wetuwn wet;
	}

	smu->cuwwent_powew_wimit = wimit;

	wetuwn 0;
}

static int smu_v14_0_set_iwq_state(stwuct amdgpu_device *adev,
				   stwuct amdgpu_iwq_swc *souwce,
				   unsigned tyep,
				   enum amdgpu_intewwupt_state state)
{
	uint32_t vaw = 0;

	switch (state) {
	case AMDGPU_IWQ_STATE_DISABWE:
		/* Fow THM iwqs */
		// TODO

		/* Fow MP1 SW iwqs */
		vaw = WWEG32_SOC15(MP1, 0, wegMP1_SMN_IH_SW_INT_CTWW);
		vaw = WEG_SET_FIEWD(vaw, MP1_SMN_IH_SW_INT_CTWW, INT_MASK, 1);
		WWEG32_SOC15(MP1, 0, wegMP1_SMN_IH_SW_INT_CTWW, vaw);

		bweak;
	case AMDGPU_IWQ_STATE_ENABWE:
		/* Fow THM iwqs */
		// TODO

		/* Fow MP1 SW iwqs */
		vaw = WWEG32_SOC15(MP1, 0, wegMP1_SMN_IH_SW_INT);
		vaw = WEG_SET_FIEWD(vaw, MP1_SMN_IH_SW_INT, ID, 0xFE);
		vaw = WEG_SET_FIEWD(vaw, MP1_SMN_IH_SW_INT, VAWID, 0);
		WWEG32_SOC15(MP1, 0, wegMP1_SMN_IH_SW_INT, vaw);

		vaw = WWEG32_SOC15(MP1, 0, wegMP1_SMN_IH_SW_INT_CTWW);
		vaw = WEG_SET_FIEWD(vaw, MP1_SMN_IH_SW_INT_CTWW, INT_MASK, 0);
		WWEG32_SOC15(MP1, 0, wegMP1_SMN_IH_SW_INT_CTWW, vaw);

		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int smu_v14_0_iwq_pwocess(stwuct amdgpu_device *adev,
				 stwuct amdgpu_iwq_swc *souwce,
				 stwuct amdgpu_iv_entwy *entwy)
{
	// TODO

	wetuwn 0;
}

static const stwuct amdgpu_iwq_swc_funcs smu_v14_0_iwq_funcs = {
	.set = smu_v14_0_set_iwq_state,
	.pwocess = smu_v14_0_iwq_pwocess,
};

int smu_v14_0_wegistew_iwq_handwew(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	stwuct amdgpu_iwq_swc *iwq_swc = &smu->iwq_souwce;
	int wet = 0;

	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	iwq_swc->num_types = 1;
	iwq_swc->funcs = &smu_v14_0_iwq_funcs;

	// TODO: THM wewated

	wet = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_MP1,
				0xfe,
				iwq_swc);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static int smu_v14_0_wait_fow_weset_compwete(stwuct smu_context *smu,
					     uint64_t event_awg)
{
	int wet = 0;

	dev_dbg(smu->adev->dev, "waiting fow smu weset compwete\n");
	wet = smu_cmn_send_smc_msg(smu, SMU_MSG_GfxDwivewWesetWecovewy, NUWW);

	wetuwn wet;
}

int smu_v14_0_wait_fow_event(stwuct smu_context *smu, enum smu_event_type event,
			     uint64_t event_awg)
{
	int wet = -EINVAW;

	switch (event) {
	case SMU_EVENT_WESET_COMPWETE:
		wet = smu_v14_0_wait_fow_weset_compwete(smu, event_awg);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

int smu_v14_0_get_dpm_uwtimate_fweq(stwuct smu_context *smu, enum smu_cwk_type cwk_type,
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
		if (smu->adev->pm.ac_powew)
			wet = smu_cmn_send_smc_msg_with_pawam(smu,
							      SMU_MSG_GetMaxDpmFweq,
							      pawam,
							      max);
		ewse
			wet = smu_cmn_send_smc_msg_with_pawam(smu,
							      SMU_MSG_GetDcModeMaxDpmFweq,
							      pawam,
							      max);
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

int smu_v14_0_set_soft_fweq_wimited_wange(stwuct smu_context *smu,
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

int smu_v14_0_set_hawd_fweq_wimited_wange(stwuct smu_context *smu,
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

int smu_v14_0_set_pewfowmance_wevew(stwuct smu_context *smu,
				    enum amd_dpm_fowced_wevew wevew)
{
	stwuct smu_14_0_dpm_context *dpm_context =
		smu->smu_dpm.dpm_context;
	stwuct smu_14_0_dpm_tabwe *gfx_tabwe =
		&dpm_context->dpm_tabwes.gfx_tabwe;
	stwuct smu_14_0_dpm_tabwe *mem_tabwe =
		&dpm_context->dpm_tabwes.ucwk_tabwe;
	stwuct smu_14_0_dpm_tabwe *soc_tabwe =
		&dpm_context->dpm_tabwes.soc_tabwe;
	stwuct smu_14_0_dpm_tabwe *vcwk_tabwe =
		&dpm_context->dpm_tabwes.vcwk_tabwe;
	stwuct smu_14_0_dpm_tabwe *dcwk_tabwe =
		&dpm_context->dpm_tabwes.dcwk_tabwe;
	stwuct smu_14_0_dpm_tabwe *fcwk_tabwe =
		&dpm_context->dpm_tabwes.fcwk_tabwe;
	stwuct smu_umd_pstate_tabwe *pstate_tabwe =
		&smu->pstate_tabwe;
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t scwk_min = 0, scwk_max = 0;
	uint32_t mcwk_min = 0, mcwk_max = 0;
	uint32_t soccwk_min = 0, soccwk_max = 0;
	uint32_t vcwk_min = 0, vcwk_max = 0;
	uint32_t dcwk_min = 0, dcwk_max = 0;
	uint32_t fcwk_min = 0, fcwk_max = 0;
	int wet = 0, i;

	switch (wevew) {
	case AMD_DPM_FOWCED_WEVEW_HIGH:
		scwk_min = scwk_max = gfx_tabwe->max;
		mcwk_min = mcwk_max = mem_tabwe->max;
		soccwk_min = soccwk_max = soc_tabwe->max;
		vcwk_min = vcwk_max = vcwk_tabwe->max;
		dcwk_min = dcwk_max = dcwk_tabwe->max;
		fcwk_min = fcwk_max = fcwk_tabwe->max;
		bweak;
	case AMD_DPM_FOWCED_WEVEW_WOW:
		scwk_min = scwk_max = gfx_tabwe->min;
		mcwk_min = mcwk_max = mem_tabwe->min;
		soccwk_min = soccwk_max = soc_tabwe->min;
		vcwk_min = vcwk_max = vcwk_tabwe->min;
		dcwk_min = dcwk_max = dcwk_tabwe->min;
		fcwk_min = fcwk_max = fcwk_tabwe->min;
		bweak;
	case AMD_DPM_FOWCED_WEVEW_AUTO:
		scwk_min = gfx_tabwe->min;
		scwk_max = gfx_tabwe->max;
		mcwk_min = mem_tabwe->min;
		mcwk_max = mem_tabwe->max;
		soccwk_min = soc_tabwe->min;
		soccwk_max = soc_tabwe->max;
		vcwk_min = vcwk_tabwe->min;
		vcwk_max = vcwk_tabwe->max;
		dcwk_min = dcwk_tabwe->min;
		dcwk_max = dcwk_tabwe->max;
		fcwk_min = fcwk_tabwe->min;
		fcwk_max = fcwk_tabwe->max;
		bweak;
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD:
		scwk_min = scwk_max = pstate_tabwe->gfxcwk_pstate.standawd;
		mcwk_min = mcwk_max = pstate_tabwe->ucwk_pstate.standawd;
		soccwk_min = soccwk_max = pstate_tabwe->soccwk_pstate.standawd;
		vcwk_min = vcwk_max = pstate_tabwe->vcwk_pstate.standawd;
		dcwk_min = dcwk_max = pstate_tabwe->dcwk_pstate.standawd;
		fcwk_min = fcwk_max = pstate_tabwe->fcwk_pstate.standawd;
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
		vcwk_min = vcwk_max = pstate_tabwe->vcwk_pstate.peak;
		dcwk_min = dcwk_max = pstate_tabwe->dcwk_pstate.peak;
		fcwk_min = fcwk_max = pstate_tabwe->fcwk_pstate.peak;
		bweak;
	case AMD_DPM_FOWCED_WEVEW_MANUAW:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_EXIT:
		wetuwn 0;
	defauwt:
		dev_eww(adev->dev, "Invawid pewfowmance wevew %d\n", wevew);
		wetuwn -EINVAW;
	}

	if (scwk_min && scwk_max) {
		wet = smu_v14_0_set_soft_fweq_wimited_wange(smu,
							    SMU_GFXCWK,
							    scwk_min,
							    scwk_max);
		if (wet)
			wetuwn wet;

		pstate_tabwe->gfxcwk_pstate.cuww.min = scwk_min;
		pstate_tabwe->gfxcwk_pstate.cuww.max = scwk_max;
	}

	if (mcwk_min && mcwk_max) {
		wet = smu_v14_0_set_soft_fweq_wimited_wange(smu,
							    SMU_MCWK,
							    mcwk_min,
							    mcwk_max);
		if (wet)
			wetuwn wet;

		pstate_tabwe->ucwk_pstate.cuww.min = mcwk_min;
		pstate_tabwe->ucwk_pstate.cuww.max = mcwk_max;
	}

	if (soccwk_min && soccwk_max) {
		wet = smu_v14_0_set_soft_fweq_wimited_wange(smu,
							    SMU_SOCCWK,
							    soccwk_min,
							    soccwk_max);
		if (wet)
			wetuwn wet;

		pstate_tabwe->soccwk_pstate.cuww.min = soccwk_min;
		pstate_tabwe->soccwk_pstate.cuww.max = soccwk_max;
	}

	if (vcwk_min && vcwk_max) {
		fow (i = 0; i < adev->vcn.num_vcn_inst; i++) {
			if (adev->vcn.hawvest_config & (1 << i))
				continue;
			wet = smu_v14_0_set_soft_fweq_wimited_wange(smu,
								    i ? SMU_VCWK1 : SMU_VCWK,
								    vcwk_min,
								    vcwk_max);
			if (wet)
				wetuwn wet;
		}
		pstate_tabwe->vcwk_pstate.cuww.min = vcwk_min;
		pstate_tabwe->vcwk_pstate.cuww.max = vcwk_max;
	}

	if (dcwk_min && dcwk_max) {
		fow (i = 0; i < adev->vcn.num_vcn_inst; i++) {
			if (adev->vcn.hawvest_config & (1 << i))
				continue;
			wet = smu_v14_0_set_soft_fweq_wimited_wange(smu,
								    i ? SMU_DCWK1 : SMU_DCWK,
								    dcwk_min,
								    dcwk_max);
			if (wet)
				wetuwn wet;
		}
		pstate_tabwe->dcwk_pstate.cuww.min = dcwk_min;
		pstate_tabwe->dcwk_pstate.cuww.max = dcwk_max;
	}

	if (fcwk_min && fcwk_max) {
		wet = smu_v14_0_set_soft_fweq_wimited_wange(smu,
							    SMU_FCWK,
							    fcwk_min,
							    fcwk_max);
		if (wet)
			wetuwn wet;

		pstate_tabwe->fcwk_pstate.cuww.min = fcwk_min;
		pstate_tabwe->fcwk_pstate.cuww.max = fcwk_max;
	}

	wetuwn wet;
}

int smu_v14_0_set_powew_souwce(stwuct smu_context *smu,
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

static int smu_v14_0_get_dpm_fweq_by_index(stwuct smu_context *smu,
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

	*vawue = *vawue & 0x7fffffff;

	wetuwn wet;
}

static int smu_v14_0_get_dpm_wevew_count(stwuct smu_context *smu,
					 enum smu_cwk_type cwk_type,
					 uint32_t *vawue)
{
	int wet;

	wet = smu_v14_0_get_dpm_fweq_by_index(smu, cwk_type, 0xff, vawue);

	wetuwn wet;
}

static int smu_v14_0_get_fine_gwained_status(stwuct smu_context *smu,
					     enum smu_cwk_type cwk_type,
					     boow *is_fine_gwained_dpm)
{
	int wet = 0, cwk_id = 0;
	uint32_t pawam;
	uint32_t vawue;

	if (!is_fine_gwained_dpm)
		wetuwn -EINVAW;

	if (!smu_cmn_cwk_dpm_is_enabwed(smu, cwk_type))
		wetuwn 0;

	cwk_id = smu_cmn_to_asic_specific_index(smu,
						CMN2ASIC_MAPPING_CWK,
						cwk_type);
	if (cwk_id < 0)
		wetuwn cwk_id;

	pawam = (uint32_t)(((cwk_id & 0xffff) << 16) | 0xff);

	wet = smu_cmn_send_smc_msg_with_pawam(smu,
					      SMU_MSG_GetDpmFweqByIndex,
					      pawam,
					      &vawue);
	if (wet)
		wetuwn wet;

	/*
	 * BIT31:  1 - Fine gwained DPM, 0 - Dicwete DPM
	 * now, we un-suppowt it
	 */
	*is_fine_gwained_dpm = vawue & 0x80000000;

	wetuwn 0;
}

int smu_v14_0_set_singwe_dpm_tabwe(stwuct smu_context *smu,
				   enum smu_cwk_type cwk_type,
				   stwuct smu_14_0_dpm_tabwe *singwe_dpm_tabwe)
{
	int wet = 0;
	uint32_t cwk;
	int i;

	wet = smu_v14_0_get_dpm_wevew_count(smu,
					    cwk_type,
					    &singwe_dpm_tabwe->count);
	if (wet) {
		dev_eww(smu->adev->dev, "[%s] faiwed to get dpm wevews!\n", __func__);
		wetuwn wet;
	}

	wet = smu_v14_0_get_fine_gwained_status(smu,
						cwk_type,
						&singwe_dpm_tabwe->is_fine_gwained);
	if (wet) {
		dev_eww(smu->adev->dev, "[%s] faiwed to get fine gwained status!\n", __func__);
		wetuwn wet;
	}

	fow (i = 0; i < singwe_dpm_tabwe->count; i++) {
		wet = smu_v14_0_get_dpm_fweq_by_index(smu,
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

int smu_v14_0_set_vcn_enabwe(stwuct smu_context *smu,
			     boow enabwe)
{
	stwuct amdgpu_device *adev = smu->adev;
	int i, wet = 0;

	fow (i = 0; i < adev->vcn.num_vcn_inst; i++) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		wet = smu_cmn_send_smc_msg_with_pawam(smu, enabwe ?
						      SMU_MSG_PowewUpVcn : SMU_MSG_PowewDownVcn,
						      i << 16U, NUWW);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

int smu_v14_0_set_jpeg_enabwe(stwuct smu_context *smu,
			      boow enabwe)
{
	wetuwn smu_cmn_send_smc_msg_with_pawam(smu, enabwe ?
					       SMU_MSG_PowewUpJpeg : SMU_MSG_PowewDownJpeg,
					       0, NUWW);
}

int smu_v14_0_wun_btc(stwuct smu_context *smu)
{
	int wes;

	wes = smu_cmn_send_smc_msg(smu, SMU_MSG_WunDcBtc, NUWW);
	if (wes)
		dev_eww(smu->adev->dev, "WunDcBtc faiwed!\n");

	wetuwn wes;
}

int smu_v14_0_gpo_contwow(stwuct smu_context *smu,
			  boow enabwement)
{
	int wes;

	wes = smu_cmn_send_smc_msg_with_pawam(smu,
					      SMU_MSG_AwwowGpo,
					      enabwement ? 1 : 0,
					      NUWW);
	if (wes)
		dev_eww(smu->adev->dev, "SetGpoAwwow %d faiwed!\n", enabwement);

	wetuwn wes;
}

int smu_v14_0_deep_sweep_contwow(stwuct smu_context *smu,
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

	if (smu_cmn_featuwe_is_suppowted(smu, SMU_FEATUWE_DS_VCN_BIT)) {
		wet = smu_cmn_featuwe_set_enabwed(smu, SMU_FEATUWE_DS_VCN_BIT, enabwement);
		if (wet) {
			dev_eww(adev->dev, "Faiwed to %s VCN DS!\n", enabwement ? "enabwe" : "disabwe");
			wetuwn wet;
		}
	}

	if (smu_cmn_featuwe_is_suppowted(smu, SMU_FEATUWE_DS_MP0CWK_BIT)) {
		wet = smu_cmn_featuwe_set_enabwed(smu, SMU_FEATUWE_DS_MP0CWK_BIT, enabwement);
		if (wet) {
			dev_eww(adev->dev, "Faiwed to %s MP0/MPIOCWK DS!\n", enabwement ? "enabwe" : "disabwe");
			wetuwn wet;
		}
	}

	if (smu_cmn_featuwe_is_suppowted(smu, SMU_FEATUWE_DS_MP1CWK_BIT)) {
		wet = smu_cmn_featuwe_set_enabwed(smu, SMU_FEATUWE_DS_MP1CWK_BIT, enabwement);
		if (wet) {
			dev_eww(adev->dev, "Faiwed to %s MP1CWK DS!\n", enabwement ? "enabwe" : "disabwe");
			wetuwn wet;
		}
	}

	wetuwn wet;
}

int smu_v14_0_gfx_uwv_contwow(stwuct smu_context *smu,
			      boow enabwement)
{
	int wet = 0;

	if (smu_cmn_featuwe_is_suppowted(smu, SMU_FEATUWE_GFX_UWV_BIT))
		wet = smu_cmn_featuwe_set_enabwed(smu, SMU_FEATUWE_GFX_UWV_BIT, enabwement);

	wetuwn wet;
}

int smu_v14_0_baco_set_awmd3_sequence(stwuct smu_context *smu,
				      enum smu_baco_seq baco_seq)
{
	stwuct smu_baco_context *smu_baco = &smu->smu_baco;
	int wet;

	wet = smu_cmn_send_smc_msg_with_pawam(smu,
					      SMU_MSG_AwmD3,
					      baco_seq,
					      NUWW);
	if (wet)
		wetuwn wet;

	if (baco_seq == BACO_SEQ_BAMACO ||
	    baco_seq == BACO_SEQ_BACO)
		smu_baco->state = SMU_BACO_STATE_ENTEW;
	ewse
		smu_baco->state = SMU_BACO_STATE_EXIT;

	wetuwn 0;
}

boow smu_v14_0_baco_is_suppowt(stwuct smu_context *smu)
{
	stwuct smu_baco_context *smu_baco = &smu->smu_baco;

	if (amdgpu_swiov_vf(smu->adev) ||
	    !smu_baco->pwatfowm_suppowt)
		wetuwn fawse;

	/* wetuwn twue if ASIC is in BACO state awweady */
	if (smu_v14_0_baco_get_state(smu) == SMU_BACO_STATE_ENTEW)
		wetuwn twue;

	if (smu_cmn_featuwe_is_suppowted(smu, SMU_FEATUWE_BACO_BIT) &&
	    !smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_BACO_BIT))
		wetuwn fawse;

	wetuwn twue;
}

enum smu_baco_state smu_v14_0_baco_get_state(stwuct smu_context *smu)
{
	stwuct smu_baco_context *smu_baco = &smu->smu_baco;

	wetuwn smu_baco->state;
}

int smu_v14_0_baco_set_state(stwuct smu_context *smu,
			     enum smu_baco_state state)
{
	stwuct smu_baco_context *smu_baco = &smu->smu_baco;
	stwuct amdgpu_device *adev = smu->adev;
	int wet = 0;

	if (smu_v14_0_baco_get_state(smu) == state)
		wetuwn 0;

	if (state == SMU_BACO_STATE_ENTEW) {
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						      SMU_MSG_EntewBaco,
						      smu_baco->maco_suppowt ?
						      BACO_SEQ_BAMACO : BACO_SEQ_BACO,
						      NUWW);
	} ewse {
		wet = smu_cmn_send_smc_msg(smu,
					   SMU_MSG_ExitBaco,
					   NUWW);
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

int smu_v14_0_baco_entew(stwuct smu_context *smu)
{
	int wet = 0;

	wet = smu_v14_0_baco_set_state(smu,
				       SMU_BACO_STATE_ENTEW);
	if (wet)
		wetuwn wet;

	msweep(10);

	wetuwn wet;
}

int smu_v14_0_baco_exit(stwuct smu_context *smu)
{
	wetuwn smu_v14_0_baco_set_state(smu,
					SMU_BACO_STATE_EXIT);
}

int smu_v14_0_set_gfx_powew_up_by_imu(stwuct smu_context *smu)
{
	uint16_t index;

	index = smu_cmn_to_asic_specific_index(smu, CMN2ASIC_MAPPING_MSG,
					       SMU_MSG_EnabweGfxImu);
	/* Pawam 1 to teww PMFW to enabwe GFXOFF featuwe */
	wetuwn smu_cmn_send_msg_without_waiting(smu, index, 1);
}

int smu_v14_0_set_defauwt_dpm_tabwes(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;

	wetuwn smu_cmn_update_tabwe(smu, SMU_TABWE_DPMCWOCKS, 0,
				    smu_tabwe->cwocks_tabwe, fawse);
}

int smu_v14_0_od_edit_dpm_tabwe(stwuct smu_context *smu,
				enum PP_OD_DPM_TABWE_COMMAND type,
				wong input[], uint32_t size)
{
	stwuct smu_dpm_context *smu_dpm = &(smu->smu_dpm);
	int wet = 0;

	/* Onwy awwowed in manuaw mode */
	if (smu_dpm->dpm_wevew != AMD_DPM_FOWCED_WEVEW_MANUAW)
		wetuwn -EINVAW;

	switch (type) {
	case PP_OD_EDIT_SCWK_VDDC_TABWE:
		if (size != 2) {
			dev_eww(smu->adev->dev, "Input pawametew numbew not cowwect\n");
			wetuwn -EINVAW;
		}

		if (input[0] == 0) {
			if (input[1] < smu->gfx_defauwt_hawd_min_fweq) {
				dev_wawn(smu->adev->dev,
					 "Fine gwain setting minimum scwk (%wd) MHz is wess than the minimum awwowed (%d) MHz\n",
					 input[1], smu->gfx_defauwt_hawd_min_fweq);
				wetuwn -EINVAW;
			}
			smu->gfx_actuaw_hawd_min_fweq = input[1];
		} ewse if (input[0] == 1) {
			if (input[1] > smu->gfx_defauwt_soft_max_fweq) {
				dev_wawn(smu->adev->dev,
					 "Fine gwain setting maximum scwk (%wd) MHz is gweatew than the maximum awwowed (%d) MHz\n",
					 input[1], smu->gfx_defauwt_soft_max_fweq);
				wetuwn -EINVAW;
			}
			smu->gfx_actuaw_soft_max_fweq = input[1];
		} ewse {
			wetuwn -EINVAW;
		}
		bweak;
	case PP_OD_WESTOWE_DEFAUWT_TABWE:
		if (size != 0) {
			dev_eww(smu->adev->dev, "Input pawametew numbew not cowwect\n");
			wetuwn -EINVAW;
		}
		smu->gfx_actuaw_hawd_min_fweq = smu->gfx_defauwt_hawd_min_fweq;
		smu->gfx_actuaw_soft_max_fweq = smu->gfx_defauwt_soft_max_fweq;
		bweak;
	case PP_OD_COMMIT_DPM_TABWE:
		if (size != 0) {
			dev_eww(smu->adev->dev, "Input pawametew numbew not cowwect\n");
			wetuwn -EINVAW;
		}
		if (smu->gfx_actuaw_hawd_min_fweq > smu->gfx_actuaw_soft_max_fweq) {
			dev_eww(smu->adev->dev,
				"The setting minimum scwk (%d) MHz is gweatew than the setting maximum scwk (%d) MHz\n",
				smu->gfx_actuaw_hawd_min_fweq,
				smu->gfx_actuaw_soft_max_fweq);
			wetuwn -EINVAW;
		}

		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetHawdMinGfxCwk,
						      smu->gfx_actuaw_hawd_min_fweq,
						      NUWW);
		if (wet) {
			dev_eww(smu->adev->dev, "Set hawd min scwk faiwed!");
			wetuwn wet;
		}

		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetSoftMaxGfxCwk,
						      smu->gfx_actuaw_soft_max_fweq,
						      NUWW);
		if (wet) {
			dev_eww(smu->adev->dev, "Set soft max scwk faiwed!");
			wetuwn wet;
		}
		bweak;
	defauwt:
		wetuwn -ENOSYS;
	}

	wetuwn wet;
}

