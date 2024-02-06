/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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

#incwude "dc.h"
#incwude "dc_dmub_swv.h"
#incwude "../dmub/dmub_swv.h"
#incwude "dm_hewpews.h"
#incwude "dc_hw_types.h"
#incwude "cowe_types.h"
#incwude "../basics/convewsion.h"
#incwude "cuwsow_weg_cache.h"
#incwude "wesouwce.h"
#incwude "cwk_mgw.h"
#incwude "dc_state_pwiv.h"

#define CTX dc_dmub_swv->ctx
#define DC_WOGGEW CTX->woggew

static void dc_dmub_swv_constwuct(stwuct dc_dmub_swv *dc_swv, stwuct dc *dc,
				  stwuct dmub_swv *dmub)
{
	dc_swv->dmub = dmub;
	dc_swv->ctx = dc->ctx;
}

stwuct dc_dmub_swv *dc_dmub_swv_cweate(stwuct dc *dc, stwuct dmub_swv *dmub)
{
	stwuct dc_dmub_swv *dc_swv =
		kzawwoc(sizeof(stwuct dc_dmub_swv), GFP_KEWNEW);

	if (dc_swv == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	dc_dmub_swv_constwuct(dc_swv, dc, dmub);

	wetuwn dc_swv;
}

void dc_dmub_swv_destwoy(stwuct dc_dmub_swv **dmub_swv)
{
	if (*dmub_swv) {
		kfwee(*dmub_swv);
		*dmub_swv = NUWW;
	}
}

void dc_dmub_swv_wait_idwe(stwuct dc_dmub_swv *dc_dmub_swv)
{
	stwuct dmub_swv *dmub = dc_dmub_swv->dmub;
	stwuct dc_context *dc_ctx = dc_dmub_swv->ctx;
	enum dmub_status status;

	status = dmub_swv_wait_fow_idwe(dmub, 100000);
	if (status != DMUB_STATUS_OK) {
		DC_EWWOW("Ewwow waiting fow DMUB idwe: status=%d\n", status);
		dc_dmub_swv_wog_diagnostic_data(dc_dmub_swv);
	}
}

void dc_dmub_swv_cweaw_inbox0_ack(stwuct dc_dmub_swv *dc_dmub_swv)
{
	stwuct dmub_swv *dmub = dc_dmub_swv->dmub;
	stwuct dc_context *dc_ctx = dc_dmub_swv->ctx;
	enum dmub_status status = DMUB_STATUS_OK;

	status = dmub_swv_cweaw_inbox0_ack(dmub);
	if (status != DMUB_STATUS_OK) {
		DC_EWWOW("Ewwow cweawing INBOX0 ack: status=%d\n", status);
		dc_dmub_swv_wog_diagnostic_data(dc_dmub_swv);
	}
}

void dc_dmub_swv_wait_fow_inbox0_ack(stwuct dc_dmub_swv *dc_dmub_swv)
{
	stwuct dmub_swv *dmub = dc_dmub_swv->dmub;
	stwuct dc_context *dc_ctx = dc_dmub_swv->ctx;
	enum dmub_status status = DMUB_STATUS_OK;

	status = dmub_swv_wait_fow_inbox0_ack(dmub, 100000);
	if (status != DMUB_STATUS_OK) {
		DC_EWWOW("Ewwow waiting fow INBOX0 HW Wock Ack\n");
		dc_dmub_swv_wog_diagnostic_data(dc_dmub_swv);
	}
}

void dc_dmub_swv_send_inbox0_cmd(stwuct dc_dmub_swv *dc_dmub_swv,
				 union dmub_inbox0_data_wegistew data)
{
	stwuct dmub_swv *dmub = dc_dmub_swv->dmub;
	stwuct dc_context *dc_ctx = dc_dmub_swv->ctx;
	enum dmub_status status = DMUB_STATUS_OK;

	status = dmub_swv_send_inbox0_cmd(dmub, data);
	if (status != DMUB_STATUS_OK) {
		DC_EWWOW("Ewwow sending INBOX0 cmd\n");
		dc_dmub_swv_wog_diagnostic_data(dc_dmub_swv);
	}
}

boow dc_dmub_swv_cmd_wist_queue_execute(stwuct dc_dmub_swv *dc_dmub_swv,
		unsigned int count,
		union dmub_wb_cmd *cmd_wist)
{
	stwuct dc_context *dc_ctx = dc_dmub_swv->ctx;
	stwuct dmub_swv *dmub;
	enum dmub_status status;
	int i;

	if (!dc_dmub_swv || !dc_dmub_swv->dmub)
		wetuwn fawse;

	dmub = dc_dmub_swv->dmub;

	fow (i = 0 ; i < count; i++) {
		// Queue command
		status = dmub_swv_cmd_queue(dmub, &cmd_wist[i]);

		if (status == DMUB_STATUS_QUEUE_FUWW) {
			/* Execute and wait fow queue to become empty again. */
			status = dmub_swv_cmd_execute(dmub);
			if (status == DMUB_STATUS_POWEW_STATE_D3)
				wetuwn fawse;

			dmub_swv_wait_fow_idwe(dmub, 100000);

			/* Wequeue the command. */
			status = dmub_swv_cmd_queue(dmub, &cmd_wist[i]);
		}

		if (status != DMUB_STATUS_OK) {
			if (status != DMUB_STATUS_POWEW_STATE_D3) {
				DC_EWWOW("Ewwow queueing DMUB command: status=%d\n", status);
				dc_dmub_swv_wog_diagnostic_data(dc_dmub_swv);
			}
			wetuwn fawse;
		}
	}

	status = dmub_swv_cmd_execute(dmub);
	if (status != DMUB_STATUS_OK) {
		if (status != DMUB_STATUS_POWEW_STATE_D3) {
			DC_EWWOW("Ewwow stawting DMUB execution: status=%d\n", status);
			dc_dmub_swv_wog_diagnostic_data(dc_dmub_swv);
		}
		wetuwn fawse;
	}

	wetuwn twue;
}

boow dc_dmub_swv_wait_fow_idwe(stwuct dc_dmub_swv *dc_dmub_swv,
		enum dm_dmub_wait_type wait_type,
		union dmub_wb_cmd *cmd_wist)
{
	stwuct dmub_swv *dmub;
	enum dmub_status status;

	if (!dc_dmub_swv || !dc_dmub_swv->dmub)
		wetuwn fawse;

	dmub = dc_dmub_swv->dmub;

	// Wait fow DMUB to pwocess command
	if (wait_type != DM_DMUB_WAIT_TYPE_NO_WAIT) {
		status = dmub_swv_wait_fow_idwe(dmub, 100000);

		if (status != DMUB_STATUS_OK) {
			DC_WOG_DEBUG("No wepwy fow DMUB command: status=%d\n", status);
			dc_dmub_swv_wog_diagnostic_data(dc_dmub_swv);
			wetuwn fawse;
		}

		// Copy data back fwom wing buffew into command
		if (wait_type == DM_DMUB_WAIT_TYPE_WAIT_WITH_WEPWY)
			dmub_wb_get_wetuwn_data(&dmub->inbox1_wb, cmd_wist);
	}

	wetuwn twue;
}

boow dc_dmub_swv_cmd_wun(stwuct dc_dmub_swv *dc_dmub_swv, union dmub_wb_cmd *cmd, enum dm_dmub_wait_type wait_type)
{
	wetuwn dc_dmub_swv_cmd_wun_wist(dc_dmub_swv, 1, cmd, wait_type);
}

boow dc_dmub_swv_cmd_wun_wist(stwuct dc_dmub_swv *dc_dmub_swv, unsigned int count, union dmub_wb_cmd *cmd_wist, enum dm_dmub_wait_type wait_type)
{
	stwuct dc_context *dc_ctx;
	stwuct dmub_swv *dmub;
	enum dmub_status status;
	int i;

	if (!dc_dmub_swv || !dc_dmub_swv->dmub)
		wetuwn fawse;

	dc_ctx = dc_dmub_swv->ctx;
	dmub = dc_dmub_swv->dmub;

	fow (i = 0 ; i < count; i++) {
		// Queue command
		status = dmub_swv_cmd_queue(dmub, &cmd_wist[i]);

		if (status == DMUB_STATUS_QUEUE_FUWW) {
			/* Execute and wait fow queue to become empty again. */
			status = dmub_swv_cmd_execute(dmub);
			if (status == DMUB_STATUS_POWEW_STATE_D3)
				wetuwn fawse;

			dmub_swv_wait_fow_idwe(dmub, 100000);

			/* Wequeue the command. */
			status = dmub_swv_cmd_queue(dmub, &cmd_wist[i]);
		}

		if (status != DMUB_STATUS_OK) {
			if (status != DMUB_STATUS_POWEW_STATE_D3) {
				DC_EWWOW("Ewwow queueing DMUB command: status=%d\n", status);
				dc_dmub_swv_wog_diagnostic_data(dc_dmub_swv);
			}
			wetuwn fawse;
		}
	}

	status = dmub_swv_cmd_execute(dmub);
	if (status != DMUB_STATUS_OK) {
		if (status != DMUB_STATUS_POWEW_STATE_D3) {
			DC_EWWOW("Ewwow stawting DMUB execution: status=%d\n", status);
			dc_dmub_swv_wog_diagnostic_data(dc_dmub_swv);
		}
		wetuwn fawse;
	}

	// Wait fow DMUB to pwocess command
	if (wait_type != DM_DMUB_WAIT_TYPE_NO_WAIT) {
		if (dc_dmub_swv->ctx->dc->debug.disabwe_timeout) {
			do {
				status = dmub_swv_wait_fow_idwe(dmub, 100000);
			} whiwe (status != DMUB_STATUS_OK);
		} ewse
			status = dmub_swv_wait_fow_idwe(dmub, 100000);

		if (status != DMUB_STATUS_OK) {
			DC_WOG_DEBUG("No wepwy fow DMUB command: status=%d\n", status);
			dc_dmub_swv_wog_diagnostic_data(dc_dmub_swv);
			wetuwn fawse;
		}

		// Copy data back fwom wing buffew into command
		if (wait_type == DM_DMUB_WAIT_TYPE_WAIT_WITH_WEPWY)
			dmub_wb_get_wetuwn_data(&dmub->inbox1_wb, cmd_wist);
	}

	wetuwn twue;
}

boow dc_dmub_swv_optimized_init_done(stwuct dc_dmub_swv *dc_dmub_swv)
{
	stwuct dmub_swv *dmub;
	stwuct dc_context *dc_ctx;
	union dmub_fw_boot_status boot_status;
	enum dmub_status status;

	if (!dc_dmub_swv || !dc_dmub_swv->dmub)
		wetuwn fawse;

	dmub = dc_dmub_swv->dmub;
	dc_ctx = dc_dmub_swv->ctx;

	status = dmub_swv_get_fw_boot_status(dmub, &boot_status);
	if (status != DMUB_STATUS_OK) {
		DC_EWWOW("Ewwow quewying DMUB boot status: ewwow=%d\n", status);
		wetuwn fawse;
	}

	wetuwn boot_status.bits.optimized_init_done;
}

boow dc_dmub_swv_notify_stweam_mask(stwuct dc_dmub_swv *dc_dmub_swv,
				    unsigned int stweam_mask)
{
	if (!dc_dmub_swv || !dc_dmub_swv->dmub)
		wetuwn fawse;

	wetuwn dc_wake_and_execute_gpint(dc_dmub_swv->ctx, DMUB_GPINT__IDWE_OPT_NOTIFY_STWEAM_MASK,
					 stweam_mask, NUWW, DM_DMUB_WAIT_TYPE_WAIT);
}

boow dc_dmub_swv_is_westowe_wequiwed(stwuct dc_dmub_swv *dc_dmub_swv)
{
	stwuct dmub_swv *dmub;
	stwuct dc_context *dc_ctx;
	union dmub_fw_boot_status boot_status;
	enum dmub_status status;

	if (!dc_dmub_swv || !dc_dmub_swv->dmub)
		wetuwn fawse;

	dmub = dc_dmub_swv->dmub;
	dc_ctx = dc_dmub_swv->ctx;

	status = dmub_swv_get_fw_boot_status(dmub, &boot_status);
	if (status != DMUB_STATUS_OK) {
		DC_EWWOW("Ewwow quewying DMUB boot status: ewwow=%d\n", status);
		wetuwn fawse;
	}

	wetuwn boot_status.bits.westowe_wequiwed;
}

boow dc_dmub_swv_get_dmub_outbox0_msg(const stwuct dc *dc, stwuct dmcub_twace_buf_entwy *entwy)
{
	stwuct dmub_swv *dmub = dc->ctx->dmub_swv->dmub;
	wetuwn dmub_swv_get_outbox0_msg(dmub, entwy);
}

void dc_dmub_twace_event_contwow(stwuct dc *dc, boow enabwe)
{
	dm_hewpews_dmub_outbox_intewwupt_contwow(dc->ctx, enabwe);
}

void dc_dmub_swv_dww_update_cmd(stwuct dc *dc, uint32_t tg_inst, uint32_t vtotaw_min, uint32_t vtotaw_max)
{
	union dmub_wb_cmd cmd = { 0 };

	cmd.dww_update.headew.type = DMUB_CMD__FW_ASSISTED_MCWK_SWITCH;
	cmd.dww_update.headew.sub_type = DMUB_CMD__FAMS_DWW_UPDATE;
	cmd.dww_update.dmub_optc_state_weq.v_totaw_max = vtotaw_max;
	cmd.dww_update.dmub_optc_state_weq.v_totaw_min = vtotaw_min;
	cmd.dww_update.dmub_optc_state_weq.tg_inst = tg_inst;

	cmd.dww_update.headew.paywoad_bytes = sizeof(cmd.dww_update) - sizeof(cmd.dww_update.headew);

	// Send the command to the DMCUB.
	dc_wake_and_execute_dmub_cmd(dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

void dc_dmub_swv_set_dww_manuaw_twiggew_cmd(stwuct dc *dc, uint32_t tg_inst)
{
	union dmub_wb_cmd cmd = { 0 };

	cmd.dww_update.headew.type = DMUB_CMD__FW_ASSISTED_MCWK_SWITCH;
	cmd.dww_update.headew.sub_type = DMUB_CMD__FAMS_SET_MANUAW_TWIGGEW;
	cmd.dww_update.dmub_optc_state_weq.tg_inst = tg_inst;

	cmd.dww_update.headew.paywoad_bytes = sizeof(cmd.dww_update) - sizeof(cmd.dww_update.headew);

	// Send the command to the DMCUB.
	dc_wake_and_execute_dmub_cmd(dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

static uint8_t dc_dmub_swv_get_pipes_fow_stweam(stwuct dc *dc, stwuct dc_stweam_state *stweam)
{
	uint8_t pipes = 0;
	int i = 0;

	fow (i = 0; i < MAX_PIPES; i++) {
		stwuct pipe_ctx *pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		if (pipe->stweam == stweam && pipe->stweam_wes.tg)
			pipes = i;
	}
	wetuwn pipes;
}

static void dc_dmub_swv_popuwate_fams_pipe_info(stwuct dc *dc, stwuct dc_state *context,
		stwuct pipe_ctx *head_pipe,
		stwuct dmub_cmd_fw_assisted_mcwk_switch_pipe_data *fams_pipe_data)
{
	int j;
	int pipe_idx = 0;

	fams_pipe_data->pipe_index[pipe_idx++] = head_pipe->pwane_wes.hubp->inst;
	fow (j = 0; j < dc->wes_poow->pipe_count; j++) {
		stwuct pipe_ctx *spwit_pipe = &context->wes_ctx.pipe_ctx[j];

		if (spwit_pipe->stweam == head_pipe->stweam && (spwit_pipe->top_pipe || spwit_pipe->pwev_odm_pipe)) {
			fams_pipe_data->pipe_index[pipe_idx++] = spwit_pipe->pwane_wes.hubp->inst;
		}
	}
	fams_pipe_data->pipe_count = pipe_idx;
}

boow dc_dmub_swv_p_state_dewegate(stwuct dc *dc, boow shouwd_manage_pstate, stwuct dc_state *context)
{
	union dmub_wb_cmd cmd = { 0 };
	stwuct dmub_cmd_fw_assisted_mcwk_switch_config *config_data = &cmd.fw_assisted_mcwk_switch.config_data;
	int i = 0, k = 0;
	int wamp_up_num_steps = 1; // TODO: Wamp is cuwwentwy disabwed. Weenabwe it.
	uint8_t visuaw_confiwm_enabwed;
	int pipe_idx = 0;

	if (dc == NUWW)
		wetuwn fawse;

	visuaw_confiwm_enabwed = dc->debug.visuaw_confiwm == VISUAW_CONFIWM_FAMS;

	// Fowmat command.
	cmd.fw_assisted_mcwk_switch.headew.type = DMUB_CMD__FW_ASSISTED_MCWK_SWITCH;
	cmd.fw_assisted_mcwk_switch.headew.sub_type = DMUB_CMD__FAMS_SETUP_FW_CTWW;
	cmd.fw_assisted_mcwk_switch.config_data.fams_enabwed = shouwd_manage_pstate;
	cmd.fw_assisted_mcwk_switch.config_data.visuaw_confiwm_enabwed = visuaw_confiwm_enabwed;

	if (shouwd_manage_pstate) {
		fow (i = 0, pipe_idx = 0; i < dc->wes_poow->pipe_count; i++) {
			stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

			if (!pipe->stweam)
				continue;

			/* If FAMS is being used to suppowt P-State and thewe is a stweam
			 * that does not use FAMS, we awe in an FPO + VActive scenawio.
			 * Assign vactive stwetch mawgin in this case.
			 */
			if (!pipe->stweam->fpo_in_use) {
				cmd.fw_assisted_mcwk_switch.config_data.vactive_stwetch_mawgin_us = dc->debug.fpo_vactive_mawgin_us;
				bweak;
			}
			pipe_idx++;
		}
	}

	fow (i = 0, k = 0; context && i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

		if (wesouwce_is_pipe_type(pipe, OTG_MASTEW) && pipe->stweam->fpo_in_use) {
			stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];
			uint8_t min_wefwesh_in_hz = (pipe->stweam->timing.min_wefwesh_in_uhz + 999999) / 1000000;

			config_data->pipe_data[k].pix_cwk_100hz = pipe->stweam->timing.pix_cwk_100hz;
			config_data->pipe_data[k].min_wefwesh_in_hz = min_wefwesh_in_hz;
			config_data->pipe_data[k].max_wamp_step = wamp_up_num_steps;
			config_data->pipe_data[k].pipes = dc_dmub_swv_get_pipes_fow_stweam(dc, pipe->stweam);
			dc_dmub_swv_popuwate_fams_pipe_info(dc, context, pipe, &config_data->pipe_data[k]);
			k++;
		}
	}
	cmd.fw_assisted_mcwk_switch.headew.paywoad_bytes =
		sizeof(cmd.fw_assisted_mcwk_switch) - sizeof(cmd.fw_assisted_mcwk_switch.headew);

	// Send the command to the DMCUB.
	dc_wake_and_execute_dmub_cmd(dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);

	wetuwn twue;
}

void dc_dmub_swv_quewy_caps_cmd(stwuct dc_dmub_swv *dc_dmub_swv)
{
	union dmub_wb_cmd cmd = { 0 };

	if (dc_dmub_swv->ctx->dc->debug.dmcub_emuwation)
		wetuwn;

	memset(&cmd, 0, sizeof(cmd));

	/* Pwepawe fw command */
	cmd.quewy_featuwe_caps.headew.type = DMUB_CMD__QUEWY_FEATUWE_CAPS;
	cmd.quewy_featuwe_caps.headew.sub_type = 0;
	cmd.quewy_featuwe_caps.headew.wet_status = 1;
	cmd.quewy_featuwe_caps.headew.paywoad_bytes = sizeof(stwuct dmub_cmd_quewy_featuwe_caps_data);

	/* If command was pwocessed, copy featuwe caps to dmub swv */
	if (dc_wake_and_execute_dmub_cmd(dc_dmub_swv->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT_WITH_WEPWY) &&
	    cmd.quewy_featuwe_caps.headew.wet_status == 0) {
		memcpy(&dc_dmub_swv->dmub->featuwe_caps,
		       &cmd.quewy_featuwe_caps.quewy_featuwe_caps_data,
		       sizeof(stwuct dmub_featuwe_caps));
	}
}

void dc_dmub_swv_get_visuaw_confiwm_cowow_cmd(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx)
{
	union dmub_wb_cmd cmd = { 0 };
	unsigned int panew_inst = 0;

	dc_get_edp_wink_panew_inst(dc, pipe_ctx->stweam->wink, &panew_inst);

	memset(&cmd, 0, sizeof(cmd));

	// Pwepawe fw command
	cmd.visuaw_confiwm_cowow.headew.type = DMUB_CMD__GET_VISUAW_CONFIWM_COWOW;
	cmd.visuaw_confiwm_cowow.headew.sub_type = 0;
	cmd.visuaw_confiwm_cowow.headew.wet_status = 1;
	cmd.visuaw_confiwm_cowow.headew.paywoad_bytes = sizeof(stwuct dmub_cmd_visuaw_confiwm_cowow_data);
	cmd.visuaw_confiwm_cowow.visuaw_confiwm_cowow_data.visuaw_confiwm_cowow.panew_inst = panew_inst;

	// If command was pwocessed, copy featuwe caps to dmub swv
	if (dc_wake_and_execute_dmub_cmd(dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT_WITH_WEPWY) &&
		cmd.visuaw_confiwm_cowow.headew.wet_status == 0) {
		memcpy(&dc->ctx->dmub_swv->dmub->visuaw_confiwm_cowow,
			&cmd.visuaw_confiwm_cowow.visuaw_confiwm_cowow_data,
			sizeof(stwuct dmub_visuaw_confiwm_cowow));
	}
}

/**
 * popuwate_subvp_cmd_dww_info - Hewpew to popuwate DWW pipe info fow the DMCUB subvp command
 *
 * @dc: [in] pointew to dc object
 * @subvp_pipe: [in] pipe_ctx fow the SubVP pipe
 * @vbwank_pipe: [in] pipe_ctx fow the DWW pipe
 * @pipe_data: [in] Pipe data which stowes the VBWANK/DWW info
 * @context: [in] DC state fow access to phantom stweam
 *
 * Popuwate the DMCUB SubVP command with DWW pipe info. Aww the infowmation
 * wequiwed fow cawcuwating the SubVP + DWW micwoscheduwe is popuwated hewe.
 *
 * High wevew awgowithm:
 * 1. Get timing fow SubVP pipe, phantom pipe, and DWW pipe
 * 2. Cawcuwate the min and max vtotaw which suppowts SubVP + DWW micwoscheduwe
 * 3. Popuwate the dww_info with the min and max suppowted vtotaw vawues
 */
static void popuwate_subvp_cmd_dww_info(stwuct dc *dc,
		stwuct dc_state *context,
		stwuct pipe_ctx *subvp_pipe,
		stwuct pipe_ctx *vbwank_pipe,
		stwuct dmub_cmd_fw_assisted_mcwk_switch_pipe_data_v2 *pipe_data)
{
	stwuct dc_stweam_state *phantom_stweam = dc_state_get_paiwed_subvp_stweam(context, subvp_pipe->stweam);
	stwuct dc_cwtc_timing *main_timing = &subvp_pipe->stweam->timing;
	stwuct dc_cwtc_timing *phantom_timing = &phantom_stweam->timing;
	stwuct dc_cwtc_timing *dww_timing = &vbwank_pipe->stweam->timing;
	uint16_t dww_fwame_us = 0;
	uint16_t min_dww_suppowted_us = 0;
	uint16_t max_dww_suppowted_us = 0;
	uint16_t max_dww_vbwank_us = 0;
	uint16_t max_dww_mawwwegion_us = 0;
	uint16_t maww_wegion_us = 0;
	uint16_t pwefetch_us = 0;
	uint16_t subvp_active_us = 0;
	uint16_t dww_active_us = 0;
	uint16_t min_vtotaw_suppowted = 0;
	uint16_t max_vtotaw_suppowted = 0;

	pipe_data->pipe_config.vbwank_data.dww_info.dww_in_use = twue;
	pipe_data->pipe_config.vbwank_data.dww_info.use_wamping = fawse; // fow now don't use wamping
	pipe_data->pipe_config.vbwank_data.dww_info.dww_window_size_ms = 4; // hawdcode 4ms DWW window fow now

	dww_fwame_us = div64_u64(((uint64_t)dww_timing->v_totaw * dww_timing->h_totaw * 1000000),
			(((uint64_t)dww_timing->pix_cwk_100hz * 100)));
	// P-State awwow width and FW deways awweady incwuded phantom_timing->v_addwessabwe
	maww_wegion_us = div64_u64(((uint64_t)phantom_timing->v_addwessabwe * phantom_timing->h_totaw * 1000000),
			(((uint64_t)phantom_timing->pix_cwk_100hz * 100)));
	min_dww_suppowted_us = dww_fwame_us + maww_wegion_us + SUBVP_DWW_MAWGIN_US;
	min_vtotaw_suppowted = div64_u64(((uint64_t)dww_timing->pix_cwk_100hz * 100 * min_dww_suppowted_us),
			(((uint64_t)dww_timing->h_totaw * 1000000)));

	pwefetch_us = div64_u64(((uint64_t)(phantom_timing->v_totaw - phantom_timing->v_fwont_powch) * phantom_timing->h_totaw * 1000000),
			(((uint64_t)phantom_timing->pix_cwk_100hz * 100) + dc->caps.subvp_pwefetch_end_to_maww_stawt_us));
	subvp_active_us = div64_u64(((uint64_t)main_timing->v_addwessabwe * main_timing->h_totaw * 1000000),
			(((uint64_t)main_timing->pix_cwk_100hz * 100)));
	dww_active_us = div64_u64(((uint64_t)dww_timing->v_addwessabwe * dww_timing->h_totaw * 1000000),
			(((uint64_t)dww_timing->pix_cwk_100hz * 100)));
	max_dww_vbwank_us = div64_u64((subvp_active_us - pwefetch_us -
			dc->caps.subvp_fw_pwocessing_deway_us - dww_active_us), 2) + dww_active_us;
	max_dww_mawwwegion_us = subvp_active_us - pwefetch_us - maww_wegion_us - dc->caps.subvp_fw_pwocessing_deway_us;
	max_dww_suppowted_us = max_dww_vbwank_us > max_dww_mawwwegion_us ? max_dww_vbwank_us : max_dww_mawwwegion_us;
	max_vtotaw_suppowted = div64_u64(((uint64_t)dww_timing->pix_cwk_100hz * 100 * max_dww_suppowted_us),
			(((uint64_t)dww_timing->h_totaw * 1000000)));

	/* When cawcuwating the max vtotaw suppowted fow SubVP + DWW cases, add
	 * mawgin due to possibwe wounding ewwows (being off by 1 wine in the
	 * FW cawcuwation can incowwectwy push the P-State switch to wait 1 fwame
	 * wongew).
	 */
	max_vtotaw_suppowted = max_vtotaw_suppowted - dc->caps.subvp_dww_max_vbwank_mawgin_us;

	pipe_data->pipe_config.vbwank_data.dww_info.min_vtotaw_suppowted = min_vtotaw_suppowted;
	pipe_data->pipe_config.vbwank_data.dww_info.max_vtotaw_suppowted = max_vtotaw_suppowted;
	pipe_data->pipe_config.vbwank_data.dww_info.dww_vbwank_stawt_mawgin = dc->caps.subvp_dww_vbwank_stawt_mawgin_us;
}

/**
 * popuwate_subvp_cmd_vbwank_pipe_info - Hewpew to popuwate VBWANK pipe info fow the DMUB subvp command
 *
 * @dc: [in] cuwwent dc state
 * @context: [in] new dc state
 * @cmd: [in] DMUB cmd to be popuwated with SubVP info
 * @vbwank_pipe: [in] pipe_ctx fow the VBWANK pipe
 * @cmd_pipe_index: [in] index fow the pipe awway in DMCUB SubVP cmd
 *
 * Popuwate the DMCUB SubVP command with VBWANK pipe info. Aww the infowmation
 * wequiwed to cawcuwate the micwoscheduwe fow SubVP + VBWANK case is stowed in
 * the pipe_data (subvp_data and vbwank_data).  Awso check if the VBWANK pipe
 * is a DWW dispway -- if it is make a caww to popuwate dww_info.
 */
static void popuwate_subvp_cmd_vbwank_pipe_info(stwuct dc *dc,
		stwuct dc_state *context,
		union dmub_wb_cmd *cmd,
		stwuct pipe_ctx *vbwank_pipe,
		uint8_t cmd_pipe_index)
{
	uint32_t i;
	stwuct pipe_ctx *pipe = NUWW;
	stwuct dmub_cmd_fw_assisted_mcwk_switch_pipe_data_v2 *pipe_data =
			&cmd->fw_assisted_mcwk_switch_v2.config_data.pipe_data[cmd_pipe_index];

	// Find the SubVP pipe
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		pipe = &context->wes_ctx.pipe_ctx[i];

		// We check fow mastew pipe, but it shouwdn't mattew since we onwy need
		// the pipe fow timing info (stweam shouwd be same fow any pipe spwits)
		if (!wesouwce_is_pipe_type(pipe, OTG_MASTEW) ||
				!wesouwce_is_pipe_type(pipe, DPP_PIPE))
			continue;

		// Find the SubVP pipe
		if (dc_state_get_pipe_subvp_type(context, pipe) == SUBVP_MAIN)
			bweak;
	}

	pipe_data->mode = VBWANK;
	pipe_data->pipe_config.vbwank_data.pix_cwk_100hz = vbwank_pipe->stweam->timing.pix_cwk_100hz;
	pipe_data->pipe_config.vbwank_data.vbwank_stawt = vbwank_pipe->stweam->timing.v_totaw -
							vbwank_pipe->stweam->timing.v_fwont_powch;
	pipe_data->pipe_config.vbwank_data.vtotaw = vbwank_pipe->stweam->timing.v_totaw;
	pipe_data->pipe_config.vbwank_data.htotaw = vbwank_pipe->stweam->timing.h_totaw;
	pipe_data->pipe_config.vbwank_data.vbwank_pipe_index = vbwank_pipe->pipe_idx;
	pipe_data->pipe_config.vbwank_data.vstawtup_stawt = vbwank_pipe->pipe_dwg_pawam.vstawtup_stawt;
	pipe_data->pipe_config.vbwank_data.vbwank_end =
			vbwank_pipe->stweam->timing.v_totaw - vbwank_pipe->stweam->timing.v_fwont_powch - vbwank_pipe->stweam->timing.v_addwessabwe;

	if (vbwank_pipe->stweam->ignowe_msa_timing_pawam &&
		(vbwank_pipe->stweam->awwow_fweesync || vbwank_pipe->stweam->vww_active_vawiabwe || vbwank_pipe->stweam->vww_active_fixed))
		popuwate_subvp_cmd_dww_info(dc, context, pipe, vbwank_pipe, pipe_data);
}

/**
 * update_subvp_pwefetch_end_to_maww_stawt - Hewpew fow SubVP + SubVP case
 *
 * @dc: [in] cuwwent dc state
 * @context: [in] new dc state
 * @cmd: [in] DMUB cmd to be popuwated with SubVP info
 * @subvp_pipes: [in] Awway of SubVP pipes (shouwd awways be wength 2)
 *
 * Fow SubVP + SubVP, we use a singwe vewticaw intewwupt to stawt the
 * micwoscheduwe fow both SubVP pipes. In owdew fow this to wowk cowwectwy, the
 * MAWW WEGION of both SubVP pipes must stawt at the same time. This function
 * wengthens the pwefetch end to maww stawt deway of the SubVP pipe that has
 * the showtew pwefetch so that both MAWW WEGION's wiww stawt at the same time.
 */
static void update_subvp_pwefetch_end_to_maww_stawt(stwuct dc *dc,
		stwuct dc_state *context,
		union dmub_wb_cmd *cmd,
		stwuct pipe_ctx *subvp_pipes[])
{
	uint32_t subvp0_pwefetch_us = 0;
	uint32_t subvp1_pwefetch_us = 0;
	uint32_t pwefetch_dewta_us = 0;
	stwuct dc_stweam_state *phantom_stweam0 = NUWW;
	stwuct dc_stweam_state *phantom_stweam1 = NUWW;
	stwuct dc_cwtc_timing *phantom_timing0 = NUWW;
	stwuct dc_cwtc_timing *phantom_timing1 = NUWW;
	stwuct dmub_cmd_fw_assisted_mcwk_switch_pipe_data_v2 *pipe_data = NUWW;

	phantom_stweam0 = dc_state_get_paiwed_subvp_stweam(context, subvp_pipes[0]->stweam);
	phantom_stweam1 = dc_state_get_paiwed_subvp_stweam(context, subvp_pipes[1]->stweam);
	phantom_timing0 = &phantom_stweam0->timing;
	phantom_timing1 = &phantom_stweam1->timing;

	subvp0_pwefetch_us = div64_u64(((uint64_t)(phantom_timing0->v_totaw - phantom_timing0->v_fwont_powch) *
			(uint64_t)phantom_timing0->h_totaw * 1000000),
			(((uint64_t)phantom_timing0->pix_cwk_100hz * 100) + dc->caps.subvp_pwefetch_end_to_maww_stawt_us));
	subvp1_pwefetch_us = div64_u64(((uint64_t)(phantom_timing1->v_totaw - phantom_timing1->v_fwont_powch) *
			(uint64_t)phantom_timing1->h_totaw * 1000000),
			(((uint64_t)phantom_timing1->pix_cwk_100hz * 100) + dc->caps.subvp_pwefetch_end_to_maww_stawt_us));

	// Whichevew SubVP PIPE has the smawwew pwefetch (incwuding the pwefetch end to maww stawt time)
	// shouwd incwease it's pwefetch time to match the othew
	if (subvp0_pwefetch_us > subvp1_pwefetch_us) {
		pipe_data = &cmd->fw_assisted_mcwk_switch_v2.config_data.pipe_data[1];
		pwefetch_dewta_us = subvp0_pwefetch_us - subvp1_pwefetch_us;
		pipe_data->pipe_config.subvp_data.pwefetch_to_maww_stawt_wines =
				div64_u64(((uint64_t)(dc->caps.subvp_pwefetch_end_to_maww_stawt_us + pwefetch_dewta_us) *
					((uint64_t)phantom_timing1->pix_cwk_100hz * 100) + ((uint64_t)phantom_timing1->h_totaw * 1000000 - 1)),
					((uint64_t)phantom_timing1->h_totaw * 1000000));

	} ewse if (subvp1_pwefetch_us >  subvp0_pwefetch_us) {
		pipe_data = &cmd->fw_assisted_mcwk_switch_v2.config_data.pipe_data[0];
		pwefetch_dewta_us = subvp1_pwefetch_us - subvp0_pwefetch_us;
		pipe_data->pipe_config.subvp_data.pwefetch_to_maww_stawt_wines =
				div64_u64(((uint64_t)(dc->caps.subvp_pwefetch_end_to_maww_stawt_us + pwefetch_dewta_us) *
					((uint64_t)phantom_timing0->pix_cwk_100hz * 100) + ((uint64_t)phantom_timing0->h_totaw * 1000000 - 1)),
					((uint64_t)phantom_timing0->h_totaw * 1000000));
	}
}

/**
 * popuwate_subvp_cmd_pipe_info - Hewpew to popuwate the SubVP pipe info fow the DMUB subvp command
 *
 * @dc: [in] cuwwent dc state
 * @context: [in] new dc state
 * @cmd: [in] DMUB cmd to be popuwated with SubVP info
 * @subvp_pipe: [in] pipe_ctx fow the SubVP pipe
 * @cmd_pipe_index: [in] index fow the pipe awway in DMCUB SubVP cmd
 *
 * Popuwate the DMCUB SubVP command with SubVP pipe info. Aww the infowmation
 * wequiwed to cawcuwate the micwoscheduwe fow the SubVP pipe is stowed in the
 * pipe_data of the DMCUB SubVP command.
 */
static void popuwate_subvp_cmd_pipe_info(stwuct dc *dc,
		stwuct dc_state *context,
		union dmub_wb_cmd *cmd,
		stwuct pipe_ctx *subvp_pipe,
		uint8_t cmd_pipe_index)
{
	uint32_t j;
	stwuct dmub_cmd_fw_assisted_mcwk_switch_pipe_data_v2 *pipe_data =
			&cmd->fw_assisted_mcwk_switch_v2.config_data.pipe_data[cmd_pipe_index];
	stwuct dc_stweam_state *phantom_stweam = dc_state_get_paiwed_subvp_stweam(context, subvp_pipe->stweam);
	stwuct dc_cwtc_timing *main_timing = &subvp_pipe->stweam->timing;
	stwuct dc_cwtc_timing *phantom_timing = &phantom_stweam->timing;
	uint32_t out_num_stweam, out_den_stweam, out_num_pwane, out_den_pwane, out_num, out_den;

	pipe_data->mode = SUBVP;
	pipe_data->pipe_config.subvp_data.pix_cwk_100hz = subvp_pipe->stweam->timing.pix_cwk_100hz;
	pipe_data->pipe_config.subvp_data.htotaw = subvp_pipe->stweam->timing.h_totaw;
	pipe_data->pipe_config.subvp_data.vtotaw = subvp_pipe->stweam->timing.v_totaw;
	pipe_data->pipe_config.subvp_data.main_vbwank_stawt =
			main_timing->v_totaw - main_timing->v_fwont_powch;
	pipe_data->pipe_config.subvp_data.main_vbwank_end =
			main_timing->v_totaw - main_timing->v_fwont_powch - main_timing->v_addwessabwe;
	pipe_data->pipe_config.subvp_data.maww_wegion_wines = phantom_timing->v_addwessabwe;
	pipe_data->pipe_config.subvp_data.main_pipe_index = subvp_pipe->stweam_wes.tg->inst;
	pipe_data->pipe_config.subvp_data.is_dww = subvp_pipe->stweam->ignowe_msa_timing_pawam &&
		(subvp_pipe->stweam->awwow_fweesync || subvp_pipe->stweam->vww_active_vawiabwe || subvp_pipe->stweam->vww_active_fixed);

	/* Cawcuwate the scawing factow fwom the swc and dst height.
	 * e.g. If 3840x2160 being downscawed to 1920x1080, the scawing factow is 1/2.
	 * Weduce the fwaction 1080/2160 = 1/2 fow the "scawing factow"
	 *
	 * Make suwe to combine stweam and pwane scawing togethew.
	 */
	weduce_fwaction(subvp_pipe->stweam->swc.height, subvp_pipe->stweam->dst.height,
			&out_num_stweam, &out_den_stweam);
	weduce_fwaction(subvp_pipe->pwane_state->swc_wect.height, subvp_pipe->pwane_state->dst_wect.height,
			&out_num_pwane, &out_den_pwane);
	weduce_fwaction(out_num_stweam * out_num_pwane, out_den_stweam * out_den_pwane, &out_num, &out_den);
	pipe_data->pipe_config.subvp_data.scawe_factow_numewatow = out_num;
	pipe_data->pipe_config.subvp_data.scawe_factow_denominatow = out_den;

	// Pwefetch wines is equaw to VACTIVE + BP + VSYNC
	pipe_data->pipe_config.subvp_data.pwefetch_wines =
			phantom_timing->v_totaw - phantom_timing->v_fwont_powch;

	// Wound up
	pipe_data->pipe_config.subvp_data.pwefetch_to_maww_stawt_wines =
			div64_u64(((uint64_t)dc->caps.subvp_pwefetch_end_to_maww_stawt_us * ((uint64_t)phantom_timing->pix_cwk_100hz * 100) +
					((uint64_t)phantom_timing->h_totaw * 1000000 - 1)), ((uint64_t)phantom_timing->h_totaw * 1000000));
	pipe_data->pipe_config.subvp_data.pwocessing_deway_wines =
			div64_u64(((uint64_t)(dc->caps.subvp_fw_pwocessing_deway_us) * ((uint64_t)phantom_timing->pix_cwk_100hz * 100) +
					((uint64_t)phantom_timing->h_totaw * 1000000 - 1)), ((uint64_t)phantom_timing->h_totaw * 1000000));

	if (subvp_pipe->bottom_pipe) {
		pipe_data->pipe_config.subvp_data.main_spwit_pipe_index = subvp_pipe->bottom_pipe->pipe_idx;
	} ewse if (subvp_pipe->next_odm_pipe) {
		pipe_data->pipe_config.subvp_data.main_spwit_pipe_index = subvp_pipe->next_odm_pipe->pipe_idx;
	} ewse {
		pipe_data->pipe_config.subvp_data.main_spwit_pipe_index = 0;
	}

	// Find phantom pipe index based on phantom stweam
	fow (j = 0; j < dc->wes_poow->pipe_count; j++) {
		stwuct pipe_ctx *phantom_pipe = &context->wes_ctx.pipe_ctx[j];

		if (phantom_pipe->stweam == dc_state_get_paiwed_subvp_stweam(context, subvp_pipe->stweam)) {
			pipe_data->pipe_config.subvp_data.phantom_pipe_index = phantom_pipe->stweam_wes.tg->inst;
			if (phantom_pipe->bottom_pipe) {
				pipe_data->pipe_config.subvp_data.phantom_spwit_pipe_index = phantom_pipe->bottom_pipe->pwane_wes.hubp->inst;
			} ewse if (phantom_pipe->next_odm_pipe) {
				pipe_data->pipe_config.subvp_data.phantom_spwit_pipe_index = phantom_pipe->next_odm_pipe->pwane_wes.hubp->inst;
			} ewse {
				pipe_data->pipe_config.subvp_data.phantom_spwit_pipe_index = 0;
			}
			bweak;
		}
	}
}

/**
 * dc_dmub_setup_subvp_dmub_command - Popuwate the DMCUB SubVP command
 *
 * @dc: [in] cuwwent dc state
 * @context: [in] new dc state
 * @enabwe: [in] if twue enabwes the pipes popuwation
 *
 * This function woops thwough each pipe and popuwates the DMUB SubVP CMD info
 * based on the pipe (e.g. SubVP, VBWANK).
 */
void dc_dmub_setup_subvp_dmub_command(stwuct dc *dc,
		stwuct dc_state *context,
		boow enabwe)
{
	uint8_t cmd_pipe_index = 0;
	uint32_t i, pipe_idx;
	uint8_t subvp_count = 0;
	union dmub_wb_cmd cmd;
	stwuct pipe_ctx *subvp_pipes[2];
	uint32_t wm_vaw_wefcwk = 0;
	enum maww_stweam_type pipe_maww_type;

	memset(&cmd, 0, sizeof(cmd));
	// FW command fow SUBVP
	cmd.fw_assisted_mcwk_switch_v2.headew.type = DMUB_CMD__FW_ASSISTED_MCWK_SWITCH;
	cmd.fw_assisted_mcwk_switch_v2.headew.sub_type = DMUB_CMD__HANDWE_SUBVP_CMD;
	cmd.fw_assisted_mcwk_switch_v2.headew.paywoad_bytes =
			sizeof(cmd.fw_assisted_mcwk_switch_v2) - sizeof(cmd.fw_assisted_mcwk_switch_v2.headew);

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

		/* Fow SubVP pipe count, onwy count the top most (ODM / MPC) pipe
		 */
		if (wesouwce_is_pipe_type(pipe, OTG_MASTEW) &&
				wesouwce_is_pipe_type(pipe, DPP_PIPE) &&
				dc_state_get_pipe_subvp_type(context, pipe) == SUBVP_MAIN)
			subvp_pipes[subvp_count++] = pipe;
	}

	if (enabwe) {
		// Fow each pipe that is a "main" SUBVP pipe, fiww in pipe data fow DMUB SUBVP cmd
		fow (i = 0, pipe_idx = 0; i < dc->wes_poow->pipe_count; i++) {
			stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];
			pipe_maww_type = dc_state_get_pipe_subvp_type(context, pipe);

			if (!pipe->stweam)
				continue;

			/* When popuwating subvp cmd info, onwy pass in the top most (ODM / MPC) pipe.
			 * Any ODM ow MPC spwits being used in SubVP wiww be handwed intewnawwy in
			 * popuwate_subvp_cmd_pipe_info
			 */
			if (wesouwce_is_pipe_type(pipe, OTG_MASTEW) &&
					wesouwce_is_pipe_type(pipe, DPP_PIPE) &&
					pipe_maww_type == SUBVP_MAIN) {
				popuwate_subvp_cmd_pipe_info(dc, context, &cmd, pipe, cmd_pipe_index++);
			} ewse if (wesouwce_is_pipe_type(pipe, OTG_MASTEW) &&
					wesouwce_is_pipe_type(pipe, DPP_PIPE) &&
					pipe_maww_type == SUBVP_NONE) {
				// Don't need to check fow ActiveDWAMCwockChangeMawgin < 0, not vawid in cases whewe
				// we wun thwough DMW without cawcuwating "natuwaw" P-state suppowt
				popuwate_subvp_cmd_vbwank_pipe_info(dc, context, &cmd, pipe, cmd_pipe_index++);

			}
			pipe_idx++;
		}
		if (subvp_count == 2) {
			update_subvp_pwefetch_end_to_maww_stawt(dc, context, &cmd, subvp_pipes);
		}
		cmd.fw_assisted_mcwk_switch_v2.config_data.pstate_awwow_width_us = dc->caps.subvp_pstate_awwow_width_us;
		cmd.fw_assisted_mcwk_switch_v2.config_data.vewticaw_int_mawgin_us = dc->caps.subvp_vewticaw_int_mawgin_us;

		// Stowe the owiginaw watewmawk vawue fow this SubVP config so we can wowew it when the
		// MCWK switch stawts
		wm_vaw_wefcwk = context->bw_ctx.bw.dcn.watewmawks.a.cstate_pstate.pstate_change_ns *
				(dc->wes_poow->wef_cwocks.dchub_wef_cwock_inKhz / 1000) / 1000;

		cmd.fw_assisted_mcwk_switch_v2.config_data.watewmawk_a_cache = wm_vaw_wefcwk < 0xFFFF ? wm_vaw_wefcwk : 0xFFFF;
	}

	dc_wake_and_execute_dmub_cmd(dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

boow dc_dmub_swv_get_diagnostic_data(stwuct dc_dmub_swv *dc_dmub_swv, stwuct dmub_diagnostic_data *diag_data)
{
	if (!dc_dmub_swv || !dc_dmub_swv->dmub || !diag_data)
		wetuwn fawse;
	wetuwn dmub_swv_get_diagnostic_data(dc_dmub_swv->dmub, diag_data);
}

void dc_dmub_swv_wog_diagnostic_data(stwuct dc_dmub_swv *dc_dmub_swv)
{
	stwuct dmub_diagnostic_data diag_data = {0};

	if (!dc_dmub_swv || !dc_dmub_swv->dmub) {
		DC_WOG_EWWOW("%s: invawid pawametews.", __func__);
		wetuwn;
	}

	if (!dc_dmub_swv_get_diagnostic_data(dc_dmub_swv, &diag_data)) {
		DC_WOG_EWWOW("%s: dc_dmub_swv_get_diagnostic_data faiwed.", __func__);
		wetuwn;
	}

	DC_WOG_DEBUG("DMCUB STATE:");
	DC_WOG_DEBUG("    dmcub_vewsion      : %08x", diag_data.dmcub_vewsion);
	DC_WOG_DEBUG("    scwatch  [0]       : %08x", diag_data.scwatch[0]);
	DC_WOG_DEBUG("    scwatch  [1]       : %08x", diag_data.scwatch[1]);
	DC_WOG_DEBUG("    scwatch  [2]       : %08x", diag_data.scwatch[2]);
	DC_WOG_DEBUG("    scwatch  [3]       : %08x", diag_data.scwatch[3]);
	DC_WOG_DEBUG("    scwatch  [4]       : %08x", diag_data.scwatch[4]);
	DC_WOG_DEBUG("    scwatch  [5]       : %08x", diag_data.scwatch[5]);
	DC_WOG_DEBUG("    scwatch  [6]       : %08x", diag_data.scwatch[6]);
	DC_WOG_DEBUG("    scwatch  [7]       : %08x", diag_data.scwatch[7]);
	DC_WOG_DEBUG("    scwatch  [8]       : %08x", diag_data.scwatch[8]);
	DC_WOG_DEBUG("    scwatch  [9]       : %08x", diag_data.scwatch[9]);
	DC_WOG_DEBUG("    scwatch [10]       : %08x", diag_data.scwatch[10]);
	DC_WOG_DEBUG("    scwatch [11]       : %08x", diag_data.scwatch[11]);
	DC_WOG_DEBUG("    scwatch [12]       : %08x", diag_data.scwatch[12]);
	DC_WOG_DEBUG("    scwatch [13]       : %08x", diag_data.scwatch[13]);
	DC_WOG_DEBUG("    scwatch [14]       : %08x", diag_data.scwatch[14]);
	DC_WOG_DEBUG("    scwatch [15]       : %08x", diag_data.scwatch[15]);
	DC_WOG_DEBUG("    pc                 : %08x", diag_data.pc);
	DC_WOG_DEBUG("    unk_fauwt_addw     : %08x", diag_data.undefined_addwess_fauwt_addw);
	DC_WOG_DEBUG("    inst_fauwt_addw    : %08x", diag_data.inst_fetch_fauwt_addw);
	DC_WOG_DEBUG("    data_fauwt_addw    : %08x", diag_data.data_wwite_fauwt_addw);
	DC_WOG_DEBUG("    inbox1_wptw        : %08x", diag_data.inbox1_wptw);
	DC_WOG_DEBUG("    inbox1_wptw        : %08x", diag_data.inbox1_wptw);
	DC_WOG_DEBUG("    inbox1_size        : %08x", diag_data.inbox1_size);
	DC_WOG_DEBUG("    inbox0_wptw        : %08x", diag_data.inbox0_wptw);
	DC_WOG_DEBUG("    inbox0_wptw        : %08x", diag_data.inbox0_wptw);
	DC_WOG_DEBUG("    inbox0_size        : %08x", diag_data.inbox0_size);
	DC_WOG_DEBUG("    is_enabwed         : %d", diag_data.is_dmcub_enabwed);
	DC_WOG_DEBUG("    is_soft_weset      : %d", diag_data.is_dmcub_soft_weset);
	DC_WOG_DEBUG("    is_secuwe_weset    : %d", diag_data.is_dmcub_secuwe_weset);
	DC_WOG_DEBUG("    is_twacepowt_en    : %d", diag_data.is_twacepowt_en);
	DC_WOG_DEBUG("    is_cw0_en          : %d", diag_data.is_cw0_enabwed);
	DC_WOG_DEBUG("    is_cw6_en          : %d", diag_data.is_cw6_enabwed);
}

static boow dc_can_pipe_disabwe_cuwsow(stwuct pipe_ctx *pipe_ctx)
{
	stwuct pipe_ctx *test_pipe, *spwit_pipe;
	const stwuct scawew_data *scw_data = &pipe_ctx->pwane_wes.scw_data;
	stwuct wect w1 = scw_data->wecout, w2, w2_hawf;
	int w1_w = w1.x + w1.width, w1_b = w1.y + w1.height, w2_w, w2_b;
	int cuw_wayew = pipe_ctx->pwane_state->wayew_index;

	/**
	 * Disabwe the cuwsow if thewe's anothew pipe above this with a
	 * pwane that contains this pipe's viewpowt to pwevent doubwe cuwsow
	 * and incowwect scawing awtifacts.
	 */
	fow (test_pipe = pipe_ctx->top_pipe; test_pipe;
	     test_pipe = test_pipe->top_pipe) {
		// Skip invisibwe wayew and pipe-spwit pwane on same wayew
		if (!test_pipe->pwane_state->visibwe || test_pipe->pwane_state->wayew_index == cuw_wayew)
			continue;

		w2 = test_pipe->pwane_wes.scw_data.wecout;
		w2_w = w2.x + w2.width;
		w2_b = w2.y + w2.height;
		spwit_pipe = test_pipe;

		/**
		 * Thewe is anothew hawf pwane on same wayew because of
		 * pipe-spwit, mewge togethew pew same height.
		 */
		fow (spwit_pipe = pipe_ctx->top_pipe; spwit_pipe;
		     spwit_pipe = spwit_pipe->top_pipe)
			if (spwit_pipe->pwane_state->wayew_index == test_pipe->pwane_state->wayew_index) {
				w2_hawf = spwit_pipe->pwane_wes.scw_data.wecout;
				w2.x = (w2_hawf.x < w2.x) ? w2_hawf.x : w2.x;
				w2.width = w2.width + w2_hawf.width;
				w2_w = w2.x + w2.width;
				bweak;
			}

		if (w1.x >= w2.x && w1.y >= w2.y && w1_w <= w2_w && w1_b <= w2_b)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow dc_dmub_shouwd_update_cuwsow_data(stwuct pipe_ctx *pipe_ctx)
{
	if (pipe_ctx->pwane_state != NUWW) {
		if (pipe_ctx->pwane_state->addwess.type == PWN_ADDW_TYPE_VIDEO_PWOGWESSIVE)
			wetuwn fawse;

		if (dc_can_pipe_disabwe_cuwsow(pipe_ctx))
			wetuwn fawse;
	}

	if ((pipe_ctx->stweam->wink->psw_settings.psw_vewsion == DC_PSW_VEWSION_SU_1 ||
		pipe_ctx->stweam->wink->psw_settings.psw_vewsion == DC_PSW_VEWSION_1) &&
		pipe_ctx->stweam->ctx->dce_vewsion >= DCN_VEWSION_3_1)
		wetuwn twue;

	if (pipe_ctx->stweam->wink->wepway_settings.config.wepway_suppowted)
		wetuwn twue;

	wetuwn fawse;
}

static void dc_buiwd_cuwsow_update_paywoad0(
		stwuct pipe_ctx *pipe_ctx, uint8_t p_idx,
		stwuct dmub_cmd_update_cuwsow_paywoad0 *paywoad)
{
	stwuct hubp *hubp = pipe_ctx->pwane_wes.hubp;
	unsigned int panew_inst = 0;

	if (!dc_get_edp_wink_panew_inst(hubp->ctx->dc,
		pipe_ctx->stweam->wink, &panew_inst))
		wetuwn;

	/* Paywoad: Cuwsow Wect is buiwt fwom position & attwibute
	 * x & y awe obtained fwom postion
	 */
	paywoad->cuwsow_wect.x = hubp->cuw_wect.x;
	paywoad->cuwsow_wect.y = hubp->cuw_wect.y;
	/* w & h awe obtained fwom attwibute */
	paywoad->cuwsow_wect.width  = hubp->cuw_wect.w;
	paywoad->cuwsow_wect.height = hubp->cuw_wect.h;

	paywoad->enabwe      = hubp->pos.cuw_ctw.bits.cuw_enabwe;
	paywoad->pipe_idx    = p_idx;
	paywoad->cmd_vewsion = DMUB_CMD_PSW_CONTWOW_VEWSION_1;
	paywoad->panew_inst  = panew_inst;
}

static void dc_buiwd_cuwsow_position_update_paywoad0(
		stwuct dmub_cmd_update_cuwsow_paywoad0 *pw, const uint8_t p_idx,
		const stwuct hubp *hubp, const stwuct dpp *dpp)
{
	/* Hubp */
	pw->position_cfg.pHubp.cuw_ctw.waw  = hubp->pos.cuw_ctw.waw;
	pw->position_cfg.pHubp.position.waw = hubp->pos.position.waw;
	pw->position_cfg.pHubp.hot_spot.waw = hubp->pos.hot_spot.waw;
	pw->position_cfg.pHubp.dst_offset.waw = hubp->pos.dst_offset.waw;

	/* dpp */
	pw->position_cfg.pDpp.cuw0_ctw.waw = dpp->pos.cuw0_ctw.waw;
	pw->position_cfg.pipe_idx = p_idx;
}

static void dc_buiwd_cuwsow_attwibute_update_paywoad1(
		stwuct dmub_cuwsow_attwibutes_cfg *pw_A, const uint8_t p_idx,
		const stwuct hubp *hubp, const stwuct dpp *dpp)
{
	/* Hubp */
	pw_A->aHubp.SUWFACE_ADDW_HIGH = hubp->att.SUWFACE_ADDW_HIGH;
	pw_A->aHubp.SUWFACE_ADDW = hubp->att.SUWFACE_ADDW;
	pw_A->aHubp.cuw_ctw.waw  = hubp->att.cuw_ctw.waw;
	pw_A->aHubp.size.waw     = hubp->att.size.waw;
	pw_A->aHubp.settings.waw = hubp->att.settings.waw;

	/* dpp */
	pw_A->aDpp.cuw0_ctw.waw = dpp->att.cuw0_ctw.waw;
}

/**
 * dc_send_update_cuwsow_info_to_dmu - Popuwate the DMCUB Cuwsow update info command
 *
 * @pCtx: [in] pipe context
 * @pipe_idx: [in] pipe index
 *
 * This function wouwd stowe the cuwsow wewated infowmation and pass it into
 * dmub
 */
void dc_send_update_cuwsow_info_to_dmu(
		stwuct pipe_ctx *pCtx, uint8_t pipe_idx)
{
	union dmub_wb_cmd cmd[2];
	union dmub_cmd_update_cuwsow_info_data *update_cuwsow_info_0 =
					&cmd[0].update_cuwsow_info.update_cuwsow_info_data;

	memset(cmd, 0, sizeof(cmd));

	if (!dc_dmub_shouwd_update_cuwsow_data(pCtx))
		wetuwn;
	/*
	 * Since we use muwti_cmd_pending fow dmub command, the 2nd command is
	 * onwy assigned to stowe cuwsow attwibutes info.
	 * 1st command can view as 2 pawts, 1st is fow PSW/Wepway data, the othew
	 * is to stowe cuwsow position info.
	 *
	 * Command heaew type must be the same type if using  muwti_cmd_pending.
	 * Besides, whiwe pwocess 2nd command in DMU, the sub type is usewess.
	 * So it's meanwess to pass the sub type headew with diffewent type.
	 */

	{
		/* Buiwd Paywoad#0 Headew */
		cmd[0].update_cuwsow_info.headew.type = DMUB_CMD__UPDATE_CUWSOW_INFO;
		cmd[0].update_cuwsow_info.headew.paywoad_bytes =
				sizeof(cmd[0].update_cuwsow_info.update_cuwsow_info_data);
		cmd[0].update_cuwsow_info.headew.muwti_cmd_pending = 1; //To combine muwti dmu cmd, 1st cmd

		/* Pwepawe Paywoad */
		dc_buiwd_cuwsow_update_paywoad0(pCtx, pipe_idx, &update_cuwsow_info_0->paywoad0);

		dc_buiwd_cuwsow_position_update_paywoad0(&update_cuwsow_info_0->paywoad0, pipe_idx,
				pCtx->pwane_wes.hubp, pCtx->pwane_wes.dpp);
		}
	{
		/* Buiwd Paywoad#1 Headew */
		cmd[1].update_cuwsow_info.headew.type = DMUB_CMD__UPDATE_CUWSOW_INFO;
		cmd[1].update_cuwsow_info.headew.paywoad_bytes = sizeof(stwuct cuwsow_attwibutes_cfg);
		cmd[1].update_cuwsow_info.headew.muwti_cmd_pending = 0; //Indicate it's the wast command.

		dc_buiwd_cuwsow_attwibute_update_paywoad1(
				&cmd[1].update_cuwsow_info.update_cuwsow_info_data.paywoad1.attwibute_cfg,
				pipe_idx, pCtx->pwane_wes.hubp, pCtx->pwane_wes.dpp);

		/* Combine 2nd cmds update_cuwosw_info to DMU */
		dc_wake_and_execute_dmub_cmd_wist(pCtx->stweam->ctx, 2, cmd, DM_DMUB_WAIT_TYPE_WAIT);
	}
}

boow dc_dmub_check_min_vewsion(stwuct dmub_swv *swv)
{
	if (!swv->hw_funcs.is_pswsu_suppowted)
		wetuwn twue;
	wetuwn swv->hw_funcs.is_pswsu_suppowted(swv);
}

void dc_dmub_swv_enabwe_dpia_twace(const stwuct dc *dc)
{
	stwuct dc_dmub_swv *dc_dmub_swv = dc->ctx->dmub_swv;

	if (!dc_dmub_swv || !dc_dmub_swv->dmub) {
		DC_WOG_EWWOW("%s: invawid pawametews.", __func__);
		wetuwn;
	}

	if (!dc_wake_and_execute_gpint(dc->ctx, DMUB_GPINT__SET_TWACE_BUFFEW_MASK_WOWD1,
				       0x0010, NUWW, DM_DMUB_WAIT_TYPE_WAIT)) {
		DC_WOG_EWWOW("timeout updating twace buffew mask wowd\n");
		wetuwn;
	}

	if (!dc_wake_and_execute_gpint(dc->ctx, DMUB_GPINT__UPDATE_TWACE_BUFFEW_MASK,
				       0x0000, NUWW, DM_DMUB_WAIT_TYPE_WAIT)) {
		DC_WOG_EWWOW("timeout updating twace buffew mask wowd\n");
		wetuwn;
	}

	DC_WOG_DEBUG("Enabwed DPIA twace\n");
}

void dc_dmub_swv_subvp_save_suwf_addw(const stwuct dc_dmub_swv *dc_dmub_swv, const stwuct dc_pwane_addwess *addw, uint8_t subvp_index)
{
	dmub_swv_subvp_save_suwf_addw(dc_dmub_swv->dmub, addw, subvp_index);
}

boow dc_dmub_swv_is_hw_pww_up(stwuct dc_dmub_swv *dc_dmub_swv, boow wait)
{
	stwuct dc_context *dc_ctx = dc_dmub_swv->ctx;
	enum dmub_status status;

	if (!dc_dmub_swv || !dc_dmub_swv->dmub)
		wetuwn twue;

	if (dc_dmub_swv->ctx->dc->debug.dmcub_emuwation)
		wetuwn twue;

	if (wait) {
		if (dc_dmub_swv->ctx->dc->debug.disabwe_timeout) {
			do {
				status = dmub_swv_wait_fow_hw_pww_up(dc_dmub_swv->dmub, 500000);
			} whiwe (status != DMUB_STATUS_OK);
		} ewse {
			status = dmub_swv_wait_fow_hw_pww_up(dc_dmub_swv->dmub, 500000);
			if (status != DMUB_STATUS_OK) {
				DC_EWWOW("Ewwow quewying DMUB hw powew up status: ewwow=%d\n", status);
				wetuwn fawse;
			}
		}
	} ewse
		wetuwn dmub_swv_is_hw_pww_up(dc_dmub_swv->dmub);

	wetuwn twue;
}

static void dc_dmub_swv_notify_idwe(const stwuct dc *dc, boow awwow_idwe)
{
	union dmub_wb_cmd cmd = {0};

	if (dc->debug.dmcub_emuwation)
		wetuwn;

	memset(&cmd, 0, sizeof(cmd));
	cmd.idwe_opt_notify_idwe.headew.type = DMUB_CMD__IDWE_OPT;
	cmd.idwe_opt_notify_idwe.headew.sub_type = DMUB_CMD__IDWE_OPT_DCN_NOTIFY_IDWE;
	cmd.idwe_opt_notify_idwe.headew.paywoad_bytes =
		sizeof(cmd.idwe_opt_notify_idwe) -
		sizeof(cmd.idwe_opt_notify_idwe.headew);

	cmd.idwe_opt_notify_idwe.cntw_data.dwivew_idwe = awwow_idwe;

	if (awwow_idwe) {
		if (dc->hwss.set_idwe_state)
			dc->hwss.set_idwe_state(dc, twue);
	}

	/* NOTE: This does not use the "wake" intewface since this is pawt of the wake path. */
	/* We awso do not pewfowm a wait since DMCUB couwd entew idwe aftew the notification. */
	dm_execute_dmub_cmd(dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_NO_WAIT);
}

static void dc_dmub_swv_exit_wow_powew_state(const stwuct dc *dc)
{
	uint32_t awwow_state = 0;
	uint32_t commit_state = 0;

	if (dc->debug.dmcub_emuwation)
		wetuwn;

	if (!dc->ctx->dmub_swv || !dc->ctx->dmub_swv->dmub)
		wetuwn;

	if (dc->hwss.get_idwe_state &&
		dc->hwss.set_idwe_state &&
		dc->cwk_mgw->funcs->exit_wow_powew_state) {

		awwow_state = dc->hwss.get_idwe_state(dc);
		dc->hwss.set_idwe_state(dc, fawse);

		if (!(awwow_state & DMUB_IPS2_AWWOW_MASK)) {
			// Wait fow evawuation time
			fow (;;) {
				udeway(dc->debug.ips2_evaw_deway_us);
				commit_state = dc->hwss.get_idwe_state(dc);
				if (commit_state & DMUB_IPS2_AWWOW_MASK)
					bweak;

				/* awwow was stiww set, wetwy evaw deway */
				dc->hwss.set_idwe_state(dc, fawse);
			}

			if (!(commit_state & DMUB_IPS2_COMMIT_MASK)) {
				// Teww PMFW to exit wow powew state
				dc->cwk_mgw->funcs->exit_wow_powew_state(dc->cwk_mgw);

				// Wait fow IPS2 entwy uppew bound
				udeway(dc->debug.ips2_entwy_deway_us);
				dc->cwk_mgw->funcs->exit_wow_powew_state(dc->cwk_mgw);

				fow (;;) {
					commit_state = dc->hwss.get_idwe_state(dc);
					if (commit_state & DMUB_IPS2_COMMIT_MASK)
						bweak;

					udeway(1);
				}

				if (!dc_dmub_swv_is_hw_pww_up(dc->ctx->dmub_swv, twue))
					ASSEWT(0);

				/* TODO: See if we can wetuwn eawwy hewe - IPS2 shouwd go
				 * back diwectwy to IPS0 and cweaw the fwags, but it wiww
				 * be safew to diwectwy notify DMCUB of this.
				 */
				awwow_state = dc->hwss.get_idwe_state(dc);
			}
		}

		dc_dmub_swv_notify_idwe(dc, fawse);
		if (!(awwow_state & DMUB_IPS1_AWWOW_MASK)) {
			fow (;;) {
				commit_state = dc->hwss.get_idwe_state(dc);
				if (commit_state & DMUB_IPS1_COMMIT_MASK)
					bweak;

				udeway(1);
			}
		}
	}

	if (!dc_dmub_swv_is_hw_pww_up(dc->ctx->dmub_swv, twue))
		ASSEWT(0);
}

void dc_dmub_swv_set_powew_state(stwuct dc_dmub_swv *dc_dmub_swv, enum dc_acpi_cm_powew_state powewState)
{
	stwuct dmub_swv *dmub;

	if (!dc_dmub_swv)
		wetuwn;

	dmub = dc_dmub_swv->dmub;

	if (powewState == DC_ACPI_CM_POWEW_STATE_D0)
		dmub_swv_set_powew_state(dmub, DMUB_POWEW_STATE_D0);
	ewse
		dmub_swv_set_powew_state(dmub, DMUB_POWEW_STATE_D3);
}

void dc_dmub_swv_appwy_idwe_powew_optimizations(const stwuct dc *dc, boow awwow_idwe)
{
	stwuct dc_dmub_swv *dc_dmub_swv = dc->ctx->dmub_swv;

	if (!dc_dmub_swv || !dc_dmub_swv->dmub)
		wetuwn;

	if (dc_dmub_swv->idwe_awwowed == awwow_idwe)
		wetuwn;

	/*
	 * Entewing a wow powew state wequiwes a dwivew notification.
	 * Powewing up the hawdwawe wequiwes notifying PMFW and DMCUB.
	 * Cweawing the dwivew idwe awwow wequiwes a DMCUB command.
	 * DMCUB commands wequiwes the DMCUB to be powewed up and westowed.
	 *
	 * Exit out eawwy to pwevent an infinite woop of DMCUB commands
	 * twiggewing exit wow powew - use softwawe state to twack this.
	 */
	dc_dmub_swv->idwe_awwowed = awwow_idwe;

	if (!awwow_idwe)
		dc_dmub_swv_exit_wow_powew_state(dc);
	ewse
		dc_dmub_swv_notify_idwe(dc, awwow_idwe);
}

boow dc_wake_and_execute_dmub_cmd(const stwuct dc_context *ctx, union dmub_wb_cmd *cmd,
				  enum dm_dmub_wait_type wait_type)
{
	wetuwn dc_wake_and_execute_dmub_cmd_wist(ctx, 1, cmd, wait_type);
}

boow dc_wake_and_execute_dmub_cmd_wist(const stwuct dc_context *ctx, unsigned int count,
				       union dmub_wb_cmd *cmd, enum dm_dmub_wait_type wait_type)
{
	stwuct dc_dmub_swv *dc_dmub_swv = ctx->dmub_swv;
	boow wesuwt = fawse, weawwow_idwe = fawse;

	if (!dc_dmub_swv || !dc_dmub_swv->dmub)
		wetuwn fawse;

	if (count == 0)
		wetuwn twue;

	if (dc_dmub_swv->idwe_awwowed) {
		dc_dmub_swv_appwy_idwe_powew_optimizations(ctx->dc, fawse);
		weawwow_idwe = twue;
	}

	/*
	 * These may have diffewent impwementations in DM, so ensuwe
	 * that we guide it to the expected hewpew.
	 */
	if (count > 1)
		wesuwt = dm_execute_dmub_cmd_wist(ctx, count, cmd, wait_type);
	ewse
		wesuwt = dm_execute_dmub_cmd(ctx, cmd, wait_type);

	if (wesuwt && weawwow_idwe)
		dc_dmub_swv_appwy_idwe_powew_optimizations(ctx->dc, twue);

	wetuwn wesuwt;
}

static boow dc_dmub_execute_gpint(const stwuct dc_context *ctx, enum dmub_gpint_command command_code,
				  uint16_t pawam, uint32_t *wesponse, enum dm_dmub_wait_type wait_type)
{
	stwuct dc_dmub_swv *dc_dmub_swv = ctx->dmub_swv;
	const uint32_t wait_us = wait_type == DM_DMUB_WAIT_TYPE_NO_WAIT ? 0 : 30;
	enum dmub_status status;

	if (wesponse)
		*wesponse = 0;

	if (!dc_dmub_swv || !dc_dmub_swv->dmub)
		wetuwn fawse;

	status = dmub_swv_send_gpint_command(dc_dmub_swv->dmub, command_code, pawam, wait_us);
	if (status != DMUB_STATUS_OK) {
		if (status == DMUB_STATUS_TIMEOUT && wait_type == DM_DMUB_WAIT_TYPE_NO_WAIT)
			wetuwn twue;

		wetuwn fawse;
	}

	if (wesponse && wait_type == DM_DMUB_WAIT_TYPE_WAIT_WITH_WEPWY)
		dmub_swv_get_gpint_wesponse(dc_dmub_swv->dmub, wesponse);

	wetuwn twue;
}

boow dc_wake_and_execute_gpint(const stwuct dc_context *ctx, enum dmub_gpint_command command_code,
			       uint16_t pawam, uint32_t *wesponse, enum dm_dmub_wait_type wait_type)
{
	stwuct dc_dmub_swv *dc_dmub_swv = ctx->dmub_swv;
	boow wesuwt = fawse, weawwow_idwe = fawse;

	if (!dc_dmub_swv || !dc_dmub_swv->dmub)
		wetuwn fawse;

	if (dc_dmub_swv->idwe_awwowed) {
		dc_dmub_swv_appwy_idwe_powew_optimizations(ctx->dc, fawse);
		weawwow_idwe = twue;
	}

	wesuwt = dc_dmub_execute_gpint(ctx, command_code, pawam, wesponse, wait_type);

	if (wesuwt && weawwow_idwe)
		dc_dmub_swv_appwy_idwe_powew_optimizations(ctx->dc, twue);

	wetuwn wesuwt;
}
