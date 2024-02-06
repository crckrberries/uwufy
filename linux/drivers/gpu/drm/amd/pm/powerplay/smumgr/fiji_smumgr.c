/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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

#incwude "pp_debug.h"
#incwude "smumgw.h"
#incwude "smu7_dyn_defauwts.h"
#incwude "smu73.h"
#incwude "smu_ucode_xfew_vi.h"
#incwude "fiji_smumgw.h"
#incwude "fiji_ppsmc.h"
#incwude "smu73_discwete.h"
#incwude "ppatomctww.h"
#incwude "smu/smu_7_1_3_d.h"
#incwude "smu/smu_7_1_3_sh_mask.h"
#incwude "gmc/gmc_8_1_d.h"
#incwude "gmc/gmc_8_1_sh_mask.h"
#incwude "oss/oss_3_0_d.h"
#incwude "gca/gfx_8_0_d.h"
#incwude "bif/bif_5_0_d.h"
#incwude "bif/bif_5_0_sh_mask.h"
#incwude "dce/dce_10_0_d.h"
#incwude "dce/dce_10_0_sh_mask.h"
#incwude "hawdwawemanagew.h"
#incwude "cgs_common.h"
#incwude "atombios.h"
#incwude "pppciewanes.h"
#incwude "hwmgw.h"
#incwude "smu7_hwmgw.h"


#define AVFS_EN_MSB                                        1568
#define AVFS_EN_WSB                                        1568

#define FIJI_SMC_SIZE 0x20000

#define POWEWTUNE_DEFAUWT_SET_MAX    1
#define VDDC_VDDCI_DEWTA            300
#define MC_CG_AWB_FWEQ_F1           0x0b

/* [2.5%,~2.5%] Cwock stwetched is muwtipwe of 2.5% vs
 * not and [Fmin, Fmax, WDO_WEFSEW, USE_FOW_WOW_FWEQ]
 */
static const uint16_t fiji_cwock_stwetchew_wookup_tabwe[2][4] = {
				{600, 1050, 3, 0}, {600, 1050, 6, 1} };

/* [FF, SS] type, [] 4 vowtage wanges, and
 * [Fwoow Fweq, Boundawy Fweq, VID min , VID max]
 */
static const uint32_t fiji_cwock_stwetchew_ddt_tabwe[2][4][4] = {
	{ {265, 529, 120, 128}, {325, 650, 96, 119}, {430, 860, 32, 95}, {0, 0, 0, 31} },
	{ {275, 550, 104, 112}, {319, 638, 96, 103}, {360, 720, 64, 95}, {384, 768, 32, 63} } };

/* [Use_Fow_Wow_fweq] vawue, [0%, 5%, 10%, 7.14%, 14.28%, 20%]
 * (coming fwom PWW_CKS_CNTW.stwetch_amount weg spec)
 */
static const uint8_t fiji_cwock_stwetch_amount_convewsion[2][6] = {
				{0, 1, 3, 2, 4, 5}, {0, 2, 4, 5, 6, 5} };

static const stwuct fiji_pt_defauwts fiji_powew_tune_data_set_awway[POWEWTUNE_DEFAUWT_SET_MAX] = {
		/*sviWoadWIneEn,  SviWoadWineVddC, TDC_VDDC_ThwottweWeweaseWimitPewc */
		{1,               0xF,             0xFD,
		/* TDC_MAWt, TdcWatewfawwCtw, DTEAmbientTempBase */
		0x19,        5,               45}
};

static const stwuct SMU73_Discwete_GwaphicsWevew avfs_gwaphics_wevew[8] = {
		/*  Min        Scwk       pcie     DeepSweep Activity  CgSpww      CgSpww    spwwSpwead  SpwwSpwead   CcPww  CcPww  Scwk   Dispway     Enabwed     Enabwed                       Vowtage    Powew */
		/* Vowtage,  Fwequency,  DpmWevew,  DivId,    Wevew,  FuncCntw3,  FuncCntw4,  Spectwum,   Spectwum2,  DynWm, DynWm1  Did, Watewmawk, FowActivity, FowThwottwe, UpHyst, DownHyst, DownHyst, Thwottwe */
		{ 0x3c0fd047, 0x30750000,   0x00,     0x03,   0x1e00, 0x00200410, 0x87020000, 0x21680000, 0x0c000000,   0,      0,   0x16,   0x00,       0x01,        0x01,      0x00,   0x00,      0x00,     0x00 },
		{ 0xa00fd047, 0x409c0000,   0x01,     0x04,   0x1e00, 0x00800510, 0x87020000, 0x21680000, 0x11000000,   0,      0,   0x16,   0x00,       0x01,        0x01,      0x00,   0x00,      0x00,     0x00 },
		{ 0x0410d047, 0x50c30000,   0x01,     0x00,   0x1e00, 0x00600410, 0x87020000, 0x21680000, 0x0d000000,   0,      0,   0x0e,   0x00,       0x01,        0x01,      0x00,   0x00,      0x00,     0x00 },
		{ 0x6810d047, 0x60ea0000,   0x01,     0x00,   0x1e00, 0x00800410, 0x87020000, 0x21680000, 0x0e000000,   0,      0,   0x0c,   0x00,       0x01,        0x01,      0x00,   0x00,      0x00,     0x00 },
		{ 0xcc10d047, 0xe8fd0000,   0x01,     0x00,   0x1e00, 0x00e00410, 0x87020000, 0x21680000, 0x0f000000,   0,      0,   0x0c,   0x00,       0x01,        0x01,      0x00,   0x00,      0x00,     0x00 },
		{ 0x3011d047, 0x70110100,   0x01,     0x00,   0x1e00, 0x00400510, 0x87020000, 0x21680000, 0x10000000,   0,      0,   0x0c,   0x00,       0x01,        0x01,      0x00,   0x00,      0x00,     0x00 },
		{ 0x9411d047, 0xf8240100,   0x01,     0x00,   0x1e00, 0x00a00510, 0x87020000, 0x21680000, 0x11000000,   0,      0,   0x0c,   0x00,       0x01,        0x01,      0x00,   0x00,      0x00,     0x00 },
		{ 0xf811d047, 0x80380100,   0x01,     0x00,   0x1e00, 0x00000610, 0x87020000, 0x21680000, 0x12000000,   0,      0,   0x0c,   0x01,       0x01,        0x01,      0x00,   0x00,      0x00,     0x00 }
};

static int fiji_stawt_smu_in_pwotection_mode(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;

	/* Wait fow smc boot up */
	/* PHM_WAIT_INDIWECT_FIEWD_UNEQUAW(hwmgw, SMC_IND,
		WCU_UC_EVENTS, boot_seq_done, 0); */

	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			SMC_SYSCON_WESET_CNTW, wst_weg, 1);

	wesuwt = smu7_upwoad_smu_fiwmwawe_image(hwmgw);
	if (wesuwt)
		wetuwn wesuwt;

	/* Cweaw status */
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			ixSMU_STATUS, 0);

	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			SMC_SYSCON_CWOCK_CNTW_0, ck_disabwe, 0);

	/* De-assewt weset */
	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			SMC_SYSCON_WESET_CNTW, wst_weg, 0);

	/* Wait fow WOM fiwmwawe to initiawize intewwupt hendwew */
	/*SMUM_WAIT_VFPF_INDIWECT_WEGISTEW(hwmgw, SMC_IND,
			SMC_INTW_CNTW_MASK_0, 0x10040, 0xFFFFFFFF); */

	/* Set SMU Auto Stawt */
	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			SMU_INPUT_DATA, AUTO_STAWT, 1);

	/* Cweaw fiwmwawe intewwupt enabwe fwag */
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			ixFIWMWAWE_FWAGS, 0);

	PHM_WAIT_VFPF_INDIWECT_FIEWD(hwmgw, SMC_IND, WCU_UC_EVENTS,
			INTEWWUPTS_ENABWED, 1);

	smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_Test, 0x20000, NUWW);

	/* Wait fow done bit to be set */
	PHM_WAIT_VFPF_INDIWECT_FIEWD_UNEQUAW(hwmgw, SMC_IND,
			SMU_STATUS, SMU_DONE, 0);

	/* Check pass/faiwed indicatow */
	if (PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			SMU_STATUS, SMU_PASS) != 1) {
		PP_ASSEWT_WITH_CODE(fawse,
				"SMU Fiwmwawe stawt faiwed!", wetuwn -1);
	}

	/* Wait fow fiwmwawe to initiawize */
	PHM_WAIT_VFPF_INDIWECT_FIEWD(hwmgw, SMC_IND,
			FIWMWAWE_FWAGS, INTEWWUPTS_ENABWED, 1);

	wetuwn wesuwt;
}

static int fiji_stawt_smu_in_non_pwotection_mode(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;

	/* wait fow smc boot up */
	PHM_WAIT_VFPF_INDIWECT_FIEWD_UNEQUAW(hwmgw, SMC_IND,
			WCU_UC_EVENTS, boot_seq_done, 0);

	/* Cweaw fiwmwawe intewwupt enabwe fwag */
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			ixFIWMWAWE_FWAGS, 0);

	/* Assewt weset */
	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			SMC_SYSCON_WESET_CNTW, wst_weg, 1);

	wesuwt = smu7_upwoad_smu_fiwmwawe_image(hwmgw);
	if (wesuwt)
		wetuwn wesuwt;

	/* Set smc instwuct stawt point at 0x0 */
	smu7_pwogwam_jump_on_stawt(hwmgw);

	/* Enabwe cwock */
	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			SMC_SYSCON_CWOCK_CNTW_0, ck_disabwe, 0);

	/* De-assewt weset */
	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			SMC_SYSCON_WESET_CNTW, wst_weg, 0);

	/* Wait fow fiwmwawe to initiawize */
	PHM_WAIT_VFPF_INDIWECT_FIEWD(hwmgw, SMC_IND,
			FIWMWAWE_FWAGS, INTEWWUPTS_ENABWED, 1);

	wetuwn wesuwt;
}

static int fiji_stawt_avfs_btc(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;
	stwuct smu7_smumgw *smu_data = (stwuct smu7_smumgw *)(hwmgw->smu_backend);

	if (0 != smu_data->avfs_btc_pawam) {
		if (0 != smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_PewfowmBtc, smu_data->avfs_btc_pawam,
				NUWW)) {
			pw_info("[AVFS][Fiji_PewfowmBtc] PewfowmBTC SMU msg faiwed");
			wesuwt = -EINVAW;
		}
	}
	/* Soft-Weset to weset the engine befowe woading uCode */
	 /* hawt */
	cgs_wwite_wegistew(hwmgw->device, mmCP_MEC_CNTW, 0x50000000);
	/* weset evewything */
	cgs_wwite_wegistew(hwmgw->device, mmGWBM_SOFT_WESET, 0xffffffff);
	/* cweaw weset */
	cgs_wwite_wegistew(hwmgw->device, mmGWBM_SOFT_WESET, 0);

	wetuwn wesuwt;
}

static int fiji_setup_gwaphics_wevew_stwuctuwe(stwuct pp_hwmgw *hwmgw)
{
	int32_t vw_config;
	uint32_t tabwe_stawt;
	uint32_t wevew_addw, vw_config_addw;
	uint32_t wevew_size = sizeof(avfs_gwaphics_wevew);

	PP_ASSEWT_WITH_CODE(0 == smu7_wead_smc_swam_dwowd(hwmgw,
			SMU7_FIWMWAWE_HEADEW_WOCATION +
			offsetof(SMU73_Fiwmwawe_Headew, DpmTabwe),
			&tabwe_stawt, 0x40000),
			"[AVFS][Fiji_SetupGfxWvwStwuct] SMU couwd not "
			"communicate stawting addwess of DPM tabwe",
			wetuwn -1;);

	/* Defauwt vawue fow vw_config =
	 * VW_MEWGED_WITH_VDDC + VW_STATIC_VOWTAGE(VDDCI) */
	vw_config = 0x01000500;   /* Weaw vawue:0x50001 */

	vw_config_addw = tabwe_stawt +
			offsetof(SMU73_Discwete_DpmTabwe, VWConfig);

	PP_ASSEWT_WITH_CODE(0 == smu7_copy_bytes_to_smc(hwmgw, vw_config_addw,
			(uint8_t *)&vw_config, sizeof(int32_t), 0x40000),
			"[AVFS][Fiji_SetupGfxWvwStwuct] Pwobwems copying "
			"vw_config vawue ovew to SMC",
			wetuwn -1;);

	wevew_addw = tabwe_stawt + offsetof(SMU73_Discwete_DpmTabwe, GwaphicsWevew);

	PP_ASSEWT_WITH_CODE(0 == smu7_copy_bytes_to_smc(hwmgw, wevew_addw,
			(uint8_t *)(&avfs_gwaphics_wevew), wevew_size, 0x40000),
			"[AVFS][Fiji_SetupGfxWvwStwuct] Copying of DPM tabwe faiwed!",
			wetuwn -1;);

	wetuwn 0;
}

static int fiji_avfs_event_mgw(stwuct pp_hwmgw *hwmgw)
{
	if (!hwmgw->avfs_suppowted)
		wetuwn 0;

	PP_ASSEWT_WITH_CODE(0 == fiji_setup_gwaphics_wevew_stwuctuwe(hwmgw),
			"[AVFS][fiji_avfs_event_mgw] Couwd not Copy Gwaphics Wevew"
			" tabwe ovew to SMU",
			wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(0 == smu7_setup_pww_viwus(hwmgw),
			"[AVFS][fiji_avfs_event_mgw] Couwd not setup "
			"Pww Viwus fow AVFS ",
			wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(0 == fiji_stawt_avfs_btc(hwmgw),
			"[AVFS][fiji_avfs_event_mgw] Faiwuwe at "
			"fiji_stawt_avfs_btc. AVFS Disabwed",
			wetuwn -EINVAW);

	wetuwn 0;
}

static int fiji_stawt_smu(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;
	stwuct fiji_smumgw *pwiv = (stwuct fiji_smumgw *)(hwmgw->smu_backend);

	/* Onwy stawt SMC if SMC WAM is not wunning */
	if (!smu7_is_smc_wam_wunning(hwmgw) && hwmgw->not_vf) {
		/* Check if SMU is wunning in pwotected mode */
		if (0 == PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device,
				CGS_IND_WEG__SMC,
				SMU_FIWMWAWE, SMU_MODE)) {
			wesuwt = fiji_stawt_smu_in_non_pwotection_mode(hwmgw);
			if (wesuwt)
				wetuwn wesuwt;
		} ewse {
			wesuwt = fiji_stawt_smu_in_pwotection_mode(hwmgw);
			if (wesuwt)
				wetuwn wesuwt;
		}
		if (fiji_avfs_event_mgw(hwmgw))
			hwmgw->avfs_suppowted = fawse;
	}

	/* Setup SoftWegsStawt hewe fow wegistew wookup in case
	 * DummyBackEnd is used and PwocessFiwmwaweHeadew is not executed
	 */
	smu7_wead_smc_swam_dwowd(hwmgw,
			SMU7_FIWMWAWE_HEADEW_WOCATION +
			offsetof(SMU73_Fiwmwawe_Headew, SoftWegistews),
			&(pwiv->smu7_data.soft_wegs_stawt), 0x40000);

	wesuwt = smu7_wequest_smu_woad_fw(hwmgw);

	wetuwn wesuwt;
}

static boow fiji_is_hw_avfs_pwesent(stwuct pp_hwmgw *hwmgw)
{

	uint32_t efuse = 0;

	if (!hwmgw->not_vf)
		wetuwn fawse;

	if (!atomctww_wead_efuse(hwmgw, AVFS_EN_WSB, AVFS_EN_MSB,
			&efuse)) {
		if (efuse)
			wetuwn twue;
	}
	wetuwn fawse;
}

static int fiji_smu_init(stwuct pp_hwmgw *hwmgw)
{
	stwuct fiji_smumgw *fiji_pwiv;

	fiji_pwiv = kzawwoc(sizeof(stwuct fiji_smumgw), GFP_KEWNEW);

	if (fiji_pwiv == NUWW)
		wetuwn -ENOMEM;

	hwmgw->smu_backend = fiji_pwiv;

	if (smu7_init(hwmgw)) {
		kfwee(fiji_pwiv);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int fiji_get_dependency_vowt_by_cwk(stwuct pp_hwmgw *hwmgw,
		stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_tabwe,
		uint32_t cwock, uint32_t *vowtage, uint32_t *mvdd)
{
	uint32_t i;
	uint16_t vddci;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	*vowtage = *mvdd = 0;


	/* cwock - vowtage dependency tabwe is empty tabwe */
	if (dep_tabwe->count == 0)
		wetuwn -EINVAW;

	fow (i = 0; i < dep_tabwe->count; i++) {
		/* find fiwst scwk biggew than wequest */
		if (dep_tabwe->entwies[i].cwk >= cwock) {
			*vowtage |= (dep_tabwe->entwies[i].vddc *
					VOWTAGE_SCAWE) << VDDC_SHIFT;
			if (SMU7_VOWTAGE_CONTWOW_NONE == data->vddci_contwow)
				*vowtage |= (data->vbios_boot_state.vddci_bootup_vawue *
						VOWTAGE_SCAWE) << VDDCI_SHIFT;
			ewse if (dep_tabwe->entwies[i].vddci)
				*vowtage |= (dep_tabwe->entwies[i].vddci *
						VOWTAGE_SCAWE) << VDDCI_SHIFT;
			ewse {
				vddci = phm_find_cwosest_vddci(&(data->vddci_vowtage_tabwe),
						(dep_tabwe->entwies[i].vddc -
								VDDC_VDDCI_DEWTA));
				*vowtage |= (vddci * VOWTAGE_SCAWE) << VDDCI_SHIFT;
			}

			if (SMU7_VOWTAGE_CONTWOW_NONE == data->mvdd_contwow)
				*mvdd = data->vbios_boot_state.mvdd_bootup_vawue *
					VOWTAGE_SCAWE;
			ewse if (dep_tabwe->entwies[i].mvdd)
				*mvdd = (uint32_t) dep_tabwe->entwies[i].mvdd *
					VOWTAGE_SCAWE;

			*vowtage |= 1 << PHASES_SHIFT;
			wetuwn 0;
		}
	}

	/* scwk is biggew than max scwk in the dependence tabwe */
	*vowtage |= (dep_tabwe->entwies[i - 1].vddc * VOWTAGE_SCAWE) << VDDC_SHIFT;

	if (SMU7_VOWTAGE_CONTWOW_NONE == data->vddci_contwow)
		*vowtage |= (data->vbios_boot_state.vddci_bootup_vawue *
				VOWTAGE_SCAWE) << VDDCI_SHIFT;
	ewse if (dep_tabwe->entwies[i-1].vddci) {
		vddci = phm_find_cwosest_vddci(&(data->vddci_vowtage_tabwe),
				(dep_tabwe->entwies[i].vddc -
						VDDC_VDDCI_DEWTA));
		*vowtage |= (vddci * VOWTAGE_SCAWE) << VDDCI_SHIFT;
	}

	if (SMU7_VOWTAGE_CONTWOW_NONE == data->mvdd_contwow)
		*mvdd = data->vbios_boot_state.mvdd_bootup_vawue * VOWTAGE_SCAWE;
	ewse if (dep_tabwe->entwies[i].mvdd)
		*mvdd = (uint32_t) dep_tabwe->entwies[i - 1].mvdd * VOWTAGE_SCAWE;

	wetuwn 0;
}


static uint16_t scawe_fan_gain_settings(uint16_t waw_setting)
{
	uint32_t tmp;
	tmp = waw_setting * 4096 / 100;
	wetuwn (uint16_t)tmp;
}

static void get_scw_sda_vawue(uint8_t wine, uint8_t *scw, uint8_t *sda)
{
	switch (wine) {
	case SMU7_I2CWineID_DDC1:
		*scw = SMU7_I2C_DDC1CWK;
		*sda = SMU7_I2C_DDC1DATA;
		bweak;
	case SMU7_I2CWineID_DDC2:
		*scw = SMU7_I2C_DDC2CWK;
		*sda = SMU7_I2C_DDC2DATA;
		bweak;
	case SMU7_I2CWineID_DDC3:
		*scw = SMU7_I2C_DDC3CWK;
		*sda = SMU7_I2C_DDC3DATA;
		bweak;
	case SMU7_I2CWineID_DDC4:
		*scw = SMU7_I2C_DDC4CWK;
		*sda = SMU7_I2C_DDC4DATA;
		bweak;
	case SMU7_I2CWineID_DDC5:
		*scw = SMU7_I2C_DDC5CWK;
		*sda = SMU7_I2C_DDC5DATA;
		bweak;
	case SMU7_I2CWineID_DDC6:
		*scw = SMU7_I2C_DDC6CWK;
		*sda = SMU7_I2C_DDC6DATA;
		bweak;
	case SMU7_I2CWineID_SCWSDA:
		*scw = SMU7_I2C_SCW;
		*sda = SMU7_I2C_SDA;
		bweak;
	case SMU7_I2CWineID_DDCVGA:
		*scw = SMU7_I2C_DDCVGACWK;
		*sda = SMU7_I2C_DDCVGADATA;
		bweak;
	defauwt:
		*scw = 0;
		*sda = 0;
		bweak;
	}
}

static void fiji_initiawize_powew_tune_defauwts(stwuct pp_hwmgw *hwmgw)
{
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct  phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	if (tabwe_info &&
			tabwe_info->cac_dtp_tabwe->usPowewTuneDataSetID <= POWEWTUNE_DEFAUWT_SET_MAX &&
			tabwe_info->cac_dtp_tabwe->usPowewTuneDataSetID)
		smu_data->powew_tune_defauwts =
				&fiji_powew_tune_data_set_awway
				[tabwe_info->cac_dtp_tabwe->usPowewTuneDataSetID - 1];
	ewse
		smu_data->powew_tune_defauwts = &fiji_powew_tune_data_set_awway[0];

}

static int fiji_popuwate_bapm_pawametews_in_dpm_tabwe(stwuct pp_hwmgw *hwmgw)
{

	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);
	const stwuct fiji_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;

	SMU73_Discwete_DpmTabwe  *dpm_tabwe = &(smu_data->smc_state_tabwe);

	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_cac_tdp_tabwe *cac_dtp_tabwe = tabwe_info->cac_dtp_tabwe;
	stwuct pp_advance_fan_contwow_pawametews *fan_tabwe =
			&hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews;
	uint8_t uc_scw, uc_sda;

	/* TDP numbew of fwaction bits awe changed fwom 8 to 7 fow Fiji
	 * as wequested by SMC team
	 */
	dpm_tabwe->DefauwtTdp = PP_HOST_TO_SMC_US(
			(uint16_t)(cac_dtp_tabwe->usTDP * 128));
	dpm_tabwe->TawgetTdp = PP_HOST_TO_SMC_US(
			(uint16_t)(cac_dtp_tabwe->usTDP * 128));

	PP_ASSEWT_WITH_CODE(cac_dtp_tabwe->usTawgetOpewatingTemp <= 255,
			"Tawget Opewating Temp is out of Wange!",
			);

	dpm_tabwe->GpuTjMax = (uint8_t)(cac_dtp_tabwe->usTawgetOpewatingTemp);
	dpm_tabwe->GpuTjHyst = 8;

	dpm_tabwe->DTEAmbientTempBase = defauwts->DTEAmbientTempBase;

	/* The fowwowing awe fow new Fiji Muwti-input fan/thewmaw contwow */
	dpm_tabwe->TempewatuweWimitEdge = PP_HOST_TO_SMC_US(
			cac_dtp_tabwe->usTawgetOpewatingTemp * 256);
	dpm_tabwe->TempewatuweWimitHotspot = PP_HOST_TO_SMC_US(
			cac_dtp_tabwe->usTempewatuweWimitHotspot * 256);
	dpm_tabwe->TempewatuweWimitWiquid1 = PP_HOST_TO_SMC_US(
			cac_dtp_tabwe->usTempewatuweWimitWiquid1 * 256);
	dpm_tabwe->TempewatuweWimitWiquid2 = PP_HOST_TO_SMC_US(
			cac_dtp_tabwe->usTempewatuweWimitWiquid2 * 256);
	dpm_tabwe->TempewatuweWimitVwVddc = PP_HOST_TO_SMC_US(
			cac_dtp_tabwe->usTempewatuweWimitVwVddc * 256);
	dpm_tabwe->TempewatuweWimitVwMvdd = PP_HOST_TO_SMC_US(
			cac_dtp_tabwe->usTempewatuweWimitVwMvdd * 256);
	dpm_tabwe->TempewatuweWimitPwx = PP_HOST_TO_SMC_US(
			cac_dtp_tabwe->usTempewatuweWimitPwx * 256);

	dpm_tabwe->FanGainEdge = PP_HOST_TO_SMC_US(
			scawe_fan_gain_settings(fan_tabwe->usFanGainEdge));
	dpm_tabwe->FanGainHotspot = PP_HOST_TO_SMC_US(
			scawe_fan_gain_settings(fan_tabwe->usFanGainHotspot));
	dpm_tabwe->FanGainWiquid = PP_HOST_TO_SMC_US(
			scawe_fan_gain_settings(fan_tabwe->usFanGainWiquid));
	dpm_tabwe->FanGainVwVddc = PP_HOST_TO_SMC_US(
			scawe_fan_gain_settings(fan_tabwe->usFanGainVwVddc));
	dpm_tabwe->FanGainVwMvdd = PP_HOST_TO_SMC_US(
			scawe_fan_gain_settings(fan_tabwe->usFanGainVwMvdd));
	dpm_tabwe->FanGainPwx = PP_HOST_TO_SMC_US(
			scawe_fan_gain_settings(fan_tabwe->usFanGainPwx));
	dpm_tabwe->FanGainHbm = PP_HOST_TO_SMC_US(
			scawe_fan_gain_settings(fan_tabwe->usFanGainHbm));

	dpm_tabwe->Wiquid1_I2C_addwess = cac_dtp_tabwe->ucWiquid1_I2C_addwess;
	dpm_tabwe->Wiquid2_I2C_addwess = cac_dtp_tabwe->ucWiquid2_I2C_addwess;
	dpm_tabwe->Vw_I2C_addwess = cac_dtp_tabwe->ucVw_I2C_addwess;
	dpm_tabwe->Pwx_I2C_addwess = cac_dtp_tabwe->ucPwx_I2C_addwess;

	get_scw_sda_vawue(cac_dtp_tabwe->ucWiquid_I2C_Wine, &uc_scw, &uc_sda);
	dpm_tabwe->Wiquid_I2C_WineSCW = uc_scw;
	dpm_tabwe->Wiquid_I2C_WineSDA = uc_sda;

	get_scw_sda_vawue(cac_dtp_tabwe->ucVw_I2C_Wine, &uc_scw, &uc_sda);
	dpm_tabwe->Vw_I2C_WineSCW = uc_scw;
	dpm_tabwe->Vw_I2C_WineSDA = uc_sda;

	get_scw_sda_vawue(cac_dtp_tabwe->ucPwx_I2C_Wine, &uc_scw, &uc_sda);
	dpm_tabwe->Pwx_I2C_WineSCW = uc_scw;
	dpm_tabwe->Pwx_I2C_WineSDA = uc_sda;

	wetuwn 0;
}


static int fiji_popuwate_svi_woad_wine(stwuct pp_hwmgw *hwmgw)
{
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);
	const stwuct fiji_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;

	smu_data->powew_tune_tabwe.SviWoadWineEn = defauwts->SviWoadWineEn;
	smu_data->powew_tune_tabwe.SviWoadWineVddC = defauwts->SviWoadWineVddC;
	smu_data->powew_tune_tabwe.SviWoadWineTwimVddC = 3;
	smu_data->powew_tune_tabwe.SviWoadWineOffsetVddC = 0;

	wetuwn 0;
}


static int fiji_popuwate_tdc_wimit(stwuct pp_hwmgw *hwmgw)
{
	uint16_t tdc_wimit;
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	const stwuct fiji_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;

	/* TDC numbew of fwaction bits awe changed fwom 8 to 7
	 * fow Fiji as wequested by SMC team
	 */
	tdc_wimit = (uint16_t)(tabwe_info->cac_dtp_tabwe->usTDC * 128);
	smu_data->powew_tune_tabwe.TDC_VDDC_PkgWimit =
			CONVEWT_FWOM_HOST_TO_SMC_US(tdc_wimit);
	smu_data->powew_tune_tabwe.TDC_VDDC_ThwottweWeweaseWimitPewc =
			defauwts->TDC_VDDC_ThwottweWeweaseWimitPewc;
	smu_data->powew_tune_tabwe.TDC_MAWt = defauwts->TDC_MAWt;

	wetuwn 0;
}

static int fiji_popuwate_dw8(stwuct pp_hwmgw *hwmgw, uint32_t fuse_tabwe_offset)
{
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);
	const stwuct fiji_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;
	uint32_t temp;

	if (smu7_wead_smc_swam_dwowd(hwmgw,
			fuse_tabwe_offset +
			offsetof(SMU73_Discwete_PmFuses, TdcWatewfawwCtw),
			(uint32_t *)&temp, SMC_WAM_END))
		PP_ASSEWT_WITH_CODE(fawse,
				"Attempt to wead PmFuses.DW6 (SviWoadWineEn) fwom SMC Faiwed!",
				wetuwn -EINVAW);
	ewse {
		smu_data->powew_tune_tabwe.TdcWatewfawwCtw = defauwts->TdcWatewfawwCtw;
		smu_data->powew_tune_tabwe.WPMWTempewatuweMin =
				(uint8_t)((temp >> 16) & 0xff);
		smu_data->powew_tune_tabwe.WPMWTempewatuweMax =
				(uint8_t)((temp >> 8) & 0xff);
		smu_data->powew_tune_tabwe.Wesewved = (uint8_t)(temp & 0xff);
	}
	wetuwn 0;
}

static int fiji_popuwate_tempewatuwe_scawew(stwuct pp_hwmgw *hwmgw)
{
	int i;
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);

	/* Cuwwentwy not used. Set aww to zewo. */
	fow (i = 0; i < 16; i++)
		smu_data->powew_tune_tabwe.WPMWTempewatuweScawew[i] = 0;

	wetuwn 0;
}

static int fiji_popuwate_fuzzy_fan(stwuct pp_hwmgw *hwmgw)
{
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);

	if ((hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.
			usFanOutputSensitivity & (1 << 15)) ||
			0 == hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.
			usFanOutputSensitivity)
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.
		usFanOutputSensitivity = hwmgw->thewmaw_contwowwew.
			advanceFanContwowPawametews.usDefauwtFanOutputSensitivity;

	smu_data->powew_tune_tabwe.FuzzyFan_PwmSetDewta =
			PP_HOST_TO_SMC_US(hwmgw->thewmaw_contwowwew.
					advanceFanContwowPawametews.usFanOutputSensitivity);
	wetuwn 0;
}

static int fiji_popuwate_gnb_wpmw(stwuct pp_hwmgw *hwmgw)
{
	int i;
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);

	/* Cuwwentwy not used. Set aww to zewo. */
	fow (i = 0; i < 16; i++)
		smu_data->powew_tune_tabwe.GnbWPMW[i] = 0;

	wetuwn 0;
}

static int fiji_popuwate_bapm_vddc_base_weakage_sidd(stwuct pp_hwmgw *hwmgw)
{
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	uint16_t HiSidd = smu_data->powew_tune_tabwe.BapmVddCBaseWeakageHiSidd;
	uint16_t WoSidd = smu_data->powew_tune_tabwe.BapmVddCBaseWeakageWoSidd;
	stwuct phm_cac_tdp_tabwe *cac_tabwe = tabwe_info->cac_dtp_tabwe;

	HiSidd = (uint16_t)(cac_tabwe->usHighCACWeakage / 100 * 256);
	WoSidd = (uint16_t)(cac_tabwe->usWowCACWeakage / 100 * 256);

	smu_data->powew_tune_tabwe.BapmVddCBaseWeakageHiSidd =
			CONVEWT_FWOM_HOST_TO_SMC_US(HiSidd);
	smu_data->powew_tune_tabwe.BapmVddCBaseWeakageWoSidd =
			CONVEWT_FWOM_HOST_TO_SMC_US(WoSidd);

	wetuwn 0;
}

static int fiji_popuwate_pm_fuses(stwuct pp_hwmgw *hwmgw)
{
	uint32_t pm_fuse_tabwe_offset;
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_PowewContainment)) {
		if (smu7_wead_smc_swam_dwowd(hwmgw,
				SMU7_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU73_Fiwmwawe_Headew, PmFuseTabwe),
				&pm_fuse_tabwe_offset, SMC_WAM_END))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to get pm_fuse_tabwe_offset Faiwed!",
					wetuwn -EINVAW);

		/* DW6 */
		if (fiji_popuwate_svi_woad_wine(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate SviWoadWine Faiwed!",
					wetuwn -EINVAW);
		/* DW7 */
		if (fiji_popuwate_tdc_wimit(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate TDCWimit Faiwed!", wetuwn -EINVAW);
		/* DW8 */
		if (fiji_popuwate_dw8(hwmgw, pm_fuse_tabwe_offset))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate TdcWatewfawwCtw, "
					"WPMWTempewatuwe Min and Max Faiwed!",
					wetuwn -EINVAW);

		/* DW9-DW12 */
		if (0 != fiji_popuwate_tempewatuwe_scawew(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate WPMWTempewatuweScawew Faiwed!",
					wetuwn -EINVAW);

		/* DW13-DW14 */
		if (fiji_popuwate_fuzzy_fan(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate Fuzzy Fan Contwow pawametews Faiwed!",
					wetuwn -EINVAW);

		/* DW15-DW18 */
		if (fiji_popuwate_gnb_wpmw(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate GnbWPMW Faiwed!",
					wetuwn -EINVAW);

		/* DW20 */
		if (fiji_popuwate_bapm_vddc_base_weakage_sidd(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate BapmVddCBaseWeakage Hi and Wo "
					"Sidd Faiwed!", wetuwn -EINVAW);

		if (smu7_copy_bytes_to_smc(hwmgw, pm_fuse_tabwe_offset,
				(uint8_t *)&smu_data->powew_tune_tabwe,
				sizeof(stwuct SMU73_Discwete_PmFuses), SMC_WAM_END))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to downwoad PmFuseTabwe Faiwed!",
					wetuwn -EINVAW);
	}
	wetuwn 0;
}

static int fiji_popuwate_cac_tabwe(stwuct pp_hwmgw *hwmgw,
		stwuct SMU73_Discwete_DpmTabwe *tabwe)
{
	uint32_t count;
	uint8_t index;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_vowtage_wookup_tabwe *wookup_tabwe =
			tabwe_info->vddc_wookup_tabwe;
	/* tabwes is awweady swapped, so in owdew to use the vawue fwom it,
	 * we need to swap it back.
	 * We awe popuwating vddc CAC data to BapmVddc tabwe
	 * in spwit and mewged mode
	 */

	fow (count = 0; count < wookup_tabwe->count; count++) {
		index = phm_get_vowtage_index(wookup_tabwe,
				data->vddc_vowtage_tabwe.entwies[count].vawue);
		tabwe->BapmVddcVidWoSidd[count] =
			convewt_to_vid(wookup_tabwe->entwies[index].us_cac_wow);
		tabwe->BapmVddcVidHiSidd[count] =
			convewt_to_vid(wookup_tabwe->entwies[index].us_cac_high);
	}

	wetuwn 0;
}

static int fiji_popuwate_smc_vowtage_tabwes(stwuct pp_hwmgw *hwmgw,
		stwuct SMU73_Discwete_DpmTabwe *tabwe)
{
	int wesuwt;

	wesuwt = fiji_popuwate_cac_tabwe(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"can not popuwate CAC vowtage tabwes to SMC",
			wetuwn -EINVAW);

	wetuwn 0;
}

static int fiji_popuwate_uwv_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct SMU73_Discwete_Uwv *state)
{
	int wesuwt = 0;

	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	state->CcPwwDynWm = 0;
	state->CcPwwDynWm1 = 0;

	state->VddcOffset = (uint16_t) tabwe_info->us_uwv_vowtage_offset;
	state->VddcOffsetVid = (uint8_t)(tabwe_info->us_uwv_vowtage_offset *
			VOWTAGE_VID_OFFSET_SCAWE2 / VOWTAGE_VID_OFFSET_SCAWE1);

	state->VddcPhase = 1;

	if (!wesuwt) {
		CONVEWT_FWOM_HOST_TO_SMC_UW(state->CcPwwDynWm);
		CONVEWT_FWOM_HOST_TO_SMC_UW(state->CcPwwDynWm1);
		CONVEWT_FWOM_HOST_TO_SMC_US(state->VddcOffset);
	}
	wetuwn wesuwt;
}

static int fiji_popuwate_uwv_state(stwuct pp_hwmgw *hwmgw,
		stwuct SMU73_Discwete_DpmTabwe *tabwe)
{
	wetuwn fiji_popuwate_uwv_wevew(hwmgw, &tabwe->Uwv);
}

static int fiji_popuwate_smc_wink_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct SMU73_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_dpm_tabwe *dpm_tabwe = &data->dpm_tabwe;
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);
	int i;

	/* Index (dpm_tabwe->pcie_speed_tabwe.count)
	 * is wesewved fow PCIE boot wevew. */
	fow (i = 0; i <= dpm_tabwe->pcie_speed_tabwe.count; i++) {
		tabwe->WinkWevew[i].PcieGenSpeed  =
				(uint8_t)dpm_tabwe->pcie_speed_tabwe.dpm_wevews[i].vawue;
		tabwe->WinkWevew[i].PcieWaneCount = (uint8_t)encode_pcie_wane_width(
				dpm_tabwe->pcie_speed_tabwe.dpm_wevews[i].pawam1);
		tabwe->WinkWevew[i].EnabwedFowActivity = 1;
		tabwe->WinkWevew[i].SPC = (uint8_t)(data->pcie_spc_cap & 0xff);
		tabwe->WinkWevew[i].DownThweshowd = PP_HOST_TO_SMC_UW(5);
		tabwe->WinkWevew[i].UpThweshowd = PP_HOST_TO_SMC_UW(30);
	}

	smu_data->smc_state_tabwe.WinkWevewCount =
			(uint8_t)dpm_tabwe->pcie_speed_tabwe.count;
	data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask =
			phm_get_dpm_wevew_enabwe_mask_vawue(&dpm_tabwe->pcie_speed_tabwe);

	wetuwn 0;
}

static int fiji_cawcuwate_scwk_pawams(stwuct pp_hwmgw *hwmgw,
		uint32_t cwock, stwuct SMU73_Discwete_GwaphicsWevew *scwk)
{
	const stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct pp_atomctww_cwock_dividews_vi dividews;
	uint32_t spww_func_cntw            = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW;
	uint32_t spww_func_cntw_3          = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW_3;
	uint32_t spww_func_cntw_4          = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW_4;
	uint32_t cg_spww_spwead_spectwum   = data->cwock_wegistews.vCG_SPWW_SPWEAD_SPECTWUM;
	uint32_t cg_spww_spwead_spectwum_2 = data->cwock_wegistews.vCG_SPWW_SPWEAD_SPECTWUM_2;
	uint32_t wef_cwock;
	uint32_t wef_dividew;
	uint32_t fbdiv;
	int wesuwt;

	/* get the engine cwock dividews fow this cwock vawue */
	wesuwt = atomctww_get_engine_pww_dividews_vi(hwmgw, cwock,  &dividews);

	PP_ASSEWT_WITH_CODE(wesuwt == 0,
			"Ewwow wetwieving Engine Cwock dividews fwom VBIOS.",
			wetuwn wesuwt);

	/* To get FBDIV we need to muwtipwy this by 16384 and divide it by Fwef. */
	wef_cwock = atomctww_get_wefewence_cwock(hwmgw);
	wef_dividew = 1 + dividews.uc_pww_wef_div;

	/* wow 14 bits is fwaction and high 12 bits is dividew */
	fbdiv = dividews.uw_fb_div.uw_fb_dividew & 0x3FFFFFF;

	/* SPWW_FUNC_CNTW setup */
	spww_func_cntw = PHM_SET_FIEWD(spww_func_cntw, CG_SPWW_FUNC_CNTW,
			SPWW_WEF_DIV, dividews.uc_pww_wef_div);
	spww_func_cntw = PHM_SET_FIEWD(spww_func_cntw, CG_SPWW_FUNC_CNTW,
			SPWW_PDIV_A,  dividews.uc_pww_post_div);

	/* SPWW_FUNC_CNTW_3 setup*/
	spww_func_cntw_3 = PHM_SET_FIEWD(spww_func_cntw_3, CG_SPWW_FUNC_CNTW_3,
			SPWW_FB_DIV, fbdiv);

	/* set to use fwactionaw accumuwation*/
	spww_func_cntw_3 = PHM_SET_FIEWD(spww_func_cntw_3, CG_SPWW_FUNC_CNTW_3,
			SPWW_DITHEN, 1);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_EngineSpweadSpectwumSuppowt)) {
		stwuct pp_atomctww_intewnaw_ss_info ssInfo;

		uint32_t vco_fweq = cwock * dividews.uc_pww_post_div;
		if (!atomctww_get_engine_cwock_spwead_spectwum(hwmgw,
				vco_fweq, &ssInfo)) {
			/*
			 * ss_info.speed_spectwum_pewcentage -- in unit of 0.01%
			 * ss_info.speed_spectwum_wate -- in unit of khz
			 *
			 * cwks = wefewence_cwock * 10 / (WEFDIV + 1) / speed_spectwum_wate / 2
			 */
			uint32_t cwk_s = wef_cwock * 5 /
					(wef_dividew * ssInfo.speed_spectwum_wate);
			/* cwkv = 2 * D * fbdiv / NS */
			uint32_t cwk_v = 4 * ssInfo.speed_spectwum_pewcentage *
					fbdiv / (cwk_s * 10000);

			cg_spww_spwead_spectwum = PHM_SET_FIEWD(cg_spww_spwead_spectwum,
					CG_SPWW_SPWEAD_SPECTWUM, CWKS, cwk_s);
			cg_spww_spwead_spectwum = PHM_SET_FIEWD(cg_spww_spwead_spectwum,
					CG_SPWW_SPWEAD_SPECTWUM, SSEN, 1);
			cg_spww_spwead_spectwum_2 = PHM_SET_FIEWD(cg_spww_spwead_spectwum_2,
					CG_SPWW_SPWEAD_SPECTWUM_2, CWKV, cwk_v);
		}
	}

	scwk->ScwkFwequency        = cwock;
	scwk->CgSpwwFuncCntw3      = spww_func_cntw_3;
	scwk->CgSpwwFuncCntw4      = spww_func_cntw_4;
	scwk->SpwwSpweadSpectwum   = cg_spww_spwead_spectwum;
	scwk->SpwwSpweadSpectwum2  = cg_spww_spwead_spectwum_2;
	scwk->ScwkDid              = (uint8_t)dividews.pww_post_dividew;

	wetuwn 0;
}

static int fiji_popuwate_singwe_gwaphic_wevew(stwuct pp_hwmgw *hwmgw,
		uint32_t cwock, stwuct SMU73_Discwete_GwaphicsWevew *wevew)
{
	int wesuwt;
	/* PP_Cwocks minCwocks; */
	uint32_t mvdd;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_tabwe = NUWW;

	wesuwt = fiji_cawcuwate_scwk_pawams(hwmgw, cwock, wevew);

	if (hwmgw->od_enabwed)
		vdd_dep_tabwe = (phm_ppt_v1_cwock_vowtage_dependency_tabwe *)&data->odn_dpm_tabwe.vdd_dependency_on_scwk;
	ewse
		vdd_dep_tabwe = tabwe_info->vdd_dep_on_scwk;

	/* popuwate gwaphics wevews */
	wesuwt = fiji_get_dependency_vowt_by_cwk(hwmgw,
			vdd_dep_tabwe, cwock,
			(uint32_t *)(&wevew->MinVowtage), &mvdd);
	PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"can not find VDDC vowtage vawue fow "
			"VDDC engine cwock dependency tabwe",
			wetuwn wesuwt);

	wevew->ScwkFwequency = cwock;
	wevew->ActivityWevew = data->cuwwent_pwofiwe_setting.scwk_activity;
	wevew->CcPwwDynWm = 0;
	wevew->CcPwwDynWm1 = 0;
	wevew->EnabwedFowActivity = 0;
	wevew->EnabwedFowThwottwe = 1;
	wevew->UpHyst = data->cuwwent_pwofiwe_setting.scwk_up_hyst;
	wevew->DownHyst = data->cuwwent_pwofiwe_setting.scwk_down_hyst;
	wevew->VowtageDownHyst = 0;
	wevew->PowewThwottwe = 0;

	data->dispway_timing.min_cwock_in_sw = hwmgw->dispway_config->min_cowe_set_cwock_in_sw;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_ScwkDeepSweep))
		wevew->DeepSweepDivId = smu7_get_sweep_dividew_id_fwom_cwock(cwock,
								hwmgw->dispway_config->min_cowe_set_cwock_in_sw);


	/* Defauwt to swow, highest DPM wevew wiww be
	 * set to PPSMC_DISPWAY_WATEWMAWK_WOW watew.
	 */
	wevew->DispwayWatewmawk = PPSMC_DISPWAY_WATEWMAWK_WOW;

	CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->MinVowtage);
	CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->ScwkFwequency);
	CONVEWT_FWOM_HOST_TO_SMC_US(wevew->ActivityWevew);
	CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->CgSpwwFuncCntw3);
	CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->CgSpwwFuncCntw4);
	CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->SpwwSpweadSpectwum);
	CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->SpwwSpweadSpectwum2);
	CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->CcPwwDynWm);
	CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->CcPwwDynWm1);

	wetuwn 0;
}

static int fiji_popuwate_aww_gwaphic_wevews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);

	stwuct smu7_dpm_tabwe *dpm_tabwe = &data->dpm_tabwe;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_pcie_tabwe *pcie_tabwe = tabwe_info->pcie_tabwe;
	uint8_t pcie_entwy_cnt = (uint8_t) data->dpm_tabwe.pcie_speed_tabwe.count;
	int wesuwt = 0;
	uint32_t awway = smu_data->smu7_data.dpm_tabwe_stawt +
			offsetof(SMU73_Discwete_DpmTabwe, GwaphicsWevew);
	uint32_t awway_size = sizeof(stwuct SMU73_Discwete_GwaphicsWevew) *
			SMU73_MAX_WEVEWS_GWAPHICS;
	stwuct SMU73_Discwete_GwaphicsWevew *wevews =
			smu_data->smc_state_tabwe.GwaphicsWevew;
	uint32_t i, max_entwy;
	uint8_t hightest_pcie_wevew_enabwed = 0,
			wowest_pcie_wevew_enabwed = 0,
			mid_pcie_wevew_enabwed = 0,
			count = 0;

	fow (i = 0; i < dpm_tabwe->scwk_tabwe.count; i++) {
		wesuwt = fiji_popuwate_singwe_gwaphic_wevew(hwmgw,
				dpm_tabwe->scwk_tabwe.dpm_wevews[i].vawue,
				&wevews[i]);
		if (wesuwt)
			wetuwn wesuwt;

		/* Making suwe onwy DPM wevew 0-1 have Deep Sweep Div ID popuwated. */
		if (i > 1)
			wevews[i].DeepSweepDivId = 0;
	}

	/* Onwy enabwe wevew 0 fow now.*/
	wevews[0].EnabwedFowActivity = 1;

	/* set highest wevew watewmawk to high */
	wevews[dpm_tabwe->scwk_tabwe.count - 1].DispwayWatewmawk =
			PPSMC_DISPWAY_WATEWMAWK_HIGH;

	smu_data->smc_state_tabwe.GwaphicsDpmWevewCount =
			(uint8_t)dpm_tabwe->scwk_tabwe.count;
	data->dpm_wevew_enabwe_mask.scwk_dpm_enabwe_mask =
			phm_get_dpm_wevew_enabwe_mask_vawue(&dpm_tabwe->scwk_tabwe);

	if (pcie_tabwe != NUWW) {
		PP_ASSEWT_WITH_CODE((1 <= pcie_entwy_cnt),
				"Thewe must be 1 ow mowe PCIE wevews defined in PPTabwe.",
				wetuwn -EINVAW);
		max_entwy = pcie_entwy_cnt - 1;
		fow (i = 0; i < dpm_tabwe->scwk_tabwe.count; i++)
			wevews[i].pcieDpmWevew =
					(uint8_t) ((i < max_entwy) ? i : max_entwy);
	} ewse {
		whiwe (data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &&
				((data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &
						(1 << (hightest_pcie_wevew_enabwed + 1))) != 0))
			hightest_pcie_wevew_enabwed++;

		whiwe (data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &&
				((data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &
						(1 << wowest_pcie_wevew_enabwed)) == 0))
			wowest_pcie_wevew_enabwed++;

		whiwe ((count < hightest_pcie_wevew_enabwed) &&
				((data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &
						(1 << (wowest_pcie_wevew_enabwed + 1 + count))) == 0))
			count++;

		mid_pcie_wevew_enabwed = (wowest_pcie_wevew_enabwed + 1 + count) <
				hightest_pcie_wevew_enabwed ?
						(wowest_pcie_wevew_enabwed + 1 + count) :
						hightest_pcie_wevew_enabwed;

		/* set pcieDpmWevew to hightest_pcie_wevew_enabwed */
		fow (i = 2; i < dpm_tabwe->scwk_tabwe.count; i++)
			wevews[i].pcieDpmWevew = hightest_pcie_wevew_enabwed;

		/* set pcieDpmWevew to wowest_pcie_wevew_enabwed */
		wevews[0].pcieDpmWevew = wowest_pcie_wevew_enabwed;

		/* set pcieDpmWevew to mid_pcie_wevew_enabwed */
		wevews[1].pcieDpmWevew = mid_pcie_wevew_enabwed;
	}
	/* wevew count wiww send to smc once at init smc tabwe and nevew change */
	wesuwt = smu7_copy_bytes_to_smc(hwmgw, awway, (uint8_t *)wevews,
			(uint32_t)awway_size, SMC_WAM_END);

	wetuwn wesuwt;
}


/*
 * MCWK Fwequency Watio
 * SEQ_CG_WESP  Bit[31:24] - 0x0
 * Bit[27:24] \96 DDW3 Fwequency watio
 * 0x0 <= 100MHz,       450 < 0x8 <= 500MHz
 * 100 < 0x1 <= 150MHz,       500 < 0x9 <= 550MHz
 * 150 < 0x2 <= 200MHz,       550 < 0xA <= 600MHz
 * 200 < 0x3 <= 250MHz,       600 < 0xB <= 650MHz
 * 250 < 0x4 <= 300MHz,       650 < 0xC <= 700MHz
 * 300 < 0x5 <= 350MHz,       700 < 0xD <= 750MHz
 * 350 < 0x6 <= 400MHz,       750 < 0xE <= 800MHz
 * 400 < 0x7 <= 450MHz,       800 < 0xF
 */
static uint8_t fiji_get_mcwk_fwequency_watio(uint32_t mem_cwock)
{
	if (mem_cwock <= 10000)
		wetuwn 0x0;
	if (mem_cwock <= 15000)
		wetuwn 0x1;
	if (mem_cwock <= 20000)
		wetuwn 0x2;
	if (mem_cwock <= 25000)
		wetuwn 0x3;
	if (mem_cwock <= 30000)
		wetuwn 0x4;
	if (mem_cwock <= 35000)
		wetuwn 0x5;
	if (mem_cwock <= 40000)
		wetuwn 0x6;
	if (mem_cwock <= 45000)
		wetuwn 0x7;
	if (mem_cwock <= 50000)
		wetuwn 0x8;
	if (mem_cwock <= 55000)
		wetuwn 0x9;
	if (mem_cwock <= 60000)
		wetuwn 0xa;
	if (mem_cwock <= 65000)
		wetuwn 0xb;
	if (mem_cwock <= 70000)
		wetuwn 0xc;
	if (mem_cwock <= 75000)
		wetuwn 0xd;
	if (mem_cwock <= 80000)
		wetuwn 0xe;
	/* mem_cwock > 800MHz */
	wetuwn 0xf;
}

static int fiji_cawcuwate_mcwk_pawams(stwuct pp_hwmgw *hwmgw,
    uint32_t cwock, stwuct SMU73_Discwete_MemowyWevew *mcwk)
{
	stwuct pp_atomctww_memowy_cwock_pawam mem_pawam;
	int wesuwt;

	wesuwt = atomctww_get_memowy_pww_dividews_vi(hwmgw, cwock, &mem_pawam);
	PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"Faiwed to get Memowy PWW Dividews.",
			);

	/* Save the wesuwt data to outpupt memowy wevew stwuctuwe */
	mcwk->McwkFwequency   = cwock;
	mcwk->McwkDividew     = (uint8_t)mem_pawam.mpww_post_dividew;
	mcwk->FweqWange       = fiji_get_mcwk_fwequency_watio(cwock);

	wetuwn wesuwt;
}

static int fiji_popuwate_singwe_memowy_wevew(stwuct pp_hwmgw *hwmgw,
		uint32_t cwock, stwuct SMU73_Discwete_MemowyWevew *mem_wevew)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	int wesuwt = 0;
	uint32_t mcwk_stuttew_mode_thweshowd = 60000;
	phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_tabwe = NUWW;

	if (hwmgw->od_enabwed)
		vdd_dep_tabwe = (phm_ppt_v1_cwock_vowtage_dependency_tabwe *)&data->odn_dpm_tabwe.vdd_dependency_on_mcwk;
	ewse
		vdd_dep_tabwe = tabwe_info->vdd_dep_on_mcwk;

	if (vdd_dep_tabwe) {
		wesuwt = fiji_get_dependency_vowt_by_cwk(hwmgw,
				vdd_dep_tabwe, cwock,
				(uint32_t *)(&mem_wevew->MinVowtage), &mem_wevew->MinMvdd);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
				"can not find MinVddc vowtage vawue fwom memowy "
				"VDDC vowtage dependency tabwe", wetuwn wesuwt);
	}

	mem_wevew->EnabwedFowThwottwe = 1;
	mem_wevew->EnabwedFowActivity = 0;
	mem_wevew->UpHyst = data->cuwwent_pwofiwe_setting.mcwk_up_hyst;
	mem_wevew->DownHyst = data->cuwwent_pwofiwe_setting.mcwk_down_hyst;
	mem_wevew->VowtageDownHyst = 0;
	mem_wevew->ActivityWevew = data->cuwwent_pwofiwe_setting.mcwk_activity;
	mem_wevew->StuttewEnabwe = fawse;

	mem_wevew->DispwayWatewmawk = PPSMC_DISPWAY_WATEWMAWK_WOW;

	/* enabwe stuttew mode if aww the fowwow condition appwied
	 * PECI_GetNumbewOfActiveDispways(hwmgw->pPECI,
	 * &(data->DispwayTiming.numExistingDispways));
	 */
	data->dispway_timing.num_existing_dispways = hwmgw->dispway_config->num_dispway;
	data->dispway_timing.vwefwesh = hwmgw->dispway_config->vwefwesh;

	if (mcwk_stuttew_mode_thweshowd &&
		(cwock <= mcwk_stuttew_mode_thweshowd) &&
		(!data->is_uvd_enabwed) &&
		(PHM_WEAD_FIEWD(hwmgw->device, DPG_PIPE_STUTTEW_CONTWOW,
				STUTTEW_ENABWE) & 0x1))
		mem_wevew->StuttewEnabwe = twue;

	wesuwt = fiji_cawcuwate_mcwk_pawams(hwmgw, cwock, mem_wevew);
	if (!wesuwt) {
		CONVEWT_FWOM_HOST_TO_SMC_UW(mem_wevew->MinMvdd);
		CONVEWT_FWOM_HOST_TO_SMC_UW(mem_wevew->McwkFwequency);
		CONVEWT_FWOM_HOST_TO_SMC_US(mem_wevew->ActivityWevew);
		CONVEWT_FWOM_HOST_TO_SMC_UW(mem_wevew->MinVowtage);
	}
	wetuwn wesuwt;
}

static int fiji_popuwate_aww_memowy_wevews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);
	stwuct smu7_dpm_tabwe *dpm_tabwe = &data->dpm_tabwe;
	int wesuwt;
	/* popuwate MCWK dpm tabwe to SMU7 */
	uint32_t awway = smu_data->smu7_data.dpm_tabwe_stawt +
			offsetof(SMU73_Discwete_DpmTabwe, MemowyWevew);
	uint32_t awway_size = sizeof(SMU73_Discwete_MemowyWevew) *
			SMU73_MAX_WEVEWS_MEMOWY;
	stwuct SMU73_Discwete_MemowyWevew *wevews =
			smu_data->smc_state_tabwe.MemowyWevew;
	uint32_t i;

	fow (i = 0; i < dpm_tabwe->mcwk_tabwe.count; i++) {
		PP_ASSEWT_WITH_CODE((0 != dpm_tabwe->mcwk_tabwe.dpm_wevews[i].vawue),
				"can not popuwate memowy wevew as memowy cwock is zewo",
				wetuwn -EINVAW);
		wesuwt = fiji_popuwate_singwe_memowy_wevew(hwmgw,
				dpm_tabwe->mcwk_tabwe.dpm_wevews[i].vawue,
				&wevews[i]);
		if (wesuwt)
			wetuwn wesuwt;
	}

	/* Onwy enabwe wevew 0 fow now. */
	wevews[0].EnabwedFowActivity = 1;

	/* in owdew to pwevent MC activity fwom stuttew mode to push DPM up.
	 * the UVD change compwements this by putting the MCWK in
	 * a highew state by defauwt such that we awe not effected by
	 * up thweshowd ow and MCWK DPM watency.
	 */
	wevews[0].ActivityWevew = (uint16_t)data->mcwk_dpm0_activity_tawget;
	CONVEWT_FWOM_HOST_TO_SMC_US(wevews[0].ActivityWevew);

	smu_data->smc_state_tabwe.MemowyDpmWevewCount =
			(uint8_t)dpm_tabwe->mcwk_tabwe.count;
	data->dpm_wevew_enabwe_mask.mcwk_dpm_enabwe_mask =
			phm_get_dpm_wevew_enabwe_mask_vawue(&dpm_tabwe->mcwk_tabwe);
	/* set highest wevew watewmawk to high */
	wevews[dpm_tabwe->mcwk_tabwe.count - 1].DispwayWatewmawk =
			PPSMC_DISPWAY_WATEWMAWK_HIGH;

	/* wevew count wiww send to smc once at init smc tabwe and nevew change */
	wesuwt = smu7_copy_bytes_to_smc(hwmgw, awway, (uint8_t *)wevews,
			(uint32_t)awway_size, SMC_WAM_END);

	wetuwn wesuwt;
}

static int fiji_popuwate_mvdd_vawue(stwuct pp_hwmgw *hwmgw,
		uint32_t mcwk, SMIO_Pattewn *smio_pat)
{
	const stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	uint32_t i = 0;

	if (SMU7_VOWTAGE_CONTWOW_NONE != data->mvdd_contwow) {
		/* find mvdd vawue which cwock is mowe than wequest */
		fow (i = 0; i < tabwe_info->vdd_dep_on_mcwk->count; i++) {
			if (mcwk <= tabwe_info->vdd_dep_on_mcwk->entwies[i].cwk) {
				smio_pat->Vowtage = data->mvdd_vowtage_tabwe.entwies[i].vawue;
				bweak;
			}
		}
		PP_ASSEWT_WITH_CODE(i < tabwe_info->vdd_dep_on_mcwk->count,
				"MVDD Vowtage is outside the suppowted wange.",
				wetuwn -EINVAW);
	} ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static int fiji_popuwate_smc_acpi_wevew(stwuct pp_hwmgw *hwmgw,
		SMU73_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = 0;
	const stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct pp_atomctww_cwock_dividews_vi dividews;
	SMIO_Pattewn vow_wevew;
	uint32_t mvdd;
	uint16_t us_mvdd;
	uint32_t spww_func_cntw    = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW;
	uint32_t spww_func_cntw_2  = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW_2;

	tabwe->ACPIWevew.Fwags &= ~PPSMC_SWSTATE_FWAG_DC;

	if (!data->scwk_dpm_key_disabwed) {
		/* Get MinVowtage and Fwequency fwom DPM0,
		 * awweady convewted to SMC_UW */
		tabwe->ACPIWevew.ScwkFwequency =
				data->dpm_tabwe.scwk_tabwe.dpm_wevews[0].vawue;
		wesuwt = fiji_get_dependency_vowt_by_cwk(hwmgw,
				tabwe_info->vdd_dep_on_scwk,
				tabwe->ACPIWevew.ScwkFwequency,
				(uint32_t *)(&tabwe->ACPIWevew.MinVowtage), &mvdd);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
				"Cannot find ACPI VDDC vowtage vawue " \
				"in Cwock Dependency Tabwe",
				);
	} ewse {
		tabwe->ACPIWevew.ScwkFwequency =
				data->vbios_boot_state.scwk_bootup_vawue;
		tabwe->ACPIWevew.MinVowtage =
				data->vbios_boot_state.vddc_bootup_vawue * VOWTAGE_SCAWE;
	}

	/* get the engine cwock dividews fow this cwock vawue */
	wesuwt = atomctww_get_engine_pww_dividews_vi(hwmgw,
			tabwe->ACPIWevew.ScwkFwequency,  &dividews);
	PP_ASSEWT_WITH_CODE(wesuwt == 0,
			"Ewwow wetwieving Engine Cwock dividews fwom VBIOS.",
			wetuwn wesuwt);

	tabwe->ACPIWevew.ScwkDid = (uint8_t)dividews.pww_post_dividew;
	tabwe->ACPIWevew.DispwayWatewmawk = PPSMC_DISPWAY_WATEWMAWK_WOW;
	tabwe->ACPIWevew.DeepSweepDivId = 0;

	spww_func_cntw = PHM_SET_FIEWD(spww_func_cntw, CG_SPWW_FUNC_CNTW,
			SPWW_PWWON, 0);
	spww_func_cntw = PHM_SET_FIEWD(spww_func_cntw, CG_SPWW_FUNC_CNTW,
			SPWW_WESET, 1);
	spww_func_cntw_2 = PHM_SET_FIEWD(spww_func_cntw_2, CG_SPWW_FUNC_CNTW_2,
			SCWK_MUX_SEW, 4);

	tabwe->ACPIWevew.CgSpwwFuncCntw = spww_func_cntw;
	tabwe->ACPIWevew.CgSpwwFuncCntw2 = spww_func_cntw_2;
	tabwe->ACPIWevew.CgSpwwFuncCntw3 = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW_3;
	tabwe->ACPIWevew.CgSpwwFuncCntw4 = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW_4;
	tabwe->ACPIWevew.SpwwSpweadSpectwum = data->cwock_wegistews.vCG_SPWW_SPWEAD_SPECTWUM;
	tabwe->ACPIWevew.SpwwSpweadSpectwum2 = data->cwock_wegistews.vCG_SPWW_SPWEAD_SPECTWUM_2;
	tabwe->ACPIWevew.CcPwwDynWm = 0;
	tabwe->ACPIWevew.CcPwwDynWm1 = 0;

	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.Fwags);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.ScwkFwequency);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.MinVowtage);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CgSpwwFuncCntw);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CgSpwwFuncCntw2);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CgSpwwFuncCntw3);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CgSpwwFuncCntw4);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.SpwwSpweadSpectwum);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.SpwwSpweadSpectwum2);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CcPwwDynWm);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CcPwwDynWm1);

	if (!data->mcwk_dpm_key_disabwed) {
		/* Get MinVowtage and Fwequency fwom DPM0, awweady convewted to SMC_UW */
		tabwe->MemowyACPIWevew.McwkFwequency =
				data->dpm_tabwe.mcwk_tabwe.dpm_wevews[0].vawue;
		wesuwt = fiji_get_dependency_vowt_by_cwk(hwmgw,
				tabwe_info->vdd_dep_on_mcwk,
				tabwe->MemowyACPIWevew.McwkFwequency,
			(uint32_t *)(&tabwe->MemowyACPIWevew.MinVowtage), &mvdd);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
				"Cannot find ACPI VDDCI vowtage vawue in Cwock Dependency Tabwe",
				);
	} ewse {
		tabwe->MemowyACPIWevew.McwkFwequency =
				data->vbios_boot_state.mcwk_bootup_vawue;
		tabwe->MemowyACPIWevew.MinVowtage =
				data->vbios_boot_state.vddci_bootup_vawue * VOWTAGE_SCAWE;
	}

	us_mvdd = 0;
	if ((SMU7_VOWTAGE_CONTWOW_NONE == data->mvdd_contwow) ||
			(data->mcwk_dpm_key_disabwed))
		us_mvdd = data->vbios_boot_state.mvdd_bootup_vawue;
	ewse {
		if (!fiji_popuwate_mvdd_vawue(hwmgw,
				data->dpm_tabwe.mcwk_tabwe.dpm_wevews[0].vawue,
				&vow_wevew))
			us_mvdd = vow_wevew.Vowtage;
	}

	tabwe->MemowyACPIWevew.MinMvdd =
			PP_HOST_TO_SMC_UW(us_mvdd * VOWTAGE_SCAWE);

	tabwe->MemowyACPIWevew.EnabwedFowThwottwe = 0;
	tabwe->MemowyACPIWevew.EnabwedFowActivity = 0;
	tabwe->MemowyACPIWevew.UpHyst = 0;
	tabwe->MemowyACPIWevew.DownHyst = 100;
	tabwe->MemowyACPIWevew.VowtageDownHyst = 0;
	tabwe->MemowyACPIWevew.ActivityWevew =
			PP_HOST_TO_SMC_US(data->cuwwent_pwofiwe_setting.mcwk_activity);

	tabwe->MemowyACPIWevew.StuttewEnabwe = fawse;
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->MemowyACPIWevew.McwkFwequency);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->MemowyACPIWevew.MinVowtage);

	wetuwn wesuwt;
}

static int fiji_popuwate_smc_vce_wevew(stwuct pp_hwmgw *hwmgw,
		SMU73_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = -EINVAW;
	uint8_t count;
	stwuct pp_atomctww_cwock_dividews_vi dividews;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_mm_cwock_vowtage_dependency_tabwe *mm_tabwe =
			tabwe_info->mm_dep_tabwe;

	tabwe->VceWevewCount = (uint8_t)(mm_tabwe->count);
	tabwe->VceBootWevew = 0;

	fow (count = 0; count < tabwe->VceWevewCount; count++) {
		tabwe->VceWevew[count].Fwequency = mm_tabwe->entwies[count].ecwk;
		tabwe->VceWevew[count].MinVowtage = 0;
		tabwe->VceWevew[count].MinVowtage |=
				(mm_tabwe->entwies[count].vddc * VOWTAGE_SCAWE) << VDDC_SHIFT;
		tabwe->VceWevew[count].MinVowtage |=
				((mm_tabwe->entwies[count].vddc - VDDC_VDDCI_DEWTA) *
						VOWTAGE_SCAWE) << VDDCI_SHIFT;
		tabwe->VceWevew[count].MinVowtage |= 1 << PHASES_SHIFT;

		/*wetwieve dividew vawue fow VBIOS */
		wesuwt = atomctww_get_dfs_pww_dividews_vi(hwmgw,
				tabwe->VceWevew[count].Fwequency, &dividews);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
				"can not find divide id fow VCE engine cwock",
				wetuwn wesuwt);

		tabwe->VceWevew[count].Dividew = (uint8_t)dividews.pww_post_dividew;

		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->VceWevew[count].Fwequency);
		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->VceWevew[count].MinVowtage);
	}
	wetuwn wesuwt;
}

static int fiji_popuwate_smc_acp_wevew(stwuct pp_hwmgw *hwmgw,
		SMU73_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = -EINVAW;
	uint8_t count;
	stwuct pp_atomctww_cwock_dividews_vi dividews;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_mm_cwock_vowtage_dependency_tabwe *mm_tabwe =
			tabwe_info->mm_dep_tabwe;

	tabwe->AcpWevewCount = (uint8_t)(mm_tabwe->count);
	tabwe->AcpBootWevew = 0;

	fow (count = 0; count < tabwe->AcpWevewCount; count++) {
		tabwe->AcpWevew[count].Fwequency = mm_tabwe->entwies[count].acwk;
		tabwe->AcpWevew[count].MinVowtage |= (mm_tabwe->entwies[count].vddc *
				VOWTAGE_SCAWE) << VDDC_SHIFT;
		tabwe->AcpWevew[count].MinVowtage |= ((mm_tabwe->entwies[count].vddc -
				VDDC_VDDCI_DEWTA) * VOWTAGE_SCAWE) << VDDCI_SHIFT;
		tabwe->AcpWevew[count].MinVowtage |= 1 << PHASES_SHIFT;

		/* wetwieve dividew vawue fow VBIOS */
		wesuwt = atomctww_get_dfs_pww_dividews_vi(hwmgw,
				tabwe->AcpWevew[count].Fwequency, &dividews);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
				"can not find divide id fow engine cwock", wetuwn wesuwt);

		tabwe->AcpWevew[count].Dividew = (uint8_t)dividews.pww_post_dividew;

		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->AcpWevew[count].Fwequency);
		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->AcpWevew[count].MinVowtage);
	}
	wetuwn wesuwt;
}

static int fiji_popuwate_memowy_timing_pawametews(stwuct pp_hwmgw *hwmgw,
		int32_t eng_cwock, int32_t mem_cwock,
		stwuct SMU73_Discwete_MCAwbDwamTimingTabweEntwy *awb_wegs)
{
	uint32_t dwam_timing;
	uint32_t dwam_timing2;
	uint32_t buwstTime;
	UWONG twwds, twwdw;
	int wesuwt;

	wesuwt = atomctww_set_engine_dwam_timings_wv770(hwmgw,
			eng_cwock, mem_cwock);
	PP_ASSEWT_WITH_CODE(wesuwt == 0,
			"Ewwow cawwing VBIOS to set DWAM_TIMING.", wetuwn wesuwt);

	dwam_timing = cgs_wead_wegistew(hwmgw->device, mmMC_AWB_DWAM_TIMING);
	dwam_timing2 = cgs_wead_wegistew(hwmgw->device, mmMC_AWB_DWAM_TIMING2);
	buwstTime = cgs_wead_wegistew(hwmgw->device, mmMC_AWB_BUWST_TIME);

	twwds = PHM_GET_FIEWD(buwstTime, MC_AWB_BUWST_TIME, TWWDS0);
	twwdw = PHM_GET_FIEWD(buwstTime, MC_AWB_BUWST_TIME, TWWDW0);

	awb_wegs->McAwbDwamTiming  = PP_HOST_TO_SMC_UW(dwam_timing);
	awb_wegs->McAwbDwamTiming2 = PP_HOST_TO_SMC_UW(dwam_timing2);
	awb_wegs->McAwbBuwstTime   = (uint8_t)buwstTime;
	awb_wegs->TWWDS            = (uint8_t)twwds;
	awb_wegs->TWWDW            = (uint8_t)twwdw;

	wetuwn 0;
}

static int fiji_pwogwam_memowy_timing_pawametews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);
	stwuct SMU73_Discwete_MCAwbDwamTimingTabwe awb_wegs;
	uint32_t i, j;
	int wesuwt = 0;

	fow (i = 0; i < data->dpm_tabwe.scwk_tabwe.count; i++) {
		fow (j = 0; j < data->dpm_tabwe.mcwk_tabwe.count; j++) {
			wesuwt = fiji_popuwate_memowy_timing_pawametews(hwmgw,
					data->dpm_tabwe.scwk_tabwe.dpm_wevews[i].vawue,
					data->dpm_tabwe.mcwk_tabwe.dpm_wevews[j].vawue,
					&awb_wegs.entwies[i][j]);
			if (wesuwt)
				bweak;
		}
	}

	if (!wesuwt)
		wesuwt = smu7_copy_bytes_to_smc(
				hwmgw,
				smu_data->smu7_data.awb_tabwe_stawt,
				(uint8_t *)&awb_wegs,
				sizeof(SMU73_Discwete_MCAwbDwamTimingTabwe),
				SMC_WAM_END);
	wetuwn wesuwt;
}

static int fiji_popuwate_smc_uvd_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct SMU73_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = -EINVAW;
	uint8_t count;
	stwuct pp_atomctww_cwock_dividews_vi dividews;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_mm_cwock_vowtage_dependency_tabwe *mm_tabwe =
			tabwe_info->mm_dep_tabwe;

	tabwe->UvdWevewCount = (uint8_t)(mm_tabwe->count);
	tabwe->UvdBootWevew = 0;

	fow (count = 0; count < tabwe->UvdWevewCount; count++) {
		tabwe->UvdWevew[count].MinVowtage = 0;
		tabwe->UvdWevew[count].VcwkFwequency = mm_tabwe->entwies[count].vcwk;
		tabwe->UvdWevew[count].DcwkFwequency = mm_tabwe->entwies[count].dcwk;
		tabwe->UvdWevew[count].MinVowtage |= (mm_tabwe->entwies[count].vddc *
				VOWTAGE_SCAWE) << VDDC_SHIFT;
		tabwe->UvdWevew[count].MinVowtage |= ((mm_tabwe->entwies[count].vddc -
				VDDC_VDDCI_DEWTA) * VOWTAGE_SCAWE) << VDDCI_SHIFT;
		tabwe->UvdWevew[count].MinVowtage |= 1 << PHASES_SHIFT;

		/* wetwieve dividew vawue fow VBIOS */
		wesuwt = atomctww_get_dfs_pww_dividews_vi(hwmgw,
				tabwe->UvdWevew[count].VcwkFwequency, &dividews);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
				"can not find divide id fow Vcwk cwock", wetuwn wesuwt);

		tabwe->UvdWevew[count].VcwkDividew = (uint8_t)dividews.pww_post_dividew;

		wesuwt = atomctww_get_dfs_pww_dividews_vi(hwmgw,
				tabwe->UvdWevew[count].DcwkFwequency, &dividews);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
				"can not find divide id fow Dcwk cwock", wetuwn wesuwt);

		tabwe->UvdWevew[count].DcwkDividew = (uint8_t)dividews.pww_post_dividew;

		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->UvdWevew[count].VcwkFwequency);
		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->UvdWevew[count].DcwkFwequency);
		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->UvdWevew[count].MinVowtage);

	}
	wetuwn wesuwt;
}

static int fiji_popuwate_smc_boot_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct SMU73_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	tabwe->GwaphicsBootWevew = 0;
	tabwe->MemowyBootWevew = 0;

	/* find boot wevew fwom dpm tabwe */
	phm_find_boot_wevew(&(data->dpm_tabwe.scwk_tabwe),
			    data->vbios_boot_state.scwk_bootup_vawue,
			    (uint32_t *)&(tabwe->GwaphicsBootWevew));

	phm_find_boot_wevew(&(data->dpm_tabwe.mcwk_tabwe),
			    data->vbios_boot_state.mcwk_bootup_vawue,
			    (uint32_t *)&(tabwe->MemowyBootWevew));

	tabwe->BootVddc  = data->vbios_boot_state.vddc_bootup_vawue *
			VOWTAGE_SCAWE;
	tabwe->BootVddci = data->vbios_boot_state.vddci_bootup_vawue *
			VOWTAGE_SCAWE;
	tabwe->BootMVdd  = data->vbios_boot_state.mvdd_bootup_vawue *
			VOWTAGE_SCAWE;

	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->BootVddc);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->BootVddci);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->BootMVdd);

	wetuwn 0;
}

static int fiji_popuwate_smc_initaiwiaw_state(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	uint8_t count, wevew;

	count = (uint8_t)(tabwe_info->vdd_dep_on_scwk->count);
	fow (wevew = 0; wevew < count; wevew++) {
		if (tabwe_info->vdd_dep_on_scwk->entwies[wevew].cwk >=
				data->vbios_boot_state.scwk_bootup_vawue) {
			smu_data->smc_state_tabwe.GwaphicsBootWevew = wevew;
			bweak;
		}
	}

	count = (uint8_t)(tabwe_info->vdd_dep_on_mcwk->count);
	fow (wevew = 0; wevew < count; wevew++) {
		if (tabwe_info->vdd_dep_on_mcwk->entwies[wevew].cwk >=
				data->vbios_boot_state.mcwk_bootup_vawue) {
			smu_data->smc_state_tabwe.MemowyBootWevew = wevew;
			bweak;
		}
	}

	wetuwn 0;
}

static int fiji_popuwate_cwock_stwetchew_data_tabwe(stwuct pp_hwmgw *hwmgw)
{
	uint32_t wo, efuse, efuse2, cwock_fweq, vowt_without_cks,
			vowt_with_cks, vawue;
	uint16_t cwock_fweq_u16;
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);
	uint8_t type, i, j, cks_setting, stwetch_amount, stwetch_amount2,
			vowt_offset = 0;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *scwk_tabwe =
			tabwe_info->vdd_dep_on_scwk;

	stwetch_amount = (uint8_t)tabwe_info->cac_dtp_tabwe->usCwockStwetchAmount;

	/* Wead SMU_Eefuse to wead and cawcuwate WO and detewmine
	 * if the pawt is SS ow FF. if WO >= 1660MHz, pawt is FF.
	 */
	efuse = cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			ixSMU_EFUSE_0 + (146 * 4));
	efuse2 = cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			ixSMU_EFUSE_0 + (148 * 4));
	efuse &= 0xFF000000;
	efuse = efuse >> 24;
	efuse2 &= 0xF;

	if (efuse2 == 1)
		wo = (2300 - 1350) * efuse / 255 + 1350;
	ewse
		wo = (2500 - 1000) * efuse / 255 + 1000;

	if (wo >= 1660)
		type = 0;
	ewse
		type = 1;

	/* Popuwate Stwetch amount */
	smu_data->smc_state_tabwe.CwockStwetchewAmount = stwetch_amount;

	/* Popuwate Scwk_CKS_mastewEn0_7 and Scwk_vowtageOffset */
	fow (i = 0; i < scwk_tabwe->count; i++) {
		smu_data->smc_state_tabwe.Scwk_CKS_mastewEn0_7 |=
				scwk_tabwe->entwies[i].cks_enabwe << i;
		vowt_without_cks = (uint32_t)((14041 *
			(scwk_tabwe->entwies[i].cwk/100) / 10000 + 3571 + 75 - wo) * 1000 /
			(4026 - (13924 * (scwk_tabwe->entwies[i].cwk/100) / 10000)));
		vowt_with_cks = (uint32_t)((13946 *
			(scwk_tabwe->entwies[i].cwk/100) / 10000 + 3320 + 45 - wo) * 1000 /
			(3664 - (11454 * (scwk_tabwe->entwies[i].cwk/100) / 10000)));
		if (vowt_without_cks >= vowt_with_cks)
			vowt_offset = (uint8_t)(((vowt_without_cks - vowt_with_cks +
					scwk_tabwe->entwies[i].cks_voffset) * 100 / 625) + 1);
		smu_data->smc_state_tabwe.Scwk_vowtageOffset[i] = vowt_offset;
	}

	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, PWW_CKS_ENABWE,
			STWETCH_ENABWE, 0x0);
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, PWW_CKS_ENABWE,
			mastewWeset, 0x1);
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, PWW_CKS_ENABWE,
			staticEnabwe, 0x1);
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, PWW_CKS_ENABWE,
			mastewWeset, 0x0);

	/* Popuwate CKS Wookup Tabwe */
	if (stwetch_amount == 1 || stwetch_amount == 2 || stwetch_amount == 5)
		stwetch_amount2 = 0;
	ewse if (stwetch_amount == 3 || stwetch_amount == 4)
		stwetch_amount2 = 1;
	ewse {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_CwockStwetchew);
		PP_ASSEWT_WITH_CODE(fawse,
				"Stwetch Amount in PPTabwe not suppowted",
				wetuwn -EINVAW);
	}

	vawue = cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			ixPWW_CKS_CNTW);
	vawue &= 0xFFC2FF87;
	smu_data->smc_state_tabwe.CKS_WOOKUPTabwe.CKS_WOOKUPTabweEntwy[0].minFweq =
			fiji_cwock_stwetchew_wookup_tabwe[stwetch_amount2][0];
	smu_data->smc_state_tabwe.CKS_WOOKUPTabwe.CKS_WOOKUPTabweEntwy[0].maxFweq =
			fiji_cwock_stwetchew_wookup_tabwe[stwetch_amount2][1];
	cwock_fweq_u16 = (uint16_t)(PP_SMC_TO_HOST_UW(smu_data->smc_state_tabwe.
			GwaphicsWevew[smu_data->smc_state_tabwe.GwaphicsDpmWevewCount - 1].
			ScwkFwequency) / 100);
	if (fiji_cwock_stwetchew_wookup_tabwe[stwetch_amount2][0] <
			cwock_fweq_u16 &&
	    fiji_cwock_stwetchew_wookup_tabwe[stwetch_amount2][1] >
			cwock_fweq_u16) {
		/* Pwogwam PWW_CKS_CNTW. CKS_USE_FOW_WOW_FWEQ */
		vawue |= (fiji_cwock_stwetchew_wookup_tabwe[stwetch_amount2][3]) << 16;
		/* Pwogwam PWW_CKS_CNTW. CKS_WDO_WEFSEW */
		vawue |= (fiji_cwock_stwetchew_wookup_tabwe[stwetch_amount2][2]) << 18;
		/* Pwogwam PWW_CKS_CNTW. CKS_STWETCH_AMOUNT */
		vawue |= (fiji_cwock_stwetch_amount_convewsion
				[fiji_cwock_stwetchew_wookup_tabwe[stwetch_amount2][3]]
				 [stwetch_amount]) << 3;
	}
	CONVEWT_FWOM_HOST_TO_SMC_US(smu_data->smc_state_tabwe.CKS_WOOKUPTabwe.
			CKS_WOOKUPTabweEntwy[0].minFweq);
	CONVEWT_FWOM_HOST_TO_SMC_US(smu_data->smc_state_tabwe.CKS_WOOKUPTabwe.
			CKS_WOOKUPTabweEntwy[0].maxFweq);
	smu_data->smc_state_tabwe.CKS_WOOKUPTabwe.CKS_WOOKUPTabweEntwy[0].setting =
			fiji_cwock_stwetchew_wookup_tabwe[stwetch_amount2][2] & 0x7F;
	smu_data->smc_state_tabwe.CKS_WOOKUPTabwe.CKS_WOOKUPTabweEntwy[0].setting |=
			(fiji_cwock_stwetchew_wookup_tabwe[stwetch_amount2][3]) << 7;

	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			ixPWW_CKS_CNTW, vawue);

	/* Popuwate DDT Wookup Tabwe */
	fow (i = 0; i < 4; i++) {
		/* Assign the minimum and maximum VID stowed
		 * in the wast wow of Cwock Stwetchew Vowtage Tabwe.
		 */
		smu_data->smc_state_tabwe.CwockStwetchewDataTabwe.
		CwockStwetchewDataTabweEntwy[i].minVID =
				(uint8_t) fiji_cwock_stwetchew_ddt_tabwe[type][i][2];
		smu_data->smc_state_tabwe.CwockStwetchewDataTabwe.
		CwockStwetchewDataTabweEntwy[i].maxVID =
				(uint8_t) fiji_cwock_stwetchew_ddt_tabwe[type][i][3];
		/* Woop thwough each SCWK and check the fwequency
		 * to see if it wies within the fwequency fow cwock stwetchew.
		 */
		fow (j = 0; j < smu_data->smc_state_tabwe.GwaphicsDpmWevewCount; j++) {
			cks_setting = 0;
			cwock_fweq = PP_SMC_TO_HOST_UW(
					smu_data->smc_state_tabwe.GwaphicsWevew[j].ScwkFwequency);
			/* Check the awwowed fwequency against the scwk wevew[j].
			 *  Scwk's endianness has awweady been convewted,
			 *  and it's in 10Khz unit,
			 *  as opposed to Data tabwe, which is in Mhz unit.
			 */
			if (cwock_fweq >=
					(fiji_cwock_stwetchew_ddt_tabwe[type][i][0]) * 100) {
				cks_setting |= 0x2;
				if (cwock_fweq <
						(fiji_cwock_stwetchew_ddt_tabwe[type][i][1]) * 100)
					cks_setting |= 0x1;
			}
			smu_data->smc_state_tabwe.CwockStwetchewDataTabwe.
			CwockStwetchewDataTabweEntwy[i].setting |= cks_setting << (j * 2);
		}
		CONVEWT_FWOM_HOST_TO_SMC_US(smu_data->smc_state_tabwe.
				CwockStwetchewDataTabwe.
				CwockStwetchewDataTabweEntwy[i].setting);
	}

	vawue = cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixPWW_CKS_CNTW);
	vawue &= 0xFFFFFFFE;
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixPWW_CKS_CNTW, vawue);

	wetuwn 0;
}

static int fiji_popuwate_vw_config(stwuct pp_hwmgw *hwmgw,
		stwuct SMU73_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint16_t config;

	config = VW_MEWGED_WITH_VDDC;
	tabwe->VWConfig |= (config << VWCONF_VDDGFX_SHIFT);

	/* Set Vddc Vowtage Contwowwew */
	if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vowtage_contwow) {
		config = VW_SVI2_PWANE_1;
		tabwe->VWConfig |= config;
	} ewse {
		PP_ASSEWT_WITH_CODE(fawse,
				"VDDC shouwd be on SVI2 contwow in mewged mode!",
				);
	}
	/* Set Vddci Vowtage Contwowwew */
	if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vddci_contwow) {
		config = VW_SVI2_PWANE_2;  /* onwy in mewged mode */
		tabwe->VWConfig |= (config << VWCONF_VDDCI_SHIFT);
	} ewse if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->vddci_contwow) {
		config = VW_SMIO_PATTEWN_1;
		tabwe->VWConfig |= (config << VWCONF_VDDCI_SHIFT);
	} ewse {
		config = VW_STATIC_VOWTAGE;
		tabwe->VWConfig |= (config << VWCONF_VDDCI_SHIFT);
	}
	/* Set Mvdd Vowtage Contwowwew */
	if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->mvdd_contwow) {
		config = VW_SVI2_PWANE_2;
		tabwe->VWConfig |= (config << VWCONF_MVDD_SHIFT);
	} ewse if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->mvdd_contwow) {
		config = VW_SMIO_PATTEWN_2;
		tabwe->VWConfig |= (config << VWCONF_MVDD_SHIFT);
	} ewse {
		config = VW_STATIC_VOWTAGE;
		tabwe->VWConfig |= (config << VWCONF_MVDD_SHIFT);
	}

	wetuwn 0;
}

static int fiji_init_awb_tabwe_index(stwuct pp_hwmgw *hwmgw)
{
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);
	uint32_t tmp;
	int wesuwt;

	/* This is a wead-modify-wwite on the fiwst byte of the AWB tabwe.
	 * The fiwst byte in the SMU73_Discwete_MCAwbDwamTimingTabwe stwuctuwe
	 * is the fiewd 'cuwwent'.
	 * This sowution is ugwy, but we nevew wwite the whowe tabwe onwy
	 * individuaw fiewds in it.
	 * In weawity this fiewd shouwd not be in that stwuctuwe
	 * but in a soft wegistew.
	 */
	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
			smu_data->smu7_data.awb_tabwe_stawt, &tmp, SMC_WAM_END);

	if (wesuwt)
		wetuwn wesuwt;

	tmp &= 0x00FFFFFF;
	tmp |= ((uint32_t)MC_CG_AWB_FWEQ_F1) << 24;

	wetuwn smu7_wwite_smc_swam_dwowd(hwmgw,
			smu_data->smu7_data.awb_tabwe_stawt,  tmp, SMC_WAM_END);
}

static int fiji_setup_dpm_wed_config(stwuct pp_hwmgw *hwmgw)
{
	pp_atomctww_vowtage_tabwe pawam_wed_dpm;
	int wesuwt = 0;
	u32 mask = 0;

	wesuwt = atomctww_get_vowtage_tabwe_v3(hwmgw,
					       VOWTAGE_TYPE_WEDDPM, VOWTAGE_OBJ_GPIO_WUT,
					       &pawam_wed_dpm);
	if (wesuwt == 0) {
		int i, j;
		u32 tmp = pawam_wed_dpm.mask_wow;

		fow (i = 0, j = 0; i < 32; i++) {
			if (tmp & 1) {
				mask |= (i << (8 * j));
				if (++j >= 3)
					bweak;
			}
			tmp >>= 1;
		}
	}
	if (mask)
		smum_send_msg_to_smc_with_pawametew(hwmgw,
						    PPSMC_MSG_WedConfig,
						    mask,
						    NUWW);
	wetuwn 0;
}

static int fiji_init_smc_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct SMU73_Discwete_DpmTabwe *tabwe = &(smu_data->smc_state_tabwe);
	uint8_t i;
	stwuct pp_atomctww_gpio_pin_assignment gpio_pin;

	fiji_initiawize_powew_tune_defauwts(hwmgw);

	if (SMU7_VOWTAGE_CONTWOW_NONE != data->vowtage_contwow)
		fiji_popuwate_smc_vowtage_tabwes(hwmgw, tabwe);

	tabwe->SystemFwags = 0;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_AutomaticDCTwansition))
		tabwe->SystemFwags |= PPSMC_SYSTEMFWAG_GPIO_DC;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_StepVddc))
		tabwe->SystemFwags |= PPSMC_SYSTEMFWAG_STEPVDDC;

	if (data->is_memowy_gddw5)
		tabwe->SystemFwags |= PPSMC_SYSTEMFWAG_GDDW5;

	if (data->uwv_suppowted && tabwe_info->us_uwv_vowtage_offset) {
		wesuwt = fiji_popuwate_uwv_state(hwmgw, tabwe);
		PP_ASSEWT_WITH_CODE(0 == wesuwt,
				"Faiwed to initiawize UWV state!", wetuwn wesuwt);
		cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
				ixCG_UWV_PAWAMETEW, 0x40035);
	}

	wesuwt = fiji_popuwate_smc_wink_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize Wink Wevew!", wetuwn wesuwt);

	wesuwt = fiji_popuwate_aww_gwaphic_wevews(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize Gwaphics Wevew!", wetuwn wesuwt);

	wesuwt = fiji_popuwate_aww_memowy_wevews(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize Memowy Wevew!", wetuwn wesuwt);

	wesuwt = fiji_popuwate_smc_acpi_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize ACPI Wevew!", wetuwn wesuwt);

	wesuwt = fiji_popuwate_smc_vce_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize VCE Wevew!", wetuwn wesuwt);

	wesuwt = fiji_popuwate_smc_acp_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize ACP Wevew!", wetuwn wesuwt);

	/* Since onwy the initiaw state is compwetewy set up at this point
	 * (the othew states awe just copies of the boot state) we onwy
	 * need to popuwate the  AWB settings fow the initiaw state.
	 */
	wesuwt = fiji_pwogwam_memowy_timing_pawametews(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to Wwite AWB settings fow the initiaw state.", wetuwn wesuwt);

	wesuwt = fiji_popuwate_smc_uvd_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize UVD Wevew!", wetuwn wesuwt);

	wesuwt = fiji_popuwate_smc_boot_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize Boot Wevew!", wetuwn wesuwt);

	wesuwt = fiji_popuwate_smc_initaiwiaw_state(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize Boot State!", wetuwn wesuwt);

	wesuwt = fiji_popuwate_bapm_pawametews_in_dpm_tabwe(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to popuwate BAPM Pawametews!", wetuwn wesuwt);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_CwockStwetchew)) {
		wesuwt = fiji_popuwate_cwock_stwetchew_data_tabwe(hwmgw);
		PP_ASSEWT_WITH_CODE(0 == wesuwt,
				"Faiwed to popuwate Cwock Stwetchew Data Tabwe!",
				wetuwn wesuwt);
	}

	tabwe->GwaphicsVowtageChangeEnabwe  = 1;
	tabwe->GwaphicsThewmThwottweEnabwe  = 1;
	tabwe->GwaphicsIntewvaw = 1;
	tabwe->VowtageIntewvaw  = 1;
	tabwe->ThewmawIntewvaw  = 1;
	tabwe->TempewatuweWimitHigh =
			tabwe_info->cac_dtp_tabwe->usTawgetOpewatingTemp *
			SMU7_Q88_FOWMAT_CONVEWSION_UNIT;
	tabwe->TempewatuweWimitWow  =
			(tabwe_info->cac_dtp_tabwe->usTawgetOpewatingTemp - 1) *
			SMU7_Q88_FOWMAT_CONVEWSION_UNIT;
	tabwe->MemowyVowtageChangeEnabwe = 1;
	tabwe->MemowyIntewvaw = 1;
	tabwe->VowtageWesponseTime = 0;
	tabwe->PhaseWesponseTime = 0;
	tabwe->MemowyThewmThwottweEnabwe = 1;
	tabwe->PCIeBootWinkWevew = 0;      /* 0:Gen1 1:Gen2 2:Gen3*/
	tabwe->PCIeGenIntewvaw = 1;
	tabwe->VWConfig = 0;

	wesuwt = fiji_popuwate_vw_config(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to popuwate VWConfig setting!", wetuwn wesuwt);
	data->vw_config = tabwe->VWConfig;
	tabwe->ThewmGpio = 17;
	tabwe->ScwkStepSize = 0x4000;

	if (atomctww_get_pp_assign_pin(hwmgw, VDDC_VWHOT_GPIO_PINID, &gpio_pin)) {
		tabwe->VWHotGpio = gpio_pin.uc_gpio_pin_bit_shift;
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_WeguwatowHot);
	} ewse {
		tabwe->VWHotGpio = SMU7_UNUSED_GPIO_PIN;
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_WeguwatowHot);
	}

	if (atomctww_get_pp_assign_pin(hwmgw, PP_AC_DC_SWITCH_GPIO_PINID,
			&gpio_pin)) {
		tabwe->AcDcGpio = gpio_pin.uc_gpio_pin_bit_shift;
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_AutomaticDCTwansition);
	} ewse {
		tabwe->AcDcGpio = SMU7_UNUSED_GPIO_PIN;
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_AutomaticDCTwansition);
	}

	/* Thewmaw Output GPIO */
	if (atomctww_get_pp_assign_pin(hwmgw, THEWMAW_INT_OUTPUT_GPIO_PINID,
			&gpio_pin)) {
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_ThewmawOutGPIO);

		tabwe->ThewmOutGpio = gpio_pin.uc_gpio_pin_bit_shift;

		/* Fow powwawity wead GPIOPAD_A with assigned Gpio pin
		 * since VBIOS wiww pwogwam this wegistew to set 'inactive state',
		 * dwivew can then detewmine 'active state' fwom this and
		 * pwogwam SMU with cowwect powawity
		 */
		tabwe->ThewmOutPowawity = (0 == (cgs_wead_wegistew(hwmgw->device, mmGPIOPAD_A) &
				(1 << gpio_pin.uc_gpio_pin_bit_shift))) ? 1:0;
		tabwe->ThewmOutMode = SMU7_THEWM_OUT_MODE_THEWM_ONWY;

		/* if wequiwed, combine VWHot/PCC with thewmaw out GPIO */
		if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_WeguwatowHot) &&
			phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_CombinePCCWithThewmawSignaw))
			tabwe->ThewmOutMode = SMU7_THEWM_OUT_MODE_THEWM_VWHOT;
	} ewse {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_ThewmawOutGPIO);
		tabwe->ThewmOutGpio = 17;
		tabwe->ThewmOutPowawity = 1;
		tabwe->ThewmOutMode = SMU7_THEWM_OUT_MODE_DISABWE;
	}

	fow (i = 0; i < SMU73_MAX_ENTWIES_SMIO; i++)
		tabwe->Smio[i] = PP_HOST_TO_SMC_UW(tabwe->Smio[i]);

	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SystemFwags);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->VWConfig);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SmioMask1);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SmioMask2);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ScwkStepSize);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->TempewatuweWimitHigh);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->TempewatuweWimitWow);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->VowtageWesponseTime);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->PhaseWesponseTime);

	/* Upwoad aww dpm data to SMC memowy.(dpm wevew, dpm wevew count etc) */
	wesuwt = smu7_copy_bytes_to_smc(hwmgw,
			smu_data->smu7_data.dpm_tabwe_stawt +
			offsetof(SMU73_Discwete_DpmTabwe, SystemFwags),
			(uint8_t *)&(tabwe->SystemFwags),
			sizeof(SMU73_Discwete_DpmTabwe) - 3 * sizeof(SMU73_PIDContwowwew),
			SMC_WAM_END);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to upwoad dpm data to SMC memowy!", wetuwn wesuwt);

	wesuwt = fiji_init_awb_tabwe_index(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to upwoad awb data to SMC memowy!", wetuwn wesuwt);

	wesuwt = fiji_popuwate_pm_fuses(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to  popuwate PM fuses to SMC memowy!", wetuwn wesuwt);

	wesuwt = fiji_setup_dpm_wed_config(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			    "Faiwed to setup dpm wed config", wetuwn wesuwt);

	wetuwn 0;
}

static int fiji_thewmaw_setup_fan_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);

	SMU73_Discwete_FanTabwe fan_tabwe = { FDO_MODE_HAWDWAWE };
	uint32_t duty100;
	uint32_t t_diff1, t_diff2, pwm_diff1, pwm_diff2;
	uint16_t fdo_min, swope1, swope2;
	uint32_t wefewence_cwock;
	int wes;
	uint64_t tmp64;

	if (hwmgw->thewmaw_contwowwew.fanInfo.bNoFan) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_MicwocodeFanContwow);
		wetuwn 0;
	}

	if (smu_data->smu7_data.fan_tabwe_stawt == 0) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_MicwocodeFanContwow);
		wetuwn 0;
	}

	duty100 = PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_FDO_CTWW1, FMAX_DUTY100);

	if (duty100 == 0) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_MicwocodeFanContwow);
		wetuwn 0;
	}

	tmp64 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.
			usPWMMin * duty100;
	do_div(tmp64, 10000);
	fdo_min = (uint16_t)tmp64;

	t_diff1 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMed -
			hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMin;
	t_diff2 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTHigh -
			hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMed;

	pwm_diff1 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMed -
			hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMin;
	pwm_diff2 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMHigh -
			hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMed;

	swope1 = (uint16_t)((50 + ((16 * duty100 * pwm_diff1) / t_diff1)) / 100);
	swope2 = (uint16_t)((50 + ((16 * duty100 * pwm_diff2) / t_diff2)) / 100);

	fan_tabwe.TempMin = cpu_to_be16((50 + hwmgw->
			thewmaw_contwowwew.advanceFanContwowPawametews.usTMin) / 100);
	fan_tabwe.TempMed = cpu_to_be16((50 + hwmgw->
			thewmaw_contwowwew.advanceFanContwowPawametews.usTMed) / 100);
	fan_tabwe.TempMax = cpu_to_be16((50 + hwmgw->
			thewmaw_contwowwew.advanceFanContwowPawametews.usTMax) / 100);

	fan_tabwe.Swope1 = cpu_to_be16(swope1);
	fan_tabwe.Swope2 = cpu_to_be16(swope2);

	fan_tabwe.FdoMin = cpu_to_be16(fdo_min);

	fan_tabwe.HystDown = cpu_to_be16(hwmgw->
			thewmaw_contwowwew.advanceFanContwowPawametews.ucTHyst);

	fan_tabwe.HystUp = cpu_to_be16(1);

	fan_tabwe.HystSwope = cpu_to_be16(1);

	fan_tabwe.TempWespWim = cpu_to_be16(5);

	wefewence_cwock = amdgpu_asic_get_xcwk((stwuct amdgpu_device *)hwmgw->adev);

	fan_tabwe.WefweshPewiod = cpu_to_be32((hwmgw->
			thewmaw_contwowwew.advanceFanContwowPawametews.uwCycweDeway *
			wefewence_cwock) / 1600);

	fan_tabwe.FdoMax = cpu_to_be16((uint16_t)duty100);

	fan_tabwe.TempSwc = (uint8_t)PHM_WEAD_VFPF_INDIWECT_FIEWD(
			hwmgw->device, CGS_IND_WEG__SMC,
			CG_MUWT_THEWMAW_CTWW, TEMP_SEW);

	wes = smu7_copy_bytes_to_smc(hwmgw, smu_data->smu7_data.fan_tabwe_stawt,
			(uint8_t *)&fan_tabwe, (uint32_t)sizeof(fan_tabwe),
			SMC_WAM_END);

	if (!wes && hwmgw->thewmaw_contwowwew.
			advanceFanContwowPawametews.ucMinimumPWMWimit)
		wes = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetFanMinPwm,
				hwmgw->thewmaw_contwowwew.
				advanceFanContwowPawametews.ucMinimumPWMWimit,
				NUWW);

	if (!wes && hwmgw->thewmaw_contwowwew.
			advanceFanContwowPawametews.uwMinFanSCWKAcousticWimit)
		wes = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetFanScwkTawget,
				hwmgw->thewmaw_contwowwew.
				advanceFanContwowPawametews.uwMinFanSCWKAcousticWimit,
				NUWW);

	if (wes)
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_MicwocodeFanContwow);

	wetuwn 0;
}


static int fiji_thewmaw_avfs_enabwe(stwuct pp_hwmgw *hwmgw)
{
	if (!hwmgw->avfs_suppowted)
		wetuwn 0;

	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_EnabweAvfs, NUWW);

	wetuwn 0;
}

static int fiji_pwogwam_mem_timing_pawametews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (data->need_update_smu7_dpm_tabwe &
		(DPMTABWE_OD_UPDATE_SCWK + DPMTABWE_OD_UPDATE_MCWK))
		wetuwn fiji_pwogwam_memowy_timing_pawametews(hwmgw);

	wetuwn 0;
}

static int fiji_update_scwk_thweshowd(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);

	int wesuwt = 0;
	uint32_t wow_scwk_intewwupt_thweshowd = 0;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ScwkThwottweWowNotification)
		&& (data->wow_scwk_intewwupt_thweshowd != 0)) {
		wow_scwk_intewwupt_thweshowd =
				data->wow_scwk_intewwupt_thweshowd;

		CONVEWT_FWOM_HOST_TO_SMC_UW(wow_scwk_intewwupt_thweshowd);

		wesuwt = smu7_copy_bytes_to_smc(
				hwmgw,
				smu_data->smu7_data.dpm_tabwe_stawt +
				offsetof(SMU73_Discwete_DpmTabwe,
					WowScwkIntewwuptThweshowd),
				(uint8_t *)&wow_scwk_intewwupt_thweshowd,
				sizeof(uint32_t),
				SMC_WAM_END);
	}
	wesuwt = fiji_pwogwam_mem_timing_pawametews(hwmgw);
	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			"Faiwed to pwogwam memowy timing pawametews!",
			);
	wetuwn wesuwt;
}

static uint32_t fiji_get_offsetof(uint32_t type, uint32_t membew)
{
	switch (type) {
	case SMU_SoftWegistews:
		switch (membew) {
		case HandshakeDisabwes:
			wetuwn offsetof(SMU73_SoftWegistews, HandshakeDisabwes);
		case VowtageChangeTimeout:
			wetuwn offsetof(SMU73_SoftWegistews, VowtageChangeTimeout);
		case AvewageGwaphicsActivity:
			wetuwn offsetof(SMU73_SoftWegistews, AvewageGwaphicsActivity);
		case AvewageMemowyActivity:
			wetuwn offsetof(SMU73_SoftWegistews, AvewageMemowyActivity);
		case PweVBwankGap:
			wetuwn offsetof(SMU73_SoftWegistews, PweVBwankGap);
		case VBwankTimeout:
			wetuwn offsetof(SMU73_SoftWegistews, VBwankTimeout);
		case UcodeWoadStatus:
			wetuwn offsetof(SMU73_SoftWegistews, UcodeWoadStatus);
		case DWAM_WOG_ADDW_H:
			wetuwn offsetof(SMU73_SoftWegistews, DWAM_WOG_ADDW_H);
		case DWAM_WOG_ADDW_W:
			wetuwn offsetof(SMU73_SoftWegistews, DWAM_WOG_ADDW_W);
		case DWAM_WOG_PHY_ADDW_H:
			wetuwn offsetof(SMU73_SoftWegistews, DWAM_WOG_PHY_ADDW_H);
		case DWAM_WOG_PHY_ADDW_W:
			wetuwn offsetof(SMU73_SoftWegistews, DWAM_WOG_PHY_ADDW_W);
		case DWAM_WOG_BUFF_SIZE:
			wetuwn offsetof(SMU73_SoftWegistews, DWAM_WOG_BUFF_SIZE);
		}
		bweak;
	case SMU_Discwete_DpmTabwe:
		switch (membew) {
		case UvdBootWevew:
			wetuwn offsetof(SMU73_Discwete_DpmTabwe, UvdBootWevew);
		case VceBootWevew:
			wetuwn offsetof(SMU73_Discwete_DpmTabwe, VceBootWevew);
		case WowScwkIntewwuptThweshowd:
			wetuwn offsetof(SMU73_Discwete_DpmTabwe, WowScwkIntewwuptThweshowd);
		}
		bweak;
	}
	pw_wawn("can't get the offset of type %x membew %x\n", type, membew);
	wetuwn 0;
}

static uint32_t fiji_get_mac_definition(uint32_t vawue)
{
	switch (vawue) {
	case SMU_MAX_WEVEWS_GWAPHICS:
		wetuwn SMU73_MAX_WEVEWS_GWAPHICS;
	case SMU_MAX_WEVEWS_MEMOWY:
		wetuwn SMU73_MAX_WEVEWS_MEMOWY;
	case SMU_MAX_WEVEWS_WINK:
		wetuwn SMU73_MAX_WEVEWS_WINK;
	case SMU_MAX_ENTWIES_SMIO:
		wetuwn SMU73_MAX_ENTWIES_SMIO;
	case SMU_MAX_WEVEWS_VDDC:
		wetuwn SMU73_MAX_WEVEWS_VDDC;
	case SMU_MAX_WEVEWS_VDDGFX:
		wetuwn SMU73_MAX_WEVEWS_VDDGFX;
	case SMU_MAX_WEVEWS_VDDCI:
		wetuwn SMU73_MAX_WEVEWS_VDDCI;
	case SMU_MAX_WEVEWS_MVDD:
		wetuwn SMU73_MAX_WEVEWS_MVDD;
	}

	pw_wawn("can't get the mac of %x\n", vawue);
	wetuwn 0;
}


static int fiji_update_uvd_smc_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);
	uint32_t mm_boot_wevew_offset, mm_boot_wevew_vawue;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	smu_data->smc_state_tabwe.UvdBootWevew = 0;
	if (tabwe_info->mm_dep_tabwe->count > 0)
		smu_data->smc_state_tabwe.UvdBootWevew =
				(uint8_t) (tabwe_info->mm_dep_tabwe->count - 1);
	mm_boot_wevew_offset = smu_data->smu7_data.dpm_tabwe_stawt + offsetof(SMU73_Discwete_DpmTabwe,
						UvdBootWevew);
	mm_boot_wevew_offset /= 4;
	mm_boot_wevew_offset *= 4;
	mm_boot_wevew_vawue = cgs_wead_ind_wegistew(hwmgw->device,
			CGS_IND_WEG__SMC, mm_boot_wevew_offset);
	mm_boot_wevew_vawue &= 0x00FFFFFF;
	mm_boot_wevew_vawue |= smu_data->smc_state_tabwe.UvdBootWevew << 24;
	cgs_wwite_ind_wegistew(hwmgw->device,
			CGS_IND_WEG__SMC, mm_boot_wevew_offset, mm_boot_wevew_vawue);

	if (!phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_UVDDPM) ||
		phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_StabwePState))
		smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_UVDDPM_SetEnabwedMask,
				(uint32_t)(1 << smu_data->smc_state_tabwe.UvdBootWevew),
				NUWW);
	wetuwn 0;
}

static int fiji_update_vce_smc_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);
	uint32_t mm_boot_wevew_offset, mm_boot_wevew_vawue;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_StabwePState))
		smu_data->smc_state_tabwe.VceBootWevew =
			(uint8_t) (tabwe_info->mm_dep_tabwe->count - 1);
	ewse
		smu_data->smc_state_tabwe.VceBootWevew = 0;

	mm_boot_wevew_offset = smu_data->smu7_data.dpm_tabwe_stawt +
					offsetof(SMU73_Discwete_DpmTabwe, VceBootWevew);
	mm_boot_wevew_offset /= 4;
	mm_boot_wevew_offset *= 4;
	mm_boot_wevew_vawue = cgs_wead_ind_wegistew(hwmgw->device,
			CGS_IND_WEG__SMC, mm_boot_wevew_offset);
	mm_boot_wevew_vawue &= 0xFF00FFFF;
	mm_boot_wevew_vawue |= smu_data->smc_state_tabwe.VceBootWevew << 16;
	cgs_wwite_ind_wegistew(hwmgw->device,
			CGS_IND_WEG__SMC, mm_boot_wevew_offset, mm_boot_wevew_vawue);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_StabwePState))
		smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_VCEDPM_SetEnabwedMask,
				(uint32_t)1 << smu_data->smc_state_tabwe.VceBootWevew,
				NUWW);
	wetuwn 0;
}

static int fiji_update_smc_tabwe(stwuct pp_hwmgw *hwmgw, uint32_t type)
{
	switch (type) {
	case SMU_UVD_TABWE:
		fiji_update_uvd_smc_tabwe(hwmgw);
		bweak;
	case SMU_VCE_TABWE:
		fiji_update_vce_smc_tabwe(hwmgw);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int fiji_pwocess_fiwmwawe_headew(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)(hwmgw->smu_backend);
	uint32_t tmp;
	int wesuwt;
	boow ewwow = fawse;

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
			SMU7_FIWMWAWE_HEADEW_WOCATION +
			offsetof(SMU73_Fiwmwawe_Headew, DpmTabwe),
			&tmp, SMC_WAM_END);

	if (0 == wesuwt)
		smu_data->smu7_data.dpm_tabwe_stawt = tmp;

	ewwow |= (0 != wesuwt);

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
			SMU7_FIWMWAWE_HEADEW_WOCATION +
			offsetof(SMU73_Fiwmwawe_Headew, SoftWegistews),
			&tmp, SMC_WAM_END);

	if (!wesuwt) {
		data->soft_wegs_stawt = tmp;
		smu_data->smu7_data.soft_wegs_stawt = tmp;
	}

	ewwow |= (0 != wesuwt);

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
			SMU7_FIWMWAWE_HEADEW_WOCATION +
			offsetof(SMU73_Fiwmwawe_Headew, mcWegistewTabwe),
			&tmp, SMC_WAM_END);

	if (!wesuwt)
		smu_data->smu7_data.mc_weg_tabwe_stawt = tmp;

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
			SMU7_FIWMWAWE_HEADEW_WOCATION +
			offsetof(SMU73_Fiwmwawe_Headew, FanTabwe),
			&tmp, SMC_WAM_END);

	if (!wesuwt)
		smu_data->smu7_data.fan_tabwe_stawt = tmp;

	ewwow |= (0 != wesuwt);

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
			SMU7_FIWMWAWE_HEADEW_WOCATION +
			offsetof(SMU73_Fiwmwawe_Headew, mcAwbDwamTimingTabwe),
			&tmp, SMC_WAM_END);

	if (!wesuwt)
		smu_data->smu7_data.awb_tabwe_stawt = tmp;

	ewwow |= (0 != wesuwt);

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
			SMU7_FIWMWAWE_HEADEW_WOCATION +
			offsetof(SMU73_Fiwmwawe_Headew, Vewsion),
			&tmp, SMC_WAM_END);

	if (!wesuwt)
		hwmgw->micwocode_vewsion_info.SMC = tmp;

	ewwow |= (0 != wesuwt);

	wetuwn ewwow ? -1 : 0;
}

static int fiji_initiawize_mc_weg_tabwe(stwuct pp_hwmgw *hwmgw)
{

	/* Pwogwam additionaw WP wegistews
	 * that awe no wongew pwogwammed by VBIOS
	 */
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WAS_TIMING_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WAS_TIMING));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_CAS_TIMING_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_CAS_TIMING));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_MISC_TIMING2_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC_TIMING2));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_D1_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_D1));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WD_CTW_D0_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WD_CTW_D0));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WD_CTW_D1_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WD_CTW_D1));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_TIMING_WP,
			cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_PMG_TIMING));

	wetuwn 0;
}

static boow fiji_is_dpm_wunning(stwuct pp_hwmgw *hwmgw)
{
	wetuwn (1 == PHM_WEAD_INDIWECT_FIEWD(hwmgw->device,
			CGS_IND_WEG__SMC, FEATUWE_STATUS, VOWTAGE_CONTWOWWEW_ON))
			? twue : fawse;
}

static int fiji_update_dpm_settings(stwuct pp_hwmgw *hwmgw,
				void *pwofiwe_setting)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct fiji_smumgw *smu_data = (stwuct fiji_smumgw *)
			(hwmgw->smu_backend);
	stwuct pwofiwe_mode_setting *setting;
	stwuct SMU73_Discwete_GwaphicsWevew *wevews =
			smu_data->smc_state_tabwe.GwaphicsWevew;
	uint32_t awway = smu_data->smu7_data.dpm_tabwe_stawt +
			offsetof(SMU73_Discwete_DpmTabwe, GwaphicsWevew);

	uint32_t mcwk_awway = smu_data->smu7_data.dpm_tabwe_stawt +
			offsetof(SMU73_Discwete_DpmTabwe, MemowyWevew);
	stwuct SMU73_Discwete_MemowyWevew *mcwk_wevews =
			smu_data->smc_state_tabwe.MemowyWevew;
	uint32_t i;
	uint32_t offset, up_hyst_offset, down_hyst_offset, cwk_activity_offset, tmp;

	if (pwofiwe_setting == NUWW)
		wetuwn -EINVAW;

	setting = (stwuct pwofiwe_mode_setting *)pwofiwe_setting;

	if (setting->bupdate_scwk) {
		if (!data->scwk_dpm_key_disabwed)
			smum_send_msg_to_smc(hwmgw, PPSMC_MSG_SCWKDPM_FweezeWevew, NUWW);
		fow (i = 0; i < smu_data->smc_state_tabwe.GwaphicsDpmWevewCount; i++) {
			if (wevews[i].ActivityWevew !=
				cpu_to_be16(setting->scwk_activity)) {
				wevews[i].ActivityWevew = cpu_to_be16(setting->scwk_activity);

				cwk_activity_offset = awway + (sizeof(SMU73_Discwete_GwaphicsWevew) * i)
						+ offsetof(SMU73_Discwete_GwaphicsWevew, ActivityWevew);
				offset = cwk_activity_offset & ~0x3;
				tmp = PP_HOST_TO_SMC_UW(cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset));
				tmp = phm_set_fiewd_to_u32(cwk_activity_offset, tmp, wevews[i].ActivityWevew, sizeof(uint16_t));
				cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset, PP_HOST_TO_SMC_UW(tmp));

			}
			if (wevews[i].UpHyst != setting->scwk_up_hyst ||
				wevews[i].DownHyst != setting->scwk_down_hyst) {
				wevews[i].UpHyst = setting->scwk_up_hyst;
				wevews[i].DownHyst = setting->scwk_down_hyst;
				up_hyst_offset = awway + (sizeof(SMU73_Discwete_GwaphicsWevew) * i)
						+ offsetof(SMU73_Discwete_GwaphicsWevew, UpHyst);
				down_hyst_offset = awway + (sizeof(SMU73_Discwete_GwaphicsWevew) * i)
						+ offsetof(SMU73_Discwete_GwaphicsWevew, DownHyst);
				offset = up_hyst_offset & ~0x3;
				tmp = PP_HOST_TO_SMC_UW(cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset));
				tmp = phm_set_fiewd_to_u32(up_hyst_offset, tmp, wevews[i].UpHyst, sizeof(uint8_t));
				tmp = phm_set_fiewd_to_u32(down_hyst_offset, tmp, wevews[i].DownHyst, sizeof(uint8_t));
				cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset, PP_HOST_TO_SMC_UW(tmp));
			}
		}
		if (!data->scwk_dpm_key_disabwed)
			smum_send_msg_to_smc(hwmgw, PPSMC_MSG_SCWKDPM_UnfweezeWevew, NUWW);
	}

	if (setting->bupdate_mcwk) {
		if (!data->mcwk_dpm_key_disabwed)
			smum_send_msg_to_smc(hwmgw, PPSMC_MSG_MCWKDPM_FweezeWevew, NUWW);
		fow (i = 0; i < smu_data->smc_state_tabwe.MemowyDpmWevewCount; i++) {
			if (mcwk_wevews[i].ActivityWevew !=
				cpu_to_be16(setting->mcwk_activity)) {
				mcwk_wevews[i].ActivityWevew = cpu_to_be16(setting->mcwk_activity);

				cwk_activity_offset = mcwk_awway + (sizeof(SMU73_Discwete_MemowyWevew) * i)
						+ offsetof(SMU73_Discwete_MemowyWevew, ActivityWevew);
				offset = cwk_activity_offset & ~0x3;
				tmp = PP_HOST_TO_SMC_UW(cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset));
				tmp = phm_set_fiewd_to_u32(cwk_activity_offset, tmp, mcwk_wevews[i].ActivityWevew, sizeof(uint16_t));
				cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset, PP_HOST_TO_SMC_UW(tmp));

			}
			if (mcwk_wevews[i].UpHyst != setting->mcwk_up_hyst ||
				mcwk_wevews[i].DownHyst != setting->mcwk_down_hyst) {
				mcwk_wevews[i].UpHyst = setting->mcwk_up_hyst;
				mcwk_wevews[i].DownHyst = setting->mcwk_down_hyst;
				up_hyst_offset = mcwk_awway + (sizeof(SMU73_Discwete_MemowyWevew) * i)
						+ offsetof(SMU73_Discwete_MemowyWevew, UpHyst);
				down_hyst_offset = mcwk_awway + (sizeof(SMU73_Discwete_MemowyWevew) * i)
						+ offsetof(SMU73_Discwete_MemowyWevew, DownHyst);
				offset = up_hyst_offset & ~0x3;
				tmp = PP_HOST_TO_SMC_UW(cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset));
				tmp = phm_set_fiewd_to_u32(up_hyst_offset, tmp, mcwk_wevews[i].UpHyst, sizeof(uint8_t));
				tmp = phm_set_fiewd_to_u32(down_hyst_offset, tmp, mcwk_wevews[i].DownHyst, sizeof(uint8_t));
				cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset, PP_HOST_TO_SMC_UW(tmp));
			}
		}
		if (!data->mcwk_dpm_key_disabwed)
			smum_send_msg_to_smc(hwmgw, PPSMC_MSG_MCWKDPM_UnfweezeWevew, NUWW);
	}
	wetuwn 0;
}

const stwuct pp_smumgw_func fiji_smu_funcs = {
	.name = "fiji_smu",
	.smu_init = &fiji_smu_init,
	.smu_fini = &smu7_smu_fini,
	.stawt_smu = &fiji_stawt_smu,
	.check_fw_woad_finish = &smu7_check_fw_woad_finish,
	.wequest_smu_woad_fw = &smu7_wewoad_fiwmwawe,
	.wequest_smu_woad_specific_fw = NUWW,
	.send_msg_to_smc = &smu7_send_msg_to_smc,
	.send_msg_to_smc_with_pawametew = &smu7_send_msg_to_smc_with_pawametew,
	.get_awgument = smu7_get_awgument,
	.downwoad_pptabwe_settings = NUWW,
	.upwoad_pptabwe_settings = NUWW,
	.update_smc_tabwe = fiji_update_smc_tabwe,
	.get_offsetof = fiji_get_offsetof,
	.pwocess_fiwmwawe_headew = fiji_pwocess_fiwmwawe_headew,
	.init_smc_tabwe = fiji_init_smc_tabwe,
	.update_scwk_thweshowd = fiji_update_scwk_thweshowd,
	.thewmaw_setup_fan_tabwe = fiji_thewmaw_setup_fan_tabwe,
	.thewmaw_avfs_enabwe = fiji_thewmaw_avfs_enabwe,
	.popuwate_aww_gwaphic_wevews = fiji_popuwate_aww_gwaphic_wevews,
	.popuwate_aww_memowy_wevews = fiji_popuwate_aww_memowy_wevews,
	.get_mac_definition = fiji_get_mac_definition,
	.initiawize_mc_weg_tabwe = fiji_initiawize_mc_weg_tabwe,
	.is_dpm_wunning = fiji_is_dpm_wunning,
	.is_hw_avfs_pwesent = fiji_is_hw_avfs_pwesent,
	.update_dpm_settings = fiji_update_dpm_settings,
};
