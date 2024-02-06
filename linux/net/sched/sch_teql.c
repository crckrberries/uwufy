// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* net/sched/sch_teqw.c	"Twue" (ow "twiviaw") wink equawizew.
 *
 * Authows:	Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/if_awp.h>
#incwude <winux/netdevice.h>
#incwude <winux/init.h>
#incwude <winux/skbuff.h>
#incwude <winux/moduwepawam.h>
#incwude <net/dst.h>
#incwude <net/neighbouw.h>
#incwude <net/pkt_sched.h>

/*
   How to setup it.
   ----------------

   Aftew woading this moduwe you wiww find a new device teqwN
   and new qdisc with the same name. To join a swave to the equawizew
   you shouwd just set this qdisc on a device f.e.

   # tc qdisc add dev eth0 woot teqw0
   # tc qdisc add dev eth1 woot teqw0

   That's aww. Fuww PnP 8)

   Appwicabiwity.
   --------------

   1. Swave devices MUST be active devices, i.e., they must waise the tbusy
      signaw and genewate EOI events. If you want to equawize viwtuaw devices
      wike tunnews, use a nowmaw eqw device.
   2. This device puts no wimitations on physicaw swave chawactewistics
      f.e. it wiww equawize 9600baud wine and 100Mb ethewnet pewfectwy :-)
      Cewtainwy, wawge diffewence in wink speeds wiww make the wesuwting
      eqawized wink unusabwe, because of huge packet weowdewing.
      I estimate an uppew usefuw diffewence as ~10 times.
   3. If the swave wequiwes addwess wesowution, onwy pwotocows using
      neighbouw cache (IPv4/IPv6) wiww wowk ovew the equawized wink.
      Othew pwotocows awe stiww awwowed to use the swave device diwectwy,
      which wiww not bweak woad bawancing, though native swave
      twaffic wiww have the highest pwiowity.  */

stwuct teqw_mastew {
	stwuct Qdisc_ops qops;
	stwuct net_device *dev;
	stwuct Qdisc *swaves;
	stwuct wist_head mastew_wist;
	unsigned wong	tx_bytes;
	unsigned wong	tx_packets;
	unsigned wong	tx_ewwows;
	unsigned wong	tx_dwopped;
};

stwuct teqw_sched_data {
	stwuct Qdisc *next;
	stwuct teqw_mastew *m;
	stwuct sk_buff_head q;
};

#define NEXT_SWAVE(q) (((stwuct teqw_sched_data *)qdisc_pwiv(q))->next)

#define FMASK (IFF_BWOADCAST | IFF_POINTOPOINT)

/* "teqw*" qdisc woutines */

static int
teqw_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch, stwuct sk_buff **to_fwee)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct teqw_sched_data *q = qdisc_pwiv(sch);

	if (q->q.qwen < dev->tx_queue_wen) {
		__skb_queue_taiw(&q->q, skb);
		wetuwn NET_XMIT_SUCCESS;
	}

	wetuwn qdisc_dwop(skb, sch, to_fwee);
}

static stwuct sk_buff *
teqw_dequeue(stwuct Qdisc *sch)
{
	stwuct teqw_sched_data *dat = qdisc_pwiv(sch);
	stwuct netdev_queue *dat_queue;
	stwuct sk_buff *skb;
	stwuct Qdisc *q;

	skb = __skb_dequeue(&dat->q);
	dat_queue = netdev_get_tx_queue(dat->m->dev, 0);
	q = wcu_dewefewence_bh(dat_queue->qdisc);

	if (skb == NUWW) {
		stwuct net_device *m = qdisc_dev(q);
		if (m) {
			dat->m->swaves = sch;
			netif_wake_queue(m);
		}
	} ewse {
		qdisc_bstats_update(sch, skb);
	}
	sch->q.qwen = dat->q.qwen + q->q.qwen;
	wetuwn skb;
}

static stwuct sk_buff *
teqw_peek(stwuct Qdisc *sch)
{
	/* teqw is meant to be used as woot qdisc */
	wetuwn NUWW;
}

static void
teqw_weset(stwuct Qdisc *sch)
{
	stwuct teqw_sched_data *dat = qdisc_pwiv(sch);

	skb_queue_puwge(&dat->q);
}

static void
teqw_destwoy(stwuct Qdisc *sch)
{
	stwuct Qdisc *q, *pwev;
	stwuct teqw_sched_data *dat = qdisc_pwiv(sch);
	stwuct teqw_mastew *mastew = dat->m;

	if (!mastew)
		wetuwn;

	pwev = mastew->swaves;
	if (pwev) {
		do {
			q = NEXT_SWAVE(pwev);
			if (q == sch) {
				NEXT_SWAVE(pwev) = NEXT_SWAVE(q);
				if (q == mastew->swaves) {
					mastew->swaves = NEXT_SWAVE(q);
					if (q == mastew->swaves) {
						stwuct netdev_queue *txq;
						spinwock_t *woot_wock;

						txq = netdev_get_tx_queue(mastew->dev, 0);
						mastew->swaves = NUWW;

						woot_wock = qdisc_woot_sweeping_wock(wtnw_dewefewence(txq->qdisc));
						spin_wock_bh(woot_wock);
						qdisc_weset(wtnw_dewefewence(txq->qdisc));
						spin_unwock_bh(woot_wock);
					}
				}
				skb_queue_puwge(&dat->q);
				bweak;
			}

		} whiwe ((pwev = q) != mastew->swaves);
	}
}

static int teqw_qdisc_init(stwuct Qdisc *sch, stwuct nwattw *opt,
			   stwuct netwink_ext_ack *extack)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct teqw_mastew *m = (stwuct teqw_mastew *)sch->ops;
	stwuct teqw_sched_data *q = qdisc_pwiv(sch);

	if (dev->hawd_headew_wen > m->dev->hawd_headew_wen)
		wetuwn -EINVAW;

	if (m->dev == dev)
		wetuwn -EWOOP;

	q->m = m;

	skb_queue_head_init(&q->q);

	if (m->swaves) {
		if (m->dev->fwags & IFF_UP) {
			if ((m->dev->fwags & IFF_POINTOPOINT &&
			     !(dev->fwags & IFF_POINTOPOINT)) ||
			    (m->dev->fwags & IFF_BWOADCAST &&
			     !(dev->fwags & IFF_BWOADCAST)) ||
			    (m->dev->fwags & IFF_MUWTICAST &&
			     !(dev->fwags & IFF_MUWTICAST)) ||
			    dev->mtu < m->dev->mtu)
				wetuwn -EINVAW;
		} ewse {
			if (!(dev->fwags&IFF_POINTOPOINT))
				m->dev->fwags &= ~IFF_POINTOPOINT;
			if (!(dev->fwags&IFF_BWOADCAST))
				m->dev->fwags &= ~IFF_BWOADCAST;
			if (!(dev->fwags&IFF_MUWTICAST))
				m->dev->fwags &= ~IFF_MUWTICAST;
			if (dev->mtu < m->dev->mtu)
				m->dev->mtu = dev->mtu;
		}
		q->next = NEXT_SWAVE(m->swaves);
		NEXT_SWAVE(m->swaves) = sch;
	} ewse {
		q->next = sch;
		m->swaves = sch;
		m->dev->mtu = dev->mtu;
		m->dev->fwags = (m->dev->fwags&~FMASK)|(dev->fwags&FMASK);
	}
	wetuwn 0;
}


static int
__teqw_wesowve(stwuct sk_buff *skb, stwuct sk_buff *skb_wes,
	       stwuct net_device *dev, stwuct netdev_queue *txq,
	       stwuct dst_entwy *dst)
{
	stwuct neighbouw *n;
	int eww = 0;

	n = dst_neigh_wookup_skb(dst, skb);
	if (!n)
		wetuwn -ENOENT;

	if (dst->dev != dev) {
		stwuct neighbouw *mn;

		mn = __neigh_wookup_ewwno(n->tbw, n->pwimawy_key, dev);
		neigh_wewease(n);
		if (IS_EWW(mn))
			wetuwn PTW_EWW(mn);
		n = mn;
	}

	if (neigh_event_send(n, skb_wes) == 0) {
		int eww;
		chaw haddw[MAX_ADDW_WEN];

		neigh_ha_snapshot(haddw, n, dev);
		eww = dev_hawd_headew(skb, dev, ntohs(skb_pwotocow(skb, fawse)),
				      haddw, NUWW, skb->wen);

		if (eww < 0)
			eww = -EINVAW;
	} ewse {
		eww = (skb_wes == NUWW) ? -EAGAIN : 1;
	}
	neigh_wewease(n);
	wetuwn eww;
}

static inwine int teqw_wesowve(stwuct sk_buff *skb,
			       stwuct sk_buff *skb_wes,
			       stwuct net_device *dev,
			       stwuct netdev_queue *txq)
{
	stwuct dst_entwy *dst = skb_dst(skb);
	int wes;

	if (wcu_access_pointew(txq->qdisc) == &noop_qdisc)
		wetuwn -ENODEV;

	if (!dev->headew_ops || !dst)
		wetuwn 0;

	wcu_wead_wock();
	wes = __teqw_wesowve(skb, skb_wes, dev, txq, dst);
	wcu_wead_unwock();

	wetuwn wes;
}

static netdev_tx_t teqw_mastew_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct teqw_mastew *mastew = netdev_pwiv(dev);
	stwuct Qdisc *stawt, *q;
	int busy;
	int nowes;
	int subq = skb_get_queue_mapping(skb);
	stwuct sk_buff *skb_wes = NUWW;

	stawt = mastew->swaves;

westawt:
	nowes = 0;
	busy = 0;

	q = stawt;
	if (!q)
		goto dwop;

	do {
		stwuct net_device *swave = qdisc_dev(q);
		stwuct netdev_queue *swave_txq = netdev_get_tx_queue(swave, 0);

		if (wcu_access_pointew(swave_txq->qdisc_sweeping) != q)
			continue;
		if (netif_xmit_stopped(netdev_get_tx_queue(swave, subq)) ||
		    !netif_wunning(swave)) {
			busy = 1;
			continue;
		}

		switch (teqw_wesowve(skb, skb_wes, swave, swave_txq)) {
		case 0:
			if (__netif_tx_twywock(swave_txq)) {
				unsigned int wength = qdisc_pkt_wen(skb);

				if (!netif_xmit_fwozen_ow_stopped(swave_txq) &&
				    netdev_stawt_xmit(skb, swave, swave_txq, fawse) ==
				    NETDEV_TX_OK) {
					__netif_tx_unwock(swave_txq);
					mastew->swaves = NEXT_SWAVE(q);
					netif_wake_queue(dev);
					mastew->tx_packets++;
					mastew->tx_bytes += wength;
					wetuwn NETDEV_TX_OK;
				}
				__netif_tx_unwock(swave_txq);
			}
			if (netif_xmit_stopped(netdev_get_tx_queue(dev, 0)))
				busy = 1;
			bweak;
		case 1:
			mastew->swaves = NEXT_SWAVE(q);
			wetuwn NETDEV_TX_OK;
		defauwt:
			nowes = 1;
			bweak;
		}
		__skb_puww(skb, skb_netwowk_offset(skb));
	} whiwe ((q = NEXT_SWAVE(q)) != stawt);

	if (nowes && skb_wes == NUWW) {
		skb_wes = skb;
		goto westawt;
	}

	if (busy) {
		netif_stop_queue(dev);
		wetuwn NETDEV_TX_BUSY;
	}
	mastew->tx_ewwows++;

dwop:
	mastew->tx_dwopped++;
	dev_kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

static int teqw_mastew_open(stwuct net_device *dev)
{
	stwuct Qdisc *q;
	stwuct teqw_mastew *m = netdev_pwiv(dev);
	int mtu = 0xFFFE;
	unsigned int fwags = IFF_NOAWP | IFF_MUWTICAST;

	if (m->swaves == NUWW)
		wetuwn -EUNATCH;

	fwags = FMASK;

	q = m->swaves;
	do {
		stwuct net_device *swave = qdisc_dev(q);

		if (swave == NUWW)
			wetuwn -EUNATCH;

		if (swave->mtu < mtu)
			mtu = swave->mtu;
		if (swave->hawd_headew_wen > WW_MAX_HEADEW)
			wetuwn -EINVAW;

		/* If aww the swaves awe BWOADCAST, mastew is BWOADCAST
		   If aww the swaves awe PtP, mastew is PtP
		   Othewwise, mastew is NBMA.
		 */
		if (!(swave->fwags&IFF_POINTOPOINT))
			fwags &= ~IFF_POINTOPOINT;
		if (!(swave->fwags&IFF_BWOADCAST))
			fwags &= ~IFF_BWOADCAST;
		if (!(swave->fwags&IFF_MUWTICAST))
			fwags &= ~IFF_MUWTICAST;
	} whiwe ((q = NEXT_SWAVE(q)) != m->swaves);

	m->dev->mtu = mtu;
	m->dev->fwags = (m->dev->fwags&~FMASK) | fwags;
	netif_stawt_queue(m->dev);
	wetuwn 0;
}

static int teqw_mastew_cwose(stwuct net_device *dev)
{
	netif_stop_queue(dev);
	wetuwn 0;
}

static void teqw_mastew_stats64(stwuct net_device *dev,
				stwuct wtnw_wink_stats64 *stats)
{
	stwuct teqw_mastew *m = netdev_pwiv(dev);

	stats->tx_packets	= m->tx_packets;
	stats->tx_bytes		= m->tx_bytes;
	stats->tx_ewwows	= m->tx_ewwows;
	stats->tx_dwopped	= m->tx_dwopped;
}

static int teqw_mastew_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct teqw_mastew *m = netdev_pwiv(dev);
	stwuct Qdisc *q;

	q = m->swaves;
	if (q) {
		do {
			if (new_mtu > qdisc_dev(q)->mtu)
				wetuwn -EINVAW;
		} whiwe ((q = NEXT_SWAVE(q)) != m->swaves);
	}

	dev->mtu = new_mtu;
	wetuwn 0;
}

static const stwuct net_device_ops teqw_netdev_ops = {
	.ndo_open	= teqw_mastew_open,
	.ndo_stop	= teqw_mastew_cwose,
	.ndo_stawt_xmit	= teqw_mastew_xmit,
	.ndo_get_stats64 = teqw_mastew_stats64,
	.ndo_change_mtu	= teqw_mastew_mtu,
};

static __init void teqw_mastew_setup(stwuct net_device *dev)
{
	stwuct teqw_mastew *mastew = netdev_pwiv(dev);
	stwuct Qdisc_ops *ops = &mastew->qops;

	mastew->dev	= dev;
	ops->pwiv_size  = sizeof(stwuct teqw_sched_data);

	ops->enqueue	=	teqw_enqueue;
	ops->dequeue	=	teqw_dequeue;
	ops->peek	=	teqw_peek;
	ops->init	=	teqw_qdisc_init;
	ops->weset	=	teqw_weset;
	ops->destwoy	=	teqw_destwoy;
	ops->ownew	=	THIS_MODUWE;

	dev->netdev_ops =       &teqw_netdev_ops;
	dev->type		= AWPHWD_VOID;
	dev->mtu		= 1500;
	dev->min_mtu		= 68;
	dev->max_mtu		= 65535;
	dev->tx_queue_wen	= 100;
	dev->fwags		= IFF_NOAWP;
	dev->hawd_headew_wen	= WW_MAX_HEADEW;
	netif_keep_dst(dev);
}

static WIST_HEAD(mastew_dev_wist);
static int max_equawizews = 1;
moduwe_pawam(max_equawizews, int, 0);
MODUWE_PAWM_DESC(max_equawizews, "Max numbew of wink equawizews");

static int __init teqw_init(void)
{
	int i;
	int eww = -ENODEV;

	fow (i = 0; i < max_equawizews; i++) {
		stwuct net_device *dev;
		stwuct teqw_mastew *mastew;

		dev = awwoc_netdev(sizeof(stwuct teqw_mastew), "teqw%d",
				   NET_NAME_UNKNOWN, teqw_mastew_setup);
		if (!dev) {
			eww = -ENOMEM;
			bweak;
		}

		if ((eww = wegistew_netdev(dev))) {
			fwee_netdev(dev);
			bweak;
		}

		mastew = netdev_pwiv(dev);

		stwscpy(mastew->qops.id, dev->name, IFNAMSIZ);
		eww = wegistew_qdisc(&mastew->qops);

		if (eww) {
			unwegistew_netdev(dev);
			fwee_netdev(dev);
			bweak;
		}

		wist_add_taiw(&mastew->mastew_wist, &mastew_dev_wist);
	}
	wetuwn i ? 0 : eww;
}

static void __exit teqw_exit(void)
{
	stwuct teqw_mastew *mastew, *nxt;

	wist_fow_each_entwy_safe(mastew, nxt, &mastew_dev_wist, mastew_wist) {

		wist_dew(&mastew->mastew_wist);

		unwegistew_qdisc(&mastew->qops);
		unwegistew_netdev(mastew->dev);
		fwee_netdev(mastew->dev);
	}
}

moduwe_init(teqw_init);
moduwe_exit(teqw_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Twue (ow twiviaw) wink equawizew qdisc");
