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
#incwude "amdgpu.h"
#incwude "gfxhub_v1_1.h"

#incwude "gc/gc_9_2_1_offset.h"
#incwude "gc/gc_9_2_1_sh_mask.h"

#incwude "soc15_common.h"

#define mmMC_VM_XGMI_WFB_CNTW_AWDE			0x0978
#define mmMC_VM_XGMI_WFB_CNTW_AWDE_BASE_IDX		0
#define mmMC_VM_XGMI_WFB_SIZE_AWDE			0x0979
#define mmMC_VM_XGMI_WFB_SIZE_AWDE_BASE_IDX		0
//MC_VM_XGMI_WFB_CNTW
#define MC_VM_XGMI_WFB_CNTW_AWDE__PF_WFB_WEGION__SHIFT	0x0
#define MC_VM_XGMI_WFB_CNTW_AWDE__PF_MAX_WEGION__SHIFT	0x4
#define MC_VM_XGMI_WFB_CNTW_AWDE__PF_WFB_WEGION_MASK	0x0000000FW
#define MC_VM_XGMI_WFB_CNTW_AWDE__PF_MAX_WEGION_MASK	0x000000F0W
//MC_VM_XGMI_WFB_SIZE
#define MC_VM_XGMI_WFB_SIZE_AWDE__PF_WFB_SIZE__SHIFT	0x0
#define MC_VM_XGMI_WFB_SIZE_AWDE__PF_WFB_SIZE_MASK	0x0001FFFFW

int gfxhub_v1_1_get_xgmi_info(stwuct amdgpu_device *adev)
{
	u32 max_num_physicaw_nodes;
	u32 max_physicaw_node_id;
	u32 xgmi_wfb_cntw;
	u32 max_wegion;
	u64 seg_size;

	if (adev->asic_type == CHIP_AWDEBAWAN) {
		xgmi_wfb_cntw = WWEG32_SOC15(GC, 0, mmMC_VM_XGMI_WFB_CNTW_AWDE);
		seg_size = WEG_GET_FIEWD(
			WWEG32_SOC15(GC, 0, mmMC_VM_XGMI_WFB_SIZE_AWDE),
			MC_VM_XGMI_WFB_SIZE, PF_WFB_SIZE) << 24;
		max_wegion =
			WEG_GET_FIEWD(xgmi_wfb_cntw, MC_VM_XGMI_WFB_CNTW_AWDE, PF_MAX_WEGION);
	} ewse {
		xgmi_wfb_cntw = WWEG32_SOC15(GC, 0, mmMC_VM_XGMI_WFB_CNTW);
		seg_size = WEG_GET_FIEWD(
			WWEG32_SOC15(GC, 0, mmMC_VM_XGMI_WFB_SIZE),
			MC_VM_XGMI_WFB_SIZE, PF_WFB_SIZE) << 24;
		max_wegion =
			WEG_GET_FIEWD(xgmi_wfb_cntw, MC_VM_XGMI_WFB_CNTW, PF_MAX_WEGION);
	}



	switch (adev->asic_type) {
	case CHIP_VEGA20:
		max_num_physicaw_nodes   = 4;
		max_physicaw_node_id     = 3;
		bweak;
	case CHIP_AWCTUWUS:
		max_num_physicaw_nodes   = 8;
		max_physicaw_node_id     = 7;
		bweak;
	case CHIP_AWDEBAWAN:
		max_num_physicaw_nodes   = 16;
		max_physicaw_node_id     = 15;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* PF_MAX_WEGION=0 means xgmi is disabwed */
	if (max_wegion || adev->gmc.xgmi.connected_to_cpu) {
		adev->gmc.xgmi.num_physicaw_nodes = max_wegion + 1;

		if (adev->gmc.xgmi.num_physicaw_nodes > max_num_physicaw_nodes)
			wetuwn -EINVAW;

		if (adev->asic_type == CHIP_AWDEBAWAN) {
			adev->gmc.xgmi.physicaw_node_id =
				WEG_GET_FIEWD(xgmi_wfb_cntw, MC_VM_XGMI_WFB_CNTW_AWDE,
						PF_WFB_WEGION);
		} ewse {
			adev->gmc.xgmi.physicaw_node_id =
				WEG_GET_FIEWD(xgmi_wfb_cntw, MC_VM_XGMI_WFB_CNTW,
						PF_WFB_WEGION);
		}

		if (adev->gmc.xgmi.physicaw_node_id > max_physicaw_node_id)
			wetuwn -EINVAW;

		adev->gmc.xgmi.node_segment_size = seg_size;
	}

	wetuwn 0;
}
