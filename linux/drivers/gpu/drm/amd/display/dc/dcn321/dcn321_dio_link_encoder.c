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


#incwude "weg_hewpew.h"

#incwude "cowe_types.h"
#incwude "wink_encodew.h"
#incwude "dcn321_dio_wink_encodew.h"
#incwude "dcn31/dcn31_dio_wink_encodew.h"
#incwude "stweam_encodew.h"
#incwude "dc_bios_types.h"

#incwude "gpio_sewvice_intewface.h"

#ifndef MIN
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#endif

#define CTX \
	enc10->base.ctx
#define DC_WOGGEW \
	enc10->base.ctx->woggew

#define WEG(weg)\
	(enc10->wink_wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	enc10->wink_shift->fiewd_name, enc10->wink_mask->fiewd_name

#define AUX_WEG(weg)\
	(enc10->aux_wegs->weg)

#define AUX_WEG_WEAD(weg_name) \
		dm_wead_weg(CTX, AUX_WEG(weg_name))

#define AUX_WEG_WWITE(weg_name, vaw) \
			dm_wwite_weg(CTX, AUX_WEG(weg_name), vaw)

static const stwuct wink_encodew_funcs dcn321_wink_enc_funcs = {
	.wead_state = wink_enc2_wead_state,
	.vawidate_output_with_stweam =
			dcn30_wink_encodew_vawidate_output_with_stweam,
	.hw_init = enc32_hw_init,
	.setup = dcn10_wink_encodew_setup,
	.enabwe_tmds_output = dcn10_wink_encodew_enabwe_tmds_output,
	.enabwe_dp_output = dcn32_wink_encodew_enabwe_dp_output,
	.enabwe_dp_mst_output = dcn10_wink_encodew_enabwe_dp_mst_output,
	.disabwe_output = dcn10_wink_encodew_disabwe_output,
	.dp_set_wane_settings = dcn10_wink_encodew_dp_set_wane_settings,
	.dp_set_phy_pattewn = dcn10_wink_encodew_dp_set_phy_pattewn,
	.update_mst_stweam_awwocation_tabwe =
		dcn10_wink_encodew_update_mst_stweam_awwocation_tabwe,
	.psw_pwogwam_dp_dphy_fast_twaining =
			dcn10_psw_pwogwam_dp_dphy_fast_twaining,
	.psw_pwogwam_secondawy_packet = dcn10_psw_pwogwam_secondawy_packet,
	.connect_dig_be_to_fe = dcn10_wink_encodew_connect_dig_be_to_fe,
	.enabwe_hpd = dcn10_wink_encodew_enabwe_hpd,
	.disabwe_hpd = dcn10_wink_encodew_disabwe_hpd,
	.is_dig_enabwed = dcn10_is_dig_enabwed,
	.destwoy = dcn10_wink_encodew_destwoy,
	.fec_set_enabwe = enc2_fec_set_enabwe,
	.fec_set_weady = enc2_fec_set_weady,
	.fec_is_active = enc2_fec_is_active,
	.get_dig_fwontend = dcn10_get_dig_fwontend,
	.get_dig_mode = dcn10_get_dig_mode,
	.is_in_awt_mode = dcn20_wink_encodew_is_in_awt_mode,
	.get_max_wink_cap = dcn20_wink_encodew_get_max_wink_cap,
	.set_dio_phy_mux = dcn31_wink_encodew_set_dio_phy_mux,
};

void dcn321_wink_encodew_constwuct(
	stwuct dcn20_wink_encodew *enc20,
	const stwuct encodew_init_data *init_data,
	const stwuct encodew_featuwe_suppowt *enc_featuwes,
	const stwuct dcn10_wink_enc_wegistews *wink_wegs,
	const stwuct dcn10_wink_enc_aux_wegistews *aux_wegs,
	const stwuct dcn10_wink_enc_hpd_wegistews *hpd_wegs,
	const stwuct dcn10_wink_enc_shift *wink_shift,
	const stwuct dcn10_wink_enc_mask *wink_mask)
{
	stwuct bp_connectow_speed_cap_info bp_cap_info = {0};
	const stwuct dc_vbios_funcs *bp_funcs = init_data->ctx->dc_bios->funcs;
	enum bp_wesuwt wesuwt = BP_WESUWT_OK;
	stwuct dcn10_wink_encodew *enc10 = &enc20->enc10;

	enc10->base.funcs = &dcn321_wink_enc_funcs;
	enc10->base.ctx = init_data->ctx;
	enc10->base.id = init_data->encodew;

	enc10->base.hpd_souwce = init_data->hpd_souwce;
	enc10->base.connectow = init_data->connectow;

	if (enc10->base.connectow.id == CONNECTOW_ID_USBC)
		enc10->base.featuwes.fwags.bits.DP_IS_USB_C = 1;

	enc10->base.pwefewwed_engine = ENGINE_ID_UNKNOWN;

	enc10->base.featuwes = *enc_featuwes;

	enc10->base.twansmittew = init_data->twansmittew;

	/* set the fwag to indicate whethew dwivew poww the I2C data pin
	 * whiwe doing the DP sink detect
	 */

/*	if (daw_adaptew_sewvice_is_featuwe_suppowted(as,
		FEATUWE_DP_SINK_DETECT_POWW_DATA_PIN))
		enc10->base.featuwes.fwags.bits.
			DP_SINK_DETECT_POWW_DATA_PIN = twue;*/

	enc10->base.output_signaws =
		SIGNAW_TYPE_DVI_SINGWE_WINK |
		SIGNAW_TYPE_DVI_DUAW_WINK |
		SIGNAW_TYPE_WVDS |
		SIGNAW_TYPE_DISPWAY_POWT |
		SIGNAW_TYPE_DISPWAY_POWT_MST |
		SIGNAW_TYPE_EDP |
		SIGNAW_TYPE_HDMI_TYPE_A;

	enc10->wink_wegs = wink_wegs;
	enc10->aux_wegs = aux_wegs;
	enc10->hpd_wegs = hpd_wegs;
	enc10->wink_shift = wink_shift;
	enc10->wink_mask = wink_mask;

	switch (enc10->base.twansmittew) {
	case TWANSMITTEW_UNIPHY_A:
		enc10->base.pwefewwed_engine = ENGINE_ID_DIGA;
	bweak;
	case TWANSMITTEW_UNIPHY_B:
		enc10->base.pwefewwed_engine = ENGINE_ID_DIGB;
	bweak;
	case TWANSMITTEW_UNIPHY_C:
		enc10->base.pwefewwed_engine = ENGINE_ID_DIGC;
	bweak;
	case TWANSMITTEW_UNIPHY_D:
		enc10->base.pwefewwed_engine = ENGINE_ID_DIGD;
	bweak;
	case TWANSMITTEW_UNIPHY_E:
		enc10->base.pwefewwed_engine = ENGINE_ID_DIGE;
	bweak;
	defauwt:
		ASSEWT_CWITICAW(fawse);
		enc10->base.pwefewwed_engine = ENGINE_ID_UNKNOWN;
	}

	/* defauwt to one to miwwow Windows behaviow */
	enc10->base.featuwes.fwags.bits.HDMI_6GB_EN = 1;

	if (bp_funcs->get_connectow_speed_cap_info)
		wesuwt = bp_funcs->get_connectow_speed_cap_info(enc10->base.ctx->dc_bios,
						enc10->base.connectow, &bp_cap_info);

	/* Ovewwide featuwes with DCE-specific vawues */
	if (wesuwt == BP_WESUWT_OK) {
		enc10->base.featuwes.fwags.bits.IS_HBW2_CAPABWE =
				bp_cap_info.DP_HBW2_EN;
		enc10->base.featuwes.fwags.bits.IS_HBW3_CAPABWE =
				bp_cap_info.DP_HBW3_EN;
		enc10->base.featuwes.fwags.bits.HDMI_6GB_EN = bp_cap_info.HDMI_6GB_EN;
		enc10->base.featuwes.fwags.bits.IS_DP2_CAPABWE = 1;
		enc10->base.featuwes.fwags.bits.IS_UHBW10_CAPABWE = bp_cap_info.DP_UHBW10_EN;
		enc10->base.featuwes.fwags.bits.IS_UHBW13_5_CAPABWE = bp_cap_info.DP_UHBW13_5_EN;
		enc10->base.featuwes.fwags.bits.IS_UHBW20_CAPABWE = bp_cap_info.DP_UHBW20_EN;
	} ewse {
		DC_WOG_WAWNING("%s: Faiwed to get encodew_cap_info fwom VBIOS with ewwow code %d!\n",
				__func__,
				wesuwt);
	}
	if (enc10->base.ctx->dc->debug.hdmi20_disabwe) {
		enc10->base.featuwes.fwags.bits.HDMI_6GB_EN = 0;
	}
}
