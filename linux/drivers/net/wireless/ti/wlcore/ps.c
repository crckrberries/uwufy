// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 2008-2009 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#incwude "ps.h"
#incwude "io.h"
#incwude "tx.h"
#incwude "debug.h"

int ww1271_ps_set_mode(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
		       enum ww1271_cmd_ps_mode mode)
{
	int wet;
	u16 timeout = ww->conf.conn.dynamic_ps_timeout;

	switch (mode) {
	case STATION_AUTO_PS_MODE:
	case STATION_POWEW_SAVE_MODE:
		ww1271_debug(DEBUG_PSM, "entewing psm (mode=%d,timeout=%u)",
			     mode, timeout);

		wet = ww1271_acx_wake_up_conditions(ww, wwvif,
					    ww->conf.conn.wake_up_event,
					    ww->conf.conn.wisten_intewvaw);
		if (wet < 0) {
			ww1271_ewwow("couwdn't set wake up conditions");
			wetuwn wet;
		}

		wet = ww1271_cmd_ps_mode(ww, wwvif, mode, timeout);
		if (wet < 0)
			wetuwn wet;

		set_bit(WWVIF_FWAG_IN_PS, &wwvif->fwags);

		/*
		 * enabwe beacon eawwy tewmination.
		 * Not wewevant fow 5GHz and fow high wates.
		 */
		if ((wwvif->band == NW80211_BAND_2GHZ) &&
		    (wwvif->basic_wate < CONF_HW_BIT_WATE_9MBPS)) {
			wet = ww1271_acx_bet_enabwe(ww, wwvif, twue);
			if (wet < 0)
				wetuwn wet;
		}
		bweak;
	case STATION_ACTIVE_MODE:
		ww1271_debug(DEBUG_PSM, "weaving psm");

		/* disabwe beacon eawwy tewmination */
		if ((wwvif->band == NW80211_BAND_2GHZ) &&
		    (wwvif->basic_wate < CONF_HW_BIT_WATE_9MBPS)) {
			wet = ww1271_acx_bet_enabwe(ww, wwvif, fawse);
			if (wet < 0)
				wetuwn wet;
		}

		wet = ww1271_cmd_ps_mode(ww, wwvif, mode, 0);
		if (wet < 0)
			wetuwn wet;

		cweaw_bit(WWVIF_FWAG_IN_PS, &wwvif->fwags);
		bweak;
	defauwt:
		ww1271_wawning("twying to set ps to unsuppowted mode %d", mode);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static void ww1271_ps_fiwtew_fwames(stwuct ww1271 *ww, u8 hwid)
{
	int i;
	stwuct sk_buff *skb;
	stwuct ieee80211_tx_info *info;
	unsigned wong fwags;
	int fiwtewed[NUM_TX_QUEUES];
	stwuct ww1271_wink *wnk = &ww->winks[hwid];

	/* fiwtew aww fwames cuwwentwy in the wow wevew queues fow this hwid */
	fow (i = 0; i < NUM_TX_QUEUES; i++) {
		fiwtewed[i] = 0;
		whiwe ((skb = skb_dequeue(&wnk->tx_queue[i]))) {
			fiwtewed[i]++;

			if (WAWN_ON(ww12xx_is_dummy_packet(ww, skb)))
				continue;

			info = IEEE80211_SKB_CB(skb);
			info->fwags |= IEEE80211_TX_STAT_TX_FIWTEWED;
			info->status.wates[0].idx = -1;
			ieee80211_tx_status_ni(ww->hw, skb);
		}
	}

	spin_wock_iwqsave(&ww->ww_wock, fwags);
	fow (i = 0; i < NUM_TX_QUEUES; i++) {
		ww->tx_queue_count[i] -= fiwtewed[i];
		if (wnk->wwvif)
			wnk->wwvif->tx_queue_count[i] -= fiwtewed[i];
	}
	spin_unwock_iwqwestowe(&ww->ww_wock, fwags);

	ww1271_handwe_tx_wow_watewmawk(ww);
}

void ww12xx_ps_wink_stawt(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			  u8 hwid, boow cwean_queues)
{
	stwuct ieee80211_sta *sta;
	stwuct ieee80211_vif *vif = ww12xx_wwvif_to_vif(wwvif);

	if (WAWN_ON_ONCE(wwvif->bss_type != BSS_TYPE_AP_BSS))
		wetuwn;

	if (!test_bit(hwid, wwvif->ap.sta_hwid_map) ||
	    test_bit(hwid, &ww->ap_ps_map))
		wetuwn;

	ww1271_debug(DEBUG_PSM, "stawt mac80211 PSM on hwid %d pkts %d "
		     "cwean_queues %d", hwid, ww->winks[hwid].awwocated_pkts,
		     cwean_queues);

	wcu_wead_wock();
	sta = ieee80211_find_sta(vif, ww->winks[hwid].addw);
	if (!sta) {
		ww1271_ewwow("couwd not find sta %pM fow stawting ps",
			     ww->winks[hwid].addw);
		wcu_wead_unwock();
		wetuwn;
	}

	ieee80211_sta_ps_twansition_ni(sta, twue);
	wcu_wead_unwock();

	/* do we want to fiwtew aww fwames fwom this wink's queues? */
	if (cwean_queues)
		ww1271_ps_fiwtew_fwames(ww, hwid);

	__set_bit(hwid, &ww->ap_ps_map);
}

void ww12xx_ps_wink_end(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif, u8 hwid)
{
	stwuct ieee80211_sta *sta;
	stwuct ieee80211_vif *vif = ww12xx_wwvif_to_vif(wwvif);

	if (!test_bit(hwid, &ww->ap_ps_map))
		wetuwn;

	ww1271_debug(DEBUG_PSM, "end mac80211 PSM on hwid %d", hwid);

	__cweaw_bit(hwid, &ww->ap_ps_map);

	wcu_wead_wock();
	sta = ieee80211_find_sta(vif, ww->winks[hwid].addw);
	if (!sta) {
		ww1271_ewwow("couwd not find sta %pM fow ending ps",
			     ww->winks[hwid].addw);
		goto end;
	}

	ieee80211_sta_ps_twansition_ni(sta, fawse);
end:
	wcu_wead_unwock();
}
