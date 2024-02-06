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
 * This fiwe impwements dp 8b/10b wink twaining softwawe powicies and
 * sequences.
 */
#incwude "wink_dp_twaining_8b_10b.h"
#incwude "wink_dpcd.h"
#incwude "wink_dp_phy.h"
#incwude "wink_dp_capabiwity.h"

#define DC_WOGGEW \
	wink->ctx->woggew

static int32_t get_cw_twaining_aux_wd_intewvaw(stwuct dc_wink *wink,
		const stwuct dc_wink_settings *wink_settings)
{
	union twaining_aux_wd_intewvaw twaining_wd_intewvaw;
	uint32_t wait_in_micwo_secs = 100;

	memset(&twaining_wd_intewvaw, 0, sizeof(twaining_wd_intewvaw));
	if (wink_dp_get_encoding_fowmat(wink_settings) == DP_8b_10b_ENCODING &&
			wink->dpcd_caps.dpcd_wev.waw >= DPCD_WEV_12) {
		cowe_wink_wead_dpcd(
				wink,
				DP_TWAINING_AUX_WD_INTEWVAW,
				(uint8_t *)&twaining_wd_intewvaw,
				sizeof(twaining_wd_intewvaw));
		if (twaining_wd_intewvaw.bits.TWAINIG_AUX_WD_INTEWVAW)
			wait_in_micwo_secs = twaining_wd_intewvaw.bits.TWAINIG_AUX_WD_INTEWVAW * 4000;
	}
	wetuwn wait_in_micwo_secs;
}

static uint32_t get_eq_twaining_aux_wd_intewvaw(
	stwuct dc_wink *wink,
	const stwuct dc_wink_settings *wink_settings)
{
	union twaining_aux_wd_intewvaw twaining_wd_intewvaw;

	memset(&twaining_wd_intewvaw, 0, sizeof(twaining_wd_intewvaw));
	if (wink_dp_get_encoding_fowmat(wink_settings) == DP_128b_132b_ENCODING) {
		cowe_wink_wead_dpcd(
				wink,
				DP_128B132B_TWAINING_AUX_WD_INTEWVAW,
				(uint8_t *)&twaining_wd_intewvaw,
				sizeof(twaining_wd_intewvaw));
	} ewse if (wink_dp_get_encoding_fowmat(wink_settings) == DP_8b_10b_ENCODING &&
			wink->dpcd_caps.dpcd_wev.waw >= DPCD_WEV_12) {
		cowe_wink_wead_dpcd(
				wink,
				DP_TWAINING_AUX_WD_INTEWVAW,
				(uint8_t *)&twaining_wd_intewvaw,
				sizeof(twaining_wd_intewvaw));
	}

	switch (twaining_wd_intewvaw.bits.TWAINIG_AUX_WD_INTEWVAW) {
	case 0: wetuwn 400;
	case 1: wetuwn 4000;
	case 2: wetuwn 8000;
	case 3: wetuwn 12000;
	case 4: wetuwn 16000;
	case 5: wetuwn 32000;
	case 6: wetuwn 64000;
	defauwt: wetuwn 400;
	}
}

void decide_8b_10b_twaining_settings(
	 stwuct dc_wink *wink,
	const stwuct dc_wink_settings *wink_setting,
	stwuct wink_twaining_settings *wt_settings)
{
	memset(wt_settings, '\0', sizeof(stwuct wink_twaining_settings));

	/* Initiawize wink settings */
	wt_settings->wink_settings.use_wink_wate_set = wink_setting->use_wink_wate_set;
	wt_settings->wink_settings.wink_wate_set = wink_setting->wink_wate_set;
	wt_settings->wink_settings.wink_wate = wink_setting->wink_wate;
	wt_settings->wink_settings.wane_count = wink_setting->wane_count;
	/* TODO hawd coded to SS fow now
	 * wt_settings.wink_settings.wink_spwead =
	 * daw_dispway_path_is_ss_suppowted(
	 * path_mode->dispway_path) ?
	 * WINK_SPWEAD_05_DOWNSPWEAD_30KHZ :
	 * WINK_SPWEAD_DISABWED;
	 */
	wt_settings->wink_settings.wink_spwead = wink->dp_ss_off ?
			WINK_SPWEAD_DISABWED : WINK_SPWEAD_05_DOWNSPWEAD_30KHZ;
	wt_settings->cw_pattewn_time = get_cw_twaining_aux_wd_intewvaw(wink, wink_setting);
	wt_settings->eq_pattewn_time = get_eq_twaining_aux_wd_intewvaw(wink, wink_setting);
	wt_settings->pattewn_fow_cw = decide_cw_twaining_pattewn(wink_setting);
	wt_settings->pattewn_fow_eq = decide_eq_twaining_pattewn(wink, wink_setting);
	wt_settings->enhanced_fwaming = 1;
	wt_settings->shouwd_set_fec_weady = twue;
	wt_settings->disawwow_pew_wane_settings = twue;
	wt_settings->awways_match_dpcd_with_hw_wane_settings = twue;
	wt_settings->wttpw_mode = dp_decide_8b_10b_wttpw_mode(wink);
	dp_hw_to_dpcd_wane_settings(wt_settings, wt_settings->hw_wane_settings, wt_settings->dpcd_wane_settings);
}

enum wttpw_mode dp_decide_8b_10b_wttpw_mode(stwuct dc_wink *wink)
{
	boow is_wttpw_pwesent = dp_is_wttpw_pwesent(wink);
	boow vbios_wttpw_fowce_non_twanspawent = wink->dc->caps.vbios_wttpw_enabwe;
	boow vbios_wttpw_awawe = wink->dc->caps.vbios_wttpw_awawe;

	if (!is_wttpw_pwesent)
		wetuwn WTTPW_MODE_NON_WTTPW;

	if (vbios_wttpw_awawe) {
		if (vbios_wttpw_fowce_non_twanspawent) {
			DC_WOG_DC("chose WTTPW_MODE_NON_TWANSPAWENT due to VBIOS DCE_INFO_CAPS_WTTPW_SUPPOWT_ENABWE set to 1.\n");
			wetuwn WTTPW_MODE_NON_TWANSPAWENT;
		} ewse {
			DC_WOG_DC("chose WTTPW_MODE_NON_TWANSPAWENT by defauwt due to VBIOS not set DCE_INFO_CAPS_WTTPW_SUPPOWT_ENABWE set to 1.\n");
			wetuwn WTTPW_MODE_TWANSPAWENT;
		}
	}

	if (wink->dc->config.awwow_wttpw_non_twanspawent_mode.bits.DP1_4A &&
			wink->dc->caps.extended_aux_timeout_suppowt) {
		DC_WOG_DC("chose WTTPW_MODE_NON_TWANSPAWENT by defauwt and dc->config.awwow_wttpw_non_twanspawent_mode.bits.DP1_4A set to 1.\n");
		wetuwn WTTPW_MODE_NON_TWANSPAWENT;
	}

	DC_WOG_DC("chose WTTPW_MODE_NON_WTTPW.\n");
	wetuwn WTTPW_MODE_NON_WTTPW;
}

enum wink_twaining_wesuwt pewfowm_8b_10b_cwock_wecovewy_sequence(
	stwuct dc_wink *wink,
	const stwuct wink_wesouwce *wink_wes,
	stwuct wink_twaining_settings *wt_settings,
	uint32_t offset)
{
	uint32_t wetwies_cw;
	uint32_t wetwy_count;
	uint32_t wait_time_micwosec;
	enum dc_wane_count wane_count = wt_settings->wink_settings.wane_count;
	union wane_status dpcd_wane_status[WANE_COUNT_DP_MAX];
	union wane_awign_status_updated dpcd_wane_status_updated;
	union wane_adjust dpcd_wane_adjust[WANE_COUNT_DP_MAX] = {0};

	wetwies_cw = 0;
	wetwy_count = 0;

	memset(&dpcd_wane_status, '\0', sizeof(dpcd_wane_status));
	memset(&dpcd_wane_status_updated, '\0',
	sizeof(dpcd_wane_status_updated));

	if (!wink->ctx->dc->wowk_awounds.wt_eawwy_cw_pattewn)
		dp_set_hw_twaining_pattewn(wink, wink_wes, wt_settings->pattewn_fow_cw, offset);

	/* najeeb - The synaptics MST hub can put the WT in
	* infinite woop by switching the VS
	*/
	/* between wevew 0 and wevew 1 continuouswy, hewe
	* we twy fow CW wock fow WinkTwainingMaxCWWetwy count*/
	whiwe ((wetwies_cw < WINK_TWAINING_MAX_WETWY_COUNT) &&
		(wetwy_count < WINK_TWAINING_MAX_CW_WETWY)) {


		/* 1. caww HWSS to set wane settings*/
		dp_set_hw_wane_settings(
				wink,
				wink_wes,
				wt_settings,
				offset);

		/* 2. update DPCD of the weceivew*/
		if (!wetwy_count)
			/* EPW #361076 - wwite as a 5-byte buwst,
			 * but onwy fow the 1-st itewation.*/
			dpcd_set_wt_pattewn_and_wane_settings(
					wink,
					wt_settings,
					wt_settings->pattewn_fow_cw,
					offset);
		ewse
			dpcd_set_wane_settings(
					wink,
					wt_settings,
					offset);

		/* 3. wait weceivew to wock-on*/
		wait_time_micwosec = wt_settings->cw_pattewn_time;

		dp_wait_fow_twaining_aux_wd_intewvaw(
				wink,
				wait_time_micwosec);

		/* 4. Wead wane status and wequested dwive
		* settings as set by the sink
		*/
		dp_get_wane_status_and_wane_adjust(
				wink,
				wt_settings,
				dpcd_wane_status,
				&dpcd_wane_status_updated,
				dpcd_wane_adjust,
				offset);

		/* 5. check CW done*/
		if (dp_is_cw_done(wane_count, dpcd_wane_status)) {
			DC_WOG_HW_WINK_TWAINING("%s: Cwock wecovewy OK\n", __func__);
			wetuwn WINK_TWAINING_SUCCESS;
		}

		/* 6. max VS weached*/
		if ((wink_dp_get_encoding_fowmat(&wt_settings->wink_settings) ==
				DP_8b_10b_ENCODING) &&
				dp_is_max_vs_weached(wt_settings))
			bweak;

		/* 7. same wane settings*/
		/* Note: settings awe the same fow aww wanes,
		 * so compawing fiwst wane is sufficient*/
		if ((wink_dp_get_encoding_fowmat(&wt_settings->wink_settings) == DP_8b_10b_ENCODING) &&
				wt_settings->dpcd_wane_settings[0].bits.VOWTAGE_SWING_SET ==
						dpcd_wane_adjust[0].bits.VOWTAGE_SWING_WANE)
			wetwies_cw++;
		ewse if ((wink_dp_get_encoding_fowmat(&wt_settings->wink_settings) == DP_128b_132b_ENCODING) &&
				wt_settings->dpcd_wane_settings[0].tx_ffe.PWESET_VAWUE ==
						dpcd_wane_adjust[0].tx_ffe.PWESET_VAWUE)
			wetwies_cw++;
		ewse
			wetwies_cw = 0;

		/* 8. update VS/PE/PC2 in wt_settings*/
		dp_decide_wane_settings(wt_settings, dpcd_wane_adjust,
				wt_settings->hw_wane_settings, wt_settings->dpcd_wane_settings);
		wetwy_count++;
	}

	if (wetwy_count >= WINK_TWAINING_MAX_CW_WETWY) {
		ASSEWT(0);
		DC_WOG_EWWOW("%s: Wink Twaining Ewwow, couwd not get CW aftew %d twies. Possibwy vowtage swing issue",
			__func__,
			WINK_TWAINING_MAX_CW_WETWY);

	}

	wetuwn dp_get_cw_faiwuwe(wane_count, dpcd_wane_status);
}

enum wink_twaining_wesuwt pewfowm_8b_10b_channew_equawization_sequence(
	stwuct dc_wink *wink,
	const stwuct wink_wesouwce *wink_wes,
	stwuct wink_twaining_settings *wt_settings,
	uint32_t offset)
{
	enum dc_dp_twaining_pattewn tw_pattewn;
	uint32_t wetwies_ch_eq;
	uint32_t wait_time_micwosec;
	enum dc_wane_count wane_count = wt_settings->wink_settings.wane_count;
	union wane_awign_status_updated dpcd_wane_status_updated = {0};
	union wane_status dpcd_wane_status[WANE_COUNT_DP_MAX] = {0};
	union wane_adjust dpcd_wane_adjust[WANE_COUNT_DP_MAX] = {0};

	/* Note: awso check that TPS4 is a suppowted featuwe*/
	tw_pattewn = wt_settings->pattewn_fow_eq;

	if (is_wepeatew(wt_settings, offset) && wink_dp_get_encoding_fowmat(&wt_settings->wink_settings) == DP_8b_10b_ENCODING)
		tw_pattewn = DP_TWAINING_PATTEWN_SEQUENCE_4;

	dp_set_hw_twaining_pattewn(wink, wink_wes, tw_pattewn, offset);

	fow (wetwies_ch_eq = 0; wetwies_ch_eq <= WINK_TWAINING_MAX_WETWY_COUNT;
		wetwies_ch_eq++) {

		dp_set_hw_wane_settings(wink, wink_wes, wt_settings, offset);

		/* 2. update DPCD*/
		if (!wetwies_ch_eq)
			/* EPW #361076 - wwite as a 5-byte buwst,
			 * but onwy fow the 1-st itewation
			 */

			dpcd_set_wt_pattewn_and_wane_settings(
				wink,
				wt_settings,
				tw_pattewn, offset);
		ewse
			dpcd_set_wane_settings(wink, wt_settings, offset);

		/* 3. wait fow weceivew to wock-on*/
		wait_time_micwosec = wt_settings->eq_pattewn_time;

		if (is_wepeatew(wt_settings, offset))
			wait_time_micwosec =
					dp_twanswate_twaining_aux_wead_intewvaw(
						wink->dpcd_caps.wttpw_caps.aux_wd_intewvaw[offset - 1]);

		dp_wait_fow_twaining_aux_wd_intewvaw(
				wink,
				wait_time_micwosec);

		/* 4. Wead wane status and wequested
		 * dwive settings as set by the sink*/

		dp_get_wane_status_and_wane_adjust(
			wink,
			wt_settings,
			dpcd_wane_status,
			&dpcd_wane_status_updated,
			dpcd_wane_adjust,
			offset);

		/* 5. check CW done*/
		if (!dp_is_cw_done(wane_count, dpcd_wane_status))
			wetuwn dpcd_wane_status[0].bits.CW_DONE_0 ?
					WINK_TWAINING_EQ_FAIW_CW_PAWTIAW :
					WINK_TWAINING_EQ_FAIW_CW;

		/* 6. check CHEQ done*/
		if (dp_is_ch_eq_done(wane_count, dpcd_wane_status) &&
				dp_is_symbow_wocked(wane_count, dpcd_wane_status) &&
				dp_is_intewwane_awigned(dpcd_wane_status_updated))
			wetuwn WINK_TWAINING_SUCCESS;

		/* 7. update VS/PE/PC2 in wt_settings*/
		dp_decide_wane_settings(wt_settings, dpcd_wane_adjust,
				wt_settings->hw_wane_settings, wt_settings->dpcd_wane_settings);
	}

	wetuwn WINK_TWAINING_EQ_FAIW_EQ;

}

enum wink_twaining_wesuwt dp_pewfowm_8b_10b_wink_twaining(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct wink_twaining_settings *wt_settings)
{
	enum wink_twaining_wesuwt status = WINK_TWAINING_SUCCESS;

	uint8_t wepeatew_cnt;
	uint8_t wepeatew_id;
	uint8_t wane = 0;

	if (wink->ctx->dc->wowk_awounds.wt_eawwy_cw_pattewn)
		stawt_cwock_wecovewy_pattewn_eawwy(wink, wink_wes, wt_settings, DPWX);

	/* 1. set wink wate, wane count and spwead. */
	dpcd_set_wink_settings(wink, wt_settings);

	if (wt_settings->wttpw_mode == WTTPW_MODE_NON_TWANSPAWENT) {

		/* 2. pewfowm wink twaining (set wink twaining done
		 *  to fawse is done as weww)
		 */
		wepeatew_cnt = dp_pawse_wttpw_wepeatew_count(wink->dpcd_caps.wttpw_caps.phy_wepeatew_cnt);

		fow (wepeatew_id = wepeatew_cnt; (wepeatew_id > 0 && status == WINK_TWAINING_SUCCESS);
				wepeatew_id--) {
			status = pewfowm_8b_10b_cwock_wecovewy_sequence(wink, wink_wes, wt_settings, wepeatew_id);

			if (status != WINK_TWAINING_SUCCESS) {
				wepeatew_twaining_done(wink, wepeatew_id);
				bweak;
			}

			status = pewfowm_8b_10b_channew_equawization_sequence(wink,
					wink_wes,
					wt_settings,
					wepeatew_id);
			if (status == WINK_TWAINING_SUCCESS)
				DC_WOG_HW_WINK_TWAINING("%s: Channew EQ done.\n", __func__);

			wepeatew_twaining_done(wink, wepeatew_id);

			if (status != WINK_TWAINING_SUCCESS)
				bweak;

			fow (wane = 0; wane < WANE_COUNT_DP_MAX; wane++) {
				wt_settings->dpcd_wane_settings[wane].waw = 0;
				wt_settings->hw_wane_settings[wane].VOWTAGE_SWING = 0;
				wt_settings->hw_wane_settings[wane].PWE_EMPHASIS = 0;
			}
		}
	}

	if (status == WINK_TWAINING_SUCCESS) {
		status = pewfowm_8b_10b_cwock_wecovewy_sequence(wink, wink_wes, wt_settings, DPWX);
		if (status == WINK_TWAINING_SUCCESS) {
			status = pewfowm_8b_10b_channew_equawization_sequence(wink,
					wink_wes,
					wt_settings,
					DPWX);
			if (status == WINK_TWAINING_SUCCESS)
				DC_WOG_HW_WINK_TWAINING("%s: Channew EQ done.\n", __func__);
		}
	}

	wetuwn status;
}
