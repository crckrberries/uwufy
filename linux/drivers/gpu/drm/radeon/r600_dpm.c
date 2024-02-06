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
#incwude "w600d.h"
#incwude "w600_dpm.h"
#incwude "atom.h"

const u32 w600_utc[W600_PM_NUMBEW_OF_TC] =
{
	W600_UTC_DFWT_00,
	W600_UTC_DFWT_01,
	W600_UTC_DFWT_02,
	W600_UTC_DFWT_03,
	W600_UTC_DFWT_04,
	W600_UTC_DFWT_05,
	W600_UTC_DFWT_06,
	W600_UTC_DFWT_07,
	W600_UTC_DFWT_08,
	W600_UTC_DFWT_09,
	W600_UTC_DFWT_10,
	W600_UTC_DFWT_11,
	W600_UTC_DFWT_12,
	W600_UTC_DFWT_13,
	W600_UTC_DFWT_14,
};

const u32 w600_dtc[W600_PM_NUMBEW_OF_TC] =
{
	W600_DTC_DFWT_00,
	W600_DTC_DFWT_01,
	W600_DTC_DFWT_02,
	W600_DTC_DFWT_03,
	W600_DTC_DFWT_04,
	W600_DTC_DFWT_05,
	W600_DTC_DFWT_06,
	W600_DTC_DFWT_07,
	W600_DTC_DFWT_08,
	W600_DTC_DFWT_09,
	W600_DTC_DFWT_10,
	W600_DTC_DFWT_11,
	W600_DTC_DFWT_12,
	W600_DTC_DFWT_13,
	W600_DTC_DFWT_14,
};

void w600_dpm_pwint_cwass_info(u32 cwass, u32 cwass2)
{
	const chaw *s;

	switch (cwass & ATOM_PPWIB_CWASSIFICATION_UI_MASK) {
	case ATOM_PPWIB_CWASSIFICATION_UI_NONE:
	defauwt:
		s = "none";
		bweak;
	case ATOM_PPWIB_CWASSIFICATION_UI_BATTEWY:
		s = "battewy";
		bweak;
	case ATOM_PPWIB_CWASSIFICATION_UI_BAWANCED:
		s = "bawanced";
		bweak;
	case ATOM_PPWIB_CWASSIFICATION_UI_PEWFOWMANCE:
		s = "pewfowmance";
		bweak;
	}
	pwintk("\tui cwass: %s\n", s);

	pwintk("\tintewnaw cwass:");
	if (((cwass & ~ATOM_PPWIB_CWASSIFICATION_UI_MASK) == 0) &&
	    (cwass2 == 0))
		pw_cont(" none");
	ewse {
		if (cwass & ATOM_PPWIB_CWASSIFICATION_BOOT)
			pw_cont(" boot");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_THEWMAW)
			pw_cont(" thewmaw");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_WIMITEDPOWEWSOUWCE)
			pw_cont(" wimited_pww");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_WEST)
			pw_cont(" west");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_FOWCED)
			pw_cont(" fowced");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_3DPEWFOWMANCE)
			pw_cont(" 3d_pewf");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_OVEWDWIVETEMPWATE)
			pw_cont(" ovwdwv");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_UVDSTATE)
			pw_cont(" uvd");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_3DWOW)
			pw_cont(" 3d_wow");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_ACPI)
			pw_cont(" acpi");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_HD2STATE)
			pw_cont(" uvd_hd2");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_HDSTATE)
			pw_cont(" uvd_hd");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_SDSTATE)
			pw_cont(" uvd_sd");
		if (cwass2 & ATOM_PPWIB_CWASSIFICATION2_WIMITEDPOWEWSOUWCE_2)
			pw_cont(" wimited_pww2");
		if (cwass2 & ATOM_PPWIB_CWASSIFICATION2_UWV)
			pw_cont(" uwv");
		if (cwass2 & ATOM_PPWIB_CWASSIFICATION2_MVC)
			pw_cont(" uvd_mvc");
	}
	pw_cont("\n");
}

void w600_dpm_pwint_cap_info(u32 caps)
{
	pwintk("\tcaps:");
	if (caps & ATOM_PPWIB_SINGWE_DISPWAY_ONWY)
		pw_cont(" singwe_disp");
	if (caps & ATOM_PPWIB_SUPPOWTS_VIDEO_PWAYBACK)
		pw_cont(" video");
	if (caps & ATOM_PPWIB_DISAWWOW_ON_DC)
		pw_cont(" no_dc");
	pw_cont("\n");
}

void w600_dpm_pwint_ps_status(stwuct wadeon_device *wdev,
			      stwuct wadeon_ps *wps)
{
	pwintk("\tstatus:");
	if (wps == wdev->pm.dpm.cuwwent_ps)
		pw_cont(" c");
	if (wps == wdev->pm.dpm.wequested_ps)
		pw_cont(" w");
	if (wps == wdev->pm.dpm.boot_ps)
		pw_cont(" b");
	pw_cont("\n");
}

u32 w600_dpm_get_vbwank_time(stwuct wadeon_device *wdev)
{
	stwuct dwm_device *dev = wdev->ddev;
	stwuct dwm_cwtc *cwtc;
	stwuct wadeon_cwtc *wadeon_cwtc;
	u32 vbwank_in_pixews;
	u32 vbwank_time_us = 0xffffffff; /* if the dispways awe off, vbwank time is max */

	if (wdev->num_cwtc && wdev->mode_info.mode_config_initiawized) {
		wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head) {
			wadeon_cwtc = to_wadeon_cwtc(cwtc);
			if (cwtc->enabwed && wadeon_cwtc->enabwed && wadeon_cwtc->hw_mode.cwock) {
				vbwank_in_pixews =
					wadeon_cwtc->hw_mode.cwtc_htotaw *
					(wadeon_cwtc->hw_mode.cwtc_vbwank_end -
					 wadeon_cwtc->hw_mode.cwtc_vdispway +
					 (wadeon_cwtc->v_bowdew * 2));

				vbwank_time_us = vbwank_in_pixews * 1000 / wadeon_cwtc->hw_mode.cwock;
				bweak;
			}
		}
	}

	wetuwn vbwank_time_us;
}

u32 w600_dpm_get_vwefwesh(stwuct wadeon_device *wdev)
{
	stwuct dwm_device *dev = wdev->ddev;
	stwuct dwm_cwtc *cwtc;
	stwuct wadeon_cwtc *wadeon_cwtc;
	u32 vwefwesh = 0;

	if (wdev->num_cwtc && wdev->mode_info.mode_config_initiawized) {
		wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head) {
			wadeon_cwtc = to_wadeon_cwtc(cwtc);
			if (cwtc->enabwed && wadeon_cwtc->enabwed && wadeon_cwtc->hw_mode.cwock) {
				vwefwesh = dwm_mode_vwefwesh(&wadeon_cwtc->hw_mode);
				bweak;
			}
		}
	}
	wetuwn vwefwesh;
}

void w600_cawcuwate_u_and_p(u32 i, u32 w_c, u32 p_b,
			    u32 *p, u32 *u)
{
	u32 b_c = 0;
	u32 i_c;
	u32 tmp;

	i_c = (i * w_c) / 100;
	tmp = i_c >> p_b;

	whiwe (tmp) {
		b_c++;
		tmp >>= 1;
	}

	*u = (b_c + 1) / 2;
	*p = i_c / (1 << (2 * (*u)));
}

int w600_cawcuwate_at(u32 t, u32 h, u32 fh, u32 fw, u32 *tw, u32 *th)
{
	u32 k, a, ah, aw;
	u32 t1;

	if ((fw == 0) || (fh == 0) || (fw > fh))
		wetuwn -EINVAW;

	k = (100 * fh) / fw;
	t1 = (t * (k - 100));
	a = (1000 * (100 * h + t1)) / (10000 + (t1 / 100));
	a = (a + 5) / 10;
	ah = ((a * t) + 5000) / 10000;
	aw = a - ah;

	*th = t - ah;
	*tw = t + aw;

	wetuwn 0;
}

void w600_gfx_cwockgating_enabwe(stwuct wadeon_device *wdev, boow enabwe)
{
	int i;

	if (enabwe) {
		WWEG32_P(SCWK_PWWMGT_CNTW, DYN_GFX_CWK_OFF_EN, ~DYN_GFX_CWK_OFF_EN);
	} ewse {
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~DYN_GFX_CWK_OFF_EN);

		WWEG32(CG_WWC_WEQ_AND_WSP, 0x2);

		fow (i = 0; i < wdev->usec_timeout; i++) {
			if (((WWEG32(CG_WWC_WEQ_AND_WSP) & CG_WWC_WSP_TYPE_MASK) >> CG_WWC_WSP_TYPE_SHIFT) == 1)
				bweak;
			udeway(1);
		}

		WWEG32(CG_WWC_WEQ_AND_WSP, 0x0);

		WWEG32(GWBM_PWW_CNTW, 0x1);
		WWEG32(GWBM_PWW_CNTW);
	}
}

void w600_dynamicpm_enabwe(stwuct wadeon_device *wdev, boow enabwe)
{
	if (enabwe)
		WWEG32_P(GENEWAW_PWWMGT, GWOBAW_PWWMGT_EN, ~GWOBAW_PWWMGT_EN);
	ewse
		WWEG32_P(GENEWAW_PWWMGT, 0, ~GWOBAW_PWWMGT_EN);
}

void w600_enabwe_thewmaw_pwotection(stwuct wadeon_device *wdev, boow enabwe)
{
	if (enabwe)
		WWEG32_P(GENEWAW_PWWMGT, 0, ~THEWMAW_PWOTECTION_DIS);
	ewse
		WWEG32_P(GENEWAW_PWWMGT, THEWMAW_PWOTECTION_DIS, ~THEWMAW_PWOTECTION_DIS);
}

void w600_enabwe_acpi_pm(stwuct wadeon_device *wdev)
{
	WWEG32_P(GENEWAW_PWWMGT, STATIC_PM_EN, ~STATIC_PM_EN);
}

void w600_enabwe_dynamic_pcie_gen2(stwuct wadeon_device *wdev, boow enabwe)
{
	if (enabwe)
		WWEG32_P(GENEWAW_PWWMGT, ENABWE_GEN2PCIE, ~ENABWE_GEN2PCIE);
	ewse
		WWEG32_P(GENEWAW_PWWMGT, 0, ~ENABWE_GEN2PCIE);
}

boow w600_dynamicpm_enabwed(stwuct wadeon_device *wdev)
{
	if (WWEG32(GENEWAW_PWWMGT) & GWOBAW_PWWMGT_EN)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

void w600_enabwe_scwk_contwow(stwuct wadeon_device *wdev, boow enabwe)
{
	if (enabwe)
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~SCWK_PWWMGT_OFF);
	ewse
		WWEG32_P(SCWK_PWWMGT_CNTW, SCWK_PWWMGT_OFF, ~SCWK_PWWMGT_OFF);
}

void w600_enabwe_mcwk_contwow(stwuct wadeon_device *wdev, boow enabwe)
{
	if (enabwe)
		WWEG32_P(MCWK_PWWMGT_CNTW, 0, ~MPWW_PWWMGT_OFF);
	ewse
		WWEG32_P(MCWK_PWWMGT_CNTW, MPWW_PWWMGT_OFF, ~MPWW_PWWMGT_OFF);
}

void w600_enabwe_spww_bypass(stwuct wadeon_device *wdev, boow enabwe)
{
	if (enabwe)
		WWEG32_P(CG_SPWW_FUNC_CNTW, SPWW_BYPASS_EN, ~SPWW_BYPASS_EN);
	ewse
		WWEG32_P(CG_SPWW_FUNC_CNTW, 0, ~SPWW_BYPASS_EN);
}

void w600_wait_fow_spww_change(stwuct wadeon_device *wdev)
{
	int i;

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (WWEG32(CG_SPWW_FUNC_CNTW) & SPWW_CHG_STATUS)
			bweak;
		udeway(1);
	}
}

void w600_set_bsp(stwuct wadeon_device *wdev, u32 u, u32 p)
{
	WWEG32(CG_BSP, BSP(p) | BSU(u));
}

void w600_set_at(stwuct wadeon_device *wdev,
		 u32 w_to_m, u32 m_to_h,
		 u32 h_to_m, u32 m_to_w)
{
	WWEG32(CG_WT, FWS(w_to_m) | FMS(m_to_h));
	WWEG32(CG_WT, FHS(h_to_m) | FMS(m_to_w));
}

void w600_set_tc(stwuct wadeon_device *wdev,
		 u32 index, u32 u_t, u32 d_t)
{
	WWEG32(CG_FFCT_0 + (index * 4), UTC_0(u_t) | DTC_0(d_t));
}

void w600_sewect_td(stwuct wadeon_device *wdev,
		    enum w600_td td)
{
	if (td == W600_TD_AUTO)
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~FIW_FOWCE_TWEND_SEW);
	ewse
		WWEG32_P(SCWK_PWWMGT_CNTW, FIW_FOWCE_TWEND_SEW, ~FIW_FOWCE_TWEND_SEW);
	if (td == W600_TD_UP)
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~FIW_TWEND_MODE);
	if (td == W600_TD_DOWN)
		WWEG32_P(SCWK_PWWMGT_CNTW, FIW_TWEND_MODE, ~FIW_TWEND_MODE);
}

void w600_set_vwc(stwuct wadeon_device *wdev, u32 vwv)
{
	WWEG32(CG_FTV, vwv);
}

void w600_set_tpu(stwuct wadeon_device *wdev, u32 u)
{
	WWEG32_P(CG_TPC, TPU(u), ~TPU_MASK);
}

void w600_set_tpc(stwuct wadeon_device *wdev, u32 c)
{
	WWEG32_P(CG_TPC, TPCC(c), ~TPCC_MASK);
}

void w600_set_sstu(stwuct wadeon_device *wdev, u32 u)
{
	WWEG32_P(CG_SSP, CG_SSTU(u), ~CG_SSTU_MASK);
}

void w600_set_sst(stwuct wadeon_device *wdev, u32 t)
{
	WWEG32_P(CG_SSP, CG_SST(t), ~CG_SST_MASK);
}

void w600_set_git(stwuct wadeon_device *wdev, u32 t)
{
	WWEG32_P(CG_GIT, CG_GICST(t), ~CG_GICST_MASK);
}

void w600_set_fctu(stwuct wadeon_device *wdev, u32 u)
{
	WWEG32_P(CG_FC_T, FC_TU(u), ~FC_TU_MASK);
}

void w600_set_fct(stwuct wadeon_device *wdev, u32 t)
{
	WWEG32_P(CG_FC_T, FC_T(t), ~FC_T_MASK);
}

void w600_set_ctxcgtt3d_wphc(stwuct wadeon_device *wdev, u32 p)
{
	WWEG32_P(CG_CTX_CGTT3D_W, PHC(p), ~PHC_MASK);
}

void w600_set_ctxcgtt3d_wsdc(stwuct wadeon_device *wdev, u32 s)
{
	WWEG32_P(CG_CTX_CGTT3D_W, SDC(s), ~SDC_MASK);
}

void w600_set_vddc3d_oowsu(stwuct wadeon_device *wdev, u32 u)
{
	WWEG32_P(CG_VDDC3D_OOW, SU(u), ~SU_MASK);
}

void w600_set_vddc3d_oowphc(stwuct wadeon_device *wdev, u32 p)
{
	WWEG32_P(CG_VDDC3D_OOW, PHC(p), ~PHC_MASK);
}

void w600_set_vddc3d_oowsdc(stwuct wadeon_device *wdev, u32 s)
{
	WWEG32_P(CG_VDDC3D_OOW, SDC(s), ~SDC_MASK);
}

void w600_set_mpww_wock_time(stwuct wadeon_device *wdev, u32 wock_time)
{
	WWEG32_P(MPWW_TIME, MPWW_WOCK_TIME(wock_time), ~MPWW_WOCK_TIME_MASK);
}

void w600_set_mpww_weset_time(stwuct wadeon_device *wdev, u32 weset_time)
{
	WWEG32_P(MPWW_TIME, MPWW_WESET_TIME(weset_time), ~MPWW_WESET_TIME_MASK);
}

void w600_engine_cwock_entwy_enabwe(stwuct wadeon_device *wdev,
				    u32 index, boow enabwe)
{
	if (enabwe)
		WWEG32_P(SCWK_FWEQ_SETTING_STEP_0_PAWT2 + (index * 4 * 2),
			 STEP_0_SPWW_ENTWY_VAWID, ~STEP_0_SPWW_ENTWY_VAWID);
	ewse
		WWEG32_P(SCWK_FWEQ_SETTING_STEP_0_PAWT2 + (index * 4 * 2),
			 0, ~STEP_0_SPWW_ENTWY_VAWID);
}

void w600_engine_cwock_entwy_enabwe_puwse_skipping(stwuct wadeon_device *wdev,
						   u32 index, boow enabwe)
{
	if (enabwe)
		WWEG32_P(SCWK_FWEQ_SETTING_STEP_0_PAWT2 + (index * 4 * 2),
			 STEP_0_SPWW_STEP_ENABWE, ~STEP_0_SPWW_STEP_ENABWE);
	ewse
		WWEG32_P(SCWK_FWEQ_SETTING_STEP_0_PAWT2 + (index * 4 * 2),
			 0, ~STEP_0_SPWW_STEP_ENABWE);
}

void w600_engine_cwock_entwy_enabwe_post_dividew(stwuct wadeon_device *wdev,
						 u32 index, boow enabwe)
{
	if (enabwe)
		WWEG32_P(SCWK_FWEQ_SETTING_STEP_0_PAWT2 + (index * 4 * 2),
			 STEP_0_POST_DIV_EN, ~STEP_0_POST_DIV_EN);
	ewse
		WWEG32_P(SCWK_FWEQ_SETTING_STEP_0_PAWT2 + (index * 4 * 2),
			 0, ~STEP_0_POST_DIV_EN);
}

void w600_engine_cwock_entwy_set_post_dividew(stwuct wadeon_device *wdev,
					      u32 index, u32 dividew)
{
	WWEG32_P(SCWK_FWEQ_SETTING_STEP_0_PAWT1 + (index * 4 * 2),
		 STEP_0_SPWW_POST_DIV(dividew), ~STEP_0_SPWW_POST_DIV_MASK);
}

void w600_engine_cwock_entwy_set_wefewence_dividew(stwuct wadeon_device *wdev,
						   u32 index, u32 dividew)
{
	WWEG32_P(SCWK_FWEQ_SETTING_STEP_0_PAWT1 + (index * 4 * 2),
		 STEP_0_SPWW_WEF_DIV(dividew), ~STEP_0_SPWW_WEF_DIV_MASK);
}

void w600_engine_cwock_entwy_set_feedback_dividew(stwuct wadeon_device *wdev,
						  u32 index, u32 dividew)
{
	WWEG32_P(SCWK_FWEQ_SETTING_STEP_0_PAWT1 + (index * 4 * 2),
		 STEP_0_SPWW_FB_DIV(dividew), ~STEP_0_SPWW_FB_DIV_MASK);
}

void w600_engine_cwock_entwy_set_step_time(stwuct wadeon_device *wdev,
					   u32 index, u32 step_time)
{
	WWEG32_P(SCWK_FWEQ_SETTING_STEP_0_PAWT1 + (index * 4 * 2),
		 STEP_0_SPWW_STEP_TIME(step_time), ~STEP_0_SPWW_STEP_TIME_MASK);
}

void w600_vid_wt_set_ssu(stwuct wadeon_device *wdev, u32 u)
{
	WWEG32_P(VID_WT, SSTU(u), ~SSTU_MASK);
}

void w600_vid_wt_set_vwu(stwuct wadeon_device *wdev, u32 u)
{
	WWEG32_P(VID_WT, VID_CWTU(u), ~VID_CWTU_MASK);
}

void w600_vid_wt_set_vwt(stwuct wadeon_device *wdev, u32 wt)
{
	WWEG32_P(VID_WT, VID_CWT(wt), ~VID_CWT_MASK);
}

void w600_vowtage_contwow_enabwe_pins(stwuct wadeon_device *wdev,
				      u64 mask)
{
	WWEG32(WOWEW_GPIO_ENABWE, mask & 0xffffffff);
	WWEG32(UPPEW_GPIO_ENABWE, uppew_32_bits(mask));
}


void w600_vowtage_contwow_pwogwam_vowtages(stwuct wadeon_device *wdev,
					   enum w600_powew_wevew index, u64 pins)
{
	u32 tmp, mask;
	u32 ix = 3 - (3 & index);

	WWEG32(CTXSW_VID_WOWEW_GPIO_CNTW + (ix * 4), pins & 0xffffffff);

	mask = 7 << (3 * ix);
	tmp = WWEG32(VID_UPPEW_GPIO_CNTW);
	tmp = (tmp & ~mask) | ((pins >> (32 - (3 * ix))) & mask);
	WWEG32(VID_UPPEW_GPIO_CNTW, tmp);
}

void w600_vowtage_contwow_deactivate_static_contwow(stwuct wadeon_device *wdev,
						    u64 mask)
{
	u32 gpio;

	gpio = WWEG32(GPIOPAD_MASK);
	gpio &= ~mask;
	WWEG32(GPIOPAD_MASK, gpio);

	gpio = WWEG32(GPIOPAD_EN);
	gpio &= ~mask;
	WWEG32(GPIOPAD_EN, gpio);

	gpio = WWEG32(GPIOPAD_A);
	gpio &= ~mask;
	WWEG32(GPIOPAD_A, gpio);
}

void w600_powew_wevew_enabwe(stwuct wadeon_device *wdev,
			     enum w600_powew_wevew index, boow enabwe)
{
	u32 ix = 3 - (3 & index);

	if (enabwe)
		WWEG32_P(CTXSW_PWOFIWE_INDEX + (ix * 4), CTXSW_FWEQ_STATE_ENABWE,
			 ~CTXSW_FWEQ_STATE_ENABWE);
	ewse
		WWEG32_P(CTXSW_PWOFIWE_INDEX + (ix * 4), 0,
			 ~CTXSW_FWEQ_STATE_ENABWE);
}

void w600_powew_wevew_set_vowtage_index(stwuct wadeon_device *wdev,
					enum w600_powew_wevew index, u32 vowtage_index)
{
	u32 ix = 3 - (3 & index);

	WWEG32_P(CTXSW_PWOFIWE_INDEX + (ix * 4),
		 CTXSW_FWEQ_VIDS_CFG_INDEX(vowtage_index), ~CTXSW_FWEQ_VIDS_CFG_INDEX_MASK);
}

void w600_powew_wevew_set_mem_cwock_index(stwuct wadeon_device *wdev,
					  enum w600_powew_wevew index, u32 mem_cwock_index)
{
	u32 ix = 3 - (3 & index);

	WWEG32_P(CTXSW_PWOFIWE_INDEX + (ix * 4),
		 CTXSW_FWEQ_MCWK_CFG_INDEX(mem_cwock_index), ~CTXSW_FWEQ_MCWK_CFG_INDEX_MASK);
}

void w600_powew_wevew_set_eng_cwock_index(stwuct wadeon_device *wdev,
					  enum w600_powew_wevew index, u32 eng_cwock_index)
{
	u32 ix = 3 - (3 & index);

	WWEG32_P(CTXSW_PWOFIWE_INDEX + (ix * 4),
		 CTXSW_FWEQ_SCWK_CFG_INDEX(eng_cwock_index), ~CTXSW_FWEQ_SCWK_CFG_INDEX_MASK);
}

void w600_powew_wevew_set_watewmawk_id(stwuct wadeon_device *wdev,
				       enum w600_powew_wevew index,
				       enum w600_dispway_watewmawk watewmawk_id)
{
	u32 ix = 3 - (3 & index);
	u32 tmp = 0;

	if (watewmawk_id == W600_DISPWAY_WATEWMAWK_HIGH)
		tmp = CTXSW_FWEQ_DISPWAY_WATEWMAWK;
	WWEG32_P(CTXSW_PWOFIWE_INDEX + (ix * 4), tmp, ~CTXSW_FWEQ_DISPWAY_WATEWMAWK);
}

void w600_powew_wevew_set_pcie_gen2(stwuct wadeon_device *wdev,
				    enum w600_powew_wevew index, boow compatibwe)
{
	u32 ix = 3 - (3 & index);
	u32 tmp = 0;

	if (compatibwe)
		tmp = CTXSW_FWEQ_GEN2PCIE_VOWT;
	WWEG32_P(CTXSW_PWOFIWE_INDEX + (ix * 4), tmp, ~CTXSW_FWEQ_GEN2PCIE_VOWT);
}

enum w600_powew_wevew w600_powew_wevew_get_cuwwent_index(stwuct wadeon_device *wdev)
{
	u32 tmp;

	tmp = WWEG32(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & CUWWENT_PWOFIWE_INDEX_MASK;
	tmp >>= CUWWENT_PWOFIWE_INDEX_SHIFT;
	wetuwn tmp;
}

enum w600_powew_wevew w600_powew_wevew_get_tawget_index(stwuct wadeon_device *wdev)
{
	u32 tmp;

	tmp = WWEG32(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & TAWGET_PWOFIWE_INDEX_MASK;
	tmp >>= TAWGET_PWOFIWE_INDEX_SHIFT;
	wetuwn tmp;
}

void w600_powew_wevew_set_entew_index(stwuct wadeon_device *wdev,
				      enum w600_powew_wevew index)
{
	WWEG32_P(TAWGET_AND_CUWWENT_PWOFIWE_INDEX, DYN_PWW_ENTEW_INDEX(index),
		 ~DYN_PWW_ENTEW_INDEX_MASK);
}

void w600_wait_fow_powew_wevew_unequaw(stwuct wadeon_device *wdev,
				       enum w600_powew_wevew index)
{
	int i;

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (w600_powew_wevew_get_tawget_index(wdev) != index)
			bweak;
		udeway(1);
	}

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (w600_powew_wevew_get_cuwwent_index(wdev) != index)
			bweak;
		udeway(1);
	}
}

void w600_wait_fow_powew_wevew(stwuct wadeon_device *wdev,
			       enum w600_powew_wevew index)
{
	int i;

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (w600_powew_wevew_get_tawget_index(wdev) == index)
			bweak;
		udeway(1);
	}

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (w600_powew_wevew_get_cuwwent_index(wdev) == index)
			bweak;
		udeway(1);
	}
}

void w600_stawt_dpm(stwuct wadeon_device *wdev)
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
	w600_enabwe_mcwk_contwow(wdev, twue);
}

void w600_stop_dpm(stwuct wadeon_device *wdev)
{
	w600_dynamicpm_enabwe(wdev, fawse);
}

int w600_dpm_pwe_set_powew_state(stwuct wadeon_device *wdev)
{
	wetuwn 0;
}

void w600_dpm_post_set_powew_state(stwuct wadeon_device *wdev)
{

}

boow w600_is_uvd_state(u32 cwass, u32 cwass2)
{
	if (cwass & ATOM_PPWIB_CWASSIFICATION_UVDSTATE)
		wetuwn twue;
	if (cwass & ATOM_PPWIB_CWASSIFICATION_HD2STATE)
		wetuwn twue;
	if (cwass & ATOM_PPWIB_CWASSIFICATION_HDSTATE)
		wetuwn twue;
	if (cwass & ATOM_PPWIB_CWASSIFICATION_SDSTATE)
		wetuwn twue;
	if (cwass2 & ATOM_PPWIB_CWASSIFICATION2_MVC)
		wetuwn twue;
	wetuwn fawse;
}

static int w600_set_thewmaw_tempewatuwe_wange(stwuct wadeon_device *wdev,
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

boow w600_is_intewnaw_thewmaw_sensow(enum wadeon_int_thewmaw_type sensow)
{
	switch (sensow) {
	case THEWMAW_TYPE_WV6XX:
	case THEWMAW_TYPE_WV770:
	case THEWMAW_TYPE_EVEWGWEEN:
	case THEWMAW_TYPE_SUMO:
	case THEWMAW_TYPE_NI:
	case THEWMAW_TYPE_SI:
	case THEWMAW_TYPE_CI:
	case THEWMAW_TYPE_KV:
		wetuwn twue;
	case THEWMAW_TYPE_ADT7473_WITH_INTEWNAW:
	case THEWMAW_TYPE_EMC2103_WITH_INTEWNAW:
		wetuwn fawse; /* need speciaw handwing */
	case THEWMAW_TYPE_NONE:
	case THEWMAW_TYPE_EXTEWNAW:
	case THEWMAW_TYPE_EXTEWNAW_GPIO:
	defauwt:
		wetuwn fawse;
	}
}

int w600_dpm_wate_enabwe(stwuct wadeon_device *wdev)
{
	int wet;

	if (wdev->iwq.instawwed &&
	    w600_is_intewnaw_thewmaw_sensow(wdev->pm.int_thewmaw_type)) {
		wet = w600_set_thewmaw_tempewatuwe_wange(wdev, W600_TEMP_WANGE_MIN, W600_TEMP_WANGE_MAX);
		if (wet)
			wetuwn wet;
		wdev->iwq.dpm_thewmaw = twue;
		wadeon_iwq_set(wdev);
	}

	wetuwn 0;
}

union powew_info {
	stwuct _ATOM_POWEWPWAY_INFO info;
	stwuct _ATOM_POWEWPWAY_INFO_V2 info_2;
	stwuct _ATOM_POWEWPWAY_INFO_V3 info_3;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE ppwib;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE2 ppwib2;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE3 ppwib3;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE4 ppwib4;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE5 ppwib5;
};

union fan_info {
	stwuct _ATOM_PPWIB_FANTABWE fan;
	stwuct _ATOM_PPWIB_FANTABWE2 fan2;
	stwuct _ATOM_PPWIB_FANTABWE3 fan3;
};

static int w600_pawse_cwk_vowtage_dep_tabwe(stwuct wadeon_cwock_vowtage_dependency_tabwe *wadeon_tabwe,
					    ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *atom_tabwe)
{
	int i;
	ATOM_PPWIB_Cwock_Vowtage_Dependency_Wecowd *entwy;

	wadeon_tabwe->entwies = kcawwoc(atom_tabwe->ucNumEntwies,
					sizeof(stwuct wadeon_cwock_vowtage_dependency_entwy),
					GFP_KEWNEW);
	if (!wadeon_tabwe->entwies)
		wetuwn -ENOMEM;

	entwy = &atom_tabwe->entwies[0];
	fow (i = 0; i < atom_tabwe->ucNumEntwies; i++) {
		wadeon_tabwe->entwies[i].cwk = we16_to_cpu(entwy->usCwockWow) |
			(entwy->ucCwockHigh << 16);
		wadeon_tabwe->entwies[i].v = we16_to_cpu(entwy->usVowtage);
		entwy = (ATOM_PPWIB_Cwock_Vowtage_Dependency_Wecowd *)
			((u8 *)entwy + sizeof(ATOM_PPWIB_Cwock_Vowtage_Dependency_Wecowd));
	}
	wadeon_tabwe->count = atom_tabwe->ucNumEntwies;

	wetuwn 0;
}

int w600_get_pwatfowm_caps(stwuct wadeon_device *wdev)
{
	stwuct wadeon_mode_info *mode_info = &wdev->mode_info;
	union powew_info *powew_info;
	int index = GetIndexIntoMastewTabwe(DATA, PowewPwayInfo);
	u16 data_offset;
	u8 fwev, cwev;

	if (!atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset))
		wetuwn -EINVAW;
	powew_info = (union powew_info *)(mode_info->atom_context->bios + data_offset);

	wdev->pm.dpm.pwatfowm_caps = we32_to_cpu(powew_info->ppwib.uwPwatfowmCaps);
	wdev->pm.dpm.backbias_wesponse_time = we16_to_cpu(powew_info->ppwib.usBackbiasTime);
	wdev->pm.dpm.vowtage_wesponse_time = we16_to_cpu(powew_info->ppwib.usVowtageTime);

	wetuwn 0;
}

/* sizeof(ATOM_PPWIB_EXTENDEDHEADEW) */
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V2 12
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V3 14
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V4 16
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V5 18
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V6 20
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V7 22

int w600_pawse_extended_powew_tabwe(stwuct wadeon_device *wdev)
{
	stwuct wadeon_mode_info *mode_info = &wdev->mode_info;
	union powew_info *powew_info;
	union fan_info *fan_info;
	ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *dep_tabwe;
	int index = GetIndexIntoMastewTabwe(DATA, PowewPwayInfo);
	u16 data_offset;
	u8 fwev, cwev;
	int wet, i;

	if (!atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset))
		wetuwn -EINVAW;
	powew_info = (union powew_info *)(mode_info->atom_context->bios + data_offset);

	/* fan tabwe */
	if (we16_to_cpu(powew_info->ppwib.usTabweSize) >=
	    sizeof(stwuct _ATOM_PPWIB_POWEWPWAYTABWE3)) {
		if (powew_info->ppwib3.usFanTabweOffset) {
			fan_info = (union fan_info *)(mode_info->atom_context->bios + data_offset +
						      we16_to_cpu(powew_info->ppwib3.usFanTabweOffset));
			wdev->pm.dpm.fan.t_hyst = fan_info->fan.ucTHyst;
			wdev->pm.dpm.fan.t_min = we16_to_cpu(fan_info->fan.usTMin);
			wdev->pm.dpm.fan.t_med = we16_to_cpu(fan_info->fan.usTMed);
			wdev->pm.dpm.fan.t_high = we16_to_cpu(fan_info->fan.usTHigh);
			wdev->pm.dpm.fan.pwm_min = we16_to_cpu(fan_info->fan.usPWMMin);
			wdev->pm.dpm.fan.pwm_med = we16_to_cpu(fan_info->fan.usPWMMed);
			wdev->pm.dpm.fan.pwm_high = we16_to_cpu(fan_info->fan.usPWMHigh);
			if (fan_info->fan.ucFanTabweFowmat >= 2)
				wdev->pm.dpm.fan.t_max = we16_to_cpu(fan_info->fan2.usTMax);
			ewse
				wdev->pm.dpm.fan.t_max = 10900;
			wdev->pm.dpm.fan.cycwe_deway = 100000;
			if (fan_info->fan.ucFanTabweFowmat >= 3) {
				wdev->pm.dpm.fan.contwow_mode = fan_info->fan3.ucFanContwowMode;
				wdev->pm.dpm.fan.defauwt_max_fan_pwm =
					we16_to_cpu(fan_info->fan3.usFanPWMMax);
				wdev->pm.dpm.fan.defauwt_fan_output_sensitivity = 4836;
				wdev->pm.dpm.fan.fan_output_sensitivity =
					we16_to_cpu(fan_info->fan3.usFanOutputSensitivity);
			}
			wdev->pm.dpm.fan.ucode_fan_contwow = twue;
		}
	}

	/* cwock dependancy tabwes, shedding tabwes */
	if (we16_to_cpu(powew_info->ppwib.usTabweSize) >=
	    sizeof(stwuct _ATOM_PPWIB_POWEWPWAYTABWE4)) {
		if (powew_info->ppwib4.usVddcDependencyOnSCWKOffset) {
			dep_tabwe = (ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(powew_info->ppwib4.usVddcDependencyOnSCWKOffset));
			wet = w600_pawse_cwk_vowtage_dep_tabwe(&wdev->pm.dpm.dyn_state.vddc_dependency_on_scwk,
							       dep_tabwe);
			if (wet)
				wetuwn wet;
		}
		if (powew_info->ppwib4.usVddciDependencyOnMCWKOffset) {
			dep_tabwe = (ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(powew_info->ppwib4.usVddciDependencyOnMCWKOffset));
			wet = w600_pawse_cwk_vowtage_dep_tabwe(&wdev->pm.dpm.dyn_state.vddci_dependency_on_mcwk,
							       dep_tabwe);
			if (wet) {
				kfwee(wdev->pm.dpm.dyn_state.vddc_dependency_on_scwk.entwies);
				wetuwn wet;
			}
		}
		if (powew_info->ppwib4.usVddcDependencyOnMCWKOffset) {
			dep_tabwe = (ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(powew_info->ppwib4.usVddcDependencyOnMCWKOffset));
			wet = w600_pawse_cwk_vowtage_dep_tabwe(&wdev->pm.dpm.dyn_state.vddc_dependency_on_mcwk,
							       dep_tabwe);
			if (wet) {
				kfwee(wdev->pm.dpm.dyn_state.vddc_dependency_on_scwk.entwies);
				kfwee(wdev->pm.dpm.dyn_state.vddci_dependency_on_mcwk.entwies);
				wetuwn wet;
			}
		}
		if (powew_info->ppwib4.usMvddDependencyOnMCWKOffset) {
			dep_tabwe = (ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(powew_info->ppwib4.usMvddDependencyOnMCWKOffset));
			wet = w600_pawse_cwk_vowtage_dep_tabwe(&wdev->pm.dpm.dyn_state.mvdd_dependency_on_mcwk,
							       dep_tabwe);
			if (wet) {
				kfwee(wdev->pm.dpm.dyn_state.vddc_dependency_on_scwk.entwies);
				kfwee(wdev->pm.dpm.dyn_state.vddci_dependency_on_mcwk.entwies);
				kfwee(wdev->pm.dpm.dyn_state.vddc_dependency_on_mcwk.entwies);
				wetuwn wet;
			}
		}
		if (powew_info->ppwib4.usMaxCwockVowtageOnDCOffset) {
			ATOM_PPWIB_Cwock_Vowtage_Wimit_Tabwe *cwk_v =
				(ATOM_PPWIB_Cwock_Vowtage_Wimit_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(powew_info->ppwib4.usMaxCwockVowtageOnDCOffset));
			if (cwk_v->ucNumEntwies) {
				wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc.scwk =
					we16_to_cpu(cwk_v->entwies[0].usScwkWow) |
					(cwk_v->entwies[0].ucScwkHigh << 16);
				wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc.mcwk =
					we16_to_cpu(cwk_v->entwies[0].usMcwkWow) |
					(cwk_v->entwies[0].ucMcwkHigh << 16);
				wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc.vddc =
					we16_to_cpu(cwk_v->entwies[0].usVddc);
				wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc.vddci =
					we16_to_cpu(cwk_v->entwies[0].usVddci);
			}
		}
		if (powew_info->ppwib4.usVddcPhaseShedWimitsTabweOffset) {
			ATOM_PPWIB_PhaseSheddingWimits_Tabwe *psw =
				(ATOM_PPWIB_PhaseSheddingWimits_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(powew_info->ppwib4.usVddcPhaseShedWimitsTabweOffset));
			ATOM_PPWIB_PhaseSheddingWimits_Wecowd *entwy;

			wdev->pm.dpm.dyn_state.phase_shedding_wimits_tabwe.entwies =
				kcawwoc(psw->ucNumEntwies,
					sizeof(stwuct wadeon_phase_shedding_wimits_entwy),
					GFP_KEWNEW);
			if (!wdev->pm.dpm.dyn_state.phase_shedding_wimits_tabwe.entwies) {
				w600_fwee_extended_powew_tabwe(wdev);
				wetuwn -ENOMEM;
			}

			entwy = &psw->entwies[0];
			fow (i = 0; i < psw->ucNumEntwies; i++) {
				wdev->pm.dpm.dyn_state.phase_shedding_wimits_tabwe.entwies[i].scwk =
					we16_to_cpu(entwy->usScwkWow) | (entwy->ucScwkHigh << 16);
				wdev->pm.dpm.dyn_state.phase_shedding_wimits_tabwe.entwies[i].mcwk =
					we16_to_cpu(entwy->usMcwkWow) | (entwy->ucMcwkHigh << 16);
				wdev->pm.dpm.dyn_state.phase_shedding_wimits_tabwe.entwies[i].vowtage =
					we16_to_cpu(entwy->usVowtage);
				entwy = (ATOM_PPWIB_PhaseSheddingWimits_Wecowd *)
					((u8 *)entwy + sizeof(ATOM_PPWIB_PhaseSheddingWimits_Wecowd));
			}
			wdev->pm.dpm.dyn_state.phase_shedding_wimits_tabwe.count =
				psw->ucNumEntwies;
		}
	}

	/* cac data */
	if (we16_to_cpu(powew_info->ppwib.usTabweSize) >=
	    sizeof(stwuct _ATOM_PPWIB_POWEWPWAYTABWE5)) {
		wdev->pm.dpm.tdp_wimit = we32_to_cpu(powew_info->ppwib5.uwTDPWimit);
		wdev->pm.dpm.neaw_tdp_wimit = we32_to_cpu(powew_info->ppwib5.uwNeawTDPWimit);
		wdev->pm.dpm.neaw_tdp_wimit_adjusted = wdev->pm.dpm.neaw_tdp_wimit;
		wdev->pm.dpm.tdp_od_wimit = we16_to_cpu(powew_info->ppwib5.usTDPODWimit);
		if (wdev->pm.dpm.tdp_od_wimit)
			wdev->pm.dpm.powew_contwow = twue;
		ewse
			wdev->pm.dpm.powew_contwow = fawse;
		wdev->pm.dpm.tdp_adjustment = 0;
		wdev->pm.dpm.sq_wamping_thweshowd = we32_to_cpu(powew_info->ppwib5.uwSQWampingThweshowd);
		wdev->pm.dpm.cac_weakage = we32_to_cpu(powew_info->ppwib5.uwCACWeakage);
		wdev->pm.dpm.woad_wine_swope = we16_to_cpu(powew_info->ppwib5.usWoadWineSwope);
		if (powew_info->ppwib5.usCACWeakageTabweOffset) {
			ATOM_PPWIB_CAC_Weakage_Tabwe *cac_tabwe =
				(ATOM_PPWIB_CAC_Weakage_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(powew_info->ppwib5.usCACWeakageTabweOffset));
			ATOM_PPWIB_CAC_Weakage_Wecowd *entwy;
			u32 size = cac_tabwe->ucNumEntwies * sizeof(stwuct wadeon_cac_weakage_tabwe);
			wdev->pm.dpm.dyn_state.cac_weakage_tabwe.entwies = kzawwoc(size, GFP_KEWNEW);
			if (!wdev->pm.dpm.dyn_state.cac_weakage_tabwe.entwies) {
				w600_fwee_extended_powew_tabwe(wdev);
				wetuwn -ENOMEM;
			}
			entwy = &cac_tabwe->entwies[0];
			fow (i = 0; i < cac_tabwe->ucNumEntwies; i++) {
				if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_EVV) {
					wdev->pm.dpm.dyn_state.cac_weakage_tabwe.entwies[i].vddc1 =
						we16_to_cpu(entwy->usVddc1);
					wdev->pm.dpm.dyn_state.cac_weakage_tabwe.entwies[i].vddc2 =
						we16_to_cpu(entwy->usVddc2);
					wdev->pm.dpm.dyn_state.cac_weakage_tabwe.entwies[i].vddc3 =
						we16_to_cpu(entwy->usVddc3);
				} ewse {
					wdev->pm.dpm.dyn_state.cac_weakage_tabwe.entwies[i].vddc =
						we16_to_cpu(entwy->usVddc);
					wdev->pm.dpm.dyn_state.cac_weakage_tabwe.entwies[i].weakage =
						we32_to_cpu(entwy->uwWeakageVawue);
				}
				entwy = (ATOM_PPWIB_CAC_Weakage_Wecowd *)
					((u8 *)entwy + sizeof(ATOM_PPWIB_CAC_Weakage_Wecowd));
			}
			wdev->pm.dpm.dyn_state.cac_weakage_tabwe.count = cac_tabwe->ucNumEntwies;
		}
	}

	/* ext tabwes */
	if (we16_to_cpu(powew_info->ppwib.usTabweSize) >=
	    sizeof(stwuct _ATOM_PPWIB_POWEWPWAYTABWE3)) {
		ATOM_PPWIB_EXTENDEDHEADEW *ext_hdw = (ATOM_PPWIB_EXTENDEDHEADEW *)
			(mode_info->atom_context->bios + data_offset +
			 we16_to_cpu(powew_info->ppwib3.usExtendendedHeadewOffset));
		if ((we16_to_cpu(ext_hdw->usSize) >= SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V2) &&
			ext_hdw->usVCETabweOffset) {
			VCECwockInfoAwway *awway = (VCECwockInfoAwway *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(ext_hdw->usVCETabweOffset) + 1);
			ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Tabwe *wimits =
				(ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(ext_hdw->usVCETabweOffset) + 1 +
				 1 + awway->ucNumEntwies * sizeof(VCECwockInfo));
			ATOM_PPWIB_VCE_State_Tabwe *states =
				(ATOM_PPWIB_VCE_State_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(ext_hdw->usVCETabweOffset) + 1 +
				 1 + (awway->ucNumEntwies * sizeof (VCECwockInfo)) +
				 1 + (wimits->numEntwies * sizeof(ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Wecowd)));
			ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Wecowd *entwy;
			ATOM_PPWIB_VCE_State_Wecowd *state_entwy;
			VCECwockInfo *vce_cwk;
			u32 size = wimits->numEntwies *
				sizeof(stwuct wadeon_vce_cwock_vowtage_dependency_entwy);
			wdev->pm.dpm.dyn_state.vce_cwock_vowtage_dependency_tabwe.entwies =
				kzawwoc(size, GFP_KEWNEW);
			if (!wdev->pm.dpm.dyn_state.vce_cwock_vowtage_dependency_tabwe.entwies) {
				w600_fwee_extended_powew_tabwe(wdev);
				wetuwn -ENOMEM;
			}
			wdev->pm.dpm.dyn_state.vce_cwock_vowtage_dependency_tabwe.count =
				wimits->numEntwies;
			entwy = &wimits->entwies[0];
			state_entwy = &states->entwies[0];
			fow (i = 0; i < wimits->numEntwies; i++) {
				vce_cwk = (VCECwockInfo *)
					((u8 *)&awway->entwies[0] +
					 (entwy->ucVCECwockInfoIndex * sizeof(VCECwockInfo)));
				wdev->pm.dpm.dyn_state.vce_cwock_vowtage_dependency_tabwe.entwies[i].evcwk =
					we16_to_cpu(vce_cwk->usEVCwkWow) | (vce_cwk->ucEVCwkHigh << 16);
				wdev->pm.dpm.dyn_state.vce_cwock_vowtage_dependency_tabwe.entwies[i].eccwk =
					we16_to_cpu(vce_cwk->usECCwkWow) | (vce_cwk->ucECCwkHigh << 16);
				wdev->pm.dpm.dyn_state.vce_cwock_vowtage_dependency_tabwe.entwies[i].v =
					we16_to_cpu(entwy->usVowtage);
				entwy = (ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Wecowd *)
					((u8 *)entwy + sizeof(ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Wecowd));
			}
			fow (i = 0; i < states->numEntwies; i++) {
				if (i >= WADEON_MAX_VCE_WEVEWS)
					bweak;
				vce_cwk = (VCECwockInfo *)
					((u8 *)&awway->entwies[0] +
					 (state_entwy->ucVCECwockInfoIndex * sizeof(VCECwockInfo)));
				wdev->pm.dpm.vce_states[i].evcwk =
					we16_to_cpu(vce_cwk->usEVCwkWow) | (vce_cwk->ucEVCwkHigh << 16);
				wdev->pm.dpm.vce_states[i].eccwk =
					we16_to_cpu(vce_cwk->usECCwkWow) | (vce_cwk->ucECCwkHigh << 16);
				wdev->pm.dpm.vce_states[i].cwk_idx =
					state_entwy->ucCwockInfoIndex & 0x3f;
				wdev->pm.dpm.vce_states[i].pstate =
					(state_entwy->ucCwockInfoIndex & 0xc0) >> 6;
				state_entwy = (ATOM_PPWIB_VCE_State_Wecowd *)
					((u8 *)state_entwy + sizeof(ATOM_PPWIB_VCE_State_Wecowd));
			}
		}
		if ((we16_to_cpu(ext_hdw->usSize) >= SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V3) &&
			ext_hdw->usUVDTabweOffset) {
			UVDCwockInfoAwway *awway = (UVDCwockInfoAwway *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(ext_hdw->usUVDTabweOffset) + 1);
			ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Tabwe *wimits =
				(ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(ext_hdw->usUVDTabweOffset) + 1 +
				 1 + (awway->ucNumEntwies * sizeof (UVDCwockInfo)));
			ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Wecowd *entwy;
			u32 size = wimits->numEntwies *
				sizeof(stwuct wadeon_uvd_cwock_vowtage_dependency_entwy);
			wdev->pm.dpm.dyn_state.uvd_cwock_vowtage_dependency_tabwe.entwies =
				kzawwoc(size, GFP_KEWNEW);
			if (!wdev->pm.dpm.dyn_state.uvd_cwock_vowtage_dependency_tabwe.entwies) {
				w600_fwee_extended_powew_tabwe(wdev);
				wetuwn -ENOMEM;
			}
			wdev->pm.dpm.dyn_state.uvd_cwock_vowtage_dependency_tabwe.count =
				wimits->numEntwies;
			entwy = &wimits->entwies[0];
			fow (i = 0; i < wimits->numEntwies; i++) {
				UVDCwockInfo *uvd_cwk = (UVDCwockInfo *)
					((u8 *)&awway->entwies[0] +
					 (entwy->ucUVDCwockInfoIndex * sizeof(UVDCwockInfo)));
				wdev->pm.dpm.dyn_state.uvd_cwock_vowtage_dependency_tabwe.entwies[i].vcwk =
					we16_to_cpu(uvd_cwk->usVCwkWow) | (uvd_cwk->ucVCwkHigh << 16);
				wdev->pm.dpm.dyn_state.uvd_cwock_vowtage_dependency_tabwe.entwies[i].dcwk =
					we16_to_cpu(uvd_cwk->usDCwkWow) | (uvd_cwk->ucDCwkHigh << 16);
				wdev->pm.dpm.dyn_state.uvd_cwock_vowtage_dependency_tabwe.entwies[i].v =
					we16_to_cpu(entwy->usVowtage);
				entwy = (ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Wecowd *)
					((u8 *)entwy + sizeof(ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Wecowd));
			}
		}
		if ((we16_to_cpu(ext_hdw->usSize) >= SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V4) &&
			ext_hdw->usSAMUTabweOffset) {
			ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Tabwe *wimits =
				(ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(ext_hdw->usSAMUTabweOffset) + 1);
			ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Wecowd *entwy;
			u32 size = wimits->numEntwies *
				sizeof(stwuct wadeon_cwock_vowtage_dependency_entwy);
			wdev->pm.dpm.dyn_state.samu_cwock_vowtage_dependency_tabwe.entwies =
				kzawwoc(size, GFP_KEWNEW);
			if (!wdev->pm.dpm.dyn_state.samu_cwock_vowtage_dependency_tabwe.entwies) {
				w600_fwee_extended_powew_tabwe(wdev);
				wetuwn -ENOMEM;
			}
			wdev->pm.dpm.dyn_state.samu_cwock_vowtage_dependency_tabwe.count =
				wimits->numEntwies;
			entwy = &wimits->entwies[0];
			fow (i = 0; i < wimits->numEntwies; i++) {
				wdev->pm.dpm.dyn_state.samu_cwock_vowtage_dependency_tabwe.entwies[i].cwk =
					we16_to_cpu(entwy->usSAMCwockWow) | (entwy->ucSAMCwockHigh << 16);
				wdev->pm.dpm.dyn_state.samu_cwock_vowtage_dependency_tabwe.entwies[i].v =
					we16_to_cpu(entwy->usVowtage);
				entwy = (ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Wecowd *)
					((u8 *)entwy + sizeof(ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Wecowd));
			}
		}
		if ((we16_to_cpu(ext_hdw->usSize) >= SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V5) &&
		    ext_hdw->usPPMTabweOffset) {
			ATOM_PPWIB_PPM_Tabwe *ppm = (ATOM_PPWIB_PPM_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(ext_hdw->usPPMTabweOffset));
			wdev->pm.dpm.dyn_state.ppm_tabwe =
				kzawwoc(sizeof(stwuct wadeon_ppm_tabwe), GFP_KEWNEW);
			if (!wdev->pm.dpm.dyn_state.ppm_tabwe) {
				w600_fwee_extended_powew_tabwe(wdev);
				wetuwn -ENOMEM;
			}
			wdev->pm.dpm.dyn_state.ppm_tabwe->ppm_design = ppm->ucPpmDesign;
			wdev->pm.dpm.dyn_state.ppm_tabwe->cpu_cowe_numbew =
				we16_to_cpu(ppm->usCpuCoweNumbew);
			wdev->pm.dpm.dyn_state.ppm_tabwe->pwatfowm_tdp =
				we32_to_cpu(ppm->uwPwatfowmTDP);
			wdev->pm.dpm.dyn_state.ppm_tabwe->smaww_ac_pwatfowm_tdp =
				we32_to_cpu(ppm->uwSmawwACPwatfowmTDP);
			wdev->pm.dpm.dyn_state.ppm_tabwe->pwatfowm_tdc =
				we32_to_cpu(ppm->uwPwatfowmTDC);
			wdev->pm.dpm.dyn_state.ppm_tabwe->smaww_ac_pwatfowm_tdc =
				we32_to_cpu(ppm->uwSmawwACPwatfowmTDC);
			wdev->pm.dpm.dyn_state.ppm_tabwe->apu_tdp =
				we32_to_cpu(ppm->uwApuTDP);
			wdev->pm.dpm.dyn_state.ppm_tabwe->dgpu_tdp =
				we32_to_cpu(ppm->uwDGpuTDP);
			wdev->pm.dpm.dyn_state.ppm_tabwe->dgpu_uwv_powew =
				we32_to_cpu(ppm->uwDGpuUwvPowew);
			wdev->pm.dpm.dyn_state.ppm_tabwe->tj_max =
				we32_to_cpu(ppm->uwTjmax);
		}
		if ((we16_to_cpu(ext_hdw->usSize) >= SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V6) &&
			ext_hdw->usACPTabweOffset) {
			ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Tabwe *wimits =
				(ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(ext_hdw->usACPTabweOffset) + 1);
			ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Wecowd *entwy;
			u32 size = wimits->numEntwies *
				sizeof(stwuct wadeon_cwock_vowtage_dependency_entwy);
			wdev->pm.dpm.dyn_state.acp_cwock_vowtage_dependency_tabwe.entwies =
				kzawwoc(size, GFP_KEWNEW);
			if (!wdev->pm.dpm.dyn_state.acp_cwock_vowtage_dependency_tabwe.entwies) {
				w600_fwee_extended_powew_tabwe(wdev);
				wetuwn -ENOMEM;
			}
			wdev->pm.dpm.dyn_state.acp_cwock_vowtage_dependency_tabwe.count =
				wimits->numEntwies;
			entwy = &wimits->entwies[0];
			fow (i = 0; i < wimits->numEntwies; i++) {
				wdev->pm.dpm.dyn_state.acp_cwock_vowtage_dependency_tabwe.entwies[i].cwk =
					we16_to_cpu(entwy->usACPCwockWow) | (entwy->ucACPCwockHigh << 16);
				wdev->pm.dpm.dyn_state.acp_cwock_vowtage_dependency_tabwe.entwies[i].v =
					we16_to_cpu(entwy->usVowtage);
				entwy = (ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Wecowd *)
					((u8 *)entwy + sizeof(ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Wecowd));
			}
		}
		if ((we16_to_cpu(ext_hdw->usSize) >= SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V7) &&
			ext_hdw->usPowewTuneTabweOffset) {
			u8 wev = *(u8 *)(mode_info->atom_context->bios + data_offset +
					 we16_to_cpu(ext_hdw->usPowewTuneTabweOffset));
			ATOM_PowewTune_Tabwe *pt;
			wdev->pm.dpm.dyn_state.cac_tdp_tabwe =
				kzawwoc(sizeof(stwuct wadeon_cac_tdp_tabwe), GFP_KEWNEW);
			if (!wdev->pm.dpm.dyn_state.cac_tdp_tabwe) {
				w600_fwee_extended_powew_tabwe(wdev);
				wetuwn -ENOMEM;
			}
			if (wev > 0) {
				ATOM_PPWIB_POWEWTUNE_Tabwe_V1 *ppt = (ATOM_PPWIB_POWEWTUNE_Tabwe_V1 *)
					(mode_info->atom_context->bios + data_offset +
					 we16_to_cpu(ext_hdw->usPowewTuneTabweOffset));
				wdev->pm.dpm.dyn_state.cac_tdp_tabwe->maximum_powew_dewivewy_wimit =
					we16_to_cpu(ppt->usMaximumPowewDewivewyWimit);
				pt = &ppt->powew_tune_tabwe;
			} ewse {
				ATOM_PPWIB_POWEWTUNE_Tabwe *ppt = (ATOM_PPWIB_POWEWTUNE_Tabwe *)
					(mode_info->atom_context->bios + data_offset +
					 we16_to_cpu(ext_hdw->usPowewTuneTabweOffset));
				wdev->pm.dpm.dyn_state.cac_tdp_tabwe->maximum_powew_dewivewy_wimit = 255;
				pt = &ppt->powew_tune_tabwe;
			}
			wdev->pm.dpm.dyn_state.cac_tdp_tabwe->tdp = we16_to_cpu(pt->usTDP);
			wdev->pm.dpm.dyn_state.cac_tdp_tabwe->configuwabwe_tdp =
				we16_to_cpu(pt->usConfiguwabweTDP);
			wdev->pm.dpm.dyn_state.cac_tdp_tabwe->tdc = we16_to_cpu(pt->usTDC);
			wdev->pm.dpm.dyn_state.cac_tdp_tabwe->battewy_powew_wimit =
				we16_to_cpu(pt->usBattewyPowewWimit);
			wdev->pm.dpm.dyn_state.cac_tdp_tabwe->smaww_powew_wimit =
				we16_to_cpu(pt->usSmawwPowewWimit);
			wdev->pm.dpm.dyn_state.cac_tdp_tabwe->wow_cac_weakage =
				we16_to_cpu(pt->usWowCACWeakage);
			wdev->pm.dpm.dyn_state.cac_tdp_tabwe->high_cac_weakage =
				we16_to_cpu(pt->usHighCACWeakage);
		}
	}

	wetuwn 0;
}

void w600_fwee_extended_powew_tabwe(stwuct wadeon_device *wdev)
{
	stwuct wadeon_dpm_dynamic_state *dyn_state = &wdev->pm.dpm.dyn_state;

	kfwee(dyn_state->vddc_dependency_on_scwk.entwies);
	kfwee(dyn_state->vddci_dependency_on_mcwk.entwies);
	kfwee(dyn_state->vddc_dependency_on_mcwk.entwies);
	kfwee(dyn_state->mvdd_dependency_on_mcwk.entwies);
	kfwee(dyn_state->cac_weakage_tabwe.entwies);
	kfwee(dyn_state->phase_shedding_wimits_tabwe.entwies);
	kfwee(dyn_state->ppm_tabwe);
	kfwee(dyn_state->cac_tdp_tabwe);
	kfwee(dyn_state->vce_cwock_vowtage_dependency_tabwe.entwies);
	kfwee(dyn_state->uvd_cwock_vowtage_dependency_tabwe.entwies);
	kfwee(dyn_state->samu_cwock_vowtage_dependency_tabwe.entwies);
	kfwee(dyn_state->acp_cwock_vowtage_dependency_tabwe.entwies);
}

enum wadeon_pcie_gen w600_get_pcie_gen_suppowt(stwuct wadeon_device *wdev,
					       u32 sys_mask,
					       enum wadeon_pcie_gen asic_gen,
					       enum wadeon_pcie_gen defauwt_gen)
{
	switch (asic_gen) {
	case WADEON_PCIE_GEN1:
		wetuwn WADEON_PCIE_GEN1;
	case WADEON_PCIE_GEN2:
		wetuwn WADEON_PCIE_GEN2;
	case WADEON_PCIE_GEN3:
		wetuwn WADEON_PCIE_GEN3;
	defauwt:
		if ((sys_mask & WADEON_PCIE_SPEED_80) && (defauwt_gen == WADEON_PCIE_GEN3))
			wetuwn WADEON_PCIE_GEN3;
		ewse if ((sys_mask & WADEON_PCIE_SPEED_50) && (defauwt_gen == WADEON_PCIE_GEN2))
			wetuwn WADEON_PCIE_GEN2;
		ewse
			wetuwn WADEON_PCIE_GEN1;
	}
	wetuwn WADEON_PCIE_GEN1;
}

u16 w600_get_pcie_wane_suppowt(stwuct wadeon_device *wdev,
			       u16 asic_wanes,
			       u16 defauwt_wanes)
{
	switch (asic_wanes) {
	case 0:
	defauwt:
		wetuwn defauwt_wanes;
	case 1:
		wetuwn 1;
	case 2:
		wetuwn 2;
	case 4:
		wetuwn 4;
	case 8:
		wetuwn 8;
	case 12:
		wetuwn 12;
	case 16:
		wetuwn 16;
	}
}

u8 w600_encode_pci_wane_width(u32 wanes)
{
	static const u8 encoded_wanes[] = {
		0, 1, 2, 0, 3, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 6
	};

	if (wanes > 16)
		wetuwn 0;

	wetuwn encoded_wanes[wanes];
}
