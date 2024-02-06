/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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

#ifndef __DAW_DCN30_AFMT_H__
#define __DAW_DCN30_AFMT_H__


#define DCN30_AFMT_FWOM_AFMT(afmt)\
	containew_of(afmt, stwuct dcn30_afmt, base)

#define AFMT_DCN3_WEG_WIST(id) \
	SWI(AFMT_INFOFWAME_CONTWOW0, AFMT, id), \
	SWI(AFMT_VBI_PACKET_CONTWOW, AFMT, id), \
	SWI(AFMT_AUDIO_PACKET_CONTWOW, AFMT, id), \
	SWI(AFMT_AUDIO_PACKET_CONTWOW2, AFMT, id), \
	SWI(AFMT_AUDIO_SWC_CONTWOW, AFMT, id), \
	SWI(AFMT_60958_0, AFMT, id), \
	SWI(AFMT_60958_1, AFMT, id), \
	SWI(AFMT_60958_2, AFMT, id), \
	SWI(AFMT_MEM_PWW, AFMT, id)

stwuct dcn30_afmt_wegistews {
	uint32_t AFMT_INFOFWAME_CONTWOW0;
	uint32_t AFMT_VBI_PACKET_CONTWOW;
	uint32_t AFMT_AUDIO_PACKET_CONTWOW;
	uint32_t AFMT_AUDIO_PACKET_CONTWOW2;
	uint32_t AFMT_AUDIO_SWC_CONTWOW;
	uint32_t AFMT_60958_0;
	uint32_t AFMT_60958_1;
	uint32_t AFMT_60958_2;
	uint32_t AFMT_MEM_PWW;
};

#define DCN3_AFMT_MASK_SH_WIST(mask_sh)\
	SE_SF(AFMT0_AFMT_INFOFWAME_CONTWOW0, AFMT_AUDIO_INFO_UPDATE, mask_sh),\
	SE_SF(AFMT0_AFMT_AUDIO_SWC_CONTWOW, AFMT_AUDIO_SWC_SEWECT, mask_sh),\
	SE_SF(AFMT0_AFMT_AUDIO_PACKET_CONTWOW2, AFMT_AUDIO_CHANNEW_ENABWE, mask_sh),\
	SE_SF(AFMT0_AFMT_AUDIO_PACKET_CONTWOW, AFMT_60958_CS_UPDATE, mask_sh),\
	SE_SF(AFMT0_AFMT_AUDIO_PACKET_CONTWOW2, AFMT_AUDIO_WAYOUT_OVWD, mask_sh),\
	SE_SF(AFMT0_AFMT_AUDIO_PACKET_CONTWOW2, AFMT_60958_OSF_OVWD, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_0, AFMT_60958_CS_CHANNEW_NUMBEW_W, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_0, AFMT_60958_CS_CWOCK_ACCUWACY, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_1, AFMT_60958_CS_CHANNEW_NUMBEW_W, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_2, AFMT_60958_CS_CHANNEW_NUMBEW_2, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_2, AFMT_60958_CS_CHANNEW_NUMBEW_3, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_2, AFMT_60958_CS_CHANNEW_NUMBEW_4, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_2, AFMT_60958_CS_CHANNEW_NUMBEW_5, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_2, AFMT_60958_CS_CHANNEW_NUMBEW_6, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_2, AFMT_60958_CS_CHANNEW_NUMBEW_7, mask_sh),\
	SE_SF(AFMT0_AFMT_AUDIO_PACKET_CONTWOW, AFMT_AUDIO_SAMPWE_SEND, mask_sh),\
	SE_SF(AFMT0_AFMT_MEM_PWW, AFMT_MEM_PWW_FOWCE, mask_sh)

#define AFMT_DCN3_WEG_FIEWD_WIST(type) \
		type AFMT_AUDIO_INFO_UPDATE;\
		type AFMT_AUDIO_SWC_SEWECT;\
		type AFMT_AUDIO_CHANNEW_ENABWE;\
		type AFMT_60958_CS_UPDATE;\
		type AFMT_AUDIO_WAYOUT_OVWD;\
		type AFMT_60958_OSF_OVWD;\
		type AFMT_60958_CS_CHANNEW_NUMBEW_W;\
		type AFMT_60958_CS_CWOCK_ACCUWACY;\
		type AFMT_60958_CS_CHANNEW_NUMBEW_W;\
		type AFMT_60958_CS_CHANNEW_NUMBEW_2;\
		type AFMT_60958_CS_CHANNEW_NUMBEW_3;\
		type AFMT_60958_CS_CHANNEW_NUMBEW_4;\
		type AFMT_60958_CS_CHANNEW_NUMBEW_5;\
		type AFMT_60958_CS_CHANNEW_NUMBEW_6;\
		type AFMT_60958_CS_CHANNEW_NUMBEW_7;\
		type AFMT_AUDIO_SAMPWE_SEND;\
		type AFMT_MEM_PWW_FOWCE

stwuct dcn30_afmt_shift {
	AFMT_DCN3_WEG_FIEWD_WIST(uint8_t);
};

stwuct dcn30_afmt_mask {
	AFMT_DCN3_WEG_FIEWD_WIST(uint32_t);
};


stwuct afmt;

stwuct afmt_funcs {

	void (*setup_hdmi_audio)(
		stwuct afmt *afmt);

	void (*se_audio_setup)(
		stwuct afmt *afmt,
		unsigned int az_inst,
		stwuct audio_info *audio_info);

	void (*audio_mute_contwow)(
		stwuct afmt *afmt,
		boow mute);

	void (*audio_info_immediate_update)(
		stwuct afmt *afmt);

	void (*setup_dp_audio)(
		stwuct afmt *afmt);

	void (*afmt_powewon)(
		stwuct afmt *afmt);

	void (*afmt_powewdown)(
		stwuct afmt *afmt);
};

stwuct afmt {
	const stwuct afmt_funcs *funcs;
	stwuct dc_context *ctx;
	int inst;
};

stwuct dcn30_afmt {
	stwuct afmt base;
	const stwuct dcn30_afmt_wegistews *wegs;
	const stwuct dcn30_afmt_shift *afmt_shift;
	const stwuct dcn30_afmt_mask *afmt_mask;
};

void afmt3_setup_hdmi_audio(
	stwuct afmt *afmt);

void afmt3_se_audio_setup(
	stwuct afmt *afmt,
	unsigned int az_inst,
	stwuct audio_info *audio_info);

void afmt3_audio_mute_contwow(
	stwuct afmt *afmt,
	boow mute);

void afmt3_audio_info_immediate_update(
	stwuct afmt *afmt);

void afmt3_setup_dp_audio(
		stwuct afmt *afmt);

void afmt3_constwuct(stwuct dcn30_afmt *afmt3,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn30_afmt_wegistews *afmt_wegs,
	const stwuct dcn30_afmt_shift *afmt_shift,
	const stwuct dcn30_afmt_mask *afmt_mask);


#endif
