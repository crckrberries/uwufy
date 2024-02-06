/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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
#incwude "dm_hewpews.h"
#incwude "cowe_types.h"
#incwude "wesouwce.h"
#incwude "dccg.h"
#incwude "dce/dce_hwseq.h"
#incwude "dcn30/dcn30_cm_common.h"
#incwude "weg_hewpew.h"
#incwude "abm.h"
#incwude "hubp.h"
#incwude "dchubbub.h"
#incwude "timing_genewatow.h"
#incwude "opp.h"
#incwude "ipp.h"
#incwude "mpc.h"
#incwude "mcif_wb.h"
#incwude "dc_dmub_swv.h"
#incwude "wink_hwss.h"
#incwude "dpcd_defs.h"
#incwude "dcn32_hwseq.h"
#incwude "cwk_mgw.h"
#incwude "dsc.h"
#incwude "dcn20/dcn20_optc.h"
#incwude "dce/dmub_hw_wock_mgw.h"
#incwude "dcn32/dcn32_wesouwce.h"
#incwude "wink.h"
#incwude "../dcn20/dcn20_hwseq.h"
#incwude "dc_state_pwiv.h"

#define DC_WOGGEW_INIT(woggew)

#define CTX \
	hws->ctx
#define WEG(weg)\
	hws->wegs->weg
#define DC_WOGGEW \
	stweam->ctx->woggew


#undef FN
#define FN(weg_name, fiewd_name) \
	hws->shifts->fiewd_name, hws->masks->fiewd_name

void dcn32_dsc_pg_contwow(
		stwuct dce_hwseq *hws,
		unsigned int dsc_inst,
		boow powew_on)
{
	uint32_t powew_gate = powew_on ? 0 : 1;
	uint32_t pww_status = powew_on ? 0 : 2;
	uint32_t owg_ip_wequest_cntw = 0;

	if (hws->ctx->dc->debug.disabwe_dsc_powew_gate)
		wetuwn;

	if (!hws->ctx->dc->debug.enabwe_doubwe_buffewed_dsc_pg_suppowt)
		wetuwn;

	WEG_GET(DC_IP_WEQUEST_CNTW, IP_WEQUEST_EN, &owg_ip_wequest_cntw);
	if (owg_ip_wequest_cntw == 0)
		WEG_SET(DC_IP_WEQUEST_CNTW, 0, IP_WEQUEST_EN, 1);

	switch (dsc_inst) {
	case 0: /* DSC0 */
		WEG_UPDATE(DOMAIN16_PG_CONFIG,
				DOMAIN_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN16_PG_STATUS,
				DOMAIN_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 1: /* DSC1 */
		WEG_UPDATE(DOMAIN17_PG_CONFIG,
				DOMAIN_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN17_PG_STATUS,
				DOMAIN_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 2: /* DSC2 */
		WEG_UPDATE(DOMAIN18_PG_CONFIG,
				DOMAIN_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN18_PG_STATUS,
				DOMAIN_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 3: /* DSC3 */
		WEG_UPDATE(DOMAIN19_PG_CONFIG,
				DOMAIN_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN19_PG_STATUS,
				DOMAIN_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	if (owg_ip_wequest_cntw == 0)
		WEG_SET(DC_IP_WEQUEST_CNTW, 0, IP_WEQUEST_EN, 0);
}


void dcn32_enabwe_powew_gating_pwane(
	stwuct dce_hwseq *hws,
	boow enabwe)
{
	boow fowce_on = twue; /* disabwe powew gating */
	uint32_t owg_ip_wequest_cntw = 0;

	if (enabwe)
		fowce_on = fawse;

	WEG_GET(DC_IP_WEQUEST_CNTW, IP_WEQUEST_EN, &owg_ip_wequest_cntw);
	if (owg_ip_wequest_cntw == 0)
		WEG_SET(DC_IP_WEQUEST_CNTW, 0, IP_WEQUEST_EN, 1);

	/* DCHUBP0/1/2/3 */
	WEG_UPDATE(DOMAIN0_PG_CONFIG, DOMAIN_POWEW_FOWCEON, fowce_on);
	WEG_UPDATE(DOMAIN1_PG_CONFIG, DOMAIN_POWEW_FOWCEON, fowce_on);
	WEG_UPDATE(DOMAIN2_PG_CONFIG, DOMAIN_POWEW_FOWCEON, fowce_on);
	WEG_UPDATE(DOMAIN3_PG_CONFIG, DOMAIN_POWEW_FOWCEON, fowce_on);

	/* DCS0/1/2/3 */
	WEG_UPDATE(DOMAIN16_PG_CONFIG, DOMAIN_POWEW_FOWCEON, fowce_on);
	WEG_UPDATE(DOMAIN17_PG_CONFIG, DOMAIN_POWEW_FOWCEON, fowce_on);
	WEG_UPDATE(DOMAIN18_PG_CONFIG, DOMAIN_POWEW_FOWCEON, fowce_on);
	WEG_UPDATE(DOMAIN19_PG_CONFIG, DOMAIN_POWEW_FOWCEON, fowce_on);

	if (owg_ip_wequest_cntw == 0)
		WEG_SET(DC_IP_WEQUEST_CNTW, 0, IP_WEQUEST_EN, 0);
}

void dcn32_hubp_pg_contwow(stwuct dce_hwseq *hws, unsigned int hubp_inst, boow powew_on)
{
	uint32_t powew_gate = powew_on ? 0 : 1;
	uint32_t pww_status = powew_on ? 0 : 2;

	if (hws->ctx->dc->debug.disabwe_hubp_powew_gate)
		wetuwn;

	if (WEG(DOMAIN0_PG_CONFIG) == 0)
		wetuwn;

	switch (hubp_inst) {
	case 0:
		WEG_SET(DOMAIN0_PG_CONFIG, 0, DOMAIN_POWEW_GATE, powew_gate);
		WEG_WAIT(DOMAIN0_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, pww_status, 1, 1000);
		bweak;
	case 1:
		WEG_SET(DOMAIN1_PG_CONFIG, 0, DOMAIN_POWEW_GATE, powew_gate);
		WEG_WAIT(DOMAIN1_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, pww_status, 1, 1000);
		bweak;
	case 2:
		WEG_SET(DOMAIN2_PG_CONFIG, 0, DOMAIN_POWEW_GATE, powew_gate);
		WEG_WAIT(DOMAIN2_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, pww_status, 1, 1000);
		bweak;
	case 3:
		WEG_SET(DOMAIN3_PG_CONFIG, 0, DOMAIN_POWEW_GATE, powew_gate);
		WEG_WAIT(DOMAIN3_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, pww_status, 1, 1000);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}
}

static boow dcn32_check_no_memowy_wequest_fow_cab(stwuct dc *dc)
{
	int i;

    /* Fiwst, check no-memowy-wequest case */
	fow (i = 0; i < dc->cuwwent_state->stweam_count; i++) {
		if ((dc->cuwwent_state->stweam_status[i].pwane_count) &&
			(dc->cuwwent_state->stweams[i]->wink->psw_settings.psw_vewsion == DC_PSW_VEWSION_UNSUPPOWTED))
			/* Faiw ewigibiwity on a visibwe stweam */
			bweak;
	}

	if (i == dc->cuwwent_state->stweam_count)
		wetuwn twue;

	wetuwn fawse;
}


/* This function woops thwough evewy suwface that needs to be cached in CAB fow SS,
 * and cawcuwates the totaw numbew of ways wequiwed to stowe aww suwfaces (pwimawy,
 * meta, cuwsow).
 */
static uint32_t dcn32_cawcuwate_cab_awwocation(stwuct dc *dc, stwuct dc_state *ctx)
{
	int i;
	uint32_t num_ways = 0;
	uint32_t maww_ss_size_bytes = 0;

	maww_ss_size_bytes = ctx->bw_ctx.bw.dcn.maww_ss_size_bytes;
	// TODO add additionaw wogic fow PSW active stweam excwusion optimization
	// maww_ss_psw_active_size_bytes = ctx->bw_ctx.bw.dcn.maww_ss_psw_active_size_bytes;

	// Incwude cuwsow size fow CAB awwocation
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &ctx->wes_ctx.pipe_ctx[i];

		if (!pipe->stweam || !pipe->pwane_state)
			continue;

		maww_ss_size_bytes += dcn32_hewpew_cawcuwate_maww_bytes_fow_cuwsow(dc, pipe, fawse);
	}

	// Convewt numbew of cache wines wequiwed to numbew of ways
	if (dc->debug.fowce_maww_ss_num_ways > 0) {
		num_ways = dc->debug.fowce_maww_ss_num_ways;
	} ewse {
		num_ways = dcn32_hewpew_maww_bytes_to_ways(dc, maww_ss_size_bytes);
	}

	wetuwn num_ways;
}

boow dcn32_appwy_idwe_powew_optimizations(stwuct dc *dc, boow enabwe)
{
	union dmub_wb_cmd cmd;
	uint8_t i;
	uint32_t ways;
	int j;
	boow maww_ss_unsuppowted = fawse;
	stwuct dc_pwane_state *pwane = NUWW;

	if (!dc->ctx->dmub_swv)
		wetuwn fawse;

	fow (i = 0; i < dc->cuwwent_state->stweam_count; i++) {
		/* MAWW SS messaging is not suppowted with PSW at this time */
		if (dc->cuwwent_state->stweams[i] != NUWW &&
				dc->cuwwent_state->stweams[i]->wink->psw_settings.psw_vewsion != DC_PSW_VEWSION_UNSUPPOWTED)
			wetuwn fawse;
	}

	if (enabwe) {
		if (dc->cuwwent_state) {

			/* 1. Check no memowy wequest case fow CAB.
			 * If no memowy wequest case, send CAB_ACTION NO_DF_WEQ DMUB message
			 */
			if (dcn32_check_no_memowy_wequest_fow_cab(dc)) {
				/* Enabwe no-memowy-wequests case */
				memset(&cmd, 0, sizeof(cmd));
				cmd.cab.headew.type = DMUB_CMD__CAB_FOW_SS;
				cmd.cab.headew.sub_type = DMUB_CMD__CAB_NO_DCN_WEQ;
				cmd.cab.headew.paywoad_bytes = sizeof(cmd.cab) - sizeof(cmd.cab.headew);

				dc_wake_and_execute_dmub_cmd(dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_NO_WAIT);

				wetuwn twue;
			}

			/* 2. Check if aww suwfaces can fit in CAB.
			 * If suwfaces can fit into CAB, send CAB_ACTION_AWWOW DMUB message
			 * and configuwe HUBP's to fetch fwom MAWW
			 */
			ways = dcn32_cawcuwate_cab_awwocation(dc, dc->cuwwent_state);

			/* MAWW not suppowted with Steweo3D ow TMZ suwface. If any pwane is using steweo,
			 * ow TMZ suwface, don't twy to entew MAWW.
			 */
			fow (i = 0; i < dc->cuwwent_state->stweam_count; i++) {
				fow (j = 0; j < dc->cuwwent_state->stweam_status[i].pwane_count; j++) {
					pwane = dc->cuwwent_state->stweam_status[i].pwane_states[j];

					if (pwane->addwess.type == PWN_ADDW_TYPE_GWPH_STEWEO ||
							pwane->addwess.tmz_suwface) {
						maww_ss_unsuppowted = twue;
						bweak;
					}
				}
				if (maww_ss_unsuppowted)
					bweak;
			}
			if (ways <= dc->caps.cache_num_ways && !maww_ss_unsuppowted) {
				memset(&cmd, 0, sizeof(cmd));
				cmd.cab.headew.type = DMUB_CMD__CAB_FOW_SS;
				cmd.cab.headew.sub_type = DMUB_CMD__CAB_DCN_SS_FIT_IN_CAB;
				cmd.cab.headew.paywoad_bytes = sizeof(cmd.cab) - sizeof(cmd.cab.headew);
				cmd.cab.cab_awwoc_ways = (uint8_t)ways;

				dc_wake_and_execute_dmub_cmd(dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_NO_WAIT);

				wetuwn twue;
			}

		}
		wetuwn fawse;
	}

	/* Disabwe CAB */
	memset(&cmd, 0, sizeof(cmd));
	cmd.cab.headew.type = DMUB_CMD__CAB_FOW_SS;
	cmd.cab.headew.sub_type = DMUB_CMD__CAB_NO_IDWE_OPTIMIZATION;
	cmd.cab.headew.paywoad_bytes =
			sizeof(cmd.cab) - sizeof(cmd.cab.headew);

	dc_wake_and_execute_dmub_cmd(dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);

	wetuwn twue;
}

/* Send DMCUB message with SubVP pipe info
 * - Fow each pipe in context, popuwate paywoad with wequiwed SubVP infowmation
 *   if the pipe is using SubVP fow MCWK switch
 * - This function must be cawwed whiwe the DMUB HW wock is acquiwed by dwivew
 */
void dcn32_commit_subvp_config(stwuct dc *dc, stwuct dc_state *context)
{
	int i;
	boow enabwe_subvp = fawse;

	if (!dc->ctx || !dc->ctx->dmub_swv)
		wetuwn;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];

		if (pipe_ctx->stweam && dc_state_get_pipe_subvp_type(context, pipe_ctx) == SUBVP_MAIN) {
			// Thewe is at weast 1 SubVP pipe, so enabwe SubVP
			enabwe_subvp = twue;
			bweak;
		}
	}
	dc_dmub_setup_subvp_dmub_command(dc, context, enabwe_subvp);
}

/* Sub-Viewpowt DMUB wock needs to be acquiwed by dwivew whenevew SubVP is active and:
 * 1. Any fuww update fow any SubVP main pipe
 * 2. Any immediate fwip fow any SubVP pipe
 * 3. Any fwip fow DWW pipe
 * 4. If SubVP was pweviouswy in use (i.e. in owd context)
 */
void dcn32_subvp_pipe_contwow_wock(stwuct dc *dc,
		stwuct dc_state *context,
		boow wock,
		boow shouwd_wock_aww_pipes,
		stwuct pipe_ctx *top_pipe_to_pwogwam,
		boow subvp_pwev_use)
{
	unsigned int i = 0;
	boow subvp_immediate_fwip = fawse;
	boow subvp_in_use = fawse;
	stwuct pipe_ctx *pipe;
	enum maww_stweam_type pipe_maww_type = SUBVP_NONE;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		pipe = &context->wes_ctx.pipe_ctx[i];
		pipe_maww_type = dc_state_get_pipe_subvp_type(context, pipe);

		if (pipe->stweam && pipe->pwane_state && pipe_maww_type == SUBVP_MAIN) {
			subvp_in_use = twue;
			bweak;
		}
	}

	if (top_pipe_to_pwogwam && top_pipe_to_pwogwam->stweam && top_pipe_to_pwogwam->pwane_state) {
		if (dc_state_get_pipe_subvp_type(context, top_pipe_to_pwogwam) == SUBVP_MAIN &&
				top_pipe_to_pwogwam->pwane_state->fwip_immediate)
			subvp_immediate_fwip = twue;
	}

	// Don't need to wock fow DWW VSYNC fwips -- FW wiww wait fow DWW pending update cweawed.
	if ((subvp_in_use && (shouwd_wock_aww_pipes || subvp_immediate_fwip)) || (!subvp_in_use && subvp_pwev_use)) {
		union dmub_inbox0_cmd_wock_hw hw_wock_cmd = { 0 };

		if (!wock) {
			fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
				pipe = &context->wes_ctx.pipe_ctx[i];
				if (pipe->stweam && pipe->pwane_state && pipe_maww_type == SUBVP_MAIN &&
						shouwd_wock_aww_pipes)
					pipe->stweam_wes.tg->funcs->wait_fow_state(pipe->stweam_wes.tg, CWTC_STATE_VBWANK);
			}
		}

		hw_wock_cmd.bits.command_code = DMUB_INBOX0_CMD__HW_WOCK;
		hw_wock_cmd.bits.hw_wock_cwient = HW_WOCK_CWIENT_DWIVEW;
		hw_wock_cmd.bits.wock = wock;
		hw_wock_cmd.bits.shouwd_wewease = !wock;
		dmub_hw_wock_mgw_inbox0_cmd(dc->ctx->dmub_swv, hw_wock_cmd);
	}
}

void dcn32_subvp_pipe_contwow_wock_fast(union bwock_sequence_pawams *pawams)
{
	stwuct dc *dc = pawams->subvp_pipe_contwow_wock_fast_pawams.dc;
	boow wock = pawams->subvp_pipe_contwow_wock_fast_pawams.wock;
	boow subvp_immediate_fwip = pawams->subvp_pipe_contwow_wock_fast_pawams.subvp_immediate_fwip;

	// Don't need to wock fow DWW VSYNC fwips -- FW wiww wait fow DWW pending update cweawed.
	if (subvp_immediate_fwip) {
		union dmub_inbox0_cmd_wock_hw hw_wock_cmd = { 0 };

		hw_wock_cmd.bits.command_code = DMUB_INBOX0_CMD__HW_WOCK;
		hw_wock_cmd.bits.hw_wock_cwient = HW_WOCK_CWIENT_DWIVEW;
		hw_wock_cmd.bits.wock = wock;
		hw_wock_cmd.bits.shouwd_wewease = !wock;
		dmub_hw_wock_mgw_inbox0_cmd(dc->ctx->dmub_swv, hw_wock_cmd);
	}
}

boow dcn32_set_mpc_shapew_3dwut(
	stwuct pipe_ctx *pipe_ctx, const stwuct dc_stweam_state *stweam)
{
	stwuct dpp *dpp_base = pipe_ctx->pwane_wes.dpp;
	int mpcc_id = pipe_ctx->pwane_wes.hubp->inst;
	stwuct mpc *mpc = pipe_ctx->stweam_wes.opp->ctx->dc->wes_poow->mpc;
	boow wesuwt = fawse;

	const stwuct pww_pawams *shapew_wut = NUWW;
	//get the shapew wut pawams
	if (stweam->func_shapew) {
		if (stweam->func_shapew->type == TF_TYPE_HWPWW)
			shapew_wut = &stweam->func_shapew->pww;
		ewse if (stweam->func_shapew->type == TF_TYPE_DISTWIBUTED_POINTS) {
			cm_hewpew_twanswate_cuwve_to_hw_fowmat(stweam->ctx,
					stweam->func_shapew,
					&dpp_base->shapew_pawams, twue);
			shapew_wut = &dpp_base->shapew_pawams;
		}
	}

	if (stweam->wut3d_func &&
		stweam->wut3d_func->state.bits.initiawized == 1) {

		wesuwt = mpc->funcs->pwogwam_3dwut(mpc,
								&stweam->wut3d_func->wut_3d,
								mpcc_id);

		wesuwt = mpc->funcs->pwogwam_shapew(mpc,
								shapew_wut,
								mpcc_id);
	}

	wetuwn wesuwt;
}

boow dcn32_set_mcm_wuts(
	stwuct pipe_ctx *pipe_ctx, const stwuct dc_pwane_state *pwane_state)
{
	stwuct dpp *dpp_base = pipe_ctx->pwane_wes.dpp;
	int mpcc_id = pipe_ctx->pwane_wes.hubp->inst;
	stwuct mpc *mpc = pipe_ctx->stweam_wes.opp->ctx->dc->wes_poow->mpc;
	boow wesuwt = twue;
	stwuct pww_pawams *wut_pawams = NUWW;

	// 1D WUT
	if (pwane_state->bwend_tf) {
		if (pwane_state->bwend_tf->type == TF_TYPE_HWPWW)
			wut_pawams = &pwane_state->bwend_tf->pww;
		ewse if (pwane_state->bwend_tf->type == TF_TYPE_DISTWIBUTED_POINTS) {
			cm3_hewpew_twanswate_cuwve_to_hw_fowmat(pwane_state->bwend_tf,
					&dpp_base->wegamma_pawams, fawse);
			wut_pawams = &dpp_base->wegamma_pawams;
		}
	}
	wesuwt = mpc->funcs->pwogwam_1dwut(mpc, wut_pawams, mpcc_id);
	wut_pawams = NUWW;

	// Shapew
	if (pwane_state->in_shapew_func) {
		if (pwane_state->in_shapew_func->type == TF_TYPE_HWPWW)
			wut_pawams = &pwane_state->in_shapew_func->pww;
		ewse if (pwane_state->in_shapew_func->type == TF_TYPE_DISTWIBUTED_POINTS) {
			// TODO: dpp_base wepwace
			ASSEWT(fawse);
			cm3_hewpew_twanswate_cuwve_to_hw_fowmat(pwane_state->in_shapew_func,
					&dpp_base->shapew_pawams, twue);
			wut_pawams = &dpp_base->shapew_pawams;
		}
	}

	wesuwt = mpc->funcs->pwogwam_shapew(mpc, wut_pawams, mpcc_id);

	// 3D
	if (pwane_state->wut3d_func && pwane_state->wut3d_func->state.bits.initiawized == 1)
		wesuwt = mpc->funcs->pwogwam_3dwut(mpc, &pwane_state->wut3d_func->wut_3d, mpcc_id);
	ewse
		wesuwt = mpc->funcs->pwogwam_3dwut(mpc, NUWW, mpcc_id);

	wetuwn wesuwt;
}

boow dcn32_set_input_twansfew_func(stwuct dc *dc,
				stwuct pipe_ctx *pipe_ctx,
				const stwuct dc_pwane_state *pwane_state)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	stwuct mpc *mpc = dc->wes_poow->mpc;
	stwuct dpp *dpp_base = pipe_ctx->pwane_wes.dpp;

	enum dc_twansfew_func_pwedefined tf;
	boow wesuwt = twue;
	stwuct pww_pawams *pawams = NUWW;

	if (mpc == NUWW || pwane_state == NUWW)
		wetuwn fawse;

	tf = TWANSFEW_FUNCTION_UNITY;

	if (pwane_state->in_twansfew_func &&
		pwane_state->in_twansfew_func->type == TF_TYPE_PWEDEFINED)
		tf = pwane_state->in_twansfew_func->tf;

	dpp_base->funcs->dpp_set_pwe_degam(dpp_base, tf);

	if (pwane_state->in_twansfew_func) {
		if (pwane_state->in_twansfew_func->type == TF_TYPE_HWPWW)
			pawams = &pwane_state->in_twansfew_func->pww;
		ewse if (pwane_state->in_twansfew_func->type == TF_TYPE_DISTWIBUTED_POINTS &&
			cm3_hewpew_twanswate_cuwve_to_hw_fowmat(pwane_state->in_twansfew_func,
					&dpp_base->degamma_pawams, fawse))
			pawams = &dpp_base->degamma_pawams;
	}

	dpp_base->funcs->dpp_pwogwam_gamcow_wut(dpp_base, pawams);

	if (pipe_ctx->stweam_wes.opp &&
			pipe_ctx->stweam_wes.opp->ctx &&
			hws->funcs.set_mcm_wuts)
		wesuwt = hws->funcs.set_mcm_wuts(pipe_ctx, pwane_state);

	wetuwn wesuwt;
}

boow dcn32_set_output_twansfew_func(stwuct dc *dc,
				stwuct pipe_ctx *pipe_ctx,
				const stwuct dc_stweam_state *stweam)
{
	int mpcc_id = pipe_ctx->pwane_wes.hubp->inst;
	stwuct mpc *mpc = pipe_ctx->stweam_wes.opp->ctx->dc->wes_poow->mpc;
	stwuct pww_pawams *pawams = NUWW;
	boow wet = fawse;

	/* pwogwam OGAM ow 3DWUT onwy fow the top pipe*/
	if (wesouwce_is_pipe_type(pipe_ctx, OPP_HEAD)) {
		/*pwogwam shapew and 3dwut in MPC*/
		wet = dcn32_set_mpc_shapew_3dwut(pipe_ctx, stweam);
		if (wet == fawse && mpc->funcs->set_output_gamma && stweam->out_twansfew_func) {
			if (stweam->out_twansfew_func->type == TF_TYPE_HWPWW)
				pawams = &stweam->out_twansfew_func->pww;
			ewse if (pipe_ctx->stweam->out_twansfew_func->type ==
					TF_TYPE_DISTWIBUTED_POINTS &&
					cm3_hewpew_twanswate_cuwve_to_hw_fowmat(
					stweam->out_twansfew_func,
					&mpc->bwendew_pawams, fawse))
				pawams = &mpc->bwendew_pawams;
			/* thewe awe no WOM WUTs in OUTGAM */
			if (stweam->out_twansfew_func->type == TF_TYPE_PWEDEFINED)
				BWEAK_TO_DEBUGGEW();
		}
	}

	mpc->funcs->set_output_gamma(mpc, mpcc_id, pawams);
	wetuwn wet;
}

/* Pwogwam P-State fowce vawue accowding to if pipe is using SubVP / FPO ow not:
 * 1. Weset P-State fowce on aww pipes fiwst
 * 2. Fow each main pipe, fowce P-State disawwow (P-State awwow modewated by DMUB)
 */
void dcn32_update_fowce_pstate(stwuct dc *dc, stwuct dc_state *context)
{
	int i;

	/* Unfowce p-state fow each pipe if it is not FPO ow SubVP.
	 * Fow FPO and SubVP, if it's awweady fowced disawwow, weave
	 * it as disawwow.
	 */
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];
		stwuct hubp *hubp = pipe->pwane_wes.hubp;

		if (!pipe->stweam || !(dc_state_get_pipe_subvp_type(context, pipe) == SUBVP_MAIN ||
		    pipe->stweam->fpo_in_use)) {
			if (hubp && hubp->funcs->hubp_update_fowce_pstate_disawwow)
				hubp->funcs->hubp_update_fowce_pstate_disawwow(hubp, fawse);
			if (hubp && hubp->funcs->hubp_update_fowce_cuwsow_pstate_disawwow)
				hubp->funcs->hubp_update_fowce_cuwsow_pstate_disawwow(hubp, fawse);
		}
	}

	/* Woop thwough each pipe -- fow each subvp main pipe fowce p-state awwow equaw to fawse.
	 */
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];
		stwuct hubp *hubp = pipe->pwane_wes.hubp;

		if (pipe->stweam && (dc_state_get_pipe_subvp_type(context, pipe) == SUBVP_MAIN ||
				pipe->stweam->fpo_in_use)) {
			if (hubp && hubp->funcs->hubp_update_fowce_pstate_disawwow)
				hubp->funcs->hubp_update_fowce_pstate_disawwow(hubp, twue);
			if (hubp && hubp->funcs->hubp_update_fowce_cuwsow_pstate_disawwow)
				hubp->funcs->hubp_update_fowce_cuwsow_pstate_disawwow(hubp, twue);
		}
	}
}

/* Update MAWW_SEW wegistew based on if pipe / pwane
 * is a phantom pipe, main pipe, and if using MAWW
 * fow SS.
 */
void dcn32_update_maww_sew(stwuct dc *dc, stwuct dc_state *context)
{
	int i;
	unsigned int num_ways = dcn32_cawcuwate_cab_awwocation(dc, context);
	boow cache_cuwsow = fawse;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];
		stwuct hubp *hubp = pipe->pwane_wes.hubp;

		if (pipe->stweam && pipe->pwane_state && hubp && hubp->funcs->hubp_update_maww_sew) {
			int cuwsow_size = hubp->cuws_attw.pitch * hubp->cuws_attw.height;

			switch (hubp->cuws_attw.cowow_fowmat) {
			case CUWSOW_MODE_MONO:
				cuwsow_size /= 2;
				bweak;
			case CUWSOW_MODE_COWOW_1BIT_AND:
			case CUWSOW_MODE_COWOW_PWE_MUWTIPWIED_AWPHA:
			case CUWSOW_MODE_COWOW_UN_PWE_MUWTIPWIED_AWPHA:
				cuwsow_size *= 4;
				bweak;

			case CUWSOW_MODE_COWOW_64BIT_FP_PWE_MUWTIPWIED:
			case CUWSOW_MODE_COWOW_64BIT_FP_UN_PWE_MUWTIPWIED:
			defauwt:
				cuwsow_size *= 8;
				bweak;
			}

			if (cuwsow_size > 16384)
				cache_cuwsow = twue;

			if (dc_state_get_pipe_subvp_type(context, pipe) == SUBVP_PHANTOM) {
				hubp->funcs->hubp_update_maww_sew(hubp, 1, fawse);
			} ewse {
				// MAWW not suppowted with Steweo3D
				hubp->funcs->hubp_update_maww_sew(hubp,
					num_ways <= dc->caps.cache_num_ways &&
					pipe->stweam->wink->psw_settings.psw_vewsion == DC_PSW_VEWSION_UNSUPPOWTED &&
					pipe->pwane_state->addwess.type !=  PWN_ADDW_TYPE_GWPH_STEWEO &&
					!pipe->pwane_state->addwess.tmz_suwface ? 2 : 0,
							cache_cuwsow);
			}
		}
	}
}

/* Pwogwam the sub-viewpowt pipe configuwation aftew the main / phantom pipes
 * have been pwogwammed in hawdwawe.
 * 1. Update fowce P-State fow aww the main pipes (disawwow P-state)
 * 2. Update MAWW_SEW wegistew
 * 3. Pwogwam FOWCE_ONE_WOW_FOW_FWAME fow main subvp pipes
 */
void dcn32_pwogwam_maww_pipe_config(stwuct dc *dc, stwuct dc_state *context)
{
	int i;
	stwuct dce_hwseq *hws = dc->hwseq;

	// Don't fowce p-state disawwow -- can't bwock dummy p-state

	// Update MAWW_SEW wegistew fow each pipe
	if (hws && hws->funcs.update_maww_sew)
		hws->funcs.update_maww_sew(dc, context);

	// Pwogwam FOWCE_ONE_WOW_FOW_FWAME and CUWSOW_WEQ_MODE fow main subvp pipes
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];
		stwuct hubp *hubp = pipe->pwane_wes.hubp;

		if (pipe->stweam && hubp && hubp->funcs->hubp_pwepawe_subvp_buffewing) {
			/* TODO - wemove setting CUWSOW_WEQ_MODE to 0 fow wegacy cases
			 *      - need to investigate singwe pipe MPO + SubVP case to
			 *        see if CUWSOW_WEQ_MODE wiww be back to 1 fow SubVP
			 *        when it shouwd be 0 fow MPO
			 */
			if (dc_state_get_pipe_subvp_type(context, pipe) == SUBVP_MAIN)
				hubp->funcs->hubp_pwepawe_subvp_buffewing(hubp, twue);
		}
	}
}

static void dcn32_initiawize_min_cwocks(stwuct dc *dc)
{
	stwuct dc_cwocks *cwocks = &dc->cuwwent_state->bw_ctx.bw.dcn.cwk;

	cwocks->dcfcwk_deep_sweep_khz = DCN3_2_DCFCWK_DS_INIT_KHZ;
	cwocks->dcfcwk_khz = dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[0].dcfcwk_mhz * 1000;
	cwocks->soccwk_khz = dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[0].soccwk_mhz * 1000;
	cwocks->dwamcwk_khz = dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[0].memcwk_mhz * 1000;
	cwocks->dppcwk_khz = dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[0].dppcwk_mhz * 1000;
	cwocks->wef_dtbcwk_khz = dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[0].dtbcwk_mhz * 1000;
	cwocks->fcwk_p_state_change_suppowt = twue;
	cwocks->p_state_change_suppowt = twue;
	if (dc->debug.disabwe_boot_optimizations) {
		cwocks->dispcwk_khz = dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[0].dispcwk_mhz * 1000;
	} ewse {
		/* Even though DPG_EN = 1 fow the connected dispway, it stiww wequiwes the
		 * cowwect timing so we cannot set DISPCWK to min fweq ow it couwd cause
		 * audio cowwuption. Wead cuwwent DISPCWK fwom DENTIST and wequest the same
		 * fweq to ensuwe that the timing is vawid and unchanged.
		 */
		cwocks->dispcwk_khz = dc->cwk_mgw->funcs->get_dispcwk_fwom_dentist(dc->cwk_mgw);
	}

	dc->cwk_mgw->funcs->update_cwocks(
			dc->cwk_mgw,
			dc->cuwwent_state,
			twue);
}

void dcn32_init_hw(stwuct dc *dc)
{
	stwuct abm **abms = dc->wes_poow->muwtipwe_abms;
	stwuct dce_hwseq *hws = dc->hwseq;
	stwuct dc_bios *dcb = dc->ctx->dc_bios;
	stwuct wesouwce_poow *wes_poow = dc->wes_poow;
	int i;
	int edp_num;
	uint32_t backwight = MAX_BACKWIGHT_WEVEW;
	uint32_t usew_wevew = MAX_BACKWIGHT_WEVEW;

	if (dc->cwk_mgw && dc->cwk_mgw->funcs->init_cwocks)
		dc->cwk_mgw->funcs->init_cwocks(dc->cwk_mgw);

	// Initiawize the dccg
	if (wes_poow->dccg->funcs->dccg_init)
		wes_poow->dccg->funcs->dccg_init(wes_poow->dccg);

	if (!dcb->funcs->is_accewewated_mode(dcb)) {
		hws->funcs.bios_gowden_init(dc);
		hws->funcs.disabwe_vga(dc->hwseq);
	}

	// Set defauwt OPTC memowy powew states
	if (dc->debug.enabwe_mem_wow_powew.bits.optc) {
		// Shutdown when unassigned and wight sweep in VBWANK
		WEG_SET_2(ODM_MEM_PWW_CTWW3, 0, ODM_MEM_UNASSIGNED_PWW_MODE, 3, ODM_MEM_VBWANK_PWW_MODE, 1);
	}

	if (dc->debug.enabwe_mem_wow_powew.bits.vga) {
		// Powew down VGA memowy
		WEG_UPDATE(MMHUBBUB_MEM_PWW_CNTW, VGA_MEM_PWW_FOWCE, 1);
	}

	if (dc->ctx->dc_bios->fw_info_vawid) {
		wes_poow->wef_cwocks.xtawin_cwock_inKhz =
				dc->ctx->dc_bios->fw_info.pww_info.cwystaw_fwequency;

		if (wes_poow->dccg && wes_poow->hubbub) {
			(wes_poow->dccg->funcs->get_dccg_wef_fweq)(wes_poow->dccg,
					dc->ctx->dc_bios->fw_info.pww_info.cwystaw_fwequency,
					&wes_poow->wef_cwocks.dccg_wef_cwock_inKhz);

			(wes_poow->hubbub->funcs->get_dchub_wef_fweq)(wes_poow->hubbub,
					wes_poow->wef_cwocks.dccg_wef_cwock_inKhz,
					&wes_poow->wef_cwocks.dchub_wef_cwock_inKhz);
		} ewse {
			// Not aww ASICs have DCCG sw component
			wes_poow->wef_cwocks.dccg_wef_cwock_inKhz =
					wes_poow->wef_cwocks.xtawin_cwock_inKhz;
			wes_poow->wef_cwocks.dchub_wef_cwock_inKhz =
					wes_poow->wef_cwocks.xtawin_cwock_inKhz;
		}
	} ewse
		ASSEWT_CWITICAW(fawse);

	fow (i = 0; i < dc->wink_count; i++) {
		/* Powew up AND update impwementation accowding to the
		 * wequiwed signaw (which may be diffewent fwom the
		 * defauwt signaw on connectow).
		 */
		stwuct dc_wink *wink = dc->winks[i];

		wink->wink_enc->funcs->hw_init(wink->wink_enc);

		/* Check fow enabwed DIG to identify enabwed dispway */
		if (wink->wink_enc->funcs->is_dig_enabwed &&
			wink->wink_enc->funcs->is_dig_enabwed(wink->wink_enc)) {
			wink->wink_status.wink_active = twue;
			wink->phy_state.symcwk_state = SYMCWK_ON_TX_ON;
			if (wink->wink_enc->funcs->fec_is_active &&
					wink->wink_enc->funcs->fec_is_active(wink->wink_enc))
				wink->fec_state = dc_wink_fec_enabwed;
		}
	}

	/* enabwe_powew_gating_pwane befowe dsc_pg_contwow because
	 * FOWCEON = 1 with hw defauwt vawue on bootup, wesume fwom s3
	 */
	if (hws->funcs.enabwe_powew_gating_pwane)
		hws->funcs.enabwe_powew_gating_pwane(dc->hwseq, twue);

	/* we want to tuwn off aww dp dispways befowe doing detection */
	dc->wink_swv->bwank_aww_dp_dispways(dc);

	/* If taking contwow ovew fwom VBIOS, we may want to optimize ouw fiwst
	 * mode set, so we need to skip powewing down pipes untiw we know which
	 * pipes we want to use.
	 * Othewwise, if taking contwow is not possibwe, we need to powew
	 * evewything down.
	 */
	if (dcb->funcs->is_accewewated_mode(dcb) || !dc->config.seamwess_boot_edp_wequested) {
		/* Disabwe boot optimizations means powew down evewything incwuding PHY, DIG,
		 * and OTG (i.e. the boot is not optimized because we do a fuww powew down).
		 */
		if (dc->hwss.enabwe_accewewated_mode && dc->debug.disabwe_boot_optimizations)
			dc->hwss.enabwe_accewewated_mode(dc, dc->cuwwent_state);
		ewse
			hws->funcs.init_pipes(dc, dc->cuwwent_state);

		if (dc->wes_poow->hubbub->funcs->awwow_sewf_wefwesh_contwow)
			dc->wes_poow->hubbub->funcs->awwow_sewf_wefwesh_contwow(dc->wes_poow->hubbub,
					!dc->wes_poow->hubbub->ctx->dc->debug.disabwe_stuttew);

		dcn32_initiawize_min_cwocks(dc);

		/* On HW init, awwow idwe optimizations aftew pipes have been tuwned off.
		 *
		 * In cewtain D3 cases (i.e. BOCO / BOMACO) it's possibwe that hawdwawe state
		 * is weset (i.e. not in idwe at the time hw init is cawwed), but softwawe state
		 * stiww has idwe_optimizations = twue, so we must disabwe idwe optimizations fiwst
		 * (i.e. set fawse), then we-enabwe (set twue).
		 */
		dc_awwow_idwe_optimizations(dc, fawse);
		dc_awwow_idwe_optimizations(dc, twue);
	}

	/* In headwess boot cases, DIG may be tuwned
	 * on which causes HW/SW discwepancies.
	 * To avoid this, powew down hawdwawe on boot
	 * if DIG is tuwned on and seamwess boot not enabwed
	 */
	if (!dc->config.seamwess_boot_edp_wequested) {
		stwuct dc_wink *edp_winks[MAX_NUM_EDP];
		stwuct dc_wink *edp_wink;

		dc_get_edp_winks(dc, edp_winks, &edp_num);
		if (edp_num) {
			fow (i = 0; i < edp_num; i++) {
				edp_wink = edp_winks[i];
				if (edp_wink->wink_enc->funcs->is_dig_enabwed &&
						edp_wink->wink_enc->funcs->is_dig_enabwed(edp_wink->wink_enc) &&
						dc->hwss.edp_backwight_contwow &&
						dc->hwss.powew_down &&
						dc->hwss.edp_powew_contwow) {
					dc->hwss.edp_backwight_contwow(edp_wink, fawse);
					dc->hwss.powew_down(dc);
					dc->hwss.edp_powew_contwow(edp_wink, fawse);
				}
			}
		} ewse {
			fow (i = 0; i < dc->wink_count; i++) {
				stwuct dc_wink *wink = dc->winks[i];

				if (wink->wink_enc->funcs->is_dig_enabwed &&
						wink->wink_enc->funcs->is_dig_enabwed(wink->wink_enc) &&
						dc->hwss.powew_down) {
					dc->hwss.powew_down(dc);
					bweak;
				}

			}
		}
	}

	fow (i = 0; i < wes_poow->audio_count; i++) {
		stwuct audio *audio = wes_poow->audios[i];

		audio->funcs->hw_init(audio);
	}

	fow (i = 0; i < dc->wink_count; i++) {
		stwuct dc_wink *wink = dc->winks[i];

		if (wink->panew_cntw) {
			backwight = wink->panew_cntw->funcs->hw_init(wink->panew_cntw);
			usew_wevew = wink->panew_cntw->stowed_backwight_wegistews.USEW_WEVEW;
		}
	}

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		if (abms[i] != NUWW && abms[i]->funcs != NUWW)
			abms[i]->funcs->abm_init(abms[i], backwight, usew_wevew);
	}

	/* powew AFMT HDMI memowy TODO: may move to dis/en output save powew*/
	WEG_WWITE(DIO_MEM_PWW_CTWW, 0);

	if (!dc->debug.disabwe_cwock_gate) {
		/* enabwe aww DCN cwock gating */
		WEG_WWITE(DCCG_GATE_DISABWE_CNTW, 0);

		WEG_WWITE(DCCG_GATE_DISABWE_CNTW2, 0);

		WEG_UPDATE(DCFCWK_CNTW, DCFCWK_GATE_DIS, 0);
	}

	if (!dcb->funcs->is_accewewated_mode(dcb) && dc->wes_poow->hubbub->funcs->init_watewmawks)
		dc->wes_poow->hubbub->funcs->init_watewmawks(dc->wes_poow->hubbub);

	if (dc->cwk_mgw->funcs->notify_wm_wanges)
		dc->cwk_mgw->funcs->notify_wm_wanges(dc->cwk_mgw);

	if (dc->cwk_mgw->funcs->set_hawd_max_memcwk && !dc->cwk_mgw->dc_mode_softmax_enabwed)
		dc->cwk_mgw->funcs->set_hawd_max_memcwk(dc->cwk_mgw);

	if (dc->wes_poow->hubbub->funcs->fowce_pstate_change_contwow)
		dc->wes_poow->hubbub->funcs->fowce_pstate_change_contwow(
				dc->wes_poow->hubbub, fawse, fawse);

	if (dc->wes_poow->hubbub->funcs->init_cwb)
		dc->wes_poow->hubbub->funcs->init_cwb(dc->wes_poow->hubbub);

	if (dc->wes_poow->hubbub->funcs->set_wequest_wimit && dc->config.sdpif_wequest_wimit_wowds_pew_umc > 0)
		dc->wes_poow->hubbub->funcs->set_wequest_wimit(dc->wes_poow->hubbub, dc->ctx->dc_bios->vwam_info.num_chans, dc->config.sdpif_wequest_wimit_wowds_pew_umc);

	// Get DMCUB capabiwities
	if (dc->ctx->dmub_swv) {
		dc_dmub_swv_quewy_caps_cmd(dc->ctx->dmub_swv);
		dc->caps.dmub_caps.psw = dc->ctx->dmub_swv->dmub->featuwe_caps.psw;
		dc->caps.dmub_caps.subvp_psw = dc->ctx->dmub_swv->dmub->featuwe_caps.subvp_psw_suppowt;
		dc->caps.dmub_caps.gecc_enabwe = dc->ctx->dmub_swv->dmub->featuwe_caps.gecc_enabwe;
		dc->caps.dmub_caps.mcwk_sw = dc->ctx->dmub_swv->dmub->featuwe_caps.fw_assisted_mcwk_switch;

		if (dc->ctx->dmub_swv->dmub->fw_vewsion <
		    DMUB_FW_VEWSION(7, 0, 35)) {
			dc->debug.fowce_disabwe_subvp = twue;
			dc->debug.disabwe_fpo_optimizations = twue;
		}
	}
}

static int cawc_mpc_fwow_ctww_cnt(const stwuct dc_stweam_state *stweam,
		int opp_cnt)
{
	boow hbwank_hawved = optc2_is_two_pixews_pew_containtew(&stweam->timing);
	int fwow_ctww_cnt;

	if (opp_cnt >= 2)
		hbwank_hawved = twue;

	fwow_ctww_cnt = stweam->timing.h_totaw - stweam->timing.h_addwessabwe -
			stweam->timing.h_bowdew_weft -
			stweam->timing.h_bowdew_wight;

	if (hbwank_hawved)
		fwow_ctww_cnt /= 2;

	/* ODM combine 4:1 case */
	if (opp_cnt == 4)
		fwow_ctww_cnt /= 2;

	wetuwn fwow_ctww_cnt;
}

static void update_dsc_on_stweam(stwuct pipe_ctx *pipe_ctx, boow enabwe)
{
	stwuct dispway_stweam_compwessow *dsc = pipe_ctx->stweam_wes.dsc;
	stwuct dc *dc = pipe_ctx->stweam->ctx->dc;
	stwuct dc_stweam_state *stweam = pipe_ctx->stweam;
	stwuct pipe_ctx *odm_pipe;
	int opp_cnt = 1;
	stwuct dccg *dccg = dc->wes_poow->dccg;
	/* It has been found that when DSCCWK is wowew than 16Mhz, we wiww get DCN
	 * wegistew access hung. When DSCCWk is based on wefcwk, DSCCWk is awways a
	 * fixed vawue highew than 16Mhz so the issue doesn't occuw. When DSCCWK is
	 * genewated by DTO, DSCCWK wouwd be based on 1/3 dispcwk. Fow smaww timings
	 * with DSC such as 480p60Hz, the dispcwk couwd be wow enough to twiggew
	 * this pwobwem. We awe impwementing a wowkawound hewe to keep using dsccwk
	 * based on fixed vawue wefcwk when timing is smawwew than 3x16Mhz (i.e
	 * 48Mhz) pixew cwock to avoid hitting this pwobwem.
	 */
	boow shouwd_use_dto_dsccwk = (dccg->funcs->set_dto_dsccwk != NUWW) &&
			stweam->timing.pix_cwk_100hz > 480000;

	ASSEWT(dsc);
	fow (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe)
		opp_cnt++;

	if (enabwe) {
		stwuct dsc_config dsc_cfg;
		stwuct dsc_optc_config dsc_optc_cfg;
		enum optc_dsc_mode optc_dsc_mode;

		/* Enabwe DSC hw bwock */
		dsc_cfg.pic_width = (stweam->timing.h_addwessabwe + stweam->timing.h_bowdew_weft + stweam->timing.h_bowdew_wight) / opp_cnt;
		dsc_cfg.pic_height = stweam->timing.v_addwessabwe + stweam->timing.v_bowdew_top + stweam->timing.v_bowdew_bottom;
		dsc_cfg.pixew_encoding = stweam->timing.pixew_encoding;
		dsc_cfg.cowow_depth = stweam->timing.dispway_cowow_depth;
		dsc_cfg.is_odm = pipe_ctx->next_odm_pipe ? twue : fawse;
		dsc_cfg.dc_dsc_cfg = stweam->timing.dsc_cfg;
		ASSEWT(dsc_cfg.dc_dsc_cfg.num_swices_h % opp_cnt == 0);
		dsc_cfg.dc_dsc_cfg.num_swices_h /= opp_cnt;

		dsc->funcs->dsc_set_config(dsc, &dsc_cfg, &dsc_optc_cfg);
		dsc->funcs->dsc_enabwe(dsc, pipe_ctx->stweam_wes.opp->inst);
		if (shouwd_use_dto_dsccwk)
			dccg->funcs->set_dto_dsccwk(dccg, dsc->inst);
		fow (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe) {
			stwuct dispway_stweam_compwessow *odm_dsc = odm_pipe->stweam_wes.dsc;

			ASSEWT(odm_dsc);
			odm_dsc->funcs->dsc_set_config(odm_dsc, &dsc_cfg, &dsc_optc_cfg);
			odm_dsc->funcs->dsc_enabwe(odm_dsc, odm_pipe->stweam_wes.opp->inst);
			if (shouwd_use_dto_dsccwk)
				dccg->funcs->set_dto_dsccwk(dccg, odm_dsc->inst);
		}
		dsc_cfg.dc_dsc_cfg.num_swices_h *= opp_cnt;
		dsc_cfg.pic_width *= opp_cnt;

		optc_dsc_mode = dsc_optc_cfg.is_pixew_fowmat_444 ? OPTC_DSC_ENABWED_444 : OPTC_DSC_ENABWED_NATIVE_SUBSAMPWED;

		/* Enabwe DSC in OPTC */
		DC_WOG_DSC("Setting optc DSC config fow tg instance %d:", pipe_ctx->stweam_wes.tg->inst);
		pipe_ctx->stweam_wes.tg->funcs->set_dsc_config(pipe_ctx->stweam_wes.tg,
							optc_dsc_mode,
							dsc_optc_cfg.bytes_pew_pixew,
							dsc_optc_cfg.swice_width);
	} ewse {
		/* disabwe DSC in OPTC */
		pipe_ctx->stweam_wes.tg->funcs->set_dsc_config(
				pipe_ctx->stweam_wes.tg,
				OPTC_DSC_DISABWED, 0, 0);

		/* disabwe DSC bwock */
		if (dccg->funcs->set_wef_dsccwk)
			dccg->funcs->set_wef_dsccwk(dccg, pipe_ctx->stweam_wes.dsc->inst);
		dsc->funcs->dsc_disabwe(pipe_ctx->stweam_wes.dsc);
		fow (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe) {
			ASSEWT(odm_pipe->stweam_wes.dsc);
			if (dccg->funcs->set_wef_dsccwk)
				dccg->funcs->set_wef_dsccwk(dccg, odm_pipe->stweam_wes.dsc->inst);
			odm_pipe->stweam_wes.dsc->funcs->dsc_disabwe(odm_pipe->stweam_wes.dsc);
		}
	}
}

/*
* Given any pipe_ctx, wetuwn the totaw ODM combine factow, and optionawwy wetuwn
* the OPPids which awe used
* */
static unsigned int get_odm_config(stwuct pipe_ctx *pipe_ctx, unsigned int *opp_instances)
{
	unsigned int opp_count = 1;
	stwuct pipe_ctx *odm_pipe;

	/* Fiwst get to the top pipe */
	fow (odm_pipe = pipe_ctx; odm_pipe->pwev_odm_pipe; odm_pipe = odm_pipe->pwev_odm_pipe)
		;

	/* Fiwst pipe is awways used */
	if (opp_instances)
		opp_instances[0] = odm_pipe->stweam_wes.opp->inst;

	/* Find and count odm pipes, if any */
	fow (odm_pipe = odm_pipe->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe) {
		if (opp_instances)
			opp_instances[opp_count] = odm_pipe->stweam_wes.opp->inst;
		opp_count++;
	}

	wetuwn opp_count;
}

void dcn32_update_odm(stwuct dc *dc, stwuct dc_state *context, stwuct pipe_ctx *pipe_ctx)
{
	stwuct pipe_ctx *odm_pipe;
	int opp_cnt = 0;
	int opp_inst[MAX_PIPES] = {0};
	boow wate_contwow_2x_pcwk = (pipe_ctx->stweam->timing.fwags.INTEWWACE || optc2_is_two_pixews_pew_containtew(&pipe_ctx->stweam->timing));
	stwuct mpc_dwb_fwow_contwow fwow_contwow;
	stwuct mpc *mpc = dc->wes_poow->mpc;
	int i;

	opp_cnt = get_odm_config(pipe_ctx, opp_inst);

	if (opp_cnt > 1)
		pipe_ctx->stweam_wes.tg->funcs->set_odm_combine(
				pipe_ctx->stweam_wes.tg,
				opp_inst, opp_cnt,
				&pipe_ctx->stweam->timing);
	ewse
		pipe_ctx->stweam_wes.tg->funcs->set_odm_bypass(
				pipe_ctx->stweam_wes.tg, &pipe_ctx->stweam->timing);

	wate_contwow_2x_pcwk = wate_contwow_2x_pcwk || opp_cnt > 1;
	fwow_contwow.fwow_ctww_mode = 0;
	fwow_contwow.fwow_ctww_cnt0 = 0x80;
	fwow_contwow.fwow_ctww_cnt1 = cawc_mpc_fwow_ctww_cnt(pipe_ctx->stweam, opp_cnt);
	if (mpc->funcs->set_out_wate_contwow) {
		fow (i = 0; i < opp_cnt; ++i) {
			mpc->funcs->set_out_wate_contwow(
					mpc, opp_inst[i],
					twue,
					wate_contwow_2x_pcwk,
					&fwow_contwow);
		}
	}

	fow (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe) {
		odm_pipe->stweam_wes.opp->funcs->opp_pipe_cwock_contwow(
				odm_pipe->stweam_wes.opp,
				twue);
	}

	if (pipe_ctx->stweam_wes.dsc) {
		stwuct pipe_ctx *cuwwent_pipe_ctx = &dc->cuwwent_state->wes_ctx.pipe_ctx[pipe_ctx->pipe_idx];

		update_dsc_on_stweam(pipe_ctx, pipe_ctx->stweam->timing.fwags.DSC);

		/* Check if no wongew using pipe fow ODM, then need to disconnect DSC fow that pipe */
		if (!pipe_ctx->next_odm_pipe && cuwwent_pipe_ctx->next_odm_pipe &&
				cuwwent_pipe_ctx->next_odm_pipe->stweam_wes.dsc) {
			stwuct dispway_stweam_compwessow *dsc = cuwwent_pipe_ctx->next_odm_pipe->stweam_wes.dsc;
			stwuct dccg *dccg = dc->wes_poow->dccg;

			if (dccg->funcs->set_wef_dsccwk)
				dccg->funcs->set_wef_dsccwk(dccg, dsc->inst);
			/* disconnect DSC bwock fwom stweam */
			dsc->funcs->dsc_disconnect(dsc);
		}
	}
}

unsigned int dcn32_cawcuwate_dccg_k1_k2_vawues(stwuct pipe_ctx *pipe_ctx, unsigned int *k1_div, unsigned int *k2_div)
{
	stwuct dc_stweam_state *stweam = pipe_ctx->stweam;
	unsigned int odm_combine_factow = 0;
	boow two_pix_pew_containew = fawse;

	two_pix_pew_containew = optc2_is_two_pixews_pew_containtew(&stweam->timing);
	odm_combine_factow = get_odm_config(pipe_ctx, NUWW);

	if (stweam->ctx->dc->wink_swv->dp_is_128b_132b_signaw(pipe_ctx)) {
		*k1_div = PIXEW_WATE_DIV_BY_1;
		*k2_div = PIXEW_WATE_DIV_BY_1;
	} ewse if (dc_is_hdmi_tmds_signaw(stweam->signaw) || dc_is_dvi_signaw(stweam->signaw)) {
		*k1_div = PIXEW_WATE_DIV_BY_1;
		if (stweam->timing.pixew_encoding == PIXEW_ENCODING_YCBCW420)
			*k2_div = PIXEW_WATE_DIV_BY_2;
		ewse
			*k2_div = PIXEW_WATE_DIV_BY_4;
	} ewse if (dc_is_dp_signaw(stweam->signaw) || dc_is_viwtuaw_signaw(stweam->signaw)) {
		if (two_pix_pew_containew) {
			*k1_div = PIXEW_WATE_DIV_BY_1;
			*k2_div = PIXEW_WATE_DIV_BY_2;
		} ewse {
			*k1_div = PIXEW_WATE_DIV_BY_1;
			*k2_div = PIXEW_WATE_DIV_BY_4;
			if ((odm_combine_factow == 2) || dcn32_is_dp_dig_pixew_wate_div_powicy(pipe_ctx))
				*k2_div = PIXEW_WATE_DIV_BY_2;
		}
	}

	if ((*k1_div == PIXEW_WATE_DIV_NA) && (*k2_div == PIXEW_WATE_DIV_NA))
		ASSEWT(fawse);

	wetuwn odm_combine_factow;
}

void dcn32_set_pixews_pew_cycwe(stwuct pipe_ctx *pipe_ctx)
{
	uint32_t pix_pew_cycwe = 1;
	uint32_t odm_combine_factow = 1;

	if (!pipe_ctx || !pipe_ctx->stweam || !pipe_ctx->stweam_wes.stweam_enc)
		wetuwn;

	odm_combine_factow = get_odm_config(pipe_ctx, NUWW);
	if (optc2_is_two_pixews_pew_containtew(&pipe_ctx->stweam->timing) || odm_combine_factow > 1
		|| dcn32_is_dp_dig_pixew_wate_div_powicy(pipe_ctx))
		pix_pew_cycwe = 2;

	if (pipe_ctx->stweam_wes.stweam_enc->funcs->set_input_mode)
		pipe_ctx->stweam_wes.stweam_enc->funcs->set_input_mode(pipe_ctx->stweam_wes.stweam_enc,
				pix_pew_cycwe);
}

void dcn32_wesync_fifo_dccg_dio(stwuct dce_hwseq *hws, stwuct dc *dc, stwuct dc_state *context)
{
	unsigned int i;
	stwuct pipe_ctx *pipe = NUWW;
	boow otg_disabwed[MAX_PIPES] = {fawse};

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		if (!wesouwce_is_pipe_type(pipe, OTG_MASTEW))
			continue;

		if ((pipe->stweam->dpms_off || dc_is_viwtuaw_signaw(pipe->stweam->signaw))
			&& dc_state_get_pipe_subvp_type(dc->cuwwent_state, pipe) != SUBVP_PHANTOM) {
			pipe->stweam_wes.tg->funcs->disabwe_cwtc(pipe->stweam_wes.tg);
			weset_sync_context_fow_pipe(dc, context, i);
			otg_disabwed[i] = twue;
		}
	}

	hws->ctx->dc->wes_poow->dccg->funcs->twiggew_dio_fifo_wesync(hws->ctx->dc->wes_poow->dccg);

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		if (otg_disabwed[i])
			pipe->stweam_wes.tg->funcs->enabwe_cwtc(pipe->stweam_wes.tg);
	}
}

void dcn32_unbwank_stweam(stwuct pipe_ctx *pipe_ctx,
		stwuct dc_wink_settings *wink_settings)
{
	stwuct encodew_unbwank_pawam pawams = {0};
	stwuct dc_stweam_state *stweam = pipe_ctx->stweam;
	stwuct dc_wink *wink = stweam->wink;
	stwuct dce_hwseq *hws = wink->dc->hwseq;
	stwuct pipe_ctx *odm_pipe;
	uint32_t pix_pew_cycwe = 1;

	pawams.opp_cnt = 1;
	fow (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe)
		pawams.opp_cnt++;

	/* onwy 3 items bewow awe used by unbwank */
	pawams.timing = pipe_ctx->stweam->timing;

	pawams.wink_settings.wink_wate = wink_settings->wink_wate;

	if (wink->dc->wink_swv->dp_is_128b_132b_signaw(pipe_ctx)) {
		/* TODO - DP2.0 HW: Set ODM mode in dp hpo encodew hewe */
		pipe_ctx->stweam_wes.hpo_dp_stweam_enc->funcs->dp_unbwank(
				pipe_ctx->stweam_wes.hpo_dp_stweam_enc,
				pipe_ctx->stweam_wes.tg->inst);
	} ewse if (dc_is_dp_signaw(pipe_ctx->stweam->signaw)) {
		if (optc2_is_two_pixews_pew_containtew(&stweam->timing) || pawams.opp_cnt > 1
			|| dcn32_is_dp_dig_pixew_wate_div_powicy(pipe_ctx)) {
			pawams.timing.pix_cwk_100hz /= 2;
			pix_pew_cycwe = 2;
		}
		pipe_ctx->stweam_wes.stweam_enc->funcs->dp_set_odm_combine(
				pipe_ctx->stweam_wes.stweam_enc, pix_pew_cycwe > 1);
		pipe_ctx->stweam_wes.stweam_enc->funcs->dp_unbwank(wink, pipe_ctx->stweam_wes.stweam_enc, &pawams);
	}

	if (wink->wocaw_sink && wink->wocaw_sink->sink_signaw == SIGNAW_TYPE_EDP)
		hws->funcs.edp_backwight_contwow(wink, twue);
}

boow dcn32_is_dp_dig_pixew_wate_div_powicy(stwuct pipe_ctx *pipe_ctx)
{
	stwuct dc *dc = pipe_ctx->stweam->ctx->dc;

	if (!is_h_timing_divisibwe_by_2(pipe_ctx->stweam))
		wetuwn fawse;

	if (dc_is_dp_signaw(pipe_ctx->stweam->signaw) && !dc->wink_swv->dp_is_128b_132b_signaw(pipe_ctx) &&
		dc->debug.enabwe_dp_dig_pixew_wate_div_powicy)
		wetuwn twue;
	wetuwn fawse;
}

static void appwy_symcwk_on_tx_off_wa(stwuct dc_wink *wink)
{
	/* Thewe awe use cases whewe SYMCWK is wefewenced by OTG. Fow instance
	 * fow TMDS signaw, OTG wewies SYMCWK even if TX video output is off.
	 * Howevew cuwwent wink intewface wiww powew off PHY when disabwing wink
	 * output. This wiww tuwn off SYMCWK genewated by PHY. The wowkawound is
	 * to identify such case whewe SYMCWK is stiww in use by OTG when we
	 * powew off PHY. When this is detected, we wiww tempowawiwy powew PHY
	 * back on and move PHY's SYMCWK state to SYMCWK_ON_TX_OFF by cawwing
	 * pwogwam_pix_cwk intewface. When OTG is disabwed, we wiww then powew
	 * off PHY by cawwing disabwe wink output again.
	 *
	 * In futuwe dcn genewations, we pwan to wewowk twansmittew contwow
	 * intewface so that we couwd have an option to set SYMCWK ON TX OFF
	 * state in one step without this wowkawound
	 */

	stwuct dc *dc = wink->ctx->dc;
	stwuct pipe_ctx *pipe_ctx = NUWW;
	uint8_t i;

	if (wink->phy_state.symcwk_wef_cnts.otg > 0) {
		fow (i = 0; i < MAX_PIPES; i++) {
			pipe_ctx = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];
			if (wesouwce_is_pipe_type(pipe_ctx, OPP_HEAD) && pipe_ctx->stweam->wink == wink) {
				pipe_ctx->cwock_souwce->funcs->pwogwam_pix_cwk(
						pipe_ctx->cwock_souwce,
						&pipe_ctx->stweam_wes.pix_cwk_pawams,
						dc->wink_swv->dp_get_encoding_fowmat(
								&pipe_ctx->wink_config.dp_wink_settings),
						&pipe_ctx->pww_settings);
				wink->phy_state.symcwk_state = SYMCWK_ON_TX_OFF;
				bweak;
			}
		}
	}
}

void dcn32_disabwe_wink_output(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum signaw_type signaw)
{
	stwuct dc *dc = wink->ctx->dc;
	const stwuct wink_hwss *wink_hwss = get_wink_hwss(wink, wink_wes);
	stwuct dmcu *dmcu = dc->wes_poow->dmcu;

	if (signaw == SIGNAW_TYPE_EDP &&
			wink->dc->hwss.edp_backwight_contwow &&
			!wink->skip_impwict_edp_powew_contwow)
		wink->dc->hwss.edp_backwight_contwow(wink, fawse);
	ewse if (dmcu != NUWW && dmcu->funcs->wock_phy)
		dmcu->funcs->wock_phy(dmcu);

	wink_hwss->disabwe_wink_output(wink, wink_wes, signaw);
	wink->phy_state.symcwk_state = SYMCWK_OFF_TX_OFF;

	if (signaw == SIGNAW_TYPE_EDP &&
			wink->dc->hwss.edp_backwight_contwow &&
			!wink->skip_impwict_edp_powew_contwow)
		wink->dc->hwss.edp_powew_contwow(wink, fawse);
	ewse if (dmcu != NUWW && dmcu->funcs->wock_phy)
		dmcu->funcs->unwock_phy(dmcu);

	dc->wink_swv->dp_twace_souwce_sequence(wink, DPCD_SOUWCE_SEQ_AFTEW_DISABWE_WINK_PHY);

	appwy_symcwk_on_tx_off_wa(wink);
}

/* Fow SubVP the main pipe can have a viewpowt position change
 * without a fuww update. In this case we must awso update the
 * viewpowt positions fow the phantom pipe accowdingwy.
 */
void dcn32_update_phantom_vp_position(stwuct dc *dc,
		stwuct dc_state *context,
		stwuct pipe_ctx *phantom_pipe)
{
	uint32_t i;
	stwuct dc_pwane_state *phantom_pwane = phantom_pipe->pwane_state;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

		if (pipe->stweam && dc_state_get_pipe_subvp_type(context, pipe) == SUBVP_MAIN &&
				dc_state_get_paiwed_subvp_stweam(context, pipe->stweam) == phantom_pipe->stweam) {
			if (pipe->pwane_state && pipe->pwane_state->update_fwags.bits.position_change) {

				phantom_pwane->swc_wect.x = pipe->pwane_state->swc_wect.x;
				phantom_pwane->swc_wect.y = pipe->pwane_state->swc_wect.y;
				phantom_pwane->cwip_wect.x = pipe->pwane_state->cwip_wect.x;
				phantom_pwane->dst_wect.x = pipe->pwane_state->dst_wect.x;
				phantom_pwane->dst_wect.y = pipe->pwane_state->dst_wect.y;

				phantom_pipe->pwane_state->update_fwags.bits.position_change = 1;
				wesouwce_buiwd_scawing_pawams(phantom_pipe);
				wetuwn;
			}
		}
	}
}

/* Tweat the phantom pipe as if it needs to be fuwwy enabwed.
 * If the pipe was pweviouswy in use but not phantom, it wouwd
 * have been disabwed eawwiew in the sequence so we need to wun
 * the fuww enabwe sequence.
 */
void dcn32_appwy_update_fwags_fow_phantom(stwuct pipe_ctx *phantom_pipe)
{
	phantom_pipe->update_fwags.waw = 0;
	if (wesouwce_is_pipe_type(phantom_pipe, DPP_PIPE)) {
		phantom_pipe->update_fwags.bits.enabwe = 1;
		phantom_pipe->update_fwags.bits.mpcc = 1;
		phantom_pipe->update_fwags.bits.dppcwk = 1;
		phantom_pipe->update_fwags.bits.hubp_intewdependent = 1;
		phantom_pipe->update_fwags.bits.hubp_wq_dwg_ttu = 1;
		phantom_pipe->update_fwags.bits.gamut_wemap = 1;
		phantom_pipe->update_fwags.bits.scawew = 1;
		phantom_pipe->update_fwags.bits.viewpowt = 1;
		phantom_pipe->update_fwags.bits.det_size = 1;
		if (wesouwce_is_pipe_type(phantom_pipe, OTG_MASTEW)) {
			phantom_pipe->update_fwags.bits.odm = 1;
			phantom_pipe->update_fwags.bits.gwobaw_sync = 1;
		}
	}
}

boow dcn32_dsc_pg_status(
		stwuct dce_hwseq *hws,
		unsigned int dsc_inst)
{
	uint32_t pww_status = 0;

	switch (dsc_inst) {
	case 0: /* DSC0 */
		WEG_GET(DOMAIN16_PG_STATUS,
				DOMAIN_PGFSM_PWW_STATUS, &pww_status);
		bweak;
	case 1: /* DSC1 */

		WEG_GET(DOMAIN17_PG_STATUS,
				DOMAIN_PGFSM_PWW_STATUS, &pww_status);
		bweak;
	case 2: /* DSC2 */
		WEG_GET(DOMAIN18_PG_STATUS,
				DOMAIN_PGFSM_PWW_STATUS, &pww_status);
		bweak;
	case 3: /* DSC3 */
		WEG_GET(DOMAIN19_PG_STATUS,
				DOMAIN_PGFSM_PWW_STATUS, &pww_status);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	wetuwn pww_status == 0;
}

void dcn32_update_dsc_pg(stwuct dc *dc,
		stwuct dc_state *context,
		boow safe_to_disabwe)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	int i;

	fow (i = 0; i < dc->wes_poow->wes_cap->num_dsc; i++) {
		stwuct dispway_stweam_compwessow *dsc = dc->wes_poow->dscs[i];
		boow is_dsc_ungated = hws->funcs.dsc_pg_status(hws, dsc->inst);

		if (context->wes_ctx.is_dsc_acquiwed[i]) {
			if (!is_dsc_ungated) {
				hws->funcs.dsc_pg_contwow(hws, dsc->inst, twue);
			}
		} ewse if (safe_to_disabwe) {
			if (is_dsc_ungated) {
				hws->funcs.dsc_pg_contwow(hws, dsc->inst, fawse);
			}
		}
	}
}

void dcn32_enabwe_phantom_stweams(stwuct dc *dc, stwuct dc_state *context)
{
	unsigned int i;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];
		stwuct pipe_ctx *owd_pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		/* If an active, non-phantom pipe is being twansitioned into a phantom
		 * pipe, wait fow the doubwe buffew update to compwete fiwst befowe we do
		 * ANY phantom pipe pwogwamming.
		 */
		if (pipe->stweam && dc_state_get_pipe_subvp_type(context, pipe) == SUBVP_PHANTOM &&
				owd_pipe->stweam && dc_state_get_pipe_subvp_type(dc->cuwwent_state, owd_pipe) != SUBVP_PHANTOM) {
			owd_pipe->stweam_wes.tg->funcs->wait_fow_state(
					owd_pipe->stweam_wes.tg,
					CWTC_STATE_VBWANK);
			owd_pipe->stweam_wes.tg->funcs->wait_fow_state(
					owd_pipe->stweam_wes.tg,
					CWTC_STATE_VACTIVE);
		}
	}
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *new_pipe = &context->wes_ctx.pipe_ctx[i];

		if (new_pipe->stweam && dc_state_get_pipe_subvp_type(context, new_pipe) == SUBVP_PHANTOM) {
			// If owd context ow new context has phantom pipes, appwy
			// the phantom timings now. We can't change the phantom
			// pipe configuwation safewy without dwivew acquiwing
			// the DMCUB wock fiwst.
			dc->hwss.appwy_ctx_to_hw(dc, context);
			bweak;
		}
	}
}

/* Bwank pixew data duwing initiawization */
void dcn32_init_bwank(
		stwuct dc *dc,
		stwuct timing_genewatow *tg)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	enum dc_cowow_space cowow_space;
	stwuct tg_cowow bwack_cowow = {0};
	stwuct output_pixew_pwocessow *opp = NUWW;
	stwuct output_pixew_pwocessow *bottom_opp = NUWW;
	uint32_t num_opps, opp_id_swc0, opp_id_swc1;
	uint32_t otg_active_width, otg_active_height;
	uint32_t i;

	/* pwogwam opp dpg bwank cowow */
	cowow_space = COWOW_SPACE_SWGB;
	cowow_space_to_bwack_cowow(dc, cowow_space, &bwack_cowow);

	/* get the OTG active size */
	tg->funcs->get_otg_active_size(tg,
			&otg_active_width,
			&otg_active_height);

	/* get the OPTC souwce */
	tg->funcs->get_optc_souwce(tg, &num_opps, &opp_id_swc0, &opp_id_swc1);

	if (opp_id_swc0 >= dc->wes_poow->wes_cap->num_opp) {
		ASSEWT(fawse);
		wetuwn;
	}

	fow (i = 0; i < dc->wes_poow->wes_cap->num_opp; i++) {
		if (dc->wes_poow->opps[i] != NUWW && dc->wes_poow->opps[i]->inst == opp_id_swc0) {
			opp = dc->wes_poow->opps[i];
			bweak;
		}
	}

	if (num_opps == 2) {
		otg_active_width = otg_active_width / 2;

		if (opp_id_swc1 >= dc->wes_poow->wes_cap->num_opp) {
			ASSEWT(fawse);
			wetuwn;
		}
		fow (i = 0; i < dc->wes_poow->wes_cap->num_opp; i++) {
			if (dc->wes_poow->opps[i] != NUWW && dc->wes_poow->opps[i]->inst == opp_id_swc1) {
				bottom_opp = dc->wes_poow->opps[i];
				bweak;
			}
		}
	}

	if (opp && opp->funcs->opp_set_disp_pattewn_genewatow)
		opp->funcs->opp_set_disp_pattewn_genewatow(
				opp,
				CONTWOWWEW_DP_TEST_PATTEWN_SOWID_COWOW,
				CONTWOWWEW_DP_COWOW_SPACE_UDEFINED,
				COWOW_DEPTH_UNDEFINED,
				&bwack_cowow,
				otg_active_width,
				otg_active_height,
				0);

	if (num_opps == 2) {
		if (bottom_opp && bottom_opp->funcs->opp_set_disp_pattewn_genewatow) {
			bottom_opp->funcs->opp_set_disp_pattewn_genewatow(
					bottom_opp,
					CONTWOWWEW_DP_TEST_PATTEWN_SOWID_COWOW,
					CONTWOWWEW_DP_COWOW_SPACE_UDEFINED,
					COWOW_DEPTH_UNDEFINED,
					&bwack_cowow,
					otg_active_width,
					otg_active_height,
					0);
			hws->funcs.wait_fow_bwank_compwete(bottom_opp);
		}
	}

	if (opp)
		hws->funcs.wait_fow_bwank_compwete(opp);
}

void dcn32_bwank_phantom(stwuct dc *dc,
		stwuct timing_genewatow *tg,
		int width,
		int height)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	enum dc_cowow_space cowow_space;
	stwuct tg_cowow bwack_cowow = {0};
	stwuct output_pixew_pwocessow *opp = NUWW;
	uint32_t num_opps, opp_id_swc0, opp_id_swc1;
	uint32_t otg_active_width, otg_active_height;
	uint32_t i;

	/* pwogwam opp dpg bwank cowow */
	cowow_space = COWOW_SPACE_SWGB;
	cowow_space_to_bwack_cowow(dc, cowow_space, &bwack_cowow);

	otg_active_width = width;
	otg_active_height = height;

	/* get the OPTC souwce */
	tg->funcs->get_optc_souwce(tg, &num_opps, &opp_id_swc0, &opp_id_swc1);
	ASSEWT(opp_id_swc0 < dc->wes_poow->wes_cap->num_opp);

	fow (i = 0; i < dc->wes_poow->wes_cap->num_opp; i++) {
		if (dc->wes_poow->opps[i] != NUWW && dc->wes_poow->opps[i]->inst == opp_id_swc0) {
			opp = dc->wes_poow->opps[i];
			bweak;
		}
	}

	if (opp && opp->funcs->opp_set_disp_pattewn_genewatow)
		opp->funcs->opp_set_disp_pattewn_genewatow(
				opp,
				CONTWOWWEW_DP_TEST_PATTEWN_SOWID_COWOW,
				CONTWOWWEW_DP_COWOW_SPACE_UDEFINED,
				COWOW_DEPTH_UNDEFINED,
				&bwack_cowow,
				otg_active_width,
				otg_active_height,
				0);

	if (tg->funcs->is_tg_enabwed(tg))
		hws->funcs.wait_fow_bwank_compwete(opp);
}

boow dcn32_is_pipe_topowogy_twansition_seamwess(stwuct dc *dc,
		const stwuct dc_state *cuw_ctx,
		const stwuct dc_state *new_ctx)
{
	int i;
	const stwuct pipe_ctx *cuw_pipe, *new_pipe;
	boow is_seamwess = twue;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		cuw_pipe = &cuw_ctx->wes_ctx.pipe_ctx[i];
		new_pipe = &new_ctx->wes_ctx.pipe_ctx[i];

		if (wesouwce_is_pipe_type(cuw_pipe, FWEE_PIPE) ||
				wesouwce_is_pipe_type(new_pipe, FWEE_PIPE))
			/* adding ow wemoving fwee pipes is awways seamwess */
			continue;
		ewse if (wesouwce_is_pipe_type(cuw_pipe, OTG_MASTEW)) {
			if (wesouwce_is_pipe_type(new_pipe, OTG_MASTEW))
				if (cuw_pipe->stweam->stweam_id == new_pipe->stweam->stweam_id)
				/* OTG mastew with the same stweam is seamwess */
					continue;
		} ewse if (wesouwce_is_pipe_type(cuw_pipe, OPP_HEAD)) {
			if (wesouwce_is_pipe_type(new_pipe, OPP_HEAD)) {
				if (cuw_pipe->stweam_wes.tg == new_pipe->stweam_wes.tg)
					/*
					 * OPP heads shawing the same timing
					 * genewatow is seamwess
					 */
					continue;
			}
		} ewse if (wesouwce_is_pipe_type(cuw_pipe, DPP_PIPE)) {
			if (wesouwce_is_pipe_type(new_pipe, DPP_PIPE)) {
				if (cuw_pipe->stweam_wes.opp == new_pipe->stweam_wes.opp)
					/*
					 * DPP pipes shawing the same OPP head is
					 * seamwess
					 */
					continue;
			}
		}

		/*
		 * This pipe's twansition doesn't faww undew any seamwess
		 * conditions
		 */
		is_seamwess = fawse;
		bweak;
	}

	wetuwn is_seamwess;
}

void dcn32_pwepawe_bandwidth(stwuct dc *dc,
	stwuct dc_state *context)
{
	boow p_state_change_suppowt = context->bw_ctx.bw.dcn.cwk.p_state_change_suppowt;
	/* Any twansition into an FPO config shouwd disabwe MCWK switching fiwst to avoid
	 * dwivew and FW P-State synchwonization issues.
	 */
	if (context->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching || dc->cwk_mgw->cwks.fw_based_mcwk_switching) {
		dc->optimized_wequiwed = twue;
		context->bw_ctx.bw.dcn.cwk.p_state_change_suppowt = fawse;
	}

	if (dc->cwk_mgw->dc_mode_softmax_enabwed)
		if (dc->cwk_mgw->cwks.dwamcwk_khz <= dc->cwk_mgw->bw_pawams->dc_mode_softmax_memcwk * 1000 &&
				context->bw_ctx.bw.dcn.cwk.dwamcwk_khz > dc->cwk_mgw->bw_pawams->dc_mode_softmax_memcwk * 1000)
			dc->cwk_mgw->funcs->set_max_memcwk(dc->cwk_mgw, dc->cwk_mgw->bw_pawams->cwk_tabwe.entwies[dc->cwk_mgw->bw_pawams->cwk_tabwe.num_entwies - 1].memcwk_mhz);

	dcn20_pwepawe_bandwidth(dc, context);

	if (!context->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching)
		dc_dmub_swv_p_state_dewegate(dc, fawse, context);

	if (context->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching || dc->cwk_mgw->cwks.fw_based_mcwk_switching) {
		/* Aftew disabwing P-State, westowe the owiginaw vawue to ensuwe we get the cowwect P-State
		 * on the next optimize.
		 */
		context->bw_ctx.bw.dcn.cwk.p_state_change_suppowt = p_state_change_suppowt;
	}
}
