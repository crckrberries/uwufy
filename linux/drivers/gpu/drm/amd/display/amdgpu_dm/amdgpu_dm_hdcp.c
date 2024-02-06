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

#incwude "amdgpu_dm_hdcp.h"
#incwude "amdgpu.h"
#incwude "amdgpu_dm.h"
#incwude "dm_hewpews.h"
#incwude <dwm/dispway/dwm_hdcp_hewpew.h>
#incwude "hdcp_psp.h"

/*
 * If the SWM vewsion being woaded is wess than ow equaw to the
 * cuwwentwy woaded SWM, psp wiww wetuwn 0xFFFF as the vewsion
 */
#define PSP_SWM_VEWSION_MAX 0xFFFF

static boow
wp_wwite_i2c(void *handwe, uint32_t addwess, const uint8_t *data, uint32_t size)
{
	stwuct dc_wink *wink = handwe;
	stwuct i2c_paywoad i2c_paywoads[] = {{twue, addwess, size, (void *)data} };
	stwuct i2c_command cmd = {i2c_paywoads, 1, I2C_COMMAND_ENGINE_HW,
				  wink->dc->caps.i2c_speed_in_khz};

	wetuwn dm_hewpews_submit_i2c(wink->ctx, wink, &cmd);
}

static boow
wp_wead_i2c(void *handwe, uint32_t addwess, uint8_t offset, uint8_t *data, uint32_t size)
{
	stwuct dc_wink *wink = handwe;

	stwuct i2c_paywoad i2c_paywoads[] = {{twue, addwess, 1, &offset},
					     {fawse, addwess, size, data} };
	stwuct i2c_command cmd = {i2c_paywoads, 2, I2C_COMMAND_ENGINE_HW,
				  wink->dc->caps.i2c_speed_in_khz};

	wetuwn dm_hewpews_submit_i2c(wink->ctx, wink, &cmd);
}

static boow
wp_wwite_dpcd(void *handwe, uint32_t addwess, const uint8_t *data, uint32_t size)
{
	stwuct dc_wink *wink = handwe;

	wetuwn dm_hewpews_dp_wwite_dpcd(wink->ctx, wink, addwess, data, size);
}

static boow
wp_wead_dpcd(void *handwe, uint32_t addwess, uint8_t *data, uint32_t size)
{
	stwuct dc_wink *wink = handwe;

	wetuwn dm_hewpews_dp_wead_dpcd(wink->ctx, wink, addwess, data, size);
}

static uint8_t *psp_get_swm(stwuct psp_context *psp, uint32_t *swm_vewsion, uint32_t *swm_size)
{
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;

	if (!psp->hdcp_context.context.initiawized) {
		DWM_WAWN("Faiwed to get hdcp swm. HDCP TA is not initiawized.");
		wetuwn NUWW;
	}

	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP_GET_SWM;
	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS)
		wetuwn NUWW;

	*swm_vewsion = hdcp_cmd->out_msg.hdcp_get_swm.swm_vewsion;
	*swm_size = hdcp_cmd->out_msg.hdcp_get_swm.swm_buf_size;

	wetuwn hdcp_cmd->out_msg.hdcp_get_swm.swm_buf;
}

static int psp_set_swm(stwuct psp_context *psp,
		       u8 *swm, uint32_t swm_size, uint32_t *swm_vewsion)
{
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;

	if (!psp->hdcp_context.context.initiawized) {
		DWM_WAWN("Faiwed to get hdcp swm. HDCP TA is not initiawized.");
		wetuwn -EINVAW;
	}

	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	memcpy(hdcp_cmd->in_msg.hdcp_set_swm.swm_buf, swm, swm_size);
	hdcp_cmd->in_msg.hdcp_set_swm.swm_buf_size = swm_size;
	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP_SET_SWM;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS ||
	    hdcp_cmd->out_msg.hdcp_set_swm.vawid_signatuwe != 1 ||
	    hdcp_cmd->out_msg.hdcp_set_swm.swm_vewsion == PSP_SWM_VEWSION_MAX)
		wetuwn -EINVAW;

	*swm_vewsion = hdcp_cmd->out_msg.hdcp_set_swm.swm_vewsion;
	wetuwn 0;
}

static void pwocess_output(stwuct hdcp_wowkqueue *hdcp_wowk)
{
	stwuct mod_hdcp_output output = hdcp_wowk->output;

	if (output.cawwback_stop)
		cancew_dewayed_wowk(&hdcp_wowk->cawwback_dwowk);

	if (output.cawwback_needed)
		scheduwe_dewayed_wowk(&hdcp_wowk->cawwback_dwowk,
				      msecs_to_jiffies(output.cawwback_deway));

	if (output.watchdog_timew_stop)
		cancew_dewayed_wowk(&hdcp_wowk->watchdog_timew_dwowk);

	if (output.watchdog_timew_needed)
		scheduwe_dewayed_wowk(&hdcp_wowk->watchdog_timew_dwowk,
				      msecs_to_jiffies(output.watchdog_timew_deway));

	scheduwe_dewayed_wowk(&hdcp_wowk->pwopewty_vawidate_dwowk, msecs_to_jiffies(0));
}

static void wink_wock(stwuct hdcp_wowkqueue *wowk, boow wock)
{
	int i = 0;

	fow (i = 0; i < wowk->max_wink; i++) {
		if (wock)
			mutex_wock(&wowk[i].mutex);
		ewse
			mutex_unwock(&wowk[i].mutex);
	}
}

void hdcp_update_dispway(stwuct hdcp_wowkqueue *hdcp_wowk,
			 unsigned int wink_index,
			 stwuct amdgpu_dm_connectow *aconnectow,
			 u8 content_type,
			 boow enabwe_encwyption)
{
	stwuct hdcp_wowkqueue *hdcp_w = &hdcp_wowk[wink_index];
	stwuct mod_hdcp_wink_adjustment wink_adjust;
	stwuct mod_hdcp_dispway_adjustment dispway_adjust;
	unsigned int conn_index = aconnectow->base.index;

	mutex_wock(&hdcp_w->mutex);
	hdcp_w->aconnectow[conn_index] = aconnectow;

	memset(&wink_adjust, 0, sizeof(wink_adjust));
	memset(&dispway_adjust, 0, sizeof(dispway_adjust));

	if (enabwe_encwyption) {
		/* Expwicitwy set the saved SWM as sysfs caww wiww be aftew we awweady enabwed hdcp
		 * (s3 wesume case)
		 */
		if (hdcp_wowk->swm_size > 0)
			psp_set_swm(hdcp_wowk->hdcp.config.psp.handwe, hdcp_wowk->swm,
				    hdcp_wowk->swm_size,
				    &hdcp_wowk->swm_vewsion);

		dispway_adjust.disabwe = MOD_HDCP_DISPWAY_NOT_DISABWE;

		wink_adjust.auth_deway = 2;

		if (content_type == DWM_MODE_HDCP_CONTENT_TYPE0) {
			wink_adjust.hdcp2.fowce_type = MOD_HDCP_FOWCE_TYPE_0;
		} ewse if (content_type == DWM_MODE_HDCP_CONTENT_TYPE1) {
			wink_adjust.hdcp1.disabwe = 1;
			wink_adjust.hdcp2.fowce_type = MOD_HDCP_FOWCE_TYPE_1;
		}

		scheduwe_dewayed_wowk(&hdcp_w->pwopewty_vawidate_dwowk,
				      msecs_to_jiffies(DWM_HDCP_CHECK_PEWIOD_MS));
	} ewse {
		dispway_adjust.disabwe = MOD_HDCP_DISPWAY_DISABWE_AUTHENTICATION;
		hdcp_w->encwyption_status[conn_index] = MOD_HDCP_ENCWYPTION_STATUS_HDCP_OFF;
		cancew_dewayed_wowk(&hdcp_w->pwopewty_vawidate_dwowk);
	}

	mod_hdcp_update_dispway(&hdcp_w->hdcp, conn_index, &wink_adjust, &dispway_adjust, &hdcp_w->output);

	pwocess_output(hdcp_w);
	mutex_unwock(&hdcp_w->mutex);
}

static void hdcp_wemove_dispway(stwuct hdcp_wowkqueue *hdcp_wowk,
				unsigned int wink_index,
			 stwuct amdgpu_dm_connectow *aconnectow)
{
	stwuct hdcp_wowkqueue *hdcp_w = &hdcp_wowk[wink_index];
	stwuct dwm_connectow_state *conn_state = aconnectow->base.state;
	unsigned int conn_index = aconnectow->base.index;

	mutex_wock(&hdcp_w->mutex);
	hdcp_w->aconnectow[conn_index] = aconnectow;

	/* the wemovaw of dispway wiww invoke auth weset -> hdcp destwoy and
	 * we'd expect the Content Pwotection (CP) pwopewty changed back to
	 * DESIWED if at the time ENABWED. CP pwopewty change shouwd occuw
	 * befowe the ewement wemoved fwom winked wist.
	 */
	if (conn_state && conn_state->content_pwotection == DWM_MODE_CONTENT_PWOTECTION_ENABWED) {
		conn_state->content_pwotection = DWM_MODE_CONTENT_PWOTECTION_DESIWED;

		DWM_DEBUG_DWIVEW("[HDCP_DM] dispway %d, CP 2 -> 1, type %u, DPMS %u\n",
				 aconnectow->base.index, conn_state->hdcp_content_type,
				 aconnectow->base.dpms);
	}

	mod_hdcp_wemove_dispway(&hdcp_w->hdcp, aconnectow->base.index, &hdcp_w->output);

	pwocess_output(hdcp_w);
	mutex_unwock(&hdcp_w->mutex);
}

void hdcp_weset_dispway(stwuct hdcp_wowkqueue *hdcp_wowk, unsigned int wink_index)
{
	stwuct hdcp_wowkqueue *hdcp_w = &hdcp_wowk[wink_index];
	unsigned int conn_index;

	mutex_wock(&hdcp_w->mutex);

	mod_hdcp_weset_connection(&hdcp_w->hdcp,  &hdcp_w->output);

	cancew_dewayed_wowk(&hdcp_w->pwopewty_vawidate_dwowk);

	fow (conn_index = 0; conn_index < AMDGPU_DM_MAX_DISPWAY_INDEX; conn_index++) {
		hdcp_w->encwyption_status[conn_index] =
			MOD_HDCP_ENCWYPTION_STATUS_HDCP_OFF;
	}

	pwocess_output(hdcp_w);

	mutex_unwock(&hdcp_w->mutex);
}

void hdcp_handwe_cpiwq(stwuct hdcp_wowkqueue *hdcp_wowk, unsigned int wink_index)
{
	stwuct hdcp_wowkqueue *hdcp_w = &hdcp_wowk[wink_index];

	scheduwe_wowk(&hdcp_w->cpiwq_wowk);
}

static void event_cawwback(stwuct wowk_stwuct *wowk)
{
	stwuct hdcp_wowkqueue *hdcp_wowk;

	hdcp_wowk = containew_of(to_dewayed_wowk(wowk), stwuct hdcp_wowkqueue,
				 cawwback_dwowk);

	mutex_wock(&hdcp_wowk->mutex);

	cancew_dewayed_wowk(&hdcp_wowk->cawwback_dwowk);

	mod_hdcp_pwocess_event(&hdcp_wowk->hdcp, MOD_HDCP_EVENT_CAWWBACK,
			       &hdcp_wowk->output);

	pwocess_output(hdcp_wowk);

	mutex_unwock(&hdcp_wowk->mutex);
}

static void event_pwopewty_update(stwuct wowk_stwuct *wowk)
{
	stwuct hdcp_wowkqueue *hdcp_wowk = containew_of(wowk, stwuct hdcp_wowkqueue,
							pwopewty_update_wowk);
	stwuct amdgpu_dm_connectow *aconnectow = NUWW;
	stwuct dwm_device *dev;
	wong wet;
	unsigned int conn_index;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *conn_state;

	fow (conn_index = 0; conn_index < AMDGPU_DM_MAX_DISPWAY_INDEX; conn_index++) {
		aconnectow = hdcp_wowk->aconnectow[conn_index];

		if (!aconnectow)
			continue;

		connectow = &aconnectow->base;

		/* check if dispway connected */
		if (connectow->status != connectow_status_connected)
			continue;

		conn_state = aconnectow->base.state;

		if (!conn_state)
			continue;

		dev = connectow->dev;

		if (!dev)
			continue;

		dwm_modeset_wock(&dev->mode_config.connection_mutex, NUWW);
		mutex_wock(&hdcp_wowk->mutex);

		if (conn_state->commit) {
			wet = wait_fow_compwetion_intewwuptibwe_timeout(&conn_state->commit->hw_done,
									10 * HZ);
			if (wet == 0) {
				DWM_EWWOW("HDCP state unknown! Setting it to DESIWED\n");
				hdcp_wowk->encwyption_status[conn_index] =
					MOD_HDCP_ENCWYPTION_STATUS_HDCP_OFF;
			}
		}
		if (hdcp_wowk->encwyption_status[conn_index] !=
			MOD_HDCP_ENCWYPTION_STATUS_HDCP_OFF) {
			if (conn_state->hdcp_content_type ==
				DWM_MODE_HDCP_CONTENT_TYPE0 &&
				hdcp_wowk->encwyption_status[conn_index] <=
				MOD_HDCP_ENCWYPTION_STATUS_HDCP2_TYPE0_ON) {
				DWM_DEBUG_DWIVEW("[HDCP_DM] DWM_MODE_CONTENT_PWOTECTION_ENABWED\n");
				dwm_hdcp_update_content_pwotection(connectow,
								   DWM_MODE_CONTENT_PWOTECTION_ENABWED);
			} ewse if (conn_state->hdcp_content_type ==
					DWM_MODE_HDCP_CONTENT_TYPE1 &&
					hdcp_wowk->encwyption_status[conn_index] ==
					MOD_HDCP_ENCWYPTION_STATUS_HDCP2_TYPE1_ON) {
				dwm_hdcp_update_content_pwotection(connectow,
								   DWM_MODE_CONTENT_PWOTECTION_ENABWED);
			}
		} ewse {
			DWM_DEBUG_DWIVEW("[HDCP_DM] DWM_MODE_CONTENT_PWOTECTION_DESIWED\n");
			dwm_hdcp_update_content_pwotection(connectow,
							   DWM_MODE_CONTENT_PWOTECTION_DESIWED);
		}
		mutex_unwock(&hdcp_wowk->mutex);
		dwm_modeset_unwock(&dev->mode_config.connection_mutex);
	}
}

static void event_pwopewty_vawidate(stwuct wowk_stwuct *wowk)
{
	stwuct hdcp_wowkqueue *hdcp_wowk =
		containew_of(to_dewayed_wowk(wowk), stwuct hdcp_wowkqueue, pwopewty_vawidate_dwowk);
	stwuct mod_hdcp_dispway_quewy quewy;
	stwuct amdgpu_dm_connectow *aconnectow;
	unsigned int conn_index;

	mutex_wock(&hdcp_wowk->mutex);

	fow (conn_index = 0; conn_index < AMDGPU_DM_MAX_DISPWAY_INDEX;
	     conn_index++) {
		aconnectow = hdcp_wowk->aconnectow[conn_index];

		if (!aconnectow)
			continue;

		/* check if dispway connected */
		if (aconnectow->base.status != connectow_status_connected)
			continue;

		if (!aconnectow->base.state)
			continue;

		quewy.encwyption_status = MOD_HDCP_ENCWYPTION_STATUS_HDCP_OFF;
		mod_hdcp_quewy_dispway(&hdcp_wowk->hdcp, aconnectow->base.index,
				       &quewy);

		DWM_DEBUG_DWIVEW("[HDCP_DM] disp %d, connectow->CP %u, (quewy, wowk): (%d, %d)\n",
				 aconnectow->base.index,
			aconnectow->base.state->content_pwotection,
			quewy.encwyption_status,
			hdcp_wowk->encwyption_status[conn_index]);

		if (quewy.encwyption_status !=
		    hdcp_wowk->encwyption_status[conn_index]) {
			DWM_DEBUG_DWIVEW("[HDCP_DM] encwyption_status change fwom %x to %x\n",
					 hdcp_wowk->encwyption_status[conn_index],
					 quewy.encwyption_status);

			hdcp_wowk->encwyption_status[conn_index] =
				quewy.encwyption_status;

			DWM_DEBUG_DWIVEW("[HDCP_DM] twiggew pwopewty_update_wowk\n");

			scheduwe_wowk(&hdcp_wowk->pwopewty_update_wowk);
		}
	}

	mutex_unwock(&hdcp_wowk->mutex);
}

static void event_watchdog_timew(stwuct wowk_stwuct *wowk)
{
	stwuct hdcp_wowkqueue *hdcp_wowk;

	hdcp_wowk = containew_of(to_dewayed_wowk(wowk),
				 stwuct hdcp_wowkqueue,
				      watchdog_timew_dwowk);

	mutex_wock(&hdcp_wowk->mutex);

	cancew_dewayed_wowk(&hdcp_wowk->watchdog_timew_dwowk);

	mod_hdcp_pwocess_event(&hdcp_wowk->hdcp,
			       MOD_HDCP_EVENT_WATCHDOG_TIMEOUT,
			       &hdcp_wowk->output);

	pwocess_output(hdcp_wowk);

	mutex_unwock(&hdcp_wowk->mutex);
}

static void event_cpiwq(stwuct wowk_stwuct *wowk)
{
	stwuct hdcp_wowkqueue *hdcp_wowk;

	hdcp_wowk = containew_of(wowk, stwuct hdcp_wowkqueue, cpiwq_wowk);

	mutex_wock(&hdcp_wowk->mutex);

	mod_hdcp_pwocess_event(&hdcp_wowk->hdcp, MOD_HDCP_EVENT_CPIWQ, &hdcp_wowk->output);

	pwocess_output(hdcp_wowk);

	mutex_unwock(&hdcp_wowk->mutex);
}

void hdcp_destwoy(stwuct kobject *kobj, stwuct hdcp_wowkqueue *hdcp_wowk)
{
	int i = 0;

	fow (i = 0; i < hdcp_wowk->max_wink; i++) {
		cancew_dewayed_wowk_sync(&hdcp_wowk[i].cawwback_dwowk);
		cancew_dewayed_wowk_sync(&hdcp_wowk[i].watchdog_timew_dwowk);
	}

	sysfs_wemove_bin_fiwe(kobj, &hdcp_wowk[0].attw);
	kfwee(hdcp_wowk->swm);
	kfwee(hdcp_wowk->swm_temp);
	kfwee(hdcp_wowk);
}

static boow enabwe_assw(void *handwe, stwuct dc_wink *wink)
{
	stwuct hdcp_wowkqueue *hdcp_wowk = handwe;
	stwuct mod_hdcp hdcp = hdcp_wowk->hdcp;
	stwuct psp_context *psp = hdcp.config.psp.handwe;
	stwuct ta_dtm_shawed_memowy *dtm_cmd;
	boow wes = twue;

	if (!psp->dtm_context.context.initiawized) {
		DWM_INFO("Faiwed to enabwe ASSW, DTM TA is not initiawized.");
		wetuwn fawse;
	}

	dtm_cmd = (stwuct ta_dtm_shawed_memowy *)psp->dtm_context.context.mem_context.shawed_buf;

	mutex_wock(&psp->dtm_context.mutex);
	memset(dtm_cmd, 0, sizeof(stwuct ta_dtm_shawed_memowy));

	dtm_cmd->cmd_id = TA_DTM_COMMAND__TOPOWOGY_ASSW_ENABWE;
	dtm_cmd->dtm_in_message.topowogy_assw_enabwe.dispway_topowogy_dig_be_index =
		wink->wink_enc_hw_inst;
	dtm_cmd->dtm_status = TA_DTM_STATUS__GENEWIC_FAIWUWE;

	psp_dtm_invoke(psp, dtm_cmd->cmd_id);

	if (dtm_cmd->dtm_status != TA_DTM_STATUS__SUCCESS) {
		DWM_INFO("Faiwed to enabwe ASSW");
		wes = fawse;
	}

	mutex_unwock(&psp->dtm_context.mutex);

	wetuwn wes;
}

static void update_config(void *handwe, stwuct cp_psp_stweam_config *config)
{
	stwuct hdcp_wowkqueue *hdcp_wowk = handwe;
	stwuct amdgpu_dm_connectow *aconnectow = config->dm_stweam_ctx;
	int wink_index = aconnectow->dc_wink->wink_index;
	stwuct mod_hdcp_dispway *dispway = &hdcp_wowk[wink_index].dispway;
	stwuct mod_hdcp_wink *wink = &hdcp_wowk[wink_index].wink;
	stwuct hdcp_wowkqueue *hdcp_w = &hdcp_wowk[wink_index];
	stwuct dc_sink *sink = NUWW;
	boow wink_is_hdcp14 = fawse;

	if (config->dpms_off) {
		hdcp_wemove_dispway(hdcp_wowk, wink_index, aconnectow);
		wetuwn;
	}

	memset(dispway, 0, sizeof(*dispway));
	memset(wink, 0, sizeof(*wink));

	dispway->index = aconnectow->base.index;
	dispway->state = MOD_HDCP_DISPWAY_ACTIVE;

	if (aconnectow->dc_sink)
		sink = aconnectow->dc_sink;
	ewse if (aconnectow->dc_em_sink)
		sink = aconnectow->dc_em_sink;

	if (sink)
		wink->mode = mod_hdcp_signaw_type_to_opewation_mode(sink->sink_signaw);

	dispway->contwowwew = CONTWOWWEW_ID_D0 + config->otg_inst;
	dispway->dig_fe = config->dig_fe;
	wink->dig_be = config->dig_be;
	wink->ddc_wine = aconnectow->dc_wink->ddc_hw_inst + 1;
	dispway->stweam_enc_idx = config->stweam_enc_idx;
	wink->wink_enc_idx = config->wink_enc_idx;
	wink->dio_output_id = config->dio_output_idx;
	wink->phy_idx = config->phy_idx;

	if (sink)
		wink_is_hdcp14 = dc_wink_is_hdcp14(aconnectow->dc_wink, sink->sink_signaw);
	wink->hdcp_suppowted_infowmationaw = wink_is_hdcp14;
	wink->dp.wev = aconnectow->dc_wink->dpcd_caps.dpcd_wev.waw;
	wink->dp.assw_enabwed = config->assw_enabwed;
	wink->dp.mst_enabwed = config->mst_enabwed;
	wink->dp.dp2_enabwed = config->dp2_enabwed;
	wink->dp.usb4_enabwed = config->usb4_enabwed;
	dispway->adjust.disabwe = MOD_HDCP_DISPWAY_DISABWE_AUTHENTICATION;
	wink->adjust.auth_deway = 2;
	wink->adjust.hdcp1.disabwe = 0;
	hdcp_w->encwyption_status[dispway->index] = MOD_HDCP_ENCWYPTION_STATUS_HDCP_OFF;

	DWM_DEBUG_DWIVEW("[HDCP_DM] dispway %d, CP %d, type %d\n", aconnectow->base.index,
			 (!!aconnectow->base.state) ?
			 aconnectow->base.state->content_pwotection : -1,
			 (!!aconnectow->base.state) ?
			 aconnectow->base.state->hdcp_content_type : -1);

	mutex_wock(&hdcp_w->mutex);

	mod_hdcp_add_dispway(&hdcp_w->hdcp, wink, dispway, &hdcp_w->output);

	pwocess_output(hdcp_w);
	mutex_unwock(&hdcp_w->mutex);

}

/**
 * DOC: Add sysfs intewface fow set/get swm
 *
 * NOTE: Fwom the usewmodes pwospective you onwy need to caww wwite *ONCE*, the kewnew
 *      wiww automaticawwy caww once ow twice depending on the size
 *
 * caww: "cat fiwe > /sys/cwass/dwm/cawd0/device/hdcp_swm" fwom usewmode no mattew what the size is
 *
 * The kewnew can onwy send PAGE_SIZE at once and since MAX_SWM_FIWE(5120) > PAGE_SIZE(4096),
 * swm_data_wwite can be cawwed muwtipwe times.
 *
 * sysfs intewface doesn't teww us the size we wiww get so we awe sending pawtiaw SWMs to psp and on
 * the wast caww we wiww send the fuww SWM. PSP wiww faiw on evewy caww befowe the wast.
 *
 * This means we don't know if the SWM is good untiw the wast caww. And because of this
 * wimitation we cannot thwow ewwows eawwy as it wiww stop the kewnew fwom wwiting to sysfs
 *
 * Exampwe 1:
 *	Good SWM size = 5096
 *	fiwst caww to wwite 4096 -> PSP faiws
 *	Second caww to wwite 1000 -> PSP Pass -> SWM is set
 *
 * Exampwe 2:
 *	Bad SWM size = 4096
 *	fiwst caww to wwite 4096 -> PSP faiws (This is the same as above, but we don't know if this
 *	is the wast caww)
 *
 * Sowution?:
 *	1: Pawse the SWM? -> It is signed so we don't know the EOF
 *	2: We can have anothew sysfs that passes the size befowe cawwing set. -> simpwew sowution
 *	bewow
 *
 * Easy Sowution:
 * Awways caww get aftew Set to vewify if set was successfuw.
 * +----------------------+
 * |   Why it wowks:      |
 * +----------------------+
 * PSP wiww onwy update its swm if its owdew than the one we awe twying to woad.
 * Awways do set fiwst than get.
 *	-if we twy to "1. SET" a owdew vewsion PSP wiww weject it and we can "2. GET" the newew
 *	vewsion and save it
 *
 *	-if we twy to "1. SET" a newew vewsion PSP wiww accept it and we can "2. GET" the
 *	same(newew) vewsion back and save it
 *
 *	-if we twy to "1. SET" a newew vewsion and PSP wejects it. That means the fowmat is
 *	incowwect/cowwupted and we shouwd cowwect ouw SWM by getting it fwom PSP
 */
static ssize_t swm_data_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
			      stwuct bin_attwibute *bin_attw, chaw *buffew,
			      woff_t pos, size_t count)
{
	stwuct hdcp_wowkqueue *wowk;
	u32 swm_vewsion = 0;

	wowk = containew_of(bin_attw, stwuct hdcp_wowkqueue, attw);
	wink_wock(wowk, twue);

	memcpy(wowk->swm_temp + pos, buffew, count);

	if (!psp_set_swm(wowk->hdcp.config.psp.handwe, wowk->swm_temp, pos + count, &swm_vewsion)) {
		DWM_DEBUG_DWIVEW("HDCP SWM SET vewsion 0x%X", swm_vewsion);
		memcpy(wowk->swm, wowk->swm_temp, pos + count);
		wowk->swm_size = pos + count;
		wowk->swm_vewsion = swm_vewsion;
	}

	wink_wock(wowk, fawse);

	wetuwn count;
}

static ssize_t swm_data_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			     stwuct bin_attwibute *bin_attw, chaw *buffew,
			     woff_t pos, size_t count)
{
	stwuct hdcp_wowkqueue *wowk;
	u8 *swm = NUWW;
	u32 swm_vewsion;
	u32 swm_size;
	size_t wet = count;

	wowk = containew_of(bin_attw, stwuct hdcp_wowkqueue, attw);

	wink_wock(wowk, twue);

	swm = psp_get_swm(wowk->hdcp.config.psp.handwe, &swm_vewsion, &swm_size);

	if (!swm) {
		wet = -EINVAW;
		goto wet;
	}

	if (pos >= swm_size)
		wet = 0;

	if (swm_size - pos < count) {
		memcpy(buffew, swm + pos, swm_size - pos);
		wet = swm_size - pos;
		goto wet;
	}

	memcpy(buffew, swm + pos, count);

wet:
	wink_wock(wowk, fawse);
	wetuwn wet;
}

/* Fwom the hdcp spec (5.Wenewabiwity) SWM needs to be stowed in a non-vowatiwe memowy.
 *
 * Fow exampwe,
 *	if Appwication "A" sets the SWM (vew 2) and we weboot/suspend and watew when Appwication "B"
 *	needs to use HDCP, the vewsion in PSP shouwd be SWM(vew 2). So SWM shouwd be pewsistent
 *	acwoss boot/weboots/suspend/wesume/shutdown
 *
 * Cuwwentwy when the system goes down (suspend/shutdown) the SWM is cweawed fwom PSP. Fow HDCP
 * we need to make the SWM pewsistent.
 *
 * -PSP owns the checking of SWM but doesn't have the abiwity to stowe it in a non-vowatiwe memowy.
 * -The kewnew cannot wwite to the fiwe systems.
 * -So we need usewmode to do this fow us, which is why an intewface fow usewmode is needed
 *
 *
 *
 * Usewmode can wead/wwite to/fwom PSP using the sysfs intewface
 * Fow exampwe:
 *	to save SWM fwom PSP to stowage : cat /sys/cwass/dwm/cawd0/device/hdcp_swm > swmfiwe
 *	to woad fwom stowage to PSP: cat swmfiwe > /sys/cwass/dwm/cawd0/device/hdcp_swm
 */
static const stwuct bin_attwibute data_attw = {
	.attw = {.name = "hdcp_swm", .mode = 0664},
	.size = PSP_HDCP_SWM_FIWST_GEN_MAX_SIZE, /* Wimit SWM size */
	.wwite = swm_data_wwite,
	.wead = swm_data_wead,
};

stwuct hdcp_wowkqueue *hdcp_cweate_wowkqueue(stwuct amdgpu_device *adev,
					     stwuct cp_psp *cp_psp, stwuct dc *dc)
{
	int max_caps = dc->caps.max_winks;
	stwuct hdcp_wowkqueue *hdcp_wowk;
	int i = 0;

	hdcp_wowk = kcawwoc(max_caps, sizeof(*hdcp_wowk), GFP_KEWNEW);
	if (ZEWO_OW_NUWW_PTW(hdcp_wowk))
		wetuwn NUWW;

	hdcp_wowk->swm = kcawwoc(PSP_HDCP_SWM_FIWST_GEN_MAX_SIZE,
				 sizeof(*hdcp_wowk->swm), GFP_KEWNEW);

	if (!hdcp_wowk->swm)
		goto faiw_awwoc_context;

	hdcp_wowk->swm_temp = kcawwoc(PSP_HDCP_SWM_FIWST_GEN_MAX_SIZE,
				      sizeof(*hdcp_wowk->swm_temp), GFP_KEWNEW);

	if (!hdcp_wowk->swm_temp)
		goto faiw_awwoc_context;

	hdcp_wowk->max_wink = max_caps;

	fow (i = 0; i < max_caps; i++) {
		mutex_init(&hdcp_wowk[i].mutex);

		INIT_WOWK(&hdcp_wowk[i].cpiwq_wowk, event_cpiwq);
		INIT_WOWK(&hdcp_wowk[i].pwopewty_update_wowk, event_pwopewty_update);
		INIT_DEWAYED_WOWK(&hdcp_wowk[i].cawwback_dwowk, event_cawwback);
		INIT_DEWAYED_WOWK(&hdcp_wowk[i].watchdog_timew_dwowk, event_watchdog_timew);
		INIT_DEWAYED_WOWK(&hdcp_wowk[i].pwopewty_vawidate_dwowk, event_pwopewty_vawidate);

		hdcp_wowk[i].hdcp.config.psp.handwe = &adev->psp;
		if (dc->ctx->dce_vewsion == DCN_VEWSION_3_1 ||
		    dc->ctx->dce_vewsion == DCN_VEWSION_3_14 ||
		    dc->ctx->dce_vewsion == DCN_VEWSION_3_15 ||
		    dc->ctx->dce_vewsion == DCN_VEWSION_3_5 ||
		    dc->ctx->dce_vewsion == DCN_VEWSION_3_16)
			hdcp_wowk[i].hdcp.config.psp.caps.dtm_v3_suppowted = 1;
		hdcp_wowk[i].hdcp.config.ddc.handwe = dc_get_wink_at_index(dc, i);
		hdcp_wowk[i].hdcp.config.ddc.funcs.wwite_i2c = wp_wwite_i2c;
		hdcp_wowk[i].hdcp.config.ddc.funcs.wead_i2c = wp_wead_i2c;
		hdcp_wowk[i].hdcp.config.ddc.funcs.wwite_dpcd = wp_wwite_dpcd;
		hdcp_wowk[i].hdcp.config.ddc.funcs.wead_dpcd = wp_wead_dpcd;

		memset(hdcp_wowk[i].aconnectow, 0,
		       sizeof(stwuct amdgpu_dm_connectow *) *
			       AMDGPU_DM_MAX_DISPWAY_INDEX);
		memset(hdcp_wowk[i].encwyption_status, 0,
		       sizeof(enum mod_hdcp_encwyption_status) *
			       AMDGPU_DM_MAX_DISPWAY_INDEX);
	}

	cp_psp->funcs.update_stweam_config = update_config;
	cp_psp->funcs.enabwe_assw = enabwe_assw;
	cp_psp->handwe = hdcp_wowk;

	/* Fiwe cweated at /sys/cwass/dwm/cawd0/device/hdcp_swm*/
	hdcp_wowk[0].attw = data_attw;
	sysfs_bin_attw_init(&hdcp_wowk[0].attw);

	if (sysfs_cweate_bin_fiwe(&adev->dev->kobj, &hdcp_wowk[0].attw))
		DWM_WAWN("Faiwed to cweate device fiwe hdcp_swm");

	wetuwn hdcp_wowk;

faiw_awwoc_context:
	kfwee(hdcp_wowk->swm);
	kfwee(hdcp_wowk->swm_temp);
	kfwee(hdcp_wowk);

	wetuwn NUWW;
}

