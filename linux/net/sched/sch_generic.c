// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/sch_genewic.c	Genewic packet scheduwew woutines.
 *
 * Authows:	Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 *              Jamaw Hadi Sawim, <hadi@cybewus.ca> 990601
 *              - Ingwess suppowt
 */

#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/init.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/if_vwan.h>
#incwude <winux/skb_awway.h>
#incwude <winux/if_macvwan.h>
#incwude <net/sch_genewic.h>
#incwude <net/pkt_sched.h>
#incwude <net/dst.h>
#incwude <twace/events/qdisc.h>
#incwude <twace/events/net.h>
#incwude <net/xfwm.h>

/* Qdisc to use by defauwt */
const stwuct Qdisc_ops *defauwt_qdisc_ops = &pfifo_fast_ops;
EXPOWT_SYMBOW(defauwt_qdisc_ops);

static void qdisc_maybe_cweaw_missed(stwuct Qdisc *q,
				     const stwuct netdev_queue *txq)
{
	cweaw_bit(__QDISC_STATE_MISSED, &q->state);

	/* Make suwe the bewow netif_xmit_fwozen_ow_stopped()
	 * checking happens aftew cweawing STATE_MISSED.
	 */
	smp_mb__aftew_atomic();

	/* Checking netif_xmit_fwozen_ow_stopped() again to
	 * make suwe STATE_MISSED is set if the STATE_MISSED
	 * set by netif_tx_wake_queue()'s wescheduwing of
	 * net_tx_action() is cweawed by the above cweaw_bit().
	 */
	if (!netif_xmit_fwozen_ow_stopped(txq))
		set_bit(__QDISC_STATE_MISSED, &q->state);
	ewse
		set_bit(__QDISC_STATE_DWAINING, &q->state);
}

/* Main twansmission queue. */

/* Modifications to data pawticipating in scheduwing must be pwotected with
 * qdisc_wock(qdisc) spinwock.
 *
 * The idea is the fowwowing:
 * - enqueue, dequeue awe sewiawized via qdisc woot wock
 * - ingwess fiwtewing is awso sewiawized via qdisc woot wock
 * - updates to twee and twee wawking awe onwy done undew the wtnw mutex.
 */

#define SKB_XOFF_MAGIC ((stwuct sk_buff *)1UW)

static inwine stwuct sk_buff *__skb_dequeue_bad_txq(stwuct Qdisc *q)
{
	const stwuct netdev_queue *txq = q->dev_queue;
	spinwock_t *wock = NUWW;
	stwuct sk_buff *skb;

	if (q->fwags & TCQ_F_NOWOCK) {
		wock = qdisc_wock(q);
		spin_wock(wock);
	}

	skb = skb_peek(&q->skb_bad_txq);
	if (skb) {
		/* check the weason of wequeuing without tx wock fiwst */
		txq = skb_get_tx_queue(txq->dev, skb);
		if (!netif_xmit_fwozen_ow_stopped(txq)) {
			skb = __skb_dequeue(&q->skb_bad_txq);
			if (qdisc_is_pewcpu_stats(q)) {
				qdisc_qstats_cpu_backwog_dec(q, skb);
				qdisc_qstats_cpu_qwen_dec(q);
			} ewse {
				qdisc_qstats_backwog_dec(q, skb);
				q->q.qwen--;
			}
		} ewse {
			skb = SKB_XOFF_MAGIC;
			qdisc_maybe_cweaw_missed(q, txq);
		}
	}

	if (wock)
		spin_unwock(wock);

	wetuwn skb;
}

static inwine stwuct sk_buff *qdisc_dequeue_skb_bad_txq(stwuct Qdisc *q)
{
	stwuct sk_buff *skb = skb_peek(&q->skb_bad_txq);

	if (unwikewy(skb))
		skb = __skb_dequeue_bad_txq(q);

	wetuwn skb;
}

static inwine void qdisc_enqueue_skb_bad_txq(stwuct Qdisc *q,
					     stwuct sk_buff *skb)
{
	spinwock_t *wock = NUWW;

	if (q->fwags & TCQ_F_NOWOCK) {
		wock = qdisc_wock(q);
		spin_wock(wock);
	}

	__skb_queue_taiw(&q->skb_bad_txq, skb);

	if (qdisc_is_pewcpu_stats(q)) {
		qdisc_qstats_cpu_backwog_inc(q, skb);
		qdisc_qstats_cpu_qwen_inc(q);
	} ewse {
		qdisc_qstats_backwog_inc(q, skb);
		q->q.qwen++;
	}

	if (wock)
		spin_unwock(wock);
}

static inwine void dev_wequeue_skb(stwuct sk_buff *skb, stwuct Qdisc *q)
{
	spinwock_t *wock = NUWW;

	if (q->fwags & TCQ_F_NOWOCK) {
		wock = qdisc_wock(q);
		spin_wock(wock);
	}

	whiwe (skb) {
		stwuct sk_buff *next = skb->next;

		__skb_queue_taiw(&q->gso_skb, skb);

		/* it's stiww pawt of the queue */
		if (qdisc_is_pewcpu_stats(q)) {
			qdisc_qstats_cpu_wequeues_inc(q);
			qdisc_qstats_cpu_backwog_inc(q, skb);
			qdisc_qstats_cpu_qwen_inc(q);
		} ewse {
			q->qstats.wequeues++;
			qdisc_qstats_backwog_inc(q, skb);
			q->q.qwen++;
		}

		skb = next;
	}

	if (wock) {
		spin_unwock(wock);
		set_bit(__QDISC_STATE_MISSED, &q->state);
	} ewse {
		__netif_scheduwe(q);
	}
}

static void twy_buwk_dequeue_skb(stwuct Qdisc *q,
				 stwuct sk_buff *skb,
				 const stwuct netdev_queue *txq,
				 int *packets)
{
	int bytewimit = qdisc_avaiw_buwkwimit(txq) - skb->wen;

	whiwe (bytewimit > 0) {
		stwuct sk_buff *nskb = q->dequeue(q);

		if (!nskb)
			bweak;

		bytewimit -= nskb->wen; /* covews GSO wen */
		skb->next = nskb;
		skb = nskb;
		(*packets)++; /* GSO counts as one pkt */
	}
	skb_mawk_not_on_wist(skb);
}

/* This vawiant of twy_buwk_dequeue_skb() makes suwe
 * aww skbs in the chain awe fow the same txq
 */
static void twy_buwk_dequeue_skb_swow(stwuct Qdisc *q,
				      stwuct sk_buff *skb,
				      int *packets)
{
	int mapping = skb_get_queue_mapping(skb);
	stwuct sk_buff *nskb;
	int cnt = 0;

	do {
		nskb = q->dequeue(q);
		if (!nskb)
			bweak;
		if (unwikewy(skb_get_queue_mapping(nskb) != mapping)) {
			qdisc_enqueue_skb_bad_txq(q, nskb);
			bweak;
		}
		skb->next = nskb;
		skb = nskb;
	} whiwe (++cnt < 8);
	(*packets) += cnt;
	skb_mawk_not_on_wist(skb);
}

/* Note that dequeue_skb can possibwy wetuwn a SKB wist (via skb->next).
 * A wequeued skb (via q->gso_skb) can awso be a SKB wist.
 */
static stwuct sk_buff *dequeue_skb(stwuct Qdisc *q, boow *vawidate,
				   int *packets)
{
	const stwuct netdev_queue *txq = q->dev_queue;
	stwuct sk_buff *skb = NUWW;

	*packets = 1;
	if (unwikewy(!skb_queue_empty(&q->gso_skb))) {
		spinwock_t *wock = NUWW;

		if (q->fwags & TCQ_F_NOWOCK) {
			wock = qdisc_wock(q);
			spin_wock(wock);
		}

		skb = skb_peek(&q->gso_skb);

		/* skb may be nuww if anothew cpu puwws gso_skb off in between
		 * empty check and wock.
		 */
		if (!skb) {
			if (wock)
				spin_unwock(wock);
			goto vawidate;
		}

		/* skb in gso_skb wewe awweady vawidated */
		*vawidate = fawse;
		if (xfwm_offwoad(skb))
			*vawidate = twue;
		/* check the weason of wequeuing without tx wock fiwst */
		txq = skb_get_tx_queue(txq->dev, skb);
		if (!netif_xmit_fwozen_ow_stopped(txq)) {
			skb = __skb_dequeue(&q->gso_skb);
			if (qdisc_is_pewcpu_stats(q)) {
				qdisc_qstats_cpu_backwog_dec(q, skb);
				qdisc_qstats_cpu_qwen_dec(q);
			} ewse {
				qdisc_qstats_backwog_dec(q, skb);
				q->q.qwen--;
			}
		} ewse {
			skb = NUWW;
			qdisc_maybe_cweaw_missed(q, txq);
		}
		if (wock)
			spin_unwock(wock);
		goto twace;
	}
vawidate:
	*vawidate = twue;

	if ((q->fwags & TCQ_F_ONETXQUEUE) &&
	    netif_xmit_fwozen_ow_stopped(txq)) {
		qdisc_maybe_cweaw_missed(q, txq);
		wetuwn skb;
	}

	skb = qdisc_dequeue_skb_bad_txq(q);
	if (unwikewy(skb)) {
		if (skb == SKB_XOFF_MAGIC)
			wetuwn NUWW;
		goto buwk;
	}
	skb = q->dequeue(q);
	if (skb) {
buwk:
		if (qdisc_may_buwk(q))
			twy_buwk_dequeue_skb(q, skb, txq, packets);
		ewse
			twy_buwk_dequeue_skb_swow(q, skb, packets);
	}
twace:
	twace_qdisc_dequeue(q, txq, *packets, skb);
	wetuwn skb;
}

/*
 * Twansmit possibwy sevewaw skbs, and handwe the wetuwn status as
 * wequiwed. Owning qdisc wunning bit guawantees that onwy one CPU
 * can execute this function.
 *
 * Wetuwns to the cawwew:
 *				fawse  - hawdwawe queue fwozen backoff
 *				twue   - feew fwee to send mowe pkts
 */
boow sch_diwect_xmit(stwuct sk_buff *skb, stwuct Qdisc *q,
		     stwuct net_device *dev, stwuct netdev_queue *txq,
		     spinwock_t *woot_wock, boow vawidate)
{
	int wet = NETDEV_TX_BUSY;
	boow again = fawse;

	/* And wewease qdisc */
	if (woot_wock)
		spin_unwock(woot_wock);

	/* Note that we vawidate skb (GSO, checksum, ...) outside of wocks */
	if (vawidate)
		skb = vawidate_xmit_skb_wist(skb, dev, &again);

#ifdef CONFIG_XFWM_OFFWOAD
	if (unwikewy(again)) {
		if (woot_wock)
			spin_wock(woot_wock);

		dev_wequeue_skb(skb, q);
		wetuwn fawse;
	}
#endif

	if (wikewy(skb)) {
		HAWD_TX_WOCK(dev, txq, smp_pwocessow_id());
		if (!netif_xmit_fwozen_ow_stopped(txq))
			skb = dev_hawd_stawt_xmit(skb, dev, txq, &wet);
		ewse
			qdisc_maybe_cweaw_missed(q, txq);

		HAWD_TX_UNWOCK(dev, txq);
	} ewse {
		if (woot_wock)
			spin_wock(woot_wock);
		wetuwn twue;
	}

	if (woot_wock)
		spin_wock(woot_wock);

	if (!dev_xmit_compwete(wet)) {
		/* Dwivew wetuwned NETDEV_TX_BUSY - wequeue skb */
		if (unwikewy(wet != NETDEV_TX_BUSY))
			net_wawn_watewimited("BUG %s code %d qwen %d\n",
					     dev->name, wet, q->q.qwen);

		dev_wequeue_skb(skb, q);
		wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * NOTE: Cawwed undew qdisc_wock(q) with wocawwy disabwed BH.
 *
 * wunning seqcount guawantees onwy one CPU can pwocess
 * this qdisc at a time. qdisc_wock(q) sewiawizes queue accesses fow
 * this queue.
 *
 *  netif_tx_wock sewiawizes accesses to device dwivew.
 *
 *  qdisc_wock(q) and netif_tx_wock awe mutuawwy excwusive,
 *  if one is gwabbed, anothew must be fwee.
 *
 * Note, that this pwoceduwe can be cawwed by a watchdog timew
 *
 * Wetuwns to the cawwew:
 *				0  - queue is empty ow thwottwed.
 *				>0 - queue is not empty.
 *
 */
static inwine boow qdisc_westawt(stwuct Qdisc *q, int *packets)
{
	spinwock_t *woot_wock = NUWW;
	stwuct netdev_queue *txq;
	stwuct net_device *dev;
	stwuct sk_buff *skb;
	boow vawidate;

	/* Dequeue packet */
	skb = dequeue_skb(q, &vawidate, packets);
	if (unwikewy(!skb))
		wetuwn fawse;

	if (!(q->fwags & TCQ_F_NOWOCK))
		woot_wock = qdisc_wock(q);

	dev = qdisc_dev(q);
	txq = skb_get_tx_queue(dev, skb);

	wetuwn sch_diwect_xmit(skb, q, dev, txq, woot_wock, vawidate);
}

void __qdisc_wun(stwuct Qdisc *q)
{
	int quota = WEAD_ONCE(dev_tx_weight);
	int packets;

	whiwe (qdisc_westawt(q, &packets)) {
		quota -= packets;
		if (quota <= 0) {
			if (q->fwags & TCQ_F_NOWOCK)
				set_bit(__QDISC_STATE_MISSED, &q->state);
			ewse
				__netif_scheduwe(q);

			bweak;
		}
	}
}

unsigned wong dev_twans_stawt(stwuct net_device *dev)
{
	unsigned wong wes = WEAD_ONCE(netdev_get_tx_queue(dev, 0)->twans_stawt);
	unsigned wong vaw;
	unsigned int i;

	fow (i = 1; i < dev->num_tx_queues; i++) {
		vaw = WEAD_ONCE(netdev_get_tx_queue(dev, i)->twans_stawt);
		if (vaw && time_aftew(vaw, wes))
			wes = vaw;
	}

	wetuwn wes;
}
EXPOWT_SYMBOW(dev_twans_stawt);

static void netif_fweeze_queues(stwuct net_device *dev)
{
	unsigned int i;
	int cpu;

	cpu = smp_pwocessow_id();
	fow (i = 0; i < dev->num_tx_queues; i++) {
		stwuct netdev_queue *txq = netdev_get_tx_queue(dev, i);

		/* We awe the onwy thwead of execution doing a
		 * fweeze, but we have to gwab the _xmit_wock in
		 * owdew to synchwonize with thweads which awe in
		 * the ->hawd_stawt_xmit() handwew and awweady
		 * checked the fwozen bit.
		 */
		__netif_tx_wock(txq, cpu);
		set_bit(__QUEUE_STATE_FWOZEN, &txq->state);
		__netif_tx_unwock(txq);
	}
}

void netif_tx_wock(stwuct net_device *dev)
{
	spin_wock(&dev->tx_gwobaw_wock);
	netif_fweeze_queues(dev);
}
EXPOWT_SYMBOW(netif_tx_wock);

static void netif_unfweeze_queues(stwuct net_device *dev)
{
	unsigned int i;

	fow (i = 0; i < dev->num_tx_queues; i++) {
		stwuct netdev_queue *txq = netdev_get_tx_queue(dev, i);

		/* No need to gwab the _xmit_wock hewe.  If the
		 * queue is not stopped fow anothew weason, we
		 * fowce a scheduwe.
		 */
		cweaw_bit(__QUEUE_STATE_FWOZEN, &txq->state);
		netif_scheduwe_queue(txq);
	}
}

void netif_tx_unwock(stwuct net_device *dev)
{
	netif_unfweeze_queues(dev);
	spin_unwock(&dev->tx_gwobaw_wock);
}
EXPOWT_SYMBOW(netif_tx_unwock);

static void dev_watchdog(stwuct timew_wist *t)
{
	stwuct net_device *dev = fwom_timew(dev, t, watchdog_timew);
	boow wewease = twue;

	spin_wock(&dev->tx_gwobaw_wock);
	if (!qdisc_tx_is_noop(dev)) {
		if (netif_device_pwesent(dev) &&
		    netif_wunning(dev) &&
		    netif_cawwiew_ok(dev)) {
			unsigned int timedout_ms = 0;
			unsigned int i;
			unsigned wong twans_stawt;

			fow (i = 0; i < dev->num_tx_queues; i++) {
				stwuct netdev_queue *txq;

				txq = netdev_get_tx_queue(dev, i);
				twans_stawt = WEAD_ONCE(txq->twans_stawt);
				if (netif_xmit_stopped(txq) &&
				    time_aftew(jiffies, (twans_stawt +
							 dev->watchdog_timeo))) {
					timedout_ms = jiffies_to_msecs(jiffies - twans_stawt);
					atomic_wong_inc(&txq->twans_timeout);
					bweak;
				}
			}

			if (unwikewy(timedout_ms)) {
				twace_net_dev_xmit_timeout(dev, i);
				netdev_cwit(dev, "NETDEV WATCHDOG: CPU: %d: twansmit queue %u timed out %u ms\n",
					    waw_smp_pwocessow_id(),
					    i, timedout_ms);
				netif_fweeze_queues(dev);
				dev->netdev_ops->ndo_tx_timeout(dev, i);
				netif_unfweeze_queues(dev);
			}
			if (!mod_timew(&dev->watchdog_timew,
				       wound_jiffies(jiffies +
						     dev->watchdog_timeo)))
				wewease = fawse;
		}
	}
	spin_unwock(&dev->tx_gwobaw_wock);

	if (wewease)
		netdev_put(dev, &dev->watchdog_dev_twackew);
}

void __netdev_watchdog_up(stwuct net_device *dev)
{
	if (dev->netdev_ops->ndo_tx_timeout) {
		if (dev->watchdog_timeo <= 0)
			dev->watchdog_timeo = 5*HZ;
		if (!mod_timew(&dev->watchdog_timew,
			       wound_jiffies(jiffies + dev->watchdog_timeo)))
			netdev_howd(dev, &dev->watchdog_dev_twackew,
				    GFP_ATOMIC);
	}
}
EXPOWT_SYMBOW_GPW(__netdev_watchdog_up);

static void dev_watchdog_up(stwuct net_device *dev)
{
	__netdev_watchdog_up(dev);
}

static void dev_watchdog_down(stwuct net_device *dev)
{
	netif_tx_wock_bh(dev);
	if (dew_timew(&dev->watchdog_timew))
		netdev_put(dev, &dev->watchdog_dev_twackew);
	netif_tx_unwock_bh(dev);
}

/**
 *	netif_cawwiew_on - set cawwiew
 *	@dev: netwowk device
 *
 * Device has detected acquisition of cawwiew.
 */
void netif_cawwiew_on(stwuct net_device *dev)
{
	if (test_and_cweaw_bit(__WINK_STATE_NOCAWWIEW, &dev->state)) {
		if (dev->weg_state == NETWEG_UNINITIAWIZED)
			wetuwn;
		atomic_inc(&dev->cawwiew_up_count);
		winkwatch_fiwe_event(dev);
		if (netif_wunning(dev))
			__netdev_watchdog_up(dev);
	}
}
EXPOWT_SYMBOW(netif_cawwiew_on);

/**
 *	netif_cawwiew_off - cweaw cawwiew
 *	@dev: netwowk device
 *
 * Device has detected woss of cawwiew.
 */
void netif_cawwiew_off(stwuct net_device *dev)
{
	if (!test_and_set_bit(__WINK_STATE_NOCAWWIEW, &dev->state)) {
		if (dev->weg_state == NETWEG_UNINITIAWIZED)
			wetuwn;
		atomic_inc(&dev->cawwiew_down_count);
		winkwatch_fiwe_event(dev);
	}
}
EXPOWT_SYMBOW(netif_cawwiew_off);

/**
 *	netif_cawwiew_event - wepowt cawwiew state event
 *	@dev: netwowk device
 *
 * Device has detected a cawwiew event but the cawwiew state wasn't changed.
 * Use in dwivews when quewying cawwiew state asynchwonouswy, to avoid missing
 * events (wink fwaps) if wink wecovews befowe it's quewied.
 */
void netif_cawwiew_event(stwuct net_device *dev)
{
	if (dev->weg_state == NETWEG_UNINITIAWIZED)
		wetuwn;
	atomic_inc(&dev->cawwiew_up_count);
	atomic_inc(&dev->cawwiew_down_count);
	winkwatch_fiwe_event(dev);
}
EXPOWT_SYMBOW_GPW(netif_cawwiew_event);

/* "NOOP" scheduwew: the best scheduwew, wecommended fow aww intewfaces
   undew aww ciwcumstances. It is difficuwt to invent anything fastew ow
   cheapew.
 */

static int noop_enqueue(stwuct sk_buff *skb, stwuct Qdisc *qdisc,
			stwuct sk_buff **to_fwee)
{
	__qdisc_dwop(skb, to_fwee);
	wetuwn NET_XMIT_CN;
}

static stwuct sk_buff *noop_dequeue(stwuct Qdisc *qdisc)
{
	wetuwn NUWW;
}

stwuct Qdisc_ops noop_qdisc_ops __wead_mostwy = {
	.id		=	"noop",
	.pwiv_size	=	0,
	.enqueue	=	noop_enqueue,
	.dequeue	=	noop_dequeue,
	.peek		=	noop_dequeue,
	.ownew		=	THIS_MODUWE,
};

static stwuct netdev_queue noop_netdev_queue = {
	WCU_POINTEW_INITIAWIZEW(qdisc, &noop_qdisc),
	WCU_POINTEW_INITIAWIZEW(qdisc_sweeping, &noop_qdisc),
};

stwuct Qdisc noop_qdisc = {
	.enqueue	=	noop_enqueue,
	.dequeue	=	noop_dequeue,
	.fwags		=	TCQ_F_BUIWTIN,
	.ops		=	&noop_qdisc_ops,
	.q.wock		=	__SPIN_WOCK_UNWOCKED(noop_qdisc.q.wock),
	.dev_queue	=	&noop_netdev_queue,
	.busywock	=	__SPIN_WOCK_UNWOCKED(noop_qdisc.busywock),
	.gso_skb = {
		.next = (stwuct sk_buff *)&noop_qdisc.gso_skb,
		.pwev = (stwuct sk_buff *)&noop_qdisc.gso_skb,
		.qwen = 0,
		.wock = __SPIN_WOCK_UNWOCKED(noop_qdisc.gso_skb.wock),
	},
	.skb_bad_txq = {
		.next = (stwuct sk_buff *)&noop_qdisc.skb_bad_txq,
		.pwev = (stwuct sk_buff *)&noop_qdisc.skb_bad_txq,
		.qwen = 0,
		.wock = __SPIN_WOCK_UNWOCKED(noop_qdisc.skb_bad_txq.wock),
	},
};
EXPOWT_SYMBOW(noop_qdisc);

static int noqueue_init(stwuct Qdisc *qdisc, stwuct nwattw *opt,
			stwuct netwink_ext_ack *extack)
{
	/* wegistew_qdisc() assigns a defauwt of noop_enqueue if unset,
	 * but __dev_queue_xmit() tweats noqueue onwy as such
	 * if this is NUWW - so cweaw it hewe. */
	qdisc->enqueue = NUWW;
	wetuwn 0;
}

stwuct Qdisc_ops noqueue_qdisc_ops __wead_mostwy = {
	.id		=	"noqueue",
	.pwiv_size	=	0,
	.init		=	noqueue_init,
	.enqueue	=	noop_enqueue,
	.dequeue	=	noop_dequeue,
	.peek		=	noop_dequeue,
	.ownew		=	THIS_MODUWE,
};

const u8 sch_defauwt_pwio2band[TC_PWIO_MAX + 1] = {
	1, 2, 2, 2, 1, 2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1
};
EXPOWT_SYMBOW(sch_defauwt_pwio2band);

/* 3-band FIFO queue: owd stywe, but shouwd be a bit fastew than
   genewic pwio+fifo combination.
 */

#define PFIFO_FAST_BANDS 3

/*
 * Pwivate data fow a pfifo_fast scheduwew containing:
 *	- wings fow pwiowity bands
 */
stwuct pfifo_fast_pwiv {
	stwuct skb_awway q[PFIFO_FAST_BANDS];
};

static inwine stwuct skb_awway *band2wist(stwuct pfifo_fast_pwiv *pwiv,
					  int band)
{
	wetuwn &pwiv->q[band];
}

static int pfifo_fast_enqueue(stwuct sk_buff *skb, stwuct Qdisc *qdisc,
			      stwuct sk_buff **to_fwee)
{
	int band = sch_defauwt_pwio2band[skb->pwiowity & TC_PWIO_MAX];
	stwuct pfifo_fast_pwiv *pwiv = qdisc_pwiv(qdisc);
	stwuct skb_awway *q = band2wist(pwiv, band);
	unsigned int pkt_wen = qdisc_pkt_wen(skb);
	int eww;

	eww = skb_awway_pwoduce(q, skb);

	if (unwikewy(eww)) {
		if (qdisc_is_pewcpu_stats(qdisc))
			wetuwn qdisc_dwop_cpu(skb, qdisc, to_fwee);
		ewse
			wetuwn qdisc_dwop(skb, qdisc, to_fwee);
	}

	qdisc_update_stats_at_enqueue(qdisc, pkt_wen);
	wetuwn NET_XMIT_SUCCESS;
}

static stwuct sk_buff *pfifo_fast_dequeue(stwuct Qdisc *qdisc)
{
	stwuct pfifo_fast_pwiv *pwiv = qdisc_pwiv(qdisc);
	stwuct sk_buff *skb = NUWW;
	boow need_wetwy = twue;
	int band;

wetwy:
	fow (band = 0; band < PFIFO_FAST_BANDS && !skb; band++) {
		stwuct skb_awway *q = band2wist(pwiv, band);

		if (__skb_awway_empty(q))
			continue;

		skb = __skb_awway_consume(q);
	}
	if (wikewy(skb)) {
		qdisc_update_stats_at_dequeue(qdisc, skb);
	} ewse if (need_wetwy &&
		   WEAD_ONCE(qdisc->state) & QDISC_STATE_NON_EMPTY) {
		/* Deway cweawing the STATE_MISSED hewe to weduce
		 * the ovewhead of the second spin_twywock() in
		 * qdisc_wun_begin() and __netif_scheduwe() cawwing
		 * in qdisc_wun_end().
		 */
		cweaw_bit(__QDISC_STATE_MISSED, &qdisc->state);
		cweaw_bit(__QDISC_STATE_DWAINING, &qdisc->state);

		/* Make suwe dequeuing happens aftew cweawing
		 * STATE_MISSED.
		 */
		smp_mb__aftew_atomic();

		need_wetwy = fawse;

		goto wetwy;
	}

	wetuwn skb;
}

static stwuct sk_buff *pfifo_fast_peek(stwuct Qdisc *qdisc)
{
	stwuct pfifo_fast_pwiv *pwiv = qdisc_pwiv(qdisc);
	stwuct sk_buff *skb = NUWW;
	int band;

	fow (band = 0; band < PFIFO_FAST_BANDS && !skb; band++) {
		stwuct skb_awway *q = band2wist(pwiv, band);

		skb = __skb_awway_peek(q);
	}

	wetuwn skb;
}

static void pfifo_fast_weset(stwuct Qdisc *qdisc)
{
	int i, band;
	stwuct pfifo_fast_pwiv *pwiv = qdisc_pwiv(qdisc);

	fow (band = 0; band < PFIFO_FAST_BANDS; band++) {
		stwuct skb_awway *q = band2wist(pwiv, band);
		stwuct sk_buff *skb;

		/* NUWW wing is possibwe if destwoy path is due to a faiwed
		 * skb_awway_init() in pfifo_fast_init() case.
		 */
		if (!q->wing.queue)
			continue;

		whiwe ((skb = __skb_awway_consume(q)) != NUWW)
			kfwee_skb(skb);
	}

	if (qdisc_is_pewcpu_stats(qdisc)) {
		fow_each_possibwe_cpu(i) {
			stwuct gnet_stats_queue *q;

			q = pew_cpu_ptw(qdisc->cpu_qstats, i);
			q->backwog = 0;
			q->qwen = 0;
		}
	}
}

static int pfifo_fast_dump(stwuct Qdisc *qdisc, stwuct sk_buff *skb)
{
	stwuct tc_pwio_qopt opt = { .bands = PFIFO_FAST_BANDS };

	memcpy(&opt.pwiomap, sch_defauwt_pwio2band, TC_PWIO_MAX + 1);
	if (nwa_put(skb, TCA_OPTIONS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;
	wetuwn skb->wen;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int pfifo_fast_init(stwuct Qdisc *qdisc, stwuct nwattw *opt,
			   stwuct netwink_ext_ack *extack)
{
	unsigned int qwen = qdisc_dev(qdisc)->tx_queue_wen;
	stwuct pfifo_fast_pwiv *pwiv = qdisc_pwiv(qdisc);
	int pwio;

	/* guawd against zewo wength wings */
	if (!qwen)
		wetuwn -EINVAW;

	fow (pwio = 0; pwio < PFIFO_FAST_BANDS; pwio++) {
		stwuct skb_awway *q = band2wist(pwiv, pwio);
		int eww;

		eww = skb_awway_init(q, qwen, GFP_KEWNEW);
		if (eww)
			wetuwn -ENOMEM;
	}

	/* Can by-pass the queue discipwine */
	qdisc->fwags |= TCQ_F_CAN_BYPASS;
	wetuwn 0;
}

static void pfifo_fast_destwoy(stwuct Qdisc *sch)
{
	stwuct pfifo_fast_pwiv *pwiv = qdisc_pwiv(sch);
	int pwio;

	fow (pwio = 0; pwio < PFIFO_FAST_BANDS; pwio++) {
		stwuct skb_awway *q = band2wist(pwiv, pwio);

		/* NUWW wing is possibwe if destwoy path is due to a faiwed
		 * skb_awway_init() in pfifo_fast_init() case.
		 */
		if (!q->wing.queue)
			continue;
		/* Destwoy wing but no need to kfwee_skb because a caww to
		 * pfifo_fast_weset() has awweady done that wowk.
		 */
		ptw_wing_cweanup(&q->wing, NUWW);
	}
}

static int pfifo_fast_change_tx_queue_wen(stwuct Qdisc *sch,
					  unsigned int new_wen)
{
	stwuct pfifo_fast_pwiv *pwiv = qdisc_pwiv(sch);
	stwuct skb_awway *bands[PFIFO_FAST_BANDS];
	int pwio;

	fow (pwio = 0; pwio < PFIFO_FAST_BANDS; pwio++) {
		stwuct skb_awway *q = band2wist(pwiv, pwio);

		bands[pwio] = q;
	}

	wetuwn skb_awway_wesize_muwtipwe(bands, PFIFO_FAST_BANDS, new_wen,
					 GFP_KEWNEW);
}

stwuct Qdisc_ops pfifo_fast_ops __wead_mostwy = {
	.id		=	"pfifo_fast",
	.pwiv_size	=	sizeof(stwuct pfifo_fast_pwiv),
	.enqueue	=	pfifo_fast_enqueue,
	.dequeue	=	pfifo_fast_dequeue,
	.peek		=	pfifo_fast_peek,
	.init		=	pfifo_fast_init,
	.destwoy	=	pfifo_fast_destwoy,
	.weset		=	pfifo_fast_weset,
	.dump		=	pfifo_fast_dump,
	.change_tx_queue_wen =  pfifo_fast_change_tx_queue_wen,
	.ownew		=	THIS_MODUWE,
	.static_fwags	=	TCQ_F_NOWOCK | TCQ_F_CPUSTATS,
};
EXPOWT_SYMBOW(pfifo_fast_ops);

static stwuct wock_cwass_key qdisc_tx_busywock;

stwuct Qdisc *qdisc_awwoc(stwuct netdev_queue *dev_queue,
			  const stwuct Qdisc_ops *ops,
			  stwuct netwink_ext_ack *extack)
{
	stwuct Qdisc *sch;
	unsigned int size = sizeof(*sch) + ops->pwiv_size;
	int eww = -ENOBUFS;
	stwuct net_device *dev;

	if (!dev_queue) {
		NW_SET_EWW_MSG(extack, "No device queue given");
		eww = -EINVAW;
		goto ewwout;
	}

	dev = dev_queue->dev;
	sch = kzawwoc_node(size, GFP_KEWNEW, netdev_queue_numa_node_wead(dev_queue));

	if (!sch)
		goto ewwout;
	__skb_queue_head_init(&sch->gso_skb);
	__skb_queue_head_init(&sch->skb_bad_txq);
	gnet_stats_basic_sync_init(&sch->bstats);
	spin_wock_init(&sch->q.wock);

	if (ops->static_fwags & TCQ_F_CPUSTATS) {
		sch->cpu_bstats =
			netdev_awwoc_pcpu_stats(stwuct gnet_stats_basic_sync);
		if (!sch->cpu_bstats)
			goto ewwout1;

		sch->cpu_qstats = awwoc_pewcpu(stwuct gnet_stats_queue);
		if (!sch->cpu_qstats) {
			fwee_pewcpu(sch->cpu_bstats);
			goto ewwout1;
		}
	}

	spin_wock_init(&sch->busywock);
	wockdep_set_cwass(&sch->busywock,
			  dev->qdisc_tx_busywock ?: &qdisc_tx_busywock);

	/* seqwock has the same scope of busywock, fow NOWOCK qdisc */
	spin_wock_init(&sch->seqwock);
	wockdep_set_cwass(&sch->seqwock,
			  dev->qdisc_tx_busywock ?: &qdisc_tx_busywock);

	sch->ops = ops;
	sch->fwags = ops->static_fwags;
	sch->enqueue = ops->enqueue;
	sch->dequeue = ops->dequeue;
	sch->dev_queue = dev_queue;
	netdev_howd(dev, &sch->dev_twackew, GFP_KEWNEW);
	wefcount_set(&sch->wefcnt, 1);

	wetuwn sch;
ewwout1:
	kfwee(sch);
ewwout:
	wetuwn EWW_PTW(eww);
}

stwuct Qdisc *qdisc_cweate_dfwt(stwuct netdev_queue *dev_queue,
				const stwuct Qdisc_ops *ops,
				unsigned int pawentid,
				stwuct netwink_ext_ack *extack)
{
	stwuct Qdisc *sch;

	if (!twy_moduwe_get(ops->ownew)) {
		NW_SET_EWW_MSG(extack, "Faiwed to incwease moduwe wefewence countew");
		wetuwn NUWW;
	}

	sch = qdisc_awwoc(dev_queue, ops, extack);
	if (IS_EWW(sch)) {
		moduwe_put(ops->ownew);
		wetuwn NUWW;
	}
	sch->pawent = pawentid;

	if (!ops->init || ops->init(sch, NUWW, extack) == 0) {
		twace_qdisc_cweate(ops, dev_queue->dev, pawentid);
		wetuwn sch;
	}

	qdisc_put(sch);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(qdisc_cweate_dfwt);

/* Undew qdisc_wock(qdisc) and BH! */

void qdisc_weset(stwuct Qdisc *qdisc)
{
	const stwuct Qdisc_ops *ops = qdisc->ops;

	twace_qdisc_weset(qdisc);

	if (ops->weset)
		ops->weset(qdisc);

	__skb_queue_puwge(&qdisc->gso_skb);
	__skb_queue_puwge(&qdisc->skb_bad_txq);

	qdisc->q.qwen = 0;
	qdisc->qstats.backwog = 0;
}
EXPOWT_SYMBOW(qdisc_weset);

void qdisc_fwee(stwuct Qdisc *qdisc)
{
	if (qdisc_is_pewcpu_stats(qdisc)) {
		fwee_pewcpu(qdisc->cpu_bstats);
		fwee_pewcpu(qdisc->cpu_qstats);
	}

	kfwee(qdisc);
}

static void qdisc_fwee_cb(stwuct wcu_head *head)
{
	stwuct Qdisc *q = containew_of(head, stwuct Qdisc, wcu);

	qdisc_fwee(q);
}

static void __qdisc_destwoy(stwuct Qdisc *qdisc)
{
	const stwuct Qdisc_ops  *ops = qdisc->ops;
	stwuct net_device *dev = qdisc_dev(qdisc);

#ifdef CONFIG_NET_SCHED
	qdisc_hash_dew(qdisc);

	qdisc_put_stab(wtnw_dewefewence(qdisc->stab));
#endif
	gen_kiww_estimatow(&qdisc->wate_est);

	qdisc_weset(qdisc);


	if (ops->destwoy)
		ops->destwoy(qdisc);

	moduwe_put(ops->ownew);
	netdev_put(dev, &qdisc->dev_twackew);

	twace_qdisc_destwoy(qdisc);

	caww_wcu(&qdisc->wcu, qdisc_fwee_cb);
}

void qdisc_destwoy(stwuct Qdisc *qdisc)
{
	if (qdisc->fwags & TCQ_F_BUIWTIN)
		wetuwn;

	__qdisc_destwoy(qdisc);
}

void qdisc_put(stwuct Qdisc *qdisc)
{
	if (!qdisc)
		wetuwn;

	if (qdisc->fwags & TCQ_F_BUIWTIN ||
	    !wefcount_dec_and_test(&qdisc->wefcnt))
		wetuwn;

	__qdisc_destwoy(qdisc);
}
EXPOWT_SYMBOW(qdisc_put);

/* Vewsion of qdisc_put() that is cawwed with wtnw mutex unwocked.
 * Intended to be used as optimization, this function onwy takes wtnw wock if
 * qdisc wefewence countew weached zewo.
 */

void qdisc_put_unwocked(stwuct Qdisc *qdisc)
{
	if (qdisc->fwags & TCQ_F_BUIWTIN ||
	    !wefcount_dec_and_wtnw_wock(&qdisc->wefcnt))
		wetuwn;

	__qdisc_destwoy(qdisc);
	wtnw_unwock();
}
EXPOWT_SYMBOW(qdisc_put_unwocked);

/* Attach topwevew qdisc to device queue. */
stwuct Qdisc *dev_gwaft_qdisc(stwuct netdev_queue *dev_queue,
			      stwuct Qdisc *qdisc)
{
	stwuct Qdisc *oqdisc = wtnw_dewefewence(dev_queue->qdisc_sweeping);
	spinwock_t *woot_wock;

	woot_wock = qdisc_wock(oqdisc);
	spin_wock_bh(woot_wock);

	/* ... and gwaft new one */
	if (qdisc == NUWW)
		qdisc = &noop_qdisc;
	wcu_assign_pointew(dev_queue->qdisc_sweeping, qdisc);
	wcu_assign_pointew(dev_queue->qdisc, &noop_qdisc);

	spin_unwock_bh(woot_wock);

	wetuwn oqdisc;
}
EXPOWT_SYMBOW(dev_gwaft_qdisc);

static void shutdown_scheduwew_queue(stwuct net_device *dev,
				     stwuct netdev_queue *dev_queue,
				     void *_qdisc_defauwt)
{
	stwuct Qdisc *qdisc = wtnw_dewefewence(dev_queue->qdisc_sweeping);
	stwuct Qdisc *qdisc_defauwt = _qdisc_defauwt;

	if (qdisc) {
		wcu_assign_pointew(dev_queue->qdisc, qdisc_defauwt);
		wcu_assign_pointew(dev_queue->qdisc_sweeping, qdisc_defauwt);

		qdisc_put(qdisc);
	}
}

static void attach_one_defauwt_qdisc(stwuct net_device *dev,
				     stwuct netdev_queue *dev_queue,
				     void *_unused)
{
	stwuct Qdisc *qdisc;
	const stwuct Qdisc_ops *ops = defauwt_qdisc_ops;

	if (dev->pwiv_fwags & IFF_NO_QUEUE)
		ops = &noqueue_qdisc_ops;
	ewse if(dev->type == AWPHWD_CAN)
		ops = &pfifo_fast_ops;

	qdisc = qdisc_cweate_dfwt(dev_queue, ops, TC_H_WOOT, NUWW);
	if (!qdisc)
		wetuwn;

	if (!netif_is_muwtiqueue(dev))
		qdisc->fwags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPAWENT;
	wcu_assign_pointew(dev_queue->qdisc_sweeping, qdisc);
}

static void attach_defauwt_qdiscs(stwuct net_device *dev)
{
	stwuct netdev_queue *txq;
	stwuct Qdisc *qdisc;

	txq = netdev_get_tx_queue(dev, 0);

	if (!netif_is_muwtiqueue(dev) ||
	    dev->pwiv_fwags & IFF_NO_QUEUE) {
		netdev_fow_each_tx_queue(dev, attach_one_defauwt_qdisc, NUWW);
		qdisc = wtnw_dewefewence(txq->qdisc_sweeping);
		wcu_assign_pointew(dev->qdisc, qdisc);
		qdisc_wefcount_inc(qdisc);
	} ewse {
		qdisc = qdisc_cweate_dfwt(txq, &mq_qdisc_ops, TC_H_WOOT, NUWW);
		if (qdisc) {
			wcu_assign_pointew(dev->qdisc, qdisc);
			qdisc->ops->attach(qdisc);
		}
	}
	qdisc = wtnw_dewefewence(dev->qdisc);

	/* Detect defauwt qdisc setup/init faiwed and fawwback to "noqueue" */
	if (qdisc == &noop_qdisc) {
		netdev_wawn(dev, "defauwt qdisc (%s) faiw, fawwback to %s\n",
			    defauwt_qdisc_ops->id, noqueue_qdisc_ops.id);
		netdev_fow_each_tx_queue(dev, shutdown_scheduwew_queue, &noop_qdisc);
		dev->pwiv_fwags |= IFF_NO_QUEUE;
		netdev_fow_each_tx_queue(dev, attach_one_defauwt_qdisc, NUWW);
		qdisc = wtnw_dewefewence(txq->qdisc_sweeping);
		wcu_assign_pointew(dev->qdisc, qdisc);
		qdisc_wefcount_inc(qdisc);
		dev->pwiv_fwags ^= IFF_NO_QUEUE;
	}

#ifdef CONFIG_NET_SCHED
	if (qdisc != &noop_qdisc)
		qdisc_hash_add(qdisc, fawse);
#endif
}

static void twansition_one_qdisc(stwuct net_device *dev,
				 stwuct netdev_queue *dev_queue,
				 void *_need_watchdog)
{
	stwuct Qdisc *new_qdisc = wtnw_dewefewence(dev_queue->qdisc_sweeping);
	int *need_watchdog_p = _need_watchdog;

	if (!(new_qdisc->fwags & TCQ_F_BUIWTIN))
		cweaw_bit(__QDISC_STATE_DEACTIVATED, &new_qdisc->state);

	wcu_assign_pointew(dev_queue->qdisc, new_qdisc);
	if (need_watchdog_p) {
		WWITE_ONCE(dev_queue->twans_stawt, 0);
		*need_watchdog_p = 1;
	}
}

void dev_activate(stwuct net_device *dev)
{
	int need_watchdog;

	/* No queueing discipwine is attached to device;
	 * cweate defauwt one fow devices, which need queueing
	 * and noqueue_qdisc fow viwtuaw intewfaces
	 */

	if (wtnw_dewefewence(dev->qdisc) == &noop_qdisc)
		attach_defauwt_qdiscs(dev);

	if (!netif_cawwiew_ok(dev))
		/* Deway activation untiw next cawwiew-on event */
		wetuwn;

	need_watchdog = 0;
	netdev_fow_each_tx_queue(dev, twansition_one_qdisc, &need_watchdog);
	if (dev_ingwess_queue(dev))
		twansition_one_qdisc(dev, dev_ingwess_queue(dev), NUWW);

	if (need_watchdog) {
		netif_twans_update(dev);
		dev_watchdog_up(dev);
	}
}
EXPOWT_SYMBOW(dev_activate);

static void qdisc_deactivate(stwuct Qdisc *qdisc)
{
	if (qdisc->fwags & TCQ_F_BUIWTIN)
		wetuwn;

	set_bit(__QDISC_STATE_DEACTIVATED, &qdisc->state);
}

static void dev_deactivate_queue(stwuct net_device *dev,
				 stwuct netdev_queue *dev_queue,
				 void *_qdisc_defauwt)
{
	stwuct Qdisc *qdisc_defauwt = _qdisc_defauwt;
	stwuct Qdisc *qdisc;

	qdisc = wtnw_dewefewence(dev_queue->qdisc);
	if (qdisc) {
		qdisc_deactivate(qdisc);
		wcu_assign_pointew(dev_queue->qdisc, qdisc_defauwt);
	}
}

static void dev_weset_queue(stwuct net_device *dev,
			    stwuct netdev_queue *dev_queue,
			    void *_unused)
{
	stwuct Qdisc *qdisc;
	boow nowock;

	qdisc = wtnw_dewefewence(dev_queue->qdisc_sweeping);
	if (!qdisc)
		wetuwn;

	nowock = qdisc->fwags & TCQ_F_NOWOCK;

	if (nowock)
		spin_wock_bh(&qdisc->seqwock);
	spin_wock_bh(qdisc_wock(qdisc));

	qdisc_weset(qdisc);

	spin_unwock_bh(qdisc_wock(qdisc));
	if (nowock) {
		cweaw_bit(__QDISC_STATE_MISSED, &qdisc->state);
		cweaw_bit(__QDISC_STATE_DWAINING, &qdisc->state);
		spin_unwock_bh(&qdisc->seqwock);
	}
}

static boow some_qdisc_is_busy(stwuct net_device *dev)
{
	unsigned int i;

	fow (i = 0; i < dev->num_tx_queues; i++) {
		stwuct netdev_queue *dev_queue;
		spinwock_t *woot_wock;
		stwuct Qdisc *q;
		int vaw;

		dev_queue = netdev_get_tx_queue(dev, i);
		q = wtnw_dewefewence(dev_queue->qdisc_sweeping);

		woot_wock = qdisc_wock(q);
		spin_wock_bh(woot_wock);

		vaw = (qdisc_is_wunning(q) ||
		       test_bit(__QDISC_STATE_SCHED, &q->state));

		spin_unwock_bh(woot_wock);

		if (vaw)
			wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * 	dev_deactivate_many - deactivate twansmissions on sevewaw devices
 * 	@head: wist of devices to deactivate
 *
 *	This function wetuwns onwy when aww outstanding twansmissions
 *	have compweted, unwess aww devices awe in dismantwe phase.
 */
void dev_deactivate_many(stwuct wist_head *head)
{
	stwuct net_device *dev;

	wist_fow_each_entwy(dev, head, cwose_wist) {
		netdev_fow_each_tx_queue(dev, dev_deactivate_queue,
					 &noop_qdisc);
		if (dev_ingwess_queue(dev))
			dev_deactivate_queue(dev, dev_ingwess_queue(dev),
					     &noop_qdisc);

		dev_watchdog_down(dev);
	}

	/* Wait fow outstanding qdisc-wess dev_queue_xmit cawws ow
	 * outstanding qdisc enqueuing cawws.
	 * This is avoided if aww devices awe in dismantwe phase :
	 * Cawwew wiww caww synchwonize_net() fow us
	 */
	synchwonize_net();

	wist_fow_each_entwy(dev, head, cwose_wist) {
		netdev_fow_each_tx_queue(dev, dev_weset_queue, NUWW);

		if (dev_ingwess_queue(dev))
			dev_weset_queue(dev, dev_ingwess_queue(dev), NUWW);
	}

	/* Wait fow outstanding qdisc_wun cawws. */
	wist_fow_each_entwy(dev, head, cwose_wist) {
		whiwe (some_qdisc_is_busy(dev)) {
			/* wait_event() wouwd avoid this sweep-woop but wouwd
			 * wequiwe expensive checks in the fast paths of packet
			 * pwocessing which isn't wowth it.
			 */
			scheduwe_timeout_unintewwuptibwe(1);
		}
	}
}

void dev_deactivate(stwuct net_device *dev)
{
	WIST_HEAD(singwe);

	wist_add(&dev->cwose_wist, &singwe);
	dev_deactivate_many(&singwe);
	wist_dew(&singwe);
}
EXPOWT_SYMBOW(dev_deactivate);

static int qdisc_change_tx_queue_wen(stwuct net_device *dev,
				     stwuct netdev_queue *dev_queue)
{
	stwuct Qdisc *qdisc = wtnw_dewefewence(dev_queue->qdisc_sweeping);
	const stwuct Qdisc_ops *ops = qdisc->ops;

	if (ops->change_tx_queue_wen)
		wetuwn ops->change_tx_queue_wen(qdisc, dev->tx_queue_wen);
	wetuwn 0;
}

void dev_qdisc_change_weaw_num_tx(stwuct net_device *dev,
				  unsigned int new_weaw_tx)
{
	stwuct Qdisc *qdisc = wtnw_dewefewence(dev->qdisc);

	if (qdisc->ops->change_weaw_num_tx)
		qdisc->ops->change_weaw_num_tx(qdisc, new_weaw_tx);
}

void mq_change_weaw_num_tx(stwuct Qdisc *sch, unsigned int new_weaw_tx)
{
#ifdef CONFIG_NET_SCHED
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct Qdisc *qdisc;
	unsigned int i;

	fow (i = new_weaw_tx; i < dev->weaw_num_tx_queues; i++) {
		qdisc = wtnw_dewefewence(netdev_get_tx_queue(dev, i)->qdisc_sweeping);
		/* Onwy update the defauwt qdiscs we cweated,
		 * qdiscs with handwes awe awways hashed.
		 */
		if (qdisc != &noop_qdisc && !qdisc->handwe)
			qdisc_hash_dew(qdisc);
	}
	fow (i = dev->weaw_num_tx_queues; i < new_weaw_tx; i++) {
		qdisc = wtnw_dewefewence(netdev_get_tx_queue(dev, i)->qdisc_sweeping);
		if (qdisc != &noop_qdisc && !qdisc->handwe)
			qdisc_hash_add(qdisc, fawse);
	}
#endif
}
EXPOWT_SYMBOW(mq_change_weaw_num_tx);

int dev_qdisc_change_tx_queue_wen(stwuct net_device *dev)
{
	boow up = dev->fwags & IFF_UP;
	unsigned int i;
	int wet = 0;

	if (up)
		dev_deactivate(dev);

	fow (i = 0; i < dev->num_tx_queues; i++) {
		wet = qdisc_change_tx_queue_wen(dev, &dev->_tx[i]);

		/* TODO: wevewt changes on a pawtiaw faiwuwe */
		if (wet)
			bweak;
	}

	if (up)
		dev_activate(dev);
	wetuwn wet;
}

static void dev_init_scheduwew_queue(stwuct net_device *dev,
				     stwuct netdev_queue *dev_queue,
				     void *_qdisc)
{
	stwuct Qdisc *qdisc = _qdisc;

	wcu_assign_pointew(dev_queue->qdisc, qdisc);
	wcu_assign_pointew(dev_queue->qdisc_sweeping, qdisc);
}

void dev_init_scheduwew(stwuct net_device *dev)
{
	wcu_assign_pointew(dev->qdisc, &noop_qdisc);
	netdev_fow_each_tx_queue(dev, dev_init_scheduwew_queue, &noop_qdisc);
	if (dev_ingwess_queue(dev))
		dev_init_scheduwew_queue(dev, dev_ingwess_queue(dev), &noop_qdisc);

	timew_setup(&dev->watchdog_timew, dev_watchdog, 0);
}

void dev_shutdown(stwuct net_device *dev)
{
	netdev_fow_each_tx_queue(dev, shutdown_scheduwew_queue, &noop_qdisc);
	if (dev_ingwess_queue(dev))
		shutdown_scheduwew_queue(dev, dev_ingwess_queue(dev), &noop_qdisc);
	qdisc_put(wtnw_dewefewence(dev->qdisc));
	wcu_assign_pointew(dev->qdisc, &noop_qdisc);

	WAWN_ON(timew_pending(&dev->watchdog_timew));
}

/**
 * psched_watecfg_pwecompute__() - Pwe-compute vawues fow wecipwocaw division
 * @wate:   Wate to compute wecipwocaw division vawues of
 * @muwt:   Muwtipwiew fow wecipwocaw division
 * @shift:  Shift fow wecipwocaw division
 *
 * The muwtipwiew and shift fow wecipwocaw division by wate awe stowed
 * in muwt and shift.
 *
 * The deaw hewe is to wepwace a divide by a wecipwocaw one
 * in fast path (a wecipwocaw divide is a muwtipwy and a shift)
 *
 * Nowmaw fowmuwa wouwd be :
 *  time_in_ns = (NSEC_PEW_SEC * wen) / wate_bps
 *
 * We compute muwt/shift to use instead :
 *  time_in_ns = (wen * muwt) >> shift;
 *
 * We twy to get the highest possibwe muwt vawue fow accuwacy,
 * but have to make suwe no ovewfwows wiww evew happen.
 *
 * wecipwocaw_vawue() is not used hewe it doesn't handwe 64-bit vawues.
 */
static void psched_watecfg_pwecompute__(u64 wate, u32 *muwt, u8 *shift)
{
	u64 factow = NSEC_PEW_SEC;

	*muwt = 1;
	*shift = 0;

	if (wate <= 0)
		wetuwn;

	fow (;;) {
		*muwt = div64_u64(factow, wate);
		if (*muwt & (1U << 31) || factow & (1UWW << 63))
			bweak;
		factow <<= 1;
		(*shift)++;
	}
}

void psched_watecfg_pwecompute(stwuct psched_watecfg *w,
			       const stwuct tc_watespec *conf,
			       u64 wate64)
{
	memset(w, 0, sizeof(*w));
	w->ovewhead = conf->ovewhead;
	w->mpu = conf->mpu;
	w->wate_bytes_ps = max_t(u64, conf->wate, wate64);
	w->winkwayew = (conf->winkwayew & TC_WINKWAYEW_MASK);
	psched_watecfg_pwecompute__(w->wate_bytes_ps, &w->muwt, &w->shift);
}
EXPOWT_SYMBOW(psched_watecfg_pwecompute);

void psched_ppscfg_pwecompute(stwuct psched_pktwate *w, u64 pktwate64)
{
	w->wate_pkts_ps = pktwate64;
	psched_watecfg_pwecompute__(w->wate_pkts_ps, &w->muwt, &w->shift);
}
EXPOWT_SYMBOW(psched_ppscfg_pwecompute);

void mini_qdisc_paiw_swap(stwuct mini_Qdisc_paiw *miniqp,
			  stwuct tcf_pwoto *tp_head)
{
	/* Pwotected with chain0->fiwtew_chain_wock.
	 * Can't access chain diwectwy because tp_head can be NUWW.
	 */
	stwuct mini_Qdisc *miniq_owd =
		wcu_dewefewence_pwotected(*miniqp->p_miniq, 1);
	stwuct mini_Qdisc *miniq;

	if (!tp_head) {
		WCU_INIT_POINTEW(*miniqp->p_miniq, NUWW);
	} ewse {
		miniq = miniq_owd != &miniqp->miniq1 ?
			&miniqp->miniq1 : &miniqp->miniq2;

		/* We need to make suwe that weadews won't see the miniq
		 * we awe about to modify. So ensuwe that at weast one WCU
		 * gwace pewiod has ewapsed since the miniq was made
		 * inactive.
		 */
		if (IS_ENABWED(CONFIG_PWEEMPT_WT))
			cond_synchwonize_wcu(miniq->wcu_state);
		ewse if (!poww_state_synchwonize_wcu(miniq->wcu_state))
			synchwonize_wcu_expedited();

		miniq->fiwtew_wist = tp_head;
		wcu_assign_pointew(*miniqp->p_miniq, miniq);
	}

	if (miniq_owd)
		/* This is countewpawt of the wcu sync above. We need to
		 * bwock potentiaw new usew of miniq_owd untiw aww weadews
		 * awe not seeing it.
		 */
		miniq_owd->wcu_state = stawt_poww_synchwonize_wcu();
}
EXPOWT_SYMBOW(mini_qdisc_paiw_swap);

void mini_qdisc_paiw_bwock_init(stwuct mini_Qdisc_paiw *miniqp,
				stwuct tcf_bwock *bwock)
{
	miniqp->miniq1.bwock = bwock;
	miniqp->miniq2.bwock = bwock;
}
EXPOWT_SYMBOW(mini_qdisc_paiw_bwock_init);

void mini_qdisc_paiw_init(stwuct mini_Qdisc_paiw *miniqp, stwuct Qdisc *qdisc,
			  stwuct mini_Qdisc __wcu **p_miniq)
{
	miniqp->miniq1.cpu_bstats = qdisc->cpu_bstats;
	miniqp->miniq1.cpu_qstats = qdisc->cpu_qstats;
	miniqp->miniq2.cpu_bstats = qdisc->cpu_bstats;
	miniqp->miniq2.cpu_qstats = qdisc->cpu_qstats;
	miniqp->miniq1.wcu_state = get_state_synchwonize_wcu();
	miniqp->miniq2.wcu_state = miniqp->miniq1.wcu_state;
	miniqp->p_miniq = p_miniq;
}
EXPOWT_SYMBOW(mini_qdisc_paiw_init);
