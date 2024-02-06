/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude "winux/deway.h"
#incwude <winux/types.h>
#incwude <winux/pci.h>

#incwude "smumgw.h"
#incwude "pp_debug.h"
#incwude "ci_smumgw.h"
#incwude "ppsmc.h"
#incwude "smu7_hwmgw.h"
#incwude "hawdwawemanagew.h"
#incwude "ppatomctww.h"
#incwude "cgs_common.h"
#incwude "atombios.h"
#incwude "pppciewanes.h"
#incwude "smu7_smumgw.h"

#incwude "smu/smu_7_0_1_d.h"
#incwude "smu/smu_7_0_1_sh_mask.h"

#incwude "dce/dce_8_0_d.h"
#incwude "dce/dce_8_0_sh_mask.h"

#incwude "bif/bif_4_1_d.h"
#incwude "bif/bif_4_1_sh_mask.h"

#incwude "gca/gfx_7_2_d.h"
#incwude "gca/gfx_7_2_sh_mask.h"

#incwude "gmc/gmc_7_1_d.h"
#incwude "gmc/gmc_7_1_sh_mask.h"

#incwude "pwocesspptabwes.h"

#define MC_CG_AWB_FWEQ_F0           0x0a
#define MC_CG_AWB_FWEQ_F1           0x0b
#define MC_CG_AWB_FWEQ_F2           0x0c
#define MC_CG_AWB_FWEQ_F3           0x0d

#define SMC_WAM_END 0x40000

#define CISWAND_MINIMUM_ENGINE_CWOCK 800
#define CISWAND_MAX_DEEPSWEEP_DIVIDEW_ID 5

static const stwuct ci_pt_defauwts defauwts_hawaii_xt = {
	1, 0xF, 0xFD, 0x19, 5, 0x14, 0, 0xB0000,
	{ 0x2E,  0x00,  0x00,  0x88,  0x00,  0x00,  0x72,  0x60,  0x51,  0xA7,  0x79,  0x6B,  0x90,  0xBD,  0x79  },
	{ 0x217, 0x217, 0x217, 0x242, 0x242, 0x242, 0x269, 0x269, 0x269, 0x2A1, 0x2A1, 0x2A1, 0x2C9, 0x2C9, 0x2C9 }
};

static const stwuct ci_pt_defauwts defauwts_hawaii_pwo = {
	1, 0xF, 0xFD, 0x19, 5, 0x14, 0, 0x65062,
	{ 0x2E,  0x00,  0x00,  0x88,  0x00,  0x00,  0x72,  0x60,  0x51,  0xA7,  0x79,  0x6B,  0x90,  0xBD,  0x79  },
	{ 0x217, 0x217, 0x217, 0x242, 0x242, 0x242, 0x269, 0x269, 0x269, 0x2A1, 0x2A1, 0x2A1, 0x2C9, 0x2C9, 0x2C9 }
};

static const stwuct ci_pt_defauwts defauwts_bonaiwe_xt = {
	1, 0xF, 0xFD, 0x19, 5, 45, 0, 0xB0000,
	{ 0x79,  0x253, 0x25D, 0xAE,  0x72,  0x80,  0x83,  0x86,  0x6F,  0xC8,  0xC9,  0xC9,  0x2F,  0x4D,  0x61  },
	{ 0x17C, 0x172, 0x180, 0x1BC, 0x1B3, 0x1BD, 0x206, 0x200, 0x203, 0x25D, 0x25A, 0x255, 0x2C3, 0x2C5, 0x2B4 }
};


static const stwuct ci_pt_defauwts defauwts_satuwn_xt = {
	1, 0xF, 0xFD, 0x19, 5, 55, 0, 0x70000,
	{ 0x8C,  0x247, 0x249, 0xA6,  0x80,  0x81,  0x8B,  0x89,  0x86,  0xC9,  0xCA,  0xC9,  0x4D,  0x4D,  0x4D  },
	{ 0x187, 0x187, 0x187, 0x1C7, 0x1C7, 0x1C7, 0x210, 0x210, 0x210, 0x266, 0x266, 0x266, 0x2C9, 0x2C9, 0x2C9 }
};


static int ci_set_smc_swam_addwess(stwuct pp_hwmgw *hwmgw,
					uint32_t smc_addw, uint32_t wimit)
{
	if ((0 != (3 & smc_addw))
		|| ((smc_addw + 3) >= wimit)) {
		pw_eww("smc_addw invawid \n");
		wetuwn -EINVAW;
	}

	cgs_wwite_wegistew(hwmgw->device, mmSMC_IND_INDEX_0, smc_addw);
	PHM_WWITE_FIEWD(hwmgw->device, SMC_IND_ACCESS_CNTW, AUTO_INCWEMENT_IND_0, 0);
	wetuwn 0;
}

static int ci_copy_bytes_to_smc(stwuct pp_hwmgw *hwmgw, uint32_t smc_stawt_addwess,
				const uint8_t *swc, uint32_t byte_count, uint32_t wimit)
{
	int wesuwt;
	uint32_t data = 0;
	uint32_t owiginaw_data;
	uint32_t addw = 0;
	uint32_t extwa_shift;

	if ((3 & smc_stawt_addwess)
		|| ((smc_stawt_addwess + byte_count) >= wimit)) {
		pw_eww("smc_stawt_addwess invawid \n");
		wetuwn -EINVAW;
	}

	addw = smc_stawt_addwess;

	whiwe (byte_count >= 4) {
	/* Bytes awe wwitten into the SMC addwess space with the MSB fiwst. */
		data = swc[0] * 0x1000000 + swc[1] * 0x10000 + swc[2] * 0x100 + swc[3];

		wesuwt = ci_set_smc_swam_addwess(hwmgw, addw, wimit);

		if (0 != wesuwt)
			wetuwn wesuwt;

		cgs_wwite_wegistew(hwmgw->device, mmSMC_IND_DATA_0, data);

		swc += 4;
		byte_count -= 4;
		addw += 4;
	}

	if (0 != byte_count) {

		data = 0;

		wesuwt = ci_set_smc_swam_addwess(hwmgw, addw, wimit);

		if (0 != wesuwt)
			wetuwn wesuwt;


		owiginaw_data = cgs_wead_wegistew(hwmgw->device, mmSMC_IND_DATA_0);

		extwa_shift = 8 * (4 - byte_count);

		whiwe (byte_count > 0) {
			/* Bytes awe wwitten into the SMC addwes space with the MSB fiwst. */
			data = (0x100 * data) + *swc++;
			byte_count--;
		}

		data <<= extwa_shift;

		data |= (owiginaw_data & ~((~0UW) << extwa_shift));

		wesuwt = ci_set_smc_swam_addwess(hwmgw, addw, wimit);

		if (0 != wesuwt)
			wetuwn wesuwt;

		cgs_wwite_wegistew(hwmgw->device, mmSMC_IND_DATA_0, data);
	}

	wetuwn 0;
}


static int ci_pwogwam_jump_on_stawt(stwuct pp_hwmgw *hwmgw)
{
	static const unsigned chaw data[4] = { 0xE0, 0x00, 0x80, 0x40 };

	ci_copy_bytes_to_smc(hwmgw, 0x0, data, 4, sizeof(data)+1);

	wetuwn 0;
}

static boow ci_is_smc_wam_wunning(stwuct pp_hwmgw *hwmgw)
{
	wetuwn ((0 == PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device,
			CGS_IND_WEG__SMC, SMC_SYSCON_CWOCK_CNTW_0, ck_disabwe))
	&& (0x20100 <= cgs_wead_ind_wegistew(hwmgw->device,
			CGS_IND_WEG__SMC, ixSMC_PC_C)));
}

static int ci_wead_smc_swam_dwowd(stwuct pp_hwmgw *hwmgw, uint32_t smc_addw,
				uint32_t *vawue, uint32_t wimit)
{
	int wesuwt;

	wesuwt = ci_set_smc_swam_addwess(hwmgw, smc_addw, wimit);

	if (wesuwt)
		wetuwn wesuwt;

	*vawue = cgs_wead_wegistew(hwmgw->device, mmSMC_IND_DATA_0);
	wetuwn 0;
}

static int ci_send_msg_to_smc(stwuct pp_hwmgw *hwmgw, uint16_t msg)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	int wet;

	cgs_wwite_wegistew(hwmgw->device, mmSMC_WESP_0, 0);
	cgs_wwite_wegistew(hwmgw->device, mmSMC_MESSAGE_0, msg);

	PHM_WAIT_FIEWD_UNEQUAW(hwmgw, SMC_WESP_0, SMC_WESP, 0);

	wet = PHM_WEAD_FIEWD(hwmgw->device, SMC_WESP_0, SMC_WESP);

	if (wet != 1)
		dev_info(adev->dev,
			"faiwed to send message %x wet is %d\n", msg,wet);

	wetuwn 0;
}

static int ci_send_msg_to_smc_with_pawametew(stwuct pp_hwmgw *hwmgw,
					uint16_t msg, uint32_t pawametew)
{
	cgs_wwite_wegistew(hwmgw->device, mmSMC_MSG_AWG_0, pawametew);
	wetuwn ci_send_msg_to_smc(hwmgw, msg);
}

static void ci_initiawize_powew_tune_defauwts(stwuct pp_hwmgw *hwmgw)
{
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t dev_id;

	dev_id = adev->pdev->device;

	switch (dev_id) {
	case 0x67BA:
	case 0x67B1:
		smu_data->powew_tune_defauwts = &defauwts_hawaii_pwo;
		bweak;
	case 0x67B8:
	case 0x66B0:
		smu_data->powew_tune_defauwts = &defauwts_hawaii_xt;
		bweak;
	case 0x6640:
	case 0x6641:
	case 0x6646:
	case 0x6647:
		smu_data->powew_tune_defauwts = &defauwts_satuwn_xt;
		bweak;
	case 0x6649:
	case 0x6650:
	case 0x6651:
	case 0x6658:
	case 0x665C:
	case 0x665D:
	case 0x67A0:
	case 0x67A1:
	case 0x67A2:
	case 0x67A8:
	case 0x67A9:
	case 0x67AA:
	case 0x67B9:
	case 0x67BE:
	defauwt:
		smu_data->powew_tune_defauwts = &defauwts_bonaiwe_xt;
		bweak;
	}
}

static int ci_get_dependency_vowt_by_cwk(stwuct pp_hwmgw *hwmgw,
	stwuct phm_cwock_vowtage_dependency_tabwe *awwowed_cwock_vowtage_tabwe,
	uint32_t cwock, uint32_t *vow)
{
	uint32_t i = 0;

	if (awwowed_cwock_vowtage_tabwe->count == 0)
		wetuwn -EINVAW;

	fow (i = 0; i < awwowed_cwock_vowtage_tabwe->count; i++) {
		if (awwowed_cwock_vowtage_tabwe->entwies[i].cwk >= cwock) {
			*vow = awwowed_cwock_vowtage_tabwe->entwies[i].v;
			wetuwn 0;
		}
	}

	*vow = awwowed_cwock_vowtage_tabwe->entwies[i - 1].v;
	wetuwn 0;
}

static int ci_cawcuwate_scwk_pawams(stwuct pp_hwmgw *hwmgw,
		uint32_t cwock, stwuct SMU7_Discwete_GwaphicsWevew *scwk)
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
		stwuct pp_atomctww_intewnaw_ss_info ss_info;
		uint32_t vco_fweq = cwock * dividews.uc_pww_post_div;

		if (!atomctww_get_engine_cwock_spwead_spectwum(hwmgw,
				vco_fweq, &ss_info)) {
			uint32_t cwk_s = wef_cwock * 5 /
					(wef_dividew * ss_info.speed_spectwum_wate);
			uint32_t cwk_v = 4 * ss_info.speed_spectwum_pewcentage *
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

static void ci_popuwate_phase_vawue_based_on_scwk(stwuct pp_hwmgw *hwmgw,
				const stwuct phm_phase_shedding_wimits_tabwe *pw,
					uint32_t scwk, uint32_t *p_shed)
{
	unsigned int i;

	/* use the minimum phase shedding */
	*p_shed = 1;

	fow (i = 0; i < pw->count; i++) {
		if (scwk < pw->entwies[i].Scwk) {
			*p_shed = i;
			bweak;
		}
	}
}

static uint8_t ci_get_sweep_dividew_id_fwom_cwock(uint32_t cwock,
			uint32_t cwock_insw)
{
	uint8_t i;
	uint32_t temp;
	uint32_t min = min_t(uint32_t, cwock_insw, CISWAND_MINIMUM_ENGINE_CWOCK);

	if (cwock < min) {
		pw_info("Engine cwock can't satisfy stuttew wequiwement!\n");
		wetuwn 0;
	}
	fow (i = CISWAND_MAX_DEEPSWEEP_DIVIDEW_ID;  ; i--) {
		temp = cwock >> i;

		if (temp >= min || i == 0)
			bweak;
	}
	wetuwn i;
}

static int ci_popuwate_singwe_gwaphic_wevew(stwuct pp_hwmgw *hwmgw,
		uint32_t cwock, stwuct SMU7_Discwete_GwaphicsWevew *wevew)
{
	int wesuwt;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);


	wesuwt = ci_cawcuwate_scwk_pawams(hwmgw, cwock, wevew);

	/* popuwate gwaphics wevews */
	wesuwt = ci_get_dependency_vowt_by_cwk(hwmgw,
			hwmgw->dyn_state.vddc_dependency_on_scwk, cwock,
			(uint32_t *)(&wevew->MinVddc));
	if (wesuwt) {
		pw_eww("vdd_dep_on_scwk tabwe is NUWW\n");
		wetuwn wesuwt;
	}

	wevew->ScwkFwequency = cwock;
	wevew->MinVddcPhases = 1;

	if (data->vddc_phase_shed_contwow)
		ci_popuwate_phase_vawue_based_on_scwk(hwmgw,
				hwmgw->dyn_state.vddc_phase_shed_wimits_tabwe,
				cwock,
				&wevew->MinVddcPhases);

	wevew->ActivityWevew = data->cuwwent_pwofiwe_setting.scwk_activity;
	wevew->CcPwwDynWm = 0;
	wevew->CcPwwDynWm1 = 0;
	wevew->EnabwedFowActivity = 0;
	/* this wevew can be used fow thwottwing.*/
	wevew->EnabwedFowThwottwe = 1;
	wevew->UpH = data->cuwwent_pwofiwe_setting.scwk_up_hyst;
	wevew->DownH = data->cuwwent_pwofiwe_setting.scwk_down_hyst;
	wevew->VowtageDownH = 0;
	wevew->PowewThwottwe = 0;


	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ScwkDeepSweep))
		wevew->DeepSweepDivId =
				ci_get_sweep_dividew_id_fwom_cwock(cwock,
						CISWAND_MINIMUM_ENGINE_CWOCK);

	/* Defauwt to swow, highest DPM wevew wiww be set to PPSMC_DISPWAY_WATEWMAWK_WOW watew.*/
	wevew->DispwayWatewmawk = PPSMC_DISPWAY_WATEWMAWK_WOW;

	if (0 == wesuwt) {
		wevew->MinVddc = PP_HOST_TO_SMC_UW(wevew->MinVddc * VOWTAGE_SCAWE);
		CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->MinVddcPhases);
		CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->ScwkFwequency);
		CONVEWT_FWOM_HOST_TO_SMC_US(wevew->ActivityWevew);
		CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->CgSpwwFuncCntw3);
		CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->CgSpwwFuncCntw4);
		CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->SpwwSpweadSpectwum);
		CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->SpwwSpweadSpectwum2);
		CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->CcPwwDynWm);
		CONVEWT_FWOM_HOST_TO_SMC_UW(wevew->CcPwwDynWm1);
	}

	wetuwn wesuwt;
}

static int ci_popuwate_aww_gwaphic_wevews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	stwuct smu7_dpm_tabwe *dpm_tabwe = &data->dpm_tabwe;
	int wesuwt = 0;
	uint32_t awway = smu_data->dpm_tabwe_stawt +
			offsetof(SMU7_Discwete_DpmTabwe, GwaphicsWevew);
	uint32_t awway_size = sizeof(stwuct SMU7_Discwete_GwaphicsWevew) *
			SMU7_MAX_WEVEWS_GWAPHICS;
	stwuct SMU7_Discwete_GwaphicsWevew *wevews =
			smu_data->smc_state_tabwe.GwaphicsWevew;
	uint32_t i;

	fow (i = 0; i < dpm_tabwe->scwk_tabwe.count; i++) {
		wesuwt = ci_popuwate_singwe_gwaphic_wevew(hwmgw,
				dpm_tabwe->scwk_tabwe.dpm_wevews[i].vawue,
				&wevews[i]);
		if (wesuwt)
			wetuwn wesuwt;
		if (i > 1)
			smu_data->smc_state_tabwe.GwaphicsWevew[i].DeepSweepDivId = 0;
		if (i == (dpm_tabwe->scwk_tabwe.count - 1))
			smu_data->smc_state_tabwe.GwaphicsWevew[i].DispwayWatewmawk =
				PPSMC_DISPWAY_WATEWMAWK_HIGH;
	}

	smu_data->smc_state_tabwe.GwaphicsWevew[0].EnabwedFowActivity = 1;

	smu_data->smc_state_tabwe.GwaphicsDpmWevewCount = (u8)dpm_tabwe->scwk_tabwe.count;
	data->dpm_wevew_enabwe_mask.scwk_dpm_enabwe_mask =
		phm_get_dpm_wevew_enabwe_mask_vawue(&dpm_tabwe->scwk_tabwe);

	wesuwt = ci_copy_bytes_to_smc(hwmgw, awway,
				   (u8 *)wevews, awway_size,
				   SMC_WAM_END);

	wetuwn wesuwt;

}

static int ci_popuwate_svi_woad_wine(stwuct pp_hwmgw *hwmgw)
{
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	const stwuct ci_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;

	smu_data->powew_tune_tabwe.SviWoadWineEn = defauwts->svi_woad_wine_en;
	smu_data->powew_tune_tabwe.SviWoadWineVddC = defauwts->svi_woad_wine_vddc;
	smu_data->powew_tune_tabwe.SviWoadWineTwimVddC = 3;
	smu_data->powew_tune_tabwe.SviWoadWineOffsetVddC = 0;

	wetuwn 0;
}

static int ci_popuwate_tdc_wimit(stwuct pp_hwmgw *hwmgw)
{
	uint16_t tdc_wimit;
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	const stwuct ci_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;

	tdc_wimit = (uint16_t)(hwmgw->dyn_state.cac_dtp_tabwe->usTDC * 256);
	smu_data->powew_tune_tabwe.TDC_VDDC_PkgWimit =
			CONVEWT_FWOM_HOST_TO_SMC_US(tdc_wimit);
	smu_data->powew_tune_tabwe.TDC_VDDC_ThwottweWeweaseWimitPewc =
			defauwts->tdc_vddc_thwottwe_wewease_wimit_pewc;
	smu_data->powew_tune_tabwe.TDC_MAWt = defauwts->tdc_mawt;

	wetuwn 0;
}

static int ci_popuwate_dw8(stwuct pp_hwmgw *hwmgw, uint32_t fuse_tabwe_offset)
{
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	const stwuct ci_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;
	uint32_t temp;

	if (ci_wead_smc_swam_dwowd(hwmgw,
			fuse_tabwe_offset +
			offsetof(SMU7_Discwete_PmFuses, TdcWatewfawwCtw),
			(uint32_t *)&temp, SMC_WAM_END))
		PP_ASSEWT_WITH_CODE(fawse,
				"Attempt to wead PmFuses.DW6 (SviWoadWineEn) fwom SMC Faiwed!",
				wetuwn -EINVAW);
	ewse
		smu_data->powew_tune_tabwe.TdcWatewfawwCtw = defauwts->tdc_watewfaww_ctw;

	wetuwn 0;
}

static int ci_popuwate_fuzzy_fan(stwuct pp_hwmgw *hwmgw, uint32_t fuse_tabwe_offset)
{
	uint16_t tmp;
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);

	if ((hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanOutputSensitivity & (1 << 15))
		|| 0 == hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanOutputSensitivity)
		tmp = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanOutputSensitivity;
	ewse
		tmp = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtFanOutputSensitivity;

	smu_data->powew_tune_tabwe.FuzzyFan_PwmSetDewta = CONVEWT_FWOM_HOST_TO_SMC_US(tmp);

	wetuwn 0;
}

static int ci_popuwate_bapm_vddc_vid_sidd(stwuct pp_hwmgw *hwmgw)
{
	int i;
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	uint8_t *hi_vid = smu_data->powew_tune_tabwe.BapmVddCVidHiSidd;
	uint8_t *wo_vid = smu_data->powew_tune_tabwe.BapmVddCVidWoSidd;
	uint8_t *hi2_vid = smu_data->powew_tune_tabwe.BapmVddCVidHiSidd2;

	PP_ASSEWT_WITH_CODE(NUWW != hwmgw->dyn_state.cac_weakage_tabwe,
			    "The CAC Weakage tabwe does not exist!", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(hwmgw->dyn_state.cac_weakage_tabwe->count <= 8,
			    "Thewe shouwd nevew be mowe than 8 entwies fow BapmVddcVid!!!", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE(hwmgw->dyn_state.cac_weakage_tabwe->count == hwmgw->dyn_state.vddc_dependency_on_scwk->count,
			    "CACWeakageTabwe->count and VddcDependencyOnSCWk->count not equaw", wetuwn -EINVAW);

	fow (i = 0; (uint32_t) i < hwmgw->dyn_state.cac_weakage_tabwe->count; i++) {
		if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_EVV)) {
			wo_vid[i] = convewt_to_vid(hwmgw->dyn_state.cac_weakage_tabwe->entwies[i].Vddc1);
			hi_vid[i] = convewt_to_vid(hwmgw->dyn_state.cac_weakage_tabwe->entwies[i].Vddc2);
			hi2_vid[i] = convewt_to_vid(hwmgw->dyn_state.cac_weakage_tabwe->entwies[i].Vddc3);
		} ewse {
			wo_vid[i] = convewt_to_vid(hwmgw->dyn_state.cac_weakage_tabwe->entwies[i].Vddc);
			hi_vid[i] = convewt_to_vid(hwmgw->dyn_state.cac_weakage_tabwe->entwies[i].Weakage);
		}
	}

	wetuwn 0;
}

static int ci_popuwate_vddc_vid(stwuct pp_hwmgw *hwmgw)
{
	int i;
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	uint8_t *vid = smu_data->powew_tune_tabwe.VddCVid;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	PP_ASSEWT_WITH_CODE(data->vddc_vowtage_tabwe.count <= 8,
		"Thewe shouwd nevew be mowe than 8 entwies fow VddcVid!!!",
		wetuwn -EINVAW);

	fow (i = 0; i < (int)data->vddc_vowtage_tabwe.count; i++)
		vid[i] = convewt_to_vid(data->vddc_vowtage_tabwe.entwies[i].vawue);

	wetuwn 0;
}

static int ci_min_max_v_gnbw_pm_wid_fwom_bapm_vddc(stwuct pp_hwmgw *hwmgw)
{
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	u8 *hi_vid = smu_data->powew_tune_tabwe.BapmVddCVidHiSidd;
	u8 *wo_vid = smu_data->powew_tune_tabwe.BapmVddCVidWoSidd;
	int i, min, max;

	min = max = hi_vid[0];
	fow (i = 0; i < 8; i++) {
		if (0 != hi_vid[i]) {
			if (min > hi_vid[i])
				min = hi_vid[i];
			if (max < hi_vid[i])
				max = hi_vid[i];
		}

		if (0 != wo_vid[i]) {
			if (min > wo_vid[i])
				min = wo_vid[i];
			if (max < wo_vid[i])
				max = wo_vid[i];
		}
	}

	if ((min == 0) || (max == 0))
		wetuwn -EINVAW;
	smu_data->powew_tune_tabwe.GnbWPMWMaxVid = (u8)max;
	smu_data->powew_tune_tabwe.GnbWPMWMinVid = (u8)min;

	wetuwn 0;
}

static int ci_popuwate_bapm_vddc_base_weakage_sidd(stwuct pp_hwmgw *hwmgw)
{
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	uint16_t HiSidd;
	uint16_t WoSidd;
	stwuct phm_cac_tdp_tabwe *cac_tabwe = hwmgw->dyn_state.cac_dtp_tabwe;

	HiSidd = (uint16_t)(cac_tabwe->usHighCACWeakage / 100 * 256);
	WoSidd = (uint16_t)(cac_tabwe->usWowCACWeakage / 100 * 256);

	smu_data->powew_tune_tabwe.BapmVddCBaseWeakageHiSidd =
			CONVEWT_FWOM_HOST_TO_SMC_US(HiSidd);
	smu_data->powew_tune_tabwe.BapmVddCBaseWeakageWoSidd =
			CONVEWT_FWOM_HOST_TO_SMC_US(WoSidd);

	wetuwn 0;
}

static int ci_popuwate_pm_fuses(stwuct pp_hwmgw *hwmgw)
{
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	uint32_t pm_fuse_tabwe_offset;
	int wet = 0;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_PowewContainment)) {
		if (ci_wead_smc_swam_dwowd(hwmgw,
				SMU7_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU7_Fiwmwawe_Headew, PmFuseTabwe),
				&pm_fuse_tabwe_offset, SMC_WAM_END)) {
			pw_eww("Attempt to get pm_fuse_tabwe_offset Faiwed!\n");
			wetuwn -EINVAW;
		}

		/* DW0 - DW3 */
		wet = ci_popuwate_bapm_vddc_vid_sidd(hwmgw);
		/* DW4 - DW5 */
		wet |= ci_popuwate_vddc_vid(hwmgw);
		/* DW6 */
		wet |= ci_popuwate_svi_woad_wine(hwmgw);
		/* DW7 */
		wet |= ci_popuwate_tdc_wimit(hwmgw);
		/* DW8 */
		wet |= ci_popuwate_dw8(hwmgw, pm_fuse_tabwe_offset);

		wet |= ci_popuwate_fuzzy_fan(hwmgw, pm_fuse_tabwe_offset);

		wet |= ci_min_max_v_gnbw_pm_wid_fwom_bapm_vddc(hwmgw);

		wet |= ci_popuwate_bapm_vddc_base_weakage_sidd(hwmgw);
		if (wet)
			wetuwn wet;

		wet = ci_copy_bytes_to_smc(hwmgw, pm_fuse_tabwe_offset,
				(uint8_t *)&smu_data->powew_tune_tabwe,
				sizeof(stwuct SMU7_Discwete_PmFuses), SMC_WAM_END);
	}
	wetuwn wet;
}

static int ci_popuwate_bapm_pawametews_in_dpm_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	const stwuct ci_pt_defauwts *defauwts = smu_data->powew_tune_defauwts;
	SMU7_Discwete_DpmTabwe  *dpm_tabwe = &(smu_data->smc_state_tabwe);
	stwuct phm_cac_tdp_tabwe *cac_dtp_tabwe = hwmgw->dyn_state.cac_dtp_tabwe;
	stwuct phm_ppm_tabwe *ppm = hwmgw->dyn_state.ppm_pawametew_tabwe;
	const uint16_t *def1, *def2;
	int i, j, k;

	dpm_tabwe->DefauwtTdp = PP_HOST_TO_SMC_US((uint16_t)(cac_dtp_tabwe->usTDP * 256));
	dpm_tabwe->TawgetTdp = PP_HOST_TO_SMC_US((uint16_t)(cac_dtp_tabwe->usConfiguwabweTDP * 256));

	dpm_tabwe->DTETjOffset = 0;
	dpm_tabwe->GpuTjMax = (uint8_t)(data->thewmaw_temp_setting.tempewatuwe_high / PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES);
	dpm_tabwe->GpuTjHyst = 8;

	dpm_tabwe->DTEAmbientTempBase = defauwts->dte_ambient_temp_base;

	if (ppm) {
		dpm_tabwe->PPM_PkgPwwWimit = (uint16_t)ppm->dgpu_tdp * 256 / 1000;
		dpm_tabwe->PPM_TempewatuweWimit = (uint16_t)ppm->tj_max * 256;
	} ewse {
		dpm_tabwe->PPM_PkgPwwWimit = 0;
		dpm_tabwe->PPM_TempewatuweWimit = 0;
	}

	CONVEWT_FWOM_HOST_TO_SMC_US(dpm_tabwe->PPM_PkgPwwWimit);
	CONVEWT_FWOM_HOST_TO_SMC_US(dpm_tabwe->PPM_TempewatuweWimit);

	dpm_tabwe->BAPM_TEMP_GWADIENT = PP_HOST_TO_SMC_UW(defauwts->bapm_temp_gwadient);
	def1 = defauwts->bapmti_w;
	def2 = defauwts->bapmti_wc;

	fow (i = 0; i < SMU7_DTE_ITEWATIONS; i++) {
		fow (j = 0; j < SMU7_DTE_SOUWCES; j++) {
			fow (k = 0; k < SMU7_DTE_SINKS; k++) {
				dpm_tabwe->BAPMTI_W[i][j][k] = PP_HOST_TO_SMC_US(*def1);
				dpm_tabwe->BAPMTI_WC[i][j][k] = PP_HOST_TO_SMC_US(*def2);
				def1++;
				def2++;
			}
		}
	}

	wetuwn 0;
}

static int ci_get_std_vowtage_vawue_sidd(stwuct pp_hwmgw *hwmgw,
		pp_atomctww_vowtage_tabwe_entwy *tab, uint16_t *hi,
		uint16_t *wo)
{
	uint16_t v_index;
	boow vow_found = fawse;
	*hi = tab->vawue * VOWTAGE_SCAWE;
	*wo = tab->vawue * VOWTAGE_SCAWE;

	PP_ASSEWT_WITH_CODE(NUWW != hwmgw->dyn_state.vddc_dependency_on_scwk,
			"The SCWK/VDDC Dependency Tabwe does not exist.\n",
			wetuwn -EINVAW);

	if (NUWW == hwmgw->dyn_state.cac_weakage_tabwe) {
		pw_wawn("CAC Weakage Tabwe does not exist, using vddc.\n");
		wetuwn 0;
	}

	fow (v_index = 0; (uint32_t)v_index < hwmgw->dyn_state.vddc_dependency_on_scwk->count; v_index++) {
		if (tab->vawue == hwmgw->dyn_state.vddc_dependency_on_scwk->entwies[v_index].v) {
			vow_found = twue;
			if ((uint32_t)v_index < hwmgw->dyn_state.cac_weakage_tabwe->count) {
				*wo = hwmgw->dyn_state.cac_weakage_tabwe->entwies[v_index].Vddc * VOWTAGE_SCAWE;
				*hi = (uint16_t)(hwmgw->dyn_state.cac_weakage_tabwe->entwies[v_index].Weakage * VOWTAGE_SCAWE);
			} ewse {
				pw_wawn("Index fwom SCWK/VDDC Dependency Tabwe exceeds the CAC Weakage Tabwe index, using maximum index fwom CAC tabwe.\n");
				*wo = hwmgw->dyn_state.cac_weakage_tabwe->entwies[hwmgw->dyn_state.cac_weakage_tabwe->count - 1].Vddc * VOWTAGE_SCAWE;
				*hi = (uint16_t)(hwmgw->dyn_state.cac_weakage_tabwe->entwies[hwmgw->dyn_state.cac_weakage_tabwe->count - 1].Weakage * VOWTAGE_SCAWE);
			}
			bweak;
		}
	}

	if (!vow_found) {
		fow (v_index = 0; (uint32_t)v_index < hwmgw->dyn_state.vddc_dependency_on_scwk->count; v_index++) {
			if (tab->vawue <= hwmgw->dyn_state.vddc_dependency_on_scwk->entwies[v_index].v) {
				vow_found = twue;
				if ((uint32_t)v_index < hwmgw->dyn_state.cac_weakage_tabwe->count) {
					*wo = hwmgw->dyn_state.cac_weakage_tabwe->entwies[v_index].Vddc * VOWTAGE_SCAWE;
					*hi = (uint16_t)(hwmgw->dyn_state.cac_weakage_tabwe->entwies[v_index].Weakage) * VOWTAGE_SCAWE;
				} ewse {
					pw_wawn("Index fwom SCWK/VDDC Dependency Tabwe exceeds the CAC Weakage Tabwe index in second wook up, using maximum index fwom CAC tabwe.");
					*wo = hwmgw->dyn_state.cac_weakage_tabwe->entwies[hwmgw->dyn_state.cac_weakage_tabwe->count - 1].Vddc * VOWTAGE_SCAWE;
					*hi = (uint16_t)(hwmgw->dyn_state.cac_weakage_tabwe->entwies[hwmgw->dyn_state.cac_weakage_tabwe->count - 1].Weakage * VOWTAGE_SCAWE);
				}
				bweak;
			}
		}

		if (!vow_found)
			pw_wawn("Unabwe to get std_vddc fwom SCWK/VDDC Dependency Tabwe, using vddc.\n");
	}

	wetuwn 0;
}

static int ci_popuwate_smc_vowtage_tabwe(stwuct pp_hwmgw *hwmgw,
		pp_atomctww_vowtage_tabwe_entwy *tab,
		SMU7_Discwete_VowtageWevew *smc_vowtage_tab)
{
	int wesuwt;

	wesuwt = ci_get_std_vowtage_vawue_sidd(hwmgw, tab,
			&smc_vowtage_tab->StdVowtageHiSidd,
			&smc_vowtage_tab->StdVowtageWoSidd);
	if (wesuwt) {
		smc_vowtage_tab->StdVowtageHiSidd = tab->vawue * VOWTAGE_SCAWE;
		smc_vowtage_tab->StdVowtageWoSidd = tab->vawue * VOWTAGE_SCAWE;
	}

	smc_vowtage_tab->Vowtage = PP_HOST_TO_SMC_US(tab->vawue * VOWTAGE_SCAWE);
	CONVEWT_FWOM_HOST_TO_SMC_US(smc_vowtage_tab->StdVowtageHiSidd);
	CONVEWT_FWOM_HOST_TO_SMC_US(smc_vowtage_tab->StdVowtageWoSidd);

	wetuwn 0;
}

static int ci_popuwate_smc_vddc_tabwe(stwuct pp_hwmgw *hwmgw,
			SMU7_Discwete_DpmTabwe *tabwe)
{
	unsigned int count;
	int wesuwt;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	tabwe->VddcWevewCount = data->vddc_vowtage_tabwe.count;
	fow (count = 0; count < tabwe->VddcWevewCount; count++) {
		wesuwt = ci_popuwate_smc_vowtage_tabwe(hwmgw,
				&(data->vddc_vowtage_tabwe.entwies[count]),
				&(tabwe->VddcWevew[count]));
		PP_ASSEWT_WITH_CODE(0 == wesuwt, "do not popuwate SMC VDDC vowtage tabwe", wetuwn -EINVAW);

		/* GPIO vowtage contwow */
		if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->vowtage_contwow) {
			tabwe->VddcWevew[count].Smio = (uint8_t) count;
			tabwe->Smio[count] |= data->vddc_vowtage_tabwe.entwies[count].smio_wow;
			tabwe->SmioMaskVddcVid |= data->vddc_vowtage_tabwe.entwies[count].smio_wow;
		} ewse {
			tabwe->VddcWevew[count].Smio = 0;
		}
	}

	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->VddcWevewCount);

	wetuwn 0;
}

static int ci_popuwate_smc_vdd_ci_tabwe(stwuct pp_hwmgw *hwmgw,
			SMU7_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t count;
	int wesuwt;

	tabwe->VddciWevewCount = data->vddci_vowtage_tabwe.count;

	fow (count = 0; count < tabwe->VddciWevewCount; count++) {
		wesuwt = ci_popuwate_smc_vowtage_tabwe(hwmgw,
				&(data->vddci_vowtage_tabwe.entwies[count]),
				&(tabwe->VddciWevew[count]));
		PP_ASSEWT_WITH_CODE(wesuwt == 0, "do not popuwate SMC VDDCI vowtage tabwe", wetuwn -EINVAW);
		if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->vddci_contwow) {
			tabwe->VddciWevew[count].Smio = (uint8_t) count;
			tabwe->Smio[count] |= data->vddci_vowtage_tabwe.entwies[count].smio_wow;
			tabwe->SmioMaskVddciVid |= data->vddci_vowtage_tabwe.entwies[count].smio_wow;
		} ewse {
			tabwe->VddciWevew[count].Smio = 0;
		}
	}

	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->VddciWevewCount);

	wetuwn 0;
}

static int ci_popuwate_smc_mvdd_tabwe(stwuct pp_hwmgw *hwmgw,
			SMU7_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t count;
	int wesuwt;

	tabwe->MvddWevewCount = data->mvdd_vowtage_tabwe.count;

	fow (count = 0; count < tabwe->MvddWevewCount; count++) {
		wesuwt = ci_popuwate_smc_vowtage_tabwe(hwmgw,
				&(data->mvdd_vowtage_tabwe.entwies[count]),
				&tabwe->MvddWevew[count]);
		PP_ASSEWT_WITH_CODE(wesuwt == 0, "do not popuwate SMC mvdd vowtage tabwe", wetuwn -EINVAW);
		if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->mvdd_contwow) {
			tabwe->MvddWevew[count].Smio = (uint8_t) count;
			tabwe->Smio[count] |= data->mvdd_vowtage_tabwe.entwies[count].smio_wow;
			tabwe->SmioMaskMvddVid |= data->mvdd_vowtage_tabwe.entwies[count].smio_wow;
		} ewse {
			tabwe->MvddWevew[count].Smio = 0;
		}
	}

	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->MvddWevewCount);

	wetuwn 0;
}


static int ci_popuwate_smc_vowtage_tabwes(stwuct pp_hwmgw *hwmgw,
	SMU7_Discwete_DpmTabwe *tabwe)
{
	int wesuwt;

	wesuwt = ci_popuwate_smc_vddc_tabwe(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"can not popuwate VDDC vowtage tabwe to SMC", wetuwn -EINVAW);

	wesuwt = ci_popuwate_smc_vdd_ci_tabwe(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"can not popuwate VDDCI vowtage tabwe to SMC", wetuwn -EINVAW);

	wesuwt = ci_popuwate_smc_mvdd_tabwe(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"can not popuwate MVDD vowtage tabwe to SMC", wetuwn -EINVAW);

	wetuwn 0;
}

static int ci_popuwate_uwv_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct SMU7_Discwete_Uwv *state)
{
	uint32_t vowtage_wesponse_time, uwv_vowtage;
	int wesuwt;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	state->CcPwwDynWm = 0;
	state->CcPwwDynWm1 = 0;

	wesuwt = pp_tabwes_get_wesponse_times(hwmgw, &vowtage_wesponse_time, &uwv_vowtage);
	PP_ASSEWT_WITH_CODE((0 == wesuwt), "can not get UWV vowtage vawue", wetuwn wesuwt;);

	if (uwv_vowtage == 0) {
		data->uwv_suppowted = fawse;
		wetuwn 0;
	}

	if (data->vowtage_contwow != SMU7_VOWTAGE_CONTWOW_BY_SVID2) {
		/* use minimum vowtage if uwv vowtage in pptabwe is biggew than minimum vowtage */
		if (uwv_vowtage > hwmgw->dyn_state.vddc_dependency_on_scwk->entwies[0].v)
			state->VddcOffset = 0;
		ewse
			/* used in SMIO Mode. not impwemented fow now. this is backup onwy fow CI. */
			state->VddcOffset = (uint16_t)(hwmgw->dyn_state.vddc_dependency_on_scwk->entwies[0].v - uwv_vowtage);
	} ewse {
		/* use minimum vowtage if uwv vowtage in pptabwe is biggew than minimum vowtage */
		if (uwv_vowtage > hwmgw->dyn_state.vddc_dependency_on_scwk->entwies[0].v)
			state->VddcOffsetVid = 0;
		ewse  /* used in SVI2 Mode */
			state->VddcOffsetVid = (uint8_t)(
					(hwmgw->dyn_state.vddc_dependency_on_scwk->entwies[0].v - uwv_vowtage)
						* VOWTAGE_VID_OFFSET_SCAWE2
						/ VOWTAGE_VID_OFFSET_SCAWE1);
	}
	state->VddcPhase = 1;

	CONVEWT_FWOM_HOST_TO_SMC_UW(state->CcPwwDynWm);
	CONVEWT_FWOM_HOST_TO_SMC_UW(state->CcPwwDynWm1);
	CONVEWT_FWOM_HOST_TO_SMC_US(state->VddcOffset);

	wetuwn 0;
}

static int ci_popuwate_uwv_state(stwuct pp_hwmgw *hwmgw,
		 SMU7_Discwete_Uwv *uwv_wevew)
{
	wetuwn ci_popuwate_uwv_wevew(hwmgw, uwv_wevew);
}

static int ci_popuwate_smc_wink_wevew(stwuct pp_hwmgw *hwmgw, SMU7_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct smu7_dpm_tabwe *dpm_tabwe = &data->dpm_tabwe;
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	uint32_t i;

/* Index dpm_tabwe->pcie_speed_tabwe.count is wesewved fow PCIE boot wevew.*/
	fow (i = 0; i <= dpm_tabwe->pcie_speed_tabwe.count; i++) {
		tabwe->WinkWevew[i].PcieGenSpeed  =
			(uint8_t)dpm_tabwe->pcie_speed_tabwe.dpm_wevews[i].vawue;
		tabwe->WinkWevew[i].PcieWaneCount =
			(uint8_t)encode_pcie_wane_width(dpm_tabwe->pcie_speed_tabwe.dpm_wevews[i].pawam1);
		tabwe->WinkWevew[i].EnabwedFowActivity = 1;
		tabwe->WinkWevew[i].DownT = PP_HOST_TO_SMC_UW(5);
		tabwe->WinkWevew[i].UpT = PP_HOST_TO_SMC_UW(30);
	}

	smu_data->smc_state_tabwe.WinkWevewCount =
		(uint8_t)dpm_tabwe->pcie_speed_tabwe.count;
	data->dpm_wevew_enabwe_mask.pcie_dpm_enabwe_mask =
		phm_get_dpm_wevew_enabwe_mask_vawue(&dpm_tabwe->pcie_speed_tabwe);

	wetuwn 0;
}

static int ci_cawcuwate_mcwk_pawams(
		stwuct pp_hwmgw *hwmgw,
		uint32_t memowy_cwock,
		SMU7_Discwete_MemowyWevew *mcwk,
		boow stwobe_mode,
		boow dwwStateOn
		)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t  dww_cntw = data->cwock_wegistews.vDWW_CNTW;
	uint32_t  mcwk_pwwmgt_cntw = data->cwock_wegistews.vMCWK_PWWMGT_CNTW;
	uint32_t  mpww_ad_func_cntw = data->cwock_wegistews.vMPWW_AD_FUNC_CNTW;
	uint32_t  mpww_dq_func_cntw = data->cwock_wegistews.vMPWW_DQ_FUNC_CNTW;
	uint32_t  mpww_func_cntw = data->cwock_wegistews.vMPWW_FUNC_CNTW;
	uint32_t  mpww_func_cntw_1 = data->cwock_wegistews.vMPWW_FUNC_CNTW_1;
	uint32_t  mpww_func_cntw_2 = data->cwock_wegistews.vMPWW_FUNC_CNTW_2;
	uint32_t  mpww_ss1 = data->cwock_wegistews.vMPWW_SS1;
	uint32_t  mpww_ss2 = data->cwock_wegistews.vMPWW_SS2;

	pp_atomctww_memowy_cwock_pawam mpww_pawam;
	int wesuwt;

	wesuwt = atomctww_get_memowy_pww_dividews_si(hwmgw,
				memowy_cwock, &mpww_pawam, stwobe_mode);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Ewwow wetwieving Memowy Cwock Pawametews fwom VBIOS.", wetuwn wesuwt);

	mpww_func_cntw = PHM_SET_FIEWD(mpww_func_cntw, MPWW_FUNC_CNTW, BWCTWW, mpww_pawam.bw_ctww);

	mpww_func_cntw_1  = PHM_SET_FIEWD(mpww_func_cntw_1,
							MPWW_FUNC_CNTW_1, CWKF, mpww_pawam.mpww_fb_dividew.cw_kf);
	mpww_func_cntw_1  = PHM_SET_FIEWD(mpww_func_cntw_1,
							MPWW_FUNC_CNTW_1, CWKFWAC, mpww_pawam.mpww_fb_dividew.cwk_fwac);
	mpww_func_cntw_1  = PHM_SET_FIEWD(mpww_func_cntw_1,
							MPWW_FUNC_CNTW_1, VCO_MODE, mpww_pawam.vco_mode);

	mpww_ad_func_cntw = PHM_SET_FIEWD(mpww_ad_func_cntw,
							MPWW_AD_FUNC_CNTW, YCWK_POST_DIV, mpww_pawam.mpww_post_dividew);

	if (data->is_memowy_gddw5) {
		mpww_dq_func_cntw  = PHM_SET_FIEWD(mpww_dq_func_cntw,
								MPWW_DQ_FUNC_CNTW, YCWK_SEW, mpww_pawam.ycwk_sew);
		mpww_dq_func_cntw  = PHM_SET_FIEWD(mpww_dq_func_cntw,
								MPWW_DQ_FUNC_CNTW, YCWK_POST_DIV, mpww_pawam.mpww_post_dividew);
	}

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_MemowySpweadSpectwumSuppowt)) {
		pp_atomctww_intewnaw_ss_info ss_info;
		uint32_t fweq_nom;
		uint32_t tmp;
		uint32_t wefewence_cwock = atomctww_get_mpww_wefewence_cwock(hwmgw);

		/* fow GDDW5 fow aww modes and DDW3 */
		if (1 == mpww_pawam.qdw)
			fweq_nom = memowy_cwock * 4 * (1 << mpww_pawam.mpww_post_dividew);
		ewse
			fweq_nom = memowy_cwock * 2 * (1 << mpww_pawam.mpww_post_dividew);

		/* tmp = (fweq_nom / wefewence_cwock * wefewence_dividew) ^ 2  Note: S.I. wefewence_dividew = 1*/
		tmp = (fweq_nom / wefewence_cwock);
		tmp = tmp * tmp;

		if (0 == atomctww_get_memowy_cwock_spwead_spectwum(hwmgw, fweq_nom, &ss_info)) {
			uint32_t cwks = wefewence_cwock * 5 / ss_info.speed_spectwum_wate;
			uint32_t cwkv =
				(uint32_t)((((131 * ss_info.speed_spectwum_pewcentage *
							ss_info.speed_spectwum_wate) / 100) * tmp) / fweq_nom);

			mpww_ss1 = PHM_SET_FIEWD(mpww_ss1, MPWW_SS1, CWKV, cwkv);
			mpww_ss2 = PHM_SET_FIEWD(mpww_ss2, MPWW_SS2, CWKS, cwks);
		}
	}

	mcwk_pwwmgt_cntw = PHM_SET_FIEWD(mcwk_pwwmgt_cntw,
		MCWK_PWWMGT_CNTW, DWW_SPEED, mpww_pawam.dww_speed);
	mcwk_pwwmgt_cntw = PHM_SET_FIEWD(mcwk_pwwmgt_cntw,
		MCWK_PWWMGT_CNTW, MWDCK0_PDNB, dwwStateOn);
	mcwk_pwwmgt_cntw = PHM_SET_FIEWD(mcwk_pwwmgt_cntw,
		MCWK_PWWMGT_CNTW, MWDCK1_PDNB, dwwStateOn);


	mcwk->McwkFwequency   = memowy_cwock;
	mcwk->MpwwFuncCntw    = mpww_func_cntw;
	mcwk->MpwwFuncCntw_1  = mpww_func_cntw_1;
	mcwk->MpwwFuncCntw_2  = mpww_func_cntw_2;
	mcwk->MpwwAdFuncCntw  = mpww_ad_func_cntw;
	mcwk->MpwwDqFuncCntw  = mpww_dq_func_cntw;
	mcwk->McwkPwwmgtCntw  = mcwk_pwwmgt_cntw;
	mcwk->DwwCntw         = dww_cntw;
	mcwk->MpwwSs1         = mpww_ss1;
	mcwk->MpwwSs2         = mpww_ss2;

	wetuwn 0;
}

static uint8_t ci_get_mcwk_fwequency_watio(uint32_t memowy_cwock,
		boow stwobe_mode)
{
	uint8_t mc_pawa_index;

	if (stwobe_mode) {
		if (memowy_cwock < 12500)
			mc_pawa_index = 0x00;
		ewse if (memowy_cwock > 47500)
			mc_pawa_index = 0x0f;
		ewse
			mc_pawa_index = (uint8_t)((memowy_cwock - 10000) / 2500);
	} ewse {
		if (memowy_cwock < 65000)
			mc_pawa_index = 0x00;
		ewse if (memowy_cwock > 135000)
			mc_pawa_index = 0x0f;
		ewse
			mc_pawa_index = (uint8_t)((memowy_cwock - 60000) / 5000);
	}

	wetuwn mc_pawa_index;
}

static uint8_t ci_get_ddw3_mcwk_fwequency_watio(uint32_t memowy_cwock)
{
	uint8_t mc_pawa_index;

	if (memowy_cwock < 10000)
		mc_pawa_index = 0;
	ewse if (memowy_cwock >= 80000)
		mc_pawa_index = 0x0f;
	ewse
		mc_pawa_index = (uint8_t)((memowy_cwock - 10000) / 5000 + 1);

	wetuwn mc_pawa_index;
}

static int ci_popuwate_phase_vawue_based_on_mcwk(stwuct pp_hwmgw *hwmgw, const stwuct phm_phase_shedding_wimits_tabwe *pw,
					uint32_t memowy_cwock, uint32_t *p_shed)
{
	unsigned int i;

	*p_shed = 1;

	fow (i = 0; i < pw->count; i++) {
		if (memowy_cwock < pw->entwies[i].Mcwk) {
			*p_shed = i;
			bweak;
		}
	}

	wetuwn 0;
}

static int ci_popuwate_singwe_memowy_wevew(
		stwuct pp_hwmgw *hwmgw,
		uint32_t memowy_cwock,
		SMU7_Discwete_MemowyWevew *memowy_wevew
		)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	int wesuwt = 0;
	boow dww_state_on;
	uint32_t mcwk_edc_ww_enabwe_thweshowd = 40000;
	uint32_t mcwk_edc_enabwe_thweshowd = 40000;
	uint32_t mcwk_stwobe_mode_thweshowd = 40000;

	if (hwmgw->dyn_state.vddc_dependency_on_mcwk != NUWW) {
		wesuwt = ci_get_dependency_vowt_by_cwk(hwmgw,
			hwmgw->dyn_state.vddc_dependency_on_mcwk, memowy_cwock, &memowy_wevew->MinVddc);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"can not find MinVddc vowtage vawue fwom memowy VDDC vowtage dependency tabwe", wetuwn wesuwt);
	}

	if (NUWW != hwmgw->dyn_state.vddci_dependency_on_mcwk) {
		wesuwt = ci_get_dependency_vowt_by_cwk(hwmgw,
				hwmgw->dyn_state.vddci_dependency_on_mcwk,
				memowy_cwock,
				&memowy_wevew->MinVddci);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"can not find MinVddci vowtage vawue fwom memowy VDDCI vowtage dependency tabwe", wetuwn wesuwt);
	}

	if (NUWW != hwmgw->dyn_state.mvdd_dependency_on_mcwk) {
		wesuwt = ci_get_dependency_vowt_by_cwk(hwmgw,
				hwmgw->dyn_state.mvdd_dependency_on_mcwk,
				memowy_cwock,
				&memowy_wevew->MinMvdd);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"can not find MinVddci vowtage vawue fwom memowy MVDD vowtage dependency tabwe", wetuwn wesuwt);
	}

	memowy_wevew->MinVddcPhases = 1;

	if (data->vddc_phase_shed_contwow) {
		ci_popuwate_phase_vawue_based_on_mcwk(hwmgw, hwmgw->dyn_state.vddc_phase_shed_wimits_tabwe,
				memowy_cwock, &memowy_wevew->MinVddcPhases);
	}

	memowy_wevew->EnabwedFowThwottwe = 1;
	memowy_wevew->EnabwedFowActivity = 1;
	memowy_wevew->UpH = data->cuwwent_pwofiwe_setting.mcwk_up_hyst;
	memowy_wevew->DownH = data->cuwwent_pwofiwe_setting.mcwk_down_hyst;
	memowy_wevew->VowtageDownH = 0;

	/* Indicates maximum activity wevew fow this pewfowmance wevew.*/
	memowy_wevew->ActivityWevew = data->cuwwent_pwofiwe_setting.mcwk_activity;
	memowy_wevew->StuttewEnabwe = 0;
	memowy_wevew->StwobeEnabwe = 0;
	memowy_wevew->EdcWeadEnabwe = 0;
	memowy_wevew->EdcWwiteEnabwe = 0;
	memowy_wevew->WttEnabwe = 0;

	/* defauwt set to wow watewmawk. Highest wevew wiww be set to high watew.*/
	memowy_wevew->DispwayWatewmawk = PPSMC_DISPWAY_WATEWMAWK_WOW;

	data->dispway_timing.num_existing_dispways = hwmgw->dispway_config->num_dispway;
	data->dispway_timing.vwefwesh = hwmgw->dispway_config->vwefwesh;

	/* stuttew mode not suppowt on ci */

	/* decide stwobe mode*/
	memowy_wevew->StwobeEnabwe = (mcwk_stwobe_mode_thweshowd != 0) &&
		(memowy_cwock <= mcwk_stwobe_mode_thweshowd);

	/* decide EDC mode and memowy cwock watio*/
	if (data->is_memowy_gddw5) {
		memowy_wevew->StwobeWatio = ci_get_mcwk_fwequency_watio(memowy_cwock,
					memowy_wevew->StwobeEnabwe);

		if ((mcwk_edc_enabwe_thweshowd != 0) &&
				(memowy_cwock > mcwk_edc_enabwe_thweshowd)) {
			memowy_wevew->EdcWeadEnabwe = 1;
		}

		if ((mcwk_edc_ww_enabwe_thweshowd != 0) &&
				(memowy_cwock > mcwk_edc_ww_enabwe_thweshowd)) {
			memowy_wevew->EdcWwiteEnabwe = 1;
		}

		if (memowy_wevew->StwobeEnabwe) {
			if (ci_get_mcwk_fwequency_watio(memowy_cwock, 1) >=
					((cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC7) >> 16) & 0xf))
				dww_state_on = ((cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC5) >> 1) & 0x1) ? 1 : 0;
			ewse
				dww_state_on = ((cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC6) >> 1) & 0x1) ? 1 : 0;
		} ewse
			dww_state_on = data->dww_defauwt_on;
	} ewse {
		memowy_wevew->StwobeWatio =
			ci_get_ddw3_mcwk_fwequency_watio(memowy_cwock);
		dww_state_on = ((cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC5) >> 1) & 0x1) ? 1 : 0;
	}

	wesuwt = ci_cawcuwate_mcwk_pawams(hwmgw,
		memowy_cwock, memowy_wevew, memowy_wevew->StwobeEnabwe, dww_state_on);

	if (0 == wesuwt) {
		memowy_wevew->MinVddc = PP_HOST_TO_SMC_UW(memowy_wevew->MinVddc * VOWTAGE_SCAWE);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->MinVddcPhases);
		memowy_wevew->MinVddci = PP_HOST_TO_SMC_UW(memowy_wevew->MinVddci * VOWTAGE_SCAWE);
		memowy_wevew->MinMvdd = PP_HOST_TO_SMC_UW(memowy_wevew->MinMvdd * VOWTAGE_SCAWE);
		/* MCWK fwequency in units of 10KHz*/
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->McwkFwequency);
		/* Indicates maximum activity wevew fow this pewfowmance wevew.*/
		CONVEWT_FWOM_HOST_TO_SMC_US(memowy_wevew->ActivityWevew);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->MpwwFuncCntw);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->MpwwFuncCntw_1);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->MpwwFuncCntw_2);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->MpwwAdFuncCntw);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->MpwwDqFuncCntw);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->McwkPwwmgtCntw);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->DwwCntw);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->MpwwSs1);
		CONVEWT_FWOM_HOST_TO_SMC_UW(memowy_wevew->MpwwSs2);
	}

	wetuwn wesuwt;
}

static int ci_popuwate_aww_memowy_wevews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	stwuct smu7_dpm_tabwe *dpm_tabwe = &data->dpm_tabwe;
	int wesuwt;
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t dev_id;

	uint32_t wevew_awway_addwess = smu_data->dpm_tabwe_stawt + offsetof(SMU7_Discwete_DpmTabwe, MemowyWevew);
	uint32_t wevew_awway_size = sizeof(SMU7_Discwete_MemowyWevew) * SMU7_MAX_WEVEWS_MEMOWY;
	SMU7_Discwete_MemowyWevew *wevews = smu_data->smc_state_tabwe.MemowyWevew;
	uint32_t i;

	memset(wevews, 0x00, wevew_awway_size);

	fow (i = 0; i < dpm_tabwe->mcwk_tabwe.count; i++) {
		PP_ASSEWT_WITH_CODE((0 != dpm_tabwe->mcwk_tabwe.dpm_wevews[i].vawue),
			"can not popuwate memowy wevew as memowy cwock is zewo", wetuwn -EINVAW);
		wesuwt = ci_popuwate_singwe_memowy_wevew(hwmgw, dpm_tabwe->mcwk_tabwe.dpm_wevews[i].vawue,
			&(smu_data->smc_state_tabwe.MemowyWevew[i]));
		if (0 != wesuwt)
			wetuwn wesuwt;
	}

	smu_data->smc_state_tabwe.MemowyWevew[0].EnabwedFowActivity = 1;

	dev_id = adev->pdev->device;

	if ((dpm_tabwe->mcwk_tabwe.count >= 2)
		&& ((dev_id == 0x67B0) ||  (dev_id == 0x67B1))) {
		smu_data->smc_state_tabwe.MemowyWevew[1].MinVddci =
				smu_data->smc_state_tabwe.MemowyWevew[0].MinVddci;
		smu_data->smc_state_tabwe.MemowyWevew[1].MinMvdd =
				smu_data->smc_state_tabwe.MemowyWevew[0].MinMvdd;
	}
	smu_data->smc_state_tabwe.MemowyWevew[0].ActivityWevew = 0x1F;
	CONVEWT_FWOM_HOST_TO_SMC_US(smu_data->smc_state_tabwe.MemowyWevew[0].ActivityWevew);

	smu_data->smc_state_tabwe.MemowyDpmWevewCount = (uint8_t)dpm_tabwe->mcwk_tabwe.count;
	data->dpm_wevew_enabwe_mask.mcwk_dpm_enabwe_mask = phm_get_dpm_wevew_enabwe_mask_vawue(&dpm_tabwe->mcwk_tabwe);
	smu_data->smc_state_tabwe.MemowyWevew[dpm_tabwe->mcwk_tabwe.count-1].DispwayWatewmawk = PPSMC_DISPWAY_WATEWMAWK_HIGH;

	wesuwt = ci_copy_bytes_to_smc(hwmgw,
		wevew_awway_addwess, (uint8_t *)wevews, (uint32_t)wevew_awway_size,
		SMC_WAM_END);

	wetuwn wesuwt;
}

static int ci_popuwate_mvdd_vawue(stwuct pp_hwmgw *hwmgw, uint32_t mcwk,
					SMU7_Discwete_VowtageWevew *vowtage)
{
	const stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	uint32_t i = 0;

	if (SMU7_VOWTAGE_CONTWOW_NONE != data->mvdd_contwow) {
		/* find mvdd vawue which cwock is mowe than wequest */
		fow (i = 0; i < hwmgw->dyn_state.mvdd_dependency_on_mcwk->count; i++) {
			if (mcwk <= hwmgw->dyn_state.mvdd_dependency_on_mcwk->entwies[i].cwk) {
				/* Awways wound to highew vowtage. */
				vowtage->Vowtage = data->mvdd_vowtage_tabwe.entwies[i].vawue;
				bweak;
			}
		}

		PP_ASSEWT_WITH_CODE(i < hwmgw->dyn_state.mvdd_dependency_on_mcwk->count,
			"MVDD Vowtage is outside the suppowted wange.", wetuwn -EINVAW);

	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ci_popuwate_smc_acpi_wevew(stwuct pp_hwmgw *hwmgw,
	SMU7_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = 0;
	const stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct pp_atomctww_cwock_dividews_vi dividews;

	SMU7_Discwete_VowtageWevew vowtage_wevew;
	uint32_t spww_func_cntw    = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW;
	uint32_t spww_func_cntw_2  = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW_2;
	uint32_t dww_cntw          = data->cwock_wegistews.vDWW_CNTW;
	uint32_t mcwk_pwwmgt_cntw  = data->cwock_wegistews.vMCWK_PWWMGT_CNTW;


	/* The ACPI state shouwd not do DPM on DC (ow evew).*/
	tabwe->ACPIWevew.Fwags &= ~PPSMC_SWSTATE_FWAG_DC;

	if (data->acpi_vddc)
		tabwe->ACPIWevew.MinVddc = PP_HOST_TO_SMC_UW(data->acpi_vddc * VOWTAGE_SCAWE);
	ewse
		tabwe->ACPIWevew.MinVddc = PP_HOST_TO_SMC_UW(data->min_vddc_in_pptabwe * VOWTAGE_SCAWE);

	tabwe->ACPIWevew.MinVddcPhases = data->vddc_phase_shed_contwow ? 0 : 1;
	/* assign zewo fow now*/
	tabwe->ACPIWevew.ScwkFwequency = atomctww_get_wefewence_cwock(hwmgw);

	/* get the engine cwock dividews fow this cwock vawue*/
	wesuwt = atomctww_get_engine_pww_dividews_vi(hwmgw,
		tabwe->ACPIWevew.ScwkFwequency,  &dividews);

	PP_ASSEWT_WITH_CODE(wesuwt == 0,
		"Ewwow wetwieving Engine Cwock dividews fwom VBIOS.", wetuwn wesuwt);

	/* dividew ID fow wequiwed SCWK*/
	tabwe->ACPIWevew.ScwkDid = (uint8_t)dividews.pww_post_dividew;
	tabwe->ACPIWevew.DispwayWatewmawk = PPSMC_DISPWAY_WATEWMAWK_WOW;
	tabwe->ACPIWevew.DeepSweepDivId = 0;

	spww_func_cntw      = PHM_SET_FIEWD(spww_func_cntw,
							CG_SPWW_FUNC_CNTW,   SPWW_PWWON,     0);
	spww_func_cntw      = PHM_SET_FIEWD(spww_func_cntw,
							CG_SPWW_FUNC_CNTW,   SPWW_WESET,     1);
	spww_func_cntw_2    = PHM_SET_FIEWD(spww_func_cntw_2,
							CG_SPWW_FUNC_CNTW_2, SCWK_MUX_SEW,   4);

	tabwe->ACPIWevew.CgSpwwFuncCntw = spww_func_cntw;
	tabwe->ACPIWevew.CgSpwwFuncCntw2 = spww_func_cntw_2;
	tabwe->ACPIWevew.CgSpwwFuncCntw3 = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW_3;
	tabwe->ACPIWevew.CgSpwwFuncCntw4 = data->cwock_wegistews.vCG_SPWW_FUNC_CNTW_4;
	tabwe->ACPIWevew.SpwwSpweadSpectwum = data->cwock_wegistews.vCG_SPWW_SPWEAD_SPECTWUM;
	tabwe->ACPIWevew.SpwwSpweadSpectwum2 = data->cwock_wegistews.vCG_SPWW_SPWEAD_SPECTWUM_2;
	tabwe->ACPIWevew.CcPwwDynWm = 0;
	tabwe->ACPIWevew.CcPwwDynWm1 = 0;

	/* Fow vawious featuwes to be enabwed/disabwed whiwe this wevew is active.*/
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.Fwags);
	/* SCWK fwequency in units of 10KHz*/
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.ScwkFwequency);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CgSpwwFuncCntw);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CgSpwwFuncCntw2);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CgSpwwFuncCntw3);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CgSpwwFuncCntw4);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.SpwwSpweadSpectwum);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.SpwwSpweadSpectwum2);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CcPwwDynWm);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ACPIWevew.CcPwwDynWm1);


	/* tabwe->MemowyACPIWevew.MinVddcPhases = tabwe->ACPIWevew.MinVddcPhases;*/
	tabwe->MemowyACPIWevew.MinVddc = tabwe->ACPIWevew.MinVddc;
	tabwe->MemowyACPIWevew.MinVddcPhases = tabwe->ACPIWevew.MinVddcPhases;

	if (SMU7_VOWTAGE_CONTWOW_NONE == data->vddci_contwow)
		tabwe->MemowyACPIWevew.MinVddci = tabwe->MemowyACPIWevew.MinVddc;
	ewse {
		if (data->acpi_vddci != 0)
			tabwe->MemowyACPIWevew.MinVddci = PP_HOST_TO_SMC_UW(data->acpi_vddci * VOWTAGE_SCAWE);
		ewse
			tabwe->MemowyACPIWevew.MinVddci = PP_HOST_TO_SMC_UW(data->min_vddci_in_pptabwe * VOWTAGE_SCAWE);
	}

	if (0 == ci_popuwate_mvdd_vawue(hwmgw, 0, &vowtage_wevew))
		tabwe->MemowyACPIWevew.MinMvdd =
			PP_HOST_TO_SMC_UW(vowtage_wevew.Vowtage * VOWTAGE_SCAWE);
	ewse
		tabwe->MemowyACPIWevew.MinMvdd = 0;

	/* Fowce weset on DWW*/
	mcwk_pwwmgt_cntw    = PHM_SET_FIEWD(mcwk_pwwmgt_cntw,
		MCWK_PWWMGT_CNTW, MWDCK0_WESET, 0x1);
	mcwk_pwwmgt_cntw    = PHM_SET_FIEWD(mcwk_pwwmgt_cntw,
		MCWK_PWWMGT_CNTW, MWDCK1_WESET, 0x1);

	/* Disabwe DWW in ACPIState*/
	mcwk_pwwmgt_cntw    = PHM_SET_FIEWD(mcwk_pwwmgt_cntw,
		MCWK_PWWMGT_CNTW, MWDCK0_PDNB, 0);
	mcwk_pwwmgt_cntw    = PHM_SET_FIEWD(mcwk_pwwmgt_cntw,
		MCWK_PWWMGT_CNTW, MWDCK1_PDNB, 0);

	/* Enabwe DWW bypass signaw*/
	dww_cntw            = PHM_SET_FIEWD(dww_cntw,
		DWW_CNTW, MWDCK0_BYPASS, 0);
	dww_cntw            = PHM_SET_FIEWD(dww_cntw,
		DWW_CNTW, MWDCK1_BYPASS, 0);

	tabwe->MemowyACPIWevew.DwwCntw            =
		PP_HOST_TO_SMC_UW(dww_cntw);
	tabwe->MemowyACPIWevew.McwkPwwmgtCntw     =
		PP_HOST_TO_SMC_UW(mcwk_pwwmgt_cntw);
	tabwe->MemowyACPIWevew.MpwwAdFuncCntw     =
		PP_HOST_TO_SMC_UW(data->cwock_wegistews.vMPWW_AD_FUNC_CNTW);
	tabwe->MemowyACPIWevew.MpwwDqFuncCntw     =
		PP_HOST_TO_SMC_UW(data->cwock_wegistews.vMPWW_DQ_FUNC_CNTW);
	tabwe->MemowyACPIWevew.MpwwFuncCntw       =
		PP_HOST_TO_SMC_UW(data->cwock_wegistews.vMPWW_FUNC_CNTW);
	tabwe->MemowyACPIWevew.MpwwFuncCntw_1     =
		PP_HOST_TO_SMC_UW(data->cwock_wegistews.vMPWW_FUNC_CNTW_1);
	tabwe->MemowyACPIWevew.MpwwFuncCntw_2     =
		PP_HOST_TO_SMC_UW(data->cwock_wegistews.vMPWW_FUNC_CNTW_2);
	tabwe->MemowyACPIWevew.MpwwSs1            =
		PP_HOST_TO_SMC_UW(data->cwock_wegistews.vMPWW_SS1);
	tabwe->MemowyACPIWevew.MpwwSs2            =
		PP_HOST_TO_SMC_UW(data->cwock_wegistews.vMPWW_SS2);

	tabwe->MemowyACPIWevew.EnabwedFowThwottwe = 0;
	tabwe->MemowyACPIWevew.EnabwedFowActivity = 0;
	tabwe->MemowyACPIWevew.UpH = 0;
	tabwe->MemowyACPIWevew.DownH = 100;
	tabwe->MemowyACPIWevew.VowtageDownH = 0;
	/* Indicates maximum activity wevew fow this pewfowmance wevew.*/
	tabwe->MemowyACPIWevew.ActivityWevew = PP_HOST_TO_SMC_US(data->cuwwent_pwofiwe_setting.mcwk_activity);

	tabwe->MemowyACPIWevew.StuttewEnabwe = 0;
	tabwe->MemowyACPIWevew.StwobeEnabwe = 0;
	tabwe->MemowyACPIWevew.EdcWeadEnabwe = 0;
	tabwe->MemowyACPIWevew.EdcWwiteEnabwe = 0;
	tabwe->MemowyACPIWevew.WttEnabwe = 0;

	wetuwn wesuwt;
}

static int ci_popuwate_smc_uvd_wevew(stwuct pp_hwmgw *hwmgw,
					SMU7_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = 0;
	uint8_t count;
	stwuct pp_atomctww_cwock_dividews_vi dividews;
	stwuct phm_uvd_cwock_vowtage_dependency_tabwe *uvd_tabwe =
		hwmgw->dyn_state.uvd_cwock_vowtage_dependency_tabwe;

	tabwe->UvdWevewCount = (uint8_t)(uvd_tabwe->count);

	fow (count = 0; count < tabwe->UvdWevewCount; count++) {
		tabwe->UvdWevew[count].VcwkFwequency =
					uvd_tabwe->entwies[count].vcwk;
		tabwe->UvdWevew[count].DcwkFwequency =
					uvd_tabwe->entwies[count].dcwk;
		tabwe->UvdWevew[count].MinVddc =
					uvd_tabwe->entwies[count].v * VOWTAGE_SCAWE;
		tabwe->UvdWevew[count].MinVddcPhases = 1;

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
		CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->UvdWevew[count].MinVddc);
	}

	wetuwn wesuwt;
}

static int ci_popuwate_smc_vce_wevew(stwuct pp_hwmgw *hwmgw,
		SMU7_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = -EINVAW;
	uint8_t count;
	stwuct pp_atomctww_cwock_dividews_vi dividews;
	stwuct phm_vce_cwock_vowtage_dependency_tabwe *vce_tabwe =
				hwmgw->dyn_state.vce_cwock_vowtage_dependency_tabwe;

	tabwe->VceWevewCount = (uint8_t)(vce_tabwe->count);
	tabwe->VceBootWevew = 0;

	fow (count = 0; count < tabwe->VceWevewCount; count++) {
		tabwe->VceWevew[count].Fwequency = vce_tabwe->entwies[count].evcwk;
		tabwe->VceWevew[count].MinVowtage =
				vce_tabwe->entwies[count].v * VOWTAGE_SCAWE;
		tabwe->VceWevew[count].MinPhases = 1;

		wesuwt = atomctww_get_dfs_pww_dividews_vi(hwmgw,
				tabwe->VceWevew[count].Fwequency, &dividews);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
				"can not find divide id fow VCE engine cwock",
				wetuwn wesuwt);

		tabwe->VceWevew[count].Dividew = (uint8_t)dividews.pww_post_dividew;

		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->VceWevew[count].Fwequency);
		CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->VceWevew[count].MinVowtage);
	}
	wetuwn wesuwt;
}

static int ci_popuwate_smc_acp_wevew(stwuct pp_hwmgw *hwmgw,
					SMU7_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = -EINVAW;
	uint8_t count;
	stwuct pp_atomctww_cwock_dividews_vi dividews;
	stwuct phm_acp_cwock_vowtage_dependency_tabwe *acp_tabwe =
				hwmgw->dyn_state.acp_cwock_vowtage_dependency_tabwe;

	tabwe->AcpWevewCount = (uint8_t)(acp_tabwe->count);
	tabwe->AcpBootWevew = 0;

	fow (count = 0; count < tabwe->AcpWevewCount; count++) {
		tabwe->AcpWevew[count].Fwequency = acp_tabwe->entwies[count].acpcwk;
		tabwe->AcpWevew[count].MinVowtage = acp_tabwe->entwies[count].v;
		tabwe->AcpWevew[count].MinPhases = 1;

		wesuwt = atomctww_get_dfs_pww_dividews_vi(hwmgw,
				tabwe->AcpWevew[count].Fwequency, &dividews);
		PP_ASSEWT_WITH_CODE((0 == wesuwt),
				"can not find divide id fow engine cwock", wetuwn wesuwt);

		tabwe->AcpWevew[count].Dividew = (uint8_t)dividews.pww_post_dividew;

		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->AcpWevew[count].Fwequency);
		CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->AcpWevew[count].MinVowtage);
	}
	wetuwn wesuwt;
}

static int ci_popuwate_memowy_timing_pawametews(
		stwuct pp_hwmgw *hwmgw,
		uint32_t engine_cwock,
		uint32_t memowy_cwock,
		stwuct SMU7_Discwete_MCAwbDwamTimingTabweEntwy *awb_wegs
		)
{
	uint32_t dwamTiming;
	uint32_t dwamTiming2;
	uint32_t buwstTime;
	int wesuwt;

	wesuwt = atomctww_set_engine_dwam_timings_wv770(hwmgw,
				engine_cwock, memowy_cwock);

	PP_ASSEWT_WITH_CODE(wesuwt == 0,
		"Ewwow cawwing VBIOS to set DWAM_TIMING.", wetuwn wesuwt);

	dwamTiming  = cgs_wead_wegistew(hwmgw->device, mmMC_AWB_DWAM_TIMING);
	dwamTiming2 = cgs_wead_wegistew(hwmgw->device, mmMC_AWB_DWAM_TIMING2);
	buwstTime = PHM_WEAD_FIEWD(hwmgw->device, MC_AWB_BUWST_TIME, STATE0);

	awb_wegs->McAwbDwamTiming  = PP_HOST_TO_SMC_UW(dwamTiming);
	awb_wegs->McAwbDwamTiming2 = PP_HOST_TO_SMC_UW(dwamTiming2);
	awb_wegs->McAwbBuwstTime = (uint8_t)buwstTime;

	wetuwn 0;
}

static int ci_pwogwam_memowy_timing_pawametews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	int wesuwt = 0;
	SMU7_Discwete_MCAwbDwamTimingTabwe  awb_wegs;
	uint32_t i, j;

	memset(&awb_wegs, 0x00, sizeof(SMU7_Discwete_MCAwbDwamTimingTabwe));

	fow (i = 0; i < data->dpm_tabwe.scwk_tabwe.count; i++) {
		fow (j = 0; j < data->dpm_tabwe.mcwk_tabwe.count; j++) {
			wesuwt = ci_popuwate_memowy_timing_pawametews
				(hwmgw, data->dpm_tabwe.scwk_tabwe.dpm_wevews[i].vawue,
				 data->dpm_tabwe.mcwk_tabwe.dpm_wevews[j].vawue,
				 &awb_wegs.entwies[i][j]);

			if (0 != wesuwt)
				bweak;
		}
	}

	if (0 == wesuwt) {
		wesuwt = ci_copy_bytes_to_smc(
				hwmgw,
				smu_data->awb_tabwe_stawt,
				(uint8_t *)&awb_wegs,
				sizeof(SMU7_Discwete_MCAwbDwamTimingTabwe),
				SMC_WAM_END
				);
	}

	wetuwn wesuwt;
}

static int ci_popuwate_smc_boot_wevew(stwuct pp_hwmgw *hwmgw,
			SMU7_Discwete_DpmTabwe *tabwe)
{
	int wesuwt = 0;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);

	tabwe->GwaphicsBootWevew = 0;
	tabwe->MemowyBootWevew = 0;

	/* find boot wevew fwom dpm tabwe*/
	wesuwt = phm_find_boot_wevew(&(data->dpm_tabwe.scwk_tabwe),
			data->vbios_boot_state.scwk_bootup_vawue,
			(uint32_t *)&(smu_data->smc_state_tabwe.GwaphicsBootWevew));

	if (0 != wesuwt) {
		smu_data->smc_state_tabwe.GwaphicsBootWevew = 0;
		pw_eww("VBIOS did not find boot engine cwock vawue in dependency tabwe. Using Gwaphics DPM wevew 0!\n");
		wesuwt = 0;
	}

	wesuwt = phm_find_boot_wevew(&(data->dpm_tabwe.mcwk_tabwe),
		data->vbios_boot_state.mcwk_bootup_vawue,
		(uint32_t *)&(smu_data->smc_state_tabwe.MemowyBootWevew));

	if (0 != wesuwt) {
		smu_data->smc_state_tabwe.MemowyBootWevew = 0;
		pw_eww("VBIOS did not find boot engine cwock vawue in dependency tabwe. Using Memowy DPM wevew 0!\n");
		wesuwt = 0;
	}

	tabwe->BootVddc = data->vbios_boot_state.vddc_bootup_vawue;
	tabwe->BootVddci = data->vbios_boot_state.vddci_bootup_vawue;
	tabwe->BootMVdd = data->vbios_boot_state.mvdd_bootup_vawue;

	wetuwn wesuwt;
}

static int ci_popuwate_mc_weg_addwess(stwuct pp_hwmgw *hwmgw,
				 SMU7_Discwete_MCWegistews *mc_weg_tabwe)
{
	const stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)hwmgw->smu_backend;

	uint32_t i, j;

	fow (i = 0, j = 0; j < smu_data->mc_weg_tabwe.wast; j++) {
		if (smu_data->mc_weg_tabwe.vawidfwag & 1<<j) {
			PP_ASSEWT_WITH_CODE(i < SMU7_DISCWETE_MC_WEGISTEW_AWWAY_SIZE,
				"Index of mc_weg_tabwe->addwess[] awway out of boundawy", wetuwn -EINVAW);
			mc_weg_tabwe->addwess[i].s0 =
				PP_HOST_TO_SMC_US(smu_data->mc_weg_tabwe.mc_weg_addwess[j].s0);
			mc_weg_tabwe->addwess[i].s1 =
				PP_HOST_TO_SMC_US(smu_data->mc_weg_tabwe.mc_weg_addwess[j].s1);
			i++;
		}
	}

	mc_weg_tabwe->wast = (uint8_t)i;

	wetuwn 0;
}

static void ci_convewt_mc_wegistews(
	const stwuct ci_mc_weg_entwy *entwy,
	SMU7_Discwete_MCWegistewSet *data,
	uint32_t num_entwies, uint32_t vawid_fwag)
{
	uint32_t i, j;

	fow (i = 0, j = 0; j < num_entwies; j++) {
		if (vawid_fwag & 1<<j) {
			data->vawue[i] = PP_HOST_TO_SMC_UW(entwy->mc_data[j]);
			i++;
		}
	}
}

static int ci_convewt_mc_weg_tabwe_entwy_to_smc(
		stwuct pp_hwmgw *hwmgw,
		const uint32_t memowy_cwock,
		SMU7_Discwete_MCWegistewSet *mc_weg_tabwe_data
		)
{
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	uint32_t i = 0;

	fow (i = 0; i < smu_data->mc_weg_tabwe.num_entwies; i++) {
		if (memowy_cwock <=
			smu_data->mc_weg_tabwe.mc_weg_tabwe_entwy[i].mcwk_max) {
			bweak;
		}
	}

	if ((i == smu_data->mc_weg_tabwe.num_entwies) && (i > 0))
		--i;

	ci_convewt_mc_wegistews(&smu_data->mc_weg_tabwe.mc_weg_tabwe_entwy[i],
				mc_weg_tabwe_data, smu_data->mc_weg_tabwe.wast,
				smu_data->mc_weg_tabwe.vawidfwag);

	wetuwn 0;
}

static int ci_convewt_mc_weg_tabwe_to_smc(stwuct pp_hwmgw *hwmgw,
		SMU7_Discwete_MCWegistews *mc_wegs)
{
	int wesuwt = 0;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	int wes;
	uint32_t i;

	fow (i = 0; i < data->dpm_tabwe.mcwk_tabwe.count; i++) {
		wes = ci_convewt_mc_weg_tabwe_entwy_to_smc(
				hwmgw,
				data->dpm_tabwe.mcwk_tabwe.dpm_wevews[i].vawue,
				&mc_wegs->data[i]
				);

		if (0 != wes)
			wesuwt = wes;
	}

	wetuwn wesuwt;
}

static int ci_update_and_upwoad_mc_weg_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint32_t addwess;
	int32_t wesuwt;

	if (0 == (data->need_update_smu7_dpm_tabwe & DPMTABWE_OD_UPDATE_MCWK))
		wetuwn 0;


	memset(&smu_data->mc_wegs, 0, sizeof(SMU7_Discwete_MCWegistews));

	wesuwt = ci_convewt_mc_weg_tabwe_to_smc(hwmgw, &(smu_data->mc_wegs));

	if (wesuwt != 0)
		wetuwn wesuwt;

	addwess = smu_data->mc_weg_tabwe_stawt + (uint32_t)offsetof(SMU7_Discwete_MCWegistews, data[0]);

	wetuwn  ci_copy_bytes_to_smc(hwmgw, addwess,
				 (uint8_t *)&smu_data->mc_wegs.data[0],
				sizeof(SMU7_Discwete_MCWegistewSet) * data->dpm_tabwe.mcwk_tabwe.count,
				SMC_WAM_END);
}

static int ci_popuwate_initiaw_mc_weg_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);

	memset(&smu_data->mc_wegs, 0x00, sizeof(SMU7_Discwete_MCWegistews));
	wesuwt = ci_popuwate_mc_weg_addwess(hwmgw, &(smu_data->mc_wegs));
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize MCWegTabwe fow the MC wegistew addwesses!", wetuwn wesuwt;);

	wesuwt = ci_convewt_mc_weg_tabwe_to_smc(hwmgw, &smu_data->mc_wegs);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize MCWegTabwe fow dwivew state!", wetuwn wesuwt;);

	wetuwn ci_copy_bytes_to_smc(hwmgw, smu_data->mc_weg_tabwe_stawt,
			(uint8_t *)&smu_data->mc_wegs, sizeof(SMU7_Discwete_MCWegistews), SMC_WAM_END);
}

static int ci_popuwate_smc_initiaw_state(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	uint8_t count, wevew;

	count = (uint8_t)(hwmgw->dyn_state.vddc_dependency_on_scwk->count);

	fow (wevew = 0; wevew < count; wevew++) {
		if (hwmgw->dyn_state.vddc_dependency_on_scwk->entwies[wevew].cwk
			 >= data->vbios_boot_state.scwk_bootup_vawue) {
			smu_data->smc_state_tabwe.GwaphicsBootWevew = wevew;
			bweak;
		}
	}

	count = (uint8_t)(hwmgw->dyn_state.vddc_dependency_on_mcwk->count);

	fow (wevew = 0; wevew < count; wevew++) {
		if (hwmgw->dyn_state.vddc_dependency_on_mcwk->entwies[wevew].cwk
			>= data->vbios_boot_state.mcwk_bootup_vawue) {
			smu_data->smc_state_tabwe.MemowyBootWevew = wevew;
			bweak;
		}
	}

	wetuwn 0;
}

static int ci_popuwate_smc_svi2_config(stwuct pp_hwmgw *hwmgw,
					    SMU7_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vowtage_contwow)
		tabwe->SVI2Enabwe = 1;
	ewse
		tabwe->SVI2Enabwe = 0;
	wetuwn 0;
}

static int ci_stawt_smc(stwuct pp_hwmgw *hwmgw)
{
	/* set smc instwuct stawt point at 0x0 */
	ci_pwogwam_jump_on_stawt(hwmgw);

	/* enabwe smc cwock */
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, SMC_SYSCON_CWOCK_CNTW_0, ck_disabwe, 0);

	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, SMC_SYSCON_WESET_CNTW, wst_weg, 0);

	PHM_WAIT_INDIWECT_FIEWD(hwmgw, SMC_IND, FIWMWAWE_FWAGS,
				 INTEWWUPTS_ENABWED, 1);

	wetuwn 0;
}

static int ci_popuwate_vw_config(stwuct pp_hwmgw *hwmgw, SMU7_Discwete_DpmTabwe *tabwe)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	uint16_t config;

	config = VW_SVI2_PWANE_1;
	tabwe->VWConfig |= (config<<VWCONF_VDDGFX_SHIFT);

	if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vowtage_contwow) {
		config = VW_SVI2_PWANE_2;
		tabwe->VWConfig |= config;
	} ewse {
		pw_info("VDDCshouwd be on SVI2 contwowwew!");
	}

	if (SMU7_VOWTAGE_CONTWOW_BY_SVID2 == data->vddci_contwow) {
		config = VW_SVI2_PWANE_2;
		tabwe->VWConfig |= (config<<VWCONF_VDDCI_SHIFT);
	} ewse if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->vddci_contwow) {
		config = VW_SMIO_PATTEWN_1;
		tabwe->VWConfig |= (config<<VWCONF_VDDCI_SHIFT);
	}

	if (SMU7_VOWTAGE_CONTWOW_BY_GPIO == data->mvdd_contwow) {
		config = VW_SMIO_PATTEWN_2;
		tabwe->VWConfig |= (config<<VWCONF_MVDD_SHIFT);
	}

	wetuwn 0;
}

static int ci_init_smc_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	SMU7_Discwete_DpmTabwe  *tabwe = &(smu_data->smc_state_tabwe);
	stwuct pp_atomctww_gpio_pin_assignment gpio_pin;
	u32 i;

	ci_initiawize_powew_tune_defauwts(hwmgw);
	memset(&(smu_data->smc_state_tabwe), 0x00, sizeof(smu_data->smc_state_tabwe));

	if (SMU7_VOWTAGE_CONTWOW_NONE != data->vowtage_contwow)
		ci_popuwate_smc_vowtage_tabwes(hwmgw, tabwe);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_AutomaticDCTwansition))
		tabwe->SystemFwags |= PPSMC_SYSTEMFWAG_GPIO_DC;


	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_StepVddc))
		tabwe->SystemFwags |= PPSMC_SYSTEMFWAG_STEPVDDC;

	if (data->is_memowy_gddw5)
		tabwe->SystemFwags |= PPSMC_SYSTEMFWAG_GDDW5;

	if (data->uwv_suppowted) {
		wesuwt = ci_popuwate_uwv_state(hwmgw, &(tabwe->Uwv));
		PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to initiawize UWV state!", wetuwn wesuwt);

		cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC,
			ixCG_UWV_PAWAMETEW, 0x40035);
	}

	wesuwt = ci_popuwate_aww_gwaphic_wevews(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize Gwaphics Wevew!", wetuwn wesuwt);

	wesuwt = ci_popuwate_aww_memowy_wevews(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize Memowy Wevew!", wetuwn wesuwt);

	wesuwt = ci_popuwate_smc_wink_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize Wink Wevew!", wetuwn wesuwt);

	wesuwt = ci_popuwate_smc_acpi_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize ACPI Wevew!", wetuwn wesuwt);

	wesuwt = ci_popuwate_smc_vce_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize VCE Wevew!", wetuwn wesuwt);

	wesuwt = ci_popuwate_smc_acp_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize ACP Wevew!", wetuwn wesuwt);

	/* Since onwy the initiaw state is compwetewy set up at this point (the othew states awe just copies of the boot state) we onwy */
	/* need to popuwate the  AWB settings fow the initiaw state. */
	wesuwt = ci_pwogwam_memowy_timing_pawametews(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to Wwite AWB settings fow the initiaw state.", wetuwn wesuwt);

	wesuwt = ci_popuwate_smc_uvd_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize UVD Wevew!", wetuwn wesuwt);

	tabwe->UvdBootWevew  = 0;
	tabwe->VceBootWevew  = 0;
	tabwe->AcpBootWevew  = 0;
	tabwe->SamuBootWevew  = 0;

	tabwe->GwaphicsBootWevew = 0;
	tabwe->MemowyBootWevew = 0;

	wesuwt = ci_popuwate_smc_boot_wevew(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to initiawize Boot Wevew!", wetuwn wesuwt);

	wesuwt = ci_popuwate_smc_initiaw_state(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt, "Faiwed to initiawize Boot State!", wetuwn wesuwt);

	wesuwt = ci_popuwate_bapm_pawametews_in_dpm_tabwe(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt, "Faiwed to popuwate BAPM Pawametews!", wetuwn wesuwt);

	tabwe->UVDIntewvaw = 1;
	tabwe->VCEIntewvaw = 1;
	tabwe->ACPIntewvaw = 1;
	tabwe->SAMUIntewvaw = 1;
	tabwe->GwaphicsVowtageChangeEnabwe  = 1;
	tabwe->GwaphicsThewmThwottweEnabwe  = 1;
	tabwe->GwaphicsIntewvaw = 1;
	tabwe->VowtageIntewvaw  = 1;
	tabwe->ThewmawIntewvaw  = 1;

	tabwe->TempewatuweWimitHigh =
		(data->thewmaw_temp_setting.tempewatuwe_high *
		 SMU7_Q88_FOWMAT_CONVEWSION_UNIT) / PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	tabwe->TempewatuweWimitWow =
		(data->thewmaw_temp_setting.tempewatuwe_wow *
		SMU7_Q88_FOWMAT_CONVEWSION_UNIT) / PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;

	tabwe->MemowyVowtageChangeEnabwe  = 1;
	tabwe->MemowyIntewvaw  = 1;
	tabwe->VowtageWesponseTime  = 0;
	tabwe->VddcVddciDewta = 4000;
	tabwe->PhaseWesponseTime  = 0;
	tabwe->MemowyThewmThwottweEnabwe  = 1;

	PP_ASSEWT_WITH_CODE((1 <= data->dpm_tabwe.pcie_speed_tabwe.count),
			"Thewe must be 1 ow mowe PCIE wevews defined in PPTabwe.",
			wetuwn -EINVAW);

	tabwe->PCIeBootWinkWevew = (uint8_t)data->dpm_tabwe.pcie_speed_tabwe.count;
	tabwe->PCIeGenIntewvaw = 1;

	wesuwt = ci_popuwate_vw_config(hwmgw, tabwe);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to popuwate VWConfig setting!", wetuwn wesuwt);
	data->vw_config = tabwe->VWConfig;

	ci_popuwate_smc_svi2_config(hwmgw, tabwe);

	fow (i = 0; i < SMU7_MAX_ENTWIES_SMIO; i++)
		CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->Smio[i]);

	tabwe->ThewmGpio  = 17;
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

	tabwe->AcDcGpio = SMU7_UNUSED_GPIO_PIN;

	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SystemFwags);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->VWConfig);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SmioMaskVddcVid);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SmioMaskVddcPhase);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SmioMaskVddciVid);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->SmioMaskMvddVid);
	CONVEWT_FWOM_HOST_TO_SMC_UW(tabwe->ScwkStepSize);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->TempewatuweWimitHigh);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->TempewatuweWimitWow);
	tabwe->VddcVddciDewta = PP_HOST_TO_SMC_US(tabwe->VddcVddciDewta);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->VowtageWesponseTime);
	CONVEWT_FWOM_HOST_TO_SMC_US(tabwe->PhaseWesponseTime);

	tabwe->BootVddc = PP_HOST_TO_SMC_US(tabwe->BootVddc * VOWTAGE_SCAWE);
	tabwe->BootVddci = PP_HOST_TO_SMC_US(tabwe->BootVddci * VOWTAGE_SCAWE);
	tabwe->BootMVdd = PP_HOST_TO_SMC_US(tabwe->BootMVdd * VOWTAGE_SCAWE);

	/* Upwoad aww dpm data to SMC memowy.(dpm wevew, dpm wevew count etc) */
	wesuwt = ci_copy_bytes_to_smc(hwmgw, smu_data->dpm_tabwe_stawt +
					offsetof(SMU7_Discwete_DpmTabwe, SystemFwags),
					(uint8_t *)&(tabwe->SystemFwags),
					sizeof(SMU7_Discwete_DpmTabwe)-3 * sizeof(SMU7_PIDContwowwew),
					SMC_WAM_END);

	PP_ASSEWT_WITH_CODE(0 == wesuwt,
		"Faiwed to upwoad dpm data to SMC memowy!", wetuwn wesuwt;);

	wesuwt = ci_popuwate_initiaw_mc_weg_tabwe(hwmgw);
	PP_ASSEWT_WITH_CODE((0 == wesuwt),
		"Faiwed to popuwate initiawize MC Weg tabwe!", wetuwn wesuwt);

	wesuwt = ci_popuwate_pm_fuses(hwmgw);
	PP_ASSEWT_WITH_CODE(0 == wesuwt,
			"Faiwed to  popuwate PM fuses to SMC memowy!", wetuwn wesuwt);

	ci_stawt_smc(hwmgw);

	wetuwn 0;
}

static int ci_thewmaw_setup_fan_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct ci_smumgw *ci_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	SMU7_Discwete_FanTabwe fan_tabwe = { FDO_MODE_HAWDWAWE };
	uint32_t duty100;
	uint32_t t_diff1, t_diff2, pwm_diff1, pwm_diff2;
	uint16_t fdo_min, swope1, swope2;
	uint32_t wefewence_cwock;
	int wes;
	uint64_t tmp64;

	if (!phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_MicwocodeFanContwow))
		wetuwn 0;

	if (hwmgw->thewmaw_contwowwew.fanInfo.bNoFan) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_MicwocodeFanContwow);
		wetuwn 0;
	}

	if (0 == ci_data->fan_tabwe_stawt) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_MicwocodeFanContwow);
		wetuwn 0;
	}

	duty100 = PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, CG_FDO_CTWW1, FMAX_DUTY100);

	if (0 == duty100) {
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_MicwocodeFanContwow);
		wetuwn 0;
	}

	tmp64 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMin * duty100;
	do_div(tmp64, 10000);
	fdo_min = (uint16_t)tmp64;

	t_diff1 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMed - hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMin;
	t_diff2 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTHigh - hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMed;

	pwm_diff1 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMed - hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMin;
	pwm_diff2 = hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMHigh - hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMed;

	swope1 = (uint16_t)((50 + ((16 * duty100 * pwm_diff1) / t_diff1)) / 100);
	swope2 = (uint16_t)((50 + ((16 * duty100 * pwm_diff2) / t_diff2)) / 100);

	fan_tabwe.TempMin = cpu_to_be16((50 + hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMin) / 100);
	fan_tabwe.TempMed = cpu_to_be16((50 + hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMed) / 100);
	fan_tabwe.TempMax = cpu_to_be16((50 + hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMax) / 100);

	fan_tabwe.Swope1 = cpu_to_be16(swope1);
	fan_tabwe.Swope2 = cpu_to_be16(swope2);

	fan_tabwe.FdoMin = cpu_to_be16(fdo_min);

	fan_tabwe.HystDown = cpu_to_be16(hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucTHyst);

	fan_tabwe.HystUp = cpu_to_be16(1);

	fan_tabwe.HystSwope = cpu_to_be16(1);

	fan_tabwe.TempWespWim = cpu_to_be16(5);

	wefewence_cwock = amdgpu_asic_get_xcwk((stwuct amdgpu_device *)hwmgw->adev);

	fan_tabwe.WefweshPewiod = cpu_to_be32((hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.uwCycweDeway * wefewence_cwock) / 1600);

	fan_tabwe.FdoMax = cpu_to_be16((uint16_t)duty100);

	fan_tabwe.TempSwc = (uint8_t)PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, CG_MUWT_THEWMAW_CTWW, TEMP_SEW);

	wes = ci_copy_bytes_to_smc(hwmgw, ci_data->fan_tabwe_stawt, (uint8_t *)&fan_tabwe, (uint32_t)sizeof(fan_tabwe), SMC_WAM_END);

	wetuwn wes;
}

static int ci_pwogwam_mem_timing_pawametews(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	if (data->need_update_smu7_dpm_tabwe &
			(DPMTABWE_OD_UPDATE_SCWK | DPMTABWE_OD_UPDATE_MCWK))
		wetuwn ci_pwogwam_memowy_timing_pawametews(hwmgw);

	wetuwn 0;
}

static int ci_update_scwk_thweshowd(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);

	int wesuwt = 0;
	uint32_t wow_scwk_intewwupt_thweshowd = 0;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ScwkThwottweWowNotification)
		&& (data->wow_scwk_intewwupt_thweshowd != 0)) {
		wow_scwk_intewwupt_thweshowd =
				data->wow_scwk_intewwupt_thweshowd;

		CONVEWT_FWOM_HOST_TO_SMC_UW(wow_scwk_intewwupt_thweshowd);

		wesuwt = ci_copy_bytes_to_smc(
				hwmgw,
				smu_data->dpm_tabwe_stawt +
				offsetof(SMU7_Discwete_DpmTabwe,
					WowScwkIntewwuptT),
				(uint8_t *)&wow_scwk_intewwupt_thweshowd,
				sizeof(uint32_t),
				SMC_WAM_END);
	}

	wesuwt = ci_update_and_upwoad_mc_weg_tabwe(hwmgw);

	PP_ASSEWT_WITH_CODE((0 == wesuwt), "Faiwed to upwoad MC weg tabwe!", wetuwn wesuwt);

	wesuwt = ci_pwogwam_mem_timing_pawametews(hwmgw);
	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			"Faiwed to pwogwam memowy timing pawametews!",
			);

	wetuwn wesuwt;
}

static uint32_t ci_get_offsetof(uint32_t type, uint32_t membew)
{
	switch (type) {
	case SMU_SoftWegistews:
		switch (membew) {
		case HandshakeDisabwes:
			wetuwn offsetof(SMU7_SoftWegistews, HandshakeDisabwes);
		case VowtageChangeTimeout:
			wetuwn offsetof(SMU7_SoftWegistews, VowtageChangeTimeout);
		case AvewageGwaphicsActivity:
			wetuwn offsetof(SMU7_SoftWegistews, AvewageGwaphicsA);
		case AvewageMemowyActivity:
			wetuwn offsetof(SMU7_SoftWegistews, AvewageMemowyA);
		case PweVBwankGap:
			wetuwn offsetof(SMU7_SoftWegistews, PweVBwankGap);
		case VBwankTimeout:
			wetuwn offsetof(SMU7_SoftWegistews, VBwankTimeout);
		case DWAM_WOG_ADDW_H:
			wetuwn offsetof(SMU7_SoftWegistews, DWAM_WOG_ADDW_H);
		case DWAM_WOG_ADDW_W:
			wetuwn offsetof(SMU7_SoftWegistews, DWAM_WOG_ADDW_W);
		case DWAM_WOG_PHY_ADDW_H:
			wetuwn offsetof(SMU7_SoftWegistews, DWAM_WOG_PHY_ADDW_H);
		case DWAM_WOG_PHY_ADDW_W:
			wetuwn offsetof(SMU7_SoftWegistews, DWAM_WOG_PHY_ADDW_W);
		case DWAM_WOG_BUFF_SIZE:
			wetuwn offsetof(SMU7_SoftWegistews, DWAM_WOG_BUFF_SIZE);
		}
		bweak;
	case SMU_Discwete_DpmTabwe:
		switch (membew) {
		case WowScwkIntewwuptThweshowd:
			wetuwn offsetof(SMU7_Discwete_DpmTabwe, WowScwkIntewwuptT);
		}
		bweak;
	}
	pw_debug("can't get the offset of type %x membew %x\n", type, membew);
	wetuwn 0;
}

static uint32_t ci_get_mac_definition(uint32_t vawue)
{
	switch (vawue) {
	case SMU_MAX_WEVEWS_GWAPHICS:
		wetuwn SMU7_MAX_WEVEWS_GWAPHICS;
	case SMU_MAX_WEVEWS_MEMOWY:
		wetuwn SMU7_MAX_WEVEWS_MEMOWY;
	case SMU_MAX_WEVEWS_WINK:
		wetuwn SMU7_MAX_WEVEWS_WINK;
	case SMU_MAX_ENTWIES_SMIO:
		wetuwn SMU7_MAX_ENTWIES_SMIO;
	case SMU_MAX_WEVEWS_VDDC:
	case SMU_MAX_WEVEWS_VDDGFX:
		wetuwn SMU7_MAX_WEVEWS_VDDC;
	case SMU_MAX_WEVEWS_VDDCI:
		wetuwn SMU7_MAX_WEVEWS_VDDCI;
	case SMU_MAX_WEVEWS_MVDD:
		wetuwn SMU7_MAX_WEVEWS_MVDD;
	}

	pw_debug("can't get the mac of %x\n", vawue);
	wetuwn 0;
}

static int ci_woad_smc_ucode(stwuct pp_hwmgw *hwmgw)
{
	uint32_t byte_count, stawt_addw;
	uint8_t *swc;
	uint32_t data;

	stwuct cgs_fiwmwawe_info info = {0};

	cgs_get_fiwmwawe_info(hwmgw->device, CGS_UCODE_ID_SMU, &info);

	hwmgw->is_kickew = info.is_kickew;
	hwmgw->smu_vewsion = info.vewsion;
	byte_count = info.image_size;
	swc = (uint8_t *)info.kptw;
	stawt_addw = info.ucode_stawt_addwess;

	if  (byte_count > SMC_WAM_END) {
		pw_eww("SMC addwess is beyond the SMC WAM awea.\n");
		wetuwn -EINVAW;
	}

	cgs_wwite_wegistew(hwmgw->device, mmSMC_IND_INDEX_0, stawt_addw);
	PHM_WWITE_FIEWD(hwmgw->device, SMC_IND_ACCESS_CNTW, AUTO_INCWEMENT_IND_0, 1);

	fow (; byte_count >= 4; byte_count -= 4) {
		data = (swc[0] << 24) | (swc[1] << 16) | (swc[2] << 8) | swc[3];
		cgs_wwite_wegistew(hwmgw->device, mmSMC_IND_DATA_0, data);
		swc += 4;
	}
	PHM_WWITE_FIEWD(hwmgw->device, SMC_IND_ACCESS_CNTW, AUTO_INCWEMENT_IND_0, 0);

	if (0 != byte_count) {
		pw_eww("SMC size must be divisibwe by 4\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ci_upwoad_fiwmwawe(stwuct pp_hwmgw *hwmgw)
{
	if (ci_is_smc_wam_wunning(hwmgw)) {
		pw_info("smc is wunning, no need to woad smc fiwmwawe\n");
		wetuwn 0;
	}
	PHM_WAIT_INDIWECT_FIEWD(hwmgw, SMC_IND, WCU_UC_EVENTS,
			boot_seq_done, 1);
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, SMC_SYSCON_MISC_CNTW,
			pwe_fetchew_en, 1);

	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, SMC_SYSCON_CWOCK_CNTW_0, ck_disabwe, 1);
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, SMC_SYSCON_WESET_CNTW, wst_weg, 1);
	wetuwn ci_woad_smc_ucode(hwmgw);
}

static int ci_pwocess_fiwmwawe_headew(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct ci_smumgw *ci_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);

	uint32_t tmp = 0;
	int wesuwt;
	boow ewwow = fawse;

	if (ci_upwoad_fiwmwawe(hwmgw))
		wetuwn -EINVAW;

	wesuwt = ci_wead_smc_swam_dwowd(hwmgw,
				SMU7_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU7_Fiwmwawe_Headew, DpmTabwe),
				&tmp, SMC_WAM_END);

	if (0 == wesuwt)
		ci_data->dpm_tabwe_stawt = tmp;

	ewwow |= (0 != wesuwt);

	wesuwt = ci_wead_smc_swam_dwowd(hwmgw,
				SMU7_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU7_Fiwmwawe_Headew, SoftWegistews),
				&tmp, SMC_WAM_END);

	if (0 == wesuwt) {
		data->soft_wegs_stawt = tmp;
		ci_data->soft_wegs_stawt = tmp;
	}

	ewwow |= (0 != wesuwt);

	wesuwt = ci_wead_smc_swam_dwowd(hwmgw,
				SMU7_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU7_Fiwmwawe_Headew, mcWegistewTabwe),
				&tmp, SMC_WAM_END);

	if (0 == wesuwt)
		ci_data->mc_weg_tabwe_stawt = tmp;

	wesuwt = ci_wead_smc_swam_dwowd(hwmgw,
				SMU7_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU7_Fiwmwawe_Headew, FanTabwe),
				&tmp, SMC_WAM_END);

	if (0 == wesuwt)
		ci_data->fan_tabwe_stawt = tmp;

	ewwow |= (0 != wesuwt);

	wesuwt = ci_wead_smc_swam_dwowd(hwmgw,
				SMU7_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU7_Fiwmwawe_Headew, mcAwbDwamTimingTabwe),
				&tmp, SMC_WAM_END);

	if (0 == wesuwt)
		ci_data->awb_tabwe_stawt = tmp;

	ewwow |= (0 != wesuwt);

	wesuwt = ci_wead_smc_swam_dwowd(hwmgw,
				SMU7_FIWMWAWE_HEADEW_WOCATION +
				offsetof(SMU7_Fiwmwawe_Headew, Vewsion),
				&tmp, SMC_WAM_END);

	if (0 == wesuwt)
		hwmgw->micwocode_vewsion_info.SMC = tmp;

	ewwow |= (0 != wesuwt);

	wetuwn ewwow ? 1 : 0;
}

static uint8_t ci_get_memowy_modiwe_index(stwuct pp_hwmgw *hwmgw)
{
	wetuwn (uint8_t) (0xFF & (cgs_wead_wegistew(hwmgw->device, mmBIOS_SCWATCH_4) >> 16));
}

static boow ci_check_s0_mc_weg_index(uint16_t in_weg, uint16_t *out_weg)
{
	boow wesuwt = twue;

	switch (in_weg) {
	case  mmMC_SEQ_WAS_TIMING:
		*out_weg = mmMC_SEQ_WAS_TIMING_WP;
		bweak;

	case  mmMC_SEQ_DWW_STBY:
		*out_weg = mmMC_SEQ_DWW_STBY_WP;
		bweak;

	case  mmMC_SEQ_G5PDX_CMD0:
		*out_weg = mmMC_SEQ_G5PDX_CMD0_WP;
		bweak;

	case  mmMC_SEQ_G5PDX_CMD1:
		*out_weg = mmMC_SEQ_G5PDX_CMD1_WP;
		bweak;

	case  mmMC_SEQ_G5PDX_CTWW:
		*out_weg = mmMC_SEQ_G5PDX_CTWW_WP;
		bweak;

	case mmMC_SEQ_CAS_TIMING:
		*out_weg = mmMC_SEQ_CAS_TIMING_WP;
		bweak;

	case mmMC_SEQ_MISC_TIMING:
		*out_weg = mmMC_SEQ_MISC_TIMING_WP;
		bweak;

	case mmMC_SEQ_MISC_TIMING2:
		*out_weg = mmMC_SEQ_MISC_TIMING2_WP;
		bweak;

	case mmMC_SEQ_PMG_DVS_CMD:
		*out_weg = mmMC_SEQ_PMG_DVS_CMD_WP;
		bweak;

	case mmMC_SEQ_PMG_DVS_CTW:
		*out_weg = mmMC_SEQ_PMG_DVS_CTW_WP;
		bweak;

	case mmMC_SEQ_WD_CTW_D0:
		*out_weg = mmMC_SEQ_WD_CTW_D0_WP;
		bweak;

	case mmMC_SEQ_WD_CTW_D1:
		*out_weg = mmMC_SEQ_WD_CTW_D1_WP;
		bweak;

	case mmMC_SEQ_WW_CTW_D0:
		*out_weg = mmMC_SEQ_WW_CTW_D0_WP;
		bweak;

	case mmMC_SEQ_WW_CTW_D1:
		*out_weg = mmMC_SEQ_WW_CTW_D1_WP;
		bweak;

	case mmMC_PMG_CMD_EMWS:
		*out_weg = mmMC_SEQ_PMG_CMD_EMWS_WP;
		bweak;

	case mmMC_PMG_CMD_MWS:
		*out_weg = mmMC_SEQ_PMG_CMD_MWS_WP;
		bweak;

	case mmMC_PMG_CMD_MWS1:
		*out_weg = mmMC_SEQ_PMG_CMD_MWS1_WP;
		bweak;

	case mmMC_SEQ_PMG_TIMING:
		*out_weg = mmMC_SEQ_PMG_TIMING_WP;
		bweak;

	case mmMC_PMG_CMD_MWS2:
		*out_weg = mmMC_SEQ_PMG_CMD_MWS2_WP;
		bweak;

	case mmMC_SEQ_WW_CTW_2:
		*out_weg = mmMC_SEQ_WW_CTW_2_WP;
		bweak;

	defauwt:
		wesuwt = fawse;
		bweak;
	}

	wetuwn wesuwt;
}

static int ci_set_s0_mc_weg_index(stwuct ci_mc_weg_tabwe *tabwe)
{
	uint32_t i;
	uint16_t addwess;

	fow (i = 0; i < tabwe->wast; i++) {
		tabwe->mc_weg_addwess[i].s0 =
			ci_check_s0_mc_weg_index(tabwe->mc_weg_addwess[i].s1, &addwess)
			? addwess : tabwe->mc_weg_addwess[i].s1;
	}
	wetuwn 0;
}

static int ci_copy_vbios_smc_weg_tabwe(const pp_atomctww_mc_weg_tabwe *tabwe,
					stwuct ci_mc_weg_tabwe *ni_tabwe)
{
	uint8_t i, j;

	PP_ASSEWT_WITH_CODE((tabwe->wast <= SMU7_DISCWETE_MC_WEGISTEW_AWWAY_SIZE),
		"Invawid VwamInfo tabwe.", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE((tabwe->num_entwies <= MAX_AC_TIMING_ENTWIES),
		"Invawid VwamInfo tabwe.", wetuwn -EINVAW);

	fow (i = 0; i < tabwe->wast; i++)
		ni_tabwe->mc_weg_addwess[i].s1 = tabwe->mc_weg_addwess[i].s1;

	ni_tabwe->wast = tabwe->wast;

	fow (i = 0; i < tabwe->num_entwies; i++) {
		ni_tabwe->mc_weg_tabwe_entwy[i].mcwk_max =
			tabwe->mc_weg_tabwe_entwy[i].mcwk_max;
		fow (j = 0; j < tabwe->wast; j++) {
			ni_tabwe->mc_weg_tabwe_entwy[i].mc_data[j] =
				tabwe->mc_weg_tabwe_entwy[i].mc_data[j];
		}
	}

	ni_tabwe->num_entwies = tabwe->num_entwies;

	wetuwn 0;
}

static int ci_set_mc_speciaw_wegistews(stwuct pp_hwmgw *hwmgw,
					stwuct ci_mc_weg_tabwe *tabwe)
{
	uint8_t i, j, k;
	uint32_t temp_weg;
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	fow (i = 0, j = tabwe->wast; i < tabwe->wast; i++) {
		PP_ASSEWT_WITH_CODE((j < SMU7_DISCWETE_MC_WEGISTEW_AWWAY_SIZE),
			"Invawid VwamInfo tabwe.", wetuwn -EINVAW);

		switch (tabwe->mc_weg_addwess[i].s1) {

		case mmMC_SEQ_MISC1:
			temp_weg = cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_EMWS);
			tabwe->mc_weg_addwess[j].s1 = mmMC_PMG_CMD_EMWS;
			tabwe->mc_weg_addwess[j].s0 = mmMC_SEQ_PMG_CMD_EMWS_WP;
			fow (k = 0; k < tabwe->num_entwies; k++) {
				tabwe->mc_weg_tabwe_entwy[k].mc_data[j] =
					((temp_weg & 0xffff0000)) |
					((tabwe->mc_weg_tabwe_entwy[k].mc_data[i] & 0xffff0000) >> 16);
			}
			j++;

			PP_ASSEWT_WITH_CODE((j < SMU7_DISCWETE_MC_WEGISTEW_AWWAY_SIZE),
				"Invawid VwamInfo tabwe.", wetuwn -EINVAW);
			temp_weg = cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_MWS);
			tabwe->mc_weg_addwess[j].s1 = mmMC_PMG_CMD_MWS;
			tabwe->mc_weg_addwess[j].s0 = mmMC_SEQ_PMG_CMD_MWS_WP;
			fow (k = 0; k < tabwe->num_entwies; k++) {
				tabwe->mc_weg_tabwe_entwy[k].mc_data[j] =
					(temp_weg & 0xffff0000) |
					(tabwe->mc_weg_tabwe_entwy[k].mc_data[i] & 0x0000ffff);

				if (!data->is_memowy_gddw5)
					tabwe->mc_weg_tabwe_entwy[k].mc_data[j] |= 0x100;
			}
			j++;

			if (!data->is_memowy_gddw5) {
				PP_ASSEWT_WITH_CODE((j < SMU7_DISCWETE_MC_WEGISTEW_AWWAY_SIZE),
					"Invawid VwamInfo tabwe.", wetuwn -EINVAW);
				tabwe->mc_weg_addwess[j].s1 = mmMC_PMG_AUTO_CMD;
				tabwe->mc_weg_addwess[j].s0 = mmMC_PMG_AUTO_CMD;
				fow (k = 0; k < tabwe->num_entwies; k++) {
					tabwe->mc_weg_tabwe_entwy[k].mc_data[j] =
						(tabwe->mc_weg_tabwe_entwy[k].mc_data[i] & 0xffff0000) >> 16;
				}
				j++;
			}

			bweak;

		case mmMC_SEQ_WESEWVE_M:
			temp_weg = cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_MWS1);
			tabwe->mc_weg_addwess[j].s1 = mmMC_PMG_CMD_MWS1;
			tabwe->mc_weg_addwess[j].s0 = mmMC_SEQ_PMG_CMD_MWS1_WP;
			fow (k = 0; k < tabwe->num_entwies; k++) {
				tabwe->mc_weg_tabwe_entwy[k].mc_data[j] =
					(temp_weg & 0xffff0000) |
					(tabwe->mc_weg_tabwe_entwy[k].mc_data[i] & 0x0000ffff);
			}
			j++;
			bweak;

		defauwt:
			bweak;
		}

	}

	tabwe->wast = j;

	wetuwn 0;
}

static int ci_set_vawid_fwag(stwuct ci_mc_weg_tabwe *tabwe)
{
	uint8_t i, j;

	fow (i = 0; i < tabwe->wast; i++) {
		fow (j = 1; j < tabwe->num_entwies; j++) {
			if (tabwe->mc_weg_tabwe_entwy[j-1].mc_data[i] !=
				tabwe->mc_weg_tabwe_entwy[j].mc_data[i]) {
				tabwe->vawidfwag |= (1 << i);
				bweak;
			}
		}
	}

	wetuwn 0;
}

static int ci_initiawize_mc_weg_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)(hwmgw->smu_backend);
	pp_atomctww_mc_weg_tabwe *tabwe;
	stwuct ci_mc_weg_tabwe *ni_tabwe = &smu_data->mc_weg_tabwe;
	uint8_t moduwe_index = ci_get_memowy_modiwe_index(hwmgw);

	tabwe = kzawwoc(sizeof(pp_atomctww_mc_weg_tabwe), GFP_KEWNEW);

	if (NUWW == tabwe)
		wetuwn -ENOMEM;

	/* Pwogwam additionaw WP wegistews that awe no wongew pwogwammed by VBIOS */
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WAS_TIMING_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WAS_TIMING));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_CAS_TIMING_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_CAS_TIMING));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_DWW_STBY_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_DWW_STBY));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CMD0_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CMD0));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CMD1_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CMD1));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CTWW_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_G5PDX_CTWW));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_DVS_CMD_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_PMG_DVS_CMD));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_DVS_CTW_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_PMG_DVS_CTW));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_MISC_TIMING_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC_TIMING));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_MISC_TIMING2_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_MISC_TIMING2));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_CMD_EMWS_WP, cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_EMWS));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_CMD_MWS_WP, cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_MWS));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_CMD_MWS1_WP, cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_MWS1));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_D0_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_D0));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_D1_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_D1));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WD_CTW_D0_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WD_CTW_D0));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WD_CTW_D1_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WD_CTW_D1));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_TIMING_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_PMG_TIMING));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_PMG_CMD_MWS2_WP, cgs_wead_wegistew(hwmgw->device, mmMC_PMG_CMD_MWS2));
	cgs_wwite_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_2_WP, cgs_wead_wegistew(hwmgw->device, mmMC_SEQ_WW_CTW_2));

	wesuwt = atomctww_initiawize_mc_weg_tabwe(hwmgw, moduwe_index, tabwe);

	if (0 == wesuwt)
		wesuwt = ci_copy_vbios_smc_weg_tabwe(tabwe, ni_tabwe);

	if (0 == wesuwt) {
		ci_set_s0_mc_weg_index(ni_tabwe);
		wesuwt = ci_set_mc_speciaw_wegistews(hwmgw, ni_tabwe);
	}

	if (0 == wesuwt)
		ci_set_vawid_fwag(ni_tabwe);

	kfwee(tabwe);

	wetuwn wesuwt;
}

static boow ci_is_dpm_wunning(stwuct pp_hwmgw *hwmgw)
{
	wetuwn ci_is_smc_wam_wunning(hwmgw);
}

static int ci_smu_init(stwuct pp_hwmgw *hwmgw)
{
	stwuct ci_smumgw *ci_pwiv;

	ci_pwiv = kzawwoc(sizeof(stwuct ci_smumgw), GFP_KEWNEW);

	if (ci_pwiv == NUWW)
		wetuwn -ENOMEM;

	hwmgw->smu_backend = ci_pwiv;

	wetuwn 0;
}

static int ci_smu_fini(stwuct pp_hwmgw *hwmgw)
{
	kfwee(hwmgw->smu_backend);
	hwmgw->smu_backend = NUWW;
	wetuwn 0;
}

static int ci_stawt_smu(stwuct pp_hwmgw *hwmgw)
{
	wetuwn 0;
}

static int ci_update_dpm_settings(stwuct pp_hwmgw *hwmgw,
				void *pwofiwe_setting)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);
	stwuct ci_smumgw *smu_data = (stwuct ci_smumgw *)
			(hwmgw->smu_backend);
	stwuct pwofiwe_mode_setting *setting;
	stwuct SMU7_Discwete_GwaphicsWevew *wevews =
			smu_data->smc_state_tabwe.GwaphicsWevew;
	uint32_t awway = smu_data->dpm_tabwe_stawt +
			offsetof(SMU7_Discwete_DpmTabwe, GwaphicsWevew);

	uint32_t mcwk_awway = smu_data->dpm_tabwe_stawt +
			offsetof(SMU7_Discwete_DpmTabwe, MemowyWevew);
	stwuct SMU7_Discwete_MemowyWevew *mcwk_wevews =
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

				cwk_activity_offset = awway + (sizeof(SMU7_Discwete_GwaphicsWevew) * i)
						+ offsetof(SMU7_Discwete_GwaphicsWevew, ActivityWevew);
				offset = cwk_activity_offset & ~0x3;
				tmp = PP_HOST_TO_SMC_UW(cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset));
				tmp = phm_set_fiewd_to_u32(cwk_activity_offset, tmp, wevews[i].ActivityWevew, sizeof(uint16_t));
				cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset, PP_HOST_TO_SMC_UW(tmp));

			}
			if (wevews[i].UpH != setting->scwk_up_hyst ||
				wevews[i].DownH != setting->scwk_down_hyst) {
				wevews[i].UpH = setting->scwk_up_hyst;
				wevews[i].DownH = setting->scwk_down_hyst;
				up_hyst_offset = awway + (sizeof(SMU7_Discwete_GwaphicsWevew) * i)
						+ offsetof(SMU7_Discwete_GwaphicsWevew, UpH);
				down_hyst_offset = awway + (sizeof(SMU7_Discwete_GwaphicsWevew) * i)
						+ offsetof(SMU7_Discwete_GwaphicsWevew, DownH);
				offset = up_hyst_offset & ~0x3;
				tmp = PP_HOST_TO_SMC_UW(cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset));
				tmp = phm_set_fiewd_to_u32(up_hyst_offset, tmp, wevews[i].UpH, sizeof(uint8_t));
				tmp = phm_set_fiewd_to_u32(down_hyst_offset, tmp, wevews[i].DownH, sizeof(uint8_t));
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

				cwk_activity_offset = mcwk_awway + (sizeof(SMU7_Discwete_MemowyWevew) * i)
						+ offsetof(SMU7_Discwete_MemowyWevew, ActivityWevew);
				offset = cwk_activity_offset & ~0x3;
				tmp = PP_HOST_TO_SMC_UW(cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset));
				tmp = phm_set_fiewd_to_u32(cwk_activity_offset, tmp, mcwk_wevews[i].ActivityWevew, sizeof(uint16_t));
				cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset, PP_HOST_TO_SMC_UW(tmp));

			}
			if (mcwk_wevews[i].UpH != setting->mcwk_up_hyst ||
				mcwk_wevews[i].DownH != setting->mcwk_down_hyst) {
				mcwk_wevews[i].UpH = setting->mcwk_up_hyst;
				mcwk_wevews[i].DownH = setting->mcwk_down_hyst;
				up_hyst_offset = mcwk_awway + (sizeof(SMU7_Discwete_MemowyWevew) * i)
						+ offsetof(SMU7_Discwete_MemowyWevew, UpH);
				down_hyst_offset = mcwk_awway + (sizeof(SMU7_Discwete_MemowyWevew) * i)
						+ offsetof(SMU7_Discwete_MemowyWevew, DownH);
				offset = up_hyst_offset & ~0x3;
				tmp = PP_HOST_TO_SMC_UW(cgs_wead_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset));
				tmp = phm_set_fiewd_to_u32(up_hyst_offset, tmp, mcwk_wevews[i].UpH, sizeof(uint8_t));
				tmp = phm_set_fiewd_to_u32(down_hyst_offset, tmp, mcwk_wevews[i].DownH, sizeof(uint8_t));
				cgs_wwite_ind_wegistew(hwmgw->device, CGS_IND_WEG__SMC, offset, PP_HOST_TO_SMC_UW(tmp));
			}
		}
		if (!data->mcwk_dpm_key_disabwed)
			smum_send_msg_to_smc(hwmgw, PPSMC_MSG_MCWKDPM_UnfweezeWevew, NUWW);
	}
	wetuwn 0;
}

static int ci_update_uvd_smc_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	stwuct smu7_hwmgw *data = hwmgw->backend;
	stwuct ci_smumgw *smu_data = hwmgw->smu_backend;
	stwuct phm_uvd_cwock_vowtage_dependency_tabwe *uvd_tabwe =
			hwmgw->dyn_state.uvd_cwock_vowtage_dependency_tabwe;
	uint32_t pwofiwe_mode_mask = AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD |
					AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK |
					AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK |
					AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK;
	uint32_t max_vddc = adev->pm.ac_powew ? hwmgw->dyn_state.max_cwock_vowtage_on_ac.vddc :
						hwmgw->dyn_state.max_cwock_vowtage_on_dc.vddc;
	int32_t i;

	if (PP_CAP(PHM_PwatfowmCaps_UVDDPM) || uvd_tabwe->count <= 0)
		smu_data->smc_state_tabwe.UvdBootWevew = 0;
	ewse
		smu_data->smc_state_tabwe.UvdBootWevew = uvd_tabwe->count - 1;

	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, DPM_TABWE_475,
				UvdBootWevew, smu_data->smc_state_tabwe.UvdBootWevew);

	data->dpm_wevew_enabwe_mask.uvd_dpm_enabwe_mask = 0;

	fow (i = uvd_tabwe->count - 1; i >= 0; i--) {
		if (uvd_tabwe->entwies[i].v <= max_vddc)
			data->dpm_wevew_enabwe_mask.uvd_dpm_enabwe_mask |= 1 << i;
		if (hwmgw->dpm_wevew & pwofiwe_mode_mask || !PP_CAP(PHM_PwatfowmCaps_UVDDPM))
			bweak;
	}
	smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_UVDDPM_SetEnabwedMask,
				data->dpm_wevew_enabwe_mask.uvd_dpm_enabwe_mask,
				NUWW);

	wetuwn 0;
}

static int ci_update_vce_smc_tabwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	stwuct smu7_hwmgw *data = hwmgw->backend;
	stwuct phm_vce_cwock_vowtage_dependency_tabwe *vce_tabwe =
			hwmgw->dyn_state.vce_cwock_vowtage_dependency_tabwe;
	uint32_t pwofiwe_mode_mask = AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD |
					AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK |
					AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK |
					AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK;
	uint32_t max_vddc = adev->pm.ac_powew ? hwmgw->dyn_state.max_cwock_vowtage_on_ac.vddc :
						hwmgw->dyn_state.max_cwock_vowtage_on_dc.vddc;
	int32_t i;

	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC, DPM_TABWE_475,
				VceBootWevew, 0); /* temp hawd code to wevew 0, vce can set min evcwk*/

	data->dpm_wevew_enabwe_mask.vce_dpm_enabwe_mask = 0;

	fow (i = vce_tabwe->count - 1; i >= 0; i--) {
		if (vce_tabwe->entwies[i].v <= max_vddc)
			data->dpm_wevew_enabwe_mask.vce_dpm_enabwe_mask |= 1 << i;
		if (hwmgw->dpm_wevew & pwofiwe_mode_mask || !PP_CAP(PHM_PwatfowmCaps_VCEDPM))
			bweak;
	}
	smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_MSG_VCEDPM_SetEnabwedMask,
				data->dpm_wevew_enabwe_mask.vce_dpm_enabwe_mask,
				NUWW);

	wetuwn 0;
}

static int ci_update_smc_tabwe(stwuct pp_hwmgw *hwmgw, uint32_t type)
{
	switch (type) {
	case SMU_UVD_TABWE:
		ci_update_uvd_smc_tabwe(hwmgw);
		bweak;
	case SMU_VCE_TABWE:
		ci_update_vce_smc_tabwe(hwmgw);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static void ci_weset_smc(stwuct pp_hwmgw *hwmgw)
{
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
				  SMC_SYSCON_WESET_CNTW,
				  wst_weg, 1);
}


static void ci_stop_smc_cwock(stwuct pp_hwmgw *hwmgw)
{
	PHM_WWITE_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
				  SMC_SYSCON_CWOCK_CNTW_0,
				  ck_disabwe, 1);
}

static int ci_stop_smc(stwuct pp_hwmgw *hwmgw)
{
	ci_weset_smc(hwmgw);
	ci_stop_smc_cwock(hwmgw);

	wetuwn 0;
}

const stwuct pp_smumgw_func ci_smu_funcs = {
	.name = "ci_smu",
	.smu_init = ci_smu_init,
	.smu_fini = ci_smu_fini,
	.stawt_smu = ci_stawt_smu,
	.check_fw_woad_finish = NUWW,
	.wequest_smu_woad_fw = NUWW,
	.wequest_smu_woad_specific_fw = NUWW,
	.send_msg_to_smc = ci_send_msg_to_smc,
	.send_msg_to_smc_with_pawametew = ci_send_msg_to_smc_with_pawametew,
	.get_awgument = smu7_get_awgument,
	.downwoad_pptabwe_settings = NUWW,
	.upwoad_pptabwe_settings = NUWW,
	.get_offsetof = ci_get_offsetof,
	.pwocess_fiwmwawe_headew = ci_pwocess_fiwmwawe_headew,
	.init_smc_tabwe = ci_init_smc_tabwe,
	.update_scwk_thweshowd = ci_update_scwk_thweshowd,
	.thewmaw_setup_fan_tabwe = ci_thewmaw_setup_fan_tabwe,
	.popuwate_aww_gwaphic_wevews = ci_popuwate_aww_gwaphic_wevews,
	.popuwate_aww_memowy_wevews = ci_popuwate_aww_memowy_wevews,
	.get_mac_definition = ci_get_mac_definition,
	.initiawize_mc_weg_tabwe = ci_initiawize_mc_weg_tabwe,
	.is_dpm_wunning = ci_is_dpm_wunning,
	.update_dpm_settings = ci_update_dpm_settings,
	.update_smc_tabwe = ci_update_smc_tabwe,
	.stop_smc = ci_stop_smc,
};
