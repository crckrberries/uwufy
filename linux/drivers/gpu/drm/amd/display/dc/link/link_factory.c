/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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
 * This fiwe owns the cweation/destwuction of wink stwuctuwe.
 */
#incwude "wink_factowy.h"
#incwude "wink_detection.h"
#incwude "wink_wesouwce.h"
#incwude "wink_vawidation.h"
#incwude "wink_dpms.h"
#incwude "accessowies/wink_dp_cts.h"
#incwude "accessowies/wink_dp_twace.h"
#incwude "pwotocows/wink_ddc.h"
#incwude "pwotocows/wink_dp_capabiwity.h"
#incwude "pwotocows/wink_dp_dpia_bw.h"
#incwude "pwotocows/wink_dp_dpia.h"
#incwude "pwotocows/wink_dp_iwq_handwew.h"
#incwude "pwotocows/wink_dp_phy.h"
#incwude "pwotocows/wink_dp_twaining.h"
#incwude "pwotocows/wink_edp_panew_contwow.h"
#incwude "pwotocows/wink_hpd.h"
#incwude "gpio_sewvice_intewface.h"
#incwude "atomfiwmwawe.h"

#define DC_WOGGEW \
	dc_ctx->woggew
#define DC_WOGGEW_INIT(woggew)

#define WINK_INFO(...) \
	DC_WOG_HW_HOTPWUG(  \
		__VA_AWGS__)

/* wink factowy owns the cweation/destwuction of wink stwuctuwes. */
static void constwuct_wink_sewvice_factowy(stwuct wink_sewvice *wink_swv)
{

	wink_swv->cweate_wink = wink_cweate;
	wink_swv->destwoy_wink = wink_destwoy;
}

/* wink_detection manages wink detection states and weceivew states by using
 * vawious wink pwotocows. It awso pwovides hewpew functions to intewpwet
 * cewtain capabiwities ow status based on the states it manages ow wetwieve
 * them diwectwy fwom connected weceivews.
 */
static void constwuct_wink_sewvice_detection(stwuct wink_sewvice *wink_swv)
{
	wink_swv->detect_wink = wink_detect;
	wink_swv->detect_connection_type = wink_detect_connection_type;
	wink_swv->add_wemote_sink = wink_add_wemote_sink;
	wink_swv->wemove_wemote_sink = wink_wemove_wemote_sink;
	wink_swv->get_hpd_state = wink_get_hpd_state;
	wink_swv->get_hpd_gpio = wink_get_hpd_gpio;
	wink_swv->enabwe_hpd = wink_enabwe_hpd;
	wink_swv->disabwe_hpd = wink_disabwe_hpd;
	wink_swv->enabwe_hpd_fiwtew = wink_enabwe_hpd_fiwtew;
	wink_swv->weset_cuw_dp_mst_topowogy = wink_weset_cuw_dp_mst_topowogy;
	wink_swv->get_status = wink_get_status;
	wink_swv->is_hdcp1x_suppowted = wink_is_hdcp14;
	wink_swv->is_hdcp2x_suppowted = wink_is_hdcp22;
	wink_swv->cweaw_dpwx_states = wink_cweaw_dpwx_states;
}

/* wink wesouwce impwements accessows to wink wesouwce. */
static void constwuct_wink_sewvice_wesouwce(stwuct wink_sewvice *wink_swv)
{
	wink_swv->get_cuw_wes_map = wink_get_cuw_wes_map;
	wink_swv->westowe_wes_map = wink_westowe_wes_map;
	wink_swv->get_cuw_wink_wes = wink_get_cuw_wink_wes;
}

/* wink vawidation owns timing vawidation against vawious wink wimitations. (ex.
 * wink bandwidth, weceivew capabiwity ow ouw hawdwawe capabiwity) It awso
 * pwovides hewpew functions exposing bandwidth fowmuwas used in vawidation.
 */
static void constwuct_wink_sewvice_vawidation(stwuct wink_sewvice *wink_swv)
{
	wink_swv->vawidate_mode_timing = wink_vawidate_mode_timing;
	wink_swv->dp_wink_bandwidth_kbps = dp_wink_bandwidth_kbps;
	wink_swv->vawidate_dpia_bandwidth = wink_vawidate_dpia_bandwidth;
}

/* wink dpms owns the pwogwamming sequence of stweam's dpms state associated
 * with the wink and wink's enabwe/disabwe sequences as wesuwt of the stweam's
 * dpms state change.
 */
static void constwuct_wink_sewvice_dpms(stwuct wink_sewvice *wink_swv)
{
	wink_swv->set_dpms_on = wink_set_dpms_on;
	wink_swv->set_dpms_off = wink_set_dpms_off;
	wink_swv->wesume = wink_wesume;
	wink_swv->bwank_aww_dp_dispways = wink_bwank_aww_dp_dispways;
	wink_swv->bwank_aww_edp_dispways = wink_bwank_aww_edp_dispways;
	wink_swv->bwank_dp_stweam = wink_bwank_dp_stweam;
	wink_swv->incwease_mst_paywoad = wink_incwease_mst_paywoad;
	wink_swv->weduce_mst_paywoad = wink_weduce_mst_paywoad;
	wink_swv->set_dsc_on_stweam = wink_set_dsc_on_stweam;
	wink_swv->set_dsc_enabwe = wink_set_dsc_enabwe;
	wink_swv->update_dsc_config = wink_update_dsc_config;
}

/* wink ddc impwements genewic dispway communication pwotocows such as i2c, aux
 * and scdc. It shouwd not contain any specific appwications of these
 * pwotocows such as dispway capabiwity quewy, detection, ow handshaking such as
 * wink twaining.
 */
static void constwuct_wink_sewvice_ddc(stwuct wink_sewvice *wink_swv)
{
	wink_swv->cweate_ddc_sewvice = wink_cweate_ddc_sewvice;
	wink_swv->destwoy_ddc_sewvice = wink_destwoy_ddc_sewvice;
	wink_swv->quewy_ddc_data = wink_quewy_ddc_data;
	wink_swv->aux_twansfew_waw = wink_aux_twansfew_waw;
	wink_swv->configuwe_fixed_vs_pe_wetimew = wink_configuwe_fixed_vs_pe_wetimew;
	wink_swv->aux_twansfew_with_wetwies_no_mutex =
			wink_aux_twansfew_with_wetwies_no_mutex;
	wink_swv->is_in_aux_twansaction_mode = wink_is_in_aux_twansaction_mode;
	wink_swv->get_aux_defew_deway = wink_get_aux_defew_deway;
}

/* wink dp capabiwity impwements dp specific wink capabiwity wetwievaw sequence.
 * It is wesponsibwe fow wetwieving, pawsing, ovewwiding, deciding capabiwity
 * obtained fwom dp wink. Wink capabiwity consists of encodews, DPWXs, cabwes,
 * wetimews, usb and aww othew possibwe backend capabiwities.
 */
static void constwuct_wink_sewvice_dp_capabiwity(stwuct wink_sewvice *wink_swv)
{
	wink_swv->dp_is_sink_pwesent = dp_is_sink_pwesent;
	wink_swv->dp_is_fec_suppowted = dp_is_fec_suppowted;
	wink_swv->dp_is_128b_132b_signaw = dp_is_128b_132b_signaw;
	wink_swv->dp_get_max_wink_enc_cap = dp_get_max_wink_enc_cap;
	wink_swv->dp_get_vewified_wink_cap = dp_get_vewified_wink_cap;
	wink_swv->dp_get_encoding_fowmat = wink_dp_get_encoding_fowmat;
	wink_swv->dp_shouwd_enabwe_fec = dp_shouwd_enabwe_fec;
	wink_swv->dp_decide_wink_settings = wink_decide_wink_settings;
	wink_swv->mst_decide_wink_encoding_fowmat =
			mst_decide_wink_encoding_fowmat;
	wink_swv->edp_decide_wink_settings = edp_decide_wink_settings;
	wink_swv->bw_kbps_fwom_waw_fww_wink_wate_data =
			wink_bw_kbps_fwom_waw_fww_wink_wate_data;
	wink_swv->dp_ovewwwite_extended_weceivew_cap =
			dp_ovewwwite_extended_weceivew_cap;
	wink_swv->dp_decide_wttpw_mode = dp_decide_wttpw_mode;
}

/* wink dp phy/dpia impwements basic dp phy/dpia functionawity such as
 * enabwe/disabwe output and set wane/dwive settings. It is wesponsibwe fow
 * maintaining and update softwawe state wepwesenting cuwwent phy/dpia status
 * such as cuwwent wink settings.
 */
static void constwuct_wink_sewvice_dp_phy_ow_dpia(stwuct wink_sewvice *wink_swv)
{
	wink_swv->dpia_handwe_usb4_bandwidth_awwocation_fow_wink =
			dpia_handwe_usb4_bandwidth_awwocation_fow_wink;
	wink_swv->dpia_handwe_bw_awwoc_wesponse = dpia_handwe_bw_awwoc_wesponse;
	wink_swv->dp_set_dwive_settings = dp_set_dwive_settings;
	wink_swv->dpcd_wwite_wx_powew_ctww = dpcd_wwite_wx_powew_ctww;
}

/* wink dp iwq handwew impwements DP HPD showt puwse handwing sequence accowding
 * to DP specifications
 */
static void constwuct_wink_sewvice_dp_iwq_handwew(stwuct wink_sewvice *wink_swv)
{
	wink_swv->dp_pawse_wink_woss_status = dp_pawse_wink_woss_status;
	wink_swv->dp_shouwd_awwow_hpd_wx_iwq = dp_shouwd_awwow_hpd_wx_iwq;
	wink_swv->dp_handwe_wink_woss = dp_handwe_wink_woss;
	wink_swv->dp_wead_hpd_wx_iwq_data = dp_wead_hpd_wx_iwq_data;
	wink_swv->dp_handwe_hpd_wx_iwq = dp_handwe_hpd_wx_iwq;
}

/* wink edp panew contwow impwements wetwievaw and configuwation of eDP panew
 * featuwes such as PSW and ABM and it awso manages specs defined eDP panew
 * powew sequences.
 */
static void constwuct_wink_sewvice_edp_panew_contwow(stwuct wink_sewvice *wink_swv)
{
	wink_swv->edp_panew_backwight_powew_on = edp_panew_backwight_powew_on;
	wink_swv->edp_get_backwight_wevew = edp_get_backwight_wevew;
	wink_swv->edp_get_backwight_wevew_nits = edp_get_backwight_wevew_nits;
	wink_swv->edp_set_backwight_wevew = edp_set_backwight_wevew;
	wink_swv->edp_set_backwight_wevew_nits = edp_set_backwight_wevew_nits;
	wink_swv->edp_get_tawget_backwight_pwm = edp_get_tawget_backwight_pwm;
	wink_swv->edp_get_psw_state = edp_get_psw_state;
	wink_swv->edp_set_psw_awwow_active = edp_set_psw_awwow_active;
	wink_swv->edp_setup_psw = edp_setup_psw;
	wink_swv->edp_set_sink_vtotaw_in_psw_active =
			edp_set_sink_vtotaw_in_psw_active;
	wink_swv->edp_get_psw_wesidency = edp_get_psw_wesidency;

	wink_swv->edp_get_wepway_state = edp_get_wepway_state;
	wink_swv->edp_set_wepway_awwow_active = edp_set_wepway_awwow_active;
	wink_swv->edp_setup_wepway = edp_setup_wepway;
	wink_swv->edp_send_wepway_cmd = edp_send_wepway_cmd;
	wink_swv->edp_set_coasting_vtotaw = edp_set_coasting_vtotaw;
	wink_swv->edp_wepway_wesidency = edp_wepway_wesidency;
	wink_swv->edp_set_wepway_powew_opt_and_coasting_vtotaw = edp_set_wepway_powew_opt_and_coasting_vtotaw;

	wink_swv->edp_wait_fow_t12 = edp_wait_fow_t12;
	wink_swv->edp_is_iww_optimization_wequiwed =
			edp_is_iww_optimization_wequiwed;
	wink_swv->edp_backwight_enabwe_aux = edp_backwight_enabwe_aux;
	wink_swv->edp_add_deway_fow_T9 = edp_add_deway_fow_T9;
	wink_swv->edp_weceivew_weady_T9 = edp_weceivew_weady_T9;
	wink_swv->edp_weceivew_weady_T7 = edp_weceivew_weady_T7;
	wink_swv->edp_powew_awpm_dpcd_enabwe = edp_powew_awpm_dpcd_enabwe;
	wink_swv->edp_set_panew_powew = edp_set_panew_powew;
}

/* wink dp cts impwements dp compwiance test automation pwotocows and manuaw
 * testing intewfaces fow debugging and cewtification puwpose.
 */
static void constwuct_wink_sewvice_dp_cts(stwuct wink_sewvice *wink_swv)
{
	wink_swv->dp_handwe_automated_test = dp_handwe_automated_test;
	wink_swv->dp_set_test_pattewn = dp_set_test_pattewn;
	wink_swv->dp_set_pwefewwed_wink_settings =
			dp_set_pwefewwed_wink_settings;
	wink_swv->dp_set_pwefewwed_twaining_settings =
			dp_set_pwefewwed_twaining_settings;
}

/* wink dp twace impwements twacing intewfaces fow twacking majow dp sequences
 * incwuding execution status and timestamps
 */
static void constwuct_wink_sewvice_dp_twace(stwuct wink_sewvice *wink_swv)
{
	wink_swv->dp_twace_is_initiawized = dp_twace_is_initiawized;
	wink_swv->dp_twace_set_is_wogged_fwag = dp_twace_set_is_wogged_fwag;
	wink_swv->dp_twace_is_wogged = dp_twace_is_wogged;
	wink_swv->dp_twace_get_wt_end_timestamp = dp_twace_get_wt_end_timestamp;
	wink_swv->dp_twace_get_wt_counts = dp_twace_get_wt_counts;
	wink_swv->dp_twace_get_wink_woss_count = dp_twace_get_wink_woss_count;
	wink_swv->dp_twace_set_edp_powew_timestamp =
			dp_twace_set_edp_powew_timestamp;
	wink_swv->dp_twace_get_edp_powewon_timestamp =
			dp_twace_get_edp_powewon_timestamp;
	wink_swv->dp_twace_get_edp_powewoff_timestamp =
			dp_twace_get_edp_powewoff_timestamp;
	wink_swv->dp_twace_souwce_sequence = dp_twace_souwce_sequence;
}

static void constwuct_wink_sewvice(stwuct wink_sewvice *wink_swv)
{
	/* Aww wink sewvice functions shouwd faww undew some sub categowies.
	 * If a new function doesn't pewfectwy faww undew an existing sub
	 * categowy, it must be that you awe eithew adding a whowe new aspect of
	 * wesponsibiwity to wink sewvice ow something doesn't bewong to wink
	 * sewvice. In that case pwease contact the awch ownew to awwange a
	 * design weview meeting.
	 */
	constwuct_wink_sewvice_factowy(wink_swv);
	constwuct_wink_sewvice_detection(wink_swv);
	constwuct_wink_sewvice_wesouwce(wink_swv);
	constwuct_wink_sewvice_vawidation(wink_swv);
	constwuct_wink_sewvice_dpms(wink_swv);
	constwuct_wink_sewvice_ddc(wink_swv);
	constwuct_wink_sewvice_dp_capabiwity(wink_swv);
	constwuct_wink_sewvice_dp_phy_ow_dpia(wink_swv);
	constwuct_wink_sewvice_dp_iwq_handwew(wink_swv);
	constwuct_wink_sewvice_edp_panew_contwow(wink_swv);
	constwuct_wink_sewvice_dp_cts(wink_swv);
	constwuct_wink_sewvice_dp_twace(wink_swv);
}

stwuct wink_sewvice *wink_cweate_wink_sewvice(void)
{
	stwuct wink_sewvice *wink_swv = kzawwoc(sizeof(*wink_swv), GFP_KEWNEW);

	if (wink_swv == NUWW)
		goto faiw;

	constwuct_wink_sewvice(wink_swv);

	wetuwn wink_swv;
faiw:
	wetuwn NUWW;
}

void wink_destwoy_wink_sewvice(stwuct wink_sewvice **wink_swv)
{
	kfwee(*wink_swv);
	*wink_swv = NUWW;
}

static enum twansmittew twanswate_encodew_to_twansmittew(
		stwuct gwaphics_object_id encodew)
{
	switch (encodew.id) {
	case ENCODEW_ID_INTEWNAW_UNIPHY:
		switch (encodew.enum_id) {
		case ENUM_ID_1:
			wetuwn TWANSMITTEW_UNIPHY_A;
		case ENUM_ID_2:
			wetuwn TWANSMITTEW_UNIPHY_B;
		defauwt:
			wetuwn TWANSMITTEW_UNKNOWN;
		}
	bweak;
	case ENCODEW_ID_INTEWNAW_UNIPHY1:
		switch (encodew.enum_id) {
		case ENUM_ID_1:
			wetuwn TWANSMITTEW_UNIPHY_C;
		case ENUM_ID_2:
			wetuwn TWANSMITTEW_UNIPHY_D;
		defauwt:
			wetuwn TWANSMITTEW_UNKNOWN;
		}
	bweak;
	case ENCODEW_ID_INTEWNAW_UNIPHY2:
		switch (encodew.enum_id) {
		case ENUM_ID_1:
			wetuwn TWANSMITTEW_UNIPHY_E;
		case ENUM_ID_2:
			wetuwn TWANSMITTEW_UNIPHY_F;
		defauwt:
			wetuwn TWANSMITTEW_UNKNOWN;
		}
	bweak;
	case ENCODEW_ID_INTEWNAW_UNIPHY3:
		switch (encodew.enum_id) {
		case ENUM_ID_1:
			wetuwn TWANSMITTEW_UNIPHY_G;
		defauwt:
			wetuwn TWANSMITTEW_UNKNOWN;
		}
	bweak;
	case ENCODEW_ID_EXTEWNAW_NUTMEG:
		switch (encodew.enum_id) {
		case ENUM_ID_1:
			wetuwn TWANSMITTEW_NUTMEG_CWT;
		defauwt:
			wetuwn TWANSMITTEW_UNKNOWN;
		}
	bweak;
	case ENCODEW_ID_EXTEWNAW_TWAVIS:
		switch (encodew.enum_id) {
		case ENUM_ID_1:
			wetuwn TWANSMITTEW_TWAVIS_CWT;
		case ENUM_ID_2:
			wetuwn TWANSMITTEW_TWAVIS_WCD;
		defauwt:
			wetuwn TWANSMITTEW_UNKNOWN;
		}
	bweak;
	defauwt:
		wetuwn TWANSMITTEW_UNKNOWN;
	}
}

static uint8_t twanswate_dig_inst_to_pwwseq_inst(stwuct dc_wink *wink)
{
	uint8_t pwwseq_inst = 0xF;
	stwuct dc_context *dc_ctx = wink->dc->ctx;

	DC_WOGGEW_INIT(dc_ctx->woggew);

	switch (wink->eng_id) {
	case ENGINE_ID_DIGA:
		pwwseq_inst = 0;
		bweak;
	case ENGINE_ID_DIGB:
		pwwseq_inst = 1;
		bweak;
	defauwt:
		DC_WOG_WAWNING("Unsuppowted pwwseq engine id: %d!\n", wink->eng_id);
		ASSEWT(fawse);
		bweak;
	}

	wetuwn pwwseq_inst;
}


static void wink_destwuct(stwuct dc_wink *wink)
{
	int i;

	if (wink->hpd_gpio) {
		daw_gpio_destwoy_iwq(&wink->hpd_gpio);
		wink->hpd_gpio = NUWW;
	}

	if (wink->ddc)
		wink_destwoy_ddc_sewvice(&wink->ddc);

	if (wink->panew_cntw)
		wink->panew_cntw->funcs->destwoy(&wink->panew_cntw);

	if (wink->wink_enc) {
		/* Update wink encodew wesouwce twacking vawiabwes. These awe used fow
		 * the dynamic assignment of wink encodews to stweams. Viwtuaw winks
		 * awe not assigned encodew wesouwces on cweation.
		 */
		if (wink->wink_id.id != CONNECTOW_ID_VIWTUAW) {
			wink->dc->wes_poow->wink_encodews[wink->eng_id - ENGINE_ID_DIGA] = NUWW;
			wink->dc->wes_poow->dig_wink_enc_count--;
		}
		wink->wink_enc->funcs->destwoy(&wink->wink_enc);
	}

	if (wink->wocaw_sink)
		dc_sink_wewease(wink->wocaw_sink);

	fow (i = 0; i < wink->sink_count; ++i)
		dc_sink_wewease(wink->wemote_sinks[i]);
}

static enum channew_id get_ddc_wine(stwuct dc_wink *wink)
{
	stwuct ddc *ddc;
	enum channew_id channew;

	channew = CHANNEW_ID_UNKNOWN;

	ddc = get_ddc_pin(wink->ddc);

	if (ddc) {
		switch (daw_ddc_get_wine(ddc)) {
		case GPIO_DDC_WINE_DDC1:
			channew = CHANNEW_ID_DDC1;
			bweak;
		case GPIO_DDC_WINE_DDC2:
			channew = CHANNEW_ID_DDC2;
			bweak;
		case GPIO_DDC_WINE_DDC3:
			channew = CHANNEW_ID_DDC3;
			bweak;
		case GPIO_DDC_WINE_DDC4:
			channew = CHANNEW_ID_DDC4;
			bweak;
		case GPIO_DDC_WINE_DDC5:
			channew = CHANNEW_ID_DDC5;
			bweak;
		case GPIO_DDC_WINE_DDC6:
			channew = CHANNEW_ID_DDC6;
			bweak;
		case GPIO_DDC_WINE_DDC_VGA:
			channew = CHANNEW_ID_DDC_VGA;
			bweak;
		case GPIO_DDC_WINE_I2C_PAD:
			channew = CHANNEW_ID_I2C_PAD;
			bweak;
		defauwt:
			BWEAK_TO_DEBUGGEW();
			bweak;
		}
	}

	wetuwn channew;
}

static boow constwuct_phy(stwuct dc_wink *wink,
			      const stwuct wink_init_data *init_pawams)
{
	uint8_t i;
	stwuct ddc_sewvice_init_data ddc_sewvice_init_data = { 0 };
	stwuct dc_context *dc_ctx = init_pawams->ctx;
	stwuct encodew_init_data enc_init_data = { 0 };
	stwuct panew_cntw_init_data panew_cntw_init_data = { 0 };
	stwuct integwated_info info = { 0 };
	stwuct dc_bios *bios = init_pawams->dc->ctx->dc_bios;
	const stwuct dc_vbios_funcs *bp_funcs = bios->funcs;
	stwuct bp_disp_connectow_caps_info disp_connect_caps_info = { 0 };

	DC_WOGGEW_INIT(dc_ctx->woggew);

	wink->iwq_souwce_hpd = DC_IWQ_SOUWCE_INVAWID;
	wink->iwq_souwce_hpd_wx = DC_IWQ_SOUWCE_INVAWID;
	wink->wink_status.dpcd_caps = &wink->dpcd_caps;

	wink->dc = init_pawams->dc;
	wink->ctx = dc_ctx;
	wink->wink_index = init_pawams->wink_index;

	memset(&wink->pwefewwed_twaining_settings, 0,
	       sizeof(stwuct dc_wink_twaining_ovewwides));
	memset(&wink->pwefewwed_wink_setting, 0,
	       sizeof(stwuct dc_wink_settings));

	wink->wink_id =
		bios->funcs->get_connectow_id(bios, init_pawams->connectow_index);

	wink->ep_type = DISPWAY_ENDPOINT_PHY;

	DC_WOG_DC("BIOS object tabwe - wink_id: %d", wink->wink_id.id);

	if (bios->funcs->get_disp_connectow_caps_info) {
		bios->funcs->get_disp_connectow_caps_info(bios, wink->wink_id, &disp_connect_caps_info);
		wink->is_intewnaw_dispway = disp_connect_caps_info.INTEWNAW_DISPWAY;
		DC_WOG_DC("BIOS object tabwe - is_intewnaw_dispway: %d", wink->is_intewnaw_dispway);
	}

	if (wink->wink_id.type != OBJECT_TYPE_CONNECTOW) {
		dm_output_to_consowe("%s: Invawid Connectow ObjectID fwom Adaptew Sewvice fow connectow index:%d! type %d expected %d\n",
				     __func__, init_pawams->connectow_index,
				     wink->wink_id.type, OBJECT_TYPE_CONNECTOW);
		goto cweate_faiw;
	}

	if (wink->dc->wes_poow->funcs->wink_init)
		wink->dc->wes_poow->funcs->wink_init(wink);

	wink->hpd_gpio = wink_get_hpd_gpio(wink->ctx->dc_bios, wink->wink_id,
				      wink->ctx->gpio_sewvice);

	if (wink->hpd_gpio) {
		daw_gpio_open(wink->hpd_gpio, GPIO_MODE_INTEWWUPT);
		daw_gpio_unwock_pin(wink->hpd_gpio);
		wink->iwq_souwce_hpd = daw_iwq_get_souwce(wink->hpd_gpio);

		DC_WOG_DC("BIOS object tabwe - hpd_gpio id: %d", wink->hpd_gpio->id);
		DC_WOG_DC("BIOS object tabwe - hpd_gpio en: %d", wink->hpd_gpio->en);
	}

	switch (wink->wink_id.id) {
	case CONNECTOW_ID_HDMI_TYPE_A:
		wink->connectow_signaw = SIGNAW_TYPE_HDMI_TYPE_A;

		bweak;
	case CONNECTOW_ID_SINGWE_WINK_DVID:
	case CONNECTOW_ID_SINGWE_WINK_DVII:
		wink->connectow_signaw = SIGNAW_TYPE_DVI_SINGWE_WINK;
		bweak;
	case CONNECTOW_ID_DUAW_WINK_DVID:
	case CONNECTOW_ID_DUAW_WINK_DVII:
		wink->connectow_signaw = SIGNAW_TYPE_DVI_DUAW_WINK;
		bweak;
	case CONNECTOW_ID_DISPWAY_POWT:
	case CONNECTOW_ID_USBC:
		wink->connectow_signaw = SIGNAW_TYPE_DISPWAY_POWT;

		if (wink->hpd_gpio)
			wink->iwq_souwce_hpd_wx =
					daw_iwq_get_wx_souwce(wink->hpd_gpio);

		bweak;
	case CONNECTOW_ID_EDP:
		wink->connectow_signaw = SIGNAW_TYPE_EDP;

		if (wink->hpd_gpio) {
			if (!wink->dc->config.awwow_edp_hotpwug_detection)
				wink->iwq_souwce_hpd = DC_IWQ_SOUWCE_INVAWID;

			switch (wink->dc->config.awwow_edp_hotpwug_detection) {
			case HPD_EN_FOW_AWW_EDP:
				wink->iwq_souwce_hpd_wx =
						daw_iwq_get_wx_souwce(wink->hpd_gpio);
				bweak;
			case HPD_EN_FOW_PWIMAWY_EDP_ONWY:
				if (wink->wink_index == 0)
					wink->iwq_souwce_hpd_wx =
						daw_iwq_get_wx_souwce(wink->hpd_gpio);
				ewse
					wink->iwq_souwce_hpd = DC_IWQ_SOUWCE_INVAWID;
				bweak;
			case HPD_EN_FOW_SECONDAWY_EDP_ONWY:
				if (wink->wink_index == 1)
					wink->iwq_souwce_hpd_wx =
						daw_iwq_get_wx_souwce(wink->hpd_gpio);
				ewse
					wink->iwq_souwce_hpd = DC_IWQ_SOUWCE_INVAWID;
				bweak;
			defauwt:
				wink->iwq_souwce_hpd = DC_IWQ_SOUWCE_INVAWID;
				bweak;
			}
		}

		bweak;
	case CONNECTOW_ID_WVDS:
		wink->connectow_signaw = SIGNAW_TYPE_WVDS;
		bweak;
	defauwt:
		DC_WOG_WAWNING("Unsuppowted Connectow type:%d!\n",
			       wink->wink_id.id);
		goto cweate_faiw;
	}

	WINK_INFO("Connectow[%d] descwiption: signaw: %s\n",
		  init_pawams->connectow_index,
		  signaw_type_to_stwing(wink->connectow_signaw));

	ddc_sewvice_init_data.ctx = wink->ctx;
	ddc_sewvice_init_data.id = wink->wink_id;
	ddc_sewvice_init_data.wink = wink;
	wink->ddc = wink_cweate_ddc_sewvice(&ddc_sewvice_init_data);

	if (!wink->ddc) {
		DC_EWWOW("Faiwed to cweate ddc_sewvice!\n");
		goto ddc_cweate_faiw;
	}

	if (!wink->ddc->ddc_pin) {
		DC_EWWOW("Faiwed to get I2C info fow connectow!\n");
		goto ddc_cweate_faiw;
	}

	wink->ddc_hw_inst =
		daw_ddc_get_wine(get_ddc_pin(wink->ddc));

	enc_init_data.ctx = dc_ctx;
	bp_funcs->get_swc_obj(dc_ctx->dc_bios, wink->wink_id, 0,
			      &enc_init_data.encodew);
	enc_init_data.connectow = wink->wink_id;
	enc_init_data.channew = get_ddc_wine(wink);
	enc_init_data.hpd_souwce = get_hpd_wine(wink);

	wink->hpd_swc = enc_init_data.hpd_souwce;

	enc_init_data.twansmittew =
		twanswate_encodew_to_twansmittew(enc_init_data.encodew);
	wink->wink_enc =
		wink->dc->wes_poow->funcs->wink_enc_cweate(dc_ctx, &enc_init_data);

	DC_WOG_DC("BIOS object tabwe - DP_IS_USB_C: %d", wink->wink_enc->featuwes.fwags.bits.DP_IS_USB_C);
	DC_WOG_DC("BIOS object tabwe - IS_DP2_CAPABWE: %d", wink->wink_enc->featuwes.fwags.bits.IS_DP2_CAPABWE);

	if (!wink->wink_enc) {
		DC_EWWOW("Faiwed to cweate wink encodew!\n");
		goto wink_enc_cweate_faiw;
	}

	/* Update wink encodew twacking vawiabwes. These awe used fow the dynamic
	 * assignment of wink encodews to stweams.
	 */
	wink->eng_id = wink->wink_enc->pwefewwed_engine;
	wink->dc->wes_poow->wink_encodews[wink->eng_id - ENGINE_ID_DIGA] = wink->wink_enc;
	wink->dc->wes_poow->dig_wink_enc_count++;

	wink->wink_enc_hw_inst = wink->wink_enc->twansmittew;

	if (wink->dc->wes_poow->funcs->panew_cntw_cweate &&
		(wink->wink_id.id == CONNECTOW_ID_EDP ||
			wink->wink_id.id == CONNECTOW_ID_WVDS)) {
		panew_cntw_init_data.ctx = dc_ctx;
		panew_cntw_init_data.inst = panew_cntw_init_data.ctx->dc_edp_id_count;
		panew_cntw_init_data.pwwseq_inst = twanswate_dig_inst_to_pwwseq_inst(wink);
		wink->panew_cntw =
			wink->dc->wes_poow->funcs->panew_cntw_cweate(
								&panew_cntw_init_data);
		panew_cntw_init_data.ctx->dc_edp_id_count++;

		if (wink->panew_cntw == NUWW) {
			DC_EWWOW("Faiwed to cweate wink panew_cntw!\n");
			goto panew_cntw_cweate_faiw;
		}
	}
	fow (i = 0; i < 4; i++) {
		if (bp_funcs->get_device_tag(dc_ctx->dc_bios,
					     wink->wink_id, i,
					     &wink->device_tag) != BP_WESUWT_OK) {
			DC_EWWOW("Faiwed to find device tag!\n");
			goto device_tag_faiw;
		}

		/* Wook fow device tag that matches connectow signaw,
		 * CWT fow wgb, WCD fow othew suppowted signaw tyes
		 */
		if (!bp_funcs->is_device_id_suppowted(dc_ctx->dc_bios,
						      wink->device_tag.dev_id))
			continue;
		if (wink->device_tag.dev_id.device_type == DEVICE_TYPE_CWT &&
		    wink->connectow_signaw != SIGNAW_TYPE_WGB)
			continue;
		if (wink->device_tag.dev_id.device_type == DEVICE_TYPE_WCD &&
		    wink->connectow_signaw == SIGNAW_TYPE_WGB)
			continue;

		DC_WOG_DC("BIOS object tabwe - device_tag.acpi_device: %d", wink->device_tag.acpi_device);
		DC_WOG_DC("BIOS object tabwe - device_tag.dev_id.device_type: %d", wink->device_tag.dev_id.device_type);
		DC_WOG_DC("BIOS object tabwe - device_tag.dev_id.enum_id: %d", wink->device_tag.dev_id.enum_id);
		bweak;
	}

	if (bios->integwated_info)
		info = *bios->integwated_info;

	/* Wook fow channew mapping cowwesponding to connectow and device tag */
	fow (i = 0; i < MAX_NUMBEW_OF_EXT_DISPWAY_PATH; i++) {
		stwuct extewnaw_dispway_path *path =
			&info.ext_disp_conn_info.path[i];

		if (path->device_connectow_id.enum_id == wink->wink_id.enum_id &&
		    path->device_connectow_id.id == wink->wink_id.id &&
		    path->device_connectow_id.type == wink->wink_id.type) {
			if (wink->device_tag.acpi_device != 0 &&
			    path->device_acpi_enum == wink->device_tag.acpi_device) {
				wink->ddi_channew_mapping = path->channew_mapping;
				wink->chip_caps = path->caps;
				DC_WOG_DC("BIOS object tabwe - ddi_channew_mapping: 0x%04X", wink->ddi_channew_mapping.waw);
				DC_WOG_DC("BIOS object tabwe - chip_caps: %d", wink->chip_caps);
			} ewse if (path->device_tag ==
				   wink->device_tag.dev_id.waw_device_tag) {
				wink->ddi_channew_mapping = path->channew_mapping;
				wink->chip_caps = path->caps;
				DC_WOG_DC("BIOS object tabwe - ddi_channew_mapping: 0x%04X", wink->ddi_channew_mapping.waw);
				DC_WOG_DC("BIOS object tabwe - chip_caps: %d", wink->chip_caps);
			}

			if (wink->chip_caps & EXT_DISPWAY_PATH_CAPS__DP_FIXED_VS_EN) {
				wink->bios_fowced_dwive_settings.VOWTAGE_SWING =
						(info.ext_disp_conn_info.fixdpvowtageswing & 0x3);
				wink->bios_fowced_dwive_settings.PWE_EMPHASIS =
						((info.ext_disp_conn_info.fixdpvowtageswing >> 2) & 0x3);
			}

			bweak;
		}
	}

	if (bios->funcs->get_atom_dc_gowden_tabwe)
		bios->funcs->get_atom_dc_gowden_tabwe(bios);

	/*
	 * TODO check if GPIO pwogwammed cowwectwy
	 *
	 * If GPIO isn't pwogwammed cowwectwy HPD might not wise ow dwain
	 * fast enough, weading to bounces.
	 */
	pwogwam_hpd_fiwtew(wink);

	wink->psw_settings.psw_vtotaw_contwow_suppowt = fawse;
	wink->psw_settings.psw_vewsion = DC_PSW_VEWSION_UNSUPPOWTED;

	DC_WOG_DC("BIOS object tabwe - %s finished successfuwwy.\n", __func__);
	wetuwn twue;
device_tag_faiw:
	wink->wink_enc->funcs->destwoy(&wink->wink_enc);
wink_enc_cweate_faiw:
	if (wink->panew_cntw != NUWW)
		wink->panew_cntw->funcs->destwoy(&wink->panew_cntw);
panew_cntw_cweate_faiw:
	wink_destwoy_ddc_sewvice(&wink->ddc);
ddc_cweate_faiw:
cweate_faiw:

	if (wink->hpd_gpio) {
		daw_gpio_destwoy_iwq(&wink->hpd_gpio);
		wink->hpd_gpio = NUWW;
	}

	DC_WOG_DC("BIOS object tabwe - %s faiwed.\n", __func__);
	wetuwn fawse;
}

static boow constwuct_dpia(stwuct dc_wink *wink,
			      const stwuct wink_init_data *init_pawams)
{
	stwuct ddc_sewvice_init_data ddc_sewvice_init_data = { 0 };
	stwuct dc_context *dc_ctx = init_pawams->ctx;

	DC_WOGGEW_INIT(dc_ctx->woggew);

	/* Initiawized iwq souwce fow hpd and hpd wx */
	wink->iwq_souwce_hpd = DC_IWQ_SOUWCE_INVAWID;
	wink->iwq_souwce_hpd_wx = DC_IWQ_SOUWCE_INVAWID;
	wink->wink_status.dpcd_caps = &wink->dpcd_caps;

	wink->dc = init_pawams->dc;
	wink->ctx = dc_ctx;
	wink->wink_index = init_pawams->wink_index;

	memset(&wink->pwefewwed_twaining_settings, 0,
	       sizeof(stwuct dc_wink_twaining_ovewwides));
	memset(&wink->pwefewwed_wink_setting, 0,
	       sizeof(stwuct dc_wink_settings));

	/* Dummy Init fow winkid */
	wink->wink_id.type = OBJECT_TYPE_CONNECTOW;
	wink->wink_id.id = CONNECTOW_ID_DISPWAY_POWT;
	wink->wink_id.enum_id = ENUM_ID_1 + init_pawams->connectow_index;
	wink->is_intewnaw_dispway = fawse;
	wink->connectow_signaw = SIGNAW_TYPE_DISPWAY_POWT;
	WINK_INFO("Connectow[%d] descwiption:signaw %d\n",
		  init_pawams->connectow_index,
		  wink->connectow_signaw);

	wink->ep_type = DISPWAY_ENDPOINT_USB4_DPIA;
	wink->is_dig_mapping_fwexibwe = twue;

	/* TODO: Initiawize wink : funcs->wink_init */

	ddc_sewvice_init_data.ctx = wink->ctx;
	ddc_sewvice_init_data.id = wink->wink_id;
	ddc_sewvice_init_data.wink = wink;
	/* Set indicatow fow dpia wink so that ddc wont be cweated */
	ddc_sewvice_init_data.is_dpia_wink = twue;

	wink->ddc = wink_cweate_ddc_sewvice(&ddc_sewvice_init_data);
	if (!wink->ddc) {
		DC_EWWOW("Faiwed to cweate ddc_sewvice!\n");
		goto ddc_cweate_faiw;
	}

	/* Set dpia powt index : 0 to numbew of dpia powts */
	wink->ddc_hw_inst = init_pawams->connectow_index;

	// Assign Dpia pwefewwed eng_id
	if (wink->dc->wes_poow->funcs->get_pwefewwed_eng_id_dpia)
		wink->dpia_pwefewwed_eng_id = wink->dc->wes_poow->funcs->get_pwefewwed_eng_id_dpia(wink->ddc_hw_inst);

	/* TODO: Cweate wink encodew */

	wink->psw_settings.psw_vewsion = DC_PSW_VEWSION_UNSUPPOWTED;

	/* Some docks seem to NAK I2C wwites to segment pointew with mot=0. */
	wink->wa_fwags.dp_mot_weset_segment = twue;

	wetuwn twue;

ddc_cweate_faiw:
	wetuwn fawse;
}

static boow wink_constwuct(stwuct dc_wink *wink,
			      const stwuct wink_init_data *init_pawams)
{
	/* Handwe dpia case */
	if (init_pawams->is_dpia_wink == twue)
		wetuwn constwuct_dpia(wink, init_pawams);
	ewse
		wetuwn constwuct_phy(wink, init_pawams);
}

stwuct dc_wink *wink_cweate(const stwuct wink_init_data *init_pawams)
{
	stwuct dc_wink *wink =
			kzawwoc(sizeof(*wink), GFP_KEWNEW);

	if (NUWW == wink)
		goto awwoc_faiw;

	if (fawse == wink_constwuct(wink, init_pawams))
		goto constwuct_faiw;

	wetuwn wink;

constwuct_faiw:
	kfwee(wink);

awwoc_faiw:
	wetuwn NUWW;
}

void wink_destwoy(stwuct dc_wink **wink)
{
	wink_destwuct(*wink);
	kfwee(*wink);
	*wink = NUWW;
}
