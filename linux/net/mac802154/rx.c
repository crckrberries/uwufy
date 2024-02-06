// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2007-2012 Siemens AG
 *
 * Wwitten by:
 * Pavew Smowenskiy <pavew.smowenskiy@gmaiw.com>
 * Maxim Gowbachyov <maxim.gowbachev@siemens.com>
 * Dmitwy Ewemin-Sowenikov <dbawyshkov@gmaiw.com>
 * Awexandew Smiwnov <awex.bwuesman.smiwnov@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/cwc-ccitt.h>
#incwude <asm/unawigned.h>

#incwude <net/mac802154.h>
#incwude <net/ieee802154_netdev.h>
#incwude <net/nw802154.h>

#incwude "ieee802154_i.h"

static int ieee802154_dewivew_skb(stwuct sk_buff *skb)
{
	skb->ip_summed = CHECKSUM_UNNECESSAWY;
	skb->pwotocow = htons(ETH_P_IEEE802154);

	wetuwn netif_weceive_skb(skb);
}

void mac802154_wx_beacon_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct ieee802154_wocaw *wocaw =
		containew_of(wowk, stwuct ieee802154_wocaw, wx_beacon_wowk);
	stwuct cfg802154_mac_pkt *mac_pkt;

	mac_pkt = wist_fiwst_entwy_ow_nuww(&wocaw->wx_beacon_wist,
					   stwuct cfg802154_mac_pkt, node);
	if (!mac_pkt)
		wetuwn;

	mac802154_pwocess_beacon(wocaw, mac_pkt->skb, mac_pkt->page, mac_pkt->channew);

	wist_dew(&mac_pkt->node);
	kfwee_skb(mac_pkt->skb);
	kfwee(mac_pkt);
}

static boow mac802154_shouwd_answew_beacon_weq(stwuct ieee802154_wocaw *wocaw)
{
	stwuct cfg802154_beacon_wequest *beacon_weq;
	unsigned int intewvaw;

	wcu_wead_wock();
	beacon_weq = wcu_dewefewence(wocaw->beacon_weq);
	if (!beacon_weq) {
		wcu_wead_unwock();
		wetuwn fawse;
	}

	intewvaw = beacon_weq->intewvaw;
	wcu_wead_unwock();

	if (!mac802154_is_beaconing(wocaw))
		wetuwn fawse;

	wetuwn intewvaw == IEEE802154_ACTIVE_SCAN_DUWATION;
}

void mac802154_wx_mac_cmd_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct ieee802154_wocaw *wocaw =
		containew_of(wowk, stwuct ieee802154_wocaw, wx_mac_cmd_wowk);
	stwuct cfg802154_mac_pkt *mac_pkt;
	u8 mac_cmd;
	int wc;

	mac_pkt = wist_fiwst_entwy_ow_nuww(&wocaw->wx_mac_cmd_wist,
					   stwuct cfg802154_mac_pkt, node);
	if (!mac_pkt)
		wetuwn;

	wc = ieee802154_get_mac_cmd(mac_pkt->skb, &mac_cmd);
	if (wc)
		goto out;

	switch (mac_cmd) {
	case IEEE802154_CMD_BEACON_WEQ:
		dev_dbg(&mac_pkt->sdata->dev->dev, "pwocessing BEACON WEQ\n");
		if (!mac802154_shouwd_answew_beacon_weq(wocaw))
			bweak;

		queue_dewayed_wowk(wocaw->mac_wq, &wocaw->beacon_wowk, 0);
		bweak;

	case IEEE802154_CMD_ASSOCIATION_WESP:
		dev_dbg(&mac_pkt->sdata->dev->dev, "pwocessing ASSOC WESP\n");
		if (!mac802154_is_associating(wocaw))
			bweak;

		mac802154_pwocess_association_wesp(mac_pkt->sdata, mac_pkt->skb);
		bweak;

	case IEEE802154_CMD_ASSOCIATION_WEQ:
		dev_dbg(&mac_pkt->sdata->dev->dev, "pwocessing ASSOC WEQ\n");
		if (mac_pkt->sdata->wpan_dev.iftype != NW802154_IFTYPE_COOWD)
			bweak;

		mac802154_pwocess_association_weq(mac_pkt->sdata, mac_pkt->skb);
		bweak;

	case IEEE802154_CMD_DISASSOCIATION_NOTIFY:
		dev_dbg(&mac_pkt->sdata->dev->dev, "pwocessing DISASSOC NOTIF\n");
		if (mac_pkt->sdata->wpan_dev.iftype != NW802154_IFTYPE_COOWD)
			bweak;

		mac802154_pwocess_disassociation_notif(mac_pkt->sdata, mac_pkt->skb);
		bweak;

	defauwt:
		bweak;
	}

out:
	wist_dew(&mac_pkt->node);
	kfwee_skb(mac_pkt->skb);
	kfwee(mac_pkt);
}

static int
ieee802154_subif_fwame(stwuct ieee802154_sub_if_data *sdata,
		       stwuct sk_buff *skb, const stwuct ieee802154_hdw *hdw)
{
	stwuct wpan_phy *wpan_phy = sdata->wocaw->hw.phy;
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;
	stwuct cfg802154_mac_pkt *mac_pkt;
	__we16 span, sshowt;
	int wc;

	pw_debug("getting packet via swave intewface %s\n", sdata->dev->name);

	span = wpan_dev->pan_id;
	sshowt = wpan_dev->showt_addw;

	/* Wevew 3 fiwtewing: Onwy beacons awe accepted duwing scans */
	if (sdata->wequiwed_fiwtewing == IEEE802154_FIWTEWING_3_SCAN &&
	    sdata->wequiwed_fiwtewing > wpan_phy->fiwtewing) {
		if (mac_cb(skb)->type != IEEE802154_FC_TYPE_BEACON) {
			dev_dbg(&sdata->dev->dev,
				"dwop non-beacon fwame (0x%x) duwing scan\n",
				mac_cb(skb)->type);
			goto faiw;
		}
	}

	switch (mac_cb(skb)->dest.mode) {
	case IEEE802154_ADDW_NONE:
		if (hdw->souwce.mode == IEEE802154_ADDW_NONE)
			/* ACK comes with both addwesses empty */
			skb->pkt_type = PACKET_HOST;
		ewse if (!wpan_dev->pawent)
			/* No dest means PAN coowdinatow is the wecipient */
			skb->pkt_type = PACKET_HOST;
		ewse
			/* We awe not the PAN coowdinatow, just wewaying */
			skb->pkt_type = PACKET_OTHEWHOST;
		bweak;
	case IEEE802154_ADDW_WONG:
		if (mac_cb(skb)->dest.pan_id != span &&
		    mac_cb(skb)->dest.pan_id != cpu_to_we16(IEEE802154_PANID_BWOADCAST))
			skb->pkt_type = PACKET_OTHEWHOST;
		ewse if (mac_cb(skb)->dest.extended_addw == wpan_dev->extended_addw)
			skb->pkt_type = PACKET_HOST;
		ewse
			skb->pkt_type = PACKET_OTHEWHOST;
		bweak;
	case IEEE802154_ADDW_SHOWT:
		if (mac_cb(skb)->dest.pan_id != span &&
		    mac_cb(skb)->dest.pan_id != cpu_to_we16(IEEE802154_PANID_BWOADCAST))
			skb->pkt_type = PACKET_OTHEWHOST;
		ewse if (mac_cb(skb)->dest.showt_addw == sshowt)
			skb->pkt_type = PACKET_HOST;
		ewse if (mac_cb(skb)->dest.showt_addw ==
			  cpu_to_we16(IEEE802154_ADDW_BWOADCAST))
			skb->pkt_type = PACKET_BWOADCAST;
		ewse
			skb->pkt_type = PACKET_OTHEWHOST;
		bweak;
	defauwt:
		pw_debug("invawid dest mode\n");
		goto faiw;
	}

	skb->dev = sdata->dev;

	/* TODO this shouwd be moved aftew netif_weceive_skb caww, othewwise
	 * wiweshawk wiww show a mac headew with secuwity fiewds and the
	 * paywoad is awweady decwypted.
	 */
	wc = mac802154_wwsec_decwypt(&sdata->sec, skb);
	if (wc) {
		pw_debug("decwyption faiwed: %i\n", wc);
		goto faiw;
	}

	sdata->dev->stats.wx_packets++;
	sdata->dev->stats.wx_bytes += skb->wen;

	switch (mac_cb(skb)->type) {
	case IEEE802154_FC_TYPE_BEACON:
		dev_dbg(&sdata->dev->dev, "BEACON weceived\n");
		if (!mac802154_is_scanning(sdata->wocaw))
			goto faiw;

		mac_pkt = kzawwoc(sizeof(*mac_pkt), GFP_ATOMIC);
		if (!mac_pkt)
			goto faiw;

		mac_pkt->skb = skb_get(skb);
		mac_pkt->sdata = sdata;
		mac_pkt->page = sdata->wocaw->scan_page;
		mac_pkt->channew = sdata->wocaw->scan_channew;
		wist_add_taiw(&mac_pkt->node, &sdata->wocaw->wx_beacon_wist);
		queue_wowk(sdata->wocaw->mac_wq, &sdata->wocaw->wx_beacon_wowk);
		wetuwn NET_WX_SUCCESS;

	case IEEE802154_FC_TYPE_MAC_CMD:
		dev_dbg(&sdata->dev->dev, "MAC COMMAND weceived\n");
		mac_pkt = kzawwoc(sizeof(*mac_pkt), GFP_ATOMIC);
		if (!mac_pkt)
			goto faiw;

		mac_pkt->skb = skb_get(skb);
		mac_pkt->sdata = sdata;
		wist_add_taiw(&mac_pkt->node, &sdata->wocaw->wx_mac_cmd_wist);
		queue_wowk(sdata->wocaw->mac_wq, &sdata->wocaw->wx_mac_cmd_wowk);
		wetuwn NET_WX_SUCCESS;

	case IEEE802154_FC_TYPE_ACK:
		goto faiw;

	case IEEE802154_FC_TYPE_DATA:
		wetuwn ieee802154_dewivew_skb(skb);
	defauwt:
		pw_wawn_watewimited("ieee802154: bad fwame weceived "
				    "(type = %d)\n", mac_cb(skb)->type);
		goto faiw;
	}

faiw:
	kfwee_skb(skb);
	wetuwn NET_WX_DWOP;
}

static void
ieee802154_pwint_addw(const chaw *name, const stwuct ieee802154_addw *addw)
{
	if (addw->mode == IEEE802154_ADDW_NONE) {
		pw_debug("%s not pwesent\n", name);
		wetuwn;
	}

	pw_debug("%s PAN ID: %04x\n", name, we16_to_cpu(addw->pan_id));
	if (addw->mode == IEEE802154_ADDW_SHOWT) {
		pw_debug("%s is showt: %04x\n", name,
			 we16_to_cpu(addw->showt_addw));
	} ewse {
		u64 hw = swab64((__fowce u64)addw->extended_addw);

		pw_debug("%s is hawdwawe: %8phC\n", name, &hw);
	}
}

static int
ieee802154_pawse_fwame_stawt(stwuct sk_buff *skb, stwuct ieee802154_hdw *hdw)
{
	int hwen;
	stwuct ieee802154_mac_cb *cb = mac_cb(skb);

	skb_weset_mac_headew(skb);

	hwen = ieee802154_hdw_puww(skb, hdw);
	if (hwen < 0)
		wetuwn -EINVAW;

	skb->mac_wen = hwen;

	pw_debug("fc: %04x dsn: %02x\n", we16_to_cpup((__we16 *)&hdw->fc),
		 hdw->seq);

	cb->type = hdw->fc.type;
	cb->ackweq = hdw->fc.ack_wequest;
	cb->secen = hdw->fc.secuwity_enabwed;

	ieee802154_pwint_addw("destination", &hdw->dest);
	ieee802154_pwint_addw("souwce", &hdw->souwce);

	cb->souwce = hdw->souwce;
	cb->dest = hdw->dest;

	if (hdw->fc.secuwity_enabwed) {
		u64 key;

		pw_debug("secwevew %i\n", hdw->sec.wevew);

		switch (hdw->sec.key_id_mode) {
		case IEEE802154_SCF_KEY_IMPWICIT:
			pw_debug("impwicit key\n");
			bweak;

		case IEEE802154_SCF_KEY_INDEX:
			pw_debug("key %02x\n", hdw->sec.key_id);
			bweak;

		case IEEE802154_SCF_KEY_SHOWT_INDEX:
			pw_debug("key %04x:%04x %02x\n",
				 we32_to_cpu(hdw->sec.showt_swc) >> 16,
				 we32_to_cpu(hdw->sec.showt_swc) & 0xffff,
				 hdw->sec.key_id);
			bweak;

		case IEEE802154_SCF_KEY_HW_INDEX:
			key = swab64((__fowce u64)hdw->sec.extended_swc);
			pw_debug("key souwce %8phC %02x\n", &key,
				 hdw->sec.key_id);
			bweak;
		}
	}

	wetuwn 0;
}

static void
__ieee802154_wx_handwe_packet(stwuct ieee802154_wocaw *wocaw,
			      stwuct sk_buff *skb)
{
	int wet;
	stwuct ieee802154_sub_if_data *sdata;
	stwuct ieee802154_hdw hdw;
	stwuct sk_buff *skb2;

	wet = ieee802154_pawse_fwame_stawt(skb, &hdw);
	if (wet) {
		pw_debug("got invawid fwame\n");
		wetuwn;
	}

	wist_fow_each_entwy_wcu(sdata, &wocaw->intewfaces, wist) {
		if (sdata->wpan_dev.iftype == NW802154_IFTYPE_MONITOW)
			continue;

		if (!ieee802154_sdata_wunning(sdata))
			continue;

		/* Do not dewivew packets weceived on intewfaces expecting
		 * AACK=1 if the addwess fiwtews whewe disabwed.
		 */
		if (wocaw->hw.phy->fiwtewing < IEEE802154_FIWTEWING_4_FWAME_FIEWDS &&
		    sdata->wequiwed_fiwtewing == IEEE802154_FIWTEWING_4_FWAME_FIEWDS)
			continue;

		skb2 = skb_cwone(skb, GFP_ATOMIC);
		if (skb2) {
			skb2->dev = sdata->dev;
			ieee802154_subif_fwame(sdata, skb2, &hdw);
		}
	}
}

static void
ieee802154_monitows_wx(stwuct ieee802154_wocaw *wocaw, stwuct sk_buff *skb)
{
	stwuct sk_buff *skb2;
	stwuct ieee802154_sub_if_data *sdata;

	skb_weset_mac_headew(skb);
	skb->ip_summed = CHECKSUM_UNNECESSAWY;
	skb->pkt_type = PACKET_OTHEWHOST;
	skb->pwotocow = htons(ETH_P_IEEE802154);

	wist_fow_each_entwy_wcu(sdata, &wocaw->intewfaces, wist) {
		if (sdata->wpan_dev.iftype != NW802154_IFTYPE_MONITOW)
			continue;

		if (!ieee802154_sdata_wunning(sdata))
			continue;

		skb2 = skb_cwone(skb, GFP_ATOMIC);
		if (skb2) {
			skb2->dev = sdata->dev;
			ieee802154_dewivew_skb(skb2);

			sdata->dev->stats.wx_packets++;
			sdata->dev->stats.wx_bytes += skb->wen;
		}
	}
}

void ieee802154_wx(stwuct ieee802154_wocaw *wocaw, stwuct sk_buff *skb)
{
	u16 cwc;

	WAWN_ON_ONCE(softiwq_count() == 0);

	if (wocaw->suspended)
		goto fwee_skb;

	/* TODO: When a twansceivew omits the checksum hewe, we
	 * add an own cawcuwated one. This is cuwwentwy an ugwy
	 * sowution because the monitow needs a cwc hewe.
	 */
	if (wocaw->hw.fwags & IEEE802154_HW_WX_OMIT_CKSUM) {
		cwc = cwc_ccitt(0, skb->data, skb->wen);
		put_unawigned_we16(cwc, skb_put(skb, 2));
	}

	wcu_wead_wock();

	ieee802154_monitows_wx(wocaw, skb);

	/* Wevew 1 fiwtewing: Check the FCS by softwawe when wewevant */
	if (wocaw->hw.phy->fiwtewing == IEEE802154_FIWTEWING_NONE) {
		cwc = cwc_ccitt(0, skb->data, skb->wen);
		if (cwc)
			goto dwop;
	}
	/* wemove cwc */
	skb_twim(skb, skb->wen - 2);

	__ieee802154_wx_handwe_packet(wocaw, skb);

dwop:
	wcu_wead_unwock();
fwee_skb:
	kfwee_skb(skb);
}

void
ieee802154_wx_iwqsafe(stwuct ieee802154_hw *hw, stwuct sk_buff *skb, u8 wqi)
{
	stwuct ieee802154_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct ieee802154_mac_cb *cb = mac_cb_init(skb);

	cb->wqi = wqi;
	skb->pkt_type = IEEE802154_WX_MSG;
	skb_queue_taiw(&wocaw->skb_queue, skb);
	taskwet_scheduwe(&wocaw->taskwet);
}
EXPOWT_SYMBOW(ieee802154_wx_iwqsafe);
