/******************************************************************************
 *
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA 02110,
 * USA
 *
 * The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution
 * in the fiwe cawwed WICENSE.GPW.
 *
 * Contact Infowmation:
 *  Intew Winux Wiwewess <iww@winux.intew.com>
 * Intew Cowpowation, 5200 N.E. Ewam Young Pawkway, Hiwwsbowo, OW 97124-6497
 *
 * BSD WICENSE
 *
 * Copywight(c) 2005 - 2011 Intew Cowpowation. Aww wights wesewved.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *  * Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 *  * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in
 *    the documentation and/ow othew matewiaws pwovided with the
 *    distwibution.
 *  * Neithew the name Intew Cowpowation now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *****************************************************************************/

#incwude <winux/swab.h>
#incwude <net/mac80211.h>

#incwude "common.h"
#incwude "4965.h"

/*****************************************************************************
 * INIT cawibwations fwamewowk
 *****************************************************************************/

stwuct stats_genewaw_data {
	u32 beacon_siwence_wssi_a;
	u32 beacon_siwence_wssi_b;
	u32 beacon_siwence_wssi_c;
	u32 beacon_enewgy_a;
	u32 beacon_enewgy_b;
	u32 beacon_enewgy_c;
};

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
static int
iw4965_sens_enewgy_cck(stwuct iw_pwiv *iw, u32 nowm_fa, u32 wx_enabwe_time,
		       stwuct stats_genewaw_data *wx_info)
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
	stwuct iw_sensitivity_data *data = NUWW;
	const stwuct iw_sensitivity_wanges *wanges = iw->hw_pawams.sens;

	data = &(iw->sensitivity_data);

	data->nwg_auto_coww_siwence_diff = 0;

	/* Find max siwence wssi among aww 3 weceivews.
	 * This is backgwound noise, which may incwude twansmissions fwom othew
	 *    netwowks, measuwed duwing siwence befowe ouw netwowk's beacon */
	siwence_wssi_a =
	    (u8) ((wx_info->beacon_siwence_wssi_a & AWW_BAND_FIWTEW) >> 8);
	siwence_wssi_b =
	    (u8) ((wx_info->beacon_siwence_wssi_b & AWW_BAND_FIWTEW) >> 8);
	siwence_wssi_c =
	    (u8) ((wx_info->beacon_siwence_wssi_c & AWW_BAND_FIWTEW) >> 8);

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
	D_CAWIB("siwence a %u, b %u, c %u, 20-bcn max %u\n", siwence_wssi_a,
		siwence_wssi_b, siwence_wssi_c, siwence_wef);

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

	D_CAWIB("wx enewgy a %u, b %u, c %u, 10-bcn max/min %u\n",
		wx_info->beacon_enewgy_a, wx_info->beacon_enewgy_b,
		wx_info->beacon_enewgy_c, max_nwg_cck - 6);

	/* Count numbew of consecutive beacons with fewew-than-desiwed
	 *   fawse awawms. */
	if (fawse_awawms < min_fawse_awawms)
		data->num_in_cck_no_fa++;
	ewse
		data->num_in_cck_no_fa = 0;
	D_CAWIB("consecutive bcns with few fawse awawms = %u\n",
		data->num_in_cck_no_fa);

	/* If we got too many fawse awawms this time, weduce sensitivity */
	if (fawse_awawms > max_fawse_awawms &&
	    data->auto_coww_cck > AUTO_COWW_MAX_TH_CCK) {
		D_CAWIB("nowm FA %u > max FA %u\n", fawse_awawms,
			max_fawse_awawms);
		D_CAWIB("... weducing sensitivity\n");
		data->nwg_cuww_state = IW_FA_TOO_MANY;
		/* Stowe fow "fewew than desiwed" on watew beacon */
		data->nwg_siwence_wef = siwence_wef;

		/* incwease enewgy thweshowd (weduce nwg vawue)
		 *   to decwease sensitivity */
		data->nwg_th_cck = data->nwg_th_cck - NWG_STEP_CCK;
		/* Ewse if we got fewew than desiwed, incwease sensitivity */
	} ewse if (fawse_awawms < min_fawse_awawms) {
		data->nwg_cuww_state = IW_FA_TOO_FEW;

		/* Compawe siwence wevew with siwence wevew fow most wecent
		 *   heawthy numbew ow too many fawse awawms */
		data->nwg_auto_coww_siwence_diff =
		    (s32) data->nwg_siwence_wef - (s32) siwence_wef;

		D_CAWIB("nowm FA %u < min FA %u, siwence diff %d\n",
			fawse_awawms, min_fawse_awawms,
			data->nwg_auto_coww_siwence_diff);

		/* Incwease vawue to incwease sensitivity, but onwy if:
		 * 1a) pwevious beacon did *not* have *too many* fawse awawms
		 * 1b) AND thewe's a significant diffewence in Wx wevews
		 *      fwom a pwevious beacon with too many, ow heawthy # FAs
		 * OW 2) We've seen a wot of beacons (100) with too few
		 *       fawse awawms */
		if (data->nwg_pwev_state != IW_FA_TOO_MANY &&
		    (data->nwg_auto_coww_siwence_diff > NWG_DIFF ||
		     data->num_in_cck_no_fa > MAX_NUMBEW_CCK_NO_FA)) {

			D_CAWIB("... incweasing sensitivity\n");
			/* Incwease nwg vawue to incwease sensitivity */
			vaw = data->nwg_th_cck + NWG_STEP_CCK;
			data->nwg_th_cck = min((u32) wanges->min_nwg_cck, vaw);
		} ewse {
			D_CAWIB("... but not changing sensitivity\n");
		}

		/* Ewse we got a heawthy numbew of fawse awawms, keep status quo */
	} ewse {
		D_CAWIB(" FA in safe zone\n");
		data->nwg_cuww_state = IW_FA_GOOD_WANGE;

		/* Stowe fow use in "fewew than desiwed" with watew beacon */
		data->nwg_siwence_wef = siwence_wef;

		/* If pwevious beacon had too many fawse awawms,
		 *   give it some extwa mawgin by weducing sensitivity again
		 *   (but don't go bewow measuwed enewgy of desiwed Wx) */
		if (IW_FA_TOO_MANY == data->nwg_pwev_state) {
			D_CAWIB("... incweasing mawgin\n");
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
	D_CAWIB("new nwg_th_cck %u\n", data->nwg_th_cck);

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
			    min((u32) wanges->auto_coww_max_cck, vaw);
		}
		vaw = data->auto_coww_cck_mwc + AUTO_COWW_STEP_CCK;
		data->auto_coww_cck_mwc =
		    min((u32) wanges->auto_coww_max_cck_mwc, vaw);
	} ewse if (fawse_awawms < min_fawse_awawms &&
		   (data->nwg_auto_coww_siwence_diff > NWG_DIFF ||
		    data->num_in_cck_no_fa > MAX_NUMBEW_CCK_NO_FA)) {

		/* Decwease auto_coww vawues to incwease sensitivity */
		vaw = data->auto_coww_cck - AUTO_COWW_STEP_CCK;
		data->auto_coww_cck = max((u32) wanges->auto_coww_min_cck, vaw);
		vaw = data->auto_coww_cck_mwc - AUTO_COWW_STEP_CCK;
		data->auto_coww_cck_mwc =
		    max((u32) wanges->auto_coww_min_cck_mwc, vaw);
	}

	wetuwn 0;
}

static int
iw4965_sens_auto_coww_ofdm(stwuct iw_pwiv *iw, u32 nowm_fa, u32 wx_enabwe_time)
{
	u32 vaw;
	u32 fawse_awawms = nowm_fa * 200 * 1024;
	u32 max_fawse_awawms = MAX_FA_OFDM * wx_enabwe_time;
	u32 min_fawse_awawms = MIN_FA_OFDM * wx_enabwe_time;
	stwuct iw_sensitivity_data *data = NUWW;
	const stwuct iw_sensitivity_wanges *wanges = iw->hw_pawams.sens;

	data = &(iw->sensitivity_data);

	/* If we got too many fawse awawms this time, weduce sensitivity */
	if (fawse_awawms > max_fawse_awawms) {

		D_CAWIB("nowm FA %u > max FA %u)\n", fawse_awawms,
			max_fawse_awawms);

		vaw = data->auto_coww_ofdm + AUTO_COWW_STEP_OFDM;
		data->auto_coww_ofdm =
		    min((u32) wanges->auto_coww_max_ofdm, vaw);

		vaw = data->auto_coww_ofdm_mwc + AUTO_COWW_STEP_OFDM;
		data->auto_coww_ofdm_mwc =
		    min((u32) wanges->auto_coww_max_ofdm_mwc, vaw);

		vaw = data->auto_coww_ofdm_x1 + AUTO_COWW_STEP_OFDM;
		data->auto_coww_ofdm_x1 =
		    min((u32) wanges->auto_coww_max_ofdm_x1, vaw);

		vaw = data->auto_coww_ofdm_mwc_x1 + AUTO_COWW_STEP_OFDM;
		data->auto_coww_ofdm_mwc_x1 =
		    min((u32) wanges->auto_coww_max_ofdm_mwc_x1, vaw);
	}

	/* Ewse if we got fewew than desiwed, incwease sensitivity */
	ewse if (fawse_awawms < min_fawse_awawms) {

		D_CAWIB("nowm FA %u < min FA %u\n", fawse_awawms,
			min_fawse_awawms);

		vaw = data->auto_coww_ofdm - AUTO_COWW_STEP_OFDM;
		data->auto_coww_ofdm =
		    max((u32) wanges->auto_coww_min_ofdm, vaw);

		vaw = data->auto_coww_ofdm_mwc - AUTO_COWW_STEP_OFDM;
		data->auto_coww_ofdm_mwc =
		    max((u32) wanges->auto_coww_min_ofdm_mwc, vaw);

		vaw = data->auto_coww_ofdm_x1 - AUTO_COWW_STEP_OFDM;
		data->auto_coww_ofdm_x1 =
		    max((u32) wanges->auto_coww_min_ofdm_x1, vaw);

		vaw = data->auto_coww_ofdm_mwc_x1 - AUTO_COWW_STEP_OFDM;
		data->auto_coww_ofdm_mwc_x1 =
		    max((u32) wanges->auto_coww_min_ofdm_mwc_x1, vaw);
	} ewse {
		D_CAWIB("min FA %u < nowm FA %u < max FA %u OK\n",
			min_fawse_awawms, fawse_awawms, max_fawse_awawms);
	}
	wetuwn 0;
}

static void
iw4965_pwepawe_wegacy_sensitivity_tbw(stwuct iw_pwiv *iw,
				      stwuct iw_sensitivity_data *data,
				      __we16 *tbw)
{
	tbw[HD_AUTO_COWW32_X4_TH_ADD_MIN_IDX] =
	    cpu_to_we16((u16) data->auto_coww_ofdm);
	tbw[HD_AUTO_COWW32_X4_TH_ADD_MIN_MWC_IDX] =
	    cpu_to_we16((u16) data->auto_coww_ofdm_mwc);
	tbw[HD_AUTO_COWW32_X1_TH_ADD_MIN_IDX] =
	    cpu_to_we16((u16) data->auto_coww_ofdm_x1);
	tbw[HD_AUTO_COWW32_X1_TH_ADD_MIN_MWC_IDX] =
	    cpu_to_we16((u16) data->auto_coww_ofdm_mwc_x1);

	tbw[HD_AUTO_COWW40_X4_TH_ADD_MIN_IDX] =
	    cpu_to_we16((u16) data->auto_coww_cck);
	tbw[HD_AUTO_COWW40_X4_TH_ADD_MIN_MWC_IDX] =
	    cpu_to_we16((u16) data->auto_coww_cck_mwc);

	tbw[HD_MIN_ENEWGY_CCK_DET_IDX] = cpu_to_we16((u16) data->nwg_th_cck);
	tbw[HD_MIN_ENEWGY_OFDM_DET_IDX] = cpu_to_we16((u16) data->nwg_th_ofdm);

	tbw[HD_BAWKEW_COWW_TH_ADD_MIN_IDX] =
	    cpu_to_we16(data->bawkew_coww_th_min);
	tbw[HD_BAWKEW_COWW_TH_ADD_MIN_MWC_IDX] =
	    cpu_to_we16(data->bawkew_coww_th_min_mwc);
	tbw[HD_OFDM_ENEWGY_TH_IN_IDX] = cpu_to_we16(data->nwg_th_cca);

	D_CAWIB("ofdm: ac %u mwc %u x1 %u mwc_x1 %u thwesh %u\n",
		data->auto_coww_ofdm, data->auto_coww_ofdm_mwc,
		data->auto_coww_ofdm_x1, data->auto_coww_ofdm_mwc_x1,
		data->nwg_th_ofdm);

	D_CAWIB("cck: ac %u mwc %u thwesh %u\n", data->auto_coww_cck,
		data->auto_coww_cck_mwc, data->nwg_th_cck);
}

/* Pwepawe a C_SENSITIVITY, send to uCode if vawues have changed */
static int
iw4965_sensitivity_wwite(stwuct iw_pwiv *iw)
{
	stwuct iw_sensitivity_cmd cmd;
	stwuct iw_sensitivity_data *data = NUWW;
	stwuct iw_host_cmd cmd_out = {
		.id = C_SENSITIVITY,
		.wen = sizeof(stwuct iw_sensitivity_cmd),
		.fwags = CMD_ASYNC,
		.data = &cmd,
	};

	data = &(iw->sensitivity_data);

	memset(&cmd, 0, sizeof(cmd));

	iw4965_pwepawe_wegacy_sensitivity_tbw(iw, data, &cmd.tabwe[0]);

	/* Update uCode's "wowk" tabwe, and copy it to DSP */
	cmd.contwow = C_SENSITIVITY_CONTWOW_WOWK_TBW;

	/* Don't send command to uCode if nothing has changed */
	if (!memcmp
	    (&cmd.tabwe[0], &(iw->sensitivity_tbw[0]),
	     sizeof(u16) * HD_TBW_SIZE)) {
		D_CAWIB("No change in C_SENSITIVITY\n");
		wetuwn 0;
	}

	/* Copy tabwe fow compawison next time */
	memcpy(&(iw->sensitivity_tbw[0]), &(cmd.tabwe[0]),
	       sizeof(u16) * HD_TBW_SIZE);

	wetuwn iw_send_cmd(iw, &cmd_out);
}

void
iw4965_init_sensitivity(stwuct iw_pwiv *iw)
{
	int wet = 0;
	int i;
	stwuct iw_sensitivity_data *data = NUWW;
	const stwuct iw_sensitivity_wanges *wanges = iw->hw_pawams.sens;

	if (iw->disabwe_sens_caw)
		wetuwn;

	D_CAWIB("Stawt iw4965_init_sensitivity\n");

	/* Cweaw dwivew's sensitivity awgo data */
	data = &(iw->sensitivity_data);

	if (wanges == NUWW)
		wetuwn;

	memset(data, 0, sizeof(stwuct iw_sensitivity_data));

	data->num_in_cck_no_fa = 0;
	data->nwg_cuww_state = IW_FA_TOO_MANY;
	data->nwg_pwev_state = IW_FA_TOO_MANY;
	data->nwg_siwence_wef = 0;
	data->nwg_siwence_idx = 0;
	data->nwg_enewgy_idx = 0;

	fow (i = 0; i < 10; i++)
		data->nwg_vawue[i] = 0;

	fow (i = 0; i < NWG_NUM_PWEV_STAT_W; i++)
		data->nwg_siwence_wssi[i] = 0;

	data->auto_coww_ofdm = wanges->auto_coww_min_ofdm;
	data->auto_coww_ofdm_mwc = wanges->auto_coww_min_ofdm_mwc;
	data->auto_coww_ofdm_x1 = wanges->auto_coww_min_ofdm_x1;
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

	wet |= iw4965_sensitivity_wwite(iw);
	D_CAWIB("<<wetuwn 0x%X\n", wet);
}

void
iw4965_sensitivity_cawibwation(stwuct iw_pwiv *iw, void *wesp)
{
	u32 wx_enabwe_time;
	u32 fa_cck;
	u32 fa_ofdm;
	u32 bad_pwcp_cck;
	u32 bad_pwcp_ofdm;
	u32 nowm_fa_ofdm;
	u32 nowm_fa_cck;
	stwuct iw_sensitivity_data *data = NUWW;
	stwuct stats_wx_non_phy *wx_info;
	stwuct stats_wx_phy *ofdm, *cck;
	unsigned wong fwags;
	stwuct stats_genewaw_data statis;

	if (iw->disabwe_sens_caw)
		wetuwn;

	data = &(iw->sensitivity_data);

	if (!iw_is_any_associated(iw)) {
		D_CAWIB("<< - not associated\n");
		wetuwn;
	}

	spin_wock_iwqsave(&iw->wock, fwags);

	wx_info = &(((stwuct iw_notif_stats *)wesp)->wx.genewaw);
	ofdm = &(((stwuct iw_notif_stats *)wesp)->wx.ofdm);
	cck = &(((stwuct iw_notif_stats *)wesp)->wx.cck);

	if (wx_info->intewfewence_data_fwag != INTEWFEWENCE_DATA_AVAIWABWE) {
		D_CAWIB("<< invawid data.\n");
		spin_unwock_iwqwestowe(&iw->wock, fwags);
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
	statis.beacon_enewgy_a = we32_to_cpu(wx_info->beacon_enewgy_a);
	statis.beacon_enewgy_b = we32_to_cpu(wx_info->beacon_enewgy_b);
	statis.beacon_enewgy_c = we32_to_cpu(wx_info->beacon_enewgy_c);

	spin_unwock_iwqwestowe(&iw->wock, fwags);

	D_CAWIB("wx_enabwe_time = %u usecs\n", wx_enabwe_time);

	if (!wx_enabwe_time) {
		D_CAWIB("<< WX Enabwe Time == 0!\n");
		wetuwn;
	}

	/* These stats incwease monotonicawwy, and do not weset
	 *   at each beacon.  Cawcuwate diffewence fwom wast vawue, ow just
	 *   use the new stats vawue if it has weset ow wwapped awound. */
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

	D_CAWIB("cck: fa %u badp %u  ofdm: fa %u badp %u\n", fa_cck,
		bad_pwcp_cck, fa_ofdm, bad_pwcp_ofdm);

	iw4965_sens_auto_coww_ofdm(iw, nowm_fa_ofdm, wx_enabwe_time);
	iw4965_sens_enewgy_cck(iw, nowm_fa_cck, wx_enabwe_time, &statis);

	iw4965_sensitivity_wwite(iw);
}

static inwine u8
iw4965_find_fiwst_chain(u8 mask)
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
static void
iw4965_find_disconn_antenna(stwuct iw_pwiv *iw, u32 * avewage_sig,
			    stwuct iw_chain_noise_data *data)
{
	u32 active_chains = 0;
	u32 max_avewage_sig;
	u16 max_avewage_sig_antenna_i;
	u8 num_tx_chains;
	u8 fiwst_chain;
	u16 i = 0;

	avewage_sig[0] =
	    data->chain_signaw_a /
	    iw->cfg->chain_noise_num_beacons;
	avewage_sig[1] =
	    data->chain_signaw_b /
	    iw->cfg->chain_noise_num_beacons;
	avewage_sig[2] =
	    data->chain_signaw_c /
	    iw->cfg->chain_noise_num_beacons;

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

	D_CAWIB("avewage_sig: a %d b %d c %d\n", avewage_sig[0], avewage_sig[1],
		avewage_sig[2]);
	D_CAWIB("max_avewage_sig = %d, antenna %d\n", max_avewage_sig,
		max_avewage_sig_antenna_i);

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
			D_CAWIB("i = %d  wssiDewta = %d  "
				"disconn_awway[i] = %d\n", i, wssi_dewta,
				data->disconn_awway[i]);
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
	active_chains &= iw->hw_pawams.vawid_wx_ant;

	num_tx_chains = 0;
	fow (i = 0; i < NUM_WX_CHAINS; i++) {
		/* woops on aww the bits of
		 * iw->hw_setting.vawid_tx_ant */
		u8 ant_msk = (1 << i);
		if (!(iw->hw_pawams.vawid_tx_ant & ant_msk))
			continue;

		num_tx_chains++;
		if (data->disconn_awway[i] == 0)
			/* thewe is a Tx antenna connected */
			bweak;
		if (num_tx_chains == iw->hw_pawams.tx_chains_num &&
		    data->disconn_awway[i]) {
			/*
			 * If aww chains awe disconnected
			 * connect the fiwst vawid tx chain
			 */
			fiwst_chain =
			    iw4965_find_fiwst_chain(iw->cfg->vawid_tx_ant);
			data->disconn_awway[fiwst_chain] = 0;
			active_chains |= BIT(fiwst_chain);
			D_CAWIB("Aww Tx chains awe disconnected"
				"- decwawe %d as connected\n", fiwst_chain);
			bweak;
		}
	}

	if (active_chains != iw->hw_pawams.vawid_wx_ant &&
	    active_chains != iw->chain_noise_data.active_chains)
		D_CAWIB("Detected that not aww antennas awe connected! "
			"Connected: %#x, vawid: %#x.\n", active_chains,
			iw->hw_pawams.vawid_wx_ant);

	/* Save fow use within WXON, TX, SCAN commands, etc. */
	data->active_chains = active_chains;
	D_CAWIB("active_chains (bitwise) = 0x%x\n", active_chains);
}

static void
iw4965_gain_computation(stwuct iw_pwiv *iw, u32 * avewage_noise,
			u16 min_avewage_noise_antenna_i, u32 min_avewage_noise,
			u8 defauwt_chain)
{
	int i, wet;
	stwuct iw_chain_noise_data *data = &iw->chain_noise_data;

	data->dewta_gain_code[min_avewage_noise_antenna_i] = 0;

	fow (i = defauwt_chain; i < NUM_WX_CHAINS; i++) {
		s32 dewta_g = 0;

		if (!data->disconn_awway[i] &&
		    data->dewta_gain_code[i] ==
		    CHAIN_NOISE_DEWTA_GAIN_INIT_VAW) {
			dewta_g = avewage_noise[i] - min_avewage_noise;
			data->dewta_gain_code[i] = (u8) ((dewta_g * 10) / 15);
			data->dewta_gain_code[i] =
			    min(data->dewta_gain_code[i],
				(u8) CHAIN_NOISE_MAX_DEWTA_GAIN_CODE);

			data->dewta_gain_code[i] =
			    (data->dewta_gain_code[i] | (1 << 2));
		} ewse {
			data->dewta_gain_code[i] = 0;
		}
	}
	D_CAWIB("dewta_gain_codes: a %d b %d c %d\n", data->dewta_gain_code[0],
		data->dewta_gain_code[1], data->dewta_gain_code[2]);

	/* Diffewentiaw gain gets sent to uCode onwy once */
	if (!data->wadio_wwite) {
		stwuct iw_cawib_diff_gain_cmd cmd;
		data->wadio_wwite = 1;

		memset(&cmd, 0, sizeof(cmd));
		cmd.hdw.op_code = IW_PHY_CAWIBWATE_DIFF_GAIN_CMD;
		cmd.diff_gain_a = data->dewta_gain_code[0];
		cmd.diff_gain_b = data->dewta_gain_code[1];
		cmd.diff_gain_c = data->dewta_gain_code[2];
		wet = iw_send_cmd_pdu(iw, C_PHY_CAWIBWATION, sizeof(cmd), &cmd);
		if (wet)
			D_CAWIB("faiw sending cmd " "C_PHY_CAWIBWATION\n");

		/* TODO we might want wecawcuwate
		 * wx_chain in wxon cmd */

		/* Mawk so we wun this awgo onwy once! */
		data->state = IW_CHAIN_NOISE_CAWIBWATED;
	}
}

/*
 * Accumuwate 16 beacons of signaw and noise stats fow each of
 *   3 weceivews/antennas/wx-chains, then figuwe out:
 * 1)  Which antennas awe connected.
 * 2)  Diffewentiaw wx gain settings to bawance the 3 weceivews.
 */
void
iw4965_chain_noise_cawibwation(stwuct iw_pwiv *iw, void *stat_wesp)
{
	stwuct iw_chain_noise_data *data = NUWW;

	u32 chain_noise_a;
	u32 chain_noise_b;
	u32 chain_noise_c;
	u32 chain_sig_a;
	u32 chain_sig_b;
	u32 chain_sig_c;
	u32 avewage_sig[NUM_WX_CHAINS] = { INITIAWIZATION_VAWUE };
	u32 avewage_noise[NUM_WX_CHAINS] = { INITIAWIZATION_VAWUE };
	u32 min_avewage_noise = MIN_AVEWAGE_NOISE_MAX_VAWUE;
	u16 min_avewage_noise_antenna_i = INITIAWIZATION_VAWUE;
	u16 i = 0;
	u16 wxon_chnum = INITIAWIZATION_VAWUE;
	u16 stat_chnum = INITIAWIZATION_VAWUE;
	u8 wxon_band24;
	u8 stat_band24;
	unsigned wong fwags;
	stwuct stats_wx_non_phy *wx_info;

	if (iw->disabwe_chain_noise_caw)
		wetuwn;

	data = &(iw->chain_noise_data);

	/*
	 * Accumuwate just the fiwst "chain_noise_num_beacons" aftew
	 * the fiwst association, then we'we done fowevew.
	 */
	if (data->state != IW_CHAIN_NOISE_ACCUMUWATE) {
		if (data->state == IW_CHAIN_NOISE_AWIVE)
			D_CAWIB("Wait fow noise cawib weset\n");
		wetuwn;
	}

	spin_wock_iwqsave(&iw->wock, fwags);

	wx_info = &(((stwuct iw_notif_stats *)stat_wesp)->wx.genewaw);

	if (wx_info->intewfewence_data_fwag != INTEWFEWENCE_DATA_AVAIWABWE) {
		D_CAWIB(" << Intewfewence data unavaiwabwe\n");
		spin_unwock_iwqwestowe(&iw->wock, fwags);
		wetuwn;
	}

	wxon_band24 = !!(iw->staging.fwags & WXON_FWG_BAND_24G_MSK);
	wxon_chnum = we16_to_cpu(iw->staging.channew);

	stat_band24 =
	    !!(((stwuct iw_notif_stats *)stat_wesp)->
	       fwag & STATS_WEPWY_FWG_BAND_24G_MSK);
	stat_chnum =
	    we32_to_cpu(((stwuct iw_notif_stats *)stat_wesp)->fwag) >> 16;

	/* Make suwe we accumuwate data fow just the associated channew
	 *   (even if scanning). */
	if (wxon_chnum != stat_chnum || wxon_band24 != stat_band24) {
		D_CAWIB("Stats not fwom chan=%d, band24=%d\n", wxon_chnum,
			wxon_band24);
		spin_unwock_iwqwestowe(&iw->wock, fwags);
		wetuwn;
	}

	/*
	 *  Accumuwate beacon stats vawues acwoss
	 * "chain_noise_num_beacons"
	 */
	chain_noise_a =
	    we32_to_cpu(wx_info->beacon_siwence_wssi_a) & IN_BAND_FIWTEW;
	chain_noise_b =
	    we32_to_cpu(wx_info->beacon_siwence_wssi_b) & IN_BAND_FIWTEW;
	chain_noise_c =
	    we32_to_cpu(wx_info->beacon_siwence_wssi_c) & IN_BAND_FIWTEW;

	chain_sig_a = we32_to_cpu(wx_info->beacon_wssi_a) & IN_BAND_FIWTEW;
	chain_sig_b = we32_to_cpu(wx_info->beacon_wssi_b) & IN_BAND_FIWTEW;
	chain_sig_c = we32_to_cpu(wx_info->beacon_wssi_c) & IN_BAND_FIWTEW;

	spin_unwock_iwqwestowe(&iw->wock, fwags);

	data->beacon_count++;

	data->chain_noise_a = (chain_noise_a + data->chain_noise_a);
	data->chain_noise_b = (chain_noise_b + data->chain_noise_b);
	data->chain_noise_c = (chain_noise_c + data->chain_noise_c);

	data->chain_signaw_a = (chain_sig_a + data->chain_signaw_a);
	data->chain_signaw_b = (chain_sig_b + data->chain_signaw_b);
	data->chain_signaw_c = (chain_sig_c + data->chain_signaw_c);

	D_CAWIB("chan=%d, band24=%d, beacon=%d\n", wxon_chnum, wxon_band24,
		data->beacon_count);
	D_CAWIB("chain_sig: a %d b %d c %d\n", chain_sig_a, chain_sig_b,
		chain_sig_c);
	D_CAWIB("chain_noise: a %d b %d c %d\n", chain_noise_a, chain_noise_b,
		chain_noise_c);

	/* If this is the "chain_noise_num_beacons", detewmine:
	 * 1)  Disconnected antennas (using signaw stwengths)
	 * 2)  Diffewentiaw gain (using siwence noise) to bawance weceivews */
	if (data->beacon_count != iw->cfg->chain_noise_num_beacons)
		wetuwn;

	/* Anawyze signaw fow disconnected antenna */
	iw4965_find_disconn_antenna(iw, avewage_sig, data);

	/* Anawyze noise fow wx bawance */
	avewage_noise[0] =
	    data->chain_noise_a / iw->cfg->chain_noise_num_beacons;
	avewage_noise[1] =
	    data->chain_noise_b / iw->cfg->chain_noise_num_beacons;
	avewage_noise[2] =
	    data->chain_noise_c / iw->cfg->chain_noise_num_beacons;

	fow (i = 0; i < NUM_WX_CHAINS; i++) {
		if (!data->disconn_awway[i] &&
		    avewage_noise[i] <= min_avewage_noise) {
			/* This means that chain i is active and has
			 * wowew noise vawues so faw: */
			min_avewage_noise = avewage_noise[i];
			min_avewage_noise_antenna_i = i;
		}
	}

	D_CAWIB("avewage_noise: a %d b %d c %d\n", avewage_noise[0],
		avewage_noise[1], avewage_noise[2]);

	D_CAWIB("min_avewage_noise = %d, antenna %d\n", min_avewage_noise,
		min_avewage_noise_antenna_i);

	iw4965_gain_computation(iw, avewage_noise, min_avewage_noise_antenna_i,
				min_avewage_noise,
				iw4965_find_fiwst_chain(iw->cfg->vawid_wx_ant));

	/* Some powew changes may have been made duwing the cawibwation.
	 * Update and commit the WXON
	 */
	if (iw->ops->update_chain_fwags)
		iw->ops->update_chain_fwags(iw);

	data->state = IW_CHAIN_NOISE_DONE;
	iw_powew_update_mode(iw, fawse);
}

void
iw4965_weset_wun_time_cawib(stwuct iw_pwiv *iw)
{
	int i;
	memset(&(iw->sensitivity_data), 0, sizeof(stwuct iw_sensitivity_data));
	memset(&(iw->chain_noise_data), 0, sizeof(stwuct iw_chain_noise_data));
	fow (i = 0; i < NUM_WX_CHAINS; i++)
		iw->chain_noise_data.dewta_gain_code[i] =
		    CHAIN_NOISE_DEWTA_GAIN_INIT_VAW;

	/* Ask fow stats now, the uCode wiww send notification
	 * pewiodicawwy aftew association */
	iw_send_stats_wequest(iw, CMD_ASYNC, twue);
}
