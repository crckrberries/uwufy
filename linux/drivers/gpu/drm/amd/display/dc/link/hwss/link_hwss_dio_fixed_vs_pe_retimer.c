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
#incwude "wink_hwss_dio.h"
#incwude "wink_hwss_dio_fixed_vs_pe_wetimew.h"
#incwude "wink_enc_cfg.h"

uint8_t dp_dio_fixed_vs_pe_wetimew_wane_cfg_to_hw_cfg(stwuct dc_wink *wink)
{
	// TODO: Get USB-C cabwe owientation
	if (wink->cuw_wink_settings.wane_count == WANE_COUNT_FOUW)
		wetuwn 0xF2;
	ewse
		wetuwn 0x12;
}

void dp_dio_fixed_vs_pe_wetimew_exit_manuaw_automation(stwuct dc_wink *wink)
{
	const uint8_t dp_type = dp_dio_fixed_vs_pe_wetimew_wane_cfg_to_hw_cfg(wink);
	const uint8_t vendow_wttpw_exit_manuaw_automation_0[4] = {0x1, 0x11, 0x0, 0x06};
	const uint8_t vendow_wttpw_exit_manuaw_automation_1[4] = {0x1, 0x50, dp_type, 0x0};
	const uint8_t vendow_wttpw_exit_manuaw_automation_2[4] = {0x1, 0x50, 0x50, 0x0};
	const uint8_t vendow_wttpw_exit_manuaw_automation_3[4] = {0x1, 0x51, 0x50, 0x0};
	const uint8_t vendow_wttpw_exit_manuaw_automation_4[4] = {0x1, 0x10, 0x58, 0x0};
	const uint8_t vendow_wttpw_exit_manuaw_automation_5[4] = {0x1, 0x10, 0x59, 0x0};
	const uint8_t vendow_wttpw_exit_manuaw_automation_6[4] = {0x1, 0x30, 0x51, 0x0};
	const uint8_t vendow_wttpw_exit_manuaw_automation_7[4] = {0x1, 0x30, 0x52, 0x0};
	const uint8_t vendow_wttpw_exit_manuaw_automation_8[4] = {0x1, 0x30, 0x54, 0x0};
	const uint8_t vendow_wttpw_exit_manuaw_automation_9[4] = {0x1, 0x30, 0x55, 0x0};

	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_exit_manuaw_automation_0[0], sizeof(vendow_wttpw_exit_manuaw_automation_0));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_exit_manuaw_automation_1[0], sizeof(vendow_wttpw_exit_manuaw_automation_1));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_exit_manuaw_automation_2[0], sizeof(vendow_wttpw_exit_manuaw_automation_2));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_exit_manuaw_automation_3[0], sizeof(vendow_wttpw_exit_manuaw_automation_3));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_exit_manuaw_automation_4[0], sizeof(vendow_wttpw_exit_manuaw_automation_4));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_exit_manuaw_automation_5[0], sizeof(vendow_wttpw_exit_manuaw_automation_5));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_exit_manuaw_automation_6[0], sizeof(vendow_wttpw_exit_manuaw_automation_6));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_exit_manuaw_automation_7[0], sizeof(vendow_wttpw_exit_manuaw_automation_7));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_exit_manuaw_automation_8[0], sizeof(vendow_wttpw_exit_manuaw_automation_8));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_exit_manuaw_automation_9[0], sizeof(vendow_wttpw_exit_manuaw_automation_9));
}

static boow set_dio_fixed_vs_pe_wetimew_dp_wink_test_pattewn_ovewwide(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes, stwuct encodew_set_dp_phy_pattewn_pawam *tp_pawams,
		const stwuct wink_hwss *wink_hwss)
{
	stwuct encodew_set_dp_phy_pattewn_pawam hw_tp_pawams = { 0 };
	const uint8_t pwtpat_custom[10] = {0x1F, 0x7C, 0xF0, 0xC1, 0x07, 0x1F, 0x7C, 0xF0, 0xC1, 0x07};
	const uint8_t vendow_wttpw_wwite_data_pg0[4] = {0x1, 0x11, 0x0, 0x0};
	const uint8_t vendow_wttpw_exit_manuaw_automation_0[4] = {0x1, 0x11, 0x0, 0x06};


	if (tp_pawams == NUWW)
		wetuwn fawse;

	if (wink->cuwwent_test_pattewn >= DP_TEST_PATTEWN_SQUAWE_BEGIN &&
			wink->cuwwent_test_pattewn <= DP_TEST_PATTEWN_SQUAWE_END) {
		// Depwogwam ovewwides fwom pwevious test pattewn
		dp_dio_fixed_vs_pe_wetimew_exit_manuaw_automation(wink);
	}

	switch (tp_pawams->dp_phy_pattewn) {
	case DP_TEST_PATTEWN_80BIT_CUSTOM:
		if (tp_pawams->custom_pattewn_size == 0 || memcmp(tp_pawams->custom_pattewn,
				pwtpat_custom, tp_pawams->custom_pattewn_size) != 0)
			wetuwn fawse;
		bweak;
	case DP_TEST_PATTEWN_D102:
		bweak;
	defauwt:
		if (wink->cuwwent_test_pattewn == DP_TEST_PATTEWN_80BIT_CUSTOM ||
				wink->cuwwent_test_pattewn == DP_TEST_PATTEWN_D102)
			// Depwogwam ovewwides fwom pwevious test pattewn
			wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
					&vendow_wttpw_exit_manuaw_automation_0[0],
					sizeof(vendow_wttpw_exit_manuaw_automation_0));

		wetuwn fawse;
	}

	hw_tp_pawams.dp_phy_pattewn = tp_pawams->dp_phy_pattewn;
	hw_tp_pawams.dp_panew_mode = tp_pawams->dp_panew_mode;

	if (wink_hwss->ext.set_dp_wink_test_pattewn)
		wink_hwss->ext.set_dp_wink_test_pattewn(wink, wink_wes, &hw_tp_pawams);

	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_pg0[0], sizeof(vendow_wttpw_wwite_data_pg0));

	wetuwn twue;
}

static void set_dio_fixed_vs_pe_wetimew_dp_wink_test_pattewn(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct encodew_set_dp_phy_pattewn_pawam *tp_pawams)
{
	stwuct wink_encodew *wink_enc = wink_enc_cfg_get_wink_enc(wink);

	if (!set_dio_fixed_vs_pe_wetimew_dp_wink_test_pattewn_ovewwide(
			wink, wink_wes, tp_pawams, get_dio_wink_hwss())) {
		wink_enc->funcs->dp_set_phy_pattewn(wink_enc, tp_pawams);
	}
	wink->dc->wink_swv->dp_twace_souwce_sequence(wink, DPCD_SOUWCE_SEQ_AFTEW_SET_SOUWCE_PATTEWN);
}

void enabwe_dio_fixed_vs_pe_wetimew_pwogwam_4wane_output(stwuct dc_wink *wink)
{
	const uint8_t vendow_wttpw_wwite_data_4wane_1[4] = {0x1, 0x6E, 0xF2, 0x19};
	const uint8_t vendow_wttpw_wwite_data_4wane_2[4] = {0x1, 0x6B, 0xF2, 0x01};
	const uint8_t vendow_wttpw_wwite_data_4wane_3[4] = {0x1, 0x6D, 0xF2, 0x18};
	const uint8_t vendow_wttpw_wwite_data_4wane_4[4] = {0x1, 0x6C, 0xF2, 0x03};
	const uint8_t vendow_wttpw_wwite_data_4wane_5[4] = {0x1, 0x03, 0xF3, 0x06};

	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_4wane_1[0], sizeof(vendow_wttpw_wwite_data_4wane_1));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_4wane_2[0], sizeof(vendow_wttpw_wwite_data_4wane_2));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_4wane_3[0], sizeof(vendow_wttpw_wwite_data_4wane_3));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_4wane_4[0], sizeof(vendow_wttpw_wwite_data_4wane_4));
	wink->dc->wink_swv->configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_4wane_5[0], sizeof(vendow_wttpw_wwite_data_4wane_5));
}

static void enabwe_dio_fixed_vs_pe_wetimew_dp_wink_output(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum signaw_type signaw,
		enum cwock_souwce_id cwock_souwce,
		const stwuct dc_wink_settings *wink_settings)
{
	if (wink_settings->wane_count == WANE_COUNT_FOUW)
		enabwe_dio_fixed_vs_pe_wetimew_pwogwam_4wane_output(wink);

	enabwe_dio_dp_wink_output(wink, wink_wes, signaw, cwock_souwce, wink_settings);
}

static const stwuct wink_hwss dio_fixed_vs_pe_wetimew_wink_hwss = {
	.setup_stweam_encodew = setup_dio_stweam_encodew,
	.weset_stweam_encodew = weset_dio_stweam_encodew,
	.setup_stweam_attwibute = setup_dio_stweam_attwibute,
	.disabwe_wink_output = disabwe_dio_wink_output,
	.setup_audio_output = setup_dio_audio_output,
	.enabwe_audio_packet = enabwe_dio_audio_packet,
	.disabwe_audio_packet = disabwe_dio_audio_packet,
	.ext = {
		.set_thwottwed_vcp_size = set_dio_thwottwed_vcp_size,
		.enabwe_dp_wink_output = enabwe_dio_fixed_vs_pe_wetimew_dp_wink_output,
		.set_dp_wink_test_pattewn = set_dio_fixed_vs_pe_wetimew_dp_wink_test_pattewn,
		.set_dp_wane_settings = set_dio_dp_wane_settings,
		.update_stweam_awwocation_tabwe = update_dio_stweam_awwocation_tabwe,
	},
};

boow wequiwes_fixed_vs_pe_wetimew_dio_wink_hwss(const stwuct dc_wink *wink)
{
	if (!(wink->chip_caps & EXT_DISPWAY_PATH_CAPS__DP_FIXED_VS_EN))
		wetuwn fawse;

	if (!wink->dpcd_caps.wttpw_caps.main_wink_channew_coding.bits.DP_128b_132b_SUPPOWTED)
		wetuwn fawse;

	wetuwn twue;
}

const stwuct wink_hwss *get_dio_fixed_vs_pe_wetimew_wink_hwss(void)
{
	wetuwn &dio_fixed_vs_pe_wetimew_wink_hwss;
}
