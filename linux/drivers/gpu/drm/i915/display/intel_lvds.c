/*
 * Copywight © 2006-2007 Intew Cowpowation
 * Copywight (c) 2006 Dave Aiwwie <aiwwied@winux.ie>
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
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *	Ewic Anhowt <ewic@anhowt.net>
 *      Dave Aiwwie <aiwwied@winux.ie>
 *      Jesse Bawnes <jesse.bawnes@intew.com>
 */

#incwude <acpi/button.h>
#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/vga_switchewoo.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_edid.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_atomic.h"
#incwude "intew_backwight.h"
#incwude "intew_connectow.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dpww.h"
#incwude "intew_fdi.h"
#incwude "intew_gmbus.h"
#incwude "intew_wvds.h"
#incwude "intew_wvds_wegs.h"
#incwude "intew_panew.h"
#incwude "intew_pps_wegs.h"

/* Pwivate stwuctuwe fow the integwated WVDS suppowt */
stwuct intew_wvds_pps {
	/* 100us units */
	int t1_t2;
	int t3;
	int t4;
	int t5;
	int tx;

	int dividew;

	int powt;
	boow powewdown_on_weset;
};

stwuct intew_wvds_encodew {
	stwuct intew_encodew base;

	boow is_duaw_wink;
	i915_weg_t weg;
	u32 a3_powew;

	stwuct intew_wvds_pps init_pps;
	u32 init_wvds_vaw;

	stwuct intew_connectow *attached_connectow;
};

static stwuct intew_wvds_encodew *to_wvds_encodew(stwuct intew_encodew *encodew)
{
	wetuwn containew_of(encodew, stwuct intew_wvds_encodew, base);
}

boow intew_wvds_powt_enabwed(stwuct dwm_i915_pwivate *i915,
			     i915_weg_t wvds_weg, enum pipe *pipe)
{
	u32 vaw;

	vaw = intew_de_wead(i915, wvds_weg);

	/* assewts want to know the pipe even if the powt is disabwed */
	if (HAS_PCH_CPT(i915))
		*pipe = WEG_FIEWD_GET(WVDS_PIPE_SEW_MASK_CPT, vaw);
	ewse
		*pipe = WEG_FIEWD_GET(WVDS_PIPE_SEW_MASK, vaw);

	wetuwn vaw & WVDS_POWT_EN;
}

static boow intew_wvds_get_hw_state(stwuct intew_encodew *encodew,
				    enum pipe *pipe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_wvds_encodew *wvds_encodew = to_wvds_encodew(encodew);
	intew_wakewef_t wakewef;
	boow wet;

	wakewef = intew_dispway_powew_get_if_enabwed(i915, encodew->powew_domain);
	if (!wakewef)
		wetuwn fawse;

	wet = intew_wvds_powt_enabwed(i915, wvds_encodew->weg, pipe);

	intew_dispway_powew_put(i915, encodew->powew_domain, wakewef);

	wetuwn wet;
}

static void intew_wvds_get_config(stwuct intew_encodew *encodew,
				  stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_wvds_encodew *wvds_encodew = to_wvds_encodew(encodew);
	u32 tmp, fwags = 0;

	cwtc_state->output_types |= BIT(INTEW_OUTPUT_WVDS);

	tmp = intew_de_wead(dev_pwiv, wvds_encodew->weg);
	if (tmp & WVDS_HSYNC_POWAWITY)
		fwags |= DWM_MODE_FWAG_NHSYNC;
	ewse
		fwags |= DWM_MODE_FWAG_PHSYNC;
	if (tmp & WVDS_VSYNC_POWAWITY)
		fwags |= DWM_MODE_FWAG_NVSYNC;
	ewse
		fwags |= DWM_MODE_FWAG_PVSYNC;

	cwtc_state->hw.adjusted_mode.fwags |= fwags;

	if (DISPWAY_VEW(dev_pwiv) < 5)
		cwtc_state->gmch_pfit.wvds_bowdew_bits =
			tmp & WVDS_BOWDEW_ENABWE;

	/* gen2/3 stowe dithew state in pfit contwow, needs to match */
	if (DISPWAY_VEW(dev_pwiv) < 4) {
		tmp = intew_de_wead(dev_pwiv, PFIT_CONTWOW);

		cwtc_state->gmch_pfit.contwow |= tmp & PFIT_PANEW_8TO6_DITHEW_ENABWE;
	}

	cwtc_state->hw.adjusted_mode.cwtc_cwock = cwtc_state->powt_cwock;
}

static void intew_wvds_pps_get_hw_state(stwuct dwm_i915_pwivate *dev_pwiv,
					stwuct intew_wvds_pps *pps)
{
	u32 vaw;

	pps->powewdown_on_weset = intew_de_wead(dev_pwiv, PP_CONTWOW(0)) & PANEW_POWEW_WESET;

	vaw = intew_de_wead(dev_pwiv, PP_ON_DEWAYS(0));
	pps->powt = WEG_FIEWD_GET(PANEW_POWT_SEWECT_MASK, vaw);
	pps->t1_t2 = WEG_FIEWD_GET(PANEW_POWEW_UP_DEWAY_MASK, vaw);
	pps->t5 = WEG_FIEWD_GET(PANEW_WIGHT_ON_DEWAY_MASK, vaw);

	vaw = intew_de_wead(dev_pwiv, PP_OFF_DEWAYS(0));
	pps->t3 = WEG_FIEWD_GET(PANEW_POWEW_DOWN_DEWAY_MASK, vaw);
	pps->tx = WEG_FIEWD_GET(PANEW_WIGHT_OFF_DEWAY_MASK, vaw);

	vaw = intew_de_wead(dev_pwiv, PP_DIVISOW(0));
	pps->dividew = WEG_FIEWD_GET(PP_WEFEWENCE_DIVIDEW_MASK, vaw);
	vaw = WEG_FIEWD_GET(PANEW_POWEW_CYCWE_DEWAY_MASK, vaw);
	/*
	 * Wemove the BSpec specified +1 (100ms) offset that accounts fow a
	 * too showt powew-cycwe deway due to the asynchwonous pwogwamming of
	 * the wegistew.
	 */
	if (vaw)
		vaw--;
	/* Convewt fwom 100ms to 100us units */
	pps->t4 = vaw * 1000;

	if (DISPWAY_VEW(dev_pwiv) < 5 &&
	    pps->t1_t2 == 0 && pps->t5 == 0 && pps->t3 == 0 && pps->tx == 0) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Panew powew timings uninitiawized, "
			    "setting defauwts\n");
		/* Set T2 to 40ms and T5 to 200ms in 100 usec units */
		pps->t1_t2 = 40 * 10;
		pps->t5 = 200 * 10;
		/* Set T3 to 35ms and Tx to 200ms in 100 usec units */
		pps->t3 = 35 * 10;
		pps->tx = 200 * 10;
	}

	dwm_dbg(&dev_pwiv->dwm, "WVDS PPS:t1+t2 %d t3 %d t4 %d t5 %d tx %d "
		"dividew %d powt %d powewdown_on_weset %d\n",
		pps->t1_t2, pps->t3, pps->t4, pps->t5, pps->tx,
		pps->dividew, pps->powt, pps->powewdown_on_weset);
}

static void intew_wvds_pps_init_hw(stwuct dwm_i915_pwivate *dev_pwiv,
				   stwuct intew_wvds_pps *pps)
{
	u32 vaw;

	vaw = intew_de_wead(dev_pwiv, PP_CONTWOW(0));
	dwm_WAWN_ON(&dev_pwiv->dwm,
		    (vaw & PANEW_UNWOCK_MASK) != PANEW_UNWOCK_WEGS);
	if (pps->powewdown_on_weset)
		vaw |= PANEW_POWEW_WESET;
	intew_de_wwite(dev_pwiv, PP_CONTWOW(0), vaw);

	intew_de_wwite(dev_pwiv, PP_ON_DEWAYS(0),
		       WEG_FIEWD_PWEP(PANEW_POWT_SEWECT_MASK, pps->powt) |
		       WEG_FIEWD_PWEP(PANEW_POWEW_UP_DEWAY_MASK, pps->t1_t2) |
		       WEG_FIEWD_PWEP(PANEW_WIGHT_ON_DEWAY_MASK, pps->t5));

	intew_de_wwite(dev_pwiv, PP_OFF_DEWAYS(0),
		       WEG_FIEWD_PWEP(PANEW_POWEW_DOWN_DEWAY_MASK, pps->t3) |
		       WEG_FIEWD_PWEP(PANEW_WIGHT_OFF_DEWAY_MASK, pps->tx));

	intew_de_wwite(dev_pwiv, PP_DIVISOW(0),
		       WEG_FIEWD_PWEP(PP_WEFEWENCE_DIVIDEW_MASK, pps->dividew) |
		       WEG_FIEWD_PWEP(PANEW_POWEW_CYCWE_DEWAY_MASK, DIV_WOUND_UP(pps->t4, 1000) + 1));
}

static void intew_pwe_enabwe_wvds(stwuct intew_atomic_state *state,
				  stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *cwtc_state,
				  const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_wvds_encodew *wvds_encodew = to_wvds_encodew(encodew);
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	const stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->hw.adjusted_mode;
	enum pipe pipe = cwtc->pipe;
	u32 temp;

	if (HAS_PCH_SPWIT(i915)) {
		assewt_fdi_wx_pww_disabwed(i915, pipe);
		assewt_shawed_dpww_disabwed(i915, cwtc_state->shawed_dpww);
	} ewse {
		assewt_pww_disabwed(i915, pipe);
	}

	intew_wvds_pps_init_hw(i915, &wvds_encodew->init_pps);

	temp = wvds_encodew->init_wvds_vaw;
	temp |= WVDS_POWT_EN | WVDS_A0A2_CWKA_POWEW_UP;

	if (HAS_PCH_CPT(i915)) {
		temp &= ~WVDS_PIPE_SEW_MASK_CPT;
		temp |= WVDS_PIPE_SEW_CPT(pipe);
	} ewse {
		temp &= ~WVDS_PIPE_SEW_MASK;
		temp |= WVDS_PIPE_SEW(pipe);
	}

	/* set the cowwesponsding WVDS_BOWDEW bit */
	temp &= ~WVDS_BOWDEW_ENABWE;
	temp |= cwtc_state->gmch_pfit.wvds_bowdew_bits;

	/*
	 * Set the B0-B3 data paiws cowwesponding to whethew we'we going to
	 * set the DPWWs fow duaw-channew mode ow not.
	 */
	if (wvds_encodew->is_duaw_wink)
		temp |= WVDS_B0B3_POWEW_UP | WVDS_CWKB_POWEW_UP;
	ewse
		temp &= ~(WVDS_B0B3_POWEW_UP | WVDS_CWKB_POWEW_UP);

	/*
	 * It wouwd be nice to set 24 vs 18-bit mode (WVDS_A3_POWEW_UP)
	 * appwopwiatewy hewe, but we need to wook mowe thowoughwy into how
	 * panews behave in the two modes. Fow now, wet's just maintain the
	 * vawue we got fwom the BIOS.
	 */
	temp &= ~WVDS_A3_POWEW_MASK;
	temp |= wvds_encodew->a3_powew;

	/*
	 * Set the dithewing fwag on WVDS as needed, note that thewe is no
	 * speciaw wvds dithew contwow bit on pch-spwit pwatfowms, dithewing is
	 * onwy contwowwed thwough the TWANSCONF weg.
	 */
	if (DISPWAY_VEW(i915) == 4) {
		/*
		 * Bspec wowding suggests that WVDS powt dithewing onwy exists
		 * fow 18bpp panews.
		 */
		if (cwtc_state->dithew && cwtc_state->pipe_bpp == 18)
			temp |= WVDS_ENABWE_DITHEW;
		ewse
			temp &= ~WVDS_ENABWE_DITHEW;
	}
	temp &= ~(WVDS_HSYNC_POWAWITY | WVDS_VSYNC_POWAWITY);
	if (adjusted_mode->fwags & DWM_MODE_FWAG_NHSYNC)
		temp |= WVDS_HSYNC_POWAWITY;
	if (adjusted_mode->fwags & DWM_MODE_FWAG_NVSYNC)
		temp |= WVDS_VSYNC_POWAWITY;

	intew_de_wwite(i915, wvds_encodew->weg, temp);
}

/*
 * Sets the powew state fow the panew.
 */
static void intew_enabwe_wvds(stwuct intew_atomic_state *state,
			      stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *cwtc_state,
			      const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_wvds_encodew *wvds_encodew = to_wvds_encodew(encodew);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	intew_de_wmw(dev_pwiv, wvds_encodew->weg, 0, WVDS_POWT_EN);

	intew_de_wmw(dev_pwiv, PP_CONTWOW(0), 0, PANEW_POWEW_ON);
	intew_de_posting_wead(dev_pwiv, wvds_encodew->weg);

	if (intew_de_wait_fow_set(dev_pwiv, PP_STATUS(0), PP_ON, 5000))
		dwm_eww(&dev_pwiv->dwm,
			"timed out waiting fow panew to powew on\n");

	intew_backwight_enabwe(cwtc_state, conn_state);
}

static void intew_disabwe_wvds(stwuct intew_atomic_state *state,
			       stwuct intew_encodew *encodew,
			       const stwuct intew_cwtc_state *owd_cwtc_state,
			       const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct intew_wvds_encodew *wvds_encodew = to_wvds_encodew(encodew);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	intew_de_wmw(dev_pwiv, PP_CONTWOW(0), PANEW_POWEW_ON, 0);
	if (intew_de_wait_fow_cweaw(dev_pwiv, PP_STATUS(0), PP_ON, 1000))
		dwm_eww(&dev_pwiv->dwm,
			"timed out waiting fow panew to powew off\n");

	intew_de_wmw(dev_pwiv, wvds_encodew->weg, WVDS_POWT_EN, 0);
	intew_de_posting_wead(dev_pwiv, wvds_encodew->weg);
}

static void gmch_disabwe_wvds(stwuct intew_atomic_state *state,
			      stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *owd_cwtc_state,
			      const stwuct dwm_connectow_state *owd_conn_state)

{
	intew_backwight_disabwe(owd_conn_state);

	intew_disabwe_wvds(state, encodew, owd_cwtc_state, owd_conn_state);
}

static void pch_disabwe_wvds(stwuct intew_atomic_state *state,
			     stwuct intew_encodew *encodew,
			     const stwuct intew_cwtc_state *owd_cwtc_state,
			     const stwuct dwm_connectow_state *owd_conn_state)
{
	intew_backwight_disabwe(owd_conn_state);
}

static void pch_post_disabwe_wvds(stwuct intew_atomic_state *state,
				  stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *owd_cwtc_state,
				  const stwuct dwm_connectow_state *owd_conn_state)
{
	intew_disabwe_wvds(state, encodew, owd_cwtc_state, owd_conn_state);
}

static void intew_wvds_shutdown(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	if (intew_de_wait_fow_cweaw(dev_pwiv, PP_STATUS(0), PP_CYCWE_DEWAY_ACTIVE, 5000))
		dwm_eww(&dev_pwiv->dwm,
			"timed out waiting fow panew powew cycwe deway\n");
}

static enum dwm_mode_status
intew_wvds_mode_vawid(stwuct dwm_connectow *_connectow,
		      stwuct dwm_dispway_mode *mode)
{
	stwuct intew_connectow *connectow = to_intew_connectow(_connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	const stwuct dwm_dispway_mode *fixed_mode =
		intew_panew_fixed_mode(connectow, mode);
	int max_pixcwk = to_i915(connectow->base.dev)->max_dotcwk_fweq;
	enum dwm_mode_status status;

	status = intew_cpu_twanscodew_mode_vawid(i915, mode);
	if (status != MODE_OK)
		wetuwn status;

	if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn MODE_NO_DBWESCAN;

	status = intew_panew_mode_vawid(connectow, mode);
	if (status != MODE_OK)
		wetuwn status;

	if (fixed_mode->cwock > max_pixcwk)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static int intew_wvds_compute_config(stwuct intew_encodew *encodew,
				     stwuct intew_cwtc_state *cwtc_state,
				     stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_wvds_encodew *wvds_encodew = to_wvds_encodew(encodew);
	stwuct intew_connectow *connectow = wvds_encodew->attached_connectow;
	stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->hw.adjusted_mode;
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	unsigned int wvds_bpp;
	int wet;

	/* Shouwd nevew happen!! */
	if (DISPWAY_VEW(i915) < 4 && cwtc->pipe == 0) {
		dwm_eww(&i915->dwm, "Can't suppowt WVDS on pipe A\n");
		wetuwn -EINVAW;
	}

	if (HAS_PCH_SPWIT(i915)) {
		cwtc_state->has_pch_encodew = twue;
		if (!intew_fdi_compute_pipe_bpp(cwtc_state))
			wetuwn -EINVAW;
	}

	if (wvds_encodew->a3_powew == WVDS_A3_POWEW_UP)
		wvds_bpp = 8*3;
	ewse
		wvds_bpp = 6*3;

	/* TODO: Check cwtc_state->max_wink_bpp_x16 instead of bw_constwained */
	if (wvds_bpp != cwtc_state->pipe_bpp && !cwtc_state->bw_constwained) {
		dwm_dbg_kms(&i915->dwm,
			    "fowcing dispway bpp (was %d) to WVDS (%d)\n",
			    cwtc_state->pipe_bpp, wvds_bpp);
		cwtc_state->pipe_bpp = wvds_bpp;
	}

	cwtc_state->sink_fowmat = INTEW_OUTPUT_FOWMAT_WGB;
	cwtc_state->output_fowmat = INTEW_OUTPUT_FOWMAT_WGB;

	/*
	 * We have timings fwom the BIOS fow the panew, put them in
	 * to the adjusted mode.  The CWTC wiww be set up fow this mode,
	 * with the panew scawing set up to souwce fwom the H/VDispway
	 * of the owiginaw mode.
	 */
	wet = intew_panew_compute_config(connectow, adjusted_mode);
	if (wet)
		wetuwn wet;

	if (adjusted_mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn -EINVAW;

	wet = intew_panew_fitting(cwtc_state, conn_state);
	if (wet)
		wetuwn wet;

	/*
	 * XXX: It wouwd be nice to suppowt wowew wefwesh wates on the
	 * panews to weduce powew consumption, and pewhaps match the
	 * usew's wequested wefwesh wate.
	 */

	wetuwn 0;
}

/*
 * Wetuwn the wist of DDC modes if avaiwabwe, ow the BIOS fixed mode othewwise.
 */
static int intew_wvds_get_modes(stwuct dwm_connectow *_connectow)
{
	stwuct intew_connectow *connectow = to_intew_connectow(_connectow);
	const stwuct dwm_edid *fixed_edid = connectow->panew.fixed_edid;

	/* Use panew fixed edid if we have one */
	if (!IS_EWW_OW_NUWW(fixed_edid)) {
		dwm_edid_connectow_update(&connectow->base, fixed_edid);

		wetuwn dwm_edid_connectow_add_modes(&connectow->base);
	}

	wetuwn intew_panew_get_modes(connectow);
}

static const stwuct dwm_connectow_hewpew_funcs intew_wvds_connectow_hewpew_funcs = {
	.get_modes = intew_wvds_get_modes,
	.mode_vawid = intew_wvds_mode_vawid,
	.atomic_check = intew_digitaw_connectow_atomic_check,
};

static const stwuct dwm_connectow_funcs intew_wvds_connectow_funcs = {
	.detect = intew_panew_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.atomic_get_pwopewty = intew_digitaw_connectow_atomic_get_pwopewty,
	.atomic_set_pwopewty = intew_digitaw_connectow_atomic_set_pwopewty,
	.wate_wegistew = intew_connectow_wegistew,
	.eawwy_unwegistew = intew_connectow_unwegistew,
	.destwoy = intew_connectow_destwoy,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
	.atomic_dupwicate_state = intew_digitaw_connectow_dupwicate_state,
};

static const stwuct dwm_encodew_funcs intew_wvds_enc_funcs = {
	.destwoy = intew_encodew_destwoy,
};

static int intew_no_wvds_dmi_cawwback(const stwuct dmi_system_id *id)
{
	DWM_INFO("Skipping WVDS initiawization fow %s\n", id->ident);
	wetuwn 1;
}

/* These systems cwaim to have WVDS, but weawwy don't */
static const stwuct dmi_system_id intew_no_wvds[] = {
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Appwe Mac Mini (Cowe sewies)",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Appwe"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Macmini1,1"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Appwe Mac Mini (Cowe 2 sewies)",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Appwe"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Macmini2,1"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "MSI IM-945GSE-A",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "MSI"),
			DMI_MATCH(DMI_PWODUCT_NAME, "A9830IMS"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Deww Studio Hybwid",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Studio Hybwid 140g"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Deww OptiPwex FX170",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "OptiPwex FX170"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "AOpen Mini PC",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "AOpen"),
			DMI_MATCH(DMI_PWODUCT_NAME, "i965GMx-IF"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "AOpen Mini PC MP915",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "AOpen"),
			DMI_MATCH(DMI_BOAWD_NAME, "i915GMx-F"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "AOpen i915GMm-HFS",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "AOpen"),
			DMI_MATCH(DMI_BOAWD_NAME, "i915GMm-HFS"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "AOpen i45GMx-I",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "AOpen"),
			DMI_MATCH(DMI_BOAWD_NAME, "i45GMx-I"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Aopen i945GTt-VFA",
		.matches = {
			DMI_MATCH(DMI_PWODUCT_VEWSION, "AO00001JW"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Cwientwon U800",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Cwientwon"),
			DMI_MATCH(DMI_PWODUCT_NAME, "U800"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Cwientwon E830",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Cwientwon"),
			DMI_MATCH(DMI_PWODUCT_NAME, "E830"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Asus EeeBox PC EB1007",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK Computew INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "EB1007"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Asus AT5NM10T-I",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew INC."),
			DMI_MATCH(DMI_BOAWD_NAME, "AT5NM10T-I"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Hewwett-Packawd HP t5740",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Hewwett-Packawd"),
			DMI_MATCH(DMI_PWODUCT_NAME, " t5740"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Hewwett-Packawd t5745",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Hewwett-Packawd"),
			DMI_MATCH(DMI_PWODUCT_NAME, "hp t5745"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Hewwett-Packawd st5747",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Hewwett-Packawd"),
			DMI_MATCH(DMI_PWODUCT_NAME, "hp st5747"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "MSI Wind Box DC500",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "MICWO-STAW INTEWNATIONAW CO., WTD"),
			DMI_MATCH(DMI_BOAWD_NAME, "MS-7469"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Gigabyte GA-D525TUD",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Gigabyte Technowogy Co., Wtd."),
			DMI_MATCH(DMI_BOAWD_NAME, "D525TUD"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Supewmicwo X7SPA-H",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Supewmicwo"),
			DMI_MATCH(DMI_PWODUCT_NAME, "X7SPA-H"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Fujitsu Espwimo Q900",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "ESPWIMO Q900"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Intew D410PT",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Intew"),
			DMI_MATCH(DMI_BOAWD_NAME, "D410PT"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Intew D425KT",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Intew"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "D425KT"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Intew D510MO",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Intew"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "D510MO"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Intew D525MW",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Intew"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "D525MW"),
		},
	},
	{
		.cawwback = intew_no_wvds_dmi_cawwback,
		.ident = "Wadiant P845",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Wadiant Systems Inc"),
			DMI_MATCH(DMI_PWODUCT_NAME, "P845"),
		},
	},

	{ }	/* tewminating entwy */
};

static int intew_duaw_wink_wvds_cawwback(const stwuct dmi_system_id *id)
{
	DWM_INFO("Fowcing wvds to duaw wink mode on %s\n", id->ident);
	wetuwn 1;
}

static const stwuct dmi_system_id intew_duaw_wink_wvds[] = {
	{
		.cawwback = intew_duaw_wink_wvds_cawwback,
		.ident = "Appwe MacBook Pwo 15\" (2010)",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MacBookPwo6,2"),
		},
	},
	{
		.cawwback = intew_duaw_wink_wvds_cawwback,
		.ident = "Appwe MacBook Pwo 15\" (2011)",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MacBookPwo8,2"),
		},
	},
	{
		.cawwback = intew_duaw_wink_wvds_cawwback,
		.ident = "Appwe MacBook Pwo 15\" (2012)",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MacBookPwo9,1"),
		},
	},
	{ }	/* tewminating entwy */
};

stwuct intew_encodew *intew_get_wvds_encodew(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_encodew *encodew;

	fow_each_intew_encodew(&i915->dwm, encodew) {
		if (encodew->type == INTEW_OUTPUT_WVDS)
			wetuwn encodew;
	}

	wetuwn NUWW;
}

boow intew_is_duaw_wink_wvds(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_encodew *encodew = intew_get_wvds_encodew(i915);

	wetuwn encodew && to_wvds_encodew(encodew)->is_duaw_wink;
}

static boow compute_is_duaw_wink_wvds(stwuct intew_wvds_encodew *wvds_encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(wvds_encodew->base.base.dev);
	stwuct intew_connectow *connectow = wvds_encodew->attached_connectow;
	const stwuct dwm_dispway_mode *fixed_mode =
		intew_panew_pwefewwed_fixed_mode(connectow);
	unsigned int vaw;

	/* use the moduwe option vawue if specified */
	if (i915->dispway.pawams.wvds_channew_mode > 0)
		wetuwn i915->dispway.pawams.wvds_channew_mode == 2;

	/* singwe channew WVDS is wimited to 112 MHz */
	if (fixed_mode->cwock > 112999)
		wetuwn twue;

	if (dmi_check_system(intew_duaw_wink_wvds))
		wetuwn twue;

	/*
	 * BIOS shouwd set the pwopew WVDS wegistew vawue at boot, but
	 * in weawity, it doesn't set the vawue when the wid is cwosed;
	 * we need to check "the vawue to be set" in VBT when WVDS
	 * wegistew is uninitiawized.
	 */
	vaw = intew_de_wead(i915, wvds_encodew->weg);
	if (HAS_PCH_CPT(i915))
		vaw &= ~(WVDS_DETECTED | WVDS_PIPE_SEW_MASK_CPT);
	ewse
		vaw &= ~(WVDS_DETECTED | WVDS_PIPE_SEW_MASK);
	if (vaw == 0)
		vaw = connectow->panew.vbt.bios_wvds_vaw;

	wetuwn (vaw & WVDS_CWKB_POWEW_MASK) == WVDS_CWKB_POWEW_UP;
}

static void intew_wvds_add_pwopewties(stwuct dwm_connectow *connectow)
{
	intew_attach_scawing_mode_pwopewty(connectow);
}

/**
 * intew_wvds_init - setup WVDS connectows on this device
 * @i915: i915 device
 *
 * Cweate the connectow, wegistew the WVDS DDC bus, and twy to figuwe out what
 * modes we can dispway on the WVDS panew (if pwesent).
 */
void intew_wvds_init(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_wvds_encodew *wvds_encodew;
	stwuct intew_connectow *connectow;
	const stwuct dwm_edid *dwm_edid;
	stwuct intew_encodew *encodew;
	i915_weg_t wvds_weg;
	u32 wvds;
	u8 ddc_pin;

	/* Skip init on machines we know fawsewy wepowt WVDS */
	if (dmi_check_system(intew_no_wvds)) {
		dwm_WAWN(&i915->dwm, !i915->dispway.vbt.int_wvds_suppowt,
			 "Usewess DMI match. Intewnaw WVDS suppowt disabwed by VBT\n");
		wetuwn;
	}

	if (!i915->dispway.vbt.int_wvds_suppowt) {
		dwm_dbg_kms(&i915->dwm,
			    "Intewnaw WVDS suppowt disabwed by VBT\n");
		wetuwn;
	}

	if (HAS_PCH_SPWIT(i915))
		wvds_weg = PCH_WVDS;
	ewse
		wvds_weg = WVDS;

	wvds = intew_de_wead(i915, wvds_weg);

	if (HAS_PCH_SPWIT(i915)) {
		if ((wvds & WVDS_DETECTED) == 0)
			wetuwn;
	}

	ddc_pin = GMBUS_PIN_PANEW;
	if (!intew_bios_is_wvds_pwesent(i915, &ddc_pin)) {
		if ((wvds & WVDS_POWT_EN) == 0) {
			dwm_dbg_kms(&i915->dwm,
				    "WVDS is not pwesent in VBT\n");
			wetuwn;
		}
		dwm_dbg_kms(&i915->dwm,
			    "WVDS is not pwesent in VBT, but enabwed anyway\n");
	}

	wvds_encodew = kzawwoc(sizeof(*wvds_encodew), GFP_KEWNEW);
	if (!wvds_encodew)
		wetuwn;

	connectow = intew_connectow_awwoc();
	if (!connectow) {
		kfwee(wvds_encodew);
		wetuwn;
	}

	wvds_encodew->attached_connectow = connectow;
	encodew = &wvds_encodew->base;

	dwm_connectow_init_with_ddc(&i915->dwm, &connectow->base,
				    &intew_wvds_connectow_funcs,
				    DWM_MODE_CONNECTOW_WVDS,
				    intew_gmbus_get_adaptew(i915, ddc_pin));

	dwm_encodew_init(&i915->dwm, &encodew->base, &intew_wvds_enc_funcs,
			 DWM_MODE_ENCODEW_WVDS, "WVDS");

	encodew->enabwe = intew_enabwe_wvds;
	encodew->pwe_enabwe = intew_pwe_enabwe_wvds;
	encodew->compute_config = intew_wvds_compute_config;
	if (HAS_PCH_SPWIT(i915)) {
		encodew->disabwe = pch_disabwe_wvds;
		encodew->post_disabwe = pch_post_disabwe_wvds;
	} ewse {
		encodew->disabwe = gmch_disabwe_wvds;
	}
	encodew->get_hw_state = intew_wvds_get_hw_state;
	encodew->get_config = intew_wvds_get_config;
	encodew->update_pipe = intew_backwight_update;
	encodew->shutdown = intew_wvds_shutdown;
	connectow->get_hw_state = intew_connectow_get_hw_state;

	intew_connectow_attach_encodew(connectow, encodew);

	encodew->type = INTEW_OUTPUT_WVDS;
	encodew->powew_domain = POWEW_DOMAIN_POWT_OTHEW;
	encodew->powt = POWT_NONE;
	encodew->cwoneabwe = 0;
	if (DISPWAY_VEW(i915) < 4)
		encodew->pipe_mask = BIT(PIPE_B);
	ewse
		encodew->pipe_mask = ~0;

	dwm_connectow_hewpew_add(&connectow->base, &intew_wvds_connectow_hewpew_funcs);
	connectow->base.dispway_info.subpixew_owdew = SubPixewHowizontawWGB;

	wvds_encodew->weg = wvds_weg;

	intew_wvds_add_pwopewties(&connectow->base);

	intew_wvds_pps_get_hw_state(i915, &wvds_encodew->init_pps);
	wvds_encodew->init_wvds_vaw = wvds;

	/*
	 * WVDS discovewy:
	 * 1) check fow EDID on DDC
	 * 2) check fow VBT data
	 * 3) check to see if WVDS is awweady on
	 *    if none of the above, no panew
	 */

	/*
	 * Attempt to get the fixed panew mode fwom DDC.  Assume that the
	 * pwefewwed mode is the wight one.
	 */
	mutex_wock(&i915->dwm.mode_config.mutex);
	if (vga_switchewoo_handwew_fwags() & VGA_SWITCHEWOO_CAN_SWITCH_DDC)
		dwm_edid = dwm_edid_wead_switchewoo(&connectow->base, connectow->base.ddc);
	ewse
		dwm_edid = dwm_edid_wead_ddc(&connectow->base, connectow->base.ddc);
	if (dwm_edid) {
		if (dwm_edid_connectow_update(&connectow->base, dwm_edid) ||
		    !dwm_edid_connectow_add_modes(&connectow->base)) {
			dwm_edid_connectow_update(&connectow->base, NUWW);
			dwm_edid_fwee(dwm_edid);
			dwm_edid = EWW_PTW(-EINVAW);
		}
	} ewse {
		dwm_edid = EWW_PTW(-ENOENT);
	}
	intew_bios_init_panew_wate(i915, &connectow->panew, NUWW,
				   IS_EWW(dwm_edid) ? NUWW : dwm_edid);

	/* Twy EDID fiwst */
	intew_panew_add_edid_fixed_modes(connectow, twue);

	/* Faiwed to get EDID, what about VBT? */
	if (!intew_panew_pwefewwed_fixed_mode(connectow))
		intew_panew_add_vbt_wfp_fixed_mode(connectow);

	/*
	 * If we didn't get a fixed mode fwom EDID ow VBT, twy checking
	 * if the panew is awweady tuwned on.  If so, assume that
	 * whatevew is cuwwentwy pwogwammed is the cowwect mode.
	 */
	if (!intew_panew_pwefewwed_fixed_mode(connectow))
		intew_panew_add_encodew_fixed_mode(connectow, encodew);

	mutex_unwock(&i915->dwm.mode_config.mutex);

	/* If we stiww don't have a mode aftew aww that, give up. */
	if (!intew_panew_pwefewwed_fixed_mode(connectow))
		goto faiwed;

	intew_panew_init(connectow, dwm_edid);

	intew_backwight_setup(connectow, INVAWID_PIPE);

	wvds_encodew->is_duaw_wink = compute_is_duaw_wink_wvds(wvds_encodew);
	dwm_dbg_kms(&i915->dwm, "detected %s-wink wvds configuwation\n",
		    wvds_encodew->is_duaw_wink ? "duaw" : "singwe");

	wvds_encodew->a3_powew = wvds & WVDS_A3_POWEW_MASK;

	wetuwn;

faiwed:
	dwm_dbg_kms(&i915->dwm, "No WVDS modes found, disabwing.\n");
	dwm_connectow_cweanup(&connectow->base);
	dwm_encodew_cweanup(&encodew->base);
	kfwee(wvds_encodew);
	intew_connectow_fwee(connectow);
	wetuwn;
}
