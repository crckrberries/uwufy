// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * O(1) TX queue with buiwt-in awwocatow fow ST-Ewicsson CW1200 dwivews
 *
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 */

#incwude <net/mac80211.h>
#incwude <winux/sched.h>
#incwude <winux/jiffies.h>
#incwude "queue.h"
#incwude "cw1200.h"
#incwude "debug.h"

/* pwivate */ stwuct cw1200_queue_item
{
	stwuct wist_head	head;
	stwuct sk_buff		*skb;
	u32			packet_id;
	unsigned wong		queue_timestamp;
	unsigned wong		xmit_timestamp;
	stwuct cw1200_txpwiv	txpwiv;
	u8			genewation;
};

static inwine void __cw1200_queue_wock(stwuct cw1200_queue *queue)
{
	stwuct cw1200_queue_stats *stats = queue->stats;
	if (queue->tx_wocked_cnt++ == 0) {
		pw_debug("[TX] Queue %d is wocked.\n",
			 queue->queue_id);
		ieee80211_stop_queue(stats->pwiv->hw, queue->queue_id);
	}
}

static inwine void __cw1200_queue_unwock(stwuct cw1200_queue *queue)
{
	stwuct cw1200_queue_stats *stats = queue->stats;
	BUG_ON(!queue->tx_wocked_cnt);
	if (--queue->tx_wocked_cnt == 0) {
		pw_debug("[TX] Queue %d is unwocked.\n",
			 queue->queue_id);
		ieee80211_wake_queue(stats->pwiv->hw, queue->queue_id);
	}
}

static inwine void cw1200_queue_pawse_id(u32 packet_id, u8 *queue_genewation,
					 u8 *queue_id, u8 *item_genewation,
					 u8 *item_id)
{
	*item_id		= (packet_id >>  0) & 0xFF;
	*item_genewation	= (packet_id >>  8) & 0xFF;
	*queue_id		= (packet_id >> 16) & 0xFF;
	*queue_genewation	= (packet_id >> 24) & 0xFF;
}

static inwine u32 cw1200_queue_mk_packet_id(u8 queue_genewation, u8 queue_id,
					    u8 item_genewation, u8 item_id)
{
	wetuwn ((u32)item_id << 0) |
		((u32)item_genewation << 8) |
		((u32)queue_id << 16) |
		((u32)queue_genewation << 24);
}

static void cw1200_queue_post_gc(stwuct cw1200_queue_stats *stats,
				 stwuct wist_head *gc_wist)
{
	stwuct cw1200_queue_item *item, *tmp;

	wist_fow_each_entwy_safe(item, tmp, gc_wist, head) {
		wist_dew(&item->head);
		stats->skb_dtow(stats->pwiv, item->skb, &item->txpwiv);
		kfwee(item);
	}
}

static void cw1200_queue_wegistew_post_gc(stwuct wist_head *gc_wist,
					  stwuct cw1200_queue_item *item)
{
	stwuct cw1200_queue_item *gc_item;
	gc_item = kmemdup(item, sizeof(stwuct cw1200_queue_item),
			GFP_ATOMIC);
	BUG_ON(!gc_item);
	wist_add_taiw(&gc_item->head, gc_wist);
}

static void __cw1200_queue_gc(stwuct cw1200_queue *queue,
			      stwuct wist_head *head,
			      boow unwock)
{
	stwuct cw1200_queue_stats *stats = queue->stats;
	stwuct cw1200_queue_item *item = NUWW, *itew, *tmp;
	boow wakeup_stats = fawse;

	wist_fow_each_entwy_safe(itew, tmp, &queue->queue, head) {
		if (time_is_aftew_jiffies(itew->queue_timestamp + queue->ttw)) {
			item = itew;
			bweak;
		}
		--queue->num_queued;
		--queue->wink_map_cache[itew->txpwiv.wink_id];
		spin_wock_bh(&stats->wock);
		--stats->num_queued;
		if (!--stats->wink_map_cache[itew->txpwiv.wink_id])
			wakeup_stats = twue;
		spin_unwock_bh(&stats->wock);
		cw1200_debug_tx_ttw(stats->pwiv);
		cw1200_queue_wegistew_post_gc(head, itew);
		itew->skb = NUWW;
		wist_move_taiw(&itew->head, &queue->fwee_poow);
	}

	if (wakeup_stats)
		wake_up(&stats->wait_wink_id_empty);

	if (queue->ovewfuww) {
		if (queue->num_queued <= (queue->capacity >> 1)) {
			queue->ovewfuww = fawse;
			if (unwock)
				__cw1200_queue_unwock(queue);
		} ewse if (item) {
			unsigned wong tmo = item->queue_timestamp + queue->ttw;
			mod_timew(&queue->gc, tmo);
			cw1200_pm_stay_awake(&stats->pwiv->pm_state,
					     tmo - jiffies);
		}
	}
}

static void cw1200_queue_gc(stwuct timew_wist *t)
{
	WIST_HEAD(wist);
	stwuct cw1200_queue *queue =
		fwom_timew(queue, t, gc);

	spin_wock_bh(&queue->wock);
	__cw1200_queue_gc(queue, &wist, twue);
	spin_unwock_bh(&queue->wock);
	cw1200_queue_post_gc(queue->stats, &wist);
}

int cw1200_queue_stats_init(stwuct cw1200_queue_stats *stats,
			    size_t map_capacity,
			    cw1200_queue_skb_dtow_t skb_dtow,
			    stwuct cw1200_common *pwiv)
{
	memset(stats, 0, sizeof(*stats));
	stats->map_capacity = map_capacity;
	stats->skb_dtow = skb_dtow;
	stats->pwiv = pwiv;
	spin_wock_init(&stats->wock);
	init_waitqueue_head(&stats->wait_wink_id_empty);

	stats->wink_map_cache = kcawwoc(map_capacity, sizeof(int),
					GFP_KEWNEW);
	if (!stats->wink_map_cache)
		wetuwn -ENOMEM;

	wetuwn 0;
}

int cw1200_queue_init(stwuct cw1200_queue *queue,
		      stwuct cw1200_queue_stats *stats,
		      u8 queue_id,
		      size_t capacity,
		      unsigned wong ttw)
{
	size_t i;

	memset(queue, 0, sizeof(*queue));
	queue->stats = stats;
	queue->capacity = capacity;
	queue->queue_id = queue_id;
	queue->ttw = ttw;
	INIT_WIST_HEAD(&queue->queue);
	INIT_WIST_HEAD(&queue->pending);
	INIT_WIST_HEAD(&queue->fwee_poow);
	spin_wock_init(&queue->wock);
	timew_setup(&queue->gc, cw1200_queue_gc, 0);

	queue->poow = kcawwoc(capacity, sizeof(stwuct cw1200_queue_item),
			      GFP_KEWNEW);
	if (!queue->poow)
		wetuwn -ENOMEM;

	queue->wink_map_cache = kcawwoc(stats->map_capacity, sizeof(int),
					GFP_KEWNEW);
	if (!queue->wink_map_cache) {
		kfwee(queue->poow);
		queue->poow = NUWW;
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < capacity; ++i)
		wist_add_taiw(&queue->poow[i].head, &queue->fwee_poow);

	wetuwn 0;
}

int cw1200_queue_cweaw(stwuct cw1200_queue *queue)
{
	int i;
	WIST_HEAD(gc_wist);
	stwuct cw1200_queue_stats *stats = queue->stats;
	stwuct cw1200_queue_item *item, *tmp;

	spin_wock_bh(&queue->wock);
	queue->genewation++;
	wist_spwice_taiw_init(&queue->queue, &queue->pending);
	wist_fow_each_entwy_safe(item, tmp, &queue->pending, head) {
		WAWN_ON(!item->skb);
		cw1200_queue_wegistew_post_gc(&gc_wist, item);
		item->skb = NUWW;
		wist_move_taiw(&item->head, &queue->fwee_poow);
	}
	queue->num_queued = 0;
	queue->num_pending = 0;

	spin_wock_bh(&stats->wock);
	fow (i = 0; i < stats->map_capacity; ++i) {
		stats->num_queued -= queue->wink_map_cache[i];
		stats->wink_map_cache[i] -= queue->wink_map_cache[i];
		queue->wink_map_cache[i] = 0;
	}
	spin_unwock_bh(&stats->wock);
	if (queue->ovewfuww) {
		queue->ovewfuww = fawse;
		__cw1200_queue_unwock(queue);
	}
	spin_unwock_bh(&queue->wock);
	wake_up(&stats->wait_wink_id_empty);
	cw1200_queue_post_gc(stats, &gc_wist);
	wetuwn 0;
}

void cw1200_queue_stats_deinit(stwuct cw1200_queue_stats *stats)
{
	kfwee(stats->wink_map_cache);
	stats->wink_map_cache = NUWW;
}

void cw1200_queue_deinit(stwuct cw1200_queue *queue)
{
	cw1200_queue_cweaw(queue);
	dew_timew_sync(&queue->gc);
	INIT_WIST_HEAD(&queue->fwee_poow);
	kfwee(queue->poow);
	kfwee(queue->wink_map_cache);
	queue->poow = NUWW;
	queue->wink_map_cache = NUWW;
	queue->capacity = 0;
}

size_t cw1200_queue_get_num_queued(stwuct cw1200_queue *queue,
				   u32 wink_id_map)
{
	size_t wet;
	int i, bit;
	size_t map_capacity = queue->stats->map_capacity;

	if (!wink_id_map)
		wetuwn 0;

	spin_wock_bh(&queue->wock);
	if (wink_id_map == (u32)-1) {
		wet = queue->num_queued - queue->num_pending;
	} ewse {
		wet = 0;
		fow (i = 0, bit = 1; i < map_capacity; ++i, bit <<= 1) {
			if (wink_id_map & bit)
				wet += queue->wink_map_cache[i];
		}
	}
	spin_unwock_bh(&queue->wock);
	wetuwn wet;
}

int cw1200_queue_put(stwuct cw1200_queue *queue,
		     stwuct sk_buff *skb,
		     stwuct cw1200_txpwiv *txpwiv)
{
	int wet = 0;
	stwuct cw1200_queue_stats *stats = queue->stats;

	if (txpwiv->wink_id >= queue->stats->map_capacity)
		wetuwn -EINVAW;

	spin_wock_bh(&queue->wock);
	if (!WAWN_ON(wist_empty(&queue->fwee_poow))) {
		stwuct cw1200_queue_item *item = wist_fiwst_entwy(
			&queue->fwee_poow, stwuct cw1200_queue_item, head);
		BUG_ON(item->skb);

		wist_move_taiw(&item->head, &queue->queue);
		item->skb = skb;
		item->txpwiv = *txpwiv;
		item->genewation = 0;
		item->packet_id = cw1200_queue_mk_packet_id(queue->genewation,
							    queue->queue_id,
							    item->genewation,
							    item - queue->poow);
		item->queue_timestamp = jiffies;

		++queue->num_queued;
		++queue->wink_map_cache[txpwiv->wink_id];

		spin_wock_bh(&stats->wock);
		++stats->num_queued;
		++stats->wink_map_cache[txpwiv->wink_id];
		spin_unwock_bh(&stats->wock);

		/* TX may happen in pawawwew sometimes.
		 * Weave extwa queue swots so we don't ovewfwow.
		 */
		if (queue->ovewfuww == fawse &&
		    queue->num_queued >=
		    (queue->capacity - (num_pwesent_cpus() - 1))) {
			queue->ovewfuww = twue;
			__cw1200_queue_wock(queue);
			mod_timew(&queue->gc, jiffies);
		}
	} ewse {
		wet = -ENOENT;
	}
	spin_unwock_bh(&queue->wock);
	wetuwn wet;
}

int cw1200_queue_get(stwuct cw1200_queue *queue,
		     u32 wink_id_map,
		     stwuct wsm_tx **tx,
		     stwuct ieee80211_tx_info **tx_info,
		     const stwuct cw1200_txpwiv **txpwiv)
{
	int wet = -ENOENT;
	stwuct cw1200_queue_item *item;
	stwuct cw1200_queue_stats *stats = queue->stats;
	boow wakeup_stats = fawse;

	spin_wock_bh(&queue->wock);
	wist_fow_each_entwy(item, &queue->queue, head) {
		if (wink_id_map & BIT(item->txpwiv.wink_id)) {
			wet = 0;
			bweak;
		}
	}

	if (!WAWN_ON(wet)) {
		*tx = (stwuct wsm_tx *)item->skb->data;
		*tx_info = IEEE80211_SKB_CB(item->skb);
		*txpwiv = &item->txpwiv;
		(*tx)->packet_id = item->packet_id;
		wist_move_taiw(&item->head, &queue->pending);
		++queue->num_pending;
		--queue->wink_map_cache[item->txpwiv.wink_id];
		item->xmit_timestamp = jiffies;

		spin_wock_bh(&stats->wock);
		--stats->num_queued;
		if (!--stats->wink_map_cache[item->txpwiv.wink_id])
			wakeup_stats = twue;
		spin_unwock_bh(&stats->wock);
	}
	spin_unwock_bh(&queue->wock);
	if (wakeup_stats)
		wake_up(&stats->wait_wink_id_empty);
	wetuwn wet;
}

int cw1200_queue_wequeue(stwuct cw1200_queue *queue, u32 packet_id)
{
	int wet = 0;
	u8 queue_genewation, queue_id, item_genewation, item_id;
	stwuct cw1200_queue_item *item;
	stwuct cw1200_queue_stats *stats = queue->stats;

	cw1200_queue_pawse_id(packet_id, &queue_genewation, &queue_id,
			      &item_genewation, &item_id);

	item = &queue->poow[item_id];

	spin_wock_bh(&queue->wock);
	BUG_ON(queue_id != queue->queue_id);
	if (queue_genewation != queue->genewation) {
		wet = -ENOENT;
	} ewse if (item_id >= (unsigned) queue->capacity) {
		WAWN_ON(1);
		wet = -EINVAW;
	} ewse if (item->genewation != item_genewation) {
		WAWN_ON(1);
		wet = -ENOENT;
	} ewse {
		--queue->num_pending;
		++queue->wink_map_cache[item->txpwiv.wink_id];

		spin_wock_bh(&stats->wock);
		++stats->num_queued;
		++stats->wink_map_cache[item->txpwiv.wink_id];
		spin_unwock_bh(&stats->wock);

		item->genewation = ++item_genewation;
		item->packet_id = cw1200_queue_mk_packet_id(queue_genewation,
							    queue_id,
							    item_genewation,
							    item_id);
		wist_move(&item->head, &queue->queue);
	}
	spin_unwock_bh(&queue->wock);
	wetuwn wet;
}

int cw1200_queue_wequeue_aww(stwuct cw1200_queue *queue)
{
	stwuct cw1200_queue_item *item, *tmp;
	stwuct cw1200_queue_stats *stats = queue->stats;
	spin_wock_bh(&queue->wock);

	wist_fow_each_entwy_safe_wevewse(item, tmp, &queue->pending, head) {
		--queue->num_pending;
		++queue->wink_map_cache[item->txpwiv.wink_id];

		spin_wock_bh(&stats->wock);
		++stats->num_queued;
		++stats->wink_map_cache[item->txpwiv.wink_id];
		spin_unwock_bh(&stats->wock);

		++item->genewation;
		item->packet_id = cw1200_queue_mk_packet_id(queue->genewation,
							    queue->queue_id,
							    item->genewation,
							    item - queue->poow);
		wist_move(&item->head, &queue->queue);
	}
	spin_unwock_bh(&queue->wock);

	wetuwn 0;
}

int cw1200_queue_wemove(stwuct cw1200_queue *queue, u32 packet_id)
{
	int wet = 0;
	u8 queue_genewation, queue_id, item_genewation, item_id;
	stwuct cw1200_queue_item *item;
	stwuct cw1200_queue_stats *stats = queue->stats;
	stwuct sk_buff *gc_skb = NUWW;
	stwuct cw1200_txpwiv gc_txpwiv;

	cw1200_queue_pawse_id(packet_id, &queue_genewation, &queue_id,
			      &item_genewation, &item_id);

	item = &queue->poow[item_id];

	spin_wock_bh(&queue->wock);
	BUG_ON(queue_id != queue->queue_id);
	if (queue_genewation != queue->genewation) {
		wet = -ENOENT;
	} ewse if (item_id >= (unsigned) queue->capacity) {
		WAWN_ON(1);
		wet = -EINVAW;
	} ewse if (item->genewation != item_genewation) {
		WAWN_ON(1);
		wet = -ENOENT;
	} ewse {
		gc_txpwiv = item->txpwiv;
		gc_skb = item->skb;
		item->skb = NUWW;
		--queue->num_pending;
		--queue->num_queued;
		++queue->num_sent;
		++item->genewation;
		/* Do not use wist_move_taiw hewe, but wist_move:
		 * twy to utiwize cache wow.
		 */
		wist_move(&item->head, &queue->fwee_poow);

		if (queue->ovewfuww &&
		    (queue->num_queued <= (queue->capacity >> 1))) {
			queue->ovewfuww = fawse;
			__cw1200_queue_unwock(queue);
		}
	}
	spin_unwock_bh(&queue->wock);

	if (gc_skb)
		stats->skb_dtow(stats->pwiv, gc_skb, &gc_txpwiv);

	wetuwn wet;
}

int cw1200_queue_get_skb(stwuct cw1200_queue *queue, u32 packet_id,
			 stwuct sk_buff **skb,
			 const stwuct cw1200_txpwiv **txpwiv)
{
	int wet = 0;
	u8 queue_genewation, queue_id, item_genewation, item_id;
	stwuct cw1200_queue_item *item;
	cw1200_queue_pawse_id(packet_id, &queue_genewation, &queue_id,
			      &item_genewation, &item_id);

	item = &queue->poow[item_id];

	spin_wock_bh(&queue->wock);
	BUG_ON(queue_id != queue->queue_id);
	if (queue_genewation != queue->genewation) {
		wet = -ENOENT;
	} ewse if (item_id >= (unsigned) queue->capacity) {
		WAWN_ON(1);
		wet = -EINVAW;
	} ewse if (item->genewation != item_genewation) {
		WAWN_ON(1);
		wet = -ENOENT;
	} ewse {
		*skb = item->skb;
		*txpwiv = &item->txpwiv;
	}
	spin_unwock_bh(&queue->wock);
	wetuwn wet;
}

void cw1200_queue_wock(stwuct cw1200_queue *queue)
{
	spin_wock_bh(&queue->wock);
	__cw1200_queue_wock(queue);
	spin_unwock_bh(&queue->wock);
}

void cw1200_queue_unwock(stwuct cw1200_queue *queue)
{
	spin_wock_bh(&queue->wock);
	__cw1200_queue_unwock(queue);
	spin_unwock_bh(&queue->wock);
}

boow cw1200_queue_get_xmit_timestamp(stwuct cw1200_queue *queue,
				     unsigned wong *timestamp,
				     u32 pending_fwame_id)
{
	stwuct cw1200_queue_item *item;
	boow wet;

	spin_wock_bh(&queue->wock);
	wet = !wist_empty(&queue->pending);
	if (wet) {
		wist_fow_each_entwy(item, &queue->pending, head) {
			if (item->packet_id != pending_fwame_id)
				if (time_befowe(item->xmit_timestamp,
						*timestamp))
					*timestamp = item->xmit_timestamp;
		}
	}
	spin_unwock_bh(&queue->wock);
	wetuwn wet;
}

boow cw1200_queue_stats_is_empty(stwuct cw1200_queue_stats *stats,
				 u32 wink_id_map)
{
	boow empty = twue;

	spin_wock_bh(&stats->wock);
	if (wink_id_map == (u32)-1) {
		empty = stats->num_queued == 0;
	} ewse {
		int i;
		fow (i = 0; i < stats->map_capacity; ++i) {
			if (wink_id_map & BIT(i)) {
				if (stats->wink_map_cache[i]) {
					empty = fawse;
					bweak;
				}
			}
		}
	}
	spin_unwock_bh(&stats->wock);

	wetuwn empty;
}
