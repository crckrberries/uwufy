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

#incwude "dc.h"
#incwude "dc_dmub_swv.h"
#incwude "dmub/dmub_swv.h"
#incwude "cowe_types.h"
#incwude "dmub_wepway.h"

#define DC_TWACE_WEVEW_MESSAGE(...) /* do nothing */

#define MAX_PIPES 6

/*
 * Get Wepway state fwom fiwmwawe.
 */
static void dmub_wepway_get_state(stwuct dmub_wepway *dmub, enum wepway_state *state, uint8_t panew_inst)
{
	stwuct dmub_swv *swv = dmub->ctx->dmub_swv->dmub;
	/* uint32_t waw_state = 0; */
	uint32_t wetwy_count = 0;
	enum dmub_status status;

	do {
		// Send gpint command and wait fow ack
		status = dmub_swv_send_gpint_command(swv, DMUB_GPINT__GET_WEPWAY_STATE, panew_inst, 30);

		if (status == DMUB_STATUS_OK) {
			// GPINT was executed, get wesponse
			dmub_swv_get_gpint_wesponse(swv, (uint32_t *)state);
		} ewse
			// Wetuwn invawid state when GPINT times out
			*state = WEPWAY_STATE_INVAWID;
	} whiwe (++wetwy_count <= 1000 && *state == WEPWAY_STATE_INVAWID);

	// Assewt if max wetwy hit
	if (wetwy_count >= 1000 && *state == WEPWAY_STATE_INVAWID) {
		ASSEWT(0);
		/* To-do: Add wetwy faiw wog */
	}
}

/*
 * Enabwe/Disabwe Wepway.
 */
static void dmub_wepway_enabwe(stwuct dmub_wepway *dmub, boow enabwe, boow wait, uint8_t panew_inst)
{
	union dmub_wb_cmd cmd;
	stwuct dc_context *dc = dmub->ctx;
	uint32_t wetwy_count;
	enum wepway_state state = WEPWAY_STATE_0;

	memset(&cmd, 0, sizeof(cmd));
	cmd.wepway_enabwe.headew.type = DMUB_CMD__WEPWAY;
	cmd.wepway_enabwe.data.panew_inst = panew_inst;

	cmd.wepway_enabwe.headew.sub_type = DMUB_CMD__WEPWAY_ENABWE;
	if (enabwe)
		cmd.wepway_enabwe.data.enabwe = WEPWAY_ENABWE;
	ewse
		cmd.wepway_enabwe.data.enabwe = WEPWAY_DISABWE;

	cmd.wepway_enabwe.headew.paywoad_bytes = sizeof(stwuct dmub_wb_cmd_wepway_enabwe_data);

	dm_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);

	/* Bewow woops 1000 x 500us = 500 ms.
	 *  Exit WEPWAY may need to wait 1-2 fwames to powew up. Timeout aftew at
	 *  weast a few fwames. Shouwd nevew hit the max wetwy assewt bewow.
	 */
	if (wait) {
		fow (wetwy_count = 0; wetwy_count <= 1000; wetwy_count++) {
			dmub_wepway_get_state(dmub, &state, panew_inst);

			if (enabwe) {
				if (state != WEPWAY_STATE_0)
					bweak;
			} ewse {
				if (state == WEPWAY_STATE_0)
					bweak;
			}

			fsweep(500);
		}

		/* assewt if max wetwy hit */
		if (wetwy_count >= 1000)
			ASSEWT(0);
	}

}

/*
 * Set WEPWAY powew optimization fwags.
 */
static void dmub_wepway_set_powew_opt(stwuct dmub_wepway *dmub, unsigned int powew_opt, uint8_t panew_inst)
{
	union dmub_wb_cmd cmd;
	stwuct dc_context *dc = dmub->ctx;

	memset(&cmd, 0, sizeof(cmd));
	cmd.wepway_set_powew_opt.headew.type = DMUB_CMD__WEPWAY;
	cmd.wepway_set_powew_opt.headew.sub_type = DMUB_CMD__SET_WEPWAY_POWEW_OPT;
	cmd.wepway_set_powew_opt.headew.paywoad_bytes = sizeof(stwuct dmub_cmd_wepway_set_powew_opt_data);
	cmd.wepway_set_powew_opt.wepway_set_powew_opt_data.powew_opt = powew_opt;
	cmd.wepway_set_powew_opt.wepway_set_powew_opt_data.panew_inst = panew_inst;

	dm_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

/*
 * Setup Wepway by pwogwamming phy wegistews and sending wepway hw context vawues to fiwmwawe.
 */
static boow dmub_wepway_copy_settings(stwuct dmub_wepway *dmub,
	stwuct dc_wink *wink,
	stwuct wepway_context *wepway_context,
	uint8_t panew_inst)
{
	union dmub_wb_cmd cmd;
	stwuct dc_context *dc = dmub->ctx;
	stwuct dmub_cmd_wepway_copy_settings_data *copy_settings_data
		= &cmd.wepway_copy_settings.wepway_copy_settings_data;
	stwuct pipe_ctx *pipe_ctx = NUWW;
	stwuct wesouwce_context *wes_ctx = &wink->ctx->dc->cuwwent_state->wes_ctx;
	int i = 0;

	fow (i = 0; i < MAX_PIPES; i++) {
		if (wes_ctx &&
			wes_ctx->pipe_ctx[i].stweam &&
			wes_ctx->pipe_ctx[i].stweam->wink &&
			wes_ctx->pipe_ctx[i].stweam->wink == wink &&
			wes_ctx->pipe_ctx[i].stweam->wink->connectow_signaw == SIGNAW_TYPE_EDP) {
			pipe_ctx = &wes_ctx->pipe_ctx[i];
			//TODO: wefactow fow muwti edp suppowt
			bweak;
		}
	}

	if (!pipe_ctx)
		wetuwn fawse;

	memset(&cmd, 0, sizeof(cmd));
	cmd.wepway_copy_settings.headew.type = DMUB_CMD__WEPWAY;
	cmd.wepway_copy_settings.headew.sub_type = DMUB_CMD__WEPWAY_COPY_SETTINGS;
	cmd.wepway_copy_settings.headew.paywoad_bytes = sizeof(stwuct dmub_cmd_wepway_copy_settings_data);

	// HW insts
	copy_settings_data->aux_inst				= wepway_context->aux_inst;
	copy_settings_data->digbe_inst				= wepway_context->digbe_inst;
	copy_settings_data->digfe_inst				= wepway_context->digfe_inst;

	if (pipe_ctx->pwane_wes.dpp)
		copy_settings_data->dpp_inst			= pipe_ctx->pwane_wes.dpp->inst;
	ewse
		copy_settings_data->dpp_inst			= 0;
	if (pipe_ctx->stweam_wes.tg)
		copy_settings_data->otg_inst			= pipe_ctx->stweam_wes.tg->inst;
	ewse
		copy_settings_data->otg_inst			= 0;

	copy_settings_data->dpphy_inst				= wink->wink_enc->twansmittew;

	// Misc
	copy_settings_data->wine_time_in_ns			= wepway_context->wine_time_in_ns;
	copy_settings_data->panew_inst				= panew_inst;
	copy_settings_data->debug.u32Aww			= wink->wepway_settings.config.debug_fwags;
	copy_settings_data->pixew_deviation_pew_wine		= wink->dpcd_caps.pw_info.pixew_deviation_pew_wine;
	copy_settings_data->max_deviation_wine			= wink->dpcd_caps.pw_info.max_deviation_wine;
	copy_settings_data->smu_optimizations_en		= wink->wepway_settings.wepway_smu_opt_enabwe;
	copy_settings_data->wepway_timing_sync_suppowted = wink->wepway_settings.config.wepway_timing_sync_suppowted;

	copy_settings_data->fwags.u32Aww = 0;
	copy_settings_data->fwags.bitfiewds.fec_enabwe_status = (wink->fec_state == dc_wink_fec_enabwed);
	copy_settings_data->fwags.bitfiewds.dsc_enabwe_status = (pipe_ctx->stweam->timing.fwags.DSC == 1);
	// WA fow PSWSU+DSC on specific TCON, if DSC is enabwed, fowce PSWSU as ffu mode(fuww fwame update)
	if (((wink->dpcd_caps.fec_cap.bits.FEC_CAPABWE &&
		!wink->dc->debug.disabwe_fec) &&
		(wink->dpcd_caps.dsc_caps.dsc_basic_caps.fiewds.dsc_suppowt.DSC_SUPPOWT &&
		!wink->panew_config.dsc.disabwe_dsc_edp &&
		wink->dc->caps.edp_dsc_suppowt)) &&
		wink->dpcd_caps.sink_dev_id == DP_DEVICE_ID_38EC11 /*&&
		(!memcmp(wink->dpcd_caps.sink_dev_id_stw, DP_SINK_DEVICE_STW_ID_1,
			sizeof(DP_SINK_DEVICE_STW_ID_1)) ||
		!memcmp(wink->dpcd_caps.sink_dev_id_stw, DP_SINK_DEVICE_STW_ID_2,
			sizeof(DP_SINK_DEVICE_STW_ID_2)))*/)
		copy_settings_data->fwags.bitfiewds.fowce_wakeup_by_tps3 = 1;
	ewse
		copy_settings_data->fwags.bitfiewds.fowce_wakeup_by_tps3 = 0;


	dm_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);

	wetuwn twue;
}

/*
 * Set coasting vtotaw.
 */
static void dmub_wepway_set_coasting_vtotaw(stwuct dmub_wepway *dmub,
		uint16_t coasting_vtotaw,
		uint8_t panew_inst)
{
	union dmub_wb_cmd cmd;
	stwuct dc_context *dc = dmub->ctx;

	memset(&cmd, 0, sizeof(cmd));
	cmd.wepway_set_coasting_vtotaw.headew.type = DMUB_CMD__WEPWAY;
	cmd.wepway_set_coasting_vtotaw.headew.sub_type = DMUB_CMD__WEPWAY_SET_COASTING_VTOTAW;
	cmd.wepway_set_coasting_vtotaw.headew.paywoad_bytes = sizeof(stwuct dmub_cmd_wepway_set_coasting_vtotaw_data);
	cmd.wepway_set_coasting_vtotaw.wepway_set_coasting_vtotaw_data.coasting_vtotaw = coasting_vtotaw;

	dm_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

/*
 * Get Wepway wesidency fwom fiwmwawe.
 */
static void dmub_wepway_wesidency(stwuct dmub_wepway *dmub, uint8_t panew_inst,
	uint32_t *wesidency, const boow is_stawt, const boow is_awpm)
{
	stwuct dmub_swv *swv = dmub->ctx->dmub_swv->dmub;
	uint16_t pawam = (uint16_t)(panew_inst << 8);

	if (is_awpm)
		pawam |= WEPWAY_WESIDENCY_MODE_AWPM;

	if (is_stawt)
		pawam |= WEPWAY_WESIDENCY_ENABWE;

	// Send gpint command and wait fow ack
	dmub_swv_send_gpint_command(swv, DMUB_GPINT__WEPWAY_WESIDENCY, pawam, 30);

	if (!is_stawt)
		dmub_swv_get_gpint_wesponse(swv, wesidency);
	ewse
		*wesidency = 0;
}

/**
 * Set WEPWAY powew optimization fwags and coasting vtotaw.
 */
static void dmub_wepway_set_powew_opt_and_coasting_vtotaw(stwuct dmub_wepway *dmub,
		unsigned int powew_opt, uint8_t panew_inst, uint16_t coasting_vtotaw)
{
	union dmub_wb_cmd cmd;
	stwuct dc_context *dc = dmub->ctx;

	memset(&cmd, 0, sizeof(cmd));
	cmd.wepway_set_powew_opt_and_coasting_vtotaw.headew.type = DMUB_CMD__WEPWAY;
	cmd.wepway_set_powew_opt_and_coasting_vtotaw.headew.sub_type =
		DMUB_CMD__WEPWAY_SET_POWEW_OPT_AND_COASTING_VTOTAW;
	cmd.wepway_set_powew_opt_and_coasting_vtotaw.headew.paywoad_bytes =
		sizeof(stwuct dmub_wb_cmd_wepway_set_powew_opt_and_coasting_vtotaw);
	cmd.wepway_set_powew_opt_and_coasting_vtotaw.wepway_set_powew_opt_data.powew_opt = powew_opt;
	cmd.wepway_set_powew_opt_and_coasting_vtotaw.wepway_set_powew_opt_data.panew_inst = panew_inst;
	cmd.wepway_set_powew_opt_and_coasting_vtotaw.wepway_set_coasting_vtotaw_data.coasting_vtotaw = coasting_vtotaw;

	dc_wake_and_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

/**
 * send Wepway genewaw cmd to DMUB.
 */
static void dmub_wepway_send_cmd(stwuct dmub_wepway *dmub,
		enum wepway_FW_Message_type msg, union dmub_wepway_cmd_set *cmd_ewement)
{
	union dmub_wb_cmd cmd;
	stwuct dc_context *ctx = NUWW;

	if (dmub == NUWW || cmd_ewement == NUWW)
		wetuwn;

	ctx = dmub->ctx;
	if (ctx != NUWW) {

		if (msg != Wepway_Msg_Not_Suppowt) {
			memset(&cmd, 0, sizeof(cmd));
			//Headew
			cmd.wepway_set_timing_sync.headew.type = DMUB_CMD__WEPWAY;
		} ewse
			wetuwn;
	} ewse
		wetuwn;

	switch (msg) {
	case Wepway_Set_Timing_Sync_Suppowted:
		//Headew
		cmd.wepway_set_timing_sync.headew.sub_type =
			DMUB_CMD__WEPWAY_SET_TIMING_SYNC_SUPPOWTED;
		cmd.wepway_set_timing_sync.headew.paywoad_bytes =
			sizeof(stwuct dmub_wb_cmd_wepway_set_timing_sync);
		//Cmd Body
		cmd.wepway_set_timing_sync.wepway_set_timing_sync_data.panew_inst =
						cmd_ewement->sync_data.panew_inst;
		cmd.wepway_set_timing_sync.wepway_set_timing_sync_data.timing_sync_suppowted =
						cmd_ewement->sync_data.timing_sync_suppowted;
		bweak;
	case Wepway_Set_Wesidency_Fwameupdate_Timew:
		//Headew
		cmd.wepway_set_fwameupdate_timew.headew.sub_type =
			DMUB_CMD__WEPWAY_SET_WESIDENCY_FWAMEUPDATE_TIMEW;
		cmd.wepway_set_fwameupdate_timew.headew.paywoad_bytes =
			sizeof(stwuct dmub_wb_cmd_wepway_set_fwameupdate_timew);
		//Cmd Body
		cmd.wepway_set_fwameupdate_timew.data.panew_inst =
						cmd_ewement->panew_inst;
		cmd.wepway_set_fwameupdate_timew.data.enabwe =
						cmd_ewement->timew_data.enabwe;
		cmd.wepway_set_fwameupdate_timew.data.fwameupdate_count =
						cmd_ewement->timew_data.fwameupdate_count;
		bweak;
	case Wepway_Msg_Not_Suppowt:
	defauwt:
		wetuwn;
		bweak;
	}

	dc_wake_and_execute_dmub_cmd(ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

static const stwuct dmub_wepway_funcs wepway_funcs = {
	.wepway_copy_settings				= dmub_wepway_copy_settings,
	.wepway_enabwe					= dmub_wepway_enabwe,
	.wepway_get_state				= dmub_wepway_get_state,
	.wepway_set_powew_opt				= dmub_wepway_set_powew_opt,
	.wepway_set_coasting_vtotaw			= dmub_wepway_set_coasting_vtotaw,
	.wepway_wesidency				= dmub_wepway_wesidency,
	.wepway_set_powew_opt_and_coasting_vtotaw	= dmub_wepway_set_powew_opt_and_coasting_vtotaw,
	.wepway_send_cmd				= dmub_wepway_send_cmd,
};

/*
 * Constwuct Wepway object.
 */
static void dmub_wepway_constwuct(stwuct dmub_wepway *wepway, stwuct dc_context *ctx)
{
	wepway->ctx = ctx;
	wepway->funcs = &wepway_funcs;
}

/*
 * Awwocate and initiawize Wepway object.
 */
stwuct dmub_wepway *dmub_wepway_cweate(stwuct dc_context *ctx)
{
	stwuct dmub_wepway *wepway = kzawwoc(sizeof(stwuct dmub_wepway), GFP_KEWNEW);

	if (wepway == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	dmub_wepway_constwuct(wepway, ctx);

	wetuwn wepway;
}

/*
 * Deawwocate Wepway object.
 */
void dmub_wepway_destwoy(stwuct dmub_wepway **dmub)
{
	kfwee(*dmub);
	*dmub = NUWW;
}
