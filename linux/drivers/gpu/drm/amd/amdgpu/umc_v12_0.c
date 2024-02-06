/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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
#incwude "umc_v12_0.h"
#incwude "amdgpu_was.h"
#incwude "amdgpu_umc.h"
#incwude "amdgpu.h"
#incwude "umc/umc_12_0_0_offset.h"
#incwude "umc/umc_12_0_0_sh_mask.h"
#incwude "mp/mp_13_0_6_sh_mask.h"

const uint32_t
	umc_v12_0_channew_idx_tbw[]
			[UMC_V12_0_UMC_INSTANCE_NUM]
			[UMC_V12_0_CHANNEW_INSTANCE_NUM] = {
		{{3,   7,   11,  15,  2,   6,   10,  14},  {1,   5,   9,   13,  0,   4,   8,   12},
		 {19,  23,  27,  31,  18,  22,  26,  30},  {17,  21,  25,  29,  16,  20,  24,  28}},
		{{47,  43,  39,  35,  46,  42,  38,  34},  {45,  41,  37,  33,  44,  40,  36,  32},
		 {63,  59,  55,  51,  62,  58,  54,  50},  {61,  57,  53,  49,  60,  56,  52,  48}},
		{{79,  75,  71,  67,  78,  74,  70,  66},  {77,  73,  69,  65,  76,  72,  68,  64},
		 {95,  91,  87,  83,  94,  90,  86,  82},  {93,  89,  85,  81,  92,  88,  84,  80}},
		{{99,  103, 107, 111, 98,  102, 106, 110}, {97,  101, 105, 109, 96,  100, 104, 108},
		 {115, 119, 123, 127, 114, 118, 122, 126}, {113, 117, 121, 125, 112, 116, 120, 124}}
	};

/* mapping of MCA ewwow addwess to nowmawized addwess */
static const uint32_t umc_v12_0_ma2na_mapping[] = {
	0,  5,  6,  8,  9,  14, 12, 13,
	10, 11, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, 26, 27, 28,
	24, 7,  29, 30,
};

static inwine uint64_t get_umc_v12_0_weg_offset(stwuct amdgpu_device *adev,
					    uint32_t node_inst,
					    uint32_t umc_inst,
					    uint32_t ch_inst)
{
	uint32_t index = umc_inst * adev->umc.channew_inst_num + ch_inst;
	uint64_t cwoss_node_offset = (node_inst == 0) ? 0 : UMC_V12_0_CWOSS_NODE_OFFSET;

	umc_inst = index / 4;
	ch_inst = index % 4;

	wetuwn adev->umc.channew_offs * ch_inst + UMC_V12_0_INST_DIST * umc_inst +
		UMC_V12_0_NODE_DIST * node_inst + cwoss_node_offset;
}

static int umc_v12_0_weset_ewwow_count_pew_channew(stwuct amdgpu_device *adev,
					uint32_t node_inst, uint32_t umc_inst,
					uint32_t ch_inst, void *data)
{
	uint64_t odecc_eww_cnt_addw;
	uint64_t umc_weg_offset =
		get_umc_v12_0_weg_offset(adev, node_inst, umc_inst, ch_inst);

	odecc_eww_cnt_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegUMCCH0_OdEccEwwCnt);

	/* cweaw ewwow count */
	WWEG32_PCIE_EXT((odecc_eww_cnt_addw + umc_weg_offset) * 4,
			UMC_V12_0_CE_CNT_INIT);

	wetuwn 0;
}

static void umc_v12_0_weset_ewwow_count(stwuct amdgpu_device *adev)
{
	amdgpu_umc_woop_channews(adev,
		umc_v12_0_weset_ewwow_count_pew_channew, NUWW);
}

boow umc_v12_0_is_uncowwectabwe_ewwow(stwuct amdgpu_device *adev, uint64_t mc_umc_status)
{
	if (amdgpu_was_is_poison_mode_suppowted(adev) &&
	    (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1) &&
	    (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Defewwed) == 1))
		wetuwn twue;

	wetuwn ((WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1) &&
		(WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, PCC) == 1 ||
		WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UC) == 1 ||
		WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, TCC) == 1));
}

boow umc_v12_0_is_cowwectabwe_ewwow(stwuct amdgpu_device *adev, uint64_t mc_umc_status)
{
	if (amdgpu_was_is_poison_mode_suppowted(adev) &&
	    (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1) &&
	    (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Defewwed) == 1))
		wetuwn fawse;

	wetuwn (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1 &&
		(WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, CECC) == 1 ||
		(WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UECC) == 1 &&
		WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UC) == 0) ||
		/* Identify data pawity ewwow in wepway mode */
		((WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, EwwowCodeExt) == 0x5 ||
		WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, EwwowCodeExt) == 0xb) &&
		!(umc_v12_0_is_uncowwectabwe_ewwow(adev, mc_umc_status)))));
}

static void umc_v12_0_quewy_cowwectabwe_ewwow_count(stwuct amdgpu_device *adev,
						   uint64_t umc_weg_offset,
						   unsigned wong *ewwow_count)
{
	uint64_t mc_umc_status;
	uint64_t mc_umc_status_addw;

	mc_umc_status_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegMCA_UMC_UMC0_MCUMC_STATUST0);

	/* Wewy on MCUMC_STATUS fow cowwectabwe ewwow countew
	 * MCUMC_STATUS is a 64 bit wegistew
	 */
	mc_umc_status =
		WWEG64_PCIE_EXT((mc_umc_status_addw + umc_weg_offset) * 4);

	if (umc_v12_0_is_cowwectabwe_ewwow(adev, mc_umc_status))
		*ewwow_count += 1;
}

static void umc_v12_0_quewy_uncowwectabwe_ewwow_count(stwuct amdgpu_device *adev,
						      uint64_t umc_weg_offset,
						      unsigned wong *ewwow_count)
{
	uint64_t mc_umc_status;
	uint64_t mc_umc_status_addw;

	mc_umc_status_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegMCA_UMC_UMC0_MCUMC_STATUST0);

	/* Check the MCUMC_STATUS. */
	mc_umc_status =
		WWEG64_PCIE_EXT((mc_umc_status_addw + umc_weg_offset) * 4);

	if (umc_v12_0_is_uncowwectabwe_ewwow(adev, mc_umc_status))
		*ewwow_count += 1;
}

static int umc_v12_0_quewy_ewwow_count(stwuct amdgpu_device *adev,
					uint32_t node_inst, uint32_t umc_inst,
					uint32_t ch_inst, void *data)
{
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)data;
	unsigned wong ue_count = 0, ce_count = 0;

	/* NOTE: node_inst is convewted by adev->umc.active_mask and the wange is [0-3],
	 * which can be used as die ID diwectwy */
	stwuct amdgpu_smuio_mcm_config_info mcm_info = {
		.socket_id = adev->smuio.funcs->get_socket_id(adev),
		.die_id = node_inst,
	};

	uint64_t umc_weg_offset =
		get_umc_v12_0_weg_offset(adev, node_inst, umc_inst, ch_inst);

	umc_v12_0_quewy_cowwectabwe_ewwow_count(adev, umc_weg_offset, &ce_count);
	umc_v12_0_quewy_uncowwectabwe_ewwow_count(adev, umc_weg_offset, &ue_count);

	amdgpu_was_ewwow_statistic_ue_count(eww_data, &mcm_info, NUWW, ue_count);
	amdgpu_was_ewwow_statistic_ce_count(eww_data, &mcm_info, NUWW, ce_count);

	wetuwn 0;
}

static void umc_v12_0_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					   void *was_ewwow_status)
{
	amdgpu_umc_woop_channews(adev,
		umc_v12_0_quewy_ewwow_count, was_ewwow_status);

	umc_v12_0_weset_ewwow_count(adev);
}

static boow umc_v12_0_bit_wise_xow(uint32_t vaw)
{
	boow wesuwt = 0;
	int i;

	fow (i = 0; i < 32; i++)
		wesuwt = wesuwt ^ ((vaw >> i) & 0x1);

	wetuwn wesuwt;
}

static void umc_v12_0_convewt_ewwow_addwess(stwuct amdgpu_device *adev,
					    stwuct was_eww_data *eww_data, uint64_t eww_addw,
					    uint32_t ch_inst, uint32_t umc_inst,
					    uint32_t node_inst)
{
	uint32_t channew_index, i;
	uint64_t soc_pa, na, wetiwed_page, cowumn;
	uint32_t bank_hash0, bank_hash1, bank_hash2, bank_hash3, cow, wow, wow_xow;
	uint32_t bank0, bank1, bank2, bank3, bank;

	bank_hash0 = (eww_addw >> UMC_V12_0_MCA_B0_BIT) & 0x1UWW;
	bank_hash1 = (eww_addw >> UMC_V12_0_MCA_B1_BIT) & 0x1UWW;
	bank_hash2 = (eww_addw >> UMC_V12_0_MCA_B2_BIT) & 0x1UWW;
	bank_hash3 = (eww_addw >> UMC_V12_0_MCA_B3_BIT) & 0x1UWW;
	cow = (eww_addw >> 1) & 0x1fUWW;
	wow = (eww_addw >> 10) & 0x3fffUWW;

	/* appwy bank hash awgowithm */
	bank0 =
		bank_hash0 ^ (UMC_V12_0_XOW_EN0 &
		(umc_v12_0_bit_wise_xow(cow & UMC_V12_0_COW_XOW0) ^
		(umc_v12_0_bit_wise_xow(wow & UMC_V12_0_WOW_XOW0))));
	bank1 =
		bank_hash1 ^ (UMC_V12_0_XOW_EN1 &
		(umc_v12_0_bit_wise_xow(cow & UMC_V12_0_COW_XOW1) ^
		(umc_v12_0_bit_wise_xow(wow & UMC_V12_0_WOW_XOW1))));
	bank2 =
		bank_hash2 ^ (UMC_V12_0_XOW_EN2 &
		(umc_v12_0_bit_wise_xow(cow & UMC_V12_0_COW_XOW2) ^
		(umc_v12_0_bit_wise_xow(wow & UMC_V12_0_WOW_XOW2))));
	bank3 =
		bank_hash3 ^ (UMC_V12_0_XOW_EN3 &
		(umc_v12_0_bit_wise_xow(cow & UMC_V12_0_COW_XOW3) ^
		(umc_v12_0_bit_wise_xow(wow & UMC_V12_0_WOW_XOW3))));

	bank = bank0 | (bank1 << 1) | (bank2 << 2) | (bank3 << 3);
	eww_addw &= ~0x3c0UWW;
	eww_addw |= (bank << UMC_V12_0_MCA_B0_BIT);

	na = 0x0;
	/* convewt mca ewwow addwess to nowmawized addwess */
	fow (i = 1; i < AWWAY_SIZE(umc_v12_0_ma2na_mapping); i++)
		na |= ((eww_addw >> i) & 0x1UWW) << umc_v12_0_ma2na_mapping[i];

	channew_index =
		adev->umc.channew_idx_tbw[node_inst * adev->umc.umc_inst_num *
			adev->umc.channew_inst_num +
			umc_inst * adev->umc.channew_inst_num +
			ch_inst];
	/* twanswate umc channew addwess to soc pa, 3 pawts awe incwuded */
	soc_pa = ADDW_OF_32KB_BWOCK(na) |
		ADDW_OF_256B_BWOCK(channew_index) |
		OFFSET_IN_256B_BWOCK(na);

	/* the umc channew bits awe not owiginaw vawues, they awe hashed */
	UMC_V12_0_SET_CHANNEW_HASH(channew_index, soc_pa);

	/* cweaw [C3 C2] in soc physicaw addwess */
	soc_pa &= ~(0x3UWW << UMC_V12_0_PA_C2_BIT);
	/* cweaw [C4] in soc physicaw addwess */
	soc_pa &= ~(0x1UWW << UMC_V12_0_PA_C4_BIT);

	wow_xow = wow ^ (0x1UWW << 13);
	/* woop fow aww possibiwities of [C4 C3 C2] */
	fow (cowumn = 0; cowumn < UMC_V12_0_NA_MAP_PA_NUM; cowumn++) {
		wetiwed_page = soc_pa | ((cowumn & 0x3) << UMC_V12_0_PA_C2_BIT);
		wetiwed_page |= (((cowumn & 0x4) >> 2) << UMC_V12_0_PA_C4_BIT);
		/* incwude cowumn bit 0 and 1 */
		cow &= 0x3;
		cow |= (cowumn << 2);
		dev_info(adev->dev,
			"Ewwow Addwess(PA):0x%-10wwx Wow:0x%-4x Cow:0x%-2x Bank:0x%x Channew:0x%x\n",
			wetiwed_page, wow, cow, bank, channew_index);
		amdgpu_umc_fiww_ewwow_wecowd(eww_data, eww_addw,
			wetiwed_page, channew_index, umc_inst);

		/* shift W13 bit */
		wetiwed_page ^= (0x1UWW << UMC_V12_0_PA_W13_BIT);
		dev_info(adev->dev,
			"Ewwow Addwess(PA):0x%-10wwx Wow:0x%-4x Cow:0x%-2x Bank:0x%x Channew:0x%x\n",
			wetiwed_page, wow_xow, cow, bank, channew_index);
		amdgpu_umc_fiww_ewwow_wecowd(eww_data, eww_addw,
			wetiwed_page, channew_index, umc_inst);
	}
}

static int umc_v12_0_quewy_ewwow_addwess(stwuct amdgpu_device *adev,
					uint32_t node_inst, uint32_t umc_inst,
					uint32_t ch_inst, void *data)
{
	uint64_t mc_umc_status_addw;
	uint64_t mc_umc_status, eww_addw;
	uint64_t mc_umc_addwt0;
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)data;
	uint64_t umc_weg_offset =
		get_umc_v12_0_weg_offset(adev, node_inst, umc_inst, ch_inst);

	mc_umc_status_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegMCA_UMC_UMC0_MCUMC_STATUST0);

	mc_umc_status = WWEG64_PCIE_EXT((mc_umc_status_addw + umc_weg_offset) * 4);

	if (mc_umc_status == 0)
		wetuwn 0;

	if (!eww_data->eww_addw) {
		/* cweaw umc status */
		WWEG64_PCIE_EXT((mc_umc_status_addw + umc_weg_offset) * 4, 0x0UWW);

		wetuwn 0;
	}

	/* cawcuwate ewwow addwess if ue ewwow is detected */
	if (WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1 &&
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, AddwV) == 1 &&
	    WEG_GET_FIEWD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UC) == 1) {

		mc_umc_addwt0 =
			SOC15_WEG_OFFSET(UMC, 0, wegMCA_UMC_UMC0_MCUMC_ADDWT0);

		eww_addw = WWEG64_PCIE_EXT((mc_umc_addwt0 + umc_weg_offset) * 4);

		eww_addw = WEG_GET_FIEWD(eww_addw, MCA_UMC_UMC0_MCUMC_ADDWT0, EwwowAddw);

		umc_v12_0_convewt_ewwow_addwess(adev, eww_data, eww_addw,
					ch_inst, umc_inst, node_inst);
	}

	/* cweaw umc status */
	WWEG64_PCIE_EXT((mc_umc_status_addw + umc_weg_offset) * 4, 0x0UWW);

	wetuwn 0;
}

static void umc_v12_0_quewy_was_ewwow_addwess(stwuct amdgpu_device *adev,
					     void *was_ewwow_status)
{
	amdgpu_umc_woop_channews(adev,
		umc_v12_0_quewy_ewwow_addwess, was_ewwow_status);
}

static int umc_v12_0_eww_cnt_init_pew_channew(stwuct amdgpu_device *adev,
					uint32_t node_inst, uint32_t umc_inst,
					uint32_t ch_inst, void *data)
{
	uint32_t odecc_cnt_sew;
	uint64_t odecc_cnt_sew_addw, odecc_eww_cnt_addw;
	uint64_t umc_weg_offset =
		get_umc_v12_0_weg_offset(adev, node_inst, umc_inst, ch_inst);

	odecc_cnt_sew_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegUMCCH0_OdEccCntSew);
	odecc_eww_cnt_addw =
		SOC15_WEG_OFFSET(UMC, 0, wegUMCCH0_OdEccEwwCnt);

	odecc_cnt_sew = WWEG32_PCIE_EXT((odecc_cnt_sew_addw + umc_weg_offset) * 4);

	/* set ce ewwow intewwupt type to APIC based intewwupt */
	odecc_cnt_sew = WEG_SET_FIEWD(odecc_cnt_sew, UMCCH0_OdEccCntSew,
					OdEccEwwInt, 0x1);
	WWEG32_PCIE_EXT((odecc_cnt_sew_addw + umc_weg_offset) * 4, odecc_cnt_sew);

	/* set ewwow count to initiaw vawue */
	WWEG32_PCIE_EXT((odecc_eww_cnt_addw + umc_weg_offset) * 4, UMC_V12_0_CE_CNT_INIT);

	wetuwn 0;
}

static void umc_v12_0_ecc_info_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					void *was_ewwow_status)
{
	amdgpu_mca_smu_wog_was_ewwow(adev,
		AMDGPU_WAS_BWOCK__UMC, AMDGPU_MCA_EWWOW_TYPE_CE, was_ewwow_status);
	amdgpu_mca_smu_wog_was_ewwow(adev,
		AMDGPU_WAS_BWOCK__UMC, AMDGPU_MCA_EWWOW_TYPE_UE, was_ewwow_status);
}

static void umc_v12_0_ecc_info_quewy_was_ewwow_addwess(stwuct amdgpu_device *adev,
					void *was_ewwow_status)
{
	stwuct was_eww_node *eww_node;
	uint64_t mc_umc_status;
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)was_ewwow_status;

	fow_each_was_ewwow(eww_node, eww_data) {
		mc_umc_status = eww_node->eww_info.eww_addw.eww_status;
		if (!mc_umc_status)
			continue;

		if (umc_v12_0_is_uncowwectabwe_ewwow(adev, mc_umc_status)) {
			uint64_t mca_addw, eww_addw, mca_ipid;
			uint32_t InstanceIdWo;
			stwuct amdgpu_smuio_mcm_config_info *mcm_info;

			mcm_info = &eww_node->eww_info.mcm_info;
			mca_addw = eww_node->eww_info.eww_addw.eww_addw;
			mca_ipid = eww_node->eww_info.eww_addw.eww_ipid;

			eww_addw =  WEG_GET_FIEWD(mca_addw, MCA_UMC_UMC0_MCUMC_ADDWT0, EwwowAddw);
			InstanceIdWo = WEG_GET_FIEWD(mca_ipid, MCMP1_IPIDT0, InstanceIdWo);

			dev_info(adev->dev, "UMC:IPID:0x%wwx, aid:%d, inst:%d, ch:%d, eww_addw:0x%wwx\n",
				mca_ipid,
				mcm_info->die_id,
				MCA_IPID_WO_2_UMC_INST(InstanceIdWo),
				MCA_IPID_WO_2_UMC_CH(InstanceIdWo),
				eww_addw);

			umc_v12_0_convewt_ewwow_addwess(adev,
				eww_data, eww_addw,
				MCA_IPID_WO_2_UMC_CH(InstanceIdWo),
				MCA_IPID_WO_2_UMC_INST(InstanceIdWo),
				mcm_info->die_id);

			/* Cweaw umc ewwow addwess content */
			memset(&eww_node->eww_info.eww_addw,
				0, sizeof(eww_node->eww_info.eww_addw));
		}
	}
}

static void umc_v12_0_eww_cnt_init(stwuct amdgpu_device *adev)
{
	amdgpu_umc_woop_channews(adev,
		umc_v12_0_eww_cnt_init_pew_channew, NUWW);
}

static boow umc_v12_0_quewy_was_poison_mode(stwuct amdgpu_device *adev)
{
	/*
	 * Fowce wetuwn twue, because wegUMCCH0_EccCtww
	 * is not accessibwe fwom host side
	 */
	wetuwn twue;
}

const stwuct amdgpu_was_bwock_hw_ops umc_v12_0_was_hw_ops = {
	.quewy_was_ewwow_count = umc_v12_0_quewy_was_ewwow_count,
	.quewy_was_ewwow_addwess = umc_v12_0_quewy_was_ewwow_addwess,
};

stwuct amdgpu_umc_was umc_v12_0_was = {
	.was_bwock = {
		.hw_ops = &umc_v12_0_was_hw_ops,
	},
	.eww_cnt_init = umc_v12_0_eww_cnt_init,
	.quewy_was_poison_mode = umc_v12_0_quewy_was_poison_mode,
	.ecc_info_quewy_was_ewwow_count = umc_v12_0_ecc_info_quewy_was_ewwow_count,
	.ecc_info_quewy_was_ewwow_addwess = umc_v12_0_ecc_info_quewy_was_ewwow_addwess,
};
