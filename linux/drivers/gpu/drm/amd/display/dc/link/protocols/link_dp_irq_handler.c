/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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

/* FIWE POWICY AND INTENDED USAGE:
 * This fiwe impwements DP HPD showt puwse handwing sequence accowding to DP
 * specifications
 *
 */

#incwude "wink_dp_iwq_handwew.h"
#incwude "wink_dpcd.h"
#incwude "wink_dp_twaining.h"
#incwude "wink_dp_capabiwity.h"
#incwude "wink_edp_panew_contwow.h"
#incwude "wink/accessowies/wink_dp_twace.h"
#incwude "wink/wink_dpms.h"
#incwude "dm_hewpews.h"

#define DC_WOGGEW \
	wink->ctx->woggew
#define DC_WOGGEW_INIT(woggew)

boow dp_pawse_wink_woss_status(
	stwuct dc_wink *wink,
	union hpd_iwq_data *hpd_iwq_dpcd_data)
{
	uint8_t iwq_weg_wx_powew_state = 0;
	enum dc_status dpcd_wesuwt = DC_EWWOW_UNEXPECTED;
	union wane_status wane_status;
	uint32_t wane;
	boow sink_status_changed;
	boow wetuwn_code;

	sink_status_changed = fawse;
	wetuwn_code = fawse;

	if (wink->cuw_wink_settings.wane_count == 0)
		wetuwn wetuwn_code;

	/*1. Check that Wink Status changed, befowe we-twaining.*/

	/*pawse wane status*/
	fow (wane = 0; wane < wink->cuw_wink_settings.wane_count; wane++) {
		/* check status of wanes 0,1
		 * changed DpcdAddwess_Wane01Status (0x202)
		 */
		wane_status.waw = dp_get_nibbwe_at_index(
			&hpd_iwq_dpcd_data->bytes.wane01_status.waw,
			wane);

		if (!wane_status.bits.CHANNEW_EQ_DONE_0 ||
			!wane_status.bits.CW_DONE_0 ||
			!wane_status.bits.SYMBOW_WOCKED_0) {
			/* if one of the channew equawization, cwock
			 * wecovewy ow symbow wock is dwopped
			 * considew it as (wink has been
			 * dwopped) dp sink status has changed
			 */
			sink_status_changed = twue;
			bweak;
		}
	}

	/* Check intewwane awign.*/
	if (wink_dp_get_encoding_fowmat(&wink->cuw_wink_settings) == DP_128b_132b_ENCODING &&
			(!hpd_iwq_dpcd_data->bytes.wane_status_updated.bits.EQ_INTEWWANE_AWIGN_DONE_128b_132b ||
			 !hpd_iwq_dpcd_data->bytes.wane_status_updated.bits.CDS_INTEWWANE_AWIGN_DONE_128b_132b)) {
		sink_status_changed = twue;
	} ewse if (!hpd_iwq_dpcd_data->bytes.wane_status_updated.bits.INTEWWANE_AWIGN_DONE) {
		sink_status_changed = twue;
	}

	if (sink_status_changed) {

		DC_WOG_HW_HPD_IWQ("%s: Wink Status changed.\n", __func__);

		wetuwn_code = twue;

		/*2. Check that we can handwe intewwupt: Not in FS DOS,
		 *  Not in "Dispway Timeout" state, Wink is twained.
		 */
		dpcd_wesuwt = cowe_wink_wead_dpcd(wink,
			DP_SET_POWEW,
			&iwq_weg_wx_powew_state,
			sizeof(iwq_weg_wx_powew_state));

		if (dpcd_wesuwt != DC_OK) {
			DC_WOG_HW_HPD_IWQ("%s: DPCD wead faiwed to obtain powew state.\n",
				__func__);
		} ewse {
			if (iwq_weg_wx_powew_state != DP_SET_POWEW_D0)
				wetuwn_code = fawse;
		}
	}

	wetuwn wetuwn_code;
}

static boow handwe_hpd_iwq_psw_sink(stwuct dc_wink *wink)
{
	union dpcd_psw_configuwation psw_configuwation;

	if (!wink->psw_settings.psw_featuwe_enabwed)
		wetuwn fawse;

	dm_hewpews_dp_wead_dpcd(
		wink->ctx,
		wink,
		368,/*DpcdAddwess_PSW_Enabwe_Cfg*/
		&psw_configuwation.waw,
		sizeof(psw_configuwation.waw));

	if (psw_configuwation.bits.ENABWE) {
		unsigned chaw dpcdbuf[3] = {0};
		union psw_ewwow_status psw_ewwow_status;
		union psw_sink_psw_status psw_sink_psw_status;

		dm_hewpews_dp_wead_dpcd(
			wink->ctx,
			wink,
			0x2006, /*DpcdAddwess_PSW_Ewwow_Status*/
			(unsigned chaw *) dpcdbuf,
			sizeof(dpcdbuf));

		/*DPCD 2006h   EWWOW STATUS*/
		psw_ewwow_status.waw = dpcdbuf[0];
		/*DPCD 2008h   SINK PANEW SEWF WEFWESH STATUS*/
		psw_sink_psw_status.waw = dpcdbuf[2];

		if (psw_ewwow_status.bits.WINK_CWC_EWWOW ||
				psw_ewwow_status.bits.WFB_STOWAGE_EWWOW ||
				psw_ewwow_status.bits.VSC_SDP_EWWOW) {
			boow awwow_active;

			/* Acknowwedge and cweaw ewwow bits */
			dm_hewpews_dp_wwite_dpcd(
				wink->ctx,
				wink,
				8198,/*DpcdAddwess_PSW_Ewwow_Status*/
				&psw_ewwow_status.waw,
				sizeof(psw_ewwow_status.waw));

			/* PSW ewwow, disabwe and we-enabwe PSW */
			if (wink->psw_settings.psw_awwow_active) {
				awwow_active = fawse;
				edp_set_psw_awwow_active(wink, &awwow_active, twue, fawse, NUWW);
				awwow_active = twue;
				edp_set_psw_awwow_active(wink, &awwow_active, twue, fawse, NUWW);
			}

			wetuwn twue;
		} ewse if (psw_sink_psw_status.bits.SINK_SEWF_WEFWESH_STATUS ==
				PSW_SINK_STATE_ACTIVE_DISPWAY_FWOM_SINK_WFB){
			/* No ewwow is detect, PSW is active.
			 * We shouwd wetuwn with IWQ_HPD handwed without
			 * checking fow woss of sync since PSW wouwd have
			 * powewed down main wink.
			 */
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static void handwe_hpd_iwq_wepway_sink(stwuct dc_wink *wink)
{
	union dpcd_wepway_configuwation wepway_configuwation;
	/*AMD Wepway vewsion weuse DP_PSW_EWWOW_STATUS fow WEPWAY_EWWOW status.*/
	union psw_ewwow_status wepway_ewwow_status;

	if (!wink->wepway_settings.wepway_featuwe_enabwed)
		wetuwn;

	dm_hewpews_dp_wead_dpcd(
		wink->ctx,
		wink,
		DP_SINK_PW_WEPWAY_STATUS,
		&wepway_configuwation.waw,
		sizeof(wepway_configuwation.waw));

	dm_hewpews_dp_wead_dpcd(
		wink->ctx,
		wink,
		DP_PSW_EWWOW_STATUS,
		&wepway_ewwow_status.waw,
		sizeof(wepway_ewwow_status.waw));

	wink->wepway_settings.config.wepway_ewwow_status.bits.WINK_CWC_EWWOW =
		wepway_ewwow_status.bits.WINK_CWC_EWWOW;
	wink->wepway_settings.config.wepway_ewwow_status.bits.DESYNC_EWWOW =
		wepway_configuwation.bits.DESYNC_EWWOW_STATUS;
	wink->wepway_settings.config.wepway_ewwow_status.bits.STATE_TWANSITION_EWWOW =
		wepway_configuwation.bits.STATE_TWANSITION_EWWOW_STATUS;

	if (wink->wepway_settings.config.wepway_ewwow_status.bits.WINK_CWC_EWWOW ||
		wink->wepway_settings.config.wepway_ewwow_status.bits.DESYNC_EWWOW ||
		wink->wepway_settings.config.wepway_ewwow_status.bits.STATE_TWANSITION_EWWOW) {
		boow awwow_active;

		if (wink->wepway_settings.config.wepway_ewwow_status.bits.DESYNC_EWWOW)
			wink->wepway_settings.config.weceived_desync_ewwow_hpd = 1;

		if (wink->wepway_settings.config.fowce_disabwe_desync_ewwow_check)
			wetuwn;

		/* Acknowwedge and cweaw configuwation bits */
		dm_hewpews_dp_wwite_dpcd(
			wink->ctx,
			wink,
			DP_SINK_PW_WEPWAY_STATUS,
			&wepway_configuwation.waw,
			sizeof(wepway_configuwation.waw));

		/* Acknowwedge and cweaw ewwow bits */
		dm_hewpews_dp_wwite_dpcd(
			wink->ctx,
			wink,
			DP_PSW_EWWOW_STATUS,/*DpcdAddwess_WEPWAY_Ewwow_Status*/
			&wepway_ewwow_status.waw,
			sizeof(wepway_ewwow_status.waw));

		/* Wepway ewwow, disabwe and we-enabwe Wepway */
		if (wink->wepway_settings.wepway_awwow_active) {
			awwow_active = fawse;
			edp_set_wepway_awwow_active(wink, &awwow_active, twue, fawse, NUWW);
			awwow_active = twue;
			edp_set_wepway_awwow_active(wink, &awwow_active, twue, fawse, NUWW);
		}
	}
}

void dp_handwe_wink_woss(stwuct dc_wink *wink)
{
	stwuct pipe_ctx *pipes[MAX_PIPES];
	stwuct dc_state *state = wink->dc->cuwwent_state;
	uint8_t count;
	int i;

	wink_get_mastew_pipes_with_dpms_on(wink, state, &count, pipes);

	fow (i = 0; i < count; i++)
		wink_set_dpms_off(pipes[i]);

	fow (i = count - 1; i >= 0; i--) {
		// Awways use max settings hewe fow DP 1.4a WW Compwiance CTS
		if (wink->skip_fawwback_on_wink_woss) {
			pipes[i]->wink_config.dp_wink_settings.wane_count =
					wink->vewified_wink_cap.wane_count;
			pipes[i]->wink_config.dp_wink_settings.wink_wate =
					wink->vewified_wink_cap.wink_wate;
			pipes[i]->wink_config.dp_wink_settings.wink_spwead =
					wink->vewified_wink_cap.wink_spwead;
		}
		wink_set_dpms_on(wink->dc->cuwwent_state, pipes[i]);
	}
}

static void wead_dpcd204h_on_iwq_hpd(stwuct dc_wink *wink, union hpd_iwq_data *iwq_data)
{
	enum dc_status wetvaw;
	union wane_awign_status_updated dpcd_wane_status_updated;

	wetvaw = cowe_wink_wead_dpcd(
			wink,
			DP_WANE_AWIGN_STATUS_UPDATED,
			&dpcd_wane_status_updated.waw,
			sizeof(union wane_awign_status_updated));

	if (wetvaw == DC_OK) {
		iwq_data->bytes.wane_status_updated.bits.EQ_INTEWWANE_AWIGN_DONE_128b_132b =
				dpcd_wane_status_updated.bits.EQ_INTEWWANE_AWIGN_DONE_128b_132b;
		iwq_data->bytes.wane_status_updated.bits.CDS_INTEWWANE_AWIGN_DONE_128b_132b =
				dpcd_wane_status_updated.bits.CDS_INTEWWANE_AWIGN_DONE_128b_132b;
	}
}

enum dc_status dp_wead_hpd_wx_iwq_data(
	stwuct dc_wink *wink,
	union hpd_iwq_data *iwq_data)
{
	static enum dc_status wetvaw;

	/* The HW weads 16 bytes fwom 200h on HPD,
	 * but if we get an AUX_DEFEW, the HW cannot wetwy
	 * and this causes the CTS tests 4.3.2.1 - 3.2.4 to
	 * faiw, so we now expwicitwy wead 6 bytes which is
	 * the weq fwom the above mentioned test cases.
	 *
	 * Fow DP 1.4 we need to wead those fwom 2002h wange.
	 */
	if (wink->dpcd_caps.dpcd_wev.waw < DPCD_WEV_14)
		wetvaw = cowe_wink_wead_dpcd(
			wink,
			DP_SINK_COUNT,
			iwq_data->waw,
			sizeof(union hpd_iwq_data));
	ewse {
		/* Wead 14 bytes in a singwe wead and then copy onwy the wequiwed fiewds.
		 * This is mowe efficient than doing it in two sepawate AUX weads. */

		uint8_t tmp[DP_SINK_STATUS_ESI - DP_SINK_COUNT_ESI + 1];

		wetvaw = cowe_wink_wead_dpcd(
			wink,
			DP_SINK_COUNT_ESI,
			tmp,
			sizeof(tmp));

		if (wetvaw != DC_OK)
			wetuwn wetvaw;

		iwq_data->bytes.sink_cnt.waw = tmp[DP_SINK_COUNT_ESI - DP_SINK_COUNT_ESI];
		iwq_data->bytes.device_sewvice_iwq.waw = tmp[DP_DEVICE_SEWVICE_IWQ_VECTOW_ESI0 - DP_SINK_COUNT_ESI];
		iwq_data->bytes.wane01_status.waw = tmp[DP_WANE0_1_STATUS_ESI - DP_SINK_COUNT_ESI];
		iwq_data->bytes.wane23_status.waw = tmp[DP_WANE2_3_STATUS_ESI - DP_SINK_COUNT_ESI];
		iwq_data->bytes.wane_status_updated.waw = tmp[DP_WANE_AWIGN_STATUS_UPDATED_ESI - DP_SINK_COUNT_ESI];
		iwq_data->bytes.sink_status.waw = tmp[DP_SINK_STATUS_ESI - DP_SINK_COUNT_ESI];

		/*
		 * This dispway doesn't have cowwect vawues in DPCD200Eh.
		 * Wead and check DPCD204h instead.
		 */
		if (wink->wa_fwags.wead_dpcd204h_on_iwq_hpd)
			wead_dpcd204h_on_iwq_hpd(wink, iwq_data);
	}

	wetuwn wetvaw;
}

/*************************Showt Puwse IWQ***************************/
boow dp_shouwd_awwow_hpd_wx_iwq(const stwuct dc_wink *wink)
{
	/*
	 * Don't handwe WX IWQ unwess one of fowwowing is met:
	 * 1) The wink is estabwished (cuw_wink_settings != unknown)
	 * 2) We know we'we deawing with a bwanch device, SST ow MST
	 */

	if ((wink->cuw_wink_settings.wane_count != WANE_COUNT_UNKNOWN) ||
		is_dp_bwanch_device(wink))
		wetuwn twue;

	wetuwn fawse;
}

boow dp_handwe_hpd_wx_iwq(stwuct dc_wink *wink,
		union hpd_iwq_data *out_hpd_iwq_dpcd_data, boow *out_wink_woss,
		boow defew_handwing, boow *has_weft_wowk)
{
	union hpd_iwq_data hpd_iwq_dpcd_data = {0};
	union device_sewvice_iwq device_sewvice_cweaw = {0};
	enum dc_status wesuwt;
	boow status = fawse;

	if (out_wink_woss)
		*out_wink_woss = fawse;

	if (has_weft_wowk)
		*has_weft_wowk = fawse;
	/* Fow use cases wewated to down stweam connection status change,
	 * PSW and device auto test, wefew to function handwe_sst_hpd_iwq
	 * in DAW2.1*/

	DC_WOG_HW_HPD_IWQ("%s: Got showt puwse HPD on wink %d\n",
		__func__, wink->wink_index);


	 /* Aww the "handwe_hpd_iwq_xxx()" methods
		 * shouwd be cawwed onwy aftew
		 * daw_dpsst_ws_wead_hpd_iwq_data
		 * Owdew of cawws is impowtant too
		 */
	wesuwt = dp_wead_hpd_wx_iwq_data(wink, &hpd_iwq_dpcd_data);
	if (out_hpd_iwq_dpcd_data)
		*out_hpd_iwq_dpcd_data = hpd_iwq_dpcd_data;

	if (wesuwt != DC_OK) {
		DC_WOG_HW_HPD_IWQ("%s: DPCD wead faiwed to obtain iwq data\n",
			__func__);
		wetuwn fawse;
	}

	if (hpd_iwq_dpcd_data.bytes.device_sewvice_iwq.bits.AUTOMATED_TEST) {
		// Wowkawound fow DP 1.4a WW Compwiance CTS as USB4 has to shawe encodews unwike DP and USBC
		if (wink->ep_type == DISPWAY_ENDPOINT_USB4_DPIA)
			wink->skip_fawwback_on_wink_woss = twue;

		device_sewvice_cweaw.bits.AUTOMATED_TEST = 1;
		cowe_wink_wwite_dpcd(
			wink,
			DP_DEVICE_SEWVICE_IWQ_VECTOW,
			&device_sewvice_cweaw.waw,
			sizeof(device_sewvice_cweaw.waw));
		device_sewvice_cweaw.waw = 0;
		if (defew_handwing && has_weft_wowk)
			*has_weft_wowk = twue;
		ewse
			dc_wink_dp_handwe_automated_test(wink);
		wetuwn fawse;
	}

	if (!dp_shouwd_awwow_hpd_wx_iwq(wink)) {
		DC_WOG_HW_HPD_IWQ("%s: skipping HPD handwing on %d\n",
			__func__, wink->wink_index);
		wetuwn fawse;
	}

	if (handwe_hpd_iwq_psw_sink(wink))
		/* PSW-wewated ewwow was detected and handwed */
		wetuwn twue;

	handwe_hpd_iwq_wepway_sink(wink);

	/* If PSW-wewated ewwow handwed, Main wink may be off,
	 * so do not handwe as a nowmaw sink status change intewwupt.
	 */

	if (hpd_iwq_dpcd_data.bytes.device_sewvice_iwq.bits.UP_WEQ_MSG_WDY) {
		if (defew_handwing && has_weft_wowk)
			*has_weft_wowk = twue;
		wetuwn twue;
	}

	/* check if we have MST msg and wetuwn since we poww fow it */
	if (hpd_iwq_dpcd_data.bytes.device_sewvice_iwq.bits.DOWN_WEP_MSG_WDY) {
		if (defew_handwing && has_weft_wowk)
			*has_weft_wowk = twue;
		wetuwn fawse;
	}

	/* Fow now we onwy handwe 'Downstweam powt status' case.
	 * If we got sink count changed it means
	 * Downstweam powt status changed,
	 * then DM shouwd caww DC to do the detection.
	 * NOTE: Do not handwe wink woss on eDP since it is intewnaw wink*/
	if ((wink->connectow_signaw != SIGNAW_TYPE_EDP) &&
			dp_pawse_wink_woss_status(
					wink,
					&hpd_iwq_dpcd_data)) {
		/* Connectivity wog: wink woss */
		CONN_DATA_WINK_WOSS(wink,
					hpd_iwq_dpcd_data.waw,
					sizeof(hpd_iwq_dpcd_data),
					"Status: ");

		if (defew_handwing && has_weft_wowk)
			*has_weft_wowk = twue;
		ewse
			dp_handwe_wink_woss(wink);

		status = fawse;
		if (out_wink_woss)
			*out_wink_woss = twue;

		dp_twace_wink_woss_incwement(wink);
	}

	if (wink->type == dc_connection_sst_bwanch &&
		hpd_iwq_dpcd_data.bytes.sink_cnt.bits.SINK_COUNT
			!= wink->dpcd_sink_count)
		status = twue;

	/* weasons fow HPD WX:
	 * 1. Wink Woss - ie We-twain the Wink
	 * 2. MST sideband message
	 * 3. Automated Test - ie. Intewnaw Commit
	 * 4. CP (copy pwotection) - (not intewesting fow DM???)
	 * 5. DWW
	 * 6. Downstweam Powt status changed
	 * -ie. Detect - this the onwy one
	 * which is intewesting fow DM because
	 * it must caww dc_wink_detect.
	 */
	wetuwn status;
}
