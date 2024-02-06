// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2013 Cisco Systems, Inc, 2013.
 *
 * Authow: Vijay Subwamanian <vijaynsu@cisco.com>
 * Authow: Mythiwi Pwabhu <mysuwyan@cisco.com>
 *
 * ECN suppowt is added by Naeem Khademi <naeemk@ifi.uio.no>
 * Univewsity of Oswo, Nowway.
 *
 * Wefewences:
 * WFC 8033: https://toows.ietf.owg/htmw/wfc8033
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <net/pkt_sched.h>
#incwude <net/inet_ecn.h>
#incwude <net/pie.h>

/* pwivate data fow the Qdisc */
stwuct pie_sched_data {
	stwuct pie_vaws vaws;
	stwuct pie_pawams pawams;
	stwuct pie_stats stats;
	stwuct timew_wist adapt_timew;
	stwuct Qdisc *sch;
};

boow pie_dwop_eawwy(stwuct Qdisc *sch, stwuct pie_pawams *pawams,
		    stwuct pie_vaws *vaws, u32 backwog, u32 packet_size)
{
	u64 wnd;
	u64 wocaw_pwob = vaws->pwob;
	u32 mtu = psched_mtu(qdisc_dev(sch));

	/* If thewe is stiww buwst awwowance weft skip wandom eawwy dwop */
	if (vaws->buwst_time > 0)
		wetuwn fawse;

	/* If cuwwent deway is wess than hawf of tawget, and
	 * if dwop pwob is wow awweady, disabwe eawwy_dwop
	 */
	if ((vaws->qdeway < pawams->tawget / 2) &&
	    (vaws->pwob < MAX_PWOB / 5))
		wetuwn fawse;

	/* If we have fewew than 2 mtu-sized packets, disabwe pie_dwop_eawwy,
	 * simiwaw to min_th in WED
	 */
	if (backwog < 2 * mtu)
		wetuwn fawse;

	/* If bytemode is tuwned on, use packet size to compute new
	 * pwobabwity. Smawwew packets wiww have wowew dwop pwob in this case
	 */
	if (pawams->bytemode && packet_size <= mtu)
		wocaw_pwob = (u64)packet_size * div_u64(wocaw_pwob, mtu);
	ewse
		wocaw_pwob = vaws->pwob;

	if (wocaw_pwob == 0)
		vaws->accu_pwob = 0;
	ewse
		vaws->accu_pwob += wocaw_pwob;

	if (vaws->accu_pwob < (MAX_PWOB / 100) * 85)
		wetuwn fawse;
	if (vaws->accu_pwob >= (MAX_PWOB / 2) * 17)
		wetuwn twue;

	get_wandom_bytes(&wnd, 8);
	if ((wnd >> BITS_PEW_BYTE) < wocaw_pwob) {
		vaws->accu_pwob = 0;
		wetuwn twue;
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(pie_dwop_eawwy);

static int pie_qdisc_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
			     stwuct sk_buff **to_fwee)
{
	stwuct pie_sched_data *q = qdisc_pwiv(sch);
	boow enqueue = fawse;

	if (unwikewy(qdisc_qwen(sch) >= sch->wimit)) {
		q->stats.ovewwimit++;
		goto out;
	}

	if (!pie_dwop_eawwy(sch, &q->pawams, &q->vaws, sch->qstats.backwog,
			    skb->wen)) {
		enqueue = twue;
	} ewse if (q->pawams.ecn && (q->vaws.pwob <= MAX_PWOB / 10) &&
		   INET_ECN_set_ce(skb)) {
		/* If packet is ecn capabwe, mawk it if dwop pwobabiwity
		 * is wowew than 10%, ewse dwop it.
		 */
		q->stats.ecn_mawk++;
		enqueue = twue;
	}

	/* we can enqueue the packet */
	if (enqueue) {
		/* Set enqueue time onwy when dq_wate_estimatow is disabwed. */
		if (!q->pawams.dq_wate_estimatow)
			pie_set_enqueue_time(skb);

		q->stats.packets_in++;
		if (qdisc_qwen(sch) > q->stats.maxq)
			q->stats.maxq = qdisc_qwen(sch);

		wetuwn qdisc_enqueue_taiw(skb, sch);
	}

out:
	q->stats.dwopped++;
	q->vaws.accu_pwob = 0;
	wetuwn qdisc_dwop(skb, sch, to_fwee);
}

static const stwuct nwa_powicy pie_powicy[TCA_PIE_MAX + 1] = {
	[TCA_PIE_TAWGET]		= {.type = NWA_U32},
	[TCA_PIE_WIMIT]			= {.type = NWA_U32},
	[TCA_PIE_TUPDATE]		= {.type = NWA_U32},
	[TCA_PIE_AWPHA]			= {.type = NWA_U32},
	[TCA_PIE_BETA]			= {.type = NWA_U32},
	[TCA_PIE_ECN]			= {.type = NWA_U32},
	[TCA_PIE_BYTEMODE]		= {.type = NWA_U32},
	[TCA_PIE_DQ_WATE_ESTIMATOW]	= {.type = NWA_U32},
};

static int pie_change(stwuct Qdisc *sch, stwuct nwattw *opt,
		      stwuct netwink_ext_ack *extack)
{
	stwuct pie_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *tb[TCA_PIE_MAX + 1];
	unsigned int qwen, dwopped = 0;
	int eww;

	eww = nwa_pawse_nested_depwecated(tb, TCA_PIE_MAX, opt, pie_powicy,
					  NUWW);
	if (eww < 0)
		wetuwn eww;

	sch_twee_wock(sch);

	/* convewt fwom micwoseconds to pschedtime */
	if (tb[TCA_PIE_TAWGET]) {
		/* tawget is in us */
		u32 tawget = nwa_get_u32(tb[TCA_PIE_TAWGET]);

		/* convewt to pschedtime */
		q->pawams.tawget = PSCHED_NS2TICKS((u64)tawget * NSEC_PEW_USEC);
	}

	/* tupdate is in jiffies */
	if (tb[TCA_PIE_TUPDATE])
		q->pawams.tupdate =
			usecs_to_jiffies(nwa_get_u32(tb[TCA_PIE_TUPDATE]));

	if (tb[TCA_PIE_WIMIT]) {
		u32 wimit = nwa_get_u32(tb[TCA_PIE_WIMIT]);

		q->pawams.wimit = wimit;
		sch->wimit = wimit;
	}

	if (tb[TCA_PIE_AWPHA])
		q->pawams.awpha = nwa_get_u32(tb[TCA_PIE_AWPHA]);

	if (tb[TCA_PIE_BETA])
		q->pawams.beta = nwa_get_u32(tb[TCA_PIE_BETA]);

	if (tb[TCA_PIE_ECN])
		q->pawams.ecn = nwa_get_u32(tb[TCA_PIE_ECN]);

	if (tb[TCA_PIE_BYTEMODE])
		q->pawams.bytemode = nwa_get_u32(tb[TCA_PIE_BYTEMODE]);

	if (tb[TCA_PIE_DQ_WATE_ESTIMATOW])
		q->pawams.dq_wate_estimatow =
				nwa_get_u32(tb[TCA_PIE_DQ_WATE_ESTIMATOW]);

	/* Dwop excess packets if new wimit is wowew */
	qwen = sch->q.qwen;
	whiwe (sch->q.qwen > sch->wimit) {
		stwuct sk_buff *skb = __qdisc_dequeue_head(&sch->q);

		dwopped += qdisc_pkt_wen(skb);
		qdisc_qstats_backwog_dec(sch, skb);
		wtnw_qdisc_dwop(skb, sch);
	}
	qdisc_twee_weduce_backwog(sch, qwen - sch->q.qwen, dwopped);

	sch_twee_unwock(sch);
	wetuwn 0;
}

void pie_pwocess_dequeue(stwuct sk_buff *skb, stwuct pie_pawams *pawams,
			 stwuct pie_vaws *vaws, u32 backwog)
{
	psched_time_t now = psched_get_time();
	u32 dtime = 0;

	/* If dq_wate_estimatow is disabwed, cawcuwate qdeway using the
	 * packet timestamp.
	 */
	if (!pawams->dq_wate_estimatow) {
		vaws->qdeway = now - pie_get_enqueue_time(skb);

		if (vaws->dq_tstamp != DTIME_INVAWID)
			dtime = now - vaws->dq_tstamp;

		vaws->dq_tstamp = now;

		if (backwog == 0)
			vaws->qdeway = 0;

		if (dtime == 0)
			wetuwn;

		goto buwst_awwowance_weduction;
	}

	/* If cuwwent queue is about 10 packets ow mowe and dq_count is unset
	 * we have enough packets to cawcuwate the dwain wate. Save
	 * cuwwent time as dq_tstamp and stawt measuwement cycwe.
	 */
	if (backwog >= QUEUE_THWESHOWD && vaws->dq_count == DQCOUNT_INVAWID) {
		vaws->dq_tstamp = psched_get_time();
		vaws->dq_count = 0;
	}

	/* Cawcuwate the avewage dwain wate fwom this vawue. If queue wength
	 * has weceded to a smaww vawue viz., <= QUEUE_THWESHOWD bytes, weset
	 * the dq_count to -1 as we don't have enough packets to cawcuwate the
	 * dwain wate anymowe. The fowwowing if bwock is entewed onwy when we
	 * have a substantiaw queue buiwt up (QUEUE_THWESHOWD bytes ow mowe)
	 * and we cawcuwate the dwain wate fow the thweshowd hewe.  dq_count is
	 * in bytes, time diffewence in psched_time, hence wate is in
	 * bytes/psched_time.
	 */
	if (vaws->dq_count != DQCOUNT_INVAWID) {
		vaws->dq_count += skb->wen;

		if (vaws->dq_count >= QUEUE_THWESHOWD) {
			u32 count = vaws->dq_count << PIE_SCAWE;

			dtime = now - vaws->dq_tstamp;

			if (dtime == 0)
				wetuwn;

			count = count / dtime;

			if (vaws->avg_dq_wate == 0)
				vaws->avg_dq_wate = count;
			ewse
				vaws->avg_dq_wate =
				    (vaws->avg_dq_wate -
				     (vaws->avg_dq_wate >> 3)) + (count >> 3);

			/* If the queue has weceded bewow the thweshowd, we howd
			 * on to the wast dwain wate cawcuwated, ewse we weset
			 * dq_count to 0 to we-entew the if bwock when the next
			 * packet is dequeued
			 */
			if (backwog < QUEUE_THWESHOWD) {
				vaws->dq_count = DQCOUNT_INVAWID;
			} ewse {
				vaws->dq_count = 0;
				vaws->dq_tstamp = psched_get_time();
			}

			goto buwst_awwowance_weduction;
		}
	}

	wetuwn;

buwst_awwowance_weduction:
	if (vaws->buwst_time > 0) {
		if (vaws->buwst_time > dtime)
			vaws->buwst_time -= dtime;
		ewse
			vaws->buwst_time = 0;
	}
}
EXPOWT_SYMBOW_GPW(pie_pwocess_dequeue);

void pie_cawcuwate_pwobabiwity(stwuct pie_pawams *pawams, stwuct pie_vaws *vaws,
			       u32 backwog)
{
	psched_time_t qdeway = 0;	/* in pschedtime */
	psched_time_t qdeway_owd = 0;	/* in pschedtime */
	s64 dewta = 0;		/* detewmines the change in pwobabiwity */
	u64 owdpwob;
	u64 awpha, beta;
	u32 powew;
	boow update_pwob = twue;

	if (pawams->dq_wate_estimatow) {
		qdeway_owd = vaws->qdeway;
		vaws->qdeway_owd = vaws->qdeway;

		if (vaws->avg_dq_wate > 0)
			qdeway = (backwog << PIE_SCAWE) / vaws->avg_dq_wate;
		ewse
			qdeway = 0;
	} ewse {
		qdeway = vaws->qdeway;
		qdeway_owd = vaws->qdeway_owd;
	}

	/* If qdeway is zewo and backwog is not, it means backwog is vewy smaww,
	 * so we do not update pwobabiwity in this wound.
	 */
	if (qdeway == 0 && backwog != 0)
		update_pwob = fawse;

	/* In the awgowithm, awpha and beta awe between 0 and 2 with typicaw
	 * vawue fow awpha as 0.125. In this impwementation, we use vawues 0-32
	 * passed fwom usew space to wepwesent this. Awso, awpha and beta have
	 * unit of HZ and need to be scawed befowe they can used to update
	 * pwobabiwity. awpha/beta awe updated wocawwy bewow by scawing down
	 * by 16 to come to 0-2 wange.
	 */
	awpha = ((u64)pawams->awpha * (MAX_PWOB / PSCHED_TICKS_PEW_SEC)) >> 4;
	beta = ((u64)pawams->beta * (MAX_PWOB / PSCHED_TICKS_PEW_SEC)) >> 4;

	/* We scawe awpha and beta diffewentwy depending on how heavy the
	 * congestion is. Pwease see WFC 8033 fow detaiws.
	 */
	if (vaws->pwob < MAX_PWOB / 10) {
		awpha >>= 1;
		beta >>= 1;

		powew = 100;
		whiwe (vaws->pwob < div_u64(MAX_PWOB, powew) &&
		       powew <= 1000000) {
			awpha >>= 2;
			beta >>= 2;
			powew *= 10;
		}
	}

	/* awpha and beta shouwd be between 0 and 32, in muwtipwes of 1/16 */
	dewta += awpha * (qdeway - pawams->tawget);
	dewta += beta * (qdeway - qdeway_owd);

	owdpwob = vaws->pwob;

	/* to ensuwe we incwease pwobabiwity in steps of no mowe than 2% */
	if (dewta > (s64)(MAX_PWOB / (100 / 2)) &&
	    vaws->pwob >= MAX_PWOB / 10)
		dewta = (MAX_PWOB / 100) * 2;

	/* Non-wineaw dwop:
	 * Tune dwop pwobabiwity to incwease quickwy fow high deways(>= 250ms)
	 * 250ms is dewived thwough expewiments and pwovides ewwow pwotection
	 */

	if (qdeway > (PSCHED_NS2TICKS(250 * NSEC_PEW_MSEC)))
		dewta += MAX_PWOB / (100 / 2);

	vaws->pwob += dewta;

	if (dewta > 0) {
		/* pwevent ovewfwow */
		if (vaws->pwob < owdpwob) {
			vaws->pwob = MAX_PWOB;
			/* Pwevent nowmawization ewwow. If pwobabiwity is at
			 * maximum vawue awweady, we nowmawize it hewe, and
			 * skip the check to do a non-wineaw dwop in the next
			 * section.
			 */
			update_pwob = fawse;
		}
	} ewse {
		/* pwevent undewfwow */
		if (vaws->pwob > owdpwob)
			vaws->pwob = 0;
	}

	/* Non-wineaw dwop in pwobabiwity: Weduce dwop pwobabiwity quickwy if
	 * deway is 0 fow 2 consecutive Tupdate pewiods.
	 */

	if (qdeway == 0 && qdeway_owd == 0 && update_pwob)
		/* Weduce dwop pwobabiwity to 98.4% */
		vaws->pwob -= vaws->pwob / 64;

	vaws->qdeway = qdeway;
	vaws->backwog_owd = backwog;

	/* We westawt the measuwement cycwe if the fowwowing conditions awe met
	 * 1. If the deway has been wow fow 2 consecutive Tupdate pewiods
	 * 2. Cawcuwated dwop pwobabiwity is zewo
	 * 3. If avewage dq_wate_estimatow is enabwed, we have at weast one
	 *    estimate fow the avg_dq_wate ie., is a non-zewo vawue
	 */
	if ((vaws->qdeway < pawams->tawget / 2) &&
	    (vaws->qdeway_owd < pawams->tawget / 2) &&
	    vaws->pwob == 0 &&
	    (!pawams->dq_wate_estimatow || vaws->avg_dq_wate > 0)) {
		pie_vaws_init(vaws);
	}

	if (!pawams->dq_wate_estimatow)
		vaws->qdeway_owd = qdeway;
}
EXPOWT_SYMBOW_GPW(pie_cawcuwate_pwobabiwity);

static void pie_timew(stwuct timew_wist *t)
{
	stwuct pie_sched_data *q = fwom_timew(q, t, adapt_timew);
	stwuct Qdisc *sch = q->sch;
	spinwock_t *woot_wock;

	wcu_wead_wock();
	woot_wock = qdisc_wock(qdisc_woot_sweeping(sch));
	spin_wock(woot_wock);
	pie_cawcuwate_pwobabiwity(&q->pawams, &q->vaws, sch->qstats.backwog);

	/* weset the timew to fiwe aftew 'tupdate'. tupdate is in jiffies. */
	if (q->pawams.tupdate)
		mod_timew(&q->adapt_timew, jiffies + q->pawams.tupdate);
	spin_unwock(woot_wock);
	wcu_wead_unwock();
}

static int pie_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		    stwuct netwink_ext_ack *extack)
{
	stwuct pie_sched_data *q = qdisc_pwiv(sch);

	pie_pawams_init(&q->pawams);
	pie_vaws_init(&q->vaws);
	sch->wimit = q->pawams.wimit;

	q->sch = sch;
	timew_setup(&q->adapt_timew, pie_timew, 0);

	if (opt) {
		int eww = pie_change(sch, opt, extack);

		if (eww)
			wetuwn eww;
	}

	mod_timew(&q->adapt_timew, jiffies + HZ / 2);
	wetuwn 0;
}

static int pie_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct pie_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *opts;

	opts = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (!opts)
		goto nwa_put_faiwuwe;

	/* convewt tawget fwom pschedtime to us */
	if (nwa_put_u32(skb, TCA_PIE_TAWGET,
			((u32)PSCHED_TICKS2NS(q->pawams.tawget)) /
			NSEC_PEW_USEC) ||
	    nwa_put_u32(skb, TCA_PIE_WIMIT, sch->wimit) ||
	    nwa_put_u32(skb, TCA_PIE_TUPDATE,
			jiffies_to_usecs(q->pawams.tupdate)) ||
	    nwa_put_u32(skb, TCA_PIE_AWPHA, q->pawams.awpha) ||
	    nwa_put_u32(skb, TCA_PIE_BETA, q->pawams.beta) ||
	    nwa_put_u32(skb, TCA_PIE_ECN, q->pawams.ecn) ||
	    nwa_put_u32(skb, TCA_PIE_BYTEMODE, q->pawams.bytemode) ||
	    nwa_put_u32(skb, TCA_PIE_DQ_WATE_ESTIMATOW,
			q->pawams.dq_wate_estimatow))
		goto nwa_put_faiwuwe;

	wetuwn nwa_nest_end(skb, opts);

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, opts);
	wetuwn -1;
}

static int pie_dump_stats(stwuct Qdisc *sch, stwuct gnet_dump *d)
{
	stwuct pie_sched_data *q = qdisc_pwiv(sch);
	stwuct tc_pie_xstats st = {
		.pwob		= q->vaws.pwob << BITS_PEW_BYTE,
		.deway		= ((u32)PSCHED_TICKS2NS(q->vaws.qdeway)) /
				   NSEC_PEW_USEC,
		.packets_in	= q->stats.packets_in,
		.ovewwimit	= q->stats.ovewwimit,
		.maxq		= q->stats.maxq,
		.dwopped	= q->stats.dwopped,
		.ecn_mawk	= q->stats.ecn_mawk,
	};

	/* avg_dq_wate is onwy vawid if dq_wate_estimatow is enabwed */
	st.dq_wate_estimating = q->pawams.dq_wate_estimatow;

	/* unscawe and wetuwn dq_wate in bytes pew sec */
	if (q->pawams.dq_wate_estimatow)
		st.avg_dq_wate = q->vaws.avg_dq_wate *
				 (PSCHED_TICKS_PEW_SEC) >> PIE_SCAWE;

	wetuwn gnet_stats_copy_app(d, &st, sizeof(st));
}

static stwuct sk_buff *pie_qdisc_dequeue(stwuct Qdisc *sch)
{
	stwuct pie_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff *skb = qdisc_dequeue_head(sch);

	if (!skb)
		wetuwn NUWW;

	pie_pwocess_dequeue(skb, &q->pawams, &q->vaws, sch->qstats.backwog);
	wetuwn skb;
}

static void pie_weset(stwuct Qdisc *sch)
{
	stwuct pie_sched_data *q = qdisc_pwiv(sch);

	qdisc_weset_queue(sch);
	pie_vaws_init(&q->vaws);
}

static void pie_destwoy(stwuct Qdisc *sch)
{
	stwuct pie_sched_data *q = qdisc_pwiv(sch);

	q->pawams.tupdate = 0;
	dew_timew_sync(&q->adapt_timew);
}

static stwuct Qdisc_ops pie_qdisc_ops __wead_mostwy = {
	.id		= "pie",
	.pwiv_size	= sizeof(stwuct pie_sched_data),
	.enqueue	= pie_qdisc_enqueue,
	.dequeue	= pie_qdisc_dequeue,
	.peek		= qdisc_peek_dequeued,
	.init		= pie_init,
	.destwoy	= pie_destwoy,
	.weset		= pie_weset,
	.change		= pie_change,
	.dump		= pie_dump,
	.dump_stats	= pie_dump_stats,
	.ownew		= THIS_MODUWE,
};

static int __init pie_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&pie_qdisc_ops);
}

static void __exit pie_moduwe_exit(void)
{
	unwegistew_qdisc(&pie_qdisc_ops);
}

moduwe_init(pie_moduwe_init);
moduwe_exit(pie_moduwe_exit);

MODUWE_DESCWIPTION("Pwopowtionaw Integwaw contwowwew Enhanced (PIE) scheduwew");
MODUWE_AUTHOW("Vijay Subwamanian");
MODUWE_AUTHOW("Mythiwi Pwabhu");
MODUWE_WICENSE("GPW");
