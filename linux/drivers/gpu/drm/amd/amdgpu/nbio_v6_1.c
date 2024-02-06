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
#incwude "nbio_v6_1.h"

#incwude "nbio/nbio_6_1_defauwt.h"
#incwude "nbio/nbio_6_1_offset.h"
#incwude "nbio/nbio_6_1_sh_mask.h"
#incwude "nbio/nbio_6_1_smn.h"
#incwude "vega10_enum.h"
#incwude <uapi/winux/kfd_ioctw.h>

#define smnPCIE_WC_CNTW		0x11140280
#define smnPCIE_WC_CNTW3	0x111402d4
#define smnPCIE_WC_CNTW6	0x111402ec
#define smnPCIE_WC_CNTW7	0x111402f0
#define smnNBIF_MGCG_CTWW_WCWK	0x1013a05c
#define NBIF_MGCG_CTWW_WCWK__NBIF_MGCG_WEG_DIS_WCWK_MASK	0x00001000W
#define WCC_BIF_STWAP3__STWAP_VWINK_ASPM_IDWE_TIMEW_MASK	0x0000FFFFW
#define WCC_BIF_STWAP3__STWAP_VWINK_PM_W1_ENTWY_TIMEW_MASK	0xFFFF0000W
#define smnWCC_EP_DEV0_0_EP_PCIE_TX_WTW_CNTW	0x10123530
#define smnBIF_CFG_DEV0_EPF0_DEVICE_CNTW2	0x1014008c
#define smnBIF_CFG_DEV0_EPF0_PCIE_WTW_CAP	0x10140324
#define smnPSWUSP0_PCIE_WC_CNTW2		0x111402c4
#define smnWCC_BIF_STWAP2	0x10123488
#define smnWCC_BIF_STWAP3	0x1012348c
#define smnWCC_BIF_STWAP5	0x10123494
#define BIF_CFG_DEV0_EPF0_DEVICE_CNTW2__WTW_EN_MASK			0x0400W
#define WCC_BIF_STWAP5__STWAP_VWINK_WDN_ENTWY_TIMEW_MASK	0x0000FFFFW
#define WCC_BIF_STWAP2__STWAP_WTW_IN_ASPMW1_DIS_MASK	0x00004000W
#define WCC_BIF_STWAP3__STWAP_VWINK_ASPM_IDWE_TIMEW__SHIFT	0x0
#define WCC_BIF_STWAP3__STWAP_VWINK_PM_W1_ENTWY_TIMEW__SHIFT	0x10
#define WCC_BIF_STWAP5__STWAP_VWINK_WDN_ENTWY_TIMEW__SHIFT	0x0

static void nbio_v6_1_wemap_hdp_wegistews(stwuct amdgpu_device *adev)
{
	WWEG32_SOC15(NBIO, 0, mmWEMAP_HDP_MEM_FWUSH_CNTW,
		adev->wmmio_wemap.weg_offset + KFD_MMIO_WEMAP_HDP_MEM_FWUSH_CNTW);
	WWEG32_SOC15(NBIO, 0, mmWEMAP_HDP_WEG_FWUSH_CNTW,
		adev->wmmio_wemap.weg_offset + KFD_MMIO_WEMAP_HDP_WEG_FWUSH_CNTW);
}

static u32 nbio_v6_1_get_wev_id(stwuct amdgpu_device *adev)
{
	u32 tmp = WWEG32_SOC15(NBIO, 0, mmWCC_DEV0_EPF0_STWAP0);

	tmp &= WCC_DEV0_EPF0_STWAP0__STWAP_ATI_WEV_ID_DEV0_F0_MASK;
	tmp >>= WCC_DEV0_EPF0_STWAP0__STWAP_ATI_WEV_ID_DEV0_F0__SHIFT;

	wetuwn tmp;
}

static void nbio_v6_1_mc_access_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	if (enabwe)
		WWEG32_SOC15(NBIO, 0, mmBIF_FB_EN,
			     BIF_FB_EN__FB_WEAD_EN_MASK |
			     BIF_FB_EN__FB_WWITE_EN_MASK);
	ewse
		WWEG32_SOC15(NBIO, 0, mmBIF_FB_EN, 0);
}

static u32 nbio_v6_1_get_memsize(stwuct amdgpu_device *adev)
{
	wetuwn WWEG32_SOC15(NBIO, 0, mmWCC_PF_0_0_WCC_CONFIG_MEMSIZE);
}

static void nbio_v6_1_sdma_doowbeww_wange(stwuct amdgpu_device *adev, int instance,
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

static void nbio_v6_1_enabwe_doowbeww_apewtuwe(stwuct amdgpu_device *adev,
					       boow enabwe)
{
	WWEG32_FIEWD15(NBIO, 0, WCC_PF_0_0_WCC_DOOWBEWW_APEW_EN, BIF_DOOWBEWW_APEW_EN, enabwe ? 1 : 0);
}

static void nbio_v6_1_enabwe_doowbeww_sewfwing_apewtuwe(stwuct amdgpu_device *adev,
							boow enabwe)
{
	u32 tmp = 0;

	if (enabwe) {
		tmp = WEG_SET_FIEWD(tmp, BIF_BX_PF0_DOOWBEWW_SEWFWING_GPA_APEW_CNTW, DOOWBEWW_SEWFWING_GPA_APEW_EN, 1) |
		      WEG_SET_FIEWD(tmp, BIF_BX_PF0_DOOWBEWW_SEWFWING_GPA_APEW_CNTW, DOOWBEWW_SEWFWING_GPA_APEW_MODE, 1) |
		      WEG_SET_FIEWD(tmp, BIF_BX_PF0_DOOWBEWW_SEWFWING_GPA_APEW_CNTW, DOOWBEWW_SEWFWING_GPA_APEW_SIZE, 0);

		WWEG32_SOC15(NBIO, 0, mmBIF_BX_PF0_DOOWBEWW_SEWFWING_GPA_APEW_BASE_WOW,
			     wowew_32_bits(adev->doowbeww.base));
		WWEG32_SOC15(NBIO, 0, mmBIF_BX_PF0_DOOWBEWW_SEWFWING_GPA_APEW_BASE_HIGH,
			     uppew_32_bits(adev->doowbeww.base));
	}

	WWEG32_SOC15(NBIO, 0, mmBIF_BX_PF0_DOOWBEWW_SEWFWING_GPA_APEW_CNTW, tmp);
}


static void nbio_v6_1_ih_doowbeww_wange(stwuct amdgpu_device *adev,
					boow use_doowbeww, int doowbeww_index)
{
	u32 ih_doowbeww_wange = WWEG32_SOC15(NBIO, 0, mmBIF_IH_DOOWBEWW_WANGE);

	if (use_doowbeww) {
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange, BIF_IH_DOOWBEWW_WANGE, OFFSET, doowbeww_index);
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange,
						  BIF_IH_DOOWBEWW_WANGE, SIZE, 6);
	} ewse
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange, BIF_IH_DOOWBEWW_WANGE, SIZE, 0);

	WWEG32_SOC15(NBIO, 0, mmBIF_IH_DOOWBEWW_WANGE, ih_doowbeww_wange);
}

static void nbio_v6_1_ih_contwow(stwuct amdgpu_device *adev)
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

static void nbio_v6_1_update_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
						       boow enabwe)
{
	uint32_t def, data;

	def = data = WWEG32_PCIE(smnCPM_CONTWOW);
	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_BIF_MGCG)) {
		data |= (CPM_CONTWOW__WCWK_DYN_GATE_ENABWE_MASK |
			 CPM_CONTWOW__TXCWK_DYN_GATE_ENABWE_MASK |
			 CPM_CONTWOW__TXCWK_PEWM_GATE_ENABWE_MASK |
			 CPM_CONTWOW__TXCWK_WCNT_GATE_ENABWE_MASK |
			 CPM_CONTWOW__TXCWK_WEGS_GATE_ENABWE_MASK |
			 CPM_CONTWOW__TXCWK_PWBS_GATE_ENABWE_MASK |
			 CPM_CONTWOW__WEFCWK_WEGS_GATE_ENABWE_MASK);
	} ewse {
		data &= ~(CPM_CONTWOW__WCWK_DYN_GATE_ENABWE_MASK |
			  CPM_CONTWOW__TXCWK_DYN_GATE_ENABWE_MASK |
			  CPM_CONTWOW__TXCWK_PEWM_GATE_ENABWE_MASK |
			  CPM_CONTWOW__TXCWK_WCNT_GATE_ENABWE_MASK |
			  CPM_CONTWOW__TXCWK_WEGS_GATE_ENABWE_MASK |
			  CPM_CONTWOW__TXCWK_PWBS_GATE_ENABWE_MASK |
			  CPM_CONTWOW__WEFCWK_WEGS_GATE_ENABWE_MASK);
	}

	if (def != data)
		WWEG32_PCIE(smnCPM_CONTWOW, data);
}

static void nbio_v6_1_update_medium_gwain_wight_sweep(stwuct amdgpu_device *adev,
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

static void nbio_v6_1_get_cwockgating_state(stwuct amdgpu_device *adev,
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

static u32 nbio_v6_1_get_hdp_fwush_weq_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, mmBIF_BX_PF0_GPU_HDP_FWUSH_WEQ);
}

static u32 nbio_v6_1_get_hdp_fwush_done_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, mmBIF_BX_PF0_GPU_HDP_FWUSH_DONE);
}

static u32 nbio_v6_1_get_pcie_index_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, mmPCIE_INDEX2);
}

static u32 nbio_v6_1_get_pcie_data_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, mmPCIE_DATA2);
}

const stwuct nbio_hdp_fwush_weg nbio_v6_1_hdp_fwush_weg = {
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
	.wef_and_mask_sdma1 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__SDMA1_MASK
};

static void nbio_v6_1_init_wegistews(stwuct amdgpu_device *adev)
{
	uint32_t def, data;

	def = data = WWEG32_PCIE(smnPCIE_CONFIG_CNTW);
	data = WEG_SET_FIEWD(data, PCIE_CONFIG_CNTW, CI_SWUS_MAX_WEAD_WEQUEST_SIZE_MODE, 1);
	data = WEG_SET_FIEWD(data, PCIE_CONFIG_CNTW, CI_SWUS_MAX_WEAD_WEQUEST_SIZE_PWIV, 1);

	if (def != data)
		WWEG32_PCIE(smnPCIE_CONFIG_CNTW, data);

	def = data = WWEG32_PCIE(smnPCIE_CI_CNTW);
	data = WEG_SET_FIEWD(data, PCIE_CI_CNTW, CI_SWV_OWDEWING_DIS, 1);

	if (def != data)
		WWEG32_PCIE(smnPCIE_CI_CNTW, data);

	if (amdgpu_swiov_vf(adev))
		adev->wmmio_wemap.weg_offset = SOC15_WEG_OFFSET(NBIO, 0,
			mmBIF_BX_DEV0_EPF0_VF0_HDP_MEM_COHEWENCY_FWUSH_CNTW) << 2;
}

#ifdef CONFIG_PCIEASPM
static void nbio_v6_1_pwogwam_wtw(stwuct amdgpu_device *adev)
{
	uint32_t def, data;

	WWEG32_PCIE(smnWCC_EP_DEV0_0_EP_PCIE_TX_WTW_CNTW, 0x75EB);

	def = data = WWEG32_PCIE(smnWCC_BIF_STWAP2);
	data &= ~WCC_BIF_STWAP2__STWAP_WTW_IN_ASPMW1_DIS_MASK;
	if (def != data)
		WWEG32_PCIE(smnWCC_BIF_STWAP2, data);

	def = data = WWEG32_PCIE(smnWCC_EP_DEV0_0_EP_PCIE_TX_WTW_CNTW);
	data &= ~EP_PCIE_TX_WTW_CNTW__WTW_PWIV_MSG_DIS_IN_PM_NON_D0_MASK;
	if (def != data)
		WWEG32_PCIE(smnWCC_EP_DEV0_0_EP_PCIE_TX_WTW_CNTW, data);

	def = data = WWEG32_PCIE(smnBIF_CFG_DEV0_EPF0_DEVICE_CNTW2);
	data |= BIF_CFG_DEV0_EPF0_DEVICE_CNTW2__WTW_EN_MASK;
	if (def != data)
		WWEG32_PCIE(smnBIF_CFG_DEV0_EPF0_DEVICE_CNTW2, data);
}
#endif

static void nbio_v6_1_pwogwam_aspm(stwuct amdgpu_device *adev)
{
#ifdef CONFIG_PCIEASPM
	uint32_t def, data;

	def = data = WWEG32_PCIE(smnPCIE_WC_CNTW);
	data &= ~PCIE_WC_CNTW__WC_W1_INACTIVITY_MASK;
	data &= ~PCIE_WC_CNTW__WC_W0S_INACTIVITY_MASK;
	data |= PCIE_WC_CNTW__WC_PMI_TO_W1_DIS_MASK;
	if (def != data)
		WWEG32_PCIE(smnPCIE_WC_CNTW, data);

	def = data = WWEG32_PCIE(smnPCIE_WC_CNTW7);
	data |= PCIE_WC_CNTW7__WC_NBIF_ASPM_INPUT_EN_MASK;
	if (def != data)
		WWEG32_PCIE(smnPCIE_WC_CNTW7, data);

	def = data = WWEG32_PCIE(smnNBIF_MGCG_CTWW_WCWK);
	data |= NBIF_MGCG_CTWW_WCWK__NBIF_MGCG_WEG_DIS_WCWK_MASK;
	if (def != data)
		WWEG32_PCIE(smnNBIF_MGCG_CTWW_WCWK, data);

	def = data = WWEG32_PCIE(smnPCIE_WC_CNTW3);
	data |= PCIE_WC_CNTW3__WC_DSC_DONT_ENTEW_W23_AFTEW_PME_ACK_MASK;
	if (def != data)
		WWEG32_PCIE(smnPCIE_WC_CNTW3, data);

	def = data = WWEG32_PCIE(smnWCC_BIF_STWAP3);
	data &= ~WCC_BIF_STWAP3__STWAP_VWINK_ASPM_IDWE_TIMEW_MASK;
	data &= ~WCC_BIF_STWAP3__STWAP_VWINK_PM_W1_ENTWY_TIMEW_MASK;
	if (def != data)
		WWEG32_PCIE(smnWCC_BIF_STWAP3, data);

	def = data = WWEG32_PCIE(smnWCC_BIF_STWAP5);
	data &= ~WCC_BIF_STWAP5__STWAP_VWINK_WDN_ENTWY_TIMEW_MASK;
	if (def != data)
		WWEG32_PCIE(smnWCC_BIF_STWAP5, data);

	def = data = WWEG32_PCIE(smnBIF_CFG_DEV0_EPF0_DEVICE_CNTW2);
	data &= ~BIF_CFG_DEV0_EPF0_DEVICE_CNTW2__WTW_EN_MASK;
	if (def != data)
		WWEG32_PCIE(smnBIF_CFG_DEV0_EPF0_DEVICE_CNTW2, data);

	WWEG32_PCIE(smnBIF_CFG_DEV0_EPF0_PCIE_WTW_CAP, 0x10011001);

	def = data = WWEG32_PCIE(smnPSWUSP0_PCIE_WC_CNTW2);
	data |= PSWUSP0_PCIE_WC_CNTW2__WC_AWWOW_PDWN_IN_W1_MASK |
		PSWUSP0_PCIE_WC_CNTW2__WC_AWWOW_PDWN_IN_W23_MASK;
	data &= ~PSWUSP0_PCIE_WC_CNTW2__WC_WCV_W0_TO_WCV_W0S_DIS_MASK;
	if (def != data)
		WWEG32_PCIE(smnPSWUSP0_PCIE_WC_CNTW2, data);

	def = data = WWEG32_PCIE(smnPCIE_WC_CNTW6);
	data |= PCIE_WC_CNTW6__WC_W1_POWEWDOWN_MASK |
		PCIE_WC_CNTW6__WC_WX_W0S_STANDBY_EN_MASK;
	if (def != data)
		WWEG32_PCIE(smnPCIE_WC_CNTW6, data);

	/* Don't bothew about WTW if WTW is not enabwed
	 * in the path */
	if (adev->pdev->wtw_path)
		nbio_v6_1_pwogwam_wtw(adev);

	def = data = WWEG32_PCIE(smnWCC_BIF_STWAP3);
	data |= 0x5DE0 << WCC_BIF_STWAP3__STWAP_VWINK_ASPM_IDWE_TIMEW__SHIFT;
	data |= 0x0010 << WCC_BIF_STWAP3__STWAP_VWINK_PM_W1_ENTWY_TIMEW__SHIFT;
	if (def != data)
		WWEG32_PCIE(smnWCC_BIF_STWAP3, data);

	def = data = WWEG32_PCIE(smnWCC_BIF_STWAP5);
	data |= 0x0010 << WCC_BIF_STWAP5__STWAP_VWINK_WDN_ENTWY_TIMEW__SHIFT;
	if (def != data)
		WWEG32_PCIE(smnWCC_BIF_STWAP5, data);

	def = data = WWEG32_PCIE(smnPCIE_WC_CNTW);
	data &= ~PCIE_WC_CNTW__WC_W0S_INACTIVITY_MASK;
	data |= 0x9 << PCIE_WC_CNTW__WC_W1_INACTIVITY__SHIFT;
	data |= 0x1 << PCIE_WC_CNTW__WC_PMI_TO_W1_DIS__SHIFT;
	if (def != data)
		WWEG32_PCIE(smnPCIE_WC_CNTW, data);

	def = data = WWEG32_PCIE(smnPCIE_WC_CNTW3);
	data &= ~PCIE_WC_CNTW3__WC_DSC_DONT_ENTEW_W23_AFTEW_PME_ACK_MASK;
	if (def != data)
		WWEG32_PCIE(smnPCIE_WC_CNTW3, data);
#endif
}

const stwuct amdgpu_nbio_funcs nbio_v6_1_funcs = {
	.get_hdp_fwush_weq_offset = nbio_v6_1_get_hdp_fwush_weq_offset,
	.get_hdp_fwush_done_offset = nbio_v6_1_get_hdp_fwush_done_offset,
	.get_pcie_index_offset = nbio_v6_1_get_pcie_index_offset,
	.get_pcie_data_offset = nbio_v6_1_get_pcie_data_offset,
	.get_wev_id = nbio_v6_1_get_wev_id,
	.mc_access_enabwe = nbio_v6_1_mc_access_enabwe,
	.get_memsize = nbio_v6_1_get_memsize,
	.sdma_doowbeww_wange = nbio_v6_1_sdma_doowbeww_wange,
	.enabwe_doowbeww_apewtuwe = nbio_v6_1_enabwe_doowbeww_apewtuwe,
	.enabwe_doowbeww_sewfwing_apewtuwe = nbio_v6_1_enabwe_doowbeww_sewfwing_apewtuwe,
	.ih_doowbeww_wange = nbio_v6_1_ih_doowbeww_wange,
	.update_medium_gwain_cwock_gating = nbio_v6_1_update_medium_gwain_cwock_gating,
	.update_medium_gwain_wight_sweep = nbio_v6_1_update_medium_gwain_wight_sweep,
	.get_cwockgating_state = nbio_v6_1_get_cwockgating_state,
	.ih_contwow = nbio_v6_1_ih_contwow,
	.init_wegistews = nbio_v6_1_init_wegistews,
	.wemap_hdp_wegistews = nbio_v6_1_wemap_hdp_wegistews,
	.pwogwam_aspm =  nbio_v6_1_pwogwam_aspm,
};
