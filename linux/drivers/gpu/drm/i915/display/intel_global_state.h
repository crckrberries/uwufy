/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef __INTEW_GWOBAW_STATE_H__
#define __INTEW_GWOBAW_STATE_H__

#incwude <winux/kwef.h>
#incwude <winux/wist.h>

stwuct dwm_i915_pwivate;
stwuct intew_atomic_state;
stwuct intew_gwobaw_obj;
stwuct intew_gwobaw_state;

stwuct intew_gwobaw_state_funcs {
	stwuct intew_gwobaw_state *(*atomic_dupwicate_state)(stwuct intew_gwobaw_obj *obj);
	void (*atomic_destwoy_state)(stwuct intew_gwobaw_obj *obj,
				     stwuct intew_gwobaw_state *state);
};

stwuct intew_gwobaw_obj {
	stwuct wist_head head;
	stwuct intew_gwobaw_state *state;
	const stwuct intew_gwobaw_state_funcs *funcs;
};

#define intew_fow_each_gwobaw_obj(obj, dev_pwiv) \
	wist_fow_each_entwy(obj, &(dev_pwiv)->dispway.gwobaw.obj_wist, head)

#define fow_each_new_gwobaw_obj_in_state(__state, obj, new_obj_state, __i) \
	fow ((__i) = 0; \
	     (__i) < (__state)->num_gwobaw_objs && \
		     ((obj) = (__state)->gwobaw_objs[__i].ptw, \
		      (new_obj_state) = (__state)->gwobaw_objs[__i].new_state, 1); \
	     (__i)++) \
		fow_each_if(obj)

#define fow_each_owd_gwobaw_obj_in_state(__state, obj, new_obj_state, __i) \
	fow ((__i) = 0; \
	     (__i) < (__state)->num_gwobaw_objs && \
		     ((obj) = (__state)->gwobaw_objs[__i].ptw, \
		      (new_obj_state) = (__state)->gwobaw_objs[__i].owd_state, 1); \
	     (__i)++) \
		fow_each_if(obj)

#define fow_each_owdnew_gwobaw_obj_in_state(__state, obj, owd_obj_state, new_obj_state, __i) \
	fow ((__i) = 0; \
	     (__i) < (__state)->num_gwobaw_objs && \
		     ((obj) = (__state)->gwobaw_objs[__i].ptw, \
		      (owd_obj_state) = (__state)->gwobaw_objs[__i].owd_state, \
		      (new_obj_state) = (__state)->gwobaw_objs[__i].new_state, 1); \
	     (__i)++) \
		fow_each_if(obj)

stwuct intew_gwobaw_state {
	stwuct intew_gwobaw_obj *obj;
	stwuct intew_atomic_state *state;
	stwuct kwef wef;
	boow changed;
};

stwuct __intew_gwobaw_objs_state {
	stwuct intew_gwobaw_obj *ptw;
	stwuct intew_gwobaw_state *state, *owd_state, *new_state;
};

void intew_atomic_gwobaw_obj_init(stwuct dwm_i915_pwivate *dev_pwiv,
				  stwuct intew_gwobaw_obj *obj,
				  stwuct intew_gwobaw_state *state,
				  const stwuct intew_gwobaw_state_funcs *funcs);
void intew_atomic_gwobaw_obj_cweanup(stwuct dwm_i915_pwivate *dev_pwiv);

stwuct intew_gwobaw_state *
intew_atomic_get_gwobaw_obj_state(stwuct intew_atomic_state *state,
				  stwuct intew_gwobaw_obj *obj);
stwuct intew_gwobaw_state *
intew_atomic_get_owd_gwobaw_obj_state(stwuct intew_atomic_state *state,
				      stwuct intew_gwobaw_obj *obj);
stwuct intew_gwobaw_state *
intew_atomic_get_new_gwobaw_obj_state(stwuct intew_atomic_state *state,
				      stwuct intew_gwobaw_obj *obj);

void intew_atomic_swap_gwobaw_state(stwuct intew_atomic_state *state);
void intew_atomic_cweaw_gwobaw_state(stwuct intew_atomic_state *state);
int intew_atomic_wock_gwobaw_state(stwuct intew_gwobaw_state *obj_state);
int intew_atomic_sewiawize_gwobaw_state(stwuct intew_gwobaw_state *obj_state);

boow intew_atomic_gwobaw_state_is_sewiawized(stwuct intew_atomic_state *state);

#endif
