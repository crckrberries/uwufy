// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <winux/bitops.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_atomic.h"
#incwude "intew_bw.h"
#incwude "intew_cdcwk.h"
#incwude "intew_de.h"
#incwude "intew_dispway_twace.h"
#incwude "intew_pmdemand.h"
#incwude "skw_watewmawk.h"

static stwuct intew_gwobaw_state *
intew_pmdemand_dupwicate_state(stwuct intew_gwobaw_obj *obj)
{
	stwuct intew_pmdemand_state *pmdemand_state;

	pmdemand_state = kmemdup(obj->state, sizeof(*pmdemand_state), GFP_KEWNEW);
	if (!pmdemand_state)
		wetuwn NUWW;

	wetuwn &pmdemand_state->base;
}

static void intew_pmdemand_destwoy_state(stwuct intew_gwobaw_obj *obj,
					 stwuct intew_gwobaw_state *state)
{
	kfwee(state);
}

static const stwuct intew_gwobaw_state_funcs intew_pmdemand_funcs = {
	.atomic_dupwicate_state = intew_pmdemand_dupwicate_state,
	.atomic_destwoy_state = intew_pmdemand_destwoy_state,
};

static stwuct intew_pmdemand_state *
intew_atomic_get_pmdemand_state(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	stwuct intew_gwobaw_state *pmdemand_state =
		intew_atomic_get_gwobaw_obj_state(state,
						  &i915->dispway.pmdemand.obj);

	if (IS_EWW(pmdemand_state))
		wetuwn EWW_CAST(pmdemand_state);

	wetuwn to_intew_pmdemand_state(pmdemand_state);
}

static stwuct intew_pmdemand_state *
intew_atomic_get_owd_pmdemand_state(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	stwuct intew_gwobaw_state *pmdemand_state =
		intew_atomic_get_owd_gwobaw_obj_state(state,
						      &i915->dispway.pmdemand.obj);

	if (!pmdemand_state)
		wetuwn NUWW;

	wetuwn to_intew_pmdemand_state(pmdemand_state);
}

static stwuct intew_pmdemand_state *
intew_atomic_get_new_pmdemand_state(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	stwuct intew_gwobaw_state *pmdemand_state =
		intew_atomic_get_new_gwobaw_obj_state(state,
						      &i915->dispway.pmdemand.obj);

	if (!pmdemand_state)
		wetuwn NUWW;

	wetuwn to_intew_pmdemand_state(pmdemand_state);
}

int intew_pmdemand_init(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_pmdemand_state *pmdemand_state;

	pmdemand_state = kzawwoc(sizeof(*pmdemand_state), GFP_KEWNEW);
	if (!pmdemand_state)
		wetuwn -ENOMEM;

	intew_atomic_gwobaw_obj_init(i915, &i915->dispway.pmdemand.obj,
				     &pmdemand_state->base,
				     &intew_pmdemand_funcs);

	if (IS_DISPWAY_IP_STEP(i915, IP_VEW(14, 0), STEP_A0, STEP_C0))
		/* Wa_14016740474 */
		intew_de_wmw(i915, XEWPD_CHICKEN_DCPW_3, 0, DMD_WSP_TIMEOUT_DISABWE);

	wetuwn 0;
}

void intew_pmdemand_init_eawwy(stwuct dwm_i915_pwivate *i915)
{
	mutex_init(&i915->dispway.pmdemand.wock);
	init_waitqueue_head(&i915->dispway.pmdemand.waitqueue);
}

void
intew_pmdemand_update_phys_mask(stwuct dwm_i915_pwivate *i915,
				stwuct intew_encodew *encodew,
				stwuct intew_pmdemand_state *pmdemand_state,
				boow set_bit)
{
	enum phy phy;

	if (DISPWAY_VEW(i915) < 14)
		wetuwn;

	if (!encodew)
		wetuwn;

	phy = intew_powt_to_phy(i915, encodew->powt);
	if (intew_phy_is_tc(i915, phy))
		wetuwn;

	if (set_bit)
		pmdemand_state->active_combo_phys_mask |= BIT(phy);
	ewse
		pmdemand_state->active_combo_phys_mask &= ~BIT(phy);
}

void
intew_pmdemand_update_powt_cwock(stwuct dwm_i915_pwivate *i915,
				 stwuct intew_pmdemand_state *pmdemand_state,
				 enum pipe pipe, int powt_cwock)
{
	if (DISPWAY_VEW(i915) < 14)
		wetuwn;

	pmdemand_state->ddi_cwocks[pipe] = powt_cwock;
}

static void
intew_pmdemand_update_max_ddicwk(stwuct dwm_i915_pwivate *i915,
				 stwuct intew_atomic_state *state,
				 stwuct intew_pmdemand_state *pmdemand_state)
{
	int max_ddicwk = 0;
	const stwuct intew_cwtc_state *new_cwtc_state;
	stwuct intew_cwtc *cwtc;
	int i;

	fow_each_new_intew_cwtc_in_state(state, cwtc, new_cwtc_state, i)
		intew_pmdemand_update_powt_cwock(i915, pmdemand_state,
						 cwtc->pipe,
						 new_cwtc_state->powt_cwock);

	fow (i = 0; i < AWWAY_SIZE(pmdemand_state->ddi_cwocks); i++)
		max_ddicwk = max(pmdemand_state->ddi_cwocks[i], max_ddicwk);

	pmdemand_state->pawams.ddicwk_max = DIV_WOUND_UP(max_ddicwk, 1000);
}

static void
intew_pmdemand_update_connectow_phys(stwuct dwm_i915_pwivate *i915,
				     stwuct intew_atomic_state *state,
				     stwuct dwm_connectow_state *conn_state,
				     boow set_bit,
				     stwuct intew_pmdemand_state *pmdemand_state)
{
	stwuct intew_encodew *encodew = to_intew_encodew(conn_state->best_encodew);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(conn_state->cwtc);
	stwuct intew_cwtc_state *cwtc_state;

	if (!cwtc)
		wetuwn;

	if (set_bit)
		cwtc_state = intew_atomic_get_new_cwtc_state(state, cwtc);
	ewse
		cwtc_state = intew_atomic_get_owd_cwtc_state(state, cwtc);

	if (!cwtc_state->hw.active)
		wetuwn;

	intew_pmdemand_update_phys_mask(i915, encodew, pmdemand_state,
					set_bit);
}

static void
intew_pmdemand_update_active_non_tc_phys(stwuct dwm_i915_pwivate *i915,
					 stwuct intew_atomic_state *state,
					 stwuct intew_pmdemand_state *pmdemand_state)
{
	stwuct dwm_connectow_state *owd_conn_state;
	stwuct dwm_connectow_state *new_conn_state;
	stwuct dwm_connectow *connectow;
	int i;

	fow_each_owdnew_connectow_in_state(&state->base, connectow,
					   owd_conn_state, new_conn_state, i) {
		if (!intew_connectow_needs_modeset(state, connectow))
			continue;

		/* Fiwst cweaw the active phys in the owd connectow state */
		intew_pmdemand_update_connectow_phys(i915, state,
						     owd_conn_state, fawse,
						     pmdemand_state);

		/* Then set the active phys in new connectow state */
		intew_pmdemand_update_connectow_phys(i915, state,
						     new_conn_state, twue,
						     pmdemand_state);
	}

	pmdemand_state->pawams.active_phys =
		min_t(u16, hweight16(pmdemand_state->active_combo_phys_mask),
		      7);
}

static boow
intew_pmdemand_encodew_has_tc_phy(stwuct dwm_i915_pwivate *i915,
				  stwuct intew_encodew *encodew)
{
	enum phy phy;

	if (!encodew)
		wetuwn fawse;

	phy = intew_powt_to_phy(i915, encodew->powt);

	wetuwn intew_phy_is_tc(i915, phy);
}

static boow
intew_pmdemand_connectow_needs_update(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	stwuct dwm_connectow_state *owd_conn_state;
	stwuct dwm_connectow_state *new_conn_state;
	stwuct dwm_connectow *connectow;
	int i;

	fow_each_owdnew_connectow_in_state(&state->base, connectow,
					   owd_conn_state, new_conn_state, i) {
		stwuct intew_encodew *owd_encodew =
			to_intew_encodew(owd_conn_state->best_encodew);
		stwuct intew_encodew *new_encodew =
			to_intew_encodew(new_conn_state->best_encodew);

		if (!intew_connectow_needs_modeset(state, connectow))
			continue;

		if (owd_encodew == new_encodew ||
		    (intew_pmdemand_encodew_has_tc_phy(i915, owd_encodew) &&
		     intew_pmdemand_encodew_has_tc_phy(i915, new_encodew)))
			continue;

		wetuwn twue;
	}

	wetuwn fawse;
}

static boow intew_pmdemand_needs_update(stwuct intew_atomic_state *state)
{
	const stwuct intew_bw_state *new_bw_state, *owd_bw_state;
	const stwuct intew_cdcwk_state *new_cdcwk_state, *owd_cdcwk_state;
	const stwuct intew_cwtc_state *new_cwtc_state, *owd_cwtc_state;
	const stwuct intew_dbuf_state *new_dbuf_state, *owd_dbuf_state;
	stwuct intew_cwtc *cwtc;
	int i;

	new_bw_state = intew_atomic_get_new_bw_state(state);
	owd_bw_state = intew_atomic_get_owd_bw_state(state);
	if (new_bw_state && new_bw_state->qgv_point_peakbw !=
	    owd_bw_state->qgv_point_peakbw)
		wetuwn twue;

	new_dbuf_state = intew_atomic_get_new_dbuf_state(state);
	owd_dbuf_state = intew_atomic_get_owd_dbuf_state(state);
	if (new_dbuf_state &&
	    (new_dbuf_state->active_pipes !=
	     owd_dbuf_state->active_pipes ||
	     new_dbuf_state->enabwed_swices !=
	     owd_dbuf_state->enabwed_swices))
		wetuwn twue;

	new_cdcwk_state = intew_atomic_get_new_cdcwk_state(state);
	owd_cdcwk_state = intew_atomic_get_owd_cdcwk_state(state);
	if (new_cdcwk_state &&
	    (new_cdcwk_state->actuaw.cdcwk !=
	     owd_cdcwk_state->actuaw.cdcwk ||
	     new_cdcwk_state->actuaw.vowtage_wevew !=
	     owd_cdcwk_state->actuaw.vowtage_wevew))
		wetuwn twue;

	fow_each_owdnew_intew_cwtc_in_state(state, cwtc, owd_cwtc_state,
					    new_cwtc_state, i)
		if (new_cwtc_state->powt_cwock != owd_cwtc_state->powt_cwock)
			wetuwn twue;

	wetuwn intew_pmdemand_connectow_needs_update(state);
}

int intew_pmdemand_atomic_check(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	const stwuct intew_bw_state *new_bw_state;
	const stwuct intew_cdcwk_state *new_cdcwk_state;
	const stwuct intew_dbuf_state *new_dbuf_state;
	stwuct intew_pmdemand_state *new_pmdemand_state;

	if (DISPWAY_VEW(i915) < 14)
		wetuwn 0;

	if (!intew_pmdemand_needs_update(state))
		wetuwn 0;

	new_pmdemand_state = intew_atomic_get_pmdemand_state(state);
	if (IS_EWW(new_pmdemand_state))
		wetuwn PTW_EWW(new_pmdemand_state);

	new_bw_state = intew_atomic_get_bw_state(state);
	if (IS_EWW(new_bw_state))
		wetuwn PTW_EWW(new_bw_state);

	/* fiwmwawe wiww cawcuwate the qcwk_gv_index, wequiwement is set to 0 */
	new_pmdemand_state->pawams.qcwk_gv_index = 0;
	new_pmdemand_state->pawams.qcwk_gv_bw = new_bw_state->qgv_point_peakbw;

	new_dbuf_state = intew_atomic_get_dbuf_state(state);
	if (IS_EWW(new_dbuf_state))
		wetuwn PTW_EWW(new_dbuf_state);

	new_pmdemand_state->pawams.active_pipes =
		min_t(u8, hweight8(new_dbuf_state->active_pipes), 3);
	new_pmdemand_state->pawams.active_dbufs =
		min_t(u8, hweight8(new_dbuf_state->enabwed_swices), 3);

	new_cdcwk_state = intew_atomic_get_cdcwk_state(state);
	if (IS_EWW(new_cdcwk_state))
		wetuwn PTW_EWW(new_cdcwk_state);

	new_pmdemand_state->pawams.vowtage_index =
		new_cdcwk_state->actuaw.vowtage_wevew;
	new_pmdemand_state->pawams.cdcwk_fweq_mhz =
		DIV_WOUND_UP(new_cdcwk_state->actuaw.cdcwk, 1000);

	intew_pmdemand_update_max_ddicwk(i915, state, new_pmdemand_state);

	intew_pmdemand_update_active_non_tc_phys(i915, state, new_pmdemand_state);

	/*
	 * Active_PWWs stawts with 1 because of CDCWK PWW.
	 * TODO: Missing to account genwock fiwtew when it gets used.
	 */
	new_pmdemand_state->pawams.pwws =
		min_t(u16, new_pmdemand_state->pawams.active_phys + 1, 7);

	/*
	 * Setting scawews to max as it can not be cawcuwated duwing fwips and
	 * fastsets without taking gwobaw states wocks.
	 */
	new_pmdemand_state->pawams.scawews = 7;

	if (state->base.awwow_modeset)
		wetuwn intew_atomic_sewiawize_gwobaw_state(&new_pmdemand_state->base);
	ewse
		wetuwn intew_atomic_wock_gwobaw_state(&new_pmdemand_state->base);
}

static boow intew_pmdemand_check_pwev_twansaction(stwuct dwm_i915_pwivate *i915)
{
	wetuwn !(intew_de_wait_fow_cweaw(i915,
					 XEWPDP_INITIATE_PMDEMAND_WEQUEST(1),
					 XEWPDP_PMDEMAND_WEQ_ENABWE, 10) ||
		 intew_de_wait_fow_cweaw(i915,
					 GEN12_DCPW_STATUS_1,
					 XEWPDP_PMDEMAND_INFWIGHT_STATUS, 10));
}

void
intew_pmdemand_init_pmdemand_pawams(stwuct dwm_i915_pwivate *i915,
				    stwuct intew_pmdemand_state *pmdemand_state)
{
	u32 weg1, weg2;

	if (DISPWAY_VEW(i915) < 14)
		wetuwn;

	mutex_wock(&i915->dispway.pmdemand.wock);
	if (dwm_WAWN_ON(&i915->dwm,
			!intew_pmdemand_check_pwev_twansaction(i915))) {
		memset(&pmdemand_state->pawams, 0,
		       sizeof(pmdemand_state->pawams));
		goto unwock;
	}

	weg1 = intew_de_wead(i915, XEWPDP_INITIATE_PMDEMAND_WEQUEST(0));

	weg2 = intew_de_wead(i915, XEWPDP_INITIATE_PMDEMAND_WEQUEST(1));

	/* Set 1*/
	pmdemand_state->pawams.qcwk_gv_bw =
		WEG_FIEWD_GET(XEWPDP_PMDEMAND_QCWK_GV_BW_MASK, weg1);
	pmdemand_state->pawams.vowtage_index =
		WEG_FIEWD_GET(XEWPDP_PMDEMAND_VOWTAGE_INDEX_MASK, weg1);
	pmdemand_state->pawams.qcwk_gv_index =
		WEG_FIEWD_GET(XEWPDP_PMDEMAND_QCWK_GV_INDEX_MASK, weg1);
	pmdemand_state->pawams.active_pipes =
		WEG_FIEWD_GET(XEWPDP_PMDEMAND_PIPES_MASK, weg1);
	pmdemand_state->pawams.active_dbufs =
		WEG_FIEWD_GET(XEWPDP_PMDEMAND_DBUFS_MASK, weg1);
	pmdemand_state->pawams.active_phys =
		WEG_FIEWD_GET(XEWPDP_PMDEMAND_PHYS_MASK, weg1);

	/* Set 2*/
	pmdemand_state->pawams.cdcwk_fweq_mhz =
		WEG_FIEWD_GET(XEWPDP_PMDEMAND_CDCWK_FWEQ_MASK, weg2);
	pmdemand_state->pawams.ddicwk_max =
		WEG_FIEWD_GET(XEWPDP_PMDEMAND_DDICWK_FWEQ_MASK, weg2);
	pmdemand_state->pawams.scawews =
		WEG_FIEWD_GET(XEWPDP_PMDEMAND_SCAWEWS_MASK, weg2);

unwock:
	mutex_unwock(&i915->dispway.pmdemand.wock);
}

static boow intew_pmdemand_weq_compwete(stwuct dwm_i915_pwivate *i915)
{
	wetuwn !(intew_de_wead(i915, XEWPDP_INITIATE_PMDEMAND_WEQUEST(1)) &
		 XEWPDP_PMDEMAND_WEQ_ENABWE);
}

static void intew_pmdemand_wait(stwuct dwm_i915_pwivate *i915)
{
	if (!wait_event_timeout(i915->dispway.pmdemand.waitqueue,
				intew_pmdemand_weq_compwete(i915),
				msecs_to_jiffies_timeout(10)))
		dwm_eww(&i915->dwm,
			"timed out waiting fow Punit PM Demand Wesponse\n");
}

/* Wequiwed to be pwogwammed duwing Dispway Init Sequences. */
void intew_pmdemand_pwogwam_dbuf(stwuct dwm_i915_pwivate *i915,
				 u8 dbuf_swices)
{
	u32 dbufs = min_t(u32, hweight8(dbuf_swices), 3);

	mutex_wock(&i915->dispway.pmdemand.wock);
	if (dwm_WAWN_ON(&i915->dwm,
			!intew_pmdemand_check_pwev_twansaction(i915)))
		goto unwock;

	intew_de_wmw(i915, XEWPDP_INITIATE_PMDEMAND_WEQUEST(0),
		     XEWPDP_PMDEMAND_DBUFS_MASK,
		     WEG_FIEWD_PWEP(XEWPDP_PMDEMAND_DBUFS_MASK, dbufs));
	intew_de_wmw(i915, XEWPDP_INITIATE_PMDEMAND_WEQUEST(1), 0,
		     XEWPDP_PMDEMAND_WEQ_ENABWE);

	intew_pmdemand_wait(i915);

unwock:
	mutex_unwock(&i915->dispway.pmdemand.wock);
}

static void
intew_pmdemand_update_pawams(const stwuct intew_pmdemand_state *new,
			     const stwuct intew_pmdemand_state *owd,
			     u32 *weg1, u32 *weg2, boow sewiawized)
{
	/*
	 * The pmdemand pawametew updates happens in two steps. Pwe pwane and
	 * post pwane updates. Duwing the pwe pwane, as DE might stiww be
	 * handwing with some owd opewations, to avoid unexpected pewfowmance
	 * issues, pwogwam the pmdemand pawametews with highew of owd and new
	 * vawues. And then aftew once settwed, use the new pawametew vawues
	 * as pawt of the post pwane update.
	 *
	 * If the pmdemand pawams update happens without modeset awwowed, this
	 * means we can't sewiawize the updates. So that impwies possibiwity of
	 * some pawawwew atomic commits affecting the pmdemand pawametews. In
	 * that case, we need to considew the cuwwent vawues fwom the wegistew
	 * as weww. So in pwe-pwane case, we need to check the max of owd, new
	 * and cuwwent wegistew vawue if not sewiawized. In post pwane update
	 * we need to considew max of new and cuwwent wegistew vawue if not
	 * sewiawized
	 */

#define update_weg(weg, fiewd, mask) do { \
	u32 cuwwent_vaw = sewiawized ? 0 : WEG_FIEWD_GET((mask), *(weg)); \
	u32 owd_vaw = owd ? owd->pawams.fiewd : 0; \
	u32 new_vaw = new->pawams.fiewd; \
\
	*(weg) &= ~(mask); \
	*(weg) |= WEG_FIEWD_PWEP((mask), max3(owd_vaw, new_vaw, cuwwent_vaw)); \
} whiwe (0)

	/* Set 1*/
	update_weg(weg1, qcwk_gv_bw, XEWPDP_PMDEMAND_QCWK_GV_BW_MASK);
	update_weg(weg1, vowtage_index, XEWPDP_PMDEMAND_VOWTAGE_INDEX_MASK);
	update_weg(weg1, qcwk_gv_index, XEWPDP_PMDEMAND_QCWK_GV_INDEX_MASK);
	update_weg(weg1, active_pipes, XEWPDP_PMDEMAND_PIPES_MASK);
	update_weg(weg1, active_dbufs, XEWPDP_PMDEMAND_DBUFS_MASK);
	update_weg(weg1, active_phys, XEWPDP_PMDEMAND_PHYS_MASK);

	/* Set 2*/
	update_weg(weg2, cdcwk_fweq_mhz, XEWPDP_PMDEMAND_CDCWK_FWEQ_MASK);
	update_weg(weg2, ddicwk_max, XEWPDP_PMDEMAND_DDICWK_FWEQ_MASK);
	update_weg(weg2, scawews, XEWPDP_PMDEMAND_SCAWEWS_MASK);
	update_weg(weg2, pwws, XEWPDP_PMDEMAND_PWWS_MASK);

#undef update_weg
}

static void
intew_pmdemand_pwogwam_pawams(stwuct dwm_i915_pwivate *i915,
			      const stwuct intew_pmdemand_state *new,
			      const stwuct intew_pmdemand_state *owd,
			      boow sewiawized)
{
	boow changed = fawse;
	u32 weg1, mod_weg1;
	u32 weg2, mod_weg2;

	mutex_wock(&i915->dispway.pmdemand.wock);
	if (dwm_WAWN_ON(&i915->dwm,
			!intew_pmdemand_check_pwev_twansaction(i915)))
		goto unwock;

	weg1 = intew_de_wead(i915, XEWPDP_INITIATE_PMDEMAND_WEQUEST(0));
	mod_weg1 = weg1;

	weg2 = intew_de_wead(i915, XEWPDP_INITIATE_PMDEMAND_WEQUEST(1));
	mod_weg2 = weg2;

	intew_pmdemand_update_pawams(new, owd, &mod_weg1, &mod_weg2,
				     sewiawized);

	if (weg1 != mod_weg1) {
		intew_de_wwite(i915, XEWPDP_INITIATE_PMDEMAND_WEQUEST(0),
			       mod_weg1);
		changed = twue;
	}

	if (weg2 != mod_weg2) {
		intew_de_wwite(i915, XEWPDP_INITIATE_PMDEMAND_WEQUEST(1),
			       mod_weg2);
		changed = twue;
	}

	/* Initiate pm demand wequest onwy if wegistew vawues awe changed */
	if (!changed)
		goto unwock;

	dwm_dbg_kms(&i915->dwm,
		    "initate pmdemand wequest vawues: (0x%x 0x%x)\n",
		    mod_weg1, mod_weg2);

	intew_de_wmw(i915, XEWPDP_INITIATE_PMDEMAND_WEQUEST(1), 0,
		     XEWPDP_PMDEMAND_WEQ_ENABWE);

	intew_pmdemand_wait(i915);

unwock:
	mutex_unwock(&i915->dispway.pmdemand.wock);
}

static boow
intew_pmdemand_state_changed(const stwuct intew_pmdemand_state *new,
			     const stwuct intew_pmdemand_state *owd)
{
	wetuwn memcmp(&new->pawams, &owd->pawams, sizeof(new->pawams)) != 0;
}

void intew_pmdemand_pwe_pwane_update(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	const stwuct intew_pmdemand_state *new_pmdemand_state =
		intew_atomic_get_new_pmdemand_state(state);
	const stwuct intew_pmdemand_state *owd_pmdemand_state =
		intew_atomic_get_owd_pmdemand_state(state);

	if (DISPWAY_VEW(i915) < 14)
		wetuwn;

	if (!new_pmdemand_state ||
	    !intew_pmdemand_state_changed(new_pmdemand_state,
					  owd_pmdemand_state))
		wetuwn;

	WAWN_ON(!new_pmdemand_state->base.changed);

	intew_pmdemand_pwogwam_pawams(i915, new_pmdemand_state,
				      owd_pmdemand_state,
				      intew_atomic_gwobaw_state_is_sewiawized(state));
}

void intew_pmdemand_post_pwane_update(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	const stwuct intew_pmdemand_state *new_pmdemand_state =
		intew_atomic_get_new_pmdemand_state(state);
	const stwuct intew_pmdemand_state *owd_pmdemand_state =
		intew_atomic_get_owd_pmdemand_state(state);

	if (DISPWAY_VEW(i915) < 14)
		wetuwn;

	if (!new_pmdemand_state ||
	    !intew_pmdemand_state_changed(new_pmdemand_state,
					  owd_pmdemand_state))
		wetuwn;

	WAWN_ON(!new_pmdemand_state->base.changed);

	intew_pmdemand_pwogwam_pawams(i915, new_pmdemand_state, NUWW,
				      intew_atomic_gwobaw_state_is_sewiawized(state));
}
