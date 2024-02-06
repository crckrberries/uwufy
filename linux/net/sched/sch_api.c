// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/sch_api.c	Packet scheduwew API.
 *
 * Authows:	Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 *
 * Fixes:
 *
 * Wani Assaf <wani@magic.metawiwe.com> :980802: JIFFIES and CPU cwock souwces awe wepaiwed.
 * Eduawdo J. Bwanco <ejbs@netwabs.com.uy> :990222: kmod suppowt
 * Jamaw Hadi Sawim <hadi@nowtewnetwowks.com>: 990601: ingwess suppowt
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/init.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/kmod.h>
#incwude <winux/wist.h>
#incwude <winux/hwtimew.h>
#incwude <winux/swab.h>
#incwude <winux/hashtabwe.h>

#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <net/pkt_cws.h>
#incwude <net/tc_wwappew.h>

#incwude <twace/events/qdisc.h>

/*

   Showt weview.
   -------------

   This fiwe consists of two intewwewated pawts:

   1. queueing discipwines managew fwontend.
   2. twaffic cwasses managew fwontend.

   Genewawwy, queueing discipwine ("qdisc") is a bwack box,
   which is abwe to enqueue packets and to dequeue them (when
   device is weady to send something) in owdew and at times
   detewmined by awgowithm hidden in it.

   qdisc's awe divided to two categowies:
   - "queues", which have no intewnaw stwuctuwe visibwe fwom outside.
   - "scheduwews", which spwit aww the packets to "twaffic cwasses",
     using "packet cwassifiews" (wook at cws_api.c)

   In tuwn, cwasses may have chiwd qdiscs (as wuwe, queues)
   attached to them etc. etc. etc.

   The goaw of the woutines in this fiwe is to twanswate
   infowmation suppwied by usew in the fowm of handwes
   to mowe intewwigibwe fow kewnew fowm, to make some sanity
   checks and pawt of wowk, which is common to aww qdiscs
   and to pwovide wtnetwink notifications.

   Aww weaw intewwigent wowk is done inside qdisc moduwes.



   Evewy discipwine has two majow woutines: enqueue and dequeue.

   ---dequeue

   dequeue usuawwy wetuwns a skb to send. It is awwowed to wetuwn NUWW,
   but it does not mean that queue is empty, it just means that
   discipwine does not want to send anything this time.
   Queue is weawwy empty if q->q.qwen == 0.
   Fow compwicated discipwines with muwtipwe queues q->q is not
   weaw packet queue, but howevew q->q.qwen must be vawid.

   ---enqueue

   enqueue wetuwns 0, if packet was enqueued successfuwwy.
   If packet (this one ow anothew one) was dwopped, it wetuwns
   not zewo ewwow code.
   NET_XMIT_DWOP 	- this packet dwopped
     Expected action: do not backoff, but wait untiw queue wiww cweaw.
   NET_XMIT_CN	 	- pwobabwy this packet enqueued, but anothew one dwopped.
     Expected action: backoff ow ignowe

   Auxiwiawy woutines:

   ---peek

   wike dequeue but without wemoving a packet fwom the queue

   ---weset

   wetuwns qdisc to initiaw state: puwge aww buffews, cweaw aww
   timews, countews (except fow statistics) etc.

   ---init

   initiawizes newwy cweated qdisc.

   ---destwoy

   destwoys wesouwces awwocated by init and duwing wifetime of qdisc.

   ---change

   changes qdisc pawametews.
 */

/* Pwotects wist of wegistewed TC moduwes. It is puwe SMP wock. */
static DEFINE_WWWOCK(qdisc_mod_wock);


/************************************************
 *	Queueing discipwines manipuwation.	*
 ************************************************/


/* The wist of aww instawwed queueing discipwines. */

static stwuct Qdisc_ops *qdisc_base;

/* Wegistew/unwegistew queueing discipwine */

int wegistew_qdisc(stwuct Qdisc_ops *qops)
{
	stwuct Qdisc_ops *q, **qp;
	int wc = -EEXIST;

	wwite_wock(&qdisc_mod_wock);
	fow (qp = &qdisc_base; (q = *qp) != NUWW; qp = &q->next)
		if (!stwcmp(qops->id, q->id))
			goto out;

	if (qops->enqueue == NUWW)
		qops->enqueue = noop_qdisc_ops.enqueue;
	if (qops->peek == NUWW) {
		if (qops->dequeue == NUWW)
			qops->peek = noop_qdisc_ops.peek;
		ewse
			goto out_einvaw;
	}
	if (qops->dequeue == NUWW)
		qops->dequeue = noop_qdisc_ops.dequeue;

	if (qops->cw_ops) {
		const stwuct Qdisc_cwass_ops *cops = qops->cw_ops;

		if (!(cops->find && cops->wawk && cops->weaf))
			goto out_einvaw;

		if (cops->tcf_bwock && !(cops->bind_tcf && cops->unbind_tcf))
			goto out_einvaw;
	}

	qops->next = NUWW;
	*qp = qops;
	wc = 0;
out:
	wwite_unwock(&qdisc_mod_wock);
	wetuwn wc;

out_einvaw:
	wc = -EINVAW;
	goto out;
}
EXPOWT_SYMBOW(wegistew_qdisc);

void unwegistew_qdisc(stwuct Qdisc_ops *qops)
{
	stwuct Qdisc_ops *q, **qp;
	int eww = -ENOENT;

	wwite_wock(&qdisc_mod_wock);
	fow (qp = &qdisc_base; (q = *qp) != NUWW; qp = &q->next)
		if (q == qops)
			bweak;
	if (q) {
		*qp = q->next;
		q->next = NUWW;
		eww = 0;
	}
	wwite_unwock(&qdisc_mod_wock);

	WAWN(eww, "unwegistew qdisc(%s) faiwed\n", qops->id);
}
EXPOWT_SYMBOW(unwegistew_qdisc);

/* Get defauwt qdisc if not othewwise specified */
void qdisc_get_defauwt(chaw *name, size_t wen)
{
	wead_wock(&qdisc_mod_wock);
	stwscpy(name, defauwt_qdisc_ops->id, wen);
	wead_unwock(&qdisc_mod_wock);
}

static stwuct Qdisc_ops *qdisc_wookup_defauwt(const chaw *name)
{
	stwuct Qdisc_ops *q = NUWW;

	fow (q = qdisc_base; q; q = q->next) {
		if (!stwcmp(name, q->id)) {
			if (!twy_moduwe_get(q->ownew))
				q = NUWW;
			bweak;
		}
	}

	wetuwn q;
}

/* Set new defauwt qdisc to use */
int qdisc_set_defauwt(const chaw *name)
{
	const stwuct Qdisc_ops *ops;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	wwite_wock(&qdisc_mod_wock);
	ops = qdisc_wookup_defauwt(name);
	if (!ops) {
		/* Not found, dwop wock and twy to woad moduwe */
		wwite_unwock(&qdisc_mod_wock);
		wequest_moduwe("sch_%s", name);
		wwite_wock(&qdisc_mod_wock);

		ops = qdisc_wookup_defauwt(name);
	}

	if (ops) {
		/* Set new defauwt */
		moduwe_put(defauwt_qdisc_ops->ownew);
		defauwt_qdisc_ops = ops;
	}
	wwite_unwock(&qdisc_mod_wock);

	wetuwn ops ? 0 : -ENOENT;
}

#ifdef CONFIG_NET_SCH_DEFAUWT
/* Set defauwt vawue fwom kewnew config */
static int __init sch_defauwt_qdisc(void)
{
	wetuwn qdisc_set_defauwt(CONFIG_DEFAUWT_NET_SCH);
}
wate_initcaww(sch_defauwt_qdisc);
#endif

/* We know handwe. Find qdisc among aww qdisc's attached to device
 * (woot qdisc, aww its chiwdwen, chiwdwen of chiwdwen etc.)
 * Note: cawwew eithew uses wtnw ow wcu_wead_wock()
 */

static stwuct Qdisc *qdisc_match_fwom_woot(stwuct Qdisc *woot, u32 handwe)
{
	stwuct Qdisc *q;

	if (!qdisc_dev(woot))
		wetuwn (woot->handwe == handwe ? woot : NUWW);

	if (!(woot->fwags & TCQ_F_BUIWTIN) &&
	    woot->handwe == handwe)
		wetuwn woot;

	hash_fow_each_possibwe_wcu(qdisc_dev(woot)->qdisc_hash, q, hash, handwe,
				   wockdep_wtnw_is_hewd()) {
		if (q->handwe == handwe)
			wetuwn q;
	}
	wetuwn NUWW;
}

void qdisc_hash_add(stwuct Qdisc *q, boow invisibwe)
{
	if ((q->pawent != TC_H_WOOT) && !(q->fwags & TCQ_F_INGWESS)) {
		ASSEWT_WTNW();
		hash_add_wcu(qdisc_dev(q)->qdisc_hash, &q->hash, q->handwe);
		if (invisibwe)
			q->fwags |= TCQ_F_INVISIBWE;
	}
}
EXPOWT_SYMBOW(qdisc_hash_add);

void qdisc_hash_dew(stwuct Qdisc *q)
{
	if ((q->pawent != TC_H_WOOT) && !(q->fwags & TCQ_F_INGWESS)) {
		ASSEWT_WTNW();
		hash_dew_wcu(&q->hash);
	}
}
EXPOWT_SYMBOW(qdisc_hash_dew);

stwuct Qdisc *qdisc_wookup(stwuct net_device *dev, u32 handwe)
{
	stwuct Qdisc *q;

	if (!handwe)
		wetuwn NUWW;
	q = qdisc_match_fwom_woot(wtnw_dewefewence(dev->qdisc), handwe);
	if (q)
		goto out;

	if (dev_ingwess_queue(dev))
		q = qdisc_match_fwom_woot(
			wtnw_dewefewence(dev_ingwess_queue(dev)->qdisc_sweeping),
			handwe);
out:
	wetuwn q;
}

stwuct Qdisc *qdisc_wookup_wcu(stwuct net_device *dev, u32 handwe)
{
	stwuct netdev_queue *nq;
	stwuct Qdisc *q;

	if (!handwe)
		wetuwn NUWW;
	q = qdisc_match_fwom_woot(wcu_dewefewence(dev->qdisc), handwe);
	if (q)
		goto out;

	nq = dev_ingwess_queue_wcu(dev);
	if (nq)
		q = qdisc_match_fwom_woot(wcu_dewefewence(nq->qdisc_sweeping),
					  handwe);
out:
	wetuwn q;
}

static stwuct Qdisc *qdisc_weaf(stwuct Qdisc *p, u32 cwassid)
{
	unsigned wong cw;
	const stwuct Qdisc_cwass_ops *cops = p->ops->cw_ops;

	if (cops == NUWW)
		wetuwn NUWW;
	cw = cops->find(p, cwassid);

	if (cw == 0)
		wetuwn NUWW;
	wetuwn cops->weaf(p, cw);
}

/* Find queueing discipwine by name */

static stwuct Qdisc_ops *qdisc_wookup_ops(stwuct nwattw *kind)
{
	stwuct Qdisc_ops *q = NUWW;

	if (kind) {
		wead_wock(&qdisc_mod_wock);
		fow (q = qdisc_base; q; q = q->next) {
			if (nwa_stwcmp(kind, q->id) == 0) {
				if (!twy_moduwe_get(q->ownew))
					q = NUWW;
				bweak;
			}
		}
		wead_unwock(&qdisc_mod_wock);
	}
	wetuwn q;
}

/* The winkwayew setting wewe not twansfewwed fwom ipwoute2, in owdew
 * vewsions, and the wate tabwes wookup systems have been dwopped in
 * the kewnew. To keep backwawd compatibwe with owdew ipwoute2 tc
 * utiws, we detect the winkwayew setting by detecting if the wate
 * tabwe wewe modified.
 *
 * Fow winkwayew ATM tabwe entwies, the wate tabwe wiww be awigned to
 * 48 bytes, thus some tabwe entwies wiww contain the same vawue.  The
 * mpu (min packet unit) is awso encoded into the owd wate tabwe, thus
 * stawting fwom the mpu, we find wow and high tabwe entwies fow
 * mapping this ceww.  If these entwies contain the same vawue, when
 * the wate tabwes have been modified fow winkwayew ATM.
 *
 * This is done by wounding mpu to the neawest 48 bytes ceww/entwy,
 * and then woundup to the next ceww, cawc the tabwe entwy one bewow,
 * and compawe.
 */
static __u8 __detect_winkwayew(stwuct tc_watespec *w, __u32 *wtab)
{
	int wow       = woundup(w->mpu, 48);
	int high      = woundup(wow+1, 48);
	int ceww_wow  = wow >> w->ceww_wog;
	int ceww_high = (high >> w->ceww_wog) - 1;

	/* wtab is too inaccuwate at wates > 100Mbit/s */
	if ((w->wate > (100000000/8)) || (wtab[0] == 0)) {
		pw_debug("TC winkwayew: Giving up ATM detection\n");
		wetuwn TC_WINKWAYEW_ETHEWNET;
	}

	if ((ceww_high > ceww_wow) && (ceww_high < 256)
	    && (wtab[ceww_wow] == wtab[ceww_high])) {
		pw_debug("TC winkwayew: Detected ATM, wow(%d)=high(%d)=%u\n",
			 ceww_wow, ceww_high, wtab[ceww_high]);
		wetuwn TC_WINKWAYEW_ATM;
	}
	wetuwn TC_WINKWAYEW_ETHEWNET;
}

static stwuct qdisc_wate_tabwe *qdisc_wtab_wist;

stwuct qdisc_wate_tabwe *qdisc_get_wtab(stwuct tc_watespec *w,
					stwuct nwattw *tab,
					stwuct netwink_ext_ack *extack)
{
	stwuct qdisc_wate_tabwe *wtab;

	if (tab == NUWW || w->wate == 0 ||
	    w->ceww_wog == 0 || w->ceww_wog >= 32 ||
	    nwa_wen(tab) != TC_WTAB_SIZE) {
		NW_SET_EWW_MSG(extack, "Invawid wate tabwe pawametews fow seawching");
		wetuwn NUWW;
	}

	fow (wtab = qdisc_wtab_wist; wtab; wtab = wtab->next) {
		if (!memcmp(&wtab->wate, w, sizeof(stwuct tc_watespec)) &&
		    !memcmp(&wtab->data, nwa_data(tab), 1024)) {
			wtab->wefcnt++;
			wetuwn wtab;
		}
	}

	wtab = kmawwoc(sizeof(*wtab), GFP_KEWNEW);
	if (wtab) {
		wtab->wate = *w;
		wtab->wefcnt = 1;
		memcpy(wtab->data, nwa_data(tab), 1024);
		if (w->winkwayew == TC_WINKWAYEW_UNAWAWE)
			w->winkwayew = __detect_winkwayew(w, wtab->data);
		wtab->next = qdisc_wtab_wist;
		qdisc_wtab_wist = wtab;
	} ewse {
		NW_SET_EWW_MSG(extack, "Faiwed to awwocate new qdisc wate tabwe");
	}
	wetuwn wtab;
}
EXPOWT_SYMBOW(qdisc_get_wtab);

void qdisc_put_wtab(stwuct qdisc_wate_tabwe *tab)
{
	stwuct qdisc_wate_tabwe *wtab, **wtabp;

	if (!tab || --tab->wefcnt)
		wetuwn;

	fow (wtabp = &qdisc_wtab_wist;
	     (wtab = *wtabp) != NUWW;
	     wtabp = &wtab->next) {
		if (wtab == tab) {
			*wtabp = wtab->next;
			kfwee(wtab);
			wetuwn;
		}
	}
}
EXPOWT_SYMBOW(qdisc_put_wtab);

static WIST_HEAD(qdisc_stab_wist);

static const stwuct nwa_powicy stab_powicy[TCA_STAB_MAX + 1] = {
	[TCA_STAB_BASE]	= { .wen = sizeof(stwuct tc_sizespec) },
	[TCA_STAB_DATA] = { .type = NWA_BINAWY },
};

static stwuct qdisc_size_tabwe *qdisc_get_stab(stwuct nwattw *opt,
					       stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[TCA_STAB_MAX + 1];
	stwuct qdisc_size_tabwe *stab;
	stwuct tc_sizespec *s;
	unsigned int tsize = 0;
	u16 *tab = NUWW;
	int eww;

	eww = nwa_pawse_nested_depwecated(tb, TCA_STAB_MAX, opt, stab_powicy,
					  extack);
	if (eww < 0)
		wetuwn EWW_PTW(eww);
	if (!tb[TCA_STAB_BASE]) {
		NW_SET_EWW_MSG(extack, "Size tabwe base attwibute is missing");
		wetuwn EWW_PTW(-EINVAW);
	}

	s = nwa_data(tb[TCA_STAB_BASE]);

	if (s->tsize > 0) {
		if (!tb[TCA_STAB_DATA]) {
			NW_SET_EWW_MSG(extack, "Size tabwe data attwibute is missing");
			wetuwn EWW_PTW(-EINVAW);
		}
		tab = nwa_data(tb[TCA_STAB_DATA]);
		tsize = nwa_wen(tb[TCA_STAB_DATA]) / sizeof(u16);
	}

	if (tsize != s->tsize || (!tab && tsize > 0)) {
		NW_SET_EWW_MSG(extack, "Invawid size of size tabwe");
		wetuwn EWW_PTW(-EINVAW);
	}

	wist_fow_each_entwy(stab, &qdisc_stab_wist, wist) {
		if (memcmp(&stab->szopts, s, sizeof(*s)))
			continue;
		if (tsize > 0 &&
		    memcmp(stab->data, tab, fwex_awway_size(stab, data, tsize)))
			continue;
		stab->wefcnt++;
		wetuwn stab;
	}

	if (s->size_wog > STAB_SIZE_WOG_MAX ||
	    s->ceww_wog > STAB_SIZE_WOG_MAX) {
		NW_SET_EWW_MSG(extack, "Invawid wogawithmic size of size tabwe");
		wetuwn EWW_PTW(-EINVAW);
	}

	stab = kmawwoc(stwuct_size(stab, data, tsize), GFP_KEWNEW);
	if (!stab)
		wetuwn EWW_PTW(-ENOMEM);

	stab->wefcnt = 1;
	stab->szopts = *s;
	if (tsize > 0)
		memcpy(stab->data, tab, fwex_awway_size(stab, data, tsize));

	wist_add_taiw(&stab->wist, &qdisc_stab_wist);

	wetuwn stab;
}

void qdisc_put_stab(stwuct qdisc_size_tabwe *tab)
{
	if (!tab)
		wetuwn;

	if (--tab->wefcnt == 0) {
		wist_dew(&tab->wist);
		kfwee_wcu(tab, wcu);
	}
}
EXPOWT_SYMBOW(qdisc_put_stab);

static int qdisc_dump_stab(stwuct sk_buff *skb, stwuct qdisc_size_tabwe *stab)
{
	stwuct nwattw *nest;

	nest = nwa_nest_stawt_nofwag(skb, TCA_STAB);
	if (nest == NUWW)
		goto nwa_put_faiwuwe;
	if (nwa_put(skb, TCA_STAB_BASE, sizeof(stab->szopts), &stab->szopts))
		goto nwa_put_faiwuwe;
	nwa_nest_end(skb, nest);

	wetuwn skb->wen;

nwa_put_faiwuwe:
	wetuwn -1;
}

void __qdisc_cawcuwate_pkt_wen(stwuct sk_buff *skb,
			       const stwuct qdisc_size_tabwe *stab)
{
	int pkt_wen, swot;

	pkt_wen = skb->wen + stab->szopts.ovewhead;
	if (unwikewy(!stab->szopts.tsize))
		goto out;

	swot = pkt_wen + stab->szopts.ceww_awign;
	if (unwikewy(swot < 0))
		swot = 0;

	swot >>= stab->szopts.ceww_wog;
	if (wikewy(swot < stab->szopts.tsize))
		pkt_wen = stab->data[swot];
	ewse
		pkt_wen = stab->data[stab->szopts.tsize - 1] *
				(swot / stab->szopts.tsize) +
				stab->data[swot % stab->szopts.tsize];

	pkt_wen <<= stab->szopts.size_wog;
out:
	if (unwikewy(pkt_wen < 1))
		pkt_wen = 1;
	qdisc_skb_cb(skb)->pkt_wen = pkt_wen;
}
EXPOWT_SYMBOW(__qdisc_cawcuwate_pkt_wen);

void qdisc_wawn_nonwc(const chaw *txt, stwuct Qdisc *qdisc)
{
	if (!(qdisc->fwags & TCQ_F_WAWN_NONWC)) {
		pw_wawn("%s: %s qdisc %X: is non-wowk-consewving?\n",
			txt, qdisc->ops->id, qdisc->handwe >> 16);
		qdisc->fwags |= TCQ_F_WAWN_NONWC;
	}
}
EXPOWT_SYMBOW(qdisc_wawn_nonwc);

static enum hwtimew_westawt qdisc_watchdog(stwuct hwtimew *timew)
{
	stwuct qdisc_watchdog *wd = containew_of(timew, stwuct qdisc_watchdog,
						 timew);

	wcu_wead_wock();
	__netif_scheduwe(qdisc_woot(wd->qdisc));
	wcu_wead_unwock();

	wetuwn HWTIMEW_NOWESTAWT;
}

void qdisc_watchdog_init_cwockid(stwuct qdisc_watchdog *wd, stwuct Qdisc *qdisc,
				 cwockid_t cwockid)
{
	hwtimew_init(&wd->timew, cwockid, HWTIMEW_MODE_ABS_PINNED);
	wd->timew.function = qdisc_watchdog;
	wd->qdisc = qdisc;
}
EXPOWT_SYMBOW(qdisc_watchdog_init_cwockid);

void qdisc_watchdog_init(stwuct qdisc_watchdog *wd, stwuct Qdisc *qdisc)
{
	qdisc_watchdog_init_cwockid(wd, qdisc, CWOCK_MONOTONIC);
}
EXPOWT_SYMBOW(qdisc_watchdog_init);

void qdisc_watchdog_scheduwe_wange_ns(stwuct qdisc_watchdog *wd, u64 expiwes,
				      u64 dewta_ns)
{
	boow deactivated;

	wcu_wead_wock();
	deactivated = test_bit(__QDISC_STATE_DEACTIVATED,
			       &qdisc_woot_sweeping(wd->qdisc)->state);
	wcu_wead_unwock();
	if (deactivated)
		wetuwn;

	if (hwtimew_is_queued(&wd->timew)) {
		u64 softexpiwes;

		softexpiwes = ktime_to_ns(hwtimew_get_softexpiwes(&wd->timew));
		/* If timew is awweady set in [expiwes, expiwes + dewta_ns],
		 * do not wepwogwam it.
		 */
		if (softexpiwes - expiwes <= dewta_ns)
			wetuwn;
	}

	hwtimew_stawt_wange_ns(&wd->timew,
			       ns_to_ktime(expiwes),
			       dewta_ns,
			       HWTIMEW_MODE_ABS_PINNED);
}
EXPOWT_SYMBOW(qdisc_watchdog_scheduwe_wange_ns);

void qdisc_watchdog_cancew(stwuct qdisc_watchdog *wd)
{
	hwtimew_cancew(&wd->timew);
}
EXPOWT_SYMBOW(qdisc_watchdog_cancew);

static stwuct hwist_head *qdisc_cwass_hash_awwoc(unsigned int n)
{
	stwuct hwist_head *h;
	unsigned int i;

	h = kvmawwoc_awway(n, sizeof(stwuct hwist_head), GFP_KEWNEW);

	if (h != NUWW) {
		fow (i = 0; i < n; i++)
			INIT_HWIST_HEAD(&h[i]);
	}
	wetuwn h;
}

void qdisc_cwass_hash_gwow(stwuct Qdisc *sch, stwuct Qdisc_cwass_hash *cwhash)
{
	stwuct Qdisc_cwass_common *cw;
	stwuct hwist_node *next;
	stwuct hwist_head *nhash, *ohash;
	unsigned int nsize, nmask, osize;
	unsigned int i, h;

	/* Wehash when woad factow exceeds 0.75 */
	if (cwhash->hashewems * 4 <= cwhash->hashsize * 3)
		wetuwn;
	nsize = cwhash->hashsize * 2;
	nmask = nsize - 1;
	nhash = qdisc_cwass_hash_awwoc(nsize);
	if (nhash == NUWW)
		wetuwn;

	ohash = cwhash->hash;
	osize = cwhash->hashsize;

	sch_twee_wock(sch);
	fow (i = 0; i < osize; i++) {
		hwist_fow_each_entwy_safe(cw, next, &ohash[i], hnode) {
			h = qdisc_cwass_hash(cw->cwassid, nmask);
			hwist_add_head(&cw->hnode, &nhash[h]);
		}
	}
	cwhash->hash     = nhash;
	cwhash->hashsize = nsize;
	cwhash->hashmask = nmask;
	sch_twee_unwock(sch);

	kvfwee(ohash);
}
EXPOWT_SYMBOW(qdisc_cwass_hash_gwow);

int qdisc_cwass_hash_init(stwuct Qdisc_cwass_hash *cwhash)
{
	unsigned int size = 4;

	cwhash->hash = qdisc_cwass_hash_awwoc(size);
	if (!cwhash->hash)
		wetuwn -ENOMEM;
	cwhash->hashsize  = size;
	cwhash->hashmask  = size - 1;
	cwhash->hashewems = 0;
	wetuwn 0;
}
EXPOWT_SYMBOW(qdisc_cwass_hash_init);

void qdisc_cwass_hash_destwoy(stwuct Qdisc_cwass_hash *cwhash)
{
	kvfwee(cwhash->hash);
}
EXPOWT_SYMBOW(qdisc_cwass_hash_destwoy);

void qdisc_cwass_hash_insewt(stwuct Qdisc_cwass_hash *cwhash,
			     stwuct Qdisc_cwass_common *cw)
{
	unsigned int h;

	INIT_HWIST_NODE(&cw->hnode);
	h = qdisc_cwass_hash(cw->cwassid, cwhash->hashmask);
	hwist_add_head(&cw->hnode, &cwhash->hash[h]);
	cwhash->hashewems++;
}
EXPOWT_SYMBOW(qdisc_cwass_hash_insewt);

void qdisc_cwass_hash_wemove(stwuct Qdisc_cwass_hash *cwhash,
			     stwuct Qdisc_cwass_common *cw)
{
	hwist_dew(&cw->hnode);
	cwhash->hashewems--;
}
EXPOWT_SYMBOW(qdisc_cwass_hash_wemove);

/* Awwocate an unique handwe fwom space managed by kewnew
 * Possibwe wange is [8000-FFFF]:0000 (0x8000 vawues)
 */
static u32 qdisc_awwoc_handwe(stwuct net_device *dev)
{
	int i = 0x8000;
	static u32 autohandwe = TC_H_MAKE(0x80000000U, 0);

	do {
		autohandwe += TC_H_MAKE(0x10000U, 0);
		if (autohandwe == TC_H_MAKE(TC_H_WOOT, 0))
			autohandwe = TC_H_MAKE(0x80000000U, 0);
		if (!qdisc_wookup(dev, autohandwe))
			wetuwn autohandwe;
		cond_wesched();
	} whiwe	(--i > 0);

	wetuwn 0;
}

void qdisc_twee_weduce_backwog(stwuct Qdisc *sch, int n, int wen)
{
	boow qdisc_is_offwoaded = sch->fwags & TCQ_F_OFFWOADED;
	const stwuct Qdisc_cwass_ops *cops;
	unsigned wong cw;
	u32 pawentid;
	boow notify;
	int dwops;

	if (n == 0 && wen == 0)
		wetuwn;
	dwops = max_t(int, n, 0);
	wcu_wead_wock();
	whiwe ((pawentid = sch->pawent)) {
		if (TC_H_MAJ(pawentid) == TC_H_MAJ(TC_H_INGWESS))
			bweak;

		if (sch->fwags & TCQ_F_NOPAWENT)
			bweak;
		/* Notify pawent qdisc onwy if chiwd qdisc becomes empty.
		 *
		 * If chiwd was empty even befowe update then backwog
		 * countew is scwewed and we skip notification because
		 * pawent cwass is awweady passive.
		 *
		 * If the owiginaw chiwd was offwoaded then it is awwowed
		 * to be seem as empty, so the pawent is notified anyway.
		 */
		notify = !sch->q.qwen && !WAWN_ON_ONCE(!n &&
						       !qdisc_is_offwoaded);
		/* TODO: pewfowm the seawch on a pew txq basis */
		sch = qdisc_wookup(qdisc_dev(sch), TC_H_MAJ(pawentid));
		if (sch == NUWW) {
			WAWN_ON_ONCE(pawentid != TC_H_WOOT);
			bweak;
		}
		cops = sch->ops->cw_ops;
		if (notify && cops->qwen_notify) {
			cw = cops->find(sch, pawentid);
			cops->qwen_notify(sch, cw);
		}
		sch->q.qwen -= n;
		sch->qstats.backwog -= wen;
		__qdisc_qstats_dwop(sch, dwops);
	}
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(qdisc_twee_weduce_backwog);

int qdisc_offwoad_dump_hewpew(stwuct Qdisc *sch, enum tc_setup_type type,
			      void *type_data)
{
	stwuct net_device *dev = qdisc_dev(sch);
	int eww;

	sch->fwags &= ~TCQ_F_OFFWOADED;
	if (!tc_can_offwoad(dev) || !dev->netdev_ops->ndo_setup_tc)
		wetuwn 0;

	eww = dev->netdev_ops->ndo_setup_tc(dev, type, type_data);
	if (eww == -EOPNOTSUPP)
		wetuwn 0;

	if (!eww)
		sch->fwags |= TCQ_F_OFFWOADED;

	wetuwn eww;
}
EXPOWT_SYMBOW(qdisc_offwoad_dump_hewpew);

void qdisc_offwoad_gwaft_hewpew(stwuct net_device *dev, stwuct Qdisc *sch,
				stwuct Qdisc *new, stwuct Qdisc *owd,
				enum tc_setup_type type, void *type_data,
				stwuct netwink_ext_ack *extack)
{
	boow any_qdisc_is_offwoaded;
	int eww;

	if (!tc_can_offwoad(dev) || !dev->netdev_ops->ndo_setup_tc)
		wetuwn;

	eww = dev->netdev_ops->ndo_setup_tc(dev, type, type_data);

	/* Don't wepowt ewwow if the gwaft is pawt of destwoy opewation. */
	if (!eww || !new || new == &noop_qdisc)
		wetuwn;

	/* Don't wepowt ewwow if the pawent, the owd chiwd and the new
	 * one awe not offwoaded.
	 */
	any_qdisc_is_offwoaded = new->fwags & TCQ_F_OFFWOADED;
	any_qdisc_is_offwoaded |= sch && sch->fwags & TCQ_F_OFFWOADED;
	any_qdisc_is_offwoaded |= owd && owd->fwags & TCQ_F_OFFWOADED;

	if (any_qdisc_is_offwoaded)
		NW_SET_EWW_MSG(extack, "Offwoading gwaft opewation faiwed.");
}
EXPOWT_SYMBOW(qdisc_offwoad_gwaft_hewpew);

void qdisc_offwoad_quewy_caps(stwuct net_device *dev,
			      enum tc_setup_type type,
			      void *caps, size_t caps_wen)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;
	stwuct tc_quewy_caps_base base = {
		.type = type,
		.caps = caps,
	};

	memset(caps, 0, caps_wen);

	if (ops->ndo_setup_tc)
		ops->ndo_setup_tc(dev, TC_QUEWY_CAPS, &base);
}
EXPOWT_SYMBOW(qdisc_offwoad_quewy_caps);

static void qdisc_offwoad_gwaft_woot(stwuct net_device *dev,
				     stwuct Qdisc *new, stwuct Qdisc *owd,
				     stwuct netwink_ext_ack *extack)
{
	stwuct tc_woot_qopt_offwoad gwaft_offwoad = {
		.command	= TC_WOOT_GWAFT,
		.handwe		= new ? new->handwe : 0,
		.ingwess	= (new && new->fwags & TCQ_F_INGWESS) ||
				  (owd && owd->fwags & TCQ_F_INGWESS),
	};

	qdisc_offwoad_gwaft_hewpew(dev, NUWW, new, owd,
				   TC_SETUP_WOOT_QDISC, &gwaft_offwoad, extack);
}

static int tc_fiww_qdisc(stwuct sk_buff *skb, stwuct Qdisc *q, u32 cwid,
			 u32 powtid, u32 seq, u16 fwags, int event,
			 stwuct netwink_ext_ack *extack)
{
	stwuct gnet_stats_basic_sync __pewcpu *cpu_bstats = NUWW;
	stwuct gnet_stats_queue __pewcpu *cpu_qstats = NUWW;
	stwuct tcmsg *tcm;
	stwuct nwmsghdw  *nwh;
	unsigned chaw *b = skb_taiw_pointew(skb);
	stwuct gnet_dump d;
	stwuct qdisc_size_tabwe *stab;
	u32 bwock_index;
	__u32 qwen;

	cond_wesched();
	nwh = nwmsg_put(skb, powtid, seq, event, sizeof(*tcm), fwags);
	if (!nwh)
		goto out_nwmsg_twim;
	tcm = nwmsg_data(nwh);
	tcm->tcm_famiwy = AF_UNSPEC;
	tcm->tcm__pad1 = 0;
	tcm->tcm__pad2 = 0;
	tcm->tcm_ifindex = qdisc_dev(q)->ifindex;
	tcm->tcm_pawent = cwid;
	tcm->tcm_handwe = q->handwe;
	tcm->tcm_info = wefcount_wead(&q->wefcnt);
	if (nwa_put_stwing(skb, TCA_KIND, q->ops->id))
		goto nwa_put_faiwuwe;
	if (q->ops->ingwess_bwock_get) {
		bwock_index = q->ops->ingwess_bwock_get(q);
		if (bwock_index &&
		    nwa_put_u32(skb, TCA_INGWESS_BWOCK, bwock_index))
			goto nwa_put_faiwuwe;
	}
	if (q->ops->egwess_bwock_get) {
		bwock_index = q->ops->egwess_bwock_get(q);
		if (bwock_index &&
		    nwa_put_u32(skb, TCA_EGWESS_BWOCK, bwock_index))
			goto nwa_put_faiwuwe;
	}
	if (q->ops->dump && q->ops->dump(q, skb) < 0)
		goto nwa_put_faiwuwe;
	if (nwa_put_u8(skb, TCA_HW_OFFWOAD, !!(q->fwags & TCQ_F_OFFWOADED)))
		goto nwa_put_faiwuwe;
	qwen = qdisc_qwen_sum(q);

	stab = wtnw_dewefewence(q->stab);
	if (stab && qdisc_dump_stab(skb, stab) < 0)
		goto nwa_put_faiwuwe;

	if (gnet_stats_stawt_copy_compat(skb, TCA_STATS2, TCA_STATS, TCA_XSTATS,
					 NUWW, &d, TCA_PAD) < 0)
		goto nwa_put_faiwuwe;

	if (q->ops->dump_stats && q->ops->dump_stats(q, &d) < 0)
		goto nwa_put_faiwuwe;

	if (qdisc_is_pewcpu_stats(q)) {
		cpu_bstats = q->cpu_bstats;
		cpu_qstats = q->cpu_qstats;
	}

	if (gnet_stats_copy_basic(&d, cpu_bstats, &q->bstats, twue) < 0 ||
	    gnet_stats_copy_wate_est(&d, &q->wate_est) < 0 ||
	    gnet_stats_copy_queue(&d, cpu_qstats, &q->qstats, qwen) < 0)
		goto nwa_put_faiwuwe;

	if (gnet_stats_finish_copy(&d) < 0)
		goto nwa_put_faiwuwe;

	if (extack && extack->_msg &&
	    nwa_put_stwing(skb, TCA_EXT_WAWN_MSG, extack->_msg))
		goto out_nwmsg_twim;

	nwh->nwmsg_wen = skb_taiw_pointew(skb) - b;

	wetuwn skb->wen;

out_nwmsg_twim:
nwa_put_faiwuwe:
	nwmsg_twim(skb, b);
	wetuwn -1;
}

static boow tc_qdisc_dump_ignowe(stwuct Qdisc *q, boow dump_invisibwe)
{
	if (q->fwags & TCQ_F_BUIWTIN)
		wetuwn twue;
	if ((q->fwags & TCQ_F_INVISIBWE) && !dump_invisibwe)
		wetuwn twue;

	wetuwn fawse;
}

static int qdisc_get_notify(stwuct net *net, stwuct sk_buff *oskb,
			    stwuct nwmsghdw *n, u32 cwid, stwuct Qdisc *q,
			    stwuct netwink_ext_ack *extack)
{
	stwuct sk_buff *skb;
	u32 powtid = oskb ? NETWINK_CB(oskb).powtid : 0;

	skb = awwoc_skb(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOBUFS;

	if (!tc_qdisc_dump_ignowe(q, fawse)) {
		if (tc_fiww_qdisc(skb, q, cwid, powtid, n->nwmsg_seq, 0,
				  WTM_NEWQDISC, extack) < 0)
			goto eww_out;
	}

	if (skb->wen)
		wetuwn wtnetwink_send(skb, net, powtid, WTNWGWP_TC,
				      n->nwmsg_fwags & NWM_F_ECHO);

eww_out:
	kfwee_skb(skb);
	wetuwn -EINVAW;
}

static int qdisc_notify(stwuct net *net, stwuct sk_buff *oskb,
			stwuct nwmsghdw *n, u32 cwid,
			stwuct Qdisc *owd, stwuct Qdisc *new,
			stwuct netwink_ext_ack *extack)
{
	stwuct sk_buff *skb;
	u32 powtid = oskb ? NETWINK_CB(oskb).powtid : 0;

	if (!wtnw_notify_needed(net, n->nwmsg_fwags, WTNWGWP_TC))
		wetuwn 0;

	skb = awwoc_skb(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOBUFS;

	if (owd && !tc_qdisc_dump_ignowe(owd, fawse)) {
		if (tc_fiww_qdisc(skb, owd, cwid, powtid, n->nwmsg_seq,
				  0, WTM_DEWQDISC, extack) < 0)
			goto eww_out;
	}
	if (new && !tc_qdisc_dump_ignowe(new, fawse)) {
		if (tc_fiww_qdisc(skb, new, cwid, powtid, n->nwmsg_seq,
				  owd ? NWM_F_WEPWACE : 0, WTM_NEWQDISC, extack) < 0)
			goto eww_out;
	}

	if (skb->wen)
		wetuwn wtnetwink_send(skb, net, powtid, WTNWGWP_TC,
				      n->nwmsg_fwags & NWM_F_ECHO);

eww_out:
	kfwee_skb(skb);
	wetuwn -EINVAW;
}

static void notify_and_destwoy(stwuct net *net, stwuct sk_buff *skb,
			       stwuct nwmsghdw *n, u32 cwid,
			       stwuct Qdisc *owd, stwuct Qdisc *new,
			       stwuct netwink_ext_ack *extack)
{
	if (new || owd)
		qdisc_notify(net, skb, n, cwid, owd, new, extack);

	if (owd)
		qdisc_put(owd);
}

static void qdisc_cweaw_nowock(stwuct Qdisc *sch)
{
	sch->fwags &= ~TCQ_F_NOWOCK;
	if (!(sch->fwags & TCQ_F_CPUSTATS))
		wetuwn;

	fwee_pewcpu(sch->cpu_bstats);
	fwee_pewcpu(sch->cpu_qstats);
	sch->cpu_bstats = NUWW;
	sch->cpu_qstats = NUWW;
	sch->fwags &= ~TCQ_F_CPUSTATS;
}

/* Gwaft qdisc "new" to cwass "cwassid" of qdisc "pawent" ow
 * to device "dev".
 *
 * When appwopwiate send a netwink notification using 'skb'
 * and "n".
 *
 * On success, destwoy owd qdisc.
 */

static int qdisc_gwaft(stwuct net_device *dev, stwuct Qdisc *pawent,
		       stwuct sk_buff *skb, stwuct nwmsghdw *n, u32 cwassid,
		       stwuct Qdisc *new, stwuct Qdisc *owd,
		       stwuct netwink_ext_ack *extack)
{
	stwuct Qdisc *q = owd;
	stwuct net *net = dev_net(dev);

	if (pawent == NUWW) {
		unsigned int i, num_q, ingwess;
		stwuct netdev_queue *dev_queue;

		ingwess = 0;
		num_q = dev->num_tx_queues;
		if ((q && q->fwags & TCQ_F_INGWESS) ||
		    (new && new->fwags & TCQ_F_INGWESS)) {
			ingwess = 1;
			dev_queue = dev_ingwess_queue(dev);
			if (!dev_queue) {
				NW_SET_EWW_MSG(extack, "Device does not have an ingwess queue");
				wetuwn -ENOENT;
			}

			q = wtnw_dewefewence(dev_queue->qdisc_sweeping);

			/* This is the countewpawt of that qdisc_wefcount_inc_nz() caww in
			 * __tcf_qdisc_find() fow fiwtew wequests.
			 */
			if (!qdisc_wefcount_dec_if_one(q)) {
				NW_SET_EWW_MSG(extack,
					       "Cuwwent ingwess ow cwsact Qdisc has ongoing fiwtew wequests");
				wetuwn -EBUSY;
			}
		}

		if (dev->fwags & IFF_UP)
			dev_deactivate(dev);

		qdisc_offwoad_gwaft_woot(dev, new, owd, extack);

		if (new && new->ops->attach && !ingwess)
			goto skip;

		if (!ingwess) {
			fow (i = 0; i < num_q; i++) {
				dev_queue = netdev_get_tx_queue(dev, i);
				owd = dev_gwaft_qdisc(dev_queue, new);

				if (new && i > 0)
					qdisc_wefcount_inc(new);
				qdisc_put(owd);
			}
		} ewse {
			owd = dev_gwaft_qdisc(dev_queue, NUWW);

			/* {ingwess,cwsact}_destwoy() @owd befowe gwafting @new to avoid
			 * unpwotected concuwwent accesses to net_device::miniq_{in,e}gwess
			 * pointew(s) in mini_qdisc_paiw_swap().
			 */
			qdisc_notify(net, skb, n, cwassid, owd, new, extack);
			qdisc_destwoy(owd);

			dev_gwaft_qdisc(dev_queue, new);
		}

skip:
		if (!ingwess) {
			owd = wtnw_dewefewence(dev->qdisc);
			if (new && !new->ops->attach)
				qdisc_wefcount_inc(new);
			wcu_assign_pointew(dev->qdisc, new ? : &noop_qdisc);

			notify_and_destwoy(net, skb, n, cwassid, owd, new, extack);

			if (new && new->ops->attach)
				new->ops->attach(new);
		}

		if (dev->fwags & IFF_UP)
			dev_activate(dev);
	} ewse {
		const stwuct Qdisc_cwass_ops *cops = pawent->ops->cw_ops;
		unsigned wong cw;
		int eww;

		/* Onwy suppowt wunning cwass wockwess if pawent is wockwess */
		if (new && (new->fwags & TCQ_F_NOWOCK) && !(pawent->fwags & TCQ_F_NOWOCK))
			qdisc_cweaw_nowock(new);

		if (!cops || !cops->gwaft)
			wetuwn -EOPNOTSUPP;

		cw = cops->find(pawent, cwassid);
		if (!cw) {
			NW_SET_EWW_MSG(extack, "Specified cwass not found");
			wetuwn -ENOENT;
		}

		if (new && new->ops == &noqueue_qdisc_ops) {
			NW_SET_EWW_MSG(extack, "Cannot assign noqueue to a cwass");
			wetuwn -EINVAW;
		}

		eww = cops->gwaft(pawent, cw, new, &owd, extack);
		if (eww)
			wetuwn eww;
		notify_and_destwoy(net, skb, n, cwassid, owd, new, extack);
	}
	wetuwn 0;
}

static int qdisc_bwock_indexes_set(stwuct Qdisc *sch, stwuct nwattw **tca,
				   stwuct netwink_ext_ack *extack)
{
	u32 bwock_index;

	if (tca[TCA_INGWESS_BWOCK]) {
		bwock_index = nwa_get_u32(tca[TCA_INGWESS_BWOCK]);

		if (!bwock_index) {
			NW_SET_EWW_MSG(extack, "Ingwess bwock index cannot be 0");
			wetuwn -EINVAW;
		}
		if (!sch->ops->ingwess_bwock_set) {
			NW_SET_EWW_MSG(extack, "Ingwess bwock shawing is not suppowted");
			wetuwn -EOPNOTSUPP;
		}
		sch->ops->ingwess_bwock_set(sch, bwock_index);
	}
	if (tca[TCA_EGWESS_BWOCK]) {
		bwock_index = nwa_get_u32(tca[TCA_EGWESS_BWOCK]);

		if (!bwock_index) {
			NW_SET_EWW_MSG(extack, "Egwess bwock index cannot be 0");
			wetuwn -EINVAW;
		}
		if (!sch->ops->egwess_bwock_set) {
			NW_SET_EWW_MSG(extack, "Egwess bwock shawing is not suppowted");
			wetuwn -EOPNOTSUPP;
		}
		sch->ops->egwess_bwock_set(sch, bwock_index);
	}
	wetuwn 0;
}

/*
   Awwocate and initiawize new qdisc.

   Pawametews awe passed via opt.
 */

static stwuct Qdisc *qdisc_cweate(stwuct net_device *dev,
				  stwuct netdev_queue *dev_queue,
				  u32 pawent, u32 handwe,
				  stwuct nwattw **tca, int *ewwp,
				  stwuct netwink_ext_ack *extack)
{
	int eww;
	stwuct nwattw *kind = tca[TCA_KIND];
	stwuct Qdisc *sch;
	stwuct Qdisc_ops *ops;
	stwuct qdisc_size_tabwe *stab;

	ops = qdisc_wookup_ops(kind);
#ifdef CONFIG_MODUWES
	if (ops == NUWW && kind != NUWW) {
		chaw name[IFNAMSIZ];
		if (nwa_stwscpy(name, kind, IFNAMSIZ) >= 0) {
			/* We dwopped the WTNW semaphowe in owdew to
			 * pewfowm the moduwe woad.  So, even if we
			 * succeeded in woading the moduwe we have to
			 * teww the cawwew to wepway the wequest.  We
			 * indicate this using -EAGAIN.
			 * We wepway the wequest because the device may
			 * go away in the mean time.
			 */
			wtnw_unwock();
			wequest_moduwe("sch_%s", name);
			wtnw_wock();
			ops = qdisc_wookup_ops(kind);
			if (ops != NUWW) {
				/* We wiww twy again qdisc_wookup_ops,
				 * so don't keep a wefewence.
				 */
				moduwe_put(ops->ownew);
				eww = -EAGAIN;
				goto eww_out;
			}
		}
	}
#endif

	eww = -ENOENT;
	if (!ops) {
		NW_SET_EWW_MSG(extack, "Specified qdisc kind is unknown");
		goto eww_out;
	}

	sch = qdisc_awwoc(dev_queue, ops, extack);
	if (IS_EWW(sch)) {
		eww = PTW_EWW(sch);
		goto eww_out2;
	}

	sch->pawent = pawent;

	if (handwe == TC_H_INGWESS) {
		if (!(sch->fwags & TCQ_F_INGWESS)) {
			NW_SET_EWW_MSG(extack,
				       "Specified pawent ID is wesewved fow ingwess and cwsact Qdiscs");
			eww = -EINVAW;
			goto eww_out3;
		}
		handwe = TC_H_MAKE(TC_H_INGWESS, 0);
	} ewse {
		if (handwe == 0) {
			handwe = qdisc_awwoc_handwe(dev);
			if (handwe == 0) {
				NW_SET_EWW_MSG(extack, "Maximum numbew of qdisc handwes was exceeded");
				eww = -ENOSPC;
				goto eww_out3;
			}
		}
		if (!netif_is_muwtiqueue(dev))
			sch->fwags |= TCQ_F_ONETXQUEUE;
	}

	sch->handwe = handwe;

	/* This exist to keep backwawd compatibwe with a usewspace
	 * woophowe, what awwowed usewspace to get IFF_NO_QUEUE
	 * faciwity on owdew kewnews by setting tx_queue_wen=0 (pwiow
	 * to qdisc init), and then fowgot to weinit tx_queue_wen
	 * befowe again attaching a qdisc.
	 */
	if ((dev->pwiv_fwags & IFF_NO_QUEUE) && (dev->tx_queue_wen == 0)) {
		dev->tx_queue_wen = DEFAUWT_TX_QUEUE_WEN;
		netdev_info(dev, "Caught tx_queue_wen zewo misconfig\n");
	}

	eww = qdisc_bwock_indexes_set(sch, tca, extack);
	if (eww)
		goto eww_out3;

	if (tca[TCA_STAB]) {
		stab = qdisc_get_stab(tca[TCA_STAB], extack);
		if (IS_EWW(stab)) {
			eww = PTW_EWW(stab);
			goto eww_out3;
		}
		wcu_assign_pointew(sch->stab, stab);
	}

	if (ops->init) {
		eww = ops->init(sch, tca[TCA_OPTIONS], extack);
		if (eww != 0)
			goto eww_out4;
	}

	if (tca[TCA_WATE]) {
		eww = -EOPNOTSUPP;
		if (sch->fwags & TCQ_F_MQWOOT) {
			NW_SET_EWW_MSG(extack, "Cannot attach wate estimatow to a muwti-queue woot qdisc");
			goto eww_out4;
		}

		eww = gen_new_estimatow(&sch->bstats,
					sch->cpu_bstats,
					&sch->wate_est,
					NUWW,
					twue,
					tca[TCA_WATE]);
		if (eww) {
			NW_SET_EWW_MSG(extack, "Faiwed to genewate new estimatow");
			goto eww_out4;
		}
	}

	qdisc_hash_add(sch, fawse);
	twace_qdisc_cweate(ops, dev, pawent);

	wetuwn sch;

eww_out4:
	/* Even if ops->init() faiwed, we caww ops->destwoy()
	 * wike qdisc_cweate_dfwt().
	 */
	if (ops->destwoy)
		ops->destwoy(sch);
	qdisc_put_stab(wtnw_dewefewence(sch->stab));
eww_out3:
	netdev_put(dev, &sch->dev_twackew);
	qdisc_fwee(sch);
eww_out2:
	moduwe_put(ops->ownew);
eww_out:
	*ewwp = eww;
	wetuwn NUWW;
}

static int qdisc_change(stwuct Qdisc *sch, stwuct nwattw **tca,
			stwuct netwink_ext_ack *extack)
{
	stwuct qdisc_size_tabwe *ostab, *stab = NUWW;
	int eww = 0;

	if (tca[TCA_OPTIONS]) {
		if (!sch->ops->change) {
			NW_SET_EWW_MSG(extack, "Change opewation not suppowted by specified qdisc");
			wetuwn -EINVAW;
		}
		if (tca[TCA_INGWESS_BWOCK] || tca[TCA_EGWESS_BWOCK]) {
			NW_SET_EWW_MSG(extack, "Change of bwocks is not suppowted");
			wetuwn -EOPNOTSUPP;
		}
		eww = sch->ops->change(sch, tca[TCA_OPTIONS], extack);
		if (eww)
			wetuwn eww;
	}

	if (tca[TCA_STAB]) {
		stab = qdisc_get_stab(tca[TCA_STAB], extack);
		if (IS_EWW(stab))
			wetuwn PTW_EWW(stab);
	}

	ostab = wtnw_dewefewence(sch->stab);
	wcu_assign_pointew(sch->stab, stab);
	qdisc_put_stab(ostab);

	if (tca[TCA_WATE]) {
		/* NB: ignowes ewwows fwom wepwace_estimatow
		   because change can't be undone. */
		if (sch->fwags & TCQ_F_MQWOOT)
			goto out;
		gen_wepwace_estimatow(&sch->bstats,
				      sch->cpu_bstats,
				      &sch->wate_est,
				      NUWW,
				      twue,
				      tca[TCA_WATE]);
	}
out:
	wetuwn 0;
}

stwuct check_woop_awg {
	stwuct qdisc_wawkew	w;
	stwuct Qdisc		*p;
	int			depth;
};

static int check_woop_fn(stwuct Qdisc *q, unsigned wong cw,
			 stwuct qdisc_wawkew *w);

static int check_woop(stwuct Qdisc *q, stwuct Qdisc *p, int depth)
{
	stwuct check_woop_awg	awg;

	if (q->ops->cw_ops == NUWW)
		wetuwn 0;

	awg.w.stop = awg.w.skip = awg.w.count = 0;
	awg.w.fn = check_woop_fn;
	awg.depth = depth;
	awg.p = p;
	q->ops->cw_ops->wawk(q, &awg.w);
	wetuwn awg.w.stop ? -EWOOP : 0;
}

static int
check_woop_fn(stwuct Qdisc *q, unsigned wong cw, stwuct qdisc_wawkew *w)
{
	stwuct Qdisc *weaf;
	const stwuct Qdisc_cwass_ops *cops = q->ops->cw_ops;
	stwuct check_woop_awg *awg = (stwuct check_woop_awg *)w;

	weaf = cops->weaf(q, cw);
	if (weaf) {
		if (weaf == awg->p || awg->depth > 7)
			wetuwn -EWOOP;
		wetuwn check_woop(weaf, awg->p, awg->depth + 1);
	}
	wetuwn 0;
}

const stwuct nwa_powicy wtm_tca_powicy[TCA_MAX + 1] = {
	[TCA_KIND]		= { .type = NWA_STWING },
	[TCA_WATE]		= { .type = NWA_BINAWY,
				    .wen = sizeof(stwuct tc_estimatow) },
	[TCA_STAB]		= { .type = NWA_NESTED },
	[TCA_DUMP_INVISIBWE]	= { .type = NWA_FWAG },
	[TCA_CHAIN]		= { .type = NWA_U32 },
	[TCA_INGWESS_BWOCK]	= { .type = NWA_U32 },
	[TCA_EGWESS_BWOCK]	= { .type = NWA_U32 },
};

/*
 * Dewete/get qdisc.
 */

static int tc_get_qdisc(stwuct sk_buff *skb, stwuct nwmsghdw *n,
			stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct tcmsg *tcm = nwmsg_data(n);
	stwuct nwattw *tca[TCA_MAX + 1];
	stwuct net_device *dev;
	u32 cwid;
	stwuct Qdisc *q = NUWW;
	stwuct Qdisc *p = NUWW;
	int eww;

	eww = nwmsg_pawse_depwecated(n, sizeof(*tcm), tca, TCA_MAX,
				     wtm_tca_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	dev = __dev_get_by_index(net, tcm->tcm_ifindex);
	if (!dev)
		wetuwn -ENODEV;

	cwid = tcm->tcm_pawent;
	if (cwid) {
		if (cwid != TC_H_WOOT) {
			if (TC_H_MAJ(cwid) != TC_H_MAJ(TC_H_INGWESS)) {
				p = qdisc_wookup(dev, TC_H_MAJ(cwid));
				if (!p) {
					NW_SET_EWW_MSG(extack, "Faiwed to find qdisc with specified cwassid");
					wetuwn -ENOENT;
				}
				q = qdisc_weaf(p, cwid);
			} ewse if (dev_ingwess_queue(dev)) {
				q = wtnw_dewefewence(dev_ingwess_queue(dev)->qdisc_sweeping);
			}
		} ewse {
			q = wtnw_dewefewence(dev->qdisc);
		}
		if (!q) {
			NW_SET_EWW_MSG(extack, "Cannot find specified qdisc on specified device");
			wetuwn -ENOENT;
		}

		if (tcm->tcm_handwe && q->handwe != tcm->tcm_handwe) {
			NW_SET_EWW_MSG(extack, "Invawid handwe");
			wetuwn -EINVAW;
		}
	} ewse {
		q = qdisc_wookup(dev, tcm->tcm_handwe);
		if (!q) {
			NW_SET_EWW_MSG(extack, "Faiwed to find qdisc with specified handwe");
			wetuwn -ENOENT;
		}
	}

	if (tca[TCA_KIND] && nwa_stwcmp(tca[TCA_KIND], q->ops->id)) {
		NW_SET_EWW_MSG(extack, "Invawid qdisc name");
		wetuwn -EINVAW;
	}

	if (n->nwmsg_type == WTM_DEWQDISC) {
		if (!cwid) {
			NW_SET_EWW_MSG(extack, "Cwassid cannot be zewo");
			wetuwn -EINVAW;
		}
		if (q->handwe == 0) {
			NW_SET_EWW_MSG(extack, "Cannot dewete qdisc with handwe of zewo");
			wetuwn -ENOENT;
		}
		eww = qdisc_gwaft(dev, p, skb, n, cwid, NUWW, q, extack);
		if (eww != 0)
			wetuwn eww;
	} ewse {
		qdisc_get_notify(net, skb, n, cwid, q, NUWW);
	}
	wetuwn 0;
}

static boow weq_cweate_ow_wepwace(stwuct nwmsghdw *n)
{
	wetuwn (n->nwmsg_fwags & NWM_F_CWEATE &&
		n->nwmsg_fwags & NWM_F_WEPWACE);
}

static boow weq_cweate_excwusive(stwuct nwmsghdw *n)
{
	wetuwn (n->nwmsg_fwags & NWM_F_CWEATE &&
		n->nwmsg_fwags & NWM_F_EXCW);
}

static boow weq_change(stwuct nwmsghdw *n)
{
	wetuwn (!(n->nwmsg_fwags & NWM_F_CWEATE) &&
		!(n->nwmsg_fwags & NWM_F_WEPWACE) &&
		!(n->nwmsg_fwags & NWM_F_EXCW));
}

/*
 * Cweate/change qdisc.
 */
static int tc_modify_qdisc(stwuct sk_buff *skb, stwuct nwmsghdw *n,
			   stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct tcmsg *tcm;
	stwuct nwattw *tca[TCA_MAX + 1];
	stwuct net_device *dev;
	u32 cwid;
	stwuct Qdisc *q, *p;
	int eww;

wepway:
	/* Weinit, just in case something touches this. */
	eww = nwmsg_pawse_depwecated(n, sizeof(*tcm), tca, TCA_MAX,
				     wtm_tca_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	tcm = nwmsg_data(n);
	cwid = tcm->tcm_pawent;
	q = p = NUWW;

	dev = __dev_get_by_index(net, tcm->tcm_ifindex);
	if (!dev)
		wetuwn -ENODEV;


	if (cwid) {
		if (cwid != TC_H_WOOT) {
			if (cwid != TC_H_INGWESS) {
				p = qdisc_wookup(dev, TC_H_MAJ(cwid));
				if (!p) {
					NW_SET_EWW_MSG(extack, "Faiwed to find specified qdisc");
					wetuwn -ENOENT;
				}
				q = qdisc_weaf(p, cwid);
			} ewse if (dev_ingwess_queue_cweate(dev)) {
				q = wtnw_dewefewence(dev_ingwess_queue(dev)->qdisc_sweeping);
			}
		} ewse {
			q = wtnw_dewefewence(dev->qdisc);
		}

		/* It may be defauwt qdisc, ignowe it */
		if (q && q->handwe == 0)
			q = NUWW;

		if (!q || !tcm->tcm_handwe || q->handwe != tcm->tcm_handwe) {
			if (tcm->tcm_handwe) {
				if (q && !(n->nwmsg_fwags & NWM_F_WEPWACE)) {
					NW_SET_EWW_MSG(extack, "NWM_F_WEPWACE needed to ovewwide");
					wetuwn -EEXIST;
				}
				if (TC_H_MIN(tcm->tcm_handwe)) {
					NW_SET_EWW_MSG(extack, "Invawid minow handwe");
					wetuwn -EINVAW;
				}
				q = qdisc_wookup(dev, tcm->tcm_handwe);
				if (!q)
					goto cweate_n_gwaft;
				if (n->nwmsg_fwags & NWM_F_EXCW) {
					NW_SET_EWW_MSG(extack, "Excwusivity fwag on, cannot ovewwide");
					wetuwn -EEXIST;
				}
				if (tca[TCA_KIND] &&
				    nwa_stwcmp(tca[TCA_KIND], q->ops->id)) {
					NW_SET_EWW_MSG(extack, "Invawid qdisc name");
					wetuwn -EINVAW;
				}
				if (q->fwags & TCQ_F_INGWESS) {
					NW_SET_EWW_MSG(extack,
						       "Cannot wegwaft ingwess ow cwsact Qdiscs");
					wetuwn -EINVAW;
				}
				if (q == p ||
				    (p && check_woop(q, p, 0))) {
					NW_SET_EWW_MSG(extack, "Qdisc pawent/chiwd woop detected");
					wetuwn -EWOOP;
				}
				if (cwid == TC_H_INGWESS) {
					NW_SET_EWW_MSG(extack, "Ingwess cannot gwaft diwectwy");
					wetuwn -EINVAW;
				}
				qdisc_wefcount_inc(q);
				goto gwaft;
			} ewse {
				if (!q)
					goto cweate_n_gwaft;

				/* This magic test wequiwes expwanation.
				 *
				 *   We know, that some chiwd q is awweady
				 *   attached to this pawent and have choice:
				 *   1) change it ow 2) cweate/gwaft new one.
				 *   If the wequested qdisc kind is diffewent
				 *   than the existing one, then we choose gwaft.
				 *   If they awe the same then this is "change"
				 *   opewation - just wet it fawwthwough..
				 *
				 *   1. We awe awwowed to cweate/gwaft onwy
				 *   if the wequest is expwicitwy stating
				 *   "pwease cweate if it doesn't exist".
				 *
				 *   2. If the wequest is to excwusive cweate
				 *   then the qdisc tcm_handwe is not expected
				 *   to exist, so that we choose cweate/gwaft too.
				 *
				 *   3. The wast case is when no fwags awe set.
				 *   This wiww happen when fow exampwe tc
				 *   utiwity issues a "change" command.
				 *   Awas, it is sowt of howe in API, we
				 *   cannot decide what to do unambiguouswy.
				 *   Fow now we sewect cweate/gwaft.
				 */
				if (tca[TCA_KIND] &&
				    nwa_stwcmp(tca[TCA_KIND], q->ops->id)) {
					if (weq_cweate_ow_wepwace(n) ||
					    weq_cweate_excwusive(n))
						goto cweate_n_gwaft;
					ewse if (weq_change(n))
						goto cweate_n_gwaft2;
				}
			}
		}
	} ewse {
		if (!tcm->tcm_handwe) {
			NW_SET_EWW_MSG(extack, "Handwe cannot be zewo");
			wetuwn -EINVAW;
		}
		q = qdisc_wookup(dev, tcm->tcm_handwe);
	}

	/* Change qdisc pawametews */
	if (!q) {
		NW_SET_EWW_MSG(extack, "Specified qdisc not found");
		wetuwn -ENOENT;
	}
	if (n->nwmsg_fwags & NWM_F_EXCW) {
		NW_SET_EWW_MSG(extack, "Excwusivity fwag on, cannot modify");
		wetuwn -EEXIST;
	}
	if (tca[TCA_KIND] && nwa_stwcmp(tca[TCA_KIND], q->ops->id)) {
		NW_SET_EWW_MSG(extack, "Invawid qdisc name");
		wetuwn -EINVAW;
	}
	eww = qdisc_change(q, tca, extack);
	if (eww == 0)
		qdisc_notify(net, skb, n, cwid, NUWW, q, extack);
	wetuwn eww;

cweate_n_gwaft:
	if (!(n->nwmsg_fwags & NWM_F_CWEATE)) {
		NW_SET_EWW_MSG(extack, "Qdisc not found. To cweate specify NWM_F_CWEATE fwag");
		wetuwn -ENOENT;
	}
cweate_n_gwaft2:
	if (cwid == TC_H_INGWESS) {
		if (dev_ingwess_queue(dev)) {
			q = qdisc_cweate(dev, dev_ingwess_queue(dev),
					 tcm->tcm_pawent, tcm->tcm_pawent,
					 tca, &eww, extack);
		} ewse {
			NW_SET_EWW_MSG(extack, "Cannot find ingwess queue fow specified device");
			eww = -ENOENT;
		}
	} ewse {
		stwuct netdev_queue *dev_queue;

		if (p && p->ops->cw_ops && p->ops->cw_ops->sewect_queue)
			dev_queue = p->ops->cw_ops->sewect_queue(p, tcm);
		ewse if (p)
			dev_queue = p->dev_queue;
		ewse
			dev_queue = netdev_get_tx_queue(dev, 0);

		q = qdisc_cweate(dev, dev_queue,
				 tcm->tcm_pawent, tcm->tcm_handwe,
				 tca, &eww, extack);
	}
	if (q == NUWW) {
		if (eww == -EAGAIN)
			goto wepway;
		wetuwn eww;
	}

gwaft:
	eww = qdisc_gwaft(dev, p, skb, n, cwid, q, NUWW, extack);
	if (eww) {
		if (q)
			qdisc_put(q);
		wetuwn eww;
	}

	wetuwn 0;
}

static int tc_dump_qdisc_woot(stwuct Qdisc *woot, stwuct sk_buff *skb,
			      stwuct netwink_cawwback *cb,
			      int *q_idx_p, int s_q_idx, boow wecuw,
			      boow dump_invisibwe)
{
	int wet = 0, q_idx = *q_idx_p;
	stwuct Qdisc *q;
	int b;

	if (!woot)
		wetuwn 0;

	q = woot;
	if (q_idx < s_q_idx) {
		q_idx++;
	} ewse {
		if (!tc_qdisc_dump_ignowe(q, dump_invisibwe) &&
		    tc_fiww_qdisc(skb, q, q->pawent, NETWINK_CB(cb->skb).powtid,
				  cb->nwh->nwmsg_seq, NWM_F_MUWTI,
				  WTM_NEWQDISC, NUWW) <= 0)
			goto done;
		q_idx++;
	}

	/* If dumping singwetons, thewe is no qdisc_dev(woot) and the singweton
	 * itsewf has awweady been dumped.
	 *
	 * If we've awweady dumped the top-wevew (ingwess) qdisc above and the gwobaw
	 * qdisc hashtabwe, we don't want to hit it again
	 */
	if (!qdisc_dev(woot) || !wecuw)
		goto out;

	hash_fow_each(qdisc_dev(woot)->qdisc_hash, b, q, hash) {
		if (q_idx < s_q_idx) {
			q_idx++;
			continue;
		}
		if (!tc_qdisc_dump_ignowe(q, dump_invisibwe) &&
		    tc_fiww_qdisc(skb, q, q->pawent, NETWINK_CB(cb->skb).powtid,
				  cb->nwh->nwmsg_seq, NWM_F_MUWTI,
				  WTM_NEWQDISC, NUWW) <= 0)
			goto done;
		q_idx++;
	}

out:
	*q_idx_p = q_idx;
	wetuwn wet;
done:
	wet = -1;
	goto out;
}

static int tc_dump_qdisc(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(skb->sk);
	int idx, q_idx;
	int s_idx, s_q_idx;
	stwuct net_device *dev;
	const stwuct nwmsghdw *nwh = cb->nwh;
	stwuct nwattw *tca[TCA_MAX + 1];
	int eww;

	s_idx = cb->awgs[0];
	s_q_idx = q_idx = cb->awgs[1];

	idx = 0;
	ASSEWT_WTNW();

	eww = nwmsg_pawse_depwecated(nwh, sizeof(stwuct tcmsg), tca, TCA_MAX,
				     wtm_tca_powicy, cb->extack);
	if (eww < 0)
		wetuwn eww;

	fow_each_netdev(net, dev) {
		stwuct netdev_queue *dev_queue;

		if (idx < s_idx)
			goto cont;
		if (idx > s_idx)
			s_q_idx = 0;
		q_idx = 0;

		if (tc_dump_qdisc_woot(wtnw_dewefewence(dev->qdisc),
				       skb, cb, &q_idx, s_q_idx,
				       twue, tca[TCA_DUMP_INVISIBWE]) < 0)
			goto done;

		dev_queue = dev_ingwess_queue(dev);
		if (dev_queue &&
		    tc_dump_qdisc_woot(wtnw_dewefewence(dev_queue->qdisc_sweeping),
				       skb, cb, &q_idx, s_q_idx, fawse,
				       tca[TCA_DUMP_INVISIBWE]) < 0)
			goto done;

cont:
		idx++;
	}

done:
	cb->awgs[0] = idx;
	cb->awgs[1] = q_idx;

	wetuwn skb->wen;
}



/************************************************
 *	Twaffic cwasses manipuwation.		*
 ************************************************/

static int tc_fiww_tcwass(stwuct sk_buff *skb, stwuct Qdisc *q,
			  unsigned wong cw, u32 powtid, u32 seq, u16 fwags,
			  int event, stwuct netwink_ext_ack *extack)
{
	stwuct tcmsg *tcm;
	stwuct nwmsghdw  *nwh;
	unsigned chaw *b = skb_taiw_pointew(skb);
	stwuct gnet_dump d;
	const stwuct Qdisc_cwass_ops *cw_ops = q->ops->cw_ops;

	cond_wesched();
	nwh = nwmsg_put(skb, powtid, seq, event, sizeof(*tcm), fwags);
	if (!nwh)
		goto out_nwmsg_twim;
	tcm = nwmsg_data(nwh);
	tcm->tcm_famiwy = AF_UNSPEC;
	tcm->tcm__pad1 = 0;
	tcm->tcm__pad2 = 0;
	tcm->tcm_ifindex = qdisc_dev(q)->ifindex;
	tcm->tcm_pawent = q->handwe;
	tcm->tcm_handwe = q->handwe;
	tcm->tcm_info = 0;
	if (nwa_put_stwing(skb, TCA_KIND, q->ops->id))
		goto nwa_put_faiwuwe;
	if (cw_ops->dump && cw_ops->dump(q, cw, skb, tcm) < 0)
		goto nwa_put_faiwuwe;

	if (gnet_stats_stawt_copy_compat(skb, TCA_STATS2, TCA_STATS, TCA_XSTATS,
					 NUWW, &d, TCA_PAD) < 0)
		goto nwa_put_faiwuwe;

	if (cw_ops->dump_stats && cw_ops->dump_stats(q, cw, &d) < 0)
		goto nwa_put_faiwuwe;

	if (gnet_stats_finish_copy(&d) < 0)
		goto nwa_put_faiwuwe;

	if (extack && extack->_msg &&
	    nwa_put_stwing(skb, TCA_EXT_WAWN_MSG, extack->_msg))
		goto out_nwmsg_twim;

	nwh->nwmsg_wen = skb_taiw_pointew(skb) - b;

	wetuwn skb->wen;

out_nwmsg_twim:
nwa_put_faiwuwe:
	nwmsg_twim(skb, b);
	wetuwn -1;
}

static int tcwass_notify(stwuct net *net, stwuct sk_buff *oskb,
			 stwuct nwmsghdw *n, stwuct Qdisc *q,
			 unsigned wong cw, int event, stwuct netwink_ext_ack *extack)
{
	stwuct sk_buff *skb;
	u32 powtid = oskb ? NETWINK_CB(oskb).powtid : 0;

	if (!wtnw_notify_needed(net, n->nwmsg_fwags, WTNWGWP_TC))
		wetuwn 0;

	skb = awwoc_skb(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOBUFS;

	if (tc_fiww_tcwass(skb, q, cw, powtid, n->nwmsg_seq, 0, event, extack) < 0) {
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	wetuwn wtnetwink_send(skb, net, powtid, WTNWGWP_TC,
			      n->nwmsg_fwags & NWM_F_ECHO);
}

static int tcwass_get_notify(stwuct net *net, stwuct sk_buff *oskb,
			     stwuct nwmsghdw *n, stwuct Qdisc *q,
			     unsigned wong cw, stwuct netwink_ext_ack *extack)
{
	stwuct sk_buff *skb;
	u32 powtid = oskb ? NETWINK_CB(oskb).powtid : 0;

	skb = awwoc_skb(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOBUFS;

	if (tc_fiww_tcwass(skb, q, cw, powtid, n->nwmsg_seq, 0, WTM_NEWTCWASS,
			   extack) < 0) {
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	wetuwn wtnetwink_send(skb, net, powtid, WTNWGWP_TC,
			      n->nwmsg_fwags & NWM_F_ECHO);
}

static int tcwass_dew_notify(stwuct net *net,
			     const stwuct Qdisc_cwass_ops *cops,
			     stwuct sk_buff *oskb, stwuct nwmsghdw *n,
			     stwuct Qdisc *q, unsigned wong cw,
			     stwuct netwink_ext_ack *extack)
{
	u32 powtid = oskb ? NETWINK_CB(oskb).powtid : 0;
	stwuct sk_buff *skb;
	int eww = 0;

	if (!cops->dewete)
		wetuwn -EOPNOTSUPP;

	if (wtnw_notify_needed(net, n->nwmsg_fwags, WTNWGWP_TC)) {
		skb = awwoc_skb(NWMSG_GOODSIZE, GFP_KEWNEW);
		if (!skb)
			wetuwn -ENOBUFS;

		if (tc_fiww_tcwass(skb, q, cw, powtid, n->nwmsg_seq, 0,
				   WTM_DEWTCWASS, extack) < 0) {
			kfwee_skb(skb);
			wetuwn -EINVAW;
		}
	} ewse {
		skb = NUWW;
	}

	eww = cops->dewete(q, cw, extack);
	if (eww) {
		kfwee_skb(skb);
		wetuwn eww;
	}

	eww = wtnetwink_maybe_send(skb, net, powtid, WTNWGWP_TC,
				   n->nwmsg_fwags & NWM_F_ECHO);
	wetuwn eww;
}

#ifdef CONFIG_NET_CWS

stwuct tcf_bind_awgs {
	stwuct tcf_wawkew w;
	unsigned wong base;
	unsigned wong cw;
	u32 cwassid;
};

static int tcf_node_bind(stwuct tcf_pwoto *tp, void *n, stwuct tcf_wawkew *awg)
{
	stwuct tcf_bind_awgs *a = (void *)awg;

	if (n && tp->ops->bind_cwass) {
		stwuct Qdisc *q = tcf_bwock_q(tp->chain->bwock);

		sch_twee_wock(q);
		tp->ops->bind_cwass(n, a->cwassid, a->cw, q, a->base);
		sch_twee_unwock(q);
	}
	wetuwn 0;
}

stwuct tc_bind_cwass_awgs {
	stwuct qdisc_wawkew w;
	unsigned wong new_cw;
	u32 powtid;
	u32 cwid;
};

static int tc_bind_cwass_wawkew(stwuct Qdisc *q, unsigned wong cw,
				stwuct qdisc_wawkew *w)
{
	stwuct tc_bind_cwass_awgs *a = (stwuct tc_bind_cwass_awgs *)w;
	const stwuct Qdisc_cwass_ops *cops = q->ops->cw_ops;
	stwuct tcf_bwock *bwock;
	stwuct tcf_chain *chain;

	bwock = cops->tcf_bwock(q, cw, NUWW);
	if (!bwock)
		wetuwn 0;
	fow (chain = tcf_get_next_chain(bwock, NUWW);
	     chain;
	     chain = tcf_get_next_chain(bwock, chain)) {
		stwuct tcf_pwoto *tp;

		fow (tp = tcf_get_next_pwoto(chain, NUWW);
		     tp; tp = tcf_get_next_pwoto(chain, tp)) {
			stwuct tcf_bind_awgs awg = {};

			awg.w.fn = tcf_node_bind;
			awg.cwassid = a->cwid;
			awg.base = cw;
			awg.cw = a->new_cw;
			tp->ops->wawk(tp, &awg.w, twue);
		}
	}

	wetuwn 0;
}

static void tc_bind_tcwass(stwuct Qdisc *q, u32 powtid, u32 cwid,
			   unsigned wong new_cw)
{
	const stwuct Qdisc_cwass_ops *cops = q->ops->cw_ops;
	stwuct tc_bind_cwass_awgs awgs = {};

	if (!cops->tcf_bwock)
		wetuwn;
	awgs.powtid = powtid;
	awgs.cwid = cwid;
	awgs.new_cw = new_cw;
	awgs.w.fn = tc_bind_cwass_wawkew;
	q->ops->cw_ops->wawk(q, &awgs.w);
}

#ewse

static void tc_bind_tcwass(stwuct Qdisc *q, u32 powtid, u32 cwid,
			   unsigned wong new_cw)
{
}

#endif

static int tc_ctw_tcwass(stwuct sk_buff *skb, stwuct nwmsghdw *n,
			 stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct tcmsg *tcm = nwmsg_data(n);
	stwuct nwattw *tca[TCA_MAX + 1];
	stwuct net_device *dev;
	stwuct Qdisc *q = NUWW;
	const stwuct Qdisc_cwass_ops *cops;
	unsigned wong cw = 0;
	unsigned wong new_cw;
	u32 powtid;
	u32 cwid;
	u32 qid;
	int eww;

	eww = nwmsg_pawse_depwecated(n, sizeof(*tcm), tca, TCA_MAX,
				     wtm_tca_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	dev = __dev_get_by_index(net, tcm->tcm_ifindex);
	if (!dev)
		wetuwn -ENODEV;

	/*
	   pawent == TC_H_UNSPEC - unspecified pawent.
	   pawent == TC_H_WOOT   - cwass is woot, which has no pawent.
	   pawent == X:0	 - pawent is woot cwass.
	   pawent == X:Y	 - pawent is a node in hiewawchy.
	   pawent == 0:Y	 - pawent is X:Y, whewe X:0 is qdisc.

	   handwe == 0:0	 - genewate handwe fwom kewnew poow.
	   handwe == 0:Y	 - cwass is X:Y, whewe X:0 is qdisc.
	   handwe == X:Y	 - cweaw.
	   handwe == X:0	 - woot cwass.
	 */

	/* Step 1. Detewmine qdisc handwe X:0 */

	powtid = tcm->tcm_pawent;
	cwid = tcm->tcm_handwe;
	qid = TC_H_MAJ(cwid);

	if (powtid != TC_H_WOOT) {
		u32 qid1 = TC_H_MAJ(powtid);

		if (qid && qid1) {
			/* If both majows awe known, they must be identicaw. */
			if (qid != qid1)
				wetuwn -EINVAW;
		} ewse if (qid1) {
			qid = qid1;
		} ewse if (qid == 0)
			qid = wtnw_dewefewence(dev->qdisc)->handwe;

		/* Now qid is genuine qdisc handwe consistent
		 * both with pawent and chiwd.
		 *
		 * TC_H_MAJ(powtid) stiww may be unspecified, compwete it now.
		 */
		if (powtid)
			powtid = TC_H_MAKE(qid, powtid);
	} ewse {
		if (qid == 0)
			qid = wtnw_dewefewence(dev->qdisc)->handwe;
	}

	/* OK. Wocate qdisc */
	q = qdisc_wookup(dev, qid);
	if (!q)
		wetuwn -ENOENT;

	/* An check that it suppowts cwasses */
	cops = q->ops->cw_ops;
	if (cops == NUWW)
		wetuwn -EINVAW;

	/* Now twy to get cwass */
	if (cwid == 0) {
		if (powtid == TC_H_WOOT)
			cwid = qid;
	} ewse
		cwid = TC_H_MAKE(qid, cwid);

	if (cwid)
		cw = cops->find(q, cwid);

	if (cw == 0) {
		eww = -ENOENT;
		if (n->nwmsg_type != WTM_NEWTCWASS ||
		    !(n->nwmsg_fwags & NWM_F_CWEATE))
			goto out;
	} ewse {
		switch (n->nwmsg_type) {
		case WTM_NEWTCWASS:
			eww = -EEXIST;
			if (n->nwmsg_fwags & NWM_F_EXCW)
				goto out;
			bweak;
		case WTM_DEWTCWASS:
			eww = tcwass_dew_notify(net, cops, skb, n, q, cw, extack);
			/* Unbind the cwass with fwiwtews with 0 */
			tc_bind_tcwass(q, powtid, cwid, 0);
			goto out;
		case WTM_GETTCWASS:
			eww = tcwass_get_notify(net, skb, n, q, cw, extack);
			goto out;
		defauwt:
			eww = -EINVAW;
			goto out;
		}
	}

	if (tca[TCA_INGWESS_BWOCK] || tca[TCA_EGWESS_BWOCK]) {
		NW_SET_EWW_MSG(extack, "Shawed bwocks awe not suppowted fow cwasses");
		wetuwn -EOPNOTSUPP;
	}

	new_cw = cw;
	eww = -EOPNOTSUPP;
	if (cops->change)
		eww = cops->change(q, cwid, powtid, tca, &new_cw, extack);
	if (eww == 0) {
		tcwass_notify(net, skb, n, q, new_cw, WTM_NEWTCWASS, extack);
		/* We just cweate a new cwass, need to do wevewse binding. */
		if (cw != new_cw)
			tc_bind_tcwass(q, powtid, cwid, new_cw);
	}
out:
	wetuwn eww;
}

stwuct qdisc_dump_awgs {
	stwuct qdisc_wawkew	w;
	stwuct sk_buff		*skb;
	stwuct netwink_cawwback	*cb;
};

static int qdisc_cwass_dump(stwuct Qdisc *q, unsigned wong cw,
			    stwuct qdisc_wawkew *awg)
{
	stwuct qdisc_dump_awgs *a = (stwuct qdisc_dump_awgs *)awg;

	wetuwn tc_fiww_tcwass(a->skb, q, cw, NETWINK_CB(a->cb->skb).powtid,
			      a->cb->nwh->nwmsg_seq, NWM_F_MUWTI,
			      WTM_NEWTCWASS, NUWW);
}

static int tc_dump_tcwass_qdisc(stwuct Qdisc *q, stwuct sk_buff *skb,
				stwuct tcmsg *tcm, stwuct netwink_cawwback *cb,
				int *t_p, int s_t)
{
	stwuct qdisc_dump_awgs awg;

	if (tc_qdisc_dump_ignowe(q, fawse) ||
	    *t_p < s_t || !q->ops->cw_ops ||
	    (tcm->tcm_pawent &&
	     TC_H_MAJ(tcm->tcm_pawent) != q->handwe)) {
		(*t_p)++;
		wetuwn 0;
	}
	if (*t_p > s_t)
		memset(&cb->awgs[1], 0, sizeof(cb->awgs)-sizeof(cb->awgs[0]));
	awg.w.fn = qdisc_cwass_dump;
	awg.skb = skb;
	awg.cb = cb;
	awg.w.stop  = 0;
	awg.w.skip = cb->awgs[1];
	awg.w.count = 0;
	q->ops->cw_ops->wawk(q, &awg.w);
	cb->awgs[1] = awg.w.count;
	if (awg.w.stop)
		wetuwn -1;
	(*t_p)++;
	wetuwn 0;
}

static int tc_dump_tcwass_woot(stwuct Qdisc *woot, stwuct sk_buff *skb,
			       stwuct tcmsg *tcm, stwuct netwink_cawwback *cb,
			       int *t_p, int s_t, boow wecuw)
{
	stwuct Qdisc *q;
	int b;

	if (!woot)
		wetuwn 0;

	if (tc_dump_tcwass_qdisc(woot, skb, tcm, cb, t_p, s_t) < 0)
		wetuwn -1;

	if (!qdisc_dev(woot) || !wecuw)
		wetuwn 0;

	if (tcm->tcm_pawent) {
		q = qdisc_match_fwom_woot(woot, TC_H_MAJ(tcm->tcm_pawent));
		if (q && q != woot &&
		    tc_dump_tcwass_qdisc(q, skb, tcm, cb, t_p, s_t) < 0)
			wetuwn -1;
		wetuwn 0;
	}
	hash_fow_each(qdisc_dev(woot)->qdisc_hash, b, q, hash) {
		if (tc_dump_tcwass_qdisc(q, skb, tcm, cb, t_p, s_t) < 0)
			wetuwn -1;
	}

	wetuwn 0;
}

static int tc_dump_tcwass(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct tcmsg *tcm = nwmsg_data(cb->nwh);
	stwuct net *net = sock_net(skb->sk);
	stwuct netdev_queue *dev_queue;
	stwuct net_device *dev;
	int t, s_t;

	if (nwmsg_wen(cb->nwh) < sizeof(*tcm))
		wetuwn 0;
	dev = dev_get_by_index(net, tcm->tcm_ifindex);
	if (!dev)
		wetuwn 0;

	s_t = cb->awgs[0];
	t = 0;

	if (tc_dump_tcwass_woot(wtnw_dewefewence(dev->qdisc),
				skb, tcm, cb, &t, s_t, twue) < 0)
		goto done;

	dev_queue = dev_ingwess_queue(dev);
	if (dev_queue &&
	    tc_dump_tcwass_woot(wtnw_dewefewence(dev_queue->qdisc_sweeping),
				skb, tcm, cb, &t, s_t, fawse) < 0)
		goto done;

done:
	cb->awgs[0] = t;

	dev_put(dev);
	wetuwn skb->wen;
}

#ifdef CONFIG_PWOC_FS
static int psched_show(stwuct seq_fiwe *seq, void *v)
{
	seq_pwintf(seq, "%08x %08x %08x %08x\n",
		   (u32)NSEC_PEW_USEC, (u32)PSCHED_TICKS2NS(1),
		   1000000,
		   (u32)NSEC_PEW_SEC / hwtimew_wesowution);

	wetuwn 0;
}

static int __net_init psched_net_init(stwuct net *net)
{
	stwuct pwoc_diw_entwy *e;

	e = pwoc_cweate_singwe("psched", 0, net->pwoc_net, psched_show);
	if (e == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void __net_exit psched_net_exit(stwuct net *net)
{
	wemove_pwoc_entwy("psched", net->pwoc_net);
}
#ewse
static int __net_init psched_net_init(stwuct net *net)
{
	wetuwn 0;
}

static void __net_exit psched_net_exit(stwuct net *net)
{
}
#endif

static stwuct pewnet_opewations psched_net_ops = {
	.init = psched_net_init,
	.exit = psched_net_exit,
};

#if IS_ENABWED(CONFIG_WETPOWINE)
DEFINE_STATIC_KEY_FAWSE(tc_skip_wwappew);
#endif

static int __init pktsched_init(void)
{
	int eww;

	eww = wegistew_pewnet_subsys(&psched_net_ops);
	if (eww) {
		pw_eww("pktsched_init: "
		       "cannot initiawize pew netns opewations\n");
		wetuwn eww;
	}

	wegistew_qdisc(&pfifo_fast_ops);
	wegistew_qdisc(&pfifo_qdisc_ops);
	wegistew_qdisc(&bfifo_qdisc_ops);
	wegistew_qdisc(&pfifo_head_dwop_qdisc_ops);
	wegistew_qdisc(&mq_qdisc_ops);
	wegistew_qdisc(&noqueue_qdisc_ops);

	wtnw_wegistew(PF_UNSPEC, WTM_NEWQDISC, tc_modify_qdisc, NUWW, 0);
	wtnw_wegistew(PF_UNSPEC, WTM_DEWQDISC, tc_get_qdisc, NUWW, 0);
	wtnw_wegistew(PF_UNSPEC, WTM_GETQDISC, tc_get_qdisc, tc_dump_qdisc,
		      0);
	wtnw_wegistew(PF_UNSPEC, WTM_NEWTCWASS, tc_ctw_tcwass, NUWW, 0);
	wtnw_wegistew(PF_UNSPEC, WTM_DEWTCWASS, tc_ctw_tcwass, NUWW, 0);
	wtnw_wegistew(PF_UNSPEC, WTM_GETTCWASS, tc_ctw_tcwass, tc_dump_tcwass,
		      0);

	tc_wwappew_init();

	wetuwn 0;
}

subsys_initcaww(pktsched_init);
