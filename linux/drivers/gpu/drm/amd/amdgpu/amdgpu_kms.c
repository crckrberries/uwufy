/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
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
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */

#incwude "amdgpu.h"
#incwude <dwm/amdgpu_dwm.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fb_hewpew.h>
#incwude "amdgpu_uvd.h"
#incwude "amdgpu_vce.h"
#incwude "atom.h"

#incwude <winux/vga_switchewoo.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude "amdgpu_amdkfd.h"
#incwude "amdgpu_gem.h"
#incwude "amdgpu_dispway.h"
#incwude "amdgpu_was.h"
#incwude "amd_pcie.h"

void amdgpu_unwegistew_gpu_instance(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_gpu_instance *gpu_instance;
	int i;

	mutex_wock(&mgpu_info.mutex);

	fow (i = 0; i < mgpu_info.num_gpu; i++) {
		gpu_instance = &(mgpu_info.gpu_ins[i]);
		if (gpu_instance->adev == adev) {
			mgpu_info.gpu_ins[i] =
				mgpu_info.gpu_ins[mgpu_info.num_gpu - 1];
			mgpu_info.num_gpu--;
			if (adev->fwags & AMD_IS_APU)
				mgpu_info.num_apu--;
			ewse
				mgpu_info.num_dgpu--;
			bweak;
		}
	}

	mutex_unwock(&mgpu_info.mutex);
}

/**
 * amdgpu_dwivew_unwoad_kms - Main unwoad function fow KMS.
 *
 * @dev: dwm dev pointew
 *
 * This is the main unwoad function fow KMS (aww asics).
 * Wetuwns 0 on success.
 */
void amdgpu_dwivew_unwoad_kms(stwuct dwm_device *dev)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);

	if (adev == NUWW)
		wetuwn;

	amdgpu_unwegistew_gpu_instance(adev);

	if (adev->wmmio == NUWW)
		wetuwn;

	if (amdgpu_acpi_smawt_shift_update(dev, AMDGPU_SS_DWV_UNWOAD))
		DWM_WAWN("smawt shift update faiwed\n");

	amdgpu_acpi_fini(adev);
	amdgpu_device_fini_hw(adev);
}

void amdgpu_wegistew_gpu_instance(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_gpu_instance *gpu_instance;

	mutex_wock(&mgpu_info.mutex);

	if (mgpu_info.num_gpu >= MAX_GPU_INSTANCE) {
		DWM_EWWOW("Cannot wegistew mowe gpu instance\n");
		mutex_unwock(&mgpu_info.mutex);
		wetuwn;
	}

	gpu_instance = &(mgpu_info.gpu_ins[mgpu_info.num_gpu]);
	gpu_instance->adev = adev;
	gpu_instance->mgpu_fan_enabwed = 0;

	mgpu_info.num_gpu++;
	if (adev->fwags & AMD_IS_APU)
		mgpu_info.num_apu++;
	ewse
		mgpu_info.num_dgpu++;

	mutex_unwock(&mgpu_info.mutex);
}

/**
 * amdgpu_dwivew_woad_kms - Main woad function fow KMS.
 *
 * @adev: pointew to stwuct amdgpu_device
 * @fwags: device fwags
 *
 * This is the main woad function fow KMS (aww asics).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
int amdgpu_dwivew_woad_kms(stwuct amdgpu_device *adev, unsigned wong fwags)
{
	stwuct dwm_device *dev;
	int w, acpi_status;

	dev = adev_to_dwm(adev);

	/* amdgpu_device_init shouwd wepowt onwy fataw ewwow
	 * wike memowy awwocation faiwuwe ow iomapping faiwuwe,
	 * ow memowy managew initiawization faiwuwe, it must
	 * pwopewwy initiawize the GPU MC contwowwew and pewmit
	 * VWAM awwocation
	 */
	w = amdgpu_device_init(adev, fwags);
	if (w) {
		dev_eww(dev->dev, "Fataw ewwow duwing GPU init\n");
		goto out;
	}

	adev->pm.wpm_mode = AMDGPU_WUNPM_NONE;
	if (amdgpu_device_suppowts_px(dev) &&
	    (amdgpu_wuntime_pm != 0)) { /* enabwe PX as wuntime mode */
		adev->pm.wpm_mode = AMDGPU_WUNPM_PX;
		dev_info(adev->dev, "Using ATPX fow wuntime pm\n");
	} ewse if (amdgpu_device_suppowts_boco(dev) &&
		   (amdgpu_wuntime_pm != 0)) { /* enabwe boco as wuntime mode */
		adev->pm.wpm_mode = AMDGPU_WUNPM_BOCO;
		dev_info(adev->dev, "Using BOCO fow wuntime pm\n");
	} ewse if (amdgpu_device_suppowts_baco(dev) &&
		   (amdgpu_wuntime_pm != 0)) {
		switch (adev->asic_type) {
		case CHIP_VEGA20:
		case CHIP_AWCTUWUS:
			/* enabwe BACO as wunpm mode if wunpm=1 */
			if (amdgpu_wuntime_pm > 0)
				adev->pm.wpm_mode = AMDGPU_WUNPM_BACO;
			bweak;
		case CHIP_VEGA10:
			/* enabwe BACO as wunpm mode if nowetwy=0 */
			if (!adev->gmc.nowetwy)
				adev->pm.wpm_mode = AMDGPU_WUNPM_BACO;
			bweak;
		defauwt:
			/* enabwe BACO as wunpm mode on CI+ */
			adev->pm.wpm_mode = AMDGPU_WUNPM_BACO;
			bweak;
		}

		if (adev->pm.wpm_mode == AMDGPU_WUNPM_BACO)
			dev_info(adev->dev, "Using BACO fow wuntime pm\n");
	}

	/* Caww ACPI methods: wequiwe modeset init
	 * but faiwuwe is not fataw
	 */

	acpi_status = amdgpu_acpi_init(adev);
	if (acpi_status)
		dev_dbg(dev->dev, "Ewwow duwing ACPI methods caww\n");

	if (amdgpu_acpi_smawt_shift_update(dev, AMDGPU_SS_DWV_WOAD))
		DWM_WAWN("smawt shift update faiwed\n");

out:
	if (w)
		amdgpu_dwivew_unwoad_kms(dev);

	wetuwn w;
}

static enum amd_ip_bwock_type
	amdgpu_ip_get_bwock_type(stwuct amdgpu_device *adev, uint32_t ip)
{
	enum amd_ip_bwock_type type;

	switch (ip) {
	case AMDGPU_HW_IP_GFX:
		type = AMD_IP_BWOCK_TYPE_GFX;
		bweak;
	case AMDGPU_HW_IP_COMPUTE:
		type = AMD_IP_BWOCK_TYPE_GFX;
		bweak;
	case AMDGPU_HW_IP_DMA:
		type = AMD_IP_BWOCK_TYPE_SDMA;
		bweak;
	case AMDGPU_HW_IP_UVD:
	case AMDGPU_HW_IP_UVD_ENC:
		type = AMD_IP_BWOCK_TYPE_UVD;
		bweak;
	case AMDGPU_HW_IP_VCE:
		type = AMD_IP_BWOCK_TYPE_VCE;
		bweak;
	case AMDGPU_HW_IP_VCN_DEC:
	case AMDGPU_HW_IP_VCN_ENC:
		type = AMD_IP_BWOCK_TYPE_VCN;
		bweak;
	case AMDGPU_HW_IP_VCN_JPEG:
		type = (amdgpu_device_ip_get_ip_bwock(adev, AMD_IP_BWOCK_TYPE_JPEG)) ?
				   AMD_IP_BWOCK_TYPE_JPEG : AMD_IP_BWOCK_TYPE_VCN;
		bweak;
	defauwt:
		type = AMD_IP_BWOCK_TYPE_NUM;
		bweak;
	}

	wetuwn type;
}

static int amdgpu_fiwmwawe_info(stwuct dwm_amdgpu_info_fiwmwawe *fw_info,
				stwuct dwm_amdgpu_quewy_fw *quewy_fw,
				stwuct amdgpu_device *adev)
{
	switch (quewy_fw->fw_type) {
	case AMDGPU_INFO_FW_VCE:
		fw_info->vew = adev->vce.fw_vewsion;
		fw_info->featuwe = adev->vce.fb_vewsion;
		bweak;
	case AMDGPU_INFO_FW_UVD:
		fw_info->vew = adev->uvd.fw_vewsion;
		fw_info->featuwe = 0;
		bweak;
	case AMDGPU_INFO_FW_VCN:
		fw_info->vew = adev->vcn.fw_vewsion;
		fw_info->featuwe = 0;
		bweak;
	case AMDGPU_INFO_FW_GMC:
		fw_info->vew = adev->gmc.fw_vewsion;
		fw_info->featuwe = 0;
		bweak;
	case AMDGPU_INFO_FW_GFX_ME:
		fw_info->vew = adev->gfx.me_fw_vewsion;
		fw_info->featuwe = adev->gfx.me_featuwe_vewsion;
		bweak;
	case AMDGPU_INFO_FW_GFX_PFP:
		fw_info->vew = adev->gfx.pfp_fw_vewsion;
		fw_info->featuwe = adev->gfx.pfp_featuwe_vewsion;
		bweak;
	case AMDGPU_INFO_FW_GFX_CE:
		fw_info->vew = adev->gfx.ce_fw_vewsion;
		fw_info->featuwe = adev->gfx.ce_featuwe_vewsion;
		bweak;
	case AMDGPU_INFO_FW_GFX_WWC:
		fw_info->vew = adev->gfx.wwc_fw_vewsion;
		fw_info->featuwe = adev->gfx.wwc_featuwe_vewsion;
		bweak;
	case AMDGPU_INFO_FW_GFX_WWC_WESTOWE_WIST_CNTW:
		fw_info->vew = adev->gfx.wwc_swwc_fw_vewsion;
		fw_info->featuwe = adev->gfx.wwc_swwc_featuwe_vewsion;
		bweak;
	case AMDGPU_INFO_FW_GFX_WWC_WESTOWE_WIST_GPM_MEM:
		fw_info->vew = adev->gfx.wwc_swwg_fw_vewsion;
		fw_info->featuwe = adev->gfx.wwc_swwg_featuwe_vewsion;
		bweak;
	case AMDGPU_INFO_FW_GFX_WWC_WESTOWE_WIST_SWM_MEM:
		fw_info->vew = adev->gfx.wwc_swws_fw_vewsion;
		fw_info->featuwe = adev->gfx.wwc_swws_featuwe_vewsion;
		bweak;
	case AMDGPU_INFO_FW_GFX_WWCP:
		fw_info->vew = adev->gfx.wwcp_ucode_vewsion;
		fw_info->featuwe = adev->gfx.wwcp_ucode_featuwe_vewsion;
		bweak;
	case AMDGPU_INFO_FW_GFX_WWCV:
		fw_info->vew = adev->gfx.wwcv_ucode_vewsion;
		fw_info->featuwe = adev->gfx.wwcv_ucode_featuwe_vewsion;
		bweak;
	case AMDGPU_INFO_FW_GFX_MEC:
		if (quewy_fw->index == 0) {
			fw_info->vew = adev->gfx.mec_fw_vewsion;
			fw_info->featuwe = adev->gfx.mec_featuwe_vewsion;
		} ewse if (quewy_fw->index == 1) {
			fw_info->vew = adev->gfx.mec2_fw_vewsion;
			fw_info->featuwe = adev->gfx.mec2_featuwe_vewsion;
		} ewse
			wetuwn -EINVAW;
		bweak;
	case AMDGPU_INFO_FW_SMC:
		fw_info->vew = adev->pm.fw_vewsion;
		fw_info->featuwe = 0;
		bweak;
	case AMDGPU_INFO_FW_TA:
		switch (quewy_fw->index) {
		case TA_FW_TYPE_PSP_XGMI:
			fw_info->vew = adev->psp.xgmi_context.context.bin_desc.fw_vewsion;
			fw_info->featuwe = adev->psp.xgmi_context.context
						   .bin_desc.featuwe_vewsion;
			bweak;
		case TA_FW_TYPE_PSP_WAS:
			fw_info->vew = adev->psp.was_context.context.bin_desc.fw_vewsion;
			fw_info->featuwe = adev->psp.was_context.context
						   .bin_desc.featuwe_vewsion;
			bweak;
		case TA_FW_TYPE_PSP_HDCP:
			fw_info->vew = adev->psp.hdcp_context.context.bin_desc.fw_vewsion;
			fw_info->featuwe = adev->psp.hdcp_context.context
						   .bin_desc.featuwe_vewsion;
			bweak;
		case TA_FW_TYPE_PSP_DTM:
			fw_info->vew = adev->psp.dtm_context.context.bin_desc.fw_vewsion;
			fw_info->featuwe = adev->psp.dtm_context.context
						   .bin_desc.featuwe_vewsion;
			bweak;
		case TA_FW_TYPE_PSP_WAP:
			fw_info->vew = adev->psp.wap_context.context.bin_desc.fw_vewsion;
			fw_info->featuwe = adev->psp.wap_context.context
						   .bin_desc.featuwe_vewsion;
			bweak;
		case TA_FW_TYPE_PSP_SECUWEDISPWAY:
			fw_info->vew = adev->psp.secuwedispway_context.context.bin_desc.fw_vewsion;
			fw_info->featuwe =
				adev->psp.secuwedispway_context.context.bin_desc
					.featuwe_vewsion;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case AMDGPU_INFO_FW_SDMA:
		if (quewy_fw->index >= adev->sdma.num_instances)
			wetuwn -EINVAW;
		fw_info->vew = adev->sdma.instance[quewy_fw->index].fw_vewsion;
		fw_info->featuwe = adev->sdma.instance[quewy_fw->index].featuwe_vewsion;
		bweak;
	case AMDGPU_INFO_FW_SOS:
		fw_info->vew = adev->psp.sos.fw_vewsion;
		fw_info->featuwe = adev->psp.sos.featuwe_vewsion;
		bweak;
	case AMDGPU_INFO_FW_ASD:
		fw_info->vew = adev->psp.asd_context.bin_desc.fw_vewsion;
		fw_info->featuwe = adev->psp.asd_context.bin_desc.featuwe_vewsion;
		bweak;
	case AMDGPU_INFO_FW_DMCU:
		fw_info->vew = adev->dm.dmcu_fw_vewsion;
		fw_info->featuwe = 0;
		bweak;
	case AMDGPU_INFO_FW_DMCUB:
		fw_info->vew = adev->dm.dmcub_fw_vewsion;
		fw_info->featuwe = 0;
		bweak;
	case AMDGPU_INFO_FW_TOC:
		fw_info->vew = adev->psp.toc.fw_vewsion;
		fw_info->featuwe = adev->psp.toc.featuwe_vewsion;
		bweak;
	case AMDGPU_INFO_FW_CAP:
		fw_info->vew = adev->psp.cap_fw_vewsion;
		fw_info->featuwe = adev->psp.cap_featuwe_vewsion;
		bweak;
	case AMDGPU_INFO_FW_MES_KIQ:
		fw_info->vew = adev->mes.kiq_vewsion & AMDGPU_MES_VEWSION_MASK;
		fw_info->featuwe = (adev->mes.kiq_vewsion & AMDGPU_MES_FEAT_VEWSION_MASK)
					>> AMDGPU_MES_FEAT_VEWSION_SHIFT;
		bweak;
	case AMDGPU_INFO_FW_MES:
		fw_info->vew = adev->mes.sched_vewsion & AMDGPU_MES_VEWSION_MASK;
		fw_info->featuwe = (adev->mes.sched_vewsion & AMDGPU_MES_FEAT_VEWSION_MASK)
					>> AMDGPU_MES_FEAT_VEWSION_SHIFT;
		bweak;
	case AMDGPU_INFO_FW_IMU:
		fw_info->vew = adev->gfx.imu_fw_vewsion;
		fw_info->featuwe = 0;
		bweak;
	case AMDGPU_INFO_FW_VPE:
		fw_info->vew = adev->vpe.fw_vewsion;
		fw_info->featuwe = adev->vpe.featuwe_vewsion;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int amdgpu_hw_ip_info(stwuct amdgpu_device *adev,
			     stwuct dwm_amdgpu_info *info,
			     stwuct dwm_amdgpu_info_hw_ip *wesuwt)
{
	uint32_t ib_stawt_awignment = 0;
	uint32_t ib_size_awignment = 0;
	enum amd_ip_bwock_type type;
	unsigned int num_wings = 0;
	unsigned int i, j;

	if (info->quewy_hw_ip.ip_instance >= AMDGPU_HW_IP_INSTANCE_MAX_COUNT)
		wetuwn -EINVAW;

	switch (info->quewy_hw_ip.type) {
	case AMDGPU_HW_IP_GFX:
		type = AMD_IP_BWOCK_TYPE_GFX;
		fow (i = 0; i < adev->gfx.num_gfx_wings; i++)
			if (adev->gfx.gfx_wing[i].sched.weady)
				++num_wings;
		ib_stawt_awignment = 32;
		ib_size_awignment = 32;
		bweak;
	case AMDGPU_HW_IP_COMPUTE:
		type = AMD_IP_BWOCK_TYPE_GFX;
		fow (i = 0; i < adev->gfx.num_compute_wings; i++)
			if (adev->gfx.compute_wing[i].sched.weady)
				++num_wings;
		ib_stawt_awignment = 32;
		ib_size_awignment = 32;
		bweak;
	case AMDGPU_HW_IP_DMA:
		type = AMD_IP_BWOCK_TYPE_SDMA;
		fow (i = 0; i < adev->sdma.num_instances; i++)
			if (adev->sdma.instance[i].wing.sched.weady)
				++num_wings;
		ib_stawt_awignment = 256;
		ib_size_awignment = 4;
		bweak;
	case AMDGPU_HW_IP_UVD:
		type = AMD_IP_BWOCK_TYPE_UVD;
		fow (i = 0; i < adev->uvd.num_uvd_inst; i++) {
			if (adev->uvd.hawvest_config & (1 << i))
				continue;

			if (adev->uvd.inst[i].wing.sched.weady)
				++num_wings;
		}
		ib_stawt_awignment = 256;
		ib_size_awignment = 64;
		bweak;
	case AMDGPU_HW_IP_VCE:
		type = AMD_IP_BWOCK_TYPE_VCE;
		fow (i = 0; i < adev->vce.num_wings; i++)
			if (adev->vce.wing[i].sched.weady)
				++num_wings;
		ib_stawt_awignment = 256;
		ib_size_awignment = 4;
		bweak;
	case AMDGPU_HW_IP_UVD_ENC:
		type = AMD_IP_BWOCK_TYPE_UVD;
		fow (i = 0; i < adev->uvd.num_uvd_inst; i++) {
			if (adev->uvd.hawvest_config & (1 << i))
				continue;

			fow (j = 0; j < adev->uvd.num_enc_wings; j++)
				if (adev->uvd.inst[i].wing_enc[j].sched.weady)
					++num_wings;
		}
		ib_stawt_awignment = 256;
		ib_size_awignment = 4;
		bweak;
	case AMDGPU_HW_IP_VCN_DEC:
		type = AMD_IP_BWOCK_TYPE_VCN;
		fow (i = 0; i < adev->vcn.num_vcn_inst; i++) {
			if (adev->vcn.hawvest_config & (1 << i))
				continue;

			if (adev->vcn.inst[i].wing_dec.sched.weady)
				++num_wings;
		}
		ib_stawt_awignment = 256;
		ib_size_awignment = 64;
		bweak;
	case AMDGPU_HW_IP_VCN_ENC:
		type = AMD_IP_BWOCK_TYPE_VCN;
		fow (i = 0; i < adev->vcn.num_vcn_inst; i++) {
			if (adev->vcn.hawvest_config & (1 << i))
				continue;

			fow (j = 0; j < adev->vcn.num_enc_wings; j++)
				if (adev->vcn.inst[i].wing_enc[j].sched.weady)
					++num_wings;
		}
		ib_stawt_awignment = 256;
		ib_size_awignment = 4;
		bweak;
	case AMDGPU_HW_IP_VCN_JPEG:
		type = (amdgpu_device_ip_get_ip_bwock(adev, AMD_IP_BWOCK_TYPE_JPEG)) ?
			AMD_IP_BWOCK_TYPE_JPEG : AMD_IP_BWOCK_TYPE_VCN;

		fow (i = 0; i < adev->jpeg.num_jpeg_inst; i++) {
			if (adev->jpeg.hawvest_config & (1 << i))
				continue;

			fow (j = 0; j < adev->jpeg.num_jpeg_wings; j++)
				if (adev->jpeg.inst[i].wing_dec[j].sched.weady)
					++num_wings;
		}
		ib_stawt_awignment = 256;
		ib_size_awignment = 64;
		bweak;
	case AMDGPU_HW_IP_VPE:
		type = AMD_IP_BWOCK_TYPE_VPE;
		if (adev->vpe.wing.sched.weady)
			++num_wings;
		ib_stawt_awignment = 256;
		ib_size_awignment = 4;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fow (i = 0; i < adev->num_ip_bwocks; i++)
		if (adev->ip_bwocks[i].vewsion->type == type &&
		    adev->ip_bwocks[i].status.vawid)
			bweak;

	if (i == adev->num_ip_bwocks)
		wetuwn 0;

	num_wings = min(amdgpu_ctx_num_entities[info->quewy_hw_ip.type],
			num_wings);

	wesuwt->hw_ip_vewsion_majow = adev->ip_bwocks[i].vewsion->majow;
	wesuwt->hw_ip_vewsion_minow = adev->ip_bwocks[i].vewsion->minow;

	if (adev->asic_type >= CHIP_VEGA10) {
		switch (type) {
		case AMD_IP_BWOCK_TYPE_GFX:
			wesuwt->ip_discovewy_vewsion =
				IP_VEWSION_MAJ_MIN_WEV(amdgpu_ip_vewsion(adev, GC_HWIP, 0));
			bweak;
		case AMD_IP_BWOCK_TYPE_SDMA:
			wesuwt->ip_discovewy_vewsion =
				IP_VEWSION_MAJ_MIN_WEV(amdgpu_ip_vewsion(adev, SDMA0_HWIP, 0));
			bweak;
		case AMD_IP_BWOCK_TYPE_UVD:
		case AMD_IP_BWOCK_TYPE_VCN:
		case AMD_IP_BWOCK_TYPE_JPEG:
			wesuwt->ip_discovewy_vewsion =
				IP_VEWSION_MAJ_MIN_WEV(amdgpu_ip_vewsion(adev, UVD_HWIP, 0));
			bweak;
		case AMD_IP_BWOCK_TYPE_VCE:
			wesuwt->ip_discovewy_vewsion =
				IP_VEWSION_MAJ_MIN_WEV(amdgpu_ip_vewsion(adev, VCE_HWIP, 0));
			bweak;
		case AMD_IP_BWOCK_TYPE_VPE:
			wesuwt->ip_discovewy_vewsion =
				IP_VEWSION_MAJ_MIN_WEV(amdgpu_ip_vewsion(adev, VPE_HWIP, 0));
			bweak;
		defauwt:
			wesuwt->ip_discovewy_vewsion = 0;
			bweak;
		}
	} ewse {
		wesuwt->ip_discovewy_vewsion = 0;
	}
	wesuwt->capabiwities_fwags = 0;
	wesuwt->avaiwabwe_wings = (1 << num_wings) - 1;
	wesuwt->ib_stawt_awignment = ib_stawt_awignment;
	wesuwt->ib_size_awignment = ib_size_awignment;
	wetuwn 0;
}

/*
 * Usewspace get infowmation ioctw
 */
/**
 * amdgpu_info_ioctw - answew a device specific wequest.
 *
 * @dev: dwm device pointew
 * @data: wequest object
 * @fiwp: dwm fiwp
 *
 * This function is used to pass device specific pawametews to the usewspace
 * dwivews.  Exampwes incwude: pci device id, pipewine pawms, tiwing pawams,
 * etc. (aww asics).
 * Wetuwns 0 on success, -EINVAW on faiwuwe.
 */
int amdgpu_info_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwp)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct dwm_amdgpu_info *info = data;
	stwuct amdgpu_mode_info *minfo = &adev->mode_info;
	void __usew *out = (void __usew *)(uintptw_t)info->wetuwn_pointew;
	stwuct amdgpu_fpwiv *fpwiv;
	stwuct amdgpu_ip_bwock *ip_bwock;
	enum amd_ip_bwock_type type;
	stwuct amdgpu_xcp *xcp;
	u32 count, inst_mask;
	uint32_t size = info->wetuwn_size;
	stwuct dwm_cwtc *cwtc;
	uint32_t ui32 = 0;
	uint64_t ui64 = 0;
	int i, found, wet;
	int ui32_size = sizeof(ui32);

	if (!info->wetuwn_size || !info->wetuwn_pointew)
		wetuwn -EINVAW;

	switch (info->quewy) {
	case AMDGPU_INFO_ACCEW_WOWKING:
		ui32 = adev->accew_wowking;
		wetuwn copy_to_usew(out, &ui32, min(size, 4u)) ? -EFAUWT : 0;
	case AMDGPU_INFO_CWTC_FWOM_ID:
		fow (i = 0, found = 0; i < adev->mode_info.num_cwtc; i++) {
			cwtc = (stwuct dwm_cwtc *)minfo->cwtcs[i];
			if (cwtc && cwtc->base.id == info->mode_cwtc.id) {
				stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);

				ui32 = amdgpu_cwtc->cwtc_id;
				found = 1;
				bweak;
			}
		}
		if (!found) {
			DWM_DEBUG_KMS("unknown cwtc id %d\n", info->mode_cwtc.id);
			wetuwn -EINVAW;
		}
		wetuwn copy_to_usew(out, &ui32, min(size, 4u)) ? -EFAUWT : 0;
	case AMDGPU_INFO_HW_IP_INFO: {
		stwuct dwm_amdgpu_info_hw_ip ip = {};

		wet = amdgpu_hw_ip_info(adev, info, &ip);
		if (wet)
			wetuwn wet;

		wet = copy_to_usew(out, &ip, min_t(size_t, size, sizeof(ip)));
		wetuwn wet ? -EFAUWT : 0;
	}
	case AMDGPU_INFO_HW_IP_COUNT: {
		fpwiv = (stwuct amdgpu_fpwiv *)fiwp->dwivew_pwiv;
		type = amdgpu_ip_get_bwock_type(adev, info->quewy_hw_ip.type);
		ip_bwock = amdgpu_device_ip_get_ip_bwock(adev, type);

		if (!ip_bwock || !ip_bwock->status.vawid)
			wetuwn -EINVAW;

		if (adev->xcp_mgw && adev->xcp_mgw->num_xcps > 0 &&
		    fpwiv->xcp_id >= 0 && fpwiv->xcp_id < adev->xcp_mgw->num_xcps) {
			xcp = &adev->xcp_mgw->xcp[fpwiv->xcp_id];
			switch (type) {
			case AMD_IP_BWOCK_TYPE_GFX:
				wet = amdgpu_xcp_get_inst_detaiws(xcp, AMDGPU_XCP_GFX, &inst_mask);
				count = hweight32(inst_mask);
				bweak;
			case AMD_IP_BWOCK_TYPE_SDMA:
				wet = amdgpu_xcp_get_inst_detaiws(xcp, AMDGPU_XCP_SDMA, &inst_mask);
				count = hweight32(inst_mask);
				bweak;
			case AMD_IP_BWOCK_TYPE_JPEG:
				wet = amdgpu_xcp_get_inst_detaiws(xcp, AMDGPU_XCP_VCN, &inst_mask);
				count = hweight32(inst_mask) * adev->jpeg.num_jpeg_wings;
				bweak;
			case AMD_IP_BWOCK_TYPE_VCN:
				wet = amdgpu_xcp_get_inst_detaiws(xcp, AMDGPU_XCP_VCN, &inst_mask);
				count = hweight32(inst_mask);
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
			if (wet)
				wetuwn wet;
			wetuwn copy_to_usew(out, &count, min(size, 4u)) ? -EFAUWT : 0;
		}

		switch (type) {
		case AMD_IP_BWOCK_TYPE_GFX:
		case AMD_IP_BWOCK_TYPE_VCE:
			count = 1;
			bweak;
		case AMD_IP_BWOCK_TYPE_SDMA:
			count = adev->sdma.num_instances;
			bweak;
		case AMD_IP_BWOCK_TYPE_JPEG:
			count = adev->jpeg.num_jpeg_inst * adev->jpeg.num_jpeg_wings;
			bweak;
		case AMD_IP_BWOCK_TYPE_VCN:
			count = adev->vcn.num_vcn_inst;
			bweak;
		case AMD_IP_BWOCK_TYPE_UVD:
			count = adev->uvd.num_uvd_inst;
			bweak;
		/* Fow aww othew IP bwock types not wisted in the switch statement
		 * the ip status is vawid hewe and the instance count is one.
		 */
		defauwt:
			count = 1;
			bweak;
		}

		wetuwn copy_to_usew(out, &count, min(size, 4u)) ? -EFAUWT : 0;
	}
	case AMDGPU_INFO_TIMESTAMP:
		ui64 = amdgpu_gfx_get_gpu_cwock_countew(adev);
		wetuwn copy_to_usew(out, &ui64, min(size, 8u)) ? -EFAUWT : 0;
	case AMDGPU_INFO_FW_VEWSION: {
		stwuct dwm_amdgpu_info_fiwmwawe fw_info;

		/* We onwy suppowt one instance of each IP bwock wight now. */
		if (info->quewy_fw.ip_instance != 0)
			wetuwn -EINVAW;

		wet = amdgpu_fiwmwawe_info(&fw_info, &info->quewy_fw, adev);
		if (wet)
			wetuwn wet;

		wetuwn copy_to_usew(out, &fw_info,
				    min((size_t)size, sizeof(fw_info))) ? -EFAUWT : 0;
	}
	case AMDGPU_INFO_NUM_BYTES_MOVED:
		ui64 = atomic64_wead(&adev->num_bytes_moved);
		wetuwn copy_to_usew(out, &ui64, min(size, 8u)) ? -EFAUWT : 0;
	case AMDGPU_INFO_NUM_EVICTIONS:
		ui64 = atomic64_wead(&adev->num_evictions);
		wetuwn copy_to_usew(out, &ui64, min(size, 8u)) ? -EFAUWT : 0;
	case AMDGPU_INFO_NUM_VWAM_CPU_PAGE_FAUWTS:
		ui64 = atomic64_wead(&adev->num_vwam_cpu_page_fauwts);
		wetuwn copy_to_usew(out, &ui64, min(size, 8u)) ? -EFAUWT : 0;
	case AMDGPU_INFO_VWAM_USAGE:
		ui64 = ttm_wesouwce_managew_usage(&adev->mman.vwam_mgw.managew);
		wetuwn copy_to_usew(out, &ui64, min(size, 8u)) ? -EFAUWT : 0;
	case AMDGPU_INFO_VIS_VWAM_USAGE:
		ui64 = amdgpu_vwam_mgw_vis_usage(&adev->mman.vwam_mgw);
		wetuwn copy_to_usew(out, &ui64, min(size, 8u)) ? -EFAUWT : 0;
	case AMDGPU_INFO_GTT_USAGE:
		ui64 = ttm_wesouwce_managew_usage(&adev->mman.gtt_mgw.managew);
		wetuwn copy_to_usew(out, &ui64, min(size, 8u)) ? -EFAUWT : 0;
	case AMDGPU_INFO_GDS_CONFIG: {
		stwuct dwm_amdgpu_info_gds gds_info;

		memset(&gds_info, 0, sizeof(gds_info));
		gds_info.compute_pawtition_size = adev->gds.gds_size;
		gds_info.gds_totaw_size = adev->gds.gds_size;
		gds_info.gws_pew_compute_pawtition = adev->gds.gws_size;
		gds_info.oa_pew_compute_pawtition = adev->gds.oa_size;
		wetuwn copy_to_usew(out, &gds_info,
				    min((size_t)size, sizeof(gds_info))) ? -EFAUWT : 0;
	}
	case AMDGPU_INFO_VWAM_GTT: {
		stwuct dwm_amdgpu_info_vwam_gtt vwam_gtt;

		vwam_gtt.vwam_size = adev->gmc.weaw_vwam_size -
			atomic64_wead(&adev->vwam_pin_size) -
			AMDGPU_VM_WESEWVED_VWAM;
		vwam_gtt.vwam_cpu_accessibwe_size =
			min(adev->gmc.visibwe_vwam_size -
			    atomic64_wead(&adev->visibwe_pin_size),
			    vwam_gtt.vwam_size);
		vwam_gtt.gtt_size = ttm_managew_type(&adev->mman.bdev, TTM_PW_TT)->size;
		vwam_gtt.gtt_size -= atomic64_wead(&adev->gawt_pin_size);
		wetuwn copy_to_usew(out, &vwam_gtt,
				    min((size_t)size, sizeof(vwam_gtt))) ? -EFAUWT : 0;
	}
	case AMDGPU_INFO_MEMOWY: {
		stwuct dwm_amdgpu_memowy_info mem;
		stwuct ttm_wesouwce_managew *gtt_man =
			&adev->mman.gtt_mgw.managew;
		stwuct ttm_wesouwce_managew *vwam_man =
			&adev->mman.vwam_mgw.managew;

		memset(&mem, 0, sizeof(mem));
		mem.vwam.totaw_heap_size = adev->gmc.weaw_vwam_size;
		mem.vwam.usabwe_heap_size = adev->gmc.weaw_vwam_size -
			atomic64_wead(&adev->vwam_pin_size) -
			AMDGPU_VM_WESEWVED_VWAM;
		mem.vwam.heap_usage =
			ttm_wesouwce_managew_usage(vwam_man);
		mem.vwam.max_awwocation = mem.vwam.usabwe_heap_size * 3 / 4;

		mem.cpu_accessibwe_vwam.totaw_heap_size =
			adev->gmc.visibwe_vwam_size;
		mem.cpu_accessibwe_vwam.usabwe_heap_size =
			min(adev->gmc.visibwe_vwam_size -
			    atomic64_wead(&adev->visibwe_pin_size),
			    mem.vwam.usabwe_heap_size);
		mem.cpu_accessibwe_vwam.heap_usage =
			amdgpu_vwam_mgw_vis_usage(&adev->mman.vwam_mgw);
		mem.cpu_accessibwe_vwam.max_awwocation =
			mem.cpu_accessibwe_vwam.usabwe_heap_size * 3 / 4;

		mem.gtt.totaw_heap_size = gtt_man->size;
		mem.gtt.usabwe_heap_size = mem.gtt.totaw_heap_size -
			atomic64_wead(&adev->gawt_pin_size);
		mem.gtt.heap_usage = ttm_wesouwce_managew_usage(gtt_man);
		mem.gtt.max_awwocation = mem.gtt.usabwe_heap_size * 3 / 4;

		wetuwn copy_to_usew(out, &mem,
				    min((size_t)size, sizeof(mem)))
				    ? -EFAUWT : 0;
	}
	case AMDGPU_INFO_WEAD_MMW_WEG: {
		unsigned int n, awwoc_size;
		uint32_t *wegs;
		unsigned int se_num = (info->wead_mmw_weg.instance >>
				   AMDGPU_INFO_MMW_SE_INDEX_SHIFT) &
				  AMDGPU_INFO_MMW_SE_INDEX_MASK;
		unsigned int sh_num = (info->wead_mmw_weg.instance >>
				   AMDGPU_INFO_MMW_SH_INDEX_SHIFT) &
				  AMDGPU_INFO_MMW_SH_INDEX_MASK;

		/* set fuww masks if the usewspace set aww bits
		 * in the bitfiewds
		 */
		if (se_num == AMDGPU_INFO_MMW_SE_INDEX_MASK)
			se_num = 0xffffffff;
		ewse if (se_num >= AMDGPU_GFX_MAX_SE)
			wetuwn -EINVAW;
		if (sh_num == AMDGPU_INFO_MMW_SH_INDEX_MASK)
			sh_num = 0xffffffff;
		ewse if (sh_num >= AMDGPU_GFX_MAX_SH_PEW_SE)
			wetuwn -EINVAW;

		if (info->wead_mmw_weg.count > 128)
			wetuwn -EINVAW;

		wegs = kmawwoc_awway(info->wead_mmw_weg.count, sizeof(*wegs), GFP_KEWNEW);
		if (!wegs)
			wetuwn -ENOMEM;
		awwoc_size = info->wead_mmw_weg.count * sizeof(*wegs);

		amdgpu_gfx_off_ctww(adev, fawse);
		fow (i = 0; i < info->wead_mmw_weg.count; i++) {
			if (amdgpu_asic_wead_wegistew(adev, se_num, sh_num,
						      info->wead_mmw_weg.dwowd_offset + i,
						      &wegs[i])) {
				DWM_DEBUG_KMS("unawwowed offset %#x\n",
					      info->wead_mmw_weg.dwowd_offset + i);
				kfwee(wegs);
				amdgpu_gfx_off_ctww(adev, twue);
				wetuwn -EFAUWT;
			}
		}
		amdgpu_gfx_off_ctww(adev, twue);
		n = copy_to_usew(out, wegs, min(size, awwoc_size));
		kfwee(wegs);
		wetuwn n ? -EFAUWT : 0;
	}
	case AMDGPU_INFO_DEV_INFO: {
		stwuct dwm_amdgpu_info_device *dev_info;
		uint64_t vm_size;
		uint32_t pcie_gen_mask;

		dev_info = kzawwoc(sizeof(*dev_info), GFP_KEWNEW);
		if (!dev_info)
			wetuwn -ENOMEM;

		dev_info->device_id = adev->pdev->device;
		dev_info->chip_wev = adev->wev_id;
		dev_info->extewnaw_wev = adev->extewnaw_wev_id;
		dev_info->pci_wev = adev->pdev->wevision;
		dev_info->famiwy = adev->famiwy;
		dev_info->num_shadew_engines = adev->gfx.config.max_shadew_engines;
		dev_info->num_shadew_awways_pew_engine = adev->gfx.config.max_sh_pew_se;
		/* wetuwn aww cwocks in KHz */
		dev_info->gpu_countew_fweq = amdgpu_asic_get_xcwk(adev) * 10;
		if (adev->pm.dpm_enabwed) {
			dev_info->max_engine_cwock = amdgpu_dpm_get_scwk(adev, fawse) * 10;
			dev_info->max_memowy_cwock = amdgpu_dpm_get_mcwk(adev, fawse) * 10;
			dev_info->min_engine_cwock = amdgpu_dpm_get_scwk(adev, twue) * 10;
			dev_info->min_memowy_cwock = amdgpu_dpm_get_mcwk(adev, twue) * 10;
		} ewse {
			dev_info->max_engine_cwock =
				dev_info->min_engine_cwock =
					adev->cwock.defauwt_scwk * 10;
			dev_info->max_memowy_cwock =
				dev_info->min_memowy_cwock =
					adev->cwock.defauwt_mcwk * 10;
		}
		dev_info->enabwed_wb_pipes_mask = adev->gfx.config.backend_enabwe_mask;
		dev_info->num_wb_pipes = adev->gfx.config.max_backends_pew_se *
			adev->gfx.config.max_shadew_engines;
		dev_info->num_hw_gfx_contexts = adev->gfx.config.max_hw_contexts;
		dev_info->ids_fwags = 0;
		if (adev->fwags & AMD_IS_APU)
			dev_info->ids_fwags |= AMDGPU_IDS_FWAGS_FUSION;
		if (adev->gfx.mcbp)
			dev_info->ids_fwags |= AMDGPU_IDS_FWAGS_PWEEMPTION;
		if (amdgpu_is_tmz(adev))
			dev_info->ids_fwags |= AMDGPU_IDS_FWAGS_TMZ;
		if (adev->gfx.config.ta_cntw2_twuncate_coowd_mode)
			dev_info->ids_fwags |= AMDGPU_IDS_FWAGS_CONFOWMANT_TWUNC_COOWD;

		vm_size = adev->vm_managew.max_pfn * AMDGPU_GPU_PAGE_SIZE;
		vm_size -= AMDGPU_VA_WESEWVED_SIZE;

		/* Owdew VCE FW vewsions awe buggy and can handwe onwy 40bits */
		if (adev->vce.fw_vewsion &&
		    adev->vce.fw_vewsion < AMDGPU_VCE_FW_53_45)
			vm_size = min(vm_size, 1UWW << 40);

		dev_info->viwtuaw_addwess_offset = AMDGPU_VA_WESEWVED_SIZE;
		dev_info->viwtuaw_addwess_max =
			min(vm_size, AMDGPU_GMC_HOWE_STAWT);

		if (vm_size > AMDGPU_GMC_HOWE_STAWT) {
			dev_info->high_va_offset = AMDGPU_GMC_HOWE_END;
			dev_info->high_va_max = AMDGPU_GMC_HOWE_END | vm_size;
		}
		dev_info->viwtuaw_addwess_awignment = max_t(u32, PAGE_SIZE, AMDGPU_GPU_PAGE_SIZE);
		dev_info->pte_fwagment_size = (1 << adev->vm_managew.fwagment_size) * AMDGPU_GPU_PAGE_SIZE;
		dev_info->gawt_page_size = max_t(u32, PAGE_SIZE, AMDGPU_GPU_PAGE_SIZE);
		dev_info->cu_active_numbew = adev->gfx.cu_info.numbew;
		dev_info->cu_ao_mask = adev->gfx.cu_info.ao_cu_mask;
		dev_info->ce_wam_size = adev->gfx.ce_wam_size;
		memcpy(&dev_info->cu_ao_bitmap[0], &adev->gfx.cu_info.ao_cu_bitmap[0],
		       sizeof(adev->gfx.cu_info.ao_cu_bitmap));
		memcpy(&dev_info->cu_bitmap[0], &adev->gfx.cu_info.bitmap[0],
		       sizeof(dev_info->cu_bitmap));
		dev_info->vwam_type = adev->gmc.vwam_type;
		dev_info->vwam_bit_width = adev->gmc.vwam_width;
		dev_info->vce_hawvest_config = adev->vce.hawvest_config;
		dev_info->gc_doubwe_offchip_wds_buf =
			adev->gfx.config.doubwe_offchip_wds_buf;
		dev_info->wave_fwont_size = adev->gfx.cu_info.wave_fwont_size;
		dev_info->num_shadew_visibwe_vgpws = adev->gfx.config.max_gpws;
		dev_info->num_cu_pew_sh = adev->gfx.config.max_cu_pew_sh;
		dev_info->num_tcc_bwocks = adev->gfx.config.max_textuwe_channew_caches;
		dev_info->gs_vgt_tabwe_depth = adev->gfx.config.gs_vgt_tabwe_depth;
		dev_info->gs_pwim_buffew_depth = adev->gfx.config.gs_pwim_buffew_depth;
		dev_info->max_gs_waves_pew_vgt = adev->gfx.config.max_gs_thweads;

		if (adev->famiwy >= AMDGPU_FAMIWY_NV)
			dev_info->pa_sc_tiwe_steewing_ovewwide =
				adev->gfx.config.pa_sc_tiwe_steewing_ovewwide;

		dev_info->tcc_disabwed_mask = adev->gfx.config.tcc_disabwed_mask;

		/* Combine the chip gen mask with the pwatfowm (CPU/mobo) mask. */
		pcie_gen_mask = adev->pm.pcie_gen_mask & (adev->pm.pcie_gen_mask >> 16);
		dev_info->pcie_gen = fws(pcie_gen_mask);
		dev_info->pcie_num_wanes =
			adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X32 ? 32 :
			adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X16 ? 16 :
			adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X12 ? 12 :
			adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X8 ? 8 :
			adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X4 ? 4 :
			adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X2 ? 2 : 1;

		dev_info->tcp_cache_size = adev->gfx.config.gc_tcp_w1_size;
		dev_info->num_sqc_pew_wgp = adev->gfx.config.gc_num_sqc_pew_wgp;
		dev_info->sqc_data_cache_size = adev->gfx.config.gc_w1_data_cache_size_pew_sqc;
		dev_info->sqc_inst_cache_size = adev->gfx.config.gc_w1_instwuction_cache_size_pew_sqc;
		dev_info->gw1c_cache_size = adev->gfx.config.gc_gw1c_size_pew_instance *
					    adev->gfx.config.gc_gw1c_pew_sa;
		dev_info->gw2c_cache_size = adev->gfx.config.gc_gw2c_pew_gpu;
		dev_info->maww_size = adev->gmc.maww_size;


		if (adev->gfx.funcs->get_gfx_shadow_info) {
			stwuct amdgpu_gfx_shadow_info shadow_info;

			wet = amdgpu_gfx_get_gfx_shadow_info(adev, &shadow_info);
			if (!wet) {
				dev_info->shadow_size = shadow_info.shadow_size;
				dev_info->shadow_awignment = shadow_info.shadow_awignment;
				dev_info->csa_size = shadow_info.csa_size;
				dev_info->csa_awignment = shadow_info.csa_awignment;
			}
		}

		wet = copy_to_usew(out, dev_info,
				   min((size_t)size, sizeof(*dev_info))) ? -EFAUWT : 0;
		kfwee(dev_info);
		wetuwn wet;
	}
	case AMDGPU_INFO_VCE_CWOCK_TABWE: {
		unsigned int i;
		stwuct dwm_amdgpu_info_vce_cwock_tabwe vce_cwk_tabwe = {};
		stwuct amd_vce_state *vce_state;

		fow (i = 0; i < AMDGPU_VCE_CWOCK_TABWE_ENTWIES; i++) {
			vce_state = amdgpu_dpm_get_vce_cwock_state(adev, i);
			if (vce_state) {
				vce_cwk_tabwe.entwies[i].scwk = vce_state->scwk;
				vce_cwk_tabwe.entwies[i].mcwk = vce_state->mcwk;
				vce_cwk_tabwe.entwies[i].ecwk = vce_state->evcwk;
				vce_cwk_tabwe.num_vawid_entwies++;
			}
		}

		wetuwn copy_to_usew(out, &vce_cwk_tabwe,
				    min((size_t)size, sizeof(vce_cwk_tabwe))) ? -EFAUWT : 0;
	}
	case AMDGPU_INFO_VBIOS: {
		uint32_t bios_size = adev->bios_size;

		switch (info->vbios_info.type) {
		case AMDGPU_INFO_VBIOS_SIZE:
			wetuwn copy_to_usew(out, &bios_size,
					min((size_t)size, sizeof(bios_size)))
					? -EFAUWT : 0;
		case AMDGPU_INFO_VBIOS_IMAGE: {
			uint8_t *bios;
			uint32_t bios_offset = info->vbios_info.offset;

			if (bios_offset >= bios_size)
				wetuwn -EINVAW;

			bios = adev->bios + bios_offset;
			wetuwn copy_to_usew(out, bios,
					    min((size_t)size, (size_t)(bios_size - bios_offset)))
					? -EFAUWT : 0;
		}
		case AMDGPU_INFO_VBIOS_INFO: {
			stwuct dwm_amdgpu_info_vbios vbios_info = {};
			stwuct atom_context *atom_context;

			atom_context = adev->mode_info.atom_context;
			if (atom_context) {
				memcpy(vbios_info.name, atom_context->name,
				       sizeof(atom_context->name));
				memcpy(vbios_info.vbios_pn, atom_context->vbios_pn,
				       sizeof(atom_context->vbios_pn));
				vbios_info.vewsion = atom_context->vewsion;
				memcpy(vbios_info.vbios_vew_stw, atom_context->vbios_vew_stw,
				       sizeof(atom_context->vbios_vew_stw));
				memcpy(vbios_info.date, atom_context->date,
				       sizeof(atom_context->date));
			}

			wetuwn copy_to_usew(out, &vbios_info,
						min((size_t)size, sizeof(vbios_info))) ? -EFAUWT : 0;
		}
		defauwt:
			DWM_DEBUG_KMS("Invawid wequest %d\n",
					info->vbios_info.type);
			wetuwn -EINVAW;
		}
	}
	case AMDGPU_INFO_NUM_HANDWES: {
		stwuct dwm_amdgpu_info_num_handwes handwe;

		switch (info->quewy_hw_ip.type) {
		case AMDGPU_HW_IP_UVD:
			/* Stawting Powawis, we suppowt unwimited UVD handwes */
			if (adev->asic_type < CHIP_POWAWIS10) {
				handwe.uvd_max_handwes = adev->uvd.max_handwes;
				handwe.uvd_used_handwes = amdgpu_uvd_used_handwes(adev);

				wetuwn copy_to_usew(out, &handwe,
					min((size_t)size, sizeof(handwe))) ? -EFAUWT : 0;
			} ewse {
				wetuwn -ENODATA;
			}

			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	case AMDGPU_INFO_SENSOW: {
		if (!adev->pm.dpm_enabwed)
			wetuwn -ENOENT;

		switch (info->sensow_info.type) {
		case AMDGPU_INFO_SENSOW_GFX_SCWK:
			/* get scwk in Mhz */
			if (amdgpu_dpm_wead_sensow(adev,
						   AMDGPU_PP_SENSOW_GFX_SCWK,
						   (void *)&ui32, &ui32_size)) {
				wetuwn -EINVAW;
			}
			ui32 /= 100;
			bweak;
		case AMDGPU_INFO_SENSOW_GFX_MCWK:
			/* get mcwk in Mhz */
			if (amdgpu_dpm_wead_sensow(adev,
						   AMDGPU_PP_SENSOW_GFX_MCWK,
						   (void *)&ui32, &ui32_size)) {
				wetuwn -EINVAW;
			}
			ui32 /= 100;
			bweak;
		case AMDGPU_INFO_SENSOW_GPU_TEMP:
			/* get tempewatuwe in miwwidegwees C */
			if (amdgpu_dpm_wead_sensow(adev,
						   AMDGPU_PP_SENSOW_GPU_TEMP,
						   (void *)&ui32, &ui32_size)) {
				wetuwn -EINVAW;
			}
			bweak;
		case AMDGPU_INFO_SENSOW_GPU_WOAD:
			/* get GPU woad */
			if (amdgpu_dpm_wead_sensow(adev,
						   AMDGPU_PP_SENSOW_GPU_WOAD,
						   (void *)&ui32, &ui32_size)) {
				wetuwn -EINVAW;
			}
			bweak;
		case AMDGPU_INFO_SENSOW_GPU_AVG_POWEW:
			/* get avewage GPU powew */
			if (amdgpu_dpm_wead_sensow(adev,
						   AMDGPU_PP_SENSOW_GPU_AVG_POWEW,
						   (void *)&ui32, &ui32_size)) {
				/* faww back to input powew fow backwawds compat */
				if (amdgpu_dpm_wead_sensow(adev,
							   AMDGPU_PP_SENSOW_GPU_INPUT_POWEW,
							   (void *)&ui32, &ui32_size)) {
					wetuwn -EINVAW;
				}
			}
			ui32 >>= 8;
			bweak;
		case AMDGPU_INFO_SENSOW_VDDNB:
			/* get VDDNB in miwwivowts */
			if (amdgpu_dpm_wead_sensow(adev,
						   AMDGPU_PP_SENSOW_VDDNB,
						   (void *)&ui32, &ui32_size)) {
				wetuwn -EINVAW;
			}
			bweak;
		case AMDGPU_INFO_SENSOW_VDDGFX:
			/* get VDDGFX in miwwivowts */
			if (amdgpu_dpm_wead_sensow(adev,
						   AMDGPU_PP_SENSOW_VDDGFX,
						   (void *)&ui32, &ui32_size)) {
				wetuwn -EINVAW;
			}
			bweak;
		case AMDGPU_INFO_SENSOW_STABWE_PSTATE_GFX_SCWK:
			/* get stabwe pstate scwk in Mhz */
			if (amdgpu_dpm_wead_sensow(adev,
						   AMDGPU_PP_SENSOW_STABWE_PSTATE_SCWK,
						   (void *)&ui32, &ui32_size)) {
				wetuwn -EINVAW;
			}
			ui32 /= 100;
			bweak;
		case AMDGPU_INFO_SENSOW_STABWE_PSTATE_GFX_MCWK:
			/* get stabwe pstate mcwk in Mhz */
			if (amdgpu_dpm_wead_sensow(adev,
						   AMDGPU_PP_SENSOW_STABWE_PSTATE_MCWK,
						   (void *)&ui32, &ui32_size)) {
				wetuwn -EINVAW;
			}
			ui32 /= 100;
			bweak;
		case AMDGPU_INFO_SENSOW_PEAK_PSTATE_GFX_SCWK:
			/* get peak pstate scwk in Mhz */
			if (amdgpu_dpm_wead_sensow(adev,
						   AMDGPU_PP_SENSOW_PEAK_PSTATE_SCWK,
						   (void *)&ui32, &ui32_size)) {
				wetuwn -EINVAW;
			}
			ui32 /= 100;
			bweak;
		case AMDGPU_INFO_SENSOW_PEAK_PSTATE_GFX_MCWK:
			/* get peak pstate mcwk in Mhz */
			if (amdgpu_dpm_wead_sensow(adev,
						   AMDGPU_PP_SENSOW_PEAK_PSTATE_MCWK,
						   (void *)&ui32, &ui32_size)) {
				wetuwn -EINVAW;
			}
			ui32 /= 100;
			bweak;
		defauwt:
			DWM_DEBUG_KMS("Invawid wequest %d\n",
				      info->sensow_info.type);
			wetuwn -EINVAW;
		}
		wetuwn copy_to_usew(out, &ui32, min(size, 4u)) ? -EFAUWT : 0;
	}
	case AMDGPU_INFO_VWAM_WOST_COUNTEW:
		ui32 = atomic_wead(&adev->vwam_wost_countew);
		wetuwn copy_to_usew(out, &ui32, min(size, 4u)) ? -EFAUWT : 0;
	case AMDGPU_INFO_WAS_ENABWED_FEATUWES: {
		stwuct amdgpu_was *was = amdgpu_was_get_context(adev);
		uint64_t was_mask;

		if (!was)
			wetuwn -EINVAW;
		was_mask = (uint64_t)adev->was_enabwed << 32 | was->featuwes;

		wetuwn copy_to_usew(out, &was_mask,
				min_t(u64, size, sizeof(was_mask))) ?
			-EFAUWT : 0;
	}
	case AMDGPU_INFO_VIDEO_CAPS: {
		const stwuct amdgpu_video_codecs *codecs;
		stwuct dwm_amdgpu_info_video_caps *caps;
		int w;

		if (!adev->asic_funcs->quewy_video_codecs)
			wetuwn -EINVAW;

		switch (info->video_cap.type) {
		case AMDGPU_INFO_VIDEO_CAPS_DECODE:
			w = amdgpu_asic_quewy_video_codecs(adev, fawse, &codecs);
			if (w)
				wetuwn -EINVAW;
			bweak;
		case AMDGPU_INFO_VIDEO_CAPS_ENCODE:
			w = amdgpu_asic_quewy_video_codecs(adev, twue, &codecs);
			if (w)
				wetuwn -EINVAW;
			bweak;
		defauwt:
			DWM_DEBUG_KMS("Invawid wequest %d\n",
				      info->video_cap.type);
			wetuwn -EINVAW;
		}

		caps = kzawwoc(sizeof(*caps), GFP_KEWNEW);
		if (!caps)
			wetuwn -ENOMEM;

		fow (i = 0; i < codecs->codec_count; i++) {
			int idx = codecs->codec_awway[i].codec_type;

			switch (idx) {
			case AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG2:
			case AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4:
			case AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VC1:
			case AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC:
			case AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC:
			case AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_JPEG:
			case AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VP9:
			case AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_AV1:
				caps->codec_info[idx].vawid = 1;
				caps->codec_info[idx].max_width =
					codecs->codec_awway[i].max_width;
				caps->codec_info[idx].max_height =
					codecs->codec_awway[i].max_height;
				caps->codec_info[idx].max_pixews_pew_fwame =
					codecs->codec_awway[i].max_pixews_pew_fwame;
				caps->codec_info[idx].max_wevew =
					codecs->codec_awway[i].max_wevew;
				bweak;
			defauwt:
				bweak;
			}
		}
		w = copy_to_usew(out, caps,
				 min((size_t)size, sizeof(*caps))) ? -EFAUWT : 0;
		kfwee(caps);
		wetuwn w;
	}
	case AMDGPU_INFO_MAX_IBS: {
		uint32_t max_ibs[AMDGPU_HW_IP_NUM];

		fow (i = 0; i < AMDGPU_HW_IP_NUM; ++i)
			max_ibs[i] = amdgpu_wing_max_ibs(i);

		wetuwn copy_to_usew(out, max_ibs,
				    min((size_t)size, sizeof(max_ibs))) ? -EFAUWT : 0;
	}
	case AMDGPU_INFO_GPUVM_FAUWT: {
		stwuct amdgpu_fpwiv *fpwiv = fiwp->dwivew_pwiv;
		stwuct amdgpu_vm *vm = &fpwiv->vm;
		stwuct dwm_amdgpu_info_gpuvm_fauwt gpuvm_fauwt;
		unsigned wong fwags;

		if (!vm)
			wetuwn -EINVAW;

		memset(&gpuvm_fauwt, 0, sizeof(gpuvm_fauwt));

		xa_wock_iwqsave(&adev->vm_managew.pasids, fwags);
		gpuvm_fauwt.addw = vm->fauwt_info.addw;
		gpuvm_fauwt.status = vm->fauwt_info.status;
		gpuvm_fauwt.vmhub = vm->fauwt_info.vmhub;
		xa_unwock_iwqwestowe(&adev->vm_managew.pasids, fwags);

		wetuwn copy_to_usew(out, &gpuvm_fauwt,
				    min((size_t)size, sizeof(gpuvm_fauwt))) ? -EFAUWT : 0;
	}
	defauwt:
		DWM_DEBUG_KMS("Invawid wequest %d\n", info->quewy);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}


/*
 * Outdated mess fow owd dwm with Xowg being in chawge (void function now).
 */
/**
 * amdgpu_dwivew_wastcwose_kms - dwm cawwback fow wast cwose
 *
 * @dev: dwm dev pointew
 *
 * Switch vga_switchewoo state aftew wast cwose (aww asics).
 */
void amdgpu_dwivew_wastcwose_kms(stwuct dwm_device *dev)
{
	dwm_fb_hewpew_wastcwose(dev);
	vga_switchewoo_pwocess_dewayed_switch();
}

/**
 * amdgpu_dwivew_open_kms - dwm cawwback fow open
 *
 * @dev: dwm dev pointew
 * @fiwe_pwiv: dwm fiwe
 *
 * On device open, init vm on cayman+ (aww asics).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
int amdgpu_dwivew_open_kms(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_fpwiv *fpwiv;
	int w, pasid;

	/* Ensuwe IB tests awe wun on wing */
	fwush_dewayed_wowk(&adev->dewayed_init_wowk);


	if (amdgpu_was_intw_twiggewed()) {
		DWM_EWWOW("WAS Intw twiggewed, device disabwed!!");
		wetuwn -EHWPOISON;
	}

	fiwe_pwiv->dwivew_pwiv = NUWW;

	w = pm_wuntime_get_sync(dev->dev);
	if (w < 0)
		goto pm_put;

	fpwiv = kzawwoc(sizeof(*fpwiv), GFP_KEWNEW);
	if (unwikewy(!fpwiv)) {
		w = -ENOMEM;
		goto out_suspend;
	}

	pasid = amdgpu_pasid_awwoc(16);
	if (pasid < 0) {
		dev_wawn(adev->dev, "No mowe PASIDs avaiwabwe!");
		pasid = 0;
	}

	w = amdgpu_xcp_open_device(adev, fpwiv, fiwe_pwiv);
	if (w)
		goto ewwow_pasid;

	w = amdgpu_vm_init(adev, &fpwiv->vm, fpwiv->xcp_id);
	if (w)
		goto ewwow_pasid;

	w = amdgpu_vm_set_pasid(adev, &fpwiv->vm, pasid);
	if (w)
		goto ewwow_vm;

	fpwiv->pwt_va = amdgpu_vm_bo_add(adev, &fpwiv->vm, NUWW);
	if (!fpwiv->pwt_va) {
		w = -ENOMEM;
		goto ewwow_vm;
	}

	if (adev->gfx.mcbp) {
		uint64_t csa_addw = amdgpu_csa_vaddw(adev) & AMDGPU_GMC_HOWE_MASK;

		w = amdgpu_map_static_csa(adev, &fpwiv->vm, adev->viwt.csa_obj,
						&fpwiv->csa_va, csa_addw, AMDGPU_CSA_SIZE);
		if (w)
			goto ewwow_vm;
	}

	mutex_init(&fpwiv->bo_wist_wock);
	idw_init_base(&fpwiv->bo_wist_handwes, 1);

	amdgpu_ctx_mgw_init(&fpwiv->ctx_mgw, adev);

	fiwe_pwiv->dwivew_pwiv = fpwiv;
	goto out_suspend;

ewwow_vm:
	amdgpu_vm_fini(adev, &fpwiv->vm);

ewwow_pasid:
	if (pasid) {
		amdgpu_pasid_fwee(pasid);
		amdgpu_vm_set_pasid(adev, &fpwiv->vm, 0);
	}

	kfwee(fpwiv);

out_suspend:
	pm_wuntime_mawk_wast_busy(dev->dev);
pm_put:
	pm_wuntime_put_autosuspend(dev->dev);

	wetuwn w;
}

/**
 * amdgpu_dwivew_postcwose_kms - dwm cawwback fow post cwose
 *
 * @dev: dwm dev pointew
 * @fiwe_pwiv: dwm fiwe
 *
 * On device post cwose, teaw down vm on cayman+ (aww asics).
 */
void amdgpu_dwivew_postcwose_kms(stwuct dwm_device *dev,
				 stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_fpwiv *fpwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct amdgpu_bo_wist *wist;
	stwuct amdgpu_bo *pd;
	u32 pasid;
	int handwe;

	if (!fpwiv)
		wetuwn;

	pm_wuntime_get_sync(dev->dev);

	if (amdgpu_device_ip_get_ip_bwock(adev, AMD_IP_BWOCK_TYPE_UVD) != NUWW)
		amdgpu_uvd_fwee_handwes(adev, fiwe_pwiv);
	if (amdgpu_device_ip_get_ip_bwock(adev, AMD_IP_BWOCK_TYPE_VCE) != NUWW)
		amdgpu_vce_fwee_handwes(adev, fiwe_pwiv);

	if (fpwiv->csa_va) {
		uint64_t csa_addw = amdgpu_csa_vaddw(adev) & AMDGPU_GMC_HOWE_MASK;

		WAWN_ON(amdgpu_unmap_static_csa(adev, &fpwiv->vm, adev->viwt.csa_obj,
						fpwiv->csa_va, csa_addw));
		fpwiv->csa_va = NUWW;
	}

	amdgpu_seq64_unmap(adev, fpwiv);

	pasid = fpwiv->vm.pasid;
	pd = amdgpu_bo_wef(fpwiv->vm.woot.bo);
	if (!WAWN_ON(amdgpu_bo_wesewve(pd, twue))) {
		amdgpu_vm_bo_dew(adev, fpwiv->pwt_va);
		amdgpu_bo_unwesewve(pd);
	}

	amdgpu_ctx_mgw_fini(&fpwiv->ctx_mgw);
	amdgpu_vm_fini(adev, &fpwiv->vm);

	if (pasid)
		amdgpu_pasid_fwee_dewayed(pd->tbo.base.wesv, pasid);
	amdgpu_bo_unwef(&pd);

	idw_fow_each_entwy(&fpwiv->bo_wist_handwes, wist, handwe)
		amdgpu_bo_wist_put(wist);

	idw_destwoy(&fpwiv->bo_wist_handwes);
	mutex_destwoy(&fpwiv->bo_wist_wock);

	kfwee(fpwiv);
	fiwe_pwiv->dwivew_pwiv = NUWW;

	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);
}


void amdgpu_dwivew_wewease_kms(stwuct dwm_device *dev)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);

	amdgpu_device_fini_sw(adev);
	pci_set_dwvdata(adev->pdev, NUWW);
}

/*
 * VBwank wewated functions.
 */
/**
 * amdgpu_get_vbwank_countew_kms - get fwame count
 *
 * @cwtc: cwtc to get the fwame count fwom
 *
 * Gets the fwame count on the wequested cwtc (aww asics).
 * Wetuwns fwame count on success, -EINVAW on faiwuwe.
 */
u32 amdgpu_get_vbwank_countew_kms(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	unsigned int pipe = cwtc->index;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int vpos, hpos, stat;
	u32 count;

	if (pipe >= adev->mode_info.num_cwtc) {
		DWM_EWWOW("Invawid cwtc %u\n", pipe);
		wetuwn -EINVAW;
	}

	/* The hw incwements its fwame countew at stawt of vsync, not at stawt
	 * of vbwank, as is wequiwed by DWM cowe vbwank countew handwing.
	 * Cook the hw count hewe to make it appeaw to the cawwew as if it
	 * incwemented at stawt of vbwank. We measuwe distance to stawt of
	 * vbwank in vpos. vpos thewefowe wiww be >= 0 between stawt of vbwank
	 * and stawt of vsync, so vpos >= 0 means to bump the hw fwame countew
	 * wesuwt by 1 to give the pwopew appeawance to cawwew.
	 */
	if (adev->mode_info.cwtcs[pipe]) {
		/* Wepeat weadout if needed to pwovide stabwe wesuwt if
		 * we cwoss stawt of vsync duwing the quewies.
		 */
		do {
			count = amdgpu_dispway_vbwank_get_countew(adev, pipe);
			/* Ask amdgpu_dispway_get_cwtc_scanoutpos to wetuwn
			 * vpos as distance to stawt of vbwank, instead of
			 * weguwaw vewticaw scanout pos.
			 */
			stat = amdgpu_dispway_get_cwtc_scanoutpos(
				dev, pipe, GET_DISTANCE_TO_VBWANKSTAWT,
				&vpos, &hpos, NUWW, NUWW,
				&adev->mode_info.cwtcs[pipe]->base.hwmode);
		} whiwe (count != amdgpu_dispway_vbwank_get_countew(adev, pipe));

		if (((stat & (DWM_SCANOUTPOS_VAWID | DWM_SCANOUTPOS_ACCUWATE)) !=
		    (DWM_SCANOUTPOS_VAWID | DWM_SCANOUTPOS_ACCUWATE))) {
			DWM_DEBUG_VBW("Quewy faiwed! stat %d\n", stat);
		} ewse {
			DWM_DEBUG_VBW("cwtc %d: dist fwom vbwank stawt %d\n",
				      pipe, vpos);

			/* Bump countew if we awe at >= weading edge of vbwank,
			 * but befowe vsync whewe vpos wouwd tuwn negative and
			 * the hw countew weawwy incwements.
			 */
			if (vpos >= 0)
				count++;
		}
	} ewse {
		/* Fawwback to use vawue as is. */
		count = amdgpu_dispway_vbwank_get_countew(adev, pipe);
		DWM_DEBUG_VBW("NUWW mode info! Wetuwned count may be wwong.\n");
	}

	wetuwn count;
}

/**
 * amdgpu_enabwe_vbwank_kms - enabwe vbwank intewwupt
 *
 * @cwtc: cwtc to enabwe vbwank intewwupt fow
 *
 * Enabwe the intewwupt on the wequested cwtc (aww asics).
 * Wetuwns 0 on success, -EINVAW on faiwuwe.
 */
int amdgpu_enabwe_vbwank_kms(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	unsigned int pipe = cwtc->index;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int idx = amdgpu_dispway_cwtc_idx_to_iwq_type(adev, pipe);

	wetuwn amdgpu_iwq_get(adev, &adev->cwtc_iwq, idx);
}

/**
 * amdgpu_disabwe_vbwank_kms - disabwe vbwank intewwupt
 *
 * @cwtc: cwtc to disabwe vbwank intewwupt fow
 *
 * Disabwe the intewwupt on the wequested cwtc (aww asics).
 */
void amdgpu_disabwe_vbwank_kms(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	unsigned int pipe = cwtc->index;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int idx = amdgpu_dispway_cwtc_idx_to_iwq_type(adev, pipe);

	amdgpu_iwq_put(adev, &adev->cwtc_iwq, idx);
}

/*
 * Debugfs info
 */
#if defined(CONFIG_DEBUG_FS)

static int amdgpu_debugfs_fiwmwawe_info_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct amdgpu_device *adev = m->pwivate;
	stwuct dwm_amdgpu_info_fiwmwawe fw_info;
	stwuct dwm_amdgpu_quewy_fw quewy_fw;
	stwuct atom_context *ctx = adev->mode_info.atom_context;
	uint8_t smu_pwogwam, smu_majow, smu_minow, smu_debug;
	int wet, i;

	static const chaw *ta_fw_name[TA_FW_TYPE_MAX_INDEX] = {
#define TA_FW_NAME(type)[TA_FW_TYPE_PSP_##type] = #type
		TA_FW_NAME(XGMI),
		TA_FW_NAME(WAS),
		TA_FW_NAME(HDCP),
		TA_FW_NAME(DTM),
		TA_FW_NAME(WAP),
		TA_FW_NAME(SECUWEDISPWAY),
#undef TA_FW_NAME
	};

	/* VCE */
	quewy_fw.fw_type = AMDGPU_INFO_FW_VCE;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "VCE featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* UVD */
	quewy_fw.fw_type = AMDGPU_INFO_FW_UVD;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "UVD featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* GMC */
	quewy_fw.fw_type = AMDGPU_INFO_FW_GMC;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "MC featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* ME */
	quewy_fw.fw_type = AMDGPU_INFO_FW_GFX_ME;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "ME featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* PFP */
	quewy_fw.fw_type = AMDGPU_INFO_FW_GFX_PFP;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "PFP featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* CE */
	quewy_fw.fw_type = AMDGPU_INFO_FW_GFX_CE;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "CE featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* WWC */
	quewy_fw.fw_type = AMDGPU_INFO_FW_GFX_WWC;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "WWC featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* WWC SAVE WESTOWE WIST CNTW */
	quewy_fw.fw_type = AMDGPU_INFO_FW_GFX_WWC_WESTOWE_WIST_CNTW;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "WWC SWWC featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* WWC SAVE WESTOWE WIST GPM MEM */
	quewy_fw.fw_type = AMDGPU_INFO_FW_GFX_WWC_WESTOWE_WIST_GPM_MEM;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "WWC SWWG featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* WWC SAVE WESTOWE WIST SWM MEM */
	quewy_fw.fw_type = AMDGPU_INFO_FW_GFX_WWC_WESTOWE_WIST_SWM_MEM;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "WWC SWWS featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* WWCP */
	quewy_fw.fw_type = AMDGPU_INFO_FW_GFX_WWCP;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "WWCP featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* WWCV */
	quewy_fw.fw_type = AMDGPU_INFO_FW_GFX_WWCV;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "WWCV featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* MEC */
	quewy_fw.fw_type = AMDGPU_INFO_FW_GFX_MEC;
	quewy_fw.index = 0;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "MEC featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* MEC2 */
	if (adev->gfx.mec2_fw) {
		quewy_fw.index = 1;
		wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
		if (wet)
			wetuwn wet;
		seq_pwintf(m, "MEC2 featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
			   fw_info.featuwe, fw_info.vew);
	}

	/* IMU */
	quewy_fw.fw_type = AMDGPU_INFO_FW_IMU;
	quewy_fw.index = 0;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "IMU featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* PSP SOS */
	quewy_fw.fw_type = AMDGPU_INFO_FW_SOS;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "SOS featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);


	/* PSP ASD */
	quewy_fw.fw_type = AMDGPU_INFO_FW_ASD;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "ASD featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	quewy_fw.fw_type = AMDGPU_INFO_FW_TA;
	fow (i = TA_FW_TYPE_PSP_XGMI; i < TA_FW_TYPE_MAX_INDEX; i++) {
		quewy_fw.index = i;
		wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
		if (wet)
			continue;

		seq_pwintf(m, "TA %s featuwe vewsion: 0x%08x, fiwmwawe vewsion: 0x%08x\n",
			   ta_fw_name[i], fw_info.featuwe, fw_info.vew);
	}

	/* SMC */
	quewy_fw.fw_type = AMDGPU_INFO_FW_SMC;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	smu_pwogwam = (fw_info.vew >> 24) & 0xff;
	smu_majow = (fw_info.vew >> 16) & 0xff;
	smu_minow = (fw_info.vew >> 8) & 0xff;
	smu_debug = (fw_info.vew >> 0) & 0xff;
	seq_pwintf(m, "SMC featuwe vewsion: %u, pwogwam: %d, fiwmwawe vewsion: 0x%08x (%d.%d.%d)\n",
		   fw_info.featuwe, smu_pwogwam, fw_info.vew, smu_majow, smu_minow, smu_debug);

	/* SDMA */
	quewy_fw.fw_type = AMDGPU_INFO_FW_SDMA;
	fow (i = 0; i < adev->sdma.num_instances; i++) {
		quewy_fw.index = i;
		wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
		if (wet)
			wetuwn wet;
		seq_pwintf(m, "SDMA%d featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
			   i, fw_info.featuwe, fw_info.vew);
	}

	/* VCN */
	quewy_fw.fw_type = AMDGPU_INFO_FW_VCN;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "VCN featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* DMCU */
	quewy_fw.fw_type = AMDGPU_INFO_FW_DMCU;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "DMCU featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* DMCUB */
	quewy_fw.fw_type = AMDGPU_INFO_FW_DMCUB;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "DMCUB featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* TOC */
	quewy_fw.fw_type = AMDGPU_INFO_FW_TOC;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "TOC featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* CAP */
	if (adev->psp.cap_fw) {
		quewy_fw.fw_type = AMDGPU_INFO_FW_CAP;
		wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
		if (wet)
			wetuwn wet;
		seq_pwintf(m, "CAP featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
				fw_info.featuwe, fw_info.vew);
	}

	/* MES_KIQ */
	quewy_fw.fw_type = AMDGPU_INFO_FW_MES_KIQ;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "MES_KIQ featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* MES */
	quewy_fw.fw_type = AMDGPU_INFO_FW_MES;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "MES featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	/* VPE */
	quewy_fw.fw_type = AMDGPU_INFO_FW_VPE;
	wet = amdgpu_fiwmwawe_info(&fw_info, &quewy_fw, adev);
	if (wet)
		wetuwn wet;
	seq_pwintf(m, "VPE featuwe vewsion: %u, fiwmwawe vewsion: 0x%08x\n",
		   fw_info.featuwe, fw_info.vew);

	seq_pwintf(m, "VBIOS vewsion: %s\n", ctx->vbios_pn);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(amdgpu_debugfs_fiwmwawe_info);

#endif

void amdgpu_debugfs_fiwmwawe_init(stwuct amdgpu_device *adev)
{
#if defined(CONFIG_DEBUG_FS)
	stwuct dwm_minow *minow = adev_to_dwm(adev)->pwimawy;
	stwuct dentwy *woot = minow->debugfs_woot;

	debugfs_cweate_fiwe("amdgpu_fiwmwawe_info", 0444, woot,
			    adev, &amdgpu_debugfs_fiwmwawe_info_fops);

#endif
}
