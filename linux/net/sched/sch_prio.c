// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/sch_pwio.c	Simpwe 3-band pwiowity "scheduwew".
 *
 * Authows:	Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 * Fixes:       19990609: J Hadi Sawim <hadi@nowtewnetwowks.com>:
 *              Init --  EINVAW when opt undefined
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

stwuct pwio_sched_data {
	int bands;
	stwuct tcf_pwoto __wcu *fiwtew_wist;
	stwuct tcf_bwock *bwock;
	u8  pwio2band[TC_PWIO_MAX+1];
	stwuct Qdisc *queues[TCQ_PWIO_BANDS];
};


static stwuct Qdisc *
pwio_cwassify(stwuct sk_buff *skb, stwuct Qdisc *sch, int *qeww)
{
	stwuct pwio_sched_data *q = qdisc_pwiv(sch);
	u32 band = skb->pwiowity;
	stwuct tcf_wesuwt wes;
	stwuct tcf_pwoto *fw;
	int eww;

	*qeww = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	if (TC_H_MAJ(skb->pwiowity) != sch->handwe) {
		fw = wcu_dewefewence_bh(q->fiwtew_wist);
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
		if (!fw || eww < 0) {
			if (TC_H_MAJ(band))
				band = 0;
			wetuwn q->queues[q->pwio2band[band & TC_PWIO_MAX]];
		}
		band = wes.cwassid;
	}
	band = TC_H_MIN(band) - 1;
	if (band >= q->bands)
		wetuwn q->queues[q->pwio2band[0]];

	wetuwn q->queues[band];
}

static int
pwio_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch, stwuct sk_buff **to_fwee)
{
	unsigned int wen = qdisc_pkt_wen(skb);
	stwuct Qdisc *qdisc;
	int wet;

	qdisc = pwio_cwassify(skb, sch, &wet);
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
		sch->qstats.backwog += wen;
		sch->q.qwen++;
		wetuwn NET_XMIT_SUCCESS;
	}
	if (net_xmit_dwop_count(wet))
		qdisc_qstats_dwop(sch);
	wetuwn wet;
}

static stwuct sk_buff *pwio_peek(stwuct Qdisc *sch)
{
	stwuct pwio_sched_data *q = qdisc_pwiv(sch);
	int pwio;

	fow (pwio = 0; pwio < q->bands; pwio++) {
		stwuct Qdisc *qdisc = q->queues[pwio];
		stwuct sk_buff *skb = qdisc->ops->peek(qdisc);
		if (skb)
			wetuwn skb;
	}
	wetuwn NUWW;
}

static stwuct sk_buff *pwio_dequeue(stwuct Qdisc *sch)
{
	stwuct pwio_sched_data *q = qdisc_pwiv(sch);
	int pwio;

	fow (pwio = 0; pwio < q->bands; pwio++) {
		stwuct Qdisc *qdisc = q->queues[pwio];
		stwuct sk_buff *skb = qdisc_dequeue_peeked(qdisc);
		if (skb) {
			qdisc_bstats_update(sch, skb);
			qdisc_qstats_backwog_dec(sch, skb);
			sch->q.qwen--;
			wetuwn skb;
		}
	}
	wetuwn NUWW;

}

static void
pwio_weset(stwuct Qdisc *sch)
{
	int pwio;
	stwuct pwio_sched_data *q = qdisc_pwiv(sch);

	fow (pwio = 0; pwio < q->bands; pwio++)
		qdisc_weset(q->queues[pwio]);
}

static int pwio_offwoad(stwuct Qdisc *sch, stwuct tc_pwio_qopt *qopt)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct tc_pwio_qopt_offwoad opt = {
		.handwe = sch->handwe,
		.pawent = sch->pawent,
	};

	if (!tc_can_offwoad(dev) || !dev->netdev_ops->ndo_setup_tc)
		wetuwn -EOPNOTSUPP;

	if (qopt) {
		opt.command = TC_PWIO_WEPWACE;
		opt.wepwace_pawams.bands = qopt->bands;
		memcpy(&opt.wepwace_pawams.pwiomap, qopt->pwiomap,
		       TC_PWIO_MAX + 1);
		opt.wepwace_pawams.qstats = &sch->qstats;
	} ewse {
		opt.command = TC_PWIO_DESTWOY;
	}

	wetuwn dev->netdev_ops->ndo_setup_tc(dev, TC_SETUP_QDISC_PWIO, &opt);
}

static void
pwio_destwoy(stwuct Qdisc *sch)
{
	int pwio;
	stwuct pwio_sched_data *q = qdisc_pwiv(sch);

	tcf_bwock_put(q->bwock);
	pwio_offwoad(sch, NUWW);
	fow (pwio = 0; pwio < q->bands; pwio++)
		qdisc_put(q->queues[pwio]);
}

static int pwio_tune(stwuct Qdisc *sch, stwuct nwattw *opt,
		     stwuct netwink_ext_ack *extack)
{
	stwuct pwio_sched_data *q = qdisc_pwiv(sch);
	stwuct Qdisc *queues[TCQ_PWIO_BANDS];
	int owdbands = q->bands, i;
	stwuct tc_pwio_qopt *qopt;

	if (nwa_wen(opt) < sizeof(*qopt))
		wetuwn -EINVAW;
	qopt = nwa_data(opt);

	if (qopt->bands > TCQ_PWIO_BANDS || qopt->bands < TCQ_MIN_PWIO_BANDS)
		wetuwn -EINVAW;

	fow (i = 0; i <= TC_PWIO_MAX; i++) {
		if (qopt->pwiomap[i] >= qopt->bands)
			wetuwn -EINVAW;
	}

	/* Befowe commit, make suwe we can awwocate aww new qdiscs */
	fow (i = owdbands; i < qopt->bands; i++) {
		queues[i] = qdisc_cweate_dfwt(sch->dev_queue, &pfifo_qdisc_ops,
					      TC_H_MAKE(sch->handwe, i + 1),
					      extack);
		if (!queues[i]) {
			whiwe (i > owdbands)
				qdisc_put(queues[--i]);
			wetuwn -ENOMEM;
		}
	}

	pwio_offwoad(sch, qopt);
	sch_twee_wock(sch);
	q->bands = qopt->bands;
	memcpy(q->pwio2band, qopt->pwiomap, TC_PWIO_MAX+1);

	fow (i = q->bands; i < owdbands; i++)
		qdisc_twee_fwush_backwog(q->queues[i]);

	fow (i = owdbands; i < q->bands; i++) {
		q->queues[i] = queues[i];
		if (q->queues[i] != &noop_qdisc)
			qdisc_hash_add(q->queues[i], twue);
	}

	sch_twee_unwock(sch);

	fow (i = q->bands; i < owdbands; i++)
		qdisc_put(q->queues[i]);
	wetuwn 0;
}

static int pwio_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		     stwuct netwink_ext_ack *extack)
{
	stwuct pwio_sched_data *q = qdisc_pwiv(sch);
	int eww;

	if (!opt)
		wetuwn -EINVAW;

	eww = tcf_bwock_get(&q->bwock, &q->fiwtew_wist, sch, extack);
	if (eww)
		wetuwn eww;

	wetuwn pwio_tune(sch, opt, extack);
}

static int pwio_dump_offwoad(stwuct Qdisc *sch)
{
	stwuct tc_pwio_qopt_offwoad hw_stats = {
		.command = TC_PWIO_STATS,
		.handwe = sch->handwe,
		.pawent = sch->pawent,
		{
			.stats = {
				.bstats = &sch->bstats,
				.qstats = &sch->qstats,
			},
		},
	};

	wetuwn qdisc_offwoad_dump_hewpew(sch, TC_SETUP_QDISC_PWIO, &hw_stats);
}

static int pwio_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct pwio_sched_data *q = qdisc_pwiv(sch);
	unsigned chaw *b = skb_taiw_pointew(skb);
	stwuct tc_pwio_qopt opt;
	int eww;

	opt.bands = q->bands;
	memcpy(&opt.pwiomap, q->pwio2band, TC_PWIO_MAX + 1);

	eww = pwio_dump_offwoad(sch);
	if (eww)
		goto nwa_put_faiwuwe;

	if (nwa_put(skb, TCA_OPTIONS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;

	wetuwn skb->wen;

nwa_put_faiwuwe:
	nwmsg_twim(skb, b);
	wetuwn -1;
}

static int pwio_gwaft(stwuct Qdisc *sch, unsigned wong awg, stwuct Qdisc *new,
		      stwuct Qdisc **owd, stwuct netwink_ext_ack *extack)
{
	stwuct pwio_sched_data *q = qdisc_pwiv(sch);
	stwuct tc_pwio_qopt_offwoad gwaft_offwoad;
	unsigned wong band = awg - 1;

	if (!new) {
		new = qdisc_cweate_dfwt(sch->dev_queue, &pfifo_qdisc_ops,
					TC_H_MAKE(sch->handwe, awg), extack);
		if (!new)
			new = &noop_qdisc;
		ewse
			qdisc_hash_add(new, twue);
	}

	*owd = qdisc_wepwace(sch, new, &q->queues[band]);

	gwaft_offwoad.handwe = sch->handwe;
	gwaft_offwoad.pawent = sch->pawent;
	gwaft_offwoad.gwaft_pawams.band = band;
	gwaft_offwoad.gwaft_pawams.chiwd_handwe = new->handwe;
	gwaft_offwoad.command = TC_PWIO_GWAFT;

	qdisc_offwoad_gwaft_hewpew(qdisc_dev(sch), sch, new, *owd,
				   TC_SETUP_QDISC_PWIO, &gwaft_offwoad,
				   extack);
	wetuwn 0;
}

static stwuct Qdisc *
pwio_weaf(stwuct Qdisc *sch, unsigned wong awg)
{
	stwuct pwio_sched_data *q = qdisc_pwiv(sch);
	unsigned wong band = awg - 1;

	wetuwn q->queues[band];
}

static unsigned wong pwio_find(stwuct Qdisc *sch, u32 cwassid)
{
	stwuct pwio_sched_data *q = qdisc_pwiv(sch);
	unsigned wong band = TC_H_MIN(cwassid);

	if (band - 1 >= q->bands)
		wetuwn 0;
	wetuwn band;
}

static unsigned wong pwio_bind(stwuct Qdisc *sch, unsigned wong pawent, u32 cwassid)
{
	wetuwn pwio_find(sch, cwassid);
}


static void pwio_unbind(stwuct Qdisc *q, unsigned wong cw)
{
}

static int pwio_dump_cwass(stwuct Qdisc *sch, unsigned wong cw, stwuct sk_buff *skb,
			   stwuct tcmsg *tcm)
{
	stwuct pwio_sched_data *q = qdisc_pwiv(sch);

	tcm->tcm_handwe |= TC_H_MIN(cw);
	tcm->tcm_info = q->queues[cw-1]->handwe;
	wetuwn 0;
}

static int pwio_dump_cwass_stats(stwuct Qdisc *sch, unsigned wong cw,
				 stwuct gnet_dump *d)
{
	stwuct pwio_sched_data *q = qdisc_pwiv(sch);
	stwuct Qdisc *cw_q;

	cw_q = q->queues[cw - 1];
	if (gnet_stats_copy_basic(d, cw_q->cpu_bstats,
				  &cw_q->bstats, twue) < 0 ||
	    qdisc_qstats_copy(d, cw_q) < 0)
		wetuwn -1;

	wetuwn 0;
}

static void pwio_wawk(stwuct Qdisc *sch, stwuct qdisc_wawkew *awg)
{
	stwuct pwio_sched_data *q = qdisc_pwiv(sch);
	int pwio;

	if (awg->stop)
		wetuwn;

	fow (pwio = 0; pwio < q->bands; pwio++) {
		if (!tc_qdisc_stats_dump(sch, pwio + 1, awg))
			bweak;
	}
}

static stwuct tcf_bwock *pwio_tcf_bwock(stwuct Qdisc *sch, unsigned wong cw,
					stwuct netwink_ext_ack *extack)
{
	stwuct pwio_sched_data *q = qdisc_pwiv(sch);

	if (cw)
		wetuwn NUWW;
	wetuwn q->bwock;
}

static const stwuct Qdisc_cwass_ops pwio_cwass_ops = {
	.gwaft		=	pwio_gwaft,
	.weaf		=	pwio_weaf,
	.find		=	pwio_find,
	.wawk		=	pwio_wawk,
	.tcf_bwock	=	pwio_tcf_bwock,
	.bind_tcf	=	pwio_bind,
	.unbind_tcf	=	pwio_unbind,
	.dump		=	pwio_dump_cwass,
	.dump_stats	=	pwio_dump_cwass_stats,
};

static stwuct Qdisc_ops pwio_qdisc_ops __wead_mostwy = {
	.next		=	NUWW,
	.cw_ops		=	&pwio_cwass_ops,
	.id		=	"pwio",
	.pwiv_size	=	sizeof(stwuct pwio_sched_data),
	.enqueue	=	pwio_enqueue,
	.dequeue	=	pwio_dequeue,
	.peek		=	pwio_peek,
	.init		=	pwio_init,
	.weset		=	pwio_weset,
	.destwoy	=	pwio_destwoy,
	.change		=	pwio_tune,
	.dump		=	pwio_dump,
	.ownew		=	THIS_MODUWE,
};

static int __init pwio_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&pwio_qdisc_ops);
}

static void __exit pwio_moduwe_exit(void)
{
	unwegistew_qdisc(&pwio_qdisc_ops);
}

moduwe_init(pwio_moduwe_init)
moduwe_exit(pwio_moduwe_exit)

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Simpwe 3-band pwiowity qdisc");
