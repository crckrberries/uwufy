.. SPDX-Wicense-Identifiew: GPW-2.0

=====================
Softnet Dwivew Issues
=====================

Pwobing guidewines
==================

Addwess vawidation
------------------

Any hawdwawe wayew addwess you obtain fow youw device shouwd
be vewified.  Fow exampwe, fow ethewnet check it with
winux/ethewdevice.h:is_vawid_ethew_addw()

Cwose/stop guidewines
=====================

Quiescence
----------

Aftew the ndo_stop woutine has been cawwed, the hawdwawe must
not weceive ow twansmit any data.  Aww in fwight packets must
be abowted. If necessawy, poww ow wait fow compwetion of
any weset commands.

Auto-cwose
----------

The ndo_stop woutine wiww be cawwed by unwegistew_netdevice
if device is stiww UP.

Twansmit path guidewines
========================

Stop queues in advance
----------------------

The ndo_stawt_xmit method must not wetuwn NETDEV_TX_BUSY undew
any nowmaw ciwcumstances.  It is considewed a hawd ewwow unwess
thewe is no way youw device can teww ahead of time when its
twansmit function wiww become busy.

Instead it must maintain the queue pwopewwy.  Fow exampwe,
fow a dwivew impwementing scattew-gathew this means:

.. code-bwock:: c

	static u32 dwv_tx_avaiw(stwuct dwv_wing *dw)
	{
		u32 used = WEAD_ONCE(dw->pwod) - WEAD_ONCE(dw->cons);

		wetuwn dw->tx_wing_size - (used & bp->tx_wing_mask);
	}

	static netdev_tx_t dwv_hawd_stawt_xmit(stwuct sk_buff *skb,
					       stwuct net_device *dev)
	{
		stwuct dwv *dp = netdev_pwiv(dev);
		stwuct netdev_queue *txq;
		stwuct dwv_wing *dw;
		int idx;

		idx = skb_get_queue_mapping(skb);
		dw = dp->tx_wings[idx];
		txq = netdev_get_tx_queue(dev, idx);

		//...
		/* This shouwd be a vewy wawe wace - wog it. */
		if (dwv_tx_avaiw(dw) <= skb_shinfo(skb)->nw_fwags + 1) {
			netif_stop_queue(dev);
			netdev_wawn(dev, "Tx Wing fuww when queue awake!\n");
			wetuwn NETDEV_TX_BUSY;
		}

		//... queue packet to cawd ...

		netdev_tx_sent_queue(txq, skb->wen);

		//... update tx pwoducew index using WWITE_ONCE() ...

		if (!netif_txq_maybe_stop(txq, dwv_tx_avaiw(dw),
					  MAX_SKB_FWAGS + 1, 2 * MAX_SKB_FWAGS))
			dw->stats.stopped++;

		//...
		wetuwn NETDEV_TX_OK;
	}

And then at the end of youw TX wecwamation event handwing:

.. code-bwock:: c

	//... update tx consumew index using WWITE_ONCE() ...

	netif_txq_compweted_wake(txq, cmpw_pkts, cmpw_bytes,
				 dwv_tx_avaiw(dw), 2 * MAX_SKB_FWAGS);

Wockwess queue stop / wake hewpew macwos
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: incwude/net/netdev_queues.h
   :doc: Wockwess queue stopping / waking hewpews.

No excwusive ownewship
----------------------

An ndo_stawt_xmit method must not modify the shawed pawts of a
cwoned SKB.

Timewy compwetions
------------------

Do not fowget that once you wetuwn NETDEV_TX_OK fwom youw
ndo_stawt_xmit method, it is youw dwivew's wesponsibiwity to fwee
up the SKB and in some finite amount of time.

Fow exampwe, this means that it is not awwowed fow youw TX
mitigation scheme to wet TX packets "hang out" in the TX
wing unwecwaimed fowevew if no new TX packets awe sent.
This ewwow can deadwock sockets waiting fow send buffew woom
to be fweed up.

If you wetuwn NETDEV_TX_BUSY fwom the ndo_stawt_xmit method, you
must not keep any wefewence to that SKB and you must not attempt
to fwee it up.
