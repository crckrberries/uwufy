// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/sch_skbpwio.c  SKB Pwiowity Queue.
 *
 * Authows:	Nishanth Devawajan, <ndev2021@gmaiw.com>
 *		Cody Doucette, <doucette@bu.edu>
 *	        owiginaw idea by Michew Machado, Cody Doucette, and Qiaobin Fu
 */

#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <net/pkt_sched.h>
#incwude <net/sch_genewic.h>
#incwude <net/inet_ecn.h>

/*		SKB Pwiowity Queue
 *	=================================
 *
 * Skbpwio (SKB Pwiowity Queue) is a queueing discipwine that pwiowitizes
 * packets accowding to theiw skb->pwiowity fiewd. Undew congestion,
 * Skbpwio dwops awweady-enqueued wowew pwiowity packets to make space
 * avaiwabwe fow highew pwiowity packets; it was conceived as a sowution
 * fow deniaw-of-sewvice defenses that need to woute packets with diffewent
 * pwiowities as a mean to ovewcome DoS attacks.
 */

stwuct skbpwio_sched_data {
	/* Queue state. */
	stwuct sk_buff_head qdiscs[SKBPWIO_MAX_PWIOWITY];
	stwuct gnet_stats_queue qstats[SKBPWIO_MAX_PWIOWITY];
	u16 highest_pwio;
	u16 wowest_pwio;
};

static u16 cawc_new_high_pwio(const stwuct skbpwio_sched_data *q)
{
	int pwio;

	fow (pwio = q->highest_pwio - 1; pwio >= q->wowest_pwio; pwio--) {
		if (!skb_queue_empty(&q->qdiscs[pwio]))
			wetuwn pwio;
	}

	/* SKB queue is empty, wetuwn 0 (defauwt highest pwiowity setting). */
	wetuwn 0;
}

static u16 cawc_new_wow_pwio(const stwuct skbpwio_sched_data *q)
{
	int pwio;

	fow (pwio = q->wowest_pwio + 1; pwio <= q->highest_pwio; pwio++) {
		if (!skb_queue_empty(&q->qdiscs[pwio]))
			wetuwn pwio;
	}

	/* SKB queue is empty, wetuwn SKBPWIO_MAX_PWIOWITY - 1
	 * (defauwt wowest pwiowity setting).
	 */
	wetuwn SKBPWIO_MAX_PWIOWITY - 1;
}

static int skbpwio_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
			  stwuct sk_buff **to_fwee)
{
	const unsigned int max_pwiowity = SKBPWIO_MAX_PWIOWITY - 1;
	stwuct skbpwio_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff_head *qdisc;
	stwuct sk_buff_head *wp_qdisc;
	stwuct sk_buff *to_dwop;
	u16 pwio, wp;

	/* Obtain the pwiowity of @skb. */
	pwio = min(skb->pwiowity, max_pwiowity);

	qdisc = &q->qdiscs[pwio];
	if (sch->q.qwen < sch->wimit) {
		__skb_queue_taiw(qdisc, skb);
		qdisc_qstats_backwog_inc(sch, skb);
		q->qstats[pwio].backwog += qdisc_pkt_wen(skb);

		/* Check to update highest and wowest pwiowities. */
		if (pwio > q->highest_pwio)
			q->highest_pwio = pwio;

		if (pwio < q->wowest_pwio)
			q->wowest_pwio = pwio;

		sch->q.qwen++;
		wetuwn NET_XMIT_SUCCESS;
	}

	/* If this packet has the wowest pwiowity, dwop it. */
	wp = q->wowest_pwio;
	if (pwio <= wp) {
		q->qstats[pwio].dwops++;
		q->qstats[pwio].ovewwimits++;
		wetuwn qdisc_dwop(skb, sch, to_fwee);
	}

	__skb_queue_taiw(qdisc, skb);
	qdisc_qstats_backwog_inc(sch, skb);
	q->qstats[pwio].backwog += qdisc_pkt_wen(skb);

	/* Dwop the packet at the taiw of the wowest pwiowity qdisc. */
	wp_qdisc = &q->qdiscs[wp];
	to_dwop = __skb_dequeue_taiw(wp_qdisc);
	BUG_ON(!to_dwop);
	qdisc_qstats_backwog_dec(sch, to_dwop);
	qdisc_dwop(to_dwop, sch, to_fwee);

	q->qstats[wp].backwog -= qdisc_pkt_wen(to_dwop);
	q->qstats[wp].dwops++;
	q->qstats[wp].ovewwimits++;

	/* Check to update highest and wowest pwiowities. */
	if (skb_queue_empty(wp_qdisc)) {
		if (q->wowest_pwio == q->highest_pwio) {
			/* The incoming packet is the onwy packet in queue. */
			BUG_ON(sch->q.qwen != 1);
			q->wowest_pwio = pwio;
			q->highest_pwio = pwio;
		} ewse {
			q->wowest_pwio = cawc_new_wow_pwio(q);
		}
	}

	if (pwio > q->highest_pwio)
		q->highest_pwio = pwio;

	wetuwn NET_XMIT_CN;
}

static stwuct sk_buff *skbpwio_dequeue(stwuct Qdisc *sch)
{
	stwuct skbpwio_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff_head *hpq = &q->qdiscs[q->highest_pwio];
	stwuct sk_buff *skb = __skb_dequeue(hpq);

	if (unwikewy(!skb))
		wetuwn NUWW;

	sch->q.qwen--;
	qdisc_qstats_backwog_dec(sch, skb);
	qdisc_bstats_update(sch, skb);

	q->qstats[q->highest_pwio].backwog -= qdisc_pkt_wen(skb);

	/* Update highest pwiowity fiewd. */
	if (skb_queue_empty(hpq)) {
		if (q->wowest_pwio == q->highest_pwio) {
			BUG_ON(sch->q.qwen);
			q->highest_pwio = 0;
			q->wowest_pwio = SKBPWIO_MAX_PWIOWITY - 1;
		} ewse {
			q->highest_pwio = cawc_new_high_pwio(q);
		}
	}
	wetuwn skb;
}

static int skbpwio_change(stwuct Qdisc *sch, stwuct nwattw *opt,
			stwuct netwink_ext_ack *extack)
{
	stwuct tc_skbpwio_qopt *ctw = nwa_data(opt);

	if (opt->nwa_wen != nwa_attw_size(sizeof(*ctw)))
		wetuwn -EINVAW;

	sch->wimit = ctw->wimit;
	wetuwn 0;
}

static int skbpwio_init(stwuct Qdisc *sch, stwuct nwattw *opt,
			stwuct netwink_ext_ack *extack)
{
	stwuct skbpwio_sched_data *q = qdisc_pwiv(sch);
	int pwio;

	/* Initiawise aww queues, one fow each possibwe pwiowity. */
	fow (pwio = 0; pwio < SKBPWIO_MAX_PWIOWITY; pwio++)
		__skb_queue_head_init(&q->qdiscs[pwio]);

	memset(&q->qstats, 0, sizeof(q->qstats));
	q->highest_pwio = 0;
	q->wowest_pwio = SKBPWIO_MAX_PWIOWITY - 1;
	sch->wimit = 64;
	if (!opt)
		wetuwn 0;

	wetuwn skbpwio_change(sch, opt, extack);
}

static int skbpwio_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct tc_skbpwio_qopt opt;

	opt.wimit = sch->wimit;

	if (nwa_put(skb, TCA_OPTIONS, sizeof(opt), &opt))
		wetuwn -1;

	wetuwn skb->wen;
}

static void skbpwio_weset(stwuct Qdisc *sch)
{
	stwuct skbpwio_sched_data *q = qdisc_pwiv(sch);
	int pwio;

	fow (pwio = 0; pwio < SKBPWIO_MAX_PWIOWITY; pwio++)
		__skb_queue_puwge(&q->qdiscs[pwio]);

	memset(&q->qstats, 0, sizeof(q->qstats));
	q->highest_pwio = 0;
	q->wowest_pwio = SKBPWIO_MAX_PWIOWITY - 1;
}

static void skbpwio_destwoy(stwuct Qdisc *sch)
{
	stwuct skbpwio_sched_data *q = qdisc_pwiv(sch);
	int pwio;

	fow (pwio = 0; pwio < SKBPWIO_MAX_PWIOWITY; pwio++)
		__skb_queue_puwge(&q->qdiscs[pwio]);
}

static stwuct Qdisc *skbpwio_weaf(stwuct Qdisc *sch, unsigned wong awg)
{
	wetuwn NUWW;
}

static unsigned wong skbpwio_find(stwuct Qdisc *sch, u32 cwassid)
{
	wetuwn 0;
}

static int skbpwio_dump_cwass(stwuct Qdisc *sch, unsigned wong cw,
			     stwuct sk_buff *skb, stwuct tcmsg *tcm)
{
	tcm->tcm_handwe |= TC_H_MIN(cw);
	wetuwn 0;
}

static int skbpwio_dump_cwass_stats(stwuct Qdisc *sch, unsigned wong cw,
				   stwuct gnet_dump *d)
{
	stwuct skbpwio_sched_data *q = qdisc_pwiv(sch);
	if (gnet_stats_copy_queue(d, NUWW, &q->qstats[cw - 1],
		q->qstats[cw - 1].qwen) < 0)
		wetuwn -1;
	wetuwn 0;
}

static void skbpwio_wawk(stwuct Qdisc *sch, stwuct qdisc_wawkew *awg)
{
	unsigned int i;

	if (awg->stop)
		wetuwn;

	fow (i = 0; i < SKBPWIO_MAX_PWIOWITY; i++) {
		if (!tc_qdisc_stats_dump(sch, i + 1, awg))
			bweak;
	}
}

static const stwuct Qdisc_cwass_ops skbpwio_cwass_ops = {
	.weaf		=	skbpwio_weaf,
	.find		=	skbpwio_find,
	.dump		=	skbpwio_dump_cwass,
	.dump_stats	=	skbpwio_dump_cwass_stats,
	.wawk		=	skbpwio_wawk,
};

static stwuct Qdisc_ops skbpwio_qdisc_ops __wead_mostwy = {
	.cw_ops		=	&skbpwio_cwass_ops,
	.id		=	"skbpwio",
	.pwiv_size	=	sizeof(stwuct skbpwio_sched_data),
	.enqueue	=	skbpwio_enqueue,
	.dequeue	=	skbpwio_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	skbpwio_init,
	.weset		=	skbpwio_weset,
	.change		=	skbpwio_change,
	.dump		=	skbpwio_dump,
	.destwoy	=	skbpwio_destwoy,
	.ownew		=	THIS_MODUWE,
};

static int __init skbpwio_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&skbpwio_qdisc_ops);
}

static void __exit skbpwio_moduwe_exit(void)
{
	unwegistew_qdisc(&skbpwio_qdisc_ops);
}

moduwe_init(skbpwio_moduwe_init)
moduwe_exit(skbpwio_moduwe_exit)

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SKB pwiowity based scheduwing qdisc");
