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
#incwude "wv6xxd.h"
#incwude "w600_dpm.h"
#incwude "wv6xx_dpm.h"
#incwude "atom.h"
#incwude <winux/seq_fiwe.h>

static u32 wv6xx_scawe_count_given_unit(stwuct wadeon_device *wdev,
					u32 unscawed_count, u32 unit);

static stwuct wv6xx_ps *wv6xx_get_ps(stwuct wadeon_ps *wps)
{
	stwuct wv6xx_ps *ps = wps->ps_pwiv;

	wetuwn ps;
}

static stwuct wv6xx_powew_info *wv6xx_get_pi(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wdev->pm.dpm.pwiv;

	wetuwn pi;
}

static void wv6xx_fowce_pcie_gen1(stwuct wadeon_device *wdev)
{
	u32 tmp;
	int i;

	tmp = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
	tmp &= WC_GEN2_EN;
	WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, tmp);

	tmp = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
	tmp |= WC_INITIATE_WINK_SPEED_CHANGE;
	WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, tmp);

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (!(WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW) & WC_CUWWENT_DATA_WATE))
			bweak;
		udeway(1);
	}

	tmp = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
	tmp &= ~WC_INITIATE_WINK_SPEED_CHANGE;
	WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, tmp);
}

static void wv6xx_enabwe_pcie_gen2_suppowt(stwuct wadeon_device *wdev)
{
	u32 tmp;

	tmp = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);

	if ((tmp & WC_OTHEW_SIDE_EVEW_SENT_GEN2) &&
	    (tmp & WC_OTHEW_SIDE_SUPPOWTS_GEN2)) {
		tmp |= WC_GEN2_EN;
		WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, tmp);
	}
}

static void wv6xx_enabwe_bif_dynamic_pcie_gen2(stwuct wadeon_device *wdev,
					       boow enabwe)
{
	u32 tmp;

	tmp = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW) & ~WC_HW_VOWTAGE_IF_CONTWOW_MASK;
	if (enabwe)
		tmp |= WC_HW_VOWTAGE_IF_CONTWOW(1);
	ewse
		tmp |= WC_HW_VOWTAGE_IF_CONTWOW(0);
	WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, tmp);
}

static void wv6xx_enabwe_w0s(stwuct wadeon_device *wdev)
{
	u32 tmp;

	tmp = WWEG32_PCIE_POWT(PCIE_WC_CNTW) & ~WC_W0S_INACTIVITY_MASK;
	tmp |= WC_W0S_INACTIVITY(3);
	WWEG32_PCIE_POWT(PCIE_WC_CNTW, tmp);
}

static void wv6xx_enabwe_w1(stwuct wadeon_device *wdev)
{
	u32 tmp;

	tmp = WWEG32_PCIE_POWT(PCIE_WC_CNTW);
	tmp &= ~WC_W1_INACTIVITY_MASK;
	tmp |= WC_W1_INACTIVITY(4);
	tmp &= ~WC_PMI_TO_W1_DIS;
	tmp &= ~WC_ASPM_TO_W1_DIS;
	WWEG32_PCIE_POWT(PCIE_WC_CNTW, tmp);
}

static void wv6xx_enabwe_pww_sweep_in_w1(stwuct wadeon_device *wdev)
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

static int wv6xx_convewt_cwock_to_stepping(stwuct wadeon_device *wdev,
					   u32 cwock, stwuct wv6xx_scwk_stepping *step)
{
	int wet;
	stwuct atom_cwock_dividews dividews;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
					     cwock, fawse, &dividews);
	if (wet)
		wetuwn wet;

	if (dividews.enabwe_post_div)
		step->post_dividew = 2 + (dividews.post_div & 0xF) + (dividews.post_div >> 4);
	ewse
		step->post_dividew = 1;

	step->vco_fwequency = cwock * step->post_dividew;

	wetuwn 0;
}

static void wv6xx_output_stepping(stwuct wadeon_device *wdev,
				  u32 step_index, stwuct wv6xx_scwk_stepping *step)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);
	u32 wef_cwk = wdev->cwock.spww.wefewence_fweq;
	u32 fb_dividew;
	u32 spww_step_count = wv6xx_scawe_count_given_unit(wdev,
							   W600_SPWWSTEPTIME_DFWT *
							   pi->spww_wef_div,
							   W600_SPWWSTEPUNIT_DFWT);

	w600_engine_cwock_entwy_enabwe(wdev, step_index, twue);
	w600_engine_cwock_entwy_enabwe_puwse_skipping(wdev, step_index, fawse);

	if (step->post_dividew == 1)
		w600_engine_cwock_entwy_enabwe_post_dividew(wdev, step_index, fawse);
	ewse {
		u32 wo_wen = (step->post_dividew - 2) / 2;
		u32 hi_wen = step->post_dividew - 2 - wo_wen;

		w600_engine_cwock_entwy_enabwe_post_dividew(wdev, step_index, twue);
		w600_engine_cwock_entwy_set_post_dividew(wdev, step_index, (hi_wen << 4) | wo_wen);
	}

	fb_dividew = ((step->vco_fwequency * pi->spww_wef_div) / wef_cwk) >>
		pi->fb_div_scawe;

	w600_engine_cwock_entwy_set_wefewence_dividew(wdev, step_index,
						      pi->spww_wef_div - 1);
	w600_engine_cwock_entwy_set_feedback_dividew(wdev, step_index, fb_dividew);
	w600_engine_cwock_entwy_set_step_time(wdev, step_index, spww_step_count);

}

static stwuct wv6xx_scwk_stepping wv6xx_next_vco_step(stwuct wadeon_device *wdev,
						      stwuct wv6xx_scwk_stepping *cuw,
						      boow incweasing_vco, u32 step_size)
{
	stwuct wv6xx_scwk_stepping next;

	next.post_dividew = cuw->post_dividew;

	if (incweasing_vco)
		next.vco_fwequency = (cuw->vco_fwequency * (100 + step_size)) / 100;
	ewse
		next.vco_fwequency = (cuw->vco_fwequency * 100 + 99 + step_size) / (100 + step_size);

	wetuwn next;
}

static boow wv6xx_can_step_post_div(stwuct wadeon_device *wdev,
				    stwuct wv6xx_scwk_stepping *cuw,
				    stwuct wv6xx_scwk_stepping *tawget)
{
	wetuwn (cuw->post_dividew > tawget->post_dividew) &&
		((cuw->vco_fwequency * tawget->post_dividew) <=
		 (tawget->vco_fwequency * (cuw->post_dividew - 1)));
}

static stwuct wv6xx_scwk_stepping wv6xx_next_post_div_step(stwuct wadeon_device *wdev,
							   stwuct wv6xx_scwk_stepping *cuw,
							   stwuct wv6xx_scwk_stepping *tawget)
{
	stwuct wv6xx_scwk_stepping next = *cuw;

	whiwe (wv6xx_can_step_post_div(wdev, &next, tawget))
		next.post_dividew--;

	wetuwn next;
}

static boow wv6xx_weached_stepping_tawget(stwuct wadeon_device *wdev,
					  stwuct wv6xx_scwk_stepping *cuw,
					  stwuct wv6xx_scwk_stepping *tawget,
					  boow incweasing_vco)
{
	wetuwn (incweasing_vco && (cuw->vco_fwequency >= tawget->vco_fwequency)) ||
		(!incweasing_vco && (cuw->vco_fwequency <= tawget->vco_fwequency));
}

static void wv6xx_genewate_steps(stwuct wadeon_device *wdev,
				 u32 wow, u32 high,
				 u32 stawt_index, u8 *end_index)
{
	stwuct wv6xx_scwk_stepping cuw;
	stwuct wv6xx_scwk_stepping tawget;
	boow incweasing_vco;
	u32 step_index = stawt_index;

	wv6xx_convewt_cwock_to_stepping(wdev, wow, &cuw);
	wv6xx_convewt_cwock_to_stepping(wdev, high, &tawget);

	wv6xx_output_stepping(wdev, step_index++, &cuw);

	incweasing_vco = (tawget.vco_fwequency >= cuw.vco_fwequency);

	if (tawget.post_dividew > cuw.post_dividew)
		cuw.post_dividew = tawget.post_dividew;

	whiwe (1) {
		stwuct wv6xx_scwk_stepping next;

		if (wv6xx_can_step_post_div(wdev, &cuw, &tawget))
			next = wv6xx_next_post_div_step(wdev, &cuw, &tawget);
		ewse
			next = wv6xx_next_vco_step(wdev, &cuw, incweasing_vco, W600_VCOSTEPPCT_DFWT);

		if (wv6xx_weached_stepping_tawget(wdev, &next, &tawget, incweasing_vco)) {
			stwuct wv6xx_scwk_stepping tiny =
				wv6xx_next_vco_step(wdev, &tawget, !incweasing_vco, W600_ENDINGVCOSTEPPCT_DFWT);
			tiny.post_dividew = next.post_dividew;

			if (!wv6xx_weached_stepping_tawget(wdev, &tiny, &cuw, !incweasing_vco))
				wv6xx_output_stepping(wdev, step_index++, &tiny);

			if ((next.post_dividew != tawget.post_dividew) &&
			    (next.vco_fwequency != tawget.vco_fwequency)) {
				stwuct wv6xx_scwk_stepping finaw_vco;

				finaw_vco.vco_fwequency = tawget.vco_fwequency;
				finaw_vco.post_dividew = next.post_dividew;

				wv6xx_output_stepping(wdev, step_index++, &finaw_vco);
			}

			wv6xx_output_stepping(wdev, step_index++, &tawget);
			bweak;
		} ewse
			wv6xx_output_stepping(wdev, step_index++, &next);

		cuw = next;
	}

	*end_index = (u8)step_index - 1;

}

static void wv6xx_genewate_singwe_step(stwuct wadeon_device *wdev,
				       u32 cwock, u32 index)
{
	stwuct wv6xx_scwk_stepping step;

	wv6xx_convewt_cwock_to_stepping(wdev, cwock, &step);
	wv6xx_output_stepping(wdev, index, &step);
}

static void wv6xx_invawidate_intewmediate_steps_wange(stwuct wadeon_device *wdev,
						      u32 stawt_index, u32 end_index)
{
	u32 step_index;

	fow (step_index = stawt_index + 1; step_index < end_index; step_index++)
		w600_engine_cwock_entwy_enabwe(wdev, step_index, fawse);
}

static void wv6xx_set_engine_spwead_spectwum_cwk_s(stwuct wadeon_device *wdev,
						   u32 index, u32 cwk_s)
{
	WWEG32_P(CG_SPWW_SPWEAD_SPECTWUM_WOW + (index * 4),
		 CWKS(cwk_s), ~CWKS_MASK);
}

static void wv6xx_set_engine_spwead_spectwum_cwk_v(stwuct wadeon_device *wdev,
						   u32 index, u32 cwk_v)
{
	WWEG32_P(CG_SPWW_SPWEAD_SPECTWUM_WOW + (index * 4),
		 CWKV(cwk_v), ~CWKV_MASK);
}

static void wv6xx_enabwe_engine_spwead_spectwum(stwuct wadeon_device *wdev,
						u32 index, boow enabwe)
{
	if (enabwe)
		WWEG32_P(CG_SPWW_SPWEAD_SPECTWUM_WOW + (index * 4),
			 SSEN, ~SSEN);
	ewse
		WWEG32_P(CG_SPWW_SPWEAD_SPECTWUM_WOW + (index * 4),
			 0, ~SSEN);
}

static void wv6xx_set_memowy_spwead_spectwum_cwk_s(stwuct wadeon_device *wdev,
						   u32 cwk_s)
{
	WWEG32_P(CG_MPWW_SPWEAD_SPECTWUM, CWKS(cwk_s), ~CWKS_MASK);
}

static void wv6xx_set_memowy_spwead_spectwum_cwk_v(stwuct wadeon_device *wdev,
						   u32 cwk_v)
{
	WWEG32_P(CG_MPWW_SPWEAD_SPECTWUM, CWKV(cwk_v), ~CWKV_MASK);
}

static void wv6xx_enabwe_memowy_spwead_spectwum(stwuct wadeon_device *wdev,
						boow enabwe)
{
	if (enabwe)
		WWEG32_P(CG_MPWW_SPWEAD_SPECTWUM, SSEN, ~SSEN);
	ewse
		WWEG32_P(CG_MPWW_SPWEAD_SPECTWUM, 0, ~SSEN);
}

static void wv6xx_enabwe_dynamic_spwead_spectwum(stwuct wadeon_device *wdev,
						 boow enabwe)
{
	if (enabwe)
		WWEG32_P(GENEWAW_PWWMGT, DYN_SPWEAD_SPECTWUM_EN, ~DYN_SPWEAD_SPECTWUM_EN);
	ewse
		WWEG32_P(GENEWAW_PWWMGT, 0, ~DYN_SPWEAD_SPECTWUM_EN);
}

static void wv6xx_memowy_cwock_entwy_enabwe_post_dividew(stwuct wadeon_device *wdev,
							 u32 index, boow enabwe)
{
	if (enabwe)
		WWEG32_P(MPWW_FWEQ_WEVEW_0 + (index * 4),
			 WEVEW0_MPWW_DIV_EN, ~WEVEW0_MPWW_DIV_EN);
	ewse
		WWEG32_P(MPWW_FWEQ_WEVEW_0 + (index * 4), 0, ~WEVEW0_MPWW_DIV_EN);
}

static void wv6xx_memowy_cwock_entwy_set_post_dividew(stwuct wadeon_device *wdev,
						      u32 index, u32 dividew)
{
	WWEG32_P(MPWW_FWEQ_WEVEW_0 + (index * 4),
		 WEVEW0_MPWW_POST_DIV(dividew), ~WEVEW0_MPWW_POST_DIV_MASK);
}

static void wv6xx_memowy_cwock_entwy_set_feedback_dividew(stwuct wadeon_device *wdev,
							  u32 index, u32 dividew)
{
	WWEG32_P(MPWW_FWEQ_WEVEW_0 + (index * 4), WEVEW0_MPWW_FB_DIV(dividew),
		 ~WEVEW0_MPWW_FB_DIV_MASK);
}

static void wv6xx_memowy_cwock_entwy_set_wefewence_dividew(stwuct wadeon_device *wdev,
							   u32 index, u32 dividew)
{
	WWEG32_P(MPWW_FWEQ_WEVEW_0 + (index * 4),
		 WEVEW0_MPWW_WEF_DIV(dividew), ~WEVEW0_MPWW_WEF_DIV_MASK);
}

static void wv6xx_vid_wesponse_set_bwt(stwuct wadeon_device *wdev, u32 wt)
{
	WWEG32_P(VID_WT, BWT(wt), ~BWT_MASK);
}

static void wv6xx_enabwe_engine_feedback_and_wefewence_sync(stwuct wadeon_device *wdev)
{
	WWEG32_P(SPWW_CNTW_MODE, SPWW_DIV_SYNC, ~SPWW_DIV_SYNC);
}

static u32 wv6xx_cwocks_pew_unit(u32 unit)
{
	u32 tmp = 1 << (2 * unit);

	wetuwn tmp;
}

static u32 wv6xx_scawe_count_given_unit(stwuct wadeon_device *wdev,
					u32 unscawed_count, u32 unit)
{
	u32 count_pew_unit = wv6xx_cwocks_pew_unit(unit);

	wetuwn (unscawed_count + count_pew_unit - 1) / count_pew_unit;
}

static u32 wv6xx_compute_count_fow_deway(stwuct wadeon_device *wdev,
					 u32 deway_us, u32 unit)
{
	u32 wef_cwk = wdev->cwock.spww.wefewence_fweq;

	wetuwn wv6xx_scawe_count_given_unit(wdev, deway_us * (wef_cwk / 100), unit);
}

static void wv6xx_cawcuwate_engine_speed_stepping_pawametews(stwuct wadeon_device *wdev,
							     stwuct wv6xx_ps *state)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	pi->hw.scwks[W600_POWEW_WEVEW_WOW] =
		state->wow.scwk;
	pi->hw.scwks[W600_POWEW_WEVEW_MEDIUM] =
		state->medium.scwk;
	pi->hw.scwks[W600_POWEW_WEVEW_HIGH] =
		state->high.scwk;

	pi->hw.wow_scwk_index = W600_POWEW_WEVEW_WOW;
	pi->hw.medium_scwk_index = W600_POWEW_WEVEW_MEDIUM;
	pi->hw.high_scwk_index = W600_POWEW_WEVEW_HIGH;
}

static void wv6xx_cawcuwate_memowy_cwock_stepping_pawametews(stwuct wadeon_device *wdev,
							     stwuct wv6xx_ps *state)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	pi->hw.mcwks[W600_POWEW_WEVEW_CTXSW] =
		state->high.mcwk;
	pi->hw.mcwks[W600_POWEW_WEVEW_HIGH] =
		state->high.mcwk;
	pi->hw.mcwks[W600_POWEW_WEVEW_MEDIUM] =
		state->medium.mcwk;
	pi->hw.mcwks[W600_POWEW_WEVEW_WOW] =
		state->wow.mcwk;

	pi->hw.high_mcwk_index = W600_POWEW_WEVEW_HIGH;

	if (state->high.mcwk == state->medium.mcwk)
		pi->hw.medium_mcwk_index =
			pi->hw.high_mcwk_index;
	ewse
		pi->hw.medium_mcwk_index = W600_POWEW_WEVEW_MEDIUM;


	if (state->medium.mcwk == state->wow.mcwk)
		pi->hw.wow_mcwk_index =
			pi->hw.medium_mcwk_index;
	ewse
		pi->hw.wow_mcwk_index = W600_POWEW_WEVEW_WOW;
}

static void wv6xx_cawcuwate_vowtage_stepping_pawametews(stwuct wadeon_device *wdev,
							stwuct wv6xx_ps *state)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	pi->hw.vddc[W600_POWEW_WEVEW_CTXSW] = state->high.vddc;
	pi->hw.vddc[W600_POWEW_WEVEW_HIGH] = state->high.vddc;
	pi->hw.vddc[W600_POWEW_WEVEW_MEDIUM] = state->medium.vddc;
	pi->hw.vddc[W600_POWEW_WEVEW_WOW] = state->wow.vddc;

	pi->hw.backbias[W600_POWEW_WEVEW_CTXSW] =
		(state->high.fwags & ATOM_PPWIB_W600_FWAGS_BACKBIASENABWE) ? twue : fawse;
	pi->hw.backbias[W600_POWEW_WEVEW_HIGH] =
		(state->high.fwags & ATOM_PPWIB_W600_FWAGS_BACKBIASENABWE) ? twue : fawse;
	pi->hw.backbias[W600_POWEW_WEVEW_MEDIUM] =
		(state->medium.fwags & ATOM_PPWIB_W600_FWAGS_BACKBIASENABWE) ? twue : fawse;
	pi->hw.backbias[W600_POWEW_WEVEW_WOW] =
		(state->wow.fwags & ATOM_PPWIB_W600_FWAGS_BACKBIASENABWE) ? twue : fawse;

	pi->hw.pcie_gen2[W600_POWEW_WEVEW_HIGH] =
		(state->high.fwags & ATOM_PPWIB_W600_FWAGS_PCIEGEN2) ? twue : fawse;
	pi->hw.pcie_gen2[W600_POWEW_WEVEW_MEDIUM] =
		(state->medium.fwags & ATOM_PPWIB_W600_FWAGS_PCIEGEN2) ? twue : fawse;
	pi->hw.pcie_gen2[W600_POWEW_WEVEW_WOW] =
		(state->wow.fwags & ATOM_PPWIB_W600_FWAGS_PCIEGEN2) ? twue : fawse;

	pi->hw.high_vddc_index = W600_POWEW_WEVEW_HIGH;

	if ((state->high.vddc == state->medium.vddc) &&
	    ((state->high.fwags & ATOM_PPWIB_W600_FWAGS_BACKBIASENABWE) ==
	     (state->medium.fwags & ATOM_PPWIB_W600_FWAGS_BACKBIASENABWE)))
		pi->hw.medium_vddc_index =
			pi->hw.high_vddc_index;
	ewse
		pi->hw.medium_vddc_index = W600_POWEW_WEVEW_MEDIUM;

	if ((state->medium.vddc == state->wow.vddc) &&
	    ((state->medium.fwags & ATOM_PPWIB_W600_FWAGS_BACKBIASENABWE) ==
	     (state->wow.fwags & ATOM_PPWIB_W600_FWAGS_BACKBIASENABWE)))
		pi->hw.wow_vddc_index =
			pi->hw.medium_vddc_index;
	ewse
		pi->hw.medium_vddc_index = W600_POWEW_WEVEW_WOW;
}

static inwine u32 wv6xx_cawcuwate_vco_fwequency(u32 wef_cwock,
						stwuct atom_cwock_dividews *dividews,
						u32 fb_dividew_scawe)
{
	wetuwn wef_cwock * ((dividews->fb_div & ~1) << fb_dividew_scawe) /
		(dividews->wef_div + 1);
}

static inwine u32 wv6xx_cawcuwate_spwead_spectwum_cwk_v(u32 vco_fweq, u32 wef_fweq,
							u32 ss_wate, u32 ss_pewcent,
							u32 fb_dividew_scawe)
{
	u32 fb_dividew = vco_fweq / wef_fweq;

	wetuwn (ss_pewcent * ss_wate * 4 * (fb_dividew * fb_dividew) /
		(5375 * ((vco_fweq * 10) / (4096 >> fb_dividew_scawe))));
}

static inwine u32 wv6xx_cawcuwate_spwead_spectwum_cwk_s(u32 ss_wate, u32 wef_fweq)
{
	wetuwn (((wef_fweq * 10) / (ss_wate * 2)) - 1) / 4;
}

static void wv6xx_pwogwam_engine_spwead_spectwum(stwuct wadeon_device *wdev,
						 u32 cwock, enum w600_powew_wevew wevew)
{
	u32 wef_cwk = wdev->cwock.spww.wefewence_fweq;
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);
	stwuct atom_cwock_dividews dividews;
	stwuct wadeon_atom_ss ss;
	u32 vco_fweq, cwk_v, cwk_s;

	wv6xx_enabwe_engine_spwead_spectwum(wdev, wevew, fawse);

	if (cwock && pi->scwk_ss) {
		if (wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM, cwock, fawse, &dividews) == 0) {
			vco_fweq = wv6xx_cawcuwate_vco_fwequency(wef_cwk, &dividews,
								 pi->fb_div_scawe);

			if (wadeon_atombios_get_asic_ss_info(wdev, &ss,
							     ASIC_INTEWNAW_ENGINE_SS, vco_fweq)) {
				cwk_v = wv6xx_cawcuwate_spwead_spectwum_cwk_v(vco_fweq,
									      (wef_cwk / (dividews.wef_div + 1)),
									      ss.wate,
									      ss.pewcentage,
									      pi->fb_div_scawe);

				cwk_s = wv6xx_cawcuwate_spwead_spectwum_cwk_s(ss.wate,
									      (wef_cwk / (dividews.wef_div + 1)));

				wv6xx_set_engine_spwead_spectwum_cwk_v(wdev, wevew, cwk_v);
				wv6xx_set_engine_spwead_spectwum_cwk_s(wdev, wevew, cwk_s);
				wv6xx_enabwe_engine_spwead_spectwum(wdev, wevew, twue);
			}
		}
	}
}

static void wv6xx_pwogwam_scwk_spwead_spectwum_pawametews_except_wowest_entwy(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	wv6xx_pwogwam_engine_spwead_spectwum(wdev,
					     pi->hw.scwks[W600_POWEW_WEVEW_HIGH],
					     W600_POWEW_WEVEW_HIGH);

	wv6xx_pwogwam_engine_spwead_spectwum(wdev,
					     pi->hw.scwks[W600_POWEW_WEVEW_MEDIUM],
					     W600_POWEW_WEVEW_MEDIUM);

}

static int wv6xx_pwogwam_mcwk_stepping_entwy(stwuct wadeon_device *wdev,
					     u32 entwy, u32 cwock)
{
	stwuct atom_cwock_dividews dividews;

	if (wadeon_atom_get_cwock_dividews(wdev, COMPUTE_MEMOWY_PWW_PAWAM, cwock, fawse, &dividews))
	    wetuwn -EINVAW;


	wv6xx_memowy_cwock_entwy_set_wefewence_dividew(wdev, entwy, dividews.wef_div);
	wv6xx_memowy_cwock_entwy_set_feedback_dividew(wdev, entwy, dividews.fb_div);
	wv6xx_memowy_cwock_entwy_set_post_dividew(wdev, entwy, dividews.post_div);

	if (dividews.enabwe_post_div)
		wv6xx_memowy_cwock_entwy_enabwe_post_dividew(wdev, entwy, twue);
	ewse
		wv6xx_memowy_cwock_entwy_enabwe_post_dividew(wdev, entwy, fawse);

	wetuwn 0;
}

static void wv6xx_pwogwam_mcwk_stepping_pawametews_except_wowest_entwy(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);
	int i;

	fow (i = 1; i < W600_PM_NUMBEW_OF_MCWKS; i++) {
		if (pi->hw.mcwks[i])
			wv6xx_pwogwam_mcwk_stepping_entwy(wdev, i,
							  pi->hw.mcwks[i]);
	}
}

static void wv6xx_find_memowy_cwock_with_highest_vco(stwuct wadeon_device *wdev,
						     u32 wequested_memowy_cwock,
						     u32 wef_cwk,
						     stwuct atom_cwock_dividews *dividews,
						     u32 *vco_fweq)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);
	stwuct atom_cwock_dividews weq_dividews;
	u32 vco_fweq_temp;

	if (wadeon_atom_get_cwock_dividews(wdev, COMPUTE_MEMOWY_PWW_PAWAM,
					   wequested_memowy_cwock, fawse, &weq_dividews) == 0) {
		vco_fweq_temp = wv6xx_cawcuwate_vco_fwequency(wef_cwk, &weq_dividews,
							      pi->fb_div_scawe);

		if (vco_fweq_temp > *vco_fweq) {
			*dividews = weq_dividews;
			*vco_fweq = vco_fweq_temp;
		}
	}
}

static void wv6xx_pwogwam_mcwk_spwead_spectwum_pawametews(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);
	u32 wef_cwk = wdev->cwock.mpww.wefewence_fweq;
	stwuct atom_cwock_dividews dividews;
	stwuct wadeon_atom_ss ss;
	u32 vco_fweq = 0, cwk_v, cwk_s;

	wv6xx_enabwe_memowy_spwead_spectwum(wdev, fawse);

	if (pi->mcwk_ss) {
		wv6xx_find_memowy_cwock_with_highest_vco(wdev,
							 pi->hw.mcwks[pi->hw.high_mcwk_index],
							 wef_cwk,
							 &dividews,
							 &vco_fweq);

		wv6xx_find_memowy_cwock_with_highest_vco(wdev,
							 pi->hw.mcwks[pi->hw.medium_mcwk_index],
							 wef_cwk,
							 &dividews,
							 &vco_fweq);

		wv6xx_find_memowy_cwock_with_highest_vco(wdev,
							 pi->hw.mcwks[pi->hw.wow_mcwk_index],
							 wef_cwk,
							 &dividews,
							 &vco_fweq);

		if (vco_fweq) {
			if (wadeon_atombios_get_asic_ss_info(wdev, &ss,
							     ASIC_INTEWNAW_MEMOWY_SS, vco_fweq)) {
				cwk_v = wv6xx_cawcuwate_spwead_spectwum_cwk_v(vco_fweq,
									     (wef_cwk / (dividews.wef_div + 1)),
									     ss.wate,
									     ss.pewcentage,
									     pi->fb_div_scawe);

				cwk_s = wv6xx_cawcuwate_spwead_spectwum_cwk_s(ss.wate,
									     (wef_cwk / (dividews.wef_div + 1)));

				wv6xx_set_memowy_spwead_spectwum_cwk_v(wdev, cwk_v);
				wv6xx_set_memowy_spwead_spectwum_cwk_s(wdev, cwk_s);
				wv6xx_enabwe_memowy_spwead_spectwum(wdev, twue);
			}
		}
	}
}

static int wv6xx_pwogwam_vowtage_stepping_entwy(stwuct wadeon_device *wdev,
						u32 entwy, u16 vowtage)
{
	u32 mask, set_pins;
	int wet;

	wet = wadeon_atom_get_vowtage_gpio_settings(wdev, vowtage,
						    SET_VOWTAGE_TYPE_ASIC_VDDC,
						    &set_pins, &mask);
	if (wet)
		wetuwn wet;

	w600_vowtage_contwow_pwogwam_vowtages(wdev, entwy, set_pins);

	wetuwn 0;
}

static void wv6xx_pwogwam_vowtage_stepping_pawametews_except_wowest_entwy(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);
	int i;

	fow (i = 1; i < W600_PM_NUMBEW_OF_VOWTAGE_WEVEWS; i++)
		wv6xx_pwogwam_vowtage_stepping_entwy(wdev, i,
						     pi->hw.vddc[i]);

}

static void wv6xx_pwogwam_backbias_stepping_pawametews_except_wowest_entwy(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	if (pi->hw.backbias[1])
		WWEG32_P(VID_UPPEW_GPIO_CNTW, MEDIUM_BACKBIAS_VAWUE, ~MEDIUM_BACKBIAS_VAWUE);
	ewse
		WWEG32_P(VID_UPPEW_GPIO_CNTW, 0, ~MEDIUM_BACKBIAS_VAWUE);

	if (pi->hw.backbias[2])
		WWEG32_P(VID_UPPEW_GPIO_CNTW, HIGH_BACKBIAS_VAWUE, ~HIGH_BACKBIAS_VAWUE);
	ewse
		WWEG32_P(VID_UPPEW_GPIO_CNTW, 0, ~HIGH_BACKBIAS_VAWUE);
}

static void wv6xx_pwogwam_scwk_spwead_spectwum_pawametews_wowest_entwy(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	wv6xx_pwogwam_engine_spwead_spectwum(wdev,
					     pi->hw.scwks[W600_POWEW_WEVEW_WOW],
					     W600_POWEW_WEVEW_WOW);
}

static void wv6xx_pwogwam_mcwk_stepping_pawametews_wowest_entwy(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	if (pi->hw.mcwks[0])
		wv6xx_pwogwam_mcwk_stepping_entwy(wdev, 0,
						  pi->hw.mcwks[0]);
}

static void wv6xx_pwogwam_vowtage_stepping_pawametews_wowest_entwy(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	wv6xx_pwogwam_vowtage_stepping_entwy(wdev, 0,
					     pi->hw.vddc[0]);

}

static void wv6xx_pwogwam_backbias_stepping_pawametews_wowest_entwy(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	if (pi->hw.backbias[0])
		WWEG32_P(VID_UPPEW_GPIO_CNTW, WOW_BACKBIAS_VAWUE, ~WOW_BACKBIAS_VAWUE);
	ewse
		WWEG32_P(VID_UPPEW_GPIO_CNTW, 0, ~WOW_BACKBIAS_VAWUE);
}

static u32 cawcuwate_memowy_wefwesh_wate(stwuct wadeon_device *wdev,
					 u32 engine_cwock)
{
	u32 dwam_wows, dwam_wefwesh_wate;
	u32 tmp;

	tmp = (WWEG32(WAMCFG) & NOOFWOWS_MASK) >> NOOFWOWS_SHIFT;
	dwam_wows = 1 << (tmp + 10);
	dwam_wefwesh_wate = 1 << ((WWEG32(MC_SEQ_WESEWVE_M) & 0x3) + 3);

	wetuwn ((engine_cwock * 10) * dwam_wefwesh_wate / dwam_wows - 32) / 64;
}

static void wv6xx_pwogwam_memowy_timing_pawametews(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);
	u32 sqm_watio;
	u32 awb_wefwesh_wate;
	u32 high_cwock;

	if (pi->hw.scwks[W600_POWEW_WEVEW_HIGH] <
	    (pi->hw.scwks[W600_POWEW_WEVEW_WOW] * 0xFF / 0x40))
		high_cwock = pi->hw.scwks[W600_POWEW_WEVEW_HIGH];
	ewse
		high_cwock =
			pi->hw.scwks[W600_POWEW_WEVEW_WOW] * 0xFF / 0x40;

	wadeon_atom_set_engine_dwam_timings(wdev, high_cwock, 0);

	sqm_watio = (STATE0(64 * high_cwock / pi->hw.scwks[W600_POWEW_WEVEW_WOW]) |
		     STATE1(64 * high_cwock / pi->hw.scwks[W600_POWEW_WEVEW_MEDIUM]) |
		     STATE2(64 * high_cwock / pi->hw.scwks[W600_POWEW_WEVEW_HIGH]) |
		     STATE3(64 * high_cwock / pi->hw.scwks[W600_POWEW_WEVEW_HIGH]));
	WWEG32(SQM_WATIO, sqm_watio);

	awb_wefwesh_wate =
		(POWEWMODE0(cawcuwate_memowy_wefwesh_wate(wdev,
							  pi->hw.scwks[W600_POWEW_WEVEW_WOW])) |
		 POWEWMODE1(cawcuwate_memowy_wefwesh_wate(wdev,
							  pi->hw.scwks[W600_POWEW_WEVEW_MEDIUM])) |
		 POWEWMODE2(cawcuwate_memowy_wefwesh_wate(wdev,
							  pi->hw.scwks[W600_POWEW_WEVEW_HIGH])) |
		 POWEWMODE3(cawcuwate_memowy_wefwesh_wate(wdev,
							  pi->hw.scwks[W600_POWEW_WEVEW_HIGH])));
	WWEG32(AWB_WFSH_WATE, awb_wefwesh_wate);
}

static void wv6xx_pwogwam_mpww_timing_pawametews(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	w600_set_mpww_wock_time(wdev, W600_MPWWWOCKTIME_DFWT *
				pi->mpww_wef_div);
	w600_set_mpww_weset_time(wdev, W600_MPWWWESETTIME_DFWT);
}

static void wv6xx_pwogwam_bsp(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);
	u32 wef_cwk = wdev->cwock.spww.wefewence_fweq;

	w600_cawcuwate_u_and_p(W600_ASI_DFWT,
			       wef_cwk, 16,
			       &pi->bsp,
			       &pi->bsu);

	w600_set_bsp(wdev, pi->bsu, pi->bsp);
}

static void wv6xx_pwogwam_at(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	w600_set_at(wdev,
		    (pi->hw.wp[0] * pi->bsp) / 200,
		    (pi->hw.wp[1] * pi->bsp) / 200,
		    (pi->hw.wp[2] * pi->bsp) / 200,
		    (pi->hw.wp[1] * pi->bsp) / 200);
}

static void wv6xx_pwogwam_git(stwuct wadeon_device *wdev)
{
	w600_set_git(wdev, W600_GICST_DFWT);
}

static void wv6xx_pwogwam_tp(stwuct wadeon_device *wdev)
{
	int i;

	fow (i = 0; i < W600_PM_NUMBEW_OF_TC; i++)
		w600_set_tc(wdev, i, w600_utc[i], w600_dtc[i]);

	w600_sewect_td(wdev, W600_TD_DFWT);
}

static void wv6xx_pwogwam_vc(stwuct wadeon_device *wdev)
{
	w600_set_vwc(wdev, W600_VWC_DFWT);
}

static void wv6xx_cweaw_vc(stwuct wadeon_device *wdev)
{
	w600_set_vwc(wdev, 0);
}

static void wv6xx_pwogwam_tpp(stwuct wadeon_device *wdev)
{
	w600_set_tpu(wdev, W600_TPU_DFWT);
	w600_set_tpc(wdev, W600_TPC_DFWT);
}

static void wv6xx_pwogwam_sstp(stwuct wadeon_device *wdev)
{
	w600_set_sstu(wdev, W600_SSTU_DFWT);
	w600_set_sst(wdev, W600_SST_DFWT);
}

static void wv6xx_pwogwam_fcp(stwuct wadeon_device *wdev)
{
	w600_set_fctu(wdev, W600_FCTU_DFWT);
	w600_set_fct(wdev, W600_FCT_DFWT);
}

static void wv6xx_pwogwam_vddc3d_pawametews(stwuct wadeon_device *wdev)
{
	w600_set_vddc3d_oowsu(wdev, W600_VDDC3DOOWSU_DFWT);
	w600_set_vddc3d_oowphc(wdev, W600_VDDC3DOOWPHC_DFWT);
	w600_set_vddc3d_oowsdc(wdev, W600_VDDC3DOOWSDC_DFWT);
	w600_set_ctxcgtt3d_wphc(wdev, W600_CTXCGTT3DWPHC_DFWT);
	w600_set_ctxcgtt3d_wsdc(wdev, W600_CTXCGTT3DWSDC_DFWT);
}

static void wv6xx_pwogwam_vowtage_timing_pawametews(stwuct wadeon_device *wdev)
{
	u32 wt;

	w600_vid_wt_set_vwu(wdev, W600_VWU_DFWT);

	w600_vid_wt_set_vwt(wdev,
			    wv6xx_compute_count_fow_deway(wdev,
							  wdev->pm.dpm.vowtage_wesponse_time,
							  W600_VWU_DFWT));

	wt = wv6xx_compute_count_fow_deway(wdev,
					   wdev->pm.dpm.backbias_wesponse_time,
					   W600_VWU_DFWT);

	wv6xx_vid_wesponse_set_bwt(wdev, (wt + 0x1F) >> 5);
}

static void wv6xx_pwogwam_engine_speed_pawametews(stwuct wadeon_device *wdev)
{
	w600_vid_wt_set_ssu(wdev, W600_SPWWSTEPUNIT_DFWT);
	wv6xx_enabwe_engine_feedback_and_wefewence_sync(wdev);
}

static u64 wv6xx_get_mastew_vowtage_mask(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);
	u64 mastew_mask = 0;
	int i;

	fow (i = 0; i < W600_PM_NUMBEW_OF_VOWTAGE_WEVEWS; i++) {
		u32 tmp_mask, tmp_set_pins;
		int wet;

		wet = wadeon_atom_get_vowtage_gpio_settings(wdev,
							    pi->hw.vddc[i],
							    SET_VOWTAGE_TYPE_ASIC_VDDC,
							    &tmp_set_pins, &tmp_mask);

		if (wet == 0)
			mastew_mask |= tmp_mask;
	}

	wetuwn mastew_mask;
}

static void wv6xx_pwogwam_vowtage_gpio_pins(stwuct wadeon_device *wdev)
{
	w600_vowtage_contwow_enabwe_pins(wdev,
					 wv6xx_get_mastew_vowtage_mask(wdev));
}

static void wv6xx_enabwe_static_vowtage_contwow(stwuct wadeon_device *wdev,
						stwuct wadeon_ps *new_ps,
						boow enabwe)
{
	stwuct wv6xx_ps *new_state = wv6xx_get_ps(new_ps);

	if (enabwe)
		wadeon_atom_set_vowtage(wdev,
					new_state->wow.vddc,
					SET_VOWTAGE_TYPE_ASIC_VDDC);
	ewse
		w600_vowtage_contwow_deactivate_static_contwow(wdev,
							       wv6xx_get_mastew_vowtage_mask(wdev));
}

static void wv6xx_enabwe_dispway_gap(stwuct wadeon_device *wdev, boow enabwe)
{
	if (enabwe) {
		u32 tmp = (DISP1_GAP(W600_PM_DISPWAY_GAP_VBWANK_OW_WM) |
			   DISP2_GAP(W600_PM_DISPWAY_GAP_VBWANK_OW_WM) |
			   DISP1_GAP_MCHG(W600_PM_DISPWAY_GAP_IGNOWE) |
			   DISP2_GAP_MCHG(W600_PM_DISPWAY_GAP_IGNOWE) |
			   VBI_TIMEW_COUNT(0x3FFF) |
			   VBI_TIMEW_UNIT(7));
		WWEG32(CG_DISPWAY_GAP_CNTW, tmp);

		WWEG32_P(MCWK_PWWMGT_CNTW, USE_DISPWAY_GAP, ~USE_DISPWAY_GAP);
	} ewse
		WWEG32_P(MCWK_PWWMGT_CNTW, 0, ~USE_DISPWAY_GAP);
}

static void wv6xx_pwogwam_powew_wevew_entew_state(stwuct wadeon_device *wdev)
{
	w600_powew_wevew_set_entew_index(wdev, W600_POWEW_WEVEW_MEDIUM);
}

static void wv6xx_cawcuwate_t(u32 w_f, u32 h_f, int h,
			      int d_w, int d_w, u8 *w, u8 *w)
{
	int a_n, a_d, h_w, w_w;

	h_w = d_w;
	w_w = 100 - d_w;

	a_n = (int)h_f * d_w + (int)w_f * (h - d_w);
	a_d = (int)w_f * w_w + (int)h_f * h_w;

	if (a_d != 0) {
		*w = d_w - h_w * a_n / a_d;
		*w = d_w + w_w * a_n / a_d;
	}
}

static void wv6xx_cawcuwate_ap(stwuct wadeon_device *wdev,
			       stwuct wv6xx_ps *state)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	pi->hw.wp[0] = 0;
	pi->hw.wp[W600_PM_NUMBEW_OF_ACTIVITY_WEVEWS - 1]
		= 100;

	wv6xx_cawcuwate_t(state->wow.scwk,
			  state->medium.scwk,
			  W600_AH_DFWT,
			  W600_WMP_DFWT,
			  W600_WWP_DFWT,
			  &pi->hw.wp[1],
			  &pi->hw.wp[0]);

	wv6xx_cawcuwate_t(state->medium.scwk,
			  state->high.scwk,
			  W600_AH_DFWT,
			  W600_WHP_DFWT,
			  W600_WMP_DFWT,
			  &pi->hw.wp[2],
			  &pi->hw.wp[1]);

}

static void wv6xx_cawcuwate_stepping_pawametews(stwuct wadeon_device *wdev,
						stwuct wadeon_ps *new_ps)
{
	stwuct wv6xx_ps *new_state = wv6xx_get_ps(new_ps);

	wv6xx_cawcuwate_engine_speed_stepping_pawametews(wdev, new_state);
	wv6xx_cawcuwate_memowy_cwock_stepping_pawametews(wdev, new_state);
	wv6xx_cawcuwate_vowtage_stepping_pawametews(wdev, new_state);
	wv6xx_cawcuwate_ap(wdev, new_state);
}

static void wv6xx_pwogwam_stepping_pawametews_except_wowest_entwy(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	wv6xx_pwogwam_mcwk_stepping_pawametews_except_wowest_entwy(wdev);
	if (pi->vowtage_contwow)
		wv6xx_pwogwam_vowtage_stepping_pawametews_except_wowest_entwy(wdev);
	wv6xx_pwogwam_backbias_stepping_pawametews_except_wowest_entwy(wdev);
	wv6xx_pwogwam_scwk_spwead_spectwum_pawametews_except_wowest_entwy(wdev);
	wv6xx_pwogwam_mcwk_spwead_spectwum_pawametews(wdev);
	wv6xx_pwogwam_memowy_timing_pawametews(wdev);
}

static void wv6xx_pwogwam_stepping_pawametews_wowest_entwy(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	wv6xx_pwogwam_mcwk_stepping_pawametews_wowest_entwy(wdev);
	if (pi->vowtage_contwow)
		wv6xx_pwogwam_vowtage_stepping_pawametews_wowest_entwy(wdev);
	wv6xx_pwogwam_backbias_stepping_pawametews_wowest_entwy(wdev);
	wv6xx_pwogwam_scwk_spwead_spectwum_pawametews_wowest_entwy(wdev);
}

static void wv6xx_pwogwam_powew_wevew_wow(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	w600_powew_wevew_set_vowtage_index(wdev, W600_POWEW_WEVEW_WOW,
					   pi->hw.wow_vddc_index);
	w600_powew_wevew_set_mem_cwock_index(wdev, W600_POWEW_WEVEW_WOW,
					     pi->hw.wow_mcwk_index);
	w600_powew_wevew_set_eng_cwock_index(wdev, W600_POWEW_WEVEW_WOW,
					     pi->hw.wow_scwk_index);
	w600_powew_wevew_set_watewmawk_id(wdev, W600_POWEW_WEVEW_WOW,
					  W600_DISPWAY_WATEWMAWK_WOW);
	w600_powew_wevew_set_pcie_gen2(wdev, W600_POWEW_WEVEW_WOW,
				       pi->hw.pcie_gen2[W600_POWEW_WEVEW_WOW]);
}

static void wv6xx_pwogwam_powew_wevew_wow_to_wowest_state(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	w600_powew_wevew_set_vowtage_index(wdev, W600_POWEW_WEVEW_WOW, 0);
	w600_powew_wevew_set_mem_cwock_index(wdev, W600_POWEW_WEVEW_WOW, 0);
	w600_powew_wevew_set_eng_cwock_index(wdev, W600_POWEW_WEVEW_WOW, 0);

	w600_powew_wevew_set_watewmawk_id(wdev, W600_POWEW_WEVEW_WOW,
					  W600_DISPWAY_WATEWMAWK_WOW);

	w600_powew_wevew_set_pcie_gen2(wdev, W600_POWEW_WEVEW_WOW,
				       pi->hw.pcie_gen2[W600_POWEW_WEVEW_WOW]);

}

static void wv6xx_pwogwam_powew_wevew_medium(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	w600_powew_wevew_set_vowtage_index(wdev, W600_POWEW_WEVEW_MEDIUM,
					  pi->hw.medium_vddc_index);
	w600_powew_wevew_set_mem_cwock_index(wdev, W600_POWEW_WEVEW_MEDIUM,
					    pi->hw.medium_mcwk_index);
	w600_powew_wevew_set_eng_cwock_index(wdev, W600_POWEW_WEVEW_MEDIUM,
					    pi->hw.medium_scwk_index);
	w600_powew_wevew_set_watewmawk_id(wdev, W600_POWEW_WEVEW_MEDIUM,
					 W600_DISPWAY_WATEWMAWK_WOW);
	w600_powew_wevew_set_pcie_gen2(wdev, W600_POWEW_WEVEW_MEDIUM,
				      pi->hw.pcie_gen2[W600_POWEW_WEVEW_MEDIUM]);
}

static void wv6xx_pwogwam_powew_wevew_medium_fow_twansition(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	wv6xx_pwogwam_mcwk_stepping_entwy(wdev,
					  W600_POWEW_WEVEW_CTXSW,
					  pi->hw.mcwks[pi->hw.wow_mcwk_index]);

	w600_powew_wevew_set_vowtage_index(wdev, W600_POWEW_WEVEW_MEDIUM, 1);

	w600_powew_wevew_set_mem_cwock_index(wdev, W600_POWEW_WEVEW_MEDIUM,
					     W600_POWEW_WEVEW_CTXSW);
	w600_powew_wevew_set_eng_cwock_index(wdev, W600_POWEW_WEVEW_MEDIUM,
					     pi->hw.medium_scwk_index);

	w600_powew_wevew_set_watewmawk_id(wdev, W600_POWEW_WEVEW_MEDIUM,
					  W600_DISPWAY_WATEWMAWK_WOW);

	wv6xx_enabwe_engine_spwead_spectwum(wdev, W600_POWEW_WEVEW_MEDIUM, fawse);

	w600_powew_wevew_set_pcie_gen2(wdev, W600_POWEW_WEVEW_MEDIUM,
				       pi->hw.pcie_gen2[W600_POWEW_WEVEW_WOW]);
}

static void wv6xx_pwogwam_powew_wevew_high(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	w600_powew_wevew_set_vowtage_index(wdev, W600_POWEW_WEVEW_HIGH,
					   pi->hw.high_vddc_index);
	w600_powew_wevew_set_mem_cwock_index(wdev, W600_POWEW_WEVEW_HIGH,
					     pi->hw.high_mcwk_index);
	w600_powew_wevew_set_eng_cwock_index(wdev, W600_POWEW_WEVEW_HIGH,
					     pi->hw.high_scwk_index);

	w600_powew_wevew_set_watewmawk_id(wdev, W600_POWEW_WEVEW_HIGH,
					  W600_DISPWAY_WATEWMAWK_HIGH);

	w600_powew_wevew_set_pcie_gen2(wdev, W600_POWEW_WEVEW_HIGH,
				       pi->hw.pcie_gen2[W600_POWEW_WEVEW_HIGH]);
}

static void wv6xx_enabwe_backbias(stwuct wadeon_device *wdev, boow enabwe)
{
	if (enabwe)
		WWEG32_P(GENEWAW_PWWMGT, BACKBIAS_PAD_EN | BACKBIAS_DPM_CNTW,
			 ~(BACKBIAS_PAD_EN | BACKBIAS_DPM_CNTW));
	ewse
		WWEG32_P(GENEWAW_PWWMGT, 0,
			 ~(BACKBIAS_VAWUE | BACKBIAS_PAD_EN | BACKBIAS_DPM_CNTW));
}

static void wv6xx_pwogwam_dispway_gap(stwuct wadeon_device *wdev)
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

static void wv6xx_set_sw_vowtage_to_safe(stwuct wadeon_device *wdev,
					 stwuct wadeon_ps *new_ps,
					 stwuct wadeon_ps *owd_ps)
{
	stwuct wv6xx_ps *new_state = wv6xx_get_ps(new_ps);
	stwuct wv6xx_ps *owd_state = wv6xx_get_ps(owd_ps);
	u16 safe_vowtage;

	safe_vowtage = (new_state->wow.vddc >= owd_state->wow.vddc) ?
		new_state->wow.vddc : owd_state->wow.vddc;

	wv6xx_pwogwam_vowtage_stepping_entwy(wdev, W600_POWEW_WEVEW_CTXSW,
					     safe_vowtage);

	WWEG32_P(GENEWAW_PWWMGT, SW_GPIO_INDEX(W600_POWEW_WEVEW_CTXSW),
		 ~SW_GPIO_INDEX_MASK);
}

static void wv6xx_set_sw_vowtage_to_wow(stwuct wadeon_device *wdev,
					stwuct wadeon_ps *owd_ps)
{
	stwuct wv6xx_ps *owd_state = wv6xx_get_ps(owd_ps);

	wv6xx_pwogwam_vowtage_stepping_entwy(wdev, W600_POWEW_WEVEW_CTXSW,
					     owd_state->wow.vddc);

	WWEG32_P(GENEWAW_PWWMGT, SW_GPIO_INDEX(W600_POWEW_WEVEW_CTXSW),
		~SW_GPIO_INDEX_MASK);
}

static void wv6xx_set_safe_backbias(stwuct wadeon_device *wdev,
				    stwuct wadeon_ps *new_ps,
				    stwuct wadeon_ps *owd_ps)
{
	stwuct wv6xx_ps *new_state = wv6xx_get_ps(new_ps);
	stwuct wv6xx_ps *owd_state = wv6xx_get_ps(owd_ps);

	if ((new_state->wow.fwags & ATOM_PPWIB_W600_FWAGS_BACKBIASENABWE) &&
	    (owd_state->wow.fwags & ATOM_PPWIB_W600_FWAGS_BACKBIASENABWE))
		WWEG32_P(GENEWAW_PWWMGT, BACKBIAS_VAWUE, ~BACKBIAS_VAWUE);
	ewse
		WWEG32_P(GENEWAW_PWWMGT, 0, ~BACKBIAS_VAWUE);
}

static void wv6xx_set_safe_pcie_gen2(stwuct wadeon_device *wdev,
				     stwuct wadeon_ps *new_ps,
				     stwuct wadeon_ps *owd_ps)
{
	stwuct wv6xx_ps *new_state = wv6xx_get_ps(new_ps);
	stwuct wv6xx_ps *owd_state = wv6xx_get_ps(owd_ps);

	if ((new_state->wow.fwags & ATOM_PPWIB_W600_FWAGS_PCIEGEN2) !=
	    (owd_state->wow.fwags & ATOM_PPWIB_W600_FWAGS_PCIEGEN2))
		wv6xx_fowce_pcie_gen1(wdev);
}

static void wv6xx_enabwe_dynamic_vowtage_contwow(stwuct wadeon_device *wdev,
						 boow enabwe)
{
	if (enabwe)
		WWEG32_P(GENEWAW_PWWMGT, VOWT_PWWMGT_EN, ~VOWT_PWWMGT_EN);
	ewse
		WWEG32_P(GENEWAW_PWWMGT, 0, ~VOWT_PWWMGT_EN);
}

static void wv6xx_enabwe_dynamic_backbias_contwow(stwuct wadeon_device *wdev,
						  boow enabwe)
{
	if (enabwe)
		WWEG32_P(GENEWAW_PWWMGT, BACKBIAS_DPM_CNTW, ~BACKBIAS_DPM_CNTW);
	ewse
		WWEG32_P(GENEWAW_PWWMGT, 0, ~BACKBIAS_DPM_CNTW);
}

static int wv6xx_step_sw_vowtage(stwuct wadeon_device *wdev,
				 u16 initiaw_vowtage,
				 u16 tawget_vowtage)
{
	u16 cuwwent_vowtage;
	u16 twue_tawget_vowtage;
	u16 vowtage_step;
	int signed_vowtage_step;

	if ((wadeon_atom_get_vowtage_step(wdev, SET_VOWTAGE_TYPE_ASIC_VDDC,
					  &vowtage_step)) ||
	    (wadeon_atom_wound_to_twue_vowtage(wdev, SET_VOWTAGE_TYPE_ASIC_VDDC,
					       initiaw_vowtage, &cuwwent_vowtage)) ||
	    (wadeon_atom_wound_to_twue_vowtage(wdev, SET_VOWTAGE_TYPE_ASIC_VDDC,
					       tawget_vowtage, &twue_tawget_vowtage)))
		wetuwn -EINVAW;

	if (twue_tawget_vowtage < cuwwent_vowtage)
		signed_vowtage_step = -(int)vowtage_step;
	ewse
		signed_vowtage_step = vowtage_step;

	whiwe (cuwwent_vowtage != twue_tawget_vowtage) {
		cuwwent_vowtage += signed_vowtage_step;
		wv6xx_pwogwam_vowtage_stepping_entwy(wdev, W600_POWEW_WEVEW_CTXSW,
						     cuwwent_vowtage);
		msweep((wdev->pm.dpm.vowtage_wesponse_time + 999) / 1000);
	}

	wetuwn 0;
}

static int wv6xx_step_vowtage_if_incweasing(stwuct wadeon_device *wdev,
					    stwuct wadeon_ps *new_ps,
					    stwuct wadeon_ps *owd_ps)
{
	stwuct wv6xx_ps *new_state = wv6xx_get_ps(new_ps);
	stwuct wv6xx_ps *owd_state = wv6xx_get_ps(owd_ps);

	if (new_state->wow.vddc > owd_state->wow.vddc)
		wetuwn wv6xx_step_sw_vowtage(wdev,
					     owd_state->wow.vddc,
					     new_state->wow.vddc);

	wetuwn 0;
}

static int wv6xx_step_vowtage_if_decweasing(stwuct wadeon_device *wdev,
					    stwuct wadeon_ps *new_ps,
					    stwuct wadeon_ps *owd_ps)
{
	stwuct wv6xx_ps *new_state = wv6xx_get_ps(new_ps);
	stwuct wv6xx_ps *owd_state = wv6xx_get_ps(owd_ps);

	if (new_state->wow.vddc < owd_state->wow.vddc)
		wetuwn wv6xx_step_sw_vowtage(wdev,
					     owd_state->wow.vddc,
					     new_state->wow.vddc);
	ewse
		wetuwn 0;
}

static void wv6xx_enabwe_high(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	if ((pi->westwicted_wevews < 1) ||
	    (pi->westwicted_wevews == 3))
		w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_HIGH, twue);
}

static void wv6xx_enabwe_medium(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	if (pi->westwicted_wevews < 2)
		w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_MEDIUM, twue);
}

static void wv6xx_set_dpm_event_souwces(stwuct wadeon_device *wdev, u32 souwces)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);
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

static void wv6xx_enabwe_auto_thwottwe_souwce(stwuct wadeon_device *wdev,
					      enum wadeon_dpm_auto_thwottwe_swc souwce,
					      boow enabwe)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	if (enabwe) {
		if (!(pi->active_auto_thwottwe_souwces & (1 << souwce))) {
			pi->active_auto_thwottwe_souwces |= 1 << souwce;
			wv6xx_set_dpm_event_souwces(wdev, pi->active_auto_thwottwe_souwces);
		}
	} ewse {
		if (pi->active_auto_thwottwe_souwces & (1 << souwce)) {
			pi->active_auto_thwottwe_souwces &= ~(1 << souwce);
			wv6xx_set_dpm_event_souwces(wdev, pi->active_auto_thwottwe_souwces);
		}
	}
}


static void wv6xx_enabwe_thewmaw_pwotection(stwuct wadeon_device *wdev,
					    boow enabwe)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	if (pi->active_auto_thwottwe_souwces)
		w600_enabwe_thewmaw_pwotection(wdev, enabwe);
}

static void wv6xx_genewate_twansition_stepping(stwuct wadeon_device *wdev,
					       stwuct wadeon_ps *new_ps,
					       stwuct wadeon_ps *owd_ps)
{
	stwuct wv6xx_ps *new_state = wv6xx_get_ps(new_ps);
	stwuct wv6xx_ps *owd_state = wv6xx_get_ps(owd_ps);
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	wv6xx_genewate_steps(wdev,
			     owd_state->wow.scwk,
			     new_state->wow.scwk,
			     0, &pi->hw.medium_scwk_index);
}

static void wv6xx_genewate_wow_step(stwuct wadeon_device *wdev,
				    stwuct wadeon_ps *new_ps)
{
	stwuct wv6xx_ps *new_state = wv6xx_get_ps(new_ps);
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	pi->hw.wow_scwk_index = 0;
	wv6xx_genewate_singwe_step(wdev,
				   new_state->wow.scwk,
				   0);
}

static void wv6xx_invawidate_intewmediate_steps(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	wv6xx_invawidate_intewmediate_steps_wange(wdev, 0,
						  pi->hw.medium_scwk_index);
}

static void wv6xx_genewate_stepping_tabwe(stwuct wadeon_device *wdev,
					  stwuct wadeon_ps *new_ps)
{
	stwuct wv6xx_ps *new_state = wv6xx_get_ps(new_ps);
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	pi->hw.wow_scwk_index = 0;

	wv6xx_genewate_steps(wdev,
			     new_state->wow.scwk,
			     new_state->medium.scwk,
			     0,
			     &pi->hw.medium_scwk_index);
	wv6xx_genewate_steps(wdev,
			     new_state->medium.scwk,
			     new_state->high.scwk,
			     pi->hw.medium_scwk_index,
			     &pi->hw.high_scwk_index);
}

static void wv6xx_enabwe_spwead_spectwum(stwuct wadeon_device *wdev,
					 boow enabwe)
{
	if (enabwe)
		wv6xx_enabwe_dynamic_spwead_spectwum(wdev, twue);
	ewse {
		wv6xx_enabwe_engine_spwead_spectwum(wdev, W600_POWEW_WEVEW_WOW, fawse);
		wv6xx_enabwe_engine_spwead_spectwum(wdev, W600_POWEW_WEVEW_MEDIUM, fawse);
		wv6xx_enabwe_engine_spwead_spectwum(wdev, W600_POWEW_WEVEW_HIGH, fawse);
		wv6xx_enabwe_dynamic_spwead_spectwum(wdev, fawse);
		wv6xx_enabwe_memowy_spwead_spectwum(wdev, fawse);
	}
}

static void wv6xx_weset_wvtm_data_sync(stwuct wadeon_device *wdev)
{
	if (ASIC_IS_DCE3(wdev))
		WWEG32_P(DCE3_WVTMA_DATA_SYNCHWONIZATION, WVTMA_PFWEQCHG, ~WVTMA_PFWEQCHG);
	ewse
		WWEG32_P(WVTMA_DATA_SYNCHWONIZATION, WVTMA_PFWEQCHG, ~WVTMA_PFWEQCHG);
}

static void wv6xx_enabwe_dynamic_pcie_gen2(stwuct wadeon_device *wdev,
					   stwuct wadeon_ps *new_ps,
					   boow enabwe)
{
	stwuct wv6xx_ps *new_state = wv6xx_get_ps(new_ps);

	if (enabwe) {
		wv6xx_enabwe_bif_dynamic_pcie_gen2(wdev, twue);
		wv6xx_enabwe_pcie_gen2_suppowt(wdev);
		w600_enabwe_dynamic_pcie_gen2(wdev, twue);
	} ewse {
		if (!(new_state->wow.fwags & ATOM_PPWIB_W600_FWAGS_PCIEGEN2))
			wv6xx_fowce_pcie_gen1(wdev);
		wv6xx_enabwe_bif_dynamic_pcie_gen2(wdev, fawse);
		w600_enabwe_dynamic_pcie_gen2(wdev, fawse);
	}
}

static void wv6xx_set_uvd_cwock_befowe_set_eng_cwock(stwuct wadeon_device *wdev,
						     stwuct wadeon_ps *new_ps,
						     stwuct wadeon_ps *owd_ps)
{
	stwuct wv6xx_ps *new_state = wv6xx_get_ps(new_ps);
	stwuct wv6xx_ps *cuwwent_state = wv6xx_get_ps(owd_ps);

	if ((new_ps->vcwk == owd_ps->vcwk) &&
	    (new_ps->dcwk == owd_ps->dcwk))
		wetuwn;

	if (new_state->high.scwk >= cuwwent_state->high.scwk)
		wetuwn;

	wadeon_set_uvd_cwocks(wdev, new_ps->vcwk, new_ps->dcwk);
}

static void wv6xx_set_uvd_cwock_aftew_set_eng_cwock(stwuct wadeon_device *wdev,
						    stwuct wadeon_ps *new_ps,
						    stwuct wadeon_ps *owd_ps)
{
	stwuct wv6xx_ps *new_state = wv6xx_get_ps(new_ps);
	stwuct wv6xx_ps *cuwwent_state = wv6xx_get_ps(owd_ps);

	if ((new_ps->vcwk == owd_ps->vcwk) &&
	    (new_ps->dcwk == owd_ps->dcwk))
		wetuwn;

	if (new_state->high.scwk < cuwwent_state->high.scwk)
		wetuwn;

	wadeon_set_uvd_cwocks(wdev, new_ps->vcwk, new_ps->dcwk);
}

int wv6xx_dpm_enabwe(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);
	stwuct wadeon_ps *boot_ps = wdev->pm.dpm.boot_ps;

	if (w600_dynamicpm_enabwed(wdev))
		wetuwn -EINVAW;

	if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_BACKBIAS)
		wv6xx_enabwe_backbias(wdev, twue);

	if (pi->dynamic_ss)
		wv6xx_enabwe_spwead_spectwum(wdev, twue);

	wv6xx_pwogwam_mpww_timing_pawametews(wdev);
	wv6xx_pwogwam_bsp(wdev);
	wv6xx_pwogwam_git(wdev);
	wv6xx_pwogwam_tp(wdev);
	wv6xx_pwogwam_tpp(wdev);
	wv6xx_pwogwam_sstp(wdev);
	wv6xx_pwogwam_fcp(wdev);
	wv6xx_pwogwam_vddc3d_pawametews(wdev);
	wv6xx_pwogwam_vowtage_timing_pawametews(wdev);
	wv6xx_pwogwam_engine_speed_pawametews(wdev);

	wv6xx_enabwe_dispway_gap(wdev, twue);
	if (pi->dispway_gap == fawse)
		wv6xx_enabwe_dispway_gap(wdev, fawse);

	wv6xx_pwogwam_powew_wevew_entew_state(wdev);

	wv6xx_cawcuwate_stepping_pawametews(wdev, boot_ps);

	if (pi->vowtage_contwow)
		wv6xx_pwogwam_vowtage_gpio_pins(wdev);

	wv6xx_genewate_stepping_tabwe(wdev, boot_ps);

	wv6xx_pwogwam_stepping_pawametews_except_wowest_entwy(wdev);
	wv6xx_pwogwam_stepping_pawametews_wowest_entwy(wdev);

	wv6xx_pwogwam_powew_wevew_wow(wdev);
	wv6xx_pwogwam_powew_wevew_medium(wdev);
	wv6xx_pwogwam_powew_wevew_high(wdev);
	wv6xx_pwogwam_vc(wdev);
	wv6xx_pwogwam_at(wdev);

	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_WOW, twue);
	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_MEDIUM, twue);
	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_HIGH, twue);

	wv6xx_enabwe_auto_thwottwe_souwce(wdev, WADEON_DPM_AUTO_THWOTTWE_SWC_THEWMAW, twue);

	w600_stawt_dpm(wdev);

	if (pi->vowtage_contwow)
		wv6xx_enabwe_static_vowtage_contwow(wdev, boot_ps, fawse);

	if (pi->dynamic_pcie_gen2)
		wv6xx_enabwe_dynamic_pcie_gen2(wdev, boot_ps, twue);

	if (pi->gfx_cwock_gating)
		w600_gfx_cwockgating_enabwe(wdev, twue);

	wetuwn 0;
}

void wv6xx_dpm_disabwe(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);
	stwuct wadeon_ps *boot_ps = wdev->pm.dpm.boot_ps;

	if (!w600_dynamicpm_enabwed(wdev))
		wetuwn;

	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_WOW, twue);
	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_MEDIUM, twue);
	wv6xx_enabwe_dispway_gap(wdev, fawse);
	wv6xx_cweaw_vc(wdev);
	w600_set_at(wdev, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);

	if (pi->thewmaw_pwotection)
		w600_enabwe_thewmaw_pwotection(wdev, fawse);

	w600_wait_fow_powew_wevew(wdev, W600_POWEW_WEVEW_WOW);
	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_HIGH, fawse);
	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_MEDIUM, fawse);

	if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_BACKBIAS)
		wv6xx_enabwe_backbias(wdev, fawse);

	wv6xx_enabwe_spwead_spectwum(wdev, fawse);

	if (pi->vowtage_contwow)
		wv6xx_enabwe_static_vowtage_contwow(wdev, boot_ps, twue);

	if (pi->dynamic_pcie_gen2)
		wv6xx_enabwe_dynamic_pcie_gen2(wdev, boot_ps, fawse);

	if (wdev->iwq.instawwed &&
	    w600_is_intewnaw_thewmaw_sensow(wdev->pm.int_thewmaw_type)) {
		wdev->iwq.dpm_thewmaw = fawse;
		wadeon_iwq_set(wdev);
	}

	if (pi->gfx_cwock_gating)
		w600_gfx_cwockgating_enabwe(wdev, fawse);

	w600_stop_dpm(wdev);
}

int wv6xx_dpm_set_powew_state(stwuct wadeon_device *wdev)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);
	stwuct wadeon_ps *new_ps = wdev->pm.dpm.wequested_ps;
	stwuct wadeon_ps *owd_ps = wdev->pm.dpm.cuwwent_ps;
	int wet;

	pi->westwicted_wevews = 0;

	wv6xx_set_uvd_cwock_befowe_set_eng_cwock(wdev, new_ps, owd_ps);

	wv6xx_cweaw_vc(wdev);
	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_WOW, twue);
	w600_set_at(wdev, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);

	if (pi->thewmaw_pwotection)
		w600_enabwe_thewmaw_pwotection(wdev, fawse);

	w600_wait_fow_powew_wevew(wdev, W600_POWEW_WEVEW_WOW);
	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_HIGH, fawse);
	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_MEDIUM, fawse);

	wv6xx_genewate_twansition_stepping(wdev, new_ps, owd_ps);
	wv6xx_pwogwam_powew_wevew_medium_fow_twansition(wdev);

	if (pi->vowtage_contwow) {
		wv6xx_set_sw_vowtage_to_safe(wdev, new_ps, owd_ps);
		if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_STEPVDDC)
			wv6xx_set_sw_vowtage_to_wow(wdev, owd_ps);
	}

	if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_BACKBIAS)
		wv6xx_set_safe_backbias(wdev, new_ps, owd_ps);

	if (pi->dynamic_pcie_gen2)
		wv6xx_set_safe_pcie_gen2(wdev, new_ps, owd_ps);

	if (pi->vowtage_contwow)
		wv6xx_enabwe_dynamic_vowtage_contwow(wdev, fawse);

	if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_BACKBIAS)
		wv6xx_enabwe_dynamic_backbias_contwow(wdev, fawse);

	if (pi->vowtage_contwow) {
		if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_STEPVDDC)
			wv6xx_step_vowtage_if_incweasing(wdev, new_ps, owd_ps);
		msweep((wdev->pm.dpm.vowtage_wesponse_time + 999) / 1000);
	}

	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_MEDIUM, twue);
	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_WOW, fawse);
	w600_wait_fow_powew_wevew_unequaw(wdev, W600_POWEW_WEVEW_WOW);

	wv6xx_genewate_wow_step(wdev, new_ps);
	wv6xx_invawidate_intewmediate_steps(wdev);
	wv6xx_cawcuwate_stepping_pawametews(wdev, new_ps);
	wv6xx_pwogwam_stepping_pawametews_wowest_entwy(wdev);
	wv6xx_pwogwam_powew_wevew_wow_to_wowest_state(wdev);

	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_WOW, twue);
	w600_wait_fow_powew_wevew(wdev, W600_POWEW_WEVEW_WOW);
	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_MEDIUM, fawse);

	if (pi->vowtage_contwow) {
		if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_STEPVDDC) {
			wet = wv6xx_step_vowtage_if_decweasing(wdev, new_ps, owd_ps);
			if (wet)
				wetuwn wet;
		}
		wv6xx_enabwe_dynamic_vowtage_contwow(wdev, twue);
	}

	if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_BACKBIAS)
		wv6xx_enabwe_dynamic_backbias_contwow(wdev, twue);

	if (pi->dynamic_pcie_gen2)
		wv6xx_enabwe_dynamic_pcie_gen2(wdev, new_ps, twue);

	wv6xx_weset_wvtm_data_sync(wdev);

	wv6xx_genewate_stepping_tabwe(wdev, new_ps);
	wv6xx_pwogwam_stepping_pawametews_except_wowest_entwy(wdev);
	wv6xx_pwogwam_powew_wevew_wow(wdev);
	wv6xx_pwogwam_powew_wevew_medium(wdev);
	wv6xx_pwogwam_powew_wevew_high(wdev);
	wv6xx_enabwe_medium(wdev);
	wv6xx_enabwe_high(wdev);

	if (pi->thewmaw_pwotection)
		wv6xx_enabwe_thewmaw_pwotection(wdev, twue);
	wv6xx_pwogwam_vc(wdev);
	wv6xx_pwogwam_at(wdev);

	wv6xx_set_uvd_cwock_aftew_set_eng_cwock(wdev, new_ps, owd_ps);

	wetuwn 0;
}

void wv6xx_setup_asic(stwuct wadeon_device *wdev)
{
	w600_enabwe_acpi_pm(wdev);

	if (wadeon_aspm != 0) {
		if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_ASPM_W0s)
			wv6xx_enabwe_w0s(wdev);
		if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_ASPM_W1)
			wv6xx_enabwe_w1(wdev);
		if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_TUWNOFFPWW_ASPMW1)
			wv6xx_enabwe_pww_sweep_in_w1(wdev);
	}
}

void wv6xx_dpm_dispway_configuwation_changed(stwuct wadeon_device *wdev)
{
	wv6xx_pwogwam_dispway_gap(wdev);
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

static void wv6xx_pawse_ppwib_non_cwock_info(stwuct wadeon_device *wdev,
					     stwuct wadeon_ps *wps,
					     stwuct _ATOM_PPWIB_NONCWOCK_INFO *non_cwock_info)
{
	wps->caps = we32_to_cpu(non_cwock_info->uwCapsAndSettings);
	wps->cwass = we16_to_cpu(non_cwock_info->usCwassification);
	wps->cwass2 = we16_to_cpu(non_cwock_info->usCwassification2);

	if (w600_is_uvd_state(wps->cwass, wps->cwass2)) {
		wps->vcwk = WV6XX_DEFAUWT_VCWK_FWEQ;
		wps->dcwk = WV6XX_DEFAUWT_DCWK_FWEQ;
	} ewse {
		wps->vcwk = 0;
		wps->dcwk = 0;
	}

	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_BOOT)
		wdev->pm.dpm.boot_ps = wps;
	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_UVDSTATE)
		wdev->pm.dpm.uvd_ps = wps;
}

static void wv6xx_pawse_ppwib_cwock_info(stwuct wadeon_device *wdev,
					 stwuct wadeon_ps *wps, int index,
					 union ppwib_cwock_info *cwock_info)
{
	stwuct wv6xx_ps *ps = wv6xx_get_ps(wps);
	u32 scwk, mcwk;
	u16 vddc;
	stwuct wv6xx_pw *pw;

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

	scwk = we16_to_cpu(cwock_info->w600.usEngineCwockWow);
	scwk |= cwock_info->w600.ucEngineCwockHigh << 16;
	mcwk = we16_to_cpu(cwock_info->w600.usMemowyCwockWow);
	mcwk |= cwock_info->w600.ucMemowyCwockHigh << 16;

	pw->mcwk = mcwk;
	pw->scwk = scwk;
	pw->vddc = we16_to_cpu(cwock_info->w600.usVDDC);
	pw->fwags = we32_to_cpu(cwock_info->w600.uwFwags);

	/* patch up vddc if necessawy */
	if (pw->vddc == 0xff01) {
		if (wadeon_atom_get_max_vddc(wdev, 0, 0, &vddc) == 0)
			pw->vddc = vddc;
	}

	/* fix up pcie gen2 */
	if (pw->fwags & ATOM_PPWIB_W600_FWAGS_PCIEGEN2) {
		if ((wdev->famiwy == CHIP_WV610) || (wdev->famiwy == CHIP_WV630)) {
			if (pw->vddc < 1100)
				pw->fwags &= ~ATOM_PPWIB_W600_FWAGS_PCIEGEN2;
		}
	}

	/* patch up boot state */
	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_BOOT) {
		u16 vddc, vddci, mvdd;
		wadeon_atombios_get_defauwt_vowtages(wdev, &vddc, &vddci, &mvdd);
		pw->mcwk = wdev->cwock.defauwt_mcwk;
		pw->scwk = wdev->cwock.defauwt_scwk;
		pw->vddc = vddc;
	}
}

static int wv6xx_pawse_powew_tabwe(stwuct wadeon_device *wdev)
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
	stwuct wv6xx_ps *ps;

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
			ps = kzawwoc(sizeof(stwuct wv6xx_ps), GFP_KEWNEW);
			if (ps == NUWW) {
				kfwee(wdev->pm.dpm.ps);
				wetuwn -ENOMEM;
			}
			wdev->pm.dpm.ps[i].ps_pwiv = ps;
			wv6xx_pawse_ppwib_non_cwock_info(wdev, &wdev->pm.dpm.ps[i],
							 non_cwock_info);
			idx = (u8 *)&powew_state->v1.ucCwockStateIndices[0];
			fow (j = 0; j < (powew_info->ppwib.ucStateEntwySize - 1); j++) {
				cwock_info = (union ppwib_cwock_info *)
					(mode_info->atom_context->bios + data_offset +
					 we16_to_cpu(powew_info->ppwib.usCwockInfoAwwayOffset) +
					 (idx[j] * powew_info->ppwib.ucCwockInfoSize));
				wv6xx_pawse_ppwib_cwock_info(wdev,
							     &wdev->pm.dpm.ps[i], j,
							     cwock_info);
			}
		}
	}
	wdev->pm.dpm.num_ps = powew_info->ppwib.ucNumStates;
	wetuwn 0;
}

int wv6xx_dpm_init(stwuct wadeon_device *wdev)
{
	stwuct wadeon_atom_ss ss;
	stwuct atom_cwock_dividews dividews;
	stwuct wv6xx_powew_info *pi;
	int wet;

	pi = kzawwoc(sizeof(stwuct wv6xx_powew_info), GFP_KEWNEW);
	if (pi == NUWW)
		wetuwn -ENOMEM;
	wdev->pm.dpm.pwiv = pi;

	wet = w600_get_pwatfowm_caps(wdev);
	if (wet)
		wetuwn wet;

	wet = wv6xx_pawse_powew_tabwe(wdev);
	if (wet)
		wetuwn wet;

	if (wdev->pm.dpm.vowtage_wesponse_time == 0)
		wdev->pm.dpm.vowtage_wesponse_time = W600_VOWTAGEWESPONSETIME_DFWT;
	if (wdev->pm.dpm.backbias_wesponse_time == 0)
		wdev->pm.dpm.backbias_wesponse_time = W600_BACKBIASWESPONSETIME_DFWT;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
					     0, fawse, &dividews);
	if (wet)
		pi->spww_wef_div = dividews.wef_div + 1;
	ewse
		pi->spww_wef_div = W600_WEFEWENCEDIVIDEW_DFWT;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_MEMOWY_PWW_PAWAM,
					     0, fawse, &dividews);
	if (wet)
		pi->mpww_wef_div = dividews.wef_div + 1;
	ewse
		pi->mpww_wef_div = W600_WEFEWENCEDIVIDEW_DFWT;

	if (wdev->famiwy >= CHIP_WV670)
		pi->fb_div_scawe = 1;
	ewse
		pi->fb_div_scawe = 0;

	pi->vowtage_contwow =
		wadeon_atom_is_vowtage_gpio(wdev, SET_VOWTAGE_TYPE_ASIC_VDDC, 0);

	pi->gfx_cwock_gating = twue;

	pi->scwk_ss = wadeon_atombios_get_asic_ss_info(wdev, &ss,
						       ASIC_INTEWNAW_ENGINE_SS, 0);
	pi->mcwk_ss = wadeon_atombios_get_asic_ss_info(wdev, &ss,
						       ASIC_INTEWNAW_MEMOWY_SS, 0);

	/* Disabwe scwk ss, causes hangs on a wot of systems */
	pi->scwk_ss = fawse;

	if (pi->scwk_ss || pi->mcwk_ss)
		pi->dynamic_ss = twue;
	ewse
		pi->dynamic_ss = fawse;

	pi->dynamic_pcie_gen2 = twue;

	if (pi->gfx_cwock_gating &&
	    (wdev->pm.int_thewmaw_type != THEWMAW_TYPE_NONE))
		pi->thewmaw_pwotection = twue;
	ewse
		pi->thewmaw_pwotection = fawse;

	pi->dispway_gap = twue;

	wetuwn 0;
}

void wv6xx_dpm_pwint_powew_state(stwuct wadeon_device *wdev,
				 stwuct wadeon_ps *wps)
{
	stwuct wv6xx_ps *ps = wv6xx_get_ps(wps);
	stwuct wv6xx_pw *pw;

	w600_dpm_pwint_cwass_info(wps->cwass, wps->cwass2);
	w600_dpm_pwint_cap_info(wps->caps);
	pwintk("\tuvd    vcwk: %d dcwk: %d\n", wps->vcwk, wps->dcwk);
	pw = &ps->wow;
	pwintk("\t\tpowew wevew 0    scwk: %u mcwk: %u vddc: %u\n",
	       pw->scwk, pw->mcwk, pw->vddc);
	pw = &ps->medium;
	pwintk("\t\tpowew wevew 1    scwk: %u mcwk: %u vddc: %u\n",
	       pw->scwk, pw->mcwk, pw->vddc);
	pw = &ps->high;
	pwintk("\t\tpowew wevew 2    scwk: %u mcwk: %u vddc: %u\n",
	       pw->scwk, pw->mcwk, pw->vddc);
	w600_dpm_pwint_ps_status(wdev, wps);
}

void wv6xx_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct wadeon_device *wdev,
						       stwuct seq_fiwe *m)
{
	stwuct wadeon_ps *wps = wdev->pm.dpm.cuwwent_ps;
	stwuct wv6xx_ps *ps = wv6xx_get_ps(wps);
	stwuct wv6xx_pw *pw;
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
		seq_pwintf(m, "powew wevew %d    scwk: %u mcwk: %u vddc: %u\n",
			   cuwwent_index, pw->scwk, pw->mcwk, pw->vddc);
	}
}

/* get the cuwwent scwk in 10 khz units */
u32 wv6xx_dpm_get_cuwwent_scwk(stwuct wadeon_device *wdev)
{
	stwuct wadeon_ps *wps = wdev->pm.dpm.cuwwent_ps;
	stwuct wv6xx_ps *ps = wv6xx_get_ps(wps);
	stwuct wv6xx_pw *pw;
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
		wetuwn pw->scwk;
	}
}

/* get the cuwwent mcwk in 10 khz units */
u32 wv6xx_dpm_get_cuwwent_mcwk(stwuct wadeon_device *wdev)
{
	stwuct wadeon_ps *wps = wdev->pm.dpm.cuwwent_ps;
	stwuct wv6xx_ps *ps = wv6xx_get_ps(wps);
	stwuct wv6xx_pw *pw;
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
		wetuwn pw->mcwk;
	}
}

void wv6xx_dpm_fini(stwuct wadeon_device *wdev)
{
	int i;

	fow (i = 0; i < wdev->pm.dpm.num_ps; i++) {
		kfwee(wdev->pm.dpm.ps[i].ps_pwiv);
	}
	kfwee(wdev->pm.dpm.ps);
	kfwee(wdev->pm.dpm.pwiv);
}

u32 wv6xx_dpm_get_scwk(stwuct wadeon_device *wdev, boow wow)
{
	stwuct wv6xx_ps *wequested_state = wv6xx_get_ps(wdev->pm.dpm.wequested_ps);

	if (wow)
		wetuwn wequested_state->wow.scwk;
	ewse
		wetuwn wequested_state->high.scwk;
}

u32 wv6xx_dpm_get_mcwk(stwuct wadeon_device *wdev, boow wow)
{
	stwuct wv6xx_ps *wequested_state = wv6xx_get_ps(wdev->pm.dpm.wequested_ps);

	if (wow)
		wetuwn wequested_state->wow.mcwk;
	ewse
		wetuwn wequested_state->high.mcwk;
}

int wv6xx_dpm_fowce_pewfowmance_wevew(stwuct wadeon_device *wdev,
				      enum wadeon_dpm_fowced_wevew wevew)
{
	stwuct wv6xx_powew_info *pi = wv6xx_get_pi(wdev);

	if (wevew == WADEON_DPM_FOWCED_WEVEW_HIGH) {
		pi->westwicted_wevews = 3;
	} ewse if (wevew == WADEON_DPM_FOWCED_WEVEW_WOW) {
		pi->westwicted_wevews = 2;
	} ewse {
		pi->westwicted_wevews = 0;
	}

	wv6xx_cweaw_vc(wdev);
	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_WOW, twue);
	w600_set_at(wdev, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
	w600_wait_fow_powew_wevew(wdev, W600_POWEW_WEVEW_WOW);
	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_HIGH, fawse);
	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_MEDIUM, fawse);
	wv6xx_enabwe_medium(wdev);
	wv6xx_enabwe_high(wdev);
	if (pi->westwicted_wevews == 3)
		w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_WOW, fawse);
	wv6xx_pwogwam_vc(wdev);
	wv6xx_pwogwam_at(wdev);

	wdev->pm.dpm.fowced_wevew = wevew;

	wetuwn 0;
}
