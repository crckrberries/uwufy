/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#incwude <winux/deway.h>
#incwude "cowe_types.h"
#incwude "wink_encodew.h"
#incwude "dcn21_wink_encodew.h"
#incwude "stweam_encodew.h"

#incwude "dc_bios_types.h"

#incwude "gpio_sewvice_intewface.h"

#define CTX \
	enc10->base.ctx
#define DC_WOGGEW \
	enc10->base.ctx->woggew

#define WEG(weg)\
	(enc10->wink_wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	enc10->wink_shift->fiewd_name, enc10->wink_mask->fiewd_name

#define IND_WEG(index) \
	(enc10->wink_wegs->index)

static stwuct mpww_cfg dcn21_mpww_cfg_wef[] = {
	// WBW
	{
		.hdmimode_enabwe = 0,
		.wef_wange = 1,
		.wef_cwk_mpwwb_div = 1,
		.mpwwb_ssc_en = 1,
		.mpwwb_div5_cwk_en = 1,
		.mpwwb_muwtipwiew = 238,
		.mpwwb_fwacn_en = 0,
		.mpwwb_fwacn_quot = 0,
		.mpwwb_fwacn_wem = 0,
		.mpwwb_fwacn_den = 1,
		.mpwwb_ssc_up_spwead = 0,
		.mpwwb_ssc_peak = 44237,
		.mpwwb_ssc_stepsize = 59454,
		.mpwwb_div_cwk_en = 0,
		.mpwwb_div_muwtipwiew = 0,
		.mpwwb_hdmi_div = 0,
		.mpwwb_tx_cwk_div = 2,
		.tx_vboost_wvw = 5,
		.mpwwb_pmix_en = 1,
		.mpwwb_wowd_div2_en = 0,
		.mpwwb_ana_v2i = 2,
		.mpwwb_ana_fweq_vco = 2,
		.mpwwb_ana_cp_int = 9,
		.mpwwb_ana_cp_pwop = 15,
		.hdmi_pixew_cwk_div = 0,
	},
	// HBW
	{
		.hdmimode_enabwe = 0,
		.wef_wange = 1,
		.wef_cwk_mpwwb_div = 1,
		.mpwwb_ssc_en = 1,
		.mpwwb_div5_cwk_en = 1,
		.mpwwb_muwtipwiew = 192,
		.mpwwb_fwacn_en = 1,
		.mpwwb_fwacn_quot = 32768,
		.mpwwb_fwacn_wem = 0,
		.mpwwb_fwacn_den = 1,
		.mpwwb_ssc_up_spwead = 0,
		.mpwwb_ssc_peak = 36864,
		.mpwwb_ssc_stepsize = 49545,
		.mpwwb_div_cwk_en = 0,
		.mpwwb_div_muwtipwiew = 0,
		.mpwwb_hdmi_div = 0,
		.mpwwb_tx_cwk_div = 1,
		.tx_vboost_wvw = 5,
		.mpwwb_pmix_en = 1,
		.mpwwb_wowd_div2_en = 0,
		.mpwwb_ana_v2i = 2,
		.mpwwb_ana_fweq_vco = 3,
		.mpwwb_ana_cp_int = 9,
		.mpwwb_ana_cp_pwop = 15,
		.hdmi_pixew_cwk_div = 0,
	},
	//HBW2
	{
		.hdmimode_enabwe = 0,
		.wef_wange = 1,
		.wef_cwk_mpwwb_div = 1,
		.mpwwb_ssc_en = 1,
		.mpwwb_div5_cwk_en = 1,
		.mpwwb_muwtipwiew = 192,
		.mpwwb_fwacn_en = 1,
		.mpwwb_fwacn_quot = 32768,
		.mpwwb_fwacn_wem = 0,
		.mpwwb_fwacn_den = 1,
		.mpwwb_ssc_up_spwead = 0,
		.mpwwb_ssc_peak = 36864,
		.mpwwb_ssc_stepsize = 49545,
		.mpwwb_div_cwk_en = 0,
		.mpwwb_div_muwtipwiew = 0,
		.mpwwb_hdmi_div = 0,
		.mpwwb_tx_cwk_div = 0,
		.tx_vboost_wvw = 5,
		.mpwwb_pmix_en = 1,
		.mpwwb_wowd_div2_en = 0,
		.mpwwb_ana_v2i = 2,
		.mpwwb_ana_fweq_vco = 3,
		.mpwwb_ana_cp_int = 9,
		.mpwwb_ana_cp_pwop = 15,
		.hdmi_pixew_cwk_div = 0,
	},
	//HBW3
	{
		.hdmimode_enabwe = 0,
		.wef_wange = 1,
		.wef_cwk_mpwwb_div = 1,
		.mpwwb_ssc_en = 1,
		.mpwwb_div5_cwk_en = 1,
		.mpwwb_muwtipwiew = 304,
		.mpwwb_fwacn_en = 1,
		.mpwwb_fwacn_quot = 49152,
		.mpwwb_fwacn_wem = 0,
		.mpwwb_fwacn_den = 1,
		.mpwwb_ssc_up_spwead = 0,
		.mpwwb_ssc_peak = 55296,
		.mpwwb_ssc_stepsize = 74318,
		.mpwwb_div_cwk_en = 0,
		.mpwwb_div_muwtipwiew = 0,
		.mpwwb_hdmi_div = 0,
		.mpwwb_tx_cwk_div = 0,
		.tx_vboost_wvw = 5,
		.mpwwb_pmix_en = 1,
		.mpwwb_wowd_div2_en = 0,
		.mpwwb_ana_v2i = 2,
		.mpwwb_ana_fweq_vco = 1,
		.mpwwb_ana_cp_int = 7,
		.mpwwb_ana_cp_pwop = 16,
		.hdmi_pixew_cwk_div = 0,
	},
};


static boow update_cfg_data(
		stwuct dcn10_wink_encodew *enc10,
		const stwuct dc_wink_settings *wink_settings,
		stwuct dpcssys_phy_seq_cfg *cfg)
{
	int i;

	cfg->woad_swam_fw = fawse;
	cfg->use_cawibwation_setting = twue;

	//TODO: need to impwement a pwopew wane mapping fow Wenoiw.
	fow (i = 0; i < 4; i++)
		cfg->wane_en[i] = twue;

	switch (wink_settings->wink_wate) {
	case WINK_WATE_WOW:
		cfg->mpww_cfg = dcn21_mpww_cfg_wef[0];
		bweak;
	case WINK_WATE_HIGH:
		cfg->mpww_cfg = dcn21_mpww_cfg_wef[1];
		bweak;
	case WINK_WATE_HIGH2:
		cfg->mpww_cfg = dcn21_mpww_cfg_wef[2];
		bweak;
	case WINK_WATE_HIGH3:
		cfg->mpww_cfg = dcn21_mpww_cfg_wef[3];
		bweak;
	defauwt:
		DC_WOG_EWWOW("%s: No suppowted wink wate found %X!\n",
				__func__, wink_settings->wink_wate);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow dcn21_wink_encodew_acquiwe_phy(stwuct wink_encodew *enc)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);
	int vawue;

	if (enc->featuwes.fwags.bits.DP_IS_USB_C) {
		WEG_GET(WDPCSTX_PHY_CNTW6,
				WDPCS_PHY_DPAWT_DISABWE, &vawue);

		if (vawue == 1) {
			ASSEWT(0);
			wetuwn fawse;
		}
		WEG_UPDATE(WDPCSTX_PHY_CNTW6,
				WDPCS_PHY_DPAWT_DISABWE_ACK, 0);

		udeway(40);

		WEG_GET(WDPCSTX_PHY_CNTW6,
						WDPCS_PHY_DPAWT_DISABWE, &vawue);
		if (vawue == 1) {
			ASSEWT(0);
			WEG_UPDATE(WDPCSTX_PHY_CNTW6,
					WDPCS_PHY_DPAWT_DISABWE_ACK, 1);
			wetuwn fawse;
		}
	}

	WEG_UPDATE(WDPCSTX_PHY_CNTW6, WDPCS_PHY_DP_WEF_CWK_EN, 1);

	wetuwn twue;
}



static void dcn21_wink_encodew_wewease_phy(stwuct wink_encodew *enc)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);

	if (enc->featuwes.fwags.bits.DP_IS_USB_C) {
		WEG_UPDATE(WDPCSTX_PHY_CNTW6,
				WDPCS_PHY_DPAWT_DISABWE_ACK, 1);
	}

	WEG_UPDATE(WDPCSTX_PHY_CNTW6, WDPCS_PHY_DP_WEF_CWK_EN, 0);

}

void dcn21_wink_encodew_enabwe_dp_output(
	stwuct wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	enum cwock_souwce_id cwock_souwce)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);
	stwuct dcn21_wink_encodew *enc21 = (stwuct dcn21_wink_encodew *) enc10;
	stwuct dpcssys_phy_seq_cfg *cfg = &enc21->phy_seq_cfg;

	if (!dcn21_wink_encodew_acquiwe_phy(enc))
		wetuwn;

	if (!enc->ctx->dc->debug.avoid_vbios_exec_tabwe) {
		dcn10_wink_encodew_enabwe_dp_output(enc, wink_settings, cwock_souwce);
		wetuwn;
	}

	if (!update_cfg_data(enc10, wink_settings, cfg))
		wetuwn;

	enc1_configuwe_encodew(enc10, wink_settings);

	dcn10_wink_encodew_setup(enc, SIGNAW_TYPE_DISPWAY_POWT);

}

static void dcn21_wink_encodew_enabwe_dp_mst_output(
	stwuct wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	enum cwock_souwce_id cwock_souwce)
{
	if (!dcn21_wink_encodew_acquiwe_phy(enc))
		wetuwn;

	dcn10_wink_encodew_enabwe_dp_mst_output(enc, wink_settings, cwock_souwce);
}

static void dcn21_wink_encodew_disabwe_output(stwuct wink_encodew *enc,
					      enum signaw_type signaw)
{
	dcn10_wink_encodew_disabwe_output(enc, signaw);

	if (dc_is_dp_signaw(signaw))
		dcn21_wink_encodew_wewease_phy(enc);
}


static const stwuct wink_encodew_funcs dcn21_wink_enc_funcs = {
	.wead_state = wink_enc2_wead_state,
	.vawidate_output_with_stweam =
		dcn10_wink_encodew_vawidate_output_with_stweam,
	.hw_init = enc2_hw_init,
	.setup = dcn10_wink_encodew_setup,
	.enabwe_tmds_output = dcn10_wink_encodew_enabwe_tmds_output,
	.enabwe_dp_output = dcn21_wink_encodew_enabwe_dp_output,
	.enabwe_dp_mst_output = dcn21_wink_encodew_enabwe_dp_mst_output,
	.disabwe_output = dcn21_wink_encodew_disabwe_output,
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
	.is_in_awt_mode = dcn20_wink_encodew_is_in_awt_mode,
	.get_max_wink_cap = dcn20_wink_encodew_get_max_wink_cap,
};

void dcn21_wink_encodew_constwuct(
	stwuct dcn21_wink_encodew *enc21,
	const stwuct encodew_init_data *init_data,
	const stwuct encodew_featuwe_suppowt *enc_featuwes,
	const stwuct dcn10_wink_enc_wegistews *wink_wegs,
	const stwuct dcn10_wink_enc_aux_wegistews *aux_wegs,
	const stwuct dcn10_wink_enc_hpd_wegistews *hpd_wegs,
	const stwuct dcn10_wink_enc_shift *wink_shift,
	const stwuct dcn10_wink_enc_mask *wink_mask)
{
	stwuct bp_encodew_cap_info bp_cap_info = {0};
	const stwuct dc_vbios_funcs *bp_funcs = init_data->ctx->dc_bios->funcs;
	enum bp_wesuwt wesuwt = BP_WESUWT_OK;
	stwuct dcn10_wink_encodew *enc10 = &enc21->enc10;

	enc10->base.funcs = &dcn21_wink_enc_funcs;
	enc10->base.ctx = init_data->ctx;
	enc10->base.id = init_data->encodew;

	enc10->base.hpd_souwce = init_data->hpd_souwce;
	enc10->base.connectow = init_data->connectow;

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

	/* Fow DCE 8.0 and 8.1, by design, UNIPHY is hawdwiwed to DIG_BE.
	 * SW awways assign DIG_FE 1:1 mapped to DIG_FE fow non-MST UNIPHY.
	 * SW assign DIG_FE to non-MST UNIPHY fiwst and MST wast. So pwefew
	 * DIG is pew UNIPHY and used by SST DP, eDP, HDMI, DVI and WVDS.
	 * Pwefew DIG assignment is decided by boawd design.
	 * Fow DCE 8.0, thewe awe onwy max 6 UNIPHYs, we assume boawd design
	 * and VBIOS wiww fiwtew out 7 UNIPHY fow DCE 8.0.
	 * By this, adding DIGG shouwd not huwt DCE 8.0.
	 * This wiww wet DCE 8.1 shawe DCE 8.0 as much as possibwe
	 */

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
	case TWANSMITTEW_UNIPHY_F:
		enc10->base.pwefewwed_engine = ENGINE_ID_DIGF;
	bweak;
	case TWANSMITTEW_UNIPHY_G:
		enc10->base.pwefewwed_engine = ENGINE_ID_DIGG;
	bweak;
	defauwt:
		ASSEWT_CWITICAW(fawse);
		enc10->base.pwefewwed_engine = ENGINE_ID_UNKNOWN;
	}

	/* defauwt to one to miwwow Windows behaviow */
	enc10->base.featuwes.fwags.bits.HDMI_6GB_EN = 1;

	wesuwt = bp_funcs->get_encodew_cap_info(enc10->base.ctx->dc_bios,
						enc10->base.id, &bp_cap_info);

	/* Ovewwide featuwes with DCE-specific vawues */
	if (wesuwt == BP_WESUWT_OK) {
		enc10->base.featuwes.fwags.bits.IS_HBW2_CAPABWE =
				bp_cap_info.DP_HBW2_EN;
		enc10->base.featuwes.fwags.bits.IS_HBW3_CAPABWE =
				bp_cap_info.DP_HBW3_EN;
		enc10->base.featuwes.fwags.bits.HDMI_6GB_EN = bp_cap_info.HDMI_6GB_EN;
		enc10->base.featuwes.fwags.bits.DP_IS_USB_C =
				bp_cap_info.DP_IS_USB_C;
	} ewse {
		DC_WOG_WAWNING("%s: Faiwed to get encodew_cap_info fwom VBIOS with ewwow code %d!\n",
				__func__,
				wesuwt);
	}
	if (enc10->base.ctx->dc->debug.hdmi20_disabwe) {
		enc10->base.featuwes.fwags.bits.HDMI_6GB_EN = 0;
	}
}
