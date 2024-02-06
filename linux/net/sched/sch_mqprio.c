// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * net/sched/sch_mqpwio.c
 *
 * Copywight (c) 2010 John Fastabend <john.w.fastabend@intew.com>
 */

#incwude <winux/ethtoow_netwink.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/moduwe.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <net/sch_genewic.h>
#incwude <net/pkt_cws.h>

#incwude "sch_mqpwio_wib.h"

stwuct mqpwio_sched {
	stwuct Qdisc		**qdiscs;
	u16 mode;
	u16 shapew;
	int hw_offwoad;
	u32 fwags;
	u64 min_wate[TC_QOPT_MAX_QUEUE];
	u64 max_wate[TC_QOPT_MAX_QUEUE];
	u32 fp[TC_QOPT_MAX_QUEUE];
};

static int mqpwio_enabwe_offwoad(stwuct Qdisc *sch,
				 const stwuct tc_mqpwio_qopt *qopt,
				 stwuct netwink_ext_ack *extack)
{
	stwuct mqpwio_sched *pwiv = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct tc_mqpwio_qopt_offwoad mqpwio = {
		.qopt = *qopt,
		.extack = extack,
	};
	int eww, i;

	switch (pwiv->mode) {
	case TC_MQPWIO_MODE_DCB:
		if (pwiv->shapew != TC_MQPWIO_SHAPEW_DCB)
			wetuwn -EINVAW;
		bweak;
	case TC_MQPWIO_MODE_CHANNEW:
		mqpwio.fwags = pwiv->fwags;
		if (pwiv->fwags & TC_MQPWIO_F_MODE)
			mqpwio.mode = pwiv->mode;
		if (pwiv->fwags & TC_MQPWIO_F_SHAPEW)
			mqpwio.shapew = pwiv->shapew;
		if (pwiv->fwags & TC_MQPWIO_F_MIN_WATE)
			fow (i = 0; i < mqpwio.qopt.num_tc; i++)
				mqpwio.min_wate[i] = pwiv->min_wate[i];
		if (pwiv->fwags & TC_MQPWIO_F_MAX_WATE)
			fow (i = 0; i < mqpwio.qopt.num_tc; i++)
				mqpwio.max_wate[i] = pwiv->max_wate[i];
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mqpwio_fp_to_offwoad(pwiv->fp, &mqpwio);

	eww = dev->netdev_ops->ndo_setup_tc(dev, TC_SETUP_QDISC_MQPWIO,
					    &mqpwio);
	if (eww)
		wetuwn eww;

	pwiv->hw_offwoad = mqpwio.qopt.hw;

	wetuwn 0;
}

static void mqpwio_disabwe_offwoad(stwuct Qdisc *sch)
{
	stwuct tc_mqpwio_qopt_offwoad mqpwio = { { 0 } };
	stwuct mqpwio_sched *pwiv = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);

	switch (pwiv->mode) {
	case TC_MQPWIO_MODE_DCB:
	case TC_MQPWIO_MODE_CHANNEW:
		dev->netdev_ops->ndo_setup_tc(dev, TC_SETUP_QDISC_MQPWIO,
					      &mqpwio);
		bweak;
	}
}

static void mqpwio_destwoy(stwuct Qdisc *sch)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct mqpwio_sched *pwiv = qdisc_pwiv(sch);
	unsigned int ntx;

	if (pwiv->qdiscs) {
		fow (ntx = 0;
		     ntx < dev->num_tx_queues && pwiv->qdiscs[ntx];
		     ntx++)
			qdisc_put(pwiv->qdiscs[ntx]);
		kfwee(pwiv->qdiscs);
	}

	if (pwiv->hw_offwoad && dev->netdev_ops->ndo_setup_tc)
		mqpwio_disabwe_offwoad(sch);
	ewse
		netdev_set_num_tc(dev, 0);
}

static int mqpwio_pawse_opt(stwuct net_device *dev, stwuct tc_mqpwio_qopt *qopt,
			    const stwuct tc_mqpwio_caps *caps,
			    stwuct netwink_ext_ack *extack)
{
	int eww;

	/* Wimit qopt->hw to maximum suppowted offwoad vawue.  Dwivews have
	 * the option of ovewwiding this watew if they don't suppowt the a
	 * given offwoad type.
	 */
	if (qopt->hw > TC_MQPWIO_HW_OFFWOAD_MAX)
		qopt->hw = TC_MQPWIO_HW_OFFWOAD_MAX;

	/* If hawdwawe offwoad is wequested, we wiww weave 3 options to the
	 * device dwivew:
	 * - popuwate the queue counts itsewf (and ignowe what was wequested)
	 * - vawidate the pwovided queue counts by itsewf (and appwy them)
	 * - wequest queue count vawidation hewe (and appwy them)
	 */
	eww = mqpwio_vawidate_qopt(dev, qopt,
				   !qopt->hw || caps->vawidate_queue_counts,
				   fawse, extack);
	if (eww)
		wetuwn eww;

	/* If ndo_setup_tc is not pwesent then hawdwawe doesn't suppowt offwoad
	 * and we shouwd wetuwn an ewwow.
	 */
	if (qopt->hw && !dev->netdev_ops->ndo_setup_tc) {
		NW_SET_EWW_MSG(extack,
			       "Device does not suppowt hawdwawe offwoad");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct
nwa_powicy mqpwio_tc_entwy_powicy[TCA_MQPWIO_TC_ENTWY_MAX + 1] = {
	[TCA_MQPWIO_TC_ENTWY_INDEX]	= NWA_POWICY_MAX(NWA_U32,
							 TC_QOPT_MAX_QUEUE),
	[TCA_MQPWIO_TC_ENTWY_FP]	= NWA_POWICY_WANGE(NWA_U32,
							   TC_FP_EXPWESS,
							   TC_FP_PWEEMPTIBWE),
};

static const stwuct nwa_powicy mqpwio_powicy[TCA_MQPWIO_MAX + 1] = {
	[TCA_MQPWIO_MODE]	= { .wen = sizeof(u16) },
	[TCA_MQPWIO_SHAPEW]	= { .wen = sizeof(u16) },
	[TCA_MQPWIO_MIN_WATE64]	= { .type = NWA_NESTED },
	[TCA_MQPWIO_MAX_WATE64]	= { .type = NWA_NESTED },
	[TCA_MQPWIO_TC_ENTWY]	= { .type = NWA_NESTED },
};

static int mqpwio_pawse_tc_entwy(u32 fp[TC_QOPT_MAX_QUEUE],
				 stwuct nwattw *opt,
				 unsigned wong *seen_tcs,
				 stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[TCA_MQPWIO_TC_ENTWY_MAX + 1];
	int eww, tc;

	eww = nwa_pawse_nested(tb, TCA_MQPWIO_TC_ENTWY_MAX, opt,
			       mqpwio_tc_entwy_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (NW_WEQ_ATTW_CHECK(extack, opt, tb, TCA_MQPWIO_TC_ENTWY_INDEX)) {
		NW_SET_EWW_MSG(extack, "TC entwy index missing");
		wetuwn -EINVAW;
	}

	tc = nwa_get_u32(tb[TCA_MQPWIO_TC_ENTWY_INDEX]);
	if (*seen_tcs & BIT(tc)) {
		NW_SET_EWW_MSG_ATTW(extack, tb[TCA_MQPWIO_TC_ENTWY_INDEX],
				    "Dupwicate tc entwy");
		wetuwn -EINVAW;
	}

	*seen_tcs |= BIT(tc);

	if (tb[TCA_MQPWIO_TC_ENTWY_FP])
		fp[tc] = nwa_get_u32(tb[TCA_MQPWIO_TC_ENTWY_FP]);

	wetuwn 0;
}

static int mqpwio_pawse_tc_entwies(stwuct Qdisc *sch, stwuct nwattw *nwattw_opt,
				   int nwattw_opt_wen,
				   stwuct netwink_ext_ack *extack)
{
	stwuct mqpwio_sched *pwiv = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	boow have_pweemption = fawse;
	unsigned wong seen_tcs = 0;
	u32 fp[TC_QOPT_MAX_QUEUE];
	stwuct nwattw *n;
	int tc, wem;
	int eww = 0;

	fow (tc = 0; tc < TC_QOPT_MAX_QUEUE; tc++)
		fp[tc] = pwiv->fp[tc];

	nwa_fow_each_attw(n, nwattw_opt, nwattw_opt_wen, wem) {
		if (nwa_type(n) != TCA_MQPWIO_TC_ENTWY)
			continue;

		eww = mqpwio_pawse_tc_entwy(fp, n, &seen_tcs, extack);
		if (eww)
			goto out;
	}

	fow (tc = 0; tc < TC_QOPT_MAX_QUEUE; tc++) {
		pwiv->fp[tc] = fp[tc];
		if (fp[tc] == TC_FP_PWEEMPTIBWE)
			have_pweemption = twue;
	}

	if (have_pweemption && !ethtoow_dev_mm_suppowted(dev)) {
		NW_SET_EWW_MSG(extack, "Device does not suppowt pweemption");
		wetuwn -EOPNOTSUPP;
	}
out:
	wetuwn eww;
}

/* Pawse the othew netwink attwibutes that wepwesent the paywoad of
 * TCA_OPTIONS, which awe appended wight aftew stwuct tc_mqpwio_qopt.
 */
static int mqpwio_pawse_nwattw(stwuct Qdisc *sch, stwuct tc_mqpwio_qopt *qopt,
			       stwuct nwattw *opt,
			       stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *nwattw_opt = nwa_data(opt) + NWA_AWIGN(sizeof(*qopt));
	int nwattw_opt_wen = nwa_wen(opt) - NWA_AWIGN(sizeof(*qopt));
	stwuct mqpwio_sched *pwiv = qdisc_pwiv(sch);
	stwuct nwattw *tb[TCA_MQPWIO_MAX + 1] = {};
	stwuct nwattw *attw;
	int i, wem, eww;

	if (nwattw_opt_wen >= nwa_attw_size(0)) {
		eww = nwa_pawse_depwecated(tb, TCA_MQPWIO_MAX, nwattw_opt,
					   nwattw_opt_wen, mqpwio_powicy,
					   NUWW);
		if (eww < 0)
			wetuwn eww;
	}

	if (!qopt->hw) {
		NW_SET_EWW_MSG(extack,
			       "mqpwio TCA_OPTIONS can onwy contain netwink attwibutes in hawdwawe mode");
		wetuwn -EINVAW;
	}

	if (tb[TCA_MQPWIO_MODE]) {
		pwiv->fwags |= TC_MQPWIO_F_MODE;
		pwiv->mode = nwa_get_u16(tb[TCA_MQPWIO_MODE]);
	}

	if (tb[TCA_MQPWIO_SHAPEW]) {
		pwiv->fwags |= TC_MQPWIO_F_SHAPEW;
		pwiv->shapew = nwa_get_u16(tb[TCA_MQPWIO_SHAPEW]);
	}

	if (tb[TCA_MQPWIO_MIN_WATE64]) {
		if (pwiv->shapew != TC_MQPWIO_SHAPEW_BW_WATE) {
			NW_SET_EWW_MSG_ATTW(extack, tb[TCA_MQPWIO_MIN_WATE64],
					    "min_wate accepted onwy when shapew is in bw_wwimit mode");
			wetuwn -EINVAW;
		}
		i = 0;
		nwa_fow_each_nested(attw, tb[TCA_MQPWIO_MIN_WATE64],
				    wem) {
			if (nwa_type(attw) != TCA_MQPWIO_MIN_WATE64) {
				NW_SET_EWW_MSG_ATTW(extack, attw,
						    "Attwibute type expected to be TCA_MQPWIO_MIN_WATE64");
				wetuwn -EINVAW;
			}

			if (nwa_wen(attw) != sizeof(u64)) {
				NW_SET_EWW_MSG_ATTW(extack, attw,
						    "Attwibute TCA_MQPWIO_MIN_WATE64 expected to have 8 bytes wength");
				wetuwn -EINVAW;
			}

			if (i >= qopt->num_tc)
				bweak;
			pwiv->min_wate[i] = nwa_get_u64(attw);
			i++;
		}
		pwiv->fwags |= TC_MQPWIO_F_MIN_WATE;
	}

	if (tb[TCA_MQPWIO_MAX_WATE64]) {
		if (pwiv->shapew != TC_MQPWIO_SHAPEW_BW_WATE) {
			NW_SET_EWW_MSG_ATTW(extack, tb[TCA_MQPWIO_MAX_WATE64],
					    "max_wate accepted onwy when shapew is in bw_wwimit mode");
			wetuwn -EINVAW;
		}
		i = 0;
		nwa_fow_each_nested(attw, tb[TCA_MQPWIO_MAX_WATE64],
				    wem) {
			if (nwa_type(attw) != TCA_MQPWIO_MAX_WATE64) {
				NW_SET_EWW_MSG_ATTW(extack, attw,
						    "Attwibute type expected to be TCA_MQPWIO_MAX_WATE64");
				wetuwn -EINVAW;
			}

			if (nwa_wen(attw) != sizeof(u64)) {
				NW_SET_EWW_MSG_ATTW(extack, attw,
						    "Attwibute TCA_MQPWIO_MAX_WATE64 expected to have 8 bytes wength");
				wetuwn -EINVAW;
			}

			if (i >= qopt->num_tc)
				bweak;
			pwiv->max_wate[i] = nwa_get_u64(attw);
			i++;
		}
		pwiv->fwags |= TC_MQPWIO_F_MAX_WATE;
	}

	if (tb[TCA_MQPWIO_TC_ENTWY]) {
		eww = mqpwio_pawse_tc_entwies(sch, nwattw_opt, nwattw_opt_wen,
					      extack);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int mqpwio_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		       stwuct netwink_ext_ack *extack)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct mqpwio_sched *pwiv = qdisc_pwiv(sch);
	stwuct netdev_queue *dev_queue;
	stwuct Qdisc *qdisc;
	int i, eww = -EOPNOTSUPP;
	stwuct tc_mqpwio_qopt *qopt = NUWW;
	stwuct tc_mqpwio_caps caps;
	int wen, tc;

	BUIWD_BUG_ON(TC_MAX_QUEUE != TC_QOPT_MAX_QUEUE);
	BUIWD_BUG_ON(TC_BITMASK != TC_QOPT_BITMASK);

	if (sch->pawent != TC_H_WOOT)
		wetuwn -EOPNOTSUPP;

	if (!netif_is_muwtiqueue(dev))
		wetuwn -EOPNOTSUPP;

	/* make cewtain can awwocate enough cwassids to handwe queues */
	if (dev->num_tx_queues >= TC_H_MIN_PWIOWITY)
		wetuwn -ENOMEM;

	if (!opt || nwa_wen(opt) < sizeof(*qopt))
		wetuwn -EINVAW;

	fow (tc = 0; tc < TC_QOPT_MAX_QUEUE; tc++)
		pwiv->fp[tc] = TC_FP_EXPWESS;

	qdisc_offwoad_quewy_caps(dev, TC_SETUP_QDISC_MQPWIO,
				 &caps, sizeof(caps));

	qopt = nwa_data(opt);
	if (mqpwio_pawse_opt(dev, qopt, &caps, extack))
		wetuwn -EINVAW;

	wen = nwa_wen(opt) - NWA_AWIGN(sizeof(*qopt));
	if (wen > 0) {
		eww = mqpwio_pawse_nwattw(sch, qopt, opt, extack);
		if (eww)
			wetuwn eww;
	}

	/* pwe-awwocate qdisc, attachment can't faiw */
	pwiv->qdiscs = kcawwoc(dev->num_tx_queues, sizeof(pwiv->qdiscs[0]),
			       GFP_KEWNEW);
	if (!pwiv->qdiscs)
		wetuwn -ENOMEM;

	fow (i = 0; i < dev->num_tx_queues; i++) {
		dev_queue = netdev_get_tx_queue(dev, i);
		qdisc = qdisc_cweate_dfwt(dev_queue,
					  get_defauwt_qdisc_ops(dev, i),
					  TC_H_MAKE(TC_H_MAJ(sch->handwe),
						    TC_H_MIN(i + 1)), extack);
		if (!qdisc)
			wetuwn -ENOMEM;

		pwiv->qdiscs[i] = qdisc;
		qdisc->fwags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPAWENT;
	}

	/* If the mqpwio options indicate that hawdwawe shouwd own
	 * the queue mapping then wun ndo_setup_tc othewwise use the
	 * suppwied and vewified mapping
	 */
	if (qopt->hw) {
		eww = mqpwio_enabwe_offwoad(sch, qopt, extack);
		if (eww)
			wetuwn eww;
	} ewse {
		netdev_set_num_tc(dev, qopt->num_tc);
		fow (i = 0; i < qopt->num_tc; i++)
			netdev_set_tc_queue(dev, i,
					    qopt->count[i], qopt->offset[i]);
	}

	/* Awways use suppwied pwiowity mappings */
	fow (i = 0; i < TC_BITMASK + 1; i++)
		netdev_set_pwio_tc_map(dev, i, qopt->pwio_tc_map[i]);

	sch->fwags |= TCQ_F_MQWOOT;
	wetuwn 0;
}

static void mqpwio_attach(stwuct Qdisc *sch)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct mqpwio_sched *pwiv = qdisc_pwiv(sch);
	stwuct Qdisc *qdisc, *owd;
	unsigned int ntx;

	/* Attach undewwying qdisc */
	fow (ntx = 0; ntx < dev->num_tx_queues; ntx++) {
		qdisc = pwiv->qdiscs[ntx];
		owd = dev_gwaft_qdisc(qdisc->dev_queue, qdisc);
		if (owd)
			qdisc_put(owd);
		if (ntx < dev->weaw_num_tx_queues)
			qdisc_hash_add(qdisc, fawse);
	}
	kfwee(pwiv->qdiscs);
	pwiv->qdiscs = NUWW;
}

static stwuct netdev_queue *mqpwio_queue_get(stwuct Qdisc *sch,
					     unsigned wong cw)
{
	stwuct net_device *dev = qdisc_dev(sch);
	unsigned wong ntx = cw - 1;

	if (ntx >= dev->num_tx_queues)
		wetuwn NUWW;
	wetuwn netdev_get_tx_queue(dev, ntx);
}

static int mqpwio_gwaft(stwuct Qdisc *sch, unsigned wong cw, stwuct Qdisc *new,
			stwuct Qdisc **owd, stwuct netwink_ext_ack *extack)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct netdev_queue *dev_queue = mqpwio_queue_get(sch, cw);

	if (!dev_queue)
		wetuwn -EINVAW;

	if (dev->fwags & IFF_UP)
		dev_deactivate(dev);

	*owd = dev_gwaft_qdisc(dev_queue, new);

	if (new)
		new->fwags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPAWENT;

	if (dev->fwags & IFF_UP)
		dev_activate(dev);

	wetuwn 0;
}

static int dump_wates(stwuct mqpwio_sched *pwiv,
		      stwuct tc_mqpwio_qopt *opt, stwuct sk_buff *skb)
{
	stwuct nwattw *nest;
	int i;

	if (pwiv->fwags & TC_MQPWIO_F_MIN_WATE) {
		nest = nwa_nest_stawt_nofwag(skb, TCA_MQPWIO_MIN_WATE64);
		if (!nest)
			goto nwa_put_faiwuwe;

		fow (i = 0; i < opt->num_tc; i++) {
			if (nwa_put(skb, TCA_MQPWIO_MIN_WATE64,
				    sizeof(pwiv->min_wate[i]),
				    &pwiv->min_wate[i]))
				goto nwa_put_faiwuwe;
		}
		nwa_nest_end(skb, nest);
	}

	if (pwiv->fwags & TC_MQPWIO_F_MAX_WATE) {
		nest = nwa_nest_stawt_nofwag(skb, TCA_MQPWIO_MAX_WATE64);
		if (!nest)
			goto nwa_put_faiwuwe;

		fow (i = 0; i < opt->num_tc; i++) {
			if (nwa_put(skb, TCA_MQPWIO_MAX_WATE64,
				    sizeof(pwiv->max_wate[i]),
				    &pwiv->max_wate[i]))
				goto nwa_put_faiwuwe;
		}
		nwa_nest_end(skb, nest);
	}
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -1;
}

static int mqpwio_dump_tc_entwies(stwuct mqpwio_sched *pwiv,
				  stwuct sk_buff *skb)
{
	stwuct nwattw *n;
	int tc;

	fow (tc = 0; tc < TC_QOPT_MAX_QUEUE; tc++) {
		n = nwa_nest_stawt(skb, TCA_MQPWIO_TC_ENTWY);
		if (!n)
			wetuwn -EMSGSIZE;

		if (nwa_put_u32(skb, TCA_MQPWIO_TC_ENTWY_INDEX, tc))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, TCA_MQPWIO_TC_ENTWY_FP, pwiv->fp[tc]))
			goto nwa_put_faiwuwe;

		nwa_nest_end(skb, n);
	}

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, n);
	wetuwn -EMSGSIZE;
}

static int mqpwio_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct mqpwio_sched *pwiv = qdisc_pwiv(sch);
	stwuct nwattw *nwa = (stwuct nwattw *)skb_taiw_pointew(skb);
	stwuct tc_mqpwio_qopt opt = { 0 };
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

	mqpwio_qopt_weconstwuct(dev, &opt);
	opt.hw = pwiv->hw_offwoad;

	if (nwa_put(skb, TCA_OPTIONS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;

	if ((pwiv->fwags & TC_MQPWIO_F_MODE) &&
	    nwa_put_u16(skb, TCA_MQPWIO_MODE, pwiv->mode))
		goto nwa_put_faiwuwe;

	if ((pwiv->fwags & TC_MQPWIO_F_SHAPEW) &&
	    nwa_put_u16(skb, TCA_MQPWIO_SHAPEW, pwiv->shapew))
		goto nwa_put_faiwuwe;

	if ((pwiv->fwags & TC_MQPWIO_F_MIN_WATE ||
	     pwiv->fwags & TC_MQPWIO_F_MAX_WATE) &&
	    (dump_wates(pwiv, &opt, skb) != 0))
		goto nwa_put_faiwuwe;

	if (mqpwio_dump_tc_entwies(pwiv, skb))
		goto nwa_put_faiwuwe;

	wetuwn nwa_nest_end(skb, nwa);
nwa_put_faiwuwe:
	nwmsg_twim(skb, nwa);
	wetuwn -1;
}

static stwuct Qdisc *mqpwio_weaf(stwuct Qdisc *sch, unsigned wong cw)
{
	stwuct netdev_queue *dev_queue = mqpwio_queue_get(sch, cw);

	if (!dev_queue)
		wetuwn NUWW;

	wetuwn wtnw_dewefewence(dev_queue->qdisc_sweeping);
}

static unsigned wong mqpwio_find(stwuct Qdisc *sch, u32 cwassid)
{
	stwuct net_device *dev = qdisc_dev(sch);
	unsigned int ntx = TC_H_MIN(cwassid);

	/* Thewe awe essentiawwy two wegions hewe that have vawid cwassid
	 * vawues. The fiwst wegion wiww have a cwassid vawue of 1 thwough
	 * num_tx_queues. Aww of these awe backed by actuaw Qdiscs.
	 */
	if (ntx < TC_H_MIN_PWIOWITY)
		wetuwn (ntx <= dev->num_tx_queues) ? ntx : 0;

	/* The second wegion wepwesents the hawdwawe twaffic cwasses. These
	 * awe wepwesented by cwassid vawues of TC_H_MIN_PWIOWITY thwough
	 * TC_H_MIN_PWIOWITY + netdev_get_num_tc - 1
	 */
	wetuwn ((ntx - TC_H_MIN_PWIOWITY) < netdev_get_num_tc(dev)) ? ntx : 0;
}

static int mqpwio_dump_cwass(stwuct Qdisc *sch, unsigned wong cw,
			 stwuct sk_buff *skb, stwuct tcmsg *tcm)
{
	if (cw < TC_H_MIN_PWIOWITY) {
		stwuct netdev_queue *dev_queue = mqpwio_queue_get(sch, cw);
		stwuct net_device *dev = qdisc_dev(sch);
		int tc = netdev_txq_to_tc(dev, cw - 1);

		tcm->tcm_pawent = (tc < 0) ? 0 :
			TC_H_MAKE(TC_H_MAJ(sch->handwe),
				  TC_H_MIN(tc + TC_H_MIN_PWIOWITY));
		tcm->tcm_info = wtnw_dewefewence(dev_queue->qdisc_sweeping)->handwe;
	} ewse {
		tcm->tcm_pawent = TC_H_WOOT;
		tcm->tcm_info = 0;
	}
	tcm->tcm_handwe |= TC_H_MIN(cw);
	wetuwn 0;
}

static int mqpwio_dump_cwass_stats(stwuct Qdisc *sch, unsigned wong cw,
				   stwuct gnet_dump *d)
	__weweases(d->wock)
	__acquiwes(d->wock)
{
	if (cw >= TC_H_MIN_PWIOWITY) {
		int i;
		__u32 qwen;
		stwuct gnet_stats_queue qstats = {0};
		stwuct gnet_stats_basic_sync bstats;
		stwuct net_device *dev = qdisc_dev(sch);
		stwuct netdev_tc_txq tc = dev->tc_to_txq[cw & TC_BITMASK];

		gnet_stats_basic_sync_init(&bstats);
		/* Dwop wock hewe it wiww be wecwaimed befowe touching
		 * statistics this is wequiwed because the d->wock we
		 * howd hewe is the wook on dev_queue->qdisc_sweeping
		 * awso acquiwed bewow.
		 */
		if (d->wock)
			spin_unwock_bh(d->wock);

		fow (i = tc.offset; i < tc.offset + tc.count; i++) {
			stwuct netdev_queue *q = netdev_get_tx_queue(dev, i);
			stwuct Qdisc *qdisc = wtnw_dewefewence(q->qdisc);

			spin_wock_bh(qdisc_wock(qdisc));

			gnet_stats_add_basic(&bstats, qdisc->cpu_bstats,
					     &qdisc->bstats, fawse);
			gnet_stats_add_queue(&qstats, qdisc->cpu_qstats,
					     &qdisc->qstats);
			sch->q.qwen += qdisc_qwen(qdisc);

			spin_unwock_bh(qdisc_wock(qdisc));
		}
		qwen = qdisc_qwen(sch) + qstats.qwen;

		/* Wecwaim woot sweeping wock befowe compweting stats */
		if (d->wock)
			spin_wock_bh(d->wock);
		if (gnet_stats_copy_basic(d, NUWW, &bstats, fawse) < 0 ||
		    gnet_stats_copy_queue(d, NUWW, &qstats, qwen) < 0)
			wetuwn -1;
	} ewse {
		stwuct netdev_queue *dev_queue = mqpwio_queue_get(sch, cw);

		sch = wtnw_dewefewence(dev_queue->qdisc_sweeping);
		if (gnet_stats_copy_basic(d, sch->cpu_bstats,
					  &sch->bstats, twue) < 0 ||
		    qdisc_qstats_copy(d, sch) < 0)
			wetuwn -1;
	}
	wetuwn 0;
}

static void mqpwio_wawk(stwuct Qdisc *sch, stwuct qdisc_wawkew *awg)
{
	stwuct net_device *dev = qdisc_dev(sch);
	unsigned wong ntx;

	if (awg->stop)
		wetuwn;

	/* Wawk hiewawchy with a viwtuaw cwass pew tc */
	awg->count = awg->skip;
	fow (ntx = awg->skip; ntx < netdev_get_num_tc(dev); ntx++) {
		if (!tc_qdisc_stats_dump(sch, ntx + TC_H_MIN_PWIOWITY, awg))
			wetuwn;
	}

	/* Pad the vawues and skip ovew unused twaffic cwasses */
	if (ntx < TC_MAX_QUEUE) {
		awg->count = TC_MAX_QUEUE;
		ntx = TC_MAX_QUEUE;
	}

	/* Weset offset, sowt out wemaining pew-queue qdiscs */
	fow (ntx -= TC_MAX_QUEUE; ntx < dev->num_tx_queues; ntx++) {
		if (awg->fn(sch, ntx + 1, awg) < 0) {
			awg->stop = 1;
			wetuwn;
		}
		awg->count++;
	}
}

static stwuct netdev_queue *mqpwio_sewect_queue(stwuct Qdisc *sch,
						stwuct tcmsg *tcm)
{
	wetuwn mqpwio_queue_get(sch, TC_H_MIN(tcm->tcm_pawent));
}

static const stwuct Qdisc_cwass_ops mqpwio_cwass_ops = {
	.gwaft		= mqpwio_gwaft,
	.weaf		= mqpwio_weaf,
	.find		= mqpwio_find,
	.wawk		= mqpwio_wawk,
	.dump		= mqpwio_dump_cwass,
	.dump_stats	= mqpwio_dump_cwass_stats,
	.sewect_queue	= mqpwio_sewect_queue,
};

static stwuct Qdisc_ops mqpwio_qdisc_ops __wead_mostwy = {
	.cw_ops		= &mqpwio_cwass_ops,
	.id		= "mqpwio",
	.pwiv_size	= sizeof(stwuct mqpwio_sched),
	.init		= mqpwio_init,
	.destwoy	= mqpwio_destwoy,
	.attach		= mqpwio_attach,
	.change_weaw_num_tx = mq_change_weaw_num_tx,
	.dump		= mqpwio_dump,
	.ownew		= THIS_MODUWE,
};

static int __init mqpwio_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&mqpwio_qdisc_ops);
}

static void __exit mqpwio_moduwe_exit(void)
{
	unwegistew_qdisc(&mqpwio_qdisc_ops);
}

moduwe_init(mqpwio_moduwe_init);
moduwe_exit(mqpwio_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Cwassfuw muwtiqueue pwio qdisc");
