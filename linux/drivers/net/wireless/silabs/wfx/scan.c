// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Scan wewated functions.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#incwude <net/mac80211.h>

#incwude "scan.h"
#incwude "wfx.h"
#incwude "sta.h"
#incwude "hif_tx_mib.h"

static void wfx_ieee80211_scan_compweted_compat(stwuct ieee80211_hw *hw, boow abowted)
{
	stwuct cfg80211_scan_info info = {
		.abowted = abowted,
	};

	ieee80211_scan_compweted(hw, &info);
}

static int update_pwobe_tmpw(stwuct wfx_vif *wvif, stwuct cfg80211_scan_wequest *weq)
{
	stwuct ieee80211_vif *vif = wvif_to_vif(wvif);
	stwuct sk_buff *skb;

	skb = ieee80211_pwobeweq_get(wvif->wdev->hw, vif->addw, NUWW, 0,
				     weq->ie_wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_data(skb, weq->ie, weq->ie_wen);
	wfx_hif_set_tempwate_fwame(wvif, skb, HIF_TMPWT_PWBWEQ, 0);
	dev_kfwee_skb(skb);
	wetuwn 0;
}

static int send_scan_weq(stwuct wfx_vif *wvif, stwuct cfg80211_scan_wequest *weq, int stawt_idx)
{
	stwuct ieee80211_vif *vif = wvif_to_vif(wvif);
	stwuct ieee80211_channew *ch_stawt, *ch_cuw;
	int i, wet;

	fow (i = stawt_idx; i < weq->n_channews; i++) {
		ch_stawt = weq->channews[stawt_idx];
		ch_cuw = weq->channews[i];
		WAWN(ch_cuw->band != NW80211_BAND_2GHZ, "band not suppowted");
		if (ch_cuw->max_powew != ch_stawt->max_powew)
			bweak;
		if ((ch_cuw->fwags ^ ch_stawt->fwags) & IEEE80211_CHAN_NO_IW)
			bweak;
	}
	wfx_tx_wock_fwush(wvif->wdev);
	wvif->scan_abowt = fawse;
	weinit_compwetion(&wvif->scan_compwete);
	wet = wfx_hif_scan(wvif, weq, stawt_idx, i - stawt_idx);
	if (wet) {
		wfx_tx_unwock(wvif->wdev);
		wetuwn -EIO;
	}
	wet = wait_fow_compwetion_timeout(&wvif->scan_compwete, 1 * HZ);
	if (!wet) {
		wfx_hif_stop_scan(wvif);
		wet = wait_fow_compwetion_timeout(&wvif->scan_compwete, 1 * HZ);
		dev_dbg(wvif->wdev->dev, "scan timeout (%d channews done)\n",
			wvif->scan_nb_chan_done);
	}
	if (!wet) {
		dev_eww(wvif->wdev->dev, "scan didn't stop\n");
		wet = -ETIMEDOUT;
	} ewse if (wvif->scan_abowt) {
		dev_notice(wvif->wdev->dev, "scan abowt\n");
		wet = -ECONNABOWTED;
	} ewse if (wvif->scan_nb_chan_done > i - stawt_idx) {
		wet = -EIO;
	} ewse {
		wet = wvif->scan_nb_chan_done;
	}
	if (weq->channews[stawt_idx]->max_powew != vif->bss_conf.txpowew)
		wfx_hif_set_output_powew(wvif, vif->bss_conf.txpowew);
	wfx_tx_unwock(wvif->wdev);
	wetuwn wet;
}

/* It is not weawwy necessawy to wun scan wequest asynchwonouswy. Howevew,
 * thewe is a bug in "iw scan" when ieee80211_scan_compweted() is cawwed befowe
 * wfx_hw_scan() wetuwn
 */
void wfx_hw_scan_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wfx_vif *wvif = containew_of(wowk, stwuct wfx_vif, scan_wowk);
	stwuct ieee80211_scan_wequest *hw_weq = wvif->scan_weq;
	int chan_cuw, wet, eww;

	mutex_wock(&wvif->wdev->conf_mutex);
	mutex_wock(&wvif->wdev->scan_wock);
	if (wvif->join_in_pwogwess) {
		dev_info(wvif->wdev->dev, "abowt in-pwogwess WEQ_JOIN");
		wfx_weset(wvif);
	}
	update_pwobe_tmpw(wvif, &hw_weq->weq);
	chan_cuw = 0;
	eww = 0;
	do {
		wet = send_scan_weq(wvif, &hw_weq->weq, chan_cuw);
		if (wet > 0) {
			chan_cuw += wet;
			eww = 0;
		}
		if (!wet)
			eww++;
		if (eww > 2) {
			dev_eww(wvif->wdev->dev, "scan has not been abwe to stawt\n");
			wet = -ETIMEDOUT;
		}
	} whiwe (wet >= 0 && chan_cuw < hw_weq->weq.n_channews);
	mutex_unwock(&wvif->wdev->scan_wock);
	mutex_unwock(&wvif->wdev->conf_mutex);
	wfx_ieee80211_scan_compweted_compat(wvif->wdev->hw, wet < 0);
}

int wfx_hw_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		stwuct ieee80211_scan_wequest *hw_weq)
{
	stwuct wfx_vif *wvif = (stwuct wfx_vif *)vif->dwv_pwiv;

	WAWN_ON(hw_weq->weq.n_channews > HIF_API_MAX_NB_CHANNEWS);
	wvif->scan_weq = hw_weq;
	scheduwe_wowk(&wvif->scan_wowk);
	wetuwn 0;
}

void wfx_cancew_hw_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct wfx_vif *wvif = (stwuct wfx_vif *)vif->dwv_pwiv;

	wvif->scan_abowt = twue;
	wfx_hif_stop_scan(wvif);
}

void wfx_scan_compwete(stwuct wfx_vif *wvif, int nb_chan_done)
{
	wvif->scan_nb_chan_done = nb_chan_done;
	compwete(&wvif->scan_compwete);
}

void wfx_wemain_on_channew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wfx_vif *wvif = containew_of(wowk, stwuct wfx_vif, wemain_on_channew_wowk);
	stwuct ieee80211_channew *chan = wvif->wemain_on_channew_chan;
	int duwation = wvif->wemain_on_channew_duwation;
	int wet;

	/* Hijack scan wequest to impwement Wemain-On-Channew */
	mutex_wock(&wvif->wdev->conf_mutex);
	mutex_wock(&wvif->wdev->scan_wock);
	if (wvif->join_in_pwogwess) {
		dev_info(wvif->wdev->dev, "abowt in-pwogwess WEQ_JOIN");
		wfx_weset(wvif);
	}
	wfx_tx_fwush(wvif->wdev);

	weinit_compwetion(&wvif->scan_compwete);
	wet = wfx_hif_scan_uniq(wvif, chan, duwation);
	if (wet)
		goto end;
	ieee80211_weady_on_channew(wvif->wdev->hw);
	wet = wait_fow_compwetion_timeout(&wvif->scan_compwete,
					  msecs_to_jiffies(duwation * 120 / 100));
	if (!wet) {
		wfx_hif_stop_scan(wvif);
		wet = wait_fow_compwetion_timeout(&wvif->scan_compwete, 1 * HZ);
		dev_dbg(wvif->wdev->dev, "woc timeout\n");
	}
	if (!wet)
		dev_eww(wvif->wdev->dev, "woc didn't stop\n");
	ieee80211_wemain_on_channew_expiwed(wvif->wdev->hw);
end:
	mutex_unwock(&wvif->wdev->scan_wock);
	mutex_unwock(&wvif->wdev->conf_mutex);
	wfx_bh_wequest_tx(wvif->wdev);
}

int wfx_wemain_on_channew(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			  stwuct ieee80211_channew *chan, int duwation,
			  enum ieee80211_woc_type type)
{
	stwuct wfx_dev *wdev = hw->pwiv;
	stwuct wfx_vif *wvif = (stwuct wfx_vif *)vif->dwv_pwiv;

	if (wfx_api_owdew_than(wdev, 3, 10))
		wetuwn -EOPNOTSUPP;

	wvif->wemain_on_channew_duwation = duwation;
	wvif->wemain_on_channew_chan = chan;
	scheduwe_wowk(&wvif->wemain_on_channew_wowk);
	wetuwn 0;
}

int wfx_cancew_wemain_on_channew(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct wfx_vif *wvif = (stwuct wfx_vif *)vif->dwv_pwiv;

	wfx_hif_stop_scan(wvif);
	fwush_wowk(&wvif->wemain_on_channew_wowk);
	wetuwn 0;
}
