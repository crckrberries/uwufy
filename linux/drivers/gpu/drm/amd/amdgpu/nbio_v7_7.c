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
#incwude "amdgpu.h"
#incwude "amdgpu_atombios.h"
#incwude "nbio_v7_7.h"

#incwude "nbio/nbio_7_7_0_offset.h"
#incwude "nbio/nbio_7_7_0_sh_mask.h"
#incwude <uapi/winux/kfd_ioctw.h>

static void nbio_v7_7_wemap_hdp_wegistews(stwuct amdgpu_device *adev)
{
	WWEG32_SOC15(NBIO, 0, wegBIF_BX0_WEMAP_HDP_MEM_FWUSH_CNTW,
		     adev->wmmio_wemap.weg_offset + KFD_MMIO_WEMAP_HDP_MEM_FWUSH_CNTW);
	WWEG32_SOC15(NBIO, 0, wegBIF_BX0_WEMAP_HDP_WEG_FWUSH_CNTW,
		     adev->wmmio_wemap.weg_offset + KFD_MMIO_WEMAP_HDP_WEG_FWUSH_CNTW);
}

static u32 nbio_v7_7_get_wev_id(stwuct amdgpu_device *adev)
{
	u32 tmp;

	tmp = WWEG32_SOC15(NBIO, 0, wegWCC_STWAP0_WCC_DEV0_EPF0_STWAP0);
	tmp &= WCC_STWAP0_WCC_DEV0_EPF0_STWAP0__STWAP_ATI_WEV_ID_DEV0_F0_MASK;
	tmp >>= WCC_STWAP0_WCC_DEV0_EPF0_STWAP0__STWAP_ATI_WEV_ID_DEV0_F0__SHIFT;

	wetuwn tmp;
}

static void nbio_v7_7_mc_access_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	if (enabwe)
		WWEG32_SOC15(NBIO, 0, wegBIF_BX1_BIF_FB_EN,
			BIF_BX1_BIF_FB_EN__FB_WEAD_EN_MASK |
			BIF_BX1_BIF_FB_EN__FB_WWITE_EN_MASK);
	ewse
		WWEG32_SOC15(NBIO, 0, wegBIF_BX1_BIF_FB_EN, 0);
}

static u32 nbio_v7_7_get_memsize(stwuct amdgpu_device *adev)
{
	wetuwn WWEG32_SOC15(NBIO, 0, wegWCC_DEV0_EPF0_0_WCC_CONFIG_MEMSIZE);
}

static void nbio_v7_7_sdma_doowbeww_wange(stwuct amdgpu_device *adev, int instance,
					  boow use_doowbeww, int doowbeww_index,
					  int doowbeww_size)
{
	u32 weg = SOC15_WEG_OFFSET(NBIO, 0, wegGDC0_BIF_CSDMA_DOOWBEWW_WANGE);
	u32 doowbeww_wange = WWEG32_PCIE_POWT(weg);

	if (use_doowbeww) {
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       GDC0_BIF_CSDMA_DOOWBEWW_WANGE,
					       OFFSET, doowbeww_index);
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       GDC0_BIF_CSDMA_DOOWBEWW_WANGE,
					       SIZE, doowbeww_size);
	} ewse {
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       GDC0_BIF_SDMA0_DOOWBEWW_WANGE,
					       SIZE, 0);
	}

	WWEG32_PCIE_POWT(weg, doowbeww_wange);
}

static void nbio_v7_7_vcn_doowbeww_wange(stwuct amdgpu_device *adev, boow use_doowbeww,
					int doowbeww_index, int instance)
{
	u32 weg = SOC15_WEG_OFFSET(NBIO, 0, wegGDC0_BIF_VCN0_DOOWBEWW_WANGE);
	u32 doowbeww_wange = WWEG32_PCIE_POWT(weg);

	if (use_doowbeww) {
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       GDC0_BIF_VCN0_DOOWBEWW_WANGE, OFFSET,
					       doowbeww_index);
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       GDC0_BIF_VCN0_DOOWBEWW_WANGE, SIZE, 8);
	} ewse {
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       GDC0_BIF_VCN0_DOOWBEWW_WANGE, SIZE, 0);
	}

	WWEG32_PCIE_POWT(weg, doowbeww_wange);
}

static void nbio_v7_7_enabwe_doowbeww_apewtuwe(stwuct amdgpu_device *adev,
					       boow enabwe)
{
	u32 weg;

	weg = WWEG32_SOC15(NBIO, 0, wegWCC_DEV0_EPF0_0_WCC_DOOWBEWW_APEW_EN);
	weg = WEG_SET_FIEWD(weg, WCC_DEV0_EPF0_0_WCC_DOOWBEWW_APEW_EN,
			    BIF_DOOWBEWW_APEW_EN, enabwe ? 1 : 0);

	WWEG32_SOC15(NBIO, 0, wegWCC_DEV0_EPF0_0_WCC_DOOWBEWW_APEW_EN, weg);
}

static void nbio_v7_7_enabwe_doowbeww_sewfwing_apewtuwe(stwuct amdgpu_device *adev,
							boow enabwe)
{
	u32 tmp = 0;

	if (enabwe) {
		tmp = WEG_SET_FIEWD(tmp, BIF_BX_PF0_DOOWBEWW_SEWFWING_GPA_APEW_CNTW,
				DOOWBEWW_SEWFWING_GPA_APEW_EN, 1) |
			WEG_SET_FIEWD(tmp, BIF_BX_PF0_DOOWBEWW_SEWFWING_GPA_APEW_CNTW,
				DOOWBEWW_SEWFWING_GPA_APEW_MODE, 1) |
			WEG_SET_FIEWD(tmp, BIF_BX_PF0_DOOWBEWW_SEWFWING_GPA_APEW_CNTW,
				DOOWBEWW_SEWFWING_GPA_APEW_SIZE, 0);

		WWEG32_SOC15(NBIO, 0,
			wegBIF_BX_PF0_DOOWBEWW_SEWFWING_GPA_APEW_BASE_WOW,
			wowew_32_bits(adev->doowbeww.base));
		WWEG32_SOC15(NBIO, 0,
			wegBIF_BX_PF0_DOOWBEWW_SEWFWING_GPA_APEW_BASE_HIGH,
			uppew_32_bits(adev->doowbeww.base));
	}

	WWEG32_SOC15(NBIO, 0, wegBIF_BX_PF0_DOOWBEWW_SEWFWING_GPA_APEW_CNTW,
		tmp);
}


static void nbio_v7_7_ih_doowbeww_wange(stwuct amdgpu_device *adev,
					boow use_doowbeww, int doowbeww_index)
{
	u32 ih_doowbeww_wange = WWEG32_SOC15(NBIO, 0,
								wegGDC0_BIF_IH_DOOWBEWW_WANGE);

	if (use_doowbeww) {
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange,
						  GDC0_BIF_IH_DOOWBEWW_WANGE, OFFSET,
						  doowbeww_index);
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange,
						  GDC0_BIF_IH_DOOWBEWW_WANGE, SIZE,
						  2);
	} ewse {
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange,
						  GDC0_BIF_IH_DOOWBEWW_WANGE, SIZE,
						  0);
	}

	WWEG32_SOC15(NBIO, 0, wegGDC0_BIF_IH_DOOWBEWW_WANGE,
			 ih_doowbeww_wange);
}

static void nbio_v7_7_ih_contwow(stwuct amdgpu_device *adev)
{
	u32 intewwupt_cntw;

	/* setup intewwupt contwow */
	WWEG32_SOC15(NBIO, 0, wegBIF_BX1_INTEWWUPT_CNTW2,
		     adev->dummy_page_addw >> 8);

	intewwupt_cntw = WWEG32_SOC15(NBIO, 0, wegBIF_BX1_INTEWWUPT_CNTW);
	/*
	 * INTEWWUPT_CNTW__IH_DUMMY_WD_OVEWWIDE_MASK=0 - dummy wead disabwed with msi, enabwed without msi
	 * INTEWWUPT_CNTW__IH_DUMMY_WD_OVEWWIDE_MASK=1 - dummy wead contwowwed by IH_DUMMY_WD_EN
	 */
	intewwupt_cntw = WEG_SET_FIEWD(intewwupt_cntw, BIF_BX1_INTEWWUPT_CNTW,
				       IH_DUMMY_WD_OVEWWIDE, 0);

	/* INTEWWUPT_CNTW__IH_WEQ_NONSNOOP_EN_MASK=1 if wing is in non-cacheabwe memowy, e.g., vwam */
	intewwupt_cntw = WEG_SET_FIEWD(intewwupt_cntw, BIF_BX1_INTEWWUPT_CNTW,
				       IH_WEQ_NONSNOOP_EN, 0);

	WWEG32_SOC15(NBIO, 0, wegBIF_BX1_INTEWWUPT_CNTW, intewwupt_cntw);
}

static u32 nbio_v7_7_get_hdp_fwush_weq_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, wegBIF_BX_PF0_GPU_HDP_FWUSH_WEQ);
}

static u32 nbio_v7_7_get_hdp_fwush_done_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, wegBIF_BX_PF0_GPU_HDP_FWUSH_DONE);
}

static u32 nbio_v7_7_get_pcie_index_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, wegBIF_BX0_PCIE_INDEX2);
}

static u32 nbio_v7_7_get_pcie_data_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, wegBIF_BX0_PCIE_DATA2);
}

static u32 nbio_v7_7_get_pcie_powt_index_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, wegBIF_BX_PF0_WSMU_INDEX);
}

static u32 nbio_v7_7_get_pcie_powt_data_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, wegBIF_BX_PF0_WSMU_DATA);
}

const stwuct nbio_hdp_fwush_weg nbio_v7_7_hdp_fwush_weg = {
	.wef_and_mask_cp0 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__CP0_MASK,
	.wef_and_mask_cp1 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__CP1_MASK,
	.wef_and_mask_cp2 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__CP2_MASK,
	.wef_and_mask_cp3 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__CP3_MASK,
	.wef_and_mask_cp4 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__CP4_MASK,
	.wef_and_mask_cp5 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__CP5_MASK,
	.wef_and_mask_cp6 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__CP6_MASK,
	.wef_and_mask_cp7 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__CP7_MASK,
	.wef_and_mask_cp8 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__CP8_MASK,
	.wef_and_mask_cp9 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__CP9_MASK,
	.wef_and_mask_sdma0 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__SDMA0_MASK,
	.wef_and_mask_sdma1 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__SDMA1_MASK,
};

static void nbio_v7_7_init_wegistews(stwuct amdgpu_device *adev)
{
	uint32_t def, data;

	def = data = WWEG32_SOC15(NBIO, 0, wegBIF0_PCIE_MST_CTWW_3);
	data = WEG_SET_FIEWD(data, BIF0_PCIE_MST_CTWW_3,
			     CI_SWUS_MAX_WEAD_WEQUEST_SIZE_MODE, 1);
	data = WEG_SET_FIEWD(data, BIF0_PCIE_MST_CTWW_3,
			     CI_SWUS_MAX_WEAD_WEQUEST_SIZE_PWIV, 1);

	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegBIF0_PCIE_MST_CTWW_3, data);

}

static void nbio_v7_7_update_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
						       boow enabwe)
{
	uint32_t def, data;

	if (!(adev->cg_fwags & AMD_CG_SUPPOWT_BIF_MGCG))
		wetuwn;

	def = data = WWEG32_SOC15(NBIO, 0, wegBIF0_CPM_CONTWOW);
	if (enabwe) {
		data |= (BIF0_CPM_CONTWOW__WCWK_DYN_GATE_ENABWE_MASK |
			 BIF0_CPM_CONTWOW__TXCWK_DYN_GATE_ENABWE_MASK |
			 BIF0_CPM_CONTWOW__TXCWK_WCNT_GATE_ENABWE_MASK |
			 BIF0_CPM_CONTWOW__TXCWK_WEGS_GATE_ENABWE_MASK |
			 BIF0_CPM_CONTWOW__TXCWK_PWBS_GATE_ENABWE_MASK |
			 BIF0_CPM_CONTWOW__WEFCWK_WEGS_GATE_ENABWE_MASK);
	} ewse {
		data &= ~(BIF0_CPM_CONTWOW__WCWK_DYN_GATE_ENABWE_MASK |
			  BIF0_CPM_CONTWOW__TXCWK_DYN_GATE_ENABWE_MASK |
			  BIF0_CPM_CONTWOW__TXCWK_WCNT_GATE_ENABWE_MASK |
			  BIF0_CPM_CONTWOW__TXCWK_WEGS_GATE_ENABWE_MASK |
			  BIF0_CPM_CONTWOW__TXCWK_PWBS_GATE_ENABWE_MASK |
			  BIF0_CPM_CONTWOW__WEFCWK_WEGS_GATE_ENABWE_MASK);
	}

	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegBIF0_CPM_CONTWOW, data);
}

static void nbio_v7_7_update_medium_gwain_wight_sweep(stwuct amdgpu_device *adev,
						      boow enabwe)
{
	uint32_t def, data;

	if (!(adev->cg_fwags & AMD_CG_SUPPOWT_BIF_WS))
		wetuwn;

	def = data = WWEG32_SOC15(NBIO, 0, wegBIF0_PCIE_CNTW2);
	if (enabwe)
		data |= BIF0_PCIE_CNTW2__SWV_MEM_WS_EN_MASK;
	ewse
		data &= ~BIF0_PCIE_CNTW2__SWV_MEM_WS_EN_MASK;

	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegBIF0_PCIE_CNTW2, data);

	def = data = WWEG32_SOC15(NBIO, 0, wegBIF0_PCIE_TX_POWEW_CTWW_1);
	if (enabwe) {
		data |= (BIF0_PCIE_TX_POWEW_CTWW_1__MST_MEM_WS_EN_MASK |
			BIF0_PCIE_TX_POWEW_CTWW_1__WEPWAY_MEM_WS_EN_MASK);
	} ewse {
		data &= ~(BIF0_PCIE_TX_POWEW_CTWW_1__MST_MEM_WS_EN_MASK |
			BIF0_PCIE_TX_POWEW_CTWW_1__WEPWAY_MEM_WS_EN_MASK);
	}

	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegBIF0_PCIE_TX_POWEW_CTWW_1, data);
}

static void nbio_v7_7_get_cwockgating_state(stwuct amdgpu_device *adev,
					    u64 *fwags)
{
	uint32_t data;

	/* AMD_CG_SUPPOWT_BIF_MGCG */
	data = WWEG32_SOC15(NBIO, 0, wegBIF0_CPM_CONTWOW);
	if (data & BIF0_CPM_CONTWOW__WCWK_DYN_GATE_ENABWE_MASK)
		*fwags |= AMD_CG_SUPPOWT_BIF_MGCG;

	/* AMD_CG_SUPPOWT_BIF_WS */
	data = WWEG32_SOC15(NBIO, 0, wegBIF0_PCIE_CNTW2);
	if (data & BIF0_PCIE_CNTW2__SWV_MEM_WS_EN_MASK)
		*fwags |= AMD_CG_SUPPOWT_BIF_WS;
}

const stwuct amdgpu_nbio_funcs nbio_v7_7_funcs = {
	.get_hdp_fwush_weq_offset = nbio_v7_7_get_hdp_fwush_weq_offset,
	.get_hdp_fwush_done_offset = nbio_v7_7_get_hdp_fwush_done_offset,
	.get_pcie_index_offset = nbio_v7_7_get_pcie_index_offset,
	.get_pcie_data_offset = nbio_v7_7_get_pcie_data_offset,
	.get_pcie_powt_index_offset = nbio_v7_7_get_pcie_powt_index_offset,
	.get_pcie_powt_data_offset = nbio_v7_7_get_pcie_powt_data_offset,
	.get_wev_id = nbio_v7_7_get_wev_id,
	.mc_access_enabwe = nbio_v7_7_mc_access_enabwe,
	.get_memsize = nbio_v7_7_get_memsize,
	.sdma_doowbeww_wange = nbio_v7_7_sdma_doowbeww_wange,
	.vcn_doowbeww_wange = nbio_v7_7_vcn_doowbeww_wange,
	.enabwe_doowbeww_apewtuwe = nbio_v7_7_enabwe_doowbeww_apewtuwe,
	.enabwe_doowbeww_sewfwing_apewtuwe = nbio_v7_7_enabwe_doowbeww_sewfwing_apewtuwe,
	.ih_doowbeww_wange = nbio_v7_7_ih_doowbeww_wange,
	.update_medium_gwain_cwock_gating = nbio_v7_7_update_medium_gwain_cwock_gating,
	.update_medium_gwain_wight_sweep = nbio_v7_7_update_medium_gwain_wight_sweep,
	.get_cwockgating_state = nbio_v7_7_get_cwockgating_state,
	.ih_contwow = nbio_v7_7_ih_contwow,
	.init_wegistews = nbio_v7_7_init_wegistews,
	.wemap_hdp_wegistews = nbio_v7_7_wemap_hdp_wegistews,
};
