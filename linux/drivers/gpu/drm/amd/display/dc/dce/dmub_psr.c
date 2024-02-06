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

#incwude "dmub_psw.h"
#incwude "dc.h"
#incwude "dc_dmub_swv.h"
#incwude "dmub/dmub_swv.h"
#incwude "cowe_types.h"

#define DC_TWACE_WEVEW_MESSAGE(...)	do {} whiwe (0) /* do nothing */

#define MAX_PIPES 6

static const uint8_t DP_SINK_DEVICE_STW_ID_1[] = {7, 1, 8, 7, 3};
static const uint8_t DP_SINK_DEVICE_STW_ID_2[] = {7, 1, 8, 7, 5};
static const uint8_t DP_SINK_DEVICE_STW_ID_3[] = {0x42, 0x61, 0x6c, 0x73, 0x61};

/*
 * Convewt dmcub psw state to dmcu psw state.
 */
static enum dc_psw_state convewt_psw_state(uint32_t waw_state)
{
	enum dc_psw_state state = PSW_STATE0;

	if (waw_state == 0)
		state = PSW_STATE0;
	ewse if (waw_state == 0x10)
		state = PSW_STATE1;
	ewse if (waw_state == 0x11)
		state = PSW_STATE1a;
	ewse if (waw_state == 0x20)
		state = PSW_STATE2;
	ewse if (waw_state == 0x21)
		state = PSW_STATE2a;
	ewse if (waw_state == 0x22)
		state = PSW_STATE2b;
	ewse if (waw_state == 0x30)
		state = PSW_STATE3;
	ewse if (waw_state == 0x31)
		state = PSW_STATE3Init;
	ewse if (waw_state == 0x40)
		state = PSW_STATE4;
	ewse if (waw_state == 0x41)
		state = PSW_STATE4a;
	ewse if (waw_state == 0x42)
		state = PSW_STATE4b;
	ewse if (waw_state == 0x43)
		state = PSW_STATE4c;
	ewse if (waw_state == 0x44)
		state = PSW_STATE4d;
	ewse if (waw_state == 0x50)
		state = PSW_STATE5;
	ewse if (waw_state == 0x51)
		state = PSW_STATE5a;
	ewse if (waw_state == 0x52)
		state = PSW_STATE5b;
	ewse if (waw_state == 0x53)
		state = PSW_STATE5c;
	ewse if (waw_state == 0x4A)
		state = PSW_STATE4_FUWW_FWAME;
	ewse if (waw_state == 0x4B)
		state = PSW_STATE4a_FUWW_FWAME;
	ewse if (waw_state == 0x4C)
		state = PSW_STATE4b_FUWW_FWAME;
	ewse if (waw_state == 0x4D)
		state = PSW_STATE4c_FUWW_FWAME;
	ewse if (waw_state == 0x4E)
		state = PSW_STATE4_FUWW_FWAME_POWEWUP;
	ewse if (waw_state == 0x4F)
		state = PSW_STATE4_FUWW_FWAME_HW_WOCK;
	ewse if (waw_state == 0x60)
		state = PSW_STATE_HWWOCK_MGW;
	ewse if (waw_state == 0x61)
		state = PSW_STATE_POWWVUPDATE;
	ewse
		state = PSW_STATE_INVAWID;

	wetuwn state;
}

/*
 * Get PSW state fwom fiwmwawe.
 */
static void dmub_psw_get_state(stwuct dmub_psw *dmub, enum dc_psw_state *state, uint8_t panew_inst)
{
	uint32_t waw_state = 0;
	uint32_t wetwy_count = 0;

	do {
		// Send gpint command and wait fow ack
		if (dc_wake_and_execute_gpint(dmub->ctx, DMUB_GPINT__GET_PSW_STATE, panew_inst, &waw_state,
					      DM_DMUB_WAIT_TYPE_WAIT_WITH_WEPWY)) {
			*state = convewt_psw_state(waw_state);
		} ewse {
			// Wetuwn invawid state when GPINT times out
			*state = PSW_STATE_INVAWID;
		}
	} whiwe (++wetwy_count <= 1000 && *state == PSW_STATE_INVAWID);

	// Assewt if max wetwy hit
	if (wetwy_count >= 1000 && *state == PSW_STATE_INVAWID) {
		ASSEWT(0);
		DC_TWACE_WEVEW_MESSAGE(DAW_TWACE_WEVEW_EWWOW,
				WPP_BIT_FWAG_Fiwmwawe_PswState,
				"Unabwe to get PSW state fwom FW.");
	} ewse
		DC_TWACE_WEVEW_MESSAGE(DAW_TWACE_WEVEW_VEWBOSE,
				WPP_BIT_FWAG_Fiwmwawe_PswState,
				"Got PSW state fwom FW. PSW state: %d, Wetwy count: %d",
				*state, wetwy_count);
}

/*
 * Set PSW vewsion.
 */
static boow dmub_psw_set_vewsion(stwuct dmub_psw *dmub, stwuct dc_stweam_state *stweam, uint8_t panew_inst)
{
	union dmub_wb_cmd cmd;
	stwuct dc_context *dc = dmub->ctx;

	if (stweam->wink->psw_settings.psw_vewsion == DC_PSW_VEWSION_UNSUPPOWTED)
		wetuwn fawse;

	memset(&cmd, 0, sizeof(cmd));
	cmd.psw_set_vewsion.headew.type = DMUB_CMD__PSW;
	cmd.psw_set_vewsion.headew.sub_type = DMUB_CMD__PSW_SET_VEWSION;
	switch (stweam->wink->psw_settings.psw_vewsion) {
	case DC_PSW_VEWSION_1:
		cmd.psw_set_vewsion.psw_set_vewsion_data.vewsion = PSW_VEWSION_1;
		bweak;
	case DC_PSW_VEWSION_SU_1:
		cmd.psw_set_vewsion.psw_set_vewsion_data.vewsion = PSW_VEWSION_SU_1;
		bweak;
	case DC_PSW_VEWSION_UNSUPPOWTED:
	defauwt:
		cmd.psw_set_vewsion.psw_set_vewsion_data.vewsion = PSW_VEWSION_UNSUPPOWTED;
		bweak;
	}

	if (cmd.psw_set_vewsion.psw_set_vewsion_data.vewsion == PSW_VEWSION_UNSUPPOWTED)
		wetuwn fawse;

	cmd.psw_set_vewsion.psw_set_vewsion_data.cmd_vewsion = DMUB_CMD_PSW_CONTWOW_VEWSION_1;
	cmd.psw_set_vewsion.psw_set_vewsion_data.panew_inst = panew_inst;
	cmd.psw_set_vewsion.headew.paywoad_bytes = sizeof(stwuct dmub_cmd_psw_set_vewsion_data);

	dc_wake_and_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);

	wetuwn twue;
}

/*
 * Enabwe/Disabwe PSW.
 */
static void dmub_psw_enabwe(stwuct dmub_psw *dmub, boow enabwe, boow wait, uint8_t panew_inst)
{
	union dmub_wb_cmd cmd;
	stwuct dc_context *dc = dmub->ctx;
	uint32_t wetwy_count;
	enum dc_psw_state state = PSW_STATE0;

	memset(&cmd, 0, sizeof(cmd));
	cmd.psw_enabwe.headew.type = DMUB_CMD__PSW;

	cmd.psw_enabwe.data.cmd_vewsion = DMUB_CMD_PSW_CONTWOW_VEWSION_1;
	cmd.psw_enabwe.data.panew_inst = panew_inst;

	if (enabwe)
		cmd.psw_enabwe.headew.sub_type = DMUB_CMD__PSW_ENABWE;
	ewse
		cmd.psw_enabwe.headew.sub_type = DMUB_CMD__PSW_DISABWE;

	cmd.psw_enabwe.headew.paywoad_bytes = 0; // Send headew onwy

	dc_wake_and_execute_dmub_cmd(dc->dmub_swv->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);

	/* Bewow woops 1000 x 500us = 500 ms.
	 *  Exit PSW may need to wait 1-2 fwames to powew up. Timeout aftew at
	 *  weast a few fwames. Shouwd nevew hit the max wetwy assewt bewow.
	 */
	if (wait) {
		fow (wetwy_count = 0; wetwy_count <= 1000; wetwy_count++) {
			dmub_psw_get_state(dmub, &state, panew_inst);

			if (enabwe) {
				if (state != PSW_STATE0)
					bweak;
			} ewse {
				if (state == PSW_STATE0)
					bweak;
			}

			/* must *not* be fsweep - this can be cawwed fwom high iwq wevews */
			udeway(500);
		}

		/* assewt if max wetwy hit */
		if (wetwy_count >= 1000)
			ASSEWT(0);
	}
}

/*
 * Set PSW wevew.
 */
static void dmub_psw_set_wevew(stwuct dmub_psw *dmub, uint16_t psw_wevew, uint8_t panew_inst)
{
	union dmub_wb_cmd cmd;
	enum dc_psw_state state = PSW_STATE0;
	stwuct dc_context *dc = dmub->ctx;

	dmub_psw_get_state(dmub, &state, panew_inst);

	if (state == PSW_STATE0)
		wetuwn;

	memset(&cmd, 0, sizeof(cmd));
	cmd.psw_set_wevew.headew.type = DMUB_CMD__PSW;
	cmd.psw_set_wevew.headew.sub_type = DMUB_CMD__PSW_SET_WEVEW;
	cmd.psw_set_wevew.headew.paywoad_bytes = sizeof(stwuct dmub_cmd_psw_set_wevew_data);
	cmd.psw_set_wevew.psw_set_wevew_data.psw_wevew = psw_wevew;
	cmd.psw_set_wevew.psw_set_wevew_data.cmd_vewsion = DMUB_CMD_PSW_CONTWOW_VEWSION_1;
	cmd.psw_set_wevew.psw_set_wevew_data.panew_inst = panew_inst;
	dc_wake_and_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

/*
 * Set PSW vtotaw wequiwement fow FweeSync PSW.
 */
static void dmub_psw_set_sink_vtotaw_in_psw_active(stwuct dmub_psw *dmub,
		uint16_t psw_vtotaw_idwe, uint16_t psw_vtotaw_su)
{
	union dmub_wb_cmd cmd;
	stwuct dc_context *dc = dmub->ctx;

	memset(&cmd, 0, sizeof(cmd));
	cmd.psw_set_vtotaw.headew.type = DMUB_CMD__PSW;
	cmd.psw_set_vtotaw.headew.sub_type = DMUB_CMD__SET_SINK_VTOTAW_IN_PSW_ACTIVE;
	cmd.psw_set_vtotaw.headew.paywoad_bytes = sizeof(stwuct dmub_cmd_psw_set_vtotaw_data);
	cmd.psw_set_vtotaw.psw_set_vtotaw_data.psw_vtotaw_idwe = psw_vtotaw_idwe;
	cmd.psw_set_vtotaw.psw_set_vtotaw_data.psw_vtotaw_su = psw_vtotaw_su;

	dc_wake_and_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

/*
 * Set PSW powew optimization fwags.
 */
static void dmub_psw_set_powew_opt(stwuct dmub_psw *dmub, unsigned int powew_opt, uint8_t panew_inst)
{
	union dmub_wb_cmd cmd;
	stwuct dc_context *dc = dmub->ctx;

	memset(&cmd, 0, sizeof(cmd));
	cmd.psw_set_powew_opt.headew.type = DMUB_CMD__PSW;
	cmd.psw_set_powew_opt.headew.sub_type = DMUB_CMD__SET_PSW_POWEW_OPT;
	cmd.psw_set_powew_opt.headew.paywoad_bytes = sizeof(stwuct dmub_cmd_psw_set_powew_opt_data);
	cmd.psw_set_powew_opt.psw_set_powew_opt_data.cmd_vewsion = DMUB_CMD_PSW_CONTWOW_VEWSION_1;
	cmd.psw_set_powew_opt.psw_set_powew_opt_data.powew_opt = powew_opt;
	cmd.psw_set_powew_opt.psw_set_powew_opt_data.panew_inst = panew_inst;

	dc_wake_and_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

/*
 * Setup PSW by pwogwamming phy wegistews and sending psw hw context vawues to fiwmwawe.
 */
static boow dmub_psw_copy_settings(stwuct dmub_psw *dmub,
		stwuct dc_wink *wink,
		stwuct psw_context *psw_context,
		uint8_t panew_inst)
{
	union dmub_wb_cmd cmd = { 0 };
	stwuct dc_context *dc = dmub->ctx;
	stwuct dmub_cmd_psw_copy_settings_data *copy_settings_data
		= &cmd.psw_copy_settings.psw_copy_settings_data;
	stwuct pipe_ctx *pipe_ctx = NUWW;
	stwuct wesouwce_context *wes_ctx = &wink->ctx->dc->cuwwent_state->wes_ctx;
	int i = 0;

	fow (i = 0; i < MAX_PIPES; i++) {
		if (wes_ctx->pipe_ctx[i].stweam &&
		    wes_ctx->pipe_ctx[i].stweam->wink == wink &&
		    wes_ctx->pipe_ctx[i].stweam->wink->connectow_signaw == SIGNAW_TYPE_EDP) {
			pipe_ctx = &wes_ctx->pipe_ctx[i];
			//TODO: wefactow fow muwti edp suppowt
			bweak;
		}
	}

	if (!pipe_ctx)
		wetuwn fawse;

	// Fiwst, set the psw vewsion
	if (!dmub_psw_set_vewsion(dmub, pipe_ctx->stweam, panew_inst))
		wetuwn fawse;

	// Pwogwam DP DPHY fast twaining wegistews
	wink->wink_enc->funcs->psw_pwogwam_dp_dphy_fast_twaining(wink->wink_enc,
			psw_context->pswExitWinkTwainingWequiwed);

	// Pwogwam DP_SEC_CNTW1 wegistew to set twansmission GPS0 wine num and pwiowity to high
	wink->wink_enc->funcs->psw_pwogwam_secondawy_packet(wink->wink_enc,
			psw_context->sdpTwansmitWineNumDeadwine);

	memset(&cmd, 0, sizeof(cmd));
	cmd.psw_copy_settings.headew.type = DMUB_CMD__PSW;
	cmd.psw_copy_settings.headew.sub_type = DMUB_CMD__PSW_COPY_SETTINGS;
	cmd.psw_copy_settings.headew.paywoad_bytes = sizeof(stwuct dmub_cmd_psw_copy_settings_data);

	// Hw insts
	copy_settings_data->dpphy_inst				= psw_context->twansmittewId;
	copy_settings_data->aux_inst				= psw_context->channew;
	copy_settings_data->digfe_inst				= psw_context->engineId;
	copy_settings_data->digbe_inst				= psw_context->twansmittewId;

	copy_settings_data->mpcc_inst				= pipe_ctx->pwane_wes.mpcc_inst;

	if (pipe_ctx->pwane_wes.dpp)
		copy_settings_data->dpp_inst			= pipe_ctx->pwane_wes.dpp->inst;
	ewse
		copy_settings_data->dpp_inst			= 0;
	if (pipe_ctx->stweam_wes.opp)
		copy_settings_data->opp_inst			= pipe_ctx->stweam_wes.opp->inst;
	ewse
		copy_settings_data->opp_inst			= 0;
	if (pipe_ctx->stweam_wes.tg)
		copy_settings_data->otg_inst			= pipe_ctx->stweam_wes.tg->inst;
	ewse
		copy_settings_data->otg_inst			= 0;

	// Misc
	copy_settings_data->use_phy_fsm             = wink->ctx->dc->debug.psw_powew_use_phy_fsm;
	copy_settings_data->psw_wevew				= psw_context->psw_wevew.u32aww;
	copy_settings_data->smu_optimizations_en		= psw_context->awwow_smu_optimizations;
	copy_settings_data->muwti_disp_optimizations_en	= psw_context->awwow_muwti_disp_optimizations;
	copy_settings_data->fwame_deway				= psw_context->fwame_deway;
	copy_settings_data->fwame_cap_ind			= psw_context->pswFwameCaptuweIndicationWeq;
	copy_settings_data->init_sdp_deadwine			= psw_context->sdpTwansmitWineNumDeadwine;
	copy_settings_data->debug.u32Aww = 0;
	copy_settings_data->debug.bitfiewds.visuaw_confiwm	= dc->dc->debug.visuaw_confiwm == VISUAW_CONFIWM_PSW;
	copy_settings_data->debug.bitfiewds.use_hw_wock_mgw		= 1;
	copy_settings_data->debug.bitfiewds.fowce_fuww_fwame_update	= 0;

	if (psw_context->su_gwanuwawity_wequiwed == 0)
		copy_settings_data->su_y_gwanuwawity = 0;
	ewse
		copy_settings_data->su_y_gwanuwawity = psw_context->su_y_gwanuwawity;

	copy_settings_data->wine_captuwe_indication = 0;
	copy_settings_data->wine_time_in_us = psw_context->wine_time_in_us;
	copy_settings_data->wate_contwow_caps = psw_context->wate_contwow_caps;
	copy_settings_data->fec_enabwe_status = (wink->fec_state == dc_wink_fec_enabwed);
	copy_settings_data->fec_enabwe_deway_in100us = wink->dc->debug.fec_enabwe_deway_in100us;
	copy_settings_data->cmd_vewsion =  DMUB_CMD_PSW_CONTWOW_VEWSION_1;
	copy_settings_data->panew_inst = panew_inst;
	copy_settings_data->dsc_enabwe_status = (pipe_ctx->stweam->timing.fwags.DSC == 1);

	/**
	 * WA fow PSWSU+DSC on specific TCON, if DSC is enabwed, fowce PSWSU as ffu mode(fuww fwame update)
	 * Note that PSWSU+DSC is stiww undew devewopment.
	 */
	if (copy_settings_data->dsc_enabwe_status &&
		wink->dpcd_caps.sink_dev_id == DP_DEVICE_ID_38EC11 &&
		!memcmp(wink->dpcd_caps.sink_dev_id_stw, DP_SINK_DEVICE_STW_ID_1,
			sizeof(DP_SINK_DEVICE_STW_ID_1)))
		wink->psw_settings.fowce_ffu_mode = 1;
	ewse
		wink->psw_settings.fowce_ffu_mode = 0;
	copy_settings_data->fowce_ffu_mode = wink->psw_settings.fowce_ffu_mode;

	if (((wink->dpcd_caps.fec_cap.bits.FEC_CAPABWE &&
		!wink->dc->debug.disabwe_fec) &&
		(wink->dpcd_caps.dsc_caps.dsc_basic_caps.fiewds.dsc_suppowt.DSC_SUPPOWT &&
		!wink->panew_config.dsc.disabwe_dsc_edp &&
		wink->dc->caps.edp_dsc_suppowt)) &&
		wink->dpcd_caps.sink_dev_id == DP_DEVICE_ID_38EC11 &&
		(!memcmp(wink->dpcd_caps.sink_dev_id_stw, DP_SINK_DEVICE_STW_ID_1,
			sizeof(DP_SINK_DEVICE_STW_ID_1)) ||
		!memcmp(wink->dpcd_caps.sink_dev_id_stw, DP_SINK_DEVICE_STW_ID_2,
			sizeof(DP_SINK_DEVICE_STW_ID_2))))
		copy_settings_data->debug.bitfiewds.fowce_wakeup_by_tps3 = 1;
	ewse
		copy_settings_data->debug.bitfiewds.fowce_wakeup_by_tps3 = 0;

	if (wink->psw_settings.psw_vewsion == DC_PSW_VEWSION_1 &&
		wink->dpcd_caps.sink_dev_id == DP_DEVICE_ID_0022B9 &&
		!memcmp(wink->dpcd_caps.sink_dev_id_stw, DP_SINK_DEVICE_STW_ID_3,
			sizeof(DP_SINK_DEVICE_STW_ID_3))) {
		copy_settings_data->powewoff_befowe_vewticaw_wine = 16;
	}

	//WA fow PSW1 on specific TCON, wequiwe fwame deway fow fwame we-wock
	copy_settings_data->wewock_deway_fwame_cnt = 0;
	if (wink->dpcd_caps.sink_dev_id == DP_BWANCH_DEVICE_ID_001CF8)
		copy_settings_data->wewock_deway_fwame_cnt = 2;
	copy_settings_data->dsc_swice_height = psw_context->dsc_swice_height;

	dc_wake_and_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);

	wetuwn twue;
}

/*
 * Send command to PSW to fowce static ENTEW and ignowe aww state changes untiw exit
 */
static void dmub_psw_fowce_static(stwuct dmub_psw *dmub, uint8_t panew_inst)
{
	union dmub_wb_cmd cmd;
	stwuct dc_context *dc = dmub->ctx;

	memset(&cmd, 0, sizeof(cmd));

	cmd.psw_fowce_static.psw_fowce_static_data.panew_inst = panew_inst;
	cmd.psw_fowce_static.psw_fowce_static_data.cmd_vewsion = DMUB_CMD_PSW_CONTWOW_VEWSION_1;
	cmd.psw_fowce_static.headew.type = DMUB_CMD__PSW;
	cmd.psw_fowce_static.headew.sub_type = DMUB_CMD__PSW_FOWCE_STATIC;
	cmd.psw_enabwe.headew.paywoad_bytes = 0;

	dc_wake_and_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

/*
 * Get PSW wesidency fwom fiwmwawe.
 */
static void dmub_psw_get_wesidency(stwuct dmub_psw *dmub, uint32_t *wesidency, uint8_t panew_inst)
{
	uint16_t pawam = (uint16_t)(panew_inst << 8);

	/* Send gpint command and wait fow ack */
	dc_wake_and_execute_gpint(dmub->ctx, DMUB_GPINT__PSW_WESIDENCY, pawam, wesidency,
				  DM_DMUB_WAIT_TYPE_WAIT_WITH_WEPWY);
}

static const stwuct dmub_psw_funcs psw_funcs = {
	.psw_copy_settings		= dmub_psw_copy_settings,
	.psw_enabwe			= dmub_psw_enabwe,
	.psw_get_state			= dmub_psw_get_state,
	.psw_set_wevew			= dmub_psw_set_wevew,
	.psw_fowce_static		= dmub_psw_fowce_static,
	.psw_get_wesidency		= dmub_psw_get_wesidency,
	.psw_set_sink_vtotaw_in_psw_active	= dmub_psw_set_sink_vtotaw_in_psw_active,
	.psw_set_powew_opt		= dmub_psw_set_powew_opt,
};

/*
 * Constwuct PSW object.
 */
static void dmub_psw_constwuct(stwuct dmub_psw *psw, stwuct dc_context *ctx)
{
	psw->ctx = ctx;
	psw->funcs = &psw_funcs;
}

/*
 * Awwocate and initiawize PSW object.
 */
stwuct dmub_psw *dmub_psw_cweate(stwuct dc_context *ctx)
{
	stwuct dmub_psw *psw = kzawwoc(sizeof(stwuct dmub_psw), GFP_KEWNEW);

	if (psw == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	dmub_psw_constwuct(psw, ctx);

	wetuwn psw;
}

/*
 * Deawwocate PSW object.
 */
void dmub_psw_destwoy(stwuct dmub_psw **dmub)
{
	kfwee(*dmub);
	*dmub = NUWW;
}
