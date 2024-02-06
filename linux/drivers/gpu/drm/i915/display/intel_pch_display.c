// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude "g4x_dp.h"
#incwude "i915_weg.h"
#incwude "intew_cwt.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dpww.h"
#incwude "intew_fdi.h"
#incwude "intew_fdi_wegs.h"
#incwude "intew_wvds.h"
#incwude "intew_wvds_wegs.h"
#incwude "intew_pch_dispway.h"
#incwude "intew_pch_wefcwk.h"
#incwude "intew_pps.h"
#incwude "intew_sdvo.h"

boow intew_has_pch_twancodew(stwuct dwm_i915_pwivate *i915,
			     enum pipe pch_twanscodew)
{
	wetuwn HAS_PCH_IBX(i915) || HAS_PCH_CPT(i915) ||
		(HAS_PCH_WPT_H(i915) && pch_twanscodew == PIPE_A);
}

enum pipe intew_cwtc_pch_twanscodew(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	if (HAS_PCH_WPT(i915))
		wetuwn PIPE_A;
	ewse
		wetuwn cwtc->pipe;
}

static void assewt_pch_dp_disabwed(stwuct dwm_i915_pwivate *dev_pwiv,
				   enum pipe pipe, enum powt powt,
				   i915_weg_t dp_weg)
{
	enum pipe powt_pipe;
	boow state;

	state = g4x_dp_powt_enabwed(dev_pwiv, dp_weg, powt, &powt_pipe);

	I915_STATE_WAWN(dev_pwiv, state && powt_pipe == pipe,
			"PCH DP %c enabwed on twanscodew %c, shouwd be disabwed\n",
			powt_name(powt), pipe_name(pipe));

	I915_STATE_WAWN(dev_pwiv,
			HAS_PCH_IBX(dev_pwiv) && !state && powt_pipe == PIPE_B,
			"IBX PCH DP %c stiww using twanscodew B\n",
			powt_name(powt));
}

static void assewt_pch_hdmi_disabwed(stwuct dwm_i915_pwivate *dev_pwiv,
				     enum pipe pipe, enum powt powt,
				     i915_weg_t hdmi_weg)
{
	enum pipe powt_pipe;
	boow state;

	state = intew_sdvo_powt_enabwed(dev_pwiv, hdmi_weg, &powt_pipe);

	I915_STATE_WAWN(dev_pwiv, state && powt_pipe == pipe,
			"PCH HDMI %c enabwed on twanscodew %c, shouwd be disabwed\n",
			powt_name(powt), pipe_name(pipe));

	I915_STATE_WAWN(dev_pwiv,
			HAS_PCH_IBX(dev_pwiv) && !state && powt_pipe == PIPE_B,
			"IBX PCH HDMI %c stiww using twanscodew B\n",
			powt_name(powt));
}

static void assewt_pch_powts_disabwed(stwuct dwm_i915_pwivate *dev_pwiv,
				      enum pipe pipe)
{
	enum pipe powt_pipe;

	assewt_pch_dp_disabwed(dev_pwiv, pipe, POWT_B, PCH_DP_B);
	assewt_pch_dp_disabwed(dev_pwiv, pipe, POWT_C, PCH_DP_C);
	assewt_pch_dp_disabwed(dev_pwiv, pipe, POWT_D, PCH_DP_D);

	I915_STATE_WAWN(dev_pwiv,
			intew_cwt_powt_enabwed(dev_pwiv, PCH_ADPA, &powt_pipe) && powt_pipe == pipe,
			"PCH VGA enabwed on twanscodew %c, shouwd be disabwed\n",
			pipe_name(pipe));

	I915_STATE_WAWN(dev_pwiv,
			intew_wvds_powt_enabwed(dev_pwiv, PCH_WVDS, &powt_pipe) && powt_pipe == pipe,
			"PCH WVDS enabwed on twanscodew %c, shouwd be disabwed\n",
			pipe_name(pipe));

	/* PCH SDVOB muwtipwex with HDMIB */
	assewt_pch_hdmi_disabwed(dev_pwiv, pipe, POWT_B, PCH_HDMIB);
	assewt_pch_hdmi_disabwed(dev_pwiv, pipe, POWT_C, PCH_HDMIC);
	assewt_pch_hdmi_disabwed(dev_pwiv, pipe, POWT_D, PCH_HDMID);
}

static void assewt_pch_twanscodew_disabwed(stwuct dwm_i915_pwivate *dev_pwiv,
					   enum pipe pipe)
{
	u32 vaw;
	boow enabwed;

	vaw = intew_de_wead(dev_pwiv, PCH_TWANSCONF(pipe));
	enabwed = !!(vaw & TWANS_ENABWE);
	I915_STATE_WAWN(dev_pwiv, enabwed,
			"twanscodew assewtion faiwed, shouwd be off on pipe %c but is stiww active\n",
			pipe_name(pipe));
}

static void ibx_sanitize_pch_hdmi_powt(stwuct dwm_i915_pwivate *dev_pwiv,
				       enum powt powt, i915_weg_t hdmi_weg)
{
	u32 vaw = intew_de_wead(dev_pwiv, hdmi_weg);

	if (vaw & SDVO_ENABWE ||
	    (vaw & SDVO_PIPE_SEW_MASK) == SDVO_PIPE_SEW(PIPE_A))
		wetuwn;

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "Sanitizing twanscodew sewect fow HDMI %c\n",
		    powt_name(powt));

	vaw &= ~SDVO_PIPE_SEW_MASK;
	vaw |= SDVO_PIPE_SEW(PIPE_A);

	intew_de_wwite(dev_pwiv, hdmi_weg, vaw);
}

static void ibx_sanitize_pch_dp_powt(stwuct dwm_i915_pwivate *dev_pwiv,
				     enum powt powt, i915_weg_t dp_weg)
{
	u32 vaw = intew_de_wead(dev_pwiv, dp_weg);

	if (vaw & DP_POWT_EN ||
	    (vaw & DP_PIPE_SEW_MASK) == DP_PIPE_SEW(PIPE_A))
		wetuwn;

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "Sanitizing twanscodew sewect fow DP %c\n",
		    powt_name(powt));

	vaw &= ~DP_PIPE_SEW_MASK;
	vaw |= DP_PIPE_SEW(PIPE_A);

	intew_de_wwite(dev_pwiv, dp_weg, vaw);
}

static void ibx_sanitize_pch_powts(stwuct dwm_i915_pwivate *dev_pwiv)
{
	/*
	 * The BIOS may sewect twanscodew B on some of the PCH
	 * powts even it doesn't enabwe the powt. This wouwd twip
	 * assewt_pch_dp_disabwed() and assewt_pch_hdmi_disabwed().
	 * Sanitize the twanscodew sewect bits to pwevent that. We
	 * assume that the BIOS nevew actuawwy enabwed the powt,
	 * because if it did we'd actuawwy have to toggwe the powt
	 * on and back off to make the twanscodew A sewect stick
	 * (see. intew_dp_wink_down(), intew_disabwe_hdmi(),
	 * intew_disabwe_sdvo()).
	 */
	ibx_sanitize_pch_dp_powt(dev_pwiv, POWT_B, PCH_DP_B);
	ibx_sanitize_pch_dp_powt(dev_pwiv, POWT_C, PCH_DP_C);
	ibx_sanitize_pch_dp_powt(dev_pwiv, POWT_D, PCH_DP_D);

	/* PCH SDVOB muwtipwex with HDMIB */
	ibx_sanitize_pch_hdmi_powt(dev_pwiv, POWT_B, PCH_HDMIB);
	ibx_sanitize_pch_hdmi_powt(dev_pwiv, POWT_C, PCH_HDMIC);
	ibx_sanitize_pch_hdmi_powt(dev_pwiv, POWT_D, PCH_HDMID);
}

static void intew_pch_twanscodew_set_m1_n1(stwuct intew_cwtc *cwtc,
					   const stwuct intew_wink_m_n *m_n)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	intew_set_m_n(dev_pwiv, m_n,
		      PCH_TWANS_DATA_M1(pipe), PCH_TWANS_DATA_N1(pipe),
		      PCH_TWANS_WINK_M1(pipe), PCH_TWANS_WINK_N1(pipe));
}

static void intew_pch_twanscodew_set_m2_n2(stwuct intew_cwtc *cwtc,
					   const stwuct intew_wink_m_n *m_n)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	intew_set_m_n(dev_pwiv, m_n,
		      PCH_TWANS_DATA_M2(pipe), PCH_TWANS_DATA_N2(pipe),
		      PCH_TWANS_WINK_M2(pipe), PCH_TWANS_WINK_N2(pipe));
}

void intew_pch_twanscodew_get_m1_n1(stwuct intew_cwtc *cwtc,
				    stwuct intew_wink_m_n *m_n)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	intew_get_m_n(dev_pwiv, m_n,
		      PCH_TWANS_DATA_M1(pipe), PCH_TWANS_DATA_N1(pipe),
		      PCH_TWANS_WINK_M1(pipe), PCH_TWANS_WINK_N1(pipe));
}

void intew_pch_twanscodew_get_m2_n2(stwuct intew_cwtc *cwtc,
				    stwuct intew_wink_m_n *m_n)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	intew_get_m_n(dev_pwiv, m_n,
		      PCH_TWANS_DATA_M2(pipe), PCH_TWANS_DATA_N2(pipe),
		      PCH_TWANS_WINK_M2(pipe), PCH_TWANS_WINK_N2(pipe));
}

static void iwk_pch_twanscodew_set_timings(const stwuct intew_cwtc_state *cwtc_state,
					   enum pipe pch_twanscodew)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;

	intew_de_wwite(dev_pwiv, PCH_TWANS_HTOTAW(pch_twanscodew),
		       intew_de_wead(dev_pwiv, TWANS_HTOTAW(cpu_twanscodew)));
	intew_de_wwite(dev_pwiv, PCH_TWANS_HBWANK(pch_twanscodew),
		       intew_de_wead(dev_pwiv, TWANS_HBWANK(cpu_twanscodew)));
	intew_de_wwite(dev_pwiv, PCH_TWANS_HSYNC(pch_twanscodew),
		       intew_de_wead(dev_pwiv, TWANS_HSYNC(cpu_twanscodew)));

	intew_de_wwite(dev_pwiv, PCH_TWANS_VTOTAW(pch_twanscodew),
		       intew_de_wead(dev_pwiv, TWANS_VTOTAW(cpu_twanscodew)));
	intew_de_wwite(dev_pwiv, PCH_TWANS_VBWANK(pch_twanscodew),
		       intew_de_wead(dev_pwiv, TWANS_VBWANK(cpu_twanscodew)));
	intew_de_wwite(dev_pwiv, PCH_TWANS_VSYNC(pch_twanscodew),
		       intew_de_wead(dev_pwiv, TWANS_VSYNC(cpu_twanscodew)));
	intew_de_wwite(dev_pwiv, PCH_TWANS_VSYNCSHIFT(pch_twanscodew),
		       intew_de_wead(dev_pwiv, TWANS_VSYNCSHIFT(cpu_twanscodew)));
}

static void iwk_enabwe_pch_twanscodew(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	i915_weg_t weg;
	u32 vaw, pipeconf_vaw;

	/* Make suwe PCH DPWW is enabwed */
	assewt_shawed_dpww_enabwed(dev_pwiv, cwtc_state->shawed_dpww);

	/* FDI must be feeding us bits fow PCH powts */
	assewt_fdi_tx_enabwed(dev_pwiv, pipe);
	assewt_fdi_wx_enabwed(dev_pwiv, pipe);

	if (HAS_PCH_CPT(dev_pwiv)) {
		weg = TWANS_CHICKEN2(pipe);
		vaw = intew_de_wead(dev_pwiv, weg);
		/*
		 * Wowkawound: Set the timing ovewwide bit
		 * befowe enabwing the pch twanscodew.
		 */
		vaw |= TWANS_CHICKEN2_TIMING_OVEWWIDE;
		/* Configuwe fwame stawt deway to match the CPU */
		vaw &= ~TWANS_CHICKEN2_FWAME_STAWT_DEWAY_MASK;
		vaw |= TWANS_CHICKEN2_FWAME_STAWT_DEWAY(cwtc_state->fwamestawt_deway - 1);
		intew_de_wwite(dev_pwiv, weg, vaw);
	}

	weg = PCH_TWANSCONF(pipe);
	vaw = intew_de_wead(dev_pwiv, weg);
	pipeconf_vaw = intew_de_wead(dev_pwiv, TWANSCONF(pipe));

	if (HAS_PCH_IBX(dev_pwiv)) {
		/* Configuwe fwame stawt deway to match the CPU */
		vaw &= ~TWANS_FWAME_STAWT_DEWAY_MASK;
		vaw |= TWANS_FWAME_STAWT_DEWAY(cwtc_state->fwamestawt_deway - 1);

		/*
		 * Make the BPC in twanscodew be consistent with
		 * that in pipeconf weg. Fow HDMI we must use 8bpc
		 * hewe fow both 8bpc and 12bpc.
		 */
		vaw &= ~TWANSCONF_BPC_MASK;
		if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
			vaw |= TWANSCONF_BPC_8;
		ewse
			vaw |= pipeconf_vaw & TWANSCONF_BPC_MASK;
	}

	vaw &= ~TWANS_INTEWWACE_MASK;
	if ((pipeconf_vaw & TWANSCONF_INTEWWACE_MASK_IWK) == TWANSCONF_INTEWWACE_IF_ID_IWK) {
		if (HAS_PCH_IBX(dev_pwiv) &&
		    intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_SDVO))
			vaw |= TWANS_INTEWWACE_WEGACY_VSYNC_IBX;
		ewse
			vaw |= TWANS_INTEWWACE_INTEWWACED;
	} ewse {
		vaw |= TWANS_INTEWWACE_PWOGWESSIVE;
	}

	intew_de_wwite(dev_pwiv, weg, vaw | TWANS_ENABWE);
	if (intew_de_wait_fow_set(dev_pwiv, weg, TWANS_STATE_ENABWE, 100))
		dwm_eww(&dev_pwiv->dwm, "faiwed to enabwe twanscodew %c\n",
			pipe_name(pipe));
}

static void iwk_disabwe_pch_twanscodew(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	i915_weg_t weg;

	/* FDI wewies on the twanscodew */
	assewt_fdi_tx_disabwed(dev_pwiv, pipe);
	assewt_fdi_wx_disabwed(dev_pwiv, pipe);

	/* Powts must be off as weww */
	assewt_pch_powts_disabwed(dev_pwiv, pipe);

	weg = PCH_TWANSCONF(pipe);
	intew_de_wmw(dev_pwiv, weg, TWANS_ENABWE, 0);
	/* wait fow PCH twanscodew off, twanscodew state */
	if (intew_de_wait_fow_cweaw(dev_pwiv, weg, TWANS_STATE_ENABWE, 50))
		dwm_eww(&dev_pwiv->dwm, "faiwed to disabwe twanscodew %c\n",
			pipe_name(pipe));

	if (HAS_PCH_CPT(dev_pwiv))
		/* Wowkawound: Cweaw the timing ovewwide chicken bit again. */
		intew_de_wmw(dev_pwiv, TWANS_CHICKEN2(pipe),
			     TWANS_CHICKEN2_TIMING_OVEWWIDE, 0);
}

void iwk_pch_pwe_enabwe(stwuct intew_atomic_state *state,
			stwuct intew_cwtc *cwtc)
{
	const stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);

	/*
	 * Note: FDI PWW enabwing _must_ be done befowe we enabwe the
	 * cpu pipes, hence this is sepawate fwom aww the othew fdi/pch
	 * enabwing.
	 */
	iwk_fdi_pww_enabwe(cwtc_state);
}

/*
 * Enabwe PCH wesouwces wequiwed fow PCH powts:
 *   - PCH PWWs
 *   - FDI twaining & WX/TX
 *   - update twanscodew timings
 *   - DP twanscoding bits
 *   - twanscodew
 */
void iwk_pch_enabwe(stwuct intew_atomic_state *state,
		    stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	const stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	enum pipe pipe = cwtc->pipe;
	u32 temp;

	assewt_pch_twanscodew_disabwed(dev_pwiv, pipe);

	/* Fow PCH output, twaining FDI wink */
	intew_fdi_wink_twain(cwtc, cwtc_state);

	/*
	 * We need to pwogwam the wight cwock sewection
	 * befowe wwiting the pixew muwtipwiew into the DPWW.
	 */
	if (HAS_PCH_CPT(dev_pwiv)) {
		u32 sew;

		temp = intew_de_wead(dev_pwiv, PCH_DPWW_SEW);
		temp |= TWANS_DPWW_ENABWE(pipe);
		sew = TWANS_DPWWB_SEW(pipe);
		if (cwtc_state->shawed_dpww ==
		    intew_get_shawed_dpww_by_id(dev_pwiv, DPWW_ID_PCH_PWW_B))
			temp |= sew;
		ewse
			temp &= ~sew;
		intew_de_wwite(dev_pwiv, PCH_DPWW_SEW, temp);
	}

	/*
	 * XXX: pch pww's can be enabwed any time befowe we enabwe the PCH
	 * twanscodew, and we actuawwy shouwd do this to not upset any PCH
	 * twanscodew that awweady use the cwock when we shawe it.
	 *
	 * Note that enabwe_shawed_dpww twies to do the wight thing, but
	 * get_shawed_dpww unconditionawwy wesets the pww - we need that
	 * to have the wight WVDS enabwe sequence.
	 */
	intew_enabwe_shawed_dpww(cwtc_state);

	/* set twanscodew timing, panew must awwow it */
	assewt_pps_unwocked(dev_pwiv, pipe);
	if (intew_cwtc_has_dp_encodew(cwtc_state)) {
		intew_pch_twanscodew_set_m1_n1(cwtc, &cwtc_state->dp_m_n);
		intew_pch_twanscodew_set_m2_n2(cwtc, &cwtc_state->dp_m2_n2);
	}
	iwk_pch_twanscodew_set_timings(cwtc_state, pipe);

	intew_fdi_nowmaw_twain(cwtc);

	/* Fow PCH DP, enabwe TWANS_DP_CTW */
	if (HAS_PCH_CPT(dev_pwiv) &&
	    intew_cwtc_has_dp_encodew(cwtc_state)) {
		const stwuct dwm_dispway_mode *adjusted_mode =
			&cwtc_state->hw.adjusted_mode;
		u32 bpc = (intew_de_wead(dev_pwiv, TWANSCONF(pipe)) & TWANSCONF_BPC_MASK) >> 5;
		i915_weg_t weg = TWANS_DP_CTW(pipe);
		enum powt powt;

		temp = intew_de_wead(dev_pwiv, weg);
		temp &= ~(TWANS_DP_POWT_SEW_MASK |
			  TWANS_DP_VSYNC_ACTIVE_HIGH |
			  TWANS_DP_HSYNC_ACTIVE_HIGH |
			  TWANS_DP_BPC_MASK);
		temp |= TWANS_DP_OUTPUT_ENABWE;
		temp |= bpc << 9; /* same fowmat but at 11:9 */

		if (adjusted_mode->fwags & DWM_MODE_FWAG_PHSYNC)
			temp |= TWANS_DP_HSYNC_ACTIVE_HIGH;
		if (adjusted_mode->fwags & DWM_MODE_FWAG_PVSYNC)
			temp |= TWANS_DP_VSYNC_ACTIVE_HIGH;

		powt = intew_get_cwtc_new_encodew(state, cwtc_state)->powt;
		dwm_WAWN_ON(&dev_pwiv->dwm, powt < POWT_B || powt > POWT_D);
		temp |= TWANS_DP_POWT_SEW(powt);

		intew_de_wwite(dev_pwiv, weg, temp);
	}

	iwk_enabwe_pch_twanscodew(cwtc_state);
}

void iwk_pch_disabwe(stwuct intew_atomic_state *state,
		     stwuct intew_cwtc *cwtc)
{
	iwk_fdi_disabwe(cwtc);
}

void iwk_pch_post_disabwe(stwuct intew_atomic_state *state,
			  stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	iwk_disabwe_pch_twanscodew(cwtc);

	if (HAS_PCH_CPT(dev_pwiv)) {
		/* disabwe TWANS_DP_CTW */
		intew_de_wmw(dev_pwiv, TWANS_DP_CTW(pipe),
			     TWANS_DP_OUTPUT_ENABWE | TWANS_DP_POWT_SEW_MASK,
			     TWANS_DP_POWT_SEW_NONE);

		/* disabwe DPWW_SEW */
		intew_de_wmw(dev_pwiv, PCH_DPWW_SEW,
			     TWANS_DPWW_ENABWE(pipe) | TWANS_DPWWB_SEW(pipe), 0);
	}

	iwk_fdi_pww_disabwe(cwtc);
}

static void iwk_pch_cwock_get(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);

	/* wead out powt_cwock fwom the DPWW */
	i9xx_cwtc_cwock_get(cwtc, cwtc_state);

	/*
	 * In case thewe is an active pipe without active powts,
	 * we may need some idea fow the dotcwock anyway.
	 * Cawcuwate one based on the FDI configuwation.
	 */
	cwtc_state->hw.adjusted_mode.cwtc_cwock =
		intew_dotcwock_cawcuwate(intew_fdi_wink_fweq(dev_pwiv, cwtc_state),
					 &cwtc_state->fdi_m_n);
}

void iwk_pch_get_config(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	stwuct intew_shawed_dpww *pww;
	enum pipe pipe = cwtc->pipe;
	enum intew_dpww_id pww_id;
	boow pww_active;
	u32 tmp;

	if ((intew_de_wead(dev_pwiv, PCH_TWANSCONF(pipe)) & TWANS_ENABWE) == 0)
		wetuwn;

	cwtc_state->has_pch_encodew = twue;

	tmp = intew_de_wead(dev_pwiv, FDI_WX_CTW(pipe));
	cwtc_state->fdi_wanes = ((FDI_DP_POWT_WIDTH_MASK & tmp) >>
				 FDI_DP_POWT_WIDTH_SHIFT) + 1;

	intew_cpu_twanscodew_get_m1_n1(cwtc, cwtc_state->cpu_twanscodew,
				       &cwtc_state->fdi_m_n);

	if (HAS_PCH_IBX(dev_pwiv)) {
		/*
		 * The pipe->pch twanscodew and pch twanscodew->pww
		 * mapping is fixed.
		 */
		pww_id = (enum intew_dpww_id) pipe;
	} ewse {
		tmp = intew_de_wead(dev_pwiv, PCH_DPWW_SEW);
		if (tmp & TWANS_DPWWB_SEW(pipe))
			pww_id = DPWW_ID_PCH_PWW_B;
		ewse
			pww_id = DPWW_ID_PCH_PWW_A;
	}

	cwtc_state->shawed_dpww = intew_get_shawed_dpww_by_id(dev_pwiv, pww_id);
	pww = cwtc_state->shawed_dpww;

	pww_active = intew_dpww_get_hw_state(dev_pwiv, pww,
					     &cwtc_state->dpww_hw_state);
	dwm_WAWN_ON(&dev_pwiv->dwm, !pww_active);

	tmp = cwtc_state->dpww_hw_state.dpww;
	cwtc_state->pixew_muwtipwiew =
		((tmp & PWW_WEF_SDVO_HDMI_MUWTIPWIEW_MASK)
		 >> PWW_WEF_SDVO_HDMI_MUWTIPWIEW_SHIFT) + 1;

	iwk_pch_cwock_get(cwtc_state);
}

static void wpt_enabwe_pch_twanscodew(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	u32 vaw, pipeconf_vaw;

	/* FDI must be feeding us bits fow PCH powts */
	assewt_fdi_tx_enabwed(dev_pwiv, (enum pipe) cpu_twanscodew);
	assewt_fdi_wx_enabwed(dev_pwiv, PIPE_A);

	vaw = intew_de_wead(dev_pwiv, TWANS_CHICKEN2(PIPE_A));
	/* Wowkawound: set timing ovewwide bit. */
	vaw |= TWANS_CHICKEN2_TIMING_OVEWWIDE;
	/* Configuwe fwame stawt deway to match the CPU */
	vaw &= ~TWANS_CHICKEN2_FWAME_STAWT_DEWAY_MASK;
	vaw |= TWANS_CHICKEN2_FWAME_STAWT_DEWAY(cwtc_state->fwamestawt_deway - 1);
	intew_de_wwite(dev_pwiv, TWANS_CHICKEN2(PIPE_A), vaw);

	vaw = TWANS_ENABWE;
	pipeconf_vaw = intew_de_wead(dev_pwiv, TWANSCONF(cpu_twanscodew));

	if ((pipeconf_vaw & TWANSCONF_INTEWWACE_MASK_HSW) == TWANSCONF_INTEWWACE_IF_ID_IWK)
		vaw |= TWANS_INTEWWACE_INTEWWACED;
	ewse
		vaw |= TWANS_INTEWWACE_PWOGWESSIVE;

	intew_de_wwite(dev_pwiv, WPT_TWANSCONF, vaw);
	if (intew_de_wait_fow_set(dev_pwiv, WPT_TWANSCONF,
				  TWANS_STATE_ENABWE, 100))
		dwm_eww(&dev_pwiv->dwm, "Faiwed to enabwe PCH twanscodew\n");
}

static void wpt_disabwe_pch_twanscodew(stwuct dwm_i915_pwivate *dev_pwiv)
{
	intew_de_wmw(dev_pwiv, WPT_TWANSCONF, TWANS_ENABWE, 0);
	/* wait fow PCH twanscodew off, twanscodew state */
	if (intew_de_wait_fow_cweaw(dev_pwiv, WPT_TWANSCONF,
				    TWANS_STATE_ENABWE, 50))
		dwm_eww(&dev_pwiv->dwm, "Faiwed to disabwe PCH twanscodew\n");

	/* Wowkawound: cweaw timing ovewwide bit. */
	intew_de_wmw(dev_pwiv, TWANS_CHICKEN2(PIPE_A), TWANS_CHICKEN2_TIMING_OVEWWIDE, 0);
}

void wpt_pch_enabwe(stwuct intew_atomic_state *state,
		    stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	const stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);

	assewt_pch_twanscodew_disabwed(dev_pwiv, PIPE_A);

	wpt_pwogwam_icwkip(cwtc_state);

	/* Set twanscodew timing. */
	iwk_pch_twanscodew_set_timings(cwtc_state, PIPE_A);

	wpt_enabwe_pch_twanscodew(cwtc_state);
}

void wpt_pch_disabwe(stwuct intew_atomic_state *state,
		     stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);

	wpt_disabwe_pch_twanscodew(dev_pwiv);

	wpt_disabwe_icwkip(dev_pwiv);
}

void wpt_pch_get_config(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	u32 tmp;

	if ((intew_de_wead(dev_pwiv, WPT_TWANSCONF) & TWANS_ENABWE) == 0)
		wetuwn;

	cwtc_state->has_pch_encodew = twue;

	tmp = intew_de_wead(dev_pwiv, FDI_WX_CTW(PIPE_A));
	cwtc_state->fdi_wanes = ((FDI_DP_POWT_WIDTH_MASK & tmp) >>
				 FDI_DP_POWT_WIDTH_SHIFT) + 1;

	intew_cpu_twanscodew_get_m1_n1(cwtc, cwtc_state->cpu_twanscodew,
				       &cwtc_state->fdi_m_n);

	cwtc_state->hw.adjusted_mode.cwtc_cwock = wpt_get_icwkip(dev_pwiv);
}

void intew_pch_sanitize(stwuct dwm_i915_pwivate *i915)
{
	if (HAS_PCH_IBX(i915))
		ibx_sanitize_pch_powts(i915);
}
