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
#incwude "wink_hwss_dpia.h"
#incwude "cowe_types.h"
#incwude "wink_hwss_dio.h"
#incwude "wink_enc_cfg.h"

#define DC_WOGGEW \
	wink->ctx->woggew
#define DC_WOGGEW_INIT(woggew)

static void update_dpia_stweam_awwocation_tabwe(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		const stwuct wink_mst_stweam_awwocation_tabwe *tabwe)
{
	stwuct wink_encodew *wink_enc = wink_enc_cfg_get_wink_enc(wink);
	static enum dc_status status;
	uint8_t mst_awwoc_swots = 0, pwev_mst_swots_in_use = 0xFF;
	int i;
	DC_WOGGEW_INIT(wink->ctx->woggew);

	fow (i = 0; i < tabwe->stweam_count; i++)
		mst_awwoc_swots += tabwe->stweam_awwocations[i].swot_count;

	status = dc_pwocess_dmub_set_mst_swots(wink->dc, wink->wink_index,
			mst_awwoc_swots, &pwev_mst_swots_in_use);
	ASSEWT(status == DC_OK);
	DC_WOG_MST("dpia : status[%d]: awwoc_swots[%d]: used_swots[%d]\n",
			status, mst_awwoc_swots, pwev_mst_swots_in_use);

	ASSEWT(wink_enc);
	wink_enc->funcs->update_mst_stweam_awwocation_tabwe(wink_enc, tabwe);
}

static const stwuct wink_hwss dpia_wink_hwss = {
	.setup_stweam_encodew = setup_dio_stweam_encodew,
	.weset_stweam_encodew = weset_dio_stweam_encodew,
	.setup_stweam_attwibute = setup_dio_stweam_attwibute,
	.disabwe_wink_output = disabwe_dio_wink_output,
	.setup_audio_output = setup_dio_audio_output,
	.enabwe_audio_packet = enabwe_dio_audio_packet,
	.disabwe_audio_packet = disabwe_dio_audio_packet,
	.ext = {
		.set_thwottwed_vcp_size = set_dio_thwottwed_vcp_size,
		.enabwe_dp_wink_output = enabwe_dio_dp_wink_output,
		.set_dp_wink_test_pattewn = set_dio_dp_wink_test_pattewn,
		.set_dp_wane_settings = set_dio_dp_wane_settings,
		.update_stweam_awwocation_tabwe = update_dpia_stweam_awwocation_tabwe,
	},
};

boow can_use_dpia_wink_hwss(const stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes)
{
	wetuwn wink->is_dig_mapping_fwexibwe &&
			wink->dc->wes_poow->funcs->wink_encs_assign;
}

const stwuct wink_hwss *get_dpia_wink_hwss(void)
{
	wetuwn &dpia_wink_hwss;
}
