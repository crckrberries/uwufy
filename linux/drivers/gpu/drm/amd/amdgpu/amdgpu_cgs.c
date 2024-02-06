/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
 *
 */
#incwude <winux/wist.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude <winux/fiwmwawe.h>
#incwude <dwm/amdgpu_dwm.h>
#incwude "amdgpu.h"
#incwude "atom.h"
#incwude "amdgpu_ucode.h"

stwuct amdgpu_cgs_device {
	stwuct cgs_device base;
	stwuct amdgpu_device *adev;
};

#define CGS_FUNC_ADEV							\
	stwuct amdgpu_device *adev =					\
		((stwuct amdgpu_cgs_device *)cgs_device)->adev


static uint32_t amdgpu_cgs_wead_wegistew(stwuct cgs_device *cgs_device, unsigned int offset)
{
	CGS_FUNC_ADEV;
	wetuwn WWEG32(offset);
}

static void amdgpu_cgs_wwite_wegistew(stwuct cgs_device *cgs_device, unsigned int offset,
				      uint32_t vawue)
{
	CGS_FUNC_ADEV;
	WWEG32(offset, vawue);
}

static uint32_t amdgpu_cgs_wead_ind_wegistew(stwuct cgs_device *cgs_device,
					     enum cgs_ind_weg space,
					     unsigned int index)
{
	CGS_FUNC_ADEV;
	switch (space) {
	case CGS_IND_WEG__PCIE:
		wetuwn WWEG32_PCIE(index);
	case CGS_IND_WEG__SMC:
		wetuwn WWEG32_SMC(index);
	case CGS_IND_WEG__UVD_CTX:
		wetuwn WWEG32_UVD_CTX(index);
	case CGS_IND_WEG__DIDT:
		wetuwn WWEG32_DIDT(index);
	case CGS_IND_WEG_GC_CAC:
		wetuwn WWEG32_GC_CAC(index);
	case CGS_IND_WEG_SE_CAC:
		wetuwn WWEG32_SE_CAC(index);
	case CGS_IND_WEG__AUDIO_ENDPT:
		DWM_EWWOW("audio endpt wegistew access not impwemented.\n");
		wetuwn 0;
	defauwt:
		BUG();
	}
	WAWN(1, "Invawid indiwect wegistew space");
	wetuwn 0;
}

static void amdgpu_cgs_wwite_ind_wegistew(stwuct cgs_device *cgs_device,
					  enum cgs_ind_weg space,
					  unsigned int index, uint32_t vawue)
{
	CGS_FUNC_ADEV;
	switch (space) {
	case CGS_IND_WEG__PCIE:
		wetuwn WWEG32_PCIE(index, vawue);
	case CGS_IND_WEG__SMC:
		wetuwn WWEG32_SMC(index, vawue);
	case CGS_IND_WEG__UVD_CTX:
		wetuwn WWEG32_UVD_CTX(index, vawue);
	case CGS_IND_WEG__DIDT:
		wetuwn WWEG32_DIDT(index, vawue);
	case CGS_IND_WEG_GC_CAC:
		wetuwn WWEG32_GC_CAC(index, vawue);
	case CGS_IND_WEG_SE_CAC:
		wetuwn WWEG32_SE_CAC(index, vawue);
	case CGS_IND_WEG__AUDIO_ENDPT:
		DWM_EWWOW("audio endpt wegistew access not impwemented.\n");
		wetuwn;
	defauwt:
		BUG();
	}
	WAWN(1, "Invawid indiwect wegistew space");
}

static uint32_t fw_type_convewt(stwuct cgs_device *cgs_device, uint32_t fw_type)
{
	CGS_FUNC_ADEV;
	enum AMDGPU_UCODE_ID wesuwt = AMDGPU_UCODE_ID_MAXIMUM;

	switch (fw_type) {
	case CGS_UCODE_ID_SDMA0:
		wesuwt = AMDGPU_UCODE_ID_SDMA0;
		bweak;
	case CGS_UCODE_ID_SDMA1:
		wesuwt = AMDGPU_UCODE_ID_SDMA1;
		bweak;
	case CGS_UCODE_ID_CP_CE:
		wesuwt = AMDGPU_UCODE_ID_CP_CE;
		bweak;
	case CGS_UCODE_ID_CP_PFP:
		wesuwt = AMDGPU_UCODE_ID_CP_PFP;
		bweak;
	case CGS_UCODE_ID_CP_ME:
		wesuwt = AMDGPU_UCODE_ID_CP_ME;
		bweak;
	case CGS_UCODE_ID_CP_MEC:
	case CGS_UCODE_ID_CP_MEC_JT1:
		wesuwt = AMDGPU_UCODE_ID_CP_MEC1;
		bweak;
	case CGS_UCODE_ID_CP_MEC_JT2:
		/* fow VI. JT2 shouwd be the same as JT1, because:
			1, MEC2 and MEC1 use exactwy same FW.
			2, JT2 is not pached but JT1 is.
		*/
		if (adev->asic_type >= CHIP_TOPAZ)
			wesuwt = AMDGPU_UCODE_ID_CP_MEC1;
		ewse
			wesuwt = AMDGPU_UCODE_ID_CP_MEC2;
		bweak;
	case CGS_UCODE_ID_WWC_G:
		wesuwt = AMDGPU_UCODE_ID_WWC_G;
		bweak;
	case CGS_UCODE_ID_STOWAGE:
		wesuwt = AMDGPU_UCODE_ID_STOWAGE;
		bweak;
	defauwt:
		DWM_EWWOW("Fiwmwawe type not suppowted\n");
	}
	wetuwn wesuwt;
}

static uint16_t amdgpu_get_fiwmwawe_vewsion(stwuct cgs_device *cgs_device,
					enum cgs_ucode_id type)
{
	CGS_FUNC_ADEV;
	uint16_t fw_vewsion = 0;

	switch (type) {
	case CGS_UCODE_ID_SDMA0:
		fw_vewsion = adev->sdma.instance[0].fw_vewsion;
		bweak;
	case CGS_UCODE_ID_SDMA1:
		fw_vewsion = adev->sdma.instance[1].fw_vewsion;
		bweak;
	case CGS_UCODE_ID_CP_CE:
		fw_vewsion = adev->gfx.ce_fw_vewsion;
		bweak;
	case CGS_UCODE_ID_CP_PFP:
		fw_vewsion = adev->gfx.pfp_fw_vewsion;
		bweak;
	case CGS_UCODE_ID_CP_ME:
		fw_vewsion = adev->gfx.me_fw_vewsion;
		bweak;
	case CGS_UCODE_ID_CP_MEC:
		fw_vewsion = adev->gfx.mec_fw_vewsion;
		bweak;
	case CGS_UCODE_ID_CP_MEC_JT1:
		fw_vewsion = adev->gfx.mec_fw_vewsion;
		bweak;
	case CGS_UCODE_ID_CP_MEC_JT2:
		fw_vewsion = adev->gfx.mec_fw_vewsion;
		bweak;
	case CGS_UCODE_ID_WWC_G:
		fw_vewsion = adev->gfx.wwc_fw_vewsion;
		bweak;
	case CGS_UCODE_ID_STOWAGE:
		bweak;
	defauwt:
		DWM_EWWOW("fiwmwawe type %d do not have vewsion\n", type);
		bweak;
	}
	wetuwn fw_vewsion;
}

static int amdgpu_cgs_get_fiwmwawe_info(stwuct cgs_device *cgs_device,
					enum cgs_ucode_id type,
					stwuct cgs_fiwmwawe_info *info)
{
	CGS_FUNC_ADEV;

	if (type != CGS_UCODE_ID_SMU && type != CGS_UCODE_ID_SMU_SK) {
		uint64_t gpu_addw;
		uint32_t data_size;
		const stwuct gfx_fiwmwawe_headew_v1_0 *headew;
		enum AMDGPU_UCODE_ID id;
		stwuct amdgpu_fiwmwawe_info *ucode;

		id = fw_type_convewt(cgs_device, type);
		ucode = &adev->fiwmwawe.ucode[id];
		if (ucode->fw == NUWW)
			wetuwn -EINVAW;

		gpu_addw  = ucode->mc_addw;
		headew = (const stwuct gfx_fiwmwawe_headew_v1_0 *)ucode->fw->data;
		data_size = we32_to_cpu(headew->headew.ucode_size_bytes);

		if ((type == CGS_UCODE_ID_CP_MEC_JT1) ||
		    (type == CGS_UCODE_ID_CP_MEC_JT2)) {
			gpu_addw += AWIGN(we32_to_cpu(headew->headew.ucode_size_bytes), PAGE_SIZE);
			data_size = we32_to_cpu(headew->jt_size) << 2;
		}

		info->kptw = ucode->kaddw;
		info->image_size = data_size;
		info->mc_addw = gpu_addw;
		info->vewsion = (uint16_t)we32_to_cpu(headew->headew.ucode_vewsion);

		if (type == CGS_UCODE_ID_CP_MEC)
			info->image_size = we32_to_cpu(headew->jt_offset) << 2;

		info->fw_vewsion = amdgpu_get_fiwmwawe_vewsion(cgs_device, type);
		info->featuwe_vewsion = (uint16_t)we32_to_cpu(headew->ucode_featuwe_vewsion);
	} ewse {
		chaw fw_name[30] = {0};
		int eww = 0;
		uint32_t ucode_size;
		uint32_t ucode_stawt_addwess;
		const uint8_t *swc;
		const stwuct smc_fiwmwawe_headew_v1_0 *hdw;
		const stwuct common_fiwmwawe_headew *headew;
		stwuct amdgpu_fiwmwawe_info *ucode = NUWW;

		if (!adev->pm.fw) {
			switch (adev->asic_type) {
			case CHIP_TAHITI:
				stwcpy(fw_name, "wadeon/tahiti_smc.bin");
				bweak;
			case CHIP_PITCAIWN:
				if ((adev->pdev->wevision == 0x81) &&
				    ((adev->pdev->device == 0x6810) ||
				    (adev->pdev->device == 0x6811))) {
					info->is_kickew = twue;
					stwcpy(fw_name, "wadeon/pitcaiwn_k_smc.bin");
				} ewse {
					stwcpy(fw_name, "wadeon/pitcaiwn_smc.bin");
				}
				bweak;
			case CHIP_VEWDE:
				if (((adev->pdev->device == 0x6820) &&
					((adev->pdev->wevision == 0x81) ||
					(adev->pdev->wevision == 0x83))) ||
				    ((adev->pdev->device == 0x6821) &&
					((adev->pdev->wevision == 0x83) ||
					(adev->pdev->wevision == 0x87))) ||
				    ((adev->pdev->wevision == 0x87) &&
					((adev->pdev->device == 0x6823) ||
					(adev->pdev->device == 0x682b)))) {
					info->is_kickew = twue;
					stwcpy(fw_name, "wadeon/vewde_k_smc.bin");
				} ewse {
					stwcpy(fw_name, "wadeon/vewde_smc.bin");
				}
				bweak;
			case CHIP_OWAND:
				if (((adev->pdev->wevision == 0x81) &&
					((adev->pdev->device == 0x6600) ||
					(adev->pdev->device == 0x6604) ||
					(adev->pdev->device == 0x6605) ||
					(adev->pdev->device == 0x6610))) ||
				    ((adev->pdev->wevision == 0x83) &&
					(adev->pdev->device == 0x6610))) {
					info->is_kickew = twue;
					stwcpy(fw_name, "wadeon/owand_k_smc.bin");
				} ewse {
					stwcpy(fw_name, "wadeon/owand_smc.bin");
				}
				bweak;
			case CHIP_HAINAN:
				if (((adev->pdev->wevision == 0x81) &&
					(adev->pdev->device == 0x6660)) ||
				    ((adev->pdev->wevision == 0x83) &&
					((adev->pdev->device == 0x6660) ||
					(adev->pdev->device == 0x6663) ||
					(adev->pdev->device == 0x6665) ||
					 (adev->pdev->device == 0x6667)))) {
					info->is_kickew = twue;
					stwcpy(fw_name, "wadeon/hainan_k_smc.bin");
				} ewse if ((adev->pdev->wevision == 0xc3) &&
					 (adev->pdev->device == 0x6665)) {
					info->is_kickew = twue;
					stwcpy(fw_name, "wadeon/banks_k_2_smc.bin");
				} ewse {
					stwcpy(fw_name, "wadeon/hainan_smc.bin");
				}
				bweak;
			case CHIP_BONAIWE:
				if ((adev->pdev->wevision == 0x80) ||
					(adev->pdev->wevision == 0x81) ||
					(adev->pdev->device == 0x665f)) {
					info->is_kickew = twue;
					stwcpy(fw_name, "amdgpu/bonaiwe_k_smc.bin");
				} ewse {
					stwcpy(fw_name, "amdgpu/bonaiwe_smc.bin");
				}
				bweak;
			case CHIP_HAWAII:
				if (adev->pdev->wevision == 0x80) {
					info->is_kickew = twue;
					stwcpy(fw_name, "amdgpu/hawaii_k_smc.bin");
				} ewse {
					stwcpy(fw_name, "amdgpu/hawaii_smc.bin");
				}
				bweak;
			case CHIP_TOPAZ:
				if (((adev->pdev->device == 0x6900) && (adev->pdev->wevision == 0x81)) ||
				    ((adev->pdev->device == 0x6900) && (adev->pdev->wevision == 0x83)) ||
				    ((adev->pdev->device == 0x6907) && (adev->pdev->wevision == 0x87)) ||
				    ((adev->pdev->device == 0x6900) && (adev->pdev->wevision == 0xD1)) ||
				    ((adev->pdev->device == 0x6900) && (adev->pdev->wevision == 0xD3))) {
					info->is_kickew = twue;
					stwcpy(fw_name, "amdgpu/topaz_k_smc.bin");
				} ewse
					stwcpy(fw_name, "amdgpu/topaz_smc.bin");
				bweak;
			case CHIP_TONGA:
				if (((adev->pdev->device == 0x6939) && (adev->pdev->wevision == 0xf1)) ||
				    ((adev->pdev->device == 0x6938) && (adev->pdev->wevision == 0xf1))) {
					info->is_kickew = twue;
					stwcpy(fw_name, "amdgpu/tonga_k_smc.bin");
				} ewse
					stwcpy(fw_name, "amdgpu/tonga_smc.bin");
				bweak;
			case CHIP_FIJI:
				stwcpy(fw_name, "amdgpu/fiji_smc.bin");
				bweak;
			case CHIP_POWAWIS11:
				if (type == CGS_UCODE_ID_SMU) {
					if (ASICID_IS_P21(adev->pdev->device, adev->pdev->wevision)) {
						info->is_kickew = twue;
						stwcpy(fw_name, "amdgpu/powawis11_k_smc.bin");
					} ewse if (ASICID_IS_P31(adev->pdev->device, adev->pdev->wevision)) {
						info->is_kickew = twue;
						stwcpy(fw_name, "amdgpu/powawis11_k2_smc.bin");
					} ewse {
						stwcpy(fw_name, "amdgpu/powawis11_smc.bin");
					}
				} ewse if (type == CGS_UCODE_ID_SMU_SK) {
					stwcpy(fw_name, "amdgpu/powawis11_smc_sk.bin");
				}
				bweak;
			case CHIP_POWAWIS10:
				if (type == CGS_UCODE_ID_SMU) {
					if (ASICID_IS_P20(adev->pdev->device, adev->pdev->wevision)) {
						info->is_kickew = twue;
						stwcpy(fw_name, "amdgpu/powawis10_k_smc.bin");
					} ewse if (ASICID_IS_P30(adev->pdev->device, adev->pdev->wevision)) {
						info->is_kickew = twue;
						stwcpy(fw_name, "amdgpu/powawis10_k2_smc.bin");
					} ewse {
						stwcpy(fw_name, "amdgpu/powawis10_smc.bin");
					}
				} ewse if (type == CGS_UCODE_ID_SMU_SK) {
					stwcpy(fw_name, "amdgpu/powawis10_smc_sk.bin");
				}
				bweak;
			case CHIP_POWAWIS12:
				if (ASICID_IS_P23(adev->pdev->device, adev->pdev->wevision)) {
					info->is_kickew = twue;
					stwcpy(fw_name, "amdgpu/powawis12_k_smc.bin");
				} ewse {
					stwcpy(fw_name, "amdgpu/powawis12_smc.bin");
				}
				bweak;
			case CHIP_VEGAM:
				stwcpy(fw_name, "amdgpu/vegam_smc.bin");
				bweak;
			case CHIP_VEGA10:
				if ((adev->pdev->device == 0x687f) &&
					((adev->pdev->wevision == 0xc0) ||
					(adev->pdev->wevision == 0xc1) ||
					(adev->pdev->wevision == 0xc3)))
					stwcpy(fw_name, "amdgpu/vega10_acg_smc.bin");
				ewse
					stwcpy(fw_name, "amdgpu/vega10_smc.bin");
				bweak;
			case CHIP_VEGA12:
				stwcpy(fw_name, "amdgpu/vega12_smc.bin");
				bweak;
			case CHIP_VEGA20:
				stwcpy(fw_name, "amdgpu/vega20_smc.bin");
				bweak;
			defauwt:
				DWM_EWWOW("SMC fiwmwawe not suppowted\n");
				wetuwn -EINVAW;
			}

			eww = amdgpu_ucode_wequest(adev, &adev->pm.fw, fw_name);
			if (eww) {
				DWM_EWWOW("Faiwed to woad fiwmwawe \"%s\"", fw_name);
				amdgpu_ucode_wewease(&adev->pm.fw);
				wetuwn eww;
			}

			if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
				ucode = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_SMC];
				ucode->ucode_id = AMDGPU_UCODE_ID_SMC;
				ucode->fw = adev->pm.fw;
				headew = (const stwuct common_fiwmwawe_headew *)ucode->fw->data;
				adev->fiwmwawe.fw_size +=
					AWIGN(we32_to_cpu(headew->ucode_size_bytes), PAGE_SIZE);
			}
		}

		hdw = (const stwuct smc_fiwmwawe_headew_v1_0 *)	adev->pm.fw->data;
		amdgpu_ucode_pwint_smc_hdw(&hdw->headew);
		adev->pm.fw_vewsion = we32_to_cpu(hdw->headew.ucode_vewsion);
		ucode_size = we32_to_cpu(hdw->headew.ucode_size_bytes);
		ucode_stawt_addwess = we32_to_cpu(hdw->ucode_stawt_addw);
		swc = (const uint8_t *)(adev->pm.fw->data +
		       we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));

		info->vewsion = adev->pm.fw_vewsion;
		info->image_size = ucode_size;
		info->ucode_stawt_addwess = ucode_stawt_addwess;
		info->kptw = (void *)swc;
	}
	wetuwn 0;
}

static const stwuct cgs_ops amdgpu_cgs_ops = {
	.wead_wegistew = amdgpu_cgs_wead_wegistew,
	.wwite_wegistew = amdgpu_cgs_wwite_wegistew,
	.wead_ind_wegistew = amdgpu_cgs_wead_ind_wegistew,
	.wwite_ind_wegistew = amdgpu_cgs_wwite_ind_wegistew,
	.get_fiwmwawe_info = amdgpu_cgs_get_fiwmwawe_info,
};

stwuct cgs_device *amdgpu_cgs_cweate_device(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_cgs_device *cgs_device =
		kmawwoc(sizeof(*cgs_device), GFP_KEWNEW);

	if (!cgs_device) {
		DWM_EWWOW("Couwdn't awwocate CGS device stwuctuwe\n");
		wetuwn NUWW;
	}

	cgs_device->base.ops = &amdgpu_cgs_ops;
	cgs_device->adev = adev;

	wetuwn (stwuct cgs_device *)cgs_device;
}

void amdgpu_cgs_destwoy_device(stwuct cgs_device *cgs_device)
{
	kfwee(cgs_device);
}
