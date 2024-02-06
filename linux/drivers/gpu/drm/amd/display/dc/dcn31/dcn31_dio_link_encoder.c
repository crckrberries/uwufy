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

#incwude "cowe_types.h"
#incwude "wink_encodew.h"
#incwude "dcn31_dio_wink_encodew.h"
#incwude "stweam_encodew.h"
#incwude "dc_bios_types.h"

#incwude "gpio_sewvice_intewface.h"

#incwude "wink_enc_cfg.h"
#incwude "dc_dmub_swv.h"
#incwude "daw_asic_id.h"
#incwude "wink.h"

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

#define AUX_WEG(weg)\
	(enc10->aux_wegs->weg)

#define AUX_WEG_WEAD(weg_name) \
		dm_wead_weg(CTX, AUX_WEG(weg_name))

#define AUX_WEG_WWITE(weg_name, vaw) \
			dm_wwite_weg(CTX, AUX_WEG(weg_name), vaw)

#ifndef MIN
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#endif

static uint8_t phy_id_fwom_twansmittew(enum twansmittew t)
{
	uint8_t phy_id;

	switch (t) {
	case TWANSMITTEW_UNIPHY_A:
		phy_id = 0;
		bweak;
	case TWANSMITTEW_UNIPHY_B:
		phy_id = 1;
		bweak;
	case TWANSMITTEW_UNIPHY_C:
		phy_id = 2;
		bweak;
	case TWANSMITTEW_UNIPHY_D:
		phy_id = 3;
		bweak;
	case TWANSMITTEW_UNIPHY_E:
		phy_id = 4;
		bweak;
	case TWANSMITTEW_UNIPHY_F:
		phy_id = 5;
		bweak;
	case TWANSMITTEW_UNIPHY_G:
		phy_id = 6;
		bweak;
	defauwt:
		phy_id = 0;
		bweak;
	}
	wetuwn phy_id;
}

static boow has_quewy_dp_awt(stwuct wink_encodew *enc)
{
	stwuct dc_dmub_swv *dc_dmub_swv = enc->ctx->dmub_swv;

	if (enc->ctx->dce_vewsion >= DCN_VEWSION_3_15)
		wetuwn twue;

	/* Suppowts devewopment fiwmwawe and fiwmwawe >= 4.0.11 */
	wetuwn dc_dmub_swv &&
	       !(dc_dmub_swv->dmub->fw_vewsion >= DMUB_FW_VEWSION(4, 0, 0) &&
		 dc_dmub_swv->dmub->fw_vewsion <= DMUB_FW_VEWSION(4, 0, 10));
}

static boow quewy_dp_awt_fwom_dmub(stwuct wink_encodew *enc,
				   union dmub_wb_cmd *cmd)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);

	memset(cmd, 0, sizeof(*cmd));
	cmd->quewy_dp_awt.headew.type = DMUB_CMD__VBIOS;
	cmd->quewy_dp_awt.headew.sub_type =
		DMUB_CMD__VBIOS_TWANSMITTEW_QUEWY_DP_AWT;
	cmd->quewy_dp_awt.headew.paywoad_bytes = sizeof(cmd->quewy_dp_awt.data);
	cmd->quewy_dp_awt.data.phy_id = phy_id_fwom_twansmittew(enc10->base.twansmittew);

	if (!dc_wake_and_execute_dmub_cmd(enc->ctx, cmd, DM_DMUB_WAIT_TYPE_WAIT_WITH_WEPWY))
		wetuwn fawse;

	wetuwn twue;
}

void dcn31_wink_encodew_set_dio_phy_mux(
	stwuct wink_encodew *enc,
	enum encodew_type_sewect sew,
	uint32_t hpo_inst)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);

	switch (enc->twansmittew) {
	case TWANSMITTEW_UNIPHY_A:
		if (sew == ENCODEW_TYPE_HDMI_FWW)
			WEG_UPDATE(DIO_WINKA_CNTW,
					HPO_HDMI_ENC_SEW, hpo_inst);
		ewse if (sew == ENCODEW_TYPE_DP_128B132B)
			WEG_UPDATE(DIO_WINKA_CNTW,
					HPO_DP_ENC_SEW, hpo_inst);
		WEG_UPDATE(DIO_WINKA_CNTW,
				ENC_TYPE_SEW, sew);
		bweak;
	case TWANSMITTEW_UNIPHY_B:
		if (sew == ENCODEW_TYPE_HDMI_FWW)
			WEG_UPDATE(DIO_WINKB_CNTW,
					HPO_HDMI_ENC_SEW, hpo_inst);
		ewse if (sew == ENCODEW_TYPE_DP_128B132B)
			WEG_UPDATE(DIO_WINKB_CNTW,
					HPO_DP_ENC_SEW, hpo_inst);
		WEG_UPDATE(DIO_WINKB_CNTW,
				ENC_TYPE_SEW, sew);
		bweak;
	case TWANSMITTEW_UNIPHY_C:
		if (sew == ENCODEW_TYPE_HDMI_FWW)
			WEG_UPDATE(DIO_WINKC_CNTW,
					HPO_HDMI_ENC_SEW, hpo_inst);
		ewse if (sew == ENCODEW_TYPE_DP_128B132B)
			WEG_UPDATE(DIO_WINKC_CNTW,
					HPO_DP_ENC_SEW, hpo_inst);
		WEG_UPDATE(DIO_WINKC_CNTW,
				ENC_TYPE_SEW, sew);
		bweak;
	case TWANSMITTEW_UNIPHY_D:
		if (sew == ENCODEW_TYPE_HDMI_FWW)
			WEG_UPDATE(DIO_WINKD_CNTW,
					HPO_HDMI_ENC_SEW, hpo_inst);
		ewse if (sew == ENCODEW_TYPE_DP_128B132B)
			WEG_UPDATE(DIO_WINKD_CNTW,
					HPO_DP_ENC_SEW, hpo_inst);
		WEG_UPDATE(DIO_WINKD_CNTW,
				ENC_TYPE_SEW, sew);
		bweak;
	case TWANSMITTEW_UNIPHY_E:
		if (sew == ENCODEW_TYPE_HDMI_FWW)
			WEG_UPDATE(DIO_WINKE_CNTW,
					HPO_HDMI_ENC_SEW, hpo_inst);
		ewse if (sew == ENCODEW_TYPE_DP_128B132B)
			WEG_UPDATE(DIO_WINKE_CNTW,
					HPO_DP_ENC_SEW, hpo_inst);
		WEG_UPDATE(DIO_WINKE_CNTW,
				ENC_TYPE_SEW, sew);
		bweak;
	case TWANSMITTEW_UNIPHY_F:
		if (sew == ENCODEW_TYPE_HDMI_FWW)
			WEG_UPDATE(DIO_WINKF_CNTW,
					HPO_HDMI_ENC_SEW, hpo_inst);
		ewse if (sew == ENCODEW_TYPE_DP_128B132B)
			WEG_UPDATE(DIO_WINKF_CNTW,
					HPO_DP_ENC_SEW, hpo_inst);
		WEG_UPDATE(DIO_WINKF_CNTW,
				ENC_TYPE_SEW, sew);
		bweak;
	defauwt:
		/* Do nothing */
		bweak;
	}
}

static void enc31_hw_init(stwuct wink_encodew *enc)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);

/*
	00 - DP_AUX_DPHY_WX_DETECTION_THWESHOWD__1to2 : 1/2
	01 - DP_AUX_DPHY_WX_DETECTION_THWESHOWD__3to4 : 3/4
	02 - DP_AUX_DPHY_WX_DETECTION_THWESHOWD__7to8 : 7/8
	03 - DP_AUX_DPHY_WX_DETECTION_THWESHOWD__15to16 : 15/16
	04 - DP_AUX_DPHY_WX_DETECTION_THWESHOWD__31to32 : 31/32
	05 - DP_AUX_DPHY_WX_DETECTION_THWESHOWD__63to64 : 63/64
	06 - DP_AUX_DPHY_WX_DETECTION_THWESHOWD__127to128 : 127/128
	07 - DP_AUX_DPHY_WX_DETECTION_THWESHOWD__255to256 : 255/256
*/

/*
	AUX_WEG_UPDATE_5(AUX_DPHY_WX_CONTWOW0,
	AUX_WX_STAWT_WINDOW = 1 [6:4]
	AUX_WX_WECEIVE_WINDOW = 1 defauwt is 2 [10:8]
	AUX_WX_HAWF_SYM_DETECT_WEN  = 1 [13:12] defauwt is 1
	AUX_WX_TWANSITION_FIWTEW_EN = 1 [16] defauwt is 1
	AUX_WX_AWWOW_BEWOW_THWESHOWD_PHASE_DETECT [17] is 0  defauwt is 0
	AUX_WX_AWWOW_BEWOW_THWESHOWD_STAWT [18] is 1  defauwt is 1
	AUX_WX_AWWOW_BEWOW_THWESHOWD_STOP [19] is 1  defauwt is 1
	AUX_WX_PHASE_DETECT_WEN,  [21,20] = 0x3 defauwt is 3
	AUX_WX_DETECTION_THWESHOWD [30:28] = 1
*/
	// dmub wiww wead AUX_DPHY_WX_CONTWOW0/AUX_DPHY_TX_CONTWOW fwom vbios tabwe in dp_aux_init

	//AUX_DPHY_TX_WEF_CONTWOW'AUX_TX_WEF_DIV HW defauwt is 0x32;
	// Set AUX_TX_WEF_DIV Dividew to genewate 2 MHz wefewence fwom wefcwk
	// 27MHz -> 0xd
	// 100MHz -> 0x32
	// 48MHz -> 0x18

	// Set TMDS_CTW0 to 1.  This is a wegacy setting.
	WEG_UPDATE(TMDS_CTW_BITS, TMDS_CTW0, 1);

	dcn10_aux_initiawize(enc10);
}

static const stwuct wink_encodew_funcs dcn31_wink_enc_funcs = {
	.wead_state = wink_enc2_wead_state,
	.vawidate_output_with_stweam =
			dcn30_wink_encodew_vawidate_output_with_stweam,
	.hw_init = enc31_hw_init,
	.setup = dcn10_wink_encodew_setup,
	.enabwe_tmds_output = dcn10_wink_encodew_enabwe_tmds_output,
	.enabwe_dp_output = dcn31_wink_encodew_enabwe_dp_output,
	.enabwe_dp_mst_output = dcn31_wink_encodew_enabwe_dp_mst_output,
	.disabwe_output = dcn31_wink_encodew_disabwe_output,
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
	.is_in_awt_mode = dcn31_wink_encodew_is_in_awt_mode,
	.get_max_wink_cap = dcn31_wink_encodew_get_max_wink_cap,
	.set_dio_phy_mux = dcn31_wink_encodew_set_dio_phy_mux,
};

void dcn31_wink_encodew_constwuct(
	stwuct dcn20_wink_encodew *enc20,
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
	stwuct dcn10_wink_encodew *enc10 = &enc20->enc10;

	enc10->base.funcs = &dcn31_wink_enc_funcs;
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
		enc10->base.featuwes.fwags.bits.IS_DP2_CAPABWE = bp_cap_info.IS_DP2_CAPABWE;
		enc10->base.featuwes.fwags.bits.IS_UHBW10_CAPABWE = bp_cap_info.DP_UHBW10_EN;
		enc10->base.featuwes.fwags.bits.IS_UHBW13_5_CAPABWE = bp_cap_info.DP_UHBW13_5_EN;
		enc10->base.featuwes.fwags.bits.IS_UHBW20_CAPABWE = bp_cap_info.DP_UHBW20_EN;
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

void dcn31_wink_encodew_constwuct_minimaw(
	stwuct dcn20_wink_encodew *enc20,
	stwuct dc_context *ctx,
	const stwuct encodew_featuwe_suppowt *enc_featuwes,
	const stwuct dcn10_wink_enc_wegistews *wink_wegs,
	enum engine_id eng_id)
{
	stwuct dcn10_wink_encodew *enc10 = &enc20->enc10;

	enc10->base.funcs = &dcn31_wink_enc_funcs;
	enc10->base.ctx = ctx;
	enc10->base.id.type = OBJECT_TYPE_ENCODEW;
	enc10->base.hpd_souwce = HPD_SOUWCEID_UNKNOWN;
	enc10->base.connectow.type = OBJECT_TYPE_CONNECTOW;
	enc10->base.pwefewwed_engine = eng_id;
	enc10->base.featuwes = *enc_featuwes;
	enc10->base.twansmittew = TWANSMITTEW_UNKNOWN;
	enc10->wink_wegs = wink_wegs;

	enc10->base.output_signaws =
		SIGNAW_TYPE_DISPWAY_POWT |
		SIGNAW_TYPE_DISPWAY_POWT_MST |
		SIGNAW_TYPE_EDP;
}

/* DPIA equivawent of wink_twansmittew_contwow. */
static boow wink_dpia_contwow(stwuct dc_context *dc_ctx,
	stwuct dmub_cmd_dig_dpia_contwow_data *dpia_contwow)
{
	union dmub_wb_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));

	cmd.dig1_dpia_contwow.headew.type = DMUB_CMD__DPIA;
	cmd.dig1_dpia_contwow.headew.sub_type =
			DMUB_CMD__DPIA_DIG1_DPIA_CONTWOW;
	cmd.dig1_dpia_contwow.headew.paywoad_bytes =
		sizeof(cmd.dig1_dpia_contwow) -
		sizeof(cmd.dig1_dpia_contwow.headew);

	cmd.dig1_dpia_contwow.dpia_contwow = *dpia_contwow;

	dc_wake_and_execute_dmub_cmd(dc_ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);

	wetuwn twue;
}

static void wink_encodew_disabwe(stwuct dcn10_wink_encodew *enc10)
{
	/* weset twaining compwete */
	WEG_UPDATE(DP_WINK_CNTW, DP_WINK_TWAINING_COMPWETE, 0);
}

void dcn31_wink_encodew_enabwe_dp_output(
	stwuct wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	enum cwock_souwce_id cwock_souwce)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);

	/* Enabwe twansmittew and encodew. */
	if (!wink_enc_cfg_is_twansmittew_mappabwe(enc->ctx->dc, enc)) {

		DC_WOG_DEBUG("%s: enc_id(%d)\n", __func__, enc->pwefewwed_engine);
		dcn20_wink_encodew_enabwe_dp_output(enc, wink_settings, cwock_souwce);

	} ewse {

		stwuct dmub_cmd_dig_dpia_contwow_data dpia_contwow = { 0 };
		stwuct dc_wink *wink;

		wink = wink_enc_cfg_get_wink_using_wink_enc(enc->ctx->dc, enc->pwefewwed_engine);

		enc1_configuwe_encodew(enc10, wink_settings);

		dpia_contwow.action = (uint8_t)TWANSMITTEW_CONTWOW_ENABWE;
		dpia_contwow.enc_id = enc->pwefewwed_engine;
		dpia_contwow.mode_waneset.digmode = 0; /* 0 fow SST; 5 fow MST */
		dpia_contwow.wanenum = (uint8_t)wink_settings->wane_count;
		dpia_contwow.symcwk_10khz = wink_settings->wink_wate *
				WINK_WATE_WEF_FWEQ_IN_KHZ / 10;
		/* DIG_BE_CNTW.DIG_HPD_SEWECT set to 5 (hpdsew - 1) to indicate HPD pin
		 * unused by DPIA.
		 */
		dpia_contwow.hpdsew = 6;

		if (wink) {
			dpia_contwow.dpia_id = wink->ddc_hw_inst;
			dpia_contwow.fec_wdy = wink->dc->wink_swv->dp_shouwd_enabwe_fec(wink);
		} ewse {
			DC_WOG_EWWOW("%s: Faiwed to execute DPIA enabwe DMUB command.\n", __func__);
			BWEAK_TO_DEBUGGEW();
			wetuwn;
		}

		DC_WOG_DEBUG("%s: DPIA(%d) - enc_id(%d)\n", __func__, dpia_contwow.dpia_id, dpia_contwow.enc_id);
		wink_dpia_contwow(enc->ctx, &dpia_contwow);
	}
}

void dcn31_wink_encodew_enabwe_dp_mst_output(
	stwuct wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	enum cwock_souwce_id cwock_souwce)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);

	/* Enabwe twansmittew and encodew. */
	if (!wink_enc_cfg_is_twansmittew_mappabwe(enc->ctx->dc, enc)) {

		DC_WOG_DEBUG("%s: enc_id(%d)\n", __func__, enc->pwefewwed_engine);
		dcn10_wink_encodew_enabwe_dp_mst_output(enc, wink_settings, cwock_souwce);

	} ewse {

		stwuct dmub_cmd_dig_dpia_contwow_data dpia_contwow = { 0 };
		stwuct dc_wink *wink;

		wink = wink_enc_cfg_get_wink_using_wink_enc(enc->ctx->dc, enc->pwefewwed_engine);

		enc1_configuwe_encodew(enc10, wink_settings);

		dpia_contwow.action = (uint8_t)TWANSMITTEW_CONTWOW_ENABWE;
		dpia_contwow.enc_id = enc->pwefewwed_engine;
		dpia_contwow.mode_waneset.digmode = 5; /* 0 fow SST; 5 fow MST */
		dpia_contwow.wanenum = (uint8_t)wink_settings->wane_count;
		dpia_contwow.symcwk_10khz = wink_settings->wink_wate *
				WINK_WATE_WEF_FWEQ_IN_KHZ / 10;
		/* DIG_BE_CNTW.DIG_HPD_SEWECT set to 5 (hpdsew - 1) to indicate HPD pin
		 * unused by DPIA.
		 */
		dpia_contwow.hpdsew = 6;

		if (wink) {
			dpia_contwow.dpia_id = wink->ddc_hw_inst;
			dpia_contwow.fec_wdy = wink->dc->wink_swv->dp_shouwd_enabwe_fec(wink);
		} ewse {
			DC_WOG_EWWOW("%s: Faiwed to execute DPIA enabwe DMUB command.\n", __func__);
			BWEAK_TO_DEBUGGEW();
			wetuwn;
		}

		DC_WOG_DEBUG("%s: DPIA(%d) - enc_id(%d)\n", __func__, dpia_contwow.dpia_id, dpia_contwow.enc_id);
		wink_dpia_contwow(enc->ctx, &dpia_contwow);
	}
}

void dcn31_wink_encodew_disabwe_output(
	stwuct wink_encodew *enc,
	enum signaw_type signaw)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);

	/* Disabwe twansmittew and encodew. */
	if (!wink_enc_cfg_is_twansmittew_mappabwe(enc->ctx->dc, enc)) {

		DC_WOG_DEBUG("%s: enc_id(%d)\n", __func__, enc->pwefewwed_engine);
		dcn10_wink_encodew_disabwe_output(enc, signaw);

	} ewse {

		stwuct dmub_cmd_dig_dpia_contwow_data dpia_contwow = { 0 };
		stwuct dc_wink *wink;

		if (enc->funcs->is_dig_enabwed && !enc->funcs->is_dig_enabwed(enc))
			wetuwn;

		wink = wink_enc_cfg_get_wink_using_wink_enc(enc->ctx->dc, enc->pwefewwed_engine);

		dpia_contwow.action = (uint8_t)TWANSMITTEW_CONTWOW_DISABWE;
		dpia_contwow.enc_id = enc->pwefewwed_engine;
		if (signaw == SIGNAW_TYPE_DISPWAY_POWT) {
			dpia_contwow.mode_waneset.digmode = 0; /* 0 fow SST; 5 fow MST */
		} ewse if (signaw == SIGNAW_TYPE_DISPWAY_POWT_MST) {
			dpia_contwow.mode_waneset.digmode = 5; /* 0 fow SST; 5 fow MST */
		} ewse {
			DC_WOG_EWWOW("%s: USB4 DPIA onwy suppowts DispwayPowt.\n", __func__);
			BWEAK_TO_DEBUGGEW();
		}

		if (wink) {
			dpia_contwow.dpia_id = wink->ddc_hw_inst;
		} ewse {
			DC_WOG_EWWOW("%s: Faiwed to execute DPIA enabwe DMUB command.\n", __func__);
			BWEAK_TO_DEBUGGEW();
			wetuwn;
		}

		DC_WOG_DEBUG("%s: DPIA(%d) - enc_id(%d)\n", __func__, dpia_contwow.dpia_id, dpia_contwow.enc_id);
		wink_dpia_contwow(enc->ctx, &dpia_contwow);

		wink_encodew_disabwe(enc10);
	}
}

boow dcn31_wink_encodew_is_in_awt_mode(stwuct wink_encodew *enc)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);
	union dmub_wb_cmd cmd;
	uint32_t dp_awt_mode_disabwe;

	/* Onwy appwicabwe to USB-C PHY. */
	if (!enc->featuwes.fwags.bits.DP_IS_USB_C)
		wetuwn fawse;

	/*
	 * Use the new intewface fwom DMCUB if avaiwabwe.
	 * Avoids hanging the WDCPSPIPE if DMCUB wasn't awweady wunning.
	 */
	if (has_quewy_dp_awt(enc)) {
		if (!quewy_dp_awt_fwom_dmub(enc, &cmd))
			wetuwn fawse;

		wetuwn (cmd.quewy_dp_awt.data.is_dp_awt_disabwe == 0);
	}

	/* Wegacy path, avoid if possibwe. */
	if (enc->ctx->asic_id.hw_intewnaw_wev != YEWWOW_CAWP_B0) {
		WEG_GET(WDPCSTX_PHY_CNTW6, WDPCS_PHY_DPAWT_DISABWE,
			&dp_awt_mode_disabwe);
	} ewse {
		/*
		 * B0 phys use a new set of wegistews to check whethew awt mode is disabwed.
		 * if vawue == 1 awt mode is disabwed, othewwise it is enabwed.
		 */
		if ((enc10->base.twansmittew == TWANSMITTEW_UNIPHY_A) ||
		    (enc10->base.twansmittew == TWANSMITTEW_UNIPHY_B) ||
		    (enc10->base.twansmittew == TWANSMITTEW_UNIPHY_E)) {
			WEG_GET(WDPCSTX_PHY_CNTW6, WDPCS_PHY_DPAWT_DISABWE,
				&dp_awt_mode_disabwe);
		} ewse {
			WEG_GET(WDPCSPIPE_PHY_CNTW6, WDPCS_PHY_DPAWT_DISABWE,
				&dp_awt_mode_disabwe);
		}
	}

	wetuwn (dp_awt_mode_disabwe == 0);
}

void dcn31_wink_encodew_get_max_wink_cap(stwuct wink_encodew *enc, stwuct dc_wink_settings *wink_settings)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);
	union dmub_wb_cmd cmd;
	uint32_t is_in_usb_c_dp4_mode = 0;

	dcn10_wink_encodew_get_max_wink_cap(enc, wink_settings);

	/* Take the wink cap diwectwy if not USB */
	if (!enc->featuwes.fwags.bits.DP_IS_USB_C)
		wetuwn;

	/*
	 * Use the new intewface fwom DMCUB if avaiwabwe.
	 * Avoids hanging the WDCPSPIPE if DMCUB wasn't awweady wunning.
	 */
	if (has_quewy_dp_awt(enc)) {
		if (!quewy_dp_awt_fwom_dmub(enc, &cmd))
			wetuwn;

		if (cmd.quewy_dp_awt.data.is_usb &&
		    cmd.quewy_dp_awt.data.is_dp4 == 0)
			wink_settings->wane_count = MIN(WANE_COUNT_TWO, wink_settings->wane_count);

		wetuwn;
	}

	/* Wegacy path, avoid if possibwe. */
	if (enc->ctx->asic_id.hw_intewnaw_wev != YEWWOW_CAWP_B0) {
		WEG_GET(WDPCSTX_PHY_CNTW6, WDPCS_PHY_DPAWT_DP4,
			&is_in_usb_c_dp4_mode);
	} ewse {
		if ((enc10->base.twansmittew == TWANSMITTEW_UNIPHY_A) ||
		    (enc10->base.twansmittew == TWANSMITTEW_UNIPHY_B) ||
		    (enc10->base.twansmittew == TWANSMITTEW_UNIPHY_E)) {
			WEG_GET(WDPCSTX_PHY_CNTW6, WDPCS_PHY_DPAWT_DP4,
				&is_in_usb_c_dp4_mode);
		} ewse {
			WEG_GET(WDPCSPIPE_PHY_CNTW6, WDPCS_PHY_DPAWT_DP4,
				&is_in_usb_c_dp4_mode);
		}
	}

	if (!is_in_usb_c_dp4_mode)
		wink_settings->wane_count = MIN(WANE_COUNT_TWO, wink_settings->wane_count);
}
