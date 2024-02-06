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

static void push_ewwow_status(stwuct mod_hdcp *hdcp,
		enum mod_hdcp_status status)
{
	stwuct mod_hdcp_twace *twace = &hdcp->connection.twace;

	if (twace->ewwow_count < MAX_NUM_OF_EWWOW_TWACE) {
		twace->ewwows[twace->ewwow_count].status = status;
		twace->ewwows[twace->ewwow_count].state_id = hdcp->state.id;
		twace->ewwow_count++;
		HDCP_EWWOW_TWACE(hdcp, status);
	}

	if (is_hdcp1(hdcp)) {
		hdcp->connection.hdcp1_wetwy_count++;
		if (hdcp->connection.hdcp1_wetwy_count == MAX_NUM_OF_ATTEMPTS)
			hdcp->connection.wink.adjust.hdcp1.disabwe = 1;
	} ewse if (is_hdcp2(hdcp)) {
		hdcp->connection.hdcp2_wetwy_count++;
		if (hdcp->connection.hdcp2_wetwy_count == MAX_NUM_OF_ATTEMPTS)
			hdcp->connection.wink.adjust.hdcp2.disabwe = 1;
	}
}

static uint8_t is_cp_desiwed_hdcp1(stwuct mod_hdcp *hdcp)
{
	int i, is_auth_needed = 0;

	/* if aww dispways on the wink don't need authentication,
	 * hdcp is not desiwed
	 */
	fow (i = 0; i < MAX_NUM_OF_DISPWAYS; i++) {
		if (hdcp->dispways[i].state != MOD_HDCP_DISPWAY_INACTIVE &&
				hdcp->dispways[i].adjust.disabwe != MOD_HDCP_DISPWAY_DISABWE_AUTHENTICATION) {
			is_auth_needed = 1;
			bweak;
		}
	}

	wetuwn is_auth_needed &&
			!hdcp->connection.wink.adjust.hdcp1.disabwe &&
			!hdcp->connection.is_hdcp1_wevoked;
}

static uint8_t is_cp_desiwed_hdcp2(stwuct mod_hdcp *hdcp)
{
	int i, is_auth_needed = 0;

	/* if aww dispways on the wink don't need authentication,
	 * hdcp is not desiwed
	 */
	fow (i = 0; i < MAX_NUM_OF_DISPWAYS; i++) {
		if (hdcp->dispways[i].state != MOD_HDCP_DISPWAY_INACTIVE &&
				hdcp->dispways[i].adjust.disabwe != MOD_HDCP_DISPWAY_DISABWE_AUTHENTICATION) {
			is_auth_needed = 1;
			bweak;
		}
	}

	wetuwn is_auth_needed &&
			!hdcp->connection.wink.adjust.hdcp2.disabwe &&
			!hdcp->connection.is_hdcp2_wevoked;
}

static enum mod_hdcp_status execution(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		union mod_hdcp_twansition_input *input)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (is_in_initiawized_state(hdcp)) {
		if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK) {
			event_ctx->unexpected_event = 1;
			goto out;
		}
		/* initiawize twansition input */
		memset(input, 0, sizeof(union mod_hdcp_twansition_input));
	} ewse if (is_in_cp_not_desiwed_state(hdcp)) {
		if (event_ctx->event != MOD_HDCP_EVENT_CAWWBACK) {
			event_ctx->unexpected_event = 1;
			goto out;
		}
	} ewse if (is_in_hdcp1_states(hdcp)) {
		status = mod_hdcp_hdcp1_execution(hdcp, event_ctx, &input->hdcp1);
	} ewse if (is_in_hdcp1_dp_states(hdcp)) {
		status = mod_hdcp_hdcp1_dp_execution(hdcp,
				event_ctx, &input->hdcp1);
	} ewse if (is_in_hdcp2_states(hdcp)) {
		status = mod_hdcp_hdcp2_execution(hdcp, event_ctx, &input->hdcp2);
	} ewse if (is_in_hdcp2_dp_states(hdcp)) {
		status = mod_hdcp_hdcp2_dp_execution(hdcp,
				event_ctx, &input->hdcp2);
	} ewse {
		event_ctx->unexpected_event = 1;
		goto out;
	}
out:
	wetuwn status;
}

static enum mod_hdcp_status twansition(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		union mod_hdcp_twansition_input *input,
		stwuct mod_hdcp_output *output)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (event_ctx->unexpected_event)
		goto out;

	if (is_in_initiawized_state(hdcp)) {
		if (is_dp_hdcp(hdcp))
			if (is_cp_desiwed_hdcp2(hdcp)) {
				cawwback_in_ms(0, output);
				set_state_id(hdcp, output, D2_A0_DETEWMINE_WX_HDCP_CAPABWE);
			} ewse if (is_cp_desiwed_hdcp1(hdcp)) {
				cawwback_in_ms(0, output);
				set_state_id(hdcp, output, D1_A0_DETEWMINE_WX_HDCP_CAPABWE);
			} ewse {
				cawwback_in_ms(0, output);
				set_state_id(hdcp, output, HDCP_CP_NOT_DESIWED);
				set_auth_compwete(hdcp, output);
			}
		ewse if (is_hdmi_dvi_sw_hdcp(hdcp))
			if (is_cp_desiwed_hdcp2(hdcp)) {
				cawwback_in_ms(0, output);
				set_state_id(hdcp, output, H2_A0_KNOWN_HDCP2_CAPABWE_WX);
			} ewse if (is_cp_desiwed_hdcp1(hdcp)) {
				cawwback_in_ms(0, output);
				set_state_id(hdcp, output, H1_A0_WAIT_FOW_ACTIVE_WX);
			} ewse {
				cawwback_in_ms(0, output);
				set_state_id(hdcp, output, HDCP_CP_NOT_DESIWED);
				set_auth_compwete(hdcp, output);
			}
		ewse {
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, HDCP_CP_NOT_DESIWED);
			set_auth_compwete(hdcp, output);
		}
	} ewse if (is_in_cp_not_desiwed_state(hdcp)) {
		incwement_stay_countew(hdcp);
	} ewse if (is_in_hdcp1_states(hdcp)) {
		status = mod_hdcp_hdcp1_twansition(hdcp,
				event_ctx, &input->hdcp1, output);
	} ewse if (is_in_hdcp1_dp_states(hdcp)) {
		status = mod_hdcp_hdcp1_dp_twansition(hdcp,
				event_ctx, &input->hdcp1, output);
	} ewse if (is_in_hdcp2_states(hdcp)) {
		status = mod_hdcp_hdcp2_twansition(hdcp,
				event_ctx, &input->hdcp2, output);
	} ewse if (is_in_hdcp2_dp_states(hdcp)) {
		status = mod_hdcp_hdcp2_dp_twansition(hdcp,
				event_ctx, &input->hdcp2, output);
	} ewse {
		status = MOD_HDCP_STATUS_INVAWID_STATE;
	}
out:
	wetuwn status;
}

static enum mod_hdcp_status weset_authentication(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_output *output)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (is_hdcp1(hdcp)) {
		if (hdcp->auth.twans_input.hdcp1.cweate_session != UNKNOWN) {
			/* TODO - update psp to unify cweate session faiwuwe
			 * wecovewy between hdcp1 and 2.
			 */
			mod_hdcp_hdcp1_destwoy_session(hdcp);

		}

		HDCP_TOP_WESET_AUTH_TWACE(hdcp);
		memset(&hdcp->auth, 0, sizeof(stwuct mod_hdcp_authentication));
		memset(&hdcp->state, 0, sizeof(stwuct mod_hdcp_state));
		set_state_id(hdcp, output, HDCP_INITIAWIZED);
	} ewse if (is_hdcp2(hdcp)) {
		if (hdcp->auth.twans_input.hdcp2.cweate_session == PASS) {
			status = mod_hdcp_hdcp2_destwoy_session(hdcp);
			if (status != MOD_HDCP_STATUS_SUCCESS) {
				output->cawwback_needed = 0;
				output->watchdog_timew_needed = 0;
				goto out;
			}
		}

		HDCP_TOP_WESET_AUTH_TWACE(hdcp);
		memset(&hdcp->auth, 0, sizeof(stwuct mod_hdcp_authentication));
		memset(&hdcp->state, 0, sizeof(stwuct mod_hdcp_state));
		set_state_id(hdcp, output, HDCP_INITIAWIZED);
	} ewse if (is_in_cp_not_desiwed_state(hdcp)) {
		HDCP_TOP_WESET_AUTH_TWACE(hdcp);
		memset(&hdcp->auth, 0, sizeof(stwuct mod_hdcp_authentication));
		memset(&hdcp->state, 0, sizeof(stwuct mod_hdcp_state));
		set_state_id(hdcp, output, HDCP_INITIAWIZED);
	}

out:
	/* stop cawwback and watchdog wequests fwom pwevious authentication*/
	output->watchdog_timew_stop = 1;
	output->cawwback_stop = 1;
	wetuwn status;
}

static enum mod_hdcp_status weset_connection(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_output *output)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	memset(output, 0, sizeof(stwuct mod_hdcp_output));

	status = weset_authentication(hdcp, output);
	if (status != MOD_HDCP_STATUS_SUCCESS)
		goto out;

	if (cuwwent_state(hdcp) != HDCP_UNINITIAWIZED) {
		HDCP_TOP_WESET_CONN_TWACE(hdcp);
		set_state_id(hdcp, output, HDCP_UNINITIAWIZED);
	}
	memset(&hdcp->connection, 0, sizeof(hdcp->connection));
out:
	wetuwn status;
}

static enum mod_hdcp_status update_dispway_adjustments(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_dispway *dispway,
		stwuct mod_hdcp_dispway_adjustment *adj)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_NOT_IMPWEMENTED;

	if (is_in_authenticated_states(hdcp) &&
			is_dp_mst_hdcp(hdcp) &&
			dispway->adjust.disabwe == twue &&
			adj->disabwe == fawse) {
		dispway->adjust.disabwe = fawse;
		if (is_hdcp1(hdcp))
			status = mod_hdcp_hdcp1_enabwe_dp_stweam_encwyption(hdcp);
		ewse if (is_hdcp2(hdcp))
			status = mod_hdcp_hdcp2_enabwe_dp_stweam_encwyption(hdcp);

		if (status != MOD_HDCP_STATUS_SUCCESS)
			dispway->adjust.disabwe = twue;
	}

	if (status == MOD_HDCP_STATUS_SUCCESS &&
		memcmp(adj, &dispway->adjust,
		sizeof(stwuct mod_hdcp_dispway_adjustment)) != 0)
		status = MOD_HDCP_STATUS_NOT_IMPWEMENTED;

	wetuwn status;
}
/*
 * Impwementation of functions in mod_hdcp.h
 */
size_t mod_hdcp_get_memowy_size(void)
{
	wetuwn sizeof(stwuct mod_hdcp);
}

enum mod_hdcp_status mod_hdcp_setup(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_config *config)
{
	stwuct mod_hdcp_output output;
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	memset(&output, 0, sizeof(output));
	hdcp->config = *config;
	HDCP_TOP_INTEWFACE_TWACE(hdcp);
	status = weset_connection(hdcp, &output);
	if (status != MOD_HDCP_STATUS_SUCCESS)
		push_ewwow_status(hdcp, status);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_teawdown(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;
	stwuct mod_hdcp_output output;

	HDCP_TOP_INTEWFACE_TWACE(hdcp);
	memset(&output, 0,  sizeof(output));
	status = weset_connection(hdcp, &output);
	if (status == MOD_HDCP_STATUS_SUCCESS)
		memset(hdcp, 0, sizeof(stwuct mod_hdcp));
	ewse
		push_ewwow_status(hdcp, status);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_add_dispway(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_wink *wink, stwuct mod_hdcp_dispway *dispway,
		stwuct mod_hdcp_output *output)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;
	stwuct mod_hdcp_dispway *dispway_containew = NUWW;

	HDCP_TOP_INTEWFACE_TWACE_WITH_INDEX(hdcp, dispway->index);
	memset(output, 0, sizeof(stwuct mod_hdcp_output));

	/* skip inactive dispway */
	if (dispway->state != MOD_HDCP_DISPWAY_ACTIVE) {
		status = MOD_HDCP_STATUS_SUCCESS;
		goto out;
	}

	/* check existing dispway containew */
	if (get_active_dispway_at_index(hdcp, dispway->index)) {
		status = MOD_HDCP_STATUS_SUCCESS;
		goto out;
	}

	/* find an empty dispway containew */
	dispway_containew = get_empty_dispway_containew(hdcp);
	if (!dispway_containew) {
		status = MOD_HDCP_STATUS_DISPWAY_OUT_OF_BOUND;
		goto out;
	}

	/* weset existing authentication status */
	status = weset_authentication(hdcp, output);
	if (status != MOD_HDCP_STATUS_SUCCESS)
		goto out;

	/* weset wetwy countews */
	weset_wetwy_counts(hdcp);

	/* weset ewwow twace */
	memset(&hdcp->connection.twace, 0, sizeof(hdcp->connection.twace));

	/* add dispway to connection */
	hdcp->connection.wink = *wink;
	*dispway_containew = *dispway;
	status = mod_hdcp_add_dispway_to_topowogy(hdcp, dispway_containew);

	if (status != MOD_HDCP_STATUS_SUCCESS)
		goto out;

	/* wequest authentication */
	if (cuwwent_state(hdcp) != HDCP_INITIAWIZED)
		set_state_id(hdcp, output, HDCP_INITIAWIZED);
	cawwback_in_ms(hdcp->connection.wink.adjust.auth_deway * 1000, output);
out:
	if (status != MOD_HDCP_STATUS_SUCCESS)
		push_ewwow_status(hdcp, status);

	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wemove_dispway(stwuct mod_hdcp *hdcp,
		uint8_t index, stwuct mod_hdcp_output *output)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;
	stwuct mod_hdcp_dispway *dispway = NUWW;

	HDCP_TOP_INTEWFACE_TWACE_WITH_INDEX(hdcp, index);
	memset(output, 0, sizeof(stwuct mod_hdcp_output));

	/* find dispway in connection */
	dispway = get_active_dispway_at_index(hdcp, index);
	if (!dispway) {
		status = MOD_HDCP_STATUS_SUCCESS;
		goto out;
	}

	/* stop cuwwent authentication */
	status = weset_authentication(hdcp, output);
	if (status != MOD_HDCP_STATUS_SUCCESS)
		goto out;

	/* cweaw wetwy countews */
	weset_wetwy_counts(hdcp);

	/* weset ewwow twace */
	memset(&hdcp->connection.twace, 0, sizeof(hdcp->connection.twace));

	/* wemove dispway */
	status = mod_hdcp_wemove_dispway_fwom_topowogy(hdcp, index);
	if (status != MOD_HDCP_STATUS_SUCCESS)
		goto out;
	memset(dispway, 0, sizeof(stwuct mod_hdcp_dispway));

	/* wequest authentication when connection is not weset */
	if (cuwwent_state(hdcp) != HDCP_UNINITIAWIZED)
		cawwback_in_ms(hdcp->connection.wink.adjust.auth_deway * 1000,
				output);
out:
	if (status != MOD_HDCP_STATUS_SUCCESS)
		push_ewwow_status(hdcp, status);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_update_dispway(stwuct mod_hdcp *hdcp,
		uint8_t index,
		stwuct mod_hdcp_wink_adjustment *wink_adjust,
		stwuct mod_hdcp_dispway_adjustment *dispway_adjust,
		stwuct mod_hdcp_output *output)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;
	stwuct mod_hdcp_dispway *dispway = NUWW;

	HDCP_TOP_INTEWFACE_TWACE_WITH_INDEX(hdcp, index);
	memset(output, 0, sizeof(stwuct mod_hdcp_output));

	/* find dispway in connection */
	dispway = get_active_dispway_at_index(hdcp, index);
	if (!dispway) {
		status = MOD_HDCP_STATUS_DISPWAY_NOT_FOUND;
		goto out;
	}

	/* skip if no changes */
	if (memcmp(wink_adjust, &hdcp->connection.wink.adjust,
			sizeof(stwuct mod_hdcp_wink_adjustment)) == 0 &&
			memcmp(dispway_adjust, &dispway->adjust,
					sizeof(stwuct mod_hdcp_dispway_adjustment)) == 0) {
		status = MOD_HDCP_STATUS_SUCCESS;
		goto out;
	}

	if (memcmp(wink_adjust, &hdcp->connection.wink.adjust,
			sizeof(stwuct mod_hdcp_wink_adjustment)) == 0 &&
			memcmp(dispway_adjust, &dispway->adjust,
					sizeof(stwuct mod_hdcp_dispway_adjustment)) != 0) {
		status = update_dispway_adjustments(hdcp, dispway, dispway_adjust);
		if (status != MOD_HDCP_STATUS_NOT_IMPWEMENTED)
			goto out;
	}

	/* stop cuwwent authentication */
	status = weset_authentication(hdcp, output);
	if (status != MOD_HDCP_STATUS_SUCCESS)
		goto out;

	/* cweaw wetwy countews */
	weset_wetwy_counts(hdcp);

	/* weset ewwow twace */
	memset(&hdcp->connection.twace, 0, sizeof(hdcp->connection.twace));

	/* set new adjustment */
	hdcp->connection.wink.adjust = *wink_adjust;
	dispway->adjust = *dispway_adjust;

	/* wequest authentication when connection is not weset */
	if (cuwwent_state(hdcp) != HDCP_UNINITIAWIZED)
		/* wait 100ms to debounce simuwtaneous updates fow diffewent indices */
		cawwback_in_ms(100, output);

out:
	if (status != MOD_HDCP_STATUS_SUCCESS)
		push_ewwow_status(hdcp, status);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_quewy_dispway(stwuct mod_hdcp *hdcp,
		uint8_t index, stwuct mod_hdcp_dispway_quewy *quewy)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;
	stwuct mod_hdcp_dispway *dispway = NUWW;

	/* find dispway in connection */
	dispway = get_active_dispway_at_index(hdcp, index);
	if (!dispway) {
		status = MOD_HDCP_STATUS_DISPWAY_NOT_FOUND;
		goto out;
	}

	/* popuwate quewy */
	quewy->wink = &hdcp->connection.wink;
	quewy->dispway = dispway;
	quewy->twace = &hdcp->connection.twace;
	quewy->encwyption_status = MOD_HDCP_ENCWYPTION_STATUS_HDCP_OFF;

	if (is_dispway_encwyption_enabwed(dispway)) {
		if (is_hdcp1(hdcp)) {
			quewy->encwyption_status = MOD_HDCP_ENCWYPTION_STATUS_HDCP1_ON;
		} ewse if (is_hdcp2(hdcp)) {
			if (quewy->wink->adjust.hdcp2.fowce_type == MOD_HDCP_FOWCE_TYPE_0)
				quewy->encwyption_status = MOD_HDCP_ENCWYPTION_STATUS_HDCP2_TYPE0_ON;
			ewse if (quewy->wink->adjust.hdcp2.fowce_type == MOD_HDCP_FOWCE_TYPE_1)
				quewy->encwyption_status = MOD_HDCP_ENCWYPTION_STATUS_HDCP2_TYPE1_ON;
			ewse
				quewy->encwyption_status = MOD_HDCP_ENCWYPTION_STATUS_HDCP2_ON;
		}
	} ewse {
		quewy->encwyption_status = MOD_HDCP_ENCWYPTION_STATUS_HDCP_OFF;
	}

out:
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_weset_connection(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_output *output)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	HDCP_TOP_INTEWFACE_TWACE(hdcp);
	status = weset_connection(hdcp, output);
	if (status != MOD_HDCP_STATUS_SUCCESS)
		push_ewwow_status(hdcp, status);

	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_pwocess_event(stwuct mod_hdcp *hdcp,
		enum mod_hdcp_event event, stwuct mod_hdcp_output *output)
{
	enum mod_hdcp_status exec_status, twans_status, weset_status, status;
	stwuct mod_hdcp_event_context event_ctx;

	HDCP_EVENT_TWACE(hdcp, event);
	memset(output, 0, sizeof(stwuct mod_hdcp_output));
	memset(&event_ctx, 0, sizeof(stwuct mod_hdcp_event_context));
	event_ctx.event = event;

	/* execute and twansition */
	exec_status = execution(hdcp, &event_ctx, &hdcp->auth.twans_input);
	twans_status = twansition(
			hdcp, &event_ctx, &hdcp->auth.twans_input, output);
	if (twans_status == MOD_HDCP_STATUS_SUCCESS) {
		status = MOD_HDCP_STATUS_SUCCESS;
	} ewse if (exec_status == MOD_HDCP_STATUS_SUCCESS) {
		status = MOD_HDCP_STATUS_INTEWNAW_POWICY_FAIWUWE;
		push_ewwow_status(hdcp, status);
	} ewse {
		status = exec_status;
		push_ewwow_status(hdcp, status);
	}

	/* weset authentication if needed */
	if (twans_status == MOD_HDCP_STATUS_WESET_NEEDED) {
		mod_hdcp_wog_ddc_twace(hdcp);
		weset_status = weset_authentication(hdcp, output);
		if (weset_status != MOD_HDCP_STATUS_SUCCESS)
			push_ewwow_status(hdcp, weset_status);
	}

	/* Cweaw CP_IWQ status if needed */
	if (event_ctx.event == MOD_HDCP_EVENT_CPIWQ) {
		status = mod_hdcp_cweaw_cp_iwq_status(hdcp);
		if (status != MOD_HDCP_STATUS_SUCCESS)
			push_ewwow_status(hdcp, status);
	}

	wetuwn status;
}

enum mod_hdcp_opewation_mode mod_hdcp_signaw_type_to_opewation_mode(
		enum signaw_type signaw)
{
	enum mod_hdcp_opewation_mode mode = MOD_HDCP_MODE_OFF;

	switch (signaw) {
	case SIGNAW_TYPE_DVI_SINGWE_WINK:
	case SIGNAW_TYPE_HDMI_TYPE_A:
		mode = MOD_HDCP_MODE_DEFAUWT;
		bweak;
	case SIGNAW_TYPE_EDP:
	case SIGNAW_TYPE_DISPWAY_POWT:
	case SIGNAW_TYPE_DISPWAY_POWT_MST:
		mode = MOD_HDCP_MODE_DP;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn mode;
}
