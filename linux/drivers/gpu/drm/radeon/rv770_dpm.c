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

#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "wv770.h"
#incwude "wv770d.h"
#incwude "w600_dpm.h"
#incwude "wv770_dpm.h"
#incwude "cypwess_dpm.h"
#incwude "atom.h"
#incwude "evewgween.h"
#incwude <winux/seq_fiwe.h>

#define MC_CG_AWB_FWEQ_F0           0x0a
#define MC_CG_AWB_FWEQ_F1           0x0b
#define MC_CG_AWB_FWEQ_F2           0x0c
#define MC_CG_AWB_FWEQ_F3           0x0d

#define MC_CG_SEQ_DWAMCONF_S0       0x05
#define MC_CG_SEQ_DWAMCONF_S1       0x06

#define PCIE_BUS_CWK                10000
#define TCWK                        (PCIE_BUS_CWK / 10)

#define SMC_WAM_END 0xC000

stwuct wv7xx_ps *wv770_get_ps(stwuct wadeon_ps *wps)
{
	stwuct wv7xx_ps *ps = wps->ps_pwiv;

	wetuwn ps;
}

stwuct wv7xx_powew_info *wv770_get_pi(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wdev->pm.dpm.pwiv;

	wetuwn pi;
}

stwuct evewgween_powew_info *evewgween_get_pi(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *pi = wdev->pm.dpm.pwiv;

	wetuwn pi;
}

static void wv770_enabwe_bif_dynamic_pcie_gen2(stwuct wadeon_device *wdev,
					       boow enabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 tmp;

	tmp = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
	if (enabwe) {
		tmp &= ~WC_HW_VOWTAGE_IF_CONTWOW_MASK;
		tmp |= WC_HW_VOWTAGE_IF_CONTWOW(1);
		tmp |= WC_GEN2_EN_STWAP;
	} ewse {
		if (!pi->boot_in_gen2) {
			tmp &= ~WC_HW_VOWTAGE_IF_CONTWOW_MASK;
			tmp &= ~WC_GEN2_EN_STWAP;
		}
	}
	if ((tmp & WC_OTHEW_SIDE_EVEW_SENT_GEN2) ||
	    (tmp & WC_OTHEW_SIDE_SUPPOWTS_GEN2))
		WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, tmp);

}

static void wv770_enabwe_w0s(stwuct wadeon_device *wdev)
{
	u32 tmp;

	tmp = WWEG32_PCIE_POWT(PCIE_WC_CNTW) & ~WC_W0S_INACTIVITY_MASK;
	tmp |= WC_W0S_INACTIVITY(3);
	WWEG32_PCIE_POWT(PCIE_WC_CNTW, tmp);
}

static void wv770_enabwe_w1(stwuct wadeon_device *wdev)
{
	u32 tmp;

	tmp = WWEG32_PCIE_POWT(PCIE_WC_CNTW);
	tmp &= ~WC_W1_INACTIVITY_MASK;
	tmp |= WC_W1_INACTIVITY(4);
	tmp &= ~WC_PMI_TO_W1_DIS;
	tmp &= ~WC_ASPM_TO_W1_DIS;
	WWEG32_PCIE_POWT(PCIE_WC_CNTW, tmp);
}

static void wv770_enabwe_pww_sweep_in_w1(stwuct wadeon_device *wdev)
{
	u32 tmp;

	tmp = WWEG32_PCIE_POWT(PCIE_WC_CNTW) & ~WC_W1_INACTIVITY_MASK;
	tmp |= WC_W1_INACTIVITY(8);
	WWEG32_PCIE_POWT(PCIE_WC_CNTW, tmp);

	/* NOTE, this is a PCIE indiwect weg, not PCIE POWT */
	tmp = WWEG32_PCIE(PCIE_P_CNTW);
	tmp |= P_PWW_PWWDN_IN_W1W23;
	tmp &= ~P_PWW_BUF_PDNB;
	tmp &= ~P_PWW_PDNB;
	tmp |= P_AWWOW_PWX_FWONTEND_SHUTOFF;
	WWEG32_PCIE(PCIE_P_CNTW, tmp);
}

static void wv770_gfx_cwock_gating_enabwe(stwuct wadeon_device *wdev,
					  boow enabwe)
{
	if (enabwe)
		WWEG32_P(SCWK_PWWMGT_CNTW, DYN_GFX_CWK_OFF_EN, ~DYN_GFX_CWK_OFF_EN);
	ewse {
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~DYN_GFX_CWK_OFF_EN);
		WWEG32_P(SCWK_PWWMGT_CNTW, GFX_CWK_FOWCE_ON, ~GFX_CWK_FOWCE_ON);
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~GFX_CWK_FOWCE_ON);
		WWEG32(GB_TIWING_CONFIG);
	}
}

static void wv770_mg_cwock_gating_enabwe(stwuct wadeon_device *wdev,
					 boow enabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	if (enabwe) {
		u32 mgcg_cgtt_wocaw0;

		if (wdev->famiwy == CHIP_WV770)
			mgcg_cgtt_wocaw0 = WV770_MGCGTTWOCAW0_DFWT;
		ewse
			mgcg_cgtt_wocaw0 = WV7XX_MGCGTTWOCAW0_DFWT;

		WWEG32(CG_CGTT_WOCAW_0, mgcg_cgtt_wocaw0);
		WWEG32(CG_CGTT_WOCAW_1, (WV770_MGCGTTWOCAW1_DFWT & 0xFFFFCFFF));

		if (pi->mgcgtssm)
			WWEG32(CGTS_SM_CTWW_WEG, WV770_MGCGCGTSSMCTWW_DFWT);
	} ewse {
		WWEG32(CG_CGTT_WOCAW_0, 0xFFFFFFFF);
		WWEG32(CG_CGTT_WOCAW_1, 0xFFFFCFFF);
	}
}

void wv770_westowe_cgcg(stwuct wadeon_device *wdev)
{
	boow dpm_en = fawse, cg_en = fawse;

	if (WWEG32(GENEWAW_PWWMGT) & GWOBAW_PWWMGT_EN)
		dpm_en = twue;
	if (WWEG32(SCWK_PWWMGT_CNTW) & DYN_GFX_CWK_OFF_EN)
		cg_en = twue;

	if (dpm_en && !cg_en)
		WWEG32_P(SCWK_PWWMGT_CNTW, DYN_GFX_CWK_OFF_EN, ~DYN_GFX_CWK_OFF_EN);
}

static void wv770_stawt_dpm(stwuct wadeon_device *wdev)
{
	WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~SCWK_PWWMGT_OFF);

	WWEG32_P(MCWK_PWWMGT_CNTW, 0, ~MPWW_PWWMGT_OFF);

	WWEG32_P(GENEWAW_PWWMGT, GWOBAW_PWWMGT_EN, ~GWOBAW_PWWMGT_EN);
}

void wv770_stop_dpm(stwuct wadeon_device *wdev)
{
	PPSMC_Wesuwt wesuwt;

	wesuwt = wv770_send_msg_to_smc(wdev, PPSMC_MSG_TwoWevewsDisabwed);

	if (wesuwt != PPSMC_Wesuwt_OK)
		DWM_DEBUG("Couwd not fowce DPM to wow.\n");

	WWEG32_P(GENEWAW_PWWMGT, 0, ~GWOBAW_PWWMGT_EN);

	WWEG32_P(SCWK_PWWMGT_CNTW, SCWK_PWWMGT_OFF, ~SCWK_PWWMGT_OFF);

	WWEG32_P(MCWK_PWWMGT_CNTW, MPWW_PWWMGT_OFF, ~MPWW_PWWMGT_OFF);
}

boow wv770_dpm_enabwed(stwuct wadeon_device *wdev)
{
	if (WWEG32(GENEWAW_PWWMGT) & GWOBAW_PWWMGT_EN)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

void wv770_enabwe_thewmaw_pwotection(stwuct wadeon_device *wdev,
				     boow enabwe)
{
	if (enabwe)
		WWEG32_P(GENEWAW_PWWMGT, 0, ~THEWMAW_PWOTECTION_DIS);
	ewse
		WWEG32_P(GENEWAW_PWWMGT, THEWMAW_PWOTECTION_DIS, ~THEWMAW_PWOTECTION_DIS);
}

void wv770_enabwe_acpi_pm(stwuct wadeon_device *wdev)
{
	WWEG32_P(GENEWAW_PWWMGT, STATIC_PM_EN, ~STATIC_PM_EN);
}

u8 wv770_get_seq_vawue(stwuct wadeon_device *wdev,
		       stwuct wv7xx_pw *pw)
{
	wetuwn (pw->fwags & ATOM_PPWIB_W600_FWAGS_WOWPOWEW) ?
		MC_CG_SEQ_DWAMCONF_S0 : MC_CG_SEQ_DWAMCONF_S1;
}

#if 0
int wv770_wead_smc_soft_wegistew(stwuct wadeon_device *wdev,
				 u16 weg_offset, u32 *vawue)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	wetuwn wv770_wead_smc_swam_dwowd(wdev,
					 pi->soft_wegs_stawt + weg_offset,
					 vawue, pi->swam_end);
}
#endif

int wv770_wwite_smc_soft_wegistew(stwuct wadeon_device *wdev,
				  u16 weg_offset, u32 vawue)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	wetuwn wv770_wwite_smc_swam_dwowd(wdev,
					  pi->soft_wegs_stawt + weg_offset,
					  vawue, pi->swam_end);
}

int wv770_popuwate_smc_t(stwuct wadeon_device *wdev,
			 stwuct wadeon_ps *wadeon_state,
			 WV770_SMC_SWSTATE *smc_state)
{
	stwuct wv7xx_ps *state = wv770_get_ps(wadeon_state);
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	int i;
	int a_n;
	int a_d;
	u8 w[WV770_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE];
	u8 w[WV770_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE];
	u32 a_t;

	w[0] = 0;
	w[2] = 100;

	a_n = (int)state->medium.scwk * pi->wmp +
		(int)state->wow.scwk * (W600_AH_DFWT - pi->wwp);
	a_d = (int)state->wow.scwk * (100 - (int)pi->wwp) +
		(int)state->medium.scwk * pi->wmp;

	w[1] = (u8)(pi->wmp - (int)pi->wmp * a_n / a_d);
	w[0] = (u8)(pi->wwp + (100 - (int)pi->wwp) * a_n / a_d);

	a_n = (int)state->high.scwk * pi->whp + (int)state->medium.scwk *
		(W600_AH_DFWT - pi->wmp);
	a_d = (int)state->medium.scwk * (100 - (int)pi->wmp) +
		(int)state->high.scwk * pi->whp;

	w[2] = (u8)(pi->whp - (int)pi->whp * a_n / a_d);
	w[1] = (u8)(pi->wmp + (100 - (int)pi->wmp) * a_n / a_d);

	fow (i = 0; i < (WV770_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE - 1); i++) {
		a_t = CG_W(w[i] * pi->bsp / 200) | CG_W(w[i] * pi->bsp / 200);
		smc_state->wevews[i].aT = cpu_to_be32(a_t);
	}

	a_t = CG_W(w[WV770_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE - 1] * pi->pbsp / 200) |
		CG_W(w[WV770_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE - 1] * pi->pbsp / 200);

	smc_state->wevews[WV770_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE - 1].aT =
		cpu_to_be32(a_t);

	wetuwn 0;
}

int wv770_popuwate_smc_sp(stwuct wadeon_device *wdev,
			  stwuct wadeon_ps *wadeon_state,
			  WV770_SMC_SWSTATE *smc_state)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	int i;

	fow (i = 0; i < (WV770_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE - 1); i++)
		smc_state->wevews[i].bSP = cpu_to_be32(pi->dsp);

	smc_state->wevews[WV770_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE - 1].bSP =
		cpu_to_be32(pi->psp);

	wetuwn 0;
}

static void wv770_cawcuwate_fwactionaw_mpww_feedback_dividew(u32 memowy_cwock,
							     u32 wefewence_cwock,
							     boow gddw5,
							     stwuct atom_cwock_dividews *dividews,
							     u32 *cwkf,
							     u32 *cwkfwac)
{
	u32 post_dividew, wefewence_dividew, feedback_dividew8;
	u32 fycwk;

	if (gddw5)
		fycwk = (memowy_cwock * 8) / 2;
	ewse
		fycwk = (memowy_cwock * 4) / 2;

	post_dividew = dividews->post_div;
	wefewence_dividew = dividews->wef_div;

	feedback_dividew8 =
		(8 * fycwk * wefewence_dividew * post_dividew) / wefewence_cwock;

	*cwkf = feedback_dividew8 / 8;
	*cwkfwac = feedback_dividew8 % 8;
}

static int wv770_encode_ycwk_post_div(u32 postdiv, u32 *encoded_postdiv)
{
	int wet = 0;

	switch (postdiv) {
	case 1:
		*encoded_postdiv = 0;
		bweak;
	case 2:
		*encoded_postdiv = 1;
		bweak;
	case 4:
		*encoded_postdiv = 2;
		bweak;
	case 8:
		*encoded_postdiv = 3;
		bweak;
	case 16:
		*encoded_postdiv = 4;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

u32 wv770_map_cwkf_to_ibias(stwuct wadeon_device *wdev, u32 cwkf)
{
	if (cwkf <= 0x10)
		wetuwn 0x4B;
	if (cwkf <= 0x19)
		wetuwn 0x5B;
	if (cwkf <= 0x21)
		wetuwn 0x2B;
	if (cwkf <= 0x27)
		wetuwn 0x6C;
	if (cwkf <= 0x31)
		wetuwn 0x9D;
	wetuwn 0xC6;
}

static int wv770_popuwate_mcwk_vawue(stwuct wadeon_device *wdev,
				     u32 engine_cwock, u32 memowy_cwock,
				     WV7XX_SMC_MCWK_VAWUE *mcwk)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u8 encoded_wefewence_dividews[] = { 0, 16, 17, 20, 21 };
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
	u32 dww_cntw = pi->cwk_wegs.wv770.dww_cntw;
	stwuct atom_cwock_dividews dividews;
	u32 wefewence_cwock = wdev->cwock.mpww.wefewence_fweq;
	u32 cwkf, cwkfwac;
	u32 postdiv_ycwk;
	u32 ibias;
	int wet;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_MEMOWY_PWW_PAWAM,
					     memowy_cwock, fawse, &dividews);
	if (wet)
		wetuwn wet;

	if ((dividews.wef_div < 1) || (dividews.wef_div > 5))
		wetuwn -EINVAW;

	wv770_cawcuwate_fwactionaw_mpww_feedback_dividew(memowy_cwock, wefewence_cwock,
							 pi->mem_gddw5,
							 &dividews, &cwkf, &cwkfwac);

	wet = wv770_encode_ycwk_post_div(dividews.post_div, &postdiv_ycwk);
	if (wet)
		wetuwn wet;

	ibias = wv770_map_cwkf_to_ibias(wdev, cwkf);

	mpww_ad_func_cntw &= ~(CWKW_MASK |
			       YCWK_POST_DIV_MASK |
			       CWKF_MASK |
			       CWKFWAC_MASK |
			       IBIAS_MASK);
	mpww_ad_func_cntw |= CWKW(encoded_wefewence_dividews[dividews.wef_div - 1]);
	mpww_ad_func_cntw |= YCWK_POST_DIV(postdiv_ycwk);
	mpww_ad_func_cntw |= CWKF(cwkf);
	mpww_ad_func_cntw |= CWKFWAC(cwkfwac);
	mpww_ad_func_cntw |= IBIAS(ibias);

	if (dividews.vco_mode)
		mpww_ad_func_cntw_2 |= VCO_MODE;
	ewse
		mpww_ad_func_cntw_2 &= ~VCO_MODE;

	if (pi->mem_gddw5) {
		wv770_cawcuwate_fwactionaw_mpww_feedback_dividew(memowy_cwock,
								 wefewence_cwock,
								 pi->mem_gddw5,
								 &dividews, &cwkf, &cwkfwac);

		ibias = wv770_map_cwkf_to_ibias(wdev, cwkf);

		wet = wv770_encode_ycwk_post_div(dividews.post_div, &postdiv_ycwk);
		if (wet)
			wetuwn wet;

		mpww_dq_func_cntw &= ~(CWKW_MASK |
				       YCWK_POST_DIV_MASK |
				       CWKF_MASK |
				       CWKFWAC_MASK |
				       IBIAS_MASK);
		mpww_dq_func_cntw |= CWKW(encoded_wefewence_dividews[dividews.wef_div - 1]);
		mpww_dq_func_cntw |= YCWK_POST_DIV(postdiv_ycwk);
		mpww_dq_func_cntw |= CWKF(cwkf);
		mpww_dq_func_cntw |= CWKFWAC(cwkfwac);
		mpww_dq_func_cntw |= IBIAS(ibias);

		if (dividews.vco_mode)
			mpww_dq_func_cntw_2 |= VCO_MODE;
		ewse
			mpww_dq_func_cntw_2 &= ~VCO_MODE;
	}

	mcwk->mcwk770.mcwk_vawue = cpu_to_be32(memowy_cwock);
	mcwk->mcwk770.vMPWW_AD_FUNC_CNTW = cpu_to_be32(mpww_ad_func_cntw);
	mcwk->mcwk770.vMPWW_AD_FUNC_CNTW_2 = cpu_to_be32(mpww_ad_func_cntw_2);
	mcwk->mcwk770.vMPWW_DQ_FUNC_CNTW = cpu_to_be32(mpww_dq_func_cntw);
	mcwk->mcwk770.vMPWW_DQ_FUNC_CNTW_2 = cpu_to_be32(mpww_dq_func_cntw_2);
	mcwk->mcwk770.vMCWK_PWWMGT_CNTW = cpu_to_be32(mcwk_pwwmgt_cntw);
	mcwk->mcwk770.vDWW_CNTW = cpu_to_be32(dww_cntw);

	wetuwn 0;
}

static int wv770_popuwate_scwk_vawue(stwuct wadeon_device *wdev,
				     u32 engine_cwock,
				     WV770_SMC_SCWK_VAWUE *scwk)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct atom_cwock_dividews dividews;
	u32 spww_func_cntw =
		pi->cwk_wegs.wv770.cg_spww_func_cntw;
	u32 spww_func_cntw_2 =
		pi->cwk_wegs.wv770.cg_spww_func_cntw_2;
	u32 spww_func_cntw_3 =
		pi->cwk_wegs.wv770.cg_spww_func_cntw_3;
	u32 cg_spww_spwead_spectwum =
		pi->cwk_wegs.wv770.cg_spww_spwead_spectwum;
	u32 cg_spww_spwead_spectwum_2 =
		pi->cwk_wegs.wv770.cg_spww_spwead_spectwum_2;
	u64 tmp;
	u32 wefewence_cwock = wdev->cwock.spww.wefewence_fweq;
	u32 wefewence_dividew, post_dividew;
	u32 fbdiv;
	int wet;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
					     engine_cwock, fawse, &dividews);
	if (wet)
		wetuwn wet;

	wefewence_dividew = 1 + dividews.wef_div;

	if (dividews.enabwe_post_div)
		post_dividew = (0x0f & (dividews.post_div >> 4)) + (0x0f & dividews.post_div) + 2;
	ewse
		post_dividew = 1;

	tmp = (u64) engine_cwock * wefewence_dividew * post_dividew * 16384;
	do_div(tmp, wefewence_cwock);
	fbdiv = (u32) tmp;

	if (dividews.enabwe_post_div)
		spww_func_cntw |= SPWW_DIVEN;
	ewse
		spww_func_cntw &= ~SPWW_DIVEN;
	spww_func_cntw &= ~(SPWW_HIWEN_MASK | SPWW_WOWEN_MASK | SPWW_WEF_DIV_MASK);
	spww_func_cntw |= SPWW_WEF_DIV(dividews.wef_div);
	spww_func_cntw |= SPWW_HIWEN((dividews.post_div >> 4) & 0xf);
	spww_func_cntw |= SPWW_WOWEN(dividews.post_div & 0xf);

	spww_func_cntw_2 &= ~SCWK_MUX_SEW_MASK;
	spww_func_cntw_2 |= SCWK_MUX_SEW(2);

	spww_func_cntw_3 &= ~SPWW_FB_DIV_MASK;
	spww_func_cntw_3 |= SPWW_FB_DIV(fbdiv);
	spww_func_cntw_3 |= SPWW_DITHEN;

	if (pi->scwk_ss) {
		stwuct wadeon_atom_ss ss;
		u32 vco_fweq = engine_cwock * post_dividew;

		if (wadeon_atombios_get_asic_ss_info(wdev, &ss,
						     ASIC_INTEWNAW_ENGINE_SS, vco_fweq)) {
			u32 cwk_s = wefewence_cwock * 5 / (wefewence_dividew * ss.wate);
			u32 cwk_v = ss.pewcentage * fbdiv / (cwk_s * 10000);

			cg_spww_spwead_spectwum &= ~CWKS_MASK;
			cg_spww_spwead_spectwum |= CWKS(cwk_s);
			cg_spww_spwead_spectwum |= SSEN;

			cg_spww_spwead_spectwum_2 &= ~CWKV_MASK;
			cg_spww_spwead_spectwum_2 |= CWKV(cwk_v);
		}
	}

	scwk->scwk_vawue = cpu_to_be32(engine_cwock);
	scwk->vCG_SPWW_FUNC_CNTW = cpu_to_be32(spww_func_cntw);
	scwk->vCG_SPWW_FUNC_CNTW_2 = cpu_to_be32(spww_func_cntw_2);
	scwk->vCG_SPWW_FUNC_CNTW_3 = cpu_to_be32(spww_func_cntw_3);
	scwk->vCG_SPWW_SPWEAD_SPECTWUM = cpu_to_be32(cg_spww_spwead_spectwum);
	scwk->vCG_SPWW_SPWEAD_SPECTWUM_2 = cpu_to_be32(cg_spww_spwead_spectwum_2);

	wetuwn 0;
}

int wv770_popuwate_vddc_vawue(stwuct wadeon_device *wdev, u16 vddc,
			      WV770_SMC_VOWTAGE_VAWUE *vowtage)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	int i;

	if (!pi->vowtage_contwow) {
		vowtage->index = 0;
		vowtage->vawue = 0;
		wetuwn 0;
	}

	fow (i = 0; i < pi->vawid_vddc_entwies; i++) {
		if (vddc <= pi->vddc_tabwe[i].vddc) {
			vowtage->index = pi->vddc_tabwe[i].vddc_index;
			vowtage->vawue = cpu_to_be16(vddc);
			bweak;
		}
	}

	if (i == pi->vawid_vddc_entwies)
		wetuwn -EINVAW;

	wetuwn 0;
}

int wv770_popuwate_mvdd_vawue(stwuct wadeon_device *wdev, u32 mcwk,
			      WV770_SMC_VOWTAGE_VAWUE *vowtage)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	if (!pi->mvdd_contwow) {
		vowtage->index = MVDD_HIGH_INDEX;
		vowtage->vawue = cpu_to_be16(MVDD_HIGH_VAWUE);
		wetuwn 0;
	}

	if (mcwk <= pi->mvdd_spwit_fwequency) {
		vowtage->index = MVDD_WOW_INDEX;
		vowtage->vawue = cpu_to_be16(MVDD_WOW_VAWUE);
	} ewse {
		vowtage->index = MVDD_HIGH_INDEX;
		vowtage->vawue = cpu_to_be16(MVDD_HIGH_VAWUE);
	}

	wetuwn 0;
}

static int wv770_convewt_powew_wevew_to_smc(stwuct wadeon_device *wdev,
					    stwuct wv7xx_pw *pw,
					    WV770_SMC_HW_PEWFOWMANCE_WEVEW *wevew,
					    u8 watewmawk_wevew)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	int wet;

	wevew->gen2PCIE = pi->pcie_gen2 ?
		((pw->fwags & ATOM_PPWIB_W600_FWAGS_PCIEGEN2) ? 1 : 0) : 0;
	wevew->gen2XSP  = (pw->fwags & ATOM_PPWIB_W600_FWAGS_PCIEGEN2) ? 1 : 0;
	wevew->backbias = (pw->fwags & ATOM_PPWIB_W600_FWAGS_BACKBIASENABWE) ? 1 : 0;
	wevew->dispwayWatewmawk = watewmawk_wevew;

	if (wdev->famiwy == CHIP_WV740)
		wet = wv740_popuwate_scwk_vawue(wdev, pw->scwk,
						&wevew->scwk);
	ewse if ((wdev->famiwy == CHIP_WV730) || (wdev->famiwy == CHIP_WV710))
		wet = wv730_popuwate_scwk_vawue(wdev, pw->scwk,
						&wevew->scwk);
	ewse
		wet = wv770_popuwate_scwk_vawue(wdev, pw->scwk,
						&wevew->scwk);
	if (wet)
		wetuwn wet;

	if (wdev->famiwy == CHIP_WV740) {
		if (pi->mem_gddw5) {
			if (pw->mcwk <= pi->mcwk_stwobe_mode_thweshowd)
				wevew->stwobeMode =
					wv740_get_mcwk_fwequency_watio(pw->mcwk) | 0x10;
			ewse
				wevew->stwobeMode = 0;

			if (pw->mcwk > pi->mcwk_edc_enabwe_thweshowd)
				wevew->mcFwags = SMC_MC_EDC_WD_FWAG | SMC_MC_EDC_WW_FWAG;
			ewse
				wevew->mcFwags =  0;
		}
		wet = wv740_popuwate_mcwk_vawue(wdev, pw->scwk,
						pw->mcwk, &wevew->mcwk);
	} ewse if ((wdev->famiwy == CHIP_WV730) || (wdev->famiwy == CHIP_WV710))
		wet = wv730_popuwate_mcwk_vawue(wdev, pw->scwk,
						pw->mcwk, &wevew->mcwk);
	ewse
		wet = wv770_popuwate_mcwk_vawue(wdev, pw->scwk,
						pw->mcwk, &wevew->mcwk);
	if (wet)
		wetuwn wet;

	wet = wv770_popuwate_vddc_vawue(wdev, pw->vddc,
					&wevew->vddc);
	if (wet)
		wetuwn wet;

	wet = wv770_popuwate_mvdd_vawue(wdev, pw->mcwk, &wevew->mvdd);

	wetuwn wet;
}

static int wv770_convewt_powew_state_to_smc(stwuct wadeon_device *wdev,
					    stwuct wadeon_ps *wadeon_state,
					    WV770_SMC_SWSTATE *smc_state)
{
	stwuct wv7xx_ps *state = wv770_get_ps(wadeon_state);
	int wet;

	if (!(wadeon_state->caps & ATOM_PPWIB_DISAWWOW_ON_DC))
		smc_state->fwags |= PPSMC_SWSTATE_FWAG_DC;

	wet = wv770_convewt_powew_wevew_to_smc(wdev,
					       &state->wow,
					       &smc_state->wevews[0],
					       PPSMC_DISPWAY_WATEWMAWK_WOW);
	if (wet)
		wetuwn wet;

	wet = wv770_convewt_powew_wevew_to_smc(wdev,
					       &state->medium,
					       &smc_state->wevews[1],
					       PPSMC_DISPWAY_WATEWMAWK_WOW);
	if (wet)
		wetuwn wet;

	wet = wv770_convewt_powew_wevew_to_smc(wdev,
					       &state->high,
					       &smc_state->wevews[2],
					       PPSMC_DISPWAY_WATEWMAWK_HIGH);
	if (wet)
		wetuwn wet;

	smc_state->wevews[0].awbVawue = MC_CG_AWB_FWEQ_F1;
	smc_state->wevews[1].awbVawue = MC_CG_AWB_FWEQ_F2;
	smc_state->wevews[2].awbVawue = MC_CG_AWB_FWEQ_F3;

	smc_state->wevews[0].seqVawue = wv770_get_seq_vawue(wdev,
							    &state->wow);
	smc_state->wevews[1].seqVawue = wv770_get_seq_vawue(wdev,
							    &state->medium);
	smc_state->wevews[2].seqVawue = wv770_get_seq_vawue(wdev,
							    &state->high);

	wv770_popuwate_smc_sp(wdev, wadeon_state, smc_state);

	wetuwn wv770_popuwate_smc_t(wdev, wadeon_state, smc_state);

}

u32 wv770_cawcuwate_memowy_wefwesh_wate(stwuct wadeon_device *wdev,
					u32 engine_cwock)
{
	u32 dwam_wows;
	u32 dwam_wefwesh_wate;
	u32 mc_awb_wfsh_wate;
	u32 tmp;

	tmp = (WWEG32(MC_AWB_WAMCFG) & NOOFWOWS_MASK) >> NOOFWOWS_SHIFT;
	dwam_wows = 1 << (tmp + 10);
	tmp = WWEG32(MC_SEQ_MISC0) & 3;
	dwam_wefwesh_wate = 1 << (tmp + 3);
	mc_awb_wfsh_wate = ((engine_cwock * 10) * dwam_wefwesh_wate / dwam_wows - 32) / 64;

	wetuwn mc_awb_wfsh_wate;
}

static void wv770_pwogwam_memowy_timing_pawametews(stwuct wadeon_device *wdev,
						   stwuct wadeon_ps *wadeon_state)
{
	stwuct wv7xx_ps *state = wv770_get_ps(wadeon_state);
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 sqm_watio;
	u32 awb_wefwesh_wate;
	u32 high_cwock;

	if (state->high.scwk < (state->wow.scwk * 0xFF / 0x40))
		high_cwock = state->high.scwk;
	ewse
		high_cwock = (state->wow.scwk * 0xFF / 0x40);

	wadeon_atom_set_engine_dwam_timings(wdev, high_cwock,
					    state->high.mcwk);

	sqm_watio =
		STATE0(64 * high_cwock / pi->boot_scwk) |
		STATE1(64 * high_cwock / state->wow.scwk) |
		STATE2(64 * high_cwock / state->medium.scwk) |
		STATE3(64 * high_cwock / state->high.scwk);
	WWEG32(MC_AWB_SQM_WATIO, sqm_watio);

	awb_wefwesh_wate =
		POWEWMODE0(wv770_cawcuwate_memowy_wefwesh_wate(wdev, pi->boot_scwk)) |
		POWEWMODE1(wv770_cawcuwate_memowy_wefwesh_wate(wdev, state->wow.scwk)) |
		POWEWMODE2(wv770_cawcuwate_memowy_wefwesh_wate(wdev, state->medium.scwk)) |
		POWEWMODE3(wv770_cawcuwate_memowy_wefwesh_wate(wdev, state->high.scwk));
	WWEG32(MC_AWB_WFSH_WATE, awb_wefwesh_wate);
}

void wv770_enabwe_backbias(stwuct wadeon_device *wdev,
			   boow enabwe)
{
	if (enabwe)
		WWEG32_P(GENEWAW_PWWMGT, BACKBIAS_PAD_EN, ~BACKBIAS_PAD_EN);
	ewse
		WWEG32_P(GENEWAW_PWWMGT, 0, ~(BACKBIAS_VAWUE | BACKBIAS_PAD_EN));
}

static void wv770_enabwe_spwead_spectwum(stwuct wadeon_device *wdev,
					 boow enabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	if (enabwe) {
		if (pi->scwk_ss)
			WWEG32_P(GENEWAW_PWWMGT, DYN_SPWEAD_SPECTWUM_EN, ~DYN_SPWEAD_SPECTWUM_EN);

		if (pi->mcwk_ss) {
			if (wdev->famiwy == CHIP_WV740)
				wv740_enabwe_mcwk_spwead_spectwum(wdev, twue);
		}
	} ewse {
		WWEG32_P(CG_SPWW_SPWEAD_SPECTWUM, 0, ~SSEN);

		WWEG32_P(GENEWAW_PWWMGT, 0, ~DYN_SPWEAD_SPECTWUM_EN);

		WWEG32_P(CG_MPWW_SPWEAD_SPECTWUM, 0, ~SSEN);

		if (wdev->famiwy == CHIP_WV740)
			wv740_enabwe_mcwk_spwead_spectwum(wdev, fawse);
	}
}

static void wv770_pwogwam_mpww_timing_pawametews(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	if ((wdev->famiwy == CHIP_WV770) && !pi->mem_gddw5) {
		WWEG32(MPWW_TIME,
		       (MPWW_WOCK_TIME(W600_MPWWWOCKTIME_DFWT * pi->wef_div) |
			MPWW_WESET_TIME(W600_MPWWWESETTIME_DFWT)));
	}
}

void wv770_setup_bsp(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 xcwk = wadeon_get_xcwk(wdev);

	w600_cawcuwate_u_and_p(pi->asi,
			       xcwk,
			       16,
			       &pi->bsp,
			       &pi->bsu);

	w600_cawcuwate_u_and_p(pi->pasi,
			       xcwk,
			       16,
			       &pi->pbsp,
			       &pi->pbsu);

	pi->dsp = BSP(pi->bsp) | BSU(pi->bsu);
	pi->psp = BSP(pi->pbsp) | BSU(pi->pbsu);

	WWEG32(CG_BSP, pi->dsp);

}

void wv770_pwogwam_git(stwuct wadeon_device *wdev)
{
	WWEG32_P(CG_GIT, CG_GICST(W600_GICST_DFWT), ~CG_GICST_MASK);
}

void wv770_pwogwam_tp(stwuct wadeon_device *wdev)
{
	int i;
	enum w600_td td = W600_TD_DFWT;

	fow (i = 0; i < W600_PM_NUMBEW_OF_TC; i++)
		WWEG32(CG_FFCT_0 + (i * 4), (UTC_0(w600_utc[i]) | DTC_0(w600_dtc[i])));

	if (td == W600_TD_AUTO)
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~FIW_FOWCE_TWEND_SEW);
	ewse
		WWEG32_P(SCWK_PWWMGT_CNTW, FIW_FOWCE_TWEND_SEW, ~FIW_FOWCE_TWEND_SEW);
	if (td == W600_TD_UP)
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~FIW_TWEND_MODE);
	if (td == W600_TD_DOWN)
		WWEG32_P(SCWK_PWWMGT_CNTW, FIW_TWEND_MODE, ~FIW_TWEND_MODE);
}

void wv770_pwogwam_tpp(stwuct wadeon_device *wdev)
{
	WWEG32(CG_TPC, W600_TPC_DFWT);
}

void wv770_pwogwam_sstp(stwuct wadeon_device *wdev)
{
	WWEG32(CG_SSP, (SSTU(W600_SSTU_DFWT) | SST(W600_SST_DFWT)));
}

void wv770_pwogwam_engine_speed_pawametews(stwuct wadeon_device *wdev)
{
	WWEG32_P(SPWW_CNTW_MODE, SPWW_DIV_SYNC, ~SPWW_DIV_SYNC);
}

static void wv770_enabwe_dispway_gap(stwuct wadeon_device *wdev)
{
	u32 tmp = WWEG32(CG_DISPWAY_GAP_CNTW);

	tmp &= ~(DISP1_GAP_MCHG_MASK | DISP2_GAP_MCHG_MASK);
	tmp |= (DISP1_GAP_MCHG(W600_PM_DISPWAY_GAP_IGNOWE) |
		DISP2_GAP_MCHG(W600_PM_DISPWAY_GAP_IGNOWE));
	WWEG32(CG_DISPWAY_GAP_CNTW, tmp);
}

void wv770_pwogwam_vc(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	WWEG32(CG_FTV, pi->vwc);
}

void wv770_cweaw_vc(stwuct wadeon_device *wdev)
{
	WWEG32(CG_FTV, 0);
}

int wv770_upwoad_fiwmwawe(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	int wet;

	wv770_weset_smc(wdev);
	wv770_stop_smc_cwock(wdev);

	wet = wv770_woad_smc_ucode(wdev, pi->swam_end);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int wv770_popuwate_smc_acpi_state(stwuct wadeon_device *wdev,
					 WV770_SMC_STATETABWE *tabwe)
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
	u32 spww_func_cntw =
		pi->cwk_wegs.wv770.cg_spww_func_cntw;
	u32 spww_func_cntw_2 =
		pi->cwk_wegs.wv770.cg_spww_func_cntw_2;
	u32 spww_func_cntw_3 =
		pi->cwk_wegs.wv770.cg_spww_func_cntw_3;
	u32 mcwk_pwwmgt_cntw;
	u32 dww_cntw;

	tabwe->ACPIState = tabwe->initiawState;

	tabwe->ACPIState.fwags &= ~PPSMC_SWSTATE_FWAG_DC;

	if (pi->acpi_vddc) {
		wv770_popuwate_vddc_vawue(wdev, pi->acpi_vddc,
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
		wv770_popuwate_vddc_vawue(wdev, pi->min_vddc_in_tabwe,
					  &tabwe->ACPIState.wevews[0].vddc);
		tabwe->ACPIState.wevews[0].gen2PCIE = 0;
	}


	mpww_ad_func_cntw_2 |= BIAS_GEN_PDNB | WESET_EN;

	mpww_dq_func_cntw_2 |= BIAS_GEN_PDNB | WESET_EN;

	mcwk_pwwmgt_cntw = (MWDCKA0_WESET |
			    MWDCKA1_WESET |
			    MWDCKB0_WESET |
			    MWDCKB1_WESET |
			    MWDCKC0_WESET |
			    MWDCKC1_WESET |
			    MWDCKD0_WESET |
			    MWDCKD1_WESET);

	dww_cntw = 0xff000000;

	spww_func_cntw |= SPWW_WESET | SPWW_SWEEP | SPWW_BYPASS_EN;

	spww_func_cntw_2 &= ~SCWK_MUX_SEW_MASK;
	spww_func_cntw_2 |= SCWK_MUX_SEW(4);

	tabwe->ACPIState.wevews[0].mcwk.mcwk770.vMPWW_AD_FUNC_CNTW = cpu_to_be32(mpww_ad_func_cntw);
	tabwe->ACPIState.wevews[0].mcwk.mcwk770.vMPWW_AD_FUNC_CNTW_2 = cpu_to_be32(mpww_ad_func_cntw_2);
	tabwe->ACPIState.wevews[0].mcwk.mcwk770.vMPWW_DQ_FUNC_CNTW = cpu_to_be32(mpww_dq_func_cntw);
	tabwe->ACPIState.wevews[0].mcwk.mcwk770.vMPWW_DQ_FUNC_CNTW_2 = cpu_to_be32(mpww_dq_func_cntw_2);

	tabwe->ACPIState.wevews[0].mcwk.mcwk770.vMCWK_PWWMGT_CNTW = cpu_to_be32(mcwk_pwwmgt_cntw);
	tabwe->ACPIState.wevews[0].mcwk.mcwk770.vDWW_CNTW = cpu_to_be32(dww_cntw);

	tabwe->ACPIState.wevews[0].mcwk.mcwk770.mcwk_vawue = 0;

	tabwe->ACPIState.wevews[0].scwk.vCG_SPWW_FUNC_CNTW = cpu_to_be32(spww_func_cntw);
	tabwe->ACPIState.wevews[0].scwk.vCG_SPWW_FUNC_CNTW_2 = cpu_to_be32(spww_func_cntw_2);
	tabwe->ACPIState.wevews[0].scwk.vCG_SPWW_FUNC_CNTW_3 = cpu_to_be32(spww_func_cntw_3);

	tabwe->ACPIState.wevews[0].scwk.scwk_vawue = 0;

	wv770_popuwate_mvdd_vawue(wdev, 0, &tabwe->ACPIState.wevews[0].mvdd);

	tabwe->ACPIState.wevews[1] = tabwe->ACPIState.wevews[0];
	tabwe->ACPIState.wevews[2] = tabwe->ACPIState.wevews[0];

	wetuwn 0;
}

int wv770_popuwate_initiaw_mvdd_vawue(stwuct wadeon_device *wdev,
				      WV770_SMC_VOWTAGE_VAWUE *vowtage)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	if ((pi->s0_vid_wowew_smio_cntw & pi->mvdd_mask_wow) ==
	     (pi->mvdd_wow_smio[MVDD_WOW_INDEX] & pi->mvdd_mask_wow) ) {
		vowtage->index = MVDD_WOW_INDEX;
		vowtage->vawue = cpu_to_be16(MVDD_WOW_VAWUE);
	} ewse {
		vowtage->index = MVDD_HIGH_INDEX;
		vowtage->vawue = cpu_to_be16(MVDD_HIGH_VAWUE);
	}

	wetuwn 0;
}

static int wv770_popuwate_smc_initiaw_state(stwuct wadeon_device *wdev,
					    stwuct wadeon_ps *wadeon_state,
					    WV770_SMC_STATETABWE *tabwe)
{
	stwuct wv7xx_ps *initiaw_state = wv770_get_ps(wadeon_state);
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
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

	tabwe->initiawState.wevews[0].seqVawue =
		wv770_get_seq_vawue(wdev, &initiaw_state->wow);

	wv770_popuwate_vddc_vawue(wdev,
				  initiaw_state->wow.vddc,
				  &tabwe->initiawState.wevews[0].vddc);
	wv770_popuwate_initiaw_mvdd_vawue(wdev,
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

	if (wdev->famiwy == CHIP_WV740) {
		if (pi->mem_gddw5) {
			if (initiaw_state->wow.mcwk <= pi->mcwk_stwobe_mode_thweshowd)
				tabwe->initiawState.wevews[0].stwobeMode =
					wv740_get_mcwk_fwequency_watio(initiaw_state->wow.mcwk) | 0x10;
			ewse
				tabwe->initiawState.wevews[0].stwobeMode = 0;

			if (initiaw_state->wow.mcwk >= pi->mcwk_edc_enabwe_thweshowd)
				tabwe->initiawState.wevews[0].mcFwags = SMC_MC_EDC_WD_FWAG | SMC_MC_EDC_WW_FWAG;
			ewse
				tabwe->initiawState.wevews[0].mcFwags =  0;
		}
	}

	tabwe->initiawState.wevews[1] = tabwe->initiawState.wevews[0];
	tabwe->initiawState.wevews[2] = tabwe->initiawState.wevews[0];

	tabwe->initiawState.fwags |= PPSMC_SWSTATE_FWAG_DC;

	wetuwn 0;
}

static int wv770_popuwate_smc_vddc_tabwe(stwuct wadeon_device *wdev,
					 WV770_SMC_STATETABWE *tabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	int i;

	fow (i = 0; i < pi->vawid_vddc_entwies; i++) {
		tabwe->highSMIO[pi->vddc_tabwe[i].vddc_index] =
			pi->vddc_tabwe[i].high_smio;
		tabwe->wowSMIO[pi->vddc_tabwe[i].vddc_index] =
			cpu_to_be32(pi->vddc_tabwe[i].wow_smio);
	}

	tabwe->vowtageMaskTabwe.highMask[WV770_SMC_VOWTAGEMASK_VDDC] = 0;
	tabwe->vowtageMaskTabwe.wowMask[WV770_SMC_VOWTAGEMASK_VDDC] =
		cpu_to_be32(pi->vddc_mask_wow);

	fow (i = 0;
	     ((i < pi->vawid_vddc_entwies) &&
	      (pi->max_vddc_in_tabwe >
	       pi->vddc_tabwe[i].vddc));
	     i++);

	tabwe->maxVDDCIndexInPPTabwe =
		pi->vddc_tabwe[i].vddc_index;

	wetuwn 0;
}

static int wv770_popuwate_smc_mvdd_tabwe(stwuct wadeon_device *wdev,
					 WV770_SMC_STATETABWE *tabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	if (pi->mvdd_contwow) {
		tabwe->wowSMIO[MVDD_HIGH_INDEX] |=
			cpu_to_be32(pi->mvdd_wow_smio[MVDD_HIGH_INDEX]);
		tabwe->wowSMIO[MVDD_WOW_INDEX] |=
			cpu_to_be32(pi->mvdd_wow_smio[MVDD_WOW_INDEX]);

		tabwe->vowtageMaskTabwe.highMask[WV770_SMC_VOWTAGEMASK_MVDD] = 0;
		tabwe->vowtageMaskTabwe.wowMask[WV770_SMC_VOWTAGEMASK_MVDD] =
			cpu_to_be32(pi->mvdd_mask_wow);
	}

	wetuwn 0;
}

static int wv770_init_smc_tabwe(stwuct wadeon_device *wdev,
				stwuct wadeon_ps *wadeon_boot_state)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct wv7xx_ps *boot_state = wv770_get_ps(wadeon_boot_state);
	WV770_SMC_STATETABWE *tabwe = &pi->smc_statetabwe;
	int wet;

	memset(tabwe, 0, sizeof(WV770_SMC_STATETABWE));

	pi->boot_scwk = boot_state->wow.scwk;

	wv770_popuwate_smc_vddc_tabwe(wdev, tabwe);
	wv770_popuwate_smc_mvdd_tabwe(wdev, tabwe);

	switch (wdev->pm.int_thewmaw_type) {
	case THEWMAW_TYPE_WV770:
	case THEWMAW_TYPE_ADT7473_WITH_INTEWNAW:
		tabwe->thewmawPwotectType = PPSMC_THEWMAW_PWOTECT_TYPE_INTEWNAW;
		bweak;
	case THEWMAW_TYPE_NONE:
		tabwe->thewmawPwotectType = PPSMC_THEWMAW_PWOTECT_TYPE_NONE;
		bweak;
	case THEWMAW_TYPE_EXTEWNAW_GPIO:
	defauwt:
		tabwe->thewmawPwotectType = PPSMC_THEWMAW_PWOTECT_TYPE_EXTEWNAW;
		bweak;
	}

	if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_HAWDWAWEDC) {
		tabwe->systemFwags |= PPSMC_SYSTEMFWAG_GPIO_DC;

		if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_DONT_WAIT_FOW_VBWANK_ON_AWEWT)
			tabwe->extwaFwags |= PPSMC_EXTWAFWAGS_AC2DC_DONT_WAIT_FOW_VBWANK;

		if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_GOTO_BOOT_ON_AWEWT)
			tabwe->extwaFwags |= PPSMC_EXTWAFWAGS_AC2DC_ACTION_GOTOINITIAWSTATE;
	}

	if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_STEPVDDC)
		tabwe->systemFwags |= PPSMC_SYSTEMFWAG_STEPVDDC;

	if (pi->mem_gddw5)
		tabwe->systemFwags |= PPSMC_SYSTEMFWAG_GDDW5;

	if ((wdev->famiwy == CHIP_WV730) || (wdev->famiwy == CHIP_WV710))
		wet = wv730_popuwate_smc_initiaw_state(wdev, wadeon_boot_state, tabwe);
	ewse
		wet = wv770_popuwate_smc_initiaw_state(wdev, wadeon_boot_state, tabwe);
	if (wet)
		wetuwn wet;

	if (wdev->famiwy == CHIP_WV740)
		wet = wv740_popuwate_smc_acpi_state(wdev, tabwe);
	ewse if ((wdev->famiwy == CHIP_WV730) || (wdev->famiwy == CHIP_WV710))
		wet = wv730_popuwate_smc_acpi_state(wdev, tabwe);
	ewse
		wet = wv770_popuwate_smc_acpi_state(wdev, tabwe);
	if (wet)
		wetuwn wet;

	tabwe->dwivewState = tabwe->initiawState;

	wetuwn wv770_copy_bytes_to_smc(wdev,
				       pi->state_tabwe_stawt,
				       (const u8 *)tabwe,
				       sizeof(WV770_SMC_STATETABWE),
				       pi->swam_end);
}

static int wv770_constwuct_vddc_tabwe(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u16 min, max, step;
	u32 steps = 0;
	u8 vddc_index = 0;
	u32 i;

	wadeon_atom_get_min_vowtage(wdev, SET_VOWTAGE_TYPE_ASIC_VDDC, &min);
	wadeon_atom_get_max_vowtage(wdev, SET_VOWTAGE_TYPE_ASIC_VDDC, &max);
	wadeon_atom_get_vowtage_step(wdev, SET_VOWTAGE_TYPE_ASIC_VDDC, &step);

	steps = (max - min) / step + 1;

	if (steps > MAX_NO_VWEG_STEPS)
		wetuwn -EINVAW;

	fow (i = 0; i < steps; i++) {
		u32 gpio_pins, gpio_mask;

		pi->vddc_tabwe[i].vddc = (u16)(min + i * step);
		wadeon_atom_get_vowtage_gpio_settings(wdev,
						      pi->vddc_tabwe[i].vddc,
						      SET_VOWTAGE_TYPE_ASIC_VDDC,
						      &gpio_pins, &gpio_mask);
		pi->vddc_tabwe[i].wow_smio = gpio_pins & gpio_mask;
		pi->vddc_tabwe[i].high_smio = 0;
		pi->vddc_mask_wow = gpio_mask;
		if (i > 0) {
			if ((pi->vddc_tabwe[i].wow_smio !=
			     pi->vddc_tabwe[i - 1].wow_smio ) ||
			     (pi->vddc_tabwe[i].high_smio !=
			      pi->vddc_tabwe[i - 1].high_smio))
				vddc_index++;
		}
		pi->vddc_tabwe[i].vddc_index = vddc_index;
	}

	pi->vawid_vddc_entwies = (u8)steps;

	wetuwn 0;
}

static u32 wv770_get_mcwk_spwit_point(stwuct atom_memowy_info *memowy_info)
{
	if (memowy_info->mem_type == MEM_TYPE_GDDW3)
		wetuwn 30000;

	wetuwn 0;
}

static int wv770_get_mvdd_pin_configuwation(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 gpio_pins, gpio_mask;

	wadeon_atom_get_vowtage_gpio_settings(wdev,
					      MVDD_HIGH_VAWUE, SET_VOWTAGE_TYPE_ASIC_MVDDC,
					      &gpio_pins, &gpio_mask);
	pi->mvdd_mask_wow = gpio_mask;
	pi->mvdd_wow_smio[MVDD_HIGH_INDEX] =
		gpio_pins & gpio_mask;

	wadeon_atom_get_vowtage_gpio_settings(wdev,
					      MVDD_WOW_VAWUE, SET_VOWTAGE_TYPE_ASIC_MVDDC,
					      &gpio_pins, &gpio_mask);
	pi->mvdd_wow_smio[MVDD_WOW_INDEX] =
		gpio_pins & gpio_mask;

	wetuwn 0;
}

u8 wv770_get_memowy_moduwe_index(stwuct wadeon_device *wdev)
{
	wetuwn (u8) ((WWEG32(BIOS_SCWATCH_4) >> 16) & 0xff);
}

static int wv770_get_mvdd_configuwation(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u8 memowy_moduwe_index;
	stwuct atom_memowy_info memowy_info;

	memowy_moduwe_index = wv770_get_memowy_moduwe_index(wdev);

	if (wadeon_atom_get_memowy_info(wdev, memowy_moduwe_index, &memowy_info)) {
		pi->mvdd_contwow = fawse;
		wetuwn 0;
	}

	pi->mvdd_spwit_fwequency =
		wv770_get_mcwk_spwit_point(&memowy_info);

	if (pi->mvdd_spwit_fwequency == 0) {
		pi->mvdd_contwow = fawse;
		wetuwn 0;
	}

	wetuwn wv770_get_mvdd_pin_configuwation(wdev);
}

void wv770_enabwe_vowtage_contwow(stwuct wadeon_device *wdev,
				  boow enabwe)
{
	if (enabwe)
		WWEG32_P(GENEWAW_PWWMGT, VOWT_PWWMGT_EN, ~VOWT_PWWMGT_EN);
	ewse
		WWEG32_P(GENEWAW_PWWMGT, 0, ~VOWT_PWWMGT_EN);
}

static void wv770_pwogwam_dispway_gap(stwuct wadeon_device *wdev)
{
	u32 tmp = WWEG32(CG_DISPWAY_GAP_CNTW);

	tmp &= ~(DISP1_GAP_MCHG_MASK | DISP2_GAP_MCHG_MASK);
	if (wdev->pm.dpm.new_active_cwtcs & 1) {
		tmp |= DISP1_GAP_MCHG(W600_PM_DISPWAY_GAP_VBWANK);
		tmp |= DISP2_GAP_MCHG(W600_PM_DISPWAY_GAP_IGNOWE);
	} ewse if (wdev->pm.dpm.new_active_cwtcs & 2) {
		tmp |= DISP1_GAP_MCHG(W600_PM_DISPWAY_GAP_IGNOWE);
		tmp |= DISP2_GAP_MCHG(W600_PM_DISPWAY_GAP_VBWANK);
	} ewse {
		tmp |= DISP1_GAP_MCHG(W600_PM_DISPWAY_GAP_IGNOWE);
		tmp |= DISP2_GAP_MCHG(W600_PM_DISPWAY_GAP_IGNOWE);
	}
	WWEG32(CG_DISPWAY_GAP_CNTW, tmp);
}

static void wv770_enabwe_dynamic_pcie_gen2(stwuct wadeon_device *wdev,
					   boow enabwe)
{
	wv770_enabwe_bif_dynamic_pcie_gen2(wdev, enabwe);

	if (enabwe)
		WWEG32_P(GENEWAW_PWWMGT, ENABWE_GEN2PCIE, ~ENABWE_GEN2PCIE);
	ewse
		WWEG32_P(GENEWAW_PWWMGT, 0, ~ENABWE_GEN2PCIE);
}

static void w7xx_pwogwam_memowy_timing_pawametews(stwuct wadeon_device *wdev,
						  stwuct wadeon_ps *wadeon_new_state)
{
	if ((wdev->famiwy == CHIP_WV730) ||
	    (wdev->famiwy == CHIP_WV710) ||
	    (wdev->famiwy == CHIP_WV740))
		wv730_pwogwam_memowy_timing_pawametews(wdev, wadeon_new_state);
	ewse
		wv770_pwogwam_memowy_timing_pawametews(wdev, wadeon_new_state);
}

static int wv770_upwoad_sw_state(stwuct wadeon_device *wdev,
				 stwuct wadeon_ps *wadeon_new_state)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u16 addwess = pi->state_tabwe_stawt +
		offsetof(WV770_SMC_STATETABWE, dwivewState);
	WV770_SMC_SWSTATE state = { 0 };
	int wet;

	wet = wv770_convewt_powew_state_to_smc(wdev, wadeon_new_state, &state);
	if (wet)
		wetuwn wet;

	wetuwn wv770_copy_bytes_to_smc(wdev, addwess, (const u8 *)&state,
				       sizeof(WV770_SMC_SWSTATE),
				       pi->swam_end);
}

int wv770_hawt_smc(stwuct wadeon_device *wdev)
{
	if (wv770_send_msg_to_smc(wdev, PPSMC_MSG_Hawt) != PPSMC_Wesuwt_OK)
		wetuwn -EINVAW;

	if (wv770_wait_fow_smc_inactive(wdev) != PPSMC_Wesuwt_OK)
		wetuwn -EINVAW;

	wetuwn 0;
}

int wv770_wesume_smc(stwuct wadeon_device *wdev)
{
	if (wv770_send_msg_to_smc(wdev, PPSMC_MSG_Wesume) != PPSMC_Wesuwt_OK)
		wetuwn -EINVAW;
	wetuwn 0;
}

int wv770_set_sw_state(stwuct wadeon_device *wdev)
{
	if (wv770_send_msg_to_smc(wdev, PPSMC_MSG_SwitchToSwState) != PPSMC_Wesuwt_OK)
		DWM_DEBUG("wv770_set_sw_state faiwed\n");
	wetuwn 0;
}

int wv770_set_boot_state(stwuct wadeon_device *wdev)
{
	if (wv770_send_msg_to_smc(wdev, PPSMC_MSG_SwitchToInitiawState) != PPSMC_Wesuwt_OK)
		wetuwn -EINVAW;
	wetuwn 0;
}

void wv770_set_uvd_cwock_befowe_set_eng_cwock(stwuct wadeon_device *wdev,
					      stwuct wadeon_ps *new_ps,
					      stwuct wadeon_ps *owd_ps)
{
	stwuct wv7xx_ps *new_state = wv770_get_ps(new_ps);
	stwuct wv7xx_ps *cuwwent_state = wv770_get_ps(owd_ps);

	if ((new_ps->vcwk == owd_ps->vcwk) &&
	    (new_ps->dcwk == owd_ps->dcwk))
		wetuwn;

	if (new_state->high.scwk >= cuwwent_state->high.scwk)
		wetuwn;

	wadeon_set_uvd_cwocks(wdev, new_ps->vcwk, new_ps->dcwk);
}

void wv770_set_uvd_cwock_aftew_set_eng_cwock(stwuct wadeon_device *wdev,
					     stwuct wadeon_ps *new_ps,
					     stwuct wadeon_ps *owd_ps)
{
	stwuct wv7xx_ps *new_state = wv770_get_ps(new_ps);
	stwuct wv7xx_ps *cuwwent_state = wv770_get_ps(owd_ps);

	if ((new_ps->vcwk == owd_ps->vcwk) &&
	    (new_ps->dcwk == owd_ps->dcwk))
		wetuwn;

	if (new_state->high.scwk < cuwwent_state->high.scwk)
		wetuwn;

	wadeon_set_uvd_cwocks(wdev, new_ps->vcwk, new_ps->dcwk);
}

int wv770_westwict_pewfowmance_wevews_befowe_switch(stwuct wadeon_device *wdev)
{
	if (wv770_send_msg_to_smc(wdev, (PPSMC_Msg)(PPSMC_MSG_NoFowcedWevew)) != PPSMC_Wesuwt_OK)
		wetuwn -EINVAW;

	if (wv770_send_msg_to_smc(wdev, (PPSMC_Msg)(PPSMC_MSG_TwoWevewsDisabwed)) != PPSMC_Wesuwt_OK)
		wetuwn -EINVAW;

	wetuwn 0;
}

int wv770_dpm_fowce_pewfowmance_wevew(stwuct wadeon_device *wdev,
				      enum wadeon_dpm_fowced_wevew wevew)
{
	PPSMC_Msg msg;

	if (wevew == WADEON_DPM_FOWCED_WEVEW_HIGH) {
		if (wv770_send_msg_to_smc(wdev, PPSMC_MSG_ZewoWevewsDisabwed) != PPSMC_Wesuwt_OK)
			wetuwn -EINVAW;
		msg = PPSMC_MSG_FowceHigh;
	} ewse if (wevew == WADEON_DPM_FOWCED_WEVEW_WOW) {
		if (wv770_send_msg_to_smc(wdev, PPSMC_MSG_NoFowcedWevew) != PPSMC_Wesuwt_OK)
			wetuwn -EINVAW;
		msg = (PPSMC_Msg)(PPSMC_MSG_TwoWevewsDisabwed);
	} ewse {
		if (wv770_send_msg_to_smc(wdev, PPSMC_MSG_NoFowcedWevew) != PPSMC_Wesuwt_OK)
			wetuwn -EINVAW;
		msg = (PPSMC_Msg)(PPSMC_MSG_ZewoWevewsDisabwed);
	}

	if (wv770_send_msg_to_smc(wdev, msg) != PPSMC_Wesuwt_OK)
		wetuwn -EINVAW;

	wdev->pm.dpm.fowced_wevew = wevew;

	wetuwn 0;
}

void w7xx_stawt_smc(stwuct wadeon_device *wdev)
{
	wv770_stawt_smc(wdev);
	wv770_stawt_smc_cwock(wdev);
}


void w7xx_stop_smc(stwuct wadeon_device *wdev)
{
	wv770_weset_smc(wdev);
	wv770_stop_smc_cwock(wdev);
}

static void wv770_wead_cwock_wegistews(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	pi->cwk_wegs.wv770.cg_spww_func_cntw =
		WWEG32(CG_SPWW_FUNC_CNTW);
	pi->cwk_wegs.wv770.cg_spww_func_cntw_2 =
		WWEG32(CG_SPWW_FUNC_CNTW_2);
	pi->cwk_wegs.wv770.cg_spww_func_cntw_3 =
		WWEG32(CG_SPWW_FUNC_CNTW_3);
	pi->cwk_wegs.wv770.cg_spww_spwead_spectwum =
		WWEG32(CG_SPWW_SPWEAD_SPECTWUM);
	pi->cwk_wegs.wv770.cg_spww_spwead_spectwum_2 =
		WWEG32(CG_SPWW_SPWEAD_SPECTWUM_2);
	pi->cwk_wegs.wv770.mpww_ad_func_cntw =
		WWEG32(MPWW_AD_FUNC_CNTW);
	pi->cwk_wegs.wv770.mpww_ad_func_cntw_2 =
		WWEG32(MPWW_AD_FUNC_CNTW_2);
	pi->cwk_wegs.wv770.mpww_dq_func_cntw =
		WWEG32(MPWW_DQ_FUNC_CNTW);
	pi->cwk_wegs.wv770.mpww_dq_func_cntw_2 =
		WWEG32(MPWW_DQ_FUNC_CNTW_2);
	pi->cwk_wegs.wv770.mcwk_pwwmgt_cntw =
		WWEG32(MCWK_PWWMGT_CNTW);
	pi->cwk_wegs.wv770.dww_cntw = WWEG32(DWW_CNTW);
}

static void w7xx_wead_cwock_wegistews(stwuct wadeon_device *wdev)
{
	if (wdev->famiwy == CHIP_WV740)
		wv740_wead_cwock_wegistews(wdev);
	ewse if ((wdev->famiwy == CHIP_WV730) || (wdev->famiwy == CHIP_WV710))
		wv730_wead_cwock_wegistews(wdev);
	ewse
		wv770_wead_cwock_wegistews(wdev);
}

void wv770_wead_vowtage_smio_wegistews(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	pi->s0_vid_wowew_smio_cntw =
		WWEG32(S0_VID_WOWEW_SMIO_CNTW);
}

void wv770_weset_smio_status(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 sw_smio_index, vid_smio_cntw;

	sw_smio_index =
		(WWEG32(GENEWAW_PWWMGT) & SW_SMIO_INDEX_MASK) >> SW_SMIO_INDEX_SHIFT;
	switch (sw_smio_index) {
	case 3:
		vid_smio_cntw = WWEG32(S3_VID_WOWEW_SMIO_CNTW);
		bweak;
	case 2:
		vid_smio_cntw = WWEG32(S2_VID_WOWEW_SMIO_CNTW);
		bweak;
	case 1:
		vid_smio_cntw = WWEG32(S1_VID_WOWEW_SMIO_CNTW);
		bweak;
	case 0:
		wetuwn;
	defauwt:
		vid_smio_cntw = pi->s0_vid_wowew_smio_cntw;
		bweak;
	}

	WWEG32(S0_VID_WOWEW_SMIO_CNTW, vid_smio_cntw);
	WWEG32_P(GENEWAW_PWWMGT, SW_SMIO_INDEX(0), ~SW_SMIO_INDEX_MASK);
}

void wv770_get_memowy_type(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 tmp;

	tmp = WWEG32(MC_SEQ_MISC0);

	if (((tmp & MC_SEQ_MISC0_GDDW5_MASK) >> MC_SEQ_MISC0_GDDW5_SHIFT) ==
	    MC_SEQ_MISC0_GDDW5_VAWUE)
		pi->mem_gddw5 = twue;
	ewse
		pi->mem_gddw5 = fawse;

}

void wv770_get_pcie_gen2_status(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 tmp;

	tmp = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);

	if ((tmp & WC_OTHEW_SIDE_EVEW_SENT_GEN2) &&
	    (tmp & WC_OTHEW_SIDE_SUPPOWTS_GEN2))
		pi->pcie_gen2 = twue;
	ewse
		pi->pcie_gen2 = fawse;

	if (pi->pcie_gen2) {
		if (tmp & WC_CUWWENT_DATA_WATE)
			pi->boot_in_gen2 = twue;
		ewse
			pi->boot_in_gen2 = fawse;
	} ewse
		pi->boot_in_gen2 = fawse;
}

#if 0
static int wv770_entew_uwp_state(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	if (pi->gfx_cwock_gating) {
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~DYN_GFX_CWK_OFF_EN);
		WWEG32_P(SCWK_PWWMGT_CNTW, GFX_CWK_FOWCE_ON, ~GFX_CWK_FOWCE_ON);
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~GFX_CWK_FOWCE_ON);
		WWEG32(GB_TIWING_CONFIG);
	}

	WWEG32_P(SMC_MSG, HOST_SMC_MSG(PPSMC_MSG_SwitchToMinimumPowew),
		 ~HOST_SMC_MSG_MASK);

	udeway(7000);

	wetuwn 0;
}

static int wv770_exit_uwp_state(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	int i;

	WWEG32_P(SMC_MSG, HOST_SMC_MSG(PPSMC_MSG_WesumeFwomMinimumPowew),
		 ~HOST_SMC_MSG_MASK);

	udeway(7000);

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (((WWEG32(SMC_MSG) & HOST_SMC_WESP_MASK) >> HOST_SMC_WESP_SHIFT) == 1)
			bweak;
		udeway(1000);
	}

	if (pi->gfx_cwock_gating)
		WWEG32_P(SCWK_PWWMGT_CNTW, DYN_GFX_CWK_OFF_EN, ~DYN_GFX_CWK_OFF_EN);

	wetuwn 0;
}
#endif

static void wv770_get_mcwk_odt_thweshowd(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u8 memowy_moduwe_index;
	stwuct atom_memowy_info memowy_info;

	pi->mcwk_odt_thweshowd = 0;

	if ((wdev->famiwy == CHIP_WV730) || (wdev->famiwy == CHIP_WV710)) {
		memowy_moduwe_index = wv770_get_memowy_moduwe_index(wdev);

		if (wadeon_atom_get_memowy_info(wdev, memowy_moduwe_index, &memowy_info))
			wetuwn;

		if (memowy_info.mem_type == MEM_TYPE_DDW2 ||
		    memowy_info.mem_type == MEM_TYPE_DDW3)
			pi->mcwk_odt_thweshowd = 30000;
	}
}

void wv770_get_max_vddc(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u16 vddc;

	if (wadeon_atom_get_max_vddc(wdev, 0, 0, &vddc))
		pi->max_vddc = 0;
	ewse
		pi->max_vddc = vddc;
}

void wv770_pwogwam_wesponse_times(stwuct wadeon_device *wdev)
{
	u32 vowtage_wesponse_time, backbias_wesponse_time;
	u32 acpi_deway_time, vbi_time_out;
	u32 vddc_dwy, bb_dwy, acpi_dwy, vbi_dwy;
	u32 wefewence_cwock;

	vowtage_wesponse_time = (u32)wdev->pm.dpm.vowtage_wesponse_time;
	backbias_wesponse_time = (u32)wdev->pm.dpm.backbias_wesponse_time;

	if (vowtage_wesponse_time == 0)
		vowtage_wesponse_time = 1000;

	if (backbias_wesponse_time == 0)
		backbias_wesponse_time = 1000;

	acpi_deway_time = 15000;
	vbi_time_out = 100000;

	wefewence_cwock = wadeon_get_xcwk(wdev);

	vddc_dwy = (vowtage_wesponse_time  * wefewence_cwock) / 1600;
	bb_dwy = (backbias_wesponse_time * wefewence_cwock) / 1600;
	acpi_dwy = (acpi_deway_time * wefewence_cwock) / 1600;
	vbi_dwy = (vbi_time_out * wefewence_cwock) / 1600;

	wv770_wwite_smc_soft_wegistew(wdev,
				      WV770_SMC_SOFT_WEGISTEW_deway_vweg, vddc_dwy);
	wv770_wwite_smc_soft_wegistew(wdev,
				      WV770_SMC_SOFT_WEGISTEW_deway_bbias, bb_dwy);
	wv770_wwite_smc_soft_wegistew(wdev,
				      WV770_SMC_SOFT_WEGISTEW_deway_acpi, acpi_dwy);
	wv770_wwite_smc_soft_wegistew(wdev,
				      WV770_SMC_SOFT_WEGISTEW_mcwk_chg_timeout, vbi_dwy);
#if 0
	/* XXX wook up hw wevision */
	if (WEKIVA_A21)
		wv770_wwite_smc_soft_wegistew(wdev,
					      WV770_SMC_SOFT_WEGISTEW_baby_step_timew,
					      0x10);
#endif
}

static void wv770_pwogwam_dcodt_befowe_state_switch(stwuct wadeon_device *wdev,
						    stwuct wadeon_ps *wadeon_new_state,
						    stwuct wadeon_ps *wadeon_cuwwent_state)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct wv7xx_ps *new_state = wv770_get_ps(wadeon_new_state);
	stwuct wv7xx_ps *cuwwent_state = wv770_get_ps(wadeon_cuwwent_state);
	boow cuwwent_use_dc = fawse;
	boow new_use_dc = fawse;

	if (pi->mcwk_odt_thweshowd == 0)
		wetuwn;

	if (cuwwent_state->high.mcwk <= pi->mcwk_odt_thweshowd)
		cuwwent_use_dc = twue;

	if (new_state->high.mcwk <= pi->mcwk_odt_thweshowd)
		new_use_dc = twue;

	if (cuwwent_use_dc == new_use_dc)
		wetuwn;

	if (!cuwwent_use_dc && new_use_dc)
		wetuwn;

	if ((wdev->famiwy == CHIP_WV730) || (wdev->famiwy == CHIP_WV710))
		wv730_pwogwam_dcodt(wdev, new_use_dc);
}

static void wv770_pwogwam_dcodt_aftew_state_switch(stwuct wadeon_device *wdev,
						   stwuct wadeon_ps *wadeon_new_state,
						   stwuct wadeon_ps *wadeon_cuwwent_state)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct wv7xx_ps *new_state = wv770_get_ps(wadeon_new_state);
	stwuct wv7xx_ps *cuwwent_state = wv770_get_ps(wadeon_cuwwent_state);
	boow cuwwent_use_dc = fawse;
	boow new_use_dc = fawse;

	if (pi->mcwk_odt_thweshowd == 0)
		wetuwn;

	if (cuwwent_state->high.mcwk <= pi->mcwk_odt_thweshowd)
		cuwwent_use_dc = twue;

	if (new_state->high.mcwk <= pi->mcwk_odt_thweshowd)
		new_use_dc = twue;

	if (cuwwent_use_dc == new_use_dc)
		wetuwn;

	if (cuwwent_use_dc && !new_use_dc)
		wetuwn;

	if ((wdev->famiwy == CHIP_WV730) || (wdev->famiwy == CHIP_WV710))
		wv730_pwogwam_dcodt(wdev, new_use_dc);
}

static void wv770_wetwieve_odt_vawues(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	if (pi->mcwk_odt_thweshowd == 0)
		wetuwn;

	if ((wdev->famiwy == CHIP_WV730) || (wdev->famiwy == CHIP_WV710))
		wv730_get_odt_vawues(wdev);
}

static void wv770_set_dpm_event_souwces(stwuct wadeon_device *wdev, u32 souwces)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	boow want_thewmaw_pwotection;
	enum wadeon_dpm_event_swc dpm_event_swc;

	switch (souwces) {
	case 0:
	defauwt:
		want_thewmaw_pwotection = fawse;
		bweak;
	case (1 << WADEON_DPM_AUTO_THWOTTWE_SWC_THEWMAW):
		want_thewmaw_pwotection = twue;
		dpm_event_swc = WADEON_DPM_EVENT_SWC_DIGITAW;
		bweak;

	case (1 << WADEON_DPM_AUTO_THWOTTWE_SWC_EXTEWNAW):
		want_thewmaw_pwotection = twue;
		dpm_event_swc = WADEON_DPM_EVENT_SWC_EXTEWNAW;
		bweak;

	case ((1 << WADEON_DPM_AUTO_THWOTTWE_SWC_EXTEWNAW) |
	      (1 << WADEON_DPM_AUTO_THWOTTWE_SWC_THEWMAW)):
		want_thewmaw_pwotection = twue;
		dpm_event_swc = WADEON_DPM_EVENT_SWC_DIGIAW_OW_EXTEWNAW;
		bweak;
	}

	if (want_thewmaw_pwotection) {
		WWEG32_P(CG_THEWMAW_CTWW, DPM_EVENT_SWC(dpm_event_swc), ~DPM_EVENT_SWC_MASK);
		if (pi->thewmaw_pwotection)
			WWEG32_P(GENEWAW_PWWMGT, 0, ~THEWMAW_PWOTECTION_DIS);
	} ewse {
		WWEG32_P(GENEWAW_PWWMGT, THEWMAW_PWOTECTION_DIS, ~THEWMAW_PWOTECTION_DIS);
	}
}

void wv770_enabwe_auto_thwottwe_souwce(stwuct wadeon_device *wdev,
				       enum wadeon_dpm_auto_thwottwe_swc souwce,
				       boow enabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	if (enabwe) {
		if (!(pi->active_auto_thwottwe_souwces & (1 << souwce))) {
			pi->active_auto_thwottwe_souwces |= 1 << souwce;
			wv770_set_dpm_event_souwces(wdev, pi->active_auto_thwottwe_souwces);
		}
	} ewse {
		if (pi->active_auto_thwottwe_souwces & (1 << souwce)) {
			pi->active_auto_thwottwe_souwces &= ~(1 << souwce);
			wv770_set_dpm_event_souwces(wdev, pi->active_auto_thwottwe_souwces);
		}
	}
}

static int wv770_set_thewmaw_tempewatuwe_wange(stwuct wadeon_device *wdev,
					       int min_temp, int max_temp)
{
	int wow_temp = 0 * 1000;
	int high_temp = 255 * 1000;

	if (wow_temp < min_temp)
		wow_temp = min_temp;
	if (high_temp > max_temp)
		high_temp = max_temp;
	if (high_temp < wow_temp) {
		DWM_EWWOW("invawid thewmaw wange: %d - %d\n", wow_temp, high_temp);
		wetuwn -EINVAW;
	}

	WWEG32_P(CG_THEWMAW_INT, DIG_THEWM_INTH(high_temp / 1000), ~DIG_THEWM_INTH_MASK);
	WWEG32_P(CG_THEWMAW_INT, DIG_THEWM_INTW(wow_temp / 1000), ~DIG_THEWM_INTW_MASK);
	WWEG32_P(CG_THEWMAW_CTWW, DIG_THEWM_DPM(high_temp / 1000), ~DIG_THEWM_DPM_MASK);

	wdev->pm.dpm.thewmaw.min_temp = wow_temp;
	wdev->pm.dpm.thewmaw.max_temp = high_temp;

	wetuwn 0;
}

int wv770_dpm_enabwe(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct wadeon_ps *boot_ps = wdev->pm.dpm.boot_ps;
	int wet;

	if (pi->gfx_cwock_gating)
		wv770_westowe_cgcg(wdev);

	if (wv770_dpm_enabwed(wdev))
		wetuwn -EINVAW;

	if (pi->vowtage_contwow) {
		wv770_enabwe_vowtage_contwow(wdev, twue);
		wet = wv770_constwuct_vddc_tabwe(wdev);
		if (wet) {
			DWM_EWWOW("wv770_constwuct_vddc_tabwe faiwed\n");
			wetuwn wet;
		}
	}

	if (pi->dcodt)
		wv770_wetwieve_odt_vawues(wdev);

	if (pi->mvdd_contwow) {
		wet = wv770_get_mvdd_configuwation(wdev);
		if (wet) {
			DWM_EWWOW("wv770_get_mvdd_configuwation faiwed\n");
			wetuwn wet;
		}
	}

	if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_BACKBIAS)
		wv770_enabwe_backbias(wdev, twue);

	wv770_enabwe_spwead_spectwum(wdev, twue);

	if (pi->thewmaw_pwotection)
		wv770_enabwe_thewmaw_pwotection(wdev, twue);

	wv770_pwogwam_mpww_timing_pawametews(wdev);
	wv770_setup_bsp(wdev);
	wv770_pwogwam_git(wdev);
	wv770_pwogwam_tp(wdev);
	wv770_pwogwam_tpp(wdev);
	wv770_pwogwam_sstp(wdev);
	wv770_pwogwam_engine_speed_pawametews(wdev);
	wv770_enabwe_dispway_gap(wdev);
	wv770_pwogwam_vc(wdev);

	if (pi->dynamic_pcie_gen2)
		wv770_enabwe_dynamic_pcie_gen2(wdev, twue);

	wet = wv770_upwoad_fiwmwawe(wdev);
	if (wet) {
		DWM_EWWOW("wv770_upwoad_fiwmwawe faiwed\n");
		wetuwn wet;
	}
	wet = wv770_init_smc_tabwe(wdev, boot_ps);
	if (wet) {
		DWM_EWWOW("wv770_init_smc_tabwe faiwed\n");
		wetuwn wet;
	}

	wv770_pwogwam_wesponse_times(wdev);
	w7xx_stawt_smc(wdev);

	if ((wdev->famiwy == CHIP_WV730) || (wdev->famiwy == CHIP_WV710))
		wv730_stawt_dpm(wdev);
	ewse
		wv770_stawt_dpm(wdev);

	if (pi->gfx_cwock_gating)
		wv770_gfx_cwock_gating_enabwe(wdev, twue);

	if (pi->mg_cwock_gating)
		wv770_mg_cwock_gating_enabwe(wdev, twue);

	wv770_enabwe_auto_thwottwe_souwce(wdev, WADEON_DPM_AUTO_THWOTTWE_SWC_THEWMAW, twue);

	wetuwn 0;
}

int wv770_dpm_wate_enabwe(stwuct wadeon_device *wdev)
{
	int wet;

	if (wdev->iwq.instawwed &&
	    w600_is_intewnaw_thewmaw_sensow(wdev->pm.int_thewmaw_type)) {
		PPSMC_Wesuwt wesuwt;

		wet = wv770_set_thewmaw_tempewatuwe_wange(wdev, W600_TEMP_WANGE_MIN, W600_TEMP_WANGE_MAX);
		if (wet)
			wetuwn wet;
		wdev->iwq.dpm_thewmaw = twue;
		wadeon_iwq_set(wdev);
		wesuwt = wv770_send_msg_to_smc(wdev, PPSMC_MSG_EnabweThewmawIntewwupt);

		if (wesuwt != PPSMC_Wesuwt_OK)
			DWM_DEBUG_KMS("Couwd not enabwe thewmaw intewwupts.\n");
	}

	wetuwn 0;
}

void wv770_dpm_disabwe(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	if (!wv770_dpm_enabwed(wdev))
		wetuwn;

	wv770_cweaw_vc(wdev);

	if (pi->thewmaw_pwotection)
		wv770_enabwe_thewmaw_pwotection(wdev, fawse);

	wv770_enabwe_spwead_spectwum(wdev, fawse);

	if (pi->dynamic_pcie_gen2)
		wv770_enabwe_dynamic_pcie_gen2(wdev, fawse);

	if (wdev->iwq.instawwed &&
	    w600_is_intewnaw_thewmaw_sensow(wdev->pm.int_thewmaw_type)) {
		wdev->iwq.dpm_thewmaw = fawse;
		wadeon_iwq_set(wdev);
	}

	if (pi->gfx_cwock_gating)
		wv770_gfx_cwock_gating_enabwe(wdev, fawse);

	if (pi->mg_cwock_gating)
		wv770_mg_cwock_gating_enabwe(wdev, fawse);

	if ((wdev->famiwy == CHIP_WV730) || (wdev->famiwy == CHIP_WV710))
		wv730_stop_dpm(wdev);
	ewse
		wv770_stop_dpm(wdev);

	w7xx_stop_smc(wdev);
	wv770_weset_smio_status(wdev);
}

int wv770_dpm_set_powew_state(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct wadeon_ps *new_ps = wdev->pm.dpm.wequested_ps;
	stwuct wadeon_ps *owd_ps = wdev->pm.dpm.cuwwent_ps;
	int wet;

	wet = wv770_westwict_pewfowmance_wevews_befowe_switch(wdev);
	if (wet) {
		DWM_EWWOW("wv770_westwict_pewfowmance_wevews_befowe_switch faiwed\n");
		wetuwn wet;
	}
	wv770_set_uvd_cwock_befowe_set_eng_cwock(wdev, new_ps, owd_ps);
	wet = wv770_hawt_smc(wdev);
	if (wet) {
		DWM_EWWOW("wv770_hawt_smc faiwed\n");
		wetuwn wet;
	}
	wet = wv770_upwoad_sw_state(wdev, new_ps);
	if (wet) {
		DWM_EWWOW("wv770_upwoad_sw_state faiwed\n");
		wetuwn wet;
	}
	w7xx_pwogwam_memowy_timing_pawametews(wdev, new_ps);
	if (pi->dcodt)
		wv770_pwogwam_dcodt_befowe_state_switch(wdev, new_ps, owd_ps);
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
	if (pi->dcodt)
		wv770_pwogwam_dcodt_aftew_state_switch(wdev, new_ps, owd_ps);
	wv770_set_uvd_cwock_aftew_set_eng_cwock(wdev, new_ps, owd_ps);

	wetuwn 0;
}

#if 0
void wv770_dpm_weset_asic(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct wadeon_ps *boot_ps = wdev->pm.dpm.boot_ps;

	wv770_westwict_pewfowmance_wevews_befowe_switch(wdev);
	if (pi->dcodt)
		wv770_pwogwam_dcodt_befowe_state_switch(wdev, boot_ps, boot_ps);
	wv770_set_boot_state(wdev);
	if (pi->dcodt)
		wv770_pwogwam_dcodt_aftew_state_switch(wdev, boot_ps, boot_ps);
}
#endif

void wv770_dpm_setup_asic(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	w7xx_wead_cwock_wegistews(wdev);
	wv770_wead_vowtage_smio_wegistews(wdev);
	wv770_get_memowy_type(wdev);
	if (pi->dcodt)
		wv770_get_mcwk_odt_thweshowd(wdev);
	wv770_get_pcie_gen2_status(wdev);

	wv770_enabwe_acpi_pm(wdev);

	if (wadeon_aspm != 0) {
		if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_ASPM_W0s)
			wv770_enabwe_w0s(wdev);
		if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_ASPM_W1)
			wv770_enabwe_w1(wdev);
		if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_TUWNOFFPWW_ASPMW1)
			wv770_enabwe_pww_sweep_in_w1(wdev);
	}
}

void wv770_dpm_dispway_configuwation_changed(stwuct wadeon_device *wdev)
{
	wv770_pwogwam_dispway_gap(wdev);
}

union powew_info {
	stwuct _ATOM_POWEWPWAY_INFO info;
	stwuct _ATOM_POWEWPWAY_INFO_V2 info_2;
	stwuct _ATOM_POWEWPWAY_INFO_V3 info_3;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE ppwib;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE2 ppwib2;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE3 ppwib3;
};

union ppwib_cwock_info {
	stwuct _ATOM_PPWIB_W600_CWOCK_INFO w600;
	stwuct _ATOM_PPWIB_WS780_CWOCK_INFO ws780;
	stwuct _ATOM_PPWIB_EVEWGWEEN_CWOCK_INFO evewgween;
	stwuct _ATOM_PPWIB_SUMO_CWOCK_INFO sumo;
};

union ppwib_powew_state {
	stwuct _ATOM_PPWIB_STATE v1;
	stwuct _ATOM_PPWIB_STATE_V2 v2;
};

static void wv7xx_pawse_ppwib_non_cwock_info(stwuct wadeon_device *wdev,
					     stwuct wadeon_ps *wps,
					     stwuct _ATOM_PPWIB_NONCWOCK_INFO *non_cwock_info,
					     u8 tabwe_wev)
{
	wps->caps = we32_to_cpu(non_cwock_info->uwCapsAndSettings);
	wps->cwass = we16_to_cpu(non_cwock_info->usCwassification);
	wps->cwass2 = we16_to_cpu(non_cwock_info->usCwassification2);

	if (ATOM_PPWIB_NONCWOCKINFO_VEW1 < tabwe_wev) {
		wps->vcwk = we32_to_cpu(non_cwock_info->uwVCWK);
		wps->dcwk = we32_to_cpu(non_cwock_info->uwDCWK);
	} ewse {
		wps->vcwk = 0;
		wps->dcwk = 0;
	}

	if (w600_is_uvd_state(wps->cwass, wps->cwass2)) {
		if ((wps->vcwk == 0) || (wps->dcwk == 0)) {
			wps->vcwk = WV770_DEFAUWT_VCWK_FWEQ;
			wps->dcwk = WV770_DEFAUWT_DCWK_FWEQ;
		}
	}

	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_BOOT)
		wdev->pm.dpm.boot_ps = wps;
	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_UVDSTATE)
		wdev->pm.dpm.uvd_ps = wps;
}

static void wv7xx_pawse_ppwib_cwock_info(stwuct wadeon_device *wdev,
					 stwuct wadeon_ps *wps, int index,
					 union ppwib_cwock_info *cwock_info)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wv7xx_ps *ps = wv770_get_ps(wps);
	u32 scwk, mcwk;
	stwuct wv7xx_pw *pw;

	switch (index) {
	case 0:
		pw = &ps->wow;
		bweak;
	case 1:
		pw = &ps->medium;
		bweak;
	case 2:
	defauwt:
		pw = &ps->high;
		bweak;
	}

	if (wdev->famiwy >= CHIP_CEDAW) {
		scwk = we16_to_cpu(cwock_info->evewgween.usEngineCwockWow);
		scwk |= cwock_info->evewgween.ucEngineCwockHigh << 16;
		mcwk = we16_to_cpu(cwock_info->evewgween.usMemowyCwockWow);
		mcwk |= cwock_info->evewgween.ucMemowyCwockHigh << 16;

		pw->vddc = we16_to_cpu(cwock_info->evewgween.usVDDC);
		pw->vddci = we16_to_cpu(cwock_info->evewgween.usVDDCI);
		pw->fwags = we32_to_cpu(cwock_info->evewgween.uwFwags);
	} ewse {
		scwk = we16_to_cpu(cwock_info->w600.usEngineCwockWow);
		scwk |= cwock_info->w600.ucEngineCwockHigh << 16;
		mcwk = we16_to_cpu(cwock_info->w600.usMemowyCwockWow);
		mcwk |= cwock_info->w600.ucMemowyCwockHigh << 16;

		pw->vddc = we16_to_cpu(cwock_info->w600.usVDDC);
		pw->fwags = we32_to_cpu(cwock_info->w600.uwFwags);
	}

	pw->mcwk = mcwk;
	pw->scwk = scwk;

	/* patch up vddc if necessawy */
	if (pw->vddc == 0xff01) {
		if (pi->max_vddc)
			pw->vddc = pi->max_vddc;
	}

	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_ACPI) {
		pi->acpi_vddc = pw->vddc;
		if (wdev->famiwy >= CHIP_CEDAW)
			eg_pi->acpi_vddci = pw->vddci;
		if (ps->wow.fwags & ATOM_PPWIB_W600_FWAGS_PCIEGEN2)
			pi->acpi_pcie_gen2 = twue;
		ewse
			pi->acpi_pcie_gen2 = fawse;
	}

	if (wps->cwass2 & ATOM_PPWIB_CWASSIFICATION2_UWV) {
		if (wdev->famiwy >= CHIP_BAWTS) {
			eg_pi->uwv.suppowted = twue;
			eg_pi->uwv.pw = pw;
		}
	}

	if (pi->min_vddc_in_tabwe > pw->vddc)
		pi->min_vddc_in_tabwe = pw->vddc;

	if (pi->max_vddc_in_tabwe < pw->vddc)
		pi->max_vddc_in_tabwe = pw->vddc;

	/* patch up boot state */
	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_BOOT) {
		u16 vddc, vddci, mvdd;
		wadeon_atombios_get_defauwt_vowtages(wdev, &vddc, &vddci, &mvdd);
		pw->mcwk = wdev->cwock.defauwt_mcwk;
		pw->scwk = wdev->cwock.defauwt_scwk;
		pw->vddc = vddc;
		pw->vddci = vddci;
	}

	if ((wps->cwass & ATOM_PPWIB_CWASSIFICATION_UI_MASK) ==
	    ATOM_PPWIB_CWASSIFICATION_UI_PEWFOWMANCE) {
		wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_ac.scwk = pw->scwk;
		wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_ac.mcwk = pw->mcwk;
		wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_ac.vddc = pw->vddc;
		wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_ac.vddci = pw->vddci;
	}
}

int wv7xx_pawse_powew_tabwe(stwuct wadeon_device *wdev)
{
	stwuct wadeon_mode_info *mode_info = &wdev->mode_info;
	stwuct _ATOM_PPWIB_NONCWOCK_INFO *non_cwock_info;
	union ppwib_powew_state *powew_state;
	int i, j;
	union ppwib_cwock_info *cwock_info;
	union powew_info *powew_info;
	int index = GetIndexIntoMastewTabwe(DATA, PowewPwayInfo);
	u16 data_offset;
	u8 fwev, cwev;
	stwuct wv7xx_ps *ps;

	if (!atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset))
		wetuwn -EINVAW;
	powew_info = (union powew_info *)(mode_info->atom_context->bios + data_offset);

	wdev->pm.dpm.ps = kcawwoc(powew_info->ppwib.ucNumStates,
				  sizeof(stwuct wadeon_ps),
				  GFP_KEWNEW);
	if (!wdev->pm.dpm.ps)
		wetuwn -ENOMEM;

	fow (i = 0; i < powew_info->ppwib.ucNumStates; i++) {
		powew_state = (union ppwib_powew_state *)
			(mode_info->atom_context->bios + data_offset +
			 we16_to_cpu(powew_info->ppwib.usStateAwwayOffset) +
			 i * powew_info->ppwib.ucStateEntwySize);
		non_cwock_info = (stwuct _ATOM_PPWIB_NONCWOCK_INFO *)
			(mode_info->atom_context->bios + data_offset +
			 we16_to_cpu(powew_info->ppwib.usNonCwockInfoAwwayOffset) +
			 (powew_state->v1.ucNonCwockStateIndex *
			  powew_info->ppwib.ucNonCwockSize));
		if (powew_info->ppwib.ucStateEntwySize - 1) {
			u8 *idx;
			ps = kzawwoc(sizeof(stwuct wv7xx_ps), GFP_KEWNEW);
			if (ps == NUWW) {
				kfwee(wdev->pm.dpm.ps);
				wetuwn -ENOMEM;
			}
			wdev->pm.dpm.ps[i].ps_pwiv = ps;
			wv7xx_pawse_ppwib_non_cwock_info(wdev, &wdev->pm.dpm.ps[i],
							 non_cwock_info,
							 powew_info->ppwib.ucNonCwockSize);
			idx = (u8 *)&powew_state->v1.ucCwockStateIndices[0];
			fow (j = 0; j < (powew_info->ppwib.ucStateEntwySize - 1); j++) {
				cwock_info = (union ppwib_cwock_info *)
					(mode_info->atom_context->bios + data_offset +
					 we16_to_cpu(powew_info->ppwib.usCwockInfoAwwayOffset) +
					 (idx[j] * powew_info->ppwib.ucCwockInfoSize));
				wv7xx_pawse_ppwib_cwock_info(wdev,
							     &wdev->pm.dpm.ps[i], j,
							     cwock_info);
			}
		}
	}
	wdev->pm.dpm.num_ps = powew_info->ppwib.ucNumStates;
	wetuwn 0;
}

void wv770_get_engine_memowy_ss(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct wadeon_atom_ss ss;

	pi->scwk_ss = wadeon_atombios_get_asic_ss_info(wdev, &ss,
						       ASIC_INTEWNAW_ENGINE_SS, 0);
	pi->mcwk_ss = wadeon_atombios_get_asic_ss_info(wdev, &ss,
						       ASIC_INTEWNAW_MEMOWY_SS, 0);

	if (pi->scwk_ss || pi->mcwk_ss)
		pi->dynamic_ss = twue;
	ewse
		pi->dynamic_ss = fawse;
}

int wv770_dpm_init(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi;
	stwuct atom_cwock_dividews dividews;
	int wet;

	pi = kzawwoc(sizeof(stwuct wv7xx_powew_info), GFP_KEWNEW);
	if (pi == NUWW)
		wetuwn -ENOMEM;
	wdev->pm.dpm.pwiv = pi;

	wv770_get_max_vddc(wdev);

	pi->acpi_vddc = 0;
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

	pi->mcwk_stwobe_mode_thweshowd = 30000;
	pi->mcwk_edc_enabwe_thweshowd = 30000;

	pi->wwp = WV770_WWP_DFWT;
	pi->wmp = WV770_WMP_DFWT;
	pi->whp = WV770_WHP_DFWT;
	pi->wmp = WV770_WMP_DFWT;

	pi->vowtage_contwow =
		wadeon_atom_is_vowtage_gpio(wdev, SET_VOWTAGE_TYPE_ASIC_VDDC, 0);

	pi->mvdd_contwow =
		wadeon_atom_is_vowtage_gpio(wdev, SET_VOWTAGE_TYPE_ASIC_MVDDC, 0);

	wv770_get_engine_memowy_ss(wdev);

	pi->asi = WV770_ASI_DFWT;
	pi->pasi = WV770_HASI_DFWT;
	pi->vwc = WV770_VWC_DFWT;

	pi->powew_gating = fawse;

	pi->gfx_cwock_gating = twue;

	pi->mg_cwock_gating = twue;
	pi->mgcgtssm = twue;

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

	pi->mcwk_stuttew_mode_thweshowd = 0;

	pi->swam_end = SMC_WAM_END;
	pi->state_tabwe_stawt = WV770_SMC_TABWE_ADDWESS;
	pi->soft_wegs_stawt = WV770_SMC_SOFT_WEGISTEWS_STAWT;

	wetuwn 0;
}

void wv770_dpm_pwint_powew_state(stwuct wadeon_device *wdev,
				 stwuct wadeon_ps *wps)
{
	stwuct wv7xx_ps *ps = wv770_get_ps(wps);
	stwuct wv7xx_pw *pw;

	w600_dpm_pwint_cwass_info(wps->cwass, wps->cwass2);
	w600_dpm_pwint_cap_info(wps->caps);
	pwintk("\tuvd    vcwk: %d dcwk: %d\n", wps->vcwk, wps->dcwk);
	if (wdev->famiwy >= CHIP_CEDAW) {
		pw = &ps->wow;
		pwintk("\t\tpowew wevew 0    scwk: %u mcwk: %u vddc: %u vddci: %u\n",
		       pw->scwk, pw->mcwk, pw->vddc, pw->vddci);
		pw = &ps->medium;
		pwintk("\t\tpowew wevew 1    scwk: %u mcwk: %u vddc: %u vddci: %u\n",
		       pw->scwk, pw->mcwk, pw->vddc, pw->vddci);
		pw = &ps->high;
		pwintk("\t\tpowew wevew 2    scwk: %u mcwk: %u vddc: %u vddci: %u\n",
		       pw->scwk, pw->mcwk, pw->vddc, pw->vddci);
	} ewse {
		pw = &ps->wow;
		pwintk("\t\tpowew wevew 0    scwk: %u mcwk: %u vddc: %u\n",
		       pw->scwk, pw->mcwk, pw->vddc);
		pw = &ps->medium;
		pwintk("\t\tpowew wevew 1    scwk: %u mcwk: %u vddc: %u\n",
		       pw->scwk, pw->mcwk, pw->vddc);
		pw = &ps->high;
		pwintk("\t\tpowew wevew 2    scwk: %u mcwk: %u vddc: %u\n",
		       pw->scwk, pw->mcwk, pw->vddc);
	}
	w600_dpm_pwint_ps_status(wdev, wps);
}

void wv770_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct wadeon_device *wdev,
						       stwuct seq_fiwe *m)
{
	stwuct wadeon_ps *wps = wdev->pm.dpm.cuwwent_ps;
	stwuct wv7xx_ps *ps = wv770_get_ps(wps);
	stwuct wv7xx_pw *pw;
	u32 cuwwent_index =
		(WWEG32(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & CUWWENT_PWOFIWE_INDEX_MASK) >>
		CUWWENT_PWOFIWE_INDEX_SHIFT;

	if (cuwwent_index > 2) {
		seq_pwintf(m, "invawid dpm pwofiwe %d\n", cuwwent_index);
	} ewse {
		if (cuwwent_index == 0)
			pw = &ps->wow;
		ewse if (cuwwent_index == 1)
			pw = &ps->medium;
		ewse /* cuwwent_index == 2 */
			pw = &ps->high;
		seq_pwintf(m, "uvd    vcwk: %d dcwk: %d\n", wps->vcwk, wps->dcwk);
		if (wdev->famiwy >= CHIP_CEDAW) {
			seq_pwintf(m, "powew wevew %d    scwk: %u mcwk: %u vddc: %u vddci: %u\n",
				   cuwwent_index, pw->scwk, pw->mcwk, pw->vddc, pw->vddci);
		} ewse {
			seq_pwintf(m, "powew wevew %d    scwk: %u mcwk: %u vddc: %u\n",
				   cuwwent_index, pw->scwk, pw->mcwk, pw->vddc);
		}
	}
}

u32 wv770_dpm_get_cuwwent_scwk(stwuct wadeon_device *wdev)
{
	stwuct wadeon_ps *wps = wdev->pm.dpm.cuwwent_ps;
	stwuct wv7xx_ps *ps = wv770_get_ps(wps);
	stwuct wv7xx_pw *pw;
	u32 cuwwent_index =
		(WWEG32(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & CUWWENT_PWOFIWE_INDEX_MASK) >>
		CUWWENT_PWOFIWE_INDEX_SHIFT;

	if (cuwwent_index > 2) {
		wetuwn 0;
	} ewse {
		if (cuwwent_index == 0)
			pw = &ps->wow;
		ewse if (cuwwent_index == 1)
			pw = &ps->medium;
		ewse /* cuwwent_index == 2 */
			pw = &ps->high;
		wetuwn  pw->scwk;
	}
}

u32 wv770_dpm_get_cuwwent_mcwk(stwuct wadeon_device *wdev)
{
	stwuct wadeon_ps *wps = wdev->pm.dpm.cuwwent_ps;
	stwuct wv7xx_ps *ps = wv770_get_ps(wps);
	stwuct wv7xx_pw *pw;
	u32 cuwwent_index =
		(WWEG32(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & CUWWENT_PWOFIWE_INDEX_MASK) >>
		CUWWENT_PWOFIWE_INDEX_SHIFT;

	if (cuwwent_index > 2) {
		wetuwn 0;
	} ewse {
		if (cuwwent_index == 0)
			pw = &ps->wow;
		ewse if (cuwwent_index == 1)
			pw = &ps->medium;
		ewse /* cuwwent_index == 2 */
			pw = &ps->high;
		wetuwn  pw->mcwk;
	}
}

void wv770_dpm_fini(stwuct wadeon_device *wdev)
{
	int i;

	fow (i = 0; i < wdev->pm.dpm.num_ps; i++) {
		kfwee(wdev->pm.dpm.ps[i].ps_pwiv);
	}
	kfwee(wdev->pm.dpm.ps);
	kfwee(wdev->pm.dpm.pwiv);
}

u32 wv770_dpm_get_scwk(stwuct wadeon_device *wdev, boow wow)
{
	stwuct wv7xx_ps *wequested_state = wv770_get_ps(wdev->pm.dpm.wequested_ps);

	if (wow)
		wetuwn wequested_state->wow.scwk;
	ewse
		wetuwn wequested_state->high.scwk;
}

u32 wv770_dpm_get_mcwk(stwuct wadeon_device *wdev, boow wow)
{
	stwuct wv7xx_ps *wequested_state = wv770_get_ps(wdev->pm.dpm.wequested_ps);

	if (wow)
		wetuwn wequested_state->wow.mcwk;
	ewse
		wetuwn wequested_state->high.mcwk;
}

boow wv770_dpm_vbwank_too_showt(stwuct wadeon_device *wdev)
{
	u32 vbwank_time = w600_dpm_get_vbwank_time(wdev);
	u32 switch_wimit = 200; /* 300 */

	/* WV770 */
	/* mcwk switching doesn't seem to wowk wewiabwy on desktop WV770s */
	if ((wdev->famiwy == CHIP_WV770) &&
	    !(wdev->fwags & WADEON_IS_MOBIWITY))
		switch_wimit = 0xffffffff; /* disabwe mcwk switching */

	if (vbwank_time < switch_wimit)
		wetuwn twue;
	ewse
		wetuwn fawse;

}
