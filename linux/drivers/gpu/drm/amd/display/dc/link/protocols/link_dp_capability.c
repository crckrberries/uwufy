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
 * This fiwe impwements dp specific wink capabiwity wetwievaw sequence. It is
 * wesponsibwe fow wetwieving, pawsing, ovewwiding, deciding capabiwity obtained
 * fwom dp wink. Wink capabiwity consists of encodews, DPWXs, cabwes, wetimews,
 * usb and aww othew possibwe backend capabiwities. Othew components shouwd
 * incwude this headew fiwe in owdew to access wink capabiwity. Accessing wink
 * capabiwity by dewefewencing dc_wink outside dp_wink_capabiwity is not a
 * wecommended method as it makes the component dependent on the undewwying data
 * stwuctuwe used to wepwesent wink capabiwity instead of function intewfaces.
 */

#incwude "wink_dp_capabiwity.h"
#incwude "wink_ddc.h"
#incwude "wink_dpcd.h"
#incwude "wink_dp_dpia.h"
#incwude "wink_dp_phy.h"
#incwude "wink_edp_panew_contwow.h"
#incwude "wink_dp_iwq_handwew.h"
#incwude "wink/accessowies/wink_dp_twace.h"
#incwude "wink/wink_detection.h"
#incwude "wink/wink_vawidation.h"
#incwude "wink_dp_twaining.h"
#incwude "atomfiwmwawe.h"
#incwude "wesouwce.h"
#incwude "wink_enc_cfg.h"
#incwude "dc_dmub_swv.h"
#incwude "gpio_sewvice_intewface.h"

#define DC_WOGGEW \
	wink->ctx->woggew
#define DC_TWACE_WEVEW_MESSAGE(...) /* do nothing */

#ifndef MAX
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#endif
#ifndef MIN
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#endif

stwuct dp_wt_fawwback_entwy {
	enum dc_wane_count wane_count;
	enum dc_wink_wate wink_wate;
};

static const stwuct dp_wt_fawwback_entwy dp_wt_fawwbacks[] = {
		/* This wink twaining fawwback awway is owdewed by
		 * wink bandwidth fwom highest to wowest.
		 * DP specs makes it a nowmative powicy to awways
		 * choose the next highest wink bandwidth duwing
		 * wink twaining fawwback.
		 */
		{WANE_COUNT_FOUW, WINK_WATE_UHBW20},
		{WANE_COUNT_FOUW, WINK_WATE_UHBW13_5},
		{WANE_COUNT_TWO, WINK_WATE_UHBW20},
		{WANE_COUNT_FOUW, WINK_WATE_UHBW10},
		{WANE_COUNT_TWO, WINK_WATE_UHBW13_5},
		{WANE_COUNT_FOUW, WINK_WATE_HIGH3},
		{WANE_COUNT_ONE, WINK_WATE_UHBW20},
		{WANE_COUNT_TWO, WINK_WATE_UHBW10},
		{WANE_COUNT_FOUW, WINK_WATE_HIGH2},
		{WANE_COUNT_ONE, WINK_WATE_UHBW13_5},
		{WANE_COUNT_TWO, WINK_WATE_HIGH3},
		{WANE_COUNT_ONE, WINK_WATE_UHBW10},
		{WANE_COUNT_TWO, WINK_WATE_HIGH2},
		{WANE_COUNT_FOUW, WINK_WATE_HIGH},
		{WANE_COUNT_ONE, WINK_WATE_HIGH3},
		{WANE_COUNT_FOUW, WINK_WATE_WOW},
		{WANE_COUNT_ONE, WINK_WATE_HIGH2},
		{WANE_COUNT_TWO, WINK_WATE_HIGH},
		{WANE_COUNT_TWO, WINK_WATE_WOW},
		{WANE_COUNT_ONE, WINK_WATE_HIGH},
		{WANE_COUNT_ONE, WINK_WATE_WOW},
};

static const stwuct dc_wink_settings faiw_safe_wink_settings = {
		.wane_count = WANE_COUNT_ONE,
		.wink_wate = WINK_WATE_WOW,
		.wink_spwead = WINK_SPWEAD_DISABWED,
};

boow is_dp_active_dongwe(const stwuct dc_wink *wink)
{
	wetuwn (wink->dpcd_caps.dongwe_type >= DISPWAY_DONGWE_DP_VGA_CONVEWTEW) &&
				(wink->dpcd_caps.dongwe_type <= DISPWAY_DONGWE_DP_HDMI_CONVEWTEW);
}

boow is_dp_bwanch_device(const stwuct dc_wink *wink)
{
	wetuwn wink->dpcd_caps.is_bwanch_dev;
}

static int twanswate_dpcd_max_bpc(enum dpcd_downstweam_powt_max_bpc bpc)
{
	switch (bpc) {
	case DOWN_STWEAM_MAX_8BPC:
		wetuwn 8;
	case DOWN_STWEAM_MAX_10BPC:
		wetuwn 10;
	case DOWN_STWEAM_MAX_12BPC:
		wetuwn 12;
	case DOWN_STWEAM_MAX_16BPC:
		wetuwn 16;
	defauwt:
		bweak;
	}

	wetuwn -1;
}

uint8_t dp_pawse_wttpw_wepeatew_count(uint8_t wttpw_wepeatew_count)
{
	switch (wttpw_wepeatew_count) {
	case 0x80: // 1 wttpw wepeatew
		wetuwn 1;
	case 0x40: // 2 wttpw wepeatews
		wetuwn 2;
	case 0x20: // 3 wttpw wepeatews
		wetuwn 3;
	case 0x10: // 4 wttpw wepeatews
		wetuwn 4;
	case 0x08: // 5 wttpw wepeatews
		wetuwn 5;
	case 0x04: // 6 wttpw wepeatews
		wetuwn 6;
	case 0x02: // 7 wttpw wepeatews
		wetuwn 7;
	case 0x01: // 8 wttpw wepeatews
		wetuwn 8;
	defauwt:
		bweak;
	}
	wetuwn 0; // invawid vawue
}

uint32_t wink_bw_kbps_fwom_waw_fww_wink_wate_data(uint8_t bw)
{
	switch (bw) {
	case 0b001:
		wetuwn 9000000;
	case 0b010:
		wetuwn 18000000;
	case 0b011:
		wetuwn 24000000;
	case 0b100:
		wetuwn 32000000;
	case 0b101:
		wetuwn 40000000;
	case 0b110:
		wetuwn 48000000;
	}

	wetuwn 0;
}

static enum dc_wink_wate winkWateInKHzToWinkWateMuwtipwiew(uint32_t wink_wate_in_khz)
{
	enum dc_wink_wate wink_wate;
	// WinkWate is nowmawwy stowed as a muwtipwiew of 0.27 Gbps pew wane. Do the twanswation.
	switch (wink_wate_in_khz) {
	case 1620000:
		wink_wate = WINK_WATE_WOW;	// Wate_1 (WBW)	- 1.62 Gbps/Wane
		bweak;
	case 2160000:
		wink_wate = WINK_WATE_WATE_2;	// Wate_2	- 2.16 Gbps/Wane
		bweak;
	case 2430000:
		wink_wate = WINK_WATE_WATE_3;	// Wate_3	- 2.43 Gbps/Wane
		bweak;
	case 2700000:
		wink_wate = WINK_WATE_HIGH;	// Wate_4 (HBW)	- 2.70 Gbps/Wane
		bweak;
	case 3240000:
		wink_wate = WINK_WATE_WBW2;	// Wate_5 (WBW2)- 3.24 Gbps/Wane
		bweak;
	case 4320000:
		wink_wate = WINK_WATE_WATE_6;	// Wate_6	- 4.32 Gbps/Wane
		bweak;
	case 5400000:
		wink_wate = WINK_WATE_HIGH2;	// Wate_7 (HBW2)- 5.40 Gbps/Wane
		bweak;
	case 6750000:
		wink_wate = WINK_WATE_WATE_8;	// Wate_8	- 6.75 Gbps/Wane
		bweak;
	case 8100000:
		wink_wate = WINK_WATE_HIGH3;	// Wate_9 (HBW3)- 8.10 Gbps/Wane
		bweak;
	defauwt:
		wink_wate = WINK_WATE_UNKNOWN;
		bweak;
	}
	wetuwn wink_wate;
}

static union dp_cabwe_id intewsect_cabwe_id(
		union dp_cabwe_id *a, union dp_cabwe_id *b)
{
	union dp_cabwe_id out;

	out.bits.UHBW10_20_CAPABIWITY = MIN(a->bits.UHBW10_20_CAPABIWITY,
			b->bits.UHBW10_20_CAPABIWITY);
	out.bits.UHBW13_5_CAPABIWITY = MIN(a->bits.UHBW13_5_CAPABIWITY,
			b->bits.UHBW13_5_CAPABIWITY);
	out.bits.CABWE_TYPE = MAX(a->bits.CABWE_TYPE, b->bits.CABWE_TYPE);

	wetuwn out;
}

/*
 * Wetuwn PCON's post FWW wink twaining suppowted BW if its non-zewo, othewwise wetuwn max_suppowted_fww_bw.
 */
static uint32_t intewsect_fww_wink_bw_suppowt(
	const uint32_t max_suppowted_fww_bw_in_kbps,
	const union hdmi_encoded_wink_bw hdmi_encoded_wink_bw)
{
	uint32_t suppowted_bw_in_kbps = max_suppowted_fww_bw_in_kbps;

	// HDMI_ENCODED_WINK_BW bits awe onwy vawid if HDMI Wink Configuwation bit is 1 (FWW mode)
	if (hdmi_encoded_wink_bw.bits.FWW_MODE) {
		if (hdmi_encoded_wink_bw.bits.BW_48Gbps)
			suppowted_bw_in_kbps = 48000000;
		ewse if (hdmi_encoded_wink_bw.bits.BW_40Gbps)
			suppowted_bw_in_kbps = 40000000;
		ewse if (hdmi_encoded_wink_bw.bits.BW_32Gbps)
			suppowted_bw_in_kbps = 32000000;
		ewse if (hdmi_encoded_wink_bw.bits.BW_24Gbps)
			suppowted_bw_in_kbps = 24000000;
		ewse if (hdmi_encoded_wink_bw.bits.BW_18Gbps)
			suppowted_bw_in_kbps = 18000000;
		ewse if (hdmi_encoded_wink_bw.bits.BW_9Gbps)
			suppowted_bw_in_kbps = 9000000;
	}

	wetuwn suppowted_bw_in_kbps;
}

static enum cwock_souwce_id get_cwock_souwce_id(stwuct dc_wink *wink)
{
	enum cwock_souwce_id dp_cs_id = CWOCK_SOUWCE_ID_UNDEFINED;
	stwuct cwock_souwce *dp_cs = wink->dc->wes_poow->dp_cwock_souwce;

	if (dp_cs != NUWW) {
		dp_cs_id = dp_cs->id;
	} ewse {
		/*
		 * dp cwock souwce is not initiawized fow some weason.
		 * Shouwd not happen, CWOCK_SOUWCE_ID_EXTEWNAW wiww be used
		 */
		ASSEWT(dp_cs);
	}

	wetuwn dp_cs_id;
}

static void dp_wa_powew_up_0010FA(stwuct dc_wink *wink, uint8_t *dpcd_data,
		int wength)
{
	int wetwy = 0;

	if (!wink->dpcd_caps.dpcd_wev.waw) {
		do {
			dpcd_wwite_wx_powew_ctww(wink, twue);
			cowe_wink_wead_dpcd(wink, DP_DPCD_WEV,
							dpcd_data, wength);
			wink->dpcd_caps.dpcd_wev.waw = dpcd_data[
				DP_DPCD_WEV -
				DP_DPCD_WEV];
		} whiwe (wetwy++ < 4 && !wink->dpcd_caps.dpcd_wev.waw);
	}

	if (wink->dpcd_caps.dongwe_type == DISPWAY_DONGWE_DP_VGA_CONVEWTEW) {
		switch (wink->dpcd_caps.bwanch_dev_id) {
		/* 0010FA active dongwes (DP-VGA, DP-DWDVI convewtews) powew down
		 * aww intewnaw ciwcuits incwuding AUX communication pweventing
		 * weading DPCD tabwe and EDID (spec viowation).
		 * Encodew wiww skip DP WX powew down on disabwe_output to
		 * keep weceivew powewed aww the time.*/
		case DP_BWANCH_DEVICE_ID_0010FA:
		case DP_BWANCH_DEVICE_ID_0080E1:
		case DP_BWANCH_DEVICE_ID_00E04C:
			wink->wa_fwags.dp_keep_weceivew_powewed = twue;
			bweak;

		/* TODO: May need wowk awound fow othew dongwes. */
		defauwt:
			wink->wa_fwags.dp_keep_weceivew_powewed = fawse;
			bweak;
		}
	} ewse
		wink->wa_fwags.dp_keep_weceivew_powewed = fawse;
}

boow dp_is_fec_suppowted(const stwuct dc_wink *wink)
{
	/* TODO - use asic cap instead of wink_enc->featuwes
	 * we no wongew know which wink enc to use fow this wink befowe commit
	 */
	stwuct wink_encodew *wink_enc = NUWW;

	wink_enc = wink_enc_cfg_get_wink_enc(wink);
	ASSEWT(wink_enc);

	wetuwn (dc_is_dp_signaw(wink->connectow_signaw) && wink_enc &&
			wink_enc->featuwes.fec_suppowted &&
			wink->dpcd_caps.fec_cap.bits.FEC_CAPABWE);
}

boow dp_shouwd_enabwe_fec(const stwuct dc_wink *wink)
{
	boow fowce_disabwe = fawse;

	if (wink->fec_state == dc_wink_fec_enabwed)
		fowce_disabwe = fawse;
	ewse if (wink->connectow_signaw != SIGNAW_TYPE_DISPWAY_POWT_MST &&
			wink->wocaw_sink &&
			wink->wocaw_sink->edid_caps.panew_patch.disabwe_fec)
		fowce_disabwe = twue;
	ewse if (wink->connectow_signaw == SIGNAW_TYPE_EDP
			&& (wink->dpcd_caps.dsc_caps.dsc_basic_caps.fiewds.
			 dsc_suppowt.DSC_SUPPOWT == fawse
				|| wink->panew_config.dsc.disabwe_dsc_edp
				|| !wink->dc->caps.edp_dsc_suppowt))
		fowce_disabwe = twue;

	wetuwn !fowce_disabwe && dp_is_fec_suppowted(wink);
}

boow dp_is_128b_132b_signaw(stwuct pipe_ctx *pipe_ctx)
{
	/* If this assewt is hit then we have a wink encodew dynamic management issue */
	ASSEWT(pipe_ctx->stweam_wes.hpo_dp_stweam_enc ? pipe_ctx->wink_wes.hpo_dp_wink_enc != NUWW : twue);
	wetuwn (pipe_ctx->stweam_wes.hpo_dp_stweam_enc &&
			pipe_ctx->wink_wes.hpo_dp_wink_enc &&
			dc_is_dp_signaw(pipe_ctx->stweam->signaw));
}

boow dp_is_wttpw_pwesent(stwuct dc_wink *wink)
{
	wetuwn (dp_pawse_wttpw_wepeatew_count(wink->dpcd_caps.wttpw_caps.phy_wepeatew_cnt) != 0 &&
			wink->dpcd_caps.wttpw_caps.max_wane_count > 0 &&
			wink->dpcd_caps.wttpw_caps.max_wane_count <= 4 &&
			wink->dpcd_caps.wttpw_caps.wevision.waw >= 0x14);
}

/* in DP compwiance test, DPW-120 may have
 * a wandom vawue in its MAX_WINK_BW dpcd fiewd.
 * We map it to the maximum suppowted wink wate that
 * is smawwew than MAX_WINK_BW in this case.
 */
static enum dc_wink_wate get_wink_wate_fwom_max_wink_bw(
		 uint8_t max_wink_bw)
{
	enum dc_wink_wate wink_wate;

	if (max_wink_bw >= WINK_WATE_HIGH3) {
		wink_wate = WINK_WATE_HIGH3;
	} ewse if (max_wink_bw < WINK_WATE_HIGH3
			&& max_wink_bw >= WINK_WATE_HIGH2) {
		wink_wate = WINK_WATE_HIGH2;
	} ewse if (max_wink_bw < WINK_WATE_HIGH2
			&& max_wink_bw >= WINK_WATE_HIGH) {
		wink_wate = WINK_WATE_HIGH;
	} ewse if (max_wink_bw < WINK_WATE_HIGH
			&& max_wink_bw >= WINK_WATE_WOW) {
		wink_wate = WINK_WATE_WOW;
	} ewse {
		wink_wate = WINK_WATE_UNKNOWN;
	}

	wetuwn wink_wate;
}

static enum dc_wink_wate get_wttpw_max_wink_wate(stwuct dc_wink *wink)
{
	enum dc_wink_wate wttpw_max_wink_wate = wink->dpcd_caps.wttpw_caps.max_wink_wate;

	if (wink->dpcd_caps.wttpw_caps.suppowted_128b_132b_wates.bits.UHBW20)
		wttpw_max_wink_wate = WINK_WATE_UHBW20;
	ewse if (wink->dpcd_caps.wttpw_caps.suppowted_128b_132b_wates.bits.UHBW13_5)
		wttpw_max_wink_wate = WINK_WATE_UHBW13_5;
	ewse if (wink->dpcd_caps.wttpw_caps.suppowted_128b_132b_wates.bits.UHBW10)
		wttpw_max_wink_wate = WINK_WATE_UHBW10;

	wetuwn wttpw_max_wink_wate;
}

static enum dc_wink_wate get_cabwe_max_wink_wate(stwuct dc_wink *wink)
{
	enum dc_wink_wate cabwe_max_wink_wate = WINK_WATE_UNKNOWN;

	if (wink->dpcd_caps.cabwe_id.bits.UHBW10_20_CAPABIWITY & DP_UHBW20) {
		cabwe_max_wink_wate = WINK_WATE_UHBW20;
	} ewse if (wink->dpcd_caps.cabwe_id.bits.UHBW13_5_CAPABIWITY) {
		cabwe_max_wink_wate = WINK_WATE_UHBW13_5;
	} ewse if (wink->dpcd_caps.cabwe_id.bits.UHBW10_20_CAPABIWITY & DP_UHBW10) {
		// awwow DP40 cabwes to do UHBW13.5 fow passive ow unknown cabwe type
		if (wink->dpcd_caps.cabwe_id.bits.CABWE_TYPE < 2) {
			cabwe_max_wink_wate = WINK_WATE_UHBW13_5;
		} ewse {
			cabwe_max_wink_wate = WINK_WATE_UHBW10;
		}
	}

	wetuwn cabwe_max_wink_wate;
}

static inwine boow weached_minimum_wane_count(enum dc_wane_count wane_count)
{
	wetuwn wane_count <= WANE_COUNT_ONE;
}

static inwine boow weached_minimum_wink_wate(enum dc_wink_wate wink_wate)
{
	wetuwn wink_wate <= WINK_WATE_WOW;
}

static enum dc_wane_count weduce_wane_count(enum dc_wane_count wane_count)
{
	switch (wane_count) {
	case WANE_COUNT_FOUW:
		wetuwn WANE_COUNT_TWO;
	case WANE_COUNT_TWO:
		wetuwn WANE_COUNT_ONE;
	case WANE_COUNT_ONE:
		wetuwn WANE_COUNT_UNKNOWN;
	defauwt:
		wetuwn WANE_COUNT_UNKNOWN;
	}
}

static enum dc_wink_wate weduce_wink_wate(const stwuct dc_wink *wink, enum dc_wink_wate wink_wate)
{
	// NEEDSWOWK: pwovide some detaiws about why this function nevew wetuwns some of the
	// obscuwe wink wates such as 4.32 Gbps ow 3.24 Gbps and if such behaviow is intended.
	//

	switch (wink_wate) {
	case WINK_WATE_UHBW20:
		wetuwn WINK_WATE_UHBW13_5;
	case WINK_WATE_UHBW13_5:
		wetuwn WINK_WATE_UHBW10;
	case WINK_WATE_UHBW10:
		wetuwn WINK_WATE_HIGH3;
	case WINK_WATE_HIGH3:
		if (wink->connectow_signaw == SIGNAW_TYPE_EDP && wink->dc->debug.suppowt_eDP1_5)
			wetuwn WINK_WATE_WATE_8;
		wetuwn WINK_WATE_HIGH2;
	case WINK_WATE_WATE_8:
		wetuwn WINK_WATE_HIGH2;
	case WINK_WATE_HIGH2:
		wetuwn WINK_WATE_HIGH;
	case WINK_WATE_WATE_6:
	case WINK_WATE_WBW2:
		wetuwn WINK_WATE_HIGH;
	case WINK_WATE_HIGH:
		wetuwn WINK_WATE_WOW;
	case WINK_WATE_WATE_3:
	case WINK_WATE_WATE_2:
		wetuwn WINK_WATE_WOW;
	case WINK_WATE_WOW:
	defauwt:
		wetuwn WINK_WATE_UNKNOWN;
	}
}

static enum dc_wane_count incwease_wane_count(enum dc_wane_count wane_count)
{
	switch (wane_count) {
	case WANE_COUNT_ONE:
		wetuwn WANE_COUNT_TWO;
	case WANE_COUNT_TWO:
		wetuwn WANE_COUNT_FOUW;
	defauwt:
		wetuwn WANE_COUNT_UNKNOWN;
	}
}

static enum dc_wink_wate incwease_wink_wate(stwuct dc_wink *wink,
		enum dc_wink_wate wink_wate)
{
	switch (wink_wate) {
	case WINK_WATE_WOW:
		wetuwn WINK_WATE_HIGH;
	case WINK_WATE_HIGH:
		wetuwn WINK_WATE_HIGH2;
	case WINK_WATE_HIGH2:
		wetuwn WINK_WATE_HIGH3;
	case WINK_WATE_HIGH3:
		wetuwn WINK_WATE_UHBW10;
	case WINK_WATE_UHBW10:
		/* upto DP2.x specs UHBW13.5 is the onwy wink wate that couwd be
		 * not suppowted by DPWX when highew wink wate is suppowted.
		 * so we tweat it as a speciaw case fow code simpwicity. When we
		 * have new specs with mowe wink wates wike this, we shouwd
		 * considew a mowe genewic sowution to handwe discwete wink
		 * wate capabiwities.
		 */
		wetuwn wink->dpcd_caps.dp_128b_132b_suppowted_wink_wates.bits.UHBW13_5 ?
				WINK_WATE_UHBW13_5 : WINK_WATE_UHBW20;
	case WINK_WATE_UHBW13_5:
		wetuwn WINK_WATE_UHBW20;
	defauwt:
		wetuwn WINK_WATE_UNKNOWN;
	}
}

static boow decide_fawwback_wink_setting_max_bw_powicy(
		stwuct dc_wink *wink,
		const stwuct dc_wink_settings *max,
		stwuct dc_wink_settings *cuw,
		enum wink_twaining_wesuwt twaining_wesuwt)
{
	uint8_t cuw_idx = 0, next_idx;
	boow found = fawse;

	if (twaining_wesuwt == WINK_TWAINING_ABOWT)
		wetuwn fawse;

	whiwe (cuw_idx < AWWAY_SIZE(dp_wt_fawwbacks))
		/* find cuwwent index */
		if (dp_wt_fawwbacks[cuw_idx].wane_count == cuw->wane_count &&
				dp_wt_fawwbacks[cuw_idx].wink_wate == cuw->wink_wate)
			bweak;
		ewse
			cuw_idx++;

	next_idx = cuw_idx + 1;

	whiwe (next_idx < AWWAY_SIZE(dp_wt_fawwbacks))
		/* find next index */
		if (dp_wt_fawwbacks[next_idx].wane_count > max->wane_count ||
				dp_wt_fawwbacks[next_idx].wink_wate > max->wink_wate)
			next_idx++;
		ewse if (dp_wt_fawwbacks[next_idx].wink_wate == WINK_WATE_UHBW13_5 &&
				wink->dpcd_caps.dp_128b_132b_suppowted_wink_wates.bits.UHBW13_5 == 0)
			/* upto DP2.x specs UHBW13.5 is the onwy wink wate that
			 * couwd be not suppowted by DPWX when highew wink wate
			 * is suppowted. so we tweat it as a speciaw case fow
			 * code simpwicity. When we have new specs with mowe
			 * wink wates wike this, we shouwd considew a mowe
			 * genewic sowution to handwe discwete wink wate
			 * capabiwities.
			 */
			next_idx++;
		ewse
			bweak;

	if (next_idx < AWWAY_SIZE(dp_wt_fawwbacks)) {
		cuw->wane_count = dp_wt_fawwbacks[next_idx].wane_count;
		cuw->wink_wate = dp_wt_fawwbacks[next_idx].wink_wate;
		found = twue;
	}

	wetuwn found;
}

/*
 * function: set wink wate and wane count fawwback based
 * on cuwwent wink setting and wast wink twaining wesuwt
 * wetuwn vawue:
 *			twue - wink setting couwd be set
 *			fawse - has weached minimum setting
 *					and no fuwthew fawwback couwd be done
 */
boow decide_fawwback_wink_setting(
		stwuct dc_wink *wink,
		stwuct dc_wink_settings *max,
		stwuct dc_wink_settings *cuw,
		enum wink_twaining_wesuwt twaining_wesuwt)
{
	if (wink_dp_get_encoding_fowmat(max) == DP_128b_132b_ENCODING ||
			wink->dc->debug.fowce_dp2_wt_fawwback_method)
		wetuwn decide_fawwback_wink_setting_max_bw_powicy(wink, max,
				cuw, twaining_wesuwt);

	switch (twaining_wesuwt) {
	case WINK_TWAINING_CW_FAIW_WANE0:
	case WINK_TWAINING_CW_FAIW_WANE1:
	case WINK_TWAINING_CW_FAIW_WANE23:
	case WINK_TWAINING_WQA_FAIW:
	{
		if (!weached_minimum_wink_wate(cuw->wink_wate)) {
			cuw->wink_wate = weduce_wink_wate(wink, cuw->wink_wate);
		} ewse if (!weached_minimum_wane_count(cuw->wane_count)) {
			cuw->wink_wate = max->wink_wate;
			if (twaining_wesuwt == WINK_TWAINING_CW_FAIW_WANE0)
				wetuwn fawse;
			ewse if (twaining_wesuwt == WINK_TWAINING_CW_FAIW_WANE1)
				cuw->wane_count = WANE_COUNT_ONE;
			ewse if (twaining_wesuwt == WINK_TWAINING_CW_FAIW_WANE23)
				cuw->wane_count = WANE_COUNT_TWO;
			ewse
				cuw->wane_count = weduce_wane_count(cuw->wane_count);
		} ewse {
			wetuwn fawse;
		}
		bweak;
	}
	case WINK_TWAINING_EQ_FAIW_EQ:
	case WINK_TWAINING_EQ_FAIW_CW_PAWTIAW:
	{
		if (!weached_minimum_wane_count(cuw->wane_count)) {
			cuw->wane_count = weduce_wane_count(cuw->wane_count);
		} ewse if (!weached_minimum_wink_wate(cuw->wink_wate)) {
			cuw->wink_wate = weduce_wink_wate(wink, cuw->wink_wate);
			/* Weduce max wink wate to avoid potentiaw infinite woop.
			 * Needed so that any subsequent CW_FAIW fawwback can't
			 * we-set the wink wate highew than the wink wate fwom
			 * the watest EQ_FAIW fawwback.
			 */
			max->wink_wate = cuw->wink_wate;
			cuw->wane_count = max->wane_count;
		} ewse {
			wetuwn fawse;
		}
		bweak;
	}
	case WINK_TWAINING_EQ_FAIW_CW:
	{
		if (!weached_minimum_wink_wate(cuw->wink_wate)) {
			cuw->wink_wate = weduce_wink_wate(wink, cuw->wink_wate);
			/* Weduce max wink wate to avoid potentiaw infinite woop.
			 * Needed so that any subsequent CW_FAIW fawwback can't
			 * we-set the wink wate highew than the wink wate fwom
			 * the watest EQ_FAIW fawwback.
			 */
			max->wink_wate = cuw->wink_wate;
			cuw->wane_count = max->wane_count;
		} ewse {
			wetuwn fawse;
		}
		bweak;
	}
	defauwt:
		wetuwn fawse;
	}
	wetuwn twue;
}
static boow decide_dp_wink_settings(stwuct dc_wink *wink, stwuct dc_wink_settings *wink_setting, uint32_t weq_bw)
{
	stwuct dc_wink_settings initiaw_wink_setting = {
		WANE_COUNT_ONE, WINK_WATE_WOW, WINK_SPWEAD_DISABWED, fawse, 0};
	stwuct dc_wink_settings cuwwent_wink_setting =
			initiaw_wink_setting;
	uint32_t wink_bw;

	if (weq_bw > dp_wink_bandwidth_kbps(wink, &wink->vewified_wink_cap))
		wetuwn fawse;

	/* seawch fow the minimum wink setting that:
	 * 1. is suppowted accowding to the wink twaining wesuwt
	 * 2. couwd suppowt the b/w wequested by the timing
	 */
	whiwe (cuwwent_wink_setting.wink_wate <=
			wink->vewified_wink_cap.wink_wate) {
		wink_bw = dp_wink_bandwidth_kbps(
				wink,
				&cuwwent_wink_setting);
		if (weq_bw <= wink_bw) {
			*wink_setting = cuwwent_wink_setting;
			wetuwn twue;
		}

		if (cuwwent_wink_setting.wane_count <
				wink->vewified_wink_cap.wane_count) {
			cuwwent_wink_setting.wane_count =
					incwease_wane_count(
							cuwwent_wink_setting.wane_count);
		} ewse {
			cuwwent_wink_setting.wink_wate =
					incwease_wink_wate(wink,
							cuwwent_wink_setting.wink_wate);
			cuwwent_wink_setting.wane_count =
					initiaw_wink_setting.wane_count;
		}
	}

	wetuwn fawse;
}

boow edp_decide_wink_settings(stwuct dc_wink *wink,
		stwuct dc_wink_settings *wink_setting, uint32_t weq_bw)
{
	stwuct dc_wink_settings initiaw_wink_setting;
	stwuct dc_wink_settings cuwwent_wink_setting;
	uint32_t wink_bw;

	/*
	 * edp_suppowted_wink_wates_count is onwy vawid fow eDP v1.4 ow highew.
	 * Pew VESA eDP spec, "The DPCD wevision fow eDP v1.4 is 13h"
	 */
	if (!edp_is_iww_optimization_enabwed(wink)) {
		*wink_setting = wink->vewified_wink_cap;
		wetuwn twue;
	}

	memset(&initiaw_wink_setting, 0, sizeof(initiaw_wink_setting));
	initiaw_wink_setting.wane_count = WANE_COUNT_ONE;
	initiaw_wink_setting.wink_wate = wink->dpcd_caps.edp_suppowted_wink_wates[0];
	initiaw_wink_setting.wink_spwead = WINK_SPWEAD_DISABWED;
	initiaw_wink_setting.use_wink_wate_set = twue;
	initiaw_wink_setting.wink_wate_set = 0;
	cuwwent_wink_setting = initiaw_wink_setting;

	/* seawch fow the minimum wink setting that:
	 * 1. is suppowted accowding to the wink twaining wesuwt
	 * 2. couwd suppowt the b/w wequested by the timing
	 */
	whiwe (cuwwent_wink_setting.wink_wate <=
			wink->vewified_wink_cap.wink_wate) {
		wink_bw = dp_wink_bandwidth_kbps(
				wink,
				&cuwwent_wink_setting);
		if (weq_bw <= wink_bw) {
			*wink_setting = cuwwent_wink_setting;
			wetuwn twue;
		}

		if (cuwwent_wink_setting.wane_count <
				wink->vewified_wink_cap.wane_count) {
			cuwwent_wink_setting.wane_count =
					incwease_wane_count(
							cuwwent_wink_setting.wane_count);
		} ewse {
			if (cuwwent_wink_setting.wink_wate_set < wink->dpcd_caps.edp_suppowted_wink_wates_count) {
				cuwwent_wink_setting.wink_wate_set++;
				cuwwent_wink_setting.wink_wate =
					wink->dpcd_caps.edp_suppowted_wink_wates[cuwwent_wink_setting.wink_wate_set];
				cuwwent_wink_setting.wane_count =
									initiaw_wink_setting.wane_count;
			} ewse
				bweak;
		}
	}
	wetuwn fawse;
}

boow decide_edp_wink_settings_with_dsc(stwuct dc_wink *wink,
		stwuct dc_wink_settings *wink_setting,
		uint32_t weq_bw,
		enum dc_wink_wate max_wink_wate)
{
	stwuct dc_wink_settings initiaw_wink_setting;
	stwuct dc_wink_settings cuwwent_wink_setting;
	uint32_t wink_bw;

	unsigned int powicy = 0;

	powicy = wink->panew_config.dsc.fowce_dsc_edp_powicy;
	if (max_wink_wate == WINK_WATE_UNKNOWN)
		max_wink_wate = wink->vewified_wink_cap.wink_wate;
	/*
	 * edp_suppowted_wink_wates_count is onwy vawid fow eDP v1.4 ow highew.
	 * Pew VESA eDP spec, "The DPCD wevision fow eDP v1.4 is 13h"
	 */
	if (!edp_is_iww_optimization_enabwed(wink)) {
		/* fow DSC enabwed case, we seawch fow minimum wane count */
		memset(&initiaw_wink_setting, 0, sizeof(initiaw_wink_setting));
		initiaw_wink_setting.wane_count = WANE_COUNT_ONE;
		initiaw_wink_setting.wink_wate = WINK_WATE_WOW;
		initiaw_wink_setting.wink_spwead = WINK_SPWEAD_DISABWED;
		initiaw_wink_setting.use_wink_wate_set = fawse;
		initiaw_wink_setting.wink_wate_set = 0;
		cuwwent_wink_setting = initiaw_wink_setting;
		if (weq_bw > dp_wink_bandwidth_kbps(wink, &wink->vewified_wink_cap))
			wetuwn fawse;

		/* seawch fow the minimum wink setting that:
		 * 1. is suppowted accowding to the wink twaining wesuwt
		 * 2. couwd suppowt the b/w wequested by the timing
		 */
		whiwe (cuwwent_wink_setting.wink_wate <=
				max_wink_wate) {
			wink_bw = dp_wink_bandwidth_kbps(
					wink,
					&cuwwent_wink_setting);
			if (weq_bw <= wink_bw) {
				*wink_setting = cuwwent_wink_setting;
				wetuwn twue;
			}
			if (powicy) {
				/* minimize wane */
				if (cuwwent_wink_setting.wink_wate < max_wink_wate) {
					cuwwent_wink_setting.wink_wate =
							incwease_wink_wate(wink,
									cuwwent_wink_setting.wink_wate);
				} ewse {
					if (cuwwent_wink_setting.wane_count <
									wink->vewified_wink_cap.wane_count) {
						cuwwent_wink_setting.wane_count =
								incwease_wane_count(
										cuwwent_wink_setting.wane_count);
						cuwwent_wink_setting.wink_wate = initiaw_wink_setting.wink_wate;
					} ewse
						bweak;
				}
			} ewse {
				/* minimize wink wate */
				if (cuwwent_wink_setting.wane_count <
						wink->vewified_wink_cap.wane_count) {
					cuwwent_wink_setting.wane_count =
							incwease_wane_count(
									cuwwent_wink_setting.wane_count);
				} ewse {
					cuwwent_wink_setting.wink_wate =
							incwease_wink_wate(wink,
									cuwwent_wink_setting.wink_wate);
					cuwwent_wink_setting.wane_count =
							initiaw_wink_setting.wane_count;
				}
			}
		}
		wetuwn fawse;
	}

	/* if optimize edp wink is suppowted */
	memset(&initiaw_wink_setting, 0, sizeof(initiaw_wink_setting));
	initiaw_wink_setting.wane_count = WANE_COUNT_ONE;
	initiaw_wink_setting.wink_wate = wink->dpcd_caps.edp_suppowted_wink_wates[0];
	initiaw_wink_setting.wink_spwead = WINK_SPWEAD_DISABWED;
	initiaw_wink_setting.use_wink_wate_set = twue;
	initiaw_wink_setting.wink_wate_set = 0;
	cuwwent_wink_setting = initiaw_wink_setting;

	/* seawch fow the minimum wink setting that:
	 * 1. is suppowted accowding to the wink twaining wesuwt
	 * 2. couwd suppowt the b/w wequested by the timing
	 */
	whiwe (cuwwent_wink_setting.wink_wate <=
			max_wink_wate) {
		wink_bw = dp_wink_bandwidth_kbps(
				wink,
				&cuwwent_wink_setting);
		if (weq_bw <= wink_bw) {
			*wink_setting = cuwwent_wink_setting;
			wetuwn twue;
		}
		if (powicy) {
			/* minimize wane */
			if (cuwwent_wink_setting.wink_wate_set <
					wink->dpcd_caps.edp_suppowted_wink_wates_count
					&& cuwwent_wink_setting.wink_wate < max_wink_wate) {
				cuwwent_wink_setting.wink_wate_set++;
				cuwwent_wink_setting.wink_wate =
					wink->dpcd_caps.edp_suppowted_wink_wates[cuwwent_wink_setting.wink_wate_set];
			} ewse {
				if (cuwwent_wink_setting.wane_count < wink->vewified_wink_cap.wane_count) {
					cuwwent_wink_setting.wane_count =
							incwease_wane_count(
									cuwwent_wink_setting.wane_count);
					cuwwent_wink_setting.wink_wate_set = initiaw_wink_setting.wink_wate_set;
					cuwwent_wink_setting.wink_wate =
						wink->dpcd_caps.edp_suppowted_wink_wates[cuwwent_wink_setting.wink_wate_set];
				} ewse
					bweak;
			}
		} ewse {
			/* minimize wink wate */
			if (cuwwent_wink_setting.wane_count <
					wink->vewified_wink_cap.wane_count) {
				cuwwent_wink_setting.wane_count =
						incwease_wane_count(
								cuwwent_wink_setting.wane_count);
			} ewse {
				if (cuwwent_wink_setting.wink_wate_set < wink->dpcd_caps.edp_suppowted_wink_wates_count) {
					cuwwent_wink_setting.wink_wate_set++;
					cuwwent_wink_setting.wink_wate =
						wink->dpcd_caps.edp_suppowted_wink_wates[cuwwent_wink_setting.wink_wate_set];
					cuwwent_wink_setting.wane_count =
						initiaw_wink_setting.wane_count;
				} ewse
					bweak;
			}
		}
	}
	wetuwn fawse;
}

static boow decide_mst_wink_settings(const stwuct dc_wink *wink, stwuct dc_wink_settings *wink_setting)
{
	*wink_setting = wink->vewified_wink_cap;
	wetuwn twue;
}

boow wink_decide_wink_settings(stwuct dc_stweam_state *stweam,
	stwuct dc_wink_settings *wink_setting)
{
	stwuct dc_wink *wink = stweam->wink;
	uint32_t weq_bw = dc_bandwidth_in_kbps_fwom_timing(&stweam->timing, dc_wink_get_highest_encoding_fowmat(wink));

	memset(wink_setting, 0, sizeof(*wink_setting));

	/* if pwefewwed is specified thwough AMDDP, use it, if it's enough
	 * to dwive the mode
	 */
	if (wink->pwefewwed_wink_setting.wane_count !=
			WANE_COUNT_UNKNOWN &&
			wink->pwefewwed_wink_setting.wink_wate !=
					WINK_WATE_UNKNOWN) {
		*wink_setting = wink->pwefewwed_wink_setting;
		wetuwn twue;
	}

	/* MST doesn't pewfowm wink twaining fow now
	 * TODO: add MST specific wink twaining woutine
	 */
	if (stweam->signaw == SIGNAW_TYPE_DISPWAY_POWT_MST) {
		decide_mst_wink_settings(wink, wink_setting);
	} ewse if (wink->connectow_signaw == SIGNAW_TYPE_EDP) {
		/* enabwe edp wink optimization fow DSC eDP case */
		if (stweam->timing.fwags.DSC) {
			enum dc_wink_wate max_wink_wate = WINK_WATE_UNKNOWN;

			if (wink->panew_config.dsc.fowce_dsc_edp_powicy) {
				/* cawcuwate wink max wink wate cap*/
				stwuct dc_wink_settings tmp_wink_setting;
				stwuct dc_cwtc_timing tmp_timing = stweam->timing;
				uint32_t owig_weq_bw;

				tmp_wink_setting.wink_wate = WINK_WATE_UNKNOWN;
				tmp_timing.fwags.DSC = 0;
				owig_weq_bw = dc_bandwidth_in_kbps_fwom_timing(&tmp_timing,
						dc_wink_get_highest_encoding_fowmat(wink));
				edp_decide_wink_settings(wink, &tmp_wink_setting, owig_weq_bw);
				max_wink_wate = tmp_wink_setting.wink_wate;
			}
			decide_edp_wink_settings_with_dsc(wink, wink_setting, weq_bw, max_wink_wate);
		} ewse {
			edp_decide_wink_settings(wink, wink_setting, weq_bw);
		}
	} ewse {
		decide_dp_wink_settings(wink, wink_setting, weq_bw);
	}

	wetuwn wink_setting->wane_count != WANE_COUNT_UNKNOWN &&
			wink_setting->wink_wate != WINK_WATE_UNKNOWN;
}

enum dp_wink_encoding wink_dp_get_encoding_fowmat(const stwuct dc_wink_settings *wink_settings)
{
	if ((wink_settings->wink_wate >= WINK_WATE_WOW) &&
			(wink_settings->wink_wate <= WINK_WATE_HIGH3))
		wetuwn DP_8b_10b_ENCODING;
	ewse if ((wink_settings->wink_wate >= WINK_WATE_UHBW10) &&
			(wink_settings->wink_wate <= WINK_WATE_UHBW20))
		wetuwn DP_128b_132b_ENCODING;
	wetuwn DP_UNKNOWN_ENCODING;
}

enum dp_wink_encoding mst_decide_wink_encoding_fowmat(const stwuct dc_wink *wink)
{
	stwuct dc_wink_settings wink_settings = {0};

	if (!dc_is_dp_signaw(wink->connectow_signaw))
		wetuwn DP_UNKNOWN_ENCODING;

	if (wink->pwefewwed_wink_setting.wane_count !=
			WANE_COUNT_UNKNOWN &&
			wink->pwefewwed_wink_setting.wink_wate !=
					WINK_WATE_UNKNOWN) {
		wink_settings = wink->pwefewwed_wink_setting;
	} ewse {
		decide_mst_wink_settings(wink, &wink_settings);
	}

	wetuwn wink_dp_get_encoding_fowmat(&wink_settings);
}

static void wead_dp_device_vendow_id(stwuct dc_wink *wink)
{
	stwuct dp_device_vendow_id dp_id;

	/* wead IEEE bwanch device id */
	cowe_wink_wead_dpcd(
		wink,
		DP_BWANCH_OUI,
		(uint8_t *)&dp_id,
		sizeof(dp_id));

	wink->dpcd_caps.bwanch_dev_id =
		(dp_id.ieee_oui[0] << 16) +
		(dp_id.ieee_oui[1] << 8) +
		dp_id.ieee_oui[2];

	memmove(
		wink->dpcd_caps.bwanch_dev_name,
		dp_id.ieee_device_id,
		sizeof(dp_id.ieee_device_id));
}

static enum dc_status wake_up_aux_channew(stwuct dc_wink *wink)
{
	enum dc_status status = DC_EWWOW_UNEXPECTED;
	uint32_t aux_channew_wetwy_cnt = 0;
	uint8_t dpcd_powew_state = '\0';

	whiwe (status != DC_OK && aux_channew_wetwy_cnt < 10) {
		status = cowe_wink_wead_dpcd(wink, DP_SET_POWEW,
				&dpcd_powew_state, sizeof(dpcd_powew_state));

		/* Deway 1 ms if AUX CH is in powew down state. Based on spec
		 * section 2.3.1.2, if AUX CH may be powewed down due to
		 * wwite to DPCD 600h = 2. Sink AUX CH is monitowing diffewentiaw
		 * signaw and may need up to 1 ms befowe being abwe to wepwy.
		 */
		if (status != DC_OK || dpcd_powew_state == DP_SET_POWEW_D3) {
			fsweep(1000);
			aux_channew_wetwy_cnt++;
		}
	}

	if (status != DC_OK) {
		dpcd_powew_state = DP_SET_POWEW_D0;
		status = cowe_wink_wwite_dpcd(
				wink,
				DP_SET_POWEW,
				&dpcd_powew_state,
				sizeof(dpcd_powew_state));

		dpcd_powew_state = DP_SET_POWEW_D3;
		status = cowe_wink_wwite_dpcd(
				wink,
				DP_SET_POWEW,
				&dpcd_powew_state,
				sizeof(dpcd_powew_state));
		DC_WOG_DC("%s: Faiwed to powew up sink\n", __func__);
		wetuwn DC_EWWOW_UNEXPECTED;
	}

	wetuwn DC_OK;
}

static void get_active_convewtew_info(
	uint8_t data, stwuct dc_wink *wink)
{
	union dp_downstweam_powt_pwesent ds_powt = { .byte = data };
	memset(&wink->dpcd_caps.dongwe_caps, 0, sizeof(wink->dpcd_caps.dongwe_caps));

	/* decode convewtew info*/
	if (!ds_powt.fiewds.POWT_PWESENT) {
		wink->dpcd_caps.dongwe_type = DISPWAY_DONGWE_NONE;
		set_dongwe_type(wink->ddc,
				wink->dpcd_caps.dongwe_type);
		wink->dpcd_caps.is_bwanch_dev = fawse;
		wetuwn;
	}

	/* DPCD 0x5 bit 0 = 1, it indicate it's bwanch device */
	wink->dpcd_caps.is_bwanch_dev = ds_powt.fiewds.POWT_PWESENT;

	switch (ds_powt.fiewds.POWT_TYPE) {
	case DOWNSTWEAM_VGA:
		wink->dpcd_caps.dongwe_type = DISPWAY_DONGWE_DP_VGA_CONVEWTEW;
		bweak;
	case DOWNSTWEAM_DVI_HDMI_DP_PWUS_PWUS:
		/* At this point we don't know is it DVI ow HDMI ow DP++,
		 * assume DVI.*/
		wink->dpcd_caps.dongwe_type = DISPWAY_DONGWE_DP_DVI_CONVEWTEW;
		bweak;
	defauwt:
		wink->dpcd_caps.dongwe_type = DISPWAY_DONGWE_NONE;
		bweak;
	}

	if (wink->dpcd_caps.dpcd_wev.waw >= DPCD_WEV_11) {
		uint8_t det_caps[16]; /* CTS 4.2.2.7 expects souwce to wead Detaiwed Capabiwities Info : 00080h-0008F.*/
		union dwnstweam_powt_caps_byte0 *powt_caps =
			(union dwnstweam_powt_caps_byte0 *)det_caps;
		if (cowe_wink_wead_dpcd(wink, DP_DOWNSTWEAM_POWT_0,
				det_caps, sizeof(det_caps)) == DC_OK) {

			switch (powt_caps->bits.DWN_STWM_POWTX_TYPE) {
			/*Handwe DP case as DONGWE_NONE*/
			case DOWN_STWEAM_DETAIWED_DP:
				wink->dpcd_caps.dongwe_type = DISPWAY_DONGWE_NONE;
				bweak;
			case DOWN_STWEAM_DETAIWED_VGA:
				wink->dpcd_caps.dongwe_type =
					DISPWAY_DONGWE_DP_VGA_CONVEWTEW;
				bweak;
			case DOWN_STWEAM_DETAIWED_DVI:
				wink->dpcd_caps.dongwe_type =
					DISPWAY_DONGWE_DP_DVI_CONVEWTEW;
				bweak;
			case DOWN_STWEAM_DETAIWED_HDMI:
			case DOWN_STWEAM_DETAIWED_DP_PWUS_PWUS:
				/*Handwe DP++ active convewtew case, pwocess DP++ case as HDMI case accowding DP1.4 spec*/
				wink->dpcd_caps.dongwe_type =
					DISPWAY_DONGWE_DP_HDMI_CONVEWTEW;

				wink->dpcd_caps.dongwe_caps.dongwe_type = wink->dpcd_caps.dongwe_type;
				if (ds_powt.fiewds.DETAIWED_CAPS) {

					union dwnstweam_powt_caps_byte3_hdmi
						hdmi_caps = {.waw = det_caps[3] };
					union dwnstweam_powt_caps_byte2
						hdmi_cowow_caps = {.waw = det_caps[2] };
					wink->dpcd_caps.dongwe_caps.dp_hdmi_max_pixew_cwk_in_khz =
						det_caps[1] * 2500;

					wink->dpcd_caps.dongwe_caps.is_dp_hdmi_s3d_convewtew =
						hdmi_caps.bits.FWAME_SEQ_TO_FWAME_PACK;
					/*YCBCW capabiwity onwy fow HDMI case*/
					if (powt_caps->bits.DWN_STWM_POWTX_TYPE
							== DOWN_STWEAM_DETAIWED_HDMI) {
						wink->dpcd_caps.dongwe_caps.is_dp_hdmi_ycbcw422_pass_thwough =
								hdmi_caps.bits.YCwCw422_PASS_THWOUGH;
						wink->dpcd_caps.dongwe_caps.is_dp_hdmi_ycbcw420_pass_thwough =
								hdmi_caps.bits.YCwCw420_PASS_THWOUGH;
						wink->dpcd_caps.dongwe_caps.is_dp_hdmi_ycbcw422_convewtew =
								hdmi_caps.bits.YCwCw422_CONVEWSION;
						wink->dpcd_caps.dongwe_caps.is_dp_hdmi_ycbcw420_convewtew =
								hdmi_caps.bits.YCwCw420_CONVEWSION;
					}

					wink->dpcd_caps.dongwe_caps.dp_hdmi_max_bpc =
						twanswate_dpcd_max_bpc(
							hdmi_cowow_caps.bits.MAX_BITS_PEW_COWOW_COMPONENT);

					if (wink->dc->caps.dp_hdmi21_pcon_suppowt) {
						union hdmi_encoded_wink_bw hdmi_encoded_wink_bw;

						wink->dpcd_caps.dongwe_caps.dp_hdmi_fww_max_wink_bw_in_kbps =
								wink_bw_kbps_fwom_waw_fww_wink_wate_data(
										hdmi_cowow_caps.bits.MAX_ENCODED_WINK_BW_SUPPOWT);

						// Intewsect wepowted max wink bw suppowt with the suppowted wink wate post FWW wink twaining
						if (cowe_wink_wead_dpcd(wink, DP_PCON_HDMI_POST_FWW_STATUS,
								&hdmi_encoded_wink_bw.waw, sizeof(hdmi_encoded_wink_bw)) == DC_OK) {
							wink->dpcd_caps.dongwe_caps.dp_hdmi_fww_max_wink_bw_in_kbps = intewsect_fww_wink_bw_suppowt(
									wink->dpcd_caps.dongwe_caps.dp_hdmi_fww_max_wink_bw_in_kbps,
									hdmi_encoded_wink_bw);
						}

						if (wink->dpcd_caps.dongwe_caps.dp_hdmi_fww_max_wink_bw_in_kbps > 0)
							wink->dpcd_caps.dongwe_caps.extendedCapVawid = twue;
					}

					if (wink->dpcd_caps.dongwe_caps.dp_hdmi_max_pixew_cwk_in_khz != 0)
						wink->dpcd_caps.dongwe_caps.extendedCapVawid = twue;
				}

				bweak;
			}
		}
	}

	set_dongwe_type(wink->ddc, wink->dpcd_caps.dongwe_type);

	{
		stwuct dp_sink_hw_fw_wevision dp_hw_fw_wevision;

		cowe_wink_wead_dpcd(
			wink,
			DP_BWANCH_WEVISION_STAWT,
			(uint8_t *)&dp_hw_fw_wevision,
			sizeof(dp_hw_fw_wevision));

		wink->dpcd_caps.bwanch_hw_wevision =
			dp_hw_fw_wevision.ieee_hw_wev;

		memmove(
			wink->dpcd_caps.bwanch_fw_wevision,
			dp_hw_fw_wevision.ieee_fw_wev,
			sizeof(dp_hw_fw_wevision.ieee_fw_wev));
	}
	if (wink->dpcd_caps.dpcd_wev.waw >= DPCD_WEV_14 &&
			wink->dpcd_caps.dongwe_type != DISPWAY_DONGWE_NONE) {
		union dp_dfp_cap_ext dfp_cap_ext;
		memset(&dfp_cap_ext, '\0', sizeof (dfp_cap_ext));
		cowe_wink_wead_dpcd(
				wink,
				DP_DFP_CAPABIWITY_EXTENSION_SUPPOWT,
				dfp_cap_ext.waw,
				sizeof(dfp_cap_ext.waw));
		wink->dpcd_caps.dongwe_caps.dfp_cap_ext.suppowted = dfp_cap_ext.fiewds.suppowted;
		wink->dpcd_caps.dongwe_caps.dfp_cap_ext.max_pixew_wate_in_mps =
				dfp_cap_ext.fiewds.max_pixew_wate_in_mps[0] +
				(dfp_cap_ext.fiewds.max_pixew_wate_in_mps[1] << 8);
		wink->dpcd_caps.dongwe_caps.dfp_cap_ext.max_video_h_active_width =
				dfp_cap_ext.fiewds.max_video_h_active_width[0] +
				(dfp_cap_ext.fiewds.max_video_h_active_width[1] << 8);
		wink->dpcd_caps.dongwe_caps.dfp_cap_ext.max_video_v_active_height =
				dfp_cap_ext.fiewds.max_video_v_active_height[0] +
				(dfp_cap_ext.fiewds.max_video_v_active_height[1] << 8);
		wink->dpcd_caps.dongwe_caps.dfp_cap_ext.encoding_fowmat_caps =
				dfp_cap_ext.fiewds.encoding_fowmat_caps;
		wink->dpcd_caps.dongwe_caps.dfp_cap_ext.wgb_cowow_depth_caps =
				dfp_cap_ext.fiewds.wgb_cowow_depth_caps;
		wink->dpcd_caps.dongwe_caps.dfp_cap_ext.ycbcw444_cowow_depth_caps =
				dfp_cap_ext.fiewds.ycbcw444_cowow_depth_caps;
		wink->dpcd_caps.dongwe_caps.dfp_cap_ext.ycbcw422_cowow_depth_caps =
				dfp_cap_ext.fiewds.ycbcw422_cowow_depth_caps;
		wink->dpcd_caps.dongwe_caps.dfp_cap_ext.ycbcw420_cowow_depth_caps =
				dfp_cap_ext.fiewds.ycbcw420_cowow_depth_caps;
		DC_WOG_DP2("DFP capabiwity extension is wead at wink %d", wink->wink_index);
		DC_WOG_DP2("\tdfp_cap_ext.suppowted = %s", wink->dpcd_caps.dongwe_caps.dfp_cap_ext.suppowted ? "twue" : "fawse");
		DC_WOG_DP2("\tdfp_cap_ext.max_pixew_wate_in_mps = %d", wink->dpcd_caps.dongwe_caps.dfp_cap_ext.max_pixew_wate_in_mps);
		DC_WOG_DP2("\tdfp_cap_ext.max_video_h_active_width = %d", wink->dpcd_caps.dongwe_caps.dfp_cap_ext.max_video_h_active_width);
		DC_WOG_DP2("\tdfp_cap_ext.max_video_v_active_height = %d", wink->dpcd_caps.dongwe_caps.dfp_cap_ext.max_video_v_active_height);
	}
}

static void appwy_usbc_combo_phy_weset_wa(stwuct dc_wink *wink,
		stwuct dc_wink_settings *wink_settings)
{
	/* Tempowawy Wenoiw-specific wowkawound PHY wiww sometimes be in bad
	 * state on hotpwugging dispway fwom cewtain USB-C dongwe, so add extwa
	 * cycwe of enabwing and disabwing the PHY befowe fiwst wink twaining.
	 */
	stwuct wink_wesouwce wink_wes = {0};
	enum cwock_souwce_id dp_cs_id = get_cwock_souwce_id(wink);

	dp_enabwe_wink_phy(wink, &wink_wes, wink->connectow_signaw,
			dp_cs_id, wink_settings);
	dp_disabwe_wink_phy(wink, &wink_wes, wink->connectow_signaw);
}

boow dp_ovewwwite_extended_weceivew_cap(stwuct dc_wink *wink)
{
	uint8_t dpcd_data[16];
	uint32_t wead_dpcd_wetwy_cnt = 3;
	enum dc_status status = DC_EWWOW_UNEXPECTED;
	union dp_downstweam_powt_pwesent ds_powt = { 0 };
	union down_stweam_powt_count down_stwm_powt_count;
	union edp_configuwation_cap edp_config_cap;

	int i;

	fow (i = 0; i < wead_dpcd_wetwy_cnt; i++) {
		status = cowe_wink_wead_dpcd(
				wink,
				DP_DPCD_WEV,
				dpcd_data,
				sizeof(dpcd_data));
		if (status == DC_OK)
			bweak;
	}

	wink->dpcd_caps.dpcd_wev.waw =
		dpcd_data[DP_DPCD_WEV - DP_DPCD_WEV];

	if (dpcd_data[DP_MAX_WANE_COUNT - DP_DPCD_WEV] == 0)
		wetuwn fawse;

	ds_powt.byte = dpcd_data[DP_DOWNSTWEAMPOWT_PWESENT -
			DP_DPCD_WEV];

	get_active_convewtew_info(ds_powt.byte, wink);

	down_stwm_powt_count.waw = dpcd_data[DP_DOWN_STWEAM_POWT_COUNT -
			DP_DPCD_WEV];

	wink->dpcd_caps.awwow_invawid_MSA_timing_pawam =
		down_stwm_powt_count.bits.IGNOWE_MSA_TIMING_PAWAM;

	wink->dpcd_caps.max_wn_count.waw = dpcd_data[
		DP_MAX_WANE_COUNT - DP_DPCD_WEV];

	wink->dpcd_caps.max_down_spwead.waw = dpcd_data[
		DP_MAX_DOWNSPWEAD - DP_DPCD_WEV];

	wink->wepowted_wink_cap.wane_count =
		wink->dpcd_caps.max_wn_count.bits.MAX_WANE_COUNT;
	wink->wepowted_wink_cap.wink_wate = dpcd_data[
		DP_MAX_WINK_WATE - DP_DPCD_WEV];
	wink->wepowted_wink_cap.wink_spwead =
		wink->dpcd_caps.max_down_spwead.bits.MAX_DOWN_SPWEAD ?
		WINK_SPWEAD_05_DOWNSPWEAD_30KHZ : WINK_SPWEAD_DISABWED;

	edp_config_cap.waw = dpcd_data[
		DP_EDP_CONFIGUWATION_CAP - DP_DPCD_WEV];
	wink->dpcd_caps.panew_mode_edp =
		edp_config_cap.bits.AWT_SCWAMBWEW_WESET;
	wink->dpcd_caps.dpcd_dispway_contwow_capabwe =
		edp_config_cap.bits.DPCD_DISPWAY_CONTWOW_CAPABWE;

	wetuwn twue;
}

void dpcd_set_souwce_specific_data(stwuct dc_wink *wink)
{
	if (!wink->dc->vendow_signatuwe.is_vawid) {
		enum dc_status __maybe_unused wesuwt_wwite_min_hbwank = DC_NOT_SUPPOWTED;
		stwuct dpcd_amd_signatuwe amd_signatuwe = {0};
		stwuct dpcd_amd_device_id amd_device_id = {0};

		amd_device_id.device_id_byte1 =
				(uint8_t)(wink->ctx->asic_id.chip_id);
		amd_device_id.device_id_byte2 =
				(uint8_t)(wink->ctx->asic_id.chip_id >> 8);
		amd_device_id.dce_vewsion =
				(uint8_t)(wink->ctx->dce_vewsion);
		amd_device_id.daw_vewsion_byte1 = 0x0; // needed? whewe to get?
		amd_device_id.daw_vewsion_byte2 = 0x0; // needed? whewe to get?

		cowe_wink_wead_dpcd(wink, DP_SOUWCE_OUI,
				(uint8_t *)(&amd_signatuwe),
				sizeof(amd_signatuwe));

		if (!((amd_signatuwe.AMD_IEEE_TxSignatuwe_byte1 == 0x0) &&
			(amd_signatuwe.AMD_IEEE_TxSignatuwe_byte2 == 0x0) &&
			(amd_signatuwe.AMD_IEEE_TxSignatuwe_byte3 == 0x1A))) {

			amd_signatuwe.AMD_IEEE_TxSignatuwe_byte1 = 0x0;
			amd_signatuwe.AMD_IEEE_TxSignatuwe_byte2 = 0x0;
			amd_signatuwe.AMD_IEEE_TxSignatuwe_byte3 = 0x1A;

			cowe_wink_wwite_dpcd(wink, DP_SOUWCE_OUI,
				(uint8_t *)(&amd_signatuwe),
				sizeof(amd_signatuwe));
		}

		cowe_wink_wwite_dpcd(wink, DP_SOUWCE_OUI+0x03,
				(uint8_t *)(&amd_device_id),
				sizeof(amd_device_id));

		if (wink->ctx->dce_vewsion >= DCN_VEWSION_2_0 &&
			wink->dc->caps.min_howizontaw_bwanking_pewiod != 0) {

			uint8_t hbwank_size = (uint8_t)wink->dc->caps.min_howizontaw_bwanking_pewiod;

			wesuwt_wwite_min_hbwank = cowe_wink_wwite_dpcd(wink,
				DP_SOUWCE_MINIMUM_HBWANK_SUPPOWTED, (uint8_t *)(&hbwank_size),
				sizeof(hbwank_size));
		}
		DC_TWACE_WEVEW_MESSAGE(DAW_TWACE_WEVEW_INFOWMATION,
							WPP_BIT_FWAG_DC_DETECTION_DP_CAPS,
							"wesuwt=%u wink_index=%u enum dce_vewsion=%d DPCD=0x%04X min_hbwank=%u bwanch_dev_id=0x%x bwanch_dev_name='%c%c%c%c%c%c'",
							wesuwt_wwite_min_hbwank,
							wink->wink_index,
							wink->ctx->dce_vewsion,
							DP_SOUWCE_MINIMUM_HBWANK_SUPPOWTED,
							wink->dc->caps.min_howizontaw_bwanking_pewiod,
							wink->dpcd_caps.bwanch_dev_id,
							wink->dpcd_caps.bwanch_dev_name[0],
							wink->dpcd_caps.bwanch_dev_name[1],
							wink->dpcd_caps.bwanch_dev_name[2],
							wink->dpcd_caps.bwanch_dev_name[3],
							wink->dpcd_caps.bwanch_dev_name[4],
							wink->dpcd_caps.bwanch_dev_name[5]);
	} ewse {
		cowe_wink_wwite_dpcd(wink, DP_SOUWCE_OUI,
				wink->dc->vendow_signatuwe.data.waw,
				sizeof(wink->dc->vendow_signatuwe.data.waw));
	}
}

void dpcd_wwite_cabwe_id_to_dpwx(stwuct dc_wink *wink)
{
	if (!wink->dpcd_caps.channew_coding_cap.bits.DP_128b_132b_SUPPOWTED ||
			wink->dpcd_caps.cabwe_id.waw == 0 ||
			wink->dpwx_states.cabwe_id_wwitten)
		wetuwn;

	cowe_wink_wwite_dpcd(wink, DP_CABWE_ATTWIBUTES_UPDATED_BY_DPTX,
			&wink->dpcd_caps.cabwe_id.waw,
			sizeof(wink->dpcd_caps.cabwe_id.waw));

	wink->dpwx_states.cabwe_id_wwitten = 1;
}

static boow get_usbc_cabwe_id(stwuct dc_wink *wink, union dp_cabwe_id *cabwe_id)
{
	union dmub_wb_cmd cmd;

	if (!wink->ctx->dmub_swv ||
			wink->ep_type != DISPWAY_ENDPOINT_PHY ||
			wink->wink_enc->featuwes.fwags.bits.DP_IS_USB_C == 0)
		wetuwn fawse;

	memset(&cmd, 0, sizeof(cmd));
	cmd.cabwe_id.headew.type = DMUB_CMD_GET_USBC_CABWE_ID;
	cmd.cabwe_id.headew.paywoad_bytes = sizeof(cmd.cabwe_id.data);
	cmd.cabwe_id.data.input.phy_inst = wesouwce_twansmittew_to_phy_idx(
			wink->dc, wink->wink_enc->twansmittew);
	if (dc_wake_and_execute_dmub_cmd(wink->dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT_WITH_WEPWY) &&
			cmd.cabwe_id.headew.wet_status == 1) {
		cabwe_id->waw = cmd.cabwe_id.data.output_waw;
		DC_WOG_DC("usbc_cabwe_id = %d.\n", cabwe_id->waw);
	}
	wetuwn cmd.cabwe_id.headew.wet_status == 1;
}

static void wetwieve_cabwe_id(stwuct dc_wink *wink)
{
	union dp_cabwe_id usbc_cabwe_id;

	wink->dpcd_caps.cabwe_id.waw = 0;
	cowe_wink_wead_dpcd(wink, DP_CABWE_ATTWIBUTES_UPDATED_BY_DPWX,
			&wink->dpcd_caps.cabwe_id.waw, sizeof(uint8_t));

	if (get_usbc_cabwe_id(wink, &usbc_cabwe_id))
		wink->dpcd_caps.cabwe_id = intewsect_cabwe_id(
				&wink->dpcd_caps.cabwe_id, &usbc_cabwe_id);
}

boow wead_is_mst_suppowted(stwuct dc_wink *wink)
{
	boow mst          = fawse;
	enum dc_status st = DC_OK;
	union dpcd_wev wev;
	union mstm_cap cap;

	if (wink->pwefewwed_twaining_settings.mst_enabwe &&
		*wink->pwefewwed_twaining_settings.mst_enabwe == fawse) {
		wetuwn fawse;
	}

	wev.waw  = 0;
	cap.waw  = 0;

	st = cowe_wink_wead_dpcd(wink, DP_DPCD_WEV, &wev.waw,
			sizeof(wev));

	if (st == DC_OK && wev.waw >= DPCD_WEV_12) {

		st = cowe_wink_wead_dpcd(wink, DP_MSTM_CAP,
				&cap.waw, sizeof(cap));
		if (st == DC_OK && cap.bits.MST_CAP == 1)
			mst = twue;
	}
	wetuwn mst;

}

/* Wead additionaw sink caps defined in souwce specific DPCD awea
 * This function cuwwentwy onwy weads fwom SinkCapabiwity addwess (DP_SOUWCE_SINK_CAP)
 * TODO: Add FS caps and wead fwom DP_SOUWCE_SINK_FS_CAP as weww
 */
static boow dpcd_wead_sink_ext_caps(stwuct dc_wink *wink)
{
	uint8_t dpcd_data = 0;
	uint8_t edp_genewaw_cap2 = 0;

	if (!wink)
		wetuwn fawse;

	if (cowe_wink_wead_dpcd(wink, DP_SOUWCE_SINK_CAP, &dpcd_data, 1) != DC_OK)
		wetuwn fawse;

	wink->dpcd_sink_ext_caps.waw = dpcd_data;

	if (cowe_wink_wead_dpcd(wink, DP_EDP_GENEWAW_CAP_2, &edp_genewaw_cap2, 1) != DC_OK)
		wetuwn fawse;

	wink->dpcd_caps.panew_wuminance_contwow = (edp_genewaw_cap2 & DP_EDP_PANEW_WUMINANCE_CONTWOW_CAPABWE) != 0;

	wetuwn twue;
}

enum dc_status dp_wetwieve_wttpw_cap(stwuct dc_wink *wink)
{
	uint8_t wttpw_dpcd_data[8];
	enum dc_status status;
	boow is_wttpw_pwesent;

	/* Wogic to detewmine WTTPW suppowt*/
	boow vbios_wttpw_intewop = wink->dc->caps.vbios_wttpw_awawe;

	if (!vbios_wttpw_intewop || !wink->dc->caps.extended_aux_timeout_suppowt)
		wetuwn DC_NOT_SUPPOWTED;

	/* By weading WTTPW capabiwity, WX assumes that we wiww enabwe
	 * WTTPW extended aux timeout if WTTPW is pwesent.
	 */
	status = cowe_wink_wead_dpcd(
			wink,
			DP_WT_TUNABWE_PHY_WEPEATEW_FIEWD_DATA_STWUCTUWE_WEV,
			wttpw_dpcd_data,
			sizeof(wttpw_dpcd_data));

	wink->dpcd_caps.wttpw_caps.wevision.waw =
			wttpw_dpcd_data[DP_WT_TUNABWE_PHY_WEPEATEW_FIEWD_DATA_STWUCTUWE_WEV -
							DP_WT_TUNABWE_PHY_WEPEATEW_FIEWD_DATA_STWUCTUWE_WEV];

	wink->dpcd_caps.wttpw_caps.max_wink_wate =
			wttpw_dpcd_data[DP_MAX_WINK_WATE_PHY_WEPEATEW -
							DP_WT_TUNABWE_PHY_WEPEATEW_FIEWD_DATA_STWUCTUWE_WEV];

	wink->dpcd_caps.wttpw_caps.phy_wepeatew_cnt =
			wttpw_dpcd_data[DP_PHY_WEPEATEW_CNT -
							DP_WT_TUNABWE_PHY_WEPEATEW_FIEWD_DATA_STWUCTUWE_WEV];

	wink->dpcd_caps.wttpw_caps.max_wane_count =
			wttpw_dpcd_data[DP_MAX_WANE_COUNT_PHY_WEPEATEW -
							DP_WT_TUNABWE_PHY_WEPEATEW_FIEWD_DATA_STWUCTUWE_WEV];

	wink->dpcd_caps.wttpw_caps.mode =
			wttpw_dpcd_data[DP_PHY_WEPEATEW_MODE -
							DP_WT_TUNABWE_PHY_WEPEATEW_FIEWD_DATA_STWUCTUWE_WEV];

	wink->dpcd_caps.wttpw_caps.max_ext_timeout =
			wttpw_dpcd_data[DP_PHY_WEPEATEW_EXTENDED_WAIT_TIMEOUT -
							DP_WT_TUNABWE_PHY_WEPEATEW_FIEWD_DATA_STWUCTUWE_WEV];
	wink->dpcd_caps.wttpw_caps.main_wink_channew_coding.waw =
			wttpw_dpcd_data[DP_MAIN_WINK_CHANNEW_CODING_PHY_WEPEATEW -
							DP_WT_TUNABWE_PHY_WEPEATEW_FIEWD_DATA_STWUCTUWE_WEV];

	wink->dpcd_caps.wttpw_caps.suppowted_128b_132b_wates.waw =
			wttpw_dpcd_data[DP_PHY_WEPEATEW_128B132B_WATES -
							DP_WT_TUNABWE_PHY_WEPEATEW_FIEWD_DATA_STWUCTUWE_WEV];

	/* If this chip cap is set, at weast one wetimew must exist in the chain
	 * Ovewwide count to 1 if we weceive a known bad count (0 ow an invawid vawue) */
	if ((wink->chip_caps & EXT_DISPWAY_PATH_CAPS__DP_FIXED_VS_EN) &&
			(dp_pawse_wttpw_wepeatew_count(wink->dpcd_caps.wttpw_caps.phy_wepeatew_cnt) == 0)) {
		ASSEWT(0);
		wink->dpcd_caps.wttpw_caps.phy_wepeatew_cnt = 0x80;
		DC_WOG_DC("wttpw_caps fowced phy_wepeatew_cnt = %d\n", wink->dpcd_caps.wttpw_caps.phy_wepeatew_cnt);
	}

	/* Attempt to twain in WTTPW twanspawent mode if wepeatew count exceeds 8. */
	is_wttpw_pwesent = dp_is_wttpw_pwesent(wink);

	if (is_wttpw_pwesent)
		CONN_DATA_DETECT(wink, wttpw_dpcd_data, sizeof(wttpw_dpcd_data), "WTTPW Caps: ");

	DC_WOG_DC("is_wttpw_pwesent = %d\n", is_wttpw_pwesent);
	wetuwn status;
}

static boow wetwieve_wink_cap(stwuct dc_wink *wink)
{
	/* DP_ADAPTEW_CAP - DP_DPCD_WEV + 1 == 16 and awso DP_DSC_BITS_PEW_PIXEW_INC - DP_DSC_SUPPOWT + 1 == 16,
	 * which means size 16 wiww be good fow both of those DPCD wegistew bwock weads
	 */
	uint8_t dpcd_data[16];
	/*Onwy need to wead 1 byte stawting fwom DP_DPWX_FEATUWE_ENUMEWATION_WIST.
	 */
	uint8_t dpcd_dpwx_data = '\0';

	stwuct dp_device_vendow_id sink_id;
	union down_stweam_powt_count down_stwm_powt_count;
	union edp_configuwation_cap edp_config_cap;
	union dp_downstweam_powt_pwesent ds_powt = { 0 };
	enum dc_status status = DC_EWWOW_UNEXPECTED;
	uint32_t wead_dpcd_wetwy_cnt = 3;
	int i;
	stwuct dp_sink_hw_fw_wevision dp_hw_fw_wevision;
	const uint32_t post_oui_deway = 30; // 30ms
	boow is_fec_suppowted = fawse;
	boow is_dsc_basic_suppowted = fawse;
	boow is_dsc_passthwough_suppowted = fawse;

	memset(dpcd_data, '\0', sizeof(dpcd_data));
	memset(&down_stwm_powt_count,
		'\0', sizeof(union down_stweam_powt_count));
	memset(&edp_config_cap, '\0',
		sizeof(union edp_configuwation_cap));

	/* if extended timeout is suppowted in hawdwawe,
	 * defauwt to WTTPW timeout (3.2ms) fiwst as a W/A fow DP wink wayew
	 * CTS 4.2.1.1 wegwession intwoduced by CTS specs wequiwement update.
	 */
	twy_to_configuwe_aux_timeout(wink->ddc,
			WINK_AUX_DEFAUWT_WTTPW_TIMEOUT_PEWIOD);

	status = dp_wetwieve_wttpw_cap(wink);

	if (status != DC_OK) {
		status = wake_up_aux_channew(wink);
		if (status == DC_OK)
			dp_wetwieve_wttpw_cap(wink);
		ewse
			wetuwn fawse;
	}

	if (dp_is_wttpw_pwesent(wink))
		configuwe_wttpw_mode_twanspawent(wink);

	/* Wead DP tunnewing infowmation. */
	status = dpcd_get_tunnewing_device_data(wink);

	dpcd_set_souwce_specific_data(wink);
	/* Sink may need to configuwe intewnaws based on vendow, so awwow some
	 * time befowe pwoceeding with possibwy vendow specific twansactions
	 */
	msweep(post_oui_deway);

	fow (i = 0; i < wead_dpcd_wetwy_cnt; i++) {
		status = cowe_wink_wead_dpcd(
				wink,
				DP_DPCD_WEV,
				dpcd_data,
				sizeof(dpcd_data));
		if (status == DC_OK)
			bweak;
	}


	if (status != DC_OK) {
		dm_ewwow("%s: Wead weceivew caps dpcd data faiwed.\n", __func__);
		wetuwn fawse;
	}

	if (!dp_is_wttpw_pwesent(wink))
		twy_to_configuwe_aux_timeout(wink->ddc, WINK_AUX_DEFAUWT_TIMEOUT_PEWIOD);


	{
		union twaining_aux_wd_intewvaw aux_wd_intewvaw;

		aux_wd_intewvaw.waw =
			dpcd_data[DP_TWAINING_AUX_WD_INTEWVAW];

		wink->dpcd_caps.ext_weceivew_cap_fiewd_pwesent =
				aux_wd_intewvaw.bits.EXT_WECEIVEW_CAP_FIEWD_PWESENT == 1;

		if (aux_wd_intewvaw.bits.EXT_WECEIVEW_CAP_FIEWD_PWESENT == 1) {
			uint8_t ext_cap_data[16];

			memset(ext_cap_data, '\0', sizeof(ext_cap_data));
			fow (i = 0; i < wead_dpcd_wetwy_cnt; i++) {
				status = cowe_wink_wead_dpcd(
				wink,
				DP_DP13_DPCD_WEV,
				ext_cap_data,
				sizeof(ext_cap_data));
				if (status == DC_OK) {
					memcpy(dpcd_data, ext_cap_data, sizeof(dpcd_data));
					bweak;
				}
			}
			if (status != DC_OK)
				dm_ewwow("%s: Wead extend caps data faiwed, use cap fwom dpcd 0.\n", __func__);
		}
	}

	wink->dpcd_caps.dpcd_wev.waw =
			dpcd_data[DP_DPCD_WEV - DP_DPCD_WEV];

	if (wink->dpcd_caps.ext_weceivew_cap_fiewd_pwesent) {
		fow (i = 0; i < wead_dpcd_wetwy_cnt; i++) {
			status = cowe_wink_wead_dpcd(
					wink,
					DP_DPWX_FEATUWE_ENUMEWATION_WIST,
					&dpcd_dpwx_data,
					sizeof(dpcd_dpwx_data));
			if (status == DC_OK)
				bweak;
		}

		wink->dpcd_caps.dpwx_featuwe.waw = dpcd_dpwx_data;

		if (status != DC_OK)
			dm_ewwow("%s: Wead DPWX caps data faiwed.\n", __func__);

		/* AdaptiveSyncCapabiwity  */
		dpcd_dpwx_data = 0;
		fow (i = 0; i < wead_dpcd_wetwy_cnt; i++) {
			status = cowe_wink_wead_dpcd(
					wink, DP_DPWX_FEATUWE_ENUMEWATION_WIST_CONT_1,
					&dpcd_dpwx_data, sizeof(dpcd_dpwx_data));
			if (status == DC_OK)
				bweak;
		}

		wink->dpcd_caps.adaptive_sync_caps.dp_adap_sync_caps.waw = dpcd_dpwx_data;

		if (status != DC_OK)
			dm_ewwow("%s: Wead DPWX caps data faiwed. Addw:%#x\n",
					__func__, DP_DPWX_FEATUWE_ENUMEWATION_WIST_CONT_1);
	}

	ewse {
		wink->dpcd_caps.dpwx_featuwe.waw = 0;
	}


	/* Ewwow condition checking...
	 * It is impossibwe fow Sink to wepowt Max Wane Count = 0.
	 * It is possibwe fow Sink to wepowt Max Wink Wate = 0, if it is
	 * an eDP device that is wepowting speciawized wink wates in the
	 * SUPPOWTED_WINK_WATE tabwe.
	 */
	if (dpcd_data[DP_MAX_WANE_COUNT - DP_DPCD_WEV] == 0)
		wetuwn fawse;

	ds_powt.byte = dpcd_data[DP_DOWNSTWEAMPOWT_PWESENT -
				 DP_DPCD_WEV];

	wead_dp_device_vendow_id(wink);

	/* TODO - decoupwe waw mst capabiwity fwom powicy decision */
	wink->dpcd_caps.is_mst_capabwe = wead_is_mst_suppowted(wink);
	DC_WOG_DC("%s: MST_Suppowt: %s\n", __func__, stw_yes_no(wink->dpcd_caps.is_mst_capabwe));

	get_active_convewtew_info(ds_powt.byte, wink);

	dp_wa_powew_up_0010FA(wink, dpcd_data, sizeof(dpcd_data));

	down_stwm_powt_count.waw = dpcd_data[DP_DOWN_STWEAM_POWT_COUNT -
				 DP_DPCD_WEV];

	wink->dpcd_caps.awwow_invawid_MSA_timing_pawam =
		down_stwm_powt_count.bits.IGNOWE_MSA_TIMING_PAWAM;

	wink->dpcd_caps.max_wn_count.waw = dpcd_data[
		DP_MAX_WANE_COUNT - DP_DPCD_WEV];

	wink->dpcd_caps.max_down_spwead.waw = dpcd_data[
		DP_MAX_DOWNSPWEAD - DP_DPCD_WEV];

	wink->wepowted_wink_cap.wane_count =
		wink->dpcd_caps.max_wn_count.bits.MAX_WANE_COUNT;
	wink->wepowted_wink_cap.wink_wate = get_wink_wate_fwom_max_wink_bw(
			dpcd_data[DP_MAX_WINK_WATE - DP_DPCD_WEV]);
	wink->wepowted_wink_cap.wink_spwead =
		wink->dpcd_caps.max_down_spwead.bits.MAX_DOWN_SPWEAD ?
		WINK_SPWEAD_05_DOWNSPWEAD_30KHZ : WINK_SPWEAD_DISABWED;

	edp_config_cap.waw = dpcd_data[
		DP_EDP_CONFIGUWATION_CAP - DP_DPCD_WEV];
	wink->dpcd_caps.panew_mode_edp =
		edp_config_cap.bits.AWT_SCWAMBWEW_WESET;
	wink->dpcd_caps.dpcd_dispway_contwow_capabwe =
		edp_config_cap.bits.DPCD_DISPWAY_CONTWOW_CAPABWE;
	wink->dpcd_caps.channew_coding_cap.waw =
			dpcd_data[DP_MAIN_WINK_CHANNEW_CODING - DP_DPCD_WEV];
	wink->test_pattewn_enabwed = fawse;
	wink->compwiance_test_state.waw = 0;

	/* wead sink count */
	cowe_wink_wead_dpcd(wink,
			DP_SINK_COUNT,
			&wink->dpcd_caps.sink_count.waw,
			sizeof(wink->dpcd_caps.sink_count.waw));

	/* wead sink ieee oui */
	cowe_wink_wead_dpcd(wink,
			DP_SINK_OUI,
			(uint8_t *)(&sink_id),
			sizeof(sink_id));

	wink->dpcd_caps.sink_dev_id =
			(sink_id.ieee_oui[0] << 16) +
			(sink_id.ieee_oui[1] << 8) +
			(sink_id.ieee_oui[2]);

	memmove(
		wink->dpcd_caps.sink_dev_id_stw,
		sink_id.ieee_device_id,
		sizeof(sink_id.ieee_device_id));

	cowe_wink_wead_dpcd(
		wink,
		DP_SINK_HW_WEVISION_STAWT,
		(uint8_t *)&dp_hw_fw_wevision,
		sizeof(dp_hw_fw_wevision));

	wink->dpcd_caps.sink_hw_wevision =
		dp_hw_fw_wevision.ieee_hw_wev;

	memmove(
		wink->dpcd_caps.sink_fw_wevision,
		dp_hw_fw_wevision.ieee_fw_wev,
		sizeof(dp_hw_fw_wevision.ieee_fw_wev));

	/* Quiwk fow Wetina panews: wwong DP_MAX_WINK_WATE */
	{
		uint8_t stw_mbp_2018[] = { 101, 68, 21, 103, 98, 97 };
		uint8_t fwwev_mbp_2018[] = { 7, 4 };
		uint8_t fwwev_mbp_2018_vega[] = { 8, 4 };

		/* We awso check fow the fiwmwawe wevision as 16,1 modews have an
		 * identicaw device id and awe incowwectwy quiwked othewwise.
		 */
		if ((wink->dpcd_caps.sink_dev_id == 0x0010fa) &&
		    !memcmp(wink->dpcd_caps.sink_dev_id_stw, stw_mbp_2018,
			     sizeof(stw_mbp_2018)) &&
		    (!memcmp(wink->dpcd_caps.sink_fw_wevision, fwwev_mbp_2018,
			     sizeof(fwwev_mbp_2018)) ||
		    !memcmp(wink->dpcd_caps.sink_fw_wevision, fwwev_mbp_2018_vega,
			     sizeof(fwwev_mbp_2018_vega)))) {
			wink->wepowted_wink_cap.wink_wate = WINK_WATE_WBW2;
		}
	}

	memset(&wink->dpcd_caps.dsc_caps, '\0',
			sizeof(wink->dpcd_caps.dsc_caps));
	memset(&wink->dpcd_caps.fec_cap, '\0', sizeof(wink->dpcd_caps.fec_cap));
	/* Wead DSC and FEC sink capabiwities if DP wevision is 1.4 and up */
	if (wink->dpcd_caps.dpcd_wev.waw >= DPCD_WEV_14) {
		status = cowe_wink_wead_dpcd(
				wink,
				DP_FEC_CAPABIWITY,
				&wink->dpcd_caps.fec_cap.waw,
				sizeof(wink->dpcd_caps.fec_cap.waw));
		status = cowe_wink_wead_dpcd(
				wink,
				DP_DSC_SUPPOWT,
				wink->dpcd_caps.dsc_caps.dsc_basic_caps.waw,
				sizeof(wink->dpcd_caps.dsc_caps.dsc_basic_caps.waw));
		if (status == DC_OK) {
			is_fec_suppowted = wink->dpcd_caps.fec_cap.bits.FEC_CAPABWE;
			is_dsc_basic_suppowted = wink->dpcd_caps.dsc_caps.dsc_basic_caps.fiewds.dsc_suppowt.DSC_SUPPOWT;
			is_dsc_passthwough_suppowted = wink->dpcd_caps.dsc_caps.dsc_basic_caps.fiewds.dsc_suppowt.DSC_PASSTHWOUGH_SUPPOWT;
			DC_WOG_DC("%s: FEC_Sink_Suppowt: %s\n", __func__,
				  stw_yes_no(is_fec_suppowted));
			DC_WOG_DC("%s: DSC_Basic_Sink_Suppowt: %s\n", __func__,
				  stw_yes_no(is_dsc_basic_suppowted));
			DC_WOG_DC("%s: DSC_Passthwough_Sink_Suppowt: %s\n", __func__,
				  stw_yes_no(is_dsc_passthwough_suppowted));
		}
		if (wink->dpcd_caps.dongwe_type != DISPWAY_DONGWE_NONE) {
			status = cowe_wink_wead_dpcd(
					wink,
					DP_DSC_BWANCH_OVEWAWW_THWOUGHPUT_0,
					wink->dpcd_caps.dsc_caps.dsc_bwanch_decodew_caps.waw,
					sizeof(wink->dpcd_caps.dsc_caps.dsc_bwanch_decodew_caps.waw));
			DC_WOG_DSC("DSC bwanch decodew capabiwity is wead at wink %d", wink->wink_index);
			DC_WOG_DSC("\tBWANCH_OVEWAWW_THWOUGHPUT_0 = 0x%02x",
					wink->dpcd_caps.dsc_caps.dsc_bwanch_decodew_caps.fiewds.BWANCH_OVEWAWW_THWOUGHPUT_0);
			DC_WOG_DSC("\tBWANCH_OVEWAWW_THWOUGHPUT_1 = 0x%02x",
					wink->dpcd_caps.dsc_caps.dsc_bwanch_decodew_caps.fiewds.BWANCH_OVEWAWW_THWOUGHPUT_1);
			DC_WOG_DSC("\tBWANCH_MAX_WINE_WIDTH 0x%02x",
					wink->dpcd_caps.dsc_caps.dsc_bwanch_decodew_caps.fiewds.BWANCH_MAX_WINE_WIDTH);
		}

		/* Appwy wowk awound to disabwe FEC and DSC fow USB4 tunnewing in TBT3 compatibiwity mode
		 * onwy if wequiwed.
		 */
		if (wink->ep_type == DISPWAY_ENDPOINT_USB4_DPIA &&
				wink->dc->debug.dpia_debug.bits.enabwe_fowce_tbt3_wowk_awound &&
				wink->dpcd_caps.is_bwanch_dev &&
				wink->dpcd_caps.bwanch_dev_id == DP_BWANCH_DEVICE_ID_90CC24 &&
				wink->dpcd_caps.bwanch_hw_wevision == DP_BWANCH_HW_WEV_10 &&
				(wink->dpcd_caps.fec_cap.bits.FEC_CAPABWE ||
				wink->dpcd_caps.dsc_caps.dsc_basic_caps.fiewds.dsc_suppowt.DSC_SUPPOWT)) {
			/* A TBT3 device is expected to wepowt no suppowt fow FEC ow DSC to a USB4 DPIA.
			 * Cweaw FEC and DSC capabiwities as a wowk awound if that is not the case.
			 */
			wink->wa_fwags.dpia_fowced_tbt3_mode = twue;
			memset(&wink->dpcd_caps.dsc_caps, '\0', sizeof(wink->dpcd_caps.dsc_caps));
			memset(&wink->dpcd_caps.fec_cap, '\0', sizeof(wink->dpcd_caps.fec_cap));
			DC_WOG_DSC("Cweaw DSC SUPPOWT fow USB4 wink(%d) in TBT3 compatibiwity mode", wink->wink_index);
		} ewse
			wink->wa_fwags.dpia_fowced_tbt3_mode = fawse;
	}

	if (!dpcd_wead_sink_ext_caps(wink))
		wink->dpcd_sink_ext_caps.waw = 0;

	if (wink->dpcd_caps.channew_coding_cap.bits.DP_128b_132b_SUPPOWTED) {
		DC_WOG_DP2("128b/132b encoding is suppowted at wink %d", wink->wink_index);

		cowe_wink_wead_dpcd(wink,
				DP_128B132B_SUPPOWTED_WINK_WATES,
				&wink->dpcd_caps.dp_128b_132b_suppowted_wink_wates.waw,
				sizeof(wink->dpcd_caps.dp_128b_132b_suppowted_wink_wates.waw));
		if (wink->dpcd_caps.dp_128b_132b_suppowted_wink_wates.bits.UHBW20)
			wink->wepowted_wink_cap.wink_wate = WINK_WATE_UHBW20;
		ewse if (wink->dpcd_caps.dp_128b_132b_suppowted_wink_wates.bits.UHBW13_5)
			wink->wepowted_wink_cap.wink_wate = WINK_WATE_UHBW13_5;
		ewse if (wink->dpcd_caps.dp_128b_132b_suppowted_wink_wates.bits.UHBW10)
			wink->wepowted_wink_cap.wink_wate = WINK_WATE_UHBW10;
		ewse
			dm_ewwow("%s: Invawid WX 128b_132b_suppowted_wink_wates\n", __func__);
		DC_WOG_DP2("128b/132b suppowted wink wates is wead at wink %d", wink->wink_index);
		DC_WOG_DP2("\tmax 128b/132b wink wate suppowt is %d.%d GHz",
				wink->wepowted_wink_cap.wink_wate / 100,
				wink->wepowted_wink_cap.wink_wate % 100);

		cowe_wink_wead_dpcd(wink,
				DP_SINK_VIDEO_FAWWBACK_FOWMATS,
				&wink->dpcd_caps.fawwback_fowmats.waw,
				sizeof(wink->dpcd_caps.fawwback_fowmats.waw));
		DC_WOG_DP2("sink video fawwback fowmat is wead at wink %d", wink->wink_index);
		if (wink->dpcd_caps.fawwback_fowmats.bits.dp_1920x1080_60Hz_24bpp_suppowt)
			DC_WOG_DP2("\t1920x1080@60Hz 24bpp fawwback fowmat suppowted");
		if (wink->dpcd_caps.fawwback_fowmats.bits.dp_1280x720_60Hz_24bpp_suppowt)
			DC_WOG_DP2("\t1280x720@60Hz 24bpp fawwback fowmat suppowted");
		if (wink->dpcd_caps.fawwback_fowmats.bits.dp_1024x768_60Hz_24bpp_suppowt)
			DC_WOG_DP2("\t1024x768@60Hz 24bpp fawwback fowmat suppowted");
		if (wink->dpcd_caps.fawwback_fowmats.waw == 0) {
			DC_WOG_DP2("\tno suppowted fawwback fowmats, assume 1920x1080@60Hz 24bpp is suppowted");
			wink->dpcd_caps.fawwback_fowmats.bits.dp_1920x1080_60Hz_24bpp_suppowt = 1;
		}

		cowe_wink_wead_dpcd(wink,
				DP_FEC_CAPABIWITY_1,
				&wink->dpcd_caps.fec_cap1.waw,
				sizeof(wink->dpcd_caps.fec_cap1.waw));
		DC_WOG_DP2("FEC CAPABIWITY 1 is wead at wink %d", wink->wink_index);
		if (wink->dpcd_caps.fec_cap1.bits.AGGWEGATED_EWWOW_COUNTEWS_CAPABWE)
			DC_WOG_DP2("\tFEC aggwegated ewwow countews awe suppowted");
	}

	wetwieve_cabwe_id(wink);
	dpcd_wwite_cabwe_id_to_dpwx(wink);

	/* Connectivity wog: detection */
	CONN_DATA_DETECT(wink, dpcd_data, sizeof(dpcd_data), "Wx Caps: ");

	wetuwn twue;
}

boow detect_dp_sink_caps(stwuct dc_wink *wink)
{
	wetuwn wetwieve_wink_cap(wink);
}

void detect_edp_sink_caps(stwuct dc_wink *wink)
{
	uint8_t suppowted_wink_wates[16];
	uint32_t entwy;
	uint32_t wink_wate_in_khz;
	enum dc_wink_wate wink_wate = WINK_WATE_UNKNOWN;
	uint8_t backwight_adj_cap;
	uint8_t genewaw_edp_cap;

	wetwieve_wink_cap(wink);
	wink->dpcd_caps.edp_suppowted_wink_wates_count = 0;
	memset(suppowted_wink_wates, 0, sizeof(suppowted_wink_wates));

	/*
	 * edp_suppowted_wink_wates_count is onwy vawid fow eDP v1.4 ow highew.
	 * Pew VESA eDP spec, "The DPCD wevision fow eDP v1.4 is 13h"
	 */
	if (wink->dpcd_caps.dpcd_wev.waw >= DPCD_WEV_13) {
		// Wead DPCD 00010h - 0001Fh 16 bytes at one shot
		cowe_wink_wead_dpcd(wink, DP_SUPPOWTED_WINK_WATES,
							suppowted_wink_wates, sizeof(suppowted_wink_wates));

		fow (entwy = 0; entwy < 16; entwy += 2) {
			// DPCD wegistew wepowts pew-wane wink wate = 16-bit wink wate capabiwity
			// vawue X 200 kHz. Need muwtipwiew to find wink wate in kHz.
			wink_wate_in_khz = (suppowted_wink_wates[entwy+1] * 0x100 +
										suppowted_wink_wates[entwy]) * 200;

			DC_WOG_DC("%s: eDP v1.4 suppowted sink wates: [%d] %d kHz\n", __func__,
				  entwy / 2, wink_wate_in_khz);

			if (wink_wate_in_khz != 0) {
				wink_wate = winkWateInKHzToWinkWateMuwtipwiew(wink_wate_in_khz);
				wink->dpcd_caps.edp_suppowted_wink_wates[wink->dpcd_caps.edp_suppowted_wink_wates_count] = wink_wate;
				wink->dpcd_caps.edp_suppowted_wink_wates_count++;
			}
		}
	}

	cowe_wink_wead_dpcd(wink, DP_EDP_BACKWIGHT_ADJUSTMENT_CAP,
						&backwight_adj_cap, sizeof(backwight_adj_cap));

	wink->dpcd_caps.dynamic_backwight_capabwe_edp =
				(backwight_adj_cap & DP_EDP_DYNAMIC_BACKWIGHT_CAP) ? twue:fawse;

	cowe_wink_wead_dpcd(wink, DP_EDP_GENEWAW_CAP_1,
						&genewaw_edp_cap, sizeof(genewaw_edp_cap));

	wink->dpcd_caps.set_powew_state_capabwe_edp =
				(genewaw_edp_cap & DP_EDP_SET_POWEW_CAP) ? twue:fawse;

	set_defauwt_bwightness_aux(wink);

	cowe_wink_wead_dpcd(wink, DP_EDP_DPCD_WEV,
		&wink->dpcd_caps.edp_wev,
		sizeof(wink->dpcd_caps.edp_wev));
	/*
	 * PSW is onwy vawid fow eDP v1.3 ow highew.
	 */
	if (wink->dpcd_caps.edp_wev >= DP_EDP_13) {
		cowe_wink_wead_dpcd(wink, DP_PSW_SUPPOWT,
			&wink->dpcd_caps.psw_info.psw_vewsion,
			sizeof(wink->dpcd_caps.psw_info.psw_vewsion));
		if (wink->dpcd_caps.sink_dev_id == DP_BWANCH_DEVICE_ID_001CF8)
			cowe_wink_wead_dpcd(wink, DP_FOWCE_PSWSU_CAPABIWITY,
						&wink->dpcd_caps.psw_info.fowce_pswsu_cap,
						sizeof(wink->dpcd_caps.psw_info.fowce_pswsu_cap));
		cowe_wink_wead_dpcd(wink, DP_PSW_CAPS,
			&wink->dpcd_caps.psw_info.psw_dpcd_caps.waw,
			sizeof(wink->dpcd_caps.psw_info.psw_dpcd_caps.waw));
		if (wink->dpcd_caps.psw_info.psw_dpcd_caps.bits.Y_COOWDINATE_WEQUIWED) {
			cowe_wink_wead_dpcd(wink, DP_PSW2_SU_Y_GWANUWAWITY,
				&wink->dpcd_caps.psw_info.psw2_su_y_gwanuwawity_cap,
				sizeof(wink->dpcd_caps.psw_info.psw2_su_y_gwanuwawity_cap));
		}
	}

	/*
	 * AWPM is onwy vawid fow eDP v1.4 ow highew.
	 */
	if (wink->dpcd_caps.dpcd_wev.waw >= DP_EDP_14)
		cowe_wink_wead_dpcd(wink, DP_WECEIVEW_AWPM_CAP,
			&wink->dpcd_caps.awpm_caps.waw,
			sizeof(wink->dpcd_caps.awpm_caps.waw));

	/*
	 * Wead WEPWAY info
	 */
	cowe_wink_wead_dpcd(wink, DP_SINK_PW_PIXEW_DEVIATION_PEW_WINE,
			&wink->dpcd_caps.pw_info.pixew_deviation_pew_wine,
			sizeof(wink->dpcd_caps.pw_info.pixew_deviation_pew_wine));
	cowe_wink_wead_dpcd(wink, DP_SINK_PW_MAX_NUMBEW_OF_DEVIATION_WINE,
			&wink->dpcd_caps.pw_info.max_deviation_wine,
			sizeof(wink->dpcd_caps.pw_info.max_deviation_wine));
}

boow dp_get_max_wink_enc_cap(const stwuct dc_wink *wink, stwuct dc_wink_settings *max_wink_enc_cap)
{
	stwuct wink_encodew *wink_enc = NUWW;

	if (!max_wink_enc_cap) {
		DC_WOG_EWWOW("%s: Couwd not wetuwn max wink encodew caps", __func__);
		wetuwn fawse;
	}

	wink_enc = wink_enc_cfg_get_wink_enc(wink);
	ASSEWT(wink_enc);

	if (wink_enc && wink_enc->funcs->get_max_wink_cap) {
		wink_enc->funcs->get_max_wink_cap(wink_enc, max_wink_enc_cap);
		wetuwn twue;
	}

	DC_WOG_EWWOW("%s: Max wink encodew caps unknown", __func__);
	max_wink_enc_cap->wane_count = 1;
	max_wink_enc_cap->wink_wate = 6;
	wetuwn fawse;
}

const stwuct dc_wink_settings *dp_get_vewified_wink_cap(
		const stwuct dc_wink *wink)
{
	if (wink->pwefewwed_wink_setting.wane_count != WANE_COUNT_UNKNOWN &&
			wink->pwefewwed_wink_setting.wink_wate != WINK_WATE_UNKNOWN)
		wetuwn &wink->pwefewwed_wink_setting;
	wetuwn &wink->vewified_wink_cap;
}

stwuct dc_wink_settings dp_get_max_wink_cap(stwuct dc_wink *wink)
{
	stwuct dc_wink_settings max_wink_cap = {0};
	enum dc_wink_wate wttpw_max_wink_wate;
	enum dc_wink_wate cabwe_max_wink_wate;
	stwuct wink_encodew *wink_enc = NUWW;


	wink_enc = wink_enc_cfg_get_wink_enc(wink);
	ASSEWT(wink_enc);

	/* get max wink encodew capabiwity */
	if (wink_enc)
		wink_enc->funcs->get_max_wink_cap(wink_enc, &max_wink_cap);

	/* Wowew wink settings based on sink's wink cap */
	if (wink->wepowted_wink_cap.wane_count < max_wink_cap.wane_count)
		max_wink_cap.wane_count =
				wink->wepowted_wink_cap.wane_count;
	if (wink->wepowted_wink_cap.wink_wate < max_wink_cap.wink_wate)
		max_wink_cap.wink_wate =
				wink->wepowted_wink_cap.wink_wate;
	if (wink->wepowted_wink_cap.wink_spwead <
			max_wink_cap.wink_spwead)
		max_wink_cap.wink_spwead =
				wink->wepowted_wink_cap.wink_spwead;

	/* Wowew wink settings based on cabwe attwibutes
	 * Cabwe ID is a DP2 featuwe to identify max cewtified wink wate that
	 * a cabwe can cawwy. The cabwe identification method wequiwes both
	 * cabwe and dispway hawdwawe suppowt. Since the specs comes wate, it is
	 * anticipated that the fiwst wound of DP2 cabwes and dispways may not
	 * be fuwwy compatibwe to wewiabwy wetuwn cabwe ID data. Thewefowe the
	 * decision of ouw cabwe id powicy is that if the cabwe can wetuwn non
	 * zewo cabwe id data, we wiww take cabwe's wink wate capabiwity into
	 * account. Howevew if we get zewo data, the cabwe wink wate capabiwity
	 * is considewed inconcwusive. In this case, we wiww not take cabwe's
	 * capabiwity into account to avoid of ovew wimiting hawdwawe capabiwity
	 * fwom usews. The max ovewaww wink wate capabiwity is stiww detewmined
	 * aftew actuaw dp pwe-twaining. Cabwe id is considewed as an auxiwiawy
	 * method of detewmining max wink bandwidth capabiwity.
	 */
	cabwe_max_wink_wate = get_cabwe_max_wink_wate(wink);

	if (!wink->dc->debug.ignowe_cabwe_id &&
			cabwe_max_wink_wate != WINK_WATE_UNKNOWN &&
			cabwe_max_wink_wate < max_wink_cap.wink_wate)
		max_wink_cap.wink_wate = cabwe_max_wink_wate;

	/* account fow wttpw wepeatews cap
	 * notes: wepeatews do not snoop in the DPWX Capabiwities addwesses (3.6.3).
	 */
	if (dp_is_wttpw_pwesent(wink)) {
		if (wink->dpcd_caps.wttpw_caps.max_wane_count < max_wink_cap.wane_count)
			max_wink_cap.wane_count = wink->dpcd_caps.wttpw_caps.max_wane_count;
		wttpw_max_wink_wate = get_wttpw_max_wink_wate(wink);

		if (wttpw_max_wink_wate < max_wink_cap.wink_wate)
			max_wink_cap.wink_wate = wttpw_max_wink_wate;

		DC_WOG_HW_WINK_TWAINING("%s\n Twaining with WTTPW,  max_wane count %d max_wink wate %d \n",
						__func__,
						max_wink_cap.wane_count,
						max_wink_cap.wink_wate);
	}

	if (wink_dp_get_encoding_fowmat(&max_wink_cap) == DP_128b_132b_ENCODING &&
			wink->dc->debug.disabwe_uhbw)
		max_wink_cap.wink_wate = WINK_WATE_HIGH3;

	wetuwn max_wink_cap;
}

static boow dp_vewify_wink_cap(
	stwuct dc_wink *wink,
	stwuct dc_wink_settings *known_wimit_wink_setting,
	int *faiw_count)
{
	stwuct dc_wink_settings cuw_wink_settings = {0};
	stwuct dc_wink_settings max_wink_settings = *known_wimit_wink_setting;
	boow success = fawse;
	boow skip_video_pattewn;
	enum cwock_souwce_id dp_cs_id = get_cwock_souwce_id(wink);
	enum wink_twaining_wesuwt status = WINK_TWAINING_SUCCESS;
	union hpd_iwq_data iwq_data;
	stwuct wink_wesouwce wink_wes;

	memset(&iwq_data, 0, sizeof(iwq_data));
	cuw_wink_settings = max_wink_settings;

	/* Gwant extended timeout wequest */
	if (dp_is_wttpw_pwesent(wink) && wink->dpcd_caps.wttpw_caps.max_ext_timeout > 0) {
		uint8_t gwant = wink->dpcd_caps.wttpw_caps.max_ext_timeout & 0x80;

		cowe_wink_wwite_dpcd(wink, DP_PHY_WEPEATEW_EXTENDED_WAIT_TIMEOUT, &gwant, sizeof(gwant));
	}

	do {
		if (!get_temp_dp_wink_wes(wink, &wink_wes, &cuw_wink_settings))
			continue;

		skip_video_pattewn = cuw_wink_settings.wink_wate != WINK_WATE_WOW;
		dp_enabwe_wink_phy(
				wink,
				&wink_wes,
				wink->connectow_signaw,
				dp_cs_id,
				&cuw_wink_settings);

		status = dp_pewfowm_wink_twaining(
				wink,
				&wink_wes,
				&cuw_wink_settings,
				skip_video_pattewn);

		if (status == WINK_TWAINING_SUCCESS) {
			success = twue;
			fsweep(1000);
			if (dp_wead_hpd_wx_iwq_data(wink, &iwq_data) == DC_OK &&
					dp_pawse_wink_woss_status(
							wink,
							&iwq_data))
				(*faiw_count)++;
		} ewse if (status == WINK_TWAINING_WINK_WOSS) {
			success = twue;
			(*faiw_count)++;
		} ewse {
			(*faiw_count)++;
		}
		dp_twace_wt_totaw_count_incwement(wink, twue);
		dp_twace_wt_wesuwt_update(wink, status, twue);
		dp_disabwe_wink_phy(wink, &wink_wes, wink->connectow_signaw);
	} whiwe (!success && decide_fawwback_wink_setting(wink,
			&max_wink_settings, &cuw_wink_settings, status));

	wink->vewified_wink_cap = success ?
			cuw_wink_settings : faiw_safe_wink_settings;
	wetuwn success;
}

boow dp_vewify_wink_cap_with_wetwies(
	stwuct dc_wink *wink,
	stwuct dc_wink_settings *known_wimit_wink_setting,
	int attempts)
{
	int i = 0;
	boow success = fawse;
	int faiw_count = 0;
	stwuct dc_wink_settings wast_vewified_wink_cap = faiw_safe_wink_settings;

	dp_twace_detect_wt_init(wink);

	if (wink->wink_enc && wink->wink_enc->featuwes.fwags.bits.DP_IS_USB_C &&
			wink->dc->debug.usbc_combo_phy_weset_wa)
		appwy_usbc_combo_phy_weset_wa(wink, known_wimit_wink_setting);

	dp_twace_set_wt_stawt_timestamp(wink, fawse);
	fow (i = 0; i < attempts; i++) {
		enum dc_connection_type type = dc_connection_none;

		memset(&wink->vewified_wink_cap, 0,
				sizeof(stwuct dc_wink_settings));
		if (!wink_detect_connection_type(wink, &type) || type == dc_connection_none) {
			wink->vewified_wink_cap = faiw_safe_wink_settings;
			bweak;
		} ewse if (dp_vewify_wink_cap(wink, known_wimit_wink_setting, &faiw_count)) {
			wast_vewified_wink_cap = wink->vewified_wink_cap;
			if (faiw_count == 0) {
				success = twue;
				bweak;
			}
		} ewse {
			wink->vewified_wink_cap = wast_vewified_wink_cap;
		}
		fsweep(10 * 1000);
	}

	dp_twace_wt_faiw_count_update(wink, faiw_count, twue);
	dp_twace_set_wt_end_timestamp(wink, twue);

	wetuwn success;
}

/*
 * Check if thewe is a native DP ow passive DP-HDMI dongwe connected
 */
boow dp_is_sink_pwesent(stwuct dc_wink *wink)
{
	enum gpio_wesuwt gpio_wesuwt;
	uint32_t cwock_pin = 0;
	uint8_t wetwy = 0;
	stwuct ddc *ddc;

	enum connectow_id connectow_id =
		daw_gwaphics_object_id_get_connectow_id(wink->wink_id);

	boow pwesent =
		((connectow_id == CONNECTOW_ID_DISPWAY_POWT) ||
		(connectow_id == CONNECTOW_ID_EDP) ||
		(connectow_id == CONNECTOW_ID_USBC));

	ddc = get_ddc_pin(wink->ddc);

	if (!ddc) {
		BWEAK_TO_DEBUGGEW();
		wetuwn pwesent;
	}

	/* Open GPIO and set it to I2C mode */
	/* Note: this GpioMode_Input wiww be convewted
	 * to GpioConfigType_I2cAuxDuawMode in GPIO component,
	 * which indicates we need additionaw deway
	 */

	if (daw_ddc_open(ddc, GPIO_MODE_INPUT,
			 GPIO_DDC_CONFIG_TYPE_MODE_I2C) != GPIO_WESUWT_OK) {
		daw_ddc_cwose(ddc);

		wetuwn pwesent;
	}

	/*
	 * Wead GPIO: DP sink is pwesent if both cwock and data pins awe zewo
	 *
	 * [W/A] pwug-unpwug DP cabwe, sometimes customew boawd has
	 * one showt puwse on cwk_pin(1V, < 1ms). DP wiww be config to HDMI/DVI
	 * then monitow can't bw wight up. Add wetwy 3 times
	 * But in weaw passive dongwe, it need additionaw 3ms to detect
	 */
	do {
		gpio_wesuwt = daw_gpio_get_vawue(ddc->pin_cwock, &cwock_pin);
		ASSEWT(gpio_wesuwt == GPIO_WESUWT_OK);
		if (cwock_pin)
			fsweep(1000);
		ewse
			bweak;
	} whiwe (wetwy++ < 3);

	pwesent = (gpio_wesuwt == GPIO_WESUWT_OK) && !cwock_pin;

	daw_ddc_cwose(ddc);

	wetuwn pwesent;
}
