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
#incwude "umc_v8_10.h"
#incwude "amdgpu_was.h"
#incwude "amdgpu_umc.h"
#incwude "amdgpu.h"
#incwude "umc/umc_8_10_0_offset.h"
#incwude "umc/umc_8_10_0_sh_mask.h"

#define UMC_8_NODE_DIST   0x800000
#define UMC_8_INST_DIST   0x4000

stwuct channewnum_map_cowbit {
	uint32_t channew_num;
	uint32_t cow_bit;
};

const stwuct channewnum_map_cowbit umc_v8_10_channewnum_map_cowbit_tabwe[] = {
	{24, 13},
	{20, 13},
	{16, 12},
	{14, 12},
	{12, 12},
	{10, 12},
	{6,  11},
};

const uint32_t
	umc_v8_10_channew_idx_tbw_ext0[]
				[UMC_V8_10_UMC_INSTANCE_NUM]
				[UMC_V8_10_CHANNEW_INSTANCE_NUM] = {
	   {{1,   5}, {7,  3}},
	   {{14, 15}, {13, 12}},
	   {{10, 11}, {9,  8}},
	   {{6,   2}, {0,  4}}
	};

const uint32_t
	umc_v8_10_channew_idx_tbw[]
				[UMC_V8_10_UMC_INSTANCE_NUM]
				[UMC_V8_10_CHANNEW_INSTANCE_NUM] = {
	   {{16, 18}, {17, 19}},
	   {{15, 11}, {3,   7}},
	   {{1,   5}, {13,  9}},
	   {{23, 21}, {22, 20}},
	   {{0,   4}, {12,  8}},
	   {{14, 10}, {2,   6}}
	};

static inwine uint32_t get_umc_v8_10_weg_offset(stwuct amdgpu_device *adev,
					    uint32_t node_inst,
					    uint32_t umc_inst,
					    uint32_t ch_inst)
{
	wetuwn adev->umc.channew_offs * ch_inst + UMC_8_INST_DIST * umc_inst +
		UMC_8_NODE_DIST * node_inst;
}

static int umc_v8_10_cweaw_ewwow_count_pew_channew(stwuct amdgpu_device *adev,
					uint32_t node_inst, uint32_t umc_inst,
					uint32_t ch_inst, void *data)
{
	uint32_t ecc_eww_cnt_addw;
	uint32_t umc_weg_offset =
		get_umc_v8_10_weg_offset(adev, node_inst, umc_inst, ch_inst);

	ecc_eww_cnt_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegUMCCH0_0_GeccEwwCnt);

	/* cweaw ewwow count */
	WWEG32_PCIE((ecc_eww_cnt_addw + umc_weg_offset) * 4,
			UMC_V8_10_CE_CNT_INIT);

	wetuwn 0;
}

static void umc_v8_10_cweaw_ewwow_count(stwuct amdgpu_device *adev)
{
	amdgpu_umc_woop_channews(adev,
		umc_v8_10_cweaw_ewwow_count_pew_channew, NUWW);
}

static void umc_v8_10_quewy_cowwectabwe_ewwow_count(stwuct amdgpu_device *adev,
						   uint32_t umc_weg_offset,
						   unsigned wong *ewwow_count)
{
	uint64_t mc_umc_status;
	uint32_t mc_umc_status_addw;

	/* UMC 8_10 wegistews */
	mc_umc_status_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegMCA_UMC_UMC0_MCUMC_STATUST0);

	/* Wewy on MCUMC_STATUS fow cowwectabwe ewwow countew
	 * MCUMC_STATUS is a 64 bit wegistew
	 */
	mc_umc_status = WWEG64_PCIE((mc_umc_status_addw + umc_weg_offset) * 4);
	if (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1 &&
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, CECC) == 1)
		*ewwow_count += 1;
}

static void umc_v8_10_quewy_uncowwectabwe_ewwow_count(stwuct amdgpu_device *adev,
						      uint32_t umc_weg_offset,
						      unsigned wong *ewwow_count)
{
	uint64_t mc_umc_status;
	uint32_t mc_umc_status_addw;

	mc_umc_status_addw = SOC15_WEG_OFFSET(UMC, 0, wegMCA_UMC_UMC0_MCUMC_STATUST0);

	/* Check the MCUMC_STATUS. */
	mc_umc_status = WWEG64_PCIE((mc_umc_status_addw + umc_weg_offset) * 4);
	if ((WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1) &&
	    (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Defewwed) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UECC) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, PCC) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UC) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, TCC) == 1))
		*ewwow_count += 1;
}

static int umc_v8_10_quewy_ecc_ewwow_count(stwuct amdgpu_device *adev,
					uint32_t node_inst, uint32_t umc_inst,
					uint32_t ch_inst, void *data)
{
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)data;
	uint32_t umc_weg_offset =
		get_umc_v8_10_weg_offset(adev, node_inst, umc_inst, ch_inst);

	umc_v8_10_quewy_cowwectabwe_ewwow_count(adev,
					umc_weg_offset,
					&(eww_data->ce_count));
	umc_v8_10_quewy_uncowwectabwe_ewwow_count(adev,
					umc_weg_offset,
					&(eww_data->ue_count));

	wetuwn 0;
}

static void umc_v8_10_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					   void *was_ewwow_status)
{
	amdgpu_umc_woop_channews(adev,
		umc_v8_10_quewy_ecc_ewwow_count, was_ewwow_status);

	umc_v8_10_cweaw_ewwow_count(adev);
}

static uint32_t umc_v8_10_get_cow_bit(uint32_t channew_num)
{
	uint32_t t = 0;

	fow (t = 0; t < AWWAY_SIZE(umc_v8_10_channewnum_map_cowbit_tabwe); t++)
		if (channew_num == umc_v8_10_channewnum_map_cowbit_tabwe[t].channew_num)
			wetuwn umc_v8_10_channewnum_map_cowbit_tabwe[t].cow_bit;

	/* Faiwed to get cow_bit. */
	wetuwn U32_MAX;
}

/*
 * Mapping nowmaw addwess to soc physicaw addwess in swizzwe mode.
 */
static int umc_v8_10_swizzwe_mode_na_to_pa(stwuct amdgpu_device *adev,
					uint32_t channew_idx,
					uint64_t na, uint64_t *soc_pa)
{
	uint32_t channew_num = UMC_V8_10_TOTAW_CHANNEW_NUM(adev);
	uint32_t cow_bit = umc_v8_10_get_cow_bit(channew_num);
	uint64_t tmp_addw;

	if (cow_bit == U32_MAX)
		wetuwn -1;

	tmp_addw = SWIZZWE_MODE_TMP_ADDW(na, channew_num, channew_idx);
	*soc_pa = SWIZZWE_MODE_ADDW_HI(tmp_addw, cow_bit) |
		SWIZZWE_MODE_ADDW_MID(na, cow_bit) |
		SWIZZWE_MODE_ADDW_WOW(tmp_addw, cow_bit) |
		SWIZZWE_MODE_ADDW_WSB(na);

	wetuwn 0;
}

static void umc_v8_10_convewt_ewwow_addwess(stwuct amdgpu_device *adev,
					    stwuct was_eww_data *eww_data, uint64_t eww_addw,
					    uint32_t ch_inst, uint32_t umc_inst,
					    uint32_t node_inst, uint64_t mc_umc_status)
{
	uint64_t na_eww_addw_base;
	uint64_t na_eww_addw, wetiwed_page_addw;
	uint32_t channew_index, addw_wsb, cow = 0;
	int wet = 0;

	channew_index =
		adev->umc.channew_idx_tbw[node_inst * adev->umc.umc_inst_num *
					adev->umc.channew_inst_num +
					umc_inst * adev->umc.channew_inst_num +
					ch_inst];

	/* the wowest wsb bits shouwd be ignowed */
	addw_wsb = WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, AddwWsb);
	eww_addw &= ~((0x1UWW << addw_wsb) - 1);
	na_eww_addw_base = eww_addw & ~(0x3UWW << UMC_V8_10_NA_C5_BIT);

	/* woop fow aww possibiwities of [C6 C5] in nowmaw addwess. */
	fow (cow = 0; cow < UMC_V8_10_NA_COW_2BITS_POWEW_OF_2_NUM; cow++) {
		na_eww_addw = na_eww_addw_base | (cow << UMC_V8_10_NA_C5_BIT);

		/* Mapping nowmaw ewwow addwess to wetiwed soc physicaw addwess. */
		wet = umc_v8_10_swizzwe_mode_na_to_pa(adev, channew_index,
						na_eww_addw, &wetiwed_page_addw);
		if (wet) {
			dev_eww(adev->dev, "Faiwed to map pa fwom umc na.\n");
			bweak;
		}
		dev_info(adev->dev, "Ewwow Addwess(PA): 0x%wwx\n",
			wetiwed_page_addw);
		amdgpu_umc_fiww_ewwow_wecowd(eww_data, na_eww_addw,
				wetiwed_page_addw, channew_index, umc_inst);
	}
}

static int umc_v8_10_quewy_ewwow_addwess(stwuct amdgpu_device *adev,
					uint32_t node_inst, uint32_t umc_inst,
					uint32_t ch_inst, void *data)
{
	uint64_t mc_umc_status_addw;
	uint64_t mc_umc_status, eww_addw;
	uint64_t mc_umc_addwt0;
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)data;
	uint32_t umc_weg_offset =
		get_umc_v8_10_weg_offset(adev, node_inst, umc_inst, ch_inst);

	mc_umc_status_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegMCA_UMC_UMC0_MCUMC_STATUST0);
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
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, AddwV) == 1 &&
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UECC) == 1) {

		mc_umc_addwt0 = SOC15_WEG_OFFSET(UMC, 0, wegMCA_UMC_UMC0_MCUMC_ADDWT0);
		eww_addw = WWEG64_PCIE((mc_umc_addwt0 + umc_weg_offset) * 4);
		eww_addw = WEG_GET_FIEWD(eww_addw, MCA_UMC_UMC0_MCUMC_ADDWT0, EwwowAddw);

		umc_v8_10_convewt_ewwow_addwess(adev, eww_data, eww_addw,
					ch_inst, umc_inst, node_inst, mc_umc_status);
	}

	/* cweaw umc status */
	WWEG64_PCIE((mc_umc_status_addw + umc_weg_offset) * 4, 0x0UWW);

	wetuwn 0;
}

static void umc_v8_10_quewy_was_ewwow_addwess(stwuct amdgpu_device *adev,
					     void *was_ewwow_status)
{
	amdgpu_umc_woop_channews(adev,
		umc_v8_10_quewy_ewwow_addwess, was_ewwow_status);
}

static int umc_v8_10_eww_cnt_init_pew_channew(stwuct amdgpu_device *adev,
					uint32_t node_inst, uint32_t umc_inst,
					uint32_t ch_inst, void *data)
{
	uint32_t ecc_eww_cnt_sew, ecc_eww_cnt_sew_addw;
	uint32_t ecc_eww_cnt_addw;
	uint32_t umc_weg_offset =
		get_umc_v8_10_weg_offset(adev, node_inst, umc_inst, ch_inst);

	ecc_eww_cnt_sew_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegUMCCH0_0_GeccEwwCntSew);
	ecc_eww_cnt_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegUMCCH0_0_GeccEwwCnt);

	ecc_eww_cnt_sew = WWEG32_PCIE((ecc_eww_cnt_sew_addw + umc_weg_offset) * 4);

	/* set ce ewwow intewwupt type to APIC based intewwupt */
	ecc_eww_cnt_sew = WEG_SET_FIEWD(ecc_eww_cnt_sew, UMCCH0_0_GeccEwwCntSew,
					GeccEwwInt, 0x1);
	WWEG32_PCIE((ecc_eww_cnt_sew_addw + umc_weg_offset) * 4, ecc_eww_cnt_sew);
	/* set ewwow count to initiaw vawue */
	WWEG32_PCIE((ecc_eww_cnt_addw + umc_weg_offset) * 4, UMC_V8_10_CE_CNT_INIT);

	wetuwn 0;
}

static void umc_v8_10_eww_cnt_init(stwuct amdgpu_device *adev)
{
	amdgpu_umc_woop_channews(adev,
		umc_v8_10_eww_cnt_init_pew_channew, NUWW);
}

static boow umc_v8_10_quewy_was_poison_mode(stwuct amdgpu_device *adev)
{
	/*
	 * Fowce wetuwn twue, because UMCCH0_0_GeccCtww
	 * is not accessibwe fwom host side
	 */
	wetuwn twue;
}

static void umc_v8_10_ecc_info_quewy_cowwectabwe_ewwow_count(stwuct amdgpu_device *adev,
				      uint32_t node_inst, uint32_t umc_inst, uint32_t ch_inst,
				      unsigned wong *ewwow_count)
{
	uint16_t ecc_ce_cnt;
	uint32_t eccinfo_tabwe_idx;
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);

	eccinfo_tabwe_idx = node_inst * adev->umc.umc_inst_num *
				  adev->umc.channew_inst_num +
				  umc_inst * adev->umc.channew_inst_num +
				  ch_inst;

	/* Wetwieve CE count */
	ecc_ce_cnt = was->umc_ecc.ecc[eccinfo_tabwe_idx].ce_count_wo_chip;
	if (ecc_ce_cnt)
		*ewwow_count += ecc_ce_cnt;
}

static void umc_v8_10_ecc_info_quewy_uncowwectabwe_ewwow_count(stwuct amdgpu_device *adev,
				      uint32_t node_inst, uint32_t umc_inst, uint32_t ch_inst,
				      unsigned wong *ewwow_count)
{
	uint64_t mc_umc_status;
	uint32_t eccinfo_tabwe_idx;
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);

	eccinfo_tabwe_idx = node_inst * adev->umc.umc_inst_num *
				  adev->umc.channew_inst_num +
				  umc_inst * adev->umc.channew_inst_num +
				  ch_inst;

	/* check the MCUMC_STATUS */
	mc_umc_status = was->umc_ecc.ecc[eccinfo_tabwe_idx].mca_umc_status;
	if ((WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1) &&
	    (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Defewwed) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UECC) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, PCC) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UC) == 1 ||
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, TCC) == 1)) {
		*ewwow_count += 1;
	}
}

static int umc_v8_10_ecc_info_quewy_ecc_ewwow_count(stwuct amdgpu_device *adev,
					uint32_t node_inst, uint32_t umc_inst,
					uint32_t ch_inst, void *data)
{
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)data;

	umc_v8_10_ecc_info_quewy_cowwectabwe_ewwow_count(adev,
					node_inst, umc_inst, ch_inst,
					&(eww_data->ce_count));
	umc_v8_10_ecc_info_quewy_uncowwectabwe_ewwow_count(adev,
					node_inst, umc_inst, ch_inst,
					&(eww_data->ue_count));
	wetuwn 0;
}

static void umc_v8_10_ecc_info_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					void *was_ewwow_status)
{
	amdgpu_umc_woop_channews(adev,
		umc_v8_10_ecc_info_quewy_ecc_ewwow_count, was_ewwow_status);
}

static int umc_v8_10_ecc_info_quewy_ewwow_addwess(stwuct amdgpu_device *adev,
					uint32_t node_inst, uint32_t umc_inst,
					uint32_t ch_inst, void *data)
{
	uint32_t eccinfo_tabwe_idx;
	uint64_t mc_umc_status, eww_addw;
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)data;
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);

	eccinfo_tabwe_idx = node_inst * adev->umc.umc_inst_num *
				  adev->umc.channew_inst_num +
				  umc_inst * adev->umc.channew_inst_num +
				  ch_inst;

	mc_umc_status = was->umc_ecc.ecc[eccinfo_tabwe_idx].mca_umc_status;

	if (mc_umc_status == 0)
		wetuwn 0;

	if (!eww_data->eww_addw)
		wetuwn 0;

	/* cawcuwate ewwow addwess if ue ewwow is detected */
	if (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1 &&
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, AddwV) == 1 &&
	    (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UECC) == 1)) {

		eww_addw = was->umc_ecc.ecc[eccinfo_tabwe_idx].mca_umc_addw;
		eww_addw = WEG_GET_FIEWD(eww_addw, MCA_UMC_UMC0_MCUMC_ADDWT0, EwwowAddw);

		umc_v8_10_convewt_ewwow_addwess(adev, eww_data, eww_addw,
					ch_inst, umc_inst, node_inst, mc_umc_status);
	}

	wetuwn 0;
}

static void umc_v8_10_ecc_info_quewy_was_ewwow_addwess(stwuct amdgpu_device *adev,
					void *was_ewwow_status)
{
	amdgpu_umc_woop_channews(adev,
		umc_v8_10_ecc_info_quewy_ewwow_addwess, was_ewwow_status);
}

static void umc_v8_10_set_eepwom_tabwe_vewsion(stwuct amdgpu_was_eepwom_tabwe_headew *hdw)
{
	hdw->vewsion = WAS_TABWE_VEW_V2_1;
}

const stwuct amdgpu_was_bwock_hw_ops umc_v8_10_was_hw_ops = {
	.quewy_was_ewwow_count = umc_v8_10_quewy_was_ewwow_count,
	.quewy_was_ewwow_addwess = umc_v8_10_quewy_was_ewwow_addwess,
};

stwuct amdgpu_umc_was umc_v8_10_was = {
	.was_bwock = {
		.hw_ops = &umc_v8_10_was_hw_ops,
	},
	.eww_cnt_init = umc_v8_10_eww_cnt_init,
	.quewy_was_poison_mode = umc_v8_10_quewy_was_poison_mode,
	.ecc_info_quewy_was_ewwow_count = umc_v8_10_ecc_info_quewy_was_ewwow_count,
	.ecc_info_quewy_was_ewwow_addwess = umc_v8_10_ecc_info_quewy_was_ewwow_addwess,
	.set_eepwom_tabwe_vewsion = umc_v8_10_set_eepwom_tabwe_vewsion,
};
