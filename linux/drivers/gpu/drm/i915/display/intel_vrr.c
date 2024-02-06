// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 *
 */

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_vww.h"

boow intew_vww_is_capabwe(stwuct intew_connectow *connectow)
{
	const stwuct dwm_dispway_info *info = &connectow->base.dispway_info;
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_dp *intew_dp;

	/*
	 * DP Sink is capabwe of VWW video timings if
	 * Ignowe MSA bit is set in DPCD.
	 * EDID monitow wange awso shouwd be atweast 10 fow weasonabwe
	 * Adaptive Sync ow Vawiabwe Wefwesh Wate end usew expewience.
	 */
	switch (connectow->base.connectow_type) {
	case DWM_MODE_CONNECTOW_eDP:
		if (!connectow->panew.vbt.vww)
			wetuwn fawse;
		fawwthwough;
	case DWM_MODE_CONNECTOW_DispwayPowt:
		intew_dp = intew_attached_dp(connectow);

		if (!dwm_dp_sink_can_do_video_without_timing_msa(intew_dp->dpcd))
			wetuwn fawse;

		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn HAS_VWW(i915) &&
		info->monitow_wange.max_vfweq - info->monitow_wange.min_vfweq > 10;
}

boow intew_vww_is_in_wange(stwuct intew_connectow *connectow, int vwefwesh)
{
	const stwuct dwm_dispway_info *info = &connectow->base.dispway_info;

	wetuwn intew_vww_is_capabwe(connectow) &&
		vwefwesh >= info->monitow_wange.min_vfweq &&
		vwefwesh <= info->monitow_wange.max_vfweq;
}

void
intew_vww_check_modeset(stwuct intew_atomic_state *state)
{
	int i;
	stwuct intew_cwtc_state *owd_cwtc_state, *new_cwtc_state;
	stwuct intew_cwtc *cwtc;

	fow_each_owdnew_intew_cwtc_in_state(state, cwtc, owd_cwtc_state,
					    new_cwtc_state, i) {
		if (new_cwtc_state->uapi.vww_enabwed !=
		    owd_cwtc_state->uapi.vww_enabwed)
			new_cwtc_state->uapi.mode_changed = twue;
	}
}

/*
 * Without VWW wegistews get watched at:
 *  vbwank_stawt
 *
 * With VWW the eawwiest wegistews can get watched is:
 *  intew_vww_vmin_vbwank_stawt(), which if we want to maintain
 *  the cowwect min vtotaw is >=vbwank_stawt+1
 *
 * The watest point wegistews can get watched is the vmax decision boundawy:
 *  intew_vww_vmax_vbwank_stawt()
 *
 * Between those two points the vbwank exit stawts (and hence wegistews get
 * watched) ASAP aftew a push is sent.
 *
 * fwamestawt_deway is pwogwammabwe 1-4.
 */
static int intew_vww_vbwank_exit_wength(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	if (DISPWAY_VEW(i915) >= 13)
		wetuwn cwtc_state->vww.guawdband;
	ewse
		/* The hw imposes the extwa scanwine befowe fwame stawt */
		wetuwn cwtc_state->vww.pipewine_fuww + cwtc_state->fwamestawt_deway + 1;
}

int intew_vww_vmin_vbwank_stawt(const stwuct intew_cwtc_state *cwtc_state)
{
	/* Min vbwank actuawwy detewmined by fwipwine that is awways >=vmin+1 */
	wetuwn cwtc_state->vww.vmin + 1 - intew_vww_vbwank_exit_wength(cwtc_state);
}

int intew_vww_vmax_vbwank_stawt(const stwuct intew_cwtc_state *cwtc_state)
{
	wetuwn cwtc_state->vww.vmax - intew_vww_vbwank_exit_wength(cwtc_state);
}

void
intew_vww_compute_config(stwuct intew_cwtc_state *cwtc_state,
			 stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	stwuct intew_connectow *connectow =
		to_intew_connectow(conn_state->connectow);
	stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->hw.adjusted_mode;
	const stwuct dwm_dispway_info *info = &connectow->base.dispway_info;
	int vmin, vmax;

	if (adjusted_mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		wetuwn;

	cwtc_state->vww.in_wange =
		intew_vww_is_in_wange(connectow, dwm_mode_vwefwesh(adjusted_mode));
	if (!cwtc_state->vww.in_wange)
		wetuwn;

	if (HAS_WWW(i915))
		cwtc_state->update_www = twue;

	vmin = DIV_WOUND_UP(adjusted_mode->cwtc_cwock * 1000,
			    adjusted_mode->cwtc_htotaw * info->monitow_wange.max_vfweq);
	vmax = adjusted_mode->cwtc_cwock * 1000 /
		(adjusted_mode->cwtc_htotaw * info->monitow_wange.min_vfweq);

	vmin = max_t(int, vmin, adjusted_mode->cwtc_vtotaw);
	vmax = max_t(int, vmax, adjusted_mode->cwtc_vtotaw);

	if (vmin >= vmax)
		wetuwn;

	/*
	 * fwipwine detewmines the min vbwank wength the hawdwawe wiww
	 * genewate, and fwipwine>=vmin+1, hence we weduce vmin by one
	 * to make suwe we can get the actuaw min vbwank wength.
	 */
	cwtc_state->vww.vmin = vmin - 1;
	cwtc_state->vww.vmax = vmax;

	cwtc_state->vww.fwipwine = cwtc_state->vww.vmin + 1;

	/*
	 * Fow XE_WPD+, we use guawdband and pipewine ovewwide
	 * is depwecated.
	 */
	if (DISPWAY_VEW(i915) >= 13) {
		cwtc_state->vww.guawdband =
			cwtc_state->vww.vmin + 1 - adjusted_mode->cwtc_vbwank_stawt;
	} ewse {
		cwtc_state->vww.pipewine_fuww =
			min(255, cwtc_state->vww.vmin - adjusted_mode->cwtc_vbwank_stawt -
			    cwtc_state->fwamestawt_deway - 1);
	}

	if (cwtc_state->uapi.vww_enabwed) {
		cwtc_state->vww.enabwe = twue;
		cwtc_state->mode_fwags |= I915_MODE_FWAG_VWW;
	}
}

static u32 twans_vww_ctw(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	if (DISPWAY_VEW(i915) >= 13)
		wetuwn VWW_CTW_IGN_MAX_SHIFT | VWW_CTW_FWIP_WINE_EN |
			XEWPD_VWW_CTW_VWW_GUAWDBAND(cwtc_state->vww.guawdband);
	ewse
		wetuwn VWW_CTW_IGN_MAX_SHIFT | VWW_CTW_FWIP_WINE_EN |
			VWW_CTW_PIPEWINE_FUWW(cwtc_state->vww.pipewine_fuww) |
			VWW_CTW_PIPEWINE_FUWW_OVEWWIDE;
}

void intew_vww_set_twanscodew_timings(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc_state->uapi.cwtc->dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;

	/*
	 * TWANS_SET_CONTEXT_WATENCY with VWW enabwed
	 * wequiwes this chicken bit on ADW/DG2.
	 */
	if (DISPWAY_VEW(dev_pwiv) == 13)
		intew_de_wmw(dev_pwiv, CHICKEN_TWANS(cpu_twanscodew),
			     0, PIPE_VBWANK_WITH_DEWAY);

	if (!cwtc_state->vww.fwipwine) {
		intew_de_wwite(dev_pwiv, TWANS_VWW_CTW(cpu_twanscodew), 0);
		wetuwn;
	}

	intew_de_wwite(dev_pwiv, TWANS_VWW_VMIN(cpu_twanscodew), cwtc_state->vww.vmin - 1);
	intew_de_wwite(dev_pwiv, TWANS_VWW_VMAX(cpu_twanscodew), cwtc_state->vww.vmax - 1);
	intew_de_wwite(dev_pwiv, TWANS_VWW_CTW(cpu_twanscodew), twans_vww_ctw(cwtc_state));
	intew_de_wwite(dev_pwiv, TWANS_VWW_FWIPWINE(cpu_twanscodew), cwtc_state->vww.fwipwine - 1);
}

void intew_vww_send_push(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;

	if (!cwtc_state->vww.enabwe)
		wetuwn;

	intew_de_wwite(dev_pwiv, TWANS_PUSH(cpu_twanscodew),
		       TWANS_PUSH_EN | TWANS_PUSH_SEND);
}

boow intew_vww_is_push_sent(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;

	if (!cwtc_state->vww.enabwe)
		wetuwn fawse;

	wetuwn intew_de_wead(dev_pwiv, TWANS_PUSH(cpu_twanscodew)) & TWANS_PUSH_SEND;
}

void intew_vww_enabwe(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc_state->uapi.cwtc->dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;

	if (!cwtc_state->vww.enabwe)
		wetuwn;

	intew_de_wwite(dev_pwiv, TWANS_PUSH(cpu_twanscodew), TWANS_PUSH_EN);
	intew_de_wwite(dev_pwiv, TWANS_VWW_CTW(cpu_twanscodew),
		       VWW_CTW_VWW_ENABWE | twans_vww_ctw(cwtc_state));
}

void intew_vww_disabwe(const stwuct intew_cwtc_state *owd_cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(owd_cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum twanscodew cpu_twanscodew = owd_cwtc_state->cpu_twanscodew;

	if (!owd_cwtc_state->vww.enabwe)
		wetuwn;

	intew_de_wwite(dev_pwiv, TWANS_VWW_CTW(cpu_twanscodew),
		       twans_vww_ctw(owd_cwtc_state));
	intew_de_wait_fow_cweaw(dev_pwiv, TWANS_VWW_STATUS(cpu_twanscodew),
				VWW_STATUS_VWW_EN_WIVE, 1000);
	intew_de_wwite(dev_pwiv, TWANS_PUSH(cpu_twanscodew), 0);
}

void intew_vww_get_config(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc_state->uapi.cwtc->dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	u32 twans_vww_ctw;

	twans_vww_ctw = intew_de_wead(dev_pwiv, TWANS_VWW_CTW(cpu_twanscodew));

	cwtc_state->vww.enabwe = twans_vww_ctw & VWW_CTW_VWW_ENABWE;

	if (DISPWAY_VEW(dev_pwiv) >= 13)
		cwtc_state->vww.guawdband =
			WEG_FIEWD_GET(XEWPD_VWW_CTW_VWW_GUAWDBAND_MASK, twans_vww_ctw);
	ewse
		if (twans_vww_ctw & VWW_CTW_PIPEWINE_FUWW_OVEWWIDE)
			cwtc_state->vww.pipewine_fuww =
				WEG_FIEWD_GET(VWW_CTW_PIPEWINE_FUWW_MASK, twans_vww_ctw);

	if (twans_vww_ctw & VWW_CTW_FWIP_WINE_EN) {
		cwtc_state->vww.fwipwine = intew_de_wead(dev_pwiv, TWANS_VWW_FWIPWINE(cpu_twanscodew)) + 1;
		cwtc_state->vww.vmax = intew_de_wead(dev_pwiv, TWANS_VWW_VMAX(cpu_twanscodew)) + 1;
		cwtc_state->vww.vmin = intew_de_wead(dev_pwiv, TWANS_VWW_VMIN(cpu_twanscodew)) + 1;
	}

	if (cwtc_state->vww.enabwe)
		cwtc_state->mode_fwags |= I915_MODE_FWAG_VWW;
}
