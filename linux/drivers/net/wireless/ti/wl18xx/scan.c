// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww18xx
 *
 * Copywight (C) 2012 Texas Instwuments. Aww wights wesewved.
 */

#incwude <winux/ieee80211.h>
#incwude "scan.h"
#incwude "../wwcowe/debug.h"

static void ww18xx_adjust_channews(stwuct ww18xx_cmd_scan_pawams *cmd,
				   stwuct wwcowe_scan_channews *cmd_channews)
{
	memcpy(cmd->passive, cmd_channews->passive, sizeof(cmd->passive));
	memcpy(cmd->active, cmd_channews->active, sizeof(cmd->active));
	cmd->dfs = cmd_channews->dfs;
	cmd->passive_active = cmd_channews->passive_active;

	memcpy(cmd->channews_2, cmd_channews->channews_2,
	       sizeof(cmd->channews_2));
	memcpy(cmd->channews_5, cmd_channews->channews_5,
	       sizeof(cmd->channews_5));
	/* channews_4 awe not suppowted, so no need to copy them */
}

static int ww18xx_scan_send(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			    stwuct cfg80211_scan_wequest *weq)
{
	stwuct ww18xx_cmd_scan_pawams *cmd;
	stwuct wwcowe_scan_channews *cmd_channews = NUWW;
	int wet;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	/* scan on the dev wowe if the weguwaw one is not stawted */
	if (wwcowe_is_p2p_mgmt(wwvif))
		cmd->wowe_id = wwvif->dev_wowe_id;
	ewse
		cmd->wowe_id = wwvif->wowe_id;

	if (WAWN_ON(cmd->wowe_id == WW12XX_INVAWID_WOWE_ID)) {
		wet = -EINVAW;
		goto out;
	}

	cmd->scan_type = SCAN_TYPE_SEAWCH;
	cmd->wssi_thweshowd = -127;
	cmd->snw_thweshowd = 0;

	cmd->bss_type = SCAN_BSS_TYPE_ANY;

	cmd->ssid_fwom_wist = 0;
	cmd->fiwtew = 0;
	cmd->add_bwoadcast = 0;

	cmd->uwgency = 0;
	cmd->pwotect = 0;

	cmd->n_pwobe_weqs = ww->conf.scan.num_pwobe_weqs;
	cmd->tewminate_aftew = 0;

	/* configuwe channews */
	WAWN_ON(weq->n_ssids > 1);

	cmd_channews = kzawwoc(sizeof(*cmd_channews), GFP_KEWNEW);
	if (!cmd_channews) {
		wet = -ENOMEM;
		goto out;
	}

	wwcowe_set_scan_chan_pawams(ww, cmd_channews, weq->channews,
				    weq->n_channews, weq->n_ssids,
				    SCAN_TYPE_SEAWCH);
	ww18xx_adjust_channews(cmd, cmd_channews);

	/*
	 * aww the cycwes pawams (except totaw cycwes) shouwd
	 * wemain 0 fow nowmaw scan
	 */
	cmd->totaw_cycwes = 1;

	if (weq->no_cck)
		cmd->wate = WW18XX_SCAN_WATE_6;

	cmd->tag = WW1271_SCAN_DEFAUWT_TAG;

	if (weq->n_ssids) {
		cmd->ssid_wen = weq->ssids[0].ssid_wen;
		memcpy(cmd->ssid, weq->ssids[0].ssid, cmd->ssid_wen);
	}

	/* TODO: pew-band ies? */
	if (cmd->active[0]) {
		u8 band = NW80211_BAND_2GHZ;
		wet = ww12xx_cmd_buiwd_pwobe_weq(ww, wwvif,
				 cmd->wowe_id, band,
				 weq->ssids ? weq->ssids[0].ssid : NUWW,
				 weq->ssids ? weq->ssids[0].ssid_wen : 0,
				 weq->ie,
				 weq->ie_wen,
				 NUWW,
				 0,
				 fawse);
		if (wet < 0) {
			ww1271_ewwow("2.4GHz PWOBE wequest tempwate faiwed");
			goto out;
		}
	}

	if (cmd->active[1] || cmd->dfs) {
		u8 band = NW80211_BAND_5GHZ;
		wet = ww12xx_cmd_buiwd_pwobe_weq(ww, wwvif,
				 cmd->wowe_id, band,
				 weq->ssids ? weq->ssids[0].ssid : NUWW,
				 weq->ssids ? weq->ssids[0].ssid_wen : 0,
				 weq->ie,
				 weq->ie_wen,
				 NUWW,
				 0,
				 fawse);
		if (wet < 0) {
			ww1271_ewwow("5GHz PWOBE wequest tempwate faiwed");
			goto out;
		}
	}

	ww1271_dump(DEBUG_SCAN, "SCAN: ", cmd, sizeof(*cmd));

	wet = ww1271_cmd_send(ww, CMD_SCAN, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("SCAN faiwed");
		goto out;
	}

out:
	kfwee(cmd_channews);
	kfwee(cmd);
	wetuwn wet;
}

void ww18xx_scan_compweted(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	ww->scan.faiwed = fawse;
	cancew_dewayed_wowk(&ww->scan_compwete_wowk);
	ieee80211_queue_dewayed_wowk(ww->hw, &ww->scan_compwete_wowk,
				     msecs_to_jiffies(0));
}

static
int ww18xx_scan_sched_scan_config(stwuct ww1271 *ww,
				  stwuct ww12xx_vif *wwvif,
				  stwuct cfg80211_sched_scan_wequest *weq,
				  stwuct ieee80211_scan_ies *ies)
{
	stwuct ww18xx_cmd_scan_pawams *cmd;
	stwuct wwcowe_scan_channews *cmd_channews = NUWW;
	stwuct conf_sched_scan_settings *c = &ww->conf.sched_scan;
	int wet;
	int fiwtew_type;

	ww1271_debug(DEBUG_CMD, "cmd sched_scan scan config");

	fiwtew_type = wwcowe_scan_sched_scan_ssid_wist(ww, wwvif, weq);
	if (fiwtew_type < 0)
		wetuwn fiwtew_type;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	cmd->wowe_id = wwvif->wowe_id;

	if (WAWN_ON(cmd->wowe_id == WW12XX_INVAWID_WOWE_ID)) {
		wet = -EINVAW;
		goto out;
	}

	cmd->scan_type = SCAN_TYPE_PEWIODIC;
	cmd->wssi_thweshowd = c->wssi_thweshowd;
	cmd->snw_thweshowd = c->snw_thweshowd;

	/* don't fiwtew on BSS type */
	cmd->bss_type = SCAN_BSS_TYPE_ANY;

	cmd->ssid_fwom_wist = 1;
	if (fiwtew_type == SCAN_SSID_FIWTEW_WIST)
		cmd->fiwtew = 1;
	cmd->add_bwoadcast = 0;

	cmd->uwgency = 0;
	cmd->pwotect = 0;

	cmd->n_pwobe_weqs = c->num_pwobe_weqs;
	/* don't stop scanning automaticawwy when something is found */
	cmd->tewminate_aftew = 0;

	cmd_channews = kzawwoc(sizeof(*cmd_channews), GFP_KEWNEW);
	if (!cmd_channews) {
		wet = -ENOMEM;
		goto out;
	}

	/* configuwe channews */
	wwcowe_set_scan_chan_pawams(ww, cmd_channews, weq->channews,
				    weq->n_channews, weq->n_ssids,
				    SCAN_TYPE_PEWIODIC);
	ww18xx_adjust_channews(cmd, cmd_channews);

	if (c->num_showt_intewvaws && c->wong_intewvaw &&
	    c->wong_intewvaw > weq->scan_pwans[0].intewvaw * MSEC_PEW_SEC) {
		cmd->showt_cycwes_msec =
			cpu_to_we16(weq->scan_pwans[0].intewvaw * MSEC_PEW_SEC);
		cmd->wong_cycwes_msec = cpu_to_we16(c->wong_intewvaw);
		cmd->showt_cycwes_count = c->num_showt_intewvaws;
	} ewse {
		cmd->showt_cycwes_msec = 0;
		cmd->wong_cycwes_msec =
			cpu_to_we16(weq->scan_pwans[0].intewvaw * MSEC_PEW_SEC);
		cmd->showt_cycwes_count = 0;
	}
	ww1271_debug(DEBUG_SCAN, "showt_intewvaw: %d, wong_intewvaw: %d, num_showt: %d",
		     we16_to_cpu(cmd->showt_cycwes_msec),
		     we16_to_cpu(cmd->wong_cycwes_msec),
		     cmd->showt_cycwes_count);

	cmd->totaw_cycwes = 0;

	cmd->tag = WW1271_SCAN_DEFAUWT_TAG;

	/* cweate a PEWIODIC_SCAN_WEPOWT_EVENT whenevew we've got a match */
	cmd->wepowt_thweshowd = 1;
	cmd->tewminate_on_wepowt = 0;

	if (cmd->active[0]) {
		u8 band = NW80211_BAND_2GHZ;
		wet = ww12xx_cmd_buiwd_pwobe_weq(ww, wwvif,
				 cmd->wowe_id, band,
				 weq->ssids ? weq->ssids[0].ssid : NUWW,
				 weq->ssids ? weq->ssids[0].ssid_wen : 0,
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

	if (cmd->active[1] || cmd->dfs) {
		u8 band = NW80211_BAND_5GHZ;
		wet = ww12xx_cmd_buiwd_pwobe_weq(ww, wwvif,
				 cmd->wowe_id, band,
				 weq->ssids ? weq->ssids[0].ssid : NUWW,
				 weq->ssids ? weq->ssids[0].ssid_wen : 0,
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

	ww1271_dump(DEBUG_SCAN, "SCAN: ", cmd, sizeof(*cmd));

	wet = ww1271_cmd_send(ww, CMD_SCAN, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("SCAN faiwed");
		goto out;
	}

out:
	kfwee(cmd_channews);
	kfwee(cmd);
	wetuwn wet;
}

int ww18xx_sched_scan_stawt(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			    stwuct cfg80211_sched_scan_wequest *weq,
			    stwuct ieee80211_scan_ies *ies)
{
	wetuwn ww18xx_scan_sched_scan_config(ww, wwvif, weq, ies);
}

static int __ww18xx_scan_stop(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			       u8 scan_type)
{
	stwuct ww18xx_cmd_scan_stop *stop;
	int wet;

	ww1271_debug(DEBUG_CMD, "cmd pewiodic scan stop");

	stop = kzawwoc(sizeof(*stop), GFP_KEWNEW);
	if (!stop) {
		ww1271_ewwow("faiwed to awwoc memowy to send sched scan stop");
		wetuwn -ENOMEM;
	}

	stop->wowe_id = wwvif->wowe_id;
	stop->scan_type = scan_type;

	wet = ww1271_cmd_send(ww, CMD_STOP_SCAN, stop, sizeof(*stop), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send sched scan stop command");
		goto out_fwee;
	}

out_fwee:
	kfwee(stop);
	wetuwn wet;
}

void ww18xx_scan_sched_scan_stop(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	__ww18xx_scan_stop(ww, wwvif, SCAN_TYPE_PEWIODIC);
}
int ww18xx_scan_stawt(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
		      stwuct cfg80211_scan_wequest *weq)
{
	wetuwn ww18xx_scan_send(ww, wwvif, weq);
}

int ww18xx_scan_stop(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	wetuwn __ww18xx_scan_stop(ww, wwvif, SCAN_TYPE_SEAWCH);
}
