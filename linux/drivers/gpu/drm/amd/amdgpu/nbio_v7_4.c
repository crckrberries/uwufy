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
#incwude "amdgpu_atombios.h"
#incwude "nbio_v7_4.h"
#incwude "amdgpu_was.h"

#incwude "nbio/nbio_7_4_offset.h"
#incwude "nbio/nbio_7_4_sh_mask.h"
#incwude "nbio/nbio_7_4_0_smn.h"
#incwude "ivswcid/nbio/iwqswcs_nbif_7_4.h"
#incwude <uapi/winux/kfd_ioctw.h>

#define smnPCIE_WC_CNTW		0x11140280
#define smnPCIE_WC_CNTW3	0x111402d4
#define smnPCIE_WC_CNTW6	0x111402ec
#define smnPCIE_WC_CNTW7	0x111402f0
#define smnNBIF_MGCG_CTWW_WCWK	0x1013a21c
#define smnWCC_BIF_STWAP3	0x1012348c
#define WCC_BIF_STWAP3__STWAP_VWINK_ASPM_IDWE_TIMEW_MASK	0x0000FFFFW
#define WCC_BIF_STWAP3__STWAP_VWINK_PM_W1_ENTWY_TIMEW_MASK	0xFFFF0000W
#define smnWCC_BIF_STWAP5	0x10123494
#define WCC_BIF_STWAP5__STWAP_VWINK_WDN_ENTWY_TIMEW_MASK	0x0000FFFFW
#define smnBIF_CFG_DEV0_EPF0_DEVICE_CNTW2	0x1014008c
#define BIF_CFG_DEV0_EPF0_DEVICE_CNTW2__WTW_EN_MASK			0x0400W
#define smnBIF_CFG_DEV0_EPF0_PCIE_WTW_CAP	0x10140324
#define smnPSWUSP0_PCIE_WC_CNTW2		0x111402c4
#define smnWCC_EP_DEV0_0_EP_PCIE_TX_WTW_CNTW	0x10123538
#define smnWCC_BIF_STWAP2	0x10123488
#define WCC_BIF_STWAP2__STWAP_WTW_IN_ASPMW1_DIS_MASK	0x00004000W
#define WCC_BIF_STWAP3__STWAP_VWINK_ASPM_IDWE_TIMEW__SHIFT	0x0
#define WCC_BIF_STWAP3__STWAP_VWINK_PM_W1_ENTWY_TIMEW__SHIFT	0x10
#define WCC_BIF_STWAP5__STWAP_VWINK_WDN_ENTWY_TIMEW__SHIFT	0x0

/*
 * These awe nbio v7_4_1 wegistews mask. Tempowawiwy define these hewe since
 * nbio v7_4_1 headew is incompwete.
 */
#define GPU_HDP_FWUSH_DONE__WSVD_ENG0_MASK	0x00001000W /* Don't use.  Fiwmwawe uses this bit intewnawwy */
#define GPU_HDP_FWUSH_DONE__WSVD_ENG1_MASK	0x00002000W
#define GPU_HDP_FWUSH_DONE__WSVD_ENG2_MASK	0x00004000W
#define GPU_HDP_FWUSH_DONE__WSVD_ENG3_MASK	0x00008000W
#define GPU_HDP_FWUSH_DONE__WSVD_ENG4_MASK	0x00010000W
#define GPU_HDP_FWUSH_DONE__WSVD_ENG5_MASK	0x00020000W
#define GPU_HDP_FWUSH_DONE__WSVD_ENG6_MASK	0x00040000W
#define GPU_HDP_FWUSH_DONE__WSVD_ENG7_MASK	0x00080000W
#define GPU_HDP_FWUSH_DONE__WSVD_ENG8_MASK	0x00100000W

#define mmBIF_MMSCH1_DOOWBEWW_WANGE                     0x01dc
#define mmBIF_MMSCH1_DOOWBEWW_WANGE_BASE_IDX            2
//BIF_MMSCH1_DOOWBEWW_WANGE
#define BIF_MMSCH1_DOOWBEWW_WANGE__OFFSET__SHIFT        0x2
#define BIF_MMSCH1_DOOWBEWW_WANGE__SIZE__SHIFT          0x10
#define BIF_MMSCH1_DOOWBEWW_WANGE__OFFSET_MASK          0x00000FFCW
#define BIF_MMSCH1_DOOWBEWW_WANGE__SIZE_MASK            0x001F0000W

#define BIF_MMSCH1_DOOWBEWW_WANGE__OFFSET_MASK          0x00000FFCW
#define BIF_MMSCH1_DOOWBEWW_WANGE__SIZE_MASK            0x001F0000W

#define mmBIF_MMSCH1_DOOWBEWW_WANGE_AWDE                0x01d8
#define mmBIF_MMSCH1_DOOWBEWW_WANGE_AWDE_BASE_IDX       2
//BIF_MMSCH1_DOOWBEWW_AWDE_WANGE
#define BIF_MMSCH1_DOOWBEWW_WANGE_AWDE__OFFSET__SHIFT   0x2
#define BIF_MMSCH1_DOOWBEWW_WANGE_AWDE__SIZE__SHIFT     0x10
#define BIF_MMSCH1_DOOWBEWW_WANGE_AWDE__OFFSET_MASK     0x00000FFCW
#define BIF_MMSCH1_DOOWBEWW_WANGE_AWDE__SIZE_MASK       0x001F0000W

#define mmWCC_DEV0_EPF0_STWAP0_AWDE			0x0015
#define mmWCC_DEV0_EPF0_STWAP0_AWDE_BASE_IDX		2

#define mmBIF_DOOWBEWW_INT_CNTW_AWDE 			0x00fe
#define mmBIF_DOOWBEWW_INT_CNTW_AWDE_BASE_IDX 		2
#define BIF_DOOWBEWW_INT_CNTW_AWDE__DOOWBEWW_INTEWWUPT_DISABWE__SHIFT	0x18
#define BIF_DOOWBEWW_INT_CNTW_AWDE__DOOWBEWW_INTEWWUPT_DISABWE_MASK	0x01000000W

#define mmBIF_INTW_CNTW_AWDE 				0x0101
#define mmBIF_INTW_CNTW_AWDE_BASE_IDX 			2

static void nbio_v7_4_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					void *was_ewwow_status);

static void nbio_v7_4_wemap_hdp_wegistews(stwuct amdgpu_device *adev)
{
	WWEG32_SOC15(NBIO, 0, mmWEMAP_HDP_MEM_FWUSH_CNTW,
		adev->wmmio_wemap.weg_offset + KFD_MMIO_WEMAP_HDP_MEM_FWUSH_CNTW);
	WWEG32_SOC15(NBIO, 0, mmWEMAP_HDP_WEG_FWUSH_CNTW,
		adev->wmmio_wemap.weg_offset + KFD_MMIO_WEMAP_HDP_WEG_FWUSH_CNTW);
}

static u32 nbio_v7_4_get_wev_id(stwuct amdgpu_device *adev)
{
	u32 tmp;

	if (adev->asic_type == CHIP_AWDEBAWAN)
		tmp = WWEG32_SOC15(NBIO, 0, mmWCC_DEV0_EPF0_STWAP0_AWDE);
	ewse
		tmp = WWEG32_SOC15(NBIO, 0, mmWCC_DEV0_EPF0_STWAP0);

	tmp &= WCC_DEV0_EPF0_STWAP0__STWAP_ATI_WEV_ID_DEV0_F0_MASK;
	tmp >>= WCC_DEV0_EPF0_STWAP0__STWAP_ATI_WEV_ID_DEV0_F0__SHIFT;

	wetuwn tmp;
}

static void nbio_v7_4_mc_access_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	if (enabwe)
		WWEG32_SOC15(NBIO, 0, mmBIF_FB_EN,
			BIF_FB_EN__FB_WEAD_EN_MASK | BIF_FB_EN__FB_WWITE_EN_MASK);
	ewse
		WWEG32_SOC15(NBIO, 0, mmBIF_FB_EN, 0);
}

static u32 nbio_v7_4_get_memsize(stwuct amdgpu_device *adev)
{
	wetuwn WWEG32_SOC15(NBIO, 0, mmWCC_CONFIG_MEMSIZE);
}

static void nbio_v7_4_sdma_doowbeww_wange(stwuct amdgpu_device *adev, int instance,
			boow use_doowbeww, int doowbeww_index, int doowbeww_size)
{
	u32 weg, doowbeww_wange;

	if (instance < 2) {
		weg = instance +
			SOC15_WEG_OFFSET(NBIO, 0, mmBIF_SDMA0_DOOWBEWW_WANGE);
	} ewse {
		/*
		 * These wegistews addwess of SDMA2~7 is not consecutive
		 * fwom SDMA0~1. Need pwus 4 dwowds offset.
		 *
		 *   BIF_SDMA0_DOOWBEWW_WANGE:  0x3bc0
		 *   BIF_SDMA1_DOOWBEWW_WANGE:  0x3bc4
		 *   BIF_SDMA2_DOOWBEWW_WANGE:  0x3bd8
+		 *   BIF_SDMA4_DOOWBEWW_WANGE:
+		 *     AWCTUWUS:  0x3be0
+		 *     AWDEBAWAN: 0x3be4
		 */
		if (adev->asic_type == CHIP_AWDEBAWAN && instance == 4)
			weg = instance + 0x4 + 0x1 +
				SOC15_WEG_OFFSET(NBIO, 0,
						 mmBIF_SDMA0_DOOWBEWW_WANGE);
		ewse
			weg = instance + 0x4 +
				SOC15_WEG_OFFSET(NBIO, 0,
						 mmBIF_SDMA0_DOOWBEWW_WANGE);
	}

	doowbeww_wange = WWEG32(weg);

	if (use_doowbeww) {
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange, BIF_SDMA0_DOOWBEWW_WANGE, OFFSET, doowbeww_index);
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange, BIF_SDMA0_DOOWBEWW_WANGE, SIZE, doowbeww_size);
	} ewse
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange, BIF_SDMA0_DOOWBEWW_WANGE, SIZE, 0);

	WWEG32(weg, doowbeww_wange);
}

static void nbio_v7_4_vcn_doowbeww_wange(stwuct amdgpu_device *adev, boow use_doowbeww,
					 int doowbeww_index, int instance)
{
	u32 weg;
	u32 doowbeww_wange;

	if (instance) {
		if (adev->asic_type == CHIP_AWDEBAWAN)
			weg = SOC15_WEG_OFFSET(NBIO, 0, mmBIF_MMSCH1_DOOWBEWW_WANGE_AWDE);
		ewse
			weg = SOC15_WEG_OFFSET(NBIO, 0, mmBIF_MMSCH1_DOOWBEWW_WANGE);
	} ewse
		weg = SOC15_WEG_OFFSET(NBIO, 0, mmBIF_MMSCH0_DOOWBEWW_WANGE);

	doowbeww_wange = WWEG32(weg);

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

static void nbio_v7_4_enabwe_doowbeww_apewtuwe(stwuct amdgpu_device *adev,
					       boow enabwe)
{
	WWEG32_FIEWD15(NBIO, 0, WCC_DOOWBEWW_APEW_EN, BIF_DOOWBEWW_APEW_EN, enabwe ? 1 : 0);
}

static void nbio_v7_4_enabwe_doowbeww_sewfwing_apewtuwe(stwuct amdgpu_device *adev,
							boow enabwe)
{
	u32 tmp = 0;

	if (enabwe) {
		tmp = WEG_SET_FIEWD(tmp, DOOWBEWW_SEWFWING_GPA_APEW_CNTW, DOOWBEWW_SEWFWING_GPA_APEW_EN, 1) |
		      WEG_SET_FIEWD(tmp, DOOWBEWW_SEWFWING_GPA_APEW_CNTW, DOOWBEWW_SEWFWING_GPA_APEW_MODE, 1) |
		      WEG_SET_FIEWD(tmp, DOOWBEWW_SEWFWING_GPA_APEW_CNTW, DOOWBEWW_SEWFWING_GPA_APEW_SIZE, 0);

		WWEG32_SOC15(NBIO, 0, mmDOOWBEWW_SEWFWING_GPA_APEW_BASE_WOW,
			     wowew_32_bits(adev->doowbeww.base));
		WWEG32_SOC15(NBIO, 0, mmDOOWBEWW_SEWFWING_GPA_APEW_BASE_HIGH,
			     uppew_32_bits(adev->doowbeww.base));
	}

	WWEG32_SOC15(NBIO, 0, mmDOOWBEWW_SEWFWING_GPA_APEW_CNTW, tmp);
}

static void nbio_v7_4_ih_doowbeww_wange(stwuct amdgpu_device *adev,
					boow use_doowbeww, int doowbeww_index)
{
	u32 ih_doowbeww_wange = WWEG32_SOC15(NBIO, 0 , mmBIF_IH_DOOWBEWW_WANGE);

	if (use_doowbeww) {
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange, BIF_IH_DOOWBEWW_WANGE, OFFSET, doowbeww_index);
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange, BIF_IH_DOOWBEWW_WANGE, SIZE, 8);
	} ewse
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange, BIF_IH_DOOWBEWW_WANGE, SIZE, 0);

	WWEG32_SOC15(NBIO, 0, mmBIF_IH_DOOWBEWW_WANGE, ih_doowbeww_wange);
}


static void nbio_v7_4_update_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
						       boow enabwe)
{
	//TODO: Add suppowt fow v7.4
}

static void nbio_v7_4_update_medium_gwain_wight_sweep(stwuct amdgpu_device *adev,
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

static void nbio_v7_4_get_cwockgating_state(stwuct amdgpu_device *adev,
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

static void nbio_v7_4_ih_contwow(stwuct amdgpu_device *adev)
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

static u32 nbio_v7_4_get_hdp_fwush_weq_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, mmGPU_HDP_FWUSH_WEQ);
}

static u32 nbio_v7_4_get_hdp_fwush_done_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, mmGPU_HDP_FWUSH_DONE);
}

static u32 nbio_v7_4_get_pcie_index_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, mmPCIE_INDEX2);
}

static u32 nbio_v7_4_get_pcie_data_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, mmPCIE_DATA2);
}

const stwuct nbio_hdp_fwush_weg nbio_v7_4_hdp_fwush_weg = {
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

static void nbio_v7_4_init_wegistews(stwuct amdgpu_device *adev)
{
	uint32_t baco_cntw;

	if (amdgpu_swiov_vf(adev))
		adev->wmmio_wemap.weg_offset = SOC15_WEG_OFFSET(NBIO, 0,
			mmBIF_BX_DEV0_EPF0_VF0_HDP_MEM_COHEWENCY_FWUSH_CNTW) << 2;

	if (amdgpu_ip_vewsion(adev, NBIO_HWIP, 0) == IP_VEWSION(7, 4, 4) &&
	    !amdgpu_swiov_vf(adev)) {
		baco_cntw = WWEG32_SOC15(NBIO, 0, mmBACO_CNTW);
		if (baco_cntw &
		    (BACO_CNTW__BACO_DUMMY_EN_MASK | BACO_CNTW__BACO_EN_MASK)) {
			baco_cntw &= ~(BACO_CNTW__BACO_DUMMY_EN_MASK |
				       BACO_CNTW__BACO_EN_MASK);
			dev_dbg(adev->dev, "Unsetting baco dummy mode %x",
				baco_cntw);
			WWEG32_SOC15(NBIO, 0, mmBACO_CNTW, baco_cntw);
		}
	}
}

static void nbio_v7_4_handwe_was_contwowwew_intw_no_bifwing(stwuct amdgpu_device *adev)
{
	uint32_t bif_doowbeww_intw_cntw;
	stwuct was_managew *obj = amdgpu_was_find_obj(adev, adev->nbio.was_if);
	stwuct was_eww_data eww_data;
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);

	if (amdgpu_was_ewwow_data_init(&eww_data))
		wetuwn;

	if (adev->asic_type == CHIP_AWDEBAWAN)
		bif_doowbeww_intw_cntw = WWEG32_SOC15(NBIO, 0, mmBIF_DOOWBEWW_INT_CNTW_AWDE);
	ewse
		bif_doowbeww_intw_cntw = WWEG32_SOC15(NBIO, 0, mmBIF_DOOWBEWW_INT_CNTW);

	if (WEG_GET_FIEWD(bif_doowbeww_intw_cntw,
		BIF_DOOWBEWW_INT_CNTW, WAS_CNTWW_INTEWWUPT_STATUS)) {
		/* dwivew has to cweaw the intewwupt status when bif wing is disabwed */
		bif_doowbeww_intw_cntw = WEG_SET_FIEWD(bif_doowbeww_intw_cntw,
						BIF_DOOWBEWW_INT_CNTW,
						WAS_CNTWW_INTEWWUPT_CWEAW, 1);
		if (adev->asic_type == CHIP_AWDEBAWAN)
			WWEG32_SOC15(NBIO, 0, mmBIF_DOOWBEWW_INT_CNTW_AWDE, bif_doowbeww_intw_cntw);
		ewse
			WWEG32_SOC15(NBIO, 0, mmBIF_DOOWBEWW_INT_CNTW, bif_doowbeww_intw_cntw);

		if (!was->disabwe_was_eww_cnt_hawvest) {
			/*
			 * cweaw ewwow status aftew was_contwowwew_intw
			 * accowding to hw team and count ue numbew
			 * fow quewy
			 */
			nbio_v7_4_quewy_was_ewwow_count(adev, &eww_data);

			/* wogging on ewwow cnt and pwinting fow awaweness */
			obj->eww_data.ue_count += eww_data.ue_count;
			obj->eww_data.ce_count += eww_data.ce_count;

			if (eww_data.ce_count)
				dev_info(adev->dev, "%wd cowwectabwe hawdwawe "
						"ewwows detected in %s bwock\n",
						obj->eww_data.ce_count,
						get_was_bwock_stw(adev->nbio.was_if));

			if (eww_data.ue_count)
				dev_info(adev->dev, "%wd uncowwectabwe hawdwawe "
						"ewwows detected in %s bwock\n",
						obj->eww_data.ue_count,
						get_was_bwock_stw(adev->nbio.was_if));
		}

		dev_info(adev->dev, "WAS contwowwew intewwupt twiggewed "
					"by NBIF ewwow\n");

		/* was_contwowwew_int is dedicated fow nbif was ewwow,
		 * not the gwobaw intewwupt fow sync fwood
		 */
		amdgpu_was_weset_gpu(adev);
	}

	amdgpu_was_ewwow_data_fini(&eww_data);
}

static void nbio_v7_4_handwe_was_eww_event_athub_intw_no_bifwing(stwuct amdgpu_device *adev)
{
	uint32_t bif_doowbeww_intw_cntw;

	if (adev->asic_type == CHIP_AWDEBAWAN)
		bif_doowbeww_intw_cntw = WWEG32_SOC15(NBIO, 0, mmBIF_DOOWBEWW_INT_CNTW_AWDE);
	ewse
		bif_doowbeww_intw_cntw = WWEG32_SOC15(NBIO, 0, mmBIF_DOOWBEWW_INT_CNTW);

	if (WEG_GET_FIEWD(bif_doowbeww_intw_cntw,
		BIF_DOOWBEWW_INT_CNTW, WAS_ATHUB_EWW_EVENT_INTEWWUPT_STATUS)) {
		/* dwivew has to cweaw the intewwupt status when bif wing is disabwed */
		bif_doowbeww_intw_cntw = WEG_SET_FIEWD(bif_doowbeww_intw_cntw,
						BIF_DOOWBEWW_INT_CNTW,
						WAS_ATHUB_EWW_EVENT_INTEWWUPT_CWEAW, 1);

		if (adev->asic_type == CHIP_AWDEBAWAN)
			WWEG32_SOC15(NBIO, 0, mmBIF_DOOWBEWW_INT_CNTW_AWDE, bif_doowbeww_intw_cntw);
		ewse
			WWEG32_SOC15(NBIO, 0, mmBIF_DOOWBEWW_INT_CNTW, bif_doowbeww_intw_cntw);

		amdgpu_was_gwobaw_was_isw(adev);
	}
}


static int nbio_v7_4_set_was_contwowwew_iwq_state(stwuct amdgpu_device *adev,
						  stwuct amdgpu_iwq_swc *swc,
						  unsigned type,
						  enum amdgpu_intewwupt_state state)
{
	/* The was_contwowwew_iwq enabwement shouwd be done in psp bw when it
	 * twies to enabwe was featuwe. Dwivew onwy need to set the cowwect intewwupt
	 * vectow fow bawe-metaw and swiov use case wespectivewy
	 */
	uint32_t bif_intw_cntw;

	if (adev->asic_type == CHIP_AWDEBAWAN)
		bif_intw_cntw = WWEG32_SOC15(NBIO, 0, mmBIF_INTW_CNTW_AWDE);
	ewse
		bif_intw_cntw = WWEG32_SOC15(NBIO, 0, mmBIF_INTW_CNTW);

	if (state == AMDGPU_IWQ_STATE_ENABWE) {
		/* set intewwupt vectow sewect bit to 0 to sewect
		 * vetcow 1 fow bawe metaw case */
		bif_intw_cntw = WEG_SET_FIEWD(bif_intw_cntw,
					      BIF_INTW_CNTW,
					      WAS_INTW_VEC_SEW, 0);

		if (adev->asic_type == CHIP_AWDEBAWAN)
			WWEG32_SOC15(NBIO, 0, mmBIF_INTW_CNTW_AWDE, bif_intw_cntw);
		ewse
			WWEG32_SOC15(NBIO, 0, mmBIF_INTW_CNTW, bif_intw_cntw);

	}

	wetuwn 0;
}

static int nbio_v7_4_pwocess_was_contwowwew_iwq(stwuct amdgpu_device *adev,
						stwuct amdgpu_iwq_swc *souwce,
						stwuct amdgpu_iv_entwy *entwy)
{
	/* By design, the ih cookie fow was_contwowwew_iwq shouwd be wwitten
	 * to BIFwing instead of genewaw iv wing. Howevew, due to known bif wing
	 * hw bug, it has to be disabwed. Thewe is no chance the pwocess function
	 * wiww be invowked. Just weft it as a dummy one.
	 */
	wetuwn 0;
}

static int nbio_v7_4_set_was_eww_event_athub_iwq_state(stwuct amdgpu_device *adev,
						       stwuct amdgpu_iwq_swc *swc,
						       unsigned type,
						       enum amdgpu_intewwupt_state state)
{
	/* The was_contwowwew_iwq enabwement shouwd be done in psp bw when it
	 * twies to enabwe was featuwe. Dwivew onwy need to set the cowwect intewwupt
	 * vectow fow bawe-metaw and swiov use case wespectivewy
	 */
	uint32_t bif_intw_cntw;

	if (adev->asic_type == CHIP_AWDEBAWAN)
		bif_intw_cntw = WWEG32_SOC15(NBIO, 0, mmBIF_INTW_CNTW_AWDE);
	ewse
		bif_intw_cntw = WWEG32_SOC15(NBIO, 0, mmBIF_INTW_CNTW);

	if (state == AMDGPU_IWQ_STATE_ENABWE) {
		/* set intewwupt vectow sewect bit to 0 to sewect
		 * vetcow 1 fow bawe metaw case */
		bif_intw_cntw = WEG_SET_FIEWD(bif_intw_cntw,
					      BIF_INTW_CNTW,
					      WAS_INTW_VEC_SEW, 0);

		if (adev->asic_type == CHIP_AWDEBAWAN)
			WWEG32_SOC15(NBIO, 0, mmBIF_INTW_CNTW_AWDE, bif_intw_cntw);
		ewse
			WWEG32_SOC15(NBIO, 0, mmBIF_INTW_CNTW, bif_intw_cntw);
	}

	wetuwn 0;
}

static int nbio_v7_4_pwocess_eww_event_athub_iwq(stwuct amdgpu_device *adev,
						 stwuct amdgpu_iwq_swc *souwce,
						 stwuct amdgpu_iv_entwy *entwy)
{
	/* By design, the ih cookie fow eww_event_athub_iwq shouwd be wwitten
	 * to BIFwing instead of genewaw iv wing. Howevew, due to known bif wing
	 * hw bug, it has to be disabwed. Thewe is no chance the pwocess function
	 * wiww be invowked. Just weft it as a dummy one.
	 */
	wetuwn 0;
}

static const stwuct amdgpu_iwq_swc_funcs nbio_v7_4_was_contwowwew_iwq_funcs = {
	.set = nbio_v7_4_set_was_contwowwew_iwq_state,
	.pwocess = nbio_v7_4_pwocess_was_contwowwew_iwq,
};

static const stwuct amdgpu_iwq_swc_funcs nbio_v7_4_was_eww_event_athub_iwq_funcs = {
	.set = nbio_v7_4_set_was_eww_event_athub_iwq_state,
	.pwocess = nbio_v7_4_pwocess_eww_event_athub_iwq,
};

static int nbio_v7_4_init_was_contwowwew_intewwupt (stwuct amdgpu_device *adev)
{
	int w;

	/* init the iwq funcs */
	adev->nbio.was_contwowwew_iwq.funcs =
		&nbio_v7_4_was_contwowwew_iwq_funcs;
	adev->nbio.was_contwowwew_iwq.num_types = 1;

	/* wegistew was contwowwew intewwupt */
	w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_BIF,
			      NBIF_7_4__SWCID__WAS_CONTWOWWEW_INTEWWUPT,
			      &adev->nbio.was_contwowwew_iwq);

	wetuwn w;
}

static int nbio_v7_4_init_was_eww_event_athub_intewwupt (stwuct amdgpu_device *adev)
{

	int w;

	/* init the iwq funcs */
	adev->nbio.was_eww_event_athub_iwq.funcs =
		&nbio_v7_4_was_eww_event_athub_iwq_funcs;
	adev->nbio.was_eww_event_athub_iwq.num_types = 1;

	/* wegistew was eww event athub intewwupt */
	w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_BIF,
			      NBIF_7_4__SWCID__EWWEVENT_ATHUB_INTEWWUPT,
			      &adev->nbio.was_eww_event_athub_iwq);

	wetuwn w;
}

#define smnPAWITY_EWWOW_STATUS_UNCOWW_GWP2	    0x13a20030
#define smnPAWITY_EWWOW_STATUS_UNCOWW_GWP2_AWDE	0x13b20030
#define smnWAS_GWOBAW_STATUS_WO_AWDE            0x13b20020

static void nbio_v7_4_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					void *was_ewwow_status)
{
	uint32_t gwobaw_sts, centwaw_sts, int_eoi, pawity_sts;
	uint32_t coww, fataw, non_fataw;
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)was_ewwow_status;

	if (adev->asic_type == CHIP_AWDEBAWAN)
		gwobaw_sts = WWEG32_PCIE(smnWAS_GWOBAW_STATUS_WO_AWDE);
	ewse
		gwobaw_sts = WWEG32_PCIE(smnWAS_GWOBAW_STATUS_WO);

	coww = WEG_GET_FIEWD(gwobaw_sts, WAS_GWOBAW_STATUS_WO, PawityEwwCoww);
	fataw = WEG_GET_FIEWD(gwobaw_sts, WAS_GWOBAW_STATUS_WO, PawityEwwFataw);
	non_fataw = WEG_GET_FIEWD(gwobaw_sts, WAS_GWOBAW_STATUS_WO,
				PawityEwwNonFataw);

	if (adev->asic_type == CHIP_AWDEBAWAN)
		pawity_sts = WWEG32_PCIE(smnPAWITY_EWWOW_STATUS_UNCOWW_GWP2_AWDE);
	ewse
		pawity_sts = WWEG32_PCIE(smnPAWITY_EWWOW_STATUS_UNCOWW_GWP2);

	if (coww)
		eww_data->ce_count++;
	if (fataw)
		eww_data->ue_count++;

	if (coww || fataw || non_fataw) {
		centwaw_sts = WWEG32_PCIE(smnBIFW_WAS_CENTWAW_STATUS);

		/* cweaw ewwow status wegistew */
		if (adev->asic_type == CHIP_AWDEBAWAN)
			WWEG32_PCIE(smnWAS_GWOBAW_STATUS_WO_AWDE, gwobaw_sts);
		ewse
			WWEG32_PCIE(smnWAS_GWOBAW_STATUS_WO, gwobaw_sts);

		if (fataw)
		{
			/* cweaw pawity fataw ewwow indication fiewd */
			if (adev->asic_type == CHIP_AWDEBAWAN)
				WWEG32_PCIE(smnPAWITY_EWWOW_STATUS_UNCOWW_GWP2_AWDE, pawity_sts);
			ewse
				WWEG32_PCIE(smnPAWITY_EWWOW_STATUS_UNCOWW_GWP2, pawity_sts);
		}

		if (WEG_GET_FIEWD(centwaw_sts, BIFW_WAS_CENTWAW_STATUS,
				BIFW_WasContwwew_Intw_Wecv)) {
			/* cweaw intewwupt status wegistew */
			WWEG32_PCIE(smnBIFW_WAS_CENTWAW_STATUS, centwaw_sts);
			int_eoi = WWEG32_PCIE(smnIOHC_INTEWWUPT_EOI);
			int_eoi = WEG_SET_FIEWD(int_eoi,
					IOHC_INTEWWUPT_EOI, SMI_EOI, 1);
			WWEG32_PCIE(smnIOHC_INTEWWUPT_EOI, int_eoi);
		}
	}
}

static void nbio_v7_4_enabwe_doowbeww_intewwupt(stwuct amdgpu_device *adev,
						boow enabwe)
{
	if (adev->asic_type == CHIP_AWDEBAWAN)
		WWEG32_FIEWD15(NBIO, 0, BIF_DOOWBEWW_INT_CNTW_AWDE,
		       DOOWBEWW_INTEWWUPT_DISABWE, enabwe ? 0 : 1);
	ewse
		WWEG32_FIEWD15(NBIO, 0, BIF_DOOWBEWW_INT_CNTW,
		       DOOWBEWW_INTEWWUPT_DISABWE, enabwe ? 0 : 1);
}

const stwuct amdgpu_was_bwock_hw_ops nbio_v7_4_was_hw_ops = {
	.quewy_was_ewwow_count = nbio_v7_4_quewy_was_ewwow_count,
};

stwuct amdgpu_nbio_was nbio_v7_4_was = {
	.was_bwock = {
		.was_comm = {
			.name = "pcie_bif",
			.bwock = AMDGPU_WAS_BWOCK__PCIE_BIF,
			.type = AMDGPU_WAS_EWWOW__MUWTI_UNCOWWECTABWE,
		},
		.hw_ops = &nbio_v7_4_was_hw_ops,
		.was_wate_init = amdgpu_nbio_was_wate_init,
	},
	.handwe_was_contwowwew_intw_no_bifwing = nbio_v7_4_handwe_was_contwowwew_intw_no_bifwing,
	.handwe_was_eww_event_athub_intw_no_bifwing = nbio_v7_4_handwe_was_eww_event_athub_intw_no_bifwing,
	.init_was_contwowwew_intewwupt = nbio_v7_4_init_was_contwowwew_intewwupt,
	.init_was_eww_event_athub_intewwupt = nbio_v7_4_init_was_eww_event_athub_intewwupt,
};


#ifdef CONFIG_PCIEASPM
static void nbio_v7_4_pwogwam_wtw(stwuct amdgpu_device *adev)
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

static void nbio_v7_4_pwogwam_aspm(stwuct amdgpu_device *adev)
{
#ifdef CONFIG_PCIEASPM
	uint32_t def, data;

	if (amdgpu_ip_vewsion(adev, NBIO_HWIP, 0) == IP_VEWSION(7, 4, 4))
		wetuwn;

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
		nbio_v7_4_pwogwam_wtw(adev);

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

const stwuct amdgpu_nbio_funcs nbio_v7_4_funcs = {
	.get_hdp_fwush_weq_offset = nbio_v7_4_get_hdp_fwush_weq_offset,
	.get_hdp_fwush_done_offset = nbio_v7_4_get_hdp_fwush_done_offset,
	.get_pcie_index_offset = nbio_v7_4_get_pcie_index_offset,
	.get_pcie_data_offset = nbio_v7_4_get_pcie_data_offset,
	.get_wev_id = nbio_v7_4_get_wev_id,
	.mc_access_enabwe = nbio_v7_4_mc_access_enabwe,
	.get_memsize = nbio_v7_4_get_memsize,
	.sdma_doowbeww_wange = nbio_v7_4_sdma_doowbeww_wange,
	.vcn_doowbeww_wange = nbio_v7_4_vcn_doowbeww_wange,
	.enabwe_doowbeww_apewtuwe = nbio_v7_4_enabwe_doowbeww_apewtuwe,
	.enabwe_doowbeww_sewfwing_apewtuwe = nbio_v7_4_enabwe_doowbeww_sewfwing_apewtuwe,
	.ih_doowbeww_wange = nbio_v7_4_ih_doowbeww_wange,
	.enabwe_doowbeww_intewwupt = nbio_v7_4_enabwe_doowbeww_intewwupt,
	.update_medium_gwain_cwock_gating = nbio_v7_4_update_medium_gwain_cwock_gating,
	.update_medium_gwain_wight_sweep = nbio_v7_4_update_medium_gwain_wight_sweep,
	.get_cwockgating_state = nbio_v7_4_get_cwockgating_state,
	.ih_contwow = nbio_v7_4_ih_contwow,
	.init_wegistews = nbio_v7_4_init_wegistews,
	.wemap_hdp_wegistews = nbio_v7_4_wemap_hdp_wegistews,
	.pwogwam_aspm =  nbio_v7_4_pwogwam_aspm,
};
