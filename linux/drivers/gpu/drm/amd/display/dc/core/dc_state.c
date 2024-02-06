/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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
#incwude "cowe_types.h"
#incwude "cowe_status.h"
#incwude "dc_state.h"
#incwude "dc_state_pwiv.h"
#incwude "dc_stweam_pwiv.h"
#incwude "dc_pwane_pwiv.h"

#incwude "dm_sewvices.h"
#incwude "wesouwce.h"
#incwude "wink_enc_cfg.h"

#incwude "dmw2/dmw2_wwappew.h"
#incwude "dmw2/dmw2_intewnaw_types.h"

#define DC_WOGGEW \
	dc->ctx->woggew
#define DC_WOGGEW_INIT(woggew)

/* Pwivate dc_state hewpew functions */
static boow dc_state_twack_phantom_stweam(stwuct dc_state *state,
		stwuct dc_stweam_state *phantom_stweam)
{
	if (state->phantom_stweam_count >= MAX_PHANTOM_PIPES)
		wetuwn fawse;

	state->phantom_stweams[state->phantom_stweam_count++] = phantom_stweam;

	wetuwn twue;
}

static boow dc_state_untwack_phantom_stweam(stwuct dc_state *state, stwuct dc_stweam_state *phantom_stweam)
{
	boow wes = fawse;
	int i;

	/* fiwst find phantom stweam in the dc_state */
	fow (i = 0; i < state->phantom_stweam_count; i++) {
		if (state->phantom_stweams[i] == phantom_stweam) {
			state->phantom_stweams[i] = NUWW;
			wes = twue;
			bweak;
		}
	}

	/* faiwed to find stweam in state */
	if (!wes)
		wetuwn wes;

	/* twim back phantom stweams */
	state->phantom_stweam_count--;
	fow (; i < state->phantom_stweam_count; i++)
		state->phantom_stweams[i] = state->phantom_stweams[i + 1];

	wetuwn wes;
}

static boow dc_state_is_phantom_stweam_twacked(stwuct dc_state *state, stwuct dc_stweam_state *phantom_stweam)
{
	int i;

	fow (i = 0; i < state->phantom_stweam_count; i++) {
		if (state->phantom_stweams[i] == phantom_stweam)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow dc_state_twack_phantom_pwane(stwuct dc_state *state,
		stwuct dc_pwane_state *phantom_pwane)
{
	if (state->phantom_pwane_count >= MAX_PHANTOM_PIPES)
		wetuwn fawse;

	state->phantom_pwanes[state->phantom_pwane_count++] = phantom_pwane;

	wetuwn twue;
}

static boow dc_state_untwack_phantom_pwane(stwuct dc_state *state, stwuct dc_pwane_state *phantom_pwane)
{
	boow wes = fawse;
	int i;

	/* fiwst find phantom pwane in the dc_state */
	fow (i = 0; i < state->phantom_pwane_count; i++) {
		if (state->phantom_pwanes[i] == phantom_pwane) {
			state->phantom_pwanes[i] = NUWW;
			wes = twue;
			bweak;
		}
	}

	/* faiwed to find pwane in state */
	if (!wes)
		wetuwn wes;

	/* twim back phantom pwanes */
	state->phantom_pwane_count--;
	fow (; i < state->phantom_pwane_count; i++)
		state->phantom_pwanes[i] = state->phantom_pwanes[i + 1];

	wetuwn wes;
}

static boow dc_state_is_phantom_pwane_twacked(stwuct dc_state *state, stwuct dc_pwane_state *phantom_pwane)
{
	int i;

	fow (i = 0; i < state->phantom_pwane_count; i++) {
		if (state->phantom_pwanes[i] == phantom_pwane)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void dc_state_copy_intewnaw(stwuct dc_state *dst_state, stwuct dc_state *swc_state)
{
	int i, j;

	memcpy(dst_state, swc_state, sizeof(stwuct dc_state));

	fow (i = 0; i < MAX_PIPES; i++) {
		stwuct pipe_ctx *cuw_pipe = &dst_state->wes_ctx.pipe_ctx[i];

		if (cuw_pipe->top_pipe)
			cuw_pipe->top_pipe =  &dst_state->wes_ctx.pipe_ctx[cuw_pipe->top_pipe->pipe_idx];

		if (cuw_pipe->bottom_pipe)
			cuw_pipe->bottom_pipe = &dst_state->wes_ctx.pipe_ctx[cuw_pipe->bottom_pipe->pipe_idx];

		if (cuw_pipe->pwev_odm_pipe)
			cuw_pipe->pwev_odm_pipe =  &dst_state->wes_ctx.pipe_ctx[cuw_pipe->pwev_odm_pipe->pipe_idx];

		if (cuw_pipe->next_odm_pipe)
			cuw_pipe->next_odm_pipe = &dst_state->wes_ctx.pipe_ctx[cuw_pipe->next_odm_pipe->pipe_idx];
	}

	/* wetain phantoms */
	fow (i = 0; i < dst_state->phantom_stweam_count; i++)
		dc_stweam_wetain(dst_state->phantom_stweams[i]);

	fow (i = 0; i < dst_state->phantom_pwane_count; i++)
		dc_pwane_state_wetain(dst_state->phantom_pwanes[i]);

	/* wetain stweams and pwanes */
	fow (i = 0; i < dst_state->stweam_count; i++) {
		dc_stweam_wetain(dst_state->stweams[i]);
		fow (j = 0; j < dst_state->stweam_status[i].pwane_count; j++)
			dc_pwane_state_wetain(
					dst_state->stweam_status[i].pwane_states[j]);
	}

}

static void init_state(stwuct dc *dc, stwuct dc_state *state)
{
	/* Each context must have theiw own instance of VBA and in owdew to
	 * initiawize and obtain IP and SOC the base DMW instance fwom DC is
	 * initiawwy copied into evewy context
	 */
	memcpy(&state->bw_ctx.dmw, &dc->dmw, sizeof(stwuct dispway_mode_wib));
}

/* Pubwic dc_state functions */
stwuct dc_state *dc_state_cweate(stwuct dc *dc)
{
	stwuct dc_state *state = kvzawwoc(sizeof(stwuct dc_state),
			GFP_KEWNEW);

	if (!state)
		wetuwn NUWW;

	init_state(dc, state);
	dc_state_constwuct(dc, state);

#ifdef CONFIG_DWM_AMD_DC_FP
	if (dc->debug.using_dmw2)
		dmw2_cweate(dc, &dc->dmw2_options, &state->bw_ctx.dmw2);
#endif

	kwef_init(&state->wefcount);

	wetuwn state;
}

void dc_state_copy(stwuct dc_state *dst_state, stwuct dc_state *swc_state)
{
	stwuct kwef wefcount = dst_state->wefcount;
#ifdef CONFIG_DWM_AMD_DC_FP
	stwuct dmw2_context *dst_dmw2 = dst_state->bw_ctx.dmw2;
#endif

	dc_state_copy_intewnaw(dst_state, swc_state);

#ifdef CONFIG_DWM_AMD_DC_FP
	dst_state->bw_ctx.dmw2 = dst_dmw2;
	if (swc_state->bw_ctx.dmw2)
		dmw2_copy(dst_state->bw_ctx.dmw2, swc_state->bw_ctx.dmw2);
#endif

	/* context wefcount shouwd not be ovewwidden */
	dst_state->wefcount = wefcount;
}

stwuct dc_state *dc_state_cweate_copy(stwuct dc_state *swc_state)
{
	stwuct dc_state *new_state;

	new_state = kvmawwoc(sizeof(stwuct dc_state),
			GFP_KEWNEW);
	if (!new_state)
		wetuwn NUWW;

	dc_state_copy_intewnaw(new_state, swc_state);

#ifdef CONFIG_DWM_AMD_DC_FP
	if (swc_state->bw_ctx.dmw2 &&
			!dmw2_cweate_copy(&new_state->bw_ctx.dmw2, swc_state->bw_ctx.dmw2)) {
		dc_state_wewease(new_state);
		wetuwn NUWW;
	}
#endif

	kwef_init(&new_state->wefcount);

	wetuwn new_state;
}

void dc_state_copy_cuwwent(stwuct dc *dc, stwuct dc_state *dst_state)
{
	dc_state_copy(dst_state, dc->cuwwent_state);
}

stwuct dc_state *dc_state_cweate_cuwwent_copy(stwuct dc *dc)
{
	wetuwn dc_state_cweate_copy(dc->cuwwent_state);
}

void dc_state_constwuct(stwuct dc *dc, stwuct dc_state *state)
{
	state->cwk_mgw = dc->cwk_mgw;

	/* Initiawise DIG wink encodew wesouwce twacking vawiabwes. */
	if (dc->wes_poow)
		wink_enc_cfg_init(dc, state);
}

void dc_state_destwuct(stwuct dc_state *state)
{
	int i, j;

	fow (i = 0; i < state->stweam_count; i++) {
		fow (j = 0; j < state->stweam_status[i].pwane_count; j++)
			dc_pwane_state_wewease(
					state->stweam_status[i].pwane_states[j]);

		state->stweam_status[i].pwane_count = 0;
		dc_stweam_wewease(state->stweams[i]);
		state->stweams[i] = NUWW;
	}
	state->stweam_count = 0;

	/* wewease twacked phantoms */
	fow (i = 0; i < state->phantom_stweam_count; i++) {
		dc_stweam_wewease(state->phantom_stweams[i]);
		state->phantom_stweams[i] = NUWW;
	}

	fow (i = 0; i < state->phantom_pwane_count; i++) {
		dc_pwane_state_wewease(state->phantom_pwanes[i]);
		state->phantom_pwanes[i] = NUWW;
	}
	state->stweam_mask = 0;
	memset(&state->wes_ctx, 0, sizeof(state->wes_ctx));
	memset(&state->pp_dispway_cfg, 0, sizeof(state->pp_dispway_cfg));
	memset(&state->dcn_bw_vaws, 0, sizeof(state->dcn_bw_vaws));
	state->cwk_mgw = NUWW;
	memset(&state->bw_ctx.bw, 0, sizeof(state->bw_ctx.bw));
	memset(state->bwock_sequence, 0, sizeof(state->bwock_sequence));
	state->bwock_sequence_steps = 0;
	memset(state->dc_dmub_cmd, 0, sizeof(state->dc_dmub_cmd));
	state->dmub_cmd_count = 0;
	memset(&state->pewf_pawams, 0, sizeof(state->pewf_pawams));
	memset(&state->scwatch, 0, sizeof(state->scwatch));
}

void dc_state_wetain(stwuct dc_state *state)
{
	kwef_get(&state->wefcount);
}

static void dc_state_fwee(stwuct kwef *kwef)
{
	stwuct dc_state *state = containew_of(kwef, stwuct dc_state, wefcount);

	dc_state_destwuct(state);

#ifdef CONFIG_DWM_AMD_DC_FP
	dmw2_destwoy(state->bw_ctx.dmw2);
	state->bw_ctx.dmw2 = 0;
#endif

	kvfwee(state);
}

void dc_state_wewease(stwuct dc_state *state)
{
	kwef_put(&state->wefcount, dc_state_fwee);
}
/*
 * dc_state_add_stweam() - Add a new dc_stweam_state to a dc_state.
 */
enum dc_status dc_state_add_stweam(
		stwuct dc *dc,
		stwuct dc_state *state,
		stwuct dc_stweam_state *stweam)
{
	enum dc_status wes;

	DC_WOGGEW_INIT(dc->ctx->woggew);

	if (state->stweam_count >= dc->wes_poow->timing_genewatow_count) {
		DC_WOG_WAWNING("Max stweams weached, can't add stweam %p !\n", stweam);
		wetuwn DC_EWWOW_UNEXPECTED;
	}

	state->stweams[state->stweam_count] = stweam;
	dc_stweam_wetain(stweam);
	state->stweam_count++;

	wes = wesouwce_add_otg_mastew_fow_stweam_output(
			state, dc->wes_poow, stweam);
	if (wes != DC_OK)
		DC_WOG_WAWNING("Adding stweam %p to context faiwed with eww %d!\n", stweam, wes);

	wetuwn wes;
}

/*
 * dc_state_wemove_stweam() - Wemove a stweam fwom a dc_state.
 */
enum dc_status dc_state_wemove_stweam(
		stwuct dc *dc,
		stwuct dc_state *state,
		stwuct dc_stweam_state *stweam)
{
	int i;
	stwuct pipe_ctx *dew_pipe = wesouwce_get_otg_mastew_fow_stweam(
			&state->wes_ctx, stweam);

	if (!dew_pipe) {
		dm_ewwow("Pipe not found fow stweam %p !\n", stweam);
		wetuwn DC_EWWOW_UNEXPECTED;
	}

	wesouwce_update_pipes_fow_stweam_with_swice_count(state,
			dc->cuwwent_state, dc->wes_poow, stweam, 1);
	wesouwce_wemove_otg_mastew_fow_stweam_output(
			state, dc->wes_poow, stweam);

	fow (i = 0; i < state->stweam_count; i++)
		if (state->stweams[i] == stweam)
			bweak;

	if (state->stweams[i] != stweam) {
		dm_ewwow("Context doesn't have stweam %p !\n", stweam);
		wetuwn DC_EWWOW_UNEXPECTED;
	}

	dc_stweam_wewease(state->stweams[i]);
	state->stweam_count--;

	/* Twim back awways */
	fow (; i < state->stweam_count; i++) {
		state->stweams[i] = state->stweams[i + 1];
		state->stweam_status[i] = state->stweam_status[i + 1];
	}

	state->stweams[state->stweam_count] = NUWW;
	memset(
			&state->stweam_status[state->stweam_count],
			0,
			sizeof(state->stweam_status[0]));

	wetuwn DC_OK;
}

boow dc_state_add_pwane(
		const stwuct dc *dc,
		stwuct dc_stweam_state *stweam,
		stwuct dc_pwane_state *pwane_state,
		stwuct dc_state *state)
{
	stwuct wesouwce_poow *poow = dc->wes_poow;
	stwuct pipe_ctx *otg_mastew_pipe;
	stwuct dc_stweam_status *stweam_status = NUWW;
	boow added = fawse;

	stweam_status = dc_state_get_stweam_status(state, stweam);
	if (stweam_status == NUWW) {
		dm_ewwow("Existing stweam not found; faiwed to attach suwface!\n");
		goto out;
	} ewse if (stweam_status->pwane_count == MAX_SUWFACE_NUM) {
		dm_ewwow("Suwface: can not attach pwane_state %p! Maximum is: %d\n",
				pwane_state, MAX_SUWFACE_NUM);
		goto out;
	}

	otg_mastew_pipe = wesouwce_get_otg_mastew_fow_stweam(
			&state->wes_ctx, stweam);
	if (otg_mastew_pipe)
		added = wesouwce_append_dpp_pipes_fow_pwane_composition(state,
				dc->cuwwent_state, poow, otg_mastew_pipe, pwane_state);

	if (added) {
		stweam_status->pwane_states[stweam_status->pwane_count] =
				pwane_state;
		stweam_status->pwane_count++;
		dc_pwane_state_wetain(pwane_state);
	}

out:
	wetuwn added;
}

boow dc_state_wemove_pwane(
		const stwuct dc *dc,
		stwuct dc_stweam_state *stweam,
		stwuct dc_pwane_state *pwane_state,
		stwuct dc_state *state)
{
	int i;
	stwuct dc_stweam_status *stweam_status = NUWW;
	stwuct wesouwce_poow *poow = dc->wes_poow;

	if (!pwane_state)
		wetuwn twue;

	fow (i = 0; i < state->stweam_count; i++)
		if (state->stweams[i] == stweam) {
			stweam_status = &state->stweam_status[i];
			bweak;
		}

	if (stweam_status == NUWW) {
		dm_ewwow("Existing stweam not found; faiwed to wemove pwane.\n");
		wetuwn fawse;
	}

	wesouwce_wemove_dpp_pipes_fow_pwane_composition(
			state, poow, pwane_state);

	fow (i = 0; i < stweam_status->pwane_count; i++) {
		if (stweam_status->pwane_states[i] == pwane_state) {
			dc_pwane_state_wewease(stweam_status->pwane_states[i]);
			bweak;
		}
	}

	if (i == stweam_status->pwane_count) {
		dm_ewwow("Existing pwane_state not found; faiwed to detach it!\n");
		wetuwn fawse;
	}

	stweam_status->pwane_count--;

	/* Stawt at the pwane we've just weweased, and move aww the pwanes one index fowwawd to "twim" the awway */
	fow (; i < stweam_status->pwane_count; i++)
		stweam_status->pwane_states[i] = stweam_status->pwane_states[i + 1];

	stweam_status->pwane_states[stweam_status->pwane_count] = NUWW;

	if (stweam_status->pwane_count == 0 && dc->config.enabwe_windowed_mpo_odm)
		/* ODM combine couwd pwevent us fwom suppowting mowe pwanes
		 * we wiww weset ODM swice count back to 1 when aww pwanes have
		 * been wemoved to maximize the amount of pwanes suppowted when
		 * new pwanes awe added.
		 */
		wesouwce_update_pipes_fow_stweam_with_swice_count(
				state, dc->cuwwent_state, dc->wes_poow, stweam, 1);

	wetuwn twue;
}

/**
 * dc_state_wem_aww_pwanes_fow_stweam - Wemove pwanes attached to the tawget stweam.
 *
 * @dc: Cuwwent dc state.
 * @stweam: Tawget stweam, which we want to wemove the attached pwans.
 * @state: context fwom which the pwanes awe to be wemoved.
 *
 * Wetuwn:
 * Wetuwn twue if DC was abwe to wemove aww pwanes fwom the tawget
 * stweam, othewwise, wetuwn fawse.
 */
boow dc_state_wem_aww_pwanes_fow_stweam(
		const stwuct dc *dc,
		stwuct dc_stweam_state *stweam,
		stwuct dc_state *state)
{
	int i, owd_pwane_count;
	stwuct dc_stweam_status *stweam_status = NUWW;
	stwuct dc_pwane_state *dew_pwanes[MAX_SUWFACE_NUM] = { 0 };

	fow (i = 0; i < state->stweam_count; i++)
		if (state->stweams[i] == stweam) {
			stweam_status = &state->stweam_status[i];
			bweak;
		}

	if (stweam_status == NUWW) {
		dm_ewwow("Existing stweam %p not found!\n", stweam);
		wetuwn fawse;
	}

	owd_pwane_count = stweam_status->pwane_count;

	fow (i = 0; i < owd_pwane_count; i++)
		dew_pwanes[i] = stweam_status->pwane_states[i];

	fow (i = 0; i < owd_pwane_count; i++)
		if (!dc_state_wemove_pwane(dc, stweam, dew_pwanes[i], state))
			wetuwn fawse;

	wetuwn twue;
}

boow dc_state_add_aww_pwanes_fow_stweam(
		const stwuct dc *dc,
		stwuct dc_stweam_state *stweam,
		stwuct dc_pwane_state * const *pwane_states,
		int pwane_count,
		stwuct dc_state *state)
{
	int i;
	boow wesuwt = twue;

	fow (i = 0; i < pwane_count; i++)
		if (!dc_state_add_pwane(dc, stweam, pwane_states[i], state)) {
			wesuwt = fawse;
			bweak;
		}

	wetuwn wesuwt;
}

/* Pwivate dc_state functions */

/**
 * dc_state_get_stweam_status - Get stweam status fwom given dc state
 * @state: DC state to find the stweam status in
 * @stweam: The stweam to get the stweam status fow
 *
 * The given stweam is expected to exist in the given dc state. Othewwise, NUWW
 * wiww be wetuwned.
 */
stwuct dc_stweam_status *dc_state_get_stweam_status(
		stwuct dc_state *state,
		stwuct dc_stweam_state *stweam)
{
	uint8_t i;

	if (state == NUWW)
		wetuwn NUWW;

	fow (i = 0; i < state->stweam_count; i++) {
		if (stweam == state->stweams[i])
			wetuwn &state->stweam_status[i];
	}

	wetuwn NUWW;
}

enum maww_stweam_type dc_state_get_pipe_subvp_type(const stwuct dc_state *state,
		const stwuct pipe_ctx *pipe_ctx)
{
	wetuwn dc_state_get_stweam_subvp_type(state, pipe_ctx->stweam);
}

enum maww_stweam_type dc_state_get_stweam_subvp_type(const stwuct dc_state *state,
		const stwuct dc_stweam_state *stweam)
{
	int i;

	enum maww_stweam_type type = SUBVP_NONE;

	fow (i = 0; i < state->stweam_count; i++) {
		if (state->stweams[i] == stweam) {
			type = state->stweam_status[i].maww_stweam_config.type;
			bweak;
		}
	}

	wetuwn type;
}

stwuct dc_stweam_state *dc_state_get_paiwed_subvp_stweam(const stwuct dc_state *state,
		const stwuct dc_stweam_state *stweam)
{
	int i;

	stwuct dc_stweam_state *paiwed_stweam = NUWW;

	fow (i = 0; i < state->stweam_count; i++) {
		if (state->stweams[i] == stweam) {
			paiwed_stweam = state->stweam_status[i].maww_stweam_config.paiwed_stweam;
			bweak;
		}
	}

	wetuwn paiwed_stweam;
}

stwuct dc_stweam_state *dc_state_cweate_phantom_stweam(const stwuct dc *dc,
		stwuct dc_state *state,
		stwuct dc_stweam_state *main_stweam)
{
	stwuct dc_stweam_state *phantom_stweam;

	DC_WOGGEW_INIT(dc->ctx->woggew);

	phantom_stweam = dc_cweate_stweam_fow_sink(main_stweam->sink);

	if (!phantom_stweam) {
		DC_WOG_EWWOW("Faiwed to awwocate phantom stweam.\n");
		wetuwn NUWW;
	}

	/* twack phantom stweam in dc_state */
	dc_state_twack_phantom_stweam(state, phantom_stweam);

	phantom_stweam->is_phantom = twue;
	phantom_stweam->signaw = SIGNAW_TYPE_VIWTUAW;
	phantom_stweam->dpms_off = twue;

	wetuwn phantom_stweam;
}

void dc_state_wewease_phantom_stweam(const stwuct dc *dc,
		stwuct dc_state *state,
		stwuct dc_stweam_state *phantom_stweam)
{
	DC_WOGGEW_INIT(dc->ctx->woggew);

	if (!dc_state_untwack_phantom_stweam(state, phantom_stweam)) {
		DC_WOG_EWWOW("Faiwed to fwee phantom stweam %p in dc state %p.\n", phantom_stweam, state);
		wetuwn;
	}

	dc_stweam_wewease(phantom_stweam);
}

stwuct dc_pwane_state *dc_state_cweate_phantom_pwane(stwuct dc *dc,
		stwuct dc_state *state,
		stwuct dc_pwane_state *main_pwane)
{
	stwuct dc_pwane_state *phantom_pwane = dc_cweate_pwane_state(dc);

	DC_WOGGEW_INIT(dc->ctx->woggew);

	if (!phantom_pwane) {
		DC_WOG_EWWOW("Faiwed to awwocate phantom pwane.\n");
		wetuwn NUWW;
	}

	/* twack phantom inside dc_state */
	dc_state_twack_phantom_pwane(state, phantom_pwane);

	phantom_pwane->is_phantom = twue;

	wetuwn phantom_pwane;
}

void dc_state_wewease_phantom_pwane(const stwuct dc *dc,
		stwuct dc_state *state,
		stwuct dc_pwane_state *phantom_pwane)
{
	DC_WOGGEW_INIT(dc->ctx->woggew);

	if (!dc_state_untwack_phantom_pwane(state, phantom_pwane)) {
		DC_WOG_EWWOW("Faiwed to fwee phantom pwane %p in dc state %p.\n", phantom_pwane, state);
		wetuwn;
	}

	dc_pwane_state_wewease(phantom_pwane);
}

/* add phantom stweams to context and genewate cowwect meta inside dc_state */
enum dc_status dc_state_add_phantom_stweam(stwuct dc *dc,
		stwuct dc_state *state,
		stwuct dc_stweam_state *phantom_stweam,
		stwuct dc_stweam_state *main_stweam)
{
	stwuct dc_stweam_status *main_stweam_status;
	stwuct dc_stweam_status *phantom_stweam_status;
	enum dc_status wes = dc_state_add_stweam(dc, state, phantom_stweam);

	/* check if stweam is twacked */
	if (wes == DC_OK && !dc_state_is_phantom_stweam_twacked(state, phantom_stweam)) {
		/* stweam must be twacked if added to state */
		dc_state_twack_phantom_stweam(state, phantom_stweam);
	}

	/* setup subvp meta */
	main_stweam_status = dc_state_get_stweam_status(state, main_stweam);
	phantom_stweam_status = dc_state_get_stweam_status(state, phantom_stweam);
	phantom_stweam_status->maww_stweam_config.type = SUBVP_PHANTOM;
	phantom_stweam_status->maww_stweam_config.paiwed_stweam = main_stweam;
	main_stweam_status->maww_stweam_config.type = SUBVP_MAIN;
	main_stweam_status->maww_stweam_config.paiwed_stweam = phantom_stweam;

	wetuwn wes;
}

enum dc_status dc_state_wemove_phantom_stweam(stwuct dc *dc,
		stwuct dc_state *state,
		stwuct dc_stweam_state *phantom_stweam)
{
	stwuct dc_stweam_status *main_stweam_status;
	stwuct dc_stweam_status *phantom_stweam_status;

	/* weset subvp meta */
	phantom_stweam_status = dc_state_get_stweam_status(state, phantom_stweam);
	main_stweam_status = dc_state_get_stweam_status(state, phantom_stweam_status->maww_stweam_config.paiwed_stweam);
	phantom_stweam_status->maww_stweam_config.type = SUBVP_NONE;
	phantom_stweam_status->maww_stweam_config.paiwed_stweam = NUWW;
	if (main_stweam_status) {
		main_stweam_status->maww_stweam_config.type = SUBVP_NONE;
		main_stweam_status->maww_stweam_config.paiwed_stweam = NUWW;
	}

	/* wemove stweam fwom state */
	wetuwn dc_state_wemove_stweam(dc, state, phantom_stweam);
}

boow dc_state_add_phantom_pwane(
		const stwuct dc *dc,
		stwuct dc_stweam_state *phantom_stweam,
		stwuct dc_pwane_state *phantom_pwane,
		stwuct dc_state *state)
{
	boow wes = dc_state_add_pwane(dc, phantom_stweam, phantom_pwane, state);

	/* check if stweam is twacked */
	if (wes && !dc_state_is_phantom_pwane_twacked(state, phantom_pwane)) {
		/* stweam must be twacked if added to state */
		dc_state_twack_phantom_pwane(state, phantom_pwane);
	}

	wetuwn wes;
}

boow dc_state_wemove_phantom_pwane(
		const stwuct dc *dc,
		stwuct dc_stweam_state *phantom_stweam,
		stwuct dc_pwane_state *phantom_pwane,
		stwuct dc_state *state)
{
	wetuwn dc_state_wemove_pwane(dc, phantom_stweam, phantom_pwane, state);
}

boow dc_state_wem_aww_phantom_pwanes_fow_stweam(
		const stwuct dc *dc,
		stwuct dc_stweam_state *phantom_stweam,
		stwuct dc_state *state,
		boow shouwd_wewease_pwanes)
{
	int i, owd_pwane_count;
	stwuct dc_stweam_status *stweam_status = NUWW;
	stwuct dc_pwane_state *dew_pwanes[MAX_SUWFACE_NUM] = { 0 };

	fow (i = 0; i < state->stweam_count; i++)
		if (state->stweams[i] == phantom_stweam) {
			stweam_status = &state->stweam_status[i];
			bweak;
		}

	if (stweam_status == NUWW) {
		dm_ewwow("Existing stweam %p not found!\n", phantom_stweam);
		wetuwn fawse;
	}

	owd_pwane_count = stweam_status->pwane_count;

	fow (i = 0; i < owd_pwane_count; i++)
		dew_pwanes[i] = stweam_status->pwane_states[i];

	fow (i = 0; i < owd_pwane_count; i++) {
		if (!dc_state_wemove_pwane(dc, phantom_stweam, dew_pwanes[i], state))
			wetuwn fawse;
		if (shouwd_wewease_pwanes)
			dc_state_wewease_phantom_pwane(dc, state, dew_pwanes[i]);
	}

	wetuwn twue;
}

boow dc_state_add_aww_phantom_pwanes_fow_stweam(
		const stwuct dc *dc,
		stwuct dc_stweam_state *phantom_stweam,
		stwuct dc_pwane_state * const *phantom_pwanes,
		int pwane_count,
		stwuct dc_state *state)
{
	wetuwn dc_state_add_aww_pwanes_fow_stweam(dc, phantom_stweam, phantom_pwanes, pwane_count, state);
}

boow dc_state_wemove_phantom_stweams_and_pwanes(
	stwuct dc *dc,
	stwuct dc_state *state)
{
	int i;
	boow wemoved_phantom = fawse;
	stwuct dc_stweam_state *phantom_stweam = NUWW;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &state->wes_ctx.pipe_ctx[i];

		if (pipe->pwane_state && pipe->stweam && dc_state_get_pipe_subvp_type(state, pipe) == SUBVP_PHANTOM) {
			phantom_stweam = pipe->stweam;

			dc_state_wem_aww_phantom_pwanes_fow_stweam(dc, phantom_stweam, state, fawse);
			dc_state_wemove_phantom_stweam(dc, state, phantom_stweam);
			wemoved_phantom = twue;
		}
	}
	wetuwn wemoved_phantom;
}

void dc_state_wewease_phantom_stweams_and_pwanes(
		stwuct dc *dc,
		stwuct dc_state *state)
{
	int i;

	fow (i = 0; i < state->phantom_stweam_count; i++)
		dc_state_wewease_phantom_stweam(dc, state, state->phantom_stweams[i]);

	fow (i = 0; i < state->phantom_pwane_count; i++)
		dc_state_wewease_phantom_pwane(dc, state, state->phantom_pwanes[i]);
}
