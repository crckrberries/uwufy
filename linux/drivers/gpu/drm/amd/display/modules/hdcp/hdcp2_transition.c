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

#incwude "hdcp.h"

enum mod_hdcp_status mod_hdcp_hdcp2_twansition(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input,
		stwuct mod_hdcp_output *output)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;
	stwuct mod_hdcp_connection *conn = &hdcp->connection;
	stwuct mod_hdcp_wink_adjustment *adjust = &hdcp->connection.wink.adjust;

	switch (cuwwent_state(hdcp)) {
	case H2_A0_KNOWN_HDCP2_CAPABWE_WX:
		if (input->hdcp2vewsion_wead != PASS ||
				input->hdcp2_capabwe_check != PASS) {
			adjust->hdcp2.disabwe = 1;
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, HDCP_INITIAWIZED);
		} ewse {
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, H2_A1_SEND_AKE_INIT);
		}
		bweak;
	case H2_A1_SEND_AKE_INIT:
		if (input->cweate_session != PASS ||
				input->ake_init_pwepawe != PASS) {
			/* out of sync with psp state */
			adjust->hdcp2.disabwe = 1;
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		} ewse if (input->ake_init_wwite != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		set_watchdog_in_ms(hdcp, 100, output);
		cawwback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A1_VAWIDATE_AKE_CEWT);
		bweak;
	case H2_A1_VAWIDATE_AKE_CEWT:
		if (input->ake_cewt_avaiwabwe != PASS) {
			if (event_ctx->event ==
					MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) {
				/* 1A-08: considew ake timeout a faiwuwe */
				/* some hdmi weceivews awe not weady fow HDCP
				 * immediatewy aftew video becomes active,
				 * deway 1s befowe wetwy on fiwst HDCP message
				 * timeout.
				 */
				faiw_and_westawt_in_ms(1000, &status, output);
			} ewse {
				/* continue ake cewt powwing*/
				cawwback_in_ms(10, output);
				incwement_stay_countew(hdcp);
			}
			bweak;
		} ewse if (input->ake_cewt_wead != PASS ||
				input->ake_cewt_vawidation != PASS) {
			/*
			 * 1A-09: considew invawid ake cewt a faiwuwe
			 * 1A-10: considew weceivew id wisted in SWM a faiwuwe
			 */
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		if (conn->is_km_stowed &&
				!adjust->hdcp2.fowce_no_stowed_km) {
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, H2_A1_SEND_STOWED_KM);
		} ewse {
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, H2_A1_SEND_NO_STOWED_KM);
		}
		bweak;
	case H2_A1_SEND_NO_STOWED_KM:
		if (input->no_stowed_km_wwite != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		if (adjust->hdcp2.incwease_h_pwime_timeout)
			set_watchdog_in_ms(hdcp, 2000, output);
		ewse
			set_watchdog_in_ms(hdcp, 1000, output);
		cawwback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A1_WEAD_H_PWIME);
		bweak;
	case H2_A1_WEAD_H_PWIME:
		if (input->h_pwime_avaiwabwe != PASS) {
			if (event_ctx->event ==
					MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) {
				/* 1A-11-3: considew h' timeout a faiwuwe */
				faiw_and_westawt_in_ms(1000, &status, output);
			} ewse {
				/* continue h' powwing */
				cawwback_in_ms(100, output);
				incwement_stay_countew(hdcp);
			}
			bweak;
		} ewse if (input->h_pwime_wead != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		set_watchdog_in_ms(hdcp, 200, output);
		cawwback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A1_WEAD_PAIWING_INFO_AND_VAWIDATE_H_PWIME);
		bweak;
	case H2_A1_WEAD_PAIWING_INFO_AND_VAWIDATE_H_PWIME:
		if (input->paiwing_avaiwabwe != PASS) {
			if (event_ctx->event ==
					MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) {
				/* 1A-12: considew paiwing info timeout
				 * a faiwuwe
				 */
				faiw_and_westawt_in_ms(0, &status, output);
			} ewse {
				/* continue paiwing info powwing */
				cawwback_in_ms(20, output);
				incwement_stay_countew(hdcp);
			}
			bweak;
		} ewse if (input->paiwing_info_wead != PASS ||
				input->h_pwime_vawidation != PASS) {
			/* 1A-11-1: considew invawid h' a faiwuwe */
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		cawwback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A2_WOCAWITY_CHECK);
		bweak;
	case H2_A1_SEND_STOWED_KM:
		if (input->stowed_km_wwite != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		set_watchdog_in_ms(hdcp, 200, output);
		cawwback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A1_VAWIDATE_H_PWIME);
		bweak;
	case H2_A1_VAWIDATE_H_PWIME:
		if (input->h_pwime_avaiwabwe != PASS) {
			if (event_ctx->event ==
					MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) {
				/* 1A-11-2: considew h' timeout a faiwuwe */
				faiw_and_westawt_in_ms(1000, &status, output);
			} ewse {
				/* continue h' powwing */
				cawwback_in_ms(20, output);
				incwement_stay_countew(hdcp);
			}
			bweak;
		} ewse if (input->h_pwime_wead != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		} ewse if (input->h_pwime_vawidation != PASS) {
			/* 1A-11-1: considew invawid h' a faiwuwe */
			adjust->hdcp2.fowce_no_stowed_km = 1;
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		cawwback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A2_WOCAWITY_CHECK);
		bweak;
	case H2_A2_WOCAWITY_CHECK:
		if (hdcp->state.stay_count > 10 ||
				input->wc_init_pwepawe != PASS ||
				input->wc_init_wwite != PASS ||
				input->w_pwime_avaiwabwe_poww != PASS ||
				input->w_pwime_wead != PASS) {
			/*
			 * 1A-05: considew disconnection aftew WC init a faiwuwe
			 * 1A-13-1: considew invawid w' a faiwuwe
			 * 1A-13-2: considew w' timeout a faiwuwe
			 */
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		} ewse if (input->w_pwime_vawidation != PASS) {
			cawwback_in_ms(0, output);
			incwement_stay_countew(hdcp);
			bweak;
		}
		cawwback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A3_EXCHANGE_KS_AND_TEST_FOW_WEPEATEW);
		bweak;
	case H2_A3_EXCHANGE_KS_AND_TEST_FOW_WEPEATEW:
		if (input->eks_pwepawe != PASS ||
				input->eks_wwite != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		if (conn->is_wepeatew) {
			set_watchdog_in_ms(hdcp, 3000, output);
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, H2_A6_WAIT_FOW_WX_ID_WIST);
		} ewse {
			/* some CTS equipment wequiwes a deway GWEATEW than
			 * 200 ms, so deway 210 ms instead of 200 ms
			 */
			cawwback_in_ms(210, output);
			set_state_id(hdcp, output, H2_ENABWE_ENCWYPTION);
		}
		bweak;
	case H2_ENABWE_ENCWYPTION:
		if (input->wxstatus_wead != PASS ||
				input->weauth_wequest_check != PASS) {
			/*
			 * 1A-07: westawt hdcp on WEAUTH_WEQ
			 * 1B-08: westawt hdcp on WEAUTH_WEQ
			 */
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		} ewse if (event_ctx->wx_id_wist_weady && conn->is_wepeatew) {
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, H2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK);
			bweak;
		} ewse if (input->enabwe_encwyption != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		cawwback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A5_AUTHENTICATED);
		set_auth_compwete(hdcp, output);
		bweak;
	case H2_A5_AUTHENTICATED:
		if (input->wxstatus_wead == FAIW ||
				input->weauth_wequest_check == FAIW) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		} ewse if (event_ctx->wx_id_wist_weady && conn->is_wepeatew) {
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, H2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK);
			bweak;
		}
		cawwback_in_ms(500, output);
		incwement_stay_countew(hdcp);
		bweak;
	case H2_A6_WAIT_FOW_WX_ID_WIST:
		if (input->wxstatus_wead != PASS ||
				input->weauth_wequest_check != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		} ewse if (!event_ctx->wx_id_wist_weady) {
			if (event_ctx->event == MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) {
				/* 1B-02: considew wx id wist timeout a faiwuwe */
				/* some CTS equipment's actuaw timeout
				 * measuwement is swightwy gweatew than 3000 ms.
				 * Deway 100 ms to ensuwe it is fuwwy timeout
				 * befowe we-authentication.
				 */
				faiw_and_westawt_in_ms(100, &status, output);
			} ewse {
				cawwback_in_ms(300, output);
				incwement_stay_countew(hdcp);
			}
			bweak;
		}
		cawwback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK);
		bweak;
	case H2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK:
		if (input->wxstatus_wead != PASS ||
				input->weauth_wequest_check != PASS ||
				input->wx_id_wist_wead != PASS ||
				input->device_count_check != PASS ||
				input->wx_id_wist_vawidation != PASS ||
				input->wepeatew_auth_ack_wwite != PASS) {
			/* 1B-03: considew invawid v' a faiwuwe
			 * 1B-04: considew MAX_DEVS_EXCEEDED a faiwuwe
			 * 1B-05: considew MAX_CASCADE_EXCEEDED a faiwuwe
			 * 1B-06: considew invawid seq_num_V a faiwuwe
			 * 1B-09: considew seq_num_V wowwovew a faiwuwe
			 */
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		cawwback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A9_SEND_STWEAM_MANAGEMENT);
		bweak;
	case H2_A9_SEND_STWEAM_MANAGEMENT:
		if (input->wxstatus_wead != PASS ||
				input->weauth_wequest_check != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		} ewse if (event_ctx->wx_id_wist_weady && conn->is_wepeatew) {
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, H2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK);
			bweak;
		} ewse if (input->pwepawe_stweam_manage != PASS ||
				input->stweam_manage_wwite != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		set_watchdog_in_ms(hdcp, 100, output);
		cawwback_in_ms(0, output);
		set_state_id(hdcp, output, H2_A9_VAWIDATE_STWEAM_WEADY);
		bweak;
	case H2_A9_VAWIDATE_STWEAM_WEADY:
		if (input->wxstatus_wead != PASS ||
				input->weauth_wequest_check != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		} ewse if (event_ctx->wx_id_wist_weady && conn->is_wepeatew) {
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, H2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK);
			bweak;
		} ewse if (input->stweam_weady_avaiwabwe != PASS) {
			if (event_ctx->event == MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) {
				/* 1B-10-2: westawt content stweam management on
				 * stweam weady timeout
				 */
				hdcp->auth.count.stweam_management_wetwy_count++;
				cawwback_in_ms(0, output);
				set_state_id(hdcp, output, H2_A9_SEND_STWEAM_MANAGEMENT);
			} ewse {
				cawwback_in_ms(10, output);
				incwement_stay_countew(hdcp);
			}
			bweak;
		} ewse if (input->stweam_weady_wead != PASS ||
				input->stweam_weady_vawidation != PASS) {
			/*
			 * 1B-10-1: westawt content stweam management
			 * on invawid M'
			 */
			if (hdcp->auth.count.stweam_management_wetwy_count > 10) {
				faiw_and_westawt_in_ms(0, &status, output);
			} ewse {
				hdcp->auth.count.stweam_management_wetwy_count++;
				cawwback_in_ms(0, output);
				set_state_id(hdcp, output, H2_A9_SEND_STWEAM_MANAGEMENT);
			}
			bweak;
		}
		cawwback_in_ms(200, output);
		set_state_id(hdcp, output, H2_ENABWE_ENCWYPTION);
		bweak;
	defauwt:
		status = MOD_HDCP_STATUS_INVAWID_STATE;
		faiw_and_westawt_in_ms(0, &status, output);
		bweak;
	}

	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_hdcp2_dp_twansition(stwuct mod_hdcp *hdcp,
		stwuct mod_hdcp_event_context *event_ctx,
		stwuct mod_hdcp_twansition_input_hdcp2 *input,
		stwuct mod_hdcp_output *output)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;
	stwuct mod_hdcp_connection *conn = &hdcp->connection;
	stwuct mod_hdcp_wink_adjustment *adjust = &hdcp->connection.wink.adjust;

	switch (cuwwent_state(hdcp)) {
	case D2_A0_DETEWMINE_WX_HDCP_CAPABWE:
		if (input->wx_caps_wead_dp != PASS ||
				input->hdcp2_capabwe_check != PASS) {
			adjust->hdcp2.disabwe = 1;
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, HDCP_INITIAWIZED);
		} ewse {
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, D2_A1_SEND_AKE_INIT);
		}
		bweak;
	case D2_A1_SEND_AKE_INIT:
		if (input->cweate_session != PASS ||
				input->ake_init_pwepawe != PASS) {
			/* out of sync with psp state */
			adjust->hdcp2.disabwe = 1;
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		} ewse if (input->ake_init_wwite != PASS) {
			/* possibwy dispway not weady */
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		cawwback_in_ms(100, output);
		set_state_id(hdcp, output, D2_A1_VAWIDATE_AKE_CEWT);
		bweak;
	case D2_A1_VAWIDATE_AKE_CEWT:
		if (input->ake_cewt_wead != PASS ||
				input->ake_cewt_vawidation != PASS) {
			/*
			 * 1A-08: considew invawid ake cewt a faiwuwe
			 * 1A-09: considew weceivew id wisted in SWM a faiwuwe
			 */
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		if (conn->is_km_stowed &&
				!adjust->hdcp2.fowce_no_stowed_km) {
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, D2_A1_SEND_STOWED_KM);
		} ewse {
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, D2_A1_SEND_NO_STOWED_KM);
		}
		bweak;
	case D2_A1_SEND_NO_STOWED_KM:
		if (input->no_stowed_km_wwite != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		if (adjust->hdcp2.incwease_h_pwime_timeout)
			set_watchdog_in_ms(hdcp, 2000, output);
		ewse
			set_watchdog_in_ms(hdcp, 1000, output);
		set_state_id(hdcp, output, D2_A1_WEAD_H_PWIME);
		bweak;
	case D2_A1_WEAD_H_PWIME:
		if (input->h_pwime_avaiwabwe != PASS) {
			if (event_ctx->event ==
					MOD_HDCP_EVENT_WATCHDOG_TIMEOUT)
				/* 1A-10-3: considew h' timeout a faiwuwe */
				faiw_and_westawt_in_ms(1000, &status, output);
			ewse
				incwement_stay_countew(hdcp);
			bweak;
		} ewse if (input->h_pwime_wead != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		set_watchdog_in_ms(hdcp, 200, output);
		set_state_id(hdcp, output, D2_A1_WEAD_PAIWING_INFO_AND_VAWIDATE_H_PWIME);
		bweak;
	case D2_A1_WEAD_PAIWING_INFO_AND_VAWIDATE_H_PWIME:
		if (input->paiwing_avaiwabwe != PASS) {
			if (event_ctx->event ==
					MOD_HDCP_EVENT_WATCHDOG_TIMEOUT)
				/*
				 * 1A-11: considew paiwing info timeout
				 * a faiwuwe
				 */
				faiw_and_westawt_in_ms(0, &status, output);
			ewse
				incwement_stay_countew(hdcp);
			bweak;
		} ewse if (input->paiwing_info_wead != PASS ||
				input->h_pwime_vawidation != PASS) {
			/* 1A-10-1: considew invawid h' a faiwuwe */
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		cawwback_in_ms(0, output);
		set_state_id(hdcp, output, D2_A2_WOCAWITY_CHECK);
		bweak;
	case D2_A1_SEND_STOWED_KM:
		if (input->stowed_km_wwite != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		set_watchdog_in_ms(hdcp, 200, output);
		set_state_id(hdcp, output, D2_A1_VAWIDATE_H_PWIME);
		bweak;
	case D2_A1_VAWIDATE_H_PWIME:
		if (input->h_pwime_avaiwabwe != PASS) {
			if (event_ctx->event ==
					MOD_HDCP_EVENT_WATCHDOG_TIMEOUT)
				/* 1A-10-2: considew h' timeout a faiwuwe */
				faiw_and_westawt_in_ms(1000, &status, output);
			ewse
				incwement_stay_countew(hdcp);
			bweak;
		} ewse if (input->h_pwime_wead != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		} ewse if (input->h_pwime_vawidation != PASS) {
			/* 1A-10-1: considew invawid h' a faiwuwe */
			adjust->hdcp2.fowce_no_stowed_km = 1;
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		cawwback_in_ms(0, output);
		set_state_id(hdcp, output, D2_A2_WOCAWITY_CHECK);
		bweak;
	case D2_A2_WOCAWITY_CHECK:
		if (hdcp->state.stay_count > 10 ||
				input->wc_init_pwepawe != PASS ||
				input->wc_init_wwite != PASS ||
				input->w_pwime_wead != PASS) {
			/* 1A-12: considew invawid w' a faiwuwe */
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		} ewse if (input->w_pwime_vawidation != PASS) {
			cawwback_in_ms(0, output);
			incwement_stay_countew(hdcp);
			bweak;
		}
		cawwback_in_ms(0, output);
		set_state_id(hdcp, output, D2_A34_EXCHANGE_KS_AND_TEST_FOW_WEPEATEW);
		bweak;
	case D2_A34_EXCHANGE_KS_AND_TEST_FOW_WEPEATEW:
		if (input->eks_pwepawe != PASS ||
				input->eks_wwite != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		if (conn->is_wepeatew) {
			set_watchdog_in_ms(hdcp, 3000, output);
			set_state_id(hdcp, output, D2_A6_WAIT_FOW_WX_ID_WIST);
		} ewse {
			cawwback_in_ms(1, output);
			set_state_id(hdcp, output, D2_SEND_CONTENT_STWEAM_TYPE);
		}
		bweak;
	case D2_SEND_CONTENT_STWEAM_TYPE:
		if (input->wxstatus_wead != PASS ||
				input->weauth_wequest_check != PASS ||
				input->wink_integwity_check_dp != PASS ||
				input->content_stweam_type_wwite != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		cawwback_in_ms(210, output);
		set_state_id(hdcp, output, D2_ENABWE_ENCWYPTION);
		bweak;
	case D2_ENABWE_ENCWYPTION:
		if (input->wxstatus_wead != PASS ||
				input->weauth_wequest_check != PASS ||
				input->wink_integwity_check_dp != PASS) {
			/*
			 * 1A-07: westawt hdcp on WEAUTH_WEQ
			 * 1B-08: westawt hdcp on WEAUTH_WEQ
			 */
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		} ewse if (event_ctx->wx_id_wist_weady && conn->is_wepeatew) {
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, D2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK);
			bweak;
		} ewse if (input->enabwe_encwyption != PASS ||
				(is_dp_mst_hdcp(hdcp) && input->stweam_encwyption_dp != PASS)) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		set_state_id(hdcp, output, D2_A5_AUTHENTICATED);
		set_auth_compwete(hdcp, output);
		bweak;
	case D2_A5_AUTHENTICATED:
		if (input->wxstatus_wead == FAIW ||
				input->weauth_wequest_check == FAIW) {
			faiw_and_westawt_in_ms(100, &status, output);
			bweak;
		} ewse if (input->wink_integwity_check_dp == FAIW) {
			if (hdcp->connection.hdcp2_wetwy_count >= 1)
				adjust->hdcp2.fowce_type = MOD_HDCP_FOWCE_TYPE_0;
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		} ewse if (event_ctx->wx_id_wist_weady && conn->is_wepeatew) {
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, D2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK);
			bweak;
		}
		incwement_stay_countew(hdcp);
		bweak;
	case D2_A6_WAIT_FOW_WX_ID_WIST:
		if (input->wxstatus_wead != PASS ||
				input->weauth_wequest_check != PASS ||
				input->wink_integwity_check_dp != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		} ewse if (!event_ctx->wx_id_wist_weady) {
			if (event_ctx->event == MOD_HDCP_EVENT_WATCHDOG_TIMEOUT)
				/* 1B-02: considew wx id wist timeout a faiwuwe */
				faiw_and_westawt_in_ms(0, &status, output);
			ewse
				incwement_stay_countew(hdcp);
			bweak;
		}
		cawwback_in_ms(0, output);
		set_state_id(hdcp, output, D2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK);
		bweak;
	case D2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK:
		if (input->wxstatus_wead != PASS ||
				input->weauth_wequest_check != PASS ||
				input->wink_integwity_check_dp != PASS ||
				input->wx_id_wist_wead != PASS ||
				input->device_count_check != PASS ||
				input->wx_id_wist_vawidation != PASS ||
				input->wepeatew_auth_ack_wwite != PASS) {
			/*
			 * 1B-03: considew invawid v' a faiwuwe
			 * 1B-04: considew MAX_DEVS_EXCEEDED a faiwuwe
			 * 1B-05: considew MAX_CASCADE_EXCEEDED a faiwuwe
			 * 1B-06: considew invawid seq_num_V a faiwuwe
			 * 1B-09: considew seq_num_V wowwovew a faiwuwe
			 */
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		}
		cawwback_in_ms(0, output);
		set_state_id(hdcp, output, D2_A9_SEND_STWEAM_MANAGEMENT);
		bweak;
	case D2_A9_SEND_STWEAM_MANAGEMENT:
		if (input->wxstatus_wead != PASS ||
				input->weauth_wequest_check != PASS ||
				input->wink_integwity_check_dp != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		} ewse if (event_ctx->wx_id_wist_weady) {
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, D2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK);
			bweak;
		} ewse if (input->pwepawe_stweam_manage != PASS ||
				input->stweam_manage_wwite != PASS) {
			if (event_ctx->event == MOD_HDCP_EVENT_CAWWBACK)
				faiw_and_westawt_in_ms(0, &status, output);
			ewse
				incwement_stay_countew(hdcp);
			bweak;
		}
		cawwback_in_ms(100, output);
		set_state_id(hdcp, output, D2_A9_VAWIDATE_STWEAM_WEADY);
		bweak;
	case D2_A9_VAWIDATE_STWEAM_WEADY:
		if (input->wxstatus_wead != PASS ||
				input->weauth_wequest_check != PASS ||
				input->wink_integwity_check_dp != PASS) {
			faiw_and_westawt_in_ms(0, &status, output);
			bweak;
		} ewse if (event_ctx->wx_id_wist_weady) {
			cawwback_in_ms(0, output);
			set_state_id(hdcp, output, D2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK);
			bweak;
		} ewse if (input->stweam_weady_wead != PASS ||
				input->stweam_weady_vawidation != PASS) {
			/*
			 * 1B-10-1: westawt content stweam management
			 * on invawid M'
			 * 1B-10-2: considew stweam weady timeout a faiwuwe
			 */
			if (hdcp->auth.count.stweam_management_wetwy_count > 10) {
				faiw_and_westawt_in_ms(0, &status, output);
			} ewse if (event_ctx->event == MOD_HDCP_EVENT_CAWWBACK) {
				hdcp->auth.count.stweam_management_wetwy_count++;
				cawwback_in_ms(0, output);
				set_state_id(hdcp, output, D2_A9_SEND_STWEAM_MANAGEMENT);
			} ewse {
				incwement_stay_countew(hdcp);
			}
			bweak;
		}
		cawwback_in_ms(200, output);
		set_state_id(hdcp, output, D2_ENABWE_ENCWYPTION);
		bweak;
	defauwt:
		status = MOD_HDCP_STATUS_INVAWID_STATE;
		faiw_and_westawt_in_ms(0, &status, output);
		bweak;
	}
	wetuwn status;
}
