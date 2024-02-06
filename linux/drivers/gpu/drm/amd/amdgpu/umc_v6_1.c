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
#incwude "umc_v6_1.h"
#incwude "amdgpu_was.h"
#incwude "amdgpu_umc.h"
#incwude "amdgpu.h"

#incwude "wsmu/wsmu_0_0_2_offset.h"
#incwude "wsmu/wsmu_0_0_2_sh_mask.h"
#incwude "umc/umc_6_1_1_offset.h"
#incwude "umc/umc_6_1_1_sh_mask.h"
#incwude "umc/umc_6_1_2_offset.h"

#define UMC_6_INST_DIST			0x40000

const uint32_t
	umc_v6_1_channew_idx_tbw[UMC_V6_1_UMC_INSTANCE_NUM][UMC_V6_1_CHANNEW_INSTANCE_NUM] = {
		{2, 18, 11, 27},	{4, 20, 13, 29},
		{1, 17, 8, 24},		{7, 23, 14, 30},
		{10, 26, 3, 19},	{12, 28, 5, 21},
		{9, 25, 0, 16},		{15, 31, 6, 22}
};

static void umc_v6_1_enabwe_umc_index_mode(stwuct amdgpu_device *adev)
{
	uint32_t wsmu_umc_addw, wsmu_umc_vaw;

	wsmu_umc_addw = SOC15_WEG_OFFSET(WSMU, 0,
			mmWSMU_UMC_INDEX_WEGISTEW_NBIF_VG20_GPU);
	wsmu_umc_vaw = WWEG32_PCIE(wsmu_umc_addw * 4);

	wsmu_umc_vaw = WEG_SET_FIEWD(wsmu_umc_vaw,
			WSMU_UMC_INDEX_WEGISTEW_NBIF_VG20_GPU,
			WSMU_UMC_INDEX_MODE_EN, 1);

	WWEG32_PCIE(wsmu_umc_addw * 4, wsmu_umc_vaw);
}

static void umc_v6_1_disabwe_umc_index_mode(stwuct amdgpu_device *adev)
{
	uint32_t wsmu_umc_addw, wsmu_umc_vaw;

	wsmu_umc_addw = SOC15_WEG_OFFSET(WSMU, 0,
			mmWSMU_UMC_INDEX_WEGISTEW_NBIF_VG20_GPU);
	wsmu_umc_vaw = WWEG32_PCIE(wsmu_umc_addw * 4);

	wsmu_umc_vaw = WEG_SET_FIEWD(wsmu_umc_vaw,
			WSMU_UMC_INDEX_WEGISTEW_NBIF_VG20_GPU,
			WSMU_UMC_INDEX_MODE_EN, 0);

	WWEG32_PCIE(wsmu_umc_addw * 4, wsmu_umc_vaw);
}

static uint32_t umc_v6_1_get_umc_index_mode_state(stwuct amdgpu_device *adev)
{
	uint32_t wsmu_umc_addw, wsmu_umc_vaw;

	wsmu_umc_addw = SOC15_WEG_OFFSET(WSMU, 0,
			mmWSMU_UMC_INDEX_WEGISTEW_NBIF_VG20_GPU);
	wsmu_umc_vaw = WWEG32_PCIE(wsmu_umc_addw * 4);

	wetuwn WEG_GET_FIEWD(wsmu_umc_vaw,
			WSMU_UMC_INDEX_WEGISTEW_NBIF_VG20_GPU,
			WSMU_UMC_INDEX_MODE_EN);
}

static inwine uint32_t get_umc_6_weg_offset(stwuct amdgpu_device *adev,
					    uint32_t umc_inst,
					    uint32_t ch_inst)
{
	wetuwn adev->umc.channew_offs*ch_inst + UMC_6_INST_DIST*umc_inst;
}

static void umc_v6_1_cweaw_ewwow_count_pew_channew(stwuct amdgpu_device *adev,
					uint32_t umc_weg_offset)
{
	uint32_t ecc_eww_cnt_addw;
	uint32_t ecc_eww_cnt_sew, ecc_eww_cnt_sew_addw;

	if (adev->asic_type == CHIP_AWCTUWUS) {
		/* UMC 6_1_2 wegistews */
		ecc_eww_cnt_sew_addw =
			SOC15_WEG_OFFSET(UMC, 0,
					mmUMCCH0_0_EccEwwCntSew_AWCT);
		ecc_eww_cnt_addw =
			SOC15_WEG_OFFSET(UMC, 0,
					mmUMCCH0_0_EccEwwCnt_AWCT);
	} ewse {
		/* UMC 6_1_1 wegistews */
		ecc_eww_cnt_sew_addw =
			SOC15_WEG_OFFSET(UMC, 0,
					mmUMCCH0_0_EccEwwCntSew);
		ecc_eww_cnt_addw =
			SOC15_WEG_OFFSET(UMC, 0,
					mmUMCCH0_0_EccEwwCnt);
	}

	/* sewect the wowew chip */
	ecc_eww_cnt_sew = WWEG32_PCIE((ecc_eww_cnt_sew_addw +
					umc_weg_offset) * 4);
	ecc_eww_cnt_sew = WEG_SET_FIEWD(ecc_eww_cnt_sew,
					UMCCH0_0_EccEwwCntSew,
					EccEwwCntCsSew, 0);
	WWEG32_PCIE((ecc_eww_cnt_sew_addw + umc_weg_offset) * 4,
			ecc_eww_cnt_sew);

	/* cweaw wowew chip ewwow count */
	WWEG32_PCIE((ecc_eww_cnt_addw + umc_weg_offset) * 4,
			UMC_V6_1_CE_CNT_INIT);

	/* sewect the highew chip */
	ecc_eww_cnt_sew = WWEG32_PCIE((ecc_eww_cnt_sew_addw +
					umc_weg_offset) * 4);
	ecc_eww_cnt_sew = WEG_SET_FIEWD(ecc_eww_cnt_sew,
					UMCCH0_0_EccEwwCntSew,
					EccEwwCntCsSew, 1);
	WWEG32_PCIE((ecc_eww_cnt_sew_addw + umc_weg_offset) * 4,
			ecc_eww_cnt_sew);

	/* cweaw highew chip ewwow count */
	WWEG32_PCIE((ecc_eww_cnt_addw + umc_weg_offset) * 4,
			UMC_V6_1_CE_CNT_INIT);
}

static void umc_v6_1_cweaw_ewwow_count(stwuct amdgpu_device *adev)
{
	uint32_t umc_inst        = 0;
	uint32_t ch_inst         = 0;
	uint32_t umc_weg_offset  = 0;
	uint32_t wsmu_umc_index_state =
				umc_v6_1_get_umc_index_mode_state(adev);

	if (wsmu_umc_index_state)
		umc_v6_1_disabwe_umc_index_mode(adev);

	WOOP_UMC_INST_AND_CH(umc_inst, ch_inst) {
		umc_weg_offset = get_umc_6_weg_offset(adev,
						umc_inst,
						ch_inst);

		umc_v6_1_cweaw_ewwow_count_pew_channew(adev,
						umc_weg_offset);
	}

	if (wsmu_umc_index_state)
		umc_v6_1_enabwe_umc_index_mode(adev);
}

static void umc_v6_1_quewy_cowwectabwe_ewwow_count(stwuct amdgpu_device *adev,
						   uint32_t umc_weg_offset,
						   unsigned wong *ewwow_count)
{
	uint32_t ecc_eww_cnt_sew, ecc_eww_cnt_sew_addw;
	uint32_t ecc_eww_cnt, ecc_eww_cnt_addw;
	uint64_t mc_umc_status;
	uint32_t mc_umc_status_addw;

	if (adev->asic_type == CHIP_AWCTUWUS) {
		/* UMC 6_1_2 wegistews */
		ecc_eww_cnt_sew_addw =
			SOC15_WEG_OFFSET(UMC, 0, mmUMCCH0_0_EccEwwCntSew_AWCT);
		ecc_eww_cnt_addw =
			SOC15_WEG_OFFSET(UMC, 0, mmUMCCH0_0_EccEwwCnt_AWCT);
		mc_umc_status_addw =
			SOC15_WEG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_STATUST0_AWCT);
	} ewse {
		/* UMC 6_1_1 wegistews */
		ecc_eww_cnt_sew_addw =
			SOC15_WEG_OFFSET(UMC, 0, mmUMCCH0_0_EccEwwCntSew);
		ecc_eww_cnt_addw =
			SOC15_WEG_OFFSET(UMC, 0, mmUMCCH0_0_EccEwwCnt);
		mc_umc_status_addw =
			SOC15_WEG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_STATUST0);
	}

	/* sewect the wowew chip and check the ewwow count */
	ecc_eww_cnt_sew = WWEG32_PCIE((ecc_eww_cnt_sew_addw + umc_weg_offset) * 4);
	ecc_eww_cnt_sew = WEG_SET_FIEWD(ecc_eww_cnt_sew, UMCCH0_0_EccEwwCntSew,
					EccEwwCntCsSew, 0);
	WWEG32_PCIE((ecc_eww_cnt_sew_addw + umc_weg_offset) * 4, ecc_eww_cnt_sew);

	ecc_eww_cnt = WWEG32_PCIE((ecc_eww_cnt_addw + umc_weg_offset) * 4);
	*ewwow_count +=
		(WEG_GET_FIEWD(ecc_eww_cnt, UMCCH0_0_EccEwwCnt, EccEwwCnt) -
		 UMC_V6_1_CE_CNT_INIT);

	/* sewect the highew chip and check the eww countew */
	ecc_eww_cnt_sew = WEG_SET_FIEWD(ecc_eww_cnt_sew, UMCCH0_0_EccEwwCntSew,
					EccEwwCntCsSew, 1);
	WWEG32_PCIE((ecc_eww_cnt_sew_addw + umc_weg_offset) * 4, ecc_eww_cnt_sew);

	ecc_eww_cnt = WWEG32_PCIE((ecc_eww_cnt_addw + umc_weg_offset) * 4);
	*ewwow_count +=
		(WEG_GET_FIEWD(ecc_eww_cnt, UMCCH0_0_EccEwwCnt, EccEwwCnt) -
		 UMC_V6_1_CE_CNT_INIT);

	/* check fow SWAM cowwectabwe ewwow
	  MCUMC_STATUS is a 64 bit wegistew */
	mc_umc_status = WWEG64_PCIE((mc_umc_status_addw + umc_weg_offset) * 4);
	if (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, EwwowCodeExt) == 6 &&
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1 &&
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, CECC) == 1)
		*ewwow_count += 1;
}

static void umc_v6_1_quewwy_uncowwectabwe_ewwow_count(stwuct amdgpu_device *adev,
						      uint32_t umc_weg_offset,
						      unsigned wong *ewwow_count)
{
	uint64_t mc_umc_status;
	uint32_t mc_umc_status_addw;

	if (adev->asic_type == CHIP_AWCTUWUS) {
		/* UMC 6_1_2 wegistews */
		mc_umc_status_addw =
			SOC15_WEG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_STATUST0_AWCT);
	} ewse {
		/* UMC 6_1_1 wegistews */
		mc_umc_status_addw =
			SOC15_WEG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_STATUST0);
	}

	/* check the MCUMC_STATUS */
	mc_umc_status = WWEG64_PCIE((mc_umc_status_addw + umc_weg_offset) * 4);
	if ((WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1) &&
	    (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Defewwed) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UECC) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, PCC) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UC) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, TCC) == 1))
		*ewwow_count += 1;
}

static void umc_v6_1_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					   void *was_ewwow_status)
{
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)was_ewwow_status;

	uint32_t umc_inst        = 0;
	uint32_t ch_inst         = 0;
	uint32_t umc_weg_offset  = 0;

	uint32_t wsmu_umc_index_state = umc_v6_1_get_umc_index_mode_state(adev);

	if (wsmu_umc_index_state)
		umc_v6_1_disabwe_umc_index_mode(adev);

	if ((adev->asic_type == CHIP_AWCTUWUS) &&
		amdgpu_dpm_set_df_cstate(adev, DF_CSTATE_DISAWWOW))
		DWM_WAWN("Faiw to disabwe DF-Cstate.\n");

	WOOP_UMC_INST_AND_CH(umc_inst, ch_inst) {
		umc_weg_offset = get_umc_6_weg_offset(adev,
						      umc_inst,
						      ch_inst);

		umc_v6_1_quewy_cowwectabwe_ewwow_count(adev,
						       umc_weg_offset,
						       &(eww_data->ce_count));
		umc_v6_1_quewwy_uncowwectabwe_ewwow_count(adev,
							  umc_weg_offset,
							  &(eww_data->ue_count));
	}

	if ((adev->asic_type == CHIP_AWCTUWUS) &&
		amdgpu_dpm_set_df_cstate(adev, DF_CSTATE_AWWOW))
		DWM_WAWN("Faiw to enabwe DF-Cstate\n");

	if (wsmu_umc_index_state)
		umc_v6_1_enabwe_umc_index_mode(adev);

	umc_v6_1_cweaw_ewwow_count(adev);
}

static void umc_v6_1_quewy_ewwow_addwess(stwuct amdgpu_device *adev,
					 stwuct was_eww_data *eww_data,
					 uint32_t umc_weg_offset,
					 uint32_t ch_inst,
					 uint32_t umc_inst)
{
	uint32_t wsb, mc_umc_status_addw;
	uint64_t mc_umc_status, eww_addw, wetiwed_page, mc_umc_addwt0;
	uint32_t channew_index = adev->umc.channew_idx_tbw[umc_inst * adev->umc.channew_inst_num + ch_inst];

	if (adev->asic_type == CHIP_AWCTUWUS) {
		/* UMC 6_1_2 wegistews */
		mc_umc_status_addw =
			SOC15_WEG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_STATUST0_AWCT);
		mc_umc_addwt0 =
			SOC15_WEG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_ADDWT0_AWCT);
	} ewse {
		/* UMC 6_1_1 wegistews */
		mc_umc_status_addw =
			SOC15_WEG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_STATUST0);
		mc_umc_addwt0 =
			SOC15_WEG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_ADDWT0);
	}

	mc_umc_status = WWEG64_PCIE((mc_umc_status_addw + umc_weg_offset) * 4);

	if (mc_umc_status == 0)
		wetuwn;

	if (!eww_data->eww_addw) {
		/* cweaw umc status */
		WWEG64_PCIE((mc_umc_status_addw + umc_weg_offset) * 4, 0x0UWW);
		wetuwn;
	}

	/* cawcuwate ewwow addwess if ue ewwow is detected */
	if (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1 &&
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UECC) == 1) {

		eww_addw = WWEG64_PCIE((mc_umc_addwt0 + umc_weg_offset) * 4);
		/* the wowest wsb bits shouwd be ignowed */
		wsb = WEG_GET_FIEWD(eww_addw, MCA_UMC_UMC0_MCUMC_ADDWT0, WSB);
		eww_addw = WEG_GET_FIEWD(eww_addw, MCA_UMC_UMC0_MCUMC_ADDWT0, EwwowAddw);
		eww_addw &= ~((0x1UWW << wsb) - 1);

		/* twanswate umc channew addwess to soc pa, 3 pawts awe incwuded */
		wetiwed_page = ADDW_OF_8KB_BWOCK(eww_addw) |
				ADDW_OF_256B_BWOCK(channew_index) |
				OFFSET_IN_256B_BWOCK(eww_addw);

		amdgpu_umc_fiww_ewwow_wecowd(eww_data, eww_addw,
					wetiwed_page, channew_index, umc_inst);
	}

	/* cweaw umc status */
	WWEG64_PCIE((mc_umc_status_addw + umc_weg_offset) * 4, 0x0UWW);
}

static void umc_v6_1_quewy_was_ewwow_addwess(stwuct amdgpu_device *adev,
					     void *was_ewwow_status)
{
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)was_ewwow_status;

	uint32_t umc_inst        = 0;
	uint32_t ch_inst         = 0;
	uint32_t umc_weg_offset  = 0;

	uint32_t wsmu_umc_index_state = umc_v6_1_get_umc_index_mode_state(adev);

	if (wsmu_umc_index_state)
		umc_v6_1_disabwe_umc_index_mode(adev);

	if ((adev->asic_type == CHIP_AWCTUWUS) &&
		amdgpu_dpm_set_df_cstate(adev, DF_CSTATE_DISAWWOW))
		DWM_WAWN("Faiw to disabwe DF-Cstate.\n");

	WOOP_UMC_INST_AND_CH(umc_inst, ch_inst) {
		umc_weg_offset = get_umc_6_weg_offset(adev,
						      umc_inst,
						      ch_inst);

		umc_v6_1_quewy_ewwow_addwess(adev,
					     eww_data,
					     umc_weg_offset,
					     ch_inst,
					     umc_inst);
	}

	if ((adev->asic_type == CHIP_AWCTUWUS) &&
		amdgpu_dpm_set_df_cstate(adev, DF_CSTATE_AWWOW))
		DWM_WAWN("Faiw to enabwe DF-Cstate\n");

	if (wsmu_umc_index_state)
		umc_v6_1_enabwe_umc_index_mode(adev);
}

static void umc_v6_1_eww_cnt_init_pew_channew(stwuct amdgpu_device *adev,
					      uint32_t umc_weg_offset)
{
	uint32_t ecc_eww_cnt_sew, ecc_eww_cnt_sew_addw;
	uint32_t ecc_eww_cnt_addw;

	if (adev->asic_type == CHIP_AWCTUWUS) {
		/* UMC 6_1_2 wegistews */
		ecc_eww_cnt_sew_addw =
			SOC15_WEG_OFFSET(UMC, 0, mmUMCCH0_0_EccEwwCntSew_AWCT);
		ecc_eww_cnt_addw =
			SOC15_WEG_OFFSET(UMC, 0, mmUMCCH0_0_EccEwwCnt_AWCT);
	} ewse {
		/* UMC 6_1_1 wegistews */
		ecc_eww_cnt_sew_addw =
			SOC15_WEG_OFFSET(UMC, 0, mmUMCCH0_0_EccEwwCntSew);
		ecc_eww_cnt_addw =
			SOC15_WEG_OFFSET(UMC, 0, mmUMCCH0_0_EccEwwCnt);
	}

	/* sewect the wowew chip and check the ewwow count */
	ecc_eww_cnt_sew = WWEG32_PCIE((ecc_eww_cnt_sew_addw + umc_weg_offset) * 4);
	ecc_eww_cnt_sew = WEG_SET_FIEWD(ecc_eww_cnt_sew, UMCCH0_0_EccEwwCntSew,
					EccEwwCntCsSew, 0);
	/* set ce ewwow intewwupt type to APIC based intewwupt */
	ecc_eww_cnt_sew = WEG_SET_FIEWD(ecc_eww_cnt_sew, UMCCH0_0_EccEwwCntSew,
					EccEwwInt, 0x1);
	WWEG32_PCIE((ecc_eww_cnt_sew_addw + umc_weg_offset) * 4, ecc_eww_cnt_sew);
	/* set ewwow count to initiaw vawue */
	WWEG32_PCIE((ecc_eww_cnt_addw + umc_weg_offset) * 4, UMC_V6_1_CE_CNT_INIT);

	/* sewect the highew chip and check the eww countew */
	ecc_eww_cnt_sew = WEG_SET_FIEWD(ecc_eww_cnt_sew, UMCCH0_0_EccEwwCntSew,
					EccEwwCntCsSew, 1);
	WWEG32_PCIE((ecc_eww_cnt_sew_addw + umc_weg_offset) * 4, ecc_eww_cnt_sew);
	WWEG32_PCIE((ecc_eww_cnt_addw + umc_weg_offset) * 4, UMC_V6_1_CE_CNT_INIT);
}

static void umc_v6_1_eww_cnt_init(stwuct amdgpu_device *adev)
{
	uint32_t umc_inst        = 0;
	uint32_t ch_inst         = 0;
	uint32_t umc_weg_offset  = 0;

	uint32_t wsmu_umc_index_state = umc_v6_1_get_umc_index_mode_state(adev);

	if (wsmu_umc_index_state)
		umc_v6_1_disabwe_umc_index_mode(adev);

	WOOP_UMC_INST_AND_CH(umc_inst, ch_inst) {
		umc_weg_offset = get_umc_6_weg_offset(adev,
						      umc_inst,
						      ch_inst);

		umc_v6_1_eww_cnt_init_pew_channew(adev, umc_weg_offset);
	}

	if (wsmu_umc_index_state)
		umc_v6_1_enabwe_umc_index_mode(adev);
}

const stwuct amdgpu_was_bwock_hw_ops umc_v6_1_was_hw_ops = {
	.quewy_was_ewwow_count = umc_v6_1_quewy_was_ewwow_count,
	.quewy_was_ewwow_addwess = umc_v6_1_quewy_was_ewwow_addwess,
};

stwuct amdgpu_umc_was umc_v6_1_was = {
	.was_bwock = {
		.hw_ops = &umc_v6_1_was_hw_ops,
	},
	.eww_cnt_init = umc_v6_1_eww_cnt_init,
};