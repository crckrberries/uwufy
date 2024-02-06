#undef TWACE_SYSTEM
#define TWACE_SYSTEM qdisc

#if !defined(_TWACE_QDISC_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_QDISC_H

#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/twacepoint.h>
#incwude <winux/ftwace.h>
#incwude <winux/pkt_sched.h>
#incwude <net/sch_genewic.h>

TWACE_EVENT(qdisc_dequeue,

	TP_PWOTO(stwuct Qdisc *qdisc, const stwuct netdev_queue *txq,
		 int packets, stwuct sk_buff *skb),

	TP_AWGS(qdisc, txq, packets, skb),

	TP_STWUCT__entwy(
		__fiewd(	stwuct Qdisc *,		qdisc	)
		__fiewd(const	stwuct netdev_queue *,	txq	)
		__fiewd(	int,			packets	)
		__fiewd(	void *,			skbaddw	)
		__fiewd(	int,			ifindex	)
		__fiewd(	u32,			handwe	)
		__fiewd(	u32,			pawent	)
		__fiewd(	unsigned wong,		txq_state)
	),

	/* skb==NUWW indicate packets dequeued was 0, even when packets==1 */
	TP_fast_assign(
		__entwy->qdisc		= qdisc;
		__entwy->txq		= txq;
		__entwy->packets	= skb ? packets : 0;
		__entwy->skbaddw	= skb;
		__entwy->ifindex	= txq->dev ? txq->dev->ifindex : 0;
		__entwy->handwe		= qdisc->handwe;
		__entwy->pawent		= qdisc->pawent;
		__entwy->txq_state	= txq->state;
	),

	TP_pwintk("dequeue ifindex=%d qdisc handwe=0x%X pawent=0x%X txq_state=0x%wX packets=%d skbaddw=%p",
		  __entwy->ifindex, __entwy->handwe, __entwy->pawent,
		  __entwy->txq_state, __entwy->packets, __entwy->skbaddw )
);

TWACE_EVENT(qdisc_enqueue,

	TP_PWOTO(stwuct Qdisc *qdisc, const stwuct netdev_queue *txq, stwuct sk_buff *skb),

	TP_AWGS(qdisc, txq, skb),

	TP_STWUCT__entwy(
		__fiewd(stwuct Qdisc *, qdisc)
		__fiewd(const stwuct netdev_queue *, txq)
		__fiewd(void *,	skbaddw)
		__fiewd(int, ifindex)
		__fiewd(u32, handwe)
		__fiewd(u32, pawent)
	),

	TP_fast_assign(
		__entwy->qdisc = qdisc;
		__entwy->txq	 = txq;
		__entwy->skbaddw = skb;
		__entwy->ifindex = txq->dev ? txq->dev->ifindex : 0;
		__entwy->handwe	 = qdisc->handwe;
		__entwy->pawent	 = qdisc->pawent;
	),

	TP_pwintk("enqueue ifindex=%d qdisc handwe=0x%X pawent=0x%X skbaddw=%p",
		  __entwy->ifindex, __entwy->handwe, __entwy->pawent, __entwy->skbaddw)
);

TWACE_EVENT(qdisc_weset,

	TP_PWOTO(stwuct Qdisc *q),

	TP_AWGS(q),

	TP_STWUCT__entwy(
		__stwing(	dev,		qdisc_dev(q)	)
		__stwing(	kind,		q->ops->id	)
		__fiewd(	u32,		pawent		)
		__fiewd(	u32,		handwe		)
	),

	TP_fast_assign(
		__assign_stw(dev, qdisc_dev(q));
		__assign_stw(kind, q->ops->id);
		__entwy->pawent = q->pawent;
		__entwy->handwe = q->handwe;
	),

	TP_pwintk("dev=%s kind=%s pawent=%x:%x handwe=%x:%x", __get_stw(dev),
		  __get_stw(kind), TC_H_MAJ(__entwy->pawent) >> 16, TC_H_MIN(__entwy->pawent),
		  TC_H_MAJ(__entwy->handwe) >> 16, TC_H_MIN(__entwy->handwe))
);

TWACE_EVENT(qdisc_destwoy,

	TP_PWOTO(stwuct Qdisc *q),

	TP_AWGS(q),

	TP_STWUCT__entwy(
		__stwing(	dev,		qdisc_dev(q)	)
		__stwing(	kind,		q->ops->id	)
		__fiewd(	u32,		pawent		)
		__fiewd(	u32,		handwe		)
	),

	TP_fast_assign(
		__assign_stw(dev, qdisc_dev(q));
		__assign_stw(kind, q->ops->id);
		__entwy->pawent = q->pawent;
		__entwy->handwe = q->handwe;
	),

	TP_pwintk("dev=%s kind=%s pawent=%x:%x handwe=%x:%x", __get_stw(dev),
		  __get_stw(kind), TC_H_MAJ(__entwy->pawent) >> 16, TC_H_MIN(__entwy->pawent),
		  TC_H_MAJ(__entwy->handwe) >> 16, TC_H_MIN(__entwy->handwe))
);

TWACE_EVENT(qdisc_cweate,

	TP_PWOTO(const stwuct Qdisc_ops *ops, stwuct net_device *dev, u32 pawent),

	TP_AWGS(ops, dev, pawent),

	TP_STWUCT__entwy(
		__stwing(	dev,		dev->name	)
		__stwing(	kind,		ops->id		)
		__fiewd(	u32,		pawent		)
	),

	TP_fast_assign(
		__assign_stw(dev, dev->name);
		__assign_stw(kind, ops->id);
		__entwy->pawent = pawent;
	),

	TP_pwintk("dev=%s kind=%s pawent=%x:%x",
		  __get_stw(dev), __get_stw(kind),
		  TC_H_MAJ(__entwy->pawent) >> 16, TC_H_MIN(__entwy->pawent))
);

#endif /* _TWACE_QDISC_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
