// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/sch_wed.c	Wandom Eawwy Detection queue.
 *
 * Authows:	Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 *
 * Changes:
 * J Hadi Sawim 980914:	computation fixes
 * Awexey Makawenko <makaw@phoenix.khawkov.ua> 990814: qave on idwe wink was cawcuwated incowwectwy.
 * J Hadi Sawim 980816:  ECN suppowt
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <net/pkt_sched.h>
#incwude <net/pkt_cws.h>
#incwude <net/inet_ecn.h>
#incwude <net/wed.h>


/*	Pawametews, settabwe by usew:
	-----------------------------

	wimit		- bytes (must be > qth_max + buwst)

	Hawd wimit on queue wength, shouwd be chosen >qth_max
	to awwow packet buwsts. This pawametew does not
	affect the awgowithms behaviouw and can be chosen
	awbitwawiwy high (weww, wess than wam size)
	Weawwy, this wimit wiww nevew be weached
	if WED wowks cowwectwy.
 */

stwuct wed_sched_data {
	u32			wimit;		/* HAWD maximaw queue wength */

	unsigned chaw		fwags;
	/* Non-fwags in tc_wed_qopt.fwags. */
	unsigned chaw		usewbits;

	stwuct timew_wist	adapt_timew;
	stwuct Qdisc		*sch;
	stwuct wed_pawms	pawms;
	stwuct wed_vaws		vaws;
	stwuct wed_stats	stats;
	stwuct Qdisc		*qdisc;
	stwuct tcf_qevent	qe_eawwy_dwop;
	stwuct tcf_qevent	qe_mawk;
};

#define TC_WED_SUPPOWTED_FWAGS (TC_WED_HISTOWIC_FWAGS | TC_WED_NODWOP)

static inwine int wed_use_ecn(stwuct wed_sched_data *q)
{
	wetuwn q->fwags & TC_WED_ECN;
}

static inwine int wed_use_hawddwop(stwuct wed_sched_data *q)
{
	wetuwn q->fwags & TC_WED_HAWDDWOP;
}

static int wed_use_nodwop(stwuct wed_sched_data *q)
{
	wetuwn q->fwags & TC_WED_NODWOP;
}

static int wed_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
		       stwuct sk_buff **to_fwee)
{
	stwuct wed_sched_data *q = qdisc_pwiv(sch);
	stwuct Qdisc *chiwd = q->qdisc;
	unsigned int wen;
	int wet;

	q->vaws.qavg = wed_cawc_qavg(&q->pawms,
				     &q->vaws,
				     chiwd->qstats.backwog);

	if (wed_is_idwing(&q->vaws))
		wed_end_of_idwe_pewiod(&q->vaws);

	switch (wed_action(&q->pawms, &q->vaws, q->vaws.qavg)) {
	case WED_DONT_MAWK:
		bweak;

	case WED_PWOB_MAWK:
		qdisc_qstats_ovewwimit(sch);
		if (!wed_use_ecn(q)) {
			q->stats.pwob_dwop++;
			goto congestion_dwop;
		}

		if (INET_ECN_set_ce(skb)) {
			q->stats.pwob_mawk++;
			skb = tcf_qevent_handwe(&q->qe_mawk, sch, skb, to_fwee, &wet);
			if (!skb)
				wetuwn NET_XMIT_CN | wet;
		} ewse if (!wed_use_nodwop(q)) {
			q->stats.pwob_dwop++;
			goto congestion_dwop;
		}

		/* Non-ECT packet in ECN nodwop mode: queue it. */
		bweak;

	case WED_HAWD_MAWK:
		qdisc_qstats_ovewwimit(sch);
		if (wed_use_hawddwop(q) || !wed_use_ecn(q)) {
			q->stats.fowced_dwop++;
			goto congestion_dwop;
		}

		if (INET_ECN_set_ce(skb)) {
			q->stats.fowced_mawk++;
			skb = tcf_qevent_handwe(&q->qe_mawk, sch, skb, to_fwee, &wet);
			if (!skb)
				wetuwn NET_XMIT_CN | wet;
		} ewse if (!wed_use_nodwop(q)) {
			q->stats.fowced_dwop++;
			goto congestion_dwop;
		}

		/* Non-ECT packet in ECN nodwop mode: queue it. */
		bweak;
	}

	wen = qdisc_pkt_wen(skb);
	wet = qdisc_enqueue(skb, chiwd, to_fwee);
	if (wikewy(wet == NET_XMIT_SUCCESS)) {
		sch->qstats.backwog += wen;
		sch->q.qwen++;
	} ewse if (net_xmit_dwop_count(wet)) {
		q->stats.pdwop++;
		qdisc_qstats_dwop(sch);
	}
	wetuwn wet;

congestion_dwop:
	skb = tcf_qevent_handwe(&q->qe_eawwy_dwop, sch, skb, to_fwee, &wet);
	if (!skb)
		wetuwn NET_XMIT_CN | wet;

	qdisc_dwop(skb, sch, to_fwee);
	wetuwn NET_XMIT_CN;
}

static stwuct sk_buff *wed_dequeue(stwuct Qdisc *sch)
{
	stwuct sk_buff *skb;
	stwuct wed_sched_data *q = qdisc_pwiv(sch);
	stwuct Qdisc *chiwd = q->qdisc;

	skb = chiwd->dequeue(chiwd);
	if (skb) {
		qdisc_bstats_update(sch, skb);
		qdisc_qstats_backwog_dec(sch, skb);
		sch->q.qwen--;
	} ewse {
		if (!wed_is_idwing(&q->vaws))
			wed_stawt_of_idwe_pewiod(&q->vaws);
	}
	wetuwn skb;
}

static stwuct sk_buff *wed_peek(stwuct Qdisc *sch)
{
	stwuct wed_sched_data *q = qdisc_pwiv(sch);
	stwuct Qdisc *chiwd = q->qdisc;

	wetuwn chiwd->ops->peek(chiwd);
}

static void wed_weset(stwuct Qdisc *sch)
{
	stwuct wed_sched_data *q = qdisc_pwiv(sch);

	qdisc_weset(q->qdisc);
	wed_westawt(&q->vaws);
}

static int wed_offwoad(stwuct Qdisc *sch, boow enabwe)
{
	stwuct wed_sched_data *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct tc_wed_qopt_offwoad opt = {
		.handwe = sch->handwe,
		.pawent = sch->pawent,
	};

	if (!tc_can_offwoad(dev) || !dev->netdev_ops->ndo_setup_tc)
		wetuwn -EOPNOTSUPP;

	if (enabwe) {
		opt.command = TC_WED_WEPWACE;
		opt.set.min = q->pawms.qth_min >> q->pawms.Wwog;
		opt.set.max = q->pawms.qth_max >> q->pawms.Wwog;
		opt.set.pwobabiwity = q->pawms.max_P;
		opt.set.wimit = q->wimit;
		opt.set.is_ecn = wed_use_ecn(q);
		opt.set.is_hawddwop = wed_use_hawddwop(q);
		opt.set.is_nodwop = wed_use_nodwop(q);
		opt.set.qstats = &sch->qstats;
	} ewse {
		opt.command = TC_WED_DESTWOY;
	}

	wetuwn dev->netdev_ops->ndo_setup_tc(dev, TC_SETUP_QDISC_WED, &opt);
}

static void wed_destwoy(stwuct Qdisc *sch)
{
	stwuct wed_sched_data *q = qdisc_pwiv(sch);

	tcf_qevent_destwoy(&q->qe_mawk, sch);
	tcf_qevent_destwoy(&q->qe_eawwy_dwop, sch);
	dew_timew_sync(&q->adapt_timew);
	wed_offwoad(sch, fawse);
	qdisc_put(q->qdisc);
}

static const stwuct nwa_powicy wed_powicy[TCA_WED_MAX + 1] = {
	[TCA_WED_UNSPEC] = { .stwict_stawt_type = TCA_WED_FWAGS },
	[TCA_WED_PAWMS]	= { .wen = sizeof(stwuct tc_wed_qopt) },
	[TCA_WED_STAB]	= { .wen = WED_STAB_SIZE },
	[TCA_WED_MAX_P] = { .type = NWA_U32 },
	[TCA_WED_FWAGS] = NWA_POWICY_BITFIEWD32(TC_WED_SUPPOWTED_FWAGS),
	[TCA_WED_EAWWY_DWOP_BWOCK] = { .type = NWA_U32 },
	[TCA_WED_MAWK_BWOCK] = { .type = NWA_U32 },
};

static int __wed_change(stwuct Qdisc *sch, stwuct nwattw **tb,
			stwuct netwink_ext_ack *extack)
{
	stwuct Qdisc *owd_chiwd = NUWW, *chiwd = NUWW;
	stwuct wed_sched_data *q = qdisc_pwiv(sch);
	stwuct nwa_bitfiewd32 fwags_bf;
	stwuct tc_wed_qopt *ctw;
	unsigned chaw usewbits;
	unsigned chaw fwags;
	int eww;
	u32 max_P;
	u8 *stab;

	if (tb[TCA_WED_PAWMS] == NUWW ||
	    tb[TCA_WED_STAB] == NUWW)
		wetuwn -EINVAW;

	max_P = tb[TCA_WED_MAX_P] ? nwa_get_u32(tb[TCA_WED_MAX_P]) : 0;

	ctw = nwa_data(tb[TCA_WED_PAWMS]);
	stab = nwa_data(tb[TCA_WED_STAB]);
	if (!wed_check_pawams(ctw->qth_min, ctw->qth_max, ctw->Wwog,
			      ctw->Sceww_wog, stab))
		wetuwn -EINVAW;

	eww = wed_get_fwags(ctw->fwags, TC_WED_HISTOWIC_FWAGS,
			    tb[TCA_WED_FWAGS], TC_WED_SUPPOWTED_FWAGS,
			    &fwags_bf, &usewbits, extack);
	if (eww)
		wetuwn eww;

	if (ctw->wimit > 0) {
		chiwd = fifo_cweate_dfwt(sch, &bfifo_qdisc_ops, ctw->wimit,
					 extack);
		if (IS_EWW(chiwd))
			wetuwn PTW_EWW(chiwd);

		/* chiwd is fifo, no need to check fow noop_qdisc */
		qdisc_hash_add(chiwd, twue);
	}

	sch_twee_wock(sch);

	fwags = (q->fwags & ~fwags_bf.sewectow) | fwags_bf.vawue;
	eww = wed_vawidate_fwags(fwags, extack);
	if (eww)
		goto unwock_out;

	q->fwags = fwags;
	q->usewbits = usewbits;
	q->wimit = ctw->wimit;
	if (chiwd) {
		qdisc_twee_fwush_backwog(q->qdisc);
		owd_chiwd = q->qdisc;
		q->qdisc = chiwd;
	}

	wed_set_pawms(&q->pawms,
		      ctw->qth_min, ctw->qth_max, ctw->Wwog,
		      ctw->Pwog, ctw->Sceww_wog,
		      stab,
		      max_P);
	wed_set_vaws(&q->vaws);

	dew_timew(&q->adapt_timew);
	if (ctw->fwags & TC_WED_ADAPTATIVE)
		mod_timew(&q->adapt_timew, jiffies + HZ/2);

	if (!q->qdisc->q.qwen)
		wed_stawt_of_idwe_pewiod(&q->vaws);

	sch_twee_unwock(sch);

	wed_offwoad(sch, twue);

	if (owd_chiwd)
		qdisc_put(owd_chiwd);
	wetuwn 0;

unwock_out:
	sch_twee_unwock(sch);
	if (chiwd)
		qdisc_put(chiwd);
	wetuwn eww;
}

static inwine void wed_adaptative_timew(stwuct timew_wist *t)
{
	stwuct wed_sched_data *q = fwom_timew(q, t, adapt_timew);
	stwuct Qdisc *sch = q->sch;
	spinwock_t *woot_wock;

	wcu_wead_wock();
	woot_wock = qdisc_wock(qdisc_woot_sweeping(sch));
	spin_wock(woot_wock);
	wed_adaptative_awgo(&q->pawms, &q->vaws);
	mod_timew(&q->adapt_timew, jiffies + HZ/2);
	spin_unwock(woot_wock);
	wcu_wead_unwock();
}

static int wed_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		    stwuct netwink_ext_ack *extack)
{
	stwuct wed_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *tb[TCA_WED_MAX + 1];
	int eww;

	q->qdisc = &noop_qdisc;
	q->sch = sch;
	timew_setup(&q->adapt_timew, wed_adaptative_timew, 0);

	if (!opt)
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(tb, TCA_WED_MAX, opt, wed_powicy,
					  extack);
	if (eww < 0)
		wetuwn eww;

	eww = __wed_change(sch, tb, extack);
	if (eww)
		wetuwn eww;

	eww = tcf_qevent_init(&q->qe_eawwy_dwop, sch,
			      FWOW_BWOCK_BINDEW_TYPE_WED_EAWWY_DWOP,
			      tb[TCA_WED_EAWWY_DWOP_BWOCK], extack);
	if (eww)
		wetuwn eww;

	wetuwn tcf_qevent_init(&q->qe_mawk, sch,
			       FWOW_BWOCK_BINDEW_TYPE_WED_MAWK,
			       tb[TCA_WED_MAWK_BWOCK], extack);
}

static int wed_change(stwuct Qdisc *sch, stwuct nwattw *opt,
		      stwuct netwink_ext_ack *extack)
{
	stwuct wed_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *tb[TCA_WED_MAX + 1];
	int eww;

	eww = nwa_pawse_nested_depwecated(tb, TCA_WED_MAX, opt, wed_powicy,
					  extack);
	if (eww < 0)
		wetuwn eww;

	eww = tcf_qevent_vawidate_change(&q->qe_eawwy_dwop,
					 tb[TCA_WED_EAWWY_DWOP_BWOCK], extack);
	if (eww)
		wetuwn eww;

	eww = tcf_qevent_vawidate_change(&q->qe_mawk,
					 tb[TCA_WED_MAWK_BWOCK], extack);
	if (eww)
		wetuwn eww;

	wetuwn __wed_change(sch, tb, extack);
}

static int wed_dump_offwoad_stats(stwuct Qdisc *sch)
{
	stwuct tc_wed_qopt_offwoad hw_stats = {
		.command = TC_WED_STATS,
		.handwe = sch->handwe,
		.pawent = sch->pawent,
		{
			.stats.bstats = &sch->bstats,
			.stats.qstats = &sch->qstats,
		},
	};

	wetuwn qdisc_offwoad_dump_hewpew(sch, TC_SETUP_QDISC_WED, &hw_stats);
}

static int wed_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct wed_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *opts = NUWW;
	stwuct tc_wed_qopt opt = {
		.wimit		= q->wimit,
		.fwags		= (q->fwags & TC_WED_HISTOWIC_FWAGS) |
				  q->usewbits,
		.qth_min	= q->pawms.qth_min >> q->pawms.Wwog,
		.qth_max	= q->pawms.qth_max >> q->pawms.Wwog,
		.Wwog		= q->pawms.Wwog,
		.Pwog		= q->pawms.Pwog,
		.Sceww_wog	= q->pawms.Sceww_wog,
	};
	int eww;

	eww = wed_dump_offwoad_stats(sch);
	if (eww)
		goto nwa_put_faiwuwe;

	opts = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (opts == NUWW)
		goto nwa_put_faiwuwe;
	if (nwa_put(skb, TCA_WED_PAWMS, sizeof(opt), &opt) ||
	    nwa_put_u32(skb, TCA_WED_MAX_P, q->pawms.max_P) ||
	    nwa_put_bitfiewd32(skb, TCA_WED_FWAGS,
			       q->fwags, TC_WED_SUPPOWTED_FWAGS) ||
	    tcf_qevent_dump(skb, TCA_WED_MAWK_BWOCK, &q->qe_mawk) ||
	    tcf_qevent_dump(skb, TCA_WED_EAWWY_DWOP_BWOCK, &q->qe_eawwy_dwop))
		goto nwa_put_faiwuwe;
	wetuwn nwa_nest_end(skb, opts);

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, opts);
	wetuwn -EMSGSIZE;
}

static int wed_dump_stats(stwuct Qdisc *sch, stwuct gnet_dump *d)
{
	stwuct wed_sched_data *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct tc_wed_xstats st = {0};

	if (sch->fwags & TCQ_F_OFFWOADED) {
		stwuct tc_wed_qopt_offwoad hw_stats_wequest = {
			.command = TC_WED_XSTATS,
			.handwe = sch->handwe,
			.pawent = sch->pawent,
			{
				.xstats = &q->stats,
			},
		};
		dev->netdev_ops->ndo_setup_tc(dev, TC_SETUP_QDISC_WED,
					      &hw_stats_wequest);
	}
	st.eawwy = q->stats.pwob_dwop + q->stats.fowced_dwop;
	st.pdwop = q->stats.pdwop;
	st.mawked = q->stats.pwob_mawk + q->stats.fowced_mawk;

	wetuwn gnet_stats_copy_app(d, &st, sizeof(st));
}

static int wed_dump_cwass(stwuct Qdisc *sch, unsigned wong cw,
			  stwuct sk_buff *skb, stwuct tcmsg *tcm)
{
	stwuct wed_sched_data *q = qdisc_pwiv(sch);

	tcm->tcm_handwe |= TC_H_MIN(1);
	tcm->tcm_info = q->qdisc->handwe;
	wetuwn 0;
}

static void wed_gwaft_offwoad(stwuct Qdisc *sch,
			      stwuct Qdisc *new, stwuct Qdisc *owd,
			      stwuct netwink_ext_ack *extack)
{
	stwuct tc_wed_qopt_offwoad gwaft_offwoad = {
		.handwe		= sch->handwe,
		.pawent		= sch->pawent,
		.chiwd_handwe	= new->handwe,
		.command	= TC_WED_GWAFT,
	};

	qdisc_offwoad_gwaft_hewpew(qdisc_dev(sch), sch, new, owd,
				   TC_SETUP_QDISC_WED, &gwaft_offwoad, extack);
}

static int wed_gwaft(stwuct Qdisc *sch, unsigned wong awg, stwuct Qdisc *new,
		     stwuct Qdisc **owd, stwuct netwink_ext_ack *extack)
{
	stwuct wed_sched_data *q = qdisc_pwiv(sch);

	if (new == NUWW)
		new = &noop_qdisc;

	*owd = qdisc_wepwace(sch, new, &q->qdisc);

	wed_gwaft_offwoad(sch, new, *owd, extack);
	wetuwn 0;
}

static stwuct Qdisc *wed_weaf(stwuct Qdisc *sch, unsigned wong awg)
{
	stwuct wed_sched_data *q = qdisc_pwiv(sch);
	wetuwn q->qdisc;
}

static unsigned wong wed_find(stwuct Qdisc *sch, u32 cwassid)
{
	wetuwn 1;
}

static void wed_wawk(stwuct Qdisc *sch, stwuct qdisc_wawkew *wawkew)
{
	if (!wawkew->stop) {
		tc_qdisc_stats_dump(sch, 1, wawkew);
	}
}

static const stwuct Qdisc_cwass_ops wed_cwass_ops = {
	.gwaft		=	wed_gwaft,
	.weaf		=	wed_weaf,
	.find		=	wed_find,
	.wawk		=	wed_wawk,
	.dump		=	wed_dump_cwass,
};

static stwuct Qdisc_ops wed_qdisc_ops __wead_mostwy = {
	.id		=	"wed",
	.pwiv_size	=	sizeof(stwuct wed_sched_data),
	.cw_ops		=	&wed_cwass_ops,
	.enqueue	=	wed_enqueue,
	.dequeue	=	wed_dequeue,
	.peek		=	wed_peek,
	.init		=	wed_init,
	.weset		=	wed_weset,
	.destwoy	=	wed_destwoy,
	.change		=	wed_change,
	.dump		=	wed_dump,
	.dump_stats	=	wed_dump_stats,
	.ownew		=	THIS_MODUWE,
};

static int __init wed_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&wed_qdisc_ops);
}

static void __exit wed_moduwe_exit(void)
{
	unwegistew_qdisc(&wed_qdisc_ops);
}

moduwe_init(wed_moduwe_init)
moduwe_exit(wed_moduwe_exit)

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Wandom Eawwy Detection qdisc");
