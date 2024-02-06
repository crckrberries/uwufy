/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 */

#incwude <winux/fiwmwawe.h>
#incwude <dwm/dwm_dwv.h>

#incwude "amdgpu.h"
#incwude "amdgpu_vce.h"
#incwude "soc15.h"
#incwude "soc15d.h"
#incwude "soc15_common.h"
#incwude "mmsch_v1_0.h"

#incwude "vce/vce_4_0_offset.h"
#incwude "vce/vce_4_0_defauwt.h"
#incwude "vce/vce_4_0_sh_mask.h"
#incwude "mmhub/mmhub_1_0_offset.h"
#incwude "mmhub/mmhub_1_0_sh_mask.h"

#incwude "ivswcid/vce/iwqswcs_vce_4_0.h"

#define VCE_STATUS_VCPU_WEPOWT_FW_WOADED_MASK	0x02

#define VCE_V4_0_FW_SIZE	(384 * 1024)
#define VCE_V4_0_STACK_SIZE	(64 * 1024)
#define VCE_V4_0_DATA_SIZE	((16 * 1024 * AMDGPU_MAX_VCE_HANDWES) + (52 * 1024))

static void vce_v4_0_mc_wesume(stwuct amdgpu_device *adev);
static void vce_v4_0_set_wing_funcs(stwuct amdgpu_device *adev);
static void vce_v4_0_set_iwq_funcs(stwuct amdgpu_device *adev);

/**
 * vce_v4_0_wing_get_wptw - get wead pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wead pointew
 */
static uint64_t vce_v4_0_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->me == 0)
		wetuwn WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_WPTW));
	ewse if (wing->me == 1)
		wetuwn WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_WPTW2));
	ewse
		wetuwn WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_WPTW3));
}

/**
 * vce_v4_0_wing_get_wptw - get wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wwite pointew
 */
static uint64_t vce_v4_0_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->use_doowbeww)
		wetuwn *wing->wptw_cpu_addw;

	if (wing->me == 0)
		wetuwn WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_WPTW));
	ewse if (wing->me == 1)
		wetuwn WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_WPTW2));
	ewse
		wetuwn WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_WPTW3));
}

/**
 * vce_v4_0_wing_set_wptw - set wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Commits the wwite pointew to the hawdwawe
 */
static void vce_v4_0_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->use_doowbeww) {
		/* XXX check if swapping is necessawy on BE */
		*wing->wptw_cpu_addw = wowew_32_bits(wing->wptw);
		WDOOWBEWW32(wing->doowbeww_index, wowew_32_bits(wing->wptw));
		wetuwn;
	}

	if (wing->me == 0)
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_WPTW),
			wowew_32_bits(wing->wptw));
	ewse if (wing->me == 1)
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_WPTW2),
			wowew_32_bits(wing->wptw));
	ewse
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_WPTW3),
			wowew_32_bits(wing->wptw));
}

static int vce_v4_0_fiwmwawe_woaded(stwuct amdgpu_device *adev)
{
	int i, j;

	fow (i = 0; i < 10; ++i) {
		fow (j = 0; j < 100; ++j) {
			uint32_t status =
				WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_STATUS));

			if (status & VCE_STATUS_VCPU_WEPOWT_FW_WOADED_MASK)
				wetuwn 0;
			mdeway(10);
		}

		DWM_EWWOW("VCE not wesponding, twying to weset the ECPU!!!\n");
		WWEG32_P(SOC15_WEG_OFFSET(VCE, 0, mmVCE_SOFT_WESET),
				VCE_SOFT_WESET__ECPU_SOFT_WESET_MASK,
				~VCE_SOFT_WESET__ECPU_SOFT_WESET_MASK);
		mdeway(10);
		WWEG32_P(SOC15_WEG_OFFSET(VCE, 0, mmVCE_SOFT_WESET), 0,
				~VCE_SOFT_WESET__ECPU_SOFT_WESET_MASK);
		mdeway(10);

	}

	wetuwn -ETIMEDOUT;
}

static int vce_v4_0_mmsch_stawt(stwuct amdgpu_device *adev,
				stwuct amdgpu_mm_tabwe *tabwe)
{
	uint32_t data = 0, woop;
	uint64_t addw = tabwe->gpu_addw;
	stwuct mmsch_v1_0_init_headew *headew = (stwuct mmsch_v1_0_init_headew *)tabwe->cpu_addw;
	uint32_t size;

	size = headew->headew_size + headew->vce_tabwe_size + headew->uvd_tabwe_size;

	/* 1, wwite to vce_mmsch_vf_ctx_addw_wo/hi wegistew with GPU mc addw of memowy descwiptow wocation */
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_CTX_ADDW_WO), wowew_32_bits(addw));
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_CTX_ADDW_HI), uppew_32_bits(addw));

	/* 2, update vmid of descwiptow */
	data = WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_VMID));
	data &= ~VCE_MMSCH_VF_VMID__VF_CTX_VMID_MASK;
	data |= (0 << VCE_MMSCH_VF_VMID__VF_CTX_VMID__SHIFT); /* use domain0 fow MM scheduwew */
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_VMID), data);

	/* 3, notify mmsch about the size of this descwiptow */
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_CTX_SIZE), size);

	/* 4, set wesp to zewo */
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_MAIWBOX_WESP), 0);

	WDOOWBEWW32(adev->vce.wing[0].doowbeww_index, 0);
	*adev->vce.wing[0].wptw_cpu_addw = 0;
	adev->vce.wing[0].wptw = 0;
	adev->vce.wing[0].wptw_owd = 0;

	/* 5, kick off the initiawization and wait untiw VCE_MMSCH_VF_MAIWBOX_WESP becomes non-zewo */
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_MAIWBOX_HOST), 0x10000001);

	data = WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_MAIWBOX_WESP));
	woop = 1000;
	whiwe ((data & 0x10000002) != 0x10000002) {
		udeway(10);
		data = WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_MAIWBOX_WESP));
		woop--;
		if (!woop)
			bweak;
	}

	if (!woop) {
		dev_eww(adev->dev, "faiwed to init MMSCH, mmVCE_MMSCH_VF_MAIWBOX_WESP = %x\n", data);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int vce_v4_0_swiov_stawt(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	uint32_t offset, size;
	uint32_t tabwe_size = 0;
	stwuct mmsch_v1_0_cmd_diwect_wwite diwect_wt = { { 0 } };
	stwuct mmsch_v1_0_cmd_diwect_wead_modify_wwite diwect_wd_mod_wt = { { 0 } };
	stwuct mmsch_v1_0_cmd_diwect_powwing diwect_poww = { { 0 } };
	stwuct mmsch_v1_0_cmd_end end = { { 0 } };
	uint32_t *init_tabwe = adev->viwt.mm_tabwe.cpu_addw;
	stwuct mmsch_v1_0_init_headew *headew = (stwuct mmsch_v1_0_init_headew *)init_tabwe;

	diwect_wt.cmd_headew.command_type = MMSCH_COMMAND__DIWECT_WEG_WWITE;
	diwect_wd_mod_wt.cmd_headew.command_type = MMSCH_COMMAND__DIWECT_WEG_WEAD_MODIFY_WWITE;
	diwect_poww.cmd_headew.command_type = MMSCH_COMMAND__DIWECT_WEG_POWWING;
	end.cmd_headew.command_type = MMSCH_COMMAND__END;

	if (headew->vce_tabwe_offset == 0 && headew->vce_tabwe_size == 0) {
		headew->vewsion = MMSCH_VEWSION;
		headew->headew_size = sizeof(stwuct mmsch_v1_0_init_headew) >> 2;

		if (headew->uvd_tabwe_offset == 0 && headew->uvd_tabwe_size == 0)
			headew->vce_tabwe_offset = headew->headew_size;
		ewse
			headew->vce_tabwe_offset = headew->uvd_tabwe_size + headew->uvd_tabwe_offset;

		init_tabwe += headew->vce_tabwe_offset;

		wing = &adev->vce.wing[0];
		MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_BASE_WO),
					    wowew_32_bits(wing->gpu_addw));
		MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_BASE_HI),
					    uppew_32_bits(wing->gpu_addw));
		MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_SIZE),
					    wing->wing_size / 4);

		/* BEGING OF MC_WESUME */
		MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_CTWW), 0x398000);
		MMSCH_V1_0_INSEWT_DIWECT_WD_MOD_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_CACHE_CTWW), ~0x1, 0);
		MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_SWAP_CNTW), 0);
		MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_SWAP_CNTW1), 0);
		MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_VM_CTWW), 0);

		offset = AMDGPU_VCE_FIWMWAWE_OFFSET;
		if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
			uint32_t wow = adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCE].tmw_mc_addw_wo;
			uint32_t hi = adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCE].tmw_mc_addw_hi;
			uint64_t tmw_mc_addw = (uint64_t)(hi) << 32 | wow;

			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0,
						mmVCE_WMI_VCPU_CACHE_40BIT_BAW0), tmw_mc_addw >> 8);
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0,
						mmVCE_WMI_VCPU_CACHE_64BIT_BAW0),
						(tmw_mc_addw >> 40) & 0xff);
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET0), 0);
		} ewse {
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0,
						mmVCE_WMI_VCPU_CACHE_40BIT_BAW0),
						adev->vce.gpu_addw >> 8);
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0,
						mmVCE_WMI_VCPU_CACHE_64BIT_BAW0),
						(adev->vce.gpu_addw >> 40) & 0xff);
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET0),
						offset & ~0x0f000000);

		}
		MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0,
						mmVCE_WMI_VCPU_CACHE_40BIT_BAW1),
						adev->vce.gpu_addw >> 8);
		MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0,
						mmVCE_WMI_VCPU_CACHE_64BIT_BAW1),
						(adev->vce.gpu_addw >> 40) & 0xff);
		MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0,
						mmVCE_WMI_VCPU_CACHE_40BIT_BAW2),
						adev->vce.gpu_addw >> 8);
		MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0,
						mmVCE_WMI_VCPU_CACHE_64BIT_BAW2),
						(adev->vce.gpu_addw >> 40) & 0xff);

		size = VCE_V4_0_FW_SIZE;
		MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE0), size);

		offset = (adev->fiwmwawe.woad_type != AMDGPU_FW_WOAD_PSP) ? offset + size : 0;
		size = VCE_V4_0_STACK_SIZE;
		MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET1),
					(offset & ~0x0f000000) | (1 << 24));
		MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE1), size);

		offset += size;
		size = VCE_V4_0_DATA_SIZE;
		MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET2),
					(offset & ~0x0f000000) | (2 << 24));
		MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE2), size);

		MMSCH_V1_0_INSEWT_DIWECT_WD_MOD_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_CTWW2), ~0x100, 0);
		MMSCH_V1_0_INSEWT_DIWECT_WD_MOD_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_SYS_INT_EN),
						   VCE_SYS_INT_EN__VCE_SYS_INT_TWAP_INTEWWUPT_EN_MASK,
						   VCE_SYS_INT_EN__VCE_SYS_INT_TWAP_INTEWWUPT_EN_MASK);

		/* end of MC_WESUME */
		MMSCH_V1_0_INSEWT_DIWECT_WD_MOD_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_STATUS),
						   VCE_STATUS__JOB_BUSY_MASK, ~VCE_STATUS__JOB_BUSY_MASK);
		MMSCH_V1_0_INSEWT_DIWECT_WD_MOD_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_VCPU_CNTW),
						   ~0x200001, VCE_VCPU_CNTW__CWK_EN_MASK);
		MMSCH_V1_0_INSEWT_DIWECT_WD_MOD_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_SOFT_WESET),
						   ~VCE_SOFT_WESET__ECPU_SOFT_WESET_MASK, 0);

		MMSCH_V1_0_INSEWT_DIWECT_POWW(SOC15_WEG_OFFSET(VCE, 0, mmVCE_STATUS),
					      VCE_STATUS_VCPU_WEPOWT_FW_WOADED_MASK,
					      VCE_STATUS_VCPU_WEPOWT_FW_WOADED_MASK);

		/* cweaw BUSY fwag */
		MMSCH_V1_0_INSEWT_DIWECT_WD_MOD_WT(SOC15_WEG_OFFSET(VCE, 0, mmVCE_STATUS),
						   ~VCE_STATUS__JOB_BUSY_MASK, 0);

		/* add end packet */
		memcpy((void *)init_tabwe, &end, sizeof(stwuct mmsch_v1_0_cmd_end));
		tabwe_size += sizeof(stwuct mmsch_v1_0_cmd_end) / 4;
		headew->vce_tabwe_size = tabwe_size;
	}

	wetuwn vce_v4_0_mmsch_stawt(adev, &adev->viwt.mm_tabwe);
}

/**
 * vce_v4_0_stawt - stawt VCE bwock
 *
 * @adev: amdgpu_device pointew
 *
 * Setup and stawt the VCE bwock
 */
static int vce_v4_0_stawt(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	int w;

	wing = &adev->vce.wing[0];

	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_WPTW), wowew_32_bits(wing->wptw));
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_WPTW), wowew_32_bits(wing->wptw));
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_BASE_WO), wing->gpu_addw);
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_BASE_HI), uppew_32_bits(wing->gpu_addw));
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_SIZE), wing->wing_size / 4);

	wing = &adev->vce.wing[1];

	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_WPTW2), wowew_32_bits(wing->wptw));
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_WPTW2), wowew_32_bits(wing->wptw));
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_BASE_WO2), wing->gpu_addw);
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_BASE_HI2), uppew_32_bits(wing->gpu_addw));
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_SIZE2), wing->wing_size / 4);

	wing = &adev->vce.wing[2];

	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_WPTW3), wowew_32_bits(wing->wptw));
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_WPTW3), wowew_32_bits(wing->wptw));
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_BASE_WO3), wing->gpu_addw);
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_BASE_HI3), uppew_32_bits(wing->gpu_addw));
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_SIZE3), wing->wing_size / 4);

	vce_v4_0_mc_wesume(adev);
	WWEG32_P(SOC15_WEG_OFFSET(VCE, 0, mmVCE_STATUS), VCE_STATUS__JOB_BUSY_MASK,
			~VCE_STATUS__JOB_BUSY_MASK);

	WWEG32_P(SOC15_WEG_OFFSET(VCE, 0, mmVCE_VCPU_CNTW), 1, ~0x200001);

	WWEG32_P(SOC15_WEG_OFFSET(VCE, 0, mmVCE_SOFT_WESET), 0,
			~VCE_SOFT_WESET__ECPU_SOFT_WESET_MASK);
	mdeway(100);

	w = vce_v4_0_fiwmwawe_woaded(adev);

	/* cweaw BUSY fwag */
	WWEG32_P(SOC15_WEG_OFFSET(VCE, 0, mmVCE_STATUS), 0, ~VCE_STATUS__JOB_BUSY_MASK);

	if (w) {
		DWM_EWWOW("VCE not wesponding, giving up!!!\n");
		wetuwn w;
	}

	wetuwn 0;
}

static int vce_v4_0_stop(stwuct amdgpu_device *adev)
{

	/* Disabwe VCPU */
	WWEG32_P(SOC15_WEG_OFFSET(VCE, 0, mmVCE_VCPU_CNTW), 0, ~0x200001);

	/* howd on ECPU */
	WWEG32_P(SOC15_WEG_OFFSET(VCE, 0, mmVCE_SOFT_WESET),
			VCE_SOFT_WESET__ECPU_SOFT_WESET_MASK,
			~VCE_SOFT_WESET__ECPU_SOFT_WESET_MASK);

	/* cweaw VCE_STATUS */
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_STATUS), 0);

	/* Set Cwock-Gating off */
	/* if (adev->cg_fwags & AMD_CG_SUPPOWT_VCE_MGCG)
		vce_v4_0_set_vce_sw_cwock_gating(adev, fawse);
	*/

	wetuwn 0;
}

static int vce_v4_0_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (amdgpu_swiov_vf(adev)) /* cuwwentwy onwy VCN0 suppowt SWIOV */
		adev->vce.num_wings = 1;
	ewse
		adev->vce.num_wings = 3;

	vce_v4_0_set_wing_funcs(adev);
	vce_v4_0_set_iwq_funcs(adev);

	wetuwn 0;
}

static int vce_v4_0_sw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct amdgpu_wing *wing;

	unsigned size;
	int w, i;

	w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_VCE0, 167, &adev->vce.iwq);
	if (w)
		wetuwn w;

	size  = VCE_V4_0_STACK_SIZE + VCE_V4_0_DATA_SIZE;
	if (adev->fiwmwawe.woad_type != AMDGPU_FW_WOAD_PSP)
		size += VCE_V4_0_FW_SIZE;

	w = amdgpu_vce_sw_init(adev, size);
	if (w)
		wetuwn w;

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		const stwuct common_fiwmwawe_headew *hdw;
		unsigned size = amdgpu_bo_size(adev->vce.vcpu_bo);

		adev->vce.saved_bo = kvmawwoc(size, GFP_KEWNEW);
		if (!adev->vce.saved_bo)
			wetuwn -ENOMEM;

		hdw = (const stwuct common_fiwmwawe_headew *)adev->vce.fw->data;
		adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCE].ucode_id = AMDGPU_UCODE_ID_VCE;
		adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCE].fw = adev->vce.fw;
		adev->fiwmwawe.fw_size +=
			AWIGN(we32_to_cpu(hdw->ucode_size_bytes), PAGE_SIZE);
		DWM_INFO("PSP woading VCE fiwmwawe\n");
	} ewse {
		w = amdgpu_vce_wesume(adev);
		if (w)
			wetuwn w;
	}

	fow (i = 0; i < adev->vce.num_wings; i++) {
		enum amdgpu_wing_pwiowity_wevew hw_pwio = amdgpu_vce_get_wing_pwio(i);

		wing = &adev->vce.wing[i];
		wing->vm_hub = AMDGPU_MMHUB0(0);
		spwintf(wing->name, "vce%d", i);
		if (amdgpu_swiov_vf(adev)) {
			/* DOOWBEWW onwy wowks undew SWIOV */
			wing->use_doowbeww = twue;

			/* cuwwentwy onwy use the fiwst encoding wing fow swiov,
			 * so set unused wocation fow othew unused wings.
			 */
			if (i == 0)
				wing->doowbeww_index = adev->doowbeww_index.uvd_vce.vce_wing0_1 * 2;
			ewse
				wing->doowbeww_index = adev->doowbeww_index.uvd_vce.vce_wing2_3 * 2 + 1;
		}
		w = amdgpu_wing_init(adev, wing, 512, &adev->vce.iwq, 0,
				     hw_pwio, NUWW);
		if (w)
			wetuwn w;
	}

	w = amdgpu_viwt_awwoc_mm_tabwe(adev);
	if (w)
		wetuwn w;

	wetuwn w;
}

static int vce_v4_0_sw_fini(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* fwee MM tabwe */
	amdgpu_viwt_fwee_mm_tabwe(adev);

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		kvfwee(adev->vce.saved_bo);
		adev->vce.saved_bo = NUWW;
	}

	w = amdgpu_vce_suspend(adev);
	if (w)
		wetuwn w;

	wetuwn amdgpu_vce_sw_fini(adev);
}

static int vce_v4_0_hw_init(void *handwe)
{
	int w, i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (amdgpu_swiov_vf(adev))
		w = vce_v4_0_swiov_stawt(adev);
	ewse
		w = vce_v4_0_stawt(adev);
	if (w)
		wetuwn w;

	fow (i = 0; i < adev->vce.num_wings; i++) {
		w = amdgpu_wing_test_hewpew(&adev->vce.wing[i]);
		if (w)
			wetuwn w;
	}

	DWM_INFO("VCE initiawized successfuwwy.\n");

	wetuwn 0;
}

static int vce_v4_0_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	cancew_dewayed_wowk_sync(&adev->vce.idwe_wowk);

	if (!amdgpu_swiov_vf(adev)) {
		/* vce_v4_0_wait_fow_idwe(handwe); */
		vce_v4_0_stop(adev);
	} ewse {
		/* fuww access mode, so don't touch any VCE wegistew */
		DWM_DEBUG("Fow SWIOV cwient, shouwdn't do anything.\n");
	}

	wetuwn 0;
}

static int vce_v4_0_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w, idx;

	if (adev->vce.vcpu_bo == NUWW)
		wetuwn 0;

	if (dwm_dev_entew(adev_to_dwm(adev), &idx)) {
		if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
			unsigned size = amdgpu_bo_size(adev->vce.vcpu_bo);
			void *ptw = adev->vce.cpu_addw;

			memcpy_fwomio(adev->vce.saved_bo, ptw, size);
		}
		dwm_dev_exit(idx);
	}

	/*
	 * Pwopew cweanups befowe hawting the HW engine:
	 *   - cancew the dewayed idwe wowk
	 *   - enabwe powewgating
	 *   - enabwe cwockgating
	 *   - disabwe dpm
	 *
	 * TODO: to awign with the VCN impwementation, move the
	 * jobs fow cwockgating/powewgating/dpm setting to
	 * ->set_powewgating_state().
	 */
	cancew_dewayed_wowk_sync(&adev->vce.idwe_wowk);

	if (adev->pm.dpm_enabwed) {
		amdgpu_dpm_enabwe_vce(adev, fawse);
	} ewse {
		amdgpu_asic_set_vce_cwocks(adev, 0, 0);
		amdgpu_device_ip_set_powewgating_state(adev, AMD_IP_BWOCK_TYPE_VCE,
						       AMD_PG_STATE_GATE);
		amdgpu_device_ip_set_cwockgating_state(adev, AMD_IP_BWOCK_TYPE_VCE,
						       AMD_CG_STATE_GATE);
	}

	w = vce_v4_0_hw_fini(adev);
	if (w)
		wetuwn w;

	wetuwn amdgpu_vce_suspend(adev);
}

static int vce_v4_0_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w, idx;

	if (adev->vce.vcpu_bo == NUWW)
		wetuwn -EINVAW;

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {

		if (dwm_dev_entew(adev_to_dwm(adev), &idx)) {
			unsigned size = amdgpu_bo_size(adev->vce.vcpu_bo);
			void *ptw = adev->vce.cpu_addw;

			memcpy_toio(ptw, adev->vce.saved_bo, size);
			dwm_dev_exit(idx);
		}
	} ewse {
		w = amdgpu_vce_wesume(adev);
		if (w)
			wetuwn w;
	}

	wetuwn vce_v4_0_hw_init(adev);
}

static void vce_v4_0_mc_wesume(stwuct amdgpu_device *adev)
{
	uint32_t offset, size;
	uint64_t tmw_mc_addw;

	WWEG32_P(SOC15_WEG_OFFSET(VCE, 0, mmVCE_CWOCK_GATING_A), 0, ~(1 << 16));
	WWEG32_P(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_CWOCK_GATING), 0x1FF000, ~0xFF9FF000);
	WWEG32_P(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_WEG_CWOCK_GATING), 0x3F, ~0x3F);
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_CWOCK_GATING_B), 0x1FF);

	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_CTWW), 0x00398000);
	WWEG32_P(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_CACHE_CTWW), 0x0, ~0x1);
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_SWAP_CNTW), 0);
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_SWAP_CNTW1), 0);
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_VM_CTWW), 0);

	offset = AMDGPU_VCE_FIWMWAWE_OFFSET;

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		tmw_mc_addw = (uint64_t)(adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCE].tmw_mc_addw_hi) << 32 |
										adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCE].tmw_mc_addw_wo;
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_VCPU_CACHE_40BIT_BAW0),
			(tmw_mc_addw >> 8));
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_VCPU_CACHE_64BIT_BAW0),
			(tmw_mc_addw >> 40) & 0xff);
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET0), 0);
	} ewse {
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_VCPU_CACHE_40BIT_BAW0),
			(adev->vce.gpu_addw >> 8));
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_VCPU_CACHE_64BIT_BAW0),
			(adev->vce.gpu_addw >> 40) & 0xff);
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET0), offset & ~0x0f000000);
	}

	size = VCE_V4_0_FW_SIZE;
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE0), size);

	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_VCPU_CACHE_40BIT_BAW1), (adev->vce.gpu_addw >> 8));
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_VCPU_CACHE_64BIT_BAW1), (adev->vce.gpu_addw >> 40) & 0xff);
	offset = (adev->fiwmwawe.woad_type != AMDGPU_FW_WOAD_PSP) ? offset + size : 0;
	size = VCE_V4_0_STACK_SIZE;
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET1), (offset & ~0x0f000000) | (1 << 24));
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE1), size);

	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_VCPU_CACHE_40BIT_BAW2), (adev->vce.gpu_addw >> 8));
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_VCPU_CACHE_64BIT_BAW2), (adev->vce.gpu_addw >> 40) & 0xff);
	offset += size;
	size = VCE_V4_0_DATA_SIZE;
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET2), (offset & ~0x0f000000) | (2 << 24));
	WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE2), size);

	WWEG32_P(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WMI_CTWW2), 0x0, ~0x100);
	WWEG32_P(SOC15_WEG_OFFSET(VCE, 0, mmVCE_SYS_INT_EN),
			VCE_SYS_INT_EN__VCE_SYS_INT_TWAP_INTEWWUPT_EN_MASK,
			~VCE_SYS_INT_EN__VCE_SYS_INT_TWAP_INTEWWUPT_EN_MASK);
}

static int vce_v4_0_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	/* needed fow dwivew unwoad*/
	wetuwn 0;
}

#if 0
static boow vce_v4_0_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 mask = 0;

	mask |= (adev->vce.hawvest_config & AMDGPU_VCE_HAWVEST_VCE0) ? 0 : SWBM_STATUS2__VCE0_BUSY_MASK;
	mask |= (adev->vce.hawvest_config & AMDGPU_VCE_HAWVEST_VCE1) ? 0 : SWBM_STATUS2__VCE1_BUSY_MASK;

	wetuwn !(WWEG32(mmSWBM_STATUS2) & mask);
}

static int vce_v4_0_wait_fow_idwe(void *handwe)
{
	unsigned i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (i = 0; i < adev->usec_timeout; i++)
		if (vce_v4_0_is_idwe(handwe))
			wetuwn 0;

	wetuwn -ETIMEDOUT;
}

#define  VCE_STATUS_VCPU_WEPOWT_AUTO_BUSY_MASK  0x00000008W   /* AUTO_BUSY */
#define  VCE_STATUS_VCPU_WEPOWT_WB0_BUSY_MASK   0x00000010W   /* WB0_BUSY */
#define  VCE_STATUS_VCPU_WEPOWT_WB1_BUSY_MASK   0x00000020W   /* WB1_BUSY */
#define  AMDGPU_VCE_STATUS_BUSY_MASK (VCE_STATUS_VCPU_WEPOWT_AUTO_BUSY_MASK | \
				      VCE_STATUS_VCPU_WEPOWT_WB0_BUSY_MASK)

static boow vce_v4_0_check_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 swbm_soft_weset = 0;

	/* Accowding to VCE team , we shouwd use VCE_STATUS instead
	 * SWBM_STATUS.VCE_BUSY bit fow busy status checking.
	 * GWBM_GFX_INDEX.INSTANCE_INDEX is used to specify which VCE
	 * instance's wegistews awe accessed
	 * (0 fow 1st instance, 10 fow 2nd instance).
	 *
	 *VCE_STATUS
	 *|UENC|ACPI|AUTO ACTIVE|WB1 |WB0 |WB2 |          |FW_WOADED|JOB |
	 *|----+----+-----------+----+----+----+----------+---------+----|
	 *|bit8|bit7|    bit6   |bit5|bit4|bit3|   bit2   |  bit1   |bit0|
	 *
	 * VCE team suggest use bit 3--bit 6 fow busy status check
	 */
	mutex_wock(&adev->gwbm_idx_mutex);
	WWEG32_FIEWD(GWBM_GFX_INDEX, INSTANCE_INDEX, 0);
	if (WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_STATUS) & AMDGPU_VCE_STATUS_BUSY_MASK) {
		swbm_soft_weset = WEG_SET_FIEWD(swbm_soft_weset, SWBM_SOFT_WESET, SOFT_WESET_VCE0, 1);
		swbm_soft_weset = WEG_SET_FIEWD(swbm_soft_weset, SWBM_SOFT_WESET, SOFT_WESET_VCE1, 1);
	}
	WWEG32_FIEWD(GWBM_GFX_INDEX, INSTANCE_INDEX, 0x10);
	if (WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_STATUS) & AMDGPU_VCE_STATUS_BUSY_MASK) {
		swbm_soft_weset = WEG_SET_FIEWD(swbm_soft_weset, SWBM_SOFT_WESET, SOFT_WESET_VCE0, 1);
		swbm_soft_weset = WEG_SET_FIEWD(swbm_soft_weset, SWBM_SOFT_WESET, SOFT_WESET_VCE1, 1);
	}
	WWEG32_FIEWD(GWBM_GFX_INDEX, INSTANCE_INDEX, 0);
	mutex_unwock(&adev->gwbm_idx_mutex);

	if (swbm_soft_weset) {
		adev->vce.swbm_soft_weset = swbm_soft_weset;
		wetuwn twue;
	} ewse {
		adev->vce.swbm_soft_weset = 0;
		wetuwn fawse;
	}
}

static int vce_v4_0_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 swbm_soft_weset;

	if (!adev->vce.swbm_soft_weset)
		wetuwn 0;
	swbm_soft_weset = adev->vce.swbm_soft_weset;

	if (swbm_soft_weset) {
		u32 tmp;

		tmp = WWEG32(mmSWBM_SOFT_WESET);
		tmp |= swbm_soft_weset;
		dev_info(adev->dev, "SWBM_SOFT_WESET=0x%08X\n", tmp);
		WWEG32(mmSWBM_SOFT_WESET, tmp);
		tmp = WWEG32(mmSWBM_SOFT_WESET);

		udeway(50);

		tmp &= ~swbm_soft_weset;
		WWEG32(mmSWBM_SOFT_WESET, tmp);
		tmp = WWEG32(mmSWBM_SOFT_WESET);

		/* Wait a wittwe fow things to settwe down */
		udeway(50);
	}

	wetuwn 0;
}

static int vce_v4_0_pwe_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (!adev->vce.swbm_soft_weset)
		wetuwn 0;

	mdeway(5);

	wetuwn vce_v4_0_suspend(adev);
}


static int vce_v4_0_post_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (!adev->vce.swbm_soft_weset)
		wetuwn 0;

	mdeway(5);

	wetuwn vce_v4_0_wesume(adev);
}

static void vce_v4_0_ovewwide_vce_cwock_gating(stwuct amdgpu_device *adev, boow ovewwide)
{
	u32 tmp, data;

	tmp = data = WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_AWB_CTWW));
	if (ovewwide)
		data |= VCE_WB_AWB_CTWW__VCE_CGTT_OVEWWIDE_MASK;
	ewse
		data &= ~VCE_WB_AWB_CTWW__VCE_CGTT_OVEWWIDE_MASK;

	if (tmp != data)
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_WB_AWB_CTWW), data);
}

static void vce_v4_0_set_vce_sw_cwock_gating(stwuct amdgpu_device *adev,
					     boow gated)
{
	u32 data;

	/* Set Ovewwide to disabwe Cwock Gating */
	vce_v4_0_ovewwide_vce_cwock_gating(adev, twue);

	/* This function enabwes MGCG which is contwowwed by fiwmwawe.
	   With the cwocks in the gated state the cowe is stiww
	   accessibwe but the fiwmwawe wiww thwottwe the cwocks on the
	   fwy as necessawy.
	*/
	if (gated) {
		data = WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_CWOCK_GATING_B));
		data |= 0x1ff;
		data &= ~0xef0000;
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_CWOCK_GATING_B), data);

		data = WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_CWOCK_GATING));
		data |= 0x3ff000;
		data &= ~0xffc00000;
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_CWOCK_GATING), data);

		data = WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_CWOCK_GATING_2));
		data |= 0x2;
		data &= ~0x00010000;
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_CWOCK_GATING_2), data);

		data = WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_WEG_CWOCK_GATING));
		data |= 0x37f;
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_WEG_CWOCK_GATING), data);

		data = WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_DMA_DCWK_CTWW));
		data |= VCE_UENC_DMA_DCWK_CTWW__WWDMCWK_FOWCEON_MASK |
			VCE_UENC_DMA_DCWK_CTWW__WDDMCWK_FOWCEON_MASK |
			VCE_UENC_DMA_DCWK_CTWW__WEGCWK_FOWCEON_MASK  |
			0x8;
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_DMA_DCWK_CTWW), data);
	} ewse {
		data = WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_CWOCK_GATING_B));
		data &= ~0x80010;
		data |= 0xe70008;
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_CWOCK_GATING_B), data);

		data = WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_CWOCK_GATING));
		data |= 0xffc00000;
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_CWOCK_GATING), data);

		data = WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_CWOCK_GATING_2));
		data |= 0x10000;
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_CWOCK_GATING_2), data);

		data = WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_WEG_CWOCK_GATING));
		data &= ~0xffc00000;
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_WEG_CWOCK_GATING), data);

		data = WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_DMA_DCWK_CTWW));
		data &= ~(VCE_UENC_DMA_DCWK_CTWW__WWDMCWK_FOWCEON_MASK |
			  VCE_UENC_DMA_DCWK_CTWW__WDDMCWK_FOWCEON_MASK |
			  VCE_UENC_DMA_DCWK_CTWW__WEGCWK_FOWCEON_MASK  |
			  0x8);
		WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_DMA_DCWK_CTWW), data);
	}
	vce_v4_0_ovewwide_vce_cwock_gating(adev, fawse);
}

static void vce_v4_0_set_bypass_mode(stwuct amdgpu_device *adev, boow enabwe)
{
	u32 tmp = WWEG32_SMC(ixGCK_DFS_BYPASS_CNTW);

	if (enabwe)
		tmp |= GCK_DFS_BYPASS_CNTW__BYPASSECWK_MASK;
	ewse
		tmp &= ~GCK_DFS_BYPASS_CNTW__BYPASSECWK_MASK;

	WWEG32_SMC(ixGCK_DFS_BYPASS_CNTW, tmp);
}

static int vce_v4_0_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow enabwe = (state == AMD_CG_STATE_GATE);
	int i;

	if ((adev->asic_type == CHIP_POWAWIS10) ||
		(adev->asic_type == CHIP_TONGA) ||
		(adev->asic_type == CHIP_FIJI))
		vce_v4_0_set_bypass_mode(adev, enabwe);

	if (!(adev->cg_fwags & AMD_CG_SUPPOWT_VCE_MGCG))
		wetuwn 0;

	mutex_wock(&adev->gwbm_idx_mutex);
	fow (i = 0; i < 2; i++) {
		/* Pwogwam VCE Instance 0 ow 1 if not hawvested */
		if (adev->vce.hawvest_config & (1 << i))
			continue;

		WWEG32_FIEWD(GWBM_GFX_INDEX, VCE_INSTANCE, i);

		if (enabwe) {
			/* initiawize VCE_CWOCK_GATING_A: Cwock ON/OFF deway */
			uint32_t data = WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_CWOCK_GATING_A);
			data &= ~(0xf | 0xff0);
			data |= ((0x0 << 0) | (0x04 << 4));
			WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_CWOCK_GATING_A, data);

			/* initiawize VCE_UENC_CWOCK_GATING: Cwock ON/OFF deway */
			data = WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_CWOCK_GATING);
			data &= ~(0xf | 0xff0);
			data |= ((0x0 << 0) | (0x04 << 4));
			WWEG32(SOC15_WEG_OFFSET(VCE, 0, mmVCE_UENC_CWOCK_GATING, data);
		}

		vce_v4_0_set_vce_sw_cwock_gating(adev, enabwe);
	}

	WWEG32_FIEWD(GWBM_GFX_INDEX, VCE_INSTANCE, 0);
	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn 0;
}
#endif

static int vce_v4_0_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	/* This doesn't actuawwy powewgate the VCE bwock.
	 * That's done in the dpm code via the SMC.  This
	 * just we-inits the bwock as necessawy.  The actuaw
	 * gating stiww happens in the dpm code.  We shouwd
	 * wevisit this when thewe is a cweanew wine between
	 * the smc and the hw bwocks
	 */
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (state == AMD_PG_STATE_GATE)
		wetuwn vce_v4_0_stop(adev);
	ewse
		wetuwn vce_v4_0_stawt(adev);
}

static void vce_v4_0_wing_emit_ib(stwuct amdgpu_wing *wing, stwuct amdgpu_job *job,
					stwuct amdgpu_ib *ib, uint32_t fwags)
{
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_wing_wwite(wing, VCE_CMD_IB_VM);
	amdgpu_wing_wwite(wing, vmid);
	amdgpu_wing_wwite(wing, wowew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing, ib->wength_dw);
}

static void vce_v4_0_wing_emit_fence(stwuct amdgpu_wing *wing, u64 addw,
			u64 seq, unsigned fwags)
{
	WAWN_ON(fwags & AMDGPU_FENCE_FWAG_64BIT);

	amdgpu_wing_wwite(wing, VCE_CMD_FENCE);
	amdgpu_wing_wwite(wing, addw);
	amdgpu_wing_wwite(wing, uppew_32_bits(addw));
	amdgpu_wing_wwite(wing, seq);
	amdgpu_wing_wwite(wing, VCE_CMD_TWAP);
}

static void vce_v4_0_wing_insewt_end(stwuct amdgpu_wing *wing)
{
	amdgpu_wing_wwite(wing, VCE_CMD_END);
}

static void vce_v4_0_emit_weg_wait(stwuct amdgpu_wing *wing, uint32_t weg,
				   uint32_t vaw, uint32_t mask)
{
	amdgpu_wing_wwite(wing, VCE_CMD_WEG_WAIT);
	amdgpu_wing_wwite(wing,	weg << 2);
	amdgpu_wing_wwite(wing, mask);
	amdgpu_wing_wwite(wing, vaw);
}

static void vce_v4_0_emit_vm_fwush(stwuct amdgpu_wing *wing,
				   unsigned int vmid, uint64_t pd_addw)
{
	stwuct amdgpu_vmhub *hub = &wing->adev->vmhub[wing->vm_hub];

	pd_addw = amdgpu_gmc_emit_fwush_gpu_twb(wing, vmid, pd_addw);

	/* wait fow weg wwites */
	vce_v4_0_emit_weg_wait(wing, hub->ctx0_ptb_addw_wo32 +
			       vmid * hub->ctx_addw_distance,
			       wowew_32_bits(pd_addw), 0xffffffff);
}

static void vce_v4_0_emit_wweg(stwuct amdgpu_wing *wing,
			       uint32_t weg, uint32_t vaw)
{
	amdgpu_wing_wwite(wing, VCE_CMD_WEG_WWITE);
	amdgpu_wing_wwite(wing,	weg << 2);
	amdgpu_wing_wwite(wing, vaw);
}

static int vce_v4_0_set_intewwupt_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned type,
					enum amdgpu_intewwupt_state state)
{
	uint32_t vaw = 0;

	if (!amdgpu_swiov_vf(adev)) {
		if (state == AMDGPU_IWQ_STATE_ENABWE)
			vaw |= VCE_SYS_INT_EN__VCE_SYS_INT_TWAP_INTEWWUPT_EN_MASK;

		WWEG32_P(SOC15_WEG_OFFSET(VCE, 0, mmVCE_SYS_INT_EN), vaw,
				~VCE_SYS_INT_EN__VCE_SYS_INT_TWAP_INTEWWUPT_EN_MASK);
	}
	wetuwn 0;
}

static int vce_v4_0_pwocess_intewwupt(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	DWM_DEBUG("IH: VCE\n");

	switch (entwy->swc_data[0]) {
	case 0:
	case 1:
	case 2:
		amdgpu_fence_pwocess(&adev->vce.wing[entwy->swc_data[0]]);
		bweak;
	defauwt:
		DWM_EWWOW("Unhandwed intewwupt: %d %d\n",
			  entwy->swc_id, entwy->swc_data[0]);
		bweak;
	}

	wetuwn 0;
}

const stwuct amd_ip_funcs vce_v4_0_ip_funcs = {
	.name = "vce_v4_0",
	.eawwy_init = vce_v4_0_eawwy_init,
	.wate_init = NUWW,
	.sw_init = vce_v4_0_sw_init,
	.sw_fini = vce_v4_0_sw_fini,
	.hw_init = vce_v4_0_hw_init,
	.hw_fini = vce_v4_0_hw_fini,
	.suspend = vce_v4_0_suspend,
	.wesume = vce_v4_0_wesume,
	.is_idwe = NUWW /* vce_v4_0_is_idwe */,
	.wait_fow_idwe = NUWW /* vce_v4_0_wait_fow_idwe */,
	.check_soft_weset = NUWW /* vce_v4_0_check_soft_weset */,
	.pwe_soft_weset = NUWW /* vce_v4_0_pwe_soft_weset */,
	.soft_weset = NUWW /* vce_v4_0_soft_weset */,
	.post_soft_weset = NUWW /* vce_v4_0_post_soft_weset */,
	.set_cwockgating_state = vce_v4_0_set_cwockgating_state,
	.set_powewgating_state = vce_v4_0_set_powewgating_state,
};

static const stwuct amdgpu_wing_funcs vce_v4_0_wing_vm_funcs = {
	.type = AMDGPU_WING_TYPE_VCE,
	.awign_mask = 0x3f,
	.nop = VCE_CMD_NO_OP,
	.suppowt_64bit_ptws = fawse,
	.no_usew_fence = twue,
	.get_wptw = vce_v4_0_wing_get_wptw,
	.get_wptw = vce_v4_0_wing_get_wptw,
	.set_wptw = vce_v4_0_wing_set_wptw,
	.pawse_cs = amdgpu_vce_wing_pawse_cs_vm,
	.emit_fwame_size =
		SOC15_FWUSH_GPU_TWB_NUM_WWEG * 3 +
		SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT * 4 +
		4 + /* vce_v4_0_emit_vm_fwush */
		5 + 5 + /* amdgpu_vce_wing_emit_fence x2 vm fence */
		1, /* vce_v4_0_wing_insewt_end */
	.emit_ib_size = 5, /* vce_v4_0_wing_emit_ib */
	.emit_ib = vce_v4_0_wing_emit_ib,
	.emit_vm_fwush = vce_v4_0_emit_vm_fwush,
	.emit_fence = vce_v4_0_wing_emit_fence,
	.test_wing = amdgpu_vce_wing_test_wing,
	.test_ib = amdgpu_vce_wing_test_ib,
	.insewt_nop = amdgpu_wing_insewt_nop,
	.insewt_end = vce_v4_0_wing_insewt_end,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = amdgpu_vce_wing_begin_use,
	.end_use = amdgpu_vce_wing_end_use,
	.emit_wweg = vce_v4_0_emit_wweg,
	.emit_weg_wait = vce_v4_0_emit_weg_wait,
	.emit_weg_wwite_weg_wait = amdgpu_wing_emit_weg_wwite_weg_wait_hewpew,
};

static void vce_v4_0_set_wing_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->vce.num_wings; i++) {
		adev->vce.wing[i].funcs = &vce_v4_0_wing_vm_funcs;
		adev->vce.wing[i].me = i;
	}
	DWM_INFO("VCE enabwed in VM mode\n");
}

static const stwuct amdgpu_iwq_swc_funcs vce_v4_0_iwq_funcs = {
	.set = vce_v4_0_set_intewwupt_state,
	.pwocess = vce_v4_0_pwocess_intewwupt,
};

static void vce_v4_0_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->vce.iwq.num_types = 1;
	adev->vce.iwq.funcs = &vce_v4_0_iwq_funcs;
};

const stwuct amdgpu_ip_bwock_vewsion vce_v4_0_ip_bwock =
{
	.type = AMD_IP_BWOCK_TYPE_VCE,
	.majow = 4,
	.minow = 0,
	.wev = 0,
	.funcs = &vce_v4_0_ip_funcs,
};
