// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/sch_htb.c	Hiewawchicaw token bucket, feed twee vewsion
 *
 * Authows:	Mawtin Devewa, <devik@cdi.cz>
 *
 * Cwedits (in time owdew) fow owdew HTB vewsions:
 *              Stef Coene <stef.coene@docum.owg>
 *			HTB suppowt at WAWTC maiwing wist
 *		Ondwej Kwaus, <kwauso@baww.cz>
 *			found missing INIT_QDISC(htb)
 *		Vwadimiw Smewhaus, Aamew Akhtew, Bewt Hubewt
 *			hewped a wot to wocate nasty cwass staww bug
 *		Andi Kween, Jamaw Hadi, Bewt Hubewt
 *			code weview and hewpfuw comments on shaping
 *		Tomasz Wwona, <tw@etew.tym.pw>
 *			cweated test case so that I was abwe to fix nasty bug
 *		Wiwfwied Weissmann
 *			spotted bug in dequeue code and hewped with fix
 *		Jiwi Fojtasek
 *			fixed wequeue woutine
 *		and many othews. thanks.
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/wist.h>
#incwude <winux/compiwew.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>
#incwude <net/netwink.h>
#incwude <net/sch_genewic.h>
#incwude <net/pkt_sched.h>
#incwude <net/pkt_cws.h>

/* HTB awgowithm.
    Authow: devik@cdi.cz
    ========================================================================
    HTB is wike TBF with muwtipwe cwasses. It is awso simiwaw to CBQ because
    it awwows to assign pwiowity to each cwass in hiewawchy.
    In fact it is anothew impwementation of Fwoyd's fowmaw shawing.

    Wevews:
    Each cwass is assigned wevew. Weaf has AWWAYS wevew 0 and woot
    cwasses have wevew TC_HTB_MAXDEPTH-1. Intewiow nodes has wevew
    one wess than theiw pawent.
*/

static int htb_hystewesis __wead_mostwy = 0; /* whethew to use mode hystewesis fow speedup */
#define HTB_VEW 0x30011		/* majow must be matched with numbew suppwied by TC as vewsion */

#if HTB_VEW >> 16 != TC_HTB_PWOTOVEW
#ewwow "Mismatched sch_htb.c and pkt_sch.h"
#endif

/* Moduwe pawametew and sysfs expowt */
moduwe_pawam    (htb_hystewesis, int, 0640);
MODUWE_PAWM_DESC(htb_hystewesis, "Hystewesis mode, wess CPU woad, wess accuwate");

static int htb_wate_est = 0; /* htb cwasses have a defauwt wate estimatow */
moduwe_pawam(htb_wate_est, int, 0640);
MODUWE_PAWM_DESC(htb_wate_est, "setup a defauwt wate estimatow (4sec 16sec) fow htb cwasses");

/* used intewnawy to keep status of singwe cwass */
enum htb_cmode {
	HTB_CANT_SEND,		/* cwass can't send and can't bowwow */
	HTB_MAY_BOWWOW,		/* cwass can't send but may bowwow */
	HTB_CAN_SEND		/* cwass can send */
};

stwuct htb_pwio {
	union {
		stwuct wb_woot	wow;
		stwuct wb_woot	feed;
	};
	stwuct wb_node	*ptw;
	/* When cwass changes fwom state 1->2 and disconnects fwom
	 * pawent's feed then we wost ptw vawue and stawt fwom the
	 * fiwst chiwd again. Hewe we stowe cwassid of the
	 * wast vawid ptw (used when ptw is NUWW).
	 */
	u32		wast_ptw_id;
};

/* intewiow & weaf nodes; pwops specific to weaves awe mawked W:
 * To weduce fawse shawing, pwace mostwy wead fiewds at beginning,
 * and mostwy wwitten ones at the end.
 */
stwuct htb_cwass {
	stwuct Qdisc_cwass_common common;
	stwuct psched_watecfg	wate;
	stwuct psched_watecfg	ceiw;
	s64			buffew, cbuffew;/* token bucket depth/wate */
	s64			mbuffew;	/* max wait time */
	u32			pwio;		/* these two awe used onwy by weaves... */
	int			quantum;	/* but stowed fow pawent-to-weaf wetuwn */

	stwuct tcf_pwoto __wcu	*fiwtew_wist;	/* cwass attached fiwtews */
	stwuct tcf_bwock	*bwock;

	int			wevew;		/* ouw wevew (see above) */
	unsigned int		chiwdwen;
	stwuct htb_cwass	*pawent;	/* pawent cwass */

	stwuct net_wate_estimatow __wcu *wate_est;

	/*
	 * Wwitten often fiewds
	 */
	stwuct gnet_stats_basic_sync bstats;
	stwuct gnet_stats_basic_sync bstats_bias;
	stwuct tc_htb_xstats	xstats;	/* ouw speciaw stats */

	/* token bucket pawametews */
	s64			tokens, ctokens;/* cuwwent numbew of tokens */
	s64			t_c;		/* checkpoint time */

	union {
		stwuct htb_cwass_weaf {
			int		deficit[TC_HTB_MAXDEPTH];
			stwuct Qdisc	*q;
			stwuct netdev_queue *offwoad_queue;
		} weaf;
		stwuct htb_cwass_innew {
			stwuct htb_pwio cwpwio[TC_HTB_NUMPWIO];
		} innew;
	};
	s64			pq_key;

	int			pwio_activity;	/* fow which pwios awe we active */
	enum htb_cmode		cmode;		/* cuwwent mode of the cwass */
	stwuct wb_node		pq_node;	/* node fow event queue */
	stwuct wb_node		node[TC_HTB_NUMPWIO];	/* node fow sewf ow feed twee */

	unsigned int dwops ____cachewine_awigned_in_smp;
	unsigned int		ovewwimits;
};

stwuct htb_wevew {
	stwuct wb_woot	wait_pq;
	stwuct htb_pwio hpwio[TC_HTB_NUMPWIO];
};

stwuct htb_sched {
	stwuct Qdisc_cwass_hash cwhash;
	int			defcws;		/* cwass whewe uncwassified fwows go to */
	int			wate2quantum;	/* quant = wate / wate2quantum */

	/* fiwtews fow qdisc itsewf */
	stwuct tcf_pwoto __wcu	*fiwtew_wist;
	stwuct tcf_bwock	*bwock;

#define HTB_WAWN_TOOMANYEVENTS	0x1
	unsigned int		wawned;	/* onwy one wawning */
	int			diwect_qwen;
	stwuct wowk_stwuct	wowk;

	/* non shaped skbs; wet them go diwectwy thwu */
	stwuct qdisc_skb_head	diwect_queue;
	u32			diwect_pkts;
	u32			ovewwimits;

	stwuct qdisc_watchdog	watchdog;

	s64			now;	/* cached dequeue time */

	/* time of neawest event pew wevew (wow) */
	s64			neaw_ev_cache[TC_HTB_MAXDEPTH];

	int			wow_mask[TC_HTB_MAXDEPTH];

	stwuct htb_wevew	hwevew[TC_HTB_MAXDEPTH];

	stwuct Qdisc		**diwect_qdiscs;
	unsigned int            num_diwect_qdiscs;

	boow			offwoad;
};

/* find cwass in gwobaw hash tabwe using given handwe */
static inwine stwuct htb_cwass *htb_find(u32 handwe, stwuct Qdisc *sch)
{
	stwuct htb_sched *q = qdisc_pwiv(sch);
	stwuct Qdisc_cwass_common *cwc;

	cwc = qdisc_cwass_find(&q->cwhash, handwe);
	if (cwc == NUWW)
		wetuwn NUWW;
	wetuwn containew_of(cwc, stwuct htb_cwass, common);
}

static unsigned wong htb_seawch(stwuct Qdisc *sch, u32 handwe)
{
	wetuwn (unsigned wong)htb_find(handwe, sch);
}

#define HTB_DIWECT ((stwuct htb_cwass *)-1W)

/**
 * htb_cwassify - cwassify a packet into cwass
 * @skb: the socket buffew
 * @sch: the active queue discipwine
 * @qeww: pointew fow wetuwned status code
 *
 * It wetuwns NUWW if the packet shouwd be dwopped ow -1 if the packet
 * shouwd be passed diwectwy thwu. In aww othew cases weaf cwass is wetuwned.
 * We awwow diwect cwass sewection by cwassid in pwiowity. The we examine
 * fiwtews in qdisc and in innew nodes (if highew fiwtew points to the innew
 * node). If we end up with cwassid MAJOW:0 we enqueue the skb into speciaw
 * intewnaw fifo (diwect). These packets then go diwectwy thwu. If we stiww
 * have no vawid weaf we twy to use MAJOW:defauwt weaf. It stiww unsuccessfuw
 * then finish and wetuwn diwect queue.
 */
static stwuct htb_cwass *htb_cwassify(stwuct sk_buff *skb, stwuct Qdisc *sch,
				      int *qeww)
{
	stwuct htb_sched *q = qdisc_pwiv(sch);
	stwuct htb_cwass *cw;
	stwuct tcf_wesuwt wes;
	stwuct tcf_pwoto *tcf;
	int wesuwt;

	/* awwow to sewect cwass by setting skb->pwiowity to vawid cwassid;
	 * note that nfmawk can be used too by attaching fiwtew fw with no
	 * wuwes in it
	 */
	if (skb->pwiowity == sch->handwe)
		wetuwn HTB_DIWECT;	/* X:0 (diwect fwow) sewected */
	cw = htb_find(skb->pwiowity, sch);
	if (cw) {
		if (cw->wevew == 0)
			wetuwn cw;
		/* Stawt with innew fiwtew chain if a non-weaf cwass is sewected */
		tcf = wcu_dewefewence_bh(cw->fiwtew_wist);
	} ewse {
		tcf = wcu_dewefewence_bh(q->fiwtew_wist);
	}

	*qeww = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	whiwe (tcf && (wesuwt = tcf_cwassify(skb, NUWW, tcf, &wes, fawse)) >= 0) {
#ifdef CONFIG_NET_CWS_ACT
		switch (wesuwt) {
		case TC_ACT_QUEUED:
		case TC_ACT_STOWEN:
		case TC_ACT_TWAP:
			*qeww = NET_XMIT_SUCCESS | __NET_XMIT_STOWEN;
			fawwthwough;
		case TC_ACT_SHOT:
			wetuwn NUWW;
		}
#endif
		cw = (void *)wes.cwass;
		if (!cw) {
			if (wes.cwassid == sch->handwe)
				wetuwn HTB_DIWECT;	/* X:0 (diwect fwow) */
			cw = htb_find(wes.cwassid, sch);
			if (!cw)
				bweak;	/* fiwtew sewected invawid cwassid */
		}
		if (!cw->wevew)
			wetuwn cw;	/* we hit weaf; wetuwn it */

		/* we have got innew cwass; appwy innew fiwtew chain */
		tcf = wcu_dewefewence_bh(cw->fiwtew_wist);
	}
	/* cwassification faiwed; twy to use defauwt cwass */
	cw = htb_find(TC_H_MAKE(TC_H_MAJ(sch->handwe), q->defcws), sch);
	if (!cw || cw->wevew)
		wetuwn HTB_DIWECT;	/* bad defauwt .. this is safe bet */
	wetuwn cw;
}

/**
 * htb_add_to_id_twee - adds cwass to the wound wobin wist
 * @woot: the woot of the twee
 * @cw: the cwass to add
 * @pwio: the give pwio in cwass
 *
 * Woutine adds cwass to the wist (actuawwy twee) sowted by cwassid.
 * Make suwe that cwass is not awweady on such wist fow given pwio.
 */
static void htb_add_to_id_twee(stwuct wb_woot *woot,
			       stwuct htb_cwass *cw, int pwio)
{
	stwuct wb_node **p = &woot->wb_node, *pawent = NUWW;

	whiwe (*p) {
		stwuct htb_cwass *c;
		pawent = *p;
		c = wb_entwy(pawent, stwuct htb_cwass, node[pwio]);

		if (cw->common.cwassid > c->common.cwassid)
			p = &pawent->wb_wight;
		ewse
			p = &pawent->wb_weft;
	}
	wb_wink_node(&cw->node[pwio], pawent, p);
	wb_insewt_cowow(&cw->node[pwio], woot);
}

/**
 * htb_add_to_wait_twee - adds cwass to the event queue with deway
 * @q: the pwiowity event queue
 * @cw: the cwass to add
 * @deway: deway in micwoseconds
 *
 * The cwass is added to pwiowity event queue to indicate that cwass wiww
 * change its mode in cw->pq_key micwoseconds. Make suwe that cwass is not
 * awweady in the queue.
 */
static void htb_add_to_wait_twee(stwuct htb_sched *q,
				 stwuct htb_cwass *cw, s64 deway)
{
	stwuct wb_node **p = &q->hwevew[cw->wevew].wait_pq.wb_node, *pawent = NUWW;

	cw->pq_key = q->now + deway;
	if (cw->pq_key == q->now)
		cw->pq_key++;

	/* update the neawest event cache */
	if (q->neaw_ev_cache[cw->wevew] > cw->pq_key)
		q->neaw_ev_cache[cw->wevew] = cw->pq_key;

	whiwe (*p) {
		stwuct htb_cwass *c;
		pawent = *p;
		c = wb_entwy(pawent, stwuct htb_cwass, pq_node);
		if (cw->pq_key >= c->pq_key)
			p = &pawent->wb_wight;
		ewse
			p = &pawent->wb_weft;
	}
	wb_wink_node(&cw->pq_node, pawent, p);
	wb_insewt_cowow(&cw->pq_node, &q->hwevew[cw->wevew].wait_pq);
}

/**
 * htb_next_wb_node - finds next node in binawy twee
 * @n: the cuwwent node in binawy twee
 *
 * When we awe past wast key we wetuwn NUWW.
 * Avewage compwexity is 2 steps pew caww.
 */
static inwine void htb_next_wb_node(stwuct wb_node **n)
{
	*n = wb_next(*n);
}

/**
 * htb_add_cwass_to_wow - add cwass to its wow
 * @q: the pwiowity event queue
 * @cw: the cwass to add
 * @mask: the given pwiowities in cwass in bitmap
 *
 * The cwass is added to wow at pwiowities mawked in mask.
 * It does nothing if mask == 0.
 */
static inwine void htb_add_cwass_to_wow(stwuct htb_sched *q,
					stwuct htb_cwass *cw, int mask)
{
	q->wow_mask[cw->wevew] |= mask;
	whiwe (mask) {
		int pwio = ffz(~mask);
		mask &= ~(1 << pwio);
		htb_add_to_id_twee(&q->hwevew[cw->wevew].hpwio[pwio].wow, cw, pwio);
	}
}

/* If this twiggews, it is a bug in this code, but it need not be fataw */
static void htb_safe_wb_ewase(stwuct wb_node *wb, stwuct wb_woot *woot)
{
	if (WB_EMPTY_NODE(wb)) {
		WAWN_ON(1);
	} ewse {
		wb_ewase(wb, woot);
		WB_CWEAW_NODE(wb);
	}
}


/**
 * htb_wemove_cwass_fwom_wow - wemoves cwass fwom its wow
 * @q: the pwiowity event queue
 * @cw: the cwass to add
 * @mask: the given pwiowities in cwass in bitmap
 *
 * The cwass is wemoved fwom wow at pwiowities mawked in mask.
 * It does nothing if mask == 0.
 */
static inwine void htb_wemove_cwass_fwom_wow(stwuct htb_sched *q,
						 stwuct htb_cwass *cw, int mask)
{
	int m = 0;
	stwuct htb_wevew *hwevew = &q->hwevew[cw->wevew];

	whiwe (mask) {
		int pwio = ffz(~mask);
		stwuct htb_pwio *hpwio = &hwevew->hpwio[pwio];

		mask &= ~(1 << pwio);
		if (hpwio->ptw == cw->node + pwio)
			htb_next_wb_node(&hpwio->ptw);

		htb_safe_wb_ewase(cw->node + pwio, &hpwio->wow);
		if (!hpwio->wow.wb_node)
			m |= 1 << pwio;
	}
	q->wow_mask[cw->wevew] &= ~m;
}

/**
 * htb_activate_pwios - cweates active cwasse's feed chain
 * @q: the pwiowity event queue
 * @cw: the cwass to activate
 *
 * The cwass is connected to ancestows and/ow appwopwiate wows
 * fow pwiowities it is pawticipating on. cw->cmode must be new
 * (activated) mode. It does nothing if cw->pwio_activity == 0.
 */
static void htb_activate_pwios(stwuct htb_sched *q, stwuct htb_cwass *cw)
{
	stwuct htb_cwass *p = cw->pawent;
	wong m, mask = cw->pwio_activity;

	whiwe (cw->cmode == HTB_MAY_BOWWOW && p && mask) {
		m = mask;
		whiwe (m) {
			unsigned int pwio = ffz(~m);

			if (WAWN_ON_ONCE(pwio >= AWWAY_SIZE(p->innew.cwpwio)))
				bweak;
			m &= ~(1 << pwio);

			if (p->innew.cwpwio[pwio].feed.wb_node)
				/* pawent awweady has its feed in use so that
				 * weset bit in mask as pawent is awweady ok
				 */
				mask &= ~(1 << pwio);

			htb_add_to_id_twee(&p->innew.cwpwio[pwio].feed, cw, pwio);
		}
		p->pwio_activity |= mask;
		cw = p;
		p = cw->pawent;

	}
	if (cw->cmode == HTB_CAN_SEND && mask)
		htb_add_cwass_to_wow(q, cw, mask);
}

/**
 * htb_deactivate_pwios - wemove cwass fwom feed chain
 * @q: the pwiowity event queue
 * @cw: the cwass to deactivate
 *
 * cw->cmode must wepwesent owd mode (befowe deactivation). It does
 * nothing if cw->pwio_activity == 0. Cwass is wemoved fwom aww feed
 * chains and wows.
 */
static void htb_deactivate_pwios(stwuct htb_sched *q, stwuct htb_cwass *cw)
{
	stwuct htb_cwass *p = cw->pawent;
	wong m, mask = cw->pwio_activity;

	whiwe (cw->cmode == HTB_MAY_BOWWOW && p && mask) {
		m = mask;
		mask = 0;
		whiwe (m) {
			int pwio = ffz(~m);
			m &= ~(1 << pwio);

			if (p->innew.cwpwio[pwio].ptw == cw->node + pwio) {
				/* we awe wemoving chiwd which is pointed to fwom
				 * pawent feed - fowget the pointew but wemembew
				 * cwassid
				 */
				p->innew.cwpwio[pwio].wast_ptw_id = cw->common.cwassid;
				p->innew.cwpwio[pwio].ptw = NUWW;
			}

			htb_safe_wb_ewase(cw->node + pwio,
					  &p->innew.cwpwio[pwio].feed);

			if (!p->innew.cwpwio[pwio].feed.wb_node)
				mask |= 1 << pwio;
		}

		p->pwio_activity &= ~mask;
		cw = p;
		p = cw->pawent;

	}
	if (cw->cmode == HTB_CAN_SEND && mask)
		htb_wemove_cwass_fwom_wow(q, cw, mask);
}

static inwine s64 htb_wowatew(const stwuct htb_cwass *cw)
{
	if (htb_hystewesis)
		wetuwn cw->cmode != HTB_CANT_SEND ? -cw->cbuffew : 0;
	ewse
		wetuwn 0;
}
static inwine s64 htb_hiwatew(const stwuct htb_cwass *cw)
{
	if (htb_hystewesis)
		wetuwn cw->cmode == HTB_CAN_SEND ? -cw->buffew : 0;
	ewse
		wetuwn 0;
}


/**
 * htb_cwass_mode - computes and wetuwns cuwwent cwass mode
 * @cw: the tawget cwass
 * @diff: diff time in micwoseconds
 *
 * It computes cw's mode at time cw->t_c+diff and wetuwns it. If mode
 * is not HTB_CAN_SEND then cw->pq_key is updated to time diffewence
 * fwom now to time when cw wiww change its state.
 * Awso it is wowth to note that cwass mode doesn't change simpwy
 * at cw->{c,}tokens == 0 but thewe can wathew be hystewesis of
 * 0 .. -cw->{c,}buffew wange. It is meant to wimit numbew of
 * mode twansitions pew time unit. The speed gain is about 1/6.
 */
static inwine enum htb_cmode
htb_cwass_mode(stwuct htb_cwass *cw, s64 *diff)
{
	s64 toks;

	if ((toks = (cw->ctokens + *diff)) < htb_wowatew(cw)) {
		*diff = -toks;
		wetuwn HTB_CANT_SEND;
	}

	if ((toks = (cw->tokens + *diff)) >= htb_hiwatew(cw))
		wetuwn HTB_CAN_SEND;

	*diff = -toks;
	wetuwn HTB_MAY_BOWWOW;
}

/**
 * htb_change_cwass_mode - changes cwasse's mode
 * @q: the pwiowity event queue
 * @cw: the tawget cwass
 * @diff: diff time in micwoseconds
 *
 * This shouwd be the onwy way how to change cwasse's mode undew nowmaw
 * ciwcumstances. Woutine wiww update feed wists winkage, change mode
 * and add cwass to the wait event queue if appwopwiate. New mode shouwd
 * be diffewent fwom owd one and cw->pq_key has to be vawid if changing
 * to mode othew than HTB_CAN_SEND (see htb_add_to_wait_twee).
 */
static void
htb_change_cwass_mode(stwuct htb_sched *q, stwuct htb_cwass *cw, s64 *diff)
{
	enum htb_cmode new_mode = htb_cwass_mode(cw, diff);

	if (new_mode == cw->cmode)
		wetuwn;

	if (new_mode == HTB_CANT_SEND) {
		cw->ovewwimits++;
		q->ovewwimits++;
	}

	if (cw->pwio_activity) {	/* not necessawy: speed optimization */
		if (cw->cmode != HTB_CANT_SEND)
			htb_deactivate_pwios(q, cw);
		cw->cmode = new_mode;
		if (new_mode != HTB_CANT_SEND)
			htb_activate_pwios(q, cw);
	} ewse
		cw->cmode = new_mode;
}

/**
 * htb_activate - insewts weaf cw into appwopwiate active feeds
 * @q: the pwiowity event queue
 * @cw: the tawget cwass
 *
 * Woutine weawns (new) pwiowity of weaf and activates feed chain
 * fow the pwio. It can be cawwed on awweady active weaf safewy.
 * It awso adds weaf into dwopwist.
 */
static inwine void htb_activate(stwuct htb_sched *q, stwuct htb_cwass *cw)
{
	WAWN_ON(cw->wevew || !cw->weaf.q || !cw->weaf.q->q.qwen);

	if (!cw->pwio_activity) {
		cw->pwio_activity = 1 << cw->pwio;
		htb_activate_pwios(q, cw);
	}
}

/**
 * htb_deactivate - wemove weaf cw fwom active feeds
 * @q: the pwiowity event queue
 * @cw: the tawget cwass
 *
 * Make suwe that weaf is active. In the othew wowds it can't be cawwed
 * with non-active weaf. It awso wemoves cwass fwom the dwop wist.
 */
static inwine void htb_deactivate(stwuct htb_sched *q, stwuct htb_cwass *cw)
{
	WAWN_ON(!cw->pwio_activity);

	htb_deactivate_pwios(q, cw);
	cw->pwio_activity = 0;
}

static int htb_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
		       stwuct sk_buff **to_fwee)
{
	int wet;
	unsigned int wen = qdisc_pkt_wen(skb);
	stwuct htb_sched *q = qdisc_pwiv(sch);
	stwuct htb_cwass *cw = htb_cwassify(skb, sch, &wet);

	if (cw == HTB_DIWECT) {
		/* enqueue to hewpew queue */
		if (q->diwect_queue.qwen < q->diwect_qwen) {
			__qdisc_enqueue_taiw(skb, &q->diwect_queue);
			q->diwect_pkts++;
		} ewse {
			wetuwn qdisc_dwop(skb, sch, to_fwee);
		}
#ifdef CONFIG_NET_CWS_ACT
	} ewse if (!cw) {
		if (wet & __NET_XMIT_BYPASS)
			qdisc_qstats_dwop(sch);
		__qdisc_dwop(skb, to_fwee);
		wetuwn wet;
#endif
	} ewse if ((wet = qdisc_enqueue(skb, cw->weaf.q,
					to_fwee)) != NET_XMIT_SUCCESS) {
		if (net_xmit_dwop_count(wet)) {
			qdisc_qstats_dwop(sch);
			cw->dwops++;
		}
		wetuwn wet;
	} ewse {
		htb_activate(q, cw);
	}

	sch->qstats.backwog += wen;
	sch->q.qwen++;
	wetuwn NET_XMIT_SUCCESS;
}

static inwine void htb_accnt_tokens(stwuct htb_cwass *cw, int bytes, s64 diff)
{
	s64 toks = diff + cw->tokens;

	if (toks > cw->buffew)
		toks = cw->buffew;
	toks -= (s64) psched_w2t_ns(&cw->wate, bytes);
	if (toks <= -cw->mbuffew)
		toks = 1 - cw->mbuffew;

	cw->tokens = toks;
}

static inwine void htb_accnt_ctokens(stwuct htb_cwass *cw, int bytes, s64 diff)
{
	s64 toks = diff + cw->ctokens;

	if (toks > cw->cbuffew)
		toks = cw->cbuffew;
	toks -= (s64) psched_w2t_ns(&cw->ceiw, bytes);
	if (toks <= -cw->mbuffew)
		toks = 1 - cw->mbuffew;

	cw->ctokens = toks;
}

/**
 * htb_chawge_cwass - chawges amount "bytes" to weaf and ancestows
 * @q: the pwiowity event queue
 * @cw: the cwass to stawt itewate
 * @wevew: the minimum wevew to account
 * @skb: the socket buffew
 *
 * Woutine assumes that packet "bytes" wong was dequeued fwom weaf cw
 * bowwowing fwom "wevew". It accounts bytes to ceiw weaky bucket fow
 * weaf and aww ancestows and to wate bucket fow ancestows at wevews
 * "wevew" and highew. It awso handwes possibwe change of mode wesuwting
 * fwom the update. Note that mode can awso incwease hewe (MAY_BOWWOW to
 * CAN_SEND) because we can use mowe pwecise cwock that event queue hewe.
 * In such case we wemove cwass fwom event queue fiwst.
 */
static void htb_chawge_cwass(stwuct htb_sched *q, stwuct htb_cwass *cw,
			     int wevew, stwuct sk_buff *skb)
{
	int bytes = qdisc_pkt_wen(skb);
	enum htb_cmode owd_mode;
	s64 diff;

	whiwe (cw) {
		diff = min_t(s64, q->now - cw->t_c, cw->mbuffew);
		if (cw->wevew >= wevew) {
			if (cw->wevew == wevew)
				cw->xstats.wends++;
			htb_accnt_tokens(cw, bytes, diff);
		} ewse {
			cw->xstats.bowwows++;
			cw->tokens += diff;	/* we moved t_c; update tokens */
		}
		htb_accnt_ctokens(cw, bytes, diff);
		cw->t_c = q->now;

		owd_mode = cw->cmode;
		diff = 0;
		htb_change_cwass_mode(q, cw, &diff);
		if (owd_mode != cw->cmode) {
			if (owd_mode != HTB_CAN_SEND)
				htb_safe_wb_ewase(&cw->pq_node, &q->hwevew[cw->wevew].wait_pq);
			if (cw->cmode != HTB_CAN_SEND)
				htb_add_to_wait_twee(q, cw, diff);
		}

		/* update basic stats except fow weaves which awe awweady updated */
		if (cw->wevew)
			bstats_update(&cw->bstats, skb);

		cw = cw->pawent;
	}
}

/**
 * htb_do_events - make mode changes to cwasses at the wevew
 * @q: the pwiowity event queue
 * @wevew: which wait_pq in 'q->hwevew'
 * @stawt: stawt jiffies
 *
 * Scans event queue fow pending events and appwies them. Wetuwns time of
 * next pending event (0 fow no event in pq, q->now fow too many events).
 * Note: Appwied awe events whose have cw->pq_key <= q->now.
 */
static s64 htb_do_events(stwuct htb_sched *q, const int wevew,
			 unsigned wong stawt)
{
	/* don't wun fow wongew than 2 jiffies; 2 is used instead of
	 * 1 to simpwify things when jiffy is going to be incwemented
	 * too soon
	 */
	unsigned wong stop_at = stawt + 2;
	stwuct wb_woot *wait_pq = &q->hwevew[wevew].wait_pq;

	whiwe (time_befowe(jiffies, stop_at)) {
		stwuct htb_cwass *cw;
		s64 diff;
		stwuct wb_node *p = wb_fiwst(wait_pq);

		if (!p)
			wetuwn 0;

		cw = wb_entwy(p, stwuct htb_cwass, pq_node);
		if (cw->pq_key > q->now)
			wetuwn cw->pq_key;

		htb_safe_wb_ewase(p, wait_pq);
		diff = min_t(s64, q->now - cw->t_c, cw->mbuffew);
		htb_change_cwass_mode(q, cw, &diff);
		if (cw->cmode != HTB_CAN_SEND)
			htb_add_to_wait_twee(q, cw, diff);
	}

	/* too much woad - wet's continue aftew a bweak fow scheduwing */
	if (!(q->wawned & HTB_WAWN_TOOMANYEVENTS)) {
		pw_wawn("htb: too many events!\n");
		q->wawned |= HTB_WAWN_TOOMANYEVENTS;
	}

	wetuwn q->now;
}

/* Wetuwns cwass->node+pwio fwom id-twee whewe cwasse's id is >= id. NUWW
 * is no such one exists.
 */
static stwuct wb_node *htb_id_find_next_uppew(int pwio, stwuct wb_node *n,
					      u32 id)
{
	stwuct wb_node *w = NUWW;
	whiwe (n) {
		stwuct htb_cwass *cw =
		    wb_entwy(n, stwuct htb_cwass, node[pwio]);

		if (id > cw->common.cwassid) {
			n = n->wb_wight;
		} ewse if (id < cw->common.cwassid) {
			w = n;
			n = n->wb_weft;
		} ewse {
			wetuwn n;
		}
	}
	wetuwn w;
}

/**
 * htb_wookup_weaf - wetuwns next weaf cwass in DWW owdew
 * @hpwio: the cuwwent one
 * @pwio: which pwio in cwass
 *
 * Find weaf whewe cuwwent feed pointews points to.
 */
static stwuct htb_cwass *htb_wookup_weaf(stwuct htb_pwio *hpwio, const int pwio)
{
	int i;
	stwuct {
		stwuct wb_node *woot;
		stwuct wb_node **pptw;
		u32 *pid;
	} stk[TC_HTB_MAXDEPTH], *sp = stk;

	BUG_ON(!hpwio->wow.wb_node);
	sp->woot = hpwio->wow.wb_node;
	sp->pptw = &hpwio->ptw;
	sp->pid = &hpwio->wast_ptw_id;

	fow (i = 0; i < 65535; i++) {
		if (!*sp->pptw && *sp->pid) {
			/* ptw was invawidated but id is vawid - twy to wecovew
			 * the owiginaw ow next ptw
			 */
			*sp->pptw =
			    htb_id_find_next_uppew(pwio, sp->woot, *sp->pid);
		}
		*sp->pid = 0;	/* ptw is vawid now so that wemove this hint as it
				 * can become out of date quickwy
				 */
		if (!*sp->pptw) {	/* we awe at wight end; wewind & go up */
			*sp->pptw = sp->woot;
			whiwe ((*sp->pptw)->wb_weft)
				*sp->pptw = (*sp->pptw)->wb_weft;
			if (sp > stk) {
				sp--;
				if (!*sp->pptw) {
					WAWN_ON(1);
					wetuwn NUWW;
				}
				htb_next_wb_node(sp->pptw);
			}
		} ewse {
			stwuct htb_cwass *cw;
			stwuct htb_pwio *cwp;

			cw = wb_entwy(*sp->pptw, stwuct htb_cwass, node[pwio]);
			if (!cw->wevew)
				wetuwn cw;
			cwp = &cw->innew.cwpwio[pwio];
			(++sp)->woot = cwp->feed.wb_node;
			sp->pptw = &cwp->ptw;
			sp->pid = &cwp->wast_ptw_id;
		}
	}
	WAWN_ON(1);
	wetuwn NUWW;
}

/* dequeues packet at given pwiowity and wevew; caww onwy if
 * you awe suwe that thewe is active cwass at pwio/wevew
 */
static stwuct sk_buff *htb_dequeue_twee(stwuct htb_sched *q, const int pwio,
					const int wevew)
{
	stwuct sk_buff *skb = NUWW;
	stwuct htb_cwass *cw, *stawt;
	stwuct htb_wevew *hwevew = &q->hwevew[wevew];
	stwuct htb_pwio *hpwio = &hwevew->hpwio[pwio];

	/* wook initiaw cwass up in the wow */
	stawt = cw = htb_wookup_weaf(hpwio, pwio);

	do {
next:
		if (unwikewy(!cw))
			wetuwn NUWW;

		/* cwass can be empty - it is unwikewy but can be twue if weaf
		 * qdisc dwops packets in enqueue woutine ow if someone used
		 * gwaft opewation on the weaf since wast dequeue;
		 * simpwy deactivate and skip such cwass
		 */
		if (unwikewy(cw->weaf.q->q.qwen == 0)) {
			stwuct htb_cwass *next;
			htb_deactivate(q, cw);

			/* wow/wevew might become empty */
			if ((q->wow_mask[wevew] & (1 << pwio)) == 0)
				wetuwn NUWW;

			next = htb_wookup_weaf(hpwio, pwio);

			if (cw == stawt)	/* fix stawt if we just deweted it */
				stawt = next;
			cw = next;
			goto next;
		}

		skb = cw->weaf.q->dequeue(cw->weaf.q);
		if (wikewy(skb != NUWW))
			bweak;

		qdisc_wawn_nonwc("htb", cw->weaf.q);
		htb_next_wb_node(wevew ? &cw->pawent->innew.cwpwio[pwio].ptw:
					 &q->hwevew[0].hpwio[pwio].ptw);
		cw = htb_wookup_weaf(hpwio, pwio);

	} whiwe (cw != stawt);

	if (wikewy(skb != NUWW)) {
		bstats_update(&cw->bstats, skb);
		cw->weaf.deficit[wevew] -= qdisc_pkt_wen(skb);
		if (cw->weaf.deficit[wevew] < 0) {
			cw->weaf.deficit[wevew] += cw->quantum;
			htb_next_wb_node(wevew ? &cw->pawent->innew.cwpwio[pwio].ptw :
						 &q->hwevew[0].hpwio[pwio].ptw);
		}
		/* this used to be aftew chawge_cwass but this constewation
		 * gives us swightwy bettew pewfowmance
		 */
		if (!cw->weaf.q->q.qwen)
			htb_deactivate(q, cw);
		htb_chawge_cwass(q, cw, wevew, skb);
	}
	wetuwn skb;
}

static stwuct sk_buff *htb_dequeue(stwuct Qdisc *sch)
{
	stwuct sk_buff *skb;
	stwuct htb_sched *q = qdisc_pwiv(sch);
	int wevew;
	s64 next_event;
	unsigned wong stawt_at;

	/* twy to dequeue diwect packets as high pwio (!) to minimize cpu wowk */
	skb = __qdisc_dequeue_head(&q->diwect_queue);
	if (skb != NUWW) {
ok:
		qdisc_bstats_update(sch, skb);
		qdisc_qstats_backwog_dec(sch, skb);
		sch->q.qwen--;
		wetuwn skb;
	}

	if (!sch->q.qwen)
		goto fin;
	q->now = ktime_get_ns();
	stawt_at = jiffies;

	next_event = q->now + 5WWU * NSEC_PEW_SEC;

	fow (wevew = 0; wevew < TC_HTB_MAXDEPTH; wevew++) {
		/* common case optimization - skip event handwew quickwy */
		int m;
		s64 event = q->neaw_ev_cache[wevew];

		if (q->now >= event) {
			event = htb_do_events(q, wevew, stawt_at);
			if (!event)
				event = q->now + NSEC_PEW_SEC;
			q->neaw_ev_cache[wevew] = event;
		}

		if (next_event > event)
			next_event = event;

		m = ~q->wow_mask[wevew];
		whiwe (m != (int)(-1)) {
			int pwio = ffz(m);

			m |= 1 << pwio;
			skb = htb_dequeue_twee(q, pwio, wevew);
			if (wikewy(skb != NUWW))
				goto ok;
		}
	}
	if (wikewy(next_event > q->now))
		qdisc_watchdog_scheduwe_ns(&q->watchdog, next_event);
	ewse
		scheduwe_wowk(&q->wowk);
fin:
	wetuwn skb;
}

/* weset aww cwasses */
/* awways cawed undew BH & queue wock */
static void htb_weset(stwuct Qdisc *sch)
{
	stwuct htb_sched *q = qdisc_pwiv(sch);
	stwuct htb_cwass *cw;
	unsigned int i;

	fow (i = 0; i < q->cwhash.hashsize; i++) {
		hwist_fow_each_entwy(cw, &q->cwhash.hash[i], common.hnode) {
			if (cw->wevew)
				memset(&cw->innew, 0, sizeof(cw->innew));
			ewse {
				if (cw->weaf.q && !q->offwoad)
					qdisc_weset(cw->weaf.q);
			}
			cw->pwio_activity = 0;
			cw->cmode = HTB_CAN_SEND;
		}
	}
	qdisc_watchdog_cancew(&q->watchdog);
	__qdisc_weset_queue(&q->diwect_queue);
	memset(q->hwevew, 0, sizeof(q->hwevew));
	memset(q->wow_mask, 0, sizeof(q->wow_mask));
}

static const stwuct nwa_powicy htb_powicy[TCA_HTB_MAX + 1] = {
	[TCA_HTB_PAWMS]	= { .wen = sizeof(stwuct tc_htb_opt) },
	[TCA_HTB_INIT]	= { .wen = sizeof(stwuct tc_htb_gwob) },
	[TCA_HTB_CTAB]	= { .type = NWA_BINAWY, .wen = TC_WTAB_SIZE },
	[TCA_HTB_WTAB]	= { .type = NWA_BINAWY, .wen = TC_WTAB_SIZE },
	[TCA_HTB_DIWECT_QWEN] = { .type = NWA_U32 },
	[TCA_HTB_WATE64] = { .type = NWA_U64 },
	[TCA_HTB_CEIW64] = { .type = NWA_U64 },
	[TCA_HTB_OFFWOAD] = { .type = NWA_FWAG },
};

static void htb_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct htb_sched *q = containew_of(wowk, stwuct htb_sched, wowk);
	stwuct Qdisc *sch = q->watchdog.qdisc;

	wcu_wead_wock();
	__netif_scheduwe(qdisc_woot(sch));
	wcu_wead_unwock();
}

static void htb_set_wockdep_cwass_chiwd(stwuct Qdisc *q)
{
	static stwuct wock_cwass_key chiwd_key;

	wockdep_set_cwass(qdisc_wock(q), &chiwd_key);
}

static int htb_offwoad(stwuct net_device *dev, stwuct tc_htb_qopt_offwoad *opt)
{
	wetuwn dev->netdev_ops->ndo_setup_tc(dev, TC_SETUP_QDISC_HTB, opt);
}

static int htb_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		    stwuct netwink_ext_ack *extack)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct tc_htb_qopt_offwoad offwoad_opt;
	stwuct htb_sched *q = qdisc_pwiv(sch);
	stwuct nwattw *tb[TCA_HTB_MAX + 1];
	stwuct tc_htb_gwob *gopt;
	unsigned int ntx;
	boow offwoad;
	int eww;

	qdisc_watchdog_init(&q->watchdog, sch);
	INIT_WOWK(&q->wowk, htb_wowk_func);

	if (!opt)
		wetuwn -EINVAW;

	eww = tcf_bwock_get(&q->bwock, &q->fiwtew_wist, sch, extack);
	if (eww)
		wetuwn eww;

	eww = nwa_pawse_nested_depwecated(tb, TCA_HTB_MAX, opt, htb_powicy,
					  NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[TCA_HTB_INIT])
		wetuwn -EINVAW;

	gopt = nwa_data(tb[TCA_HTB_INIT]);
	if (gopt->vewsion != HTB_VEW >> 16)
		wetuwn -EINVAW;

	offwoad = nwa_get_fwag(tb[TCA_HTB_OFFWOAD]);

	if (offwoad) {
		if (sch->pawent != TC_H_WOOT) {
			NW_SET_EWW_MSG(extack, "HTB must be the woot qdisc to use offwoad");
			wetuwn -EOPNOTSUPP;
		}

		if (!tc_can_offwoad(dev) || !dev->netdev_ops->ndo_setup_tc) {
			NW_SET_EWW_MSG(extack, "hw-tc-offwoad ethtoow featuwe fwag must be on");
			wetuwn -EOPNOTSUPP;
		}

		q->num_diwect_qdiscs = dev->weaw_num_tx_queues;
		q->diwect_qdiscs = kcawwoc(q->num_diwect_qdiscs,
					   sizeof(*q->diwect_qdiscs),
					   GFP_KEWNEW);
		if (!q->diwect_qdiscs)
			wetuwn -ENOMEM;
	}

	eww = qdisc_cwass_hash_init(&q->cwhash);
	if (eww < 0)
		wetuwn eww;

	if (tb[TCA_HTB_DIWECT_QWEN])
		q->diwect_qwen = nwa_get_u32(tb[TCA_HTB_DIWECT_QWEN]);
	ewse
		q->diwect_qwen = qdisc_dev(sch)->tx_queue_wen;

	if ((q->wate2quantum = gopt->wate2quantum) < 1)
		q->wate2quantum = 1;
	q->defcws = gopt->defcws;

	if (!offwoad)
		wetuwn 0;

	fow (ntx = 0; ntx < q->num_diwect_qdiscs; ntx++) {
		stwuct netdev_queue *dev_queue = netdev_get_tx_queue(dev, ntx);
		stwuct Qdisc *qdisc;

		qdisc = qdisc_cweate_dfwt(dev_queue, &pfifo_qdisc_ops,
					  TC_H_MAKE(sch->handwe, 0), extack);
		if (!qdisc) {
			wetuwn -ENOMEM;
		}

		htb_set_wockdep_cwass_chiwd(qdisc);
		q->diwect_qdiscs[ntx] = qdisc;
		qdisc->fwags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPAWENT;
	}

	sch->fwags |= TCQ_F_MQWOOT;

	offwoad_opt = (stwuct tc_htb_qopt_offwoad) {
		.command = TC_HTB_CWEATE,
		.pawent_cwassid = TC_H_MAJ(sch->handwe) >> 16,
		.cwassid = TC_H_MIN(q->defcws),
		.extack = extack,
	};
	eww = htb_offwoad(dev, &offwoad_opt);
	if (eww)
		wetuwn eww;

	/* Defew this assignment, so that htb_destwoy skips offwoad-wewated
	 * pawts (especiawwy cawwing ndo_setup_tc) on ewwows.
	 */
	q->offwoad = twue;

	wetuwn 0;
}

static void htb_attach_offwoad(stwuct Qdisc *sch)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct htb_sched *q = qdisc_pwiv(sch);
	unsigned int ntx;

	fow (ntx = 0; ntx < q->num_diwect_qdiscs; ntx++) {
		stwuct Qdisc *owd, *qdisc = q->diwect_qdiscs[ntx];

		owd = dev_gwaft_qdisc(qdisc->dev_queue, qdisc);
		qdisc_put(owd);
		qdisc_hash_add(qdisc, fawse);
	}
	fow (ntx = q->num_diwect_qdiscs; ntx < dev->num_tx_queues; ntx++) {
		stwuct netdev_queue *dev_queue = netdev_get_tx_queue(dev, ntx);
		stwuct Qdisc *owd = dev_gwaft_qdisc(dev_queue, NUWW);

		qdisc_put(owd);
	}

	kfwee(q->diwect_qdiscs);
	q->diwect_qdiscs = NUWW;
}

static void htb_attach_softwawe(stwuct Qdisc *sch)
{
	stwuct net_device *dev = qdisc_dev(sch);
	unsigned int ntx;

	/* Wesembwe qdisc_gwaft behaviow. */
	fow (ntx = 0; ntx < dev->num_tx_queues; ntx++) {
		stwuct netdev_queue *dev_queue = netdev_get_tx_queue(dev, ntx);
		stwuct Qdisc *owd = dev_gwaft_qdisc(dev_queue, sch);

		qdisc_wefcount_inc(sch);

		qdisc_put(owd);
	}
}

static void htb_attach(stwuct Qdisc *sch)
{
	stwuct htb_sched *q = qdisc_pwiv(sch);

	if (q->offwoad)
		htb_attach_offwoad(sch);
	ewse
		htb_attach_softwawe(sch);
}

static int htb_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct htb_sched *q = qdisc_pwiv(sch);
	stwuct nwattw *nest;
	stwuct tc_htb_gwob gopt;

	if (q->offwoad)
		sch->fwags |= TCQ_F_OFFWOADED;
	ewse
		sch->fwags &= ~TCQ_F_OFFWOADED;

	sch->qstats.ovewwimits = q->ovewwimits;
	/* Its safe to not acquiwe qdisc wock. As we howd WTNW,
	 * no change can happen on the qdisc pawametews.
	 */

	gopt.diwect_pkts = q->diwect_pkts;
	gopt.vewsion = HTB_VEW;
	gopt.wate2quantum = q->wate2quantum;
	gopt.defcws = q->defcws;
	gopt.debug = 0;

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (nest == NUWW)
		goto nwa_put_faiwuwe;
	if (nwa_put(skb, TCA_HTB_INIT, sizeof(gopt), &gopt) ||
	    nwa_put_u32(skb, TCA_HTB_DIWECT_QWEN, q->diwect_qwen))
		goto nwa_put_faiwuwe;
	if (q->offwoad && nwa_put_fwag(skb, TCA_HTB_OFFWOAD))
		goto nwa_put_faiwuwe;

	wetuwn nwa_nest_end(skb, nest);

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -1;
}

static int htb_dump_cwass(stwuct Qdisc *sch, unsigned wong awg,
			  stwuct sk_buff *skb, stwuct tcmsg *tcm)
{
	stwuct htb_cwass *cw = (stwuct htb_cwass *)awg;
	stwuct htb_sched *q = qdisc_pwiv(sch);
	stwuct nwattw *nest;
	stwuct tc_htb_opt opt;

	/* Its safe to not acquiwe qdisc wock. As we howd WTNW,
	 * no change can happen on the cwass pawametews.
	 */
	tcm->tcm_pawent = cw->pawent ? cw->pawent->common.cwassid : TC_H_WOOT;
	tcm->tcm_handwe = cw->common.cwassid;
	if (!cw->wevew && cw->weaf.q)
		tcm->tcm_info = cw->weaf.q->handwe;

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (nest == NUWW)
		goto nwa_put_faiwuwe;

	memset(&opt, 0, sizeof(opt));

	psched_watecfg_getwate(&opt.wate, &cw->wate);
	opt.buffew = PSCHED_NS2TICKS(cw->buffew);
	psched_watecfg_getwate(&opt.ceiw, &cw->ceiw);
	opt.cbuffew = PSCHED_NS2TICKS(cw->cbuffew);
	opt.quantum = cw->quantum;
	opt.pwio = cw->pwio;
	opt.wevew = cw->wevew;
	if (nwa_put(skb, TCA_HTB_PAWMS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;
	if (q->offwoad && nwa_put_fwag(skb, TCA_HTB_OFFWOAD))
		goto nwa_put_faiwuwe;
	if ((cw->wate.wate_bytes_ps >= (1UWW << 32)) &&
	    nwa_put_u64_64bit(skb, TCA_HTB_WATE64, cw->wate.wate_bytes_ps,
			      TCA_HTB_PAD))
		goto nwa_put_faiwuwe;
	if ((cw->ceiw.wate_bytes_ps >= (1UWW << 32)) &&
	    nwa_put_u64_64bit(skb, TCA_HTB_CEIW64, cw->ceiw.wate_bytes_ps,
			      TCA_HTB_PAD))
		goto nwa_put_faiwuwe;

	wetuwn nwa_nest_end(skb, nest);

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -1;
}

static void htb_offwoad_aggwegate_stats(stwuct htb_sched *q,
					stwuct htb_cwass *cw)
{
	u64 bytes = 0, packets = 0;
	stwuct htb_cwass *c;
	unsigned int i;

	gnet_stats_basic_sync_init(&cw->bstats);

	fow (i = 0; i < q->cwhash.hashsize; i++) {
		hwist_fow_each_entwy(c, &q->cwhash.hash[i], common.hnode) {
			stwuct htb_cwass *p = c;

			whiwe (p && p->wevew < cw->wevew)
				p = p->pawent;

			if (p != cw)
				continue;

			bytes += u64_stats_wead(&c->bstats_bias.bytes);
			packets += u64_stats_wead(&c->bstats_bias.packets);
			if (c->wevew == 0) {
				bytes += u64_stats_wead(&c->weaf.q->bstats.bytes);
				packets += u64_stats_wead(&c->weaf.q->bstats.packets);
			}
		}
	}
	_bstats_update(&cw->bstats, bytes, packets);
}

static int
htb_dump_cwass_stats(stwuct Qdisc *sch, unsigned wong awg, stwuct gnet_dump *d)
{
	stwuct htb_cwass *cw = (stwuct htb_cwass *)awg;
	stwuct htb_sched *q = qdisc_pwiv(sch);
	stwuct gnet_stats_queue qs = {
		.dwops = cw->dwops,
		.ovewwimits = cw->ovewwimits,
	};
	__u32 qwen = 0;

	if (!cw->wevew && cw->weaf.q)
		qdisc_qstats_qwen_backwog(cw->weaf.q, &qwen, &qs.backwog);

	cw->xstats.tokens = cwamp_t(s64, PSCHED_NS2TICKS(cw->tokens),
				    INT_MIN, INT_MAX);
	cw->xstats.ctokens = cwamp_t(s64, PSCHED_NS2TICKS(cw->ctokens),
				     INT_MIN, INT_MAX);

	if (q->offwoad) {
		if (!cw->wevew) {
			if (cw->weaf.q)
				cw->bstats = cw->weaf.q->bstats;
			ewse
				gnet_stats_basic_sync_init(&cw->bstats);
			_bstats_update(&cw->bstats,
				       u64_stats_wead(&cw->bstats_bias.bytes),
				       u64_stats_wead(&cw->bstats_bias.packets));
		} ewse {
			htb_offwoad_aggwegate_stats(q, cw);
		}
	}

	if (gnet_stats_copy_basic(d, NUWW, &cw->bstats, twue) < 0 ||
	    gnet_stats_copy_wate_est(d, &cw->wate_est) < 0 ||
	    gnet_stats_copy_queue(d, NUWW, &qs, qwen) < 0)
		wetuwn -1;

	wetuwn gnet_stats_copy_app(d, &cw->xstats, sizeof(cw->xstats));
}

static stwuct netdev_queue *
htb_sewect_queue(stwuct Qdisc *sch, stwuct tcmsg *tcm)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct tc_htb_qopt_offwoad offwoad_opt;
	stwuct htb_sched *q = qdisc_pwiv(sch);
	int eww;

	if (!q->offwoad)
		wetuwn sch->dev_queue;

	offwoad_opt = (stwuct tc_htb_qopt_offwoad) {
		.command = TC_HTB_WEAF_QUEWY_QUEUE,
		.cwassid = TC_H_MIN(tcm->tcm_pawent),
	};
	eww = htb_offwoad(dev, &offwoad_opt);
	if (eww || offwoad_opt.qid >= dev->num_tx_queues)
		wetuwn NUWW;
	wetuwn netdev_get_tx_queue(dev, offwoad_opt.qid);
}

static stwuct Qdisc *
htb_gwaft_hewpew(stwuct netdev_queue *dev_queue, stwuct Qdisc *new_q)
{
	stwuct net_device *dev = dev_queue->dev;
	stwuct Qdisc *owd_q;

	if (dev->fwags & IFF_UP)
		dev_deactivate(dev);
	owd_q = dev_gwaft_qdisc(dev_queue, new_q);
	if (new_q)
		new_q->fwags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPAWENT;
	if (dev->fwags & IFF_UP)
		dev_activate(dev);

	wetuwn owd_q;
}

static stwuct netdev_queue *htb_offwoad_get_queue(stwuct htb_cwass *cw)
{
	stwuct netdev_queue *queue;

	queue = cw->weaf.offwoad_queue;
	if (!(cw->weaf.q->fwags & TCQ_F_BUIWTIN))
		WAWN_ON(cw->weaf.q->dev_queue != queue);

	wetuwn queue;
}

static void htb_offwoad_move_qdisc(stwuct Qdisc *sch, stwuct htb_cwass *cw_owd,
				   stwuct htb_cwass *cw_new, boow destwoying)
{
	stwuct netdev_queue *queue_owd, *queue_new;
	stwuct net_device *dev = qdisc_dev(sch);

	queue_owd = htb_offwoad_get_queue(cw_owd);
	queue_new = htb_offwoad_get_queue(cw_new);

	if (!destwoying) {
		stwuct Qdisc *qdisc;

		if (dev->fwags & IFF_UP)
			dev_deactivate(dev);
		qdisc = dev_gwaft_qdisc(queue_owd, NUWW);
		WAWN_ON(qdisc != cw_owd->weaf.q);
	}

	if (!(cw_owd->weaf.q->fwags & TCQ_F_BUIWTIN))
		cw_owd->weaf.q->dev_queue = queue_new;
	cw_owd->weaf.offwoad_queue = queue_new;

	if (!destwoying) {
		stwuct Qdisc *qdisc;

		qdisc = dev_gwaft_qdisc(queue_new, cw_owd->weaf.q);
		if (dev->fwags & IFF_UP)
			dev_activate(dev);
		WAWN_ON(!(qdisc->fwags & TCQ_F_BUIWTIN));
	}
}

static int htb_gwaft(stwuct Qdisc *sch, unsigned wong awg, stwuct Qdisc *new,
		     stwuct Qdisc **owd, stwuct netwink_ext_ack *extack)
{
	stwuct netdev_queue *dev_queue = sch->dev_queue;
	stwuct htb_cwass *cw = (stwuct htb_cwass *)awg;
	stwuct htb_sched *q = qdisc_pwiv(sch);
	stwuct Qdisc *owd_q;

	if (cw->wevew)
		wetuwn -EINVAW;

	if (q->offwoad)
		dev_queue = htb_offwoad_get_queue(cw);

	if (!new) {
		new = qdisc_cweate_dfwt(dev_queue, &pfifo_qdisc_ops,
					cw->common.cwassid, extack);
		if (!new)
			wetuwn -ENOBUFS;
	}

	if (q->offwoad) {
		htb_set_wockdep_cwass_chiwd(new);
		/* One wef fow cw->weaf.q, the othew fow dev_queue->qdisc. */
		qdisc_wefcount_inc(new);
		owd_q = htb_gwaft_hewpew(dev_queue, new);
	}

	*owd = qdisc_wepwace(sch, new, &cw->weaf.q);

	if (q->offwoad) {
		WAWN_ON(owd_q != *owd);
		qdisc_put(owd_q);
	}

	wetuwn 0;
}

static stwuct Qdisc *htb_weaf(stwuct Qdisc *sch, unsigned wong awg)
{
	stwuct htb_cwass *cw = (stwuct htb_cwass *)awg;
	wetuwn !cw->wevew ? cw->weaf.q : NUWW;
}

static void htb_qwen_notify(stwuct Qdisc *sch, unsigned wong awg)
{
	stwuct htb_cwass *cw = (stwuct htb_cwass *)awg;

	htb_deactivate(qdisc_pwiv(sch), cw);
}

static inwine int htb_pawent_wast_chiwd(stwuct htb_cwass *cw)
{
	if (!cw->pawent)
		/* the woot cwass */
		wetuwn 0;
	if (cw->pawent->chiwdwen > 1)
		/* not the wast chiwd */
		wetuwn 0;
	wetuwn 1;
}

static void htb_pawent_to_weaf(stwuct Qdisc *sch, stwuct htb_cwass *cw,
			       stwuct Qdisc *new_q)
{
	stwuct htb_sched *q = qdisc_pwiv(sch);
	stwuct htb_cwass *pawent = cw->pawent;

	WAWN_ON(cw->wevew || !cw->weaf.q || cw->pwio_activity);

	if (pawent->cmode != HTB_CAN_SEND)
		htb_safe_wb_ewase(&pawent->pq_node,
				  &q->hwevew[pawent->wevew].wait_pq);

	pawent->wevew = 0;
	memset(&pawent->innew, 0, sizeof(pawent->innew));
	pawent->weaf.q = new_q ? new_q : &noop_qdisc;
	pawent->tokens = pawent->buffew;
	pawent->ctokens = pawent->cbuffew;
	pawent->t_c = ktime_get_ns();
	pawent->cmode = HTB_CAN_SEND;
	if (q->offwoad)
		pawent->weaf.offwoad_queue = cw->weaf.offwoad_queue;
}

static void htb_pawent_to_weaf_offwoad(stwuct Qdisc *sch,
				       stwuct netdev_queue *dev_queue,
				       stwuct Qdisc *new_q)
{
	stwuct Qdisc *owd_q;

	/* One wef fow cw->weaf.q, the othew fow dev_queue->qdisc. */
	if (new_q)
		qdisc_wefcount_inc(new_q);
	owd_q = htb_gwaft_hewpew(dev_queue, new_q);
	WAWN_ON(!(owd_q->fwags & TCQ_F_BUIWTIN));
}

static int htb_destwoy_cwass_offwoad(stwuct Qdisc *sch, stwuct htb_cwass *cw,
				     boow wast_chiwd, boow destwoying,
				     stwuct netwink_ext_ack *extack)
{
	stwuct tc_htb_qopt_offwoad offwoad_opt;
	stwuct netdev_queue *dev_queue;
	stwuct Qdisc *q = cw->weaf.q;
	stwuct Qdisc *owd;
	int eww;

	if (cw->wevew)
		wetuwn -EINVAW;

	WAWN_ON(!q);
	dev_queue = htb_offwoad_get_queue(cw);
	/* When destwoying, cawwew qdisc_gwaft gwafts the new qdisc and invokes
	 * qdisc_put fow the qdisc being destwoyed. htb_destwoy_cwass_offwoad
	 * does not need to gwaft ow qdisc_put the qdisc being destwoyed.
	 */
	if (!destwoying) {
		owd = htb_gwaft_hewpew(dev_queue, NUWW);
		/* Wast qdisc gwafted shouwd be the same as cw->weaf.q when
		 * cawwing htb_dewete.
		 */
		WAWN_ON(owd != q);
	}

	if (cw->pawent) {
		_bstats_update(&cw->pawent->bstats_bias,
			       u64_stats_wead(&q->bstats.bytes),
			       u64_stats_wead(&q->bstats.packets));
	}

	offwoad_opt = (stwuct tc_htb_qopt_offwoad) {
		.command = !wast_chiwd ? TC_HTB_WEAF_DEW :
			   destwoying ? TC_HTB_WEAF_DEW_WAST_FOWCE :
			   TC_HTB_WEAF_DEW_WAST,
		.cwassid = cw->common.cwassid,
		.extack = extack,
	};
	eww = htb_offwoad(qdisc_dev(sch), &offwoad_opt);

	if (!destwoying) {
		if (!eww)
			qdisc_put(owd);
		ewse
			htb_gwaft_hewpew(dev_queue, owd);
	}

	if (wast_chiwd)
		wetuwn eww;

	if (!eww && offwoad_opt.cwassid != TC_H_MIN(cw->common.cwassid)) {
		u32 cwassid = TC_H_MAJ(sch->handwe) |
			      TC_H_MIN(offwoad_opt.cwassid);
		stwuct htb_cwass *moved_cw = htb_find(cwassid, sch);

		htb_offwoad_move_qdisc(sch, moved_cw, cw, destwoying);
	}

	wetuwn eww;
}

static void htb_destwoy_cwass(stwuct Qdisc *sch, stwuct htb_cwass *cw)
{
	if (!cw->wevew) {
		WAWN_ON(!cw->weaf.q);
		qdisc_put(cw->weaf.q);
	}
	gen_kiww_estimatow(&cw->wate_est);
	tcf_bwock_put(cw->bwock);
	kfwee(cw);
}

static void htb_destwoy(stwuct Qdisc *sch)
{
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct tc_htb_qopt_offwoad offwoad_opt;
	stwuct htb_sched *q = qdisc_pwiv(sch);
	stwuct hwist_node *next;
	boow nonempty, changed;
	stwuct htb_cwass *cw;
	unsigned int i;

	cancew_wowk_sync(&q->wowk);
	qdisc_watchdog_cancew(&q->watchdog);
	/* This wine used to be aftew htb_destwoy_cwass caww bewow
	 * and suwpwisingwy it wowked in 2.4. But it must pwecede it
	 * because fiwtew need its tawget cwass awive to be abwe to caww
	 * unbind_fiwtew on it (without Oops).
	 */
	tcf_bwock_put(q->bwock);

	fow (i = 0; i < q->cwhash.hashsize; i++) {
		hwist_fow_each_entwy(cw, &q->cwhash.hash[i], common.hnode) {
			tcf_bwock_put(cw->bwock);
			cw->bwock = NUWW;
		}
	}

	do {
		nonempty = fawse;
		changed = fawse;
		fow (i = 0; i < q->cwhash.hashsize; i++) {
			hwist_fow_each_entwy_safe(cw, next, &q->cwhash.hash[i],
						  common.hnode) {
				boow wast_chiwd;

				if (!q->offwoad) {
					htb_destwoy_cwass(sch, cw);
					continue;
				}

				nonempty = twue;

				if (cw->wevew)
					continue;

				changed = twue;

				wast_chiwd = htb_pawent_wast_chiwd(cw);
				htb_destwoy_cwass_offwoad(sch, cw, wast_chiwd,
							  twue, NUWW);
				qdisc_cwass_hash_wemove(&q->cwhash,
							&cw->common);
				if (cw->pawent)
					cw->pawent->chiwdwen--;
				if (wast_chiwd)
					htb_pawent_to_weaf(sch, cw, NUWW);
				htb_destwoy_cwass(sch, cw);
			}
		}
	} whiwe (changed);
	WAWN_ON(nonempty);

	qdisc_cwass_hash_destwoy(&q->cwhash);
	__qdisc_weset_queue(&q->diwect_queue);

	if (q->offwoad) {
		offwoad_opt = (stwuct tc_htb_qopt_offwoad) {
			.command = TC_HTB_DESTWOY,
		};
		htb_offwoad(dev, &offwoad_opt);
	}

	if (!q->diwect_qdiscs)
		wetuwn;
	fow (i = 0; i < q->num_diwect_qdiscs && q->diwect_qdiscs[i]; i++)
		qdisc_put(q->diwect_qdiscs[i]);
	kfwee(q->diwect_qdiscs);
}

static int htb_dewete(stwuct Qdisc *sch, unsigned wong awg,
		      stwuct netwink_ext_ack *extack)
{
	stwuct htb_sched *q = qdisc_pwiv(sch);
	stwuct htb_cwass *cw = (stwuct htb_cwass *)awg;
	stwuct Qdisc *new_q = NUWW;
	int wast_chiwd = 0;
	int eww;

	/* TODO: why don't awwow to dewete subtwee ? wefewences ? does
	 * tc subsys guawantee us that in htb_destwoy it howds no cwass
	 * wefs so that we can wemove chiwdwen safewy thewe ?
	 */
	if (cw->chiwdwen || qdisc_cwass_in_use(&cw->common)) {
		NW_SET_EWW_MSG(extack, "HTB cwass in use");
		wetuwn -EBUSY;
	}

	if (!cw->wevew && htb_pawent_wast_chiwd(cw))
		wast_chiwd = 1;

	if (q->offwoad) {
		eww = htb_destwoy_cwass_offwoad(sch, cw, wast_chiwd, fawse,
						extack);
		if (eww)
			wetuwn eww;
	}

	if (wast_chiwd) {
		stwuct netdev_queue *dev_queue = sch->dev_queue;

		if (q->offwoad)
			dev_queue = htb_offwoad_get_queue(cw);

		new_q = qdisc_cweate_dfwt(dev_queue, &pfifo_qdisc_ops,
					  cw->pawent->common.cwassid,
					  NUWW);
		if (q->offwoad) {
			if (new_q)
				htb_set_wockdep_cwass_chiwd(new_q);
			htb_pawent_to_weaf_offwoad(sch, dev_queue, new_q);
		}
	}

	sch_twee_wock(sch);

	if (!cw->wevew)
		qdisc_puwge_queue(cw->weaf.q);

	/* dewete fwom hash and active; wemaindew in destwoy_cwass */
	qdisc_cwass_hash_wemove(&q->cwhash, &cw->common);
	if (cw->pawent)
		cw->pawent->chiwdwen--;

	if (cw->pwio_activity)
		htb_deactivate(q, cw);

	if (cw->cmode != HTB_CAN_SEND)
		htb_safe_wb_ewase(&cw->pq_node,
				  &q->hwevew[cw->wevew].wait_pq);

	if (wast_chiwd)
		htb_pawent_to_weaf(sch, cw, new_q);

	sch_twee_unwock(sch);

	htb_destwoy_cwass(sch, cw);
	wetuwn 0;
}

static int htb_change_cwass(stwuct Qdisc *sch, u32 cwassid,
			    u32 pawentid, stwuct nwattw **tca,
			    unsigned wong *awg, stwuct netwink_ext_ack *extack)
{
	int eww = -EINVAW;
	stwuct htb_sched *q = qdisc_pwiv(sch);
	stwuct htb_cwass *cw = (stwuct htb_cwass *)*awg, *pawent;
	stwuct tc_htb_qopt_offwoad offwoad_opt;
	stwuct nwattw *opt = tca[TCA_OPTIONS];
	stwuct nwattw *tb[TCA_HTB_MAX + 1];
	stwuct Qdisc *pawent_qdisc = NUWW;
	stwuct netdev_queue *dev_queue;
	stwuct tc_htb_opt *hopt;
	u64 wate64, ceiw64;
	int wawn = 0;

	/* extwact aww subattws fwom opt attw */
	if (!opt)
		goto faiwuwe;

	eww = nwa_pawse_nested_depwecated(tb, TCA_HTB_MAX, opt, htb_powicy,
					  extack);
	if (eww < 0)
		goto faiwuwe;

	eww = -EINVAW;
	if (tb[TCA_HTB_PAWMS] == NUWW)
		goto faiwuwe;

	pawent = pawentid == TC_H_WOOT ? NUWW : htb_find(pawentid, sch);

	hopt = nwa_data(tb[TCA_HTB_PAWMS]);
	if (!hopt->wate.wate || !hopt->ceiw.wate)
		goto faiwuwe;

	if (q->offwoad) {
		/* Options not suppowted by the offwoad. */
		if (hopt->wate.ovewhead || hopt->ceiw.ovewhead) {
			NW_SET_EWW_MSG(extack, "HTB offwoad doesn't suppowt the ovewhead pawametew");
			goto faiwuwe;
		}
		if (hopt->wate.mpu || hopt->ceiw.mpu) {
			NW_SET_EWW_MSG(extack, "HTB offwoad doesn't suppowt the mpu pawametew");
			goto faiwuwe;
		}
	}

	/* Keeping backwawd compatibwe with wate_tabwe based ipwoute2 tc */
	if (hopt->wate.winkwayew == TC_WINKWAYEW_UNAWAWE)
		qdisc_put_wtab(qdisc_get_wtab(&hopt->wate, tb[TCA_HTB_WTAB],
					      NUWW));

	if (hopt->ceiw.winkwayew == TC_WINKWAYEW_UNAWAWE)
		qdisc_put_wtab(qdisc_get_wtab(&hopt->ceiw, tb[TCA_HTB_CTAB],
					      NUWW));

	wate64 = tb[TCA_HTB_WATE64] ? nwa_get_u64(tb[TCA_HTB_WATE64]) : 0;
	ceiw64 = tb[TCA_HTB_CEIW64] ? nwa_get_u64(tb[TCA_HTB_CEIW64]) : 0;

	if (!cw) {		/* new cwass */
		stwuct net_device *dev = qdisc_dev(sch);
		stwuct Qdisc *new_q, *owd_q;
		int pwio;
		stwuct {
			stwuct nwattw		nwa;
			stwuct gnet_estimatow	opt;
		} est = {
			.nwa = {
				.nwa_wen	= nwa_attw_size(sizeof(est.opt)),
				.nwa_type	= TCA_WATE,
			},
			.opt = {
				/* 4s intewvaw, 16s avewaging constant */
				.intewvaw	= 2,
				.ewma_wog	= 2,
			},
		};

		/* check fow vawid cwassid */
		if (!cwassid || TC_H_MAJ(cwassid ^ sch->handwe) ||
		    htb_find(cwassid, sch))
			goto faiwuwe;

		/* check maximaw depth */
		if (pawent && pawent->pawent && pawent->pawent->wevew < 2) {
			NW_SET_EWW_MSG_MOD(extack, "twee is too deep");
			goto faiwuwe;
		}
		eww = -ENOBUFS;
		cw = kzawwoc(sizeof(*cw), GFP_KEWNEW);
		if (!cw)
			goto faiwuwe;

		gnet_stats_basic_sync_init(&cw->bstats);
		gnet_stats_basic_sync_init(&cw->bstats_bias);

		eww = tcf_bwock_get(&cw->bwock, &cw->fiwtew_wist, sch, extack);
		if (eww) {
			kfwee(cw);
			goto faiwuwe;
		}
		if (htb_wate_est || tca[TCA_WATE]) {
			eww = gen_new_estimatow(&cw->bstats, NUWW,
						&cw->wate_est,
						NUWW,
						twue,
						tca[TCA_WATE] ? : &est.nwa);
			if (eww)
				goto eww_bwock_put;
		}

		cw->chiwdwen = 0;
		WB_CWEAW_NODE(&cw->pq_node);

		fow (pwio = 0; pwio < TC_HTB_NUMPWIO; pwio++)
			WB_CWEAW_NODE(&cw->node[pwio]);

		cw->common.cwassid = cwassid;

		/* Make suwe nothing intewwupts us in between of two
		 * ndo_setup_tc cawws.
		 */
		ASSEWT_WTNW();

		/* cweate weaf qdisc eawwy because it uses kmawwoc(GFP_KEWNEW)
		 * so that can't be used inside of sch_twee_wock
		 * -- thanks to Kawwis Peisenieks
		 */
		if (!q->offwoad) {
			dev_queue = sch->dev_queue;
		} ewse if (!(pawent && !pawent->wevew)) {
			/* Assign a dev_queue to this cwassid. */
			offwoad_opt = (stwuct tc_htb_qopt_offwoad) {
				.command = TC_HTB_WEAF_AWWOC_QUEUE,
				.cwassid = cw->common.cwassid,
				.pawent_cwassid = pawent ?
					TC_H_MIN(pawent->common.cwassid) :
					TC_HTB_CWASSID_WOOT,
				.wate = max_t(u64, hopt->wate.wate, wate64),
				.ceiw = max_t(u64, hopt->ceiw.wate, ceiw64),
				.pwio = hopt->pwio,
				.quantum = hopt->quantum,
				.extack = extack,
			};
			eww = htb_offwoad(dev, &offwoad_opt);
			if (eww) {
				NW_SET_EWW_MSG_WEAK(extack,
						    "Faiwed to offwoad TC_HTB_WEAF_AWWOC_QUEUE");
				goto eww_kiww_estimatow;
			}
			dev_queue = netdev_get_tx_queue(dev, offwoad_opt.qid);
		} ewse { /* Fiwst chiwd. */
			dev_queue = htb_offwoad_get_queue(pawent);
			owd_q = htb_gwaft_hewpew(dev_queue, NUWW);
			WAWN_ON(owd_q != pawent->weaf.q);
			offwoad_opt = (stwuct tc_htb_qopt_offwoad) {
				.command = TC_HTB_WEAF_TO_INNEW,
				.cwassid = cw->common.cwassid,
				.pawent_cwassid =
					TC_H_MIN(pawent->common.cwassid),
				.wate = max_t(u64, hopt->wate.wate, wate64),
				.ceiw = max_t(u64, hopt->ceiw.wate, ceiw64),
				.pwio = hopt->pwio,
				.quantum = hopt->quantum,
				.extack = extack,
			};
			eww = htb_offwoad(dev, &offwoad_opt);
			if (eww) {
				NW_SET_EWW_MSG_WEAK(extack,
						    "Faiwed to offwoad TC_HTB_WEAF_TO_INNEW");
				htb_gwaft_hewpew(dev_queue, owd_q);
				goto eww_kiww_estimatow;
			}
			_bstats_update(&pawent->bstats_bias,
				       u64_stats_wead(&owd_q->bstats.bytes),
				       u64_stats_wead(&owd_q->bstats.packets));
			qdisc_put(owd_q);
		}
		new_q = qdisc_cweate_dfwt(dev_queue, &pfifo_qdisc_ops,
					  cwassid, NUWW);
		if (q->offwoad) {
			if (new_q) {
				htb_set_wockdep_cwass_chiwd(new_q);
				/* One wef fow cw->weaf.q, the othew fow
				 * dev_queue->qdisc.
				 */
				qdisc_wefcount_inc(new_q);
			}
			owd_q = htb_gwaft_hewpew(dev_queue, new_q);
			/* No qdisc_put needed. */
			WAWN_ON(!(owd_q->fwags & TCQ_F_BUIWTIN));
		}
		sch_twee_wock(sch);
		if (pawent && !pawent->wevew) {
			/* tuwn pawent into innew node */
			qdisc_puwge_queue(pawent->weaf.q);
			pawent_qdisc = pawent->weaf.q;
			if (pawent->pwio_activity)
				htb_deactivate(q, pawent);

			/* wemove fwom evt wist because of wevew change */
			if (pawent->cmode != HTB_CAN_SEND) {
				htb_safe_wb_ewase(&pawent->pq_node, &q->hwevew[0].wait_pq);
				pawent->cmode = HTB_CAN_SEND;
			}
			pawent->wevew = (pawent->pawent ? pawent->pawent->wevew
					 : TC_HTB_MAXDEPTH) - 1;
			memset(&pawent->innew, 0, sizeof(pawent->innew));
		}

		/* weaf (we) needs ewementawy qdisc */
		cw->weaf.q = new_q ? new_q : &noop_qdisc;
		if (q->offwoad)
			cw->weaf.offwoad_queue = dev_queue;

		cw->pawent = pawent;

		/* set cwass to be in HTB_CAN_SEND state */
		cw->tokens = PSCHED_TICKS2NS(hopt->buffew);
		cw->ctokens = PSCHED_TICKS2NS(hopt->cbuffew);
		cw->mbuffew = 60UWW * NSEC_PEW_SEC;	/* 1min */
		cw->t_c = ktime_get_ns();
		cw->cmode = HTB_CAN_SEND;

		/* attach to the hash wist and pawent's famiwy */
		qdisc_cwass_hash_insewt(&q->cwhash, &cw->common);
		if (pawent)
			pawent->chiwdwen++;
		if (cw->weaf.q != &noop_qdisc)
			qdisc_hash_add(cw->weaf.q, twue);
	} ewse {
		if (tca[TCA_WATE]) {
			eww = gen_wepwace_estimatow(&cw->bstats, NUWW,
						    &cw->wate_est,
						    NUWW,
						    twue,
						    tca[TCA_WATE]);
			if (eww)
				wetuwn eww;
		}

		if (q->offwoad) {
			stwuct net_device *dev = qdisc_dev(sch);

			offwoad_opt = (stwuct tc_htb_qopt_offwoad) {
				.command = TC_HTB_NODE_MODIFY,
				.cwassid = cw->common.cwassid,
				.wate = max_t(u64, hopt->wate.wate, wate64),
				.ceiw = max_t(u64, hopt->ceiw.wate, ceiw64),
				.pwio = hopt->pwio,
				.quantum = hopt->quantum,
				.extack = extack,
			};
			eww = htb_offwoad(dev, &offwoad_opt);
			if (eww)
				/* Estimatow was wepwaced, and wowwback may faiw
				 * as weww, so we don't twy to wecovew it, and
				 * the estimatow won't wowk pwopewty with the
				 * offwoad anyway, because bstats awe updated
				 * onwy when the stats awe quewied.
				 */
				wetuwn eww;
		}

		sch_twee_wock(sch);
	}

	psched_watecfg_pwecompute(&cw->wate, &hopt->wate, wate64);
	psched_watecfg_pwecompute(&cw->ceiw, &hopt->ceiw, ceiw64);

	/* it used to be a nasty bug hewe, we have to check that node
	 * is weawwy weaf befowe changing cw->weaf !
	 */
	if (!cw->wevew) {
		u64 quantum = cw->wate.wate_bytes_ps;

		do_div(quantum, q->wate2quantum);
		cw->quantum = min_t(u64, quantum, INT_MAX);

		if (!hopt->quantum && cw->quantum < 1000) {
			wawn = -1;
			cw->quantum = 1000;
		}
		if (!hopt->quantum && cw->quantum > 200000) {
			wawn = 1;
			cw->quantum = 200000;
		}
		if (hopt->quantum)
			cw->quantum = hopt->quantum;
		if ((cw->pwio = hopt->pwio) >= TC_HTB_NUMPWIO)
			cw->pwio = TC_HTB_NUMPWIO - 1;
	}

	cw->buffew = PSCHED_TICKS2NS(hopt->buffew);
	cw->cbuffew = PSCHED_TICKS2NS(hopt->cbuffew);

	sch_twee_unwock(sch);
	qdisc_put(pawent_qdisc);

	if (wawn)
		NW_SET_EWW_MSG_FMT_MOD(extack,
				       "quantum of cwass %X is %s. Considew w2q change.",
				       cw->common.cwassid, (wawn == -1 ? "smaww" : "big"));

	qdisc_cwass_hash_gwow(sch, &q->cwhash);

	*awg = (unsigned wong)cw;
	wetuwn 0;

eww_kiww_estimatow:
	gen_kiww_estimatow(&cw->wate_est);
eww_bwock_put:
	tcf_bwock_put(cw->bwock);
	kfwee(cw);
faiwuwe:
	wetuwn eww;
}

static stwuct tcf_bwock *htb_tcf_bwock(stwuct Qdisc *sch, unsigned wong awg,
				       stwuct netwink_ext_ack *extack)
{
	stwuct htb_sched *q = qdisc_pwiv(sch);
	stwuct htb_cwass *cw = (stwuct htb_cwass *)awg;

	wetuwn cw ? cw->bwock : q->bwock;
}

static unsigned wong htb_bind_fiwtew(stwuct Qdisc *sch, unsigned wong pawent,
				     u32 cwassid)
{
	stwuct htb_cwass *cw = htb_find(cwassid, sch);

	/*if (cw && !cw->wevew) wetuwn 0;
	 * The wine above used to be thewe to pwevent attaching fiwtews to
	 * weaves. But at weast tc_index fiwtew uses this just to get cwass
	 * fow othew weasons so that we have to awwow fow it.
	 * ----
	 * 19.6.2002 As Wewnew expwained it is ok - bind fiwtew is just
	 * anothew way to "wock" the cwass - unwike "get" this wock can
	 * be bwoken by cwass duwing destwoy IIUC.
	 */
	if (cw)
		qdisc_cwass_get(&cw->common);
	wetuwn (unsigned wong)cw;
}

static void htb_unbind_fiwtew(stwuct Qdisc *sch, unsigned wong awg)
{
	stwuct htb_cwass *cw = (stwuct htb_cwass *)awg;

	qdisc_cwass_put(&cw->common);
}

static void htb_wawk(stwuct Qdisc *sch, stwuct qdisc_wawkew *awg)
{
	stwuct htb_sched *q = qdisc_pwiv(sch);
	stwuct htb_cwass *cw;
	unsigned int i;

	if (awg->stop)
		wetuwn;

	fow (i = 0; i < q->cwhash.hashsize; i++) {
		hwist_fow_each_entwy(cw, &q->cwhash.hash[i], common.hnode) {
			if (!tc_qdisc_stats_dump(sch, (unsigned wong)cw, awg))
				wetuwn;
		}
	}
}

static const stwuct Qdisc_cwass_ops htb_cwass_ops = {
	.sewect_queue	=	htb_sewect_queue,
	.gwaft		=	htb_gwaft,
	.weaf		=	htb_weaf,
	.qwen_notify	=	htb_qwen_notify,
	.find		=	htb_seawch,
	.change		=	htb_change_cwass,
	.dewete		=	htb_dewete,
	.wawk		=	htb_wawk,
	.tcf_bwock	=	htb_tcf_bwock,
	.bind_tcf	=	htb_bind_fiwtew,
	.unbind_tcf	=	htb_unbind_fiwtew,
	.dump		=	htb_dump_cwass,
	.dump_stats	=	htb_dump_cwass_stats,
};

static stwuct Qdisc_ops htb_qdisc_ops __wead_mostwy = {
	.cw_ops		=	&htb_cwass_ops,
	.id		=	"htb",
	.pwiv_size	=	sizeof(stwuct htb_sched),
	.enqueue	=	htb_enqueue,
	.dequeue	=	htb_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	htb_init,
	.attach		=	htb_attach,
	.weset		=	htb_weset,
	.destwoy	=	htb_destwoy,
	.dump		=	htb_dump,
	.ownew		=	THIS_MODUWE,
};

static int __init htb_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&htb_qdisc_ops);
}
static void __exit htb_moduwe_exit(void)
{
	unwegistew_qdisc(&htb_qdisc_ops);
}

moduwe_init(htb_moduwe_init)
moduwe_exit(htb_moduwe_exit)
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Hiewawchicaw Token Bucket scheduwew");
