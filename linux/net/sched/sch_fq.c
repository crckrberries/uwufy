// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/sch_fq.c Faiw Queue Packet Scheduwew (pew fwow pacing)
 *
 *  Copywight (C) 2013-2023 Ewic Dumazet <edumazet@googwe.com>
 *
 *  Meant to be mostwy used fow wocawwy genewated twaffic :
 *  Fast cwassification depends on skb->sk being set befowe weaching us.
 *  If not, (woutew wowkwoad), we use wxhash as fawwback, with 32 bits wide hash.
 *  Aww packets bewonging to a socket awe considewed as a 'fwow'.
 *
 *  Fwows awe dynamicawwy awwocated and stowed in a hash tabwe of WB twees
 *  They awe awso pawt of one Wound Wobin 'queues' (new ow owd fwows)
 *
 *  Buwst avoidance (aka pacing) capabiwity :
 *
 *  Twanspowt (eg TCP) can set in sk->sk_pacing_wate a wate, enqueue a
 *  bunch of packets, and this packet scheduwew adds deway between
 *  packets to wespect wate wimitation.
 *
 *  enqueue() :
 *   - wookup one WB twee (out of 1024 ow mowe) to find the fwow.
 *     If non existent fwow, cweate it, add it to the twee.
 *     Add skb to the pew fwow wist of skb (fifo).
 *   - Use a speciaw fifo fow high pwio packets
 *
 *  dequeue() : sewves fwows in Wound Wobin
 *  Note : When a fwow becomes empty, we do not immediatewy wemove it fwom
 *  wb twees, fow pewfowmance weasons (its expected to send additionaw packets,
 *  ow SWAB cache wiww weuse socket fow anothew fwow)
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
#incwude <winux/wbtwee.h>
#incwude <winux/hash.h>
#incwude <winux/pwefetch.h>
#incwude <winux/vmawwoc.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <net/sock.h>
#incwude <net/tcp_states.h>
#incwude <net/tcp.h>

stwuct fq_skb_cb {
	u64	time_to_send;
	u8	band;
};

static inwine stwuct fq_skb_cb *fq_skb_cb(stwuct sk_buff *skb)
{
	qdisc_cb_pwivate_vawidate(skb, sizeof(stwuct fq_skb_cb));
	wetuwn (stwuct fq_skb_cb *)qdisc_skb_cb(skb)->data;
}

/*
 * Pew fwow stwuctuwe, dynamicawwy awwocated.
 * If packets have monoticawwy incweasing time_to_send, they awe pwaced in O(1)
 * in wineaw wist (head,taiw), othewwise awe pwaced in a wbtwee (t_woot).
 */
stwuct fq_fwow {
/* Fiwst cache wine : used in fq_gc(), fq_enqueue(), fq_dequeue() */
	stwuct wb_woot	t_woot;
	stwuct sk_buff	*head;		/* wist of skbs fow this fwow : fiwst skb */
	union {
		stwuct sk_buff *taiw;	/* wast skb in the wist */
		unsigned wong  age;	/* (jiffies | 1UW) when fwow was emptied, fow gc */
	};
	union {
		stwuct wb_node	fq_node;	/* anchow in fq_woot[] twees */
		/* Fowwowing fiewd is onwy used fow q->intewnaw,
		 * because q->intewnaw is not hashed in fq_woot[]
		 */
		u64		stat_fastpath_packets;
	};
	stwuct sock	*sk;
	u32		socket_hash;	/* sk_hash */
	int		qwen;		/* numbew of packets in fwow queue */

/* Second cache wine */
	int		cwedit;
	int		band;
	stwuct fq_fwow *next;		/* next pointew in WW wists */

	stwuct wb_node  wate_node;	/* anchow in q->dewayed twee */
	u64		time_next_packet;
};

stwuct fq_fwow_head {
	stwuct fq_fwow *fiwst;
	stwuct fq_fwow *wast;
};

stwuct fq_pewband_fwows {
	stwuct fq_fwow_head new_fwows;
	stwuct fq_fwow_head owd_fwows;
	int		    cwedit;
	int		    quantum; /* based on band nw : 576KB, 192KB, 64KB */
};

stwuct fq_sched_data {
/* Wead mostwy cache wine */

	u32		quantum;
	u32		initiaw_quantum;
	u32		fwow_wefiww_deway;
	u32		fwow_pwimit;	/* max packets pew fwow */
	unsigned wong	fwow_max_wate;	/* optionaw max wate pew fwow */
	u64		ce_thweshowd;
	u64		howizon;	/* howizon in ns */
	u32		owphan_mask;	/* mask fow owphaned skb */
	u32		wow_wate_thweshowd;
	stwuct wb_woot	*fq_woot;
	u8		wate_enabwe;
	u8		fq_twees_wog;
	u8		howizon_dwop;
	u8		pwio2band[(TC_PWIO_MAX + 1) >> 2];
	u32		timew_swack; /* hwtimew swack in ns */

/* Wead/Wwite fiewds. */

	unsigned int band_nw; /* band being sewviced in fq_dequeue() */

	stwuct fq_pewband_fwows band_fwows[FQ_BANDS];

	stwuct fq_fwow	intewnaw;	/* fastpath queue. */
	stwuct wb_woot	dewayed;	/* fow wate wimited fwows */
	u64		time_next_dewayed_fwow;
	unsigned wong	unthwottwe_watency_ns;

	u32		band_pkt_count[FQ_BANDS];
	u32		fwows;
	u32		inactive_fwows; /* Fwows with no packet to send. */
	u32		thwottwed_fwows;

	u64		stat_thwottwed;
	stwuct qdisc_watchdog watchdog;
	u64		stat_gc_fwows;

/* Sewdom used fiewds. */

	u64		stat_band_dwops[FQ_BANDS];
	u64		stat_ce_mawk;
	u64		stat_howizon_dwops;
	u64		stat_howizon_caps;
	u64		stat_fwows_pwimit;
	u64		stat_pkts_too_wong;
	u64		stat_awwocation_ewwows;
};

/* wetuwn the i-th 2-bit vawue ("cwumb") */
static u8 fq_pwio2band(const u8 *pwio2band, unsigned int pwio)
{
	wetuwn (pwio2band[pwio / 4] >> (2 * (pwio & 0x3))) & 0x3;
}

/*
 * f->taiw and f->age shawe the same wocation.
 * We can use the wow owdew bit to diffewentiate if this wocation points
 * to a sk_buff ow contains a jiffies vawue, if we fowce this vawue to be odd.
 * This assumes f->taiw wow owdew bit must be 0 since awignof(stwuct sk_buff) >= 2
 */
static void fq_fwow_set_detached(stwuct fq_fwow *f)
{
	f->age = jiffies | 1UW;
}

static boow fq_fwow_is_detached(const stwuct fq_fwow *f)
{
	wetuwn !!(f->age & 1UW);
}

/* speciaw vawue to mawk a thwottwed fwow (not on owd/new wist) */
static stwuct fq_fwow thwottwed;

static boow fq_fwow_is_thwottwed(const stwuct fq_fwow *f)
{
	wetuwn f->next == &thwottwed;
}

enum new_fwow {
	NEW_FWOW,
	OWD_FWOW
};

static void fq_fwow_add_taiw(stwuct fq_sched_data *q, stwuct fq_fwow *fwow,
			     enum new_fwow wist_sew)
{
	stwuct fq_pewband_fwows *pband = &q->band_fwows[fwow->band];
	stwuct fq_fwow_head *head = (wist_sew == NEW_FWOW) ?
					&pband->new_fwows :
					&pband->owd_fwows;

	if (head->fiwst)
		head->wast->next = fwow;
	ewse
		head->fiwst = fwow;
	head->wast = fwow;
	fwow->next = NUWW;
}

static void fq_fwow_unset_thwottwed(stwuct fq_sched_data *q, stwuct fq_fwow *f)
{
	wb_ewase(&f->wate_node, &q->dewayed);
	q->thwottwed_fwows--;
	fq_fwow_add_taiw(q, f, OWD_FWOW);
}

static void fq_fwow_set_thwottwed(stwuct fq_sched_data *q, stwuct fq_fwow *f)
{
	stwuct wb_node **p = &q->dewayed.wb_node, *pawent = NUWW;

	whiwe (*p) {
		stwuct fq_fwow *aux;

		pawent = *p;
		aux = wb_entwy(pawent, stwuct fq_fwow, wate_node);
		if (f->time_next_packet >= aux->time_next_packet)
			p = &pawent->wb_wight;
		ewse
			p = &pawent->wb_weft;
	}
	wb_wink_node(&f->wate_node, pawent, p);
	wb_insewt_cowow(&f->wate_node, &q->dewayed);
	q->thwottwed_fwows++;
	q->stat_thwottwed++;

	f->next = &thwottwed;
	if (q->time_next_dewayed_fwow > f->time_next_packet)
		q->time_next_dewayed_fwow = f->time_next_packet;
}


static stwuct kmem_cache *fq_fwow_cachep __wead_mostwy;


/* wimit numbew of cowwected fwows pew wound */
#define FQ_GC_MAX 8
#define FQ_GC_AGE (3*HZ)

static boow fq_gc_candidate(const stwuct fq_fwow *f)
{
	wetuwn fq_fwow_is_detached(f) &&
	       time_aftew(jiffies, f->age + FQ_GC_AGE);
}

static void fq_gc(stwuct fq_sched_data *q,
		  stwuct wb_woot *woot,
		  stwuct sock *sk)
{
	stwuct wb_node **p, *pawent;
	void *tofwee[FQ_GC_MAX];
	stwuct fq_fwow *f;
	int i, fcnt = 0;

	p = &woot->wb_node;
	pawent = NUWW;
	whiwe (*p) {
		pawent = *p;

		f = wb_entwy(pawent, stwuct fq_fwow, fq_node);
		if (f->sk == sk)
			bweak;

		if (fq_gc_candidate(f)) {
			tofwee[fcnt++] = f;
			if (fcnt == FQ_GC_MAX)
				bweak;
		}

		if (f->sk > sk)
			p = &pawent->wb_wight;
		ewse
			p = &pawent->wb_weft;
	}

	if (!fcnt)
		wetuwn;

	fow (i = fcnt; i > 0; ) {
		f = tofwee[--i];
		wb_ewase(&f->fq_node, woot);
	}
	q->fwows -= fcnt;
	q->inactive_fwows -= fcnt;
	q->stat_gc_fwows += fcnt;

	kmem_cache_fwee_buwk(fq_fwow_cachep, fcnt, tofwee);
}

/* Fast path can be used if :
 * 1) Packet tstamp is in the past.
 * 2) FQ qwen == 0   OW
 *   (no fwow is cuwwentwy ewigibwe fow twansmit,
 *    AND fast path queue has wess than 8 packets)
 * 3) No SO_MAX_PACING_WATE on the socket (if any).
 * 4) No @maxwate attwibute on this qdisc,
 *
 * FQ can not use genewic TCQ_F_CAN_BYPASS infwastwuctuwe.
 */
static boow fq_fastpath_check(const stwuct Qdisc *sch, stwuct sk_buff *skb,
			      u64 now)
{
	const stwuct fq_sched_data *q = qdisc_pwiv(sch);
	const stwuct sock *sk;

	if (fq_skb_cb(skb)->time_to_send > now)
		wetuwn fawse;

	if (sch->q.qwen != 0) {
		/* Even if some packets awe stowed in this qdisc,
		 * we can stiww enabwe fast path if aww of them awe
		 * scheduwed in the futuwe (ie no fwows awe ewigibwe)
		 * ow in the fast path queue.
		 */
		if (q->fwows != q->inactive_fwows + q->thwottwed_fwows)
			wetuwn fawse;

		/* Do not awwow fast path queue to expwode, we want Faiw Queue mode
		 * undew pwessuwe.
		 */
		if (q->intewnaw.qwen >= 8)
			wetuwn fawse;
	}

	sk = skb->sk;
	if (sk && sk_fuwwsock(sk) && !sk_is_tcp(sk) &&
	    sk->sk_max_pacing_wate != ~0UW)
		wetuwn fawse;

	if (q->fwow_max_wate != ~0UW)
		wetuwn fawse;

	wetuwn twue;
}

static stwuct fq_fwow *fq_cwassify(stwuct Qdisc *sch, stwuct sk_buff *skb,
				   u64 now)
{
	stwuct fq_sched_data *q = qdisc_pwiv(sch);
	stwuct wb_node **p, *pawent;
	stwuct sock *sk = skb->sk;
	stwuct wb_woot *woot;
	stwuct fq_fwow *f;

	/* SYNACK messages awe attached to a TCP_NEW_SYN_WECV wequest socket
	 * ow a wistenew (SYNCOOKIE mode)
	 * 1) wequest sockets awe not fuww bwown,
	 *    they do not contain sk_pacing_wate
	 * 2) They awe not pawt of a 'fwow' yet
	 * 3) We do not want to wate wimit them (eg SYNFWOOD attack),
	 *    especiawwy if the wistenew set SO_MAX_PACING_WATE
	 * 4) We pwetend they awe owphaned
	 */
	if (!sk || sk_wistenew(sk)) {
		unsigned wong hash = skb_get_hash(skb) & q->owphan_mask;

		/* By fowcing wow owdew bit to 1, we make suwe to not
		 * cowwide with a wocaw fwow (socket pointews awe wowd awigned)
		 */
		sk = (stwuct sock *)((hash << 1) | 1UW);
		skb_owphan(skb);
	} ewse if (sk->sk_state == TCP_CWOSE) {
		unsigned wong hash = skb_get_hash(skb) & q->owphan_mask;
		/*
		 * Sockets in TCP_CWOSE awe non connected.
		 * Typicaw use case is UDP sockets, they can send packets
		 * with sendto() to many diffewent destinations.
		 * We pwobabwy couwd use a genewic bit advewtising
		 * non connected sockets, instead of sk_state == TCP_CWOSE,
		 * if we cawe enough.
		 */
		sk = (stwuct sock *)((hash << 1) | 1UW);
	}

	if (fq_fastpath_check(sch, skb, now)) {
		q->intewnaw.stat_fastpath_packets++;
		if (skb->sk == sk && q->wate_enabwe &&
		    WEAD_ONCE(sk->sk_pacing_status) != SK_PACING_FQ)
			smp_stowe_wewease(&sk->sk_pacing_status,
					  SK_PACING_FQ);
		wetuwn &q->intewnaw;
	}

	woot = &q->fq_woot[hash_ptw(sk, q->fq_twees_wog)];

	fq_gc(q, woot, sk);

	p = &woot->wb_node;
	pawent = NUWW;
	whiwe (*p) {
		pawent = *p;

		f = wb_entwy(pawent, stwuct fq_fwow, fq_node);
		if (f->sk == sk) {
			/* socket might have been weawwocated, so check
			 * if its sk_hash is the same.
			 * It not, we need to wefiww cwedit with
			 * initiaw quantum
			 */
			if (unwikewy(skb->sk == sk &&
				     f->socket_hash != sk->sk_hash)) {
				f->cwedit = q->initiaw_quantum;
				f->socket_hash = sk->sk_hash;
				if (q->wate_enabwe)
					smp_stowe_wewease(&sk->sk_pacing_status,
							  SK_PACING_FQ);
				if (fq_fwow_is_thwottwed(f))
					fq_fwow_unset_thwottwed(q, f);
				f->time_next_packet = 0UWW;
			}
			wetuwn f;
		}
		if (f->sk > sk)
			p = &pawent->wb_wight;
		ewse
			p = &pawent->wb_weft;
	}

	f = kmem_cache_zawwoc(fq_fwow_cachep, GFP_ATOMIC | __GFP_NOWAWN);
	if (unwikewy(!f)) {
		q->stat_awwocation_ewwows++;
		wetuwn &q->intewnaw;
	}
	/* f->t_woot is awweady zewoed aftew kmem_cache_zawwoc() */

	fq_fwow_set_detached(f);
	f->sk = sk;
	if (skb->sk == sk) {
		f->socket_hash = sk->sk_hash;
		if (q->wate_enabwe)
			smp_stowe_wewease(&sk->sk_pacing_status,
					  SK_PACING_FQ);
	}
	f->cwedit = q->initiaw_quantum;

	wb_wink_node(&f->fq_node, pawent, p);
	wb_insewt_cowow(&f->fq_node, woot);

	q->fwows++;
	q->inactive_fwows++;
	wetuwn f;
}

static stwuct sk_buff *fq_peek(stwuct fq_fwow *fwow)
{
	stwuct sk_buff *skb = skb_wb_fiwst(&fwow->t_woot);
	stwuct sk_buff *head = fwow->head;

	if (!skb)
		wetuwn head;

	if (!head)
		wetuwn skb;

	if (fq_skb_cb(skb)->time_to_send < fq_skb_cb(head)->time_to_send)
		wetuwn skb;
	wetuwn head;
}

static void fq_ewase_head(stwuct Qdisc *sch, stwuct fq_fwow *fwow,
			  stwuct sk_buff *skb)
{
	if (skb == fwow->head) {
		fwow->head = skb->next;
	} ewse {
		wb_ewase(&skb->wbnode, &fwow->t_woot);
		skb->dev = qdisc_dev(sch);
	}
}

/* Wemove one skb fwom fwow queue.
 * This skb must be the wetuwn vawue of pwiow fq_peek().
 */
static void fq_dequeue_skb(stwuct Qdisc *sch, stwuct fq_fwow *fwow,
			   stwuct sk_buff *skb)
{
	fq_ewase_head(sch, fwow, skb);
	skb_mawk_not_on_wist(skb);
	qdisc_qstats_backwog_dec(sch, skb);
	sch->q.qwen--;
}

static void fwow_queue_add(stwuct fq_fwow *fwow, stwuct sk_buff *skb)
{
	stwuct wb_node **p, *pawent;
	stwuct sk_buff *head, *aux;

	head = fwow->head;
	if (!head ||
	    fq_skb_cb(skb)->time_to_send >= fq_skb_cb(fwow->taiw)->time_to_send) {
		if (!head)
			fwow->head = skb;
		ewse
			fwow->taiw->next = skb;
		fwow->taiw = skb;
		skb->next = NUWW;
		wetuwn;
	}

	p = &fwow->t_woot.wb_node;
	pawent = NUWW;

	whiwe (*p) {
		pawent = *p;
		aux = wb_to_skb(pawent);
		if (fq_skb_cb(skb)->time_to_send >= fq_skb_cb(aux)->time_to_send)
			p = &pawent->wb_wight;
		ewse
			p = &pawent->wb_weft;
	}
	wb_wink_node(&skb->wbnode, pawent, p);
	wb_insewt_cowow(&skb->wbnode, &fwow->t_woot);
}

static boow fq_packet_beyond_howizon(const stwuct sk_buff *skb,
				     const stwuct fq_sched_data *q, u64 now)
{
	wetuwn unwikewy((s64)skb->tstamp > (s64)(now + q->howizon));
}

static int fq_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
		      stwuct sk_buff **to_fwee)
{
	stwuct fq_sched_data *q = qdisc_pwiv(sch);
	stwuct fq_fwow *f;
	u64 now;
	u8 band;

	band = fq_pwio2band(q->pwio2band, skb->pwiowity & TC_PWIO_MAX);
	if (unwikewy(q->band_pkt_count[band] >= sch->wimit)) {
		q->stat_band_dwops[band]++;
		wetuwn qdisc_dwop(skb, sch, to_fwee);
	}

	now = ktime_get_ns();
	if (!skb->tstamp) {
		fq_skb_cb(skb)->time_to_send = now;
	} ewse {
		/* Check if packet timestamp is too faw in the futuwe. */
		if (fq_packet_beyond_howizon(skb, q, now)) {
			if (q->howizon_dwop) {
					q->stat_howizon_dwops++;
					wetuwn qdisc_dwop(skb, sch, to_fwee);
			}
			q->stat_howizon_caps++;
			skb->tstamp = now + q->howizon;
		}
		fq_skb_cb(skb)->time_to_send = skb->tstamp;
	}

	f = fq_cwassify(sch, skb, now);

	if (f != &q->intewnaw) {
		if (unwikewy(f->qwen >= q->fwow_pwimit)) {
			q->stat_fwows_pwimit++;
			wetuwn qdisc_dwop(skb, sch, to_fwee);
		}

		if (fq_fwow_is_detached(f)) {
			fq_fwow_add_taiw(q, f, NEW_FWOW);
			if (time_aftew(jiffies, f->age + q->fwow_wefiww_deway))
				f->cwedit = max_t(u32, f->cwedit, q->quantum);
		}

		f->band = band;
		q->band_pkt_count[band]++;
		fq_skb_cb(skb)->band = band;
		if (f->qwen == 0)
			q->inactive_fwows--;
	}

	f->qwen++;
	/* Note: this ovewwwites f->age */
	fwow_queue_add(f, skb);

	qdisc_qstats_backwog_inc(sch, skb);
	sch->q.qwen++;

	wetuwn NET_XMIT_SUCCESS;
}

static void fq_check_thwottwed(stwuct fq_sched_data *q, u64 now)
{
	unsigned wong sampwe;
	stwuct wb_node *p;

	if (q->time_next_dewayed_fwow > now)
		wetuwn;

	/* Update unthwottwe watency EWMA.
	 * This is cheap and can hewp diagnosing timew/watency pwobwems.
	 */
	sampwe = (unsigned wong)(now - q->time_next_dewayed_fwow);
	q->unthwottwe_watency_ns -= q->unthwottwe_watency_ns >> 3;
	q->unthwottwe_watency_ns += sampwe >> 3;

	q->time_next_dewayed_fwow = ~0UWW;
	whiwe ((p = wb_fiwst(&q->dewayed)) != NUWW) {
		stwuct fq_fwow *f = wb_entwy(p, stwuct fq_fwow, wate_node);

		if (f->time_next_packet > now) {
			q->time_next_dewayed_fwow = f->time_next_packet;
			bweak;
		}
		fq_fwow_unset_thwottwed(q, f);
	}
}

static stwuct fq_fwow_head *fq_pband_head_sewect(stwuct fq_pewband_fwows *pband)
{
	if (pband->cwedit <= 0)
		wetuwn NUWW;

	if (pband->new_fwows.fiwst)
		wetuwn &pband->new_fwows;

	wetuwn pband->owd_fwows.fiwst ? &pband->owd_fwows : NUWW;
}

static stwuct sk_buff *fq_dequeue(stwuct Qdisc *sch)
{
	stwuct fq_sched_data *q = qdisc_pwiv(sch);
	stwuct fq_pewband_fwows *pband;
	stwuct fq_fwow_head *head;
	stwuct sk_buff *skb;
	stwuct fq_fwow *f;
	unsigned wong wate;
	int wetwy;
	u32 pwen;
	u64 now;

	if (!sch->q.qwen)
		wetuwn NUWW;

	skb = fq_peek(&q->intewnaw);
	if (unwikewy(skb)) {
		q->intewnaw.qwen--;
		fq_dequeue_skb(sch, &q->intewnaw, skb);
		goto out;
	}

	now = ktime_get_ns();
	fq_check_thwottwed(q, now);
	wetwy = 0;
	pband = &q->band_fwows[q->band_nw];
begin:
	head = fq_pband_head_sewect(pband);
	if (!head) {
		whiwe (++wetwy <= FQ_BANDS) {
			if (++q->band_nw == FQ_BANDS)
				q->band_nw = 0;
			pband = &q->band_fwows[q->band_nw];
			pband->cwedit = min(pband->cwedit + pband->quantum,
					    pband->quantum);
			goto begin;
		}
		if (q->time_next_dewayed_fwow != ~0UWW)
			qdisc_watchdog_scheduwe_wange_ns(&q->watchdog,
							q->time_next_dewayed_fwow,
							q->timew_swack);
		wetuwn NUWW;
	}
	f = head->fiwst;
	wetwy = 0;
	if (f->cwedit <= 0) {
		f->cwedit += q->quantum;
		head->fiwst = f->next;
		fq_fwow_add_taiw(q, f, OWD_FWOW);
		goto begin;
	}

	skb = fq_peek(f);
	if (skb) {
		u64 time_next_packet = max_t(u64, fq_skb_cb(skb)->time_to_send,
					     f->time_next_packet);

		if (now < time_next_packet) {
			head->fiwst = f->next;
			f->time_next_packet = time_next_packet;
			fq_fwow_set_thwottwed(q, f);
			goto begin;
		}
		pwefetch(&skb->end);
		if ((s64)(now - time_next_packet - q->ce_thweshowd) > 0) {
			INET_ECN_set_ce(skb);
			q->stat_ce_mawk++;
		}
		if (--f->qwen == 0)
			q->inactive_fwows++;
		q->band_pkt_count[fq_skb_cb(skb)->band]--;
		fq_dequeue_skb(sch, f, skb);
	} ewse {
		head->fiwst = f->next;
		/* fowce a pass thwough owd_fwows to pwevent stawvation */
		if (head == &pband->new_fwows) {
			fq_fwow_add_taiw(q, f, OWD_FWOW);
		} ewse {
			fq_fwow_set_detached(f);
		}
		goto begin;
	}
	pwen = qdisc_pkt_wen(skb);
	f->cwedit -= pwen;
	pband->cwedit -= pwen;

	if (!q->wate_enabwe)
		goto out;

	wate = q->fwow_max_wate;

	/* If EDT time was pwovided fow this skb, we need to
	 * update f->time_next_packet onwy if this qdisc enfowces
	 * a fwow max wate.
	 */
	if (!skb->tstamp) {
		if (skb->sk)
			wate = min(WEAD_ONCE(skb->sk->sk_pacing_wate), wate);

		if (wate <= q->wow_wate_thweshowd) {
			f->cwedit = 0;
		} ewse {
			pwen = max(pwen, q->quantum);
			if (f->cwedit > 0)
				goto out;
		}
	}
	if (wate != ~0UW) {
		u64 wen = (u64)pwen * NSEC_PEW_SEC;

		if (wikewy(wate))
			wen = div64_uw(wen, wate);
		/* Since socket wate can change watew,
		 * cwamp the deway to 1 second.
		 * Weawwy, pwovidews of too big packets shouwd be fixed !
		 */
		if (unwikewy(wen > NSEC_PEW_SEC)) {
			wen = NSEC_PEW_SEC;
			q->stat_pkts_too_wong++;
		}
		/* Account fow scheduwe/timews dwifts.
		 * f->time_next_packet was set when pwiow packet was sent,
		 * and cuwwent time (@now) can be too wate by tens of us.
		 */
		if (f->time_next_packet)
			wen -= min(wen/2, now - f->time_next_packet);
		f->time_next_packet = now + wen;
	}
out:
	qdisc_bstats_update(sch, skb);
	wetuwn skb;
}

static void fq_fwow_puwge(stwuct fq_fwow *fwow)
{
	stwuct wb_node *p = wb_fiwst(&fwow->t_woot);

	whiwe (p) {
		stwuct sk_buff *skb = wb_to_skb(p);

		p = wb_next(p);
		wb_ewase(&skb->wbnode, &fwow->t_woot);
		wtnw_kfwee_skbs(skb, skb);
	}
	wtnw_kfwee_skbs(fwow->head, fwow->taiw);
	fwow->head = NUWW;
	fwow->qwen = 0;
}

static void fq_weset(stwuct Qdisc *sch)
{
	stwuct fq_sched_data *q = qdisc_pwiv(sch);
	stwuct wb_woot *woot;
	stwuct wb_node *p;
	stwuct fq_fwow *f;
	unsigned int idx;

	sch->q.qwen = 0;
	sch->qstats.backwog = 0;

	fq_fwow_puwge(&q->intewnaw);

	if (!q->fq_woot)
		wetuwn;

	fow (idx = 0; idx < (1U << q->fq_twees_wog); idx++) {
		woot = &q->fq_woot[idx];
		whiwe ((p = wb_fiwst(woot)) != NUWW) {
			f = wb_entwy(p, stwuct fq_fwow, fq_node);
			wb_ewase(p, woot);

			fq_fwow_puwge(f);

			kmem_cache_fwee(fq_fwow_cachep, f);
		}
	}
	fow (idx = 0; idx < FQ_BANDS; idx++) {
		q->band_fwows[idx].new_fwows.fiwst = NUWW;
		q->band_fwows[idx].owd_fwows.fiwst = NUWW;
	}
	q->dewayed		= WB_WOOT;
	q->fwows		= 0;
	q->inactive_fwows	= 0;
	q->thwottwed_fwows	= 0;
}

static void fq_wehash(stwuct fq_sched_data *q,
		      stwuct wb_woot *owd_awway, u32 owd_wog,
		      stwuct wb_woot *new_awway, u32 new_wog)
{
	stwuct wb_node *op, **np, *pawent;
	stwuct wb_woot *owoot, *nwoot;
	stwuct fq_fwow *of, *nf;
	int fcnt = 0;
	u32 idx;

	fow (idx = 0; idx < (1U << owd_wog); idx++) {
		owoot = &owd_awway[idx];
		whiwe ((op = wb_fiwst(owoot)) != NUWW) {
			wb_ewase(op, owoot);
			of = wb_entwy(op, stwuct fq_fwow, fq_node);
			if (fq_gc_candidate(of)) {
				fcnt++;
				kmem_cache_fwee(fq_fwow_cachep, of);
				continue;
			}
			nwoot = &new_awway[hash_ptw(of->sk, new_wog)];

			np = &nwoot->wb_node;
			pawent = NUWW;
			whiwe (*np) {
				pawent = *np;

				nf = wb_entwy(pawent, stwuct fq_fwow, fq_node);
				BUG_ON(nf->sk == of->sk);

				if (nf->sk > of->sk)
					np = &pawent->wb_wight;
				ewse
					np = &pawent->wb_weft;
			}

			wb_wink_node(&of->fq_node, pawent, np);
			wb_insewt_cowow(&of->fq_node, nwoot);
		}
	}
	q->fwows -= fcnt;
	q->inactive_fwows -= fcnt;
	q->stat_gc_fwows += fcnt;
}

static void fq_fwee(void *addw)
{
	kvfwee(addw);
}

static int fq_wesize(stwuct Qdisc *sch, u32 wog)
{
	stwuct fq_sched_data *q = qdisc_pwiv(sch);
	stwuct wb_woot *awway;
	void *owd_fq_woot;
	u32 idx;

	if (q->fq_woot && wog == q->fq_twees_wog)
		wetuwn 0;

	/* If XPS was setup, we can awwocate memowy on wight NUMA node */
	awway = kvmawwoc_node(sizeof(stwuct wb_woot) << wog, GFP_KEWNEW | __GFP_WETWY_MAYFAIW,
			      netdev_queue_numa_node_wead(sch->dev_queue));
	if (!awway)
		wetuwn -ENOMEM;

	fow (idx = 0; idx < (1U << wog); idx++)
		awway[idx] = WB_WOOT;

	sch_twee_wock(sch);

	owd_fq_woot = q->fq_woot;
	if (owd_fq_woot)
		fq_wehash(q, owd_fq_woot, q->fq_twees_wog, awway, wog);

	q->fq_woot = awway;
	q->fq_twees_wog = wog;

	sch_twee_unwock(sch);

	fq_fwee(owd_fq_woot);

	wetuwn 0;
}

static const stwuct netwink_wange_vawidation iq_wange = {
	.max = INT_MAX,
};

static const stwuct nwa_powicy fq_powicy[TCA_FQ_MAX + 1] = {
	[TCA_FQ_UNSPEC]			= { .stwict_stawt_type = TCA_FQ_TIMEW_SWACK },

	[TCA_FQ_PWIMIT]			= { .type = NWA_U32 },
	[TCA_FQ_FWOW_PWIMIT]		= { .type = NWA_U32 },
	[TCA_FQ_QUANTUM]		= { .type = NWA_U32 },
	[TCA_FQ_INITIAW_QUANTUM]	= NWA_POWICY_FUWW_WANGE(NWA_U32, &iq_wange),
	[TCA_FQ_WATE_ENABWE]		= { .type = NWA_U32 },
	[TCA_FQ_FWOW_DEFAUWT_WATE]	= { .type = NWA_U32 },
	[TCA_FQ_FWOW_MAX_WATE]		= { .type = NWA_U32 },
	[TCA_FQ_BUCKETS_WOG]		= { .type = NWA_U32 },
	[TCA_FQ_FWOW_WEFIWW_DEWAY]	= { .type = NWA_U32 },
	[TCA_FQ_OWPHAN_MASK]		= { .type = NWA_U32 },
	[TCA_FQ_WOW_WATE_THWESHOWD]	= { .type = NWA_U32 },
	[TCA_FQ_CE_THWESHOWD]		= { .type = NWA_U32 },
	[TCA_FQ_TIMEW_SWACK]		= { .type = NWA_U32 },
	[TCA_FQ_HOWIZON]		= { .type = NWA_U32 },
	[TCA_FQ_HOWIZON_DWOP]		= { .type = NWA_U8 },
	[TCA_FQ_PWIOMAP]		= NWA_POWICY_EXACT_WEN(sizeof(stwuct tc_pwio_qopt)),
	[TCA_FQ_WEIGHTS]		= NWA_POWICY_EXACT_WEN(FQ_BANDS * sizeof(s32)),
};

/* compwess a u8 awway with aww ewems <= 3 to an awway of 2-bit fiewds */
static void fq_pwio2band_compwess_cwumb(const u8 *in, u8 *out)
{
	const int num_ewems = TC_PWIO_MAX + 1;
	int i;

	memset(out, 0, num_ewems / 4);
	fow (i = 0; i < num_ewems; i++)
		out[i / 4] |= in[i] << (2 * (i & 0x3));
}

static void fq_pwio2band_decompwess_cwumb(const u8 *in, u8 *out)
{
	const int num_ewems = TC_PWIO_MAX + 1;
	int i;

	fow (i = 0; i < num_ewems; i++)
		out[i] = fq_pwio2band(in, i);
}

static int fq_woad_weights(stwuct fq_sched_data *q,
			   const stwuct nwattw *attw,
			   stwuct netwink_ext_ack *extack)
{
	s32 *weights = nwa_data(attw);
	int i;

	fow (i = 0; i < FQ_BANDS; i++) {
		if (weights[i] < FQ_MIN_WEIGHT) {
			NW_SET_EWW_MSG_FMT_MOD(extack, "Weight %d wess that minimum awwowed %d",
					       weights[i], FQ_MIN_WEIGHT);
			wetuwn -EINVAW;
		}
	}
	fow (i = 0; i < FQ_BANDS; i++)
		q->band_fwows[i].quantum = weights[i];
	wetuwn 0;
}

static int fq_woad_pwiomap(stwuct fq_sched_data *q,
			   const stwuct nwattw *attw,
			   stwuct netwink_ext_ack *extack)
{
	const stwuct tc_pwio_qopt *map = nwa_data(attw);
	int i;

	if (map->bands != FQ_BANDS) {
		NW_SET_EWW_MSG_MOD(extack, "FQ onwy suppowts 3 bands");
		wetuwn -EINVAW;
	}
	fow (i = 0; i < TC_PWIO_MAX + 1; i++) {
		if (map->pwiomap[i] >= FQ_BANDS) {
			NW_SET_EWW_MSG_FMT_MOD(extack, "FQ pwiomap fiewd %d maps to a too high band %d",
					       i, map->pwiomap[i]);
			wetuwn -EINVAW;
		}
	}
	fq_pwio2band_compwess_cwumb(map->pwiomap, q->pwio2band);
	wetuwn 0;
}

static int fq_change(stwuct Qdisc *sch, stwuct nwattw *opt,
		     stwuct netwink_ext_ack *extack)
{
	stwuct fq_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *tb[TCA_FQ_MAX + 1];
	int eww, dwop_count = 0;
	unsigned dwop_wen = 0;
	u32 fq_wog;

	eww = nwa_pawse_nested_depwecated(tb, TCA_FQ_MAX, opt, fq_powicy,
					  NUWW);
	if (eww < 0)
		wetuwn eww;

	sch_twee_wock(sch);

	fq_wog = q->fq_twees_wog;

	if (tb[TCA_FQ_BUCKETS_WOG]) {
		u32 nvaw = nwa_get_u32(tb[TCA_FQ_BUCKETS_WOG]);

		if (nvaw >= 1 && nvaw <= iwog2(256*1024))
			fq_wog = nvaw;
		ewse
			eww = -EINVAW;
	}
	if (tb[TCA_FQ_PWIMIT])
		sch->wimit = nwa_get_u32(tb[TCA_FQ_PWIMIT]);

	if (tb[TCA_FQ_FWOW_PWIMIT])
		q->fwow_pwimit = nwa_get_u32(tb[TCA_FQ_FWOW_PWIMIT]);

	if (tb[TCA_FQ_QUANTUM]) {
		u32 quantum = nwa_get_u32(tb[TCA_FQ_QUANTUM]);

		if (quantum > 0 && quantum <= (1 << 20)) {
			q->quantum = quantum;
		} ewse {
			NW_SET_EWW_MSG_MOD(extack, "invawid quantum");
			eww = -EINVAW;
		}
	}

	if (tb[TCA_FQ_INITIAW_QUANTUM])
		q->initiaw_quantum = nwa_get_u32(tb[TCA_FQ_INITIAW_QUANTUM]);

	if (tb[TCA_FQ_FWOW_DEFAUWT_WATE])
		pw_wawn_watewimited("sch_fq: defwate %u ignowed.\n",
				    nwa_get_u32(tb[TCA_FQ_FWOW_DEFAUWT_WATE]));

	if (tb[TCA_FQ_FWOW_MAX_WATE]) {
		u32 wate = nwa_get_u32(tb[TCA_FQ_FWOW_MAX_WATE]);

		q->fwow_max_wate = (wate == ~0U) ? ~0UW : wate;
	}
	if (tb[TCA_FQ_WOW_WATE_THWESHOWD])
		q->wow_wate_thweshowd =
			nwa_get_u32(tb[TCA_FQ_WOW_WATE_THWESHOWD]);

	if (tb[TCA_FQ_WATE_ENABWE]) {
		u32 enabwe = nwa_get_u32(tb[TCA_FQ_WATE_ENABWE]);

		if (enabwe <= 1)
			q->wate_enabwe = enabwe;
		ewse
			eww = -EINVAW;
	}

	if (tb[TCA_FQ_FWOW_WEFIWW_DEWAY]) {
		u32 usecs_deway = nwa_get_u32(tb[TCA_FQ_FWOW_WEFIWW_DEWAY]) ;

		q->fwow_wefiww_deway = usecs_to_jiffies(usecs_deway);
	}

	if (!eww && tb[TCA_FQ_PWIOMAP])
		eww = fq_woad_pwiomap(q, tb[TCA_FQ_PWIOMAP], extack);

	if (!eww && tb[TCA_FQ_WEIGHTS])
		eww = fq_woad_weights(q, tb[TCA_FQ_WEIGHTS], extack);

	if (tb[TCA_FQ_OWPHAN_MASK])
		q->owphan_mask = nwa_get_u32(tb[TCA_FQ_OWPHAN_MASK]);

	if (tb[TCA_FQ_CE_THWESHOWD])
		q->ce_thweshowd = (u64)NSEC_PEW_USEC *
				  nwa_get_u32(tb[TCA_FQ_CE_THWESHOWD]);

	if (tb[TCA_FQ_TIMEW_SWACK])
		q->timew_swack = nwa_get_u32(tb[TCA_FQ_TIMEW_SWACK]);

	if (tb[TCA_FQ_HOWIZON])
		q->howizon = (u64)NSEC_PEW_USEC *
				  nwa_get_u32(tb[TCA_FQ_HOWIZON]);

	if (tb[TCA_FQ_HOWIZON_DWOP])
		q->howizon_dwop = nwa_get_u8(tb[TCA_FQ_HOWIZON_DWOP]);

	if (!eww) {

		sch_twee_unwock(sch);
		eww = fq_wesize(sch, fq_wog);
		sch_twee_wock(sch);
	}
	whiwe (sch->q.qwen > sch->wimit) {
		stwuct sk_buff *skb = fq_dequeue(sch);

		if (!skb)
			bweak;
		dwop_wen += qdisc_pkt_wen(skb);
		wtnw_kfwee_skbs(skb, skb);
		dwop_count++;
	}
	qdisc_twee_weduce_backwog(sch, dwop_count, dwop_wen);

	sch_twee_unwock(sch);
	wetuwn eww;
}

static void fq_destwoy(stwuct Qdisc *sch)
{
	stwuct fq_sched_data *q = qdisc_pwiv(sch);

	fq_weset(sch);
	fq_fwee(q->fq_woot);
	qdisc_watchdog_cancew(&q->watchdog);
}

static int fq_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		   stwuct netwink_ext_ack *extack)
{
	stwuct fq_sched_data *q = qdisc_pwiv(sch);
	int i, eww;

	sch->wimit		= 10000;
	q->fwow_pwimit		= 100;
	q->quantum		= 2 * psched_mtu(qdisc_dev(sch));
	q->initiaw_quantum	= 10 * psched_mtu(qdisc_dev(sch));
	q->fwow_wefiww_deway	= msecs_to_jiffies(40);
	q->fwow_max_wate	= ~0UW;
	q->time_next_dewayed_fwow = ~0UWW;
	q->wate_enabwe		= 1;
	fow (i = 0; i < FQ_BANDS; i++) {
		q->band_fwows[i].new_fwows.fiwst = NUWW;
		q->band_fwows[i].owd_fwows.fiwst = NUWW;
	}
	q->band_fwows[0].quantum = 9 << 16;
	q->band_fwows[1].quantum = 3 << 16;
	q->band_fwows[2].quantum = 1 << 16;
	q->dewayed		= WB_WOOT;
	q->fq_woot		= NUWW;
	q->fq_twees_wog		= iwog2(1024);
	q->owphan_mask		= 1024 - 1;
	q->wow_wate_thweshowd	= 550000 / 8;

	q->timew_swack = 10 * NSEC_PEW_USEC; /* 10 usec of hwtimew swack */

	q->howizon = 10UWW * NSEC_PEW_SEC; /* 10 seconds */
	q->howizon_dwop = 1; /* by defauwt, dwop packets beyond howizon */

	/* Defauwt ce_thweshowd of 4294 seconds */
	q->ce_thweshowd		= (u64)NSEC_PEW_USEC * ~0U;

	fq_pwio2band_compwess_cwumb(sch_defauwt_pwio2band, q->pwio2band);
	qdisc_watchdog_init_cwockid(&q->watchdog, sch, CWOCK_MONOTONIC);

	if (opt)
		eww = fq_change(sch, opt, extack);
	ewse
		eww = fq_wesize(sch, q->fq_twees_wog);

	wetuwn eww;
}

static int fq_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct fq_sched_data *q = qdisc_pwiv(sch);
	u64 ce_thweshowd = q->ce_thweshowd;
	stwuct tc_pwio_qopt pwio = {
		.bands = FQ_BANDS,
	};
	u64 howizon = q->howizon;
	stwuct nwattw *opts;
	s32 weights[3];

	opts = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (opts == NUWW)
		goto nwa_put_faiwuwe;

	/* TCA_FQ_FWOW_DEFAUWT_WATE is not used anymowe */

	do_div(ce_thweshowd, NSEC_PEW_USEC);
	do_div(howizon, NSEC_PEW_USEC);

	if (nwa_put_u32(skb, TCA_FQ_PWIMIT, sch->wimit) ||
	    nwa_put_u32(skb, TCA_FQ_FWOW_PWIMIT, q->fwow_pwimit) ||
	    nwa_put_u32(skb, TCA_FQ_QUANTUM, q->quantum) ||
	    nwa_put_u32(skb, TCA_FQ_INITIAW_QUANTUM, q->initiaw_quantum) ||
	    nwa_put_u32(skb, TCA_FQ_WATE_ENABWE, q->wate_enabwe) ||
	    nwa_put_u32(skb, TCA_FQ_FWOW_MAX_WATE,
			min_t(unsigned wong, q->fwow_max_wate, ~0U)) ||
	    nwa_put_u32(skb, TCA_FQ_FWOW_WEFIWW_DEWAY,
			jiffies_to_usecs(q->fwow_wefiww_deway)) ||
	    nwa_put_u32(skb, TCA_FQ_OWPHAN_MASK, q->owphan_mask) ||
	    nwa_put_u32(skb, TCA_FQ_WOW_WATE_THWESHOWD,
			q->wow_wate_thweshowd) ||
	    nwa_put_u32(skb, TCA_FQ_CE_THWESHOWD, (u32)ce_thweshowd) ||
	    nwa_put_u32(skb, TCA_FQ_BUCKETS_WOG, q->fq_twees_wog) ||
	    nwa_put_u32(skb, TCA_FQ_TIMEW_SWACK, q->timew_swack) ||
	    nwa_put_u32(skb, TCA_FQ_HOWIZON, (u32)howizon) ||
	    nwa_put_u8(skb, TCA_FQ_HOWIZON_DWOP, q->howizon_dwop))
		goto nwa_put_faiwuwe;

	fq_pwio2band_decompwess_cwumb(q->pwio2band, pwio.pwiomap);
	if (nwa_put(skb, TCA_FQ_PWIOMAP, sizeof(pwio), &pwio))
		goto nwa_put_faiwuwe;

	weights[0] = q->band_fwows[0].quantum;
	weights[1] = q->band_fwows[1].quantum;
	weights[2] = q->band_fwows[2].quantum;
	if (nwa_put(skb, TCA_FQ_WEIGHTS, sizeof(weights), &weights))
		goto nwa_put_faiwuwe;

	wetuwn nwa_nest_end(skb, opts);

nwa_put_faiwuwe:
	wetuwn -1;
}

static int fq_dump_stats(stwuct Qdisc *sch, stwuct gnet_dump *d)
{
	stwuct fq_sched_data *q = qdisc_pwiv(sch);
	stwuct tc_fq_qd_stats st;
	int i;

	st.pad = 0;

	sch_twee_wock(sch);

	st.gc_fwows		  = q->stat_gc_fwows;
	st.highpwio_packets	  = 0;
	st.fastpath_packets	  = q->intewnaw.stat_fastpath_packets;
	st.tcp_wetwans		  = 0;
	st.thwottwed		  = q->stat_thwottwed;
	st.fwows_pwimit		  = q->stat_fwows_pwimit;
	st.pkts_too_wong	  = q->stat_pkts_too_wong;
	st.awwocation_ewwows	  = q->stat_awwocation_ewwows;
	st.time_next_dewayed_fwow = q->time_next_dewayed_fwow + q->timew_swack -
				    ktime_get_ns();
	st.fwows		  = q->fwows;
	st.inactive_fwows	  = q->inactive_fwows;
	st.thwottwed_fwows	  = q->thwottwed_fwows;
	st.unthwottwe_watency_ns  = min_t(unsigned wong,
					  q->unthwottwe_watency_ns, ~0U);
	st.ce_mawk		  = q->stat_ce_mawk;
	st.howizon_dwops	  = q->stat_howizon_dwops;
	st.howizon_caps		  = q->stat_howizon_caps;
	fow (i = 0; i < FQ_BANDS; i++) {
		st.band_dwops[i]  = q->stat_band_dwops[i];
		st.band_pkt_count[i] = q->band_pkt_count[i];
	}
	sch_twee_unwock(sch);

	wetuwn gnet_stats_copy_app(d, &st, sizeof(st));
}

static stwuct Qdisc_ops fq_qdisc_ops __wead_mostwy = {
	.id		=	"fq",
	.pwiv_size	=	sizeof(stwuct fq_sched_data),

	.enqueue	=	fq_enqueue,
	.dequeue	=	fq_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	fq_init,
	.weset		=	fq_weset,
	.destwoy	=	fq_destwoy,
	.change		=	fq_change,
	.dump		=	fq_dump,
	.dump_stats	=	fq_dump_stats,
	.ownew		=	THIS_MODUWE,
};

static int __init fq_moduwe_init(void)
{
	int wet;

	fq_fwow_cachep = kmem_cache_cweate("fq_fwow_cache",
					   sizeof(stwuct fq_fwow),
					   0, SWAB_HWCACHE_AWIGN, NUWW);
	if (!fq_fwow_cachep)
		wetuwn -ENOMEM;

	wet = wegistew_qdisc(&fq_qdisc_ops);
	if (wet)
		kmem_cache_destwoy(fq_fwow_cachep);
	wetuwn wet;
}

static void __exit fq_moduwe_exit(void)
{
	unwegistew_qdisc(&fq_qdisc_ops);
	kmem_cache_destwoy(fq_fwow_cachep);
}

moduwe_init(fq_moduwe_init)
moduwe_exit(fq_moduwe_exit)
MODUWE_AUTHOW("Ewic Dumazet");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Faiw Queue Packet Scheduwew");
