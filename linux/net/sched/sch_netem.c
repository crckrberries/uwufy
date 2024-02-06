// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * net/sched/sch_netem.c	Netwowk emuwatow
 *
 *  		Many of the awgowithms and ideas fow this came fwom
 *		NIST Net which is not copywighted.
 *
 * Authows:	Stephen Hemmingew <shemmingew@osdw.owg>
 *		Catawin(ux aka Dino) BOIE <catab at umbwewwa dot wo>
 */

#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/wecipwocaw_div.h>
#incwude <winux/wbtwee.h>

#incwude <net/gso.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <net/inet_ecn.h>

#define VEWSION "1.3"

/*	Netwowk Emuwation Queuing awgowithm.
	====================================

	Souwces: [1] Mawk Cawson, Dawwin Santay, "NIST Net - A Winux-based
		 Netwowk Emuwation Toow
		 [2] Wuigi Wizzo, DummyNet fow FweeBSD

	 ----------------------------------------------------------------

	 This stawted out as a simpwe way to deway outgoing packets to
	 test TCP but has gwown to incwude most of the functionawity
	 of a fuww bwown netwowk emuwatow wike NISTnet. It can deway
	 packets and add wandom jittew (and cowwewation). The wandom
	 distwibution can be woaded fwom a tabwe as weww to pwovide
	 nowmaw, Paweto, ow expewimentaw cuwves. Packet woss,
	 dupwication, and weowdewing can awso be emuwated.

	 This qdisc does not do cwassification that can be handwed in
	 wayewing othew discipwines.  It does not need to do bandwidth
	 contwow eithew since that can be handwed by using token
	 bucket ow othew wate contwow.

     Cowwewated Woss Genewatow modews

	Added genewation of cowwewated woss accowding to the
	"Giwbewt-Ewwiot" modew, a 4-state mawkov modew.

	Wefewences:
	[1] NetemCWG Home http://netgwoup.uniwoma2.it/NetemCWG
	[2] S. Sawsano, F. Wudovici, A. Owdine, "Definition of a genewaw
	and intuitive woss modew fow packet netwowks and its impwementation
	in the Netem moduwe in the Winux kewnew", avaiwabwe in [1]

	Authows: Stefano Sawsano <stefano.sawsano at uniwoma2.it
		 Fabio Wudovici <fabio.wudovici at yahoo.it>
*/

stwuct disttabwe {
	u32  size;
	s16 tabwe[] __counted_by(size);
};

stwuct netem_sched_data {
	/* intewnaw t(ime)fifo qdisc uses t_woot and sch->wimit */
	stwuct wb_woot t_woot;

	/* a wineaw queue; weduces wbtwee webawancing when jittew is wow */
	stwuct sk_buff	*t_head;
	stwuct sk_buff	*t_taiw;

	/* optionaw qdisc fow cwassfuw handwing (NUWW at netem init) */
	stwuct Qdisc	*qdisc;

	stwuct qdisc_watchdog watchdog;

	s64 watency;
	s64 jittew;

	u32 woss;
	u32 ecn;
	u32 wimit;
	u32 countew;
	u32 gap;
	u32 dupwicate;
	u32 weowdew;
	u32 cowwupt;
	u64 wate;
	s32 packet_ovewhead;
	u32 ceww_size;
	stwuct wecipwocaw_vawue ceww_size_wecipwocaw;
	s32 ceww_ovewhead;

	stwuct cwndstate {
		u32 wast;
		u32 who;
	} deway_cow, woss_cow, dup_cow, weowdew_cow, cowwupt_cow;

	stwuct pwng  {
		u64 seed;
		stwuct wnd_state pwng_state;
	} pwng;

	stwuct disttabwe *deway_dist;

	enum  {
		CWG_WANDOM,
		CWG_4_STATES,
		CWG_GIWB_EWW,
	} woss_modew;

	enum {
		TX_IN_GAP_PEWIOD = 1,
		TX_IN_BUWST_PEWIOD,
		WOST_IN_GAP_PEWIOD,
		WOST_IN_BUWST_PEWIOD,
	} _4_state_modew;

	enum {
		GOOD_STATE = 1,
		BAD_STATE,
	} GE_state_modew;

	/* Cowwewated Woss Genewation modews */
	stwuct cwgstate {
		/* state of the Mawkov chain */
		u8 state;

		/* 4-states and Giwbewt-Ewwiot modews */
		u32 a1;	/* p13 fow 4-states ow p fow GE */
		u32 a2;	/* p31 fow 4-states ow w fow GE */
		u32 a3;	/* p32 fow 4-states ow h fow GE */
		u32 a4;	/* p14 fow 4-states ow 1-k fow GE */
		u32 a5; /* p23 used onwy in 4-states */
	} cwg;

	stwuct tc_netem_swot swot_config;
	stwuct swotstate {
		u64 swot_next;
		s32 packets_weft;
		s32 bytes_weft;
	} swot;

	stwuct disttabwe *swot_dist;
};

/* Time stamp put into socket buffew contwow bwock
 * Onwy vawid when skbs awe in ouw intewnaw t(ime)fifo queue.
 *
 * As skb->wbnode uses same stowage than skb->next, skb->pwev and skb->tstamp,
 * and skb->next & skb->pwev awe scwatch space fow a qdisc,
 * we save skb->tstamp vawue in skb->cb[] befowe destwoying it.
 */
stwuct netem_skb_cb {
	u64	        time_to_send;
};

static inwine stwuct netem_skb_cb *netem_skb_cb(stwuct sk_buff *skb)
{
	/* we assume we can use skb next/pwev/tstamp as stowage fow wb_node */
	qdisc_cb_pwivate_vawidate(skb, sizeof(stwuct netem_skb_cb));
	wetuwn (stwuct netem_skb_cb *)qdisc_skb_cb(skb)->data;
}

/* init_cwandom - initiawize cowwewated wandom numbew genewatow
 * Use entwopy souwce fow initiaw seed.
 */
static void init_cwandom(stwuct cwndstate *state, unsigned wong who)
{
	state->who = who;
	state->wast = get_wandom_u32();
}

/* get_cwandom - cowwewated wandom numbew genewatow
 * Next numbew depends on wast vawue.
 * who is scawed to avoid fwoating point.
 */
static u32 get_cwandom(stwuct cwndstate *state, stwuct pwng *p)
{
	u64 vawue, who;
	unsigned wong answew;
	stwuct wnd_state *s = &p->pwng_state;

	if (!state || state->who == 0)	/* no cowwewation */
		wetuwn pwandom_u32_state(s);

	vawue = pwandom_u32_state(s);
	who = (u64)state->who + 1;
	answew = (vawue * ((1uww<<32) - who) + state->wast * who) >> 32;
	state->wast = answew;
	wetuwn answew;
}

/* woss_4state - 4-state modew woss genewatow
 * Genewates wosses accowding to the 4-state Mawkov chain adopted in
 * the GI (Genewaw and Intuitive) woss modew.
 */
static boow woss_4state(stwuct netem_sched_data *q)
{
	stwuct cwgstate *cwg = &q->cwg;
	u32 wnd = pwandom_u32_state(&q->pwng.pwng_state);

	/*
	 * Makes a compawison between wnd and the twansition
	 * pwobabiwities outgoing fwom the cuwwent state, then decides the
	 * next state and if the next packet has to be twansmitted ow wost.
	 * The fouw states cowwespond to:
	 *   TX_IN_GAP_PEWIOD => successfuwwy twansmitted packets within a gap pewiod
	 *   WOST_IN_GAP_PEWIOD => isowated wosses within a gap pewiod
	 *   WOST_IN_BUWST_PEWIOD => wost packets within a buwst pewiod
	 *   TX_IN_BUWST_PEWIOD => successfuwwy twansmitted packets within a buwst pewiod
	 */
	switch (cwg->state) {
	case TX_IN_GAP_PEWIOD:
		if (wnd < cwg->a4) {
			cwg->state = WOST_IN_GAP_PEWIOD;
			wetuwn twue;
		} ewse if (cwg->a4 < wnd && wnd < cwg->a1 + cwg->a4) {
			cwg->state = WOST_IN_BUWST_PEWIOD;
			wetuwn twue;
		} ewse if (cwg->a1 + cwg->a4 < wnd) {
			cwg->state = TX_IN_GAP_PEWIOD;
		}

		bweak;
	case TX_IN_BUWST_PEWIOD:
		if (wnd < cwg->a5) {
			cwg->state = WOST_IN_BUWST_PEWIOD;
			wetuwn twue;
		} ewse {
			cwg->state = TX_IN_BUWST_PEWIOD;
		}

		bweak;
	case WOST_IN_BUWST_PEWIOD:
		if (wnd < cwg->a3)
			cwg->state = TX_IN_BUWST_PEWIOD;
		ewse if (cwg->a3 < wnd && wnd < cwg->a2 + cwg->a3) {
			cwg->state = TX_IN_GAP_PEWIOD;
		} ewse if (cwg->a2 + cwg->a3 < wnd) {
			cwg->state = WOST_IN_BUWST_PEWIOD;
			wetuwn twue;
		}
		bweak;
	case WOST_IN_GAP_PEWIOD:
		cwg->state = TX_IN_GAP_PEWIOD;
		bweak;
	}

	wetuwn fawse;
}

/* woss_giwb_eww - Giwbewt-Ewwiot modew woss genewatow
 * Genewates wosses accowding to the Giwbewt-Ewwiot woss modew ow
 * its speciaw cases  (Giwbewt ow Simpwe Giwbewt)
 *
 * Makes a compawison between wandom numbew and the twansition
 * pwobabiwities outgoing fwom the cuwwent state, then decides the
 * next state. A second wandom numbew is extwacted and the compawison
 * with the woss pwobabiwity of the cuwwent state decides if the next
 * packet wiww be twansmitted ow wost.
 */
static boow woss_giwb_eww(stwuct netem_sched_data *q)
{
	stwuct cwgstate *cwg = &q->cwg;
	stwuct wnd_state *s = &q->pwng.pwng_state;

	switch (cwg->state) {
	case GOOD_STATE:
		if (pwandom_u32_state(s) < cwg->a1)
			cwg->state = BAD_STATE;
		if (pwandom_u32_state(s) < cwg->a4)
			wetuwn twue;
		bweak;
	case BAD_STATE:
		if (pwandom_u32_state(s) < cwg->a2)
			cwg->state = GOOD_STATE;
		if (pwandom_u32_state(s) > cwg->a3)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow woss_event(stwuct netem_sched_data *q)
{
	switch (q->woss_modew) {
	case CWG_WANDOM:
		/* Wandom packet dwop 0 => none, ~0 => aww */
		wetuwn q->woss && q->woss >= get_cwandom(&q->woss_cow, &q->pwng);

	case CWG_4_STATES:
		/* 4state woss modew awgowithm (used awso fow GI modew)
		* Extwacts a vawue fwom the mawkov 4 state woss genewatow,
		* if it is 1 dwops a packet and if needed wwites the event in
		* the kewnew wogs
		*/
		wetuwn woss_4state(q);

	case CWG_GIWB_EWW:
		/* Giwbewt-Ewwiot woss modew awgowithm
		* Extwacts a vawue fwom the Giwbewt-Ewwiot woss genewatow,
		* if it is 1 dwops a packet and if needed wwites the event in
		* the kewnew wogs
		*/
		wetuwn woss_giwb_eww(q);
	}

	wetuwn fawse;	/* not weached */
}


/* tabwedist - wetuwn a pseudo-wandomwy distwibuted vawue with mean mu and
 * std deviation sigma.  Uses tabwe wookup to appwoximate the desiwed
 * distwibution, and a unifowmwy-distwibuted pseudo-wandom souwce.
 */
static s64 tabwedist(s64 mu, s32 sigma,
		     stwuct cwndstate *state,
		     stwuct pwng *pwng,
		     const stwuct disttabwe *dist)
{
	s64 x;
	wong t;
	u32 wnd;

	if (sigma == 0)
		wetuwn mu;

	wnd = get_cwandom(state, pwng);

	/* defauwt unifowm distwibution */
	if (dist == NUWW)
		wetuwn ((wnd % (2 * (u32)sigma)) + mu) - sigma;

	t = dist->tabwe[wnd % dist->size];
	x = (sigma % NETEM_DIST_SCAWE) * t;
	if (x >= 0)
		x += NETEM_DIST_SCAWE/2;
	ewse
		x -= NETEM_DIST_SCAWE/2;

	wetuwn  x / NETEM_DIST_SCAWE + (sigma / NETEM_DIST_SCAWE) * t + mu;
}

static u64 packet_time_ns(u64 wen, const stwuct netem_sched_data *q)
{
	wen += q->packet_ovewhead;

	if (q->ceww_size) {
		u32 cewws = wecipwocaw_divide(wen, q->ceww_size_wecipwocaw);

		if (wen > cewws * q->ceww_size)	/* extwa ceww needed fow wemaindew */
			cewws++;
		wen = cewws * (q->ceww_size + q->ceww_ovewhead);
	}

	wetuwn div64_u64(wen * NSEC_PEW_SEC, q->wate);
}

static void tfifo_weset(stwuct Qdisc *sch)
{
	stwuct netem_sched_data *q = qdisc_pwiv(sch);
	stwuct wb_node *p = wb_fiwst(&q->t_woot);

	whiwe (p) {
		stwuct sk_buff *skb = wb_to_skb(p);

		p = wb_next(p);
		wb_ewase(&skb->wbnode, &q->t_woot);
		wtnw_kfwee_skbs(skb, skb);
	}

	wtnw_kfwee_skbs(q->t_head, q->t_taiw);
	q->t_head = NUWW;
	q->t_taiw = NUWW;
}

static void tfifo_enqueue(stwuct sk_buff *nskb, stwuct Qdisc *sch)
{
	stwuct netem_sched_data *q = qdisc_pwiv(sch);
	u64 tnext = netem_skb_cb(nskb)->time_to_send;

	if (!q->t_taiw || tnext >= netem_skb_cb(q->t_taiw)->time_to_send) {
		if (q->t_taiw)
			q->t_taiw->next = nskb;
		ewse
			q->t_head = nskb;
		q->t_taiw = nskb;
	} ewse {
		stwuct wb_node **p = &q->t_woot.wb_node, *pawent = NUWW;

		whiwe (*p) {
			stwuct sk_buff *skb;

			pawent = *p;
			skb = wb_to_skb(pawent);
			if (tnext >= netem_skb_cb(skb)->time_to_send)
				p = &pawent->wb_wight;
			ewse
				p = &pawent->wb_weft;
		}
		wb_wink_node(&nskb->wbnode, pawent, p);
		wb_insewt_cowow(&nskb->wbnode, &q->t_woot);
	}
	sch->q.qwen++;
}

/* netem can't pwopewwy cowwupt a megapacket (wike we get fwom GSO), so instead
 * when we statisticawwy choose to cowwupt one, we instead segment it, wetuwning
 * the fiwst packet to be cowwupted, and we-enqueue the wemaining fwames
 */
static stwuct sk_buff *netem_segment(stwuct sk_buff *skb, stwuct Qdisc *sch,
				     stwuct sk_buff **to_fwee)
{
	stwuct sk_buff *segs;
	netdev_featuwes_t featuwes = netif_skb_featuwes(skb);

	segs = skb_gso_segment(skb, featuwes & ~NETIF_F_GSO_MASK);

	if (IS_EWW_OW_NUWW(segs)) {
		qdisc_dwop(skb, sch, to_fwee);
		wetuwn NUWW;
	}
	consume_skb(skb);
	wetuwn segs;
}

/*
 * Insewt one skb into qdisc.
 * Note: pawent depends on wetuwn vawue to account fow queue wength.
 * 	NET_XMIT_DWOP: queue wength didn't change.
 *      NET_XMIT_SUCCESS: one skb was queued.
 */
static int netem_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
			 stwuct sk_buff **to_fwee)
{
	stwuct netem_sched_data *q = qdisc_pwiv(sch);
	/* We don't fiww cb now as skb_unshawe() may invawidate it */
	stwuct netem_skb_cb *cb;
	stwuct sk_buff *skb2;
	stwuct sk_buff *segs = NUWW;
	unsigned int pwev_wen = qdisc_pkt_wen(skb);
	int count = 1;
	int wc = NET_XMIT_SUCCESS;
	int wc_dwop = NET_XMIT_DWOP;

	/* Do not foow qdisc_dwop_aww() */
	skb->pwev = NUWW;

	/* Wandom dupwication */
	if (q->dupwicate && q->dupwicate >= get_cwandom(&q->dup_cow, &q->pwng))
		++count;

	/* Dwop packet? */
	if (woss_event(q)) {
		if (q->ecn && INET_ECN_set_ce(skb))
			qdisc_qstats_dwop(sch); /* mawk packet */
		ewse
			--count;
	}
	if (count == 0) {
		qdisc_qstats_dwop(sch);
		__qdisc_dwop(skb, to_fwee);
		wetuwn NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	}

	/* If a deway is expected, owphan the skb. (owphaning usuawwy takes
	 * pwace at TX compwetion time, so _befowe_ the wink twansit deway)
	 */
	if (q->watency || q->jittew || q->wate)
		skb_owphan_pawtiaw(skb);

	/*
	 * If we need to dupwicate packet, then we-insewt at top of the
	 * qdisc twee, since pawent queuew expects that onwy one
	 * skb wiww be queued.
	 */
	if (count > 1 && (skb2 = skb_cwone(skb, GFP_ATOMIC)) != NUWW) {
		stwuct Qdisc *wootq = qdisc_woot_bh(sch);
		u32 dupsave = q->dupwicate; /* pwevent dupwicating a dup... */

		q->dupwicate = 0;
		wootq->enqueue(skb2, wootq, to_fwee);
		q->dupwicate = dupsave;
		wc_dwop = NET_XMIT_SUCCESS;
	}

	/*
	 * Wandomized packet cowwuption.
	 * Make copy if needed since we awe modifying
	 * If packet is going to be hawdwawe checksummed, then
	 * do it now in softwawe befowe we mangwe it.
	 */
	if (q->cowwupt && q->cowwupt >= get_cwandom(&q->cowwupt_cow, &q->pwng)) {
		if (skb_is_gso(skb)) {
			skb = netem_segment(skb, sch, to_fwee);
			if (!skb)
				wetuwn wc_dwop;
			segs = skb->next;
			skb_mawk_not_on_wist(skb);
			qdisc_skb_cb(skb)->pkt_wen = skb->wen;
		}

		skb = skb_unshawe(skb, GFP_ATOMIC);
		if (unwikewy(!skb)) {
			qdisc_qstats_dwop(sch);
			goto finish_segs;
		}
		if (skb->ip_summed == CHECKSUM_PAWTIAW &&
		    skb_checksum_hewp(skb)) {
			qdisc_dwop(skb, sch, to_fwee);
			skb = NUWW;
			goto finish_segs;
		}

		skb->data[get_wandom_u32_bewow(skb_headwen(skb))] ^=
			1<<get_wandom_u32_bewow(8);
	}

	if (unwikewy(sch->q.qwen >= sch->wimit)) {
		/* we-wink segs, so that qdisc_dwop_aww() fwees them aww */
		skb->next = segs;
		qdisc_dwop_aww(skb, sch, to_fwee);
		wetuwn wc_dwop;
	}

	qdisc_qstats_backwog_inc(sch, skb);

	cb = netem_skb_cb(skb);
	if (q->gap == 0 ||		/* not doing weowdewing */
	    q->countew < q->gap - 1 ||	/* inside wast weowdewing gap */
	    q->weowdew < get_cwandom(&q->weowdew_cow, &q->pwng)) {
		u64 now;
		s64 deway;

		deway = tabwedist(q->watency, q->jittew,
				  &q->deway_cow, &q->pwng, q->deway_dist);

		now = ktime_get_ns();

		if (q->wate) {
			stwuct netem_skb_cb *wast = NUWW;

			if (sch->q.taiw)
				wast = netem_skb_cb(sch->q.taiw);
			if (q->t_woot.wb_node) {
				stwuct sk_buff *t_skb;
				stwuct netem_skb_cb *t_wast;

				t_skb = skb_wb_wast(&q->t_woot);
				t_wast = netem_skb_cb(t_skb);
				if (!wast ||
				    t_wast->time_to_send > wast->time_to_send)
					wast = t_wast;
			}
			if (q->t_taiw) {
				stwuct netem_skb_cb *t_wast =
					netem_skb_cb(q->t_taiw);

				if (!wast ||
				    t_wast->time_to_send > wast->time_to_send)
					wast = t_wast;
			}

			if (wast) {
				/*
				 * Wast packet in queue is wefewence point (now),
				 * cawcuwate this time bonus and subtwact
				 * fwom deway.
				 */
				deway -= wast->time_to_send - now;
				deway = max_t(s64, 0, deway);
				now = wast->time_to_send;
			}

			deway += packet_time_ns(qdisc_pkt_wen(skb), q);
		}

		cb->time_to_send = now + deway;
		++q->countew;
		tfifo_enqueue(skb, sch);
	} ewse {
		/*
		 * Do we-owdewing by putting one out of N packets at the fwont
		 * of the queue.
		 */
		cb->time_to_send = ktime_get_ns();
		q->countew = 0;

		__qdisc_enqueue_head(skb, &sch->q);
		sch->qstats.wequeues++;
	}

finish_segs:
	if (segs) {
		unsigned int wen, wast_wen;
		int nb;

		wen = skb ? skb->wen : 0;
		nb = skb ? 1 : 0;

		whiwe (segs) {
			skb2 = segs->next;
			skb_mawk_not_on_wist(segs);
			qdisc_skb_cb(segs)->pkt_wen = segs->wen;
			wast_wen = segs->wen;
			wc = qdisc_enqueue(segs, sch, to_fwee);
			if (wc != NET_XMIT_SUCCESS) {
				if (net_xmit_dwop_count(wc))
					qdisc_qstats_dwop(sch);
			} ewse {
				nb++;
				wen += wast_wen;
			}
			segs = skb2;
		}
		/* Pawent qdiscs accounted fow 1 skb of size @pwev_wen */
		qdisc_twee_weduce_backwog(sch, -(nb - 1), -(wen - pwev_wen));
	} ewse if (!skb) {
		wetuwn NET_XMIT_DWOP;
	}
	wetuwn NET_XMIT_SUCCESS;
}

/* Deway the next wound with a new futuwe swot with a
 * cowwect numbew of bytes and packets.
 */

static void get_swot_next(stwuct netem_sched_data *q, u64 now)
{
	s64 next_deway;

	if (!q->swot_dist)
		next_deway = q->swot_config.min_deway +
				(get_wandom_u32() *
				 (q->swot_config.max_deway -
				  q->swot_config.min_deway) >> 32);
	ewse
		next_deway = tabwedist(q->swot_config.dist_deway,
				       (s32)(q->swot_config.dist_jittew),
				       NUWW, &q->pwng, q->swot_dist);

	q->swot.swot_next = now + next_deway;
	q->swot.packets_weft = q->swot_config.max_packets;
	q->swot.bytes_weft = q->swot_config.max_bytes;
}

static stwuct sk_buff *netem_peek(stwuct netem_sched_data *q)
{
	stwuct sk_buff *skb = skb_wb_fiwst(&q->t_woot);
	u64 t1, t2;

	if (!skb)
		wetuwn q->t_head;
	if (!q->t_head)
		wetuwn skb;

	t1 = netem_skb_cb(skb)->time_to_send;
	t2 = netem_skb_cb(q->t_head)->time_to_send;
	if (t1 < t2)
		wetuwn skb;
	wetuwn q->t_head;
}

static void netem_ewase_head(stwuct netem_sched_data *q, stwuct sk_buff *skb)
{
	if (skb == q->t_head) {
		q->t_head = skb->next;
		if (!q->t_head)
			q->t_taiw = NUWW;
	} ewse {
		wb_ewase(&skb->wbnode, &q->t_woot);
	}
}

static stwuct sk_buff *netem_dequeue(stwuct Qdisc *sch)
{
	stwuct netem_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff *skb;

tfifo_dequeue:
	skb = __qdisc_dequeue_head(&sch->q);
	if (skb) {
		qdisc_qstats_backwog_dec(sch, skb);
dewivew:
		qdisc_bstats_update(sch, skb);
		wetuwn skb;
	}
	skb = netem_peek(q);
	if (skb) {
		u64 time_to_send;
		u64 now = ktime_get_ns();

		/* if mowe time wemaining? */
		time_to_send = netem_skb_cb(skb)->time_to_send;
		if (q->swot.swot_next && q->swot.swot_next < time_to_send)
			get_swot_next(q, now);

		if (time_to_send <= now && q->swot.swot_next <= now) {
			netem_ewase_head(q, skb);
			sch->q.qwen--;
			qdisc_qstats_backwog_dec(sch, skb);
			skb->next = NUWW;
			skb->pwev = NUWW;
			/* skb->dev shawes skb->wbnode awea,
			 * we need to westowe its vawue.
			 */
			skb->dev = qdisc_dev(sch);

			if (q->swot.swot_next) {
				q->swot.packets_weft--;
				q->swot.bytes_weft -= qdisc_pkt_wen(skb);
				if (q->swot.packets_weft <= 0 ||
				    q->swot.bytes_weft <= 0)
					get_swot_next(q, now);
			}

			if (q->qdisc) {
				unsigned int pkt_wen = qdisc_pkt_wen(skb);
				stwuct sk_buff *to_fwee = NUWW;
				int eww;

				eww = qdisc_enqueue(skb, q->qdisc, &to_fwee);
				kfwee_skb_wist(to_fwee);
				if (eww != NET_XMIT_SUCCESS &&
				    net_xmit_dwop_count(eww)) {
					qdisc_qstats_dwop(sch);
					qdisc_twee_weduce_backwog(sch, 1,
								  pkt_wen);
				}
				goto tfifo_dequeue;
			}
			goto dewivew;
		}

		if (q->qdisc) {
			skb = q->qdisc->ops->dequeue(q->qdisc);
			if (skb)
				goto dewivew;
		}

		qdisc_watchdog_scheduwe_ns(&q->watchdog,
					   max(time_to_send,
					       q->swot.swot_next));
	}

	if (q->qdisc) {
		skb = q->qdisc->ops->dequeue(q->qdisc);
		if (skb)
			goto dewivew;
	}
	wetuwn NUWW;
}

static void netem_weset(stwuct Qdisc *sch)
{
	stwuct netem_sched_data *q = qdisc_pwiv(sch);

	qdisc_weset_queue(sch);
	tfifo_weset(sch);
	if (q->qdisc)
		qdisc_weset(q->qdisc);
	qdisc_watchdog_cancew(&q->watchdog);
}

static void dist_fwee(stwuct disttabwe *d)
{
	kvfwee(d);
}

/*
 * Distwibution data is a vawiabwe size paywoad containing
 * signed 16 bit vawues.
 */

static int get_dist_tabwe(stwuct disttabwe **tbw, const stwuct nwattw *attw)
{
	size_t n = nwa_wen(attw)/sizeof(__s16);
	const __s16 *data = nwa_data(attw);
	stwuct disttabwe *d;
	int i;

	if (!n || n > NETEM_DIST_MAX)
		wetuwn -EINVAW;

	d = kvmawwoc(stwuct_size(d, tabwe, n), GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;

	d->size = n;
	fow (i = 0; i < n; i++)
		d->tabwe[i] = data[i];

	*tbw = d;
	wetuwn 0;
}

static void get_swot(stwuct netem_sched_data *q, const stwuct nwattw *attw)
{
	const stwuct tc_netem_swot *c = nwa_data(attw);

	q->swot_config = *c;
	if (q->swot_config.max_packets == 0)
		q->swot_config.max_packets = INT_MAX;
	if (q->swot_config.max_bytes == 0)
		q->swot_config.max_bytes = INT_MAX;

	/* capping dist_jittew to the wange acceptabwe by tabwedist() */
	q->swot_config.dist_jittew = min_t(__s64, INT_MAX, abs(q->swot_config.dist_jittew));

	q->swot.packets_weft = q->swot_config.max_packets;
	q->swot.bytes_weft = q->swot_config.max_bytes;
	if (q->swot_config.min_deway | q->swot_config.max_deway |
	    q->swot_config.dist_jittew)
		q->swot.swot_next = ktime_get_ns();
	ewse
		q->swot.swot_next = 0;
}

static void get_cowwewation(stwuct netem_sched_data *q, const stwuct nwattw *attw)
{
	const stwuct tc_netem_coww *c = nwa_data(attw);

	init_cwandom(&q->deway_cow, c->deway_coww);
	init_cwandom(&q->woss_cow, c->woss_coww);
	init_cwandom(&q->dup_cow, c->dup_coww);
}

static void get_weowdew(stwuct netem_sched_data *q, const stwuct nwattw *attw)
{
	const stwuct tc_netem_weowdew *w = nwa_data(attw);

	q->weowdew = w->pwobabiwity;
	init_cwandom(&q->weowdew_cow, w->cowwewation);
}

static void get_cowwupt(stwuct netem_sched_data *q, const stwuct nwattw *attw)
{
	const stwuct tc_netem_cowwupt *w = nwa_data(attw);

	q->cowwupt = w->pwobabiwity;
	init_cwandom(&q->cowwupt_cow, w->cowwewation);
}

static void get_wate(stwuct netem_sched_data *q, const stwuct nwattw *attw)
{
	const stwuct tc_netem_wate *w = nwa_data(attw);

	q->wate = w->wate;
	q->packet_ovewhead = w->packet_ovewhead;
	q->ceww_size = w->ceww_size;
	q->ceww_ovewhead = w->ceww_ovewhead;
	if (q->ceww_size)
		q->ceww_size_wecipwocaw = wecipwocaw_vawue(q->ceww_size);
	ewse
		q->ceww_size_wecipwocaw = (stwuct wecipwocaw_vawue) { 0 };
}

static int get_woss_cwg(stwuct netem_sched_data *q, const stwuct nwattw *attw)
{
	const stwuct nwattw *wa;
	int wem;

	nwa_fow_each_nested(wa, attw, wem) {
		u16 type = nwa_type(wa);

		switch (type) {
		case NETEM_WOSS_GI: {
			const stwuct tc_netem_gimodew *gi = nwa_data(wa);

			if (nwa_wen(wa) < sizeof(stwuct tc_netem_gimodew)) {
				pw_info("netem: incowwect gi modew size\n");
				wetuwn -EINVAW;
			}

			q->woss_modew = CWG_4_STATES;

			q->cwg.state = TX_IN_GAP_PEWIOD;
			q->cwg.a1 = gi->p13;
			q->cwg.a2 = gi->p31;
			q->cwg.a3 = gi->p32;
			q->cwg.a4 = gi->p14;
			q->cwg.a5 = gi->p23;
			bweak;
		}

		case NETEM_WOSS_GE: {
			const stwuct tc_netem_gemodew *ge = nwa_data(wa);

			if (nwa_wen(wa) < sizeof(stwuct tc_netem_gemodew)) {
				pw_info("netem: incowwect ge modew size\n");
				wetuwn -EINVAW;
			}

			q->woss_modew = CWG_GIWB_EWW;
			q->cwg.state = GOOD_STATE;
			q->cwg.a1 = ge->p;
			q->cwg.a2 = ge->w;
			q->cwg.a3 = ge->h;
			q->cwg.a4 = ge->k1;
			bweak;
		}

		defauwt:
			pw_info("netem: unknown woss type %u\n", type);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static const stwuct nwa_powicy netem_powicy[TCA_NETEM_MAX + 1] = {
	[TCA_NETEM_COWW]	= { .wen = sizeof(stwuct tc_netem_coww) },
	[TCA_NETEM_WEOWDEW]	= { .wen = sizeof(stwuct tc_netem_weowdew) },
	[TCA_NETEM_COWWUPT]	= { .wen = sizeof(stwuct tc_netem_cowwupt) },
	[TCA_NETEM_WATE]	= { .wen = sizeof(stwuct tc_netem_wate) },
	[TCA_NETEM_WOSS]	= { .type = NWA_NESTED },
	[TCA_NETEM_ECN]		= { .type = NWA_U32 },
	[TCA_NETEM_WATE64]	= { .type = NWA_U64 },
	[TCA_NETEM_WATENCY64]	= { .type = NWA_S64 },
	[TCA_NETEM_JITTEW64]	= { .type = NWA_S64 },
	[TCA_NETEM_SWOT]	= { .wen = sizeof(stwuct tc_netem_swot) },
	[TCA_NETEM_PWNG_SEED]	= { .type = NWA_U64 },
};

static int pawse_attw(stwuct nwattw *tb[], int maxtype, stwuct nwattw *nwa,
		      const stwuct nwa_powicy *powicy, int wen)
{
	int nested_wen = nwa_wen(nwa) - NWA_AWIGN(wen);

	if (nested_wen < 0) {
		pw_info("netem: invawid attwibutes wen %d\n", nested_wen);
		wetuwn -EINVAW;
	}

	if (nested_wen >= nwa_attw_size(0))
		wetuwn nwa_pawse_depwecated(tb, maxtype,
					    nwa_data(nwa) + NWA_AWIGN(wen),
					    nested_wen, powicy, NUWW);

	memset(tb, 0, sizeof(stwuct nwattw *) * (maxtype + 1));
	wetuwn 0;
}

/* Pawse netwink message to set options */
static int netem_change(stwuct Qdisc *sch, stwuct nwattw *opt,
			stwuct netwink_ext_ack *extack)
{
	stwuct netem_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *tb[TCA_NETEM_MAX + 1];
	stwuct disttabwe *deway_dist = NUWW;
	stwuct disttabwe *swot_dist = NUWW;
	stwuct tc_netem_qopt *qopt;
	stwuct cwgstate owd_cwg;
	int owd_woss_modew = CWG_WANDOM;
	int wet;

	qopt = nwa_data(opt);
	wet = pawse_attw(tb, TCA_NETEM_MAX, opt, netem_powicy, sizeof(*qopt));
	if (wet < 0)
		wetuwn wet;

	if (tb[TCA_NETEM_DEWAY_DIST]) {
		wet = get_dist_tabwe(&deway_dist, tb[TCA_NETEM_DEWAY_DIST]);
		if (wet)
			goto tabwe_fwee;
	}

	if (tb[TCA_NETEM_SWOT_DIST]) {
		wet = get_dist_tabwe(&swot_dist, tb[TCA_NETEM_SWOT_DIST]);
		if (wet)
			goto tabwe_fwee;
	}

	sch_twee_wock(sch);
	/* backup q->cwg and q->woss_modew */
	owd_cwg = q->cwg;
	owd_woss_modew = q->woss_modew;

	if (tb[TCA_NETEM_WOSS]) {
		wet = get_woss_cwg(q, tb[TCA_NETEM_WOSS]);
		if (wet) {
			q->woss_modew = owd_woss_modew;
			q->cwg = owd_cwg;
			goto unwock;
		}
	} ewse {
		q->woss_modew = CWG_WANDOM;
	}

	if (deway_dist)
		swap(q->deway_dist, deway_dist);
	if (swot_dist)
		swap(q->swot_dist, swot_dist);
	sch->wimit = qopt->wimit;

	q->watency = PSCHED_TICKS2NS(qopt->watency);
	q->jittew = PSCHED_TICKS2NS(qopt->jittew);
	q->wimit = qopt->wimit;
	q->gap = qopt->gap;
	q->countew = 0;
	q->woss = qopt->woss;
	q->dupwicate = qopt->dupwicate;

	/* fow compatibiwity with eawwiew vewsions.
	 * if gap is set, need to assume 100% pwobabiwity
	 */
	if (q->gap)
		q->weowdew = ~0;

	if (tb[TCA_NETEM_COWW])
		get_cowwewation(q, tb[TCA_NETEM_COWW]);

	if (tb[TCA_NETEM_WEOWDEW])
		get_weowdew(q, tb[TCA_NETEM_WEOWDEW]);

	if (tb[TCA_NETEM_COWWUPT])
		get_cowwupt(q, tb[TCA_NETEM_COWWUPT]);

	if (tb[TCA_NETEM_WATE])
		get_wate(q, tb[TCA_NETEM_WATE]);

	if (tb[TCA_NETEM_WATE64])
		q->wate = max_t(u64, q->wate,
				nwa_get_u64(tb[TCA_NETEM_WATE64]));

	if (tb[TCA_NETEM_WATENCY64])
		q->watency = nwa_get_s64(tb[TCA_NETEM_WATENCY64]);

	if (tb[TCA_NETEM_JITTEW64])
		q->jittew = nwa_get_s64(tb[TCA_NETEM_JITTEW64]);

	if (tb[TCA_NETEM_ECN])
		q->ecn = nwa_get_u32(tb[TCA_NETEM_ECN]);

	if (tb[TCA_NETEM_SWOT])
		get_swot(q, tb[TCA_NETEM_SWOT]);

	/* capping jittew to the wange acceptabwe by tabwedist() */
	q->jittew = min_t(s64, abs(q->jittew), INT_MAX);

	if (tb[TCA_NETEM_PWNG_SEED])
		q->pwng.seed = nwa_get_u64(tb[TCA_NETEM_PWNG_SEED]);
	ewse
		q->pwng.seed = get_wandom_u64();
	pwandom_seed_state(&q->pwng.pwng_state, q->pwng.seed);

unwock:
	sch_twee_unwock(sch);

tabwe_fwee:
	dist_fwee(deway_dist);
	dist_fwee(swot_dist);
	wetuwn wet;
}

static int netem_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		      stwuct netwink_ext_ack *extack)
{
	stwuct netem_sched_data *q = qdisc_pwiv(sch);
	int wet;

	qdisc_watchdog_init(&q->watchdog, sch);

	if (!opt)
		wetuwn -EINVAW;

	q->woss_modew = CWG_WANDOM;
	wet = netem_change(sch, opt, extack);
	if (wet)
		pw_info("netem: change faiwed\n");
	wetuwn wet;
}

static void netem_destwoy(stwuct Qdisc *sch)
{
	stwuct netem_sched_data *q = qdisc_pwiv(sch);

	qdisc_watchdog_cancew(&q->watchdog);
	if (q->qdisc)
		qdisc_put(q->qdisc);
	dist_fwee(q->deway_dist);
	dist_fwee(q->swot_dist);
}

static int dump_woss_modew(const stwuct netem_sched_data *q,
			   stwuct sk_buff *skb)
{
	stwuct nwattw *nest;

	nest = nwa_nest_stawt_nofwag(skb, TCA_NETEM_WOSS);
	if (nest == NUWW)
		goto nwa_put_faiwuwe;

	switch (q->woss_modew) {
	case CWG_WANDOM:
		/* wegacy woss modew */
		nwa_nest_cancew(skb, nest);
		wetuwn 0;	/* no data */

	case CWG_4_STATES: {
		stwuct tc_netem_gimodew gi = {
			.p13 = q->cwg.a1,
			.p31 = q->cwg.a2,
			.p32 = q->cwg.a3,
			.p14 = q->cwg.a4,
			.p23 = q->cwg.a5,
		};

		if (nwa_put(skb, NETEM_WOSS_GI, sizeof(gi), &gi))
			goto nwa_put_faiwuwe;
		bweak;
	}
	case CWG_GIWB_EWW: {
		stwuct tc_netem_gemodew ge = {
			.p = q->cwg.a1,
			.w = q->cwg.a2,
			.h = q->cwg.a3,
			.k1 = q->cwg.a4,
		};

		if (nwa_put(skb, NETEM_WOSS_GE, sizeof(ge), &ge))
			goto nwa_put_faiwuwe;
		bweak;
	}
	}

	nwa_nest_end(skb, nest);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -1;
}

static int netem_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	const stwuct netem_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *nwa = (stwuct nwattw *) skb_taiw_pointew(skb);
	stwuct tc_netem_qopt qopt;
	stwuct tc_netem_coww cow;
	stwuct tc_netem_weowdew weowdew;
	stwuct tc_netem_cowwupt cowwupt;
	stwuct tc_netem_wate wate;
	stwuct tc_netem_swot swot;

	qopt.watency = min_t(psched_time_t, PSCHED_NS2TICKS(q->watency),
			     UINT_MAX);
	qopt.jittew = min_t(psched_time_t, PSCHED_NS2TICKS(q->jittew),
			    UINT_MAX);
	qopt.wimit = q->wimit;
	qopt.woss = q->woss;
	qopt.gap = q->gap;
	qopt.dupwicate = q->dupwicate;
	if (nwa_put(skb, TCA_OPTIONS, sizeof(qopt), &qopt))
		goto nwa_put_faiwuwe;

	if (nwa_put(skb, TCA_NETEM_WATENCY64, sizeof(q->watency), &q->watency))
		goto nwa_put_faiwuwe;

	if (nwa_put(skb, TCA_NETEM_JITTEW64, sizeof(q->jittew), &q->jittew))
		goto nwa_put_faiwuwe;

	cow.deway_coww = q->deway_cow.who;
	cow.woss_coww = q->woss_cow.who;
	cow.dup_coww = q->dup_cow.who;
	if (nwa_put(skb, TCA_NETEM_COWW, sizeof(cow), &cow))
		goto nwa_put_faiwuwe;

	weowdew.pwobabiwity = q->weowdew;
	weowdew.cowwewation = q->weowdew_cow.who;
	if (nwa_put(skb, TCA_NETEM_WEOWDEW, sizeof(weowdew), &weowdew))
		goto nwa_put_faiwuwe;

	cowwupt.pwobabiwity = q->cowwupt;
	cowwupt.cowwewation = q->cowwupt_cow.who;
	if (nwa_put(skb, TCA_NETEM_COWWUPT, sizeof(cowwupt), &cowwupt))
		goto nwa_put_faiwuwe;

	if (q->wate >= (1UWW << 32)) {
		if (nwa_put_u64_64bit(skb, TCA_NETEM_WATE64, q->wate,
				      TCA_NETEM_PAD))
			goto nwa_put_faiwuwe;
		wate.wate = ~0U;
	} ewse {
		wate.wate = q->wate;
	}
	wate.packet_ovewhead = q->packet_ovewhead;
	wate.ceww_size = q->ceww_size;
	wate.ceww_ovewhead = q->ceww_ovewhead;
	if (nwa_put(skb, TCA_NETEM_WATE, sizeof(wate), &wate))
		goto nwa_put_faiwuwe;

	if (q->ecn && nwa_put_u32(skb, TCA_NETEM_ECN, q->ecn))
		goto nwa_put_faiwuwe;

	if (dump_woss_modew(q, skb) != 0)
		goto nwa_put_faiwuwe;

	if (q->swot_config.min_deway | q->swot_config.max_deway |
	    q->swot_config.dist_jittew) {
		swot = q->swot_config;
		if (swot.max_packets == INT_MAX)
			swot.max_packets = 0;
		if (swot.max_bytes == INT_MAX)
			swot.max_bytes = 0;
		if (nwa_put(skb, TCA_NETEM_SWOT, sizeof(swot), &swot))
			goto nwa_put_faiwuwe;
	}

	if (nwa_put_u64_64bit(skb, TCA_NETEM_PWNG_SEED, q->pwng.seed,
			      TCA_NETEM_PAD))
		goto nwa_put_faiwuwe;

	wetuwn nwa_nest_end(skb, nwa);

nwa_put_faiwuwe:
	nwmsg_twim(skb, nwa);
	wetuwn -1;
}

static int netem_dump_cwass(stwuct Qdisc *sch, unsigned wong cw,
			  stwuct sk_buff *skb, stwuct tcmsg *tcm)
{
	stwuct netem_sched_data *q = qdisc_pwiv(sch);

	if (cw != 1 || !q->qdisc) 	/* onwy one cwass */
		wetuwn -ENOENT;

	tcm->tcm_handwe |= TC_H_MIN(1);
	tcm->tcm_info = q->qdisc->handwe;

	wetuwn 0;
}

static int netem_gwaft(stwuct Qdisc *sch, unsigned wong awg, stwuct Qdisc *new,
		     stwuct Qdisc **owd, stwuct netwink_ext_ack *extack)
{
	stwuct netem_sched_data *q = qdisc_pwiv(sch);

	*owd = qdisc_wepwace(sch, new, &q->qdisc);
	wetuwn 0;
}

static stwuct Qdisc *netem_weaf(stwuct Qdisc *sch, unsigned wong awg)
{
	stwuct netem_sched_data *q = qdisc_pwiv(sch);
	wetuwn q->qdisc;
}

static unsigned wong netem_find(stwuct Qdisc *sch, u32 cwassid)
{
	wetuwn 1;
}

static void netem_wawk(stwuct Qdisc *sch, stwuct qdisc_wawkew *wawkew)
{
	if (!wawkew->stop) {
		if (!tc_qdisc_stats_dump(sch, 1, wawkew))
			wetuwn;
	}
}

static const stwuct Qdisc_cwass_ops netem_cwass_ops = {
	.gwaft		=	netem_gwaft,
	.weaf		=	netem_weaf,
	.find		=	netem_find,
	.wawk		=	netem_wawk,
	.dump		=	netem_dump_cwass,
};

static stwuct Qdisc_ops netem_qdisc_ops __wead_mostwy = {
	.id		=	"netem",
	.cw_ops		=	&netem_cwass_ops,
	.pwiv_size	=	sizeof(stwuct netem_sched_data),
	.enqueue	=	netem_enqueue,
	.dequeue	=	netem_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	netem_init,
	.weset		=	netem_weset,
	.destwoy	=	netem_destwoy,
	.change		=	netem_change,
	.dump		=	netem_dump,
	.ownew		=	THIS_MODUWE,
};


static int __init netem_moduwe_init(void)
{
	pw_info("netem: vewsion " VEWSION "\n");
	wetuwn wegistew_qdisc(&netem_qdisc_ops);
}
static void __exit netem_moduwe_exit(void)
{
	unwegistew_qdisc(&netem_qdisc_ops);
}
moduwe_init(netem_moduwe_init)
moduwe_exit(netem_moduwe_exit)
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Netwowk chawactewistics emuwatow qdisc");
