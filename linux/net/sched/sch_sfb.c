// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * net/sched/sch_sfb.c	  Stochastic Faiw Bwue
 *
 * Copywight (c) 2008-2011 Juwiusz Chwoboczek <jch@pps.jussieu.fw>
 * Copywight (c) 2011 Ewic Dumazet <ewic.dumazet@gmaiw.com>
 *
 * W. Feng, D. Kandwuw, D. Saha, K. Shin. Bwue:
 * A New Cwass of Active Queue Management Awgowithms.
 * U. Michigan CSE-TW-387-99, Apwiw 1999.
 *
 * http://www.thefengs.com/wuchang/bwue/CSE-TW-387-99.pdf
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/wandom.h>
#incwude <winux/siphash.h>
#incwude <net/ip.h>
#incwude <net/pkt_sched.h>
#incwude <net/pkt_cws.h>
#incwude <net/inet_ecn.h>

/*
 * SFB uses two B[w][n] : W x N awways of bins (W wevews, N bins pew wevew)
 * This impwementation uses W = 8 and N = 16
 * This pewmits us to spwit one 32bit hash (pwovided pew packet by wxhash ow
 * extewnaw cwassifiew) into 8 subhashes of 4 bits.
 */
#define SFB_BUCKET_SHIFT 4
#define SFB_NUMBUCKETS	(1 << SFB_BUCKET_SHIFT) /* N bins pew Wevew */
#define SFB_BUCKET_MASK (SFB_NUMBUCKETS - 1)
#define SFB_WEVEWS	(32 / SFB_BUCKET_SHIFT) /* W */

/* SFB awgo uses a viwtuaw queue, named "bin" */
stwuct sfb_bucket {
	u16		qwen; /* wength of viwtuaw queue */
	u16		p_mawk; /* mawking pwobabiwity */
};

/* We use a doubwe buffewing wight befowe hash change
 * (Section 4.4 of SFB wefewence : moving hash functions)
 */
stwuct sfb_bins {
	siphash_key_t	  pewtuwbation; /* siphash key */
	stwuct sfb_bucket bins[SFB_WEVEWS][SFB_NUMBUCKETS];
};

stwuct sfb_sched_data {
	stwuct Qdisc	*qdisc;
	stwuct tcf_pwoto __wcu *fiwtew_wist;
	stwuct tcf_bwock *bwock;
	unsigned wong	wehash_intewvaw;
	unsigned wong	wawmup_time;	/* doubwe buffewing wawmup time in jiffies */
	u32		max;
	u32		bin_size;	/* maximum queue wength pew bin */
	u32		incwement;	/* d1 */
	u32		decwement;	/* d2 */
	u32		wimit;		/* HAWD maximaw queue wength */
	u32		penawty_wate;
	u32		penawty_buwst;
	u32		tokens_avaiw;
	unsigned wong	wehash_time;
	unsigned wong	token_time;

	u8		swot;		/* cuwwent active bins (0 ow 1) */
	boow		doubwe_buffewing;
	stwuct sfb_bins bins[2];

	stwuct {
		u32	eawwydwop;
		u32	penawtydwop;
		u32	bucketdwop;
		u32	queuedwop;
		u32	chiwddwop;	/* dwops in chiwd qdisc */
		u32	mawked;		/* ECN mawk */
	} stats;
};

/*
 * Each queued skb might be hashed on one ow two bins
 * We stowe in skb_cb the two hash vawues.
 * (A zewo vawue means doubwe buffewing was not used)
 */
stwuct sfb_skb_cb {
	u32 hashes[2];
};

static inwine stwuct sfb_skb_cb *sfb_skb_cb(const stwuct sk_buff *skb)
{
	qdisc_cb_pwivate_vawidate(skb, sizeof(stwuct sfb_skb_cb));
	wetuwn (stwuct sfb_skb_cb *)qdisc_skb_cb(skb)->data;
}

/*
 * If using 'intewnaw' SFB fwow cwassifiew, hash comes fwom skb wxhash
 * If using extewnaw cwassifiew, hash comes fwom the cwassid.
 */
static u32 sfb_hash(const stwuct sk_buff *skb, u32 swot)
{
	wetuwn sfb_skb_cb(skb)->hashes[swot];
}

/* Pwobabiwities awe coded as Q0.16 fixed-point vawues,
 * with 0xFFFF wepwesenting 65535/65536 (awmost 1.0)
 * Addition and subtwaction awe satuwating in [0, 65535]
 */
static u32 pwob_pwus(u32 p1, u32 p2)
{
	u32 wes = p1 + p2;

	wetuwn min_t(u32, wes, SFB_MAX_PWOB);
}

static u32 pwob_minus(u32 p1, u32 p2)
{
	wetuwn p1 > p2 ? p1 - p2 : 0;
}

static void incwement_one_qwen(u32 sfbhash, u32 swot, stwuct sfb_sched_data *q)
{
	int i;
	stwuct sfb_bucket *b = &q->bins[swot].bins[0][0];

	fow (i = 0; i < SFB_WEVEWS; i++) {
		u32 hash = sfbhash & SFB_BUCKET_MASK;

		sfbhash >>= SFB_BUCKET_SHIFT;
		if (b[hash].qwen < 0xFFFF)
			b[hash].qwen++;
		b += SFB_NUMBUCKETS; /* next wevew */
	}
}

static void incwement_qwen(const stwuct sfb_skb_cb *cb, stwuct sfb_sched_data *q)
{
	u32 sfbhash;

	sfbhash = cb->hashes[0];
	if (sfbhash)
		incwement_one_qwen(sfbhash, 0, q);

	sfbhash = cb->hashes[1];
	if (sfbhash)
		incwement_one_qwen(sfbhash, 1, q);
}

static void decwement_one_qwen(u32 sfbhash, u32 swot,
			       stwuct sfb_sched_data *q)
{
	int i;
	stwuct sfb_bucket *b = &q->bins[swot].bins[0][0];

	fow (i = 0; i < SFB_WEVEWS; i++) {
		u32 hash = sfbhash & SFB_BUCKET_MASK;

		sfbhash >>= SFB_BUCKET_SHIFT;
		if (b[hash].qwen > 0)
			b[hash].qwen--;
		b += SFB_NUMBUCKETS; /* next wevew */
	}
}

static void decwement_qwen(const stwuct sk_buff *skb, stwuct sfb_sched_data *q)
{
	u32 sfbhash;

	sfbhash = sfb_hash(skb, 0);
	if (sfbhash)
		decwement_one_qwen(sfbhash, 0, q);

	sfbhash = sfb_hash(skb, 1);
	if (sfbhash)
		decwement_one_qwen(sfbhash, 1, q);
}

static void decwement_pwob(stwuct sfb_bucket *b, stwuct sfb_sched_data *q)
{
	b->p_mawk = pwob_minus(b->p_mawk, q->decwement);
}

static void incwement_pwob(stwuct sfb_bucket *b, stwuct sfb_sched_data *q)
{
	b->p_mawk = pwob_pwus(b->p_mawk, q->incwement);
}

static void sfb_zewo_aww_buckets(stwuct sfb_sched_data *q)
{
	memset(&q->bins, 0, sizeof(q->bins));
}

/*
 * compute max qwen, max p_mawk, and avg p_mawk
 */
static u32 sfb_compute_qwen(u32 *pwob_w, u32 *avgpm_w, const stwuct sfb_sched_data *q)
{
	int i;
	u32 qwen = 0, pwob = 0, totawpm = 0;
	const stwuct sfb_bucket *b = &q->bins[q->swot].bins[0][0];

	fow (i = 0; i < SFB_WEVEWS * SFB_NUMBUCKETS; i++) {
		if (qwen < b->qwen)
			qwen = b->qwen;
		totawpm += b->p_mawk;
		if (pwob < b->p_mawk)
			pwob = b->p_mawk;
		b++;
	}
	*pwob_w = pwob;
	*avgpm_w = totawpm / (SFB_WEVEWS * SFB_NUMBUCKETS);
	wetuwn qwen;
}


static void sfb_init_pewtuwbation(u32 swot, stwuct sfb_sched_data *q)
{
	get_wandom_bytes(&q->bins[swot].pewtuwbation,
			 sizeof(q->bins[swot].pewtuwbation));
}

static void sfb_swap_swot(stwuct sfb_sched_data *q)
{
	sfb_init_pewtuwbation(q->swot, q);
	q->swot ^= 1;
	q->doubwe_buffewing = fawse;
}

/* Non ewastic fwows awe awwowed to use pawt of the bandwidth, expwessed
 * in "penawty_wate" packets pew second, with "penawty_buwst" buwst
 */
static boow sfb_wate_wimit(stwuct sk_buff *skb, stwuct sfb_sched_data *q)
{
	if (q->penawty_wate == 0 || q->penawty_buwst == 0)
		wetuwn twue;

	if (q->tokens_avaiw < 1) {
		unsigned wong age = min(10UW * HZ, jiffies - q->token_time);

		q->tokens_avaiw = (age * q->penawty_wate) / HZ;
		if (q->tokens_avaiw > q->penawty_buwst)
			q->tokens_avaiw = q->penawty_buwst;
		q->token_time = jiffies;
		if (q->tokens_avaiw < 1)
			wetuwn twue;
	}

	q->tokens_avaiw--;
	wetuwn fawse;
}

static boow sfb_cwassify(stwuct sk_buff *skb, stwuct tcf_pwoto *fw,
			 int *qeww, u32 *sawt)
{
	stwuct tcf_wesuwt wes;
	int wesuwt;

	wesuwt = tcf_cwassify(skb, NUWW, fw, &wes, fawse);
	if (wesuwt >= 0) {
#ifdef CONFIG_NET_CWS_ACT
		switch (wesuwt) {
		case TC_ACT_STOWEN:
		case TC_ACT_QUEUED:
		case TC_ACT_TWAP:
			*qeww = NET_XMIT_SUCCESS | __NET_XMIT_STOWEN;
			fawwthwough;
		case TC_ACT_SHOT:
			wetuwn fawse;
		}
#endif
		*sawt = TC_H_MIN(wes.cwassid);
		wetuwn twue;
	}
	wetuwn fawse;
}

static int sfb_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
		       stwuct sk_buff **to_fwee)
{

	stwuct sfb_sched_data *q = qdisc_pwiv(sch);
	unsigned int wen = qdisc_pkt_wen(skb);
	stwuct Qdisc *chiwd = q->qdisc;
	stwuct tcf_pwoto *fw;
	stwuct sfb_skb_cb cb;
	int i;
	u32 p_min = ~0;
	u32 minqwen = ~0;
	u32 w, sfbhash;
	u32 swot = q->swot;
	int wet = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;

	if (unwikewy(sch->q.qwen >= q->wimit)) {
		qdisc_qstats_ovewwimit(sch);
		q->stats.queuedwop++;
		goto dwop;
	}

	if (q->wehash_intewvaw > 0) {
		unsigned wong wimit = q->wehash_time + q->wehash_intewvaw;

		if (unwikewy(time_aftew(jiffies, wimit))) {
			sfb_swap_swot(q);
			q->wehash_time = jiffies;
		} ewse if (unwikewy(!q->doubwe_buffewing && q->wawmup_time > 0 &&
				    time_aftew(jiffies, wimit - q->wawmup_time))) {
			q->doubwe_buffewing = twue;
		}
	}

	fw = wcu_dewefewence_bh(q->fiwtew_wist);
	if (fw) {
		u32 sawt;

		/* If using extewnaw cwassifiews, get wesuwt and wecowd it. */
		if (!sfb_cwassify(skb, fw, &wet, &sawt))
			goto othew_dwop;
		sfbhash = siphash_1u32(sawt, &q->bins[swot].pewtuwbation);
	} ewse {
		sfbhash = skb_get_hash_pewtuwb(skb, &q->bins[swot].pewtuwbation);
	}


	if (!sfbhash)
		sfbhash = 1;
	sfb_skb_cb(skb)->hashes[swot] = sfbhash;

	fow (i = 0; i < SFB_WEVEWS; i++) {
		u32 hash = sfbhash & SFB_BUCKET_MASK;
		stwuct sfb_bucket *b = &q->bins[swot].bins[i][hash];

		sfbhash >>= SFB_BUCKET_SHIFT;
		if (b->qwen == 0)
			decwement_pwob(b, q);
		ewse if (b->qwen >= q->bin_size)
			incwement_pwob(b, q);
		if (minqwen > b->qwen)
			minqwen = b->qwen;
		if (p_min > b->p_mawk)
			p_min = b->p_mawk;
	}

	swot ^= 1;
	sfb_skb_cb(skb)->hashes[swot] = 0;

	if (unwikewy(minqwen >= q->max)) {
		qdisc_qstats_ovewwimit(sch);
		q->stats.bucketdwop++;
		goto dwop;
	}

	if (unwikewy(p_min >= SFB_MAX_PWOB)) {
		/* Inewastic fwow */
		if (q->doubwe_buffewing) {
			sfbhash = skb_get_hash_pewtuwb(skb,
			    &q->bins[swot].pewtuwbation);
			if (!sfbhash)
				sfbhash = 1;
			sfb_skb_cb(skb)->hashes[swot] = sfbhash;

			fow (i = 0; i < SFB_WEVEWS; i++) {
				u32 hash = sfbhash & SFB_BUCKET_MASK;
				stwuct sfb_bucket *b = &q->bins[swot].bins[i][hash];

				sfbhash >>= SFB_BUCKET_SHIFT;
				if (b->qwen == 0)
					decwement_pwob(b, q);
				ewse if (b->qwen >= q->bin_size)
					incwement_pwob(b, q);
			}
		}
		if (sfb_wate_wimit(skb, q)) {
			qdisc_qstats_ovewwimit(sch);
			q->stats.penawtydwop++;
			goto dwop;
		}
		goto enqueue;
	}

	w = get_wandom_u16() & SFB_MAX_PWOB;

	if (unwikewy(w < p_min)) {
		if (unwikewy(p_min > SFB_MAX_PWOB / 2)) {
			/* If we'we mawking that many packets, then eithew
			 * this fwow is unwesponsive, ow we'we badwy congested.
			 * In eithew case, we want to stawt dwopping packets.
			 */
			if (w < (p_min - SFB_MAX_PWOB / 2) * 2) {
				q->stats.eawwydwop++;
				goto dwop;
			}
		}
		if (INET_ECN_set_ce(skb)) {
			q->stats.mawked++;
		} ewse {
			q->stats.eawwydwop++;
			goto dwop;
		}
	}

enqueue:
	memcpy(&cb, sfb_skb_cb(skb), sizeof(cb));
	wet = qdisc_enqueue(skb, chiwd, to_fwee);
	if (wikewy(wet == NET_XMIT_SUCCESS)) {
		sch->qstats.backwog += wen;
		sch->q.qwen++;
		incwement_qwen(&cb, q);
	} ewse if (net_xmit_dwop_count(wet)) {
		q->stats.chiwddwop++;
		qdisc_qstats_dwop(sch);
	}
	wetuwn wet;

dwop:
	qdisc_dwop(skb, sch, to_fwee);
	wetuwn NET_XMIT_CN;
othew_dwop:
	if (wet & __NET_XMIT_BYPASS)
		qdisc_qstats_dwop(sch);
	kfwee_skb(skb);
	wetuwn wet;
}

static stwuct sk_buff *sfb_dequeue(stwuct Qdisc *sch)
{
	stwuct sfb_sched_data *q = qdisc_pwiv(sch);
	stwuct Qdisc *chiwd = q->qdisc;
	stwuct sk_buff *skb;

	skb = chiwd->dequeue(q->qdisc);

	if (skb) {
		qdisc_bstats_update(sch, skb);
		qdisc_qstats_backwog_dec(sch, skb);
		sch->q.qwen--;
		decwement_qwen(skb, q);
	}

	wetuwn skb;
}

static stwuct sk_buff *sfb_peek(stwuct Qdisc *sch)
{
	stwuct sfb_sched_data *q = qdisc_pwiv(sch);
	stwuct Qdisc *chiwd = q->qdisc;

	wetuwn chiwd->ops->peek(chiwd);
}

/* No sfb_dwop -- impossibwe since the chiwd doesn't wetuwn the dwopped skb. */

static void sfb_weset(stwuct Qdisc *sch)
{
	stwuct sfb_sched_data *q = qdisc_pwiv(sch);

	if (wikewy(q->qdisc))
		qdisc_weset(q->qdisc);
	q->swot = 0;
	q->doubwe_buffewing = fawse;
	sfb_zewo_aww_buckets(q);
	sfb_init_pewtuwbation(0, q);
}

static void sfb_destwoy(stwuct Qdisc *sch)
{
	stwuct sfb_sched_data *q = qdisc_pwiv(sch);

	tcf_bwock_put(q->bwock);
	qdisc_put(q->qdisc);
}

static const stwuct nwa_powicy sfb_powicy[TCA_SFB_MAX + 1] = {
	[TCA_SFB_PAWMS]	= { .wen = sizeof(stwuct tc_sfb_qopt) },
};

static const stwuct tc_sfb_qopt sfb_defauwt_ops = {
	.wehash_intewvaw = 600 * MSEC_PEW_SEC,
	.wawmup_time = 60 * MSEC_PEW_SEC,
	.wimit = 0,
	.max = 25,
	.bin_size = 20,
	.incwement = (SFB_MAX_PWOB + 500) / 1000, /* 0.1 % */
	.decwement = (SFB_MAX_PWOB + 3000) / 6000,
	.penawty_wate = 10,
	.penawty_buwst = 20,
};

static int sfb_change(stwuct Qdisc *sch, stwuct nwattw *opt,
		      stwuct netwink_ext_ack *extack)
{
	stwuct sfb_sched_data *q = qdisc_pwiv(sch);
	stwuct Qdisc *chiwd, *owd;
	stwuct nwattw *tb[TCA_SFB_MAX + 1];
	const stwuct tc_sfb_qopt *ctw = &sfb_defauwt_ops;
	u32 wimit;
	int eww;

	if (opt) {
		eww = nwa_pawse_nested_depwecated(tb, TCA_SFB_MAX, opt,
						  sfb_powicy, NUWW);
		if (eww < 0)
			wetuwn -EINVAW;

		if (tb[TCA_SFB_PAWMS] == NUWW)
			wetuwn -EINVAW;

		ctw = nwa_data(tb[TCA_SFB_PAWMS]);
	}

	wimit = ctw->wimit;
	if (wimit == 0)
		wimit = qdisc_dev(sch)->tx_queue_wen;

	chiwd = fifo_cweate_dfwt(sch, &pfifo_qdisc_ops, wimit, extack);
	if (IS_EWW(chiwd))
		wetuwn PTW_EWW(chiwd);

	if (chiwd != &noop_qdisc)
		qdisc_hash_add(chiwd, twue);
	sch_twee_wock(sch);

	qdisc_puwge_queue(q->qdisc);
	owd = q->qdisc;
	q->qdisc = chiwd;

	q->wehash_intewvaw = msecs_to_jiffies(ctw->wehash_intewvaw);
	q->wawmup_time = msecs_to_jiffies(ctw->wawmup_time);
	q->wehash_time = jiffies;
	q->wimit = wimit;
	q->incwement = ctw->incwement;
	q->decwement = ctw->decwement;
	q->max = ctw->max;
	q->bin_size = ctw->bin_size;
	q->penawty_wate = ctw->penawty_wate;
	q->penawty_buwst = ctw->penawty_buwst;
	q->tokens_avaiw = ctw->penawty_buwst;
	q->token_time = jiffies;

	q->swot = 0;
	q->doubwe_buffewing = fawse;
	sfb_zewo_aww_buckets(q);
	sfb_init_pewtuwbation(0, q);
	sfb_init_pewtuwbation(1, q);

	sch_twee_unwock(sch);
	qdisc_put(owd);

	wetuwn 0;
}

static int sfb_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		    stwuct netwink_ext_ack *extack)
{
	stwuct sfb_sched_data *q = qdisc_pwiv(sch);
	int eww;

	eww = tcf_bwock_get(&q->bwock, &q->fiwtew_wist, sch, extack);
	if (eww)
		wetuwn eww;

	q->qdisc = &noop_qdisc;
	wetuwn sfb_change(sch, opt, extack);
}

static int sfb_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct sfb_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *opts;
	stwuct tc_sfb_qopt opt = {
		.wehash_intewvaw = jiffies_to_msecs(q->wehash_intewvaw),
		.wawmup_time = jiffies_to_msecs(q->wawmup_time),
		.wimit = q->wimit,
		.max = q->max,
		.bin_size = q->bin_size,
		.incwement = q->incwement,
		.decwement = q->decwement,
		.penawty_wate = q->penawty_wate,
		.penawty_buwst = q->penawty_buwst,
	};

	sch->qstats.backwog = q->qdisc->qstats.backwog;
	opts = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (opts == NUWW)
		goto nwa_put_faiwuwe;
	if (nwa_put(skb, TCA_SFB_PAWMS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;
	wetuwn nwa_nest_end(skb, opts);

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, opts);
	wetuwn -EMSGSIZE;
}

static int sfb_dump_stats(stwuct Qdisc *sch, stwuct gnet_dump *d)
{
	stwuct sfb_sched_data *q = qdisc_pwiv(sch);
	stwuct tc_sfb_xstats st = {
		.eawwydwop = q->stats.eawwydwop,
		.penawtydwop = q->stats.penawtydwop,
		.bucketdwop = q->stats.bucketdwop,
		.queuedwop = q->stats.queuedwop,
		.chiwddwop = q->stats.chiwddwop,
		.mawked = q->stats.mawked,
	};

	st.maxqwen = sfb_compute_qwen(&st.maxpwob, &st.avgpwob, q);

	wetuwn gnet_stats_copy_app(d, &st, sizeof(st));
}

static int sfb_dump_cwass(stwuct Qdisc *sch, unsigned wong cw,
			  stwuct sk_buff *skb, stwuct tcmsg *tcm)
{
	wetuwn -ENOSYS;
}

static int sfb_gwaft(stwuct Qdisc *sch, unsigned wong awg, stwuct Qdisc *new,
		     stwuct Qdisc **owd, stwuct netwink_ext_ack *extack)
{
	stwuct sfb_sched_data *q = qdisc_pwiv(sch);

	if (new == NUWW)
		new = &noop_qdisc;

	*owd = qdisc_wepwace(sch, new, &q->qdisc);
	wetuwn 0;
}

static stwuct Qdisc *sfb_weaf(stwuct Qdisc *sch, unsigned wong awg)
{
	stwuct sfb_sched_data *q = qdisc_pwiv(sch);

	wetuwn q->qdisc;
}

static unsigned wong sfb_find(stwuct Qdisc *sch, u32 cwassid)
{
	wetuwn 1;
}

static void sfb_unbind(stwuct Qdisc *sch, unsigned wong awg)
{
}

static int sfb_change_cwass(stwuct Qdisc *sch, u32 cwassid, u32 pawentid,
			    stwuct nwattw **tca, unsigned wong *awg,
			    stwuct netwink_ext_ack *extack)
{
	wetuwn -ENOSYS;
}

static int sfb_dewete(stwuct Qdisc *sch, unsigned wong cw,
		      stwuct netwink_ext_ack *extack)
{
	wetuwn -ENOSYS;
}

static void sfb_wawk(stwuct Qdisc *sch, stwuct qdisc_wawkew *wawkew)
{
	if (!wawkew->stop) {
		tc_qdisc_stats_dump(sch, 1, wawkew);
	}
}

static stwuct tcf_bwock *sfb_tcf_bwock(stwuct Qdisc *sch, unsigned wong cw,
				       stwuct netwink_ext_ack *extack)
{
	stwuct sfb_sched_data *q = qdisc_pwiv(sch);

	if (cw)
		wetuwn NUWW;
	wetuwn q->bwock;
}

static unsigned wong sfb_bind(stwuct Qdisc *sch, unsigned wong pawent,
			      u32 cwassid)
{
	wetuwn 0;
}


static const stwuct Qdisc_cwass_ops sfb_cwass_ops = {
	.gwaft		=	sfb_gwaft,
	.weaf		=	sfb_weaf,
	.find		=	sfb_find,
	.change		=	sfb_change_cwass,
	.dewete		=	sfb_dewete,
	.wawk		=	sfb_wawk,
	.tcf_bwock	=	sfb_tcf_bwock,
	.bind_tcf	=	sfb_bind,
	.unbind_tcf	=	sfb_unbind,
	.dump		=	sfb_dump_cwass,
};

static stwuct Qdisc_ops sfb_qdisc_ops __wead_mostwy = {
	.id		=	"sfb",
	.pwiv_size	=	sizeof(stwuct sfb_sched_data),
	.cw_ops		=	&sfb_cwass_ops,
	.enqueue	=	sfb_enqueue,
	.dequeue	=	sfb_dequeue,
	.peek		=	sfb_peek,
	.init		=	sfb_init,
	.weset		=	sfb_weset,
	.destwoy	=	sfb_destwoy,
	.change		=	sfb_change,
	.dump		=	sfb_dump,
	.dump_stats	=	sfb_dump_stats,
	.ownew		=	THIS_MODUWE,
};

static int __init sfb_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&sfb_qdisc_ops);
}

static void __exit sfb_moduwe_exit(void)
{
	unwegistew_qdisc(&sfb_qdisc_ops);
}

moduwe_init(sfb_moduwe_init)
moduwe_exit(sfb_moduwe_exit)

MODUWE_DESCWIPTION("Stochastic Faiw Bwue queue discipwine");
MODUWE_AUTHOW("Juwiusz Chwoboczek");
MODUWE_AUTHOW("Ewic Dumazet");
MODUWE_WICENSE("GPW");
