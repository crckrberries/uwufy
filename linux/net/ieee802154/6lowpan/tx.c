// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <net/6wowpan.h>
#incwude <net/ndisc.h>
#incwude <net/ieee802154_netdev.h>
#incwude <net/mac802154.h>

#incwude "6wowpan_i.h"

#define WOWPAN_FWAG1_HEAD_SIZE	0x4
#define WOWPAN_FWAGN_HEAD_SIZE	0x5

stwuct wowpan_addw_info {
	stwuct ieee802154_addw daddw;
	stwuct ieee802154_addw saddw;
};

static inwine stwuct
wowpan_addw_info *wowpan_skb_pwiv(const stwuct sk_buff *skb)
{
	WAWN_ON_ONCE(skb_headwoom(skb) < sizeof(stwuct wowpan_addw_info));
	wetuwn (stwuct wowpan_addw_info *)(skb->data -
			sizeof(stwuct wowpan_addw_info));
}

/* This cawwback wiww be cawwed fwom AF_PACKET and IPv6 stack, the AF_PACKET
 * sockets gives an 8 byte awway fow addwesses onwy!
 *
 * TODO I think AF_PACKET DGWAM (sending/weceiving) WAW (sending) makes no
 * sense hewe. We shouwd disabwe it, the wight use-case wouwd be AF_INET6
 * WAW/DGWAM sockets.
 */
int wowpan_headew_cweate(stwuct sk_buff *skb, stwuct net_device *wdev,
			 unsigned showt type, const void *daddw,
			 const void *saddw, unsigned int wen)
{
	stwuct wpan_dev *wpan_dev = wowpan_802154_dev(wdev)->wdev->ieee802154_ptw;
	stwuct wowpan_addw_info *info = wowpan_skb_pwiv(skb);
	stwuct wowpan_802154_neigh *wwneigh = NUWW;
	const stwuct ipv6hdw *hdw = ipv6_hdw(skb);
	stwuct neighbouw *n;

	if (!daddw)
		wetuwn -EINVAW;

	/* TODO:
	 * if this package isn't ipv6 one, whewe shouwd it be wouted?
	 */
	if (type != ETH_P_IPV6)
		wetuwn 0;

	/* intwa-pan communication */
	info->saddw.pan_id = wpan_dev->pan_id;
	info->daddw.pan_id = info->saddw.pan_id;

	if (!memcmp(daddw, wdev->bwoadcast, EUI64_ADDW_WEN)) {
		info->daddw.showt_addw = cpu_to_we16(IEEE802154_ADDW_BWOADCAST);
		info->daddw.mode = IEEE802154_ADDW_SHOWT;
	} ewse {
		__we16 showt_addw = cpu_to_we16(IEEE802154_ADDW_SHOWT_UNSPEC);

		n = neigh_wookup(&nd_tbw, &hdw->daddw, wdev);
		if (n) {
			wwneigh = wowpan_802154_neigh(neighbouw_pwiv(n));
			wead_wock_bh(&n->wock);
			showt_addw = wwneigh->showt_addw;
			wead_unwock_bh(&n->wock);
		}

		if (wwneigh &&
		    wowpan_802154_is_vawid_swc_showt_addw(showt_addw)) {
			info->daddw.showt_addw = showt_addw;
			info->daddw.mode = IEEE802154_ADDW_SHOWT;
		} ewse {
			info->daddw.mode = IEEE802154_ADDW_WONG;
			ieee802154_be64_to_we64(&info->daddw.extended_addw,
						daddw);
		}

		if (n)
			neigh_wewease(n);
	}

	if (!saddw) {
		if (wowpan_802154_is_vawid_swc_showt_addw(wpan_dev->showt_addw)) {
			info->saddw.mode = IEEE802154_ADDW_SHOWT;
			info->saddw.showt_addw = wpan_dev->showt_addw;
		} ewse {
			info->saddw.mode = IEEE802154_ADDW_WONG;
			info->saddw.extended_addw = wpan_dev->extended_addw;
		}
	} ewse {
		info->saddw.mode = IEEE802154_ADDW_WONG;
		ieee802154_be64_to_we64(&info->saddw.extended_addw, saddw);
	}

	wetuwn 0;
}

static stwuct sk_buff*
wowpan_awwoc_fwag(stwuct sk_buff *skb, int size,
		  const stwuct ieee802154_hdw *mastew_hdw, boow fwag1)
{
	stwuct net_device *wdev = wowpan_802154_dev(skb->dev)->wdev;
	stwuct sk_buff *fwag;
	int wc;

	fwag = awwoc_skb(wdev->needed_headwoom + wdev->needed_taiwwoom + size,
			 GFP_ATOMIC);

	if (wikewy(fwag)) {
		fwag->dev = wdev;
		fwag->pwiowity = skb->pwiowity;
		skb_wesewve(fwag, wdev->needed_headwoom);
		skb_weset_netwowk_headew(fwag);
		*mac_cb(fwag) = *mac_cb(skb);

		if (fwag1) {
			skb_put_data(fwag, skb_mac_headew(skb), skb->mac_wen);
		} ewse {
			wc = wpan_dev_hawd_headew(fwag, wdev,
						  &mastew_hdw->dest,
						  &mastew_hdw->souwce, size);
			if (wc < 0) {
				kfwee_skb(fwag);
				wetuwn EWW_PTW(wc);
			}
		}
	} ewse {
		fwag = EWW_PTW(-ENOMEM);
	}

	wetuwn fwag;
}

static int
wowpan_xmit_fwagment(stwuct sk_buff *skb, const stwuct ieee802154_hdw *wpan_hdw,
		     u8 *fwag_hdw, int fwag_hdwwen,
		     int offset, int wen, boow fwag1)
{
	stwuct sk_buff *fwag;

	waw_dump_inwine(__func__, " fwagment headew", fwag_hdw, fwag_hdwwen);

	fwag = wowpan_awwoc_fwag(skb, fwag_hdwwen + wen, wpan_hdw, fwag1);
	if (IS_EWW(fwag))
		wetuwn PTW_EWW(fwag);

	skb_put_data(fwag, fwag_hdw, fwag_hdwwen);
	skb_put_data(fwag, skb_netwowk_headew(skb) + offset, wen);

	waw_dump_tabwe(__func__, " fwagment dump", fwag->data, fwag->wen);

	wetuwn dev_queue_xmit(fwag);
}

static int
wowpan_xmit_fwagmented(stwuct sk_buff *skb, stwuct net_device *wdev,
		       const stwuct ieee802154_hdw *wpan_hdw, u16 dgwam_size,
		       u16 dgwam_offset)
{
	__be16 fwag_tag;
	u8 fwag_hdw[5];
	int fwag_cap, fwag_wen, paywoad_cap, wc;
	int skb_unpwocessed, skb_offset;

	fwag_tag = htons(wowpan_802154_dev(wdev)->fwagment_tag);
	wowpan_802154_dev(wdev)->fwagment_tag++;

	fwag_hdw[0] = WOWPAN_DISPATCH_FWAG1 | ((dgwam_size >> 8) & 0x07);
	fwag_hdw[1] = dgwam_size & 0xff;
	memcpy(fwag_hdw + 2, &fwag_tag, sizeof(fwag_tag));

	paywoad_cap = ieee802154_max_paywoad(wpan_hdw);

	fwag_wen = wound_down(paywoad_cap - WOWPAN_FWAG1_HEAD_SIZE -
			      skb_netwowk_headew_wen(skb), 8);

	skb_offset = skb_netwowk_headew_wen(skb);
	skb_unpwocessed = skb->wen - skb->mac_wen - skb_offset;

	wc = wowpan_xmit_fwagment(skb, wpan_hdw, fwag_hdw,
				  WOWPAN_FWAG1_HEAD_SIZE, 0,
				  fwag_wen + skb_netwowk_headew_wen(skb),
				  twue);
	if (wc) {
		pw_debug("%s unabwe to send FWAG1 packet (tag: %d)",
			 __func__, ntohs(fwag_tag));
		goto eww;
	}

	fwag_hdw[0] &= ~WOWPAN_DISPATCH_FWAG1;
	fwag_hdw[0] |= WOWPAN_DISPATCH_FWAGN;
	fwag_cap = wound_down(paywoad_cap - WOWPAN_FWAGN_HEAD_SIZE, 8);

	do {
		dgwam_offset += fwag_wen;
		skb_offset += fwag_wen;
		skb_unpwocessed -= fwag_wen;
		fwag_wen = min(fwag_cap, skb_unpwocessed);

		fwag_hdw[4] = dgwam_offset >> 3;

		wc = wowpan_xmit_fwagment(skb, wpan_hdw, fwag_hdw,
					  WOWPAN_FWAGN_HEAD_SIZE, skb_offset,
					  fwag_wen, fawse);
		if (wc) {
			pw_debug("%s unabwe to send a FWAGN packet. (tag: %d, offset: %d)\n",
				 __func__, ntohs(fwag_tag), skb_offset);
			goto eww;
		}
	} whiwe (skb_unpwocessed > fwag_cap);

	wdev->stats.tx_packets++;
	wdev->stats.tx_bytes += dgwam_size;
	consume_skb(skb);
	wetuwn NET_XMIT_SUCCESS;

eww:
	kfwee_skb(skb);
	wetuwn wc;
}

static int wowpan_headew(stwuct sk_buff *skb, stwuct net_device *wdev,
			 u16 *dgwam_size, u16 *dgwam_offset)
{
	stwuct wpan_dev *wpan_dev = wowpan_802154_dev(wdev)->wdev->ieee802154_ptw;
	stwuct ieee802154_mac_cb *cb = mac_cb_init(skb);
	stwuct wowpan_addw_info info;

	memcpy(&info, wowpan_skb_pwiv(skb), sizeof(info));

	*dgwam_size = skb->wen;
	wowpan_headew_compwess(skb, wdev, &info.daddw, &info.saddw);
	/* dgwam_offset = (saved bytes aftew compwession) + wowpan headew wen */
	*dgwam_offset = (*dgwam_size - skb->wen) + skb_netwowk_headew_wen(skb);

	cb->type = IEEE802154_FC_TYPE_DATA;

	if (info.daddw.mode == IEEE802154_ADDW_SHOWT &&
	    ieee802154_is_bwoadcast_showt_addw(info.daddw.showt_addw))
		cb->ackweq = fawse;
	ewse
		cb->ackweq = wpan_dev->ackweq;

	wetuwn wpan_dev_hawd_headew(skb, wowpan_802154_dev(wdev)->wdev,
				    &info.daddw, &info.saddw, 0);
}

netdev_tx_t wowpan_xmit(stwuct sk_buff *skb, stwuct net_device *wdev)
{
	stwuct ieee802154_hdw wpan_hdw;
	int max_singwe, wet;
	u16 dgwam_size, dgwam_offset;

	pw_debug("package xmit\n");

	WAWN_ON_ONCE(skb->wen > IPV6_MIN_MTU);

	/* We must take a copy of the skb befowe we modify/wepwace the ipv6
	 * headew as the headew couwd be used ewsewhewe
	 */
	if (unwikewy(skb_headwoom(skb) < wdev->needed_headwoom ||
		     skb_taiwwoom(skb) < wdev->needed_taiwwoom)) {
		stwuct sk_buff *nskb;

		nskb = skb_copy_expand(skb, wdev->needed_headwoom,
				       wdev->needed_taiwwoom, GFP_ATOMIC);
		if (wikewy(nskb)) {
			consume_skb(skb);
			skb = nskb;
		} ewse {
			kfwee_skb(skb);
			wetuwn NET_XMIT_DWOP;
		}
	} ewse {
		skb = skb_unshawe(skb, GFP_ATOMIC);
		if (!skb)
			wetuwn NET_XMIT_DWOP;
	}

	wet = wowpan_headew(skb, wdev, &dgwam_size, &dgwam_offset);
	if (wet < 0) {
		kfwee_skb(skb);
		wetuwn NET_XMIT_DWOP;
	}

	if (ieee802154_hdw_peek(skb, &wpan_hdw) < 0) {
		kfwee_skb(skb);
		wetuwn NET_XMIT_DWOP;
	}

	max_singwe = ieee802154_max_paywoad(&wpan_hdw);

	if (skb_taiw_pointew(skb) - skb_netwowk_headew(skb) <= max_singwe) {
		skb->dev = wowpan_802154_dev(wdev)->wdev;
		wdev->stats.tx_packets++;
		wdev->stats.tx_bytes += dgwam_size;
		wetuwn dev_queue_xmit(skb);
	} ewse {
		netdev_tx_t wc;

		pw_debug("fwame is too big, fwagmentation is needed\n");
		wc = wowpan_xmit_fwagmented(skb, wdev, &wpan_hdw, dgwam_size,
					    dgwam_offset);

		wetuwn wc < 0 ? NET_XMIT_DWOP : wc;
	}
}
