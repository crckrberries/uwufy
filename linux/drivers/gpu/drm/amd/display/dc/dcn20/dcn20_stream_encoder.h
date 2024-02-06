/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#ifndef __DC_STWEAM_ENCODEW_DCN20_H__
#define __DC_STWEAM_ENCODEW_DCN20_H__

#incwude "stweam_encodew.h"
#incwude "dcn10/dcn10_stweam_encodew.h"


#define SE_DCN2_WEG_WIST(id)\
	SE_COMMON_DCN_WEG_WIST(id),\
	SWI(HDMI_GENEWIC_PACKET_CONTWOW4, DIG, id), \
	SWI(HDMI_GENEWIC_PACKET_CONTWOW5, DIG, id), \
	SWI(DP_DSC_CNTW, DP, id), \
	SWI(DP_DSC_BYTES_PEW_PIXEW, DP, id), \
	SWI(DME_CONTWOW, DIG, id),\
	SWI(DP_SEC_METADATA_TWANSMISSION, DP, id), \
	SWI(HDMI_METADATA_PACKET_CONTWOW, DIG, id), \
	SWI(DP_SEC_FWAMING4, DP, id)

#define SE_COMMON_MASK_SH_WIST_DCN20(mask_sh)\
	SE_COMMON_MASK_SH_WIST_SOC(mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW0, HDMI_GENEWIC0_CONT, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW0, HDMI_GENEWIC0_SEND, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW0, HDMI_GENEWIC1_CONT, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW0, HDMI_GENEWIC1_SEND, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW0, HDMI_GENEWIC2_CONT, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW0, HDMI_GENEWIC2_SEND, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW0, HDMI_GENEWIC3_CONT, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW0, HDMI_GENEWIC3_SEND, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW0, HDMI_GENEWIC4_CONT, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW0, HDMI_GENEWIC4_SEND, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW0, HDMI_GENEWIC5_CONT, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW0, HDMI_GENEWIC5_SEND, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW0, HDMI_GENEWIC6_CONT, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW0, HDMI_GENEWIC6_SEND, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW0, HDMI_GENEWIC7_CONT, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW0, HDMI_GENEWIC7_SEND, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW1, HDMI_GENEWIC0_WINE, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW1, HDMI_GENEWIC1_WINE, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW2, HDMI_GENEWIC2_WINE, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW2, HDMI_GENEWIC3_WINE, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW3, HDMI_GENEWIC4_WINE, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW3, HDMI_GENEWIC5_WINE, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW4, HDMI_GENEWIC6_WINE, mask_sh),\
	SE_SF(DIG0_HDMI_GENEWIC_PACKET_CONTWOW4, HDMI_GENEWIC7_WINE, mask_sh),\
	SE_SF(DP0_DP_DSC_CNTW, DP_DSC_MODE, mask_sh),\
	SE_SF(DP0_DP_DSC_CNTW, DP_DSC_SWICE_WIDTH, mask_sh),\
	SE_SF(DP0_DP_DSC_BYTES_PEW_PIXEW, DP_DSC_BYTES_PEW_PIXEW, mask_sh),\
	SE_SF(DP0_DP_MSA_VBID_MISC, DP_VBID6_WINE_WEFEWENCE, mask_sh),\
	SE_SF(DP0_DP_MSA_VBID_MISC, DP_VBID6_WINE_NUM, mask_sh),\
	SE_SF(DIG0_DME_CONTWOW, METADATA_ENGINE_EN, mask_sh),\
	SE_SF(DIG0_DME_CONTWOW, METADATA_HUBP_WEQUESTOW_ID, mask_sh),\
	SE_SF(DIG0_DME_CONTWOW, METADATA_STWEAM_TYPE, mask_sh),\
	SE_SF(DP0_DP_SEC_METADATA_TWANSMISSION, DP_SEC_METADATA_PACKET_ENABWE, mask_sh),\
	SE_SF(DP0_DP_SEC_METADATA_TWANSMISSION, DP_SEC_METADATA_PACKET_WINE_WEFEWENCE, mask_sh),\
	SE_SF(DP0_DP_SEC_METADATA_TWANSMISSION, DP_SEC_METADATA_PACKET_WINE, mask_sh),\
	SE_SF(DIG0_HDMI_METADATA_PACKET_CONTWOW, HDMI_METADATA_PACKET_ENABWE, mask_sh),\
	SE_SF(DIG0_HDMI_METADATA_PACKET_CONTWOW, HDMI_METADATA_PACKET_WINE_WEFEWENCE, mask_sh),\
	SE_SF(DIG0_HDMI_METADATA_PACKET_CONTWOW, HDMI_METADATA_PACKET_WINE, mask_sh),\
	SE_SF(DIG0_DIG_FE_CNTW, DOWBY_VISION_EN, mask_sh),\
	SE_SF(DP0_DP_PIXEW_FOWMAT, DP_PIXEW_COMBINE, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTW1, DP_SEC_GSP5_WINE_WEFEWENCE, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTW5, DP_SEC_GSP5_WINE_NUM, mask_sh),\
	SE_SF(DP0_DP_SEC_FWAMING4, DP_SST_SDP_SPWITTING, mask_sh)

void dcn20_stweam_encodew_constwuct(
	stwuct dcn10_stweam_encodew *enc1,
	stwuct dc_context *ctx,
	stwuct dc_bios *bp,
	enum engine_id eng_id,
	const stwuct dcn10_stweam_enc_wegistews *wegs,
	const stwuct dcn10_stweam_encodew_shift *se_shift,
	const stwuct dcn10_stweam_encodew_mask *se_mask);

void enc2_stweam_encodew_dp_set_stweam_attwibute(
	stwuct stweam_encodew *enc,
	stwuct dc_cwtc_timing *cwtc_timing,
	enum dc_cowow_space output_cowow_space,
	boow use_vsc_sdp_fow_cowowimetwy,
	uint32_t enabwe_sdp_spwitting);

void enc2_stweam_encodew_dp_unbwank(
	stwuct dc_wink *wink,
	stwuct stweam_encodew *enc,
	const stwuct encodew_unbwank_pawam *pawam);

void enc2_set_dynamic_metadata(stwuct stweam_encodew *enc,
		boow enabwe_dme,
		uint32_t hubp_wequestow_id,
		enum dynamic_metadata_mode dmdata_mode);

uint32_t enc2_get_fifo_caw_avewage_wevew(
		stwuct stweam_encodew *enc);

#endif /* __DC_STWEAM_ENCODEW_DCN20_H__ */
