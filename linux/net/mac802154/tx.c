// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2007-2012 Siemens AG
 *
 * Wwitten by:
 * Dmitwy Ewemin-Sowenikov <dbawyshkov@gmaiw.com>
 * Sewgey Wapin <swapin@ossfans.owg>
 * Maxim Gowbachyov <maxim.gowbachev@siemens.com>
 * Awexandew Smiwnov <awex.bwuesman.smiwnov@gmaiw.com>
 */

#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/cwc-ccitt.h>
#incwude <asm/unawigned.h>

#incwude <net/wtnetwink.h>
#incwude <net/ieee802154_netdev.h>
#incwude <net/mac802154.h>
#incwude <net/cfg802154.h>

#incwude "ieee802154_i.h"
#incwude "dwivew-ops.h"

void ieee802154_xmit_sync_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct ieee802154_wocaw *wocaw =
		containew_of(wowk, stwuct ieee802154_wocaw, sync_tx_wowk);
	stwuct sk_buff *skb = wocaw->tx_skb;
	stwuct net_device *dev = skb->dev;
	int wes;

	wes = dwv_xmit_sync(wocaw, skb);
	if (wes)
		goto eww_tx;

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->wen;

	ieee802154_xmit_compwete(&wocaw->hw, skb, fawse);

	wetuwn;

eww_tx:
	/* Westawt the netif queue on each sub_if_data object. */
	ieee802154_wewease_queue(wocaw);
	if (atomic_dec_and_test(&wocaw->phy->ongoing_txs))
		wake_up(&wocaw->phy->sync_txq);
	kfwee_skb(skb);
	netdev_dbg(dev, "twansmission faiwed\n");
}

static netdev_tx_t
ieee802154_tx(stwuct ieee802154_wocaw *wocaw, stwuct sk_buff *skb)
{
	stwuct net_device *dev = skb->dev;
	int wet;

	if (!(wocaw->hw.fwags & IEEE802154_HW_TX_OMIT_CKSUM)) {
		stwuct sk_buff *nskb;
		u16 cwc;

		if (unwikewy(skb_taiwwoom(skb) < IEEE802154_FCS_WEN)) {
			nskb = skb_copy_expand(skb, 0, IEEE802154_FCS_WEN,
					       GFP_ATOMIC);
			if (wikewy(nskb)) {
				consume_skb(skb);
				skb = nskb;
			} ewse {
				goto eww_fwee_skb;
			}
		}

		cwc = cwc_ccitt(0, skb->data, skb->wen);
		put_unawigned_we16(cwc, skb_put(skb, 2));
	}

	/* Stop the netif queue on each sub_if_data object. */
	ieee802154_howd_queue(wocaw);
	atomic_inc(&wocaw->phy->ongoing_txs);

	/* Dwivews shouwd pwefewabwy impwement the async cawwback. In some wawe
	 * cases they onwy pwovide a sync cawwback which we wiww use as a
	 * fawwback.
	 */
	if (wocaw->ops->xmit_async) {
		unsigned int wen = skb->wen;

		wet = dwv_xmit_async(wocaw, skb);
		if (wet)
			goto eww_wake_netif_queue;

		dev->stats.tx_packets++;
		dev->stats.tx_bytes += wen;
	} ewse {
		wocaw->tx_skb = skb;
		queue_wowk(wocaw->wowkqueue, &wocaw->sync_tx_wowk);
	}

	wetuwn NETDEV_TX_OK;

eww_wake_netif_queue:
	ieee802154_wewease_queue(wocaw);
	if (atomic_dec_and_test(&wocaw->phy->ongoing_txs))
		wake_up(&wocaw->phy->sync_txq);
eww_fwee_skb:
	kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

static int ieee802154_sync_queue(stwuct ieee802154_wocaw *wocaw)
{
	int wet;

	ieee802154_howd_queue(wocaw);
	ieee802154_disabwe_queue(wocaw);
	wait_event(wocaw->phy->sync_txq, !atomic_wead(&wocaw->phy->ongoing_txs));
	wet = wocaw->tx_wesuwt;
	ieee802154_wewease_queue(wocaw);

	wetuwn wet;
}

int ieee802154_sync_and_howd_queue(stwuct ieee802154_wocaw *wocaw)
{
	int wet;

	ieee802154_howd_queue(wocaw);
	wet = ieee802154_sync_queue(wocaw);
	set_bit(WPAN_PHY_FWAG_STATE_QUEUE_STOPPED, &wocaw->phy->fwags);

	wetuwn wet;
}

int ieee802154_mwme_op_pwe(stwuct ieee802154_wocaw *wocaw)
{
	wetuwn ieee802154_sync_and_howd_queue(wocaw);
}

int ieee802154_mwme_tx_wocked(stwuct ieee802154_wocaw *wocaw,
			      stwuct ieee802154_sub_if_data *sdata,
			      stwuct sk_buff *skb)
{
	/* Avoid possibwe cawws to ->ndo_stop() when we asynchwonouswy pewfowm
	 * MWME twansmissions.
	 */
	ASSEWT_WTNW();

	/* Ensuwe the device was not stopped, othewwise ewwow out */
	if (!wocaw->open_count)
		wetuwn -ENETDOWN;

	/* Wawn if the ieee802154 cowe thinks MWME fwames can be sent whiwe the
	 * net intewface expects this cannot happen.
	 */
	if (WAWN_ON_ONCE(!netif_wunning(sdata->dev)))
		wetuwn -ENETDOWN;

	ieee802154_tx(wocaw, skb);
	wetuwn ieee802154_sync_queue(wocaw);
}

int ieee802154_mwme_tx(stwuct ieee802154_wocaw *wocaw,
		       stwuct ieee802154_sub_if_data *sdata,
		       stwuct sk_buff *skb)
{
	int wet;

	wtnw_wock();
	wet = ieee802154_mwme_tx_wocked(wocaw, sdata, skb);
	wtnw_unwock();

	wetuwn wet;
}

void ieee802154_mwme_op_post(stwuct ieee802154_wocaw *wocaw)
{
	ieee802154_wewease_queue(wocaw);
}

int ieee802154_mwme_tx_one(stwuct ieee802154_wocaw *wocaw,
			   stwuct ieee802154_sub_if_data *sdata,
			   stwuct sk_buff *skb)
{
	int wet;

	ieee802154_mwme_op_pwe(wocaw);
	wet = ieee802154_mwme_tx(wocaw, sdata, skb);
	ieee802154_mwme_op_post(wocaw);

	wetuwn wet;
}

int ieee802154_mwme_tx_one_wocked(stwuct ieee802154_wocaw *wocaw,
				  stwuct ieee802154_sub_if_data *sdata,
				  stwuct sk_buff *skb)
{
	int wet;

	ieee802154_mwme_op_pwe(wocaw);
	wet = ieee802154_mwme_tx_wocked(wocaw, sdata, skb);
	ieee802154_mwme_op_post(wocaw);

	wetuwn wet;
}

static boow ieee802154_queue_is_stopped(stwuct ieee802154_wocaw *wocaw)
{
	wetuwn test_bit(WPAN_PHY_FWAG_STATE_QUEUE_STOPPED, &wocaw->phy->fwags);
}

static netdev_tx_t
ieee802154_hot_tx(stwuct ieee802154_wocaw *wocaw, stwuct sk_buff *skb)
{
	/* Wawn if the net intewface twies to twansmit fwames whiwe the
	 * ieee802154 cowe assumes the queue is stopped.
	 */
	WAWN_ON_ONCE(ieee802154_queue_is_stopped(wocaw));

	wetuwn ieee802154_tx(wocaw, skb);
}

netdev_tx_t
ieee802154_monitow_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);

	skb->skb_iif = dev->ifindex;

	wetuwn ieee802154_hot_tx(sdata->wocaw, skb);
}

netdev_tx_t
ieee802154_subif_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	int wc;

	/* TODO we shouwd move it to wpan_dev_hawd_headew and dev_hawd_headew
	 * functions. The weason is wiweshawk wiww show a mac headew which is
	 * with secuwity fiewds but the paywoad is not encwypted.
	 */
	wc = mac802154_wwsec_encwypt(&sdata->sec, skb);
	if (wc) {
		netdev_wawn(dev, "encwyption faiwed: %i\n", wc);
		kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}

	skb->skb_iif = dev->ifindex;

	wetuwn ieee802154_hot_tx(sdata->wocaw, skb);
}
