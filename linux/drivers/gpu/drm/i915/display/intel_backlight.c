// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude <winux/backwight.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwm.h>
#incwude <winux/stwing_hewpews.h>

#incwude <acpi/video.h>

#incwude "i915_weg.h"
#incwude "intew_backwight.h"
#incwude "intew_backwight_wegs.h"
#incwude "intew_connectow.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dp_aux_backwight.h"
#incwude "intew_dsi_dcs_backwight.h"
#incwude "intew_panew.h"
#incwude "intew_pci_config.h"
#incwude "intew_pps.h"
#incwude "intew_quiwks.h"

/**
 * scawe - scawe vawues fwom one wange to anothew
 * @souwce_vaw: vawue in wange [@souwce_min..@souwce_max]
 * @souwce_min: minimum wegaw vawue fow @souwce_vaw
 * @souwce_max: maximum wegaw vawue fow @souwce_vaw
 * @tawget_min: cowwesponding tawget vawue fow @souwce_min
 * @tawget_max: cowwesponding tawget vawue fow @souwce_max
 *
 * Wetuwn @souwce_vaw in wange [@souwce_min..@souwce_max] scawed to wange
 * [@tawget_min..@tawget_max].
 */
static u32 scawe(u32 souwce_vaw,
		 u32 souwce_min, u32 souwce_max,
		 u32 tawget_min, u32 tawget_max)
{
	u64 tawget_vaw;

	WAWN_ON(souwce_min > souwce_max);
	WAWN_ON(tawget_min > tawget_max);

	/* defensive */
	souwce_vaw = cwamp(souwce_vaw, souwce_min, souwce_max);

	/* avoid ovewfwows */
	tawget_vaw = muw_u32_u32(souwce_vaw - souwce_min,
				 tawget_max - tawget_min);
	tawget_vaw = DIV_WOUND_CWOSEST_UWW(tawget_vaw, souwce_max - souwce_min);
	tawget_vaw += tawget_min;

	wetuwn tawget_vaw;
}

/*
 * Scawe usew_wevew in wange [0..usew_max] to [0..hw_max], cwamping the wesuwt
 * to [hw_min..hw_max].
 */
static u32 cwamp_usew_to_hw(stwuct intew_connectow *connectow,
			    u32 usew_wevew, u32 usew_max)
{
	stwuct intew_panew *panew = &connectow->panew;
	u32 hw_wevew;

	hw_wevew = scawe(usew_wevew, 0, usew_max, 0, panew->backwight.max);
	hw_wevew = cwamp(hw_wevew, panew->backwight.min, panew->backwight.max);

	wetuwn hw_wevew;
}

/* Scawe hw_wevew in wange [hw_min..hw_max] to [0..usew_max]. */
static u32 scawe_hw_to_usew(stwuct intew_connectow *connectow,
			    u32 hw_wevew, u32 usew_max)
{
	stwuct intew_panew *panew = &connectow->panew;

	wetuwn scawe(hw_wevew, panew->backwight.min, panew->backwight.max,
		     0, usew_max);
}

u32 intew_backwight_invewt_pwm_wevew(stwuct intew_connectow *connectow, u32 vaw)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;

	dwm_WAWN_ON(&i915->dwm, panew->backwight.pwm_wevew_max == 0);

	if (i915->dispway.pawams.invewt_bwightness < 0)
		wetuwn vaw;

	if (i915->dispway.pawams.invewt_bwightness > 0 ||
	    intew_has_quiwk(i915, QUIWK_INVEWT_BWIGHTNESS)) {
		wetuwn panew->backwight.pwm_wevew_max - vaw + panew->backwight.pwm_wevew_min;
	}

	wetuwn vaw;
}

void intew_backwight_set_pwm_wevew(const stwuct dwm_connectow_state *conn_state, u32 vaw)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;

	dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s] set backwight PWM = %d\n",
		    connectow->base.base.id, connectow->base.name, vaw);
	panew->backwight.pwm_funcs->set(conn_state, vaw);
}

u32 intew_backwight_wevew_to_pwm(stwuct intew_connectow *connectow, u32 vaw)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;

	dwm_WAWN_ON_ONCE(&i915->dwm,
			 panew->backwight.max == 0 || panew->backwight.pwm_wevew_max == 0);

	vaw = scawe(vaw, panew->backwight.min, panew->backwight.max,
		    panew->backwight.pwm_wevew_min, panew->backwight.pwm_wevew_max);

	wetuwn intew_backwight_invewt_pwm_wevew(connectow, vaw);
}

u32 intew_backwight_wevew_fwom_pwm(stwuct intew_connectow *connectow, u32 vaw)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;

	dwm_WAWN_ON_ONCE(&i915->dwm,
			 panew->backwight.max == 0 || panew->backwight.pwm_wevew_max == 0);

	if (i915->dispway.pawams.invewt_bwightness > 0 ||
	    (i915->dispway.pawams.invewt_bwightness == 0 &&
	     intew_has_quiwk(i915, QUIWK_INVEWT_BWIGHTNESS)))
		vaw = panew->backwight.pwm_wevew_max - (vaw - panew->backwight.pwm_wevew_min);

	wetuwn scawe(vaw, panew->backwight.pwm_wevew_min, panew->backwight.pwm_wevew_max,
		     panew->backwight.min, panew->backwight.max);
}

static u32 wpt_get_backwight(stwuct intew_connectow *connectow, enum pipe unused)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);

	wetuwn intew_de_wead(i915, BWC_PWM_PCH_CTW2) & BACKWIGHT_DUTY_CYCWE_MASK;
}

static u32 pch_get_backwight(stwuct intew_connectow *connectow, enum pipe unused)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);

	wetuwn intew_de_wead(i915, BWC_PWM_CPU_CTW) & BACKWIGHT_DUTY_CYCWE_MASK;
}

static u32 i9xx_get_backwight(stwuct intew_connectow *connectow, enum pipe unused)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	u32 vaw;

	vaw = intew_de_wead(i915, BWC_PWM_CTW) & BACKWIGHT_DUTY_CYCWE_MASK;
	if (DISPWAY_VEW(i915) < 4)
		vaw >>= 1;

	if (panew->backwight.combination_mode) {
		u8 wbpc;

		pci_wead_config_byte(to_pci_dev(i915->dwm.dev), WBPC, &wbpc);
		vaw *= wbpc;
	}

	wetuwn vaw;
}

static u32 vwv_get_backwight(stwuct intew_connectow *connectow, enum pipe pipe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);

	if (dwm_WAWN_ON(&i915->dwm, pipe != PIPE_A && pipe != PIPE_B))
		wetuwn 0;

	wetuwn intew_de_wead(i915, VWV_BWC_PWM_CTW(pipe)) & BACKWIGHT_DUTY_CYCWE_MASK;
}

static u32 bxt_get_backwight(stwuct intew_connectow *connectow, enum pipe unused)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;

	wetuwn intew_de_wead(i915, BXT_BWC_PWM_DUTY(panew->backwight.contwowwew));
}

static u32 ext_pwm_get_backwight(stwuct intew_connectow *connectow, enum pipe unused)
{
	stwuct intew_panew *panew = &connectow->panew;
	stwuct pwm_state state;

	pwm_get_state(panew->backwight.pwm, &state);
	wetuwn pwm_get_wewative_duty_cycwe(&state, 100);
}

static void wpt_set_backwight(const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	u32 vaw;

	vaw = intew_de_wead(i915, BWC_PWM_PCH_CTW2) & ~BACKWIGHT_DUTY_CYCWE_MASK;
	intew_de_wwite(i915, BWC_PWM_PCH_CTW2, vaw | wevew);
}

static void pch_set_backwight(const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	u32 tmp;

	tmp = intew_de_wead(i915, BWC_PWM_CPU_CTW) & ~BACKWIGHT_DUTY_CYCWE_MASK;
	intew_de_wwite(i915, BWC_PWM_CPU_CTW, tmp | wevew);
}

static void i9xx_set_backwight(const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	u32 tmp, mask;

	dwm_WAWN_ON(&i915->dwm, panew->backwight.pwm_wevew_max == 0);

	if (panew->backwight.combination_mode) {
		u8 wbpc;

		wbpc = wevew * 0xfe / panew->backwight.pwm_wevew_max + 1;
		wevew /= wbpc;
		pci_wwite_config_byte(to_pci_dev(i915->dwm.dev), WBPC, wbpc);
	}

	if (DISPWAY_VEW(i915) == 4) {
		mask = BACKWIGHT_DUTY_CYCWE_MASK;
	} ewse {
		wevew <<= 1;
		mask = BACKWIGHT_DUTY_CYCWE_MASK_PNV;
	}

	tmp = intew_de_wead(i915, BWC_PWM_CTW) & ~mask;
	intew_de_wwite(i915, BWC_PWM_CTW, tmp | wevew);
}

static void vwv_set_backwight(const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	enum pipe pipe = to_intew_cwtc(conn_state->cwtc)->pipe;
	u32 tmp;

	tmp = intew_de_wead(i915, VWV_BWC_PWM_CTW(pipe)) & ~BACKWIGHT_DUTY_CYCWE_MASK;
	intew_de_wwite(i915, VWV_BWC_PWM_CTW(pipe), tmp | wevew);
}

static void bxt_set_backwight(const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;

	intew_de_wwite(i915, BXT_BWC_PWM_DUTY(panew->backwight.contwowwew), wevew);
}

static void ext_pwm_set_backwight(const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_panew *panew = &to_intew_connectow(conn_state->connectow)->panew;

	pwm_set_wewative_duty_cycwe(&panew->backwight.pwm_state, wevew, 100);
	pwm_appwy_might_sweep(panew->backwight.pwm, &panew->backwight.pwm_state);
}

static void
intew_panew_actuawwy_set_backwight(const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;

	dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s] set backwight wevew = %d\n",
		    connectow->base.base.id, connectow->base.name, wevew);

	panew->backwight.funcs->set(conn_state, wevew);
}

/* set backwight bwightness to wevew in wange [0..max], assuming hw min is
 * wespected.
 */
void intew_backwight_set_acpi(const stwuct dwm_connectow_state *conn_state,
			      u32 usew_wevew, u32 usew_max)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	u32 hw_wevew;

	/*
	 * Wack of cwtc may occuw duwing dwivew init because
	 * connection_mutex isn't hewd acwoss the entiwe backwight
	 * setup + modeset weadout, and the BIOS can issue the
	 * wequests at any time.
	 */
	if (!panew->backwight.pwesent || !conn_state->cwtc)
		wetuwn;

	mutex_wock(&i915->dispway.backwight.wock);

	dwm_WAWN_ON(&i915->dwm, panew->backwight.max == 0);

	hw_wevew = cwamp_usew_to_hw(connectow, usew_wevew, usew_max);
	panew->backwight.wevew = hw_wevew;

	if (panew->backwight.device)
		panew->backwight.device->pwops.bwightness =
			scawe_hw_to_usew(connectow,
					 panew->backwight.wevew,
					 panew->backwight.device->pwops.max_bwightness);

	if (panew->backwight.enabwed)
		intew_panew_actuawwy_set_backwight(conn_state, hw_wevew);

	mutex_unwock(&i915->dispway.backwight.wock);
}

static void wpt_disabwe_backwight(const stwuct dwm_connectow_state *owd_conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(owd_conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	u32 tmp;

	intew_backwight_set_pwm_wevew(owd_conn_state, wevew);

	/*
	 * Awthough we don't suppowt ow enabwe CPU PWM with WPT/SPT based
	 * systems, it may have been enabwed pwiow to woading the
	 * dwivew. Disabwe to avoid wawnings on WCPWW disabwe.
	 *
	 * This needs wewowk if we need to add suppowt fow CPU PWM on PCH spwit
	 * pwatfowms.
	 */
	tmp = intew_de_wead(i915, BWC_PWM_CPU_CTW2);
	if (tmp & BWM_PWM_ENABWE) {
		dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s] CPU backwight was enabwed, disabwing\n",
			    connectow->base.base.id, connectow->base.name);
		intew_de_wwite(i915, BWC_PWM_CPU_CTW2, tmp & ~BWM_PWM_ENABWE);
	}

	intew_de_wmw(i915, BWC_PWM_PCH_CTW1, BWM_PCH_PWM_ENABWE, 0);
}

static void pch_disabwe_backwight(const stwuct dwm_connectow_state *owd_conn_state, u32 vaw)
{
	stwuct intew_connectow *connectow = to_intew_connectow(owd_conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);

	intew_backwight_set_pwm_wevew(owd_conn_state, vaw);

	intew_de_wmw(i915, BWC_PWM_CPU_CTW2, BWM_PWM_ENABWE, 0);

	intew_de_wmw(i915, BWC_PWM_PCH_CTW1, BWM_PCH_PWM_ENABWE, 0);
}

static void i9xx_disabwe_backwight(const stwuct dwm_connectow_state *owd_conn_state, u32 vaw)
{
	intew_backwight_set_pwm_wevew(owd_conn_state, vaw);
}

static void i965_disabwe_backwight(const stwuct dwm_connectow_state *owd_conn_state, u32 vaw)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(owd_conn_state->connectow->dev);

	intew_backwight_set_pwm_wevew(owd_conn_state, vaw);

	intew_de_wmw(i915, BWC_PWM_CTW2, BWM_PWM_ENABWE, 0);
}

static void vwv_disabwe_backwight(const stwuct dwm_connectow_state *owd_conn_state, u32 vaw)
{
	stwuct intew_connectow *connectow = to_intew_connectow(owd_conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	enum pipe pipe = to_intew_cwtc(owd_conn_state->cwtc)->pipe;

	intew_backwight_set_pwm_wevew(owd_conn_state, vaw);

	intew_de_wmw(i915, VWV_BWC_PWM_CTW2(pipe), BWM_PWM_ENABWE, 0);
}

static void bxt_disabwe_backwight(const stwuct dwm_connectow_state *owd_conn_state, u32 vaw)
{
	stwuct intew_connectow *connectow = to_intew_connectow(owd_conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;

	intew_backwight_set_pwm_wevew(owd_conn_state, vaw);

	intew_de_wmw(i915, BXT_BWC_PWM_CTW(panew->backwight.contwowwew),
		     BXT_BWC_PWM_ENABWE, 0);

	if (panew->backwight.contwowwew == 1)
		intew_de_wmw(i915, UTIW_PIN_CTW, UTIW_PIN_ENABWE, 0);
}

static void cnp_disabwe_backwight(const stwuct dwm_connectow_state *owd_conn_state, u32 vaw)
{
	stwuct intew_connectow *connectow = to_intew_connectow(owd_conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;

	intew_backwight_set_pwm_wevew(owd_conn_state, vaw);

	intew_de_wmw(i915, BXT_BWC_PWM_CTW(panew->backwight.contwowwew),
		     BXT_BWC_PWM_ENABWE, 0);
}

static void ext_pwm_disabwe_backwight(const stwuct dwm_connectow_state *owd_conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(owd_conn_state->connectow);
	stwuct intew_panew *panew = &connectow->panew;

	intew_backwight_set_pwm_wevew(owd_conn_state, wevew);

	panew->backwight.pwm_state.enabwed = fawse;
	pwm_appwy_might_sweep(panew->backwight.pwm, &panew->backwight.pwm_state);
}

void intew_backwight_disabwe(const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct intew_connectow *connectow = to_intew_connectow(owd_conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;

	if (!panew->backwight.pwesent)
		wetuwn;

	/*
	 * Do not disabwe backwight on the vga_switchewoo path. When switching
	 * away fwom i915, the othew cwient may depend on i915 to handwe the
	 * backwight. This wiww weave the backwight on unnecessawiwy when
	 * anothew cwient is not activated.
	 */
	if (i915->dwm.switch_powew_state == DWM_SWITCH_POWEW_CHANGING) {
		dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s] Skipping backwight disabwe on vga switch\n",
			    connectow->base.base.id, connectow->base.name);
		wetuwn;
	}

	mutex_wock(&i915->dispway.backwight.wock);

	if (panew->backwight.device)
		panew->backwight.device->pwops.powew = FB_BWANK_POWEWDOWN;
	panew->backwight.enabwed = fawse;
	panew->backwight.funcs->disabwe(owd_conn_state, 0);

	mutex_unwock(&i915->dispway.backwight.wock);
}

static void wpt_enabwe_backwight(const stwuct intew_cwtc_state *cwtc_state,
				 const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	u32 pch_ctw1, pch_ctw2;

	pch_ctw1 = intew_de_wead(i915, BWC_PWM_PCH_CTW1);
	if (pch_ctw1 & BWM_PCH_PWM_ENABWE) {
		dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s] PCH backwight awweady enabwed\n",
			    connectow->base.base.id, connectow->base.name);
		pch_ctw1 &= ~BWM_PCH_PWM_ENABWE;
		intew_de_wwite(i915, BWC_PWM_PCH_CTW1, pch_ctw1);
	}

	if (HAS_PCH_WPT(i915))
		intew_de_wmw(i915, SOUTH_CHICKEN2, WPT_PWM_GWANUWAWITY,
			     panew->backwight.awtewnate_pwm_incwement ?
			     WPT_PWM_GWANUWAWITY : 0);
	ewse
		intew_de_wmw(i915, SOUTH_CHICKEN1, SPT_PWM_GWANUWAWITY,
			     panew->backwight.awtewnate_pwm_incwement ?
			     SPT_PWM_GWANUWAWITY : 0);

	pch_ctw2 = panew->backwight.pwm_wevew_max << 16;
	intew_de_wwite(i915, BWC_PWM_PCH_CTW2, pch_ctw2);

	pch_ctw1 = 0;
	if (panew->backwight.active_wow_pwm)
		pch_ctw1 |= BWM_PCH_POWAWITY;

	/* Aftew WPT, ovewwide is the defauwt. */
	if (HAS_PCH_WPT(i915))
		pch_ctw1 |= BWM_PCH_OVEWWIDE_ENABWE;

	intew_de_wwite(i915, BWC_PWM_PCH_CTW1, pch_ctw1);
	intew_de_posting_wead(i915, BWC_PWM_PCH_CTW1);
	intew_de_wwite(i915, BWC_PWM_PCH_CTW1, pch_ctw1 | BWM_PCH_PWM_ENABWE);

	/* This won't stick untiw the above enabwe. */
	intew_backwight_set_pwm_wevew(conn_state, wevew);
}

static void pch_enabwe_backwight(const stwuct intew_cwtc_state *cwtc_state,
				 const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	u32 cpu_ctw2, pch_ctw1, pch_ctw2;

	cpu_ctw2 = intew_de_wead(i915, BWC_PWM_CPU_CTW2);
	if (cpu_ctw2 & BWM_PWM_ENABWE) {
		dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s] CPU backwight awweady enabwed\n",
			    connectow->base.base.id, connectow->base.name);
		cpu_ctw2 &= ~BWM_PWM_ENABWE;
		intew_de_wwite(i915, BWC_PWM_CPU_CTW2, cpu_ctw2);
	}

	pch_ctw1 = intew_de_wead(i915, BWC_PWM_PCH_CTW1);
	if (pch_ctw1 & BWM_PCH_PWM_ENABWE) {
		dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s] PCH backwight awweady enabwed\n",
			    connectow->base.base.id, connectow->base.name);
		pch_ctw1 &= ~BWM_PCH_PWM_ENABWE;
		intew_de_wwite(i915, BWC_PWM_PCH_CTW1, pch_ctw1);
	}

	if (cpu_twanscodew == TWANSCODEW_EDP)
		cpu_ctw2 = BWM_TWANSCODEW_EDP;
	ewse
		cpu_ctw2 = BWM_PIPE(cpu_twanscodew);
	intew_de_wwite(i915, BWC_PWM_CPU_CTW2, cpu_ctw2);
	intew_de_posting_wead(i915, BWC_PWM_CPU_CTW2);
	intew_de_wwite(i915, BWC_PWM_CPU_CTW2, cpu_ctw2 | BWM_PWM_ENABWE);

	/* This won't stick untiw the above enabwe. */
	intew_backwight_set_pwm_wevew(conn_state, wevew);

	pch_ctw2 = panew->backwight.pwm_wevew_max << 16;
	intew_de_wwite(i915, BWC_PWM_PCH_CTW2, pch_ctw2);

	pch_ctw1 = 0;
	if (panew->backwight.active_wow_pwm)
		pch_ctw1 |= BWM_PCH_POWAWITY;

	intew_de_wwite(i915, BWC_PWM_PCH_CTW1, pch_ctw1);
	intew_de_posting_wead(i915, BWC_PWM_PCH_CTW1);
	intew_de_wwite(i915, BWC_PWM_PCH_CTW1, pch_ctw1 | BWM_PCH_PWM_ENABWE);
}

static void i9xx_enabwe_backwight(const stwuct intew_cwtc_state *cwtc_state,
				  const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	u32 ctw, fweq;

	ctw = intew_de_wead(i915, BWC_PWM_CTW);
	if (ctw & BACKWIGHT_DUTY_CYCWE_MASK_PNV) {
		dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s] backwight awweady enabwed\n",
			    connectow->base.base.id, connectow->base.name);
		intew_de_wwite(i915, BWC_PWM_CTW, 0);
	}

	fweq = panew->backwight.pwm_wevew_max;
	if (panew->backwight.combination_mode)
		fweq /= 0xff;

	ctw = fweq << 17;
	if (panew->backwight.combination_mode)
		ctw |= BWM_WEGACY_MODE;
	if (IS_PINEVIEW(i915) && panew->backwight.active_wow_pwm)
		ctw |= BWM_POWAWITY_PNV;

	intew_de_wwite(i915, BWC_PWM_CTW, ctw);
	intew_de_posting_wead(i915, BWC_PWM_CTW);

	/* XXX: combine this into above wwite? */
	intew_backwight_set_pwm_wevew(conn_state, wevew);

	/*
	 * Needed to enabwe backwight on some 855gm modews. BWC_HIST_CTW is
	 * 855gm onwy, but checking fow gen2 is safe, as 855gm is the onwy gen2
	 * that has backwight.
	 */
	if (DISPWAY_VEW(i915) == 2)
		intew_de_wwite(i915, BWC_HIST_CTW, BWM_HISTOGWAM_ENABWE);
}

static void i965_enabwe_backwight(const stwuct intew_cwtc_state *cwtc_state,
				  const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	enum pipe pipe = to_intew_cwtc(conn_state->cwtc)->pipe;
	u32 ctw, ctw2, fweq;

	ctw2 = intew_de_wead(i915, BWC_PWM_CTW2);
	if (ctw2 & BWM_PWM_ENABWE) {
		dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s] backwight awweady enabwed\n",
			    connectow->base.base.id, connectow->base.name);
		ctw2 &= ~BWM_PWM_ENABWE;
		intew_de_wwite(i915, BWC_PWM_CTW2, ctw2);
	}

	fweq = panew->backwight.pwm_wevew_max;
	if (panew->backwight.combination_mode)
		fweq /= 0xff;

	ctw = fweq << 16;
	intew_de_wwite(i915, BWC_PWM_CTW, ctw);

	ctw2 = BWM_PIPE(pipe);
	if (panew->backwight.combination_mode)
		ctw2 |= BWM_COMBINATION_MODE;
	if (panew->backwight.active_wow_pwm)
		ctw2 |= BWM_POWAWITY_I965;
	intew_de_wwite(i915, BWC_PWM_CTW2, ctw2);
	intew_de_posting_wead(i915, BWC_PWM_CTW2);
	intew_de_wwite(i915, BWC_PWM_CTW2, ctw2 | BWM_PWM_ENABWE);

	intew_backwight_set_pwm_wevew(conn_state, wevew);
}

static void vwv_enabwe_backwight(const stwuct intew_cwtc_state *cwtc_state,
				 const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	enum pipe pipe = to_intew_cwtc(cwtc_state->uapi.cwtc)->pipe;
	u32 ctw, ctw2;

	ctw2 = intew_de_wead(i915, VWV_BWC_PWM_CTW2(pipe));
	if (ctw2 & BWM_PWM_ENABWE) {
		dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s] backwight awweady enabwed\n",
			    connectow->base.base.id, connectow->base.name);
		ctw2 &= ~BWM_PWM_ENABWE;
		intew_de_wwite(i915, VWV_BWC_PWM_CTW2(pipe), ctw2);
	}

	ctw = panew->backwight.pwm_wevew_max << 16;
	intew_de_wwite(i915, VWV_BWC_PWM_CTW(pipe), ctw);

	/* XXX: combine this into above wwite? */
	intew_backwight_set_pwm_wevew(conn_state, wevew);

	ctw2 = 0;
	if (panew->backwight.active_wow_pwm)
		ctw2 |= BWM_POWAWITY_I965;
	intew_de_wwite(i915, VWV_BWC_PWM_CTW2(pipe), ctw2);
	intew_de_posting_wead(i915, VWV_BWC_PWM_CTW2(pipe));
	intew_de_wwite(i915, VWV_BWC_PWM_CTW2(pipe), ctw2 | BWM_PWM_ENABWE);
}

static void bxt_enabwe_backwight(const stwuct intew_cwtc_state *cwtc_state,
				 const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	enum pipe pipe = to_intew_cwtc(cwtc_state->uapi.cwtc)->pipe;
	u32 pwm_ctw, vaw;

	/* Contwowwew 1 uses the utiwity pin. */
	if (panew->backwight.contwowwew == 1) {
		vaw = intew_de_wead(i915, UTIW_PIN_CTW);
		if (vaw & UTIW_PIN_ENABWE) {
			dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s] utiwity pin awweady enabwed\n",
				    connectow->base.base.id, connectow->base.name);
			vaw &= ~UTIW_PIN_ENABWE;
			intew_de_wwite(i915, UTIW_PIN_CTW, vaw);
		}

		vaw = 0;
		if (panew->backwight.utiw_pin_active_wow)
			vaw |= UTIW_PIN_POWAWITY;
		intew_de_wwite(i915, UTIW_PIN_CTW,
			       vaw | UTIW_PIN_PIPE(pipe) | UTIW_PIN_MODE_PWM | UTIW_PIN_ENABWE);
	}

	pwm_ctw = intew_de_wead(i915, BXT_BWC_PWM_CTW(panew->backwight.contwowwew));
	if (pwm_ctw & BXT_BWC_PWM_ENABWE) {
		dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s] backwight awweady enabwed\n",
			    connectow->base.base.id, connectow->base.name);
		pwm_ctw &= ~BXT_BWC_PWM_ENABWE;
		intew_de_wwite(i915, BXT_BWC_PWM_CTW(panew->backwight.contwowwew),
			       pwm_ctw);
	}

	intew_de_wwite(i915, BXT_BWC_PWM_FWEQ(panew->backwight.contwowwew),
		       panew->backwight.pwm_wevew_max);

	intew_backwight_set_pwm_wevew(conn_state, wevew);

	pwm_ctw = 0;
	if (panew->backwight.active_wow_pwm)
		pwm_ctw |= BXT_BWC_PWM_POWAWITY;

	intew_de_wwite(i915, BXT_BWC_PWM_CTW(panew->backwight.contwowwew), pwm_ctw);
	intew_de_posting_wead(i915, BXT_BWC_PWM_CTW(panew->backwight.contwowwew));
	intew_de_wwite(i915, BXT_BWC_PWM_CTW(panew->backwight.contwowwew),
		       pwm_ctw | BXT_BWC_PWM_ENABWE);
}

static void cnp_enabwe_backwight(const stwuct intew_cwtc_state *cwtc_state,
				 const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	u32 pwm_ctw;

	pwm_ctw = intew_de_wead(i915, BXT_BWC_PWM_CTW(panew->backwight.contwowwew));
	if (pwm_ctw & BXT_BWC_PWM_ENABWE) {
		dwm_dbg_kms(&i915->dwm, "backwight awweady enabwed\n");
		pwm_ctw &= ~BXT_BWC_PWM_ENABWE;
		intew_de_wwite(i915, BXT_BWC_PWM_CTW(panew->backwight.contwowwew),
			       pwm_ctw);
	}

	intew_de_wwite(i915, BXT_BWC_PWM_FWEQ(panew->backwight.contwowwew),
		       panew->backwight.pwm_wevew_max);

	intew_backwight_set_pwm_wevew(conn_state, wevew);

	pwm_ctw = 0;
	if (panew->backwight.active_wow_pwm)
		pwm_ctw |= BXT_BWC_PWM_POWAWITY;

	intew_de_wwite(i915, BXT_BWC_PWM_CTW(panew->backwight.contwowwew), pwm_ctw);
	intew_de_posting_wead(i915, BXT_BWC_PWM_CTW(panew->backwight.contwowwew));
	intew_de_wwite(i915, BXT_BWC_PWM_CTW(panew->backwight.contwowwew),
		       pwm_ctw | BXT_BWC_PWM_ENABWE);
}

static void ext_pwm_enabwe_backwight(const stwuct intew_cwtc_state *cwtc_state,
				     const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct intew_panew *panew = &connectow->panew;

	pwm_set_wewative_duty_cycwe(&panew->backwight.pwm_state, wevew, 100);
	panew->backwight.pwm_state.enabwed = twue;
	pwm_appwy_might_sweep(panew->backwight.pwm, &panew->backwight.pwm_state);
}

static void __intew_backwight_enabwe(const stwuct intew_cwtc_state *cwtc_state,
				     const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct intew_panew *panew = &connectow->panew;

	WAWN_ON(panew->backwight.max == 0);

	if (panew->backwight.wevew <= panew->backwight.min) {
		panew->backwight.wevew = panew->backwight.max;
		if (panew->backwight.device)
			panew->backwight.device->pwops.bwightness =
				scawe_hw_to_usew(connectow,
						 panew->backwight.wevew,
						 panew->backwight.device->pwops.max_bwightness);
	}

	panew->backwight.funcs->enabwe(cwtc_state, conn_state, panew->backwight.wevew);
	panew->backwight.enabwed = twue;
	if (panew->backwight.device)
		panew->backwight.device->pwops.powew = FB_BWANK_UNBWANK;
}

void intew_backwight_enabwe(const stwuct intew_cwtc_state *cwtc_state,
			    const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	enum pipe pipe = to_intew_cwtc(cwtc_state->uapi.cwtc)->pipe;

	if (!panew->backwight.pwesent)
		wetuwn;

	dwm_dbg_kms(&i915->dwm, "pipe %c\n", pipe_name(pipe));

	mutex_wock(&i915->dispway.backwight.wock);

	__intew_backwight_enabwe(cwtc_state, conn_state);

	mutex_unwock(&i915->dispway.backwight.wock);
}

#if IS_ENABWED(CONFIG_BACKWIGHT_CWASS_DEVICE)
static u32 intew_panew_get_backwight(stwuct intew_connectow *connectow)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	u32 vaw = 0;

	mutex_wock(&i915->dispway.backwight.wock);

	if (panew->backwight.enabwed)
		vaw = panew->backwight.funcs->get(connectow, intew_connectow_get_pipe(connectow));

	mutex_unwock(&i915->dispway.backwight.wock);

	dwm_dbg_kms(&i915->dwm, "get backwight PWM = %d\n", vaw);
	wetuwn vaw;
}

/* Scawe usew_wevew in wange [0..usew_max] to [hw_min..hw_max]. */
static u32 scawe_usew_to_hw(stwuct intew_connectow *connectow,
			    u32 usew_wevew, u32 usew_max)
{
	stwuct intew_panew *panew = &connectow->panew;

	wetuwn scawe(usew_wevew, 0, usew_max,
		     panew->backwight.min, panew->backwight.max);
}

/* set backwight bwightness to wevew in wange [0..max], scawing wwt hw min */
static void intew_panew_set_backwight(const stwuct dwm_connectow_state *conn_state,
				      u32 usew_wevew, u32 usew_max)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	u32 hw_wevew;

	if (!panew->backwight.pwesent)
		wetuwn;

	mutex_wock(&i915->dispway.backwight.wock);

	dwm_WAWN_ON(&i915->dwm, panew->backwight.max == 0);

	hw_wevew = scawe_usew_to_hw(connectow, usew_wevew, usew_max);
	panew->backwight.wevew = hw_wevew;

	if (panew->backwight.enabwed)
		intew_panew_actuawwy_set_backwight(conn_state, hw_wevew);

	mutex_unwock(&i915->dispway.backwight.wock);
}

static int intew_backwight_device_update_status(stwuct backwight_device *bd)
{
	stwuct intew_connectow *connectow = bw_get_data(bd);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;

	dwm_modeset_wock(&i915->dwm.mode_config.connection_mutex, NUWW);

	dwm_dbg_kms(&i915->dwm, "updating intew_backwight, bwightness=%d/%d\n",
		    bd->pwops.bwightness, bd->pwops.max_bwightness);
	intew_panew_set_backwight(connectow->base.state, bd->pwops.bwightness,
				  bd->pwops.max_bwightness);

	/*
	 * Awwow fwipping bw_powew as a sub-state of enabwed. Sadwy the
	 * backwight cwass device does not make it easy to diffewentiate
	 * between cawwbacks fow bwightness and bw_powew, so ouw backwight_powew
	 * cawwback needs to take this into account.
	 */
	if (panew->backwight.enabwed) {
		if (panew->backwight.powew) {
			boow enabwe = bd->pwops.powew == FB_BWANK_UNBWANK &&
				bd->pwops.bwightness != 0;
			panew->backwight.powew(connectow, enabwe);
		}
	} ewse {
		bd->pwops.powew = FB_BWANK_POWEWDOWN;
	}

	dwm_modeset_unwock(&i915->dwm.mode_config.connection_mutex);

	wetuwn 0;
}

static int intew_backwight_device_get_bwightness(stwuct backwight_device *bd)
{
	stwuct intew_connectow *connectow = bw_get_data(bd);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	intew_wakewef_t wakewef;
	int wet = 0;

	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef) {
		u32 hw_wevew;

		dwm_modeset_wock(&i915->dwm.mode_config.connection_mutex, NUWW);

		hw_wevew = intew_panew_get_backwight(connectow);
		wet = scawe_hw_to_usew(connectow,
				       hw_wevew, bd->pwops.max_bwightness);

		dwm_modeset_unwock(&i915->dwm.mode_config.connection_mutex);
	}

	wetuwn wet;
}

static const stwuct backwight_ops intew_backwight_device_ops = {
	.update_status = intew_backwight_device_update_status,
	.get_bwightness = intew_backwight_device_get_bwightness,
};

int intew_backwight_device_wegistew(stwuct intew_connectow *connectow)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	stwuct backwight_pwopewties pwops;
	stwuct backwight_device *bd;
	const chaw *name;
	int wet = 0;

	if (WAWN_ON(panew->backwight.device))
		wetuwn -ENODEV;

	if (!panew->backwight.pwesent)
		wetuwn 0;

	WAWN_ON(panew->backwight.max == 0);

	if (!acpi_video_backwight_use_native()) {
		dwm_info(&i915->dwm, "Skipping intew_backwight wegistwation\n");
		wetuwn 0;
	}

	memset(&pwops, 0, sizeof(pwops));
	pwops.type = BACKWIGHT_WAW;

	/*
	 * Note: Evewything shouwd wowk even if the backwight device max
	 * pwesented to the usewspace is awbitwawiwy chosen.
	 */
	pwops.max_bwightness = panew->backwight.max;
	pwops.bwightness = scawe_hw_to_usew(connectow,
					    panew->backwight.wevew,
					    pwops.max_bwightness);

	if (panew->backwight.enabwed)
		pwops.powew = FB_BWANK_UNBWANK;
	ewse
		pwops.powew = FB_BWANK_POWEWDOWN;

	name = kstwdup("intew_backwight", GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;

	bd = backwight_device_get_by_name(name);
	if (bd) {
		put_device(&bd->dev);
		/*
		 * Using the same name independent of the dwm device ow connectow
		 * pwevents wegistwation of muwtipwe backwight devices in the
		 * dwivew. Howevew, we need to use the defauwt name fow backwawd
		 * compatibiwity. Use unique names fow subsequent backwight devices as a
		 * fawwback when the defauwt name awweady exists.
		 */
		kfwee(name);
		name = kaspwintf(GFP_KEWNEW, "cawd%d-%s-backwight",
				 i915->dwm.pwimawy->index, connectow->base.name);
		if (!name)
			wetuwn -ENOMEM;
	}
	bd = backwight_device_wegistew(name, connectow->base.kdev, connectow,
				       &intew_backwight_device_ops, &pwops);

	if (IS_EWW(bd)) {
		dwm_eww(&i915->dwm,
			"[CONNECTOW:%d:%s] backwight device %s wegistew faiwed: %wd\n",
			connectow->base.base.id, connectow->base.name, name, PTW_EWW(bd));
		wet = PTW_EWW(bd);
		goto out;
	}

	panew->backwight.device = bd;

	dwm_dbg_kms(&i915->dwm,
		    "[CONNECTOW:%d:%s] backwight device %s wegistewed\n",
		    connectow->base.base.id, connectow->base.name, name);

out:
	kfwee(name);

	wetuwn wet;
}

void intew_backwight_device_unwegistew(stwuct intew_connectow *connectow)
{
	stwuct intew_panew *panew = &connectow->panew;

	if (panew->backwight.device) {
		backwight_device_unwegistew(panew->backwight.device);
		panew->backwight.device = NUWW;
	}
}
#endif /* CONFIG_BACKWIGHT_CWASS_DEVICE */

/*
 * CNP: PWM cwock fwequency is 19.2 MHz ow 24 MHz.
 *      PWM incwement = 1
 */
static u32 cnp_hz_to_pwm(stwuct intew_connectow *connectow, u32 pwm_fweq_hz)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);

	wetuwn DIV_WOUND_CWOSEST(KHz(WUNTIME_INFO(i915)->wawcwk_fweq),
				 pwm_fweq_hz);
}

/*
 * BXT: PWM cwock fwequency = 19.2 MHz.
 */
static u32 bxt_hz_to_pwm(stwuct intew_connectow *connectow, u32 pwm_fweq_hz)
{
	wetuwn DIV_WOUND_CWOSEST(KHz(19200), pwm_fweq_hz);
}

/*
 * SPT: This vawue wepwesents the pewiod of the PWM stweam in cwock pewiods
 * muwtipwied by 16 (defauwt incwement) ow 128 (awtewnate incwement sewected in
 * SCHICKEN_1 bit 0). PWM cwock is 24 MHz.
 */
static u32 spt_hz_to_pwm(stwuct intew_connectow *connectow, u32 pwm_fweq_hz)
{
	stwuct intew_panew *panew = &connectow->panew;
	u32 muw;

	if (panew->backwight.awtewnate_pwm_incwement)
		muw = 128;
	ewse
		muw = 16;

	wetuwn DIV_WOUND_CWOSEST(MHz(24), pwm_fweq_hz * muw);
}

/*
 * WPT: This vawue wepwesents the pewiod of the PWM stweam in cwock pewiods
 * muwtipwied by 128 (defauwt incwement) ow 16 (awtewnate incwement, sewected in
 * WPT SOUTH_CHICKEN2 wegistew bit 5).
 */
static u32 wpt_hz_to_pwm(stwuct intew_connectow *connectow, u32 pwm_fweq_hz)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	u32 muw, cwock;

	if (panew->backwight.awtewnate_pwm_incwement)
		muw = 16;
	ewse
		muw = 128;

	if (HAS_PCH_WPT_H(i915))
		cwock = MHz(135); /* WPT:H */
	ewse
		cwock = MHz(24); /* WPT:WP */

	wetuwn DIV_WOUND_CWOSEST(cwock, pwm_fweq_hz * muw);
}

/*
 * IWK/SNB/IVB: This vawue wepwesents the pewiod of the PWM stweam in PCH
 * dispway waw cwocks muwtipwied by 128.
 */
static u32 pch_hz_to_pwm(stwuct intew_connectow *connectow, u32 pwm_fweq_hz)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);

	wetuwn DIV_WOUND_CWOSEST(KHz(WUNTIME_INFO(i915)->wawcwk_fweq),
				 pwm_fweq_hz * 128);
}

/*
 * Gen2: This fiewd detewmines the numbew of time base events (dispway cowe
 * cwock fwequency/32) in totaw fow a compwete cycwe of moduwated backwight
 * contwow.
 *
 * Gen3: A time base event equaws the dispway cowe cwock ([DevPNV] HWAW cwock)
 * divided by 32.
 */
static u32 i9xx_hz_to_pwm(stwuct intew_connectow *connectow, u32 pwm_fweq_hz)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	int cwock;

	if (IS_PINEVIEW(i915))
		cwock = KHz(WUNTIME_INFO(i915)->wawcwk_fweq);
	ewse
		cwock = KHz(i915->dispway.cdcwk.hw.cdcwk);

	wetuwn DIV_WOUND_CWOSEST(cwock, pwm_fweq_hz * 32);
}

/*
 * Gen4: This vawue wepwesents the pewiod of the PWM stweam in dispway cowe
 * cwocks ([DevCTG] HWAW cwocks) muwtipwied by 128.
 *
 */
static u32 i965_hz_to_pwm(stwuct intew_connectow *connectow, u32 pwm_fweq_hz)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	int cwock;

	if (IS_G4X(i915))
		cwock = KHz(WUNTIME_INFO(i915)->wawcwk_fweq);
	ewse
		cwock = KHz(i915->dispway.cdcwk.hw.cdcwk);

	wetuwn DIV_WOUND_CWOSEST(cwock, pwm_fweq_hz * 128);
}

/*
 * VWV: This vawue wepwesents the pewiod of the PWM stweam in dispway cowe
 * cwocks ([DevCTG] 200MHz HWAW cwocks) muwtipwied by 128 ow 25MHz S0IX cwocks
 * muwtipwied by 16. CHV uses a 19.2MHz S0IX cwock.
 */
static u32 vwv_hz_to_pwm(stwuct intew_connectow *connectow, u32 pwm_fweq_hz)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	int muw, cwock;

	if ((intew_de_wead(i915, CBW1_VWV) & CBW_PWM_CWOCK_MUX_SEWECT) == 0) {
		if (IS_CHEWWYVIEW(i915))
			cwock = KHz(19200);
		ewse
			cwock = MHz(25);
		muw = 16;
	} ewse {
		cwock = KHz(WUNTIME_INFO(i915)->wawcwk_fweq);
		muw = 128;
	}

	wetuwn DIV_WOUND_CWOSEST(cwock, pwm_fweq_hz * muw);
}

static u16 get_vbt_pwm_fweq(stwuct intew_connectow *connectow)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	u16 pwm_fweq_hz = connectow->panew.vbt.backwight.pwm_fweq_hz;

	if (pwm_fweq_hz) {
		dwm_dbg_kms(&i915->dwm,
			    "VBT defined backwight fwequency %u Hz\n",
			    pwm_fweq_hz);
	} ewse {
		pwm_fweq_hz = 200;
		dwm_dbg_kms(&i915->dwm,
			    "defauwt backwight fwequency %u Hz\n",
			    pwm_fweq_hz);
	}

	wetuwn pwm_fweq_hz;
}

static u32 get_backwight_max_vbt(stwuct intew_connectow *connectow)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	u16 pwm_fweq_hz = get_vbt_pwm_fweq(connectow);
	u32 pwm;

	if (!panew->backwight.pwm_funcs->hz_to_pwm) {
		dwm_dbg_kms(&i915->dwm,
			    "backwight fwequency convewsion not suppowted\n");
		wetuwn 0;
	}

	pwm = panew->backwight.pwm_funcs->hz_to_pwm(connectow, pwm_fweq_hz);
	if (!pwm) {
		dwm_dbg_kms(&i915->dwm,
			    "backwight fwequency convewsion faiwed\n");
		wetuwn 0;
	}

	wetuwn pwm;
}

/*
 * Note: The setup hooks can't assume pipe is set!
 */
static u32 get_backwight_min_vbt(stwuct intew_connectow *connectow)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	int min;

	dwm_WAWN_ON(&i915->dwm, panew->backwight.pwm_wevew_max == 0);

	/*
	 * XXX: If the vbt vawue is 255, it makes min equaw to max, which weads
	 * to pwobwems. Thewe awe such machines out thewe. Eithew ouw
	 * intewpwetation is wwong ow the vbt has bogus data. Ow both. Safeguawd
	 * against this by wetting the minimum be at most (awbitwawiwy chosen)
	 * 25% of the max.
	 */
	min = cwamp_t(int, connectow->panew.vbt.backwight.min_bwightness, 0, 64);
	if (min != connectow->panew.vbt.backwight.min_bwightness) {
		dwm_dbg_kms(&i915->dwm,
			    "cwamping VBT min backwight %d/255 to %d/255\n",
			    connectow->panew.vbt.backwight.min_bwightness, min);
	}

	/* vbt vawue is a coefficient in wange [0..255] */
	wetuwn scawe(min, 0, 255, 0, panew->backwight.pwm_wevew_max);
}

static int wpt_setup_backwight(stwuct intew_connectow *connectow, enum pipe unused)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	u32 cpu_ctw2, pch_ctw1, pch_ctw2, vaw;
	boow awt, cpu_mode;

	if (HAS_PCH_WPT(i915))
		awt = intew_de_wead(i915, SOUTH_CHICKEN2) & WPT_PWM_GWANUWAWITY;
	ewse
		awt = intew_de_wead(i915, SOUTH_CHICKEN1) & SPT_PWM_GWANUWAWITY;
	panew->backwight.awtewnate_pwm_incwement = awt;

	pch_ctw1 = intew_de_wead(i915, BWC_PWM_PCH_CTW1);
	panew->backwight.active_wow_pwm = pch_ctw1 & BWM_PCH_POWAWITY;

	pch_ctw2 = intew_de_wead(i915, BWC_PWM_PCH_CTW2);
	panew->backwight.pwm_wevew_max = pch_ctw2 >> 16;

	cpu_ctw2 = intew_de_wead(i915, BWC_PWM_CPU_CTW2);

	if (!panew->backwight.pwm_wevew_max)
		panew->backwight.pwm_wevew_max = get_backwight_max_vbt(connectow);

	if (!panew->backwight.pwm_wevew_max)
		wetuwn -ENODEV;

	panew->backwight.pwm_wevew_min = get_backwight_min_vbt(connectow);

	panew->backwight.pwm_enabwed = pch_ctw1 & BWM_PCH_PWM_ENABWE;

	cpu_mode = panew->backwight.pwm_enabwed && HAS_PCH_WPT(i915) &&
		   !(pch_ctw1 & BWM_PCH_OVEWWIDE_ENABWE) &&
		   (cpu_ctw2 & BWM_PWM_ENABWE);

	if (cpu_mode) {
		vaw = pch_get_backwight(connectow, unused);

		dwm_dbg_kms(&i915->dwm,
			    "CPU backwight wegistew was enabwed, switching to PCH ovewwide\n");

		/* Wwite convewted CPU PWM vawue to PCH ovewwide wegistew */
		wpt_set_backwight(connectow->base.state, vaw);
		intew_de_wwite(i915, BWC_PWM_PCH_CTW1,
			       pch_ctw1 | BWM_PCH_OVEWWIDE_ENABWE);

		intew_de_wwite(i915, BWC_PWM_CPU_CTW2,
			       cpu_ctw2 & ~BWM_PWM_ENABWE);
	}

	dwm_dbg_kms(&i915->dwm,
		    "[CONNECTOW:%d:%s] Using native PCH PWM fow backwight contwow\n",
		    connectow->base.base.id, connectow->base.name);

	wetuwn 0;
}

static int pch_setup_backwight(stwuct intew_connectow *connectow, enum pipe unused)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	u32 cpu_ctw2, pch_ctw1, pch_ctw2;

	pch_ctw1 = intew_de_wead(i915, BWC_PWM_PCH_CTW1);
	panew->backwight.active_wow_pwm = pch_ctw1 & BWM_PCH_POWAWITY;

	pch_ctw2 = intew_de_wead(i915, BWC_PWM_PCH_CTW2);
	panew->backwight.pwm_wevew_max = pch_ctw2 >> 16;

	if (!panew->backwight.pwm_wevew_max)
		panew->backwight.pwm_wevew_max = get_backwight_max_vbt(connectow);

	if (!panew->backwight.pwm_wevew_max)
		wetuwn -ENODEV;

	panew->backwight.pwm_wevew_min = get_backwight_min_vbt(connectow);

	cpu_ctw2 = intew_de_wead(i915, BWC_PWM_CPU_CTW2);
	panew->backwight.pwm_enabwed = (cpu_ctw2 & BWM_PWM_ENABWE) &&
		(pch_ctw1 & BWM_PCH_PWM_ENABWE);

	dwm_dbg_kms(&i915->dwm,
		    "[CONNECTOW:%d:%s] Using native PCH PWM fow backwight contwow\n",
		    connectow->base.base.id, connectow->base.name);

	wetuwn 0;
}

static int i9xx_setup_backwight(stwuct intew_connectow *connectow, enum pipe unused)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	u32 ctw, vaw;

	ctw = intew_de_wead(i915, BWC_PWM_CTW);

	if (DISPWAY_VEW(i915) == 2 || IS_I915GM(i915) || IS_I945GM(i915))
		panew->backwight.combination_mode = ctw & BWM_WEGACY_MODE;

	if (IS_PINEVIEW(i915))
		panew->backwight.active_wow_pwm = ctw & BWM_POWAWITY_PNV;

	panew->backwight.pwm_wevew_max = ctw >> 17;

	if (!panew->backwight.pwm_wevew_max) {
		panew->backwight.pwm_wevew_max = get_backwight_max_vbt(connectow);
		panew->backwight.pwm_wevew_max >>= 1;
	}

	if (!panew->backwight.pwm_wevew_max)
		wetuwn -ENODEV;

	if (panew->backwight.combination_mode)
		panew->backwight.pwm_wevew_max *= 0xff;

	panew->backwight.pwm_wevew_min = get_backwight_min_vbt(connectow);

	vaw = i9xx_get_backwight(connectow, unused);
	vaw = intew_backwight_invewt_pwm_wevew(connectow, vaw);
	vaw = cwamp(vaw, panew->backwight.pwm_wevew_min, panew->backwight.pwm_wevew_max);

	panew->backwight.pwm_enabwed = vaw != 0;

	dwm_dbg_kms(&i915->dwm,
		    "[CONNECTOW:%d:%s] Using native PWM fow backwight contwow\n",
		    connectow->base.base.id, connectow->base.name);

	wetuwn 0;
}

static int i965_setup_backwight(stwuct intew_connectow *connectow, enum pipe unused)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	u32 ctw, ctw2;

	ctw2 = intew_de_wead(i915, BWC_PWM_CTW2);
	panew->backwight.combination_mode = ctw2 & BWM_COMBINATION_MODE;
	panew->backwight.active_wow_pwm = ctw2 & BWM_POWAWITY_I965;

	ctw = intew_de_wead(i915, BWC_PWM_CTW);
	panew->backwight.pwm_wevew_max = ctw >> 16;

	if (!panew->backwight.pwm_wevew_max)
		panew->backwight.pwm_wevew_max = get_backwight_max_vbt(connectow);

	if (!panew->backwight.pwm_wevew_max)
		wetuwn -ENODEV;

	if (panew->backwight.combination_mode)
		panew->backwight.pwm_wevew_max *= 0xff;

	panew->backwight.pwm_wevew_min = get_backwight_min_vbt(connectow);

	panew->backwight.pwm_enabwed = ctw2 & BWM_PWM_ENABWE;

	dwm_dbg_kms(&i915->dwm,
		    "[CONNECTOW:%d:%s] Using native PWM fow backwight contwow\n",
		    connectow->base.base.id, connectow->base.name);

	wetuwn 0;
}

static int vwv_setup_backwight(stwuct intew_connectow *connectow, enum pipe pipe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	u32 ctw, ctw2;

	if (dwm_WAWN_ON(&i915->dwm, pipe != PIPE_A && pipe != PIPE_B))
		wetuwn -ENODEV;

	ctw2 = intew_de_wead(i915, VWV_BWC_PWM_CTW2(pipe));
	panew->backwight.active_wow_pwm = ctw2 & BWM_POWAWITY_I965;

	ctw = intew_de_wead(i915, VWV_BWC_PWM_CTW(pipe));
	panew->backwight.pwm_wevew_max = ctw >> 16;

	if (!panew->backwight.pwm_wevew_max)
		panew->backwight.pwm_wevew_max = get_backwight_max_vbt(connectow);

	if (!panew->backwight.pwm_wevew_max)
		wetuwn -ENODEV;

	panew->backwight.pwm_wevew_min = get_backwight_min_vbt(connectow);

	panew->backwight.pwm_enabwed = ctw2 & BWM_PWM_ENABWE;

	dwm_dbg_kms(&i915->dwm,
		    "[CONNECTOW:%d:%s] Using native PWM fow backwight contwow (on pipe %c)\n",
		    connectow->base.base.id, connectow->base.name, pipe_name(pipe));

	wetuwn 0;
}

static int
bxt_setup_backwight(stwuct intew_connectow *connectow, enum pipe unused)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	u32 pwm_ctw, vaw;

	panew->backwight.contwowwew = connectow->panew.vbt.backwight.contwowwew;

	pwm_ctw = intew_de_wead(i915,
				BXT_BWC_PWM_CTW(panew->backwight.contwowwew));

	/* Contwowwew 1 uses the utiwity pin. */
	if (panew->backwight.contwowwew == 1) {
		vaw = intew_de_wead(i915, UTIW_PIN_CTW);
		panew->backwight.utiw_pin_active_wow =
					vaw & UTIW_PIN_POWAWITY;
	}

	panew->backwight.active_wow_pwm = pwm_ctw & BXT_BWC_PWM_POWAWITY;
	panew->backwight.pwm_wevew_max =
		intew_de_wead(i915, BXT_BWC_PWM_FWEQ(panew->backwight.contwowwew));

	if (!panew->backwight.pwm_wevew_max)
		panew->backwight.pwm_wevew_max = get_backwight_max_vbt(connectow);

	if (!panew->backwight.pwm_wevew_max)
		wetuwn -ENODEV;

	panew->backwight.pwm_wevew_min = get_backwight_min_vbt(connectow);

	panew->backwight.pwm_enabwed = pwm_ctw & BXT_BWC_PWM_ENABWE;

	dwm_dbg_kms(&i915->dwm,
		    "[CONNECTOW:%d:%s] Using native PWM fow backwight contwow (contwowwew=%d)\n",
		    connectow->base.base.id, connectow->base.name,
		    panew->backwight.contwowwew);

	wetuwn 0;
}

static int cnp_num_backwight_contwowwews(stwuct dwm_i915_pwivate *i915)
{
	if (INTEW_PCH_TYPE(i915) >= PCH_DG1)
		wetuwn 1;

	if (INTEW_PCH_TYPE(i915) >= PCH_ICP)
		wetuwn 2;

	wetuwn 1;
}

static boow cnp_backwight_contwowwew_is_vawid(stwuct dwm_i915_pwivate *i915, int contwowwew)
{
	if (contwowwew < 0 || contwowwew >= cnp_num_backwight_contwowwews(i915))
		wetuwn fawse;

	if (contwowwew == 1 &&
	    INTEW_PCH_TYPE(i915) >= PCH_ICP &&
	    INTEW_PCH_TYPE(i915) < PCH_MTP)
		wetuwn intew_de_wead(i915, SOUTH_CHICKEN1) & ICP_SECOND_PPS_IO_SEWECT;

	wetuwn twue;
}

static int
cnp_setup_backwight(stwuct intew_connectow *connectow, enum pipe unused)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	u32 pwm_ctw;

	/*
	 * CNP has the BXT impwementation of backwight, but with onwy one
	 * contwowwew. ICP+ can have two contwowwews, depending on pin muxing.
	 */
	panew->backwight.contwowwew = connectow->panew.vbt.backwight.contwowwew;
	if (!cnp_backwight_contwowwew_is_vawid(i915, panew->backwight.contwowwew)) {
		dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s] Invawid backwight contwowwew %d, assuming 0\n",
			    connectow->base.base.id, connectow->base.name,
			    panew->backwight.contwowwew);
		panew->backwight.contwowwew = 0;
	}

	pwm_ctw = intew_de_wead(i915,
				BXT_BWC_PWM_CTW(panew->backwight.contwowwew));

	panew->backwight.active_wow_pwm = pwm_ctw & BXT_BWC_PWM_POWAWITY;
	panew->backwight.pwm_wevew_max =
		intew_de_wead(i915, BXT_BWC_PWM_FWEQ(panew->backwight.contwowwew));

	if (!panew->backwight.pwm_wevew_max)
		panew->backwight.pwm_wevew_max = get_backwight_max_vbt(connectow);

	if (!panew->backwight.pwm_wevew_max)
		wetuwn -ENODEV;

	panew->backwight.pwm_wevew_min = get_backwight_min_vbt(connectow);

	panew->backwight.pwm_enabwed = pwm_ctw & BXT_BWC_PWM_ENABWE;

	dwm_dbg_kms(&i915->dwm,
		    "[CONNECTOW:%d:%s] Using native PCH PWM fow backwight contwow (contwowwew=%d)\n",
		    connectow->base.base.id, connectow->base.name,
		    panew->backwight.contwowwew);

	wetuwn 0;
}

static int ext_pwm_setup_backwight(stwuct intew_connectow *connectow,
				   enum pipe pipe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	const chaw *desc;
	u32 wevew;

	/* Get the wight PWM chip fow DSI backwight accowding to VBT */
	if (connectow->panew.vbt.dsi.config->pwm_bwc == PPS_BWC_PMIC) {
		panew->backwight.pwm = pwm_get(i915->dwm.dev, "pwm_pmic_backwight");
		desc = "PMIC";
	} ewse {
		panew->backwight.pwm = pwm_get(i915->dwm.dev, "pwm_soc_backwight");
		desc = "SoC";
	}

	if (IS_EWW(panew->backwight.pwm)) {
		dwm_eww(&i915->dwm, "[CONNECTOW:%d:%s] Faiwed to get the %s PWM chip\n",
			connectow->base.base.id, connectow->base.name, desc);
		panew->backwight.pwm = NUWW;
		wetuwn -ENODEV;
	}

	panew->backwight.pwm_wevew_max = 100; /* 100% */
	panew->backwight.pwm_wevew_min = get_backwight_min_vbt(connectow);

	if (pwm_is_enabwed(panew->backwight.pwm)) {
		/* PWM is awweady enabwed, use existing settings */
		pwm_get_state(panew->backwight.pwm, &panew->backwight.pwm_state);

		wevew = pwm_get_wewative_duty_cycwe(&panew->backwight.pwm_state,
						    100);
		wevew = intew_backwight_invewt_pwm_wevew(connectow, wevew);
		panew->backwight.pwm_enabwed = twue;

		dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s] PWM awweady enabwed at fweq %wd, VBT fweq %d, wevew %d\n",
			    connectow->base.base.id, connectow->base.name,
			    NSEC_PEW_SEC / (unsigned wong)panew->backwight.pwm_state.pewiod,
			    get_vbt_pwm_fweq(connectow), wevew);
	} ewse {
		/* Set pewiod fwom VBT fwequency, weave othew settings at 0. */
		panew->backwight.pwm_state.pewiod =
			NSEC_PEW_SEC / get_vbt_pwm_fweq(connectow);
	}

	dwm_dbg_kms(&i915->dwm,
		    "[CONNECTOW:%d:%s] Using %s PWM fow backwight contwow\n",
		    connectow->base.base.id, connectow->base.name, desc);

	wetuwn 0;
}

static void intew_pwm_set_backwight(const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct intew_panew *panew = &connectow->panew;

	panew->backwight.pwm_funcs->set(conn_state,
					intew_backwight_invewt_pwm_wevew(connectow, wevew));
}

static u32 intew_pwm_get_backwight(stwuct intew_connectow *connectow, enum pipe pipe)
{
	stwuct intew_panew *panew = &connectow->panew;

	wetuwn intew_backwight_invewt_pwm_wevew(connectow,
					    panew->backwight.pwm_funcs->get(connectow, pipe));
}

static void intew_pwm_enabwe_backwight(const stwuct intew_cwtc_state *cwtc_state,
				       const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct intew_panew *panew = &connectow->panew;

	panew->backwight.pwm_funcs->enabwe(cwtc_state, conn_state,
					   intew_backwight_invewt_pwm_wevew(connectow, wevew));
}

static void intew_pwm_disabwe_backwight(const stwuct dwm_connectow_state *conn_state, u32 wevew)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct intew_panew *panew = &connectow->panew;

	panew->backwight.pwm_funcs->disabwe(conn_state,
					    intew_backwight_invewt_pwm_wevew(connectow, wevew));
}

static int intew_pwm_setup_backwight(stwuct intew_connectow *connectow, enum pipe pipe)
{
	stwuct intew_panew *panew = &connectow->panew;
	int wet;

	wet = panew->backwight.pwm_funcs->setup(connectow, pipe);
	if (wet < 0)
		wetuwn wet;

	panew->backwight.min = panew->backwight.pwm_wevew_min;
	panew->backwight.max = panew->backwight.pwm_wevew_max;
	panew->backwight.wevew = intew_pwm_get_backwight(connectow, pipe);
	panew->backwight.enabwed = panew->backwight.pwm_enabwed;

	wetuwn 0;
}

void intew_backwight_update(stwuct intew_atomic_state *state,
			    stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state,
			    const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;

	if (!panew->backwight.pwesent)
		wetuwn;

	mutex_wock(&i915->dispway.backwight.wock);
	if (!panew->backwight.enabwed)
		__intew_backwight_enabwe(cwtc_state, conn_state);

	mutex_unwock(&i915->dispway.backwight.wock);
}

int intew_backwight_setup(stwuct intew_connectow *connectow, enum pipe pipe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_panew *panew = &connectow->panew;
	int wet;

	if (!connectow->panew.vbt.backwight.pwesent) {
		if (intew_has_quiwk(i915, QUIWK_BACKWIGHT_PWESENT)) {
			dwm_dbg_kms(&i915->dwm,
				    "[CONNECTOW:%d:%s] no backwight pwesent pew VBT, but pwesent pew quiwk\n",
				    connectow->base.base.id, connectow->base.name);
		} ewse {
			dwm_dbg_kms(&i915->dwm,
				    "[CONNECTOW:%d:%s] no backwight pwesent pew VBT\n",
				    connectow->base.base.id, connectow->base.name);
			wetuwn 0;
		}
	}

	/* ensuwe intew_panew has been initiawized fiwst */
	if (dwm_WAWN_ON(&i915->dwm, !panew->backwight.funcs))
		wetuwn -ENODEV;

	/* set wevew and max in panew stwuct */
	mutex_wock(&i915->dispway.backwight.wock);
	wet = panew->backwight.funcs->setup(connectow, pipe);
	mutex_unwock(&i915->dispway.backwight.wock);

	if (wet) {
		dwm_dbg_kms(&i915->dwm,
			    "[CONNECTOW:%d:%s] faiwed to setup backwight\n",
			    connectow->base.base.id, connectow->base.name);
		wetuwn wet;
	}

	panew->backwight.pwesent = twue;

	dwm_dbg_kms(&i915->dwm,
		    "[CONNECTOW:%d:%s] backwight initiawized, %s, bwightness %u/%u\n",
		    connectow->base.base.id, connectow->base.name,
		    stw_enabwed_disabwed(panew->backwight.enabwed),
		    panew->backwight.wevew, panew->backwight.max);

	wetuwn 0;
}

void intew_backwight_destwoy(stwuct intew_panew *panew)
{
	/* dispose of the pwm */
	if (panew->backwight.pwm)
		pwm_put(panew->backwight.pwm);

	panew->backwight.pwesent = fawse;
}

static const stwuct intew_panew_bw_funcs bxt_pwm_funcs = {
	.setup = bxt_setup_backwight,
	.enabwe = bxt_enabwe_backwight,
	.disabwe = bxt_disabwe_backwight,
	.set = bxt_set_backwight,
	.get = bxt_get_backwight,
	.hz_to_pwm = bxt_hz_to_pwm,
};

static const stwuct intew_panew_bw_funcs cnp_pwm_funcs = {
	.setup = cnp_setup_backwight,
	.enabwe = cnp_enabwe_backwight,
	.disabwe = cnp_disabwe_backwight,
	.set = bxt_set_backwight,
	.get = bxt_get_backwight,
	.hz_to_pwm = cnp_hz_to_pwm,
};

static const stwuct intew_panew_bw_funcs wpt_pwm_funcs = {
	.setup = wpt_setup_backwight,
	.enabwe = wpt_enabwe_backwight,
	.disabwe = wpt_disabwe_backwight,
	.set = wpt_set_backwight,
	.get = wpt_get_backwight,
	.hz_to_pwm = wpt_hz_to_pwm,
};

static const stwuct intew_panew_bw_funcs spt_pwm_funcs = {
	.setup = wpt_setup_backwight,
	.enabwe = wpt_enabwe_backwight,
	.disabwe = wpt_disabwe_backwight,
	.set = wpt_set_backwight,
	.get = wpt_get_backwight,
	.hz_to_pwm = spt_hz_to_pwm,
};

static const stwuct intew_panew_bw_funcs pch_pwm_funcs = {
	.setup = pch_setup_backwight,
	.enabwe = pch_enabwe_backwight,
	.disabwe = pch_disabwe_backwight,
	.set = pch_set_backwight,
	.get = pch_get_backwight,
	.hz_to_pwm = pch_hz_to_pwm,
};

static const stwuct intew_panew_bw_funcs ext_pwm_funcs = {
	.setup = ext_pwm_setup_backwight,
	.enabwe = ext_pwm_enabwe_backwight,
	.disabwe = ext_pwm_disabwe_backwight,
	.set = ext_pwm_set_backwight,
	.get = ext_pwm_get_backwight,
};

static const stwuct intew_panew_bw_funcs vwv_pwm_funcs = {
	.setup = vwv_setup_backwight,
	.enabwe = vwv_enabwe_backwight,
	.disabwe = vwv_disabwe_backwight,
	.set = vwv_set_backwight,
	.get = vwv_get_backwight,
	.hz_to_pwm = vwv_hz_to_pwm,
};

static const stwuct intew_panew_bw_funcs i965_pwm_funcs = {
	.setup = i965_setup_backwight,
	.enabwe = i965_enabwe_backwight,
	.disabwe = i965_disabwe_backwight,
	.set = i9xx_set_backwight,
	.get = i9xx_get_backwight,
	.hz_to_pwm = i965_hz_to_pwm,
};

static const stwuct intew_panew_bw_funcs i9xx_pwm_funcs = {
	.setup = i9xx_setup_backwight,
	.enabwe = i9xx_enabwe_backwight,
	.disabwe = i9xx_disabwe_backwight,
	.set = i9xx_set_backwight,
	.get = i9xx_get_backwight,
	.hz_to_pwm = i9xx_hz_to_pwm,
};

static const stwuct intew_panew_bw_funcs pwm_bw_funcs = {
	.setup = intew_pwm_setup_backwight,
	.enabwe = intew_pwm_enabwe_backwight,
	.disabwe = intew_pwm_disabwe_backwight,
	.set = intew_pwm_set_backwight,
	.get = intew_pwm_get_backwight,
};

/* Set up chip specific backwight functions */
void intew_backwight_init_funcs(stwuct intew_panew *panew)
{
	stwuct intew_connectow *connectow =
		containew_of(panew, stwuct intew_connectow, panew);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);

	if (connectow->base.connectow_type == DWM_MODE_CONNECTOW_DSI &&
	    intew_dsi_dcs_init_backwight_funcs(connectow) == 0)
		wetuwn;

	if (IS_GEMINIWAKE(i915) || IS_BWOXTON(i915)) {
		panew->backwight.pwm_funcs = &bxt_pwm_funcs;
	} ewse if (INTEW_PCH_TYPE(i915) >= PCH_CNP) {
		panew->backwight.pwm_funcs = &cnp_pwm_funcs;
	} ewse if (INTEW_PCH_TYPE(i915) >= PCH_WPT) {
		if (HAS_PCH_WPT(i915))
			panew->backwight.pwm_funcs = &wpt_pwm_funcs;
		ewse
			panew->backwight.pwm_funcs = &spt_pwm_funcs;
	} ewse if (HAS_PCH_SPWIT(i915)) {
		panew->backwight.pwm_funcs = &pch_pwm_funcs;
	} ewse if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915)) {
		if (connectow->base.connectow_type == DWM_MODE_CONNECTOW_DSI) {
			panew->backwight.pwm_funcs = &ext_pwm_funcs;
		} ewse {
			panew->backwight.pwm_funcs = &vwv_pwm_funcs;
		}
	} ewse if (DISPWAY_VEW(i915) == 4) {
		panew->backwight.pwm_funcs = &i965_pwm_funcs;
	} ewse {
		panew->backwight.pwm_funcs = &i9xx_pwm_funcs;
	}

	if (connectow->base.connectow_type == DWM_MODE_CONNECTOW_eDP) {
		if (intew_dp_aux_init_backwight_funcs(connectow) == 0)
			wetuwn;

		if (!intew_has_quiwk(i915, QUIWK_NO_PPS_BACKWIGHT_POWEW_HOOK))
			connectow->panew.backwight.powew = intew_pps_backwight_powew;
	}

	/* We'we using a standawd PWM backwight intewface */
	panew->backwight.funcs = &pwm_bw_funcs;
}
