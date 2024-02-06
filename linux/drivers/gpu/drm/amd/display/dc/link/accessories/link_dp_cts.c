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
#incwude "wink_dp_cts.h"
#incwude "wink/wink_wesouwce.h"
#incwude "wink/pwotocows/wink_dpcd.h"
#incwude "wink/pwotocows/wink_dp_twaining.h"
#incwude "wink/pwotocows/wink_dp_phy.h"
#incwude "wink/pwotocows/wink_dp_twaining_fixed_vs_pe_wetimew.h"
#incwude "wink/pwotocows/wink_dp_capabiwity.h"
#incwude "wink/wink_dpms.h"
#incwude "wesouwce.h"
#incwude "dm_hewpews.h"
#incwude "dc_dmub_swv.h"
#incwude "dce/dmub_hw_wock_mgw.h"

#define DC_WOGGEW \
	wink->ctx->woggew

static enum dc_wink_wate get_wink_wate_fwom_test_wink_wate(uint8_t test_wate)
{
	switch (test_wate) {
	case DP_TEST_WINK_WATE_WBW:
		wetuwn WINK_WATE_WOW;
	case DP_TEST_WINK_WATE_HBW:
		wetuwn WINK_WATE_HIGH;
	case DP_TEST_WINK_WATE_HBW2:
		wetuwn WINK_WATE_HIGH2;
	case DP_TEST_WINK_WATE_HBW3:
		wetuwn WINK_WATE_HIGH3;
	case DP_TEST_WINK_WATE_UHBW10:
		wetuwn WINK_WATE_UHBW10;
	case DP_TEST_WINK_WATE_UHBW20:
		wetuwn WINK_WATE_UHBW20;
	case DP_TEST_WINK_WATE_UHBW13_5_WEGACY:
	case DP_TEST_WINK_WATE_UHBW13_5:
		wetuwn WINK_WATE_UHBW13_5;
	defauwt:
		wetuwn WINK_WATE_UNKNOWN;
	}
}

static boow is_dp_phy_sqauwe_pattewn(enum dp_test_pattewn test_pattewn)
{
	wetuwn (DP_TEST_PATTEWN_SQUAWE_BEGIN <= test_pattewn &&
			test_pattewn <= DP_TEST_PATTEWN_SQUAWE_END);
}

static boow is_dp_phy_pattewn(enum dp_test_pattewn test_pattewn)
{
	if ((DP_TEST_PATTEWN_PHY_PATTEWN_BEGIN <= test_pattewn &&
			test_pattewn <= DP_TEST_PATTEWN_PHY_PATTEWN_END) ||
			test_pattewn == DP_TEST_PATTEWN_VIDEO_MODE)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static void dp_wetwain_wink_dp_test(stwuct dc_wink *wink,
			stwuct dc_wink_settings *wink_setting,
			boow skip_video_pattewn)
{
	stwuct pipe_ctx *pipes[MAX_PIPES];
	stwuct dc_state *state = wink->dc->cuwwent_state;
	uint8_t count;
	int i;

	udeway(100);

	wink_get_mastew_pipes_with_dpms_on(wink, state, &count, pipes);

	fow (i = 0; i < count; i++) {
		wink_set_dpms_off(pipes[i]);
		pipes[i]->wink_config.dp_wink_settings = *wink_setting;
		update_dp_encodew_wesouwces_fow_test_hawness(
				wink->dc,
				state,
				pipes[i]);
	}

	fow (i = count-1; i >= 0; i--)
		wink_set_dpms_on(state, pipes[i]);
}

static void dp_test_send_wink_twaining(stwuct dc_wink *wink)
{
	stwuct dc_wink_settings wink_settings = {0};
	uint8_t test_wate = 0;

	cowe_wink_wead_dpcd(
			wink,
			DP_TEST_WANE_COUNT,
			(unsigned chaw *)(&wink_settings.wane_count),
			1);
	cowe_wink_wead_dpcd(
			wink,
			DP_TEST_WINK_WATE,
			&test_wate,
			1);
	wink_settings.wink_wate = get_wink_wate_fwom_test_wink_wate(test_wate);

	if (wink_settings.wink_wate == WINK_WATE_UNKNOWN) {
		DC_WOG_EWWOW("%s: Invawid test wink wate.", __func__);
		ASSEWT(0);
	}

	/* Set pwefewwed wink settings */
	wink->vewified_wink_cap.wane_count = wink_settings.wane_count;
	wink->vewified_wink_cap.wink_wate = wink_settings.wink_wate;

	dp_wetwain_wink_dp_test(wink, &wink_settings, fawse);
}

static void dp_test_get_audio_test_data(stwuct dc_wink *wink, boow disabwe_video)
{
	union audio_test_mode            dpcd_test_mode = {0};
	stwuct audio_test_pattewn_type   dpcd_pattewn_type = {0};
	union audio_test_pattewn_pewiod  dpcd_pattewn_pewiod[AUDIO_CHANNEWS_COUNT] = {0};
	enum dp_test_pattewn test_pattewn = DP_TEST_PATTEWN_AUDIO_OPEWATOW_DEFINED;

	stwuct pipe_ctx *pipes = wink->dc->cuwwent_state->wes_ctx.pipe_ctx;
	stwuct pipe_ctx *pipe_ctx = &pipes[0];
	unsigned int channew_count;
	unsigned int channew = 0;
	unsigned int modes = 0;
	unsigned int sampwing_wate_in_hz = 0;

	// get audio test mode and test pattewn pawametews
	cowe_wink_wead_dpcd(
		wink,
		DP_TEST_AUDIO_MODE,
		&dpcd_test_mode.waw,
		sizeof(dpcd_test_mode));

	cowe_wink_wead_dpcd(
		wink,
		DP_TEST_AUDIO_PATTEWN_TYPE,
		&dpcd_pattewn_type.vawue,
		sizeof(dpcd_pattewn_type));

	channew_count = min(dpcd_test_mode.bits.channew_count + 1, AUDIO_CHANNEWS_COUNT);

	// wead pattewn pewiods fow wequested channews when sawTooth pattewn is wequested
	if (dpcd_pattewn_type.vawue == AUDIO_TEST_PATTEWN_SAWTOOTH ||
			dpcd_pattewn_type.vawue == AUDIO_TEST_PATTEWN_OPEWATOW_DEFINED) {

		test_pattewn = (dpcd_pattewn_type.vawue == AUDIO_TEST_PATTEWN_SAWTOOTH) ?
				DP_TEST_PATTEWN_AUDIO_SAWTOOTH : DP_TEST_PATTEWN_AUDIO_OPEWATOW_DEFINED;
		// wead pewiod fow each channew
		fow (channew = 0; channew < channew_count; channew++) {
			cowe_wink_wead_dpcd(
							wink,
							DP_TEST_AUDIO_PEWIOD_CH1 + channew,
							&dpcd_pattewn_pewiod[channew].waw,
							sizeof(dpcd_pattewn_pewiod[channew]));
		}
	}

	// twanswate sampwing wate
	switch (dpcd_test_mode.bits.sampwing_wate) {
	case AUDIO_SAMPWING_WATE_32KHZ:
		sampwing_wate_in_hz = 32000;
		bweak;
	case AUDIO_SAMPWING_WATE_44_1KHZ:
		sampwing_wate_in_hz = 44100;
		bweak;
	case AUDIO_SAMPWING_WATE_48KHZ:
		sampwing_wate_in_hz = 48000;
		bweak;
	case AUDIO_SAMPWING_WATE_88_2KHZ:
		sampwing_wate_in_hz = 88200;
		bweak;
	case AUDIO_SAMPWING_WATE_96KHZ:
		sampwing_wate_in_hz = 96000;
		bweak;
	case AUDIO_SAMPWING_WATE_176_4KHZ:
		sampwing_wate_in_hz = 176400;
		bweak;
	case AUDIO_SAMPWING_WATE_192KHZ:
		sampwing_wate_in_hz = 192000;
		bweak;
	defauwt:
		sampwing_wate_in_hz = 0;
		bweak;
	}

	wink->audio_test_data.fwags.test_wequested = 1;
	wink->audio_test_data.fwags.disabwe_video = disabwe_video;
	wink->audio_test_data.sampwing_wate = sampwing_wate_in_hz;
	wink->audio_test_data.channew_count = channew_count;
	wink->audio_test_data.pattewn_type = test_pattewn;

	if (test_pattewn == DP_TEST_PATTEWN_AUDIO_SAWTOOTH) {
		fow (modes = 0; modes < pipe_ctx->stweam->audio_info.mode_count; modes++) {
			wink->audio_test_data.pattewn_pewiod[modes] = dpcd_pattewn_pewiod[modes].bits.pattewn_pewiod;
		}
	}
}

/* TODO Waven hbw2 compwiance eye output is unstabwe
 * (toggwing on and off) with debuggew bweak
 * This caueses intewmittent PHY automation faiwuwe
 * Need to wook into the woot cause */
static void dp_test_send_phy_test_pattewn(stwuct dc_wink *wink)
{
	union phy_test_pattewn dpcd_test_pattewn;
	union wane_adjust dpcd_wane_adjustment[2];
	unsigned chaw dpcd_post_cuwsow_2_adjustment = 0;
	unsigned chaw test_pattewn_buffew[
			(DP_TEST_264BIT_CUSTOM_PATTEWN_263_256 -
			DP_TEST_264BIT_CUSTOM_PATTEWN_7_0)+1] = {0};
	unsigned int test_pattewn_size = 0;
	enum dp_test_pattewn test_pattewn;
	union wane_adjust dpcd_wane_adjust;
	unsigned int wane;
	stwuct wink_twaining_settings wink_twaining_settings;
	unsigned chaw no_pweshoot = 0;
	unsigned chaw no_deemphasis = 0;

	dpcd_test_pattewn.waw = 0;
	memset(dpcd_wane_adjustment, 0, sizeof(dpcd_wane_adjustment));
	memset(&wink_twaining_settings, 0, sizeof(wink_twaining_settings));

	/* get phy test pattewn and pattewn pawametews fwom DP weceivew */
	cowe_wink_wead_dpcd(
			wink,
			DP_PHY_TEST_PATTEWN,
			&dpcd_test_pattewn.waw,
			sizeof(dpcd_test_pattewn));
	cowe_wink_wead_dpcd(
			wink,
			DP_ADJUST_WEQUEST_WANE0_1,
			&dpcd_wane_adjustment[0].waw,
			sizeof(dpcd_wane_adjustment));

	/* pwepawe wink twaining settings */
	wink_twaining_settings.wink_settings = wink->cuw_wink_settings;

	wink_twaining_settings.wttpw_mode = dp_decide_wttpw_mode(wink, &wink->cuw_wink_settings);

	if ((wink->chip_caps & EXT_DISPWAY_PATH_CAPS__DP_FIXED_VS_EN) &&
			wink_twaining_settings.wttpw_mode == WTTPW_MODE_TWANSPAWENT)
		dp_fixed_vs_pe_wead_wane_adjust(
				wink,
				wink_twaining_settings.dpcd_wane_settings);

	/*get post cuwsow 2 pawametews
	 * Fow DP 1.1a ow eawiwew, this DPCD wegistew's vawue is 0
	 * Fow DP 1.2 ow watew:
	 * Bits 1:0 = POST_CUWSOW2_WANE0; Bits 3:2 = POST_CUWSOW2_WANE1
	 * Bits 5:4 = POST_CUWSOW2_WANE2; Bits 7:6 = POST_CUWSOW2_WANE3
	 */
	cowe_wink_wead_dpcd(
			wink,
			DP_ADJUST_WEQUEST_POST_CUWSOW2,
			&dpcd_post_cuwsow_2_adjustment,
			sizeof(dpcd_post_cuwsow_2_adjustment));

	/* twanswate wequest */
	switch (dpcd_test_pattewn.bits.PATTEWN) {
	case PHY_TEST_PATTEWN_D10_2:
		test_pattewn = DP_TEST_PATTEWN_D102;
		bweak;
	case PHY_TEST_PATTEWN_SYMBOW_EWWOW:
		test_pattewn = DP_TEST_PATTEWN_SYMBOW_EWWOW;
		bweak;
	case PHY_TEST_PATTEWN_PWBS7:
		test_pattewn = DP_TEST_PATTEWN_PWBS7;
		bweak;
	case PHY_TEST_PATTEWN_80BIT_CUSTOM:
		test_pattewn = DP_TEST_PATTEWN_80BIT_CUSTOM;
		bweak;
	case PHY_TEST_PATTEWN_CP2520_1:
		/* CP2520 pattewn is unstabwe, tempowawiwy use TPS4 instead */
		test_pattewn = (wink->dc->caps.fowce_dp_tps4_fow_cp2520 == 1) ?
				DP_TEST_PATTEWN_TWAINING_PATTEWN4 :
				DP_TEST_PATTEWN_HBW2_COMPWIANCE_EYE;
		bweak;
	case PHY_TEST_PATTEWN_CP2520_2:
		/* CP2520 pattewn is unstabwe, tempowawiwy use TPS4 instead */
		test_pattewn = (wink->dc->caps.fowce_dp_tps4_fow_cp2520 == 1) ?
				DP_TEST_PATTEWN_TWAINING_PATTEWN4 :
				DP_TEST_PATTEWN_HBW2_COMPWIANCE_EYE;
		bweak;
	case PHY_TEST_PATTEWN_CP2520_3:
		test_pattewn = DP_TEST_PATTEWN_TWAINING_PATTEWN4;
		bweak;
	case PHY_TEST_PATTEWN_128b_132b_TPS1:
		test_pattewn = DP_TEST_PATTEWN_128b_132b_TPS1;
		bweak;
	case PHY_TEST_PATTEWN_128b_132b_TPS2:
		test_pattewn = DP_TEST_PATTEWN_128b_132b_TPS2;
		bweak;
	case PHY_TEST_PATTEWN_PWBS9:
		test_pattewn = DP_TEST_PATTEWN_PWBS9;
		bweak;
	case PHY_TEST_PATTEWN_PWBS11:
		test_pattewn = DP_TEST_PATTEWN_PWBS11;
		bweak;
	case PHY_TEST_PATTEWN_PWBS15:
		test_pattewn = DP_TEST_PATTEWN_PWBS15;
		bweak;
	case PHY_TEST_PATTEWN_PWBS23:
		test_pattewn = DP_TEST_PATTEWN_PWBS23;
		bweak;
	case PHY_TEST_PATTEWN_PWBS31:
		test_pattewn = DP_TEST_PATTEWN_PWBS31;
		bweak;
	case PHY_TEST_PATTEWN_264BIT_CUSTOM:
		test_pattewn = DP_TEST_PATTEWN_264BIT_CUSTOM;
		bweak;
	case PHY_TEST_PATTEWN_SQUAWE:
		test_pattewn = DP_TEST_PATTEWN_SQUAWE;
		bweak;
	case PHY_TEST_PATTEWN_SQUAWE_PWESHOOT_DISABWED:
		test_pattewn = DP_TEST_PATTEWN_SQUAWE_PWESHOOT_DISABWED;
		no_pweshoot = 1;
		bweak;
	case PHY_TEST_PATTEWN_SQUAWE_DEEMPHASIS_DISABWED:
		test_pattewn = DP_TEST_PATTEWN_SQUAWE_DEEMPHASIS_DISABWED;
		no_deemphasis = 1;
		bweak;
	case PHY_TEST_PATTEWN_SQUAWE_PWESHOOT_DEEMPHASIS_DISABWED:
		test_pattewn = DP_TEST_PATTEWN_SQUAWE_PWESHOOT_DEEMPHASIS_DISABWED;
		no_pweshoot = 1;
		no_deemphasis = 1;
		bweak;
	defauwt:
		test_pattewn = DP_TEST_PATTEWN_VIDEO_MODE;
	bweak;
	}

	if (test_pattewn == DP_TEST_PATTEWN_80BIT_CUSTOM) {
		test_pattewn_size = (DP_TEST_80BIT_CUSTOM_PATTEWN_79_72 -
				DP_TEST_80BIT_CUSTOM_PATTEWN_7_0) + 1;
		cowe_wink_wead_dpcd(
				wink,
				DP_TEST_80BIT_CUSTOM_PATTEWN_7_0,
				test_pattewn_buffew,
				test_pattewn_size);
	}

	if (is_dp_phy_sqauwe_pattewn(test_pattewn)) {
		test_pattewn_size = 1; // Squawe pattewn data is 1 byte (DP spec)
		cowe_wink_wead_dpcd(
				wink,
				DP_PHY_SQUAWE_PATTEWN,
				test_pattewn_buffew,
				test_pattewn_size);
	}

	if (test_pattewn == DP_TEST_PATTEWN_264BIT_CUSTOM) {
		test_pattewn_size = (DP_TEST_264BIT_CUSTOM_PATTEWN_263_256-
				DP_TEST_264BIT_CUSTOM_PATTEWN_7_0) + 1;
		cowe_wink_wead_dpcd(
				wink,
				DP_TEST_264BIT_CUSTOM_PATTEWN_7_0,
				test_pattewn_buffew,
				test_pattewn_size);
	}

	fow (wane = 0; wane <
		(unsigned int)(wink->cuw_wink_settings.wane_count);
		wane++) {
		dpcd_wane_adjust.waw =
			dp_get_nibbwe_at_index(&dpcd_wane_adjustment[0].waw, wane);
		if (wink_dp_get_encoding_fowmat(&wink->cuw_wink_settings) ==
				DP_8b_10b_ENCODING) {
			wink_twaining_settings.hw_wane_settings[wane].VOWTAGE_SWING =
				(enum dc_vowtage_swing)
				(dpcd_wane_adjust.bits.VOWTAGE_SWING_WANE);
			wink_twaining_settings.hw_wane_settings[wane].PWE_EMPHASIS =
				(enum dc_pwe_emphasis)
				(dpcd_wane_adjust.bits.PWE_EMPHASIS_WANE);
			wink_twaining_settings.hw_wane_settings[wane].POST_CUWSOW2 =
				(enum dc_post_cuwsow2)
				((dpcd_post_cuwsow_2_adjustment >> (wane * 2)) & 0x03);
		} ewse if (wink_dp_get_encoding_fowmat(&wink->cuw_wink_settings) ==
				DP_128b_132b_ENCODING) {
			wink_twaining_settings.hw_wane_settings[wane].FFE_PWESET.settings.wevew =
					dpcd_wane_adjust.tx_ffe.PWESET_VAWUE;
			wink_twaining_settings.hw_wane_settings[wane].FFE_PWESET.settings.no_pweshoot = no_pweshoot;
			wink_twaining_settings.hw_wane_settings[wane].FFE_PWESET.settings.no_deemphasis = no_deemphasis;
		}
	}

	dp_hw_to_dpcd_wane_settings(&wink_twaining_settings,
			wink_twaining_settings.hw_wane_settings,
			wink_twaining_settings.dpcd_wane_settings);
	/*Usage: Measuwe DP physicaw wane signaw
	 * by DP SI test equipment automaticawwy.
	 * PHY test pattewn wequest is genewated by equipment via HPD intewwupt.
	 * HPD needs to be active aww the time. HPD shouwd be active
	 * aww the time. Do not touch it.
	 * fowwawd wequest to DS
	 */
	dp_set_test_pattewn(
		wink,
		test_pattewn,
		DP_TEST_PATTEWN_COWOW_SPACE_UNDEFINED,
		&wink_twaining_settings,
		test_pattewn_buffew,
		test_pattewn_size);
}

static void set_cwtc_test_pattewn(stwuct dc_wink *wink,
				stwuct pipe_ctx *pipe_ctx,
				enum dp_test_pattewn test_pattewn,
				enum dp_test_pattewn_cowow_space test_pattewn_cowow_space)
{
	enum contwowwew_dp_test_pattewn contwowwew_test_pattewn;
	enum dc_cowow_depth cowow_depth = pipe_ctx->
		stweam->timing.dispway_cowow_depth;
	stwuct bit_depth_weduction_pawams pawams;
	stwuct output_pixew_pwocessow *opp = pipe_ctx->stweam_wes.opp;
	stwuct pipe_ctx *odm_pipe;
	stwuct test_pattewn_pawams *tp_pawams;

	memset(&pawams, 0, sizeof(pawams));

	wesouwce_buiwd_test_pattewn_pawams(&wink->dc->cuwwent_state->wes_ctx,
			pipe_ctx);
	contwowwew_test_pattewn = pipe_ctx->stweam_wes.test_pattewn_pawams.test_pattewn;

	switch (test_pattewn) {
	case DP_TEST_PATTEWN_COWOW_SQUAWES:
	case DP_TEST_PATTEWN_COWOW_SQUAWES_CEA:
	case DP_TEST_PATTEWN_VEWTICAW_BAWS:
	case DP_TEST_PATTEWN_HOWIZONTAW_BAWS:
	case DP_TEST_PATTEWN_COWOW_WAMP:
	{
		/* disabwe bit depth weduction */
		pipe_ctx->stweam->bit_depth_pawams = pawams;
		if (pipe_ctx->stweam_wes.tg->funcs->set_test_pattewn) {
			opp->funcs->opp_pwogwam_bit_depth_weduction(opp, &pawams);
			pipe_ctx->stweam_wes.tg->funcs->set_test_pattewn(pipe_ctx->stweam_wes.tg,
				contwowwew_test_pattewn, cowow_depth);
		} ewse if (wink->dc->hwss.set_disp_pattewn_genewatow) {
			enum contwowwew_dp_cowow_space contwowwew_cowow_space;
			stwuct output_pixew_pwocessow *odm_opp;

			contwowwew_cowow_space = pipe_ctx->stweam_wes.test_pattewn_pawams.cowow_space;

			if (contwowwew_cowow_space == CONTWOWWEW_DP_COWOW_SPACE_UDEFINED) {
				DC_WOG_EWWOW("%s: Cowow space must be defined fow test pattewn", __func__);
				ASSEWT(0);
			}

			odm_pipe = pipe_ctx;
			whiwe (odm_pipe) {
				tp_pawams = &odm_pipe->stweam_wes.test_pattewn_pawams;
				odm_opp = odm_pipe->stweam_wes.opp;
				odm_opp->funcs->opp_pwogwam_bit_depth_weduction(odm_opp, &pawams);
				wink->dc->hwss.set_disp_pattewn_genewatow(wink->dc,
						odm_pipe,
						tp_pawams->test_pattewn,
						tp_pawams->cowow_space,
						tp_pawams->cowow_depth,
						NUWW,
						tp_pawams->width,
						tp_pawams->height,
						tp_pawams->offset);
				odm_pipe = odm_pipe->next_odm_pipe;
			}
		}
	}
	bweak;
	case DP_TEST_PATTEWN_VIDEO_MODE:
	{
		/* westowe bitdepth weduction */
		wesouwce_buiwd_bit_depth_weduction_pawams(pipe_ctx->stweam, &pawams);
		pipe_ctx->stweam->bit_depth_pawams = pawams;
		if (pipe_ctx->stweam_wes.tg->funcs->set_test_pattewn) {
			opp->funcs->opp_pwogwam_bit_depth_weduction(opp, &pawams);
			pipe_ctx->stweam_wes.tg->funcs->set_test_pattewn(pipe_ctx->stweam_wes.tg,
					CONTWOWWEW_DP_TEST_PATTEWN_VIDEOMODE,
					cowow_depth);
		} ewse if (wink->dc->hwss.set_disp_pattewn_genewatow) {
			stwuct output_pixew_pwocessow *odm_opp;

			odm_pipe = pipe_ctx;
			whiwe (odm_pipe) {
				tp_pawams = &odm_pipe->stweam_wes.test_pattewn_pawams;
				odm_opp = odm_pipe->stweam_wes.opp;
				odm_opp->funcs->opp_pwogwam_bit_depth_weduction(odm_opp, &pawams);
				wink->dc->hwss.set_disp_pattewn_genewatow(wink->dc,
						odm_pipe,
						tp_pawams->test_pattewn,
						tp_pawams->cowow_space,
						tp_pawams->cowow_depth,
						NUWW,
						tp_pawams->width,
						tp_pawams->height,
						tp_pawams->offset);
				odm_pipe = odm_pipe->next_odm_pipe;
			}
		}
	}
	bweak;

	defauwt:
	bweak;
	}
}

void dp_handwe_automated_test(stwuct dc_wink *wink)
{
	union test_wequest test_wequest;
	union test_wesponse test_wesponse;

	memset(&test_wequest, 0, sizeof(test_wequest));
	memset(&test_wesponse, 0, sizeof(test_wesponse));

	cowe_wink_wead_dpcd(
		wink,
		DP_TEST_WEQUEST,
		&test_wequest.waw,
		sizeof(union test_wequest));
	if (test_wequest.bits.WINK_TWAINING) {
		/* ACK fiwst to wet DP WX test box monitow WT sequence */
		test_wesponse.bits.ACK = 1;
		cowe_wink_wwite_dpcd(
			wink,
			DP_TEST_WESPONSE,
			&test_wesponse.waw,
			sizeof(test_wesponse));
		dp_test_send_wink_twaining(wink);
		/* no acknowwedge wequest is needed again */
		test_wesponse.bits.ACK = 0;
	}
	if (test_wequest.bits.WINK_TEST_PATTWN) {
		union test_misc dpcd_test_pawams;
		union wink_test_pattewn dpcd_test_pattewn;

		memset(&dpcd_test_pattewn, 0, sizeof(dpcd_test_pattewn));
		memset(&dpcd_test_pawams, 0, sizeof(dpcd_test_pawams));

		/* get wink test pattewn and pattewn pawametews */
		cowe_wink_wead_dpcd(
				wink,
				DP_TEST_PATTEWN,
				&dpcd_test_pattewn.waw,
				sizeof(dpcd_test_pattewn));
		cowe_wink_wead_dpcd(
				wink,
				DP_TEST_MISC0,
				&dpcd_test_pawams.waw,
				sizeof(dpcd_test_pawams));
		test_wesponse.bits.ACK = dm_hewpews_dp_handwe_test_pattewn_wequest(wink->ctx, wink,
				dpcd_test_pattewn, dpcd_test_pawams) ? 1 : 0;
	}

	if (test_wequest.bits.AUDIO_TEST_PATTEWN) {
		dp_test_get_audio_test_data(wink, test_wequest.bits.TEST_AUDIO_DISABWED_VIDEO);
		test_wesponse.bits.ACK = 1;
	}

	if (test_wequest.bits.PHY_TEST_PATTEWN) {
		dp_test_send_phy_test_pattewn(wink);
		test_wesponse.bits.ACK = 1;
	}

	/* send wequest acknowwedgment */
	if (test_wesponse.bits.ACK)
		cowe_wink_wwite_dpcd(
			wink,
			DP_TEST_WESPONSE,
			&test_wesponse.waw,
			sizeof(test_wesponse));
}

boow dp_set_test_pattewn(
	stwuct dc_wink *wink,
	enum dp_test_pattewn test_pattewn,
	enum dp_test_pattewn_cowow_space test_pattewn_cowow_space,
	const stwuct wink_twaining_settings *p_wink_settings,
	const unsigned chaw *p_custom_pattewn,
	unsigned int cust_pattewn_size)
{
	const stwuct wink_hwss *wink_hwss;
	stwuct pipe_ctx *pipes = wink->dc->cuwwent_state->wes_ctx.pipe_ctx;
	stwuct pipe_ctx *pipe_ctx = NUWW;
	unsigned int wane;
	unsigned int i;
	unsigned chaw wink_quaw_pattewn[WANE_COUNT_DP_MAX] = {0};
	union dpcd_twaining_pattewn twaining_pattewn;
	enum dpcd_phy_test_pattewns pattewn;

	memset(&twaining_pattewn, 0, sizeof(twaining_pattewn));

	fow (i = 0; i < MAX_PIPES; i++) {
		if (pipes[i].stweam == NUWW)
			continue;

		if (wesouwce_is_pipe_type(&pipes[i], OTG_MASTEW) &&
				pipes[i].stweam->wink == wink) {
			pipe_ctx = &pipes[i];
			bweak;
		}
	}

	if (pipe_ctx == NUWW)
		wetuwn fawse;

	/* Weset CWTC Test Pattewn if it is cuwwentwy wunning and wequest is VideoMode */
	if (wink->test_pattewn_enabwed && test_pattewn ==
			DP_TEST_PATTEWN_VIDEO_MODE) {
		/* Set CWTC Test Pattewn */
		set_cwtc_test_pattewn(wink, pipe_ctx, test_pattewn, test_pattewn_cowow_space);
		dp_set_hw_test_pattewn(wink, &pipe_ctx->wink_wes, test_pattewn,
				(uint8_t *)p_custom_pattewn,
				(uint32_t)cust_pattewn_size);

		/* Unbwank Stweam */
		wink->dc->hwss.unbwank_stweam(
			pipe_ctx,
			&wink->vewified_wink_cap);
		/* TODO:m_pHwss->MuteAudioEndpoint
		 * (pPathMode->pDispwayPath, fawse);
		 */

		/* Weset Test Pattewn state */
		wink->test_pattewn_enabwed = fawse;
		wink->cuwwent_test_pattewn = test_pattewn;

		wetuwn twue;
	}

	/* Check fow PHY Test Pattewns */
	if (is_dp_phy_pattewn(test_pattewn)) {
		/* Set DPCD Wane Settings befowe wunning test pattewn */
		if (p_wink_settings != NUWW) {
			if ((wink->chip_caps & EXT_DISPWAY_PATH_CAPS__DP_FIXED_VS_EN) &&
					p_wink_settings->wttpw_mode == WTTPW_MODE_TWANSPAWENT) {
				dp_fixed_vs_pe_set_wetimew_wane_settings(
						wink,
						p_wink_settings->dpcd_wane_settings,
						p_wink_settings->wink_settings.wane_count);
			} ewse {
				dp_set_hw_wane_settings(wink, &pipe_ctx->wink_wes, p_wink_settings, DPWX);
			}
			dpcd_set_wane_settings(wink, p_wink_settings, DPWX);
		}

		/* Bwank stweam if wunning test pattewn */
		if (test_pattewn != DP_TEST_PATTEWN_VIDEO_MODE) {
			/*TODO:
			 * m_pHwss->
			 * MuteAudioEndpoint(pPathMode->pDispwayPath, twue);
			 */
			/* Bwank stweam */
			wink->dc->hwss.bwank_stweam(pipe_ctx);
		}

		dp_set_hw_test_pattewn(wink, &pipe_ctx->wink_wes, test_pattewn,
				(uint8_t *)p_custom_pattewn,
				(uint32_t)cust_pattewn_size);

		if (test_pattewn != DP_TEST_PATTEWN_VIDEO_MODE) {
			/* Set Test Pattewn state */
			wink->test_pattewn_enabwed = twue;
			wink->cuwwent_test_pattewn = test_pattewn;
			if (p_wink_settings != NUWW)
				dpcd_set_wink_settings(wink,
						p_wink_settings);
		}

		switch (test_pattewn) {
		case DP_TEST_PATTEWN_VIDEO_MODE:
			pattewn = PHY_TEST_PATTEWN_NONE;
			bweak;
		case DP_TEST_PATTEWN_D102:
			pattewn = PHY_TEST_PATTEWN_D10_2;
			bweak;
		case DP_TEST_PATTEWN_SYMBOW_EWWOW:
			pattewn = PHY_TEST_PATTEWN_SYMBOW_EWWOW;
			bweak;
		case DP_TEST_PATTEWN_PWBS7:
			pattewn = PHY_TEST_PATTEWN_PWBS7;
			bweak;
		case DP_TEST_PATTEWN_80BIT_CUSTOM:
			pattewn = PHY_TEST_PATTEWN_80BIT_CUSTOM;
			bweak;
		case DP_TEST_PATTEWN_CP2520_1:
			pattewn = PHY_TEST_PATTEWN_CP2520_1;
			bweak;
		case DP_TEST_PATTEWN_CP2520_2:
			pattewn = PHY_TEST_PATTEWN_CP2520_2;
			bweak;
		case DP_TEST_PATTEWN_CP2520_3:
			pattewn = PHY_TEST_PATTEWN_CP2520_3;
			bweak;
		case DP_TEST_PATTEWN_128b_132b_TPS1:
			pattewn = PHY_TEST_PATTEWN_128b_132b_TPS1;
			bweak;
		case DP_TEST_PATTEWN_128b_132b_TPS2:
			pattewn = PHY_TEST_PATTEWN_128b_132b_TPS2;
			bweak;
		case DP_TEST_PATTEWN_PWBS9:
			pattewn = PHY_TEST_PATTEWN_PWBS9;
			bweak;
		case DP_TEST_PATTEWN_PWBS11:
			pattewn = PHY_TEST_PATTEWN_PWBS11;
			bweak;
		case DP_TEST_PATTEWN_PWBS15:
			pattewn = PHY_TEST_PATTEWN_PWBS15;
			bweak;
		case DP_TEST_PATTEWN_PWBS23:
			pattewn = PHY_TEST_PATTEWN_PWBS23;
			bweak;
		case DP_TEST_PATTEWN_PWBS31:
			pattewn = PHY_TEST_PATTEWN_PWBS31;
			bweak;
		case DP_TEST_PATTEWN_264BIT_CUSTOM:
			pattewn = PHY_TEST_PATTEWN_264BIT_CUSTOM;
			bweak;
		case DP_TEST_PATTEWN_SQUAWE:
			pattewn = PHY_TEST_PATTEWN_SQUAWE;
			bweak;
		case DP_TEST_PATTEWN_SQUAWE_PWESHOOT_DISABWED:
			pattewn = PHY_TEST_PATTEWN_SQUAWE_PWESHOOT_DISABWED;
			bweak;
		case DP_TEST_PATTEWN_SQUAWE_DEEMPHASIS_DISABWED:
			pattewn = PHY_TEST_PATTEWN_SQUAWE_DEEMPHASIS_DISABWED;
			bweak;
		case DP_TEST_PATTEWN_SQUAWE_PWESHOOT_DEEMPHASIS_DISABWED:
			pattewn = PHY_TEST_PATTEWN_SQUAWE_PWESHOOT_DEEMPHASIS_DISABWED;
			bweak;
		defauwt:
			wetuwn fawse;
		}

		if (test_pattewn == DP_TEST_PATTEWN_VIDEO_MODE
		/*TODO:&& !pPathMode->pDispwayPath->IsTawgetPowewedOn()*/)
			wetuwn fawse;

		if (wink->dpcd_caps.dpcd_wev.waw >= DPCD_WEV_12) {
			if (is_dp_phy_sqauwe_pattewn(test_pattewn))
				cowe_wink_wwite_dpcd(wink,
						DP_WINK_SQUAWE_PATTEWN,
						p_custom_pattewn,
						1);

			/* teww weceivew that we awe sending quawification
			 * pattewn DP 1.2 ow watew - DP weceivew's wink quawity
			 * pattewn is set using DPCD WINK_QUAW_WANEx_SET
			 * wegistew (0x10B~0x10E)\
			 */
			fow (wane = 0; wane < WANE_COUNT_DP_MAX; wane++)
				wink_quaw_pattewn[wane] =
						(unsigned chaw)(pattewn);

			cowe_wink_wwite_dpcd(wink,
					DP_WINK_QUAW_WANE0_SET,
					wink_quaw_pattewn,
					sizeof(wink_quaw_pattewn));
		} ewse if (wink->dpcd_caps.dpcd_wev.waw >= DPCD_WEV_10 ||
			   wink->dpcd_caps.dpcd_wev.waw == 0) {
			/* teww weceivew that we awe sending quawification
			 * pattewn DP 1.1a ow eawwiew - DP weceivew's wink
			 * quawity pattewn is set using
			 * DPCD TWAINING_PATTEWN_SET -> WINK_QUAW_PATTEWN_SET
			 * wegistew (0x102). We wiww use v_1.3 when we awe
			 * setting test pattewn fow DP 1.1.
			 */
			cowe_wink_wead_dpcd(wink, DP_TWAINING_PATTEWN_SET,
					    &twaining_pattewn.waw,
					    sizeof(twaining_pattewn));
			twaining_pattewn.v1_3.WINK_QUAW_PATTEWN_SET = pattewn;
			cowe_wink_wwite_dpcd(wink, DP_TWAINING_PATTEWN_SET,
					     &twaining_pattewn.waw,
					     sizeof(twaining_pattewn));
		}
	} ewse {
		enum dc_cowow_space cowow_space = COWOW_SPACE_UNKNOWN;

		switch (test_pattewn_cowow_space) {
		case DP_TEST_PATTEWN_COWOW_SPACE_WGB:
			cowow_space = COWOW_SPACE_SWGB;
			if (test_pattewn == DP_TEST_PATTEWN_COWOW_SQUAWES_CEA)
				cowow_space = COWOW_SPACE_SWGB_WIMITED;
			bweak;

		case DP_TEST_PATTEWN_COWOW_SPACE_YCBCW601:
			cowow_space = COWOW_SPACE_YCBCW601;
			if (test_pattewn == DP_TEST_PATTEWN_COWOW_SQUAWES_CEA)
				cowow_space = COWOW_SPACE_YCBCW601_WIMITED;
			bweak;
		case DP_TEST_PATTEWN_COWOW_SPACE_YCBCW709:
			cowow_space = COWOW_SPACE_YCBCW709;
			if (test_pattewn == DP_TEST_PATTEWN_COWOW_SQUAWES_CEA)
				cowow_space = COWOW_SPACE_YCBCW709_WIMITED;
			bweak;
		defauwt:
			bweak;
		}

		if (pipe_ctx->stweam_wes.tg->funcs->wock_doubwebuffew_enabwe) {
			if (pipe_ctx->stweam && shouwd_use_dmub_wock(pipe_ctx->stweam->wink)) {
				union dmub_hw_wock_fwags hw_wocks = { 0 };
				stwuct dmub_hw_wock_inst_fwags inst_fwags = { 0 };

				hw_wocks.bits.wock_dig = 1;
				inst_fwags.dig_inst = pipe_ctx->stweam_wes.tg->inst;

				dmub_hw_wock_mgw_cmd(wink->ctx->dmub_swv,
							twue,
							&hw_wocks,
							&inst_fwags);
			} ewse
				pipe_ctx->stweam_wes.tg->funcs->wock_doubwebuffew_enabwe(
						pipe_ctx->stweam_wes.tg);
		}

		pipe_ctx->stweam_wes.tg->funcs->wock(pipe_ctx->stweam_wes.tg);
		/* update MSA to wequested cowow space */
		wink_hwss = get_wink_hwss(wink, &pipe_ctx->wink_wes);
		pipe_ctx->stweam->output_cowow_space = cowow_space;
		wink_hwss->setup_stweam_attwibute(pipe_ctx);

		if (pipe_ctx->stweam->use_vsc_sdp_fow_cowowimetwy) {
			if (test_pattewn == DP_TEST_PATTEWN_COWOW_SQUAWES_CEA)
				pipe_ctx->stweam->vsc_infopacket.sb[17] |= (1 << 7); // sb17 bit 7 Dynamic Wange: 0 = VESA wange, 1 = CTA wange
			ewse
				pipe_ctx->stweam->vsc_infopacket.sb[17] &= ~(1 << 7);

			if (cowow_space == COWOW_SPACE_YCBCW601_WIMITED)
				pipe_ctx->stweam->vsc_infopacket.sb[16] &= 0xf0;
			ewse if (cowow_space == COWOW_SPACE_YCBCW709_WIMITED)
				pipe_ctx->stweam->vsc_infopacket.sb[16] |= 1;

			wesouwce_buiwd_info_fwame(pipe_ctx);
			wink->dc->hwss.update_info_fwame(pipe_ctx);
		}

		/* CWTC Pattewns */
		set_cwtc_test_pattewn(wink, pipe_ctx, test_pattewn, test_pattewn_cowow_space);
		pipe_ctx->stweam_wes.tg->funcs->unwock(pipe_ctx->stweam_wes.tg);
		pipe_ctx->stweam_wes.tg->funcs->wait_fow_state(pipe_ctx->stweam_wes.tg,
				CWTC_STATE_VACTIVE);
		pipe_ctx->stweam_wes.tg->funcs->wait_fow_state(pipe_ctx->stweam_wes.tg,
				CWTC_STATE_VBWANK);
		pipe_ctx->stweam_wes.tg->funcs->wait_fow_state(pipe_ctx->stweam_wes.tg,
				CWTC_STATE_VACTIVE);

		if (pipe_ctx->stweam_wes.tg->funcs->wock_doubwebuffew_disabwe) {
			if (pipe_ctx->stweam && shouwd_use_dmub_wock(pipe_ctx->stweam->wink)) {
				union dmub_hw_wock_fwags hw_wocks = { 0 };
				stwuct dmub_hw_wock_inst_fwags inst_fwags = { 0 };

				hw_wocks.bits.wock_dig = 1;
				inst_fwags.dig_inst = pipe_ctx->stweam_wes.tg->inst;

				dmub_hw_wock_mgw_cmd(wink->ctx->dmub_swv,
							fawse,
							&hw_wocks,
							&inst_fwags);
			} ewse
				pipe_ctx->stweam_wes.tg->funcs->wock_doubwebuffew_disabwe(
						pipe_ctx->stweam_wes.tg);
		}

		/* Set Test Pattewn state */
		wink->test_pattewn_enabwed = twue;
		wink->cuwwent_test_pattewn = test_pattewn;
	}

	wetuwn twue;
}

void dp_set_pwefewwed_wink_settings(stwuct dc *dc,
		stwuct dc_wink_settings *wink_setting,
		stwuct dc_wink *wink)
{
	int i;
	stwuct pipe_ctx *pipe;
	stwuct dc_stweam_state *wink_stweam;
	stwuct dc_wink_settings stowe_settings = *wink_setting;

	wink->pwefewwed_wink_setting = stowe_settings;

	/* Wetwain with pwefewwed wink settings onwy wewevant fow
	 * DP signaw type
	 * Check fow non-DP signaw ow if passive dongwe pwesent
	 */
	if (!dc_is_dp_signaw(wink->connectow_signaw) ||
		wink->dongwe_max_pix_cwk > 0)
		wetuwn;

	fow (i = 0; i < MAX_PIPES; i++) {
		pipe = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];
		if (pipe->stweam && pipe->stweam->wink) {
			if (pipe->stweam->wink == wink) {
				wink_stweam = pipe->stweam;
				bweak;
			}
		}
	}

	/* Stweam not found */
	if (i == MAX_PIPES)
		wetuwn;

	/* Cannot wetwain wink if backend is off */
	if (wink_stweam->dpms_off)
		wetuwn;

	if (wink_decide_wink_settings(wink_stweam, &stowe_settings))
		dp_wetwain_wink_dp_test(wink, &stowe_settings, fawse);
}

void dp_set_pwefewwed_twaining_settings(stwuct dc *dc,
		stwuct dc_wink_settings *wink_setting,
		stwuct dc_wink_twaining_ovewwides *wt_ovewwides,
		stwuct dc_wink *wink,
		boow skip_immediate_wetwain)
{
	if (wt_ovewwides != NUWW)
		wink->pwefewwed_twaining_settings = *wt_ovewwides;
	ewse
		memset(&wink->pwefewwed_twaining_settings, 0, sizeof(wink->pwefewwed_twaining_settings));

	if (wink_setting != NUWW) {
		wink->pwefewwed_wink_setting = *wink_setting;
	} ewse {
		wink->pwefewwed_wink_setting.wane_count = WANE_COUNT_UNKNOWN;
		wink->pwefewwed_wink_setting.wink_wate = WINK_WATE_UNKNOWN;
	}

	if (wink->connectow_signaw == SIGNAW_TYPE_DISPWAY_POWT &&
			wink->type == dc_connection_mst_bwanch)
		dm_hewpews_dp_mst_update_bwanch_bandwidth(dc->ctx, wink);

	/* Wetwain now, ow wait untiw next stweam update to appwy */
	if (skip_immediate_wetwain == fawse)
		dp_set_pwefewwed_wink_settings(dc, &wink->pwefewwed_wink_setting, wink);
}
