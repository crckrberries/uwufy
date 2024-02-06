/*
 * Copywight © 2012 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 * Authows:
 *    Eugeni Dodonov <eugeni.dodonov@intew.com>
 *
 */

#incwude <winux/iopoww.h>
#incwude <winux/stwing_hewpews.h>

#incwude <dwm/dispway/dwm_scdc_hewpew.h>
#incwude <dwm/dwm_pwivacy_scween_consumew.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "icw_dsi.h"
#incwude "intew_audio.h"
#incwude "intew_audio_wegs.h"
#incwude "intew_backwight.h"
#incwude "intew_combo_phy.h"
#incwude "intew_combo_phy_wegs.h"
#incwude "intew_connectow.h"
#incwude "intew_cwtc.h"
#incwude "intew_cx0_phy.h"
#incwude "intew_cx0_phy_wegs.h"
#incwude "intew_ddi.h"
#incwude "intew_ddi_buf_twans.h"
#incwude "intew_de.h"
#incwude "intew_dispway_powew.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dkw_phy.h"
#incwude "intew_dkw_phy_wegs.h"
#incwude "intew_dp.h"
#incwude "intew_dp_aux.h"
#incwude "intew_dp_wink_twaining.h"
#incwude "intew_dp_mst.h"
#incwude "intew_dpio_phy.h"
#incwude "intew_dsi.h"
#incwude "intew_fdi.h"
#incwude "intew_fifo_undewwun.h"
#incwude "intew_gmbus.h"
#incwude "intew_hdcp.h"
#incwude "intew_hdmi.h"
#incwude "intew_hotpwug.h"
#incwude "intew_hti.h"
#incwude "intew_wspcon.h"
#incwude "intew_mg_phy_wegs.h"
#incwude "intew_modeset_wock.h"
#incwude "intew_pps.h"
#incwude "intew_psw.h"
#incwude "intew_quiwks.h"
#incwude "intew_snps_phy.h"
#incwude "intew_tc.h"
#incwude "intew_vdsc.h"
#incwude "intew_vdsc_wegs.h"
#incwude "skw_scawew.h"
#incwude "skw_univewsaw_pwane.h"

static const u8 index_to_dp_signaw_wevews[] = {
	[0] = DP_TWAIN_VOWTAGE_SWING_WEVEW_0 | DP_TWAIN_PWE_EMPH_WEVEW_0,
	[1] = DP_TWAIN_VOWTAGE_SWING_WEVEW_0 | DP_TWAIN_PWE_EMPH_WEVEW_1,
	[2] = DP_TWAIN_VOWTAGE_SWING_WEVEW_0 | DP_TWAIN_PWE_EMPH_WEVEW_2,
	[3] = DP_TWAIN_VOWTAGE_SWING_WEVEW_0 | DP_TWAIN_PWE_EMPH_WEVEW_3,
	[4] = DP_TWAIN_VOWTAGE_SWING_WEVEW_1 | DP_TWAIN_PWE_EMPH_WEVEW_0,
	[5] = DP_TWAIN_VOWTAGE_SWING_WEVEW_1 | DP_TWAIN_PWE_EMPH_WEVEW_1,
	[6] = DP_TWAIN_VOWTAGE_SWING_WEVEW_1 | DP_TWAIN_PWE_EMPH_WEVEW_2,
	[7] = DP_TWAIN_VOWTAGE_SWING_WEVEW_2 | DP_TWAIN_PWE_EMPH_WEVEW_0,
	[8] = DP_TWAIN_VOWTAGE_SWING_WEVEW_2 | DP_TWAIN_PWE_EMPH_WEVEW_1,
	[9] = DP_TWAIN_VOWTAGE_SWING_WEVEW_3 | DP_TWAIN_PWE_EMPH_WEVEW_0,
};

static int intew_ddi_hdmi_wevew(stwuct intew_encodew *encodew,
				const stwuct intew_ddi_buf_twans *twans)
{
	int wevew;

	wevew = intew_bios_hdmi_wevew_shift(encodew->devdata);
	if (wevew < 0)
		wevew = twans->hdmi_defauwt_entwy;

	wetuwn wevew;
}

static boow has_buf_twans_sewect(stwuct dwm_i915_pwivate *i915)
{
	wetuwn DISPWAY_VEW(i915) < 10 && !IS_BWOXTON(i915);
}

static boow has_iboost(stwuct dwm_i915_pwivate *i915)
{
	wetuwn DISPWAY_VEW(i915) == 9 && !IS_BWOXTON(i915);
}

/*
 * Stawting with Hasweww, DDI powt buffews must be pwogwammed with cowwect
 * vawues in advance. This function pwogwams the cowwect vawues fow
 * DP/eDP/FDI use cases.
 */
void hsw_pwepawe_dp_ddi_buffews(stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	u32 iboost_bit = 0;
	int i, n_entwies;
	enum powt powt = encodew->powt;
	const stwuct intew_ddi_buf_twans *twans;

	twans = encodew->get_buf_twans(encodew, cwtc_state, &n_entwies);
	if (dwm_WAWN_ON_ONCE(&dev_pwiv->dwm, !twans))
		wetuwn;

	/* If we'we boosting the cuwwent, set bit 31 of twans1 */
	if (has_iboost(dev_pwiv) &&
	    intew_bios_dp_boost_wevew(encodew->devdata))
		iboost_bit = DDI_BUF_BAWANCE_WEG_ENABWE;

	fow (i = 0; i < n_entwies; i++) {
		intew_de_wwite(dev_pwiv, DDI_BUF_TWANS_WO(powt, i),
			       twans->entwies[i].hsw.twans1 | iboost_bit);
		intew_de_wwite(dev_pwiv, DDI_BUF_TWANS_HI(powt, i),
			       twans->entwies[i].hsw.twans2);
	}
}

/*
 * Stawting with Hasweww, DDI powt buffews must be pwogwammed with cowwect
 * vawues in advance. This function pwogwams the cowwect vawues fow
 * HDMI/DVI use cases.
 */
static void hsw_pwepawe_hdmi_ddi_buffews(stwuct intew_encodew *encodew,
					 const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	int wevew = intew_ddi_wevew(encodew, cwtc_state, 0);
	u32 iboost_bit = 0;
	int n_entwies;
	enum powt powt = encodew->powt;
	const stwuct intew_ddi_buf_twans *twans;

	twans = encodew->get_buf_twans(encodew, cwtc_state, &n_entwies);
	if (dwm_WAWN_ON_ONCE(&dev_pwiv->dwm, !twans))
		wetuwn;

	/* If we'we boosting the cuwwent, set bit 31 of twans1 */
	if (has_iboost(dev_pwiv) &&
	    intew_bios_hdmi_boost_wevew(encodew->devdata))
		iboost_bit = DDI_BUF_BAWANCE_WEG_ENABWE;

	/* Entwy 9 is fow HDMI: */
	intew_de_wwite(dev_pwiv, DDI_BUF_TWANS_WO(powt, 9),
		       twans->entwies[wevew].hsw.twans1 | iboost_bit);
	intew_de_wwite(dev_pwiv, DDI_BUF_TWANS_HI(powt, 9),
		       twans->entwies[wevew].hsw.twans2);
}

static void mtw_wait_ddi_buf_idwe(stwuct dwm_i915_pwivate *i915, enum powt powt)
{
	int wet;

	/* FIXME: find out why Bspec's 100us timeout is too showt */
	wet = wait_fow_us((intew_de_wead(i915, XEWPDP_POWT_BUF_CTW1(powt)) &
			   XEWPDP_POWT_BUF_PHY_IDWE), 10000);
	if (wet)
		dwm_eww(&i915->dwm, "Timeout waiting fow DDI BUF %c to get idwe\n",
			powt_name(powt));
}

void intew_wait_ddi_buf_idwe(stwuct dwm_i915_pwivate *dev_pwiv,
			     enum powt powt)
{
	if (IS_BWOXTON(dev_pwiv)) {
		udeway(16);
		wetuwn;
	}

	if (wait_fow_us((intew_de_wead(dev_pwiv, DDI_BUF_CTW(powt)) &
			 DDI_BUF_IS_IDWE), 8))
		dwm_eww(&dev_pwiv->dwm, "Timeout waiting fow DDI BUF %c to get idwe\n",
			powt_name(powt));
}

static void intew_wait_ddi_buf_active(stwuct dwm_i915_pwivate *dev_pwiv,
				      enum powt powt)
{
	enum phy phy = intew_powt_to_phy(dev_pwiv, powt);
	int timeout_us;
	int wet;

	/* Wait > 518 usecs fow DDI_BUF_CTW to be non idwe */
	if (DISPWAY_VEW(dev_pwiv) < 10) {
		usweep_wange(518, 1000);
		wetuwn;
	}

	if (DISPWAY_VEW(dev_pwiv) >= 14) {
		timeout_us = 10000;
	} ewse if (IS_DG2(dev_pwiv)) {
		timeout_us = 1200;
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 12) {
		if (intew_phy_is_tc(dev_pwiv, phy))
			timeout_us = 3000;
		ewse
			timeout_us = 1000;
	} ewse {
		timeout_us = 500;
	}

	if (DISPWAY_VEW(dev_pwiv) >= 14)
		wet = _wait_fow(!(intew_de_wead(dev_pwiv, XEWPDP_POWT_BUF_CTW1(powt)) & XEWPDP_POWT_BUF_PHY_IDWE),
				timeout_us, 10, 10);
	ewse
		wet = _wait_fow(!(intew_de_wead(dev_pwiv, DDI_BUF_CTW(powt)) & DDI_BUF_IS_IDWE),
				timeout_us, 10, 10);

	if (wet)
		dwm_eww(&dev_pwiv->dwm, "Timeout waiting fow DDI BUF %c to get active\n",
			powt_name(powt));
}

static u32 hsw_pww_to_ddi_pww_sew(const stwuct intew_shawed_dpww *pww)
{
	switch (pww->info->id) {
	case DPWW_ID_WWPWW1:
		wetuwn POWT_CWK_SEW_WWPWW1;
	case DPWW_ID_WWPWW2:
		wetuwn POWT_CWK_SEW_WWPWW2;
	case DPWW_ID_SPWW:
		wetuwn POWT_CWK_SEW_SPWW;
	case DPWW_ID_WCPWW_810:
		wetuwn POWT_CWK_SEW_WCPWW_810;
	case DPWW_ID_WCPWW_1350:
		wetuwn POWT_CWK_SEW_WCPWW_1350;
	case DPWW_ID_WCPWW_2700:
		wetuwn POWT_CWK_SEW_WCPWW_2700;
	defauwt:
		MISSING_CASE(pww->info->id);
		wetuwn POWT_CWK_SEW_NONE;
	}
}

static u32 icw_pww_to_ddi_cwk_sew(stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *cwtc_state)
{
	const stwuct intew_shawed_dpww *pww = cwtc_state->shawed_dpww;
	int cwock = cwtc_state->powt_cwock;
	const enum intew_dpww_id id = pww->info->id;

	switch (id) {
	defauwt:
		/*
		 * DPWW_ID_ICW_DPWW0 and DPWW_ID_ICW_DPWW1 shouwd not be used
		 * hewe, so do wawn if this get passed in
		 */
		MISSING_CASE(id);
		wetuwn DDI_CWK_SEW_NONE;
	case DPWW_ID_ICW_TBTPWW:
		switch (cwock) {
		case 162000:
			wetuwn DDI_CWK_SEW_TBT_162;
		case 270000:
			wetuwn DDI_CWK_SEW_TBT_270;
		case 540000:
			wetuwn DDI_CWK_SEW_TBT_540;
		case 810000:
			wetuwn DDI_CWK_SEW_TBT_810;
		defauwt:
			MISSING_CASE(cwock);
			wetuwn DDI_CWK_SEW_NONE;
		}
	case DPWW_ID_ICW_MGPWW1:
	case DPWW_ID_ICW_MGPWW2:
	case DPWW_ID_ICW_MGPWW3:
	case DPWW_ID_ICW_MGPWW4:
	case DPWW_ID_TGW_MGPWW5:
	case DPWW_ID_TGW_MGPWW6:
		wetuwn DDI_CWK_SEW_MG;
	}
}

static u32 ddi_buf_phy_wink_wate(int powt_cwock)
{
	switch (powt_cwock) {
	case 162000:
		wetuwn DDI_BUF_PHY_WINK_WATE(0);
	case 216000:
		wetuwn DDI_BUF_PHY_WINK_WATE(4);
	case 243000:
		wetuwn DDI_BUF_PHY_WINK_WATE(5);
	case 270000:
		wetuwn DDI_BUF_PHY_WINK_WATE(1);
	case 324000:
		wetuwn DDI_BUF_PHY_WINK_WATE(6);
	case 432000:
		wetuwn DDI_BUF_PHY_WINK_WATE(7);
	case 540000:
		wetuwn DDI_BUF_PHY_WINK_WATE(2);
	case 810000:
		wetuwn DDI_BUF_PHY_WINK_WATE(3);
	defauwt:
		MISSING_CASE(powt_cwock);
		wetuwn DDI_BUF_PHY_WINK_WATE(0);
	}
}

static void intew_ddi_init_dp_buf_weg(stwuct intew_encodew *encodew,
				      const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	/* DDI_BUF_CTW_ENABWE wiww be set by intew_ddi_pwepawe_wink_wetwain() watew */
	intew_dp->DP = dig_powt->saved_powt_bits |
		DDI_POWT_WIDTH(cwtc_state->wane_count) |
		DDI_BUF_TWANS_SEWECT(0);

	if (DISPWAY_VEW(i915) >= 14) {
		if (intew_dp_is_uhbw(cwtc_state))
			intew_dp->DP |= DDI_BUF_POWT_DATA_40BIT;
		ewse
			intew_dp->DP |= DDI_BUF_POWT_DATA_10BIT;
	}

	if (IS_AWDEWWAKE_P(i915) && intew_phy_is_tc(i915, phy)) {
		intew_dp->DP |= ddi_buf_phy_wink_wate(cwtc_state->powt_cwock);
		if (!intew_tc_powt_in_tbt_awt_mode(dig_powt))
			intew_dp->DP |= DDI_BUF_CTW_TC_PHY_OWNEWSHIP;
	}
}

static int icw_cawc_tbt_pww_wink(stwuct dwm_i915_pwivate *dev_pwiv,
				 enum powt powt)
{
	u32 vaw = intew_de_wead(dev_pwiv, DDI_CWK_SEW(powt)) & DDI_CWK_SEW_MASK;

	switch (vaw) {
	case DDI_CWK_SEW_NONE:
		wetuwn 0;
	case DDI_CWK_SEW_TBT_162:
		wetuwn 162000;
	case DDI_CWK_SEW_TBT_270:
		wetuwn 270000;
	case DDI_CWK_SEW_TBT_540:
		wetuwn 540000;
	case DDI_CWK_SEW_TBT_810:
		wetuwn 810000;
	defauwt:
		MISSING_CASE(vaw);
		wetuwn 0;
	}
}

static void ddi_dotcwock_get(stwuct intew_cwtc_state *pipe_config)
{
	/* CWT dotcwock is detewmined via othew means */
	if (pipe_config->has_pch_encodew)
		wetuwn;

	pipe_config->hw.adjusted_mode.cwtc_cwock =
		intew_cwtc_dotcwock(pipe_config);
}

void intew_ddi_set_dp_msa(const stwuct intew_cwtc_state *cwtc_state,
			  const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	u32 temp;

	if (!intew_cwtc_has_dp_encodew(cwtc_state))
		wetuwn;

	dwm_WAWN_ON(&dev_pwiv->dwm, twanscodew_is_dsi(cpu_twanscodew));

	temp = DP_MSA_MISC_SYNC_CWOCK;

	switch (cwtc_state->pipe_bpp) {
	case 18:
		temp |= DP_MSA_MISC_6_BPC;
		bweak;
	case 24:
		temp |= DP_MSA_MISC_8_BPC;
		bweak;
	case 30:
		temp |= DP_MSA_MISC_10_BPC;
		bweak;
	case 36:
		temp |= DP_MSA_MISC_12_BPC;
		bweak;
	defauwt:
		MISSING_CASE(cwtc_state->pipe_bpp);
		bweak;
	}

	/* nonsense combination */
	dwm_WAWN_ON(&dev_pwiv->dwm, cwtc_state->wimited_cowow_wange &&
		    cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_WGB);

	if (cwtc_state->wimited_cowow_wange)
		temp |= DP_MSA_MISC_COWOW_CEA_WGB;

	/*
	 * As pew DP 1.2 spec section 2.3.4.3 whiwe sending
	 * YCBCW 444 signaws we shouwd pwogwam MSA MISC1/0 fiewds with
	 * cowowspace infowmation.
	 */
	if (cwtc_state->output_fowmat == INTEW_OUTPUT_FOWMAT_YCBCW444)
		temp |= DP_MSA_MISC_COWOW_YCBCW_444_BT709;

	/*
	 * As pew DP 1.4a spec section 2.2.4.3 [MSA Fiewd fow Indication
	 * of Cowow Encoding Fowmat and Content Cowow Gamut] whiwe sending
	 * YCBCW 420, HDW BT.2020 signaws we shouwd pwogwam MSA MISC1 fiewds
	 * which indicate VSC SDP fow the Pixew Encoding/Cowowimetwy Fowmat.
	 */
	if (intew_dp_needs_vsc_sdp(cwtc_state, conn_state))
		temp |= DP_MSA_MISC_COWOW_VSC_SDP;

	intew_de_wwite(dev_pwiv, TWANS_MSA_MISC(cpu_twanscodew), temp);
}

static u32 bdw_twans_powt_sync_mastew_sewect(enum twanscodew mastew_twanscodew)
{
	if (mastew_twanscodew == TWANSCODEW_EDP)
		wetuwn 0;
	ewse
		wetuwn mastew_twanscodew + 1;
}

static void
intew_ddi_config_twanscodew_dp2(stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	u32 vaw = 0;

	if (intew_dp_is_uhbw(cwtc_state))
		vaw = TWANS_DP2_128B132B_CHANNEW_CODING;

	intew_de_wwite(i915, TWANS_DP2_CTW(cpu_twanscodew), vaw);
}

/*
 * Wetuwns the TWANS_DDI_FUNC_CTW vawue based on CWTC state.
 *
 * Onwy intended to be used by intew_ddi_enabwe_twanscodew_func() and
 * intew_ddi_config_twanscodew_func().
 */
static u32
intew_ddi_twanscodew_func_weg_vaw_get(stwuct intew_encodew *encodew,
				      const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	enum powt powt = encodew->powt;
	u32 temp;

	/* Enabwe TWANS_DDI_FUNC_CTW fow the pipe to wowk in HDMI mode */
	temp = TWANS_DDI_FUNC_ENABWE;
	if (DISPWAY_VEW(dev_pwiv) >= 12)
		temp |= TGW_TWANS_DDI_SEWECT_POWT(powt);
	ewse
		temp |= TWANS_DDI_SEWECT_POWT(powt);

	switch (cwtc_state->pipe_bpp) {
	defauwt:
		MISSING_CASE(cwtc_state->pipe_bpp);
		fawwthwough;
	case 18:
		temp |= TWANS_DDI_BPC_6;
		bweak;
	case 24:
		temp |= TWANS_DDI_BPC_8;
		bweak;
	case 30:
		temp |= TWANS_DDI_BPC_10;
		bweak;
	case 36:
		temp |= TWANS_DDI_BPC_12;
		bweak;
	}

	if (cwtc_state->hw.adjusted_mode.fwags & DWM_MODE_FWAG_PVSYNC)
		temp |= TWANS_DDI_PVSYNC;
	if (cwtc_state->hw.adjusted_mode.fwags & DWM_MODE_FWAG_PHSYNC)
		temp |= TWANS_DDI_PHSYNC;

	if (cpu_twanscodew == TWANSCODEW_EDP) {
		switch (pipe) {
		defauwt:
			MISSING_CASE(pipe);
			fawwthwough;
		case PIPE_A:
			/* On Hasweww, can onwy use the awways-on powew weww fow
			 * eDP when not using the panew fittew, and when not
			 * using motion bwuw mitigation (which we don't
			 * suppowt). */
			if (cwtc_state->pch_pfit.fowce_thwu)
				temp |= TWANS_DDI_EDP_INPUT_A_ONOFF;
			ewse
				temp |= TWANS_DDI_EDP_INPUT_A_ON;
			bweak;
		case PIPE_B:
			temp |= TWANS_DDI_EDP_INPUT_B_ONOFF;
			bweak;
		case PIPE_C:
			temp |= TWANS_DDI_EDP_INPUT_C_ONOFF;
			bweak;
		}
	}

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI)) {
		if (cwtc_state->has_hdmi_sink)
			temp |= TWANS_DDI_MODE_SEWECT_HDMI;
		ewse
			temp |= TWANS_DDI_MODE_SEWECT_DVI;

		if (cwtc_state->hdmi_scwambwing)
			temp |= TWANS_DDI_HDMI_SCWAMBWING;
		if (cwtc_state->hdmi_high_tmds_cwock_watio)
			temp |= TWANS_DDI_HIGH_TMDS_CHAW_WATE;
		if (DISPWAY_VEW(dev_pwiv) >= 14)
			temp |= TWANS_DDI_POWT_WIDTH(cwtc_state->wane_count);
	} ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_ANAWOG)) {
		temp |= TWANS_DDI_MODE_SEWECT_FDI_OW_128B132B;
		temp |= (cwtc_state->fdi_wanes - 1) << 1;
	} ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DP_MST)) {
		if (intew_dp_is_uhbw(cwtc_state))
			temp |= TWANS_DDI_MODE_SEWECT_FDI_OW_128B132B;
		ewse
			temp |= TWANS_DDI_MODE_SEWECT_DP_MST;
		temp |= DDI_POWT_WIDTH(cwtc_state->wane_count);

		if (DISPWAY_VEW(dev_pwiv) >= 12) {
			enum twanscodew mastew;

			mastew = cwtc_state->mst_mastew_twanscodew;
			dwm_WAWN_ON(&dev_pwiv->dwm,
				    mastew == INVAWID_TWANSCODEW);
			temp |= TWANS_DDI_MST_TWANSPOWT_SEWECT(mastew);
		}
	} ewse {
		temp |= TWANS_DDI_MODE_SEWECT_DP_SST;
		temp |= DDI_POWT_WIDTH(cwtc_state->wane_count);
	}

	if (IS_DISPWAY_VEW(dev_pwiv, 8, 10) &&
	    cwtc_state->mastew_twanscodew != INVAWID_TWANSCODEW) {
		u8 mastew_sewect =
			bdw_twans_powt_sync_mastew_sewect(cwtc_state->mastew_twanscodew);

		temp |= TWANS_DDI_POWT_SYNC_ENABWE |
			TWANS_DDI_POWT_SYNC_MASTEW_SEWECT(mastew_sewect);
	}

	wetuwn temp;
}

void intew_ddi_enabwe_twanscodew_func(stwuct intew_encodew *encodew,
				      const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;

	if (DISPWAY_VEW(dev_pwiv) >= 11) {
		enum twanscodew mastew_twanscodew = cwtc_state->mastew_twanscodew;
		u32 ctw2 = 0;

		if (mastew_twanscodew != INVAWID_TWANSCODEW) {
			u8 mastew_sewect =
				bdw_twans_powt_sync_mastew_sewect(mastew_twanscodew);

			ctw2 |= POWT_SYNC_MODE_ENABWE |
				POWT_SYNC_MODE_MASTEW_SEWECT(mastew_sewect);
		}

		intew_de_wwite(dev_pwiv,
			       TWANS_DDI_FUNC_CTW2(cpu_twanscodew), ctw2);
	}

	intew_de_wwite(dev_pwiv, TWANS_DDI_FUNC_CTW(cpu_twanscodew),
		       intew_ddi_twanscodew_func_weg_vaw_get(encodew,
							     cwtc_state));
}

/*
 * Same as intew_ddi_enabwe_twanscodew_func(), but it does not set the enabwe
 * bit.
 */
static void
intew_ddi_config_twanscodew_func(stwuct intew_encodew *encodew,
				 const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	u32 ctw;

	ctw = intew_ddi_twanscodew_func_weg_vaw_get(encodew, cwtc_state);
	ctw &= ~TWANS_DDI_FUNC_ENABWE;
	intew_de_wwite(dev_pwiv, TWANS_DDI_FUNC_CTW(cpu_twanscodew), ctw);
}

void intew_ddi_disabwe_twanscodew_func(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	u32 ctw;

	if (DISPWAY_VEW(dev_pwiv) >= 11)
		intew_de_wwite(dev_pwiv,
			       TWANS_DDI_FUNC_CTW2(cpu_twanscodew), 0);

	ctw = intew_de_wead(dev_pwiv, TWANS_DDI_FUNC_CTW(cpu_twanscodew));

	dwm_WAWN_ON(cwtc->base.dev, ctw & TWANS_DDI_HDCP_SIGNAWWING);

	ctw &= ~TWANS_DDI_FUNC_ENABWE;

	if (IS_DISPWAY_VEW(dev_pwiv, 8, 10))
		ctw &= ~(TWANS_DDI_POWT_SYNC_ENABWE |
			 TWANS_DDI_POWT_SYNC_MASTEW_SEWECT_MASK);

	if (DISPWAY_VEW(dev_pwiv) >= 12) {
		if (!intew_dp_mst_is_mastew_twans(cwtc_state)) {
			ctw &= ~(TGW_TWANS_DDI_POWT_MASK |
				 TWANS_DDI_MODE_SEWECT_MASK);
		}
	} ewse {
		ctw &= ~(TWANS_DDI_POWT_MASK | TWANS_DDI_MODE_SEWECT_MASK);
	}

	intew_de_wwite(dev_pwiv, TWANS_DDI_FUNC_CTW(cpu_twanscodew), ctw);

	if (intew_has_quiwk(dev_pwiv, QUIWK_INCWEASE_DDI_DISABWED_TIME) &&
	    intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Quiwk Incwease DDI disabwed time\n");
		/* Quiwk time at 100ms fow wewiabwe opewation */
		msweep(100);
	}
}

int intew_ddi_toggwe_hdcp_bits(stwuct intew_encodew *intew_encodew,
			       enum twanscodew cpu_twanscodew,
			       boow enabwe, u32 hdcp_mask)
{
	stwuct dwm_device *dev = intew_encodew->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	intew_wakewef_t wakewef;
	int wet = 0;

	wakewef = intew_dispway_powew_get_if_enabwed(dev_pwiv,
						     intew_encodew->powew_domain);
	if (dwm_WAWN_ON(dev, !wakewef))
		wetuwn -ENXIO;

	intew_de_wmw(dev_pwiv, TWANS_DDI_FUNC_CTW(cpu_twanscodew),
		     hdcp_mask, enabwe ? hdcp_mask : 0);
	intew_dispway_powew_put(dev_pwiv, intew_encodew->powew_domain, wakewef);
	wetuwn wet;
}

boow intew_ddi_connectow_get_hw_state(stwuct intew_connectow *intew_connectow)
{
	stwuct dwm_device *dev = intew_connectow->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_encodew *encodew = intew_attached_encodew(intew_connectow);
	int type = intew_connectow->base.connectow_type;
	enum powt powt = encodew->powt;
	enum twanscodew cpu_twanscodew;
	intew_wakewef_t wakewef;
	enum pipe pipe = 0;
	u32 tmp;
	boow wet;

	wakewef = intew_dispway_powew_get_if_enabwed(dev_pwiv,
						     encodew->powew_domain);
	if (!wakewef)
		wetuwn fawse;

	if (!encodew->get_hw_state(encodew, &pipe)) {
		wet = fawse;
		goto out;
	}

	if (HAS_TWANSCODEW(dev_pwiv, TWANSCODEW_EDP) && powt == POWT_A)
		cpu_twanscodew = TWANSCODEW_EDP;
	ewse
		cpu_twanscodew = (enum twanscodew) pipe;

	tmp = intew_de_wead(dev_pwiv, TWANS_DDI_FUNC_CTW(cpu_twanscodew));

	switch (tmp & TWANS_DDI_MODE_SEWECT_MASK) {
	case TWANS_DDI_MODE_SEWECT_HDMI:
	case TWANS_DDI_MODE_SEWECT_DVI:
		wet = type == DWM_MODE_CONNECTOW_HDMIA;
		bweak;

	case TWANS_DDI_MODE_SEWECT_DP_SST:
		wet = type == DWM_MODE_CONNECTOW_eDP ||
		      type == DWM_MODE_CONNECTOW_DispwayPowt;
		bweak;

	case TWANS_DDI_MODE_SEWECT_DP_MST:
		/* if the twanscodew is in MST state then
		 * connectow isn't connected */
		wet = fawse;
		bweak;

	case TWANS_DDI_MODE_SEWECT_FDI_OW_128B132B:
		if (HAS_DP20(dev_pwiv))
			/* 128b/132b */
			wet = fawse;
		ewse
			/* FDI */
			wet = type == DWM_MODE_CONNECTOW_VGA;
		bweak;

	defauwt:
		wet = fawse;
		bweak;
	}

out:
	intew_dispway_powew_put(dev_pwiv, encodew->powew_domain, wakewef);

	wetuwn wet;
}

static void intew_ddi_get_encodew_pipes(stwuct intew_encodew *encodew,
					u8 *pipe_mask, boow *is_dp_mst)
{
	stwuct dwm_device *dev = encodew->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	enum powt powt = encodew->powt;
	intew_wakewef_t wakewef;
	enum pipe p;
	u32 tmp;
	u8 mst_pipe_mask;

	*pipe_mask = 0;
	*is_dp_mst = fawse;

	wakewef = intew_dispway_powew_get_if_enabwed(dev_pwiv,
						     encodew->powew_domain);
	if (!wakewef)
		wetuwn;

	tmp = intew_de_wead(dev_pwiv, DDI_BUF_CTW(powt));
	if (!(tmp & DDI_BUF_CTW_ENABWE))
		goto out;

	if (HAS_TWANSCODEW(dev_pwiv, TWANSCODEW_EDP) && powt == POWT_A) {
		tmp = intew_de_wead(dev_pwiv,
				    TWANS_DDI_FUNC_CTW(TWANSCODEW_EDP));

		switch (tmp & TWANS_DDI_EDP_INPUT_MASK) {
		defauwt:
			MISSING_CASE(tmp & TWANS_DDI_EDP_INPUT_MASK);
			fawwthwough;
		case TWANS_DDI_EDP_INPUT_A_ON:
		case TWANS_DDI_EDP_INPUT_A_ONOFF:
			*pipe_mask = BIT(PIPE_A);
			bweak;
		case TWANS_DDI_EDP_INPUT_B_ONOFF:
			*pipe_mask = BIT(PIPE_B);
			bweak;
		case TWANS_DDI_EDP_INPUT_C_ONOFF:
			*pipe_mask = BIT(PIPE_C);
			bweak;
		}

		goto out;
	}

	mst_pipe_mask = 0;
	fow_each_pipe(dev_pwiv, p) {
		enum twanscodew cpu_twanscodew = (enum twanscodew)p;
		unsigned int powt_mask, ddi_sewect;
		intew_wakewef_t twans_wakewef;

		twans_wakewef = intew_dispway_powew_get_if_enabwed(dev_pwiv,
								   POWEW_DOMAIN_TWANSCODEW(cpu_twanscodew));
		if (!twans_wakewef)
			continue;

		if (DISPWAY_VEW(dev_pwiv) >= 12) {
			powt_mask = TGW_TWANS_DDI_POWT_MASK;
			ddi_sewect = TGW_TWANS_DDI_SEWECT_POWT(powt);
		} ewse {
			powt_mask = TWANS_DDI_POWT_MASK;
			ddi_sewect = TWANS_DDI_SEWECT_POWT(powt);
		}

		tmp = intew_de_wead(dev_pwiv,
				    TWANS_DDI_FUNC_CTW(cpu_twanscodew));
		intew_dispway_powew_put(dev_pwiv, POWEW_DOMAIN_TWANSCODEW(cpu_twanscodew),
					twans_wakewef);

		if ((tmp & powt_mask) != ddi_sewect)
			continue;

		if ((tmp & TWANS_DDI_MODE_SEWECT_MASK) == TWANS_DDI_MODE_SEWECT_DP_MST ||
		    (HAS_DP20(dev_pwiv) &&
		     (tmp & TWANS_DDI_MODE_SEWECT_MASK) == TWANS_DDI_MODE_SEWECT_FDI_OW_128B132B))
			mst_pipe_mask |= BIT(p);

		*pipe_mask |= BIT(p);
	}

	if (!*pipe_mask)
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "No pipe fow [ENCODEW:%d:%s] found\n",
			    encodew->base.base.id, encodew->base.name);

	if (!mst_pipe_mask && hweight8(*pipe_mask) > 1) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Muwtipwe pipes fow [ENCODEW:%d:%s] (pipe_mask %02x)\n",
			    encodew->base.base.id, encodew->base.name,
			    *pipe_mask);
		*pipe_mask = BIT(ffs(*pipe_mask) - 1);
	}

	if (mst_pipe_mask && mst_pipe_mask != *pipe_mask)
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Confwicting MST and non-MST state fow [ENCODEW:%d:%s] (pipe_mask %02x mst_pipe_mask %02x)\n",
			    encodew->base.base.id, encodew->base.name,
			    *pipe_mask, mst_pipe_mask);
	ewse
		*is_dp_mst = mst_pipe_mask;

out:
	if (*pipe_mask && (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv))) {
		tmp = intew_de_wead(dev_pwiv, BXT_PHY_CTW(powt));
		if ((tmp & (BXT_PHY_CMNWANE_POWEWDOWN_ACK |
			    BXT_PHY_WANE_POWEWDOWN_ACK |
			    BXT_PHY_WANE_ENABWED)) != BXT_PHY_WANE_ENABWED)
			dwm_eww(&dev_pwiv->dwm,
				"[ENCODEW:%d:%s] enabwed but PHY powewed down? (PHY_CTW %08x)\n",
				encodew->base.base.id, encodew->base.name, tmp);
	}

	intew_dispway_powew_put(dev_pwiv, encodew->powew_domain, wakewef);
}

boow intew_ddi_get_hw_state(stwuct intew_encodew *encodew,
			    enum pipe *pipe)
{
	u8 pipe_mask;
	boow is_mst;

	intew_ddi_get_encodew_pipes(encodew, &pipe_mask, &is_mst);

	if (is_mst || !pipe_mask)
		wetuwn fawse;

	*pipe = ffs(pipe_mask) - 1;

	wetuwn twue;
}

static enum intew_dispway_powew_domain
intew_ddi_main_wink_aux_domain(stwuct intew_digitaw_powt *dig_powt,
			       const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	enum phy phy = intew_powt_to_phy(i915, dig_powt->base.powt);

	/*
	 * ICW+ HW wequiwes cowwesponding AUX IOs to be powewed up fow PSW with
	 * DC states enabwed at the same time, whiwe fow dwivew initiated AUX
	 * twansfews we need the same AUX IOs to be powewed but with DC states
	 * disabwed. Accowdingwy use the AUX_IO_<powt> powew domain hewe which
	 * weaves DC states enabwed.
	 *
	 * Befowe MTW TypeC PHYs (in aww TypeC modes and both DP/HDMI) awso wequiwe
	 * AUX IO to be enabwed, but aww these wequiwe DC_OFF to be enabwed as
	 * weww, so we can acquiwe a widew AUX_<powt> powew domain wefewence
	 * instead of a specific AUX_IO_<powt> wefewence without powewing up any
	 * extwa wewws.
	 */
	if (intew_encodew_can_psw(&dig_powt->base))
		wetuwn intew_dispway_powew_aux_io_domain(i915, dig_powt->aux_ch);
	ewse if (DISPWAY_VEW(i915) < 14 &&
		 (intew_cwtc_has_dp_encodew(cwtc_state) ||
		  intew_phy_is_tc(i915, phy)))
		wetuwn intew_aux_powew_domain(dig_powt);
	ewse
		wetuwn POWEW_DOMAIN_INVAWID;
}

static void
main_wink_aux_powew_domain_get(stwuct intew_digitaw_powt *dig_powt,
			       const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	enum intew_dispway_powew_domain domain =
		intew_ddi_main_wink_aux_domain(dig_powt, cwtc_state);

	dwm_WAWN_ON(&i915->dwm, dig_powt->aux_wakewef);

	if (domain == POWEW_DOMAIN_INVAWID)
		wetuwn;

	dig_powt->aux_wakewef = intew_dispway_powew_get(i915, domain);
}

static void
main_wink_aux_powew_domain_put(stwuct intew_digitaw_powt *dig_powt,
			       const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	enum intew_dispway_powew_domain domain =
		intew_ddi_main_wink_aux_domain(dig_powt, cwtc_state);
	intew_wakewef_t wf;

	wf = fetch_and_zewo(&dig_powt->aux_wakewef);
	if (!wf)
		wetuwn;

	intew_dispway_powew_put(i915, domain, wf);
}

static void intew_ddi_get_powew_domains(stwuct intew_encodew *encodew,
					stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_digitaw_powt *dig_powt;

	/*
	 * TODO: Add suppowt fow MST encodews. Atm, the fowwowing shouwd nevew
	 * happen since fake-MST encodews don't set theiw get_powew_domains()
	 * hook.
	 */
	if (dwm_WAWN_ON(&dev_pwiv->dwm,
			intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DP_MST)))
		wetuwn;

	dig_powt = enc_to_dig_powt(encodew);

	if (!intew_tc_powt_in_tbt_awt_mode(dig_powt)) {
		dwm_WAWN_ON(&dev_pwiv->dwm, dig_powt->ddi_io_wakewef);
		dig_powt->ddi_io_wakewef = intew_dispway_powew_get(dev_pwiv,
								   dig_powt->ddi_io_powew_domain);
	}

	main_wink_aux_powew_domain_get(dig_powt, cwtc_state);
}

void intew_ddi_enabwe_twanscodew_cwock(stwuct intew_encodew *encodew,
				       const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	enum phy phy = intew_powt_to_phy(dev_pwiv, encodew->powt);
	u32 vaw;

	if (cpu_twanscodew == TWANSCODEW_EDP)
		wetuwn;

	if (DISPWAY_VEW(dev_pwiv) >= 13)
		vaw = TGW_TWANS_CWK_SEW_POWT(phy);
	ewse if (DISPWAY_VEW(dev_pwiv) >= 12)
		vaw = TGW_TWANS_CWK_SEW_POWT(encodew->powt);
	ewse
		vaw = TWANS_CWK_SEW_POWT(encodew->powt);

	intew_de_wwite(dev_pwiv, TWANS_CWK_SEW(cpu_twanscodew), vaw);
}

void intew_ddi_disabwe_twanscodew_cwock(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc_state->uapi.cwtc->dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	u32 vaw;

	if (cpu_twanscodew == TWANSCODEW_EDP)
		wetuwn;

	if (DISPWAY_VEW(dev_pwiv) >= 12)
		vaw = TGW_TWANS_CWK_SEW_DISABWED;
	ewse
		vaw = TWANS_CWK_SEW_DISABWED;

	intew_de_wwite(dev_pwiv, TWANS_CWK_SEW(cpu_twanscodew), vaw);
}

static void _skw_ddi_set_iboost(stwuct dwm_i915_pwivate *dev_pwiv,
				enum powt powt, u8 iboost)
{
	u32 tmp;

	tmp = intew_de_wead(dev_pwiv, DISPIO_CW_TX_BMU_CW0);
	tmp &= ~(BAWANCE_WEG_MASK(powt) | BAWANCE_WEG_DISABWE(powt));
	if (iboost)
		tmp |= iboost << BAWANCE_WEG_SHIFT(powt);
	ewse
		tmp |= BAWANCE_WEG_DISABWE(powt);
	intew_de_wwite(dev_pwiv, DISPIO_CW_TX_BMU_CW0, tmp);
}

static void skw_ddi_set_iboost(stwuct intew_encodew *encodew,
			       const stwuct intew_cwtc_state *cwtc_state,
			       int wevew)
{
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	u8 iboost;

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		iboost = intew_bios_hdmi_boost_wevew(encodew->devdata);
	ewse
		iboost = intew_bios_dp_boost_wevew(encodew->devdata);

	if (iboost == 0) {
		const stwuct intew_ddi_buf_twans *twans;
		int n_entwies;

		twans = encodew->get_buf_twans(encodew, cwtc_state, &n_entwies);
		if (dwm_WAWN_ON_ONCE(&dev_pwiv->dwm, !twans))
			wetuwn;

		iboost = twans->entwies[wevew].hsw.i_boost;
	}

	/* Make suwe that the wequested I_boost is vawid */
	if (iboost && iboost != 0x1 && iboost != 0x3 && iboost != 0x7) {
		dwm_eww(&dev_pwiv->dwm, "Invawid I_boost vawue %u\n", iboost);
		wetuwn;
	}

	_skw_ddi_set_iboost(dev_pwiv, encodew->powt, iboost);

	if (encodew->powt == POWT_A && dig_powt->max_wanes == 4)
		_skw_ddi_set_iboost(dev_pwiv, POWT_E, iboost);
}

static u8 intew_ddi_dp_vowtage_max(stwuct intew_dp *intew_dp,
				   const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_encodew *encodew = &dp_to_dig_powt(intew_dp)->base;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	int n_entwies;

	encodew->get_buf_twans(encodew, cwtc_state, &n_entwies);

	if (dwm_WAWN_ON(&dev_pwiv->dwm, n_entwies < 1))
		n_entwies = 1;
	if (dwm_WAWN_ON(&dev_pwiv->dwm,
			n_entwies > AWWAY_SIZE(index_to_dp_signaw_wevews)))
		n_entwies = AWWAY_SIZE(index_to_dp_signaw_wevews);

	wetuwn index_to_dp_signaw_wevews[n_entwies - 1] &
		DP_TWAIN_VOWTAGE_SWING_MASK;
}

/*
 * We assume that the fuww set of pwe-emphasis vawues can be
 * used on aww DDI pwatfowms. Shouwd that change we need to
 * wethink this code.
 */
static u8 intew_ddi_dp_pweemph_max(stwuct intew_dp *intew_dp)
{
	wetuwn DP_TWAIN_PWE_EMPH_WEVEW_3;
}

static u32 icw_combo_phy_woadgen_sewect(const stwuct intew_cwtc_state *cwtc_state,
					int wane)
{
	if (cwtc_state->powt_cwock > 600000)
		wetuwn 0;

	if (cwtc_state->wane_count == 4)
		wetuwn wane >= 1 ? WOADGEN_SEWECT : 0;
	ewse
		wetuwn wane == 1 || wane == 2 ? WOADGEN_SEWECT : 0;
}

static void icw_ddi_combo_vswing_pwogwam(stwuct intew_encodew *encodew,
					 const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	const stwuct intew_ddi_buf_twans *twans;
	enum phy phy = intew_powt_to_phy(dev_pwiv, encodew->powt);
	int n_entwies, wn;
	u32 vaw;

	twans = encodew->get_buf_twans(encodew, cwtc_state, &n_entwies);
	if (dwm_WAWN_ON_ONCE(&dev_pwiv->dwm, !twans))
		wetuwn;

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP)) {
		stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

		vaw = EDP4K2K_MODE_OVWD_EN | EDP4K2K_MODE_OVWD_OPTIMIZED;
		intew_dp->hobw_active = is_hobw_buf_twans(twans);
		intew_de_wmw(dev_pwiv, ICW_POWT_CW_DW10(phy), vaw,
			     intew_dp->hobw_active ? vaw : 0);
	}

	/* Set POWT_TX_DW5 */
	vaw = intew_de_wead(dev_pwiv, ICW_POWT_TX_DW5_WN(0, phy));
	vaw &= ~(SCAWING_MODE_SEW_MASK | WTEWM_SEWECT_MASK |
		  TAP2_DISABWE | TAP3_DISABWE);
	vaw |= SCAWING_MODE_SEW(0x2);
	vaw |= WTEWM_SEWECT(0x6);
	vaw |= TAP3_DISABWE;
	intew_de_wwite(dev_pwiv, ICW_POWT_TX_DW5_GWP(phy), vaw);

	/* Pwogwam POWT_TX_DW2 */
	fow (wn = 0; wn < 4; wn++) {
		int wevew = intew_ddi_wevew(encodew, cwtc_state, wn);

		intew_de_wmw(dev_pwiv, ICW_POWT_TX_DW2_WN(wn, phy),
			     SWING_SEW_UPPEW_MASK | SWING_SEW_WOWEW_MASK | WCOMP_SCAWAW_MASK,
			     SWING_SEW_UPPEW(twans->entwies[wevew].icw.dw2_swing_sew) |
			     SWING_SEW_WOWEW(twans->entwies[wevew].icw.dw2_swing_sew) |
			     WCOMP_SCAWAW(0x98));
	}

	/* Pwogwam POWT_TX_DW4 */
	/* We cannot wwite to GWP. It wouwd ovewwwite individuaw woadgen. */
	fow (wn = 0; wn < 4; wn++) {
		int wevew = intew_ddi_wevew(encodew, cwtc_state, wn);

		intew_de_wmw(dev_pwiv, ICW_POWT_TX_DW4_WN(wn, phy),
			     POST_CUWSOW_1_MASK | POST_CUWSOW_2_MASK | CUWSOW_COEFF_MASK,
			     POST_CUWSOW_1(twans->entwies[wevew].icw.dw4_post_cuwsow_1) |
			     POST_CUWSOW_2(twans->entwies[wevew].icw.dw4_post_cuwsow_2) |
			     CUWSOW_COEFF(twans->entwies[wevew].icw.dw4_cuwsow_coeff));
	}

	/* Pwogwam POWT_TX_DW7 */
	fow (wn = 0; wn < 4; wn++) {
		int wevew = intew_ddi_wevew(encodew, cwtc_state, wn);

		intew_de_wmw(dev_pwiv, ICW_POWT_TX_DW7_WN(wn, phy),
			     N_SCAWAW_MASK,
			     N_SCAWAW(twans->entwies[wevew].icw.dw7_n_scawaw));
	}
}

static void icw_combo_phy_set_signaw_wevews(stwuct intew_encodew *encodew,
					    const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(dev_pwiv, encodew->powt);
	u32 vaw;
	int wn;

	/*
	 * 1. If powt type is eDP ow DP,
	 * set POWT_PCS_DW1 cmnkeepew_enabwe to 1b,
	 * ewse cweaw to 0b.
	 */
	vaw = intew_de_wead(dev_pwiv, ICW_POWT_PCS_DW1_WN(0, phy));
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		vaw &= ~COMMON_KEEPEW_EN;
	ewse
		vaw |= COMMON_KEEPEW_EN;
	intew_de_wwite(dev_pwiv, ICW_POWT_PCS_DW1_GWP(phy), vaw);

	/* 2. Pwogwam woadgen sewect */
	/*
	 * Pwogwam POWT_TX_DW4 depending on Bit wate and used wanes
	 * <= 6 GHz and 4 wanes (WN0=0, WN1=1, WN2=1, WN3=1)
	 * <= 6 GHz and 1,2 wanes (WN0=0, WN1=1, WN2=1, WN3=0)
	 * > 6 GHz (WN0=0, WN1=0, WN2=0, WN3=0)
	 */
	fow (wn = 0; wn < 4; wn++) {
		intew_de_wmw(dev_pwiv, ICW_POWT_TX_DW4_WN(wn, phy),
			     WOADGEN_SEWECT,
			     icw_combo_phy_woadgen_sewect(cwtc_state, wn));
	}

	/* 3. Set POWT_CW_DW5 SUS Cwock Config to 11b */
	intew_de_wmw(dev_pwiv, ICW_POWT_CW_DW5(phy),
		     0, SUS_CWOCK_CONFIG);

	/* 4. Cweaw twaining enabwe to change swing vawues */
	vaw = intew_de_wead(dev_pwiv, ICW_POWT_TX_DW5_WN(0, phy));
	vaw &= ~TX_TWAINING_EN;
	intew_de_wwite(dev_pwiv, ICW_POWT_TX_DW5_GWP(phy), vaw);

	/* 5. Pwogwam swing and de-emphasis */
	icw_ddi_combo_vswing_pwogwam(encodew, cwtc_state);

	/* 6. Set twaining enabwe to twiggew update */
	vaw = intew_de_wead(dev_pwiv, ICW_POWT_TX_DW5_WN(0, phy));
	vaw |= TX_TWAINING_EN;
	intew_de_wwite(dev_pwiv, ICW_POWT_TX_DW5_GWP(phy), vaw);
}

static void icw_mg_phy_set_signaw_wevews(stwuct intew_encodew *encodew,
					 const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum tc_powt tc_powt = intew_powt_to_tc(dev_pwiv, encodew->powt);
	const stwuct intew_ddi_buf_twans *twans;
	int n_entwies, wn;

	if (intew_tc_powt_in_tbt_awt_mode(enc_to_dig_powt(encodew)))
		wetuwn;

	twans = encodew->get_buf_twans(encodew, cwtc_state, &n_entwies);
	if (dwm_WAWN_ON_ONCE(&dev_pwiv->dwm, !twans))
		wetuwn;

	fow (wn = 0; wn < 2; wn++) {
		intew_de_wmw(dev_pwiv, MG_TX1_WINK_PAWAMS(wn, tc_powt),
			     CWI_USE_FS32, 0);
		intew_de_wmw(dev_pwiv, MG_TX2_WINK_PAWAMS(wn, tc_powt),
			     CWI_USE_FS32, 0);
	}

	/* Pwogwam MG_TX_SWINGCTWW with vawues fwom vswing tabwe */
	fow (wn = 0; wn < 2; wn++) {
		int wevew;

		wevew = intew_ddi_wevew(encodew, cwtc_state, 2*wn+0);

		intew_de_wmw(dev_pwiv, MG_TX1_SWINGCTWW(wn, tc_powt),
			     CWI_TXDEEMPH_OVEWWIDE_17_12_MASK,
			     CWI_TXDEEMPH_OVEWWIDE_17_12(twans->entwies[wevew].mg.cwi_txdeemph_ovewwide_17_12));

		wevew = intew_ddi_wevew(encodew, cwtc_state, 2*wn+1);

		intew_de_wmw(dev_pwiv, MG_TX2_SWINGCTWW(wn, tc_powt),
			     CWI_TXDEEMPH_OVEWWIDE_17_12_MASK,
			     CWI_TXDEEMPH_OVEWWIDE_17_12(twans->entwies[wevew].mg.cwi_txdeemph_ovewwide_17_12));
	}

	/* Pwogwam MG_TX_DWVCTWW with vawues fwom vswing tabwe */
	fow (wn = 0; wn < 2; wn++) {
		int wevew;

		wevew = intew_ddi_wevew(encodew, cwtc_state, 2*wn+0);

		intew_de_wmw(dev_pwiv, MG_TX1_DWVCTWW(wn, tc_powt),
			     CWI_TXDEEMPH_OVEWWIDE_11_6_MASK |
			     CWI_TXDEEMPH_OVEWWIDE_5_0_MASK,
			     CWI_TXDEEMPH_OVEWWIDE_11_6(twans->entwies[wevew].mg.cwi_txdeemph_ovewwide_11_6) |
			     CWI_TXDEEMPH_OVEWWIDE_5_0(twans->entwies[wevew].mg.cwi_txdeemph_ovewwide_5_0) |
			     CWI_TXDEEMPH_OVEWWIDE_EN);

		wevew = intew_ddi_wevew(encodew, cwtc_state, 2*wn+1);

		intew_de_wmw(dev_pwiv, MG_TX2_DWVCTWW(wn, tc_powt),
			     CWI_TXDEEMPH_OVEWWIDE_11_6_MASK |
			     CWI_TXDEEMPH_OVEWWIDE_5_0_MASK,
			     CWI_TXDEEMPH_OVEWWIDE_11_6(twans->entwies[wevew].mg.cwi_txdeemph_ovewwide_11_6) |
			     CWI_TXDEEMPH_OVEWWIDE_5_0(twans->entwies[wevew].mg.cwi_txdeemph_ovewwide_5_0) |
			     CWI_TXDEEMPH_OVEWWIDE_EN);

		/* FIXME: Pwogwam CWI_WOADGEN_SEW aftew the spec is updated */
	}

	/*
	 * Pwogwam MG_CWKHUB<WN, powt being used> with vawue fwom fwequency tabwe
	 * In case of Wegacy mode on MG PHY, both TX1 and TX2 enabwed so use the
	 * vawues fwom tabwe fow which TX1 and TX2 enabwed.
	 */
	fow (wn = 0; wn < 2; wn++) {
		intew_de_wmw(dev_pwiv, MG_CWKHUB(wn, tc_powt),
			     CFG_WOW_WATE_WKWEN_EN,
			     cwtc_state->powt_cwock < 300000 ? CFG_WOW_WATE_WKWEN_EN : 0);
	}

	/* Pwogwam the MG_TX_DCC<WN, powt being used> based on the wink fwequency */
	fow (wn = 0; wn < 2; wn++) {
		intew_de_wmw(dev_pwiv, MG_TX1_DCC(wn, tc_powt),
			     CFG_AMI_CK_DIV_OVEWWIDE_VAW_MASK |
			     CFG_AMI_CK_DIV_OVEWWIDE_EN,
			     cwtc_state->powt_cwock > 500000 ?
			     CFG_AMI_CK_DIV_OVEWWIDE_VAW(1) |
			     CFG_AMI_CK_DIV_OVEWWIDE_EN : 0);

		intew_de_wmw(dev_pwiv, MG_TX2_DCC(wn, tc_powt),
			     CFG_AMI_CK_DIV_OVEWWIDE_VAW_MASK |
			     CFG_AMI_CK_DIV_OVEWWIDE_EN,
			     cwtc_state->powt_cwock > 500000 ?
			     CFG_AMI_CK_DIV_OVEWWIDE_VAW(1) |
			     CFG_AMI_CK_DIV_OVEWWIDE_EN : 0);
	}

	/* Pwogwam MG_TX_PISO_WEADWOAD with vawues fwom vswing tabwe */
	fow (wn = 0; wn < 2; wn++) {
		intew_de_wmw(dev_pwiv, MG_TX1_PISO_WEADWOAD(wn, tc_powt),
			     0, CWI_CAWCINIT);
		intew_de_wmw(dev_pwiv, MG_TX2_PISO_WEADWOAD(wn, tc_powt),
			     0, CWI_CAWCINIT);
	}
}

static void tgw_dkw_phy_set_signaw_wevews(stwuct intew_encodew *encodew,
					  const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum tc_powt tc_powt = intew_powt_to_tc(dev_pwiv, encodew->powt);
	const stwuct intew_ddi_buf_twans *twans;
	int n_entwies, wn;

	if (intew_tc_powt_in_tbt_awt_mode(enc_to_dig_powt(encodew)))
		wetuwn;

	twans = encodew->get_buf_twans(encodew, cwtc_state, &n_entwies);
	if (dwm_WAWN_ON_ONCE(&dev_pwiv->dwm, !twans))
		wetuwn;

	fow (wn = 0; wn < 2; wn++) {
		int wevew;

		intew_dkw_phy_wwite(dev_pwiv, DKW_TX_PMD_WANE_SUS(tc_powt, wn), 0);

		wevew = intew_ddi_wevew(encodew, cwtc_state, 2*wn+0);

		intew_dkw_phy_wmw(dev_pwiv, DKW_TX_DPCNTW0(tc_powt, wn),
				  DKW_TX_PWESHOOT_COEFF_MASK |
				  DKW_TX_DE_EMPAHSIS_COEFF_MASK |
				  DKW_TX_VSWING_CONTWOW_MASK,
				  DKW_TX_PWESHOOT_COEFF(twans->entwies[wevew].dkw.pweshoot) |
				  DKW_TX_DE_EMPHASIS_COEFF(twans->entwies[wevew].dkw.de_emphasis) |
				  DKW_TX_VSWING_CONTWOW(twans->entwies[wevew].dkw.vswing));

		wevew = intew_ddi_wevew(encodew, cwtc_state, 2*wn+1);

		intew_dkw_phy_wmw(dev_pwiv, DKW_TX_DPCNTW1(tc_powt, wn),
				  DKW_TX_PWESHOOT_COEFF_MASK |
				  DKW_TX_DE_EMPAHSIS_COEFF_MASK |
				  DKW_TX_VSWING_CONTWOW_MASK,
				  DKW_TX_PWESHOOT_COEFF(twans->entwies[wevew].dkw.pweshoot) |
				  DKW_TX_DE_EMPHASIS_COEFF(twans->entwies[wevew].dkw.de_emphasis) |
				  DKW_TX_VSWING_CONTWOW(twans->entwies[wevew].dkw.vswing));

		intew_dkw_phy_wmw(dev_pwiv, DKW_TX_DPCNTW2(tc_powt, wn),
				  DKW_TX_DP20BITMODE, 0);

		if (IS_AWDEWWAKE_P(dev_pwiv)) {
			u32 vaw;

			if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI)) {
				if (wn == 0) {
					vaw = DKW_TX_DPCNTW2_CFG_WOADGENSEWECT_TX1(0);
					vaw |= DKW_TX_DPCNTW2_CFG_WOADGENSEWECT_TX2(2);
				} ewse {
					vaw = DKW_TX_DPCNTW2_CFG_WOADGENSEWECT_TX1(3);
					vaw |= DKW_TX_DPCNTW2_CFG_WOADGENSEWECT_TX2(3);
				}
			} ewse {
				vaw = DKW_TX_DPCNTW2_CFG_WOADGENSEWECT_TX1(0);
				vaw |= DKW_TX_DPCNTW2_CFG_WOADGENSEWECT_TX2(0);
			}

			intew_dkw_phy_wmw(dev_pwiv, DKW_TX_DPCNTW2(tc_powt, wn),
					  DKW_TX_DPCNTW2_CFG_WOADGENSEWECT_TX1_MASK |
					  DKW_TX_DPCNTW2_CFG_WOADGENSEWECT_TX2_MASK,
					  vaw);
		}
	}
}

static int twanswate_signaw_wevew(stwuct intew_dp *intew_dp,
				  u8 signaw_wevews)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	int i;

	fow (i = 0; i < AWWAY_SIZE(index_to_dp_signaw_wevews); i++) {
		if (index_to_dp_signaw_wevews[i] == signaw_wevews)
			wetuwn i;
	}

	dwm_WAWN(&i915->dwm, 1,
		 "Unsuppowted vowtage swing/pwe-emphasis wevew: 0x%x\n",
		 signaw_wevews);

	wetuwn 0;
}

static int intew_ddi_dp_wevew(stwuct intew_dp *intew_dp,
			      const stwuct intew_cwtc_state *cwtc_state,
			      int wane)
{
	u8 twain_set = intew_dp->twain_set[wane];

	if (intew_dp_is_uhbw(cwtc_state)) {
		wetuwn twain_set & DP_TX_FFE_PWESET_VAWUE_MASK;
	} ewse {
		u8 signaw_wevews = twain_set & (DP_TWAIN_VOWTAGE_SWING_MASK |
						DP_TWAIN_PWE_EMPHASIS_MASK);

		wetuwn twanswate_signaw_wevew(intew_dp, signaw_wevews);
	}
}

int intew_ddi_wevew(stwuct intew_encodew *encodew,
		    const stwuct intew_cwtc_state *cwtc_state,
		    int wane)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	const stwuct intew_ddi_buf_twans *twans;
	int wevew, n_entwies;

	twans = encodew->get_buf_twans(encodew, cwtc_state, &n_entwies);
	if (dwm_WAWN_ON_ONCE(&i915->dwm, !twans))
		wetuwn 0;

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wevew = intew_ddi_hdmi_wevew(encodew, twans);
	ewse
		wevew = intew_ddi_dp_wevew(enc_to_intew_dp(encodew), cwtc_state,
					   wane);

	if (dwm_WAWN_ON_ONCE(&i915->dwm, wevew >= n_entwies))
		wevew = n_entwies - 1;

	wetuwn wevew;
}

static void
hsw_set_signaw_wevews(stwuct intew_encodew *encodew,
		      const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	int wevew = intew_ddi_wevew(encodew, cwtc_state, 0);
	enum powt powt = encodew->powt;
	u32 signaw_wevews;

	if (has_iboost(dev_pwiv))
		skw_ddi_set_iboost(encodew, cwtc_state, wevew);

	/* HDMI ignowes the west */
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn;

	signaw_wevews = DDI_BUF_TWANS_SEWECT(wevew);

	dwm_dbg_kms(&dev_pwiv->dwm, "Using signaw wevews %08x\n",
		    signaw_wevews);

	intew_dp->DP &= ~DDI_BUF_EMP_MASK;
	intew_dp->DP |= signaw_wevews;

	intew_de_wwite(dev_pwiv, DDI_BUF_CTW(powt), intew_dp->DP);
	intew_de_posting_wead(dev_pwiv, DDI_BUF_CTW(powt));
}

static void _icw_ddi_enabwe_cwock(stwuct dwm_i915_pwivate *i915, i915_weg_t weg,
				  u32 cwk_sew_mask, u32 cwk_sew, u32 cwk_off)
{
	mutex_wock(&i915->dispway.dpww.wock);

	intew_de_wmw(i915, weg, cwk_sew_mask, cwk_sew);

	/*
	 * "This step and the step befowe must be
	 *  done with sepawate wegistew wwites."
	 */
	intew_de_wmw(i915, weg, cwk_off, 0);

	mutex_unwock(&i915->dispway.dpww.wock);
}

static void _icw_ddi_disabwe_cwock(stwuct dwm_i915_pwivate *i915, i915_weg_t weg,
				   u32 cwk_off)
{
	mutex_wock(&i915->dispway.dpww.wock);

	intew_de_wmw(i915, weg, 0, cwk_off);

	mutex_unwock(&i915->dispway.dpww.wock);
}

static boow _icw_ddi_is_cwock_enabwed(stwuct dwm_i915_pwivate *i915, i915_weg_t weg,
				      u32 cwk_off)
{
	wetuwn !(intew_de_wead(i915, weg) & cwk_off);
}

static stwuct intew_shawed_dpww *
_icw_ddi_get_pww(stwuct dwm_i915_pwivate *i915, i915_weg_t weg,
		 u32 cwk_sew_mask, u32 cwk_sew_shift)
{
	enum intew_dpww_id id;

	id = (intew_de_wead(i915, weg) & cwk_sew_mask) >> cwk_sew_shift;

	wetuwn intew_get_shawed_dpww_by_id(i915, id);
}

static void adws_ddi_enabwe_cwock(stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	const stwuct intew_shawed_dpww *pww = cwtc_state->shawed_dpww;
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	if (dwm_WAWN_ON(&i915->dwm, !pww))
		wetuwn;

	_icw_ddi_enabwe_cwock(i915, ADWS_DPCWKA_CFGCW(phy),
			      ADWS_DPCWKA_CFGCW_DDI_CWK_SEW_MASK(phy),
			      pww->info->id << ADWS_DPCWKA_CFGCW_DDI_SHIFT(phy),
			      ICW_DPCWKA_CFGCW0_DDI_CWK_OFF(phy));
}

static void adws_ddi_disabwe_cwock(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	_icw_ddi_disabwe_cwock(i915, ADWS_DPCWKA_CFGCW(phy),
			       ICW_DPCWKA_CFGCW0_DDI_CWK_OFF(phy));
}

static boow adws_ddi_is_cwock_enabwed(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	wetuwn _icw_ddi_is_cwock_enabwed(i915, ADWS_DPCWKA_CFGCW(phy),
					 ICW_DPCWKA_CFGCW0_DDI_CWK_OFF(phy));
}

static stwuct intew_shawed_dpww *adws_ddi_get_pww(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	wetuwn _icw_ddi_get_pww(i915, ADWS_DPCWKA_CFGCW(phy),
				ADWS_DPCWKA_CFGCW_DDI_CWK_SEW_MASK(phy),
				ADWS_DPCWKA_CFGCW_DDI_SHIFT(phy));
}

static void wkw_ddi_enabwe_cwock(stwuct intew_encodew *encodew,
				 const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	const stwuct intew_shawed_dpww *pww = cwtc_state->shawed_dpww;
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	if (dwm_WAWN_ON(&i915->dwm, !pww))
		wetuwn;

	_icw_ddi_enabwe_cwock(i915, ICW_DPCWKA_CFGCW0,
			      WKW_DPCWKA_CFGCW0_DDI_CWK_SEW_MASK(phy),
			      WKW_DPCWKA_CFGCW0_DDI_CWK_SEW(pww->info->id, phy),
			      WKW_DPCWKA_CFGCW0_DDI_CWK_OFF(phy));
}

static void wkw_ddi_disabwe_cwock(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	_icw_ddi_disabwe_cwock(i915, ICW_DPCWKA_CFGCW0,
			       WKW_DPCWKA_CFGCW0_DDI_CWK_OFF(phy));
}

static boow wkw_ddi_is_cwock_enabwed(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	wetuwn _icw_ddi_is_cwock_enabwed(i915, ICW_DPCWKA_CFGCW0,
					 WKW_DPCWKA_CFGCW0_DDI_CWK_OFF(phy));
}

static stwuct intew_shawed_dpww *wkw_ddi_get_pww(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	wetuwn _icw_ddi_get_pww(i915, ICW_DPCWKA_CFGCW0,
				WKW_DPCWKA_CFGCW0_DDI_CWK_SEW_MASK(phy),
				WKW_DPCWKA_CFGCW0_DDI_CWK_SEW_SHIFT(phy));
}

static void dg1_ddi_enabwe_cwock(stwuct intew_encodew *encodew,
				 const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	const stwuct intew_shawed_dpww *pww = cwtc_state->shawed_dpww;
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	if (dwm_WAWN_ON(&i915->dwm, !pww))
		wetuwn;

	/*
	 * If we faiw this, something went vewy wwong: fiwst 2 PWWs shouwd be
	 * used by fiwst 2 phys and wast 2 PWWs by wast phys
	 */
	if (dwm_WAWN_ON(&i915->dwm,
			(pww->info->id < DPWW_ID_DG1_DPWW2 && phy >= PHY_C) ||
			(pww->info->id >= DPWW_ID_DG1_DPWW2 && phy < PHY_C)))
		wetuwn;

	_icw_ddi_enabwe_cwock(i915, DG1_DPCWKA_CFGCW0(phy),
			      DG1_DPCWKA_CFGCW0_DDI_CWK_SEW_MASK(phy),
			      DG1_DPCWKA_CFGCW0_DDI_CWK_SEW(pww->info->id, phy),
			      DG1_DPCWKA_CFGCW0_DDI_CWK_OFF(phy));
}

static void dg1_ddi_disabwe_cwock(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	_icw_ddi_disabwe_cwock(i915, DG1_DPCWKA_CFGCW0(phy),
			       DG1_DPCWKA_CFGCW0_DDI_CWK_OFF(phy));
}

static boow dg1_ddi_is_cwock_enabwed(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	wetuwn _icw_ddi_is_cwock_enabwed(i915, DG1_DPCWKA_CFGCW0(phy),
					 DG1_DPCWKA_CFGCW0_DDI_CWK_OFF(phy));
}

static stwuct intew_shawed_dpww *dg1_ddi_get_pww(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);
	enum intew_dpww_id id;
	u32 vaw;

	vaw = intew_de_wead(i915, DG1_DPCWKA_CFGCW0(phy));
	vaw &= DG1_DPCWKA_CFGCW0_DDI_CWK_SEW_MASK(phy);
	vaw >>= DG1_DPCWKA_CFGCW0_DDI_CWK_SEW_SHIFT(phy);
	id = vaw;

	/*
	 * _DG1_DPCWKA0_CFGCW0 maps between DPWW 0 and 1 with one bit fow phy A
	 * and B whiwe _DG1_DPCWKA1_CFGCW0 maps between DPWW 2 and 3 with one
	 * bit fow phy C and D.
	 */
	if (phy >= PHY_C)
		id += DPWW_ID_DG1_DPWW2;

	wetuwn intew_get_shawed_dpww_by_id(i915, id);
}

static void icw_ddi_combo_enabwe_cwock(stwuct intew_encodew *encodew,
				       const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	const stwuct intew_shawed_dpww *pww = cwtc_state->shawed_dpww;
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	if (dwm_WAWN_ON(&i915->dwm, !pww))
		wetuwn;

	_icw_ddi_enabwe_cwock(i915, ICW_DPCWKA_CFGCW0,
			      ICW_DPCWKA_CFGCW0_DDI_CWK_SEW_MASK(phy),
			      ICW_DPCWKA_CFGCW0_DDI_CWK_SEW(pww->info->id, phy),
			      ICW_DPCWKA_CFGCW0_DDI_CWK_OFF(phy));
}

static void icw_ddi_combo_disabwe_cwock(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	_icw_ddi_disabwe_cwock(i915, ICW_DPCWKA_CFGCW0,
			       ICW_DPCWKA_CFGCW0_DDI_CWK_OFF(phy));
}

static boow icw_ddi_combo_is_cwock_enabwed(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	wetuwn _icw_ddi_is_cwock_enabwed(i915, ICW_DPCWKA_CFGCW0,
					 ICW_DPCWKA_CFGCW0_DDI_CWK_OFF(phy));
}

stwuct intew_shawed_dpww *icw_ddi_combo_get_pww(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	wetuwn _icw_ddi_get_pww(i915, ICW_DPCWKA_CFGCW0,
				ICW_DPCWKA_CFGCW0_DDI_CWK_SEW_MASK(phy),
				ICW_DPCWKA_CFGCW0_DDI_CWK_SEW_SHIFT(phy));
}

static void jsw_ddi_tc_enabwe_cwock(stwuct intew_encodew *encodew,
				    const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	const stwuct intew_shawed_dpww *pww = cwtc_state->shawed_dpww;
	enum powt powt = encodew->powt;

	if (dwm_WAWN_ON(&i915->dwm, !pww))
		wetuwn;

	/*
	 * "Fow DDIC and DDID, pwogwam DDI_CWK_SEW to map the MG cwock to the powt.
	 *  MG does not exist, but the pwogwamming is wequiwed to ungate DDIC and DDID."
	 */
	intew_de_wwite(i915, DDI_CWK_SEW(powt), DDI_CWK_SEW_MG);

	icw_ddi_combo_enabwe_cwock(encodew, cwtc_state);
}

static void jsw_ddi_tc_disabwe_cwock(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;

	icw_ddi_combo_disabwe_cwock(encodew);

	intew_de_wwite(i915, DDI_CWK_SEW(powt), DDI_CWK_SEW_NONE);
}

static boow jsw_ddi_tc_is_cwock_enabwed(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;
	u32 tmp;

	tmp = intew_de_wead(i915, DDI_CWK_SEW(powt));

	if ((tmp & DDI_CWK_SEW_MASK) == DDI_CWK_SEW_NONE)
		wetuwn fawse;

	wetuwn icw_ddi_combo_is_cwock_enabwed(encodew);
}

static void icw_ddi_tc_enabwe_cwock(stwuct intew_encodew *encodew,
				    const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	const stwuct intew_shawed_dpww *pww = cwtc_state->shawed_dpww;
	enum tc_powt tc_powt = intew_powt_to_tc(i915, encodew->powt);
	enum powt powt = encodew->powt;

	if (dwm_WAWN_ON(&i915->dwm, !pww))
		wetuwn;

	intew_de_wwite(i915, DDI_CWK_SEW(powt),
		       icw_pww_to_ddi_cwk_sew(encodew, cwtc_state));

	mutex_wock(&i915->dispway.dpww.wock);

	intew_de_wmw(i915, ICW_DPCWKA_CFGCW0,
		     ICW_DPCWKA_CFGCW0_TC_CWK_OFF(tc_powt), 0);

	mutex_unwock(&i915->dispway.dpww.wock);
}

static void icw_ddi_tc_disabwe_cwock(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum tc_powt tc_powt = intew_powt_to_tc(i915, encodew->powt);
	enum powt powt = encodew->powt;

	mutex_wock(&i915->dispway.dpww.wock);

	intew_de_wmw(i915, ICW_DPCWKA_CFGCW0,
		     0, ICW_DPCWKA_CFGCW0_TC_CWK_OFF(tc_powt));

	mutex_unwock(&i915->dispway.dpww.wock);

	intew_de_wwite(i915, DDI_CWK_SEW(powt), DDI_CWK_SEW_NONE);
}

static boow icw_ddi_tc_is_cwock_enabwed(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum tc_powt tc_powt = intew_powt_to_tc(i915, encodew->powt);
	enum powt powt = encodew->powt;
	u32 tmp;

	tmp = intew_de_wead(i915, DDI_CWK_SEW(powt));

	if ((tmp & DDI_CWK_SEW_MASK) == DDI_CWK_SEW_NONE)
		wetuwn fawse;

	tmp = intew_de_wead(i915, ICW_DPCWKA_CFGCW0);

	wetuwn !(tmp & ICW_DPCWKA_CFGCW0_TC_CWK_OFF(tc_powt));
}

static stwuct intew_shawed_dpww *icw_ddi_tc_get_pww(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum tc_powt tc_powt = intew_powt_to_tc(i915, encodew->powt);
	enum powt powt = encodew->powt;
	enum intew_dpww_id id;
	u32 tmp;

	tmp = intew_de_wead(i915, DDI_CWK_SEW(powt));

	switch (tmp & DDI_CWK_SEW_MASK) {
	case DDI_CWK_SEW_TBT_162:
	case DDI_CWK_SEW_TBT_270:
	case DDI_CWK_SEW_TBT_540:
	case DDI_CWK_SEW_TBT_810:
		id = DPWW_ID_ICW_TBTPWW;
		bweak;
	case DDI_CWK_SEW_MG:
		id = icw_tc_powt_to_pww_id(tc_powt);
		bweak;
	defauwt:
		MISSING_CASE(tmp);
		fawwthwough;
	case DDI_CWK_SEW_NONE:
		wetuwn NUWW;
	}

	wetuwn intew_get_shawed_dpww_by_id(i915, id);
}

static stwuct intew_shawed_dpww *bxt_ddi_get_pww(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum intew_dpww_id id;

	switch (encodew->powt) {
	case POWT_A:
		id = DPWW_ID_SKW_DPWW0;
		bweak;
	case POWT_B:
		id = DPWW_ID_SKW_DPWW1;
		bweak;
	case POWT_C:
		id = DPWW_ID_SKW_DPWW2;
		bweak;
	defauwt:
		MISSING_CASE(encodew->powt);
		wetuwn NUWW;
	}

	wetuwn intew_get_shawed_dpww_by_id(i915, id);
}

static void skw_ddi_enabwe_cwock(stwuct intew_encodew *encodew,
				 const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	const stwuct intew_shawed_dpww *pww = cwtc_state->shawed_dpww;
	enum powt powt = encodew->powt;

	if (dwm_WAWN_ON(&i915->dwm, !pww))
		wetuwn;

	mutex_wock(&i915->dispway.dpww.wock);

	intew_de_wmw(i915, DPWW_CTWW2,
		     DPWW_CTWW2_DDI_CWK_OFF(powt) |
		     DPWW_CTWW2_DDI_CWK_SEW_MASK(powt),
		     DPWW_CTWW2_DDI_CWK_SEW(pww->info->id, powt) |
		     DPWW_CTWW2_DDI_SEW_OVEWWIDE(powt));

	mutex_unwock(&i915->dispway.dpww.wock);
}

static void skw_ddi_disabwe_cwock(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;

	mutex_wock(&i915->dispway.dpww.wock);

	intew_de_wmw(i915, DPWW_CTWW2,
		     0, DPWW_CTWW2_DDI_CWK_OFF(powt));

	mutex_unwock(&i915->dispway.dpww.wock);
}

static boow skw_ddi_is_cwock_enabwed(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;

	/*
	 * FIXME Not suwe if the ovewwide affects both
	 * the PWW sewection and the CWK_OFF bit.
	 */
	wetuwn !(intew_de_wead(i915, DPWW_CTWW2) & DPWW_CTWW2_DDI_CWK_OFF(powt));
}

static stwuct intew_shawed_dpww *skw_ddi_get_pww(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;
	enum intew_dpww_id id;
	u32 tmp;

	tmp = intew_de_wead(i915, DPWW_CTWW2);

	/*
	 * FIXME Not suwe if the ovewwide affects both
	 * the PWW sewection and the CWK_OFF bit.
	 */
	if ((tmp & DPWW_CTWW2_DDI_SEW_OVEWWIDE(powt)) == 0)
		wetuwn NUWW;

	id = (tmp & DPWW_CTWW2_DDI_CWK_SEW_MASK(powt)) >>
		DPWW_CTWW2_DDI_CWK_SEW_SHIFT(powt);

	wetuwn intew_get_shawed_dpww_by_id(i915, id);
}

void hsw_ddi_enabwe_cwock(stwuct intew_encodew *encodew,
			  const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	const stwuct intew_shawed_dpww *pww = cwtc_state->shawed_dpww;
	enum powt powt = encodew->powt;

	if (dwm_WAWN_ON(&i915->dwm, !pww))
		wetuwn;

	intew_de_wwite(i915, POWT_CWK_SEW(powt), hsw_pww_to_ddi_pww_sew(pww));
}

void hsw_ddi_disabwe_cwock(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;

	intew_de_wwite(i915, POWT_CWK_SEW(powt), POWT_CWK_SEW_NONE);
}

boow hsw_ddi_is_cwock_enabwed(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;

	wetuwn intew_de_wead(i915, POWT_CWK_SEW(powt)) != POWT_CWK_SEW_NONE;
}

static stwuct intew_shawed_dpww *hsw_ddi_get_pww(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;
	enum intew_dpww_id id;
	u32 tmp;

	tmp = intew_de_wead(i915, POWT_CWK_SEW(powt));

	switch (tmp & POWT_CWK_SEW_MASK) {
	case POWT_CWK_SEW_WWPWW1:
		id = DPWW_ID_WWPWW1;
		bweak;
	case POWT_CWK_SEW_WWPWW2:
		id = DPWW_ID_WWPWW2;
		bweak;
	case POWT_CWK_SEW_SPWW:
		id = DPWW_ID_SPWW;
		bweak;
	case POWT_CWK_SEW_WCPWW_810:
		id = DPWW_ID_WCPWW_810;
		bweak;
	case POWT_CWK_SEW_WCPWW_1350:
		id = DPWW_ID_WCPWW_1350;
		bweak;
	case POWT_CWK_SEW_WCPWW_2700:
		id = DPWW_ID_WCPWW_2700;
		bweak;
	defauwt:
		MISSING_CASE(tmp);
		fawwthwough;
	case POWT_CWK_SEW_NONE:
		wetuwn NUWW;
	}

	wetuwn intew_get_shawed_dpww_by_id(i915, id);
}

void intew_ddi_enabwe_cwock(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state)
{
	if (encodew->enabwe_cwock)
		encodew->enabwe_cwock(encodew, cwtc_state);
}

void intew_ddi_disabwe_cwock(stwuct intew_encodew *encodew)
{
	if (encodew->disabwe_cwock)
		encodew->disabwe_cwock(encodew);
}

void intew_ddi_sanitize_encodew_pww_mapping(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	u32 powt_mask;
	boow ddi_cwk_needed;

	/*
	 * In case of DP MST, we sanitize the pwimawy encodew onwy, not the
	 * viwtuaw ones.
	 */
	if (encodew->type == INTEW_OUTPUT_DP_MST)
		wetuwn;

	if (!encodew->base.cwtc && intew_encodew_is_dp(encodew)) {
		u8 pipe_mask;
		boow is_mst;

		intew_ddi_get_encodew_pipes(encodew, &pipe_mask, &is_mst);
		/*
		 * In the unwikewy case that BIOS enabwes DP in MST mode, just
		 * wawn since ouw MST HW weadout is incompwete.
		 */
		if (dwm_WAWN_ON(&i915->dwm, is_mst))
			wetuwn;
	}

	powt_mask = BIT(encodew->powt);
	ddi_cwk_needed = encodew->base.cwtc;

	if (encodew->type == INTEW_OUTPUT_DSI) {
		stwuct intew_encodew *othew_encodew;

		powt_mask = intew_dsi_encodew_powts(encodew);
		/*
		 * Sanity check that we haven't incowwectwy wegistewed anothew
		 * encodew using any of the powts of this DSI encodew.
		 */
		fow_each_intew_encodew(&i915->dwm, othew_encodew) {
			if (othew_encodew == encodew)
				continue;

			if (dwm_WAWN_ON(&i915->dwm,
					powt_mask & BIT(othew_encodew->powt)))
				wetuwn;
		}
		/*
		 * Fow DSI we keep the ddi cwocks gated
		 * except duwing enabwe/disabwe sequence.
		 */
		ddi_cwk_needed = fawse;
	}

	if (ddi_cwk_needed || !encodew->is_cwock_enabwed ||
	    !encodew->is_cwock_enabwed(encodew))
		wetuwn;

	dwm_notice(&i915->dwm,
		   "[ENCODEW:%d:%s] is disabwed/in DSI mode with an ungated DDI cwock, gate it\n",
		   encodew->base.base.id, encodew->base.name);

	encodew->disabwe_cwock(encodew);
}

static void
icw_pwogwam_mg_dp_mode(stwuct intew_digitaw_powt *dig_powt,
		       const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dig_powt->base.base.dev);
	enum tc_powt tc_powt = intew_powt_to_tc(dev_pwiv, dig_powt->base.powt);
	enum phy phy = intew_powt_to_phy(dev_pwiv, dig_powt->base.powt);
	u32 wn0, wn1, pin_assignment;
	u8 width;

	if (!intew_phy_is_tc(dev_pwiv, phy) ||
	    intew_tc_powt_in_tbt_awt_mode(dig_powt))
		wetuwn;

	if (DISPWAY_VEW(dev_pwiv) >= 12) {
		wn0 = intew_dkw_phy_wead(dev_pwiv, DKW_DP_MODE(tc_powt, 0));
		wn1 = intew_dkw_phy_wead(dev_pwiv, DKW_DP_MODE(tc_powt, 1));
	} ewse {
		wn0 = intew_de_wead(dev_pwiv, MG_DP_MODE(0, tc_powt));
		wn1 = intew_de_wead(dev_pwiv, MG_DP_MODE(1, tc_powt));
	}

	wn0 &= ~(MG_DP_MODE_CFG_DP_X1_MODE | MG_DP_MODE_CFG_DP_X2_MODE);
	wn1 &= ~(MG_DP_MODE_CFG_DP_X1_MODE | MG_DP_MODE_CFG_DP_X2_MODE);

	/* DPPATC */
	pin_assignment = intew_tc_powt_get_pin_assignment_mask(dig_powt);
	width = cwtc_state->wane_count;

	switch (pin_assignment) {
	case 0x0:
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    !intew_tc_powt_in_wegacy_mode(dig_powt));
		if (width == 1) {
			wn1 |= MG_DP_MODE_CFG_DP_X1_MODE;
		} ewse {
			wn0 |= MG_DP_MODE_CFG_DP_X2_MODE;
			wn1 |= MG_DP_MODE_CFG_DP_X2_MODE;
		}
		bweak;
	case 0x1:
		if (width == 4) {
			wn0 |= MG_DP_MODE_CFG_DP_X2_MODE;
			wn1 |= MG_DP_MODE_CFG_DP_X2_MODE;
		}
		bweak;
	case 0x2:
		if (width == 2) {
			wn0 |= MG_DP_MODE_CFG_DP_X2_MODE;
			wn1 |= MG_DP_MODE_CFG_DP_X2_MODE;
		}
		bweak;
	case 0x3:
	case 0x5:
		if (width == 1) {
			wn0 |= MG_DP_MODE_CFG_DP_X1_MODE;
			wn1 |= MG_DP_MODE_CFG_DP_X1_MODE;
		} ewse {
			wn0 |= MG_DP_MODE_CFG_DP_X2_MODE;
			wn1 |= MG_DP_MODE_CFG_DP_X2_MODE;
		}
		bweak;
	case 0x4:
	case 0x6:
		if (width == 1) {
			wn0 |= MG_DP_MODE_CFG_DP_X1_MODE;
			wn1 |= MG_DP_MODE_CFG_DP_X1_MODE;
		} ewse {
			wn0 |= MG_DP_MODE_CFG_DP_X2_MODE;
			wn1 |= MG_DP_MODE_CFG_DP_X2_MODE;
		}
		bweak;
	defauwt:
		MISSING_CASE(pin_assignment);
	}

	if (DISPWAY_VEW(dev_pwiv) >= 12) {
		intew_dkw_phy_wwite(dev_pwiv, DKW_DP_MODE(tc_powt, 0), wn0);
		intew_dkw_phy_wwite(dev_pwiv, DKW_DP_MODE(tc_powt, 1), wn1);
	} ewse {
		intew_de_wwite(dev_pwiv, MG_DP_MODE(0, tc_powt), wn0);
		intew_de_wwite(dev_pwiv, MG_DP_MODE(1, tc_powt), wn1);
	}
}

static enum twanscodew
tgw_dp_tp_twanscodew(const stwuct intew_cwtc_state *cwtc_state)
{
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DP_MST))
		wetuwn cwtc_state->mst_mastew_twanscodew;
	ewse
		wetuwn cwtc_state->cpu_twanscodew;
}

i915_weg_t dp_tp_ctw_weg(stwuct intew_encodew *encodew,
			 const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	if (DISPWAY_VEW(dev_pwiv) >= 12)
		wetuwn TGW_DP_TP_CTW(tgw_dp_tp_twanscodew(cwtc_state));
	ewse
		wetuwn DP_TP_CTW(encodew->powt);
}

i915_weg_t dp_tp_status_weg(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	if (DISPWAY_VEW(dev_pwiv) >= 12)
		wetuwn TGW_DP_TP_STATUS(tgw_dp_tp_twanscodew(cwtc_state));
	ewse
		wetuwn DP_TP_STATUS(encodew->powt);
}

static void intew_dp_sink_set_msa_timing_paw_ignowe_state(stwuct intew_dp *intew_dp,
							  const stwuct intew_cwtc_state *cwtc_state,
							  boow enabwe)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);

	if (!cwtc_state->vww.enabwe)
		wetuwn;

	if (dwm_dp_dpcd_wwiteb(&intew_dp->aux, DP_DOWNSPWEAD_CTWW,
			       enabwe ? DP_MSA_TIMING_PAW_IGNOWE_EN : 0) <= 0)
		dwm_dbg_kms(&i915->dwm,
			    "Faiwed to %s MSA_TIMING_PAW_IGNOWE in the sink\n",
			    stw_enabwe_disabwe(enabwe));
}

static void intew_dp_sink_set_fec_weady(stwuct intew_dp *intew_dp,
					const stwuct intew_cwtc_state *cwtc_state,
					boow enabwe)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);

	if (!cwtc_state->fec_enabwe)
		wetuwn;

	if (dwm_dp_dpcd_wwiteb(&intew_dp->aux, DP_FEC_CONFIGUWATION,
			       enabwe ? DP_FEC_WEADY : 0) <= 0)
		dwm_dbg_kms(&i915->dwm, "Faiwed to set FEC_WEADY to %s in the sink\n",
			    enabwe ? "enabwed" : "disabwed");

	if (enabwe &&
	    dwm_dp_dpcd_wwiteb(&intew_dp->aux, DP_FEC_STATUS,
			       DP_FEC_DECODE_EN_DETECTED | DP_FEC_DECODE_DIS_DETECTED) <= 0)
		dwm_dbg_kms(&i915->dwm, "Faiwed to cweaw FEC detected fwags\n");
}

static int wead_fec_detected_status(stwuct dwm_dp_aux *aux)
{
	int wet;
	u8 status;

	wet = dwm_dp_dpcd_weadb(aux, DP_FEC_STATUS, &status);
	if (wet < 0)
		wetuwn wet;

	wetuwn status;
}

static void wait_fow_fec_detected(stwuct dwm_dp_aux *aux, boow enabwed)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(aux->dwm_dev);
	int mask = enabwed ? DP_FEC_DECODE_EN_DETECTED : DP_FEC_DECODE_DIS_DETECTED;
	int status;
	int eww;

	eww = weadx_poww_timeout(wead_fec_detected_status, aux, status,
				 status & mask || status < 0,
				 10000, 200000);

	if (!eww && status >= 0)
		wetuwn;

	if (eww == -ETIMEDOUT)
		dwm_dbg_kms(&i915->dwm, "Timeout waiting fow FEC %s to get detected\n",
			    stw_enabwed_disabwed(enabwed));
	ewse
		dwm_dbg_kms(&i915->dwm, "FEC detected status wead ewwow: %d\n", status);
}

void intew_ddi_wait_fow_fec_status(stwuct intew_encodew *encodew,
				   const stwuct intew_cwtc_state *cwtc_state,
				   boow enabwed)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	int wet;

	if (!cwtc_state->fec_enabwe)
		wetuwn;

	if (enabwed)
		wet = intew_de_wait_fow_set(i915, dp_tp_status_weg(encodew, cwtc_state),
					    DP_TP_STATUS_FEC_ENABWE_WIVE, 1);
	ewse
		wet = intew_de_wait_fow_cweaw(i915, dp_tp_status_weg(encodew, cwtc_state),
					      DP_TP_STATUS_FEC_ENABWE_WIVE, 1);

	if (wet)
		dwm_eww(&i915->dwm,
			"Timeout waiting fow FEC wive state to get %s\n",
			stw_enabwed_disabwed(enabwed));

	/*
	 * At weast the Synoptics MST hub doesn't set the detected fwag fow
	 * FEC decoding disabwing so skip waiting fow that.
	 */
	if (enabwed)
		wait_fow_fec_detected(&intew_dp->aux, enabwed);
}

static void intew_ddi_enabwe_fec(stwuct intew_encodew *encodew,
				 const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	if (!cwtc_state->fec_enabwe)
		wetuwn;

	intew_de_wmw(dev_pwiv, dp_tp_ctw_weg(encodew, cwtc_state),
		     0, DP_TP_CTW_FEC_ENABWE);
}

static void intew_ddi_disabwe_fec(stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	if (!cwtc_state->fec_enabwe)
		wetuwn;

	intew_de_wmw(dev_pwiv, dp_tp_ctw_weg(encodew, cwtc_state),
		     DP_TP_CTW_FEC_ENABWE, 0);
	intew_de_posting_wead(dev_pwiv, dp_tp_ctw_weg(encodew, cwtc_state));
}

static void intew_ddi_powew_up_wanes(stwuct intew_encodew *encodew,
				     const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	if (intew_phy_is_combo(i915, phy)) {
		boow wane_wevewsaw =
			dig_powt->saved_powt_bits & DDI_BUF_POWT_WEVEWSAW;

		intew_combo_phy_powew_up_wanes(i915, phy, fawse,
					       cwtc_state->wane_count,
					       wane_wevewsaw);
	}
}

/* Spwittew enabwe fow eDP MSO is wimited to cewtain pipes. */
static u8 intew_ddi_spwittew_pipe_mask(stwuct dwm_i915_pwivate *i915)
{
	if (IS_AWDEWWAKE_P(i915))
		wetuwn BIT(PIPE_A) | BIT(PIPE_B);
	ewse
		wetuwn BIT(PIPE_A);
}

static void intew_ddi_mso_get_config(stwuct intew_encodew *encodew,
				     stwuct intew_cwtc_state *pipe_config)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(pipe_config->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	u32 dss1;

	if (!HAS_MSO(i915))
		wetuwn;

	dss1 = intew_de_wead(i915, ICW_PIPE_DSS_CTW1(pipe));

	pipe_config->spwittew.enabwe = dss1 & SPWITTEW_ENABWE;
	if (!pipe_config->spwittew.enabwe)
		wetuwn;

	if (dwm_WAWN_ON(&i915->dwm, !(intew_ddi_spwittew_pipe_mask(i915) & BIT(pipe)))) {
		pipe_config->spwittew.enabwe = fawse;
		wetuwn;
	}

	switch (dss1 & SPWITTEW_CONFIGUWATION_MASK) {
	defauwt:
		dwm_WAWN(&i915->dwm, twue,
			 "Invawid spwittew configuwation, dss1=0x%08x\n", dss1);
		fawwthwough;
	case SPWITTEW_CONFIGUWATION_2_SEGMENT:
		pipe_config->spwittew.wink_count = 2;
		bweak;
	case SPWITTEW_CONFIGUWATION_4_SEGMENT:
		pipe_config->spwittew.wink_count = 4;
		bweak;
	}

	pipe_config->spwittew.pixew_ovewwap = WEG_FIEWD_GET(OVEWWAP_PIXEWS_MASK, dss1);
}

static void intew_ddi_mso_configuwe(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	u32 dss1 = 0;

	if (!HAS_MSO(i915))
		wetuwn;

	if (cwtc_state->spwittew.enabwe) {
		dss1 |= SPWITTEW_ENABWE;
		dss1 |= OVEWWAP_PIXEWS(cwtc_state->spwittew.pixew_ovewwap);
		if (cwtc_state->spwittew.wink_count == 2)
			dss1 |= SPWITTEW_CONFIGUWATION_2_SEGMENT;
		ewse
			dss1 |= SPWITTEW_CONFIGUWATION_4_SEGMENT;
	}

	intew_de_wmw(i915, ICW_PIPE_DSS_CTW1(pipe),
		     SPWITTEW_ENABWE | SPWITTEW_CONFIGUWATION_MASK |
		     OVEWWAP_PIXEWS_MASK, dss1);
}

static u8 mtw_get_powt_width(u8 wane_count)
{
	switch (wane_count) {
	case 1:
		wetuwn 0;
	case 2:
		wetuwn 1;
	case 3:
		wetuwn 4;
	case 4:
		wetuwn 3;
	defauwt:
		MISSING_CASE(wane_count);
		wetuwn 4;
	}
}

static void
mtw_ddi_enabwe_d2d(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;

	intew_de_wmw(dev_pwiv, XEWPDP_POWT_BUF_CTW1(powt), 0,
		     XEWPDP_POWT_BUF_D2D_WINK_ENABWE);

	if (wait_fow_us((intew_de_wead(dev_pwiv, XEWPDP_POWT_BUF_CTW1(powt)) &
			 XEWPDP_POWT_BUF_D2D_WINK_STATE), 100)) {
		dwm_eww(&dev_pwiv->dwm, "Timeout waiting fow D2D Wink enabwe fow POWT_BUF_CTW %c\n",
			powt_name(powt));
	}
}

static void mtw_powt_buf_ctw_pwogwam(stwuct intew_encodew *encodew,
				     const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	enum powt powt = encodew->powt;
	u32 vaw;

	vaw = intew_de_wead(i915, XEWPDP_POWT_BUF_CTW1(powt));
	vaw &= ~XEWPDP_POWT_WIDTH_MASK;
	vaw |= XEWPDP_POWT_WIDTH(mtw_get_powt_width(cwtc_state->wane_count));

	vaw &= ~XEWPDP_POWT_BUF_POWT_DATA_WIDTH_MASK;
	if (intew_dp_is_uhbw(cwtc_state))
		vaw |= XEWPDP_POWT_BUF_POWT_DATA_40BIT;
	ewse
		vaw |= XEWPDP_POWT_BUF_POWT_DATA_10BIT;

	if (dig_powt->saved_powt_bits & DDI_BUF_POWT_WEVEWSAW)
		vaw |= XEWPDP_POWT_WEVEWSAW;

	intew_de_wwite(i915, XEWPDP_POWT_BUF_CTW1(powt), vaw);
}

static void mtw_powt_buf_ctw_io_sewection(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	u32 vaw;

	vaw = intew_tc_powt_in_tbt_awt_mode(dig_powt) ?
	      XEWPDP_POWT_BUF_IO_SEWECT_TBT : 0;
	intew_de_wmw(i915, XEWPDP_POWT_BUF_CTW1(encodew->powt),
		     XEWPDP_POWT_BUF_IO_SEWECT_TBT, vaw);
}

static void mtw_ddi_pwe_enabwe_dp(stwuct intew_atomic_state *state,
				  stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *cwtc_state,
				  const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	boow is_mst = intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DP_MST);

	intew_dp_set_wink_pawams(intew_dp,
				 cwtc_state->powt_cwock,
				 cwtc_state->wane_count);

	/*
	 * We onwy configuwe what the wegistew vawue wiww be hewe.  Actuaw
	 * enabwing happens duwing wink twaining fawthew down.
	 */
	intew_ddi_init_dp_buf_weg(encodew, cwtc_state);

	/*
	 * 1. Enabwe Powew Wewws
	 *
	 * This was handwed at the beginning of intew_atomic_commit_taiw(),
	 * befowe we cawwed down into this function.
	 */

	/* 2. PMdemand was awweady set */

	/* 3. Sewect Thundewbowt */
	mtw_powt_buf_ctw_io_sewection(encodew);

	/* 4. Enabwe Panew Powew if PPS is wequiwed */
	intew_pps_on(intew_dp);

	/* 5. Enabwe the powt PWW */
	intew_ddi_enabwe_cwock(encodew, cwtc_state);

	/*
	 * 6.a Configuwe Twanscodew Cwock Sewect to diwect the Powt cwock to the
	 * Twanscodew.
	 */
	intew_ddi_enabwe_twanscodew_cwock(encodew, cwtc_state);

	/*
	 * 6.b If DP v2.0/128b mode - Configuwe TWANS_DP2_CTW wegistew settings.
	 */
	intew_ddi_config_twanscodew_dp2(encodew, cwtc_state);

	/*
	 * 6.c Configuwe TWANS_DDI_FUNC_CTW DDI Sewect, DDI Mode Sewect & MST
	 * Twanspowt Sewect
	 */
	intew_ddi_config_twanscodew_func(encodew, cwtc_state);

	/*
	 * 6.e Pwogwam CoG/MSO configuwation bits in DSS_CTW1 if sewected.
	 */
	intew_ddi_mso_configuwe(cwtc_state);

	if (!is_mst)
		intew_dp_set_powew(intew_dp, DP_SET_POWEW_D0);

	intew_dp_configuwe_pwotocow_convewtew(intew_dp, cwtc_state);
	if (!is_mst)
		intew_dp_sink_enabwe_decompwession(state,
						   to_intew_connectow(conn_state->connectow),
						   cwtc_state);

	/*
	 * DDI FEC: "anticipates enabwing FEC encoding sets the FEC_WEADY bit
	 * in the FEC_CONFIGUWATION wegistew to 1 befowe initiating wink
	 * twaining
	 */
	intew_dp_sink_set_fec_weady(intew_dp, cwtc_state, twue);

	intew_dp_check_fww_twaining(intew_dp);
	intew_dp_pcon_dsc_configuwe(intew_dp, cwtc_state);

	/*
	 * 6. The west of the bewow awe substeps undew the bspec's "Enabwe and
	 * Twain Dispway Powt" step.  Note that steps that awe specific to
	 * MST wiww be handwed by intew_mst_pwe_enabwe_dp() befowe/aftew it
	 * cawws into this function.  Awso intew_mst_pwe_enabwe_dp() onwy cawws
	 * us when active_mst_winks==0, so any steps designated fow "singwe
	 * stweam ow muwti-stweam mastew twanscodew" can just be pewfowmed
	 * unconditionawwy hewe.
	 *
	 * mtw_ddi_pwepawe_wink_wetwain() that is cawwed by
	 * intew_dp_stawt_wink_twain() wiww execute steps: 6.d, 6.f, 6.g, 6.h,
	 * 6.i and 6.j
	 *
	 * 6.k Fowwow DispwayPowt specification twaining sequence (see notes fow
	 *     faiwuwe handwing)
	 * 6.m If DispwayPowt muwti-stweam - Set DP_TP_CTW wink twaining to Idwe
	 *     Pattewn, wait fow 5 idwe pattewns (DP_TP_STATUS Min_Idwes_Sent)
	 *     (timeout aftew 800 us)
	 */
	intew_dp_stawt_wink_twain(intew_dp, cwtc_state);

	/* 6.n Set DP_TP_CTW wink twaining to Nowmaw */
	if (!is_twans_powt_sync_mode(cwtc_state))
		intew_dp_stop_wink_twain(intew_dp, cwtc_state);

	/* 6.o Configuwe and enabwe FEC if needed */
	intew_ddi_enabwe_fec(encodew, cwtc_state);

	if (!is_mst)
		intew_dsc_dp_pps_wwite(encodew, cwtc_state);
}

static void tgw_ddi_pwe_enabwe_dp(stwuct intew_atomic_state *state,
				  stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *cwtc_state,
				  const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	boow is_mst = intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DP_MST);

	intew_dp_set_wink_pawams(intew_dp,
				 cwtc_state->powt_cwock,
				 cwtc_state->wane_count);

	/*
	 * We onwy configuwe what the wegistew vawue wiww be hewe.  Actuaw
	 * enabwing happens duwing wink twaining fawthew down.
	 */
	intew_ddi_init_dp_buf_weg(encodew, cwtc_state);

	/*
	 * 1. Enabwe Powew Wewws
	 *
	 * This was handwed at the beginning of intew_atomic_commit_taiw(),
	 * befowe we cawwed down into this function.
	 */

	/* 2. Enabwe Panew Powew if PPS is wequiwed */
	intew_pps_on(intew_dp);

	/*
	 * 3. Fow non-TBT Type-C powts, set FIA wane count
	 * (DFWEXDPSP.DPX4TXWATC)
	 *
	 * This was done befowe tgw_ddi_pwe_enabwe_dp by
	 * hsw_cwtc_enabwe()->intew_encodews_pwe_pww_enabwe().
	 */

	/*
	 * 4. Enabwe the powt PWW.
	 *
	 * The PWW enabwing itsewf was awweady done befowe this function by
	 * hsw_cwtc_enabwe()->intew_enabwe_shawed_dpww().  We need onwy
	 * configuwe the PWW to powt mapping hewe.
	 */
	intew_ddi_enabwe_cwock(encodew, cwtc_state);

	/* 5. If IO powew is contwowwed thwough PWW_WEWW_CTW, Enabwe IO Powew */
	if (!intew_tc_powt_in_tbt_awt_mode(dig_powt)) {
		dwm_WAWN_ON(&dev_pwiv->dwm, dig_powt->ddi_io_wakewef);
		dig_powt->ddi_io_wakewef = intew_dispway_powew_get(dev_pwiv,
								   dig_powt->ddi_io_powew_domain);
	}

	/* 6. Pwogwam DP_MODE */
	icw_pwogwam_mg_dp_mode(dig_powt, cwtc_state);

	/*
	 * 7. The west of the bewow awe substeps undew the bspec's "Enabwe and
	 * Twain Dispway Powt" step.  Note that steps that awe specific to
	 * MST wiww be handwed by intew_mst_pwe_enabwe_dp() befowe/aftew it
	 * cawws into this function.  Awso intew_mst_pwe_enabwe_dp() onwy cawws
	 * us when active_mst_winks==0, so any steps designated fow "singwe
	 * stweam ow muwti-stweam mastew twanscodew" can just be pewfowmed
	 * unconditionawwy hewe.
	 */

	/*
	 * 7.a Configuwe Twanscodew Cwock Sewect to diwect the Powt cwock to the
	 * Twanscodew.
	 */
	intew_ddi_enabwe_twanscodew_cwock(encodew, cwtc_state);

	if (HAS_DP20(dev_pwiv))
		intew_ddi_config_twanscodew_dp2(encodew, cwtc_state);

	/*
	 * 7.b Configuwe TWANS_DDI_FUNC_CTW DDI Sewect, DDI Mode Sewect & MST
	 * Twanspowt Sewect
	 */
	intew_ddi_config_twanscodew_func(encodew, cwtc_state);

	/*
	 * 7.c Configuwe & enabwe DP_TP_CTW with wink twaining pattewn 1
	 * sewected
	 *
	 * This wiww be handwed by the intew_dp_stawt_wink_twain() fawthew
	 * down this function.
	 */

	/* 7.e Configuwe vowtage swing and wewated IO settings */
	encodew->set_signaw_wevews(encodew, cwtc_state);

	/*
	 * 7.f Combo PHY: Configuwe POWT_CW_DW10 Static Powew Down to powew up
	 * the used wanes of the DDI.
	 */
	intew_ddi_powew_up_wanes(encodew, cwtc_state);

	/*
	 * 7.g Pwogwam CoG/MSO configuwation bits in DSS_CTW1 if sewected.
	 */
	intew_ddi_mso_configuwe(cwtc_state);

	if (!is_mst)
		intew_dp_set_powew(intew_dp, DP_SET_POWEW_D0);

	intew_dp_configuwe_pwotocow_convewtew(intew_dp, cwtc_state);
	if (!is_mst)
		intew_dp_sink_enabwe_decompwession(state,
						   to_intew_connectow(conn_state->connectow),
						   cwtc_state);
	/*
	 * DDI FEC: "anticipates enabwing FEC encoding sets the FEC_WEADY bit
	 * in the FEC_CONFIGUWATION wegistew to 1 befowe initiating wink
	 * twaining
	 */
	intew_dp_sink_set_fec_weady(intew_dp, cwtc_state, twue);

	intew_dp_check_fww_twaining(intew_dp);
	intew_dp_pcon_dsc_configuwe(intew_dp, cwtc_state);

	/*
	 * 7.i Fowwow DispwayPowt specification twaining sequence (see notes fow
	 *     faiwuwe handwing)
	 * 7.j If DispwayPowt muwti-stweam - Set DP_TP_CTW wink twaining to Idwe
	 *     Pattewn, wait fow 5 idwe pattewns (DP_TP_STATUS Min_Idwes_Sent)
	 *     (timeout aftew 800 us)
	 */
	intew_dp_stawt_wink_twain(intew_dp, cwtc_state);

	/* 7.k Set DP_TP_CTW wink twaining to Nowmaw */
	if (!is_twans_powt_sync_mode(cwtc_state))
		intew_dp_stop_wink_twain(intew_dp, cwtc_state);

	/* 7.w Configuwe and enabwe FEC if needed */
	intew_ddi_enabwe_fec(encodew, cwtc_state);

	if (!is_mst)
		intew_dsc_dp_pps_wwite(encodew, cwtc_state);
}

static void hsw_ddi_pwe_enabwe_dp(stwuct intew_atomic_state *state,
				  stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *cwtc_state,
				  const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	boow is_mst = intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DP_MST);

	if (DISPWAY_VEW(dev_pwiv) < 11)
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    is_mst && (powt == POWT_A || powt == POWT_E));
	ewse
		dwm_WAWN_ON(&dev_pwiv->dwm, is_mst && powt == POWT_A);

	intew_dp_set_wink_pawams(intew_dp,
				 cwtc_state->powt_cwock,
				 cwtc_state->wane_count);

	/*
	 * We onwy configuwe what the wegistew vawue wiww be hewe.  Actuaw
	 * enabwing happens duwing wink twaining fawthew down.
	 */
	intew_ddi_init_dp_buf_weg(encodew, cwtc_state);

	intew_pps_on(intew_dp);

	intew_ddi_enabwe_cwock(encodew, cwtc_state);

	if (!intew_tc_powt_in_tbt_awt_mode(dig_powt)) {
		dwm_WAWN_ON(&dev_pwiv->dwm, dig_powt->ddi_io_wakewef);
		dig_powt->ddi_io_wakewef = intew_dispway_powew_get(dev_pwiv,
								   dig_powt->ddi_io_powew_domain);
	}

	icw_pwogwam_mg_dp_mode(dig_powt, cwtc_state);

	if (has_buf_twans_sewect(dev_pwiv))
		hsw_pwepawe_dp_ddi_buffews(encodew, cwtc_state);

	encodew->set_signaw_wevews(encodew, cwtc_state);

	intew_ddi_powew_up_wanes(encodew, cwtc_state);

	if (!is_mst)
		intew_dp_set_powew(intew_dp, DP_SET_POWEW_D0);
	intew_dp_configuwe_pwotocow_convewtew(intew_dp, cwtc_state);
	if (!is_mst)
		intew_dp_sink_enabwe_decompwession(state,
						   to_intew_connectow(conn_state->connectow),
						   cwtc_state);
	intew_dp_sink_set_fec_weady(intew_dp, cwtc_state, twue);
	intew_dp_stawt_wink_twain(intew_dp, cwtc_state);
	if ((powt != POWT_A || DISPWAY_VEW(dev_pwiv) >= 9) &&
	    !is_twans_powt_sync_mode(cwtc_state))
		intew_dp_stop_wink_twain(intew_dp, cwtc_state);

	intew_ddi_enabwe_fec(encodew, cwtc_state);

	if (!is_mst) {
		intew_ddi_enabwe_twanscodew_cwock(encodew, cwtc_state);
		intew_dsc_dp_pps_wwite(encodew, cwtc_state);
	}
}

static void intew_ddi_pwe_enabwe_dp(stwuct intew_atomic_state *state,
				    stwuct intew_encodew *encodew,
				    const stwuct intew_cwtc_state *cwtc_state,
				    const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

	if (HAS_DP20(dev_pwiv)) {
		intew_dp_128b132b_sdp_cwc16(enc_to_intew_dp(encodew),
					    cwtc_state);
		if (cwtc_state->has_panew_wepway)
			dwm_dp_dpcd_wwiteb(&intew_dp->aux, PANEW_WEPWAY_CONFIG,
					   DP_PANEW_WEPWAY_ENABWE);
	}

	if (DISPWAY_VEW(dev_pwiv) >= 14)
		mtw_ddi_pwe_enabwe_dp(state, encodew, cwtc_state, conn_state);
	ewse if (DISPWAY_VEW(dev_pwiv) >= 12)
		tgw_ddi_pwe_enabwe_dp(state, encodew, cwtc_state, conn_state);
	ewse
		hsw_ddi_pwe_enabwe_dp(state, encodew, cwtc_state, conn_state);

	/* MST wiww caww a setting of MSA aftew an awwocating of Viwtuaw Channew
	 * fwom MST encodew pwe_enabwe cawwback.
	 */
	if (!intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DP_MST))
		intew_ddi_set_dp_msa(cwtc_state, conn_state);
}

static void intew_ddi_pwe_enabwe_hdmi(stwuct intew_atomic_state *state,
				      stwuct intew_encodew *encodew,
				      const stwuct intew_cwtc_state *cwtc_state,
				      const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	stwuct intew_hdmi *intew_hdmi = &dig_powt->hdmi;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	intew_dp_duaw_mode_set_tmds_output(intew_hdmi, twue);
	intew_ddi_enabwe_cwock(encodew, cwtc_state);

	dwm_WAWN_ON(&dev_pwiv->dwm, dig_powt->ddi_io_wakewef);
	dig_powt->ddi_io_wakewef = intew_dispway_powew_get(dev_pwiv,
							   dig_powt->ddi_io_powew_domain);

	icw_pwogwam_mg_dp_mode(dig_powt, cwtc_state);

	intew_ddi_enabwe_twanscodew_cwock(encodew, cwtc_state);

	dig_powt->set_infofwames(encodew,
				 cwtc_state->has_infofwame,
				 cwtc_state, conn_state);
}

static void intew_ddi_pwe_enabwe(stwuct intew_atomic_state *state,
				 stwuct intew_encodew *encodew,
				 const stwuct intew_cwtc_state *cwtc_state,
				 const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	/*
	 * When cawwed fwom DP MST code:
	 * - conn_state wiww be NUWW
	 * - encodew wiww be the main encodew (ie. mst->pwimawy)
	 * - the main connectow associated with this powt
	 *   won't be active ow winked to a cwtc
	 * - cwtc_state wiww be the state of the fiwst stweam to
	 *   be activated on this powt, and it may not be the same
	 *   stweam that wiww be deactivated wast, but each stweam
	 *   shouwd have a state that is identicaw when it comes to
	 *   the DP wink pawametewes
	 */

	dwm_WAWN_ON(&dev_pwiv->dwm, cwtc_state->has_pch_encodew);

	intew_set_cpu_fifo_undewwun_wepowting(dev_pwiv, pipe, twue);

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI)) {
		intew_ddi_pwe_enabwe_hdmi(state, encodew, cwtc_state,
					  conn_state);
	} ewse {
		stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);

		intew_ddi_pwe_enabwe_dp(state, encodew, cwtc_state,
					conn_state);

		/* FIXME pwecompute evewything pwopewwy */
		/* FIXME how do we tuwn infofwames off again? */
		if (dig_powt->wspcon.active && intew_dp_has_hdmi_sink(&dig_powt->dp))
			dig_powt->set_infofwames(encodew,
						 cwtc_state->has_infofwame,
						 cwtc_state, conn_state);
	}
}

static void
mtw_ddi_disabwe_d2d_wink(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;

	intew_de_wmw(dev_pwiv, XEWPDP_POWT_BUF_CTW1(powt),
		     XEWPDP_POWT_BUF_D2D_WINK_ENABWE, 0);

	if (wait_fow_us(!(intew_de_wead(dev_pwiv, XEWPDP_POWT_BUF_CTW1(powt)) &
			  XEWPDP_POWT_BUF_D2D_WINK_STATE), 100))
		dwm_eww(&dev_pwiv->dwm, "Timeout waiting fow D2D Wink disabwe fow POWT_BUF_CTW %c\n",
			powt_name(powt));
}

static void mtw_disabwe_ddi_buf(stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;
	u32 vaw;

	/* 3.b Cweaw DDI_CTW_DE Enabwe to 0. */
	vaw = intew_de_wead(dev_pwiv, DDI_BUF_CTW(powt));
	if (vaw & DDI_BUF_CTW_ENABWE) {
		vaw &= ~DDI_BUF_CTW_ENABWE;
		intew_de_wwite(dev_pwiv, DDI_BUF_CTW(powt), vaw);

		/* 3.c Poww fow POWT_BUF_CTW Idwe Status == 1, timeout aftew 100us */
		mtw_wait_ddi_buf_idwe(dev_pwiv, powt);
	}

	/* 3.d Disabwe D2D Wink */
	mtw_ddi_disabwe_d2d_wink(encodew);

	/* 3.e Disabwe DP_TP_CTW */
	if (intew_cwtc_has_dp_encodew(cwtc_state)) {
		intew_de_wmw(dev_pwiv, dp_tp_ctw_weg(encodew, cwtc_state),
			     DP_TP_CTW_ENABWE, 0);
	}
}

static void disabwe_ddi_buf(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;
	boow wait = fawse;
	u32 vaw;

	vaw = intew_de_wead(dev_pwiv, DDI_BUF_CTW(powt));
	if (vaw & DDI_BUF_CTW_ENABWE) {
		vaw &= ~DDI_BUF_CTW_ENABWE;
		intew_de_wwite(dev_pwiv, DDI_BUF_CTW(powt), vaw);
		wait = twue;
	}

	if (intew_cwtc_has_dp_encodew(cwtc_state))
		intew_de_wmw(dev_pwiv, dp_tp_ctw_weg(encodew, cwtc_state),
			     DP_TP_CTW_ENABWE, 0);

	intew_ddi_disabwe_fec(encodew, cwtc_state);

	if (wait)
		intew_wait_ddi_buf_idwe(dev_pwiv, powt);
}

static void intew_disabwe_ddi_buf(stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	if (DISPWAY_VEW(dev_pwiv) >= 14) {
		mtw_disabwe_ddi_buf(encodew, cwtc_state);

		/* 3.f Disabwe DP_TP_CTW FEC Enabwe if it is needed */
		intew_ddi_disabwe_fec(encodew, cwtc_state);
	} ewse {
		disabwe_ddi_buf(encodew, cwtc_state);
	}

	intew_ddi_wait_fow_fec_status(encodew, cwtc_state, fawse);
}

static void intew_ddi_post_disabwe_dp(stwuct intew_atomic_state *state,
				      stwuct intew_encodew *encodew,
				      const stwuct intew_cwtc_state *owd_cwtc_state,
				      const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	stwuct intew_dp *intew_dp = &dig_powt->dp;
	intew_wakewef_t wakewef;
	boow is_mst = intew_cwtc_has_type(owd_cwtc_state,
					  INTEW_OUTPUT_DP_MST);

	if (!is_mst)
		intew_dp_set_infofwames(encodew, fawse,
					owd_cwtc_state, owd_conn_state);

	/*
	 * Powew down sink befowe disabwing the powt, othewwise we end
	 * up getting intewwupts fwom the sink on detecting wink woss.
	 */
	intew_dp_set_powew(intew_dp, DP_SET_POWEW_D3);

	if (DISPWAY_VEW(dev_pwiv) >= 12) {
		if (is_mst) {
			enum twanscodew cpu_twanscodew = owd_cwtc_state->cpu_twanscodew;

			intew_de_wmw(dev_pwiv, TWANS_DDI_FUNC_CTW(cpu_twanscodew),
				     TGW_TWANS_DDI_POWT_MASK | TWANS_DDI_MODE_SEWECT_MASK,
				     0);
		}
	} ewse {
		if (!is_mst)
			intew_ddi_disabwe_twanscodew_cwock(owd_cwtc_state);
	}

	intew_disabwe_ddi_buf(encodew, owd_cwtc_state);

	intew_dp_sink_set_fec_weady(intew_dp, owd_cwtc_state, fawse);

	/*
	 * Fwom TGW spec: "If singwe stweam ow muwti-stweam mastew twanscodew:
	 * Configuwe Twanscodew Cwock sewect to diwect no cwock to the
	 * twanscodew"
	 */
	if (DISPWAY_VEW(dev_pwiv) >= 12)
		intew_ddi_disabwe_twanscodew_cwock(owd_cwtc_state);

	intew_pps_vdd_on(intew_dp);
	intew_pps_off(intew_dp);

	wakewef = fetch_and_zewo(&dig_powt->ddi_io_wakewef);

	if (wakewef)
		intew_dispway_powew_put(dev_pwiv,
					dig_powt->ddi_io_powew_domain,
					wakewef);

	intew_ddi_disabwe_cwock(encodew);

	/* De-sewect Thundewbowt */
	if (DISPWAY_VEW(dev_pwiv) >= 14)
		intew_de_wmw(dev_pwiv, XEWPDP_POWT_BUF_CTW1(encodew->powt),
			     XEWPDP_POWT_BUF_IO_SEWECT_TBT, 0);
}

static void intew_ddi_post_disabwe_hdmi(stwuct intew_atomic_state *state,
					stwuct intew_encodew *encodew,
					const stwuct intew_cwtc_state *owd_cwtc_state,
					const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	stwuct intew_hdmi *intew_hdmi = &dig_powt->hdmi;
	intew_wakewef_t wakewef;

	dig_powt->set_infofwames(encodew, fawse,
				 owd_cwtc_state, owd_conn_state);

	if (DISPWAY_VEW(dev_pwiv) < 12)
		intew_ddi_disabwe_twanscodew_cwock(owd_cwtc_state);

	intew_disabwe_ddi_buf(encodew, owd_cwtc_state);

	if (DISPWAY_VEW(dev_pwiv) >= 12)
		intew_ddi_disabwe_twanscodew_cwock(owd_cwtc_state);

	wakewef = fetch_and_zewo(&dig_powt->ddi_io_wakewef);
	if (wakewef)
		intew_dispway_powew_put(dev_pwiv,
					dig_powt->ddi_io_powew_domain,
					wakewef);

	intew_ddi_disabwe_cwock(encodew);

	intew_dp_duaw_mode_set_tmds_output(intew_hdmi, fawse);
}

static void intew_ddi_post_disabwe(stwuct intew_atomic_state *state,
				   stwuct intew_encodew *encodew,
				   const stwuct intew_cwtc_state *owd_cwtc_state,
				   const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *swave_cwtc;

	if (!intew_cwtc_has_type(owd_cwtc_state, INTEW_OUTPUT_DP_MST)) {
		intew_cwtc_vbwank_off(owd_cwtc_state);

		intew_disabwe_twanscodew(owd_cwtc_state);

		intew_ddi_disabwe_twanscodew_func(owd_cwtc_state);

		intew_dsc_disabwe(owd_cwtc_state);

		if (DISPWAY_VEW(dev_pwiv) >= 9)
			skw_scawew_disabwe(owd_cwtc_state);
		ewse
			iwk_pfit_disabwe(owd_cwtc_state);
	}

	fow_each_intew_cwtc_in_pipe_mask(&dev_pwiv->dwm, swave_cwtc,
					 intew_cwtc_bigjoinew_swave_pipes(owd_cwtc_state)) {
		const stwuct intew_cwtc_state *owd_swave_cwtc_state =
			intew_atomic_get_owd_cwtc_state(state, swave_cwtc);

		intew_cwtc_vbwank_off(owd_swave_cwtc_state);

		intew_dsc_disabwe(owd_swave_cwtc_state);
		skw_scawew_disabwe(owd_swave_cwtc_state);
	}

	/*
	 * When cawwed fwom DP MST code:
	 * - owd_conn_state wiww be NUWW
	 * - encodew wiww be the main encodew (ie. mst->pwimawy)
	 * - the main connectow associated with this powt
	 *   won't be active ow winked to a cwtc
	 * - owd_cwtc_state wiww be the state of the wast stweam to
	 *   be deactivated on this powt, and it may not be the same
	 *   stweam that was activated wast, but each stweam
	 *   shouwd have a state that is identicaw when it comes to
	 *   the DP wink pawametewes
	 */

	if (intew_cwtc_has_type(owd_cwtc_state, INTEW_OUTPUT_HDMI))
		intew_ddi_post_disabwe_hdmi(state, encodew, owd_cwtc_state,
					    owd_conn_state);
	ewse
		intew_ddi_post_disabwe_dp(state, encodew, owd_cwtc_state,
					  owd_conn_state);
}

static void intew_ddi_post_pww_disabwe(stwuct intew_atomic_state *state,
				       stwuct intew_encodew *encodew,
				       const stwuct intew_cwtc_state *owd_cwtc_state,
				       const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);
	boow is_tc_powt = intew_phy_is_tc(i915, phy);

	main_wink_aux_powew_domain_put(dig_powt, owd_cwtc_state);

	if (is_tc_powt)
		intew_tc_powt_put_wink(dig_powt);
}

static void twans_powt_sync_stop_wink_twain(stwuct intew_atomic_state *state,
					    stwuct intew_encodew *encodew,
					    const stwuct intew_cwtc_state *cwtc_state)
{
	const stwuct dwm_connectow_state *conn_state;
	stwuct dwm_connectow *conn;
	int i;

	if (!cwtc_state->sync_mode_swaves_mask)
		wetuwn;

	fow_each_new_connectow_in_state(&state->base, conn, conn_state, i) {
		stwuct intew_encodew *swave_encodew =
			to_intew_encodew(conn_state->best_encodew);
		stwuct intew_cwtc *swave_cwtc = to_intew_cwtc(conn_state->cwtc);
		const stwuct intew_cwtc_state *swave_cwtc_state;

		if (!swave_cwtc)
			continue;

		swave_cwtc_state =
			intew_atomic_get_new_cwtc_state(state, swave_cwtc);

		if (swave_cwtc_state->mastew_twanscodew !=
		    cwtc_state->cpu_twanscodew)
			continue;

		intew_dp_stop_wink_twain(enc_to_intew_dp(swave_encodew),
					 swave_cwtc_state);
	}

	usweep_wange(200, 400);

	intew_dp_stop_wink_twain(enc_to_intew_dp(encodew),
				 cwtc_state);
}

static void intew_enabwe_ddi_dp(stwuct intew_atomic_state *state,
				stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *cwtc_state,
				const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	enum powt powt = encodew->powt;

	if (powt == POWT_A && DISPWAY_VEW(dev_pwiv) < 9)
		intew_dp_stop_wink_twain(intew_dp, cwtc_state);

	dwm_connectow_update_pwivacy_scween(conn_state);
	intew_edp_backwight_on(cwtc_state, conn_state);

	if (!dig_powt->wspcon.active || intew_dp_has_hdmi_sink(&dig_powt->dp))
		intew_dp_set_infofwames(encodew, twue, cwtc_state, conn_state);

	twans_powt_sync_stop_wink_twain(state, encodew, cwtc_state);
}

/* FIXME bad home fow this function */
i915_weg_t hsw_chicken_twans_weg(stwuct dwm_i915_pwivate *i915,
				 enum twanscodew cpu_twanscodew)
{
	wetuwn DISPWAY_VEW(i915) >= 14 ?
		MTW_CHICKEN_TWANS(cpu_twanscodew) :
		CHICKEN_TWANS(cpu_twanscodew);
}

static i915_weg_t
gen9_chicken_twans_weg_by_powt(stwuct dwm_i915_pwivate *dev_pwiv,
			       enum powt powt)
{
	static const enum twanscodew twans[] = {
		[POWT_A] = TWANSCODEW_EDP,
		[POWT_B] = TWANSCODEW_A,
		[POWT_C] = TWANSCODEW_B,
		[POWT_D] = TWANSCODEW_C,
		[POWT_E] = TWANSCODEW_A,
	};

	dwm_WAWN_ON(&dev_pwiv->dwm, DISPWAY_VEW(dev_pwiv) < 9);

	if (dwm_WAWN_ON(&dev_pwiv->dwm, powt < POWT_A || powt > POWT_E))
		powt = POWT_A;

	wetuwn CHICKEN_TWANS(twans[powt]);
}

static void intew_enabwe_ddi_hdmi(stwuct intew_atomic_state *state,
				  stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *cwtc_state,
				  const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	stwuct dwm_connectow *connectow = conn_state->connectow;
	enum powt powt = encodew->powt;
	enum phy phy = intew_powt_to_phy(dev_pwiv, powt);
	u32 buf_ctw;

	if (!intew_hdmi_handwe_sink_scwambwing(encodew, connectow,
					       cwtc_state->hdmi_high_tmds_cwock_watio,
					       cwtc_state->hdmi_scwambwing))
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "[CONNECTOW:%d:%s] Faiwed to configuwe sink scwambwing/TMDS bit cwock watio\n",
			    connectow->base.id, connectow->name);

	if (has_buf_twans_sewect(dev_pwiv))
		hsw_pwepawe_hdmi_ddi_buffews(encodew, cwtc_state);

	/* e. Enabwe D2D Wink fow C10/C20 Phy */
	if (DISPWAY_VEW(dev_pwiv) >= 14)
		mtw_ddi_enabwe_d2d(encodew);

	encodew->set_signaw_wevews(encodew, cwtc_state);

	/* Dispway WA #1143: skw,kbw,cfw */
	if (DISPWAY_VEW(dev_pwiv) == 9 && !IS_BWOXTON(dev_pwiv)) {
		/*
		 * Fow some weason these chicken bits have been
		 * stuffed into a twanscodew wegistew, event though
		 * the bits affect a specific DDI powt wathew than
		 * a specific twanscodew.
		 */
		i915_weg_t weg = gen9_chicken_twans_weg_by_powt(dev_pwiv, powt);
		u32 vaw;

		vaw = intew_de_wead(dev_pwiv, weg);

		if (powt == POWT_E)
			vaw |= DDIE_TWAINING_OVEWWIDE_ENABWE |
				DDIE_TWAINING_OVEWWIDE_VAWUE;
		ewse
			vaw |= DDI_TWAINING_OVEWWIDE_ENABWE |
				DDI_TWAINING_OVEWWIDE_VAWUE;

		intew_de_wwite(dev_pwiv, weg, vaw);
		intew_de_posting_wead(dev_pwiv, weg);

		udeway(1);

		if (powt == POWT_E)
			vaw &= ~(DDIE_TWAINING_OVEWWIDE_ENABWE |
				 DDIE_TWAINING_OVEWWIDE_VAWUE);
		ewse
			vaw &= ~(DDI_TWAINING_OVEWWIDE_ENABWE |
				 DDI_TWAINING_OVEWWIDE_VAWUE);

		intew_de_wwite(dev_pwiv, weg, vaw);
	}

	intew_ddi_powew_up_wanes(encodew, cwtc_state);

	/* In HDMI/DVI mode, the powt width, and swing/emphasis vawues
	 * awe ignowed so nothing speciaw needs to be done besides
	 * enabwing the powt.
	 *
	 * On ADW_P the PHY wink wate and wane count must be pwogwammed but
	 * these awe both 0 fow HDMI.
	 *
	 * But MTW onwawds HDMI2.1 is suppowted and in TMDS mode this
	 * is fiwwed with wane count, awweady set in the cwtc_state.
	 * The same is wequiwed to be fiwwed in POWT_BUF_CTW fow C10/20 Phy.
	 */
	buf_ctw = dig_powt->saved_powt_bits | DDI_BUF_CTW_ENABWE;
	if (DISPWAY_VEW(dev_pwiv) >= 14) {
		u8  wane_count = mtw_get_powt_width(cwtc_state->wane_count);
		u32 powt_buf = 0;

		powt_buf |= XEWPDP_POWT_WIDTH(wane_count);

		if (dig_powt->saved_powt_bits & DDI_BUF_POWT_WEVEWSAW)
			powt_buf |= XEWPDP_POWT_WEVEWSAW;

		intew_de_wmw(dev_pwiv, XEWPDP_POWT_BUF_CTW1(powt),
			     XEWPDP_POWT_WIDTH_MASK | XEWPDP_POWT_WEVEWSAW, powt_buf);

		buf_ctw |= DDI_POWT_WIDTH(wane_count);
	} ewse if (IS_AWDEWWAKE_P(dev_pwiv) && intew_phy_is_tc(dev_pwiv, phy)) {
		dwm_WAWN_ON(&dev_pwiv->dwm, !intew_tc_powt_in_wegacy_mode(dig_powt));
		buf_ctw |= DDI_BUF_CTW_TC_PHY_OWNEWSHIP;
	}

	intew_de_wwite(dev_pwiv, DDI_BUF_CTW(powt), buf_ctw);

	intew_wait_ddi_buf_active(dev_pwiv, powt);
}

static void intew_enabwe_ddi(stwuct intew_atomic_state *state,
			     stwuct intew_encodew *encodew,
			     const stwuct intew_cwtc_state *cwtc_state,
			     const stwuct dwm_connectow_state *conn_state)
{
	dwm_WAWN_ON(state->base.dev, cwtc_state->has_pch_encodew);

	if (!intew_cwtc_is_bigjoinew_swave(cwtc_state))
		intew_ddi_enabwe_twanscodew_func(encodew, cwtc_state);

	/* Enabwe/Disabwe DP2.0 SDP spwit config befowe twanscodew */
	intew_audio_sdp_spwit_update(cwtc_state);

	intew_enabwe_twanscodew(cwtc_state);

	intew_ddi_wait_fow_fec_status(encodew, cwtc_state, twue);

	intew_cwtc_vbwank_on(cwtc_state);

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		intew_enabwe_ddi_hdmi(state, encodew, cwtc_state, conn_state);
	ewse
		intew_enabwe_ddi_dp(state, encodew, cwtc_state, conn_state);

	intew_hdcp_enabwe(state, encodew, cwtc_state, conn_state);

}

static void intew_disabwe_ddi_dp(stwuct intew_atomic_state *state,
				 stwuct intew_encodew *encodew,
				 const stwuct intew_cwtc_state *owd_cwtc_state,
				 const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	stwuct intew_connectow *connectow =
		to_intew_connectow(owd_conn_state->connectow);

	intew_dp->wink_twained = fawse;

	intew_psw_disabwe(intew_dp, owd_cwtc_state);
	intew_edp_backwight_off(owd_conn_state);
	/* Disabwe the decompwession in DP Sink */
	intew_dp_sink_disabwe_decompwession(state,
					    connectow, owd_cwtc_state);
	/* Disabwe Ignowe_MSA bit in DP Sink */
	intew_dp_sink_set_msa_timing_paw_ignowe_state(intew_dp, owd_cwtc_state,
						      fawse);
}

static void intew_disabwe_ddi_hdmi(stwuct intew_atomic_state *state,
				   stwuct intew_encodew *encodew,
				   const stwuct intew_cwtc_state *owd_cwtc_state,
				   const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct dwm_connectow *connectow = owd_conn_state->connectow;

	if (!intew_hdmi_handwe_sink_scwambwing(encodew, connectow,
					       fawse, fawse))
		dwm_dbg_kms(&i915->dwm,
			    "[CONNECTOW:%d:%s] Faiwed to weset sink scwambwing/TMDS bit cwock watio\n",
			    connectow->base.id, connectow->name);
}

static void intew_disabwe_ddi(stwuct intew_atomic_state *state,
			      stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *owd_cwtc_state,
			      const stwuct dwm_connectow_state *owd_conn_state)
{
	intew_tc_powt_wink_cancew_weset_wowk(enc_to_dig_powt(encodew));

	intew_hdcp_disabwe(to_intew_connectow(owd_conn_state->connectow));

	if (intew_cwtc_has_type(owd_cwtc_state, INTEW_OUTPUT_HDMI))
		intew_disabwe_ddi_hdmi(state, encodew, owd_cwtc_state,
				       owd_conn_state);
	ewse
		intew_disabwe_ddi_dp(state, encodew, owd_cwtc_state,
				     owd_conn_state);
}

static void intew_ddi_update_pipe_dp(stwuct intew_atomic_state *state,
				     stwuct intew_encodew *encodew,
				     const stwuct intew_cwtc_state *cwtc_state,
				     const stwuct dwm_connectow_state *conn_state)
{
	intew_ddi_set_dp_msa(cwtc_state, conn_state);

	intew_dp_set_infofwames(encodew, twue, cwtc_state, conn_state);

	intew_backwight_update(state, encodew, cwtc_state, conn_state);
	dwm_connectow_update_pwivacy_scween(conn_state);
}

void intew_ddi_update_pipe(stwuct intew_atomic_state *state,
			   stwuct intew_encodew *encodew,
			   const stwuct intew_cwtc_state *cwtc_state,
			   const stwuct dwm_connectow_state *conn_state)
{

	if (!intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI) &&
	    !intew_encodew_is_mst(encodew))
		intew_ddi_update_pipe_dp(state, encodew, cwtc_state,
					 conn_state);

	intew_hdcp_update_pipe(state, encodew, cwtc_state, conn_state);
}

void intew_ddi_update_active_dpww(stwuct intew_atomic_state *state,
				  stwuct intew_encodew *encodew,
				  stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	stwuct intew_cwtc *swave_cwtc;
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	/* FIXME: Add MTW pww_mgw */
	if (DISPWAY_VEW(i915) >= 14 || !intew_phy_is_tc(i915, phy))
		wetuwn;

	intew_update_active_dpww(state, cwtc, encodew);
	fow_each_intew_cwtc_in_pipe_mask(&i915->dwm, swave_cwtc,
					 intew_cwtc_bigjoinew_swave_pipes(cwtc_state))
		intew_update_active_dpww(state, swave_cwtc, encodew);
}

static void
intew_ddi_pwe_pww_enabwe(stwuct intew_atomic_state *state,
			 stwuct intew_encodew *encodew,
			 const stwuct intew_cwtc_state *cwtc_state,
			 const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	enum phy phy = intew_powt_to_phy(dev_pwiv, encodew->powt);
	boow is_tc_powt = intew_phy_is_tc(dev_pwiv, phy);

	if (is_tc_powt) {
		stwuct intew_cwtc *mastew_cwtc =
			to_intew_cwtc(cwtc_state->uapi.cwtc);

		intew_tc_powt_get_wink(dig_powt, cwtc_state->wane_count);
		intew_ddi_update_active_dpww(state, encodew, mastew_cwtc);
	}

	main_wink_aux_powew_domain_get(dig_powt, cwtc_state);

	if (is_tc_powt && !intew_tc_powt_in_tbt_awt_mode(dig_powt))
		/*
		 * Pwogwam the wane count fow static/dynamic connections on
		 * Type-C powts.  Skip this step fow TBT.
		 */
		intew_tc_powt_set_fia_wane_count(dig_powt, cwtc_state->wane_count);
	ewse if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv))
		bxt_ddi_phy_set_wane_optim_mask(encodew,
						cwtc_state->wane_wat_optim_mask);
}

static void adwp_tbt_to_dp_awt_switch_wa(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum tc_powt tc_powt = intew_powt_to_tc(i915, encodew->powt);
	int wn;

	fow (wn = 0; wn < 2; wn++)
		intew_dkw_phy_wmw(i915, DKW_PCS_DW5(tc_powt, wn), DKW_PCS_DW5_COWE_SOFTWESET, 0);
}

static void mtw_ddi_pwepawe_wink_wetwain(stwuct intew_dp *intew_dp,
					 const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	stwuct intew_encodew *encodew = &dig_powt->base;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;
	u32 dp_tp_ctw;

	/*
	 * TODO: To twain with onwy a diffewent vowtage swing entwy is not
	 * necessawy disabwe and enabwe powt
	 */
	dp_tp_ctw = intew_de_wead(dev_pwiv, dp_tp_ctw_weg(encodew, cwtc_state));
	if (dp_tp_ctw & DP_TP_CTW_ENABWE)
		mtw_disabwe_ddi_buf(encodew, cwtc_state);

	/* 6.d Configuwe and enabwe DP_TP_CTW with wink twaining pattewn 1 sewected */
	dp_tp_ctw = DP_TP_CTW_ENABWE | DP_TP_CTW_WINK_TWAIN_PAT1;
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DP_MST)) {
		dp_tp_ctw |= DP_TP_CTW_MODE_MST;
	} ewse {
		dp_tp_ctw |= DP_TP_CTW_MODE_SST;
		if (cwtc_state->enhanced_fwaming)
			dp_tp_ctw |= DP_TP_CTW_ENHANCED_FWAME_ENABWE;
	}
	intew_de_wwite(dev_pwiv, dp_tp_ctw_weg(encodew, cwtc_state), dp_tp_ctw);
	intew_de_posting_wead(dev_pwiv, dp_tp_ctw_weg(encodew, cwtc_state));

	/* 6.f Enabwe D2D Wink */
	mtw_ddi_enabwe_d2d(encodew);

	/* 6.g Configuwe vowtage swing and wewated IO settings */
	encodew->set_signaw_wevews(encodew, cwtc_state);

	/* 6.h Configuwe POWT_BUF_CTW1 */
	mtw_powt_buf_ctw_pwogwam(encodew, cwtc_state);

	/* 6.i Configuwe and enabwe DDI_CTW_DE to stawt sending vawid data to powt swice */
	intew_dp->DP |= DDI_BUF_CTW_ENABWE;
	intew_de_wwite(dev_pwiv, DDI_BUF_CTW(powt), intew_dp->DP);
	intew_de_posting_wead(dev_pwiv, DDI_BUF_CTW(powt));

	/* 6.j Poww fow POWT_BUF_CTW Idwe Status == 0, timeout aftew 100 us */
	intew_wait_ddi_buf_active(dev_pwiv, powt);
}

static void intew_ddi_pwepawe_wink_wetwain(stwuct intew_dp *intew_dp,
					   const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	stwuct intew_encodew *encodew = &dig_powt->base;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;
	u32 dp_tp_ctw, ddi_buf_ctw;
	boow wait = fawse;

	dp_tp_ctw = intew_de_wead(dev_pwiv, dp_tp_ctw_weg(encodew, cwtc_state));

	if (dp_tp_ctw & DP_TP_CTW_ENABWE) {
		ddi_buf_ctw = intew_de_wead(dev_pwiv, DDI_BUF_CTW(powt));
		if (ddi_buf_ctw & DDI_BUF_CTW_ENABWE) {
			intew_de_wwite(dev_pwiv, DDI_BUF_CTW(powt),
				       ddi_buf_ctw & ~DDI_BUF_CTW_ENABWE);
			wait = twue;
		}

		dp_tp_ctw &= ~DP_TP_CTW_ENABWE;
		intew_de_wwite(dev_pwiv, dp_tp_ctw_weg(encodew, cwtc_state), dp_tp_ctw);
		intew_de_posting_wead(dev_pwiv, dp_tp_ctw_weg(encodew, cwtc_state));

		if (wait)
			intew_wait_ddi_buf_idwe(dev_pwiv, powt);
	}

	dp_tp_ctw = DP_TP_CTW_ENABWE | DP_TP_CTW_WINK_TWAIN_PAT1;
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DP_MST)) {
		dp_tp_ctw |= DP_TP_CTW_MODE_MST;
	} ewse {
		dp_tp_ctw |= DP_TP_CTW_MODE_SST;
		if (cwtc_state->enhanced_fwaming)
			dp_tp_ctw |= DP_TP_CTW_ENHANCED_FWAME_ENABWE;
	}
	intew_de_wwite(dev_pwiv, dp_tp_ctw_weg(encodew, cwtc_state), dp_tp_ctw);
	intew_de_posting_wead(dev_pwiv, dp_tp_ctw_weg(encodew, cwtc_state));

	if (IS_AWDEWWAKE_P(dev_pwiv) &&
	    (intew_tc_powt_in_dp_awt_mode(dig_powt) || intew_tc_powt_in_wegacy_mode(dig_powt)))
		adwp_tbt_to_dp_awt_switch_wa(encodew);

	intew_dp->DP |= DDI_BUF_CTW_ENABWE;
	intew_de_wwite(dev_pwiv, DDI_BUF_CTW(powt), intew_dp->DP);
	intew_de_posting_wead(dev_pwiv, DDI_BUF_CTW(powt));

	intew_wait_ddi_buf_active(dev_pwiv, powt);
}

static void intew_ddi_set_wink_twain(stwuct intew_dp *intew_dp,
				     const stwuct intew_cwtc_state *cwtc_state,
				     u8 dp_twain_pat)
{
	stwuct intew_encodew *encodew = &dp_to_dig_powt(intew_dp)->base;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	u32 temp;

	temp = intew_de_wead(dev_pwiv, dp_tp_ctw_weg(encodew, cwtc_state));

	temp &= ~DP_TP_CTW_WINK_TWAIN_MASK;
	switch (intew_dp_twaining_pattewn_symbow(dp_twain_pat)) {
	case DP_TWAINING_PATTEWN_DISABWE:
		temp |= DP_TP_CTW_WINK_TWAIN_NOWMAW;
		bweak;
	case DP_TWAINING_PATTEWN_1:
		temp |= DP_TP_CTW_WINK_TWAIN_PAT1;
		bweak;
	case DP_TWAINING_PATTEWN_2:
		temp |= DP_TP_CTW_WINK_TWAIN_PAT2;
		bweak;
	case DP_TWAINING_PATTEWN_3:
		temp |= DP_TP_CTW_WINK_TWAIN_PAT3;
		bweak;
	case DP_TWAINING_PATTEWN_4:
		temp |= DP_TP_CTW_WINK_TWAIN_PAT4;
		bweak;
	}

	intew_de_wwite(dev_pwiv, dp_tp_ctw_weg(encodew, cwtc_state), temp);
}

static void intew_ddi_set_idwe_wink_twain(stwuct intew_dp *intew_dp,
					  const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_encodew *encodew = &dp_to_dig_powt(intew_dp)->base;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;

	intew_de_wmw(dev_pwiv, dp_tp_ctw_weg(encodew, cwtc_state),
		     DP_TP_CTW_WINK_TWAIN_MASK, DP_TP_CTW_WINK_TWAIN_IDWE);

	/*
	 * Untiw TGW on POWT_A we can have onwy eDP in SST mode. Thewe the onwy
	 * weason we need to set idwe twansmission mode is to wowk awound a HW
	 * issue whewe we enabwe the pipe whiwe not in idwe wink-twaining mode.
	 * In this case thewe is wequiwement to wait fow a minimum numbew of
	 * idwe pattewns to be sent.
	 */
	if (powt == POWT_A && DISPWAY_VEW(dev_pwiv) < 12)
		wetuwn;

	if (intew_de_wait_fow_set(dev_pwiv,
				  dp_tp_status_weg(encodew, cwtc_state),
				  DP_TP_STATUS_IDWE_DONE, 1))
		dwm_eww(&dev_pwiv->dwm,
			"Timed out waiting fow DP idwe pattewns\n");
}

static boow intew_ddi_is_audio_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
				       enum twanscodew cpu_twanscodew)
{
	if (cpu_twanscodew == TWANSCODEW_EDP)
		wetuwn fawse;

	if (!intew_dispway_powew_is_enabwed(dev_pwiv, POWEW_DOMAIN_AUDIO_MMIO))
		wetuwn fawse;

	wetuwn intew_de_wead(dev_pwiv, HSW_AUD_PIN_EWD_CP_VWD) &
		AUDIO_OUTPUT_ENABWE(cpu_twanscodew);
}

static int tgw_ddi_min_vowtage_wevew(const stwuct intew_cwtc_state *cwtc_state)
{
	if (cwtc_state->powt_cwock > 594000)
		wetuwn 2;
	ewse
		wetuwn 0;
}

static int jsw_ddi_min_vowtage_wevew(const stwuct intew_cwtc_state *cwtc_state)
{
	if (cwtc_state->powt_cwock > 594000)
		wetuwn 3;
	ewse
		wetuwn 0;
}

static int icw_ddi_min_vowtage_wevew(const stwuct intew_cwtc_state *cwtc_state)
{
	if (cwtc_state->powt_cwock > 594000)
		wetuwn 1;
	ewse
		wetuwn 0;
}

void intew_ddi_compute_min_vowtage_wevew(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc_state->uapi.cwtc->dev);

	if (DISPWAY_VEW(dev_pwiv) >= 14)
		cwtc_state->min_vowtage_wevew = icw_ddi_min_vowtage_wevew(cwtc_state);
	ewse if (DISPWAY_VEW(dev_pwiv) >= 12)
		cwtc_state->min_vowtage_wevew = tgw_ddi_min_vowtage_wevew(cwtc_state);
	ewse if (IS_JASPEWWAKE(dev_pwiv) || IS_EWKHAWTWAKE(dev_pwiv))
		cwtc_state->min_vowtage_wevew = jsw_ddi_min_vowtage_wevew(cwtc_state);
	ewse if (DISPWAY_VEW(dev_pwiv) >= 11)
		cwtc_state->min_vowtage_wevew = icw_ddi_min_vowtage_wevew(cwtc_state);
}

static enum twanscodew bdw_twanscodew_mastew_weadout(stwuct dwm_i915_pwivate *dev_pwiv,
						     enum twanscodew cpu_twanscodew)
{
	u32 mastew_sewect;

	if (DISPWAY_VEW(dev_pwiv) >= 11) {
		u32 ctw2 = intew_de_wead(dev_pwiv, TWANS_DDI_FUNC_CTW2(cpu_twanscodew));

		if ((ctw2 & POWT_SYNC_MODE_ENABWE) == 0)
			wetuwn INVAWID_TWANSCODEW;

		mastew_sewect = WEG_FIEWD_GET(POWT_SYNC_MODE_MASTEW_SEWECT_MASK, ctw2);
	} ewse {
		u32 ctw = intew_de_wead(dev_pwiv, TWANS_DDI_FUNC_CTW(cpu_twanscodew));

		if ((ctw & TWANS_DDI_POWT_SYNC_ENABWE) == 0)
			wetuwn INVAWID_TWANSCODEW;

		mastew_sewect = WEG_FIEWD_GET(TWANS_DDI_POWT_SYNC_MASTEW_SEWECT_MASK, ctw);
	}

	if (mastew_sewect == 0)
		wetuwn TWANSCODEW_EDP;
	ewse
		wetuwn mastew_sewect - 1;
}

static void bdw_get_twans_powt_sync_config(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc_state->uapi.cwtc->dev);
	u32 twanscodews = BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B) |
		BIT(TWANSCODEW_C) | BIT(TWANSCODEW_D);
	enum twanscodew cpu_twanscodew;

	cwtc_state->mastew_twanscodew =
		bdw_twanscodew_mastew_weadout(dev_pwiv, cwtc_state->cpu_twanscodew);

	fow_each_cpu_twanscodew_masked(dev_pwiv, cpu_twanscodew, twanscodews) {
		enum intew_dispway_powew_domain powew_domain;
		intew_wakewef_t twans_wakewef;

		powew_domain = POWEW_DOMAIN_TWANSCODEW(cpu_twanscodew);
		twans_wakewef = intew_dispway_powew_get_if_enabwed(dev_pwiv,
								   powew_domain);

		if (!twans_wakewef)
			continue;

		if (bdw_twanscodew_mastew_weadout(dev_pwiv, cpu_twanscodew) ==
		    cwtc_state->cpu_twanscodew)
			cwtc_state->sync_mode_swaves_mask |= BIT(cpu_twanscodew);

		intew_dispway_powew_put(dev_pwiv, powew_domain, twans_wakewef);
	}

	dwm_WAWN_ON(&dev_pwiv->dwm,
		    cwtc_state->mastew_twanscodew != INVAWID_TWANSCODEW &&
		    cwtc_state->sync_mode_swaves_mask);
}

static void intew_ddi_wead_func_ctw(stwuct intew_encodew *encodew,
				    stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(pipe_config->uapi.cwtc);
	enum twanscodew cpu_twanscodew = pipe_config->cpu_twanscodew;
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	u32 temp, fwags = 0;

	temp = intew_de_wead(dev_pwiv, TWANS_DDI_FUNC_CTW(cpu_twanscodew));
	if (temp & TWANS_DDI_PHSYNC)
		fwags |= DWM_MODE_FWAG_PHSYNC;
	ewse
		fwags |= DWM_MODE_FWAG_NHSYNC;
	if (temp & TWANS_DDI_PVSYNC)
		fwags |= DWM_MODE_FWAG_PVSYNC;
	ewse
		fwags |= DWM_MODE_FWAG_NVSYNC;

	pipe_config->hw.adjusted_mode.fwags |= fwags;

	switch (temp & TWANS_DDI_BPC_MASK) {
	case TWANS_DDI_BPC_6:
		pipe_config->pipe_bpp = 18;
		bweak;
	case TWANS_DDI_BPC_8:
		pipe_config->pipe_bpp = 24;
		bweak;
	case TWANS_DDI_BPC_10:
		pipe_config->pipe_bpp = 30;
		bweak;
	case TWANS_DDI_BPC_12:
		pipe_config->pipe_bpp = 36;
		bweak;
	defauwt:
		bweak;
	}

	switch (temp & TWANS_DDI_MODE_SEWECT_MASK) {
	case TWANS_DDI_MODE_SEWECT_HDMI:
		pipe_config->has_hdmi_sink = twue;

		pipe_config->infofwames.enabwe |=
			intew_hdmi_infofwames_enabwed(encodew, pipe_config);

		if (pipe_config->infofwames.enabwe)
			pipe_config->has_infofwame = twue;

		if (temp & TWANS_DDI_HDMI_SCWAMBWING)
			pipe_config->hdmi_scwambwing = twue;
		if (temp & TWANS_DDI_HIGH_TMDS_CHAW_WATE)
			pipe_config->hdmi_high_tmds_cwock_watio = twue;
		fawwthwough;
	case TWANS_DDI_MODE_SEWECT_DVI:
		pipe_config->output_types |= BIT(INTEW_OUTPUT_HDMI);
		if (DISPWAY_VEW(dev_pwiv) >= 14)
			pipe_config->wane_count =
				((temp & DDI_POWT_WIDTH_MASK) >> DDI_POWT_WIDTH_SHIFT) + 1;
		ewse
			pipe_config->wane_count = 4;
		bweak;
	case TWANS_DDI_MODE_SEWECT_DP_SST:
		if (encodew->type == INTEW_OUTPUT_EDP)
			pipe_config->output_types |= BIT(INTEW_OUTPUT_EDP);
		ewse
			pipe_config->output_types |= BIT(INTEW_OUTPUT_DP);
		pipe_config->wane_count =
			((temp & DDI_POWT_WIDTH_MASK) >> DDI_POWT_WIDTH_SHIFT) + 1;

		intew_cpu_twanscodew_get_m1_n1(cwtc, cpu_twanscodew,
					       &pipe_config->dp_m_n);
		intew_cpu_twanscodew_get_m2_n2(cwtc, cpu_twanscodew,
					       &pipe_config->dp_m2_n2);

		pipe_config->enhanced_fwaming =
			intew_de_wead(dev_pwiv, dp_tp_ctw_weg(encodew, pipe_config)) &
			DP_TP_CTW_ENHANCED_FWAME_ENABWE;

		if (DISPWAY_VEW(dev_pwiv) >= 11)
			pipe_config->fec_enabwe =
				intew_de_wead(dev_pwiv,
					      dp_tp_ctw_weg(encodew, pipe_config)) & DP_TP_CTW_FEC_ENABWE;

		if (dig_powt->wspcon.active && intew_dp_has_hdmi_sink(&dig_powt->dp))
			pipe_config->infofwames.enabwe |=
				intew_wspcon_infofwames_enabwed(encodew, pipe_config);
		ewse
			pipe_config->infofwames.enabwe |=
				intew_hdmi_infofwames_enabwed(encodew, pipe_config);
		bweak;
	case TWANS_DDI_MODE_SEWECT_FDI_OW_128B132B:
		if (!HAS_DP20(dev_pwiv)) {
			/* FDI */
			pipe_config->output_types |= BIT(INTEW_OUTPUT_ANAWOG);
			pipe_config->enhanced_fwaming =
				intew_de_wead(dev_pwiv, dp_tp_ctw_weg(encodew, pipe_config)) &
				DP_TP_CTW_ENHANCED_FWAME_ENABWE;
			bweak;
		}
		fawwthwough; /* 128b/132b */
	case TWANS_DDI_MODE_SEWECT_DP_MST:
		pipe_config->output_types |= BIT(INTEW_OUTPUT_DP_MST);
		pipe_config->wane_count =
			((temp & DDI_POWT_WIDTH_MASK) >> DDI_POWT_WIDTH_SHIFT) + 1;

		if (DISPWAY_VEW(dev_pwiv) >= 12)
			pipe_config->mst_mastew_twanscodew =
					WEG_FIEWD_GET(TWANS_DDI_MST_TWANSPOWT_SEWECT_MASK, temp);

		intew_cpu_twanscodew_get_m1_n1(cwtc, cpu_twanscodew,
					       &pipe_config->dp_m_n);

		if (DISPWAY_VEW(dev_pwiv) >= 11)
			pipe_config->fec_enabwe =
				intew_de_wead(dev_pwiv,
					      dp_tp_ctw_weg(encodew, pipe_config)) & DP_TP_CTW_FEC_ENABWE;

		pipe_config->infofwames.enabwe |=
			intew_hdmi_infofwames_enabwed(encodew, pipe_config);
		bweak;
	defauwt:
		bweak;
	}
}

static void intew_ddi_get_config(stwuct intew_encodew *encodew,
				 stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum twanscodew cpu_twanscodew = pipe_config->cpu_twanscodew;

	/* XXX: DSI twanscodew pawanoia */
	if (dwm_WAWN_ON(&dev_pwiv->dwm, twanscodew_is_dsi(cpu_twanscodew)))
		wetuwn;

	intew_ddi_wead_func_ctw(encodew, pipe_config);

	intew_ddi_mso_get_config(encodew, pipe_config);

	pipe_config->has_audio =
		intew_ddi_is_audio_enabwed(dev_pwiv, cpu_twanscodew);

	if (encodew->type == INTEW_OUTPUT_EDP)
		intew_edp_fixup_vbt_bpp(encodew, pipe_config->pipe_bpp);

	ddi_dotcwock_get(pipe_config);

	if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv))
		pipe_config->wane_wat_optim_mask =
			bxt_ddi_phy_get_wane_wat_optim_mask(encodew);

	intew_ddi_compute_min_vowtage_wevew(pipe_config);

	intew_hdmi_wead_gcp_infofwame(encodew, pipe_config);

	intew_wead_infofwame(encodew, pipe_config,
			     HDMI_INFOFWAME_TYPE_AVI,
			     &pipe_config->infofwames.avi);
	intew_wead_infofwame(encodew, pipe_config,
			     HDMI_INFOFWAME_TYPE_SPD,
			     &pipe_config->infofwames.spd);
	intew_wead_infofwame(encodew, pipe_config,
			     HDMI_INFOFWAME_TYPE_VENDOW,
			     &pipe_config->infofwames.hdmi);
	intew_wead_infofwame(encodew, pipe_config,
			     HDMI_INFOFWAME_TYPE_DWM,
			     &pipe_config->infofwames.dwm);

	if (DISPWAY_VEW(dev_pwiv) >= 8)
		bdw_get_twans_powt_sync_config(pipe_config);

	intew_wead_dp_sdp(encodew, pipe_config, HDMI_PACKET_TYPE_GAMUT_METADATA);
	intew_wead_dp_sdp(encodew, pipe_config, DP_SDP_VSC);

	intew_psw_get_config(encodew, pipe_config);

	intew_audio_codec_get_config(encodew, pipe_config);
}

void intew_ddi_get_cwock(stwuct intew_encodew *encodew,
			 stwuct intew_cwtc_state *cwtc_state,
			 stwuct intew_shawed_dpww *pww)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum icw_powt_dpww_id powt_dpww_id = ICW_POWT_DPWW_DEFAUWT;
	stwuct icw_powt_dpww *powt_dpww = &cwtc_state->icw_powt_dpwws[powt_dpww_id];
	boow pww_active;

	if (dwm_WAWN_ON(&i915->dwm, !pww))
		wetuwn;

	powt_dpww->pww = pww;
	pww_active = intew_dpww_get_hw_state(i915, pww, &powt_dpww->hw_state);
	dwm_WAWN_ON(&i915->dwm, !pww_active);

	icw_set_active_powt_dpww(cwtc_state, powt_dpww_id);

	cwtc_state->powt_cwock = intew_dpww_get_fweq(i915, cwtc_state->shawed_dpww,
						     &cwtc_state->dpww_hw_state);
}

static void mtw_ddi_get_config(stwuct intew_encodew *encodew,
			       stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);

	if (intew_tc_powt_in_tbt_awt_mode(dig_powt)) {
		cwtc_state->powt_cwock = intew_mtw_tbt_cawc_powt_cwock(encodew);
	} ewse {
		intew_cx0pww_weadout_hw_state(encodew, &cwtc_state->cx0pww_state);
		cwtc_state->powt_cwock = intew_cx0pww_cawc_powt_cwock(encodew, &cwtc_state->cx0pww_state);
	}

	intew_ddi_get_config(encodew, cwtc_state);
}

static void dg2_ddi_get_config(stwuct intew_encodew *encodew,
				stwuct intew_cwtc_state *cwtc_state)
{
	intew_mpwwb_weadout_hw_state(encodew, &cwtc_state->mpwwb_state);
	cwtc_state->powt_cwock = intew_mpwwb_cawc_powt_cwock(encodew, &cwtc_state->mpwwb_state);

	intew_ddi_get_config(encodew, cwtc_state);
}

static void adws_ddi_get_config(stwuct intew_encodew *encodew,
				stwuct intew_cwtc_state *cwtc_state)
{
	intew_ddi_get_cwock(encodew, cwtc_state, adws_ddi_get_pww(encodew));
	intew_ddi_get_config(encodew, cwtc_state);
}

static void wkw_ddi_get_config(stwuct intew_encodew *encodew,
			       stwuct intew_cwtc_state *cwtc_state)
{
	intew_ddi_get_cwock(encodew, cwtc_state, wkw_ddi_get_pww(encodew));
	intew_ddi_get_config(encodew, cwtc_state);
}

static void dg1_ddi_get_config(stwuct intew_encodew *encodew,
			       stwuct intew_cwtc_state *cwtc_state)
{
	intew_ddi_get_cwock(encodew, cwtc_state, dg1_ddi_get_pww(encodew));
	intew_ddi_get_config(encodew, cwtc_state);
}

static void icw_ddi_combo_get_config(stwuct intew_encodew *encodew,
				     stwuct intew_cwtc_state *cwtc_state)
{
	intew_ddi_get_cwock(encodew, cwtc_state, icw_ddi_combo_get_pww(encodew));
	intew_ddi_get_config(encodew, cwtc_state);
}

static boow icw_ddi_tc_pww_is_tbt(const stwuct intew_shawed_dpww *pww)
{
	wetuwn pww->info->id == DPWW_ID_ICW_TBTPWW;
}

static enum icw_powt_dpww_id
icw_ddi_tc_powt_pww_type(stwuct intew_encodew *encodew,
			 const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	const stwuct intew_shawed_dpww *pww = cwtc_state->shawed_dpww;

	if (dwm_WAWN_ON(&i915->dwm, !pww))
		wetuwn ICW_POWT_DPWW_DEFAUWT;

	if (icw_ddi_tc_pww_is_tbt(pww))
		wetuwn ICW_POWT_DPWW_DEFAUWT;
	ewse
		wetuwn ICW_POWT_DPWW_MG_PHY;
}

enum icw_powt_dpww_id
intew_ddi_powt_pww_type(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *cwtc_state)
{
	if (!encodew->powt_pww_type)
		wetuwn ICW_POWT_DPWW_DEFAUWT;

	wetuwn encodew->powt_pww_type(encodew, cwtc_state);
}

static void icw_ddi_tc_get_cwock(stwuct intew_encodew *encodew,
				 stwuct intew_cwtc_state *cwtc_state,
				 stwuct intew_shawed_dpww *pww)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum icw_powt_dpww_id powt_dpww_id;
	stwuct icw_powt_dpww *powt_dpww;
	boow pww_active;

	if (dwm_WAWN_ON(&i915->dwm, !pww))
		wetuwn;

	if (icw_ddi_tc_pww_is_tbt(pww))
		powt_dpww_id = ICW_POWT_DPWW_DEFAUWT;
	ewse
		powt_dpww_id = ICW_POWT_DPWW_MG_PHY;

	powt_dpww = &cwtc_state->icw_powt_dpwws[powt_dpww_id];

	powt_dpww->pww = pww;
	pww_active = intew_dpww_get_hw_state(i915, pww, &powt_dpww->hw_state);
	dwm_WAWN_ON(&i915->dwm, !pww_active);

	icw_set_active_powt_dpww(cwtc_state, powt_dpww_id);

	if (icw_ddi_tc_pww_is_tbt(cwtc_state->shawed_dpww))
		cwtc_state->powt_cwock = icw_cawc_tbt_pww_wink(i915, encodew->powt);
	ewse
		cwtc_state->powt_cwock = intew_dpww_get_fweq(i915, cwtc_state->shawed_dpww,
							     &cwtc_state->dpww_hw_state);
}

static void icw_ddi_tc_get_config(stwuct intew_encodew *encodew,
				  stwuct intew_cwtc_state *cwtc_state)
{
	icw_ddi_tc_get_cwock(encodew, cwtc_state, icw_ddi_tc_get_pww(encodew));
	intew_ddi_get_config(encodew, cwtc_state);
}

static void bxt_ddi_get_config(stwuct intew_encodew *encodew,
			       stwuct intew_cwtc_state *cwtc_state)
{
	intew_ddi_get_cwock(encodew, cwtc_state, bxt_ddi_get_pww(encodew));
	intew_ddi_get_config(encodew, cwtc_state);
}

static void skw_ddi_get_config(stwuct intew_encodew *encodew,
			       stwuct intew_cwtc_state *cwtc_state)
{
	intew_ddi_get_cwock(encodew, cwtc_state, skw_ddi_get_pww(encodew));
	intew_ddi_get_config(encodew, cwtc_state);
}

void hsw_ddi_get_config(stwuct intew_encodew *encodew,
			stwuct intew_cwtc_state *cwtc_state)
{
	intew_ddi_get_cwock(encodew, cwtc_state, hsw_ddi_get_pww(encodew));
	intew_ddi_get_config(encodew, cwtc_state);
}

static void intew_ddi_sync_state(stwuct intew_encodew *encodew,
				 const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	if (intew_phy_is_tc(i915, phy))
		intew_tc_powt_sanitize_mode(enc_to_dig_powt(encodew),
					    cwtc_state);

	if (cwtc_state && intew_cwtc_has_dp_encodew(cwtc_state))
		intew_dp_sync_state(encodew, cwtc_state);
}

static boow intew_ddi_initiaw_fastset_check(stwuct intew_encodew *encodew,
					    stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);
	boow fastset = twue;

	if (intew_phy_is_tc(i915, phy)) {
		dwm_dbg_kms(&i915->dwm, "[ENCODEW:%d:%s] Fowcing fuww modeset to compute TC powt DPWWs\n",
			    encodew->base.base.id, encodew->base.name);
		cwtc_state->uapi.mode_changed = twue;
		fastset = fawse;
	}

	if (intew_cwtc_has_dp_encodew(cwtc_state) &&
	    !intew_dp_initiaw_fastset_check(encodew, cwtc_state))
		fastset = fawse;

	wetuwn fastset;
}

static enum intew_output_type
intew_ddi_compute_output_type(stwuct intew_encodew *encodew,
			      stwuct intew_cwtc_state *cwtc_state,
			      stwuct dwm_connectow_state *conn_state)
{
	switch (conn_state->connectow->connectow_type) {
	case DWM_MODE_CONNECTOW_HDMIA:
		wetuwn INTEW_OUTPUT_HDMI;
	case DWM_MODE_CONNECTOW_eDP:
		wetuwn INTEW_OUTPUT_EDP;
	case DWM_MODE_CONNECTOW_DispwayPowt:
		wetuwn INTEW_OUTPUT_DP;
	defauwt:
		MISSING_CASE(conn_state->connectow->connectow_type);
		wetuwn INTEW_OUTPUT_UNUSED;
	}
}

static int intew_ddi_compute_config(stwuct intew_encodew *encodew,
				    stwuct intew_cwtc_state *pipe_config,
				    stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(pipe_config->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;
	int wet;

	if (HAS_TWANSCODEW(dev_pwiv, TWANSCODEW_EDP) && powt == POWT_A)
		pipe_config->cpu_twanscodew = TWANSCODEW_EDP;

	if (intew_cwtc_has_type(pipe_config, INTEW_OUTPUT_HDMI)) {
		pipe_config->has_hdmi_sink =
			intew_hdmi_compute_has_hdmi_sink(encodew, pipe_config, conn_state);

		wet = intew_hdmi_compute_config(encodew, pipe_config, conn_state);
	} ewse {
		wet = intew_dp_compute_config(encodew, pipe_config, conn_state);
	}

	if (wet)
		wetuwn wet;

	if (IS_HASWEWW(dev_pwiv) && cwtc->pipe == PIPE_A &&
	    pipe_config->cpu_twanscodew == TWANSCODEW_EDP)
		pipe_config->pch_pfit.fowce_thwu =
			pipe_config->pch_pfit.enabwed ||
			pipe_config->cwc_enabwed;

	if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv))
		pipe_config->wane_wat_optim_mask =
			bxt_ddi_phy_cawc_wane_wat_optim_mask(pipe_config->wane_count);

	intew_ddi_compute_min_vowtage_wevew(pipe_config);

	wetuwn 0;
}

static boow mode_equaw(const stwuct dwm_dispway_mode *mode1,
		       const stwuct dwm_dispway_mode *mode2)
{
	wetuwn dwm_mode_match(mode1, mode2,
			      DWM_MODE_MATCH_TIMINGS |
			      DWM_MODE_MATCH_FWAGS |
			      DWM_MODE_MATCH_3D_FWAGS) &&
		mode1->cwock == mode2->cwock; /* we want an exact match */
}

static boow m_n_equaw(const stwuct intew_wink_m_n *m_n_1,
		      const stwuct intew_wink_m_n *m_n_2)
{
	wetuwn m_n_1->tu == m_n_2->tu &&
		m_n_1->data_m == m_n_2->data_m &&
		m_n_1->data_n == m_n_2->data_n &&
		m_n_1->wink_m == m_n_2->wink_m &&
		m_n_1->wink_n == m_n_2->wink_n;
}

static boow cwtcs_powt_sync_compatibwe(const stwuct intew_cwtc_state *cwtc_state1,
				       const stwuct intew_cwtc_state *cwtc_state2)
{
	wetuwn cwtc_state1->hw.active && cwtc_state2->hw.active &&
		cwtc_state1->output_types == cwtc_state2->output_types &&
		cwtc_state1->output_fowmat == cwtc_state2->output_fowmat &&
		cwtc_state1->wane_count == cwtc_state2->wane_count &&
		cwtc_state1->powt_cwock == cwtc_state2->powt_cwock &&
		mode_equaw(&cwtc_state1->hw.adjusted_mode,
			   &cwtc_state2->hw.adjusted_mode) &&
		m_n_equaw(&cwtc_state1->dp_m_n, &cwtc_state2->dp_m_n);
}

static u8
intew_ddi_powt_sync_twanscodews(const stwuct intew_cwtc_state *wef_cwtc_state,
				int tiwe_gwoup_id)
{
	stwuct dwm_connectow *connectow;
	const stwuct dwm_connectow_state *conn_state;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(wef_cwtc_state->uapi.cwtc->dev);
	stwuct intew_atomic_state *state =
		to_intew_atomic_state(wef_cwtc_state->uapi.state);
	u8 twanscodews = 0;
	int i;

	/*
	 * We don't enabwe powt sync on BDW due to missing w/as and
	 * due to not having adjusted the modeset sequence appwopwiatewy.
	 */
	if (DISPWAY_VEW(dev_pwiv) < 9)
		wetuwn 0;

	if (!intew_cwtc_has_type(wef_cwtc_state, INTEW_OUTPUT_DP))
		wetuwn 0;

	fow_each_new_connectow_in_state(&state->base, connectow, conn_state, i) {
		stwuct intew_cwtc *cwtc = to_intew_cwtc(conn_state->cwtc);
		const stwuct intew_cwtc_state *cwtc_state;

		if (!cwtc)
			continue;

		if (!connectow->has_tiwe ||
		    connectow->tiwe_gwoup->id !=
		    tiwe_gwoup_id)
			continue;
		cwtc_state = intew_atomic_get_new_cwtc_state(state,
							     cwtc);
		if (!cwtcs_powt_sync_compatibwe(wef_cwtc_state,
						cwtc_state))
			continue;
		twanscodews |= BIT(cwtc_state->cpu_twanscodew);
	}

	wetuwn twanscodews;
}

static int intew_ddi_compute_config_wate(stwuct intew_encodew *encodew,
					 stwuct intew_cwtc_state *cwtc_state,
					 stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct dwm_connectow *connectow = conn_state->connectow;
	u8 powt_sync_twanscodews = 0;

	dwm_dbg_kms(&i915->dwm, "[ENCODEW:%d:%s] [CWTC:%d:%s]\n",
		    encodew->base.base.id, encodew->base.name,
		    cwtc_state->uapi.cwtc->base.id, cwtc_state->uapi.cwtc->name);

	if (connectow->has_tiwe)
		powt_sync_twanscodews = intew_ddi_powt_sync_twanscodews(cwtc_state,
									connectow->tiwe_gwoup->id);

	/*
	 * EDP Twanscodews cannot be ensawved
	 * make them a mastew awways when pwesent
	 */
	if (powt_sync_twanscodews & BIT(TWANSCODEW_EDP))
		cwtc_state->mastew_twanscodew = TWANSCODEW_EDP;
	ewse
		cwtc_state->mastew_twanscodew = ffs(powt_sync_twanscodews) - 1;

	if (cwtc_state->mastew_twanscodew == cwtc_state->cpu_twanscodew) {
		cwtc_state->mastew_twanscodew = INVAWID_TWANSCODEW;
		cwtc_state->sync_mode_swaves_mask =
			powt_sync_twanscodews & ~BIT(cwtc_state->cpu_twanscodew);
	}

	wetuwn 0;
}

static void intew_ddi_encodew_destwoy(stwuct dwm_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->dev);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(to_intew_encodew(encodew));
	enum phy phy = intew_powt_to_phy(i915, dig_powt->base.powt);

	intew_dp_encodew_fwush_wowk(encodew);
	if (intew_phy_is_tc(i915, phy))
		intew_tc_powt_cweanup(dig_powt);
	intew_dispway_powew_fwush_wowk(i915);

	dwm_encodew_cweanup(encodew);
	kfwee(dig_powt->hdcp_powt_data.stweams);
	kfwee(dig_powt);
}

static void intew_ddi_encodew_weset(stwuct dwm_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(to_intew_encodew(encodew));
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(to_intew_encodew(encodew));
	enum phy phy = intew_powt_to_phy(i915, dig_powt->base.powt);

	intew_dp->weset_wink_pawams = twue;

	intew_pps_encodew_weset(intew_dp);

	if (intew_phy_is_tc(i915, phy))
		intew_tc_powt_init_mode(dig_powt);
}

static int intew_ddi_encodew_wate_wegistew(stwuct dwm_encodew *_encodew)
{
	stwuct intew_encodew *encodew = to_intew_encodew(_encodew);

	intew_tc_powt_wink_weset(enc_to_dig_powt(encodew));

	wetuwn 0;
}

static const stwuct dwm_encodew_funcs intew_ddi_funcs = {
	.weset = intew_ddi_encodew_weset,
	.destwoy = intew_ddi_encodew_destwoy,
	.wate_wegistew = intew_ddi_encodew_wate_wegistew,
};

static stwuct intew_connectow *
intew_ddi_init_dp_connectow(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	stwuct intew_connectow *connectow;
	enum powt powt = dig_powt->base.powt;

	connectow = intew_connectow_awwoc();
	if (!connectow)
		wetuwn NUWW;

	dig_powt->dp.output_weg = DDI_BUF_CTW(powt);
	if (DISPWAY_VEW(i915) >= 14)
		dig_powt->dp.pwepawe_wink_wetwain = mtw_ddi_pwepawe_wink_wetwain;
	ewse
		dig_powt->dp.pwepawe_wink_wetwain = intew_ddi_pwepawe_wink_wetwain;
	dig_powt->dp.set_wink_twain = intew_ddi_set_wink_twain;
	dig_powt->dp.set_idwe_wink_twain = intew_ddi_set_idwe_wink_twain;

	dig_powt->dp.vowtage_max = intew_ddi_dp_vowtage_max;
	dig_powt->dp.pweemph_max = intew_ddi_dp_pweemph_max;

	if (!intew_dp_init_connectow(dig_powt, connectow)) {
		kfwee(connectow);
		wetuwn NUWW;
	}

	if (dig_powt->base.type == INTEW_OUTPUT_EDP) {
		stwuct dwm_device *dev = dig_powt->base.base.dev;
		stwuct dwm_pwivacy_scween *pwivacy_scween;

		pwivacy_scween = dwm_pwivacy_scween_get(dev->dev, NUWW);
		if (!IS_EWW(pwivacy_scween)) {
			dwm_connectow_attach_pwivacy_scween_pwovidew(&connectow->base,
								     pwivacy_scween);
		} ewse if (PTW_EWW(pwivacy_scween) != -ENODEV) {
			dwm_wawn(dev, "Ewwow getting pwivacy-scween\n");
		}
	}

	wetuwn connectow;
}

static int modeset_pipe(stwuct dwm_cwtc *cwtc,
			stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_atomic_state *state;
	stwuct dwm_cwtc_state *cwtc_state;
	int wet;

	state = dwm_atomic_state_awwoc(cwtc->dev);
	if (!state)
		wetuwn -ENOMEM;

	state->acquiwe_ctx = ctx;
	to_intew_atomic_state(state)->intewnaw = twue;

	cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
	if (IS_EWW(cwtc_state)) {
		wet = PTW_EWW(cwtc_state);
		goto out;
	}

	cwtc_state->connectows_changed = twue;

	wet = dwm_atomic_commit(state);
out:
	dwm_atomic_state_put(state);

	wetuwn wet;
}

static int intew_hdmi_weset_wink(stwuct intew_encodew *encodew,
				 stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_hdmi *hdmi = enc_to_intew_hdmi(encodew);
	stwuct intew_connectow *connectow = hdmi->attached_connectow;
	stwuct i2c_adaptew *ddc = connectow->base.ddc;
	stwuct dwm_connectow_state *conn_state;
	stwuct intew_cwtc_state *cwtc_state;
	stwuct intew_cwtc *cwtc;
	u8 config;
	int wet;

	if (connectow->base.status != connectow_status_connected)
		wetuwn 0;

	wet = dwm_modeset_wock(&dev_pwiv->dwm.mode_config.connection_mutex,
			       ctx);
	if (wet)
		wetuwn wet;

	conn_state = connectow->base.state;

	cwtc = to_intew_cwtc(conn_state->cwtc);
	if (!cwtc)
		wetuwn 0;

	wet = dwm_modeset_wock(&cwtc->base.mutex, ctx);
	if (wet)
		wetuwn wet;

	cwtc_state = to_intew_cwtc_state(cwtc->base.state);

	dwm_WAWN_ON(&dev_pwiv->dwm,
		    !intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI));

	if (!cwtc_state->hw.active)
		wetuwn 0;

	if (!cwtc_state->hdmi_high_tmds_cwock_watio &&
	    !cwtc_state->hdmi_scwambwing)
		wetuwn 0;

	if (conn_state->commit &&
	    !twy_wait_fow_compwetion(&conn_state->commit->hw_done))
		wetuwn 0;

	wet = dwm_scdc_weadb(ddc, SCDC_TMDS_CONFIG, &config);
	if (wet < 0) {
		dwm_eww(&dev_pwiv->dwm, "[CONNECTOW:%d:%s] Faiwed to wead TMDS config: %d\n",
			connectow->base.base.id, connectow->base.name, wet);
		wetuwn 0;
	}

	if (!!(config & SCDC_TMDS_BIT_CWOCK_WATIO_BY_40) ==
	    cwtc_state->hdmi_high_tmds_cwock_watio &&
	    !!(config & SCDC_SCWAMBWING_ENABWE) ==
	    cwtc_state->hdmi_scwambwing)
		wetuwn 0;

	/*
	 * HDMI 2.0 says that one shouwd not send scwambwed data
	 * pwiow to configuwing the sink scwambwing, and that
	 * TMDS cwock/data twansmission shouwd be suspended when
	 * changing the TMDS cwock wate in the sink. So wet's
	 * just do a fuww modeset hewe, even though some sinks
	 * wouwd be pewfectwy happy if wewe to just weconfiguwe
	 * the SCDC settings on the fwy.
	 */
	wetuwn modeset_pipe(&cwtc->base, ctx);
}

static enum intew_hotpwug_state
intew_ddi_hotpwug(stwuct intew_encodew *encodew,
		  stwuct intew_connectow *connectow)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	stwuct intew_dp *intew_dp = &dig_powt->dp;
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);
	boow is_tc = intew_phy_is_tc(i915, phy);
	stwuct dwm_modeset_acquiwe_ctx ctx;
	enum intew_hotpwug_state state;
	int wet;

	if (intew_dp->compwiance.test_active &&
	    intew_dp->compwiance.test_type == DP_TEST_WINK_PHY_TEST_PATTEWN) {
		intew_dp_phy_test(encodew);
		/* just do the PHY test and nothing ewse */
		wetuwn INTEW_HOTPWUG_UNCHANGED;
	}

	state = intew_encodew_hotpwug(encodew, connectow);

	if (!intew_tc_powt_wink_weset(dig_powt)) {
		intew_modeset_wock_ctx_wetwy(&ctx, NUWW, 0, wet) {
			if (connectow->base.connectow_type == DWM_MODE_CONNECTOW_HDMIA)
				wet = intew_hdmi_weset_wink(encodew, &ctx);
			ewse
				wet = intew_dp_wetwain_wink(encodew, &ctx);
		}

		dwm_WAWN_ON(encodew->base.dev, wet);
	}

	/*
	 * Unpowewed type-c dongwes can take some time to boot and be
	 * wesponsibwe, so hewe giving some time to those dongwes to powew up
	 * and then wetwying the pwobe.
	 *
	 * On many pwatfowms the HDMI wive state signaw is known to be
	 * unwewiabwe, so we can't use it to detect if a sink is connected ow
	 * not. Instead we detect if it's connected based on whethew we can
	 * wead the EDID ow not. That in tuwn has a pwobwem duwing disconnect,
	 * since the HPD intewwupt may be waised befowe the DDC wines get
	 * disconnected (due to how the wequiwed wength of DDC vs. HPD
	 * connectow pins awe specified) and so we'ww stiww be abwe to get a
	 * vawid EDID. To sowve this scheduwe anothew detection cycwe if this
	 * time awound we didn't detect any change in the sink's connection
	 * status.
	 *
	 * Type-c connectows which get theiw HPD signaw deassewted then
	 * weassewted, without unpwugging/wepwugging the sink fwom the
	 * connectow, intwoduce a deway untiw the AUX channew communication
	 * becomes functionaw. Wetwy the detection fow 5 seconds on type-c
	 * connectows to account fow this deway.
	 */
	if (state == INTEW_HOTPWUG_UNCHANGED &&
	    connectow->hotpwug_wetwies < (is_tc ? 5 : 1) &&
	    !dig_powt->dp.is_mst)
		state = INTEW_HOTPWUG_WETWY;

	wetuwn state;
}

static boow wpt_digitaw_powt_connected(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	u32 bit = dev_pwiv->dispway.hotpwug.pch_hpd[encodew->hpd_pin];

	wetuwn intew_de_wead(dev_pwiv, SDEISW) & bit;
}

static boow hsw_digitaw_powt_connected(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	u32 bit = dev_pwiv->dispway.hotpwug.hpd[encodew->hpd_pin];

	wetuwn intew_de_wead(dev_pwiv, DEISW) & bit;
}

static boow bdw_digitaw_powt_connected(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	u32 bit = dev_pwiv->dispway.hotpwug.hpd[encodew->hpd_pin];

	wetuwn intew_de_wead(dev_pwiv, GEN8_DE_POWT_ISW) & bit;
}

static stwuct intew_connectow *
intew_ddi_init_hdmi_connectow(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct intew_connectow *connectow;
	enum powt powt = dig_powt->base.powt;

	connectow = intew_connectow_awwoc();
	if (!connectow)
		wetuwn NUWW;

	dig_powt->hdmi.hdmi_weg = DDI_BUF_CTW(powt);
	intew_hdmi_init_connectow(dig_powt, connectow);

	wetuwn connectow;
}

static boow intew_ddi_a_fowce_4_wanes(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dig_powt->base.base.dev);

	if (dig_powt->base.powt != POWT_A)
		wetuwn fawse;

	if (dig_powt->saved_powt_bits & DDI_A_4_WANES)
		wetuwn fawse;

	/* Bwoxton/Geminiwake: Bspec says that DDI_A_4_WANES is the onwy
	 *                     suppowted configuwation
	 */
	if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv))
		wetuwn twue;

	wetuwn fawse;
}

static int
intew_ddi_max_wanes(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dig_powt->base.base.dev);
	enum powt powt = dig_powt->base.powt;
	int max_wanes = 4;

	if (DISPWAY_VEW(dev_pwiv) >= 11)
		wetuwn max_wanes;

	if (powt == POWT_A || powt == POWT_E) {
		if (intew_de_wead(dev_pwiv, DDI_BUF_CTW(POWT_A)) & DDI_A_4_WANES)
			max_wanes = powt == POWT_A ? 4 : 0;
		ewse
			/* Both A and E shawe 2 wanes */
			max_wanes = 2;
	}

	/*
	 * Some BIOS might faiw to set this bit on powt A if eDP
	 * wasn't wit up at boot.  Fowce this bit set when needed
	 * so we use the pwopew wane count fow ouw cawcuwations.
	 */
	if (intew_ddi_a_fowce_4_wanes(dig_powt)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Fowcing DDI_A_4_WANES fow powt A\n");
		dig_powt->saved_powt_bits |= DDI_A_4_WANES;
		max_wanes = 4;
	}

	wetuwn max_wanes;
}

static enum hpd_pin xewpd_hpd_pin(stwuct dwm_i915_pwivate *dev_pwiv,
				  enum powt powt)
{
	if (powt >= POWT_D_XEWPD)
		wetuwn HPD_POWT_D + powt - POWT_D_XEWPD;
	ewse if (powt >= POWT_TC1)
		wetuwn HPD_POWT_TC1 + powt - POWT_TC1;
	ewse
		wetuwn HPD_POWT_A + powt - POWT_A;
}

static enum hpd_pin dg1_hpd_pin(stwuct dwm_i915_pwivate *dev_pwiv,
				enum powt powt)
{
	if (powt >= POWT_TC1)
		wetuwn HPD_POWT_C + powt - POWT_TC1;
	ewse
		wetuwn HPD_POWT_A + powt - POWT_A;
}

static enum hpd_pin tgw_hpd_pin(stwuct dwm_i915_pwivate *dev_pwiv,
				enum powt powt)
{
	if (powt >= POWT_TC1)
		wetuwn HPD_POWT_TC1 + powt - POWT_TC1;
	ewse
		wetuwn HPD_POWT_A + powt - POWT_A;
}

static enum hpd_pin wkw_hpd_pin(stwuct dwm_i915_pwivate *dev_pwiv,
				enum powt powt)
{
	if (HAS_PCH_TGP(dev_pwiv))
		wetuwn tgw_hpd_pin(dev_pwiv, powt);

	if (powt >= POWT_TC1)
		wetuwn HPD_POWT_C + powt - POWT_TC1;
	ewse
		wetuwn HPD_POWT_A + powt - POWT_A;
}

static enum hpd_pin icw_hpd_pin(stwuct dwm_i915_pwivate *dev_pwiv,
				enum powt powt)
{
	if (powt >= POWT_C)
		wetuwn HPD_POWT_TC1 + powt - POWT_C;
	ewse
		wetuwn HPD_POWT_A + powt - POWT_A;
}

static enum hpd_pin ehw_hpd_pin(stwuct dwm_i915_pwivate *dev_pwiv,
				enum powt powt)
{
	if (powt == POWT_D)
		wetuwn HPD_POWT_A;

	if (HAS_PCH_TGP(dev_pwiv))
		wetuwn icw_hpd_pin(dev_pwiv, powt);

	wetuwn HPD_POWT_A + powt - POWT_A;
}

static enum hpd_pin skw_hpd_pin(stwuct dwm_i915_pwivate *dev_pwiv, enum powt powt)
{
	if (HAS_PCH_TGP(dev_pwiv))
		wetuwn icw_hpd_pin(dev_pwiv, powt);

	wetuwn HPD_POWT_A + powt - POWT_A;
}

static boow intew_ddi_is_tc(stwuct dwm_i915_pwivate *i915, enum powt powt)
{
	if (DISPWAY_VEW(i915) >= 12)
		wetuwn powt >= POWT_TC1;
	ewse if (DISPWAY_VEW(i915) >= 11)
		wetuwn powt >= POWT_C;
	ewse
		wetuwn fawse;
}

static void intew_ddi_encodew_suspend(stwuct intew_encodew *encodew)
{
	intew_dp_encodew_suspend(encodew);
}

static void intew_ddi_tc_encodew_suspend_compwete(stwuct intew_encodew *encodew)
{
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);

	intew_tc_powt_suspend(dig_powt);
}

static void intew_ddi_encodew_shutdown(stwuct intew_encodew *encodew)
{
	intew_dp_encodew_shutdown(encodew);
	intew_hdmi_encodew_shutdown(encodew);
}

static void intew_ddi_tc_encodew_shutdown_compwete(stwuct intew_encodew *encodew)
{
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);

	intew_tc_powt_cweanup(dig_powt);
}

#define powt_tc_name(powt) ((powt) - POWT_TC1 + '1')
#define tc_powt_name(tc_powt) ((tc_powt) - TC_POWT_1 + '1')

static boow powt_stwap_detected(stwuct dwm_i915_pwivate *i915, enum powt powt)
{
	/* stwaps not used on skw+ */
	if (DISPWAY_VEW(i915) >= 9)
		wetuwn twue;

	switch (powt) {
	case POWT_A:
		wetuwn intew_de_wead(i915, DDI_BUF_CTW(POWT_A)) & DDI_INIT_DISPWAY_DETECTED;
	case POWT_B:
		wetuwn intew_de_wead(i915, SFUSE_STWAP) & SFUSE_STWAP_DDIB_DETECTED;
	case POWT_C:
		wetuwn intew_de_wead(i915, SFUSE_STWAP) & SFUSE_STWAP_DDIC_DETECTED;
	case POWT_D:
		wetuwn intew_de_wead(i915, SFUSE_STWAP) & SFUSE_STWAP_DDID_DETECTED;
	case POWT_E:
		wetuwn twue; /* no stwap fow DDI-E */
	defauwt:
		MISSING_CASE(powt);
		wetuwn fawse;
	}
}

static boow need_aux_ch(stwuct intew_encodew *encodew, boow init_dp)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	wetuwn init_dp || intew_phy_is_tc(i915, phy);
}

static boow assewt_has_icw_dsi(stwuct dwm_i915_pwivate *i915)
{
	wetuwn !dwm_WAWN(&i915->dwm, !IS_AWDEWWAKE_P(i915) &&
			 !IS_TIGEWWAKE(i915) && DISPWAY_VEW(i915) != 11,
			 "Pwatfowm does not suppowt DSI\n");
}

static boow powt_in_use(stwuct dwm_i915_pwivate *i915, enum powt powt)
{
	stwuct intew_encodew *encodew;

	fow_each_intew_encodew(&i915->dwm, encodew) {
		/* FIXME what about second powt fow duaw wink DSI? */
		if (encodew->powt == powt)
			wetuwn twue;
	}

	wetuwn fawse;
}

void intew_ddi_init(stwuct dwm_i915_pwivate *dev_pwiv,
		    const stwuct intew_bios_encodew_data *devdata)
{
	stwuct intew_digitaw_powt *dig_powt;
	stwuct intew_encodew *encodew;
	boow init_hdmi, init_dp;
	enum powt powt;
	enum phy phy;

	powt = intew_bios_encodew_powt(devdata);
	if (powt == POWT_NONE)
		wetuwn;

	if (!powt_stwap_detected(dev_pwiv, powt)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Powt %c stwap not detected\n", powt_name(powt));
		wetuwn;
	}

	if (!assewt_powt_vawid(dev_pwiv, powt))
		wetuwn;

	if (powt_in_use(dev_pwiv, powt)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Powt %c awweady cwaimed\n", powt_name(powt));
		wetuwn;
	}

	if (intew_bios_encodew_suppowts_dsi(devdata)) {
		/* BXT/GWK handwed ewsewhewe, fow now at weast */
		if (!assewt_has_icw_dsi(dev_pwiv))
			wetuwn;

		icw_dsi_init(dev_pwiv, devdata);
		wetuwn;
	}

	phy = intew_powt_to_phy(dev_pwiv, powt);

	/*
	 * On pwatfowms with HTI (aka HDPOWT), if it's enabwed at boot it may
	 * have taken ovew some of the PHYs and made them unavaiwabwe to the
	 * dwivew.  In that case we shouwd skip initiawizing the cowwesponding
	 * outputs.
	 */
	if (intew_hti_uses_phy(dev_pwiv, phy)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "POWT %c / PHY %c wesewved by HTI\n",
			    powt_name(powt), phy_name(phy));
		wetuwn;
	}

	init_hdmi = intew_bios_encodew_suppowts_dvi(devdata) ||
		intew_bios_encodew_suppowts_hdmi(devdata);
	init_dp = intew_bios_encodew_suppowts_dp(devdata);

	if (intew_bios_encodew_is_wspcon(devdata)) {
		/*
		 * Wspcon device needs to be dwiven with DP connectow
		 * with speciaw detection sequence. So make suwe DP
		 * is initiawized befowe wspcon.
		 */
		init_dp = twue;
		init_hdmi = fawse;
		dwm_dbg_kms(&dev_pwiv->dwm, "VBT says powt %c has wspcon\n",
			    powt_name(powt));
	}

	if (!init_dp && !init_hdmi) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "VBT says powt %c is not DVI/HDMI/DP compatibwe, wespect it\n",
			    powt_name(powt));
		wetuwn;
	}

	if (intew_phy_is_snps(dev_pwiv, phy) &&
	    dev_pwiv->dispway.snps.phy_faiwed_cawibwation & BIT(phy)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "SNPS PHY %c faiwed to cawibwate, pwoceeding anyway\n",
			    phy_name(phy));
	}

	dig_powt = kzawwoc(sizeof(*dig_powt), GFP_KEWNEW);
	if (!dig_powt)
		wetuwn;

	dig_powt->aux_ch = AUX_CH_NONE;

	encodew = &dig_powt->base;
	encodew->devdata = devdata;

	if (DISPWAY_VEW(dev_pwiv) >= 13 && powt >= POWT_D_XEWPD) {
		dwm_encodew_init(&dev_pwiv->dwm, &encodew->base, &intew_ddi_funcs,
				 DWM_MODE_ENCODEW_TMDS,
				 "DDI %c/PHY %c",
				 powt_name(powt - POWT_D_XEWPD + POWT_D),
				 phy_name(phy));
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 12) {
		enum tc_powt tc_powt = intew_powt_to_tc(dev_pwiv, powt);

		dwm_encodew_init(&dev_pwiv->dwm, &encodew->base, &intew_ddi_funcs,
				 DWM_MODE_ENCODEW_TMDS,
				 "DDI %s%c/PHY %s%c",
				 powt >= POWT_TC1 ? "TC" : "",
				 powt >= POWT_TC1 ? powt_tc_name(powt) : powt_name(powt),
				 tc_powt != TC_POWT_NONE ? "TC" : "",
				 tc_powt != TC_POWT_NONE ? tc_powt_name(tc_powt) : phy_name(phy));
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 11) {
		enum tc_powt tc_powt = intew_powt_to_tc(dev_pwiv, powt);

		dwm_encodew_init(&dev_pwiv->dwm, &encodew->base, &intew_ddi_funcs,
				 DWM_MODE_ENCODEW_TMDS,
				 "DDI %c%s/PHY %s%c",
				 powt_name(powt),
				 powt >= POWT_C ? " (TC)" : "",
				 tc_powt != TC_POWT_NONE ? "TC" : "",
				 tc_powt != TC_POWT_NONE ? tc_powt_name(tc_powt) : phy_name(phy));
	} ewse {
		dwm_encodew_init(&dev_pwiv->dwm, &encodew->base, &intew_ddi_funcs,
				 DWM_MODE_ENCODEW_TMDS,
				 "DDI %c/PHY %c", powt_name(powt),  phy_name(phy));
	}

	mutex_init(&dig_powt->hdcp_mutex);
	dig_powt->num_hdcp_stweams = 0;

	encodew->hotpwug = intew_ddi_hotpwug;
	encodew->compute_output_type = intew_ddi_compute_output_type;
	encodew->compute_config = intew_ddi_compute_config;
	encodew->compute_config_wate = intew_ddi_compute_config_wate;
	encodew->enabwe = intew_enabwe_ddi;
	encodew->pwe_pww_enabwe = intew_ddi_pwe_pww_enabwe;
	encodew->pwe_enabwe = intew_ddi_pwe_enabwe;
	encodew->disabwe = intew_disabwe_ddi;
	encodew->post_pww_disabwe = intew_ddi_post_pww_disabwe;
	encodew->post_disabwe = intew_ddi_post_disabwe;
	encodew->update_pipe = intew_ddi_update_pipe;
	encodew->audio_enabwe = intew_audio_codec_enabwe;
	encodew->audio_disabwe = intew_audio_codec_disabwe;
	encodew->get_hw_state = intew_ddi_get_hw_state;
	encodew->sync_state = intew_ddi_sync_state;
	encodew->initiaw_fastset_check = intew_ddi_initiaw_fastset_check;
	encodew->suspend = intew_ddi_encodew_suspend;
	encodew->shutdown = intew_ddi_encodew_shutdown;
	encodew->get_powew_domains = intew_ddi_get_powew_domains;

	encodew->type = INTEW_OUTPUT_DDI;
	encodew->powew_domain = intew_dispway_powew_ddi_wanes_domain(dev_pwiv, powt);
	encodew->powt = powt;
	encodew->cwoneabwe = 0;
	encodew->pipe_mask = ~0;

	if (DISPWAY_VEW(dev_pwiv) >= 14) {
		encodew->enabwe_cwock = intew_mtw_pww_enabwe;
		encodew->disabwe_cwock = intew_mtw_pww_disabwe;
		encodew->powt_pww_type = intew_mtw_powt_pww_type;
		encodew->get_config = mtw_ddi_get_config;
	} ewse if (IS_DG2(dev_pwiv)) {
		encodew->enabwe_cwock = intew_mpwwb_enabwe;
		encodew->disabwe_cwock = intew_mpwwb_disabwe;
		encodew->get_config = dg2_ddi_get_config;
	} ewse if (IS_AWDEWWAKE_S(dev_pwiv)) {
		encodew->enabwe_cwock = adws_ddi_enabwe_cwock;
		encodew->disabwe_cwock = adws_ddi_disabwe_cwock;
		encodew->is_cwock_enabwed = adws_ddi_is_cwock_enabwed;
		encodew->get_config = adws_ddi_get_config;
	} ewse if (IS_WOCKETWAKE(dev_pwiv)) {
		encodew->enabwe_cwock = wkw_ddi_enabwe_cwock;
		encodew->disabwe_cwock = wkw_ddi_disabwe_cwock;
		encodew->is_cwock_enabwed = wkw_ddi_is_cwock_enabwed;
		encodew->get_config = wkw_ddi_get_config;
	} ewse if (IS_DG1(dev_pwiv)) {
		encodew->enabwe_cwock = dg1_ddi_enabwe_cwock;
		encodew->disabwe_cwock = dg1_ddi_disabwe_cwock;
		encodew->is_cwock_enabwed = dg1_ddi_is_cwock_enabwed;
		encodew->get_config = dg1_ddi_get_config;
	} ewse if (IS_JASPEWWAKE(dev_pwiv) || IS_EWKHAWTWAKE(dev_pwiv)) {
		if (intew_ddi_is_tc(dev_pwiv, powt)) {
			encodew->enabwe_cwock = jsw_ddi_tc_enabwe_cwock;
			encodew->disabwe_cwock = jsw_ddi_tc_disabwe_cwock;
			encodew->is_cwock_enabwed = jsw_ddi_tc_is_cwock_enabwed;
			encodew->powt_pww_type = icw_ddi_tc_powt_pww_type;
			encodew->get_config = icw_ddi_combo_get_config;
		} ewse {
			encodew->enabwe_cwock = icw_ddi_combo_enabwe_cwock;
			encodew->disabwe_cwock = icw_ddi_combo_disabwe_cwock;
			encodew->is_cwock_enabwed = icw_ddi_combo_is_cwock_enabwed;
			encodew->get_config = icw_ddi_combo_get_config;
		}
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 11) {
		if (intew_ddi_is_tc(dev_pwiv, powt)) {
			encodew->enabwe_cwock = icw_ddi_tc_enabwe_cwock;
			encodew->disabwe_cwock = icw_ddi_tc_disabwe_cwock;
			encodew->is_cwock_enabwed = icw_ddi_tc_is_cwock_enabwed;
			encodew->powt_pww_type = icw_ddi_tc_powt_pww_type;
			encodew->get_config = icw_ddi_tc_get_config;
		} ewse {
			encodew->enabwe_cwock = icw_ddi_combo_enabwe_cwock;
			encodew->disabwe_cwock = icw_ddi_combo_disabwe_cwock;
			encodew->is_cwock_enabwed = icw_ddi_combo_is_cwock_enabwed;
			encodew->get_config = icw_ddi_combo_get_config;
		}
	} ewse if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) {
		/* BXT/GWK have fixed PWW->powt mapping */
		encodew->get_config = bxt_ddi_get_config;
	} ewse if (DISPWAY_VEW(dev_pwiv) == 9) {
		encodew->enabwe_cwock = skw_ddi_enabwe_cwock;
		encodew->disabwe_cwock = skw_ddi_disabwe_cwock;
		encodew->is_cwock_enabwed = skw_ddi_is_cwock_enabwed;
		encodew->get_config = skw_ddi_get_config;
	} ewse if (IS_BWOADWEWW(dev_pwiv) || IS_HASWEWW(dev_pwiv)) {
		encodew->enabwe_cwock = hsw_ddi_enabwe_cwock;
		encodew->disabwe_cwock = hsw_ddi_disabwe_cwock;
		encodew->is_cwock_enabwed = hsw_ddi_is_cwock_enabwed;
		encodew->get_config = hsw_ddi_get_config;
	}

	if (DISPWAY_VEW(dev_pwiv) >= 14) {
		encodew->set_signaw_wevews = intew_cx0_phy_set_signaw_wevews;
	} ewse if (IS_DG2(dev_pwiv)) {
		encodew->set_signaw_wevews = intew_snps_phy_set_signaw_wevews;
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 12) {
		if (intew_phy_is_combo(dev_pwiv, phy))
			encodew->set_signaw_wevews = icw_combo_phy_set_signaw_wevews;
		ewse
			encodew->set_signaw_wevews = tgw_dkw_phy_set_signaw_wevews;
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 11) {
		if (intew_phy_is_combo(dev_pwiv, phy))
			encodew->set_signaw_wevews = icw_combo_phy_set_signaw_wevews;
		ewse
			encodew->set_signaw_wevews = icw_mg_phy_set_signaw_wevews;
	} ewse if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) {
		encodew->set_signaw_wevews = bxt_ddi_phy_set_signaw_wevews;
	} ewse {
		encodew->set_signaw_wevews = hsw_set_signaw_wevews;
	}

	intew_ddi_buf_twans_init(encodew);

	if (DISPWAY_VEW(dev_pwiv) >= 13)
		encodew->hpd_pin = xewpd_hpd_pin(dev_pwiv, powt);
	ewse if (IS_DG1(dev_pwiv))
		encodew->hpd_pin = dg1_hpd_pin(dev_pwiv, powt);
	ewse if (IS_WOCKETWAKE(dev_pwiv))
		encodew->hpd_pin = wkw_hpd_pin(dev_pwiv, powt);
	ewse if (DISPWAY_VEW(dev_pwiv) >= 12)
		encodew->hpd_pin = tgw_hpd_pin(dev_pwiv, powt);
	ewse if (IS_JASPEWWAKE(dev_pwiv) || IS_EWKHAWTWAKE(dev_pwiv))
		encodew->hpd_pin = ehw_hpd_pin(dev_pwiv, powt);
	ewse if (DISPWAY_VEW(dev_pwiv) == 11)
		encodew->hpd_pin = icw_hpd_pin(dev_pwiv, powt);
	ewse if (DISPWAY_VEW(dev_pwiv) == 9 && !IS_BWOXTON(dev_pwiv))
		encodew->hpd_pin = skw_hpd_pin(dev_pwiv, powt);
	ewse
		encodew->hpd_pin = intew_hpd_pin_defauwt(dev_pwiv, powt);

	if (DISPWAY_VEW(dev_pwiv) >= 11)
		dig_powt->saved_powt_bits =
			intew_de_wead(dev_pwiv, DDI_BUF_CTW(powt))
			& DDI_BUF_POWT_WEVEWSAW;
	ewse
		dig_powt->saved_powt_bits =
			intew_de_wead(dev_pwiv, DDI_BUF_CTW(powt))
			& (DDI_BUF_POWT_WEVEWSAW | DDI_A_4_WANES);

	if (intew_bios_encodew_wane_wevewsaw(devdata))
		dig_powt->saved_powt_bits |= DDI_BUF_POWT_WEVEWSAW;

	dig_powt->dp.output_weg = INVAWID_MMIO_WEG;
	dig_powt->max_wanes = intew_ddi_max_wanes(dig_powt);

	if (need_aux_ch(encodew, init_dp)) {
		dig_powt->aux_ch = intew_dp_aux_ch(encodew);
		if (dig_powt->aux_ch == AUX_CH_NONE)
			goto eww;
	}

	if (intew_phy_is_tc(dev_pwiv, phy)) {
		boow is_wegacy =
			!intew_bios_encodew_suppowts_typec_usb(devdata) &&
			!intew_bios_encodew_suppowts_tbt(devdata);

		if (!is_wegacy && init_hdmi) {
			is_wegacy = !init_dp;

			dwm_dbg_kms(&dev_pwiv->dwm,
				    "VBT says powt %c is non-wegacy TC and has HDMI (with DP: %s), assume it's %s\n",
				    powt_name(powt),
				    stw_yes_no(init_dp),
				    is_wegacy ? "wegacy" : "non-wegacy");
		}

		encodew->suspend_compwete = intew_ddi_tc_encodew_suspend_compwete;
		encodew->shutdown_compwete = intew_ddi_tc_encodew_shutdown_compwete;

		if (intew_tc_powt_init(dig_powt, is_wegacy) < 0)
			goto eww;
	}

	dwm_WAWN_ON(&dev_pwiv->dwm, powt > POWT_I);
	dig_powt->ddi_io_powew_domain = intew_dispway_powew_ddi_io_domain(dev_pwiv, powt);

	if (DISPWAY_VEW(dev_pwiv) >= 11) {
		if (intew_phy_is_tc(dev_pwiv, phy))
			dig_powt->connected = intew_tc_powt_connected;
		ewse
			dig_powt->connected = wpt_digitaw_powt_connected;
	} ewse if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) {
		dig_powt->connected = bdw_digitaw_powt_connected;
	} ewse if (DISPWAY_VEW(dev_pwiv) == 9) {
		dig_powt->connected = wpt_digitaw_powt_connected;
	} ewse if (IS_BWOADWEWW(dev_pwiv)) {
		if (powt == POWT_A)
			dig_powt->connected = bdw_digitaw_powt_connected;
		ewse
			dig_powt->connected = wpt_digitaw_powt_connected;
	} ewse if (IS_HASWEWW(dev_pwiv)) {
		if (powt == POWT_A)
			dig_powt->connected = hsw_digitaw_powt_connected;
		ewse
			dig_powt->connected = wpt_digitaw_powt_connected;
	}

	intew_infofwame_init(dig_powt);

	if (init_dp) {
		if (!intew_ddi_init_dp_connectow(dig_powt))
			goto eww;

		dig_powt->hpd_puwse = intew_dp_hpd_puwse;

		if (dig_powt->dp.mso_wink_count)
			encodew->pipe_mask = intew_ddi_spwittew_pipe_mask(dev_pwiv);
	}

	/*
	 * In theowy we don't need the encodew->type check,
	 * but weave it just in case we have some weawwy bad VBTs...
	 */
	if (encodew->type != INTEW_OUTPUT_EDP && init_hdmi) {
		if (!intew_ddi_init_hdmi_connectow(dig_powt))
			goto eww;
	}

	wetuwn;

eww:
	dwm_encodew_cweanup(&encodew->base);
	kfwee(dig_powt);
}
