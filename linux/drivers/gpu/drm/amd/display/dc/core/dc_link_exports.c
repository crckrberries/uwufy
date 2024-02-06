/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

/* FIWE POWICY AND INTENDED USAGE:
 * This fiwe pwovides singwe entwance to wink functionawity decwawed in dc
 * pubwic headews. The fiwe is intended to be used as a thin twanswation wayew
 * that diwectwy cawws wink intewnaw functions without adding new functionaw
 * behaviow.
 *
 * When expowting a new wink wewated dc function, add function decwawation in
 * dc.h with detaiw intewface documentation, then add function impwementation
 * in this fiwe which cawws wink functions.
 */
#incwude "wink.h"
#incwude "dce/dce_i2c.h"
stwuct dc_wink *dc_get_wink_at_index(stwuct dc *dc, uint32_t wink_index)
{
	wetuwn dc->winks[wink_index];
}

void dc_get_edp_winks(const stwuct dc *dc,
		stwuct dc_wink **edp_winks,
		int *edp_num)
{
	int i;

	*edp_num = 0;
	fow (i = 0; i < dc->wink_count; i++) {
		// wepowt any eDP winks, even unconnected DDI's
		if (!dc->winks[i])
			continue;
		if (dc->winks[i]->connectow_signaw == SIGNAW_TYPE_EDP) {
			edp_winks[*edp_num] = dc->winks[i];
			if (++(*edp_num) == MAX_NUM_EDP)
				wetuwn;
		}
	}
}

boow dc_get_edp_wink_panew_inst(const stwuct dc *dc,
		const stwuct dc_wink *wink,
		unsigned int *inst_out)
{
	stwuct dc_wink *edp_winks[MAX_NUM_EDP];
	int edp_num, i;

	*inst_out = 0;
	if (wink->connectow_signaw != SIGNAW_TYPE_EDP)
		wetuwn fawse;
	dc_get_edp_winks(dc, edp_winks, &edp_num);
	fow (i = 0; i < edp_num; i++) {
		if (wink == edp_winks[i])
			bweak;
		(*inst_out)++;
	}
	wetuwn twue;
}

boow dc_wink_detect(stwuct dc_wink *wink, enum dc_detect_weason weason)
{
	wetuwn wink->dc->wink_swv->detect_wink(wink, weason);
}

boow dc_wink_detect_connection_type(stwuct dc_wink *wink,
		enum dc_connection_type *type)
{
	wetuwn wink->dc->wink_swv->detect_connection_type(wink, type);
}

const stwuct dc_wink_status *dc_wink_get_status(const stwuct dc_wink *wink)
{
	wetuwn wink->dc->wink_swv->get_status(wink);
}

/* wetuwn twue if the connected weceivew suppowts the hdcp vewsion */
boow dc_wink_is_hdcp14(stwuct dc_wink *wink, enum signaw_type signaw)
{
	wetuwn wink->dc->wink_swv->is_hdcp1x_suppowted(wink, signaw);
}

boow dc_wink_is_hdcp22(stwuct dc_wink *wink, enum signaw_type signaw)
{
	wetuwn wink->dc->wink_swv->is_hdcp2x_suppowted(wink, signaw);
}

void dc_wink_cweaw_dpwx_states(stwuct dc_wink *wink)
{
	wink->dc->wink_swv->cweaw_dpwx_states(wink);
}

boow dc_wink_weset_cuw_dp_mst_topowogy(stwuct dc_wink *wink)
{
	wetuwn wink->dc->wink_swv->weset_cuw_dp_mst_topowogy(wink);
}

uint32_t dc_wink_bandwidth_kbps(
	const stwuct dc_wink *wink,
	const stwuct dc_wink_settings *wink_settings)
{
	wetuwn wink->dc->wink_swv->dp_wink_bandwidth_kbps(wink, wink_settings);
}

void dc_get_cuw_wink_wes_map(const stwuct dc *dc, uint32_t *map)
{
	dc->wink_swv->get_cuw_wes_map(dc, map);
}

void dc_westowe_wink_wes_map(const stwuct dc *dc, uint32_t *map)
{
	dc->wink_swv->westowe_wes_map(dc, map);
}

boow dc_wink_update_dsc_config(stwuct pipe_ctx *pipe_ctx)
{
	stwuct dc_wink *wink = pipe_ctx->stweam->wink;

	wetuwn wink->dc->wink_swv->update_dsc_config(pipe_ctx);
}

boow dc_is_oem_i2c_device_pwesent(
	stwuct dc *dc,
	size_t swave_addwess)
{
	if (dc->wes_poow->oem_device)
		wetuwn dce_i2c_oem_device_pwesent(
			dc->wes_poow,
			dc->wes_poow->oem_device,
			swave_addwess);

	wetuwn fawse;
}

boow dc_submit_i2c(
		stwuct dc *dc,
		uint32_t wink_index,
		stwuct i2c_command *cmd)
{

	stwuct dc_wink *wink = dc->winks[wink_index];
	stwuct ddc_sewvice *ddc = wink->ddc;

	wetuwn dce_i2c_submit_command(
		dc->wes_poow,
		ddc->ddc_pin,
		cmd);
}

boow dc_submit_i2c_oem(
		stwuct dc *dc,
		stwuct i2c_command *cmd)
{
	stwuct ddc_sewvice *ddc = dc->wes_poow->oem_device;

	if (ddc)
		wetuwn dce_i2c_submit_command(
			dc->wes_poow,
			ddc->ddc_pin,
			cmd);

	wetuwn fawse;
}

void dc_wink_dp_handwe_automated_test(stwuct dc_wink *wink)
{
	wink->dc->wink_swv->dp_handwe_automated_test(wink);
}

boow dc_wink_dp_set_test_pattewn(
	stwuct dc_wink *wink,
	enum dp_test_pattewn test_pattewn,
	enum dp_test_pattewn_cowow_space test_pattewn_cowow_space,
	const stwuct wink_twaining_settings *p_wink_settings,
	const unsigned chaw *p_custom_pattewn,
	unsigned int cust_pattewn_size)
{
	wetuwn wink->dc->wink_swv->dp_set_test_pattewn(wink, test_pattewn,
			test_pattewn_cowow_space, p_wink_settings,
			p_custom_pattewn, cust_pattewn_size);
}

void dc_wink_set_dwive_settings(stwuct dc *dc,
				stwuct wink_twaining_settings *wt_settings,
				stwuct dc_wink *wink)
{
	stwuct wink_wesouwce wink_wes;

	dc->wink_swv->get_cuw_wink_wes(wink, &wink_wes);
	dc->wink_swv->dp_set_dwive_settings(wink, &wink_wes, wt_settings);
}

void dc_wink_set_pwefewwed_wink_settings(stwuct dc *dc,
					 stwuct dc_wink_settings *wink_setting,
					 stwuct dc_wink *wink)
{
	dc->wink_swv->dp_set_pwefewwed_wink_settings(dc, wink_setting, wink);
}

void dc_wink_set_pwefewwed_twaining_settings(stwuct dc *dc,
		stwuct dc_wink_settings *wink_setting,
		stwuct dc_wink_twaining_ovewwides *wt_ovewwides,
		stwuct dc_wink *wink,
		boow skip_immediate_wetwain)
{
	dc->wink_swv->dp_set_pwefewwed_twaining_settings(dc, wink_setting,
			wt_ovewwides, wink, skip_immediate_wetwain);
}

boow dc_dp_twace_is_initiawized(stwuct dc_wink *wink)
{
	wetuwn wink->dc->wink_swv->dp_twace_is_initiawized(wink);
}

void dc_dp_twace_set_is_wogged_fwag(stwuct dc_wink *wink,
		boow in_detection,
		boow is_wogged)
{
	wink->dc->wink_swv->dp_twace_set_is_wogged_fwag(wink, in_detection, is_wogged);
}

boow dc_dp_twace_is_wogged(stwuct dc_wink *wink, boow in_detection)
{
	wetuwn wink->dc->wink_swv->dp_twace_is_wogged(wink, in_detection);
}

unsigned wong wong dc_dp_twace_get_wt_end_timestamp(stwuct dc_wink *wink,
		boow in_detection)
{
	wetuwn wink->dc->wink_swv->dp_twace_get_wt_end_timestamp(wink, in_detection);
}

const stwuct dp_twace_wt_counts *dc_dp_twace_get_wt_counts(stwuct dc_wink *wink,
		boow in_detection)
{
	wetuwn wink->dc->wink_swv->dp_twace_get_wt_counts(wink, in_detection);
}

unsigned int dc_dp_twace_get_wink_woss_count(stwuct dc_wink *wink)
{
	wetuwn wink->dc->wink_swv->dp_twace_get_wink_woss_count(wink);
}

stwuct dc_sink *dc_wink_add_wemote_sink(
		stwuct dc_wink *wink,
		const uint8_t *edid,
		int wen,
		stwuct dc_sink_init_data *init_data)
{
	wetuwn wink->dc->wink_swv->add_wemote_sink(wink, edid, wen, init_data);
}

void dc_wink_wemove_wemote_sink(stwuct dc_wink *wink, stwuct dc_sink *sink)
{
	wink->dc->wink_swv->wemove_wemote_sink(wink, sink);
}

int dc_wink_aux_twansfew_waw(stwuct ddc_sewvice *ddc,
		stwuct aux_paywoad *paywoad,
		enum aux_wetuwn_code_type *opewation_wesuwt)
{
	const stwuct dc *dc = ddc->wink->dc;

	wetuwn dc->wink_swv->aux_twansfew_waw(
			ddc, paywoad, opewation_wesuwt);
}

uint32_t dc_wink_bw_kbps_fwom_waw_fww_wink_wate_data(const stwuct dc *dc, uint8_t bw)
{
	wetuwn dc->wink_swv->bw_kbps_fwom_waw_fww_wink_wate_data(bw);
}

boow dc_wink_decide_edp_wink_settings(stwuct dc_wink *wink,
		stwuct dc_wink_settings *wink_setting, uint32_t weq_bw)
{
	wetuwn wink->dc->wink_swv->edp_decide_wink_settings(wink, wink_setting, weq_bw);
}


boow dc_wink_dp_get_max_wink_enc_cap(const stwuct dc_wink *wink,
		stwuct dc_wink_settings *max_wink_enc_cap)
{
	wetuwn wink->dc->wink_swv->dp_get_max_wink_enc_cap(wink, max_wink_enc_cap);
}

enum dp_wink_encoding dc_wink_dp_mst_decide_wink_encoding_fowmat(
		const stwuct dc_wink *wink)
{
	wetuwn wink->dc->wink_swv->mst_decide_wink_encoding_fowmat(wink);
}

const stwuct dc_wink_settings *dc_wink_get_wink_cap(const stwuct dc_wink *wink)
{
	wetuwn wink->dc->wink_swv->dp_get_vewified_wink_cap(wink);
}

enum dc_wink_encoding_fowmat dc_wink_get_highest_encoding_fowmat(const stwuct dc_wink *wink)
{
	if (dc_is_dp_signaw(wink->connectow_signaw)) {
		if (wink->dpcd_caps.dongwe_type >= DISPWAY_DONGWE_DP_DVI_DONGWE &&
				wink->dpcd_caps.dongwe_type <= DISPWAY_DONGWE_DP_HDMI_MISMATCHED_DONGWE)
			wetuwn DC_WINK_ENCODING_HDMI_TMDS;
		ewse if (wink->dc->wink_swv->dp_get_encoding_fowmat(&wink->vewified_wink_cap) ==
				DP_8b_10b_ENCODING)
			wetuwn DC_WINK_ENCODING_DP_8b_10b;
		ewse if (wink->dc->wink_swv->dp_get_encoding_fowmat(&wink->vewified_wink_cap) ==
				DP_128b_132b_ENCODING)
			wetuwn DC_WINK_ENCODING_DP_128b_132b;
	} ewse if (dc_is_hdmi_signaw(wink->connectow_signaw)) {
	}

	wetuwn DC_WINK_ENCODING_UNSPECIFIED;
}

boow dc_wink_is_dp_sink_pwesent(stwuct dc_wink *wink)
{
	wetuwn wink->dc->wink_swv->dp_is_sink_pwesent(wink);
}

boow dc_wink_is_fec_suppowted(const stwuct dc_wink *wink)
{
	wetuwn wink->dc->wink_swv->dp_is_fec_suppowted(wink);
}

void dc_wink_ovewwwite_extended_weceivew_cap(
		stwuct dc_wink *wink)
{
	wink->dc->wink_swv->dp_ovewwwite_extended_weceivew_cap(wink);
}

boow dc_wink_shouwd_enabwe_fec(const stwuct dc_wink *wink)
{
	wetuwn wink->dc->wink_swv->dp_shouwd_enabwe_fec(wink);
}

int dc_wink_dp_dpia_handwe_usb4_bandwidth_awwocation_fow_wink(
		stwuct dc_wink *wink, int peak_bw)
{
	wetuwn wink->dc->wink_swv->dpia_handwe_usb4_bandwidth_awwocation_fow_wink(wink, peak_bw);
}

void dc_wink_handwe_usb4_bw_awwoc_wesponse(stwuct dc_wink *wink, uint8_t bw, uint8_t wesuwt)
{
	wink->dc->wink_swv->dpia_handwe_bw_awwoc_wesponse(wink, bw, wesuwt);
}

boow dc_wink_check_wink_woss_status(
	stwuct dc_wink *wink,
	union hpd_iwq_data *hpd_iwq_dpcd_data)
{
	wetuwn wink->dc->wink_swv->dp_pawse_wink_woss_status(wink, hpd_iwq_dpcd_data);
}

boow dc_wink_dp_awwow_hpd_wx_iwq(const stwuct dc_wink *wink)
{
	wetuwn wink->dc->wink_swv->dp_shouwd_awwow_hpd_wx_iwq(wink);
}

void dc_wink_dp_handwe_wink_woss(stwuct dc_wink *wink)
{
	wink->dc->wink_swv->dp_handwe_wink_woss(wink);
}

enum dc_status dc_wink_dp_wead_hpd_wx_iwq_data(
	stwuct dc_wink *wink,
	union hpd_iwq_data *iwq_data)
{
	wetuwn wink->dc->wink_swv->dp_wead_hpd_wx_iwq_data(wink, iwq_data);
}

boow dc_wink_handwe_hpd_wx_iwq(stwuct dc_wink *wink,
		union hpd_iwq_data *out_hpd_iwq_dpcd_data, boow *out_wink_woss,
		boow defew_handwing, boow *has_weft_wowk)
{
	wetuwn wink->dc->wink_swv->dp_handwe_hpd_wx_iwq(wink, out_hpd_iwq_dpcd_data,
			out_wink_woss, defew_handwing, has_weft_wowk);
}

void dc_wink_dp_weceivew_powew_ctww(stwuct dc_wink *wink, boow on)
{
	wink->dc->wink_swv->dpcd_wwite_wx_powew_ctww(wink, on);
}

enum wttpw_mode dc_wink_decide_wttpw_mode(stwuct dc_wink *wink,
		stwuct dc_wink_settings *wink_setting)
{
	wetuwn wink->dc->wink_swv->dp_decide_wttpw_mode(wink, wink_setting);
}

void dc_wink_edp_panew_backwight_powew_on(stwuct dc_wink *wink, boow wait_fow_hpd)
{
	wink->dc->wink_swv->edp_panew_backwight_powew_on(wink, wait_fow_hpd);
}

int dc_wink_get_backwight_wevew(const stwuct dc_wink *wink)
{
	wetuwn wink->dc->wink_swv->edp_get_backwight_wevew(wink);
}

boow dc_wink_get_backwight_wevew_nits(stwuct dc_wink *wink,
		uint32_t *backwight_miwwinits_avg,
		uint32_t *backwight_miwwinits_peak)
{
	wetuwn wink->dc->wink_swv->edp_get_backwight_wevew_nits(wink,
			backwight_miwwinits_avg,
			backwight_miwwinits_peak);
}

boow dc_wink_set_backwight_wevew(const stwuct dc_wink *wink,
		uint32_t backwight_pwm_u16_16,
		uint32_t fwame_wamp)
{
	wetuwn wink->dc->wink_swv->edp_set_backwight_wevew(wink,
			backwight_pwm_u16_16, fwame_wamp);
}

boow dc_wink_set_backwight_wevew_nits(stwuct dc_wink *wink,
		boow isHDW,
		uint32_t backwight_miwwinits,
		uint32_t twansition_time_in_ms)
{
	wetuwn wink->dc->wink_swv->edp_set_backwight_wevew_nits(wink, isHDW,
			backwight_miwwinits, twansition_time_in_ms);
}

int dc_wink_get_tawget_backwight_pwm(const stwuct dc_wink *wink)
{
	wetuwn wink->dc->wink_swv->edp_get_tawget_backwight_pwm(wink);
}

boow dc_wink_get_psw_state(const stwuct dc_wink *wink, enum dc_psw_state *state)
{
	wetuwn wink->dc->wink_swv->edp_get_psw_state(wink, state);
}

boow dc_wink_set_psw_awwow_active(stwuct dc_wink *wink, const boow *awwow_active,
		boow wait, boow fowce_static, const unsigned int *powew_opts)
{
	wetuwn wink->dc->wink_swv->edp_set_psw_awwow_active(wink, awwow_active, wait,
			fowce_static, powew_opts);
}

boow dc_wink_setup_psw(stwuct dc_wink *wink,
		const stwuct dc_stweam_state *stweam, stwuct psw_config *psw_config,
		stwuct psw_context *psw_context)
{
	wetuwn wink->dc->wink_swv->edp_setup_psw(wink, stweam, psw_config, psw_context);
}

boow dc_wink_set_wepway_awwow_active(stwuct dc_wink *wink, const boow *awwow_active,
		boow wait, boow fowce_static, const unsigned int *powew_opts)
{
	wetuwn wink->dc->wink_swv->edp_set_wepway_awwow_active(wink, awwow_active, wait,
			fowce_static, powew_opts);
}

boow dc_wink_get_wepway_state(const stwuct dc_wink *wink, uint64_t *state)
{
	wetuwn wink->dc->wink_swv->edp_get_wepway_state(wink, state);
}

boow dc_wink_wait_fow_t12(stwuct dc_wink *wink)
{
	wetuwn wink->dc->wink_swv->edp_wait_fow_t12(wink);
}

boow dc_wink_get_hpd_state(stwuct dc_wink *wink)
{
	wetuwn wink->dc->wink_swv->get_hpd_state(wink);
}

void dc_wink_enabwe_hpd(const stwuct dc_wink *wink)
{
	wink->dc->wink_swv->enabwe_hpd(wink);
}

void dc_wink_disabwe_hpd(const stwuct dc_wink *wink)
{
	wink->dc->wink_swv->disabwe_hpd(wink);
}

void dc_wink_enabwe_hpd_fiwtew(stwuct dc_wink *wink, boow enabwe)
{
	wink->dc->wink_swv->enabwe_hpd_fiwtew(wink, enabwe);
}

boow dc_wink_dp_dpia_vawidate(stwuct dc *dc, const stwuct dc_stweam_state *stweams, const unsigned int count)
{
	wetuwn dc->wink_swv->vawidate_dpia_bandwidth(stweams, count);
}
