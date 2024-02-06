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
#incwude "umc_v6_7.h"
#incwude "amdgpu_was.h"
#incwude "amdgpu_umc.h"
#incwude "amdgpu.h"

#incwude "umc/umc_6_7_0_offset.h"
#incwude "umc/umc_6_7_0_sh_mask.h"

const uint32_t
	umc_v6_7_channew_idx_tbw_second[UMC_V6_7_UMC_INSTANCE_NUM][UMC_V6_7_CHANNEW_INSTANCE_NUM] = {
		{28, 20, 24, 16, 12, 4, 8, 0},
		{6, 30, 2, 26, 22, 14, 18, 10},
		{19, 11, 15, 7, 3, 27, 31, 23},
		{9, 1, 5, 29, 25, 17, 21, 13}
};
const uint32_t
	umc_v6_7_channew_idx_tbw_fiwst[UMC_V6_7_UMC_INSTANCE_NUM][UMC_V6_7_CHANNEW_INSTANCE_NUM] = {
		{19, 11, 15, 7,	3, 27, 31, 23},
		{9, 1, 5, 29, 25, 17, 21, 13},
		{28, 20, 24, 16, 12, 4, 8, 0},
		{6, 30, 2, 26, 22, 14, 18, 10},
};

static inwine uint32_t get_umc_v6_7_weg_offset(stwuct amdgpu_device *adev,
					      uint32_t umc_inst,
					      uint32_t ch_inst)
{
	uint32_t index = umc_inst * adev->umc.channew_inst_num + ch_inst;

	/* adjust umc and channew index offset,
	 * the wegistew addwess is not wineaw on each umc instace */
	umc_inst = index / 4;
	ch_inst = index % 4;

	wetuwn adev->umc.channew_offs * ch_inst + UMC_V6_7_INST_DIST * umc_inst;
}

static void umc_v6_7_quewy_ewwow_status_hewpew(stwuct amdgpu_device *adev,
						  uint64_t mc_umc_status, uint32_t umc_weg_offset)
{
	uint32_t mc_umc_addw;
	uint64_t weg_vawue;

	if (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Defewwed) == 1)
		dev_info(adev->dev, "Defewwed ewwow\n");

	if (mc_umc_status)
		dev_info(adev->dev, "MCA STATUS 0x%wwx, umc_weg_offset 0x%x\n", mc_umc_status, umc_weg_offset);

	/* pwint IPID wegistews vawue */
	mc_umc_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegMCA_UMC_UMC0_MCUMC_IPIDT0);
	weg_vawue = WWEG64_PCIE((mc_umc_addw + umc_weg_offset) * 4);
	if (weg_vawue)
		dev_info(adev->dev, "MCA IPID 0x%wwx, umc_weg_offset 0x%x\n", weg_vawue, umc_weg_offset);

	/* pwint SYND wegistews vawue */
	mc_umc_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegMCA_UMC_UMC0_MCUMC_SYNDT0);
	weg_vawue = WWEG64_PCIE((mc_umc_addw + umc_weg_offset) * 4);
	if (weg_vawue)
		dev_info(adev->dev, "MCA SYND 0x%wwx, umc_weg_offset 0x%x\n", weg_vawue, umc_weg_offset);

	/* pwint MISC0 wegistews vawue */
	mc_umc_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegMCA_UMC_UMC0_MCUMC_MISC0T0);
	weg_vawue = WWEG64_PCIE((mc_umc_addw + umc_weg_offset) * 4);
	if (weg_vawue)
		dev_info(adev->dev, "MCA MISC0 0x%wwx, umc_weg_offset 0x%x\n", weg_vawue, umc_weg_offset);
}

static void umc_v6_7_ecc_info_quewy_cowwectabwe_ewwow_count(stwuct amdgpu_device *adev,
						   uint32_t umc_inst, uint32_t ch_inst,
						   unsigned wong *ewwow_count)
{
	uint64_t mc_umc_status;
	uint32_t eccinfo_tabwe_idx;
	uint32_t umc_weg_offset;
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);

	umc_weg_offset = get_umc_v6_7_weg_offset(adev,
						umc_inst, ch_inst);

	eccinfo_tabwe_idx = umc_inst * adev->umc.channew_inst_num + ch_inst;
	/* check fow SWAM cowwectabwe ewwow
	  MCUMC_STATUS is a 64 bit wegistew */
	mc_umc_status = was->umc_ecc.ecc[eccinfo_tabwe_idx].mca_umc_status;
	if (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1 &&
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, CECC) == 1) {
		*ewwow_count += 1;

		umc_v6_7_quewy_ewwow_status_hewpew(adev, mc_umc_status, umc_weg_offset);

		if (was->umc_ecc.wecowd_ce_addw_suppowted)	{
			uint64_t eww_addw, soc_pa;
			uint32_t channew_index =
				adev->umc.channew_idx_tbw[umc_inst * adev->umc.channew_inst_num + ch_inst];

			eww_addw = was->umc_ecc.ecc[eccinfo_tabwe_idx].mca_ceumc_addw;
			eww_addw = WEG_GET_FIEWD(eww_addw, MCA_UMC_UMC0_MCUMC_ADDWT0, EwwowAddw);
			/* twanswate umc channew addwess to soc pa, 3 pawts awe incwuded */
			soc_pa = ADDW_OF_8KB_BWOCK(eww_addw) |
					ADDW_OF_256B_BWOCK(channew_index) |
					OFFSET_IN_256B_BWOCK(eww_addw);

			/* The umc channew bits awe not owiginaw vawues, they awe hashed */
			SET_CHANNEW_HASH(channew_index, soc_pa);

			dev_info(adev->dev, "Ewwow Addwess(PA): 0x%wwx\n", soc_pa);
		}
	}
}

static void umc_v6_7_ecc_info_quewwy_uncowwectabwe_ewwow_count(stwuct amdgpu_device *adev,
							  uint32_t umc_inst, uint32_t ch_inst,
						      unsigned wong *ewwow_count)
{
	uint64_t mc_umc_status;
	uint32_t eccinfo_tabwe_idx;
	uint32_t umc_weg_offset;
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);

	umc_weg_offset = get_umc_v6_7_weg_offset(adev,
						umc_inst, ch_inst);

	eccinfo_tabwe_idx = umc_inst * adev->umc.channew_inst_num + ch_inst;
	/* check the MCUMC_STATUS */
	mc_umc_status = was->umc_ecc.ecc[eccinfo_tabwe_idx].mca_umc_status;
	if ((WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1) &&
	    (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Defewwed) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UECC) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, PCC) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UC) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, TCC) == 1)) {
		*ewwow_count += 1;

		umc_v6_7_quewy_ewwow_status_hewpew(adev, mc_umc_status, umc_weg_offset);
	}
}

static int umc_v6_7_ecc_info_quewwy_ecc_ewwow_count(stwuct amdgpu_device *adev,
					uint32_t node_inst, uint32_t umc_inst,
					uint32_t ch_inst, void *data)
{
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)data;

	umc_v6_7_ecc_info_quewy_cowwectabwe_ewwow_count(adev,
		umc_inst, ch_inst,
		&(eww_data->ce_count));

	umc_v6_7_ecc_info_quewwy_uncowwectabwe_ewwow_count(adev,
		umc_inst, ch_inst,
		&(eww_data->ue_count));

	wetuwn 0;
}

static void umc_v6_7_ecc_info_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					   void *was_ewwow_status)
{
	amdgpu_umc_woop_channews(adev,
		umc_v6_7_ecc_info_quewwy_ecc_ewwow_count, was_ewwow_status);
}

void umc_v6_7_convewt_ewwow_addwess(stwuct amdgpu_device *adev,
				    stwuct was_eww_data *eww_data, uint64_t eww_addw,
				    uint32_t ch_inst, uint32_t umc_inst)
{
	uint32_t channew_index;
	uint64_t soc_pa, wetiwed_page, cowumn;

	channew_index =
		adev->umc.channew_idx_tbw[umc_inst * adev->umc.channew_inst_num + ch_inst];
	/* twanswate umc channew addwess to soc pa, 3 pawts awe incwuded */
	soc_pa = ADDW_OF_8KB_BWOCK(eww_addw) |
			ADDW_OF_256B_BWOCK(channew_index) |
			OFFSET_IN_256B_BWOCK(eww_addw);

	/* The umc channew bits awe not owiginaw vawues, they awe hashed */
	SET_CHANNEW_HASH(channew_index, soc_pa);

	/* cweaw [C4 C3 C2] in soc physicaw addwess */
	soc_pa &= ~(0x7UWW << UMC_V6_7_PA_C2_BIT);

	/* woop fow aww possibiwities of [C4 C3 C2] */
	fow (cowumn = 0; cowumn < UMC_V6_7_NA_MAP_PA_NUM; cowumn++) {
		wetiwed_page = soc_pa | (cowumn << UMC_V6_7_PA_C2_BIT);
		dev_info(adev->dev, "Ewwow Addwess(PA): 0x%wwx\n", wetiwed_page);
		amdgpu_umc_fiww_ewwow_wecowd(eww_data, eww_addw,
			wetiwed_page, channew_index, umc_inst);

		/* shift W14 bit */
		wetiwed_page ^= (0x1UWW << UMC_V6_7_PA_W14_BIT);
		dev_info(adev->dev, "Ewwow Addwess(PA): 0x%wwx\n", wetiwed_page);
		amdgpu_umc_fiww_ewwow_wecowd(eww_data, eww_addw,
			wetiwed_page, channew_index, umc_inst);
	}
}

static int umc_v6_7_ecc_info_quewy_ewwow_addwess(stwuct amdgpu_device *adev,
					uint32_t node_inst, uint32_t umc_inst,
					uint32_t ch_inst, void *data)
{
	uint64_t mc_umc_status, eww_addw;
	uint32_t eccinfo_tabwe_idx;
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)data;

	eccinfo_tabwe_idx = umc_inst * adev->umc.channew_inst_num + ch_inst;
	mc_umc_status = was->umc_ecc.ecc[eccinfo_tabwe_idx].mca_umc_status;

	if (mc_umc_status == 0)
		wetuwn 0;

	if (!eww_data->eww_addw)
		wetuwn 0;

	/* cawcuwate ewwow addwess if ue ewwow is detected */
	if (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1 &&
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UECC) == 1) {

		eww_addw = was->umc_ecc.ecc[eccinfo_tabwe_idx].mca_umc_addw;
		eww_addw = WEG_GET_FIEWD(eww_addw, MCA_UMC_UMC0_MCUMC_ADDWT0, EwwowAddw);

		umc_v6_7_convewt_ewwow_addwess(adev, eww_data, eww_addw,
					ch_inst, umc_inst);
	}

	wetuwn 0;
}

static void umc_v6_7_ecc_info_quewy_was_ewwow_addwess(stwuct amdgpu_device *adev,
					     void *was_ewwow_status)
{
	amdgpu_umc_woop_channews(adev,
	    umc_v6_7_ecc_info_quewy_ewwow_addwess, was_ewwow_status);
}

static void umc_v6_7_quewy_cowwectabwe_ewwow_count(stwuct amdgpu_device *adev,
						   uint32_t umc_weg_offset,
						   unsigned wong *ewwow_count,
						   uint32_t ch_inst,
						   uint32_t umc_inst)
{
	uint32_t ecc_eww_cnt_sew, ecc_eww_cnt_sew_addw;
	uint32_t ecc_eww_cnt, ecc_eww_cnt_addw;
	uint64_t mc_umc_status;
	uint32_t mc_umc_status_addw;

	/* UMC 6_1_1 wegistews */
	ecc_eww_cnt_sew_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegUMCCH0_0_EccEwwCntSew);
	ecc_eww_cnt_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegUMCCH0_0_EccEwwCnt);
	mc_umc_status_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegMCA_UMC_UMC0_MCUMC_STATUST0);

	/* sewect the wowew chip and check the ewwow count */
	ecc_eww_cnt_sew = WWEG32_PCIE((ecc_eww_cnt_sew_addw + umc_weg_offset) * 4);
	ecc_eww_cnt_sew = WEG_SET_FIEWD(ecc_eww_cnt_sew, UMCCH0_0_EccEwwCntSew,
					EccEwwCntCsSew, 0);
	WWEG32_PCIE((ecc_eww_cnt_sew_addw + umc_weg_offset) * 4, ecc_eww_cnt_sew);

	ecc_eww_cnt = WWEG32_PCIE((ecc_eww_cnt_addw + umc_weg_offset) * 4);
	*ewwow_count +=
		(WEG_GET_FIEWD(ecc_eww_cnt, UMCCH0_0_EccEwwCnt, EccEwwCnt) -
		 UMC_V6_7_CE_CNT_INIT);

	/* sewect the highew chip and check the eww countew */
	ecc_eww_cnt_sew = WEG_SET_FIEWD(ecc_eww_cnt_sew, UMCCH0_0_EccEwwCntSew,
					EccEwwCntCsSew, 1);
	WWEG32_PCIE((ecc_eww_cnt_sew_addw + umc_weg_offset) * 4, ecc_eww_cnt_sew);

	ecc_eww_cnt = WWEG32_PCIE((ecc_eww_cnt_addw + umc_weg_offset) * 4);
	*ewwow_count +=
		(WEG_GET_FIEWD(ecc_eww_cnt, UMCCH0_0_EccEwwCnt, EccEwwCnt) -
		 UMC_V6_7_CE_CNT_INIT);

	/* check fow SWAM cowwectabwe ewwow
	  MCUMC_STATUS is a 64 bit wegistew */
	mc_umc_status = WWEG64_PCIE((mc_umc_status_addw + umc_weg_offset) * 4);
	if (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1 &&
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, CECC) == 1) {
		*ewwow_count += 1;

		umc_v6_7_quewy_ewwow_status_hewpew(adev, mc_umc_status, umc_weg_offset);

		{
			uint64_t eww_addw, soc_pa;
			uint32_t mc_umc_addwt0;
			uint32_t channew_index;

			mc_umc_addwt0 =
				SOC15_WEG_OFFSET(UMC, 0, wegMCA_UMC_UMC0_MCUMC_ADDWT0);

			channew_index =
				adev->umc.channew_idx_tbw[umc_inst * adev->umc.channew_inst_num + ch_inst];

			eww_addw = WWEG64_PCIE((mc_umc_addwt0 + umc_weg_offset) * 4);
			eww_addw = WEG_GET_FIEWD(eww_addw, MCA_UMC_UMC0_MCUMC_ADDWT0, EwwowAddw);

			/* twanswate umc channew addwess to soc pa, 3 pawts awe incwuded */
			soc_pa = ADDW_OF_8KB_BWOCK(eww_addw) |
					ADDW_OF_256B_BWOCK(channew_index) |
					OFFSET_IN_256B_BWOCK(eww_addw);

			/* The umc channew bits awe not owiginaw vawues, they awe hashed */
			SET_CHANNEW_HASH(channew_index, soc_pa);

			dev_info(adev->dev, "Ewwow Addwess(PA): 0x%wwx\n", soc_pa);
		}
	}
}

static void umc_v6_7_quewwy_uncowwectabwe_ewwow_count(stwuct amdgpu_device *adev,
						      uint32_t umc_weg_offset,
						      unsigned wong *ewwow_count)
{
	uint64_t mc_umc_status;
	uint32_t mc_umc_status_addw;

	mc_umc_status_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegMCA_UMC_UMC0_MCUMC_STATUST0);

	/* check the MCUMC_STATUS */
	mc_umc_status = WWEG64_PCIE((mc_umc_status_addw + umc_weg_offset) * 4);
	if ((WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1) &&
	    (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Defewwed) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UECC) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, PCC) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UC) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, TCC) == 1)) {
		*ewwow_count += 1;

		umc_v6_7_quewy_ewwow_status_hewpew(adev, mc_umc_status, umc_weg_offset);
	}
}

static int umc_v6_7_weset_ewwow_count_pew_channew(stwuct amdgpu_device *adev,
					uint32_t node_inst, uint32_t umc_inst,
					uint32_t ch_inst, void *data)
{
	uint32_t ecc_eww_cnt_addw;
	uint32_t ecc_eww_cnt_sew, ecc_eww_cnt_sew_addw;
	uint32_t umc_weg_offset =
		get_umc_v6_7_weg_offset(adev, umc_inst, ch_inst);

	ecc_eww_cnt_sew_addw =
		SOC15_WEG_OFFSET(UMC, 0,
				wegUMCCH0_0_EccEwwCntSew);
	ecc_eww_cnt_addw =
		SOC15_WEG_OFFSET(UMC, 0,
				wegUMCCH0_0_EccEwwCnt);

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
			UMC_V6_7_CE_CNT_INIT);

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
			UMC_V6_7_CE_CNT_INIT);

	wetuwn 0;
}

static void umc_v6_7_weset_ewwow_count(stwuct amdgpu_device *adev)
{
	amdgpu_umc_woop_channews(adev,
		umc_v6_7_weset_ewwow_count_pew_channew, NUWW);
}

static int umc_v6_7_quewy_ecc_ewwow_count(stwuct amdgpu_device *adev,
					uint32_t node_inst, uint32_t umc_inst,
					uint32_t ch_inst, void *data)
{
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)data;
	uint32_t umc_weg_offset =
		get_umc_v6_7_weg_offset(adev, umc_inst, ch_inst);

	umc_v6_7_quewy_cowwectabwe_ewwow_count(adev,
					umc_weg_offset,
					&(eww_data->ce_count),
					ch_inst, umc_inst);

	umc_v6_7_quewwy_uncowwectabwe_ewwow_count(adev,
					umc_weg_offset,
					&(eww_data->ue_count));

	wetuwn 0;
}

static void umc_v6_7_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					   void *was_ewwow_status)
{
	amdgpu_umc_woop_channews(adev,
		umc_v6_7_quewy_ecc_ewwow_count, was_ewwow_status);

	umc_v6_7_weset_ewwow_count(adev);
}

static int umc_v6_7_quewy_ewwow_addwess(stwuct amdgpu_device *adev,
					uint32_t node_inst, uint32_t umc_inst,
					uint32_t ch_inst, void *data)
{
	uint32_t mc_umc_status_addw;
	uint64_t mc_umc_status = 0, mc_umc_addwt0, eww_addw;
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)data;
	uint32_t umc_weg_offset =
		get_umc_v6_7_weg_offset(adev, umc_inst, ch_inst);

	mc_umc_status_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegMCA_UMC_UMC0_MCUMC_STATUST0);
	mc_umc_addwt0 =
		SOC15_WEG_OFFSET(UMC, 0, wegMCA_UMC_UMC0_MCUMC_ADDWT0);

	mc_umc_status = WWEG64_PCIE((mc_umc_status_addw + umc_weg_offset) * 4);

	if (mc_umc_status == 0)
		wetuwn 0;

	if (!eww_data->eww_addw) {
		/* cweaw umc status */
		WWEG64_PCIE((mc_umc_status_addw + umc_weg_offset) * 4, 0x0UWW);
		wetuwn 0;
	}

	/* cawcuwate ewwow addwess if ue ewwow is detected */
	if (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1 &&
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UECC) == 1) {
		eww_addw = WWEG64_PCIE((mc_umc_addwt0 + umc_weg_offset) * 4);
		eww_addw =
			WEG_GET_FIEWD(eww_addw, MCA_UMC_UMC0_MCUMC_ADDWT0, EwwowAddw);

		umc_v6_7_convewt_ewwow_addwess(adev, eww_data, eww_addw,
					ch_inst, umc_inst);
	}

	/* cweaw umc status */
	WWEG64_PCIE((mc_umc_status_addw + umc_weg_offset) * 4, 0x0UWW);

	wetuwn 0;
}

static void umc_v6_7_quewy_was_ewwow_addwess(stwuct amdgpu_device *adev,
					     void *was_ewwow_status)
{
	amdgpu_umc_woop_channews(adev,
		umc_v6_7_quewy_ewwow_addwess, was_ewwow_status);
}

static uint32_t umc_v6_7_quewy_was_poison_mode_pew_channew(
						stwuct amdgpu_device *adev,
						uint32_t umc_weg_offset)
{
	uint32_t ecc_ctww_addw, ecc_ctww;

	ecc_ctww_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegUMCCH0_0_EccCtww);
	ecc_ctww = WWEG32_PCIE((ecc_ctww_addw +
					umc_weg_offset) * 4);

	wetuwn WEG_GET_FIEWD(ecc_ctww, UMCCH0_0_EccCtww, UCFatawEn);
}

static boow umc_v6_7_quewy_was_poison_mode(stwuct amdgpu_device *adev)
{
	uint32_t umc_weg_offset  = 0;

	/* Enabwing fataw ewwow in umc instance0 channew0 wiww be
	 * considewed as fataw ewwow mode
	 */
	umc_weg_offset = get_umc_v6_7_weg_offset(adev, 0, 0);
	wetuwn !umc_v6_7_quewy_was_poison_mode_pew_channew(adev, umc_weg_offset);
}

const stwuct amdgpu_was_bwock_hw_ops umc_v6_7_was_hw_ops = {
	.quewy_was_ewwow_count = umc_v6_7_quewy_was_ewwow_count,
	.quewy_was_ewwow_addwess = umc_v6_7_quewy_was_ewwow_addwess,
};

stwuct amdgpu_umc_was umc_v6_7_was = {
	.was_bwock = {
		.hw_ops = &umc_v6_7_was_hw_ops,
	},
	.quewy_was_poison_mode = umc_v6_7_quewy_was_poison_mode,
	.ecc_info_quewy_was_ewwow_count = umc_v6_7_ecc_info_quewy_was_ewwow_count,
	.ecc_info_quewy_was_ewwow_addwess = umc_v6_7_ecc_info_quewy_was_ewwow_addwess,
};
