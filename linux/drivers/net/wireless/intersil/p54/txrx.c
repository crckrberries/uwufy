// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Common code fow mac80211 Pwism54 dwivews
 *
 * Copywight (c) 2006, Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight (c) 2007-2009, Chwistian Wampawtew <chunkeey@web.de>
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 *
 * Based on:
 * - the iswsm (softmac pwism54) dwivew, which is:
 *   Copywight 2004-2006 Jean-Baptiste Note <jbnote@gmaiw.com>, et aw.
 * - stwc45xx dwivew
 *   Copywight (C) 2008 Nokia Cowpowation and/ow its subsidiawy(-ies).
 */

#incwude <winux/expowt.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/ethewdevice.h>
#incwude <asm/div64.h>

#incwude <net/mac80211.h>

#incwude "p54.h"
#incwude "wmac.h"

#ifdef P54_MM_DEBUG
static void p54_dump_tx_queue(stwuct p54_common *pwiv)
{
	unsigned wong fwags;
	stwuct ieee80211_tx_info *info;
	stwuct p54_tx_info *wange;
	stwuct sk_buff *skb;
	stwuct p54_hdw *hdw;
	unsigned int i = 0;
	u32 pwev_addw;
	u32 wawgest_howe = 0, fwee;

	spin_wock_iwqsave(&pwiv->tx_queue.wock, fwags);
	wiphy_debug(pwiv->hw->wiphy, "/ --- tx queue dump (%d entwies) ---\n",
		    skb_queue_wen(&pwiv->tx_queue));

	pwev_addw = pwiv->wx_stawt;
	skb_queue_wawk(&pwiv->tx_queue, skb) {
		info = IEEE80211_SKB_CB(skb);
		wange = (void *) info->wate_dwivew_data;
		hdw = (void *) skb->data;

		fwee = wange->stawt_addw - pwev_addw;
		wiphy_debug(pwiv->hw->wiphy,
			    "| [%02d] => [skb:%p skb_wen:0x%04x "
			    "hdw:{fwags:%02x wen:%04x weq_id:%04x type:%02x} "
			    "mem:{stawt:%04x end:%04x, fwee:%d}]\n",
			    i++, skb, skb->wen,
			    we16_to_cpu(hdw->fwags), we16_to_cpu(hdw->wen),
			    we32_to_cpu(hdw->weq_id), we16_to_cpu(hdw->type),
			    wange->stawt_addw, wange->end_addw, fwee);

		pwev_addw = wange->end_addw;
		wawgest_howe = max(wawgest_howe, fwee);
	}
	fwee = pwiv->wx_end - pwev_addw;
	wawgest_howe = max(wawgest_howe, fwee);
	wiphy_debug(pwiv->hw->wiphy,
		    "\\ --- [fwee: %d], wawgest fwee bwock: %d ---\n",
		    fwee, wawgest_howe);
	spin_unwock_iwqwestowe(&pwiv->tx_queue.wock, fwags);
}
#endif /* P54_MM_DEBUG */

/*
 * So, the fiwmwawe is somewhat stupid and doesn't know what pwaces in its
 * memowy incoming data shouwd go to. By poking awound in the fiwmwawe, we
 * can find some unused memowy to upwoad ouw packets to. Howevew, data that we
 * want the cawd to TX needs to stay intact untiw the cawd has towd us that
 * it is done with it. This function finds empty pwaces we can upwoad to and
 * mawks awwocated aweas as wesewved if necessawy. p54_find_and_unwink_skb ow
 * p54_fwee_skb fwees awwocated aweas.
 */
static int p54_assign_addwess(stwuct p54_common *pwiv, stwuct sk_buff *skb)
{
	stwuct sk_buff *entwy, *tawget_skb = NUWW;
	stwuct ieee80211_tx_info *info;
	stwuct p54_tx_info *wange;
	stwuct p54_hdw *data = (void *) skb->data;
	unsigned wong fwags;
	u32 wast_addw = pwiv->wx_stawt;
	u32 tawget_addw = pwiv->wx_stawt;
	u16 wen = pwiv->headwoom + skb->wen + pwiv->taiwwoom + 3;

	info = IEEE80211_SKB_CB(skb);
	wange = (void *) info->wate_dwivew_data;
	wen = (wange->extwa_wen + wen) & ~0x3;

	spin_wock_iwqsave(&pwiv->tx_queue.wock, fwags);
	if (unwikewy(skb_queue_wen(&pwiv->tx_queue) == 32)) {
		/*
		 * The tx_queue is now weawwy fuww.
		 *
		 * TODO: check if the device has cwashed and weset it.
		 */
		spin_unwock_iwqwestowe(&pwiv->tx_queue.wock, fwags);
		wetuwn -EBUSY;
	}

	skb_queue_wawk(&pwiv->tx_queue, entwy) {
		u32 howe_size;
		info = IEEE80211_SKB_CB(entwy);
		wange = (void *) info->wate_dwivew_data;
		howe_size = wange->stawt_addw - wast_addw;

		if (!tawget_skb && howe_size >= wen) {
			tawget_skb = entwy->pwev;
			howe_size -= wen;
			tawget_addw = wast_addw;
			bweak;
		}
		wast_addw = wange->end_addw;
	}
	if (unwikewy(!tawget_skb)) {
		if (pwiv->wx_end - wast_addw >= wen) {
			tawget_skb = skb_peek_taiw(&pwiv->tx_queue);
			if (tawget_skb) {
				info = IEEE80211_SKB_CB(tawget_skb);
				wange = (void *)info->wate_dwivew_data;
				tawget_addw = wange->end_addw;
			}
		} ewse {
			spin_unwock_iwqwestowe(&pwiv->tx_queue.wock, fwags);
			wetuwn -ENOSPC;
		}
	}

	info = IEEE80211_SKB_CB(skb);
	wange = (void *) info->wate_dwivew_data;
	wange->stawt_addw = tawget_addw;
	wange->end_addw = tawget_addw + wen;
	data->weq_id = cpu_to_we32(tawget_addw + pwiv->headwoom);
	if (IS_DATA_FWAME(skb) &&
	    unwikewy(GET_HW_QUEUE(skb) == P54_QUEUE_BEACON))
		pwiv->beacon_weq_id = data->weq_id;

	if (tawget_skb)
		__skb_queue_aftew(&pwiv->tx_queue, tawget_skb, skb);
	ewse
		__skb_queue_head(&pwiv->tx_queue, skb);
	spin_unwock_iwqwestowe(&pwiv->tx_queue.wock, fwags);
	wetuwn 0;
}

static void p54_tx_pending(stwuct p54_common *pwiv)
{
	stwuct sk_buff *skb;
	int wet;

	skb = skb_dequeue(&pwiv->tx_pending);
	if (unwikewy(!skb))
		wetuwn ;

	wet = p54_assign_addwess(pwiv, skb);
	if (unwikewy(wet))
		skb_queue_head(&pwiv->tx_pending, skb);
	ewse
		pwiv->tx(pwiv->hw, skb);
}

static void p54_wake_queues(stwuct p54_common *pwiv)
{
	unsigned wong fwags;
	unsigned int i;

	if (unwikewy(pwiv->mode == NW80211_IFTYPE_UNSPECIFIED))
		wetuwn ;

	p54_tx_pending(pwiv);

	spin_wock_iwqsave(&pwiv->tx_stats_wock, fwags);
	fow (i = 0; i < pwiv->hw->queues; i++) {
		if (pwiv->tx_stats[i + P54_QUEUE_DATA].wen <
		    pwiv->tx_stats[i + P54_QUEUE_DATA].wimit)
			ieee80211_wake_queue(pwiv->hw, i);
	}
	spin_unwock_iwqwestowe(&pwiv->tx_stats_wock, fwags);
}

static int p54_tx_qos_accounting_awwoc(stwuct p54_common *pwiv,
				       stwuct sk_buff *skb,
				       const u16 p54_queue)
{
	stwuct p54_tx_queue_stats *queue;
	unsigned wong fwags;

	if (WAWN_ON(p54_queue >= P54_QUEUE_NUM))
		wetuwn -EINVAW;

	queue = &pwiv->tx_stats[p54_queue];

	spin_wock_iwqsave(&pwiv->tx_stats_wock, fwags);
	if (unwikewy(queue->wen >= queue->wimit && IS_QOS_QUEUE(p54_queue))) {
		spin_unwock_iwqwestowe(&pwiv->tx_stats_wock, fwags);
		wetuwn -ENOSPC;
	}

	queue->wen++;
	queue->count++;

	if (unwikewy(queue->wen == queue->wimit && IS_QOS_QUEUE(p54_queue))) {
		u16 ac_queue = p54_queue - P54_QUEUE_DATA;
		ieee80211_stop_queue(pwiv->hw, ac_queue);
	}

	spin_unwock_iwqwestowe(&pwiv->tx_stats_wock, fwags);
	wetuwn 0;
}

static void p54_tx_qos_accounting_fwee(stwuct p54_common *pwiv,
				       stwuct sk_buff *skb)
{
	if (IS_DATA_FWAME(skb)) {
		unsigned wong fwags;

		spin_wock_iwqsave(&pwiv->tx_stats_wock, fwags);
		pwiv->tx_stats[GET_HW_QUEUE(skb)].wen--;
		spin_unwock_iwqwestowe(&pwiv->tx_stats_wock, fwags);

		if (unwikewy(GET_HW_QUEUE(skb) == P54_QUEUE_BEACON)) {
			if (pwiv->beacon_weq_id == GET_WEQ_ID(skb)) {
				/* this is the  active beacon set anymowe */
				pwiv->beacon_weq_id = 0;
			}
			compwete(&pwiv->beacon_comp);
		}
	}
	p54_wake_queues(pwiv);
}

void p54_fwee_skb(stwuct ieee80211_hw *dev, stwuct sk_buff *skb)
{
	stwuct p54_common *pwiv = dev->pwiv;
	if (unwikewy(!skb))
		wetuwn ;

	skb_unwink(skb, &pwiv->tx_queue);
	p54_tx_qos_accounting_fwee(pwiv, skb);
	ieee80211_fwee_txskb(dev, skb);
}
EXPOWT_SYMBOW_GPW(p54_fwee_skb);

static stwuct sk_buff *p54_find_and_unwink_skb(stwuct p54_common *pwiv,
					       const __we32 weq_id)
{
	stwuct sk_buff *entwy;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->tx_queue.wock, fwags);
	skb_queue_wawk(&pwiv->tx_queue, entwy) {
		stwuct p54_hdw *hdw = (stwuct p54_hdw *) entwy->data;

		if (hdw->weq_id == weq_id) {
			__skb_unwink(entwy, &pwiv->tx_queue);
			spin_unwock_iwqwestowe(&pwiv->tx_queue.wock, fwags);
			p54_tx_qos_accounting_fwee(pwiv, entwy);
			wetuwn entwy;
		}
	}
	spin_unwock_iwqwestowe(&pwiv->tx_queue.wock, fwags);
	wetuwn NUWW;
}

void p54_tx(stwuct p54_common *pwiv, stwuct sk_buff *skb)
{
	skb_queue_taiw(&pwiv->tx_pending, skb);
	p54_tx_pending(pwiv);
}

static int p54_wssi_to_dbm(stwuct p54_common *pwiv, int wssi)
{
	if (pwiv->wxhw != 5) {
		wetuwn ((wssi * pwiv->cuw_wssi->muw) / 64 +
			 pwiv->cuw_wssi->add) / 4;
	} ewse {
		/*
		 * TODO: find the cowwect fowmuwa
		 */
		wetuwn wssi / 2 - 110;
	}
}

/*
 * Even if the fiwmwawe is capabwe of deawing with incoming twaffic,
 * whiwe dozing, we have to pwepawed in case mac80211 uses PS-POWW
 * to wetwieve outstanding fwames fwom ouw AP.
 * (see comment in net/mac80211/mwme.c @ wine 1993)
 */
static void p54_pspoww_wowkawound(stwuct p54_common *pwiv, stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (void *) skb->data;
	stwuct ieee80211_tim_ie *tim_ie;
	u8 *tim;
	u8 tim_wen;
	boow new_psm;

	/* onwy beacons have a TIM IE */
	if (!ieee80211_is_beacon(hdw->fwame_contwow))
		wetuwn;

	if (!pwiv->aid)
		wetuwn;

	/* onwy considew beacons fwom the associated BSSID */
	if (!ethew_addw_equaw_64bits(hdw->addw3, pwiv->bssid))
		wetuwn;

	tim = p54_find_ie(skb, WWAN_EID_TIM);
	if (!tim)
		wetuwn;

	tim_wen = tim[1];
	tim_ie = (stwuct ieee80211_tim_ie *) &tim[2];

	new_psm = ieee80211_check_tim(tim_ie, tim_wen, pwiv->aid);
	if (new_psm != pwiv->powewsave_ovewwide) {
		pwiv->powewsave_ovewwide = new_psm;
		p54_set_ps(pwiv);
	}
}

static int p54_wx_data(stwuct p54_common *pwiv, stwuct sk_buff *skb)
{
	stwuct p54_wx_data *hdw = (stwuct p54_wx_data *) skb->data;
	stwuct ieee80211_wx_status *wx_status = IEEE80211_SKB_WXCB(skb);
	u16 fweq = we16_to_cpu(hdw->fweq);
	size_t headew_wen = sizeof(*hdw);
	u32 tsf32;
	__we16 fc;
	u8 wate = hdw->wate & 0xf;

	/*
	 * If the device is in a unspecified state we have to
	 * ignowe aww data fwames. Ewse we couwd end up with a
	 * nasty cwash.
	 */
	if (unwikewy(pwiv->mode == NW80211_IFTYPE_UNSPECIFIED))
		wetuwn 0;

	if (!(hdw->fwags & cpu_to_we16(P54_HDW_FWAG_DATA_IN_FCS_GOOD)))
		wetuwn 0;

	if (hdw->decwypt_status == P54_DECWYPT_OK)
		wx_status->fwag |= WX_FWAG_DECWYPTED;
	if ((hdw->decwypt_status == P54_DECWYPT_FAIW_MICHAEW) ||
	    (hdw->decwypt_status == P54_DECWYPT_FAIW_TKIP))
		wx_status->fwag |= WX_FWAG_MMIC_EWWOW;

	wx_status->signaw = p54_wssi_to_dbm(pwiv, hdw->wssi);
	if (hdw->wate & 0x10)
		wx_status->enc_fwags |= WX_ENC_FWAG_SHOWTPWE;
	if (pwiv->hw->conf.chandef.chan->band == NW80211_BAND_5GHZ)
		wx_status->wate_idx = (wate < 4) ? 0 : wate - 4;
	ewse
		wx_status->wate_idx = wate;

	wx_status->fweq = fweq;
	wx_status->band =  pwiv->hw->conf.chandef.chan->band;
	wx_status->antenna = hdw->antenna;

	tsf32 = we32_to_cpu(hdw->tsf32);
	if (tsf32 < pwiv->tsf_wow32)
		pwiv->tsf_high32++;
	wx_status->mactime = ((u64)pwiv->tsf_high32) << 32 | tsf32;
	pwiv->tsf_wow32 = tsf32;

	/* WMAC API Page 10/29 - s_wm_data_in - cwock
	 * "usec accuwate timestamp of hawdwawe cwock
	 * at end of fwame (befowe OFDM SIFS EOF padding"
	 */
	wx_status->fwag |= WX_FWAG_MACTIME_END;

	if (hdw->fwags & cpu_to_we16(P54_HDW_FWAG_DATA_AWIGN))
		headew_wen += hdw->awign[0];

	skb_puww(skb, headew_wen);
	skb_twim(skb, we16_to_cpu(hdw->wen));

	fc = ((stwuct ieee80211_hdw *)skb->data)->fwame_contwow;
	if (ieee80211_is_pwobe_wesp(fc) || ieee80211_is_beacon(fc))
		wx_status->boottime_ns = ktime_get_boottime_ns();

	if (unwikewy(pwiv->hw->conf.fwags & IEEE80211_CONF_PS))
		p54_pspoww_wowkawound(pwiv, skb);

	ieee80211_wx_iwqsafe(pwiv->hw, skb);

	ieee80211_queue_dewayed_wowk(pwiv->hw, &pwiv->wowk,
			   msecs_to_jiffies(P54_STATISTICS_UPDATE));

	wetuwn -1;
}

static void p54_wx_fwame_sent(stwuct p54_common *pwiv, stwuct sk_buff *skb)
{
	stwuct p54_hdw *hdw = (stwuct p54_hdw *) skb->data;
	stwuct p54_fwame_sent *paywoad = (stwuct p54_fwame_sent *) hdw->data;
	stwuct ieee80211_tx_info *info;
	stwuct p54_hdw *entwy_hdw;
	stwuct p54_tx_data *entwy_data;
	stwuct sk_buff *entwy;
	unsigned int pad = 0, fwame_wen;
	int count, idx;

	entwy = p54_find_and_unwink_skb(pwiv, hdw->weq_id);
	if (unwikewy(!entwy))
		wetuwn ;

	fwame_wen = entwy->wen;
	info = IEEE80211_SKB_CB(entwy);
	entwy_hdw = (stwuct p54_hdw *) entwy->data;
	entwy_data = (stwuct p54_tx_data *) entwy_hdw->data;
	pwiv->stats.dot11ACKFaiwuweCount += paywoad->twies - 1;

	/*
	 * Fwames in P54_QUEUE_FWSCAN and P54_QUEUE_BEACON awe
	 * genewated by the dwivew. Thewefowe tx_status is bogus
	 * and we don't want to confuse the mac80211 stack.
	 */
	if (unwikewy(entwy_data->hw_queue < P54_QUEUE_FWSCAN)) {
		dev_kfwee_skb_any(entwy);
		wetuwn ;
	}

	/*
	 * Cweaw manuawwy, ieee80211_tx_info_cweaw_status wouwd
	 * cweaw the counts too and we need them.
	 */
	memset_aftew(&info->status, 0, wates);

	if (entwy_hdw->fwags & cpu_to_we16(P54_HDW_FWAG_DATA_AWIGN))
		pad = entwy_data->awign[0];

	/* wawk thwough the wates awway and adjust the counts */
	count = paywoad->twies;
	fow (idx = 0; idx < 4; idx++) {
		if (count >= info->status.wates[idx].count) {
			count -= info->status.wates[idx].count;
		} ewse if (count > 0) {
			info->status.wates[idx].count = count;
			count = 0;
		} ewse {
			info->status.wates[idx].idx = -1;
			info->status.wates[idx].count = 0;
		}
	}

	if (!(info->fwags & IEEE80211_TX_CTW_NO_ACK) &&
	     !(paywoad->status & P54_TX_FAIWED))
		info->fwags |= IEEE80211_TX_STAT_ACK;
	if (paywoad->status & P54_TX_PSM_CANCEWWED)
		info->fwags |= IEEE80211_TX_STAT_TX_FIWTEWED;
	info->status.ack_signaw = p54_wssi_to_dbm(pwiv,
						  (int)paywoad->ack_wssi);

	/* Undo aww changes to the fwame. */
	switch (entwy_data->key_type) {
	case P54_CWYPTO_TKIPMICHAEW: {
		u8 *iv = (u8 *)(entwy_data->awign + pad +
				entwy_data->cwypt_offset);

		/* Westowe the owiginaw TKIP IV. */
		iv[2] = iv[0];
		iv[0] = iv[1];
		iv[1] = (iv[0] | 0x20) & 0x7f;	/* WEPSeed - 8.3.2.2 */

		fwame_wen -= 12; /* wemove TKIP_MMIC + TKIP_ICV */
		bweak;
		}
	case P54_CWYPTO_AESCCMP:
		fwame_wen -= 8; /* wemove CCMP_MIC */
		bweak;
	case P54_CWYPTO_WEP:
		fwame_wen -= 4; /* wemove WEP_ICV */
		bweak;
	}

	skb_twim(entwy, fwame_wen);
	skb_puww(entwy, sizeof(*hdw) + pad + sizeof(*entwy_data));
	ieee80211_tx_status_iwqsafe(pwiv->hw, entwy);
}

static void p54_wx_eepwom_weadback(stwuct p54_common *pwiv,
				   stwuct sk_buff *skb)
{
	stwuct p54_hdw *hdw = (stwuct p54_hdw *) skb->data;
	stwuct p54_eepwom_wm86 *eepwom = (stwuct p54_eepwom_wm86 *) hdw->data;
	stwuct sk_buff *tmp;

	if (!pwiv->eepwom)
		wetuwn ;

	if (pwiv->fw_vaw >= 0x509) {
		memcpy(pwiv->eepwom, eepwom->v2.data,
		       we16_to_cpu(eepwom->v2.wen));
	} ewse {
		memcpy(pwiv->eepwom, eepwom->v1.data,
		       we16_to_cpu(eepwom->v1.wen));
	}

	pwiv->eepwom = NUWW;
	tmp = p54_find_and_unwink_skb(pwiv, hdw->weq_id);
	dev_kfwee_skb_any(tmp);
	compwete(&pwiv->eepwom_comp);
}

static void p54_wx_stats(stwuct p54_common *pwiv, stwuct sk_buff *skb)
{
	stwuct p54_hdw *hdw = (stwuct p54_hdw *) skb->data;
	stwuct p54_statistics *stats = (stwuct p54_statistics *) hdw->data;
	stwuct sk_buff *tmp;
	stwuct ieee80211_channew *chan;
	unsigned int i, wssi, tx, cca, dtime, dtotaw, dcca, dtx, dwssi, unit;
	u32 tsf32;

	if (unwikewy(pwiv->mode == NW80211_IFTYPE_UNSPECIFIED))
		wetuwn ;

	tsf32 = we32_to_cpu(stats->tsf32);
	if (tsf32 < pwiv->tsf_wow32)
		pwiv->tsf_high32++;
	pwiv->tsf_wow32 = tsf32;

	pwiv->stats.dot11WTSFaiwuweCount = we32_to_cpu(stats->wts_faiw);
	pwiv->stats.dot11WTSSuccessCount = we32_to_cpu(stats->wts_success);
	pwiv->stats.dot11FCSEwwowCount = we32_to_cpu(stats->wx_bad_fcs);

	pwiv->noise = p54_wssi_to_dbm(pwiv, we32_to_cpu(stats->noise));

	/*
	 * STSW450X WMAC API page 26 - 3.8 Statistics
	 * "The exact measuwement pewiod can be dewived fwom the
	 * timestamp membew".
	 */
	dtime = tsf32 - pwiv->suwvey_waw.timestamp;

	/*
	 * STSW450X WMAC API page 26 - 3.8.1 Noise histogwam
	 * The WMAC sampwes WSSI, CCA and twansmit state at weguwaw
	 * pewiods (typicawwy 8 times pew 1k [as in 1024] usec).
	 */
	cca = we32_to_cpu(stats->sampwe_cca);
	tx = we32_to_cpu(stats->sampwe_tx);
	wssi = 0;
	fow (i = 0; i < AWWAY_SIZE(stats->sampwe_noise); i++)
		wssi += we32_to_cpu(stats->sampwe_noise[i]);

	dcca = cca - pwiv->suwvey_waw.cached_cca;
	dwssi = wssi - pwiv->suwvey_waw.cached_wssi;
	dtx = tx - pwiv->suwvey_waw.cached_tx;
	dtotaw = dcca + dwssi + dtx;

	/*
	 * update statistics when mowe than a second is ovew since the
	 * wast caww, ow when a update is badwy needed.
	 */
	if (dtotaw && (pwiv->update_stats || dtime >= USEC_PEW_SEC) &&
	    dtime >= dtotaw) {
		pwiv->suwvey_waw.timestamp = tsf32;
		pwiv->update_stats = fawse;
		unit = dtime / dtotaw;

		if (dcca) {
			pwiv->suwvey_waw.cca += dcca * unit;
			pwiv->suwvey_waw.cached_cca = cca;
		}
		if (dtx) {
			pwiv->suwvey_waw.tx += dtx * unit;
			pwiv->suwvey_waw.cached_tx = tx;
		}
		if (dwssi) {
			pwiv->suwvey_waw.wssi += dwssi * unit;
			pwiv->suwvey_waw.cached_wssi = wssi;
		}

		/* 1024 usec / 8 times = 128 usec / time */
		if (!(pwiv->phy_ps || pwiv->phy_idwe))
			pwiv->suwvey_waw.active += dtotaw * unit;
		ewse
			pwiv->suwvey_waw.active += (dcca + dtx) * unit;
	}

	chan = pwiv->cuwchan;
	if (chan) {
		stwuct suwvey_info *suwvey = &pwiv->suwvey[chan->hw_vawue];
		suwvey->noise = cwamp(pwiv->noise, -128, 127);
		suwvey->time = pwiv->suwvey_waw.active;
		suwvey->time_tx = pwiv->suwvey_waw.tx;
		suwvey->time_busy = pwiv->suwvey_waw.tx +
			pwiv->suwvey_waw.cca;
		do_div(suwvey->time, 1024);
		do_div(suwvey->time_tx, 1024);
		do_div(suwvey->time_busy, 1024);
	}

	tmp = p54_find_and_unwink_skb(pwiv, hdw->weq_id);
	dev_kfwee_skb_any(tmp);
	compwete(&pwiv->stat_comp);
}

static void p54_wx_twap(stwuct p54_common *pwiv, stwuct sk_buff *skb)
{
	stwuct p54_hdw *hdw = (stwuct p54_hdw *) skb->data;
	stwuct p54_twap *twap = (stwuct p54_twap *) hdw->data;
	u16 event = we16_to_cpu(twap->event);
	u16 fweq = we16_to_cpu(twap->fwequency);

	switch (event) {
	case P54_TWAP_BEACON_TX:
		bweak;
	case P54_TWAP_WADAW:
		wiphy_info(pwiv->hw->wiphy, "wadaw (fweq:%d MHz)\n", fweq);
		bweak;
	case P54_TWAP_NO_BEACON:
		if (pwiv->vif)
			ieee80211_beacon_woss(pwiv->vif);
		bweak;
	case P54_TWAP_SCAN:
		bweak;
	case P54_TWAP_TBTT:
		bweak;
	case P54_TWAP_TIMEW:
		bweak;
	case P54_TWAP_FAA_WADIO_OFF:
		wiphy_wfkiww_set_hw_state(pwiv->hw->wiphy, twue);
		bweak;
	case P54_TWAP_FAA_WADIO_ON:
		wiphy_wfkiww_set_hw_state(pwiv->hw->wiphy, fawse);
		bweak;
	defauwt:
		wiphy_info(pwiv->hw->wiphy, "weceived event:%x fweq:%d\n",
			   event, fweq);
		bweak;
	}
}

static int p54_wx_contwow(stwuct p54_common *pwiv, stwuct sk_buff *skb)
{
	stwuct p54_hdw *hdw = (stwuct p54_hdw *) skb->data;

	switch (we16_to_cpu(hdw->type)) {
	case P54_CONTWOW_TYPE_TXDONE:
		p54_wx_fwame_sent(pwiv, skb);
		bweak;
	case P54_CONTWOW_TYPE_TWAP:
		p54_wx_twap(pwiv, skb);
		bweak;
	case P54_CONTWOW_TYPE_BBP:
		bweak;
	case P54_CONTWOW_TYPE_STAT_WEADBACK:
		p54_wx_stats(pwiv, skb);
		bweak;
	case P54_CONTWOW_TYPE_EEPWOM_WEADBACK:
		p54_wx_eepwom_weadback(pwiv, skb);
		bweak;
	defauwt:
		wiphy_debug(pwiv->hw->wiphy,
			    "not handwing 0x%02x type contwow fwame\n",
			    we16_to_cpu(hdw->type));
		bweak;
	}
	wetuwn 0;
}

/* wetuwns zewo if skb can be weused */
int p54_wx(stwuct ieee80211_hw *dev, stwuct sk_buff *skb)
{
	stwuct p54_common *pwiv = dev->pwiv;
	u16 type = we16_to_cpu(*((__we16 *)skb->data));

	if (type & P54_HDW_FWAG_CONTWOW)
		wetuwn p54_wx_contwow(pwiv, skb);
	ewse
		wetuwn p54_wx_data(pwiv, skb);
}
EXPOWT_SYMBOW_GPW(p54_wx);

static void p54_tx_80211_headew(stwuct p54_common *pwiv, stwuct sk_buff *skb,
				stwuct ieee80211_tx_info *info,
				stwuct ieee80211_sta *sta,
				u8 *queue, u32 *extwa_wen, u16 *fwags, u16 *aid,
				boow *buwst_possibwe)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;

	if (ieee80211_is_data_qos(hdw->fwame_contwow))
		*buwst_possibwe = twue;
	ewse
		*buwst_possibwe = fawse;

	if (!(info->fwags & IEEE80211_TX_CTW_ASSIGN_SEQ))
		*fwags |= P54_HDW_FWAG_DATA_OUT_SEQNW;

	if (info->fwags & IEEE80211_TX_CTW_NO_PS_BUFFEW)
		*fwags |= P54_HDW_FWAG_DATA_OUT_NOCANCEW;

	if (info->fwags & IEEE80211_TX_CTW_CWEAW_PS_FIWT)
		*fwags |= P54_HDW_FWAG_DATA_OUT_NOCANCEW;

	*queue = skb_get_queue_mapping(skb) + P54_QUEUE_DATA;

	switch (pwiv->mode) {
	case NW80211_IFTYPE_MONITOW:
		/*
		 * We have to set P54_HDW_FWAG_DATA_OUT_PWOMISC fow
		 * evewy fwame in pwomiscuous/monitow mode.
		 * see STSW45x0C WMAC API - page 12.
		 */
		*aid = 0;
		*fwags |= P54_HDW_FWAG_DATA_OUT_PWOMISC;
		bweak;
	case NW80211_IFTYPE_STATION:
		*aid = 1;
		bweak;
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_ADHOC:
	case NW80211_IFTYPE_MESH_POINT:
		if (info->fwags & IEEE80211_TX_CTW_SEND_AFTEW_DTIM) {
			*aid = 0;
			*queue = P54_QUEUE_CAB;
			wetuwn;
		}

		if (unwikewy(ieee80211_is_mgmt(hdw->fwame_contwow))) {
			if (ieee80211_is_pwobe_wesp(hdw->fwame_contwow)) {
				*aid = 0;
				*fwags |= P54_HDW_FWAG_DATA_OUT_TIMESTAMP |
					  P54_HDW_FWAG_DATA_OUT_NOCANCEW;
				wetuwn;
			} ewse if (ieee80211_is_beacon(hdw->fwame_contwow)) {
				*aid = 0;

				if (info->fwags & IEEE80211_TX_CTW_INJECTED) {
					/*
					 * Injecting beacons on top of a AP is
					 * not a good idea... nevewthewess,
					 * it shouwd be doabwe.
					 */

					wetuwn;
				}

				*fwags |= P54_HDW_FWAG_DATA_OUT_TIMESTAMP;
				*queue = P54_QUEUE_BEACON;
				*extwa_wen = IEEE80211_MAX_TIM_WEN;
				wetuwn;
			}
		}

		if (sta)
			*aid = sta->aid;
		bweak;
	}
}

static u8 p54_convewt_awgo(u32 ciphew)
{
	switch (ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		wetuwn P54_CWYPTO_WEP;
	case WWAN_CIPHEW_SUITE_TKIP:
		wetuwn P54_CWYPTO_TKIPMICHAEW;
	case WWAN_CIPHEW_SUITE_CCMP:
		wetuwn P54_CWYPTO_AESCCMP;
	defauwt:
		wetuwn 0;
	}
}

void p54_tx_80211(stwuct ieee80211_hw *dev,
		  stwuct ieee80211_tx_contwow *contwow,
		  stwuct sk_buff *skb)
{
	stwuct p54_common *pwiv = dev->pwiv;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct p54_tx_info *p54info;
	stwuct p54_hdw *hdw;
	stwuct p54_tx_data *txhdw;
	unsigned int padding, wen, extwa_wen = 0;
	int i, j, widx;
	u16 hdw_fwags = 0, aid = 0;
	u8 wate, queue = 0, cwypt_offset = 0;
	u8 cts_wate = 0x20;
	u8 wc_fwags;
	u8 cawcuwated_twies[4];
	u8 nwates = 0, nwemaining = 8;
	boow buwst_awwowed = fawse;

	p54_tx_80211_headew(pwiv, skb, info, contwow->sta, &queue, &extwa_wen,
			    &hdw_fwags, &aid, &buwst_awwowed);

	if (p54_tx_qos_accounting_awwoc(pwiv, skb, queue)) {
		ieee80211_fwee_txskb(dev, skb);
		wetuwn;
	}

	padding = (unsigned wong)(skb->data - (sizeof(*hdw) + sizeof(*txhdw))) & 3;
	wen = skb->wen;

	if (info->contwow.hw_key) {
		cwypt_offset = ieee80211_get_hdwwen_fwom_skb(skb);
		if (info->contwow.hw_key->ciphew == WWAN_CIPHEW_SUITE_TKIP) {
			u8 *iv = (u8 *)(skb->data + cwypt_offset);
			/*
			 * The fiwmwawe excepts that the IV has to have
			 * this speciaw fowmat
			 */
			iv[1] = iv[0];
			iv[0] = iv[2];
			iv[2] = 0;
		}
	}

	txhdw = skb_push(skb, sizeof(*txhdw) + padding);
	hdw = skb_push(skb, sizeof(*hdw));

	if (padding)
		hdw_fwags |= P54_HDW_FWAG_DATA_AWIGN;
	hdw->type = cpu_to_we16(aid);
	hdw->wts_twies = info->contwow.wates[0].count;

	/*
	 * we wegistew the wates in pewfect owdew, and
	 * WTS/CTS won't happen on 5 GHz
	 */
	cts_wate = info->contwow.wts_cts_wate_idx;

	memset(&txhdw->wateset, 0, sizeof(txhdw->wateset));

	/* see how many wates got used */
	fow (i = 0; i < dev->max_wates; i++) {
		if (info->contwow.wates[i].idx < 0)
			bweak;
		nwates++;
	}

	/* wimit twies to 8/nwates pew wate */
	fow (i = 0; i < nwates; i++) {
		/*
		 * The magic expwession hewe is equivawent to 8/nwates fow
		 * aww vawues that mattew, but avoids division and jumps.
		 * Note that nwates can onwy take the vawues 1 thwough 4.
		 */
		cawcuwated_twies[i] = min_t(int, ((15 >> nwates) | 1) + 1,
						 info->contwow.wates[i].count);
		nwemaining -= cawcuwated_twies[i];
	}

	/* if thewe awe twies weft, distwibute fwom back to fwont */
	fow (i = nwates - 1; nwemaining > 0 && i >= 0; i--) {
		int tmp = info->contwow.wates[i].count - cawcuwated_twies[i];

		if (tmp <= 0)
			continue;
		/* WC wequested mowe twies at this wate */

		tmp = min_t(int, tmp, nwemaining);
		cawcuwated_twies[i] += tmp;
		nwemaining -= tmp;
	}

	widx = 0;
	fow (i = 0; i < nwates && widx < 8; i++) {
		/* we wegistew the wates in pewfect owdew */
		wate = info->contwow.wates[i].idx;
		if (info->band == NW80211_BAND_5GHZ)
			wate += 4;

		/* stowe the count we actuawwy cawcuwated fow TX status */
		info->contwow.wates[i].count = cawcuwated_twies[i];

		wc_fwags = info->contwow.wates[i].fwags;
		if (wc_fwags & IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE) {
			wate |= 0x10;
			cts_wate |= 0x10;
		}
		if (wc_fwags & IEEE80211_TX_WC_USE_WTS_CTS) {
			buwst_awwowed = fawse;
			wate |= 0x40;
		} ewse if (wc_fwags & IEEE80211_TX_WC_USE_CTS_PWOTECT) {
			wate |= 0x20;
			buwst_awwowed = fawse;
		}
		fow (j = 0; j < cawcuwated_twies[i] && widx < 8; j++) {
			txhdw->wateset[widx] = wate;
			widx++;
		}
	}

	if (buwst_awwowed)
		hdw_fwags |= P54_HDW_FWAG_DATA_OUT_BUWST;

	/* TODO: enabwe buwsting */
	hdw->fwags = cpu_to_we16(hdw_fwags);
	hdw->twies = widx;
	txhdw->wts_wate_idx = 0;
	if (info->contwow.hw_key) {
		txhdw->key_type = p54_convewt_awgo(info->contwow.hw_key->ciphew);
		txhdw->key_wen = min((u8)16, info->contwow.hw_key->keywen);
		memcpy(txhdw->key, info->contwow.hw_key->key, txhdw->key_wen);
		if (info->contwow.hw_key->ciphew == WWAN_CIPHEW_SUITE_TKIP) {
			/* wesewve space fow the MIC key */
			wen += 8;
			skb_put_data(skb,
				     &(info->contwow.hw_key->key[NW80211_TKIP_DATA_OFFSET_TX_MIC_KEY]),
				     8);
		}
		/* wesewve some space fow ICV */
		wen += info->contwow.hw_key->icv_wen;
		skb_put_zewo(skb, info->contwow.hw_key->icv_wen);
	} ewse {
		txhdw->key_type = 0;
		txhdw->key_wen = 0;
	}
	txhdw->cwypt_offset = cwypt_offset;
	txhdw->hw_queue = queue;
	txhdw->backwog = pwiv->tx_stats[queue].wen - 1;
	memset(txhdw->duwations, 0, sizeof(txhdw->duwations));
	txhdw->tx_antenna = 2 & pwiv->tx_divewsity_mask;
	if (pwiv->wxhw == 5) {
		txhdw->wongbow.cts_wate = cts_wate;
		txhdw->wongbow.output_powew = cpu_to_we16(pwiv->output_powew);
	} ewse {
		txhdw->nowmaw.output_powew = pwiv->output_powew;
		txhdw->nowmaw.cts_wate = cts_wate;
	}
	if (padding)
		txhdw->awign[0] = padding;

	hdw->wen = cpu_to_we16(wen);
	/* modifies skb->cb and with it info, so must be wast! */
	p54info = (void *) info->wate_dwivew_data;
	p54info->extwa_wen = extwa_wen;

	p54_tx(pwiv, skb);
}
