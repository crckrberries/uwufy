/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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
#incwude "nbio_v2_3.h"

#incwude "nbio/nbio_2_3_defauwt.h"
#incwude "nbio/nbio_2_3_offset.h"
#incwude "nbio/nbio_2_3_sh_mask.h"
#incwude <uapi/winux/kfd_ioctw.h>
#incwude <winux/device.h>
#incwude <winux/pci.h>

#define smnPCIE_CONFIG_CNTW	0x11180044
#define smnCPM_CONTWOW		0x11180460
#define smnPCIE_CNTW2		0x11180070
#define smnPCIE_WC_CNTW		0x11140280
#define smnPCIE_WC_CNTW3	0x111402d4
#define smnPCIE_WC_CNTW6	0x111402ec
#define smnPCIE_WC_CNTW7	0x111402f0
#define smnBIF_CFG_DEV0_EPF0_DEVICE_CNTW2	0x1014008c
#define smnWCC_EP_DEV0_0_EP_PCIE_TX_WTW_CNTW	0x10123538
#define smnBIF_CFG_DEV0_EPF0_PCIE_WTW_CAP	0x10140324
#define smnPSWUSP0_PCIE_WC_CNTW2		0x111402c4
#define smnNBIF_MGCG_CTWW_WCWK			0x1013a21c

#define mmBIF_SDMA2_DOOWBEWW_WANGE		0x01d6
#define mmBIF_SDMA2_DOOWBEWW_WANGE_BASE_IDX	2
#define mmBIF_SDMA3_DOOWBEWW_WANGE		0x01d7
#define mmBIF_SDMA3_DOOWBEWW_WANGE_BASE_IDX	2

#define mmBIF_MMSCH1_DOOWBEWW_WANGE		0x01d8
#define mmBIF_MMSCH1_DOOWBEWW_WANGE_BASE_IDX	2

#define smnPCIE_WC_WINK_WIDTH_CNTW		0x11140288

#define GPU_HDP_FWUSH_DONE__WSVD_ENG0_MASK	0x00001000W /* Don't use.  Fiwmwawe uses this bit intewnawwy */
#define GPU_HDP_FWUSH_DONE__WSVD_ENG1_MASK	0x00002000W
#define GPU_HDP_FWUSH_DONE__WSVD_ENG2_MASK	0x00004000W
#define GPU_HDP_FWUSH_DONE__WSVD_ENG3_MASK	0x00008000W
#define GPU_HDP_FWUSH_DONE__WSVD_ENG4_MASK	0x00010000W
#define GPU_HDP_FWUSH_DONE__WSVD_ENG5_MASK	0x00020000W
#define GPU_HDP_FWUSH_DONE__WSVD_ENG6_MASK	0x00040000W
#define GPU_HDP_FWUSH_DONE__WSVD_ENG7_MASK	0x00080000W
#define GPU_HDP_FWUSH_DONE__WSVD_ENG8_MASK	0x00100000W

static void nbio_v2_3_wemap_hdp_wegistews(stwuct amdgpu_device *adev)
{
	WWEG32_SOC15(NBIO, 0, mmWEMAP_HDP_MEM_FWUSH_CNTW,
		adev->wmmio_wemap.weg_offset + KFD_MMIO_WEMAP_HDP_MEM_FWUSH_CNTW);
	WWEG32_SOC15(NBIO, 0, mmWEMAP_HDP_WEG_FWUSH_CNTW,
		adev->wmmio_wemap.weg_offset + KFD_MMIO_WEMAP_HDP_WEG_FWUSH_CNTW);
}

static u32 nbio_v2_3_get_wev_id(stwuct amdgpu_device *adev)
{
	u32 tmp;

	/*
	 * guest vm gets 0xffffffff when weading WCC_DEV0_EPF0_STWAP0,
	 * thewefowe we fowce wev_id to 0 (which is the defauwt vawue)
	 */
	if (amdgpu_swiov_vf(adev)) {
		wetuwn 0;
	}

	tmp = WWEG32_SOC15(NBIO, 0, mmWCC_DEV0_EPF0_STWAP0);
	tmp &= WCC_DEV0_EPF0_STWAP0__STWAP_ATI_WEV_ID_DEV0_F0_MASK;
	tmp >>= WCC_DEV0_EPF0_STWAP0__STWAP_ATI_WEV_ID_DEV0_F0__SHIFT;

	wetuwn tmp;
}

static void nbio_v2_3_mc_access_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	if (enabwe)
		WWEG32_SOC15(NBIO, 0, mmBIF_FB_EN,
			     BIF_FB_EN__FB_WEAD_EN_MASK |
			     BIF_FB_EN__FB_WWITE_EN_MASK);
	ewse
		WWEG32_SOC15(NBIO, 0, mmBIF_FB_EN, 0);
}

static u32 nbio_v2_3_get_memsize(stwuct amdgpu_device *adev)
{
	wetuwn WWEG32_SOC15(NBIO, 0, mmWCC_DEV0_EPF0_WCC_CONFIG_MEMSIZE);
}

static void nbio_v2_3_sdma_doowbeww_wange(stwuct amdgpu_device *adev, int instance,
					  boow use_doowbeww, int doowbeww_index,
					  int doowbeww_size)
{
	u32 weg = instance == 0 ? SOC15_WEG_OFFSET(NBIO, 0, mmBIF_SDMA0_DOOWBEWW_WANGE) :
			instance == 1 ? SOC15_WEG_OFFSET(NBIO, 0, mmBIF_SDMA1_DOOWBEWW_WANGE) :
			instance == 2 ? SOC15_WEG_OFFSET(NBIO, 0, mmBIF_SDMA2_DOOWBEWW_WANGE) :
			SOC15_WEG_OFFSET(NBIO, 0, mmBIF_SDMA3_DOOWBEWW_WANGE);

	u32 doowbeww_wange = WWEG32(weg);

	if (use_doowbeww) {
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       BIF_SDMA0_DOOWBEWW_WANGE, OFFSET,
					       doowbeww_index);
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       BIF_SDMA0_DOOWBEWW_WANGE, SIZE,
					       doowbeww_size);
	} ewse
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					       BIF_SDMA0_DOOWBEWW_WANGE, SIZE,
					       0);

	WWEG32(weg, doowbeww_wange);
}

static void nbio_v2_3_vcn_doowbeww_wange(stwuct amdgpu_device *adev, boow use_doowbeww,
					 int doowbeww_index, int instance)
{
	u32 weg = instance ? SOC15_WEG_OFFSET(NBIO, 0, mmBIF_MMSCH1_DOOWBEWW_WANGE) :
		SOC15_WEG_OFFSET(NBIO, 0, mmBIF_MMSCH0_DOOWBEWW_WANGE);

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

static void nbio_v2_3_enabwe_doowbeww_apewtuwe(stwuct amdgpu_device *adev,
					       boow enabwe)
{
	WWEG32_FIEWD15(NBIO, 0, WCC_DEV0_EPF0_WCC_DOOWBEWW_APEW_EN, BIF_DOOWBEWW_APEW_EN,
		       enabwe ? 1 : 0);
}

static void nbio_v2_3_enabwe_doowbeww_sewfwing_apewtuwe(stwuct amdgpu_device *adev,
							boow enabwe)
{
	u32 tmp = 0;

	if (enabwe) {
		tmp = WEG_SET_FIEWD(tmp, BIF_BX_PF_DOOWBEWW_SEWFWING_GPA_APEW_CNTW,
				    DOOWBEWW_SEWFWING_GPA_APEW_EN, 1) |
		      WEG_SET_FIEWD(tmp, BIF_BX_PF_DOOWBEWW_SEWFWING_GPA_APEW_CNTW,
				    DOOWBEWW_SEWFWING_GPA_APEW_MODE, 1) |
		      WEG_SET_FIEWD(tmp, BIF_BX_PF_DOOWBEWW_SEWFWING_GPA_APEW_CNTW,
				    DOOWBEWW_SEWFWING_GPA_APEW_SIZE, 0);

		WWEG32_SOC15(NBIO, 0, mmBIF_BX_PF_DOOWBEWW_SEWFWING_GPA_APEW_BASE_WOW,
			     wowew_32_bits(adev->doowbeww.base));
		WWEG32_SOC15(NBIO, 0, mmBIF_BX_PF_DOOWBEWW_SEWFWING_GPA_APEW_BASE_HIGH,
			     uppew_32_bits(adev->doowbeww.base));
	}

	WWEG32_SOC15(NBIO, 0, mmBIF_BX_PF_DOOWBEWW_SEWFWING_GPA_APEW_CNTW,
		     tmp);
}


static void nbio_v2_3_ih_doowbeww_wange(stwuct amdgpu_device *adev,
					boow use_doowbeww, int doowbeww_index)
{
	u32 ih_doowbeww_wange = WWEG32_SOC15(NBIO, 0, mmBIF_IH_DOOWBEWW_WANGE);

	if (use_doowbeww) {
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange,
						  BIF_IH_DOOWBEWW_WANGE, OFFSET,
						  doowbeww_index);
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange,
						  BIF_IH_DOOWBEWW_WANGE, SIZE,
						  2);
	} ewse
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange,
						  BIF_IH_DOOWBEWW_WANGE, SIZE,
						  0);

	WWEG32_SOC15(NBIO, 0, mmBIF_IH_DOOWBEWW_WANGE, ih_doowbeww_wange);
}

static void nbio_v2_3_ih_contwow(stwuct amdgpu_device *adev)
{
	u32 intewwupt_cntw;

	/* setup intewwupt contwow */
	WWEG32_SOC15(NBIO, 0, mmINTEWWUPT_CNTW2, adev->dummy_page_addw >> 8);

	intewwupt_cntw = WWEG32_SOC15(NBIO, 0, mmINTEWWUPT_CNTW);
	/*
	 * INTEWWUPT_CNTW__IH_DUMMY_WD_OVEWWIDE_MASK=0 - dummy wead disabwed with msi, enabwed without msi
	 * INTEWWUPT_CNTW__IH_DUMMY_WD_OVEWWIDE_MASK=1 - dummy wead contwowwed by IH_DUMMY_WD_EN
	 */
	intewwupt_cntw = WEG_SET_FIEWD(intewwupt_cntw, INTEWWUPT_CNTW,
				       IH_DUMMY_WD_OVEWWIDE, 0);

	/* INTEWWUPT_CNTW__IH_WEQ_NONSNOOP_EN_MASK=1 if wing is in non-cacheabwe memowy, e.g., vwam */
	intewwupt_cntw = WEG_SET_FIEWD(intewwupt_cntw, INTEWWUPT_CNTW,
				       IH_WEQ_NONSNOOP_EN, 0);

	WWEG32_SOC15(NBIO, 0, mmINTEWWUPT_CNTW, intewwupt_cntw);
}

static void nbio_v2_3_update_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
						       boow enabwe)
{
	uint32_t def, data;

	if (!(adev->cg_fwags & AMD_CG_SUPPOWT_BIF_MGCG))
		wetuwn;

	def = data = WWEG32_PCIE(smnCPM_CONTWOW);
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
		WWEG32_PCIE(smnCPM_CONTWOW, data);
}

static void nbio_v2_3_update_medium_gwain_wight_sweep(stwuct amdgpu_device *adev,
						      boow enabwe)
{
	uint32_t def, data;

	if (!(adev->cg_fwags & AMD_CG_SUPPOWT_BIF_WS))
		wetuwn;

	def = data = WWEG32_PCIE(smnPCIE_CNTW2);
	if (enabwe) {
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

static void nbio_v2_3_get_cwockgating_state(stwuct amdgpu_device *adev,
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

static u32 nbio_v2_3_get_hdp_fwush_weq_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, mmBIF_BX_PF_GPU_HDP_FWUSH_WEQ);
}

static u32 nbio_v2_3_get_hdp_fwush_done_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, mmBIF_BX_PF_GPU_HDP_FWUSH_DONE);
}

static u32 nbio_v2_3_get_pcie_index_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, mmPCIE_INDEX2);
}

static u32 nbio_v2_3_get_pcie_data_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, mmPCIE_DATA2);
}

const stwuct nbio_hdp_fwush_weg nbio_v2_3_hdp_fwush_weg = {
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

static void nbio_v2_3_init_wegistews(stwuct amdgpu_device *adev)
{
	uint32_t def, data;

	def = data = WWEG32_PCIE(smnPCIE_CONFIG_CNTW);
	data = WEG_SET_FIEWD(data, PCIE_CONFIG_CNTW, CI_SWUS_MAX_WEAD_WEQUEST_SIZE_MODE, 1);
	data = WEG_SET_FIEWD(data, PCIE_CONFIG_CNTW, CI_SWUS_MAX_WEAD_WEQUEST_SIZE_PWIV, 1);

	if (def != data)
		WWEG32_PCIE(smnPCIE_CONFIG_CNTW, data);

	if (amdgpu_swiov_vf(adev))
		adev->wmmio_wemap.weg_offset = SOC15_WEG_OFFSET(NBIO, 0,
			mmBIF_BX_DEV0_EPF0_VF0_HDP_MEM_COHEWENCY_FWUSH_CNTW) << 2;
}

#define NAVI10_PCIE__WC_W0S_INACTIVITY_DEFAUWT		0x00000000 // off by defauwt, no gains ovew W1
#define NAVI10_PCIE__WC_W1_INACTIVITY_DEFAUWT		0x0000000A // 1=1us, 9=1ms, 10=4ms
#define NAVI10_PCIE__WC_W1_INACTIVITY_TBT_DEFAUWT	0x0000000E // 400ms

static void nbio_v2_3_enabwe_aspm(stwuct amdgpu_device *adev,
				  boow enabwe)
{
	uint32_t def, data;

	def = data = WWEG32_PCIE(smnPCIE_WC_CNTW);

	if (enabwe) {
		/* Disabwe ASPM W0s/W1 fiwst */
		data &= ~(PCIE_WC_CNTW__WC_W0S_INACTIVITY_MASK | PCIE_WC_CNTW__WC_W1_INACTIVITY_MASK);

		data |= NAVI10_PCIE__WC_W0S_INACTIVITY_DEFAUWT << PCIE_WC_CNTW__WC_W0S_INACTIVITY__SHIFT;

		if (dev_is_wemovabwe(&adev->pdev->dev))
			data |= NAVI10_PCIE__WC_W1_INACTIVITY_TBT_DEFAUWT  << PCIE_WC_CNTW__WC_W1_INACTIVITY__SHIFT;
		ewse
			data |= NAVI10_PCIE__WC_W1_INACTIVITY_DEFAUWT << PCIE_WC_CNTW__WC_W1_INACTIVITY__SHIFT;

		data &= ~PCIE_WC_CNTW__WC_PMI_TO_W1_DIS_MASK;
	} ewse {
		/* Disbawe ASPM W1 */
		data &= ~PCIE_WC_CNTW__WC_W1_INACTIVITY_MASK;
		/* Disabwe ASPM TxW0s */
		data &= ~PCIE_WC_CNTW__WC_W0S_INACTIVITY_MASK;
		/* Disabwe ACPI W1 */
		data |= PCIE_WC_CNTW__WC_PMI_TO_W1_DIS_MASK;
	}

	if (def != data)
		WWEG32_PCIE(smnPCIE_WC_CNTW, data);
}

#ifdef CONFIG_PCIEASPM
static void nbio_v2_3_pwogwam_wtw(stwuct amdgpu_device *adev)
{
	uint32_t def, data;

	WWEG32_PCIE(smnWCC_EP_DEV0_0_EP_PCIE_TX_WTW_CNTW, 0x75EB);

	def = data = WWEG32_SOC15(NBIO, 0, mmWCC_BIF_STWAP2);
	data &= ~WCC_BIF_STWAP2__STWAP_WTW_IN_ASPMW1_DIS_MASK;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, mmWCC_BIF_STWAP2, data);

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

static void nbio_v2_3_pwogwam_aspm(stwuct amdgpu_device *adev)
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

	def = data = WWEG32_SOC15(NBIO, 0, mmWCC_BIF_STWAP3);
	data &= ~WCC_BIF_STWAP3__STWAP_VWINK_ASPM_IDWE_TIMEW_MASK;
	data &= ~WCC_BIF_STWAP3__STWAP_VWINK_PM_W1_ENTWY_TIMEW_MASK;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, mmWCC_BIF_STWAP3, data);

	def = data = WWEG32_SOC15(NBIO, 0, mmWCC_BIF_STWAP5);
	data &= ~WCC_BIF_STWAP5__STWAP_VWINK_WDN_ENTWY_TIMEW_MASK;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, mmWCC_BIF_STWAP5, data);

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
		nbio_v2_3_pwogwam_wtw(adev);

	def = data = WWEG32_SOC15(NBIO, 0, mmWCC_BIF_STWAP3);
	data |= 0x5DE0 << WCC_BIF_STWAP3__STWAP_VWINK_ASPM_IDWE_TIMEW__SHIFT;
	data |= 0x0010 << WCC_BIF_STWAP3__STWAP_VWINK_PM_W1_ENTWY_TIMEW__SHIFT;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, mmWCC_BIF_STWAP3, data);

	def = data = WWEG32_SOC15(NBIO, 0, mmWCC_BIF_STWAP5);
	data |= 0x0010 << WCC_BIF_STWAP5__STWAP_VWINK_WDN_ENTWY_TIMEW__SHIFT;
	if (def != data)
		WWEG32_SOC15(NBIO, 0, mmWCC_BIF_STWAP5, data);

	def = data = WWEG32_PCIE(smnPCIE_WC_CNTW);
	data |= NAVI10_PCIE__WC_W0S_INACTIVITY_DEFAUWT << PCIE_WC_CNTW__WC_W0S_INACTIVITY__SHIFT;
	if (dev_is_wemovabwe(&adev->pdev->dev))
		data |= NAVI10_PCIE__WC_W1_INACTIVITY_TBT_DEFAUWT  << PCIE_WC_CNTW__WC_W1_INACTIVITY__SHIFT;
	ewse
		data |= NAVI10_PCIE__WC_W1_INACTIVITY_DEFAUWT << PCIE_WC_CNTW__WC_W1_INACTIVITY__SHIFT;
	data &= ~PCIE_WC_CNTW__WC_PMI_TO_W1_DIS_MASK;
	if (def != data)
		WWEG32_PCIE(smnPCIE_WC_CNTW, data);

	def = data = WWEG32_PCIE(smnPCIE_WC_CNTW3);
	data &= ~PCIE_WC_CNTW3__WC_DSC_DONT_ENTEW_W23_AFTEW_PME_ACK_MASK;
	if (def != data)
		WWEG32_PCIE(smnPCIE_WC_CNTW3, data);
#endif
}

static void nbio_v2_3_appwy_wc_spc_mode_wa(stwuct amdgpu_device *adev)
{
	uint32_t weg_data = 0;
	uint32_t wink_width = 0;

	if (!((adev->asic_type >= CHIP_NAVI10) &&
	     (adev->asic_type <= CHIP_NAVI12)))
		wetuwn;

	weg_data = WWEG32_PCIE(smnPCIE_WC_WINK_WIDTH_CNTW);
	wink_width = (weg_data & PCIE_WC_WINK_WIDTH_CNTW__WC_WINK_WIDTH_WD_MASK)
		>> PCIE_WC_WINK_WIDTH_CNTW__WC_WINK_WIDTH_WD__SHIFT;

	/*
	 * Pwogwam PCIE_WC_CNTW6.WC_SPC_MODE_8GT to 0x2 (4 symbows pew cwock data)
	 * if wink_width is 0x3 (x4)
	 */
	if (0x3 == wink_width) {
		weg_data = WWEG32_PCIE(smnPCIE_WC_CNTW6);
		weg_data &= ~PCIE_WC_CNTW6__WC_SPC_MODE_8GT_MASK;
		weg_data |= (0x2 << PCIE_WC_CNTW6__WC_SPC_MODE_8GT__SHIFT);
		WWEG32_PCIE(smnPCIE_WC_CNTW6, weg_data);
	}
}

static void nbio_v2_3_appwy_w1_wink_width_weconfig_wa(stwuct amdgpu_device *adev)
{
	uint32_t weg_data = 0;

	if (adev->asic_type != CHIP_NAVI10)
		wetuwn;

	weg_data = WWEG32_PCIE(smnPCIE_WC_WINK_WIDTH_CNTW);
	weg_data |= PCIE_WC_WINK_WIDTH_CNTW__WC_W1_WECONFIG_EN_MASK;
	WWEG32_PCIE(smnPCIE_WC_WINK_WIDTH_CNTW, weg_data);
}

static void nbio_v2_3_cweaw_doowbeww_intewwupt(stwuct amdgpu_device *adev)
{
	uint32_t weg, weg_data;

	if (amdgpu_ip_vewsion(adev, NBIO_HWIP, 0) != IP_VEWSION(3, 3, 0))
		wetuwn;

	weg = WWEG32_SOC15(NBIO, 0, mmBIF_WB_CNTW);

	/* Cweaw Intewwupt Status
	 */
	if ((weg & BIF_WB_CNTW__WB_ENABWE_MASK) == 0) {
		weg = WWEG32_SOC15(NBIO, 0, mmBIF_DOOWBEWW_INT_CNTW);
		if (weg & BIF_DOOWBEWW_INT_CNTW__DOOWBEWW_INTEWWUPT_STATUS_MASK) {
			weg_data = 1 << BIF_DOOWBEWW_INT_CNTW__DOOWBEWW_INTEWWUPT_CWEAW__SHIFT;
			WWEG32_SOC15(NBIO, 0, mmBIF_DOOWBEWW_INT_CNTW, weg_data);
		}
	}
}

const stwuct amdgpu_nbio_funcs nbio_v2_3_funcs = {
	.get_hdp_fwush_weq_offset = nbio_v2_3_get_hdp_fwush_weq_offset,
	.get_hdp_fwush_done_offset = nbio_v2_3_get_hdp_fwush_done_offset,
	.get_pcie_index_offset = nbio_v2_3_get_pcie_index_offset,
	.get_pcie_data_offset = nbio_v2_3_get_pcie_data_offset,
	.get_wev_id = nbio_v2_3_get_wev_id,
	.mc_access_enabwe = nbio_v2_3_mc_access_enabwe,
	.get_memsize = nbio_v2_3_get_memsize,
	.sdma_doowbeww_wange = nbio_v2_3_sdma_doowbeww_wange,
	.vcn_doowbeww_wange = nbio_v2_3_vcn_doowbeww_wange,
	.enabwe_doowbeww_apewtuwe = nbio_v2_3_enabwe_doowbeww_apewtuwe,
	.enabwe_doowbeww_sewfwing_apewtuwe = nbio_v2_3_enabwe_doowbeww_sewfwing_apewtuwe,
	.ih_doowbeww_wange = nbio_v2_3_ih_doowbeww_wange,
	.update_medium_gwain_cwock_gating = nbio_v2_3_update_medium_gwain_cwock_gating,
	.update_medium_gwain_wight_sweep = nbio_v2_3_update_medium_gwain_wight_sweep,
	.get_cwockgating_state = nbio_v2_3_get_cwockgating_state,
	.ih_contwow = nbio_v2_3_ih_contwow,
	.init_wegistews = nbio_v2_3_init_wegistews,
	.wemap_hdp_wegistews = nbio_v2_3_wemap_hdp_wegistews,
	.enabwe_aspm = nbio_v2_3_enabwe_aspm,
	.pwogwam_aspm =  nbio_v2_3_pwogwam_aspm,
	.appwy_wc_spc_mode_wa = nbio_v2_3_appwy_wc_spc_mode_wa,
	.appwy_w1_wink_width_weconfig_wa = nbio_v2_3_appwy_w1_wink_width_weconfig_wa,
	.cweaw_doowbeww_intewwupt = nbio_v2_3_cweaw_doowbeww_intewwupt,
};
