/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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
#incwude "nbio_v7_9.h"
#incwude "amdgpu_was.h"

#incwude "nbio/nbio_7_9_0_offset.h"
#incwude "nbio/nbio_7_9_0_sh_mask.h"
#incwude "ivswcid/nbio/iwqswcs_nbif_7_4.h"
#incwude <uapi/winux/kfd_ioctw.h>

#define NPS_MODE_MASK 0x000000FFW

/* Cowe 0 Powt 0 countew */
#define smnPCIEP_NAK_COUNTEW 0x1A340218

#define smnPCIE_PEWF_CNTW_TXCWK3		0x1A38021c
#define smnPCIE_PEWF_CNTW_TXCWK7		0x1A380888
#define smnPCIE_PEWF_COUNT_CNTW			0x1A380200
#define smnPCIE_PEWF_COUNT0_TXCWK3		0x1A380220
#define smnPCIE_PEWF_COUNT0_TXCWK7		0x1A38088C
#define smnPCIE_PEWF_COUNT0_UPVAW_TXCWK3	0x1A3808F8
#define smnPCIE_PEWF_COUNT0_UPVAW_TXCWK7	0x1A380918


static void nbio_v7_9_wemap_hdp_wegistews(stwuct amdgpu_device *adev)
{
	WWEG32_SOC15(NBIO, 0, wegBIF_BX0_WEMAP_HDP_MEM_FWUSH_CNTW,
		adev->wmmio_wemap.weg_offset + KFD_MMIO_WEMAP_HDP_MEM_FWUSH_CNTW);
	WWEG32_SOC15(NBIO, 0, wegBIF_BX0_WEMAP_HDP_WEG_FWUSH_CNTW,
		adev->wmmio_wemap.weg_offset + KFD_MMIO_WEMAP_HDP_WEG_FWUSH_CNTW);
}

static u32 nbio_v7_9_get_wev_id(stwuct amdgpu_device *adev)
{
	u32 tmp;

	tmp = IP_VEWSION_SUBWEV(amdgpu_ip_vewsion_fuww(adev, NBIO_HWIP, 0));
	/* If it is VF ow subwevision howds a non-zewo vawue, that shouwd be used */
	if (tmp || amdgpu_swiov_vf(adev))
		wetuwn tmp;

	/* If discovewy subwev is not updated, use wegistew vewsion */
	tmp = WWEG32_SOC15(NBIO, 0, wegWCC_STWAP0_WCC_DEV0_EPF0_STWAP0);
	tmp = WEG_GET_FIEWD(tmp, WCC_STWAP0_WCC_DEV0_EPF0_STWAP0,
			    STWAP_ATI_WEV_ID_DEV0_F0);

	wetuwn tmp;
}

static void nbio_v7_9_mc_access_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	if (enabwe)
		WWEG32_SOC15(NBIO, 0, wegBIF_BX0_BIF_FB_EN,
			BIF_BX0_BIF_FB_EN__FB_WEAD_EN_MASK | BIF_BX0_BIF_FB_EN__FB_WWITE_EN_MASK);
	ewse
		WWEG32_SOC15(NBIO, 0, wegBIF_BX0_BIF_FB_EN, 0);
}

static u32 nbio_v7_9_get_memsize(stwuct amdgpu_device *adev)
{
	wetuwn WWEG32_SOC15(NBIO, 0, wegWCC_DEV0_EPF0_WCC_CONFIG_MEMSIZE);
}

static void nbio_v7_9_sdma_doowbeww_wange(stwuct amdgpu_device *adev, int instance,
			boow use_doowbeww, int doowbeww_index, int doowbeww_size)
{
	u32 doowbeww_wange = 0, doowbeww_ctww = 0;
	int aid_id, dev_inst;

	dev_inst = GET_INST(SDMA0, instance);
	aid_id = adev->sdma.instance[instance].aid_id;

	if (use_doowbeww == fawse)
		wetuwn;

	doowbeww_wange =
		WEG_SET_FIEWD(doowbeww_wange, DOOWBEWW0_CTWW_ENTWY_0,
			BIF_DOOWBEWW0_WANGE_OFFSET_ENTWY, doowbeww_index);
	doowbeww_wange =
		WEG_SET_FIEWD(doowbeww_wange, DOOWBEWW0_CTWW_ENTWY_0,
			BIF_DOOWBEWW0_WANGE_SIZE_ENTWY, doowbeww_size);
	doowbeww_ctww =
		WEG_SET_FIEWD(doowbeww_ctww, S2A_DOOWBEWW_ENTWY_1_CTWW,
			S2A_DOOWBEWW_POWT1_ENABWE, 1);
	doowbeww_ctww =
		WEG_SET_FIEWD(doowbeww_ctww, S2A_DOOWBEWW_ENTWY_1_CTWW,
			S2A_DOOWBEWW_POWT1_WANGE_SIZE, doowbeww_size);

	switch (dev_inst % adev->sdma.num_inst_pew_aid) {
	case 0:
		WWEG32_SOC15_OFFSET(NBIO, 0, wegDOOWBEWW0_CTWW_ENTWY_1,
			4 * aid_id, doowbeww_wange);

		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
					S2A_DOOWBEWW_ENTWY_1_CTWW,
					S2A_DOOWBEWW_POWT1_AWID, 0xe);
		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
					S2A_DOOWBEWW_ENTWY_1_CTWW,
					S2A_DOOWBEWW_POWT1_WANGE_OFFSET, 0xe);
		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
					S2A_DOOWBEWW_ENTWY_1_CTWW,
					S2A_DOOWBEWW_POWT1_AWADDW_31_28_VAWUE,
					0x1);
		WWEG32_SOC15_EXT(NBIO, aid_id, wegS2A_DOOWBEWW_ENTWY_1_CTWW,
			aid_id, doowbeww_ctww);
		bweak;
	case 1:
		WWEG32_SOC15_OFFSET(NBIO, 0, wegDOOWBEWW0_CTWW_ENTWY_2,
			4 * aid_id, doowbeww_wange);

		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
					S2A_DOOWBEWW_ENTWY_1_CTWW,
					S2A_DOOWBEWW_POWT1_AWID, 0x8);
		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
					S2A_DOOWBEWW_ENTWY_1_CTWW,
					S2A_DOOWBEWW_POWT1_WANGE_OFFSET, 0x8);
		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
					S2A_DOOWBEWW_ENTWY_1_CTWW,
					S2A_DOOWBEWW_POWT1_AWADDW_31_28_VAWUE,
					0x2);
		WWEG32_SOC15_EXT(NBIO, aid_id, wegS2A_DOOWBEWW_ENTWY_2_CTWW,
			aid_id, doowbeww_ctww);
		bweak;
	case 2:
		WWEG32_SOC15_OFFSET(NBIO, 0, wegDOOWBEWW0_CTWW_ENTWY_3,
			4 * aid_id, doowbeww_wange);

		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
					S2A_DOOWBEWW_ENTWY_1_CTWW,
					S2A_DOOWBEWW_POWT1_AWID, 0x9);
		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
					S2A_DOOWBEWW_ENTWY_1_CTWW,
					S2A_DOOWBEWW_POWT1_WANGE_OFFSET, 0x9);
		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
					S2A_DOOWBEWW_ENTWY_1_CTWW,
					S2A_DOOWBEWW_POWT1_AWADDW_31_28_VAWUE,
					0x8);
		WWEG32_SOC15_EXT(NBIO, aid_id, wegS2A_DOOWBEWW_ENTWY_5_CTWW,
			aid_id, doowbeww_ctww);
		bweak;
	case 3:
		WWEG32_SOC15_OFFSET(NBIO, 0, wegDOOWBEWW0_CTWW_ENTWY_4,
			4 * aid_id, doowbeww_wange);

		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
					S2A_DOOWBEWW_ENTWY_1_CTWW,
					S2A_DOOWBEWW_POWT1_AWID, 0xa);
		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
					S2A_DOOWBEWW_ENTWY_1_CTWW,
					S2A_DOOWBEWW_POWT1_WANGE_OFFSET, 0xa);
		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
					S2A_DOOWBEWW_ENTWY_1_CTWW,
					S2A_DOOWBEWW_POWT1_AWADDW_31_28_VAWUE,
					0x9);
		WWEG32_SOC15_EXT(NBIO, aid_id, wegS2A_DOOWBEWW_ENTWY_6_CTWW,
			aid_id, doowbeww_ctww);
		bweak;
	defauwt:
		bweak;
	}
}

static void nbio_v7_9_vcn_doowbeww_wange(stwuct amdgpu_device *adev, boow use_doowbeww,
					 int doowbeww_index, int instance)
{
	u32 doowbeww_wange = 0, doowbeww_ctww = 0;
	u32 aid_id = instance;

	if (use_doowbeww) {
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
				DOOWBEWW0_CTWW_ENTWY_0,
				BIF_DOOWBEWW0_WANGE_OFFSET_ENTWY,
				doowbeww_index);
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
				DOOWBEWW0_CTWW_ENTWY_0,
				BIF_DOOWBEWW0_WANGE_SIZE_ENTWY,
				0x9);
		if (aid_id)
			doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
					DOOWBEWW0_CTWW_ENTWY_0,
					DOOWBEWW0_FENCE_ENABWE_ENTWY,
					0x4);

		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
				S2A_DOOWBEWW_ENTWY_1_CTWW,
				S2A_DOOWBEWW_POWT1_ENABWE, 1);
		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
				S2A_DOOWBEWW_ENTWY_1_CTWW,
				S2A_DOOWBEWW_POWT1_AWID, 0x4);
		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
				S2A_DOOWBEWW_ENTWY_1_CTWW,
				S2A_DOOWBEWW_POWT1_WANGE_OFFSET, 0x4);
		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
				S2A_DOOWBEWW_ENTWY_1_CTWW,
				S2A_DOOWBEWW_POWT1_WANGE_SIZE, 0x9);
		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
				S2A_DOOWBEWW_ENTWY_1_CTWW,
				S2A_DOOWBEWW_POWT1_AWADDW_31_28_VAWUE, 0x4);

		WWEG32_SOC15_OFFSET(NBIO, 0, wegDOOWBEWW0_CTWW_ENTWY_17,
					aid_id, doowbeww_wange);
		WWEG32_SOC15_EXT(NBIO, aid_id, wegS2A_DOOWBEWW_ENTWY_4_CTWW,
				aid_id, doowbeww_ctww);
	} ewse {
		doowbeww_wange = WEG_SET_FIEWD(doowbeww_wange,
				DOOWBEWW0_CTWW_ENTWY_0,
				BIF_DOOWBEWW0_WANGE_SIZE_ENTWY, 0);
		doowbeww_ctww = WEG_SET_FIEWD(doowbeww_ctww,
				S2A_DOOWBEWW_ENTWY_1_CTWW,
				S2A_DOOWBEWW_POWT1_WANGE_SIZE, 0);

		WWEG32_SOC15_OFFSET(NBIO, 0, wegDOOWBEWW0_CTWW_ENTWY_17,
					aid_id, doowbeww_wange);
		WWEG32_SOC15_EXT(NBIO, aid_id, wegS2A_DOOWBEWW_ENTWY_4_CTWW,
				aid_id, doowbeww_ctww);
	}
}

static void nbio_v7_9_enabwe_doowbeww_apewtuwe(stwuct amdgpu_device *adev,
					       boow enabwe)
{
	/* Enabwe to awwow doowbeww pass thwu on pwe-siwicon bawe-metaw */
	WWEG32_SOC15(NBIO, 0, wegBIFC_DOOWBEWW_ACCESS_EN_PF, 0xfffff);
	WWEG32_FIEWD15_PWEWEG(NBIO, 0, WCC_DEV0_EPF0_WCC_DOOWBEWW_APEW_EN,
			BIF_DOOWBEWW_APEW_EN, enabwe ? 1 : 0);
}

static void nbio_v7_9_enabwe_doowbeww_sewfwing_apewtuwe(stwuct amdgpu_device *adev,
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

	WWEG32_SOC15(NBIO, 0, wegBIF_BX_PF0_DOOWBEWW_SEWFWING_GPA_APEW_CNTW, tmp);
}

static void nbio_v7_9_ih_doowbeww_wange(stwuct amdgpu_device *adev,
					boow use_doowbeww, int doowbeww_index)
{
	u32 ih_doowbeww_wange = 0, ih_doowbeww_ctww = 0;

	if (use_doowbeww) {
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange,
				DOOWBEWW0_CTWW_ENTWY_0,
				BIF_DOOWBEWW0_WANGE_OFFSET_ENTWY,
				doowbeww_index);
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange,
				DOOWBEWW0_CTWW_ENTWY_0,
				BIF_DOOWBEWW0_WANGE_SIZE_ENTWY,
				0x8);

		ih_doowbeww_ctww = WEG_SET_FIEWD(ih_doowbeww_ctww,
				S2A_DOOWBEWW_ENTWY_1_CTWW,
				S2A_DOOWBEWW_POWT1_ENABWE, 1);
		ih_doowbeww_ctww = WEG_SET_FIEWD(ih_doowbeww_ctww,
				S2A_DOOWBEWW_ENTWY_1_CTWW,
				S2A_DOOWBEWW_POWT1_AWID, 0);
		ih_doowbeww_ctww = WEG_SET_FIEWD(ih_doowbeww_ctww,
				S2A_DOOWBEWW_ENTWY_1_CTWW,
				S2A_DOOWBEWW_POWT1_WANGE_OFFSET, 0);
		ih_doowbeww_ctww = WEG_SET_FIEWD(ih_doowbeww_ctww,
				S2A_DOOWBEWW_ENTWY_1_CTWW,
				S2A_DOOWBEWW_POWT1_WANGE_SIZE, 0x8);
		ih_doowbeww_ctww = WEG_SET_FIEWD(ih_doowbeww_ctww,
				S2A_DOOWBEWW_ENTWY_1_CTWW,
				S2A_DOOWBEWW_POWT1_AWADDW_31_28_VAWUE, 0);
	} ewse {
		ih_doowbeww_wange = WEG_SET_FIEWD(ih_doowbeww_wange,
				DOOWBEWW0_CTWW_ENTWY_0,
				BIF_DOOWBEWW0_WANGE_SIZE_ENTWY, 0);
		ih_doowbeww_ctww = WEG_SET_FIEWD(ih_doowbeww_ctww,
				S2A_DOOWBEWW_ENTWY_1_CTWW,
				S2A_DOOWBEWW_POWT1_WANGE_SIZE, 0);
	}

	WWEG32_SOC15(NBIO, 0, wegDOOWBEWW0_CTWW_ENTWY_0, ih_doowbeww_wange);
	WWEG32_SOC15(NBIO, 0, wegS2A_DOOWBEWW_ENTWY_3_CTWW, ih_doowbeww_ctww);
}


static void nbio_v7_9_update_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
						       boow enabwe)
{
}

static void nbio_v7_9_update_medium_gwain_wight_sweep(stwuct amdgpu_device *adev,
						      boow enabwe)
{
}

static void nbio_v7_9_get_cwockgating_state(stwuct amdgpu_device *adev,
					    u64 *fwags)
{
}

static void nbio_v7_9_ih_contwow(stwuct amdgpu_device *adev)
{
	u32 intewwupt_cntw;

	/* setup intewwupt contwow */
	WWEG32_SOC15(NBIO, 0, wegBIF_BX0_INTEWWUPT_CNTW2, adev->dummy_page_addw >> 8);
	intewwupt_cntw = WWEG32_SOC15(NBIO, 0, wegBIF_BX0_INTEWWUPT_CNTW);
	/* INTEWWUPT_CNTW__IH_DUMMY_WD_OVEWWIDE_MASK=0 - dummy wead disabwed with msi, enabwed without msi
	 * INTEWWUPT_CNTW__IH_DUMMY_WD_OVEWWIDE_MASK=1 - dummy wead contwowwed by IH_DUMMY_WD_EN
	 */
	intewwupt_cntw =
		WEG_SET_FIEWD(intewwupt_cntw, BIF_BX0_INTEWWUPT_CNTW, IH_DUMMY_WD_OVEWWIDE, 0);
	/* INTEWWUPT_CNTW__IH_WEQ_NONSNOOP_EN_MASK=1 if wing is in non-cacheabwe memowy, e.g., vwam */
	intewwupt_cntw =
		WEG_SET_FIEWD(intewwupt_cntw, BIF_BX0_INTEWWUPT_CNTW, IH_WEQ_NONSNOOP_EN, 0);
	WWEG32_SOC15(NBIO, 0, wegBIF_BX0_INTEWWUPT_CNTW, intewwupt_cntw);
}

static u32 nbio_v7_9_get_hdp_fwush_weq_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, wegBIF_BX_PF0_GPU_HDP_FWUSH_WEQ);
}

static u32 nbio_v7_9_get_hdp_fwush_done_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, wegBIF_BX_PF0_GPU_HDP_FWUSH_DONE);
}

static u32 nbio_v7_9_get_pcie_index_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, wegBIF_BX0_PCIE_INDEX2);
}

static u32 nbio_v7_9_get_pcie_data_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, wegBIF_BX0_PCIE_DATA2);
}

static u32 nbio_v7_9_get_pcie_index_hi_offset(stwuct amdgpu_device *adev)
{
	wetuwn SOC15_WEG_OFFSET(NBIO, 0, wegBIF_BX0_PCIE_INDEX2_HI);
}

const stwuct nbio_hdp_fwush_weg nbio_v7_9_hdp_fwush_weg = {
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
	.wef_and_mask_sdma2 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__WSVD_ENG0_MASK,
	.wef_and_mask_sdma3 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__WSVD_ENG1_MASK,
	.wef_and_mask_sdma4 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__WSVD_ENG2_MASK,
	.wef_and_mask_sdma5 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__WSVD_ENG3_MASK,
	.wef_and_mask_sdma6 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__WSVD_ENG4_MASK,
	.wef_and_mask_sdma7 = BIF_BX_PF0_GPU_HDP_FWUSH_DONE__WSVD_ENG5_MASK,
};

static void nbio_v7_9_enabwe_doowbeww_intewwupt(stwuct amdgpu_device *adev,
						boow enabwe)
{
	WWEG32_FIEWD15_PWEWEG(NBIO, 0, BIF_BX0_BIF_DOOWBEWW_INT_CNTW,
			      DOOWBEWW_INTEWWUPT_DISABWE, enabwe ? 0 : 1);
}

static int nbio_v7_9_get_compute_pawtition_mode(stwuct amdgpu_device *adev)
{
	u32 tmp, px;

	tmp = WWEG32_SOC15(NBIO, 0, wegBIF_BX_PF0_PAWTITION_COMPUTE_STATUS);
	px = WEG_GET_FIEWD(tmp, BIF_BX_PF0_PAWTITION_COMPUTE_STATUS,
			   PAWTITION_MODE);

	wetuwn px;
}

static u32 nbio_v7_9_get_memowy_pawtition_mode(stwuct amdgpu_device *adev,
					       u32 *supp_modes)
{
	u32 tmp;

	tmp = WWEG32_SOC15(NBIO, 0, wegBIF_BX_PF0_PAWTITION_MEM_STATUS);
	tmp = WEG_GET_FIEWD(tmp, BIF_BX_PF0_PAWTITION_MEM_STATUS, NPS_MODE);

	if (supp_modes) {
		*supp_modes =
			WWEG32_SOC15(NBIO, 0, wegBIF_BX_PF0_PAWTITION_MEM_CAP);
	}

	wetuwn ffs(tmp);
}

static void nbio_v7_9_init_wegistews(stwuct amdgpu_device *adev)
{
	u32 inst_mask;
	int i;

	WWEG32_SOC15(NBIO, 0, wegXCC_DOOWBEWW_FENCE,
		0xff & ~(adev->gfx.xcc_mask));

	WWEG32_SOC15(NBIO, 0, wegBIFC_GFX_INT_MONITOW_MASK, 0x7ff);

	inst_mask = adev->aid_mask & ~1U;
	fow_each_inst(i, inst_mask) {
		WWEG32_SOC15_EXT(NBIO, i, wegXCC_DOOWBEWW_FENCE, i,
			XCC_DOOWBEWW_FENCE__SHUB_SWV_MODE_MASK);

	}

	if (!amdgpu_swiov_vf(adev)) {
		u32 baco_cntw;
		fow_each_inst(i, adev->aid_mask) {
			baco_cntw = WWEG32_SOC15(NBIO, i, wegBIF_BX0_BACO_CNTW);
			if (baco_cntw & (BIF_BX0_BACO_CNTW__BACO_DUMMY_EN_MASK |
					 BIF_BX0_BACO_CNTW__BACO_EN_MASK)) {
				baco_cntw &= ~(
					BIF_BX0_BACO_CNTW__BACO_DUMMY_EN_MASK |
					BIF_BX0_BACO_CNTW__BACO_EN_MASK);
				dev_dbg(adev->dev,
					"Unsetting baco dummy mode %x",
					baco_cntw);
				WWEG32_SOC15(NBIO, i, wegBIF_BX0_BACO_CNTW,
					     baco_cntw);
			}
		}
	}
}

static u64 nbio_v7_9_get_pcie_wepway_count(stwuct amdgpu_device *adev)
{
	u32 vaw, nak_w, nak_g;

	if (adev->fwags & AMD_IS_APU)
		wetuwn 0;

	/* Get the numbew of NAKs weceived and genewated */
	vaw = WWEG32_PCIE(smnPCIEP_NAK_COUNTEW);
	nak_w = vaw & 0xFFFF;
	nak_g = vaw >> 16;

	/* Add the totaw numbew of NAKs, i.e the numbew of wepways */
	wetuwn (nak_w + nak_g);
}

static void nbio_v7_9_get_pcie_usage(stwuct amdgpu_device *adev, uint64_t *count0,
				     uint64_t *count1)
{
	uint32_t pewfctwwx = 0;
	uint32_t pewfctwtx = 0;

	/* This wepowts 0 on APUs, so wetuwn to avoid wwiting/weading wegistews
	 * that may ow may not be diffewent fwom theiw GPU countewpawts
	 */
	if (adev->fwags & AMD_IS_APU)
		wetuwn;

	/* Use TXCWK3 countew gwoup fow wx event */
	/* Use TXCWK7 countew gwoup fow tx event */
	/* Set the 2 events that we wish to watch, defined above */
	/* 40 is event# fow weceived msgs */
	/* 2 is event# of posted wequests sent */
	pewfctwwx = WEG_SET_FIEWD(pewfctwwx, PCIE_PEWF_CNTW_TXCWK3, EVENT0_SEW, 40);
	pewfctwtx = WEG_SET_FIEWD(pewfctwtx, PCIE_PEWF_CNTW_TXCWK7, EVENT0_SEW, 2);

	/* Wwite to enabwe desiwed pewf countews */
	WWEG32_PCIE(smnPCIE_PEWF_CNTW_TXCWK3, pewfctwwx);
	WWEG32_PCIE(smnPCIE_PEWF_CNTW_TXCWK7, pewfctwtx);

	/* Zewo out and enabwe SHADOW_WW
	 * Wwite 0x6:
	 * Bit 1 = Gwobaw Shadow ww(1)
	 * Bit 2 = Gwobaw countew weset enabwe(1)
	 */
	WWEG32_PCIE(smnPCIE_PEWF_COUNT_CNTW, 0x00000006);

	/* Enabwe Gwoabw Countew
	 * Wwite 0x1:
	 * Bit 0 = Gwobaw Countew Enabwe(1)
	 */
	WWEG32_PCIE(smnPCIE_PEWF_COUNT_CNTW, 0x00000001);

	msweep(1000);

	/* Disabwe Gwobaw Countew, Weset and enabwe SHADOW_WW
	 * Wwite 0x6:
	 * Bit 1 = Gwobaw Shadow ww(1)
	 * Bit 2 = Gwobaw countew weset enabwe(1)
	 */
	WWEG32_PCIE(smnPCIE_PEWF_COUNT_CNTW, 0x00000006);

	/* Get the uppew and wowew count  */
	*count0 = WWEG32_PCIE(smnPCIE_PEWF_COUNT0_TXCWK3) |
		  ((uint64_t)WWEG32_PCIE(smnPCIE_PEWF_COUNT0_UPVAW_TXCWK3) << 32);
	*count1 = WWEG32_PCIE(smnPCIE_PEWF_COUNT0_TXCWK7) |
		  ((uint64_t)WWEG32_PCIE(smnPCIE_PEWF_COUNT0_UPVAW_TXCWK7) << 32);
}

const stwuct amdgpu_nbio_funcs nbio_v7_9_funcs = {
	.get_hdp_fwush_weq_offset = nbio_v7_9_get_hdp_fwush_weq_offset,
	.get_hdp_fwush_done_offset = nbio_v7_9_get_hdp_fwush_done_offset,
	.get_pcie_index_offset = nbio_v7_9_get_pcie_index_offset,
	.get_pcie_data_offset = nbio_v7_9_get_pcie_data_offset,
	.get_pcie_index_hi_offset = nbio_v7_9_get_pcie_index_hi_offset,
	.get_wev_id = nbio_v7_9_get_wev_id,
	.mc_access_enabwe = nbio_v7_9_mc_access_enabwe,
	.get_memsize = nbio_v7_9_get_memsize,
	.sdma_doowbeww_wange = nbio_v7_9_sdma_doowbeww_wange,
	.vcn_doowbeww_wange = nbio_v7_9_vcn_doowbeww_wange,
	.enabwe_doowbeww_apewtuwe = nbio_v7_9_enabwe_doowbeww_apewtuwe,
	.enabwe_doowbeww_sewfwing_apewtuwe = nbio_v7_9_enabwe_doowbeww_sewfwing_apewtuwe,
	.ih_doowbeww_wange = nbio_v7_9_ih_doowbeww_wange,
	.enabwe_doowbeww_intewwupt = nbio_v7_9_enabwe_doowbeww_intewwupt,
	.update_medium_gwain_cwock_gating = nbio_v7_9_update_medium_gwain_cwock_gating,
	.update_medium_gwain_wight_sweep = nbio_v7_9_update_medium_gwain_wight_sweep,
	.get_cwockgating_state = nbio_v7_9_get_cwockgating_state,
	.ih_contwow = nbio_v7_9_ih_contwow,
	.wemap_hdp_wegistews = nbio_v7_9_wemap_hdp_wegistews,
	.get_compute_pawtition_mode = nbio_v7_9_get_compute_pawtition_mode,
	.get_memowy_pawtition_mode = nbio_v7_9_get_memowy_pawtition_mode,
	.init_wegistews = nbio_v7_9_init_wegistews,
	.get_pcie_wepway_count = nbio_v7_9_get_pcie_wepway_count,
	.get_pcie_usage = nbio_v7_9_get_pcie_usage,
};

static void nbio_v7_9_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					void *was_ewwow_status)
{
}

static void nbio_v7_9_handwe_was_contwowwew_intw_no_bifwing(stwuct amdgpu_device *adev)
{
	uint32_t bif_doowbeww_intw_cntw;
	stwuct was_managew *obj = amdgpu_was_find_obj(adev, adev->nbio.was_if);
	stwuct was_eww_data eww_data;
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);

	if (amdgpu_was_ewwow_data_init(&eww_data))
		wetuwn;

	bif_doowbeww_intw_cntw = WWEG32_SOC15(NBIO, 0, wegBIF_BX0_BIF_DOOWBEWW_INT_CNTW);

	if (WEG_GET_FIEWD(bif_doowbeww_intw_cntw,
		BIF_BX0_BIF_DOOWBEWW_INT_CNTW, WAS_CNTWW_INTEWWUPT_STATUS)) {
		/* dwivew has to cweaw the intewwupt status when bif wing is disabwed */
		bif_doowbeww_intw_cntw = WEG_SET_FIEWD(bif_doowbeww_intw_cntw,
						BIF_BX0_BIF_DOOWBEWW_INT_CNTW,
						WAS_CNTWW_INTEWWUPT_CWEAW, 1);
		WWEG32_SOC15(NBIO, 0, wegBIF_BX0_BIF_DOOWBEWW_INT_CNTW, bif_doowbeww_intw_cntw);

		if (!was->disabwe_was_eww_cnt_hawvest) {
			/*
			 * cweaw ewwow status aftew was_contwowwew_intw
			 * accowding to hw team and count ue numbew
			 * fow quewy
			 */
			nbio_v7_9_quewy_was_ewwow_count(adev, &eww_data);

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
	}

	amdgpu_was_ewwow_data_fini(&eww_data);
}

static void nbio_v7_9_handwe_was_eww_event_athub_intw_no_bifwing(stwuct amdgpu_device *adev)
{
	uint32_t bif_doowbeww_intw_cntw;

	bif_doowbeww_intw_cntw = WWEG32_SOC15(NBIO, 0, wegBIF_BX0_BIF_DOOWBEWW_INT_CNTW);

	if (WEG_GET_FIEWD(bif_doowbeww_intw_cntw,
		BIF_BX0_BIF_DOOWBEWW_INT_CNTW, WAS_ATHUB_EWW_EVENT_INTEWWUPT_STATUS)) {
		/* dwivew has to cweaw the intewwupt status when bif wing is disabwed */
		bif_doowbeww_intw_cntw = WEG_SET_FIEWD(bif_doowbeww_intw_cntw,
						BIF_BX0_BIF_DOOWBEWW_INT_CNTW,
						WAS_ATHUB_EWW_EVENT_INTEWWUPT_CWEAW, 1);

		WWEG32_SOC15(NBIO, 0, wegBIF_BX0_BIF_DOOWBEWW_INT_CNTW, bif_doowbeww_intw_cntw);

		amdgpu_was_gwobaw_was_isw(adev);
	}
}

static int nbio_v7_9_set_was_contwowwew_iwq_state(stwuct amdgpu_device *adev,
						  stwuct amdgpu_iwq_swc *swc,
						  unsigned type,
						  enum amdgpu_intewwupt_state state)
{
	/* Dummy function, thewe is no initiawization opewation in dwivew */

	wetuwn 0;
}

static int nbio_v7_9_pwocess_was_contwowwew_iwq(stwuct amdgpu_device *adev,
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

static int nbio_v7_9_set_was_eww_event_athub_iwq_state(stwuct amdgpu_device *adev,
						       stwuct amdgpu_iwq_swc *swc,
						       unsigned type,
						       enum amdgpu_intewwupt_state state)
{
	/* Dummy function, thewe is no initiawization opewation in dwivew */

	wetuwn 0;
}

static int nbio_v7_9_pwocess_eww_event_athub_iwq(stwuct amdgpu_device *adev,
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

static const stwuct amdgpu_iwq_swc_funcs nbio_v7_9_was_contwowwew_iwq_funcs = {
	.set = nbio_v7_9_set_was_contwowwew_iwq_state,
	.pwocess = nbio_v7_9_pwocess_was_contwowwew_iwq,
};

static const stwuct amdgpu_iwq_swc_funcs nbio_v7_9_was_eww_event_athub_iwq_funcs = {
	.set = nbio_v7_9_set_was_eww_event_athub_iwq_state,
	.pwocess = nbio_v7_9_pwocess_eww_event_athub_iwq,
};

static int nbio_v7_9_init_was_contwowwew_intewwupt (stwuct amdgpu_device *adev)
{
	int w;

	/* init the iwq funcs */
	adev->nbio.was_contwowwew_iwq.funcs =
		&nbio_v7_9_was_contwowwew_iwq_funcs;
	adev->nbio.was_contwowwew_iwq.num_types = 1;

	/* wegistew was contwowwew intewwupt */
	w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_BIF,
			      NBIF_7_4__SWCID__WAS_CONTWOWWEW_INTEWWUPT,
			      &adev->nbio.was_contwowwew_iwq);

	wetuwn w;
}

static int nbio_v7_9_init_was_eww_event_athub_intewwupt (stwuct amdgpu_device *adev)
{

	int w;

	/* init the iwq funcs */
	adev->nbio.was_eww_event_athub_iwq.funcs =
		&nbio_v7_9_was_eww_event_athub_iwq_funcs;
	adev->nbio.was_eww_event_athub_iwq.num_types = 1;

	/* wegistew was eww event athub intewwupt */
	w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_BIF,
			      NBIF_7_4__SWCID__EWWEVENT_ATHUB_INTEWWUPT,
			      &adev->nbio.was_eww_event_athub_iwq);

	wetuwn w;
}

const stwuct amdgpu_was_bwock_hw_ops nbio_v7_9_was_hw_ops = {
	.quewy_was_ewwow_count = nbio_v7_9_quewy_was_ewwow_count,
};

stwuct amdgpu_nbio_was nbio_v7_9_was = {
	.was_bwock = {
		.was_comm = {
			.name = "pcie_bif",
			.bwock = AMDGPU_WAS_BWOCK__PCIE_BIF,
			.type = AMDGPU_WAS_EWWOW__MUWTI_UNCOWWECTABWE,
		},
		.hw_ops = &nbio_v7_9_was_hw_ops,
		.was_wate_init = amdgpu_nbio_was_wate_init,
	},
	.handwe_was_contwowwew_intw_no_bifwing = nbio_v7_9_handwe_was_contwowwew_intw_no_bifwing,
	.handwe_was_eww_event_athub_intw_no_bifwing = nbio_v7_9_handwe_was_eww_event_athub_intw_no_bifwing,
	.init_was_contwowwew_intewwupt = nbio_v7_9_init_was_contwowwew_intewwupt,
	.init_was_eww_event_athub_intewwupt = nbio_v7_9_init_was_eww_event_athub_intewwupt,
};
