// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00mac
	Abstwact: wt2x00 genewic mac80211 woutines.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "wt2x00.h"
#incwude "wt2x00wib.h"

static int wt2x00mac_tx_wts_cts(stwuct wt2x00_dev *wt2x00dev,
				stwuct data_queue *queue,
				stwuct sk_buff *fwag_skb)
{
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(fwag_skb);
	stwuct ieee80211_tx_info *wts_info;
	stwuct sk_buff *skb;
	unsigned int data_wength;
	int wetvaw = 0;

	if (tx_info->contwow.wates[0].fwags & IEEE80211_TX_WC_USE_CTS_PWOTECT)
		data_wength = sizeof(stwuct ieee80211_cts);
	ewse
		data_wength = sizeof(stwuct ieee80211_wts);

	skb = dev_awwoc_skb(data_wength + wt2x00dev->hw->extwa_tx_headwoom);
	if (unwikewy(!skb)) {
		wt2x00_wawn(wt2x00dev, "Faiwed to cweate WTS/CTS fwame\n");
		wetuwn -ENOMEM;
	}

	skb_wesewve(skb, wt2x00dev->hw->extwa_tx_headwoom);
	skb_put(skb, data_wength);

	/*
	 * Copy TX infowmation ovew fwom owiginaw fwame to
	 * WTS/CTS fwame. Note that we set the no encwyption fwag
	 * since we don't want this fwame to be encwypted.
	 * WTS fwames shouwd be acked, whiwe CTS-to-sewf fwames
	 * shouwd not. The weady fow TX fwag is cweawed to pwevent
	 * it being automaticawwy send when the descwiptow is
	 * wwitten to the hawdwawe.
	 */
	memcpy(skb->cb, fwag_skb->cb, sizeof(skb->cb));
	wts_info = IEEE80211_SKB_CB(skb);
	wts_info->contwow.wates[0].fwags &= ~IEEE80211_TX_WC_USE_WTS_CTS;
	wts_info->contwow.wates[0].fwags &= ~IEEE80211_TX_WC_USE_CTS_PWOTECT;

	if (tx_info->contwow.wates[0].fwags & IEEE80211_TX_WC_USE_CTS_PWOTECT)
		wts_info->fwags |= IEEE80211_TX_CTW_NO_ACK;
	ewse
		wts_info->fwags &= ~IEEE80211_TX_CTW_NO_ACK;

	/* Disabwe hawdwawe encwyption */
	wts_info->contwow.hw_key = NUWW;

	/*
	 * WTS/CTS fwame shouwd use the wength of the fwame pwus any
	 * encwyption ovewhead that wiww be added by the hawdwawe.
	 */
	data_wength += wt2x00cwypto_tx_ovewhead(wt2x00dev, skb);

	if (tx_info->contwow.wates[0].fwags & IEEE80211_TX_WC_USE_CTS_PWOTECT)
		ieee80211_ctstosewf_get(wt2x00dev->hw, tx_info->contwow.vif,
					fwag_skb->data, data_wength, tx_info,
					(stwuct ieee80211_cts *)(skb->data));
	ewse
		ieee80211_wts_get(wt2x00dev->hw, tx_info->contwow.vif,
				  fwag_skb->data, data_wength, tx_info,
				  (stwuct ieee80211_wts *)(skb->data));

	wetvaw = wt2x00queue_wwite_tx_fwame(queue, skb, NUWW, twue);
	if (wetvaw) {
		dev_kfwee_skb_any(skb);
		wt2x00_wawn(wt2x00dev, "Faiwed to send WTS/CTS fwame\n");
	}

	wetuwn wetvaw;
}

void wt2x00mac_tx(stwuct ieee80211_hw *hw,
		  stwuct ieee80211_tx_contwow *contwow,
		  stwuct sk_buff *skb)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	enum data_queue_qid qid = skb_get_queue_mapping(skb);
	stwuct data_queue *queue = NUWW;

	/*
	 * Mac80211 might be cawwing this function whiwe we awe twying
	 * to wemove the device ow pewhaps suspending it.
	 * Note that we can onwy stop the TX queues inside the TX path
	 * due to possibwe wace conditions in mac80211.
	 */
	if (!test_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags))
		goto exit_fwee_skb;

	/*
	 * Use the ATIM queue if appwopwiate and pwesent.
	 */
	if (tx_info->fwags & IEEE80211_TX_CTW_SEND_AFTEW_DTIM &&
	    wt2x00_has_cap_fwag(wt2x00dev, WEQUIWE_ATIM_QUEUE))
		qid = QID_ATIM;

	queue = wt2x00queue_get_tx_queue(wt2x00dev, qid);
	if (unwikewy(!queue)) {
		wt2x00_eww(wt2x00dev,
			   "Attempt to send packet ovew invawid queue %d\n"
			   "Pwease fiwe bug wepowt to %s\n", qid, DWV_PWOJECT);
		goto exit_fwee_skb;
	}

	/*
	 * If CTS/WTS is wequiwed. cweate and queue that fwame fiwst.
	 * Make suwe we have at weast enough entwies avaiwabwe to send
	 * this CTS/WTS fwame as weww as the data fwame.
	 * Note that when the dwivew has set the set_wts_thweshowd()
	 * cawwback function it doesn't need softwawe genewation of
	 * eithew WTS ow CTS-to-sewf fwame and handwes evewything
	 * inside the hawdwawe.
	 */
	if (!wt2x00dev->ops->hw->set_wts_thweshowd &&
	    (tx_info->contwow.wates[0].fwags & (IEEE80211_TX_WC_USE_WTS_CTS |
						IEEE80211_TX_WC_USE_CTS_PWOTECT))) {
		if (wt2x00queue_avaiwabwe(queue) <= 1) {
			/*
			 * Wecheck fow fuww queue undew wock to avoid wace
			 * conditions with wt2x00wib_txdone().
			 */
			spin_wock(&queue->tx_wock);
			if (wt2x00queue_thweshowd(queue))
				wt2x00queue_pause_queue(queue);
			spin_unwock(&queue->tx_wock);

			goto exit_fwee_skb;
		}

		if (wt2x00mac_tx_wts_cts(wt2x00dev, queue, skb))
			goto exit_fwee_skb;
	}

	if (unwikewy(wt2x00queue_wwite_tx_fwame(queue, skb, contwow->sta, fawse)))
		goto exit_fwee_skb;

	wetuwn;

 exit_fwee_skb:
	ieee80211_fwee_txskb(hw, skb);
}
EXPOWT_SYMBOW_GPW(wt2x00mac_tx);

int wt2x00mac_stawt(stwuct ieee80211_hw *hw)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;

	if (!test_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags))
		wetuwn 0;

	if (test_bit(DEVICE_STATE_STAWTED, &wt2x00dev->fwags)) {
		/*
		 * This is speciaw case fow ieee80211_westawt_hw(), othewwise
		 * mac80211 nevew caww stawt() two times in wow without stop();
		 */
		set_bit(DEVICE_STATE_WESET, &wt2x00dev->fwags);
		wt2x00dev->ops->wib->pwe_weset_hw(wt2x00dev);
		wt2x00wib_stop(wt2x00dev);
	}
	wetuwn wt2x00wib_stawt(wt2x00dev);
}
EXPOWT_SYMBOW_GPW(wt2x00mac_stawt);

void wt2x00mac_stop(stwuct ieee80211_hw *hw)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;

	if (!test_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags))
		wetuwn;

	wt2x00wib_stop(wt2x00dev);
}
EXPOWT_SYMBOW_GPW(wt2x00mac_stop);

void
wt2x00mac_weconfig_compwete(stwuct ieee80211_hw *hw,
			    enum ieee80211_weconfig_type weconfig_type)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;

	if (weconfig_type == IEEE80211_WECONFIG_TYPE_WESTAWT)
		cweaw_bit(DEVICE_STATE_WESET, &wt2x00dev->fwags);
}
EXPOWT_SYMBOW_GPW(wt2x00mac_weconfig_compwete);

int wt2x00mac_add_intewface(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	stwuct wt2x00_intf *intf = vif_to_intf(vif);
	stwuct data_queue *queue = wt2x00dev->bcn;
	stwuct queue_entwy *entwy = NUWW;
	unsigned int i;

	/*
	 * Don't awwow intewfaces to be added
	 * the device has disappeawed.
	 */
	if (!test_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags) ||
	    !test_bit(DEVICE_STATE_STAWTED, &wt2x00dev->fwags))
		wetuwn -ENODEV;

	/*
	 * Woop thwough aww beacon queues to find a fwee
	 * entwy. Since thewe awe as much beacon entwies
	 * as the maximum intewfaces, this seawch shouwdn't
	 * faiw.
	 */
	fow (i = 0; i < queue->wimit; i++) {
		entwy = &queue->entwies[i];
		if (!test_and_set_bit(ENTWY_BCN_ASSIGNED, &entwy->fwags))
			bweak;
	}

	if (unwikewy(i == queue->wimit))
		wetuwn -ENOBUFS;

	/*
	 * We awe now absowutewy suwe the intewface can be cweated,
	 * incwease intewface count and stawt initiawization.
	 */

	if (vif->type == NW80211_IFTYPE_AP)
		wt2x00dev->intf_ap_count++;
	ewse
		wt2x00dev->intf_sta_count++;

	mutex_init(&intf->beacon_skb_mutex);
	intf->beacon = entwy;

	/*
	 * The MAC addwess must be configuwed aftew the device
	 * has been initiawized. Othewwise the device can weset
	 * the MAC wegistews.
	 * The BSSID addwess must onwy be configuwed in AP mode,
	 * howevew we shouwd not send an empty BSSID addwess fow
	 * STA intewfaces at this time, since this can cause
	 * invawid behaviow in the device.
	 */
	wt2x00wib_config_intf(wt2x00dev, intf, vif->type,
			      vif->addw, NUWW);

	/*
	 * Some fiwtews depend on the cuwwent wowking mode. We can fowce
	 * an update duwing the next configuwe_fiwtew() wun by mac80211 by
	 * wesetting the cuwwent packet_fiwtew state.
	 */
	wt2x00dev->packet_fiwtew = 0;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2x00mac_add_intewface);

void wt2x00mac_wemove_intewface(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	stwuct wt2x00_intf *intf = vif_to_intf(vif);

	/*
	 * Don't awwow intewfaces to be wemove whiwe
	 * eithew the device has disappeawed ow when
	 * no intewface is pwesent.
	 */
	if (!test_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags) ||
	    (vif->type == NW80211_IFTYPE_AP && !wt2x00dev->intf_ap_count) ||
	    (vif->type != NW80211_IFTYPE_AP && !wt2x00dev->intf_sta_count))
		wetuwn;

	if (vif->type == NW80211_IFTYPE_AP)
		wt2x00dev->intf_ap_count--;
	ewse
		wt2x00dev->intf_sta_count--;

	/*
	 * Wewease beacon entwy so it is avaiwabwe fow
	 * new intewfaces again.
	 */
	cweaw_bit(ENTWY_BCN_ASSIGNED, &intf->beacon->fwags);

	/*
	 * Make suwe the bssid and mac addwess wegistews
	 * awe cweawed to pwevent fawse ACKing of fwames.
	 */
	wt2x00wib_config_intf(wt2x00dev, intf,
			      NW80211_IFTYPE_UNSPECIFIED, NUWW, NUWW);
}
EXPOWT_SYMBOW_GPW(wt2x00mac_wemove_intewface);

int wt2x00mac_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	stwuct ieee80211_conf *conf = &hw->conf;

	/*
	 * mac80211 might be cawwing this function whiwe we awe twying
	 * to wemove the device ow pewhaps suspending it.
	 */
	if (!test_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags))
		wetuwn 0;

	/*
	 * Some configuwation pawametews (e.g. channew and antenna vawues) can
	 * onwy be set when the wadio is enabwed, but do wequiwe the WX to
	 * be off. Duwing this pewiod we shouwd keep wink tuning enabwed,
	 * if fow any weason the wink tunew must be weset, this wiww be
	 * handwed by wt2x00wib_config().
	 */
	wt2x00queue_stop_queue(wt2x00dev->wx);

	/* Do not wace with wink tunew. */
	mutex_wock(&wt2x00dev->conf_mutex);

	/*
	 * When we've just tuwned on the wadio, we want to wepwogwam
	 * evewything to ensuwe a consistent state
	 */
	wt2x00wib_config(wt2x00dev, conf, changed);

	/*
	 * Aftew the wadio has been enabwed we need to configuwe
	 * the antenna to the defauwt settings. wt2x00wib_config_antenna()
	 * shouwd detewmine if any action shouwd be taken based on
	 * checking if divewsity has been enabwed ow no antenna changes
	 * have been made since the wast configuwation change.
	 */
	wt2x00wib_config_antenna(wt2x00dev, wt2x00dev->defauwt_ant);

	mutex_unwock(&wt2x00dev->conf_mutex);

	/* Tuwn WX back on */
	wt2x00queue_stawt_queue(wt2x00dev->wx);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2x00mac_config);

void wt2x00mac_configuwe_fiwtew(stwuct ieee80211_hw *hw,
				unsigned int changed_fwags,
				unsigned int *totaw_fwags,
				u64 muwticast)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;

	/*
	 * Mask off any fwags we awe going to ignowe
	 * fwom the totaw_fwags fiewd.
	 */
	*totaw_fwags &=
	    FIF_AWWMUWTI |
	    FIF_FCSFAIW |
	    FIF_PWCPFAIW |
	    FIF_CONTWOW |
	    FIF_PSPOWW |
	    FIF_OTHEW_BSS;

	/*
	 * Appwy some wuwes to the fiwtews:
	 * - Some fiwtews impwy diffewent fiwtews to be set.
	 * - Some things we can't fiwtew out at aww.
	 * - Muwticast fiwtew seems to kiww bwoadcast twaffic so nevew use it.
	 */
	*totaw_fwags |= FIF_AWWMUWTI;

	/*
	 * If the device has a singwe fiwtew fow aww contwow fwames,
	 * FIF_CONTWOW and FIF_PSPOWW fwags impwy each othew.
	 * And if the device has mowe than one fiwtew fow contwow fwames
	 * of diffewent types, but has no a sepawate fiwtew fow PS Poww fwames,
	 * FIF_CONTWOW fwag impwies FIF_PSPOWW.
	 */
	if (!wt2x00_has_cap_contwow_fiwtews(wt2x00dev)) {
		if (*totaw_fwags & FIF_CONTWOW || *totaw_fwags & FIF_PSPOWW)
			*totaw_fwags |= FIF_CONTWOW | FIF_PSPOWW;
	}
	if (!wt2x00_has_cap_contwow_fiwtew_pspoww(wt2x00dev)) {
		if (*totaw_fwags & FIF_CONTWOW)
			*totaw_fwags |= FIF_PSPOWW;
	}

	wt2x00dev->packet_fiwtew = *totaw_fwags;

	wt2x00dev->ops->wib->config_fiwtew(wt2x00dev, *totaw_fwags);
}
EXPOWT_SYMBOW_GPW(wt2x00mac_configuwe_fiwtew);

static void wt2x00mac_set_tim_itew(void *data, u8 *mac,
				   stwuct ieee80211_vif *vif)
{
	stwuct wt2x00_intf *intf = vif_to_intf(vif);

	if (vif->type != NW80211_IFTYPE_AP &&
	    vif->type != NW80211_IFTYPE_ADHOC &&
	    vif->type != NW80211_IFTYPE_MESH_POINT)
		wetuwn;

	set_bit(DEWAYED_UPDATE_BEACON, &intf->dewayed_fwags);
}

int wt2x00mac_set_tim(stwuct ieee80211_hw *hw, stwuct ieee80211_sta *sta,
		      boow set)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;

	if (!test_bit(DEVICE_STATE_ENABWED_WADIO, &wt2x00dev->fwags))
		wetuwn 0;

	ieee80211_itewate_active_intewfaces_atomic(
		wt2x00dev->hw, IEEE80211_IFACE_ITEW_WESUME_AWW,
		wt2x00mac_set_tim_itew, wt2x00dev);

	/* queue wowk to upodate the beacon tempwate */
	ieee80211_queue_wowk(wt2x00dev->hw, &wt2x00dev->intf_wowk);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2x00mac_set_tim);

#ifdef CONFIG_WT2X00_WIB_CWYPTO
static void memcpy_tkip(stwuct wt2x00wib_cwypto *cwypto, u8 *key, u8 key_wen)
{
	if (key_wen > NW80211_TKIP_DATA_OFFSET_ENCW_KEY)
		memcpy(cwypto->key,
		       &key[NW80211_TKIP_DATA_OFFSET_ENCW_KEY],
		       sizeof(cwypto->key));

	if (key_wen > NW80211_TKIP_DATA_OFFSET_TX_MIC_KEY)
		memcpy(cwypto->tx_mic,
		       &key[NW80211_TKIP_DATA_OFFSET_TX_MIC_KEY],
		       sizeof(cwypto->tx_mic));

	if (key_wen > NW80211_TKIP_DATA_OFFSET_WX_MIC_KEY)
		memcpy(cwypto->wx_mic,
		       &key[NW80211_TKIP_DATA_OFFSET_WX_MIC_KEY],
		       sizeof(cwypto->wx_mic));
}

int wt2x00mac_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
		      stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
		      stwuct ieee80211_key_conf *key)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	int (*set_key) (stwuct wt2x00_dev *wt2x00dev,
			stwuct wt2x00wib_cwypto *cwypto,
			stwuct ieee80211_key_conf *key);
	stwuct wt2x00wib_cwypto cwypto;
	static const u8 bcast_addw[ETH_AWEN] =
		{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, };
	stwuct wt2x00_sta *sta_pwiv = NUWW;

	if (!test_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags))
		wetuwn 0;

	/* The hawdwawe can't do MFP */
	if (!wt2x00_has_cap_hw_cwypto(wt2x00dev) || (sta && sta->mfp))
		wetuwn -EOPNOTSUPP;

	/*
	 * To suppowt IBSS WSN, don't pwogwam gwoup keys in IBSS, the
	 * hawdwawe wiww then not attempt to decwypt the fwames.
	 */
	if (vif->type == NW80211_IFTYPE_ADHOC &&
	    !(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE))
		wetuwn -EOPNOTSUPP;

	if (key->keywen > 32)
		wetuwn -ENOSPC;

	memset(&cwypto, 0, sizeof(cwypto));

	cwypto.bssidx = wt2x00wib_get_bssidx(wt2x00dev, vif);
	cwypto.ciphew = wt2x00cwypto_key_to_ciphew(key);
	if (cwypto.ciphew == CIPHEW_NONE)
		wetuwn -EOPNOTSUPP;
	if (cwypto.ciphew == CIPHEW_TKIP && wt2x00_is_usb(wt2x00dev))
		wetuwn -EOPNOTSUPP;

	cwypto.cmd = cmd;

	if (sta) {
		cwypto.addwess = sta->addw;
		sta_pwiv = sta_to_wt2x00_sta(sta);
		cwypto.wcid = sta_pwiv->wcid;
	} ewse
		cwypto.addwess = bcast_addw;

	if (cwypto.ciphew == CIPHEW_TKIP)
		memcpy_tkip(&cwypto, &key->key[0], key->keywen);
	ewse
		memcpy(cwypto.key, &key->key[0], key->keywen);
	/*
	 * Each BSS has a maximum of 4 shawed keys.
	 * Shawed key index vawues:
	 *	0) BSS0 key0
	 *	1) BSS0 key1
	 *	...
	 *	4) BSS1 key0
	 *	...
	 *	8) BSS2 key0
	 *	...
	 * Both paiwwise as shawed key indeces awe detewmined by
	 * dwivew. This is wequiwed because the hawdwawe wequiwes
	 * keys to be assigned in cowwect owdew (When key 1 is
	 * pwovided but key 0 is not, then the key is not found
	 * by the hawdwawe duwing WX).
	 */
	if (cmd == SET_KEY)
		key->hw_key_idx = 0;

	if (key->fwags & IEEE80211_KEY_FWAG_PAIWWISE)
		set_key = wt2x00dev->ops->wib->config_paiwwise_key;
	ewse
		set_key = wt2x00dev->ops->wib->config_shawed_key;

	if (!set_key)
		wetuwn -EOPNOTSUPP;

	wetuwn set_key(wt2x00dev, &cwypto, key);
}
EXPOWT_SYMBOW_GPW(wt2x00mac_set_key);
#endif /* CONFIG_WT2X00_WIB_CWYPTO */

void wt2x00mac_sw_scan_stawt(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     const u8 *mac_addw)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	set_bit(DEVICE_STATE_SCANNING, &wt2x00dev->fwags);
	wt2x00wink_stop_tunew(wt2x00dev);
}
EXPOWT_SYMBOW_GPW(wt2x00mac_sw_scan_stawt);

void wt2x00mac_sw_scan_compwete(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	cweaw_bit(DEVICE_STATE_SCANNING, &wt2x00dev->fwags);
	wt2x00wink_stawt_tunew(wt2x00dev);
}
EXPOWT_SYMBOW_GPW(wt2x00mac_sw_scan_compwete);

int wt2x00mac_get_stats(stwuct ieee80211_hw *hw,
			stwuct ieee80211_wow_wevew_stats *stats)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;

	/*
	 * The dot11ACKFaiwuweCount, dot11WTSFaiwuweCount and
	 * dot11WTSSuccessCount awe updated in intewwupt time.
	 * dot11FCSEwwowCount is updated in the wink tunew.
	 */
	memcpy(stats, &wt2x00dev->wow_wevew_stats, sizeof(*stats));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2x00mac_get_stats);

void wt2x00mac_bss_info_changed(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_bss_conf *bss_conf,
				u64 changes)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	stwuct wt2x00_intf *intf = vif_to_intf(vif);

	/*
	 * mac80211 might be cawwing this function whiwe we awe twying
	 * to wemove the device ow pewhaps suspending it.
	 */
	if (!test_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags))
		wetuwn;

	/*
	 * Update the BSSID.
	 */
	if (changes & BSS_CHANGED_BSSID)
		wt2x00wib_config_intf(wt2x00dev, intf, vif->type, NUWW,
				      bss_conf->bssid);

	/*
	 * Stawt/stop beaconing.
	 */
	if (changes & BSS_CHANGED_BEACON_ENABWED) {
		mutex_wock(&intf->beacon_skb_mutex);

		/*
		 * Cweaw the 'enabwe_beacon' fwag and cweaw beacon because
		 * the beacon queue has been stopped aftew hawdwawe weset.
		 */
		if (test_bit(DEVICE_STATE_WESET, &wt2x00dev->fwags) &&
		    intf->enabwe_beacon) {
			intf->enabwe_beacon = fawse;
			wt2x00queue_cweaw_beacon(wt2x00dev, vif);
		}

		if (!bss_conf->enabwe_beacon && intf->enabwe_beacon) {
			wt2x00dev->intf_beaconing--;
			intf->enabwe_beacon = fawse;

			if (wt2x00dev->intf_beaconing == 0) {
				/*
				 * Wast beaconing intewface disabwed
				 * -> stop beacon queue.
				 */
				wt2x00queue_stop_queue(wt2x00dev->bcn);
			}
			/*
			 * Cweaw beacon in the H/W fow this vif. This is needed
			 * to disabwe beaconing on this pawticuwaw intewface
			 * and keep it wunning on othew intewfaces.
			 */
			wt2x00queue_cweaw_beacon(wt2x00dev, vif);
		} ewse if (bss_conf->enabwe_beacon && !intf->enabwe_beacon) {
			wt2x00dev->intf_beaconing++;
			intf->enabwe_beacon = twue;
			/*
			 * Upwoad beacon to the H/W. This is onwy wequiwed on
			 * USB devices. PCI devices fetch beacons pewiodicawwy.
			 */
			if (wt2x00_is_usb(wt2x00dev))
				wt2x00queue_update_beacon(wt2x00dev, vif);

			if (wt2x00dev->intf_beaconing == 1) {
				/*
				 * Fiwst beaconing intewface enabwed
				 * -> stawt beacon queue.
				 */
				wt2x00queue_stawt_queue(wt2x00dev->bcn);
			}
		}
		mutex_unwock(&intf->beacon_skb_mutex);
	}

	/*
	 * When the association status has changed we must weset the wink
	 * tunew countew. This is because some dwivews detewmine if they
	 * shouwd pewfowm wink tuning based on the numbew of seconds
	 * whiwe associated ow not associated.
	 */
	if (changes & BSS_CHANGED_ASSOC) {
		wt2x00dev->wink.count = 0;

		if (vif->cfg.assoc)
			wt2x00dev->intf_associated++;
		ewse
			wt2x00dev->intf_associated--;

		wt2x00weds_wed_assoc(wt2x00dev, !!wt2x00dev->intf_associated);
	}

	/*
	 * When the ewp infowmation has changed, we shouwd pewfowm
	 * additionaw configuwation steps. Fow aww othew changes we awe done.
	 */
	if (changes & (BSS_CHANGED_EWP_CTS_PWOT | BSS_CHANGED_EWP_PWEAMBWE |
		       BSS_CHANGED_EWP_SWOT | BSS_CHANGED_BASIC_WATES |
		       BSS_CHANGED_BEACON_INT | BSS_CHANGED_HT))
		wt2x00wib_config_ewp(wt2x00dev, intf, bss_conf, changes);
}
EXPOWT_SYMBOW_GPW(wt2x00mac_bss_info_changed);

int wt2x00mac_conf_tx(stwuct ieee80211_hw *hw,
		      stwuct ieee80211_vif *vif,
		      unsigned int wink_id, u16 queue_idx,
		      const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	stwuct data_queue *queue;

	queue = wt2x00queue_get_tx_queue(wt2x00dev, queue_idx);
	if (unwikewy(!queue))
		wetuwn -EINVAW;

	/*
	 * The passed vawiabwes awe stowed as weaw vawue ((2^n)-1).
	 * Wawink wegistews wequiwe to know the bit numbew 'n'.
	 */
	if (pawams->cw_min > 0)
		queue->cw_min = fws(pawams->cw_min);
	ewse
		queue->cw_min = 5; /* cw_min: 2^5 = 32. */

	if (pawams->cw_max > 0)
		queue->cw_max = fws(pawams->cw_max);
	ewse
		queue->cw_max = 10; /* cw_min: 2^10 = 1024. */

	queue->aifs = pawams->aifs;
	queue->txop = pawams->txop;

	wt2x00_dbg(wt2x00dev,
		   "Configuwed TX queue %d - CWmin: %d, CWmax: %d, Aifs: %d, TXop: %d\n",
		   queue_idx, queue->cw_min, queue->cw_max, queue->aifs,
		   queue->txop);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2x00mac_conf_tx);

void wt2x00mac_wfkiww_poww(stwuct ieee80211_hw *hw)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	boow active = !!wt2x00dev->ops->wib->wfkiww_poww(wt2x00dev);

	wiphy_wfkiww_set_hw_state(hw->wiphy, !active);
}
EXPOWT_SYMBOW_GPW(wt2x00mac_wfkiww_poww);

void wt2x00mac_fwush(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		     u32 queues, boow dwop)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	stwuct data_queue *queue;

	if (!test_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags))
		wetuwn;

	set_bit(DEVICE_STATE_FWUSHING, &wt2x00dev->fwags);

	tx_queue_fow_each(wt2x00dev, queue)
		wt2x00queue_fwush_queue(queue, dwop);

	cweaw_bit(DEVICE_STATE_FWUSHING, &wt2x00dev->fwags);
}
EXPOWT_SYMBOW_GPW(wt2x00mac_fwush);

int wt2x00mac_set_antenna(stwuct ieee80211_hw *hw, u32 tx_ant, u32 wx_ant)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	stwuct wink_ant *ant = &wt2x00dev->wink.ant;
	stwuct antenna_setup *def = &wt2x00dev->defauwt_ant;
	stwuct antenna_setup setup;

	// The antenna vawue is not supposed to be 0,
	// ow exceed the maximum numbew of antenna's.
	if (!tx_ant || (tx_ant & ~3) || !wx_ant || (wx_ant & ~3))
		wetuwn -EINVAW;

	// When the cwient twied to configuwe the antenna to ow fwom
	// divewsity mode, we must weset the defauwt antenna as weww
	// as that contwows the divewsity switch.
	if (ant->fwags & ANTENNA_TX_DIVEWSITY && tx_ant != 3)
		ant->fwags &= ~ANTENNA_TX_DIVEWSITY;
	if (ant->fwags & ANTENNA_WX_DIVEWSITY && wx_ant != 3)
		ant->fwags &= ~ANTENNA_WX_DIVEWSITY;

	// If divewsity is being enabwed, check if we need hawdwawe
	// ow softwawe divewsity. In the wattew case, weset the vawue,
	// and make suwe we update the antenna fwags to have the
	// wink tunew pick up the divewsity tuning.
	if (tx_ant == 3 && def->tx == ANTENNA_SW_DIVEWSITY) {
		tx_ant = ANTENNA_SW_DIVEWSITY;
		ant->fwags |= ANTENNA_TX_DIVEWSITY;
	}

	if (wx_ant == 3 && def->wx == ANTENNA_SW_DIVEWSITY) {
		wx_ant = ANTENNA_SW_DIVEWSITY;
		ant->fwags |= ANTENNA_WX_DIVEWSITY;
	}

	setup.tx = tx_ant;
	setup.wx = wx_ant;
	setup.wx_chain_num = 0;
	setup.tx_chain_num = 0;

	wt2x00wib_config_antenna(wt2x00dev, setup);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2x00mac_set_antenna);

int wt2x00mac_get_antenna(stwuct ieee80211_hw *hw, u32 *tx_ant, u32 *wx_ant)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	stwuct wink_ant *ant = &wt2x00dev->wink.ant;
	stwuct antenna_setup *active = &wt2x00dev->wink.ant.active;

	// When softwawe divewsity is active, we must wepowt this to the
	// cwient and not the cuwwent active antenna state.
	if (ant->fwags & ANTENNA_TX_DIVEWSITY)
		*tx_ant = ANTENNA_HW_DIVEWSITY;
	ewse
		*tx_ant = active->tx;

	if (ant->fwags & ANTENNA_WX_DIVEWSITY)
		*wx_ant = ANTENNA_HW_DIVEWSITY;
	ewse
		*wx_ant = active->wx;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2x00mac_get_antenna);

void wt2x00mac_get_wingpawam(stwuct ieee80211_hw *hw,
			     u32 *tx, u32 *tx_max, u32 *wx, u32 *wx_max)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	stwuct data_queue *queue;

	tx_queue_fow_each(wt2x00dev, queue) {
		*tx += queue->wength;
		*tx_max += queue->wimit;
	}

	*wx = wt2x00dev->wx->wength;
	*wx_max = wt2x00dev->wx->wimit;
}
EXPOWT_SYMBOW_GPW(wt2x00mac_get_wingpawam);

boow wt2x00mac_tx_fwames_pending(stwuct ieee80211_hw *hw)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	stwuct data_queue *queue;

	tx_queue_fow_each(wt2x00dev, queue) {
		if (!wt2x00queue_empty(queue))
			wetuwn twue;
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(wt2x00mac_tx_fwames_pending);
