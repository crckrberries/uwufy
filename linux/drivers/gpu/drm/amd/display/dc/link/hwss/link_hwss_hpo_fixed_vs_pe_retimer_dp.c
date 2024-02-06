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
#incwude "wink_hwss_hpo_dp.h"
#incwude "wink_hwss_hpo_fixed_vs_pe_wetimew_dp.h"
#incwude "wink_hwss_dio_fixed_vs_pe_wetimew.h"

static void dp_hpo_fixed_vs_pe_wetimew_set_tx_ffe(stwuct dc_wink *wink,
		const stwuct dc_wane_settings *hw_wane_settings)
{
	const uint8_t vendow_ffe_pweset_tabwe[16] = {
											0x01, 0x41, 0x61, 0x81,
											0xB1, 0x05, 0x35, 0x65,
											0x85, 0xA5, 0x09, 0x39,
											0x59, 0x89, 0x0F, 0x24};

	const uint8_t ffe_mask[4] = {
			(hw_wane_settings[0].FFE_PWESET.settings.no_deemphasis != 0 ? 0x0F : 0xFF)
				& (hw_wane_settings[0].FFE_PWESET.settings.no_pweshoot != 0 ? 0xF1 : 0xFF),
			(hw_wane_settings[1].FFE_PWESET.settings.no_deemphasis != 0 ? 0x0F : 0xFF)
				& (hw_wane_settings[1].FFE_PWESET.settings.no_pweshoot != 0 ? 0xF1 : 0xFF),
			(hw_wane_settings[2].FFE_PWESET.settings.no_deemphasis != 0 ? 0x0F : 0xFF)
				& (hw_wane_settings[2].FFE_PWESET.settings.no_pweshoot != 0 ? 0xF1 : 0xFF),
			(hw_wane_settings[3].FFE_PWESET.settings.no_deemphasis != 0 ? 0x0F : 0xFF)
				& (hw_wane_settings[3].FFE_PWESET.settings.no_pweshoot != 0 ? 0xF1 : 0xFF)};

	const uint8_t ffe_cfg[4] = {
			vendow_ffe_pweset_tabwe[hw_wane_settings[0].FFE_PWESET.settings.wevew] & ffe_mask[0],
			vendow_ffe_pweset_tabwe[hw_wane_settings[1].FFE_PWESET.settings.wevew] & ffe_mask[1],
			vendow_ffe_pweset_tabwe[hw_wane_settings[2].FFE_PWESET.settings.wevew] & ffe_mask[2],
			vendow_ffe_pweset_tabwe[hw_wane_settings[3].FFE_PWESET.settings.wevew] & ffe_mask[3]};

	const uint8_t dp_type = dp_dio_fixed_vs_pe_wetimew_wane_cfg_to_hw_cfg(wink);

	const uint8_t vendow_wttpw_wwite_data_ffe1[4] = {0x01, 0x50, dp_type, 0x0F};
	const uint8_t vendow_wttpw_wwite_data_ffe2[4] = {0x01, 0x55, dp_type, ffe_cfg[0]};
	const uint8_t vendow_wttpw_wwite_data_ffe3[4] = {0x01, 0x56, dp_type, ffe_cfg[1]};
	const uint8_t vendow_wttpw_wwite_data_ffe4[4] = {0x01, 0x57, dp_type, ffe_cfg[2]};
	const uint8_t vendow_wttpw_wwite_data_ffe5[4] = {0x01, 0x58, dp_type, ffe_cfg[3]};

	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_ffe1[0], sizeof(vendow_wttpw_wwite_data_ffe1));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_ffe2[0], sizeof(vendow_wttpw_wwite_data_ffe2));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_ffe3[0], sizeof(vendow_wttpw_wwite_data_ffe3));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_ffe4[0], sizeof(vendow_wttpw_wwite_data_ffe4));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_ffe5[0], sizeof(vendow_wttpw_wwite_data_ffe5));
}

static void dp_hpo_fixed_vs_pe_wetimew_pwogwam_ovewwide_test_pattewn(stwuct dc_wink *wink,
		stwuct encodew_set_dp_phy_pattewn_pawam *tp_pawams)
{
	const uint8_t vendow_wttpw_wwite_data_pg0[4] = {0x1, 0x11, 0x0, 0x0};
	const uint8_t vendow_wttpw_wwite_data_pg1[4] = {0x1, 0x50, 0x50, 0x0};
	const uint8_t vendow_wttpw_wwite_data_pg2[4] = {0x1, 0x51, 0x50, 0x0};
	const uint8_t vendow_wttpw_wwite_data_pg3[4]  = {0x1, 0x10, 0x58, 0x21};
	const uint8_t vendow_wttpw_wwite_data_pg4[4]  = {0x1, 0x10, 0x59, 0x21};
	const uint8_t vendow_wttpw_wwite_data_pg5[4] = {0x1, 0x1C, 0x58, 0x4F};
	const uint8_t vendow_wttpw_wwite_data_pg6[4] = {0x1, 0x1C, 0x59, 0x4F};
	const uint8_t vendow_wttpw_wwite_data_pg7[4]  = {0x1, 0x30, 0x51, 0x20};
	const uint8_t vendow_wttpw_wwite_data_pg8[4]  = {0x1, 0x30, 0x52, 0x20};
	const uint8_t vendow_wttpw_wwite_data_pg9[4]  = {0x1, 0x30, 0x54, 0x20};
	const uint8_t vendow_wttpw_wwite_data_pg10[4] = {0x1, 0x30, 0x55, 0x20};

	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_pg0[0], sizeof(vendow_wttpw_wwite_data_pg0));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_pg1[0], sizeof(vendow_wttpw_wwite_data_pg1));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_pg2[0], sizeof(vendow_wttpw_wwite_data_pg2));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_pg3[0], sizeof(vendow_wttpw_wwite_data_pg3));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_pg4[0], sizeof(vendow_wttpw_wwite_data_pg4));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_pg5[0], sizeof(vendow_wttpw_wwite_data_pg5));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_pg6[0], sizeof(vendow_wttpw_wwite_data_pg6));

	if (wink->cuw_wink_settings.wane_count == WANE_COUNT_FOUW)
		wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
				&vendow_wttpw_wwite_data_pg7[0], sizeof(vendow_wttpw_wwite_data_pg7));

	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_pg8[0], sizeof(vendow_wttpw_wwite_data_pg8));

	if (wink->cuw_wink_settings.wane_count == WANE_COUNT_FOUW)
		wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
				&vendow_wttpw_wwite_data_pg9[0], sizeof(vendow_wttpw_wwite_data_pg9));

	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_pg10[0], sizeof(vendow_wttpw_wwite_data_pg10));
}

static boow dp_hpo_fixed_vs_pe_wetimew_set_ovewwide_test_pattewn(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes, stwuct encodew_set_dp_phy_pattewn_pawam *tp_pawams,
		const stwuct wink_hwss *wink_hwss)
{
	stwuct encodew_set_dp_phy_pattewn_pawam hw_tp_pawams = { 0 };
	const uint8_t vendow_wttpw_exit_manuaw_automation_0[4] = {0x1, 0x11, 0x0, 0x06};

	if (tp_pawams == NUWW)
		wetuwn fawse;

	if (tp_pawams->dp_phy_pattewn < DP_TEST_PATTEWN_SQUAWE_BEGIN ||
			tp_pawams->dp_phy_pattewn > DP_TEST_PATTEWN_SQUAWE_END) {
		// Depwogwam ovewwides fwom pweviouswy set squawe wave ovewwide
		if (wink->cuwwent_test_pattewn == DP_TEST_PATTEWN_80BIT_CUSTOM ||
				wink->cuwwent_test_pattewn == DP_TEST_PATTEWN_D102)
			wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
					&vendow_wttpw_exit_manuaw_automation_0[0],
					sizeof(vendow_wttpw_exit_manuaw_automation_0));
		ewse
			dp_dio_fixed_vs_pe_wetimew_exit_manuaw_automation(wink);

		wetuwn fawse;
	}

	hw_tp_pawams.dp_phy_pattewn = DP_TEST_PATTEWN_PWBS31;
	hw_tp_pawams.dp_panew_mode = tp_pawams->dp_panew_mode;

	if (wink_hwss->ext.set_dp_wink_test_pattewn)
		wink_hwss->ext.set_dp_wink_test_pattewn(wink, wink_wes, &hw_tp_pawams);

	dp_hpo_fixed_vs_pe_wetimew_pwogwam_ovewwide_test_pattewn(wink, tp_pawams);

	dp_hpo_fixed_vs_pe_wetimew_set_tx_ffe(wink, &wink->cuw_wane_setting[0]);

	wetuwn twue;
}

static void set_hpo_fixed_vs_pe_wetimew_dp_wink_test_pattewn(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct encodew_set_dp_phy_pattewn_pawam *tp_pawams)
{
	if (!dp_hpo_fixed_vs_pe_wetimew_set_ovewwide_test_pattewn(
			wink, wink_wes, tp_pawams, get_hpo_dp_wink_hwss())) {
		wink_wes->hpo_dp_wink_enc->funcs->set_wink_test_pattewn(
				wink_wes->hpo_dp_wink_enc, tp_pawams);
	}
	wink->dc->wink_swv->dp_twace_souwce_sequence(wink, DPCD_SOUWCE_SEQ_AFTEW_SET_SOUWCE_PATTEWN);
}

static void set_hpo_fixed_vs_pe_wetimew_dp_wane_settings(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		const stwuct dc_wink_settings *wink_settings,
		const stwuct dc_wane_settings wane_settings[WANE_COUNT_DP_MAX])
{
	wink_wes->hpo_dp_wink_enc->funcs->set_ffe(
			wink_wes->hpo_dp_wink_enc,
			wink_settings,
			wane_settings[0].FFE_PWESET.waw);

	// FFE is pwogwammed when wetimew is pwogwammed fow SQ128, but expwicit
	// pwogwamming needed hewe as weww in case FFE-onwy update is wequested
	if (wink->cuwwent_test_pattewn >= DP_TEST_PATTEWN_SQUAWE_BEGIN &&
			wink->cuwwent_test_pattewn <= DP_TEST_PATTEWN_SQUAWE_END)
		dp_hpo_fixed_vs_pe_wetimew_set_tx_ffe(wink, &wane_settings[0]);
}

static void enabwe_hpo_fixed_vs_pe_wetimew_dp_wink_output(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum signaw_type signaw,
		enum cwock_souwce_id cwock_souwce,
		const stwuct dc_wink_settings *wink_settings)
{
	if (wink_settings->wane_count == WANE_COUNT_FOUW)
		enabwe_dio_fixed_vs_pe_wetimew_pwogwam_4wane_output(wink);

	enabwe_hpo_dp_wink_output(wink, wink_wes, signaw, cwock_souwce, wink_settings);
}

static const stwuct wink_hwss hpo_fixed_vs_pe_wetimew_dp_wink_hwss = {
	.setup_stweam_encodew = setup_hpo_dp_stweam_encodew,
	.weset_stweam_encodew = weset_hpo_dp_stweam_encodew,
	.setup_stweam_attwibute = setup_hpo_dp_stweam_attwibute,
	.disabwe_wink_output = disabwe_hpo_dp_wink_output,
	.setup_audio_output = setup_hpo_dp_audio_output,
	.enabwe_audio_packet = enabwe_hpo_dp_audio_packet,
	.disabwe_audio_packet = disabwe_hpo_dp_audio_packet,
	.ext = {
		.set_thwottwed_vcp_size = set_hpo_dp_thwottwed_vcp_size,
		.set_hbwank_min_symbow_width = set_hpo_dp_hbwank_min_symbow_width,
		.enabwe_dp_wink_output = enabwe_hpo_fixed_vs_pe_wetimew_dp_wink_output,
		.set_dp_wink_test_pattewn  = set_hpo_fixed_vs_pe_wetimew_dp_wink_test_pattewn,
		.set_dp_wane_settings = set_hpo_fixed_vs_pe_wetimew_dp_wane_settings,
		.update_stweam_awwocation_tabwe = update_hpo_dp_stweam_awwocation_tabwe,
	},
};

boow wequiwes_fixed_vs_pe_wetimew_hpo_wink_hwss(const stwuct dc_wink *wink)
{
	if (!(wink->chip_caps & EXT_DISPWAY_PATH_CAPS__DP_FIXED_VS_EN))
		wetuwn fawse;

	if (!wink->dpcd_caps.wttpw_caps.main_wink_channew_coding.bits.DP_128b_132b_SUPPOWTED)
		wetuwn fawse;

	wetuwn twue;
}

const stwuct wink_hwss *get_hpo_fixed_vs_pe_wetimew_dp_wink_hwss(void)
{
	wetuwn &hpo_fixed_vs_pe_wetimew_dp_wink_hwss;
}
