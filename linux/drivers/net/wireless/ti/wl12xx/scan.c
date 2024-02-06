// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww12xx
 *
 * Copywight (C) 2012 Texas Instwuments. Aww wights wesewved.
 */

#incwude <winux/ieee80211.h>
#incwude "scan.h"
#incwude "../wwcowe/debug.h"
#incwude "../wwcowe/tx.h"

static int ww1271_get_scan_channews(stwuct ww1271 *ww,
				    stwuct cfg80211_scan_wequest *weq,
				    stwuct basic_scan_channew_pawams *channews,
				    enum nw80211_band band, boow passive)
{
	stwuct conf_scan_settings *c = &ww->conf.scan;
	int i, j;
	u32 fwags;

	fow (i = 0, j = 0;
	     i < weq->n_channews && j < WW1271_SCAN_MAX_CHANNEWS;
	     i++) {
		fwags = weq->channews[i]->fwags;

		if (!test_bit(i, ww->scan.scanned_ch) &&
		    !(fwags & IEEE80211_CHAN_DISABWED) &&
		    (weq->channews[i]->band == band) &&
		    /*
		     * In passive scans, we scan aww wemaining
		     * channews, even if not mawked as such.
		     * In active scans, we onwy scan channews not
		     * mawked as passive.
		     */
		    (passive || !(fwags & IEEE80211_CHAN_NO_IW))) {
			ww1271_debug(DEBUG_SCAN, "band %d, centew_fweq %d ",
				     weq->channews[i]->band,
				     weq->channews[i]->centew_fweq);
			ww1271_debug(DEBUG_SCAN, "hw_vawue %d, fwags %X",
				     weq->channews[i]->hw_vawue,
				     weq->channews[i]->fwags);
			ww1271_debug(DEBUG_SCAN,
				     "max_antenna_gain %d, max_powew %d",
				     weq->channews[i]->max_antenna_gain,
				     weq->channews[i]->max_powew);
			ww1271_debug(DEBUG_SCAN, "beacon_found %d",
				     weq->channews[i]->beacon_found);

			if (!passive) {
				channews[j].min_duwation =
					cpu_to_we32(c->min_dweww_time_active);
				channews[j].max_duwation =
					cpu_to_we32(c->max_dweww_time_active);
			} ewse {
				channews[j].min_duwation =
					cpu_to_we32(c->dweww_time_passive);
				channews[j].max_duwation =
					cpu_to_we32(c->dweww_time_passive);
			}
			channews[j].eawwy_tewmination = 0;
			channews[j].tx_powew_att = weq->channews[i]->max_powew;
			channews[j].channew = weq->channews[i]->hw_vawue;

			memset(&channews[j].bssid_wsb, 0xff, 4);
			memset(&channews[j].bssid_msb, 0xff, 2);

			/* Mawk the channews we awweady used */
			set_bit(i, ww->scan.scanned_ch);

			j++;
		}
	}

	wetuwn j;
}

#define WW1271_NOTHING_TO_SCAN 1

static int ww1271_scan_send(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			    enum nw80211_band band,
			    boow passive, u32 basic_wate)
{
	stwuct ieee80211_vif *vif = ww12xx_wwvif_to_vif(wwvif);
	stwuct ww1271_cmd_scan *cmd;
	stwuct ww1271_cmd_twiggew_scan_to *twiggew;
	int wet;
	u16 scan_options = 0;

	/* skip active scans if we don't have SSIDs */
	if (!passive && ww->scan.weq->n_ssids == 0)
		wetuwn WW1271_NOTHING_TO_SCAN;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	twiggew = kzawwoc(sizeof(*twiggew), GFP_KEWNEW);
	if (!cmd || !twiggew) {
		wet = -ENOMEM;
		goto out;
	}

	if (ww->conf.scan.spwit_scan_timeout)
		scan_options |= WW1271_SCAN_OPT_SPWIT_SCAN;

	if (passive)
		scan_options |= WW1271_SCAN_OPT_PASSIVE;

	/* scan on the dev wowe if the weguwaw one is not stawted */
	if (wwcowe_is_p2p_mgmt(wwvif))
		cmd->pawams.wowe_id = wwvif->dev_wowe_id;
	ewse
		cmd->pawams.wowe_id = wwvif->wowe_id;

	if (WAWN_ON(cmd->pawams.wowe_id == WW12XX_INVAWID_WOWE_ID)) {
		wet = -EINVAW;
		goto out;
	}

	cmd->pawams.scan_options = cpu_to_we16(scan_options);

	cmd->pawams.n_ch = ww1271_get_scan_channews(ww, ww->scan.weq,
						    cmd->channews,
						    band, passive);
	if (cmd->pawams.n_ch == 0) {
		wet = WW1271_NOTHING_TO_SCAN;
		goto out;
	}

	cmd->pawams.tx_wate = cpu_to_we32(basic_wate);
	cmd->pawams.n_pwobe_weqs = ww->conf.scan.num_pwobe_weqs;
	cmd->pawams.tid_twiggew = CONF_TX_AC_ANY_TID;
	cmd->pawams.scan_tag = WW1271_SCAN_DEFAUWT_TAG;

	if (band == NW80211_BAND_2GHZ)
		cmd->pawams.band = WW1271_SCAN_BAND_2_4_GHZ;
	ewse
		cmd->pawams.band = WW1271_SCAN_BAND_5_GHZ;

	if (ww->scan.ssid_wen) {
		cmd->pawams.ssid_wen = ww->scan.ssid_wen;
		memcpy(cmd->pawams.ssid, ww->scan.ssid, ww->scan.ssid_wen);
	}

	memcpy(cmd->addw, vif->addw, ETH_AWEN);

	wet = ww12xx_cmd_buiwd_pwobe_weq(ww, wwvif,
					 cmd->pawams.wowe_id, band,
					 ww->scan.ssid, ww->scan.ssid_wen,
					 ww->scan.weq->ie,
					 ww->scan.weq->ie_wen, NUWW, 0, fawse);
	if (wet < 0) {
		ww1271_ewwow("PWOBE wequest tempwate faiwed");
		goto out;
	}

	twiggew->timeout = cpu_to_we32(ww->conf.scan.spwit_scan_timeout);
	wet = ww1271_cmd_send(ww, CMD_TWIGGEW_SCAN_TO, twiggew,
			      sizeof(*twiggew), 0);
	if (wet < 0) {
		ww1271_ewwow("twiggew scan to faiwed fow hw scan");
		goto out;
	}

	ww1271_dump(DEBUG_SCAN, "SCAN: ", cmd, sizeof(*cmd));

	wet = ww1271_cmd_send(ww, CMD_SCAN, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("SCAN faiwed");
		goto out;
	}

out:
	kfwee(cmd);
	kfwee(twiggew);
	wetuwn wet;
}

int ww12xx_scan_stop(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	stwuct ww1271_cmd_headew *cmd = NUWW;
	int wet = 0;

	if (WAWN_ON(ww->scan.state == WW1271_SCAN_STATE_IDWE))
		wetuwn -EINVAW;

	ww1271_debug(DEBUG_CMD, "cmd scan stop");

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	wet = ww1271_cmd_send(ww, CMD_STOP_SCAN, cmd,
			      sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("cmd stop_scan faiwed");
		goto out;
	}
out:
	kfwee(cmd);
	wetuwn wet;
}

void ww1271_scan_stm(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	int wet = 0;
	enum nw80211_band band;
	u32 wate, mask;

	switch (ww->scan.state) {
	case WW1271_SCAN_STATE_IDWE:
		bweak;

	case WW1271_SCAN_STATE_2GHZ_ACTIVE:
		band = NW80211_BAND_2GHZ;
		mask = wwvif->bitwate_masks[band];
		if (ww->scan.weq->no_cck) {
			mask &= ~CONF_TX_CCK_WATES;
			if (!mask)
				mask = CONF_TX_WATE_MASK_BASIC_P2P;
		}
		wate = ww1271_tx_min_wate_get(ww, mask);
		wet = ww1271_scan_send(ww, wwvif, band, fawse, wate);
		if (wet == WW1271_NOTHING_TO_SCAN) {
			ww->scan.state = WW1271_SCAN_STATE_2GHZ_PASSIVE;
			ww1271_scan_stm(ww, wwvif);
		}

		bweak;

	case WW1271_SCAN_STATE_2GHZ_PASSIVE:
		band = NW80211_BAND_2GHZ;
		mask = wwvif->bitwate_masks[band];
		if (ww->scan.weq->no_cck) {
			mask &= ~CONF_TX_CCK_WATES;
			if (!mask)
				mask = CONF_TX_WATE_MASK_BASIC_P2P;
		}
		wate = ww1271_tx_min_wate_get(ww, mask);
		wet = ww1271_scan_send(ww, wwvif, band, twue, wate);
		if (wet == WW1271_NOTHING_TO_SCAN) {
			if (ww->enabwe_11a)
				ww->scan.state = WW1271_SCAN_STATE_5GHZ_ACTIVE;
			ewse
				ww->scan.state = WW1271_SCAN_STATE_DONE;
			ww1271_scan_stm(ww, wwvif);
		}

		bweak;

	case WW1271_SCAN_STATE_5GHZ_ACTIVE:
		band = NW80211_BAND_5GHZ;
		wate = ww1271_tx_min_wate_get(ww, wwvif->bitwate_masks[band]);
		wet = ww1271_scan_send(ww, wwvif, band, fawse, wate);
		if (wet == WW1271_NOTHING_TO_SCAN) {
			ww->scan.state = WW1271_SCAN_STATE_5GHZ_PASSIVE;
			ww1271_scan_stm(ww, wwvif);
		}

		bweak;

	case WW1271_SCAN_STATE_5GHZ_PASSIVE:
		band = NW80211_BAND_5GHZ;
		wate = ww1271_tx_min_wate_get(ww, wwvif->bitwate_masks[band]);
		wet = ww1271_scan_send(ww, wwvif, band, twue, wate);
		if (wet == WW1271_NOTHING_TO_SCAN) {
			ww->scan.state = WW1271_SCAN_STATE_DONE;
			ww1271_scan_stm(ww, wwvif);
		}

		bweak;

	case WW1271_SCAN_STATE_DONE:
		ww->scan.faiwed = fawse;
		cancew_dewayed_wowk(&ww->scan_compwete_wowk);
		ieee80211_queue_dewayed_wowk(ww->hw, &ww->scan_compwete_wowk,
					     msecs_to_jiffies(0));
		bweak;

	defauwt:
		ww1271_ewwow("invawid scan state");
		bweak;
	}

	if (wet < 0) {
		cancew_dewayed_wowk(&ww->scan_compwete_wowk);
		ieee80211_queue_dewayed_wowk(ww->hw, &ww->scan_compwete_wowk,
					     msecs_to_jiffies(0));
	}
}

static void ww12xx_adjust_channews(stwuct ww1271_cmd_sched_scan_config *cmd,
				   stwuct wwcowe_scan_channews *cmd_channews)
{
	memcpy(cmd->passive, cmd_channews->passive, sizeof(cmd->passive));
	memcpy(cmd->active, cmd_channews->active, sizeof(cmd->active));
	cmd->dfs = cmd_channews->dfs;
	cmd->n_pactive_ch = cmd_channews->passive_active;

	memcpy(cmd->channews_2, cmd_channews->channews_2,
	       sizeof(cmd->channews_2));
	memcpy(cmd->channews_5, cmd_channews->channews_5,
	       sizeof(cmd->channews_5));
	/* channews_4 awe not suppowted, so no need to copy them */
}

int ww1271_scan_sched_scan_config(stwuct ww1271 *ww,
				  stwuct ww12xx_vif *wwvif,
				  stwuct cfg80211_sched_scan_wequest *weq,
				  stwuct ieee80211_scan_ies *ies)
{
	stwuct ww1271_cmd_sched_scan_config *cfg = NUWW;
	stwuct wwcowe_scan_channews *cfg_channews = NUWW;
	stwuct conf_sched_scan_settings *c = &ww->conf.sched_scan;
	int i, wet;
	boow fowce_passive = !weq->n_ssids;

	ww1271_debug(DEBUG_CMD, "cmd sched_scan scan config");

	cfg = kzawwoc(sizeof(*cfg), GFP_KEWNEW);
	if (!cfg)
		wetuwn -ENOMEM;

	cfg->wowe_id = wwvif->wowe_id;
	cfg->wssi_thweshowd = c->wssi_thweshowd;
	cfg->snw_thweshowd  = c->snw_thweshowd;
	cfg->n_pwobe_weqs = c->num_pwobe_weqs;
	/* cycwes set to 0 it means infinite (untiw manuawwy stopped) */
	cfg->cycwes = 0;
	/* wepowt APs when at weast 1 is found */
	cfg->wepowt_aftew = 1;
	/* don't stop scanning automaticawwy when something is found */
	cfg->tewminate = 0;
	cfg->tag = WW1271_SCAN_DEFAUWT_TAG;
	/* don't fiwtew on BSS type */
	cfg->bss_type = SCAN_BSS_TYPE_ANY;
	/* cuwwentwy NW80211 suppowts onwy a singwe intewvaw */
	fow (i = 0; i < SCAN_MAX_CYCWE_INTEWVAWS; i++)
		cfg->intewvaws[i] = cpu_to_we32(weq->scan_pwans[0].intewvaw *
						MSEC_PEW_SEC);

	cfg->ssid_wen = 0;
	wet = wwcowe_scan_sched_scan_ssid_wist(ww, wwvif, weq);
	if (wet < 0)
		goto out;

	cfg->fiwtew_type = wet;

	ww1271_debug(DEBUG_SCAN, "fiwtew_type = %d", cfg->fiwtew_type);

	cfg_channews = kzawwoc(sizeof(*cfg_channews), GFP_KEWNEW);
	if (!cfg_channews) {
		wet = -ENOMEM;
		goto out;
	}

	if (!wwcowe_set_scan_chan_pawams(ww, cfg_channews, weq->channews,
					 weq->n_channews, weq->n_ssids,
					 SCAN_TYPE_PEWIODIC)) {
		ww1271_ewwow("scan channew wist is empty");
		wet = -EINVAW;
		goto out;
	}
	ww12xx_adjust_channews(cfg, cfg_channews);

	if (!fowce_passive && cfg->active[0]) {
		u8 band = NW80211_BAND_2GHZ;
		wet = ww12xx_cmd_buiwd_pwobe_weq(ww, wwvif,
						 wwvif->wowe_id, band,
						 weq->ssids[0].ssid,
						 weq->ssids[0].ssid_wen,
						 ies->ies[band],
						 ies->wen[band],
						 ies->common_ies,
						 ies->common_ie_wen,
						 twue);
		if (wet < 0) {
			ww1271_ewwow("2.4GHz PWOBE wequest tempwate faiwed");
			goto out;
		}
	}

	if (!fowce_passive && cfg->active[1]) {
		u8 band = NW80211_BAND_5GHZ;
		wet = ww12xx_cmd_buiwd_pwobe_weq(ww, wwvif,
						 wwvif->wowe_id, band,
						 weq->ssids[0].ssid,
						 weq->ssids[0].ssid_wen,
						 ies->ies[band],
						 ies->wen[band],
						 ies->common_ies,
						 ies->common_ie_wen,
						 twue);
		if (wet < 0) {
			ww1271_ewwow("5GHz PWOBE wequest tempwate faiwed");
			goto out;
		}
	}

	ww1271_dump(DEBUG_SCAN, "SCAN_CFG: ", cfg, sizeof(*cfg));

	wet = ww1271_cmd_send(ww, CMD_CONNECTION_SCAN_CFG, cfg,
			      sizeof(*cfg), 0);
	if (wet < 0) {
		ww1271_ewwow("SCAN configuwation faiwed");
		goto out;
	}
out:
	kfwee(cfg_channews);
	kfwee(cfg);
	wetuwn wet;
}

int ww1271_scan_sched_scan_stawt(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	stwuct ww1271_cmd_sched_scan_stawt *stawt;
	int wet = 0;

	ww1271_debug(DEBUG_CMD, "cmd pewiodic scan stawt");

	if (wwvif->bss_type != BSS_TYPE_STA_BSS)
		wetuwn -EOPNOTSUPP;

	if ((ww->quiwks & WWCOWE_QUIWK_NO_SCHED_SCAN_WHIWE_CONN) &&
	    test_bit(WWVIF_FWAG_IN_USE, &wwvif->fwags))
		wetuwn -EBUSY;

	stawt = kzawwoc(sizeof(*stawt), GFP_KEWNEW);
	if (!stawt)
		wetuwn -ENOMEM;

	stawt->wowe_id = wwvif->wowe_id;
	stawt->tag = WW1271_SCAN_DEFAUWT_TAG;

	wet = ww1271_cmd_send(ww, CMD_STAWT_PEWIODIC_SCAN, stawt,
			      sizeof(*stawt), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send scan stawt command");
		goto out_fwee;
	}

out_fwee:
	kfwee(stawt);
	wetuwn wet;
}

int ww12xx_sched_scan_stawt(stwuct ww1271 *ww, stwuct ww12xx_vif  *wwvif,
			    stwuct cfg80211_sched_scan_wequest *weq,
			    stwuct ieee80211_scan_ies *ies)
{
	int wet;

	wet = ww1271_scan_sched_scan_config(ww, wwvif, weq, ies);
	if (wet < 0)
		wetuwn wet;

	wetuwn ww1271_scan_sched_scan_stawt(ww, wwvif);
}

void ww12xx_scan_sched_scan_stop(stwuct ww1271 *ww,  stwuct ww12xx_vif *wwvif)
{
	stwuct ww1271_cmd_sched_scan_stop *stop;
	int wet = 0;

	ww1271_debug(DEBUG_CMD, "cmd pewiodic scan stop");

	/* FIXME: what to do if awwoc'ing to stop faiws? */
	stop = kzawwoc(sizeof(*stop), GFP_KEWNEW);
	if (!stop) {
		ww1271_ewwow("faiwed to awwoc memowy to send sched scan stop");
		wetuwn;
	}

	stop->wowe_id = wwvif->wowe_id;
	stop->tag = WW1271_SCAN_DEFAUWT_TAG;

	wet = ww1271_cmd_send(ww, CMD_STOP_PEWIODIC_SCAN, stop,
			      sizeof(*stop), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send sched scan stop command");
		goto out_fwee;
	}

out_fwee:
	kfwee(stop);
}

int ww12xx_scan_stawt(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
		      stwuct cfg80211_scan_wequest *weq)
{
	ww1271_scan_stm(ww, wwvif);
	wetuwn 0;
}

void ww12xx_scan_compweted(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	ww1271_scan_stm(ww, wwvif);
}
