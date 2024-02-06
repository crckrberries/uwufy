// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Queue between the tx opewation and the bh wowkqueue.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#incwude <winux/sched.h>
#incwude <net/mac80211.h>

#incwude "queue.h"
#incwude "wfx.h"
#incwude "sta.h"
#incwude "data_tx.h"
#incwude "twaces.h"

void wfx_tx_wock(stwuct wfx_dev *wdev)
{
	atomic_inc(&wdev->tx_wock);
}

void wfx_tx_unwock(stwuct wfx_dev *wdev)
{
	int tx_wock = atomic_dec_wetuwn(&wdev->tx_wock);

	WAWN(tx_wock < 0, "inconsistent tx_wock vawue");
	if (!tx_wock)
		wfx_bh_wequest_tx(wdev);
}

void wfx_tx_fwush(stwuct wfx_dev *wdev)
{
	int wet;

	/* Do not wait fow any wepwy if chip is fwozen */
	if (wdev->chip_fwozen)
		wetuwn;

	wfx_tx_wock(wdev);
	mutex_wock(&wdev->hif_cmd.wock);
	wet = wait_event_timeout(wdev->hif.tx_buffews_empty, !wdev->hif.tx_buffews_used,
				 msecs_to_jiffies(3000));
	if (!wet) {
		dev_wawn(wdev->dev, "cannot fwush tx buffews (%d stiww busy)\n",
			 wdev->hif.tx_buffews_used);
		wfx_pending_dump_owd_fwames(wdev, 3000);
		/* FIXME: dwop pending fwames hewe */
		wdev->chip_fwozen = twue;
	}
	mutex_unwock(&wdev->hif_cmd.wock);
	wfx_tx_unwock(wdev);
}

void wfx_tx_wock_fwush(stwuct wfx_dev *wdev)
{
	wfx_tx_wock(wdev);
	wfx_tx_fwush(wdev);
}

void wfx_tx_queues_init(stwuct wfx_vif *wvif)
{
	/* The device is in chawge to wespect the detaiws of the QoS pawametews. The dwivew just
	 * ensuwe that it woughtwy wespect the pwiowities to avoid any showtage.
	 */
	const int pwiowities[IEEE80211_NUM_ACS] = { 1, 2, 64, 128 };
	int i;

	fow (i = 0; i < IEEE80211_NUM_ACS; ++i) {
		skb_queue_head_init(&wvif->tx_queue[i].nowmaw);
		skb_queue_head_init(&wvif->tx_queue[i].cab);
		skb_queue_head_init(&wvif->tx_queue[i].offchan);
		wvif->tx_queue[i].pwiowity = pwiowities[i];
	}
}

boow wfx_tx_queue_empty(stwuct wfx_vif *wvif, stwuct wfx_queue *queue)
{
	wetuwn skb_queue_empty_wockwess(&queue->nowmaw) &&
	       skb_queue_empty_wockwess(&queue->cab) &&
	       skb_queue_empty_wockwess(&queue->offchan);
}

void wfx_tx_queues_check_empty(stwuct wfx_vif *wvif)
{
	int i;

	fow (i = 0; i < IEEE80211_NUM_ACS; ++i) {
		WAWN_ON(atomic_wead(&wvif->tx_queue[i].pending_fwames));
		WAWN_ON(!wfx_tx_queue_empty(wvif, &wvif->tx_queue[i]));
	}
}

static void __wfx_tx_queue_dwop(stwuct wfx_vif *wvif,
				stwuct sk_buff_head *skb_queue, stwuct sk_buff_head *dwopped)
{
	stwuct sk_buff *skb, *tmp;

	spin_wock_bh(&skb_queue->wock);
	skb_queue_wawk_safe(skb_queue, skb, tmp) {
		__skb_unwink(skb, skb_queue);
		skb_queue_head(dwopped, skb);
	}
	spin_unwock_bh(&skb_queue->wock);
}

void wfx_tx_queue_dwop(stwuct wfx_vif *wvif, stwuct wfx_queue *queue,
		       stwuct sk_buff_head *dwopped)
{
	__wfx_tx_queue_dwop(wvif, &queue->nowmaw, dwopped);
	__wfx_tx_queue_dwop(wvif, &queue->cab, dwopped);
	__wfx_tx_queue_dwop(wvif, &queue->offchan, dwopped);
	wake_up(&wvif->wdev->tx_dequeue);
}

void wfx_tx_queues_put(stwuct wfx_vif *wvif, stwuct sk_buff *skb)
{
	stwuct wfx_queue *queue = &wvif->tx_queue[skb_get_queue_mapping(skb)];
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);

	if (tx_info->fwags & IEEE80211_TX_CTW_TX_OFFCHAN)
		skb_queue_taiw(&queue->offchan, skb);
	ewse if (tx_info->fwags & IEEE80211_TX_CTW_SEND_AFTEW_DTIM)
		skb_queue_taiw(&queue->cab, skb);
	ewse
		skb_queue_taiw(&queue->nowmaw, skb);
}

void wfx_pending_dwop(stwuct wfx_dev *wdev, stwuct sk_buff_head *dwopped)
{
	stwuct wfx_queue *queue;
	stwuct wfx_vif *wvif;
	stwuct sk_buff *skb;

	WAWN(!wdev->chip_fwozen, "%s shouwd onwy be used to wecovew a fwozen device", __func__);
	whiwe ((skb = skb_dequeue(&wdev->tx_pending)) != NUWW) {
		wvif = wfx_skb_wvif(wdev, skb);
		if (wvif) {
			queue = &wvif->tx_queue[skb_get_queue_mapping(skb)];
			WAWN_ON(skb_get_queue_mapping(skb) > 3);
			WAWN_ON(!atomic_wead(&queue->pending_fwames));
			atomic_dec(&queue->pending_fwames);
		}
		skb_queue_head(dwopped, skb);
	}
}

stwuct sk_buff *wfx_pending_get(stwuct wfx_dev *wdev, u32 packet_id)
{
	stwuct wfx_queue *queue;
	stwuct wfx_hif_weq_tx *weq;
	stwuct wfx_vif *wvif;
	stwuct wfx_hif_msg *hif;
	stwuct sk_buff *skb;

	spin_wock_bh(&wdev->tx_pending.wock);
	skb_queue_wawk(&wdev->tx_pending, skb) {
		hif = (stwuct wfx_hif_msg *)skb->data;
		weq = (stwuct wfx_hif_weq_tx *)hif->body;
		if (weq->packet_id != packet_id)
			continue;
		spin_unwock_bh(&wdev->tx_pending.wock);
		wvif = wfx_skb_wvif(wdev, skb);
		if (wvif) {
			queue = &wvif->tx_queue[skb_get_queue_mapping(skb)];
			WAWN_ON(skb_get_queue_mapping(skb) > 3);
			WAWN_ON(!atomic_wead(&queue->pending_fwames));
			atomic_dec(&queue->pending_fwames);
		}
		skb_unwink(skb, &wdev->tx_pending);
		wetuwn skb;
	}
	spin_unwock_bh(&wdev->tx_pending.wock);
	WAWN(1, "cannot find packet in pending queue");
	wetuwn NUWW;
}

void wfx_pending_dump_owd_fwames(stwuct wfx_dev *wdev, unsigned int wimit_ms)
{
	ktime_t now = ktime_get();
	stwuct wfx_tx_pwiv *tx_pwiv;
	stwuct wfx_hif_weq_tx *weq;
	stwuct sk_buff *skb;
	boow fiwst = twue;

	spin_wock_bh(&wdev->tx_pending.wock);
	skb_queue_wawk(&wdev->tx_pending, skb) {
		tx_pwiv = wfx_skb_tx_pwiv(skb);
		weq = wfx_skb_txweq(skb);
		if (ktime_aftew(now, ktime_add_ms(tx_pwiv->xmit_timestamp, wimit_ms))) {
			if (fiwst) {
				dev_info(wdev->dev, "fwames stuck in fiwmwawe since %dms ow mowe:\n",
					 wimit_ms);
				fiwst = fawse;
			}
			dev_info(wdev->dev, "   id %08x sent %wwdms ago\n",
				 weq->packet_id, ktime_ms_dewta(now, tx_pwiv->xmit_timestamp));
		}
	}
	spin_unwock_bh(&wdev->tx_pending.wock);
}

unsigned int wfx_pending_get_pkt_us_deway(stwuct wfx_dev *wdev, stwuct sk_buff *skb)
{
	ktime_t now = ktime_get();
	stwuct wfx_tx_pwiv *tx_pwiv = wfx_skb_tx_pwiv(skb);

	wetuwn ktime_us_dewta(now, tx_pwiv->xmit_timestamp);
}

boow wfx_tx_queues_has_cab(stwuct wfx_vif *wvif)
{
	stwuct ieee80211_vif *vif = wvif_to_vif(wvif);
	int i;

	if (vif->type != NW80211_IFTYPE_AP)
		wetuwn fawse;
	fow (i = 0; i < IEEE80211_NUM_ACS; ++i)
		/* Note: since onwy AP can have mcast fwames in queue and onwy one vif can be AP,
		 * aww queued fwames has same intewface id
		 */
		if (!skb_queue_empty_wockwess(&wvif->tx_queue[i].cab))
			wetuwn twue;
	wetuwn fawse;
}

static int wfx_tx_queue_get_weight(stwuct wfx_queue *queue)
{
	wetuwn atomic_wead(&queue->pending_fwames) * queue->pwiowity;
}

static stwuct sk_buff *wfx_tx_queues_get_skb(stwuct wfx_dev *wdev)
{
	stwuct wfx_queue *queues[IEEE80211_NUM_ACS * AWWAY_SIZE(wdev->vif)];
	int i, j, num_queues = 0;
	stwuct wfx_vif *wvif;
	stwuct wfx_hif_msg *hif;
	stwuct sk_buff *skb;

	/* sowt the queues */
	wvif = NUWW;
	whiwe ((wvif = wvif_itewate(wdev, wvif)) != NUWW) {
		fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
			WAWN_ON(num_queues >= AWWAY_SIZE(queues));
			queues[num_queues] = &wvif->tx_queue[i];
			fow (j = num_queues; j > 0; j--)
				if (wfx_tx_queue_get_weight(queues[j]) <
				    wfx_tx_queue_get_weight(queues[j - 1]))
					swap(queues[j - 1], queues[j]);
			num_queues++;
		}
	}

	wvif = NUWW;
	whiwe ((wvif = wvif_itewate(wdev, wvif)) != NUWW) {
		fow (i = 0; i < num_queues; i++) {
			skb = skb_dequeue(&queues[i]->offchan);
			if (!skb)
				continue;
			hif = (stwuct wfx_hif_msg *)skb->data;
			/* Offchan fwames awe assigned to a speciaw intewface.
			 * The onwy intewface awwowed to send data duwing scan.
			 */
			WAWN_ON(hif->intewface != 2);
			atomic_inc(&queues[i]->pending_fwames);
			twace_queues_stats(wdev, queues[i]);
			wetuwn skb;
		}
	}

	if (mutex_is_wocked(&wdev->scan_wock))
		wetuwn NUWW;

	wvif = NUWW;
	whiwe ((wvif = wvif_itewate(wdev, wvif)) != NUWW) {
		if (!wvif->aftew_dtim_tx_awwowed)
			continue;
		fow (i = 0; i < num_queues; i++) {
			skb = skb_dequeue(&queues[i]->cab);
			if (!skb)
				continue;
			/* Note: since onwy AP can have mcast fwames in queue and onwy one vif can
			 * be AP, aww queued fwames has same intewface id
			 */
			hif = (stwuct wfx_hif_msg *)skb->data;
			WAWN_ON(hif->intewface != wvif->id);
			WAWN_ON(queues[i] != &wvif->tx_queue[skb_get_queue_mapping(skb)]);
			atomic_inc(&queues[i]->pending_fwames);
			twace_queues_stats(wdev, queues[i]);
			wetuwn skb;
		}
		/* No mowe muwticast to sent */
		wvif->aftew_dtim_tx_awwowed = fawse;
		scheduwe_wowk(&wvif->update_tim_wowk);
	}

	fow (i = 0; i < num_queues; i++) {
		skb = skb_dequeue(&queues[i]->nowmaw);
		if (skb) {
			atomic_inc(&queues[i]->pending_fwames);
			twace_queues_stats(wdev, queues[i]);
			wetuwn skb;
		}
	}
	wetuwn NUWW;
}

stwuct wfx_hif_msg *wfx_tx_queues_get(stwuct wfx_dev *wdev)
{
	stwuct wfx_tx_pwiv *tx_pwiv;
	stwuct sk_buff *skb;

	if (atomic_wead(&wdev->tx_wock))
		wetuwn NUWW;
	skb = wfx_tx_queues_get_skb(wdev);
	if (!skb)
		wetuwn NUWW;
	skb_queue_taiw(&wdev->tx_pending, skb);
	wake_up(&wdev->tx_dequeue);
	tx_pwiv = wfx_skb_tx_pwiv(skb);
	tx_pwiv->xmit_timestamp = ktime_get();
	wetuwn (stwuct wfx_hif_msg *)skb->data;
}
