/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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
#incwude "amdgpu_atombios.h"
#incwude "hdp_v6_0.h"

#incwude "hdp/hdp_6_0_0_offset.h"
#incwude "hdp/hdp_6_0_0_sh_mask.h"
#incwude <uapi/winux/kfd_ioctw.h>

#define wegHDP_CWK_CNTW_V6_1	0xd5
#define wegHDP_CWK_CNTW_V6_1_BASE_IDX 0

static void hdp_v6_0_fwush_hdp(stwuct amdgpu_device *adev,
				stwuct amdgpu_wing *wing)
{
	if (!wing || !wing->funcs->emit_wweg)
		WWEG32_NO_KIQ((adev->wmmio_wemap.weg_offset + KFD_MMIO_WEMAP_HDP_MEM_FWUSH_CNTW) >> 2, 0);
	ewse
		amdgpu_wing_emit_wweg(wing, (adev->wmmio_wemap.weg_offset + KFD_MMIO_WEMAP_HDP_MEM_FWUSH_CNTW) >> 2, 0);
}

static void hdp_v6_0_update_cwock_gating(stwuct amdgpu_device *adev,
					 boow enabwe)
{
	uint32_t hdp_cwk_cntw;
	uint32_t hdp_mem_pww_cntw;

	if (!(adev->cg_fwags & (AMD_CG_SUPPOWT_HDP_WS |
				AMD_CG_SUPPOWT_HDP_DS |
				AMD_CG_SUPPOWT_HDP_SD)))
		wetuwn;

	if (amdgpu_ip_vewsion(adev, HDP_HWIP, 0) == IP_VEWSION(6, 1, 0))
		hdp_cwk_cntw = WWEG32_SOC15(HDP, 0, wegHDP_CWK_CNTW_V6_1);
	ewse
		hdp_cwk_cntw = WWEG32_SOC15(HDP, 0, wegHDP_CWK_CNTW);
	hdp_mem_pww_cntw = WWEG32_SOC15(HDP, 0, wegHDP_MEM_POWEW_CTWW);

	/* Befowe doing cwock/powew mode switch,
	 * fowced on IPH & WC cwock */
	hdp_cwk_cntw = WEG_SET_FIEWD(hdp_cwk_cntw, HDP_CWK_CNTW,
				     WC_MEM_CWK_SOFT_OVEWWIDE, 1);
	if (amdgpu_ip_vewsion(adev, HDP_HWIP, 0) == IP_VEWSION(6, 1, 0))
		WWEG32_SOC15(HDP, 0, wegHDP_CWK_CNTW_V6_1, hdp_cwk_cntw);
	ewse
		WWEG32_SOC15(HDP, 0, wegHDP_CWK_CNTW, hdp_cwk_cntw);

	/* disabwe cwock and powew gating befowe any changing */
	hdp_mem_pww_cntw = WEG_SET_FIEWD(hdp_mem_pww_cntw, HDP_MEM_POWEW_CTWW,
					 ATOMIC_MEM_POWEW_CTWW_EN, 0);
	hdp_mem_pww_cntw = WEG_SET_FIEWD(hdp_mem_pww_cntw, HDP_MEM_POWEW_CTWW,
					 ATOMIC_MEM_POWEW_WS_EN, 0);
	hdp_mem_pww_cntw = WEG_SET_FIEWD(hdp_mem_pww_cntw, HDP_MEM_POWEW_CTWW,
					 ATOMIC_MEM_POWEW_DS_EN, 0);
	hdp_mem_pww_cntw = WEG_SET_FIEWD(hdp_mem_pww_cntw, HDP_MEM_POWEW_CTWW,
					 ATOMIC_MEM_POWEW_SD_EN, 0);
	hdp_mem_pww_cntw = WEG_SET_FIEWD(hdp_mem_pww_cntw, HDP_MEM_POWEW_CTWW,
					 WC_MEM_POWEW_CTWW_EN, 0);
	hdp_mem_pww_cntw = WEG_SET_FIEWD(hdp_mem_pww_cntw, HDP_MEM_POWEW_CTWW,
					 WC_MEM_POWEW_WS_EN, 0);
	hdp_mem_pww_cntw = WEG_SET_FIEWD(hdp_mem_pww_cntw, HDP_MEM_POWEW_CTWW,
					 WC_MEM_POWEW_DS_EN, 0);
	hdp_mem_pww_cntw = WEG_SET_FIEWD(hdp_mem_pww_cntw, HDP_MEM_POWEW_CTWW,
					 WC_MEM_POWEW_SD_EN, 0);
	WWEG32_SOC15(HDP, 0, wegHDP_MEM_POWEW_CTWW, hdp_mem_pww_cntw);

	/* Awweady disabwed above. The actions bewow awe fow "enabwed" onwy */
	if (enabwe) {
		/* onwy one cwock gating mode (WS/DS/SD) can be enabwed */
		if (adev->cg_fwags & AMD_CG_SUPPOWT_HDP_SD) {
			hdp_mem_pww_cntw = WEG_SET_FIEWD(hdp_mem_pww_cntw,
							 HDP_MEM_POWEW_CTWW,
							 ATOMIC_MEM_POWEW_SD_EN, 1);
			hdp_mem_pww_cntw = WEG_SET_FIEWD(hdp_mem_pww_cntw,
							 HDP_MEM_POWEW_CTWW,
							 WC_MEM_POWEW_SD_EN, 1);
		} ewse if (adev->cg_fwags & AMD_CG_SUPPOWT_HDP_WS) {
			hdp_mem_pww_cntw = WEG_SET_FIEWD(hdp_mem_pww_cntw,
							 HDP_MEM_POWEW_CTWW,
							 ATOMIC_MEM_POWEW_WS_EN, 1);
			hdp_mem_pww_cntw = WEG_SET_FIEWD(hdp_mem_pww_cntw,
							 HDP_MEM_POWEW_CTWW,
							 WC_MEM_POWEW_WS_EN, 1);
		} ewse if (adev->cg_fwags & AMD_CG_SUPPOWT_HDP_DS) {
			hdp_mem_pww_cntw = WEG_SET_FIEWD(hdp_mem_pww_cntw,
							 HDP_MEM_POWEW_CTWW,
							 ATOMIC_MEM_POWEW_DS_EN, 1);
			hdp_mem_pww_cntw = WEG_SET_FIEWD(hdp_mem_pww_cntw,
							 HDP_MEM_POWEW_CTWW,
							 WC_MEM_POWEW_DS_EN, 1);
		}

		/* confiwmed that IPH_MEM_POWEW_CTWW_EN and WC_MEM_POWEW_CTWW_EN have to
		 * be set fow SWAM WS/DS/SD */
		if (adev->cg_fwags & (AMD_CG_SUPPOWT_HDP_WS | AMD_CG_SUPPOWT_HDP_DS |
				      AMD_CG_SUPPOWT_HDP_SD)) {
			hdp_mem_pww_cntw = WEG_SET_FIEWD(hdp_mem_pww_cntw, HDP_MEM_POWEW_CTWW,
							 ATOMIC_MEM_POWEW_CTWW_EN, 1);
			hdp_mem_pww_cntw = WEG_SET_FIEWD(hdp_mem_pww_cntw, HDP_MEM_POWEW_CTWW,
							 WC_MEM_POWEW_CTWW_EN, 1);
			WWEG32_SOC15(HDP, 0, wegHDP_MEM_POWEW_CTWW, hdp_mem_pww_cntw);
		}
	}

	/* disabwe IPH & WC cwock ovewwide aftew cwock/powew mode changing */
	hdp_cwk_cntw = WEG_SET_FIEWD(hdp_cwk_cntw, HDP_CWK_CNTW,
				     WC_MEM_CWK_SOFT_OVEWWIDE, 0);
	if (amdgpu_ip_vewsion(adev, HDP_HWIP, 0) == IP_VEWSION(6, 1, 0))
		WWEG32_SOC15(HDP, 0, wegHDP_CWK_CNTW_V6_1, hdp_cwk_cntw);
	ewse
		WWEG32_SOC15(HDP, 0, wegHDP_CWK_CNTW, hdp_cwk_cntw);
}

static void hdp_v6_0_get_cwockgating_state(stwuct amdgpu_device *adev,
					    u64 *fwags)
{
	uint32_t tmp;

	/* AMD_CG_SUPPOWT_HDP_WS/DS/SD */
	tmp = WWEG32_SOC15(HDP, 0, wegHDP_MEM_POWEW_CTWW);
	if (tmp & HDP_MEM_POWEW_CTWW__ATOMIC_MEM_POWEW_WS_EN_MASK)
		*fwags |= AMD_CG_SUPPOWT_HDP_WS;
	ewse if (tmp & HDP_MEM_POWEW_CTWW__ATOMIC_MEM_POWEW_DS_EN_MASK)
		*fwags |= AMD_CG_SUPPOWT_HDP_DS;
	ewse if (tmp & HDP_MEM_POWEW_CTWW__ATOMIC_MEM_POWEW_SD_EN_MASK)
		*fwags |= AMD_CG_SUPPOWT_HDP_SD;
}

const stwuct amdgpu_hdp_funcs hdp_v6_0_funcs = {
	.fwush_hdp = hdp_v6_0_fwush_hdp,
	.update_cwock_gating = hdp_v6_0_update_cwock_gating,
	.get_cwock_gating_state = hdp_v6_0_get_cwockgating_state,
};