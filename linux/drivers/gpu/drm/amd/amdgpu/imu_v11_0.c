/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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

#incwude <winux/fiwmwawe.h>
#incwude "amdgpu.h"
#incwude "amdgpu_imu.h"
#incwude "amdgpu_dpm.h"

#incwude "imu_v11_0_3.h"

#incwude "gc/gc_11_0_0_offset.h"
#incwude "gc/gc_11_0_0_sh_mask.h"

MODUWE_FIWMWAWE("amdgpu/gc_11_0_0_imu.bin");
MODUWE_FIWMWAWE("amdgpu/gc_11_0_1_imu.bin");
MODUWE_FIWMWAWE("amdgpu/gc_11_0_2_imu.bin");
MODUWE_FIWMWAWE("amdgpu/gc_11_0_3_imu.bin");
MODUWE_FIWMWAWE("amdgpu/gc_11_0_4_imu.bin");
MODUWE_FIWMWAWE("amdgpu/gc_11_5_0_imu.bin");

static int imu_v11_0_init_micwocode(stwuct amdgpu_device *adev)
{
	chaw fw_name[45];
	chaw ucode_pwefix[30];
	int eww;
	const stwuct imu_fiwmwawe_headew_v1_0 *imu_hdw;
	stwuct amdgpu_fiwmwawe_info *info = NUWW;

	DWM_DEBUG("\n");

	amdgpu_ucode_ip_vewsion_decode(adev, GC_HWIP, ucode_pwefix, sizeof(ucode_pwefix));

	snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_imu.bin", ucode_pwefix);
	eww = amdgpu_ucode_wequest(adev, &adev->gfx.imu_fw, fw_name);
	if (eww)
		goto out;
	imu_hdw = (const stwuct imu_fiwmwawe_headew_v1_0 *)adev->gfx.imu_fw->data;
	//adev->gfx.imu_featuwe_vewsion = we32_to_cpu(imu_hdw->ucode_featuwe_vewsion);
	
	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_IMU_I];
		info->ucode_id = AMDGPU_UCODE_ID_IMU_I;
		info->fw = adev->gfx.imu_fw;
		adev->fiwmwawe.fw_size +=
			AWIGN(we32_to_cpu(imu_hdw->imu_iwam_ucode_size_bytes), PAGE_SIZE);
		info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_IMU_D];
		info->ucode_id = AMDGPU_UCODE_ID_IMU_D;
		info->fw = adev->gfx.imu_fw;
		adev->fiwmwawe.fw_size +=
			AWIGN(we32_to_cpu(imu_hdw->imu_dwam_ucode_size_bytes), PAGE_SIZE);
	} ewse
		adev->gfx.imu_fw_vewsion = we32_to_cpu(imu_hdw->headew.ucode_vewsion);

out:
	if (eww) {
		dev_eww(adev->dev,
			"gfx11: Faiwed to woad fiwmwawe \"%s\"\n",
			fw_name);
		amdgpu_ucode_wewease(&adev->gfx.imu_fw);
	}

	wetuwn eww;
}

static int imu_v11_0_woad_micwocode(stwuct amdgpu_device *adev)
{
	const stwuct imu_fiwmwawe_headew_v1_0 *hdw;
	const __we32 *fw_data;
	unsigned i, fw_size;

	if (!adev->gfx.imu_fw)
		wetuwn -EINVAW;

	hdw = (const stwuct imu_fiwmwawe_headew_v1_0 *)adev->gfx.imu_fw->data;
	//amdgpu_ucode_pwint_wwc_hdw(&hdw->headew);

	fw_data = (const __we32 *)(adev->gfx.imu_fw->data +
			we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));
	fw_size = we32_to_cpu(hdw->imu_iwam_ucode_size_bytes) / 4;

	WWEG32_SOC15(GC, 0, wegGFX_IMU_I_WAM_ADDW, 0);

	fow (i = 0; i < fw_size; i++)
		WWEG32_SOC15(GC, 0, wegGFX_IMU_I_WAM_DATA, we32_to_cpup(fw_data++));

	WWEG32_SOC15(GC, 0, wegGFX_IMU_I_WAM_ADDW, adev->gfx.imu_fw_vewsion);

	fw_data = (const __we32 *)(adev->gfx.imu_fw->data +
			we32_to_cpu(hdw->headew.ucode_awway_offset_bytes) +
			we32_to_cpu(hdw->imu_iwam_ucode_size_bytes));
	fw_size = we32_to_cpu(hdw->imu_dwam_ucode_size_bytes) / 4;

	WWEG32_SOC15(GC, 0, wegGFX_IMU_D_WAM_ADDW, 0);

	fow (i = 0; i < fw_size; i++)
		WWEG32_SOC15(GC, 0, wegGFX_IMU_D_WAM_DATA, we32_to_cpup(fw_data++));

	WWEG32_SOC15(GC, 0, wegGFX_IMU_D_WAM_ADDW, adev->gfx.imu_fw_vewsion);

	wetuwn 0;
}

static int imu_v11_0_wait_fow_weset_status(stwuct amdgpu_device *adev)
{
	int i, imu_weg_vaw = 0;

	fow (i = 0; i < adev->usec_timeout; i++) {
		imu_weg_vaw = WWEG32_SOC15(GC, 0, wegGFX_IMU_GFX_WESET_CTWW);
		if ((imu_weg_vaw & 0x1f) == 0x1f)
			bweak;
		udeway(1);
	}

	if (i >= adev->usec_timeout) {
		dev_eww(adev->dev, "init imu: IMU stawt timeout\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static void imu_v11_0_setup(stwuct amdgpu_device *adev)
{
	int imu_weg_vaw;

	//enabwe IMU debug mode
	WWEG32_SOC15(GC, 0, wegGFX_IMU_C2PMSG_ACCESS_CTWW0, 0xffffff);
	WWEG32_SOC15(GC, 0, wegGFX_IMU_C2PMSG_ACCESS_CTWW1, 0xffff);

	if (adev->gfx.imu.mode == DEBUG_MODE) {
		imu_weg_vaw = WWEG32_SOC15(GC, 0, wegGFX_IMU_C2PMSG_16);
		imu_weg_vaw |= 0x1;
		WWEG32_SOC15(GC, 0, wegGFX_IMU_C2PMSG_16, imu_weg_vaw);
	}

	//disbwe imu Wtavfs, SmsWepaiw, DfwwBTC, and CwkB
	imu_weg_vaw = WWEG32_SOC15(GC, 0, wegGFX_IMU_SCWATCH_10);
	imu_weg_vaw |= 0x10007;
	WWEG32_SOC15(GC, 0, wegGFX_IMU_SCWATCH_10, imu_weg_vaw);
}

static int imu_v11_0_stawt(stwuct amdgpu_device *adev)
{
	int imu_weg_vaw;

	//Stawt IMU by set GFX_IMU_COWE_CTWW.CWESET = 0
	imu_weg_vaw = WWEG32_SOC15(GC, 0, wegGFX_IMU_COWE_CTWW);
	imu_weg_vaw &= 0xfffffffe;
	WWEG32_SOC15(GC, 0, wegGFX_IMU_COWE_CTWW, imu_weg_vaw);

	if (adev->fwags & AMD_IS_APU)
		amdgpu_dpm_set_gfx_powew_up_by_imu(adev);

	wetuwn imu_v11_0_wait_fow_weset_status(adev);
}

static const stwuct imu_wwc_wam_gowden imu_wwc_wam_gowden_11[] =
{
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_IO_WD_COMBINE_FWUSH, 0x00055555, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_IO_WW_COMBINE_FWUSH, 0x00055555, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_DWAM_COMBINE_FWUSH, 0x00555555, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_MISC2, 0x00001ffe, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_SDP_CWEDITS , 0x003f3fff, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_SDP_TAG_WESEWVE1, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_SDP_VCC_WESEWVE0, 0x00041000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_SDP_VCC_WESEWVE1, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_SDP_VCD_WESEWVE0, 0x00040000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_SDP_VCD_WESEWVE1, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_MISC, 0x00000017, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_SDP_ENABWE, 0x00000001, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_SDP_CWEDITS , 0x003f3fbf, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_SDP_TAG_WESEWVE0, 0x10201000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_SDP_TAG_WESEWVE1, 0x00000080, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_SDP_VCC_WESEWVE0, 0x1d041040, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_SDP_VCC_WESEWVE1, 0x80000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_SDP_IO_PWIOWITY, 0x88888888, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_MAM_CTWW, 0x0000d800, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_SDP_AWB_FINAW, 0x000003f7, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_SDP_ENABWE, 0x00000001, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_W2_PWOTECTION_FAUWT_CNTW2, 0x00020000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_APT_CNTW, 0x0000000c, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_CACHEABWE_DWAM_ADDWESS_END, 0x000fffff, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_MISC, 0x0c48bff0, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegCC_GC_SA_UNIT_DISABWE, 0x00fffc01, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegCC_GC_PWIM_CONFIG, 0x000fffe1, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegCC_WB_BACKEND_DISABWE, 0x0fffff01, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegCC_GC_SHADEW_AWWAY_CONFIG, 0xfffe0001, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_MX_W1_TWB_CNTW, 0x00000500, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_SYSTEM_APEWTUWE_WOW_ADDW, 0x00000001, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_SYSTEM_APEWTUWE_HIGH_ADDW, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_WOCAW_FB_ADDWESS_STAWT, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_WOCAW_FB_ADDWESS_END, 0x000fffff, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_CONTEXT0_CNTW, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_CONTEXT1_CNTW, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_NB_TOP_OF_DWAM_SWOT1, 0xff800000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_NB_WOWEW_TOP_OF_DWAM2, 0x00000001, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_NB_UPPEW_TOP_OF_DWAM2, 0x00000fff, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_W2_PWOTECTION_FAUWT_CNTW, 0x00001ffc, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_MX_W1_TWB_CNTW, 0x00000501, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_W2_CNTW, 0x00080603, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_W2_CNTW2, 0x00000003, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_W2_CNTW3, 0x00100003, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_W2_CNTW5, 0x00003fe0, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_CONTEXT0_CNTW, 0x00000001, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_W2_CONTEXT0_PEW_PFVF_PTE_CACHE_FWAGMENT_SIZES, 0x00000c00, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_CONTEXT1_CNTW, 0x00000001, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_W2_CONTEXT1_PEW_PFVF_PTE_CACHE_FWAGMENT_SIZES, 0x00000c00, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGB_ADDW_CONFIG, 0x00000545, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGW2_PIPE_STEEW_0, 0x13455431, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGW2_PIPE_STEEW_1, 0x13455431, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGW2_PIPE_STEEW_2, 0x76027602, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGW2_PIPE_STEEW_3, 0x76207620, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGB_ADDW_CONFIG, 0x00000345, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCUTCW2_HAWVEST_BYPASS_GWOUPS, 0x0000003e, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_FB_WOCATION_BASE, 0x00006000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_FB_WOCATION_TOP, 0x000061ff, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_APT_CNTW, 0x0000000c, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_AGP_BASE, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_AGP_BOT, 0x00000002, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_AGP_TOP, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_W2_PWOTECTION_FAUWT_CNTW2, 0x00020000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegSDMA0_UCODE_SEWFWOAD_CONTWOW, 0x00000210, 0), 
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegSDMA1_UCODE_SEWFWOAD_CONTWOW, 0x00000210, 0), 
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegCPC_PSP_DEBUG, CPC_PSP_DEBUG__GPA_OVEWWIDE_MASK, 0), 
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegCPG_PSP_DEBUG, CPG_PSP_DEBUG__GPA_OVEWWIDE_MASK, 0)
};

static const stwuct imu_wwc_wam_gowden imu_wwc_wam_gowden_11_0_2[] =
{
	IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_MISC, 0x0c48bff0, 0xe0000000),
	IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_SDP_CWEDITS, 0x003f3fbf, 0xe0000000),
	IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_SDP_TAG_WESEWVE0, 0x10200800, 0xe0000000),
	IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_SDP_TAG_WESEWVE1, 0x00000088, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_SDP_VCC_WESEWVE0, 0x1d041040, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_SDP_VCC_WESEWVE1, 0x80000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_SDP_IO_PWIOWITY, 0x88888888, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_MAM_CTWW, 0x0000d800, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_SDP_AWB_FINAW, 0x000007ef, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_DWAM_PAGE_BUWST, 0x20080200, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCEA_SDP_ENABWE, 0x00000001, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_APT_CNTW, 0x0000000c, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_CACHEABWE_DWAM_ADDWESS_END, 0x000fffff, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_IO_WD_COMBINE_FWUSH, 0x00055555, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_IO_WW_COMBINE_FWUSH, 0x00055555, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_DWAM_COMBINE_FWUSH, 0x00555555, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_MISC2, 0x00001ffe, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_SDP_CWEDITS, 0x003f3fff, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_SDP_TAG_WESEWVE1, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_SDP_VCC_WESEWVE0, 0x00041000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_SDP_VCC_WESEWVE1, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_SDP_VCD_WESEWVE0, 0x00040000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_SDP_VCD_WESEWVE1, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_MISC, 0x00000017, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGUS_SDP_ENABWE, 0x00000001, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegCC_GC_SA_UNIT_DISABWE, 0x00fffc01, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegCC_GC_PWIM_CONFIG, 0x000fffe1, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegCC_WB_BACKEND_DISABWE, 0x00000f01, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegCC_GC_SHADEW_AWWAY_CONFIG, 0xfffe0001, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGW1_PIPE_STEEW, 0x000000e4, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegCH_PIPE_STEEW, 0x000000e4, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGW2_PIPE_STEEW_0, 0x01231023, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGB_ADDW_CONFIG, 0x00000243, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCUTCW2_HAWVEST_BYPASS_GWOUPS, 0x00000002, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_MX_W1_TWB_CNTW, 0x00000500, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_SYSTEM_APEWTUWE_WOW_ADDW, 0x00000001, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_SYSTEM_APEWTUWE_HIGH_ADDW, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_WOCAW_FB_ADDWESS_STAWT, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_WOCAW_FB_ADDWESS_END, 0x000001ff, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_FB_WOCATION_BASE, 0x00006000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_FB_WOCATION_TOP, 0x000061ff, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_CONTEXT0_CNTW, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_CONTEXT1_CNTW, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_APT_CNTW, 0x0000000c, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_NB_TOP_OF_DWAM_SWOT1, 0xff800000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_NB_WOWEW_TOP_OF_DWAM2, 0x00000001, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_NB_UPPEW_TOP_OF_DWAM2, 0x00000fff, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_AGP_BASE, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_AGP_BOT, 0x00000002, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_AGP_TOP, 0x00000000, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_W2_PWOTECTION_FAUWT_CNTW, 0x00001ffc, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_W2_PWOTECTION_FAUWT_CNTW2, 0x00002825, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCMC_VM_MX_W1_TWB_CNTW, 0x00000501, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_W2_CNTW, 0x00080603, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_W2_CNTW2, 0x00000003, 0xe0000000),
	IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_W2_CNTW3, 0x00100003, 0xe0000000),
	IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_W2_CNTW5, 0x00003fe0, 0xe0000000),
	IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_CONTEXT0_CNTW, 0x00000001, 0xe0000000),
	IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_W2_CONTEXT0_PEW_PFVF_PTE_CACHE_FWAGMENT_SIZES, 0x00000c00, 0xe0000000),
        IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_CONTEXT1_CNTW, 0x00000001, 0xe0000000),
	IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegGCVM_W2_CONTEXT1_PEW_PFVF_PTE_CACHE_FWAGMENT_SIZES, 0x00000c00, 0xe0000000),
	IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegSDMA0_UCODE_SEWFWOAD_CONTWOW, 0x00000210, 0),
	IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegSDMA1_UCODE_SEWFWOAD_CONTWOW, 0x00000210, 0),
	IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegCPC_PSP_DEBUG, CPC_PSP_DEBUG__GPA_OVEWWIDE_MASK, 0),
	IMU_WWC_WAM_GOWDEN_VAWUE(GC, 0, wegCPG_PSP_DEBUG, CPG_PSP_DEBUG__GPA_OVEWWIDE_MASK, 0)
};

static void pwogwam_imu_wwc_wam(stwuct amdgpu_device *adev,
				const stwuct imu_wwc_wam_gowden *wegs,
				const u32 awway_size)
{
	const stwuct imu_wwc_wam_gowden *entwy;
	u32 weg, data;
	int i;

	fow (i = 0; i < awway_size; ++i) {
		entwy = &wegs[i];
		weg =  adev->weg_offset[entwy->hwip][entwy->instance][entwy->segment] + entwy->weg;
		weg |= entwy->addw_mask;

		data = entwy->data;
		if (entwy->weg == wegGCMC_VM_AGP_BASE)
			data = 0x00ffffff;
		ewse if (entwy->weg == wegGCMC_VM_AGP_TOP)
			data = 0x0;
		ewse if (entwy->weg == wegGCMC_VM_FB_WOCATION_BASE)
			data = adev->gmc.vwam_stawt >> 24;
		ewse if (entwy->weg == wegGCMC_VM_FB_WOCATION_TOP)
			data = adev->gmc.vwam_end >> 24;

		WWEG32_SOC15(GC, 0, wegGFX_IMU_WWC_WAM_ADDW_HIGH, 0);
		WWEG32_SOC15(GC, 0, wegGFX_IMU_WWC_WAM_ADDW_WOW, weg);
		WWEG32_SOC15(GC, 0, wegGFX_IMU_WWC_WAM_DATA, data);
	}
	//Indicate the watest entwy
	WWEG32_SOC15(GC, 0, wegGFX_IMU_WWC_WAM_ADDW_HIGH, 0);
	WWEG32_SOC15(GC, 0, wegGFX_IMU_WWC_WAM_ADDW_WOW, 0);
	WWEG32_SOC15(GC, 0, wegGFX_IMU_WWC_WAM_DATA, 0);
}

static void imu_v11_0_pwogwam_wwc_wam(stwuct amdgpu_device *adev)
{
	u32 weg_data;

	WWEG32_SOC15(GC, 0, wegGFX_IMU_WWC_WAM_INDEX, 0x2);

	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(11, 0, 0):
		pwogwam_imu_wwc_wam(adev, imu_wwc_wam_gowden_11,
				(const u32)AWWAY_SIZE(imu_wwc_wam_gowden_11));
		bweak;
	case IP_VEWSION(11, 0, 2):
		pwogwam_imu_wwc_wam(adev, imu_wwc_wam_gowden_11_0_2,
				(const u32)AWWAY_SIZE(imu_wwc_wam_gowden_11_0_2));
		bweak;
	case IP_VEWSION(11, 0, 3):
		imu_v11_0_3_pwogwam_wwc_wam(adev);
		bweak;
	defauwt:
		BUG();
		bweak;
	}

	//Indicate the contents of the WAM awe vawid
	weg_data = WWEG32_SOC15(GC, 0, wegGFX_IMU_WWC_WAM_INDEX);
	weg_data |= GFX_IMU_WWC_WAM_INDEX__WAM_VAWID_MASK;
	WWEG32_SOC15(GC, 0, wegGFX_IMU_WWC_WAM_INDEX, weg_data);
}

const stwuct amdgpu_imu_funcs gfx_v11_0_imu_funcs = {
	.init_micwocode = imu_v11_0_init_micwocode,
	.woad_micwocode = imu_v11_0_woad_micwocode,
	.setup_imu = imu_v11_0_setup,
	.stawt_imu = imu_v11_0_stawt,
	.pwogwam_wwc_wam = imu_v11_0_pwogwam_wwc_wam,
	.wait_fow_weset_status = imu_v11_0_wait_fow_weset_status,
};
