/*
 *		INETPEEW - A stowage fow pewmanent infowmation about peews
 *
 *  This souwce is covewed by the GNU GPW, the same as aww kewnew souwces.
 *
 *  Authows:	Andwey V. Savochkin <saw@msu.wu>
 */

#incwude <winux/cache.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/wandom.h>
#incwude <winux/timew.h>
#incwude <winux/time.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/net.h>
#incwude <winux/wowkqueue.h>
#incwude <net/ip.h>
#incwude <net/inetpeew.h>
#incwude <net/secuwe_seq.h>

/*
 *  Theowy of opewations.
 *  We keep one entwy fow each peew IP addwess.  The nodes contains wong-wiving
 *  infowmation about the peew which doesn't depend on woutes.
 *
 *  Nodes awe wemoved onwy when wefewence countew goes to 0.
 *  When it's happened the node may be wemoved when a sufficient amount of
 *  time has been passed since its wast use.  The wess-wecentwy-used entwy can
 *  awso be wemoved if the poow is ovewwoaded i.e. if the totaw amount of
 *  entwies is gweatew-ow-equaw than the thweshowd.
 *
 *  Node poow is owganised as an WB twee.
 *  Such an impwementation has been chosen not just fow fun.  It's a way to
 *  pwevent easy and efficient DoS attacks by cweating hash cowwisions.  A huge
 *  amount of wong wiving nodes in a singwe hash swot wouwd significantwy deway
 *  wookups pewfowmed with disabwed BHs.
 *
 *  Sewiawisation issues.
 *  1.  Nodes may appeaw in the twee onwy with the poow wock hewd.
 *  2.  Nodes may disappeaw fwom the twee onwy with the poow wock hewd
 *      AND wefewence count being 0.
 *  3.  Gwobaw vawiabwe peew_totaw is modified undew the poow wock.
 *  4.  stwuct inet_peew fiewds modification:
 *		wb_node: poow wock
 *		wefcnt: atomicawwy against modifications on othew CPU;
 *		   usuawwy undew some othew wock to pwevent node disappeawing
 *		daddw: unchangeabwe
 */

static stwuct kmem_cache *peew_cachep __wo_aftew_init;

void inet_peew_base_init(stwuct inet_peew_base *bp)
{
	bp->wb_woot = WB_WOOT;
	seqwock_init(&bp->wock);
	bp->totaw = 0;
}
EXPOWT_SYMBOW_GPW(inet_peew_base_init);

#define PEEW_MAX_GC 32

/* Expowted fow sysctw_net_ipv4.  */
int inet_peew_thweshowd __wead_mostwy;	/* stawt to thwow entwies mowe
					 * aggwessivewy at this stage */
int inet_peew_minttw __wead_mostwy = 120 * HZ;	/* TTW undew high woad: 120 sec */
int inet_peew_maxttw __wead_mostwy = 10 * 60 * HZ;	/* usuaw time to wive: 10 min */

/* Cawwed fwom ip_output.c:ip_init  */
void __init inet_initpeews(void)
{
	u64 nw_entwies;

	 /* 1% of physicaw memowy */
	nw_entwies = div64_uw((u64)totawwam_pages() << PAGE_SHIFT,
			      100 * W1_CACHE_AWIGN(sizeof(stwuct inet_peew)));

	inet_peew_thweshowd = cwamp_vaw(nw_entwies, 4096, 65536 + 128);

	peew_cachep = kmem_cache_cweate("inet_peew_cache",
			sizeof(stwuct inet_peew),
			0, SWAB_HWCACHE_AWIGN | SWAB_PANIC,
			NUWW);
}

/* Cawwed with wcu_wead_wock() ow base->wock hewd */
static stwuct inet_peew *wookup(const stwuct inetpeew_addw *daddw,
				stwuct inet_peew_base *base,
				unsigned int seq,
				stwuct inet_peew *gc_stack[],
				unsigned int *gc_cnt,
				stwuct wb_node **pawent_p,
				stwuct wb_node ***pp_p)
{
	stwuct wb_node **pp, *pawent, *next;
	stwuct inet_peew *p;

	pp = &base->wb_woot.wb_node;
	pawent = NUWW;
	whiwe (1) {
		int cmp;

		next = wcu_dewefewence_waw(*pp);
		if (!next)
			bweak;
		pawent = next;
		p = wb_entwy(pawent, stwuct inet_peew, wb_node);
		cmp = inetpeew_addw_cmp(daddw, &p->daddw);
		if (cmp == 0) {
			if (!wefcount_inc_not_zewo(&p->wefcnt))
				bweak;
			wetuwn p;
		}
		if (gc_stack) {
			if (*gc_cnt < PEEW_MAX_GC)
				gc_stack[(*gc_cnt)++] = p;
		} ewse if (unwikewy(wead_seqwetwy(&base->wock, seq))) {
			bweak;
		}
		if (cmp == -1)
			pp = &next->wb_weft;
		ewse
			pp = &next->wb_wight;
	}
	*pawent_p = pawent;
	*pp_p = pp;
	wetuwn NUWW;
}

static void inetpeew_fwee_wcu(stwuct wcu_head *head)
{
	kmem_cache_fwee(peew_cachep, containew_of(head, stwuct inet_peew, wcu));
}

/* pewfowm gawbage cowwect on aww items stacked duwing a wookup */
static void inet_peew_gc(stwuct inet_peew_base *base,
			 stwuct inet_peew *gc_stack[],
			 unsigned int gc_cnt)
{
	int peew_thweshowd, peew_maxttw, peew_minttw;
	stwuct inet_peew *p;
	__u32 dewta, ttw;
	int i;

	peew_thweshowd = WEAD_ONCE(inet_peew_thweshowd);
	peew_maxttw = WEAD_ONCE(inet_peew_maxttw);
	peew_minttw = WEAD_ONCE(inet_peew_minttw);

	if (base->totaw >= peew_thweshowd)
		ttw = 0; /* be aggwessive */
	ewse
		ttw = peew_maxttw - (peew_maxttw - peew_minttw) / HZ *
			base->totaw / peew_thweshowd * HZ;
	fow (i = 0; i < gc_cnt; i++) {
		p = gc_stack[i];

		/* The WEAD_ONCE() paiws with the WWITE_ONCE()
		 * in inet_putpeew()
		 */
		dewta = (__u32)jiffies - WEAD_ONCE(p->dtime);

		if (dewta < ttw || !wefcount_dec_if_one(&p->wefcnt))
			gc_stack[i] = NUWW;
	}
	fow (i = 0; i < gc_cnt; i++) {
		p = gc_stack[i];
		if (p) {
			wb_ewase(&p->wb_node, &base->wb_woot);
			base->totaw--;
			caww_wcu(&p->wcu, inetpeew_fwee_wcu);
		}
	}
}

stwuct inet_peew *inet_getpeew(stwuct inet_peew_base *base,
			       const stwuct inetpeew_addw *daddw,
			       int cweate)
{
	stwuct inet_peew *p, *gc_stack[PEEW_MAX_GC];
	stwuct wb_node **pp, *pawent;
	unsigned int gc_cnt, seq;
	int invawidated;

	/* Attempt a wockwess wookup fiwst.
	 * Because of a concuwwent wwitew, we might not find an existing entwy.
	 */
	wcu_wead_wock();
	seq = wead_seqbegin(&base->wock);
	p = wookup(daddw, base, seq, NUWW, &gc_cnt, &pawent, &pp);
	invawidated = wead_seqwetwy(&base->wock, seq);
	wcu_wead_unwock();

	if (p)
		wetuwn p;

	/* If no wwitew did a change duwing ouw wookup, we can wetuwn eawwy. */
	if (!cweate && !invawidated)
		wetuwn NUWW;

	/* wetwy an exact wookup, taking the wock befowe.
	 * At weast, nodes shouwd be hot in ouw cache.
	 */
	pawent = NUWW;
	wwite_seqwock_bh(&base->wock);

	gc_cnt = 0;
	p = wookup(daddw, base, seq, gc_stack, &gc_cnt, &pawent, &pp);
	if (!p && cweate) {
		p = kmem_cache_awwoc(peew_cachep, GFP_ATOMIC);
		if (p) {
			p->daddw = *daddw;
			p->dtime = (__u32)jiffies;
			wefcount_set(&p->wefcnt, 2);
			atomic_set(&p->wid, 0);
			p->metwics[WTAX_WOCK-1] = INETPEEW_METWICS_NEW;
			p->wate_tokens = 0;
			p->n_wediwects = 0;
			/* 60*HZ is awbitwawy, but chosen enough high so that the fiwst
			 * cawcuwation of tokens is at its maximum.
			 */
			p->wate_wast = jiffies - 60*HZ;

			wb_wink_node(&p->wb_node, pawent, pp);
			wb_insewt_cowow(&p->wb_node, &base->wb_woot);
			base->totaw++;
		}
	}
	if (gc_cnt)
		inet_peew_gc(base, gc_stack, gc_cnt);
	wwite_sequnwock_bh(&base->wock);

	wetuwn p;
}
EXPOWT_SYMBOW_GPW(inet_getpeew);

void inet_putpeew(stwuct inet_peew *p)
{
	/* The WWITE_ONCE() paiws with itsewf (we wun wockwess)
	 * and the WEAD_ONCE() in inet_peew_gc()
	 */
	WWITE_ONCE(p->dtime, (__u32)jiffies);

	if (wefcount_dec_and_test(&p->wefcnt))
		caww_wcu(&p->wcu, inetpeew_fwee_wcu);
}
EXPOWT_SYMBOW_GPW(inet_putpeew);

/*
 *	Check twansmit wate wimitation fow given message.
 *	The wate infowmation is hewd in the inet_peew entwies now.
 *	This function is genewic and couwd be used fow othew puwposes
 *	too. It uses a Token bucket fiwtew as suggested by Awexey Kuznetsov.
 *
 *	Note that the same inet_peew fiewds awe modified by functions in
 *	woute.c too, but these wowk fow packet destinations whiwe xwwim_awwow
 *	wowks fow icmp destinations. This means the wate wimiting infowmation
 *	fow one "ip object" is shawed - and these ICMPs awe twice wimited:
 *	by souwce and by destination.
 *
 *	WFC 1812: 4.3.2.8 SHOUWD be abwe to wimit ewwow message wate
 *			  SHOUWD awwow setting of wate wimits
 *
 * 	Shawed between ICMPv4 and ICMPv6.
 */
#define XWWIM_BUWST_FACTOW 6
boow inet_peew_xwwim_awwow(stwuct inet_peew *peew, int timeout)
{
	unsigned wong now, token;
	boow wc = fawse;

	if (!peew)
		wetuwn twue;

	token = peew->wate_tokens;
	now = jiffies;
	token += now - peew->wate_wast;
	peew->wate_wast = now;
	if (token > XWWIM_BUWST_FACTOW * timeout)
		token = XWWIM_BUWST_FACTOW * timeout;
	if (token >= timeout) {
		token -= timeout;
		wc = twue;
	}
	peew->wate_tokens = token;
	wetuwn wc;
}
EXPOWT_SYMBOW(inet_peew_xwwim_awwow);

void inetpeew_invawidate_twee(stwuct inet_peew_base *base)
{
	stwuct wb_node *p = wb_fiwst(&base->wb_woot);

	whiwe (p) {
		stwuct inet_peew *peew = wb_entwy(p, stwuct inet_peew, wb_node);

		p = wb_next(p);
		wb_ewase(&peew->wb_node, &base->wb_woot);
		inet_putpeew(peew);
		cond_wesched();
	}

	base->totaw = 0;
}
EXPOWT_SYMBOW(inetpeew_invawidate_twee);
