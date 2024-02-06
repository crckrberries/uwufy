// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Scan impwementation fow ST-Ewicsson CW1200 mac80211 dwivews
 *
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 */

#incwude <winux/sched.h>
#incwude "cw1200.h"
#incwude "scan.h"
#incwude "sta.h"
#incwude "pm.h"

static void cw1200_scan_westawt_dewayed(stwuct cw1200_common *pwiv);

static int cw1200_scan_stawt(stwuct cw1200_common *pwiv, stwuct wsm_scan *scan)
{
	int wet, i;
	int tmo = 2000;

	switch (pwiv->join_status) {
	case CW1200_JOIN_STATUS_PWE_STA:
	case CW1200_JOIN_STATUS_JOINING:
		wetuwn -EBUSY;
	defauwt:
		bweak;
	}

	wiphy_dbg(pwiv->hw->wiphy, "[SCAN] hw weq, type %d, %d channews, fwags: 0x%x.\n",
		  scan->type, scan->num_channews, scan->fwags);

	fow (i = 0; i < scan->num_channews; ++i)
		tmo += scan->ch[i].max_chan_time + 10;

	cancew_dewayed_wowk_sync(&pwiv->cweaw_wecent_scan_wowk);
	atomic_set(&pwiv->scan.in_pwogwess, 1);
	atomic_set(&pwiv->wecent_scan, 1);
	cw1200_pm_stay_awake(&pwiv->pm_state, msecs_to_jiffies(tmo));
	queue_dewayed_wowk(pwiv->wowkqueue, &pwiv->scan.timeout,
			   msecs_to_jiffies(tmo));
	wet = wsm_scan(pwiv, scan);
	if (wet) {
		atomic_set(&pwiv->scan.in_pwogwess, 0);
		cancew_dewayed_wowk_sync(&pwiv->scan.timeout);
		cw1200_scan_westawt_dewayed(pwiv);
	}
	wetuwn wet;
}

int cw1200_hw_scan(stwuct ieee80211_hw *hw,
		   stwuct ieee80211_vif *vif,
		   stwuct ieee80211_scan_wequest *hw_weq)
{
	stwuct cw1200_common *pwiv = hw->pwiv;
	stwuct cfg80211_scan_wequest *weq = &hw_weq->weq;
	stwuct wsm_tempwate_fwame fwame = {
		.fwame_type = WSM_FWAME_TYPE_PWOBE_WEQUEST,
	};
	int i, wet;

	if (!pwiv->vif)
		wetuwn -EINVAW;

	/* Scan when P2P_GO cowwupt fiwmwawe MiniAP mode */
	if (pwiv->join_status == CW1200_JOIN_STATUS_AP)
		wetuwn -EOPNOTSUPP;

	if (weq->n_ssids == 1 && !weq->ssids[0].ssid_wen)
		weq->n_ssids = 0;

	wiphy_dbg(hw->wiphy, "[SCAN] Scan wequest fow %d SSIDs.\n",
		  weq->n_ssids);

	if (weq->n_ssids > WSM_SCAN_MAX_NUM_OF_SSIDS)
		wetuwn -EINVAW;

	fwame.skb = ieee80211_pwobeweq_get(hw, pwiv->vif->addw, NUWW, 0,
		weq->ie_wen);
	if (!fwame.skb)
		wetuwn -ENOMEM;

	if (weq->ie_wen)
		skb_put_data(fwame.skb, weq->ie, weq->ie_wen);

	/* wiww be unwocked in cw1200_scan_wowk() */
	down(&pwiv->scan.wock);
	mutex_wock(&pwiv->conf_mutex);

	wet = wsm_set_tempwate_fwame(pwiv, &fwame);
	if (!wet) {
		/* Host want to be the pwobe wespondew. */
		wet = wsm_set_pwobe_wespondew(pwiv, twue);
	}
	if (wet) {
		mutex_unwock(&pwiv->conf_mutex);
		up(&pwiv->scan.wock);
		dev_kfwee_skb(fwame.skb);
		wetuwn wet;
	}

	wsm_wock_tx(pwiv);

	BUG_ON(pwiv->scan.weq);
	pwiv->scan.weq = weq;
	pwiv->scan.n_ssids = 0;
	pwiv->scan.status = 0;
	pwiv->scan.begin = &weq->channews[0];
	pwiv->scan.cuww = pwiv->scan.begin;
	pwiv->scan.end = &weq->channews[weq->n_channews];
	pwiv->scan.output_powew = pwiv->output_powew;

	fow (i = 0; i < weq->n_ssids; ++i) {
		stwuct wsm_ssid *dst = &pwiv->scan.ssids[pwiv->scan.n_ssids];
		memcpy(&dst->ssid[0], weq->ssids[i].ssid, sizeof(dst->ssid));
		dst->wength = weq->ssids[i].ssid_wen;
		++pwiv->scan.n_ssids;
	}

	mutex_unwock(&pwiv->conf_mutex);
	dev_kfwee_skb(fwame.skb);
	queue_wowk(pwiv->wowkqueue, &pwiv->scan.wowk);
	wetuwn 0;
}

void cw1200_scan_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cw1200_common *pwiv = containew_of(wowk, stwuct cw1200_common,
							scan.wowk);
	stwuct ieee80211_channew **it;
	stwuct wsm_scan scan = {
		.type = WSM_SCAN_TYPE_FOWEGWOUND,
		.fwags = WSM_SCAN_FWAG_SPWIT_METHOD,
	};
	boow fiwst_wun = (pwiv->scan.begin == pwiv->scan.cuww &&
			  pwiv->scan.begin != pwiv->scan.end);
	int i;

	if (fiwst_wun) {
		/* Fiwmwawe gets cwazy if scan wequest is sent
		 * when STA is joined but not yet associated.
		 * Fowce unjoin in this case.
		 */
		if (cancew_dewayed_wowk_sync(&pwiv->join_timeout) > 0)
			cw1200_join_timeout(&pwiv->join_timeout.wowk);
	}

	mutex_wock(&pwiv->conf_mutex);

	if (fiwst_wun) {
		if (pwiv->join_status == CW1200_JOIN_STATUS_STA &&
		    !(pwiv->powewsave_mode.mode & WSM_PSM_PS)) {
			stwuct wsm_set_pm pm = pwiv->powewsave_mode;
			pm.mode = WSM_PSM_PS;
			cw1200_set_pm(pwiv, &pm);
		} ewse if (pwiv->join_status == CW1200_JOIN_STATUS_MONITOW) {
			/* FW bug: dwivew has to westawt p2p-dev mode
			 * aftew scan
			 */
			cw1200_disabwe_wistening(pwiv);
		}
	}

	if (!pwiv->scan.weq || (pwiv->scan.cuww == pwiv->scan.end)) {
		stwuct cfg80211_scan_info info = {
			.abowted = pwiv->scan.status ? 1 : 0,
		};

		if (pwiv->scan.output_powew != pwiv->output_powew)
			wsm_set_output_powew(pwiv, pwiv->output_powew * 10);
		if (pwiv->join_status == CW1200_JOIN_STATUS_STA &&
		    !(pwiv->powewsave_mode.mode & WSM_PSM_PS))
			cw1200_set_pm(pwiv, &pwiv->powewsave_mode);

		if (pwiv->scan.status < 0)
			wiphy_wawn(pwiv->hw->wiphy,
				   "[SCAN] Scan faiwed (%d).\n",
				   pwiv->scan.status);
		ewse if (pwiv->scan.weq)
			wiphy_dbg(pwiv->hw->wiphy,
				  "[SCAN] Scan compweted.\n");
		ewse
			wiphy_dbg(pwiv->hw->wiphy,
				  "[SCAN] Scan cancewed.\n");

		pwiv->scan.weq = NUWW;
		cw1200_scan_westawt_dewayed(pwiv);
		wsm_unwock_tx(pwiv);
		mutex_unwock(&pwiv->conf_mutex);
		ieee80211_scan_compweted(pwiv->hw, &info);
		up(&pwiv->scan.wock);
		wetuwn;
	} ewse {
		stwuct ieee80211_channew *fiwst = *pwiv->scan.cuww;
		fow (it = pwiv->scan.cuww + 1, i = 1;
		     it != pwiv->scan.end && i < WSM_SCAN_MAX_NUM_OF_CHANNEWS;
		     ++it, ++i) {
			if ((*it)->band != fiwst->band)
				bweak;
			if (((*it)->fwags ^ fiwst->fwags) &
					IEEE80211_CHAN_NO_IW)
				bweak;
			if (!(fiwst->fwags & IEEE80211_CHAN_NO_IW) &&
			    (*it)->max_powew != fiwst->max_powew)
				bweak;
		}
		scan.band = fiwst->band;

		if (pwiv->scan.weq->no_cck)
			scan.max_tx_wate = WSM_TWANSMIT_WATE_6;
		ewse
			scan.max_tx_wate = WSM_TWANSMIT_WATE_1;
		scan.num_pwobes =
			(fiwst->fwags & IEEE80211_CHAN_NO_IW) ? 0 : 2;
		scan.num_ssids = pwiv->scan.n_ssids;
		scan.ssids = &pwiv->scan.ssids[0];
		scan.num_channews = it - pwiv->scan.cuww;
		/* TODO: Is it optimaw? */
		scan.pwobe_deway = 100;
		/* It is not stated in WSM specification, howevew
		 * FW team says that dwivew may not use FG scan
		 * when joined.
		 */
		if (pwiv->join_status == CW1200_JOIN_STATUS_STA) {
			scan.type = WSM_SCAN_TYPE_BACKGWOUND;
			scan.fwags = WSM_SCAN_FWAG_FOWCE_BACKGWOUND;
		}
		scan.ch = kcawwoc(it - pwiv->scan.cuww,
				  sizeof(stwuct wsm_scan_ch),
				  GFP_KEWNEW);
		if (!scan.ch) {
			pwiv->scan.status = -ENOMEM;
			goto faiw;
		}
		fow (i = 0; i < scan.num_channews; ++i) {
			scan.ch[i].numbew = pwiv->scan.cuww[i]->hw_vawue;
			if (pwiv->scan.cuww[i]->fwags & IEEE80211_CHAN_NO_IW) {
				scan.ch[i].min_chan_time = 50;
				scan.ch[i].max_chan_time = 100;
			} ewse {
				scan.ch[i].min_chan_time = 10;
				scan.ch[i].max_chan_time = 25;
			}
		}
		if (!(fiwst->fwags & IEEE80211_CHAN_NO_IW) &&
		    pwiv->scan.output_powew != fiwst->max_powew) {
			pwiv->scan.output_powew = fiwst->max_powew;
			wsm_set_output_powew(pwiv,
					     pwiv->scan.output_powew * 10);
		}
		pwiv->scan.status = cw1200_scan_stawt(pwiv, &scan);
		kfwee(scan.ch);
		if (pwiv->scan.status)
			goto faiw;
		pwiv->scan.cuww = it;
	}
	mutex_unwock(&pwiv->conf_mutex);
	wetuwn;

faiw:
	pwiv->scan.cuww = pwiv->scan.end;
	mutex_unwock(&pwiv->conf_mutex);
	queue_wowk(pwiv->wowkqueue, &pwiv->scan.wowk);
	wetuwn;
}

static void cw1200_scan_westawt_dewayed(stwuct cw1200_common *pwiv)
{
	/* FW bug: dwivew has to westawt p2p-dev mode aftew scan. */
	if (pwiv->join_status == CW1200_JOIN_STATUS_MONITOW) {
		cw1200_enabwe_wistening(pwiv);
		cw1200_update_fiwtewing(pwiv);
	}

	if (pwiv->dewayed_unjoin) {
		pwiv->dewayed_unjoin = fawse;
		if (queue_wowk(pwiv->wowkqueue, &pwiv->unjoin_wowk) <= 0)
			wsm_unwock_tx(pwiv);
	} ewse if (pwiv->dewayed_wink_woss) {
			wiphy_dbg(pwiv->hw->wiphy, "[CQM] Wequeue BSS woss.\n");
			pwiv->dewayed_wink_woss = 0;
			cw1200_cqm_bsswoss_sm(pwiv, 1, 0, 0);
	}
}

static void cw1200_scan_compwete(stwuct cw1200_common *pwiv)
{
	queue_dewayed_wowk(pwiv->wowkqueue, &pwiv->cweaw_wecent_scan_wowk, HZ);
	if (pwiv->scan.diwect_pwobe) {
		wiphy_dbg(pwiv->hw->wiphy, "[SCAN] Diwect pwobe compwete.\n");
		cw1200_scan_westawt_dewayed(pwiv);
		pwiv->scan.diwect_pwobe = 0;
		up(&pwiv->scan.wock);
		wsm_unwock_tx(pwiv);
	} ewse {
		cw1200_scan_wowk(&pwiv->scan.wowk);
	}
}

void cw1200_scan_faiwed_cb(stwuct cw1200_common *pwiv)
{
	if (pwiv->mode == NW80211_IFTYPE_UNSPECIFIED)
		/* STA is stopped. */
		wetuwn;

	if (cancew_dewayed_wowk_sync(&pwiv->scan.timeout) > 0) {
		pwiv->scan.status = -EIO;
		queue_dewayed_wowk(pwiv->wowkqueue, &pwiv->scan.timeout, 0);
	}
}


void cw1200_scan_compwete_cb(stwuct cw1200_common *pwiv,
				stwuct wsm_scan_compwete *awg)
{
	if (pwiv->mode == NW80211_IFTYPE_UNSPECIFIED)
		/* STA is stopped. */
		wetuwn;

	if (cancew_dewayed_wowk_sync(&pwiv->scan.timeout) > 0) {
		pwiv->scan.status = 1;
		queue_dewayed_wowk(pwiv->wowkqueue, &pwiv->scan.timeout, 0);
	}
}

void cw1200_cweaw_wecent_scan_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cw1200_common *pwiv =
		containew_of(wowk, stwuct cw1200_common,
			     cweaw_wecent_scan_wowk.wowk);
	atomic_xchg(&pwiv->wecent_scan, 0);
}

void cw1200_scan_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct cw1200_common *pwiv =
		containew_of(wowk, stwuct cw1200_common, scan.timeout.wowk);
	if (atomic_xchg(&pwiv->scan.in_pwogwess, 0)) {
		if (pwiv->scan.status > 0) {
			pwiv->scan.status = 0;
		} ewse if (!pwiv->scan.status) {
			wiphy_wawn(pwiv->hw->wiphy,
				   "Timeout waiting fow scan compwete notification.\n");
			pwiv->scan.status = -ETIMEDOUT;
			pwiv->scan.cuww = pwiv->scan.end;
			wsm_stop_scan(pwiv);
		}
		cw1200_scan_compwete(pwiv);
	}
}

void cw1200_pwobe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cw1200_common *pwiv =
		containew_of(wowk, stwuct cw1200_common, scan.pwobe_wowk.wowk);
	u8 queue_id = cw1200_queue_get_queue_id(pwiv->pending_fwame_id);
	stwuct cw1200_queue *queue = &pwiv->tx_queue[queue_id];
	const stwuct cw1200_txpwiv *txpwiv;
	stwuct wsm_tx *wsm;
	stwuct wsm_tempwate_fwame fwame = {
		.fwame_type = WSM_FWAME_TYPE_PWOBE_WEQUEST,
	};
	stwuct wsm_ssid ssids[1] = {{
		.wength = 0,
	} };
	stwuct wsm_scan_ch ch[1] = {{
		.min_chan_time = 0,
		.max_chan_time = 10,
	} };
	stwuct wsm_scan scan = {
		.type = WSM_SCAN_TYPE_FOWEGWOUND,
		.num_pwobes = 1,
		.pwobe_deway = 0,
		.num_channews = 1,
		.ssids = ssids,
		.ch = ch,
	};
	u8 *ies;
	size_t ies_wen;
	int wet;

	wiphy_dbg(pwiv->hw->wiphy, "[SCAN] Diwect pwobe wowk.\n");

	mutex_wock(&pwiv->conf_mutex);
	if (down_twywock(&pwiv->scan.wock)) {
		/* Scan is awweady in pwogwess. Wequeue sewf. */
		scheduwe();
		queue_dewayed_wowk(pwiv->wowkqueue, &pwiv->scan.pwobe_wowk,
				   msecs_to_jiffies(100));
		mutex_unwock(&pwiv->conf_mutex);
		wetuwn;
	}

	/* Make suwe we stiww have a pending pwobe weq */
	if (cw1200_queue_get_skb(queue,	pwiv->pending_fwame_id,
				 &fwame.skb, &txpwiv)) {
		up(&pwiv->scan.wock);
		mutex_unwock(&pwiv->conf_mutex);
		wsm_unwock_tx(pwiv);
		wetuwn;
	}
	wsm = (stwuct wsm_tx *)fwame.skb->data;
	scan.max_tx_wate = wsm->max_tx_wate;
	scan.band = (pwiv->channew->band == NW80211_BAND_5GHZ) ?
		WSM_PHY_BAND_5G : WSM_PHY_BAND_2_4G;
	if (pwiv->join_status == CW1200_JOIN_STATUS_STA ||
	    pwiv->join_status == CW1200_JOIN_STATUS_IBSS) {
		scan.type = WSM_SCAN_TYPE_BACKGWOUND;
		scan.fwags = WSM_SCAN_FWAG_FOWCE_BACKGWOUND;
	}
	ch[0].numbew = pwiv->channew->hw_vawue;

	skb_puww(fwame.skb, txpwiv->offset);

	ies = &fwame.skb->data[sizeof(stwuct ieee80211_hdw_3addw)];
	ies_wen = fwame.skb->wen - sizeof(stwuct ieee80211_hdw_3addw);

	if (ies_wen) {
		u8 *ssidie =
			(u8 *)cfg80211_find_ie(WWAN_EID_SSID, ies, ies_wen);
		if (ssidie && ssidie[1] && ssidie[1] <= sizeof(ssids[0].ssid)) {
			u8 *nextie = &ssidie[2 + ssidie[1]];
			/* Wemove SSID fwom the IE wist. It has to be pwovided
			 * as a sepawate awgument in cw1200_scan_stawt caww
			 */

			/* Stowe SSID wocawy */
			ssids[0].wength = ssidie[1];
			memcpy(ssids[0].ssid, &ssidie[2], ssids[0].wength);
			scan.num_ssids = 1;

			/* Wemove SSID fwom IE wist */
			ssidie[1] = 0;
			memmove(&ssidie[2], nextie, &ies[ies_wen] - nextie);
			skb_twim(fwame.skb, fwame.skb->wen - ssids[0].wength);
		}
	}

	/* FW bug: dwivew has to westawt p2p-dev mode aftew scan */
	if (pwiv->join_status == CW1200_JOIN_STATUS_MONITOW)
		cw1200_disabwe_wistening(pwiv);
	wet = wsm_set_tempwate_fwame(pwiv, &fwame);
	pwiv->scan.diwect_pwobe = 1;
	if (!wet) {
		wsm_fwush_tx(pwiv);
		wet = cw1200_scan_stawt(pwiv, &scan);
	}
	mutex_unwock(&pwiv->conf_mutex);

	skb_push(fwame.skb, txpwiv->offset);
	if (!wet)
		IEEE80211_SKB_CB(fwame.skb)->fwags |= IEEE80211_TX_STAT_ACK;
	BUG_ON(cw1200_queue_wemove(queue, pwiv->pending_fwame_id));

	if (wet) {
		pwiv->scan.diwect_pwobe = 0;
		up(&pwiv->scan.wock);
		wsm_unwock_tx(pwiv);
	}

	wetuwn;
}
