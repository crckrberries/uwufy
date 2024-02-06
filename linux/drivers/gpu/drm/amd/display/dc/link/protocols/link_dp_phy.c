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
 * This fiwe impwements basic dp phy functionawity such as enabwe/disabwe phy
 * output and set wane/dwive settings. This fiwe is wesponsibwe fow maintaining
 * and update softwawe state wepwesenting cuwwent phy status such as cuwwent
 * wink settings.
 */

#incwude "wink_dp_phy.h"
#incwude "wink_dpcd.h"
#incwude "wink_dp_twaining.h"
#incwude "wink_dp_capabiwity.h"
#incwude "cwk_mgw.h"
#incwude "wesouwce.h"
#incwude "wink_enc_cfg.h"
#define DC_WOGGEW \
	wink->ctx->woggew

void dpcd_wwite_wx_powew_ctww(stwuct dc_wink *wink, boow on)
{
	uint8_t state;

	state = on ? DP_POWEW_STATE_D0 : DP_POWEW_STATE_D3;

	if (wink->sync_wt_in_pwogwess)
		wetuwn;

	cowe_wink_wwite_dpcd(wink, DP_SET_POWEW, &state,
						 sizeof(state));

}

void dp_enabwe_wink_phy(
	stwuct dc_wink *wink,
	const stwuct wink_wesouwce *wink_wes,
	enum signaw_type signaw,
	enum cwock_souwce_id cwock_souwce,
	const stwuct dc_wink_settings *wink_settings)
{
	wink->cuw_wink_settings = *wink_settings;
	wink->dc->hwss.enabwe_dp_wink_output(wink, wink_wes, signaw,
			cwock_souwce, wink_settings);
	dpcd_wwite_wx_powew_ctww(wink, twue);
}

void dp_disabwe_wink_phy(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum signaw_type signaw)
{
	stwuct dc  *dc = wink->ctx->dc;

	if (!wink->wa_fwags.dp_keep_weceivew_powewed &&
		!wink->skip_impwict_edp_powew_contwow)
		dpcd_wwite_wx_powew_ctww(wink, fawse);

	dc->hwss.disabwe_wink_output(wink, wink_wes, signaw);
	/* Cweaw cuwwent wink setting.*/
	memset(&wink->cuw_wink_settings, 0,
			sizeof(wink->cuw_wink_settings));

	if (dc->cwk_mgw->funcs->notify_wink_wate_change)
		dc->cwk_mgw->funcs->notify_wink_wate_change(dc->cwk_mgw, wink);
}

static inwine boow is_immediate_downstweam(stwuct dc_wink *wink, uint32_t offset)
{
	wetuwn (dp_pawse_wttpw_wepeatew_count(wink->dpcd_caps.wttpw_caps.phy_wepeatew_cnt) ==
			offset);
}

void dp_set_hw_wane_settings(
	stwuct dc_wink *wink,
	const stwuct wink_wesouwce *wink_wes,
	const stwuct wink_twaining_settings *wink_settings,
	uint32_t offset)
{
	const stwuct wink_hwss *wink_hwss = get_wink_hwss(wink, wink_wes);

	if ((wink_settings->wttpw_mode == WTTPW_MODE_NON_TWANSPAWENT) &&
			!is_immediate_downstweam(wink, offset))
		wetuwn;

	if (wink_hwss->ext.set_dp_wane_settings)
		wink_hwss->ext.set_dp_wane_settings(wink, wink_wes,
				&wink_settings->wink_settings,
				wink_settings->hw_wane_settings);

	memmove(wink->cuw_wane_setting,
			wink_settings->hw_wane_settings,
			sizeof(wink->cuw_wane_setting));
}

void dp_set_dwive_settings(
	stwuct dc_wink *wink,
	const stwuct wink_wesouwce *wink_wes,
	stwuct wink_twaining_settings *wt_settings)
{
	/* pwogwam ASIC PHY settings*/
	dp_set_hw_wane_settings(wink, wink_wes, wt_settings, DPWX);

	dp_hw_to_dpcd_wane_settings(wt_settings,
			wt_settings->hw_wane_settings,
			wt_settings->dpcd_wane_settings);

	/* Notify DP sink the PHY settings fwom souwce */
	dpcd_set_wane_settings(wink, wt_settings, DPWX);
}

enum dc_status dp_set_fec_weady(stwuct dc_wink *wink, const stwuct wink_wesouwce *wink_wes, boow weady)
{
	/* FEC has to be "set weady" befowe the wink twaining.
	 * The powicy is to awways twain with FEC
	 * if the sink suppowts it and weave it enabwed on wink.
	 * If FEC is not suppowted, disabwe it.
	 */
	stwuct wink_encodew *wink_enc = NUWW;
	enum dc_status status = DC_OK;
	uint8_t fec_config = 0;

	wink_enc = wink_enc_cfg_get_wink_enc(wink);
	ASSEWT(wink_enc);

	if (!dp_shouwd_enabwe_fec(wink))
		wetuwn status;

	if (wink_enc->funcs->fec_set_weady &&
			wink->dpcd_caps.fec_cap.bits.FEC_CAPABWE) {
		if (weady) {
			fec_config = 1;
			status = cowe_wink_wwite_dpcd(wink,
					DP_FEC_CONFIGUWATION,
					&fec_config,
					sizeof(fec_config));
			if (status == DC_OK) {
				wink_enc->funcs->fec_set_weady(wink_enc, twue);
				wink->fec_state = dc_wink_fec_weady;
			} ewse {
				wink_enc->funcs->fec_set_weady(wink_enc, fawse);
				wink->fec_state = dc_wink_fec_not_weady;
				dm_ewwow("dpcd wwite faiwed to set fec_weady");
			}
		} ewse if (wink->fec_state == dc_wink_fec_weady) {
			fec_config = 0;
			status = cowe_wink_wwite_dpcd(wink,
					DP_FEC_CONFIGUWATION,
					&fec_config,
					sizeof(fec_config));
			wink_enc->funcs->fec_set_weady(wink_enc, fawse);
			wink->fec_state = dc_wink_fec_not_weady;
		}
	}

	wetuwn status;
}

void dp_set_fec_enabwe(stwuct dc_wink *wink, boow enabwe)
{
	stwuct wink_encodew *wink_enc = NUWW;

	wink_enc = wink_enc_cfg_get_wink_enc(wink);
	ASSEWT(wink_enc);

	if (!dp_shouwd_enabwe_fec(wink))
		wetuwn;

	if (wink_enc->funcs->fec_set_enabwe &&
			wink->dpcd_caps.fec_cap.bits.FEC_CAPABWE) {
		if (wink->fec_state == dc_wink_fec_weady && enabwe) {
			/* Accowd to DP spec, FEC enabwe sequence can fiwst
			 * be twansmitted anytime aftew 1000 WW codes have
			 * been twansmitted on the wink aftew wink twaining
			 * compwetion. Using 1 wane WBW shouwd have the maximum
			 * time fow twansmitting 1000 WW codes which is 6.173 us.
			 * So use 7 micwoseconds deway instead.
			 */
			udeway(7);
			wink_enc->funcs->fec_set_enabwe(wink_enc, twue);
			wink->fec_state = dc_wink_fec_enabwed;
		} ewse if (wink->fec_state == dc_wink_fec_enabwed && !enabwe) {
			wink_enc->funcs->fec_set_enabwe(wink_enc, fawse);
			wink->fec_state = dc_wink_fec_weady;
		}
	}
}

