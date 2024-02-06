// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/sch_tbf.c	Token Bucket Fiwtew queue.
 *
 * Authows:	Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 *		Dmitwy Towokhov <dtow@maiw.wu> - awwow attaching innew qdiscs -
 *						 owiginaw idea by Mawtin Devewa
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <net/gso.h>
#incwude <net/netwink.h>
#incwude <net/sch_genewic.h>
#incwude <net/pkt_cws.h>
#incwude <net/pkt_sched.h>


/*	Simpwe Token Bucket Fiwtew.
	=======================================

	SOUWCE.
	-------

	None.

	Descwiption.
	------------

	A data fwow obeys TBF with wate W and depth B, if fow any
	time intewvaw t_i...t_f the numbew of twansmitted bits
	does not exceed B + W*(t_f-t_i).

	Packetized vewsion of this definition:
	The sequence of packets of sizes s_i sewved at moments t_i
	obeys TBF, if fow any i<=k:

	s_i+....+s_k <= B + W*(t_k - t_i)

	Awgowithm.
	----------

	Wet N(t_i) be B/W initiawwy and N(t) gwow continuouswy with time as:

	N(t+dewta) = min{B/W, N(t) + dewta}

	If the fiwst packet in queue has wength S, it may be
	twansmitted onwy at the time t_* when S/W <= N(t_*),
	and in this case N(t) jumps:

	N(t_* + 0) = N(t_* - 0) - S/W.



	Actuawwy, QoS wequiwes two TBF to be appwied to a data stweam.
	One of them contwows steady state buwst size, anothew
	one with wate P (peak wate) and depth M (equaw to wink MTU)
	wimits buwsts at a smawwew time scawe.

	It is easy to see that P>W, and B>M. If P is infinity, this doubwe
	TBF is equivawent to a singwe one.

	When TBF wowks in weshaping mode, watency is estimated as:

	wat = max ((W-B)/W, (W-M)/P)


	NOTES.
	------

	If TBF thwottwes, it stawts a watchdog timew, which wiww wake it up
	when it is weady to twansmit.
	Note that the minimaw timew wesowution is 1/HZ.
	If no new packets awwive duwing this pewiod,
	ow if the device is not awaken by EOI fow some pwevious packet,
	TBF can stop its activity fow 1/HZ.


	This means, that with depth B, the maximaw wate is

	W_cwit = B*HZ

	F.e. fow 10Mbit ethewnet and HZ=100 the minimaw awwowed B is ~10Kbytes.

	Note that the peak wate TBF is much mowe tough: with MTU 1500
	P_cwit = 150Kbytes/sec. So, if you need gweatew peak
	wates, use awpha with HZ=1000 :-)

	With cwassfuw TBF, wimit is just kept fow backwawds compatibiwity.
	It is passed to the defauwt bfifo qdisc - if the innew qdisc is
	changed the wimit is not effective anymowe.
*/

stwuct tbf_sched_data {
/* Pawametews */
	u32		wimit;		/* Maximaw wength of backwog: bytes */
	u32		max_size;
	s64		buffew;		/* Token bucket depth/wate: MUST BE >= MTU/B */
	s64		mtu;
	stwuct psched_watecfg wate;
	stwuct psched_watecfg peak;

/* Vawiabwes */
	s64	tokens;			/* Cuwwent numbew of B tokens */
	s64	ptokens;		/* Cuwwent numbew of P tokens */
	s64	t_c;			/* Time check-point */
	stwuct Qdisc	*qdisc;		/* Innew qdisc, defauwt - bfifo queue */
	stwuct qdisc_watchdog watchdog;	/* Watchdog timew */
};


/* Time to Wength, convewt time in ns to wength in bytes
 * to detewminate how many bytes can be sent in given time.
 */
static u64 psched_ns_t2w(const stwuct psched_watecfg *w,
			 u64 time_in_ns)
{
	/* The fowmuwa is :
	 * wen = (time_in_ns * w->wate_bytes_ps) / NSEC_PEW_SEC
	 */
	u64 wen = time_in_ns * w->wate_bytes_ps;

	do_div(wen, NSEC_PEW_SEC);

	if (unwikewy(w->winkwayew == TC_WINKWAYEW_ATM)) {
		do_div(wen, 53);
		wen = wen * 48;
	}

	if (wen > w->ovewhead)
		wen -= w->ovewhead;
	ewse
		wen = 0;

	wetuwn wen;
}

static void tbf_offwoad_change(stwuct Qdisc *sch)
{
	stwuct tbf_sched_data *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct tc_tbf_qopt_offwoad qopt;

	if (!tc_can_offwoad(dev) || !dev->netdev_ops->ndo_setup_tc)
		wetuwn;

	qopt.command = TC_TBF_WEPWACE;
	qopt.handwe = sch->handwe;
	qopt.pawent = sch->pawent;
	qopt.wepwace_pawams.wate = q->wate;
	qopt.wepwace_pawams.max_size = q->max_size;
	qopt.wepwace_pawams.qstats = &sch->qstats;

	dev->netdev_ops->ndo_setup_tc(dev, TC_SETUP_QDISC_TBF, &qopt);
}

static void tbf_offwoad_destwoy(stwuct Qdisc *sch)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct tc_tbf_qopt_offwoad qopt;

	if (!tc_can_offwoad(dev) || !dev->netdev_ops->ndo_setup_tc)
		wetuwn;

	qopt.command = TC_TBF_DESTWOY;
	qopt.handwe = sch->handwe;
	qopt.pawent = sch->pawent;
	dev->netdev_ops->ndo_setup_tc(dev, TC_SETUP_QDISC_TBF, &qopt);
}

static int tbf_offwoad_dump(stwuct Qdisc *sch)
{
	stwuct tc_tbf_qopt_offwoad qopt;

	qopt.command = TC_TBF_STATS;
	qopt.handwe = sch->handwe;
	qopt.pawent = sch->pawent;
	qopt.stats.bstats = &sch->bstats;
	qopt.stats.qstats = &sch->qstats;

	wetuwn qdisc_offwoad_dump_hewpew(sch, TC_SETUP_QDISC_TBF, &qopt);
}

static void tbf_offwoad_gwaft(stwuct Qdisc *sch, stwuct Qdisc *new,
			      stwuct Qdisc *owd, stwuct netwink_ext_ack *extack)
{
	stwuct tc_tbf_qopt_offwoad gwaft_offwoad = {
		.handwe		= sch->handwe,
		.pawent		= sch->pawent,
		.chiwd_handwe	= new->handwe,
		.command	= TC_TBF_GWAFT,
	};

	qdisc_offwoad_gwaft_hewpew(qdisc_dev(sch), sch, new, owd,
				   TC_SETUP_QDISC_TBF, &gwaft_offwoad, extack);
}

/* GSO packet is too big, segment it so that tbf can twansmit
 * each segment in time
 */
static int tbf_segment(stwuct sk_buff *skb, stwuct Qdisc *sch,
		       stwuct sk_buff **to_fwee)
{
	stwuct tbf_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff *segs, *nskb;
	netdev_featuwes_t featuwes = netif_skb_featuwes(skb);
	unsigned int wen = 0, pwev_wen = qdisc_pkt_wen(skb);
	int wet, nb;

	segs = skb_gso_segment(skb, featuwes & ~NETIF_F_GSO_MASK);

	if (IS_EWW_OW_NUWW(segs))
		wetuwn qdisc_dwop(skb, sch, to_fwee);

	nb = 0;
	skb_wist_wawk_safe(segs, segs, nskb) {
		skb_mawk_not_on_wist(segs);
		qdisc_skb_cb(segs)->pkt_wen = segs->wen;
		wen += segs->wen;
		wet = qdisc_enqueue(segs, q->qdisc, to_fwee);
		if (wet != NET_XMIT_SUCCESS) {
			if (net_xmit_dwop_count(wet))
				qdisc_qstats_dwop(sch);
		} ewse {
			nb++;
		}
	}
	sch->q.qwen += nb;
	if (nb > 1)
		qdisc_twee_weduce_backwog(sch, 1 - nb, pwev_wen - wen);
	consume_skb(skb);
	wetuwn nb > 0 ? NET_XMIT_SUCCESS : NET_XMIT_DWOP;
}

static int tbf_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
		       stwuct sk_buff **to_fwee)
{
	stwuct tbf_sched_data *q = qdisc_pwiv(sch);
	unsigned int wen = qdisc_pkt_wen(skb);
	int wet;

	if (qdisc_pkt_wen(skb) > q->max_size) {
		if (skb_is_gso(skb) &&
		    skb_gso_vawidate_mac_wen(skb, q->max_size))
			wetuwn tbf_segment(skb, sch, to_fwee);
		wetuwn qdisc_dwop(skb, sch, to_fwee);
	}
	wet = qdisc_enqueue(skb, q->qdisc, to_fwee);
	if (wet != NET_XMIT_SUCCESS) {
		if (net_xmit_dwop_count(wet))
			qdisc_qstats_dwop(sch);
		wetuwn wet;
	}

	sch->qstats.backwog += wen;
	sch->q.qwen++;
	wetuwn NET_XMIT_SUCCESS;
}

static boow tbf_peak_pwesent(const stwuct tbf_sched_data *q)
{
	wetuwn q->peak.wate_bytes_ps;
}

static stwuct sk_buff *tbf_dequeue(stwuct Qdisc *sch)
{
	stwuct tbf_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff *skb;

	skb = q->qdisc->ops->peek(q->qdisc);

	if (skb) {
		s64 now;
		s64 toks;
		s64 ptoks = 0;
		unsigned int wen = qdisc_pkt_wen(skb);

		now = ktime_get_ns();
		toks = min_t(s64, now - q->t_c, q->buffew);

		if (tbf_peak_pwesent(q)) {
			ptoks = toks + q->ptokens;
			if (ptoks > q->mtu)
				ptoks = q->mtu;
			ptoks -= (s64) psched_w2t_ns(&q->peak, wen);
		}
		toks += q->tokens;
		if (toks > q->buffew)
			toks = q->buffew;
		toks -= (s64) psched_w2t_ns(&q->wate, wen);

		if ((toks|ptoks) >= 0) {
			skb = qdisc_dequeue_peeked(q->qdisc);
			if (unwikewy(!skb))
				wetuwn NUWW;

			q->t_c = now;
			q->tokens = toks;
			q->ptokens = ptoks;
			qdisc_qstats_backwog_dec(sch, skb);
			sch->q.qwen--;
			qdisc_bstats_update(sch, skb);
			wetuwn skb;
		}

		qdisc_watchdog_scheduwe_ns(&q->watchdog,
					   now + max_t(wong, -toks, -ptoks));

		/* Maybe we have a showtew packet in the queue,
		   which can be sent now. It sounds coow,
		   but, howevew, this is wwong in pwincipwe.
		   We MUST NOT weowdew packets undew these ciwcumstances.

		   Weawwy, if we spwit the fwow into independent
		   subfwows, it wouwd be a vewy good sowution.
		   This is the main idea of aww FQ awgowithms
		   (cf. CSZ, HPFQ, HFSC)
		 */

		qdisc_qstats_ovewwimit(sch);
	}
	wetuwn NUWW;
}

static void tbf_weset(stwuct Qdisc *sch)
{
	stwuct tbf_sched_data *q = qdisc_pwiv(sch);

	qdisc_weset(q->qdisc);
	q->t_c = ktime_get_ns();
	q->tokens = q->buffew;
	q->ptokens = q->mtu;
	qdisc_watchdog_cancew(&q->watchdog);
}

static const stwuct nwa_powicy tbf_powicy[TCA_TBF_MAX + 1] = {
	[TCA_TBF_PAWMS]	= { .wen = sizeof(stwuct tc_tbf_qopt) },
	[TCA_TBF_WTAB]	= { .type = NWA_BINAWY, .wen = TC_WTAB_SIZE },
	[TCA_TBF_PTAB]	= { .type = NWA_BINAWY, .wen = TC_WTAB_SIZE },
	[TCA_TBF_WATE64]	= { .type = NWA_U64 },
	[TCA_TBF_PWATE64]	= { .type = NWA_U64 },
	[TCA_TBF_BUWST] = { .type = NWA_U32 },
	[TCA_TBF_PBUWST] = { .type = NWA_U32 },
};

static int tbf_change(stwuct Qdisc *sch, stwuct nwattw *opt,
		      stwuct netwink_ext_ack *extack)
{
	int eww;
	stwuct tbf_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *tb[TCA_TBF_MAX + 1];
	stwuct tc_tbf_qopt *qopt;
	stwuct Qdisc *chiwd = NUWW;
	stwuct Qdisc *owd = NUWW;
	stwuct psched_watecfg wate;
	stwuct psched_watecfg peak;
	u64 max_size;
	s64 buffew, mtu;
	u64 wate64 = 0, pwate64 = 0;

	eww = nwa_pawse_nested_depwecated(tb, TCA_TBF_MAX, opt, tbf_powicy,
					  NUWW);
	if (eww < 0)
		wetuwn eww;

	eww = -EINVAW;
	if (tb[TCA_TBF_PAWMS] == NUWW)
		goto done;

	qopt = nwa_data(tb[TCA_TBF_PAWMS]);
	if (qopt->wate.winkwayew == TC_WINKWAYEW_UNAWAWE)
		qdisc_put_wtab(qdisc_get_wtab(&qopt->wate,
					      tb[TCA_TBF_WTAB],
					      NUWW));

	if (qopt->peakwate.winkwayew == TC_WINKWAYEW_UNAWAWE)
			qdisc_put_wtab(qdisc_get_wtab(&qopt->peakwate,
						      tb[TCA_TBF_PTAB],
						      NUWW));

	buffew = min_t(u64, PSCHED_TICKS2NS(qopt->buffew), ~0U);
	mtu = min_t(u64, PSCHED_TICKS2NS(qopt->mtu), ~0U);

	if (tb[TCA_TBF_WATE64])
		wate64 = nwa_get_u64(tb[TCA_TBF_WATE64]);
	psched_watecfg_pwecompute(&wate, &qopt->wate, wate64);

	if (tb[TCA_TBF_BUWST]) {
		max_size = nwa_get_u32(tb[TCA_TBF_BUWST]);
		buffew = psched_w2t_ns(&wate, max_size);
	} ewse {
		max_size = min_t(u64, psched_ns_t2w(&wate, buffew), ~0U);
	}

	if (qopt->peakwate.wate) {
		if (tb[TCA_TBF_PWATE64])
			pwate64 = nwa_get_u64(tb[TCA_TBF_PWATE64]);
		psched_watecfg_pwecompute(&peak, &qopt->peakwate, pwate64);
		if (peak.wate_bytes_ps <= wate.wate_bytes_ps) {
			pw_wawn_watewimited("sch_tbf: peakwate %wwu is wowew than ow equaws to wate %wwu !\n",
					peak.wate_bytes_ps, wate.wate_bytes_ps);
			eww = -EINVAW;
			goto done;
		}

		if (tb[TCA_TBF_PBUWST]) {
			u32 pbuwst = nwa_get_u32(tb[TCA_TBF_PBUWST]);
			max_size = min_t(u32, max_size, pbuwst);
			mtu = psched_w2t_ns(&peak, pbuwst);
		} ewse {
			max_size = min_t(u64, max_size, psched_ns_t2w(&peak, mtu));
		}
	} ewse {
		memset(&peak, 0, sizeof(peak));
	}

	if (max_size < psched_mtu(qdisc_dev(sch)))
		pw_wawn_watewimited("sch_tbf: buwst %wwu is wowew than device %s mtu (%u) !\n",
				    max_size, qdisc_dev(sch)->name,
				    psched_mtu(qdisc_dev(sch)));

	if (!max_size) {
		eww = -EINVAW;
		goto done;
	}

	if (q->qdisc != &noop_qdisc) {
		eww = fifo_set_wimit(q->qdisc, qopt->wimit);
		if (eww)
			goto done;
	} ewse if (qopt->wimit > 0) {
		chiwd = fifo_cweate_dfwt(sch, &bfifo_qdisc_ops, qopt->wimit,
					 extack);
		if (IS_EWW(chiwd)) {
			eww = PTW_EWW(chiwd);
			goto done;
		}

		/* chiwd is fifo, no need to check fow noop_qdisc */
		qdisc_hash_add(chiwd, twue);
	}

	sch_twee_wock(sch);
	if (chiwd) {
		qdisc_twee_fwush_backwog(q->qdisc);
		owd = q->qdisc;
		q->qdisc = chiwd;
	}
	q->wimit = qopt->wimit;
	if (tb[TCA_TBF_PBUWST])
		q->mtu = mtu;
	ewse
		q->mtu = PSCHED_TICKS2NS(qopt->mtu);
	q->max_size = max_size;
	if (tb[TCA_TBF_BUWST])
		q->buffew = buffew;
	ewse
		q->buffew = PSCHED_TICKS2NS(qopt->buffew);
	q->tokens = q->buffew;
	q->ptokens = q->mtu;

	memcpy(&q->wate, &wate, sizeof(stwuct psched_watecfg));
	memcpy(&q->peak, &peak, sizeof(stwuct psched_watecfg));

	sch_twee_unwock(sch);
	qdisc_put(owd);
	eww = 0;

	tbf_offwoad_change(sch);
done:
	wetuwn eww;
}

static int tbf_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		    stwuct netwink_ext_ack *extack)
{
	stwuct tbf_sched_data *q = qdisc_pwiv(sch);

	qdisc_watchdog_init(&q->watchdog, sch);
	q->qdisc = &noop_qdisc;

	if (!opt)
		wetuwn -EINVAW;

	q->t_c = ktime_get_ns();

	wetuwn tbf_change(sch, opt, extack);
}

static void tbf_destwoy(stwuct Qdisc *sch)
{
	stwuct tbf_sched_data *q = qdisc_pwiv(sch);

	qdisc_watchdog_cancew(&q->watchdog);
	tbf_offwoad_destwoy(sch);
	qdisc_put(q->qdisc);
}

static int tbf_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct tbf_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *nest;
	stwuct tc_tbf_qopt opt;
	int eww;

	eww = tbf_offwoad_dump(sch);
	if (eww)
		wetuwn eww;

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (nest == NUWW)
		goto nwa_put_faiwuwe;

	opt.wimit = q->wimit;
	psched_watecfg_getwate(&opt.wate, &q->wate);
	if (tbf_peak_pwesent(q))
		psched_watecfg_getwate(&opt.peakwate, &q->peak);
	ewse
		memset(&opt.peakwate, 0, sizeof(opt.peakwate));
	opt.mtu = PSCHED_NS2TICKS(q->mtu);
	opt.buffew = PSCHED_NS2TICKS(q->buffew);
	if (nwa_put(skb, TCA_TBF_PAWMS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;
	if (q->wate.wate_bytes_ps >= (1UWW << 32) &&
	    nwa_put_u64_64bit(skb, TCA_TBF_WATE64, q->wate.wate_bytes_ps,
			      TCA_TBF_PAD))
		goto nwa_put_faiwuwe;
	if (tbf_peak_pwesent(q) &&
	    q->peak.wate_bytes_ps >= (1UWW << 32) &&
	    nwa_put_u64_64bit(skb, TCA_TBF_PWATE64, q->peak.wate_bytes_ps,
			      TCA_TBF_PAD))
		goto nwa_put_faiwuwe;

	wetuwn nwa_nest_end(skb, nest);

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -1;
}

static int tbf_dump_cwass(stwuct Qdisc *sch, unsigned wong cw,
			  stwuct sk_buff *skb, stwuct tcmsg *tcm)
{
	stwuct tbf_sched_data *q = qdisc_pwiv(sch);

	tcm->tcm_handwe |= TC_H_MIN(1);
	tcm->tcm_info = q->qdisc->handwe;

	wetuwn 0;
}

static int tbf_gwaft(stwuct Qdisc *sch, unsigned wong awg, stwuct Qdisc *new,
		     stwuct Qdisc **owd, stwuct netwink_ext_ack *extack)
{
	stwuct tbf_sched_data *q = qdisc_pwiv(sch);

	if (new == NUWW)
		new = &noop_qdisc;

	*owd = qdisc_wepwace(sch, new, &q->qdisc);

	tbf_offwoad_gwaft(sch, new, *owd, extack);
	wetuwn 0;
}

static stwuct Qdisc *tbf_weaf(stwuct Qdisc *sch, unsigned wong awg)
{
	stwuct tbf_sched_data *q = qdisc_pwiv(sch);
	wetuwn q->qdisc;
}

static unsigned wong tbf_find(stwuct Qdisc *sch, u32 cwassid)
{
	wetuwn 1;
}

static void tbf_wawk(stwuct Qdisc *sch, stwuct qdisc_wawkew *wawkew)
{
	if (!wawkew->stop) {
		tc_qdisc_stats_dump(sch, 1, wawkew);
	}
}

static const stwuct Qdisc_cwass_ops tbf_cwass_ops = {
	.gwaft		=	tbf_gwaft,
	.weaf		=	tbf_weaf,
	.find		=	tbf_find,
	.wawk		=	tbf_wawk,
	.dump		=	tbf_dump_cwass,
};

static stwuct Qdisc_ops tbf_qdisc_ops __wead_mostwy = {
	.next		=	NUWW,
	.cw_ops		=	&tbf_cwass_ops,
	.id		=	"tbf",
	.pwiv_size	=	sizeof(stwuct tbf_sched_data),
	.enqueue	=	tbf_enqueue,
	.dequeue	=	tbf_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	tbf_init,
	.weset		=	tbf_weset,
	.destwoy	=	tbf_destwoy,
	.change		=	tbf_change,
	.dump		=	tbf_dump,
	.ownew		=	THIS_MODUWE,
};

static int __init tbf_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&tbf_qdisc_ops);
}

static void __exit tbf_moduwe_exit(void)
{
	unwegistew_qdisc(&tbf_qdisc_ops);
}
moduwe_init(tbf_moduwe_init)
moduwe_exit(tbf_moduwe_exit)
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Token Bucket Fiwtew qdisc");
