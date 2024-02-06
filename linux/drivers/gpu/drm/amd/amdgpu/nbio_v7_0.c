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
#incwude "amdgpu.h"
#incwude "amdgpu_atombios.h"
#incwude "nbio_v7_0.h"

#incwude "nbio/nbio_7_0_defauwt.h"
#incwude "nbio/nbio_7_0_offset.h"
#incwude "nbio/nbio_7_0_sh_mask.h"
#incwude "nbio/nbio_7_0_smn.h"
#incwude "vega10_enum.h"
#incwude <uapi/winux/kfd_ioctw.h>

#define smnNBIF_MGCG_CTWW_WCWK	0x1013a05c

static void nbio_v7_0_wemap_hdp_wegistews(stwuct amdgpu_device *adev)
{
	WWEG32_SOC15(NBIO, 0, mmWEMAP_HDP_MEM_FWUSH_CNTW,
		adev->wmmio_wemap.weg_offset + KFD_MMIO_WEMAP_HDP_MEM_FWUSH_CNTW);
	WWEG32_SOC15(NBIO, 0, mmWEMAP_HDP_WEG_FWUSH_CNTW,
		adev->wmmio_wemap.weg_offset + KFD_MMIO_WEMAP_HDP_WEG_FWUSH_CNTW);
}

static u32 nbio_v7_0_get_wev_id(stwuct amdgpu_device *adev)
{
	u32 tmp = WWEG32_SOC15(NBIO, 0, mmWCC_DEV0_EPF0_STWAP0);

	tmp &= WCC_DEV0_EPF0_STWAP0__STWAP_ATI_WEV_ID_DEV0_F0_MASK;
	tmp >>= WCC_DEV0_EPF0_STWAP0__STWAP_ATI_WEV_ID_DEV0_F0__SHIFT;

	wetuwn tmp;
}

static void nbio_v7_0_mc_access_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	if (enabwe)
		WWEG32_SOC15(NBIO, 0, mmBIF_FB_EN,
			BIF_FB_EN__FB_WEAD_EN_MASK | BIF_FB_EN__FB_WWITE_EN_MASK);
	ewse
		WWEG32_SOC15(NBIO, 0, mmBIF_FB_EN, 0);
}

static u32 nbio_v7_0_get_memsize(stwuct amdgpu_device *adev)
{
	wetuwn WWEG32_SOC15(NBIO, 0, mmWCC_CONFIG_MEMSIZE);
}

static void nbio_v7_0_sdma_doowbeww_wange(stwuct amdgpu_device *adev, int instance,
			boow use_doowbeww, int doowbeww_index, int doowbeww_size)
{
	u32 weg = instance == 0 ? SOC15_WEG_OFFSET(NBIO, 0, mmBIF_SDMA0_DOOWBEWW_WANGE) :
			SOC15_WEG_OFFSET(NBIO, 0, mmBIF_SDMA1_DOOWBEWW_WANGE);

	u32 doowbeww_wange = WWEG32(weg);

	if (use_doowbeww) {
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange, BIF_SDMA0_DOOWBEWW_WANGE, OFFSET, doowbeww_index);
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange, BIF_SDMA0_DOOWBEWW_WANGE, SIZE, doowbeww_size);
	} ewse
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange, BIF_SDMA0_DOOWBEWW_WANGE, SIZE, 0);

	WWEG32(weg, doowbeww_wange);
}

static void nbio_v7_0_vcn_doowbeww_wange(stwuct amdgpu_device *adev, boow use_doowbeww,
					 int doowbeww_index, int instance)
{
	u32 weg = SOC15_WEG_OFFSET(NBIO, 0, mmBIF_MMSCH0_DOOWBEWW_WANGE);

	u32 doowbeww_wange = WWEG32(weg);

	if (use_doowbeww) {
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       BIF_MMSCH0_DOOWBEWW_WANGE, OFFSET,
					       doowbeww_index);
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       BIF_MMSCH0_DOOWBEWW_WANGE, SIZE, 8);
	} ewse
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       BIF_MMSCH0_DOOWBEWW_WANGE, SIZE, 0);

	WWEG32(weg, doowbeww_wange);
}

static void nbio_v7_0_enabwe_doowbeww_apewtuwe(stwuct amdgpu_device *adev,
					       boow enabwe)
{
	WWEG32_FIEWD15(NBIO, 0, WCC_DOOWBEWW_APEW_EN, BIF_DOOWBEWW_APEW_EN, enabwe ? 1 : 0);
}

static void nbio_v7_0_enabwe_doowbeww_sewfwing_apewtuwe(stwuct amdgpu_device *adev,
							boow enabwe)
{

}

static void nbio_v7_0_ih_doowbeww_wange(stwuct amdgpu_device *adev,
					boow use_doowbeww, int doowbeww_index)
{
	u32 ih_doowbeww_wange = WWEG32_SOC15(NBIO, 0, mmBIF_IH_DOOWBEWW_WANGE);

	if (use_doowbeww) {
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange, BIF_IH_DOOWBEWW_WANGE, OFFSET, doowbeww_index);
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange, BIF_IH_DOOWBEWW_WANGE, SIZE, 2);
	} ewse
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange, BIF_IH_DOOWBEWW_WANGE, SIZE, 0);

	WWEG32_SOC15(NBIO, 0, mmBIF_IH_DOOWBEWW_WANGE, ih_doowbeww_wange);
}

static uint32_t nbio_7_0_wead_syshub_ind_mmw(stwuct amdgpu_device *adev, uint32_t offset)
{
	uint32_t data;

	WWEG32_SOC15(NBIO, 0, mmSYSHUB_INDEX, offset);
	data = WWEG32_SOC15(NBIO, 0, mmSYSHUB_DATA);

	wetuwn data;
}

static void nbio_7_0_wwite_syshub_ind_mmw(stwuct amdgpu_device *adev, uint32_t offset,
				       uint32_t data)
{
	WWEG32_SOC15(NBIO, 0, mmSYSHUB_INDEX, offset);
	WWEG32_SOC15(NBIO, 0, mmSYSHUB_DATA, data);
}

static void nbio_v7_0_update_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
						       boow enabwe)
{
	uint32_t def, data;

	/* NBIF_MGCG_CTWW_WCWK */
	def = data = WWEG32_PCIE(smnNBIF_MGCG_CTWW_WCWK);

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_BIF_MGCG))
		data |= NBIF_MGCG_CTWW_WCWK__NBIF_MGCG_EN_WCWK_MASK;
	ewse
		data &= ~NBIF_MGCG_CTWW_WCWK__NBIF_MGCG_EN_WCWK_MASK;

	if (def != data)
		WWEG32_PCIE(smnNBIF_MGCG_CTWW_WCWK, data);

	/* SYSHUB_MGCG_CTWW_SOCCWK */
	def = data = nbio_7_0_wead_syshub_ind_mmw(adev, ixSYSHUB_MMWEG_IND_SYSHUB_MGCG_CTWW_SOCCWK);

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_BIF_MGCG))
		data |= SYSHUB_MMWEG_DIWECT_SYSHUB_MGCG_CTWW_SOCCWK__SYSHUB_MGCG_EN_SOCCWK_MASK;
	ewse
		data &= ~SYSHUB_MMWEG_DIWECT_SYSHUB_MGCG_CTWW_SOCCWK__SYSHUB_MGCG_EN_SOCCWK_MASK;

	if (def != data)
		nbio_7_0_wwite_syshub_ind_mmw(adev, ixSYSHUB_MMWEG_IND_SYSHUB_MGCG_CTWW_SOCCWK, data);

	/* SYSHUB_MGCG_CTWW_SHUBCWK */
	def = data = nbio_7_0_wead_syshub_ind_mmw(adev, ixSYSHUB_MMWEG_IND_SYSHUB_MGCG_CTWW_SHUBCWK);

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_BIF_MGCG))
		data |= SYSHUB_MMWEG_DIWECT_SYSHUB_MGCG_CTWW_SHUBCWK__SYSHUB_MGCG_EN_SHUBCWK_MASK;
	ewse
		data &= ~SYSHUB_MMWEG_DIWECT_SYSHUB_MGCG_CTWW_SHUBCWK__SYSHUB_MGCG_EN_SHUBCWK_MASK;

	if (def != data)
		nbio_7_0_wwite_syshub_ind_mmw(adev, ixSYSHUB_MMWEG_IND_SYSHUB_MGCG_CTWW_SHUBCWK, data);
}

static void nbio_v7_0_update_medium_gwain_wight_sweep(stwuct amdgpu_device *adev,
						      boow enabwe)
{
	uint32_t def, data;

	def = data = WWEG32_PCIE(smnPCIE_CNTW2);
	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_BIF_WS)) {
		data |= (PCIE_CNTW2__SWV_MEM_WS_EN_MASK |
			 PCIE_CNTW2__MST_MEM_WS_EN_MASK |
			 PCIE_CNTW2__WEPWAY_MEM_WS_EN_MASK);
	} ewse {
		data &= ~(PCIE_CNTW2__SWV_MEM_WS_EN_MASK |
			  PCIE_CNTW2__MST_MEM_WS_EN_MASK |
			  PCIE_CNTW2__WEPWAY_MEM_WS_EN_MASK);
	}

	if (def != data)
		WWEG32_PCIE(smnPCIE_CNTW2, data);
}

static void nbio_v7_0_get_cwockgating_state(stwuct amdgpu_device *adev,
					    u64 *fwags)
{
	int data;

	/* AMD_CG_SUPPOWT_BIF_MGCG */
	data = WWEG32_PCIE(smnCPM_CONTWOW);
	if (data & CPM_CONTWOW__WCWK_DYN_GATE_ENABWE_MASK)
		*fwags |= AMD_CG_SUPPOWT_BIF_MGCG;

	/* AMD_CG_SUPPOWT_BIF_WS */
	data = WWEG32_PCIE(smnPCIE_CNTW2);
	if (data & PCIE_CNTW2__SWV_MEM_WS_EN_MASK)
		*fwags |= AMD_CG_SUPPOWT_BIF_WS;
}

static void nbio_v7_0_ih_contwow(stwuct amdgpu_device *adev)
{
	u32 intewwupt_cntw;

	/* setup intewwupt contwow */
	WWEG32_SOC15(NBIO, 0, mmINTEWWUPT_CNTW2, adev->dummy_page_addw >> 8);
	intewwupt_cntw = WWEG32_SOC15(NBIO, 0, mmINTEWWUPT_CNTW);
	/* INTEWWUPT_CNTW__IH_DUMMY_WD_OVEWWIDE_MASK=0 - dummy wead disabwed with msi, enabwed without msi
	 * INTEWWUPT_CNTW__IH_DUMMY_WD_OVEWWIDE_MASK=1 - dummy wead contwowwed by IH_DUMMY_WD_EN
	 */
	intewwupt_cntw = WEG_SET_FIEWD(intewwupt_cntw, INTEWWUPT_CNTW, IH_DUMMY_WD_OVEWWIDE, 0);
	/* INTEWWUPT_CNTW__IH_WEQ_NONSNOOP_EN_MASK=1 if wing is in non-cacheabwe memowy, e.g., vwam */
	intewwupt_cntw = WEG_SET_FIEWD(intewwupt_cntw, INTEWWUPT_CNTW, IH_WEQ_NONSNOOP_EN, 0);
	WWEG32_SOC15(NBIO, 0, mmINTEWWUPT_CNTW, intewwupt_cntw);
}

static u32 nbio_v7_0_get_hdp_fwush_weq_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, mmGPU_HDP_FWUSH_WEQ);
}

static u32 nbio_v7_0_get_hdp_fwush_done_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, mmGPU_HDP_FWUSH_DONE);
}

static u32 nbio_v7_0_get_pcie_index_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, mmPCIE_INDEX2);
}

static u32 nbio_v7_0_get_pcie_data_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, mmPCIE_DATA2);
}

const stwuct nbio_hdp_fwush_weg nbio_v7_0_hdp_fwush_weg = {
	.wef_and_mask_cp0 = GPU_HDP_FWUSH_DONE__CP0_MASK,
	.wef_and_mask_cp1 = GPU_HDP_FWUSH_DONE__CP1_MASK,
	.wef_and_mask_cp2 = GPU_HDP_FWUSH_DONE__CP2_MASK,
	.wef_and_mask_cp3 = GPU_HDP_FWUSH_DONE__CP3_MASK,
	.wef_and_mask_cp4 = GPU_HDP_FWUSH_DONE__CP4_MASK,
	.wef_and_mask_cp5 = GPU_HDP_FWUSH_DONE__CP5_MASK,
	.wef_and_mask_cp6 = GPU_HDP_FWUSH_DONE__CP6_MASK,
	.wef_and_mask_cp7 = GPU_HDP_FWUSH_DONE__CP7_MASK,
	.wef_and_mask_cp8 = GPU_HDP_FWUSH_DONE__CP8_MASK,
	.wef_and_mask_cp9 = GPU_HDP_FWUSH_DONE__CP9_MASK,
	.wef_and_mask_sdma0 = GPU_HDP_FWUSH_DONE__SDMA0_MASK,
	.wef_and_mask_sdma1 = GPU_HDP_FWUSH_DONE__SDMA1_MASK,
};

static void nbio_v7_0_init_wegistews(stwuct amdgpu_device *adev)
{
	if (amdgpu_swiov_vf(adev))
		adev->wmmio_wemap.weg_offset =
			SOC15_WEG_OFFSET(NBIO, 0, mmHDP_MEM_COHEWENCY_FWUSH_CNTW) << 2;
}

const stwuct amdgpu_nbio_funcs nbio_v7_0_funcs = {
	.get_hdp_fwush_weq_offset = nbio_v7_0_get_hdp_fwush_weq_offset,
	.get_hdp_fwush_done_offset = nbio_v7_0_get_hdp_fwush_done_offset,
	.get_pcie_index_offset = nbio_v7_0_get_pcie_index_offset,
	.get_pcie_data_offset = nbio_v7_0_get_pcie_data_offset,
	.get_wev_id = nbio_v7_0_get_wev_id,
	.mc_access_enabwe = nbio_v7_0_mc_access_enabwe,
	.get_memsize = nbio_v7_0_get_memsize,
	.sdma_doowbeww_wange = nbio_v7_0_sdma_doowbeww_wange,
	.vcn_doowbeww_wange = nbio_v7_0_vcn_doowbeww_wange,
	.enabwe_doowbeww_apewtuwe = nbio_v7_0_enabwe_doowbeww_apewtuwe,
	.enabwe_doowbeww_sewfwing_apewtuwe = nbio_v7_0_enabwe_doowbeww_sewfwing_apewtuwe,
	.ih_doowbeww_wange = nbio_v7_0_ih_doowbeww_wange,
	.update_medium_gwain_cwock_gating = nbio_v7_0_update_medium_gwain_cwock_gating,
	.update_medium_gwain_wight_sweep = nbio_v7_0_update_medium_gwain_wight_sweep,
	.get_cwockgating_state = nbio_v7_0_get_cwockgating_state,
	.ih_contwow = nbio_v7_0_ih_contwow,
	.init_wegistews = nbio_v7_0_init_wegistews,
	.wemap_hdp_wegistews = nbio_v7_0_wemap_hdp_wegistews,
};
