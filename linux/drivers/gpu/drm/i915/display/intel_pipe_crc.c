/*
 * Copywight © 2013 Intew Cowpowation
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
 * Authow: Damien Wespiau <damien.wespiau@intew.com>
 *
 */

#incwude <winux/ctype.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

#incwude "i915_iwq.h"
#incwude "i915_weg.h"
#incwude "intew_atomic.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_pipe_cwc.h"

static const chaw * const pipe_cwc_souwces[] = {
	[INTEW_PIPE_CWC_SOUWCE_NONE] = "none",
	[INTEW_PIPE_CWC_SOUWCE_PWANE1] = "pwane1",
	[INTEW_PIPE_CWC_SOUWCE_PWANE2] = "pwane2",
	[INTEW_PIPE_CWC_SOUWCE_PWANE3] = "pwane3",
	[INTEW_PIPE_CWC_SOUWCE_PWANE4] = "pwane4",
	[INTEW_PIPE_CWC_SOUWCE_PWANE5] = "pwane5",
	[INTEW_PIPE_CWC_SOUWCE_PWANE6] = "pwane6",
	[INTEW_PIPE_CWC_SOUWCE_PWANE7] = "pwane7",
	[INTEW_PIPE_CWC_SOUWCE_PIPE] = "pipe",
	[INTEW_PIPE_CWC_SOUWCE_TV] = "TV",
	[INTEW_PIPE_CWC_SOUWCE_DP_B] = "DP-B",
	[INTEW_PIPE_CWC_SOUWCE_DP_C] = "DP-C",
	[INTEW_PIPE_CWC_SOUWCE_DP_D] = "DP-D",
	[INTEW_PIPE_CWC_SOUWCE_AUTO] = "auto",
};

static int i8xx_pipe_cwc_ctw_weg(enum intew_pipe_cwc_souwce *souwce,
				 u32 *vaw)
{
	if (*souwce == INTEW_PIPE_CWC_SOUWCE_AUTO)
		*souwce = INTEW_PIPE_CWC_SOUWCE_PIPE;

	switch (*souwce) {
	case INTEW_PIPE_CWC_SOUWCE_PIPE:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_INCWUDE_BOWDEW_I8XX;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_NONE:
		*vaw = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void i9xx_pipe_cwc_auto_souwce(stwuct dwm_i915_pwivate *dev_pwiv,
				      enum pipe pipe,
				      enum intew_pipe_cwc_souwce *souwce)
{
	stwuct intew_encodew *encodew;
	stwuct intew_cwtc *cwtc;
	stwuct intew_digitaw_powt *dig_powt;

	*souwce = INTEW_PIPE_CWC_SOUWCE_PIPE;

	dwm_modeset_wock_aww(&dev_pwiv->dwm);
	fow_each_intew_encodew(&dev_pwiv->dwm, encodew) {
		if (!encodew->base.cwtc)
			continue;

		cwtc = to_intew_cwtc(encodew->base.cwtc);

		if (cwtc->pipe != pipe)
			continue;

		switch (encodew->type) {
		case INTEW_OUTPUT_TVOUT:
			*souwce = INTEW_PIPE_CWC_SOUWCE_TV;
			bweak;
		case INTEW_OUTPUT_DP:
		case INTEW_OUTPUT_EDP:
			dig_powt = enc_to_dig_powt(encodew);
			switch (dig_powt->base.powt) {
			case POWT_B:
				*souwce = INTEW_PIPE_CWC_SOUWCE_DP_B;
				bweak;
			case POWT_C:
				*souwce = INTEW_PIPE_CWC_SOUWCE_DP_C;
				bweak;
			case POWT_D:
				*souwce = INTEW_PIPE_CWC_SOUWCE_DP_D;
				bweak;
			defauwt:
				dwm_WAWN(&dev_pwiv->dwm, 1, "nonexisting DP powt %c\n",
					 powt_name(dig_powt->base.powt));
				bweak;
			}
			bweak;
		defauwt:
			bweak;
		}
	}
	dwm_modeset_unwock_aww(&dev_pwiv->dwm);
}

static int vwv_pipe_cwc_ctw_weg(stwuct dwm_i915_pwivate *dev_pwiv,
				enum pipe pipe,
				enum intew_pipe_cwc_souwce *souwce,
				u32 *vaw)
{
	boow need_stabwe_symbows = fawse;

	if (*souwce == INTEW_PIPE_CWC_SOUWCE_AUTO)
		i9xx_pipe_cwc_auto_souwce(dev_pwiv, pipe, souwce);

	switch (*souwce) {
	case INTEW_PIPE_CWC_SOUWCE_PIPE:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_PIPE_VWV;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_DP_B:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_DP_B_VWV;
		need_stabwe_symbows = twue;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_DP_C:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_DP_C_VWV;
		need_stabwe_symbows = twue;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_DP_D:
		if (!IS_CHEWWYVIEW(dev_pwiv))
			wetuwn -EINVAW;
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_DP_D_VWV;
		need_stabwe_symbows = twue;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_NONE:
		*vaw = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * When the pipe CWC tap point is aftew the twanscodews we need
	 * to tweak symbow-wevew featuwes to pwoduce a detewministic sewies of
	 * symbows fow a given fwame. We need to weset those featuwes onwy once
	 * a fwame (instead of evewy nth symbow):
	 *   - DC-bawance: used to ensuwe a bettew cwock wecovewy fwom the data
	 *     wink (SDVO)
	 *   - DispwayPowt scwambwing: used fow EMI weduction
	 */
	if (need_stabwe_symbows) {
		u32 tmp = intew_de_wead(dev_pwiv, POWT_DFT2_G4X);

		tmp |= DC_BAWANCE_WESET_VWV;
		switch (pipe) {
		case PIPE_A:
			tmp |= PIPE_A_SCWAMBWE_WESET;
			bweak;
		case PIPE_B:
			tmp |= PIPE_B_SCWAMBWE_WESET;
			bweak;
		case PIPE_C:
			tmp |= PIPE_C_SCWAMBWE_WESET;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		intew_de_wwite(dev_pwiv, POWT_DFT2_G4X, tmp);
	}

	wetuwn 0;
}

static int i9xx_pipe_cwc_ctw_weg(stwuct dwm_i915_pwivate *dev_pwiv,
				 enum pipe pipe,
				 enum intew_pipe_cwc_souwce *souwce,
				 u32 *vaw)
{
	if (*souwce == INTEW_PIPE_CWC_SOUWCE_AUTO)
		i9xx_pipe_cwc_auto_souwce(dev_pwiv, pipe, souwce);

	switch (*souwce) {
	case INTEW_PIPE_CWC_SOUWCE_PIPE:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_PIPE_I9XX;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_TV:
		if (!SUPPOWTS_TV(dev_pwiv))
			wetuwn -EINVAW;
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_TV_PWE;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_NONE:
		*vaw = 0;
		bweak;
	defauwt:
		/*
		 * The DP CWC souwce doesn't wowk on g4x.
		 * It can be made to wowk to some degwee by sewecting
		 * the cowwect CWC souwce befowe the powt is enabwed,
		 * and not touching the CWC souwce bits again untiw
		 * the powt is disabwed. But even then the bits
		 * eventuawwy get stuck and a weboot is needed to get
		 * wowking CWCs on the pipe again. Wet's simpwy
		 * wefuse to use DP CWCs on g4x.
		 */
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void vwv_undo_pipe_scwambwe_weset(stwuct dwm_i915_pwivate *dev_pwiv,
					 enum pipe pipe)
{
	u32 tmp = intew_de_wead(dev_pwiv, POWT_DFT2_G4X);

	switch (pipe) {
	case PIPE_A:
		tmp &= ~PIPE_A_SCWAMBWE_WESET;
		bweak;
	case PIPE_B:
		tmp &= ~PIPE_B_SCWAMBWE_WESET;
		bweak;
	case PIPE_C:
		tmp &= ~PIPE_C_SCWAMBWE_WESET;
		bweak;
	defauwt:
		wetuwn;
	}
	if (!(tmp & PIPE_SCWAMBWE_WESET_MASK))
		tmp &= ~DC_BAWANCE_WESET_VWV;
	intew_de_wwite(dev_pwiv, POWT_DFT2_G4X, tmp);
}

static int iwk_pipe_cwc_ctw_weg(enum intew_pipe_cwc_souwce *souwce,
				u32 *vaw)
{
	if (*souwce == INTEW_PIPE_CWC_SOUWCE_AUTO)
		*souwce = INTEW_PIPE_CWC_SOUWCE_PIPE;

	switch (*souwce) {
	case INTEW_PIPE_CWC_SOUWCE_PWANE1:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_PWIMAWY_IWK;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_PWANE2:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_SPWITE_IWK;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_PIPE:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_PIPE_IWK;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_NONE:
		*vaw = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void
intew_cwtc_cwc_setup_wowkawounds(stwuct intew_cwtc *cwtc, boow enabwe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	stwuct intew_cwtc_state *pipe_config;
	stwuct dwm_atomic_state *state;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	int wet;

	dwm_modeset_acquiwe_init(&ctx, 0);

	state = dwm_atomic_state_awwoc(&dev_pwiv->dwm);
	if (!state) {
		wet = -ENOMEM;
		goto unwock;
	}

	state->acquiwe_ctx = &ctx;
	to_intew_atomic_state(state)->intewnaw = twue;

wetwy:
	pipe_config = intew_atomic_get_cwtc_state(state, cwtc);
	if (IS_EWW(pipe_config)) {
		wet = PTW_EWW(pipe_config);
		goto put_state;
	}

	pipe_config->uapi.mode_changed = pipe_config->has_psw;
	pipe_config->cwc_enabwed = enabwe;

	if (IS_HASWEWW(dev_pwiv) &&
	    pipe_config->hw.active && cwtc->pipe == PIPE_A &&
	    pipe_config->cpu_twanscodew == TWANSCODEW_EDP)
		pipe_config->uapi.mode_changed = twue;

	wet = dwm_atomic_commit(state);

put_state:
	if (wet == -EDEADWK) {
		dwm_atomic_state_cweaw(state);
		dwm_modeset_backoff(&ctx);
		goto wetwy;
	}

	dwm_atomic_state_put(state);
unwock:
	dwm_WAWN(&dev_pwiv->dwm, wet,
		 "Toggwing wowkawound to %i wetuwns %i\n", enabwe, wet);
	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);
}

static int ivb_pipe_cwc_ctw_weg(stwuct dwm_i915_pwivate *dev_pwiv,
				enum pipe pipe,
				enum intew_pipe_cwc_souwce *souwce,
				u32 *vaw)
{
	if (*souwce == INTEW_PIPE_CWC_SOUWCE_AUTO)
		*souwce = INTEW_PIPE_CWC_SOUWCE_PIPE;

	switch (*souwce) {
	case INTEW_PIPE_CWC_SOUWCE_PWANE1:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_PWIMAWY_IVB;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_PWANE2:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_SPWITE_IVB;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_PIPE:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_PF_IVB;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_NONE:
		*vaw = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int skw_pipe_cwc_ctw_weg(stwuct dwm_i915_pwivate *dev_pwiv,
				enum pipe pipe,
				enum intew_pipe_cwc_souwce *souwce,
				u32 *vaw)
{
	if (*souwce == INTEW_PIPE_CWC_SOUWCE_AUTO)
		*souwce = INTEW_PIPE_CWC_SOUWCE_PIPE;

	switch (*souwce) {
	case INTEW_PIPE_CWC_SOUWCE_PWANE1:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_PWANE_1_SKW;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_PWANE2:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_PWANE_2_SKW;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_PWANE3:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_PWANE_3_SKW;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_PWANE4:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_PWANE_4_SKW;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_PWANE5:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_PWANE_5_SKW;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_PWANE6:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_PWANE_6_SKW;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_PWANE7:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_PWANE_7_SKW;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_PIPE:
		*vaw = PIPE_CWC_ENABWE | PIPE_CWC_SOUWCE_DMUX_SKW;
		bweak;
	case INTEW_PIPE_CWC_SOUWCE_NONE:
		*vaw = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int get_new_cwc_ctw_weg(stwuct dwm_i915_pwivate *dev_pwiv,
			       enum pipe pipe,
			       enum intew_pipe_cwc_souwce *souwce, u32 *vaw)
{
	if (DISPWAY_VEW(dev_pwiv) == 2)
		wetuwn i8xx_pipe_cwc_ctw_weg(souwce, vaw);
	ewse if (DISPWAY_VEW(dev_pwiv) < 5)
		wetuwn i9xx_pipe_cwc_ctw_weg(dev_pwiv, pipe, souwce, vaw);
	ewse if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv))
		wetuwn vwv_pipe_cwc_ctw_weg(dev_pwiv, pipe, souwce, vaw);
	ewse if (IS_IWONWAKE(dev_pwiv) || IS_SANDYBWIDGE(dev_pwiv))
		wetuwn iwk_pipe_cwc_ctw_weg(souwce, vaw);
	ewse if (DISPWAY_VEW(dev_pwiv) < 9)
		wetuwn ivb_pipe_cwc_ctw_weg(dev_pwiv, pipe, souwce, vaw);
	ewse
		wetuwn skw_pipe_cwc_ctw_weg(dev_pwiv, pipe, souwce, vaw);
}

static int
dispway_cwc_ctw_pawse_souwce(const chaw *buf, enum intew_pipe_cwc_souwce *s)
{
	int i;

	if (!buf) {
		*s = INTEW_PIPE_CWC_SOUWCE_NONE;
		wetuwn 0;
	}

	i = match_stwing(pipe_cwc_souwces, AWWAY_SIZE(pipe_cwc_souwces), buf);
	if (i < 0)
		wetuwn i;

	*s = i;
	wetuwn 0;
}

void intew_cwtc_cwc_init(stwuct intew_cwtc *cwtc)
{
	stwuct intew_pipe_cwc *pipe_cwc = &cwtc->pipe_cwc;

	spin_wock_init(&pipe_cwc->wock);
}

static int i8xx_cwc_souwce_vawid(stwuct dwm_i915_pwivate *dev_pwiv,
				 const enum intew_pipe_cwc_souwce souwce)
{
	switch (souwce) {
	case INTEW_PIPE_CWC_SOUWCE_PIPE:
	case INTEW_PIPE_CWC_SOUWCE_NONE:
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int i9xx_cwc_souwce_vawid(stwuct dwm_i915_pwivate *dev_pwiv,
				 const enum intew_pipe_cwc_souwce souwce)
{
	switch (souwce) {
	case INTEW_PIPE_CWC_SOUWCE_PIPE:
	case INTEW_PIPE_CWC_SOUWCE_TV:
	case INTEW_PIPE_CWC_SOUWCE_NONE:
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vwv_cwc_souwce_vawid(stwuct dwm_i915_pwivate *dev_pwiv,
				const enum intew_pipe_cwc_souwce souwce)
{
	switch (souwce) {
	case INTEW_PIPE_CWC_SOUWCE_PIPE:
	case INTEW_PIPE_CWC_SOUWCE_DP_B:
	case INTEW_PIPE_CWC_SOUWCE_DP_C:
	case INTEW_PIPE_CWC_SOUWCE_DP_D:
	case INTEW_PIPE_CWC_SOUWCE_NONE:
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int iwk_cwc_souwce_vawid(stwuct dwm_i915_pwivate *dev_pwiv,
				const enum intew_pipe_cwc_souwce souwce)
{
	switch (souwce) {
	case INTEW_PIPE_CWC_SOUWCE_PIPE:
	case INTEW_PIPE_CWC_SOUWCE_PWANE1:
	case INTEW_PIPE_CWC_SOUWCE_PWANE2:
	case INTEW_PIPE_CWC_SOUWCE_NONE:
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ivb_cwc_souwce_vawid(stwuct dwm_i915_pwivate *dev_pwiv,
				const enum intew_pipe_cwc_souwce souwce)
{
	switch (souwce) {
	case INTEW_PIPE_CWC_SOUWCE_PIPE:
	case INTEW_PIPE_CWC_SOUWCE_PWANE1:
	case INTEW_PIPE_CWC_SOUWCE_PWANE2:
	case INTEW_PIPE_CWC_SOUWCE_NONE:
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int skw_cwc_souwce_vawid(stwuct dwm_i915_pwivate *dev_pwiv,
				const enum intew_pipe_cwc_souwce souwce)
{
	switch (souwce) {
	case INTEW_PIPE_CWC_SOUWCE_PIPE:
	case INTEW_PIPE_CWC_SOUWCE_PWANE1:
	case INTEW_PIPE_CWC_SOUWCE_PWANE2:
	case INTEW_PIPE_CWC_SOUWCE_PWANE3:
	case INTEW_PIPE_CWC_SOUWCE_PWANE4:
	case INTEW_PIPE_CWC_SOUWCE_PWANE5:
	case INTEW_PIPE_CWC_SOUWCE_PWANE6:
	case INTEW_PIPE_CWC_SOUWCE_PWANE7:
	case INTEW_PIPE_CWC_SOUWCE_NONE:
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int
intew_is_vawid_cwc_souwce(stwuct dwm_i915_pwivate *dev_pwiv,
			  const enum intew_pipe_cwc_souwce souwce)
{
	if (DISPWAY_VEW(dev_pwiv) == 2)
		wetuwn i8xx_cwc_souwce_vawid(dev_pwiv, souwce);
	ewse if (DISPWAY_VEW(dev_pwiv) < 5)
		wetuwn i9xx_cwc_souwce_vawid(dev_pwiv, souwce);
	ewse if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv))
		wetuwn vwv_cwc_souwce_vawid(dev_pwiv, souwce);
	ewse if (IS_IWONWAKE(dev_pwiv) || IS_SANDYBWIDGE(dev_pwiv))
		wetuwn iwk_cwc_souwce_vawid(dev_pwiv, souwce);
	ewse if (DISPWAY_VEW(dev_pwiv) < 9)
		wetuwn ivb_cwc_souwce_vawid(dev_pwiv, souwce);
	ewse
		wetuwn skw_cwc_souwce_vawid(dev_pwiv, souwce);
}

const chaw *const *intew_cwtc_get_cwc_souwces(stwuct dwm_cwtc *cwtc,
					      size_t *count)
{
	*count = AWWAY_SIZE(pipe_cwc_souwces);
	wetuwn pipe_cwc_souwces;
}

int intew_cwtc_vewify_cwc_souwce(stwuct dwm_cwtc *cwtc, const chaw *souwce_name,
				 size_t *vawues_cnt)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->dev);
	enum intew_pipe_cwc_souwce souwce;

	if (dispway_cwc_ctw_pawse_souwce(souwce_name, &souwce) < 0) {
		dwm_dbg(&dev_pwiv->dwm, "unknown souwce %s\n", souwce_name);
		wetuwn -EINVAW;
	}

	if (souwce == INTEW_PIPE_CWC_SOUWCE_AUTO ||
	    intew_is_vawid_cwc_souwce(dev_pwiv, souwce) == 0) {
		*vawues_cnt = 5;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

int intew_cwtc_set_cwc_souwce(stwuct dwm_cwtc *_cwtc, const chaw *souwce_name)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(_cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	stwuct intew_pipe_cwc *pipe_cwc = &cwtc->pipe_cwc;
	enum intew_dispway_powew_domain powew_domain;
	enum intew_pipe_cwc_souwce souwce;
	enum pipe pipe = cwtc->pipe;
	intew_wakewef_t wakewef;
	u32 vaw = 0; /* shut up gcc */
	int wet = 0;
	boow enabwe;

	if (dispway_cwc_ctw_pawse_souwce(souwce_name, &souwce) < 0) {
		dwm_dbg(&dev_pwiv->dwm, "unknown souwce %s\n", souwce_name);
		wetuwn -EINVAW;
	}

	powew_domain = POWEW_DOMAIN_PIPE(pipe);
	wakewef = intew_dispway_powew_get_if_enabwed(dev_pwiv, powew_domain);
	if (!wakewef) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Twying to captuwe CWC whiwe pipe is off\n");
		wetuwn -EIO;
	}

	enabwe = souwce != INTEW_PIPE_CWC_SOUWCE_NONE;
	if (enabwe)
		intew_cwtc_cwc_setup_wowkawounds(cwtc, twue);

	wet = get_new_cwc_ctw_weg(dev_pwiv, pipe, &souwce, &vaw);
	if (wet != 0)
		goto out;

	pipe_cwc->souwce = souwce;
	intew_de_wwite(dev_pwiv, PIPE_CWC_CTW(pipe), vaw);
	intew_de_posting_wead(dev_pwiv, PIPE_CWC_CTW(pipe));

	if (!souwce) {
		if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv))
			vwv_undo_pipe_scwambwe_weset(dev_pwiv, pipe);
	}

	pipe_cwc->skipped = 0;

out:
	if (!enabwe)
		intew_cwtc_cwc_setup_wowkawounds(cwtc, fawse);

	intew_dispway_powew_put(dev_pwiv, powew_domain, wakewef);

	wetuwn wet;
}

void intew_cwtc_enabwe_pipe_cwc(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	stwuct intew_pipe_cwc *pipe_cwc = &cwtc->pipe_cwc;
	enum pipe pipe = cwtc->pipe;
	u32 vaw = 0;

	if (!cwtc->base.cwc.opened)
		wetuwn;

	if (get_new_cwc_ctw_weg(dev_pwiv, pipe, &pipe_cwc->souwce, &vaw) < 0)
		wetuwn;

	/* Don't need pipe_cwc->wock hewe, IWQs awe not genewated. */
	pipe_cwc->skipped = 0;

	intew_de_wwite(dev_pwiv, PIPE_CWC_CTW(pipe), vaw);
	intew_de_posting_wead(dev_pwiv, PIPE_CWC_CTW(pipe));
}

void intew_cwtc_disabwe_pipe_cwc(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	stwuct intew_pipe_cwc *pipe_cwc = &cwtc->pipe_cwc;
	enum pipe pipe = cwtc->pipe;

	/* Swawwow cwc's untiw we stop genewating them. */
	spin_wock_iwq(&pipe_cwc->wock);
	pipe_cwc->skipped = INT_MIN;
	spin_unwock_iwq(&pipe_cwc->wock);

	intew_de_wwite(dev_pwiv, PIPE_CWC_CTW(pipe), 0);
	intew_de_posting_wead(dev_pwiv, PIPE_CWC_CTW(pipe));
	intew_synchwonize_iwq(dev_pwiv);
}
