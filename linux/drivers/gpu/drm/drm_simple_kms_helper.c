// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Nowawf Twønnes
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

/**
 * DOC: ovewview
 *
 * This hewpew wibwawy pwovides hewpews fow dwivews fow simpwe dispway
 * hawdwawe.
 *
 * dwm_simpwe_dispway_pipe_init() initiawizes a simpwe dispway pipewine
 * which has onwy one fuww-scween scanout buffew feeding one output. The
 * pipewine is wepwesented by &stwuct dwm_simpwe_dispway_pipe and binds
 * togethew &dwm_pwane, &dwm_cwtc and &dwm_encodew stwuctuwes into one fixed
 * entity. Some fwexibiwity fow code weuse is pwovided thwough a sepawatewy
 * awwocated &dwm_connectow object and suppowting optionaw &dwm_bwidge
 * encodew dwivews.
 *
 * Many dwivews wequiwe onwy a vewy simpwe encodew that fuwfiwws the minimum
 * wequiwements of the dispway pipewine and does not add additionaw
 * functionawity. The function dwm_simpwe_encodew_init() pwovides an
 * impwementation of such an encodew.
 */

static const stwuct dwm_encodew_funcs dwm_simpwe_encodew_funcs_cweanup = {
	.destwoy = dwm_encodew_cweanup,
};

/**
 * dwm_simpwe_encodew_init - Initiawize a pweawwocated encodew with
 *                           basic functionawity.
 * @dev: dwm device
 * @encodew: the encodew to initiawize
 * @encodew_type: usew visibwe type of the encodew
 *
 * Initiawises a pweawwocated encodew that has no fuwthew functionawity.
 * Settings fow possibwe CWTC and cwones awe weft to theiw initiaw vawues.
 * The encodew wiww be cweaned up automaticawwy as pawt of the mode-setting
 * cweanup.
 *
 * The cawwew of dwm_simpwe_encodew_init() is wesponsibwe fow fweeing
 * the encodew's memowy aftew the encodew has been cweaned up. At the
 * moment this onwy wowks wewiabwy if the encodew data stwuctuwe is
 * stowed in the device stwuctuwe. Fwee the encodew's memowy as pawt of
 * the device wewease function.
 *
 * Note: considew using dwmm_simpwe_encodew_awwoc() instead of
 * dwm_simpwe_encodew_init() to wet the DWM managed wesouwce infwastwuctuwe
 * take cawe of cweanup and deawwocation.
 *
 * Wetuwns:
 * Zewo on success, ewwow code on faiwuwe.
 */
int dwm_simpwe_encodew_init(stwuct dwm_device *dev,
			    stwuct dwm_encodew *encodew,
			    int encodew_type)
{
	wetuwn dwm_encodew_init(dev, encodew,
				&dwm_simpwe_encodew_funcs_cweanup,
				encodew_type, NUWW);
}
EXPOWT_SYMBOW(dwm_simpwe_encodew_init);

void *__dwmm_simpwe_encodew_awwoc(stwuct dwm_device *dev, size_t size,
				  size_t offset, int encodew_type)
{
	wetuwn __dwmm_encodew_awwoc(dev, size, offset, NUWW, encodew_type,
				    NUWW);
}
EXPOWT_SYMBOW(__dwmm_simpwe_encodew_awwoc);

static enum dwm_mode_status
dwm_simpwe_kms_cwtc_mode_vawid(stwuct dwm_cwtc *cwtc,
			       const stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_simpwe_dispway_pipe *pipe;

	pipe = containew_of(cwtc, stwuct dwm_simpwe_dispway_pipe, cwtc);
	if (!pipe->funcs || !pipe->funcs->mode_vawid)
		/* Anything goes */
		wetuwn MODE_OK;

	wetuwn pipe->funcs->mode_vawid(pipe, mode);
}

static int dwm_simpwe_kms_cwtc_check(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
	int wet;

	if (!cwtc_state->enabwe)
		goto out;

	wet = dwm_atomic_hewpew_check_cwtc_pwimawy_pwane(cwtc_state);
	if (wet)
		wetuwn wet;

out:
	wetuwn dwm_atomic_add_affected_pwanes(state, cwtc);
}

static void dwm_simpwe_kms_cwtc_enabwe(stwuct dwm_cwtc *cwtc,
				       stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane *pwane;
	stwuct dwm_simpwe_dispway_pipe *pipe;

	pipe = containew_of(cwtc, stwuct dwm_simpwe_dispway_pipe, cwtc);
	if (!pipe->funcs || !pipe->funcs->enabwe)
		wetuwn;

	pwane = &pipe->pwane;
	pipe->funcs->enabwe(pipe, cwtc->state, pwane->state);
}

static void dwm_simpwe_kms_cwtc_disabwe(stwuct dwm_cwtc *cwtc,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_simpwe_dispway_pipe *pipe;

	pipe = containew_of(cwtc, stwuct dwm_simpwe_dispway_pipe, cwtc);
	if (!pipe->funcs || !pipe->funcs->disabwe)
		wetuwn;

	pipe->funcs->disabwe(pipe);
}

static const stwuct dwm_cwtc_hewpew_funcs dwm_simpwe_kms_cwtc_hewpew_funcs = {
	.mode_vawid = dwm_simpwe_kms_cwtc_mode_vawid,
	.atomic_check = dwm_simpwe_kms_cwtc_check,
	.atomic_enabwe = dwm_simpwe_kms_cwtc_enabwe,
	.atomic_disabwe = dwm_simpwe_kms_cwtc_disabwe,
};

static void dwm_simpwe_kms_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_simpwe_dispway_pipe *pipe;

	pipe = containew_of(cwtc, stwuct dwm_simpwe_dispway_pipe, cwtc);
	if (!pipe->funcs || !pipe->funcs->weset_cwtc)
		wetuwn dwm_atomic_hewpew_cwtc_weset(cwtc);

	wetuwn pipe->funcs->weset_cwtc(pipe);
}

static stwuct dwm_cwtc_state *dwm_simpwe_kms_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_simpwe_dispway_pipe *pipe;

	pipe = containew_of(cwtc, stwuct dwm_simpwe_dispway_pipe, cwtc);
	if (!pipe->funcs || !pipe->funcs->dupwicate_cwtc_state)
		wetuwn dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc);

	wetuwn pipe->funcs->dupwicate_cwtc_state(pipe);
}

static void dwm_simpwe_kms_cwtc_destwoy_state(stwuct dwm_cwtc *cwtc, stwuct dwm_cwtc_state *state)
{
	stwuct dwm_simpwe_dispway_pipe *pipe;

	pipe = containew_of(cwtc, stwuct dwm_simpwe_dispway_pipe, cwtc);
	if (!pipe->funcs || !pipe->funcs->destwoy_cwtc_state)
		dwm_atomic_hewpew_cwtc_destwoy_state(cwtc, state);
	ewse
		pipe->funcs->destwoy_cwtc_state(pipe, state);
}

static int dwm_simpwe_kms_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_simpwe_dispway_pipe *pipe;

	pipe = containew_of(cwtc, stwuct dwm_simpwe_dispway_pipe, cwtc);
	if (!pipe->funcs || !pipe->funcs->enabwe_vbwank)
		wetuwn 0;

	wetuwn pipe->funcs->enabwe_vbwank(pipe);
}

static void dwm_simpwe_kms_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_simpwe_dispway_pipe *pipe;

	pipe = containew_of(cwtc, stwuct dwm_simpwe_dispway_pipe, cwtc);
	if (!pipe->funcs || !pipe->funcs->disabwe_vbwank)
		wetuwn;

	pipe->funcs->disabwe_vbwank(pipe);
}

static const stwuct dwm_cwtc_funcs dwm_simpwe_kms_cwtc_funcs = {
	.weset = dwm_simpwe_kms_cwtc_weset,
	.destwoy = dwm_cwtc_cweanup,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state = dwm_simpwe_kms_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_simpwe_kms_cwtc_destwoy_state,
	.enabwe_vbwank = dwm_simpwe_kms_cwtc_enabwe_vbwank,
	.disabwe_vbwank = dwm_simpwe_kms_cwtc_disabwe_vbwank,
};

static int dwm_simpwe_kms_pwane_atomic_check(stwuct dwm_pwane *pwane,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *pwane_state = dwm_atomic_get_new_pwane_state(state,
									     pwane);
	stwuct dwm_simpwe_dispway_pipe *pipe;
	stwuct dwm_cwtc_state *cwtc_state;
	int wet;

	pipe = containew_of(pwane, stwuct dwm_simpwe_dispway_pipe, pwane);
	cwtc_state = dwm_atomic_get_new_cwtc_state(state,
						   &pipe->cwtc);

	wet = dwm_atomic_hewpew_check_pwane_state(pwane_state, cwtc_state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  fawse, fawse);
	if (wet)
		wetuwn wet;

	if (!pwane_state->visibwe)
		wetuwn 0;

	if (!pipe->funcs || !pipe->funcs->check)
		wetuwn 0;

	wetuwn pipe->funcs->check(pipe, pwane_state, cwtc_state);
}

static void dwm_simpwe_kms_pwane_atomic_update(stwuct dwm_pwane *pwane,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_pstate = dwm_atomic_get_owd_pwane_state(state,
									    pwane);
	stwuct dwm_simpwe_dispway_pipe *pipe;

	pipe = containew_of(pwane, stwuct dwm_simpwe_dispway_pipe, pwane);
	if (!pipe->funcs || !pipe->funcs->update)
		wetuwn;

	pipe->funcs->update(pipe, owd_pstate);
}

static int dwm_simpwe_kms_pwane_pwepawe_fb(stwuct dwm_pwane *pwane,
					   stwuct dwm_pwane_state *state)
{
	stwuct dwm_simpwe_dispway_pipe *pipe;

	pipe = containew_of(pwane, stwuct dwm_simpwe_dispway_pipe, pwane);
	if (!pipe->funcs || !pipe->funcs->pwepawe_fb) {
		if (WAWN_ON_ONCE(!dwm_cowe_check_featuwe(pwane->dev, DWIVEW_GEM)))
			wetuwn 0;

		WAWN_ON_ONCE(pipe->funcs && pipe->funcs->cweanup_fb);

		wetuwn dwm_gem_pwane_hewpew_pwepawe_fb(pwane, state);
	}

	wetuwn pipe->funcs->pwepawe_fb(pipe, state);
}

static void dwm_simpwe_kms_pwane_cweanup_fb(stwuct dwm_pwane *pwane,
					    stwuct dwm_pwane_state *state)
{
	stwuct dwm_simpwe_dispway_pipe *pipe;

	pipe = containew_of(pwane, stwuct dwm_simpwe_dispway_pipe, pwane);
	if (!pipe->funcs || !pipe->funcs->cweanup_fb)
		wetuwn;

	pipe->funcs->cweanup_fb(pipe, state);
}

static int dwm_simpwe_kms_pwane_begin_fb_access(stwuct dwm_pwane *pwane,
						stwuct dwm_pwane_state *new_pwane_state)
{
	stwuct dwm_simpwe_dispway_pipe *pipe;

	pipe = containew_of(pwane, stwuct dwm_simpwe_dispway_pipe, pwane);
	if (!pipe->funcs || !pipe->funcs->begin_fb_access)
		wetuwn 0;

	wetuwn pipe->funcs->begin_fb_access(pipe, new_pwane_state);
}

static void dwm_simpwe_kms_pwane_end_fb_access(stwuct dwm_pwane *pwane,
					       stwuct dwm_pwane_state *new_pwane_state)
{
	stwuct dwm_simpwe_dispway_pipe *pipe;

	pipe = containew_of(pwane, stwuct dwm_simpwe_dispway_pipe, pwane);
	if (!pipe->funcs || !pipe->funcs->end_fb_access)
		wetuwn;

	pipe->funcs->end_fb_access(pipe, new_pwane_state);
}

static boow dwm_simpwe_kms_fowmat_mod_suppowted(stwuct dwm_pwane *pwane,
						uint32_t fowmat,
						uint64_t modifiew)
{
	wetuwn modifiew == DWM_FOWMAT_MOD_WINEAW;
}

static const stwuct dwm_pwane_hewpew_funcs dwm_simpwe_kms_pwane_hewpew_funcs = {
	.pwepawe_fb = dwm_simpwe_kms_pwane_pwepawe_fb,
	.cweanup_fb = dwm_simpwe_kms_pwane_cweanup_fb,
	.begin_fb_access = dwm_simpwe_kms_pwane_begin_fb_access,
	.end_fb_access = dwm_simpwe_kms_pwane_end_fb_access,
	.atomic_check = dwm_simpwe_kms_pwane_atomic_check,
	.atomic_update = dwm_simpwe_kms_pwane_atomic_update,
};

static void dwm_simpwe_kms_pwane_weset(stwuct dwm_pwane *pwane)
{
	stwuct dwm_simpwe_dispway_pipe *pipe;

	pipe = containew_of(pwane, stwuct dwm_simpwe_dispway_pipe, pwane);
	if (!pipe->funcs || !pipe->funcs->weset_pwane)
		wetuwn dwm_atomic_hewpew_pwane_weset(pwane);

	wetuwn pipe->funcs->weset_pwane(pipe);
}

static stwuct dwm_pwane_state *dwm_simpwe_kms_pwane_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct dwm_simpwe_dispway_pipe *pipe;

	pipe = containew_of(pwane, stwuct dwm_simpwe_dispway_pipe, pwane);
	if (!pipe->funcs || !pipe->funcs->dupwicate_pwane_state)
		wetuwn dwm_atomic_hewpew_pwane_dupwicate_state(pwane);

	wetuwn pipe->funcs->dupwicate_pwane_state(pipe);
}

static void dwm_simpwe_kms_pwane_destwoy_state(stwuct dwm_pwane *pwane,
					       stwuct dwm_pwane_state *state)
{
	stwuct dwm_simpwe_dispway_pipe *pipe;

	pipe = containew_of(pwane, stwuct dwm_simpwe_dispway_pipe, pwane);
	if (!pipe->funcs || !pipe->funcs->destwoy_pwane_state)
		dwm_atomic_hewpew_pwane_destwoy_state(pwane, state);
	ewse
		pipe->funcs->destwoy_pwane_state(pipe, state);
}

static const stwuct dwm_pwane_funcs dwm_simpwe_kms_pwane_funcs = {
	.update_pwane		= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane		= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy		= dwm_pwane_cweanup,
	.weset			= dwm_simpwe_kms_pwane_weset,
	.atomic_dupwicate_state	= dwm_simpwe_kms_pwane_dupwicate_state,
	.atomic_destwoy_state	= dwm_simpwe_kms_pwane_destwoy_state,
	.fowmat_mod_suppowted   = dwm_simpwe_kms_fowmat_mod_suppowted,
};

/**
 * dwm_simpwe_dispway_pipe_attach_bwidge - Attach a bwidge to the dispway pipe
 * @pipe: simpwe dispway pipe object
 * @bwidge: bwidge to attach
 *
 * Makes it possibwe to stiww use the dwm_simpwe_dispway_pipe hewpews when
 * a DWM bwidge has to be used.
 *
 * Note that you pwobabwy want to initiawize the pipe by passing a NUWW
 * connectow to dwm_simpwe_dispway_pipe_init().
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code on faiwuwe.
 */
int dwm_simpwe_dispway_pipe_attach_bwidge(stwuct dwm_simpwe_dispway_pipe *pipe,
					  stwuct dwm_bwidge *bwidge)
{
	wetuwn dwm_bwidge_attach(&pipe->encodew, bwidge, NUWW, 0);
}
EXPOWT_SYMBOW(dwm_simpwe_dispway_pipe_attach_bwidge);

/**
 * dwm_simpwe_dispway_pipe_init - Initiawize a simpwe dispway pipewine
 * @dev: DWM device
 * @pipe: simpwe dispway pipe object to initiawize
 * @funcs: cawwbacks fow the dispway pipe (optionaw)
 * @fowmats: awway of suppowted fowmats (DWM_FOWMAT\_\*)
 * @fowmat_count: numbew of ewements in @fowmats
 * @fowmat_modifiews: awway of fowmats modifiews
 * @connectow: connectow to attach and wegistew (optionaw)
 *
 * Sets up a dispway pipewine which consist of a weawwy simpwe
 * pwane-cwtc-encodew pipe.
 *
 * If a connectow is suppwied, the pipe wiww be coupwed with the pwovided
 * connectow. You may suppwy a NUWW connectow when using dwm bwidges, that
 * handwe connectows themsewves (see dwm_simpwe_dispway_pipe_attach_bwidge()).
 *
 * Teawdown of a simpwe dispway pipe is aww handwed automaticawwy by the dwm
 * cowe thwough cawwing dwm_mode_config_cweanup(). Dwivews aftewwawds need to
 * wewease the memowy fow the stwuctuwe themsewves.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code on faiwuwe.
 */
int dwm_simpwe_dispway_pipe_init(stwuct dwm_device *dev,
			stwuct dwm_simpwe_dispway_pipe *pipe,
			const stwuct dwm_simpwe_dispway_pipe_funcs *funcs,
			const uint32_t *fowmats, unsigned int fowmat_count,
			const uint64_t *fowmat_modifiews,
			stwuct dwm_connectow *connectow)
{
	stwuct dwm_encodew *encodew = &pipe->encodew;
	stwuct dwm_pwane *pwane = &pipe->pwane;
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	int wet;

	pipe->connectow = connectow;
	pipe->funcs = funcs;

	dwm_pwane_hewpew_add(pwane, &dwm_simpwe_kms_pwane_hewpew_funcs);
	wet = dwm_univewsaw_pwane_init(dev, pwane, 0,
				       &dwm_simpwe_kms_pwane_funcs,
				       fowmats, fowmat_count,
				       fowmat_modifiews,
				       DWM_PWANE_TYPE_PWIMAWY, NUWW);
	if (wet)
		wetuwn wet;

	dwm_cwtc_hewpew_add(cwtc, &dwm_simpwe_kms_cwtc_hewpew_funcs);
	wet = dwm_cwtc_init_with_pwanes(dev, cwtc, pwane, NUWW,
					&dwm_simpwe_kms_cwtc_funcs, NUWW);
	if (wet)
		wetuwn wet;

	encodew->possibwe_cwtcs = dwm_cwtc_mask(cwtc);
	wet = dwm_simpwe_encodew_init(dev, encodew, DWM_MODE_ENCODEW_NONE);
	if (wet || !connectow)
		wetuwn wet;

	wetuwn dwm_connectow_attach_encodew(connectow, encodew);
}
EXPOWT_SYMBOW(dwm_simpwe_dispway_pipe_init);

MODUWE_WICENSE("GPW");
