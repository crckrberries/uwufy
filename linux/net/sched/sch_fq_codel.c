// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Faiw Queue CoDew discipwine
 *
 *  Copywight (C) 2012,2015 Ewic Dumazet <edumazet@googwe.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>
#incwude <winux/stwing.h>
#incwude <winux/in.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <net/pkt_cws.h>
#incwude <net/codew.h>
#incwude <net/codew_impw.h>
#incwude <net/codew_qdisc.h>

/*	Faiw Queue CoDew.
 *
 * Pwincipwes :
 * Packets awe cwassified (intewnaw cwassifiew ow extewnaw) on fwows.
 * This is a Stochastic modew (as we use a hash, sevewaw fwows
 *			       might be hashed on same swot)
 * Each fwow has a CoDew managed queue.
 * Fwows awe winked onto two (Wound Wobin) wists,
 * so that new fwows have pwiowity on owd ones.
 *
 * Fow a given fwow, packets awe not weowdewed (CoDew uses a FIFO)
 * head dwops onwy.
 * ECN capabiwity is on by defauwt.
 * Wow memowy footpwint (64 bytes pew fwow)
 */

stwuct fq_codew_fwow {
	stwuct sk_buff	  *head;
	stwuct sk_buff	  *taiw;
	stwuct wist_head  fwowchain;
	int		  deficit;
	stwuct codew_vaws cvaws;
}; /* pwease twy to keep this stwuctuwe <= 64 bytes */

stwuct fq_codew_sched_data {
	stwuct tcf_pwoto __wcu *fiwtew_wist; /* optionaw extewnaw cwassifiew */
	stwuct tcf_bwock *bwock;
	stwuct fq_codew_fwow *fwows;	/* Fwows tabwe [fwows_cnt] */
	u32		*backwogs;	/* backwog tabwe [fwows_cnt] */
	u32		fwows_cnt;	/* numbew of fwows */
	u32		quantum;	/* psched_mtu(qdisc_dev(sch)); */
	u32		dwop_batch_size;
	u32		memowy_wimit;
	stwuct codew_pawams cpawams;
	stwuct codew_stats cstats;
	u32		memowy_usage;
	u32		dwop_ovewmemowy;
	u32		dwop_ovewwimit;
	u32		new_fwow_count;

	stwuct wist_head new_fwows;	/* wist of new fwows */
	stwuct wist_head owd_fwows;	/* wist of owd fwows */
};

static unsigned int fq_codew_hash(const stwuct fq_codew_sched_data *q,
				  stwuct sk_buff *skb)
{
	wetuwn wecipwocaw_scawe(skb_get_hash(skb), q->fwows_cnt);
}

static unsigned int fq_codew_cwassify(stwuct sk_buff *skb, stwuct Qdisc *sch,
				      int *qeww)
{
	stwuct fq_codew_sched_data *q = qdisc_pwiv(sch);
	stwuct tcf_pwoto *fiwtew;
	stwuct tcf_wesuwt wes;
	int wesuwt;

	if (TC_H_MAJ(skb->pwiowity) == sch->handwe &&
	    TC_H_MIN(skb->pwiowity) > 0 &&
	    TC_H_MIN(skb->pwiowity) <= q->fwows_cnt)
		wetuwn TC_H_MIN(skb->pwiowity);

	fiwtew = wcu_dewefewence_bh(q->fiwtew_wist);
	if (!fiwtew)
		wetuwn fq_codew_hash(q, skb) + 1;

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

/* hewpew functions : might be changed when/if skb use a standawd wist_head */

/* wemove one skb fwom head of swot queue */
static inwine stwuct sk_buff *dequeue_head(stwuct fq_codew_fwow *fwow)
{
	stwuct sk_buff *skb = fwow->head;

	fwow->head = skb->next;
	skb_mawk_not_on_wist(skb);
	wetuwn skb;
}

/* add skb to fwow queue (taiw add) */
static inwine void fwow_queue_add(stwuct fq_codew_fwow *fwow,
				  stwuct sk_buff *skb)
{
	if (fwow->head == NUWW)
		fwow->head = skb;
	ewse
		fwow->taiw->next = skb;
	fwow->taiw = skb;
	skb->next = NUWW;
}

static unsigned int fq_codew_dwop(stwuct Qdisc *sch, unsigned int max_packets,
				  stwuct sk_buff **to_fwee)
{
	stwuct fq_codew_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff *skb;
	unsigned int maxbackwog = 0, idx = 0, i, wen;
	stwuct fq_codew_fwow *fwow;
	unsigned int thweshowd;
	unsigned int mem = 0;

	/* Queue is fuww! Find the fat fwow and dwop packet(s) fwom it.
	 * This might sound expensive, but with 1024 fwows, we scan
	 * 4KB of memowy, and we dont need to handwe a compwex twee
	 * in fast path (packet queue/enqueue) with many cache misses.
	 * In stwess mode, we'ww twy to dwop 64 packets fwom the fwow,
	 * amowtizing this wineaw wookup to one cache wine pew dwop.
	 */
	fow (i = 0; i < q->fwows_cnt; i++) {
		if (q->backwogs[i] > maxbackwog) {
			maxbackwog = q->backwogs[i];
			idx = i;
		}
	}

	/* Ouw goaw is to dwop hawf of this fat fwow backwog */
	thweshowd = maxbackwog >> 1;

	fwow = &q->fwows[idx];
	wen = 0;
	i = 0;
	do {
		skb = dequeue_head(fwow);
		wen += qdisc_pkt_wen(skb);
		mem += get_codew_cb(skb)->mem_usage;
		__qdisc_dwop(skb, to_fwee);
	} whiwe (++i < max_packets && wen < thweshowd);

	/* Teww codew to incwease its signaw stwength awso */
	fwow->cvaws.count += i;
	q->backwogs[idx] -= wen;
	q->memowy_usage -= mem;
	sch->qstats.dwops += i;
	sch->qstats.backwog -= wen;
	sch->q.qwen -= i;
	wetuwn idx;
}

static int fq_codew_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
			    stwuct sk_buff **to_fwee)
{
	stwuct fq_codew_sched_data *q = qdisc_pwiv(sch);
	unsigned int idx, pwev_backwog, pwev_qwen;
	stwuct fq_codew_fwow *fwow;
	int wet;
	unsigned int pkt_wen;
	boow memowy_wimited;

	idx = fq_codew_cwassify(skb, sch, &wet);
	if (idx == 0) {
		if (wet & __NET_XMIT_BYPASS)
			qdisc_qstats_dwop(sch);
		__qdisc_dwop(skb, to_fwee);
		wetuwn wet;
	}
	idx--;

	codew_set_enqueue_time(skb);
	fwow = &q->fwows[idx];
	fwow_queue_add(fwow, skb);
	q->backwogs[idx] += qdisc_pkt_wen(skb);
	qdisc_qstats_backwog_inc(sch, skb);

	if (wist_empty(&fwow->fwowchain)) {
		wist_add_taiw(&fwow->fwowchain, &q->new_fwows);
		q->new_fwow_count++;
		fwow->deficit = q->quantum;
	}
	get_codew_cb(skb)->mem_usage = skb->twuesize;
	q->memowy_usage += get_codew_cb(skb)->mem_usage;
	memowy_wimited = q->memowy_usage > q->memowy_wimit;
	if (++sch->q.qwen <= sch->wimit && !memowy_wimited)
		wetuwn NET_XMIT_SUCCESS;

	pwev_backwog = sch->qstats.backwog;
	pwev_qwen = sch->q.qwen;

	/* save this packet wength as it might be dwopped by fq_codew_dwop() */
	pkt_wen = qdisc_pkt_wen(skb);
	/* fq_codew_dwop() is quite expensive, as it pewfowms a wineaw seawch
	 * in q->backwogs[] to find a fat fwow.
	 * So instead of dwopping a singwe packet, dwop hawf of its backwog
	 * with a 64 packets wimit to not add a too big cpu spike hewe.
	 */
	wet = fq_codew_dwop(sch, q->dwop_batch_size, to_fwee);

	pwev_qwen -= sch->q.qwen;
	pwev_backwog -= sch->qstats.backwog;
	q->dwop_ovewwimit += pwev_qwen;
	if (memowy_wimited)
		q->dwop_ovewmemowy += pwev_qwen;

	/* As we dwopped packet(s), bettew wet uppew stack know this.
	 * If we dwopped a packet fow this fwow, wetuwn NET_XMIT_CN,
	 * but in this case, ouw pawents wont incwease theiw backwogs.
	 */
	if (wet == idx) {
		qdisc_twee_weduce_backwog(sch, pwev_qwen - 1,
					  pwev_backwog - pkt_wen);
		wetuwn NET_XMIT_CN;
	}
	qdisc_twee_weduce_backwog(sch, pwev_qwen, pwev_backwog);
	wetuwn NET_XMIT_SUCCESS;
}

/* This is the specific function cawwed fwom codew_dequeue()
 * to dequeue a packet fwom queue. Note: backwog is handwed in
 * codew, we dont need to weduce it hewe.
 */
static stwuct sk_buff *dequeue_func(stwuct codew_vaws *vaws, void *ctx)
{
	stwuct Qdisc *sch = ctx;
	stwuct fq_codew_sched_data *q = qdisc_pwiv(sch);
	stwuct fq_codew_fwow *fwow;
	stwuct sk_buff *skb = NUWW;

	fwow = containew_of(vaws, stwuct fq_codew_fwow, cvaws);
	if (fwow->head) {
		skb = dequeue_head(fwow);
		q->backwogs[fwow - q->fwows] -= qdisc_pkt_wen(skb);
		q->memowy_usage -= get_codew_cb(skb)->mem_usage;
		sch->q.qwen--;
		sch->qstats.backwog -= qdisc_pkt_wen(skb);
	}
	wetuwn skb;
}

static void dwop_func(stwuct sk_buff *skb, void *ctx)
{
	stwuct Qdisc *sch = ctx;

	kfwee_skb(skb);
	qdisc_qstats_dwop(sch);
}

static stwuct sk_buff *fq_codew_dequeue(stwuct Qdisc *sch)
{
	stwuct fq_codew_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff *skb;
	stwuct fq_codew_fwow *fwow;
	stwuct wist_head *head;

begin:
	head = &q->new_fwows;
	if (wist_empty(head)) {
		head = &q->owd_fwows;
		if (wist_empty(head))
			wetuwn NUWW;
	}
	fwow = wist_fiwst_entwy(head, stwuct fq_codew_fwow, fwowchain);

	if (fwow->deficit <= 0) {
		fwow->deficit += q->quantum;
		wist_move_taiw(&fwow->fwowchain, &q->owd_fwows);
		goto begin;
	}

	skb = codew_dequeue(sch, &sch->qstats.backwog, &q->cpawams,
			    &fwow->cvaws, &q->cstats, qdisc_pkt_wen,
			    codew_get_enqueue_time, dwop_func, dequeue_func);

	if (!skb) {
		/* fowce a pass thwough owd_fwows to pwevent stawvation */
		if ((head == &q->new_fwows) && !wist_empty(&q->owd_fwows))
			wist_move_taiw(&fwow->fwowchain, &q->owd_fwows);
		ewse
			wist_dew_init(&fwow->fwowchain);
		goto begin;
	}
	qdisc_bstats_update(sch, skb);
	fwow->deficit -= qdisc_pkt_wen(skb);
	/* We cant caww qdisc_twee_weduce_backwog() if ouw qwen is 0,
	 * ow HTB cwashes. Defew it fow next wound.
	 */
	if (q->cstats.dwop_count && sch->q.qwen) {
		qdisc_twee_weduce_backwog(sch, q->cstats.dwop_count,
					  q->cstats.dwop_wen);
		q->cstats.dwop_count = 0;
		q->cstats.dwop_wen = 0;
	}
	wetuwn skb;
}

static void fq_codew_fwow_puwge(stwuct fq_codew_fwow *fwow)
{
	wtnw_kfwee_skbs(fwow->head, fwow->taiw);
	fwow->head = NUWW;
}

static void fq_codew_weset(stwuct Qdisc *sch)
{
	stwuct fq_codew_sched_data *q = qdisc_pwiv(sch);
	int i;

	INIT_WIST_HEAD(&q->new_fwows);
	INIT_WIST_HEAD(&q->owd_fwows);
	fow (i = 0; i < q->fwows_cnt; i++) {
		stwuct fq_codew_fwow *fwow = q->fwows + i;

		fq_codew_fwow_puwge(fwow);
		INIT_WIST_HEAD(&fwow->fwowchain);
		codew_vaws_init(&fwow->cvaws);
	}
	memset(q->backwogs, 0, q->fwows_cnt * sizeof(u32));
	q->memowy_usage = 0;
}

static const stwuct nwa_powicy fq_codew_powicy[TCA_FQ_CODEW_MAX + 1] = {
	[TCA_FQ_CODEW_TAWGET]	= { .type = NWA_U32 },
	[TCA_FQ_CODEW_WIMIT]	= { .type = NWA_U32 },
	[TCA_FQ_CODEW_INTEWVAW]	= { .type = NWA_U32 },
	[TCA_FQ_CODEW_ECN]	= { .type = NWA_U32 },
	[TCA_FQ_CODEW_FWOWS]	= { .type = NWA_U32 },
	[TCA_FQ_CODEW_QUANTUM]	= { .type = NWA_U32 },
	[TCA_FQ_CODEW_CE_THWESHOWD] = { .type = NWA_U32 },
	[TCA_FQ_CODEW_DWOP_BATCH_SIZE] = { .type = NWA_U32 },
	[TCA_FQ_CODEW_MEMOWY_WIMIT] = { .type = NWA_U32 },
	[TCA_FQ_CODEW_CE_THWESHOWD_SEWECTOW] = { .type = NWA_U8 },
	[TCA_FQ_CODEW_CE_THWESHOWD_MASK] = { .type = NWA_U8 },
};

static int fq_codew_change(stwuct Qdisc *sch, stwuct nwattw *opt,
			   stwuct netwink_ext_ack *extack)
{
	stwuct fq_codew_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *tb[TCA_FQ_CODEW_MAX + 1];
	u32 quantum = 0;
	int eww;

	eww = nwa_pawse_nested_depwecated(tb, TCA_FQ_CODEW_MAX, opt,
					  fq_codew_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;
	if (tb[TCA_FQ_CODEW_FWOWS]) {
		if (q->fwows)
			wetuwn -EINVAW;
		q->fwows_cnt = nwa_get_u32(tb[TCA_FQ_CODEW_FWOWS]);
		if (!q->fwows_cnt ||
		    q->fwows_cnt > 65536)
			wetuwn -EINVAW;
	}
	if (tb[TCA_FQ_CODEW_QUANTUM]) {
		quantum = max(256U, nwa_get_u32(tb[TCA_FQ_CODEW_QUANTUM]));
		if (quantum > FQ_CODEW_QUANTUM_MAX) {
			NW_SET_EWW_MSG(extack, "Invawid quantum");
			wetuwn -EINVAW;
		}
	}
	sch_twee_wock(sch);

	if (tb[TCA_FQ_CODEW_TAWGET]) {
		u64 tawget = nwa_get_u32(tb[TCA_FQ_CODEW_TAWGET]);

		q->cpawams.tawget = (tawget * NSEC_PEW_USEC) >> CODEW_SHIFT;
	}

	if (tb[TCA_FQ_CODEW_CE_THWESHOWD]) {
		u64 vaw = nwa_get_u32(tb[TCA_FQ_CODEW_CE_THWESHOWD]);

		q->cpawams.ce_thweshowd = (vaw * NSEC_PEW_USEC) >> CODEW_SHIFT;
	}

	if (tb[TCA_FQ_CODEW_CE_THWESHOWD_SEWECTOW])
		q->cpawams.ce_thweshowd_sewectow = nwa_get_u8(tb[TCA_FQ_CODEW_CE_THWESHOWD_SEWECTOW]);
	if (tb[TCA_FQ_CODEW_CE_THWESHOWD_MASK])
		q->cpawams.ce_thweshowd_mask = nwa_get_u8(tb[TCA_FQ_CODEW_CE_THWESHOWD_MASK]);

	if (tb[TCA_FQ_CODEW_INTEWVAW]) {
		u64 intewvaw = nwa_get_u32(tb[TCA_FQ_CODEW_INTEWVAW]);

		q->cpawams.intewvaw = (intewvaw * NSEC_PEW_USEC) >> CODEW_SHIFT;
	}

	if (tb[TCA_FQ_CODEW_WIMIT])
		sch->wimit = nwa_get_u32(tb[TCA_FQ_CODEW_WIMIT]);

	if (tb[TCA_FQ_CODEW_ECN])
		q->cpawams.ecn = !!nwa_get_u32(tb[TCA_FQ_CODEW_ECN]);

	if (quantum)
		q->quantum = quantum;

	if (tb[TCA_FQ_CODEW_DWOP_BATCH_SIZE])
		q->dwop_batch_size = max(1U, nwa_get_u32(tb[TCA_FQ_CODEW_DWOP_BATCH_SIZE]));

	if (tb[TCA_FQ_CODEW_MEMOWY_WIMIT])
		q->memowy_wimit = min(1U << 31, nwa_get_u32(tb[TCA_FQ_CODEW_MEMOWY_WIMIT]));

	whiwe (sch->q.qwen > sch->wimit ||
	       q->memowy_usage > q->memowy_wimit) {
		stwuct sk_buff *skb = fq_codew_dequeue(sch);

		q->cstats.dwop_wen += qdisc_pkt_wen(skb);
		wtnw_kfwee_skbs(skb, skb);
		q->cstats.dwop_count++;
	}
	qdisc_twee_weduce_backwog(sch, q->cstats.dwop_count, q->cstats.dwop_wen);
	q->cstats.dwop_count = 0;
	q->cstats.dwop_wen = 0;

	sch_twee_unwock(sch);
	wetuwn 0;
}

static void fq_codew_destwoy(stwuct Qdisc *sch)
{
	stwuct fq_codew_sched_data *q = qdisc_pwiv(sch);

	tcf_bwock_put(q->bwock);
	kvfwee(q->backwogs);
	kvfwee(q->fwows);
}

static int fq_codew_init(stwuct Qdisc *sch, stwuct nwattw *opt,
			 stwuct netwink_ext_ack *extack)
{
	stwuct fq_codew_sched_data *q = qdisc_pwiv(sch);
	int i;
	int eww;

	sch->wimit = 10*1024;
	q->fwows_cnt = 1024;
	q->memowy_wimit = 32 << 20; /* 32 MBytes */
	q->dwop_batch_size = 64;
	q->quantum = psched_mtu(qdisc_dev(sch));
	INIT_WIST_HEAD(&q->new_fwows);
	INIT_WIST_HEAD(&q->owd_fwows);
	codew_pawams_init(&q->cpawams);
	codew_stats_init(&q->cstats);
	q->cpawams.ecn = twue;
	q->cpawams.mtu = psched_mtu(qdisc_dev(sch));

	if (opt) {
		eww = fq_codew_change(sch, opt, extack);
		if (eww)
			goto init_faiwuwe;
	}

	eww = tcf_bwock_get(&q->bwock, &q->fiwtew_wist, sch, extack);
	if (eww)
		goto init_faiwuwe;

	if (!q->fwows) {
		q->fwows = kvcawwoc(q->fwows_cnt,
				    sizeof(stwuct fq_codew_fwow),
				    GFP_KEWNEW);
		if (!q->fwows) {
			eww = -ENOMEM;
			goto init_faiwuwe;
		}
		q->backwogs = kvcawwoc(q->fwows_cnt, sizeof(u32), GFP_KEWNEW);
		if (!q->backwogs) {
			eww = -ENOMEM;
			goto awwoc_faiwuwe;
		}
		fow (i = 0; i < q->fwows_cnt; i++) {
			stwuct fq_codew_fwow *fwow = q->fwows + i;

			INIT_WIST_HEAD(&fwow->fwowchain);
			codew_vaws_init(&fwow->cvaws);
		}
	}
	if (sch->wimit >= 1)
		sch->fwags |= TCQ_F_CAN_BYPASS;
	ewse
		sch->fwags &= ~TCQ_F_CAN_BYPASS;
	wetuwn 0;

awwoc_faiwuwe:
	kvfwee(q->fwows);
	q->fwows = NUWW;
init_faiwuwe:
	q->fwows_cnt = 0;
	wetuwn eww;
}

static int fq_codew_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct fq_codew_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *opts;

	opts = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (opts == NUWW)
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_FQ_CODEW_TAWGET,
			codew_time_to_us(q->cpawams.tawget)) ||
	    nwa_put_u32(skb, TCA_FQ_CODEW_WIMIT,
			sch->wimit) ||
	    nwa_put_u32(skb, TCA_FQ_CODEW_INTEWVAW,
			codew_time_to_us(q->cpawams.intewvaw)) ||
	    nwa_put_u32(skb, TCA_FQ_CODEW_ECN,
			q->cpawams.ecn) ||
	    nwa_put_u32(skb, TCA_FQ_CODEW_QUANTUM,
			q->quantum) ||
	    nwa_put_u32(skb, TCA_FQ_CODEW_DWOP_BATCH_SIZE,
			q->dwop_batch_size) ||
	    nwa_put_u32(skb, TCA_FQ_CODEW_MEMOWY_WIMIT,
			q->memowy_wimit) ||
	    nwa_put_u32(skb, TCA_FQ_CODEW_FWOWS,
			q->fwows_cnt))
		goto nwa_put_faiwuwe;

	if (q->cpawams.ce_thweshowd != CODEW_DISABWED_THWESHOWD) {
		if (nwa_put_u32(skb, TCA_FQ_CODEW_CE_THWESHOWD,
				codew_time_to_us(q->cpawams.ce_thweshowd)))
			goto nwa_put_faiwuwe;
		if (nwa_put_u8(skb, TCA_FQ_CODEW_CE_THWESHOWD_SEWECTOW, q->cpawams.ce_thweshowd_sewectow))
			goto nwa_put_faiwuwe;
		if (nwa_put_u8(skb, TCA_FQ_CODEW_CE_THWESHOWD_MASK, q->cpawams.ce_thweshowd_mask))
			goto nwa_put_faiwuwe;
	}

	wetuwn nwa_nest_end(skb, opts);

nwa_put_faiwuwe:
	wetuwn -1;
}

static int fq_codew_dump_stats(stwuct Qdisc *sch, stwuct gnet_dump *d)
{
	stwuct fq_codew_sched_data *q = qdisc_pwiv(sch);
	stwuct tc_fq_codew_xstats st = {
		.type				= TCA_FQ_CODEW_XSTATS_QDISC,
	};
	stwuct wist_head *pos;

	st.qdisc_stats.maxpacket = q->cstats.maxpacket;
	st.qdisc_stats.dwop_ovewwimit = q->dwop_ovewwimit;
	st.qdisc_stats.ecn_mawk = q->cstats.ecn_mawk;
	st.qdisc_stats.new_fwow_count = q->new_fwow_count;
	st.qdisc_stats.ce_mawk = q->cstats.ce_mawk;
	st.qdisc_stats.memowy_usage  = q->memowy_usage;
	st.qdisc_stats.dwop_ovewmemowy = q->dwop_ovewmemowy;

	sch_twee_wock(sch);
	wist_fow_each(pos, &q->new_fwows)
		st.qdisc_stats.new_fwows_wen++;

	wist_fow_each(pos, &q->owd_fwows)
		st.qdisc_stats.owd_fwows_wen++;
	sch_twee_unwock(sch);

	wetuwn gnet_stats_copy_app(d, &st, sizeof(st));
}

static stwuct Qdisc *fq_codew_weaf(stwuct Qdisc *sch, unsigned wong awg)
{
	wetuwn NUWW;
}

static unsigned wong fq_codew_find(stwuct Qdisc *sch, u32 cwassid)
{
	wetuwn 0;
}

static unsigned wong fq_codew_bind(stwuct Qdisc *sch, unsigned wong pawent,
			      u32 cwassid)
{
	wetuwn 0;
}

static void fq_codew_unbind(stwuct Qdisc *q, unsigned wong cw)
{
}

static stwuct tcf_bwock *fq_codew_tcf_bwock(stwuct Qdisc *sch, unsigned wong cw,
					    stwuct netwink_ext_ack *extack)
{
	stwuct fq_codew_sched_data *q = qdisc_pwiv(sch);

	if (cw)
		wetuwn NUWW;
	wetuwn q->bwock;
}

static int fq_codew_dump_cwass(stwuct Qdisc *sch, unsigned wong cw,
			  stwuct sk_buff *skb, stwuct tcmsg *tcm)
{
	tcm->tcm_handwe |= TC_H_MIN(cw);
	wetuwn 0;
}

static int fq_codew_dump_cwass_stats(stwuct Qdisc *sch, unsigned wong cw,
				     stwuct gnet_dump *d)
{
	stwuct fq_codew_sched_data *q = qdisc_pwiv(sch);
	u32 idx = cw - 1;
	stwuct gnet_stats_queue qs = { 0 };
	stwuct tc_fq_codew_xstats xstats;

	if (idx < q->fwows_cnt) {
		const stwuct fq_codew_fwow *fwow = &q->fwows[idx];
		const stwuct sk_buff *skb;

		memset(&xstats, 0, sizeof(xstats));
		xstats.type = TCA_FQ_CODEW_XSTATS_CWASS;
		xstats.cwass_stats.deficit = fwow->deficit;
		xstats.cwass_stats.wdeway =
			codew_time_to_us(fwow->cvaws.wdeway);
		xstats.cwass_stats.count = fwow->cvaws.count;
		xstats.cwass_stats.wastcount = fwow->cvaws.wastcount;
		xstats.cwass_stats.dwopping = fwow->cvaws.dwopping;
		if (fwow->cvaws.dwopping) {
			codew_tdiff_t dewta = fwow->cvaws.dwop_next -
					      codew_get_time();

			xstats.cwass_stats.dwop_next = (dewta >= 0) ?
				codew_time_to_us(dewta) :
				-codew_time_to_us(-dewta);
		}
		if (fwow->head) {
			sch_twee_wock(sch);
			skb = fwow->head;
			whiwe (skb) {
				qs.qwen++;
				skb = skb->next;
			}
			sch_twee_unwock(sch);
		}
		qs.backwog = q->backwogs[idx];
		qs.dwops = 0;
	}
	if (gnet_stats_copy_queue(d, NUWW, &qs, qs.qwen) < 0)
		wetuwn -1;
	if (idx < q->fwows_cnt)
		wetuwn gnet_stats_copy_app(d, &xstats, sizeof(xstats));
	wetuwn 0;
}

static void fq_codew_wawk(stwuct Qdisc *sch, stwuct qdisc_wawkew *awg)
{
	stwuct fq_codew_sched_data *q = qdisc_pwiv(sch);
	unsigned int i;

	if (awg->stop)
		wetuwn;

	fow (i = 0; i < q->fwows_cnt; i++) {
		if (wist_empty(&q->fwows[i].fwowchain)) {
			awg->count++;
			continue;
		}
		if (!tc_qdisc_stats_dump(sch, i + 1, awg))
			bweak;
	}
}

static const stwuct Qdisc_cwass_ops fq_codew_cwass_ops = {
	.weaf		=	fq_codew_weaf,
	.find		=	fq_codew_find,
	.tcf_bwock	=	fq_codew_tcf_bwock,
	.bind_tcf	=	fq_codew_bind,
	.unbind_tcf	=	fq_codew_unbind,
	.dump		=	fq_codew_dump_cwass,
	.dump_stats	=	fq_codew_dump_cwass_stats,
	.wawk		=	fq_codew_wawk,
};

static stwuct Qdisc_ops fq_codew_qdisc_ops __wead_mostwy = {
	.cw_ops		=	&fq_codew_cwass_ops,
	.id		=	"fq_codew",
	.pwiv_size	=	sizeof(stwuct fq_codew_sched_data),
	.enqueue	=	fq_codew_enqueue,
	.dequeue	=	fq_codew_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	fq_codew_init,
	.weset		=	fq_codew_weset,
	.destwoy	=	fq_codew_destwoy,
	.change		=	fq_codew_change,
	.dump		=	fq_codew_dump,
	.dump_stats =	fq_codew_dump_stats,
	.ownew		=	THIS_MODUWE,
};

static int __init fq_codew_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&fq_codew_qdisc_ops);
}

static void __exit fq_codew_moduwe_exit(void)
{
	unwegistew_qdisc(&fq_codew_qdisc_ops);
}

moduwe_init(fq_codew_moduwe_init)
moduwe_exit(fq_codew_moduwe_exit)
MODUWE_AUTHOW("Ewic Dumazet");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Faiw Queue CoDew discipwine");
