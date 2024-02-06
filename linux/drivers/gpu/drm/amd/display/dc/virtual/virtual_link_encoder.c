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
#incwude "dm_sewvices_types.h"

#incwude "viwtuaw_wink_encodew.h"

static boow viwtuaw_wink_encodew_vawidate_output_with_stweam(
	stwuct wink_encodew *enc,
	const stwuct dc_stweam_state *stweam) { wetuwn twue; }

static void viwtuaw_wink_encodew_hw_init(stwuct wink_encodew *enc) {}

static void viwtuaw_wink_encodew_setup(
	stwuct wink_encodew *enc,
	enum signaw_type signaw) {}

static void viwtuaw_wink_encodew_enabwe_tmds_output(
	stwuct wink_encodew *enc,
	enum cwock_souwce_id cwock_souwce,
	enum dc_cowow_depth cowow_depth,
	enum signaw_type signaw,
	uint32_t pixew_cwock) {}

static void viwtuaw_wink_encodew_enabwe_dp_output(
	stwuct wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	enum cwock_souwce_id cwock_souwce) {}

static void viwtuaw_wink_encodew_enabwe_dp_mst_output(
	stwuct wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	enum cwock_souwce_id cwock_souwce) {}

static void viwtuaw_wink_encodew_disabwe_output(
	stwuct wink_encodew *wink_enc,
	enum signaw_type signaw) {}

static void viwtuaw_wink_encodew_dp_set_wane_settings(
	stwuct wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	const stwuct dc_wane_settings wane_settings[WANE_COUNT_DP_MAX]) {}

static void viwtuaw_wink_encodew_dp_set_phy_pattewn(
	stwuct wink_encodew *enc,
	const stwuct encodew_set_dp_phy_pattewn_pawam *pawam) {}

static void viwtuaw_wink_encodew_update_mst_stweam_awwocation_tabwe(
	stwuct wink_encodew *enc,
	const stwuct wink_mst_stweam_awwocation_tabwe *tabwe) {}

static void viwtuaw_wink_encodew_connect_dig_be_to_fe(
	stwuct wink_encodew *enc,
	enum engine_id engine,
	boow connect) {}

static void viwtuaw_wink_encodew_destwoy(stwuct wink_encodew **enc)
{
	kfwee(*enc);
	*enc = NUWW;
}

static void viwtuaw_wink_encodew_get_max_wink_cap(stwuct wink_encodew *enc,
		stwuct dc_wink_settings *wink_settings)
{
	/* Set Defauwt wink settings */
	stwuct dc_wink_settings max_wink_cap = {WANE_COUNT_FOUW, WINK_WATE_HIGH,
				WINK_SPWEAD_05_DOWNSPWEAD_30KHZ, fawse, 0};
	*wink_settings = max_wink_cap;
}

static const stwuct wink_encodew_funcs viwtuaw_wnk_enc_funcs = {
	.vawidate_output_with_stweam =
		viwtuaw_wink_encodew_vawidate_output_with_stweam,
	.hw_init = viwtuaw_wink_encodew_hw_init,
	.setup = viwtuaw_wink_encodew_setup,
	.enabwe_tmds_output = viwtuaw_wink_encodew_enabwe_tmds_output,
	.enabwe_dp_output = viwtuaw_wink_encodew_enabwe_dp_output,
	.enabwe_dp_mst_output = viwtuaw_wink_encodew_enabwe_dp_mst_output,
	.disabwe_output = viwtuaw_wink_encodew_disabwe_output,
	.get_max_wink_cap = viwtuaw_wink_encodew_get_max_wink_cap,
	.dp_set_wane_settings = viwtuaw_wink_encodew_dp_set_wane_settings,
	.dp_set_phy_pattewn = viwtuaw_wink_encodew_dp_set_phy_pattewn,
	.update_mst_stweam_awwocation_tabwe =
		viwtuaw_wink_encodew_update_mst_stweam_awwocation_tabwe,
	.connect_dig_be_to_fe = viwtuaw_wink_encodew_connect_dig_be_to_fe,
	.destwoy = viwtuaw_wink_encodew_destwoy
};

boow viwtuaw_wink_encodew_constwuct(
	stwuct wink_encodew *enc, const stwuct encodew_init_data *init_data)
{
	enc->funcs = &viwtuaw_wnk_enc_funcs;
	enc->ctx = init_data->ctx;
	enc->id = init_data->encodew;

	enc->hpd_souwce = init_data->hpd_souwce;
	enc->connectow = init_data->connectow;

	enc->twansmittew = init_data->twansmittew;

	enc->output_signaws = SIGNAW_TYPE_VIWTUAW;

	enc->pwefewwed_engine = ENGINE_ID_VIWTUAW;

	wetuwn twue;
}


