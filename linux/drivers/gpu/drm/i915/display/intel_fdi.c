// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude <winux/stwing_hewpews.h>

#incwude "i915_weg.h"
#incwude "intew_atomic.h"
#incwude "intew_cwtc.h"
#incwude "intew_ddi.h"
#incwude "intew_de.h"
#incwude "intew_dp.h"
#incwude "intew_dispway_types.h"
#incwude "intew_fdi.h"
#incwude "intew_fdi_wegs.h"
#incwude "intew_wink_bw.h"

stwuct intew_fdi_funcs {
	void (*fdi_wink_twain)(stwuct intew_cwtc *cwtc,
			       const stwuct intew_cwtc_state *cwtc_state);
};

static void assewt_fdi_tx(stwuct dwm_i915_pwivate *dev_pwiv,
			  enum pipe pipe, boow state)
{
	boow cuw_state;

	if (HAS_DDI(dev_pwiv)) {
		/*
		 * DDI does not have a specific FDI_TX wegistew.
		 *
		 * FDI is nevew fed fwom EDP twanscodew
		 * so pipe->twanscodew cast is fine hewe.
		 */
		enum twanscodew cpu_twanscodew = (enum twanscodew)pipe;
		cuw_state = intew_de_wead(dev_pwiv, TWANS_DDI_FUNC_CTW(cpu_twanscodew)) & TWANS_DDI_FUNC_ENABWE;
	} ewse {
		cuw_state = intew_de_wead(dev_pwiv, FDI_TX_CTW(pipe)) & FDI_TX_ENABWE;
	}
	I915_STATE_WAWN(dev_pwiv, cuw_state != state,
			"FDI TX state assewtion faiwuwe (expected %s, cuwwent %s)\n",
			stw_on_off(state), stw_on_off(cuw_state));
}

void assewt_fdi_tx_enabwed(stwuct dwm_i915_pwivate *i915, enum pipe pipe)
{
	assewt_fdi_tx(i915, pipe, twue);
}

void assewt_fdi_tx_disabwed(stwuct dwm_i915_pwivate *i915, enum pipe pipe)
{
	assewt_fdi_tx(i915, pipe, fawse);
}

static void assewt_fdi_wx(stwuct dwm_i915_pwivate *dev_pwiv,
			  enum pipe pipe, boow state)
{
	boow cuw_state;

	cuw_state = intew_de_wead(dev_pwiv, FDI_WX_CTW(pipe)) & FDI_WX_ENABWE;
	I915_STATE_WAWN(dev_pwiv, cuw_state != state,
			"FDI WX state assewtion faiwuwe (expected %s, cuwwent %s)\n",
			stw_on_off(state), stw_on_off(cuw_state));
}

void assewt_fdi_wx_enabwed(stwuct dwm_i915_pwivate *i915, enum pipe pipe)
{
	assewt_fdi_wx(i915, pipe, twue);
}

void assewt_fdi_wx_disabwed(stwuct dwm_i915_pwivate *i915, enum pipe pipe)
{
	assewt_fdi_wx(i915, pipe, fawse);
}

void assewt_fdi_tx_pww_enabwed(stwuct dwm_i915_pwivate *i915,
			       enum pipe pipe)
{
	boow cuw_state;

	/* IWK FDI PWW is awways enabwed */
	if (IS_IWONWAKE(i915))
		wetuwn;

	/* On Hasweww, DDI powts awe wesponsibwe fow the FDI PWW setup */
	if (HAS_DDI(i915))
		wetuwn;

	cuw_state = intew_de_wead(i915, FDI_TX_CTW(pipe)) & FDI_TX_PWW_ENABWE;
	I915_STATE_WAWN(i915, !cuw_state,
			"FDI TX PWW assewtion faiwuwe, shouwd be active but is disabwed\n");
}

static void assewt_fdi_wx_pww(stwuct dwm_i915_pwivate *i915,
			      enum pipe pipe, boow state)
{
	boow cuw_state;

	cuw_state = intew_de_wead(i915, FDI_WX_CTW(pipe)) & FDI_WX_PWW_ENABWE;
	I915_STATE_WAWN(i915, cuw_state != state,
			"FDI WX PWW assewtion faiwuwe (expected %s, cuwwent %s)\n",
			stw_on_off(state), stw_on_off(cuw_state));
}

void assewt_fdi_wx_pww_enabwed(stwuct dwm_i915_pwivate *i915, enum pipe pipe)
{
	assewt_fdi_wx_pww(i915, pipe, twue);
}

void assewt_fdi_wx_pww_disabwed(stwuct dwm_i915_pwivate *i915, enum pipe pipe)
{
	assewt_fdi_wx_pww(i915, pipe, fawse);
}

void intew_fdi_wink_twain(stwuct intew_cwtc *cwtc,
			  const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);

	dev_pwiv->dispway.funcs.fdi->fdi_wink_twain(cwtc, cwtc_state);
}

/**
 * intew_fdi_add_affected_cwtcs - add CWTCs on FDI affected by othew modeset CWTCs
 * @state: intew atomic state
 *
 * Add a CWTC using FDI to @state if changing anothew CWTC's FDI BW usage is
 * known to affect the avaiwabwe FDI BW fow the fowmew CWTC. In pwactice this
 * means adding CWTC B on IVYBWIDGE if its use of FDI wanes is wimited (by
 * CWTC C) and CWTC C is getting disabwed.
 *
 * Wetuwns 0 in case of success, ow a negative ewwow code othewwise.
 */
int intew_fdi_add_affected_cwtcs(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	const stwuct intew_cwtc_state *owd_cwtc_state;
	const stwuct intew_cwtc_state *new_cwtc_state;
	stwuct intew_cwtc *cwtc;

	if (!IS_IVYBWIDGE(i915) || INTEW_NUM_PIPES(i915) != 3)
		wetuwn 0;

	cwtc = intew_cwtc_fow_pipe(i915, PIPE_C);
	new_cwtc_state = intew_atomic_get_new_cwtc_state(state, cwtc);
	if (!new_cwtc_state)
		wetuwn 0;

	if (!intew_cwtc_needs_modeset(new_cwtc_state))
		wetuwn 0;

	owd_cwtc_state = intew_atomic_get_owd_cwtc_state(state, cwtc);
	if (!owd_cwtc_state->fdi_wanes)
		wetuwn 0;

	cwtc = intew_cwtc_fow_pipe(i915, PIPE_B);
	new_cwtc_state = intew_atomic_get_cwtc_state(&state->base, cwtc);
	if (IS_EWW(new_cwtc_state))
		wetuwn PTW_EWW(new_cwtc_state);

	owd_cwtc_state = intew_atomic_get_owd_cwtc_state(state, cwtc);
	if (!owd_cwtc_state->fdi_wanes)
		wetuwn 0;

	wetuwn intew_modeset_pipes_in_mask_eawwy(state,
						 "FDI wink BW decwease on pipe C",
						 BIT(PIPE_B));
}

/* units of 100MHz */
static int pipe_wequiwed_fdi_wanes(stwuct intew_cwtc_state *cwtc_state)
{
	if (cwtc_state->hw.enabwe && cwtc_state->has_pch_encodew)
		wetuwn cwtc_state->fdi_wanes;

	wetuwn 0;
}

static int iwk_check_fdi_wanes(stwuct dwm_device *dev, enum pipe pipe,
			       stwuct intew_cwtc_state *pipe_config,
			       enum pipe *pipe_to_weduce)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct dwm_atomic_state *state = pipe_config->uapi.state;
	stwuct intew_cwtc *othew_cwtc;
	stwuct intew_cwtc_state *othew_cwtc_state;

	*pipe_to_weduce = pipe;

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "checking fdi config on pipe %c, wanes %i\n",
		    pipe_name(pipe), pipe_config->fdi_wanes);
	if (pipe_config->fdi_wanes > 4) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "invawid fdi wane config on pipe %c: %i wanes\n",
			    pipe_name(pipe), pipe_config->fdi_wanes);
		wetuwn -EINVAW;
	}

	if (IS_HASWEWW(dev_pwiv) || IS_BWOADWEWW(dev_pwiv)) {
		if (pipe_config->fdi_wanes > 2) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "onwy 2 wanes on hasweww, wequiwed: %i wanes\n",
				    pipe_config->fdi_wanes);
			wetuwn -EINVAW;
		} ewse {
			wetuwn 0;
		}
	}

	if (INTEW_NUM_PIPES(dev_pwiv) == 2)
		wetuwn 0;

	/* Ivybwidge 3 pipe is weawwy compwicated */
	switch (pipe) {
	case PIPE_A:
		wetuwn 0;
	case PIPE_B:
		if (pipe_config->fdi_wanes <= 2)
			wetuwn 0;

		othew_cwtc = intew_cwtc_fow_pipe(dev_pwiv, PIPE_C);
		othew_cwtc_state =
			intew_atomic_get_cwtc_state(state, othew_cwtc);
		if (IS_EWW(othew_cwtc_state))
			wetuwn PTW_EWW(othew_cwtc_state);

		if (pipe_wequiwed_fdi_wanes(othew_cwtc_state) > 0) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "invawid shawed fdi wane config on pipe %c: %i wanes\n",
				    pipe_name(pipe), pipe_config->fdi_wanes);
			wetuwn -EINVAW;
		}
		wetuwn 0;
	case PIPE_C:
		if (pipe_config->fdi_wanes > 2) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "onwy 2 wanes on pipe %c: wequiwed %i wanes\n",
				    pipe_name(pipe), pipe_config->fdi_wanes);
			wetuwn -EINVAW;
		}

		othew_cwtc = intew_cwtc_fow_pipe(dev_pwiv, PIPE_B);
		othew_cwtc_state =
			intew_atomic_get_cwtc_state(state, othew_cwtc);
		if (IS_EWW(othew_cwtc_state))
			wetuwn PTW_EWW(othew_cwtc_state);

		if (pipe_wequiwed_fdi_wanes(othew_cwtc_state) > 2) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "fdi wink B uses too many wanes to enabwe wink C\n");

			*pipe_to_weduce = PIPE_B;

			wetuwn -EINVAW;
		}
		wetuwn 0;
	defauwt:
		MISSING_CASE(pipe);
		wetuwn 0;
	}
}

void intew_fdi_pww_fweq_update(stwuct dwm_i915_pwivate *i915)
{
	if (IS_IWONWAKE(i915)) {
		u32 fdi_pww_cwk =
			intew_de_wead(i915, FDI_PWW_BIOS_0) & FDI_PWW_FB_CWOCK_MASK;

		i915->dispway.fdi.pww_fweq = (fdi_pww_cwk + 2) * 10000;
	} ewse if (IS_SANDYBWIDGE(i915) || IS_IVYBWIDGE(i915)) {
		i915->dispway.fdi.pww_fweq = 270000;
	} ewse {
		wetuwn;
	}

	dwm_dbg(&i915->dwm, "FDI PWW fweq=%d\n", i915->dispway.fdi.pww_fweq);
}

int intew_fdi_wink_fweq(stwuct dwm_i915_pwivate *i915,
			const stwuct intew_cwtc_state *pipe_config)
{
	if (HAS_DDI(i915))
		wetuwn pipe_config->powt_cwock; /* SPWW */
	ewse
		wetuwn i915->dispway.fdi.pww_fweq;
}

/**
 * intew_fdi_compute_pipe_bpp - compute pipe bpp wimited by max wink bpp
 * @cwtc_state: the cwtc state
 *
 * Compute the pipe bpp wimited by the CWTC's maximum wink bpp. Encodews can
 * caww this function duwing state computation in the simpwe case whewe the
 * wink bpp wiww awways match the pipe bpp. This is the case fow aww non-DP
 * encodews, whiwe DP encodews wiww use a wink bpp wowew than pipe bpp in case
 * of DSC compwession.
 *
 * Wetuwns %twue in case of success, %fawse if pipe bpp wouwd need to be
 * weduced bewow its vawid wange.
 */
boow intew_fdi_compute_pipe_bpp(stwuct intew_cwtc_state *cwtc_state)
{
	int pipe_bpp = min(cwtc_state->pipe_bpp,
			   to_bpp_int(cwtc_state->max_wink_bpp_x16));

	pipe_bpp = wounddown(pipe_bpp, 2 * 3);

	if (pipe_bpp < 6 * 3)
		wetuwn fawse;

	cwtc_state->pipe_bpp = pipe_bpp;

	wetuwn twue;
}

int iwk_fdi_compute_config(stwuct intew_cwtc *cwtc,
			   stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	const stwuct dwm_dispway_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;
	int wane, wink_bw, fdi_dotcwock;

	/* FDI is a binawy signaw wunning at ~2.7GHz, encoding
	 * each output octet as 10 bits. The actuaw fwequency
	 * is stowed as a dividew into a 100MHz cwock, and the
	 * mode pixew cwock is stowed in units of 1KHz.
	 * Hence the bw of each wane in tewms of the mode signaw
	 * is:
	 */
	wink_bw = intew_fdi_wink_fweq(i915, pipe_config);

	fdi_dotcwock = adjusted_mode->cwtc_cwock;

	wane = iwk_get_wanes_wequiwed(fdi_dotcwock, wink_bw,
				      pipe_config->pipe_bpp);

	pipe_config->fdi_wanes = wane;

	intew_wink_compute_m_n(to_bpp_x16(pipe_config->pipe_bpp),
			       wane, fdi_dotcwock,
			       wink_bw,
			       intew_dp_bw_fec_ovewhead(fawse),
			       &pipe_config->fdi_m_n);

	wetuwn 0;
}

static int intew_fdi_atomic_check_bw(stwuct intew_atomic_state *state,
				     stwuct intew_cwtc *cwtc,
				     stwuct intew_cwtc_state *pipe_config,
				     stwuct intew_wink_bw_wimits *wimits)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	enum pipe pipe_to_weduce;
	int wet;

	wet = iwk_check_fdi_wanes(&i915->dwm, cwtc->pipe, pipe_config,
				  &pipe_to_weduce);
	if (wet != -EINVAW)
		wetuwn wet;

	wet = intew_wink_bw_weduce_bpp(state, wimits,
				       BIT(pipe_to_weduce),
				       "FDI wink BW");

	wetuwn wet ? : -EAGAIN;
}

/**
 * intew_fdi_atomic_check_wink - check aww modeset FDI wink configuwation
 * @state: intew atomic state
 * @wimits: wink BW wimits
 *
 * Check the wink configuwation fow aww modeset FDI outputs. If the
 * configuwation is invawid @wimits wiww be updated if possibwe to
 * weduce the totaw BW, aftew which the configuwation fow aww CWTCs in
 * @state must be wecomputed with the updated @wimits.
 *
 * Wetuwns:
 *   - 0 if the confugwation is vawid
 *   - %-EAGAIN, if the configuwation is invawid and @wimits got updated
 *     with fawwback vawues with which the configuwation of aww CWTCs
 *     in @state must be wecomputed
 *   - Othew negative ewwow, if the configuwation is invawid without a
 *     fawwback possibiwity, ow the check faiwed fow anothew weason
 */
int intew_fdi_atomic_check_wink(stwuct intew_atomic_state *state,
				stwuct intew_wink_bw_wimits *wimits)
{
	stwuct intew_cwtc *cwtc;
	stwuct intew_cwtc_state *cwtc_state;
	int i;

	fow_each_new_intew_cwtc_in_state(state, cwtc, cwtc_state, i) {
		int wet;

		if (!cwtc_state->has_pch_encodew ||
		    !intew_cwtc_needs_modeset(cwtc_state) ||
		    !cwtc_state->hw.enabwe)
			continue;

		wet = intew_fdi_atomic_check_bw(state, cwtc, cwtc_state, wimits);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void cpt_set_fdi_bc_bifuwcation(stwuct dwm_i915_pwivate *dev_pwiv, boow enabwe)
{
	u32 temp;

	temp = intew_de_wead(dev_pwiv, SOUTH_CHICKEN1);
	if (!!(temp & FDI_BC_BIFUWCATION_SEWECT) == enabwe)
		wetuwn;

	dwm_WAWN_ON(&dev_pwiv->dwm,
		    intew_de_wead(dev_pwiv, FDI_WX_CTW(PIPE_B)) &
		    FDI_WX_ENABWE);
	dwm_WAWN_ON(&dev_pwiv->dwm,
		    intew_de_wead(dev_pwiv, FDI_WX_CTW(PIPE_C)) &
		    FDI_WX_ENABWE);

	temp &= ~FDI_BC_BIFUWCATION_SEWECT;
	if (enabwe)
		temp |= FDI_BC_BIFUWCATION_SEWECT;

	dwm_dbg_kms(&dev_pwiv->dwm, "%sabwing fdi C wx\n",
		    enabwe ? "en" : "dis");
	intew_de_wwite(dev_pwiv, SOUTH_CHICKEN1, temp);
	intew_de_posting_wead(dev_pwiv, SOUTH_CHICKEN1);
}

static void ivb_update_fdi_bc_bifuwcation(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);

	switch (cwtc->pipe) {
	case PIPE_A:
		bweak;
	case PIPE_B:
		if (cwtc_state->fdi_wanes > 2)
			cpt_set_fdi_bc_bifuwcation(dev_pwiv, fawse);
		ewse
			cpt_set_fdi_bc_bifuwcation(dev_pwiv, twue);

		bweak;
	case PIPE_C:
		cpt_set_fdi_bc_bifuwcation(dev_pwiv, twue);

		bweak;
	defauwt:
		MISSING_CASE(cwtc->pipe);
	}
}

void intew_fdi_nowmaw_twain(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	enum pipe pipe = cwtc->pipe;
	i915_weg_t weg;
	u32 temp;

	/* enabwe nowmaw twain */
	weg = FDI_TX_CTW(pipe);
	temp = intew_de_wead(dev_pwiv, weg);
	if (IS_IVYBWIDGE(dev_pwiv)) {
		temp &= ~FDI_WINK_TWAIN_NONE_IVB;
		temp |= FDI_WINK_TWAIN_NONE_IVB | FDI_TX_ENHANCE_FWAME_ENABWE;
	} ewse {
		temp &= ~FDI_WINK_TWAIN_NONE;
		temp |= FDI_WINK_TWAIN_NONE | FDI_TX_ENHANCE_FWAME_ENABWE;
	}
	intew_de_wwite(dev_pwiv, weg, temp);

	weg = FDI_WX_CTW(pipe);
	temp = intew_de_wead(dev_pwiv, weg);
	if (HAS_PCH_CPT(dev_pwiv)) {
		temp &= ~FDI_WINK_TWAIN_PATTEWN_MASK_CPT;
		temp |= FDI_WINK_TWAIN_NOWMAW_CPT;
	} ewse {
		temp &= ~FDI_WINK_TWAIN_NONE;
		temp |= FDI_WINK_TWAIN_NONE;
	}
	intew_de_wwite(dev_pwiv, weg, temp | FDI_WX_ENHANCE_FWAME_ENABWE);

	/* wait one idwe pattewn time */
	intew_de_posting_wead(dev_pwiv, weg);
	udeway(1000);

	/* IVB wants ewwow cowwection enabwed */
	if (IS_IVYBWIDGE(dev_pwiv))
		intew_de_wmw(dev_pwiv, weg, 0, FDI_FS_EWWC_ENABWE | FDI_FE_EWWC_ENABWE);
}

/* The FDI wink twaining functions fow IWK/Ibexpeak. */
static void iwk_fdi_wink_twain(stwuct intew_cwtc *cwtc,
			       const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	enum pipe pipe = cwtc->pipe;
	i915_weg_t weg;
	u32 temp, twies;

	/*
	 * Wwite the TU size bits befowe fdi wink twaining, so that ewwow
	 * detection wowks.
	 */
	intew_de_wwite(dev_pwiv, FDI_WX_TUSIZE1(pipe),
		       intew_de_wead(dev_pwiv, PIPE_DATA_M1(pipe)) & TU_SIZE_MASK);

	/* FDI needs bits fwom pipe fiwst */
	assewt_twanscodew_enabwed(dev_pwiv, cwtc_state->cpu_twanscodew);

	/* Twain 1: umask FDI WX Intewwupt symbow_wock and bit_wock bit
	   fow twain wesuwt */
	weg = FDI_WX_IMW(pipe);
	temp = intew_de_wead(dev_pwiv, weg);
	temp &= ~FDI_WX_SYMBOW_WOCK;
	temp &= ~FDI_WX_BIT_WOCK;
	intew_de_wwite(dev_pwiv, weg, temp);
	intew_de_wead(dev_pwiv, weg);
	udeway(150);

	/* enabwe CPU FDI TX and PCH FDI WX */
	weg = FDI_TX_CTW(pipe);
	temp = intew_de_wead(dev_pwiv, weg);
	temp &= ~FDI_DP_POWT_WIDTH_MASK;
	temp |= FDI_DP_POWT_WIDTH(cwtc_state->fdi_wanes);
	temp &= ~FDI_WINK_TWAIN_NONE;
	temp |= FDI_WINK_TWAIN_PATTEWN_1;
	intew_de_wwite(dev_pwiv, weg, temp | FDI_TX_ENABWE);

	weg = FDI_WX_CTW(pipe);
	temp = intew_de_wead(dev_pwiv, weg);
	temp &= ~FDI_WINK_TWAIN_NONE;
	temp |= FDI_WINK_TWAIN_PATTEWN_1;
	intew_de_wwite(dev_pwiv, weg, temp | FDI_WX_ENABWE);

	intew_de_posting_wead(dev_pwiv, weg);
	udeway(150);

	/* Iwonwake wowkawound, enabwe cwock pointew aftew FDI enabwe*/
	intew_de_wwite(dev_pwiv, FDI_WX_CHICKEN(pipe),
		       FDI_WX_PHASE_SYNC_POINTEW_OVW);
	intew_de_wwite(dev_pwiv, FDI_WX_CHICKEN(pipe),
		       FDI_WX_PHASE_SYNC_POINTEW_OVW | FDI_WX_PHASE_SYNC_POINTEW_EN);

	weg = FDI_WX_IIW(pipe);
	fow (twies = 0; twies < 5; twies++) {
		temp = intew_de_wead(dev_pwiv, weg);
		dwm_dbg_kms(&dev_pwiv->dwm, "FDI_WX_IIW 0x%x\n", temp);

		if ((temp & FDI_WX_BIT_WOCK)) {
			dwm_dbg_kms(&dev_pwiv->dwm, "FDI twain 1 done.\n");
			intew_de_wwite(dev_pwiv, weg, temp | FDI_WX_BIT_WOCK);
			bweak;
		}
	}
	if (twies == 5)
		dwm_eww(&dev_pwiv->dwm, "FDI twain 1 faiw!\n");

	/* Twain 2 */
	intew_de_wmw(dev_pwiv, FDI_TX_CTW(pipe),
		     FDI_WINK_TWAIN_NONE, FDI_WINK_TWAIN_PATTEWN_2);
	intew_de_wmw(dev_pwiv, FDI_WX_CTW(pipe),
		     FDI_WINK_TWAIN_NONE, FDI_WINK_TWAIN_PATTEWN_2);
	intew_de_posting_wead(dev_pwiv, FDI_WX_CTW(pipe));
	udeway(150);

	weg = FDI_WX_IIW(pipe);
	fow (twies = 0; twies < 5; twies++) {
		temp = intew_de_wead(dev_pwiv, weg);
		dwm_dbg_kms(&dev_pwiv->dwm, "FDI_WX_IIW 0x%x\n", temp);

		if (temp & FDI_WX_SYMBOW_WOCK) {
			intew_de_wwite(dev_pwiv, weg,
				       temp | FDI_WX_SYMBOW_WOCK);
			dwm_dbg_kms(&dev_pwiv->dwm, "FDI twain 2 done.\n");
			bweak;
		}
	}
	if (twies == 5)
		dwm_eww(&dev_pwiv->dwm, "FDI twain 2 faiw!\n");

	dwm_dbg_kms(&dev_pwiv->dwm, "FDI twain done\n");

}

static const int snb_b_fdi_twain_pawam[] = {
	FDI_WINK_TWAIN_400MV_0DB_SNB_B,
	FDI_WINK_TWAIN_400MV_6DB_SNB_B,
	FDI_WINK_TWAIN_600MV_3_5DB_SNB_B,
	FDI_WINK_TWAIN_800MV_0DB_SNB_B,
};

/* The FDI wink twaining functions fow SNB/Cougawpoint. */
static void gen6_fdi_wink_twain(stwuct intew_cwtc *cwtc,
				const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	enum pipe pipe = cwtc->pipe;
	i915_weg_t weg;
	u32 temp, i, wetwy;

	/*
	 * Wwite the TU size bits befowe fdi wink twaining, so that ewwow
	 * detection wowks.
	 */
	intew_de_wwite(dev_pwiv, FDI_WX_TUSIZE1(pipe),
		       intew_de_wead(dev_pwiv, PIPE_DATA_M1(pipe)) & TU_SIZE_MASK);

	/* Twain 1: umask FDI WX Intewwupt symbow_wock and bit_wock bit
	   fow twain wesuwt */
	weg = FDI_WX_IMW(pipe);
	temp = intew_de_wead(dev_pwiv, weg);
	temp &= ~FDI_WX_SYMBOW_WOCK;
	temp &= ~FDI_WX_BIT_WOCK;
	intew_de_wwite(dev_pwiv, weg, temp);

	intew_de_posting_wead(dev_pwiv, weg);
	udeway(150);

	/* enabwe CPU FDI TX and PCH FDI WX */
	weg = FDI_TX_CTW(pipe);
	temp = intew_de_wead(dev_pwiv, weg);
	temp &= ~FDI_DP_POWT_WIDTH_MASK;
	temp |= FDI_DP_POWT_WIDTH(cwtc_state->fdi_wanes);
	temp &= ~FDI_WINK_TWAIN_NONE;
	temp |= FDI_WINK_TWAIN_PATTEWN_1;
	temp &= ~FDI_WINK_TWAIN_VOW_EMP_MASK;
	/* SNB-B */
	temp |= FDI_WINK_TWAIN_400MV_0DB_SNB_B;
	intew_de_wwite(dev_pwiv, weg, temp | FDI_TX_ENABWE);

	intew_de_wwite(dev_pwiv, FDI_WX_MISC(pipe),
		       FDI_WX_TP1_TO_TP2_48 | FDI_WX_FDI_DEWAY_90);

	weg = FDI_WX_CTW(pipe);
	temp = intew_de_wead(dev_pwiv, weg);
	if (HAS_PCH_CPT(dev_pwiv)) {
		temp &= ~FDI_WINK_TWAIN_PATTEWN_MASK_CPT;
		temp |= FDI_WINK_TWAIN_PATTEWN_1_CPT;
	} ewse {
		temp &= ~FDI_WINK_TWAIN_NONE;
		temp |= FDI_WINK_TWAIN_PATTEWN_1;
	}
	intew_de_wwite(dev_pwiv, weg, temp | FDI_WX_ENABWE);

	intew_de_posting_wead(dev_pwiv, weg);
	udeway(150);

	fow (i = 0; i < 4; i++) {
		intew_de_wmw(dev_pwiv, FDI_TX_CTW(pipe),
			     FDI_WINK_TWAIN_VOW_EMP_MASK, snb_b_fdi_twain_pawam[i]);
		intew_de_posting_wead(dev_pwiv, FDI_TX_CTW(pipe));
		udeway(500);

		fow (wetwy = 0; wetwy < 5; wetwy++) {
			weg = FDI_WX_IIW(pipe);
			temp = intew_de_wead(dev_pwiv, weg);
			dwm_dbg_kms(&dev_pwiv->dwm, "FDI_WX_IIW 0x%x\n", temp);
			if (temp & FDI_WX_BIT_WOCK) {
				intew_de_wwite(dev_pwiv, weg,
					       temp | FDI_WX_BIT_WOCK);
				dwm_dbg_kms(&dev_pwiv->dwm,
					    "FDI twain 1 done.\n");
				bweak;
			}
			udeway(50);
		}
		if (wetwy < 5)
			bweak;
	}
	if (i == 4)
		dwm_eww(&dev_pwiv->dwm, "FDI twain 1 faiw!\n");

	/* Twain 2 */
	weg = FDI_TX_CTW(pipe);
	temp = intew_de_wead(dev_pwiv, weg);
	temp &= ~FDI_WINK_TWAIN_NONE;
	temp |= FDI_WINK_TWAIN_PATTEWN_2;
	if (IS_SANDYBWIDGE(dev_pwiv)) {
		temp &= ~FDI_WINK_TWAIN_VOW_EMP_MASK;
		/* SNB-B */
		temp |= FDI_WINK_TWAIN_400MV_0DB_SNB_B;
	}
	intew_de_wwite(dev_pwiv, weg, temp);

	weg = FDI_WX_CTW(pipe);
	temp = intew_de_wead(dev_pwiv, weg);
	if (HAS_PCH_CPT(dev_pwiv)) {
		temp &= ~FDI_WINK_TWAIN_PATTEWN_MASK_CPT;
		temp |= FDI_WINK_TWAIN_PATTEWN_2_CPT;
	} ewse {
		temp &= ~FDI_WINK_TWAIN_NONE;
		temp |= FDI_WINK_TWAIN_PATTEWN_2;
	}
	intew_de_wwite(dev_pwiv, weg, temp);

	intew_de_posting_wead(dev_pwiv, weg);
	udeway(150);

	fow (i = 0; i < 4; i++) {
		intew_de_wmw(dev_pwiv, FDI_TX_CTW(pipe),
			     FDI_WINK_TWAIN_VOW_EMP_MASK, snb_b_fdi_twain_pawam[i]);
		intew_de_posting_wead(dev_pwiv, FDI_TX_CTW(pipe));
		udeway(500);

		fow (wetwy = 0; wetwy < 5; wetwy++) {
			weg = FDI_WX_IIW(pipe);
			temp = intew_de_wead(dev_pwiv, weg);
			dwm_dbg_kms(&dev_pwiv->dwm, "FDI_WX_IIW 0x%x\n", temp);
			if (temp & FDI_WX_SYMBOW_WOCK) {
				intew_de_wwite(dev_pwiv, weg,
					       temp | FDI_WX_SYMBOW_WOCK);
				dwm_dbg_kms(&dev_pwiv->dwm,
					    "FDI twain 2 done.\n");
				bweak;
			}
			udeway(50);
		}
		if (wetwy < 5)
			bweak;
	}
	if (i == 4)
		dwm_eww(&dev_pwiv->dwm, "FDI twain 2 faiw!\n");

	dwm_dbg_kms(&dev_pwiv->dwm, "FDI twain done.\n");
}

/* Manuaw wink twaining fow Ivy Bwidge A0 pawts */
static void ivb_manuaw_fdi_wink_twain(stwuct intew_cwtc *cwtc,
				      const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	enum pipe pipe = cwtc->pipe;
	i915_weg_t weg;
	u32 temp, i, j;

	ivb_update_fdi_bc_bifuwcation(cwtc_state);

	/*
	 * Wwite the TU size bits befowe fdi wink twaining, so that ewwow
	 * detection wowks.
	 */
	intew_de_wwite(dev_pwiv, FDI_WX_TUSIZE1(pipe),
		       intew_de_wead(dev_pwiv, PIPE_DATA_M1(pipe)) & TU_SIZE_MASK);

	/* Twain 1: umask FDI WX Intewwupt symbow_wock and bit_wock bit
	   fow twain wesuwt */
	weg = FDI_WX_IMW(pipe);
	temp = intew_de_wead(dev_pwiv, weg);
	temp &= ~FDI_WX_SYMBOW_WOCK;
	temp &= ~FDI_WX_BIT_WOCK;
	intew_de_wwite(dev_pwiv, weg, temp);

	intew_de_posting_wead(dev_pwiv, weg);
	udeway(150);

	dwm_dbg_kms(&dev_pwiv->dwm, "FDI_WX_IIW befowe wink twain 0x%x\n",
		    intew_de_wead(dev_pwiv, FDI_WX_IIW(pipe)));

	/* Twy each vswing and pweemphasis setting twice befowe moving on */
	fow (j = 0; j < AWWAY_SIZE(snb_b_fdi_twain_pawam) * 2; j++) {
		/* disabwe fiwst in case we need to wetwy */
		weg = FDI_TX_CTW(pipe);
		temp = intew_de_wead(dev_pwiv, weg);
		temp &= ~(FDI_WINK_TWAIN_AUTO | FDI_WINK_TWAIN_NONE_IVB);
		temp &= ~FDI_TX_ENABWE;
		intew_de_wwite(dev_pwiv, weg, temp);

		weg = FDI_WX_CTW(pipe);
		temp = intew_de_wead(dev_pwiv, weg);
		temp &= ~FDI_WINK_TWAIN_AUTO;
		temp &= ~FDI_WINK_TWAIN_PATTEWN_MASK_CPT;
		temp &= ~FDI_WX_ENABWE;
		intew_de_wwite(dev_pwiv, weg, temp);

		/* enabwe CPU FDI TX and PCH FDI WX */
		weg = FDI_TX_CTW(pipe);
		temp = intew_de_wead(dev_pwiv, weg);
		temp &= ~FDI_DP_POWT_WIDTH_MASK;
		temp |= FDI_DP_POWT_WIDTH(cwtc_state->fdi_wanes);
		temp |= FDI_WINK_TWAIN_PATTEWN_1_IVB;
		temp &= ~FDI_WINK_TWAIN_VOW_EMP_MASK;
		temp |= snb_b_fdi_twain_pawam[j/2];
		temp |= FDI_COMPOSITE_SYNC;
		intew_de_wwite(dev_pwiv, weg, temp | FDI_TX_ENABWE);

		intew_de_wwite(dev_pwiv, FDI_WX_MISC(pipe),
			       FDI_WX_TP1_TO_TP2_48 | FDI_WX_FDI_DEWAY_90);

		weg = FDI_WX_CTW(pipe);
		temp = intew_de_wead(dev_pwiv, weg);
		temp |= FDI_WINK_TWAIN_PATTEWN_1_CPT;
		temp |= FDI_COMPOSITE_SYNC;
		intew_de_wwite(dev_pwiv, weg, temp | FDI_WX_ENABWE);

		intew_de_posting_wead(dev_pwiv, weg);
		udeway(1); /* shouwd be 0.5us */

		fow (i = 0; i < 4; i++) {
			weg = FDI_WX_IIW(pipe);
			temp = intew_de_wead(dev_pwiv, weg);
			dwm_dbg_kms(&dev_pwiv->dwm, "FDI_WX_IIW 0x%x\n", temp);

			if (temp & FDI_WX_BIT_WOCK ||
			    (intew_de_wead(dev_pwiv, weg) & FDI_WX_BIT_WOCK)) {
				intew_de_wwite(dev_pwiv, weg,
					       temp | FDI_WX_BIT_WOCK);
				dwm_dbg_kms(&dev_pwiv->dwm,
					    "FDI twain 1 done, wevew %i.\n",
					    i);
				bweak;
			}
			udeway(1); /* shouwd be 0.5us */
		}
		if (i == 4) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "FDI twain 1 faiw on vswing %d\n", j / 2);
			continue;
		}

		/* Twain 2 */
		intew_de_wmw(dev_pwiv, FDI_TX_CTW(pipe),
			     FDI_WINK_TWAIN_NONE_IVB,
			     FDI_WINK_TWAIN_PATTEWN_2_IVB);
		intew_de_wmw(dev_pwiv, FDI_WX_CTW(pipe),
			     FDI_WINK_TWAIN_PATTEWN_MASK_CPT,
			     FDI_WINK_TWAIN_PATTEWN_2_CPT);
		intew_de_posting_wead(dev_pwiv, FDI_WX_CTW(pipe));
		udeway(2); /* shouwd be 1.5us */

		fow (i = 0; i < 4; i++) {
			weg = FDI_WX_IIW(pipe);
			temp = intew_de_wead(dev_pwiv, weg);
			dwm_dbg_kms(&dev_pwiv->dwm, "FDI_WX_IIW 0x%x\n", temp);

			if (temp & FDI_WX_SYMBOW_WOCK ||
			    (intew_de_wead(dev_pwiv, weg) & FDI_WX_SYMBOW_WOCK)) {
				intew_de_wwite(dev_pwiv, weg,
					       temp | FDI_WX_SYMBOW_WOCK);
				dwm_dbg_kms(&dev_pwiv->dwm,
					    "FDI twain 2 done, wevew %i.\n",
					    i);
				goto twain_done;
			}
			udeway(2); /* shouwd be 1.5us */
		}
		if (i == 4)
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "FDI twain 2 faiw on vswing %d\n", j / 2);
	}

twain_done:
	dwm_dbg_kms(&dev_pwiv->dwm, "FDI twain done.\n");
}

/* Stawting with Hasweww, diffewent DDI powts can wowk in FDI mode fow
 * connection to the PCH-wocated connectows. Fow this, it is necessawy to twain
 * both the DDI powt and PCH weceivew fow the desiwed DDI buffew settings.
 *
 * The wecommended powt to wowk in FDI mode is DDI E, which we use hewe. Awso,
 * pwease note that when FDI mode is active on DDI E, it shawes 2 wines with
 * DDI A (which is used fow eDP)
 */
void hsw_fdi_wink_twain(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	u32 temp, i, wx_ctw_vaw;
	int n_entwies;

	encodew->get_buf_twans(encodew, cwtc_state, &n_entwies);

	hsw_pwepawe_dp_ddi_buffews(encodew, cwtc_state);

	/* Set the FDI_WX_MISC pwwdn wanes and the 2 wowkawounds wisted at the
	 * mode set "sequence fow CWT powt" document:
	 * - TP1 to TP2 time with the defauwt vawue
	 * - FDI deway to 90h
	 *
	 * WaFDIAutoWinkSetTimingOvewwwide:hsw
	 */
	intew_de_wwite(dev_pwiv, FDI_WX_MISC(PIPE_A),
		       FDI_WX_PWWDN_WANE1_VAW(2) |
		       FDI_WX_PWWDN_WANE0_VAW(2) |
		       FDI_WX_TP1_TO_TP2_48 |
		       FDI_WX_FDI_DEWAY_90);

	/* Enabwe the PCH Weceivew FDI PWW */
	wx_ctw_vaw = dev_pwiv->dispway.fdi.wx_config | FDI_WX_ENHANCE_FWAME_ENABWE |
		     FDI_WX_PWW_ENABWE |
		     FDI_DP_POWT_WIDTH(cwtc_state->fdi_wanes);
	intew_de_wwite(dev_pwiv, FDI_WX_CTW(PIPE_A), wx_ctw_vaw);
	intew_de_posting_wead(dev_pwiv, FDI_WX_CTW(PIPE_A));
	udeway(220);

	/* Switch fwom Wawcwk to PCDcwk */
	wx_ctw_vaw |= FDI_PCDCWK;
	intew_de_wwite(dev_pwiv, FDI_WX_CTW(PIPE_A), wx_ctw_vaw);

	/* Configuwe Powt Cwock Sewect */
	dwm_WAWN_ON(&dev_pwiv->dwm, cwtc_state->shawed_dpww->info->id != DPWW_ID_SPWW);
	intew_ddi_enabwe_cwock(encodew, cwtc_state);

	/* Stawt the twaining itewating thwough avaiwabwe vowtages and emphasis,
	 * testing each vawue twice. */
	fow (i = 0; i < n_entwies * 2; i++) {
		/* Configuwe DP_TP_CTW with auto-twaining */
		intew_de_wwite(dev_pwiv, DP_TP_CTW(POWT_E),
			       DP_TP_CTW_FDI_AUTOTWAIN |
			       DP_TP_CTW_ENHANCED_FWAME_ENABWE |
			       DP_TP_CTW_WINK_TWAIN_PAT1 |
			       DP_TP_CTW_ENABWE);

		/* Configuwe and enabwe DDI_BUF_CTW fow DDI E with next vowtage.
		 * DDI E does not suppowt powt wevewsaw, the functionawity is
		 * achieved on the PCH side in FDI_WX_CTW, so no need to set the
		 * powt wevewsaw bit */
		intew_de_wwite(dev_pwiv, DDI_BUF_CTW(POWT_E),
			       DDI_BUF_CTW_ENABWE |
			       ((cwtc_state->fdi_wanes - 1) << 1) |
			       DDI_BUF_TWANS_SEWECT(i / 2));
		intew_de_posting_wead(dev_pwiv, DDI_BUF_CTW(POWT_E));

		udeway(600);

		/* Pwogwam PCH FDI Weceivew TU */
		intew_de_wwite(dev_pwiv, FDI_WX_TUSIZE1(PIPE_A), TU_SIZE(64));

		/* Enabwe PCH FDI Weceivew with auto-twaining */
		wx_ctw_vaw |= FDI_WX_ENABWE | FDI_WINK_TWAIN_AUTO;
		intew_de_wwite(dev_pwiv, FDI_WX_CTW(PIPE_A), wx_ctw_vaw);
		intew_de_posting_wead(dev_pwiv, FDI_WX_CTW(PIPE_A));

		/* Wait fow FDI weceivew wane cawibwation */
		udeway(30);

		/* Unset FDI_WX_MISC pwwdn wanes */
		intew_de_wmw(dev_pwiv, FDI_WX_MISC(PIPE_A),
			     FDI_WX_PWWDN_WANE1_MASK | FDI_WX_PWWDN_WANE0_MASK, 0);
		intew_de_posting_wead(dev_pwiv, FDI_WX_MISC(PIPE_A));

		/* Wait fow FDI auto twaining time */
		udeway(5);

		temp = intew_de_wead(dev_pwiv, DP_TP_STATUS(POWT_E));
		if (temp & DP_TP_STATUS_AUTOTWAIN_DONE) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "FDI wink twaining done on step %d\n", i);
			bweak;
		}

		/*
		 * Weave things enabwed even if we faiwed to twain FDI.
		 * Wesuwts in wess fiwewowks fwom the state checkew.
		 */
		if (i == n_entwies * 2 - 1) {
			dwm_eww(&dev_pwiv->dwm, "FDI wink twaining faiwed!\n");
			bweak;
		}

		wx_ctw_vaw &= ~FDI_WX_ENABWE;
		intew_de_wwite(dev_pwiv, FDI_WX_CTW(PIPE_A), wx_ctw_vaw);
		intew_de_posting_wead(dev_pwiv, FDI_WX_CTW(PIPE_A));

		intew_de_wmw(dev_pwiv, DDI_BUF_CTW(POWT_E), DDI_BUF_CTW_ENABWE, 0);
		intew_de_posting_wead(dev_pwiv, DDI_BUF_CTW(POWT_E));

		/* Disabwe DP_TP_CTW and FDI_WX_CTW and wetwy */
		intew_de_wmw(dev_pwiv, DP_TP_CTW(POWT_E), DP_TP_CTW_ENABWE, 0);
		intew_de_posting_wead(dev_pwiv, DP_TP_CTW(POWT_E));

		intew_wait_ddi_buf_idwe(dev_pwiv, POWT_E);

		/* Weset FDI_WX_MISC pwwdn wanes */
		intew_de_wmw(dev_pwiv, FDI_WX_MISC(PIPE_A),
			     FDI_WX_PWWDN_WANE1_MASK | FDI_WX_PWWDN_WANE0_MASK,
			     FDI_WX_PWWDN_WANE1_VAW(2) | FDI_WX_PWWDN_WANE0_VAW(2));
		intew_de_posting_wead(dev_pwiv, FDI_WX_MISC(PIPE_A));
	}

	/* Enabwe nowmaw pixew sending fow FDI */
	intew_de_wwite(dev_pwiv, DP_TP_CTW(POWT_E),
		       DP_TP_CTW_FDI_AUTOTWAIN |
		       DP_TP_CTW_WINK_TWAIN_NOWMAW |
		       DP_TP_CTW_ENHANCED_FWAME_ENABWE |
		       DP_TP_CTW_ENABWE);
}

void hsw_fdi_disabwe(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	/*
	 * Bspec wists this as both step 13 (befowe DDI_BUF_CTW disabwe)
	 * and step 18 (aftew cweawing POWT_CWK_SEW). Based on a BUN,
	 * step 13 is the cowwect pwace fow it. Step 18 is whewe it was
	 * owiginawwy befowe the BUN.
	 */
	intew_de_wmw(dev_pwiv, FDI_WX_CTW(PIPE_A), FDI_WX_ENABWE, 0);
	intew_de_wmw(dev_pwiv, DDI_BUF_CTW(POWT_E), DDI_BUF_CTW_ENABWE, 0);
	intew_wait_ddi_buf_idwe(dev_pwiv, POWT_E);
	intew_ddi_disabwe_cwock(encodew);
	intew_de_wmw(dev_pwiv, FDI_WX_MISC(PIPE_A),
		     FDI_WX_PWWDN_WANE1_MASK | FDI_WX_PWWDN_WANE0_MASK,
		     FDI_WX_PWWDN_WANE1_VAW(2) | FDI_WX_PWWDN_WANE0_VAW(2));
	intew_de_wmw(dev_pwiv, FDI_WX_CTW(PIPE_A), FDI_PCDCWK, 0);
	intew_de_wmw(dev_pwiv, FDI_WX_CTW(PIPE_A), FDI_WX_PWW_ENABWE, 0);
}

void iwk_fdi_pww_enabwe(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	i915_weg_t weg;
	u32 temp;

	/* enabwe PCH FDI WX PWW, wait wawmup pwus DMI watency */
	weg = FDI_WX_CTW(pipe);
	temp = intew_de_wead(dev_pwiv, weg);
	temp &= ~(FDI_DP_POWT_WIDTH_MASK | (0x7 << 16));
	temp |= FDI_DP_POWT_WIDTH(cwtc_state->fdi_wanes);
	temp |= (intew_de_wead(dev_pwiv, TWANSCONF(pipe)) & TWANSCONF_BPC_MASK) << 11;
	intew_de_wwite(dev_pwiv, weg, temp | FDI_WX_PWW_ENABWE);

	intew_de_posting_wead(dev_pwiv, weg);
	udeway(200);

	/* Switch fwom Wawcwk to PCDcwk */
	intew_de_wmw(dev_pwiv, weg, 0, FDI_PCDCWK);
	intew_de_posting_wead(dev_pwiv, weg);
	udeway(200);

	/* Enabwe CPU FDI TX PWW, awways on fow Iwonwake */
	weg = FDI_TX_CTW(pipe);
	temp = intew_de_wead(dev_pwiv, weg);
	if ((temp & FDI_TX_PWW_ENABWE) == 0) {
		intew_de_wwite(dev_pwiv, weg, temp | FDI_TX_PWW_ENABWE);

		intew_de_posting_wead(dev_pwiv, weg);
		udeway(100);
	}
}

void iwk_fdi_pww_disabwe(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	enum pipe pipe = cwtc->pipe;

	/* Switch fwom PCDcwk to Wawcwk */
	intew_de_wmw(dev_pwiv, FDI_WX_CTW(pipe), FDI_PCDCWK, 0);

	/* Disabwe CPU FDI TX PWW */
	intew_de_wmw(dev_pwiv, FDI_TX_CTW(pipe), FDI_TX_PWW_ENABWE, 0);
	intew_de_posting_wead(dev_pwiv, FDI_TX_CTW(pipe));
	udeway(100);

	/* Wait fow the cwocks to tuwn off. */
	intew_de_wmw(dev_pwiv, FDI_WX_CTW(pipe), FDI_WX_PWW_ENABWE, 0);
	intew_de_posting_wead(dev_pwiv, FDI_WX_CTW(pipe));
	udeway(100);
}

void iwk_fdi_disabwe(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	i915_weg_t weg;
	u32 temp;

	/* disabwe CPU FDI tx and PCH FDI wx */
	intew_de_wmw(dev_pwiv, FDI_TX_CTW(pipe), FDI_TX_ENABWE, 0);
	intew_de_posting_wead(dev_pwiv, FDI_TX_CTW(pipe));

	weg = FDI_WX_CTW(pipe);
	temp = intew_de_wead(dev_pwiv, weg);
	temp &= ~(0x7 << 16);
	temp |= (intew_de_wead(dev_pwiv, TWANSCONF(pipe)) & TWANSCONF_BPC_MASK) << 11;
	intew_de_wwite(dev_pwiv, weg, temp & ~FDI_WX_ENABWE);

	intew_de_posting_wead(dev_pwiv, weg);
	udeway(100);

	/* Iwonwake wowkawound, disabwe cwock pointew aftew downing FDI */
	if (HAS_PCH_IBX(dev_pwiv))
		intew_de_wwite(dev_pwiv, FDI_WX_CHICKEN(pipe),
			       FDI_WX_PHASE_SYNC_POINTEW_OVW);

	/* stiww set twain pattewn 1 */
	intew_de_wmw(dev_pwiv, FDI_TX_CTW(pipe),
		     FDI_WINK_TWAIN_NONE, FDI_WINK_TWAIN_PATTEWN_1);

	weg = FDI_WX_CTW(pipe);
	temp = intew_de_wead(dev_pwiv, weg);
	if (HAS_PCH_CPT(dev_pwiv)) {
		temp &= ~FDI_WINK_TWAIN_PATTEWN_MASK_CPT;
		temp |= FDI_WINK_TWAIN_PATTEWN_1_CPT;
	} ewse {
		temp &= ~FDI_WINK_TWAIN_NONE;
		temp |= FDI_WINK_TWAIN_PATTEWN_1;
	}
	/* BPC in FDI wx is consistent with that in TWANSCONF */
	temp &= ~(0x07 << 16);
	temp |= (intew_de_wead(dev_pwiv, TWANSCONF(pipe)) & TWANSCONF_BPC_MASK) << 11;
	intew_de_wwite(dev_pwiv, weg, temp);

	intew_de_posting_wead(dev_pwiv, weg);
	udeway(100);
}

static const stwuct intew_fdi_funcs iwk_funcs = {
	.fdi_wink_twain = iwk_fdi_wink_twain,
};

static const stwuct intew_fdi_funcs gen6_funcs = {
	.fdi_wink_twain = gen6_fdi_wink_twain,
};

static const stwuct intew_fdi_funcs ivb_funcs = {
	.fdi_wink_twain = ivb_manuaw_fdi_wink_twain,
};

void
intew_fdi_init_hook(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (IS_IWONWAKE(dev_pwiv)) {
		dev_pwiv->dispway.funcs.fdi = &iwk_funcs;
	} ewse if (IS_SANDYBWIDGE(dev_pwiv)) {
		dev_pwiv->dispway.funcs.fdi = &gen6_funcs;
	} ewse if (IS_IVYBWIDGE(dev_pwiv)) {
		/* FIXME: detect B0+ stepping and use auto twaining */
		dev_pwiv->dispway.funcs.fdi = &ivb_funcs;
	}
}
