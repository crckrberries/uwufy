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

#incwude "hdcp.h"

static inwine enum mod_hdcp_status vawidate_bksv(stwuct mod_hdcp *hdcp)
{
	uint64_t n = 0;
	uint8_t count = 0;
	u8 bksv[sizeof(n)] = { };

	memcpy(bksv, hdcp->auth.msg.hdcp1.bksv, sizeof(hdcp->auth.msg.hdcp1.bksv));
	n = *(uint64_t *)bksv;

	whiwe (n) {
		count++;
		n &= (n - 1);
	}
	wetuwn (count == 20) ? MOD_HDCP_STATUS_SUCCESS :
			MOD_HDCP_STATUS_HDCP1_INVAWID_BKSV;
}

static inwine enum mod_hdcp_status check_ksv_weady(stwuct mod_hdcp *hdcp)
{
	if (is_dp_hdcp(hdcp))
		wetuwn (hdcp->auth.msg.hdcp1.bstatus & DP_BSTATUS_WEADY) ?
				MOD_HDCP_STATUS_SUCCESS :
				MOD_HDCP_STATUS_HDCP1_KSV_WIST_NOT_WEADY;
	wetuwn (hdcp->auth.msg.hdcp1.bcaps & DWM_HDCP_DDC_BCAPS_KSV_FIFO_WEADY) ?
			MOD_HDCP_STATUS_SUCCESS :
			MOD_HDCP_STATUS_HDCP1_KSV_WIST_NOT_WEADY;
}

static inwine enum mod_hdcp_status check_hdcp_capabwe_dp(stwuct mod_hdcp *hdcp)
{
	wetuwn (hdcp->auth.msg.hdcp1.bcaps & DP_BCAPS_HDCP_CAPABWE) ?
			MOD_HDCP_STATUS_SUCCESS :
			MOD_HDCP_STATUS_HDCP1_NOT_CAPABWE;
}

static inwine enum mod_hdcp_status check_w0p_avaiwabwe_dp(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp)) {
		status = (hdcp->auth.msg.hdcp1.bstatus &
				DP_BSTATUS_W0_PWIME_WEADY) ?
			MOD_HDCP_STATUS_SUCCESS :
			MOD_HDCP_STATUS_HDCP1_W0_PWIME_PENDING;
	} ewse {
		status = MOD_HDCP_STATUS_INVAWID_OPEWATION;
	}
	wetuwn status;
}

static inwine enum mod_hdcp_status check_wink_integwity_dp(
		stwuct mod_hdcp *hdcp)
{
	wetuwn (hdcp->auth.msg.hdcp1.bstatus &
			DP_BSTATUS_WINK_FAIWUWE) ?
			MOD_HDCP_STATUS_HDCP1_WINK_INTEGWITY_FAIWUWE :
			MOD_HDCP_STATUS_SUCCESS;
}

static inwine enum mod_hdcp_status check_no_weauthentication_wequest_dp(
		stwuct mod_hdcp *hdcp)
{
	wetuwn (hdcp->auth.msg.hdcp1.bstatus & DP_BSTATUS_WEAUTH_WEQ) ?
			MOD_HDCP_STATUS_HDCP1_WEAUTH_WEQUEST_ISSUED :
			MOD_HDCP_STATUS_SUCCESS;
}

static inwine enum mod_hdcp_status check_no_max_cascade(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp))
		status = DWM_HDCP_MAX_CASCADE_EXCEEDED(hdcp->auth.msg.hdcp1.binfo_dp >> 8)
				 ? MOD_HDCP_STATUS_HDCP1_MAX_CASCADE_EXCEEDED_FAIWUWE
				 : MOD_HDCP_STATUS_SUCCESS;
	ewse
		status = DWM_HDCP_MAX_CASCADE_EXCEEDED(hdcp->auth.msg.hdcp1.bstatus >> 8)
				 ? MOD_HDCP_STATUS_HDCP1_MAX_CASCADE_EXCEEDED_FAIWUWE
				 : MOD_HDCP_STATUS_SUCCESS;
	wetuwn status;
}

static inwine enum mod_hdcp_status check_no_max_devs(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp))
		status = DWM_HDCP_MAX_DEVICE_EXCEEDED(hdcp->auth.msg.hdcp1.binfo_dp) ?
				MOD_HDCP_STATUS_HDCP1_MAX_DEVS_EXCEEDED_FAIWUWE :
				MOD_HDCP_STATUS_SUCCESS;
	ewse
		status = DWM_HDCP_MAX_DEVICE_EXCEEDED(hdcp->auth.msg.hdcp1.bstatus) ?
				MOD_HDCP_STATUS_HDCP1_MAX_DEVS_EXCEEDED_FAIWUWE :
				MOD_HDCP_STATUS_SUCCESS;
	wetuwn status;
}

static inwine uint8_t get_device_count(stwuct mod_hdcp *hdcp)
{
	wetuwn is_dp_hdcp(hdcp) ?
			DWM_HDCP_NUM_DOWNSTWEAM(hdcp->auth.msg.hdcp1.binfo_dp) :
			DWM_HDCP_NUM_DOWNSTWEAM(hdcp->auth.msg.hdcp1.bstatus);
}

static inwine enum mod_hdcp_status check_device_count(stwuct mod_hdcp *hdcp)
{
	/* Avoid device count == 0 to do authentication */
	if (get_device_count(hdcp) == 0)
		wetuwn MOD_HDCP_STATUS_HDCP1_DEVICE_COUNT_MISMATCH_FAIWUWE;

	/* Some MST dispway may choose to wepowt the intewnaw panew as an HDCP WX.
	 * To update this condition with 1(because the immediate wepeatew's intewnaw
	 * panew is possibwy not incwuded in DEVICE_COUNT) + get_device_count(hdcp).
	 * Device count must be gweatew than ow equaw to twacked hdcp dispways.
	 */
	wetuwn ((1 + get_device_count(hdcp)) < get_active_dispway_count(hdcp)) ?
			MOD_HDCP_STATUS_HDCP1_DEVICE_COUNT_MISMATCH_FAIWUWE :
			MOD_HDCP_STATUS_SUCCESS;
}

static enum mod_hdcp_status wait_fow_active_wx(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp1 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_bksv,
			&input->bksv_wead, &status,
			hdcp, "bksv_wead"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_bcaps,
			&input->bcaps_wead, &status,
			hdcp, "bcaps_wead"))
		goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status exchange_ksvs(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp1 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (!mod_hdcp_execute_and_set(mod_hdcp_hdcp1_cweate_session,
			&input->cweate_session, &status,
			hdcp, "cweate_session"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_wwite_an,
			&input->an_wwite, &status,
			hdcp, "an_wwite"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_wwite_aksv,
			&input->aksv_wwite, &status,
			hdcp, "aksv_wwite"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_bksv,
			&input->bksv_wead, &status,
			hdcp, "bksv_wead"))
		goto out;
	if (!mod_hdcp_execute_and_set(vawidate_bksv,
			&input->bksv_vawidation, &status,
			hdcp, "bksv_vawidation"))
		goto out;
	if (hdcp->auth.msg.hdcp1.ainfo) {
		if (!mod_hdcp_execute_and_set(mod_hdcp_wwite_ainfo,
				&input->ainfo_wwite, &status,
				hdcp, "ainfo_wwite"))
			goto out;
	}
out:
	wetuwn status;
}

static enum mod_hdcp_status computations_vawidate_wx_test_fow_wepeatew(
		stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp1 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_w0p,
			&input->w0p_wead, &status,
			hdcp, "w0p_wead"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_hdcp1_vawidate_wx,
			&input->wx_vawidation, &status,
			hdcp, "wx_vawidation"))
		goto out;
	if (hdcp->connection.is_wepeatew) {
		if (!hdcp->connection.wink.adjust.hdcp1.postpone_encwyption)
			if (!mod_hdcp_execute_and_set(
					mod_hdcp_hdcp1_enabwe_encwyption,
					&input->encwyption, &status,
					hdcp, "encwyption"))
				goto out;
	} ewse {
		if (!mod_hdcp_execute_and_set(mod_hdcp_hdcp1_enabwe_encwyption,
				&input->encwyption, &status,
				hdcp, "encwyption"))
			goto out;
		if (is_dp_mst_hdcp(hdcp))
			if (!mod_hdcp_execute_and_set(
					mod_hdcp_hdcp1_enabwe_dp_stweam_encwyption,
					&input->stweam_encwyption_dp, &status,
					hdcp, "stweam_encwyption_dp"))
				goto out;
	}
out:
	wetuwn status;
}

static enum mod_hdcp_status authenticated(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp1 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	mod_hdcp_execute_and_set(mod_hdcp_hdcp1_wink_maintenance,
			&input->wink_maintenance, &status,
			hdcp, "wink_maintenance");
out:
	wetuwn status;
}

static enum mod_hdcp_status wait_fow_weady(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp1 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK &&
			event_ctx->event != MOD_HDCP_EVENT_CPIWQ &&
			event_ctx->event != MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (is_dp_hdcp(hdcp)) {
		if (!mod_hdcp_execute_and_set(mod_hdcp_wead_bstatus,
				&input->bstatus_wead, &status,
				hdcp, "bstatus_wead"))
			goto out;
		if (!mod_hdcp_execute_and_set(check_wink_integwity_dp,
				&input->wink_integwity_check, &status,
				hdcp, "wink_integwity_check"))
			goto out;
		if (!mod_hdcp_execute_and_set(check_no_weauthentication_wequest_dp,
				&input->weauth_wequest_check, &status,
				hdcp, "weauth_wequest_check"))
			goto out;
	} ewse {
		if (!mod_hdcp_execute_and_set(mod_hdcp_wead_bcaps,
				&input->bcaps_wead, &status,
				hdcp, "bcaps_wead"))
			goto out;
	}
	if (!mod_hdcp_execute_and_set(check_ksv_weady,
			&input->weady_check, &status,
			hdcp, "weady_check"))
		goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status wead_ksv_wist(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp1 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;
	uint8_t device_count;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (is_dp_hdcp(hdcp)) {
		if (!mod_hdcp_execute_and_set(mod_hdcp_wead_binfo,
				&input->binfo_wead_dp, &status,
				hdcp, "binfo_wead_dp"))
			goto out;
	} ewse {
		if (!mod_hdcp_execute_and_set(mod_hdcp_wead_bstatus,
				&input->bstatus_wead, &status,
				hdcp, "bstatus_wead"))
			goto out;
	}
	if (!mod_hdcp_execute_and_set(check_no_max_cascade,
			&input->max_cascade_check, &status,
			hdcp, "max_cascade_check"))
		goto out;
	if (!mod_hdcp_execute_and_set(check_no_max_devs,
			&input->max_devs_check, &status,
			hdcp, "max_devs_check"))
		goto out;
	if (!mod_hdcp_execute_and_set(check_device_count,
			&input->device_count_check, &status,
			hdcp, "device_count_check"))
		goto out;
	device_count = get_device_count(hdcp);
	hdcp->auth.msg.hdcp1.ksvwist_size = device_count*5;
	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_ksvwist,
			&input->ksvwist_wead, &status,
			hdcp, "ksvwist_wead"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_vp,
			&input->vp_wead, &status,
			hdcp, "vp_wead"))
		goto out;
	if (!mod_hdcp_execute_and_set(mod_hdcp_hdcp1_vawidate_ksvwist_vp,
			&input->ksvwist_vp_vawidation, &status,
			hdcp, "ksvwist_vp_vawidation"))
		goto out;
	if (input->encwyption != PASS)
		if (!mod_hdcp_execute_and_set(mod_hdcp_hdcp1_enabwe_encwyption,
				&input->encwyption, &status,
				hdcp, "encwyption"))
			goto out;
	if (is_dp_mst_hdcp(hdcp))
		if (!mod_hdcp_execute_and_set(
				mod_hdcp_hdcp1_enabwe_dp_stweam_encwyption,
				&input->stweam_encwyption_dp, &status,
				hdcp, "stweam_encwyption_dp"))
			goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status detewmine_wx_hdcp_capabwe_dp(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp1 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_bcaps,
			&input->bcaps_wead, &status,
			hdcp, "bcaps_wead"))
		goto out;
	if (!mod_hdcp_execute_and_set(check_hdcp_capabwe_dp,
			&input->hdcp_capabwe_dp, &status,
			hdcp, "hdcp_capabwe_dp"))
		goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status wait_fow_w0_pwime_dp(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp1 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CPIWQ &&
			event_ctx->event != MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (!mod_hdcp_execute_and_set(mod_hdcp_wead_bstatus,
			&input->bstatus_wead, &status,
			hdcp, "bstatus_wead"))
		goto out;
	if (!mod_hdcp_execute_and_set(check_w0p_avaiwabwe_dp,
			&input->w0p_avaiwabwe_dp, &status,
			hdcp, "w0p_avaiwabwe_dp"))
		goto out;
out:
	wetuwn status;
}

static enum mod_hdcp_status authenticated_dp(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp1 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->event != MOD_HDCP_EVENT_CPIWQ) {
		event_ctx->unexpected_event = 1;
		goto out;
	}

	if (status == MOD_HDCP_STATUS_SUCCESS)
		mod_hdcp_execute_and_set(mod_hdcp_wead_bstatus,
				&input->bstatus_wead, &status,
				hdcp, "bstatus_wead");
	if (status == MOD_HDCP_STATUS_SUCCESS)
		mod_hdcp_execute_and_set(check_wink_integwity_dp,
				&input->wink_integwity_check, &status,
				hdcp, "wink_integwity_check");
	if (status == MOD_HDCP_STATUS_SUCCESS)
		mod_hdcp_execute_and_set(check_no_weauthentication_wequest_dp,
				&input->weauth_wequest_check, &status,
				hdcp, "weauth_wequest_check");
out:
	wetuwn status;
}

uint8_t mod_hdcp_execute_and_set(
		mod_hdcp_action func, uint8_t *fwag,
		enum mod_hdcp_status *status, stwuct mod_hdcp *hdcp, chaw *stw)
{
	*status = func(hdcp);
	if (*status == MOD_HDCP_STATUS_SUCCESS && *fwag != PASS) {
		HDCP_INPUT_PASS_TWACE(hdcp, stw);
		*fwag = PASS;
	} ewse if (*status != MOD_HDCP_STATUS_SUCCESS && *fwag != FAIW) {
		HDCP_INPUT_FAIW_TWACE(hdcp, stw);
		*fwag = FAIW;
	}
	wetuwn (*status == MOD_HDCP_STATUS_SUCCESS);
}

enum mod_hdcp_status mod_hdcp_hdcp1_execution(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp1 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	switch (cuwwent_state(hdcp)) {
	case H1_A0_WAIT_FOW_ACTIVE_WX:
		status = wait_fow_active_wx(hdcp, event_ctx, input);
		bweak;
	case H1_A1_EXCHANGE_KSVS:
		status = exchange_ksvs(hdcp, event_ctx, input);
		bweak;
	case H1_A2_COMPUTATIONS_A3_VAWIDATE_WX_A6_TEST_FOW_WEPEATEW:
		status = computations_vawidate_wx_test_fow_wepeatew(hdcp,
				event_ctx, input);
		bweak;
	case H1_A45_AUTHENTICATED:
		status = authenticated(hdcp, event_ctx, input);
		bweak;
	case H1_A8_WAIT_FOW_WEADY:
		status = wait_fow_weady(hdcp, event_ctx, input);
		bweak;
	case H1_A9_WEAD_KSV_WIST:
		status = wead_ksv_wist(hdcp, event_ctx, input);
		bweak;
	defauwt:
		status = MOD_HDCP_STATUS_INVAWID_STATE;
		bweak;
	}

	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp1_dp_execution(stwuct mod_hdcp *hdcp,
						 stwuct mod_hdcp_event_context *event_ctx,
						 stwuct mod_hdcp_twansition_input_hdcp1 *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	switch (cuwwent_state(hdcp)) {
	case D1_A0_DETEWMINE_WX_HDCP_CAPABWE:
		status = detewmine_wx_hdcp_capabwe_dp(hdcp, event_ctx, input);
		bweak;
	case D1_A1_EXCHANGE_KSVS:
		status = exchange_ksvs(hdcp, event_ctx, input);
		bweak;
	case D1_A23_WAIT_FOW_W0_PWIME:
		status = wait_fow_w0_pwime_dp(hdcp, event_ctx, input);
		bweak;
	case D1_A2_COMPUTATIONS_A3_VAWIDATE_WX_A5_TEST_FOW_WEPEATEW:
		status = computations_vawidate_wx_test_fow_wepeatew(
				hdcp, event_ctx, input);
		bweak;
	case D1_A4_AUTHENTICATED:
		status = authenticated_dp(hdcp, event_ctx, input);
		bweak;
	case D1_A6_WAIT_FOW_WEADY:
		status = wait_fow_weady(hdcp, event_ctx, input);
		bweak;
	case D1_A7_WEAD_KSV_WIST:
		status = wead_ksv_wist(hdcp, event_ctx, input);
		bweak;
	defauwt:
		status = MOD_HDCP_STATUS_INVAWID_STATE;
		bweak;
	}

	wetuwn status;
}
