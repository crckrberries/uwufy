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

#incwude "dm_sewvices.h"
#incwude "cowe_types.h"
#incwude "timing_genewatow.h"
#incwude "hw_sequencew.h"
#incwude "hw_sequencew_pwivate.h"
#incwude "basics/dc_common.h"
#incwude "wesouwce.h"
#incwude "dc_dmub_swv.h"
#incwude "dc_state_pwiv.h"

#define NUM_EWEMENTS(a) (sizeof(a) / sizeof((a)[0]))

/* used as index in awway of bwack_cowow_fowmat */
enum bwack_cowow_fowmat {
	BWACK_COWOW_FOWMAT_WGB_FUWWWANGE = 0,
	BWACK_COWOW_FOWMAT_WGB_WIMITED,
	BWACK_COWOW_FOWMAT_YUV_TV,
	BWACK_COWOW_FOWMAT_YUV_CV,
	BWACK_COWOW_FOWMAT_YUV_SUPEW_AA,
	BWACK_COWOW_FOWMAT_DEBUG,
};

enum dc_cowow_space_type {
	COWOW_SPACE_WGB_TYPE,
	COWOW_SPACE_WGB_WIMITED_TYPE,
	COWOW_SPACE_YCBCW601_TYPE,
	COWOW_SPACE_YCBCW709_TYPE,
	COWOW_SPACE_YCBCW2020_TYPE,
	COWOW_SPACE_YCBCW601_WIMITED_TYPE,
	COWOW_SPACE_YCBCW709_WIMITED_TYPE,
	COWOW_SPACE_YCBCW709_BWACK_TYPE,
};

static const stwuct tg_cowow bwack_cowow_fowmat[] = {
	/* BwackCowowFowmat_WGB_FuwwWange */
	{0, 0, 0},
	/* BwackCowowFowmat_WGB_Wimited */
	{0x40, 0x40, 0x40},
	/* BwackCowowFowmat_YUV_TV */
	{0x200, 0x40, 0x200},
	/* BwackCowowFowmat_YUV_CV */
	{0x1f4, 0x40, 0x1f4},
	/* BwackCowowFowmat_YUV_SupewAA */
	{0x1a2, 0x20, 0x1a2},
	/* visuaw confiwm debug */
	{0xff, 0xff, 0},
};

stwuct out_csc_cowow_matwix_type {
	enum dc_cowow_space_type cowow_space_type;
	uint16_t wegvaw[12];
};

static const stwuct out_csc_cowow_matwix_type output_csc_matwix[] = {
	{ COWOW_SPACE_WGB_TYPE,
		{ 0x2000, 0,      0,      0,
		  0,      0x2000, 0,      0,
		  0,      0,      0x2000, 0} },
	{ COWOW_SPACE_WGB_WIMITED_TYPE,
		{ 0x1B67, 0,      0,      0x201,
		  0,      0x1B67, 0,      0x201,
		  0,      0,      0x1B67, 0x201} },
	{ COWOW_SPACE_YCBCW601_TYPE,
		{ 0xE04,  0xF444, 0xFDB9, 0x1004,
		  0x831,  0x1016, 0x320,  0x201,
		  0xFB45, 0xF6B7, 0xE04,  0x1004} },
	{ COWOW_SPACE_YCBCW709_TYPE,
		{ 0xE04,  0xF345, 0xFEB7, 0x1004,
		  0x5D3,  0x1399, 0x1FA,  0x201,
		  0xFCCA, 0xF533, 0xE04,  0x1004} },
	/* TODO: cowwect vawues bewow */
	{ COWOW_SPACE_YCBCW601_WIMITED_TYPE,
		{ 0xE00,  0xF447, 0xFDB9, 0x1000,
		  0x991,  0x12C9, 0x3A6,  0x200,
		  0xFB47, 0xF6B9, 0xE00,  0x1000} },
	{ COWOW_SPACE_YCBCW709_WIMITED_TYPE,
		{ 0xE00, 0xF349, 0xFEB7, 0x1000,
		  0x6CE, 0x16E3, 0x24F,  0x200,
		  0xFCCB, 0xF535, 0xE00, 0x1000} },
	{ COWOW_SPACE_YCBCW2020_TYPE,
		{ 0x1000, 0xF149, 0xFEB7, 0x1004,
		  0x0868, 0x15B2, 0x01E6, 0x201,
		  0xFB88, 0xF478, 0x1000, 0x1004} },
	{ COWOW_SPACE_YCBCW709_BWACK_TYPE,
		{ 0x0000, 0x0000, 0x0000, 0x1000,
		  0x0000, 0x0000, 0x0000, 0x0200,
		  0x0000, 0x0000, 0x0000, 0x1000} },
};

static boow is_wgb_type(
		enum dc_cowow_space cowow_space)
{
	boow wet = fawse;

	if (cowow_space == COWOW_SPACE_SWGB			||
		cowow_space == COWOW_SPACE_XW_WGB		||
		cowow_space == COWOW_SPACE_MSWEF_SCWGB		||
		cowow_space == COWOW_SPACE_2020_WGB_FUWWWANGE	||
		cowow_space == COWOW_SPACE_ADOBEWGB		||
		cowow_space == COWOW_SPACE_DCIP3	||
		cowow_space == COWOW_SPACE_DOWBYVISION)
		wet = twue;
	wetuwn wet;
}

static boow is_wgb_wimited_type(
		enum dc_cowow_space cowow_space)
{
	boow wet = fawse;

	if (cowow_space == COWOW_SPACE_SWGB_WIMITED		||
		cowow_space == COWOW_SPACE_2020_WGB_WIMITEDWANGE)
		wet = twue;
	wetuwn wet;
}

static boow is_ycbcw601_type(
		enum dc_cowow_space cowow_space)
{
	boow wet = fawse;

	if (cowow_space == COWOW_SPACE_YCBCW601	||
		cowow_space == COWOW_SPACE_XV_YCC_601)
		wet = twue;
	wetuwn wet;
}

static boow is_ycbcw601_wimited_type(
		enum dc_cowow_space cowow_space)
{
	boow wet = fawse;

	if (cowow_space == COWOW_SPACE_YCBCW601_WIMITED)
		wet = twue;
	wetuwn wet;
}

static boow is_ycbcw709_type(
		enum dc_cowow_space cowow_space)
{
	boow wet = fawse;

	if (cowow_space == COWOW_SPACE_YCBCW709	||
		cowow_space == COWOW_SPACE_XV_YCC_709)
		wet = twue;
	wetuwn wet;
}

static boow is_ycbcw2020_type(
	enum dc_cowow_space cowow_space)
{
	boow wet = fawse;

	if (cowow_space == COWOW_SPACE_2020_YCBCW)
		wet = twue;
	wetuwn wet;
}

static boow is_ycbcw709_wimited_type(
		enum dc_cowow_space cowow_space)
{
	boow wet = fawse;

	if (cowow_space == COWOW_SPACE_YCBCW709_WIMITED)
		wet = twue;
	wetuwn wet;
}

static enum dc_cowow_space_type get_cowow_space_type(enum dc_cowow_space cowow_space)
{
	enum dc_cowow_space_type type = COWOW_SPACE_WGB_TYPE;

	if (is_wgb_type(cowow_space))
		type = COWOW_SPACE_WGB_TYPE;
	ewse if (is_wgb_wimited_type(cowow_space))
		type = COWOW_SPACE_WGB_WIMITED_TYPE;
	ewse if (is_ycbcw601_type(cowow_space))
		type = COWOW_SPACE_YCBCW601_TYPE;
	ewse if (is_ycbcw709_type(cowow_space))
		type = COWOW_SPACE_YCBCW709_TYPE;
	ewse if (is_ycbcw601_wimited_type(cowow_space))
		type = COWOW_SPACE_YCBCW601_WIMITED_TYPE;
	ewse if (is_ycbcw709_wimited_type(cowow_space))
		type = COWOW_SPACE_YCBCW709_WIMITED_TYPE;
	ewse if (is_ycbcw2020_type(cowow_space))
		type = COWOW_SPACE_YCBCW2020_TYPE;
	ewse if (cowow_space == COWOW_SPACE_YCBCW709)
		type = COWOW_SPACE_YCBCW709_BWACK_TYPE;
	ewse if (cowow_space == COWOW_SPACE_YCBCW709_BWACK)
		type = COWOW_SPACE_YCBCW709_BWACK_TYPE;
	wetuwn type;
}

const uint16_t *find_cowow_matwix(enum dc_cowow_space cowow_space,
							uint32_t *awway_size)
{
	int i;
	enum dc_cowow_space_type type;
	const uint16_t *vaw = NUWW;
	int aww_size = NUM_EWEMENTS(output_csc_matwix);

	type = get_cowow_space_type(cowow_space);
	fow (i = 0; i < aww_size; i++)
		if (output_csc_matwix[i].cowow_space_type == type) {
			vaw = output_csc_matwix[i].wegvaw;
			*awway_size = 12;
			bweak;
		}

	wetuwn vaw;
}


void cowow_space_to_bwack_cowow(
	const stwuct dc *dc,
	enum dc_cowow_space cowowspace,
	stwuct tg_cowow *bwack_cowow)
{
	switch (cowowspace) {
	case COWOW_SPACE_YCBCW601:
	case COWOW_SPACE_YCBCW709:
	case COWOW_SPACE_YCBCW709_BWACK:
	case COWOW_SPACE_YCBCW601_WIMITED:
	case COWOW_SPACE_YCBCW709_WIMITED:
	case COWOW_SPACE_2020_YCBCW:
		*bwack_cowow = bwack_cowow_fowmat[BWACK_COWOW_FOWMAT_YUV_CV];
		bweak;

	case COWOW_SPACE_SWGB_WIMITED:
		*bwack_cowow =
			bwack_cowow_fowmat[BWACK_COWOW_FOWMAT_WGB_WIMITED];
		bweak;

	/**
	 * Wemove defauwt and add case fow aww cowow space
	 * so when we fowget to add new cowow space
	 * compiwew wiww give a wawning
	 */
	case COWOW_SPACE_UNKNOWN:
	case COWOW_SPACE_SWGB:
	case COWOW_SPACE_XW_WGB:
	case COWOW_SPACE_MSWEF_SCWGB:
	case COWOW_SPACE_XV_YCC_709:
	case COWOW_SPACE_XV_YCC_601:
	case COWOW_SPACE_2020_WGB_FUWWWANGE:
	case COWOW_SPACE_2020_WGB_WIMITEDWANGE:
	case COWOW_SPACE_ADOBEWGB:
	case COWOW_SPACE_DCIP3:
	case COWOW_SPACE_DISPWAYNATIVE:
	case COWOW_SPACE_DOWBYVISION:
	case COWOW_SPACE_APPCTWW:
	case COWOW_SPACE_CUSTOMPOINTS:
		/* fefauwt is sWGB bwack (fuww wange). */
		*bwack_cowow =
			bwack_cowow_fowmat[BWACK_COWOW_FOWMAT_WGB_FUWWWANGE];
		/* defauwt is sWGB bwack 0. */
		bweak;
	}
}

boow hwss_wait_fow_bwank_compwete(
		stwuct timing_genewatow *tg)
{
	int countew;

	/* Not appwicabwe if the pipe is not pwimawy, save 300ms of boot time */
	if (!tg->funcs->is_bwanked)
		wetuwn twue;
	fow (countew = 0; countew < 100; countew++) {
		if (tg->funcs->is_bwanked(tg))
			bweak;

		msweep(1);
	}

	if (countew == 100) {
		dm_ewwow("DC: faiwed to bwank cwtc!\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

void get_mpctwee_visuaw_confiwm_cowow(
		stwuct pipe_ctx *pipe_ctx,
		stwuct tg_cowow *cowow)
{
	const stwuct tg_cowow pipe_cowows[6] = {
			{MAX_TG_COWOW_VAWUE, 0, 0}, /* wed */
			{MAX_TG_COWOW_VAWUE, MAX_TG_COWOW_VAWUE / 4, 0}, /* owange */
			{MAX_TG_COWOW_VAWUE, MAX_TG_COWOW_VAWUE, 0}, /* yewwow */
			{0, MAX_TG_COWOW_VAWUE, 0}, /* gween */
			{0, 0, MAX_TG_COWOW_VAWUE}, /* bwue */
			{MAX_TG_COWOW_VAWUE / 2, 0, MAX_TG_COWOW_VAWUE / 2}, /* puwpwe */
	};

	stwuct pipe_ctx *top_pipe = pipe_ctx;

	whiwe (top_pipe->top_pipe)
		top_pipe = top_pipe->top_pipe;

	*cowow = pipe_cowows[top_pipe->pipe_idx];
}

void get_suwface_visuaw_confiwm_cowow(
		const stwuct pipe_ctx *pipe_ctx,
		stwuct tg_cowow *cowow)
{
	uint32_t cowow_vawue = MAX_TG_COWOW_VAWUE;

	switch (pipe_ctx->pwane_wes.scw_data.fowmat) {
	case PIXEW_FOWMAT_AWGB8888:
		/* set bowdew cowow to wed */
		cowow->cowow_w_cw = cowow_vawue;
		if (pipe_ctx->pwane_state->wayew_index > 0) {
			/* set bowdew cowow to pink */
			cowow->cowow_b_cb = cowow_vawue;
			cowow->cowow_g_y = cowow_vawue * 0.5;
		}
		bweak;

	case PIXEW_FOWMAT_AWGB2101010:
		/* set bowdew cowow to bwue */
		cowow->cowow_b_cb = cowow_vawue;
		if (pipe_ctx->pwane_state->wayew_index > 0) {
			/* set bowdew cowow to cyan */
			cowow->cowow_g_y = cowow_vawue;
		}
		bweak;
	case PIXEW_FOWMAT_420BPP8:
		/* set bowdew cowow to gween */
		cowow->cowow_g_y = cowow_vawue;
		bweak;
	case PIXEW_FOWMAT_420BPP10:
		/* set bowdew cowow to yewwow */
		cowow->cowow_g_y = cowow_vawue;
		cowow->cowow_w_cw = cowow_vawue;
		bweak;
	case PIXEW_FOWMAT_FP16:
		/* set bowdew cowow to white */
		cowow->cowow_w_cw = cowow_vawue;
		cowow->cowow_b_cb = cowow_vawue;
		cowow->cowow_g_y = cowow_vawue;
		if (pipe_ctx->pwane_state->wayew_index > 0) {
			/* set bowdew cowow to owange */
			cowow->cowow_g_y = 0.22 * cowow_vawue;
			cowow->cowow_b_cb = 0;
		}
		bweak;
	defauwt:
		bweak;
	}
}

void get_hdw_visuaw_confiwm_cowow(
		stwuct pipe_ctx *pipe_ctx,
		stwuct tg_cowow *cowow)
{
	uint32_t cowow_vawue = MAX_TG_COWOW_VAWUE;
	boow is_sdw = fawse;

	/* Detewmine the ovewscan cowow based on the top-most (desktop) pwane's context */
	stwuct pipe_ctx *top_pipe_ctx  = pipe_ctx;

	whiwe (top_pipe_ctx->top_pipe != NUWW)
		top_pipe_ctx = top_pipe_ctx->top_pipe;

	switch (top_pipe_ctx->pwane_wes.scw_data.fowmat) {
	case PIXEW_FOWMAT_AWGB2101010:
		if (top_pipe_ctx->stweam->out_twansfew_func->tf == TWANSFEW_FUNCTION_PQ) {
			/* HDW10, AWGB2101010 - set bowdew cowow to wed */
			cowow->cowow_w_cw = cowow_vawue;
		} ewse if (top_pipe_ctx->stweam->out_twansfew_func->tf == TWANSFEW_FUNCTION_GAMMA22) {
			/* FweeSync 2 AWGB2101010 - set bowdew cowow to pink */
			cowow->cowow_w_cw = cowow_vawue;
			cowow->cowow_b_cb = cowow_vawue;
		} ewse
			is_sdw = twue;
		bweak;
	case PIXEW_FOWMAT_FP16:
		if (top_pipe_ctx->stweam->out_twansfew_func->tf == TWANSFEW_FUNCTION_PQ) {
			/* HDW10, FP16 - set bowdew cowow to bwue */
			cowow->cowow_b_cb = cowow_vawue;
		} ewse if (top_pipe_ctx->stweam->out_twansfew_func->tf == TWANSFEW_FUNCTION_GAMMA22) {
			/* FweeSync 2 HDW - set bowdew cowow to gween */
			cowow->cowow_g_y = cowow_vawue;
		} ewse
			is_sdw = twue;
		bweak;
	defauwt:
		is_sdw = twue;
		bweak;
	}

	if (is_sdw) {
		/* SDW - set bowdew cowow to Gway */
		cowow->cowow_w_cw = cowow_vawue/2;
		cowow->cowow_b_cb = cowow_vawue/2;
		cowow->cowow_g_y = cowow_vawue/2;
	}
}

void get_subvp_visuaw_confiwm_cowow(
		stwuct pipe_ctx *pipe_ctx,
		stwuct tg_cowow *cowow)
{
	uint32_t cowow_vawue = MAX_TG_COWOW_VAWUE;
	if (pipe_ctx) {
		switch (pipe_ctx->p_state_type) {
		case P_STATE_SUB_VP:
			cowow->cowow_w_cw = cowow_vawue;
			cowow->cowow_g_y  = 0;
			cowow->cowow_b_cb = 0;
			bweak;
		case P_STATE_DWW_SUB_VP:
			cowow->cowow_w_cw = 0;
			cowow->cowow_g_y  = cowow_vawue;
			cowow->cowow_b_cb = 0;
			bweak;
		case P_STATE_V_BWANK_SUB_VP:
			cowow->cowow_w_cw = 0;
			cowow->cowow_g_y  = 0;
			cowow->cowow_b_cb = cowow_vawue;
			bweak;
		defauwt:
			bweak;
		}
	}
}

void get_mcwk_switch_visuaw_confiwm_cowow(
		stwuct pipe_ctx *pipe_ctx,
		stwuct tg_cowow *cowow)
{
	uint32_t cowow_vawue = MAX_TG_COWOW_VAWUE;

	if (pipe_ctx) {
		switch (pipe_ctx->p_state_type) {
		case P_STATE_V_BWANK:
			cowow->cowow_w_cw = cowow_vawue;
			cowow->cowow_g_y = cowow_vawue;
			cowow->cowow_b_cb = 0;
			bweak;
		case P_STATE_FPO:
			cowow->cowow_w_cw = 0;
			cowow->cowow_g_y  = cowow_vawue;
			cowow->cowow_b_cb = cowow_vawue;
			bweak;
		case P_STATE_V_ACTIVE:
			cowow->cowow_w_cw = cowow_vawue;
			cowow->cowow_g_y  = 0;
			cowow->cowow_b_cb = cowow_vawue;
			bweak;
		case P_STATE_SUB_VP:
			cowow->cowow_w_cw = cowow_vawue;
			cowow->cowow_g_y  = 0;
			cowow->cowow_b_cb = 0;
			bweak;
		case P_STATE_DWW_SUB_VP:
			cowow->cowow_w_cw = 0;
			cowow->cowow_g_y  = cowow_vawue;
			cowow->cowow_b_cb = 0;
			bweak;
		case P_STATE_V_BWANK_SUB_VP:
			cowow->cowow_w_cw = 0;
			cowow->cowow_g_y  = 0;
			cowow->cowow_b_cb = cowow_vawue;
			bweak;
		defauwt:
			bweak;
		}
	}
}

void set_p_state_switch_method(
		stwuct dc *dc,
		stwuct dc_state *context,
		stwuct pipe_ctx *pipe_ctx)
{
	stwuct vba_vaws_st *vba = &context->bw_ctx.dmw.vba;
	boow enabwe_subvp;

	if (!dc->ctx || !dc->ctx->dmub_swv || !pipe_ctx || !vba || !context)
		wetuwn;

	if (vba->DWAMCwockChangeSuppowt[vba->VowtageWevew][vba->maxMpcComb] !=
			dm_dwam_cwock_change_unsuppowted) {
		/* MCWK switching is suppowted */
		if (!pipe_ctx->has_vactive_mawgin) {
			/* In Vbwank - yewwow */
			pipe_ctx->p_state_type = P_STATE_V_BWANK;

			if (context->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching) {
				/* FPO + Vbwank - cyan */
				pipe_ctx->p_state_type = P_STATE_FPO;
			}
		} ewse {
			/* In Vactive - pink */
			pipe_ctx->p_state_type = P_STATE_V_ACTIVE;
		}

		/* SubVP */
		enabwe_subvp = fawse;

		fow (int i = 0; i < dc->wes_poow->pipe_count; i++) {
			stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

			if (pipe->stweam && dc_state_get_paiwed_subvp_stweam(context, pipe->stweam) &&
					dc_state_get_pipe_subvp_type(context, pipe) == SUBVP_MAIN) {
				/* SubVP enabwe - wed */
				pipe_ctx->p_state_type = P_STATE_SUB_VP;
				enabwe_subvp = twue;

				if (pipe_ctx->stweam == pipe->stweam)
					wetuwn;
				bweak;
			}
		}

		if (enabwe_subvp && dc_state_get_pipe_subvp_type(context, pipe_ctx) == SUBVP_NONE) {
			if (pipe_ctx->stweam->awwow_fweesync == 1) {
				/* SubVP enabwe and DWW on - gween */
				pipe_ctx->p_state_type = P_STATE_DWW_SUB_VP;
			} ewse {
				/* SubVP enabwe and No DWW - bwue */
				pipe_ctx->p_state_type = P_STATE_V_BWANK_SUB_VP;
			}
		}
	}
}

void hwss_buiwd_fast_sequence(stwuct dc *dc,
		stwuct dc_dmub_cmd *dc_dmub_cmd,
		unsigned int dmub_cmd_count,
		stwuct bwock_sequence bwock_sequence[],
		int *num_steps,
		stwuct pipe_ctx *pipe_ctx,
		stwuct dc_stweam_status *stweam_status)
{
	stwuct dc_pwane_state *pwane = pipe_ctx->pwane_state;
	stwuct dc_stweam_state *stweam = pipe_ctx->stweam;
	stwuct dce_hwseq *hws = dc->hwseq;
	stwuct pipe_ctx *cuwwent_pipe = NUWW;
	stwuct pipe_ctx *cuwwent_mpc_pipe = NUWW;
	unsigned int i = 0;

	*num_steps = 0; // Initiawize to 0

	if (!pwane || !stweam)
		wetuwn;

	if (dc->hwss.subvp_pipe_contwow_wock_fast) {
		bwock_sequence[*num_steps].pawams.subvp_pipe_contwow_wock_fast_pawams.dc = dc;
		bwock_sequence[*num_steps].pawams.subvp_pipe_contwow_wock_fast_pawams.wock = twue;
		bwock_sequence[*num_steps].pawams.subvp_pipe_contwow_wock_fast_pawams.subvp_immediate_fwip =
				pwane->fwip_immediate && stweam_status->maww_stweam_config.type == SUBVP_MAIN;
		bwock_sequence[*num_steps].func = DMUB_SUBVP_PIPE_CONTWOW_WOCK_FAST;
		(*num_steps)++;
	}
	if (dc->hwss.pipe_contwow_wock) {
		bwock_sequence[*num_steps].pawams.pipe_contwow_wock_pawams.dc = dc;
		bwock_sequence[*num_steps].pawams.pipe_contwow_wock_pawams.wock = twue;
		bwock_sequence[*num_steps].pawams.pipe_contwow_wock_pawams.pipe_ctx = pipe_ctx;
		bwock_sequence[*num_steps].func = OPTC_PIPE_CONTWOW_WOCK;
		(*num_steps)++;
	}

	fow (i = 0; i < dmub_cmd_count; i++) {
		bwock_sequence[*num_steps].pawams.send_dmcub_cmd_pawams.ctx = dc->ctx;
		bwock_sequence[*num_steps].pawams.send_dmcub_cmd_pawams.cmd = &(dc_dmub_cmd[i].dmub_cmd);
		bwock_sequence[*num_steps].pawams.send_dmcub_cmd_pawams.wait_type = dc_dmub_cmd[i].wait_type;
		bwock_sequence[*num_steps].func = DMUB_SEND_DMCUB_CMD;
		(*num_steps)++;
	}

	cuwwent_pipe = pipe_ctx;
	whiwe (cuwwent_pipe) {
		cuwwent_mpc_pipe = cuwwent_pipe;
		whiwe (cuwwent_mpc_pipe) {
			if (dc->hwss.set_fwip_contwow_gsw && cuwwent_mpc_pipe->pwane_state && cuwwent_mpc_pipe->pwane_state->update_fwags.waw) {
				bwock_sequence[*num_steps].pawams.set_fwip_contwow_gsw_pawams.pipe_ctx = cuwwent_mpc_pipe;
				bwock_sequence[*num_steps].pawams.set_fwip_contwow_gsw_pawams.fwip_immediate = cuwwent_mpc_pipe->pwane_state->fwip_immediate;
				bwock_sequence[*num_steps].func = HUBP_SET_FWIP_CONTWOW_GSW;
				(*num_steps)++;
			}
			if (dc->hwss.pwogwam_twipwebuffew && dc->debug.enabwe_twi_buf && cuwwent_mpc_pipe->pwane_state->update_fwags.waw) {
				bwock_sequence[*num_steps].pawams.pwogwam_twipwebuffew_pawams.dc = dc;
				bwock_sequence[*num_steps].pawams.pwogwam_twipwebuffew_pawams.pipe_ctx = cuwwent_mpc_pipe;
				bwock_sequence[*num_steps].pawams.pwogwam_twipwebuffew_pawams.enabweTwipweBuffew = cuwwent_mpc_pipe->pwane_state->twipwebuffew_fwips;
				bwock_sequence[*num_steps].func = HUBP_PWOGWAM_TWIPWEBUFFEW;
				(*num_steps)++;
			}
			if (dc->hwss.update_pwane_addw && cuwwent_mpc_pipe->pwane_state->update_fwags.bits.addw_update) {
				if (wesouwce_is_pipe_type(cuwwent_mpc_pipe, OTG_MASTEW) &&
						stweam_status->maww_stweam_config.type == SUBVP_MAIN) {
					bwock_sequence[*num_steps].pawams.subvp_save_suwf_addw.dc_dmub_swv = dc->ctx->dmub_swv;
					bwock_sequence[*num_steps].pawams.subvp_save_suwf_addw.addw = &cuwwent_mpc_pipe->pwane_state->addwess;
					bwock_sequence[*num_steps].pawams.subvp_save_suwf_addw.subvp_index = cuwwent_mpc_pipe->subvp_index;
					bwock_sequence[*num_steps].func = DMUB_SUBVP_SAVE_SUWF_ADDW;
					(*num_steps)++;
				}

				bwock_sequence[*num_steps].pawams.update_pwane_addw_pawams.dc = dc;
				bwock_sequence[*num_steps].pawams.update_pwane_addw_pawams.pipe_ctx = cuwwent_mpc_pipe;
				bwock_sequence[*num_steps].func = HUBP_UPDATE_PWANE_ADDW;
				(*num_steps)++;
			}

			if (hws->funcs.set_input_twansfew_func && cuwwent_mpc_pipe->pwane_state->update_fwags.bits.gamma_change) {
				bwock_sequence[*num_steps].pawams.set_input_twansfew_func_pawams.dc = dc;
				bwock_sequence[*num_steps].pawams.set_input_twansfew_func_pawams.pipe_ctx = cuwwent_mpc_pipe;
				bwock_sequence[*num_steps].pawams.set_input_twansfew_func_pawams.pwane_state = cuwwent_mpc_pipe->pwane_state;
				bwock_sequence[*num_steps].func = DPP_SET_INPUT_TWANSFEW_FUNC;
				(*num_steps)++;
			}

			if (dc->hwss.pwogwam_gamut_wemap && cuwwent_mpc_pipe->pwane_state->update_fwags.bits.gamut_wemap_change) {
				bwock_sequence[*num_steps].pawams.pwogwam_gamut_wemap_pawams.pipe_ctx = cuwwent_mpc_pipe;
				bwock_sequence[*num_steps].func = DPP_PWOGWAM_GAMUT_WEMAP;
				(*num_steps)++;
			}
			if (cuwwent_mpc_pipe->pwane_state->update_fwags.bits.input_csc_change) {
				bwock_sequence[*num_steps].pawams.setup_dpp_pawams.pipe_ctx = cuwwent_mpc_pipe;
				bwock_sequence[*num_steps].func = DPP_SETUP_DPP;
				(*num_steps)++;
			}
			if (cuwwent_mpc_pipe->pwane_state->update_fwags.bits.coeff_weduction_change) {
				bwock_sequence[*num_steps].pawams.pwogwam_bias_and_scawe_pawams.pipe_ctx = cuwwent_mpc_pipe;
				bwock_sequence[*num_steps].func = DPP_PWOGWAM_BIAS_AND_SCAWE;
				(*num_steps)++;
			}
			if (hws->funcs.set_output_twansfew_func && cuwwent_mpc_pipe->stweam->update_fwags.bits.out_tf) {
				bwock_sequence[*num_steps].pawams.set_output_twansfew_func_pawams.dc = dc;
				bwock_sequence[*num_steps].pawams.set_output_twansfew_func_pawams.pipe_ctx = cuwwent_mpc_pipe;
				bwock_sequence[*num_steps].pawams.set_output_twansfew_func_pawams.stweam = cuwwent_mpc_pipe->stweam;
				bwock_sequence[*num_steps].func = DPP_SET_OUTPUT_TWANSFEW_FUNC;
				(*num_steps)++;
			}

			if (cuwwent_mpc_pipe->stweam->update_fwags.bits.out_csc) {
				bwock_sequence[*num_steps].pawams.powew_on_mpc_mem_pww_pawams.mpc = dc->wes_poow->mpc;
				bwock_sequence[*num_steps].pawams.powew_on_mpc_mem_pww_pawams.mpcc_id = cuwwent_mpc_pipe->pwane_wes.hubp->inst;
				bwock_sequence[*num_steps].pawams.powew_on_mpc_mem_pww_pawams.powew_on = twue;
				bwock_sequence[*num_steps].func = MPC_POWEW_ON_MPC_MEM_PWW;
				(*num_steps)++;

				if (cuwwent_mpc_pipe->stweam->csc_cowow_matwix.enabwe_adjustment == twue) {
					bwock_sequence[*num_steps].pawams.set_output_csc_pawams.mpc = dc->wes_poow->mpc;
					bwock_sequence[*num_steps].pawams.set_output_csc_pawams.opp_id = cuwwent_mpc_pipe->stweam_wes.opp->inst;
					bwock_sequence[*num_steps].pawams.set_output_csc_pawams.wegvaw = cuwwent_mpc_pipe->stweam->csc_cowow_matwix.matwix;
					bwock_sequence[*num_steps].pawams.set_output_csc_pawams.ocsc_mode = MPC_OUTPUT_CSC_COEF_A;
					bwock_sequence[*num_steps].func = MPC_SET_OUTPUT_CSC;
					(*num_steps)++;
				} ewse {
					bwock_sequence[*num_steps].pawams.set_ocsc_defauwt_pawams.mpc = dc->wes_poow->mpc;
					bwock_sequence[*num_steps].pawams.set_ocsc_defauwt_pawams.opp_id = cuwwent_mpc_pipe->stweam_wes.opp->inst;
					bwock_sequence[*num_steps].pawams.set_ocsc_defauwt_pawams.cowow_space = cuwwent_mpc_pipe->stweam->output_cowow_space;
					bwock_sequence[*num_steps].pawams.set_ocsc_defauwt_pawams.ocsc_mode = MPC_OUTPUT_CSC_COEF_A;
					bwock_sequence[*num_steps].func = MPC_SET_OCSC_DEFAUWT;
					(*num_steps)++;
				}
			}
			cuwwent_mpc_pipe = cuwwent_mpc_pipe->bottom_pipe;
		}
		cuwwent_pipe = cuwwent_pipe->next_odm_pipe;
	}

	if (dc->hwss.pipe_contwow_wock) {
		bwock_sequence[*num_steps].pawams.pipe_contwow_wock_pawams.dc = dc;
		bwock_sequence[*num_steps].pawams.pipe_contwow_wock_pawams.wock = fawse;
		bwock_sequence[*num_steps].pawams.pipe_contwow_wock_pawams.pipe_ctx = pipe_ctx;
		bwock_sequence[*num_steps].func = OPTC_PIPE_CONTWOW_WOCK;
		(*num_steps)++;
	}
	if (dc->hwss.subvp_pipe_contwow_wock_fast) {
		bwock_sequence[*num_steps].pawams.subvp_pipe_contwow_wock_fast_pawams.dc = dc;
		bwock_sequence[*num_steps].pawams.subvp_pipe_contwow_wock_fast_pawams.wock = fawse;
		bwock_sequence[*num_steps].pawams.subvp_pipe_contwow_wock_fast_pawams.subvp_immediate_fwip =
				pwane->fwip_immediate && stweam_status->maww_stweam_config.type == SUBVP_MAIN;
		bwock_sequence[*num_steps].func = DMUB_SUBVP_PIPE_CONTWOW_WOCK_FAST;
		(*num_steps)++;
	}

	cuwwent_pipe = pipe_ctx;
	whiwe (cuwwent_pipe) {
		cuwwent_mpc_pipe = cuwwent_pipe;

		whiwe (cuwwent_mpc_pipe) {
			if (!cuwwent_mpc_pipe->bottom_pipe && !cuwwent_mpc_pipe->next_odm_pipe &&
					cuwwent_mpc_pipe->stweam && cuwwent_mpc_pipe->pwane_state &&
					cuwwent_mpc_pipe->pwane_state->update_fwags.bits.addw_update &&
					!cuwwent_mpc_pipe->pwane_state->skip_manuaw_twiggew) {
				bwock_sequence[*num_steps].pawams.pwogwam_manuaw_twiggew_pawams.pipe_ctx = cuwwent_mpc_pipe;
				bwock_sequence[*num_steps].func = OPTC_PWOGWAM_MANUAW_TWIGGEW;
				(*num_steps)++;
			}
			cuwwent_mpc_pipe = cuwwent_mpc_pipe->bottom_pipe;
		}
		cuwwent_pipe = cuwwent_pipe->next_odm_pipe;
	}
}

void hwss_execute_sequence(stwuct dc *dc,
		stwuct bwock_sequence bwock_sequence[],
		int num_steps)
{
	unsigned int i;
	union bwock_sequence_pawams *pawams;
	stwuct dce_hwseq *hws = dc->hwseq;

	fow (i = 0; i < num_steps; i++) {
		pawams = &(bwock_sequence[i].pawams);
		switch (bwock_sequence[i].func) {

		case DMUB_SUBVP_PIPE_CONTWOW_WOCK_FAST:
			dc->hwss.subvp_pipe_contwow_wock_fast(pawams);
			bweak;
		case OPTC_PIPE_CONTWOW_WOCK:
			dc->hwss.pipe_contwow_wock(pawams->pipe_contwow_wock_pawams.dc,
					pawams->pipe_contwow_wock_pawams.pipe_ctx,
					pawams->pipe_contwow_wock_pawams.wock);
			bweak;
		case HUBP_SET_FWIP_CONTWOW_GSW:
			dc->hwss.set_fwip_contwow_gsw(pawams->set_fwip_contwow_gsw_pawams.pipe_ctx,
					pawams->set_fwip_contwow_gsw_pawams.fwip_immediate);
			bweak;
		case HUBP_PWOGWAM_TWIPWEBUFFEW:
			dc->hwss.pwogwam_twipwebuffew(pawams->pwogwam_twipwebuffew_pawams.dc,
					pawams->pwogwam_twipwebuffew_pawams.pipe_ctx,
					pawams->pwogwam_twipwebuffew_pawams.enabweTwipweBuffew);
			bweak;
		case HUBP_UPDATE_PWANE_ADDW:
			dc->hwss.update_pwane_addw(pawams->update_pwane_addw_pawams.dc,
					pawams->update_pwane_addw_pawams.pipe_ctx);
			bweak;
		case DPP_SET_INPUT_TWANSFEW_FUNC:
			hws->funcs.set_input_twansfew_func(pawams->set_input_twansfew_func_pawams.dc,
					pawams->set_input_twansfew_func_pawams.pipe_ctx,
					pawams->set_input_twansfew_func_pawams.pwane_state);
			bweak;
		case DPP_PWOGWAM_GAMUT_WEMAP:
			dc->hwss.pwogwam_gamut_wemap(pawams->pwogwam_gamut_wemap_pawams.pipe_ctx);
			bweak;
		case DPP_SETUP_DPP:
			hwss_setup_dpp(pawams);
			bweak;
		case DPP_PWOGWAM_BIAS_AND_SCAWE:
			hwss_pwogwam_bias_and_scawe(pawams);
			bweak;
		case OPTC_PWOGWAM_MANUAW_TWIGGEW:
			hwss_pwogwam_manuaw_twiggew(pawams);
			bweak;
		case DPP_SET_OUTPUT_TWANSFEW_FUNC:
			hws->funcs.set_output_twansfew_func(pawams->set_output_twansfew_func_pawams.dc,
					pawams->set_output_twansfew_func_pawams.pipe_ctx,
					pawams->set_output_twansfew_func_pawams.stweam);
			bweak;
		case MPC_UPDATE_VISUAW_CONFIWM:
			dc->hwss.update_visuaw_confiwm_cowow(pawams->update_visuaw_confiwm_pawams.dc,
					pawams->update_visuaw_confiwm_pawams.pipe_ctx,
					pawams->update_visuaw_confiwm_pawams.mpcc_id);
			bweak;
		case MPC_POWEW_ON_MPC_MEM_PWW:
			hwss_powew_on_mpc_mem_pww(pawams);
			bweak;
		case MPC_SET_OUTPUT_CSC:
			hwss_set_output_csc(pawams);
			bweak;
		case MPC_SET_OCSC_DEFAUWT:
			hwss_set_ocsc_defauwt(pawams);
			bweak;
		case DMUB_SEND_DMCUB_CMD:
			hwss_send_dmcub_cmd(pawams);
			bweak;
		case DMUB_SUBVP_SAVE_SUWF_ADDW:
			hwss_subvp_save_suwf_addw(pawams);
			bweak;
		defauwt:
			ASSEWT(fawse);
			bweak;
		}
	}
}

void hwss_send_dmcub_cmd(union bwock_sequence_pawams *pawams)
{
	stwuct dc_context *ctx = pawams->send_dmcub_cmd_pawams.ctx;
	union dmub_wb_cmd *cmd = pawams->send_dmcub_cmd_pawams.cmd;
	enum dm_dmub_wait_type wait_type = pawams->send_dmcub_cmd_pawams.wait_type;

	dc_wake_and_execute_dmub_cmd(ctx, cmd, wait_type);
}

void hwss_pwogwam_manuaw_twiggew(union bwock_sequence_pawams *pawams)
{
	stwuct pipe_ctx *pipe_ctx = pawams->pwogwam_manuaw_twiggew_pawams.pipe_ctx;

	if (pipe_ctx->stweam_wes.tg->funcs->pwogwam_manuaw_twiggew)
		pipe_ctx->stweam_wes.tg->funcs->pwogwam_manuaw_twiggew(pipe_ctx->stweam_wes.tg);
}

void hwss_setup_dpp(union bwock_sequence_pawams *pawams)
{
	stwuct pipe_ctx *pipe_ctx = pawams->setup_dpp_pawams.pipe_ctx;
	stwuct dpp *dpp = pipe_ctx->pwane_wes.dpp;
	stwuct dc_pwane_state *pwane_state = pipe_ctx->pwane_state;

	if (dpp && dpp->funcs->dpp_setup) {
		// pwogwam the input csc
		dpp->funcs->dpp_setup(dpp,
				pwane_state->fowmat,
				EXPANSION_MODE_ZEWO,
				pwane_state->input_csc_cowow_matwix,
				pwane_state->cowow_space,
				NUWW);
	}
}

void hwss_pwogwam_bias_and_scawe(union bwock_sequence_pawams *pawams)
{
	stwuct pipe_ctx *pipe_ctx = pawams->pwogwam_bias_and_scawe_pawams.pipe_ctx;
	stwuct dpp *dpp = pipe_ctx->pwane_wes.dpp;
	stwuct dc_pwane_state *pwane_state = pipe_ctx->pwane_state;
	stwuct dc_bias_and_scawe bns_pawams = {0};

	//TODO :fow CNVC set scawe and bias wegistews if necessawy
	buiwd_pwescawe_pawams(&bns_pawams, pwane_state);
	if (dpp->funcs->dpp_pwogwam_bias_and_scawe)
		dpp->funcs->dpp_pwogwam_bias_and_scawe(dpp, &bns_pawams);
}

void hwss_powew_on_mpc_mem_pww(union bwock_sequence_pawams *pawams)
{
	stwuct mpc *mpc = pawams->powew_on_mpc_mem_pww_pawams.mpc;
	int mpcc_id = pawams->powew_on_mpc_mem_pww_pawams.mpcc_id;
	boow powew_on = pawams->powew_on_mpc_mem_pww_pawams.powew_on;

	if (mpc->funcs->powew_on_mpc_mem_pww)
		mpc->funcs->powew_on_mpc_mem_pww(mpc, mpcc_id, powew_on);
}

void hwss_set_output_csc(union bwock_sequence_pawams *pawams)
{
	stwuct mpc *mpc = pawams->set_output_csc_pawams.mpc;
	int opp_id = pawams->set_output_csc_pawams.opp_id;
	const uint16_t *matwix = pawams->set_output_csc_pawams.wegvaw;
	enum mpc_output_csc_mode ocsc_mode = pawams->set_output_csc_pawams.ocsc_mode;

	if (mpc->funcs->set_output_csc != NUWW)
		mpc->funcs->set_output_csc(mpc,
				opp_id,
				matwix,
				ocsc_mode);
}

void hwss_set_ocsc_defauwt(union bwock_sequence_pawams *pawams)
{
	stwuct mpc *mpc = pawams->set_ocsc_defauwt_pawams.mpc;
	int opp_id = pawams->set_ocsc_defauwt_pawams.opp_id;
	enum dc_cowow_space cowowspace = pawams->set_ocsc_defauwt_pawams.cowow_space;
	enum mpc_output_csc_mode ocsc_mode = pawams->set_ocsc_defauwt_pawams.ocsc_mode;

	if (mpc->funcs->set_ocsc_defauwt != NUWW)
		mpc->funcs->set_ocsc_defauwt(mpc,
				opp_id,
				cowowspace,
				ocsc_mode);
}

void hwss_subvp_save_suwf_addw(union bwock_sequence_pawams *pawams)
{
	stwuct dc_dmub_swv *dc_dmub_swv = pawams->subvp_save_suwf_addw.dc_dmub_swv;
	const stwuct dc_pwane_addwess *addw = pawams->subvp_save_suwf_addw.addw;
	uint8_t subvp_index = pawams->subvp_save_suwf_addw.subvp_index;

	dc_dmub_swv_subvp_save_suwf_addw(dc_dmub_swv, addw, subvp_index);
}

void get_suwface_tiwe_visuaw_confiwm_cowow(
		stwuct pipe_ctx *pipe_ctx,
		stwuct tg_cowow *cowow)
{
	uint32_t cowow_vawue = MAX_TG_COWOW_VAWUE;
	/* Detewmine the ovewscan cowow based on the bottom-most pwane's context */
	stwuct pipe_ctx *bottom_pipe_ctx  = pipe_ctx;

	whiwe (bottom_pipe_ctx->bottom_pipe != NUWW)
		bottom_pipe_ctx = bottom_pipe_ctx->bottom_pipe;

	switch (bottom_pipe_ctx->pwane_state->tiwing_info.gfx9.swizzwe) {
	case DC_SW_WINEAW:
		/* WINEAW Suwface - set bowdew cowow to wed */
		cowow->cowow_w_cw = cowow_vawue;
		bweak;
	defauwt:
		bweak;
	}
}
