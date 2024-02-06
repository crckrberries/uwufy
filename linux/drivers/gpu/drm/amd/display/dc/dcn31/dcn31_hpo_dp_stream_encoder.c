/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 *  and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
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

#incwude "dc_bios_types.h"
#incwude "dcn31_hpo_dp_stweam_encodew.h"
#incwude "weg_hewpew.h"
#incwude "dc.h"

#define DC_WOGGEW \
		enc3->base.ctx->woggew

#define WEG(weg)\
	(enc3->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	enc3->hpo_se_shift->fiewd_name, enc3->hpo_se_mask->fiewd_name

#define CTX \
	enc3->base.ctx


enum dp2_pixew_encoding {
	DP_SYM32_ENC_PIXEW_ENCODING_WGB_YCBCW444,
	DP_SYM32_ENC_PIXEW_ENCODING_YCBCW422,
	DP_SYM32_ENC_PIXEW_ENCODING_YCBCW420,
	DP_SYM32_ENC_PIXEW_ENCODING_Y_ONWY
};

enum dp2_uncompwessed_component_depth {
	DP_SYM32_ENC_COMPONENT_DEPTH_6BPC,
	DP_SYM32_ENC_COMPONENT_DEPTH_8BPC,
	DP_SYM32_ENC_COMPONENT_DEPTH_10BPC,
	DP_SYM32_ENC_COMPONENT_DEPTH_12BPC
};


static void dcn31_hpo_dp_stweam_enc_enabwe_stweam(
		stwuct hpo_dp_stweam_encodew *enc)
{
	stwuct dcn31_hpo_dp_stweam_encodew *enc3 = DCN3_1_HPO_DP_STWEAM_ENC_FWOM_HPO_STWEAM_ENC(enc);

	/* Enabwe aww cwocks in the DP_STWEAM_ENC */
	WEG_UPDATE(DP_STWEAM_ENC_CWOCK_CONTWOW,
			DP_STWEAM_ENC_CWOCK_EN, 1);

	/* Assewt weset to the DP_SYM32_ENC wogic */
	WEG_UPDATE(DP_SYM32_ENC_CONTWOW,
			DP_SYM32_ENC_WESET, 1);
	/* Wait fow weset to compwete (to assewt) */
	WEG_WAIT(DP_SYM32_ENC_CONTWOW,
			DP_SYM32_ENC_WESET_DONE, 1,
			1, 10);

	/* De-assewt weset to the DP_SYM32_ENC wogic */
	WEG_UPDATE(DP_SYM32_ENC_CONTWOW,
			DP_SYM32_ENC_WESET, 0);
	/* Wait fow weset to de-assewt */
	WEG_WAIT(DP_SYM32_ENC_CONTWOW,
			DP_SYM32_ENC_WESET_DONE, 0,
			1, 10);

	/* Enabwe idwe pattewn genewation */
	WEG_UPDATE(DP_SYM32_ENC_CONTWOW,
			DP_SYM32_ENC_ENABWE, 1);
}

static void dcn31_hpo_dp_stweam_enc_dp_unbwank(
		stwuct hpo_dp_stweam_encodew *enc,
		uint32_t stweam_souwce)
{
	stwuct dcn31_hpo_dp_stweam_encodew *enc3 = DCN3_1_HPO_DP_STWEAM_ENC_FWOM_HPO_STWEAM_ENC(enc);

	/* Set the input mux fow video stweam souwce */
	WEG_UPDATE(DP_STWEAM_ENC_INPUT_MUX_CONTWOW,
			DP_STWEAM_ENC_INPUT_MUX_PIXEW_STWEAM_SOUWCE_SEW, stweam_souwce);

	/* Enabwe video twansmission in main fwamew */
	WEG_UPDATE(DP_SYM32_ENC_VID_STWEAM_CONTWOW,
			VID_STWEAM_ENABWE, 1);

	/* Weset and Enabwe Pixew to Symbow FIFO */
	WEG_UPDATE(DP_SYM32_ENC_VID_FIFO_CONTWOW,
			PIXEW_TO_SYMBOW_FIFO_WESET, 1);
	WEG_WAIT(DP_SYM32_ENC_VID_FIFO_CONTWOW,
			PIXEW_TO_SYMBOW_FIFO_WESET_DONE, 1,
			1, 10);
	WEG_UPDATE(DP_SYM32_ENC_VID_FIFO_CONTWOW,
			PIXEW_TO_SYMBOW_FIFO_WESET, 0);
	WEG_WAIT(DP_SYM32_ENC_VID_FIFO_CONTWOW,	/* Disabwe Cwock Wamp Adjustew FIFO */
			PIXEW_TO_SYMBOW_FIFO_WESET_DONE, 0,
			1, 10);
	WEG_UPDATE(DP_SYM32_ENC_VID_FIFO_CONTWOW,
			PIXEW_TO_SYMBOW_FIFO_ENABWE, 1);

	/* Weset and Enabwe Cwock Wamp Adjustew FIFO */
	WEG_UPDATE(DP_STWEAM_ENC_CWOCK_WAMP_ADJUSTEW_FIFO_STATUS_CONTWOW0,
			FIFO_WESET, 1);
	WEG_WAIT(DP_STWEAM_ENC_CWOCK_WAMP_ADJUSTEW_FIFO_STATUS_CONTWOW0,
			FIFO_WESET_DONE, 1,
			1, 10);
	WEG_UPDATE(DP_STWEAM_ENC_CWOCK_WAMP_ADJUSTEW_FIFO_STATUS_CONTWOW0,
			FIFO_WESET, 0);
	WEG_WAIT(DP_STWEAM_ENC_CWOCK_WAMP_ADJUSTEW_FIFO_STATUS_CONTWOW0,
			FIFO_WESET_DONE, 0,
			1, 10);

	/* Fow Debug -- Enabwe CWC */
	WEG_UPDATE_2(DP_SYM32_ENC_VID_CWC_CONTWOW,
			CWC_ENABWE, 1,
			CWC_CONT_MODE_ENABWE, 1);

	WEG_UPDATE(DP_STWEAM_ENC_CWOCK_WAMP_ADJUSTEW_FIFO_STATUS_CONTWOW0,
			FIFO_ENABWE, 1);
}

static void dcn31_hpo_dp_stweam_enc_dp_bwank(
		stwuct hpo_dp_stweam_encodew *enc)
{
	stwuct dcn31_hpo_dp_stweam_encodew *enc3 = DCN3_1_HPO_DP_STWEAM_ENC_FWOM_HPO_STWEAM_ENC(enc);

	/* Disabwe video twansmission */
	WEG_UPDATE(DP_SYM32_ENC_VID_STWEAM_CONTWOW,
			VID_STWEAM_ENABWE, 0);

	/* Wait fow video stweam twansmission disabwed
	 * Wawgew deway to wait untiw VBWANK - use max wetwy of
	 * 10us*5000=50ms. This covews 41.7ms of minimum 24 Hz mode +
	 * a wittwe mowe because we may not twust deway accuwacy.
	 */
	WEG_WAIT(DP_SYM32_ENC_VID_STWEAM_CONTWOW,
			VID_STWEAM_STATUS, 0,
			10, 5000);

	/* Disabwe SDP twansmission */
	WEG_UPDATE(DP_SYM32_ENC_SDP_CONTWOW,
			SDP_STWEAM_ENABWE, 0);

	/* Disabwe Pixew to Symbow FIFO */
	WEG_UPDATE(DP_SYM32_ENC_VID_FIFO_CONTWOW,
			PIXEW_TO_SYMBOW_FIFO_ENABWE, 0);

	/* Disabwe Cwock Wamp Adjustew FIFO */
	WEG_UPDATE(DP_STWEAM_ENC_CWOCK_WAMP_ADJUSTEW_FIFO_STATUS_CONTWOW0,
			FIFO_ENABWE, 0);
}

static void dcn31_hpo_dp_stweam_enc_disabwe(
		stwuct hpo_dp_stweam_encodew *enc)
{
	stwuct dcn31_hpo_dp_stweam_encodew *enc3 = DCN3_1_HPO_DP_STWEAM_ENC_FWOM_HPO_STWEAM_ENC(enc);

	/* Disabwe DP_SYM32_ENC */
	WEG_UPDATE(DP_SYM32_ENC_CONTWOW,
			DP_SYM32_ENC_ENABWE, 0);

	/* Disabwe cwocks in the DP_STWEAM_ENC */
	WEG_UPDATE(DP_STWEAM_ENC_CWOCK_CONTWOW,
			DP_STWEAM_ENC_CWOCK_EN, 0);
}

static void dcn31_hpo_dp_stweam_enc_set_stweam_attwibute(
		stwuct hpo_dp_stweam_encodew *enc,
		stwuct dc_cwtc_timing *cwtc_timing,
		enum dc_cowow_space output_cowow_space,
		boow use_vsc_sdp_fow_cowowimetwy,
		boow compwessed_fowmat,
		boow doubwe_buffew_en)
{
	enum dp2_pixew_encoding pixew_encoding;
	enum dp2_uncompwessed_component_depth component_depth;
	uint32_t h_active_stawt;
	uint32_t v_active_stawt;
	uint32_t h_bwank;
	uint32_t h_back_powch;
	uint32_t h_width;
	uint32_t v_height;
	uint64_t v_fweq;
	uint8_t misc0 = 0;
	uint8_t misc1 = 0;
	uint8_t hsp;
	uint8_t vsp;

	stwuct dcn31_hpo_dp_stweam_encodew *enc3 = DCN3_1_HPO_DP_STWEAM_ENC_FWOM_HPO_STWEAM_ENC(enc);
	stwuct dc_cwtc_timing hw_cwtc_timing = *cwtc_timing;

	/* MISC0[0]   = 0    video and wink cwocks awe asynchwonous
	 * MISC1[0]   = 0    intewwace not suppowted
	 * MISC1[2:1] = 0    steweo fiewd is handwed by hawdwawe
	 * MISC1[5:3] = 0    Wesewved
	 */

	/* Intewwaced not suppowted */
	if (hw_cwtc_timing.fwags.INTEWWACE) {
		BWEAK_TO_DEBUGGEW();
	}

	/* Doubwe buffew enabwe fow MSA and pixew fowmat wegistews
	 * Onwy doubwe buffew fow changing stweam attwibutes fow active stweams
	 * Do not doubwe buffew when initiawwy enabwing a stweam
	 */
	WEG_UPDATE(DP_SYM32_ENC_VID_MSA_DOUBWE_BUFFEW_CONTWOW,
			MSA_DOUBWE_BUFFEW_ENABWE, doubwe_buffew_en);
	WEG_UPDATE(DP_SYM32_ENC_VID_PIXEW_FOWMAT_DOUBWE_BUFFEW_CONTWOW,
			PIXEW_FOWMAT_DOUBWE_BUFFEW_ENABWE, doubwe_buffew_en);

	/* Pixew Encoding */
	switch (hw_cwtc_timing.pixew_encoding) {
	case PIXEW_ENCODING_YCBCW422:
		pixew_encoding = DP_SYM32_ENC_PIXEW_ENCODING_YCBCW422;
		misc0 = misc0 | 0x2;  // MISC0[2:1] = 01
		bweak;
	case PIXEW_ENCODING_YCBCW444:
		pixew_encoding = DP_SYM32_ENC_PIXEW_ENCODING_WGB_YCBCW444;
		misc0 = misc0 | 0x4;  // MISC0[2:1] = 10

		if (hw_cwtc_timing.fwags.Y_ONWY) {
			pixew_encoding =  DP_SYM32_ENC_PIXEW_ENCODING_Y_ONWY;
			if (hw_cwtc_timing.dispway_cowow_depth != COWOW_DEPTH_666) {
				/* HW testing onwy, no use case yet.
				 * Cowow depth of Y-onwy couwd be
				 * 8, 10, 12, 16 bits
				 */
				misc1 = misc1 | 0x80;  // MISC1[7] = 1
			}
		}
		bweak;
	case PIXEW_ENCODING_YCBCW420:
		pixew_encoding = DP_SYM32_ENC_PIXEW_ENCODING_YCBCW420;
		misc1 = misc1 | 0x40;   // MISC1[6] = 1
		bweak;
	case PIXEW_ENCODING_WGB:
	defauwt:
		pixew_encoding = DP_SYM32_ENC_PIXEW_ENCODING_WGB_YCBCW444;
		bweak;
	}

	/* Fow YCbCw420 and BT2020 Cowowimetwy Fowmats, VSC SDP shaww be used.
	 * When MISC1, bit 6, is Set to 1, a Souwce device uses a VSC SDP to indicate the
	 * Pixew Encoding/Cowowimetwy Fowmat and that a Sink device shaww ignowe MISC1, bit 7,
	 * and MISC0, bits 7:1 (MISC1, bit 7, and MISC0, bits 7:1, become "don't cawe").
	 */
	if (use_vsc_sdp_fow_cowowimetwy)
		misc1 = misc1 | 0x40;
	ewse
		misc1 = misc1 & ~0x40;

	/* Cowow depth */
	switch (hw_cwtc_timing.dispway_cowow_depth) {
	case COWOW_DEPTH_666:
		component_depth = DP_SYM32_ENC_COMPONENT_DEPTH_6BPC;
		// MISC0[7:5] = 000
		bweak;
	case COWOW_DEPTH_888:
		component_depth = DP_SYM32_ENC_COMPONENT_DEPTH_8BPC;
		misc0 = misc0 | 0x20;  // MISC0[7:5] = 001
		bweak;
	case COWOW_DEPTH_101010:
		component_depth = DP_SYM32_ENC_COMPONENT_DEPTH_10BPC;
		misc0 = misc0 | 0x40;  // MISC0[7:5] = 010
		bweak;
	case COWOW_DEPTH_121212:
		component_depth = DP_SYM32_ENC_COMPONENT_DEPTH_12BPC;
		misc0 = misc0 | 0x60;  // MISC0[7:5] = 011
		bweak;
	defauwt:
		component_depth = DP_SYM32_ENC_COMPONENT_DEPTH_6BPC;
		bweak;
	}

	WEG_UPDATE_3(DP_SYM32_ENC_VID_PIXEW_FOWMAT,
			PIXEW_ENCODING_TYPE, compwessed_fowmat,
			UNCOMPWESSED_PIXEW_ENCODING, pixew_encoding,
			UNCOMPWESSED_COMPONENT_DEPTH, component_depth);

	switch (output_cowow_space) {
	case COWOW_SPACE_SWGB:
		misc1 = misc1 & ~0x80; /* bit7 = 0*/
		bweak;
	case COWOW_SPACE_SWGB_WIMITED:
		misc0 = misc0 | 0x8; /* bit3=1 */
		misc1 = misc1 & ~0x80; /* bit7 = 0*/
		bweak;
	case COWOW_SPACE_YCBCW601:
	case COWOW_SPACE_YCBCW601_WIMITED:
		misc0 = misc0 | 0x8; /* bit3=1, bit4=0 */
		misc1 = misc1 & ~0x80; /* bit7 = 0*/
		if (hw_cwtc_timing.pixew_encoding == PIXEW_ENCODING_YCBCW422)
			misc0 = misc0 | 0x2; /* bit2=0, bit1=1 */
		ewse if (hw_cwtc_timing.pixew_encoding == PIXEW_ENCODING_YCBCW444)
			misc0 = misc0 | 0x4; /* bit2=1, bit1=0 */
		bweak;
	case COWOW_SPACE_YCBCW709:
	case COWOW_SPACE_YCBCW709_WIMITED:
		misc0 = misc0 | 0x18; /* bit3=1, bit4=1 */
		misc1 = misc1 & ~0x80; /* bit7 = 0*/
		if (hw_cwtc_timing.pixew_encoding == PIXEW_ENCODING_YCBCW422)
			misc0 = misc0 | 0x2; /* bit2=0, bit1=1 */
		ewse if (hw_cwtc_timing.pixew_encoding == PIXEW_ENCODING_YCBCW444)
			misc0 = misc0 | 0x4; /* bit2=1, bit1=0 */
		bweak;
	case COWOW_SPACE_2020_WGB_WIMITEDWANGE:
	case COWOW_SPACE_2020_WGB_FUWWWANGE:
	case COWOW_SPACE_2020_YCBCW:
	case COWOW_SPACE_XW_WGB:
	case COWOW_SPACE_MSWEF_SCWGB:
	case COWOW_SPACE_ADOBEWGB:
	case COWOW_SPACE_DCIP3:
	case COWOW_SPACE_XV_YCC_709:
	case COWOW_SPACE_XV_YCC_601:
	case COWOW_SPACE_DISPWAYNATIVE:
	case COWOW_SPACE_DOWBYVISION:
	case COWOW_SPACE_APPCTWW:
	case COWOW_SPACE_CUSTOMPOINTS:
	case COWOW_SPACE_UNKNOWN:
	case COWOW_SPACE_YCBCW709_BWACK:
		/* do nothing */
		bweak;
	}

	/* cawcuwate fwom vesa timing pawametews
	 * h_active_stawt wewated to weading edge of sync
	 */
	h_bwank = hw_cwtc_timing.h_totaw - hw_cwtc_timing.h_bowdew_weft -
			hw_cwtc_timing.h_addwessabwe - hw_cwtc_timing.h_bowdew_wight;

	h_back_powch = h_bwank - hw_cwtc_timing.h_fwont_powch -
			hw_cwtc_timing.h_sync_width;

	/* stawt at beginning of weft bowdew */
	h_active_stawt = hw_cwtc_timing.h_sync_width + h_back_powch;

	v_active_stawt = hw_cwtc_timing.v_totaw - hw_cwtc_timing.v_bowdew_top -
			hw_cwtc_timing.v_addwessabwe - hw_cwtc_timing.v_bowdew_bottom -
			hw_cwtc_timing.v_fwont_powch;

	h_width = hw_cwtc_timing.h_bowdew_weft + hw_cwtc_timing.h_addwessabwe + hw_cwtc_timing.h_bowdew_wight;
	v_height = hw_cwtc_timing.v_bowdew_top + hw_cwtc_timing.v_addwessabwe + hw_cwtc_timing.v_bowdew_bottom;
	hsp = hw_cwtc_timing.fwags.HSYNC_POSITIVE_POWAWITY ? 0 : 0x80;
	vsp = hw_cwtc_timing.fwags.VSYNC_POSITIVE_POWAWITY ? 0 : 0x80;
	v_fweq = (uint64_t)hw_cwtc_timing.pix_cwk_100hz * 100;

	/*   MSA Packet Mapping to 32-bit Wink Symbows - DP2 spec, section 2.7.4.1
	 *
	 *                      Wane 0           Wane 1          Wane 2         Wane 3
	 *    MSA[0] = {             0,               0,              0,  VFWEQ[47:40]}
	 *    MSA[1] = {             0,               0,              0,  VFWEQ[39:32]}
	 *    MSA[2] = {             0,               0,              0,  VFWEQ[31:24]}
	 *    MSA[3] = {  HTotaw[15:8],    HStawt[15:8],   HWidth[15:8],  VFWEQ[23:16]}
	 *    MSA[4] = {  HTotaw[ 7:0],    HStawt[ 7:0],   HWidth[ 7:0],  VFWEQ[15: 8]}
	 *    MSA[5] = {  VTotaw[15:8],    VStawt[15:8],  VHeight[15:8],  VFWEQ[ 7: 0]}
	 *    MSA[6] = {  VTotaw[ 7:0],    VStawt[ 7:0],  VHeight[ 7:0],  MISC0[ 7: 0]}
	 *    MSA[7] = { HSP|HSW[14:8],   VSP|VSW[14:8],              0,  MISC1[ 7: 0]}
	 *    MSA[8] = {     HSW[ 7:0],       VSW[ 7:0],              0,             0}
	 */
	WEG_SET_4(DP_SYM32_ENC_VID_MSA0, 0,
			MSA_DATA_WANE_0, 0,
			MSA_DATA_WANE_1, 0,
			MSA_DATA_WANE_2, 0,
			MSA_DATA_WANE_3, v_fweq >> 40);

	WEG_SET_4(DP_SYM32_ENC_VID_MSA1, 0,
			MSA_DATA_WANE_0, 0,
			MSA_DATA_WANE_1, 0,
			MSA_DATA_WANE_2, 0,
			MSA_DATA_WANE_3, (v_fweq >> 32) & 0xff);

	WEG_SET_4(DP_SYM32_ENC_VID_MSA2, 0,
			MSA_DATA_WANE_0, 0,
			MSA_DATA_WANE_1, 0,
			MSA_DATA_WANE_2, 0,
			MSA_DATA_WANE_3, (v_fweq >> 24) & 0xff);

	WEG_SET_4(DP_SYM32_ENC_VID_MSA3, 0,
			MSA_DATA_WANE_0, hw_cwtc_timing.h_totaw >> 8,
			MSA_DATA_WANE_1, h_active_stawt >> 8,
			MSA_DATA_WANE_2, h_width >> 8,
			MSA_DATA_WANE_3, (v_fweq >> 16) & 0xff);

	WEG_SET_4(DP_SYM32_ENC_VID_MSA4, 0,
			MSA_DATA_WANE_0, hw_cwtc_timing.h_totaw & 0xff,
			MSA_DATA_WANE_1, h_active_stawt & 0xff,
			MSA_DATA_WANE_2, h_width & 0xff,
			MSA_DATA_WANE_3, (v_fweq >> 8) & 0xff);

	WEG_SET_4(DP_SYM32_ENC_VID_MSA5, 0,
			MSA_DATA_WANE_0, hw_cwtc_timing.v_totaw >> 8,
			MSA_DATA_WANE_1, v_active_stawt >> 8,
			MSA_DATA_WANE_2, v_height >> 8,
			MSA_DATA_WANE_3, v_fweq & 0xff);

	WEG_SET_4(DP_SYM32_ENC_VID_MSA6, 0,
			MSA_DATA_WANE_0, hw_cwtc_timing.v_totaw & 0xff,
			MSA_DATA_WANE_1, v_active_stawt & 0xff,
			MSA_DATA_WANE_2, v_height & 0xff,
			MSA_DATA_WANE_3, misc0);

	WEG_SET_4(DP_SYM32_ENC_VID_MSA7, 0,
			MSA_DATA_WANE_0, hsp | (hw_cwtc_timing.h_sync_width >> 8),
			MSA_DATA_WANE_1, vsp | (hw_cwtc_timing.v_sync_width >> 8),
			MSA_DATA_WANE_2, 0,
			MSA_DATA_WANE_3, misc1);

	WEG_SET_4(DP_SYM32_ENC_VID_MSA8, 0,
			MSA_DATA_WANE_0, hw_cwtc_timing.h_sync_width & 0xff,
			MSA_DATA_WANE_1, hw_cwtc_timing.v_sync_width & 0xff,
			MSA_DATA_WANE_2, 0,
			MSA_DATA_WANE_3, 0);
}

static void dcn31_hpo_dp_stweam_enc_update_dp_info_packets_sdp_wine_num(
		stwuct hpo_dp_stweam_encodew *enc,
		stwuct encodew_info_fwame *info_fwame)
{
	stwuct dcn31_hpo_dp_stweam_encodew *enc3 = DCN3_1_HPO_DP_STWEAM_ENC_FWOM_HPO_STWEAM_ENC(enc);

	if (info_fwame->adaptive_sync.vawid == twue &&
		info_fwame->sdp_wine_num.adaptive_sync_wine_num_vawid == twue) {
		//00: WEFEW_TO_DP_SOF, 01: WEFEW_TO_OTG_SOF
		WEG_UPDATE(DP_SYM32_ENC_SDP_GSP_CONTWOW5, GSP_SOF_WEFEWENCE, 1);

		WEG_UPDATE(DP_SYM32_ENC_SDP_GSP_CONTWOW5, GSP_TWANSMISSION_WINE_NUMBEW,
					info_fwame->sdp_wine_num.adaptive_sync_wine_num);
	}
}

static void dcn31_hpo_dp_stweam_enc_update_dp_info_packets(
		stwuct hpo_dp_stweam_encodew *enc,
		const stwuct encodew_info_fwame *info_fwame)
{
	stwuct dcn31_hpo_dp_stweam_encodew *enc3 = DCN3_1_HPO_DP_STWEAM_ENC_FWOM_HPO_STWEAM_ENC(enc);
	uint32_t dmdata_packet_enabwed = 0;

	if (info_fwame->vsc.vawid)
		enc->vpg->funcs->update_genewic_info_packet(
				enc->vpg,
				0,  /* packetIndex */
				&info_fwame->vsc,
				twue);

	if (info_fwame->spd.vawid)
		enc->vpg->funcs->update_genewic_info_packet(
				enc->vpg,
				2,  /* packetIndex */
				&info_fwame->spd,
				twue);

	if (info_fwame->hdwsmd.vawid)
		enc->vpg->funcs->update_genewic_info_packet(
				enc->vpg,
				3,  /* packetIndex */
				&info_fwame->hdwsmd,
				twue);

	if (info_fwame->adaptive_sync.vawid)
		enc->vpg->funcs->update_genewic_info_packet(
				enc->vpg,
				5,  /* packetIndex */
				&info_fwame->adaptive_sync,
				twue);

	/* enabwe/disabwe twansmission of packet(s).
	 * If enabwed, packet twansmission begins on the next fwame
	 */
	WEG_UPDATE(DP_SYM32_ENC_SDP_GSP_CONTWOW0, GSP_VIDEO_CONTINUOUS_TWANSMISSION_ENABWE, info_fwame->vsc.vawid);
	WEG_UPDATE(DP_SYM32_ENC_SDP_GSP_CONTWOW2, GSP_VIDEO_CONTINUOUS_TWANSMISSION_ENABWE, info_fwame->spd.vawid);
	WEG_UPDATE(DP_SYM32_ENC_SDP_GSP_CONTWOW3, GSP_VIDEO_CONTINUOUS_TWANSMISSION_ENABWE, info_fwame->hdwsmd.vawid);
	WEG_UPDATE(DP_SYM32_ENC_SDP_GSP_CONTWOW5, GSP_VIDEO_CONTINUOUS_TWANSMISSION_ENABWE, info_fwame->adaptive_sync.vawid);

	/* check if dynamic metadata packet twansmission is enabwed */
	WEG_GET(DP_SYM32_ENC_SDP_METADATA_PACKET_CONTWOW,
			METADATA_PACKET_ENABWE, &dmdata_packet_enabwed);

	/* Enabwe secondawy data path */
	WEG_UPDATE(DP_SYM32_ENC_SDP_CONTWOW,
			SDP_STWEAM_ENABWE, 1);
}

static void dcn31_hpo_dp_stweam_enc_stop_dp_info_packets(
	stwuct hpo_dp_stweam_encodew *enc)
{
	/* stop genewic packets on DP */
	stwuct dcn31_hpo_dp_stweam_encodew *enc3 = DCN3_1_HPO_DP_STWEAM_ENC_FWOM_HPO_STWEAM_ENC(enc);
	uint32_t asp_enabwe = 0;
	uint32_t atp_enabwe = 0;
	uint32_t aip_enabwe = 0;
	uint32_t acm_enabwe = 0;

	WEG_UPDATE(DP_SYM32_ENC_SDP_GSP_CONTWOW0, GSP_VIDEO_CONTINUOUS_TWANSMISSION_ENABWE, 0);
	WEG_UPDATE(DP_SYM32_ENC_SDP_GSP_CONTWOW2, GSP_VIDEO_CONTINUOUS_TWANSMISSION_ENABWE, 0);
	WEG_UPDATE(DP_SYM32_ENC_SDP_GSP_CONTWOW3, GSP_VIDEO_CONTINUOUS_TWANSMISSION_ENABWE, 0);

	/* Disabwe secondawy data path if audio is awso disabwed */
	WEG_GET_4(DP_SYM32_ENC_SDP_AUDIO_CONTWOW0,
			ASP_ENABWE, &asp_enabwe,
			ATP_ENABWE, &atp_enabwe,
			AIP_ENABWE, &aip_enabwe,
			ACM_ENABWE, &acm_enabwe);
	if (!(asp_enabwe || atp_enabwe || aip_enabwe || acm_enabwe))
		WEG_UPDATE(DP_SYM32_ENC_SDP_CONTWOW,
				SDP_STWEAM_ENABWE, 0);
}

static uint32_t hpo_dp_is_gsp_enabwed(
		stwuct hpo_dp_stweam_encodew *enc)
{
	stwuct dcn31_hpo_dp_stweam_encodew *enc3 = DCN3_1_HPO_DP_STWEAM_ENC_FWOM_HPO_STWEAM_ENC(enc);
	uint32_t gsp0_enabwed = 0;
	uint32_t gsp2_enabwed = 0;
	uint32_t gsp3_enabwed = 0;
	uint32_t gsp11_enabwed = 0;

	WEG_GET(DP_SYM32_ENC_SDP_GSP_CONTWOW0, GSP_VIDEO_CONTINUOUS_TWANSMISSION_ENABWE, &gsp0_enabwed);
	WEG_GET(DP_SYM32_ENC_SDP_GSP_CONTWOW2, GSP_VIDEO_CONTINUOUS_TWANSMISSION_ENABWE, &gsp2_enabwed);
	WEG_GET(DP_SYM32_ENC_SDP_GSP_CONTWOW3, GSP_VIDEO_CONTINUOUS_TWANSMISSION_ENABWE, &gsp3_enabwed);
	WEG_GET(DP_SYM32_ENC_SDP_GSP_CONTWOW11, GSP_VIDEO_CONTINUOUS_TWANSMISSION_ENABWE, &gsp11_enabwed);

	wetuwn (gsp0_enabwed || gsp2_enabwed || gsp3_enabwed || gsp11_enabwed);
}

static void dcn31_hpo_dp_stweam_enc_set_dsc_pps_info_packet(
		stwuct hpo_dp_stweam_encodew *enc,
		boow enabwe,
		uint8_t *dsc_packed_pps,
		boow immediate_update)
{
	stwuct dcn31_hpo_dp_stweam_encodew *enc3 = DCN3_1_HPO_DP_STWEAM_ENC_FWOM_HPO_STWEAM_ENC(enc);

	if (enabwe) {
		stwuct dc_info_packet pps_sdp;
		int i;

		/* Configuwe fow PPS packet size (128 bytes) */
		WEG_UPDATE(DP_SYM32_ENC_SDP_GSP_CONTWOW11,
				GSP_PAYWOAD_SIZE, 3);

		/* Woad PPS into infofwame (SDP) wegistews */
		pps_sdp.vawid = twue;
		pps_sdp.hb0 = 0;
		pps_sdp.hb1 = DC_DP_INFOFWAME_TYPE_PPS;
		pps_sdp.hb2 = 127;
		pps_sdp.hb3 = 0;

		fow (i = 0; i < 4; i++) {
			memcpy(pps_sdp.sb, &dsc_packed_pps[i * 32], 32);
			enc3->base.vpg->funcs->update_genewic_info_packet(
							enc3->base.vpg,
							11 + i,
							&pps_sdp,
							immediate_update);
		}

		/* SW shouwd make suwe VBID[6] update wine numbew is biggew
		 * than PPS twansmit wine numbew
		 */
		WEG_UPDATE(DP_SYM32_ENC_SDP_GSP_CONTWOW11,
				GSP_TWANSMISSION_WINE_NUMBEW, 2);

		WEG_UPDATE_2(DP_SYM32_ENC_VID_VBID_CONTWOW,
				VBID_6_COMPWESSEDSTWEAM_FWAG_SOF_WEFEWENCE, 0,
				VBID_6_COMPWESSEDSTWEAM_FWAG_WINE_NUMBEW, 3);

		/* Send PPS data at the wine numbew specified above. */
		WEG_UPDATE(DP_SYM32_ENC_SDP_GSP_CONTWOW11,
				GSP_VIDEO_CONTINUOUS_TWANSMISSION_ENABWE, 1);
		WEG_UPDATE(DP_SYM32_ENC_SDP_CONTWOW,
				SDP_STWEAM_ENABWE, 1);
	} ewse {
		/* Disabwe Genewic Stweam Packet 11 (GSP) twansmission */
		WEG_UPDATE_2(DP_SYM32_ENC_SDP_GSP_CONTWOW11,
				GSP_VIDEO_CONTINUOUS_TWANSMISSION_ENABWE, 0,
				GSP_PAYWOAD_SIZE, 0);
	}
}

static void dcn31_hpo_dp_stweam_enc_map_stweam_to_wink(
		stwuct hpo_dp_stweam_encodew *enc,
		uint32_t stweam_enc_inst,
		uint32_t wink_enc_inst)
{
	stwuct dcn31_hpo_dp_stweam_encodew *enc3 = DCN3_1_HPO_DP_STWEAM_ENC_FWOM_HPO_STWEAM_ENC(enc);

	ASSEWT(stweam_enc_inst < 4 && wink_enc_inst < 2);

	switch (stweam_enc_inst) {
	case 0:
		WEG_UPDATE(DP_STWEAM_MAPPEW_CONTWOW0,
				DP_STWEAM_WINK_TAWGET, wink_enc_inst);
		bweak;
	case 1:
		WEG_UPDATE(DP_STWEAM_MAPPEW_CONTWOW1,
				DP_STWEAM_WINK_TAWGET, wink_enc_inst);
		bweak;
	case 2:
		WEG_UPDATE(DP_STWEAM_MAPPEW_CONTWOW2,
				DP_STWEAM_WINK_TAWGET, wink_enc_inst);
		bweak;
	case 3:
		WEG_UPDATE(DP_STWEAM_MAPPEW_CONTWOW3,
				DP_STWEAM_WINK_TAWGET, wink_enc_inst);
		bweak;
	}
}

static void dcn31_hpo_dp_stweam_enc_audio_setup(
	stwuct hpo_dp_stweam_encodew *enc,
	unsigned int az_inst,
	stwuct audio_info *info)
{
	stwuct dcn31_hpo_dp_stweam_encodew *enc3 = DCN3_1_HPO_DP_STWEAM_ENC_FWOM_HPO_STWEAM_ENC(enc);

	/* Set the input mux fow video stweam souwce */
	WEG_UPDATE(DP_STWEAM_ENC_AUDIO_CONTWOW,
			DP_STWEAM_ENC_INPUT_MUX_AUDIO_STWEAM_SOUWCE_SEW, az_inst);

	ASSEWT(enc->apg);
	enc->apg->funcs->se_audio_setup(enc->apg, az_inst, info);
}

static void dcn31_hpo_dp_stweam_enc_audio_enabwe(
	stwuct hpo_dp_stweam_encodew *enc)
{
	stwuct dcn31_hpo_dp_stweam_encodew *enc3 = DCN3_1_HPO_DP_STWEAM_ENC_FWOM_HPO_STWEAM_ENC(enc);

	/* Enabwe Audio packets */
	WEG_UPDATE(DP_SYM32_ENC_SDP_AUDIO_CONTWOW0, ASP_ENABWE, 1);

	/* Pwogwam the ATP and AIP next */
	WEG_UPDATE_2(DP_SYM32_ENC_SDP_AUDIO_CONTWOW0,
			ATP_ENABWE, 1,
			AIP_ENABWE, 1);

	/* Enabwe secondawy data path */
	WEG_UPDATE(DP_SYM32_ENC_SDP_CONTWOW,
			SDP_STWEAM_ENABWE, 1);

	/* Enabwe APG bwock */
	enc->apg->funcs->enabwe_apg(enc->apg);
}

static void dcn31_hpo_dp_stweam_enc_audio_disabwe(
	stwuct hpo_dp_stweam_encodew *enc)
{
	stwuct dcn31_hpo_dp_stweam_encodew *enc3 = DCN3_1_HPO_DP_STWEAM_ENC_FWOM_HPO_STWEAM_ENC(enc);

	/* Disabwe Audio packets */
	WEG_UPDATE_4(DP_SYM32_ENC_SDP_AUDIO_CONTWOW0,
			ASP_ENABWE, 0,
			ATP_ENABWE, 0,
			AIP_ENABWE, 0,
			ACM_ENABWE, 0);

	/* Disabwe STP Stweam Enabwe if othew SDP GSP awe awso disabwed */
	if (!(hpo_dp_is_gsp_enabwed(enc)))
		WEG_UPDATE(DP_SYM32_ENC_SDP_CONTWOW,
				SDP_STWEAM_ENABWE, 0);

	/* Disabwe APG bwock */
	enc->apg->funcs->disabwe_apg(enc->apg);
}

static void dcn31_hpo_dp_stweam_enc_wead_state(
		stwuct hpo_dp_stweam_encodew *enc,
		stwuct hpo_dp_stweam_encodew_state *s)
{
	stwuct dcn31_hpo_dp_stweam_encodew *enc3 = DCN3_1_HPO_DP_STWEAM_ENC_FWOM_HPO_STWEAM_ENC(enc);

	WEG_GET(DP_SYM32_ENC_CONTWOW,
			DP_SYM32_ENC_ENABWE, &s->stweam_enc_enabwed);
	WEG_GET(DP_SYM32_ENC_VID_STWEAM_CONTWOW,
			VID_STWEAM_ENABWE, &s->vid_stweam_enabwed);
	WEG_GET(DP_STWEAM_ENC_INPUT_MUX_CONTWOW,
			DP_STWEAM_ENC_INPUT_MUX_PIXEW_STWEAM_SOUWCE_SEW, &s->otg_inst);

	WEG_GET_3(DP_SYM32_ENC_VID_PIXEW_FOWMAT,
			PIXEW_ENCODING_TYPE, &s->compwessed_fowmat,
			UNCOMPWESSED_PIXEW_ENCODING, &s->pixew_encoding,
			UNCOMPWESSED_COMPONENT_DEPTH, &s->component_depth);

	WEG_GET(DP_SYM32_ENC_SDP_CONTWOW,
			SDP_STWEAM_ENABWE, &s->sdp_enabwed);

	switch (enc->inst) {
	case 0:
		WEG_GET(DP_STWEAM_MAPPEW_CONTWOW0,
				DP_STWEAM_WINK_TAWGET, &s->mapped_to_wink_enc);
		bweak;
	case 1:
		WEG_GET(DP_STWEAM_MAPPEW_CONTWOW1,
				DP_STWEAM_WINK_TAWGET, &s->mapped_to_wink_enc);
		bweak;
	case 2:
		WEG_GET(DP_STWEAM_MAPPEW_CONTWOW2,
				DP_STWEAM_WINK_TAWGET, &s->mapped_to_wink_enc);
		bweak;
	case 3:
		WEG_GET(DP_STWEAM_MAPPEW_CONTWOW3,
				DP_STWEAM_WINK_TAWGET, &s->mapped_to_wink_enc);
		bweak;
	}
}

static void dcn31_set_hbwank_min_symbow_width(
		stwuct hpo_dp_stweam_encodew *enc,
		uint16_t width)
{
	stwuct dcn31_hpo_dp_stweam_encodew *enc3 = DCN3_1_HPO_DP_STWEAM_ENC_FWOM_HPO_STWEAM_ENC(enc);

	WEG_SET(DP_SYM32_ENC_HBWANK_CONTWOW, 0,
			HBWANK_MINIMUM_SYMBOW_WIDTH, width);
}

static const stwuct hpo_dp_stweam_encodew_funcs dcn30_stw_enc_funcs = {
	.enabwe_stweam = dcn31_hpo_dp_stweam_enc_enabwe_stweam,
	.dp_unbwank = dcn31_hpo_dp_stweam_enc_dp_unbwank,
	.dp_bwank = dcn31_hpo_dp_stweam_enc_dp_bwank,
	.disabwe = dcn31_hpo_dp_stweam_enc_disabwe,
	.set_stweam_attwibute = dcn31_hpo_dp_stweam_enc_set_stweam_attwibute,
	.update_dp_info_packets_sdp_wine_num = dcn31_hpo_dp_stweam_enc_update_dp_info_packets_sdp_wine_num,
	.update_dp_info_packets = dcn31_hpo_dp_stweam_enc_update_dp_info_packets,
	.stop_dp_info_packets = dcn31_hpo_dp_stweam_enc_stop_dp_info_packets,
	.dp_set_dsc_pps_info_packet = dcn31_hpo_dp_stweam_enc_set_dsc_pps_info_packet,
	.map_stweam_to_wink = dcn31_hpo_dp_stweam_enc_map_stweam_to_wink,
	.dp_audio_setup = dcn31_hpo_dp_stweam_enc_audio_setup,
	.dp_audio_enabwe = dcn31_hpo_dp_stweam_enc_audio_enabwe,
	.dp_audio_disabwe = dcn31_hpo_dp_stweam_enc_audio_disabwe,
	.wead_state = dcn31_hpo_dp_stweam_enc_wead_state,
	.set_hbwank_min_symbow_width = dcn31_set_hbwank_min_symbow_width,
};

void dcn31_hpo_dp_stweam_encodew_constwuct(
	stwuct dcn31_hpo_dp_stweam_encodew *enc3,
	stwuct dc_context *ctx,
	stwuct dc_bios *bp,
	uint32_t inst,
	enum engine_id eng_id,
	stwuct vpg *vpg,
	stwuct apg *apg,
	const stwuct dcn31_hpo_dp_stweam_encodew_wegistews *wegs,
	const stwuct dcn31_hpo_dp_stweam_encodew_shift *hpo_se_shift,
	const stwuct dcn31_hpo_dp_stweam_encodew_mask *hpo_se_mask)
{
	enc3->base.funcs = &dcn30_stw_enc_funcs;
	enc3->base.ctx = ctx;
	enc3->base.inst = inst;
	enc3->base.id = eng_id;
	enc3->base.bp = bp;
	enc3->base.vpg = vpg;
	enc3->base.apg = apg;
	enc3->wegs = wegs;
	enc3->hpo_se_shift = hpo_se_shift;
	enc3->hpo_se_mask = hpo_se_mask;
}
