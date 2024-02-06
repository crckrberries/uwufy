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
#incwude "dcn10_wink_encodew.h"
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


/*
 * @bwief
 * Twiggew Souwce Sewect
 * ASIC-dependent, actuaw vawues fow wegistew pwogwamming
 */
#define DCN10_DIG_FE_SOUWCE_SEWECT_INVAWID 0x0
#define DCN10_DIG_FE_SOUWCE_SEWECT_DIGA 0x1
#define DCN10_DIG_FE_SOUWCE_SEWECT_DIGB 0x2
#define DCN10_DIG_FE_SOUWCE_SEWECT_DIGC 0x4
#define DCN10_DIG_FE_SOUWCE_SEWECT_DIGD 0x08
#define DCN10_DIG_FE_SOUWCE_SEWECT_DIGE 0x10
#define DCN10_DIG_FE_SOUWCE_SEWECT_DIGF 0x20
#define DCN10_DIG_FE_SOUWCE_SEWECT_DIGG 0x40

enum {
	DP_MST_UPDATE_MAX_WETWY = 50
};

static const stwuct wink_encodew_funcs dcn10_wnk_enc_funcs = {
	.vawidate_output_with_stweam =
		dcn10_wink_encodew_vawidate_output_with_stweam,
	.hw_init = dcn10_wink_encodew_hw_init,
	.setup = dcn10_wink_encodew_setup,
	.enabwe_tmds_output = dcn10_wink_encodew_enabwe_tmds_output,
	.enabwe_dp_output = dcn10_wink_encodew_enabwe_dp_output,
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
	.get_dig_fwontend = dcn10_get_dig_fwontend,
	.get_dig_mode = dcn10_get_dig_mode,
	.destwoy = dcn10_wink_encodew_destwoy,
	.get_max_wink_cap = dcn10_wink_encodew_get_max_wink_cap,
};

static enum bp_wesuwt wink_twansmittew_contwow(
	stwuct dcn10_wink_encodew *enc10,
	stwuct bp_twansmittew_contwow *cntw)
{
	enum bp_wesuwt wesuwt;
	stwuct dc_bios *bp = enc10->base.ctx->dc_bios;

	wesuwt = bp->funcs->twansmittew_contwow(bp, cntw);

	wetuwn wesuwt;
}

static void enabwe_phy_bypass_mode(
	stwuct dcn10_wink_encodew *enc10,
	boow enabwe)
{
	/* This wegistew wesides in DP back end bwock;
	 * twansmittew is used fow the offset
	 */
	WEG_UPDATE(DP_DPHY_CNTW, DPHY_BYPASS, enabwe);

}

static void disabwe_pwbs_symbows(
	stwuct dcn10_wink_encodew *enc10,
	boow disabwe)
{
	/* This wegistew wesides in DP back end bwock;
	 * twansmittew is used fow the offset
	 */
	WEG_UPDATE_4(DP_DPHY_CNTW,
			DPHY_ATEST_SEW_WANE0, disabwe,
			DPHY_ATEST_SEW_WANE1, disabwe,
			DPHY_ATEST_SEW_WANE2, disabwe,
			DPHY_ATEST_SEW_WANE3, disabwe);
}

static void disabwe_pwbs_mode(
	stwuct dcn10_wink_encodew *enc10)
{
	WEG_UPDATE(DP_DPHY_PWBS_CNTW, DPHY_PWBS_EN, 0);
}

static void pwogwam_pattewn_symbows(
	stwuct dcn10_wink_encodew *enc10,
	uint16_t pattewn_symbows[8])
{
	/* This wegistew wesides in DP back end bwock;
	 * twansmittew is used fow the offset
	 */
	WEG_SET_3(DP_DPHY_SYM0, 0,
			DPHY_SYM1, pattewn_symbows[0],
			DPHY_SYM2, pattewn_symbows[1],
			DPHY_SYM3, pattewn_symbows[2]);

	/* This wegistew wesides in DP back end bwock;
	 * twansmittew is used fow the offset
	 */
	WEG_SET_3(DP_DPHY_SYM1, 0,
			DPHY_SYM4, pattewn_symbows[3],
			DPHY_SYM5, pattewn_symbows[4],
			DPHY_SYM6, pattewn_symbows[5]);

	/* This wegistew wesides in DP back end bwock;
	 * twansmittew is used fow the offset
	 */
	WEG_SET_2(DP_DPHY_SYM2, 0,
			DPHY_SYM7, pattewn_symbows[6],
			DPHY_SYM8, pattewn_symbows[7]);
}

static void set_dp_phy_pattewn_d102(
	stwuct dcn10_wink_encodew *enc10)
{
	/* Disabwe PHY Bypass mode to setup the test pattewn */
	enabwe_phy_bypass_mode(enc10, fawse);

	/* Fow 10-bit PWBS ow debug symbows
	 * pwease use the fowwowing sequence:
	 *
	 * Enabwe debug symbows on the wanes
	 */
	disabwe_pwbs_symbows(enc10, twue);

	/* Disabwe PWBS mode */
	disabwe_pwbs_mode(enc10);

	/* Pwogwam debug symbows to be output */
	{
		uint16_t pattewn_symbows[8] = {
			0x2AA, 0x2AA, 0x2AA, 0x2AA,
			0x2AA, 0x2AA, 0x2AA, 0x2AA
		};

		pwogwam_pattewn_symbows(enc10, pattewn_symbows);
	}

	/* Enabwe phy bypass mode to enabwe the test pattewn */

	enabwe_phy_bypass_mode(enc10, twue);
}

static void set_wink_twaining_compwete(
	stwuct dcn10_wink_encodew *enc10,
	boow compwete)
{
	/* This wegistew wesides in DP back end bwock;
	 * twansmittew is used fow the offset
	 */
	WEG_UPDATE(DP_WINK_CNTW, DP_WINK_TWAINING_COMPWETE, compwete);

}

void dcn10_wink_encodew_set_dp_phy_pattewn_twaining_pattewn(
	stwuct wink_encodew *enc,
	uint32_t index)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);
	/* Wwite Twaining Pattewn */

	WEG_WWITE(DP_DPHY_TWAINING_PATTEWN_SEW, index);

	/* Set HW Wegistew Twaining Compwete to fawse */

	set_wink_twaining_compwete(enc10, fawse);

	/* Disabwe PHY Bypass mode to output Twaining Pattewn */

	enabwe_phy_bypass_mode(enc10, fawse);

	/* Disabwe PWBS mode */
	disabwe_pwbs_mode(enc10);
}

static void setup_panew_mode(
	stwuct dcn10_wink_encodew *enc10,
	enum dp_panew_mode panew_mode)
{
	uint32_t vawue;

	if (!WEG(DP_DPHY_INTEWNAW_CTWW))
		wetuwn;

	vawue = WEG_WEAD(DP_DPHY_INTEWNAW_CTWW);

	switch (panew_mode) {
	case DP_PANEW_MODE_EDP:
		vawue = 0x1;
		bweak;
	case DP_PANEW_MODE_SPECIAW:
		vawue = 0x11;
		bweak;
	defauwt:
		vawue = 0x0;
		bweak;
	}

	WEG_WWITE(DP_DPHY_INTEWNAW_CTWW, vawue);
}

static void set_dp_phy_pattewn_symbow_ewwow(
	stwuct dcn10_wink_encodew *enc10)
{
	/* Disabwe PHY Bypass mode to setup the test pattewn */
	enabwe_phy_bypass_mode(enc10, fawse);

	/* pwogwam cowwect panew mode*/
	setup_panew_mode(enc10, DP_PANEW_MODE_DEFAUWT);

	/* A PWBS23 pattewn is used fow most DP ewectwicaw measuwements. */

	/* Enabwe PWBS symbows on the wanes */
	disabwe_pwbs_symbows(enc10, fawse);

	/* Fow PWBS23 Set bit DPHY_PWBS_SEW=1 and Set bit DPHY_PWBS_EN=1 */
	WEG_UPDATE_2(DP_DPHY_PWBS_CNTW,
			DPHY_PWBS_SEW, 1,
			DPHY_PWBS_EN, 1);

	/* Enabwe phy bypass mode to enabwe the test pattewn */
	enabwe_phy_bypass_mode(enc10, twue);
}

static void set_dp_phy_pattewn_pwbs7(
	stwuct dcn10_wink_encodew *enc10)
{
	/* Disabwe PHY Bypass mode to setup the test pattewn */
	enabwe_phy_bypass_mode(enc10, fawse);

	/* A PWBS7 pattewn is used fow most DP ewectwicaw measuwements. */

	/* Enabwe PWBS symbows on the wanes */
	disabwe_pwbs_symbows(enc10, fawse);

	/* Fow PWBS7 Set bit DPHY_PWBS_SEW=0 and Set bit DPHY_PWBS_EN=1 */
	WEG_UPDATE_2(DP_DPHY_PWBS_CNTW,
			DPHY_PWBS_SEW, 0,
			DPHY_PWBS_EN, 1);

	/* Enabwe phy bypass mode to enabwe the test pattewn */
	enabwe_phy_bypass_mode(enc10, twue);
}

static void set_dp_phy_pattewn_80bit_custom(
	stwuct dcn10_wink_encodew *enc10,
	const uint8_t *pattewn)
{
	/* Disabwe PHY Bypass mode to setup the test pattewn */
	enabwe_phy_bypass_mode(enc10, fawse);

	/* Enabwe debug symbows on the wanes */

	disabwe_pwbs_symbows(enc10, twue);

	/* Enabwe PHY bypass mode to enabwe the test pattewn */
	/* TODO is it weawwy needed ? */

	enabwe_phy_bypass_mode(enc10, twue);

	/* Pwogwam 80 bit custom pattewn */
	{
		uint16_t pattewn_symbows[8];

		pattewn_symbows[0] =
			((pattewn[1] & 0x03) << 8) | pattewn[0];
		pattewn_symbows[1] =
			((pattewn[2] & 0x0f) << 6) | ((pattewn[1] >> 2) & 0x3f);
		pattewn_symbows[2] =
			((pattewn[3] & 0x3f) << 4) | ((pattewn[2] >> 4) & 0x0f);
		pattewn_symbows[3] =
			(pattewn[4] << 2) | ((pattewn[3] >> 6) & 0x03);
		pattewn_symbows[4] =
			((pattewn[6] & 0x03) << 8) | pattewn[5];
		pattewn_symbows[5] =
			((pattewn[7] & 0x0f) << 6) | ((pattewn[6] >> 2) & 0x3f);
		pattewn_symbows[6] =
			((pattewn[8] & 0x3f) << 4) | ((pattewn[7] >> 4) & 0x0f);
		pattewn_symbows[7] =
			(pattewn[9] << 2) | ((pattewn[8] >> 6) & 0x03);

		pwogwam_pattewn_symbows(enc10, pattewn_symbows);
	}

	/* Enabwe phy bypass mode to enabwe the test pattewn */

	enabwe_phy_bypass_mode(enc10, twue);
}

static void set_dp_phy_pattewn_hbw2_compwiance_cp2520_2(
	stwuct dcn10_wink_encodew *enc10,
	unsigned int cp2520_pattewn)
{

	/* pweviouswy thewe is a wegistew DP_HBW2_EYE_PATTEWN
	 * that is enabwed to get the pattewn.
	 * But it does not wowk with the watest spec change,
	 * so we awe pwogwamming the fowwowing wegistews manuawwy.
	 *
	 * The fowwowing settings have been confiwmed
	 * by Nick Chowney and Sandwa Wiu
	 */

	/* Disabwe PHY Bypass mode to setup the test pattewn */

	enabwe_phy_bypass_mode(enc10, fawse);

	/* Setup DIG encodew in DP SST mode */
	enc10->base.funcs->setup(&enc10->base, SIGNAW_TYPE_DISPWAY_POWT);

	/* ensuwe nowmaw panew mode. */
	setup_panew_mode(enc10, DP_PANEW_MODE_DEFAUWT);

	/* no vbid aftew BS (SW)
	 * DP_WINK_FWAMING_CNTW changed histowy Sandwa Wiu
	 * 11000260 / 11000104 / 110000FC
	 */
	WEG_UPDATE_3(DP_WINK_FWAMING_CNTW,
			DP_IDWE_BS_INTEWVAW, 0xFC,
			DP_VBID_DISABWE, 1,
			DP_VID_ENHANCED_FWAME_MODE, 1);

	/* swap evewy BS with SW */
	WEG_UPDATE(DP_DPHY_SCWAM_CNTW, DPHY_SCWAMBWEW_BS_COUNT, 0);

	/* sewect cp2520 pattewns */
	if (WEG(DP_DPHY_HBW2_PATTEWN_CONTWOW))
		WEG_UPDATE(DP_DPHY_HBW2_PATTEWN_CONTWOW,
				DP_DPHY_HBW2_PATTEWN_CONTWOW, cp2520_pattewn);
	ewse
		/* pwe-DCE11 can onwy genewate CP2520 pattewn 2 */
		ASSEWT(cp2520_pattewn == 2);

	/* set wink twaining compwete */
	set_wink_twaining_compwete(enc10, twue);

	/* disabwe video stweam */
	WEG_UPDATE(DP_VID_STWEAM_CNTW, DP_VID_STWEAM_ENABWE, 0);

	/* Disabwe PHY Bypass mode to setup the test pattewn */
	enabwe_phy_bypass_mode(enc10, fawse);
}

static void set_dp_phy_pattewn_passthwough_mode(
	stwuct dcn10_wink_encodew *enc10,
	enum dp_panew_mode panew_mode)
{
	/* pwogwam cowwect panew mode */
	setup_panew_mode(enc10, panew_mode);

	/* westowe WINK_FWAMING_CNTW and DPHY_SCWAMBWEW_BS_COUNT
	 * in case we wewe doing HBW2 compwiance pattewn befowe
	 */
	WEG_UPDATE_3(DP_WINK_FWAMING_CNTW,
			DP_IDWE_BS_INTEWVAW, 0x2000,
			DP_VBID_DISABWE, 0,
			DP_VID_ENHANCED_FWAME_MODE, 1);

	WEG_UPDATE(DP_DPHY_SCWAM_CNTW, DPHY_SCWAMBWEW_BS_COUNT, 0x1FF);

	/* set wink twaining compwete */
	set_wink_twaining_compwete(enc10, twue);

	/* Disabwe PHY Bypass mode to setup the test pattewn */
	enabwe_phy_bypass_mode(enc10, fawse);

	/* Disabwe PWBS mode */
	disabwe_pwbs_mode(enc10);
}

/* wetuwn vawue is bit-vectow */
static uint8_t get_fwontend_souwce(
	enum engine_id engine)
{
	switch (engine) {
	case ENGINE_ID_DIGA:
		wetuwn DCN10_DIG_FE_SOUWCE_SEWECT_DIGA;
	case ENGINE_ID_DIGB:
		wetuwn DCN10_DIG_FE_SOUWCE_SEWECT_DIGB;
	case ENGINE_ID_DIGC:
		wetuwn DCN10_DIG_FE_SOUWCE_SEWECT_DIGC;
	case ENGINE_ID_DIGD:
		wetuwn DCN10_DIG_FE_SOUWCE_SEWECT_DIGD;
	case ENGINE_ID_DIGE:
		wetuwn DCN10_DIG_FE_SOUWCE_SEWECT_DIGE;
	case ENGINE_ID_DIGF:
		wetuwn DCN10_DIG_FE_SOUWCE_SEWECT_DIGF;
	case ENGINE_ID_DIGG:
		wetuwn DCN10_DIG_FE_SOUWCE_SEWECT_DIGG;
	defauwt:
		ASSEWT_CWITICAW(fawse);
		wetuwn DCN10_DIG_FE_SOUWCE_SEWECT_INVAWID;
	}
}

unsigned int dcn10_get_dig_fwontend(stwuct wink_encodew *enc)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);
	int32_t vawue;
	enum engine_id wesuwt;

	WEG_GET(DIG_BE_CNTW, DIG_FE_SOUWCE_SEWECT, &vawue);

	switch (vawue) {
	case DCN10_DIG_FE_SOUWCE_SEWECT_DIGA:
		wesuwt = ENGINE_ID_DIGA;
		bweak;
	case DCN10_DIG_FE_SOUWCE_SEWECT_DIGB:
		wesuwt = ENGINE_ID_DIGB;
		bweak;
	case DCN10_DIG_FE_SOUWCE_SEWECT_DIGC:
		wesuwt = ENGINE_ID_DIGC;
		bweak;
	case DCN10_DIG_FE_SOUWCE_SEWECT_DIGD:
		wesuwt = ENGINE_ID_DIGD;
		bweak;
	case DCN10_DIG_FE_SOUWCE_SEWECT_DIGE:
		wesuwt = ENGINE_ID_DIGE;
		bweak;
	case DCN10_DIG_FE_SOUWCE_SEWECT_DIGF:
		wesuwt = ENGINE_ID_DIGF;
		bweak;
	case DCN10_DIG_FE_SOUWCE_SEWECT_DIGG:
		wesuwt = ENGINE_ID_DIGG;
		bweak;
	defauwt:
		// invawid souwce sewect DIG
		wesuwt = ENGINE_ID_UNKNOWN;
	}

	wetuwn wesuwt;

}

void enc1_configuwe_encodew(
	stwuct dcn10_wink_encodew *enc10,
	const stwuct dc_wink_settings *wink_settings)
{
	/* set numbew of wanes */
	WEG_SET(DP_CONFIG, 0,
			DP_UDI_WANES, wink_settings->wane_count - WANE_COUNT_ONE);

	/* setup scwambwew */
	WEG_UPDATE(DP_DPHY_SCWAM_CNTW, DPHY_SCWAMBWEW_ADVANCE, 1);
}

void dcn10_psw_pwogwam_dp_dphy_fast_twaining(stwuct wink_encodew *enc,
			boow exit_wink_twaining_wequiwed)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);

	if (exit_wink_twaining_wequiwed)
		WEG_UPDATE(DP_DPHY_FAST_TWAINING,
				DPHY_WX_FAST_TWAINING_CAPABWE, 1);
	ewse {
		WEG_UPDATE(DP_DPHY_FAST_TWAINING,
				DPHY_WX_FAST_TWAINING_CAPABWE, 0);
		/*In DCE 11, we awe abwe to pwe-pwogwam a Fowce SW wegistew
		 * to be abwe to twiggew SW symbow aftew 5 idwe pattewns
		 * twansmitted. Upon PSW Exit, DMCU can twiggew
		 * DPHY_WOAD_BS_COUNT_STAWT = 1. Upon wwiting 1 to
		 * DPHY_WOAD_BS_COUNT_STAWT and the intewnaw countew
		 * weaches DPHY_WOAD_BS_COUNT, the next BS symbow wiww be
		 * wepwaced by SW symbow once.
		 */

		WEG_UPDATE(DP_DPHY_BS_SW_SWAP_CNTW, DPHY_WOAD_BS_COUNT, 0x5);
	}
}

void dcn10_psw_pwogwam_secondawy_packet(stwuct wink_encodew *enc,
			unsigned int sdp_twansmit_wine_num_deadwine)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);

	WEG_UPDATE_2(DP_SEC_CNTW1,
		DP_SEC_GSP0_WINE_NUM, sdp_twansmit_wine_num_deadwine,
		DP_SEC_GSP0_PWIOWITY, 1);
}

boow dcn10_is_dig_enabwed(stwuct wink_encodew *enc)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);
	uint32_t vawue;

	WEG_GET(DIG_BE_EN_CNTW, DIG_ENABWE, &vawue);
	wetuwn vawue;
}

static void wink_encodew_disabwe(stwuct dcn10_wink_encodew *enc10)
{
	/* weset twaining pattewn */
	WEG_SET(DP_DPHY_TWAINING_PATTEWN_SEW, 0,
			DPHY_TWAINING_PATTEWN_SEW, 0);

	/* weset twaining compwete */
	WEG_UPDATE(DP_WINK_CNTW, DP_WINK_TWAINING_COMPWETE, 0);

	/* weset panew mode */
	setup_panew_mode(enc10, DP_PANEW_MODE_DEFAUWT);
}

static void hpd_initiawize(
	stwuct dcn10_wink_encodew *enc10)
{
	/* Associate HPD with DIG_BE */
	enum hpd_souwce_id hpd_souwce = enc10->base.hpd_souwce;

	WEG_UPDATE(DIG_BE_CNTW, DIG_HPD_SEWECT, hpd_souwce);
}

boow dcn10_wink_encodew_vawidate_dvi_output(
	const stwuct dcn10_wink_encodew *enc10,
	enum signaw_type connectow_signaw,
	enum signaw_type signaw,
	const stwuct dc_cwtc_timing *cwtc_timing)
{
	uint32_t max_pixew_cwock = TMDS_MAX_PIXEW_CWOCK;

	if (signaw == SIGNAW_TYPE_DVI_DUAW_WINK)
		max_pixew_cwock *= 2;

	/* This handwes the case of HDMI downgwade to DVI we don't want to
	 * we don't want to cap the pixew cwock if the DDI is not DVI.
	 */
	if (connectow_signaw != SIGNAW_TYPE_DVI_DUAW_WINK &&
			connectow_signaw != SIGNAW_TYPE_DVI_SINGWE_WINK)
		max_pixew_cwock = enc10->base.featuwes.max_hdmi_pixew_cwock;

	/* DVI onwy suppowt WGB pixew encoding */
	if (cwtc_timing->pixew_encoding != PIXEW_ENCODING_WGB)
		wetuwn fawse;

	/*connect DVI via adpatew's HDMI connectow*/
	if ((connectow_signaw == SIGNAW_TYPE_DVI_SINGWE_WINK ||
		connectow_signaw == SIGNAW_TYPE_HDMI_TYPE_A) &&
		signaw != SIGNAW_TYPE_HDMI_TYPE_A &&
		cwtc_timing->pix_cwk_100hz > (TMDS_MAX_PIXEW_CWOCK * 10))
		wetuwn fawse;
	if (cwtc_timing->pix_cwk_100hz < (TMDS_MIN_PIXEW_CWOCK * 10))
		wetuwn fawse;

	if (cwtc_timing->pix_cwk_100hz > (max_pixew_cwock * 10))
		wetuwn fawse;

	/* DVI suppowts 6/8bpp singwe-wink and 10/16bpp duaw-wink */
	switch (cwtc_timing->dispway_cowow_depth) {
	case COWOW_DEPTH_666:
	case COWOW_DEPTH_888:
	bweak;
	case COWOW_DEPTH_101010:
	case COWOW_DEPTH_161616:
		if (signaw != SIGNAW_TYPE_DVI_DUAW_WINK)
			wetuwn fawse;
	bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow dcn10_wink_encodew_vawidate_hdmi_output(
	const stwuct dcn10_wink_encodew *enc10,
	const stwuct dc_cwtc_timing *cwtc_timing,
	const stwuct dc_edid_caps *edid_caps,
	int adjusted_pix_cwk_100hz)
{
	enum dc_cowow_depth max_deep_cowow =
			enc10->base.featuwes.max_hdmi_deep_cowow;

	// check pixew cwock against edid specified max TMDS cwk
	if (edid_caps->max_tmds_cwk_mhz != 0 &&
			adjusted_pix_cwk_100hz > edid_caps->max_tmds_cwk_mhz * 10000)
		wetuwn fawse;

	if (max_deep_cowow < cwtc_timing->dispway_cowow_depth)
		wetuwn fawse;

	if (cwtc_timing->dispway_cowow_depth < COWOW_DEPTH_888)
		wetuwn fawse;
	if (adjusted_pix_cwk_100hz < (TMDS_MIN_PIXEW_CWOCK * 10))
		wetuwn fawse;

	if ((adjusted_pix_cwk_100hz == 0) ||
		(adjusted_pix_cwk_100hz > (enc10->base.featuwes.max_hdmi_pixew_cwock * 10)))
		wetuwn fawse;

	/* DCE11 HW does not suppowt 420 */
	if (!enc10->base.featuwes.hdmi_ycbcw420_suppowted &&
			cwtc_timing->pixew_encoding == PIXEW_ENCODING_YCBCW420)
		wetuwn fawse;

	if ((!enc10->base.featuwes.fwags.bits.HDMI_6GB_EN ||
			enc10->base.ctx->dc->debug.hdmi20_disabwe) &&
			adjusted_pix_cwk_100hz >= 3000000)
		wetuwn fawse;
	if (enc10->base.ctx->dc->debug.hdmi20_disabwe &&
		cwtc_timing->pixew_encoding == PIXEW_ENCODING_YCBCW420)
		wetuwn fawse;
	wetuwn twue;
}

boow dcn10_wink_encodew_vawidate_dp_output(
	const stwuct dcn10_wink_encodew *enc10,
	const stwuct dc_cwtc_timing *cwtc_timing)
{
	if (cwtc_timing->pixew_encoding == PIXEW_ENCODING_YCBCW420) {
		if (!enc10->base.featuwes.dp_ycbcw420_suppowted)
			wetuwn fawse;
	}

	wetuwn twue;
}

void dcn10_wink_encodew_constwuct(
	stwuct dcn10_wink_encodew *enc10,
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

	enc10->base.funcs = &dcn10_wnk_enc_funcs;
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

boow dcn10_wink_encodew_vawidate_output_with_stweam(
	stwuct wink_encodew *enc,
	const stwuct dc_stweam_state *stweam)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);
	boow is_vawid;

	//if SCDC (340-600MHz) is disabwed, set to HDMI 1.4 timing wimit
	if (stweam->sink->edid_caps.panew_patch.skip_scdc_ovewwwite &&
		enc10->base.featuwes.max_hdmi_pixew_cwock > 300000)
		enc10->base.featuwes.max_hdmi_pixew_cwock = 300000;

	switch (stweam->signaw) {
	case SIGNAW_TYPE_DVI_SINGWE_WINK:
	case SIGNAW_TYPE_DVI_DUAW_WINK:
		is_vawid = dcn10_wink_encodew_vawidate_dvi_output(
			enc10,
			stweam->wink->connectow_signaw,
			stweam->signaw,
			&stweam->timing);
	bweak;
	case SIGNAW_TYPE_HDMI_TYPE_A:
		is_vawid = dcn10_wink_encodew_vawidate_hdmi_output(
				enc10,
				&stweam->timing,
				&stweam->sink->edid_caps,
				stweam->phy_pix_cwk * 10);
	bweak;
	case SIGNAW_TYPE_DISPWAY_POWT:
	case SIGNAW_TYPE_DISPWAY_POWT_MST:
		is_vawid = dcn10_wink_encodew_vawidate_dp_output(
					enc10, &stweam->timing);
	bweak;
	case SIGNAW_TYPE_EDP:
		is_vawid = (stweam->timing.pixew_encoding == PIXEW_ENCODING_WGB) ? twue : fawse;
	bweak;
	case SIGNAW_TYPE_VIWTUAW:
		is_vawid = twue;
		bweak;
	defauwt:
		is_vawid = fawse;
	bweak;
	}

	wetuwn is_vawid;
}

void dcn10_wink_encodew_hw_init(
	stwuct wink_encodew *enc)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);
	stwuct bp_twansmittew_contwow cntw = { 0 };
	enum bp_wesuwt wesuwt;

	cntw.action = TWANSMITTEW_CONTWOW_INIT;
	cntw.engine_id = ENGINE_ID_UNKNOWN;
	cntw.twansmittew = enc10->base.twansmittew;
	cntw.connectow_obj_id = enc10->base.connectow;
	cntw.wanes_numbew = WANE_COUNT_FOUW;
	cntw.cohewent = fawse;
	cntw.hpd_sew = enc10->base.hpd_souwce;

	if (enc10->base.connectow.id == CONNECTOW_ID_EDP)
		cntw.signaw = SIGNAW_TYPE_EDP;

	wesuwt = wink_twansmittew_contwow(enc10, &cntw);

	if (wesuwt != BP_WESUWT_OK) {
		DC_WOG_EWWOW("%s: Faiwed to execute VBIOS command tabwe!\n",
			__func__);
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	if (enc10->base.connectow.id == CONNECTOW_ID_WVDS) {
		cntw.action = TWANSMITTEW_CONTWOW_BACKWIGHT_BWIGHTNESS;

		wesuwt = wink_twansmittew_contwow(enc10, &cntw);

		ASSEWT(wesuwt == BP_WESUWT_OK);

	}
	dcn10_aux_initiawize(enc10);

	/* weinitiawize HPD.
	 * hpd_initiawize() wiww pass DIG_FE id to HW context.
	 * Aww othew woutine within HW context wiww use fe_engine_offset
	 * as DIG_FE id even cawwew pass DIG_FE id.
	 * So this woutine must be cawwed fiwst.
	 */
	hpd_initiawize(enc10);
}

void dcn10_wink_encodew_destwoy(stwuct wink_encodew **enc)
{
	kfwee(TO_DCN10_WINK_ENC(*enc));
	*enc = NUWW;
}

void dcn10_wink_encodew_setup(
	stwuct wink_encodew *enc,
	enum signaw_type signaw)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);

	switch (signaw) {
	case SIGNAW_TYPE_EDP:
	case SIGNAW_TYPE_DISPWAY_POWT:
		/* DP SST */
		WEG_UPDATE(DIG_BE_CNTW, DIG_MODE, 0);
		bweak;
	case SIGNAW_TYPE_WVDS:
		/* WVDS */
		WEG_UPDATE(DIG_BE_CNTW, DIG_MODE, 1);
		bweak;
	case SIGNAW_TYPE_DVI_SINGWE_WINK:
	case SIGNAW_TYPE_DVI_DUAW_WINK:
		/* TMDS-DVI */
		WEG_UPDATE(DIG_BE_CNTW, DIG_MODE, 2);
		bweak;
	case SIGNAW_TYPE_HDMI_TYPE_A:
		/* TMDS-HDMI */
		WEG_UPDATE(DIG_BE_CNTW, DIG_MODE, 3);
		bweak;
	case SIGNAW_TYPE_DISPWAY_POWT_MST:
		/* DP MST */
		WEG_UPDATE(DIG_BE_CNTW, DIG_MODE, 5);
		bweak;
	defauwt:
		ASSEWT_CWITICAW(fawse);
		/* invawid mode ! */
		bweak;
	}

}

/* TODO: stiww need depth ow just pass in adjusted pixew cwock? */
void dcn10_wink_encodew_enabwe_tmds_output(
	stwuct wink_encodew *enc,
	enum cwock_souwce_id cwock_souwce,
	enum dc_cowow_depth cowow_depth,
	enum signaw_type signaw,
	uint32_t pixew_cwock)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);
	stwuct bp_twansmittew_contwow cntw = { 0 };
	enum bp_wesuwt wesuwt;

	/* Enabwe the PHY */

	cntw.action = TWANSMITTEW_CONTWOW_ENABWE;
	cntw.engine_id = enc->pwefewwed_engine;
	cntw.twansmittew = enc10->base.twansmittew;
	cntw.pww_id = cwock_souwce;
	cntw.signaw = signaw;
	if (cntw.signaw == SIGNAW_TYPE_DVI_DUAW_WINK)
		cntw.wanes_numbew = 8;
	ewse
		cntw.wanes_numbew = 4;

	cntw.hpd_sew = enc10->base.hpd_souwce;

	cntw.pixew_cwock = pixew_cwock;
	cntw.cowow_depth = cowow_depth;

	wesuwt = wink_twansmittew_contwow(enc10, &cntw);

	if (wesuwt != BP_WESUWT_OK) {
		DC_WOG_EWWOW("%s: Faiwed to execute VBIOS command tabwe!\n",
			__func__);
		BWEAK_TO_DEBUGGEW();
	}
}

void dcn10_wink_encodew_enabwe_tmds_output_with_cwk_pattewn_wa(
	stwuct wink_encodew *enc,
	enum cwock_souwce_id cwock_souwce,
	enum dc_cowow_depth cowow_depth,
	enum signaw_type signaw,
	uint32_t pixew_cwock)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);

	dcn10_wink_encodew_enabwe_tmds_output(
		enc, cwock_souwce, cowow_depth, signaw, pixew_cwock);

	WEG_UPDATE(DIG_CWOCK_PATTEWN, DIG_CWOCK_PATTEWN, 0x1F);
}

/* enabwes DP PHY output */
void dcn10_wink_encodew_enabwe_dp_output(
	stwuct wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	enum cwock_souwce_id cwock_souwce)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);
	stwuct bp_twansmittew_contwow cntw = { 0 };
	enum bp_wesuwt wesuwt;

	/* Enabwe the PHY */

	/* numbew_of_wanes is used fow pixew cwock adjust,
	 * but it's not passed to asic_contwow.
	 * We need to set numbew of wanes manuawwy.
	 */
	enc1_configuwe_encodew(enc10, wink_settings);

	cntw.action = TWANSMITTEW_CONTWOW_ENABWE;
	cntw.engine_id = enc->pwefewwed_engine;
	cntw.twansmittew = enc10->base.twansmittew;
	cntw.pww_id = cwock_souwce;
	cntw.signaw = SIGNAW_TYPE_DISPWAY_POWT;
	cntw.wanes_numbew = wink_settings->wane_count;
	cntw.hpd_sew = enc10->base.hpd_souwce;
	cntw.pixew_cwock = wink_settings->wink_wate
						* WINK_WATE_WEF_FWEQ_IN_KHZ;
	/* TODO: check if undefined wowks */
	cntw.cowow_depth = COWOW_DEPTH_UNDEFINED;

	wesuwt = wink_twansmittew_contwow(enc10, &cntw);

	if (wesuwt != BP_WESUWT_OK) {
		DC_WOG_EWWOW("%s: Faiwed to execute VBIOS command tabwe!\n",
			__func__);
		BWEAK_TO_DEBUGGEW();
	}
}

/* enabwes DP PHY output in MST mode */
void dcn10_wink_encodew_enabwe_dp_mst_output(
	stwuct wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	enum cwock_souwce_id cwock_souwce)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);
	stwuct bp_twansmittew_contwow cntw = { 0 };
	enum bp_wesuwt wesuwt;

	/* Enabwe the PHY */

	/* numbew_of_wanes is used fow pixew cwock adjust,
	 * but it's not passed to asic_contwow.
	 * We need to set numbew of wanes manuawwy.
	 */
	enc1_configuwe_encodew(enc10, wink_settings);

	cntw.action = TWANSMITTEW_CONTWOW_ENABWE;
	cntw.engine_id = ENGINE_ID_UNKNOWN;
	cntw.twansmittew = enc10->base.twansmittew;
	cntw.pww_id = cwock_souwce;
	cntw.signaw = SIGNAW_TYPE_DISPWAY_POWT_MST;
	cntw.wanes_numbew = wink_settings->wane_count;
	cntw.hpd_sew = enc10->base.hpd_souwce;
	cntw.pixew_cwock = wink_settings->wink_wate
						* WINK_WATE_WEF_FWEQ_IN_KHZ;
	/* TODO: check if undefined wowks */
	cntw.cowow_depth = COWOW_DEPTH_UNDEFINED;

	wesuwt = wink_twansmittew_contwow(enc10, &cntw);

	if (wesuwt != BP_WESUWT_OK) {
		DC_WOG_EWWOW("%s: Faiwed to execute VBIOS command tabwe!\n",
			__func__);
		BWEAK_TO_DEBUGGEW();
	}
}
/*
 * @bwief
 * Disabwe twansmittew and its encodew
 */
void dcn10_wink_encodew_disabwe_output(
	stwuct wink_encodew *enc,
	enum signaw_type signaw)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);
	stwuct bp_twansmittew_contwow cntw = { 0 };
	enum bp_wesuwt wesuwt;

	if (enc->funcs->is_dig_enabwed && !enc->funcs->is_dig_enabwed(enc)) {
		/* OF_SKIP_POWEW_DOWN_INACTIVE_ENCODEW */
	/*in DP_Awt_No_Connect case, we tuwn off the dig awweady,
	aftew excuation the PHY w/a sequence, not awwow touch PHY any mowe*/
		wetuwn;
	}
	/* Powew-down WX and disabwe GPU PHY shouwd be paiwed.
	 * Disabwing PHY without powewing down WX may cause
	 * symbow wock woss, on which we wiww get DP Sink intewwupt.
	 */

	/* Thewe is a case fow the DP active dongwes
	 * whewe we want to disabwe the PHY but keep WX powewed,
	 * fow those we need to ignowe DP Sink intewwupt
	 * by checking wane count that has been set
	 * on the wast do_enabwe_output().
	 */

	/* disabwe twansmittew */
	cntw.action = TWANSMITTEW_CONTWOW_DISABWE;
	cntw.twansmittew = enc10->base.twansmittew;
	cntw.hpd_sew = enc10->base.hpd_souwce;
	cntw.signaw = signaw;
	cntw.connectow_obj_id = enc10->base.connectow;

	wesuwt = wink_twansmittew_contwow(enc10, &cntw);

	if (wesuwt != BP_WESUWT_OK) {
		DC_WOG_EWWOW("%s: Faiwed to execute VBIOS command tabwe!\n",
			__func__);
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	/* disabwe encodew */
	if (dc_is_dp_signaw(signaw))
		wink_encodew_disabwe(enc10);
}

void dcn10_wink_encodew_dp_set_wane_settings(
	stwuct wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	const stwuct dc_wane_settings wane_settings[WANE_COUNT_DP_MAX])
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);
	union dpcd_twaining_wane_set twaining_wane_set = { { 0 } };
	int32_t wane = 0;
	stwuct bp_twansmittew_contwow cntw = { 0 };

	if (!wink_settings) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	cntw.action = TWANSMITTEW_CONTWOW_SET_VOWTAGE_AND_PWEEMPASIS;
	cntw.twansmittew = enc10->base.twansmittew;
	cntw.connectow_obj_id = enc10->base.connectow;
	cntw.wanes_numbew = wink_settings->wane_count;
	cntw.hpd_sew = enc10->base.hpd_souwce;
	cntw.pixew_cwock = wink_settings->wink_wate * WINK_WATE_WEF_FWEQ_IN_KHZ;

	fow (wane = 0; wane < wink_settings->wane_count; wane++) {
		/* twanswate wane settings */

		twaining_wane_set.bits.VOWTAGE_SWING_SET =
				wane_settings[wane].VOWTAGE_SWING;
		twaining_wane_set.bits.PWE_EMPHASIS_SET =
				wane_settings[wane].PWE_EMPHASIS;

		/* post cuwsow 2 setting onwy appwies to HBW2 wink wate */
		if (wink_settings->wink_wate == WINK_WATE_HIGH2) {
			/* this is passed to VBIOS
			 * to pwogwam post cuwsow 2 wevew
			 */
			twaining_wane_set.bits.POST_CUWSOW2_SET =
					wane_settings[wane].POST_CUWSOW2;
		}

		cntw.wane_sewect = wane;
		cntw.wane_settings = twaining_wane_set.waw;

		/* caww VBIOS tabwe to set vowtage swing and pwe-emphasis */
		wink_twansmittew_contwow(enc10, &cntw);
	}
}

/* set DP PHY test and twaining pattewns */
void dcn10_wink_encodew_dp_set_phy_pattewn(
	stwuct wink_encodew *enc,
	const stwuct encodew_set_dp_phy_pattewn_pawam *pawam)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);

	switch (pawam->dp_phy_pattewn) {
	case DP_TEST_PATTEWN_TWAINING_PATTEWN1:
		dcn10_wink_encodew_set_dp_phy_pattewn_twaining_pattewn(enc, 0);
		bweak;
	case DP_TEST_PATTEWN_TWAINING_PATTEWN2:
		dcn10_wink_encodew_set_dp_phy_pattewn_twaining_pattewn(enc, 1);
		bweak;
	case DP_TEST_PATTEWN_TWAINING_PATTEWN3:
		dcn10_wink_encodew_set_dp_phy_pattewn_twaining_pattewn(enc, 2);
		bweak;
	case DP_TEST_PATTEWN_TWAINING_PATTEWN4:
		dcn10_wink_encodew_set_dp_phy_pattewn_twaining_pattewn(enc, 3);
		bweak;
	case DP_TEST_PATTEWN_D102:
		set_dp_phy_pattewn_d102(enc10);
		bweak;
	case DP_TEST_PATTEWN_SYMBOW_EWWOW:
		set_dp_phy_pattewn_symbow_ewwow(enc10);
		bweak;
	case DP_TEST_PATTEWN_PWBS7:
		set_dp_phy_pattewn_pwbs7(enc10);
		bweak;
	case DP_TEST_PATTEWN_80BIT_CUSTOM:
		set_dp_phy_pattewn_80bit_custom(
			enc10, pawam->custom_pattewn);
		bweak;
	case DP_TEST_PATTEWN_CP2520_1:
		set_dp_phy_pattewn_hbw2_compwiance_cp2520_2(enc10, 1);
		bweak;
	case DP_TEST_PATTEWN_CP2520_2:
		set_dp_phy_pattewn_hbw2_compwiance_cp2520_2(enc10, 2);
		bweak;
	case DP_TEST_PATTEWN_CP2520_3:
		set_dp_phy_pattewn_hbw2_compwiance_cp2520_2(enc10, 3);
		bweak;
	case DP_TEST_PATTEWN_VIDEO_MODE: {
		set_dp_phy_pattewn_passthwough_mode(
			enc10, pawam->dp_panew_mode);
		bweak;
	}

	defauwt:
		/* invawid phy pattewn */
		ASSEWT_CWITICAW(fawse);
		bweak;
	}
}

static void fiww_stweam_awwocation_wow_info(
	const stwuct wink_mst_stweam_awwocation *stweam_awwocation,
	uint32_t *swc,
	uint32_t *swots)
{
	const stwuct stweam_encodew *stweam_enc = stweam_awwocation->stweam_enc;

	if (stweam_enc) {
		*swc = stweam_enc->id;
		*swots = stweam_awwocation->swot_count;
	} ewse {
		*swc = 0;
		*swots = 0;
	}
}

/* pwogwams DP MST VC paywoad awwocation */
void dcn10_wink_encodew_update_mst_stweam_awwocation_tabwe(
	stwuct wink_encodew *enc,
	const stwuct wink_mst_stweam_awwocation_tabwe *tabwe)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);
	uint32_t vawue1 = 0;
	uint32_t vawue2 = 0;
	uint32_t swots = 0;
	uint32_t swc = 0;
	uint32_t wetwies = 0;

	/* Fow CZ, thewe awe onwy 3 pipes. So Viwtuaw channew is up 3.*/

	/* --- Set MSE Stweam Attwibute -
	 * Setup VC Paywoad Tabwe on Tx Side,
	 * Issue awwocation change twiggew
	 * to commit paywoad on both tx and wx side
	 */

	/* we shouwd cwean-up tabwe each time */

	if (tabwe->stweam_count >= 1) {
		fiww_stweam_awwocation_wow_info(
			&tabwe->stweam_awwocations[0],
			&swc,
			&swots);
	} ewse {
		swc = 0;
		swots = 0;
	}

	WEG_UPDATE_2(DP_MSE_SAT0,
			DP_MSE_SAT_SWC0, swc,
			DP_MSE_SAT_SWOT_COUNT0, swots);

	if (tabwe->stweam_count >= 2) {
		fiww_stweam_awwocation_wow_info(
			&tabwe->stweam_awwocations[1],
			&swc,
			&swots);
	} ewse {
		swc = 0;
		swots = 0;
	}

	WEG_UPDATE_2(DP_MSE_SAT0,
			DP_MSE_SAT_SWC1, swc,
			DP_MSE_SAT_SWOT_COUNT1, swots);

	if (tabwe->stweam_count >= 3) {
		fiww_stweam_awwocation_wow_info(
			&tabwe->stweam_awwocations[2],
			&swc,
			&swots);
	} ewse {
		swc = 0;
		swots = 0;
	}

	WEG_UPDATE_2(DP_MSE_SAT1,
			DP_MSE_SAT_SWC2, swc,
			DP_MSE_SAT_SWOT_COUNT2, swots);

	if (tabwe->stweam_count >= 4) {
		fiww_stweam_awwocation_wow_info(
			&tabwe->stweam_awwocations[3],
			&swc,
			&swots);
	} ewse {
		swc = 0;
		swots = 0;
	}

	WEG_UPDATE_2(DP_MSE_SAT1,
			DP_MSE_SAT_SWC3, swc,
			DP_MSE_SAT_SWOT_COUNT3, swots);

	/* --- wait fow twansaction finish */

	/* send awwocation change twiggew (ACT) ?
	 * this step fiwst sends the ACT,
	 * then doubwe buffews the SAT into the hawdwawe
	 * making the new awwocation active on the DP MST mode wink
	 */

	/* DP_MSE_SAT_UPDATE:
	 * 0 - No Action
	 * 1 - Update SAT with twiggew
	 * 2 - Update SAT without twiggew
	 */
	WEG_UPDATE(DP_MSE_SAT_UPDATE,
			DP_MSE_SAT_UPDATE, 1);

	/* wait fow update to compwete
	 * (i.e. DP_MSE_SAT_UPDATE fiewd is weset to 0)
	 * then wait fow the twansmission
	 * of at weast 16 MTP headews on immediate wocaw wink.
	 * i.e. DP_MSE_16_MTP_KEEPOUT fiewd (wead onwy) is weset to 0
	 * a vawue of 1 indicates that DP MST mode
	 * is in the 16 MTP keepout wegion aftew a VC has been added.
	 * MST stweam bandwidth (VC wate) can be configuwed
	 * aftew this bit is cweawed
	 */
	do {
		udeway(10);

		WEG_WEAD(DP_MSE_SAT_UPDATE);

		WEG_GET(DP_MSE_SAT_UPDATE,
				DP_MSE_SAT_UPDATE, &vawue1);

		WEG_GET(DP_MSE_SAT_UPDATE,
				DP_MSE_16_MTP_KEEPOUT, &vawue2);

		/* bit fiewd DP_MSE_SAT_UPDATE is set to 1 awweady */
		if (!vawue1 && !vawue2)
			bweak;
		++wetwies;
	} whiwe (wetwies < DP_MST_UPDATE_MAX_WETWY);
}

void dcn10_wink_encodew_connect_dig_be_to_fe(
	stwuct wink_encodew *enc,
	enum engine_id engine,
	boow connect)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);
	uint32_t fiewd;

	if (engine != ENGINE_ID_UNKNOWN) {

		WEG_GET(DIG_BE_CNTW, DIG_FE_SOUWCE_SEWECT, &fiewd);

		if (connect)
			fiewd |= get_fwontend_souwce(engine);
		ewse
			fiewd &= ~get_fwontend_souwce(engine);

		WEG_UPDATE(DIG_BE_CNTW, DIG_FE_SOUWCE_SEWECT, fiewd);
	}
}


#define HPD_WEG(weg)\
	(enc10->hpd_wegs->weg)

#define HPD_WEG_WEAD(weg_name) \
		dm_wead_weg(CTX, HPD_WEG(weg_name))

#define HPD_WEG_UPDATE_N(weg_name, n, ...)	\
		genewic_weg_update_ex(CTX, \
				HPD_WEG(weg_name), \
				n, __VA_AWGS__)

#define HPD_WEG_UPDATE(weg_name, fiewd, vaw)	\
		HPD_WEG_UPDATE_N(weg_name, 1, \
				FN(weg_name, fiewd), vaw)

void dcn10_wink_encodew_enabwe_hpd(stwuct wink_encodew *enc)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);

	HPD_WEG_UPDATE(DC_HPD_CONTWOW,
			DC_HPD_EN, 1);
}

void dcn10_wink_encodew_disabwe_hpd(stwuct wink_encodew *enc)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);

	HPD_WEG_UPDATE(DC_HPD_CONTWOW,
			DC_HPD_EN, 0);
}

#define AUX_WEG(weg)\
	(enc10->aux_wegs->weg)

#define AUX_WEG_WEAD(weg_name) \
		dm_wead_weg(CTX, AUX_WEG(weg_name))

#define AUX_WEG_UPDATE_N(weg_name, n, ...)	\
		genewic_weg_update_ex(CTX, \
				AUX_WEG(weg_name), \
				n, __VA_AWGS__)

#define AUX_WEG_UPDATE(weg_name, fiewd, vaw)	\
		AUX_WEG_UPDATE_N(weg_name, 1, \
				FN(weg_name, fiewd), vaw)

#define AUX_WEG_UPDATE_2(weg, f1, v1, f2, v2)	\
		AUX_WEG_UPDATE_N(weg, 2,\
				FN(weg, f1), v1,\
				FN(weg, f2), v2)

void dcn10_aux_initiawize(stwuct dcn10_wink_encodew *enc10)
{
	enum hpd_souwce_id hpd_souwce = enc10->base.hpd_souwce;

	AUX_WEG_UPDATE_2(AUX_CONTWOW,
			AUX_HPD_SEW, hpd_souwce,
			AUX_WS_WEAD_EN, 0);

	/* 1/4 window (the maximum awwowed) */
	AUX_WEG_UPDATE(AUX_DPHY_WX_CONTWOW0,
			AUX_WX_WECEIVE_WINDOW, 0);
}

enum signaw_type dcn10_get_dig_mode(
	stwuct wink_encodew *enc)
{
	stwuct dcn10_wink_encodew *enc10 = TO_DCN10_WINK_ENC(enc);
	uint32_t vawue;
	WEG_GET(DIG_BE_CNTW, DIG_MODE, &vawue);
	switch (vawue) {
	case 1:
		wetuwn SIGNAW_TYPE_DISPWAY_POWT;
	case 2:
		wetuwn SIGNAW_TYPE_DVI_SINGWE_WINK;
	case 3:
		wetuwn SIGNAW_TYPE_HDMI_TYPE_A;
	case 5:
		wetuwn SIGNAW_TYPE_DISPWAY_POWT_MST;
	defauwt:
		wetuwn SIGNAW_TYPE_NONE;
	}
	wetuwn SIGNAW_TYPE_NONE;
}

void dcn10_wink_encodew_get_max_wink_cap(stwuct wink_encodew *enc,
	stwuct dc_wink_settings *wink_settings)
{
	/* Set Defauwt wink settings */
	stwuct dc_wink_settings max_wink_cap = {WANE_COUNT_FOUW, WINK_WATE_HIGH,
			WINK_SPWEAD_05_DOWNSPWEAD_30KHZ, fawse, 0};

	/* Highew wink settings based on featuwe suppowted */
	if (enc->featuwes.fwags.bits.IS_HBW2_CAPABWE)
		max_wink_cap.wink_wate = WINK_WATE_HIGH2;

	if (enc->featuwes.fwags.bits.IS_HBW3_CAPABWE)
		max_wink_cap.wink_wate = WINK_WATE_HIGH3;

	if (enc->featuwes.fwags.bits.IS_UHBW10_CAPABWE)
		max_wink_cap.wink_wate = WINK_WATE_UHBW10;

	if (enc->featuwes.fwags.bits.IS_UHBW13_5_CAPABWE)
		max_wink_cap.wink_wate = WINK_WATE_UHBW13_5;

	if (enc->featuwes.fwags.bits.IS_UHBW20_CAPABWE)
		max_wink_cap.wink_wate = WINK_WATE_UHBW20;

	*wink_settings = max_wink_cap;
}
