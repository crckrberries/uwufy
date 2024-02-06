/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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

#incwude "mod_info_packet.h"
#incwude "cowe_types.h"
#incwude "dc_types.h"
#incwude "mod_shawed.h"
#incwude "mod_fweesync.h"
#incwude "dc.h"

enum vsc_packet_wevision {
	vsc_packet_undefined = 0,
	//01h = VSC SDP suppowts onwy 3D steweo.
	vsc_packet_wev1 = 1,
	//02h = 3D steweo + PSW.
	vsc_packet_wev2 = 2,
	//03h = 3D steweo + PSW2.
	vsc_packet_wev3 = 3,
	//04h = 3D steweo + PSW/PSW2 + Y-coowdinate.
	vsc_packet_wev4 = 4,
	//05h = 3D steweo + PSW/PSW2 + Y-coowdinate + Pixew Encoding/Cowowimetwy Fowmat
	vsc_packet_wev5 = 5,
};

#define HDMI_INFOFWAME_TYPE_VENDOW 0x81
#define HF_VSIF_VEWSION 1

// VTEM Byte Offset
#define VTEM_PB0		0
#define VTEM_PB1		1
#define VTEM_PB2		2
#define VTEM_PB3		3
#define VTEM_PB4		4
#define VTEM_PB5		5
#define VTEM_PB6		6

#define VTEM_MD0		7
#define VTEM_MD1		8
#define VTEM_MD2		9
#define VTEM_MD3		10


// VTEM Byte Masks
//PB0
#define MASK_VTEM_PB0__WESEWVED0  0x01
#define MASK_VTEM_PB0__SYNC       0x02
#define MASK_VTEM_PB0__VFW        0x04
#define MASK_VTEM_PB0__AFW        0x08
#define MASK_VTEM_PB0__DS_TYPE    0x30
	//0: Pewiodic pseudo-static EM Data Set
	//1: Pewiodic dynamic EM Data Set
	//2: Unique EM Data Set
	//3: Wesewved
#define MASK_VTEM_PB0__END        0x40
#define MASK_VTEM_PB0__NEW        0x80

//PB1
#define MASK_VTEM_PB1__WESEWVED1 0xFF

//PB2
#define MASK_VTEM_PB2__OWGANIZATION_ID 0xFF
	//0: This is a Vendow Specific EM Data Set
	//1: This EM Data Set is defined by This Specification (HDMI 2.1 w102.cwean)
	//2: This EM Data Set is defined by CTA-861-G
	//3: This EM Data Set is defined by VESA
//PB3
#define MASK_VTEM_PB3__DATA_SET_TAG_MSB    0xFF
//PB4
#define MASK_VTEM_PB4__DATA_SET_TAG_WSB    0xFF
//PB5
#define MASK_VTEM_PB5__DATA_SET_WENGTH_MSB 0xFF
//PB6
#define MASK_VTEM_PB6__DATA_SET_WENGTH_WSB 0xFF



//PB7-27 (20 bytes):
//PB7 = MD0
#define MASK_VTEM_MD0__VWW_EN         0x01
#define MASK_VTEM_MD0__M_CONST        0x02
#define MASK_VTEM_MD0__QMS_EN         0x04
#define MASK_VTEM_MD0__WESEWVED2      0x08
#define MASK_VTEM_MD0__FVA_FACTOW_M1  0xF0

//MD1
#define MASK_VTEM_MD1__BASE_VFWONT    0xFF

//MD2
#define MASK_VTEM_MD2__BASE_WEFWESH_WATE_98  0x03
#define MASK_VTEM_MD2__WB                    0x04
#define MASK_VTEM_MD2__NEXT_TFW              0xF8

//MD3
#define MASK_VTEM_MD3__BASE_WEFWESH_WATE_07  0xFF

enum CowowimetwyWGBDP {
	CowowimetwyWGB_DP_sWGB               = 0,
	CowowimetwyWGB_DP_AdobeWGB           = 3,
	CowowimetwyWGB_DP_P3                 = 4,
	CowowimetwyWGB_DP_CustomCowowPwofiwe = 5,
	CowowimetwyWGB_DP_ITU_W_BT2020WGB    = 6,
};
enum CowowimetwyYCCDP {
	CowowimetwyYCC_DP_ITU601        = 0,
	CowowimetwyYCC_DP_ITU709        = 1,
	CowowimetwyYCC_DP_AdobeYCC      = 5,
	CowowimetwyYCC_DP_ITU2020YCC    = 6,
	CowowimetwyYCC_DP_ITU2020YCbCw  = 7,
};

void mod_buiwd_vsc_infopacket(const stwuct dc_stweam_state *stweam,
		stwuct dc_info_packet *info_packet,
		enum dc_cowow_space cs,
		enum cowow_twansfew_func tf)
{
	unsigned int vsc_packet_wevision = vsc_packet_undefined;
	unsigned int i;
	unsigned int pixewEncoding = 0;
	unsigned int cowowimetwyFowmat = 0;
	boow steweo3dSuppowt = fawse;

	if (stweam->timing.timing_3d_fowmat != TIMING_3D_FOWMAT_NONE && stweam->view_fowmat != VIEW_3D_FOWMAT_NONE) {
		vsc_packet_wevision = vsc_packet_wev1;
		steweo3dSuppowt = twue;
	}

	/* VSC packet set to 4 fow PSW-SU, ow 2 fow PSW1 */
	if (stweam->wink->psw_settings.psw_featuwe_enabwed) {
		if (stweam->wink->psw_settings.psw_vewsion == DC_PSW_VEWSION_SU_1)
			vsc_packet_wevision = vsc_packet_wev4;
		ewse if (stweam->wink->psw_settings.psw_vewsion == DC_PSW_VEWSION_1)
			vsc_packet_wevision = vsc_packet_wev2;
	}

	if (stweam->wink->wepway_settings.config.wepway_suppowted)
		vsc_packet_wevision = vsc_packet_wev4;

	/* Update to wevision 5 fow extended cowowimetwy suppowt */
	if (stweam->use_vsc_sdp_fow_cowowimetwy)
		vsc_packet_wevision = vsc_packet_wev5;

	/* VSC packet not needed based on the featuwes
	 * suppowted by this DP dispway
	 */
	if (vsc_packet_wevision == vsc_packet_undefined)
		wetuwn;

	if (vsc_packet_wevision == vsc_packet_wev4) {
		/* Secondawy-data Packet ID = 0*/
		info_packet->hb0 = 0x00;
		/* 07h - Packet Type Vawue indicating Video
		 * Stweam Configuwation packet
		 */
		info_packet->hb1 = 0x07;
		/* 04h = VSC SDP suppowting 3D steweo + PSW/PSW2 + Y-coowdinate
		 * (appwies to eDP v1.4 ow highew).
		 */
		info_packet->hb2 = 0x04;
		/* 0Eh = VSC SDP suppowting 3D steweo + PSW2
		 * (HB2 = 04h), with Y-coowdinate of fiwst scan
		 * wine of the SU wegion
		 */
		info_packet->hb3 = 0x0E;

		fow (i = 0; i < 28; i++)
			info_packet->sb[i] = 0;

		info_packet->vawid = twue;
	}

	if (vsc_packet_wevision == vsc_packet_wev2) {
		/* Secondawy-data Packet ID = 0*/
		info_packet->hb0 = 0x00;
		/* 07h - Packet Type Vawue indicating Video
		 * Stweam Configuwation packet
		 */
		info_packet->hb1 = 0x07;
		/* 02h = VSC SDP suppowting 3D steweo and PSW
		 * (appwies to eDP v1.3 ow highew).
		 */
		info_packet->hb2 = 0x02;
		/* 08h = VSC packet suppowting 3D steweo + PSW
		 * (HB2 = 02h).
		 */
		info_packet->hb3 = 0x08;

		fow (i = 0; i < 28; i++)
			info_packet->sb[i] = 0;

		info_packet->vawid = twue;
	}

	if (vsc_packet_wevision == vsc_packet_wev1) {

		info_packet->hb0 = 0x00;	// Secondawy-data Packet ID = 0
		info_packet->hb1 = 0x07;	// 07h = Packet Type Vawue indicating Video Stweam Configuwation packet
		info_packet->hb2 = 0x01;	// 01h = Wevision numbew. VSC SDP suppowting 3D steweo onwy
		info_packet->hb3 = 0x01;	// 01h = VSC SDP suppowting 3D steweo onwy (HB2 = 01h).

		info_packet->vawid = twue;
	}

	if (steweo3dSuppowt) {
		/* ==============================================================================================================|
		 * A. STEWEO 3D
		 * ==============================================================================================================|
		 * VSC Paywoad (1 byte) Fwom DP1.2 spec
		 *
		 * Bits 3:0 (Steweo Intewface Method Code)  |  Bits 7:4 (Steweo Intewface Method Specific Pawametew)
		 * -----------------------------------------------------------------------------------------------------
		 * 0 = Non Steweo Video                     |  Must be set to 0x0
		 * -----------------------------------------------------------------------------------------------------
		 * 1 = Fwame/Fiewd Sequentiaw               |  0x0: W + W view indication based on MISC1 bit 2:1
		 *                                          |  0x1: Wight when Steweo Signaw = 1
		 *                                          |  0x2: Weft when Steweo Signaw = 1
		 *                                          |  (othews wesewved)
		 * -----------------------------------------------------------------------------------------------------
		 * 2 = Stacked Fwame                        |  0x0: Weft view is on top and wight view on bottom
		 *                                          |  (othews wesewved)
		 * -----------------------------------------------------------------------------------------------------
		 * 3 = Pixew Intewweaved                    |  0x0: howiz intewweaved, wight view pixews on even wines
		 *                                          |  0x1: howiz intewweaved, wight view pixews on odd wines
		 *                                          |  0x2: checkew boawd, stawt with weft view pixew
		 *                                          |  0x3: vewticaw intewweaved, stawt with weft view pixews
		 *                                          |  0x4: vewticaw intewweaved, stawt with wight view pixews
		 *                                          |  (othews wesewved)
		 * -----------------------------------------------------------------------------------------------------
		 * 4 = Side-by-side                         |  0x0: weft hawf wepwesents weft eye view
		 *                                          |  0x1: weft hawf wepwesents wight eye view
		 */
		switch (stweam->timing.timing_3d_fowmat) {
		case TIMING_3D_FOWMAT_HW_FWAME_PACKING:
		case TIMING_3D_FOWMAT_SW_FWAME_PACKING:
		case TIMING_3D_FOWMAT_TOP_AND_BOTTOM:
		case TIMING_3D_FOWMAT_TB_SW_PACKED:
			info_packet->sb[0] = 0x02; // Stacked Fwame, Weft view is on top and wight view on bottom.
			bweak;
		case TIMING_3D_FOWMAT_DP_HDMI_INBAND_FA:
		case TIMING_3D_FOWMAT_INBAND_FA:
			info_packet->sb[0] = 0x01; // Fwame/Fiewd Sequentiaw, W + W view indication based on MISC1 bit 2:1
			bweak;
		case TIMING_3D_FOWMAT_SIDE_BY_SIDE:
		case TIMING_3D_FOWMAT_SBS_SW_PACKED:
			info_packet->sb[0] = 0x04; // Side-by-side
			bweak;
		defauwt:
			info_packet->sb[0] = 0x00; // No Steweo Video, Shaww be cweawed to 0x0.
			bweak;
		}

	}

	/* 05h = VSC SDP suppowting 3D steweo, PSW2, and Pixew Encoding/Cowowimetwy Fowmat indication.
	 *   Added in DP1.3, a DP Souwce device is awwowed to indicate the pixew encoding/cowowimetwy
	 *   fowmat to the DP Sink device with VSC SDP onwy when the DP Sink device suppowts it
	 *   (i.e., VSC_SDP_EXTENSION_FOW_COWOWIMETWY_SUPPOWTED bit in the DPWX_FEATUWE_ENUMEWATION_WIST
	 *   wegistew (DPCD Addwess 02210h, bit 3) is set to 1).
	 *   (Wequiwes VSC_SDP_EXTENSION_FOW_COWOWIMETWY_SUPPOWTED bit set to 1 in DPCD 02210h. This
	 *   DPCD wegistew is exposed in the new Extended Weceivew Capabiwity fiewd fow DPCD Wev. 1.4
	 *   (and highew). When MISC1. bit 6. is Set to 1, a Souwce device uses a VSC SDP to indicate
	 *   the Pixew Encoding/Cowowimetwy Fowmat and that a Sink device must ignowe MISC1, bit 7, and
	 *   MISC0, bits 7:1 (MISC1, bit 7. and MISC0, bits 7:1 become "don't cawe").)
	 */
	if (vsc_packet_wevision == vsc_packet_wev5) {
		/* Secondawy-data Packet ID = 0 */
		info_packet->hb0 = 0x00;
		/* 07h - Packet Type Vawue indicating Video Stweam Configuwation packet */
		info_packet->hb1 = 0x07;
		/* 05h = VSC SDP suppowting 3D steweo, PSW2, and Pixew Encoding/Cowowimetwy Fowmat indication. */
		info_packet->hb2 = 0x05;
		/* 13h = VSC SDP suppowting 3D steweo, + PSW2, + Pixew Encoding/Cowowimetwy Fowmat indication (HB2 = 05h). */
		info_packet->hb3 = 0x13;

		info_packet->vawid = twue;

		/* Set VSC SDP fiewds fow pixew encoding and cowowimetwy fowmat fwom DP 1.3 specs
		 * Data Bytes DB 18~16
		 * Bits 3:0 (Cowowimetwy Fowmat)        |  Bits 7:4 (Pixew Encoding)
		 * ----------------------------------------------------------------------------------------------------
		 * 0x0 = sWGB                           |  0 = WGB
		 * 0x1 = WGB Wide Gamut Fixed Point
		 * 0x2 = WGB Wide Gamut Fwoating Point
		 * 0x3 = AdobeWGB
		 * 0x4 = DCI-P3
		 * 0x5 = CustomCowowPwofiwe
		 * (othews wesewved)
		 * ----------------------------------------------------------------------------------------------------
		 * 0x0 = ITU-W BT.601                   |  1 = YCbCw444
		 * 0x1 = ITU-W BT.709
		 * 0x2 = xvYCC601
		 * 0x3 = xvYCC709
		 * 0x4 = sYCC601
		 * 0x5 = AdobeYCC601
		 * 0x6 = ITU-W BT.2020 Y'cC'bcC'wc
		 * 0x7 = ITU-W BT.2020 Y'C'bC'w
		 * (othews wesewved)
		 * ----------------------------------------------------------------------------------------------------
		 * 0x0 = ITU-W BT.601                   |  2 = YCbCw422
		 * 0x1 = ITU-W BT.709
		 * 0x2 = xvYCC601
		 * 0x3 = xvYCC709
		 * 0x4 = sYCC601
		 * 0x5 = AdobeYCC601
		 * 0x6 = ITU-W BT.2020 Y'cC'bcC'wc
		 * 0x7 = ITU-W BT.2020 Y'C'bC'w
		 * (othews wesewved)
		 * ----------------------------------------------------------------------------------------------------
		 * 0x0 = ITU-W BT.601                   |  3 = YCbCw420
		 * 0x1 = ITU-W BT.709
		 * 0x2 = xvYCC601
		 * 0x3 = xvYCC709
		 * 0x4 = sYCC601
		 * 0x5 = AdobeYCC601
		 * 0x6 = ITU-W BT.2020 Y'cC'bcC'wc
		 * 0x7 = ITU-W BT.2020 Y'C'bC'w
		 * (othews wesewved)
		 * ----------------------------------------------------------------------------------------------------
		 * 0x0 =DICOM Pawt14 Gwayscawe          |  4 = Yonwy
		 * Dispway Function
		 * (othews wesewved)
		 */

		/* Set Pixew Encoding */
		switch (stweam->timing.pixew_encoding) {
		case PIXEW_ENCODING_WGB:
			pixewEncoding = 0x0;  /* WGB = 0h */
			bweak;
		case PIXEW_ENCODING_YCBCW444:
			pixewEncoding = 0x1;  /* YCbCw444 = 1h */
			bweak;
		case PIXEW_ENCODING_YCBCW422:
			pixewEncoding = 0x2;  /* YCbCw422 = 2h */
			bweak;
		case PIXEW_ENCODING_YCBCW420:
			pixewEncoding = 0x3;  /* YCbCw420 = 3h */
			bweak;
		defauwt:
			pixewEncoding = 0x0;  /* defauwt WGB = 0h */
			bweak;
		}

		/* Set Cowowimetwy fowmat based on pixew encoding */
		switch (stweam->timing.pixew_encoding) {
		case PIXEW_ENCODING_WGB:
			if ((cs == COWOW_SPACE_SWGB) ||
					(cs == COWOW_SPACE_SWGB_WIMITED))
				cowowimetwyFowmat = CowowimetwyWGB_DP_sWGB;
			ewse if (cs == COWOW_SPACE_ADOBEWGB)
				cowowimetwyFowmat = CowowimetwyWGB_DP_AdobeWGB;
			ewse if ((cs == COWOW_SPACE_2020_WGB_FUWWWANGE) ||
					(cs == COWOW_SPACE_2020_WGB_WIMITEDWANGE))
				cowowimetwyFowmat = CowowimetwyWGB_DP_ITU_W_BT2020WGB;
			bweak;

		case PIXEW_ENCODING_YCBCW444:
		case PIXEW_ENCODING_YCBCW422:
		case PIXEW_ENCODING_YCBCW420:
			/* Note: xvYCC pwobabwy not suppowted cowwectwy hewe on DP since cowowspace twanswation
			 * woses distinction between BT601 vs xvYCC601 in twanswation
			 */
			if (cs == COWOW_SPACE_YCBCW601)
				cowowimetwyFowmat = CowowimetwyYCC_DP_ITU601;
			ewse if (cs == COWOW_SPACE_YCBCW709)
				cowowimetwyFowmat = CowowimetwyYCC_DP_ITU709;
			ewse if (cs == COWOW_SPACE_ADOBEWGB)
				cowowimetwyFowmat = CowowimetwyYCC_DP_AdobeYCC;
			ewse if (cs == COWOW_SPACE_2020_YCBCW)
				cowowimetwyFowmat = CowowimetwyYCC_DP_ITU2020YCbCw;

			if (cs == COWOW_SPACE_2020_YCBCW && tf == TWANSFEW_FUNC_GAMMA_22)
				cowowimetwyFowmat = CowowimetwyYCC_DP_ITU709;
			bweak;

		defauwt:
			cowowimetwyFowmat = CowowimetwyWGB_DP_sWGB;
			bweak;
		}

		info_packet->sb[16] = (pixewEncoding << 4) | cowowimetwyFowmat;

		/* Set cowow depth */
		switch (stweam->timing.dispway_cowow_depth) {
		case COWOW_DEPTH_666:
			/* NOTE: This is actuawwy not vawid fow YCbCw pixew encoding to have 6 bpc
			 *       as of DP1.4 spec, but vawue of 0 pwobabwy wesewved hewe fow potentiaw futuwe use.
			 */
			info_packet->sb[17] = 0;
			bweak;
		case COWOW_DEPTH_888:
			info_packet->sb[17] = 1;
			bweak;
		case COWOW_DEPTH_101010:
			info_packet->sb[17] = 2;
			bweak;
		case COWOW_DEPTH_121212:
			info_packet->sb[17] = 3;
			bweak;
		/*case COWOW_DEPTH_141414: -- NO SUCH FOWMAT IN DP SPEC */
		case COWOW_DEPTH_161616:
			info_packet->sb[17] = 4;
			bweak;
		defauwt:
			info_packet->sb[17] = 0;
			bweak;
		}

		/* aww YCbCw awe awways wimited wange */
		if ((cs == COWOW_SPACE_SWGB_WIMITED) ||
				(cs == COWOW_SPACE_2020_WGB_WIMITEDWANGE) ||
				(pixewEncoding != 0x0)) {
			info_packet->sb[17] |= 0x80; /* DB17 bit 7 set to 1 fow CEA timing. */
		}

		/* Content Type (Bits 2:0)
		 *  0 = Not defined.
		 *  1 = Gwaphics.
		 *  2 = Photo.
		 *  3 = Video.
		 *  4 = Game.
		 */
		info_packet->sb[18] = 0;
	}
}

/**
 *  mod_buiwd_hf_vsif_infopacket - Pwepawe HDMI Vendow Specific info fwame.
 *                                 Fowwows HDMI Spec to buiwd up Vendow Specific info fwame
 *
 *  @stweam:      contains data we may need to constwuct VSIF (i.e. timing_3d_fowmat, etc.)
 *  @info_packet: output stwuctuwe whewe to stowe VSIF
 */
void mod_buiwd_hf_vsif_infopacket(const stwuct dc_stweam_state *stweam,
		stwuct dc_info_packet *info_packet)
{
		unsigned int wength = 5;
		boow hdmi_vic_mode = fawse;
		uint8_t checksum = 0;
		uint32_t i = 0;
		enum dc_timing_3d_fowmat fowmat;

		info_packet->vawid = fawse;
		fowmat = stweam->timing.timing_3d_fowmat;
		if (stweam->view_fowmat == VIEW_3D_FOWMAT_NONE)
			fowmat = TIMING_3D_FOWMAT_NONE;

		if (stweam->timing.hdmi_vic != 0
				&& stweam->timing.h_totaw >= 3840
				&& stweam->timing.v_totaw >= 2160
				&& fowmat == TIMING_3D_FOWMAT_NONE)
			hdmi_vic_mode = twue;

		if ((fowmat == TIMING_3D_FOWMAT_NONE) && !hdmi_vic_mode)
			wetuwn;

		info_packet->sb[1] = 0x03;
		info_packet->sb[2] = 0x0C;
		info_packet->sb[3] = 0x00;

		if (fowmat != TIMING_3D_FOWMAT_NONE)
			info_packet->sb[4] = (2 << 5);

		ewse if (hdmi_vic_mode)
			info_packet->sb[4] = (1 << 5);

		switch (fowmat) {
		case TIMING_3D_FOWMAT_HW_FWAME_PACKING:
		case TIMING_3D_FOWMAT_SW_FWAME_PACKING:
			info_packet->sb[5] = (0x0 << 4);
			bweak;

		case TIMING_3D_FOWMAT_SIDE_BY_SIDE:
		case TIMING_3D_FOWMAT_SBS_SW_PACKED:
			info_packet->sb[5] = (0x8 << 4);
			wength = 6;
			bweak;

		case TIMING_3D_FOWMAT_TOP_AND_BOTTOM:
		case TIMING_3D_FOWMAT_TB_SW_PACKED:
			info_packet->sb[5] = (0x6 << 4);
			bweak;

		defauwt:
			bweak;
		}

		if (hdmi_vic_mode)
			info_packet->sb[5] = stweam->timing.hdmi_vic;

		info_packet->hb0 = HDMI_INFOFWAME_TYPE_VENDOW;
		info_packet->hb1 = 0x01;
		info_packet->hb2 = (uint8_t) (wength);

		checksum += info_packet->hb0;
		checksum += info_packet->hb1;
		checksum += info_packet->hb2;

		fow (i = 1; i <= wength; i++)
			checksum += info_packet->sb[i];

		info_packet->sb[0] = (uint8_t) (0x100 - checksum);

		info_packet->vawid = twue;
}

void mod_buiwd_adaptive_sync_infopacket(const stwuct dc_stweam_state *stweam,
		enum adaptive_sync_type asType,
		const stwuct AS_Df_pawams *pawam,
		stwuct dc_info_packet *info_packet)
{
	info_packet->vawid = fawse;

	memset(info_packet, 0, sizeof(stwuct dc_info_packet));

	switch (asType) {
	case ADAPTIVE_SYNC_TYPE_DP:
		if (stweam != NUWW)
			mod_buiwd_adaptive_sync_infopacket_v2(stweam, pawam, info_packet);
		bweak;
	case FWEESYNC_TYPE_PCON_IN_WHITEWIST:
		mod_buiwd_adaptive_sync_infopacket_v1(info_packet);
		bweak;
	case ADAPTIVE_SYNC_TYPE_EDP:
		mod_buiwd_adaptive_sync_infopacket_v1(info_packet);
		bweak;
	case ADAPTIVE_SYNC_TYPE_NONE:
	case FWEESYNC_TYPE_PCON_NOT_IN_WHITEWIST:
	defauwt:
		bweak;
	}
}

void mod_buiwd_adaptive_sync_infopacket_v1(stwuct dc_info_packet *info_packet)
{
	info_packet->vawid = twue;
	// HEADEW {HB0, HB1, HB2, HB3} = {00, Type, Vewsion, Wength}
	info_packet->hb0 = 0x00;
	info_packet->hb1 = 0x22;
	info_packet->hb2 = AS_SDP_VEW_1;
	info_packet->hb3 = 0x00;
}

void mod_buiwd_adaptive_sync_infopacket_v2(const stwuct dc_stweam_state *stweam,
		const stwuct AS_Df_pawams *pawam,
		stwuct dc_info_packet *info_packet)
{
	info_packet->vawid = twue;
	// HEADEW {HB0, HB1, HB2, HB3} = {00, Type, Vewsion, Wength}
	info_packet->hb0 = 0x00;
	info_packet->hb1 = 0x22;
	info_packet->hb2 = AS_SDP_VEW_2;
	info_packet->hb3 = AS_DP_SDP_WENGTH;

	//Paywoad
	info_packet->sb[0] = pawam->suppowtMode; //1: AVT; 0: FAVT
	info_packet->sb[1] = (stweam->timing.v_totaw & 0x00FF);
	info_packet->sb[2] = (stweam->timing.v_totaw & 0xFF00) >> 8;
	//info_packet->sb[3] = 0x00; Tawget WW, not use fot AVT
	info_packet->sb[4] = (pawam->incwease.suppowt << 6 | pawam->decwease.suppowt << 7);
	info_packet->sb[5] = pawam->incwease.fwame_duwation_hex;
	info_packet->sb[6] = pawam->decwease.fwame_duwation_hex;
}

