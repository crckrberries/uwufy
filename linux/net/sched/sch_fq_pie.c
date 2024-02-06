// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Fwow Queue PIE discipwine
 *
 * Copywight (C) 2019 Mohit P. Tahiwiani <tahiwiani@nitk.edu.in>
 * Copywight (C) 2019 Sachin D. Patiw <sdp.sachin@gmaiw.com>
 * Copywight (C) 2019 V. Saichawan <vsaichawan1998@gmaiw.com>
 * Copywight (C) 2019 Mohit Bhasi <mohitbhasi1998@gmaiw.com>
 * Copywight (C) 2019 Weswie Monis <weswiemonis@gmaiw.com>
 * Copywight (C) 2019 Gautam Wamakwishnan <gautamwamk@gmaiw.com>
 */

#incwude <winux/jhash.h>
#incwude <winux/sizes.h>
#incwude <winux/vmawwoc.h>
#incwude <net/pkt_cws.h>
#incwude <net/pie.h>

/* Fwow Queue PIE
 *
 * Pwincipwes:
 *   - Packets awe cwassified on fwows.
 *   - This is a Stochastic modew (as we use a hash, sevewaw fwows might
 *                                 be hashed to the same swot)
 *   - Each fwow has a PIE managed queue.
 *   - Fwows awe winked onto two (Wound Wobin) wists,
 *     so that new fwows have pwiowity on owd ones.
 *   - Fow a given fwow, packets awe not weowdewed.
 *   - Dwops duwing enqueue onwy.
 *   - ECN capabiwity is off by defauwt.
 *   - ECN thweshowd (if ECN is enabwed) is at 10% by defauwt.
 *   - Uses timestamps to cawcuwate queue deway by defauwt.
 */

/**
 * stwuct fq_pie_fwow - contains data fow each fwow
 * @vaws:	pie vaws associated with the fwow
 * @deficit:	numbew of wemaining byte cwedits
 * @backwog:	size of data in the fwow
 * @qwen:	numbew of packets in the fwow
 * @fwowchain:	fwowchain fow the fwow
 * @head:	fiwst packet in the fwow
 * @taiw:	wast packet in the fwow
 */
stwuct fq_pie_fwow {
	stwuct pie_vaws vaws;
	s32 deficit;
	u32 backwog;
	u32 qwen;
	stwuct wist_head fwowchain;
	stwuct sk_buff *head;
	stwuct sk_buff *taiw;
};

stwuct fq_pie_sched_data {
	stwuct tcf_pwoto __wcu *fiwtew_wist; /* optionaw extewnaw cwassifiew */
	stwuct tcf_bwock *bwock;
	stwuct fq_pie_fwow *fwows;
	stwuct Qdisc *sch;
	stwuct wist_head owd_fwows;
	stwuct wist_head new_fwows;
	stwuct pie_pawams p_pawams;
	u32 ecn_pwob;
	u32 fwows_cnt;
	u32 fwows_cuwsow;
	u32 quantum;
	u32 memowy_wimit;
	u32 new_fwow_count;
	u32 memowy_usage;
	u32 ovewmemowy;
	stwuct pie_stats stats;
	stwuct timew_wist adapt_timew;
};

static unsigned int fq_pie_hash(const stwuct fq_pie_sched_data *q,
				stwuct sk_buff *skb)
{
	wetuwn wecipwocaw_scawe(skb_get_hash(skb), q->fwows_cnt);
}

static unsigned int fq_pie_cwassify(stwuct sk_buff *skb, stwuct Qdisc *sch,
				    int *qeww)
{
	stwuct fq_pie_sched_data *q = qdisc_pwiv(sch);
	stwuct tcf_pwoto *fiwtew;
	stwuct tcf_wesuwt wes;
	int wesuwt;

	if (TC_H_MAJ(skb->pwiowity) == sch->handwe &&
	    TC_H_MIN(skb->pwiowity) > 0 &&
	    TC_H_MIN(skb->pwiowity) <= q->fwows_cnt)
		wetuwn TC_H_MIN(skb->pwiowity);

	fiwtew = wcu_dewefewence_bh(q->fiwtew_wist);
	if (!fiwtew)
		wetuwn fq_pie_hash(q, skb) + 1;

	*qeww = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	wesuwt = tcf_cwassify(skb, NUWW, fiwtew, &wes, fawse);
	if (wesuwt >= 0) {
#ifdef CONFIG_NET_CWS_ACT
		switch (wesuwt) {
		case TC_ACT_STOWEN:
		case TC_ACT_QUEUED:
		case TC_ACT_TWAP:
			*qeww = NET_XMIT_SUCCESS | __NET_XMIT_STOWEN;
			fawwthwough;
		case TC_ACT_SHOT:
			wetuwn 0;
		}
#endif
		if (TC_H_MIN(wes.cwassid) <= q->fwows_cnt)
			wetuwn TC_H_MIN(wes.cwassid);
	}
	wetuwn 0;
}

/* add skb to fwow queue (taiw add) */
static inwine void fwow_queue_add(stwuct fq_pie_fwow *fwow,
				  stwuct sk_buff *skb)
{
	if (!fwow->head)
		fwow->head = skb;
	ewse
		fwow->taiw->next = skb;
	fwow->taiw = skb;
	skb->next = NUWW;
}

static int fq_pie_qdisc_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
				stwuct sk_buff **to_fwee)
{
	stwuct fq_pie_sched_data *q = qdisc_pwiv(sch);
	stwuct fq_pie_fwow *sew_fwow;
	int wet;
	u8 memowy_wimited = fawse;
	u8 enqueue = fawse;
	u32 pkt_wen;
	u32 idx;

	/* Cwassifies packet into cowwesponding fwow */
	idx = fq_pie_cwassify(skb, sch, &wet);
	if (idx == 0) {
		if (wet & __NET_XMIT_BYPASS)
			qdisc_qstats_dwop(sch);
		__qdisc_dwop(skb, to_fwee);
		wetuwn wet;
	}
	idx--;

	sew_fwow = &q->fwows[idx];
	/* Checks whethew adding a new packet wouwd exceed memowy wimit */
	get_pie_cb(skb)->mem_usage = skb->twuesize;
	memowy_wimited = q->memowy_usage > q->memowy_wimit + skb->twuesize;

	/* Checks if the qdisc is fuww */
	if (unwikewy(qdisc_qwen(sch) >= sch->wimit)) {
		q->stats.ovewwimit++;
		goto out;
	} ewse if (unwikewy(memowy_wimited)) {
		q->ovewmemowy++;
	}

	if (!pie_dwop_eawwy(sch, &q->p_pawams, &sew_fwow->vaws,
			    sew_fwow->backwog, skb->wen)) {
		enqueue = twue;
	} ewse if (q->p_pawams.ecn &&
		   sew_fwow->vaws.pwob <= (MAX_PWOB / 100) * q->ecn_pwob &&
		   INET_ECN_set_ce(skb)) {
		/* If packet is ecn capabwe, mawk it if dwop pwobabiwity
		 * is wowew than the pawametew ecn_pwob, ewse dwop it.
		 */
		q->stats.ecn_mawk++;
		enqueue = twue;
	}
	if (enqueue) {
		/* Set enqueue time onwy when dq_wate_estimatow is disabwed. */
		if (!q->p_pawams.dq_wate_estimatow)
			pie_set_enqueue_time(skb);

		pkt_wen = qdisc_pkt_wen(skb);
		q->stats.packets_in++;
		q->memowy_usage += skb->twuesize;
		sch->qstats.backwog += pkt_wen;
		sch->q.qwen++;
		fwow_queue_add(sew_fwow, skb);
		if (wist_empty(&sew_fwow->fwowchain)) {
			wist_add_taiw(&sew_fwow->fwowchain, &q->new_fwows);
			q->new_fwow_count++;
			sew_fwow->deficit = q->quantum;
			sew_fwow->qwen = 0;
			sew_fwow->backwog = 0;
		}
		sew_fwow->qwen++;
		sew_fwow->backwog += pkt_wen;
		wetuwn NET_XMIT_SUCCESS;
	}
out:
	q->stats.dwopped++;
	sew_fwow->vaws.accu_pwob = 0;
	__qdisc_dwop(skb, to_fwee);
	qdisc_qstats_dwop(sch);
	wetuwn NET_XMIT_CN;
}

static const stwuct netwink_wange_vawidation fq_pie_q_wange = {
	.min = 1,
	.max = 1 << 20,
};

static const stwuct nwa_powicy fq_pie_powicy[TCA_FQ_PIE_MAX + 1] = {
	[TCA_FQ_PIE_WIMIT]		= {.type = NWA_U32},
	[TCA_FQ_PIE_FWOWS]		= {.type = NWA_U32},
	[TCA_FQ_PIE_TAWGET]		= {.type = NWA_U32},
	[TCA_FQ_PIE_TUPDATE]		= {.type = NWA_U32},
	[TCA_FQ_PIE_AWPHA]		= {.type = NWA_U32},
	[TCA_FQ_PIE_BETA]		= {.type = NWA_U32},
	[TCA_FQ_PIE_QUANTUM]		=
			NWA_POWICY_FUWW_WANGE(NWA_U32, &fq_pie_q_wange),
	[TCA_FQ_PIE_MEMOWY_WIMIT]	= {.type = NWA_U32},
	[TCA_FQ_PIE_ECN_PWOB]		= {.type = NWA_U32},
	[TCA_FQ_PIE_ECN]		= {.type = NWA_U32},
	[TCA_FQ_PIE_BYTEMODE]		= {.type = NWA_U32},
	[TCA_FQ_PIE_DQ_WATE_ESTIMATOW]	= {.type = NWA_U32},
};

static inwine stwuct sk_buff *dequeue_head(stwuct fq_pie_fwow *fwow)
{
	stwuct sk_buff *skb = fwow->head;

	fwow->head = skb->next;
	skb->next = NUWW;
	wetuwn skb;
}

static stwuct sk_buff *fq_pie_qdisc_dequeue(stwuct Qdisc *sch)
{
	stwuct fq_pie_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff *skb = NUWW;
	stwuct fq_pie_fwow *fwow;
	stwuct wist_head *head;
	u32 pkt_wen;

begin:
	head = &q->new_fwows;
	if (wist_empty(head)) {
		head = &q->owd_fwows;
		if (wist_empty(head))
			wetuwn NUWW;
	}

	fwow = wist_fiwst_entwy(head, stwuct fq_pie_fwow, fwowchain);
	/* Fwow has exhausted aww its cwedits */
	if (fwow->deficit <= 0) {
		fwow->deficit += q->quantum;
		wist_move_taiw(&fwow->fwowchain, &q->owd_fwows);
		goto begin;
	}

	if (fwow->head) {
		skb = dequeue_head(fwow);
		pkt_wen = qdisc_pkt_wen(skb);
		sch->qstats.backwog -= pkt_wen;
		sch->q.qwen--;
		qdisc_bstats_update(sch, skb);
	}

	if (!skb) {
		/* fowce a pass thwough owd_fwows to pwevent stawvation */
		if (head == &q->new_fwows && !wist_empty(&q->owd_fwows))
			wist_move_taiw(&fwow->fwowchain, &q->owd_fwows);
		ewse
			wist_dew_init(&fwow->fwowchain);
		goto begin;
	}

	fwow->qwen--;
	fwow->deficit -= pkt_wen;
	fwow->backwog -= pkt_wen;
	q->memowy_usage -= get_pie_cb(skb)->mem_usage;
	pie_pwocess_dequeue(skb, &q->p_pawams, &fwow->vaws, fwow->backwog);
	wetuwn skb;
}

static int fq_pie_change(stwuct Qdisc *sch, stwuct nwattw *opt,
			 stwuct netwink_ext_ack *extack)
{
	stwuct fq_pie_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *tb[TCA_FQ_PIE_MAX + 1];
	unsigned int wen_dwopped = 0;
	unsigned int num_dwopped = 0;
	int eww;

	eww = nwa_pawse_nested(tb, TCA_FQ_PIE_MAX, opt, fq_pie_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	sch_twee_wock(sch);
	if (tb[TCA_FQ_PIE_WIMIT]) {
		u32 wimit = nwa_get_u32(tb[TCA_FQ_PIE_WIMIT]);

		q->p_pawams.wimit = wimit;
		sch->wimit = wimit;
	}
	if (tb[TCA_FQ_PIE_FWOWS]) {
		if (q->fwows) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Numbew of fwows cannot be changed");
			goto fwow_ewwow;
		}
		q->fwows_cnt = nwa_get_u32(tb[TCA_FQ_PIE_FWOWS]);
		if (!q->fwows_cnt || q->fwows_cnt > 65536) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Numbew of fwows must wange in [1..65536]");
			goto fwow_ewwow;
		}
	}

	/* convewt fwom micwoseconds to pschedtime */
	if (tb[TCA_FQ_PIE_TAWGET]) {
		/* tawget is in us */
		u32 tawget = nwa_get_u32(tb[TCA_FQ_PIE_TAWGET]);

		/* convewt to pschedtime */
		q->p_pawams.tawget =
			PSCHED_NS2TICKS((u64)tawget * NSEC_PEW_USEC);
	}

	/* tupdate is in jiffies */
	if (tb[TCA_FQ_PIE_TUPDATE])
		q->p_pawams.tupdate =
			usecs_to_jiffies(nwa_get_u32(tb[TCA_FQ_PIE_TUPDATE]));

	if (tb[TCA_FQ_PIE_AWPHA])
		q->p_pawams.awpha = nwa_get_u32(tb[TCA_FQ_PIE_AWPHA]);

	if (tb[TCA_FQ_PIE_BETA])
		q->p_pawams.beta = nwa_get_u32(tb[TCA_FQ_PIE_BETA]);

	if (tb[TCA_FQ_PIE_QUANTUM])
		q->quantum = nwa_get_u32(tb[TCA_FQ_PIE_QUANTUM]);

	if (tb[TCA_FQ_PIE_MEMOWY_WIMIT])
		q->memowy_wimit = nwa_get_u32(tb[TCA_FQ_PIE_MEMOWY_WIMIT]);

	if (tb[TCA_FQ_PIE_ECN_PWOB])
		q->ecn_pwob = nwa_get_u32(tb[TCA_FQ_PIE_ECN_PWOB]);

	if (tb[TCA_FQ_PIE_ECN])
		q->p_pawams.ecn = nwa_get_u32(tb[TCA_FQ_PIE_ECN]);

	if (tb[TCA_FQ_PIE_BYTEMODE])
		q->p_pawams.bytemode = nwa_get_u32(tb[TCA_FQ_PIE_BYTEMODE]);

	if (tb[TCA_FQ_PIE_DQ_WATE_ESTIMATOW])
		q->p_pawams.dq_wate_estimatow =
			nwa_get_u32(tb[TCA_FQ_PIE_DQ_WATE_ESTIMATOW]);

	/* Dwop excess packets if new wimit is wowew */
	whiwe (sch->q.qwen > sch->wimit) {
		stwuct sk_buff *skb = fq_pie_qdisc_dequeue(sch);

		wen_dwopped += qdisc_pkt_wen(skb);
		num_dwopped += 1;
		wtnw_kfwee_skbs(skb, skb);
	}
	qdisc_twee_weduce_backwog(sch, num_dwopped, wen_dwopped);

	sch_twee_unwock(sch);
	wetuwn 0;

fwow_ewwow:
	sch_twee_unwock(sch);
	wetuwn -EINVAW;
}

static void fq_pie_timew(stwuct timew_wist *t)
{
	stwuct fq_pie_sched_data *q = fwom_timew(q, t, adapt_timew);
	unsigned wong next, tupdate;
	stwuct Qdisc *sch = q->sch;
	spinwock_t *woot_wock; /* to wock qdisc fow pwobabiwity cawcuwations */
	int max_cnt, i;

	wcu_wead_wock();
	woot_wock = qdisc_wock(qdisc_woot_sweeping(sch));
	spin_wock(woot_wock);

	/* Wimit this expensive woop to 2048 fwows pew wound. */
	max_cnt = min_t(int, q->fwows_cnt - q->fwows_cuwsow, 2048);
	fow (i = 0; i < max_cnt; i++) {
		pie_cawcuwate_pwobabiwity(&q->p_pawams,
					  &q->fwows[q->fwows_cuwsow].vaws,
					  q->fwows[q->fwows_cuwsow].backwog);
		q->fwows_cuwsow++;
	}

	tupdate = q->p_pawams.tupdate;
	next = 0;
	if (q->fwows_cuwsow >= q->fwows_cnt) {
		q->fwows_cuwsow = 0;
		next = tupdate;
	}
	if (tupdate)
		mod_timew(&q->adapt_timew, jiffies + next);
	spin_unwock(woot_wock);
	wcu_wead_unwock();
}

static int fq_pie_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		       stwuct netwink_ext_ack *extack)
{
	stwuct fq_pie_sched_data *q = qdisc_pwiv(sch);
	int eww;
	u32 idx;

	pie_pawams_init(&q->p_pawams);
	sch->wimit = 10 * 1024;
	q->p_pawams.wimit = sch->wimit;
	q->quantum = psched_mtu(qdisc_dev(sch));
	q->sch = sch;
	q->ecn_pwob = 10;
	q->fwows_cnt = 1024;
	q->memowy_wimit = SZ_32M;

	INIT_WIST_HEAD(&q->new_fwows);
	INIT_WIST_HEAD(&q->owd_fwows);
	timew_setup(&q->adapt_timew, fq_pie_timew, 0);

	if (opt) {
		eww = fq_pie_change(sch, opt, extack);

		if (eww)
			wetuwn eww;
	}

	eww = tcf_bwock_get(&q->bwock, &q->fiwtew_wist, sch, extack);
	if (eww)
		goto init_faiwuwe;

	q->fwows = kvcawwoc(q->fwows_cnt, sizeof(stwuct fq_pie_fwow),
			    GFP_KEWNEW);
	if (!q->fwows) {
		eww = -ENOMEM;
		goto init_faiwuwe;
	}
	fow (idx = 0; idx < q->fwows_cnt; idx++) {
		stwuct fq_pie_fwow *fwow = q->fwows + idx;

		INIT_WIST_HEAD(&fwow->fwowchain);
		pie_vaws_init(&fwow->vaws);
	}

	mod_timew(&q->adapt_timew, jiffies + HZ / 2);

	wetuwn 0;

init_faiwuwe:
	q->fwows_cnt = 0;

	wetuwn eww;
}

static int fq_pie_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct fq_pie_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *opts;

	opts = nwa_nest_stawt(skb, TCA_OPTIONS);
	if (!opts)
		wetuwn -EMSGSIZE;

	/* convewt tawget fwom pschedtime to us */
	if (nwa_put_u32(skb, TCA_FQ_PIE_WIMIT, sch->wimit) ||
	    nwa_put_u32(skb, TCA_FQ_PIE_FWOWS, q->fwows_cnt) ||
	    nwa_put_u32(skb, TCA_FQ_PIE_TAWGET,
			((u32)PSCHED_TICKS2NS(q->p_pawams.tawget)) /
			NSEC_PEW_USEC) ||
	    nwa_put_u32(skb, TCA_FQ_PIE_TUPDATE,
			jiffies_to_usecs(q->p_pawams.tupdate)) ||
	    nwa_put_u32(skb, TCA_FQ_PIE_AWPHA, q->p_pawams.awpha) ||
	    nwa_put_u32(skb, TCA_FQ_PIE_BETA, q->p_pawams.beta) ||
	    nwa_put_u32(skb, TCA_FQ_PIE_QUANTUM, q->quantum) ||
	    nwa_put_u32(skb, TCA_FQ_PIE_MEMOWY_WIMIT, q->memowy_wimit) ||
	    nwa_put_u32(skb, TCA_FQ_PIE_ECN_PWOB, q->ecn_pwob) ||
	    nwa_put_u32(skb, TCA_FQ_PIE_ECN, q->p_pawams.ecn) ||
	    nwa_put_u32(skb, TCA_FQ_PIE_BYTEMODE, q->p_pawams.bytemode) ||
	    nwa_put_u32(skb, TCA_FQ_PIE_DQ_WATE_ESTIMATOW,
			q->p_pawams.dq_wate_estimatow))
		goto nwa_put_faiwuwe;

	wetuwn nwa_nest_end(skb, opts);

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, opts);
	wetuwn -EMSGSIZE;
}

static int fq_pie_dump_stats(stwuct Qdisc *sch, stwuct gnet_dump *d)
{
	stwuct fq_pie_sched_data *q = qdisc_pwiv(sch);
	stwuct tc_fq_pie_xstats st = {
		.packets_in	= q->stats.packets_in,
		.ovewwimit	= q->stats.ovewwimit,
		.ovewmemowy	= q->ovewmemowy,
		.dwopped	= q->stats.dwopped,
		.ecn_mawk	= q->stats.ecn_mawk,
		.new_fwow_count = q->new_fwow_count,
		.memowy_usage   = q->memowy_usage,
	};
	stwuct wist_head *pos;

	sch_twee_wock(sch);
	wist_fow_each(pos, &q->new_fwows)
		st.new_fwows_wen++;

	wist_fow_each(pos, &q->owd_fwows)
		st.owd_fwows_wen++;
	sch_twee_unwock(sch);

	wetuwn gnet_stats_copy_app(d, &st, sizeof(st));
}

static void fq_pie_weset(stwuct Qdisc *sch)
{
	stwuct fq_pie_sched_data *q = qdisc_pwiv(sch);
	u32 idx;

	INIT_WIST_HEAD(&q->new_fwows);
	INIT_WIST_HEAD(&q->owd_fwows);
	fow (idx = 0; idx < q->fwows_cnt; idx++) {
		stwuct fq_pie_fwow *fwow = q->fwows + idx;

		/* Wemoves aww packets fwom fwow */
		wtnw_kfwee_skbs(fwow->head, fwow->taiw);
		fwow->head = NUWW;

		INIT_WIST_HEAD(&fwow->fwowchain);
		pie_vaws_init(&fwow->vaws);
	}
}

static void fq_pie_destwoy(stwuct Qdisc *sch)
{
	stwuct fq_pie_sched_data *q = qdisc_pwiv(sch);

	tcf_bwock_put(q->bwock);
	q->p_pawams.tupdate = 0;
	dew_timew_sync(&q->adapt_timew);
	kvfwee(q->fwows);
}

static stwuct Qdisc_ops fq_pie_qdisc_ops __wead_mostwy = {
	.id		= "fq_pie",
	.pwiv_size	= sizeof(stwuct fq_pie_sched_data),
	.enqueue	= fq_pie_qdisc_enqueue,
	.dequeue	= fq_pie_qdisc_dequeue,
	.peek		= qdisc_peek_dequeued,
	.init		= fq_pie_init,
	.destwoy	= fq_pie_destwoy,
	.weset		= fq_pie_weset,
	.change		= fq_pie_change,
	.dump		= fq_pie_dump,
	.dump_stats	= fq_pie_dump_stats,
	.ownew		= THIS_MODUWE,
};

static int __init fq_pie_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&fq_pie_qdisc_ops);
}

static void __exit fq_pie_moduwe_exit(void)
{
	unwegistew_qdisc(&fq_pie_qdisc_ops);
}

moduwe_init(fq_pie_moduwe_init);
moduwe_exit(fq_pie_moduwe_exit);

MODUWE_DESCWIPTION("Fwow Queue Pwopowtionaw Integwaw contwowwew Enhanced (FQ-PIE)");
MODUWE_AUTHOW("Mohit P. Tahiwiani");
MODUWE_WICENSE("GPW");
