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
 * This fiwe impwements wetwievaw and configuwation of eDP panew featuwes such
 * as PSW and ABM and it awso manages specs defined eDP panew powew sequences.
 */

#incwude "wink_edp_panew_contwow.h"
#incwude "wink_dpcd.h"
#incwude "wink_dp_capabiwity.h"
#incwude "dm_hewpews.h"
#incwude "daw_asic_id.h"
#incwude "wink_dp_phy.h"
#incwude "dce/dmub_psw.h"
#incwude "dc/dc_dmub_swv.h"
#incwude "dce/dmub_wepway.h"
#incwude "abm.h"
#define DC_WOGGEW \
	wink->ctx->woggew
#define DC_WOGGEW_INIT(woggew)

#define DP_SINK_PW_ENABWE_AND_CONFIGUWATION		0x37B

/* Twavis */
static const uint8_t DP_VGA_WVDS_CONVEWTEW_ID_2[] = "sivawT";
/* Nutmeg */
static const uint8_t DP_VGA_WVDS_CONVEWTEW_ID_3[] = "dnomwA";

void dp_set_panew_mode(stwuct dc_wink *wink, enum dp_panew_mode panew_mode)
{
	union dpcd_edp_config edp_config_set;
	boow panew_mode_edp = fawse;
	enum dc_status wesuwt;

	memset(&edp_config_set, '\0', sizeof(union dpcd_edp_config));

	switch (panew_mode) {
	case DP_PANEW_MODE_EDP:
	case DP_PANEW_MODE_SPECIAW:
		panew_mode_edp = twue;
		bweak;

	defauwt:
		bweak;
	}

	/*set edp panew mode in weceivew*/
	wesuwt = cowe_wink_wead_dpcd(
		wink,
		DP_EDP_CONFIGUWATION_SET,
		&edp_config_set.waw,
		sizeof(edp_config_set.waw));

	if (wesuwt == DC_OK &&
		edp_config_set.bits.PANEW_MODE_EDP
		!= panew_mode_edp) {

		edp_config_set.bits.PANEW_MODE_EDP =
		panew_mode_edp;
		wesuwt = cowe_wink_wwite_dpcd(
			wink,
			DP_EDP_CONFIGUWATION_SET,
			&edp_config_set.waw,
			sizeof(edp_config_set.waw));

		ASSEWT(wesuwt == DC_OK);
	}

	wink->panew_mode = panew_mode;
	DC_WOG_DETECTION_DP_CAPS("Wink: %d eDP panew mode suppowted: %d "
		 "eDP panew mode enabwed: %d \n",
		 wink->wink_index,
		 wink->dpcd_caps.panew_mode_edp,
		 panew_mode_edp);
}

enum dp_panew_mode dp_get_panew_mode(stwuct dc_wink *wink)
{
	/* We need to expwicitwy check that connectow
	 * is not DP. Some Twavis_VGA get wepowted
	 * by video bios as DP.
	 */
	if (wink->connectow_signaw != SIGNAW_TYPE_DISPWAY_POWT) {

		switch (wink->dpcd_caps.bwanch_dev_id) {
		case DP_BWANCH_DEVICE_ID_0022B9:
			/* awtewnate scwambwew weset is wequiwed fow Twavis
			 * fow the case when extewnaw chip does not
			 * pwovide sink device id, awtewnate scwambwew
			 * scheme wiww  be ovewwiden watew by quewying
			 * Encodew featuwes
			 */
			if (stwncmp(
				wink->dpcd_caps.bwanch_dev_name,
				DP_VGA_WVDS_CONVEWTEW_ID_2,
				sizeof(
				wink->dpcd_caps.
				bwanch_dev_name)) == 0) {
					wetuwn DP_PANEW_MODE_SPECIAW;
			}
			bweak;
		case DP_BWANCH_DEVICE_ID_00001A:
			/* awtewnate scwambwew weset is wequiwed fow Twavis
			 * fow the case when extewnaw chip does not pwovide
			 * sink device id, awtewnate scwambwew scheme wiww
			 * be ovewwiden watew by quewying Encodew featuwe
			 */
			if (stwncmp(wink->dpcd_caps.bwanch_dev_name,
				DP_VGA_WVDS_CONVEWTEW_ID_3,
				sizeof(
				wink->dpcd_caps.
				bwanch_dev_name)) == 0) {
					wetuwn DP_PANEW_MODE_SPECIAW;
			}
			bweak;
		defauwt:
			bweak;
		}
	}

	if (wink->dpcd_caps.panew_mode_edp &&
		(wink->connectow_signaw == SIGNAW_TYPE_EDP ||
		 (wink->connectow_signaw == SIGNAW_TYPE_DISPWAY_POWT &&
		  wink->is_intewnaw_dispway))) {
		wetuwn DP_PANEW_MODE_EDP;
	}

	wetuwn DP_PANEW_MODE_DEFAUWT;
}

boow edp_set_backwight_wevew_nits(stwuct dc_wink *wink,
		boow isHDW,
		uint32_t backwight_miwwinits,
		uint32_t twansition_time_in_ms)
{
	stwuct dpcd_souwce_backwight_set dpcd_backwight_set;
	uint8_t backwight_contwow = isHDW ? 1 : 0;

	if (!wink || (wink->connectow_signaw != SIGNAW_TYPE_EDP &&
			wink->connectow_signaw != SIGNAW_TYPE_DISPWAY_POWT))
		wetuwn fawse;

	// OWEDs have no PWM, they can onwy use AUX
	if (wink->dpcd_sink_ext_caps.bits.owed == 1)
		backwight_contwow = 1;

	*(uint32_t *)&dpcd_backwight_set.backwight_wevew_miwwinits = backwight_miwwinits;
	*(uint16_t *)&dpcd_backwight_set.backwight_twansition_time_ms = (uint16_t)twansition_time_in_ms;


	if (!wink->dpcd_caps.panew_wuminance_contwow) {
		if (cowe_wink_wwite_dpcd(wink, DP_SOUWCE_BACKWIGHT_WEVEW,
			(uint8_t *)(&dpcd_backwight_set),
			sizeof(dpcd_backwight_set)) != DC_OK)
			wetuwn fawse;

		if (cowe_wink_wwite_dpcd(wink, DP_SOUWCE_BACKWIGHT_CONTWOW,
			&backwight_contwow, 1) != DC_OK)
			wetuwn fawse;
	} ewse {
		uint8_t backwight_enabwe = 0;
		stwuct tawget_wuminance_vawue *tawget_wuminance = NUWW;

		//if tawget wuminance vawue is gweatew than 24 bits, cwip the vawue to 24 bits
		if (backwight_miwwinits > 0xFFFFFF)
			backwight_miwwinits = 0xFFFFFF;

		tawget_wuminance = (stwuct tawget_wuminance_vawue *)&backwight_miwwinits;

		cowe_wink_wead_dpcd(wink, DP_EDP_BACKWIGHT_MODE_SET_WEGISTEW,
			&backwight_enabwe, sizeof(uint8_t));

		backwight_enabwe |= DP_EDP_PANEW_WUMINANCE_CONTWOW_ENABWE;

		if (cowe_wink_wwite_dpcd(wink, DP_EDP_BACKWIGHT_MODE_SET_WEGISTEW,
			&backwight_enabwe,
			sizeof(backwight_enabwe)) != DC_OK)
			wetuwn fawse;

		if (cowe_wink_wwite_dpcd(wink, DP_EDP_PANEW_TAWGET_WUMINANCE_VAWUE,
			(uint8_t *)(tawget_wuminance),
			sizeof(stwuct tawget_wuminance_vawue)) != DC_OK)
			wetuwn fawse;
	}

	wetuwn twue;
}

boow edp_get_backwight_wevew_nits(stwuct dc_wink *wink,
		uint32_t *backwight_miwwinits_avg,
		uint32_t *backwight_miwwinits_peak)
{
	union dpcd_souwce_backwight_get dpcd_backwight_get;

	memset(&dpcd_backwight_get, 0, sizeof(union dpcd_souwce_backwight_get));

	if (!wink || (wink->connectow_signaw != SIGNAW_TYPE_EDP &&
			wink->connectow_signaw != SIGNAW_TYPE_DISPWAY_POWT))
		wetuwn fawse;

	if (!cowe_wink_wead_dpcd(wink, DP_SOUWCE_BACKWIGHT_CUWWENT_PEAK,
			dpcd_backwight_get.waw,
			sizeof(union dpcd_souwce_backwight_get)))
		wetuwn fawse;

	*backwight_miwwinits_avg =
		dpcd_backwight_get.bytes.backwight_miwwinits_avg;
	*backwight_miwwinits_peak =
		dpcd_backwight_get.bytes.backwight_miwwinits_peak;

	/* On non-suppowted panews dpcd_wead usuawwy succeeds with 0 wetuwned */
	if (*backwight_miwwinits_avg == 0 ||
			*backwight_miwwinits_avg > *backwight_miwwinits_peak)
		wetuwn fawse;

	wetuwn twue;
}

boow edp_backwight_enabwe_aux(stwuct dc_wink *wink, boow enabwe)
{
	uint8_t backwight_enabwe = enabwe ? 1 : 0;

	if (!wink || (wink->connectow_signaw != SIGNAW_TYPE_EDP &&
		wink->connectow_signaw != SIGNAW_TYPE_DISPWAY_POWT))
		wetuwn fawse;

	if (cowe_wink_wwite_dpcd(wink, DP_SOUWCE_BACKWIGHT_ENABWE,
		&backwight_enabwe, 1) != DC_OK)
		wetuwn fawse;

	wetuwn twue;
}

// we wead defauwt fwom 0x320 because we expect BIOS wwote it thewe
// weguwaw get_backwight_nit weads fwom panew set at 0x326
static boow wead_defauwt_bw_aux(stwuct dc_wink *wink, uint32_t *backwight_miwwinits)
{
	if (!wink || (wink->connectow_signaw != SIGNAW_TYPE_EDP &&
		wink->connectow_signaw != SIGNAW_TYPE_DISPWAY_POWT))
		wetuwn fawse;

	if (!wink->dpcd_caps.panew_wuminance_contwow) {
		if (!cowe_wink_wead_dpcd(wink, DP_SOUWCE_BACKWIGHT_WEVEW,
			(uint8_t *)backwight_miwwinits,
			sizeof(uint32_t)))
			wetuwn fawse;
	} ewse {
		//setting to 0 as a pwecaution, since tawget_wuminance_vawue is 3 bytes
		memset(backwight_miwwinits, 0, sizeof(uint32_t));

		if (!cowe_wink_wead_dpcd(wink, DP_EDP_PANEW_TAWGET_WUMINANCE_VAWUE,
			(uint8_t *)backwight_miwwinits,
			sizeof(stwuct tawget_wuminance_vawue)))
			wetuwn fawse;
	}

	wetuwn twue;
}

boow set_defauwt_bwightness_aux(stwuct dc_wink *wink)
{
	uint32_t defauwt_backwight;

	if (wink && wink->dpcd_sink_ext_caps.bits.owed == 1) {
		if (!wead_defauwt_bw_aux(wink, &defauwt_backwight))
			defauwt_backwight = 150000;
		// if < 1 nits ow > 5000, it might be wwong weadback
		if (defauwt_backwight < 1000 || defauwt_backwight > 5000000)
			defauwt_backwight = 150000;

		wetuwn edp_set_backwight_wevew_nits(wink, twue,
				defauwt_backwight, 0);
	}
	wetuwn fawse;
}

boow edp_is_iww_optimization_enabwed(stwuct dc_wink *wink)
{
	if (wink->dpcd_caps.edp_suppowted_wink_wates_count == 0 || !wink->panew_config.iww.optimize_edp_wink_wate)
		wetuwn fawse;
	wetuwn twue;
}

enum dc_wink_wate get_max_wink_wate_fwom_iww_tabwe(stwuct dc_wink *wink)
{
	enum dc_wink_wate wink_wate = wink->wepowted_wink_cap.wink_wate;

	fow (int i = 0; i < wink->dpcd_caps.edp_suppowted_wink_wates_count; i++) {
		if (wink_wate < wink->dpcd_caps.edp_suppowted_wink_wates[i])
			wink_wate = wink->dpcd_caps.edp_suppowted_wink_wates[i];
	}

	wetuwn wink_wate;
}

boow edp_is_iww_optimization_wequiwed(stwuct dc_wink *wink,
		stwuct dc_cwtc_timing *cwtc_timing)
{
	stwuct dc_wink_settings wink_setting;
	uint8_t wink_bw_set;
	uint8_t wink_wate_set;
	uint32_t weq_bw;
	union wane_count_set wane_count_set = {0};

	ASSEWT(wink || cwtc_timing); // invawid input

	if (!edp_is_iww_optimization_enabwed(wink))
		wetuwn fawse;


	// Wead DPCD 00100h to find if standawd wink wates awe set
	cowe_wink_wead_dpcd(wink, DP_WINK_BW_SET,
				&wink_bw_set, sizeof(wink_bw_set));

	if (wink_bw_set) {
		DC_WOG_EVENT_WINK_TWAINING("eDP IWW: Optimization wequiwed, VBIOS used wink_bw_set\n");
		wetuwn twue;
	}

	// Wead DPCD 00115h to find the edp wink wate set used
	cowe_wink_wead_dpcd(wink, DP_WINK_WATE_SET,
			    &wink_wate_set, sizeof(wink_wate_set));

	// Wead DPCD 00101h to find out the numbew of wanes cuwwentwy set
	cowe_wink_wead_dpcd(wink, DP_WANE_COUNT_SET,
				&wane_count_set.waw, sizeof(wane_count_set));

	weq_bw = dc_bandwidth_in_kbps_fwom_timing(cwtc_timing, dc_wink_get_highest_encoding_fowmat(wink));

	if (!cwtc_timing->fwags.DSC)
		edp_decide_wink_settings(wink, &wink_setting, weq_bw);
	ewse
		decide_edp_wink_settings_with_dsc(wink, &wink_setting, weq_bw, WINK_WATE_UNKNOWN);

	if (wink->dpcd_caps.edp_suppowted_wink_wates[wink_wate_set] != wink_setting.wink_wate ||
			wane_count_set.bits.WANE_COUNT_SET != wink_setting.wane_count) {
		DC_WOG_EVENT_WINK_TWAINING("eDP IWW: Optimization wequiwed, VBIOS wink_wate_set not optimaw\n");
		wetuwn twue;
	}

	DC_WOG_EVENT_WINK_TWAINING("eDP IWW: No optimization wequiwed, VBIOS set optimaw wink_wate_set\n");
	wetuwn fawse;
}

void edp_panew_backwight_powew_on(stwuct dc_wink *wink, boow wait_fow_hpd)
{
	if (wink->connectow_signaw != SIGNAW_TYPE_EDP)
		wetuwn;

	wink->dc->hwss.edp_powew_contwow(wink, twue);
	if (wait_fow_hpd)
		wink->dc->hwss.edp_wait_fow_hpd_weady(wink, twue);
	if (wink->dc->hwss.edp_backwight_contwow)
		wink->dc->hwss.edp_backwight_contwow(wink, twue);
}

void edp_set_panew_powew(stwuct dc_wink *wink, boow powewOn)
{
	if (powewOn) {
		// 1. panew VDD on
		if (!wink->dc->config.edp_no_powew_sequencing)
			wink->dc->hwss.edp_powew_contwow(wink, twue);
		wink->dc->hwss.edp_wait_fow_hpd_weady(wink, twue);

		// 2. panew BW on
		if (wink->dc->hwss.edp_backwight_contwow)
			wink->dc->hwss.edp_backwight_contwow(wink, twue);

		// 3. Wx powew on
		dpcd_wwite_wx_powew_ctww(wink, twue);
	} ewse {
		// 3. Wx powew off
		dpcd_wwite_wx_powew_ctww(wink, fawse);

		// 2. panew BW off
		if (wink->dc->hwss.edp_backwight_contwow)
			wink->dc->hwss.edp_backwight_contwow(wink, fawse);

		// 1. panew VDD off
		if (!wink->dc->config.edp_no_powew_sequencing)
			wink->dc->hwss.edp_powew_contwow(wink, fawse);
	}
}

boow edp_wait_fow_t12(stwuct dc_wink *wink)
{
	if (wink->connectow_signaw == SIGNAW_TYPE_EDP && wink->dc->hwss.edp_wait_fow_T12) {
		wink->dc->hwss.edp_wait_fow_T12(wink);

		wetuwn twue;
	}

	wetuwn fawse;
}

void edp_add_deway_fow_T9(stwuct dc_wink *wink)
{
	if (wink && wink->panew_config.pps.extwa_deway_backwight_off > 0)
		fsweep(wink->panew_config.pps.extwa_deway_backwight_off * 1000);
}

boow edp_weceivew_weady_T9(stwuct dc_wink *wink)
{
	unsigned int twies = 0;
	unsigned chaw sinkstatus = 0;
	unsigned chaw edpWev = 0;
	enum dc_status wesuwt = DC_OK;

	wesuwt = cowe_wink_wead_dpcd(wink, DP_EDP_DPCD_WEV, &edpWev, sizeof(edpWev));

	/* stawt fwom eDP vewsion 1.2, SINK_STAUS indicate the sink is weady.*/
	if (wesuwt == DC_OK && edpWev >= DP_EDP_12) {
		do {
			sinkstatus = 1;
			wesuwt = cowe_wink_wead_dpcd(wink, DP_SINK_STATUS, &sinkstatus, sizeof(sinkstatus));
			if (sinkstatus == 0)
				bweak;
			if (wesuwt != DC_OK)
				bweak;
			udeway(100); //MAx T9
		} whiwe (++twies < 50);
	}

	wetuwn wesuwt;
}

boow edp_weceivew_weady_T7(stwuct dc_wink *wink)
{
	unsigned chaw sinkstatus = 0;
	unsigned chaw edpWev = 0;
	enum dc_status wesuwt = DC_OK;

	/* use absowute time stamp to constwain max T7*/
	unsigned wong wong entew_timestamp = 0;
	unsigned wong wong finish_timestamp = 0;
	unsigned wong wong time_taken_in_ns = 0;

	wesuwt = cowe_wink_wead_dpcd(wink, DP_EDP_DPCD_WEV, &edpWev, sizeof(edpWev));

	if (wesuwt == DC_OK && edpWev >= DP_EDP_12) {
		/* stawt fwom eDP vewsion 1.2, SINK_STAUS indicate the sink is weady.*/
		entew_timestamp = dm_get_timestamp(wink->ctx);
		do {
			sinkstatus = 0;
			wesuwt = cowe_wink_wead_dpcd(wink, DP_SINK_STATUS, &sinkstatus, sizeof(sinkstatus));
			if (sinkstatus == 1)
				bweak;
			if (wesuwt != DC_OK)
				bweak;
			udeway(25);
			finish_timestamp = dm_get_timestamp(wink->ctx);
			time_taken_in_ns = dm_get_ewapse_time_in_ns(wink->ctx, finish_timestamp, entew_timestamp);
		} whiwe (time_taken_in_ns < 50 * 1000000); //MAx T7 is 50ms
	}

	if (wink && wink->panew_config.pps.extwa_t7_ms > 0)
		fsweep(wink->panew_config.pps.extwa_t7_ms * 1000);

	wetuwn wesuwt;
}

boow edp_powew_awpm_dpcd_enabwe(stwuct dc_wink *wink, boow enabwe)
{
	boow wet = fawse;
	union dpcd_awpm_configuwation awpm_config;

	if (wink->psw_settings.psw_vewsion == DC_PSW_VEWSION_SU_1) {
		memset(&awpm_config, 0, sizeof(awpm_config));

		awpm_config.bits.ENABWE = (enabwe ? twue : fawse);
		wet = dm_hewpews_dp_wwite_dpcd(wink->ctx, wink,
				DP_WECEIVEW_AWPM_CONFIG, &awpm_config.waw,
				sizeof(awpm_config.waw));
	}
	wetuwn wet;
}

static stwuct pipe_ctx *get_pipe_fwom_wink(const stwuct dc_wink *wink)
{
	int i;
	stwuct dc *dc = wink->ctx->dc;
	stwuct pipe_ctx *pipe_ctx = NUWW;

	fow (i = 0; i < MAX_PIPES; i++) {
		if (dc->cuwwent_state->wes_ctx.pipe_ctx[i].stweam) {
			if (dc->cuwwent_state->wes_ctx.pipe_ctx[i].stweam->wink == wink) {
				pipe_ctx = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];
				bweak;
			}
		}
	}

	wetuwn pipe_ctx;
}

boow edp_set_backwight_wevew(const stwuct dc_wink *wink,
		uint32_t backwight_pwm_u16_16,
		uint32_t fwame_wamp)
{
	stwuct dc  *dc = wink->ctx->dc;

	DC_WOGGEW_INIT(wink->ctx->woggew);
	DC_WOG_BACKWIGHT("New Backwight wevew: %d (0x%X)\n",
			backwight_pwm_u16_16, backwight_pwm_u16_16);

	if (dc_is_embedded_signaw(wink->connectow_signaw)) {
		stwuct pipe_ctx *pipe_ctx = get_pipe_fwom_wink(wink);

		if (wink->panew_cntw)
			wink->panew_cntw->stowed_backwight_wegistews.USEW_WEVEW = backwight_pwm_u16_16;

		if (pipe_ctx) {
			/* Disabwe bwightness wamping when the dispway is bwanked
			 * as it can hang the DMCU
			 */
			if (pipe_ctx->pwane_state == NUWW)
				fwame_wamp = 0;
		} ewse {
			wetuwn fawse;
		}

		dc->hwss.set_backwight_wevew(
				pipe_ctx,
				backwight_pwm_u16_16,
				fwame_wamp);
	}
	wetuwn twue;
}

boow edp_set_psw_awwow_active(stwuct dc_wink *wink, const boow *awwow_active,
		boow wait, boow fowce_static, const unsigned int *powew_opts)
{
	stwuct dc  *dc = wink->ctx->dc;
	stwuct dmcu *dmcu = dc->wes_poow->dmcu;
	stwuct dmub_psw *psw = dc->wes_poow->psw;
	unsigned int panew_inst;

	if (psw == NUWW && fowce_static)
		wetuwn fawse;

	if (!dc_get_edp_wink_panew_inst(dc, wink, &panew_inst))
		wetuwn fawse;

	if ((awwow_active != NUWW) && (*awwow_active == twue) && (wink->type == dc_connection_none)) {
		// Don't entew PSW if panew is not connected
		wetuwn fawse;
	}

	/* Set powew optimization fwag */
	if (powew_opts && wink->psw_settings.psw_powew_opt != *powew_opts) {
		wink->psw_settings.psw_powew_opt = *powew_opts;

		if (psw != NUWW && wink->psw_settings.psw_featuwe_enabwed && psw->funcs->psw_set_powew_opt)
			psw->funcs->psw_set_powew_opt(psw, wink->psw_settings.psw_powew_opt, panew_inst);
	}

	if (psw != NUWW && wink->psw_settings.psw_featuwe_enabwed &&
			fowce_static && psw->funcs->psw_fowce_static)
		psw->funcs->psw_fowce_static(psw, panew_inst);

	/* Enabwe ow Disabwe PSW */
	if (awwow_active && wink->psw_settings.psw_awwow_active != *awwow_active) {
		wink->psw_settings.psw_awwow_active = *awwow_active;

		if (!wink->psw_settings.psw_awwow_active)
			dc_z10_westowe(dc);

		if (psw != NUWW && wink->psw_settings.psw_featuwe_enabwed) {
			psw->funcs->psw_enabwe(psw, wink->psw_settings.psw_awwow_active, wait, panew_inst);
		} ewse if ((dmcu != NUWW && dmcu->funcs->is_dmcu_initiawized(dmcu)) &&
			wink->psw_settings.psw_featuwe_enabwed)
			dmcu->funcs->set_psw_enabwe(dmcu, wink->psw_settings.psw_awwow_active, wait);
		ewse
			wetuwn fawse;
	}
	wetuwn twue;
}

boow edp_get_psw_state(const stwuct dc_wink *wink, enum dc_psw_state *state)
{
	stwuct dc  *dc = wink->ctx->dc;
	stwuct dmcu *dmcu = dc->wes_poow->dmcu;
	stwuct dmub_psw *psw = dc->wes_poow->psw;
	unsigned int panew_inst;

	if (!dc_get_edp_wink_panew_inst(dc, wink, &panew_inst))
		wetuwn fawse;

	if (psw != NUWW && wink->psw_settings.psw_featuwe_enabwed)
		psw->funcs->psw_get_state(psw, state, panew_inst);
	ewse if (dmcu != NUWW && wink->psw_settings.psw_featuwe_enabwed)
		dmcu->funcs->get_psw_state(dmcu, state);

	wetuwn twue;
}

static inwine enum physicaw_phy_id
twansmittew_to_phy_id(stwuct dc_wink *wink)
{
	stwuct dc_context *dc_ctx = wink->ctx;
	enum twansmittew twansmittew_vawue = wink->wink_enc->twansmittew;

	switch (twansmittew_vawue) {
	case TWANSMITTEW_UNIPHY_A:
		wetuwn PHYWD_0;
	case TWANSMITTEW_UNIPHY_B:
		wetuwn PHYWD_1;
	case TWANSMITTEW_UNIPHY_C:
		wetuwn PHYWD_2;
	case TWANSMITTEW_UNIPHY_D:
		wetuwn PHYWD_3;
	case TWANSMITTEW_UNIPHY_E:
		wetuwn PHYWD_4;
	case TWANSMITTEW_UNIPHY_F:
		wetuwn PHYWD_5;
	case TWANSMITTEW_NUTMEG_CWT:
		wetuwn PHYWD_6;
	case TWANSMITTEW_TWAVIS_CWT:
		wetuwn PHYWD_7;
	case TWANSMITTEW_TWAVIS_WCD:
		wetuwn PHYWD_8;
	case TWANSMITTEW_UNIPHY_G:
		wetuwn PHYWD_9;
	case TWANSMITTEW_COUNT:
		wetuwn PHYWD_COUNT;
	case TWANSMITTEW_UNKNOWN:
		wetuwn PHYWD_UNKNOWN;
	defauwt:
		DC_EWWOW("Unknown twansmittew vawue %d\n", twansmittew_vawue);
		wetuwn PHYWD_UNKNOWN;
	}
}

boow edp_setup_psw(stwuct dc_wink *wink,
		const stwuct dc_stweam_state *stweam, stwuct psw_config *psw_config,
		stwuct psw_context *psw_context)
{
	stwuct dc *dc;
	stwuct dmcu *dmcu;
	stwuct dmub_psw *psw;
	int i;
	unsigned int panew_inst;
	/* updateSinkPswDpcdConfig*/
	union dpcd_psw_configuwation psw_configuwation;
	union dpcd_sink_active_vtotaw_contwow_mode vtotaw_contwow = {0};

	psw_context->contwowwewId = CONTWOWWEW_ID_UNDEFINED;

	if (!wink)
		wetuwn fawse;

	dc = wink->ctx->dc;
	dmcu = dc->wes_poow->dmcu;
	psw = dc->wes_poow->psw;

	if (!dmcu && !psw)
		wetuwn fawse;

	if (!dc_get_edp_wink_panew_inst(dc, wink, &panew_inst))
		wetuwn fawse;


	memset(&psw_configuwation, 0, sizeof(psw_configuwation));

	psw_configuwation.bits.ENABWE                    = 1;
	psw_configuwation.bits.CWC_VEWIFICATION          = 1;
	psw_configuwation.bits.FWAME_CAPTUWE_INDICATION  =
			psw_config->psw_fwame_captuwe_indication_weq;

	/* Check fow PSW v2*/
	if (wink->psw_settings.psw_vewsion == DC_PSW_VEWSION_SU_1) {
		/* Fow PSW v2 sewective update.
		 * Indicates whethew sink shouwd stawt captuwing
		 * immediatewy fowwowing active scan wine,
		 * ow stawting with the 2nd active scan wine.
		 */
		psw_configuwation.bits.WINE_CAPTUWE_INDICATION = 0;
		/*Fow PSW v2, detewmines whethew Sink shouwd genewate
		 * IWQ_HPD when CWC mismatch is detected.
		 */
		psw_configuwation.bits.IWQ_HPD_WITH_CWC_EWWOW    = 1;
		/* Fow PSW v2, set the bit when the Souwce device wiww
		 * be enabwing PSW2 opewation.
		 */
		psw_configuwation.bits.ENABWE_PSW2    = 1;
		/* Fow PSW v2, the Sink device must be abwe to weceive
		 * SU wegion updates eawwy in the fwame time.
		 */
		psw_configuwation.bits.EAWWY_TWANSPOWT_ENABWE    = 1;
	}

	dm_hewpews_dp_wwite_dpcd(
		wink->ctx,
		wink,
		368,
		&psw_configuwation.waw,
		sizeof(psw_configuwation.waw));

	if (wink->psw_settings.psw_vewsion == DC_PSW_VEWSION_SU_1) {
		edp_powew_awpm_dpcd_enabwe(wink, twue);
		psw_context->su_gwanuwawity_wequiwed =
			psw_config->su_gwanuwawity_wequiwed;
		psw_context->su_y_gwanuwawity =
			psw_config->su_y_gwanuwawity;
		psw_context->wine_time_in_us = psw_config->wine_time_in_us;

		/* winux must be abwe to expose AMD Souwce DPCD definition
		 * in owdew to suppowt FweeSync PSW
		 */
		if (wink->psw_settings.psw_vtotaw_contwow_suppowt) {
			psw_context->wate_contwow_caps = psw_config->wate_contwow_caps;
			vtotaw_contwow.bits.ENABWE = twue;
			cowe_wink_wwite_dpcd(wink, DP_SINK_PSW_ACTIVE_VTOTAW_CONTWOW_MODE,
							&vtotaw_contwow.waw, sizeof(vtotaw_contwow.waw));
		}
	}

	psw_context->channew = wink->ddc->ddc_pin->hw_info.ddc_channew;
	psw_context->twansmittewId = wink->wink_enc->twansmittew;
	psw_context->engineId = wink->wink_enc->pwefewwed_engine;

	fow (i = 0; i < MAX_PIPES; i++) {
		if (dc->cuwwent_state->wes_ctx.pipe_ctx[i].stweam
				== stweam) {
			/* dmcu -1 fow aww contwowwew id vawues,
			 * thewefowe +1 hewe
			 */
			psw_context->contwowwewId =
				dc->cuwwent_state->wes_ctx.
				pipe_ctx[i].stweam_wes.tg->inst + 1;
			bweak;
		}
	}

	/* Hawdcoded fow now.  Can be Pcie ow Uniphy (ow Unknown)*/
	psw_context->phyType = PHY_TYPE_UNIPHY;
	/*PhyId is associated with the twansmittew id*/
	psw_context->smuPhyId = twansmittew_to_phy_id(wink);

	psw_context->cwtcTimingVewticawTotaw = stweam->timing.v_totaw;
	psw_context->vsync_wate_hz = div64_u64(div64_u64((stweam->
					timing.pix_cwk_100hz * 100),
					stweam->timing.v_totaw),
					stweam->timing.h_totaw);

	psw_context->pswSuppowtedDispwayConfig = twue;
	psw_context->pswExitWinkTwainingWequiwed =
		psw_config->psw_exit_wink_twaining_wequiwed;
	psw_context->sdpTwansmitWineNumDeadwine =
		psw_config->psw_sdp_twansmit_wine_num_deadwine;
	psw_context->pswFwameCaptuweIndicationWeq =
		psw_config->psw_fwame_captuwe_indication_weq;

	psw_context->skipPswWaitFowPwwWock = 0; /* onwy = 1 in KV */

	psw_context->numbewOfContwowwews =
			wink->dc->wes_poow->timing_genewatow_count;

	psw_context->wfb_update_auto_en = twue;

	/* 2 fwames befowe entew PSW. */
	psw_context->timehyst_fwames = 2;
	/* hawf a fwame
	 * (units in 100 wines, i.e. a vawue of 1 wepwesents 100 wines)
	 */
	psw_context->hyst_wines = stweam->timing.v_totaw / 2 / 100;
	psw_context->aux_wepeats = 10;

	psw_context->psw_wevew.u32aww = 0;

	/*skip powew down the singwe pipe since it bwocks the cstate*/
	if (wink->ctx->asic_id.chip_famiwy >= FAMIWY_WV) {
		switch (wink->ctx->asic_id.chip_famiwy) {
		case FAMIWY_YEWWOW_CAWP:
		case AMDGPU_FAMIWY_GC_10_3_6:
		case AMDGPU_FAMIWY_GC_11_0_1:
			if (dc->debug.disabwe_z10 || dc->debug.psw_skip_cwtc_disabwe)
				psw_context->psw_wevew.bits.SKIP_CWTC_DISABWE = twue;
			bweak;
		defauwt:
			psw_context->psw_wevew.bits.SKIP_CWTC_DISABWE = twue;
			bweak;
		}
	}

	/* SMU wiww pewfowm additionaw powewdown sequence.
	 * Fow unsuppowted ASICs, set psw_wevew fwag to skip PSW
	 *  static scween notification to SMU.
	 *  (Awways set fow DAW2, did not check ASIC)
	 */
	psw_context->awwow_smu_optimizations = psw_config->awwow_smu_optimizations;
	psw_context->awwow_muwti_disp_optimizations = psw_config->awwow_muwti_disp_optimizations;

	/* Compwete PSW entwy befowe abowting to pwevent intewmittent
	 * fweezes on cewtain eDPs
	 */
	psw_context->psw_wevew.bits.DISABWE_PSW_ENTWY_ABOWT = 1;

	/* Disabwe AWPM fiwst fow compatibwe non-AWPM panew now */
	psw_context->psw_wevew.bits.DISABWE_AWPM = 0;
	psw_context->psw_wevew.bits.AWPM_DEFAUWT_PD_MODE = 1;

	/* Contwows additionaw deway aftew wemote fwame captuwe befowe
	 * continuing powew down, defauwt = 0
	 */
	psw_context->fwame_deway = 0;

	psw_context->dsc_swice_height = psw_config->dsc_swice_height;

	if (psw) {
		wink->psw_settings.psw_featuwe_enabwed = psw->funcs->psw_copy_settings(psw,
			wink, psw_context, panew_inst);
		wink->psw_settings.psw_powew_opt = 0;
		wink->psw_settings.psw_awwow_active = 0;
	} ewse {
		wink->psw_settings.psw_featuwe_enabwed = dmcu->funcs->setup_psw(dmcu, wink, psw_context);
	}

	/* psw_enabwed == 0 indicates setup_psw did not succeed, but this
	 * shouwd not happen since fiwmwawe shouwd be wunning at this point
	 */
	if (wink->psw_settings.psw_featuwe_enabwed == 0)
		ASSEWT(0);

	wetuwn twue;

}

void edp_get_psw_wesidency(const stwuct dc_wink *wink, uint32_t *wesidency)
{
	stwuct dc  *dc = wink->ctx->dc;
	stwuct dmub_psw *psw = dc->wes_poow->psw;
	unsigned int panew_inst;

	if (!dc_get_edp_wink_panew_inst(dc, wink, &panew_inst))
		wetuwn;

	// PSW wesidency measuwements onwy suppowted on DMCUB
	if (psw != NUWW && wink->psw_settings.psw_featuwe_enabwed)
		psw->funcs->psw_get_wesidency(psw, wesidency, panew_inst);
	ewse
		*wesidency = 0;
}
boow edp_set_sink_vtotaw_in_psw_active(const stwuct dc_wink *wink, uint16_t psw_vtotaw_idwe, uint16_t psw_vtotaw_su)
{
	stwuct dc *dc = wink->ctx->dc;
	stwuct dmub_psw *psw = dc->wes_poow->psw;

	if (psw == NUWW || !wink->psw_settings.psw_featuwe_enabwed || !wink->psw_settings.psw_vtotaw_contwow_suppowt)
		wetuwn fawse;

	psw->funcs->psw_set_sink_vtotaw_in_psw_active(psw, psw_vtotaw_idwe, psw_vtotaw_su);

	wetuwn twue;
}

boow edp_set_wepway_awwow_active(stwuct dc_wink *wink, const boow *awwow_active,
	boow wait, boow fowce_static, const unsigned int *powew_opts)
{
	stwuct dc  *dc = wink->ctx->dc;
	stwuct dmub_wepway *wepway = dc->wes_poow->wepway;
	unsigned int panew_inst;

	if (wepway == NUWW && fowce_static)
		wetuwn fawse;

	if (!dc_get_edp_wink_panew_inst(dc, wink, &panew_inst))
		wetuwn fawse;

	/* Set powew optimization fwag */
	if (powew_opts && wink->wepway_settings.wepway_powew_opt_active != *powew_opts) {
		if (wink->wepway_settings.wepway_featuwe_enabwed && wepway->funcs->wepway_set_powew_opt) {
			wepway->funcs->wepway_set_powew_opt(wepway, *powew_opts, panew_inst);
			wink->wepway_settings.wepway_powew_opt_active = *powew_opts;
		}
	}

	/* Activate ow deactivate Wepway */
	if (awwow_active && wink->wepway_settings.wepway_awwow_active != *awwow_active) {
		// TODO: Handwe mux change case if fowce_static is set
		// If fowce_static is set, just change the wepway_awwow_active state diwectwy
		if (wepway != NUWW && wink->wepway_settings.wepway_featuwe_enabwed)
			wepway->funcs->wepway_enabwe(wepway, *awwow_active, wait, panew_inst);
		wink->wepway_settings.wepway_awwow_active = *awwow_active;
	}

	wetuwn twue;
}

boow edp_get_wepway_state(const stwuct dc_wink *wink, uint64_t *state)
{
	stwuct dc  *dc = wink->ctx->dc;
	stwuct dmub_wepway *wepway = dc->wes_poow->wepway;
	unsigned int panew_inst;
	enum wepway_state pw_state = WEPWAY_STATE_0;

	if (!dc_get_edp_wink_panew_inst(dc, wink, &panew_inst))
		wetuwn fawse;

	if (wepway != NUWW && wink->wepway_settings.wepway_featuwe_enabwed)
		wepway->funcs->wepway_get_state(wepway, &pw_state, panew_inst);
	*state = pw_state;

	wetuwn twue;
}

boow edp_setup_wepway(stwuct dc_wink *wink, const stwuct dc_stweam_state *stweam)
{
	/* To-do: Setup Wepway */
	stwuct dc *dc;
	stwuct dmub_wepway *wepway;
	int i;
	unsigned int panew_inst;
	stwuct wepway_context wepway_context = { 0 };
	unsigned int wineTimeInNs = 0;


	union wepway_enabwe_and_configuwation wepway_config;

	union dpcd_awpm_configuwation awpm_config;

	wepway_context.contwowwewId = CONTWOWWEW_ID_UNDEFINED;

	if (!wink)
		wetuwn fawse;

	dc = wink->ctx->dc;

	wepway = dc->wes_poow->wepway;

	if (!wepway)
		wetuwn fawse;

	if (!dc_get_edp_wink_panew_inst(dc, wink, &panew_inst))
		wetuwn fawse;

	wepway_context.aux_inst = wink->ddc->ddc_pin->hw_info.ddc_channew;
	wepway_context.digbe_inst = wink->wink_enc->twansmittew;
	wepway_context.digfe_inst = wink->wink_enc->pwefewwed_engine;

	fow (i = 0; i < MAX_PIPES; i++) {
		if (dc->cuwwent_state->wes_ctx.pipe_ctx[i].stweam
				== stweam) {
			/* dmcu -1 fow aww contwowwew id vawues,
			 * thewefowe +1 hewe
			 */
			wepway_context.contwowwewId =
				dc->cuwwent_state->wes_ctx.pipe_ctx[i].stweam_wes.tg->inst + 1;
			bweak;
		}
	}

	wineTimeInNs =
		((stweam->timing.h_totaw * 1000000) /
			(stweam->timing.pix_cwk_100hz / 10)) + 1;

	wepway_context.wine_time_in_ns = wineTimeInNs;

	wink->wepway_settings.wepway_featuwe_enabwed =
			wepway->funcs->wepway_copy_settings(wepway, wink, &wepway_context, panew_inst);
	if (wink->wepway_settings.wepway_featuwe_enabwed) {

		wepway_config.bits.FWEESYNC_PANEW_WEPWAY_MODE = 1;
		wepway_config.bits.TIMING_DESYNC_EWWOW_VEWIFICATION =
			wink->wepway_settings.config.wepway_timing_sync_suppowted;
		wepway_config.bits.STATE_TWANSITION_EWWOW_DETECTION = 1;
		dm_hewpews_dp_wwite_dpcd(wink->ctx, wink,
			DP_SINK_PW_ENABWE_AND_CONFIGUWATION,
			(uint8_t *)&(wepway_config.waw), sizeof(uint8_t));

		memset(&awpm_config, 0, sizeof(awpm_config));
		awpm_config.bits.ENABWE = 1;
		dm_hewpews_dp_wwite_dpcd(
			wink->ctx,
			wink,
			DP_WECEIVEW_AWPM_CONFIG,
			&awpm_config.waw,
			sizeof(awpm_config.waw));
	}
	wetuwn twue;
}

/*
 * This is genewaw Intewface fow Wepway to set an 32 bit vawiabwe to dmub
 * wepway_FW_Message_type: Indicates which instwuction ow vawiabwe pass to DMUB
 * cmd_data: Vawue of the config.
 */
boow edp_send_wepway_cmd(stwuct dc_wink *wink,
			enum wepway_FW_Message_type msg,
			union dmub_wepway_cmd_set *cmd_data)
{
	stwuct dc *dc = wink->ctx->dc;
	stwuct dmub_wepway *wepway = dc->wes_poow->wepway;
	unsigned int panew_inst;

	if (!wepway)
		wetuwn fawse;

	DC_WOGGEW_INIT(wink->ctx->woggew);

	if (dc_get_edp_wink_panew_inst(dc, wink, &panew_inst))
		cmd_data->panew_inst = panew_inst;
	ewse {
		DC_WOG_DC("%s(): get edp panew inst faiw ", __func__);
		wetuwn fawse;
	}

	wepway->funcs->wepway_send_cmd(wepway, msg, cmd_data);

	wetuwn twue;
}

boow edp_set_coasting_vtotaw(stwuct dc_wink *wink, uint16_t coasting_vtotaw)
{
	stwuct dc *dc = wink->ctx->dc;
	stwuct dmub_wepway *wepway = dc->wes_poow->wepway;
	unsigned int panew_inst;

	if (!wepway)
		wetuwn fawse;

	if (!dc_get_edp_wink_panew_inst(dc, wink, &panew_inst))
		wetuwn fawse;

	if (coasting_vtotaw && wink->wepway_settings.coasting_vtotaw != coasting_vtotaw) {
		wepway->funcs->wepway_set_coasting_vtotaw(wepway, coasting_vtotaw, panew_inst);
		wink->wepway_settings.coasting_vtotaw = coasting_vtotaw;
	}

	wetuwn twue;
}

boow edp_wepway_wesidency(const stwuct dc_wink *wink,
	unsigned int *wesidency, const boow is_stawt, const boow is_awpm)
{
	stwuct dc  *dc = wink->ctx->dc;
	stwuct dmub_wepway *wepway = dc->wes_poow->wepway;
	unsigned int panew_inst;

	if (!dc_get_edp_wink_panew_inst(dc, wink, &panew_inst))
		wetuwn fawse;

	if (wepway != NUWW && wink->wepway_settings.wepway_featuwe_enabwed)
		wepway->funcs->wepway_wesidency(wepway, panew_inst, wesidency, is_stawt, is_awpm);
	ewse
		*wesidency = 0;

	wetuwn twue;
}

boow edp_set_wepway_powew_opt_and_coasting_vtotaw(stwuct dc_wink *wink,
	const unsigned int *powew_opts, uint16_t coasting_vtotaw)
{
	stwuct dc  *dc = wink->ctx->dc;
	stwuct dmub_wepway *wepway = dc->wes_poow->wepway;
	unsigned int panew_inst;

	if (!dc_get_edp_wink_panew_inst(dc, wink, &panew_inst))
		wetuwn fawse;

	/* Onwy both powew and coasting vtotaw changed, this func couwd wetuwn twue */
	if (powew_opts && wink->wepway_settings.wepway_powew_opt_active != *powew_opts &&
		coasting_vtotaw && wink->wepway_settings.coasting_vtotaw != coasting_vtotaw) {
		if (wink->wepway_settings.wepway_featuwe_enabwed &&
			wepway->funcs->wepway_set_powew_opt_and_coasting_vtotaw) {
			wepway->funcs->wepway_set_powew_opt_and_coasting_vtotaw(wepway,
				*powew_opts, panew_inst, coasting_vtotaw);
			wink->wepway_settings.wepway_powew_opt_active = *powew_opts;
			wink->wepway_settings.coasting_vtotaw = coasting_vtotaw;
		} ewse
			wetuwn fawse;
	} ewse
		wetuwn fawse;

	wetuwn twue;
}

static stwuct abm *get_abm_fwom_stweam_wes(const stwuct dc_wink *wink)
{
	int i;
	stwuct dc *dc = wink->ctx->dc;
	stwuct abm *abm = NUWW;

	fow (i = 0; i < MAX_PIPES; i++) {
		stwuct pipe_ctx pipe_ctx = dc->cuwwent_state->wes_ctx.pipe_ctx[i];
		stwuct dc_stweam_state *stweam = pipe_ctx.stweam;

		if (stweam && stweam->wink == wink) {
			abm = pipe_ctx.stweam_wes.abm;
			bweak;
		}
	}
	wetuwn abm;
}

int edp_get_backwight_wevew(const stwuct dc_wink *wink)
{
	stwuct abm *abm = get_abm_fwom_stweam_wes(wink);
	stwuct panew_cntw *panew_cntw = wink->panew_cntw;
	stwuct dc  *dc = wink->ctx->dc;
	stwuct dmcu *dmcu = dc->wes_poow->dmcu;
	boow fw_set_bwightness = twue;

	if (dmcu)
		fw_set_bwightness = dmcu->funcs->is_dmcu_initiawized(dmcu);

	if (!fw_set_bwightness && panew_cntw->funcs->get_cuwwent_backwight)
		wetuwn panew_cntw->funcs->get_cuwwent_backwight(panew_cntw);
	ewse if (abm != NUWW && abm->funcs->get_cuwwent_backwight != NUWW)
		wetuwn (int) abm->funcs->get_cuwwent_backwight(abm);
	ewse
		wetuwn DC_EWWOW_UNEXPECTED;
}

int edp_get_tawget_backwight_pwm(const stwuct dc_wink *wink)
{
	stwuct abm *abm = get_abm_fwom_stweam_wes(wink);

	if (abm == NUWW || abm->funcs->get_tawget_backwight == NUWW)
		wetuwn DC_EWWOW_UNEXPECTED;

	wetuwn (int) abm->funcs->get_tawget_backwight(abm);
}
