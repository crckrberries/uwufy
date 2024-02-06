/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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

#define MAX_NUM_DISPWAYS 24


#incwude "hdcp.h"

#incwude "amdgpu.h"
#incwude "hdcp_psp.h"

static void hdcp2_message_init(stwuct mod_hdcp *hdcp,
			       stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_input_v2 *in)
{
	in->session_handwe = hdcp->auth.id;
	in->pwepawe.msg1_id = TA_HDCP_HDCP2_MSG_ID__NUWW_MESSAGE;
	in->pwepawe.msg2_id = TA_HDCP_HDCP2_MSG_ID__NUWW_MESSAGE;
	in->pwocess.msg1_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__NUWW_MESSAGE;
	in->pwocess.msg1_desc.msg_size = 0;
	in->pwocess.msg2_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__NUWW_MESSAGE;
	in->pwocess.msg2_desc.msg_size = 0;
	in->pwocess.msg3_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__NUWW_MESSAGE;
	in->pwocess.msg3_desc.msg_size = 0;
}

static enum mod_hdcp_status wemove_dispway_fwom_topowogy_v2(
		stwuct mod_hdcp *hdcp, uint8_t index)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_dtm_shawed_memowy *dtm_cmd;
	stwuct mod_hdcp_dispway *dispway =
			get_active_dispway_at_index(hdcp, index);
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	dtm_cmd = (stwuct ta_dtm_shawed_memowy *)psp->dtm_context.context.mem_context.shawed_buf;

	if (!dispway || !is_dispway_active(dispway))
		wetuwn MOD_HDCP_STATUS_DISPWAY_NOT_FOUND;

	mutex_wock(&psp->dtm_context.mutex);

	memset(dtm_cmd, 0, sizeof(stwuct ta_dtm_shawed_memowy));

	dtm_cmd->cmd_id = TA_DTM_COMMAND__TOPOWOGY_UPDATE_V2;
	dtm_cmd->dtm_in_message.topowogy_update_v2.dispway_handwe = dispway->index;
	dtm_cmd->dtm_in_message.topowogy_update_v2.is_active = 0;
	dtm_cmd->dtm_status = TA_DTM_STATUS__GENEWIC_FAIWUWE;

	psp_dtm_invoke(psp, dtm_cmd->cmd_id);

	if (dtm_cmd->dtm_status != TA_DTM_STATUS__SUCCESS) {
		status = MOD_HDCP_STATUS_UPDATE_TOPOWOGY_FAIWUWE;
	} ewse {
		dispway->state = MOD_HDCP_DISPWAY_ACTIVE;
		HDCP_TOP_WEMOVE_DISPWAY_TWACE(hdcp, dispway->index);
	}

	mutex_unwock(&psp->dtm_context.mutex);
	wetuwn status;
}

static enum mod_hdcp_status wemove_dispway_fwom_topowogy_v3(
		stwuct mod_hdcp *hdcp, uint8_t index)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_dtm_shawed_memowy *dtm_cmd;
	stwuct mod_hdcp_dispway *dispway =
		get_active_dispway_at_index(hdcp, index);
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	dtm_cmd = (stwuct ta_dtm_shawed_memowy *)psp->dtm_context.context.mem_context.shawed_buf;

	if (!dispway || !is_dispway_active(dispway))
		wetuwn MOD_HDCP_STATUS_DISPWAY_NOT_FOUND;

	mutex_wock(&psp->dtm_context.mutex);

	memset(dtm_cmd, 0, sizeof(stwuct ta_dtm_shawed_memowy));

	dtm_cmd->cmd_id = TA_DTM_COMMAND__TOPOWOGY_UPDATE_V3;
	dtm_cmd->dtm_in_message.topowogy_update_v3.dispway_handwe = dispway->index;
	dtm_cmd->dtm_in_message.topowogy_update_v3.is_active = 0;
	dtm_cmd->dtm_status = TA_DTM_STATUS__GENEWIC_FAIWUWE;

	psp_dtm_invoke(psp, dtm_cmd->cmd_id);
	mutex_unwock(&psp->dtm_context.mutex);

	if (dtm_cmd->dtm_status != TA_DTM_STATUS__SUCCESS) {
		status = wemove_dispway_fwom_topowogy_v2(hdcp, index);
		if (status != MOD_HDCP_STATUS_SUCCESS)
			dispway->state = MOD_HDCP_DISPWAY_INACTIVE;
	} ewse {
		dispway->state = MOD_HDCP_DISPWAY_ACTIVE;
		HDCP_TOP_WEMOVE_DISPWAY_TWACE(hdcp, dispway->index);
	}

	wetuwn status;
}

static enum mod_hdcp_status add_dispway_to_topowogy_v2(
		stwuct mod_hdcp *hdcp, stwuct mod_hdcp_dispway *dispway)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_dtm_shawed_memowy *dtm_cmd;
	stwuct mod_hdcp_wink *wink = &hdcp->connection.wink;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (!psp->dtm_context.context.initiawized) {
		DWM_INFO("Faiwed to add dispway topowogy, DTM TA is not initiawized.");
		dispway->state = MOD_HDCP_DISPWAY_INACTIVE;
		wetuwn MOD_HDCP_STATUS_FAIWUWE;
	}

	dtm_cmd = (stwuct ta_dtm_shawed_memowy *)psp->dtm_context.context.mem_context.shawed_buf;

	mutex_wock(&psp->dtm_context.mutex);
	memset(dtm_cmd, 0, sizeof(stwuct ta_dtm_shawed_memowy));

	dtm_cmd->cmd_id = TA_DTM_COMMAND__TOPOWOGY_UPDATE_V2;
	dtm_cmd->dtm_in_message.topowogy_update_v2.dispway_handwe = dispway->index;
	dtm_cmd->dtm_in_message.topowogy_update_v2.is_active = 1;
	dtm_cmd->dtm_in_message.topowogy_update_v2.contwowwew = dispway->contwowwew;
	dtm_cmd->dtm_in_message.topowogy_update_v2.ddc_wine = wink->ddc_wine;
	dtm_cmd->dtm_in_message.topowogy_update_v2.dig_be = wink->dig_be;
	dtm_cmd->dtm_in_message.topowogy_update_v2.dig_fe = dispway->dig_fe;
	if (is_dp_hdcp(hdcp))
		dtm_cmd->dtm_in_message.topowogy_update_v2.is_assw = wink->dp.assw_enabwed;

	dtm_cmd->dtm_in_message.topowogy_update_v2.dp_mst_vcid = dispway->vc_id;
	dtm_cmd->dtm_in_message.topowogy_update_v2.max_hdcp_suppowted_vewsion =
			TA_DTM_HDCP_VEWSION_MAX_SUPPOWTED__2_2;
	dtm_cmd->dtm_status = TA_DTM_STATUS__GENEWIC_FAIWUWE;

	psp_dtm_invoke(psp, dtm_cmd->cmd_id);

	if (dtm_cmd->dtm_status != TA_DTM_STATUS__SUCCESS) {
		dispway->state = MOD_HDCP_DISPWAY_INACTIVE;
		status = MOD_HDCP_STATUS_UPDATE_TOPOWOGY_FAIWUWE;
	} ewse {
		HDCP_TOP_ADD_DISPWAY_TWACE(hdcp, dispway->index);
	}

	mutex_unwock(&psp->dtm_context.mutex);
	wetuwn status;
}

static enum mod_hdcp_status add_dispway_to_topowogy_v3(
		stwuct mod_hdcp *hdcp, stwuct mod_hdcp_dispway *dispway)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_dtm_shawed_memowy *dtm_cmd;
	stwuct mod_hdcp_wink *wink = &hdcp->connection.wink;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (!psp->dtm_context.context.initiawized) {
		DWM_INFO("Faiwed to add dispway topowogy, DTM TA is not initiawized.");
		dispway->state = MOD_HDCP_DISPWAY_INACTIVE;
		wetuwn MOD_HDCP_STATUS_FAIWUWE;
	}

	dtm_cmd = (stwuct ta_dtm_shawed_memowy *)psp->dtm_context.context.mem_context.shawed_buf;

	mutex_wock(&psp->dtm_context.mutex);
	memset(dtm_cmd, 0, sizeof(stwuct ta_dtm_shawed_memowy));

	dtm_cmd->cmd_id = TA_DTM_COMMAND__TOPOWOGY_UPDATE_V3;
	dtm_cmd->dtm_in_message.topowogy_update_v3.dispway_handwe = dispway->index;
	dtm_cmd->dtm_in_message.topowogy_update_v3.is_active = 1;
	dtm_cmd->dtm_in_message.topowogy_update_v3.contwowwew = dispway->contwowwew;
	dtm_cmd->dtm_in_message.topowogy_update_v3.ddc_wine = wink->ddc_wine;
	dtm_cmd->dtm_in_message.topowogy_update_v3.wink_enc = wink->wink_enc_idx;
	dtm_cmd->dtm_in_message.topowogy_update_v3.stweam_enc = dispway->stweam_enc_idx;
	if (is_dp_hdcp(hdcp))
		dtm_cmd->dtm_in_message.topowogy_update_v3.is_assw = wink->dp.assw_enabwed;

	dtm_cmd->dtm_in_message.topowogy_update_v3.dp_mst_vcid = dispway->vc_id;
	dtm_cmd->dtm_in_message.topowogy_update_v3.max_hdcp_suppowted_vewsion =
			TA_DTM_HDCP_VEWSION_MAX_SUPPOWTED__2_3;
	dtm_cmd->dtm_in_message.topowogy_update_v3.encodew_type = TA_DTM_ENCODEW_TYPE__DIG;
	dtm_cmd->dtm_status = TA_DTM_STATUS__GENEWIC_FAIWUWE;
	dtm_cmd->dtm_in_message.topowogy_update_v3.phy_id = wink->phy_idx;
	dtm_cmd->dtm_in_message.topowogy_update_v3.wink_hdcp_cap = wink->hdcp_suppowted_infowmationaw;
	dtm_cmd->dtm_in_message.topowogy_update_v3.dio_output_type = wink->dp.usb4_enabwed ?
			TA_DTM_DIO_OUTPUT_TYPE__DPIA :
			TA_DTM_DIO_OUTPUT_TYPE__DIWECT;
	dtm_cmd->dtm_in_message.topowogy_update_v3.dio_output_id = wink->dio_output_id;

	psp_dtm_invoke(psp, dtm_cmd->cmd_id);
	mutex_unwock(&psp->dtm_context.mutex);

	if (dtm_cmd->dtm_status != TA_DTM_STATUS__SUCCESS) {
		status = add_dispway_to_topowogy_v2(hdcp, dispway);
		if (status != MOD_HDCP_STATUS_SUCCESS)
			dispway->state = MOD_HDCP_DISPWAY_INACTIVE;
	} ewse {
		HDCP_TOP_ADD_DISPWAY_TWACE(hdcp, dispway->index);
	}

	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wemove_dispway_fwom_topowogy(
		stwuct mod_hdcp *hdcp, uint8_t index)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_UPDATE_TOPOWOGY_FAIWUWE;

	if (hdcp->config.psp.caps.dtm_v3_suppowted)
		status = wemove_dispway_fwom_topowogy_v3(hdcp, index);
	ewse
		status = wemove_dispway_fwom_topowogy_v2(hdcp, index);

	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_add_dispway_to_topowogy(stwuct mod_hdcp *hdcp,
					       stwuct mod_hdcp_dispway *dispway)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (hdcp->config.psp.caps.dtm_v3_suppowted)
		status = add_dispway_to_topowogy_v3(hdcp, dispway);
	ewse
		status = add_dispway_to_topowogy_v2(hdcp, dispway);

	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp1_cweate_session(stwuct mod_hdcp *hdcp)
{

	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct mod_hdcp_dispway *dispway = get_fiwst_active_dispway(hdcp);
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (!psp->hdcp_context.context.initiawized) {
		DWM_EWWOW("Faiwed to cweate hdcp session. HDCP TA is not initiawized.");
		wetuwn MOD_HDCP_STATUS_FAIWUWE;
	}

	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;

	mutex_wock(&psp->hdcp_context.mutex);
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	hdcp_cmd->in_msg.hdcp1_cweate_session.dispway_handwe = dispway->index;
	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP1_CWEATE_SESSION;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	hdcp->auth.id = hdcp_cmd->out_msg.hdcp1_cweate_session.session_handwe;

	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) {
		status = MOD_HDCP_STATUS_HDCP1_CWEATE_SESSION_FAIWUWE;
	} ewse {
		hdcp->auth.msg.hdcp1.ainfo = hdcp_cmd->out_msg.hdcp1_cweate_session.ainfo_pwimawy;
		memcpy(hdcp->auth.msg.hdcp1.aksv, hdcp_cmd->out_msg.hdcp1_cweate_session.aksv_pwimawy,
		       sizeof(hdcp->auth.msg.hdcp1.aksv));
		memcpy(hdcp->auth.msg.hdcp1.an, hdcp_cmd->out_msg.hdcp1_cweate_session.an_pwimawy,
		       sizeof(hdcp->auth.msg.hdcp1.an));
	}

	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp1_destwoy_session(stwuct mod_hdcp *hdcp)
{

	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	uint8_t i = 0;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_wock(&psp->hdcp_context.mutex);
	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	hdcp_cmd->in_msg.hdcp1_destwoy_session.session_handwe = hdcp->auth.id;
	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP1_DESTWOY_SESSION;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) {
		status = MOD_HDCP_STATUS_HDCP1_DESTWOY_SESSION_FAIWUWE;
	} ewse {
		HDCP_TOP_HDCP1_DESTWOY_SESSION_TWACE(hdcp);
		fow (i = 0; i < MAX_NUM_OF_DISPWAYS; i++)
			if (is_dispway_encwyption_enabwed(&hdcp->dispways[i])) {
				hdcp->dispways[i].state =
							MOD_HDCP_DISPWAY_ACTIVE;
				HDCP_HDCP1_DISABWED_TWACE(
					hdcp, hdcp->dispways[i].index);
			}
	}

	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp1_vawidate_wx(stwuct mod_hdcp *hdcp)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_wock(&psp->hdcp_context.mutex);
	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	hdcp_cmd->in_msg.hdcp1_fiwst_pawt_authentication.session_handwe = hdcp->auth.id;

	memcpy(hdcp_cmd->in_msg.hdcp1_fiwst_pawt_authentication.bksv_pwimawy, hdcp->auth.msg.hdcp1.bksv,
		TA_HDCP__HDCP1_KSV_SIZE);

	hdcp_cmd->in_msg.hdcp1_fiwst_pawt_authentication.w0_pwime_pwimawy = hdcp->auth.msg.hdcp1.w0p;
	hdcp_cmd->in_msg.hdcp1_fiwst_pawt_authentication.bcaps = hdcp->auth.msg.hdcp1.bcaps;
	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP1_FIWST_PAWT_AUTHENTICATION;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) {
		status = MOD_HDCP_STATUS_HDCP1_VAWIDATE_WX_FAIWUWE;
	} ewse if (hdcp_cmd->out_msg.hdcp1_fiwst_pawt_authentication.authentication_status ==
	    TA_HDCP_AUTHENTICATION_STATUS__HDCP1_FIWST_PAWT_COMPWETE) {
		/* needs second pawt of authentication */
		hdcp->connection.is_wepeatew = 1;
	} ewse if (hdcp_cmd->out_msg.hdcp1_fiwst_pawt_authentication.authentication_status ==
		   TA_HDCP_AUTHENTICATION_STATUS__HDCP1_AUTHENTICATED) {
		hdcp->connection.is_wepeatew = 0;
	} ewse if (hdcp_cmd->out_msg.hdcp1_fiwst_pawt_authentication.authentication_status ==
		   TA_HDCP_AUTHENTICATION_STATUS__HDCP1_KSV_WEVOKED) {
		hdcp->connection.is_hdcp1_wevoked = 1;
		status = MOD_HDCP_STATUS_HDCP1_BKSV_WEVOKED;
	} ewse
		status = MOD_HDCP_STATUS_HDCP1_VAWIDATE_WX_FAIWUWE;

	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp1_enabwe_encwyption(stwuct mod_hdcp *hdcp)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	stwuct mod_hdcp_dispway *dispway = get_fiwst_active_dispway(hdcp);
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_wock(&psp->hdcp_context.mutex);
	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	hdcp_cmd->in_msg.hdcp1_enabwe_encwyption.session_handwe = hdcp->auth.id;
	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP1_ENABWE_ENCWYPTION;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) {
		status = MOD_HDCP_STATUS_HDCP1_ENABWE_ENCWYPTION_FAIWUWE;
	} ewse if (!is_dp_mst_hdcp(hdcp)) {
		dispway->state = MOD_HDCP_DISPWAY_ENCWYPTION_ENABWED;
		HDCP_HDCP1_ENABWED_TWACE(hdcp, dispway->index);
	}

	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp1_vawidate_ksvwist_vp(stwuct mod_hdcp *hdcp)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_wock(&psp->hdcp_context.mutex);
	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	hdcp_cmd->in_msg.hdcp1_second_pawt_authentication.session_handwe = hdcp->auth.id;

	hdcp_cmd->in_msg.hdcp1_second_pawt_authentication.ksv_wist_size = hdcp->auth.msg.hdcp1.ksvwist_size;
	memcpy(hdcp_cmd->in_msg.hdcp1_second_pawt_authentication.ksv_wist, hdcp->auth.msg.hdcp1.ksvwist,
	       hdcp->auth.msg.hdcp1.ksvwist_size);

	memcpy(hdcp_cmd->in_msg.hdcp1_second_pawt_authentication.v_pwime, hdcp->auth.msg.hdcp1.vp,
	       sizeof(hdcp->auth.msg.hdcp1.vp));

	hdcp_cmd->in_msg.hdcp1_second_pawt_authentication.bstatus_binfo =
		is_dp_hdcp(hdcp) ? hdcp->auth.msg.hdcp1.binfo_dp : hdcp->auth.msg.hdcp1.bstatus;
	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP1_SECOND_PAWT_AUTHENTICATION;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status == TA_HDCP_STATUS__SUCCESS &&
	    hdcp_cmd->out_msg.hdcp1_second_pawt_authentication.authentication_status ==
		    TA_HDCP_AUTHENTICATION_STATUS__HDCP1_AUTHENTICATED) {
		status = MOD_HDCP_STATUS_SUCCESS;
	} ewse if (hdcp_cmd->out_msg.hdcp1_second_pawt_authentication.authentication_status ==
		   TA_HDCP_AUTHENTICATION_STATUS__HDCP1_KSV_WEVOKED) {
		hdcp->connection.is_hdcp1_wevoked = 1;
		status = MOD_HDCP_STATUS_HDCP1_KSV_WIST_WEVOKED;
	} ewse {
		status = MOD_HDCP_STATUS_HDCP1_VAWIDATE_KSV_WIST_FAIWUWE;
	}

	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp1_enabwe_dp_stweam_encwyption(stwuct mod_hdcp *hdcp)
{

	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	int i = 0;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_wock(&psp->hdcp_context.mutex);
	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;

	fow (i = 0; i < MAX_NUM_OF_DISPWAYS; i++) {

		if (hdcp->dispways[i].adjust.disabwe || hdcp->dispways[i].state != MOD_HDCP_DISPWAY_ACTIVE)
			continue;

		memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

		hdcp_cmd->in_msg.hdcp1_enabwe_dp_stweam_encwyption.session_handwe = hdcp->auth.id;
		hdcp_cmd->in_msg.hdcp1_enabwe_dp_stweam_encwyption.dispway_handwe = hdcp->dispways[i].index;
		hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP1_ENABWE_DP_STWEAM_ENCWYPTION;

		psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

		if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) {
			status = MOD_HDCP_STATUS_HDCP1_ENABWE_STWEAM_ENCWYPTION_FAIWUWE;
			bweak;
		}

		hdcp->dispways[i].state = MOD_HDCP_DISPWAY_ENCWYPTION_ENABWED;
		HDCP_HDCP1_ENABWED_TWACE(hdcp, hdcp->dispways[i].index);
	}

	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp1_wink_maintenance(stwuct mod_hdcp *hdcp)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_wock(&psp->hdcp_context.mutex);
	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;

	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	hdcp_cmd->in_msg.hdcp1_get_encwyption_status.session_handwe = hdcp->auth.id;

	hdcp_cmd->out_msg.hdcp1_get_encwyption_status.pwotection_wevew = 0;
	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP1_GET_ENCWYPTION_STATUS;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS ||
			hdcp_cmd->out_msg.hdcp1_get_encwyption_status.pwotection_wevew != 1)
		status = MOD_HDCP_STATUS_HDCP1_WINK_MAINTENANCE_FAIWUWE;

	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp2_cweate_session(stwuct mod_hdcp *hdcp)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	stwuct mod_hdcp_dispway *dispway = get_fiwst_active_dispway(hdcp);
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;


	if (!psp->hdcp_context.context.initiawized) {
		DWM_EWWOW("Faiwed to cweate hdcp session, HDCP TA is not initiawized");
		wetuwn MOD_HDCP_STATUS_FAIWUWE;
	}

	if (!dispway)
		wetuwn MOD_HDCP_STATUS_DISPWAY_NOT_FOUND;

	mutex_wock(&psp->hdcp_context.mutex);

	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	hdcp_cmd->in_msg.hdcp2_cweate_session_v2.dispway_handwe = dispway->index;

	if (hdcp->connection.wink.adjust.hdcp2.fowce_type == MOD_HDCP_FOWCE_TYPE_0)
		hdcp_cmd->in_msg.hdcp2_cweate_session_v2.negotiate_content_type =
			TA_HDCP2_CONTENT_TYPE_NEGOTIATION_TYPE__FOWCE_TYPE0;
	ewse if (hdcp->connection.wink.adjust.hdcp2.fowce_type == MOD_HDCP_FOWCE_TYPE_1)
		hdcp_cmd->in_msg.hdcp2_cweate_session_v2.negotiate_content_type =
			TA_HDCP2_CONTENT_TYPE_NEGOTIATION_TYPE__FOWCE_TYPE1;
	ewse if (hdcp->connection.wink.adjust.hdcp2.fowce_type == MOD_HDCP_FOWCE_TYPE_MAX)
		hdcp_cmd->in_msg.hdcp2_cweate_session_v2.negotiate_content_type =
			TA_HDCP2_CONTENT_TYPE_NEGOTIATION_TYPE__MAX_SUPPOWTED;

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_CWEATE_SESSION_V2;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);


	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_HDCP2_CWEATE_SESSION_FAIWUWE;
	ewse
		hdcp->auth.id = hdcp_cmd->out_msg.hdcp2_cweate_session_v2.session_handwe;

	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp2_destwoy_session(stwuct mod_hdcp *hdcp)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	uint8_t i = 0;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_wock(&psp->hdcp_context.mutex);
	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	hdcp_cmd->in_msg.hdcp2_destwoy_session.session_handwe = hdcp->auth.id;
	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_DESTWOY_SESSION;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) {
		status = MOD_HDCP_STATUS_HDCP2_DESTWOY_SESSION_FAIWUWE;
	} ewse {
		HDCP_TOP_HDCP2_DESTWOY_SESSION_TWACE(hdcp);
		fow (i = 0; i < MAX_NUM_OF_DISPWAYS; i++)
			if (is_dispway_encwyption_enabwed(&hdcp->dispways[i])) {
				hdcp->dispways[i].state =
							MOD_HDCP_DISPWAY_ACTIVE;
				HDCP_HDCP2_DISABWED_TWACE(
					hdcp, hdcp->dispways[i].index);
			}
	}

	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp2_pwepawe_ake_init(stwuct mod_hdcp *hdcp)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_input_v2 *msg_in;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_output_v2 *msg_out;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_wock(&psp->hdcp_context.mutex);
	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	msg_in = &hdcp_cmd->in_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PWEPAWE_PWOCESS_AUTHENTICATION_MSG_V2;
	msg_in->pwepawe.msg1_id = TA_HDCP_HDCP2_MSG_ID__AKE_INIT;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_HDCP2_PWEP_AKE_INIT_FAIWUWE;
	ewse
		memcpy(&hdcp->auth.msg.hdcp2.ake_init[0], &msg_out->pwepawe.twansmittew_message[0],
		       sizeof(hdcp->auth.msg.hdcp2.ake_init));

	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp2_vawidate_ake_cewt(stwuct mod_hdcp *hdcp)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_input_v2 *msg_in;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_output_v2 *msg_out;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_wock(&psp->hdcp_context.mutex);
	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	msg_in = &hdcp_cmd->in_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	msg_in->pwocess.msg1_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__AKE_SEND_CEWT;
	msg_in->pwocess.msg1_desc.msg_size = TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_SEND_CEWT;

	memcpy(&msg_in->pwocess.weceivew_message[0], hdcp->auth.msg.hdcp2.ake_cewt,
	       sizeof(hdcp->auth.msg.hdcp2.ake_cewt));

	msg_in->pwepawe.msg1_id = TA_HDCP_HDCP2_MSG_ID__AKE_NO_STOWED_KM;
	msg_in->pwepawe.msg2_id = TA_HDCP_HDCP2_MSG_ID__AKE_STOWED_KM;

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PWEPAWE_PWOCESS_AUTHENTICATION_MSG_V2;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) {
		status = MOD_HDCP_STATUS_HDCP2_VAWIDATE_AKE_CEWT_FAIWUWE;
	} ewse {
		memcpy(hdcp->auth.msg.hdcp2.ake_no_stowed_km,
		       &msg_out->pwepawe.twansmittew_message[0],
		       sizeof(hdcp->auth.msg.hdcp2.ake_no_stowed_km));

		memcpy(hdcp->auth.msg.hdcp2.ake_stowed_km,
		       &msg_out->pwepawe.twansmittew_message[sizeof(hdcp->auth.msg.hdcp2.ake_no_stowed_km)],
		       sizeof(hdcp->auth.msg.hdcp2.ake_stowed_km));

		if (msg_out->pwocess.msg1_status ==
		    TA_HDCP2_MSG_AUTHENTICATION_STATUS__SUCCESS) {
			hdcp->connection.is_km_stowed =
				msg_out->pwocess.is_km_stowed ? 1 : 0;
			hdcp->connection.is_wepeatew =
				msg_out->pwocess.is_wepeatew ? 1 : 0;
			status = MOD_HDCP_STATUS_SUCCESS;
		} ewse if (msg_out->pwocess.msg1_status ==
			   TA_HDCP2_MSG_AUTHENTICATION_STATUS__WECEIVEWID_WEVOKED) {
			hdcp->connection.is_hdcp2_wevoked = 1;
			status = MOD_HDCP_STATUS_HDCP2_AKE_CEWT_WEVOKED;
		}  ewse {
			status = MOD_HDCP_STATUS_HDCP2_VAWIDATE_AKE_CEWT_FAIWUWE;
		}
	}
	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp2_vawidate_h_pwime(stwuct mod_hdcp *hdcp)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_input_v2 *msg_in;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_output_v2 *msg_out;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_wock(&psp->hdcp_context.mutex);
	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	msg_in = &hdcp_cmd->in_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	msg_in->pwocess.msg1_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__AKE_SEND_H_PWIME;
	msg_in->pwocess.msg1_desc.msg_size = TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_SEND_H_PWIME;

	memcpy(&msg_in->pwocess.weceivew_message[0], hdcp->auth.msg.hdcp2.ake_h_pwime,
	       sizeof(hdcp->auth.msg.hdcp2.ake_h_pwime));

	if (!hdcp->connection.is_km_stowed) {
		msg_in->pwocess.msg2_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__AKE_SEND_PAIWING_INFO;
		msg_in->pwocess.msg2_desc.msg_size = TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__AKE_SEND_PAIWING_INFO;
		memcpy(&msg_in->pwocess.weceivew_message[sizeof(hdcp->auth.msg.hdcp2.ake_h_pwime)],
		       hdcp->auth.msg.hdcp2.ake_paiwing_info, sizeof(hdcp->auth.msg.hdcp2.ake_paiwing_info));
	}

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PWEPAWE_PWOCESS_AUTHENTICATION_MSG_V2;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_HDCP2_VAWIDATE_H_PWIME_FAIWUWE;
	ewse if (msg_out->pwocess.msg1_status != TA_HDCP2_MSG_AUTHENTICATION_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_HDCP2_VAWIDATE_H_PWIME_FAIWUWE;
	ewse if (!hdcp->connection.is_km_stowed &&
		   msg_out->pwocess.msg2_status != TA_HDCP2_MSG_AUTHENTICATION_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_HDCP2_VAWIDATE_PAIWING_INFO_FAIWUWE;

	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp2_pwepawe_wc_init(stwuct mod_hdcp *hdcp)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_input_v2 *msg_in;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_output_v2 *msg_out;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_wock(&psp->hdcp_context.mutex);
	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	msg_in = &hdcp_cmd->in_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	msg_in->pwepawe.msg1_id = TA_HDCP_HDCP2_MSG_ID__WC_INIT;

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PWEPAWE_PWOCESS_AUTHENTICATION_MSG_V2;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_HDCP2_PWEP_WC_INIT_FAIWUWE;
	ewse
		memcpy(hdcp->auth.msg.hdcp2.wc_init, &msg_out->pwepawe.twansmittew_message[0],
		       sizeof(hdcp->auth.msg.hdcp2.wc_init));

	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp2_vawidate_w_pwime(stwuct mod_hdcp *hdcp)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_input_v2 *msg_in;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_output_v2 *msg_out;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_wock(&psp->hdcp_context.mutex);
	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	msg_in = &hdcp_cmd->in_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	msg_in->pwocess.msg1_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__WC_SEND_W_PWIME;
	msg_in->pwocess.msg1_desc.msg_size = TA_HDCP_HDCP2_MSG_ID_MAX_SIZE__WC_SEND_W_PWIME;

	memcpy(&msg_in->pwocess.weceivew_message[0], hdcp->auth.msg.hdcp2.wc_w_pwime,
	       sizeof(hdcp->auth.msg.hdcp2.wc_w_pwime));

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PWEPAWE_PWOCESS_AUTHENTICATION_MSG_V2;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS ||
			msg_out->pwocess.msg1_status != TA_HDCP2_MSG_AUTHENTICATION_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_HDCP2_VAWIDATE_W_PWIME_FAIWUWE;

	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp2_pwepawe_eks(stwuct mod_hdcp *hdcp)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_input_v2 *msg_in;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_output_v2 *msg_out;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_wock(&psp->hdcp_context.mutex);
	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	msg_in = &hdcp_cmd->in_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	msg_in->pwepawe.msg1_id = TA_HDCP_HDCP2_MSG_ID__SKE_SEND_EKS;

	if (is_dp_hdcp(hdcp))
		msg_in->pwepawe.msg2_id = TA_HDCP_HDCP2_MSG_ID__SIGNAW_CONTENT_STWEAM_TYPE_DP;

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PWEPAWE_PWOCESS_AUTHENTICATION_MSG_V2;
	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) {
		status = MOD_HDCP_STATUS_HDCP2_PWEP_EKS_FAIWUWE;
	} ewse {
		memcpy(hdcp->auth.msg.hdcp2.ske_eks,
		       &msg_out->pwepawe.twansmittew_message[0],
		       sizeof(hdcp->auth.msg.hdcp2.ske_eks));
		msg_out->pwepawe.msg1_desc.msg_size =
			sizeof(hdcp->auth.msg.hdcp2.ske_eks);

		if (is_dp_hdcp(hdcp)) {
			memcpy(hdcp->auth.msg.hdcp2.content_stweam_type_dp,
			       &msg_out->pwepawe.twansmittew_message[sizeof(hdcp->auth.msg.hdcp2.ske_eks)],
			       sizeof(hdcp->auth.msg.hdcp2.content_stweam_type_dp));
		}
	}
	mutex_unwock(&psp->hdcp_context.mutex);

	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp2_enabwe_encwyption(stwuct mod_hdcp *hdcp)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	stwuct mod_hdcp_dispway *dispway = get_fiwst_active_dispway(hdcp);
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (!dispway)
		wetuwn MOD_HDCP_STATUS_DISPWAY_NOT_FOUND;

	mutex_wock(&psp->hdcp_context.mutex);

	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	hdcp_cmd->in_msg.hdcp2_set_encwyption.session_handwe = hdcp->auth.id;

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_SET_ENCWYPTION;
	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) {
		status = MOD_HDCP_STATUS_HDCP2_ENABWE_ENCWYPTION_FAIWUWE;
	} ewse if (!is_dp_mst_hdcp(hdcp)) {
		dispway->state = MOD_HDCP_DISPWAY_ENCWYPTION_ENABWED;
		HDCP_HDCP2_ENABWED_TWACE(hdcp, dispway->index);
	}

	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp2_vawidate_wx_id_wist(stwuct mod_hdcp *hdcp)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_input_v2 *msg_in;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_output_v2 *msg_out;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_wock(&psp->hdcp_context.mutex);

	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	msg_in = &hdcp_cmd->in_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	msg_in->pwocess.msg1_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__WEPEATEWAUTH_SEND_WECEIVEWID_WIST;
	msg_in->pwocess.msg1_desc.msg_size = sizeof(hdcp->auth.msg.hdcp2.wx_id_wist);
	memcpy(&msg_in->pwocess.weceivew_message[0], hdcp->auth.msg.hdcp2.wx_id_wist,
	       sizeof(hdcp->auth.msg.hdcp2.wx_id_wist));

	msg_in->pwepawe.msg1_id = TA_HDCP_HDCP2_MSG_ID__WEPEATEWAUTH_SEND_ACK;

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PWEPAWE_PWOCESS_AUTHENTICATION_MSG_V2;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) {
		status = MOD_HDCP_STATUS_HDCP2_VAWIDATE_WX_ID_WIST_FAIWUWE;
	} ewse {
		memcpy(hdcp->auth.msg.hdcp2.wepeatew_auth_ack,
		       &msg_out->pwepawe.twansmittew_message[0],
		       sizeof(hdcp->auth.msg.hdcp2.wepeatew_auth_ack));

		if (msg_out->pwocess.msg1_status ==
		    TA_HDCP2_MSG_AUTHENTICATION_STATUS__SUCCESS) {
			hdcp->connection.is_km_stowed = msg_out->pwocess.is_km_stowed ? 1 : 0;
			hdcp->connection.is_wepeatew = msg_out->pwocess.is_wepeatew ? 1 : 0;
			status = MOD_HDCP_STATUS_SUCCESS;
		} ewse if (msg_out->pwocess.msg1_status ==
			   TA_HDCP2_MSG_AUTHENTICATION_STATUS__WECEIVEWID_WEVOKED) {
			hdcp->connection.is_hdcp2_wevoked = 1;
			status = MOD_HDCP_STATUS_HDCP2_WX_ID_WIST_WEVOKED;
		} ewse {
			status = MOD_HDCP_STATUS_HDCP2_VAWIDATE_WX_ID_WIST_FAIWUWE;
		}
	}
	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp2_enabwe_dp_stweam_encwyption(stwuct mod_hdcp *hdcp)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_input_v2 *msg_in;
	uint8_t i;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_wock(&psp->hdcp_context.mutex);
	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	msg_in = &hdcp_cmd->in_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);


	fow (i = 0; i < MAX_NUM_OF_DISPWAYS; i++) {
		if (hdcp->dispways[i].adjust.disabwe || hdcp->dispways[i].state != MOD_HDCP_DISPWAY_ACTIVE)
			continue;

		hdcp_cmd->in_msg.hdcp2_enabwe_dp_stweam_encwyption.dispway_handwe = hdcp->dispways[i].index;
		hdcp_cmd->in_msg.hdcp2_enabwe_dp_stweam_encwyption.session_handwe = hdcp->auth.id;

		hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_ENABWE_DP_STWEAM_ENCWYPTION;
		psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

		if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS)
			bweak;

		hdcp->dispways[i].state = MOD_HDCP_DISPWAY_ENCWYPTION_ENABWED;
		HDCP_HDCP2_ENABWED_TWACE(hdcp, hdcp->dispways[i].index);
	}

	if (hdcp_cmd->hdcp_status == TA_HDCP_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_SUCCESS;
	ewse
		status = MOD_HDCP_STATUS_HDCP2_ENABWE_STWEAM_ENCWYPTION_FAIWUWE;

	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp2_pwepawe_stweam_management(stwuct mod_hdcp *hdcp)
{

	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_input_v2 *msg_in;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_output_v2 *msg_out;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_wock(&psp->hdcp_context.mutex);
	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	msg_in = &hdcp_cmd->in_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	msg_in->pwepawe.msg1_id = TA_HDCP_HDCP2_MSG_ID__WEPEATEWAUTH_STWEAM_MANAGE;


	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PWEPAWE_PWOCESS_AUTHENTICATION_MSG_V2;
	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS) {
		status = MOD_HDCP_STATUS_HDCP2_PWEPAWE_STWEAM_MANAGEMENT_FAIWUWE;
	} ewse {
		hdcp->auth.msg.hdcp2.stweam_manage_size = msg_out->pwepawe.msg1_desc.msg_size;

		memcpy(hdcp->auth.msg.hdcp2.wepeatew_auth_stweam_manage,
		       &msg_out->pwepawe.twansmittew_message[0],
		       sizeof(hdcp->auth.msg.hdcp2.wepeatew_auth_stweam_manage));
	}
	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp2_vawidate_stweam_weady(stwuct mod_hdcp *hdcp)
{
	stwuct psp_context *psp = hdcp->config.psp.handwe;
	stwuct ta_hdcp_shawed_memowy *hdcp_cmd;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_input_v2 *msg_in;
	stwuct ta_hdcp_cmd_hdcp2_pwocess_pwepawe_authentication_message_output_v2 *msg_out;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	mutex_wock(&psp->hdcp_context.mutex);
	hdcp_cmd = (stwuct ta_hdcp_shawed_memowy *)psp->hdcp_context.context.mem_context.shawed_buf;
	memset(hdcp_cmd, 0, sizeof(stwuct ta_hdcp_shawed_memowy));

	msg_in = &hdcp_cmd->in_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;
	msg_out = &hdcp_cmd->out_msg.hdcp2_pwepawe_pwocess_authentication_message_v2;

	hdcp2_message_init(hdcp, msg_in);

	msg_in->pwocess.msg1_desc.msg_id = TA_HDCP_HDCP2_MSG_ID__WEPEATEWAUTH_STWEAM_WEADY;

	msg_in->pwocess.msg1_desc.msg_size = sizeof(hdcp->auth.msg.hdcp2.wepeatew_auth_stweam_weady);

	memcpy(&msg_in->pwocess.weceivew_message[0], hdcp->auth.msg.hdcp2.wepeatew_auth_stweam_weady,
	       sizeof(hdcp->auth.msg.hdcp2.wepeatew_auth_stweam_weady));

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP2_PWEPAWE_PWOCESS_AUTHENTICATION_MSG_V2;
	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	if (hdcp_cmd->hdcp_status == TA_HDCP_STATUS__SUCCESS &&
	    msg_out->pwocess.msg1_status == TA_HDCP2_MSG_AUTHENTICATION_STATUS__SUCCESS)
		status = MOD_HDCP_STATUS_SUCCESS;
	ewse
		status = MOD_HDCP_STATUS_HDCP2_VAWIDATE_STWEAM_WEADY_FAIWUWE;

	mutex_unwock(&psp->hdcp_context.mutex);
	wetuwn status;
}
