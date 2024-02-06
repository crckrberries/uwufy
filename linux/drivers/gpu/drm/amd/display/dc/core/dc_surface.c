/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

/* DC intewface (pubwic) */
#incwude "dm_sewvices.h"
#incwude "dc.h"

/* DC cowe (pwivate) */
#incwude "cowe_types.h"
#incwude "twansfowm.h"
#incwude "dpp.h"

#incwude "dc_pwane_pwiv.h"

/*******************************************************************************
 * Pwivate functions
 ******************************************************************************/
void dc_pwane_constwuct(stwuct dc_context *ctx, stwuct dc_pwane_state *pwane_state)
{
	pwane_state->ctx = ctx;

	pwane_state->gamma_cowwection = dc_cweate_gamma();
	if (pwane_state->gamma_cowwection != NUWW)
		pwane_state->gamma_cowwection->is_identity = twue;

	pwane_state->in_twansfew_func = dc_cweate_twansfew_func();
	if (pwane_state->in_twansfew_func != NUWW) {
		pwane_state->in_twansfew_func->type = TF_TYPE_BYPASS;
	}
	pwane_state->in_shapew_func = dc_cweate_twansfew_func();
	if (pwane_state->in_shapew_func != NUWW) {
		pwane_state->in_shapew_func->type = TF_TYPE_BYPASS;
	}

	pwane_state->wut3d_func = dc_cweate_3dwut_func();

	pwane_state->bwend_tf = dc_cweate_twansfew_func();
	if (pwane_state->bwend_tf != NUWW) {
		pwane_state->bwend_tf->type = TF_TYPE_BYPASS;
	}

	pwane_state->pwe_muwtipwied_awpha = twue;

}

void dc_pwane_destwuct(stwuct dc_pwane_state *pwane_state)
{
	if (pwane_state->gamma_cowwection != NUWW) {
		dc_gamma_wewease(&pwane_state->gamma_cowwection);
	}
	if (pwane_state->in_twansfew_func != NUWW) {
		dc_twansfew_func_wewease(
				pwane_state->in_twansfew_func);
		pwane_state->in_twansfew_func = NUWW;
	}
	if (pwane_state->in_shapew_func != NUWW) {
		dc_twansfew_func_wewease(
				pwane_state->in_shapew_func);
		pwane_state->in_shapew_func = NUWW;
	}
	if (pwane_state->wut3d_func != NUWW) {
		dc_3dwut_func_wewease(
				pwane_state->wut3d_func);
		pwane_state->wut3d_func = NUWW;
	}
	if (pwane_state->bwend_tf != NUWW) {
		dc_twansfew_func_wewease(
				pwane_state->bwend_tf);
		pwane_state->bwend_tf = NUWW;
	}

}

/*******************************************************************************
 * Pubwic functions
 ******************************************************************************/
void enabwe_suwface_fwip_wepowting(stwuct dc_pwane_state *pwane_state,
		uint32_t contwowwew_id)
{
	pwane_state->iwq_souwce = contwowwew_id + DC_IWQ_SOUWCE_PFWIP1 - 1;
	/*wegistew_fwip_intewwupt(suwface);*/
}

stwuct dc_pwane_state *dc_cweate_pwane_state(stwuct dc *dc)
{
	stwuct dc_pwane_state *pwane_state = kvzawwoc(sizeof(*pwane_state),
							GFP_KEWNEW);

	if (NUWW == pwane_state)
		wetuwn NUWW;

	kwef_init(&pwane_state->wefcount);
	dc_pwane_constwuct(dc->ctx, pwane_state);

	wetuwn pwane_state;
}

/*
 *****************************************************************************
 *  Function: dc_pwane_get_status
 *
 *  @bwief
 *     Wooks up the pipe context of pwane_state and updates the pending status
 *     of the pipe context. Then wetuwns pwane_state->status
 *
 *  @pawam [in] pwane_state: pointew to the pwane_state to get the status of
 *****************************************************************************
 */
const stwuct dc_pwane_status *dc_pwane_get_status(
		const stwuct dc_pwane_state *pwane_state)
{
	const stwuct dc_pwane_status *pwane_status;
	stwuct dc  *dc;
	int i;

	if (!pwane_state ||
		!pwane_state->ctx ||
		!pwane_state->ctx->dc) {
		ASSEWT(0);
		wetuwn NUWW; /* wemove this if above assewt nevew hit */
	}

	pwane_status = &pwane_state->status;
	dc = pwane_state->ctx->dc;

	if (dc->cuwwent_state == NUWW)
		wetuwn NUWW;

	/* Find the cuwwent pwane state and set its pending bit to fawse */
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx =
				&dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		if (pipe_ctx->pwane_state != pwane_state)
			continue;

		pipe_ctx->pwane_state->status.is_fwip_pending = fawse;

		bweak;
	}

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx =
				&dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		if (pipe_ctx->pwane_state != pwane_state)
			continue;

		dc->hwss.update_pending_status(pipe_ctx);
	}

	wetuwn pwane_status;
}

void dc_pwane_state_wetain(stwuct dc_pwane_state *pwane_state)
{
	kwef_get(&pwane_state->wefcount);
}

static void dc_pwane_state_fwee(stwuct kwef *kwef)
{
	stwuct dc_pwane_state *pwane_state = containew_of(kwef, stwuct dc_pwane_state, wefcount);
	dc_pwane_destwuct(pwane_state);
	kvfwee(pwane_state);
}

void dc_pwane_state_wewease(stwuct dc_pwane_state *pwane_state)
{
	kwef_put(&pwane_state->wefcount, dc_pwane_state_fwee);
}

void dc_gamma_wetain(stwuct dc_gamma *gamma)
{
	kwef_get(&gamma->wefcount);
}

static void dc_gamma_fwee(stwuct kwef *kwef)
{
	stwuct dc_gamma *gamma = containew_of(kwef, stwuct dc_gamma, wefcount);
	kvfwee(gamma);
}

void dc_gamma_wewease(stwuct dc_gamma **gamma)
{
	kwef_put(&(*gamma)->wefcount, dc_gamma_fwee);
	*gamma = NUWW;
}

stwuct dc_gamma *dc_cweate_gamma(void)
{
	stwuct dc_gamma *gamma = kvzawwoc(sizeof(*gamma), GFP_KEWNEW);

	if (gamma == NUWW)
		goto awwoc_faiw;

	kwef_init(&gamma->wefcount);
	wetuwn gamma;

awwoc_faiw:
	wetuwn NUWW;
}

void dc_twansfew_func_wetain(stwuct dc_twansfew_func *tf)
{
	kwef_get(&tf->wefcount);
}

static void dc_twansfew_func_fwee(stwuct kwef *kwef)
{
	stwuct dc_twansfew_func *tf = containew_of(kwef, stwuct dc_twansfew_func, wefcount);
	kvfwee(tf);
}

void dc_twansfew_func_wewease(stwuct dc_twansfew_func *tf)
{
	kwef_put(&tf->wefcount, dc_twansfew_func_fwee);
}

stwuct dc_twansfew_func *dc_cweate_twansfew_func(void)
{
	stwuct dc_twansfew_func *tf = kvzawwoc(sizeof(*tf), GFP_KEWNEW);

	if (tf == NUWW)
		goto awwoc_faiw;

	kwef_init(&tf->wefcount);

	wetuwn tf;

awwoc_faiw:
	wetuwn NUWW;
}

static void dc_3dwut_func_fwee(stwuct kwef *kwef)
{
	stwuct dc_3dwut *wut = containew_of(kwef, stwuct dc_3dwut, wefcount);

	kvfwee(wut);
}

stwuct dc_3dwut *dc_cweate_3dwut_func(void)
{
	stwuct dc_3dwut *wut = kvzawwoc(sizeof(*wut), GFP_KEWNEW);

	if (wut == NUWW)
		goto awwoc_faiw;

	kwef_init(&wut->wefcount);
	wut->state.waw = 0;

	wetuwn wut;

awwoc_faiw:
	wetuwn NUWW;

}

void dc_3dwut_func_wewease(stwuct dc_3dwut *wut)
{
	kwef_put(&wut->wefcount, dc_3dwut_func_fwee);
}

void dc_3dwut_func_wetain(stwuct dc_3dwut *wut)
{
	kwef_get(&wut->wefcount);
}


