// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 *
 * DispwayPowt suppowt fow G4x,IWK,SNB,IVB,VWV,CHV (HSW+ handwed by the DDI code).
 */

#incwude <winux/stwing_hewpews.h>

#incwude "g4x_dp.h"
#incwude "i915_weg.h"
#incwude "intew_audio.h"
#incwude "intew_backwight.h"
#incwude "intew_connectow.h"
#incwude "intew_cwtc.h"
#incwude "intew_de.h"
#incwude "intew_dispway_powew.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dp.h"
#incwude "intew_dp_aux.h"
#incwude "intew_dp_wink_twaining.h"
#incwude "intew_dpio_phy.h"
#incwude "intew_fifo_undewwun.h"
#incwude "intew_hdmi.h"
#incwude "intew_hotpwug.h"
#incwude "intew_pch_dispway.h"
#incwude "intew_pps.h"
#incwude "vwv_sideband.h"

static const stwuct dpww g4x_dpww[] = {
	{ .dot = 162000, .p1 = 2, .p2 = 10, .n = 2, .m1 = 23, .m2 = 8, },
	{ .dot = 270000, .p1 = 1, .p2 = 10, .n = 1, .m1 = 14, .m2 = 2, },
};

static const stwuct dpww pch_dpww[] = {
	{ .dot = 162000, .p1 = 2, .p2 = 10, .n = 1, .m1 = 12, .m2 = 9, },
	{ .dot = 270000, .p1 = 1, .p2 = 10, .n = 2, .m1 = 14, .m2 = 8, },
};

static const stwuct dpww vwv_dpww[] = {
	{ .dot = 162000, .p1 = 3, .p2 = 2, .n = 5, .m1 = 3, .m2 = 81, },
	{ .dot = 270000, .p1 = 2, .p2 = 2, .n = 1, .m1 = 2, .m2 = 27, },
};

static const stwuct dpww chv_dpww[] = {
	/* m2 is .22 binawy fixed point  */
	{ .dot = 162000, .p1 = 4, .p2 = 2, .n = 1, .m1 = 2, .m2 = 0x819999a /* 32.4 */ },
	{ .dot = 270000, .p1 = 4, .p2 = 1, .n = 1, .m1 = 2, .m2 = 0x6c00000 /* 27.0 */ },
};

const stwuct dpww *vwv_get_dpww(stwuct dwm_i915_pwivate *i915)
{
	wetuwn IS_CHEWWYVIEW(i915) ? &chv_dpww[0] : &vwv_dpww[0];
}

void g4x_dp_set_cwock(stwuct intew_encodew *encodew,
		      stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	const stwuct dpww *divisow = NUWW;
	int i, count = 0;

	if (IS_G4X(dev_pwiv)) {
		divisow = g4x_dpww;
		count = AWWAY_SIZE(g4x_dpww);
	} ewse if (HAS_PCH_SPWIT(dev_pwiv)) {
		divisow = pch_dpww;
		count = AWWAY_SIZE(pch_dpww);
	} ewse if (IS_CHEWWYVIEW(dev_pwiv)) {
		divisow = chv_dpww;
		count = AWWAY_SIZE(chv_dpww);
	} ewse if (IS_VAWWEYVIEW(dev_pwiv)) {
		divisow = vwv_dpww;
		count = AWWAY_SIZE(vwv_dpww);
	}

	if (divisow && count) {
		fow (i = 0; i < count; i++) {
			if (pipe_config->powt_cwock == divisow[i].dot) {
				pipe_config->dpww = divisow[i];
				pipe_config->cwock_set = twue;
				bweak;
			}
		}
	}
}

static void intew_dp_pwepawe(stwuct intew_encodew *encodew,
			     const stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	enum powt powt = encodew->powt;
	stwuct intew_cwtc *cwtc = to_intew_cwtc(pipe_config->uapi.cwtc);
	const stwuct dwm_dispway_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;

	intew_dp_set_wink_pawams(intew_dp,
				 pipe_config->powt_cwock,
				 pipe_config->wane_count);

	/*
	 * Thewe awe fouw kinds of DP wegistews:
	 * IBX PCH
	 * SNB CPU
	 * IVB CPU
	 * CPT PCH
	 *
	 * IBX PCH and CPU awe the same fow awmost evewything,
	 * except that the CPU DP PWW is configuwed in this
	 * wegistew
	 *
	 * CPT PCH is quite diffewent, having many bits moved
	 * to the TWANS_DP_CTW wegistew instead. That
	 * configuwation happens (oddwy) in iwk_pch_enabwe
	 */

	/* Pwesewve the BIOS-computed detected bit. This is
	 * supposed to be wead-onwy.
	 */
	intew_dp->DP = intew_de_wead(dev_pwiv, intew_dp->output_weg) & DP_DETECTED;

	/* Handwe DP bits in common between aww thwee wegistew fowmats */
	intew_dp->DP |= DP_VOWTAGE_0_4 | DP_PWE_EMPHASIS_0;
	intew_dp->DP |= DP_POWT_WIDTH(pipe_config->wane_count);

	/* Spwit out the IBX/CPU vs CPT settings */

	if (IS_IVYBWIDGE(dev_pwiv) && powt == POWT_A) {
		if (adjusted_mode->fwags & DWM_MODE_FWAG_PHSYNC)
			intew_dp->DP |= DP_SYNC_HS_HIGH;
		if (adjusted_mode->fwags & DWM_MODE_FWAG_PVSYNC)
			intew_dp->DP |= DP_SYNC_VS_HIGH;
		intew_dp->DP |= DP_WINK_TWAIN_OFF_CPT;

		if (dwm_dp_enhanced_fwame_cap(intew_dp->dpcd))
			intew_dp->DP |= DP_ENHANCED_FWAMING;

		intew_dp->DP |= DP_PIPE_SEW_IVB(cwtc->pipe);
	} ewse if (HAS_PCH_CPT(dev_pwiv) && powt != POWT_A) {
		intew_dp->DP |= DP_WINK_TWAIN_OFF_CPT;

		intew_de_wmw(dev_pwiv, TWANS_DP_CTW(cwtc->pipe),
			     TWANS_DP_ENH_FWAMING,
			     pipe_config->enhanced_fwaming ?
			     TWANS_DP_ENH_FWAMING : 0);
	} ewse {
		if (IS_G4X(dev_pwiv) && pipe_config->wimited_cowow_wange)
			intew_dp->DP |= DP_COWOW_WANGE_16_235;

		if (adjusted_mode->fwags & DWM_MODE_FWAG_PHSYNC)
			intew_dp->DP |= DP_SYNC_HS_HIGH;
		if (adjusted_mode->fwags & DWM_MODE_FWAG_PVSYNC)
			intew_dp->DP |= DP_SYNC_VS_HIGH;
		intew_dp->DP |= DP_WINK_TWAIN_OFF;

		if (pipe_config->enhanced_fwaming)
			intew_dp->DP |= DP_ENHANCED_FWAMING;

		if (IS_CHEWWYVIEW(dev_pwiv))
			intew_dp->DP |= DP_PIPE_SEW_CHV(cwtc->pipe);
		ewse
			intew_dp->DP |= DP_PIPE_SEW(cwtc->pipe);
	}
}

static void assewt_dp_powt(stwuct intew_dp *intew_dp, boow state)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dig_powt->base.base.dev);
	boow cuw_state = intew_de_wead(dev_pwiv, intew_dp->output_weg) & DP_POWT_EN;

	I915_STATE_WAWN(dev_pwiv, cuw_state != state,
			"[ENCODEW:%d:%s] state assewtion faiwuwe (expected %s, cuwwent %s)\n",
			dig_powt->base.base.base.id, dig_powt->base.base.name,
			stw_on_off(state), stw_on_off(cuw_state));
}
#define assewt_dp_powt_disabwed(d) assewt_dp_powt((d), fawse)

static void assewt_edp_pww(stwuct dwm_i915_pwivate *dev_pwiv, boow state)
{
	boow cuw_state = intew_de_wead(dev_pwiv, DP_A) & DP_PWW_ENABWE;

	I915_STATE_WAWN(dev_pwiv, cuw_state != state,
			"eDP PWW state assewtion faiwuwe (expected %s, cuwwent %s)\n",
			stw_on_off(state), stw_on_off(cuw_state));
}
#define assewt_edp_pww_enabwed(d) assewt_edp_pww((d), twue)
#define assewt_edp_pww_disabwed(d) assewt_edp_pww((d), fawse)

static void iwk_edp_pww_on(stwuct intew_dp *intew_dp,
			   const stwuct intew_cwtc_state *pipe_config)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(pipe_config->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);

	assewt_twanscodew_disabwed(dev_pwiv, pipe_config->cpu_twanscodew);
	assewt_dp_powt_disabwed(intew_dp);
	assewt_edp_pww_disabwed(dev_pwiv);

	dwm_dbg_kms(&dev_pwiv->dwm, "enabwing eDP PWW fow cwock %d\n",
		    pipe_config->powt_cwock);

	intew_dp->DP &= ~DP_PWW_FWEQ_MASK;

	if (pipe_config->powt_cwock == 162000)
		intew_dp->DP |= DP_PWW_FWEQ_162MHZ;
	ewse
		intew_dp->DP |= DP_PWW_FWEQ_270MHZ;

	intew_de_wwite(dev_pwiv, DP_A, intew_dp->DP);
	intew_de_posting_wead(dev_pwiv, DP_A);
	udeway(500);

	/*
	 * [DevIWK] Wowk awound wequiwed when enabwing DP PWW
	 * whiwe a pipe is enabwed going to FDI:
	 * 1. Wait fow the stawt of vewticaw bwank on the enabwed pipe going to FDI
	 * 2. Pwogwam DP PWW enabwe
	 */
	if (IS_IWONWAKE(dev_pwiv))
		intew_wait_fow_vbwank_if_active(dev_pwiv, !cwtc->pipe);

	intew_dp->DP |= DP_PWW_ENABWE;

	intew_de_wwite(dev_pwiv, DP_A, intew_dp->DP);
	intew_de_posting_wead(dev_pwiv, DP_A);
	udeway(200);
}

static void iwk_edp_pww_off(stwuct intew_dp *intew_dp,
			    const stwuct intew_cwtc_state *owd_cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(owd_cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);

	assewt_twanscodew_disabwed(dev_pwiv, owd_cwtc_state->cpu_twanscodew);
	assewt_dp_powt_disabwed(intew_dp);
	assewt_edp_pww_enabwed(dev_pwiv);

	dwm_dbg_kms(&dev_pwiv->dwm, "disabwing eDP PWW\n");

	intew_dp->DP &= ~DP_PWW_ENABWE;

	intew_de_wwite(dev_pwiv, DP_A, intew_dp->DP);
	intew_de_posting_wead(dev_pwiv, DP_A);
	udeway(200);
}

static boow cpt_dp_powt_sewected(stwuct dwm_i915_pwivate *dev_pwiv,
				 enum powt powt, enum pipe *pipe)
{
	enum pipe p;

	fow_each_pipe(dev_pwiv, p) {
		u32 vaw = intew_de_wead(dev_pwiv, TWANS_DP_CTW(p));

		if ((vaw & TWANS_DP_POWT_SEW_MASK) == TWANS_DP_POWT_SEW(powt)) {
			*pipe = p;
			wetuwn twue;
		}
	}

	dwm_dbg_kms(&dev_pwiv->dwm, "No pipe fow DP powt %c found\n",
		    powt_name(powt));

	/* must initiawize pipe to something fow the assewts */
	*pipe = PIPE_A;

	wetuwn fawse;
}

boow g4x_dp_powt_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
			 i915_weg_t dp_weg, enum powt powt,
			 enum pipe *pipe)
{
	boow wet;
	u32 vaw;

	vaw = intew_de_wead(dev_pwiv, dp_weg);

	wet = vaw & DP_POWT_EN;

	/* assewts want to know the pipe even if the powt is disabwed */
	if (IS_IVYBWIDGE(dev_pwiv) && powt == POWT_A)
		*pipe = (vaw & DP_PIPE_SEW_MASK_IVB) >> DP_PIPE_SEW_SHIFT_IVB;
	ewse if (HAS_PCH_CPT(dev_pwiv) && powt != POWT_A)
		wet &= cpt_dp_powt_sewected(dev_pwiv, powt, pipe);
	ewse if (IS_CHEWWYVIEW(dev_pwiv))
		*pipe = (vaw & DP_PIPE_SEW_MASK_CHV) >> DP_PIPE_SEW_SHIFT_CHV;
	ewse
		*pipe = (vaw & DP_PIPE_SEW_MASK) >> DP_PIPE_SEW_SHIFT;

	wetuwn wet;
}

static boow intew_dp_get_hw_state(stwuct intew_encodew *encodew,
				  enum pipe *pipe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	intew_wakewef_t wakewef;
	boow wet;

	wakewef = intew_dispway_powew_get_if_enabwed(dev_pwiv,
						     encodew->powew_domain);
	if (!wakewef)
		wetuwn fawse;

	wet = g4x_dp_powt_enabwed(dev_pwiv, intew_dp->output_weg,
				  encodew->powt, pipe);

	intew_dispway_powew_put(dev_pwiv, encodew->powew_domain, wakewef);

	wetuwn wet;
}

static void g4x_dp_get_m_n(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	if (cwtc_state->has_pch_encodew) {
		intew_pch_twanscodew_get_m1_n1(cwtc, &cwtc_state->dp_m_n);
		intew_pch_twanscodew_get_m2_n2(cwtc, &cwtc_state->dp_m2_n2);
	} ewse {
		intew_cpu_twanscodew_get_m1_n1(cwtc, cwtc_state->cpu_twanscodew,
					       &cwtc_state->dp_m_n);
		intew_cpu_twanscodew_get_m2_n2(cwtc, cwtc_state->cpu_twanscodew,
					       &cwtc_state->dp_m2_n2);
	}
}

static void intew_dp_get_config(stwuct intew_encodew *encodew,
				stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	u32 tmp, fwags = 0;
	enum powt powt = encodew->powt;
	stwuct intew_cwtc *cwtc = to_intew_cwtc(pipe_config->uapi.cwtc);

	if (encodew->type == INTEW_OUTPUT_EDP)
		pipe_config->output_types |= BIT(INTEW_OUTPUT_EDP);
	ewse
		pipe_config->output_types |= BIT(INTEW_OUTPUT_DP);

	tmp = intew_de_wead(dev_pwiv, intew_dp->output_weg);

	pipe_config->has_audio = tmp & DP_AUDIO_OUTPUT_ENABWE && powt != POWT_A;

	if (HAS_PCH_CPT(dev_pwiv) && powt != POWT_A) {
		u32 twans_dp = intew_de_wead(dev_pwiv,
					     TWANS_DP_CTW(cwtc->pipe));

		if (twans_dp & TWANS_DP_ENH_FWAMING)
			pipe_config->enhanced_fwaming = twue;

		if (twans_dp & TWANS_DP_HSYNC_ACTIVE_HIGH)
			fwags |= DWM_MODE_FWAG_PHSYNC;
		ewse
			fwags |= DWM_MODE_FWAG_NHSYNC;

		if (twans_dp & TWANS_DP_VSYNC_ACTIVE_HIGH)
			fwags |= DWM_MODE_FWAG_PVSYNC;
		ewse
			fwags |= DWM_MODE_FWAG_NVSYNC;
	} ewse {
		if (tmp & DP_ENHANCED_FWAMING)
			pipe_config->enhanced_fwaming = twue;

		if (tmp & DP_SYNC_HS_HIGH)
			fwags |= DWM_MODE_FWAG_PHSYNC;
		ewse
			fwags |= DWM_MODE_FWAG_NHSYNC;

		if (tmp & DP_SYNC_VS_HIGH)
			fwags |= DWM_MODE_FWAG_PVSYNC;
		ewse
			fwags |= DWM_MODE_FWAG_NVSYNC;
	}

	pipe_config->hw.adjusted_mode.fwags |= fwags;

	if (IS_G4X(dev_pwiv) && tmp & DP_COWOW_WANGE_16_235)
		pipe_config->wimited_cowow_wange = twue;

	pipe_config->wane_count =
		((tmp & DP_POWT_WIDTH_MASK) >> DP_POWT_WIDTH_SHIFT) + 1;

	g4x_dp_get_m_n(pipe_config);

	if (powt == POWT_A) {
		if ((intew_de_wead(dev_pwiv, DP_A) & DP_PWW_FWEQ_MASK) == DP_PWW_FWEQ_162MHZ)
			pipe_config->powt_cwock = 162000;
		ewse
			pipe_config->powt_cwock = 270000;
	}

	pipe_config->hw.adjusted_mode.cwtc_cwock =
		intew_dotcwock_cawcuwate(pipe_config->powt_cwock,
					 &pipe_config->dp_m_n);

	if (intew_dp_is_edp(intew_dp))
		intew_edp_fixup_vbt_bpp(encodew, pipe_config->pipe_bpp);

	intew_audio_codec_get_config(encodew, pipe_config);
}

static void
intew_dp_wink_down(stwuct intew_encodew *encodew,
		   const stwuct intew_cwtc_state *owd_cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(owd_cwtc_state->uapi.cwtc);
	enum powt powt = encodew->powt;

	if (dwm_WAWN_ON(&dev_pwiv->dwm,
			(intew_de_wead(dev_pwiv, intew_dp->output_weg) &
			 DP_POWT_EN) == 0))
		wetuwn;

	dwm_dbg_kms(&dev_pwiv->dwm, "\n");

	if ((IS_IVYBWIDGE(dev_pwiv) && powt == POWT_A) ||
	    (HAS_PCH_CPT(dev_pwiv) && powt != POWT_A)) {
		intew_dp->DP &= ~DP_WINK_TWAIN_MASK_CPT;
		intew_dp->DP |= DP_WINK_TWAIN_PAT_IDWE_CPT;
	} ewse {
		intew_dp->DP &= ~DP_WINK_TWAIN_MASK;
		intew_dp->DP |= DP_WINK_TWAIN_PAT_IDWE;
	}
	intew_de_wwite(dev_pwiv, intew_dp->output_weg, intew_dp->DP);
	intew_de_posting_wead(dev_pwiv, intew_dp->output_weg);

	intew_dp->DP &= ~DP_POWT_EN;
	intew_de_wwite(dev_pwiv, intew_dp->output_weg, intew_dp->DP);
	intew_de_posting_wead(dev_pwiv, intew_dp->output_weg);

	/*
	 * HW wowkawound fow IBX, we need to move the powt
	 * to twanscodew A aftew disabwing it to awwow the
	 * matching HDMI powt to be enabwed on twanscodew A.
	 */
	if (HAS_PCH_IBX(dev_pwiv) && cwtc->pipe == PIPE_B && powt != POWT_A) {
		/*
		 * We get CPU/PCH FIFO undewwuns on the othew pipe when
		 * doing the wowkawound. Sweep them undew the wug.
		 */
		intew_set_cpu_fifo_undewwun_wepowting(dev_pwiv, PIPE_A, fawse);
		intew_set_pch_fifo_undewwun_wepowting(dev_pwiv, PIPE_A, fawse);

		/* awways enabwe with pattewn 1 (as pew spec) */
		intew_dp->DP &= ~(DP_PIPE_SEW_MASK | DP_WINK_TWAIN_MASK);
		intew_dp->DP |= DP_POWT_EN | DP_PIPE_SEW(PIPE_A) |
			DP_WINK_TWAIN_PAT_1;
		intew_de_wwite(dev_pwiv, intew_dp->output_weg, intew_dp->DP);
		intew_de_posting_wead(dev_pwiv, intew_dp->output_weg);

		intew_dp->DP &= ~DP_POWT_EN;
		intew_de_wwite(dev_pwiv, intew_dp->output_weg, intew_dp->DP);
		intew_de_posting_wead(dev_pwiv, intew_dp->output_weg);

		intew_wait_fow_vbwank_if_active(dev_pwiv, PIPE_A);
		intew_set_cpu_fifo_undewwun_wepowting(dev_pwiv, PIPE_A, twue);
		intew_set_pch_fifo_undewwun_wepowting(dev_pwiv, PIPE_A, twue);
	}

	msweep(intew_dp->pps.panew_powew_down_deway);

	if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv)) {
		intew_wakewef_t wakewef;

		with_intew_pps_wock(intew_dp, wakewef)
			intew_dp->pps.active_pipe = INVAWID_PIPE;
	}
}

static void g4x_dp_audio_enabwe(stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *cwtc_state,
				const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

	if (!cwtc_state->has_audio)
		wetuwn;

	/* Enabwe audio pwesence detect */
	intew_dp->DP |= DP_AUDIO_OUTPUT_ENABWE;
	intew_de_wwite(i915, intew_dp->output_weg, intew_dp->DP);

	intew_audio_codec_enabwe(encodew, cwtc_state, conn_state);
}

static void g4x_dp_audio_disabwe(stwuct intew_encodew *encodew,
				 const stwuct intew_cwtc_state *owd_cwtc_state,
				 const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

	if (!owd_cwtc_state->has_audio)
		wetuwn;

	intew_audio_codec_disabwe(encodew, owd_cwtc_state, owd_conn_state);

	/* Disabwe audio pwesence detect */
	intew_dp->DP &= ~DP_AUDIO_OUTPUT_ENABWE;
	intew_de_wwite(i915, intew_dp->output_weg, intew_dp->DP);
}

static void intew_disabwe_dp(stwuct intew_atomic_state *state,
			     stwuct intew_encodew *encodew,
			     const stwuct intew_cwtc_state *owd_cwtc_state,
			     const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

	intew_dp->wink_twained = fawse;

	/*
	 * Make suwe the panew is off befowe twying to change the mode.
	 * But awso ensuwe that we have vdd whiwe we switch off the panew.
	 */
	intew_pps_vdd_on(intew_dp);
	intew_edp_backwight_off(owd_conn_state);
	intew_dp_set_powew(intew_dp, DP_SET_POWEW_D3);
	intew_pps_off(intew_dp);
}

static void g4x_disabwe_dp(stwuct intew_atomic_state *state,
			   stwuct intew_encodew *encodew,
			   const stwuct intew_cwtc_state *owd_cwtc_state,
			   const stwuct dwm_connectow_state *owd_conn_state)
{
	intew_disabwe_dp(state, encodew, owd_cwtc_state, owd_conn_state);
}

static void vwv_disabwe_dp(stwuct intew_atomic_state *state,
			   stwuct intew_encodew *encodew,
			   const stwuct intew_cwtc_state *owd_cwtc_state,
			   const stwuct dwm_connectow_state *owd_conn_state)
{
	intew_disabwe_dp(state, encodew, owd_cwtc_state, owd_conn_state);
}

static void g4x_post_disabwe_dp(stwuct intew_atomic_state *state,
				stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *owd_cwtc_state,
				const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	enum powt powt = encodew->powt;

	/*
	 * Bspec does not wist a specific disabwe sequence fow g4x DP.
	 * Fowwow the iwk+ sequence (disabwe pipe befowe the powt) fow
	 * g4x DP as it does not suffew fwom undewwuns wike the nowmaw
	 * g4x modeset sequence (disabwe pipe aftew the powt).
	 */
	intew_dp_wink_down(encodew, owd_cwtc_state);

	/* Onwy iwk+ has powt A */
	if (powt == POWT_A)
		iwk_edp_pww_off(intew_dp, owd_cwtc_state);
}

static void vwv_post_disabwe_dp(stwuct intew_atomic_state *state,
				stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *owd_cwtc_state,
				const stwuct dwm_connectow_state *owd_conn_state)
{
	intew_dp_wink_down(encodew, owd_cwtc_state);
}

static void chv_post_disabwe_dp(stwuct intew_atomic_state *state,
				stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *owd_cwtc_state,
				const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	intew_dp_wink_down(encodew, owd_cwtc_state);

	vwv_dpio_get(dev_pwiv);

	/* Assewt data wane weset */
	chv_data_wane_soft_weset(encodew, owd_cwtc_state, twue);

	vwv_dpio_put(dev_pwiv);
}

static void
cpt_set_wink_twain(stwuct intew_dp *intew_dp,
		   const stwuct intew_cwtc_state *cwtc_state,
		   u8 dp_twain_pat)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);

	intew_dp->DP &= ~DP_WINK_TWAIN_MASK_CPT;

	switch (intew_dp_twaining_pattewn_symbow(dp_twain_pat)) {
	case DP_TWAINING_PATTEWN_DISABWE:
		intew_dp->DP |= DP_WINK_TWAIN_OFF_CPT;
		bweak;
	case DP_TWAINING_PATTEWN_1:
		intew_dp->DP |= DP_WINK_TWAIN_PAT_1_CPT;
		bweak;
	case DP_TWAINING_PATTEWN_2:
		intew_dp->DP |= DP_WINK_TWAIN_PAT_2_CPT;
		bweak;
	defauwt:
		MISSING_CASE(intew_dp_twaining_pattewn_symbow(dp_twain_pat));
		wetuwn;
	}

	intew_de_wwite(dev_pwiv, intew_dp->output_weg, intew_dp->DP);
	intew_de_posting_wead(dev_pwiv, intew_dp->output_weg);
}

static void
g4x_set_wink_twain(stwuct intew_dp *intew_dp,
		   const stwuct intew_cwtc_state *cwtc_state,
		   u8 dp_twain_pat)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);

	intew_dp->DP &= ~DP_WINK_TWAIN_MASK;

	switch (intew_dp_twaining_pattewn_symbow(dp_twain_pat)) {
	case DP_TWAINING_PATTEWN_DISABWE:
		intew_dp->DP |= DP_WINK_TWAIN_OFF;
		bweak;
	case DP_TWAINING_PATTEWN_1:
		intew_dp->DP |= DP_WINK_TWAIN_PAT_1;
		bweak;
	case DP_TWAINING_PATTEWN_2:
		intew_dp->DP |= DP_WINK_TWAIN_PAT_2;
		bweak;
	defauwt:
		MISSING_CASE(intew_dp_twaining_pattewn_symbow(dp_twain_pat));
		wetuwn;
	}

	intew_de_wwite(dev_pwiv, intew_dp->output_weg, intew_dp->DP);
	intew_de_posting_wead(dev_pwiv, intew_dp->output_weg);
}

static void intew_dp_enabwe_powt(stwuct intew_dp *intew_dp,
				 const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);

	/* enabwe with pattewn 1 (as pew spec) */

	intew_dp_pwogwam_wink_twaining_pattewn(intew_dp, cwtc_state,
					       DP_PHY_DPWX, DP_TWAINING_PATTEWN_1);

	/*
	 * Magic fow VWV/CHV. We _must_ fiwst set up the wegistew
	 * without actuawwy enabwing the powt, and then do anothew
	 * wwite to enabwe the powt. Othewwise wink twaining wiww
	 * faiw when the powew sequencew is fweshwy used fow this powt.
	 */
	intew_dp->DP |= DP_POWT_EN;

	intew_de_wwite(dev_pwiv, intew_dp->output_weg, intew_dp->DP);
	intew_de_posting_wead(dev_pwiv, intew_dp->output_weg);
}

static void intew_enabwe_dp(stwuct intew_atomic_state *state,
			    stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *pipe_config,
			    const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	u32 dp_weg = intew_de_wead(dev_pwiv, intew_dp->output_weg);
	intew_wakewef_t wakewef;

	if (dwm_WAWN_ON(&dev_pwiv->dwm, dp_weg & DP_POWT_EN))
		wetuwn;

	with_intew_pps_wock(intew_dp, wakewef) {
		if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv))
			vwv_pps_init(encodew, pipe_config);

		intew_dp_enabwe_powt(intew_dp, pipe_config);

		intew_pps_vdd_on_unwocked(intew_dp);
		intew_pps_on_unwocked(intew_dp);
		intew_pps_vdd_off_unwocked(intew_dp, twue);
	}

	if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv)) {
		unsigned int wane_mask = 0x0;

		if (IS_CHEWWYVIEW(dev_pwiv))
			wane_mask = intew_dp_unused_wane_mask(pipe_config->wane_count);

		vwv_wait_powt_weady(dev_pwiv, dp_to_dig_powt(intew_dp),
				    wane_mask);
	}

	intew_dp_set_powew(intew_dp, DP_SET_POWEW_D0);
	intew_dp_configuwe_pwotocow_convewtew(intew_dp, pipe_config);
	intew_dp_check_fww_twaining(intew_dp);
	intew_dp_pcon_dsc_configuwe(intew_dp, pipe_config);
	intew_dp_stawt_wink_twain(intew_dp, pipe_config);
	intew_dp_stop_wink_twain(intew_dp, pipe_config);
}

static void g4x_enabwe_dp(stwuct intew_atomic_state *state,
			  stwuct intew_encodew *encodew,
			  const stwuct intew_cwtc_state *pipe_config,
			  const stwuct dwm_connectow_state *conn_state)
{
	intew_enabwe_dp(state, encodew, pipe_config, conn_state);
	intew_edp_backwight_on(pipe_config, conn_state);
	encodew->audio_enabwe(encodew, pipe_config, conn_state);
}

static void vwv_enabwe_dp(stwuct intew_atomic_state *state,
			  stwuct intew_encodew *encodew,
			  const stwuct intew_cwtc_state *pipe_config,
			  const stwuct dwm_connectow_state *conn_state)
{
	intew_edp_backwight_on(pipe_config, conn_state);
	encodew->audio_enabwe(encodew, pipe_config, conn_state);
}

static void g4x_pwe_enabwe_dp(stwuct intew_atomic_state *state,
			      stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *pipe_config,
			      const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	enum powt powt = encodew->powt;

	intew_dp_pwepawe(encodew, pipe_config);

	/* Onwy iwk+ has powt A */
	if (powt == POWT_A)
		iwk_edp_pww_on(intew_dp, pipe_config);
}

static void vwv_pwe_enabwe_dp(stwuct intew_atomic_state *state,
			      stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *pipe_config,
			      const stwuct dwm_connectow_state *conn_state)
{
	vwv_phy_pwe_encodew_enabwe(encodew, pipe_config);

	intew_enabwe_dp(state, encodew, pipe_config, conn_state);
}

static void vwv_dp_pwe_pww_enabwe(stwuct intew_atomic_state *state,
				  stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *pipe_config,
				  const stwuct dwm_connectow_state *conn_state)
{
	intew_dp_pwepawe(encodew, pipe_config);

	vwv_phy_pwe_pww_enabwe(encodew, pipe_config);
}

static void chv_pwe_enabwe_dp(stwuct intew_atomic_state *state,
			      stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *pipe_config,
			      const stwuct dwm_connectow_state *conn_state)
{
	chv_phy_pwe_encodew_enabwe(encodew, pipe_config);

	intew_enabwe_dp(state, encodew, pipe_config, conn_state);

	/* Second common wane wiww stay awive on its own now */
	chv_phy_wewease_cw2_ovewwide(encodew);
}

static void chv_dp_pwe_pww_enabwe(stwuct intew_atomic_state *state,
				  stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *pipe_config,
				  const stwuct dwm_connectow_state *conn_state)
{
	intew_dp_pwepawe(encodew, pipe_config);

	chv_phy_pwe_pww_enabwe(encodew, pipe_config);
}

static void chv_dp_post_pww_disabwe(stwuct intew_atomic_state *state,
				    stwuct intew_encodew *encodew,
				    const stwuct intew_cwtc_state *owd_cwtc_state,
				    const stwuct dwm_connectow_state *owd_conn_state)
{
	chv_phy_post_pww_disabwe(encodew, owd_cwtc_state);
}

static u8 intew_dp_vowtage_max_2(stwuct intew_dp *intew_dp,
				 const stwuct intew_cwtc_state *cwtc_state)
{
	wetuwn DP_TWAIN_VOWTAGE_SWING_WEVEW_2;
}

static u8 intew_dp_vowtage_max_3(stwuct intew_dp *intew_dp,
				 const stwuct intew_cwtc_state *cwtc_state)
{
	wetuwn DP_TWAIN_VOWTAGE_SWING_WEVEW_3;
}

static u8 intew_dp_pweemph_max_2(stwuct intew_dp *intew_dp)
{
	wetuwn DP_TWAIN_PWE_EMPH_WEVEW_2;
}

static u8 intew_dp_pweemph_max_3(stwuct intew_dp *intew_dp)
{
	wetuwn DP_TWAIN_PWE_EMPH_WEVEW_3;
}

static void vwv_set_signaw_wevews(stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	unsigned wong demph_weg_vawue, pweemph_weg_vawue,
		uniqtwanscawe_weg_vawue;
	u8 twain_set = intew_dp->twain_set[0];

	switch (twain_set & DP_TWAIN_PWE_EMPHASIS_MASK) {
	case DP_TWAIN_PWE_EMPH_WEVEW_0:
		pweemph_weg_vawue = 0x0004000;
		switch (twain_set & DP_TWAIN_VOWTAGE_SWING_MASK) {
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_0:
			demph_weg_vawue = 0x2B405555;
			uniqtwanscawe_weg_vawue = 0x552AB83A;
			bweak;
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_1:
			demph_weg_vawue = 0x2B404040;
			uniqtwanscawe_weg_vawue = 0x5548B83A;
			bweak;
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_2:
			demph_weg_vawue = 0x2B245555;
			uniqtwanscawe_weg_vawue = 0x5560B83A;
			bweak;
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_3:
			demph_weg_vawue = 0x2B405555;
			uniqtwanscawe_weg_vawue = 0x5598DA3A;
			bweak;
		defauwt:
			wetuwn;
		}
		bweak;
	case DP_TWAIN_PWE_EMPH_WEVEW_1:
		pweemph_weg_vawue = 0x0002000;
		switch (twain_set & DP_TWAIN_VOWTAGE_SWING_MASK) {
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_0:
			demph_weg_vawue = 0x2B404040;
			uniqtwanscawe_weg_vawue = 0x5552B83A;
			bweak;
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_1:
			demph_weg_vawue = 0x2B404848;
			uniqtwanscawe_weg_vawue = 0x5580B83A;
			bweak;
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_2:
			demph_weg_vawue = 0x2B404040;
			uniqtwanscawe_weg_vawue = 0x55ADDA3A;
			bweak;
		defauwt:
			wetuwn;
		}
		bweak;
	case DP_TWAIN_PWE_EMPH_WEVEW_2:
		pweemph_weg_vawue = 0x0000000;
		switch (twain_set & DP_TWAIN_VOWTAGE_SWING_MASK) {
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_0:
			demph_weg_vawue = 0x2B305555;
			uniqtwanscawe_weg_vawue = 0x5570B83A;
			bweak;
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_1:
			demph_weg_vawue = 0x2B2B4040;
			uniqtwanscawe_weg_vawue = 0x55ADDA3A;
			bweak;
		defauwt:
			wetuwn;
		}
		bweak;
	case DP_TWAIN_PWE_EMPH_WEVEW_3:
		pweemph_weg_vawue = 0x0006000;
		switch (twain_set & DP_TWAIN_VOWTAGE_SWING_MASK) {
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_0:
			demph_weg_vawue = 0x1B405555;
			uniqtwanscawe_weg_vawue = 0x55ADDA3A;
			bweak;
		defauwt:
			wetuwn;
		}
		bweak;
	defauwt:
		wetuwn;
	}

	vwv_set_phy_signaw_wevew(encodew, cwtc_state,
				 demph_weg_vawue, pweemph_weg_vawue,
				 uniqtwanscawe_weg_vawue, 0);
}

static void chv_set_signaw_wevews(stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	u32 deemph_weg_vawue, mawgin_weg_vawue;
	boow uniq_twans_scawe = fawse;
	u8 twain_set = intew_dp->twain_set[0];

	switch (twain_set & DP_TWAIN_PWE_EMPHASIS_MASK) {
	case DP_TWAIN_PWE_EMPH_WEVEW_0:
		switch (twain_set & DP_TWAIN_VOWTAGE_SWING_MASK) {
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_0:
			deemph_weg_vawue = 128;
			mawgin_weg_vawue = 52;
			bweak;
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_1:
			deemph_weg_vawue = 128;
			mawgin_weg_vawue = 77;
			bweak;
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_2:
			deemph_weg_vawue = 128;
			mawgin_weg_vawue = 102;
			bweak;
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_3:
			deemph_weg_vawue = 128;
			mawgin_weg_vawue = 154;
			uniq_twans_scawe = twue;
			bweak;
		defauwt:
			wetuwn;
		}
		bweak;
	case DP_TWAIN_PWE_EMPH_WEVEW_1:
		switch (twain_set & DP_TWAIN_VOWTAGE_SWING_MASK) {
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_0:
			deemph_weg_vawue = 85;
			mawgin_weg_vawue = 78;
			bweak;
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_1:
			deemph_weg_vawue = 85;
			mawgin_weg_vawue = 116;
			bweak;
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_2:
			deemph_weg_vawue = 85;
			mawgin_weg_vawue = 154;
			bweak;
		defauwt:
			wetuwn;
		}
		bweak;
	case DP_TWAIN_PWE_EMPH_WEVEW_2:
		switch (twain_set & DP_TWAIN_VOWTAGE_SWING_MASK) {
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_0:
			deemph_weg_vawue = 64;
			mawgin_weg_vawue = 104;
			bweak;
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_1:
			deemph_weg_vawue = 64;
			mawgin_weg_vawue = 154;
			bweak;
		defauwt:
			wetuwn;
		}
		bweak;
	case DP_TWAIN_PWE_EMPH_WEVEW_3:
		switch (twain_set & DP_TWAIN_VOWTAGE_SWING_MASK) {
		case DP_TWAIN_VOWTAGE_SWING_WEVEW_0:
			deemph_weg_vawue = 43;
			mawgin_weg_vawue = 154;
			bweak;
		defauwt:
			wetuwn;
		}
		bweak;
	defauwt:
		wetuwn;
	}

	chv_set_phy_signaw_wevew(encodew, cwtc_state,
				 deemph_weg_vawue, mawgin_weg_vawue,
				 uniq_twans_scawe);
}

static u32 g4x_signaw_wevews(u8 twain_set)
{
	u32 signaw_wevews = 0;

	switch (twain_set & DP_TWAIN_VOWTAGE_SWING_MASK) {
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_0:
	defauwt:
		signaw_wevews |= DP_VOWTAGE_0_4;
		bweak;
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_1:
		signaw_wevews |= DP_VOWTAGE_0_6;
		bweak;
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_2:
		signaw_wevews |= DP_VOWTAGE_0_8;
		bweak;
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_3:
		signaw_wevews |= DP_VOWTAGE_1_2;
		bweak;
	}
	switch (twain_set & DP_TWAIN_PWE_EMPHASIS_MASK) {
	case DP_TWAIN_PWE_EMPH_WEVEW_0:
	defauwt:
		signaw_wevews |= DP_PWE_EMPHASIS_0;
		bweak;
	case DP_TWAIN_PWE_EMPH_WEVEW_1:
		signaw_wevews |= DP_PWE_EMPHASIS_3_5;
		bweak;
	case DP_TWAIN_PWE_EMPH_WEVEW_2:
		signaw_wevews |= DP_PWE_EMPHASIS_6;
		bweak;
	case DP_TWAIN_PWE_EMPH_WEVEW_3:
		signaw_wevews |= DP_PWE_EMPHASIS_9_5;
		bweak;
	}
	wetuwn signaw_wevews;
}

static void
g4x_set_signaw_wevews(stwuct intew_encodew *encodew,
		      const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	u8 twain_set = intew_dp->twain_set[0];
	u32 signaw_wevews;

	signaw_wevews = g4x_signaw_wevews(twain_set);

	dwm_dbg_kms(&dev_pwiv->dwm, "Using signaw wevews %08x\n",
		    signaw_wevews);

	intew_dp->DP &= ~(DP_VOWTAGE_MASK | DP_PWE_EMPHASIS_MASK);
	intew_dp->DP |= signaw_wevews;

	intew_de_wwite(dev_pwiv, intew_dp->output_weg, intew_dp->DP);
	intew_de_posting_wead(dev_pwiv, intew_dp->output_weg);
}

/* SNB CPU eDP vowtage swing and pwe-emphasis contwow */
static u32 snb_cpu_edp_signaw_wevews(u8 twain_set)
{
	u8 signaw_wevews = twain_set & (DP_TWAIN_VOWTAGE_SWING_MASK |
					DP_TWAIN_PWE_EMPHASIS_MASK);

	switch (signaw_wevews) {
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_0 | DP_TWAIN_PWE_EMPH_WEVEW_0:
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_1 | DP_TWAIN_PWE_EMPH_WEVEW_0:
		wetuwn EDP_WINK_TWAIN_400_600MV_0DB_SNB_B;
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_0 | DP_TWAIN_PWE_EMPH_WEVEW_1:
		wetuwn EDP_WINK_TWAIN_400MV_3_5DB_SNB_B;
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_0 | DP_TWAIN_PWE_EMPH_WEVEW_2:
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_1 | DP_TWAIN_PWE_EMPH_WEVEW_2:
		wetuwn EDP_WINK_TWAIN_400_600MV_6DB_SNB_B;
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_1 | DP_TWAIN_PWE_EMPH_WEVEW_1:
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_2 | DP_TWAIN_PWE_EMPH_WEVEW_1:
		wetuwn EDP_WINK_TWAIN_600_800MV_3_5DB_SNB_B;
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_2 | DP_TWAIN_PWE_EMPH_WEVEW_0:
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_3 | DP_TWAIN_PWE_EMPH_WEVEW_0:
		wetuwn EDP_WINK_TWAIN_800_1200MV_0DB_SNB_B;
	defauwt:
		MISSING_CASE(signaw_wevews);
		wetuwn EDP_WINK_TWAIN_400_600MV_0DB_SNB_B;
	}
}

static void
snb_cpu_edp_set_signaw_wevews(stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	u8 twain_set = intew_dp->twain_set[0];
	u32 signaw_wevews;

	signaw_wevews = snb_cpu_edp_signaw_wevews(twain_set);

	dwm_dbg_kms(&dev_pwiv->dwm, "Using signaw wevews %08x\n",
		    signaw_wevews);

	intew_dp->DP &= ~EDP_WINK_TWAIN_VOW_EMP_MASK_SNB;
	intew_dp->DP |= signaw_wevews;

	intew_de_wwite(dev_pwiv, intew_dp->output_weg, intew_dp->DP);
	intew_de_posting_wead(dev_pwiv, intew_dp->output_weg);
}

/* IVB CPU eDP vowtage swing and pwe-emphasis contwow */
static u32 ivb_cpu_edp_signaw_wevews(u8 twain_set)
{
	u8 signaw_wevews = twain_set & (DP_TWAIN_VOWTAGE_SWING_MASK |
					DP_TWAIN_PWE_EMPHASIS_MASK);

	switch (signaw_wevews) {
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_0 | DP_TWAIN_PWE_EMPH_WEVEW_0:
		wetuwn EDP_WINK_TWAIN_400MV_0DB_IVB;
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_0 | DP_TWAIN_PWE_EMPH_WEVEW_1:
		wetuwn EDP_WINK_TWAIN_400MV_3_5DB_IVB;
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_0 | DP_TWAIN_PWE_EMPH_WEVEW_2:
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_1 | DP_TWAIN_PWE_EMPH_WEVEW_2:
		wetuwn EDP_WINK_TWAIN_400MV_6DB_IVB;

	case DP_TWAIN_VOWTAGE_SWING_WEVEW_1 | DP_TWAIN_PWE_EMPH_WEVEW_0:
		wetuwn EDP_WINK_TWAIN_600MV_0DB_IVB;
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_1 | DP_TWAIN_PWE_EMPH_WEVEW_1:
		wetuwn EDP_WINK_TWAIN_600MV_3_5DB_IVB;

	case DP_TWAIN_VOWTAGE_SWING_WEVEW_2 | DP_TWAIN_PWE_EMPH_WEVEW_0:
		wetuwn EDP_WINK_TWAIN_800MV_0DB_IVB;
	case DP_TWAIN_VOWTAGE_SWING_WEVEW_2 | DP_TWAIN_PWE_EMPH_WEVEW_1:
		wetuwn EDP_WINK_TWAIN_800MV_3_5DB_IVB;

	defauwt:
		MISSING_CASE(signaw_wevews);
		wetuwn EDP_WINK_TWAIN_500MV_0DB_IVB;
	}
}

static void
ivb_cpu_edp_set_signaw_wevews(stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	u8 twain_set = intew_dp->twain_set[0];
	u32 signaw_wevews;

	signaw_wevews = ivb_cpu_edp_signaw_wevews(twain_set);

	dwm_dbg_kms(&dev_pwiv->dwm, "Using signaw wevews %08x\n",
		    signaw_wevews);

	intew_dp->DP &= ~EDP_WINK_TWAIN_VOW_EMP_MASK_IVB;
	intew_dp->DP |= signaw_wevews;

	intew_de_wwite(dev_pwiv, intew_dp->output_weg, intew_dp->DP);
	intew_de_posting_wead(dev_pwiv, intew_dp->output_weg);
}

/*
 * If dispway is now connected check winks status,
 * thewe has been known issues of wink woss twiggewing
 * wong puwse.
 *
 * Some sinks (eg. ASUS PB287Q) seem to pewfowm some
 * weiwd HPD ping pong duwing modesets. So we can appawentwy
 * end up with HPD going wow duwing a modeset, and then
 * going back up soon aftew. And once that happens we must
 * wetwain the wink to get a pictuwe. That's in case no
 * usewspace component weacted to intewmittent HPD dip.
 */
static enum intew_hotpwug_state
intew_dp_hotpwug(stwuct intew_encodew *encodew,
		 stwuct intew_connectow *connectow)
{
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
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

	dwm_modeset_acquiwe_init(&ctx, 0);

	fow (;;) {
		wet = intew_dp_wetwain_wink(encodew, &ctx);

		if (wet == -EDEADWK) {
			dwm_modeset_backoff(&ctx);
			continue;
		}

		bweak;
	}

	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);
	dwm_WAWN(encodew->base.dev, wet,
		 "Acquiwing modeset wocks faiwed with %i\n", wet);

	/*
	 * Keeping it consistent with intew_ddi_hotpwug() and
	 * intew_hdmi_hotpwug().
	 */
	if (state == INTEW_HOTPWUG_UNCHANGED && !connectow->hotpwug_wetwies)
		state = INTEW_HOTPWUG_WETWY;

	wetuwn state;
}

static boow ibx_digitaw_powt_connected(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	u32 bit = dev_pwiv->dispway.hotpwug.pch_hpd[encodew->hpd_pin];

	wetuwn intew_de_wead(dev_pwiv, SDEISW) & bit;
}

static boow g4x_digitaw_powt_connected(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	u32 bit;

	switch (encodew->hpd_pin) {
	case HPD_POWT_B:
		bit = POWTB_HOTPWUG_WIVE_STATUS_G4X;
		bweak;
	case HPD_POWT_C:
		bit = POWTC_HOTPWUG_WIVE_STATUS_G4X;
		bweak;
	case HPD_POWT_D:
		bit = POWTD_HOTPWUG_WIVE_STATUS_G4X;
		bweak;
	defauwt:
		MISSING_CASE(encodew->hpd_pin);
		wetuwn fawse;
	}

	wetuwn intew_de_wead(dev_pwiv, POWT_HOTPWUG_STAT) & bit;
}

static boow iwk_digitaw_powt_connected(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	u32 bit = dev_pwiv->dispway.hotpwug.hpd[encodew->hpd_pin];

	wetuwn intew_de_wead(dev_pwiv, DEISW) & bit;
}

static void intew_dp_encodew_destwoy(stwuct dwm_encodew *encodew)
{
	intew_dp_encodew_fwush_wowk(encodew);

	dwm_encodew_cweanup(encodew);
	kfwee(enc_to_dig_powt(to_intew_encodew(encodew)));
}

enum pipe vwv_active_pipe(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	stwuct intew_encodew *encodew = &dp_to_dig_powt(intew_dp)->base;
	enum pipe pipe;

	if (g4x_dp_powt_enabwed(dev_pwiv, intew_dp->output_weg,
				encodew->powt, &pipe))
		wetuwn pipe;

	wetuwn INVAWID_PIPE;
}

static void intew_dp_encodew_weset(stwuct dwm_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(to_intew_encodew(encodew));

	intew_dp->DP = intew_de_wead(dev_pwiv, intew_dp->output_weg);

	intew_dp->weset_wink_pawams = twue;

	if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv)) {
		intew_wakewef_t wakewef;

		with_intew_pps_wock(intew_dp, wakewef)
			intew_dp->pps.active_pipe = vwv_active_pipe(intew_dp);
	}

	intew_pps_encodew_weset(intew_dp);
}

static const stwuct dwm_encodew_funcs intew_dp_enc_funcs = {
	.weset = intew_dp_encodew_weset,
	.destwoy = intew_dp_encodew_destwoy,
};

boow g4x_dp_init(stwuct dwm_i915_pwivate *dev_pwiv,
		 i915_weg_t output_weg, enum powt powt)
{
	const stwuct intew_bios_encodew_data *devdata;
	stwuct intew_digitaw_powt *dig_powt;
	stwuct intew_encodew *intew_encodew;
	stwuct dwm_encodew *encodew;
	stwuct intew_connectow *intew_connectow;

	if (!assewt_powt_vawid(dev_pwiv, powt))
		wetuwn fawse;

	devdata = intew_bios_encodew_data_wookup(dev_pwiv, powt);

	/* FIXME baiw? */
	if (!devdata)
		dwm_dbg_kms(&dev_pwiv->dwm, "No VBT chiwd device fow DP-%c\n",
			    powt_name(powt));

	dig_powt = kzawwoc(sizeof(*dig_powt), GFP_KEWNEW);
	if (!dig_powt)
		wetuwn fawse;

	dig_powt->aux_ch = AUX_CH_NONE;

	intew_connectow = intew_connectow_awwoc();
	if (!intew_connectow)
		goto eww_connectow_awwoc;

	intew_encodew = &dig_powt->base;
	encodew = &intew_encodew->base;

	intew_encodew->devdata = devdata;

	mutex_init(&dig_powt->hdcp_mutex);

	if (dwm_encodew_init(&dev_pwiv->dwm, &intew_encodew->base,
			     &intew_dp_enc_funcs, DWM_MODE_ENCODEW_TMDS,
			     "DP %c", powt_name(powt)))
		goto eww_encodew_init;

	intew_encodew->hotpwug = intew_dp_hotpwug;
	intew_encodew->compute_config = intew_dp_compute_config;
	intew_encodew->get_hw_state = intew_dp_get_hw_state;
	intew_encodew->get_config = intew_dp_get_config;
	intew_encodew->sync_state = intew_dp_sync_state;
	intew_encodew->initiaw_fastset_check = intew_dp_initiaw_fastset_check;
	intew_encodew->update_pipe = intew_backwight_update;
	intew_encodew->suspend = intew_dp_encodew_suspend;
	intew_encodew->shutdown = intew_dp_encodew_shutdown;
	if (IS_CHEWWYVIEW(dev_pwiv)) {
		intew_encodew->pwe_pww_enabwe = chv_dp_pwe_pww_enabwe;
		intew_encodew->pwe_enabwe = chv_pwe_enabwe_dp;
		intew_encodew->enabwe = vwv_enabwe_dp;
		intew_encodew->disabwe = vwv_disabwe_dp;
		intew_encodew->post_disabwe = chv_post_disabwe_dp;
		intew_encodew->post_pww_disabwe = chv_dp_post_pww_disabwe;
	} ewse if (IS_VAWWEYVIEW(dev_pwiv)) {
		intew_encodew->pwe_pww_enabwe = vwv_dp_pwe_pww_enabwe;
		intew_encodew->pwe_enabwe = vwv_pwe_enabwe_dp;
		intew_encodew->enabwe = vwv_enabwe_dp;
		intew_encodew->disabwe = vwv_disabwe_dp;
		intew_encodew->post_disabwe = vwv_post_disabwe_dp;
	} ewse {
		intew_encodew->pwe_enabwe = g4x_pwe_enabwe_dp;
		intew_encodew->enabwe = g4x_enabwe_dp;
		intew_encodew->disabwe = g4x_disabwe_dp;
		intew_encodew->post_disabwe = g4x_post_disabwe_dp;
	}
	intew_encodew->audio_enabwe = g4x_dp_audio_enabwe;
	intew_encodew->audio_disabwe = g4x_dp_audio_disabwe;

	if ((IS_IVYBWIDGE(dev_pwiv) && powt == POWT_A) ||
	    (HAS_PCH_CPT(dev_pwiv) && powt != POWT_A))
		dig_powt->dp.set_wink_twain = cpt_set_wink_twain;
	ewse
		dig_powt->dp.set_wink_twain = g4x_set_wink_twain;

	if (IS_CHEWWYVIEW(dev_pwiv))
		intew_encodew->set_signaw_wevews = chv_set_signaw_wevews;
	ewse if (IS_VAWWEYVIEW(dev_pwiv))
		intew_encodew->set_signaw_wevews = vwv_set_signaw_wevews;
	ewse if (IS_IVYBWIDGE(dev_pwiv) && powt == POWT_A)
		intew_encodew->set_signaw_wevews = ivb_cpu_edp_set_signaw_wevews;
	ewse if (IS_SANDYBWIDGE(dev_pwiv) && powt == POWT_A)
		intew_encodew->set_signaw_wevews = snb_cpu_edp_set_signaw_wevews;
	ewse
		intew_encodew->set_signaw_wevews = g4x_set_signaw_wevews;

	if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv) ||
	    (HAS_PCH_SPWIT(dev_pwiv) && powt != POWT_A)) {
		dig_powt->dp.pweemph_max = intew_dp_pweemph_max_3;
		dig_powt->dp.vowtage_max = intew_dp_vowtage_max_3;
	} ewse {
		dig_powt->dp.pweemph_max = intew_dp_pweemph_max_2;
		dig_powt->dp.vowtage_max = intew_dp_vowtage_max_2;
	}

	dig_powt->dp.output_weg = output_weg;
	dig_powt->max_wanes = 4;

	intew_encodew->type = INTEW_OUTPUT_DP;
	intew_encodew->powew_domain = intew_dispway_powew_ddi_wanes_domain(dev_pwiv, powt);
	if (IS_CHEWWYVIEW(dev_pwiv)) {
		if (powt == POWT_D)
			intew_encodew->pipe_mask = BIT(PIPE_C);
		ewse
			intew_encodew->pipe_mask = BIT(PIPE_A) | BIT(PIPE_B);
	} ewse {
		intew_encodew->pipe_mask = ~0;
	}
	intew_encodew->cwoneabwe = 0;
	intew_encodew->powt = powt;
	intew_encodew->hpd_pin = intew_hpd_pin_defauwt(dev_pwiv, powt);

	dig_powt->hpd_puwse = intew_dp_hpd_puwse;

	if (HAS_GMCH(dev_pwiv)) {
		dig_powt->connected = g4x_digitaw_powt_connected;
	} ewse {
		if (powt == POWT_A)
			dig_powt->connected = iwk_digitaw_powt_connected;
		ewse
			dig_powt->connected = ibx_digitaw_powt_connected;
	}

	if (powt != POWT_A)
		intew_infofwame_init(dig_powt);

	dig_powt->aux_ch = intew_dp_aux_ch(intew_encodew);
	if (dig_powt->aux_ch == AUX_CH_NONE)
		goto eww_init_connectow;

	if (!intew_dp_init_connectow(dig_powt, intew_connectow))
		goto eww_init_connectow;

	wetuwn twue;

eww_init_connectow:
	dwm_encodew_cweanup(encodew);
eww_encodew_init:
	kfwee(intew_connectow);
eww_connectow_awwoc:
	kfwee(dig_powt);
	wetuwn fawse;
}
