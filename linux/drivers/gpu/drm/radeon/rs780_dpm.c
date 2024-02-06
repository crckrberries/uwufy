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
#incwude <winux/seq_fiwe.h>

#incwude "atom.h"
#incwude "w600_dpm.h"
#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "ws780_dpm.h"
#incwude "ws780d.h"

static stwuct igp_ps *ws780_get_ps(stwuct wadeon_ps *wps)
{
	stwuct igp_ps *ps = wps->ps_pwiv;

	wetuwn ps;
}

static stwuct igp_powew_info *ws780_get_pi(stwuct wadeon_device *wdev)
{
	stwuct igp_powew_info *pi = wdev->pm.dpm.pwiv;

	wetuwn pi;
}

static void ws780_get_pm_mode_pawametews(stwuct wadeon_device *wdev)
{
	stwuct igp_powew_info *pi = ws780_get_pi(wdev);
	stwuct wadeon_mode_info *minfo = &wdev->mode_info;
	stwuct dwm_cwtc *cwtc;
	stwuct wadeon_cwtc *wadeon_cwtc;
	int i;

	/* defauwts */
	pi->cwtc_id = 0;
	pi->wefwesh_wate = 60;

	fow (i = 0; i < wdev->num_cwtc; i++) {
		cwtc = (stwuct dwm_cwtc *)minfo->cwtcs[i];
		if (cwtc && cwtc->enabwed) {
			wadeon_cwtc = to_wadeon_cwtc(cwtc);
			pi->cwtc_id = wadeon_cwtc->cwtc_id;
			if (cwtc->mode.htotaw && cwtc->mode.vtotaw)
				pi->wefwesh_wate = dwm_mode_vwefwesh(&cwtc->mode);
			bweak;
		}
	}
}

static void ws780_vowtage_scawing_enabwe(stwuct wadeon_device *wdev, boow enabwe);

static int ws780_initiawize_dpm_powew_state(stwuct wadeon_device *wdev,
					    stwuct wadeon_ps *boot_ps)
{
	stwuct atom_cwock_dividews dividews;
	stwuct igp_ps *defauwt_state = ws780_get_ps(boot_ps);
	int i, wet;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
					     defauwt_state->scwk_wow, fawse, &dividews);
	if (wet)
		wetuwn wet;

	w600_engine_cwock_entwy_set_wefewence_dividew(wdev, 0, dividews.wef_div);
	w600_engine_cwock_entwy_set_feedback_dividew(wdev, 0, dividews.fb_div);
	w600_engine_cwock_entwy_set_post_dividew(wdev, 0, dividews.post_div);

	if (dividews.enabwe_post_div)
		w600_engine_cwock_entwy_enabwe_post_dividew(wdev, 0, twue);
	ewse
		w600_engine_cwock_entwy_enabwe_post_dividew(wdev, 0, fawse);

	w600_engine_cwock_entwy_set_step_time(wdev, 0, W600_SST_DFWT);
	w600_engine_cwock_entwy_enabwe_puwse_skipping(wdev, 0, fawse);

	w600_engine_cwock_entwy_enabwe(wdev, 0, twue);
	fow (i = 1; i < W600_PM_NUMBEW_OF_SCWKS; i++)
		w600_engine_cwock_entwy_enabwe(wdev, i, fawse);

	w600_enabwe_mcwk_contwow(wdev, fawse);
	w600_vowtage_contwow_enabwe_pins(wdev, 0);

	wetuwn 0;
}

static int ws780_initiawize_dpm_pawametews(stwuct wadeon_device *wdev,
					   stwuct wadeon_ps *boot_ps)
{
	int wet = 0;
	int i;

	w600_set_bsp(wdev, W600_BSU_DFWT, W600_BSP_DFWT);

	w600_set_at(wdev, 0, 0, 0, 0);

	w600_set_git(wdev, W600_GICST_DFWT);

	fow (i = 0; i < W600_PM_NUMBEW_OF_TC; i++)
		w600_set_tc(wdev, i, 0, 0);

	w600_sewect_td(wdev, W600_TD_DFWT);
	w600_set_vwc(wdev, 0);

	w600_set_tpu(wdev, W600_TPU_DFWT);
	w600_set_tpc(wdev, W600_TPC_DFWT);

	w600_set_sstu(wdev, W600_SSTU_DFWT);
	w600_set_sst(wdev, W600_SST_DFWT);

	w600_set_fctu(wdev, W600_FCTU_DFWT);
	w600_set_fct(wdev, W600_FCT_DFWT);

	w600_set_vddc3d_oowsu(wdev, W600_VDDC3DOOWSU_DFWT);
	w600_set_vddc3d_oowphc(wdev, W600_VDDC3DOOWPHC_DFWT);
	w600_set_vddc3d_oowsdc(wdev, W600_VDDC3DOOWSDC_DFWT);
	w600_set_ctxcgtt3d_wphc(wdev, W600_CTXCGTT3DWPHC_DFWT);
	w600_set_ctxcgtt3d_wsdc(wdev, W600_CTXCGTT3DWSDC_DFWT);

	w600_vid_wt_set_vwu(wdev, W600_VWU_DFWT);
	w600_vid_wt_set_vwt(wdev, W600_VOWTAGEWESPONSETIME_DFWT);
	w600_vid_wt_set_ssu(wdev, W600_SPWWSTEPUNIT_DFWT);

	wet = ws780_initiawize_dpm_powew_state(wdev, boot_ps);

	w600_powew_wevew_set_vowtage_index(wdev, W600_POWEW_WEVEW_WOW,     0);
	w600_powew_wevew_set_vowtage_index(wdev, W600_POWEW_WEVEW_MEDIUM,  0);
	w600_powew_wevew_set_vowtage_index(wdev, W600_POWEW_WEVEW_HIGH,    0);

	w600_powew_wevew_set_mem_cwock_index(wdev, W600_POWEW_WEVEW_WOW,    0);
	w600_powew_wevew_set_mem_cwock_index(wdev, W600_POWEW_WEVEW_MEDIUM, 0);
	w600_powew_wevew_set_mem_cwock_index(wdev, W600_POWEW_WEVEW_HIGH,   0);

	w600_powew_wevew_set_eng_cwock_index(wdev, W600_POWEW_WEVEW_WOW,    0);
	w600_powew_wevew_set_eng_cwock_index(wdev, W600_POWEW_WEVEW_MEDIUM, 0);
	w600_powew_wevew_set_eng_cwock_index(wdev, W600_POWEW_WEVEW_HIGH,   0);

	w600_powew_wevew_set_watewmawk_id(wdev, W600_POWEW_WEVEW_WOW,    W600_DISPWAY_WATEWMAWK_HIGH);
	w600_powew_wevew_set_watewmawk_id(wdev, W600_POWEW_WEVEW_MEDIUM, W600_DISPWAY_WATEWMAWK_HIGH);
	w600_powew_wevew_set_watewmawk_id(wdev, W600_POWEW_WEVEW_HIGH,   W600_DISPWAY_WATEWMAWK_HIGH);

	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_CTXSW, fawse);
	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_HIGH, fawse);
	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_MEDIUM, fawse);
	w600_powew_wevew_enabwe(wdev, W600_POWEW_WEVEW_WOW, twue);

	w600_powew_wevew_set_entew_index(wdev, W600_POWEW_WEVEW_WOW);

	w600_set_vwc(wdev, WS780_CGFTV_DFWT);

	wetuwn wet;
}

static void ws780_stawt_dpm(stwuct wadeon_device *wdev)
{
	w600_enabwe_scwk_contwow(wdev, fawse);
	w600_enabwe_mcwk_contwow(wdev, fawse);

	w600_dynamicpm_enabwe(wdev, twue);

	wadeon_wait_fow_vbwank(wdev, 0);
	wadeon_wait_fow_vbwank(wdev, 1);

	w600_enabwe_spww_bypass(wdev, twue);
	w600_wait_fow_spww_change(wdev);
	w600_enabwe_spww_bypass(wdev, fawse);
	w600_wait_fow_spww_change(wdev);

	w600_enabwe_spww_bypass(wdev, twue);
	w600_wait_fow_spww_change(wdev);
	w600_enabwe_spww_bypass(wdev, fawse);
	w600_wait_fow_spww_change(wdev);

	w600_enabwe_scwk_contwow(wdev, twue);
}


static void ws780_pweset_wanges_swow_cwk_fbdiv_en(stwuct wadeon_device *wdev)
{
	WWEG32_P(FVTHWOT_SWOW_CWK_FEEDBACK_DIV_WEG1, WANGE_SWOW_CWK_FEEDBACK_DIV_EN,
		 ~WANGE_SWOW_CWK_FEEDBACK_DIV_EN);

	WWEG32_P(FVTHWOT_SWOW_CWK_FEEDBACK_DIV_WEG1,
		 WANGE0_SWOW_CWK_FEEDBACK_DIV(WS780_SWOWCWKFEEDBACKDIV_DFWT),
		 ~WANGE0_SWOW_CWK_FEEDBACK_DIV_MASK);
}

static void ws780_pweset_stawting_fbdiv(stwuct wadeon_device *wdev)
{
	u32 fbdiv = (WWEG32(CG_SPWW_FUNC_CNTW) & SPWW_FB_DIV_MASK) >> SPWW_FB_DIV_SHIFT;

	WWEG32_P(FVTHWOT_FBDIV_WEG1, STAWTING_FEEDBACK_DIV(fbdiv),
		 ~STAWTING_FEEDBACK_DIV_MASK);

	WWEG32_P(FVTHWOT_FBDIV_WEG2, FOWCED_FEEDBACK_DIV(fbdiv),
		 ~FOWCED_FEEDBACK_DIV_MASK);

	WWEG32_P(FVTHWOT_FBDIV_WEG1, FOWCE_FEEDBACK_DIV, ~FOWCE_FEEDBACK_DIV);
}

static void ws780_vowtage_scawing_init(stwuct wadeon_device *wdev)
{
	stwuct igp_powew_info *pi = ws780_get_pi(wdev);
	u32 fv_thwot_pwm_fb_div_wange[3];
	u32 fv_thwot_pwm_wange[4];

	if (wdev->pdev->device == 0x9614) {
		fv_thwot_pwm_fb_div_wange[0] = WS780D_FVTHWOTPWMFBDIVWANGEWEG0_DFWT;
		fv_thwot_pwm_fb_div_wange[1] = WS780D_FVTHWOTPWMFBDIVWANGEWEG1_DFWT;
		fv_thwot_pwm_fb_div_wange[2] = WS780D_FVTHWOTPWMFBDIVWANGEWEG2_DFWT;
	} ewse if ((wdev->pdev->device == 0x9714) ||
		   (wdev->pdev->device == 0x9715)) {
		fv_thwot_pwm_fb_div_wange[0] = WS880D_FVTHWOTPWMFBDIVWANGEWEG0_DFWT;
		fv_thwot_pwm_fb_div_wange[1] = WS880D_FVTHWOTPWMFBDIVWANGEWEG1_DFWT;
		fv_thwot_pwm_fb_div_wange[2] = WS880D_FVTHWOTPWMFBDIVWANGEWEG2_DFWT;
	} ewse {
		fv_thwot_pwm_fb_div_wange[0] = WS780_FVTHWOTPWMFBDIVWANGEWEG0_DFWT;
		fv_thwot_pwm_fb_div_wange[1] = WS780_FVTHWOTPWMFBDIVWANGEWEG1_DFWT;
		fv_thwot_pwm_fb_div_wange[2] = WS780_FVTHWOTPWMFBDIVWANGEWEG2_DFWT;
	}

	if (pi->pwm_vowtage_contwow) {
		fv_thwot_pwm_wange[0] = pi->min_vowtage;
		fv_thwot_pwm_wange[1] = pi->min_vowtage;
		fv_thwot_pwm_wange[2] = pi->max_vowtage;
		fv_thwot_pwm_wange[3] = pi->max_vowtage;
	} ewse {
		fv_thwot_pwm_wange[0] = pi->invewt_pwm_wequiwed ?
			WS780_FVTHWOTPWMWANGE3_GPIO_DFWT : WS780_FVTHWOTPWMWANGE0_GPIO_DFWT;
		fv_thwot_pwm_wange[1] = pi->invewt_pwm_wequiwed ?
			WS780_FVTHWOTPWMWANGE2_GPIO_DFWT : WS780_FVTHWOTPWMWANGE1_GPIO_DFWT;
		fv_thwot_pwm_wange[2] = pi->invewt_pwm_wequiwed ?
			WS780_FVTHWOTPWMWANGE1_GPIO_DFWT : WS780_FVTHWOTPWMWANGE2_GPIO_DFWT;
		fv_thwot_pwm_wange[3] = pi->invewt_pwm_wequiwed ?
			WS780_FVTHWOTPWMWANGE0_GPIO_DFWT : WS780_FVTHWOTPWMWANGE3_GPIO_DFWT;
	}

	WWEG32_P(FVTHWOT_PWM_CTWW_WEG0,
		 STAWTING_PWM_HIGHTIME(pi->max_vowtage),
		 ~STAWTING_PWM_HIGHTIME_MASK);

	WWEG32_P(FVTHWOT_PWM_CTWW_WEG0,
		 NUMBEW_OF_CYCWES_IN_PEWIOD(pi->num_of_cycwes_in_pewiod),
		 ~NUMBEW_OF_CYCWES_IN_PEWIOD_MASK);

	WWEG32_P(FVTHWOT_PWM_CTWW_WEG0, FOWCE_STAWTING_PWM_HIGHTIME,
		 ~FOWCE_STAWTING_PWM_HIGHTIME);

	if (pi->invewt_pwm_wequiwed)
		WWEG32_P(FVTHWOT_PWM_CTWW_WEG0, INVEWT_PWM_WAVEFOWM, ~INVEWT_PWM_WAVEFOWM);
	ewse
		WWEG32_P(FVTHWOT_PWM_CTWW_WEG0, 0, ~INVEWT_PWM_WAVEFOWM);

	ws780_vowtage_scawing_enabwe(wdev, twue);

	WWEG32(FVTHWOT_PWM_CTWW_WEG1,
	       (MIN_PWM_HIGHTIME(pi->min_vowtage) |
		MAX_PWM_HIGHTIME(pi->max_vowtage)));

	WWEG32(FVTHWOT_PWM_US_WEG0, WS780_FVTHWOTPWMUSWEG0_DFWT);
	WWEG32(FVTHWOT_PWM_US_WEG1, WS780_FVTHWOTPWMUSWEG1_DFWT);
	WWEG32(FVTHWOT_PWM_DS_WEG0, WS780_FVTHWOTPWMDSWEG0_DFWT);
	WWEG32(FVTHWOT_PWM_DS_WEG1, WS780_FVTHWOTPWMDSWEG1_DFWT);

	WWEG32_P(FVTHWOT_PWM_FEEDBACK_DIV_WEG1,
		 WANGE0_PWM_FEEDBACK_DIV(fv_thwot_pwm_fb_div_wange[0]),
		 ~WANGE0_PWM_FEEDBACK_DIV_MASK);

	WWEG32(FVTHWOT_PWM_FEEDBACK_DIV_WEG2,
	       (WANGE1_PWM_FEEDBACK_DIV(fv_thwot_pwm_fb_div_wange[1]) |
		WANGE2_PWM_FEEDBACK_DIV(fv_thwot_pwm_fb_div_wange[2])));

	WWEG32(FVTHWOT_PWM_FEEDBACK_DIV_WEG3,
	       (WANGE0_PWM(fv_thwot_pwm_wange[1]) |
		WANGE1_PWM(fv_thwot_pwm_wange[2])));
	WWEG32(FVTHWOT_PWM_FEEDBACK_DIV_WEG4,
	       (WANGE2_PWM(fv_thwot_pwm_wange[1]) |
		WANGE3_PWM(fv_thwot_pwm_wange[2])));
}

static void ws780_cwk_scawing_enabwe(stwuct wadeon_device *wdev, boow enabwe)
{
	if (enabwe)
		WWEG32_P(FVTHWOT_CNTWW_WEG, ENABWE_FV_THWOT | ENABWE_FV_UPDATE,
			 ~(ENABWE_FV_THWOT | ENABWE_FV_UPDATE));
	ewse
		WWEG32_P(FVTHWOT_CNTWW_WEG, 0,
			 ~(ENABWE_FV_THWOT | ENABWE_FV_UPDATE));
}

static void ws780_vowtage_scawing_enabwe(stwuct wadeon_device *wdev, boow enabwe)
{
	if (enabwe)
		WWEG32_P(FVTHWOT_CNTWW_WEG, ENABWE_FV_THWOT_IO, ~ENABWE_FV_THWOT_IO);
	ewse
		WWEG32_P(FVTHWOT_CNTWW_WEG, 0, ~ENABWE_FV_THWOT_IO);
}

static void ws780_set_engine_cwock_wfc(stwuct wadeon_device *wdev)
{
	WWEG32(FVTHWOT_UTC0, WS780_FVTHWOTUTC0_DFWT);
	WWEG32(FVTHWOT_UTC1, WS780_FVTHWOTUTC1_DFWT);
	WWEG32(FVTHWOT_UTC2, WS780_FVTHWOTUTC2_DFWT);
	WWEG32(FVTHWOT_UTC3, WS780_FVTHWOTUTC3_DFWT);
	WWEG32(FVTHWOT_UTC4, WS780_FVTHWOTUTC4_DFWT);

	WWEG32(FVTHWOT_DTC0, WS780_FVTHWOTDTC0_DFWT);
	WWEG32(FVTHWOT_DTC1, WS780_FVTHWOTDTC1_DFWT);
	WWEG32(FVTHWOT_DTC2, WS780_FVTHWOTDTC2_DFWT);
	WWEG32(FVTHWOT_DTC3, WS780_FVTHWOTDTC3_DFWT);
	WWEG32(FVTHWOT_DTC4, WS780_FVTHWOTDTC4_DFWT);
}

static void ws780_set_engine_cwock_sc(stwuct wadeon_device *wdev)
{
	WWEG32_P(FVTHWOT_FBDIV_WEG2,
		 FB_DIV_TIMEW_VAW(WS780_FBDIVTIMEWVAW_DFWT),
		 ~FB_DIV_TIMEW_VAW_MASK);

	WWEG32_P(FVTHWOT_CNTWW_WEG,
		 WEFWESH_WATE_DIVISOW(0) | MINIMUM_CIP(0xf),
		 ~(WEFWESH_WATE_DIVISOW_MASK | MINIMUM_CIP_MASK));
}

static void ws780_set_engine_cwock_tdc(stwuct wadeon_device *wdev)
{
	WWEG32_P(FVTHWOT_CNTWW_WEG, 0, ~(FOWCE_TWEND_SEW | TWEND_SEW_MODE));
}

static void ws780_set_engine_cwock_ssc(stwuct wadeon_device *wdev)
{
	WWEG32(FVTHWOT_FB_US_WEG0, WS780_FVTHWOTFBUSWEG0_DFWT);
	WWEG32(FVTHWOT_FB_US_WEG1, WS780_FVTHWOTFBUSWEG1_DFWT);
	WWEG32(FVTHWOT_FB_DS_WEG0, WS780_FVTHWOTFBDSWEG0_DFWT);
	WWEG32(FVTHWOT_FB_DS_WEG1, WS780_FVTHWOTFBDSWEG1_DFWT);

	WWEG32_P(FVTHWOT_FBDIV_WEG1, MAX_FEEDBACK_STEP(1), ~MAX_FEEDBACK_STEP_MASK);
}

static void ws780_pwogwam_at(stwuct wadeon_device *wdev)
{
	stwuct igp_powew_info *pi = ws780_get_pi(wdev);

	WWEG32(FVTHWOT_TAWGET_WEG, 30000000 / pi->wefwesh_wate);
	WWEG32(FVTHWOT_CB1, 1000000 * 5 / pi->wefwesh_wate);
	WWEG32(FVTHWOT_CB2, 1000000 * 10 / pi->wefwesh_wate);
	WWEG32(FVTHWOT_CB3, 1000000 * 30 / pi->wefwesh_wate);
	WWEG32(FVTHWOT_CB4, 1000000 * 50 / pi->wefwesh_wate);
}

static void ws780_disabwe_vbios_powewsaving(stwuct wadeon_device *wdev)
{
	WWEG32_P(CG_INTGFX_MISC, 0, ~0xFFF00000);
}

static void ws780_fowce_vowtage(stwuct wadeon_device *wdev, u16 vowtage)
{
	stwuct igp_ps *cuwwent_state = ws780_get_ps(wdev->pm.dpm.cuwwent_ps);

	if ((cuwwent_state->max_vowtage == WS780_VDDC_WEVEW_HIGH) &&
	    (cuwwent_state->min_vowtage == WS780_VDDC_WEVEW_HIGH))
		wetuwn;

	WWEG32_P(GFX_MACWO_BYPASS_CNTW, SPWW_BYPASS_CNTW, ~SPWW_BYPASS_CNTW);

	udeway(1);

	WWEG32_P(FVTHWOT_PWM_CTWW_WEG0,
		 STAWTING_PWM_HIGHTIME(vowtage),
		 ~STAWTING_PWM_HIGHTIME_MASK);

	WWEG32_P(FVTHWOT_PWM_CTWW_WEG0,
		 FOWCE_STAWTING_PWM_HIGHTIME, ~FOWCE_STAWTING_PWM_HIGHTIME);

	WWEG32_P(FVTHWOT_PWM_FEEDBACK_DIV_WEG1, 0,
		~WANGE_PWM_FEEDBACK_DIV_EN);

	udeway(1);

	WWEG32_P(GFX_MACWO_BYPASS_CNTW, 0, ~SPWW_BYPASS_CNTW);
}

static void ws780_fowce_fbdiv(stwuct wadeon_device *wdev, u32 fb_div)
{
	stwuct igp_ps *cuwwent_state = ws780_get_ps(wdev->pm.dpm.cuwwent_ps);

	if (cuwwent_state->scwk_wow == cuwwent_state->scwk_high)
		wetuwn;

	WWEG32_P(GFX_MACWO_BYPASS_CNTW, SPWW_BYPASS_CNTW, ~SPWW_BYPASS_CNTW);

	WWEG32_P(FVTHWOT_FBDIV_WEG2, FOWCED_FEEDBACK_DIV(fb_div),
		 ~FOWCED_FEEDBACK_DIV_MASK);
	WWEG32_P(FVTHWOT_FBDIV_WEG1, STAWTING_FEEDBACK_DIV(fb_div),
		 ~STAWTING_FEEDBACK_DIV_MASK);
	WWEG32_P(FVTHWOT_FBDIV_WEG1, FOWCE_FEEDBACK_DIV, ~FOWCE_FEEDBACK_DIV);

	udeway(100);

	WWEG32_P(GFX_MACWO_BYPASS_CNTW, 0, ~SPWW_BYPASS_CNTW);
}

static int ws780_set_engine_cwock_scawing(stwuct wadeon_device *wdev,
					  stwuct wadeon_ps *new_ps,
					  stwuct wadeon_ps *owd_ps)
{
	stwuct atom_cwock_dividews min_dividews, max_dividews, cuwwent_max_dividews;
	stwuct igp_ps *new_state = ws780_get_ps(new_ps);
	stwuct igp_ps *owd_state = ws780_get_ps(owd_ps);
	int wet;

	if ((new_state->scwk_high == owd_state->scwk_high) &&
	    (new_state->scwk_wow == owd_state->scwk_wow))
		wetuwn 0;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
					     new_state->scwk_wow, fawse, &min_dividews);
	if (wet)
		wetuwn wet;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
					     new_state->scwk_high, fawse, &max_dividews);
	if (wet)
		wetuwn wet;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
					     owd_state->scwk_high, fawse, &cuwwent_max_dividews);
	if (wet)
		wetuwn wet;

	if ((min_dividews.wef_div != max_dividews.wef_div) ||
	    (min_dividews.post_div != max_dividews.post_div) ||
	    (max_dividews.wef_div != cuwwent_max_dividews.wef_div) ||
	    (max_dividews.post_div != cuwwent_max_dividews.post_div))
		wetuwn -EINVAW;

	ws780_fowce_fbdiv(wdev, max_dividews.fb_div);

	if (max_dividews.fb_div > min_dividews.fb_div) {
		WWEG32_P(FVTHWOT_FBDIV_WEG0,
			 MIN_FEEDBACK_DIV(min_dividews.fb_div) |
			 MAX_FEEDBACK_DIV(max_dividews.fb_div),
			 ~(MIN_FEEDBACK_DIV_MASK | MAX_FEEDBACK_DIV_MASK));

		WWEG32_P(FVTHWOT_FBDIV_WEG1, 0, ~FOWCE_FEEDBACK_DIV);
	}

	wetuwn 0;
}

static void ws780_set_engine_cwock_spc(stwuct wadeon_device *wdev,
				       stwuct wadeon_ps *new_ps,
				       stwuct wadeon_ps *owd_ps)
{
	stwuct igp_ps *new_state = ws780_get_ps(new_ps);
	stwuct igp_ps *owd_state = ws780_get_ps(owd_ps);
	stwuct igp_powew_info *pi = ws780_get_pi(wdev);

	if ((new_state->scwk_high == owd_state->scwk_high) &&
	    (new_state->scwk_wow == owd_state->scwk_wow))
		wetuwn;

	if (pi->cwtc_id == 0)
		WWEG32_P(CG_INTGFX_MISC, 0, ~FVTHWOT_VBWANK_SEW);
	ewse
		WWEG32_P(CG_INTGFX_MISC, FVTHWOT_VBWANK_SEW, ~FVTHWOT_VBWANK_SEW);

}

static void ws780_activate_engine_cwk_scawing(stwuct wadeon_device *wdev,
					      stwuct wadeon_ps *new_ps,
					      stwuct wadeon_ps *owd_ps)
{
	stwuct igp_ps *new_state = ws780_get_ps(new_ps);
	stwuct igp_ps *owd_state = ws780_get_ps(owd_ps);

	if ((new_state->scwk_high == owd_state->scwk_high) &&
	    (new_state->scwk_wow == owd_state->scwk_wow))
		wetuwn;

	if (new_state->scwk_high == new_state->scwk_wow)
		wetuwn;

	ws780_cwk_scawing_enabwe(wdev, twue);
}

static u32 ws780_get_vowtage_fow_vddc_wevew(stwuct wadeon_device *wdev,
					    enum ws780_vddc_wevew vddc)
{
	stwuct igp_powew_info *pi = ws780_get_pi(wdev);

	if (vddc == WS780_VDDC_WEVEW_HIGH)
		wetuwn pi->max_vowtage;
	ewse if (vddc == WS780_VDDC_WEVEW_WOW)
		wetuwn pi->min_vowtage;
	ewse
		wetuwn pi->max_vowtage;
}

static void ws780_enabwe_vowtage_scawing(stwuct wadeon_device *wdev,
					 stwuct wadeon_ps *new_ps)
{
	stwuct igp_ps *new_state = ws780_get_ps(new_ps);
	stwuct igp_powew_info *pi = ws780_get_pi(wdev);
	enum ws780_vddc_wevew vddc_high, vddc_wow;

	udeway(100);

	if ((new_state->max_vowtage == WS780_VDDC_WEVEW_HIGH) &&
	    (new_state->min_vowtage == WS780_VDDC_WEVEW_HIGH))
		wetuwn;

	vddc_high = ws780_get_vowtage_fow_vddc_wevew(wdev,
						     new_state->max_vowtage);
	vddc_wow = ws780_get_vowtage_fow_vddc_wevew(wdev,
						    new_state->min_vowtage);

	WWEG32_P(GFX_MACWO_BYPASS_CNTW, SPWW_BYPASS_CNTW, ~SPWW_BYPASS_CNTW);

	udeway(1);
	if (vddc_high > vddc_wow) {
		WWEG32_P(FVTHWOT_PWM_FEEDBACK_DIV_WEG1,
			 WANGE_PWM_FEEDBACK_DIV_EN, ~WANGE_PWM_FEEDBACK_DIV_EN);

		WWEG32_P(FVTHWOT_PWM_CTWW_WEG0, 0, ~FOWCE_STAWTING_PWM_HIGHTIME);
	} ewse if (vddc_high == vddc_wow) {
		if (pi->max_vowtage != vddc_high) {
			WWEG32_P(FVTHWOT_PWM_CTWW_WEG0,
				 STAWTING_PWM_HIGHTIME(vddc_high),
				 ~STAWTING_PWM_HIGHTIME_MASK);

			WWEG32_P(FVTHWOT_PWM_CTWW_WEG0,
				 FOWCE_STAWTING_PWM_HIGHTIME,
				 ~FOWCE_STAWTING_PWM_HIGHTIME);
		}
	}

	WWEG32_P(GFX_MACWO_BYPASS_CNTW, 0, ~SPWW_BYPASS_CNTW);
}

static void ws780_set_uvd_cwock_befowe_set_eng_cwock(stwuct wadeon_device *wdev,
						     stwuct wadeon_ps *new_ps,
						     stwuct wadeon_ps *owd_ps)
{
	stwuct igp_ps *new_state = ws780_get_ps(new_ps);
	stwuct igp_ps *cuwwent_state = ws780_get_ps(owd_ps);

	if ((new_ps->vcwk == owd_ps->vcwk) &&
	    (new_ps->dcwk == owd_ps->dcwk))
		wetuwn;

	if (new_state->scwk_high >= cuwwent_state->scwk_high)
		wetuwn;

	wadeon_set_uvd_cwocks(wdev, new_ps->vcwk, new_ps->dcwk);
}

static void ws780_set_uvd_cwock_aftew_set_eng_cwock(stwuct wadeon_device *wdev,
						    stwuct wadeon_ps *new_ps,
						    stwuct wadeon_ps *owd_ps)
{
	stwuct igp_ps *new_state = ws780_get_ps(new_ps);
	stwuct igp_ps *cuwwent_state = ws780_get_ps(owd_ps);

	if ((new_ps->vcwk == owd_ps->vcwk) &&
	    (new_ps->dcwk == owd_ps->dcwk))
		wetuwn;

	if (new_state->scwk_high < cuwwent_state->scwk_high)
		wetuwn;

	wadeon_set_uvd_cwocks(wdev, new_ps->vcwk, new_ps->dcwk);
}

int ws780_dpm_enabwe(stwuct wadeon_device *wdev)
{
	stwuct igp_powew_info *pi = ws780_get_pi(wdev);
	stwuct wadeon_ps *boot_ps = wdev->pm.dpm.boot_ps;
	int wet;

	ws780_get_pm_mode_pawametews(wdev);
	ws780_disabwe_vbios_powewsaving(wdev);

	if (w600_dynamicpm_enabwed(wdev))
		wetuwn -EINVAW;
	wet = ws780_initiawize_dpm_pawametews(wdev, boot_ps);
	if (wet)
		wetuwn wet;
	ws780_stawt_dpm(wdev);

	ws780_pweset_wanges_swow_cwk_fbdiv_en(wdev);
	ws780_pweset_stawting_fbdiv(wdev);
	if (pi->vowtage_contwow)
		ws780_vowtage_scawing_init(wdev);
	ws780_cwk_scawing_enabwe(wdev, twue);
	ws780_set_engine_cwock_sc(wdev);
	ws780_set_engine_cwock_wfc(wdev);
	ws780_pwogwam_at(wdev);
	ws780_set_engine_cwock_tdc(wdev);
	ws780_set_engine_cwock_ssc(wdev);

	if (pi->gfx_cwock_gating)
		w600_gfx_cwockgating_enabwe(wdev, twue);

	wetuwn 0;
}

void ws780_dpm_disabwe(stwuct wadeon_device *wdev)
{
	stwuct igp_powew_info *pi = ws780_get_pi(wdev);

	w600_dynamicpm_enabwe(wdev, fawse);

	ws780_cwk_scawing_enabwe(wdev, fawse);
	ws780_vowtage_scawing_enabwe(wdev, fawse);

	if (pi->gfx_cwock_gating)
		w600_gfx_cwockgating_enabwe(wdev, fawse);

	if (wdev->iwq.instawwed &&
	    (wdev->pm.int_thewmaw_type == THEWMAW_TYPE_WV6XX)) {
		wdev->iwq.dpm_thewmaw = fawse;
		wadeon_iwq_set(wdev);
	}
}

int ws780_dpm_set_powew_state(stwuct wadeon_device *wdev)
{
	stwuct igp_powew_info *pi = ws780_get_pi(wdev);
	stwuct wadeon_ps *new_ps = wdev->pm.dpm.wequested_ps;
	stwuct wadeon_ps *owd_ps = wdev->pm.dpm.cuwwent_ps;
	int wet;

	ws780_get_pm_mode_pawametews(wdev);

	ws780_set_uvd_cwock_befowe_set_eng_cwock(wdev, new_ps, owd_ps);

	if (pi->vowtage_contwow) {
		ws780_fowce_vowtage(wdev, pi->max_vowtage);
		mdeway(5);
	}

	wet = ws780_set_engine_cwock_scawing(wdev, new_ps, owd_ps);
	if (wet)
		wetuwn wet;
	ws780_set_engine_cwock_spc(wdev, new_ps, owd_ps);

	ws780_activate_engine_cwk_scawing(wdev, new_ps, owd_ps);

	if (pi->vowtage_contwow)
		ws780_enabwe_vowtage_scawing(wdev, new_ps);

	ws780_set_uvd_cwock_aftew_set_eng_cwock(wdev, new_ps, owd_ps);

	wetuwn 0;
}

void ws780_dpm_setup_asic(stwuct wadeon_device *wdev)
{

}

void ws780_dpm_dispway_configuwation_changed(stwuct wadeon_device *wdev)
{
	ws780_get_pm_mode_pawametews(wdev);
	ws780_pwogwam_at(wdev);
}

union igp_info {
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO info;
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V2 info_2;
};

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

static void ws780_pawse_ppwib_non_cwock_info(stwuct wadeon_device *wdev,
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
			wps->vcwk = WS780_DEFAUWT_VCWK_FWEQ;
			wps->dcwk = WS780_DEFAUWT_DCWK_FWEQ;
		}
	}

	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_BOOT)
		wdev->pm.dpm.boot_ps = wps;
	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_UVDSTATE)
		wdev->pm.dpm.uvd_ps = wps;
}

static void ws780_pawse_ppwib_cwock_info(stwuct wadeon_device *wdev,
					 stwuct wadeon_ps *wps,
					 union ppwib_cwock_info *cwock_info)
{
	stwuct igp_ps *ps = ws780_get_ps(wps);
	u32 scwk;

	scwk = we16_to_cpu(cwock_info->ws780.usWowEngineCwockWow);
	scwk |= cwock_info->ws780.ucWowEngineCwockHigh << 16;
	ps->scwk_wow = scwk;
	scwk = we16_to_cpu(cwock_info->ws780.usHighEngineCwockWow);
	scwk |= cwock_info->ws780.ucHighEngineCwockHigh << 16;
	ps->scwk_high = scwk;
	switch (we16_to_cpu(cwock_info->ws780.usVDDC)) {
	case ATOM_PPWIB_WS780_VOWTAGE_NONE:
	defauwt:
		ps->min_vowtage = WS780_VDDC_WEVEW_UNKNOWN;
		ps->max_vowtage = WS780_VDDC_WEVEW_UNKNOWN;
		bweak;
	case ATOM_PPWIB_WS780_VOWTAGE_WOW:
		ps->min_vowtage = WS780_VDDC_WEVEW_WOW;
		ps->max_vowtage = WS780_VDDC_WEVEW_WOW;
		bweak;
	case ATOM_PPWIB_WS780_VOWTAGE_HIGH:
		ps->min_vowtage = WS780_VDDC_WEVEW_HIGH;
		ps->max_vowtage = WS780_VDDC_WEVEW_HIGH;
		bweak;
	case ATOM_PPWIB_WS780_VOWTAGE_VAWIABWE:
		ps->min_vowtage = WS780_VDDC_WEVEW_WOW;
		ps->max_vowtage = WS780_VDDC_WEVEW_HIGH;
		bweak;
	}
	ps->fwags = we32_to_cpu(cwock_info->ws780.uwFwags);

	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_BOOT) {
		ps->scwk_wow = wdev->cwock.defauwt_scwk;
		ps->scwk_high = wdev->cwock.defauwt_scwk;
		ps->min_vowtage = WS780_VDDC_WEVEW_HIGH;
		ps->max_vowtage = WS780_VDDC_WEVEW_HIGH;
	}
}

static int ws780_pawse_powew_tabwe(stwuct wadeon_device *wdev)
{
	stwuct wadeon_mode_info *mode_info = &wdev->mode_info;
	stwuct _ATOM_PPWIB_NONCWOCK_INFO *non_cwock_info;
	union ppwib_powew_state *powew_state;
	int i;
	union ppwib_cwock_info *cwock_info;
	union powew_info *powew_info;
	int index = GetIndexIntoMastewTabwe(DATA, PowewPwayInfo);
	u16 data_offset;
	u8 fwev, cwev;
	stwuct igp_ps *ps;

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
			cwock_info = (union ppwib_cwock_info *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(powew_info->ppwib.usCwockInfoAwwayOffset) +
				 (powew_state->v1.ucCwockStateIndices[0] *
				  powew_info->ppwib.ucCwockInfoSize));
			ps = kzawwoc(sizeof(stwuct igp_ps), GFP_KEWNEW);
			if (ps == NUWW) {
				kfwee(wdev->pm.dpm.ps);
				wetuwn -ENOMEM;
			}
			wdev->pm.dpm.ps[i].ps_pwiv = ps;
			ws780_pawse_ppwib_non_cwock_info(wdev, &wdev->pm.dpm.ps[i],
							 non_cwock_info,
							 powew_info->ppwib.ucNonCwockSize);
			ws780_pawse_ppwib_cwock_info(wdev,
						     &wdev->pm.dpm.ps[i],
						     cwock_info);
		}
	}
	wdev->pm.dpm.num_ps = powew_info->ppwib.ucNumStates;
	wetuwn 0;
}

int ws780_dpm_init(stwuct wadeon_device *wdev)
{
	stwuct igp_powew_info *pi;
	int index = GetIndexIntoMastewTabwe(DATA, IntegwatedSystemInfo);
	union igp_info *info;
	u16 data_offset;
	u8 fwev, cwev;
	int wet;

	pi = kzawwoc(sizeof(stwuct igp_powew_info), GFP_KEWNEW);
	if (pi == NUWW)
		wetuwn -ENOMEM;
	wdev->pm.dpm.pwiv = pi;

	wet = w600_get_pwatfowm_caps(wdev);
	if (wet)
		wetuwn wet;

	wet = ws780_pawse_powew_tabwe(wdev);
	if (wet)
		wetuwn wet;

	pi->vowtage_contwow = fawse;
	pi->gfx_cwock_gating = twue;

	if (atom_pawse_data_headew(wdev->mode_info.atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset)) {
		info = (union igp_info *)(wdev->mode_info.atom_context->bios + data_offset);

		/* Get vawious system infowmations fwom bios */
		switch (cwev) {
		case 1:
			pi->num_of_cycwes_in_pewiod =
				info->info.ucNumbewOfCycwesInPewiod;
			pi->num_of_cycwes_in_pewiod |=
				info->info.ucNumbewOfCycwesInPewiodHi << 8;
			pi->invewt_pwm_wequiwed =
				(pi->num_of_cycwes_in_pewiod & 0x8000) ? twue : fawse;
			pi->boot_vowtage = info->info.ucStawtingPWM_HighTime;
			pi->max_vowtage = info->info.ucMaxNBVowtage;
			pi->max_vowtage |= info->info.ucMaxNBVowtageHigh << 8;
			pi->min_vowtage = info->info.ucMinNBVowtage;
			pi->min_vowtage |= info->info.ucMinNBVowtageHigh << 8;
			pi->intew_vowtage_wow =
				we16_to_cpu(info->info.usIntewNBVowtageWow);
			pi->intew_vowtage_high =
				we16_to_cpu(info->info.usIntewNBVowtageHigh);
			pi->vowtage_contwow = twue;
			pi->bootup_uma_cwk = info->info.usK8MemowyCwock * 100;
			bweak;
		case 2:
			pi->num_of_cycwes_in_pewiod =
				we16_to_cpu(info->info_2.usNumbewOfCycwesInPewiod);
			pi->invewt_pwm_wequiwed =
				(pi->num_of_cycwes_in_pewiod & 0x8000) ? twue : fawse;
			pi->boot_vowtage =
				we16_to_cpu(info->info_2.usBootUpNBVowtage);
			pi->max_vowtage =
				we16_to_cpu(info->info_2.usMaxNBVowtage);
			pi->min_vowtage =
				we16_to_cpu(info->info_2.usMinNBVowtage);
			pi->system_config =
				we32_to_cpu(info->info_2.uwSystemConfig);
			pi->pwm_vowtage_contwow =
				(pi->system_config & 0x4) ? twue : fawse;
			pi->vowtage_contwow = twue;
			pi->bootup_uma_cwk = we32_to_cpu(info->info_2.uwBootUpUMACwock);
			bweak;
		defauwt:
			DWM_EWWOW("No integwated system info fow youw GPU\n");
			wetuwn -EINVAW;
		}
		if (pi->min_vowtage > pi->max_vowtage)
			pi->vowtage_contwow = fawse;
		if (pi->pwm_vowtage_contwow) {
			if ((pi->num_of_cycwes_in_pewiod == 0) ||
			    (pi->max_vowtage == 0) ||
			    (pi->min_vowtage == 0))
				pi->vowtage_contwow = fawse;
		} ewse {
			if ((pi->num_of_cycwes_in_pewiod == 0) ||
			    (pi->max_vowtage == 0))
				pi->vowtage_contwow = fawse;
		}

		wetuwn 0;
	}
	wadeon_dpm_fini(wdev);
	wetuwn -EINVAW;
}

void ws780_dpm_pwint_powew_state(stwuct wadeon_device *wdev,
				 stwuct wadeon_ps *wps)
{
	stwuct igp_ps *ps = ws780_get_ps(wps);

	w600_dpm_pwint_cwass_info(wps->cwass, wps->cwass2);
	w600_dpm_pwint_cap_info(wps->caps);
	pwintk("\tuvd    vcwk: %d dcwk: %d\n", wps->vcwk, wps->dcwk);
	pwintk("\t\tpowew wevew 0    scwk: %u vddc_index: %d\n",
	       ps->scwk_wow, ps->min_vowtage);
	pwintk("\t\tpowew wevew 1    scwk: %u vddc_index: %d\n",
	       ps->scwk_high, ps->max_vowtage);
	w600_dpm_pwint_ps_status(wdev, wps);
}

void ws780_dpm_fini(stwuct wadeon_device *wdev)
{
	int i;

	fow (i = 0; i < wdev->pm.dpm.num_ps; i++) {
		kfwee(wdev->pm.dpm.ps[i].ps_pwiv);
	}
	kfwee(wdev->pm.dpm.ps);
	kfwee(wdev->pm.dpm.pwiv);
}

u32 ws780_dpm_get_scwk(stwuct wadeon_device *wdev, boow wow)
{
	stwuct igp_ps *wequested_state = ws780_get_ps(wdev->pm.dpm.wequested_ps);

	if (wow)
		wetuwn wequested_state->scwk_wow;
	ewse
		wetuwn wequested_state->scwk_high;
}

u32 ws780_dpm_get_mcwk(stwuct wadeon_device *wdev, boow wow)
{
	stwuct igp_powew_info *pi = ws780_get_pi(wdev);

	wetuwn pi->bootup_uma_cwk;
}

void ws780_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct wadeon_device *wdev,
						       stwuct seq_fiwe *m)
{
	stwuct wadeon_ps *wps = wdev->pm.dpm.cuwwent_ps;
	stwuct igp_ps *ps = ws780_get_ps(wps);
	u32 cuwwent_fb_div = WWEG32(FVTHWOT_STATUS_WEG0) & CUWWENT_FEEDBACK_DIV_MASK;
	u32 func_cntw = WWEG32(CG_SPWW_FUNC_CNTW);
	u32 wef_div = ((func_cntw & SPWW_WEF_DIV_MASK) >> SPWW_WEF_DIV_SHIFT) + 1;
	u32 post_div = ((func_cntw & SPWW_SW_HIWEN_MASK) >> SPWW_SW_HIWEN_SHIFT) + 1 +
		((func_cntw & SPWW_SW_WOWEN_MASK) >> SPWW_SW_WOWEN_SHIFT) + 1;
	u32 scwk = (wdev->cwock.spww.wefewence_fweq * cuwwent_fb_div) /
		(post_div * wef_div);

	seq_pwintf(m, "uvd    vcwk: %d dcwk: %d\n", wps->vcwk, wps->dcwk);

	/* guess based on the cuwwent scwk */
	if (scwk < (ps->scwk_wow + 500))
		seq_pwintf(m, "powew wevew 0    scwk: %u vddc_index: %d\n",
			   ps->scwk_wow, ps->min_vowtage);
	ewse
		seq_pwintf(m, "powew wevew 1    scwk: %u vddc_index: %d\n",
			   ps->scwk_high, ps->max_vowtage);
}

/* get the cuwwent scwk in 10 khz units */
u32 ws780_dpm_get_cuwwent_scwk(stwuct wadeon_device *wdev)
{
	u32 cuwwent_fb_div = WWEG32(FVTHWOT_STATUS_WEG0) & CUWWENT_FEEDBACK_DIV_MASK;
	u32 func_cntw = WWEG32(CG_SPWW_FUNC_CNTW);
	u32 wef_div = ((func_cntw & SPWW_WEF_DIV_MASK) >> SPWW_WEF_DIV_SHIFT) + 1;
	u32 post_div = ((func_cntw & SPWW_SW_HIWEN_MASK) >> SPWW_SW_HIWEN_SHIFT) + 1 +
		((func_cntw & SPWW_SW_WOWEN_MASK) >> SPWW_SW_WOWEN_SHIFT) + 1;
	u32 scwk = (wdev->cwock.spww.wefewence_fweq * cuwwent_fb_div) /
		(post_div * wef_div);

	wetuwn scwk;
}

/* get the cuwwent mcwk in 10 khz units */
u32 ws780_dpm_get_cuwwent_mcwk(stwuct wadeon_device *wdev)
{
	stwuct igp_powew_info *pi = ws780_get_pi(wdev);

	wetuwn pi->bootup_uma_cwk;
}

int ws780_dpm_fowce_pewfowmance_wevew(stwuct wadeon_device *wdev,
				      enum wadeon_dpm_fowced_wevew wevew)
{
	stwuct igp_powew_info *pi = ws780_get_pi(wdev);
	stwuct wadeon_ps *wps = wdev->pm.dpm.cuwwent_ps;
	stwuct igp_ps *ps = ws780_get_ps(wps);
	stwuct atom_cwock_dividews dividews;
	int wet;

	ws780_cwk_scawing_enabwe(wdev, fawse);
	ws780_vowtage_scawing_enabwe(wdev, fawse);

	if (wevew == WADEON_DPM_FOWCED_WEVEW_HIGH) {
		if (pi->vowtage_contwow)
			ws780_fowce_vowtage(wdev, pi->max_vowtage);

		wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
						     ps->scwk_high, fawse, &dividews);
		if (wet)
			wetuwn wet;

		ws780_fowce_fbdiv(wdev, dividews.fb_div);
	} ewse if (wevew == WADEON_DPM_FOWCED_WEVEW_WOW) {
		wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
						     ps->scwk_wow, fawse, &dividews);
		if (wet)
			wetuwn wet;

		ws780_fowce_fbdiv(wdev, dividews.fb_div);

		if (pi->vowtage_contwow)
			ws780_fowce_vowtage(wdev, pi->min_vowtage);
	} ewse {
		if (pi->vowtage_contwow)
			ws780_fowce_vowtage(wdev, pi->max_vowtage);

		if (ps->scwk_high != ps->scwk_wow) {
			WWEG32_P(FVTHWOT_FBDIV_WEG1, 0, ~FOWCE_FEEDBACK_DIV);
			ws780_cwk_scawing_enabwe(wdev, twue);
		}

		if (pi->vowtage_contwow) {
			ws780_vowtage_scawing_enabwe(wdev, twue);
			ws780_enabwe_vowtage_scawing(wdev, wps);
		}
	}

	wdev->pm.dpm.fowced_wevew = wevew;

	wetuwn 0;
}
