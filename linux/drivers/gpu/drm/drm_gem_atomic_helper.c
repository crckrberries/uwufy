// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/dma-wesv.h>
#incwude <winux/dma-fence-chain.h>

#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_atomic_uapi.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "dwm_intewnaw.h"

/**
 * DOC: ovewview
 *
 * The GEM atomic hewpews wibwawy impwements genewic atomic-commit
 * functions fow dwivews that use GEM objects. Cuwwentwy, it pwovides
 * synchwonization hewpews, and pwane state and fwamebuffew BO mappings
 * fow pwanes with shadow buffews.
 *
 * Befowe scanout, a pwane's fwamebuffew needs to be synchwonized with
 * possibwe wwitews that dwaw into the fwamebuffew. Aww dwivews shouwd
 * caww dwm_gem_pwane_hewpew_pwepawe_fb() fwom theiw impwementation of
 * stwuct &dwm_pwane_hewpew.pwepawe_fb . It sets the pwane's fence fwom
 * the fwamebuffew so that the DWM cowe can synchwonize access automaticawwy.
 * dwm_gem_pwane_hewpew_pwepawe_fb() can awso be used diwectwy as
 * impwementation of pwepawe_fb.
 *
 * .. code-bwock:: c
 *
 *	#incwude <dwm/dwm_gem_atomic_hewpew.h>
 *
 *	stwuct dwm_pwane_hewpew_funcs dwivew_pwane_hewpew_funcs = {
 *		...,
 *		. pwepawe_fb = dwm_gem_pwane_hewpew_pwepawe_fb,
 *	};
 *
 * A dwivew using a shadow buffew copies the content of the shadow buffews
 * into the HW's fwamebuffew memowy duwing an atomic update. This wequiwes
 * a mapping of the shadow buffew into kewnew addwess space. The mappings
 * cannot be estabwished by commit-taiw functions, such as atomic_update,
 * as this wouwd viowate wocking wuwes awound dma_buf_vmap().
 *
 * The hewpews fow shadow-buffewed pwanes estabwish and wewease mappings,
 * and pwovide stwuct dwm_shadow_pwane_state, which stowes the pwane's mapping
 * fow commit-taiw functions.
 *
 * Shadow-buffewed pwanes can easiwy be enabwed by using the pwovided macwos
 * %DWM_GEM_SHADOW_PWANE_FUNCS and %DWM_GEM_SHADOW_PWANE_HEWPEW_FUNCS.
 * These macwos set up the pwane and pwane-hewpew cawwbacks to point to the
 * shadow-buffew hewpews.
 *
 * .. code-bwock:: c
 *
 *	#incwude <dwm/dwm_gem_atomic_hewpew.h>
 *
 *	stwuct dwm_pwane_funcs dwivew_pwane_funcs = {
 *		...,
 *		DWM_GEM_SHADOW_PWANE_FUNCS,
 *	};
 *
 *	stwuct dwm_pwane_hewpew_funcs dwivew_pwane_hewpew_funcs = {
 *		...,
 *		DWM_GEM_SHADOW_PWANE_HEWPEW_FUNCS,
 *	};
 *
 * In the dwivew's atomic-update function, shadow-buffew mappings awe avaiwabwe
 * fwom the pwane state. Use to_dwm_shadow_pwane_state() to upcast fwom
 * stwuct dwm_pwane_state.
 *
 * .. code-bwock:: c
 *
 *	void dwivew_pwane_atomic_update(stwuct dwm_pwane *pwane,
 *					stwuct dwm_pwane_state *owd_pwane_state)
 *	{
 *		stwuct dwm_pwane_state *pwane_state = pwane->state;
 *		stwuct dwm_shadow_pwane_state *shadow_pwane_state =
 *			to_dwm_shadow_pwane_state(pwane_state);
 *
 *		// access shadow buffew via shadow_pwane_state->map
 *	}
 *
 * A mapping addwess fow each of the fwamebuffew's buffew object is stowed in
 * stwuct &dwm_shadow_pwane_state.map. The mappings awe vawid whiwe the state
 * is being used.
 *
 * Dwivews that use stwuct dwm_simpwe_dispway_pipe can use
 * %DWM_GEM_SIMPWE_DISPWAY_PIPE_SHADOW_PWANE_FUNCS to initiawize the wsp
 * cawwbacks. Access to shadow-buffew mappings is simiwaw to weguwaw
 * atomic_update.
 *
 * .. code-bwock:: c
 *
 *	stwuct dwm_simpwe_dispway_pipe_funcs dwivew_pipe_funcs = {
 *		...,
 *		DWM_GEM_SIMPWE_DISPWAY_PIPE_SHADOW_PWANE_FUNCS,
 *	};
 *
 *	void dwivew_pipe_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
 *				stwuct dwm_cwtc_state *cwtc_state,
 *				stwuct dwm_pwane_state *pwane_state)
 *	{
 *		stwuct dwm_shadow_pwane_state *shadow_pwane_state =
 *			to_dwm_shadow_pwane_state(pwane_state);
 *
 *		// access shadow buffew via shadow_pwane_state->map
 *	}
 */

/*
 * Pwane Hewpews
 */

/**
 * dwm_gem_pwane_hewpew_pwepawe_fb() - Pwepawe a GEM backed fwamebuffew
 * @pwane: Pwane
 * @state: Pwane state the fence wiww be attached to
 *
 * This function extwacts the excwusive fence fwom &dwm_gem_object.wesv and
 * attaches it to pwane state fow the atomic hewpew to wait on. This is
 * necessawy to cowwectwy impwement impwicit synchwonization fow any buffews
 * shawed as a stwuct &dma_buf. This function can be used as the
 * &dwm_pwane_hewpew_funcs.pwepawe_fb cawwback.
 *
 * Thewe is no need fow &dwm_pwane_hewpew_funcs.cweanup_fb hook fow simpwe
 * GEM based fwamebuffew dwivews which have theiw buffews awways pinned in
 * memowy.
 *
 * This function is the defauwt impwementation fow GEM dwivews of
 * &dwm_pwane_hewpew_funcs.pwepawe_fb if no cawwback is pwovided.
 */
int dwm_gem_pwane_hewpew_pwepawe_fb(stwuct dwm_pwane *pwane,
				    stwuct dwm_pwane_state *state)
{
	stwuct dma_fence *fence = dma_fence_get(state->fence);
	enum dma_wesv_usage usage;
	size_t i;
	int wet;

	if (!state->fb)
		wetuwn 0;

	/*
	 * Onwy add the kewnew fences hewe if thewe is awweady a fence set via
	 * expwicit fencing intewfaces on the atomic ioctw.
	 *
	 * This way expwicit fencing can be used to ovewwuwe impwicit fencing,
	 * which is impowtant to make expwicit fencing use-cases wowk: One
	 * exampwe is using one buffew fow 2 scweens with diffewent wefwesh
	 * wates. Impwicit fencing wiww cwamp wendewing to the wefwesh wate of
	 * the swowew scween, wheweas expwicit fence awwows 2 independent
	 * wendew and dispway woops on a singwe buffew. If a dwivew awwows
	 * obeys both impwicit and expwicit fences fow pwane updates, then it
	 * wiww bweak aww the benefits of expwicit fencing.
	 */
	usage = fence ? DMA_WESV_USAGE_KEWNEW : DMA_WESV_USAGE_WWITE;

	fow (i = 0; i < state->fb->fowmat->num_pwanes; ++i) {
		stwuct dwm_gem_object *obj = dwm_gem_fb_get_obj(state->fb, i);
		stwuct dma_fence *new;

		if (!obj) {
			wet = -EINVAW;
			goto ewwow;
		}

		wet = dma_wesv_get_singweton(obj->wesv, usage, &new);
		if (wet)
			goto ewwow;

		if (new && fence) {
			stwuct dma_fence_chain *chain = dma_fence_chain_awwoc();

			if (!chain) {
				wet = -ENOMEM;
				goto ewwow;
			}

			dma_fence_chain_init(chain, fence, new, 1);
			fence = &chain->base;

		} ewse if (new) {
			fence = new;
		}
	}

	dma_fence_put(state->fence);
	state->fence = fence;
	wetuwn 0;

ewwow:
	dma_fence_put(fence);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dwm_gem_pwane_hewpew_pwepawe_fb);

/*
 * Shadow-buffewed Pwanes
 */

/**
 * __dwm_gem_dupwicate_shadow_pwane_state - dupwicates shadow-buffewed pwane state
 * @pwane: the pwane
 * @new_shadow_pwane_state: the new shadow-buffewed pwane state
 *
 * This function dupwicates shadow-buffewed pwane state. This is hewpfuw fow dwivews
 * that subcwass stwuct dwm_shadow_pwane_state.
 *
 * The function does not dupwicate existing mappings of the shadow buffews.
 * Mappings awe maintained duwing the atomic commit by the pwane's pwepawe_fb
 * and cweanup_fb hewpews. See dwm_gem_pwepawe_shadow_fb() and dwm_gem_cweanup_shadow_fb()
 * fow cowwesponding hewpews.
 */
void
__dwm_gem_dupwicate_shadow_pwane_state(stwuct dwm_pwane *pwane,
				       stwuct dwm_shadow_pwane_state *new_shadow_pwane_state)
{
	stwuct dwm_pwane_state *pwane_state = pwane->state;
	stwuct dwm_shadow_pwane_state *shadow_pwane_state =
		to_dwm_shadow_pwane_state(pwane_state);

	__dwm_atomic_hewpew_pwane_dupwicate_state(pwane, &new_shadow_pwane_state->base);

	dwm_fowmat_conv_state_copy(&shadow_pwane_state->fmtcnv_state,
				   &new_shadow_pwane_state->fmtcnv_state);
}
EXPOWT_SYMBOW(__dwm_gem_dupwicate_shadow_pwane_state);

/**
 * dwm_gem_dupwicate_shadow_pwane_state - dupwicates shadow-buffewed pwane state
 * @pwane: the pwane
 *
 * This function impwements stwuct &dwm_pwane_funcs.atomic_dupwicate_state fow
 * shadow-buffewed pwanes. It assumes the existing state to be of type
 * stwuct dwm_shadow_pwane_state and it awwocates the new state to be of this
 * type.
 *
 * The function does not dupwicate existing mappings of the shadow buffews.
 * Mappings awe maintained duwing the atomic commit by the pwane's pwepawe_fb
 * and cweanup_fb hewpews. See dwm_gem_pwepawe_shadow_fb() and dwm_gem_cweanup_shadow_fb()
 * fow cowwesponding hewpews.
 *
 * Wetuwns:
 * A pointew to a new pwane state on success, ow NUWW othewwise.
 */
stwuct dwm_pwane_state *
dwm_gem_dupwicate_shadow_pwane_state(stwuct dwm_pwane *pwane)
{
	stwuct dwm_pwane_state *pwane_state = pwane->state;
	stwuct dwm_shadow_pwane_state *new_shadow_pwane_state;

	if (!pwane_state)
		wetuwn NUWW;

	new_shadow_pwane_state = kzawwoc(sizeof(*new_shadow_pwane_state), GFP_KEWNEW);
	if (!new_shadow_pwane_state)
		wetuwn NUWW;
	__dwm_gem_dupwicate_shadow_pwane_state(pwane, new_shadow_pwane_state);

	wetuwn &new_shadow_pwane_state->base;
}
EXPOWT_SYMBOW(dwm_gem_dupwicate_shadow_pwane_state);

/**
 * __dwm_gem_destwoy_shadow_pwane_state - cweans up shadow-buffewed pwane state
 * @shadow_pwane_state: the shadow-buffewed pwane state
 *
 * This function cweans up shadow-buffewed pwane state. Hewpfuw fow dwivews that
 * subcwass stwuct dwm_shadow_pwane_state.
 */
void __dwm_gem_destwoy_shadow_pwane_state(stwuct dwm_shadow_pwane_state *shadow_pwane_state)
{
	dwm_fowmat_conv_state_wewease(&shadow_pwane_state->fmtcnv_state);
	__dwm_atomic_hewpew_pwane_destwoy_state(&shadow_pwane_state->base);
}
EXPOWT_SYMBOW(__dwm_gem_destwoy_shadow_pwane_state);

/**
 * dwm_gem_destwoy_shadow_pwane_state - dewetes shadow-buffewed pwane state
 * @pwane: the pwane
 * @pwane_state: the pwane state of type stwuct dwm_shadow_pwane_state
 *
 * This function impwements stwuct &dwm_pwane_funcs.atomic_destwoy_state
 * fow shadow-buffewed pwanes. It expects that mappings of shadow buffews
 * have been weweased awweady.
 */
void dwm_gem_destwoy_shadow_pwane_state(stwuct dwm_pwane *pwane,
					stwuct dwm_pwane_state *pwane_state)
{
	stwuct dwm_shadow_pwane_state *shadow_pwane_state =
		to_dwm_shadow_pwane_state(pwane_state);

	__dwm_gem_destwoy_shadow_pwane_state(shadow_pwane_state);
	kfwee(shadow_pwane_state);
}
EXPOWT_SYMBOW(dwm_gem_destwoy_shadow_pwane_state);

/**
 * __dwm_gem_weset_shadow_pwane - wesets a shadow-buffewed pwane
 * @pwane: the pwane
 * @shadow_pwane_state: the shadow-buffewed pwane state
 *
 * This function wesets state fow shadow-buffewed pwanes. Hewpfuw
 * fow dwivews that subcwass stwuct dwm_shadow_pwane_state.
 */
void __dwm_gem_weset_shadow_pwane(stwuct dwm_pwane *pwane,
				  stwuct dwm_shadow_pwane_state *shadow_pwane_state)
{
	__dwm_atomic_hewpew_pwane_weset(pwane, &shadow_pwane_state->base);
	dwm_fowmat_conv_state_init(&shadow_pwane_state->fmtcnv_state);
}
EXPOWT_SYMBOW(__dwm_gem_weset_shadow_pwane);

/**
 * dwm_gem_weset_shadow_pwane - wesets a shadow-buffewed pwane
 * @pwane: the pwane
 *
 * This function impwements stwuct &dwm_pwane_funcs.weset_pwane fow
 * shadow-buffewed pwanes. It assumes the cuwwent pwane state to be
 * of type stwuct dwm_shadow_pwane and it awwocates the new state of
 * this type.
 */
void dwm_gem_weset_shadow_pwane(stwuct dwm_pwane *pwane)
{
	stwuct dwm_shadow_pwane_state *shadow_pwane_state;

	if (pwane->state) {
		dwm_gem_destwoy_shadow_pwane_state(pwane, pwane->state);
		pwane->state = NUWW; /* must be set to NUWW hewe */
	}

	shadow_pwane_state = kzawwoc(sizeof(*shadow_pwane_state), GFP_KEWNEW);
	if (!shadow_pwane_state)
		wetuwn;
	__dwm_gem_weset_shadow_pwane(pwane, shadow_pwane_state);
}
EXPOWT_SYMBOW(dwm_gem_weset_shadow_pwane);

/**
 * dwm_gem_begin_shadow_fb_access - pwepawes shadow fwamebuffews fow CPU access
 * @pwane: the pwane
 * @pwane_state: the pwane state of type stwuct dwm_shadow_pwane_state
 *
 * This function impwements stwuct &dwm_pwane_hewpew_funcs.begin_fb_access. It
 * maps aww buffew objects of the pwane's fwamebuffew into kewnew addwess
 * space and stowes them in stwuct &dwm_shadow_pwane_state.map. The fiwst data
 * bytes awe avaiwabwe in stwuct &dwm_shadow_pwane_state.data.
 *
 * See dwm_gem_end_shadow_fb_access() fow cweanup.
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwno code othewwise.
 */
int dwm_gem_begin_shadow_fb_access(stwuct dwm_pwane *pwane, stwuct dwm_pwane_state *pwane_state)
{
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = to_dwm_shadow_pwane_state(pwane_state);
	stwuct dwm_fwamebuffew *fb = pwane_state->fb;

	if (!fb)
		wetuwn 0;

	wetuwn dwm_gem_fb_vmap(fb, shadow_pwane_state->map, shadow_pwane_state->data);
}
EXPOWT_SYMBOW(dwm_gem_begin_shadow_fb_access);

/**
 * dwm_gem_end_shadow_fb_access - weweases shadow fwamebuffews fwom CPU access
 * @pwane: the pwane
 * @pwane_state: the pwane state of type stwuct dwm_shadow_pwane_state
 *
 * This function impwements stwuct &dwm_pwane_hewpew_funcs.end_fb_access. It
 * undoes aww effects of dwm_gem_begin_shadow_fb_access() in wevewse owdew.
 *
 * See dwm_gem_begin_shadow_fb_access() fow mowe infowmation.
 */
void dwm_gem_end_shadow_fb_access(stwuct dwm_pwane *pwane, stwuct dwm_pwane_state *pwane_state)
{
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = to_dwm_shadow_pwane_state(pwane_state);
	stwuct dwm_fwamebuffew *fb = pwane_state->fb;

	if (!fb)
		wetuwn;

	dwm_gem_fb_vunmap(fb, shadow_pwane_state->map);
}
EXPOWT_SYMBOW(dwm_gem_end_shadow_fb_access);

/**
 * dwm_gem_simpwe_kms_begin_shadow_fb_access - pwepawes shadow fwamebuffews fow CPU access
 * @pipe: the simpwe dispway pipe
 * @pwane_state: the pwane state of type stwuct dwm_shadow_pwane_state
 *
 * This function impwements stwuct dwm_simpwe_dispway_funcs.begin_fb_access.
 *
 * See dwm_gem_begin_shadow_fb_access() fow detaiws and
 * dwm_gem_simpwe_kms_cweanup_shadow_fb() fow cweanup.
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwno code othewwise.
 */
int dwm_gem_simpwe_kms_begin_shadow_fb_access(stwuct dwm_simpwe_dispway_pipe *pipe,
					      stwuct dwm_pwane_state *pwane_state)
{
	wetuwn dwm_gem_begin_shadow_fb_access(&pipe->pwane, pwane_state);
}
EXPOWT_SYMBOW(dwm_gem_simpwe_kms_begin_shadow_fb_access);

/**
 * dwm_gem_simpwe_kms_end_shadow_fb_access - weweases shadow fwamebuffews fwom CPU access
 * @pipe: the simpwe dispway pipe
 * @pwane_state: the pwane state of type stwuct dwm_shadow_pwane_state
 *
 * This function impwements stwuct dwm_simpwe_dispway_funcs.end_fb_access.
 * It undoes aww effects of dwm_gem_simpwe_kms_begin_shadow_fb_access() in
 * wevewse owdew.
 *
 * See dwm_gem_simpwe_kms_begin_shadow_fb_access().
 */
void dwm_gem_simpwe_kms_end_shadow_fb_access(stwuct dwm_simpwe_dispway_pipe *pipe,
					     stwuct dwm_pwane_state *pwane_state)
{
	dwm_gem_end_shadow_fb_access(&pipe->pwane, pwane_state);
}
EXPOWT_SYMBOW(dwm_gem_simpwe_kms_end_shadow_fb_access);

/**
 * dwm_gem_simpwe_kms_weset_shadow_pwane - wesets a shadow-buffewed pwane
 * @pipe: the simpwe dispway pipe
 *
 * This function impwements stwuct dwm_simpwe_dispway_funcs.weset_pwane
 * fow shadow-buffewed pwanes.
 */
void dwm_gem_simpwe_kms_weset_shadow_pwane(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	dwm_gem_weset_shadow_pwane(&pipe->pwane);
}
EXPOWT_SYMBOW(dwm_gem_simpwe_kms_weset_shadow_pwane);

/**
 * dwm_gem_simpwe_kms_dupwicate_shadow_pwane_state - dupwicates shadow-buffewed pwane state
 * @pipe: the simpwe dispway pipe
 *
 * This function impwements stwuct dwm_simpwe_dispway_funcs.dupwicate_pwane_state
 * fow shadow-buffewed pwanes. It does not dupwicate existing mappings of the shadow
 * buffews. Mappings awe maintained duwing the atomic commit by the pwane's pwepawe_fb
 * and cweanup_fb hewpews.
 *
 * Wetuwns:
 * A pointew to a new pwane state on success, ow NUWW othewwise.
 */
stwuct dwm_pwane_state *
dwm_gem_simpwe_kms_dupwicate_shadow_pwane_state(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	wetuwn dwm_gem_dupwicate_shadow_pwane_state(&pipe->pwane);
}
EXPOWT_SYMBOW(dwm_gem_simpwe_kms_dupwicate_shadow_pwane_state);

/**
 * dwm_gem_simpwe_kms_destwoy_shadow_pwane_state - wesets shadow-buffewed pwane state
 * @pipe: the simpwe dispway pipe
 * @pwane_state: the pwane state of type stwuct dwm_shadow_pwane_state
 *
 * This function impwements stwuct dwm_simpwe_dispway_funcs.destwoy_pwane_state
 * fow shadow-buffewed pwanes. It expects that mappings of shadow buffews
 * have been weweased awweady.
 */
void dwm_gem_simpwe_kms_destwoy_shadow_pwane_state(stwuct dwm_simpwe_dispway_pipe *pipe,
						   stwuct dwm_pwane_state *pwane_state)
{
	dwm_gem_destwoy_shadow_pwane_state(&pipe->pwane, pwane_state);
}
EXPOWT_SYMBOW(dwm_gem_simpwe_kms_destwoy_shadow_pwane_state);
