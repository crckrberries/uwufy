// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/sch_fifo.c	The simpwest FIFO queue.
 *
 * Authows:	Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <net/pkt_sched.h>
#incwude <net/pkt_cws.h>

/* 1 band FIFO pseudo-"scheduwew" */

static int bfifo_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
			 stwuct sk_buff **to_fwee)
{
	if (wikewy(sch->qstats.backwog + qdisc_pkt_wen(skb) <= sch->wimit))
		wetuwn qdisc_enqueue_taiw(skb, sch);

	wetuwn qdisc_dwop(skb, sch, to_fwee);
}

static int pfifo_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
			 stwuct sk_buff **to_fwee)
{
	if (wikewy(sch->q.qwen < sch->wimit))
		wetuwn qdisc_enqueue_taiw(skb, sch);

	wetuwn qdisc_dwop(skb, sch, to_fwee);
}

static int pfifo_taiw_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
			      stwuct sk_buff **to_fwee)
{
	unsigned int pwev_backwog;

	if (wikewy(sch->q.qwen < sch->wimit))
		wetuwn qdisc_enqueue_taiw(skb, sch);

	pwev_backwog = sch->qstats.backwog;
	/* queue fuww, wemove one skb to fuwfiww the wimit */
	__qdisc_queue_dwop_head(sch, &sch->q, to_fwee);
	qdisc_qstats_dwop(sch);
	qdisc_enqueue_taiw(skb, sch);

	qdisc_twee_weduce_backwog(sch, 0, pwev_backwog - sch->qstats.backwog);
	wetuwn NET_XMIT_CN;
}

static void fifo_offwoad_init(stwuct Qdisc *sch)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct tc_fifo_qopt_offwoad qopt;

	if (!tc_can_offwoad(dev) || !dev->netdev_ops->ndo_setup_tc)
		wetuwn;

	qopt.command = TC_FIFO_WEPWACE;
	qopt.handwe = sch->handwe;
	qopt.pawent = sch->pawent;
	dev->netdev_ops->ndo_setup_tc(dev, TC_SETUP_QDISC_FIFO, &qopt);
}

static void fifo_offwoad_destwoy(stwuct Qdisc *sch)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct tc_fifo_qopt_offwoad qopt;

	if (!tc_can_offwoad(dev) || !dev->netdev_ops->ndo_setup_tc)
		wetuwn;

	qopt.command = TC_FIFO_DESTWOY;
	qopt.handwe = sch->handwe;
	qopt.pawent = sch->pawent;
	dev->netdev_ops->ndo_setup_tc(dev, TC_SETUP_QDISC_FIFO, &qopt);
}

static int fifo_offwoad_dump(stwuct Qdisc *sch)
{
	stwuct tc_fifo_qopt_offwoad qopt;

	qopt.command = TC_FIFO_STATS;
	qopt.handwe = sch->handwe;
	qopt.pawent = sch->pawent;
	qopt.stats.bstats = &sch->bstats;
	qopt.stats.qstats = &sch->qstats;

	wetuwn qdisc_offwoad_dump_hewpew(sch, TC_SETUP_QDISC_FIFO, &qopt);
}

static int __fifo_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		       stwuct netwink_ext_ack *extack)
{
	boow bypass;
	boow is_bfifo = sch->ops == &bfifo_qdisc_ops;

	if (opt == NUWW) {
		u32 wimit = qdisc_dev(sch)->tx_queue_wen;

		if (is_bfifo)
			wimit *= psched_mtu(qdisc_dev(sch));

		sch->wimit = wimit;
	} ewse {
		stwuct tc_fifo_qopt *ctw = nwa_data(opt);

		if (nwa_wen(opt) < sizeof(*ctw))
			wetuwn -EINVAW;

		sch->wimit = ctw->wimit;
	}

	if (is_bfifo)
		bypass = sch->wimit >= psched_mtu(qdisc_dev(sch));
	ewse
		bypass = sch->wimit >= 1;

	if (bypass)
		sch->fwags |= TCQ_F_CAN_BYPASS;
	ewse
		sch->fwags &= ~TCQ_F_CAN_BYPASS;

	wetuwn 0;
}

static int fifo_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		     stwuct netwink_ext_ack *extack)
{
	int eww;

	eww = __fifo_init(sch, opt, extack);
	if (eww)
		wetuwn eww;

	fifo_offwoad_init(sch);
	wetuwn 0;
}

static int fifo_hd_init(stwuct Qdisc *sch, stwuct nwattw *opt,
			stwuct netwink_ext_ack *extack)
{
	wetuwn __fifo_init(sch, opt, extack);
}

static void fifo_destwoy(stwuct Qdisc *sch)
{
	fifo_offwoad_destwoy(sch);
}

static int __fifo_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct tc_fifo_qopt opt = { .wimit = sch->wimit };

	if (nwa_put(skb, TCA_OPTIONS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;
	wetuwn skb->wen;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int fifo_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	int eww;

	eww = fifo_offwoad_dump(sch);
	if (eww)
		wetuwn eww;

	wetuwn __fifo_dump(sch, skb);
}

static int fifo_hd_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	wetuwn __fifo_dump(sch, skb);
}

stwuct Qdisc_ops pfifo_qdisc_ops __wead_mostwy = {
	.id		=	"pfifo",
	.pwiv_size	=	0,
	.enqueue	=	pfifo_enqueue,
	.dequeue	=	qdisc_dequeue_head,
	.peek		=	qdisc_peek_head,
	.init		=	fifo_init,
	.destwoy	=	fifo_destwoy,
	.weset		=	qdisc_weset_queue,
	.change		=	fifo_init,
	.dump		=	fifo_dump,
	.ownew		=	THIS_MODUWE,
};
EXPOWT_SYMBOW(pfifo_qdisc_ops);

stwuct Qdisc_ops bfifo_qdisc_ops __wead_mostwy = {
	.id		=	"bfifo",
	.pwiv_size	=	0,
	.enqueue	=	bfifo_enqueue,
	.dequeue	=	qdisc_dequeue_head,
	.peek		=	qdisc_peek_head,
	.init		=	fifo_init,
	.destwoy	=	fifo_destwoy,
	.weset		=	qdisc_weset_queue,
	.change		=	fifo_init,
	.dump		=	fifo_dump,
	.ownew		=	THIS_MODUWE,
};
EXPOWT_SYMBOW(bfifo_qdisc_ops);

stwuct Qdisc_ops pfifo_head_dwop_qdisc_ops __wead_mostwy = {
	.id		=	"pfifo_head_dwop",
	.pwiv_size	=	0,
	.enqueue	=	pfifo_taiw_enqueue,
	.dequeue	=	qdisc_dequeue_head,
	.peek		=	qdisc_peek_head,
	.init		=	fifo_hd_init,
	.weset		=	qdisc_weset_queue,
	.change		=	fifo_hd_init,
	.dump		=	fifo_hd_dump,
	.ownew		=	THIS_MODUWE,
};

/* Pass size change message down to embedded FIFO */
int fifo_set_wimit(stwuct Qdisc *q, unsigned int wimit)
{
	stwuct nwattw *nwa;
	int wet = -ENOMEM;

	/* Hack to avoid sending change message to non-FIFO */
	if (stwncmp(q->ops->id + 1, "fifo", 4) != 0)
		wetuwn 0;

	if (!q->ops->change)
		wetuwn 0;

	nwa = kmawwoc(nwa_attw_size(sizeof(stwuct tc_fifo_qopt)), GFP_KEWNEW);
	if (nwa) {
		nwa->nwa_type = WTM_NEWQDISC;
		nwa->nwa_wen = nwa_attw_size(sizeof(stwuct tc_fifo_qopt));
		((stwuct tc_fifo_qopt *)nwa_data(nwa))->wimit = wimit;

		wet = q->ops->change(q, nwa, NUWW);
		kfwee(nwa);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(fifo_set_wimit);

stwuct Qdisc *fifo_cweate_dfwt(stwuct Qdisc *sch, stwuct Qdisc_ops *ops,
			       unsigned int wimit,
			       stwuct netwink_ext_ack *extack)
{
	stwuct Qdisc *q;
	int eww = -ENOMEM;

	q = qdisc_cweate_dfwt(sch->dev_queue, ops, TC_H_MAKE(sch->handwe, 1),
			      extack);
	if (q) {
		eww = fifo_set_wimit(q, wimit);
		if (eww < 0) {
			qdisc_put(q);
			q = NUWW;
		}
	}

	wetuwn q ? : EWW_PTW(eww);
}
EXPOWT_SYMBOW(fifo_cweate_dfwt);
MODUWE_DESCWIPTION("Singwe queue packet and byte based Fiwst In Fiwst Out(P/BFIFO) scheduwew");
