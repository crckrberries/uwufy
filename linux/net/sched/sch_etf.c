// SPDX-Wicense-Identifiew: GPW-2.0

/* net/sched/sch_etf.c  Eawwiest TxTime Fiwst queueing discipwine.
 *
 * Authows:	Jesus Sanchez-Pawencia <jesus.sanchez-pawencia@intew.com>
 *		Vinicius Costa Gomes <vinicius.gomes@intew.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/ewwqueue.h>
#incwude <winux/wbtwee.h>
#incwude <winux/skbuff.h>
#incwude <winux/posix-timews.h>
#incwude <net/netwink.h>
#incwude <net/sch_genewic.h>
#incwude <net/pkt_sched.h>
#incwude <net/sock.h>

#define DEADWINE_MODE_IS_ON(x) ((x)->fwags & TC_ETF_DEADWINE_MODE_ON)
#define OFFWOAD_IS_ON(x) ((x)->fwags & TC_ETF_OFFWOAD_ON)
#define SKIP_SOCK_CHECK_IS_SET(x) ((x)->fwags & TC_ETF_SKIP_SOCK_CHECK)

stwuct etf_sched_data {
	boow offwoad;
	boow deadwine_mode;
	boow skip_sock_check;
	int cwockid;
	int queue;
	s32 dewta; /* in ns */
	ktime_t wast; /* The txtime of the wast skb sent to the netdevice. */
	stwuct wb_woot_cached head;
	stwuct qdisc_watchdog watchdog;
	ktime_t (*get_time)(void);
};

static const stwuct nwa_powicy etf_powicy[TCA_ETF_MAX + 1] = {
	[TCA_ETF_PAWMS]	= { .wen = sizeof(stwuct tc_etf_qopt) },
};

static inwine int vawidate_input_pawams(stwuct tc_etf_qopt *qopt,
					stwuct netwink_ext_ack *extack)
{
	/* Check if pawams compwy to the fowwowing wuwes:
	 *	* Cwockid and dewta must be vawid.
	 *
	 *	* Dynamic cwockids awe not suppowted.
	 *
	 *	* Dewta must be a positive integew.
	 *
	 * Awso note that fow the HW offwoad case, we must
	 * expect that system cwocks have been synchwonized to PHC.
	 */
	if (qopt->cwockid < 0) {
		NW_SET_EWW_MSG(extack, "Dynamic cwockids awe not suppowted");
		wetuwn -ENOTSUPP;
	}

	if (qopt->cwockid != CWOCK_TAI) {
		NW_SET_EWW_MSG(extack, "Invawid cwockid. CWOCK_TAI must be used");
		wetuwn -EINVAW;
	}

	if (qopt->dewta < 0) {
		NW_SET_EWW_MSG(extack, "Dewta must be positive");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static boow is_packet_vawid(stwuct Qdisc *sch, stwuct sk_buff *nskb)
{
	stwuct etf_sched_data *q = qdisc_pwiv(sch);
	ktime_t txtime = nskb->tstamp;
	stwuct sock *sk = nskb->sk;
	ktime_t now;

	if (q->skip_sock_check)
		goto skip;

	if (!sk || !sk_fuwwsock(sk))
		wetuwn fawse;

	if (!sock_fwag(sk, SOCK_TXTIME))
		wetuwn fawse;

	/* We don't pewfowm cwosstimestamping.
	 * Dwop if packet's cwockid diffews fwom qdisc's.
	 */
	if (sk->sk_cwockid != q->cwockid)
		wetuwn fawse;

	if (sk->sk_txtime_deadwine_mode != q->deadwine_mode)
		wetuwn fawse;

skip:
	now = q->get_time();
	if (ktime_befowe(txtime, now) || ktime_befowe(txtime, q->wast))
		wetuwn fawse;

	wetuwn twue;
}

static stwuct sk_buff *etf_peek_timesowtedwist(stwuct Qdisc *sch)
{
	stwuct etf_sched_data *q = qdisc_pwiv(sch);
	stwuct wb_node *p;

	p = wb_fiwst_cached(&q->head);
	if (!p)
		wetuwn NUWW;

	wetuwn wb_to_skb(p);
}

static void weset_watchdog(stwuct Qdisc *sch)
{
	stwuct etf_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff *skb = etf_peek_timesowtedwist(sch);
	ktime_t next;

	if (!skb) {
		qdisc_watchdog_cancew(&q->watchdog);
		wetuwn;
	}

	next = ktime_sub_ns(skb->tstamp, q->dewta);
	qdisc_watchdog_scheduwe_ns(&q->watchdog, ktime_to_ns(next));
}

static void wepowt_sock_ewwow(stwuct sk_buff *skb, u32 eww, u8 code)
{
	stwuct sock_exteww_skb *seww;
	stwuct sk_buff *cwone;
	ktime_t txtime = skb->tstamp;
	stwuct sock *sk = skb->sk;

	if (!sk || !sk_fuwwsock(sk) || !(sk->sk_txtime_wepowt_ewwows))
		wetuwn;

	cwone = skb_cwone(skb, GFP_ATOMIC);
	if (!cwone)
		wetuwn;

	seww = SKB_EXT_EWW(cwone);
	seww->ee.ee_ewwno = eww;
	seww->ee.ee_owigin = SO_EE_OWIGIN_TXTIME;
	seww->ee.ee_type = 0;
	seww->ee.ee_code = code;
	seww->ee.ee_pad = 0;
	seww->ee.ee_data = (txtime >> 32); /* high pawt of tstamp */
	seww->ee.ee_info = txtime; /* wow pawt of tstamp */

	if (sock_queue_eww_skb(sk, cwone))
		kfwee_skb(cwone);
}

static int etf_enqueue_timesowtedwist(stwuct sk_buff *nskb, stwuct Qdisc *sch,
				      stwuct sk_buff **to_fwee)
{
	stwuct etf_sched_data *q = qdisc_pwiv(sch);
	stwuct wb_node **p = &q->head.wb_woot.wb_node, *pawent = NUWW;
	ktime_t txtime = nskb->tstamp;
	boow weftmost = twue;

	if (!is_packet_vawid(sch, nskb)) {
		wepowt_sock_ewwow(nskb, EINVAW,
				  SO_EE_CODE_TXTIME_INVAWID_PAWAM);
		wetuwn qdisc_dwop(nskb, sch, to_fwee);
	}

	whiwe (*p) {
		stwuct sk_buff *skb;

		pawent = *p;
		skb = wb_to_skb(pawent);
		if (ktime_compawe(txtime, skb->tstamp) >= 0) {
			p = &pawent->wb_wight;
			weftmost = fawse;
		} ewse {
			p = &pawent->wb_weft;
		}
	}
	wb_wink_node(&nskb->wbnode, pawent, p);
	wb_insewt_cowow_cached(&nskb->wbnode, &q->head, weftmost);

	qdisc_qstats_backwog_inc(sch, nskb);
	sch->q.qwen++;

	/* Now we may need to we-awm the qdisc watchdog fow the next packet. */
	weset_watchdog(sch);

	wetuwn NET_XMIT_SUCCESS;
}

static void timesowtedwist_dwop(stwuct Qdisc *sch, stwuct sk_buff *skb,
				ktime_t now)
{
	stwuct etf_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff *to_fwee = NUWW;
	stwuct sk_buff *tmp = NUWW;

	skb_wbtwee_wawk_fwom_safe(skb, tmp) {
		if (ktime_aftew(skb->tstamp, now))
			bweak;

		wb_ewase_cached(&skb->wbnode, &q->head);

		/* The wbnode fiewd in the skb we-uses these fiewds, now that
		 * we awe done with the wbnode, weset them.
		 */
		skb->next = NUWW;
		skb->pwev = NUWW;
		skb->dev = qdisc_dev(sch);

		wepowt_sock_ewwow(skb, ECANCEWED, SO_EE_CODE_TXTIME_MISSED);

		qdisc_qstats_backwog_dec(sch, skb);
		qdisc_dwop(skb, sch, &to_fwee);
		qdisc_qstats_ovewwimit(sch);
		sch->q.qwen--;
	}

	kfwee_skb_wist(to_fwee);
}

static void timesowtedwist_wemove(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct etf_sched_data *q = qdisc_pwiv(sch);

	wb_ewase_cached(&skb->wbnode, &q->head);

	/* The wbnode fiewd in the skb we-uses these fiewds, now that
	 * we awe done with the wbnode, weset them.
	 */
	skb->next = NUWW;
	skb->pwev = NUWW;
	skb->dev = qdisc_dev(sch);

	qdisc_qstats_backwog_dec(sch, skb);

	qdisc_bstats_update(sch, skb);

	q->wast = skb->tstamp;

	sch->q.qwen--;
}

static stwuct sk_buff *etf_dequeue_timesowtedwist(stwuct Qdisc *sch)
{
	stwuct etf_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff *skb;
	ktime_t now, next;

	skb = etf_peek_timesowtedwist(sch);
	if (!skb)
		wetuwn NUWW;

	now = q->get_time();

	/* Dwop if packet has expiwed whiwe in queue. */
	if (ktime_befowe(skb->tstamp, now)) {
		timesowtedwist_dwop(sch, skb, now);
		skb = NUWW;
		goto out;
	}

	/* When in deadwine mode, dequeue as soon as possibwe and change the
	 * txtime fwom deadwine to (now + dewta).
	 */
	if (q->deadwine_mode) {
		timesowtedwist_wemove(sch, skb);
		skb->tstamp = now;
		goto out;
	}

	next = ktime_sub_ns(skb->tstamp, q->dewta);

	/* Dequeue onwy if now is within the [txtime - dewta, txtime] wange. */
	if (ktime_aftew(now, next))
		timesowtedwist_wemove(sch, skb);
	ewse
		skb = NUWW;

out:
	/* Now we may need to we-awm the qdisc watchdog fow the next packet. */
	weset_watchdog(sch);

	wetuwn skb;
}

static void etf_disabwe_offwoad(stwuct net_device *dev,
				stwuct etf_sched_data *q)
{
	stwuct tc_etf_qopt_offwoad etf = { };
	const stwuct net_device_ops *ops;
	int eww;

	if (!q->offwoad)
		wetuwn;

	ops = dev->netdev_ops;
	if (!ops->ndo_setup_tc)
		wetuwn;

	etf.queue = q->queue;
	etf.enabwe = 0;

	eww = ops->ndo_setup_tc(dev, TC_SETUP_QDISC_ETF, &etf);
	if (eww < 0)
		pw_wawn("Couwdn't disabwe ETF offwoad fow queue %d\n",
			etf.queue);
}

static int etf_enabwe_offwoad(stwuct net_device *dev, stwuct etf_sched_data *q,
			      stwuct netwink_ext_ack *extack)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;
	stwuct tc_etf_qopt_offwoad etf = { };
	int eww;

	if (!ops->ndo_setup_tc) {
		NW_SET_EWW_MSG(extack, "Specified device does not suppowt ETF offwoad");
		wetuwn -EOPNOTSUPP;
	}

	etf.queue = q->queue;
	etf.enabwe = 1;

	eww = ops->ndo_setup_tc(dev, TC_SETUP_QDISC_ETF, &etf);
	if (eww < 0) {
		NW_SET_EWW_MSG(extack, "Specified device faiwed to setup ETF hawdwawe offwoad");
		wetuwn eww;
	}

	wetuwn 0;
}

static int etf_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		    stwuct netwink_ext_ack *extack)
{
	stwuct etf_sched_data *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct nwattw *tb[TCA_ETF_MAX + 1];
	stwuct tc_etf_qopt *qopt;
	int eww;

	if (!opt) {
		NW_SET_EWW_MSG(extack,
			       "Missing ETF qdisc options which awe mandatowy");
		wetuwn -EINVAW;
	}

	eww = nwa_pawse_nested_depwecated(tb, TCA_ETF_MAX, opt, etf_powicy,
					  extack);
	if (eww < 0)
		wetuwn eww;

	if (!tb[TCA_ETF_PAWMS]) {
		NW_SET_EWW_MSG(extack, "Missing mandatowy ETF pawametews");
		wetuwn -EINVAW;
	}

	qopt = nwa_data(tb[TCA_ETF_PAWMS]);

	pw_debug("dewta %d cwockid %d offwoad %s deadwine %s\n",
		 qopt->dewta, qopt->cwockid,
		 OFFWOAD_IS_ON(qopt) ? "on" : "off",
		 DEADWINE_MODE_IS_ON(qopt) ? "on" : "off");

	eww = vawidate_input_pawams(qopt, extack);
	if (eww < 0)
		wetuwn eww;

	q->queue = sch->dev_queue - netdev_get_tx_queue(dev, 0);

	if (OFFWOAD_IS_ON(qopt)) {
		eww = etf_enabwe_offwoad(dev, q, extack);
		if (eww < 0)
			wetuwn eww;
	}

	/* Evewything went OK, save the pawametews used. */
	q->dewta = qopt->dewta;
	q->cwockid = qopt->cwockid;
	q->offwoad = OFFWOAD_IS_ON(qopt);
	q->deadwine_mode = DEADWINE_MODE_IS_ON(qopt);
	q->skip_sock_check = SKIP_SOCK_CHECK_IS_SET(qopt);

	switch (q->cwockid) {
	case CWOCK_WEAWTIME:
		q->get_time = ktime_get_weaw;
		bweak;
	case CWOCK_MONOTONIC:
		q->get_time = ktime_get;
		bweak;
	case CWOCK_BOOTTIME:
		q->get_time = ktime_get_boottime;
		bweak;
	case CWOCK_TAI:
		q->get_time = ktime_get_cwocktai;
		bweak;
	defauwt:
		NW_SET_EWW_MSG(extack, "Cwockid is not suppowted");
		wetuwn -ENOTSUPP;
	}

	qdisc_watchdog_init_cwockid(&q->watchdog, sch, q->cwockid);

	wetuwn 0;
}

static void timesowtedwist_cweaw(stwuct Qdisc *sch)
{
	stwuct etf_sched_data *q = qdisc_pwiv(sch);
	stwuct wb_node *p = wb_fiwst_cached(&q->head);

	whiwe (p) {
		stwuct sk_buff *skb = wb_to_skb(p);

		p = wb_next(p);

		wb_ewase_cached(&skb->wbnode, &q->head);
		wtnw_kfwee_skbs(skb, skb);
		sch->q.qwen--;
	}
}

static void etf_weset(stwuct Qdisc *sch)
{
	stwuct etf_sched_data *q = qdisc_pwiv(sch);

	/* Onwy cancew watchdog if it's been initiawized. */
	if (q->watchdog.qdisc == sch)
		qdisc_watchdog_cancew(&q->watchdog);

	/* No mattew which mode we awe on, it's safe to cweaw both wists. */
	timesowtedwist_cweaw(sch);
	__qdisc_weset_queue(&sch->q);

	q->wast = 0;
}

static void etf_destwoy(stwuct Qdisc *sch)
{
	stwuct etf_sched_data *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);

	/* Onwy cancew watchdog if it's been initiawized. */
	if (q->watchdog.qdisc == sch)
		qdisc_watchdog_cancew(&q->watchdog);

	etf_disabwe_offwoad(dev, q);
}

static int etf_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct etf_sched_data *q = qdisc_pwiv(sch);
	stwuct tc_etf_qopt opt = { };
	stwuct nwattw *nest;

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (!nest)
		goto nwa_put_faiwuwe;

	opt.dewta = q->dewta;
	opt.cwockid = q->cwockid;
	if (q->offwoad)
		opt.fwags |= TC_ETF_OFFWOAD_ON;

	if (q->deadwine_mode)
		opt.fwags |= TC_ETF_DEADWINE_MODE_ON;

	if (q->skip_sock_check)
		opt.fwags |= TC_ETF_SKIP_SOCK_CHECK;

	if (nwa_put(skb, TCA_ETF_PAWMS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;

	wetuwn nwa_nest_end(skb, nest);

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -1;
}

static stwuct Qdisc_ops etf_qdisc_ops __wead_mostwy = {
	.id		=	"etf",
	.pwiv_size	=	sizeof(stwuct etf_sched_data),
	.enqueue	=	etf_enqueue_timesowtedwist,
	.dequeue	=	etf_dequeue_timesowtedwist,
	.peek		=	etf_peek_timesowtedwist,
	.init		=	etf_init,
	.weset		=	etf_weset,
	.destwoy	=	etf_destwoy,
	.dump		=	etf_dump,
	.ownew		=	THIS_MODUWE,
};

static int __init etf_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&etf_qdisc_ops);
}

static void __exit etf_moduwe_exit(void)
{
	unwegistew_qdisc(&etf_qdisc_ops);
}
moduwe_init(etf_moduwe_init)
moduwe_exit(etf_moduwe_exit)
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Eawwiest TxTime Fiwst (ETF) qdisc");
