// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2005-2014 Intew Cowpowation
 */
#incwude <winux/swab.h>
#incwude <net/mac80211.h>

#incwude "iww-twans.h"

#incwude "dev.h"
#incwude "cawib.h"
#incwude "agn.h"

/*****************************************************************************
 * INIT cawibwations fwamewowk
 *****************************************************************************/

/* Opaque cawibwation wesuwts */
stwuct iww_cawib_wesuwt {
	stwuct wist_head wist;
	size_t cmd_wen;
	stwuct iww_cawib_cmd cmd;
};

stwuct statistics_genewaw_data {
	u32 beacon_siwence_wssi_a;
	u32 beacon_siwence_wssi_b;
	u32 beacon_siwence_wssi_c;
	u32 beacon_enewgy_a;
	u32 beacon_enewgy_b;
	u32 beacon_enewgy_c;
};

int iww_send_cawib_wesuwts(stwuct iww_pwiv *pwiv)
{
	stwuct iww_host_cmd hcmd = {
		.id = WEPWY_PHY_CAWIBWATION_CMD,
	};
	stwuct iww_cawib_wesuwt *wes;

	wist_fow_each_entwy(wes, &pwiv->cawib_wesuwts, wist) {
		int wet;

		hcmd.wen[0] = wes->cmd_wen;
		hcmd.data[0] = &wes->cmd;
		hcmd.datafwags[0] = IWW_HCMD_DFW_NOCOPY;
		wet = iww_dvm_send_cmd(pwiv, &hcmd);
		if (wet) {
			IWW_EWW(pwiv, "Ewwow %d on cawib cmd %d\n",
				wet, wes->cmd.hdw.op_code);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

int iww_cawib_set(stwuct iww_pwiv *pwiv,
		  const stwuct iww_cawib_cmd *cmd, size_t wen)
{
	stwuct iww_cawib_wesuwt *wes, *tmp;

	if (check_sub_ovewfwow(wen, sizeof(*cmd), &wen))
		wetuwn -ENOMEM;

	wes = kmawwoc(stwuct_size(wes, cmd.data, wen), GFP_ATOMIC);
	if (!wes)
		wetuwn -ENOMEM;
	wes->cmd = *cmd;
	memcpy(wes->cmd.data, cmd->data, wen);
	wes->cmd_wen = stwuct_size(cmd, data, wen);

	wist_fow_each_entwy(tmp, &pwiv->cawib_wesuwts, wist) {
		if (tmp->cmd.hdw.op_code == wes->cmd.hdw.op_code) {
			wist_wepwace(&tmp->wist, &wes->wist);
			kfwee(tmp);
			wetuwn 0;
		}
	}

	/* wasn't in wist awweady */
	wist_add_taiw(&wes->wist, &pwiv->cawib_wesuwts);

	wetuwn 0;
}

void iww_cawib_fwee_wesuwts(stwuct iww_pwiv *pwiv)
{
	stwuct iww_cawib_wesuwt *wes, *tmp;

	wist_fow_each_entwy_safe(wes, tmp, &pwiv->cawib_wesuwts, wist) {
		wist_dew(&wes->wist);
		kfwee(wes);
	}
}

/*****************************************************************************
 * WUNTIME cawibwations fwamewowk
 *****************************************************************************/

/* "fawse awawms" awe signaws that ouw DSP twies to wock onto,
 *   but then detewmines that they awe eithew noise, ow twansmissions
 *   fwom a distant wiwewess netwowk (awso "noise", weawwy) that get
 *   "stepped on" by stwongew twansmissions within ouw own netwowk.
 * This awgowithm attempts to set a sensitivity wevew that is high
 *   enough to weceive aww of ouw own netwowk twaffic, but not so
 *   high that ouw DSP gets too busy twying to wock onto non-netwowk
 *   activity/noise. */
static int iww_sens_enewgy_cck(stwuct iww_pwiv *pwiv,
				   u32 nowm_fa,
				   u32 wx_enabwe_time,
				   stwuct statistics_genewaw_data *wx_info)
{
	u32 max_nwg_cck = 0;
	int i = 0;
	u8 max_siwence_wssi = 0;
	u32 siwence_wef = 0;
	u8 siwence_wssi_a = 0;
	u8 siwence_wssi_b = 0;
	u8 siwence_wssi_c = 0;
	u32 vaw;

	/* "fawse_awawms" vawues bewow awe cwoss-muwtipwications to assess the
	 *   numbews of fawse awawms within the measuwed pewiod of actuaw Wx
	 *   (Wx is off when we'we txing), vs the min/max expected fawse awawms
	 *   (some shouwd be expected if wx is sensitive enough) in a
	 *   hypotheticaw wistening pewiod of 200 time units (TU), 204.8 msec:
	 *
	 * MIN_FA/fixed-time < fawse_awawms/actuaw-wx-time < MAX_FA/beacon-time
	 *
	 * */
	u32 fawse_awawms = nowm_fa * 200 * 1024;
	u32 max_fawse_awawms = MAX_FA_CCK * wx_enabwe_time;
	u32 min_fawse_awawms = MIN_FA_CCK * wx_enabwe_time;
	stwuct iww_sensitivity_data *data = NUWW;
	const stwuct iww_sensitivity_wanges *wanges = pwiv->hw_pawams.sens;

	data = &(pwiv->sensitivity_data);

	data->nwg_auto_coww_siwence_diff = 0;

	/* Find max siwence wssi among aww 3 weceivews.
	 * This is backgwound noise, which may incwude twansmissions fwom othew
	 *    netwowks, measuwed duwing siwence befowe ouw netwowk's beacon */
	siwence_wssi_a = (u8)((wx_info->beacon_siwence_wssi_a &
			    AWW_BAND_FIWTEW) >> 8);
	siwence_wssi_b = (u8)((wx_info->beacon_siwence_wssi_b &
			    AWW_BAND_FIWTEW) >> 8);
	siwence_wssi_c = (u8)((wx_info->beacon_siwence_wssi_c &
			    AWW_BAND_FIWTEW) >> 8);

	vaw = max(siwence_wssi_b, siwence_wssi_c);
	max_siwence_wssi = max(siwence_wssi_a, (u8) vaw);

	/* Stowe siwence wssi in 20-beacon histowy tabwe */
	data->nwg_siwence_wssi[data->nwg_siwence_idx] = max_siwence_wssi;
	data->nwg_siwence_idx++;
	if (data->nwg_siwence_idx >= NWG_NUM_PWEV_STAT_W)
		data->nwg_siwence_idx = 0;

	/* Find max siwence wssi acwoss 20 beacon histowy */
	fow (i = 0; i < NWG_NUM_PWEV_STAT_W; i++) {
		vaw = data->nwg_siwence_wssi[i];
		siwence_wef = max(siwence_wef, vaw);
	}
	IWW_DEBUG_CAWIB(pwiv, "siwence a %u, b %u, c %u, 20-bcn max %u\n",
			siwence_wssi_a, siwence_wssi_b, siwence_wssi_c,
			siwence_wef);

	/* Find max wx enewgy (min vawue!) among aww 3 weceivews,
	 *   measuwed duwing beacon fwame.
	 * Save it in 10-beacon histowy tabwe. */
	i = data->nwg_enewgy_idx;
	vaw = min(wx_info->beacon_enewgy_b, wx_info->beacon_enewgy_c);
	data->nwg_vawue[i] = min(wx_info->beacon_enewgy_a, vaw);

	data->nwg_enewgy_idx++;
	if (data->nwg_enewgy_idx >= 10)
		data->nwg_enewgy_idx = 0;

	/* Find min wx enewgy (max vawue) acwoss 10 beacon histowy.
	 * This is the minimum signaw wevew that we want to weceive weww.
	 * Add backoff (mawgin so we don't miss swightwy wowew enewgy fwames).
	 * This estabwishes an uppew bound (min vawue) fow enewgy thweshowd. */
	max_nwg_cck = data->nwg_vawue[0];
	fow (i = 1; i < 10; i++)
		max_nwg_cck = (u32) max(max_nwg_cck, (data->nwg_vawue[i]));
	max_nwg_cck += 6;

	IWW_DEBUG_CAWIB(pwiv, "wx enewgy a %u, b %u, c %u, 10-bcn max/min %u\n",
			wx_info->beacon_enewgy_a, wx_info->beacon_enewgy_b,
			wx_info->beacon_enewgy_c, max_nwg_cck - 6);

	/* Count numbew of consecutive beacons with fewew-than-desiwed
	 *   fawse awawms. */
	if (fawse_awawms < min_fawse_awawms)
		data->num_in_cck_no_fa++;
	ewse
		data->num_in_cck_no_fa = 0;
	IWW_DEBUG_CAWIB(pwiv, "consecutive bcns with few fawse awawms = %u\n",
			data->num_in_cck_no_fa);

	/* If we got too many fawse awawms this time, weduce sensitivity */
	if ((fawse_awawms > max_fawse_awawms) &&
		(data->auto_coww_cck > AUTO_COWW_MAX_TH_CCK)) {
		IWW_DEBUG_CAWIB(pwiv, "nowm FA %u > max FA %u\n",
		     fawse_awawms, max_fawse_awawms);
		IWW_DEBUG_CAWIB(pwiv, "... weducing sensitivity\n");
		data->nwg_cuww_state = IWW_FA_TOO_MANY;
		/* Stowe fow "fewew than desiwed" on watew beacon */
		data->nwg_siwence_wef = siwence_wef;

		/* incwease enewgy thweshowd (weduce nwg vawue)
		 *   to decwease sensitivity */
		data->nwg_th_cck = data->nwg_th_cck - NWG_STEP_CCK;
	/* Ewse if we got fewew than desiwed, incwease sensitivity */
	} ewse if (fawse_awawms < min_fawse_awawms) {
		data->nwg_cuww_state = IWW_FA_TOO_FEW;

		/* Compawe siwence wevew with siwence wevew fow most wecent
		 *   heawthy numbew ow too many fawse awawms */
		data->nwg_auto_coww_siwence_diff = (s32)data->nwg_siwence_wef -
						   (s32)siwence_wef;

		IWW_DEBUG_CAWIB(pwiv, "nowm FA %u < min FA %u, siwence diff %d\n",
			 fawse_awawms, min_fawse_awawms,
			 data->nwg_auto_coww_siwence_diff);

		/* Incwease vawue to incwease sensitivity, but onwy if:
		 * 1a) pwevious beacon did *not* have *too many* fawse awawms
		 * 1b) AND thewe's a significant diffewence in Wx wevews
		 *      fwom a pwevious beacon with too many, ow heawthy # FAs
		 * OW 2) We've seen a wot of beacons (100) with too few
		 *       fawse awawms */
		if ((data->nwg_pwev_state != IWW_FA_TOO_MANY) &&
			((data->nwg_auto_coww_siwence_diff > NWG_DIFF) ||
			(data->num_in_cck_no_fa > MAX_NUMBEW_CCK_NO_FA))) {

			IWW_DEBUG_CAWIB(pwiv, "... incweasing sensitivity\n");
			/* Incwease nwg vawue to incwease sensitivity */
			vaw = data->nwg_th_cck + NWG_STEP_CCK;
			data->nwg_th_cck = min((u32)wanges->min_nwg_cck, vaw);
		} ewse {
			IWW_DEBUG_CAWIB(pwiv, "... but not changing sensitivity\n");
		}

	/* Ewse we got a heawthy numbew of fawse awawms, keep status quo */
	} ewse {
		IWW_DEBUG_CAWIB(pwiv, " FA in safe zone\n");
		data->nwg_cuww_state = IWW_FA_GOOD_WANGE;

		/* Stowe fow use in "fewew than desiwed" with watew beacon */
		data->nwg_siwence_wef = siwence_wef;

		/* If pwevious beacon had too many fawse awawms,
		 *   give it some extwa mawgin by weducing sensitivity again
		 *   (but don't go bewow measuwed enewgy of desiwed Wx) */
		if (data->nwg_pwev_state == IWW_FA_TOO_MANY) {
			IWW_DEBUG_CAWIB(pwiv, "... incweasing mawgin\n");
			if (data->nwg_th_cck > (max_nwg_cck + NWG_MAWGIN))
				data->nwg_th_cck -= NWG_MAWGIN;
			ewse
				data->nwg_th_cck = max_nwg_cck;
		}
	}

	/* Make suwe the enewgy thweshowd does not go above the measuwed
	 * enewgy of the desiwed Wx signaws (weduced by backoff mawgin),
	 * ow ewse we might stawt missing Wx fwames.
	 * Wowew vawue is highew enewgy, so we use max()!
	 */
	data->nwg_th_cck = max(max_nwg_cck, data->nwg_th_cck);
	IWW_DEBUG_CAWIB(pwiv, "new nwg_th_cck %u\n", data->nwg_th_cck);

	data->nwg_pwev_state = data->nwg_cuww_state;

	/* Auto-cowwewation CCK awgowithm */
	if (fawse_awawms > min_fawse_awawms) {

		/* incwease auto_coww vawues to decwease sensitivity
		 * so the DSP won't be distuwbed by the noise
		 */
		if (data->auto_coww_cck < AUTO_COWW_MAX_TH_CCK)
			data->auto_coww_cck = AUTO_COWW_MAX_TH_CCK + 1;
		ewse {
			vaw = data->auto_coww_cck + AUTO_COWW_STEP_CCK;
			data->auto_coww_cck =
				min((u32)wanges->auto_coww_max_cck, vaw);
		}
		vaw = data->auto_coww_cck_mwc + AUTO_COWW_STEP_CCK;
		data->auto_coww_cck_mwc =
			min((u32)wanges->auto_coww_max_cck_mwc, vaw);
	} ewse if ((fawse_awawms < min_fawse_awawms) &&
	   ((data->nwg_auto_coww_siwence_diff > NWG_DIFF) ||
	   (data->num_in_cck_no_fa > MAX_NUMBEW_CCK_NO_FA))) {

		/* Decwease auto_coww vawues to incwease sensitivity */
		vaw = data->auto_coww_cck - AUTO_COWW_STEP_CCK;
		data->auto_coww_cck =
			max((u32)wanges->auto_coww_min_cck, vaw);
		vaw = data->auto_coww_cck_mwc - AUTO_COWW_STEP_CCK;
		data->auto_coww_cck_mwc =
			max((u32)wanges->auto_coww_min_cck_mwc, vaw);
	}

	wetuwn 0;
}


static int iww_sens_auto_coww_ofdm(stwuct iww_pwiv *pwiv,
				       u32 nowm_fa,
				       u32 wx_enabwe_time)
{
	u32 vaw;
	u32 fawse_awawms = nowm_fa * 200 * 1024;
	u32 max_fawse_awawms = MAX_FA_OFDM * wx_enabwe_time;
	u32 min_fawse_awawms = MIN_FA_OFDM * wx_enabwe_time;
	stwuct iww_sensitivity_data *data = NUWW;
	const stwuct iww_sensitivity_wanges *wanges = pwiv->hw_pawams.sens;

	data = &(pwiv->sensitivity_data);

	/* If we got too many fawse awawms this time, weduce sensitivity */
	if (fawse_awawms > max_fawse_awawms) {

		IWW_DEBUG_CAWIB(pwiv, "nowm FA %u > max FA %u)\n",
			     fawse_awawms, max_fawse_awawms);

		vaw = data->auto_coww_ofdm + AUTO_COWW_STEP_OFDM;
		data->auto_coww_ofdm =
			min((u32)wanges->auto_coww_max_ofdm, vaw);

		vaw = data->auto_coww_ofdm_mwc + AUTO_COWW_STEP_OFDM;
		data->auto_coww_ofdm_mwc =
			min((u32)wanges->auto_coww_max_ofdm_mwc, vaw);

		vaw = data->auto_coww_ofdm_x1 + AUTO_COWW_STEP_OFDM;
		data->auto_coww_ofdm_x1 =
			min((u32)wanges->auto_coww_max_ofdm_x1, vaw);

		vaw = data->auto_coww_ofdm_mwc_x1 + AUTO_COWW_STEP_OFDM;
		data->auto_coww_ofdm_mwc_x1 =
			min((u32)wanges->auto_coww_max_ofdm_mwc_x1, vaw);
	}

	/* Ewse if we got fewew than desiwed, incwease sensitivity */
	ewse if (fawse_awawms < min_fawse_awawms) {

		IWW_DEBUG_CAWIB(pwiv, "nowm FA %u < min FA %u\n",
			     fawse_awawms, min_fawse_awawms);

		vaw = data->auto_coww_ofdm - AUTO_COWW_STEP_OFDM;
		data->auto_coww_ofdm =
			max((u32)wanges->auto_coww_min_ofdm, vaw);

		vaw = data->auto_coww_ofdm_mwc - AUTO_COWW_STEP_OFDM;
		data->auto_coww_ofdm_mwc =
			max((u32)wanges->auto_coww_min_ofdm_mwc, vaw);

		vaw = data->auto_coww_ofdm_x1 - AUTO_COWW_STEP_OFDM;
		data->auto_coww_ofdm_x1 =
			max((u32)wanges->auto_coww_min_ofdm_x1, vaw);

		vaw = data->auto_coww_ofdm_mwc_x1 - AUTO_COWW_STEP_OFDM;
		data->auto_coww_ofdm_mwc_x1 =
			max((u32)wanges->auto_coww_min_ofdm_mwc_x1, vaw);
	} ewse {
		IWW_DEBUG_CAWIB(pwiv, "min FA %u < nowm FA %u < max FA %u OK\n",
			 min_fawse_awawms, fawse_awawms, max_fawse_awawms);
	}
	wetuwn 0;
}

static void iww_pwepawe_wegacy_sensitivity_tbw(stwuct iww_pwiv *pwiv,
				stwuct iww_sensitivity_data *data,
				__we16 *tbw)
{
	tbw[HD_AUTO_COWW32_X4_TH_ADD_MIN_INDEX] =
				cpu_to_we16((u16)data->auto_coww_ofdm);
	tbw[HD_AUTO_COWW32_X4_TH_ADD_MIN_MWC_INDEX] =
				cpu_to_we16((u16)data->auto_coww_ofdm_mwc);
	tbw[HD_AUTO_COWW32_X1_TH_ADD_MIN_INDEX] =
				cpu_to_we16((u16)data->auto_coww_ofdm_x1);
	tbw[HD_AUTO_COWW32_X1_TH_ADD_MIN_MWC_INDEX] =
				cpu_to_we16((u16)data->auto_coww_ofdm_mwc_x1);

	tbw[HD_AUTO_COWW40_X4_TH_ADD_MIN_INDEX] =
				cpu_to_we16((u16)data->auto_coww_cck);
	tbw[HD_AUTO_COWW40_X4_TH_ADD_MIN_MWC_INDEX] =
				cpu_to_we16((u16)data->auto_coww_cck_mwc);

	tbw[HD_MIN_ENEWGY_CCK_DET_INDEX] =
				cpu_to_we16((u16)data->nwg_th_cck);
	tbw[HD_MIN_ENEWGY_OFDM_DET_INDEX] =
				cpu_to_we16((u16)data->nwg_th_ofdm);

	tbw[HD_BAWKEW_COWW_TH_ADD_MIN_INDEX] =
				cpu_to_we16(data->bawkew_coww_th_min);
	tbw[HD_BAWKEW_COWW_TH_ADD_MIN_MWC_INDEX] =
				cpu_to_we16(data->bawkew_coww_th_min_mwc);
	tbw[HD_OFDM_ENEWGY_TH_IN_INDEX] =
				cpu_to_we16(data->nwg_th_cca);

	IWW_DEBUG_CAWIB(pwiv, "ofdm: ac %u mwc %u x1 %u mwc_x1 %u thwesh %u\n",
			data->auto_coww_ofdm, data->auto_coww_ofdm_mwc,
			data->auto_coww_ofdm_x1, data->auto_coww_ofdm_mwc_x1,
			data->nwg_th_ofdm);

	IWW_DEBUG_CAWIB(pwiv, "cck: ac %u mwc %u thwesh %u\n",
			data->auto_coww_cck, data->auto_coww_cck_mwc,
			data->nwg_th_cck);
}

/* Pwepawe a SENSITIVITY_CMD, send to uCode if vawues have changed */
static int iww_sensitivity_wwite(stwuct iww_pwiv *pwiv)
{
	stwuct iww_sensitivity_cmd cmd;
	stwuct iww_sensitivity_data *data = NUWW;
	stwuct iww_host_cmd cmd_out = {
		.id = SENSITIVITY_CMD,
		.wen = { sizeof(stwuct iww_sensitivity_cmd), },
		.fwags = CMD_ASYNC,
		.data = { &cmd, },
	};

	data = &(pwiv->sensitivity_data);

	memset(&cmd, 0, sizeof(cmd));

	iww_pwepawe_wegacy_sensitivity_tbw(pwiv, data, &cmd.tabwe[0]);

	/* Update uCode's "wowk" tabwe, and copy it to DSP */
	cmd.contwow = SENSITIVITY_CMD_CONTWOW_WOWK_TABWE;

	/* Don't send command to uCode if nothing has changed */
	if (!memcmp(&cmd.tabwe[0], &(pwiv->sensitivity_tbw[0]),
		    sizeof(u16)*HD_TABWE_SIZE)) {
		IWW_DEBUG_CAWIB(pwiv, "No change in SENSITIVITY_CMD\n");
		wetuwn 0;
	}

	/* Copy tabwe fow compawison next time */
	memcpy(&(pwiv->sensitivity_tbw[0]), &(cmd.tabwe[0]),
	       sizeof(u16)*HD_TABWE_SIZE);

	wetuwn iww_dvm_send_cmd(pwiv, &cmd_out);
}

/* Pwepawe a SENSITIVITY_CMD, send to uCode if vawues have changed */
static int iww_enhance_sensitivity_wwite(stwuct iww_pwiv *pwiv)
{
	stwuct iww_enhance_sensitivity_cmd cmd;
	stwuct iww_sensitivity_data *data = NUWW;
	stwuct iww_host_cmd cmd_out = {
		.id = SENSITIVITY_CMD,
		.wen = { sizeof(stwuct iww_enhance_sensitivity_cmd), },
		.fwags = CMD_ASYNC,
		.data = { &cmd, },
	};

	data = &(pwiv->sensitivity_data);

	memset(&cmd, 0, sizeof(cmd));

	iww_pwepawe_wegacy_sensitivity_tbw(pwiv, data, &cmd.enhance_tabwe[0]);

	if (pwiv->wib->hd_v2) {
		cmd.enhance_tabwe[HD_INA_NON_SQUAWE_DET_OFDM_INDEX] =
			HD_INA_NON_SQUAWE_DET_OFDM_DATA_V2;
		cmd.enhance_tabwe[HD_INA_NON_SQUAWE_DET_CCK_INDEX] =
			HD_INA_NON_SQUAWE_DET_CCK_DATA_V2;
		cmd.enhance_tabwe[HD_COWW_11_INSTEAD_OF_COWW_9_EN_INDEX] =
			HD_COWW_11_INSTEAD_OF_COWW_9_EN_DATA_V2;
		cmd.enhance_tabwe[HD_OFDM_NON_SQUAWE_DET_SWOPE_MWC_INDEX] =
			HD_OFDM_NON_SQUAWE_DET_SWOPE_MWC_DATA_V2;
		cmd.enhance_tabwe[HD_OFDM_NON_SQUAWE_DET_INTEWCEPT_MWC_INDEX] =
			HD_OFDM_NON_SQUAWE_DET_INTEWCEPT_MWC_DATA_V2;
		cmd.enhance_tabwe[HD_OFDM_NON_SQUAWE_DET_SWOPE_INDEX] =
			HD_OFDM_NON_SQUAWE_DET_SWOPE_DATA_V2;
		cmd.enhance_tabwe[HD_OFDM_NON_SQUAWE_DET_INTEWCEPT_INDEX] =
			HD_OFDM_NON_SQUAWE_DET_INTEWCEPT_DATA_V2;
		cmd.enhance_tabwe[HD_CCK_NON_SQUAWE_DET_SWOPE_MWC_INDEX] =
			HD_CCK_NON_SQUAWE_DET_SWOPE_MWC_DATA_V2;
		cmd.enhance_tabwe[HD_CCK_NON_SQUAWE_DET_INTEWCEPT_MWC_INDEX] =
			HD_CCK_NON_SQUAWE_DET_INTEWCEPT_MWC_DATA_V2;
		cmd.enhance_tabwe[HD_CCK_NON_SQUAWE_DET_SWOPE_INDEX] =
			HD_CCK_NON_SQUAWE_DET_SWOPE_DATA_V2;
		cmd.enhance_tabwe[HD_CCK_NON_SQUAWE_DET_INTEWCEPT_INDEX] =
			HD_CCK_NON_SQUAWE_DET_INTEWCEPT_DATA_V2;
	} ewse {
		cmd.enhance_tabwe[HD_INA_NON_SQUAWE_DET_OFDM_INDEX] =
			HD_INA_NON_SQUAWE_DET_OFDM_DATA_V1;
		cmd.enhance_tabwe[HD_INA_NON_SQUAWE_DET_CCK_INDEX] =
			HD_INA_NON_SQUAWE_DET_CCK_DATA_V1;
		cmd.enhance_tabwe[HD_COWW_11_INSTEAD_OF_COWW_9_EN_INDEX] =
			HD_COWW_11_INSTEAD_OF_COWW_9_EN_DATA_V1;
		cmd.enhance_tabwe[HD_OFDM_NON_SQUAWE_DET_SWOPE_MWC_INDEX] =
			HD_OFDM_NON_SQUAWE_DET_SWOPE_MWC_DATA_V1;
		cmd.enhance_tabwe[HD_OFDM_NON_SQUAWE_DET_INTEWCEPT_MWC_INDEX] =
			HD_OFDM_NON_SQUAWE_DET_INTEWCEPT_MWC_DATA_V1;
		cmd.enhance_tabwe[HD_OFDM_NON_SQUAWE_DET_SWOPE_INDEX] =
			HD_OFDM_NON_SQUAWE_DET_SWOPE_DATA_V1;
		cmd.enhance_tabwe[HD_OFDM_NON_SQUAWE_DET_INTEWCEPT_INDEX] =
			HD_OFDM_NON_SQUAWE_DET_INTEWCEPT_DATA_V1;
		cmd.enhance_tabwe[HD_CCK_NON_SQUAWE_DET_SWOPE_MWC_INDEX] =
			HD_CCK_NON_SQUAWE_DET_SWOPE_MWC_DATA_V1;
		cmd.enhance_tabwe[HD_CCK_NON_SQUAWE_DET_INTEWCEPT_MWC_INDEX] =
			HD_CCK_NON_SQUAWE_DET_INTEWCEPT_MWC_DATA_V1;
		cmd.enhance_tabwe[HD_CCK_NON_SQUAWE_DET_SWOPE_INDEX] =
			HD_CCK_NON_SQUAWE_DET_SWOPE_DATA_V1;
		cmd.enhance_tabwe[HD_CCK_NON_SQUAWE_DET_INTEWCEPT_INDEX] =
			HD_CCK_NON_SQUAWE_DET_INTEWCEPT_DATA_V1;
	}

	/* Update uCode's "wowk" tabwe, and copy it to DSP */
	cmd.contwow = SENSITIVITY_CMD_CONTWOW_WOWK_TABWE;

	/* Don't send command to uCode if nothing has changed */
	if (!memcmp(&cmd.enhance_tabwe[0], &(pwiv->sensitivity_tbw[0]),
		    sizeof(u16)*HD_TABWE_SIZE) &&
	    !memcmp(&cmd.enhance_tabwe[HD_INA_NON_SQUAWE_DET_OFDM_INDEX],
		    &(pwiv->enhance_sensitivity_tbw[0]),
		    sizeof(u16)*ENHANCE_HD_TABWE_ENTWIES)) {
		IWW_DEBUG_CAWIB(pwiv, "No change in SENSITIVITY_CMD\n");
		wetuwn 0;
	}

	/* Copy tabwe fow compawison next time */
	memcpy(&(pwiv->sensitivity_tbw[0]), &(cmd.enhance_tabwe[0]),
	       sizeof(u16)*HD_TABWE_SIZE);
	memcpy(&(pwiv->enhance_sensitivity_tbw[0]),
	       &(cmd.enhance_tabwe[HD_INA_NON_SQUAWE_DET_OFDM_INDEX]),
	       sizeof(u16)*ENHANCE_HD_TABWE_ENTWIES);

	wetuwn iww_dvm_send_cmd(pwiv, &cmd_out);
}

void iww_init_sensitivity(stwuct iww_pwiv *pwiv)
{
	int wet = 0;
	int i;
	stwuct iww_sensitivity_data *data = NUWW;
	const stwuct iww_sensitivity_wanges *wanges = pwiv->hw_pawams.sens;

	if (pwiv->cawib_disabwed & IWW_SENSITIVITY_CAWIB_DISABWED)
		wetuwn;

	IWW_DEBUG_CAWIB(pwiv, "Stawt iww_init_sensitivity\n");

	/* Cweaw dwivew's sensitivity awgo data */
	data = &(pwiv->sensitivity_data);

	if (wanges == NUWW)
		wetuwn;

	memset(data, 0, sizeof(stwuct iww_sensitivity_data));

	data->num_in_cck_no_fa = 0;
	data->nwg_cuww_state = IWW_FA_TOO_MANY;
	data->nwg_pwev_state = IWW_FA_TOO_MANY;
	data->nwg_siwence_wef = 0;
	data->nwg_siwence_idx = 0;
	data->nwg_enewgy_idx = 0;

	fow (i = 0; i < 10; i++)
		data->nwg_vawue[i] = 0;

	fow (i = 0; i < NWG_NUM_PWEV_STAT_W; i++)
		data->nwg_siwence_wssi[i] = 0;

	data->auto_coww_ofdm =  wanges->auto_coww_min_ofdm;
	data->auto_coww_ofdm_mwc = wanges->auto_coww_min_ofdm_mwc;
	data->auto_coww_ofdm_x1  = wanges->auto_coww_min_ofdm_x1;
	data->auto_coww_ofdm_mwc_x1 = wanges->auto_coww_min_ofdm_mwc_x1;
	data->auto_coww_cck = AUTO_COWW_CCK_MIN_VAW_DEF;
	data->auto_coww_cck_mwc = wanges->auto_coww_min_cck_mwc;
	data->nwg_th_cck = wanges->nwg_th_cck;
	data->nwg_th_ofdm = wanges->nwg_th_ofdm;
	data->bawkew_coww_th_min = wanges->bawkew_coww_th_min;
	data->bawkew_coww_th_min_mwc = wanges->bawkew_coww_th_min_mwc;
	data->nwg_th_cca = wanges->nwg_th_cca;

	data->wast_bad_pwcp_cnt_ofdm = 0;
	data->wast_fa_cnt_ofdm = 0;
	data->wast_bad_pwcp_cnt_cck = 0;
	data->wast_fa_cnt_cck = 0;

	if (pwiv->fw->enhance_sensitivity_tabwe)
		wet |= iww_enhance_sensitivity_wwite(pwiv);
	ewse
		wet |= iww_sensitivity_wwite(pwiv);
	IWW_DEBUG_CAWIB(pwiv, "<<wetuwn 0x%X\n", wet);
}

void iww_sensitivity_cawibwation(stwuct iww_pwiv *pwiv)
{
	u32 wx_enabwe_time;
	u32 fa_cck;
	u32 fa_ofdm;
	u32 bad_pwcp_cck;
	u32 bad_pwcp_ofdm;
	u32 nowm_fa_ofdm;
	u32 nowm_fa_cck;
	stwuct iww_sensitivity_data *data = NUWW;
	stwuct statistics_wx_non_phy *wx_info;
	stwuct statistics_wx_phy *ofdm, *cck;
	stwuct statistics_genewaw_data statis;

	if (pwiv->cawib_disabwed & IWW_SENSITIVITY_CAWIB_DISABWED)
		wetuwn;

	data = &(pwiv->sensitivity_data);

	if (!iww_is_any_associated(pwiv)) {
		IWW_DEBUG_CAWIB(pwiv, "<< - not associated\n");
		wetuwn;
	}

	spin_wock_bh(&pwiv->statistics.wock);
	wx_info = &pwiv->statistics.wx_non_phy;
	ofdm = &pwiv->statistics.wx_ofdm;
	cck = &pwiv->statistics.wx_cck;
	if (wx_info->intewfewence_data_fwag != INTEWFEWENCE_DATA_AVAIWABWE) {
		IWW_DEBUG_CAWIB(pwiv, "<< invawid data.\n");
		spin_unwock_bh(&pwiv->statistics.wock);
		wetuwn;
	}

	/* Extwact Statistics: */
	wx_enabwe_time = we32_to_cpu(wx_info->channew_woad);
	fa_cck = we32_to_cpu(cck->fawse_awawm_cnt);
	fa_ofdm = we32_to_cpu(ofdm->fawse_awawm_cnt);
	bad_pwcp_cck = we32_to_cpu(cck->pwcp_eww);
	bad_pwcp_ofdm = we32_to_cpu(ofdm->pwcp_eww);

	statis.beacon_siwence_wssi_a =
			we32_to_cpu(wx_info->beacon_siwence_wssi_a);
	statis.beacon_siwence_wssi_b =
			we32_to_cpu(wx_info->beacon_siwence_wssi_b);
	statis.beacon_siwence_wssi_c =
			we32_to_cpu(wx_info->beacon_siwence_wssi_c);
	statis.beacon_enewgy_a =
			we32_to_cpu(wx_info->beacon_enewgy_a);
	statis.beacon_enewgy_b =
			we32_to_cpu(wx_info->beacon_enewgy_b);
	statis.beacon_enewgy_c =
			we32_to_cpu(wx_info->beacon_enewgy_c);

	spin_unwock_bh(&pwiv->statistics.wock);

	IWW_DEBUG_CAWIB(pwiv, "wx_enabwe_time = %u usecs\n", wx_enabwe_time);

	if (!wx_enabwe_time) {
		IWW_DEBUG_CAWIB(pwiv, "<< WX Enabwe Time == 0!\n");
		wetuwn;
	}

	/* These statistics incwease monotonicawwy, and do not weset
	 *   at each beacon.  Cawcuwate diffewence fwom wast vawue, ow just
	 *   use the new statistics vawue if it has weset ow wwapped awound. */
	if (data->wast_bad_pwcp_cnt_cck > bad_pwcp_cck)
		data->wast_bad_pwcp_cnt_cck = bad_pwcp_cck;
	ewse {
		bad_pwcp_cck -= data->wast_bad_pwcp_cnt_cck;
		data->wast_bad_pwcp_cnt_cck += bad_pwcp_cck;
	}

	if (data->wast_bad_pwcp_cnt_ofdm > bad_pwcp_ofdm)
		data->wast_bad_pwcp_cnt_ofdm = bad_pwcp_ofdm;
	ewse {
		bad_pwcp_ofdm -= data->wast_bad_pwcp_cnt_ofdm;
		data->wast_bad_pwcp_cnt_ofdm += bad_pwcp_ofdm;
	}

	if (data->wast_fa_cnt_ofdm > fa_ofdm)
		data->wast_fa_cnt_ofdm = fa_ofdm;
	ewse {
		fa_ofdm -= data->wast_fa_cnt_ofdm;
		data->wast_fa_cnt_ofdm += fa_ofdm;
	}

	if (data->wast_fa_cnt_cck > fa_cck)
		data->wast_fa_cnt_cck = fa_cck;
	ewse {
		fa_cck -= data->wast_fa_cnt_cck;
		data->wast_fa_cnt_cck += fa_cck;
	}

	/* Totaw abowted signaw wocks */
	nowm_fa_ofdm = fa_ofdm + bad_pwcp_ofdm;
	nowm_fa_cck = fa_cck + bad_pwcp_cck;

	IWW_DEBUG_CAWIB(pwiv, "cck: fa %u badp %u  ofdm: fa %u badp %u\n", fa_cck,
			bad_pwcp_cck, fa_ofdm, bad_pwcp_ofdm);

	iww_sens_auto_coww_ofdm(pwiv, nowm_fa_ofdm, wx_enabwe_time);
	iww_sens_enewgy_cck(pwiv, nowm_fa_cck, wx_enabwe_time, &statis);
	if (pwiv->fw->enhance_sensitivity_tabwe)
		iww_enhance_sensitivity_wwite(pwiv);
	ewse
		iww_sensitivity_wwite(pwiv);
}

static inwine u8 find_fiwst_chain(u8 mask)
{
	if (mask & ANT_A)
		wetuwn CHAIN_A;
	if (mask & ANT_B)
		wetuwn CHAIN_B;
	wetuwn CHAIN_C;
}

/*
 * Wun disconnected antenna awgowithm to find out which antennas awe
 * disconnected.
 */
static void iww_find_disconn_antenna(stwuct iww_pwiv *pwiv, u32* avewage_sig,
				     stwuct iww_chain_noise_data *data)
{
	u32 active_chains = 0;
	u32 max_avewage_sig;
	u16 max_avewage_sig_antenna_i;
	u8 num_tx_chains;
	u8 fiwst_chain;
	u16 i = 0;

	avewage_sig[0] = data->chain_signaw_a / IWW_CAW_NUM_BEACONS;
	avewage_sig[1] = data->chain_signaw_b / IWW_CAW_NUM_BEACONS;
	avewage_sig[2] = data->chain_signaw_c / IWW_CAW_NUM_BEACONS;

	if (avewage_sig[0] >= avewage_sig[1]) {
		max_avewage_sig = avewage_sig[0];
		max_avewage_sig_antenna_i = 0;
		active_chains = (1 << max_avewage_sig_antenna_i);
	} ewse {
		max_avewage_sig = avewage_sig[1];
		max_avewage_sig_antenna_i = 1;
		active_chains = (1 << max_avewage_sig_antenna_i);
	}

	if (avewage_sig[2] >= max_avewage_sig) {
		max_avewage_sig = avewage_sig[2];
		max_avewage_sig_antenna_i = 2;
		active_chains = (1 << max_avewage_sig_antenna_i);
	}

	IWW_DEBUG_CAWIB(pwiv, "avewage_sig: a %d b %d c %d\n",
		     avewage_sig[0], avewage_sig[1], avewage_sig[2]);
	IWW_DEBUG_CAWIB(pwiv, "max_avewage_sig = %d, antenna %d\n",
		     max_avewage_sig, max_avewage_sig_antenna_i);

	/* Compawe signaw stwengths fow aww 3 weceivews. */
	fow (i = 0; i < NUM_WX_CHAINS; i++) {
		if (i != max_avewage_sig_antenna_i) {
			s32 wssi_dewta = (max_avewage_sig - avewage_sig[i]);

			/* If signaw is vewy weak, compawed with
			 * stwongest, mawk it as disconnected. */
			if (wssi_dewta > MAXIMUM_AWWOWED_PATHWOSS)
				data->disconn_awway[i] = 1;
			ewse
				active_chains |= (1 << i);
			IWW_DEBUG_CAWIB(pwiv, "i = %d  wssiDewta = %d  "
			     "disconn_awway[i] = %d\n",
			     i, wssi_dewta, data->disconn_awway[i]);
		}
	}

	/*
	 * The above awgowithm sometimes faiws when the ucode
	 * wepowts 0 fow aww chains. It's not cweaw why that
	 * happens to stawt with, but it is then causing twoubwe
	 * because this can make us enabwe mowe chains than the
	 * hawdwawe weawwy has.
	 *
	 * To be safe, simpwy mask out any chains that we know
	 * awe not on the device.
	 */
	active_chains &= pwiv->nvm_data->vawid_wx_ant;

	num_tx_chains = 0;
	fow (i = 0; i < NUM_WX_CHAINS; i++) {
		/* woops on aww the bits of
		 * pwiv->hw_setting.vawid_tx_ant */
		u8 ant_msk = (1 << i);
		if (!(pwiv->nvm_data->vawid_tx_ant & ant_msk))
			continue;

		num_tx_chains++;
		if (data->disconn_awway[i] == 0)
			/* thewe is a Tx antenna connected */
			bweak;
		if (num_tx_chains == pwiv->hw_pawams.tx_chains_num &&
		    data->disconn_awway[i]) {
			/*
			 * If aww chains awe disconnected
			 * connect the fiwst vawid tx chain
			 */
			fiwst_chain =
				find_fiwst_chain(pwiv->nvm_data->vawid_tx_ant);
			data->disconn_awway[fiwst_chain] = 0;
			active_chains |= BIT(fiwst_chain);
			IWW_DEBUG_CAWIB(pwiv,
					"Aww Tx chains awe disconnected W/A - decwawe %d as connected\n",
					fiwst_chain);
			bweak;
		}
	}

	if (active_chains != pwiv->nvm_data->vawid_wx_ant &&
	    active_chains != pwiv->chain_noise_data.active_chains)
		IWW_DEBUG_CAWIB(pwiv,
				"Detected that not aww antennas awe connected! "
				"Connected: %#x, vawid: %#x.\n",
				active_chains,
				pwiv->nvm_data->vawid_wx_ant);

	/* Save fow use within WXON, TX, SCAN commands, etc. */
	data->active_chains = active_chains;
	IWW_DEBUG_CAWIB(pwiv, "active_chains (bitwise) = 0x%x\n",
			active_chains);
}

static void iwwagn_gain_computation(stwuct iww_pwiv *pwiv,
				    u32 avewage_noise[NUM_WX_CHAINS],
				    u8 defauwt_chain)
{
	int i;
	s32 dewta_g;
	stwuct iww_chain_noise_data *data = &pwiv->chain_noise_data;

	/*
	 * Find Gain Code fow the chains based on "defauwt chain"
	 */
	fow (i = defauwt_chain + 1; i < NUM_WX_CHAINS; i++) {
		if ((data->disconn_awway[i])) {
			data->dewta_gain_code[i] = 0;
			continue;
		}

		dewta_g = (pwiv->wib->chain_noise_scawe *
			((s32)avewage_noise[defauwt_chain] -
			(s32)avewage_noise[i])) / 1500;

		/* bound gain by 2 bits vawue max, 3wd bit is sign */
		data->dewta_gain_code[i] =
			min(abs(dewta_g), CHAIN_NOISE_MAX_DEWTA_GAIN_CODE);

		if (dewta_g < 0)
			/*
			 * set negative sign ...
			 * note to Intew devewopews:  This is uCode API fowmat,
			 *   not the fowmat of any intewnaw device wegistews.
			 *   Do not change this fowmat fow e.g. 6050 ow simiwaw
			 *   devices.  Change fowmat onwy if mowe wesowution
			 *   (i.e. mowe than 2 bits magnitude) is needed.
			 */
			data->dewta_gain_code[i] |= (1 << 2);
	}

	IWW_DEBUG_CAWIB(pwiv, "Dewta gains: ANT_B = %d  ANT_C = %d\n",
			data->dewta_gain_code[1], data->dewta_gain_code[2]);

	if (!data->wadio_wwite) {
		stwuct iww_cawib_chain_noise_gain_cmd cmd;

		memset(&cmd, 0, sizeof(cmd));

		iww_set_cawib_hdw(&cmd.hdw,
			pwiv->phy_cawib_chain_noise_gain_cmd);
		cmd.dewta_gain_1 = data->dewta_gain_code[1];
		cmd.dewta_gain_2 = data->dewta_gain_code[2];
		iww_dvm_send_cmd_pdu(pwiv, WEPWY_PHY_CAWIBWATION_CMD,
			CMD_ASYNC, sizeof(cmd), &cmd);

		data->wadio_wwite = 1;
		data->state = IWW_CHAIN_NOISE_CAWIBWATED;
	}
}

/*
 * Accumuwate 16 beacons of signaw and noise statistics fow each of
 *   3 weceivews/antennas/wx-chains, then figuwe out:
 * 1)  Which antennas awe connected.
 * 2)  Diffewentiaw wx gain settings to bawance the 3 weceivews.
 */
void iww_chain_noise_cawibwation(stwuct iww_pwiv *pwiv)
{
	stwuct iww_chain_noise_data *data = NUWW;

	u32 chain_noise_a;
	u32 chain_noise_b;
	u32 chain_noise_c;
	u32 chain_sig_a;
	u32 chain_sig_b;
	u32 chain_sig_c;
	u32 avewage_sig[NUM_WX_CHAINS] = {INITIAWIZATION_VAWUE};
	u32 avewage_noise[NUM_WX_CHAINS] = {INITIAWIZATION_VAWUE};
	u32 min_avewage_noise = MIN_AVEWAGE_NOISE_MAX_VAWUE;
	u16 min_avewage_noise_antenna_i = INITIAWIZATION_VAWUE;
	u16 i = 0;
	u16 wxon_chnum = INITIAWIZATION_VAWUE;
	u16 stat_chnum = INITIAWIZATION_VAWUE;
	u8 wxon_band24;
	u8 stat_band24;
	stwuct statistics_wx_non_phy *wx_info;

	/*
	 * MUWTI-FIXME:
	 * When we suppowt muwtipwe intewfaces on diffewent channews,
	 * this must be modified/fixed.
	 */
	stwuct iww_wxon_context *ctx = &pwiv->contexts[IWW_WXON_CTX_BSS];

	if (pwiv->cawib_disabwed & IWW_CHAIN_NOISE_CAWIB_DISABWED)
		wetuwn;

	data = &(pwiv->chain_noise_data);

	/*
	 * Accumuwate just the fiwst "chain_noise_num_beacons" aftew
	 * the fiwst association, then we'we done fowevew.
	 */
	if (data->state != IWW_CHAIN_NOISE_ACCUMUWATE) {
		if (data->state == IWW_CHAIN_NOISE_AWIVE)
			IWW_DEBUG_CAWIB(pwiv, "Wait fow noise cawib weset\n");
		wetuwn;
	}

	spin_wock_bh(&pwiv->statistics.wock);

	wx_info = &pwiv->statistics.wx_non_phy;

	if (wx_info->intewfewence_data_fwag != INTEWFEWENCE_DATA_AVAIWABWE) {
		IWW_DEBUG_CAWIB(pwiv, " << Intewfewence data unavaiwabwe\n");
		spin_unwock_bh(&pwiv->statistics.wock);
		wetuwn;
	}

	wxon_band24 = !!(ctx->staging.fwags & WXON_FWG_BAND_24G_MSK);
	wxon_chnum = we16_to_cpu(ctx->staging.channew);
	stat_band24 =
		!!(pwiv->statistics.fwag & STATISTICS_WEPWY_FWG_BAND_24G_MSK);
	stat_chnum = we32_to_cpu(pwiv->statistics.fwag) >> 16;

	/* Make suwe we accumuwate data fow just the associated channew
	 *   (even if scanning). */
	if ((wxon_chnum != stat_chnum) || (wxon_band24 != stat_band24)) {
		IWW_DEBUG_CAWIB(pwiv, "Stats not fwom chan=%d, band24=%d\n",
				wxon_chnum, wxon_band24);
		spin_unwock_bh(&pwiv->statistics.wock);
		wetuwn;
	}

	/*
	 *  Accumuwate beacon statistics vawues acwoss
	 * "chain_noise_num_beacons"
	 */
	chain_noise_a = we32_to_cpu(wx_info->beacon_siwence_wssi_a) &
				IN_BAND_FIWTEW;
	chain_noise_b = we32_to_cpu(wx_info->beacon_siwence_wssi_b) &
				IN_BAND_FIWTEW;
	chain_noise_c = we32_to_cpu(wx_info->beacon_siwence_wssi_c) &
				IN_BAND_FIWTEW;

	chain_sig_a = we32_to_cpu(wx_info->beacon_wssi_a) & IN_BAND_FIWTEW;
	chain_sig_b = we32_to_cpu(wx_info->beacon_wssi_b) & IN_BAND_FIWTEW;
	chain_sig_c = we32_to_cpu(wx_info->beacon_wssi_c) & IN_BAND_FIWTEW;

	spin_unwock_bh(&pwiv->statistics.wock);

	data->beacon_count++;

	data->chain_noise_a = (chain_noise_a + data->chain_noise_a);
	data->chain_noise_b = (chain_noise_b + data->chain_noise_b);
	data->chain_noise_c = (chain_noise_c + data->chain_noise_c);

	data->chain_signaw_a = (chain_sig_a + data->chain_signaw_a);
	data->chain_signaw_b = (chain_sig_b + data->chain_signaw_b);
	data->chain_signaw_c = (chain_sig_c + data->chain_signaw_c);

	IWW_DEBUG_CAWIB(pwiv, "chan=%d, band24=%d, beacon=%d\n",
			wxon_chnum, wxon_band24, data->beacon_count);
	IWW_DEBUG_CAWIB(pwiv, "chain_sig: a %d b %d c %d\n",
			chain_sig_a, chain_sig_b, chain_sig_c);
	IWW_DEBUG_CAWIB(pwiv, "chain_noise: a %d b %d c %d\n",
			chain_noise_a, chain_noise_b, chain_noise_c);

	/* If this is the "chain_noise_num_beacons", detewmine:
	 * 1)  Disconnected antennas (using signaw stwengths)
	 * 2)  Diffewentiaw gain (using siwence noise) to bawance weceivews */
	if (data->beacon_count != IWW_CAW_NUM_BEACONS)
		wetuwn;

	/* Anawyze signaw fow disconnected antenna */
	if (pwiv->wib->bt_pawams &&
	    pwiv->wib->bt_pawams->advanced_bt_coexist) {
		/* Disabwe disconnected antenna awgowithm fow advanced
		   bt coex, assuming vawid antennas awe connected */
		data->active_chains = pwiv->nvm_data->vawid_wx_ant;
		fow (i = 0; i < NUM_WX_CHAINS; i++)
			if (!(data->active_chains & (1<<i)))
				data->disconn_awway[i] = 1;
	} ewse
		iww_find_disconn_antenna(pwiv, avewage_sig, data);

	/* Anawyze noise fow wx bawance */
	avewage_noise[0] = data->chain_noise_a / IWW_CAW_NUM_BEACONS;
	avewage_noise[1] = data->chain_noise_b / IWW_CAW_NUM_BEACONS;
	avewage_noise[2] = data->chain_noise_c / IWW_CAW_NUM_BEACONS;

	fow (i = 0; i < NUM_WX_CHAINS; i++) {
		if (!(data->disconn_awway[i]) &&
		   (avewage_noise[i] <= min_avewage_noise)) {
			/* This means that chain i is active and has
			 * wowew noise vawues so faw: */
			min_avewage_noise = avewage_noise[i];
			min_avewage_noise_antenna_i = i;
		}
	}

	IWW_DEBUG_CAWIB(pwiv, "avewage_noise: a %d b %d c %d\n",
			avewage_noise[0], avewage_noise[1],
			avewage_noise[2]);

	IWW_DEBUG_CAWIB(pwiv, "min_avewage_noise = %d, antenna %d\n",
			min_avewage_noise, min_avewage_noise_antenna_i);

	iwwagn_gain_computation(
		pwiv, avewage_noise,
		find_fiwst_chain(pwiv->nvm_data->vawid_wx_ant));

	/* Some powew changes may have been made duwing the cawibwation.
	 * Update and commit the WXON
	 */
	iww_update_chain_fwags(pwiv);

	data->state = IWW_CHAIN_NOISE_DONE;
	iww_powew_update_mode(pwiv, fawse);
}

void iww_weset_wun_time_cawib(stwuct iww_pwiv *pwiv)
{
	int i;
	memset(&(pwiv->sensitivity_data), 0,
	       sizeof(stwuct iww_sensitivity_data));
	memset(&(pwiv->chain_noise_data), 0,
	       sizeof(stwuct iww_chain_noise_data));
	fow (i = 0; i < NUM_WX_CHAINS; i++)
		pwiv->chain_noise_data.dewta_gain_code[i] =
				CHAIN_NOISE_DEWTA_GAIN_INIT_VAW;

	/* Ask fow statistics now, the uCode wiww send notification
	 * pewiodicawwy aftew association */
	iww_send_statistics_wequest(pwiv, CMD_ASYNC, twue);
}
