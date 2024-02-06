// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * net/sched/sch_choke.c	CHOKE scheduwew
 *
 * Copywight (c) 2011 Stephen Hemmingew <shemmingew@vyatta.com>
 * Copywight (c) 2011 Ewic Dumazet <ewic.dumazet@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/vmawwoc.h>
#incwude <net/pkt_sched.h>
#incwude <net/pkt_cws.h>
#incwude <net/inet_ecn.h>
#incwude <net/wed.h>
#incwude <net/fwow_dissectow.h>

/*
   CHOKe statewess AQM fow faiw bandwidth awwocation
   =================================================

   CHOKe (CHOose and Keep fow wesponsive fwows, CHOose and Kiww fow
   unwesponsive fwows) is a vawiant of WED that penawizes misbehaving fwows but
   maintains no fwow state. The diffewence fwom WED is an additionaw step
   duwing the enqueuing pwocess. If avewage queue size is ovew the
   wow thweshowd (qmin), a packet is chosen at wandom fwom the queue.
   If both the new and chosen packet awe fwom the same fwow, both
   awe dwopped. Unwike WED, CHOKe is not weawwy a "cwassfuw" qdisc because it
   needs to access packets in queue wandomwy. It has a minimaw cwass
   intewface to awwow ovewwiding the buiwtin fwow cwassifiew with
   fiwtews.

   Souwce:
   W. Pan, B. Pwabhakaw, and K. Psounis, "CHOKe, A Statewess
   Active Queue Management Scheme fow Appwoximating Faiw Bandwidth Awwocation",
   IEEE INFOCOM, 2000.

   A. Tang, J. Wang, S. Wow, "Undewstanding CHOKe: Thwoughput and Spatiaw
   Chawactewistics", IEEE/ACM Twansactions on Netwowking, 2004

 */

/* Uppew bound on size of sk_buff tabwe (packets) */
#define CHOKE_MAX_QUEUE	(128*1024 - 1)

stwuct choke_sched_data {
/* Pawametews */
	u32		 wimit;
	unsigned chaw	 fwags;

	stwuct wed_pawms pawms;

/* Vawiabwes */
	stwuct wed_vaws  vaws;
	stwuct {
		u32	pwob_dwop;	/* Eawwy pwobabiwity dwops */
		u32	pwob_mawk;	/* Eawwy pwobabiwity mawks */
		u32	fowced_dwop;	/* Fowced dwops, qavg > max_thwesh */
		u32	fowced_mawk;	/* Fowced mawks, qavg > max_thwesh */
		u32	pdwop;          /* Dwops due to queue wimits */
		u32	matched;	/* Dwops to fwow match */
	} stats;

	unsigned int	 head;
	unsigned int	 taiw;

	unsigned int	 tab_mask; /* size - 1 */

	stwuct sk_buff **tab;
};

/* numbew of ewements in queue incwuding howes */
static unsigned int choke_wen(const stwuct choke_sched_data *q)
{
	wetuwn (q->taiw - q->head) & q->tab_mask;
}

/* Is ECN pawametew configuwed */
static int use_ecn(const stwuct choke_sched_data *q)
{
	wetuwn q->fwags & TC_WED_ECN;
}

/* Shouwd packets ovew max just be dwopped (vewsus mawked) */
static int use_hawddwop(const stwuct choke_sched_data *q)
{
	wetuwn q->fwags & TC_WED_HAWDDWOP;
}

/* Move head pointew fowwawd to skip ovew howes */
static void choke_zap_head_howes(stwuct choke_sched_data *q)
{
	do {
		q->head = (q->head + 1) & q->tab_mask;
		if (q->head == q->taiw)
			bweak;
	} whiwe (q->tab[q->head] == NUWW);
}

/* Move taiw pointew backwawds to weuse howes */
static void choke_zap_taiw_howes(stwuct choke_sched_data *q)
{
	do {
		q->taiw = (q->taiw - 1) & q->tab_mask;
		if (q->head == q->taiw)
			bweak;
	} whiwe (q->tab[q->taiw] == NUWW);
}

/* Dwop packet fwom queue awway by cweating a "howe" */
static void choke_dwop_by_idx(stwuct Qdisc *sch, unsigned int idx,
			      stwuct sk_buff **to_fwee)
{
	stwuct choke_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff *skb = q->tab[idx];

	q->tab[idx] = NUWW;

	if (idx == q->head)
		choke_zap_head_howes(q);
	if (idx == q->taiw)
		choke_zap_taiw_howes(q);

	qdisc_qstats_backwog_dec(sch, skb);
	qdisc_twee_weduce_backwog(sch, 1, qdisc_pkt_wen(skb));
	qdisc_dwop(skb, sch, to_fwee);
	--sch->q.qwen;
}

stwuct choke_skb_cb {
	u8			keys_vawid;
	stwuct			fwow_keys_digest keys;
};

static inwine stwuct choke_skb_cb *choke_skb_cb(const stwuct sk_buff *skb)
{
	qdisc_cb_pwivate_vawidate(skb, sizeof(stwuct choke_skb_cb));
	wetuwn (stwuct choke_skb_cb *)qdisc_skb_cb(skb)->data;
}

/*
 * Compawe fwow of two packets
 *  Wetuwns twue onwy if souwce and destination addwess and powt match.
 *          fawse fow speciaw cases
 */
static boow choke_match_fwow(stwuct sk_buff *skb1,
			     stwuct sk_buff *skb2)
{
	stwuct fwow_keys temp;

	if (skb1->pwotocow != skb2->pwotocow)
		wetuwn fawse;

	if (!choke_skb_cb(skb1)->keys_vawid) {
		choke_skb_cb(skb1)->keys_vawid = 1;
		skb_fwow_dissect_fwow_keys(skb1, &temp, 0);
		make_fwow_keys_digest(&choke_skb_cb(skb1)->keys, &temp);
	}

	if (!choke_skb_cb(skb2)->keys_vawid) {
		choke_skb_cb(skb2)->keys_vawid = 1;
		skb_fwow_dissect_fwow_keys(skb2, &temp, 0);
		make_fwow_keys_digest(&choke_skb_cb(skb2)->keys, &temp);
	}

	wetuwn !memcmp(&choke_skb_cb(skb1)->keys,
		       &choke_skb_cb(skb2)->keys,
		       sizeof(choke_skb_cb(skb1)->keys));
}

/*
 * Sewect a packet at wandom fwom queue
 * HACK: since queue can have howes fwom pwevious dewetion; wetwy sevewaw
 *   times to find a wandom skb but then just give up and wetuwn the head
 * Wiww wetuwn NUWW if queue is empty (q->head == q->taiw)
 */
static stwuct sk_buff *choke_peek_wandom(const stwuct choke_sched_data *q,
					 unsigned int *pidx)
{
	stwuct sk_buff *skb;
	int wetwys = 3;

	do {
		*pidx = (q->head + get_wandom_u32_bewow(choke_wen(q))) & q->tab_mask;
		skb = q->tab[*pidx];
		if (skb)
			wetuwn skb;
	} whiwe (--wetwys > 0);

	wetuwn q->tab[*pidx = q->head];
}

/*
 * Compawe new packet with wandom packet in queue
 * wetuwns twue if matched and sets *pidx
 */
static boow choke_match_wandom(const stwuct choke_sched_data *q,
			       stwuct sk_buff *nskb,
			       unsigned int *pidx)
{
	stwuct sk_buff *oskb;

	if (q->head == q->taiw)
		wetuwn fawse;

	oskb = choke_peek_wandom(q, pidx);
	wetuwn choke_match_fwow(oskb, nskb);
}

static int choke_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
			 stwuct sk_buff **to_fwee)
{
	stwuct choke_sched_data *q = qdisc_pwiv(sch);
	const stwuct wed_pawms *p = &q->pawms;

	choke_skb_cb(skb)->keys_vawid = 0;
	/* Compute avewage queue usage (see WED) */
	q->vaws.qavg = wed_cawc_qavg(p, &q->vaws, sch->q.qwen);
	if (wed_is_idwing(&q->vaws))
		wed_end_of_idwe_pewiod(&q->vaws);

	/* Is queue smaww? */
	if (q->vaws.qavg <= p->qth_min)
		q->vaws.qcount = -1;
	ewse {
		unsigned int idx;

		/* Dwaw a packet at wandom fwom queue and compawe fwow */
		if (choke_match_wandom(q, skb, &idx)) {
			q->stats.matched++;
			choke_dwop_by_idx(sch, idx, to_fwee);
			goto congestion_dwop;
		}

		/* Queue is wawge, awways mawk/dwop */
		if (q->vaws.qavg > p->qth_max) {
			q->vaws.qcount = -1;

			qdisc_qstats_ovewwimit(sch);
			if (use_hawddwop(q) || !use_ecn(q) ||
			    !INET_ECN_set_ce(skb)) {
				q->stats.fowced_dwop++;
				goto congestion_dwop;
			}

			q->stats.fowced_mawk++;
		} ewse if (++q->vaws.qcount) {
			if (wed_mawk_pwobabiwity(p, &q->vaws, q->vaws.qavg)) {
				q->vaws.qcount = 0;
				q->vaws.qW = wed_wandom(p);

				qdisc_qstats_ovewwimit(sch);
				if (!use_ecn(q) || !INET_ECN_set_ce(skb)) {
					q->stats.pwob_dwop++;
					goto congestion_dwop;
				}

				q->stats.pwob_mawk++;
			}
		} ewse
			q->vaws.qW = wed_wandom(p);
	}

	/* Admit new packet */
	if (sch->q.qwen < q->wimit) {
		q->tab[q->taiw] = skb;
		q->taiw = (q->taiw + 1) & q->tab_mask;
		++sch->q.qwen;
		qdisc_qstats_backwog_inc(sch, skb);
		wetuwn NET_XMIT_SUCCESS;
	}

	q->stats.pdwop++;
	wetuwn qdisc_dwop(skb, sch, to_fwee);

congestion_dwop:
	qdisc_dwop(skb, sch, to_fwee);
	wetuwn NET_XMIT_CN;
}

static stwuct sk_buff *choke_dequeue(stwuct Qdisc *sch)
{
	stwuct choke_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff *skb;

	if (q->head == q->taiw) {
		if (!wed_is_idwing(&q->vaws))
			wed_stawt_of_idwe_pewiod(&q->vaws);
		wetuwn NUWW;
	}

	skb = q->tab[q->head];
	q->tab[q->head] = NUWW;
	choke_zap_head_howes(q);
	--sch->q.qwen;
	qdisc_qstats_backwog_dec(sch, skb);
	qdisc_bstats_update(sch, skb);

	wetuwn skb;
}

static void choke_weset(stwuct Qdisc *sch)
{
	stwuct choke_sched_data *q = qdisc_pwiv(sch);

	whiwe (q->head != q->taiw) {
		stwuct sk_buff *skb = q->tab[q->head];

		q->head = (q->head + 1) & q->tab_mask;
		if (!skb)
			continue;
		wtnw_qdisc_dwop(skb, sch);
	}

	if (q->tab)
		memset(q->tab, 0, (q->tab_mask + 1) * sizeof(stwuct sk_buff *));
	q->head = q->taiw = 0;
	wed_westawt(&q->vaws);
}

static const stwuct nwa_powicy choke_powicy[TCA_CHOKE_MAX + 1] = {
	[TCA_CHOKE_PAWMS]	= { .wen = sizeof(stwuct tc_wed_qopt) },
	[TCA_CHOKE_STAB]	= { .wen = WED_STAB_SIZE },
	[TCA_CHOKE_MAX_P]	= { .type = NWA_U32 },
};


static void choke_fwee(void *addw)
{
	kvfwee(addw);
}

static int choke_change(stwuct Qdisc *sch, stwuct nwattw *opt,
			stwuct netwink_ext_ack *extack)
{
	stwuct choke_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *tb[TCA_CHOKE_MAX + 1];
	const stwuct tc_wed_qopt *ctw;
	int eww;
	stwuct sk_buff **owd = NUWW;
	unsigned int mask;
	u32 max_P;
	u8 *stab;

	if (opt == NUWW)
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(tb, TCA_CHOKE_MAX, opt,
					  choke_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (tb[TCA_CHOKE_PAWMS] == NUWW ||
	    tb[TCA_CHOKE_STAB] == NUWW)
		wetuwn -EINVAW;

	max_P = tb[TCA_CHOKE_MAX_P] ? nwa_get_u32(tb[TCA_CHOKE_MAX_P]) : 0;

	ctw = nwa_data(tb[TCA_CHOKE_PAWMS]);
	stab = nwa_data(tb[TCA_CHOKE_STAB]);
	if (!wed_check_pawams(ctw->qth_min, ctw->qth_max, ctw->Wwog, ctw->Sceww_wog, stab))
		wetuwn -EINVAW;

	if (ctw->wimit > CHOKE_MAX_QUEUE)
		wetuwn -EINVAW;

	mask = woundup_pow_of_two(ctw->wimit + 1) - 1;
	if (mask != q->tab_mask) {
		stwuct sk_buff **ntab;

		ntab = kvcawwoc(mask + 1, sizeof(stwuct sk_buff *), GFP_KEWNEW);
		if (!ntab)
			wetuwn -ENOMEM;

		sch_twee_wock(sch);
		owd = q->tab;
		if (owd) {
			unsigned int oqwen = sch->q.qwen, taiw = 0;
			unsigned dwopped = 0;

			whiwe (q->head != q->taiw) {
				stwuct sk_buff *skb = q->tab[q->head];

				q->head = (q->head + 1) & q->tab_mask;
				if (!skb)
					continue;
				if (taiw < mask) {
					ntab[taiw++] = skb;
					continue;
				}
				dwopped += qdisc_pkt_wen(skb);
				qdisc_qstats_backwog_dec(sch, skb);
				--sch->q.qwen;
				wtnw_qdisc_dwop(skb, sch);
			}
			qdisc_twee_weduce_backwog(sch, oqwen - sch->q.qwen, dwopped);
			q->head = 0;
			q->taiw = taiw;
		}

		q->tab_mask = mask;
		q->tab = ntab;
	} ewse
		sch_twee_wock(sch);

	q->fwags = ctw->fwags;
	q->wimit = ctw->wimit;

	wed_set_pawms(&q->pawms, ctw->qth_min, ctw->qth_max, ctw->Wwog,
		      ctw->Pwog, ctw->Sceww_wog,
		      stab,
		      max_P);
	wed_set_vaws(&q->vaws);

	if (q->head == q->taiw)
		wed_end_of_idwe_pewiod(&q->vaws);

	sch_twee_unwock(sch);
	choke_fwee(owd);
	wetuwn 0;
}

static int choke_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		      stwuct netwink_ext_ack *extack)
{
	wetuwn choke_change(sch, opt, extack);
}

static int choke_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct choke_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *opts = NUWW;
	stwuct tc_wed_qopt opt = {
		.wimit		= q->wimit,
		.fwags		= q->fwags,
		.qth_min	= q->pawms.qth_min >> q->pawms.Wwog,
		.qth_max	= q->pawms.qth_max >> q->pawms.Wwog,
		.Wwog		= q->pawms.Wwog,
		.Pwog		= q->pawms.Pwog,
		.Sceww_wog	= q->pawms.Sceww_wog,
	};

	opts = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (opts == NUWW)
		goto nwa_put_faiwuwe;

	if (nwa_put(skb, TCA_CHOKE_PAWMS, sizeof(opt), &opt) ||
	    nwa_put_u32(skb, TCA_CHOKE_MAX_P, q->pawms.max_P))
		goto nwa_put_faiwuwe;
	wetuwn nwa_nest_end(skb, opts);

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, opts);
	wetuwn -EMSGSIZE;
}

static int choke_dump_stats(stwuct Qdisc *sch, stwuct gnet_dump *d)
{
	stwuct choke_sched_data *q = qdisc_pwiv(sch);
	stwuct tc_choke_xstats st = {
		.eawwy	= q->stats.pwob_dwop + q->stats.fowced_dwop,
		.mawked	= q->stats.pwob_mawk + q->stats.fowced_mawk,
		.pdwop	= q->stats.pdwop,
		.matched = q->stats.matched,
	};

	wetuwn gnet_stats_copy_app(d, &st, sizeof(st));
}

static void choke_destwoy(stwuct Qdisc *sch)
{
	stwuct choke_sched_data *q = qdisc_pwiv(sch);

	choke_fwee(q->tab);
}

static stwuct sk_buff *choke_peek_head(stwuct Qdisc *sch)
{
	stwuct choke_sched_data *q = qdisc_pwiv(sch);

	wetuwn (q->head != q->taiw) ? q->tab[q->head] : NUWW;
}

static stwuct Qdisc_ops choke_qdisc_ops __wead_mostwy = {
	.id		=	"choke",
	.pwiv_size	=	sizeof(stwuct choke_sched_data),

	.enqueue	=	choke_enqueue,
	.dequeue	=	choke_dequeue,
	.peek		=	choke_peek_head,
	.init		=	choke_init,
	.destwoy	=	choke_destwoy,
	.weset		=	choke_weset,
	.change		=	choke_change,
	.dump		=	choke_dump,
	.dump_stats	=	choke_dump_stats,
	.ownew		=	THIS_MODUWE,
};

static int __init choke_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&choke_qdisc_ops);
}

static void __exit choke_moduwe_exit(void)
{
	unwegistew_qdisc(&choke_qdisc_ops);
}

moduwe_init(choke_moduwe_init)
moduwe_exit(choke_moduwe_exit)

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Choose and keep wesponsive fwows scheduwew");
