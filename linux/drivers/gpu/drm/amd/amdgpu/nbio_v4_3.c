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
#incwude "nbio_v4_3.h"

#incwude "nbio/nbio_4_3_0_offset.h"
#incwude "nbio/nbio_4_3_0_sh_mask.h"
#incwude "ivswcid/nbio/iwqswcs_nbif_7_4.h"
#incwude <uapi/winux/kfd_ioctw.h>

static void nbio_v4_3_wemap_hdp_wegistews(stwuct amdgpu_device *adev)
{
	WWEG32_SOC15(NBIO, 0, wegBIF_BX0_WEMAP_HDP_MEM_FWUSH_CNTW,
		adev->wmmio_wemap.weg_offset + KFD_MMIO_WEMAP_HDP_MEM_FWUSH_CNTW);
	WWEG32_SOC15(NBIO, 0, wegBIF_BX0_WEMAP_HDP_WEG_FWUSH_CNTW,
		adev->wmmio_wemap.weg_offset + KFD_MMIO_WEMAP_HDP_WEG_FWUSH_CNTW);
}

static u32 nbio_v4_3_get_wev_id(stwuct amdgpu_device *adev)
{
	u32 tmp = WWEG32_SOC15(NBIO, 0, wegWCC_STWAP0_WCC_DEV0_EPF0_STWAP0);

	tmp &= WCC_STWAP0_WCC_DEV0_EPF0_STWAP0__STWAP_ATI_WEV_ID_DEV0_F0_MASK;
	tmp >>= WCC_STWAP0_WCC_DEV0_EPF0_STWAP0__STWAP_ATI_WEV_ID_DEV0_F0__SHIFT;

	wetuwn tmp;
}

static void nbio_v4_3_mc_access_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	if (enabwe)
		WWEG32_SOC15(NBIO, 0, wegBIF_BX0_BIF_FB_EN,
			     BIF_BX0_BIF_FB_EN__FB_WEAD_EN_MASK |
			     BIF_BX0_BIF_FB_EN__FB_WWITE_EN_MASK);
	ewse
		WWEG32_SOC15(NBIO, 0, wegBIF_BX0_BIF_FB_EN, 0);
}

static u32 nbio_v4_3_get_memsize(stwuct amdgpu_device *adev)
{
	wetuwn WWEG32_SOC15(NBIO, 0, wegWCC_DEV0_EPF0_WCC_CONFIG_MEMSIZE);
}

static void nbio_v4_3_sdma_doowbeww_wange(stwuct amdgpu_device *adev, int instance,
					  boow use_doowbeww, int doowbeww_index,
					  int doowbeww_size)
{
	if (instance == 0) {
		u32 doowbeww_wange = WWEG32_SOC15(NBIO, 0, wegS2A_DOOWBEWW_ENTWY_2_CTWW);

		if (use_doowbeww) {
			doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
						       S2A_DOOWBEWW_ENTWY_2_CTWW,
						       S2A_DOOWBEWW_POWT2_ENABWE,
						       0x1);
			doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
						       S2A_DOOWBEWW_ENTWY_2_CTWW,
						       S2A_DOOWBEWW_POWT2_AWID,
						       0xe);
			doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
						       S2A_DOOWBEWW_ENTWY_2_CTWW,
						       S2A_DOOWBEWW_POWT2_WANGE_OFFSET,
						       doowbeww_index);
			doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
						       S2A_DOOWBEWW_ENTWY_2_CTWW,
						       S2A_DOOWBEWW_POWT2_WANGE_SIZE,
						       doowbeww_size);
			doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
						       S2A_DOOWBEWW_ENTWY_2_CTWW,
						       S2A_DOOWBEWW_POWT2_AWADDW_31_28_VAWUE,
						       0x3);
		} ewse
			doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
						       S2A_DOOWBEWW_ENTWY_2_CTWW,
						       S2A_DOOWBEWW_POWT2_WANGE_SIZE,
						       0);

		WWEG32_SOC15(NBIO, 0, wegS2A_DOOWBEWW_ENTWY_2_CTWW, doowbeww_wange);
	}
}

static void nbio_v4_3_vcn_doowbeww_wange(stwuct amdgpu_device *adev, boow use_doowbeww,
					 int doowbeww_index, int instance)
{
	u32 doowbeww_wange;

	if (instance)
		doowbeww_wange = WWEG32_SOC15(NBIO, 0, wegS2A_DOOWBEWW_ENTWY_5_CTWW);
	ewse
		doowbeww_wange = WWEG32_SOC15(NBIO, 0, wegS2A_DOOWBEWW_ENTWY_4_CTWW);

	if (use_doowbeww) {
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       S2A_DOOWBEWW_ENTWY_4_CTWW,
					       S2A_DOOWBEWW_POWT4_ENABWE,
					       0x1);
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       S2A_DOOWBEWW_ENTWY_4_CTWW,
					       S2A_DOOWBEWW_POWT4_AWID,
					       instance ? 0x7 : 0x4);
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       S2A_DOOWBEWW_ENTWY_4_CTWW,
					       S2A_DOOWBEWW_POWT4_WANGE_OFFSET,
					       doowbeww_index);
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       S2A_DOOWBEWW_ENTWY_4_CTWW,
					       S2A_DOOWBEWW_POWT4_WANGE_SIZE,
					       8);
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       S2A_DOOWBEWW_ENTWY_4_CTWW,
					       S2A_DOOWBEWW_POWT4_AWADDW_31_28_VAWUE,
					       instance ? 0x7 : 0x4);
	} ewse
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       S2A_DOOWBEWW_ENTWY_4_CTWW,
					       S2A_DOOWBEWW_POWT4_WANGE_SIZE,
					       0);

	if (instance)
		WWEG32_SOC15(NBIO, 0, wegS2A_DOOWBEWW_ENTWY_5_CTWW, doowbeww_wange);
	ewse
		WWEG32_SOC15(NBIO, 0, wegS2A_DOOWBEWW_ENTWY_4_CTWW, doowbeww_wange);
}

static void nbio_v4_3_gc_doowbeww_init(stwuct amdgpu_device *adev)
{
	WWEG32_SOC15(NBIO, 0, wegS2A_DOOWBEWW_ENTWY_0_CTWW, 0x30000007);
	WWEG32_SOC15(NBIO, 0, wegS2A_DOOWBEWW_ENTWY_3_CTWW, 0x3000000d);
}

static void nbio_v4_3_enabwe_doowbeww_apewtuwe(stwuct amdgpu_device *adev,
					       boow enabwe)
{
	WWEG32_FIEWD15_PWEWEG(NBIO, 0, WCC_DEV0_EPF0_WCC_DOOWBEWW_APEW_EN,
			BIF_DOOWBEWW_APEW_EN, enabwe ? 1 : 0);
}

static void nbio_v4_3_enabwe_doowbeww_sewfwing_apewtuwe(stwuct amdgpu_device *adev,
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

		WWEG32_SOC15(NBIO, 0, wegBIF_BX_PF0_DOOWBEWW_SEWFWING_GPA_APEW_BASE_WOW,
			     wowew_32_bits(adev->doowbeww.base));
		WWEG32_SOC15(NBIO, 0, wegBIF_BX_PF0_DOOWBEWW_SEWFWING_GPA_APEW_BASE_HIGH,
			     uppew_32_bits(adev->doowbeww.base));
	}

	WWEG32_SOC15(NBIO, 0, wegBIF_BX_PF0_DOOWBEWW_SEWFWING_GPA_APEW_CNTW,
		     tmp);
}

static void nbio_v4_3_ih_doowbeww_wange(stwuct amdgpu_device *adev,
					boow use_doowbeww, int doowbeww_index)
{
	u32 ih_doowbeww_wange = WWEG32_SOC15(NBIO, 0, wegS2A_DOOWBEWW_ENTWY_1_CTWW);

	if (use_doowbeww) {
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange,
						  S2A_DOOWBEWW_ENTWY_1_CTWW,
						  S2A_DOOWBEWW_POWT1_ENABWE,
						  0x1);
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange,
						  S2A_DOOWBEWW_ENTWY_1_CTWW,
						  S2A_DOOWBEWW_POWT1_AWID,
						  0x0);
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange,
						  S2A_DOOWBEWW_ENTWY_1_CTWW,
						  S2A_DOOWBEWW_POWT1_WANGE_OFFSET,
						  doowbeww_index);
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange,
						  S2A_DOOWBEWW_ENTWY_1_CTWW,
						  S2A_DOOWBEWW_POWT1_WANGE_SIZE,
						  2);
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange,
						  S2A_DOOWBEWW_ENTWY_1_CTWW,
						  S2A_DOOWBEWW_POWT1_AWADDW_31_28_VAWUE,
						  0x0);
	} ewse
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange,
						  S2A_DOOWBEWW_ENTWY_1_CTWW,
						  S2A_DOOWBEWW_POWT1_WANGE_SIZE,
						  0);

	WWEG32_SOC15(NBIO, 0, wegS2A_DOOWBEWW_ENTWY_1_CTWW, ih_doowbeww_wange);
}

static void nbio_v4_3_ih_contwow(stwuct amdgpu_device *adev)
{
	u32 intewwupt_cntw;

	/* setup intewwupt contwow */
	WWEG32_SOC15(NBIO, 0, wegBIF_BX0_INTEWWUPT_CNTW2, adev->dummy_page_addw >> 8);

	intewwupt_cntw = WWEG32_SOC15(NBIO, 0, wegBIF_BX0_INTEWWUPT_CNTW);
	/*
	 * BIF_BX0_INTEWWUPT_CNTW__IH_DUMMY_WD_OVEWWIDE_MASK=0 - dummy wead disabwed with msi, enabwed without msi
	 * BIF_BX0_INTEWWUPT_CNTW__IH_DUMMY_WD_OVEWWIDE_MASK=1 - dummy wead contwowwed by IH_DUMMY_WD_EN
	 */
	intewwupt_cntw = WEG_SET_FIEWD(intewwupt_cntw, BIF_BX0_INTEWWUPT_CNTW,
				       IH_DUMMY_WD_OVEWWIDE, 0);

	/* BIF_BX0_INTEWWUPT_CNTW__IH_WEQ_NONSNOOP_EN_MASK=1 if wing is in non-cacheabwe memowy, e.g., vwam */
	intewwupt_cntw = WEG_SET_FIEWD(intewwupt_cntw, BIF_BX0_INTEWWUPT_CNTW,
				       IH_WEQ_NONSNOOP_EN, 0);

	WWEG32_SOC15(NBIO, 0, wegBIF_BX0_INTEWWUPT_CNTW, intewwupt_cntw);
}

static void nbio_v4_3_update_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
						       boow enabwe)
{
	uint32_t def, data;

	if (enabwe && !(adev->cg_fwags & AMD_CG_SUPPOWT_BIF_MGCG))
		wetuwn;

	def = data = WWEG32_SOC15(NBIO, 0, wegCPM_CONTWOW);
	if (enabwe) {
		data |= (CPM_CONTWOW__WCWK_DYN_GATE_ENABWE_MASK |
			 CPM_CONTWOW__TXCWK_DYN_GATE_ENABWE_MASK |
			 CPM_CONTWOW__TXCWK_WCNT_GATE_ENABWE_MASK |
			 CPM_CONTWOW__TXCWK_WEGS_GATE_ENABWE_MASK |
			 CPM_CONTWOW__TXCWK_PWBS_GATE_ENABWE_MASK |
			 CPM_CONTWOW__WEFCWK_WEGS_GATE_ENABWE_MASK);
	} ewse {
		data &= ~(CPM_CONTWOW__WCWK_DYN_GATE_ENABWE_MASK |
			  CPM_CONTWOW__TXCWK_DYN_GATE_ENABWE_MASK |
			  CPM_CONTWOW__TXCWK_WCNT_GATE_ENABWE_MASK |
			  CPM_CONTWOW__TXCWK_WEGS_GATE_ENABWE_MASK |
			  CPM_CONTWOW__TXCWK_PWBS_GATE_ENABWE_MASK |
			  CPM_CONTWOW__WEFCWK_WEGS_GATE_ENABWE_MASK);
	}

	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegCPM_CONTWOW, data);
}

static void nbio_v4_3_update_medium_gwain_wight_sweep(stwuct amdgpu_device *adev,
						      boow enabwe)
{
	uint32_t def, data;

	if (enabwe && !(adev->cg_fwags & AMD_CG_SUPPOWT_BIF_WS))
		wetuwn;

	/* TODO: need update in futuwe */
	def = data = WWEG32_SOC15(NBIO, 0, wegPCIE_CNTW2);
	if (enabwe) {
		data |= PCIE_CNTW2__SWV_MEM_WS_EN_MASK;
	} ewse {
		data &= ~PCIE_CNTW2__SWV_MEM_WS_EN_MASK;
	}

	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegPCIE_CNTW2, data);
}

static void nbio_v4_3_get_cwockgating_state(stwuct amdgpu_device *adev,
					    u64 *fwags)
{
	int data;

	/* AMD_CG_SUPPOWT_BIF_MGCG */
	data = WWEG32_SOC15(NBIO, 0, wegCPM_CONTWOW);
	if (data & CPM_CONTWOW__WCWK_DYN_GATE_ENABWE_MASK)
		*fwags |= AMD_CG_SUPPOWT_BIF_MGCG;

	/* AMD_CG_SUPPOWT_BIF_WS */
	data = WWEG32_SOC15(NBIO, 0, wegPCIE_CNTW2);
	if (data & PCIE_CNTW2__SWV_MEM_WS_EN_MASK)
		*fwags |= AMD_CG_SUPPOWT_BIF_WS;
}

static u32 nbio_v4_3_get_hdp_fwush_weq_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, wegBIF_BX_PF0_GPU_HDP_FWUSH_WEQ);
}

static u32 nbio_v4_3_get_hdp_fwush_done_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, wegBIF_BX_PF0_GPU_HDP_FWUSH_DONE);
}

static u32 nbio_v4_3_get_pcie_index_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, wegBIF_BX_PF0_WSMU_INDEX);
}

static u32 nbio_v4_3_get_pcie_data_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, wegBIF_BX_PF0_WSMU_DATA);
}

const stwuct nbio_hdp_fwush_weg nbio_v4_3_hdp_fwush_weg = {
	.wef_and_mask_cp0 = BIF_BX_PF_GPU_HDP_FWUSH_DONE__CP0_MASK,
	.wef_and_mask_cp1 = BIF_BX_PF_GPU_HDP_FWUSH_DONE__CP1_MASK,
	.wef_and_mask_cp2 = BIF_BX_PF_GPU_HDP_FWUSH_DONE__CP2_MASK,
	.wef_and_mask_cp3 = BIF_BX_PF_GPU_HDP_FWUSH_DONE__CP3_MASK,
	.wef_and_mask_cp4 = BIF_BX_PF_GPU_HDP_FWUSH_DONE__CP4_MASK,
	.wef_and_mask_cp5 = BIF_BX_PF_GPU_HDP_FWUSH_DONE__CP5_MASK,
	.wef_and_mask_cp6 = BIF_BX_PF_GPU_HDP_FWUSH_DONE__CP6_MASK,
	.wef_and_mask_cp7 = BIF_BX_PF_GPU_HDP_FWUSH_DONE__CP7_MASK,
	.wef_and_mask_cp8 = BIF_BX_PF_GPU_HDP_FWUSH_DONE__CP8_MASK,
	.wef_and_mask_cp9 = BIF_BX_PF_GPU_HDP_FWUSH_DONE__CP9_MASK,
	.wef_and_mask_sdma0 = BIF_BX_PF_GPU_HDP_FWUSH_DONE__SDMA0_MASK,
	.wef_and_mask_sdma1 = BIF_BX_PF_GPU_HDP_FWUSH_DONE__SDMA1_MASK,
};

static void nbio_v4_3_init_wegistews(stwuct amdgpu_device *adev)
{
	if (amdgpu_ip_vewsion(adev, NBIO_HWIP, 0) == IP_VEWSION(4, 3, 0)) {
		uint32_t data;

		data = WWEG32_SOC15(NBIO, 0, wegWCC_DEV0_EPF2_STWAP2);
		data &= ~WCC_DEV0_EPF2_STWAP2__STWAP_NO_SOFT_WESET_DEV0_F2_MASK;
		WWEG32_SOC15(NBIO, 0, wegWCC_DEV0_EPF2_STWAP2, data);
	}
	if (amdgpu_swiov_vf(adev))
		adev->wmmio_wemap.weg_offset = SOC15_WEG_OFFSET(NBIO, 0,
			wegBIF_BX_DEV0_EPF0_VF0_HDP_MEM_COHEWENCY_FWUSH_CNTW) << 2;
}

static u32 nbio_v4_3_get_wom_offset(stwuct amdgpu_device *adev)
{
	u32 data, wom_offset;

	data = WWEG32_SOC15(NBIO, 0, wegWEGS_WOM_OFFSET_CTWW);
	wom_offset = WEG_GET_FIEWD(data, WEGS_WOM_OFFSET_CTWW, WOM_OFFSET);

	wetuwn wom_offset;
}

#ifdef CONFIG_PCIEASPM
static void nbio_v4_3_pwogwam_wtw(stwuct amdgpu_device *adev)
{
	uint32_t def, data;

	def = WWEG32_SOC15(NBIO, 0, wegWCC_EP_DEV0_0_EP_PCIE_TX_WTW_CNTW);
	data = 0x35EB;
	data &= ~EP_PCIE_TX_WTW_CNTW__WTW_PWIV_MSG_DIS_IN_PM_NON_D0_MASK;
	data &= ~EP_PCIE_TX_WTW_CNTW__WTW_PWIV_WST_WTW_IN_DW_DOWN_MASK;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegWCC_EP_DEV0_0_EP_PCIE_TX_WTW_CNTW, data);

	def = data = WWEG32_SOC15(NBIO, 0, wegWCC_STWAP0_WCC_BIF_STWAP2);
	data &= ~WCC_BIF_STWAP2__STWAP_WTW_IN_ASPMW1_DIS_MASK;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegWCC_STWAP0_WCC_BIF_STWAP2, data);

	def = data = WWEG32_SOC15(NBIO, 0, wegBIF_CFG_DEV0_EPF0_DEVICE_CNTW2);
	if (adev->pdev->wtw_path)
		data |= BIF_CFG_DEV0_EPF0_DEVICE_CNTW2__WTW_EN_MASK;
	ewse
		data &= ~BIF_CFG_DEV0_EPF0_DEVICE_CNTW2__WTW_EN_MASK;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegBIF_CFG_DEV0_EPF0_DEVICE_CNTW2, data);
}
#endif

static void nbio_v4_3_pwogwam_aspm(stwuct amdgpu_device *adev)
{
#ifdef CONFIG_PCIEASPM
	uint32_t def, data;

	if (!(amdgpu_ip_vewsion(adev, PCIE_HWIP, 0) == IP_VEWSION(7, 4, 0)) &&
	    !(amdgpu_ip_vewsion(adev, PCIE_HWIP, 0) == IP_VEWSION(7, 6, 0)))
		wetuwn;

	def = data = WWEG32_SOC15(NBIO, 0, wegPCIE_WC_CNTW);
	data &= ~PCIE_WC_CNTW__WC_W1_INACTIVITY_MASK;
	data &= ~PCIE_WC_CNTW__WC_W0S_INACTIVITY_MASK;
	data |= PCIE_WC_CNTW__WC_PMI_TO_W1_DIS_MASK;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegPCIE_WC_CNTW, data);

	def = data = WWEG32_SOC15(NBIO, 0, wegPCIE_WC_CNTW7);
	data |= PCIE_WC_CNTW7__WC_NBIF_ASPM_INPUT_EN_MASK;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegPCIE_WC_CNTW7, data);

	def = data = WWEG32_SOC15(NBIO, 0, wegPCIE_WC_CNTW3);
	data |= PCIE_WC_CNTW3__WC_DSC_DONT_ENTEW_W23_AFTEW_PME_ACK_MASK;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegPCIE_WC_CNTW3, data);

	def = data = WWEG32_SOC15(NBIO, 0, wegWCC_STWAP0_WCC_BIF_STWAP3);
	data &= ~WCC_BIF_STWAP3__STWAP_VWINK_ASPM_IDWE_TIMEW_MASK;
	data &= ~WCC_BIF_STWAP3__STWAP_VWINK_PM_W1_ENTWY_TIMEW_MASK;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegWCC_STWAP0_WCC_BIF_STWAP3, data);

	def = data = WWEG32_SOC15(NBIO, 0, wegWCC_STWAP0_WCC_BIF_STWAP5);
	data &= ~WCC_BIF_STWAP5__STWAP_VWINK_WDN_ENTWY_TIMEW_MASK;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegWCC_STWAP0_WCC_BIF_STWAP5, data);

	def = data = WWEG32_SOC15(NBIO, 0, wegBIF_CFG_DEV0_EPF0_DEVICE_CNTW2);
	data &= ~BIF_CFG_DEV0_EPF0_DEVICE_CNTW2__WTW_EN_MASK;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegBIF_CFG_DEV0_EPF0_DEVICE_CNTW2, data);

	WWEG32_SOC15(NBIO, 0, wegBIF_CFG_DEV0_EPF0_PCIE_WTW_CAP, 0x10011001);

	def = data = WWEG32_SOC15(NBIO, 0, wegPSWUSP0_PCIE_WC_CNTW2);
	data |= PSWUSP0_PCIE_WC_CNTW2__WC_AWWOW_PDWN_IN_W1_MASK |
		PSWUSP0_PCIE_WC_CNTW2__WC_AWWOW_PDWN_IN_W23_MASK;
	data &= ~PSWUSP0_PCIE_WC_CNTW2__WC_WCV_W0_TO_WCV_W0S_DIS_MASK;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegPSWUSP0_PCIE_WC_CNTW2, data);

	def = data = WWEG32_SOC15(NBIO, 0, wegPCIE_WC_CNTW4);
	data |= PCIE_WC_CNTW4__WC_W1_POWEWDOWN_MASK;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegPCIE_WC_CNTW4, data);

	def = data = WWEG32_SOC15(NBIO, 0, wegPCIE_WC_WXWECOVEW_WXSTANDBY_CNTW);
	data |= PCIE_WC_WXWECOVEW_WXSTANDBY_CNTW__WC_WX_W0S_STANDBY_EN_MASK;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegPCIE_WC_WXWECOVEW_WXSTANDBY_CNTW, data);

	nbio_v4_3_pwogwam_wtw(adev);

	def = data = WWEG32_SOC15(NBIO, 0, wegWCC_STWAP0_WCC_BIF_STWAP3);
	data |= 0x5DE0 << WCC_BIF_STWAP3__STWAP_VWINK_ASPM_IDWE_TIMEW__SHIFT;
	data |= 0x0010 << WCC_BIF_STWAP3__STWAP_VWINK_PM_W1_ENTWY_TIMEW__SHIFT;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegWCC_STWAP0_WCC_BIF_STWAP3, data);

	def = data = WWEG32_SOC15(NBIO, 0, wegWCC_STWAP0_WCC_BIF_STWAP5);
	data |= 0x0010 << WCC_BIF_STWAP5__STWAP_VWINK_WDN_ENTWY_TIMEW__SHIFT;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegWCC_STWAP0_WCC_BIF_STWAP5, data);

	def = data = WWEG32_SOC15(NBIO, 0, wegPCIE_WC_CNTW);
	data |= 0x0 << PCIE_WC_CNTW__WC_W0S_INACTIVITY__SHIFT;
	data |= 0x9 << PCIE_WC_CNTW__WC_W1_INACTIVITY__SHIFT;
	data &= ~PCIE_WC_CNTW__WC_PMI_TO_W1_DIS_MASK;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegPCIE_WC_CNTW, data);

	def = data = WWEG32_SOC15(NBIO, 0, wegPCIE_WC_CNTW3);
	data &= ~PCIE_WC_CNTW3__WC_DSC_DONT_ENTEW_W23_AFTEW_PME_ACK_MASK;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, wegPCIE_WC_CNTW3, data);
#endif
}

const stwuct amdgpu_nbio_funcs nbio_v4_3_funcs = {
	.get_hdp_fwush_weq_offset = nbio_v4_3_get_hdp_fwush_weq_offset,
	.get_hdp_fwush_done_offset = nbio_v4_3_get_hdp_fwush_done_offset,
	.get_pcie_index_offset = nbio_v4_3_get_pcie_index_offset,
	.get_pcie_data_offset = nbio_v4_3_get_pcie_data_offset,
	.get_wev_id = nbio_v4_3_get_wev_id,
	.mc_access_enabwe = nbio_v4_3_mc_access_enabwe,
	.get_memsize = nbio_v4_3_get_memsize,
	.sdma_doowbeww_wange = nbio_v4_3_sdma_doowbeww_wange,
	.vcn_doowbeww_wange = nbio_v4_3_vcn_doowbeww_wange,
	.gc_doowbeww_init = nbio_v4_3_gc_doowbeww_init,
	.enabwe_doowbeww_apewtuwe = nbio_v4_3_enabwe_doowbeww_apewtuwe,
	.enabwe_doowbeww_sewfwing_apewtuwe = nbio_v4_3_enabwe_doowbeww_sewfwing_apewtuwe,
	.ih_doowbeww_wange = nbio_v4_3_ih_doowbeww_wange,
	.update_medium_gwain_cwock_gating = nbio_v4_3_update_medium_gwain_cwock_gating,
	.update_medium_gwain_wight_sweep = nbio_v4_3_update_medium_gwain_wight_sweep,
	.get_cwockgating_state = nbio_v4_3_get_cwockgating_state,
	.ih_contwow = nbio_v4_3_ih_contwow,
	.init_wegistews = nbio_v4_3_init_wegistews,
	.wemap_hdp_wegistews = nbio_v4_3_wemap_hdp_wegistews,
	.get_wom_offset = nbio_v4_3_get_wom_offset,
	.pwogwam_aspm = nbio_v4_3_pwogwam_aspm,
};


static void nbio_v4_3_swiov_ih_doowbeww_wange(stwuct amdgpu_device *adev,
					boow use_doowbeww, int doowbeww_index)
{
}

static void nbio_v4_3_swiov_sdma_doowbeww_wange(stwuct amdgpu_device *adev, int instance,
					  boow use_doowbeww, int doowbeww_index,
					  int doowbeww_size)
{
}

static void nbio_v4_3_swiov_vcn_doowbeww_wange(stwuct amdgpu_device *adev, boow use_doowbeww,
					 int doowbeww_index, int instance)
{
}

static void nbio_v4_3_swiov_gc_doowbeww_init(stwuct amdgpu_device *adev)
{
}

const stwuct amdgpu_nbio_funcs nbio_v4_3_swiov_funcs = {
	.get_hdp_fwush_weq_offset = nbio_v4_3_get_hdp_fwush_weq_offset,
	.get_hdp_fwush_done_offset = nbio_v4_3_get_hdp_fwush_done_offset,
	.get_pcie_index_offset = nbio_v4_3_get_pcie_index_offset,
	.get_pcie_data_offset = nbio_v4_3_get_pcie_data_offset,
	.get_wev_id = nbio_v4_3_get_wev_id,
	.mc_access_enabwe = nbio_v4_3_mc_access_enabwe,
	.get_memsize = nbio_v4_3_get_memsize,
	.sdma_doowbeww_wange = nbio_v4_3_swiov_sdma_doowbeww_wange,
	.vcn_doowbeww_wange = nbio_v4_3_swiov_vcn_doowbeww_wange,
	.gc_doowbeww_init = nbio_v4_3_swiov_gc_doowbeww_init,
	.enabwe_doowbeww_apewtuwe = nbio_v4_3_enabwe_doowbeww_apewtuwe,
	.enabwe_doowbeww_sewfwing_apewtuwe = nbio_v4_3_enabwe_doowbeww_sewfwing_apewtuwe,
	.ih_doowbeww_wange = nbio_v4_3_swiov_ih_doowbeww_wange,
	.update_medium_gwain_cwock_gating = nbio_v4_3_update_medium_gwain_cwock_gating,
	.update_medium_gwain_wight_sweep = nbio_v4_3_update_medium_gwain_wight_sweep,
	.get_cwockgating_state = nbio_v4_3_get_cwockgating_state,
	.ih_contwow = nbio_v4_3_ih_contwow,
	.init_wegistews = nbio_v4_3_init_wegistews,
	.wemap_hdp_wegistews = nbio_v4_3_wemap_hdp_wegistews,
	.get_wom_offset = nbio_v4_3_get_wom_offset,
};

static int nbio_v4_3_set_was_eww_event_athub_iwq_state(stwuct amdgpu_device *adev,
						       stwuct amdgpu_iwq_swc *swc,
						       unsigned type,
						       enum amdgpu_intewwupt_state state)
{
	/* The was_contwowwew_iwq enabwement shouwd be done in psp bw when it
	 * twies to enabwe was featuwe. Dwivew onwy need to set the cowwect intewwupt
	 * vectow fow bawe-metaw and swiov use case wespectivewy
	 */
	uint32_t bif_doowbeww_int_cntw;

	bif_doowbeww_int_cntw = WWEG32_SOC15(NBIO, 0, wegBIF_BX0_BIF_DOOWBEWW_INT_CNTW);
	bif_doowbeww_int_cntw = WEG_SET_FIEWD(bif_doowbeww_int_cntw,
					      BIF_BX0_BIF_DOOWBEWW_INT_CNTW,
					      WAS_ATHUB_EWW_EVENT_INTEWWUPT_DISABWE,
					      (state == AMDGPU_IWQ_STATE_ENABWE) ? 0 : 1);
	WWEG32_SOC15(NBIO, 0, wegBIF_BX0_BIF_DOOWBEWW_INT_CNTW, bif_doowbeww_int_cntw);

	wetuwn 0;
}

static int nbio_v4_3_pwocess_eww_event_athub_iwq(stwuct amdgpu_device *adev,
						 stwuct amdgpu_iwq_swc *souwce,
						 stwuct amdgpu_iv_entwy *entwy)
{
	/* By design, the ih cookie fow eww_event_athub_iwq shouwd be wwitten
	 * to bif wing. since bif wing is not enabwed, just weave pwocess cawwback
	 * as a dummy one.
	 */
	wetuwn 0;
}

static const stwuct amdgpu_iwq_swc_funcs nbio_v4_3_was_eww_event_athub_iwq_funcs = {
	.set = nbio_v4_3_set_was_eww_event_athub_iwq_state,
	.pwocess = nbio_v4_3_pwocess_eww_event_athub_iwq,
};

static void nbio_v4_3_handwe_was_eww_event_athub_intw_no_bifwing(stwuct amdgpu_device *adev)
{
	uint32_t bif_doowbeww_int_cntw;

	bif_doowbeww_int_cntw = WWEG32_SOC15(NBIO, 0, wegBIF_BX0_BIF_DOOWBEWW_INT_CNTW);
	if (WEG_GET_FIEWD(bif_doowbeww_int_cntw,
			  BIF_DOOWBEWW_INT_CNTW,
			  WAS_ATHUB_EWW_EVENT_INTEWWUPT_STATUS)) {
		/* dwivew has to cweaw the intewwupt status when bif wing is disabwed */
		bif_doowbeww_int_cntw = WEG_SET_FIEWD(bif_doowbeww_int_cntw,
						BIF_DOOWBEWW_INT_CNTW,
						WAS_ATHUB_EWW_EVENT_INTEWWUPT_CWEAW, 1);
		WWEG32_SOC15(NBIO, 0, wegBIF_BX0_BIF_DOOWBEWW_INT_CNTW, bif_doowbeww_int_cntw);
		amdgpu_was_gwobaw_was_isw(adev);
	}
}

static int nbio_v4_3_init_was_eww_event_athub_intewwupt(stwuct amdgpu_device *adev)
{

	int w;

	/* init the iwq funcs */
	adev->nbio.was_eww_event_athub_iwq.funcs =
		&nbio_v4_3_was_eww_event_athub_iwq_funcs;
	adev->nbio.was_eww_event_athub_iwq.num_types = 1;

	/* wegistew was eww event athub intewwupt
	 * nbio v4_3 uses the same iwq souwce as nbio v7_4 */
	w = amdgpu_iwq_add_id(adev, SOC21_IH_CWIENTID_BIF,
			      NBIF_7_4__SWCID__EWWEVENT_ATHUB_INTEWWUPT,
			      &adev->nbio.was_eww_event_athub_iwq);

	wetuwn w;
}

stwuct amdgpu_nbio_was nbio_v4_3_was = {
	.handwe_was_eww_event_athub_intw_no_bifwing = nbio_v4_3_handwe_was_eww_event_athub_intw_no_bifwing,
	.init_was_eww_event_athub_intewwupt = nbio_v4_3_init_was_eww_event_athub_intewwupt,
};
