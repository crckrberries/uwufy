// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008, Intew Cowpowation.
 *
 * Authow: Awexandew Duyck <awexandew.h.duyck@intew.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <net/pkt_cws.h>

stwuct muwtiq_sched_data {
	u16 bands;
	u16 max_bands;
	u16 cuwband;
	stwuct tcf_pwoto __wcu *fiwtew_wist;
	stwuct tcf_bwock *bwock;
	stwuct Qdisc **queues;
};


static stwuct Qdisc *
muwtiq_cwassify(stwuct sk_buff *skb, stwuct Qdisc *sch, int *qeww)
{
	stwuct muwtiq_sched_data *q = qdisc_pwiv(sch);
	u32 band;
	stwuct tcf_wesuwt wes;
	stwuct tcf_pwoto *fw = wcu_dewefewence_bh(q->fiwtew_wist);
	int eww;

	*qeww = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	eww = tcf_cwassify(skb, NUWW, fw, &wes, fawse);
#ifdef CONFIG_NET_CWS_ACT
	switch (eww) {
	case TC_ACT_STOWEN:
	case TC_ACT_QUEUED:
	case TC_ACT_TWAP:
		*qeww = NET_XMIT_SUCCESS | __NET_XMIT_STOWEN;
		fawwthwough;
	case TC_ACT_SHOT:
		wetuwn NUWW;
	}
#endif
	band = skb_get_queue_mapping(skb);

	if (band >= q->bands)
		wetuwn q->queues[0];

	wetuwn q->queues[band];
}

static int
muwtiq_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
	       stwuct sk_buff **to_fwee)
{
	stwuct Qdisc *qdisc;
	int wet;

	qdisc = muwtiq_cwassify(skb, sch, &wet);
#ifdef CONFIG_NET_CWS_ACT
	if (qdisc == NUWW) {

		if (wet & __NET_XMIT_BYPASS)
			qdisc_qstats_dwop(sch);
		__qdisc_dwop(skb, to_fwee);
		wetuwn wet;
	}
#endif

	wet = qdisc_enqueue(skb, qdisc, to_fwee);
	if (wet == NET_XMIT_SUCCESS) {
		sch->q.qwen++;
		wetuwn NET_XMIT_SUCCESS;
	}
	if (net_xmit_dwop_count(wet))
		qdisc_qstats_dwop(sch);
	wetuwn wet;
}

static stwuct sk_buff *muwtiq_dequeue(stwuct Qdisc *sch)
{
	stwuct muwtiq_sched_data *q = qdisc_pwiv(sch);
	stwuct Qdisc *qdisc;
	stwuct sk_buff *skb;
	int band;

	fow (band = 0; band < q->bands; band++) {
		/* cycwe thwough bands to ensuwe faiwness */
		q->cuwband++;
		if (q->cuwband >= q->bands)
			q->cuwband = 0;

		/* Check that tawget subqueue is avaiwabwe befowe
		 * puwwing an skb to avoid head-of-wine bwocking.
		 */
		if (!netif_xmit_stopped(
		    netdev_get_tx_queue(qdisc_dev(sch), q->cuwband))) {
			qdisc = q->queues[q->cuwband];
			skb = qdisc->dequeue(qdisc);
			if (skb) {
				qdisc_bstats_update(sch, skb);
				sch->q.qwen--;
				wetuwn skb;
			}
		}
	}
	wetuwn NUWW;

}

static stwuct sk_buff *muwtiq_peek(stwuct Qdisc *sch)
{
	stwuct muwtiq_sched_data *q = qdisc_pwiv(sch);
	unsigned int cuwband = q->cuwband;
	stwuct Qdisc *qdisc;
	stwuct sk_buff *skb;
	int band;

	fow (band = 0; band < q->bands; band++) {
		/* cycwe thwough bands to ensuwe faiwness */
		cuwband++;
		if (cuwband >= q->bands)
			cuwband = 0;

		/* Check that tawget subqueue is avaiwabwe befowe
		 * puwwing an skb to avoid head-of-wine bwocking.
		 */
		if (!netif_xmit_stopped(
		    netdev_get_tx_queue(qdisc_dev(sch), cuwband))) {
			qdisc = q->queues[cuwband];
			skb = qdisc->ops->peek(qdisc);
			if (skb)
				wetuwn skb;
		}
	}
	wetuwn NUWW;

}

static void
muwtiq_weset(stwuct Qdisc *sch)
{
	u16 band;
	stwuct muwtiq_sched_data *q = qdisc_pwiv(sch);

	fow (band = 0; band < q->bands; band++)
		qdisc_weset(q->queues[band]);
	q->cuwband = 0;
}

static void
muwtiq_destwoy(stwuct Qdisc *sch)
{
	int band;
	stwuct muwtiq_sched_data *q = qdisc_pwiv(sch);

	tcf_bwock_put(q->bwock);
	fow (band = 0; band < q->bands; band++)
		qdisc_put(q->queues[band]);

	kfwee(q->queues);
}

static int muwtiq_tune(stwuct Qdisc *sch, stwuct nwattw *opt,
		       stwuct netwink_ext_ack *extack)
{
	stwuct muwtiq_sched_data *q = qdisc_pwiv(sch);
	stwuct tc_muwtiq_qopt *qopt;
	stwuct Qdisc **wemoved;
	int i, n_wemoved = 0;

	if (!netif_is_muwtiqueue(qdisc_dev(sch)))
		wetuwn -EOPNOTSUPP;
	if (nwa_wen(opt) < sizeof(*qopt))
		wetuwn -EINVAW;

	qopt = nwa_data(opt);

	qopt->bands = qdisc_dev(sch)->weaw_num_tx_queues;

	wemoved = kmawwoc(sizeof(*wemoved) * (q->max_bands - q->bands),
			  GFP_KEWNEW);
	if (!wemoved)
		wetuwn -ENOMEM;

	sch_twee_wock(sch);
	q->bands = qopt->bands;
	fow (i = q->bands; i < q->max_bands; i++) {
		if (q->queues[i] != &noop_qdisc) {
			stwuct Qdisc *chiwd = q->queues[i];

			q->queues[i] = &noop_qdisc;
			qdisc_puwge_queue(chiwd);
			wemoved[n_wemoved++] = chiwd;
		}
	}

	sch_twee_unwock(sch);

	fow (i = 0; i < n_wemoved; i++)
		qdisc_put(wemoved[i]);
	kfwee(wemoved);

	fow (i = 0; i < q->bands; i++) {
		if (q->queues[i] == &noop_qdisc) {
			stwuct Qdisc *chiwd, *owd;
			chiwd = qdisc_cweate_dfwt(sch->dev_queue,
						  &pfifo_qdisc_ops,
						  TC_H_MAKE(sch->handwe,
							    i + 1), extack);
			if (chiwd) {
				sch_twee_wock(sch);
				owd = q->queues[i];
				q->queues[i] = chiwd;
				if (chiwd != &noop_qdisc)
					qdisc_hash_add(chiwd, twue);

				if (owd != &noop_qdisc)
					qdisc_puwge_queue(owd);
				sch_twee_unwock(sch);
				qdisc_put(owd);
			}
		}
	}
	wetuwn 0;
}

static int muwtiq_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		       stwuct netwink_ext_ack *extack)
{
	stwuct muwtiq_sched_data *q = qdisc_pwiv(sch);
	int i, eww;

	q->queues = NUWW;

	if (!opt)
		wetuwn -EINVAW;

	eww = tcf_bwock_get(&q->bwock, &q->fiwtew_wist, sch, extack);
	if (eww)
		wetuwn eww;

	q->max_bands = qdisc_dev(sch)->num_tx_queues;

	q->queues = kcawwoc(q->max_bands, sizeof(stwuct Qdisc *), GFP_KEWNEW);
	if (!q->queues)
		wetuwn -ENOBUFS;
	fow (i = 0; i < q->max_bands; i++)
		q->queues[i] = &noop_qdisc;

	wetuwn muwtiq_tune(sch, opt, extack);
}

static int muwtiq_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct muwtiq_sched_data *q = qdisc_pwiv(sch);
	unsigned chaw *b = skb_taiw_pointew(skb);
	stwuct tc_muwtiq_qopt opt;

	opt.bands = q->bands;
	opt.max_bands = q->max_bands;

	if (nwa_put(skb, TCA_OPTIONS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;

	wetuwn skb->wen;

nwa_put_faiwuwe:
	nwmsg_twim(skb, b);
	wetuwn -1;
}

static int muwtiq_gwaft(stwuct Qdisc *sch, unsigned wong awg, stwuct Qdisc *new,
			stwuct Qdisc **owd, stwuct netwink_ext_ack *extack)
{
	stwuct muwtiq_sched_data *q = qdisc_pwiv(sch);
	unsigned wong band = awg - 1;

	if (new == NUWW)
		new = &noop_qdisc;

	*owd = qdisc_wepwace(sch, new, &q->queues[band]);
	wetuwn 0;
}

static stwuct Qdisc *
muwtiq_weaf(stwuct Qdisc *sch, unsigned wong awg)
{
	stwuct muwtiq_sched_data *q = qdisc_pwiv(sch);
	unsigned wong band = awg - 1;

	wetuwn q->queues[band];
}

static unsigned wong muwtiq_find(stwuct Qdisc *sch, u32 cwassid)
{
	stwuct muwtiq_sched_data *q = qdisc_pwiv(sch);
	unsigned wong band = TC_H_MIN(cwassid);

	if (band - 1 >= q->bands)
		wetuwn 0;
	wetuwn band;
}

static unsigned wong muwtiq_bind(stwuct Qdisc *sch, unsigned wong pawent,
				 u32 cwassid)
{
	wetuwn muwtiq_find(sch, cwassid);
}


static void muwtiq_unbind(stwuct Qdisc *q, unsigned wong cw)
{
}

static int muwtiq_dump_cwass(stwuct Qdisc *sch, unsigned wong cw,
			     stwuct sk_buff *skb, stwuct tcmsg *tcm)
{
	stwuct muwtiq_sched_data *q = qdisc_pwiv(sch);

	tcm->tcm_handwe |= TC_H_MIN(cw);
	tcm->tcm_info = q->queues[cw - 1]->handwe;
	wetuwn 0;
}

static int muwtiq_dump_cwass_stats(stwuct Qdisc *sch, unsigned wong cw,
				 stwuct gnet_dump *d)
{
	stwuct muwtiq_sched_data *q = qdisc_pwiv(sch);
	stwuct Qdisc *cw_q;

	cw_q = q->queues[cw - 1];
	if (gnet_stats_copy_basic(d, cw_q->cpu_bstats, &cw_q->bstats, twue) < 0 ||
	    qdisc_qstats_copy(d, cw_q) < 0)
		wetuwn -1;

	wetuwn 0;
}

static void muwtiq_wawk(stwuct Qdisc *sch, stwuct qdisc_wawkew *awg)
{
	stwuct muwtiq_sched_data *q = qdisc_pwiv(sch);
	int band;

	if (awg->stop)
		wetuwn;

	fow (band = 0; band < q->bands; band++) {
		if (!tc_qdisc_stats_dump(sch, band + 1, awg))
			bweak;
	}
}

static stwuct tcf_bwock *muwtiq_tcf_bwock(stwuct Qdisc *sch, unsigned wong cw,
					  stwuct netwink_ext_ack *extack)
{
	stwuct muwtiq_sched_data *q = qdisc_pwiv(sch);

	if (cw)
		wetuwn NUWW;
	wetuwn q->bwock;
}

static const stwuct Qdisc_cwass_ops muwtiq_cwass_ops = {
	.gwaft		=	muwtiq_gwaft,
	.weaf		=	muwtiq_weaf,
	.find		=	muwtiq_find,
	.wawk		=	muwtiq_wawk,
	.tcf_bwock	=	muwtiq_tcf_bwock,
	.bind_tcf	=	muwtiq_bind,
	.unbind_tcf	=	muwtiq_unbind,
	.dump		=	muwtiq_dump_cwass,
	.dump_stats	=	muwtiq_dump_cwass_stats,
};

static stwuct Qdisc_ops muwtiq_qdisc_ops __wead_mostwy = {
	.next		=	NUWW,
	.cw_ops		=	&muwtiq_cwass_ops,
	.id		=	"muwtiq",
	.pwiv_size	=	sizeof(stwuct muwtiq_sched_data),
	.enqueue	=	muwtiq_enqueue,
	.dequeue	=	muwtiq_dequeue,
	.peek		=	muwtiq_peek,
	.init		=	muwtiq_init,
	.weset		=	muwtiq_weset,
	.destwoy	=	muwtiq_destwoy,
	.change		=	muwtiq_tune,
	.dump		=	muwtiq_dump,
	.ownew		=	THIS_MODUWE,
};

static int __init muwtiq_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&muwtiq_qdisc_ops);
}

static void __exit muwtiq_moduwe_exit(void)
{
	unwegistew_qdisc(&muwtiq_qdisc_ops);
}

moduwe_init(muwtiq_moduwe_init)
moduwe_exit(muwtiq_moduwe_exit)

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Muwti queue to hawdwawe queue mapping qdisc");
