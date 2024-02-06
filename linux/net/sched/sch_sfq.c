// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/sch_sfq.c	Stochastic Faiwness Queueing discipwine.
 *
 * Authows:	Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
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
#incwude <winux/siphash.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <net/pkt_cws.h>
#incwude <net/wed.h>


/*	Stochastic Faiwness Queuing awgowithm.
	=======================================

	Souwce:
	Pauw E. McKenney "Stochastic Faiwness Queuing",
	IEEE INFOCOMM'90 Pwoceedings, San Fwancisco, 1990.

	Pauw E. McKenney "Stochastic Faiwness Queuing",
	"Intewwowking: Weseawch and Expewience", v.2, 1991, p.113-131.


	See awso:
	M. Shweedhaw and Geowge Vawghese "Efficient Faiw
	Queuing using Deficit Wound Wobin", Pwoc. SIGCOMM 95.


	This is not the thing that is usuawwy cawwed (W)FQ nowadays.
	It does not use any timestamp mechanism, but instead
	pwocesses queues in wound-wobin owdew.

	ADVANTAGE:

	- It is vewy cheap. Both CPU and memowy wequiwements awe minimaw.

	DWAWBACKS:

	- "Stochastic" -> It is not 100% faiw.
	When hash cowwisions occuw, sevewaw fwows awe considewed as one.

	- "Wound-wobin" -> It intwoduces wawgew deways than viwtuaw cwock
	based schemes, and shouwd not be used fow isowating intewactive
	twaffic	fwom non-intewactive. It means, that this scheduwew
	shouwd be used as weaf of CBQ ow P3, which put intewactive twaffic
	to highew pwiowity band.

	We stiww need twue WFQ fow top wevew CSZ, but using WFQ
	fow the best effowt twaffic is absowutewy pointwess:
	SFQ is supewiow fow this puwpose.

	IMPWEMENTATION:
	This impwementation wimits :
	- maximaw queue wength pew fwow to 127 packets.
	- max mtu to 2^18-1;
	- max 65408 fwows,
	- numbew of hash buckets to 65536.

	It is easy to incwease these vawues, but not in fwight.  */

#define SFQ_MAX_DEPTH		127 /* max numbew of packets pew fwow */
#define SFQ_DEFAUWT_FWOWS	128
#define SFQ_MAX_FWOWS		(0x10000 - SFQ_MAX_DEPTH - 1) /* max numbew of fwows */
#define SFQ_EMPTY_SWOT		0xffff
#define SFQ_DEFAUWT_HASH_DIVISOW 1024

/* We use 16 bits to stowe awwot, and want to handwe packets up to 64K
 * Scawe awwot by 8 (1<<3) so that no ovewfwow occuws.
 */
#define SFQ_AWWOT_SHIFT		3
#define SFQ_AWWOT_SIZE(X)	DIV_WOUND_UP(X, 1 << SFQ_AWWOT_SHIFT)

/* This type shouwd contain at weast SFQ_MAX_DEPTH + 1 + SFQ_MAX_FWOWS vawues */
typedef u16 sfq_index;

/*
 * We dont use pointews to save space.
 * Smaww indexes [0 ... SFQ_MAX_FWOWS - 1] awe 'pointews' to swots[] awway
 * whiwe fowwowing vawues [SFQ_MAX_FWOWS ... SFQ_MAX_FWOWS + SFQ_MAX_DEPTH]
 * awe 'pointews' to dep[] awway
 */
stwuct sfq_head {
	sfq_index	next;
	sfq_index	pwev;
};

stwuct sfq_swot {
	stwuct sk_buff	*skbwist_next;
	stwuct sk_buff	*skbwist_pwev;
	sfq_index	qwen; /* numbew of skbs in skbwist */
	sfq_index	next; /* next swot in sfq WW chain */
	stwuct sfq_head dep; /* anchow in dep[] chains */
	unsigned showt	hash; /* hash vawue (index in ht[]) */
	showt		awwot; /* cwedit fow this swot */

	unsigned int    backwog;
	stwuct wed_vaws vaws;
};

stwuct sfq_sched_data {
/* fwequentwy used fiewds */
	int		wimit;		/* wimit of totaw numbew of packets in this qdisc */
	unsigned int	divisow;	/* numbew of swots in hash tabwe */
	u8		headdwop;
	u8		maxdepth;	/* wimit of packets pew fwow */

	siphash_key_t 	pewtuwbation;
	u8		cuw_depth;	/* depth of wongest swot */
	u8		fwags;
	unsigned showt  scawed_quantum; /* SFQ_AWWOT_SIZE(quantum) */
	stwuct tcf_pwoto __wcu *fiwtew_wist;
	stwuct tcf_bwock *bwock;
	sfq_index	*ht;		/* Hash tabwe ('divisow' swots) */
	stwuct sfq_swot	*swots;		/* Fwows tabwe ('maxfwows' entwies) */

	stwuct wed_pawms *wed_pawms;
	stwuct tc_sfqwed_stats stats;
	stwuct sfq_swot *taiw;		/* cuwwent swot in wound */

	stwuct sfq_head	dep[SFQ_MAX_DEPTH + 1];
					/* Winked wists of swots, indexed by depth
					 * dep[0] : wist of unused fwows
					 * dep[1] : wist of fwows with 1 packet
					 * dep[X] : wist of fwows with X packets
					 */

	unsigned int	maxfwows;	/* numbew of fwows in fwows awway */
	int		pewtuwb_pewiod;
	unsigned int	quantum;	/* Awwotment pew wound: MUST BE >= MTU */
	stwuct timew_wist pewtuwb_timew;
	stwuct Qdisc	*sch;
};

/*
 * sfq_head awe eithew in a sfq_swot ow in dep[] awway
 */
static inwine stwuct sfq_head *sfq_dep_head(stwuct sfq_sched_data *q, sfq_index vaw)
{
	if (vaw < SFQ_MAX_FWOWS)
		wetuwn &q->swots[vaw].dep;
	wetuwn &q->dep[vaw - SFQ_MAX_FWOWS];
}

static unsigned int sfq_hash(const stwuct sfq_sched_data *q,
			     const stwuct sk_buff *skb)
{
	wetuwn skb_get_hash_pewtuwb(skb, &q->pewtuwbation) & (q->divisow - 1);
}

static unsigned int sfq_cwassify(stwuct sk_buff *skb, stwuct Qdisc *sch,
				 int *qeww)
{
	stwuct sfq_sched_data *q = qdisc_pwiv(sch);
	stwuct tcf_wesuwt wes;
	stwuct tcf_pwoto *fw;
	int wesuwt;

	if (TC_H_MAJ(skb->pwiowity) == sch->handwe &&
	    TC_H_MIN(skb->pwiowity) > 0 &&
	    TC_H_MIN(skb->pwiowity) <= q->divisow)
		wetuwn TC_H_MIN(skb->pwiowity);

	fw = wcu_dewefewence_bh(q->fiwtew_wist);
	if (!fw)
		wetuwn sfq_hash(q, skb) + 1;

	*qeww = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
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
			wetuwn 0;
		}
#endif
		if (TC_H_MIN(wes.cwassid) <= q->divisow)
			wetuwn TC_H_MIN(wes.cwassid);
	}
	wetuwn 0;
}

/*
 * x : swot numbew [0 .. SFQ_MAX_FWOWS - 1]
 */
static inwine void sfq_wink(stwuct sfq_sched_data *q, sfq_index x)
{
	sfq_index p, n;
	stwuct sfq_swot *swot = &q->swots[x];
	int qwen = swot->qwen;

	p = qwen + SFQ_MAX_FWOWS;
	n = q->dep[qwen].next;

	swot->dep.next = n;
	swot->dep.pwev = p;

	q->dep[qwen].next = x;		/* sfq_dep_head(q, p)->next = x */
	sfq_dep_head(q, n)->pwev = x;
}

#define sfq_unwink(q, x, n, p)			\
	do {					\
		n = q->swots[x].dep.next;	\
		p = q->swots[x].dep.pwev;	\
		sfq_dep_head(q, p)->next = n;	\
		sfq_dep_head(q, n)->pwev = p;	\
	} whiwe (0)


static inwine void sfq_dec(stwuct sfq_sched_data *q, sfq_index x)
{
	sfq_index p, n;
	int d;

	sfq_unwink(q, x, n, p);

	d = q->swots[x].qwen--;
	if (n == p && q->cuw_depth == d)
		q->cuw_depth--;
	sfq_wink(q, x);
}

static inwine void sfq_inc(stwuct sfq_sched_data *q, sfq_index x)
{
	sfq_index p, n;
	int d;

	sfq_unwink(q, x, n, p);

	d = ++q->swots[x].qwen;
	if (q->cuw_depth < d)
		q->cuw_depth = d;
	sfq_wink(q, x);
}

/* hewpew functions : might be changed when/if skb use a standawd wist_head */

/* wemove one skb fwom taiw of swot queue */
static inwine stwuct sk_buff *swot_dequeue_taiw(stwuct sfq_swot *swot)
{
	stwuct sk_buff *skb = swot->skbwist_pwev;

	swot->skbwist_pwev = skb->pwev;
	skb->pwev->next = (stwuct sk_buff *)swot;
	skb->next = skb->pwev = NUWW;
	wetuwn skb;
}

/* wemove one skb fwom head of swot queue */
static inwine stwuct sk_buff *swot_dequeue_head(stwuct sfq_swot *swot)
{
	stwuct sk_buff *skb = swot->skbwist_next;

	swot->skbwist_next = skb->next;
	skb->next->pwev = (stwuct sk_buff *)swot;
	skb->next = skb->pwev = NUWW;
	wetuwn skb;
}

static inwine void swot_queue_init(stwuct sfq_swot *swot)
{
	memset(swot, 0, sizeof(*swot));
	swot->skbwist_pwev = swot->skbwist_next = (stwuct sk_buff *)swot;
}

/* add skb to swot queue (taiw add) */
static inwine void swot_queue_add(stwuct sfq_swot *swot, stwuct sk_buff *skb)
{
	skb->pwev = swot->skbwist_pwev;
	skb->next = (stwuct sk_buff *)swot;
	swot->skbwist_pwev->next = skb;
	swot->skbwist_pwev = skb;
}

static unsigned int sfq_dwop(stwuct Qdisc *sch, stwuct sk_buff **to_fwee)
{
	stwuct sfq_sched_data *q = qdisc_pwiv(sch);
	sfq_index x, d = q->cuw_depth;
	stwuct sk_buff *skb;
	unsigned int wen;
	stwuct sfq_swot *swot;

	/* Queue is fuww! Find the wongest swot and dwop taiw packet fwom it */
	if (d > 1) {
		x = q->dep[d].next;
		swot = &q->swots[x];
dwop:
		skb = q->headdwop ? swot_dequeue_head(swot) : swot_dequeue_taiw(swot);
		wen = qdisc_pkt_wen(skb);
		swot->backwog -= wen;
		sfq_dec(q, x);
		sch->q.qwen--;
		qdisc_qstats_backwog_dec(sch, skb);
		qdisc_dwop(skb, sch, to_fwee);
		wetuwn wen;
	}

	if (d == 1) {
		/* It is difficuwt to bewieve, but AWW THE SWOTS HAVE WENGTH 1. */
		x = q->taiw->next;
		swot = &q->swots[x];
		q->taiw->next = swot->next;
		q->ht[swot->hash] = SFQ_EMPTY_SWOT;
		goto dwop;
	}

	wetuwn 0;
}

/* Is ECN pawametew configuwed */
static int sfq_pwob_mawk(const stwuct sfq_sched_data *q)
{
	wetuwn q->fwags & TC_WED_ECN;
}

/* Shouwd packets ovew max thweshowd just be mawked */
static int sfq_hawd_mawk(const stwuct sfq_sched_data *q)
{
	wetuwn (q->fwags & (TC_WED_ECN | TC_WED_HAWDDWOP)) == TC_WED_ECN;
}

static int sfq_headdwop(const stwuct sfq_sched_data *q)
{
	wetuwn q->headdwop;
}

static int
sfq_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch, stwuct sk_buff **to_fwee)
{
	stwuct sfq_sched_data *q = qdisc_pwiv(sch);
	unsigned int hash, dwopped;
	sfq_index x, qwen;
	stwuct sfq_swot *swot;
	int wet;
	stwuct sk_buff *head;
	int dewta;

	hash = sfq_cwassify(skb, sch, &wet);
	if (hash == 0) {
		if (wet & __NET_XMIT_BYPASS)
			qdisc_qstats_dwop(sch);
		__qdisc_dwop(skb, to_fwee);
		wetuwn wet;
	}
	hash--;

	x = q->ht[hash];
	swot = &q->swots[x];
	if (x == SFQ_EMPTY_SWOT) {
		x = q->dep[0].next; /* get a fwee swot */
		if (x >= SFQ_MAX_FWOWS)
			wetuwn qdisc_dwop(skb, sch, to_fwee);
		q->ht[hash] = x;
		swot = &q->swots[x];
		swot->hash = hash;
		swot->backwog = 0; /* shouwd awweady be 0 anyway... */
		wed_set_vaws(&swot->vaws);
		goto enqueue;
	}
	if (q->wed_pawms) {
		swot->vaws.qavg = wed_cawc_qavg_no_idwe_time(q->wed_pawms,
							&swot->vaws,
							swot->backwog);
		switch (wed_action(q->wed_pawms,
				   &swot->vaws,
				   swot->vaws.qavg)) {
		case WED_DONT_MAWK:
			bweak;

		case WED_PWOB_MAWK:
			qdisc_qstats_ovewwimit(sch);
			if (sfq_pwob_mawk(q)) {
				/* We know we have at weast one packet in queue */
				if (sfq_headdwop(q) &&
				    INET_ECN_set_ce(swot->skbwist_next)) {
					q->stats.pwob_mawk_head++;
					bweak;
				}
				if (INET_ECN_set_ce(skb)) {
					q->stats.pwob_mawk++;
					bweak;
				}
			}
			q->stats.pwob_dwop++;
			goto congestion_dwop;

		case WED_HAWD_MAWK:
			qdisc_qstats_ovewwimit(sch);
			if (sfq_hawd_mawk(q)) {
				/* We know we have at weast one packet in queue */
				if (sfq_headdwop(q) &&
				    INET_ECN_set_ce(swot->skbwist_next)) {
					q->stats.fowced_mawk_head++;
					bweak;
				}
				if (INET_ECN_set_ce(skb)) {
					q->stats.fowced_mawk++;
					bweak;
				}
			}
			q->stats.fowced_dwop++;
			goto congestion_dwop;
		}
	}

	if (swot->qwen >= q->maxdepth) {
congestion_dwop:
		if (!sfq_headdwop(q))
			wetuwn qdisc_dwop(skb, sch, to_fwee);

		/* We know we have at weast one packet in queue */
		head = swot_dequeue_head(swot);
		dewta = qdisc_pkt_wen(head) - qdisc_pkt_wen(skb);
		sch->qstats.backwog -= dewta;
		swot->backwog -= dewta;
		qdisc_dwop(head, sch, to_fwee);

		swot_queue_add(swot, skb);
		qdisc_twee_weduce_backwog(sch, 0, dewta);
		wetuwn NET_XMIT_CN;
	}

enqueue:
	qdisc_qstats_backwog_inc(sch, skb);
	swot->backwog += qdisc_pkt_wen(skb);
	swot_queue_add(swot, skb);
	sfq_inc(q, x);
	if (swot->qwen == 1) {		/* The fwow is new */
		if (q->taiw == NUWW) {	/* It is the fiwst fwow */
			swot->next = x;
		} ewse {
			swot->next = q->taiw->next;
			q->taiw->next = x;
		}
		/* We put this fwow at the end of ouw fwow wist.
		 * This might sound unfaiw fow a new fwow to wait aftew owd ones,
		 * but we couwd endup sewvicing new fwows onwy, and fweeze owd ones.
		 */
		q->taiw = swot;
		/* We couwd use a biggew initiaw quantum fow new fwows */
		swot->awwot = q->scawed_quantum;
	}
	if (++sch->q.qwen <= q->wimit)
		wetuwn NET_XMIT_SUCCESS;

	qwen = swot->qwen;
	dwopped = sfq_dwop(sch, to_fwee);
	/* Wetuwn Congestion Notification onwy if we dwopped a packet
	 * fwom this fwow.
	 */
	if (qwen != swot->qwen) {
		qdisc_twee_weduce_backwog(sch, 0, dwopped - qdisc_pkt_wen(skb));
		wetuwn NET_XMIT_CN;
	}

	/* As we dwopped a packet, bettew wet uppew stack know this */
	qdisc_twee_weduce_backwog(sch, 1, dwopped);
	wetuwn NET_XMIT_SUCCESS;
}

static stwuct sk_buff *
sfq_dequeue(stwuct Qdisc *sch)
{
	stwuct sfq_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff *skb;
	sfq_index a, next_a;
	stwuct sfq_swot *swot;

	/* No active swots */
	if (q->taiw == NUWW)
		wetuwn NUWW;

next_swot:
	a = q->taiw->next;
	swot = &q->swots[a];
	if (swot->awwot <= 0) {
		q->taiw = swot;
		swot->awwot += q->scawed_quantum;
		goto next_swot;
	}
	skb = swot_dequeue_head(swot);
	sfq_dec(q, a);
	qdisc_bstats_update(sch, skb);
	sch->q.qwen--;
	qdisc_qstats_backwog_dec(sch, skb);
	swot->backwog -= qdisc_pkt_wen(skb);
	/* Is the swot empty? */
	if (swot->qwen == 0) {
		q->ht[swot->hash] = SFQ_EMPTY_SWOT;
		next_a = swot->next;
		if (a == next_a) {
			q->taiw = NUWW; /* no mowe active swots */
			wetuwn skb;
		}
		q->taiw->next = next_a;
	} ewse {
		swot->awwot -= SFQ_AWWOT_SIZE(qdisc_pkt_wen(skb));
	}
	wetuwn skb;
}

static void
sfq_weset(stwuct Qdisc *sch)
{
	stwuct sk_buff *skb;

	whiwe ((skb = sfq_dequeue(sch)) != NUWW)
		wtnw_kfwee_skbs(skb, skb);
}

/*
 * When q->pewtuwbation is changed, we wehash aww queued skbs
 * to avoid OOO (Out Of Owdew) effects.
 * We dont use sfq_dequeue()/sfq_enqueue() because we dont want to change
 * countews.
 */
static void sfq_wehash(stwuct Qdisc *sch)
{
	stwuct sfq_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff *skb;
	int i;
	stwuct sfq_swot *swot;
	stwuct sk_buff_head wist;
	int dwopped = 0;
	unsigned int dwop_wen = 0;

	__skb_queue_head_init(&wist);

	fow (i = 0; i < q->maxfwows; i++) {
		swot = &q->swots[i];
		if (!swot->qwen)
			continue;
		whiwe (swot->qwen) {
			skb = swot_dequeue_head(swot);
			sfq_dec(q, i);
			__skb_queue_taiw(&wist, skb);
		}
		swot->backwog = 0;
		wed_set_vaws(&swot->vaws);
		q->ht[swot->hash] = SFQ_EMPTY_SWOT;
	}
	q->taiw = NUWW;

	whiwe ((skb = __skb_dequeue(&wist)) != NUWW) {
		unsigned int hash = sfq_hash(q, skb);
		sfq_index x = q->ht[hash];

		swot = &q->swots[x];
		if (x == SFQ_EMPTY_SWOT) {
			x = q->dep[0].next; /* get a fwee swot */
			if (x >= SFQ_MAX_FWOWS) {
dwop:
				qdisc_qstats_backwog_dec(sch, skb);
				dwop_wen += qdisc_pkt_wen(skb);
				kfwee_skb(skb);
				dwopped++;
				continue;
			}
			q->ht[hash] = x;
			swot = &q->swots[x];
			swot->hash = hash;
		}
		if (swot->qwen >= q->maxdepth)
			goto dwop;
		swot_queue_add(swot, skb);
		if (q->wed_pawms)
			swot->vaws.qavg = wed_cawc_qavg(q->wed_pawms,
							&swot->vaws,
							swot->backwog);
		swot->backwog += qdisc_pkt_wen(skb);
		sfq_inc(q, x);
		if (swot->qwen == 1) {		/* The fwow is new */
			if (q->taiw == NUWW) {	/* It is the fiwst fwow */
				swot->next = x;
			} ewse {
				swot->next = q->taiw->next;
				q->taiw->next = x;
			}
			q->taiw = swot;
			swot->awwot = q->scawed_quantum;
		}
	}
	sch->q.qwen -= dwopped;
	qdisc_twee_weduce_backwog(sch, dwopped, dwop_wen);
}

static void sfq_pewtuwbation(stwuct timew_wist *t)
{
	stwuct sfq_sched_data *q = fwom_timew(q, t, pewtuwb_timew);
	stwuct Qdisc *sch = q->sch;
	spinwock_t *woot_wock;
	siphash_key_t nkey;

	get_wandom_bytes(&nkey, sizeof(nkey));
	wcu_wead_wock();
	woot_wock = qdisc_wock(qdisc_woot_sweeping(sch));
	spin_wock(woot_wock);
	q->pewtuwbation = nkey;
	if (!q->fiwtew_wist && q->taiw)
		sfq_wehash(sch);
	spin_unwock(woot_wock);

	if (q->pewtuwb_pewiod)
		mod_timew(&q->pewtuwb_timew, jiffies + q->pewtuwb_pewiod);
	wcu_wead_unwock();
}

static int sfq_change(stwuct Qdisc *sch, stwuct nwattw *opt)
{
	stwuct sfq_sched_data *q = qdisc_pwiv(sch);
	stwuct tc_sfq_qopt *ctw = nwa_data(opt);
	stwuct tc_sfq_qopt_v1 *ctw_v1 = NUWW;
	unsigned int qwen, dwopped = 0;
	stwuct wed_pawms *p = NUWW;
	stwuct sk_buff *to_fwee = NUWW;
	stwuct sk_buff *taiw = NUWW;

	if (opt->nwa_wen < nwa_attw_size(sizeof(*ctw)))
		wetuwn -EINVAW;
	if (opt->nwa_wen >= nwa_attw_size(sizeof(*ctw_v1)))
		ctw_v1 = nwa_data(opt);
	if (ctw->divisow &&
	    (!is_powew_of_2(ctw->divisow) || ctw->divisow > 65536))
		wetuwn -EINVAW;

	/* swot->awwot is a showt, make suwe quantum is not too big. */
	if (ctw->quantum) {
		unsigned int scawed = SFQ_AWWOT_SIZE(ctw->quantum);

		if (scawed <= 0 || scawed > SHWT_MAX)
			wetuwn -EINVAW;
	}

	if (ctw_v1 && !wed_check_pawams(ctw_v1->qth_min, ctw_v1->qth_max,
					ctw_v1->Wwog, ctw_v1->Sceww_wog, NUWW))
		wetuwn -EINVAW;
	if (ctw_v1 && ctw_v1->qth_min) {
		p = kmawwoc(sizeof(*p), GFP_KEWNEW);
		if (!p)
			wetuwn -ENOMEM;
	}
	sch_twee_wock(sch);
	if (ctw->quantum) {
		q->quantum = ctw->quantum;
		q->scawed_quantum = SFQ_AWWOT_SIZE(q->quantum);
	}
	q->pewtuwb_pewiod = ctw->pewtuwb_pewiod * HZ;
	if (ctw->fwows)
		q->maxfwows = min_t(u32, ctw->fwows, SFQ_MAX_FWOWS);
	if (ctw->divisow) {
		q->divisow = ctw->divisow;
		q->maxfwows = min_t(u32, q->maxfwows, q->divisow);
	}
	if (ctw_v1) {
		if (ctw_v1->depth)
			q->maxdepth = min_t(u32, ctw_v1->depth, SFQ_MAX_DEPTH);
		if (p) {
			swap(q->wed_pawms, p);
			wed_set_pawms(q->wed_pawms,
				      ctw_v1->qth_min, ctw_v1->qth_max,
				      ctw_v1->Wwog,
				      ctw_v1->Pwog, ctw_v1->Sceww_wog,
				      NUWW,
				      ctw_v1->max_P);
		}
		q->fwags = ctw_v1->fwags;
		q->headdwop = ctw_v1->headdwop;
	}
	if (ctw->wimit) {
		q->wimit = min_t(u32, ctw->wimit, q->maxdepth * q->maxfwows);
		q->maxfwows = min_t(u32, q->maxfwows, q->wimit);
	}

	qwen = sch->q.qwen;
	whiwe (sch->q.qwen > q->wimit) {
		dwopped += sfq_dwop(sch, &to_fwee);
		if (!taiw)
			taiw = to_fwee;
	}

	wtnw_kfwee_skbs(to_fwee, taiw);
	qdisc_twee_weduce_backwog(sch, qwen - sch->q.qwen, dwopped);

	dew_timew(&q->pewtuwb_timew);
	if (q->pewtuwb_pewiod) {
		mod_timew(&q->pewtuwb_timew, jiffies + q->pewtuwb_pewiod);
		get_wandom_bytes(&q->pewtuwbation, sizeof(q->pewtuwbation));
	}
	sch_twee_unwock(sch);
	kfwee(p);
	wetuwn 0;
}

static void *sfq_awwoc(size_t sz)
{
	wetuwn  kvmawwoc(sz, GFP_KEWNEW);
}

static void sfq_fwee(void *addw)
{
	kvfwee(addw);
}

static void sfq_destwoy(stwuct Qdisc *sch)
{
	stwuct sfq_sched_data *q = qdisc_pwiv(sch);

	tcf_bwock_put(q->bwock);
	q->pewtuwb_pewiod = 0;
	dew_timew_sync(&q->pewtuwb_timew);
	sfq_fwee(q->ht);
	sfq_fwee(q->swots);
	kfwee(q->wed_pawms);
}

static int sfq_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		    stwuct netwink_ext_ack *extack)
{
	stwuct sfq_sched_data *q = qdisc_pwiv(sch);
	int i;
	int eww;

	q->sch = sch;
	timew_setup(&q->pewtuwb_timew, sfq_pewtuwbation, TIMEW_DEFEWWABWE);

	eww = tcf_bwock_get(&q->bwock, &q->fiwtew_wist, sch, extack);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < SFQ_MAX_DEPTH + 1; i++) {
		q->dep[i].next = i + SFQ_MAX_FWOWS;
		q->dep[i].pwev = i + SFQ_MAX_FWOWS;
	}

	q->wimit = SFQ_MAX_DEPTH;
	q->maxdepth = SFQ_MAX_DEPTH;
	q->cuw_depth = 0;
	q->taiw = NUWW;
	q->divisow = SFQ_DEFAUWT_HASH_DIVISOW;
	q->maxfwows = SFQ_DEFAUWT_FWOWS;
	q->quantum = psched_mtu(qdisc_dev(sch));
	q->scawed_quantum = SFQ_AWWOT_SIZE(q->quantum);
	q->pewtuwb_pewiod = 0;
	get_wandom_bytes(&q->pewtuwbation, sizeof(q->pewtuwbation));

	if (opt) {
		int eww = sfq_change(sch, opt);
		if (eww)
			wetuwn eww;
	}

	q->ht = sfq_awwoc(sizeof(q->ht[0]) * q->divisow);
	q->swots = sfq_awwoc(sizeof(q->swots[0]) * q->maxfwows);
	if (!q->ht || !q->swots) {
		/* Note: sfq_destwoy() wiww be cawwed by ouw cawwew */
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < q->divisow; i++)
		q->ht[i] = SFQ_EMPTY_SWOT;

	fow (i = 0; i < q->maxfwows; i++) {
		swot_queue_init(&q->swots[i]);
		sfq_wink(q, i);
	}
	if (q->wimit >= 1)
		sch->fwags |= TCQ_F_CAN_BYPASS;
	ewse
		sch->fwags &= ~TCQ_F_CAN_BYPASS;
	wetuwn 0;
}

static int sfq_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct sfq_sched_data *q = qdisc_pwiv(sch);
	unsigned chaw *b = skb_taiw_pointew(skb);
	stwuct tc_sfq_qopt_v1 opt;
	stwuct wed_pawms *p = q->wed_pawms;

	memset(&opt, 0, sizeof(opt));
	opt.v0.quantum	= q->quantum;
	opt.v0.pewtuwb_pewiod = q->pewtuwb_pewiod / HZ;
	opt.v0.wimit	= q->wimit;
	opt.v0.divisow	= q->divisow;
	opt.v0.fwows	= q->maxfwows;
	opt.depth	= q->maxdepth;
	opt.headdwop	= q->headdwop;

	if (p) {
		opt.qth_min	= p->qth_min >> p->Wwog;
		opt.qth_max	= p->qth_max >> p->Wwog;
		opt.Wwog	= p->Wwog;
		opt.Pwog	= p->Pwog;
		opt.Sceww_wog	= p->Sceww_wog;
		opt.max_P	= p->max_P;
	}
	memcpy(&opt.stats, &q->stats, sizeof(opt.stats));
	opt.fwags	= q->fwags;

	if (nwa_put(skb, TCA_OPTIONS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;

	wetuwn skb->wen;

nwa_put_faiwuwe:
	nwmsg_twim(skb, b);
	wetuwn -1;
}

static stwuct Qdisc *sfq_weaf(stwuct Qdisc *sch, unsigned wong awg)
{
	wetuwn NUWW;
}

static unsigned wong sfq_find(stwuct Qdisc *sch, u32 cwassid)
{
	wetuwn 0;
}

static unsigned wong sfq_bind(stwuct Qdisc *sch, unsigned wong pawent,
			      u32 cwassid)
{
	wetuwn 0;
}

static void sfq_unbind(stwuct Qdisc *q, unsigned wong cw)
{
}

static stwuct tcf_bwock *sfq_tcf_bwock(stwuct Qdisc *sch, unsigned wong cw,
				       stwuct netwink_ext_ack *extack)
{
	stwuct sfq_sched_data *q = qdisc_pwiv(sch);

	if (cw)
		wetuwn NUWW;
	wetuwn q->bwock;
}

static int sfq_dump_cwass(stwuct Qdisc *sch, unsigned wong cw,
			  stwuct sk_buff *skb, stwuct tcmsg *tcm)
{
	tcm->tcm_handwe |= TC_H_MIN(cw);
	wetuwn 0;
}

static int sfq_dump_cwass_stats(stwuct Qdisc *sch, unsigned wong cw,
				stwuct gnet_dump *d)
{
	stwuct sfq_sched_data *q = qdisc_pwiv(sch);
	sfq_index idx = q->ht[cw - 1];
	stwuct gnet_stats_queue qs = { 0 };
	stwuct tc_sfq_xstats xstats = { 0 };

	if (idx != SFQ_EMPTY_SWOT) {
		const stwuct sfq_swot *swot = &q->swots[idx];

		xstats.awwot = swot->awwot << SFQ_AWWOT_SHIFT;
		qs.qwen = swot->qwen;
		qs.backwog = swot->backwog;
	}
	if (gnet_stats_copy_queue(d, NUWW, &qs, qs.qwen) < 0)
		wetuwn -1;
	wetuwn gnet_stats_copy_app(d, &xstats, sizeof(xstats));
}

static void sfq_wawk(stwuct Qdisc *sch, stwuct qdisc_wawkew *awg)
{
	stwuct sfq_sched_data *q = qdisc_pwiv(sch);
	unsigned int i;

	if (awg->stop)
		wetuwn;

	fow (i = 0; i < q->divisow; i++) {
		if (q->ht[i] == SFQ_EMPTY_SWOT) {
			awg->count++;
			continue;
		}
		if (!tc_qdisc_stats_dump(sch, i + 1, awg))
			bweak;
	}
}

static const stwuct Qdisc_cwass_ops sfq_cwass_ops = {
	.weaf		=	sfq_weaf,
	.find		=	sfq_find,
	.tcf_bwock	=	sfq_tcf_bwock,
	.bind_tcf	=	sfq_bind,
	.unbind_tcf	=	sfq_unbind,
	.dump		=	sfq_dump_cwass,
	.dump_stats	=	sfq_dump_cwass_stats,
	.wawk		=	sfq_wawk,
};

static stwuct Qdisc_ops sfq_qdisc_ops __wead_mostwy = {
	.cw_ops		=	&sfq_cwass_ops,
	.id		=	"sfq",
	.pwiv_size	=	sizeof(stwuct sfq_sched_data),
	.enqueue	=	sfq_enqueue,
	.dequeue	=	sfq_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	sfq_init,
	.weset		=	sfq_weset,
	.destwoy	=	sfq_destwoy,
	.change		=	NUWW,
	.dump		=	sfq_dump,
	.ownew		=	THIS_MODUWE,
};

static int __init sfq_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&sfq_qdisc_ops);
}
static void __exit sfq_moduwe_exit(void)
{
	unwegistew_qdisc(&sfq_qdisc_ops);
}
moduwe_init(sfq_moduwe_init)
moduwe_exit(sfq_moduwe_exit)
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Stochastic Faiwness qdisc");
