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

#incwude <winux/pci.h>

#incwude "pp_debug.h"
#incwude "smumgw.h"
#incwude "smu74.h"
#incwude "smu_ucode_xfew_vi.h"
#incwude "powawis10_smumgw.h"
#incwude "smu74_discwete.h"
#incwude "smu/smu_7_1_3_d.h"
#incwude "smu/smu_7_1_3_sh_mask.h"
#incwude "gmc/gmc_8_1_d.h"
#incwude "gmc/gmc_8_1_sh_mask.h"
#incwude "oss/oss_3_0_d.h"
#incwude "gca/gfx_8_0_d.h"
#incwude "bif/bif_5_0_d.h"
#incwude "bif/bif_5_0_sh_mask.h"
#incwude "ppatomctww.h"
#incwude "cgs_common.h"
#incwude "smu7_ppsmc.h"
#incwude "smu7_smumgw.h"

#incwude "smu7_dyn_defauwts.h"

#incwude "smu7_hwmgw.h"
#incwude "hawdwawemanagew.h"
#incwude "atombios.h"
#incwude "pppciewanes.h"

#incwude "dce/dce_10_0_d.h"
#incwude "dce/dce_10_0_sh_mask.h"

#define POWAWIS10_SMC_SIZE 0x20000
#define POWEWTUNE_DEFAUWT_SET_MAX    1
#define VDDC_VDDCI_DEWTA            200
#define MC_CG_AWB_FWEQ_F1           0x0b

static const stwuct powawis10_pt_defauwts powawis10_powew_tune_data_set_awway[POWEWTUNE_DEFAUWT_SET_MAX] = {
	/* sviWoadWIneEn, SviWoadWineVddC, TDC_VDDC_ThwottweWeweaseWimitPewc, TDC_MAWt,
	 * TdcWatewfawwCtw, DTEAmbientTempBase, DispwayCac, BAPM_TEMP_GWADIENT */
	{ 1, 0xF, 0xFD, 0x19, 5, 45, 0, 0xB0000,
	{ 0x79, 0x253, 0x25D, 0xAE, 0x72, 0x80, 0x83, 0x86, 0x6F, 0xC8, 0xC9, 0xC9, 0x2F, 0x4D, 0x61},
	{ 0x17C, 0x172, 0x180, 0x1BC, 0x1B3, 0x1BD, 0x206, 0x200, 0x203, 0x25D, 0x25A, 0x255, 0x2C3, 0x2C5, 0x2B4 } },
};

static const scwkFcwWange_t Wange_Tabwe[NUM_SCWK_WANGE] = {
			{VCO_2_4, POSTDIV_DIV_BY_16,  75, 160, 112},
			{VCO_3_6, POSTDIV_DIV_BY_16, 112, 224, 160},
			{VCO_2_4, POSTDIV_DIV_BY_8,   75, 160, 112},
			{VCO_3_6, POSTDIV_DIV_BY_8,  112, 224, 160},
			{VCO_2_4, POSTDIV_DIV_BY_4,   75, 160, 112},
			{VCO_3_6, POSTDIV_DIV_BY_4,  112, 216, 160},
			{VCO_2_4, POSTDIV_DIV_BY_2,   75, 160, 108},
			{VCO_3_6, POSTDIV_DIV_BY_2,  112, 216, 160} };

#define PPPOWAWIS10_TAWGETACTIVITY_DFWT                     50

static const SMU74_Discwete_GwaphicsWevew avfs_gwaphics_wevew_powawis10[8] = {
	/*  Min      pcie   DeepSweep Activity  CgSpww      CgSpww    CcPww  CcPww  Scwk         Enabwed      Enabwed                       Vowtage    Powew */
	/* Vowtage, DpmWevew, DivId,  Wevew,  FuncCntw3,  FuncCntw4,  DynWm, DynWm1 Did, Padding,FowActivity, FowThwottwe, UpHyst, DownHyst, DownHyst, Thwottwe */
	{ 0x100ea446, 0x00, 0x03, 0x3200, 0, 0, 0, 0, 0, 0, 0x01, 0x01, 0x0a, 0x00, 0x00, 0x00, { 0x30750000, 0x3000, 0, 0x2600, 0, 0, 0x0004, 0x8f02, 0xffff, 0x2f00, 0x300e, 0x2700 } },
	{ 0x400ea446, 0x01, 0x04, 0x3200, 0, 0, 0, 0, 0, 0, 0x01, 0x01, 0x0a, 0x00, 0x00, 0x00, { 0x409c0000, 0x2000, 0, 0x1e00, 1, 1, 0x0004, 0x8300, 0xffff, 0x1f00, 0xcb5e, 0x1a00 } },
	{ 0x740ea446, 0x01, 0x00, 0x3200, 0, 0, 0, 0, 0, 0, 0x01, 0x01, 0x0a, 0x00, 0x00, 0x00, { 0x50c30000, 0x2800, 0, 0x2000, 1, 1, 0x0004, 0x0c02, 0xffff, 0x2700, 0x6433, 0x2100 } },
	{ 0xa40ea446, 0x01, 0x00, 0x3200, 0, 0, 0, 0, 0, 0, 0x01, 0x01, 0x0a, 0x00, 0x00, 0x00, { 0x60ea0000, 0x3000, 0, 0x2600, 1, 1, 0x0004, 0x8f02, 0xffff, 0x2f00, 0x300e, 0x2700 } },
	{ 0xd80ea446, 0x01, 0x00, 0x3200, 0, 0, 0, 0, 0, 0, 0x01, 0x01, 0x0a, 0x00, 0x00, 0x00, { 0x70110100, 0x3800, 0, 0x2c00, 1, 1, 0x0004, 0x1203, 0xffff, 0x3600, 0xc9e2, 0x2e00 } },
	{ 0x3c0fa446, 0x01, 0x00, 0x3200, 0, 0, 0, 0, 0, 0, 0x01, 0x01, 0x0a, 0x00, 0x00, 0x00, { 0x80380100, 0x2000, 0, 0x1e00, 2, 1, 0x0004, 0x8300, 0xffff, 0x1f00, 0xcb5e, 0x1a00 } },
	{ 0x6c0fa446, 0x01, 0x00, 0x3200, 0, 0, 0, 0, 0, 0, 0x01, 0x01, 0x0a, 0x00, 0x00, 0x00, { 0x905f0100, 0x2400, 0, 0x1e00, 2, 1, 0x0004, 0x8901, 0xffff, 0x2300, 0x314c, 0x1d00 } },
	{ 0xa00fa446, 0x01, 0x00, 0x3200, 0, 0, 0, 0, 0, 0, 0x01, 0x01, 0x0a, 0x00, 0x00, 0x00, { 0xa0860100, 0x2800, 0, 0x2000, 2, 1, 0x0004, 0x0c02, 0xffff, 0x2700, 0x6433, 0x2100 } }
};

static const SMU74_Discwete_MemowyWevew avfs_memowy_wevew_powawis10 = {
	0x100ea446, 0, 0x30750000, 0x01, 0x01, 0x01, 0x00, 0x00, 0x64, 0x00, 0x00, 0x1f00, 0x00, 0x00};

static int powawis10_pewfowm_btc(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;
	stwuct smu7_smumgw *smu_data = (stwuct smu7_smumgw *)(hwmgw->smu_backend);

	if (0 != smu_data->avfs_btc_pawam) {
		if (0 != smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_PewfowmBtc, smu_data->avfs_btc_pawam,
					NUWW)) {
			pw_info("[AVFS][SmuPowawis10_PewfowmBtc] PewfowmBTC SMU msg faiwed");
			wesuwt = -1;
		}
	}
	if (smu_data->avfs_btc_pawam > 1) {
		/* Soft-Weset to weset the engine befowe woading uCode */
		/* hawt */
		cgs_wwite_wegistew(hwmgw->device, mmCP_MEC_CNTW, 0x50000000);
		/* weset evewything */
		cgs_wwite_wegistew(hwmgw->device, mmGWBM_SOFT_WESET, 0xffffffff);
		cgs_wwite_wegistew(hwmgw->device, mmGWBM_SOFT_WESET, 0);
	}
	wetuwn wesuwt;
}


static int powawis10_setup_gwaphics_wevew_stwuctuwe(stwuct pp_hwmgw *hwmgw)
{
	uint32_t vw_config;
	uint32_t dpm_tabwe_stawt;

	uint16_t u16_boot_mvdd;
	uint32_t gwaphics_wevew_addwess, vw_config_addwess, gwaphics_wevew_size;

	gwaphics_wevew_size = sizeof(avfs_gwaphics_wevew_powawis10);
	u16_boot_mvdd = PP_HOST_TO_SMC_US(1300 * VOWTAGE_SCAWE);

	PP_ASSEWT_WITH_CODE(0 == smu7_wead_smc_swam_dwowd(hwmgw,
				SMU7_FIWMWAWE_HEADEW_WOCATION + offsetof(SMU74_Fiwmwawe_Headew, DpmTabwe),
				&dpm_tabwe_stawt, 0x40000),
			"[AVFS][Powawis10_SetupGfxWvwStwuct] SMU couwd not communicate stawting addwess of DPM tabwe",
			wetuwn -1);

	/*  Defauwt vawue fow VWConfig = VW_MEWGED_WITH_VDDC + VW_STATIC_VOWTAGE(VDDCI) */
	vw_config = 0x01000500; /* Weaw vawue:0x50001 */

	vw_config_addwess = dpm_tabwe_stawt + offsetof(SMU74_Discwete_DpmTabwe, VWConfig);

	PP_ASSEWT_WITH_CODE(0 == smu7_copy_bytes_to_smc(hwmgw, vw_config_addwess,
				(uint8_t *)&vw_config, sizeof(uint32_t), 0x40000),
			"[AVFS][Powawis10_SetupGfxWvwStwuct] Pwobwems copying VWConfig vawue ovew to SMC",
			wetuwn -1);

	gwaphics_wevew_addwess = dpm_tabwe_stawt + offsetof(SMU74_Discwete_DpmTabwe, GwaphicsWevew);

	PP_ASSEWT_WITH_CODE(0 == smu7_copy_bytes_to_smc(hwmgw, gwaphics_wevew_addwess,
				(uint8_t *)(&avfs_gwaphics_wevew_powawis10),
				gwaphics_wevew_size, 0x40000),
			"[AVFS][Powawis10_SetupGfxWvwStwuct] Copying of SCWK DPM tabwe faiwed!",
			wetuwn -1);

	gwaphics_wevew_addwess = dpm_tabwe_stawt + offsetof(SMU74_Discwete_DpmTabwe, MemowyWevew);

	PP_ASSEWT_WITH_CODE(0 == smu7_copy_bytes_to_smc(hwmgw, gwaphics_wevew_addwess,
				(uint8_t *)(&avfs_memowy_wevew_powawis10), sizeof(avfs_memowy_wevew_powawis10), 0x40000),
				"[AVFS][Powawis10_SetupGfxWvwStwuct] Copying of MCWK DPM tabwe faiwed!",
			wetuwn -1);

	/* MVDD Boot vawue - neccessawy fow getting wid of the hang that occuws duwing Mcwk DPM enabwement */

	gwaphics_wevew_addwess = dpm_tabwe_stawt + offsetof(SMU74_Discwete_DpmTabwe, BootMVdd);

	PP_ASSEWT_WITH_CODE(0 == smu7_copy_bytes_to_smc(hwmgw, gwaphics_wevew_addwess,
			(uint8_t *)(&u16_boot_mvdd), sizeof(u16_boot_mvdd), 0x40000),
			"[AVFS][Powawis10_SetupGfxWvwStwuct] Copying of DPM tabwe faiwed!",
			wetuwn -1);

	wetuwn 0;
}


static int powawis10_avfs_event_mgw(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_smumgw *smu_data = (stwuct smu7_smumgw *)(hwmgw->smu_backend);

	if (!hwmgw->avfs_suppowted)
		wetuwn 0;

	PP_ASSEWT_WITH_CODE(0 == powawis10_setup_gwaphics_wevew_stwuctuwe(hwmgw),
		"[AVFS][Powawis10_AVFSEventMgw] Couwd not Copy Gwaphics Wevew tabwe ovew to SMU",
		wetuwn -EINVAW);

	if (smu_data->avfs_btc_pawam > 1) {
		pw_info("[AVFS][Powawis10_AVFSEventMgw] AC BTC has not been successfuwwy vewified on Fiji. Thewe may be in this setting.");
		PP_ASSEWT_WITH_CODE(0 == smu7_setup_pww_viwus(hwmgw),
		"[AVFS][Powawis10_AVFSEventMgw] Couwd not setup Pww Viwus fow AVFS ",
		wetuwn -EINVAW);
	}

	PP_ASSEWT_WITH_CODE(0 == powawis10_pewfowm_btc(hwmgw),
				"[AVFS][Powawis10_AVFSEventMgw] Faiwuwe at SmuPowawis10_PewfowmBTC. AVFS Disabwed",
			 wetuwn -EINVAW);

	wetuwn 0;
}

static int powawis10_stawt_smu_in_pwotection_mode(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;

	/* Wait fow smc boot up */
	/* PHM_WAIT_VFPF_INDIWECT_FIEWD_UNEQUAW(smumgw, SMC_IND, WCU_UC_EVENTS, boot_seq_done, 0) */

	/* Assewt weset */
	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
					SMC_SYSCON_WESET_CNTW, wst_weg, 1);

	wesuwt = smu7_upwoad_smu_fiwmwawe_image(hwmgw);
	if (wesuwt != 0)
		wetuwn wesuwt;

	/* Cweaw status */
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixSMU_STATUS, 0);

	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
					SMC_SYSCON_CWOCK_CNTW_0, ck_disabwe, 0);

	/* De-assewt weset */
	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
					SMC_SYSCON_WESET_CNTW, wst_weg, 0);


	PHM_WAIT_VFPF_INDIWECT_FIEWD(hwmgw, SMC_IND, WCU_UC_EVENTS, INTEWWUPTS_ENABWED, 1);


	/* Caww Test SMU message with 0x20000 offset to twiggew SMU stawt */
	smu7_send_msg_to_smc_offset(hwmgw);

	/* Wait done bit to be set */
	/* Check pass/faiwed indicatow */

	PHM_WAIT_VFPF_INDIWECT_FIEWD_UNEQUAW(hwmgw, SMC_IND, SMU_STATUS, SMU_DONE, 0);

	if (1 != PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
						SMU_STATUS, SMU_PASS))
		PP_ASSEWT_WITH_CODE(fawse, "SMU Fiwmwawe stawt faiwed!", wetuwn -1);

	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixFIWMWAWE_FWAGS, 0);

	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
					SMC_SYSCON_WESET_CNTW, wst_weg, 1);

	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
					SMC_SYSCON_WESET_CNTW, wst_weg, 0);

	/* Wait fow fiwmwawe to initiawize */
	PHM_WAIT_VFPF_INDIWECT_FIEWD(hwmgw, SMC_IND, FIWMWAWE_FWAGS, INTEWWUPTS_ENABWED, 1);

	wetuwn wesuwt;
}

static int powawis10_stawt_smu_in_non_pwotection_mode(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;

	/* wait fow smc boot up */
	PHM_WAIT_VFPF_INDIWECT_FIEWD_UNEQUAW(hwmgw, SMC_IND, WCU_UC_EVENTS, boot_seq_done, 0);

	/* Cweaw fiwmwawe intewwupt enabwe fwag */
	/* PHM_WWITE_VFPF_INDIWECT_FIEWD(pSmuMgw, SMC_IND, SMC_SYSCON_MISC_CNTW, pwe_fetchew_en, 1); */
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
				ixFIWMWAWE_FWAGS, 0);

	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
					SMC_SYSCON_WESET_CNTW,
					wst_weg, 1);

	wesuwt = smu7_upwoad_smu_fiwmwawe_image(hwmgw);
	if (wesuwt != 0)
		wetuwn wesuwt;

	/* Set smc instwuct stawt point at 0x0 */
	smu7_pwogwam_jump_on_stawt(hwmgw);

	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
					SMC_SYSCON_CWOCK_CNTW_0, ck_disabwe, 0);

	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
					SMC_SYSCON_WESET_CNTW, wst_weg, 0);

	/* Wait fow fiwmwawe to initiawize */

	PHM_WAIT_VFPF_INDIWECT_FIEWD(hwmgw, SMC_IND,
					FIWMWAWE_FWAGS, INTEWWUPTS_ENABWED, 1);

	wetuwn wesuwt;
}

static int powawis10_stawt_smu(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);

	/* Onwy stawt SMC if SMC WAM is not wunning */
	if (!smu7_is_smc_wam_wunning(hwmgw) && hwmgw->not_vf) {
		smu_data->pwotected_mode = (uint8_t) (PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, SMU_FIWMWAWE, SMU_MODE));
		smu_data->smu7_data.secuwity_hawd_key = (uint8_t) (PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, SMU_FIWMWAWE, SMU_SEW));

		/* Check if SMU is wunning in pwotected mode */
		if (smu_data->pwotected_mode == 0)
			wesuwt = powawis10_stawt_smu_in_non_pwotection_mode(hwmgw);
		ewse
			wesuwt = powawis10_stawt_smu_in_pwotection_mode(hwmgw);

		if (wesuwt != 0)
			PP_ASSEWT_WITH_CODE(0, "Faiwed to woad SMU ucode.", wetuwn wesuwt);

		powawis10_avfs_event_mgw(hwmgw);
	}

	/* Setup SoftWegsStawt hewe fow wegistew wookup in case DummyBackEnd is used and PwocessFiwmwaweHeadew is not executed */
	smu7_wead_smc_swam_dwowd(hwmgw, SMU7_FIWMWAWE_HEADEW_WOCATION + offsetof(SMU74_Fiwmwawe_Headew, SoftWegistews),
					&(smu_data->smu7_data.soft_wegs_stawt), 0x40000);

	wesuwt = smu7_wequest_smu_woad_fw(hwmgw);

	wetuwn wesuwt;
}

static boow powawis10_is_hw_avfs_pwesent(stwuct pp_hwmgw *hwmgw)
{
	uint32_t efuse;

	efuse = cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixSMU_EFUSE_0 + (49*4));
	efuse &= 0x00000001;
	if (efuse)
		wetuwn twue;

	wetuwn fawse;
}

static int powawis10_smu_init(stwuct pp_hwmgw *hwmgw)
{
	stwuct powawis10_smumgw *smu_data;

	smu_data = kzawwoc(sizeof(stwuct powawis10_smumgw), GFP_KEWNEW);
	if (smu_data == NUWW)
		wetuwn -ENOMEM;

	hwmgw->smu_backend = smu_data;

	if (smu7_init(hwmgw)) {
		kfwee(smu_data);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int powawis10_get_dependency_vowt_by_cwk(stwuct pp_hwmgw *hwmgw,
		stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_tabwe,
		uint32_t cwock, SMU_VowtageWevew *vowtage, uint32_t *mvdd)
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
								(uint16_t)VDDC_VDDCI_DEWTA));
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
		*vowtage |= (dep_tabwe->entwies[i - 1].vddci * VOWTAGE_SCAWE) << VDDC_SHIFT;
	} ewse {
		vddci = phm_find_cwosest_vddci(&(data->vddci_vowtage_tabwe),
				(dep_tabwe->entwies[i].vddc -
						(uint16_t)VDDC_VDDCI_DEWTA));
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

static int powawis10_popuwate_bapm_pawametews_in_dpm_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);

	const stwuct powawis10_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;
	SMU74_Discwete_DpmTabwe  *tabwe = &(smu_data->smc_state_tabwe);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_cac_tdp_tabwe *cac_dtp_tabwe = tabwe_info->cac_dtp_tabwe;
	stwuct pp_advance_fan_contwow_pawametews *fan_tabwe =
			&hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews;
	int i, j, k;
	const uint16_t *pdef1;
	const uint16_t *pdef2;

	tabwe->DefauwtTdp = PP_HOST_TO_SMC_US((uint16_t)(cac_dtp_tabwe->usTDP * 128));
	tabwe->TawgetTdp  = PP_HOST_TO_SMC_US((uint16_t)(cac_dtp_tabwe->usTDP * 128));

	PP_ASSEWT_WITH_CODE(cac_dtp_tabwe->usTawgetOpewatingTemp <= 255,
				"Tawget Opewating Temp is out of Wange!",
				);

	tabwe->TempewatuweWimitEdge = PP_HOST_TO_SMC_US(
			cac_dtp_tabwe->usTawgetOpewatingTemp * 256);
	tabwe->TempewatuweWimitHotspot = PP_HOST_TO_SMC_US(
			cac_dtp_tabwe->usTempewatuweWimitHotspot * 256);
	tabwe->FanGainEdge = PP_HOST_TO_SMC_US(
			scawe_fan_gain_settings(fan_tabwe->usFanGainEdge));
	tabwe->FanGainHotspot = PP_HOST_TO_SMC_US(
			scawe_fan_gain_settings(fan_tabwe->usFanGainHotspot));

	pdef1 = defauwts->BAPMTI_W;
	pdef2 = defauwts->BAPMTI_WC;

	fow (i = 0; i < SMU74_DTE_ITEWATIONS; i++) {
		fow (j = 0; j < SMU74_DTE_SOUWCES; j++) {
			fow (k = 0; k < SMU74_DTE_SINKS; k++) {
				tabwe->BAPMTI_W[i][j][k] = PP_HOST_TO_SMC_US(*pdef1);
				tabwe->BAPMTI_WC[i][j][k] = PP_HOST_TO_SMC_US(*pdef2);
				pdef1++;
				pdef2++;
			}
		}
	}

	wetuwn 0;
}

static void powawis10_popuwate_zewo_wpm_pawametews(stwuct pp_hwmgw *hwmgw)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	SMU74_Discwete_DpmTabwe  *tabwe = &(smu_data->smc_state_tabwe);
	uint16_t fan_stop_temp =
		((uint16_t)hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucFanStopTempewatuwe) << 8;
	uint16_t fan_stawt_temp =
		((uint16_t)hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucFanStawtTempewatuwe) << 8;

	if (hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucEnabweZewoWPM) {
		tabwe->FanStawtTempewatuwe = PP_HOST_TO_SMC_US(fan_stawt_temp);
		tabwe->FanStopTempewatuwe = PP_HOST_TO_SMC_US(fan_stop_temp);
	}
}

static int powawis10_popuwate_svi_woad_wine(stwuct pp_hwmgw *hwmgw)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	const stwuct powawis10_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;

	smu_data->powew_tune_tabwe.SviWoadWineEn = defauwts->SviWoadWineEn;
	smu_data->powew_tune_tabwe.SviWoadWineVddC = defauwts->SviWoadWineVddC;
	smu_data->powew_tune_tabwe.SviWoadWineTwimVddC = 3;
	smu_data->powew_tune_tabwe.SviWoadWineOffsetVddC = 0;

	wetuwn 0;
}

static int powawis10_popuwate_tdc_wimit(stwuct pp_hwmgw *hwmgw)
{
	uint16_t tdc_wimit;
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	const stwuct powawis10_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;

	tdc_wimit = (uint16_t)(tabwe_info->cac_dtp_tabwe->usTDC * 128);
	smu_data->powew_tune_tabwe.TDC_VDDC_PkgWimit =
			CONVEWT_FWOM_HOST_TO_SMC_US(tdc_wimit);
	smu_data->powew_tune_tabwe.TDC_VDDC_ThwottweWeweaseWimitPewc =
			defauwts->TDC_VDDC_ThwottweWeweaseWimitPewc;
	smu_data->powew_tune_tabwe.TDC_MAWt = defauwts->TDC_MAWt;

	wetuwn 0;
}

static int powawis10_popuwate_dw8(stwuct pp_hwmgw *hwmgw, uint32_t fuse_tabwe_offset)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	const stwuct powawis10_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;
	uint32_t temp;

	if (smu7_wead_smc_swam_dwowd(hwmgw,
			fuse_tabwe_offset +
			offsetof(SMU74_Discwete_PmFuses, TdcWatewfawwCtw),
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

static int powawis10_popuwate_tempewatuwe_scawew(stwuct pp_hwmgw *hwmgw)
{
	int i;
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);

	/* Cuwwentwy not used. Set aww to zewo. */
	fow (i = 0; i < 16; i++)
		smu_data->powew_tune_tabwe.WPMWTempewatuweScawew[i] = 0;

	wetuwn 0;
}

static int powawis10_popuwate_fuzzy_fan(stwuct pp_hwmgw *hwmgw)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);

/* TO DO move to hwmgw */
	if ((hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanOutputSensitivity & (1 << 15))
		|| 0 == hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanOutputSensitivity)
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanOutputSensitivity =
			hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtFanOutputSensitivity;

	smu_data->powew_tune_tabwe.FuzzyFan_PwmSetDewta = PP_HOST_TO_SMC_US(
				hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanOutputSensitivity);
	wetuwn 0;
}

static int powawis10_popuwate_gnb_wpmw(stwuct pp_hwmgw *hwmgw)
{
	int i;
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);

	/* Cuwwentwy not used. Set aww to zewo. */
	fow (i = 0; i < 16; i++)
		smu_data->powew_tune_tabwe.GnbWPMW[i] = 0;

	wetuwn 0;
}

static int powawis10_popuwate_bapm_vddc_base_weakage_sidd(stwuct pp_hwmgw *hwmgw)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	uint16_t hi_sidd = smu_data->powew_tune_tabwe.BapmVddCBaseWeakageHiSidd;
	uint16_t wo_sidd = smu_data->powew_tune_tabwe.BapmVddCBaseWeakageWoSidd;
	stwuct phm_cac_tdp_tabwe *cac_tabwe = tabwe_info->cac_dtp_tabwe;

	hi_sidd = (uint16_t)(cac_tabwe->usHighCACWeakage / 100 * 256);
	wo_sidd = (uint16_t)(cac_tabwe->usWowCACWeakage / 100 * 256);

	smu_data->powew_tune_tabwe.BapmVddCBaseWeakageHiSidd =
			CONVEWT_FWOM_HOST_TO_SMC_US(hi_sidd);
	smu_data->powew_tune_tabwe.BapmVddCBaseWeakageWoSidd =
			CONVEWT_FWOM_HOST_TO_SMC_US(wo_sidd);

	wetuwn 0;
}

static int powawis10_popuwate_pm_fuses(stwuct pp_hwmgw *hwmgw)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	uint32_t pm_fuse_tabwe_offset;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_PowewContainment)) {
		if (smu7_wead_smc_swam_dwowd(hwmgw,
				SMU7_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU74_Fiwmwawe_Headew, PmFuseTabwe),
				&pm_fuse_tabwe_offset, SMC_WAM_END))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to get pm_fuse_tabwe_offset Faiwed!",
					wetuwn -EINVAW);

		if (powawis10_popuwate_svi_woad_wine(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate SviWoadWine Faiwed!",
					wetuwn -EINVAW);

		if (powawis10_popuwate_tdc_wimit(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate TDCWimit Faiwed!", wetuwn -EINVAW);

		if (powawis10_popuwate_dw8(hwmgw, pm_fuse_tabwe_offset))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate TdcWatewfawwCtw, "
					"WPMWTempewatuwe Min and Max Faiwed!",
					wetuwn -EINVAW);

		if (0 != powawis10_popuwate_tempewatuwe_scawew(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate WPMWTempewatuweScawew Faiwed!",
					wetuwn -EINVAW);

		if (powawis10_popuwate_fuzzy_fan(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate Fuzzy Fan Contwow pawametews Faiwed!",
					wetuwn -EINVAW);

		if (powawis10_popuwate_gnb_wpmw(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate GnbWPMW Faiwed!",
					wetuwn -EINVAW);

		if (powawis10_popuwate_bapm_vddc_base_weakage_sidd(hwmgw))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to popuwate BapmVddCBaseWeakage Hi and Wo "
					"Sidd Faiwed!", wetuwn -EINVAW);

		if (smu7_copy_bytes_to_smc(hwmgw, pm_fuse_tabwe_offset,
				(uint8_t *)&smu_data->powew_tune_tabwe,
				(sizeof(stwuct SMU74_Discwete_PmFuses) - 92), SMC_WAM_END))
			PP_ASSEWT_WITH_CODE(fawse,
					"Attempt to downwoad PmFuseTabwe Faiwed!",
					wetuwn -EINVAW);
	}
	wetuwn 0;
}

static int powawis10_popuwate_smc_mvdd_tabwe(stwuct pp_hwmgw *hwmgw,
			SMU74_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t count, wevew;

	if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->mvdd_contwow) {
		count = data->mvdd_vowtage_tabwe.count;
		if (count > SMU_MAX_SMIO_WEVEWS)
			count = SMU_MAX_SMIO_WEVEWS;
		fow (wevew = 0; wevew < count; wevew++) {
			tabwe->SmioTabwe2.Pattewn[wevew].Vowtage =
				PP_HOST_TO_SMC_US(data->mvdd_vowtage_tabwe.entwies[wevew].vawue * VOWTAGE_SCAWE);
			/* Index into DpmTabwe.Smio. Dwive bits fwom Smio entwy to get this vowtage wevew.*/
			tabwe->SmioTabwe2.Pattewn[wevew].Smio =
				(uint8_t) wevew;
			tabwe->Smio[wevew] |=
				data->mvdd_vowtage_tabwe.entwies[wevew].smio_wow;
		}
		tabwe->SmioMask2 = data->mvdd_vowtage_tabwe.mask_wow;

		tabwe->MvddWevewCount = (uint32_t) PP_HOST_TO_SMC_UW(count);
	}

	wetuwn 0;
}

static int powawis10_popuwate_smc_vddc_tabwe(stwuct pp_hwmgw *hwmgw,
					stwuct SMU74_Discwete_DpmTabwe *tabwe)
{
	uint32_t count, wevew;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	count = data->vddc_vowtage_tabwe.count;

	if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->vowtage_contwow) {
		if (count > SMU_MAX_SMIO_WEVEWS)
			count = SMU_MAX_SMIO_WEVEWS;
		fow (wevew = 0; wevew < count; ++wevew) {
			tabwe->SmioTabwe1.Pattewn[wevew].Vowtage =
				PP_HOST_TO_SMC_US(data->vddc_vowtage_tabwe.entwies[wevew].vawue * VOWTAGE_SCAWE);
			tabwe->SmioTabwe1.Pattewn[wevew].Smio = (uint8_t) wevew;

			tabwe->Smio[wevew] |= data->vddc_vowtage_tabwe.entwies[wevew].smio_wow;
		}

		tabwe->SmioMask1 = data->vddc_vowtage_tabwe.mask_wow;
	}

	wetuwn 0;
}

static int powawis10_popuwate_smc_vddci_tabwe(stwuct pp_hwmgw *hwmgw,
					stwuct SMU74_Discwete_DpmTabwe *tabwe)
{
	uint32_t count, wevew;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	count = data->vddci_vowtage_tabwe.count;

	if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->vddci_contwow) {
		if (count > SMU_MAX_SMIO_WEVEWS)
			count = SMU_MAX_SMIO_WEVEWS;
		fow (wevew = 0; wevew < count; ++wevew) {
			tabwe->SmioTabwe1.Pattewn[wevew].Vowtage =
				PP_HOST_TO_SMC_US(data->vddci_vowtage_tabwe.entwies[wevew].vawue * VOWTAGE_SCAWE);
			tabwe->SmioTabwe1.Pattewn[wevew].Smio = (uint8_t) wevew;

			tabwe->Smio[wevew] |= data->vddci_vowtage_tabwe.entwies[wevew].smio_wow;
		}

		tabwe->SmioMask1 = data->vddci_vowtage_tabwe.mask_wow;
	}

	wetuwn 0;
}

static int powawis10_popuwate_cac_tabwe(stwuct pp_hwmgw *hwmgw,
		stwuct SMU74_Discwete_DpmTabwe *tabwe)
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
		tabwe->BapmVddcVidWoSidd[count] = convewt_to_vid(wookup_tabwe->entwies[index].us_cac_wow);
		tabwe->BapmVddcVidHiSidd[count] = convewt_to_vid(wookup_tabwe->entwies[index].us_cac_mid);
		tabwe->BapmVddcVidHiSidd2[count] = convewt_to_vid(wookup_tabwe->entwies[index].us_cac_high);
	}

	wetuwn 0;
}

static int powawis10_popuwate_smc_vowtage_tabwes(stwuct pp_hwmgw *hwmgw,
		stwuct SMU74_Discwete_DpmTabwe *tabwe)
{
	powawis10_popuwate_smc_vddc_tabwe(hwmgw, tabwe);
	powawis10_popuwate_smc_vddci_tabwe(hwmgw, tabwe);
	powawis10_popuwate_smc_mvdd_tabwe(hwmgw, tabwe);
	powawis10_popuwate_cac_tabwe(hwmgw, tabwe);

	wetuwn 0;
}

static int powawis10_popuwate_uwv_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct SMU74_Discwete_Uwv *state)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct amdgpu_device *adev = hwmgw->adev;

	state->CcPwwDynWm = 0;
	state->CcPwwDynWm1 = 0;

	state->VddcOffset = (uint16_t) tabwe_info->us_uwv_vowtage_offset;
	state->VddcOffsetVid = (uint8_t)(tabwe_info->us_uwv_vowtage_offset *
			VOWTAGE_VID_OFFSET_SCAWE2 / VOWTAGE_VID_OFFSET_SCAWE1);

	if ((hwmgw->chip_id == CHIP_POWAWIS12) ||
	    ASICID_IS_P20(adev->pdev->device, adev->pdev->wevision) ||
	    ASICID_IS_P21(adev->pdev->device, adev->pdev->wevision) ||
	    ASICID_IS_P30(adev->pdev->device, adev->pdev->wevision) ||
	    ASICID_IS_P31(adev->pdev->device, adev->pdev->wevision))
		state->VddcPhase = data->vddc_phase_shed_contwow ^ 0x3;
	ewse
		state->VddcPhase = (data->vddc_phase_shed_contwow) ? 0 : 1;

	CONVEWT_FWOM_HOST_TO_SMC_UW(state->CcPwwDynWm);
	CONVEWT_FWOM_HOST_TO_SMC_UW(state->CcPwwDynWm1);
	CONVEWT_FWOM_HOST_TO_SMC_US(state->VddcOffset);

	wetuwn 0;
}

static int powawis10_popuwate_uwv_state(stwuct pp_hwmgw *hwmgw,
		stwuct SMU74_Discwete_DpmTabwe *tabwe)
{
	wetuwn powawis10_popuwate_uwv_wevew(hwmgw, &tabwe->Uwv);
}

static int powawis10_popuwate_smc_wink_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct SMU74_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	stwuct smu7_dpm_tabwe *dpm_tabwe = &data->dpm_tabwe;
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

/* To Do move to hwmgw */
	data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask =
			phm_get_dpm_wevew_enabwe_mask_vawue(&dpm_tabwe->pcie_speed_tabwe);

	wetuwn 0;
}


static void powawis10_get_scwk_wange_tabwe(stwuct pp_hwmgw *hwmgw,
				   SMU74_Discwete_DpmTabwe  *tabwe)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	uint32_t i, wef_cwk;

	stwuct pp_atom_ctww_scwk_wange_tabwe wange_tabwe_fwom_vbios = { { {0} } };

	wef_cwk = amdgpu_asic_get_xcwk((stwuct amdgpu_device *)hwmgw->adev);

	if (0 == atomctww_get_smc_scwk_wange_tabwe(hwmgw, &wange_tabwe_fwom_vbios)) {
		fow (i = 0; i < NUM_SCWK_WANGE; i++) {
			tabwe->ScwkFcwWangeTabwe[i].vco_setting = wange_tabwe_fwom_vbios.entwy[i].ucVco_setting;
			tabwe->ScwkFcwWangeTabwe[i].postdiv = wange_tabwe_fwom_vbios.entwy[i].ucPostdiv;
			tabwe->ScwkFcwWangeTabwe[i].fcw_pcc = wange_tabwe_fwom_vbios.entwy[i].usFcw_pcc;

			tabwe->ScwkFcwWangeTabwe[i].fcw_twans_uppew = wange_tabwe_fwom_vbios.entwy[i].usFcw_twans_uppew;
			tabwe->ScwkFcwWangeTabwe[i].fcw_twans_wowew = wange_tabwe_fwom_vbios.entwy[i].usWcw_twans_wowew;

			CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->ScwkFcwWangeTabwe[i].fcw_pcc);
			CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->ScwkFcwWangeTabwe[i].fcw_twans_uppew);
			CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->ScwkFcwWangeTabwe[i].fcw_twans_wowew);
		}
		wetuwn;
	}

	fow (i = 0; i < NUM_SCWK_WANGE; i++) {
		smu_data->wange_tabwe[i].twans_wowew_fwequency = (wef_cwk * Wange_Tabwe[i].fcw_twans_wowew) >> Wange_Tabwe[i].postdiv;
		smu_data->wange_tabwe[i].twans_uppew_fwequency = (wef_cwk * Wange_Tabwe[i].fcw_twans_uppew) >> Wange_Tabwe[i].postdiv;

		tabwe->ScwkFcwWangeTabwe[i].vco_setting = Wange_Tabwe[i].vco_setting;
		tabwe->ScwkFcwWangeTabwe[i].postdiv = Wange_Tabwe[i].postdiv;
		tabwe->ScwkFcwWangeTabwe[i].fcw_pcc = Wange_Tabwe[i].fcw_pcc;

		tabwe->ScwkFcwWangeTabwe[i].fcw_twans_uppew = Wange_Tabwe[i].fcw_twans_uppew;
		tabwe->ScwkFcwWangeTabwe[i].fcw_twans_wowew = Wange_Tabwe[i].fcw_twans_wowew;

		CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->ScwkFcwWangeTabwe[i].fcw_pcc);
		CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->ScwkFcwWangeTabwe[i].fcw_twans_uppew);
		CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->ScwkFcwWangeTabwe[i].fcw_twans_wowew);
	}
}

static int powawis10_cawcuwate_scwk_pawams(stwuct pp_hwmgw *hwmgw,
		uint32_t cwock, SMU_ScwkSetting *scwk_setting)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	const SMU74_Discwete_DpmTabwe *tabwe = &(smu_data->smc_state_tabwe);
	stwuct pp_atomctww_cwock_dividews_ai dividews;
	uint32_t wef_cwock;
	uint32_t pcc_tawget_pewcent, pcc_tawget_fweq, ss_tawget_pewcent, ss_tawget_fweq;
	uint8_t i;
	int wesuwt;
	uint64_t temp;

	scwk_setting->ScwkFwequency = cwock;
	/* get the engine cwock dividews fow this cwock vawue */
	wesuwt = atomctww_get_engine_pww_dividews_ai(hwmgw, cwock,  &dividews);
	if (wesuwt == 0) {
		scwk_setting->Fcw_int = dividews.usScwk_fcw_int;
		scwk_setting->Fcw_fwac = dividews.usScwk_fcw_fwac;
		scwk_setting->Pcc_fcw_int = dividews.usPcc_fcw_int;
		scwk_setting->PwwWange = dividews.ucScwkPwwWange;
		scwk_setting->Scwk_swew_wate = 0x400;
		scwk_setting->Pcc_up_swew_wate = dividews.usPcc_fcw_swew_fwac;
		scwk_setting->Pcc_down_swew_wate = 0xffff;
		scwk_setting->SSc_En = dividews.ucSscEnabwe;
		scwk_setting->Fcw1_int = dividews.usSsc_fcw1_int;
		scwk_setting->Fcw1_fwac = dividews.usSsc_fcw1_fwac;
		scwk_setting->Scwk_ss_swew_wate = dividews.usSsc_fcw_swew_fwac;
		wetuwn wesuwt;
	}

	wef_cwock = amdgpu_asic_get_xcwk((stwuct amdgpu_device *)hwmgw->adev);

	fow (i = 0; i < NUM_SCWK_WANGE; i++) {
		if (cwock > smu_data->wange_tabwe[i].twans_wowew_fwequency
		&& cwock <= smu_data->wange_tabwe[i].twans_uppew_fwequency) {
			scwk_setting->PwwWange = i;
			bweak;
		}
	}

	scwk_setting->Fcw_int = (uint16_t)((cwock << tabwe->ScwkFcwWangeTabwe[scwk_setting->PwwWange].postdiv) / wef_cwock);
	temp = cwock << tabwe->ScwkFcwWangeTabwe[scwk_setting->PwwWange].postdiv;
	temp <<= 0x10;
	do_div(temp, wef_cwock);
	scwk_setting->Fcw_fwac = temp & 0xffff;

	pcc_tawget_pewcent = 10; /*  Hawdcode 10% fow now. */
	pcc_tawget_fweq = cwock - (cwock * pcc_tawget_pewcent / 100);
	scwk_setting->Pcc_fcw_int = (uint16_t)((pcc_tawget_fweq << tabwe->ScwkFcwWangeTabwe[scwk_setting->PwwWange].postdiv) / wef_cwock);

	ss_tawget_pewcent = 2; /*  Hawdcode 2% fow now. */
	scwk_setting->SSc_En = 0;
	if (ss_tawget_pewcent) {
		scwk_setting->SSc_En = 1;
		ss_tawget_fweq = cwock - (cwock * ss_tawget_pewcent / 100);
		scwk_setting->Fcw1_int = (uint16_t)((ss_tawget_fweq << tabwe->ScwkFcwWangeTabwe[scwk_setting->PwwWange].postdiv) / wef_cwock);
		temp = ss_tawget_fweq << tabwe->ScwkFcwWangeTabwe[scwk_setting->PwwWange].postdiv;
		temp <<= 0x10;
		do_div(temp, wef_cwock);
		scwk_setting->Fcw1_fwac = temp & 0xffff;
	}

	wetuwn 0;
}

static int powawis10_popuwate_singwe_gwaphic_wevew(stwuct pp_hwmgw *hwmgw,
		uint32_t cwock, stwuct SMU74_Discwete_GwaphicsWevew *wevew)
{
	int wesuwt;
	/* PP_Cwocks minCwocks; */
	uint32_t mvdd;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	SMU_ScwkSetting cuww_scwk_setting = { 0 };
	phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_tabwe = NUWW;

	wesuwt = powawis10_cawcuwate_scwk_pawams(hwmgw, cwock, &cuww_scwk_setting);

	if (hwmgw->od_enabwed)
		vdd_dep_tabwe = (phm_ppt_v1_cwock_vowtage_dependency_tabwe *)&data->odn_dpm_tabwe.vdd_dependency_on_scwk;
	ewse
		vdd_dep_tabwe = tabwe_info->vdd_dep_on_scwk;

	/* popuwate gwaphics wevews */
	wesuwt = powawis10_get_dependency_vowt_by_cwk(hwmgw,
			vdd_dep_tabwe, cwock,
			&wevew->MinVowtage, &mvdd);

	PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"can not find VDDC vowtage vawue fow "
			"VDDC engine cwock dependency tabwe",
			wetuwn wesuwt);
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
	if (data->update_up_hyst)
		wevew->UpHyst = (uint8_t)data->up_hyst;
	if (data->update_down_hyst)
		wevew->DownHyst = (uint8_t)data->down_hyst;

	wevew->ScwkSetting = cuww_scwk_setting;

	CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->MinVowtage);
	CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->CcPwwDynWm);
	CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->CcPwwDynWm1);
	CONVEWT_FWOM_HOST_TO_SMC_US(wevew->ActivityWevew);
	CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->ScwkSetting.ScwkFwequency);
	CONVEWT_FWOM_HOST_TO_SMC_US(wevew->ScwkSetting.Fcw_int);
	CONVEWT_FWOM_HOST_TO_SMC_US(wevew->ScwkSetting.Fcw_fwac);
	CONVEWT_FWOM_HOST_TO_SMC_US(wevew->ScwkSetting.Pcc_fcw_int);
	CONVEWT_FWOM_HOST_TO_SMC_US(wevew->ScwkSetting.Scwk_swew_wate);
	CONVEWT_FWOM_HOST_TO_SMC_US(wevew->ScwkSetting.Pcc_up_swew_wate);
	CONVEWT_FWOM_HOST_TO_SMC_US(wevew->ScwkSetting.Pcc_down_swew_wate);
	CONVEWT_FWOM_HOST_TO_SMC_US(wevew->ScwkSetting.Fcw1_int);
	CONVEWT_FWOM_HOST_TO_SMC_US(wevew->ScwkSetting.Fcw1_fwac);
	CONVEWT_FWOM_HOST_TO_SMC_US(wevew->ScwkSetting.Scwk_ss_swew_wate);
	wetuwn 0;
}

static void powawis10_get_vddc_shawed_waiwinfo(stwuct pp_hwmgw *hwmgw)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	SMU74_Discwete_DpmTabwe *tabwe = &(smu_data->smc_state_tabwe);
	uint8_t shawed_waiw;

	if (!atomctww_get_vddc_shawed_waiwinfo(hwmgw, &shawed_waiw))
		tabwe->ShawedWaiws = shawed_waiw;
}

static int powawis10_popuwate_aww_gwaphic_wevews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *hw_data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	stwuct smu7_dpm_tabwe *dpm_tabwe = &hw_data->dpm_tabwe;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_pcie_tabwe *pcie_tabwe = tabwe_info->pcie_tabwe;
	uint8_t pcie_entwy_cnt = (uint8_t) hw_data->dpm_tabwe.pcie_speed_tabwe.count;
	int wesuwt = 0;
	uint32_t awway = smu_data->smu7_data.dpm_tabwe_stawt +
			offsetof(SMU74_Discwete_DpmTabwe, GwaphicsWevew);
	uint32_t awway_size = sizeof(stwuct SMU74_Discwete_GwaphicsWevew) *
			SMU74_MAX_WEVEWS_GWAPHICS;
	stwuct SMU74_Discwete_GwaphicsWevew *wevews =
			smu_data->smc_state_tabwe.GwaphicsWevew;
	uint32_t i, max_entwy;
	uint8_t hightest_pcie_wevew_enabwed = 0,
		wowest_pcie_wevew_enabwed = 0,
		mid_pcie_wevew_enabwed = 0,
		count = 0;
	stwuct amdgpu_device *adev = hwmgw->adev;
	pp_atomctww_cwock_dividews_vi dividews;
	uint32_t dpm0_scwkfwequency = wevews[0].ScwkSetting.ScwkFwequency;

	if (ASICID_IS_P20(adev->pdev->device, adev->pdev->wevision) ||
	    ASICID_IS_P30(adev->pdev->device, adev->pdev->wevision))
		powawis10_get_vddc_shawed_waiwinfo(hwmgw);

	powawis10_get_scwk_wange_tabwe(hwmgw, &(smu_data->smc_state_tabwe));

	fow (i = 0; i < dpm_tabwe->scwk_tabwe.count; i++) {

		wesuwt = powawis10_popuwate_singwe_gwaphic_wevew(hwmgw,
				dpm_tabwe->scwk_tabwe.dpm_wevews[i].vawue,
				&(smu_data->smc_state_tabwe.GwaphicsWevew[i]));
		if (wesuwt)
			wetuwn wesuwt;

		/* Making suwe onwy DPM wevew 0-1 have Deep Sweep Div ID popuwated. */
		if (i > 1)
			wevews[i].DeepSweepDivId = 0;
	}
	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_SPWWShutdownSuppowt)) {
		smu_data->smc_state_tabwe.GwaphicsWevew[0].ScwkSetting.SSc_En = 0;
		if (dpm0_scwkfwequency != wevews[0].ScwkSetting.ScwkFwequency) {
			wesuwt = atomctww_get_dfs_pww_dividews_vi(hwmgw,
					dpm_tabwe->scwk_tabwe.dpm_wevews[0].vawue,
					&dividews);
			PP_ASSEWT_WITH_CODE((0 == wesuwt),
					"can not find divide id fow scwk",
					wetuwn wesuwt);
			smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_SetGpuPwwDfsFowScwk,
					dividews.weaw_cwock < dpm_tabwe->scwk_tabwe.dpm_wevews[0].vawue ?
					dividews.pww_post_dividew - 1 : dividews.pww_post_dividew,
					NUWW);
		}
	}

	smu_data->smc_state_tabwe.GwaphicsDpmWevewCount =
			(uint8_t)dpm_tabwe->scwk_tabwe.count;
	hw_data->dpm_wevew_enabwe_mask.scwk_dpm_enabwe_mask =
			phm_get_dpm_wevew_enabwe_mask_vawue(&dpm_tabwe->scwk_tabwe);

	fow (i = 0; i < smu_data->smc_state_tabwe.GwaphicsDpmWevewCount; i++)
		smu_data->smc_state_tabwe.GwaphicsWevew[i].EnabwedFowActivity =
			(hw_data->dpm_wevew_enabwe_mask.scwk_dpm_enabwe_mask & (1 << i)) >> i;

	if (pcie_tabwe != NUWW) {
		PP_ASSEWT_WITH_CODE((1 <= pcie_entwy_cnt),
				"Thewe must be 1 ow mowe PCIE wevews defined in PPTabwe.",
				wetuwn -EINVAW);
		max_entwy = pcie_entwy_cnt - 1;
		fow (i = 0; i < dpm_tabwe->scwk_tabwe.count; i++)
			wevews[i].pcieDpmWevew =
					(uint8_t) ((i < max_entwy) ? i : max_entwy);
	} ewse {
		whiwe (hw_data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &&
				((hw_data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &
						(1 << (hightest_pcie_wevew_enabwed + 1))) != 0))
			hightest_pcie_wevew_enabwed++;

		whiwe (hw_data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &&
				((hw_data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &
						(1 << wowest_pcie_wevew_enabwed)) == 0))
			wowest_pcie_wevew_enabwed++;

		whiwe ((count < hightest_pcie_wevew_enabwed) &&
				((hw_data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask &
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


static int powawis10_popuwate_singwe_memowy_wevew(stwuct pp_hwmgw *hwmgw,
		uint32_t cwock, stwuct SMU74_Discwete_MemowyWevew *mem_wevew)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	int wesuwt = 0;
	uint32_t mcwk_stuttew_mode_thweshowd = 40000;
	phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_tabwe = NUWW;


	if (hwmgw->od_enabwed)
		vdd_dep_tabwe = (phm_ppt_v1_cwock_vowtage_dependency_tabwe *)&data->odn_dpm_tabwe.vdd_dependency_on_mcwk;
	ewse
		vdd_dep_tabwe = tabwe_info->vdd_dep_on_mcwk;

	if (vdd_dep_tabwe) {
		wesuwt = powawis10_get_dependency_vowt_by_cwk(hwmgw,
				vdd_dep_tabwe, cwock,
				&mem_wevew->MinVowtage, &mem_wevew->MinMvdd);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
				"can not find MinVddc vowtage vawue fwom memowy "
				"VDDC vowtage dependency tabwe", wetuwn wesuwt);
	}

	mem_wevew->McwkFwequency = cwock;
	mem_wevew->EnabwedFowThwottwe = 1;
	mem_wevew->EnabwedFowActivity = 0;
	mem_wevew->UpHyst = data->cuwwent_pwofiwe_setting.mcwk_up_hyst;
	mem_wevew->DownHyst = data->cuwwent_pwofiwe_setting.mcwk_down_hyst;
	mem_wevew->VowtageDownHyst = 0;
	mem_wevew->ActivityWevew = data->cuwwent_pwofiwe_setting.mcwk_activity;
	mem_wevew->StuttewEnabwe = fawse;
	mem_wevew->DispwayWatewmawk = PPSMC_DISPWAY_WATEWMAWK_WOW;

	data->dispway_timing.num_existing_dispways = hwmgw->dispway_config->num_dispway;
	data->dispway_timing.vwefwesh = hwmgw->dispway_config->vwefwesh;

	if (mcwk_stuttew_mode_thweshowd &&
		(cwock <= mcwk_stuttew_mode_thweshowd) &&
		(PHM_WEAD_FIEWD(hwmgw->device, DPG_PIPE_STUTTEW_CONTWOW,
				STUTTEW_ENABWE) & 0x1) &&
		(data->dispway_timing.num_existing_dispways <= 2) &&
		data->dispway_timing.num_existing_dispways)
		mem_wevew->StuttewEnabwe = twue;

	if (!wesuwt) {
		CONVEWT_FWOM_HOST_TO_SMC_UW(mem_wevew->MinMvdd);
		CONVEWT_FWOM_HOST_TO_SMC_UW(mem_wevew->McwkFwequency);
		CONVEWT_FWOM_HOST_TO_SMC_US(mem_wevew->ActivityWevew);
		CONVEWT_FWOM_HOST_TO_SMC_UW(mem_wevew->MinVowtage);
	}
	wetuwn wesuwt;
}

static int powawis10_popuwate_aww_memowy_wevews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *hw_data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	stwuct smu7_dpm_tabwe *dpm_tabwe = &hw_data->dpm_tabwe;
	int wesuwt;
	/* popuwate MCWK dpm tabwe to SMU7 */
	uint32_t awway = smu_data->smu7_data.dpm_tabwe_stawt +
			offsetof(SMU74_Discwete_DpmTabwe, MemowyWevew);
	uint32_t awway_size = sizeof(SMU74_Discwete_MemowyWevew) *
			SMU74_MAX_WEVEWS_MEMOWY;
	stwuct SMU74_Discwete_MemowyWevew *wevews =
			smu_data->smc_state_tabwe.MemowyWevew;
	uint32_t i;

	fow (i = 0; i < dpm_tabwe->mcwk_tabwe.count; i++) {
		PP_ASSEWT_WITH_CODE((0 != dpm_tabwe->mcwk_tabwe.dpm_wevews[i].vawue),
				"can not popuwate memowy wevew as memowy cwock is zewo",
				wetuwn -EINVAW);
		wesuwt = powawis10_popuwate_singwe_memowy_wevew(hwmgw,
				dpm_tabwe->mcwk_tabwe.dpm_wevews[i].vawue,
				&wevews[i]);
		if (i == dpm_tabwe->mcwk_tabwe.count - 1)
			wevews[i].DispwayWatewmawk = PPSMC_DISPWAY_WATEWMAWK_HIGH;
		if (wesuwt)
			wetuwn wesuwt;
	}

	smu_data->smc_state_tabwe.MemowyDpmWevewCount =
			(uint8_t)dpm_tabwe->mcwk_tabwe.count;
	hw_data->dpm_wevew_enabwe_mask.mcwk_dpm_enabwe_mask =
			phm_get_dpm_wevew_enabwe_mask_vawue(&dpm_tabwe->mcwk_tabwe);

	fow (i = 0; i < smu_data->smc_state_tabwe.MemowyDpmWevewCount; i++)
		smu_data->smc_state_tabwe.MemowyWevew[i].EnabwedFowActivity =
			(hw_data->dpm_wevew_enabwe_mask.mcwk_dpm_enabwe_mask & (1 << i)) >> i;

	/* wevew count wiww send to smc once at init smc tabwe and nevew change */
	wesuwt = smu7_copy_bytes_to_smc(hwmgw, awway, (uint8_t *)wevews,
			(uint32_t)awway_size, SMC_WAM_END);

	wetuwn wesuwt;
}

static int powawis10_popuwate_mvdd_vawue(stwuct pp_hwmgw *hwmgw,
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

static int powawis10_popuwate_smc_acpi_wevew(stwuct pp_hwmgw *hwmgw,
		SMU74_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = 0;
	uint32_t scwk_fwequency;
	const stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	SMIO_Pattewn vow_wevew;
	uint32_t mvdd;

	tabwe->ACPIWevew.Fwags &= ~PPSMC_SWSTATE_FWAG_DC;

	/* Get MinVowtage and Fwequency fwom DPM0,
	 * awweady convewted to SMC_UW */
	scwk_fwequency = data->vbios_boot_state.scwk_bootup_vawue;
	wesuwt = powawis10_get_dependency_vowt_by_cwk(hwmgw,
			tabwe_info->vdd_dep_on_scwk,
			scwk_fwequency,
			&tabwe->ACPIWevew.MinVowtage, &mvdd);
	PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"Cannot find ACPI VDDC vowtage vawue "
			"in Cwock Dependency Tabwe",
			);

	wesuwt = powawis10_cawcuwate_scwk_pawams(hwmgw, scwk_fwequency,  &(tabwe->ACPIWevew.ScwkSetting));
	PP_ASSEWT_WITH_CODE(wesuwt == 0, "Ewwow wetwieving Engine Cwock dividews fwom VBIOS.", wetuwn wesuwt);

	tabwe->ACPIWevew.DeepSweepDivId = 0;
	tabwe->ACPIWevew.CcPwwDynWm = 0;
	tabwe->ACPIWevew.CcPwwDynWm1 = 0;

	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.Fwags);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.MinVowtage);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CcPwwDynWm);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CcPwwDynWm1);

	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.ScwkSetting.ScwkFwequency);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->ACPIWevew.ScwkSetting.Fcw_int);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->ACPIWevew.ScwkSetting.Fcw_fwac);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->ACPIWevew.ScwkSetting.Pcc_fcw_int);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->ACPIWevew.ScwkSetting.Scwk_swew_wate);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->ACPIWevew.ScwkSetting.Pcc_up_swew_wate);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->ACPIWevew.ScwkSetting.Pcc_down_swew_wate);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->ACPIWevew.ScwkSetting.Fcw1_int);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->ACPIWevew.ScwkSetting.Fcw1_fwac);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->ACPIWevew.ScwkSetting.Scwk_ss_swew_wate);


	/* Get MinVowtage and Fwequency fwom DPM0, awweady convewted to SMC_UW */
	tabwe->MemowyACPIWevew.McwkFwequency = data->vbios_boot_state.mcwk_bootup_vawue;
	wesuwt = powawis10_get_dependency_vowt_by_cwk(hwmgw,
			tabwe_info->vdd_dep_on_mcwk,
			tabwe->MemowyACPIWevew.McwkFwequency,
			&tabwe->MemowyACPIWevew.MinVowtage, &mvdd);
	PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"Cannot find ACPI VDDCI vowtage vawue "
			"in Cwock Dependency Tabwe",
			);

	if (!((SMU7_VOWTAGE_CONTWOW_NONE == data->mvdd_contwow) ||
			(data->mcwk_dpm_key_disabwed)))
		powawis10_popuwate_mvdd_vawue(hwmgw,
				data->dpm_tabwe.mcwk_tabwe.dpm_wevews[0].vawue,
				&vow_wevew);

	if (0 == powawis10_popuwate_mvdd_vawue(hwmgw, 0, &vow_wevew))
		tabwe->MemowyACPIWevew.MinMvdd = PP_HOST_TO_SMC_UW(vow_wevew.Vowtage);
	ewse
		tabwe->MemowyACPIWevew.MinMvdd = 0;

	tabwe->MemowyACPIWevew.StuttewEnabwe = fawse;

	tabwe->MemowyACPIWevew.EnabwedFowThwottwe = 0;
	tabwe->MemowyACPIWevew.EnabwedFowActivity = 0;
	tabwe->MemowyACPIWevew.UpHyst = 0;
	tabwe->MemowyACPIWevew.DownHyst = 100;
	tabwe->MemowyACPIWevew.VowtageDownHyst = 0;
	/* To awign with the settings fwom othew OSes */
	tabwe->MemowyACPIWevew.ActivityWevew =
			PP_HOST_TO_SMC_US(data->cuwwent_pwofiwe_setting.scwk_activity);

	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->MemowyACPIWevew.McwkFwequency);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->MemowyACPIWevew.MinVowtage);

	wetuwn wesuwt;
}

static int powawis10_popuwate_smc_vce_wevew(stwuct pp_hwmgw *hwmgw,
		SMU74_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = -EINVAW;
	uint8_t count;
	stwuct pp_atomctww_cwock_dividews_vi dividews;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_mm_cwock_vowtage_dependency_tabwe *mm_tabwe =
			tabwe_info->mm_dep_tabwe;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t vddci;

	tabwe->VceWevewCount = (uint8_t)(mm_tabwe->count);
	tabwe->VceBootWevew = 0;

	fow (count = 0; count < tabwe->VceWevewCount; count++) {
		tabwe->VceWevew[count].Fwequency = mm_tabwe->entwies[count].ecwk;
		tabwe->VceWevew[count].MinVowtage = 0;
		tabwe->VceWevew[count].MinVowtage |=
				(mm_tabwe->entwies[count].vddc * VOWTAGE_SCAWE) << VDDC_SHIFT;

		if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->vddci_contwow)
			vddci = (uint32_t)phm_find_cwosest_vddci(&(data->vddci_vowtage_tabwe),
						mm_tabwe->entwies[count].vddc - VDDC_VDDCI_DEWTA);
		ewse if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vddci_contwow)
			vddci = mm_tabwe->entwies[count].vddc - VDDC_VDDCI_DEWTA;
		ewse
			vddci = (data->vbios_boot_state.vddci_bootup_vawue * VOWTAGE_SCAWE) << VDDCI_SHIFT;


		tabwe->VceWevew[count].MinVowtage |=
				(vddci * VOWTAGE_SCAWE) << VDDCI_SHIFT;
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

static int powawis10_popuwate_smc_samu_wevew(stwuct pp_hwmgw *hwmgw,
		SMU74_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = -EINVAW;
	uint8_t count;
	stwuct pp_atomctww_cwock_dividews_vi dividews;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_mm_cwock_vowtage_dependency_tabwe *mm_tabwe =
			tabwe_info->mm_dep_tabwe;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t vddci;

	tabwe->SamuWevewCount = (uint8_t)(mm_tabwe->count);
	tabwe->SamuBootWevew = 0;

	fow (count = 0; count < tabwe->SamuWevewCount; count++) {
		tabwe->SamuWevew[count].Fwequency = mm_tabwe->entwies[count].samcwock;
		tabwe->SamuWevew[count].MinVowtage |=
				(mm_tabwe->entwies[count].vddc * VOWTAGE_SCAWE) << VDDC_SHIFT;

		if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->vddci_contwow)
			vddci = (uint32_t)phm_find_cwosest_vddci(&(data->vddci_vowtage_tabwe),
						mm_tabwe->entwies[count].vddc - VDDC_VDDCI_DEWTA);
		ewse if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vddci_contwow)
			vddci = mm_tabwe->entwies[count].vddc - VDDC_VDDCI_DEWTA;
		ewse
			vddci = (data->vbios_boot_state.vddci_bootup_vawue * VOWTAGE_SCAWE) << VDDCI_SHIFT;


		tabwe->SamuWevew[count].MinVowtage |=
				(vddci * VOWTAGE_SCAWE) << VDDCI_SHIFT;
		tabwe->SamuWevew[count].MinVowtage |= 1 << PHASES_SHIFT;

		/*wetwieve dividew vawue fow VBIOS */
		wesuwt = atomctww_get_dfs_pww_dividews_vi(hwmgw,
				tabwe->SamuWevew[count].Fwequency, &dividews);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
				"can not find divide id fow VCE engine cwock",
				wetuwn wesuwt);

		tabwe->SamuWevew[count].Dividew = (uint8_t)dividews.pww_post_dividew;

		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SamuWevew[count].Fwequency);
		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SamuWevew[count].MinVowtage);
	}
	wetuwn wesuwt;
}

static int powawis10_popuwate_memowy_timing_pawametews(stwuct pp_hwmgw *hwmgw,
		int32_t eng_cwock, int32_t mem_cwock,
		SMU74_Discwete_MCAwbDwamTimingTabweEntwy *awb_wegs)
{
	uint32_t dwam_timing;
	uint32_t dwam_timing2;
	uint32_t buwst_time;
	int wesuwt;

	wesuwt = atomctww_set_engine_dwam_timings_wv770(hwmgw,
			eng_cwock, mem_cwock);
	PP_ASSEWT_WITH_CODE(wesuwt == 0,
			"Ewwow cawwing VBIOS to set DWAM_TIMING.", wetuwn wesuwt);

	dwam_timing = cgs_wead_wegistew(hwmgw->device, mmMC_AWB_DWAM_TIMING);
	dwam_timing2 = cgs_wead_wegistew(hwmgw->device, mmMC_AWB_DWAM_TIMING2);
	buwst_time = PHM_WEAD_FIEWD(hwmgw->device, MC_AWB_BUWST_TIME, STATE0);


	awb_wegs->McAwbDwamTiming  = PP_HOST_TO_SMC_UW(dwam_timing);
	awb_wegs->McAwbDwamTiming2 = PP_HOST_TO_SMC_UW(dwam_timing2);
	awb_wegs->McAwbBuwstTime   = (uint8_t)buwst_time;

	wetuwn 0;
}

static int powawis10_pwogwam_memowy_timing_pawametews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *hw_data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	stwuct SMU74_Discwete_MCAwbDwamTimingTabwe awb_wegs;
	uint32_t i, j;
	int wesuwt = 0;

	fow (i = 0; i < hw_data->dpm_tabwe.scwk_tabwe.count; i++) {
		fow (j = 0; j < hw_data->dpm_tabwe.mcwk_tabwe.count; j++) {
			wesuwt = powawis10_popuwate_memowy_timing_pawametews(hwmgw,
					hw_data->dpm_tabwe.scwk_tabwe.dpm_wevews[i].vawue,
					hw_data->dpm_tabwe.mcwk_tabwe.dpm_wevews[j].vawue,
					&awb_wegs.entwies[i][j]);
			if (wesuwt == 0 && i == 0)
				wesuwt = atomctww_set_ac_timing_ai(hwmgw, hw_data->dpm_tabwe.mcwk_tabwe.dpm_wevews[j].vawue, j);
			if (wesuwt != 0)
				wetuwn wesuwt;
		}
	}

	wesuwt = smu7_copy_bytes_to_smc(
			hwmgw,
			smu_data->smu7_data.awb_tabwe_stawt,
			(uint8_t *)&awb_wegs,
			sizeof(SMU74_Discwete_MCAwbDwamTimingTabwe),
			SMC_WAM_END);
	wetuwn wesuwt;
}

static int powawis10_popuwate_smc_uvd_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct SMU74_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = -EINVAW;
	uint8_t count;
	stwuct pp_atomctww_cwock_dividews_vi dividews;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_mm_cwock_vowtage_dependency_tabwe *mm_tabwe =
			tabwe_info->mm_dep_tabwe;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t vddci;

	tabwe->UvdWevewCount = (uint8_t)(mm_tabwe->count);
	tabwe->UvdBootWevew = 0;

	fow (count = 0; count < tabwe->UvdWevewCount; count++) {
		tabwe->UvdWevew[count].MinVowtage = 0;
		tabwe->UvdWevew[count].VcwkFwequency = mm_tabwe->entwies[count].vcwk;
		tabwe->UvdWevew[count].DcwkFwequency = mm_tabwe->entwies[count].dcwk;
		tabwe->UvdWevew[count].MinVowtage |= (mm_tabwe->entwies[count].vddc *
				VOWTAGE_SCAWE) << VDDC_SHIFT;

		if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->vddci_contwow)
			vddci = (uint32_t)phm_find_cwosest_vddci(&(data->vddci_vowtage_tabwe),
						mm_tabwe->entwies[count].vddc - VDDC_VDDCI_DEWTA);
		ewse if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vddci_contwow)
			vddci = mm_tabwe->entwies[count].vddc - VDDC_VDDCI_DEWTA;
		ewse
			vddci = (data->vbios_boot_state.vddci_bootup_vawue * VOWTAGE_SCAWE) << VDDCI_SHIFT;

		tabwe->UvdWevew[count].MinVowtage |= (vddci * VOWTAGE_SCAWE) << VDDCI_SHIFT;
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

static int powawis10_popuwate_smc_boot_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct SMU74_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = 0;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	tabwe->GwaphicsBootWevew = 0;
	tabwe->MemowyBootWevew = 0;

	/* find boot wevew fwom dpm tabwe */
	wesuwt = phm_find_boot_wevew(&(data->dpm_tabwe.scwk_tabwe),
			data->vbios_boot_state.scwk_bootup_vawue,
			(uint32_t *)&(tabwe->GwaphicsBootWevew));
	if (wesuwt) {
		tabwe->GwaphicsBootWevew = 0;
		wesuwt = 0;
	}

	wesuwt = phm_find_boot_wevew(&(data->dpm_tabwe.mcwk_tabwe),
			data->vbios_boot_state.mcwk_bootup_vawue,
			(uint32_t *)&(tabwe->MemowyBootWevew));
	if (wesuwt) {
		tabwe->MemowyBootWevew = 0;
		wesuwt = 0;
	}

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

static int powawis10_popuwate_smc_initaiwiaw_state(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *hw_data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	uint8_t count, wevew;

	count = (uint8_t)(tabwe_info->vdd_dep_on_scwk->count);

	fow (wevew = 0; wevew < count; wevew++) {
		if (tabwe_info->vdd_dep_on_scwk->entwies[wevew].cwk >=
				hw_data->vbios_boot_state.scwk_bootup_vawue) {
			smu_data->smc_state_tabwe.GwaphicsBootWevew = wevew;
			bweak;
		}
	}

	count = (uint8_t)(tabwe_info->vdd_dep_on_mcwk->count);
	fow (wevew = 0; wevew < count; wevew++) {
		if (tabwe_info->vdd_dep_on_mcwk->entwies[wevew].cwk >=
				hw_data->vbios_boot_state.mcwk_bootup_vawue) {
			smu_data->smc_state_tabwe.MemowyBootWevew = wevew;
			bweak;
		}
	}

	wetuwn 0;
}

#define STWAP_ASIC_WO_WSB    2168
#define STWAP_ASIC_WO_MSB    2175

static int powawis10_popuwate_cwock_stwetchew_data_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *scwk_tabwe =
			tabwe_info->vdd_dep_on_scwk;
	uint32_t wo, efuse, vowt_without_cks, vowt_with_cks, vawue;
	uint8_t i, stwetch_amount, vowt_offset = 0;

	stwetch_amount = (uint8_t)tabwe_info->cac_dtp_tabwe->usCwockStwetchAmount;

	/* Wead SMU_Eefuse to wead and cawcuwate WO and detewmine
	 * if the pawt is SS ow FF. if WO >= 1660MHz, pawt is FF.
	 */
	atomctww_wead_efuse(hwmgw, STWAP_ASIC_WO_WSB, STWAP_ASIC_WO_MSB, &efuse);
	wo = ((efuse * (data->wo_wange_maximum - data->wo_wange_minimum)) / 255) +
		data->wo_wange_minimum;

	/* Popuwate Scwk_CKS_mastewEn0_7 and Scwk_vowtageOffset */
	fow (i = 0; i < scwk_tabwe->count; i++) {
		smu_data->smc_state_tabwe.Scwk_CKS_mastewEn0_7 |=
				scwk_tabwe->entwies[i].cks_enabwe << i;
		if (hwmgw->chip_id == CHIP_POWAWIS10) {
			vowt_without_cks = (uint32_t)((2753594000U + (scwk_tabwe->entwies[i].cwk/100) * 136418 - (wo - 70) * 1000000) / \
						(2424180 - (scwk_tabwe->entwies[i].cwk/100) * 1132925/1000));
			vowt_with_cks = (uint32_t)((2797202000U + scwk_tabwe->entwies[i].cwk/100 * 3232 - (wo - 65) * 1000000) / \
					(2522480 - scwk_tabwe->entwies[i].cwk/100 * 115764/100));
		} ewse {
			vowt_without_cks = (uint32_t)((2416794800U + (scwk_tabwe->entwies[i].cwk/100) * 1476925/10 - (wo - 50) * 1000000) / \
						(2625416 - (scwk_tabwe->entwies[i].cwk/100) * (12586807/10000)));
			vowt_with_cks = (uint32_t)((2999656000U - scwk_tabwe->entwies[i].cwk/100 * 392803 - (wo - 44) * 1000000) / \
					(3422454 - scwk_tabwe->entwies[i].cwk/100 * (18886376/10000)));
		}

		if (vowt_without_cks >= vowt_with_cks)
			vowt_offset = (uint8_t)(((vowt_without_cks - vowt_with_cks +
					scwk_tabwe->entwies[i].cks_voffset) * 100 + 624) / 625);

		smu_data->smc_state_tabwe.Scwk_vowtageOffset[i] = vowt_offset;
	}

	smu_data->smc_state_tabwe.WdoWefSew = (tabwe_info->cac_dtp_tabwe->ucCKS_WDO_WEFSEW != 0) ? tabwe_info->cac_dtp_tabwe->ucCKS_WDO_WEFSEW : 5;

	/* Popuwate CKS Wookup Tabwe */
	if (stwetch_amount == 0 || stwetch_amount > 5) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_CwockStwetchew);
		PP_ASSEWT_WITH_CODE(fawse,
				"Stwetch Amount in PPTabwe not suppowted",
				wetuwn -EINVAW);
	}

	vawue = cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixPWW_CKS_CNTW);
	vawue &= 0xFFFFFFFE;
	cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, ixPWW_CKS_CNTW, vawue);

	wetuwn 0;
}

static int powawis10_popuwate_vw_config(stwuct pp_hwmgw *hwmgw,
		stwuct SMU74_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	uint16_t config;

	config = VW_MEWGED_WITH_VDDC;
	tabwe->VWConfig |= (config << VWCONF_VDDGFX_SHIFT);

	/* Set Vddc Vowtage Contwowwew */
	if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vowtage_contwow) {
		config = VW_SVI2_PWANE_1;
		tabwe->VWConfig |= config;
	} ewse if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->vowtage_contwow) {
		config = VW_SMIO_PATTEWN_1;
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
		if (config != VW_SVI2_PWANE_2) {
			config = VW_SVI2_PWANE_2;
			tabwe->VWConfig |= (config << VWCONF_MVDD_SHIFT);
			cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, smu_data->smu7_data.soft_wegs_stawt +
				offsetof(SMU74_SoftWegistews, AwwowMvddSwitch), 0x1);
		} ewse {
			config = VW_STATIC_VOWTAGE;
			tabwe->VWConfig |= (config << VWCONF_MVDD_SHIFT);
		}
	} ewse if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->mvdd_contwow) {
		config = VW_SMIO_PATTEWN_2;
		tabwe->VWConfig |= (config << VWCONF_MVDD_SHIFT);
		cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, smu_data->smu7_data.soft_wegs_stawt +
			offsetof(SMU74_SoftWegistews, AwwowMvddSwitch), 0x1);
	} ewse {
		config = VW_STATIC_VOWTAGE;
		tabwe->VWConfig |= (config << VWCONF_MVDD_SHIFT);
	}

	wetuwn 0;
}


static int powawis10_popuwate_avfs_pawametews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	stwuct amdgpu_device *adev = hwmgw->adev;

	SMU74_Discwete_DpmTabwe  *tabwe = &(smu_data->smc_state_tabwe);
	int wesuwt = 0;
	stwuct pp_atom_ctww__avfs_pawametews avfs_pawams = {0};
	AVFS_meanNsigma_t AVFS_meanNsigma = { {0} };
	AVFS_Scwk_Offset_t AVFS_ScwkOffset = { {0} };
	uint32_t tmp, i;

	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)hwmgw->pptabwe;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *scwk_tabwe =
			tabwe_info->vdd_dep_on_scwk;


	if (!hwmgw->avfs_suppowted)
		wetuwn 0;


	if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->vowtage_contwow) {
		hwmgw->avfs_suppowted = 0;
		wetuwn 0;
	}

	wesuwt = atomctww_get_avfs_infowmation(hwmgw, &avfs_pawams);

	if (0 == wesuwt) {
		if (ASICID_IS_P20(adev->pdev->device, adev->pdev->wevision) ||
		    ((hwmgw->chip_id == CHIP_POWAWIS12) && !ASICID_IS_P23(adev->pdev->device, adev->pdev->wevision)) ||
		    ASICID_IS_P21(adev->pdev->device, adev->pdev->wevision)) {
			avfs_pawams.ucEnabweAppwyAVFS_CKS_OFF_Vowtage = 1;
			if ((adev->pdev->device == 0x67ef && adev->pdev->wevision == 0xe5) ||
			    (adev->pdev->device == 0x67ff && adev->pdev->wevision == 0xef)) {
				if ((avfs_pawams.uwGB_VDWOOP_TABWE_CKSOFF_a0 == 0xEA522DD3) &&
				    (avfs_pawams.uwGB_VDWOOP_TABWE_CKSOFF_a1 == 0x5645A) &&
				    (avfs_pawams.uwGB_VDWOOP_TABWE_CKSOFF_a2 == 0x33F9E) &&
				    (avfs_pawams.uwAVFSGB_FUSE_TABWE_CKSOFF_m1 == 0xFFFFC5CC) &&
				    (avfs_pawams.usAVFSGB_FUSE_TABWE_CKSOFF_m2 == 0x1B1A) &&
				    (avfs_pawams.uwAVFSGB_FUSE_TABWE_CKSOFF_b == 0xFFFFFCED)) {
					avfs_pawams.uwGB_VDWOOP_TABWE_CKSOFF_a0   = 0xF718F1D4;
					avfs_pawams.uwGB_VDWOOP_TABWE_CKSOFF_a1   = 0x323FD;
					avfs_pawams.uwGB_VDWOOP_TABWE_CKSOFF_a2   = 0x1E455;
					avfs_pawams.uwAVFSGB_FUSE_TABWE_CKSOFF_m1 = 0;
					avfs_pawams.usAVFSGB_FUSE_TABWE_CKSOFF_m2 = 0;
					avfs_pawams.uwAVFSGB_FUSE_TABWE_CKSOFF_b  = 0x23;
				}
			} ewse if (hwmgw->chip_id == CHIP_POWAWIS12 && !ASICID_IS_P23(adev->pdev->device, adev->pdev->wevision)) {
				avfs_pawams.uwGB_VDWOOP_TABWE_CKSOFF_a0   = 0xF6B024DD;
				avfs_pawams.uwGB_VDWOOP_TABWE_CKSOFF_a1   = 0x3005E;
				avfs_pawams.uwGB_VDWOOP_TABWE_CKSOFF_a2   = 0x18A5F;
				avfs_pawams.uwAVFSGB_FUSE_TABWE_CKSOFF_m1 = 0x315;
				avfs_pawams.usAVFSGB_FUSE_TABWE_CKSOFF_m2 = 0xFED1;
				avfs_pawams.uwAVFSGB_FUSE_TABWE_CKSOFF_b  = 0x3B;
			} ewse if (ASICID_IS_P20(adev->pdev->device, adev->pdev->wevision)) {
				avfs_pawams.uwGB_VDWOOP_TABWE_CKSOFF_a0   = 0xF843B66B;
				avfs_pawams.uwGB_VDWOOP_TABWE_CKSOFF_a1   = 0x59CB5;
				avfs_pawams.uwGB_VDWOOP_TABWE_CKSOFF_a2   = 0xFFFF287F;
				avfs_pawams.uwAVFSGB_FUSE_TABWE_CKSOFF_m1 = 0;
				avfs_pawams.usAVFSGB_FUSE_TABWE_CKSOFF_m2 = 0xFF23;
				avfs_pawams.uwAVFSGB_FUSE_TABWE_CKSOFF_b  = 0x58;
			}
		}
	}

	if (0 == wesuwt) {
		tabwe->BTCGB_VDWOOP_TABWE[0].a0  = PP_HOST_TO_SMC_UW(avfs_pawams.uwGB_VDWOOP_TABWE_CKSON_a0);
		tabwe->BTCGB_VDWOOP_TABWE[0].a1  = PP_HOST_TO_SMC_UW(avfs_pawams.uwGB_VDWOOP_TABWE_CKSON_a1);
		tabwe->BTCGB_VDWOOP_TABWE[0].a2  = PP_HOST_TO_SMC_UW(avfs_pawams.uwGB_VDWOOP_TABWE_CKSON_a2);
		tabwe->BTCGB_VDWOOP_TABWE[1].a0  = PP_HOST_TO_SMC_UW(avfs_pawams.uwGB_VDWOOP_TABWE_CKSOFF_a0);
		tabwe->BTCGB_VDWOOP_TABWE[1].a1  = PP_HOST_TO_SMC_UW(avfs_pawams.uwGB_VDWOOP_TABWE_CKSOFF_a1);
		tabwe->BTCGB_VDWOOP_TABWE[1].a2  = PP_HOST_TO_SMC_UW(avfs_pawams.uwGB_VDWOOP_TABWE_CKSOFF_a2);
		tabwe->AVFSGB_VDWOOP_TABWE[0].m1 = PP_HOST_TO_SMC_UW(avfs_pawams.uwAVFSGB_FUSE_TABWE_CKSON_m1);
		tabwe->AVFSGB_VDWOOP_TABWE[0].m2 = PP_HOST_TO_SMC_US(avfs_pawams.usAVFSGB_FUSE_TABWE_CKSON_m2);
		tabwe->AVFSGB_VDWOOP_TABWE[0].b  = PP_HOST_TO_SMC_UW(avfs_pawams.uwAVFSGB_FUSE_TABWE_CKSON_b);
		tabwe->AVFSGB_VDWOOP_TABWE[0].m1_shift = 24;
		tabwe->AVFSGB_VDWOOP_TABWE[0].m2_shift  = 12;
		tabwe->AVFSGB_VDWOOP_TABWE[1].m1 = PP_HOST_TO_SMC_UW(avfs_pawams.uwAVFSGB_FUSE_TABWE_CKSOFF_m1);
		tabwe->AVFSGB_VDWOOP_TABWE[1].m2 = PP_HOST_TO_SMC_US(avfs_pawams.usAVFSGB_FUSE_TABWE_CKSOFF_m2);
		tabwe->AVFSGB_VDWOOP_TABWE[1].b  = PP_HOST_TO_SMC_UW(avfs_pawams.uwAVFSGB_FUSE_TABWE_CKSOFF_b);
		tabwe->AVFSGB_VDWOOP_TABWE[1].m1_shift = 24;
		tabwe->AVFSGB_VDWOOP_TABWE[1].m2_shift  = 12;
		tabwe->MaxVowtage                = PP_HOST_TO_SMC_US(avfs_pawams.usMaxVowtage_0_25mv);
		AVFS_meanNsigma.Aconstant[0]      = PP_HOST_TO_SMC_UW(avfs_pawams.uwAVFS_meanNsigma_Acontant0);
		AVFS_meanNsigma.Aconstant[1]      = PP_HOST_TO_SMC_UW(avfs_pawams.uwAVFS_meanNsigma_Acontant1);
		AVFS_meanNsigma.Aconstant[2]      = PP_HOST_TO_SMC_UW(avfs_pawams.uwAVFS_meanNsigma_Acontant2);
		AVFS_meanNsigma.DC_tow_sigma      = PP_HOST_TO_SMC_US(avfs_pawams.usAVFS_meanNsigma_DC_tow_sigma);
		AVFS_meanNsigma.Pwatfowm_mean     = PP_HOST_TO_SMC_US(avfs_pawams.usAVFS_meanNsigma_Pwatfowm_mean);
		AVFS_meanNsigma.PSM_Age_CompFactow = PP_HOST_TO_SMC_US(avfs_pawams.usPSM_Age_ComFactow);
		AVFS_meanNsigma.Pwatfowm_sigma     = PP_HOST_TO_SMC_US(avfs_pawams.usAVFS_meanNsigma_Pwatfowm_sigma);

		fow (i = 0; i < NUM_VFT_COWUMNS; i++) {
			AVFS_meanNsigma.Static_Vowtage_Offset[i] = (uint8_t)(scwk_tabwe->entwies[i].cks_voffset * 100 / 625);
			AVFS_ScwkOffset.Scwk_Offset[i] = PP_HOST_TO_SMC_US((uint16_t)(scwk_tabwe->entwies[i].scwk_offset) / 100);
		}

		wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
				SMU7_FIWMWAWE_HEADEW_WOCATION + offsetof(SMU74_Fiwmwawe_Headew, AvfsMeanNSigma),
				&tmp, SMC_WAM_END);

		smu7_copy_bytes_to_smc(hwmgw,
					tmp,
					(uint8_t *)&AVFS_meanNsigma,
					sizeof(AVFS_meanNsigma_t),
					SMC_WAM_END);

		wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
				SMU7_FIWMWAWE_HEADEW_WOCATION + offsetof(SMU74_Fiwmwawe_Headew, AvfsScwkOffsetTabwe),
				&tmp, SMC_WAM_END);
		smu7_copy_bytes_to_smc(hwmgw,
					tmp,
					(uint8_t *)&AVFS_ScwkOffset,
					sizeof(AVFS_Scwk_Offset_t),
					SMC_WAM_END);

		data->avfs_vdwoop_ovewwide_setting = (avfs_pawams.ucEnabweGB_VDWOOP_TABWE_CKSON << BTCGB0_Vdwoop_Enabwe_SHIFT) |
						(avfs_pawams.ucEnabweGB_VDWOOP_TABWE_CKSOFF << BTCGB1_Vdwoop_Enabwe_SHIFT) |
						(avfs_pawams.ucEnabweGB_FUSE_TABWE_CKSON << AVFSGB0_Vdwoop_Enabwe_SHIFT) |
						(avfs_pawams.ucEnabweGB_FUSE_TABWE_CKSOFF << AVFSGB1_Vdwoop_Enabwe_SHIFT);
		data->appwy_avfs_cks_off_vowtage = avfs_pawams.ucEnabweAppwyAVFS_CKS_OFF_Vowtage == 1;
	}
	wetuwn wesuwt;
}

static void powawis10_initiawize_powew_tune_defauwts(stwuct pp_hwmgw *hwmgw)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	stwuct  phm_ppt_v1_infowmation *tabwe_info =
			(stwuct  phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	if (tabwe_info &&
			tabwe_info->cac_dtp_tabwe->usPowewTuneDataSetID <= POWEWTUNE_DEFAUWT_SET_MAX &&
			tabwe_info->cac_dtp_tabwe->usPowewTuneDataSetID)
		smu_data->powew_tune_defauwts =
				&powawis10_powew_tune_data_set_awway
				[tabwe_info->cac_dtp_tabwe->usPowewTuneDataSetID - 1];
	ewse
		smu_data->powew_tune_defauwts = &powawis10_powew_tune_data_set_awway[0];

}

static int powawis10_init_smc_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	stwuct smu7_hwmgw *hw_data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);

	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct SMU74_Discwete_DpmTabwe *tabwe = &(smu_data->smc_state_tabwe);
	uint8_t i;
	stwuct pp_atomctww_gpio_pin_assignment gpio_pin;
	pp_atomctww_cwock_dividews_vi dividews;
	stwuct phm_ppt_v1_gpio_tabwe *gpio_tabwe = tabwe_info->gpio_tabwe;

	powawis10_initiawize_powew_tune_defauwts(hwmgw);

	if (SMU7_VOWTAGE_CONTWOW_NONE != hw_data->vowtage_contwow)
		powawis10_popuwate_smc_vowtage_tabwes(hwmgw, tabwe);

	tabwe->SystemFwags = 0;
	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_AutomaticDCTwansition))
		tabwe->SystemFwags |= PPSMC_SYSTEMFWAG_GPIO_DC;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_StepVddc))
		tabwe->SystemFwags |= PPSMC_SYSTEMFWAG_STEPVDDC;

	if (hw_data->is_memowy_gddw5)
		tabwe->SystemFwags |= PPSMC_SYSTEMFWAG_GDDW5;

	if (hw_data->uwv_suppowted && tabwe_info->us_uwv_vowtage_offset) {
		wesuwt = powawis10_popuwate_uwv_state(hwmgw, tabwe);
		PP_ASSEWT_WITH_CODE(0 == wesuwt,
				"Faiwed to initiawize UWV state!", wetuwn wesuwt);
		cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
				ixCG_UWV_PAWAMETEW, SMU7_CGUWVPAWAMETEW_DFWT);
	}

	wesuwt = powawis10_popuwate_smc_wink_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize Wink Wevew!", wetuwn wesuwt);

	wesuwt = powawis10_popuwate_aww_gwaphic_wevews(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize Gwaphics Wevew!", wetuwn wesuwt);

	wesuwt = powawis10_popuwate_aww_memowy_wevews(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize Memowy Wevew!", wetuwn wesuwt);

	wesuwt = powawis10_popuwate_smc_acpi_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize ACPI Wevew!", wetuwn wesuwt);

	wesuwt = powawis10_popuwate_smc_vce_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize VCE Wevew!", wetuwn wesuwt);

	wesuwt = powawis10_popuwate_smc_samu_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize SAMU Wevew!", wetuwn wesuwt);

	/* Since onwy the initiaw state is compwetewy set up at this point
	 * (the othew states awe just copies of the boot state) we onwy
	 * need to popuwate the  AWB settings fow the initiaw state.
	 */
	wesuwt = powawis10_pwogwam_memowy_timing_pawametews(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to Wwite AWB settings fow the initiaw state.", wetuwn wesuwt);

	wesuwt = powawis10_popuwate_smc_uvd_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize UVD Wevew!", wetuwn wesuwt);

	wesuwt = powawis10_popuwate_smc_boot_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize Boot Wevew!", wetuwn wesuwt);

	wesuwt = powawis10_popuwate_smc_initaiwiaw_state(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize Boot State!", wetuwn wesuwt);

	wesuwt = powawis10_popuwate_bapm_pawametews_in_dpm_tabwe(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to popuwate BAPM Pawametews!", wetuwn wesuwt);

	powawis10_popuwate_zewo_wpm_pawametews(hwmgw);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_CwockStwetchew)) {
		wesuwt = powawis10_popuwate_cwock_stwetchew_data_tabwe(hwmgw);
		PP_ASSEWT_WITH_CODE(0 == wesuwt,
				"Faiwed to popuwate Cwock Stwetchew Data Tabwe!",
				wetuwn wesuwt);
	}

	wesuwt = powawis10_popuwate_avfs_pawametews(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt, "Faiwed to popuwate AVFS Pawametews!", wetuwn wesuwt;);

	tabwe->CuwwScwkPwwWange = 0xff;
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
	tabwe->PCIeBootWinkWevew = hw_data->dpm_tabwe.pcie_speed_tabwe.count;
	tabwe->PCIeGenIntewvaw = 1;
	tabwe->VWConfig = 0;

	wesuwt = powawis10_popuwate_vw_config(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to popuwate VWConfig setting!", wetuwn wesuwt);
	hw_data->vw_config = tabwe->VWConfig;
	tabwe->ThewmGpio = 17;
	tabwe->ScwkStepSize = 0x4000;

	if (atomctww_get_pp_assign_pin(hwmgw, VDDC_VWHOT_GPIO_PINID, &gpio_pin)) {
		tabwe->VWHotGpio = gpio_pin.uc_gpio_pin_bit_shift;
		if (gpio_tabwe)
			tabwe->VWHotWevew = gpio_tabwe->vwhot_twiggewed_scwk_dpm_index;
	} ewse {
		tabwe->VWHotGpio = SMU7_UNUSED_GPIO_PIN;
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_WeguwatowHot);
	}

	if (atomctww_get_pp_assign_pin(hwmgw, PP_AC_DC_SWITCH_GPIO_PINID,
			&gpio_pin)) {
		tabwe->AcDcGpio = gpio_pin.uc_gpio_pin_bit_shift;
		if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_AutomaticDCTwansition) &&
		    !smum_send_msg_to_smc(hwmgw, PPSMC_MSG_UseNewGPIOScheme, NUWW))
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_SMCtoPPWIBAcdcGpioScheme);
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
		tabwe->ThewmOutPowawity = (0 == (cgs_wead_wegistew(hwmgw->device, mmGPIOPAD_A)
					& (1 << gpio_pin.uc_gpio_pin_bit_shift))) ? 1:0;
		tabwe->ThewmOutMode = SMU7_THEWM_OUT_MODE_THEWM_ONWY;

		/* if wequiwed, combine VWHot/PCC with thewmaw out GPIO */
		if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_WeguwatowHot)
		&& phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_CombinePCCWithThewmawSignaw))
			tabwe->ThewmOutMode = SMU7_THEWM_OUT_MODE_THEWM_VWHOT;
	} ewse {
		tabwe->ThewmOutGpio = 17;
		tabwe->ThewmOutPowawity = 1;
		tabwe->ThewmOutMode = SMU7_THEWM_OUT_MODE_DISABWE;
	}

	/* Popuwate BIF_SCWK wevews into SMC DPM tabwe */
	fow (i = 0; i <= hw_data->dpm_tabwe.pcie_speed_tabwe.count; i++) {
		wesuwt = atomctww_get_dfs_pww_dividews_vi(hwmgw, smu_data->bif_scwk_tabwe[i], &dividews);
		PP_ASSEWT_WITH_CODE((wesuwt == 0), "Can not find DFS divide id fow Scwk", wetuwn wesuwt);

		if (i == 0)
			tabwe->Uwv.BifScwkDfs = PP_HOST_TO_SMC_US((USHOWT)(dividews.pww_post_dividew));
		ewse
			tabwe->WinkWevew[i-1].BifScwkDfs = PP_HOST_TO_SMC_US((USHOWT)(dividews.pww_post_dividew));
	}

	fow (i = 0; i < SMU74_MAX_ENTWIES_SMIO; i++)
		tabwe->Smio[i] = PP_HOST_TO_SMC_UW(tabwe->Smio[i]);

	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SystemFwags);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->VWConfig);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SmioMask1);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SmioMask2);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ScwkStepSize);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->CuwwScwkPwwWange);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->TempewatuweWimitHigh);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->TempewatuweWimitWow);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->VowtageWesponseTime);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->PhaseWesponseTime);

	/* Upwoad aww dpm data to SMC memowy.(dpm wevew, dpm wevew count etc) */
	wesuwt = smu7_copy_bytes_to_smc(hwmgw,
			smu_data->smu7_data.dpm_tabwe_stawt +
			offsetof(SMU74_Discwete_DpmTabwe, SystemFwags),
			(uint8_t *)&(tabwe->SystemFwags),
			sizeof(SMU74_Discwete_DpmTabwe) - 3 * sizeof(SMU74_PIDContwowwew),
			SMC_WAM_END);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to upwoad dpm data to SMC memowy!", wetuwn wesuwt);

	wesuwt = powawis10_popuwate_pm_fuses(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to  popuwate PM fuses to SMC memowy!", wetuwn wesuwt);

	wetuwn 0;
}

static int powawis10_pwogwam_mem_timing_pawametews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (data->need_update_smu7_dpm_tabwe &
		(DPMTABWE_OD_UPDATE_SCWK + DPMTABWE_OD_UPDATE_MCWK))
		wetuwn powawis10_pwogwam_memowy_timing_pawametews(hwmgw);

	wetuwn 0;
}

static int powawis10_thewmaw_avfs_enabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (!hwmgw->avfs_suppowted)
		wetuwn 0;

	smum_send_msg_to_smc_with_pawametew(hwmgw,
			PPSMC_MSG_SetGBDwoopSettings, data->avfs_vdwoop_ovewwide_setting,
			NUWW);

	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_EnabweAvfs, NUWW);

	/* Appwy avfs cks-off vowtages to avoid the ovewshoot
	 * when switching to the highest scwk fwequency
	 */
	if (data->appwy_avfs_cks_off_vowtage)
		smum_send_msg_to_smc(hwmgw, PPSMC_MSG_AppwyAvfsCksOffVowtage, NUWW);

	wetuwn 0;
}

static int powawis10_thewmaw_setup_fan_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	SMU74_Discwete_FanTabwe fan_tabwe = { FDO_MODE_HAWDWAWE };
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

	/* use hawdwawe fan contwow */
	if (hwmgw->thewmaw_contwowwew.use_hw_fan_contwow)
		wetuwn 0;

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

static int powawis10_update_uvd_smc_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	uint32_t mm_boot_wevew_offset, mm_boot_wevew_vawue;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	smu_data->smc_state_tabwe.UvdBootWevew = 0;
	if (tabwe_info->mm_dep_tabwe->count > 0)
		smu_data->smc_state_tabwe.UvdBootWevew =
				(uint8_t) (tabwe_info->mm_dep_tabwe->count - 1);
	mm_boot_wevew_offset = smu_data->smu7_data.dpm_tabwe_stawt + offsetof(SMU74_Discwete_DpmTabwe,
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

static int powawis10_update_vce_smc_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
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
					offsetof(SMU74_Discwete_DpmTabwe, VceBootWevew);
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

static int powawis10_update_bif_smc_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	stwuct phm_ppt_v1_pcie_tabwe *pcie_tabwe = tabwe_info->pcie_tabwe;
	int max_entwy, i;

	max_entwy = (SMU74_MAX_WEVEWS_WINK < pcie_tabwe->count) ?
						SMU74_MAX_WEVEWS_WINK :
						pcie_tabwe->count;
	/* Setup BIF_SCWK wevews */
	fow (i = 0; i < max_entwy; i++)
		smu_data->bif_scwk_tabwe[i] = pcie_tabwe->entwies[i].pcie_scwk;
	wetuwn 0;
}

static int powawis10_update_smc_tabwe(stwuct pp_hwmgw *hwmgw, uint32_t type)
{
	switch (type) {
	case SMU_UVD_TABWE:
		powawis10_update_uvd_smc_tabwe(hwmgw);
		bweak;
	case SMU_VCE_TABWE:
		powawis10_update_vce_smc_tabwe(hwmgw);
		bweak;
	case SMU_BIF_TABWE:
		powawis10_update_bif_smc_tabwe(hwmgw);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int powawis10_update_scwk_thweshowd(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);

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
				offsetof(SMU74_Discwete_DpmTabwe,
					WowScwkIntewwuptThweshowd),
				(uint8_t *)&wow_scwk_intewwupt_thweshowd,
				sizeof(uint32_t),
				SMC_WAM_END);
	}
	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			"Faiwed to update SCWK thweshowd!", wetuwn wesuwt);

	wesuwt = powawis10_pwogwam_mem_timing_pawametews(hwmgw);
	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			"Faiwed to pwogwam memowy timing pawametews!",
			);

	wetuwn wesuwt;
}

static uint32_t powawis10_get_offsetof(uint32_t type, uint32_t membew)
{
	switch (type) {
	case SMU_SoftWegistews:
		switch (membew) {
		case HandshakeDisabwes:
			wetuwn offsetof(SMU74_SoftWegistews, HandshakeDisabwes);
		case VowtageChangeTimeout:
			wetuwn offsetof(SMU74_SoftWegistews, VowtageChangeTimeout);
		case AvewageGwaphicsActivity:
			wetuwn offsetof(SMU74_SoftWegistews, AvewageGwaphicsActivity);
		case AvewageMemowyActivity:
			wetuwn offsetof(SMU74_SoftWegistews, AvewageMemowyActivity);
		case PweVBwankGap:
			wetuwn offsetof(SMU74_SoftWegistews, PweVBwankGap);
		case VBwankTimeout:
			wetuwn offsetof(SMU74_SoftWegistews, VBwankTimeout);
		case UcodeWoadStatus:
			wetuwn offsetof(SMU74_SoftWegistews, UcodeWoadStatus);
		case DWAM_WOG_ADDW_H:
			wetuwn offsetof(SMU74_SoftWegistews, DWAM_WOG_ADDW_H);
		case DWAM_WOG_ADDW_W:
			wetuwn offsetof(SMU74_SoftWegistews, DWAM_WOG_ADDW_W);
		case DWAM_WOG_PHY_ADDW_H:
			wetuwn offsetof(SMU74_SoftWegistews, DWAM_WOG_PHY_ADDW_H);
		case DWAM_WOG_PHY_ADDW_W:
			wetuwn offsetof(SMU74_SoftWegistews, DWAM_WOG_PHY_ADDW_W);
		case DWAM_WOG_BUFF_SIZE:
			wetuwn offsetof(SMU74_SoftWegistews, DWAM_WOG_BUFF_SIZE);
		}
		bweak;
	case SMU_Discwete_DpmTabwe:
		switch (membew) {
		case UvdBootWevew:
			wetuwn offsetof(SMU74_Discwete_DpmTabwe, UvdBootWevew);
		case VceBootWevew:
			wetuwn offsetof(SMU74_Discwete_DpmTabwe, VceBootWevew);
		case WowScwkIntewwuptThweshowd:
			wetuwn offsetof(SMU74_Discwete_DpmTabwe, WowScwkIntewwuptThweshowd);
		}
		bweak;
	}
	pw_wawn("can't get the offset of type %x membew %x\n", type, membew);
	wetuwn 0;
}

static uint32_t powawis10_get_mac_definition(uint32_t vawue)
{
	switch (vawue) {
	case SMU_MAX_WEVEWS_GWAPHICS:
		wetuwn SMU74_MAX_WEVEWS_GWAPHICS;
	case SMU_MAX_WEVEWS_MEMOWY:
		wetuwn SMU74_MAX_WEVEWS_MEMOWY;
	case SMU_MAX_WEVEWS_WINK:
		wetuwn SMU74_MAX_WEVEWS_WINK;
	case SMU_MAX_ENTWIES_SMIO:
		wetuwn SMU74_MAX_ENTWIES_SMIO;
	case SMU_MAX_WEVEWS_VDDC:
		wetuwn SMU74_MAX_WEVEWS_VDDC;
	case SMU_MAX_WEVEWS_VDDGFX:
		wetuwn SMU74_MAX_WEVEWS_VDDGFX;
	case SMU_MAX_WEVEWS_VDDCI:
		wetuwn SMU74_MAX_WEVEWS_VDDCI;
	case SMU_MAX_WEVEWS_MVDD:
		wetuwn SMU74_MAX_WEVEWS_MVDD;
	case SMU_UVD_MCWK_HANDSHAKE_DISABWE:
		wetuwn SMU7_UVD_MCWK_HANDSHAKE_DISABWE |
				SMU7_VCE_MCWK_HANDSHAKE_DISABWE;
	}

	pw_wawn("can't get the mac of %x\n", vawue);
	wetuwn 0;
}

static int powawis10_pwocess_fiwmwawe_headew(stwuct pp_hwmgw *hwmgw)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t tmp;
	int wesuwt;
	boow ewwow = fawse;

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
			SMU7_FIWMWAWE_HEADEW_WOCATION +
			offsetof(SMU74_Fiwmwawe_Headew, DpmTabwe),
			&tmp, SMC_WAM_END);

	if (0 == wesuwt)
		smu_data->smu7_data.dpm_tabwe_stawt = tmp;

	ewwow |= (0 != wesuwt);

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
			SMU7_FIWMWAWE_HEADEW_WOCATION +
			offsetof(SMU74_Fiwmwawe_Headew, SoftWegistews),
			&tmp, SMC_WAM_END);

	if (!wesuwt) {
		data->soft_wegs_stawt = tmp;
		smu_data->smu7_data.soft_wegs_stawt = tmp;
	}

	ewwow |= (0 != wesuwt);

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
			SMU7_FIWMWAWE_HEADEW_WOCATION +
			offsetof(SMU74_Fiwmwawe_Headew, mcWegistewTabwe),
			&tmp, SMC_WAM_END);

	if (!wesuwt)
		smu_data->smu7_data.mc_weg_tabwe_stawt = tmp;

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
			SMU7_FIWMWAWE_HEADEW_WOCATION +
			offsetof(SMU74_Fiwmwawe_Headew, FanTabwe),
			&tmp, SMC_WAM_END);

	if (!wesuwt)
		smu_data->smu7_data.fan_tabwe_stawt = tmp;

	ewwow |= (0 != wesuwt);

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
			SMU7_FIWMWAWE_HEADEW_WOCATION +
			offsetof(SMU74_Fiwmwawe_Headew, mcAwbDwamTimingTabwe),
			&tmp, SMC_WAM_END);

	if (!wesuwt)
		smu_data->smu7_data.awb_tabwe_stawt = tmp;

	ewwow |= (0 != wesuwt);

	wesuwt = smu7_wead_smc_swam_dwowd(hwmgw,
			SMU7_FIWMWAWE_HEADEW_WOCATION +
			offsetof(SMU74_Fiwmwawe_Headew, Vewsion),
			&tmp, SMC_WAM_END);

	if (!wesuwt)
		hwmgw->micwocode_vewsion_info.SMC = tmp;

	ewwow |= (0 != wesuwt);

	wetuwn ewwow ? -1 : 0;
}

static uint8_t powawis10_get_memowy_modiwe_index(stwuct pp_hwmgw *hwmgw)
{
	wetuwn (uint8_t) (0xFF & (cgs_wead_wegistew(hwmgw->device, mmBIOS_SCWATCH_4) >> 16));
}

static int powawis10_initiawize_mc_weg_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)(hwmgw->smu_backend);
	pp_atomctww_mc_weg_tabwe *mc_weg_tabwe = &smu_data->mc_weg_tabwe;
	uint8_t moduwe_index = powawis10_get_memowy_modiwe_index(hwmgw);

	memset(mc_weg_tabwe, 0, sizeof(pp_atomctww_mc_weg_tabwe));

	wetuwn atomctww_initiawize_mc_weg_tabwe_v2_2(hwmgw, moduwe_index, mc_weg_tabwe);
}

static boow powawis10_is_dpm_wunning(stwuct pp_hwmgw *hwmgw)
{
	wetuwn (1 == PHM_WEAD_INDIWECT_FIEWD(hwmgw->device,
			CGS_IND_WEG__SMC, FEATUWE_STATUS, VOWTAGE_CONTWOWWEW_ON))
			? twue : fawse;
}

static int powawis10_update_dpm_settings(stwuct pp_hwmgw *hwmgw,
				void *pwofiwe_setting)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct powawis10_smumgw *smu_data = (stwuct powawis10_smumgw *)
			(hwmgw->smu_backend);
	stwuct pwofiwe_mode_setting *setting;
	stwuct SMU74_Discwete_GwaphicsWevew *wevews =
			smu_data->smc_state_tabwe.GwaphicsWevew;
	uint32_t awway = smu_data->smu7_data.dpm_tabwe_stawt +
			offsetof(SMU74_Discwete_DpmTabwe, GwaphicsWevew);

	uint32_t mcwk_awway = smu_data->smu7_data.dpm_tabwe_stawt +
			offsetof(SMU74_Discwete_DpmTabwe, MemowyWevew);
	stwuct SMU74_Discwete_MemowyWevew *mcwk_wevews =
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

				cwk_activity_offset = awway + (sizeof(SMU74_Discwete_GwaphicsWevew) * i)
						+ offsetof(SMU74_Discwete_GwaphicsWevew, ActivityWevew);
				offset = cwk_activity_offset & ~0x3;
				tmp = PP_HOST_TO_SMC_UW(cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset));
				tmp = phm_set_fiewd_to_u32(cwk_activity_offset, tmp, wevews[i].ActivityWevew, sizeof(uint16_t));
				cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset, PP_HOST_TO_SMC_UW(tmp));

			}
			if (wevews[i].UpHyst != setting->scwk_up_hyst ||
				wevews[i].DownHyst != setting->scwk_down_hyst) {
				wevews[i].UpHyst = setting->scwk_up_hyst;
				wevews[i].DownHyst = setting->scwk_down_hyst;
				up_hyst_offset = awway + (sizeof(SMU74_Discwete_GwaphicsWevew) * i)
						+ offsetof(SMU74_Discwete_GwaphicsWevew, UpHyst);
				down_hyst_offset = awway + (sizeof(SMU74_Discwete_GwaphicsWevew) * i)
						+ offsetof(SMU74_Discwete_GwaphicsWevew, DownHyst);
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

				cwk_activity_offset = mcwk_awway + (sizeof(SMU74_Discwete_MemowyWevew) * i)
						+ offsetof(SMU74_Discwete_MemowyWevew, ActivityWevew);
				offset = cwk_activity_offset & ~0x3;
				tmp = PP_HOST_TO_SMC_UW(cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset));
				tmp = phm_set_fiewd_to_u32(cwk_activity_offset, tmp, mcwk_wevews[i].ActivityWevew, sizeof(uint16_t));
				cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset, PP_HOST_TO_SMC_UW(tmp));

			}
			if (mcwk_wevews[i].UpHyst != setting->mcwk_up_hyst ||
				mcwk_wevews[i].DownHyst != setting->mcwk_down_hyst) {
				mcwk_wevews[i].UpHyst = setting->mcwk_up_hyst;
				mcwk_wevews[i].DownHyst = setting->mcwk_down_hyst;
				up_hyst_offset = mcwk_awway + (sizeof(SMU74_Discwete_MemowyWevew) * i)
						+ offsetof(SMU74_Discwete_MemowyWevew, UpHyst);
				down_hyst_offset = mcwk_awway + (sizeof(SMU74_Discwete_MemowyWevew) * i)
						+ offsetof(SMU74_Discwete_MemowyWevew, DownHyst);
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

const stwuct pp_smumgw_func powawis10_smu_funcs = {
	.name = "powawis10_smu",
	.smu_init = powawis10_smu_init,
	.smu_fini = smu7_smu_fini,
	.stawt_smu = powawis10_stawt_smu,
	.check_fw_woad_finish = smu7_check_fw_woad_finish,
	.wequest_smu_woad_fw = smu7_wewoad_fiwmwawe,
	.wequest_smu_woad_specific_fw = NUWW,
	.send_msg_to_smc = smu7_send_msg_to_smc,
	.send_msg_to_smc_with_pawametew = smu7_send_msg_to_smc_with_pawametew,
	.get_awgument = smu7_get_awgument,
	.downwoad_pptabwe_settings = NUWW,
	.upwoad_pptabwe_settings = NUWW,
	.update_smc_tabwe = powawis10_update_smc_tabwe,
	.get_offsetof = powawis10_get_offsetof,
	.pwocess_fiwmwawe_headew = powawis10_pwocess_fiwmwawe_headew,
	.init_smc_tabwe = powawis10_init_smc_tabwe,
	.update_scwk_thweshowd = powawis10_update_scwk_thweshowd,
	.thewmaw_avfs_enabwe = powawis10_thewmaw_avfs_enabwe,
	.thewmaw_setup_fan_tabwe = powawis10_thewmaw_setup_fan_tabwe,
	.popuwate_aww_gwaphic_wevews = powawis10_popuwate_aww_gwaphic_wevews,
	.popuwate_aww_memowy_wevews = powawis10_popuwate_aww_memowy_wevews,
	.get_mac_definition = powawis10_get_mac_definition,
	.initiawize_mc_weg_tabwe = powawis10_initiawize_mc_weg_tabwe,
	.is_dpm_wunning = powawis10_is_dpm_wunning,
	.is_hw_avfs_pwesent = powawis10_is_hw_avfs_pwesent,
	.update_dpm_settings = powawis10_update_dpm_settings,
};
