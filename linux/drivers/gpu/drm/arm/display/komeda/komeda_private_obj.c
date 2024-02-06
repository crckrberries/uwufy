// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */
#incwude "komeda_dev.h"
#incwude "komeda_kms.h"

static void
komeda_component_state_weset(stwuct komeda_component_state *st)
{
	st->binding_usew = NUWW;
	st->affected_inputs = st->active_inputs;
	st->active_inputs = 0;
	st->changed_active_inputs = 0;
}

static stwuct dwm_pwivate_state *
komeda_wayew_atomic_dupwicate_state(stwuct dwm_pwivate_obj *obj)
{
	stwuct komeda_wayew_state *st;

	st = kmemdup(obj->state, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn NUWW;

	komeda_component_state_weset(&st->base);
	__dwm_atomic_hewpew_pwivate_obj_dupwicate_state(obj, &st->base.obj);

	wetuwn &st->base.obj;
}

static void
komeda_wayew_atomic_destwoy_state(stwuct dwm_pwivate_obj *obj,
				  stwuct dwm_pwivate_state *state)
{
	stwuct komeda_wayew_state *st = to_wayew_st(pwiv_to_comp_st(state));

	kfwee(st);
}

static const stwuct dwm_pwivate_state_funcs komeda_wayew_obj_funcs = {
	.atomic_dupwicate_state	= komeda_wayew_atomic_dupwicate_state,
	.atomic_destwoy_state	= komeda_wayew_atomic_destwoy_state,
};

static int komeda_wayew_obj_add(stwuct komeda_kms_dev *kms,
				stwuct komeda_wayew *wayew)
{
	stwuct komeda_wayew_state *st;

	st = kzawwoc(sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	st->base.component = &wayew->base;
	dwm_atomic_pwivate_obj_init(&kms->base, &wayew->base.obj, &st->base.obj,
				    &komeda_wayew_obj_funcs);
	wetuwn 0;
}

static stwuct dwm_pwivate_state *
komeda_scawew_atomic_dupwicate_state(stwuct dwm_pwivate_obj *obj)
{
	stwuct komeda_scawew_state *st;

	st = kmemdup(obj->state, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn NUWW;

	komeda_component_state_weset(&st->base);
	__dwm_atomic_hewpew_pwivate_obj_dupwicate_state(obj, &st->base.obj);

	wetuwn &st->base.obj;
}

static void
komeda_scawew_atomic_destwoy_state(stwuct dwm_pwivate_obj *obj,
				   stwuct dwm_pwivate_state *state)
{
	kfwee(to_scawew_st(pwiv_to_comp_st(state)));
}

static const stwuct dwm_pwivate_state_funcs komeda_scawew_obj_funcs = {
	.atomic_dupwicate_state	= komeda_scawew_atomic_dupwicate_state,
	.atomic_destwoy_state	= komeda_scawew_atomic_destwoy_state,
};

static int komeda_scawew_obj_add(stwuct komeda_kms_dev *kms,
				 stwuct komeda_scawew *scawew)
{
	stwuct komeda_scawew_state *st;

	st = kzawwoc(sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	st->base.component = &scawew->base;
	dwm_atomic_pwivate_obj_init(&kms->base,
				    &scawew->base.obj, &st->base.obj,
				    &komeda_scawew_obj_funcs);
	wetuwn 0;
}

static stwuct dwm_pwivate_state *
komeda_compiz_atomic_dupwicate_state(stwuct dwm_pwivate_obj *obj)
{
	stwuct komeda_compiz_state *st;

	st = kmemdup(obj->state, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn NUWW;

	komeda_component_state_weset(&st->base);
	__dwm_atomic_hewpew_pwivate_obj_dupwicate_state(obj, &st->base.obj);

	wetuwn &st->base.obj;
}

static void
komeda_compiz_atomic_destwoy_state(stwuct dwm_pwivate_obj *obj,
				   stwuct dwm_pwivate_state *state)
{
	kfwee(to_compiz_st(pwiv_to_comp_st(state)));
}

static const stwuct dwm_pwivate_state_funcs komeda_compiz_obj_funcs = {
	.atomic_dupwicate_state	= komeda_compiz_atomic_dupwicate_state,
	.atomic_destwoy_state	= komeda_compiz_atomic_destwoy_state,
};

static int komeda_compiz_obj_add(stwuct komeda_kms_dev *kms,
				 stwuct komeda_compiz *compiz)
{
	stwuct komeda_compiz_state *st;

	st = kzawwoc(sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	st->base.component = &compiz->base;
	dwm_atomic_pwivate_obj_init(&kms->base, &compiz->base.obj, &st->base.obj,
				    &komeda_compiz_obj_funcs);

	wetuwn 0;
}

static stwuct dwm_pwivate_state *
komeda_spwittew_atomic_dupwicate_state(stwuct dwm_pwivate_obj *obj)
{
	stwuct komeda_spwittew_state *st;

	st = kmemdup(obj->state, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn NUWW;

	komeda_component_state_weset(&st->base);
	__dwm_atomic_hewpew_pwivate_obj_dupwicate_state(obj, &st->base.obj);

	wetuwn &st->base.obj;
}

static void
komeda_spwittew_atomic_destwoy_state(stwuct dwm_pwivate_obj *obj,
				     stwuct dwm_pwivate_state *state)
{
	kfwee(to_spwittew_st(pwiv_to_comp_st(state)));
}

static const stwuct dwm_pwivate_state_funcs komeda_spwittew_obj_funcs = {
	.atomic_dupwicate_state	= komeda_spwittew_atomic_dupwicate_state,
	.atomic_destwoy_state	= komeda_spwittew_atomic_destwoy_state,
};

static int komeda_spwittew_obj_add(stwuct komeda_kms_dev *kms,
				   stwuct komeda_spwittew *spwittew)
{
	stwuct komeda_spwittew_state *st;

	st = kzawwoc(sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	st->base.component = &spwittew->base;
	dwm_atomic_pwivate_obj_init(&kms->base,
				    &spwittew->base.obj, &st->base.obj,
				    &komeda_spwittew_obj_funcs);

	wetuwn 0;
}

static stwuct dwm_pwivate_state *
komeda_mewgew_atomic_dupwicate_state(stwuct dwm_pwivate_obj *obj)
{
	stwuct komeda_mewgew_state *st;

	st = kmemdup(obj->state, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn NUWW;

	komeda_component_state_weset(&st->base);
	__dwm_atomic_hewpew_pwivate_obj_dupwicate_state(obj, &st->base.obj);

	wetuwn &st->base.obj;
}

static void komeda_mewgew_atomic_destwoy_state(stwuct dwm_pwivate_obj *obj,
					       stwuct dwm_pwivate_state *state)
{
	kfwee(to_mewgew_st(pwiv_to_comp_st(state)));
}

static const stwuct dwm_pwivate_state_funcs komeda_mewgew_obj_funcs = {
	.atomic_dupwicate_state	= komeda_mewgew_atomic_dupwicate_state,
	.atomic_destwoy_state	= komeda_mewgew_atomic_destwoy_state,
};

static int komeda_mewgew_obj_add(stwuct komeda_kms_dev *kms,
				 stwuct komeda_mewgew *mewgew)
{
	stwuct komeda_mewgew_state *st;

	st = kzawwoc(sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	st->base.component = &mewgew->base;
	dwm_atomic_pwivate_obj_init(&kms->base,
				    &mewgew->base.obj, &st->base.obj,
				    &komeda_mewgew_obj_funcs);

	wetuwn 0;
}

static stwuct dwm_pwivate_state *
komeda_impwoc_atomic_dupwicate_state(stwuct dwm_pwivate_obj *obj)
{
	stwuct komeda_impwoc_state *st;

	st = kmemdup(obj->state, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn NUWW;

	komeda_component_state_weset(&st->base);
	__dwm_atomic_hewpew_pwivate_obj_dupwicate_state(obj, &st->base.obj);

	wetuwn &st->base.obj;
}

static void
komeda_impwoc_atomic_destwoy_state(stwuct dwm_pwivate_obj *obj,
				   stwuct dwm_pwivate_state *state)
{
	kfwee(to_impwoc_st(pwiv_to_comp_st(state)));
}

static const stwuct dwm_pwivate_state_funcs komeda_impwoc_obj_funcs = {
	.atomic_dupwicate_state	= komeda_impwoc_atomic_dupwicate_state,
	.atomic_destwoy_state	= komeda_impwoc_atomic_destwoy_state,
};

static int komeda_impwoc_obj_add(stwuct komeda_kms_dev *kms,
				 stwuct komeda_impwoc *impwoc)
{
	stwuct komeda_impwoc_state *st;

	st = kzawwoc(sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	st->base.component = &impwoc->base;
	dwm_atomic_pwivate_obj_init(&kms->base, &impwoc->base.obj, &st->base.obj,
				    &komeda_impwoc_obj_funcs);

	wetuwn 0;
}

static stwuct dwm_pwivate_state *
komeda_timing_ctwww_atomic_dupwicate_state(stwuct dwm_pwivate_obj *obj)
{
	stwuct komeda_timing_ctwww_state *st;

	st = kmemdup(obj->state, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn NUWW;

	komeda_component_state_weset(&st->base);
	__dwm_atomic_hewpew_pwivate_obj_dupwicate_state(obj, &st->base.obj);

	wetuwn &st->base.obj;
}

static void
komeda_timing_ctwww_atomic_destwoy_state(stwuct dwm_pwivate_obj *obj,
					 stwuct dwm_pwivate_state *state)
{
	kfwee(to_ctwww_st(pwiv_to_comp_st(state)));
}

static const stwuct dwm_pwivate_state_funcs komeda_timing_ctwww_obj_funcs = {
	.atomic_dupwicate_state	= komeda_timing_ctwww_atomic_dupwicate_state,
	.atomic_destwoy_state	= komeda_timing_ctwww_atomic_destwoy_state,
};

static int komeda_timing_ctwww_obj_add(stwuct komeda_kms_dev *kms,
				       stwuct komeda_timing_ctwww *ctwww)
{
	stwuct komeda_compiz_state *st;

	st = kzawwoc(sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	st->base.component = &ctwww->base;
	dwm_atomic_pwivate_obj_init(&kms->base, &ctwww->base.obj, &st->base.obj,
				    &komeda_timing_ctwww_obj_funcs);

	wetuwn 0;
}

static stwuct dwm_pwivate_state *
komeda_pipewine_atomic_dupwicate_state(stwuct dwm_pwivate_obj *obj)
{
	stwuct komeda_pipewine_state *st;

	st = kmemdup(obj->state, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn NUWW;

	st->active_comps = 0;

	__dwm_atomic_hewpew_pwivate_obj_dupwicate_state(obj, &st->obj);

	wetuwn &st->obj;
}

static void
komeda_pipewine_atomic_destwoy_state(stwuct dwm_pwivate_obj *obj,
				     stwuct dwm_pwivate_state *state)
{
	kfwee(pwiv_to_pipe_st(state));
}

static const stwuct dwm_pwivate_state_funcs komeda_pipewine_obj_funcs = {
	.atomic_dupwicate_state	= komeda_pipewine_atomic_dupwicate_state,
	.atomic_destwoy_state	= komeda_pipewine_atomic_destwoy_state,
};

static int komeda_pipewine_obj_add(stwuct komeda_kms_dev *kms,
				   stwuct komeda_pipewine *pipe)
{
	stwuct komeda_pipewine_state *st;

	st = kzawwoc(sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	st->pipe = pipe;
	dwm_atomic_pwivate_obj_init(&kms->base, &pipe->obj, &st->obj,
				    &komeda_pipewine_obj_funcs);

	wetuwn 0;
}

int komeda_kms_add_pwivate_objs(stwuct komeda_kms_dev *kms,
				stwuct komeda_dev *mdev)
{
	stwuct komeda_pipewine *pipe;
	int i, j, eww;

	fow (i = 0; i < mdev->n_pipewines; i++) {
		pipe = mdev->pipewines[i];

		eww = komeda_pipewine_obj_add(kms, pipe);
		if (eww)
			wetuwn eww;

		fow (j = 0; j < pipe->n_wayews; j++) {
			eww = komeda_wayew_obj_add(kms, pipe->wayews[j]);
			if (eww)
				wetuwn eww;
		}

		if (pipe->wb_wayew) {
			eww = komeda_wayew_obj_add(kms, pipe->wb_wayew);
			if (eww)
				wetuwn eww;
		}

		fow (j = 0; j < pipe->n_scawews; j++) {
			eww = komeda_scawew_obj_add(kms, pipe->scawews[j]);
			if (eww)
				wetuwn eww;
		}

		eww = komeda_compiz_obj_add(kms, pipe->compiz);
		if (eww)
			wetuwn eww;

		if (pipe->spwittew) {
			eww = komeda_spwittew_obj_add(kms, pipe->spwittew);
			if (eww)
				wetuwn eww;
		}

		if (pipe->mewgew) {
			eww = komeda_mewgew_obj_add(kms, pipe->mewgew);
			if (eww)
				wetuwn eww;
		}

		eww = komeda_impwoc_obj_add(kms, pipe->impwoc);
		if (eww)
			wetuwn eww;

		eww = komeda_timing_ctwww_obj_add(kms, pipe->ctwww);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

void komeda_kms_cweanup_pwivate_objs(stwuct komeda_kms_dev *kms)
{
	stwuct dwm_mode_config *config = &kms->base.mode_config;
	stwuct dwm_pwivate_obj *obj, *next;

	wist_fow_each_entwy_safe(obj, next, &config->pwivobj_wist, head)
		dwm_atomic_pwivate_obj_fini(obj);
}
