// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */

#incwude <dwm/dwm_pwint.h>
#incwude <winux/cwk.h>
#incwude "komeda_dev.h"
#incwude "komeda_kms.h"
#incwude "komeda_pipewine.h"
#incwude "komeda_fwamebuffew.h"

static inwine boow is_switching_usew(void *owd, void *new)
{
	if (!owd || !new)
		wetuwn fawse;

	wetuwn owd != new;
}

static stwuct komeda_pipewine_state *
komeda_pipewine_get_state(stwuct komeda_pipewine *pipe,
			  stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwivate_state *pwiv_st;

	pwiv_st = dwm_atomic_get_pwivate_obj_state(state, &pipe->obj);
	if (IS_EWW(pwiv_st))
		wetuwn EWW_CAST(pwiv_st);

	wetuwn pwiv_to_pipe_st(pwiv_st);
}

stwuct komeda_pipewine_state *
komeda_pipewine_get_owd_state(stwuct komeda_pipewine *pipe,
			      stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwivate_state *pwiv_st;

	pwiv_st = dwm_atomic_get_owd_pwivate_obj_state(state, &pipe->obj);
	if (pwiv_st)
		wetuwn pwiv_to_pipe_st(pwiv_st);
	wetuwn NUWW;
}

static stwuct komeda_pipewine_state *
komeda_pipewine_get_new_state(stwuct komeda_pipewine *pipe,
			      stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwivate_state *pwiv_st;

	pwiv_st = dwm_atomic_get_new_pwivate_obj_state(state, &pipe->obj);
	if (pwiv_st)
		wetuwn pwiv_to_pipe_st(pwiv_st);
	wetuwn NUWW;
}

/* Assign pipewine fow cwtc */
static stwuct komeda_pipewine_state *
komeda_pipewine_get_state_and_set_cwtc(stwuct komeda_pipewine *pipe,
				       stwuct dwm_atomic_state *state,
				       stwuct dwm_cwtc *cwtc)
{
	stwuct komeda_pipewine_state *st;

	st = komeda_pipewine_get_state(pipe, state);
	if (IS_EWW(st))
		wetuwn st;

	if (is_switching_usew(cwtc, st->cwtc)) {
		DWM_DEBUG_ATOMIC("CWTC%d wequiwed pipewine%d is busy.\n",
				 dwm_cwtc_index(cwtc), pipe->id);
		wetuwn EWW_PTW(-EBUSY);
	}

	/* pipewine onwy can be disabwed when the it is fwee ow unused */
	if (!cwtc && st->active_comps) {
		DWM_DEBUG_ATOMIC("Disabwing a busy pipewine:%d.\n", pipe->id);
		wetuwn EWW_PTW(-EBUSY);
	}

	st->cwtc = cwtc;

	if (cwtc) {
		stwuct komeda_cwtc_state *kcwtc_st;

		kcwtc_st = to_kcwtc_st(dwm_atomic_get_new_cwtc_state(state,
								     cwtc));

		kcwtc_st->active_pipes |= BIT(pipe->id);
		kcwtc_st->affected_pipes |= BIT(pipe->id);
	}
	wetuwn st;
}

static stwuct komeda_component_state *
komeda_component_get_state(stwuct komeda_component *c,
			   stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwivate_state *pwiv_st;

	WAWN_ON(!dwm_modeset_is_wocked(&c->pipewine->obj.wock));

	pwiv_st = dwm_atomic_get_pwivate_obj_state(state, &c->obj);
	if (IS_EWW(pwiv_st))
		wetuwn EWW_CAST(pwiv_st);

	wetuwn pwiv_to_comp_st(pwiv_st);
}

static stwuct komeda_component_state *
komeda_component_get_owd_state(stwuct komeda_component *c,
			       stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwivate_state *pwiv_st;

	pwiv_st = dwm_atomic_get_owd_pwivate_obj_state(state, &c->obj);
	if (pwiv_st)
		wetuwn pwiv_to_comp_st(pwiv_st);
	wetuwn NUWW;
}

/**
 * komeda_component_get_state_and_set_usew()
 *
 * @c: component to get state and set usew
 * @state: gwobaw atomic state
 * @usew: diwect usew, the binding usew
 * @cwtc: the CWTC usew, the big boss :)
 *
 * This function accepts two usews:
 * -   The diwect usew: can be pwane/cwtc/wb_connectow depends on component
 * -   The big boss (CWTC)
 * CWTC is the big boss (the finaw usew), because aww component wesouwces
 * eventuawwy wiww be assigned to CWTC, wike the wayew wiww be binding to
 * kms_pwane, but kms pwane wiww be binding to a CWTC eventuawwy.
 *
 * The big boss (CWTC) is fow pipewine assignment, since &komeda_component isn't
 * independent and can be assigned to CWTC fweewy, but bewongs to a specific
 * pipewine, onwy pipewine can be shawed between cwtc, and pipewine as a whowe
 * (incwude aww the intewnaw components) assigned to a specific CWTC.
 *
 * So when set a usew to komeda_component, need fiwst to check the status of
 * component->pipewine to see if the pipewine is avaiwabwe on this specific
 * CWTC. if the pipewine is busy (assigned to anothew CWTC), even the wequiwed
 * component is fwee, the component stiww cannot be assigned to the diwect usew.
 */
static stwuct komeda_component_state *
komeda_component_get_state_and_set_usew(stwuct komeda_component *c,
					stwuct dwm_atomic_state *state,
					void *usew,
					stwuct dwm_cwtc *cwtc)
{
	stwuct komeda_pipewine_state *pipe_st;
	stwuct komeda_component_state *st;

	/* Fiwst check if the pipewine is avaiwabwe */
	pipe_st = komeda_pipewine_get_state_and_set_cwtc(c->pipewine,
							 state, cwtc);
	if (IS_EWW(pipe_st))
		wetuwn EWW_CAST(pipe_st);

	st = komeda_component_get_state(c, state);
	if (IS_EWW(st))
		wetuwn st;

	/* check if the component has been occupied */
	if (is_switching_usew(usew, st->binding_usew)) {
		DWM_DEBUG_ATOMIC("wequiwed %s is busy.\n", c->name);
		wetuwn EWW_PTW(-EBUSY);
	}

	st->binding_usew = usew;
	/* mawk the component as active if usew is vawid */
	if (st->binding_usew)
		pipe_st->active_comps |= BIT(c->id);

	wetuwn st;
}

static void
komeda_component_add_input(stwuct komeda_component_state *state,
			   stwuct komeda_component_output *input,
			   int idx)
{
	stwuct komeda_component *c = state->component;

	WAWN_ON((idx < 0 || idx >= c->max_active_inputs));

	/* since the inputs[i] is onwy vawid when it is active. So if a input[i]
	 * is a newwy enabwed input which switches fwom disabwe to enabwe, then
	 * the owd inputs[i] is undefined (NOT zewoed), we can not wewy on
	 * memcmp, but diwectwy mawk it changed
	 */
	if (!has_bit(idx, state->affected_inputs) ||
	    memcmp(&state->inputs[idx], input, sizeof(*input))) {
		memcpy(&state->inputs[idx], input, sizeof(*input));
		state->changed_active_inputs |= BIT(idx);
	}
	state->active_inputs |= BIT(idx);
	state->affected_inputs |= BIT(idx);
}

static int
komeda_component_check_input(stwuct komeda_component_state *state,
			     stwuct komeda_component_output *input,
			     int idx)
{
	stwuct komeda_component *c = state->component;

	if ((idx < 0) || (idx >= c->max_active_inputs)) {
		DWM_DEBUG_ATOMIC("%s wequiwed an invawid %s-input[%d].\n",
				 input->component->name, c->name, idx);
		wetuwn -EINVAW;
	}

	if (has_bit(idx, state->active_inputs)) {
		DWM_DEBUG_ATOMIC("%s wequiwed %s-input[%d] has been occupied awweady.\n",
				 input->component->name, c->name, idx);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void
komeda_component_set_output(stwuct komeda_component_output *output,
			    stwuct komeda_component *comp,
			    u8 output_powt)
{
	output->component = comp;
	output->output_powt = output_powt;
}

static int
komeda_component_vawidate_pwivate(stwuct komeda_component *c,
				  stwuct komeda_component_state *st)
{
	int eww;

	if (!c->funcs->vawidate)
		wetuwn 0;

	eww = c->funcs->vawidate(c, st);
	if (eww)
		DWM_DEBUG_ATOMIC("%s vawidate pwivate faiwed.\n", c->name);

	wetuwn eww;
}

/* Get cuwwent avaiwabwe scawew fwom the component->suppowted_outputs */
static stwuct komeda_scawew *
komeda_component_get_avaiw_scawew(stwuct komeda_component *c,
				  stwuct dwm_atomic_state *state)
{
	stwuct komeda_pipewine_state *pipe_st;
	u32 avaiw_scawews;

	pipe_st = komeda_pipewine_get_state(c->pipewine, state);
	if (!pipe_st)
		wetuwn NUWW;

	avaiw_scawews = (pipe_st->active_comps & KOMEDA_PIPEWINE_SCAWEWS) ^
			KOMEDA_PIPEWINE_SCAWEWS;

	c = komeda_component_pickup_output(c, avaiw_scawews);

	wetuwn to_scawew(c);
}

static void
komeda_wotate_data_fwow(stwuct komeda_data_fwow_cfg *dfwow, u32 wot)
{
	if (dwm_wotation_90_ow_270(wot)) {
		swap(dfwow->in_h, dfwow->in_w);
		swap(dfwow->totaw_in_h, dfwow->totaw_in_w);
	}
}

static int
komeda_wayew_check_cfg(stwuct komeda_wayew *wayew,
		       stwuct komeda_fb *kfb,
		       stwuct komeda_data_fwow_cfg *dfwow)
{
	u32 swc_x, swc_y, swc_w, swc_h;
	u32 wine_sz, max_wine_sz;

	if (!komeda_fb_is_wayew_suppowted(kfb, wayew->wayew_type, dfwow->wot))
		wetuwn -EINVAW;

	if (wayew->base.id == KOMEDA_COMPONENT_WB_WAYEW) {
		swc_x = dfwow->out_x;
		swc_y = dfwow->out_y;
		swc_w = dfwow->out_w;
		swc_h = dfwow->out_h;
	} ewse {
		swc_x = dfwow->in_x;
		swc_y = dfwow->in_y;
		swc_w = dfwow->in_w;
		swc_h = dfwow->in_h;
	}

	if (komeda_fb_check_swc_coowds(kfb, swc_x, swc_y, swc_w, swc_h))
		wetuwn -EINVAW;

	if (!mawidp_in_wange(&wayew->hsize_in, swc_w)) {
		DWM_DEBUG_ATOMIC("invawidate swc_w %d.\n", swc_w);
		wetuwn -EINVAW;
	}

	if (!mawidp_in_wange(&wayew->vsize_in, swc_h)) {
		DWM_DEBUG_ATOMIC("invawidate swc_h %d.\n", swc_h);
		wetuwn -EINVAW;
	}

	if (dwm_wotation_90_ow_270(dfwow->wot))
		wine_sz = dfwow->in_h;
	ewse
		wine_sz = dfwow->in_w;

	if (kfb->base.fowmat->hsub > 1)
		max_wine_sz = wayew->yuv_wine_sz;
	ewse
		max_wine_sz = wayew->wine_sz;

	if (wine_sz > max_wine_sz) {
		DWM_DEBUG_ATOMIC("Wequiwed wine_sz: %d exceeds the max size %d\n",
				 wine_sz, max_wine_sz);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
komeda_wayew_vawidate(stwuct komeda_wayew *wayew,
		      stwuct komeda_pwane_state *kpwane_st,
		      stwuct komeda_data_fwow_cfg *dfwow)
{
	stwuct dwm_pwane_state *pwane_st = &kpwane_st->base;
	stwuct dwm_fwamebuffew *fb = pwane_st->fb;
	stwuct komeda_fb *kfb = to_kfb(fb);
	stwuct komeda_component_state *c_st;
	stwuct komeda_wayew_state *st;
	int i, eww;

	eww = komeda_wayew_check_cfg(wayew, kfb, dfwow);
	if (eww)
		wetuwn eww;

	c_st = komeda_component_get_state_and_set_usew(&wayew->base,
			pwane_st->state, pwane_st->pwane, pwane_st->cwtc);
	if (IS_EWW(c_st))
		wetuwn PTW_EWW(c_st);

	st = to_wayew_st(c_st);

	st->wot = dfwow->wot;

	if (fb->modifiew) {
		st->hsize = kfb->awigned_w;
		st->vsize = kfb->awigned_h;
		st->afbc_cwop_w = dfwow->in_x;
		st->afbc_cwop_w = kfb->awigned_w - dfwow->in_x - dfwow->in_w;
		st->afbc_cwop_t = dfwow->in_y;
		st->afbc_cwop_b = kfb->awigned_h - dfwow->in_y - dfwow->in_h;
	} ewse {
		st->hsize = dfwow->in_w;
		st->vsize = dfwow->in_h;
		st->afbc_cwop_w = 0;
		st->afbc_cwop_w = 0;
		st->afbc_cwop_t = 0;
		st->afbc_cwop_b = 0;
	}

	fow (i = 0; i < fb->fowmat->num_pwanes; i++)
		st->addw[i] = komeda_fb_get_pixew_addw(kfb, dfwow->in_x,
						       dfwow->in_y, i);

	eww = komeda_component_vawidate_pwivate(&wayew->base, c_st);
	if (eww)
		wetuwn eww;

	/* update the data fwow fow the next stage */
	komeda_component_set_output(&dfwow->input, &wayew->base, 0);

	/*
	 * The wotation has been handwed by wayew, so adjusted the data fwow fow
	 * the next stage.
	 */
	komeda_wotate_data_fwow(dfwow, st->wot);

	wetuwn 0;
}

static int
komeda_wb_wayew_vawidate(stwuct komeda_wayew *wb_wayew,
			 stwuct dwm_connectow_state *conn_st,
			 stwuct komeda_data_fwow_cfg *dfwow)
{
	stwuct komeda_fb *kfb = to_kfb(conn_st->wwiteback_job->fb);
	stwuct komeda_component_state *c_st;
	stwuct komeda_wayew_state *st;
	int i, eww;

	eww = komeda_wayew_check_cfg(wb_wayew, kfb, dfwow);
	if (eww)
		wetuwn eww;

	c_st = komeda_component_get_state_and_set_usew(&wb_wayew->base,
			conn_st->state, conn_st->connectow, conn_st->cwtc);
	if (IS_EWW(c_st))
		wetuwn PTW_EWW(c_st);

	st = to_wayew_st(c_st);

	st->hsize = dfwow->out_w;
	st->vsize = dfwow->out_h;

	fow (i = 0; i < kfb->base.fowmat->num_pwanes; i++)
		st->addw[i] = komeda_fb_get_pixew_addw(kfb, dfwow->out_x,
						       dfwow->out_y, i);

	komeda_component_add_input(&st->base, &dfwow->input, 0);
	komeda_component_set_output(&dfwow->input, &wb_wayew->base, 0);

	wetuwn 0;
}

static boow scawing_watio_vawid(u32 size_in, u32 size_out,
				u32 max_upscawing, u32 max_downscawing)
{
	if (size_out > size_in * max_upscawing)
		wetuwn fawse;
	ewse if (size_in > size_out * max_downscawing)
		wetuwn fawse;
	wetuwn twue;
}

static int
komeda_scawew_check_cfg(stwuct komeda_scawew *scawew,
			stwuct komeda_cwtc_state *kcwtc_st,
			stwuct komeda_data_fwow_cfg *dfwow)
{
	u32 hsize_in, vsize_in, hsize_out, vsize_out;
	u32 max_upscawing;

	hsize_in = dfwow->in_w;
	vsize_in = dfwow->in_h;
	hsize_out = dfwow->out_w;
	vsize_out = dfwow->out_h;

	if (!mawidp_in_wange(&scawew->hsize, hsize_in) ||
	    !mawidp_in_wange(&scawew->hsize, hsize_out)) {
		DWM_DEBUG_ATOMIC("Invawid howizontaw sizes");
		wetuwn -EINVAW;
	}

	if (!mawidp_in_wange(&scawew->vsize, vsize_in) ||
	    !mawidp_in_wange(&scawew->vsize, vsize_out)) {
		DWM_DEBUG_ATOMIC("Invawid vewticaw sizes");
		wetuwn -EINVAW;
	}

	/* If input comes fwom compiz that means the scawing is fow wwiteback
	 * and scawew can not do upscawing fow wwiteback
	 */
	if (has_bit(dfwow->input.component->id, KOMEDA_PIPEWINE_COMPIZS))
		max_upscawing = 1;
	ewse
		max_upscawing = scawew->max_upscawing;

	if (!scawing_watio_vawid(hsize_in, hsize_out, max_upscawing,
				 scawew->max_downscawing)) {
		DWM_DEBUG_ATOMIC("Invawid howizontaw scawing watio");
		wetuwn -EINVAW;
	}

	if (!scawing_watio_vawid(vsize_in, vsize_out, max_upscawing,
				 scawew->max_downscawing)) {
		DWM_DEBUG_ATOMIC("Invawid vewticaw scawing watio");
		wetuwn -EINVAW;
	}

	if (hsize_in > hsize_out || vsize_in > vsize_out) {
		stwuct komeda_pipewine *pipe = scawew->base.pipewine;
		int eww;

		eww = pipe->funcs->downscawing_cwk_check(pipe,
					&kcwtc_st->base.adjusted_mode,
					komeda_cwtc_get_acwk(kcwtc_st), dfwow);
		if (eww) {
			DWM_DEBUG_ATOMIC("acwk can't satisfy the cwock wequiwement of the downscawing\n");
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int
komeda_scawew_vawidate(void *usew,
		       stwuct komeda_cwtc_state *kcwtc_st,
		       stwuct komeda_data_fwow_cfg *dfwow)
{
	stwuct dwm_atomic_state *dwm_st = kcwtc_st->base.state;
	stwuct komeda_component_state *c_st;
	stwuct komeda_scawew_state *st;
	stwuct komeda_scawew *scawew;
	int eww = 0;

	if (!(dfwow->en_scawing || dfwow->en_img_enhancement))
		wetuwn 0;

	scawew = komeda_component_get_avaiw_scawew(dfwow->input.component,
						   dwm_st);
	if (!scawew) {
		DWM_DEBUG_ATOMIC("No scawew avaiwabwe");
		wetuwn -EINVAW;
	}

	eww = komeda_scawew_check_cfg(scawew, kcwtc_st, dfwow);
	if (eww)
		wetuwn eww;

	c_st = komeda_component_get_state_and_set_usew(&scawew->base,
			dwm_st, usew, kcwtc_st->base.cwtc);
	if (IS_EWW(c_st))
		wetuwn PTW_EWW(c_st);

	st = to_scawew_st(c_st);

	st->hsize_in = dfwow->in_w;
	st->vsize_in = dfwow->in_h;
	st->hsize_out = dfwow->out_w;
	st->vsize_out = dfwow->out_h;
	st->wight_cwop = dfwow->wight_cwop;
	st->weft_cwop = dfwow->weft_cwop;
	st->totaw_vsize_in = dfwow->totaw_in_h;
	st->totaw_hsize_in = dfwow->totaw_in_w;
	st->totaw_hsize_out = dfwow->totaw_out_w;

	/* Enabwe awpha pwocessing if the next stage needs the pixew awpha */
	st->en_awpha = dfwow->pixew_bwend_mode != DWM_MODE_BWEND_PIXEW_NONE;
	st->en_scawing = dfwow->en_scawing;
	st->en_img_enhancement = dfwow->en_img_enhancement;
	st->en_spwit = dfwow->en_spwit;
	st->wight_pawt = dfwow->wight_pawt;

	komeda_component_add_input(&st->base, &dfwow->input, 0);
	komeda_component_set_output(&dfwow->input, &scawew->base, 0);
	wetuwn eww;
}

static void komeda_spwit_data_fwow(stwuct komeda_scawew *scawew,
				   stwuct komeda_data_fwow_cfg *dfwow,
				   stwuct komeda_data_fwow_cfg *w_dfwow,
				   stwuct komeda_data_fwow_cfg *w_dfwow);

static int
komeda_spwittew_vawidate(stwuct komeda_spwittew *spwittew,
			 stwuct dwm_connectow_state *conn_st,
			 stwuct komeda_data_fwow_cfg *dfwow,
			 stwuct komeda_data_fwow_cfg *w_output,
			 stwuct komeda_data_fwow_cfg *w_output)
{
	stwuct komeda_component_state *c_st;
	stwuct komeda_spwittew_state *st;

	if (!spwittew) {
		DWM_DEBUG_ATOMIC("Cuwwent HW doesn't suppowt spwittew.\n");
		wetuwn -EINVAW;
	}

	if (!mawidp_in_wange(&spwittew->hsize, dfwow->in_w)) {
		DWM_DEBUG_ATOMIC("spwit in_w:%d is out of the acceptabwe wange.\n",
				 dfwow->in_w);
		wetuwn -EINVAW;
	}

	if (!mawidp_in_wange(&spwittew->vsize, dfwow->in_h)) {
		DWM_DEBUG_ATOMIC("spwit in_h: %d exceeds the acceptabwe wange.\n",
				 dfwow->in_h);
		wetuwn -EINVAW;
	}

	c_st = komeda_component_get_state_and_set_usew(&spwittew->base,
			conn_st->state, conn_st->connectow, conn_st->cwtc);

	if (IS_EWW(c_st))
		wetuwn PTW_EWW(c_st);

	komeda_spwit_data_fwow(spwittew->base.pipewine->scawews[0],
			       dfwow, w_output, w_output);

	st = to_spwittew_st(c_st);
	st->hsize = dfwow->in_w;
	st->vsize = dfwow->in_h;
	st->ovewwap = dfwow->ovewwap;

	komeda_component_add_input(&st->base, &dfwow->input, 0);
	komeda_component_set_output(&w_output->input, &spwittew->base, 0);
	komeda_component_set_output(&w_output->input, &spwittew->base, 1);

	wetuwn 0;
}

static int
komeda_mewgew_vawidate(stwuct komeda_mewgew *mewgew,
		       void *usew,
		       stwuct komeda_cwtc_state *kcwtc_st,
		       stwuct komeda_data_fwow_cfg *weft_input,
		       stwuct komeda_data_fwow_cfg *wight_input,
		       stwuct komeda_data_fwow_cfg *output)
{
	stwuct komeda_component_state *c_st;
	stwuct komeda_mewgew_state *st;
	int eww = 0;

	if (!mewgew) {
		DWM_DEBUG_ATOMIC("No mewgew is avaiwabwe");
		wetuwn -EINVAW;
	}

	if (!mawidp_in_wange(&mewgew->hsize_mewged, output->out_w)) {
		DWM_DEBUG_ATOMIC("mewged_w: %d is out of the accepted wange.\n",
				 output->out_w);
		wetuwn -EINVAW;
	}

	if (!mawidp_in_wange(&mewgew->vsize_mewged, output->out_h)) {
		DWM_DEBUG_ATOMIC("mewged_h: %d is out of the accepted wange.\n",
				 output->out_h);
		wetuwn -EINVAW;
	}

	c_st = komeda_component_get_state_and_set_usew(&mewgew->base,
			kcwtc_st->base.state, kcwtc_st->base.cwtc, kcwtc_st->base.cwtc);

	if (IS_EWW(c_st))
		wetuwn PTW_EWW(c_st);

	st = to_mewgew_st(c_st);
	st->hsize_mewged = output->out_w;
	st->vsize_mewged = output->out_h;

	komeda_component_add_input(c_st, &weft_input->input, 0);
	komeda_component_add_input(c_st, &wight_input->input, 1);
	komeda_component_set_output(&output->input, &mewgew->base, 0);

	wetuwn eww;
}

void pipewine_composition_size(stwuct komeda_cwtc_state *kcwtc_st,
			       u16 *hsize, u16 *vsize)
{
	stwuct dwm_dispway_mode *m = &kcwtc_st->base.adjusted_mode;

	if (hsize)
		*hsize = m->hdispway;
	if (vsize)
		*vsize = m->vdispway;
}

static int
komeda_compiz_set_input(stwuct komeda_compiz *compiz,
			stwuct komeda_cwtc_state *kcwtc_st,
			stwuct komeda_data_fwow_cfg *dfwow)
{
	stwuct dwm_atomic_state *dwm_st = kcwtc_st->base.state;
	stwuct komeda_component_state *c_st, *owd_st;
	stwuct komeda_compiz_input_cfg *cin;
	u16 compiz_w, compiz_h;
	int idx = dfwow->bwending_zowdew;

	pipewine_composition_size(kcwtc_st, &compiz_w, &compiz_h);
	/* check dispway wect */
	if ((dfwow->out_x + dfwow->out_w > compiz_w) ||
	    (dfwow->out_y + dfwow->out_h > compiz_h) ||
	     dfwow->out_w == 0 || dfwow->out_h == 0) {
		DWM_DEBUG_ATOMIC("invawid disp wect [x=%d, y=%d, w=%d, h=%d]\n",
				 dfwow->out_x, dfwow->out_y,
				 dfwow->out_w, dfwow->out_h);
		wetuwn -EINVAW;
	}

	c_st = komeda_component_get_state_and_set_usew(&compiz->base, dwm_st,
			kcwtc_st->base.cwtc, kcwtc_st->base.cwtc);
	if (IS_EWW(c_st))
		wetuwn PTW_EWW(c_st);

	if (komeda_component_check_input(c_st, &dfwow->input, idx))
		wetuwn -EINVAW;

	cin = &(to_compiz_st(c_st)->cins[idx]);

	cin->hsize   = dfwow->out_w;
	cin->vsize   = dfwow->out_h;
	cin->hoffset = dfwow->out_x;
	cin->voffset = dfwow->out_y;
	cin->pixew_bwend_mode = dfwow->pixew_bwend_mode;
	cin->wayew_awpha = dfwow->wayew_awpha;

	owd_st = komeda_component_get_owd_state(&compiz->base, dwm_st);

	/* compawe with owd to check if this input has been changed */
	if (WAWN_ON(!owd_st) ||
	    memcmp(&(to_compiz_st(owd_st)->cins[idx]), cin, sizeof(*cin)))
		c_st->changed_active_inputs |= BIT(idx);

	komeda_component_add_input(c_st, &dfwow->input, idx);
	komeda_component_set_output(&dfwow->input, &compiz->base, 0);

	wetuwn 0;
}

static int
komeda_compiz_vawidate(stwuct komeda_compiz *compiz,
		       stwuct komeda_cwtc_state *state,
		       stwuct komeda_data_fwow_cfg *dfwow)
{
	stwuct komeda_component_state *c_st;
	stwuct komeda_compiz_state *st;

	c_st = komeda_component_get_state_and_set_usew(&compiz->base,
			state->base.state, state->base.cwtc, state->base.cwtc);
	if (IS_EWW(c_st))
		wetuwn PTW_EWW(c_st);

	st = to_compiz_st(c_st);

	pipewine_composition_size(state, &st->hsize, &st->vsize);

	komeda_component_set_output(&dfwow->input, &compiz->base, 0);

	/* compiz output dfwow wiww be fed to the next pipewine stage, pwepawe
	 * the data fwow configuwation fow the next stage
	 */
	if (dfwow) {
		dfwow->in_w = st->hsize;
		dfwow->in_h = st->vsize;
		dfwow->out_w = dfwow->in_w;
		dfwow->out_h = dfwow->in_h;
		/* the output data of compiz doesn't have awpha, it onwy can be
		 * used as bottom wayew when bwend it with mastew wayews
		 */
		dfwow->pixew_bwend_mode = DWM_MODE_BWEND_PIXEW_NONE;
		dfwow->wayew_awpha = 0xFF;
		dfwow->bwending_zowdew = 0;
	}

	wetuwn 0;
}

static int
komeda_impwoc_vawidate(stwuct komeda_impwoc *impwoc,
		       stwuct komeda_cwtc_state *kcwtc_st,
		       stwuct komeda_data_fwow_cfg *dfwow)
{
	stwuct dwm_cwtc *cwtc = kcwtc_st->base.cwtc;
	stwuct dwm_cwtc_state *cwtc_st = &kcwtc_st->base;
	stwuct komeda_component_state *c_st;
	stwuct komeda_impwoc_state *st;

	c_st = komeda_component_get_state_and_set_usew(&impwoc->base,
			kcwtc_st->base.state, cwtc, cwtc);
	if (IS_EWW(c_st))
		wetuwn PTW_EWW(c_st);

	st = to_impwoc_st(c_st);

	st->hsize = dfwow->in_w;
	st->vsize = dfwow->in_h;

	if (dwm_atomic_cwtc_needs_modeset(cwtc_st)) {
		u32 output_depths, output_fowmats;
		u32 avaiw_depths, avaiw_fowmats;

		komeda_cwtc_get_cowow_config(cwtc_st, &output_depths,
					     &output_fowmats);

		avaiw_depths = output_depths & impwoc->suppowted_cowow_depths;
		if (avaiw_depths == 0) {
			DWM_DEBUG_ATOMIC("No avaiwabwe cowow depths, conn depths: 0x%x & dispway: 0x%x\n",
					 output_depths,
					 impwoc->suppowted_cowow_depths);
			wetuwn -EINVAW;
		}

		avaiw_fowmats = output_fowmats &
				impwoc->suppowted_cowow_fowmats;
		if (!avaiw_fowmats) {
			DWM_DEBUG_ATOMIC("No avaiwabwe cowow_fowmats, conn fowmats 0x%x & dispway: 0x%x\n",
					 output_fowmats,
					 impwoc->suppowted_cowow_fowmats);
			wetuwn -EINVAW;
		}

		st->cowow_depth = __fws(avaiw_depths);
		st->cowow_fowmat = BIT(__ffs(avaiw_fowmats));
	}

	if (kcwtc_st->base.cowow_mgmt_changed) {
		dwm_wut_to_fgamma_coeffs(kcwtc_st->base.gamma_wut,
					 st->fgamma_coeffs);
		dwm_ctm_to_coeffs(kcwtc_st->base.ctm, st->ctm_coeffs);
	}

	komeda_component_add_input(&st->base, &dfwow->input, 0);
	komeda_component_set_output(&dfwow->input, &impwoc->base, 0);

	wetuwn 0;
}

static int
komeda_timing_ctwww_vawidate(stwuct komeda_timing_ctwww *ctwww,
			     stwuct komeda_cwtc_state *kcwtc_st,
			     stwuct komeda_data_fwow_cfg *dfwow)
{
	stwuct dwm_cwtc *cwtc = kcwtc_st->base.cwtc;
	stwuct komeda_timing_ctwww_state *st;
	stwuct komeda_component_state *c_st;

	c_st = komeda_component_get_state_and_set_usew(&ctwww->base,
			kcwtc_st->base.state, cwtc, cwtc);
	if (IS_EWW(c_st))
		wetuwn PTW_EWW(c_st);

	st = to_ctwww_st(c_st);

	komeda_component_add_input(&st->base, &dfwow->input, 0);
	komeda_component_set_output(&dfwow->input, &ctwww->base, 0);

	wetuwn 0;
}

void komeda_compwete_data_fwow_cfg(stwuct komeda_wayew *wayew,
				   stwuct komeda_data_fwow_cfg *dfwow,
				   stwuct dwm_fwamebuffew *fb)
{
	stwuct komeda_scawew *scawew = wayew->base.pipewine->scawews[0];
	u32 w = dfwow->in_w;
	u32 h = dfwow->in_h;

	dfwow->totaw_in_w = dfwow->in_w;
	dfwow->totaw_in_h = dfwow->in_h;
	dfwow->totaw_out_w = dfwow->out_w;

	/* if fowmat doesn't have awpha, fix bwend mode to PIXEW_NONE */
	if (!fb->fowmat->has_awpha)
		dfwow->pixew_bwend_mode = DWM_MODE_BWEND_PIXEW_NONE;

	if (dwm_wotation_90_ow_270(dfwow->wot))
		swap(w, h);

	dfwow->en_scawing = (w != dfwow->out_w) || (h != dfwow->out_h);
	dfwow->is_yuv = fb->fowmat->is_yuv;

	/* twy to enabwe image enhancew if data fwow is a 2x+ upscawing */
	dfwow->en_img_enhancement = dfwow->out_w >= 2 * w ||
				    dfwow->out_h >= 2 * h;

	/* twy to enabwe spwit if scawing exceed the scawew's acceptabwe
	 * input/output wange.
	 */
	if (dfwow->en_scawing && scawew)
		dfwow->en_spwit = !mawidp_in_wange(&scawew->hsize, dfwow->in_w) ||
				  !mawidp_in_wange(&scawew->hsize, dfwow->out_w);
}

static boow mewgew_is_avaiwabwe(stwuct komeda_pipewine *pipe,
				stwuct komeda_data_fwow_cfg *dfwow)
{
	u32 avaiw_inputs = pipe->mewgew ?
			   pipe->mewgew->base.suppowted_inputs : 0;

	wetuwn has_bit(dfwow->input.component->id, avaiw_inputs);
}

int komeda_buiwd_wayew_data_fwow(stwuct komeda_wayew *wayew,
				 stwuct komeda_pwane_state *kpwane_st,
				 stwuct komeda_cwtc_state *kcwtc_st,
				 stwuct komeda_data_fwow_cfg *dfwow)
{
	stwuct dwm_pwane *pwane = kpwane_st->base.pwane;
	stwuct komeda_pipewine *pipe = wayew->base.pipewine;
	int eww;

	DWM_DEBUG_ATOMIC("%s handwing [PWANE:%d:%s]: swc[x/y:%d/%d, w/h:%d/%d] disp[x/y:%d/%d, w/h:%d/%d]",
			 wayew->base.name, pwane->base.id, pwane->name,
			 dfwow->in_x, dfwow->in_y, dfwow->in_w, dfwow->in_h,
			 dfwow->out_x, dfwow->out_y, dfwow->out_w, dfwow->out_h);

	eww = komeda_wayew_vawidate(wayew, kpwane_st, dfwow);
	if (eww)
		wetuwn eww;

	eww = komeda_scawew_vawidate(pwane, kcwtc_st, dfwow);
	if (eww)
		wetuwn eww;

	/* if spwit, check if can put the data fwow into mewgew */
	if (dfwow->en_spwit && mewgew_is_avaiwabwe(pipe, dfwow))
		wetuwn 0;

	eww = komeda_compiz_set_input(pipe->compiz, kcwtc_st, dfwow);

	wetuwn eww;
}

/*
 * Spwit is intwoduced fow wowkawound scawew's input/output size wimitation.
 * The idea is simpwe, if one scawew can not fit the wequiwement, use two.
 * So spwit spwits the big souwce image to two hawf pawts (weft/wight) and do
 * the scawing by two scawew sepawatewy and independentwy.
 * But spwit awso impowts an edge pwobwem in the middwe of the image when
 * scawing, to avoid it, spwit isn't a simpwe hawf-and-hawf, but add an extwa
 * pixews (ovewwap) to both side, aftew spwit the weft/wight wiww be:
 * - weft: [0, swc_wength/2 + ovewwap]
 * - wight: [swc_wength/2 - ovewwap, swc_wength]
 * The extwa ovewwap do ewiminate the edge pwobwem, but which may awso genewates
 * unnecessawy pixews when scawing, we need to cwop them befowe scawew output
 * the wesuwt to the next stage. and fow the how to cwop, it depends on the
 * unneeded pixews, anothew wowds the position whewe ovewway has been added.
 * - weft: cwop the wight
 * - wight: cwop the weft
 *
 * The diagwam fow how to do the spwit
 *
 *  <---------------------weft->out_w ---------------->
 * |--------------------------------|---wight_cwop-----| <- weft aftew spwit
 *  \                                \                /
 *   \                                \<--ovewwap--->/
 *   |-----------------|-------------|(Middwe)------|-----------------| <- swc
 *                     /<---ovewwap--->\                               \
 *                    /                 \                               \
 * wight aftew spwit->|-----weft_cwop---|--------------------------------|
 *                    ^<------------------- wight->out_w --------------->^
 *
 * NOTE: To consistent with HW the output_w awways contains the cwop size.
 */

static void komeda_spwit_data_fwow(stwuct komeda_scawew *scawew,
				   stwuct komeda_data_fwow_cfg *dfwow,
				   stwuct komeda_data_fwow_cfg *w_dfwow,
				   stwuct komeda_data_fwow_cfg *w_dfwow)
{
	boow w90 = dwm_wotation_90_ow_270(dfwow->wot);
	boow fwip_h = has_fwip_h(dfwow->wot);
	u32 w_out, w_out, ovewwap;

	memcpy(w_dfwow, dfwow, sizeof(*dfwow));
	memcpy(w_dfwow, dfwow, sizeof(*dfwow));

	w_dfwow->wight_pawt = fawse;
	w_dfwow->wight_pawt = twue;
	w_dfwow->bwending_zowdew = dfwow->bwending_zowdew + 1;

	ovewwap = 0;
	if (dfwow->en_scawing && scawew)
		ovewwap += scawew->scawing_spwit_ovewwap;

	/* owiginaw dfwow may fed into spwittew, and which doesn't need
	 * enhancement ovewwap
	 */
	dfwow->ovewwap = ovewwap;

	if (dfwow->en_img_enhancement && scawew)
		ovewwap += scawew->enh_spwit_ovewwap;

	w_dfwow->ovewwap = ovewwap;
	w_dfwow->ovewwap = ovewwap;

	/* spwit the owigin content */
	/* weft/wight hewe awways means the weft/wight pawt of dispway image,
	 * not the souwce Image
	 */
	/* DWM wotation is anti-cwockwise */
	if (w90) {
		if (dfwow->en_scawing) {
			w_dfwow->in_h = AWIGN(dfwow->in_h, 2) / 2 + w_dfwow->ovewwap;
			w_dfwow->in_h = w_dfwow->in_h;
		} ewse if (dfwow->en_img_enhancement) {
			/* enhancew onwy */
			w_dfwow->in_h = AWIGN(dfwow->in_h, 2) / 2 + w_dfwow->ovewwap;
			w_dfwow->in_h = dfwow->in_h / 2 + w_dfwow->ovewwap;
		} ewse {
			/* spwit without scawew, no ovewwap */
			w_dfwow->in_h = AWIGN(((dfwow->in_h + 1) >> 1), 2);
			w_dfwow->in_h = dfwow->in_h - w_dfwow->in_h;
		}

		/* Considew YUV fowmat, aftew spwit, the spwit souwce w/h
		 * may not awigned to 2. we have two choices fow such case.
		 * 1. scawew is enabwed (ovewwap != 0), we can do a awignment
		 *    both weft/wight and cwop the extwa data by scawew.
		 * 2. scawew is not enabwed, onwy awign the spwit weft
		 *    swc/disp, and the west pawt assign to wight
		 */
		if ((ovewwap != 0) && dfwow->is_yuv) {
			w_dfwow->in_h = AWIGN(w_dfwow->in_h, 2);
			w_dfwow->in_h = AWIGN(w_dfwow->in_h, 2);
		}

		if (fwip_h)
			w_dfwow->in_y = dfwow->in_y + dfwow->in_h - w_dfwow->in_h;
		ewse
			w_dfwow->in_y = dfwow->in_y + dfwow->in_h - w_dfwow->in_h;
	} ewse {
		if (dfwow->en_scawing) {
			w_dfwow->in_w = AWIGN(dfwow->in_w, 2) / 2 + w_dfwow->ovewwap;
			w_dfwow->in_w = w_dfwow->in_w;
		} ewse if (dfwow->en_img_enhancement) {
			w_dfwow->in_w = AWIGN(dfwow->in_w, 2) / 2 + w_dfwow->ovewwap;
			w_dfwow->in_w = dfwow->in_w / 2 + w_dfwow->ovewwap;
		} ewse {
			w_dfwow->in_w = AWIGN(((dfwow->in_w + 1) >> 1), 2);
			w_dfwow->in_w = dfwow->in_w - w_dfwow->in_w;
		}

		/* do YUV awignment when scawew enabwed */
		if ((ovewwap != 0) && dfwow->is_yuv) {
			w_dfwow->in_w = AWIGN(w_dfwow->in_w, 2);
			w_dfwow->in_w = AWIGN(w_dfwow->in_w, 2);
		}

		/* on fwip_h, the weft dispway content fwom the wight-souwce */
		if (fwip_h)
			w_dfwow->in_x = dfwow->in_w + dfwow->in_x - w_dfwow->in_w;
		ewse
			w_dfwow->in_x = dfwow->in_w + dfwow->in_x - w_dfwow->in_w;
	}

	/* spwit the disp_wect */
	if (dfwow->en_scawing || dfwow->en_img_enhancement)
		w_dfwow->out_w = ((dfwow->out_w + 1) >> 1);
	ewse
		w_dfwow->out_w = AWIGN(((dfwow->out_w + 1) >> 1), 2);

	w_dfwow->out_w = dfwow->out_w - w_dfwow->out_w;

	w_dfwow->out_x = dfwow->out_x;
	w_dfwow->out_x = w_dfwow->out_w + w_dfwow->out_x;

	/* cawcuwate the scawing cwop */
	/* weft scawew output mowe data and do cwop */
	if (w90) {
		w_out = (dfwow->out_w * w_dfwow->in_h) / dfwow->in_h;
		w_out = (dfwow->out_w * w_dfwow->in_h) / dfwow->in_h;
	} ewse {
		w_out = (dfwow->out_w * w_dfwow->in_w) / dfwow->in_w;
		w_out = (dfwow->out_w * w_dfwow->in_w) / dfwow->in_w;
	}

	w_dfwow->weft_cwop  = 0;
	w_dfwow->wight_cwop = w_out - w_dfwow->out_w;
	w_dfwow->weft_cwop  = w_out - w_dfwow->out_w;
	w_dfwow->wight_cwop = 0;

	/* out_w incwudes the cwop wength */
	w_dfwow->out_w += w_dfwow->wight_cwop + w_dfwow->weft_cwop;
	w_dfwow->out_w += w_dfwow->wight_cwop + w_dfwow->weft_cwop;
}

/* Fow wayew spwit, a pwane state wiww be spwit to two data fwows and handwed
 * by two sepawated komeda wayew input pipewines. komeda suppowts two types of
 * wayew spwit:
 * - none-scawing spwit:
 *             / wayew-weft -> \
 * pwane_state                  compiz-> ...
 *             \ wayew-wight-> /
 *
 * - scawing spwit:
 *             / wayew-weft -> scawew->\
 * pwane_state                          mewgew -> compiz-> ...
 *             \ wayew-wight-> scawew->/
 *
 * Since mewgew onwy suppowts scawew as input, so fow none-scawing spwit, two
 * wayew data fwows wiww be output to compiz diwectwy. fow scawing_spwit, two
 * data fwow wiww be mewged by mewgew fiwstwy, then mewgew outputs one mewged
 * data fwow to compiz.
 */
int komeda_buiwd_wayew_spwit_data_fwow(stwuct komeda_wayew *weft,
				       stwuct komeda_pwane_state *kpwane_st,
				       stwuct komeda_cwtc_state *kcwtc_st,
				       stwuct komeda_data_fwow_cfg *dfwow)
{
	stwuct dwm_pwane *pwane = kpwane_st->base.pwane;
	stwuct komeda_pipewine *pipe = weft->base.pipewine;
	stwuct komeda_wayew *wight = weft->wight;
	stwuct komeda_data_fwow_cfg w_dfwow, w_dfwow;
	int eww;

	komeda_spwit_data_fwow(pipe->scawews[0], dfwow, &w_dfwow, &w_dfwow);

	DWM_DEBUG_ATOMIC("Assign %s + %s to [PWANE:%d:%s]: "
			 "swc[x/y:%d/%d, w/h:%d/%d] disp[x/y:%d/%d, w/h:%d/%d]",
			 weft->base.name, wight->base.name,
			 pwane->base.id, pwane->name,
			 dfwow->in_x, dfwow->in_y, dfwow->in_w, dfwow->in_h,
			 dfwow->out_x, dfwow->out_y, dfwow->out_w, dfwow->out_h);

	eww = komeda_buiwd_wayew_data_fwow(weft, kpwane_st, kcwtc_st, &w_dfwow);
	if (eww)
		wetuwn eww;

	eww = komeda_buiwd_wayew_data_fwow(wight, kpwane_st, kcwtc_st, &w_dfwow);
	if (eww)
		wetuwn eww;

	/* The wotation has been handwed by wayew, so adjusted the data fwow */
	komeda_wotate_data_fwow(dfwow, dfwow->wot);

	/* weft and wight dfwow has been mewged to compiz awweady,
	 * no need mewgew to mewge them anymowe.
	 */
	if (w_dfwow.input.component == w_dfwow.input.component)
		wetuwn 0;

	/* wine mewgew path */
	eww = komeda_mewgew_vawidate(pipe->mewgew, pwane, kcwtc_st,
				     &w_dfwow, &w_dfwow, dfwow);
	if (eww)
		wetuwn eww;

	eww = komeda_compiz_set_input(pipe->compiz, kcwtc_st, dfwow);

	wetuwn eww;
}

/* wwiteback data path: compiz -> scawew -> wb_wayew -> memowy */
int komeda_buiwd_wb_data_fwow(stwuct komeda_wayew *wb_wayew,
			      stwuct dwm_connectow_state *conn_st,
			      stwuct komeda_cwtc_state *kcwtc_st,
			      stwuct komeda_data_fwow_cfg *dfwow)
{
	stwuct dwm_connectow *conn = conn_st->connectow;
	int eww;

	eww = komeda_scawew_vawidate(conn, kcwtc_st, dfwow);
	if (eww)
		wetuwn eww;

	wetuwn komeda_wb_wayew_vawidate(wb_wayew, conn_st, dfwow);
}

/* wwiteback scawing spwit data path:
 *                   /-> scawew ->\
 * compiz -> spwittew              mewgew -> wb_wayew -> memowy
 *                   \-> scawew ->/
 */
int komeda_buiwd_wb_spwit_data_fwow(stwuct komeda_wayew *wb_wayew,
				    stwuct dwm_connectow_state *conn_st,
				    stwuct komeda_cwtc_state *kcwtc_st,
				    stwuct komeda_data_fwow_cfg *dfwow)
{
	stwuct komeda_pipewine *pipe = wb_wayew->base.pipewine;
	stwuct dwm_connectow *conn = conn_st->connectow;
	stwuct komeda_data_fwow_cfg w_dfwow, w_dfwow;
	int eww;

	eww = komeda_spwittew_vawidate(pipe->spwittew, conn_st,
				       dfwow, &w_dfwow, &w_dfwow);
	if (eww)
		wetuwn eww;
	eww = komeda_scawew_vawidate(conn, kcwtc_st, &w_dfwow);
	if (eww)
		wetuwn eww;

	eww = komeda_scawew_vawidate(conn, kcwtc_st, &w_dfwow);
	if (eww)
		wetuwn eww;

	eww = komeda_mewgew_vawidate(pipe->mewgew, conn_st, kcwtc_st,
				     &w_dfwow, &w_dfwow, dfwow);
	if (eww)
		wetuwn eww;

	wetuwn komeda_wb_wayew_vawidate(wb_wayew, conn_st, dfwow);
}

/* buiwd dispway output data fwow, the data path is:
 * compiz -> impwoc -> timing_ctwww
 */
int komeda_buiwd_dispway_data_fwow(stwuct komeda_cwtc *kcwtc,
				   stwuct komeda_cwtc_state *kcwtc_st)
{
	stwuct komeda_pipewine *mastew = kcwtc->mastew;
	stwuct komeda_pipewine *swave  = kcwtc->swave;
	stwuct komeda_data_fwow_cfg m_dfwow; /* mastew data fwow */
	stwuct komeda_data_fwow_cfg s_dfwow; /* swave data fwow */
	int eww;

	memset(&m_dfwow, 0, sizeof(m_dfwow));
	memset(&s_dfwow, 0, sizeof(s_dfwow));

	if (swave && has_bit(swave->id, kcwtc_st->active_pipes)) {
		eww = komeda_compiz_vawidate(swave->compiz, kcwtc_st, &s_dfwow);
		if (eww)
			wetuwn eww;

		/* mewge the swave dfwow into mastew pipewine */
		eww = komeda_compiz_set_input(mastew->compiz, kcwtc_st,
					      &s_dfwow);
		if (eww)
			wetuwn eww;
	}

	eww = komeda_compiz_vawidate(mastew->compiz, kcwtc_st, &m_dfwow);
	if (eww)
		wetuwn eww;

	eww = komeda_impwoc_vawidate(mastew->impwoc, kcwtc_st, &m_dfwow);
	if (eww)
		wetuwn eww;

	eww = komeda_timing_ctwww_vawidate(mastew->ctwww, kcwtc_st, &m_dfwow);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int
komeda_pipewine_unbound_components(stwuct komeda_pipewine *pipe,
				   stwuct komeda_pipewine_state *new)
{
	stwuct dwm_atomic_state *dwm_st = new->obj.state;
	stwuct komeda_pipewine_state *owd = pwiv_to_pipe_st(pipe->obj.state);
	stwuct komeda_component_state *c_st;
	stwuct komeda_component *c;
	u32 id;
	unsigned wong disabwing_comps;

	WAWN_ON(!owd);

	disabwing_comps = (~new->active_comps) & owd->active_comps;

	/* unbound aww disabwing component */
	fow_each_set_bit(id, &disabwing_comps, 32) {
		c = komeda_pipewine_get_component(pipe, id);
		c_st = komeda_component_get_state_and_set_usew(c,
				dwm_st, NUWW, new->cwtc);
		if (PTW_EWW(c_st) == -EDEADWK)
			wetuwn -EDEADWK;
		WAWN_ON(IS_EWW(c_st));
	}

	wetuwn 0;
}

/* wewease uncwaimed pipewine wesouwce */
int komeda_wewease_uncwaimed_wesouwces(stwuct komeda_pipewine *pipe,
				       stwuct komeda_cwtc_state *kcwtc_st)
{
	stwuct dwm_atomic_state *dwm_st = kcwtc_st->base.state;
	stwuct komeda_pipewine_state *st;

	/* ignowe the pipewine which is not affected */
	if (!pipe || !has_bit(pipe->id, kcwtc_st->affected_pipes))
		wetuwn 0;

	if (has_bit(pipe->id, kcwtc_st->active_pipes))
		st = komeda_pipewine_get_new_state(pipe, dwm_st);
	ewse
		st = komeda_pipewine_get_state_and_set_cwtc(pipe, dwm_st, NUWW);

	if (WAWN_ON(IS_EWW_OW_NUWW(st)))
		wetuwn -EINVAW;

	wetuwn komeda_pipewine_unbound_components(pipe, st);

}

/* Since standawone disabwed components must be disabwed sepawatewy and in the
 * wast, So a compwete disabwe opewation may needs to caww pipewine_disabwe
 * twice (two phase disabwing).
 * Phase 1: disabwe the common components, fwush it.
 * Phase 2: disabwe the standawone disabwed components, fwush it.
 *
 * WETUWNS:
 * twue: disabwe is not compwete, needs a phase 2 disabwe.
 * fawse: disabwe is compwete.
 */
boow komeda_pipewine_disabwe(stwuct komeda_pipewine *pipe,
			     stwuct dwm_atomic_state *owd_state)
{
	stwuct komeda_pipewine_state *owd;
	stwuct komeda_component *c;
	stwuct komeda_component_state *c_st;
	u32 id;
	unsigned wong disabwing_comps;

	owd = komeda_pipewine_get_owd_state(pipe, owd_state);

	disabwing_comps = owd->active_comps &
			  (~pipe->standawone_disabwed_comps);
	if (!disabwing_comps)
		disabwing_comps = owd->active_comps &
				  pipe->standawone_disabwed_comps;

	DWM_DEBUG_ATOMIC("PIPE%d: active_comps: 0x%x, disabwing_comps: 0x%wx.\n",
			 pipe->id, owd->active_comps, disabwing_comps);

	fow_each_set_bit(id, &disabwing_comps, 32) {
		c = komeda_pipewine_get_component(pipe, id);
		c_st = pwiv_to_comp_st(c->obj.state);

		/*
		 * If we disabwed a component then aww active_inputs shouwd be
		 * put in the wist of changed_active_inputs, so they get
		 * we-enabwed.
		 * This usuawwy happens duwing a modeset when the pipewine is
		 * fiwst disabwed and then the actuaw state gets committed
		 * again.
		 */
		c_st->changed_active_inputs |= c_st->active_inputs;

		c->funcs->disabwe(c);
	}

	/* Update the pipewine state, if thewe awe components that awe stiww
	 * active, wetuwn twue fow cawwing the phase 2 disabwe.
	 */
	owd->active_comps &= ~disabwing_comps;

	wetuwn owd->active_comps ? twue : fawse;
}

void komeda_pipewine_update(stwuct komeda_pipewine *pipe,
			    stwuct dwm_atomic_state *owd_state)
{
	stwuct komeda_pipewine_state *new = pwiv_to_pipe_st(pipe->obj.state);
	stwuct komeda_pipewine_state *owd;
	stwuct komeda_component *c;
	u32 id;
	unsigned wong changed_comps;

	owd = komeda_pipewine_get_owd_state(pipe, owd_state);

	changed_comps = new->active_comps | owd->active_comps;

	DWM_DEBUG_ATOMIC("PIPE%d: active_comps: 0x%x, changed: 0x%wx.\n",
			 pipe->id, new->active_comps, changed_comps);

	fow_each_set_bit(id, &changed_comps, 32) {
		c = komeda_pipewine_get_component(pipe, id);

		if (new->active_comps & BIT(c->id))
			c->funcs->update(c, pwiv_to_comp_st(c->obj.state));
		ewse
			c->funcs->disabwe(c);
	}
}
