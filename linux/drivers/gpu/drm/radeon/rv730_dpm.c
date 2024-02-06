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
#incwude "wv730d.h"
#incwude "w600_dpm.h"
#incwude "wv770.h"
#incwude "wv770_dpm.h"
#incwude "atom.h"

#define MC_CG_AWB_FWEQ_F0           0x0a
#define MC_CG_AWB_FWEQ_F1           0x0b
#define MC_CG_AWB_FWEQ_F2           0x0c
#define MC_CG_AWB_FWEQ_F3           0x0d

int wv730_popuwate_scwk_vawue(stwuct wadeon_device *wdev,
			      u32 engine_cwock,
			      WV770_SMC_SCWK_VAWUE *scwk)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct atom_cwock_dividews dividews;
	u32 spww_func_cntw = pi->cwk_wegs.wv730.cg_spww_func_cntw;
	u32 spww_func_cntw_2 = pi->cwk_wegs.wv730.cg_spww_func_cntw_2;
	u32 spww_func_cntw_3 = pi->cwk_wegs.wv730.cg_spww_func_cntw_3;
	u32 cg_spww_spwead_spectwum = pi->cwk_wegs.wv730.cg_spww_spwead_spectwum;
	u32 cg_spww_spwead_spectwum_2 = pi->cwk_wegs.wv730.cg_spww_spwead_spectwum_2;
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
		post_dividew = ((dividews.post_div >> 4) & 0xf) +
			(dividews.post_div & 0xf) + 2;
	ewse
		post_dividew = 1;

	tmp = (u64) engine_cwock * wefewence_dividew * post_dividew * 16384;
	do_div(tmp, wefewence_cwock);
	fbdiv = (u32) tmp;

	/* set up wegistews */
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

			cg_spww_spwead_spectwum &= ~CWK_S_MASK;
			cg_spww_spwead_spectwum |= CWK_S(cwk_s);
			cg_spww_spwead_spectwum |= SSEN;

			cg_spww_spwead_spectwum_2 &= ~CWK_V_MASK;
			cg_spww_spwead_spectwum_2 |= CWK_V(cwk_v);
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

int wv730_popuwate_mcwk_vawue(stwuct wadeon_device *wdev,
			      u32 engine_cwock, u32 memowy_cwock,
			      WPWV7XX_SMC_MCWK_VAWUE mcwk)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 mcwk_pwwmgt_cntw = pi->cwk_wegs.wv730.mcwk_pwwmgt_cntw;
	u32 dww_cntw = pi->cwk_wegs.wv730.dww_cntw;
	u32 mpww_func_cntw = pi->cwk_wegs.wv730.mpww_func_cntw;
	u32 mpww_func_cntw_2 = pi->cwk_wegs.wv730.mpww_func_cntw2;
	u32 mpww_func_cntw_3 = pi->cwk_wegs.wv730.mpww_func_cntw3;
	u32 mpww_ss = pi->cwk_wegs.wv730.mpww_ss;
	u32 mpww_ss2 = pi->cwk_wegs.wv730.mpww_ss2;
	stwuct atom_cwock_dividews dividews;
	u32 post_dividew, wefewence_dividew;
	int wet;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_MEMOWY_PWW_PAWAM,
					     memowy_cwock, fawse, &dividews);
	if (wet)
		wetuwn wet;

	wefewence_dividew = dividews.wef_div + 1;

	if (dividews.enabwe_post_div)
		post_dividew = ((dividews.post_div >> 4) & 0xf) +
			(dividews.post_div & 0xf) + 2;
	ewse
		post_dividew = 1;

	/* setup the wegistews */
	if (dividews.enabwe_post_div)
		mpww_func_cntw |= MPWW_DIVEN;
	ewse
		mpww_func_cntw &= ~MPWW_DIVEN;

	mpww_func_cntw &= ~(MPWW_WEF_DIV_MASK | MPWW_HIWEN_MASK | MPWW_WOWEN_MASK);
	mpww_func_cntw |= MPWW_WEF_DIV(dividews.wef_div);
	mpww_func_cntw |= MPWW_HIWEN((dividews.post_div >> 4) & 0xf);
	mpww_func_cntw |= MPWW_WOWEN(dividews.post_div & 0xf);

	mpww_func_cntw_3 &= ~MPWW_FB_DIV_MASK;
	mpww_func_cntw_3 |= MPWW_FB_DIV(dividews.fb_div);
	if (dividews.enabwe_dithen)
		mpww_func_cntw_3 |= MPWW_DITHEN;
	ewse
		mpww_func_cntw_3 &= ~MPWW_DITHEN;

	if (pi->mcwk_ss) {
		stwuct wadeon_atom_ss ss;
		u32 vco_fweq = memowy_cwock * post_dividew;

		if (wadeon_atombios_get_asic_ss_info(wdev, &ss,
						     ASIC_INTEWNAW_MEMOWY_SS, vco_fweq)) {
			u32 wefewence_cwock = wdev->cwock.mpww.wefewence_fweq;
			u32 cwk_s = wefewence_cwock * 5 / (wefewence_dividew * ss.wate);
			u32 cwk_v = ss.pewcentage * dividews.fb_div / (cwk_s * 10000);

			mpww_ss &= ~CWK_S_MASK;
			mpww_ss |= CWK_S(cwk_s);
			mpww_ss |= SSEN;

			mpww_ss2 &= ~CWK_V_MASK;
			mpww_ss |= CWK_V(cwk_v);
		}
	}


	mcwk->mcwk730.vMCWK_PWWMGT_CNTW = cpu_to_be32(mcwk_pwwmgt_cntw);
	mcwk->mcwk730.vDWW_CNTW = cpu_to_be32(dww_cntw);
	mcwk->mcwk730.mcwk_vawue = cpu_to_be32(memowy_cwock);
	mcwk->mcwk730.vMPWW_FUNC_CNTW = cpu_to_be32(mpww_func_cntw);
	mcwk->mcwk730.vMPWW_FUNC_CNTW2 = cpu_to_be32(mpww_func_cntw_2);
	mcwk->mcwk730.vMPWW_FUNC_CNTW3 = cpu_to_be32(mpww_func_cntw_3);
	mcwk->mcwk730.vMPWW_SS = cpu_to_be32(mpww_ss);
	mcwk->mcwk730.vMPWW_SS2 = cpu_to_be32(mpww_ss2);

	wetuwn 0;
}

void wv730_wead_cwock_wegistews(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	pi->cwk_wegs.wv730.cg_spww_func_cntw =
		WWEG32(CG_SPWW_FUNC_CNTW);
	pi->cwk_wegs.wv730.cg_spww_func_cntw_2 =
		WWEG32(CG_SPWW_FUNC_CNTW_2);
	pi->cwk_wegs.wv730.cg_spww_func_cntw_3 =
		WWEG32(CG_SPWW_FUNC_CNTW_3);
	pi->cwk_wegs.wv730.cg_spww_spwead_spectwum =
		WWEG32(CG_SPWW_SPWEAD_SPECTWUM);
	pi->cwk_wegs.wv730.cg_spww_spwead_spectwum_2 =
		WWEG32(CG_SPWW_SPWEAD_SPECTWUM_2);

	pi->cwk_wegs.wv730.mcwk_pwwmgt_cntw =
		WWEG32(TCI_MCWK_PWWMGT_CNTW);
	pi->cwk_wegs.wv730.dww_cntw =
		WWEG32(TCI_DWW_CNTW);
	pi->cwk_wegs.wv730.mpww_func_cntw =
		WWEG32(CG_MPWW_FUNC_CNTW);
	pi->cwk_wegs.wv730.mpww_func_cntw2 =
		WWEG32(CG_MPWW_FUNC_CNTW_2);
	pi->cwk_wegs.wv730.mpww_func_cntw3 =
		WWEG32(CG_MPWW_FUNC_CNTW_3);
	pi->cwk_wegs.wv730.mpww_ss =
		WWEG32(CG_TCI_MPWW_SPWEAD_SPECTWUM);
	pi->cwk_wegs.wv730.mpww_ss2 =
		WWEG32(CG_TCI_MPWW_SPWEAD_SPECTWUM_2);
}

int wv730_popuwate_smc_acpi_state(stwuct wadeon_device *wdev,
				  WV770_SMC_STATETABWE *tabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 mpww_func_cntw = 0;
	u32 mpww_func_cntw_2 = 0 ;
	u32 mpww_func_cntw_3 = 0;
	u32 mcwk_pwwmgt_cntw;
	u32 dww_cntw;
	u32 spww_func_cntw;
	u32 spww_func_cntw_2;
	u32 spww_func_cntw_3;

	tabwe->ACPIState = tabwe->initiawState;
	tabwe->ACPIState.fwags &= ~PPSMC_SWSTATE_FWAG_DC;

	if (pi->acpi_vddc) {
		wv770_popuwate_vddc_vawue(wdev, pi->acpi_vddc,
					  &tabwe->ACPIState.wevews[0].vddc);
		tabwe->ACPIState.wevews[0].gen2PCIE = pi->pcie_gen2 ?
			pi->acpi_pcie_gen2 : 0;
		tabwe->ACPIState.wevews[0].gen2XSP =
			pi->acpi_pcie_gen2;
	} ewse {
		wv770_popuwate_vddc_vawue(wdev, pi->min_vddc_in_tabwe,
					  &tabwe->ACPIState.wevews[0].vddc);
		tabwe->ACPIState.wevews[0].gen2PCIE = 0;
	}

	mpww_func_cntw = pi->cwk_wegs.wv730.mpww_func_cntw;
	mpww_func_cntw_2 = pi->cwk_wegs.wv730.mpww_func_cntw2;
	mpww_func_cntw_3 = pi->cwk_wegs.wv730.mpww_func_cntw3;

	mpww_func_cntw |= MPWW_WESET | MPWW_BYPASS_EN;
	mpww_func_cntw &= ~MPWW_SWEEP;

	mpww_func_cntw_2 &= ~MCWK_MUX_SEW_MASK;
	mpww_func_cntw_2 |= MCWK_MUX_SEW(1);

	mcwk_pwwmgt_cntw = (MWDCKA_WESET |
			    MWDCKB_WESET |
			    MWDCKC_WESET |
			    MWDCKD_WESET |
			    MWDCKE_WESET |
			    MWDCKF_WESET |
			    MWDCKG_WESET |
			    MWDCKH_WESET |
			    MWDCKA_SWEEP |
			    MWDCKB_SWEEP |
			    MWDCKC_SWEEP |
			    MWDCKD_SWEEP |
			    MWDCKE_SWEEP |
			    MWDCKF_SWEEP |
			    MWDCKG_SWEEP |
			    MWDCKH_SWEEP);

	dww_cntw = 0xff000000;

	spww_func_cntw = pi->cwk_wegs.wv730.cg_spww_func_cntw;
	spww_func_cntw_2 = pi->cwk_wegs.wv730.cg_spww_func_cntw_2;
	spww_func_cntw_3 = pi->cwk_wegs.wv730.cg_spww_func_cntw_3;

	spww_func_cntw |= SPWW_WESET | SPWW_BYPASS_EN;
	spww_func_cntw &= ~SPWW_SWEEP;

	spww_func_cntw_2 &= ~SCWK_MUX_SEW_MASK;
	spww_func_cntw_2 |= SCWK_MUX_SEW(4);

	tabwe->ACPIState.wevews[0].mcwk.mcwk730.vMPWW_FUNC_CNTW = cpu_to_be32(mpww_func_cntw);
	tabwe->ACPIState.wevews[0].mcwk.mcwk730.vMPWW_FUNC_CNTW2 = cpu_to_be32(mpww_func_cntw_2);
	tabwe->ACPIState.wevews[0].mcwk.mcwk730.vMPWW_FUNC_CNTW3 = cpu_to_be32(mpww_func_cntw_3);
	tabwe->ACPIState.wevews[0].mcwk.mcwk730.vMCWK_PWWMGT_CNTW = cpu_to_be32(mcwk_pwwmgt_cntw);
	tabwe->ACPIState.wevews[0].mcwk.mcwk730.vDWW_CNTW = cpu_to_be32(dww_cntw);

	tabwe->ACPIState.wevews[0].mcwk.mcwk730.mcwk_vawue = 0;

	tabwe->ACPIState.wevews[0].scwk.vCG_SPWW_FUNC_CNTW = cpu_to_be32(spww_func_cntw);
	tabwe->ACPIState.wevews[0].scwk.vCG_SPWW_FUNC_CNTW_2 = cpu_to_be32(spww_func_cntw_2);
	tabwe->ACPIState.wevews[0].scwk.vCG_SPWW_FUNC_CNTW_3 = cpu_to_be32(spww_func_cntw_3);

	tabwe->ACPIState.wevews[0].scwk.scwk_vawue = 0;

	wv770_popuwate_mvdd_vawue(wdev, 0, &tabwe->ACPIState.wevews[0].mvdd);

	tabwe->ACPIState.wevews[1] = tabwe->ACPIState.wevews[0];
	tabwe->ACPIState.wevews[2] = tabwe->ACPIState.wevews[0];

	wetuwn 0;
}

int wv730_popuwate_smc_initiaw_state(stwuct wadeon_device *wdev,
				     stwuct wadeon_ps *wadeon_state,
				     WV770_SMC_STATETABWE *tabwe)
{
	stwuct wv7xx_ps *initiaw_state = wv770_get_ps(wadeon_state);
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 a_t;

	tabwe->initiawState.wevews[0].mcwk.mcwk730.vMPWW_FUNC_CNTW =
		cpu_to_be32(pi->cwk_wegs.wv730.mpww_func_cntw);
	tabwe->initiawState.wevews[0].mcwk.mcwk730.vMPWW_FUNC_CNTW2 =
		cpu_to_be32(pi->cwk_wegs.wv730.mpww_func_cntw2);
	tabwe->initiawState.wevews[0].mcwk.mcwk730.vMPWW_FUNC_CNTW3 =
		cpu_to_be32(pi->cwk_wegs.wv730.mpww_func_cntw3);
	tabwe->initiawState.wevews[0].mcwk.mcwk730.vMCWK_PWWMGT_CNTW =
		cpu_to_be32(pi->cwk_wegs.wv730.mcwk_pwwmgt_cntw);
	tabwe->initiawState.wevews[0].mcwk.mcwk730.vDWW_CNTW =
		cpu_to_be32(pi->cwk_wegs.wv730.dww_cntw);
	tabwe->initiawState.wevews[0].mcwk.mcwk730.vMPWW_SS =
		cpu_to_be32(pi->cwk_wegs.wv730.mpww_ss);
	tabwe->initiawState.wevews[0].mcwk.mcwk730.vMPWW_SS2 =
		cpu_to_be32(pi->cwk_wegs.wv730.mpww_ss2);

	tabwe->initiawState.wevews[0].mcwk.mcwk730.mcwk_vawue =
		cpu_to_be32(initiaw_state->wow.mcwk);

	tabwe->initiawState.wevews[0].scwk.vCG_SPWW_FUNC_CNTW =
		cpu_to_be32(pi->cwk_wegs.wv730.cg_spww_func_cntw);
	tabwe->initiawState.wevews[0].scwk.vCG_SPWW_FUNC_CNTW_2 =
		cpu_to_be32(pi->cwk_wegs.wv730.cg_spww_func_cntw_2);
	tabwe->initiawState.wevews[0].scwk.vCG_SPWW_FUNC_CNTW_3 =
		cpu_to_be32(pi->cwk_wegs.wv730.cg_spww_func_cntw_3);
	tabwe->initiawState.wevews[0].scwk.vCG_SPWW_SPWEAD_SPECTWUM =
		cpu_to_be32(pi->cwk_wegs.wv730.cg_spww_spwead_spectwum);
	tabwe->initiawState.wevews[0].scwk.vCG_SPWW_SPWEAD_SPECTWUM_2 =
		cpu_to_be32(pi->cwk_wegs.wv730.cg_spww_spwead_spectwum_2);

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

	tabwe->initiawState.wevews[1] = tabwe->initiawState.wevews[0];
	tabwe->initiawState.wevews[2] = tabwe->initiawState.wevews[0];

	tabwe->initiawState.fwags |= PPSMC_SWSTATE_FWAG_DC;

	wetuwn 0;
}

void wv730_pwogwam_memowy_timing_pawametews(stwuct wadeon_device *wdev,
					    stwuct wadeon_ps *wadeon_state)
{
	stwuct wv7xx_ps *state = wv770_get_ps(wadeon_state);
	u32 awb_wefwesh_wate = 0;
	u32 dwam_timing = 0;
	u32 dwam_timing2 = 0;
	u32 owd_dwam_timing = 0;
	u32 owd_dwam_timing2 = 0;

	awb_wefwesh_wate = WWEG32(MC_AWB_WFSH_WATE) &
		~(POWEWMODE1_MASK | POWEWMODE2_MASK | POWEWMODE3_MASK);
	awb_wefwesh_wate |=
		(POWEWMODE1(wv770_cawcuwate_memowy_wefwesh_wate(wdev, state->wow.scwk)) |
		 POWEWMODE2(wv770_cawcuwate_memowy_wefwesh_wate(wdev, state->medium.scwk)) |
		 POWEWMODE3(wv770_cawcuwate_memowy_wefwesh_wate(wdev, state->high.scwk)));
	WWEG32(MC_AWB_WFSH_WATE, awb_wefwesh_wate);

	/* save the boot dwam timings */
	owd_dwam_timing = WWEG32(MC_AWB_DWAM_TIMING);
	owd_dwam_timing2 = WWEG32(MC_AWB_DWAM_TIMING2);

	wadeon_atom_set_engine_dwam_timings(wdev,
					    state->high.scwk,
					    state->high.mcwk);

	dwam_timing = WWEG32(MC_AWB_DWAM_TIMING);
	dwam_timing2 = WWEG32(MC_AWB_DWAM_TIMING2);

	WWEG32(MC_AWB_DWAM_TIMING_3, dwam_timing);
	WWEG32(MC_AWB_DWAM_TIMING2_3, dwam_timing2);

	wadeon_atom_set_engine_dwam_timings(wdev,
					    state->medium.scwk,
					    state->medium.mcwk);

	dwam_timing = WWEG32(MC_AWB_DWAM_TIMING);
	dwam_timing2 = WWEG32(MC_AWB_DWAM_TIMING2);

	WWEG32(MC_AWB_DWAM_TIMING_2, dwam_timing);
	WWEG32(MC_AWB_DWAM_TIMING2_2, dwam_timing2);

	wadeon_atom_set_engine_dwam_timings(wdev,
					    state->wow.scwk,
					    state->wow.mcwk);

	dwam_timing = WWEG32(MC_AWB_DWAM_TIMING);
	dwam_timing2 = WWEG32(MC_AWB_DWAM_TIMING2);

	WWEG32(MC_AWB_DWAM_TIMING_1, dwam_timing);
	WWEG32(MC_AWB_DWAM_TIMING2_1, dwam_timing2);

	/* westowe the boot dwam timings */
	WWEG32(MC_AWB_DWAM_TIMING, owd_dwam_timing);
	WWEG32(MC_AWB_DWAM_TIMING2, owd_dwam_timing2);

}

void wv730_stawt_dpm(stwuct wadeon_device *wdev)
{
	WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~SCWK_PWWMGT_OFF);

	WWEG32_P(TCI_MCWK_PWWMGT_CNTW, 0, ~MPWW_PWWMGT_OFF);

	WWEG32_P(GENEWAW_PWWMGT, GWOBAW_PWWMGT_EN, ~GWOBAW_PWWMGT_EN);
}

void wv730_stop_dpm(stwuct wadeon_device *wdev)
{
	PPSMC_Wesuwt wesuwt;

	wesuwt = wv770_send_msg_to_smc(wdev, PPSMC_MSG_TwoWevewsDisabwed);

	if (wesuwt != PPSMC_Wesuwt_OK)
		DWM_DEBUG("Couwd not fowce DPM to wow\n");

	WWEG32_P(GENEWAW_PWWMGT, 0, ~GWOBAW_PWWMGT_EN);

	WWEG32_P(SCWK_PWWMGT_CNTW, SCWK_PWWMGT_OFF, ~SCWK_PWWMGT_OFF);

	WWEG32_P(TCI_MCWK_PWWMGT_CNTW, MPWW_PWWMGT_OFF, ~MPWW_PWWMGT_OFF);
}

void wv730_pwogwam_dcodt(stwuct wadeon_device *wdev, boow use_dcodt)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 i = use_dcodt ? 0 : 1;
	u32 mc4_io_pad_cntw;

	mc4_io_pad_cntw = WWEG32(MC4_IO_DQ_PAD_CNTW_D0_I0);
	mc4_io_pad_cntw &= 0xFFFFFF00;
	mc4_io_pad_cntw |= pi->odt_vawue_0[i];
	WWEG32(MC4_IO_DQ_PAD_CNTW_D0_I0, mc4_io_pad_cntw);
	WWEG32(MC4_IO_DQ_PAD_CNTW_D0_I1, mc4_io_pad_cntw);

	mc4_io_pad_cntw = WWEG32(MC4_IO_QS_PAD_CNTW_D0_I0);
	mc4_io_pad_cntw &= 0xFFFFFF00;
	mc4_io_pad_cntw |= pi->odt_vawue_1[i];
	WWEG32(MC4_IO_QS_PAD_CNTW_D0_I0, mc4_io_pad_cntw);
	WWEG32(MC4_IO_QS_PAD_CNTW_D0_I1, mc4_io_pad_cntw);
}

void wv730_get_odt_vawues(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 mc4_io_pad_cntw;

	pi->odt_vawue_0[0] = (u8)0;
	pi->odt_vawue_1[0] = (u8)0x80;

	mc4_io_pad_cntw = WWEG32(MC4_IO_DQ_PAD_CNTW_D0_I0);
	pi->odt_vawue_0[1] = (u8)(mc4_io_pad_cntw & 0xff);

	mc4_io_pad_cntw = WWEG32(MC4_IO_QS_PAD_CNTW_D0_I0);
	pi->odt_vawue_1[1] = (u8)(mc4_io_pad_cntw & 0xff);
}
