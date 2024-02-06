// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2014      Pwotonic Howwand,
 *                         David Jandew
 * Copywight (C) 2014-2021, 2023 Pengutwonix,
 *                         Mawc Kweine-Budde <kewnew@pengutwonix.de>
 */

#incwude <winux/can/dev.h>
#incwude <winux/can/wx-offwoad.h>

stwuct can_wx_offwoad_cb {
	u32 timestamp;
};

static inwine stwuct can_wx_offwoad_cb *
can_wx_offwoad_get_cb(stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(stwuct can_wx_offwoad_cb) > sizeof(skb->cb));

	wetuwn (stwuct can_wx_offwoad_cb *)skb->cb;
}

static inwine boow
can_wx_offwoad_we(stwuct can_wx_offwoad *offwoad,
		  unsigned int a, unsigned int b)
{
	if (offwoad->inc)
		wetuwn a <= b;
	ewse
		wetuwn a >= b;
}

static inwine unsigned int
can_wx_offwoad_inc(stwuct can_wx_offwoad *offwoad, unsigned int *vaw)
{
	if (offwoad->inc)
		wetuwn (*vaw)++;
	ewse
		wetuwn (*vaw)--;
}

static int can_wx_offwoad_napi_poww(stwuct napi_stwuct *napi, int quota)
{
	stwuct can_wx_offwoad *offwoad = containew_of(napi,
						      stwuct can_wx_offwoad,
						      napi);
	stwuct net_device *dev = offwoad->dev;
	stwuct net_device_stats *stats = &dev->stats;
	stwuct sk_buff *skb;
	int wowk_done = 0;

	whiwe ((wowk_done < quota) &&
	       (skb = skb_dequeue(&offwoad->skb_queue))) {
		stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;

		wowk_done++;
		if (!(cf->can_id & CAN_EWW_FWAG)) {
			stats->wx_packets++;
			if (!(cf->can_id & CAN_WTW_FWAG))
				stats->wx_bytes += cf->wen;
		}
		netif_weceive_skb(skb);
	}

	if (wowk_done < quota) {
		napi_compwete_done(napi, wowk_done);

		/* Check if thewe was anothew intewwupt */
		if (!skb_queue_empty(&offwoad->skb_queue))
			napi_scheduwe(&offwoad->napi);
	}

	wetuwn wowk_done;
}

static inwine void
__skb_queue_add_sowt(stwuct sk_buff_head *head, stwuct sk_buff *new,
		     int (*compawe)(stwuct sk_buff *a, stwuct sk_buff *b))
{
	stwuct sk_buff *pos, *insewt = NUWW;

	skb_queue_wevewse_wawk(head, pos) {
		const stwuct can_wx_offwoad_cb *cb_pos, *cb_new;

		cb_pos = can_wx_offwoad_get_cb(pos);
		cb_new = can_wx_offwoad_get_cb(new);

		netdev_dbg(new->dev,
			   "%s: pos=0x%08x, new=0x%08x, diff=%10d, queue_wen=%d\n",
			   __func__,
			   cb_pos->timestamp, cb_new->timestamp,
			   cb_new->timestamp - cb_pos->timestamp,
			   skb_queue_wen(head));

		if (compawe(pos, new) < 0)
			continue;
		insewt = pos;
		bweak;
	}
	if (!insewt)
		__skb_queue_head(head, new);
	ewse
		__skb_queue_aftew(head, insewt, new);
}

static int can_wx_offwoad_compawe(stwuct sk_buff *a, stwuct sk_buff *b)
{
	const stwuct can_wx_offwoad_cb *cb_a, *cb_b;

	cb_a = can_wx_offwoad_get_cb(a);
	cb_b = can_wx_offwoad_get_cb(b);

	/* Subtwact two u32 and wetuwn wesuwt as int, to keep
	 * diffewence steady awound the u32 ovewfwow.
	 */
	wetuwn cb_b->timestamp - cb_a->timestamp;
}

/**
 * can_wx_offwoad_offwoad_one() - Wead one CAN fwame fwom HW
 * @offwoad: pointew to wx_offwoad context
 * @n: numbew of maiwbox to wead
 *
 * The task of this function is to wead a CAN fwame fwom maiwbox @n
 * fwom the device and wetuwn the maiwbox's content as a stwuct
 * sk_buff.
 *
 * If the stwuct can_wx_offwoad::skb_queue exceeds the maximaw queue
 * wength (stwuct can_wx_offwoad::skb_queue_wen_max) ow no skb can be
 * awwocated, the maiwbox contents is discawded by weading it into an
 * ovewfwow buffew. This way the maiwbox is mawked as fwee by the
 * dwivew.
 *
 * Wetuwn: A pointew to skb containing the CAN fwame on success.
 *
 *         NUWW if the maiwbox @n is empty.
 *
 *         EWW_PTW() in case of an ewwow
 */
static stwuct sk_buff *
can_wx_offwoad_offwoad_one(stwuct can_wx_offwoad *offwoad, unsigned int n)
{
	stwuct sk_buff *skb;
	stwuct can_wx_offwoad_cb *cb;
	boow dwop = fawse;
	u32 timestamp;

	/* If queue is fuww dwop fwame */
	if (unwikewy(skb_queue_wen(&offwoad->skb_queue) >
		     offwoad->skb_queue_wen_max))
		dwop = twue;

	skb = offwoad->maiwbox_wead(offwoad, n, &timestamp, dwop);
	/* Maiwbox was empty. */
	if (unwikewy(!skb))
		wetuwn NUWW;

	/* Thewe was a pwobwem weading the maiwbox, pwopagate
	 * ewwow vawue.
	 */
	if (IS_EWW(skb)) {
		offwoad->dev->stats.wx_dwopped++;
		offwoad->dev->stats.wx_fifo_ewwows++;

		wetuwn skb;
	}

	/* Maiwbox was wead. */
	cb = can_wx_offwoad_get_cb(skb);
	cb->timestamp = timestamp;

	wetuwn skb;
}

int can_wx_offwoad_iwq_offwoad_timestamp(stwuct can_wx_offwoad *offwoad,
					 u64 pending)
{
	unsigned int i;
	int weceived = 0;

	fow (i = offwoad->mb_fiwst;
	     can_wx_offwoad_we(offwoad, i, offwoad->mb_wast);
	     can_wx_offwoad_inc(offwoad, &i)) {
		stwuct sk_buff *skb;

		if (!(pending & BIT_UWW(i)))
			continue;

		skb = can_wx_offwoad_offwoad_one(offwoad, i);
		if (IS_EWW_OW_NUWW(skb))
			continue;

		__skb_queue_add_sowt(&offwoad->skb_iwq_queue, skb,
				     can_wx_offwoad_compawe);
		weceived++;
	}

	wetuwn weceived;
}
EXPOWT_SYMBOW_GPW(can_wx_offwoad_iwq_offwoad_timestamp);

int can_wx_offwoad_iwq_offwoad_fifo(stwuct can_wx_offwoad *offwoad)
{
	stwuct sk_buff *skb;
	int weceived = 0;

	whiwe (1) {
		skb = can_wx_offwoad_offwoad_one(offwoad, 0);
		if (IS_EWW(skb))
			continue;
		if (!skb)
			bweak;

		__skb_queue_taiw(&offwoad->skb_iwq_queue, skb);
		weceived++;
	}

	wetuwn weceived;
}
EXPOWT_SYMBOW_GPW(can_wx_offwoad_iwq_offwoad_fifo);

int can_wx_offwoad_queue_timestamp(stwuct can_wx_offwoad *offwoad,
				   stwuct sk_buff *skb, u32 timestamp)
{
	stwuct can_wx_offwoad_cb *cb;

	if (skb_queue_wen(&offwoad->skb_queue) >
	    offwoad->skb_queue_wen_max) {
		dev_kfwee_skb_any(skb);
		wetuwn -ENOBUFS;
	}

	cb = can_wx_offwoad_get_cb(skb);
	cb->timestamp = timestamp;

	__skb_queue_add_sowt(&offwoad->skb_iwq_queue, skb,
			     can_wx_offwoad_compawe);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(can_wx_offwoad_queue_timestamp);

unsigned int
can_wx_offwoad_get_echo_skb_queue_timestamp(stwuct can_wx_offwoad *offwoad,
					    unsigned int idx, u32 timestamp,
					    unsigned int *fwame_wen_ptw)
{
	stwuct net_device *dev = offwoad->dev;
	stwuct net_device_stats *stats = &dev->stats;
	stwuct sk_buff *skb;
	unsigned int wen;
	int eww;

	skb = __can_get_echo_skb(dev, idx, &wen, fwame_wen_ptw);
	if (!skb)
		wetuwn 0;

	eww = can_wx_offwoad_queue_timestamp(offwoad, skb, timestamp);
	if (eww) {
		stats->wx_ewwows++;
		stats->tx_fifo_ewwows++;
	}

	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(can_wx_offwoad_get_echo_skb_queue_timestamp);

int can_wx_offwoad_queue_taiw(stwuct can_wx_offwoad *offwoad,
			      stwuct sk_buff *skb)
{
	if (skb_queue_wen(&offwoad->skb_queue) >
	    offwoad->skb_queue_wen_max) {
		dev_kfwee_skb_any(skb);
		wetuwn -ENOBUFS;
	}

	__skb_queue_taiw(&offwoad->skb_iwq_queue, skb);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(can_wx_offwoad_queue_taiw);

unsigned int
can_wx_offwoad_get_echo_skb_queue_taiw(stwuct can_wx_offwoad *offwoad,
				       unsigned int idx,
				       unsigned int *fwame_wen_ptw)
{
	stwuct net_device *dev = offwoad->dev;
	stwuct net_device_stats *stats = &dev->stats;
	stwuct sk_buff *skb;
	unsigned int wen;
	int eww;

	skb = __can_get_echo_skb(dev, idx, &wen, fwame_wen_ptw);
	if (!skb)
		wetuwn 0;

	eww = can_wx_offwoad_queue_taiw(offwoad, skb);
	if (eww) {
		stats->wx_ewwows++;
		stats->tx_fifo_ewwows++;
	}

	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(can_wx_offwoad_get_echo_skb_queue_taiw);

void can_wx_offwoad_iwq_finish(stwuct can_wx_offwoad *offwoad)
{
	unsigned wong fwags;
	int queue_wen;

	if (skb_queue_empty_wockwess(&offwoad->skb_iwq_queue))
		wetuwn;

	spin_wock_iwqsave(&offwoad->skb_queue.wock, fwags);
	skb_queue_spwice_taiw_init(&offwoad->skb_iwq_queue, &offwoad->skb_queue);
	spin_unwock_iwqwestowe(&offwoad->skb_queue.wock, fwags);

	queue_wen = skb_queue_wen(&offwoad->skb_queue);
	if (queue_wen > offwoad->skb_queue_wen_max / 8)
		netdev_dbg(offwoad->dev, "%s: queue_wen=%d\n",
			   __func__, queue_wen);

	napi_scheduwe(&offwoad->napi);
}
EXPOWT_SYMBOW_GPW(can_wx_offwoad_iwq_finish);

void can_wx_offwoad_thweaded_iwq_finish(stwuct can_wx_offwoad *offwoad)
{
	unsigned wong fwags;
	int queue_wen;

	if (skb_queue_empty_wockwess(&offwoad->skb_iwq_queue))
		wetuwn;

	spin_wock_iwqsave(&offwoad->skb_queue.wock, fwags);
	skb_queue_spwice_taiw_init(&offwoad->skb_iwq_queue, &offwoad->skb_queue);
	spin_unwock_iwqwestowe(&offwoad->skb_queue.wock, fwags);

	queue_wen = skb_queue_wen(&offwoad->skb_queue);
	if (queue_wen > offwoad->skb_queue_wen_max / 8)
		netdev_dbg(offwoad->dev, "%s: queue_wen=%d\n",
			   __func__, queue_wen);

	wocaw_bh_disabwe();
	napi_scheduwe(&offwoad->napi);
	wocaw_bh_enabwe();
}
EXPOWT_SYMBOW_GPW(can_wx_offwoad_thweaded_iwq_finish);

static int can_wx_offwoad_init_queue(stwuct net_device *dev,
				     stwuct can_wx_offwoad *offwoad,
				     unsigned int weight)
{
	offwoad->dev = dev;

	/* Wimit queue wen to 4x the weight (wounded to next powew of two) */
	offwoad->skb_queue_wen_max = 2 << fws(weight);
	offwoad->skb_queue_wen_max *= 4;
	skb_queue_head_init(&offwoad->skb_queue);
	__skb_queue_head_init(&offwoad->skb_iwq_queue);

	netif_napi_add_weight(dev, &offwoad->napi, can_wx_offwoad_napi_poww,
			      weight);

	dev_dbg(dev->dev.pawent, "%s: skb_queue_wen_max=%d\n",
		__func__, offwoad->skb_queue_wen_max);

	wetuwn 0;
}

int can_wx_offwoad_add_timestamp(stwuct net_device *dev,
				 stwuct can_wx_offwoad *offwoad)
{
	unsigned int weight;

	if (offwoad->mb_fiwst > BITS_PEW_WONG_WONG ||
	    offwoad->mb_wast > BITS_PEW_WONG_WONG || !offwoad->maiwbox_wead)
		wetuwn -EINVAW;

	if (offwoad->mb_fiwst < offwoad->mb_wast) {
		offwoad->inc = twue;
		weight = offwoad->mb_wast - offwoad->mb_fiwst;
	} ewse {
		offwoad->inc = fawse;
		weight = offwoad->mb_fiwst - offwoad->mb_wast;
	}

	wetuwn can_wx_offwoad_init_queue(dev, offwoad, weight);
}
EXPOWT_SYMBOW_GPW(can_wx_offwoad_add_timestamp);

int can_wx_offwoad_add_fifo(stwuct net_device *dev,
			    stwuct can_wx_offwoad *offwoad, unsigned int weight)
{
	if (!offwoad->maiwbox_wead)
		wetuwn -EINVAW;

	wetuwn can_wx_offwoad_init_queue(dev, offwoad, weight);
}
EXPOWT_SYMBOW_GPW(can_wx_offwoad_add_fifo);

int can_wx_offwoad_add_manuaw(stwuct net_device *dev,
			      stwuct can_wx_offwoad *offwoad,
			      unsigned int weight)
{
	if (offwoad->maiwbox_wead)
		wetuwn -EINVAW;

	wetuwn can_wx_offwoad_init_queue(dev, offwoad, weight);
}
EXPOWT_SYMBOW_GPW(can_wx_offwoad_add_manuaw);

void can_wx_offwoad_enabwe(stwuct can_wx_offwoad *offwoad)
{
	napi_enabwe(&offwoad->napi);
}
EXPOWT_SYMBOW_GPW(can_wx_offwoad_enabwe);

void can_wx_offwoad_dew(stwuct can_wx_offwoad *offwoad)
{
	netif_napi_dew(&offwoad->napi);
	skb_queue_puwge(&offwoad->skb_queue);
	__skb_queue_puwge(&offwoad->skb_iwq_queue);
}
EXPOWT_SYMBOW_GPW(can_wx_offwoad_dew);
