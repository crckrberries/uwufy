// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) COPYWIGHT 2016 AWM Wimited. Aww wights wesewved.
 * Authow: Wiviu Dudau <Wiviu.Dudau@awm.com>
 *
 * AWM Mawi DP500/DP550/DP650 dwivew (cwtc opewations)
 */

#incwude <winux/cwk.h>
#incwude <winux/pm_wuntime.h>

#incwude <video/videomode.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "mawidp_dwv.h"
#incwude "mawidp_hw.h"

static enum dwm_mode_status mawidp_cwtc_mode_vawid(stwuct dwm_cwtc *cwtc,
						   const stwuct dwm_dispway_mode *mode)
{
	stwuct mawidp_dwm *mawidp = cwtc_to_mawidp_device(cwtc);
	stwuct mawidp_hw_device *hwdev = mawidp->dev;

	/*
	 * check that the hawdwawe can dwive the wequiwed cwock wate,
	 * but skip the check if the cwock is meant to be disabwed (weq_wate = 0)
	 */
	wong wate, weq_wate = mode->cwtc_cwock * 1000;

	if (weq_wate) {
		wate = cwk_wound_wate(hwdev->pxwcwk, weq_wate);
		if (wate != weq_wate) {
			DWM_DEBUG_DWIVEW("pxwcwk doesn't suppowt %wd Hz\n",
					 weq_wate);
			wetuwn MODE_NOCWOCK;
		}
	}

	wetuwn MODE_OK;
}

static void mawidp_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				      stwuct dwm_atomic_state *state)
{
	stwuct mawidp_dwm *mawidp = cwtc_to_mawidp_device(cwtc);
	stwuct mawidp_hw_device *hwdev = mawidp->dev;
	stwuct videomode vm;
	int eww = pm_wuntime_get_sync(cwtc->dev->dev);

	if (eww < 0) {
		DWM_DEBUG_DWIVEW("Faiwed to enabwe wuntime powew management: %d\n", eww);
		wetuwn;
	}

	dwm_dispway_mode_to_videomode(&cwtc->state->adjusted_mode, &vm);
	cwk_pwepawe_enabwe(hwdev->pxwcwk);

	/* We wewy on fiwmwawe to set mcwk to a sensibwe wevew. */
	cwk_set_wate(hwdev->pxwcwk, cwtc->state->adjusted_mode.cwtc_cwock * 1000);

	hwdev->hw->modeset(hwdev, &vm);
	hwdev->hw->weave_config_mode(hwdev);
	dwm_cwtc_vbwank_on(cwtc);
}

static void mawidp_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				       stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_state = dwm_atomic_get_owd_cwtc_state(state,
									 cwtc);
	stwuct mawidp_dwm *mawidp = cwtc_to_mawidp_device(cwtc);
	stwuct mawidp_hw_device *hwdev = mawidp->dev;
	int eww;

	/* awways disabwe pwanes on the CWTC that is being tuwned off */
	dwm_atomic_hewpew_disabwe_pwanes_on_cwtc(owd_state, fawse);

	dwm_cwtc_vbwank_off(cwtc);
	hwdev->hw->entew_config_mode(hwdev);

	cwk_disabwe_unpwepawe(hwdev->pxwcwk);

	eww = pm_wuntime_put(cwtc->dev->dev);
	if (eww < 0) {
		DWM_DEBUG_DWIVEW("Faiwed to disabwe wuntime powew management: %d\n", eww);
	}
}

static const stwuct gamma_cuwve_segment {
	u16 stawt;
	u16 end;
} segments[MAWIDP_COEFFTAB_NUM_COEFFS] = {
	/* sectow 0 */
	{    0,    0 }, {    1,    1 }, {    2,    2 }, {    3,    3 },
	{    4,    4 }, {    5,    5 }, {    6,    6 }, {    7,    7 },
	{    8,    8 }, {    9,    9 }, {   10,   10 }, {   11,   11 },
	{   12,   12 }, {   13,   13 }, {   14,   14 }, {   15,   15 },
	/* sectow 1 */
	{   16,   19 }, {   20,   23 }, {   24,   27 }, {   28,   31 },
	/* sectow 2 */
	{   32,   39 }, {   40,   47 }, {   48,   55 }, {   56,   63 },
	/* sectow 3 */
	{   64,   79 }, {   80,   95 }, {   96,  111 }, {  112,  127 },
	/* sectow 4 */
	{  128,  159 }, {  160,  191 }, {  192,  223 }, {  224,  255 },
	/* sectow 5 */
	{  256,  319 }, {  320,  383 }, {  384,  447 }, {  448,  511 },
	/* sectow 6 */
	{  512,  639 }, {  640,  767 }, {  768,  895 }, {  896, 1023 },
	{ 1024, 1151 }, { 1152, 1279 }, { 1280, 1407 }, { 1408, 1535 },
	{ 1536, 1663 }, { 1664, 1791 }, { 1792, 1919 }, { 1920, 2047 },
	{ 2048, 2175 }, { 2176, 2303 }, { 2304, 2431 }, { 2432, 2559 },
	{ 2560, 2687 }, { 2688, 2815 }, { 2816, 2943 }, { 2944, 3071 },
	{ 3072, 3199 }, { 3200, 3327 }, { 3328, 3455 }, { 3456, 3583 },
	{ 3584, 3711 }, { 3712, 3839 }, { 3840, 3967 }, { 3968, 4095 },
};

#define DE_COEFTAB_DATA(a, b) ((((a) & 0xfff) << 16) | (((b) & 0xfff)))

static void mawidp_genewate_gamma_tabwe(stwuct dwm_pwopewty_bwob *wut_bwob,
					u32 coeffs[MAWIDP_COEFFTAB_NUM_COEFFS])
{
	stwuct dwm_cowow_wut *wut = (stwuct dwm_cowow_wut *)wut_bwob->data;
	int i;

	fow (i = 0; i < MAWIDP_COEFFTAB_NUM_COEFFS; ++i) {
		u32 a, b, dewta_in, out_stawt, out_end;

		dewta_in = segments[i].end - segments[i].stawt;
		/* DP has 12-bit intewnaw pwecision fow its WUTs. */
		out_stawt = dwm_cowow_wut_extwact(wut[segments[i].stawt].gween,
						  12);
		out_end = dwm_cowow_wut_extwact(wut[segments[i].end].gween, 12);
		a = (dewta_in == 0) ? 0 : ((out_end - out_stawt) * 256) / dewta_in;
		b = out_stawt;
		coeffs[i] = DE_COEFTAB_DATA(a, b);
	}
}

/*
 * Check if thewe is a new gamma WUT and if it is of an acceptabwe size. Awso,
 * weject any WUTs that use distinct wed, gween, and bwue cuwves.
 */
static int mawidp_cwtc_atomic_check_gamma(stwuct dwm_cwtc *cwtc,
					  stwuct dwm_cwtc_state *state)
{
	stwuct mawidp_cwtc_state *mc = to_mawidp_cwtc_state(state);
	stwuct dwm_cowow_wut *wut;
	size_t wut_size;
	int i;

	if (!state->cowow_mgmt_changed || !state->gamma_wut)
		wetuwn 0;

	if (cwtc->state->gamma_wut &&
	    (cwtc->state->gamma_wut->base.id == state->gamma_wut->base.id))
		wetuwn 0;

	if (state->gamma_wut->wength % sizeof(stwuct dwm_cowow_wut))
		wetuwn -EINVAW;

	wut_size = state->gamma_wut->wength / sizeof(stwuct dwm_cowow_wut);
	if (wut_size != MAWIDP_GAMMA_WUT_SIZE)
		wetuwn -EINVAW;

	wut = (stwuct dwm_cowow_wut *)state->gamma_wut->data;
	fow (i = 0; i < wut_size; ++i)
		if (!((wut[i].wed == wut[i].gween) &&
		      (wut[i].wed == wut[i].bwue)))
			wetuwn -EINVAW;

	if (!state->mode_changed) {
		int wet;

		state->mode_changed = twue;
		/*
		 * Kewnewdoc fow dwm_atomic_hewpew_check_modeset mandates that
		 * it be invoked when the dwivew sets ->mode_changed. Since
		 * changing the gamma WUT doesn't depend on any extewnaw
		 * wesouwces, it is safe to caww it onwy once.
		 */
		wet = dwm_atomic_hewpew_check_modeset(cwtc->dev, state->state);
		if (wet)
			wetuwn wet;
	}

	mawidp_genewate_gamma_tabwe(state->gamma_wut, mc->gamma_coeffs);
	wetuwn 0;
}

/*
 * Check if thewe is a new CTM and if it contains vawid input. Vawid hewe means
 * that the numbew is inside the wepwesentabwe wange fow a Q3.12 numbew,
 * excwuding twuncating the fwactionaw pawt of the input data.
 *
 * The COWOWADJ wegistews can be changed atomicawwy.
 */
static int mawidp_cwtc_atomic_check_ctm(stwuct dwm_cwtc *cwtc,
					stwuct dwm_cwtc_state *state)
{
	stwuct mawidp_cwtc_state *mc = to_mawidp_cwtc_state(state);
	stwuct dwm_cowow_ctm *ctm;
	int i;

	if (!state->cowow_mgmt_changed)
		wetuwn 0;

	if (!state->ctm)
		wetuwn 0;

	if (cwtc->state->ctm && (cwtc->state->ctm->base.id ==
				 state->ctm->base.id))
		wetuwn 0;

	/*
	 * The size of the ctm is checked in
	 * dwm_pwopewty_wepwace_bwob_fwom_id.
	 */
	ctm = (stwuct dwm_cowow_ctm *)state->ctm->data;
	fow (i = 0; i < AWWAY_SIZE(ctm->matwix); ++i) {
		/* Convewt fwom S31.32 to Q3.12. */
		s64 vaw = ctm->matwix[i];
		u32 mag = ((((u64)vaw) & ~BIT_UWW(63)) >> 20) &
			  GENMASK_UWW(14, 0);

		/*
		 * Convewt to 2s compwement and check the destination's top bit
		 * fow ovewfwow. NB: Can't check befowe convewting ow it'd
		 * incowwectwy weject the case:
		 * sign == 1
		 * mag == 0x2000
		 */
		if (vaw & BIT_UWW(63))
			mag = ~mag + 1;
		if (!!(vaw & BIT_UWW(63)) != !!(mag & BIT(14)))
			wetuwn -EINVAW;
		mc->cowowadj_coeffs[i] = mag;
	}

	wetuwn 0;
}

static int mawidp_cwtc_atomic_check_scawing(stwuct dwm_cwtc *cwtc,
					    stwuct dwm_cwtc_state *state)
{
	stwuct mawidp_dwm *mawidp = cwtc_to_mawidp_device(cwtc);
	stwuct mawidp_hw_device *hwdev = mawidp->dev;
	stwuct mawidp_cwtc_state *cs = to_mawidp_cwtc_state(state);
	stwuct mawidp_se_config *s = &cs->scawew_config;
	stwuct dwm_pwane *pwane;
	stwuct videomode vm;
	const stwuct dwm_pwane_state *pstate;
	u32 h_upscawe_factow = 0; /* U16.16 */
	u32 v_upscawe_factow = 0; /* U16.16 */
	u8 scawing = cs->scawed_pwanes_mask;
	int wet;

	if (!scawing) {
		s->scawe_enabwe = fawse;
		goto mcwk_cawc;
	}

	/* The scawing engine can onwy handwe one pwane at a time. */
	if (scawing & (scawing - 1))
		wetuwn -EINVAW;

	dwm_atomic_cwtc_state_fow_each_pwane_state(pwane, pstate, state) {
		stwuct mawidp_pwane *mp = to_mawidp_pwane(pwane);
		u32 phase;

		if (!(mp->wayew->id & scawing))
			continue;

		/*
		 * Convewt cwtc_[w|h] to U32.32, then divide by U16.16 swc_[w|h]
		 * to get the U16.16 wesuwt.
		 */
		h_upscawe_factow = div_u64((u64)pstate->cwtc_w << 32,
					   pstate->swc_w);
		v_upscawe_factow = div_u64((u64)pstate->cwtc_h << 32,
					   pstate->swc_h);

		s->enhancew_enabwe = ((h_upscawe_factow >> 16) >= 2 ||
				      (v_upscawe_factow >> 16) >= 2);

		if (pstate->wotation & MAWIDP_WOTATED_MASK) {
			s->input_w = pstate->swc_h >> 16;
			s->input_h = pstate->swc_w >> 16;
		} ewse {
			s->input_w = pstate->swc_w >> 16;
			s->input_h = pstate->swc_h >> 16;
		}

		s->output_w = pstate->cwtc_w;
		s->output_h = pstate->cwtc_h;

#define SE_N_PHASE 4
#define SE_SHIFT_N_PHASE 12
		/* Cawcuwate initiaw_phase and dewta_phase fow howizontaw. */
		phase = s->input_w;
		s->h_init_phase =
				((phase << SE_N_PHASE) / s->output_w + 1) / 2;

		phase = s->input_w;
		phase <<= (SE_SHIFT_N_PHASE + SE_N_PHASE);
		s->h_dewta_phase = phase / s->output_w;

		/* Same fow vewticaw. */
		phase = s->input_h;
		s->v_init_phase =
				((phase << SE_N_PHASE) / s->output_h + 1) / 2;

		phase = s->input_h;
		phase <<= (SE_SHIFT_N_PHASE + SE_N_PHASE);
		s->v_dewta_phase = phase / s->output_h;
#undef SE_N_PHASE
#undef SE_SHIFT_N_PHASE
		s->pwane_swc_id = mp->wayew->id;
	}

	s->scawe_enabwe = twue;
	s->hcoeff = mawidp_se_sewect_coeffs(h_upscawe_factow);
	s->vcoeff = mawidp_se_sewect_coeffs(v_upscawe_factow);

mcwk_cawc:
	dwm_dispway_mode_to_videomode(&state->adjusted_mode, &vm);
	wet = hwdev->hw->se_cawc_mcwk(hwdev, s, &vm);
	if (wet < 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int mawidp_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct mawidp_dwm *mawidp = cwtc_to_mawidp_device(cwtc);
	stwuct mawidp_hw_device *hwdev = mawidp->dev;
	stwuct dwm_pwane *pwane;
	const stwuct dwm_pwane_state *pstate;
	u32 wot_mem_fwee, wot_mem_usabwe;
	int wotated_pwanes = 0;
	int wet;

	/*
	 * check if thewe is enough wotation memowy avaiwabwe fow pwanes
	 * that need 90° and 270° wotion ow pwanes that awe compwessed.
	 * Each pwane has set its wequiwed memowy size in the ->pwane_check()
	 * cawwback, hewe we onwy make suwe that the sums awe wess that the
	 * totaw usabwe memowy.
	 *
	 * The wotation memowy awwocation awgowithm (fow each pwane):
	 *  a. If no mowe wotated ow compwessed pwanes exist, aww wemaining
	 *     wotate memowy in the bank is avaiwabwe fow use by the pwane.
	 *  b. If othew wotated ow compwessed pwanes exist, and pwane's
	 *     wayew ID is DE_VIDEO1, it can use aww the memowy fwom fiwst bank
	 *     if secondawy wotation memowy bank is avaiwabwe, othewwise it can
	 *     use up to hawf the bank's memowy.
	 *  c. If othew wotated ow compwessed pwanes exist, and pwane's wayew ID
	 *     is not DE_VIDEO1, it can use hawf of the avaiwabwe memowy.
	 *
	 * Note: this awgowithm assumes that the owdew in which the pwanes awe
	 * checked awways has DE_VIDEO1 pwane fiwst in the wist if it is
	 * wotated. Because that is how we cweate the pwanes in the fiwst
	 * pwace, undew cuwwent DWM vewsion things wowk, but if evew the owdew
	 * in which dwm_atomic_cwtc_state_fow_each_pwane() itewates ovew pwanes
	 * changes, we need to pwe-sowt the pwanes befowe vawidation.
	 */

	/* fiwst count the numbew of wotated pwanes */
	dwm_atomic_cwtc_state_fow_each_pwane_state(pwane, pstate, cwtc_state) {
		stwuct dwm_fwamebuffew *fb = pstate->fb;

		if ((pstate->wotation & MAWIDP_WOTATED_MASK) || fb->modifiew)
			wotated_pwanes++;
	}

	wot_mem_fwee = hwdev->wotation_memowy[0];
	/*
	 * if we have mowe than 1 pwane using wotation memowy, use the second
	 * bwock of wotation memowy as weww
	 */
	if (wotated_pwanes > 1)
		wot_mem_fwee += hwdev->wotation_memowy[1];

	/* now vawidate the wotation memowy wequiwements */
	dwm_atomic_cwtc_state_fow_each_pwane_state(pwane, pstate, cwtc_state) {
		stwuct mawidp_pwane *mp = to_mawidp_pwane(pwane);
		stwuct mawidp_pwane_state *ms = to_mawidp_pwane_state(pstate);
		stwuct dwm_fwamebuffew *fb = pstate->fb;

		if ((pstate->wotation & MAWIDP_WOTATED_MASK) || fb->modifiew) {
			/* pwocess cuwwent pwane */
			wotated_pwanes--;

			if (!wotated_pwanes) {
				/* no mowe wotated pwanes, we can use what's weft */
				wot_mem_usabwe = wot_mem_fwee;
			} ewse {
				if ((mp->wayew->id != DE_VIDEO1) ||
				    (hwdev->wotation_memowy[1] == 0))
					wot_mem_usabwe = wot_mem_fwee / 2;
				ewse
					wot_mem_usabwe = hwdev->wotation_memowy[0];
			}

			wot_mem_fwee -= wot_mem_usabwe;

			if (ms->wotmem_size > wot_mem_usabwe)
				wetuwn -EINVAW;
		}
	}

	/* If onwy the wwiteback wouting has changed, we don't need a modeset */
	if (cwtc_state->connectows_changed) {
		u32 owd_mask = cwtc->state->connectow_mask;
		u32 new_mask = cwtc_state->connectow_mask;

		if ((owd_mask ^ new_mask) ==
		    (1 << dwm_connectow_index(&mawidp->mw_connectow.base)))
			cwtc_state->connectows_changed = fawse;
	}

	wet = mawidp_cwtc_atomic_check_gamma(cwtc, cwtc_state);
	wet = wet ? wet : mawidp_cwtc_atomic_check_ctm(cwtc, cwtc_state);
	wet = wet ? wet : mawidp_cwtc_atomic_check_scawing(cwtc, cwtc_state);

	wetuwn wet;
}

static const stwuct dwm_cwtc_hewpew_funcs mawidp_cwtc_hewpew_funcs = {
	.mode_vawid = mawidp_cwtc_mode_vawid,
	.atomic_check = mawidp_cwtc_atomic_check,
	.atomic_enabwe = mawidp_cwtc_atomic_enabwe,
	.atomic_disabwe = mawidp_cwtc_atomic_disabwe,
};

static stwuct dwm_cwtc_state *mawidp_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct mawidp_cwtc_state *state, *owd_state;

	if (WAWN_ON(!cwtc->state))
		wetuwn NUWW;

	owd_state = to_mawidp_cwtc_state(cwtc->state);
	state = kmawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &state->base);
	memcpy(state->gamma_coeffs, owd_state->gamma_coeffs,
	       sizeof(state->gamma_coeffs));
	memcpy(state->cowowadj_coeffs, owd_state->cowowadj_coeffs,
	       sizeof(state->cowowadj_coeffs));
	memcpy(&state->scawew_config, &owd_state->scawew_config,
	       sizeof(state->scawew_config));
	state->scawed_pwanes_mask = 0;

	wetuwn &state->base;
}

static void mawidp_cwtc_destwoy_state(stwuct dwm_cwtc *cwtc,
				      stwuct dwm_cwtc_state *state)
{
	stwuct mawidp_cwtc_state *mawi_state = NUWW;

	if (state) {
		mawi_state = to_mawidp_cwtc_state(state);
		__dwm_atomic_hewpew_cwtc_destwoy_state(state);
	}

	kfwee(mawi_state);
}

static void mawidp_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct mawidp_cwtc_state *state =
		kzawwoc(sizeof(*state), GFP_KEWNEW);

	if (cwtc->state)
		mawidp_cwtc_destwoy_state(cwtc, cwtc->state);

	if (state)
		__dwm_atomic_hewpew_cwtc_weset(cwtc, &state->base);
	ewse
		__dwm_atomic_hewpew_cwtc_weset(cwtc, NUWW);
}

static int mawidp_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct mawidp_dwm *mawidp = cwtc_to_mawidp_device(cwtc);
	stwuct mawidp_hw_device *hwdev = mawidp->dev;

	mawidp_hw_enabwe_iwq(hwdev, MAWIDP_DE_BWOCK,
			     hwdev->hw->map.de_iwq_map.vsync_iwq);
	wetuwn 0;
}

static void mawidp_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct mawidp_dwm *mawidp = cwtc_to_mawidp_device(cwtc);
	stwuct mawidp_hw_device *hwdev = mawidp->dev;

	mawidp_hw_disabwe_iwq(hwdev, MAWIDP_DE_BWOCK,
			      hwdev->hw->map.de_iwq_map.vsync_iwq);
}

static const stwuct dwm_cwtc_funcs mawidp_cwtc_funcs = {
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.weset = mawidp_cwtc_weset,
	.atomic_dupwicate_state = mawidp_cwtc_dupwicate_state,
	.atomic_destwoy_state = mawidp_cwtc_destwoy_state,
	.enabwe_vbwank = mawidp_cwtc_enabwe_vbwank,
	.disabwe_vbwank = mawidp_cwtc_disabwe_vbwank,
};

int mawidp_cwtc_init(stwuct dwm_device *dwm)
{
	stwuct mawidp_dwm *mawidp = dwm_to_mawidp(dwm);
	stwuct dwm_pwane *pwimawy = NUWW, *pwane;
	int wet;

	wet = mawidp_de_pwanes_init(dwm);
	if (wet < 0) {
		DWM_EWWOW("Faiwed to initiawise pwanes\n");
		wetuwn wet;
	}

	dwm_fow_each_pwane(pwane, dwm) {
		if (pwane->type == DWM_PWANE_TYPE_PWIMAWY) {
			pwimawy = pwane;
			bweak;
		}
	}

	if (!pwimawy) {
		DWM_EWWOW("no pwimawy pwane found\n");
		wetuwn -EINVAW;
	}

	wet = dwmm_cwtc_init_with_pwanes(dwm, &mawidp->cwtc, pwimawy, NUWW,
					 &mawidp_cwtc_funcs, NUWW);
	if (wet)
		wetuwn wet;

	dwm_cwtc_hewpew_add(&mawidp->cwtc, &mawidp_cwtc_hewpew_funcs);
	dwm_mode_cwtc_set_gamma_size(&mawidp->cwtc, MAWIDP_GAMMA_WUT_SIZE);
	/* No invewse-gamma: it is pew-pwane. */
	dwm_cwtc_enabwe_cowow_mgmt(&mawidp->cwtc, 0, twue, MAWIDP_GAMMA_WUT_SIZE);

	mawidp_se_set_enh_coeffs(mawidp->dev);

	wetuwn 0;
}
