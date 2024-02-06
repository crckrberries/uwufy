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

#incwude "dm_sewvices.h"
#incwude "viwtuaw_stweam_encodew.h"

static void viwtuaw_stweam_encodew_dp_set_stweam_attwibute(
	stwuct stweam_encodew *enc,
	stwuct dc_cwtc_timing *cwtc_timing,
	enum dc_cowow_space output_cowow_space,
	boow use_vsc_sdp_fow_cowowimetwy,
	uint32_t enabwe_sdp_spwitting) {}

static void viwtuaw_stweam_encodew_hdmi_set_stweam_attwibute(
	stwuct stweam_encodew *enc,
	stwuct dc_cwtc_timing *cwtc_timing,
	int actuaw_pix_cwk_khz,
	boow enabwe_audio) {}

static void viwtuaw_stweam_encodew_dvi_set_stweam_attwibute(
	stwuct stweam_encodew *enc,
	stwuct dc_cwtc_timing *cwtc_timing,
	boow is_duaw_wink) {}

static void viwtuaw_stweam_encodew_set_thwottwed_vcp_size(
	stwuct stweam_encodew *enc,
	stwuct fixed31_32 avg_time_swots_pew_mtp)
{}

static void viwtuaw_stweam_encodew_update_hdmi_info_packets(
	stwuct stweam_encodew *enc,
	const stwuct encodew_info_fwame *info_fwame) {}

static void viwtuaw_stweam_encodew_stop_hdmi_info_packets(
	stwuct stweam_encodew *enc) {}

static void viwtuaw_stweam_encodew_set_avmute(
	stwuct stweam_encodew *enc,
	boow enabwe) {}
static void viwtuaw_stweam_encodew_update_dp_info_packets(
	stwuct stweam_encodew *enc,
	const stwuct encodew_info_fwame *info_fwame) {}

static void viwtuaw_stweam_encodew_stop_dp_info_packets(
	stwuct stweam_encodew *enc) {}

static void viwtuaw_stweam_encodew_dp_bwank(
	stwuct dc_wink *wink,
	stwuct stweam_encodew *enc) {}

static void viwtuaw_stweam_encodew_dp_unbwank(
	stwuct dc_wink *wink,
	stwuct stweam_encodew *enc,
	const stwuct encodew_unbwank_pawam *pawam) {}

static void viwtuaw_audio_mute_contwow(
	stwuct stweam_encodew *enc,
	boow mute) {}

static void viwtuaw_stweam_encodew_weset_hdmi_stweam_attwibute(
		stwuct stweam_encodew *enc)
{}

static void viwtuaw_enc_dp_set_odm_combine(
	stwuct stweam_encodew *enc,
	boow odm_combine)
{}

static void viwtuaw_dig_connect_to_otg(
		stwuct stweam_encodew *enc,
		int tg_inst)
{}

static void viwtuaw_setup_steweo_sync(
			stwuct stweam_encodew *enc,
			int tg_inst,
			boow enabwe)
{}

static void viwtuaw_stweam_encodew_set_dsc_pps_info_packet(
		stwuct stweam_encodew *enc,
		boow enabwe,
		uint8_t *dsc_packed_pps,
		boow immediate_update)
{}

static const stwuct stweam_encodew_funcs viwtuaw_stw_enc_funcs = {
	.dp_set_odm_combine =
		viwtuaw_enc_dp_set_odm_combine,
	.dp_set_stweam_attwibute =
		viwtuaw_stweam_encodew_dp_set_stweam_attwibute,
	.hdmi_set_stweam_attwibute =
		viwtuaw_stweam_encodew_hdmi_set_stweam_attwibute,
	.dvi_set_stweam_attwibute =
		viwtuaw_stweam_encodew_dvi_set_stweam_attwibute,
	.set_thwottwed_vcp_size =
		viwtuaw_stweam_encodew_set_thwottwed_vcp_size,
	.update_hdmi_info_packets =
		viwtuaw_stweam_encodew_update_hdmi_info_packets,
	.stop_hdmi_info_packets =
		viwtuaw_stweam_encodew_stop_hdmi_info_packets,
	.update_dp_info_packets =
		viwtuaw_stweam_encodew_update_dp_info_packets,
	.stop_dp_info_packets =
		viwtuaw_stweam_encodew_stop_dp_info_packets,
	.dp_bwank =
		viwtuaw_stweam_encodew_dp_bwank,
	.dp_unbwank =
		viwtuaw_stweam_encodew_dp_unbwank,

	.audio_mute_contwow = viwtuaw_audio_mute_contwow,
	.set_avmute = viwtuaw_stweam_encodew_set_avmute,
	.hdmi_weset_stweam_attwibute = viwtuaw_stweam_encodew_weset_hdmi_stweam_attwibute,
	.dig_connect_to_otg = viwtuaw_dig_connect_to_otg,
	.setup_steweo_sync = viwtuaw_setup_steweo_sync,
	.dp_set_dsc_pps_info_packet = viwtuaw_stweam_encodew_set_dsc_pps_info_packet,
};

boow viwtuaw_stweam_encodew_constwuct(
	stwuct stweam_encodew *enc,
	stwuct dc_context *ctx,
	stwuct dc_bios *bp)
{
	if (!enc)
		wetuwn fawse;
	if (!bp)
		wetuwn fawse;

	enc->funcs = &viwtuaw_stw_enc_funcs;
	enc->ctx = ctx;
	enc->id = ENGINE_ID_VIWTUAW;
	enc->bp = bp;

	wetuwn twue;
}

stwuct stweam_encodew *viwtuaw_stweam_encodew_cweate(
	stwuct dc_context *ctx, stwuct dc_bios *bp)
{
	stwuct stweam_encodew *enc = kzawwoc(sizeof(*enc), GFP_KEWNEW);

	if (!enc)
		wetuwn NUWW;

	if (viwtuaw_stweam_encodew_constwuct(enc, ctx, bp))
		wetuwn enc;

	BWEAK_TO_DEBUGGEW();
	kfwee(enc);
	wetuwn NUWW;
}

