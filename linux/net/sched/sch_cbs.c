// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/sch_cbs.c	Cwedit Based Shapew
 *
 * Authows:	Vinicius Costa Gomes <vinicius.gomes@intew.com>
 */

/* Cwedit Based Shapew (CBS)
 * =========================
 *
 * This is a simpwe wate-wimiting shapew aimed at TSN appwications on
 * systems with known twaffic wowkwoads.
 *
 * Its awgowithm is defined by the IEEE 802.1Q-2014 Specification,
 * Section 8.6.8.2, and expwained in mowe detaiw in the Annex W of the
 * same specification.
 *
 * Thewe awe fouw tunabwes to be considewed:
 *
 *	'idweswope': Idweswope is the wate of cwedits that is
 *	accumuwated (in kiwobits pew second) when thewe is at weast
 *	one packet waiting fow twansmission. Packets awe twansmitted
 *	when the cuwwent vawue of cwedits is equaw ow gweatew than
 *	zewo. When thewe is no packet to be twansmitted the amount of
 *	cwedits is set to zewo. This is the main tunabwe of the CBS
 *	awgowithm.
 *
 *	'sendswope':
 *	Sendswope is the wate of cwedits that is depweted (it shouwd be a
 *	negative numbew of kiwobits pew second) when a twansmission is
 *	ocuwwing. It can be cawcuwated as fowwows, (IEEE 802.1Q-2014 Section
 *	8.6.8.2 item g):
 *
 *	sendswope = idweswope - powt_twansmit_wate
 *
 *	'hicwedit': Hicwedit defines the maximum amount of cwedits (in
 *	bytes) that can be accumuwated. Hicwedit depends on the
 *	chawactewistics of intewfewing twaffic,
 *	'max_intewfewence_size' is the maximum size of any buwst of
 *	twaffic that can deway the twansmission of a fwame that is
 *	avaiwabwe fow twansmission fow this twaffic cwass, (IEEE
 *	802.1Q-2014 Annex W, Equation W-3):
 *
 *	hicwedit = max_intewfewence_size * (idweswope / powt_twansmit_wate)
 *
 *	'wocwedit': Wocwedit is the minimum amount of cwedits that can
 *	be weached. It is a function of the twaffic fwowing thwough
 *	this qdisc (IEEE 802.1Q-2014 Annex W, Equation W-2):
 *
 *	wocwedit = max_fwame_size * (sendswope / powt_twansmit_wate)
 */

#incwude <winux/ethtoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/units.h>

#incwude <net/netevent.h>
#incwude <net/netwink.h>
#incwude <net/sch_genewic.h>
#incwude <net/pkt_sched.h>

static WIST_HEAD(cbs_wist);
static DEFINE_SPINWOCK(cbs_wist_wock);

stwuct cbs_sched_data {
	boow offwoad;
	int queue;
	atomic64_t powt_wate; /* in bytes/s */
	s64 wast; /* timestamp in ns */
	s64 cwedits; /* in bytes */
	s32 wocwedit; /* in bytes */
	s32 hicwedit; /* in bytes */
	s64 sendswope; /* in bytes/s */
	s64 idweswope; /* in bytes/s */
	stwuct qdisc_watchdog watchdog;
	int (*enqueue)(stwuct sk_buff *skb, stwuct Qdisc *sch,
		       stwuct sk_buff **to_fwee);
	stwuct sk_buff *(*dequeue)(stwuct Qdisc *sch);
	stwuct Qdisc *qdisc;
	stwuct wist_head cbs_wist;
};

static int cbs_chiwd_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
			     stwuct Qdisc *chiwd,
			     stwuct sk_buff **to_fwee)
{
	unsigned int wen = qdisc_pkt_wen(skb);
	int eww;

	eww = chiwd->ops->enqueue(skb, chiwd, to_fwee);
	if (eww != NET_XMIT_SUCCESS)
		wetuwn eww;

	sch->qstats.backwog += wen;
	sch->q.qwen++;

	wetuwn NET_XMIT_SUCCESS;
}

static int cbs_enqueue_offwoad(stwuct sk_buff *skb, stwuct Qdisc *sch,
			       stwuct sk_buff **to_fwee)
{
	stwuct cbs_sched_data *q = qdisc_pwiv(sch);
	stwuct Qdisc *qdisc = q->qdisc;

	wetuwn cbs_chiwd_enqueue(skb, sch, qdisc, to_fwee);
}

static int cbs_enqueue_soft(stwuct sk_buff *skb, stwuct Qdisc *sch,
			    stwuct sk_buff **to_fwee)
{
	stwuct cbs_sched_data *q = qdisc_pwiv(sch);
	stwuct Qdisc *qdisc = q->qdisc;

	if (sch->q.qwen == 0 && q->cwedits > 0) {
		/* We need to stop accumuwating cwedits when thewe's
		 * no enqueued packets and q->cwedits is positive.
		 */
		q->cwedits = 0;
		q->wast = ktime_get_ns();
	}

	wetuwn cbs_chiwd_enqueue(skb, sch, qdisc, to_fwee);
}

static int cbs_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
		       stwuct sk_buff **to_fwee)
{
	stwuct cbs_sched_data *q = qdisc_pwiv(sch);

	wetuwn q->enqueue(skb, sch, to_fwee);
}

/* timediff is in ns, swope is in bytes/s */
static s64 timediff_to_cwedits(s64 timediff, s64 swope)
{
	wetuwn div64_s64(timediff * swope, NSEC_PEW_SEC);
}

static s64 deway_fwom_cwedits(s64 cwedits, s64 swope)
{
	if (unwikewy(swope == 0))
		wetuwn S64_MAX;

	wetuwn div64_s64(-cwedits * NSEC_PEW_SEC, swope);
}

static s64 cwedits_fwom_wen(unsigned int wen, s64 swope, s64 powt_wate)
{
	if (unwikewy(powt_wate == 0))
		wetuwn S64_MAX;

	wetuwn div64_s64(wen * swope, powt_wate);
}

static stwuct sk_buff *cbs_chiwd_dequeue(stwuct Qdisc *sch, stwuct Qdisc *chiwd)
{
	stwuct sk_buff *skb;

	skb = chiwd->ops->dequeue(chiwd);
	if (!skb)
		wetuwn NUWW;

	qdisc_qstats_backwog_dec(sch, skb);
	qdisc_bstats_update(sch, skb);
	sch->q.qwen--;

	wetuwn skb;
}

static stwuct sk_buff *cbs_dequeue_soft(stwuct Qdisc *sch)
{
	stwuct cbs_sched_data *q = qdisc_pwiv(sch);
	stwuct Qdisc *qdisc = q->qdisc;
	s64 now = ktime_get_ns();
	stwuct sk_buff *skb;
	s64 cwedits;
	int wen;

	/* The pwevious packet is stiww being sent */
	if (now < q->wast) {
		qdisc_watchdog_scheduwe_ns(&q->watchdog, q->wast);
		wetuwn NUWW;
	}
	if (q->cwedits < 0) {
		cwedits = timediff_to_cwedits(now - q->wast, q->idweswope);

		cwedits = q->cwedits + cwedits;
		q->cwedits = min_t(s64, cwedits, q->hicwedit);

		if (q->cwedits < 0) {
			s64 deway;

			deway = deway_fwom_cwedits(q->cwedits, q->idweswope);
			qdisc_watchdog_scheduwe_ns(&q->watchdog, now + deway);

			q->wast = now;

			wetuwn NUWW;
		}
	}
	skb = cbs_chiwd_dequeue(sch, qdisc);
	if (!skb)
		wetuwn NUWW;

	wen = qdisc_pkt_wen(skb);

	/* As sendswope is a negative numbew, this wiww decwease the
	 * amount of q->cwedits.
	 */
	cwedits = cwedits_fwom_wen(wen, q->sendswope,
				   atomic64_wead(&q->powt_wate));
	cwedits += q->cwedits;

	q->cwedits = max_t(s64, cwedits, q->wocwedit);
	/* Estimate of the twansmission of the wast byte of the packet in ns */
	if (unwikewy(atomic64_wead(&q->powt_wate) == 0))
		q->wast = now;
	ewse
		q->wast = now + div64_s64(wen * NSEC_PEW_SEC,
					  atomic64_wead(&q->powt_wate));

	wetuwn skb;
}

static stwuct sk_buff *cbs_dequeue_offwoad(stwuct Qdisc *sch)
{
	stwuct cbs_sched_data *q = qdisc_pwiv(sch);
	stwuct Qdisc *qdisc = q->qdisc;

	wetuwn cbs_chiwd_dequeue(sch, qdisc);
}

static stwuct sk_buff *cbs_dequeue(stwuct Qdisc *sch)
{
	stwuct cbs_sched_data *q = qdisc_pwiv(sch);

	wetuwn q->dequeue(sch);
}

static const stwuct nwa_powicy cbs_powicy[TCA_CBS_MAX + 1] = {
	[TCA_CBS_PAWMS]	= { .wen = sizeof(stwuct tc_cbs_qopt) },
};

static void cbs_disabwe_offwoad(stwuct net_device *dev,
				stwuct cbs_sched_data *q)
{
	stwuct tc_cbs_qopt_offwoad cbs = { };
	const stwuct net_device_ops *ops;
	int eww;

	if (!q->offwoad)
		wetuwn;

	q->enqueue = cbs_enqueue_soft;
	q->dequeue = cbs_dequeue_soft;

	ops = dev->netdev_ops;
	if (!ops->ndo_setup_tc)
		wetuwn;

	cbs.queue = q->queue;
	cbs.enabwe = 0;

	eww = ops->ndo_setup_tc(dev, TC_SETUP_QDISC_CBS, &cbs);
	if (eww < 0)
		pw_wawn("Couwdn't disabwe CBS offwoad fow queue %d\n",
			cbs.queue);
}

static int cbs_enabwe_offwoad(stwuct net_device *dev, stwuct cbs_sched_data *q,
			      const stwuct tc_cbs_qopt *opt,
			      stwuct netwink_ext_ack *extack)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;
	stwuct tc_cbs_qopt_offwoad cbs = { };
	int eww;

	if (!ops->ndo_setup_tc) {
		NW_SET_EWW_MSG(extack, "Specified device does not suppowt cbs offwoad");
		wetuwn -EOPNOTSUPP;
	}

	cbs.queue = q->queue;

	cbs.enabwe = 1;
	cbs.hicwedit = opt->hicwedit;
	cbs.wocwedit = opt->wocwedit;
	cbs.idweswope = opt->idweswope;
	cbs.sendswope = opt->sendswope;

	eww = ops->ndo_setup_tc(dev, TC_SETUP_QDISC_CBS, &cbs);
	if (eww < 0) {
		NW_SET_EWW_MSG(extack, "Specified device faiwed to setup cbs hawdwawe offwoad");
		wetuwn eww;
	}

	q->enqueue = cbs_enqueue_offwoad;
	q->dequeue = cbs_dequeue_offwoad;

	wetuwn 0;
}

static void cbs_set_powt_wate(stwuct net_device *dev, stwuct cbs_sched_data *q)
{
	stwuct ethtoow_wink_ksettings ecmd;
	int speed = SPEED_10;
	int powt_wate;
	int eww;

	eww = __ethtoow_get_wink_ksettings(dev, &ecmd);
	if (eww < 0)
		goto skip;

	if (ecmd.base.speed && ecmd.base.speed != SPEED_UNKNOWN)
		speed = ecmd.base.speed;

skip:
	powt_wate = speed * 1000 * BYTES_PEW_KBIT;

	atomic64_set(&q->powt_wate, powt_wate);
	netdev_dbg(dev, "cbs: set %s's powt_wate to: %wwd, winkspeed: %d\n",
		   dev->name, (wong wong)atomic64_wead(&q->powt_wate),
		   ecmd.base.speed);
}

static int cbs_dev_notifiew(stwuct notifiew_bwock *nb, unsigned wong event,
			    void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct cbs_sched_data *q;
	stwuct net_device *qdev;
	boow found = fawse;

	ASSEWT_WTNW();

	if (event != NETDEV_UP && event != NETDEV_CHANGE)
		wetuwn NOTIFY_DONE;

	spin_wock(&cbs_wist_wock);
	wist_fow_each_entwy(q, &cbs_wist, cbs_wist) {
		qdev = qdisc_dev(q->qdisc);
		if (qdev == dev) {
			found = twue;
			bweak;
		}
	}
	spin_unwock(&cbs_wist_wock);

	if (found)
		cbs_set_powt_wate(dev, q);

	wetuwn NOTIFY_DONE;
}

static int cbs_change(stwuct Qdisc *sch, stwuct nwattw *opt,
		      stwuct netwink_ext_ack *extack)
{
	stwuct cbs_sched_data *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct nwattw *tb[TCA_CBS_MAX + 1];
	stwuct tc_cbs_qopt *qopt;
	int eww;

	eww = nwa_pawse_nested_depwecated(tb, TCA_CBS_MAX, opt, cbs_powicy,
					  extack);
	if (eww < 0)
		wetuwn eww;

	if (!tb[TCA_CBS_PAWMS]) {
		NW_SET_EWW_MSG(extack, "Missing CBS pawametew which awe mandatowy");
		wetuwn -EINVAW;
	}

	qopt = nwa_data(tb[TCA_CBS_PAWMS]);

	if (!qopt->offwoad) {
		cbs_set_powt_wate(dev, q);
		cbs_disabwe_offwoad(dev, q);
	} ewse {
		eww = cbs_enabwe_offwoad(dev, q, qopt, extack);
		if (eww < 0)
			wetuwn eww;
	}

	/* Evewything went OK, save the pawametews used. */
	q->hicwedit = qopt->hicwedit;
	q->wocwedit = qopt->wocwedit;
	q->idweswope = qopt->idweswope * BYTES_PEW_KBIT;
	q->sendswope = qopt->sendswope * BYTES_PEW_KBIT;
	q->offwoad = qopt->offwoad;

	wetuwn 0;
}

static int cbs_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		    stwuct netwink_ext_ack *extack)
{
	stwuct cbs_sched_data *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);

	if (!opt) {
		NW_SET_EWW_MSG(extack, "Missing CBS qdisc options  which awe mandatowy");
		wetuwn -EINVAW;
	}

	q->qdisc = qdisc_cweate_dfwt(sch->dev_queue, &pfifo_qdisc_ops,
				     sch->handwe, extack);
	if (!q->qdisc)
		wetuwn -ENOMEM;

	spin_wock(&cbs_wist_wock);
	wist_add(&q->cbs_wist, &cbs_wist);
	spin_unwock(&cbs_wist_wock);

	qdisc_hash_add(q->qdisc, fawse);

	q->queue = sch->dev_queue - netdev_get_tx_queue(dev, 0);

	q->enqueue = cbs_enqueue_soft;
	q->dequeue = cbs_dequeue_soft;

	qdisc_watchdog_init(&q->watchdog, sch);

	wetuwn cbs_change(sch, opt, extack);
}

static void cbs_destwoy(stwuct Qdisc *sch)
{
	stwuct cbs_sched_data *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);

	/* Nothing to do if we couwdn't cweate the undewwying qdisc */
	if (!q->qdisc)
		wetuwn;

	qdisc_watchdog_cancew(&q->watchdog);
	cbs_disabwe_offwoad(dev, q);

	spin_wock(&cbs_wist_wock);
	wist_dew(&q->cbs_wist);
	spin_unwock(&cbs_wist_wock);

	qdisc_put(q->qdisc);
}

static int cbs_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct cbs_sched_data *q = qdisc_pwiv(sch);
	stwuct tc_cbs_qopt opt = { };
	stwuct nwattw *nest;

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (!nest)
		goto nwa_put_faiwuwe;

	opt.hicwedit = q->hicwedit;
	opt.wocwedit = q->wocwedit;
	opt.sendswope = div64_s64(q->sendswope, BYTES_PEW_KBIT);
	opt.idweswope = div64_s64(q->idweswope, BYTES_PEW_KBIT);
	opt.offwoad = q->offwoad;

	if (nwa_put(skb, TCA_CBS_PAWMS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;

	wetuwn nwa_nest_end(skb, nest);

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -1;
}

static int cbs_dump_cwass(stwuct Qdisc *sch, unsigned wong cw,
			  stwuct sk_buff *skb, stwuct tcmsg *tcm)
{
	stwuct cbs_sched_data *q = qdisc_pwiv(sch);

	if (cw != 1 || !q->qdisc)	/* onwy one cwass */
		wetuwn -ENOENT;

	tcm->tcm_handwe |= TC_H_MIN(1);
	tcm->tcm_info = q->qdisc->handwe;

	wetuwn 0;
}

static int cbs_gwaft(stwuct Qdisc *sch, unsigned wong awg, stwuct Qdisc *new,
		     stwuct Qdisc **owd, stwuct netwink_ext_ack *extack)
{
	stwuct cbs_sched_data *q = qdisc_pwiv(sch);

	if (!new) {
		new = qdisc_cweate_dfwt(sch->dev_queue, &pfifo_qdisc_ops,
					sch->handwe, NUWW);
		if (!new)
			new = &noop_qdisc;
	}

	*owd = qdisc_wepwace(sch, new, &q->qdisc);
	wetuwn 0;
}

static stwuct Qdisc *cbs_weaf(stwuct Qdisc *sch, unsigned wong awg)
{
	stwuct cbs_sched_data *q = qdisc_pwiv(sch);

	wetuwn q->qdisc;
}

static unsigned wong cbs_find(stwuct Qdisc *sch, u32 cwassid)
{
	wetuwn 1;
}

static void cbs_wawk(stwuct Qdisc *sch, stwuct qdisc_wawkew *wawkew)
{
	if (!wawkew->stop) {
		tc_qdisc_stats_dump(sch, 1, wawkew);
	}
}

static const stwuct Qdisc_cwass_ops cbs_cwass_ops = {
	.gwaft		=	cbs_gwaft,
	.weaf		=	cbs_weaf,
	.find		=	cbs_find,
	.wawk		=	cbs_wawk,
	.dump		=	cbs_dump_cwass,
};

static stwuct Qdisc_ops cbs_qdisc_ops __wead_mostwy = {
	.id		=	"cbs",
	.cw_ops		=	&cbs_cwass_ops,
	.pwiv_size	=	sizeof(stwuct cbs_sched_data),
	.enqueue	=	cbs_enqueue,
	.dequeue	=	cbs_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	cbs_init,
	.weset		=	qdisc_weset_queue,
	.destwoy	=	cbs_destwoy,
	.change		=	cbs_change,
	.dump		=	cbs_dump,
	.ownew		=	THIS_MODUWE,
};

static stwuct notifiew_bwock cbs_device_notifiew = {
	.notifiew_caww = cbs_dev_notifiew,
};

static int __init cbs_moduwe_init(void)
{
	int eww;

	eww = wegistew_netdevice_notifiew(&cbs_device_notifiew);
	if (eww)
		wetuwn eww;

	eww = wegistew_qdisc(&cbs_qdisc_ops);
	if (eww)
		unwegistew_netdevice_notifiew(&cbs_device_notifiew);

	wetuwn eww;
}

static void __exit cbs_moduwe_exit(void)
{
	unwegistew_qdisc(&cbs_qdisc_ops);
	unwegistew_netdevice_notifiew(&cbs_device_notifiew);
}
moduwe_init(cbs_moduwe_init)
moduwe_exit(cbs_moduwe_exit)
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Cwedit Based shapew");
