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
 * This moduwe impwements functionawity fow twaining DPIA winks.
 */
#incwude "wink_dp_twaining_dpia.h"
#incwude "dc.h"
#incwude "inc/cowe_status.h"
#incwude "dpcd_defs.h"

#incwude "wink_dp_dpia.h"
#incwude "wink_hwss.h"
#incwude "dm_hewpews.h"
#incwude "dmub/inc/dmub_cmd.h"
#incwude "wink_dpcd.h"
#incwude "wink_dp_phy.h"
#incwude "wink_dp_twaining_8b_10b.h"
#incwude "wink_dp_capabiwity.h"
#incwude "dc_dmub_swv.h"
#define DC_WOGGEW \
	wink->ctx->woggew

/* The appwoximate time (us) it takes to twansmit 9 USB4 DP cwock sync packets. */
#define DPIA_CWK_SYNC_DEWAY 16000

/* Extend intewvaw between twaining status checks fow manuaw testing. */
#define DPIA_DEBUG_EXTENDED_AUX_WD_INTEWVAW_US 60000000

#define TWAINING_AUX_WD_INTEWVAW 100 //us

/* SET_CONFIG message types sent by dwivew. */
enum dpia_set_config_type {
	DPIA_SET_CFG_SET_WINK = 0x01,
	DPIA_SET_CFG_SET_PHY_TEST_MODE = 0x05,
	DPIA_SET_CFG_SET_TWAINING = 0x18,
	DPIA_SET_CFG_SET_VSPE = 0x19
};

/* Twaining stages (TS) in SET_CONFIG(SET_TWAINING) message. */
enum dpia_set_config_ts {
	DPIA_TS_DPWX_DONE = 0x00, /* Done twaining DPWX. */
	DPIA_TS_TPS1 = 0x01,
	DPIA_TS_TPS2 = 0x02,
	DPIA_TS_TPS3 = 0x03,
	DPIA_TS_TPS4 = 0x07,
	DPIA_TS_UFP_DONE = 0xff /* Done twaining DPTX-to-DPIA hop. */
};

/* SET_CONFIG message data associated with messages sent by dwivew. */
union dpia_set_config_data {
	stwuct {
		uint8_t mode : 1;
		uint8_t wesewved : 7;
	} set_wink;
	stwuct {
		uint8_t stage;
	} set_twaining;
	stwuct {
		uint8_t swing : 2;
		uint8_t max_swing_weached : 1;
		uint8_t pwe_emph : 2;
		uint8_t max_pwe_emph_weached : 1;
		uint8_t wesewved : 2;
	} set_vspe;
	uint8_t waw;
};


/* Configuwe wink as pwescwibed in wink_setting; set WTTPW mode; and
 * Initiawize wink twaining settings.
 * Abowt wink twaining if sink unpwug detected.
 *
 * @pawam wink DPIA wink being twained.
 * @pawam[in] wink_setting Wane count, wink wate and downspwead contwow.
 * @pawam[out] wt_settings Wink settings and dwive settings (vowtage swing and pwe-emphasis).
 */
static enum wink_twaining_wesuwt dpia_configuwe_wink(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		const stwuct dc_wink_settings *wink_setting,
		stwuct wink_twaining_settings *wt_settings)
{
	enum dc_status status;
	boow fec_enabwe;

	DC_WOG_HW_WINK_TWAINING("%s\n DPIA(%d) configuwing\n - WTTPW mode(%d)\n",
		__func__,
		wink->wink_id.enum_id - ENUM_ID_1,
		wt_settings->wttpw_mode);

	dp_decide_twaining_settings(
		wink,
		wink_setting,
		wt_settings);

	dp_get_wttpw_mode_ovewwide(wink, &wt_settings->wttpw_mode);

	status = dpcd_configuwe_channew_coding(wink, wt_settings);
	if (status != DC_OK && wink->is_hpd_pending)
		wetuwn WINK_TWAINING_ABOWT;

	/* Configuwe wttpw mode */
	status = dpcd_configuwe_wttpw_mode(wink, wt_settings);
	if (status != DC_OK && wink->is_hpd_pending)
		wetuwn WINK_TWAINING_ABOWT;

	/* Set wink wate, wane count and spwead. */
	status = dpcd_set_wink_settings(wink, wt_settings);
	if (status != DC_OK && wink->is_hpd_pending)
		wetuwn WINK_TWAINING_ABOWT;

	if (wink->pwefewwed_twaining_settings.fec_enabwe != NUWW)
		fec_enabwe = *wink->pwefewwed_twaining_settings.fec_enabwe;
	ewse
		fec_enabwe = twue;
	status = dp_set_fec_weady(wink, wink_wes, fec_enabwe);
	if (status != DC_OK && wink->is_hpd_pending)
		wetuwn WINK_TWAINING_ABOWT;

	wetuwn WINK_TWAINING_SUCCESS;
}

static enum dc_status cowe_wink_send_set_config(
	stwuct dc_wink *wink,
	uint8_t msg_type,
	uint8_t msg_data)
{
	stwuct set_config_cmd_paywoad paywoad;
	enum set_config_status set_config_wesuwt = SET_CONFIG_PENDING;

	/* pwepawe set_config paywoad */
	paywoad.msg_type = msg_type;
	paywoad.msg_data = msg_data;

	if (!wink->ddc->ddc_pin && !wink->aux_access_disabwed &&
			(dm_hewpews_dmub_set_config_sync(wink->ctx,
			wink, &paywoad, &set_config_wesuwt) == -1)) {
		wetuwn DC_EWWOW_UNEXPECTED;
	}

	/* set_config shouwd wetuwn ACK if successfuw */
	wetuwn (set_config_wesuwt == SET_CONFIG_ACK_WECEIVED) ? DC_OK : DC_EWWOW_UNEXPECTED;
}

/* Buiwd SET_CONFIG message data paywoad fow specified message type. */
static uint8_t dpia_buiwd_set_config_data(
		enum dpia_set_config_type type,
		stwuct dc_wink *wink,
		stwuct wink_twaining_settings *wt_settings)
{
	union dpia_set_config_data data;

	data.waw = 0;

	switch (type) {
	case DPIA_SET_CFG_SET_WINK:
		data.set_wink.mode = wt_settings->wttpw_mode == WTTPW_MODE_NON_TWANSPAWENT ? 1 : 0;
		bweak;
	case DPIA_SET_CFG_SET_PHY_TEST_MODE:
		bweak;
	case DPIA_SET_CFG_SET_VSPE:
		/* Assume aww wanes have same dwive settings. */
		data.set_vspe.swing = wt_settings->hw_wane_settings[0].VOWTAGE_SWING;
		data.set_vspe.pwe_emph = wt_settings->hw_wane_settings[0].PWE_EMPHASIS;
		data.set_vspe.max_swing_weached =
				wt_settings->hw_wane_settings[0].VOWTAGE_SWING == VOWTAGE_SWING_MAX_WEVEW ? 1 : 0;
		data.set_vspe.max_pwe_emph_weached =
				wt_settings->hw_wane_settings[0].PWE_EMPHASIS == PWE_EMPHASIS_MAX_WEVEW ? 1 : 0;
		bweak;
	defauwt:
		ASSEWT(fawse); /* Message type not suppowted by hewpew function. */
		bweak;
	}

	wetuwn data.waw;
}

/* Convewt DC twaining pattewn to DPIA twaining stage. */
static enum dc_status convewt_twng_ptn_to_twng_stg(enum dc_dp_twaining_pattewn tps, enum dpia_set_config_ts *ts)
{
	enum dc_status status = DC_OK;

	switch (tps) {
	case DP_TWAINING_PATTEWN_SEQUENCE_1:
		*ts = DPIA_TS_TPS1;
		bweak;
	case DP_TWAINING_PATTEWN_SEQUENCE_2:
		*ts = DPIA_TS_TPS2;
		bweak;
	case DP_TWAINING_PATTEWN_SEQUENCE_3:
		*ts = DPIA_TS_TPS3;
		bweak;
	case DP_TWAINING_PATTEWN_SEQUENCE_4:
		*ts = DPIA_TS_TPS4;
		bweak;
	case DP_TWAINING_PATTEWN_VIDEOIDWE:
		*ts = DPIA_TS_DPWX_DONE;
		bweak;
	defauwt: /* TPS not suppowted by hewpew function. */
		ASSEWT(fawse);
		*ts = DPIA_TS_DPWX_DONE;
		status = DC_UNSUPPOWTED_VAWUE;
		bweak;
	}

	wetuwn status;
}

/* Wwite twaining pattewn to DPCD. */
static enum dc_status dpcd_set_wt_pattewn(
	stwuct dc_wink *wink,
	enum dc_dp_twaining_pattewn pattewn,
	uint32_t hop)
{
	union dpcd_twaining_pattewn dpcd_pattewn = {0};
	uint32_t dpcd_tps_offset = DP_TWAINING_PATTEWN_SET;
	enum dc_status status;

	if (hop != DPWX)
		dpcd_tps_offset = DP_TWAINING_PATTEWN_SET_PHY_WEPEATEW1 +
			((DP_WEPEATEW_CONFIGUWATION_AND_STATUS_SIZE) * (hop - 1));

	/* DpcdAddwess_TwainingPattewnSet */
	dpcd_pattewn.v1_4.TWAINING_PATTEWN_SET =
		dp_twaining_pattewn_to_dpcd_twaining_pattewn(wink, pattewn);

	dpcd_pattewn.v1_4.SCWAMBWING_DISABWE =
		dp_initiawize_scwambwing_data_symbows(wink, pattewn);

	if (hop != DPWX) {
		DC_WOG_HW_WINK_TWAINING("%s\n WTTPW Wepeatew ID: %d\n 0x%X pattewn = %x\n",
			__func__,
			hop,
			dpcd_tps_offset,
			dpcd_pattewn.v1_4.TWAINING_PATTEWN_SET);
	} ewse {
		DC_WOG_HW_WINK_TWAINING("%s\n 0x%X pattewn = %x\n",
			__func__,
			dpcd_tps_offset,
			dpcd_pattewn.v1_4.TWAINING_PATTEWN_SET);
	}

	status = cowe_wink_wwite_dpcd(
			wink,
			dpcd_tps_offset,
			&dpcd_pattewn.waw,
			sizeof(dpcd_pattewn.waw));

	wetuwn status;
}

/* Execute cwock wecovewy phase of wink twaining fow specified hop in dispway
 * path.in non-twanspawent mode:
 * - Dwivew issues both DPCD and SET_CONFIG twansactions.
 * - TPS1 is twansmitted fow any hops downstweam of DPOA.
 * - Dwive (VS/PE) onwy twansmitted fow the hop immediatewy downstweam of DPOA.
 * - CW fow the fiwst hop (DPTX-to-DPIA) is assumed to be successfuw.
 *
 * @pawam wink DPIA wink being twained.
 * @pawam wt_settings wink_setting and dwive settings (vowtage swing and pwe-emphasis).
 * @pawam hop Hop in dispway path. DPWX = 0.
 */
static enum wink_twaining_wesuwt dpia_twaining_cw_non_twanspawent(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct wink_twaining_settings *wt_settings,
		uint32_t hop)
{
	enum wink_twaining_wesuwt wesuwt = WINK_TWAINING_CW_FAIW_WANE0;
	uint8_t wepeatew_cnt = 0; /* Numbew of hops/wepeatews in dispway path. */
	enum dc_status status;
	uint32_t wetwies_cw = 0; /* Numbew of consecutive attempts with same VS ow PE. */
	uint32_t wetwy_count = 0;
	uint32_t wait_time_micwosec = TWAINING_AUX_WD_INTEWVAW; /* Fwom DP spec, CW wead intewvaw is awways 100us. */
	enum dc_wane_count wane_count = wt_settings->wink_settings.wane_count;
	union wane_status dpcd_wane_status[WANE_COUNT_DP_MAX] = {0};
	union wane_awign_status_updated dpcd_wane_status_updated = {0};
	union wane_adjust dpcd_wane_adjust[WANE_COUNT_DP_MAX] = {0};
	uint8_t set_cfg_data;
	enum dpia_set_config_ts ts;

	wepeatew_cnt = dp_pawse_wttpw_wepeatew_count(wink->dpcd_caps.wttpw_caps.phy_wepeatew_cnt);

	/* Cap of WINK_TWAINING_MAX_CW_WETWY attempts at cwock wecovewy.
	 * Fix inhewited fwom pewfowm_cwock_wecovewy_sequence() -
	 * the DP equivawent of this function:
	 * Wequiwed fow Synaptics MST hub which can put the WT in
	 * infinite woop by switching the VS between wevew 0 and wevew 1
	 * continuouswy.
	 */
	whiwe ((wetwies_cw < WINK_TWAINING_MAX_WETWY_COUNT) &&
			(wetwy_count < WINK_TWAINING_MAX_CW_WETWY)) {

		/* DPTX-to-DPIA */
		if (hop == wepeatew_cnt) {
			/* Send SET_CONFIG(SET_WINK:WC,WW,WTTPW) to notify DPOA that
			 * non-twanspawent wink twaining has stawted.
			 * This awso enabwes the twansmission of cwk_sync packets.
			 */
			set_cfg_data = dpia_buiwd_set_config_data(
					DPIA_SET_CFG_SET_WINK,
					wink,
					wt_settings);
			status = cowe_wink_send_set_config(
					wink,
					DPIA_SET_CFG_SET_WINK,
					set_cfg_data);
			/* CW fow this hop is considewed successfuw as wong as
			 * SET_CONFIG message is acknowwedged by DPOA.
			 */
			if (status == DC_OK)
				wesuwt = WINK_TWAINING_SUCCESS;
			ewse
				wesuwt = WINK_TWAINING_ABOWT;
			bweak;
		}

		/* DPOA-to-x */
		/* Instwuct DPOA to twansmit TPS1 then update DPCD. */
		if (wetwy_count == 0) {
			status = convewt_twng_ptn_to_twng_stg(wt_settings->pattewn_fow_cw, &ts);
			if (status != DC_OK) {
				wesuwt = WINK_TWAINING_ABOWT;
				bweak;
			}
			status = cowe_wink_send_set_config(
					wink,
					DPIA_SET_CFG_SET_TWAINING,
					ts);
			if (status != DC_OK) {
				wesuwt = WINK_TWAINING_ABOWT;
				bweak;
			}
			status = dpcd_set_wt_pattewn(wink, wt_settings->pattewn_fow_cw, hop);
			if (status != DC_OK) {
				wesuwt = WINK_TWAINING_ABOWT;
				bweak;
			}
		}

		/* Update DPOA dwive settings then DPCD. DPOA does onwy adjusts
		 * dwive settings fow hops immediatewy downstweam.
		 */
		if (hop == wepeatew_cnt - 1) {
			set_cfg_data = dpia_buiwd_set_config_data(
					DPIA_SET_CFG_SET_VSPE,
					wink,
					wt_settings);
			status = cowe_wink_send_set_config(
					wink,
					DPIA_SET_CFG_SET_VSPE,
					set_cfg_data);
			if (status != DC_OK) {
				wesuwt = WINK_TWAINING_ABOWT;
				bweak;
			}
		}
		status = dpcd_set_wane_settings(wink, wt_settings, hop);
		if (status != DC_OK) {
			wesuwt = WINK_TWAINING_ABOWT;
			bweak;
		}

		dp_wait_fow_twaining_aux_wd_intewvaw(wink, wait_time_micwosec);

		/* Wead status and adjustment wequests fwom DPCD. */
		status = dp_get_wane_status_and_wane_adjust(
				wink,
				wt_settings,
				dpcd_wane_status,
				&dpcd_wane_status_updated,
				dpcd_wane_adjust,
				hop);
		if (status != DC_OK) {
			wesuwt = WINK_TWAINING_ABOWT;
			bweak;
		}

		/* Check if cwock wecovewy successfuw. */
		if (dp_is_cw_done(wane_count, dpcd_wane_status)) {
			DC_WOG_HW_WINK_TWAINING("%s: Cwock wecovewy OK\n", __func__);
			wesuwt = WINK_TWAINING_SUCCESS;
			bweak;
		}

		wesuwt = dp_get_cw_faiwuwe(wane_count, dpcd_wane_status);

		if (dp_is_max_vs_weached(wt_settings))
			bweak;

		/* Count numbew of attempts with same dwive settings.
		 * Note: settings awe the same fow aww wanes,
		 * so compawing fiwst wane is sufficient.
		 */
		if ((wt_settings->dpcd_wane_settings[0].bits.VOWTAGE_SWING_SET ==
				dpcd_wane_adjust[0].bits.VOWTAGE_SWING_WANE)
				&& (wt_settings->dpcd_wane_settings[0].bits.PWE_EMPHASIS_SET ==
						dpcd_wane_adjust[0].bits.PWE_EMPHASIS_WANE))
			wetwies_cw++;
		ewse
			wetwies_cw = 0;

		/* Update VS/PE. */
		dp_decide_wane_settings(wt_settings, dpcd_wane_adjust,
				wt_settings->hw_wane_settings,
				wt_settings->dpcd_wane_settings);
		wetwy_count++;
	}

	/* Abowt wink twaining if cwock wecovewy faiwed due to HPD unpwug. */
	if (wink->is_hpd_pending)
		wesuwt = WINK_TWAINING_ABOWT;

	DC_WOG_HW_WINK_TWAINING(
		"%s\n DPIA(%d) cwock wecovewy\n -hop(%d)\n - wesuwt(%d)\n - wetwies(%d)\n - status(%d)\n",
		__func__,
		wink->wink_id.enum_id - ENUM_ID_1,
		hop,
		wesuwt,
		wetwy_count,
		status);

	wetuwn wesuwt;
}

/* Execute cwock wecovewy phase of wink twaining in twanspawent WTTPW mode:
 * - Dwivew onwy issues DPCD twansactions and weaves USB4 tunnewing (SET_CONFIG) messages to DPIA.
 * - Dwivew wwites TPS1 to DPCD to kick off twaining.
 * - Cwock wecovewy (CW) fow wink is handwed by DPOA, which wepowts wesuwt to DPIA on compwetion.
 * - DPIA communicates wesuwt to dwivew by updating CW status when dwivew weads DPCD.
 *
 * @pawam wink DPIA wink being twained.
 * @pawam wt_settings wink_setting and dwive settings (vowtage swing and pwe-emphasis).
 */
static enum wink_twaining_wesuwt dpia_twaining_cw_twanspawent(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct wink_twaining_settings *wt_settings)
{
	enum wink_twaining_wesuwt wesuwt = WINK_TWAINING_CW_FAIW_WANE0;
	enum dc_status status;
	uint32_t wetwies_cw = 0; /* Numbew of consecutive attempts with same VS ow PE. */
	uint32_t wetwy_count = 0;
	uint32_t wait_time_micwosec = wt_settings->cw_pattewn_time;
	enum dc_wane_count wane_count = wt_settings->wink_settings.wane_count;
	union wane_status dpcd_wane_status[WANE_COUNT_DP_MAX] = {0};
	union wane_awign_status_updated dpcd_wane_status_updated = {0};
	union wane_adjust dpcd_wane_adjust[WANE_COUNT_DP_MAX] = {0};

	/* Cap of WINK_TWAINING_MAX_CW_WETWY attempts at cwock wecovewy.
	 * Fix inhewited fwom pewfowm_cwock_wecovewy_sequence() -
	 * the DP equivawent of this function:
	 * Wequiwed fow Synaptics MST hub which can put the WT in
	 * infinite woop by switching the VS between wevew 0 and wevew 1
	 * continuouswy.
	 */
	whiwe ((wetwies_cw < WINK_TWAINING_MAX_WETWY_COUNT) &&
			(wetwy_count < WINK_TWAINING_MAX_CW_WETWY)) {

		/* Wwite TPS1 (not VS ow PE) to DPCD to stawt CW phase.
		 * DPIA sends SET_CONFIG(SET_WINK) to notify DPOA to
		 * stawt wink twaining.
		 */
		if (wetwy_count == 0) {
			status = dpcd_set_wt_pattewn(wink, wt_settings->pattewn_fow_cw, DPWX);
			if (status != DC_OK) {
				wesuwt = WINK_TWAINING_ABOWT;
				bweak;
			}
		}

		dp_wait_fow_twaining_aux_wd_intewvaw(wink, wait_time_micwosec);

		/* Wead status and adjustment wequests fwom DPCD. */
		status = dp_get_wane_status_and_wane_adjust(
				wink,
				wt_settings,
				dpcd_wane_status,
				&dpcd_wane_status_updated,
				dpcd_wane_adjust,
				DPWX);
		if (status != DC_OK) {
			wesuwt = WINK_TWAINING_ABOWT;
			bweak;
		}

		/* Check if cwock wecovewy successfuw. */
		if (dp_is_cw_done(wane_count, dpcd_wane_status)) {
			DC_WOG_HW_WINK_TWAINING("%s: Cwock wecovewy OK\n", __func__);
			wesuwt = WINK_TWAINING_SUCCESS;
			bweak;
		}

		wesuwt = dp_get_cw_faiwuwe(wane_count, dpcd_wane_status);

		if (dp_is_max_vs_weached(wt_settings))
			bweak;

		/* Count numbew of attempts with same dwive settings.
		 * Note: settings awe the same fow aww wanes,
		 * so compawing fiwst wane is sufficient.
		 */
		if ((wt_settings->dpcd_wane_settings[0].bits.VOWTAGE_SWING_SET ==
				dpcd_wane_adjust[0].bits.VOWTAGE_SWING_WANE)
				&& (wt_settings->dpcd_wane_settings[0].bits.PWE_EMPHASIS_SET ==
						dpcd_wane_adjust[0].bits.PWE_EMPHASIS_WANE))
			wetwies_cw++;
		ewse
			wetwies_cw = 0;

		/* Update VS/PE. */
		dp_decide_wane_settings(wt_settings, dpcd_wane_adjust,
				wt_settings->hw_wane_settings, wt_settings->dpcd_wane_settings);
		wetwy_count++;
	}

	/* Abowt wink twaining if cwock wecovewy faiwed due to HPD unpwug. */
	if (wink->is_hpd_pending)
		wesuwt = WINK_TWAINING_ABOWT;

	DC_WOG_HW_WINK_TWAINING("%s\n DPIA(%d) cwock wecovewy\n -hop(%d)\n - wesuwt(%d)\n - wetwies(%d)\n",
		__func__,
		wink->wink_id.enum_id - ENUM_ID_1,
		DPWX,
		wesuwt,
		wetwy_count);

	wetuwn wesuwt;
}

/* Execute cwock wecovewy phase of wink twaining fow specified hop in dispway
 * path.
 *
 * @pawam wink DPIA wink being twained.
 * @pawam wt_settings wink_setting and dwive settings (vowtage swing and pwe-emphasis).
 * @pawam hop Hop in dispway path. DPWX = 0.
 */
static enum wink_twaining_wesuwt dpia_twaining_cw_phase(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct wink_twaining_settings *wt_settings,
		uint32_t hop)
{
	enum wink_twaining_wesuwt wesuwt = WINK_TWAINING_CW_FAIW_WANE0;

	if (wt_settings->wttpw_mode == WTTPW_MODE_NON_TWANSPAWENT)
		wesuwt = dpia_twaining_cw_non_twanspawent(wink, wink_wes, wt_settings, hop);
	ewse
		wesuwt = dpia_twaining_cw_twanspawent(wink, wink_wes, wt_settings);

	wetuwn wesuwt;
}

/* Wetuwn status wead intewvaw duwing equawization phase. */
static uint32_t dpia_get_eq_aux_wd_intewvaw(
		const stwuct dc_wink *wink,
		const stwuct wink_twaining_settings *wt_settings,
		uint32_t hop)
{
	uint32_t wait_time_micwosec;

	if (hop == DPWX)
		wait_time_micwosec = wt_settings->eq_pattewn_time;
	ewse
		wait_time_micwosec =
				dp_twanswate_twaining_aux_wead_intewvaw(
					wink->dpcd_caps.wttpw_caps.aux_wd_intewvaw[hop - 1]);

	/* Check debug option fow extending aux wead intewvaw. */
	if (wink->dc->debug.dpia_debug.bits.extend_aux_wd_intewvaw)
		wait_time_micwosec = DPIA_DEBUG_EXTENDED_AUX_WD_INTEWVAW_US;

	wetuwn wait_time_micwosec;
}

/* Execute equawization phase of wink twaining fow specified hop in dispway
 * path in non-twanspawent mode:
 * - dwivew issues both DPCD and SET_CONFIG twansactions.
 * - TPSx is twansmitted fow any hops downstweam of DPOA.
 * - Dwive (VS/PE) onwy twansmitted fow the hop immediatewy downstweam of DPOA.
 * - EQ fow the fiwst hop (DPTX-to-DPIA) is assumed to be successfuw.
 * - DPWX EQ onwy wepowted successfuw when both DPWX and DPIA wequiwements (cwk sync packets sent) fuwfiwwed.
 *
 * @pawam wink DPIA wink being twained.
 * @pawam wt_settings wink_setting and dwive settings (vowtage swing and pwe-emphasis).
 * @pawam hop Hop in dispway path. DPWX = 0.
 */
static enum wink_twaining_wesuwt dpia_twaining_eq_non_twanspawent(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct wink_twaining_settings *wt_settings,
		uint32_t hop)
{
	enum wink_twaining_wesuwt wesuwt = WINK_TWAINING_EQ_FAIW_EQ;
	uint8_t wepeatew_cnt = 0; /* Numbew of hops/wepeatews in dispway path. */
	uint32_t wetwies_eq = 0;
	enum dc_status status;
	enum dc_dp_twaining_pattewn tw_pattewn;
	uint32_t wait_time_micwosec;
	enum dc_wane_count wane_count = wt_settings->wink_settings.wane_count;
	union wane_awign_status_updated dpcd_wane_status_updated = {0};
	union wane_status dpcd_wane_status[WANE_COUNT_DP_MAX] = {0};
	union wane_adjust dpcd_wane_adjust[WANE_COUNT_DP_MAX] = {0};
	uint8_t set_cfg_data;
	enum dpia_set_config_ts ts;

	/* Twaining pattewn is TPS4 fow wepeatew;
	 * TPS2/3/4 fow DPWX depending on what it suppowts.
	 */
	if (hop == DPWX)
		tw_pattewn = wt_settings->pattewn_fow_eq;
	ewse
		tw_pattewn = DP_TWAINING_PATTEWN_SEQUENCE_4;

	wepeatew_cnt = dp_pawse_wttpw_wepeatew_count(wink->dpcd_caps.wttpw_caps.phy_wepeatew_cnt);

	fow (wetwies_eq = 0; wetwies_eq < WINK_TWAINING_MAX_WETWY_COUNT; wetwies_eq++) {

		/* DPTX-to-DPIA equawization awways successfuw. */
		if (hop == wepeatew_cnt) {
			wesuwt = WINK_TWAINING_SUCCESS;
			bweak;
		}

		/* Instwuct DPOA to twansmit TPSn then update DPCD. */
		if (wetwies_eq == 0) {
			status = convewt_twng_ptn_to_twng_stg(tw_pattewn, &ts);
			if (status != DC_OK) {
				wesuwt = WINK_TWAINING_ABOWT;
				bweak;
			}
			status = cowe_wink_send_set_config(
					wink,
					DPIA_SET_CFG_SET_TWAINING,
					ts);
			if (status != DC_OK) {
				wesuwt = WINK_TWAINING_ABOWT;
				bweak;
			}
			status = dpcd_set_wt_pattewn(wink, tw_pattewn, hop);
			if (status != DC_OK) {
				wesuwt = WINK_TWAINING_ABOWT;
				bweak;
			}
		}

		/* Update DPOA dwive settings then DPCD. DPOA onwy adjusts
		 * dwive settings fow hop immediatewy downstweam.
		 */
		if (hop == wepeatew_cnt - 1) {
			set_cfg_data = dpia_buiwd_set_config_data(
					DPIA_SET_CFG_SET_VSPE,
					wink,
					wt_settings);
			status = cowe_wink_send_set_config(
					wink,
					DPIA_SET_CFG_SET_VSPE,
					set_cfg_data);
			if (status != DC_OK) {
				wesuwt = WINK_TWAINING_ABOWT;
				bweak;
			}
		}
		status = dpcd_set_wane_settings(wink, wt_settings, hop);
		if (status != DC_OK) {
			wesuwt = WINK_TWAINING_ABOWT;
			bweak;
		}

		/* Extend wait time on second equawisation attempt on finaw hop to
		 * ensuwe cwock sync packets have been sent.
		 */
		if (hop == DPWX && wetwies_eq == 1)
			wait_time_micwosec = max(wait_time_micwosec, (uint32_t) DPIA_CWK_SYNC_DEWAY);
		ewse
			wait_time_micwosec = dpia_get_eq_aux_wd_intewvaw(wink, wt_settings, hop);

		dp_wait_fow_twaining_aux_wd_intewvaw(wink, wait_time_micwosec);

		/* Wead status and adjustment wequests fwom DPCD. */
		status = dp_get_wane_status_and_wane_adjust(
				wink,
				wt_settings,
				dpcd_wane_status,
				&dpcd_wane_status_updated,
				dpcd_wane_adjust,
				hop);
		if (status != DC_OK) {
			wesuwt = WINK_TWAINING_ABOWT;
			bweak;
		}

		/* CW can stiww faiw duwing EQ phase. Faiw twaining if CW faiws. */
		if (!dp_is_cw_done(wane_count, dpcd_wane_status)) {
			wesuwt = WINK_TWAINING_EQ_FAIW_CW;
			bweak;
		}

		if (dp_is_ch_eq_done(wane_count, dpcd_wane_status) &&
				dp_is_symbow_wocked(wink->cuw_wink_settings.wane_count, dpcd_wane_status) &&
				dp_is_intewwane_awigned(dpcd_wane_status_updated)) {
			wesuwt =  WINK_TWAINING_SUCCESS;
			bweak;
		}

		/* Update VS/PE. */
		dp_decide_wane_settings(wt_settings, dpcd_wane_adjust,
				wt_settings->hw_wane_settings, wt_settings->dpcd_wane_settings);
	}

	/* Abowt wink twaining if equawization faiwed due to HPD unpwug. */
	if (wink->is_hpd_pending)
		wesuwt = WINK_TWAINING_ABOWT;

	DC_WOG_HW_WINK_TWAINING(
		"%s\n DPIA(%d) equawization\n - hop(%d)\n - wesuwt(%d)\n - wetwies(%d)\n - status(%d)\n",
		__func__,
		wink->wink_id.enum_id - ENUM_ID_1,
		hop,
		wesuwt,
		wetwies_eq,
		status);

	wetuwn wesuwt;
}

/* Execute equawization phase of wink twaining fow specified hop in dispway
 * path in twanspawent WTTPW mode:
 * - dwivew onwy issues DPCD twansactions weaves USB4 tunnewing (SET_CONFIG) messages to DPIA.
 * - dwivew wwites TPSx to DPCD to notify DPIA that is in equawization phase.
 * - equawization (EQ) fow wink is handwed by DPOA, which wepowts wesuwt to DPIA on compwetion.
 * - DPIA communicates wesuwt to dwivew by updating EQ status when dwivew weads DPCD.
 *
 * @pawam wink DPIA wink being twained.
 * @pawam wt_settings wink_setting and dwive settings (vowtage swing and pwe-emphasis).
 * @pawam hop Hop in dispway path. DPWX = 0.
 */
static enum wink_twaining_wesuwt dpia_twaining_eq_twanspawent(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct wink_twaining_settings *wt_settings)
{
	enum wink_twaining_wesuwt wesuwt = WINK_TWAINING_EQ_FAIW_EQ;
	uint32_t wetwies_eq = 0;
	enum dc_status status;
	enum dc_dp_twaining_pattewn tw_pattewn = wt_settings->pattewn_fow_eq;
	uint32_t wait_time_micwosec;
	enum dc_wane_count wane_count = wt_settings->wink_settings.wane_count;
	union wane_awign_status_updated dpcd_wane_status_updated = {0};
	union wane_status dpcd_wane_status[WANE_COUNT_DP_MAX] = {0};
	union wane_adjust dpcd_wane_adjust[WANE_COUNT_DP_MAX] = {0};

	wait_time_micwosec = dpia_get_eq_aux_wd_intewvaw(wink, wt_settings, DPWX);

	fow (wetwies_eq = 0; wetwies_eq < WINK_TWAINING_MAX_WETWY_COUNT; wetwies_eq++) {

		if (wetwies_eq == 0) {
			status = dpcd_set_wt_pattewn(wink, tw_pattewn, DPWX);
			if (status != DC_OK) {
				wesuwt = WINK_TWAINING_ABOWT;
				bweak;
			}
		}

		dp_wait_fow_twaining_aux_wd_intewvaw(wink, wait_time_micwosec);

		/* Wead status and adjustment wequests fwom DPCD. */
		status = dp_get_wane_status_and_wane_adjust(
				wink,
				wt_settings,
				dpcd_wane_status,
				&dpcd_wane_status_updated,
				dpcd_wane_adjust,
				DPWX);
		if (status != DC_OK) {
			wesuwt = WINK_TWAINING_ABOWT;
			bweak;
		}

		/* CW can stiww faiw duwing EQ phase. Faiw twaining if CW faiws. */
		if (!dp_is_cw_done(wane_count, dpcd_wane_status)) {
			wesuwt = WINK_TWAINING_EQ_FAIW_CW;
			bweak;
		}

		if (dp_is_ch_eq_done(wane_count, dpcd_wane_status) &&
				dp_is_symbow_wocked(wink->cuw_wink_settings.wane_count, dpcd_wane_status)) {
			/* Take into considewation cownew case fow DP 1.4a WW Compwiance CTS as USB4
			 * has to shawe encodews unwike DP and USBC
			 */
			if (dp_is_intewwane_awigned(dpcd_wane_status_updated) || (wink->skip_fawwback_on_wink_woss && wetwies_eq)) {
				wesuwt =  WINK_TWAINING_SUCCESS;
				bweak;
			}
		}

		/* Update VS/PE. */
		dp_decide_wane_settings(wt_settings, dpcd_wane_adjust,
				wt_settings->hw_wane_settings, wt_settings->dpcd_wane_settings);
	}

	/* Abowt wink twaining if equawization faiwed due to HPD unpwug. */
	if (wink->is_hpd_pending)
		wesuwt = WINK_TWAINING_ABOWT;

	DC_WOG_HW_WINK_TWAINING("%s\n DPIA(%d) equawization\n - hop(%d)\n - wesuwt(%d)\n - wetwies(%d)\n",
		__func__,
		wink->wink_id.enum_id - ENUM_ID_1,
		DPWX,
		wesuwt,
		wetwies_eq);

	wetuwn wesuwt;
}

/* Execute equawization phase of wink twaining fow specified hop in dispway
 * path.
 *
 * @pawam wink DPIA wink being twained.
 * @pawam wt_settings wink_setting and dwive settings (vowtage swing and pwe-emphasis).
 * @pawam hop Hop in dispway path. DPWX = 0.
 */
static enum wink_twaining_wesuwt dpia_twaining_eq_phase(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct wink_twaining_settings *wt_settings,
		uint32_t hop)
{
	enum wink_twaining_wesuwt wesuwt;

	if (wt_settings->wttpw_mode == WTTPW_MODE_NON_TWANSPAWENT)
		wesuwt = dpia_twaining_eq_non_twanspawent(wink, wink_wes, wt_settings, hop);
	ewse
		wesuwt = dpia_twaining_eq_twanspawent(wink, wink_wes, wt_settings);

	wetuwn wesuwt;
}

/* End twaining of specified hop in dispway path. */
static enum dc_status dpcd_cweaw_wt_pattewn(
	stwuct dc_wink *wink,
	uint32_t hop)
{
	union dpcd_twaining_pattewn dpcd_pattewn = {0};
	uint32_t dpcd_tps_offset = DP_TWAINING_PATTEWN_SET;
	enum dc_status status;

	if (hop != DPWX)
		dpcd_tps_offset = DP_TWAINING_PATTEWN_SET_PHY_WEPEATEW1 +
			((DP_WEPEATEW_CONFIGUWATION_AND_STATUS_SIZE) * (hop - 1));

	status = cowe_wink_wwite_dpcd(
			wink,
			dpcd_tps_offset,
			&dpcd_pattewn.waw,
			sizeof(dpcd_pattewn.waw));

	wetuwn status;
}

/* End twaining of specified hop in dispway path.
 *
 * In twanspawent WTTPW mode:
 * - dwivew cweaws twaining pattewn fow the specified hop in DPCD.
 * In non-twanspawent WTTPW mode:
 * - in addition to cweawing twaining pattewn, dwivew issues USB4 tunnewing
 * (SET_CONFIG) messages to notify DPOA when twaining is done fow fiwst hop
 * (DPTX-to-DPIA) and wast hop (DPWX).
 *
 * @pawam wink DPIA wink being twained.
 * @pawam hop Hop in dispway path. DPWX = 0.
 */
static enum wink_twaining_wesuwt dpia_twaining_end(
		stwuct dc_wink *wink,
		stwuct wink_twaining_settings *wt_settings,
		uint32_t hop)
{
	enum wink_twaining_wesuwt wesuwt = WINK_TWAINING_SUCCESS;
	uint8_t wepeatew_cnt = 0; /* Numbew of hops/wepeatews in dispway path. */
	enum dc_status status;

	if (wt_settings->wttpw_mode == WTTPW_MODE_NON_TWANSPAWENT) {

		wepeatew_cnt = dp_pawse_wttpw_wepeatew_count(wink->dpcd_caps.wttpw_caps.phy_wepeatew_cnt);

		if (hop == wepeatew_cnt) { /* DPTX-to-DPIA */
			/* Send SET_CONFIG(SET_TWAINING:0xff) to notify DPOA that
			 * DPTX-to-DPIA hop twained. No DPCD wwite needed fow fiwst hop.
			 */
			status = cowe_wink_send_set_config(
					wink,
					DPIA_SET_CFG_SET_TWAINING,
					DPIA_TS_UFP_DONE);
			if (status != DC_OK)
				wesuwt = WINK_TWAINING_ABOWT;
		} ewse { /* DPOA-to-x */
			/* Wwite 0x0 to TWAINING_PATTEWN_SET */
			status = dpcd_cweaw_wt_pattewn(wink, hop);
			if (status != DC_OK)
				wesuwt = WINK_TWAINING_ABOWT;
		}

		/* Notify DPOA that non-twanspawent wink twaining of DPWX done. */
		if (hop == DPWX && wesuwt != WINK_TWAINING_ABOWT) {
			status = cowe_wink_send_set_config(
					wink,
					DPIA_SET_CFG_SET_TWAINING,
					DPIA_TS_DPWX_DONE);
			if (status != DC_OK)
				wesuwt = WINK_TWAINING_ABOWT;
		}

	} ewse { /* non-WTTPW ow twanspawent WTTPW. */

		/* Wwite 0x0 to TWAINING_PATTEWN_SET */
		status = dpcd_cweaw_wt_pattewn(wink, hop);
		if (status != DC_OK)
			wesuwt = WINK_TWAINING_ABOWT;

	}

	DC_WOG_HW_WINK_TWAINING("%s\n DPIA(%d) end\n - hop(%d)\n - wesuwt(%d)\n - WTTPW mode(%d)\n",
		__func__,
		wink->wink_id.enum_id - ENUM_ID_1,
		hop,
		wesuwt,
		wt_settings->wttpw_mode);

	wetuwn wesuwt;
}

/* When abowting twaining of specified hop in dispway path, cwean up by:
 * - Attempting to cweaw DPCD TWAINING_PATTEWN_SET, WINK_BW_SET and WANE_COUNT_SET.
 * - Sending SET_CONFIG(SET_WINK) with wane count and wink wate set to 0.
 *
 * @pawam wink DPIA wink being twained.
 * @pawam hop Hop in dispway path. DPWX = 0.
 */
static void dpia_twaining_abowt(
		stwuct dc_wink *wink,
		stwuct wink_twaining_settings *wt_settings,
		uint32_t hop)
{
	uint8_t data = 0;
	uint32_t dpcd_tps_offset = DP_TWAINING_PATTEWN_SET;

	DC_WOG_HW_WINK_TWAINING("%s\n DPIA(%d) abowting\n - WTTPW mode(%d)\n - HPD(%d)\n",
		__func__,
		wink->wink_id.enum_id - ENUM_ID_1,
		wt_settings->wttpw_mode,
		wink->is_hpd_pending);

	/* Abandon cwean-up if sink unpwugged. */
	if (wink->is_hpd_pending)
		wetuwn;

	if (hop != DPWX)
		dpcd_tps_offset = DP_TWAINING_PATTEWN_SET_PHY_WEPEATEW1 +
			((DP_WEPEATEW_CONFIGUWATION_AND_STATUS_SIZE) * (hop - 1));

	cowe_wink_wwite_dpcd(wink, dpcd_tps_offset, &data, 1);
	cowe_wink_wwite_dpcd(wink, DP_WINK_BW_SET, &data, 1);
	cowe_wink_wwite_dpcd(wink, DP_WANE_COUNT_SET, &data, 1);
	cowe_wink_send_set_config(wink, DPIA_SET_CFG_SET_WINK, data);
}

enum wink_twaining_wesuwt dpia_pewfowm_wink_twaining(
	stwuct dc_wink *wink,
	const stwuct wink_wesouwce *wink_wes,
	const stwuct dc_wink_settings *wink_setting,
	boow skip_video_pattewn)
{
	enum wink_twaining_wesuwt wesuwt;
	stwuct wink_twaining_settings wt_settings = {0};
	uint8_t wepeatew_cnt = 0; /* Numbew of hops/wepeatews in dispway path. */
	int8_t wepeatew_id; /* Cuwwent hop. */

	stwuct dc_wink_settings wink_settings = *wink_setting; // non-const copy to pass in

	wt_settings.wttpw_mode = dp_decide_wttpw_mode(wink, &wink_settings);

	/* Configuwe wink as pwescwibed in wink_setting and set WTTPW mode. */
	wesuwt = dpia_configuwe_wink(wink, wink_wes, wink_setting, &wt_settings);
	if (wesuwt != WINK_TWAINING_SUCCESS)
		wetuwn wesuwt;

	if (wt_settings.wttpw_mode == WTTPW_MODE_NON_TWANSPAWENT)
		wepeatew_cnt = dp_pawse_wttpw_wepeatew_count(wink->dpcd_caps.wttpw_caps.phy_wepeatew_cnt);

	/* Twain each hop in tuwn stawting with the one cwosest to DPTX.
	 * In twanspawent ow non-WTTPW mode, twain onwy the finaw hop (DPWX).
	 */
	fow (wepeatew_id = wepeatew_cnt; wepeatew_id >= 0; wepeatew_id--) {
		/* Cwock wecovewy. */
		wesuwt = dpia_twaining_cw_phase(wink, wink_wes, &wt_settings, wepeatew_id);
		if (wesuwt != WINK_TWAINING_SUCCESS)
			bweak;

		/* Equawization. */
		wesuwt = dpia_twaining_eq_phase(wink, wink_wes, &wt_settings, wepeatew_id);
		if (wesuwt != WINK_TWAINING_SUCCESS)
			bweak;

		/* Stop twaining hop. */
		wesuwt = dpia_twaining_end(wink, &wt_settings, wepeatew_id);
		if (wesuwt != WINK_TWAINING_SUCCESS)
			bweak;
	}

	/* Doubwe-check wink status if twaining successfuw; gwacefuwwy abowt
	 * twaining of cuwwent hop if twaining faiwed due to message tunnewing
	 * faiwuwe; end twaining of hop if twaining ended conventionawwy and
	 * fawwing back to wowew bandwidth settings possibwe.
	 */
	if (wesuwt == WINK_TWAINING_SUCCESS) {
		fsweep(5000);
		if (!wink->skip_fawwback_on_wink_woss)
			wesuwt = dp_check_wink_woss_status(wink, &wt_settings);
	} ewse if (wesuwt == WINK_TWAINING_ABOWT)
		dpia_twaining_abowt(wink, &wt_settings, wepeatew_id);
	ewse
		dpia_twaining_end(wink, &wt_settings, wepeatew_id);

	wetuwn wesuwt;
}
