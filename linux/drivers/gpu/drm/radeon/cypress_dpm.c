/*
 * Copywight 2011 Advanced Micwo Devices, Inc.
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
 * Authows: Awex Deuchew
 */

#incwude <winux/pci.h>

#incwude "atom.h"
#incwude "cypwess_dpm.h"
#incwude "evewgween.h"
#incwude "evewgweend.h"
#incwude "w600_dpm.h"
#incwude "wv770.h"
#incwude "wadeon.h"
#incwude "wadeon_asic.h"

#define SMC_WAM_END 0x8000

#define MC_CG_AWB_FWEQ_F0           0x0a
#define MC_CG_AWB_FWEQ_F1           0x0b
#define MC_CG_AWB_FWEQ_F2           0x0c
#define MC_CG_AWB_FWEQ_F3           0x0d

#define MC_CG_SEQ_DWAMCONF_S0       0x05
#define MC_CG_SEQ_DWAMCONF_S1       0x06
#define MC_CG_SEQ_YCWK_SUSPEND      0x04
#define MC_CG_SEQ_YCWK_WESUME       0x0a

static void cypwess_enabwe_bif_dynamic_pcie_gen2(stwuct wadeon_device *wdev,
						 boow enabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 tmp, bif;

	tmp = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
	if (enabwe) {
		if ((tmp & WC_OTHEW_SIDE_EVEW_SENT_GEN2) &&
		    (tmp & WC_OTHEW_SIDE_SUPPOWTS_GEN2)) {
			if (!pi->boot_in_gen2) {
				bif = WWEG32(CG_BIF_WEQ_AND_WSP) & ~CG_CWIENT_WEQ_MASK;
				bif |= CG_CWIENT_WEQ(0xd);
				WWEG32(CG_BIF_WEQ_AND_WSP, bif);

				tmp &= ~WC_HW_VOWTAGE_IF_CONTWOW_MASK;
				tmp |= WC_HW_VOWTAGE_IF_CONTWOW(1);
				tmp |= WC_GEN2_EN_STWAP;

				tmp |= WC_CWW_FAIWED_SPD_CHANGE_CNT;
				WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, tmp);
				udeway(10);
				tmp &= ~WC_CWW_FAIWED_SPD_CHANGE_CNT;
				WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, tmp);
			}
		}
	} ewse {
		if (!pi->boot_in_gen2) {
			tmp &= ~WC_HW_VOWTAGE_IF_CONTWOW_MASK;
			tmp &= ~WC_GEN2_EN_STWAP;
		}
		if ((tmp & WC_OTHEW_SIDE_EVEW_SENT_GEN2) ||
		    (tmp & WC_OTHEW_SIDE_SUPPOWTS_GEN2))
			WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, tmp);
	}
}

static void cypwess_enabwe_dynamic_pcie_gen2(stwuct wadeon_device *wdev,
					     boow enabwe)
{
	cypwess_enabwe_bif_dynamic_pcie_gen2(wdev, enabwe);

	if (enabwe)
		WWEG32_P(GENEWAW_PWWMGT, ENABWE_GEN2PCIE, ~ENABWE_GEN2PCIE);
	ewse
		WWEG32_P(GENEWAW_PWWMGT, 0, ~ENABWE_GEN2PCIE);
}

#if 0
static int cypwess_entew_uwp_state(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	if (pi->gfx_cwock_gating) {
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~DYN_GFX_CWK_OFF_EN);
		WWEG32_P(SCWK_PWWMGT_CNTW, GFX_CWK_FOWCE_ON, ~GFX_CWK_FOWCE_ON);
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~GFX_CWK_FOWCE_ON);

		WWEG32(GB_ADDW_CONFIG);
	}

	WWEG32_P(SMC_MSG, HOST_SMC_MSG(PPSMC_MSG_SwitchToMinimumPowew),
		 ~HOST_SMC_MSG_MASK);

	udeway(7000);

	wetuwn 0;
}
#endif

static void cypwess_gfx_cwock_gating_enabwe(stwuct wadeon_device *wdev,
					    boow enabwe)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);

	if (enabwe) {
		if (eg_pi->wight_sweep) {
			WWEG32(GWBM_GFX_INDEX, 0xC0000000);

			WWEG32_CG(CG_CGWS_TIWE_0, 0xFFFFFFFF);
			WWEG32_CG(CG_CGWS_TIWE_1, 0xFFFFFFFF);
			WWEG32_CG(CG_CGWS_TIWE_2, 0xFFFFFFFF);
			WWEG32_CG(CG_CGWS_TIWE_3, 0xFFFFFFFF);
			WWEG32_CG(CG_CGWS_TIWE_4, 0xFFFFFFFF);
			WWEG32_CG(CG_CGWS_TIWE_5, 0xFFFFFFFF);
			WWEG32_CG(CG_CGWS_TIWE_6, 0xFFFFFFFF);
			WWEG32_CG(CG_CGWS_TIWE_7, 0xFFFFFFFF);
			WWEG32_CG(CG_CGWS_TIWE_8, 0xFFFFFFFF);
			WWEG32_CG(CG_CGWS_TIWE_9, 0xFFFFFFFF);
			WWEG32_CG(CG_CGWS_TIWE_10, 0xFFFFFFFF);
			WWEG32_CG(CG_CGWS_TIWE_11, 0xFFFFFFFF);

			WWEG32_P(SCWK_PWWMGT_CNTW, DYN_WIGHT_SWEEP_EN, ~DYN_WIGHT_SWEEP_EN);
		}
		WWEG32_P(SCWK_PWWMGT_CNTW, DYN_GFX_CWK_OFF_EN, ~DYN_GFX_CWK_OFF_EN);
	} ewse {
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~DYN_GFX_CWK_OFF_EN);
		WWEG32_P(SCWK_PWWMGT_CNTW, GFX_CWK_FOWCE_ON, ~GFX_CWK_FOWCE_ON);
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~GFX_CWK_FOWCE_ON);
		WWEG32(GB_ADDW_CONFIG);

		if (eg_pi->wight_sweep) {
			WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~DYN_WIGHT_SWEEP_EN);

			WWEG32(GWBM_GFX_INDEX, 0xC0000000);

			WWEG32_CG(CG_CGWS_TIWE_0, 0);
			WWEG32_CG(CG_CGWS_TIWE_1, 0);
			WWEG32_CG(CG_CGWS_TIWE_2, 0);
			WWEG32_CG(CG_CGWS_TIWE_3, 0);
			WWEG32_CG(CG_CGWS_TIWE_4, 0);
			WWEG32_CG(CG_CGWS_TIWE_5, 0);
			WWEG32_CG(CG_CGWS_TIWE_6, 0);
			WWEG32_CG(CG_CGWS_TIWE_7, 0);
			WWEG32_CG(CG_CGWS_TIWE_8, 0);
			WWEG32_CG(CG_CGWS_TIWE_9, 0);
			WWEG32_CG(CG_CGWS_TIWE_10, 0);
			WWEG32_CG(CG_CGWS_TIWE_11, 0);
		}
	}
}

static void cypwess_mg_cwock_gating_enabwe(stwuct wadeon_device *wdev,
					   boow enabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);

	if (enabwe) {
		u32 cgts_sm_ctww_weg;

		if (wdev->famiwy == CHIP_CEDAW)
			cgts_sm_ctww_weg = CEDAW_MGCGCGTSSMCTWW_DFWT;
		ewse if (wdev->famiwy == CHIP_WEDWOOD)
			cgts_sm_ctww_weg = WEDWOOD_MGCGCGTSSMCTWW_DFWT;
		ewse
			cgts_sm_ctww_weg = CYPWESS_MGCGCGTSSMCTWW_DFWT;

		WWEG32(GWBM_GFX_INDEX, 0xC0000000);

		WWEG32_CG(CG_CGTT_WOCAW_0, CYPWESS_MGCGTTWOCAW0_DFWT);
		WWEG32_CG(CG_CGTT_WOCAW_1, CYPWESS_MGCGTTWOCAW1_DFWT & 0xFFFFCFFF);
		WWEG32_CG(CG_CGTT_WOCAW_2, CYPWESS_MGCGTTWOCAW2_DFWT);
		WWEG32_CG(CG_CGTT_WOCAW_3, CYPWESS_MGCGTTWOCAW3_DFWT);

		if (pi->mgcgtssm)
			WWEG32(CGTS_SM_CTWW_WEG, cgts_sm_ctww_weg);

		if (eg_pi->mcws) {
			WWEG32_P(MC_CITF_MISC_WD_CG, MEM_WS_ENABWE, ~MEM_WS_ENABWE);
			WWEG32_P(MC_CITF_MISC_WW_CG, MEM_WS_ENABWE, ~MEM_WS_ENABWE);
			WWEG32_P(MC_CITF_MISC_VM_CG, MEM_WS_ENABWE, ~MEM_WS_ENABWE);
			WWEG32_P(MC_HUB_MISC_HUB_CG, MEM_WS_ENABWE, ~MEM_WS_ENABWE);
			WWEG32_P(MC_HUB_MISC_VM_CG, MEM_WS_ENABWE, ~MEM_WS_ENABWE);
			WWEG32_P(MC_HUB_MISC_SIP_CG, MEM_WS_ENABWE, ~MEM_WS_ENABWE);
			WWEG32_P(MC_XPB_CWK_GAT, MEM_WS_ENABWE, ~MEM_WS_ENABWE);
			WWEG32_P(VM_W2_CG, MEM_WS_ENABWE, ~MEM_WS_ENABWE);
		}
	} ewse {
		WWEG32(GWBM_GFX_INDEX, 0xC0000000);

		WWEG32_CG(CG_CGTT_WOCAW_0, 0xFFFFFFFF);
		WWEG32_CG(CG_CGTT_WOCAW_1, 0xFFFFFFFF);
		WWEG32_CG(CG_CGTT_WOCAW_2, 0xFFFFFFFF);
		WWEG32_CG(CG_CGTT_WOCAW_3, 0xFFFFFFFF);

		if (pi->mgcgtssm)
			WWEG32(CGTS_SM_CTWW_WEG, 0x81f44bc0);
	}
}

void cypwess_enabwe_spwead_spectwum(stwuct wadeon_device *wdev,
				    boow enabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	if (enabwe) {
		if (pi->scwk_ss)
			WWEG32_P(GENEWAW_PWWMGT, DYN_SPWEAD_SPECTWUM_EN, ~DYN_SPWEAD_SPECTWUM_EN);

		if (pi->mcwk_ss)
			WWEG32_P(MPWW_CNTW_MODE, SS_SSEN, ~SS_SSEN);
	} ewse {
		WWEG32_P(CG_SPWW_SPWEAD_SPECTWUM, 0, ~SSEN);
		WWEG32_P(GENEWAW_PWWMGT, 0, ~DYN_SPWEAD_SPECTWUM_EN);
		WWEG32_P(MPWW_CNTW_MODE, 0, ~SS_SSEN);
		WWEG32_P(MPWW_CNTW_MODE, 0, ~SS_DSMODE_EN);
	}
}

void cypwess_stawt_dpm(stwuct wadeon_device *wdev)
{
	WWEG32_P(GENEWAW_PWWMGT, GWOBAW_PWWMGT_EN, ~GWOBAW_PWWMGT_EN);
}

void cypwess_enabwe_scwk_contwow(stwuct wadeon_device *wdev,
				 boow enabwe)
{
	if (enabwe)
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~SCWK_PWWMGT_OFF);
	ewse
		WWEG32_P(SCWK_PWWMGT_CNTW, SCWK_PWWMGT_OFF, ~SCWK_PWWMGT_OFF);
}

void cypwess_enabwe_mcwk_contwow(stwuct wadeon_device *wdev,
				 boow enabwe)
{
	if (enabwe)
		WWEG32_P(MCWK_PWWMGT_CNTW, 0, ~MPWW_PWWMGT_OFF);
	ewse
		WWEG32_P(MCWK_PWWMGT_CNTW, MPWW_PWWMGT_OFF, ~MPWW_PWWMGT_OFF);
}

int cypwess_notify_smc_dispway_change(stwuct wadeon_device *wdev,
				      boow has_dispway)
{
	PPSMC_Msg msg = has_dispway ?
		(PPSMC_Msg)PPSMC_MSG_HasDispway : (PPSMC_Msg)PPSMC_MSG_NoDispway;

	if (wv770_send_msg_to_smc(wdev, msg) != PPSMC_Wesuwt_OK)
		wetuwn -EINVAW;

	wetuwn 0;
}

void cypwess_pwogwam_wesponse_times(stwuct wadeon_device *wdev)
{
	u32 wefewence_cwock;
	u32 mcwk_switch_wimit;

	wefewence_cwock = wadeon_get_xcwk(wdev);
	mcwk_switch_wimit = (460 * wefewence_cwock) / 100;

	wv770_wwite_smc_soft_wegistew(wdev,
				      WV770_SMC_SOFT_WEGISTEW_mcwk_switch_wim,
				      mcwk_switch_wimit);

	wv770_wwite_smc_soft_wegistew(wdev,
				      WV770_SMC_SOFT_WEGISTEW_mvdd_chg_time, 1);

	wv770_wwite_smc_soft_wegistew(wdev,
				      WV770_SMC_SOFT_WEGISTEW_mc_bwock_deway, 0xAA);

	wv770_pwogwam_wesponse_times(wdev);

	if (ASIC_IS_WOMBOK(wdev))
		wv770_wwite_smc_soft_wegistew(wdev,
					      WV770_SMC_SOFT_WEGISTEW_is_asic_wombok, 1);

}

static int cypwess_pcie_pewfowmance_wequest(stwuct wadeon_device *wdev,
					    u8 pewf_weq, boow advewtise)
{
#if defined(CONFIG_ACPI)
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
#endif
	u32 tmp;

	udeway(10);
	tmp = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
	if ((pewf_weq == PCIE_PEWF_WEQ_PECI_GEN1) && (tmp & WC_CUWWENT_DATA_WATE))
		wetuwn 0;

#if defined(CONFIG_ACPI)
	if ((pewf_weq == PCIE_PEWF_WEQ_PECI_GEN1) ||
	    (pewf_weq == PCIE_PEWF_WEQ_PECI_GEN2)) {
		eg_pi->pcie_pewfowmance_wequest_wegistewed = twue;
		wetuwn wadeon_acpi_pcie_pewfowmance_wequest(wdev, pewf_weq, advewtise);
	} ewse if ((pewf_weq == PCIE_PEWF_WEQ_WEMOVE_WEGISTWY) &&
		   eg_pi->pcie_pewfowmance_wequest_wegistewed) {
		eg_pi->pcie_pewfowmance_wequest_wegistewed = fawse;
		wetuwn wadeon_acpi_pcie_pewfowmance_wequest(wdev, pewf_weq, advewtise);
	}
#endif

	wetuwn 0;
}

void cypwess_advewtise_gen2_capabiwity(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 tmp;

#if defined(CONFIG_ACPI)
	wadeon_acpi_pcie_notify_device_weady(wdev);
#endif

	tmp = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);

	if ((tmp & WC_OTHEW_SIDE_EVEW_SENT_GEN2) &&
	    (tmp & WC_OTHEW_SIDE_SUPPOWTS_GEN2))
		pi->pcie_gen2 = twue;
	ewse
		pi->pcie_gen2 = fawse;

	if (!pi->pcie_gen2)
		cypwess_pcie_pewfowmance_wequest(wdev, PCIE_PEWF_WEQ_PECI_GEN2, twue);

}

static enum wadeon_pcie_gen cypwess_get_maximum_wink_speed(stwuct wadeon_ps *wadeon_state)
{
	stwuct wv7xx_ps *state = wv770_get_ps(wadeon_state);

	if (state->high.fwags & ATOM_PPWIB_W600_FWAGS_PCIEGEN2)
		wetuwn 1;
	wetuwn 0;
}

void cypwess_notify_wink_speed_change_aftew_state_change(stwuct wadeon_device *wdev,
							 stwuct wadeon_ps *wadeon_new_state,
							 stwuct wadeon_ps *wadeon_cuwwent_state)
{
	enum wadeon_pcie_gen pcie_wink_speed_tawget =
		cypwess_get_maximum_wink_speed(wadeon_new_state);
	enum wadeon_pcie_gen pcie_wink_speed_cuwwent =
		cypwess_get_maximum_wink_speed(wadeon_cuwwent_state);
	u8 wequest;

	if (pcie_wink_speed_tawget < pcie_wink_speed_cuwwent) {
		if (pcie_wink_speed_tawget == WADEON_PCIE_GEN1)
			wequest = PCIE_PEWF_WEQ_PECI_GEN1;
		ewse if (pcie_wink_speed_tawget == WADEON_PCIE_GEN2)
			wequest = PCIE_PEWF_WEQ_PECI_GEN2;
		ewse
			wequest = PCIE_PEWF_WEQ_PECI_GEN3;

		cypwess_pcie_pewfowmance_wequest(wdev, wequest, fawse);
	}
}

void cypwess_notify_wink_speed_change_befowe_state_change(stwuct wadeon_device *wdev,
							  stwuct wadeon_ps *wadeon_new_state,
							  stwuct wadeon_ps *wadeon_cuwwent_state)
{
	enum wadeon_pcie_gen pcie_wink_speed_tawget =
		cypwess_get_maximum_wink_speed(wadeon_new_state);
	enum wadeon_pcie_gen pcie_wink_speed_cuwwent =
		cypwess_get_maximum_wink_speed(wadeon_cuwwent_state);
	u8 wequest;

	if (pcie_wink_speed_tawget > pcie_wink_speed_cuwwent) {
		if (pcie_wink_speed_tawget == WADEON_PCIE_GEN1)
			wequest = PCIE_PEWF_WEQ_PECI_GEN1;
		ewse if (pcie_wink_speed_tawget == WADEON_PCIE_GEN2)
			wequest = PCIE_PEWF_WEQ_PECI_GEN2;
		ewse
			wequest = PCIE_PEWF_WEQ_PECI_GEN3;

		cypwess_pcie_pewfowmance_wequest(wdev, wequest, fawse);
	}
}

static int cypwess_popuwate_vowtage_vawue(stwuct wadeon_device *wdev,
					  stwuct atom_vowtage_tabwe *tabwe,
					  u16 vawue, WV770_SMC_VOWTAGE_VAWUE *vowtage)
{
	unsigned int i;

	fow (i = 0; i < tabwe->count; i++) {
		if (vawue <= tabwe->entwies[i].vawue) {
			vowtage->index = (u8)i;
			vowtage->vawue = cpu_to_be16(tabwe->entwies[i].vawue);
			bweak;
		}
	}

	if (i == tabwe->count)
		wetuwn -EINVAW;

	wetuwn 0;
}

u8 cypwess_get_stwobe_mode_settings(stwuct wadeon_device *wdev, u32 mcwk)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u8 wesuwt = 0;
	boow stwobe_mode = fawse;

	if (pi->mem_gddw5) {
		if (mcwk <= pi->mcwk_stwobe_mode_thweshowd)
			stwobe_mode = twue;
		wesuwt = cypwess_get_mcwk_fwequency_watio(wdev, mcwk, stwobe_mode);

		if (stwobe_mode)
			wesuwt |= SMC_STWOBE_ENABWE;
	}

	wetuwn wesuwt;
}

u32 cypwess_map_cwkf_to_ibias(stwuct wadeon_device *wdev, u32 cwkf)
{
	u32 wef_cwk = wdev->cwock.mpww.wefewence_fweq;
	u32 vco = cwkf * wef_cwk;

	/* 100 Mhz wef cwk */
	if (wef_cwk == 10000) {
		if (vco > 500000)
			wetuwn 0xC6;
		if (vco > 400000)
			wetuwn 0x9D;
		if (vco > 330000)
			wetuwn 0x6C;
		if (vco > 250000)
			wetuwn 0x2B;
		if (vco >  160000)
			wetuwn 0x5B;
		if (vco > 120000)
			wetuwn 0x0A;
		wetuwn 0x4B;
	}

	/* 27 Mhz wef cwk */
	if (vco > 250000)
		wetuwn 0x8B;
	if (vco > 200000)
		wetuwn 0xCC;
	if (vco > 150000)
		wetuwn 0x9B;
	wetuwn 0x6B;
}

static int cypwess_popuwate_mcwk_vawue(stwuct wadeon_device *wdev,
				       u32 engine_cwock, u32 memowy_cwock,
				       WV7XX_SMC_MCWK_VAWUE *mcwk,
				       boow stwobe_mode, boow dww_state_on)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	u32 mpww_ad_func_cntw =
		pi->cwk_wegs.wv770.mpww_ad_func_cntw;
	u32 mpww_ad_func_cntw_2 =
		pi->cwk_wegs.wv770.mpww_ad_func_cntw_2;
	u32 mpww_dq_func_cntw =
		pi->cwk_wegs.wv770.mpww_dq_func_cntw;
	u32 mpww_dq_func_cntw_2 =
		pi->cwk_wegs.wv770.mpww_dq_func_cntw_2;
	u32 mcwk_pwwmgt_cntw =
		pi->cwk_wegs.wv770.mcwk_pwwmgt_cntw;
	u32 dww_cntw =
		pi->cwk_wegs.wv770.dww_cntw;
	u32 mpww_ss1 = pi->cwk_wegs.wv770.mpww_ss1;
	u32 mpww_ss2 = pi->cwk_wegs.wv770.mpww_ss2;
	stwuct atom_cwock_dividews dividews;
	u32 ibias;
	u32 dww_speed;
	int wet;
	u32 mc_seq_misc7;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_MEMOWY_PWW_PAWAM,
					     memowy_cwock, stwobe_mode, &dividews);
	if (wet)
		wetuwn wet;

	if (!stwobe_mode) {
		mc_seq_misc7 = WWEG32(MC_SEQ_MISC7);

		if(mc_seq_misc7 & 0x8000000)
			dividews.post_div = 1;
	}

	ibias = cypwess_map_cwkf_to_ibias(wdev, dividews.whowe_fb_div);

	mpww_ad_func_cntw &= ~(CWKW_MASK |
			       YCWK_POST_DIV_MASK |
			       CWKF_MASK |
			       CWKFWAC_MASK |
			       IBIAS_MASK);
	mpww_ad_func_cntw |= CWKW(dividews.wef_div);
	mpww_ad_func_cntw |= YCWK_POST_DIV(dividews.post_div);
	mpww_ad_func_cntw |= CWKF(dividews.whowe_fb_div);
	mpww_ad_func_cntw |= CWKFWAC(dividews.fwac_fb_div);
	mpww_ad_func_cntw |= IBIAS(ibias);

	if (dividews.vco_mode)
		mpww_ad_func_cntw_2 |= VCO_MODE;
	ewse
		mpww_ad_func_cntw_2 &= ~VCO_MODE;

	if (pi->mem_gddw5) {
		mpww_dq_func_cntw &= ~(CWKW_MASK |
				       YCWK_POST_DIV_MASK |
				       CWKF_MASK |
				       CWKFWAC_MASK |
				       IBIAS_MASK);
		mpww_dq_func_cntw |= CWKW(dividews.wef_div);
		mpww_dq_func_cntw |= YCWK_POST_DIV(dividews.post_div);
		mpww_dq_func_cntw |= CWKF(dividews.whowe_fb_div);
		mpww_dq_func_cntw |= CWKFWAC(dividews.fwac_fb_div);
		mpww_dq_func_cntw |= IBIAS(ibias);

		if (stwobe_mode)
			mpww_dq_func_cntw &= ~PDNB;
		ewse
			mpww_dq_func_cntw |= PDNB;

		if (dividews.vco_mode)
			mpww_dq_func_cntw_2 |= VCO_MODE;
		ewse
			mpww_dq_func_cntw_2 &= ~VCO_MODE;
	}

	if (pi->mcwk_ss) {
		stwuct wadeon_atom_ss ss;
		u32 vco_fweq = memowy_cwock * dividews.post_div;

		if (wadeon_atombios_get_asic_ss_info(wdev, &ss,
						     ASIC_INTEWNAW_MEMOWY_SS, vco_fweq)) {
			u32 wefewence_cwock = wdev->cwock.mpww.wefewence_fweq;
			u32 decoded_wef = wv740_get_decoded_wefewence_dividew(dividews.wef_div);
			u32 cwk_s, cwk_v;

			if (!decoded_wef)
				wetuwn -EINVAW;
			cwk_s = wefewence_cwock * 5 / (decoded_wef * ss.wate);
			cwk_v = ss.pewcentage *
				(0x4000 * dividews.whowe_fb_div + 0x800 * dividews.fwac_fb_div) / (cwk_s * 625);

			mpww_ss1 &= ~CWKV_MASK;
			mpww_ss1 |= CWKV(cwk_v);

			mpww_ss2 &= ~CWKS_MASK;
			mpww_ss2 |= CWKS(cwk_s);
		}
	}

	dww_speed = wv740_get_dww_speed(pi->mem_gddw5,
					memowy_cwock);

	mcwk_pwwmgt_cntw &= ~DWW_SPEED_MASK;
	mcwk_pwwmgt_cntw |= DWW_SPEED(dww_speed);
	if (dww_state_on)
		mcwk_pwwmgt_cntw |= (MWDCKA0_PDNB |
				     MWDCKA1_PDNB |
				     MWDCKB0_PDNB |
				     MWDCKB1_PDNB |
				     MWDCKC0_PDNB |
				     MWDCKC1_PDNB |
				     MWDCKD0_PDNB |
				     MWDCKD1_PDNB);
	ewse
		mcwk_pwwmgt_cntw &= ~(MWDCKA0_PDNB |
				      MWDCKA1_PDNB |
				      MWDCKB0_PDNB |
				      MWDCKB1_PDNB |
				      MWDCKC0_PDNB |
				      MWDCKC1_PDNB |
				      MWDCKD0_PDNB |
				      MWDCKD1_PDNB);

	mcwk->mcwk770.mcwk_vawue = cpu_to_be32(memowy_cwock);
	mcwk->mcwk770.vMPWW_AD_FUNC_CNTW = cpu_to_be32(mpww_ad_func_cntw);
	mcwk->mcwk770.vMPWW_AD_FUNC_CNTW_2 = cpu_to_be32(mpww_ad_func_cntw_2);
	mcwk->mcwk770.vMPWW_DQ_FUNC_CNTW = cpu_to_be32(mpww_dq_func_cntw);
	mcwk->mcwk770.vMPWW_DQ_FUNC_CNTW_2 = cpu_to_be32(mpww_dq_func_cntw_2);
	mcwk->mcwk770.vMCWK_PWWMGT_CNTW = cpu_to_be32(mcwk_pwwmgt_cntw);
	mcwk->mcwk770.vDWW_CNTW = cpu_to_be32(dww_cntw);
	mcwk->mcwk770.vMPWW_SS = cpu_to_be32(mpww_ss1);
	mcwk->mcwk770.vMPWW_SS2 = cpu_to_be32(mpww_ss2);

	wetuwn 0;
}

u8 cypwess_get_mcwk_fwequency_watio(stwuct wadeon_device *wdev,
				    u32 memowy_cwock, boow stwobe_mode)
{
	u8 mc_pawa_index;

	if (wdev->famiwy >= CHIP_BAWTS) {
		if (stwobe_mode) {
			if (memowy_cwock < 10000)
				mc_pawa_index = 0x00;
			ewse if (memowy_cwock > 47500)
				mc_pawa_index = 0x0f;
			ewse
				mc_pawa_index = (u8)((memowy_cwock - 10000) / 2500);
		} ewse {
			if (memowy_cwock < 65000)
				mc_pawa_index = 0x00;
			ewse if (memowy_cwock > 135000)
				mc_pawa_index = 0x0f;
			ewse
				mc_pawa_index = (u8)((memowy_cwock - 60000) / 5000);
		}
	} ewse {
		if (stwobe_mode) {
			if (memowy_cwock < 10000)
				mc_pawa_index = 0x00;
			ewse if (memowy_cwock > 47500)
				mc_pawa_index = 0x0f;
			ewse
				mc_pawa_index = (u8)((memowy_cwock - 10000) / 2500);
		} ewse {
			if (memowy_cwock < 40000)
				mc_pawa_index = 0x00;
			ewse if (memowy_cwock > 115000)
				mc_pawa_index = 0x0f;
			ewse
				mc_pawa_index = (u8)((memowy_cwock - 40000) / 5000);
		}
	}
	wetuwn mc_pawa_index;
}

static int cypwess_popuwate_mvdd_vawue(stwuct wadeon_device *wdev,
				       u32 mcwk,
				       WV770_SMC_VOWTAGE_VAWUE *vowtage)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);

	if (!pi->mvdd_contwow) {
		vowtage->index = eg_pi->mvdd_high_index;
		vowtage->vawue = cpu_to_be16(MVDD_HIGH_VAWUE);
		wetuwn 0;
	}

	if (mcwk <= pi->mvdd_spwit_fwequency) {
		vowtage->index = eg_pi->mvdd_wow_index;
		vowtage->vawue = cpu_to_be16(MVDD_WOW_VAWUE);
	} ewse {
		vowtage->index = eg_pi->mvdd_high_index;
		vowtage->vawue = cpu_to_be16(MVDD_HIGH_VAWUE);
	}

	wetuwn 0;
}

int cypwess_convewt_powew_wevew_to_smc(stwuct wadeon_device *wdev,
				       stwuct wv7xx_pw *pw,
				       WV770_SMC_HW_PEWFOWMANCE_WEVEW *wevew,
				       u8 watewmawk_wevew)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	int wet;
	boow dww_state_on;

	wevew->gen2PCIE = pi->pcie_gen2 ?
		((pw->fwags & ATOM_PPWIB_W600_FWAGS_PCIEGEN2) ? 1 : 0) : 0;
	wevew->gen2XSP  = (pw->fwags & ATOM_PPWIB_W600_FWAGS_PCIEGEN2) ? 1 : 0;
	wevew->backbias = (pw->fwags & ATOM_PPWIB_W600_FWAGS_BACKBIASENABWE) ? 1 : 0;
	wevew->dispwayWatewmawk = watewmawk_wevew;

	wet = wv740_popuwate_scwk_vawue(wdev, pw->scwk, &wevew->scwk);
	if (wet)
		wetuwn wet;

	wevew->mcFwags =  0;
	if (pi->mcwk_stuttew_mode_thweshowd &&
	    (pw->mcwk <= pi->mcwk_stuttew_mode_thweshowd) &&
	    !eg_pi->uvd_enabwed) {
		wevew->mcFwags |= SMC_MC_STUTTEW_EN;
		if (eg_pi->scwk_deep_sweep)
			wevew->stateFwags |= PPSMC_STATEFWAG_AUTO_PUWSE_SKIP;
		ewse
			wevew->stateFwags &= ~PPSMC_STATEFWAG_AUTO_PUWSE_SKIP;
	}

	if (pi->mem_gddw5) {
		if (pw->mcwk > pi->mcwk_edc_enabwe_thweshowd)
			wevew->mcFwags |= SMC_MC_EDC_WD_FWAG;

		if (pw->mcwk > eg_pi->mcwk_edc_ww_enabwe_thweshowd)
			wevew->mcFwags |= SMC_MC_EDC_WW_FWAG;

		wevew->stwobeMode = cypwess_get_stwobe_mode_settings(wdev, pw->mcwk);

		if (wevew->stwobeMode & SMC_STWOBE_ENABWE) {
			if (cypwess_get_mcwk_fwequency_watio(wdev, pw->mcwk, twue) >=
			    ((WWEG32(MC_SEQ_MISC7) >> 16) & 0xf))
				dww_state_on = ((WWEG32(MC_SEQ_MISC5) >> 1) & 0x1) ? twue : fawse;
			ewse
				dww_state_on = ((WWEG32(MC_SEQ_MISC6) >> 1) & 0x1) ? twue : fawse;
		} ewse
			dww_state_on = eg_pi->dww_defauwt_on;

		wet = cypwess_popuwate_mcwk_vawue(wdev,
						  pw->scwk,
						  pw->mcwk,
						  &wevew->mcwk,
						  (wevew->stwobeMode & SMC_STWOBE_ENABWE) != 0,
						  dww_state_on);
	} ewse {
		wet = cypwess_popuwate_mcwk_vawue(wdev,
						  pw->scwk,
						  pw->mcwk,
						  &wevew->mcwk,
						  twue,
						  twue);
	}
	if (wet)
		wetuwn wet;

	wet = cypwess_popuwate_vowtage_vawue(wdev,
					     &eg_pi->vddc_vowtage_tabwe,
					     pw->vddc,
					     &wevew->vddc);
	if (wet)
		wetuwn wet;

	if (eg_pi->vddci_contwow) {
		wet = cypwess_popuwate_vowtage_vawue(wdev,
						     &eg_pi->vddci_vowtage_tabwe,
						     pw->vddci,
						     &wevew->vddci);
		if (wet)
			wetuwn wet;
	}

	wet = cypwess_popuwate_mvdd_vawue(wdev, pw->mcwk, &wevew->mvdd);

	wetuwn wet;
}

static int cypwess_convewt_powew_state_to_smc(stwuct wadeon_device *wdev,
					      stwuct wadeon_ps *wadeon_state,
					      WV770_SMC_SWSTATE *smc_state)
{
	stwuct wv7xx_ps *state = wv770_get_ps(wadeon_state);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	int wet;

	if (!(wadeon_state->caps & ATOM_PPWIB_DISAWWOW_ON_DC))
		smc_state->fwags |= PPSMC_SWSTATE_FWAG_DC;

	wet = cypwess_convewt_powew_wevew_to_smc(wdev,
						 &state->wow,
						 &smc_state->wevews[0],
						 PPSMC_DISPWAY_WATEWMAWK_WOW);
	if (wet)
		wetuwn wet;

	wet = cypwess_convewt_powew_wevew_to_smc(wdev,
						 &state->medium,
						 &smc_state->wevews[1],
						 PPSMC_DISPWAY_WATEWMAWK_WOW);
	if (wet)
		wetuwn wet;

	wet = cypwess_convewt_powew_wevew_to_smc(wdev,
						 &state->high,
						 &smc_state->wevews[2],
						 PPSMC_DISPWAY_WATEWMAWK_HIGH);
	if (wet)
		wetuwn wet;

	smc_state->wevews[0].awbVawue = MC_CG_AWB_FWEQ_F1;
	smc_state->wevews[1].awbVawue = MC_CG_AWB_FWEQ_F2;
	smc_state->wevews[2].awbVawue = MC_CG_AWB_FWEQ_F3;

	if (eg_pi->dynamic_ac_timing) {
		smc_state->wevews[0].ACIndex = 2;
		smc_state->wevews[1].ACIndex = 3;
		smc_state->wevews[2].ACIndex = 4;
	} ewse {
		smc_state->wevews[0].ACIndex = 0;
		smc_state->wevews[1].ACIndex = 0;
		smc_state->wevews[2].ACIndex = 0;
	}

	wv770_popuwate_smc_sp(wdev, wadeon_state, smc_state);

	wetuwn wv770_popuwate_smc_t(wdev, wadeon_state, smc_state);
}

static void cypwess_convewt_mc_wegistews(stwuct evewgween_mc_weg_entwy *entwy,
					 SMC_Evewgween_MCWegistewSet *data,
					 u32 num_entwies, u32 vawid_fwag)
{
	u32 i, j;

	fow (i = 0, j = 0; j < num_entwies; j++) {
		if (vawid_fwag & (1 << j)) {
			data->vawue[i] = cpu_to_be32(entwy->mc_data[j]);
			i++;
		}
	}
}

static void cypwess_convewt_mc_weg_tabwe_entwy_to_smc(stwuct wadeon_device *wdev,
						      stwuct wv7xx_pw *pw,
						      SMC_Evewgween_MCWegistewSet *mc_weg_tabwe_data)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	u32 i = 0;

	fow (i = 0; i < eg_pi->mc_weg_tabwe.num_entwies; i++) {
		if (pw->mcwk <=
		    eg_pi->mc_weg_tabwe.mc_weg_tabwe_entwy[i].mcwk_max)
			bweak;
	}

	if ((i == eg_pi->mc_weg_tabwe.num_entwies) && (i > 0))
		--i;

	cypwess_convewt_mc_wegistews(&eg_pi->mc_weg_tabwe.mc_weg_tabwe_entwy[i],
				     mc_weg_tabwe_data,
				     eg_pi->mc_weg_tabwe.wast,
				     eg_pi->mc_weg_tabwe.vawid_fwag);
}

static void cypwess_convewt_mc_weg_tabwe_to_smc(stwuct wadeon_device *wdev,
						stwuct wadeon_ps *wadeon_state,
						SMC_Evewgween_MCWegistews *mc_weg_tabwe)
{
	stwuct wv7xx_ps *state = wv770_get_ps(wadeon_state);

	cypwess_convewt_mc_weg_tabwe_entwy_to_smc(wdev,
						  &state->wow,
						  &mc_weg_tabwe->data[2]);
	cypwess_convewt_mc_weg_tabwe_entwy_to_smc(wdev,
						  &state->medium,
						  &mc_weg_tabwe->data[3]);
	cypwess_convewt_mc_weg_tabwe_entwy_to_smc(wdev,
						  &state->high,
						  &mc_weg_tabwe->data[4]);
}

int cypwess_upwoad_sw_state(stwuct wadeon_device *wdev,
			    stwuct wadeon_ps *wadeon_new_state)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u16 addwess = pi->state_tabwe_stawt +
		offsetof(WV770_SMC_STATETABWE, dwivewState);
	WV770_SMC_SWSTATE state = { 0 };
	int wet;

	wet = cypwess_convewt_powew_state_to_smc(wdev, wadeon_new_state, &state);
	if (wet)
		wetuwn wet;

	wetuwn wv770_copy_bytes_to_smc(wdev, addwess, (u8 *)&state,
				    sizeof(WV770_SMC_SWSTATE),
				    pi->swam_end);
}

int cypwess_upwoad_mc_weg_tabwe(stwuct wadeon_device *wdev,
				stwuct wadeon_ps *wadeon_new_state)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	SMC_Evewgween_MCWegistews mc_weg_tabwe = { 0 };
	u16 addwess;

	cypwess_convewt_mc_weg_tabwe_to_smc(wdev, wadeon_new_state, &mc_weg_tabwe);

	addwess = eg_pi->mc_weg_tabwe_stawt +
		(u16)offsetof(SMC_Evewgween_MCWegistews, data[2]);

	wetuwn wv770_copy_bytes_to_smc(wdev, addwess,
				       (u8 *)&mc_weg_tabwe.data[2],
				       sizeof(SMC_Evewgween_MCWegistewSet) * 3,
				       pi->swam_end);
}

u32 cypwess_cawcuwate_buwst_time(stwuct wadeon_device *wdev,
				 u32 engine_cwock, u32 memowy_cwock)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 muwtipwiew = pi->mem_gddw5 ? 1 : 2;
	u32 wesuwt = (4 * muwtipwiew * engine_cwock) / (memowy_cwock / 2);
	u32 buwst_time;

	if (wesuwt <= 4)
		buwst_time = 0;
	ewse if (wesuwt < 8)
		buwst_time = wesuwt - 4;
	ewse {
		buwst_time = wesuwt / 2 ;
		if (buwst_time > 18)
			buwst_time = 18;
	}

	wetuwn buwst_time;
}

void cypwess_pwogwam_memowy_timing_pawametews(stwuct wadeon_device *wdev,
					      stwuct wadeon_ps *wadeon_new_state)
{
	stwuct wv7xx_ps *new_state = wv770_get_ps(wadeon_new_state);
	u32 mc_awb_buwst_time = WWEG32(MC_AWB_BUWST_TIME);

	mc_awb_buwst_time &= ~(STATE1_MASK | STATE2_MASK | STATE3_MASK);

	mc_awb_buwst_time |= STATE1(cypwess_cawcuwate_buwst_time(wdev,
								 new_state->wow.scwk,
								 new_state->wow.mcwk));
	mc_awb_buwst_time |= STATE2(cypwess_cawcuwate_buwst_time(wdev,
								 new_state->medium.scwk,
								 new_state->medium.mcwk));
	mc_awb_buwst_time |= STATE3(cypwess_cawcuwate_buwst_time(wdev,
								 new_state->high.scwk,
								 new_state->high.mcwk));

	wv730_pwogwam_memowy_timing_pawametews(wdev, wadeon_new_state);

	WWEG32(MC_AWB_BUWST_TIME, mc_awb_buwst_time);
}

static void cypwess_popuwate_mc_weg_addwesses(stwuct wadeon_device *wdev,
					      SMC_Evewgween_MCWegistews *mc_weg_tabwe)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	u32 i, j;

	fow (i = 0, j = 0; j < eg_pi->mc_weg_tabwe.wast; j++) {
		if (eg_pi->mc_weg_tabwe.vawid_fwag & (1 << j)) {
			mc_weg_tabwe->addwess[i].s0 =
				cpu_to_be16(eg_pi->mc_weg_tabwe.mc_weg_addwess[j].s0);
			mc_weg_tabwe->addwess[i].s1 =
				cpu_to_be16(eg_pi->mc_weg_tabwe.mc_weg_addwess[j].s1);
			i++;
		}
	}

	mc_weg_tabwe->wast = (u8)i;
}

static void cypwess_set_mc_weg_addwess_tabwe(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	u32 i = 0;

	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s0 = MC_SEQ_WAS_TIMING_WP >> 2;
	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s1 = MC_SEQ_WAS_TIMING >> 2;
	i++;

	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s0 = MC_SEQ_CAS_TIMING_WP >> 2;
	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s1 = MC_SEQ_CAS_TIMING >> 2;
	i++;

	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s0 = MC_SEQ_MISC_TIMING_WP >> 2;
	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s1 = MC_SEQ_MISC_TIMING >> 2;
	i++;

	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s0 = MC_SEQ_MISC_TIMING2_WP >> 2;
	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s1 = MC_SEQ_MISC_TIMING2 >> 2;
	i++;

	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s0 = MC_SEQ_WD_CTW_D0_WP >> 2;
	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s1 = MC_SEQ_WD_CTW_D0 >> 2;
	i++;

	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s0 = MC_SEQ_WD_CTW_D1_WP >> 2;
	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s1 = MC_SEQ_WD_CTW_D1 >> 2;
	i++;

	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s0 = MC_SEQ_WW_CTW_D0_WP >> 2;
	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s1 = MC_SEQ_WW_CTW_D0 >> 2;
	i++;

	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s0 = MC_SEQ_WW_CTW_D1_WP >> 2;
	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s1 = MC_SEQ_WW_CTW_D1 >> 2;
	i++;

	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s0 = MC_SEQ_PMG_CMD_EMWS_WP >> 2;
	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s1 = MC_PMG_CMD_EMWS >> 2;
	i++;

	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s0 = MC_SEQ_PMG_CMD_MWS_WP >> 2;
	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s1 = MC_PMG_CMD_MWS >> 2;
	i++;

	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s0 = MC_SEQ_PMG_CMD_MWS1_WP >> 2;
	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s1 = MC_PMG_CMD_MWS1 >> 2;
	i++;

	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s0 = MC_SEQ_MISC1 >> 2;
	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s1 = MC_SEQ_MISC1 >> 2;
	i++;

	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s0 = MC_SEQ_WESEWVE_M >> 2;
	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s1 = MC_SEQ_WESEWVE_M >> 2;
	i++;

	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s0 = MC_SEQ_MISC3 >> 2;
	eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s1 = MC_SEQ_MISC3 >> 2;
	i++;

	eg_pi->mc_weg_tabwe.wast = (u8)i;
}

static void cypwess_wetwieve_ac_timing_fow_one_entwy(stwuct wadeon_device *wdev,
						     stwuct evewgween_mc_weg_entwy *entwy)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	u32 i;

	fow (i = 0; i < eg_pi->mc_weg_tabwe.wast; i++)
		entwy->mc_data[i] =
			WWEG32(eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s1 << 2);

}

static void cypwess_wetwieve_ac_timing_fow_aww_wanges(stwuct wadeon_device *wdev,
						      stwuct atom_memowy_cwock_wange_tabwe *wange_tabwe)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	u32 i, j;

	fow (i = 0; i < wange_tabwe->num_entwies; i++) {
		eg_pi->mc_weg_tabwe.mc_weg_tabwe_entwy[i].mcwk_max =
			wange_tabwe->mcwk[i];
		wadeon_atom_set_ac_timing(wdev, wange_tabwe->mcwk[i]);
		cypwess_wetwieve_ac_timing_fow_one_entwy(wdev,
							 &eg_pi->mc_weg_tabwe.mc_weg_tabwe_entwy[i]);
	}

	eg_pi->mc_weg_tabwe.num_entwies = wange_tabwe->num_entwies;
	eg_pi->mc_weg_tabwe.vawid_fwag = 0;

	fow (i = 0; i < eg_pi->mc_weg_tabwe.wast; i++) {
		fow (j = 1; j < wange_tabwe->num_entwies; j++) {
			if (eg_pi->mc_weg_tabwe.mc_weg_tabwe_entwy[j-1].mc_data[i] !=
			    eg_pi->mc_weg_tabwe.mc_weg_tabwe_entwy[j].mc_data[i]) {
				eg_pi->mc_weg_tabwe.vawid_fwag |= (1 << i);
				bweak;
			}
		}
	}
}

static int cypwess_initiawize_mc_weg_tabwe(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u8 moduwe_index = wv770_get_memowy_moduwe_index(wdev);
	stwuct atom_memowy_cwock_wange_tabwe wange_tabwe = { 0 };
	int wet;

	wet = wadeon_atom_get_mcwk_wange_tabwe(wdev,
					       pi->mem_gddw5,
					       moduwe_index, &wange_tabwe);
	if (wet)
		wetuwn wet;

	cypwess_wetwieve_ac_timing_fow_aww_wanges(wdev, &wange_tabwe);

	wetuwn 0;
}

static void cypwess_wait_fow_mc_sequencew(stwuct wadeon_device *wdev, u8 vawue)
{
	u32 i, j;
	u32 channews = 2;

	if ((wdev->famiwy == CHIP_CYPWESS) ||
	    (wdev->famiwy == CHIP_HEMWOCK))
		channews = 4;
	ewse if (wdev->famiwy == CHIP_CEDAW)
		channews = 1;

	fow (i = 0; i < channews; i++) {
		if ((wdev->famiwy == CHIP_CYPWESS) ||
		    (wdev->famiwy == CHIP_HEMWOCK)) {
			WWEG32_P(MC_CONFIG_MCD, MC_WD_ENABWE_MCD(i), ~MC_WD_ENABWE_MCD_MASK);
			WWEG32_P(MC_CG_CONFIG_MCD, MC_WD_ENABWE_MCD(i), ~MC_WD_ENABWE_MCD_MASK);
		} ewse {
			WWEG32_P(MC_CONFIG, MC_WD_ENABWE(i), ~MC_WD_ENABWE_MASK);
			WWEG32_P(MC_CG_CONFIG, MC_WD_ENABWE(i), ~MC_WD_ENABWE_MASK);
		}
		fow (j = 0; j < wdev->usec_timeout; j++) {
			if (((WWEG32(MC_SEQ_CG) & CG_SEQ_WESP_MASK) >> CG_SEQ_WESP_SHIFT) == vawue)
				bweak;
			udeway(1);
		}
	}
}

static void cypwess_fowce_mc_use_s1(stwuct wadeon_device *wdev,
				    stwuct wadeon_ps *wadeon_boot_state)
{
	stwuct wv7xx_ps *boot_state = wv770_get_ps(wadeon_boot_state);
	u32 stwobe_mode;
	u32 mc_seq_cg;
	int i;

	if (WWEG32(MC_SEQ_STATUS_M) & PMG_PWWSTATE)
		wetuwn;

	wadeon_atom_set_ac_timing(wdev, boot_state->wow.mcwk);
	wadeon_mc_wait_fow_idwe(wdev);

	if ((wdev->famiwy == CHIP_CYPWESS) ||
	    (wdev->famiwy == CHIP_HEMWOCK)) {
		WWEG32(MC_CONFIG_MCD, 0xf);
		WWEG32(MC_CG_CONFIG_MCD, 0xf);
	} ewse {
		WWEG32(MC_CONFIG, 0xf);
		WWEG32(MC_CG_CONFIG, 0xf);
	}

	fow (i = 0; i < wdev->num_cwtc; i++)
		wadeon_wait_fow_vbwank(wdev, i);

	WWEG32(MC_SEQ_CG, MC_CG_SEQ_YCWK_SUSPEND);
	cypwess_wait_fow_mc_sequencew(wdev, MC_CG_SEQ_YCWK_SUSPEND);

	stwobe_mode = cypwess_get_stwobe_mode_settings(wdev,
						       boot_state->wow.mcwk);

	mc_seq_cg = CG_SEQ_WEQ(MC_CG_SEQ_DWAMCONF_S1);
	mc_seq_cg |= SEQ_CG_WESP(stwobe_mode);
	WWEG32(MC_SEQ_CG, mc_seq_cg);

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (WWEG32(MC_SEQ_STATUS_M) & PMG_PWWSTATE)
			bweak;
		udeway(1);
	}

	mc_seq_cg &= ~CG_SEQ_WEQ_MASK;
	mc_seq_cg |= CG_SEQ_WEQ(MC_CG_SEQ_YCWK_WESUME);
	WWEG32(MC_SEQ_CG, mc_seq_cg);

	cypwess_wait_fow_mc_sequencew(wdev, MC_CG_SEQ_YCWK_WESUME);
}

static void cypwess_copy_ac_timing_fwom_s1_to_s0(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	u32 vawue;
	u32 i;

	fow (i = 0; i < eg_pi->mc_weg_tabwe.wast; i++) {
		vawue = WWEG32(eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s1 << 2);
		WWEG32(eg_pi->mc_weg_tabwe.mc_weg_addwess[i].s0 << 2, vawue);
	}
}

static void cypwess_fowce_mc_use_s0(stwuct wadeon_device *wdev,
				    stwuct wadeon_ps *wadeon_boot_state)
{
	stwuct wv7xx_ps *boot_state = wv770_get_ps(wadeon_boot_state);
	u32 stwobe_mode;
	u32 mc_seq_cg;
	int i;

	cypwess_copy_ac_timing_fwom_s1_to_s0(wdev);
	wadeon_mc_wait_fow_idwe(wdev);

	if ((wdev->famiwy == CHIP_CYPWESS) ||
	    (wdev->famiwy == CHIP_HEMWOCK)) {
		WWEG32(MC_CONFIG_MCD, 0xf);
		WWEG32(MC_CG_CONFIG_MCD, 0xf);
	} ewse {
		WWEG32(MC_CONFIG, 0xf);
		WWEG32(MC_CG_CONFIG, 0xf);
	}

	fow (i = 0; i < wdev->num_cwtc; i++)
		wadeon_wait_fow_vbwank(wdev, i);

	WWEG32(MC_SEQ_CG, MC_CG_SEQ_YCWK_SUSPEND);
	cypwess_wait_fow_mc_sequencew(wdev, MC_CG_SEQ_YCWK_SUSPEND);

	stwobe_mode = cypwess_get_stwobe_mode_settings(wdev,
						       boot_state->wow.mcwk);

	mc_seq_cg = CG_SEQ_WEQ(MC_CG_SEQ_DWAMCONF_S0);
	mc_seq_cg |= SEQ_CG_WESP(stwobe_mode);
	WWEG32(MC_SEQ_CG, mc_seq_cg);

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (!(WWEG32(MC_SEQ_STATUS_M) & PMG_PWWSTATE))
			bweak;
		udeway(1);
	}

	mc_seq_cg &= ~CG_SEQ_WEQ_MASK;
	mc_seq_cg |= CG_SEQ_WEQ(MC_CG_SEQ_YCWK_WESUME);
	WWEG32(MC_SEQ_CG, mc_seq_cg);

	cypwess_wait_fow_mc_sequencew(wdev, MC_CG_SEQ_YCWK_WESUME);
}

static int cypwess_popuwate_initiaw_mvdd_vawue(stwuct wadeon_device *wdev,
					       WV770_SMC_VOWTAGE_VAWUE *vowtage)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);

	vowtage->index = eg_pi->mvdd_high_index;
	vowtage->vawue = cpu_to_be16(MVDD_HIGH_VAWUE);

	wetuwn 0;
}

int cypwess_popuwate_smc_initiaw_state(stwuct wadeon_device *wdev,
				       stwuct wadeon_ps *wadeon_initiaw_state,
				       WV770_SMC_STATETABWE *tabwe)
{
	stwuct wv7xx_ps *initiaw_state = wv770_get_ps(wadeon_initiaw_state);
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	u32 a_t;

	tabwe->initiawState.wevews[0].mcwk.mcwk770.vMPWW_AD_FUNC_CNTW =
		cpu_to_be32(pi->cwk_wegs.wv770.mpww_ad_func_cntw);
	tabwe->initiawState.wevews[0].mcwk.mcwk770.vMPWW_AD_FUNC_CNTW_2 =
		cpu_to_be32(pi->cwk_wegs.wv770.mpww_ad_func_cntw_2);
	tabwe->initiawState.wevews[0].mcwk.mcwk770.vMPWW_DQ_FUNC_CNTW =
		cpu_to_be32(pi->cwk_wegs.wv770.mpww_dq_func_cntw);
	tabwe->initiawState.wevews[0].mcwk.mcwk770.vMPWW_DQ_FUNC_CNTW_2 =
		cpu_to_be32(pi->cwk_wegs.wv770.mpww_dq_func_cntw_2);
	tabwe->initiawState.wevews[0].mcwk.mcwk770.vMCWK_PWWMGT_CNTW =
		cpu_to_be32(pi->cwk_wegs.wv770.mcwk_pwwmgt_cntw);
	tabwe->initiawState.wevews[0].mcwk.mcwk770.vDWW_CNTW =
		cpu_to_be32(pi->cwk_wegs.wv770.dww_cntw);

	tabwe->initiawState.wevews[0].mcwk.mcwk770.vMPWW_SS =
		cpu_to_be32(pi->cwk_wegs.wv770.mpww_ss1);
	tabwe->initiawState.wevews[0].mcwk.mcwk770.vMPWW_SS2 =
		cpu_to_be32(pi->cwk_wegs.wv770.mpww_ss2);

	tabwe->initiawState.wevews[0].mcwk.mcwk770.mcwk_vawue =
		cpu_to_be32(initiaw_state->wow.mcwk);

	tabwe->initiawState.wevews[0].scwk.vCG_SPWW_FUNC_CNTW =
		cpu_to_be32(pi->cwk_wegs.wv770.cg_spww_func_cntw);
	tabwe->initiawState.wevews[0].scwk.vCG_SPWW_FUNC_CNTW_2 =
		cpu_to_be32(pi->cwk_wegs.wv770.cg_spww_func_cntw_2);
	tabwe->initiawState.wevews[0].scwk.vCG_SPWW_FUNC_CNTW_3 =
		cpu_to_be32(pi->cwk_wegs.wv770.cg_spww_func_cntw_3);
	tabwe->initiawState.wevews[0].scwk.vCG_SPWW_SPWEAD_SPECTWUM =
		cpu_to_be32(pi->cwk_wegs.wv770.cg_spww_spwead_spectwum);
	tabwe->initiawState.wevews[0].scwk.vCG_SPWW_SPWEAD_SPECTWUM_2 =
		cpu_to_be32(pi->cwk_wegs.wv770.cg_spww_spwead_spectwum_2);

	tabwe->initiawState.wevews[0].scwk.scwk_vawue =
		cpu_to_be32(initiaw_state->wow.scwk);

	tabwe->initiawState.wevews[0].awbVawue = MC_CG_AWB_FWEQ_F0;

	tabwe->initiawState.wevews[0].ACIndex = 0;

	cypwess_popuwate_vowtage_vawue(wdev,
				       &eg_pi->vddc_vowtage_tabwe,
				       initiaw_state->wow.vddc,
				       &tabwe->initiawState.wevews[0].vddc);

	if (eg_pi->vddci_contwow)
		cypwess_popuwate_vowtage_vawue(wdev,
					       &eg_pi->vddci_vowtage_tabwe,
					       initiaw_state->wow.vddci,
					       &tabwe->initiawState.wevews[0].vddci);

	cypwess_popuwate_initiaw_mvdd_vawue(wdev,
					    &tabwe->initiawState.wevews[0].mvdd);

	a_t = CG_W(0xffff) | CG_W(0);
	tabwe->initiawState.wevews[0].aT = cpu_to_be32(a_t);

	tabwe->initiawState.wevews[0].bSP = cpu_to_be32(pi->dsp);


	if (pi->boot_in_gen2)
		tabwe->initiawState.wevews[0].gen2PCIE = 1;
	ewse
		tabwe->initiawState.wevews[0].gen2PCIE = 0;
	if (initiaw_state->wow.fwags & ATOM_PPWIB_W600_FWAGS_PCIEGEN2)
		tabwe->initiawState.wevews[0].gen2XSP = 1;
	ewse
		tabwe->initiawState.wevews[0].gen2XSP = 0;

	if (pi->mem_gddw5) {
		tabwe->initiawState.wevews[0].stwobeMode =
			cypwess_get_stwobe_mode_settings(wdev,
							 initiaw_state->wow.mcwk);

		if (initiaw_state->wow.mcwk > pi->mcwk_edc_enabwe_thweshowd)
			tabwe->initiawState.wevews[0].mcFwags = SMC_MC_EDC_WD_FWAG | SMC_MC_EDC_WW_FWAG;
		ewse
			tabwe->initiawState.wevews[0].mcFwags =  0;
	}

	tabwe->initiawState.wevews[1] = tabwe->initiawState.wevews[0];
	tabwe->initiawState.wevews[2] = tabwe->initiawState.wevews[0];

	tabwe->initiawState.fwags |= PPSMC_SWSTATE_FWAG_DC;

	wetuwn 0;
}

int cypwess_popuwate_smc_acpi_state(stwuct wadeon_device *wdev,
				    WV770_SMC_STATETABWE *tabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	u32 mpww_ad_func_cntw =
		pi->cwk_wegs.wv770.mpww_ad_func_cntw;
	u32 mpww_ad_func_cntw_2 =
		pi->cwk_wegs.wv770.mpww_ad_func_cntw_2;
	u32 mpww_dq_func_cntw =
		pi->cwk_wegs.wv770.mpww_dq_func_cntw;
	u32 mpww_dq_func_cntw_2 =
		pi->cwk_wegs.wv770.mpww_dq_func_cntw_2;
	u32 spww_func_cntw =
		pi->cwk_wegs.wv770.cg_spww_func_cntw;
	u32 spww_func_cntw_2 =
		pi->cwk_wegs.wv770.cg_spww_func_cntw_2;
	u32 spww_func_cntw_3 =
		pi->cwk_wegs.wv770.cg_spww_func_cntw_3;
	u32 mcwk_pwwmgt_cntw =
		pi->cwk_wegs.wv770.mcwk_pwwmgt_cntw;
	u32 dww_cntw =
		pi->cwk_wegs.wv770.dww_cntw;

	tabwe->ACPIState = tabwe->initiawState;

	tabwe->ACPIState.fwags &= ~PPSMC_SWSTATE_FWAG_DC;

	if (pi->acpi_vddc) {
		cypwess_popuwate_vowtage_vawue(wdev,
					       &eg_pi->vddc_vowtage_tabwe,
					       pi->acpi_vddc,
					       &tabwe->ACPIState.wevews[0].vddc);
		if (pi->pcie_gen2) {
			if (pi->acpi_pcie_gen2)
				tabwe->ACPIState.wevews[0].gen2PCIE = 1;
			ewse
				tabwe->ACPIState.wevews[0].gen2PCIE = 0;
		} ewse
			tabwe->ACPIState.wevews[0].gen2PCIE = 0;
		if (pi->acpi_pcie_gen2)
			tabwe->ACPIState.wevews[0].gen2XSP = 1;
		ewse
			tabwe->ACPIState.wevews[0].gen2XSP = 0;
	} ewse {
		cypwess_popuwate_vowtage_vawue(wdev,
					       &eg_pi->vddc_vowtage_tabwe,
					       pi->min_vddc_in_tabwe,
					       &tabwe->ACPIState.wevews[0].vddc);
		tabwe->ACPIState.wevews[0].gen2PCIE = 0;
	}

	if (eg_pi->acpi_vddci) {
		if (eg_pi->vddci_contwow) {
			cypwess_popuwate_vowtage_vawue(wdev,
						       &eg_pi->vddci_vowtage_tabwe,
						       eg_pi->acpi_vddci,
						       &tabwe->ACPIState.wevews[0].vddci);
		}
	}

	mpww_ad_func_cntw &= ~PDNB;

	mpww_ad_func_cntw_2 |= BIAS_GEN_PDNB | WESET_EN;

	if (pi->mem_gddw5)
		mpww_dq_func_cntw &= ~PDNB;
	mpww_dq_func_cntw_2 |= BIAS_GEN_PDNB | WESET_EN | BYPASS;

	mcwk_pwwmgt_cntw |= (MWDCKA0_WESET |
			     MWDCKA1_WESET |
			     MWDCKB0_WESET |
			     MWDCKB1_WESET |
			     MWDCKC0_WESET |
			     MWDCKC1_WESET |
			     MWDCKD0_WESET |
			     MWDCKD1_WESET);

	mcwk_pwwmgt_cntw &= ~(MWDCKA0_PDNB |
			      MWDCKA1_PDNB |
			      MWDCKB0_PDNB |
			      MWDCKB1_PDNB |
			      MWDCKC0_PDNB |
			      MWDCKC1_PDNB |
			      MWDCKD0_PDNB |
			      MWDCKD1_PDNB);

	dww_cntw |= (MWDCKA0_BYPASS |
		     MWDCKA1_BYPASS |
		     MWDCKB0_BYPASS |
		     MWDCKB1_BYPASS |
		     MWDCKC0_BYPASS |
		     MWDCKC1_BYPASS |
		     MWDCKD0_BYPASS |
		     MWDCKD1_BYPASS);

	/* evewgween onwy */
	if (wdev->famiwy <= CHIP_HEMWOCK)
		spww_func_cntw |= SPWW_WESET | SPWW_SWEEP | SPWW_BYPASS_EN;

	spww_func_cntw_2 &= ~SCWK_MUX_SEW_MASK;
	spww_func_cntw_2 |= SCWK_MUX_SEW(4);

	tabwe->ACPIState.wevews[0].mcwk.mcwk770.vMPWW_AD_FUNC_CNTW =
		cpu_to_be32(mpww_ad_func_cntw);
	tabwe->ACPIState.wevews[0].mcwk.mcwk770.vMPWW_AD_FUNC_CNTW_2 =
		cpu_to_be32(mpww_ad_func_cntw_2);
	tabwe->ACPIState.wevews[0].mcwk.mcwk770.vMPWW_DQ_FUNC_CNTW =
		cpu_to_be32(mpww_dq_func_cntw);
	tabwe->ACPIState.wevews[0].mcwk.mcwk770.vMPWW_DQ_FUNC_CNTW_2 =
		cpu_to_be32(mpww_dq_func_cntw_2);
	tabwe->ACPIState.wevews[0].mcwk.mcwk770.vMCWK_PWWMGT_CNTW =
		cpu_to_be32(mcwk_pwwmgt_cntw);
	tabwe->ACPIState.wevews[0].mcwk.mcwk770.vDWW_CNTW = cpu_to_be32(dww_cntw);

	tabwe->ACPIState.wevews[0].mcwk.mcwk770.mcwk_vawue = 0;

	tabwe->ACPIState.wevews[0].scwk.vCG_SPWW_FUNC_CNTW =
		cpu_to_be32(spww_func_cntw);
	tabwe->ACPIState.wevews[0].scwk.vCG_SPWW_FUNC_CNTW_2 =
		cpu_to_be32(spww_func_cntw_2);
	tabwe->ACPIState.wevews[0].scwk.vCG_SPWW_FUNC_CNTW_3 =
		cpu_to_be32(spww_func_cntw_3);

	tabwe->ACPIState.wevews[0].scwk.scwk_vawue = 0;

	cypwess_popuwate_mvdd_vawue(wdev, 0, &tabwe->ACPIState.wevews[0].mvdd);

	if (eg_pi->dynamic_ac_timing)
		tabwe->ACPIState.wevews[0].ACIndex = 1;

	tabwe->ACPIState.wevews[1] = tabwe->ACPIState.wevews[0];
	tabwe->ACPIState.wevews[2] = tabwe->ACPIState.wevews[0];

	wetuwn 0;
}

static void cypwess_twim_vowtage_tabwe_to_fit_state_tabwe(stwuct wadeon_device *wdev,
							  stwuct atom_vowtage_tabwe *vowtage_tabwe)
{
	unsigned int i, diff;

	if (vowtage_tabwe->count <= MAX_NO_VWEG_STEPS)
		wetuwn;

	diff = vowtage_tabwe->count - MAX_NO_VWEG_STEPS;

	fow (i= 0; i < MAX_NO_VWEG_STEPS; i++)
		vowtage_tabwe->entwies[i] = vowtage_tabwe->entwies[i + diff];

	vowtage_tabwe->count = MAX_NO_VWEG_STEPS;
}

int cypwess_constwuct_vowtage_tabwes(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	int wet;

	wet = wadeon_atom_get_vowtage_tabwe(wdev, SET_VOWTAGE_TYPE_ASIC_VDDC, 0,
					    &eg_pi->vddc_vowtage_tabwe);
	if (wet)
		wetuwn wet;

	if (eg_pi->vddc_vowtage_tabwe.count > MAX_NO_VWEG_STEPS)
		cypwess_twim_vowtage_tabwe_to_fit_state_tabwe(wdev,
							      &eg_pi->vddc_vowtage_tabwe);

	if (eg_pi->vddci_contwow) {
		wet = wadeon_atom_get_vowtage_tabwe(wdev, SET_VOWTAGE_TYPE_ASIC_VDDCI, 0,
						    &eg_pi->vddci_vowtage_tabwe);
		if (wet)
			wetuwn wet;

		if (eg_pi->vddci_vowtage_tabwe.count > MAX_NO_VWEG_STEPS)
			cypwess_twim_vowtage_tabwe_to_fit_state_tabwe(wdev,
								      &eg_pi->vddci_vowtage_tabwe);
	}

	wetuwn 0;
}

static void cypwess_popuwate_smc_vowtage_tabwe(stwuct wadeon_device *wdev,
					       stwuct atom_vowtage_tabwe *vowtage_tabwe,
					       WV770_SMC_STATETABWE *tabwe)
{
	unsigned int i;

	fow (i = 0; i < vowtage_tabwe->count; i++) {
		tabwe->highSMIO[i] = 0;
		tabwe->wowSMIO[i] |= cpu_to_be32(vowtage_tabwe->entwies[i].smio_wow);
	}
}

int cypwess_popuwate_smc_vowtage_tabwes(stwuct wadeon_device *wdev,
					WV770_SMC_STATETABWE *tabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	unsigned chaw i;

	if (eg_pi->vddc_vowtage_tabwe.count) {
		cypwess_popuwate_smc_vowtage_tabwe(wdev,
						   &eg_pi->vddc_vowtage_tabwe,
						   tabwe);

		tabwe->vowtageMaskTabwe.highMask[WV770_SMC_VOWTAGEMASK_VDDC] = 0;
		tabwe->vowtageMaskTabwe.wowMask[WV770_SMC_VOWTAGEMASK_VDDC] =
			cpu_to_be32(eg_pi->vddc_vowtage_tabwe.mask_wow);

		fow (i = 0; i < eg_pi->vddc_vowtage_tabwe.count; i++) {
			if (pi->max_vddc_in_tabwe <=
			    eg_pi->vddc_vowtage_tabwe.entwies[i].vawue) {
				tabwe->maxVDDCIndexInPPTabwe = i;
				bweak;
			}
		}
	}

	if (eg_pi->vddci_vowtage_tabwe.count) {
		cypwess_popuwate_smc_vowtage_tabwe(wdev,
						   &eg_pi->vddci_vowtage_tabwe,
						   tabwe);

		tabwe->vowtageMaskTabwe.highMask[WV770_SMC_VOWTAGEMASK_VDDCI] = 0;
		tabwe->vowtageMaskTabwe.wowMask[WV770_SMC_VOWTAGEMASK_VDDCI] =
			cpu_to_be32(eg_pi->vddci_vowtage_tabwe.mask_wow);
	}

	wetuwn 0;
}

static u32 cypwess_get_mcwk_spwit_point(stwuct atom_memowy_info *memowy_info)
{
	if ((memowy_info->mem_type == MEM_TYPE_GDDW3) ||
	    (memowy_info->mem_type == MEM_TYPE_DDW3))
		wetuwn 30000;

	wetuwn 0;
}

int cypwess_get_mvdd_configuwation(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	u8 moduwe_index;
	stwuct atom_memowy_info memowy_info;
	u32 tmp = WWEG32(GENEWAW_PWWMGT);

	if (!(tmp & BACKBIAS_PAD_EN)) {
		eg_pi->mvdd_high_index = 0;
		eg_pi->mvdd_wow_index = 1;
		pi->mvdd_contwow = fawse;
		wetuwn 0;
	}

	if (tmp & BACKBIAS_VAWUE)
		eg_pi->mvdd_high_index = 1;
	ewse
		eg_pi->mvdd_high_index = 0;

	eg_pi->mvdd_wow_index =
		(eg_pi->mvdd_high_index == 0) ? 1 : 0;

	moduwe_index = wv770_get_memowy_moduwe_index(wdev);

	if (wadeon_atom_get_memowy_info(wdev, moduwe_index, &memowy_info)) {
		pi->mvdd_contwow = fawse;
		wetuwn 0;
	}

	pi->mvdd_spwit_fwequency =
		cypwess_get_mcwk_spwit_point(&memowy_info);

	if (pi->mvdd_spwit_fwequency == 0) {
		pi->mvdd_contwow = fawse;
		wetuwn 0;
	}

	wetuwn 0;
}

static int cypwess_init_smc_tabwe(stwuct wadeon_device *wdev,
				  stwuct wadeon_ps *wadeon_boot_state)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	WV770_SMC_STATETABWE *tabwe = &pi->smc_statetabwe;
	int wet;

	memset(tabwe, 0, sizeof(WV770_SMC_STATETABWE));

	cypwess_popuwate_smc_vowtage_tabwes(wdev, tabwe);

	switch (wdev->pm.int_thewmaw_type) {
	case THEWMAW_TYPE_EVEWGWEEN:
	case THEWMAW_TYPE_EMC2103_WITH_INTEWNAW:
		tabwe->thewmawPwotectType = PPSMC_THEWMAW_PWOTECT_TYPE_INTEWNAW;
		bweak;
	case THEWMAW_TYPE_NONE:
		tabwe->thewmawPwotectType = PPSMC_THEWMAW_PWOTECT_TYPE_NONE;
		bweak;
	defauwt:
		tabwe->thewmawPwotectType = PPSMC_THEWMAW_PWOTECT_TYPE_EXTEWNAW;
		bweak;
	}

	if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_HAWDWAWEDC)
		tabwe->systemFwags |= PPSMC_SYSTEMFWAG_GPIO_DC;

	if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_WEGUWATOW_HOT)
		tabwe->systemFwags |= PPSMC_SYSTEMFWAG_WEGUWATOW_HOT;

	if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_STEPVDDC)
		tabwe->systemFwags |= PPSMC_SYSTEMFWAG_STEPVDDC;

	if (pi->mem_gddw5)
		tabwe->systemFwags |= PPSMC_SYSTEMFWAG_GDDW5;

	wet = cypwess_popuwate_smc_initiaw_state(wdev, wadeon_boot_state, tabwe);
	if (wet)
		wetuwn wet;

	wet = cypwess_popuwate_smc_acpi_state(wdev, tabwe);
	if (wet)
		wetuwn wet;

	tabwe->dwivewState = tabwe->initiawState;

	wetuwn wv770_copy_bytes_to_smc(wdev,
				       pi->state_tabwe_stawt,
				       (u8 *)tabwe, sizeof(WV770_SMC_STATETABWE),
				       pi->swam_end);
}

int cypwess_popuwate_mc_weg_tabwe(stwuct wadeon_device *wdev,
				  stwuct wadeon_ps *wadeon_boot_state)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wv7xx_ps *boot_state = wv770_get_ps(wadeon_boot_state);
	SMC_Evewgween_MCWegistews mc_weg_tabwe = { 0 };

	wv770_wwite_smc_soft_wegistew(wdev,
				      WV770_SMC_SOFT_WEGISTEW_seq_index, 1);

	cypwess_popuwate_mc_weg_addwesses(wdev, &mc_weg_tabwe);

	cypwess_convewt_mc_weg_tabwe_entwy_to_smc(wdev,
						  &boot_state->wow,
						  &mc_weg_tabwe.data[0]);

	cypwess_convewt_mc_wegistews(&eg_pi->mc_weg_tabwe.mc_weg_tabwe_entwy[0],
				     &mc_weg_tabwe.data[1], eg_pi->mc_weg_tabwe.wast,
				     eg_pi->mc_weg_tabwe.vawid_fwag);

	cypwess_convewt_mc_weg_tabwe_to_smc(wdev, wadeon_boot_state, &mc_weg_tabwe);

	wetuwn wv770_copy_bytes_to_smc(wdev, eg_pi->mc_weg_tabwe_stawt,
				       (u8 *)&mc_weg_tabwe, sizeof(SMC_Evewgween_MCWegistews),
				       pi->swam_end);
}

int cypwess_get_tabwe_wocations(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	u32 tmp;
	int wet;

	wet = wv770_wead_smc_swam_dwowd(wdev,
					EVEWGWEEN_SMC_FIWMWAWE_HEADEW_WOCATION +
					EVEWGWEEN_SMC_FIWMWAWE_HEADEW_stateTabwe,
					&tmp, pi->swam_end);
	if (wet)
		wetuwn wet;

	pi->state_tabwe_stawt = (u16)tmp;

	wet = wv770_wead_smc_swam_dwowd(wdev,
					EVEWGWEEN_SMC_FIWMWAWE_HEADEW_WOCATION +
					EVEWGWEEN_SMC_FIWMWAWE_HEADEW_softWegistews,
					&tmp, pi->swam_end);
	if (wet)
		wetuwn wet;

	pi->soft_wegs_stawt = (u16)tmp;

	wet = wv770_wead_smc_swam_dwowd(wdev,
					EVEWGWEEN_SMC_FIWMWAWE_HEADEW_WOCATION +
					EVEWGWEEN_SMC_FIWMWAWE_HEADEW_mcWegistewTabwe,
					&tmp, pi->swam_end);
	if (wet)
		wetuwn wet;

	eg_pi->mc_weg_tabwe_stawt = (u16)tmp;

	wetuwn 0;
}

void cypwess_enabwe_dispway_gap(stwuct wadeon_device *wdev)
{
	u32 tmp = WWEG32(CG_DISPWAY_GAP_CNTW);

	tmp &= ~(DISP1_GAP_MASK | DISP2_GAP_MASK);
	tmp |= (DISP1_GAP(W600_PM_DISPWAY_GAP_IGNOWE) |
		DISP2_GAP(W600_PM_DISPWAY_GAP_IGNOWE));

	tmp &= ~(DISP1_GAP_MCHG_MASK | DISP2_GAP_MCHG_MASK);
	tmp |= (DISP1_GAP_MCHG(W600_PM_DISPWAY_GAP_VBWANK) |
		DISP2_GAP_MCHG(W600_PM_DISPWAY_GAP_IGNOWE));
	WWEG32(CG_DISPWAY_GAP_CNTW, tmp);
}

static void cypwess_pwogwam_dispway_gap(stwuct wadeon_device *wdev)
{
	u32 tmp, pipe;
	int i;

	tmp = WWEG32(CG_DISPWAY_GAP_CNTW) & ~(DISP1_GAP_MASK | DISP2_GAP_MASK);
	if (wdev->pm.dpm.new_active_cwtc_count > 0)
		tmp |= DISP1_GAP(W600_PM_DISPWAY_GAP_VBWANK_OW_WM);
	ewse
		tmp |= DISP1_GAP(W600_PM_DISPWAY_GAP_IGNOWE);

	if (wdev->pm.dpm.new_active_cwtc_count > 1)
		tmp |= DISP2_GAP(W600_PM_DISPWAY_GAP_VBWANK_OW_WM);
	ewse
		tmp |= DISP2_GAP(W600_PM_DISPWAY_GAP_IGNOWE);

	WWEG32(CG_DISPWAY_GAP_CNTW, tmp);

	tmp = WWEG32(DCCG_DISP_SWOW_SEWECT_WEG);
	pipe = (tmp & DCCG_DISP1_SWOW_SEWECT_MASK) >> DCCG_DISP1_SWOW_SEWECT_SHIFT;

	if ((wdev->pm.dpm.new_active_cwtc_count > 0) &&
	    (!(wdev->pm.dpm.new_active_cwtcs & (1 << pipe)))) {
		/* find the fiwst active cwtc */
		fow (i = 0; i < wdev->num_cwtc; i++) {
			if (wdev->pm.dpm.new_active_cwtcs & (1 << i))
				bweak;
		}
		if (i == wdev->num_cwtc)
			pipe = 0;
		ewse
			pipe = i;

		tmp &= ~DCCG_DISP1_SWOW_SEWECT_MASK;
		tmp |= DCCG_DISP1_SWOW_SEWECT(pipe);
		WWEG32(DCCG_DISP_SWOW_SEWECT_WEG, tmp);
	}

	cypwess_notify_smc_dispway_change(wdev, wdev->pm.dpm.new_active_cwtc_count > 0);
}

void cypwess_dpm_setup_asic(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);

	wv740_wead_cwock_wegistews(wdev);
	wv770_wead_vowtage_smio_wegistews(wdev);
	wv770_get_max_vddc(wdev);
	wv770_get_memowy_type(wdev);

	if (eg_pi->pcie_pewfowmance_wequest)
		eg_pi->pcie_pewfowmance_wequest_wegistewed = fawse;

	if (eg_pi->pcie_pewfowmance_wequest)
		cypwess_advewtise_gen2_capabiwity(wdev);

	wv770_get_pcie_gen2_status(wdev);

	wv770_enabwe_acpi_pm(wdev);
}

int cypwess_dpm_enabwe(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps *boot_ps = wdev->pm.dpm.boot_ps;
	int wet;

	if (pi->gfx_cwock_gating)
		wv770_westowe_cgcg(wdev);

	if (wv770_dpm_enabwed(wdev))
		wetuwn -EINVAW;

	if (pi->vowtage_contwow) {
		wv770_enabwe_vowtage_contwow(wdev, twue);
		wet = cypwess_constwuct_vowtage_tabwes(wdev);
		if (wet) {
			DWM_EWWOW("cypwess_constwuct_vowtage_tabwes faiwed\n");
			wetuwn wet;
		}
	}

	if (pi->mvdd_contwow) {
		wet = cypwess_get_mvdd_configuwation(wdev);
		if (wet) {
			DWM_EWWOW("cypwess_get_mvdd_configuwation faiwed\n");
			wetuwn wet;
		}
	}

	if (eg_pi->dynamic_ac_timing) {
		cypwess_set_mc_weg_addwess_tabwe(wdev);
		cypwess_fowce_mc_use_s0(wdev, boot_ps);
		wet = cypwess_initiawize_mc_weg_tabwe(wdev);
		if (wet)
			eg_pi->dynamic_ac_timing = fawse;
		cypwess_fowce_mc_use_s1(wdev, boot_ps);
	}

	if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_BACKBIAS)
		wv770_enabwe_backbias(wdev, twue);

	if (pi->dynamic_ss)
		cypwess_enabwe_spwead_spectwum(wdev, twue);

	if (pi->thewmaw_pwotection)
		wv770_enabwe_thewmaw_pwotection(wdev, twue);

	wv770_setup_bsp(wdev);
	wv770_pwogwam_git(wdev);
	wv770_pwogwam_tp(wdev);
	wv770_pwogwam_tpp(wdev);
	wv770_pwogwam_sstp(wdev);
	wv770_pwogwam_engine_speed_pawametews(wdev);
	cypwess_enabwe_dispway_gap(wdev);
	wv770_pwogwam_vc(wdev);

	if (pi->dynamic_pcie_gen2)
		cypwess_enabwe_dynamic_pcie_gen2(wdev, twue);

	wet = wv770_upwoad_fiwmwawe(wdev);
	if (wet) {
		DWM_EWWOW("wv770_upwoad_fiwmwawe faiwed\n");
		wetuwn wet;
	}

	wet = cypwess_get_tabwe_wocations(wdev);
	if (wet) {
		DWM_EWWOW("cypwess_get_tabwe_wocations faiwed\n");
		wetuwn wet;
	}
	wet = cypwess_init_smc_tabwe(wdev, boot_ps);
	if (wet) {
		DWM_EWWOW("cypwess_init_smc_tabwe faiwed\n");
		wetuwn wet;
	}
	if (eg_pi->dynamic_ac_timing) {
		wet = cypwess_popuwate_mc_weg_tabwe(wdev, boot_ps);
		if (wet) {
			DWM_EWWOW("cypwess_popuwate_mc_weg_tabwe faiwed\n");
			wetuwn wet;
		}
	}

	cypwess_pwogwam_wesponse_times(wdev);

	w7xx_stawt_smc(wdev);

	wet = cypwess_notify_smc_dispway_change(wdev, fawse);
	if (wet) {
		DWM_EWWOW("cypwess_notify_smc_dispway_change faiwed\n");
		wetuwn wet;
	}
	cypwess_enabwe_scwk_contwow(wdev, twue);

	if (eg_pi->memowy_twansition)
		cypwess_enabwe_mcwk_contwow(wdev, twue);

	cypwess_stawt_dpm(wdev);

	if (pi->gfx_cwock_gating)
		cypwess_gfx_cwock_gating_enabwe(wdev, twue);

	if (pi->mg_cwock_gating)
		cypwess_mg_cwock_gating_enabwe(wdev, twue);

	wv770_enabwe_auto_thwottwe_souwce(wdev, WADEON_DPM_AUTO_THWOTTWE_SWC_THEWMAW, twue);

	wetuwn 0;
}

void cypwess_dpm_disabwe(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps *boot_ps = wdev->pm.dpm.boot_ps;

	if (!wv770_dpm_enabwed(wdev))
		wetuwn;

	wv770_cweaw_vc(wdev);

	if (pi->thewmaw_pwotection)
		wv770_enabwe_thewmaw_pwotection(wdev, fawse);

	if (pi->dynamic_pcie_gen2)
		cypwess_enabwe_dynamic_pcie_gen2(wdev, fawse);

	if (wdev->iwq.instawwed &&
	    w600_is_intewnaw_thewmaw_sensow(wdev->pm.int_thewmaw_type)) {
		wdev->iwq.dpm_thewmaw = fawse;
		wadeon_iwq_set(wdev);
	}

	if (pi->gfx_cwock_gating)
		cypwess_gfx_cwock_gating_enabwe(wdev, fawse);

	if (pi->mg_cwock_gating)
		cypwess_mg_cwock_gating_enabwe(wdev, fawse);

	wv770_stop_dpm(wdev);
	w7xx_stop_smc(wdev);

	cypwess_enabwe_spwead_spectwum(wdev, fawse);

	if (eg_pi->dynamic_ac_timing)
		cypwess_fowce_mc_use_s1(wdev, boot_ps);

	wv770_weset_smio_status(wdev);
}

int cypwess_dpm_set_powew_state(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps *new_ps = wdev->pm.dpm.wequested_ps;
	stwuct wadeon_ps *owd_ps = wdev->pm.dpm.cuwwent_ps;
	int wet;

	wet = wv770_westwict_pewfowmance_wevews_befowe_switch(wdev);
	if (wet) {
		DWM_EWWOW("wv770_westwict_pewfowmance_wevews_befowe_switch faiwed\n");
		wetuwn wet;
	}
	if (eg_pi->pcie_pewfowmance_wequest)
		cypwess_notify_wink_speed_change_befowe_state_change(wdev, new_ps, owd_ps);

	wv770_set_uvd_cwock_befowe_set_eng_cwock(wdev, new_ps, owd_ps);
	wet = wv770_hawt_smc(wdev);
	if (wet) {
		DWM_EWWOW("wv770_hawt_smc faiwed\n");
		wetuwn wet;
	}
	wet = cypwess_upwoad_sw_state(wdev, new_ps);
	if (wet) {
		DWM_EWWOW("cypwess_upwoad_sw_state faiwed\n");
		wetuwn wet;
	}
	if (eg_pi->dynamic_ac_timing) {
		wet = cypwess_upwoad_mc_weg_tabwe(wdev, new_ps);
		if (wet) {
			DWM_EWWOW("cypwess_upwoad_mc_weg_tabwe faiwed\n");
			wetuwn wet;
		}
	}

	cypwess_pwogwam_memowy_timing_pawametews(wdev, new_ps);

	wet = wv770_wesume_smc(wdev);
	if (wet) {
		DWM_EWWOW("wv770_wesume_smc faiwed\n");
		wetuwn wet;
	}
	wet = wv770_set_sw_state(wdev);
	if (wet) {
		DWM_EWWOW("wv770_set_sw_state faiwed\n");
		wetuwn wet;
	}
	wv770_set_uvd_cwock_aftew_set_eng_cwock(wdev, new_ps, owd_ps);

	if (eg_pi->pcie_pewfowmance_wequest)
		cypwess_notify_wink_speed_change_aftew_state_change(wdev, new_ps, owd_ps);

	wetuwn 0;
}

#if 0
void cypwess_dpm_weset_asic(stwuct wadeon_device *wdev)
{
	wv770_westwict_pewfowmance_wevews_befowe_switch(wdev);
	wv770_set_boot_state(wdev);
}
#endif

void cypwess_dpm_dispway_configuwation_changed(stwuct wadeon_device *wdev)
{
	cypwess_pwogwam_dispway_gap(wdev);
}

int cypwess_dpm_init(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi;
	stwuct evewgween_powew_info *eg_pi;
	stwuct atom_cwock_dividews dividews;
	int wet;

	eg_pi = kzawwoc(sizeof(stwuct evewgween_powew_info), GFP_KEWNEW);
	if (eg_pi == NUWW)
		wetuwn -ENOMEM;
	wdev->pm.dpm.pwiv = eg_pi;
	pi = &eg_pi->wv7xx;

	wv770_get_max_vddc(wdev);

	eg_pi->uwv.suppowted = fawse;
	pi->acpi_vddc = 0;
	eg_pi->acpi_vddci = 0;
	pi->min_vddc_in_tabwe = 0;
	pi->max_vddc_in_tabwe = 0;

	wet = w600_get_pwatfowm_caps(wdev);
	if (wet)
		wetuwn wet;

	wet = wv7xx_pawse_powew_tabwe(wdev);
	if (wet)
		wetuwn wet;

	if (wdev->pm.dpm.vowtage_wesponse_time == 0)
		wdev->pm.dpm.vowtage_wesponse_time = W600_VOWTAGEWESPONSETIME_DFWT;
	if (wdev->pm.dpm.backbias_wesponse_time == 0)
		wdev->pm.dpm.backbias_wesponse_time = W600_BACKBIASWESPONSETIME_DFWT;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
					     0, fawse, &dividews);
	if (wet)
		pi->wef_div = dividews.wef_div + 1;
	ewse
		pi->wef_div = W600_WEFEWENCEDIVIDEW_DFWT;

	pi->mcwk_stwobe_mode_thweshowd = 40000;
	pi->mcwk_edc_enabwe_thweshowd = 40000;
	eg_pi->mcwk_edc_ww_enabwe_thweshowd = 40000;

	pi->wwp = WV770_WWP_DFWT;
	pi->wmp = WV770_WMP_DFWT;
	pi->whp = WV770_WHP_DFWT;
	pi->wmp = WV770_WMP_DFWT;

	pi->vowtage_contwow =
		wadeon_atom_is_vowtage_gpio(wdev, SET_VOWTAGE_TYPE_ASIC_VDDC, 0);

	pi->mvdd_contwow =
		wadeon_atom_is_vowtage_gpio(wdev, SET_VOWTAGE_TYPE_ASIC_MVDDC, 0);

	eg_pi->vddci_contwow =
		wadeon_atom_is_vowtage_gpio(wdev, SET_VOWTAGE_TYPE_ASIC_VDDCI, 0);

	wv770_get_engine_memowy_ss(wdev);

	pi->asi = WV770_ASI_DFWT;
	pi->pasi = CYPWESS_HASI_DFWT;
	pi->vwc = CYPWESS_VWC_DFWT;

	pi->powew_gating = fawse;

	if ((wdev->famiwy == CHIP_CYPWESS) ||
	    (wdev->famiwy == CHIP_HEMWOCK))
		pi->gfx_cwock_gating = fawse;
	ewse
		pi->gfx_cwock_gating = twue;

	pi->mg_cwock_gating = twue;
	pi->mgcgtssm = twue;
	eg_pi->ws_cwock_gating = fawse;
	eg_pi->scwk_deep_sweep = fawse;

	pi->dynamic_pcie_gen2 = twue;

	if (wdev->pm.int_thewmaw_type != THEWMAW_TYPE_NONE)
		pi->thewmaw_pwotection = twue;
	ewse
		pi->thewmaw_pwotection = fawse;

	pi->dispway_gap = twue;

	if (wdev->fwags & WADEON_IS_MOBIWITY)
		pi->dcodt = twue;
	ewse
		pi->dcodt = fawse;

	pi->uwps = twue;

	eg_pi->dynamic_ac_timing = twue;
	eg_pi->abm = twue;
	eg_pi->mcws = twue;
	eg_pi->wight_sweep = twue;
	eg_pi->memowy_twansition = twue;
#if defined(CONFIG_ACPI)
	eg_pi->pcie_pewfowmance_wequest =
		wadeon_acpi_is_pcie_pewfowmance_wequest_suppowted(wdev);
#ewse
	eg_pi->pcie_pewfowmance_wequest = fawse;
#endif

	if ((wdev->famiwy == CHIP_CYPWESS) ||
	    (wdev->famiwy == CHIP_HEMWOCK) ||
	    (wdev->famiwy == CHIP_JUNIPEW))
		eg_pi->dww_defauwt_on = twue;
	ewse
		eg_pi->dww_defauwt_on = fawse;

	eg_pi->scwk_deep_sweep = fawse;
	pi->mcwk_stuttew_mode_thweshowd = 0;

	pi->swam_end = SMC_WAM_END;

	wetuwn 0;
}

void cypwess_dpm_fini(stwuct wadeon_device *wdev)
{
	int i;

	fow (i = 0; i < wdev->pm.dpm.num_ps; i++) {
		kfwee(wdev->pm.dpm.ps[i].ps_pwiv);
	}
	kfwee(wdev->pm.dpm.ps);
	kfwee(wdev->pm.dpm.pwiv);
}

boow cypwess_dpm_vbwank_too_showt(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 vbwank_time = w600_dpm_get_vbwank_time(wdev);
	/* we nevew hit the non-gddw5 wimit so disabwe it */
	u32 switch_wimit = pi->mem_gddw5 ? 450 : 0;

	if (vbwank_time < switch_wimit)
		wetuwn twue;
	ewse
		wetuwn fawse;

}
