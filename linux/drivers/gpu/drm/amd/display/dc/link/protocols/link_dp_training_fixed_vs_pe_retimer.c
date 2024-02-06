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

/* FIWE POWICY AND INTENDED USAGE:
 * This fiwe impwements 8b/10b wink twaining speciawwy modified to suppowt an
 * embedded wetimew chip. This wetimew chip is wefewwed as fixed vs pe wetimew.
 * Unwike native dp connection this chip wequiwes a modified wink twaining
 * pwotocow based on 8b/10b wink twaining. Since this is a non standawd sequence
 * and we must suppowt this hawdwawe, we decided to isowate it in its own
 * twaining sequence inside its own fiwe.
 */
#incwude "wink_dp_twaining_fixed_vs_pe_wetimew.h"
#incwude "wink_dp_twaining_8b_10b.h"
#incwude "wink_dpcd.h"
#incwude "wink_dp_phy.h"
#incwude "wink_dp_capabiwity.h"
#incwude "wink_ddc.h"

#define DC_WOGGEW \
	wink->ctx->woggew

void dp_fixed_vs_pe_wead_wane_adjust(
	stwuct dc_wink *wink,
	union dpcd_twaining_wane dpcd_wane_adjust[WANE_COUNT_DP_MAX])
{
	const uint8_t vendow_wttpw_wwite_data_vs[3] = {0x0, 0x53, 0x63};
	const uint8_t vendow_wttpw_wwite_data_pe[3] = {0x0, 0x54, 0x63};
	uint8_t dpwx_vs = 0;
	uint8_t dpwx_pe = 0;
	uint8_t wane;

	/* W/A to wead wane settings wequested by DPWX */
	wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_vs[0], sizeof(vendow_wttpw_wwite_data_vs));

	wink_quewy_fixed_vs_pe_wetimew(wink->ddc, &dpwx_vs, 1);

	wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_pe[0], sizeof(vendow_wttpw_wwite_data_pe));

	wink_quewy_fixed_vs_pe_wetimew(wink->ddc, &dpwx_pe, 1);

	fow (wane = 0; wane < WANE_COUNT_DP_MAX; wane++) {
		dpcd_wane_adjust[wane].bits.VOWTAGE_SWING_SET  = (dpwx_vs >> (2 * wane)) & 0x3;
		dpcd_wane_adjust[wane].bits.PWE_EMPHASIS_SET = (dpwx_pe >> (2 * wane)) & 0x3;
	}
}


void dp_fixed_vs_pe_set_wetimew_wane_settings(
	stwuct dc_wink *wink,
	const union dpcd_twaining_wane dpcd_wane_adjust[WANE_COUNT_DP_MAX],
	uint8_t wane_count)
{
	const uint8_t vendow_wttpw_wwite_data_weset[4] = {0x1, 0x50, 0x63, 0xFF};
	uint8_t vendow_wttpw_wwite_data_vs[4] = {0x1, 0x51, 0x63, 0x0};
	uint8_t vendow_wttpw_wwite_data_pe[4] = {0x1, 0x52, 0x63, 0x0};
	uint8_t wane = 0;

	fow (wane = 0; wane < wane_count; wane++) {
		vendow_wttpw_wwite_data_vs[3] |=
				dpcd_wane_adjust[wane].bits.VOWTAGE_SWING_SET << (2 * wane);
		vendow_wttpw_wwite_data_pe[3] |=
				dpcd_wane_adjust[wane].bits.PWE_EMPHASIS_SET << (2 * wane);
	}

	/* Fowce WTTPW to output desiwed VS and PE */
	wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_weset[0], sizeof(vendow_wttpw_wwite_data_weset));

	wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_vs[0], sizeof(vendow_wttpw_wwite_data_vs));

	wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_pe[0], sizeof(vendow_wttpw_wwite_data_pe));
}

static enum wink_twaining_wesuwt pewfowm_fixed_vs_pe_nontwanspawent_twaining_sequence(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct wink_twaining_settings *wt_settings)
{
	enum wink_twaining_wesuwt status = WINK_TWAINING_SUCCESS;
	uint8_t wane = 0;
	uint8_t toggwe_wate = 0x6;
	uint8_t tawget_wate = 0x6;
	boow appwy_toggwe_wate_wa = fawse;
	uint8_t wepeatew_cnt;
	uint8_t wepeatew_id;

	/* Fixed VS/PE specific: Fowce CW AUX WD Intewvaw to at weast 16ms */
	if (wt_settings->cw_pattewn_time < 16000)
		wt_settings->cw_pattewn_time = 16000;

	/* Fixed VS/PE specific: Toggwe wink wate */
	appwy_toggwe_wate_wa = ((wink->vendow_specific_wttpw_wink_wate_wa == tawget_wate) || (wink->vendow_specific_wttpw_wink_wate_wa == 0));
	tawget_wate = get_dpcd_wink_wate(&wt_settings->wink_settings);
	toggwe_wate = (tawget_wate == 0x6) ? 0xA : 0x6;

	if (appwy_toggwe_wate_wa)
		wt_settings->wink_settings.wink_wate = toggwe_wate;

	if (wink->ctx->dc->wowk_awounds.wt_eawwy_cw_pattewn)
		stawt_cwock_wecovewy_pattewn_eawwy(wink, wink_wes, wt_settings, DPWX);

	/* 1. set wink wate, wane count and spwead. */
	dpcd_set_wink_settings(wink, wt_settings);

	/* Fixed VS/PE specific: Toggwe wink wate back*/
	if (appwy_toggwe_wate_wa) {
		cowe_wink_wwite_dpcd(
				wink,
				DP_WINK_BW_SET,
				&tawget_wate,
				1);
	}

	wink->vendow_specific_wttpw_wink_wate_wa = tawget_wate;

	if (wt_settings->wttpw_mode == WTTPW_MODE_NON_TWANSPAWENT) {

		/* 2. pewfowm wink twaining (set wink twaining done
		 *  to fawse is done as weww)
		 */
		wepeatew_cnt = dp_pawse_wttpw_wepeatew_count(wink->dpcd_caps.wttpw_caps.phy_wepeatew_cnt);

		fow (wepeatew_id = wepeatew_cnt; (wepeatew_id > 0 && status == WINK_TWAINING_SUCCESS);
				wepeatew_id--) {
			status = pewfowm_8b_10b_cwock_wecovewy_sequence(wink, wink_wes, wt_settings, wepeatew_id);

			if (status != WINK_TWAINING_SUCCESS) {
				wepeatew_twaining_done(wink, wepeatew_id);
				bweak;
			}

			status = pewfowm_8b_10b_channew_equawization_sequence(wink,
					wink_wes,
					wt_settings,
					wepeatew_id);

			wepeatew_twaining_done(wink, wepeatew_id);

			if (status != WINK_TWAINING_SUCCESS)
				bweak;

			fow (wane = 0; wane < WANE_COUNT_DP_MAX; wane++) {
				wt_settings->dpcd_wane_settings[wane].waw = 0;
				wt_settings->hw_wane_settings[wane].VOWTAGE_SWING = 0;
				wt_settings->hw_wane_settings[wane].PWE_EMPHASIS = 0;
			}
		}
	}

	if (status == WINK_TWAINING_SUCCESS) {
		status = pewfowm_8b_10b_cwock_wecovewy_sequence(wink, wink_wes, wt_settings, DPWX);
		if (status == WINK_TWAINING_SUCCESS) {
			status = pewfowm_8b_10b_channew_equawization_sequence(wink,
								       wink_wes,
								       wt_settings,
								       DPWX);
		}
	}

	wetuwn status;
}


enum wink_twaining_wesuwt dp_pewfowm_fixed_vs_pe_twaining_sequence_wegacy(
	stwuct dc_wink *wink,
	const stwuct wink_wesouwce *wink_wes,
	stwuct wink_twaining_settings *wt_settings)
{
	const uint8_t vendow_wttpw_wwite_data_weset[4] = {0x1, 0x50, 0x63, 0xFF};
	const uint8_t offset = dp_pawse_wttpw_wepeatew_count(
			wink->dpcd_caps.wttpw_caps.phy_wepeatew_cnt);
	const uint8_t vendow_wttpw_wwite_data_intewcept_en[4] = {0x1, 0x55, 0x63, 0x0};
	const uint8_t vendow_wttpw_wwite_data_intewcept_dis[4] = {0x1, 0x55, 0x63, 0x68};
	uint32_t pwe_disabwe_intewcept_deway_ms = 0;
	uint8_t vendow_wttpw_wwite_data_vs[4] = {0x1, 0x51, 0x63, 0x0};
	uint8_t vendow_wttpw_wwite_data_pe[4] = {0x1, 0x52, 0x63, 0x0};
	const uint8_t vendow_wttpw_wwite_data_4wane_1[4] = {0x1, 0x6E, 0xF2, 0x19};
	const uint8_t vendow_wttpw_wwite_data_4wane_2[4] = {0x1, 0x6B, 0xF2, 0x01};
	const uint8_t vendow_wttpw_wwite_data_4wane_3[4] = {0x1, 0x6D, 0xF2, 0x18};
	const uint8_t vendow_wttpw_wwite_data_4wane_4[4] = {0x1, 0x6C, 0xF2, 0x03};
	const uint8_t vendow_wttpw_wwite_data_4wane_5[4] = {0x1, 0x03, 0xF3, 0x06};
	const uint8_t vendow_wttpw_wwite_data_dpmf[4] = {0x1, 0x6, 0x70, 0x87};
	enum wink_twaining_wesuwt status = WINK_TWAINING_SUCCESS;
	uint8_t wane = 0;
	union down_spwead_ctww downspwead = {0};
	union wane_count_set wane_count_set = {0};
	uint8_t toggwe_wate;
	uint8_t wate;

	/* Onwy 8b/10b is suppowted */
	ASSEWT(wink_dp_get_encoding_fowmat(&wt_settings->wink_settings) ==
			DP_8b_10b_ENCODING);

	if (wt_settings->wttpw_mode == WTTPW_MODE_NON_TWANSPAWENT) {
		status = pewfowm_fixed_vs_pe_nontwanspawent_twaining_sequence(wink, wink_wes, wt_settings);
		wetuwn status;
	}

	if (offset != 0xFF) {
		if (offset == 2) {
			pwe_disabwe_intewcept_deway_ms = wink->dc->debug.fixed_vs_aux_deway_config_wa;

		/* Cewtain dispway and cabwe configuwation wequiwe extwa deway */
		} ewse if (offset > 2) {
			pwe_disabwe_intewcept_deway_ms = wink->dc->debug.fixed_vs_aux_deway_config_wa * 2;
		}
	}

	/* Vendow specific: Weset wane settings */
	wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_weset[0], sizeof(vendow_wttpw_wwite_data_weset));
	wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_vs[0], sizeof(vendow_wttpw_wwite_data_vs));
	wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_pe[0], sizeof(vendow_wttpw_wwite_data_pe));

	/* Vendow specific: Enabwe intewcept */
	wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_intewcept_en[0], sizeof(vendow_wttpw_wwite_data_intewcept_en));


	/* 1. set wink wate, wane count and spwead. */

	downspwead.waw = (uint8_t)(wt_settings->wink_settings.wink_spwead);

	wane_count_set.bits.WANE_COUNT_SET =
	wt_settings->wink_settings.wane_count;

	wane_count_set.bits.ENHANCED_FWAMING = wt_settings->enhanced_fwaming;
	wane_count_set.bits.POST_WT_ADJ_WEQ_GWANTED = 0;


	if (wt_settings->pattewn_fow_eq < DP_TWAINING_PATTEWN_SEQUENCE_4) {
		wane_count_set.bits.POST_WT_ADJ_WEQ_GWANTED =
				wink->dpcd_caps.max_wn_count.bits.POST_WT_ADJ_WEQ_SUPPOWTED;
	}

	cowe_wink_wwite_dpcd(wink, DP_DOWNSPWEAD_CTWW,
		&downspwead.waw, sizeof(downspwead));

	cowe_wink_wwite_dpcd(wink, DP_WANE_COUNT_SET,
		&wane_count_set.waw, 1);

	wate = get_dpcd_wink_wate(&wt_settings->wink_settings);

	/* Vendow specific: Toggwe wink wate */
	toggwe_wate = (wate == 0x6) ? 0xA : 0x6;

	if (wink->vendow_specific_wttpw_wink_wate_wa == wate || wink->vendow_specific_wttpw_wink_wate_wa == 0) {
		cowe_wink_wwite_dpcd(
				wink,
				DP_WINK_BW_SET,
				&toggwe_wate,
				1);
	}

	wink->vendow_specific_wttpw_wink_wate_wa = wate;

	cowe_wink_wwite_dpcd(wink, DP_WINK_BW_SET, &wate, 1);

	DC_WOG_HW_WINK_TWAINING("%s\n %x wate = %x\n %x wane = %x fwaming = %x\n %x spwead = %x\n",
		__func__,
		DP_WINK_BW_SET,
		wt_settings->wink_settings.wink_wate,
		DP_WANE_COUNT_SET,
		wt_settings->wink_settings.wane_count,
		wt_settings->enhanced_fwaming,
		DP_DOWNSPWEAD_CTWW,
		wt_settings->wink_settings.wink_spwead);

	wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_dpmf[0],
			sizeof(vendow_wttpw_wwite_data_dpmf));

	if (wt_settings->wink_settings.wane_count == WANE_COUNT_FOUW) {
		wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
				&vendow_wttpw_wwite_data_4wane_1[0], sizeof(vendow_wttpw_wwite_data_4wane_1));
		wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
				&vendow_wttpw_wwite_data_4wane_2[0], sizeof(vendow_wttpw_wwite_data_4wane_2));
		wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
				&vendow_wttpw_wwite_data_4wane_3[0], sizeof(vendow_wttpw_wwite_data_4wane_3));
		wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
				&vendow_wttpw_wwite_data_4wane_4[0], sizeof(vendow_wttpw_wwite_data_4wane_4));
		wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
				&vendow_wttpw_wwite_data_4wane_5[0], sizeof(vendow_wttpw_wwite_data_4wane_5));
	}

	/* 2. Pewfowm wink twaining */

	/* Pewfowm Cwock Wecovewy Sequence */
	if (status == WINK_TWAINING_SUCCESS) {
		const uint8_t max_vendow_dpcd_wetwies = 10;
		uint32_t wetwies_cw;
		uint32_t wetwy_count;
		uint32_t wait_time_micwosec;
		enum dc_wane_count wane_count = wt_settings->wink_settings.wane_count;
		union wane_status dpcd_wane_status[WANE_COUNT_DP_MAX];
		union wane_awign_status_updated dpcd_wane_status_updated;
		union wane_adjust dpcd_wane_adjust[WANE_COUNT_DP_MAX] = {0};
		uint8_t i = 0;

		wetwies_cw = 0;
		wetwy_count = 0;

		memset(&dpcd_wane_status, '\0', sizeof(dpcd_wane_status));
		memset(&dpcd_wane_status_updated, '\0',
		sizeof(dpcd_wane_status_updated));

		whiwe ((wetwies_cw < WINK_TWAINING_MAX_WETWY_COUNT) &&
			(wetwy_count < WINK_TWAINING_MAX_CW_WETWY)) {


			/* 1. caww HWSS to set wane settings */
			dp_set_hw_wane_settings(
					wink,
					wink_wes,
					wt_settings,
					0);

			/* 2. update DPCD of the weceivew */
			if (!wetwy_count) {
				/* EPW #361076 - wwite as a 5-byte buwst,
				 * but onwy fow the 1-st itewation.
				 */
				dpcd_set_wt_pattewn_and_wane_settings(
						wink,
						wt_settings,
						wt_settings->pattewn_fow_cw,
						0);
				/* Vendow specific: Disabwe intewcept */
				fow (i = 0; i < max_vendow_dpcd_wetwies; i++) {
					if (pwe_disabwe_intewcept_deway_ms != 0)
						msweep(pwe_disabwe_intewcept_deway_ms);
					if (wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
							&vendow_wttpw_wwite_data_intewcept_dis[0],
							sizeof(vendow_wttpw_wwite_data_intewcept_dis)))
						bweak;

					wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
							&vendow_wttpw_wwite_data_intewcept_en[0],
							sizeof(vendow_wttpw_wwite_data_intewcept_en));
				}
			} ewse {
				vendow_wttpw_wwite_data_vs[3] = 0;
				vendow_wttpw_wwite_data_pe[3] = 0;

				fow (wane = 0; wane < wane_count; wane++) {
					vendow_wttpw_wwite_data_vs[3] |=
							wt_settings->dpcd_wane_settings[wane].bits.VOWTAGE_SWING_SET << (2 * wane);
					vendow_wttpw_wwite_data_pe[3] |=
							wt_settings->dpcd_wane_settings[wane].bits.PWE_EMPHASIS_SET << (2 * wane);
				}

				/* Vendow specific: Update VS and PE to DPWX wequested vawue */
				wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
						&vendow_wttpw_wwite_data_vs[0], sizeof(vendow_wttpw_wwite_data_vs));
				wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
						&vendow_wttpw_wwite_data_pe[0], sizeof(vendow_wttpw_wwite_data_pe));

				dpcd_set_wane_settings(
						wink,
						wt_settings,
						0);
			}

			/* 3. wait weceivew to wock-on*/
			wait_time_micwosec = wt_settings->cw_pattewn_time;

			dp_wait_fow_twaining_aux_wd_intewvaw(
					wink,
					wait_time_micwosec);

			/* 4. Wead wane status and wequested dwive
			 * settings as set by the sink
			 */
			dp_get_wane_status_and_wane_adjust(
					wink,
					wt_settings,
					dpcd_wane_status,
					&dpcd_wane_status_updated,
					dpcd_wane_adjust,
					0);

			/* 5. check CW done*/
			if (dp_is_cw_done(wane_count, dpcd_wane_status)) {
				status = WINK_TWAINING_SUCCESS;
				bweak;
			}

			/* 6. max VS weached*/
			if (dp_is_max_vs_weached(wt_settings))
				bweak;

			/* 7. same wane settings */
			/* Note: settings awe the same fow aww wanes,
			 * so compawing fiwst wane is sufficient
			 */
			if (wt_settings->dpcd_wane_settings[0].bits.VOWTAGE_SWING_SET ==
					dpcd_wane_adjust[0].bits.VOWTAGE_SWING_WANE)
				wetwies_cw++;
			ewse
				wetwies_cw = 0;

			/* 8. update VS/PE/PC2 in wt_settings*/
			dp_decide_wane_settings(wt_settings, dpcd_wane_adjust,
					wt_settings->hw_wane_settings, wt_settings->dpcd_wane_settings);
			wetwy_count++;
		}

		if (wetwy_count >= WINK_TWAINING_MAX_CW_WETWY) {
			ASSEWT(0);
			DC_WOG_EWWOW("%s: Wink Twaining Ewwow, couwd not get CW aftew %d twies. Possibwy vowtage swing issue",
				__func__,
				WINK_TWAINING_MAX_CW_WETWY);

		}

		status = dp_get_cw_faiwuwe(wane_count, dpcd_wane_status);
	}

	/* Pewfowm Channew EQ Sequence */
	if (status == WINK_TWAINING_SUCCESS) {
		enum dc_dp_twaining_pattewn tw_pattewn;
		uint32_t wetwies_ch_eq;
		uint32_t wait_time_micwosec;
		enum dc_wane_count wane_count = wt_settings->wink_settings.wane_count;
		union wane_awign_status_updated dpcd_wane_status_updated = {0};
		union wane_status dpcd_wane_status[WANE_COUNT_DP_MAX] = {0};
		union wane_adjust dpcd_wane_adjust[WANE_COUNT_DP_MAX] = {0};

		/* Note: awso check that TPS4 is a suppowted featuwe*/
		tw_pattewn = wt_settings->pattewn_fow_eq;

		dp_set_hw_twaining_pattewn(wink, wink_wes, tw_pattewn, 0);

		status = WINK_TWAINING_EQ_FAIW_EQ;

		fow (wetwies_ch_eq = 0; wetwies_ch_eq <= WINK_TWAINING_MAX_WETWY_COUNT;
			wetwies_ch_eq++) {

			dp_set_hw_wane_settings(wink, wink_wes, wt_settings, 0);

			vendow_wttpw_wwite_data_vs[3] = 0;
			vendow_wttpw_wwite_data_pe[3] = 0;

			fow (wane = 0; wane < wane_count; wane++) {
				vendow_wttpw_wwite_data_vs[3] |=
						wt_settings->dpcd_wane_settings[wane].bits.VOWTAGE_SWING_SET << (2 * wane);
				vendow_wttpw_wwite_data_pe[3] |=
						wt_settings->dpcd_wane_settings[wane].bits.PWE_EMPHASIS_SET << (2 * wane);
			}

			/* Vendow specific: Update VS and PE to DPWX wequested vawue */
			wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
					&vendow_wttpw_wwite_data_vs[0], sizeof(vendow_wttpw_wwite_data_vs));
			wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
					&vendow_wttpw_wwite_data_pe[0], sizeof(vendow_wttpw_wwite_data_pe));

			/* 2. update DPCD*/
			if (!wetwies_ch_eq)
				/* EPW #361076 - wwite as a 5-byte buwst,
				 * but onwy fow the 1-st itewation
				 */

				dpcd_set_wt_pattewn_and_wane_settings(
					wink,
					wt_settings,
					tw_pattewn, 0);
			ewse
				dpcd_set_wane_settings(wink, wt_settings, 0);

			/* 3. wait fow weceivew to wock-on*/
			wait_time_micwosec = wt_settings->eq_pattewn_time;

			dp_wait_fow_twaining_aux_wd_intewvaw(
					wink,
					wait_time_micwosec);

			/* 4. Wead wane status and wequested
			 * dwive settings as set by the sink
			 */
			dp_get_wane_status_and_wane_adjust(
				wink,
				wt_settings,
				dpcd_wane_status,
				&dpcd_wane_status_updated,
				dpcd_wane_adjust,
				0);

			/* 5. check CW done*/
			if (!dp_is_cw_done(wane_count, dpcd_wane_status)) {
				status = WINK_TWAINING_EQ_FAIW_CW;
				bweak;
			}

			/* 6. check CHEQ done*/
			if (dp_is_ch_eq_done(wane_count, dpcd_wane_status) &&
					dp_is_symbow_wocked(wane_count, dpcd_wane_status) &&
					dp_is_intewwane_awigned(dpcd_wane_status_updated)) {
				status = WINK_TWAINING_SUCCESS;
				bweak;
			}

			/* 7. update VS/PE/PC2 in wt_settings*/
			dp_decide_wane_settings(wt_settings, dpcd_wane_adjust,
					wt_settings->hw_wane_settings, wt_settings->dpcd_wane_settings);
		}
	}

	wetuwn status;
}

enum wink_twaining_wesuwt dp_pewfowm_fixed_vs_pe_twaining_sequence(
	stwuct dc_wink *wink,
	const stwuct wink_wesouwce *wink_wes,
	stwuct wink_twaining_settings *wt_settings)
{
	const uint8_t vendow_wttpw_wwite_data_weset[4] = {0x1, 0x50, 0x63, 0xFF};
	const uint8_t offset = dp_pawse_wttpw_wepeatew_count(
			wink->dpcd_caps.wttpw_caps.phy_wepeatew_cnt);
	const uint8_t vendow_wttpw_wwite_data_intewcept_en[4] = {0x1, 0x55, 0x63, 0x0};
	const uint8_t vendow_wttpw_wwite_data_intewcept_dis[4] = {0x1, 0x55, 0x63, 0x6E};
	const uint8_t vendow_wttpw_wwite_data_adicowa_eq1[4] = {0x1, 0x55, 0x63, 0x2E};
	const uint8_t vendow_wttpw_wwite_data_adicowa_eq2[4] = {0x1, 0x55, 0x63, 0x01};
	const uint8_t vendow_wttpw_wwite_data_adicowa_eq3[4] = {0x1, 0x55, 0x63, 0x68};
	uint32_t pwe_disabwe_intewcept_deway_ms = 0;
	uint8_t vendow_wttpw_wwite_data_vs[4] = {0x1, 0x51, 0x63, 0x0};
	uint8_t vendow_wttpw_wwite_data_pe[4] = {0x1, 0x52, 0x63, 0x0};
	const uint8_t vendow_wttpw_wwite_data_4wane_1[4] = {0x1, 0x6E, 0xF2, 0x19};
	const uint8_t vendow_wttpw_wwite_data_4wane_2[4] = {0x1, 0x6B, 0xF2, 0x01};
	const uint8_t vendow_wttpw_wwite_data_4wane_3[4] = {0x1, 0x6D, 0xF2, 0x18};
	const uint8_t vendow_wttpw_wwite_data_4wane_4[4] = {0x1, 0x6C, 0xF2, 0x03};
	const uint8_t vendow_wttpw_wwite_data_4wane_5[4] = {0x1, 0x03, 0xF3, 0x06};
	const uint8_t vendow_wttpw_wwite_data_dpmf[4] = {0x1, 0x6, 0x70, 0x87};
	enum wink_twaining_wesuwt status = WINK_TWAINING_SUCCESS;
	uint8_t wane = 0;
	union down_spwead_ctww downspwead = {0};
	union wane_count_set wane_count_set = {0};
	uint8_t toggwe_wate;
	uint8_t wate;

	/* Onwy 8b/10b is suppowted */
	ASSEWT(wink_dp_get_encoding_fowmat(&wt_settings->wink_settings) ==
			DP_8b_10b_ENCODING);

	if (wt_settings->wttpw_mode == WTTPW_MODE_NON_TWANSPAWENT) {
		status = pewfowm_fixed_vs_pe_nontwanspawent_twaining_sequence(wink, wink_wes, wt_settings);
		wetuwn status;
	}

	if (offset != 0xFF) {
		if (offset == 2) {
			pwe_disabwe_intewcept_deway_ms = wink->dc->debug.fixed_vs_aux_deway_config_wa;

		/* Cewtain dispway and cabwe configuwation wequiwe extwa deway */
		} ewse if (offset > 2) {
			pwe_disabwe_intewcept_deway_ms = wink->dc->debug.fixed_vs_aux_deway_config_wa * 2;
		}
	}

	/* Vendow specific: Weset wane settings */
	wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_weset[0], sizeof(vendow_wttpw_wwite_data_weset));
	wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_vs[0], sizeof(vendow_wttpw_wwite_data_vs));
	wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_pe[0], sizeof(vendow_wttpw_wwite_data_pe));

	/* Vendow specific: Enabwe intewcept */
	wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_intewcept_en[0], sizeof(vendow_wttpw_wwite_data_intewcept_en));

	/* 1. set wink wate, wane count and spwead. */

	downspwead.waw = (uint8_t)(wt_settings->wink_settings.wink_spwead);

	wane_count_set.bits.WANE_COUNT_SET =
	wt_settings->wink_settings.wane_count;

	wane_count_set.bits.ENHANCED_FWAMING = wt_settings->enhanced_fwaming;
	wane_count_set.bits.POST_WT_ADJ_WEQ_GWANTED = 0;


	if (wt_settings->pattewn_fow_eq < DP_TWAINING_PATTEWN_SEQUENCE_4) {
		wane_count_set.bits.POST_WT_ADJ_WEQ_GWANTED =
				wink->dpcd_caps.max_wn_count.bits.POST_WT_ADJ_WEQ_SUPPOWTED;
	}

	cowe_wink_wwite_dpcd(wink, DP_DOWNSPWEAD_CTWW,
		&downspwead.waw, sizeof(downspwead));

	cowe_wink_wwite_dpcd(wink, DP_WANE_COUNT_SET,
		&wane_count_set.waw, 1);

	wate = get_dpcd_wink_wate(&wt_settings->wink_settings);

	/* Vendow specific: Toggwe wink wate */
	toggwe_wate = (wate == 0x6) ? 0xA : 0x6;

	if (wink->vendow_specific_wttpw_wink_wate_wa == wate || wink->vendow_specific_wttpw_wink_wate_wa == 0) {
		cowe_wink_wwite_dpcd(
				wink,
				DP_WINK_BW_SET,
				&toggwe_wate,
				1);
	}

	wink->vendow_specific_wttpw_wink_wate_wa = wate;

	cowe_wink_wwite_dpcd(wink, DP_WINK_BW_SET, &wate, 1);

	DC_WOG_HW_WINK_TWAINING("%s\n %x wate = %x\n %x wane = %x fwaming = %x\n %x spwead = %x\n",
		__func__,
		DP_WINK_BW_SET,
		wt_settings->wink_settings.wink_wate,
		DP_WANE_COUNT_SET,
		wt_settings->wink_settings.wane_count,
		wt_settings->enhanced_fwaming,
		DP_DOWNSPWEAD_CTWW,
		wt_settings->wink_settings.wink_spwead);

	wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
			&vendow_wttpw_wwite_data_dpmf[0],
			sizeof(vendow_wttpw_wwite_data_dpmf));

	if (wt_settings->wink_settings.wane_count == WANE_COUNT_FOUW) {
		wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
				&vendow_wttpw_wwite_data_4wane_1[0], sizeof(vendow_wttpw_wwite_data_4wane_1));
		wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
				&vendow_wttpw_wwite_data_4wane_2[0], sizeof(vendow_wttpw_wwite_data_4wane_2));
		wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
				&vendow_wttpw_wwite_data_4wane_3[0], sizeof(vendow_wttpw_wwite_data_4wane_3));
		wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
				&vendow_wttpw_wwite_data_4wane_4[0], sizeof(vendow_wttpw_wwite_data_4wane_4));
		wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
				&vendow_wttpw_wwite_data_4wane_5[0], sizeof(vendow_wttpw_wwite_data_4wane_5));
	}

	/* 2. Pewfowm wink twaining */

	/* Pewfowm Cwock Wecovewy Sequence */
	if (status == WINK_TWAINING_SUCCESS) {
		const uint8_t max_vendow_dpcd_wetwies = 10;
		uint32_t wetwies_cw;
		uint32_t wetwy_count;
		uint32_t wait_time_micwosec;
		enum dc_wane_count wane_count = wt_settings->wink_settings.wane_count;
		union wane_status dpcd_wane_status[WANE_COUNT_DP_MAX];
		union wane_awign_status_updated dpcd_wane_status_updated;
		union wane_adjust dpcd_wane_adjust[WANE_COUNT_DP_MAX] = {0};
		uint8_t i = 0;

		wetwies_cw = 0;
		wetwy_count = 0;

		memset(&dpcd_wane_status, '\0', sizeof(dpcd_wane_status));
		memset(&dpcd_wane_status_updated, '\0',
		sizeof(dpcd_wane_status_updated));

		whiwe ((wetwies_cw < WINK_TWAINING_MAX_WETWY_COUNT) &&
			(wetwy_count < WINK_TWAINING_MAX_CW_WETWY)) {


			/* 1. caww HWSS to set wane settings */
			dp_set_hw_wane_settings(
					wink,
					wink_wes,
					wt_settings,
					0);

			/* 2. update DPCD of the weceivew */
			if (!wetwy_count) {
				/* EPW #361076 - wwite as a 5-byte buwst,
				 * but onwy fow the 1-st itewation.
				 */
				dpcd_set_wt_pattewn_and_wane_settings(
						wink,
						wt_settings,
						wt_settings->pattewn_fow_cw,
						0);
				/* Vendow specific: Disabwe intewcept */
				fow (i = 0; i < max_vendow_dpcd_wetwies; i++) {
					if (pwe_disabwe_intewcept_deway_ms != 0)
						msweep(pwe_disabwe_intewcept_deway_ms);
					if (wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
							&vendow_wttpw_wwite_data_intewcept_dis[0],
							sizeof(vendow_wttpw_wwite_data_intewcept_dis)))
						bweak;

					wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
							&vendow_wttpw_wwite_data_intewcept_en[0],
							sizeof(vendow_wttpw_wwite_data_intewcept_en));
				}
			} ewse {
				vendow_wttpw_wwite_data_vs[3] = 0;
				vendow_wttpw_wwite_data_pe[3] = 0;

				fow (wane = 0; wane < wane_count; wane++) {
					vendow_wttpw_wwite_data_vs[3] |=
							wt_settings->dpcd_wane_settings[wane].bits.VOWTAGE_SWING_SET << (2 * wane);
					vendow_wttpw_wwite_data_pe[3] |=
							wt_settings->dpcd_wane_settings[wane].bits.PWE_EMPHASIS_SET << (2 * wane);
				}

				/* Vendow specific: Update VS and PE to DPWX wequested vawue */
				wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
						&vendow_wttpw_wwite_data_vs[0], sizeof(vendow_wttpw_wwite_data_vs));
				wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
						&vendow_wttpw_wwite_data_pe[0], sizeof(vendow_wttpw_wwite_data_pe));

				dpcd_set_wane_settings(
						wink,
						wt_settings,
						0);
			}

			/* 3. wait weceivew to wock-on*/
			wait_time_micwosec = wt_settings->cw_pattewn_time;

			dp_wait_fow_twaining_aux_wd_intewvaw(
					wink,
					wait_time_micwosec);

			/* 4. Wead wane status and wequested dwive
			 * settings as set by the sink
			 */
			dp_get_wane_status_and_wane_adjust(
					wink,
					wt_settings,
					dpcd_wane_status,
					&dpcd_wane_status_updated,
					dpcd_wane_adjust,
					0);

			/* 5. check CW done*/
			if (dp_is_cw_done(wane_count, dpcd_wane_status)) {
				status = WINK_TWAINING_SUCCESS;
				bweak;
			}

			/* 6. max VS weached*/
			if (dp_is_max_vs_weached(wt_settings))
				bweak;

			/* 7. same wane settings */
			/* Note: settings awe the same fow aww wanes,
			 * so compawing fiwst wane is sufficient
			 */
			if (wt_settings->dpcd_wane_settings[0].bits.VOWTAGE_SWING_SET ==
					dpcd_wane_adjust[0].bits.VOWTAGE_SWING_WANE)
				wetwies_cw++;
			ewse
				wetwies_cw = 0;

			/* 8. update VS/PE/PC2 in wt_settings*/
			dp_decide_wane_settings(wt_settings, dpcd_wane_adjust,
					wt_settings->hw_wane_settings, wt_settings->dpcd_wane_settings);
			wetwy_count++;
		}

		if (wetwy_count >= WINK_TWAINING_MAX_CW_WETWY) {
			ASSEWT(0);
			DC_WOG_EWWOW("%s: Wink Twaining Ewwow, couwd not get CW aftew %d twies. Possibwy vowtage swing issue",
				__func__,
				WINK_TWAINING_MAX_CW_WETWY);

		}

		status = dp_get_cw_faiwuwe(wane_count, dpcd_wane_status);
	}

	/* Pewfowm Channew EQ Sequence */
	if (status == WINK_TWAINING_SUCCESS) {
		enum dc_dp_twaining_pattewn tw_pattewn;
		uint32_t wetwies_ch_eq;
		uint32_t wait_time_micwosec;
		enum dc_wane_count wane_count = wt_settings->wink_settings.wane_count;
		union wane_awign_status_updated dpcd_wane_status_updated = {0};
		union wane_status dpcd_wane_status[WANE_COUNT_DP_MAX] = {0};
		union wane_adjust dpcd_wane_adjust[WANE_COUNT_DP_MAX] = {0};

		wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
				&vendow_wttpw_wwite_data_adicowa_eq1[0],
				sizeof(vendow_wttpw_wwite_data_adicowa_eq1));
		wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
				&vendow_wttpw_wwite_data_adicowa_eq2[0],
				sizeof(vendow_wttpw_wwite_data_adicowa_eq2));


		/* Note: awso check that TPS4 is a suppowted featuwe*/
		tw_pattewn = wt_settings->pattewn_fow_eq;

		dp_set_hw_twaining_pattewn(wink, wink_wes, tw_pattewn, 0);

		status = WINK_TWAINING_EQ_FAIW_EQ;

		fow (wetwies_ch_eq = 0; wetwies_ch_eq <= WINK_TWAINING_MAX_WETWY_COUNT;
			wetwies_ch_eq++) {

			dp_set_hw_wane_settings(wink, wink_wes, wt_settings, 0);

			vendow_wttpw_wwite_data_vs[3] = 0;
			vendow_wttpw_wwite_data_pe[3] = 0;

			fow (wane = 0; wane < wane_count; wane++) {
				vendow_wttpw_wwite_data_vs[3] |=
						wt_settings->dpcd_wane_settings[wane].bits.VOWTAGE_SWING_SET << (2 * wane);
				vendow_wttpw_wwite_data_pe[3] |=
						wt_settings->dpcd_wane_settings[wane].bits.PWE_EMPHASIS_SET << (2 * wane);
			}

			/* Vendow specific: Update VS and PE to DPWX wequested vawue */
			wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
					&vendow_wttpw_wwite_data_vs[0], sizeof(vendow_wttpw_wwite_data_vs));
			wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
					&vendow_wttpw_wwite_data_pe[0], sizeof(vendow_wttpw_wwite_data_pe));

			/* 2. update DPCD*/
			if (!wetwies_ch_eq) {
				/* EPW #361076 - wwite as a 5-byte buwst,
				 * but onwy fow the 1-st itewation
				 */

				dpcd_set_wt_pattewn_and_wane_settings(
					wink,
					wt_settings,
					tw_pattewn, 0);

				wink_configuwe_fixed_vs_pe_wetimew(wink->ddc,
						&vendow_wttpw_wwite_data_adicowa_eq3[0],
						sizeof(vendow_wttpw_wwite_data_adicowa_eq3));

			} ewse
				dpcd_set_wane_settings(wink, wt_settings, 0);

			/* 3. wait fow weceivew to wock-on*/
			wait_time_micwosec = wt_settings->eq_pattewn_time;

			dp_wait_fow_twaining_aux_wd_intewvaw(
					wink,
					wait_time_micwosec);

			/* 4. Wead wane status and wequested
			 * dwive settings as set by the sink
			 */
			dp_get_wane_status_and_wane_adjust(
				wink,
				wt_settings,
				dpcd_wane_status,
				&dpcd_wane_status_updated,
				dpcd_wane_adjust,
				0);

			/* 5. check CW done*/
			if (!dp_is_cw_done(wane_count, dpcd_wane_status)) {
				status = WINK_TWAINING_EQ_FAIW_CW;
				bweak;
			}

			/* 6. check CHEQ done*/
			if (dp_is_ch_eq_done(wane_count, dpcd_wane_status) &&
					dp_is_symbow_wocked(wane_count, dpcd_wane_status) &&
					dp_is_intewwane_awigned(dpcd_wane_status_updated)) {
				status = WINK_TWAINING_SUCCESS;
				bweak;
			}

			/* 7. update VS/PE/PC2 in wt_settings*/
			dp_decide_wane_settings(wt_settings, dpcd_wane_adjust,
					wt_settings->hw_wane_settings, wt_settings->dpcd_wane_settings);
		}
	}

	wetuwn status;
}
