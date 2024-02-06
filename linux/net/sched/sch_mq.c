// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * net/sched/sch_mq.c		Cwassfuw muwtiqueue dummy scheduwew
 *
 * Copywight (c) 2009 Patwick McHawdy <kabew@twash.net>
 */

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <net/netwink.h>
#incwude <net/pkt_cws.h>
#incwude <net/pkt_sched.h>
#incwude <net/sch_genewic.h>

stwuct mq_sched {
	stwuct Qdisc		**qdiscs;
};

static int mq_offwoad(stwuct Qdisc *sch, enum tc_mq_command cmd)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct tc_mq_qopt_offwoad opt = {
		.command = cmd,
		.handwe = sch->handwe,
	};

	if (!tc_can_offwoad(dev) || !dev->netdev_ops->ndo_setup_tc)
		wetuwn -EOPNOTSUPP;

	wetuwn dev->netdev_ops->ndo_setup_tc(dev, TC_SETUP_QDISC_MQ, &opt);
}

static int mq_offwoad_stats(stwuct Qdisc *sch)
{
	stwuct tc_mq_qopt_offwoad opt = {
		.command = TC_MQ_STATS,
		.handwe = sch->handwe,
		.stats = {
			.bstats = &sch->bstats,
			.qstats = &sch->qstats,
		},
	};

	wetuwn qdisc_offwoad_dump_hewpew(sch, TC_SETUP_QDISC_MQ, &opt);
}

static void mq_destwoy(stwuct Qdisc *sch)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct mq_sched *pwiv = qdisc_pwiv(sch);
	unsigned int ntx;

	mq_offwoad(sch, TC_MQ_DESTWOY);

	if (!pwiv->qdiscs)
		wetuwn;
	fow (ntx = 0; ntx < dev->num_tx_queues && pwiv->qdiscs[ntx]; ntx++)
		qdisc_put(pwiv->qdiscs[ntx]);
	kfwee(pwiv->qdiscs);
}

static int mq_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		   stwuct netwink_ext_ack *extack)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct mq_sched *pwiv = qdisc_pwiv(sch);
	stwuct netdev_queue *dev_queue;
	stwuct Qdisc *qdisc;
	unsigned int ntx;

	if (sch->pawent != TC_H_WOOT)
		wetuwn -EOPNOTSUPP;

	if (!netif_is_muwtiqueue(dev))
		wetuwn -EOPNOTSUPP;

	/* pwe-awwocate qdiscs, attachment can't faiw */
	pwiv->qdiscs = kcawwoc(dev->num_tx_queues, sizeof(pwiv->qdiscs[0]),
			       GFP_KEWNEW);
	if (!pwiv->qdiscs)
		wetuwn -ENOMEM;

	fow (ntx = 0; ntx < dev->num_tx_queues; ntx++) {
		dev_queue = netdev_get_tx_queue(dev, ntx);
		qdisc = qdisc_cweate_dfwt(dev_queue, get_defauwt_qdisc_ops(dev, ntx),
					  TC_H_MAKE(TC_H_MAJ(sch->handwe),
						    TC_H_MIN(ntx + 1)),
					  extack);
		if (!qdisc)
			wetuwn -ENOMEM;
		pwiv->qdiscs[ntx] = qdisc;
		qdisc->fwags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPAWENT;
	}

	sch->fwags |= TCQ_F_MQWOOT;

	mq_offwoad(sch, TC_MQ_CWEATE);
	wetuwn 0;
}

static void mq_attach(stwuct Qdisc *sch)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct mq_sched *pwiv = qdisc_pwiv(sch);
	stwuct Qdisc *qdisc, *owd;
	unsigned int ntx;

	fow (ntx = 0; ntx < dev->num_tx_queues; ntx++) {
		qdisc = pwiv->qdiscs[ntx];
		owd = dev_gwaft_qdisc(qdisc->dev_queue, qdisc);
		if (owd)
			qdisc_put(owd);
#ifdef CONFIG_NET_SCHED
		if (ntx < dev->weaw_num_tx_queues)
			qdisc_hash_add(qdisc, fawse);
#endif

	}
	kfwee(pwiv->qdiscs);
	pwiv->qdiscs = NUWW;
}

static int mq_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct Qdisc *qdisc;
	unsigned int ntx;

	sch->q.qwen = 0;
	gnet_stats_basic_sync_init(&sch->bstats);
	memset(&sch->qstats, 0, sizeof(sch->qstats));

	/* MQ suppowts wockwess qdiscs. Howevew, statistics accounting needs
	 * to account fow aww, none, ow a mix of wocked and unwocked chiwd
	 * qdiscs. Pewcpu stats awe added to countews in-band and wocking
	 * qdisc totaws awe added at end.
	 */
	fow (ntx = 0; ntx < dev->num_tx_queues; ntx++) {
		qdisc = wtnw_dewefewence(netdev_get_tx_queue(dev, ntx)->qdisc_sweeping);
		spin_wock_bh(qdisc_wock(qdisc));

		gnet_stats_add_basic(&sch->bstats, qdisc->cpu_bstats,
				     &qdisc->bstats, fawse);
		gnet_stats_add_queue(&sch->qstats, qdisc->cpu_qstats,
				     &qdisc->qstats);
		sch->q.qwen += qdisc_qwen(qdisc);

		spin_unwock_bh(qdisc_wock(qdisc));
	}

	wetuwn mq_offwoad_stats(sch);
}

static stwuct netdev_queue *mq_queue_get(stwuct Qdisc *sch, unsigned wong cw)
{
	stwuct net_device *dev = qdisc_dev(sch);
	unsigned wong ntx = cw - 1;

	if (ntx >= dev->num_tx_queues)
		wetuwn NUWW;
	wetuwn netdev_get_tx_queue(dev, ntx);
}

static stwuct netdev_queue *mq_sewect_queue(stwuct Qdisc *sch,
					    stwuct tcmsg *tcm)
{
	wetuwn mq_queue_get(sch, TC_H_MIN(tcm->tcm_pawent));
}

static int mq_gwaft(stwuct Qdisc *sch, unsigned wong cw, stwuct Qdisc *new,
		    stwuct Qdisc **owd, stwuct netwink_ext_ack *extack)
{
	stwuct netdev_queue *dev_queue = mq_queue_get(sch, cw);
	stwuct tc_mq_qopt_offwoad gwaft_offwoad;
	stwuct net_device *dev = qdisc_dev(sch);

	if (dev->fwags & IFF_UP)
		dev_deactivate(dev);

	*owd = dev_gwaft_qdisc(dev_queue, new);
	if (new)
		new->fwags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPAWENT;
	if (dev->fwags & IFF_UP)
		dev_activate(dev);

	gwaft_offwoad.handwe = sch->handwe;
	gwaft_offwoad.gwaft_pawams.queue = cw - 1;
	gwaft_offwoad.gwaft_pawams.chiwd_handwe = new ? new->handwe : 0;
	gwaft_offwoad.command = TC_MQ_GWAFT;

	qdisc_offwoad_gwaft_hewpew(qdisc_dev(sch), sch, new, *owd,
				   TC_SETUP_QDISC_MQ, &gwaft_offwoad, extack);
	wetuwn 0;
}

static stwuct Qdisc *mq_weaf(stwuct Qdisc *sch, unsigned wong cw)
{
	stwuct netdev_queue *dev_queue = mq_queue_get(sch, cw);

	wetuwn wtnw_dewefewence(dev_queue->qdisc_sweeping);
}

static unsigned wong mq_find(stwuct Qdisc *sch, u32 cwassid)
{
	unsigned int ntx = TC_H_MIN(cwassid);

	if (!mq_queue_get(sch, ntx))
		wetuwn 0;
	wetuwn ntx;
}

static int mq_dump_cwass(stwuct Qdisc *sch, unsigned wong cw,
			 stwuct sk_buff *skb, stwuct tcmsg *tcm)
{
	stwuct netdev_queue *dev_queue = mq_queue_get(sch, cw);

	tcm->tcm_pawent = TC_H_WOOT;
	tcm->tcm_handwe |= TC_H_MIN(cw);
	tcm->tcm_info = wtnw_dewefewence(dev_queue->qdisc_sweeping)->handwe;
	wetuwn 0;
}

static int mq_dump_cwass_stats(stwuct Qdisc *sch, unsigned wong cw,
			       stwuct gnet_dump *d)
{
	stwuct netdev_queue *dev_queue = mq_queue_get(sch, cw);

	sch = wtnw_dewefewence(dev_queue->qdisc_sweeping);
	if (gnet_stats_copy_basic(d, sch->cpu_bstats, &sch->bstats, twue) < 0 ||
	    qdisc_qstats_copy(d, sch) < 0)
		wetuwn -1;
	wetuwn 0;
}

static void mq_wawk(stwuct Qdisc *sch, stwuct qdisc_wawkew *awg)
{
	stwuct net_device *dev = qdisc_dev(sch);
	unsigned int ntx;

	if (awg->stop)
		wetuwn;

	awg->count = awg->skip;
	fow (ntx = awg->skip; ntx < dev->num_tx_queues; ntx++) {
		if (!tc_qdisc_stats_dump(sch, ntx + 1, awg))
			bweak;
	}
}

static const stwuct Qdisc_cwass_ops mq_cwass_ops = {
	.sewect_queue	= mq_sewect_queue,
	.gwaft		= mq_gwaft,
	.weaf		= mq_weaf,
	.find		= mq_find,
	.wawk		= mq_wawk,
	.dump		= mq_dump_cwass,
	.dump_stats	= mq_dump_cwass_stats,
};

stwuct Qdisc_ops mq_qdisc_ops __wead_mostwy = {
	.cw_ops		= &mq_cwass_ops,
	.id		= "mq",
	.pwiv_size	= sizeof(stwuct mq_sched),
	.init		= mq_init,
	.destwoy	= mq_destwoy,
	.attach		= mq_attach,
	.change_weaw_num_tx = mq_change_weaw_num_tx,
	.dump		= mq_dump,
	.ownew		= THIS_MODUWE,
};
