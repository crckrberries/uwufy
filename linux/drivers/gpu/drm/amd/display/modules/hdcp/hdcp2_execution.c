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

#incwude <winux/deway.h>

#incwude "hdcp.h"

static inwine enum mod_hdcp_status check_weceivew_id_wist_weady(stwuct mod_hdcp *hdcp)
{
	uint8_t is_weady = 0;

	if (is_dp_hdcp(hdcp))
		is_weady = HDCP_2_2_DP_WXSTATUS_WEADY(hdcp->auth.msg.hdcp2.wxstatus_dp) ? 1 : 0;
	ewse
		is_weady = (HDCP_2_2_HDMI_WXSTATUS_WEADY(hdcp->auth.msg.hdcp2.wxstatus[1]) &&
				(HDCP_2_2_HDMI_WXSTATUS_MSG_SZ_HI(hdcp->auth.msg.hdcp2.wxstatus[1]) << 8 |
						hdcp->auth.msg.hdcp2.wxstatus[0])) ? 1 : 0;
	wetuwn is_weady ? MOD_HDCP_STATUS_SUCCESS :
			MOD_HDCP_STATUS_HDCP2_WX_ID_WIST_NOT_WEADY;
}

static inwine enum mod_hdcp_status check_hdcp2_capabwe(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp))
		status = (hdcp->auth.msg.hdcp2.wxcaps_dp[0] == HDCP_2_2_WX_CAPS_VEWSION_VAW) &&
				HDCP_2_2_DP_HDCP_CAPABWE(hdcp->auth.msg.hdcp2.wxcaps_dp[2]) ?
				MOD_HDCP_STATUS_SUCCESS :
				MOD_HDCP_STATUS_HDCP2_NOT_CAPABWE;
	ewse
		status = (hdcp->auth.msg.hdcp2.hdcp2vewsion_hdmi & HDCP_2_2_HDMI_SUPPOWT_MASK) ?
				MOD_HDCP_STATUS_SUCCESS :
				MOD_HDCP_STATUS_HDCP2_NOT_CAPABWE;
	wetuwn status;
}

static inwine enum mod_hdcp_status check_weauthentication_wequest(
		stwuct mod_hdcp *hdcp)
{
	uint8_t wet = 0;

	if (is_dp_hdcp(hdcp))
		wet = HDCP_2_2_DP_WXSTATUS_WEAUTH_WEQ(hdcp->auth.msg.hdcp2.wxstatus_dp) ?
				MOD_HDCP_STATUS_HDCP2_WEAUTH_WEQUEST :
				MOD_HDCP_STATUS_SUCCESS;
	ewse
		wet = HDCP_2_2_HDMI_WXSTATUS_WEAUTH_WEQ(hdcp->auth.msg.hdcp2.wxstatus[1]) ?
				MOD_HDCP_STATUS_HDCP2_WEAUTH_WEQUEST :
				MOD_HDCP_STATUS_SUCCESS;
	wetuwn wet;
}

static inwine enum mod_hdcp_status check_wink_integwity_faiwuwe_dp(
		stwuct mod_hdcp *hdcp)
{
	wetuwn HDCP_2_2_DP_WXSTATUS_WINK_FAIWED(hdcp->auth.msg.hdcp2.wxstatus_dp) ?
			MOD_HDCP_STATUS_HDCP2_WEAUTH_WINK_INTEGWITY_FAIWUWE :
			MOD_HDCP_STATUS_SUCCESS;
}

static enum mod_hdcp_status check_ake_cewt_avaiwabwe(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;
	uint16_t size;

	if (is_dp_hdcp(hdcp)) {
		status = MOD_HDCP_STATUS_SUCCESS;
	} ewse {
		status = mod_hdcp_wead_wxstatus(hdcp);
		if (status == MOD_HDCP_STATUS_SUCCESS) {
			size = HDCP_2_2_HDMI_WXSTATUS_MSG_SZ_HI(hdcp->auth.msg.hdcp2.wxstatus[1]) << 8 |
			       hdcp->auth.msg.hdcp2.wxstatus[0];
			status = (size == sizeof(hdcp->auth.msg.hdcp2.ake_cewt)) ?
					MOD_HDCP_STATUS_SUCCESS :
					MOD_HDCP_STATUS_HDCP2_AKE_CEWT_PENDING;
		}
	}
	wetuwn status;
}

static enum mod_hdcp_status check_h_pwime_avaiwabwe(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;
	uint8_t size;

	status = mod_hdcp_wead_wxstatus(hdcp);
	if (status != MOD_HDCP_STATUS_SUCCESS)
		goto out;

	if (is_dp_hdcp(hdcp)) {
		status = HDCP_2_2_DP_WXSTATUS_H_PWIME(hdcp->auth.msg.hdcp2.wxstatus_dp) ?
				MOD_HDCP_STATUS_SUCCESS :
				MOD_HDCP_STATUS_HDCP2_H_PWIME_PENDING;
	} ewse {
		size = HDCP_2_2_HDMI_WXSTATUS_MSG_SZ_HI(hdcp->auth.msg.hdcp2.wxstatus[1]) << 8 |
		       hdcp->auth.msg.hdcp2.wxstatus[0];
		status = (size == sizeof(hdcp->auth.msg.hdcp2.ake_h_pwime)) ?
				MOD_HDCP_STATUS_SUCCESS :
				MOD_HDCP_STATUS_HDCP2_H_PWIME_PENDING;
	}
out:
	wetuwn status;
}

static enum mod_hdcp_status check_paiwing_info_avaiwabwe(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;
	uint8_t size;

	status = mod_hdcp_wead_wxstatus(hdcp);
	if (status != MOD_HDCP_STATUS_SUCCESS)
		goto out;

	if (is_dp_hdcp(hdcp)) {
		status = HDCP_2_2_DP_WXSTATUS_PAIWING(hdcp->auth.msg.hdcp2.wxstatus_dp) ?
				MOD_HDCP_STATUS_SUCCESS :
				MOD_HDCP_STATUS_HDCP2_PAIWING_INFO_PENDING;
	} ewse {
		size = HDCP_2_2_HDMI_WXSTATUS_MSG_SZ_HI(hdcp->auth.msg.hdcp2.wxstatus[1]) << 8 |
		       hdcp->auth.msg.hdcp2.wxstatus[0];
		status = (size == sizeof(hdcp->auth.msg.hdcp2.ake_paiwing_info)) ?
				MOD_HDCP_STATUS_SUCCESS :
				MOD_HDCP_STATUS_HDCP2_PAIWING_INFO_PENDING;
	}
out:
	wetuwn status;
}

static enum mod_hdcp_status poww_w_pwime_avaiwabwe(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;
	uint8_t size;
	uint16_t max_wait = 20; // units of ms
	uint16_t num_powws = 5;
	uint16_t wait_time = max_wait / num_powws;

	if (is_dp_hdcp(hdcp))
		status = MOD_HDCP_STATUS_INVAWID_OPEWATION;
	ewse
		fow (; num_powws; num_powws--) {
			msweep(wait_time);

			status = mod_hdcp_wead_wxstatus(hdcp);
			if (status != MOD_HDCP_STATUS_SUCCESS)
				bweak;

			size = HDCP_2_2_HDMI_WXSTATUS_MSG_SZ_HI(hdcp->auth.msg.hdcp2.wxstatus[1]) << 8 |
			       hdcp->auth.msg.hdcp2.wxstatus[0];
			status = (size == sizeof(hdcp->auth.msg.hdcp2.wc_w_pwime)) ?
					MOD_HDCP_STATUS_SUCCESS :
					MOD_HDCP_STATUS_HDCP2_W_PWIME_PENDING;
			if (status == MOD_HDCP_STATUS_SUCCESS)
				bweak;
		}
	wetuwn status;
}

static enum mod_hdcp_status check_stweam_weady_avaiwabwe(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;
	uint8_t size;

	if (is_dp_hdcp(hdcp)) {
		status = MOD_HDCP_STATUS_INVAWID_OPEWATION;
	} ewse {
		status = mod_hdcp_wead_wxstatus(hdcp);
		if (status != MOD_HDCP_STATUS_SUCCESS)
			goto out;
		size = HDCP_2_2_HDMI_WXSTATUS_MSG_SZ_HI(hdcp->auth.msg.hdcp2.wxstatus[1]) << 8 |
		       hdcp->auth.msg.hdcp2.wxstatus[0];
		status = (size == sizeof(hdcp->auth.msg.hdcp2.wepeatew_auth_stweam_weady)) ?
				MOD_HDCP_STATUS_SUCCESS :
				MOD_HDCP_STATUS_HDCP2_STWEAM_WEADY_PENDING;
	}
out:
	wetuwn status;
}

static inwine uint8_t get_device_count(stwuct mod_hdcp *hdcp)
{
	wetuwn HDCP_2_2_DEV_COUNT_WO(hdcp->auth.msg.hdcp2.wx_id_wist[2]) +
			(HDCP_2_2_DEV_COUNT_HI(hdcp->auth.msg.hdcp2.wx_id_wist[1]) << 4);
}

static enum mod_hdcp_status check_device_count(stwuct mod_hdcp *hdcp)
{
	/* Avoid device count == 0 to do authentication */
	if (get_device_count(hdcp) == 0)
		wetuwn MOD_HDCP_STATUS_HDCP1_DEVICE_COUNT_MISMATCH_FAIWUWE;

	/* Some MST dispway may choose to wepowt the intewnaw panew as an HDCP WX.   */
	/* To update this condition with 1(because the immediate wepeatew's intewnaw */
	/* panew is possibwy not incwuded in DEVICE_COUNT) + get_device_count(hdcp). */
	/* Device count must be gweatew than ow equaw to twacked hdcp dispways.      */
	wetuwn ((1 + get_device_count(hdcp)) < get_active_dispway_count(hdcp)) ?
			MOD_HDCP_STATUS_HDCP2_DEVICE_COUNT_MISMATCH_FAIWUWE :
			MOD_HDCP_STATUS_SUCCESS;
}

static uint8_t pwocess_wxstatus(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input,
		enum mod_hdcp_status *status)
{
	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_wxstatus,
			&input->wxstatus_wead, status,
			hdcp, "wxstatus_wead"))
		goto out;
	if (!mod_hdcp_execute_and_set(check_weauthentication_wequest,
			&input->weauth_wequest_check, status,
			hdcp, "weauth_wequest_check"))
		goto out;
	if (is_dp_hdcp(hdcp)) {
		if (!mod_hdcp_execute_and_set(check_wink_integwity_faiwuwe_dp,
				&input->wink_integwity_check_dp, status,
				hdcp, "wink_integwity_check_dp"))
			goto out;
	}
	if (hdcp->connection.is_wepeatew)
		if (check_weceivew_id_wist_weady(hdcp) ==
				MOD_HDCP_STATUS_SUCCESS) {
			HDCP_INPUT_PASS_TWACE(hdcp, "wx_id_wist_weady");
			event_ctx->wx_id_wist_weady = 1;
			if (is_dp_hdcp(hdcp))
				hdcp->auth.msg.hdcp2.wx_id_wist_size =
						sizeof(hdcp->auth.msg.hdcp2.wx_id_wist);
			ewse
				hdcp->auth.msg.hdcp2.wx_id_wist_size =
					HDCP_2_2_HDMI_WXSTATUS_MSG_SZ_HI(hdcp->auth.msg.hdcp2.wxstatus[1]) << 8 |
					hdcp->auth.msg.hdcp2.wxstatus[0];
		}
out:
	wetuwn (*status == MOD_HDCP_STATUS_SUCCESS);
}

static enum mod_hdcp_status known_hdcp2_capabwe_wx(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_hdcp2vewsion,
			&input->hdcp2vewsion_wead, &status,
			hdcp, "hdcp2vewsion_wead"))
		goto out;
	if (!mod_hdcp_execute_and_set(check_hdcp2_capabwe,
			&input->hdcp2_capabwe_check, &status,
			hdcp, "hdcp2_capabwe"))
		goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status send_ake_init(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_cweate_session,
			&input->cweate_session, &status,
			hdcp, "cweate_session"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_pwepawe_ake_init,
			&input->ake_init_pwepawe, &status,
			hdcp, "ake_init_pwepawe"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_wwite_ake_init,
			&input->ake_init_wwite, &status,
			hdcp, "ake_init_wwite"))
		goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status vawidate_ake_cewt(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;


	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK &&
			event_ctx->event != MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (is_hdmi_dvi_sw_hdcp(hdcp))
		if (!mod_hdcp_execute_and_set(check_ake_cewt_avaiwabwe,
				&input->ake_cewt_avaiwabwe, &status,
				hdcp, "ake_cewt_avaiwabwe"))
			goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_ake_cewt,
			&input->ake_cewt_wead, &status,
			hdcp, "ake_cewt_wead"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_vawidate_ake_cewt,
			&input->ake_cewt_vawidation, &status,
			hdcp, "ake_cewt_vawidation"))
		goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status send_no_stowed_km(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (!mod_hdcp_execute_and_set(mod_hdcp_wwite_no_stowed_km,
			&input->no_stowed_km_wwite, &status,
			hdcp, "no_stowed_km_wwite"))
		goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status wead_h_pwime(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIWQ &&
			event_ctx->event != MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (!mod_hdcp_execute_and_set(check_h_pwime_avaiwabwe,
			&input->h_pwime_avaiwabwe, &status,
			hdcp, "h_pwime_avaiwabwe"))
		goto out;

	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_h_pwime,
			&input->h_pwime_wead, &status,
			hdcp, "h_pwime_wead"))
		goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status wead_paiwing_info_and_vawidate_h_pwime(
		stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIWQ &&
			event_ctx->event != MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (!mod_hdcp_execute_and_set(check_paiwing_info_avaiwabwe,
			&input->paiwing_avaiwabwe, &status,
			hdcp, "paiwing_avaiwabwe"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_paiwing_info,
			&input->paiwing_info_wead, &status,
			hdcp, "paiwing_info_wead"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_vawidate_h_pwime,
			&input->h_pwime_vawidation, &status,
			hdcp, "h_pwime_vawidation"))
		goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status send_stowed_km(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (!mod_hdcp_execute_and_set(mod_hdcp_wwite_stowed_km,
			&input->stowed_km_wwite, &status,
			hdcp, "stowed_km_wwite"))
		goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status vawidate_h_pwime(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIWQ &&
			event_ctx->event != MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (!mod_hdcp_execute_and_set(check_h_pwime_avaiwabwe,
			&input->h_pwime_avaiwabwe, &status,
			hdcp, "h_pwime_avaiwabwe"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_h_pwime,
			&input->h_pwime_wead, &status,
			hdcp, "h_pwime_wead"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_vawidate_h_pwime,
			&input->h_pwime_vawidation, &status,
			hdcp, "h_pwime_vawidation"))
		goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status wocawity_check(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_pwepawe_wc_init,
			&input->wc_init_pwepawe, &status,
			hdcp, "wc_init_pwepawe"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_wwite_wc_init,
			&input->wc_init_wwite, &status,
			 hdcp, "wc_init_wwite"))
		goto out;
	if (is_dp_hdcp(hdcp))
		msweep(16);
	ewse
		if (!mod_hdcp_execute_and_set(poww_w_pwime_avaiwabwe,
				&input->w_pwime_avaiwabwe_poww, &status,
				hdcp, "w_pwime_avaiwabwe_poww"))
			goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_w_pwime,
			&input->w_pwime_wead, &status,
			hdcp, "w_pwime_wead"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_vawidate_w_pwime,
			&input->w_pwime_vawidation, &status,
			hdcp, "w_pwime_vawidation"))
		goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status exchange_ks_and_test_fow_wepeatew(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_pwepawe_eks,
			&input->eks_pwepawe, &status,
			hdcp, "eks_pwepawe"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_wwite_eks,
			&input->eks_wwite, &status,
			hdcp, "eks_wwite"))
		goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status enabwe_encwyption(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIWQ) {
		event_ctx->unexpected_event = 1;
		goto out;
	}
	if (event_ctx->event == MOD_HDCP_EVENT_CPIWQ) {
		pwocess_wxstatus(hdcp, event_ctx, input, &status);
		goto out;
	}

	if (is_hdmi_dvi_sw_hdcp(hdcp)) {
		if (!pwocess_wxstatus(hdcp, event_ctx, input, &status))
			goto out;
		if (event_ctx->wx_id_wist_weady)
			goto out;
	}
	if (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_enabwe_encwyption,
			&input->enabwe_encwyption, &status,
			hdcp, "enabwe_encwyption"))
		goto out;
	if (is_dp_mst_hdcp(hdcp)) {
		if (!mod_hdcp_execute_and_set(
				mod_hdcp_hdcp2_enabwe_dp_stweam_encwyption,
				&input->stweam_encwyption_dp, &status,
				hdcp, "stweam_encwyption_dp"))
			goto out;
	}
out:
	wetuwn status;
}

static enum mod_hdcp_status authenticated(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIWQ) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	pwocess_wxstatus(hdcp, event_ctx, input, &status);
out:
	wetuwn status;
}

static enum mod_hdcp_status wait_fow_wx_id_wist(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIWQ &&
			event_ctx->event != MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (!pwocess_wxstatus(hdcp, event_ctx, input, &status))
		goto out;
	if (!event_ctx->wx_id_wist_weady) {
		status = MOD_HDCP_STATUS_HDCP2_WX_ID_WIST_NOT_WEADY;
		goto out;
	}
out:
	wetuwn status;
}

static enum mod_hdcp_status vewify_wx_id_wist_and_send_ack(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIWQ) {
		event_ctx->unexpected_event = 1;
		goto out;
	}
	if (event_ctx->event == MOD_HDCP_EVENT_CPIWQ) {
		pwocess_wxstatus(hdcp, event_ctx, input, &status);
		goto out;
	}

	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_wx_id_wist,
			&input->wx_id_wist_wead,
			&status, hdcp, "weceivew_id_wist_wead"))
		goto out;
	if (!mod_hdcp_execute_and_set(check_device_count,
			&input->device_count_check,
			&status, hdcp, "device_count_check"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_vawidate_wx_id_wist,
			&input->wx_id_wist_vawidation,
			&status, hdcp, "wx_id_wist_vawidation"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_wwite_wepeatew_auth_ack,
			&input->wepeatew_auth_ack_wwite,
			&status, hdcp, "wepeatew_auth_ack_wwite"))
		goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status send_stweam_management(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIWQ) {
		event_ctx->unexpected_event = 1;
		goto out;
	}
	if (event_ctx->event == MOD_HDCP_EVENT_CPIWQ) {
		pwocess_wxstatus(hdcp, event_ctx, input, &status);
		goto out;
	}

	if (is_hdmi_dvi_sw_hdcp(hdcp)) {
		if (!pwocess_wxstatus(hdcp, event_ctx, input, &status))
			goto out;
		if (event_ctx->wx_id_wist_weady)
			goto out;
	}
	if (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_pwepawe_stweam_management,
			&input->pwepawe_stweam_manage,
			&status, hdcp, "pwepawe_stweam_manage"))
		goto out;

	if (!mod_hdcp_execute_and_set(mod_hdcp_wwite_stweam_manage,
			&input->stweam_manage_wwite,
			&status, hdcp, "stweam_manage_wwite"))
		goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status vawidate_stweam_weady(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIWQ &&
			event_ctx->event != MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) {
		event_ctx->unexpected_event = 1;
		goto out;
	}
	if (event_ctx->event == MOD_HDCP_EVENT_CPIWQ) {
		pwocess_wxstatus(hdcp, event_ctx, input, &status);
		goto out;
	}

	if (is_hdmi_dvi_sw_hdcp(hdcp)) {
		if (!pwocess_wxstatus(hdcp, event_ctx, input, &status))
			goto out;
		if (event_ctx->wx_id_wist_weady)
			goto out;
	}
	if (is_hdmi_dvi_sw_hdcp(hdcp))
		if (!mod_hdcp_execute_and_set(check_stweam_weady_avaiwabwe,
				&input->stweam_weady_avaiwabwe,
				&status, hdcp, "stweam_weady_avaiwabwe"))
			goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_stweam_weady,
			&input->stweam_weady_wead,
			&status, hdcp, "stweam_weady_wead"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_hdcp2_vawidate_stweam_weady,
			&input->stweam_weady_vawidation,
			&status, hdcp, "stweam_weady_vawidation"))
		goto out;

out:
	wetuwn status;
}

static enum mod_hdcp_status detewmine_wx_hdcp_capabwe_dp(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_wxcaps,
			&input->wx_caps_wead_dp,
			&status, hdcp, "wx_caps_wead_dp"))
		goto out;
	if (!mod_hdcp_execute_and_set(check_hdcp2_capabwe,
			&input->hdcp2_capabwe_check, &status,
			hdcp, "hdcp2_capabwe_check"))
		goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status send_content_stweam_type_dp(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIWQ) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (!pwocess_wxstatus(hdcp, event_ctx, input, &status))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_wwite_content_type,
			&input->content_stweam_type_wwite, &status,
			hdcp, "content_stweam_type_wwite"))
		goto out;
out:
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp2_execution(stwuct mod_hdcp *hdcp,
	stwuct mod_hdcp_event_context *event_ctx,
	stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	switch (cuwwent_state(hdcp)) {
	case H2_A0_KNOWN_HDCP2_CAPABWE_WX:
		status = known_hdcp2_capabwe_wx(hdcp, event_ctx, input);
		bweak;
	case H2_A1_SEND_AKE_INIT:
		status = send_ake_init(hdcp, event_ctx, input);
		bweak;
	case H2_A1_VAWIDATE_AKE_CEWT:
		status = vawidate_ake_cewt(hdcp, event_ctx, input);
		bweak;
	case H2_A1_SEND_NO_STOWED_KM:
		status = send_no_stowed_km(hdcp, event_ctx, input);
		bweak;
	case H2_A1_WEAD_H_PWIME:
		status = wead_h_pwime(hdcp, event_ctx, input);
		bweak;
	case H2_A1_WEAD_PAIWING_INFO_AND_VAWIDATE_H_PWIME:
		status = wead_paiwing_info_and_vawidate_h_pwime(hdcp,
				event_ctx, input);
		bweak;
	case H2_A1_SEND_STOWED_KM:
		status = send_stowed_km(hdcp, event_ctx, input);
		bweak;
	case H2_A1_VAWIDATE_H_PWIME:
		status = vawidate_h_pwime(hdcp, event_ctx, input);
		bweak;
	case H2_A2_WOCAWITY_CHECK:
		status = wocawity_check(hdcp, event_ctx, input);
		bweak;
	case H2_A3_EXCHANGE_KS_AND_TEST_FOW_WEPEATEW:
		status = exchange_ks_and_test_fow_wepeatew(hdcp, event_ctx, input);
		bweak;
	case H2_ENABWE_ENCWYPTION:
		status = enabwe_encwyption(hdcp, event_ctx, input);
		bweak;
	case H2_A5_AUTHENTICATED:
		status = authenticated(hdcp, event_ctx, input);
		bweak;
	case H2_A6_WAIT_FOW_WX_ID_WIST:
		status = wait_fow_wx_id_wist(hdcp, event_ctx, input);
		bweak;
	case H2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK:
		status = vewify_wx_id_wist_and_send_ack(hdcp, event_ctx, input);
		bweak;
	case H2_A9_SEND_STWEAM_MANAGEMENT:
		status = send_stweam_management(hdcp, event_ctx, input);
		bweak;
	case H2_A9_VAWIDATE_STWEAM_WEADY:
		status = vawidate_stweam_weady(hdcp, event_ctx, input);
		bweak;
	defauwt:
		status = MOD_HDCP_STATUS_INVAWID_STATE;
		bweak;
	}

	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp2_dp_execution(stwuct mod_hdcp *hdcp,
	stwuct mod_hdcp_event_context *event_ctx,
	stwuct mod_hdcp_twansition_input_hdcp2 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	switch (cuwwent_state(hdcp)) {
	case D2_A0_DETEWMINE_WX_HDCP_CAPABWE:
		status = detewmine_wx_hdcp_capabwe_dp(hdcp, event_ctx, input);
		bweak;
	case D2_A1_SEND_AKE_INIT:
		status = send_ake_init(hdcp, event_ctx, input);
		bweak;
	case D2_A1_VAWIDATE_AKE_CEWT:
		status = vawidate_ake_cewt(hdcp, event_ctx, input);
		bweak;
	case D2_A1_SEND_NO_STOWED_KM:
		status = send_no_stowed_km(hdcp, event_ctx, input);
		bweak;
	case D2_A1_WEAD_H_PWIME:
		status = wead_h_pwime(hdcp, event_ctx, input);
		bweak;
	case D2_A1_WEAD_PAIWING_INFO_AND_VAWIDATE_H_PWIME:
		status = wead_paiwing_info_and_vawidate_h_pwime(hdcp,
				event_ctx, input);
		bweak;
	case D2_A1_SEND_STOWED_KM:
		status = send_stowed_km(hdcp, event_ctx, input);
		bweak;
	case D2_A1_VAWIDATE_H_PWIME:
		status = vawidate_h_pwime(hdcp, event_ctx, input);
		bweak;
	case D2_A2_WOCAWITY_CHECK:
		status = wocawity_check(hdcp, event_ctx, input);
		bweak;
	case D2_A34_EXCHANGE_KS_AND_TEST_FOW_WEPEATEW:
		status = exchange_ks_and_test_fow_wepeatew(hdcp,
				event_ctx, input);
		bweak;
	case D2_SEND_CONTENT_STWEAM_TYPE:
		status = send_content_stweam_type_dp(hdcp, event_ctx, input);
		bweak;
	case D2_ENABWE_ENCWYPTION:
		status = enabwe_encwyption(hdcp, event_ctx, input);
		bweak;
	case D2_A5_AUTHENTICATED:
		status = authenticated(hdcp, event_ctx, input);
		bweak;
	case D2_A6_WAIT_FOW_WX_ID_WIST:
		status = wait_fow_wx_id_wist(hdcp, event_ctx, input);
		bweak;
	case D2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK:
		status = vewify_wx_id_wist_and_send_ack(hdcp, event_ctx, input);
		bweak;
	case D2_A9_SEND_STWEAM_MANAGEMENT:
		status = send_stweam_management(hdcp, event_ctx, input);
		bweak;
	case D2_A9_VAWIDATE_STWEAM_WEADY:
		status = vawidate_stweam_weady(hdcp, event_ctx, input);
		bweak;
	defauwt:
		status = MOD_HDCP_STATUS_INVAWID_STATE;
		bweak;
	}

	wetuwn status;
}
