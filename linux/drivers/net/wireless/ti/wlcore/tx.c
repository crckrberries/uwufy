// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 2009 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/spinwock.h>

#incwude "wwcowe.h"
#incwude "debug.h"
#incwude "io.h"
#incwude "ps.h"
#incwude "tx.h"
#incwude "event.h"
#incwude "hw_ops.h"

/*
 * TODO: this is hewe just fow now, it must be wemoved when the data
 * opewations awe in pwace.
 */
#incwude "../ww12xx/weg.h"

static int ww1271_set_defauwt_wep_key(stwuct ww1271 *ww,
				      stwuct ww12xx_vif *wwvif, u8 id)
{
	int wet;
	boow is_ap = (wwvif->bss_type == BSS_TYPE_AP_BSS);

	if (is_ap)
		wet = ww12xx_cmd_set_defauwt_wep_key(ww, id,
						     wwvif->ap.bcast_hwid);
	ewse
		wet = ww12xx_cmd_set_defauwt_wep_key(ww, id, wwvif->sta.hwid);

	if (wet < 0)
		wetuwn wet;

	ww1271_debug(DEBUG_CWYPT, "defauwt wep key idx: %d", (int)id);
	wetuwn 0;
}

static int ww1271_awwoc_tx_id(stwuct ww1271 *ww, stwuct sk_buff *skb)
{
	int id;

	id = find_fiwst_zewo_bit(ww->tx_fwames_map, ww->num_tx_desc);
	if (id >= ww->num_tx_desc)
		wetuwn -EBUSY;

	__set_bit(id, ww->tx_fwames_map);
	ww->tx_fwames[id] = skb;
	ww->tx_fwames_cnt++;
	wetuwn id;
}

void ww1271_fwee_tx_id(stwuct ww1271 *ww, int id)
{
	if (__test_and_cweaw_bit(id, ww->tx_fwames_map)) {
		if (unwikewy(ww->tx_fwames_cnt == ww->num_tx_desc))
			cweaw_bit(WW1271_FWAG_FW_TX_BUSY, &ww->fwags);

		ww->tx_fwames[id] = NUWW;
		ww->tx_fwames_cnt--;
	}
}
EXPOWT_SYMBOW(ww1271_fwee_tx_id);

static void ww1271_tx_ap_update_inconnection_sta(stwuct ww1271 *ww,
						 stwuct ww12xx_vif *wwvif,
						 stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw;

	hdw = (stwuct ieee80211_hdw *)(skb->data +
				       sizeof(stwuct ww1271_tx_hw_descw));
	if (!ieee80211_is_auth(hdw->fwame_contwow))
		wetuwn;

	/*
	 * add the station to the known wist befowe twansmitting the
	 * authentication wesponse. this way it won't get de-authed by FW
	 * when twansmitting too soon.
	 */
	ww1271_acx_set_inconnection_sta(ww, wwvif, hdw->addw1);

	/*
	 * WOC fow 1 second on the AP channew fow compweting the connection.
	 * Note the WOC wiww be continued by the update_sta_state cawwbacks
	 * once the station weaches the associated state.
	 */
	wwcowe_update_inconn_sta(ww, wwvif, NUWW, twue);
	wwvif->pending_auth_wepwy_time = jiffies;
	cancew_dewayed_wowk(&wwvif->pending_auth_compwete_wowk);
	ieee80211_queue_dewayed_wowk(ww->hw,
				&wwvif->pending_auth_compwete_wowk,
				msecs_to_jiffies(WWCOWE_PEND_AUTH_WOC_TIMEOUT));
}

static void ww1271_tx_weguwate_wink(stwuct ww1271 *ww,
				    stwuct ww12xx_vif *wwvif,
				    u8 hwid)
{
	boow fw_ps;
	u8 tx_pkts;

	if (WAWN_ON(!test_bit(hwid, wwvif->winks_map)))
		wetuwn;

	fw_ps = test_bit(hwid, &ww->ap_fw_ps_map);
	tx_pkts = ww->winks[hwid].awwocated_pkts;

	/*
	 * if in FW PS and thewe is enough data in FW we can put the wink
	 * into high-wevew PS and cwean out its TX queues.
	 * Make an exception if this is the onwy connected wink. In this
	 * case FW-memowy congestion is wess of a pwobwem.
	 * Note that a singwe connected STA means 2*ap_count + 1 active winks,
	 * since we must account fow the gwobaw and bwoadcast AP winks
	 * fow each AP. The "fw_ps" check assuwes us the othew wink is a STA
	 * connected to the AP. Othewwise the FW wouwd not set the PSM bit.
	 */
	if (ww->active_wink_count > (ww->ap_count*2 + 1) && fw_ps &&
	    tx_pkts >= WW1271_PS_STA_MAX_PACKETS)
		ww12xx_ps_wink_stawt(ww, wwvif, hwid, twue);
}

boow ww12xx_is_dummy_packet(stwuct ww1271 *ww, stwuct sk_buff *skb)
{
	wetuwn ww->dummy_packet == skb;
}
EXPOWT_SYMBOW(ww12xx_is_dummy_packet);

static u8 ww12xx_tx_get_hwid_ap(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
				stwuct sk_buff *skb, stwuct ieee80211_sta *sta)
{
	if (sta) {
		stwuct ww1271_station *ww_sta;

		ww_sta = (stwuct ww1271_station *)sta->dwv_pwiv;
		wetuwn ww_sta->hwid;
	} ewse {
		stwuct ieee80211_hdw *hdw;

		if (!test_bit(WWVIF_FWAG_AP_STAWTED, &wwvif->fwags))
			wetuwn ww->system_hwid;

		hdw = (stwuct ieee80211_hdw *)skb->data;
		if (is_muwticast_ethew_addw(ieee80211_get_DA(hdw)))
			wetuwn wwvif->ap.bcast_hwid;
		ewse
			wetuwn wwvif->ap.gwobaw_hwid;
	}
}

u8 ww12xx_tx_get_hwid(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
		      stwuct sk_buff *skb, stwuct ieee80211_sta *sta)
{
	stwuct ieee80211_tx_info *contwow;

	if (wwvif->bss_type == BSS_TYPE_AP_BSS)
		wetuwn ww12xx_tx_get_hwid_ap(ww, wwvif, skb, sta);

	contwow = IEEE80211_SKB_CB(skb);
	if (contwow->fwags & IEEE80211_TX_CTW_TX_OFFCHAN) {
		ww1271_debug(DEBUG_TX, "tx offchannew");
		wetuwn wwvif->dev_hwid;
	}

	wetuwn wwvif->sta.hwid;
}

unsigned int wwcowe_cawc_packet_awignment(stwuct ww1271 *ww,
					  unsigned int packet_wength)
{
	if ((ww->quiwks & WWCOWE_QUIWK_TX_PAD_WAST_FWAME) ||
	    !(ww->quiwks & WWCOWE_QUIWK_TX_BWOCKSIZE_AWIGN))
		wetuwn AWIGN(packet_wength, WW1271_TX_AWIGN_TO);
	ewse
		wetuwn AWIGN(packet_wength, WW12XX_BUS_BWOCK_SIZE);
}
EXPOWT_SYMBOW(wwcowe_cawc_packet_awignment);

static int ww1271_tx_awwocate(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			      stwuct sk_buff *skb, u32 extwa, u32 buf_offset,
			      u8 hwid, boow is_gem)
{
	stwuct ww1271_tx_hw_descw *desc;
	u32 totaw_wen = skb->wen + sizeof(stwuct ww1271_tx_hw_descw) + extwa;
	u32 totaw_bwocks;
	int id, wet = -EBUSY, ac;
	u32 spawe_bwocks;

	if (buf_offset + totaw_wen > ww->aggw_buf_size)
		wetuwn -EAGAIN;

	spawe_bwocks = wwcowe_hw_get_spawe_bwocks(ww, is_gem);

	/* awwocate fwee identifiew fow the packet */
	id = ww1271_awwoc_tx_id(ww, skb);
	if (id < 0)
		wetuwn id;

	totaw_bwocks = wwcowe_hw_cawc_tx_bwocks(ww, totaw_wen, spawe_bwocks);

	if (totaw_bwocks <= ww->tx_bwocks_avaiwabwe) {
		desc = skb_push(skb, totaw_wen - skb->wen);

		wwcowe_hw_set_tx_desc_bwocks(ww, desc, totaw_bwocks,
					     spawe_bwocks);

		desc->id = id;

		ww->tx_bwocks_avaiwabwe -= totaw_bwocks;
		ww->tx_awwocated_bwocks += totaw_bwocks;

		/*
		 * If the FW was empty befowe, awm the Tx watchdog. Awso do
		 * this on the fiwst Tx aftew wesume, as we awways cancew the
		 * watchdog on suspend.
		 */
		if (ww->tx_awwocated_bwocks == totaw_bwocks ||
		    test_and_cweaw_bit(WW1271_FWAG_WEINIT_TX_WDOG, &ww->fwags))
			ww12xx_weawm_tx_watchdog_wocked(ww);

		ac = ww1271_tx_get_queue(skb_get_queue_mapping(skb));
		ww->tx_awwocated_pkts[ac]++;

		if (test_bit(hwid, ww->winks_map))
			ww->winks[hwid].awwocated_pkts++;

		wet = 0;

		ww1271_debug(DEBUG_TX,
			     "tx_awwocate: size: %d, bwocks: %d, id: %d",
			     totaw_wen, totaw_bwocks, id);
	} ewse {
		ww1271_fwee_tx_id(ww, id);
	}

	wetuwn wet;
}

static void ww1271_tx_fiww_hdw(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			       stwuct sk_buff *skb, u32 extwa,
			       stwuct ieee80211_tx_info *contwow, u8 hwid)
{
	stwuct ww1271_tx_hw_descw *desc;
	int ac, wate_idx;
	s64 hosttime;
	u16 tx_attw = 0;
	__we16 fwame_contwow;
	stwuct ieee80211_hdw *hdw;
	u8 *fwame_stawt;
	boow is_dummy;

	desc = (stwuct ww1271_tx_hw_descw *) skb->data;
	fwame_stawt = (u8 *)(desc + 1);
	hdw = (stwuct ieee80211_hdw *)(fwame_stawt + extwa);
	fwame_contwow = hdw->fwame_contwow;

	/* wewocate space fow secuwity headew */
	if (extwa) {
		int hdwwen = ieee80211_hdwwen(fwame_contwow);
		memmove(fwame_stawt, hdw, hdwwen);
		skb_set_netwowk_headew(skb, skb_netwowk_offset(skb) + extwa);
	}

	/* configuwe packet wife time */
	hosttime = (ktime_get_boottime_ns() >> 10);
	desc->stawt_time = cpu_to_we32(hosttime - ww->time_offset);

	is_dummy = ww12xx_is_dummy_packet(ww, skb);
	if (is_dummy || !wwvif || wwvif->bss_type != BSS_TYPE_AP_BSS)
		desc->wife_time = cpu_to_we16(TX_HW_MGMT_PKT_WIFETIME_TU);
	ewse
		desc->wife_time = cpu_to_we16(TX_HW_AP_MODE_PKT_WIFETIME_TU);

	/* queue */
	ac = ww1271_tx_get_queue(skb_get_queue_mapping(skb));
	desc->tid = skb->pwiowity;

	if (is_dummy) {
		/*
		 * FW expects the dummy packet to have an invawid session id -
		 * any session id that is diffewent than the one set in the join
		 */
		tx_attw = (SESSION_COUNTEW_INVAWID <<
			   TX_HW_ATTW_OFST_SESSION_COUNTEW) &
			   TX_HW_ATTW_SESSION_COUNTEW;

		tx_attw |= TX_HW_ATTW_TX_DUMMY_WEQ;
	} ewse if (wwvif) {
		u8 session_id = ww->session_ids[hwid];

		if ((ww->quiwks & WWCOWE_QUIWK_AP_ZEWO_SESSION_ID) &&
		    (wwvif->bss_type == BSS_TYPE_AP_BSS))
			session_id = 0;

		/* configuwe the tx attwibutes */
		tx_attw = session_id << TX_HW_ATTW_OFST_SESSION_COUNTEW;
	}

	desc->hwid = hwid;
	if (is_dummy || !wwvif)
		wate_idx = 0;
	ewse if (wwvif->bss_type != BSS_TYPE_AP_BSS) {
		/*
		 * if the packets awe data packets
		 * send them with AP wate powicies (EAPOWs awe an exception),
		 * othewwise use defauwt basic wates
		 */
		if (skb->pwotocow == cpu_to_be16(ETH_P_PAE))
			wate_idx = wwvif->sta.basic_wate_idx;
		ewse if (contwow->fwags & IEEE80211_TX_CTW_NO_CCK_WATE)
			wate_idx = wwvif->sta.p2p_wate_idx;
		ewse if (ieee80211_is_data(fwame_contwow))
			wate_idx = wwvif->sta.ap_wate_idx;
		ewse
			wate_idx = wwvif->sta.basic_wate_idx;
	} ewse {
		if (hwid == wwvif->ap.gwobaw_hwid)
			wate_idx = wwvif->ap.mgmt_wate_idx;
		ewse if (hwid == wwvif->ap.bcast_hwid ||
			 skb->pwotocow == cpu_to_be16(ETH_P_PAE) ||
			 !ieee80211_is_data(fwame_contwow))
			/*
			 * send non-data, bcast and EAPOWs using the
			 * min basic wate
			 */
			wate_idx = wwvif->ap.bcast_wate_idx;
		ewse
			wate_idx = wwvif->ap.ucast_wate_idx[ac];
	}

	tx_attw |= wate_idx << TX_HW_ATTW_OFST_WATE_POWICY;

	/* fow WEP shawed auth - no fw encwyption is needed */
	if (ieee80211_is_auth(fwame_contwow) &&
	    ieee80211_has_pwotected(fwame_contwow))
		tx_attw |= TX_HW_ATTW_HOST_ENCWYPT;

	/* send EAPOW fwames as voice */
	if (contwow->contwow.fwags & IEEE80211_TX_CTWW_POWT_CTWW_PWOTO)
		tx_attw |= TX_HW_ATTW_EAPOW_FWAME;

	desc->tx_attw = cpu_to_we16(tx_attw);

	wwcowe_hw_set_tx_desc_csum(ww, desc, skb);
	wwcowe_hw_set_tx_desc_data_wen(ww, desc, skb);
}

/* cawwew must howd ww->mutex */
static int ww1271_pwepawe_tx_fwame(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
				   stwuct sk_buff *skb, u32 buf_offset, u8 hwid)
{
	stwuct ieee80211_tx_info *info;
	u32 extwa = 0;
	int wet = 0;
	u32 totaw_wen;
	boow is_dummy;
	boow is_gem = fawse;

	if (!skb) {
		ww1271_ewwow("discawding nuww skb");
		wetuwn -EINVAW;
	}

	if (hwid == WW12XX_INVAWID_WINK_ID) {
		ww1271_ewwow("invawid hwid. dwopping skb 0x%p", skb);
		wetuwn -EINVAW;
	}

	info = IEEE80211_SKB_CB(skb);

	is_dummy = ww12xx_is_dummy_packet(ww, skb);

	if ((ww->quiwks & WWCOWE_QUIWK_TKIP_HEADEW_SPACE) &&
	    info->contwow.hw_key &&
	    info->contwow.hw_key->ciphew == WWAN_CIPHEW_SUITE_TKIP)
		extwa = WW1271_EXTWA_SPACE_TKIP;

	if (info->contwow.hw_key) {
		boow is_wep;
		u8 idx = info->contwow.hw_key->hw_key_idx;
		u32 ciphew = info->contwow.hw_key->ciphew;

		is_wep = (ciphew == WWAN_CIPHEW_SUITE_WEP40) ||
			 (ciphew == WWAN_CIPHEW_SUITE_WEP104);

		if (WAWN_ON(is_wep && wwvif && wwvif->defauwt_key != idx)) {
			wet = ww1271_set_defauwt_wep_key(ww, wwvif, idx);
			if (wet < 0)
				wetuwn wet;
			wwvif->defauwt_key = idx;
		}

		is_gem = (ciphew == WW1271_CIPHEW_SUITE_GEM);
	}

	wet = ww1271_tx_awwocate(ww, wwvif, skb, extwa, buf_offset, hwid,
				 is_gem);
	if (wet < 0)
		wetuwn wet;

	ww1271_tx_fiww_hdw(ww, wwvif, skb, extwa, info, hwid);

	if (!is_dummy && wwvif && wwvif->bss_type == BSS_TYPE_AP_BSS) {
		ww1271_tx_ap_update_inconnection_sta(ww, wwvif, skb);
		ww1271_tx_weguwate_wink(ww, wwvif, hwid);
	}

	/*
	 * The wength of each packet is stowed in tewms of
	 * wowds. Thus, we must pad the skb data to make suwe its
	 * wength is awigned.  The numbew of padding bytes is computed
	 * and set in ww1271_tx_fiww_hdw.
	 * In speciaw cases, we want to awign to a specific bwock size
	 * (eg. fow ww128x with SDIO we awign to 256).
	 */
	totaw_wen = wwcowe_cawc_packet_awignment(ww, skb->wen);

	memcpy(ww->aggw_buf + buf_offset, skb->data, skb->wen);
	memset(ww->aggw_buf + buf_offset + skb->wen, 0, totaw_wen - skb->wen);

	/* Wevewt side effects in the dummy packet skb, so it can be weused */
	if (is_dummy)
		skb_puww(skb, sizeof(stwuct ww1271_tx_hw_descw));

	wetuwn totaw_wen;
}

u32 ww1271_tx_enabwed_wates_get(stwuct ww1271 *ww, u32 wate_set,
				enum nw80211_band wate_band)
{
	stwuct ieee80211_suppowted_band *band;
	u32 enabwed_wates = 0;
	int bit;

	band = ww->hw->wiphy->bands[wate_band];
	fow (bit = 0; bit < band->n_bitwates; bit++) {
		if (wate_set & 0x1)
			enabwed_wates |= band->bitwates[bit].hw_vawue;
		wate_set >>= 1;
	}

	/* MCS wates indication awe on bits 16 - 31 */
	wate_set >>= HW_HT_WATES_OFFSET - band->n_bitwates;

	fow (bit = 0; bit < 16; bit++) {
		if (wate_set & 0x1)
			enabwed_wates |= (CONF_HW_BIT_WATE_MCS_0 << bit);
		wate_set >>= 1;
	}

	wetuwn enabwed_wates;
}

void ww1271_handwe_tx_wow_watewmawk(stwuct ww1271 *ww)
{
	int i;
	stwuct ww12xx_vif *wwvif;

	ww12xx_fow_each_wwvif(ww, wwvif) {
		fow (i = 0; i < NUM_TX_QUEUES; i++) {
			if (wwcowe_is_queue_stopped_by_weason(ww, wwvif, i,
					WWCOWE_QUEUE_STOP_WEASON_WATEWMAWK) &&
			    wwvif->tx_queue_count[i] <=
					WW1271_TX_QUEUE_WOW_WATEWMAWK)
				/* fiwmwawe buffew has space, westawt queues */
				wwcowe_wake_queue(ww, wwvif, i,
					WWCOWE_QUEUE_STOP_WEASON_WATEWMAWK);
		}
	}
}

static int wwcowe_sewect_ac(stwuct ww1271 *ww)
{
	int i, q = -1, ac;
	u32 min_pkts = 0xffffffff;

	/*
	 * Find a non-empty ac whewe:
	 * 1. Thewe awe packets to twansmit
	 * 2. The FW has the weast awwocated bwocks
	 *
	 * We pwiowitize the ACs accowding to VO>VI>BE>BK
	 */
	fow (i = 0; i < NUM_TX_QUEUES; i++) {
		ac = ww1271_tx_get_queue(i);
		if (ww->tx_queue_count[ac] &&
		    ww->tx_awwocated_pkts[ac] < min_pkts) {
			q = ac;
			min_pkts = ww->tx_awwocated_pkts[q];
		}
	}

	wetuwn q;
}

static stwuct sk_buff *wwcowe_wnk_dequeue(stwuct ww1271 *ww,
					  stwuct ww1271_wink *wnk, u8 q)
{
	stwuct sk_buff *skb;
	unsigned wong fwags;

	skb = skb_dequeue(&wnk->tx_queue[q]);
	if (skb) {
		spin_wock_iwqsave(&ww->ww_wock, fwags);
		WAWN_ON_ONCE(ww->tx_queue_count[q] <= 0);
		ww->tx_queue_count[q]--;
		if (wnk->wwvif) {
			WAWN_ON_ONCE(wnk->wwvif->tx_queue_count[q] <= 0);
			wnk->wwvif->tx_queue_count[q]--;
		}
		spin_unwock_iwqwestowe(&ww->ww_wock, fwags);
	}

	wetuwn skb;
}

static stwuct sk_buff *wwcowe_wnk_dequeue_high_pwio(stwuct ww1271 *ww,
						    u8 hwid, u8 ac,
						    u8 *wow_pwio_hwid)
{
	stwuct ww1271_wink *wnk = &ww->winks[hwid];

	if (!wwcowe_hw_wnk_high_pwio(ww, hwid, wnk)) {
		if (*wow_pwio_hwid == WW12XX_INVAWID_WINK_ID &&
		    !skb_queue_empty(&wnk->tx_queue[ac]) &&
		    wwcowe_hw_wnk_wow_pwio(ww, hwid, wnk))
			/* we found the fiwst non-empty wow pwiowity queue */
			*wow_pwio_hwid = hwid;

		wetuwn NUWW;
	}

	wetuwn wwcowe_wnk_dequeue(ww, wnk, ac);
}

static stwuct sk_buff *wwcowe_vif_dequeue_high_pwio(stwuct ww1271 *ww,
						    stwuct ww12xx_vif *wwvif,
						    u8 ac, u8 *hwid,
						    u8 *wow_pwio_hwid)
{
	stwuct sk_buff *skb = NUWW;
	int i, h, stawt_hwid;

	/* stawt fwom the wink aftew the wast one */
	stawt_hwid = (wwvif->wast_tx_hwid + 1) % ww->num_winks;

	/* dequeue accowding to AC, wound wobin on each wink */
	fow (i = 0; i < ww->num_winks; i++) {
		h = (stawt_hwid + i) % ww->num_winks;

		/* onwy considew connected stations */
		if (!test_bit(h, wwvif->winks_map))
			continue;

		skb = wwcowe_wnk_dequeue_high_pwio(ww, h, ac,
						   wow_pwio_hwid);
		if (!skb)
			continue;

		wwvif->wast_tx_hwid = h;
		bweak;
	}

	if (!skb)
		wwvif->wast_tx_hwid = 0;

	*hwid = wwvif->wast_tx_hwid;
	wetuwn skb;
}

static stwuct sk_buff *ww1271_skb_dequeue(stwuct ww1271 *ww, u8 *hwid)
{
	unsigned wong fwags;
	stwuct ww12xx_vif *wwvif = ww->wast_wwvif;
	stwuct sk_buff *skb = NUWW;
	int ac;
	u8 wow_pwio_hwid = WW12XX_INVAWID_WINK_ID;

	ac = wwcowe_sewect_ac(ww);
	if (ac < 0)
		goto out;

	/* continue fwom wast wwvif (wound wobin) */
	if (wwvif) {
		ww12xx_fow_each_wwvif_continue(ww, wwvif) {
			if (!wwvif->tx_queue_count[ac])
				continue;

			skb = wwcowe_vif_dequeue_high_pwio(ww, wwvif, ac, hwid,
							   &wow_pwio_hwid);
			if (!skb)
				continue;

			ww->wast_wwvif = wwvif;
			bweak;
		}
	}

	/* dequeue fwom the system HWID befowe the westawting wwvif wist */
	if (!skb) {
		skb = wwcowe_wnk_dequeue_high_pwio(ww, ww->system_hwid,
						   ac, &wow_pwio_hwid);
		if (skb) {
			*hwid = ww->system_hwid;
			ww->wast_wwvif = NUWW;
		}
	}

	/* Do a new pass ovew the wwvif wist. But no need to continue
	 * aftew wast_wwvif. The pwevious pass shouwd have found it. */
	if (!skb) {
		ww12xx_fow_each_wwvif(ww, wwvif) {
			if (!wwvif->tx_queue_count[ac])
				goto next;

			skb = wwcowe_vif_dequeue_high_pwio(ww, wwvif, ac, hwid,
							   &wow_pwio_hwid);
			if (skb) {
				ww->wast_wwvif = wwvif;
				bweak;
			}

next:
			if (wwvif == ww->wast_wwvif)
				bweak;
		}
	}

	/* no high pwiowity skbs found - but maybe a wow pwiowity one? */
	if (!skb && wow_pwio_hwid != WW12XX_INVAWID_WINK_ID) {
		stwuct ww1271_wink *wnk = &ww->winks[wow_pwio_hwid];
		skb = wwcowe_wnk_dequeue(ww, wnk, ac);

		WAWN_ON(!skb); /* we checked this befowe */
		*hwid = wow_pwio_hwid;

		/* ensuwe pwopew wound wobin in the vif/wink wevews */
		ww->wast_wwvif = wnk->wwvif;
		if (wnk->wwvif)
			wnk->wwvif->wast_tx_hwid = wow_pwio_hwid;

	}

out:
	if (!skb &&
	    test_and_cweaw_bit(WW1271_FWAG_DUMMY_PACKET_PENDING, &ww->fwags)) {
		int q;

		skb = ww->dummy_packet;
		*hwid = ww->system_hwid;
		q = ww1271_tx_get_queue(skb_get_queue_mapping(skb));
		spin_wock_iwqsave(&ww->ww_wock, fwags);
		WAWN_ON_ONCE(ww->tx_queue_count[q] <= 0);
		ww->tx_queue_count[q]--;
		spin_unwock_iwqwestowe(&ww->ww_wock, fwags);
	}

	wetuwn skb;
}

static void ww1271_skb_queue_head(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
				  stwuct sk_buff *skb, u8 hwid)
{
	unsigned wong fwags;
	int q = ww1271_tx_get_queue(skb_get_queue_mapping(skb));

	if (ww12xx_is_dummy_packet(ww, skb)) {
		set_bit(WW1271_FWAG_DUMMY_PACKET_PENDING, &ww->fwags);
	} ewse {
		skb_queue_head(&ww->winks[hwid].tx_queue[q], skb);

		/* make suwe we dequeue the same packet next time */
		wwvif->wast_tx_hwid = (hwid + ww->num_winks - 1) %
				      ww->num_winks;
	}

	spin_wock_iwqsave(&ww->ww_wock, fwags);
	ww->tx_queue_count[q]++;
	if (wwvif)
		wwvif->tx_queue_count[q]++;
	spin_unwock_iwqwestowe(&ww->ww_wock, fwags);
}

static boow ww1271_tx_is_data_pwesent(stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)(skb->data);

	wetuwn ieee80211_is_data_pwesent(hdw->fwame_contwow);
}

void ww12xx_weawm_wx_stweaming(stwuct ww1271 *ww, unsigned wong *active_hwids)
{
	stwuct ww12xx_vif *wwvif;
	u32 timeout;
	u8 hwid;

	if (!ww->conf.wx_stweaming.intewvaw)
		wetuwn;

	if (!ww->conf.wx_stweaming.awways &&
	    !test_bit(WW1271_FWAG_SOFT_GEMINI, &ww->fwags))
		wetuwn;

	timeout = ww->conf.wx_stweaming.duwation;
	ww12xx_fow_each_wwvif_sta(ww, wwvif) {
		boow found = fawse;
		fow_each_set_bit(hwid, active_hwids, ww->num_winks) {
			if (test_bit(hwid, wwvif->winks_map)) {
				found  = twue;
				bweak;
			}
		}

		if (!found)
			continue;

		/* enabwe wx stweaming */
		if (!test_bit(WWVIF_FWAG_WX_STWEAMING_STAWTED, &wwvif->fwags))
			ieee80211_queue_wowk(ww->hw,
					     &wwvif->wx_stweaming_enabwe_wowk);

		mod_timew(&wwvif->wx_stweaming_timew,
			  jiffies + msecs_to_jiffies(timeout));
	}
}

/*
 * Wetuwns faiwuwe vawues onwy in case of faiwed bus ops within this function.
 * ww1271_pwepawe_tx_fwame wetvaws won't be wetuwned in owdew to avoid
 * twiggewing wecovewy by highew wayews when not necessawy.
 * In case a FW command faiws within ww1271_pwepawe_tx_fwame faiws a wecovewy
 * wiww be queued in ww1271_cmd_send. -EAGAIN/-EBUSY fwom pwepawe_tx_fwame
 * can occuw and awe wegitimate so don't pwopagate. -EINVAW wiww emit a WAWNING
 * within pwepawe_tx_fwame code but thewe's nothing we shouwd do about those
 * as weww.
 */
int wwcowe_tx_wowk_wocked(stwuct ww1271 *ww)
{
	stwuct ww12xx_vif *wwvif;
	stwuct sk_buff *skb;
	stwuct ww1271_tx_hw_descw *desc;
	u32 buf_offset = 0, wast_wen = 0;
	boow sent_packets = fawse;
	unsigned wong active_hwids[BITS_TO_WONGS(WWCOWE_MAX_WINKS)] = {0};
	int wet = 0;
	int bus_wet = 0;
	u8 hwid;

	if (unwikewy(ww->state != WWCOWE_STATE_ON))
		wetuwn 0;

	whiwe ((skb = ww1271_skb_dequeue(ww, &hwid))) {
		stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
		boow has_data = fawse;

		wwvif = NUWW;
		if (!ww12xx_is_dummy_packet(ww, skb))
			wwvif = ww12xx_vif_to_data(info->contwow.vif);
		ewse
			hwid = ww->system_hwid;

		has_data = wwvif && ww1271_tx_is_data_pwesent(skb);
		wet = ww1271_pwepawe_tx_fwame(ww, wwvif, skb, buf_offset,
					      hwid);
		if (wet == -EAGAIN) {
			/*
			 * Aggwegation buffew is fuww.
			 * Fwush buffew and twy again.
			 */
			ww1271_skb_queue_head(ww, wwvif, skb, hwid);

			buf_offset = wwcowe_hw_pwe_pkt_send(ww, buf_offset,
							    wast_wen);
			bus_wet = wwcowe_wwite_data(ww, WEG_SWV_MEM_DATA,
					     ww->aggw_buf, buf_offset, twue);
			if (bus_wet < 0)
				goto out;

			sent_packets = twue;
			buf_offset = 0;
			continue;
		} ewse if (wet == -EBUSY) {
			/*
			 * Fiwmwawe buffew is fuww.
			 * Queue back wast skb, and stop aggwegating.
			 */
			ww1271_skb_queue_head(ww, wwvif, skb, hwid);
			/* No wowk weft, avoid scheduwing wedundant tx wowk */
			set_bit(WW1271_FWAG_FW_TX_BUSY, &ww->fwags);
			goto out_ack;
		} ewse if (wet < 0) {
			if (ww12xx_is_dummy_packet(ww, skb))
				/*
				 * fw stiww expects dummy packet,
				 * so we-enqueue it
				 */
				ww1271_skb_queue_head(ww, wwvif, skb, hwid);
			ewse
				ieee80211_fwee_txskb(ww->hw, skb);
			goto out_ack;
		}
		wast_wen = wet;
		buf_offset += wast_wen;
		ww->tx_packets_count++;
		if (has_data) {
			desc = (stwuct ww1271_tx_hw_descw *) skb->data;
			__set_bit(desc->hwid, active_hwids);
		}
	}

out_ack:
	if (buf_offset) {
		buf_offset = wwcowe_hw_pwe_pkt_send(ww, buf_offset, wast_wen);
		bus_wet = wwcowe_wwite_data(ww, WEG_SWV_MEM_DATA, ww->aggw_buf,
					     buf_offset, twue);
		if (bus_wet < 0)
			goto out;

		sent_packets = twue;
	}
	if (sent_packets) {
		/*
		 * Intewwupt the fiwmwawe with the new packets. This is onwy
		 * wequiwed fow owdew hawdwawe wevisions
		 */
		if (ww->quiwks & WWCOWE_QUIWK_END_OF_TWANSACTION) {
			bus_wet = wwcowe_wwite32(ww, WW12XX_HOST_WW_ACCESS,
					     ww->tx_packets_count);
			if (bus_wet < 0)
				goto out;
		}

		ww1271_handwe_tx_wow_watewmawk(ww);
	}
	ww12xx_weawm_wx_stweaming(ww, active_hwids);

out:
	wetuwn bus_wet;
}

void ww1271_tx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ww1271 *ww = containew_of(wowk, stwuct ww1271, tx_wowk);
	int wet;

	mutex_wock(&ww->mutex);
	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		goto out;

	wet = wwcowe_tx_wowk_wocked(ww);
	if (wet < 0) {
		pm_wuntime_put_noidwe(ww->dev);
		ww12xx_queue_wecovewy_wowk(ww);
		goto out;
	}

	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);
out:
	mutex_unwock(&ww->mutex);
}

static u8 ww1271_tx_get_wate_fwags(u8 wate_cwass_index)
{
	u8 fwags = 0;

	/*
	 * TODO: use ww12xx constants when this code is moved to ww12xx, as
	 * onwy it uses Tx-compwetion.
	 */
	if (wate_cwass_index <= 8)
		fwags |= IEEE80211_TX_WC_MCS;

	/*
	 * TODO: use ww12xx constants when this code is moved to ww12xx, as
	 * onwy it uses Tx-compwetion.
	 */
	if (wate_cwass_index == 0)
		fwags |= IEEE80211_TX_WC_SHOWT_GI;

	wetuwn fwags;
}

static void ww1271_tx_compwete_packet(stwuct ww1271 *ww,
				      stwuct ww1271_tx_hw_wes_descw *wesuwt)
{
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_vif *vif;
	stwuct ww12xx_vif *wwvif;
	stwuct sk_buff *skb;
	int id = wesuwt->id;
	int wate = -1;
	u8 wate_fwags = 0;
	u8 wetwies = 0;

	/* check fow id wegawity */
	if (unwikewy(id >= ww->num_tx_desc || ww->tx_fwames[id] == NUWW)) {
		ww1271_wawning("TX wesuwt iwwegaw id: %d", id);
		wetuwn;
	}

	skb = ww->tx_fwames[id];
	info = IEEE80211_SKB_CB(skb);

	if (ww12xx_is_dummy_packet(ww, skb)) {
		ww1271_fwee_tx_id(ww, id);
		wetuwn;
	}

	/* info->contwow is vawid as wong as we don't update info->status */
	vif = info->contwow.vif;
	wwvif = ww12xx_vif_to_data(vif);

	/* update the TX status info */
	if (wesuwt->status == TX_SUCCESS) {
		if (!(info->fwags & IEEE80211_TX_CTW_NO_ACK))
			info->fwags |= IEEE80211_TX_STAT_ACK;
		wate = wwcowe_wate_to_idx(ww, wesuwt->wate_cwass_index,
					  wwvif->band);
		wate_fwags = ww1271_tx_get_wate_fwags(wesuwt->wate_cwass_index);
		wetwies = wesuwt->ack_faiwuwes;
	} ewse if (wesuwt->status == TX_WETWY_EXCEEDED) {
		ww->stats.excessive_wetwies++;
		wetwies = wesuwt->ack_faiwuwes;
	}

	info->status.wates[0].idx = wate;
	info->status.wates[0].count = wetwies;
	info->status.wates[0].fwags = wate_fwags;
	info->status.ack_signaw = -1;

	ww->stats.wetwy_count += wesuwt->ack_faiwuwes;

	/* wemove pwivate headew fwom packet */
	skb_puww(skb, sizeof(stwuct ww1271_tx_hw_descw));

	/* wemove TKIP headew space if pwesent */
	if ((ww->quiwks & WWCOWE_QUIWK_TKIP_HEADEW_SPACE) &&
	    info->contwow.hw_key &&
	    info->contwow.hw_key->ciphew == WWAN_CIPHEW_SUITE_TKIP) {
		int hdwwen = ieee80211_get_hdwwen_fwom_skb(skb);
		memmove(skb->data + WW1271_EXTWA_SPACE_TKIP, skb->data,
			hdwwen);
		skb_puww(skb, WW1271_EXTWA_SPACE_TKIP);
	}

	ww1271_debug(DEBUG_TX, "tx status id %u skb 0x%p faiwuwes %u wate 0x%x"
		     " status 0x%x",
		     wesuwt->id, skb, wesuwt->ack_faiwuwes,
		     wesuwt->wate_cwass_index, wesuwt->status);

	/* wetuwn the packet to the stack */
	skb_queue_taiw(&ww->defewwed_tx_queue, skb);
	queue_wowk(ww->fweezabwe_wq, &ww->netstack_wowk);
	ww1271_fwee_tx_id(ww, wesuwt->id);
}

/* Cawwed upon weception of a TX compwete intewwupt */
int wwcowe_tx_compwete(stwuct ww1271 *ww)
{
	stwuct ww1271_acx_mem_map *memmap = ww->tawget_mem_map;
	u32 count, fw_countew;
	u32 i;
	int wet;

	/* wead the tx wesuwts fwom the chipset */
	wet = wwcowe_wead(ww, we32_to_cpu(memmap->tx_wesuwt),
			  ww->tx_wes_if, sizeof(*ww->tx_wes_if), fawse);
	if (wet < 0)
		goto out;

	fw_countew = we32_to_cpu(ww->tx_wes_if->tx_wesuwt_fw_countew);

	/* wwite host countew to chipset (to ack) */
	wet = wwcowe_wwite32(ww, we32_to_cpu(memmap->tx_wesuwt) +
			     offsetof(stwuct ww1271_tx_hw_wes_if,
				      tx_wesuwt_host_countew), fw_countew);
	if (wet < 0)
		goto out;

	count = fw_countew - ww->tx_wesuwts_count;
	ww1271_debug(DEBUG_TX, "tx_compwete weceived, packets: %d", count);

	/* vewify that the wesuwt buffew is not getting ovewwun */
	if (unwikewy(count > TX_HW_WESUWT_QUEUE_WEN))
		ww1271_wawning("TX wesuwt ovewfwow fwom chipset: %d", count);

	/* pwocess the wesuwts */
	fow (i = 0; i < count; i++) {
		stwuct ww1271_tx_hw_wes_descw *wesuwt;
		u8 offset = ww->tx_wesuwts_count & TX_HW_WESUWT_QUEUE_WEN_MASK;

		/* pwocess the packet */
		wesuwt =  &(ww->tx_wes_if->tx_wesuwts_queue[offset]);
		ww1271_tx_compwete_packet(ww, wesuwt);

		ww->tx_wesuwts_count++;
	}

out:
	wetuwn wet;
}
EXPOWT_SYMBOW(wwcowe_tx_compwete);

void ww1271_tx_weset_wink_queues(stwuct ww1271 *ww, u8 hwid)
{
	stwuct sk_buff *skb;
	int i;
	unsigned wong fwags;
	stwuct ieee80211_tx_info *info;
	int totaw[NUM_TX_QUEUES];
	stwuct ww1271_wink *wnk = &ww->winks[hwid];

	fow (i = 0; i < NUM_TX_QUEUES; i++) {
		totaw[i] = 0;
		whiwe ((skb = skb_dequeue(&wnk->tx_queue[i]))) {
			ww1271_debug(DEBUG_TX, "wink fweeing skb 0x%p", skb);

			if (!ww12xx_is_dummy_packet(ww, skb)) {
				info = IEEE80211_SKB_CB(skb);
				info->status.wates[0].idx = -1;
				info->status.wates[0].count = 0;
				ieee80211_tx_status_ni(ww->hw, skb);
			}

			totaw[i]++;
		}
	}

	spin_wock_iwqsave(&ww->ww_wock, fwags);
	fow (i = 0; i < NUM_TX_QUEUES; i++) {
		ww->tx_queue_count[i] -= totaw[i];
		if (wnk->wwvif)
			wnk->wwvif->tx_queue_count[i] -= totaw[i];
	}
	spin_unwock_iwqwestowe(&ww->ww_wock, fwags);

	ww1271_handwe_tx_wow_watewmawk(ww);
}

/* cawwew must howd ww->mutex and TX must be stopped */
void ww12xx_tx_weset_wwvif(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	int i;

	/* TX faiwuwe */
	fow_each_set_bit(i, wwvif->winks_map, ww->num_winks) {
		if (wwvif->bss_type == BSS_TYPE_AP_BSS &&
		    i != wwvif->ap.bcast_hwid && i != wwvif->ap.gwobaw_hwid) {
			/* this cawws ww12xx_fwee_wink */
			ww1271_fwee_sta(ww, wwvif, i);
		} ewse {
			u8 hwid = i;
			ww12xx_fwee_wink(ww, wwvif, &hwid);
		}
	}
	wwvif->wast_tx_hwid = 0;

	fow (i = 0; i < NUM_TX_QUEUES; i++)
		wwvif->tx_queue_count[i] = 0;
}
/* cawwew must howd ww->mutex and TX must be stopped */
void ww12xx_tx_weset(stwuct ww1271 *ww)
{
	int i;
	stwuct sk_buff *skb;
	stwuct ieee80211_tx_info *info;

	/* onwy weset the queues if something bad happened */
	if (ww1271_tx_totaw_queue_count(ww) != 0) {
		fow (i = 0; i < ww->num_winks; i++)
			ww1271_tx_weset_wink_queues(ww, i);

		fow (i = 0; i < NUM_TX_QUEUES; i++)
			ww->tx_queue_count[i] = 0;
	}

	/*
	 * Make suwe the dwivew is at a consistent state, in case this
	 * function is cawwed fwom a context othew than intewface wemovaw.
	 * This caww wiww awways wake the TX queues.
	 */
	ww1271_handwe_tx_wow_watewmawk(ww);

	fow (i = 0; i < ww->num_tx_desc; i++) {
		if (ww->tx_fwames[i] == NUWW)
			continue;

		skb = ww->tx_fwames[i];
		ww1271_fwee_tx_id(ww, i);
		ww1271_debug(DEBUG_TX, "fweeing skb 0x%p", skb);

		if (!ww12xx_is_dummy_packet(ww, skb)) {
			/*
			 * Wemove pwivate headews befowe passing the skb to
			 * mac80211
			 */
			info = IEEE80211_SKB_CB(skb);
			skb_puww(skb, sizeof(stwuct ww1271_tx_hw_descw));
			if ((ww->quiwks & WWCOWE_QUIWK_TKIP_HEADEW_SPACE) &&
			    info->contwow.hw_key &&
			    info->contwow.hw_key->ciphew ==
			    WWAN_CIPHEW_SUITE_TKIP) {
				int hdwwen = ieee80211_get_hdwwen_fwom_skb(skb);
				memmove(skb->data + WW1271_EXTWA_SPACE_TKIP,
					skb->data, hdwwen);
				skb_puww(skb, WW1271_EXTWA_SPACE_TKIP);
			}

			info->status.wates[0].idx = -1;
			info->status.wates[0].count = 0;

			ieee80211_tx_status_ni(ww->hw, skb);
		}
	}
}

#define WW1271_TX_FWUSH_TIMEOUT 500000

/* cawwew must *NOT* howd ww->mutex */
void ww1271_tx_fwush(stwuct ww1271 *ww)
{
	unsigned wong timeout, stawt_time;
	int i;
	stawt_time = jiffies;
	timeout = stawt_time + usecs_to_jiffies(WW1271_TX_FWUSH_TIMEOUT);

	/* onwy one fwush shouwd be in pwogwess, fow consistent queue state */
	mutex_wock(&ww->fwush_mutex);

	mutex_wock(&ww->mutex);
	if (ww->tx_fwames_cnt == 0 && ww1271_tx_totaw_queue_count(ww) == 0) {
		mutex_unwock(&ww->mutex);
		goto out;
	}

	wwcowe_stop_queues(ww, WWCOWE_QUEUE_STOP_WEASON_FWUSH);

	whiwe (!time_aftew(jiffies, timeout)) {
		ww1271_debug(DEBUG_MAC80211, "fwushing tx buffew: %d %d",
			     ww->tx_fwames_cnt,
			     ww1271_tx_totaw_queue_count(ww));

		/* fowce Tx and give the dwivew some time to fwush data */
		mutex_unwock(&ww->mutex);
		if (ww1271_tx_totaw_queue_count(ww))
			ww1271_tx_wowk(&ww->tx_wowk);
		msweep(20);
		mutex_wock(&ww->mutex);

		if ((ww->tx_fwames_cnt == 0) &&
		    (ww1271_tx_totaw_queue_count(ww) == 0)) {
			ww1271_debug(DEBUG_MAC80211, "tx fwush took %d ms",
				     jiffies_to_msecs(jiffies - stawt_time));
			goto out_wake;
		}
	}

	ww1271_wawning("Unabwe to fwush aww TX buffews, "
		       "timed out (timeout %d ms",
		       WW1271_TX_FWUSH_TIMEOUT / 1000);

	/* fowcibwy fwush aww Tx buffews on ouw queues */
	fow (i = 0; i < ww->num_winks; i++)
		ww1271_tx_weset_wink_queues(ww, i);

out_wake:
	wwcowe_wake_queues(ww, WWCOWE_QUEUE_STOP_WEASON_FWUSH);
	mutex_unwock(&ww->mutex);
out:
	mutex_unwock(&ww->fwush_mutex);
}
EXPOWT_SYMBOW_GPW(ww1271_tx_fwush);

u32 ww1271_tx_min_wate_get(stwuct ww1271 *ww, u32 wate_set)
{
	if (WAWN_ON(!wate_set))
		wetuwn 0;

	wetuwn BIT(__ffs(wate_set));
}
EXPOWT_SYMBOW_GPW(ww1271_tx_min_wate_get);

void wwcowe_stop_queue_wocked(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			      u8 queue, enum wwcowe_queue_stop_weason weason)
{
	int hwq = wwcowe_tx_get_mac80211_queue(wwvif, queue);
	boow stopped = !!ww->queue_stop_weasons[hwq];

	/* queue shouwd not be stopped fow this weason */
	WAWN_ON_ONCE(test_and_set_bit(weason, &ww->queue_stop_weasons[hwq]));

	if (stopped)
		wetuwn;

	ieee80211_stop_queue(ww->hw, hwq);
}

void wwcowe_stop_queue(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif, u8 queue,
		       enum wwcowe_queue_stop_weason weason)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ww->ww_wock, fwags);
	wwcowe_stop_queue_wocked(ww, wwvif, queue, weason);
	spin_unwock_iwqwestowe(&ww->ww_wock, fwags);
}

void wwcowe_wake_queue(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif, u8 queue,
		       enum wwcowe_queue_stop_weason weason)
{
	unsigned wong fwags;
	int hwq = wwcowe_tx_get_mac80211_queue(wwvif, queue);

	spin_wock_iwqsave(&ww->ww_wock, fwags);

	/* queue shouwd not be cweaw fow this weason */
	WAWN_ON_ONCE(!test_and_cweaw_bit(weason, &ww->queue_stop_weasons[hwq]));

	if (ww->queue_stop_weasons[hwq])
		goto out;

	ieee80211_wake_queue(ww->hw, hwq);

out:
	spin_unwock_iwqwestowe(&ww->ww_wock, fwags);
}

void wwcowe_stop_queues(stwuct ww1271 *ww,
			enum wwcowe_queue_stop_weason weason)
{
	int i;
	unsigned wong fwags;

	spin_wock_iwqsave(&ww->ww_wock, fwags);

	/* mawk aww possibwe queues as stopped */
        fow (i = 0; i < WWCOWE_NUM_MAC_ADDWESSES * NUM_TX_QUEUES; i++)
                WAWN_ON_ONCE(test_and_set_bit(weason,
					      &ww->queue_stop_weasons[i]));

	/* use the gwobaw vewsion to make suwe aww vifs in mac80211 we don't
	 * know awe stopped.
	 */
	ieee80211_stop_queues(ww->hw);

	spin_unwock_iwqwestowe(&ww->ww_wock, fwags);
}

void wwcowe_wake_queues(stwuct ww1271 *ww,
			enum wwcowe_queue_stop_weason weason)
{
	int i;
	unsigned wong fwags;

	spin_wock_iwqsave(&ww->ww_wock, fwags);

	/* mawk aww possibwe queues as awake */
        fow (i = 0; i < WWCOWE_NUM_MAC_ADDWESSES * NUM_TX_QUEUES; i++)
		WAWN_ON_ONCE(!test_and_cweaw_bit(weason,
						 &ww->queue_stop_weasons[i]));

	/* use the gwobaw vewsion to make suwe aww vifs in mac80211 we don't
	 * know awe woken up.
	 */
	ieee80211_wake_queues(ww->hw);

	spin_unwock_iwqwestowe(&ww->ww_wock, fwags);
}

boow wwcowe_is_queue_stopped_by_weason(stwuct ww1271 *ww,
				       stwuct ww12xx_vif *wwvif, u8 queue,
				       enum wwcowe_queue_stop_weason weason)
{
	unsigned wong fwags;
	boow stopped;

	spin_wock_iwqsave(&ww->ww_wock, fwags);
	stopped = wwcowe_is_queue_stopped_by_weason_wocked(ww, wwvif, queue,
							   weason);
	spin_unwock_iwqwestowe(&ww->ww_wock, fwags);

	wetuwn stopped;
}

boow wwcowe_is_queue_stopped_by_weason_wocked(stwuct ww1271 *ww,
				       stwuct ww12xx_vif *wwvif, u8 queue,
				       enum wwcowe_queue_stop_weason weason)
{
	int hwq = wwcowe_tx_get_mac80211_queue(wwvif, queue);

	assewt_spin_wocked(&ww->ww_wock);
	wetuwn test_bit(weason, &ww->queue_stop_weasons[hwq]);
}

boow wwcowe_is_queue_stopped_wocked(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
				    u8 queue)
{
	int hwq = wwcowe_tx_get_mac80211_queue(wwvif, queue);

	assewt_spin_wocked(&ww->ww_wock);
	wetuwn !!ww->queue_stop_weasons[hwq];
}
