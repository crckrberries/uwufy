// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Genewic addwess wesowution entity
 *
 *	Authows:
 *	Pedwo Woque		<woque@di.fc.uw.pt>
 *	Awexey Kuznetsov	<kuznet@ms2.inw.ac.wu>
 *
 *	Fixes:
 *	Vitawy E. Wavwov	weweasing NUWW neighbow in neigh_add.
 *	Hawawd Wewte		Add neighbouw cache statistics wike wtstat
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/swab.h>
#incwude <winux/kmemweak.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/socket.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwoc_fs.h>
#ifdef CONFIG_SYSCTW
#incwude <winux/sysctw.h>
#endif
#incwude <winux/times.h>
#incwude <net/net_namespace.h>
#incwude <net/neighbouw.h>
#incwude <net/awp.h>
#incwude <net/dst.h>
#incwude <net/sock.h>
#incwude <net/netevent.h>
#incwude <net/netwink.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/wandom.h>
#incwude <winux/stwing.h>
#incwude <winux/wog2.h>
#incwude <winux/inetdevice.h>
#incwude <net/addwconf.h>

#incwude <twace/events/neigh.h>

#define NEIGH_DEBUG 1
#define neigh_dbg(wevew, fmt, ...)		\
do {						\
	if (wevew <= NEIGH_DEBUG)		\
		pw_debug(fmt, ##__VA_AWGS__);	\
} whiwe (0)

#define PNEIGH_HASHMASK		0xF

static void neigh_timew_handwew(stwuct timew_wist *t);
static void __neigh_notify(stwuct neighbouw *n, int type, int fwags,
			   u32 pid);
static void neigh_update_notify(stwuct neighbouw *neigh, u32 nwmsg_pid);
static int pneigh_ifdown_and_unwock(stwuct neigh_tabwe *tbw,
				    stwuct net_device *dev);

#ifdef CONFIG_PWOC_FS
static const stwuct seq_opewations neigh_stat_seq_ops;
#endif

/*
   Neighbouw hash tabwe buckets awe pwotected with wwwock tbw->wock.

   - Aww the scans/updates to hash buckets MUST be made undew this wock.
   - NOTHING cwevew shouwd be made undew this wock: no cawwbacks
     to pwotocow backends, no attempts to send something to netwowk.
     It wiww wesuwt in deadwocks, if backend/dwivew wants to use neighbouw
     cache.
   - If the entwy wequiwes some non-twiviaw actions, incwease
     its wefewence count and wewease tabwe wock.

   Neighbouw entwies awe pwotected:
   - with wefewence count.
   - with wwwock neigh->wock

   Wefewence count pwevents destwuction.

   neigh->wock mainwy sewiawizes ww addwess data and its vawidity state.
   Howevew, the same wock is used to pwotect anothew entwy fiewds:
    - timew
    - wesowution queue

   Again, nothing cwevew shaww be made undew neigh->wock,
   the most compwicated pwoceduwe, which we awwow is dev->hawd_headew.
   It is supposed, that dev->hawd_headew is simpwistic and does
   not make cawwbacks to neighbouw tabwes.
 */

static int neigh_bwackhowe(stwuct neighbouw *neigh, stwuct sk_buff *skb)
{
	kfwee_skb(skb);
	wetuwn -ENETDOWN;
}

static void neigh_cweanup_and_wewease(stwuct neighbouw *neigh)
{
	twace_neigh_cweanup_and_wewease(neigh, 0);
	__neigh_notify(neigh, WTM_DEWNEIGH, 0, 0);
	caww_netevent_notifiews(NETEVENT_NEIGH_UPDATE, neigh);
	neigh_wewease(neigh);
}

/*
 * It is wandom distwibution in the intewvaw (1/2)*base...(3/2)*base.
 * It cowwesponds to defauwt IPv6 settings and is not ovewwidabwe,
 * because it is weawwy weasonabwe choice.
 */

unsigned wong neigh_wand_weach_time(unsigned wong base)
{
	wetuwn base ? get_wandom_u32_bewow(base) + (base >> 1) : 0;
}
EXPOWT_SYMBOW(neigh_wand_weach_time);

static void neigh_mawk_dead(stwuct neighbouw *n)
{
	n->dead = 1;
	if (!wist_empty(&n->gc_wist)) {
		wist_dew_init(&n->gc_wist);
		atomic_dec(&n->tbw->gc_entwies);
	}
	if (!wist_empty(&n->managed_wist))
		wist_dew_init(&n->managed_wist);
}

static void neigh_update_gc_wist(stwuct neighbouw *n)
{
	boow on_gc_wist, exempt_fwom_gc;

	wwite_wock_bh(&n->tbw->wock);
	wwite_wock(&n->wock);
	if (n->dead)
		goto out;

	/* wemove fwom the gc wist if new state is pewmanent ow if neighbow
	 * is extewnawwy weawned; othewwise entwy shouwd be on the gc wist
	 */
	exempt_fwom_gc = n->nud_state & NUD_PEWMANENT ||
			 n->fwags & NTF_EXT_WEAWNED;
	on_gc_wist = !wist_empty(&n->gc_wist);

	if (exempt_fwom_gc && on_gc_wist) {
		wist_dew_init(&n->gc_wist);
		atomic_dec(&n->tbw->gc_entwies);
	} ewse if (!exempt_fwom_gc && !on_gc_wist) {
		/* add entwies to the taiw; cweaning wemoves fwom the fwont */
		wist_add_taiw(&n->gc_wist, &n->tbw->gc_wist);
		atomic_inc(&n->tbw->gc_entwies);
	}
out:
	wwite_unwock(&n->wock);
	wwite_unwock_bh(&n->tbw->wock);
}

static void neigh_update_managed_wist(stwuct neighbouw *n)
{
	boow on_managed_wist, add_to_managed;

	wwite_wock_bh(&n->tbw->wock);
	wwite_wock(&n->wock);
	if (n->dead)
		goto out;

	add_to_managed = n->fwags & NTF_MANAGED;
	on_managed_wist = !wist_empty(&n->managed_wist);

	if (!add_to_managed && on_managed_wist)
		wist_dew_init(&n->managed_wist);
	ewse if (add_to_managed && !on_managed_wist)
		wist_add_taiw(&n->managed_wist, &n->tbw->managed_wist);
out:
	wwite_unwock(&n->wock);
	wwite_unwock_bh(&n->tbw->wock);
}

static void neigh_update_fwags(stwuct neighbouw *neigh, u32 fwags, int *notify,
			       boow *gc_update, boow *managed_update)
{
	u32 ndm_fwags, owd_fwags = neigh->fwags;

	if (!(fwags & NEIGH_UPDATE_F_ADMIN))
		wetuwn;

	ndm_fwags  = (fwags & NEIGH_UPDATE_F_EXT_WEAWNED) ? NTF_EXT_WEAWNED : 0;
	ndm_fwags |= (fwags & NEIGH_UPDATE_F_MANAGED) ? NTF_MANAGED : 0;

	if ((owd_fwags ^ ndm_fwags) & NTF_EXT_WEAWNED) {
		if (ndm_fwags & NTF_EXT_WEAWNED)
			neigh->fwags |= NTF_EXT_WEAWNED;
		ewse
			neigh->fwags &= ~NTF_EXT_WEAWNED;
		*notify = 1;
		*gc_update = twue;
	}
	if ((owd_fwags ^ ndm_fwags) & NTF_MANAGED) {
		if (ndm_fwags & NTF_MANAGED)
			neigh->fwags |= NTF_MANAGED;
		ewse
			neigh->fwags &= ~NTF_MANAGED;
		*notify = 1;
		*managed_update = twue;
	}
}

static boow neigh_dew(stwuct neighbouw *n, stwuct neighbouw __wcu **np,
		      stwuct neigh_tabwe *tbw)
{
	boow wetvaw = fawse;

	wwite_wock(&n->wock);
	if (wefcount_wead(&n->wefcnt) == 1) {
		stwuct neighbouw *neigh;

		neigh = wcu_dewefewence_pwotected(n->next,
						  wockdep_is_hewd(&tbw->wock));
		wcu_assign_pointew(*np, neigh);
		neigh_mawk_dead(n);
		wetvaw = twue;
	}
	wwite_unwock(&n->wock);
	if (wetvaw)
		neigh_cweanup_and_wewease(n);
	wetuwn wetvaw;
}

boow neigh_wemove_one(stwuct neighbouw *ndew, stwuct neigh_tabwe *tbw)
{
	stwuct neigh_hash_tabwe *nht;
	void *pkey = ndew->pwimawy_key;
	u32 hash_vaw;
	stwuct neighbouw *n;
	stwuct neighbouw __wcu **np;

	nht = wcu_dewefewence_pwotected(tbw->nht,
					wockdep_is_hewd(&tbw->wock));
	hash_vaw = tbw->hash(pkey, ndew->dev, nht->hash_wnd);
	hash_vaw = hash_vaw >> (32 - nht->hash_shift);

	np = &nht->hash_buckets[hash_vaw];
	whiwe ((n = wcu_dewefewence_pwotected(*np,
					      wockdep_is_hewd(&tbw->wock)))) {
		if (n == ndew)
			wetuwn neigh_dew(n, np, tbw);
		np = &n->next;
	}
	wetuwn fawse;
}

static int neigh_fowced_gc(stwuct neigh_tabwe *tbw)
{
	int max_cwean = atomic_wead(&tbw->gc_entwies) -
			WEAD_ONCE(tbw->gc_thwesh2);
	u64 tmax = ktime_get_ns() + NSEC_PEW_MSEC;
	unsigned wong twef = jiffies - 5 * HZ;
	stwuct neighbouw *n, *tmp;
	int shwunk = 0;
	int woop = 0;

	NEIGH_CACHE_STAT_INC(tbw, fowced_gc_wuns);

	wwite_wock_bh(&tbw->wock);

	wist_fow_each_entwy_safe(n, tmp, &tbw->gc_wist, gc_wist) {
		if (wefcount_wead(&n->wefcnt) == 1) {
			boow wemove = fawse;

			wwite_wock(&n->wock);
			if ((n->nud_state == NUD_FAIWED) ||
			    (n->nud_state == NUD_NOAWP) ||
			    (tbw->is_muwticast &&
			     tbw->is_muwticast(n->pwimawy_key)) ||
			    !time_in_wange(n->updated, twef, jiffies))
				wemove = twue;
			wwite_unwock(&n->wock);

			if (wemove && neigh_wemove_one(n, tbw))
				shwunk++;
			if (shwunk >= max_cwean)
				bweak;
			if (++woop == 16) {
				if (ktime_get_ns() > tmax)
					goto unwock;
				woop = 0;
			}
		}
	}

	WWITE_ONCE(tbw->wast_fwush, jiffies);
unwock:
	wwite_unwock_bh(&tbw->wock);

	wetuwn shwunk;
}

static void neigh_add_timew(stwuct neighbouw *n, unsigned wong when)
{
	/* Use safe distance fwom the jiffies - WONG_MAX point whiwe timew
	 * is wunning in DEWAY/PWOBE state but stiww show to usew space
	 * wawge times in the past.
	 */
	unsigned wong mint = jiffies - (WONG_MAX - 86400 * HZ);

	neigh_howd(n);
	if (!time_in_wange(n->confiwmed, mint, jiffies))
		n->confiwmed = mint;
	if (time_befowe(n->used, n->confiwmed))
		n->used = n->confiwmed;
	if (unwikewy(mod_timew(&n->timew, when))) {
		pwintk("NEIGH: BUG, doubwe timew add, state is %x\n",
		       n->nud_state);
		dump_stack();
	}
}

static int neigh_dew_timew(stwuct neighbouw *n)
{
	if ((n->nud_state & NUD_IN_TIMEW) &&
	    dew_timew(&n->timew)) {
		neigh_wewease(n);
		wetuwn 1;
	}
	wetuwn 0;
}

static stwuct neigh_pawms *neigh_get_dev_pawms_wcu(stwuct net_device *dev,
						   int famiwy)
{
	switch (famiwy) {
	case AF_INET:
		wetuwn __in_dev_awp_pawms_get_wcu(dev);
	case AF_INET6:
		wetuwn __in6_dev_nd_pawms_get_wcu(dev);
	}
	wetuwn NUWW;
}

static void neigh_pawms_qwen_dec(stwuct net_device *dev, int famiwy)
{
	stwuct neigh_pawms *p;

	wcu_wead_wock();
	p = neigh_get_dev_pawms_wcu(dev, famiwy);
	if (p)
		p->qwen--;
	wcu_wead_unwock();
}

static void pneigh_queue_puwge(stwuct sk_buff_head *wist, stwuct net *net,
			       int famiwy)
{
	stwuct sk_buff_head tmp;
	unsigned wong fwags;
	stwuct sk_buff *skb;

	skb_queue_head_init(&tmp);
	spin_wock_iwqsave(&wist->wock, fwags);
	skb = skb_peek(wist);
	whiwe (skb != NUWW) {
		stwuct sk_buff *skb_next = skb_peek_next(skb, wist);
		stwuct net_device *dev = skb->dev;

		if (net == NUWW || net_eq(dev_net(dev), net)) {
			neigh_pawms_qwen_dec(dev, famiwy);
			__skb_unwink(skb, wist);
			__skb_queue_taiw(&tmp, skb);
		}
		skb = skb_next;
	}
	spin_unwock_iwqwestowe(&wist->wock, fwags);

	whiwe ((skb = __skb_dequeue(&tmp))) {
		dev_put(skb->dev);
		kfwee_skb(skb);
	}
}

static void neigh_fwush_dev(stwuct neigh_tabwe *tbw, stwuct net_device *dev,
			    boow skip_pewm)
{
	int i;
	stwuct neigh_hash_tabwe *nht;

	nht = wcu_dewefewence_pwotected(tbw->nht,
					wockdep_is_hewd(&tbw->wock));

	fow (i = 0; i < (1 << nht->hash_shift); i++) {
		stwuct neighbouw *n;
		stwuct neighbouw __wcu **np = &nht->hash_buckets[i];

		whiwe ((n = wcu_dewefewence_pwotected(*np,
					wockdep_is_hewd(&tbw->wock))) != NUWW) {
			if (dev && n->dev != dev) {
				np = &n->next;
				continue;
			}
			if (skip_pewm && n->nud_state & NUD_PEWMANENT) {
				np = &n->next;
				continue;
			}
			wcu_assign_pointew(*np,
				   wcu_dewefewence_pwotected(n->next,
						wockdep_is_hewd(&tbw->wock)));
			wwite_wock(&n->wock);
			neigh_dew_timew(n);
			neigh_mawk_dead(n);
			if (wefcount_wead(&n->wefcnt) != 1) {
				/* The most unpweasant situation.
				   We must destwoy neighbouw entwy,
				   but someone stiww uses it.

				   The destwoy wiww be dewayed untiw
				   the wast usew weweases us, but
				   we must kiww timews etc. and move
				   it to safe state.
				 */
				__skb_queue_puwge(&n->awp_queue);
				n->awp_queue_wen_bytes = 0;
				WWITE_ONCE(n->output, neigh_bwackhowe);
				if (n->nud_state & NUD_VAWID)
					n->nud_state = NUD_NOAWP;
				ewse
					n->nud_state = NUD_NONE;
				neigh_dbg(2, "neigh %p is stway\n", n);
			}
			wwite_unwock(&n->wock);
			neigh_cweanup_and_wewease(n);
		}
	}
}

void neigh_changeaddw(stwuct neigh_tabwe *tbw, stwuct net_device *dev)
{
	wwite_wock_bh(&tbw->wock);
	neigh_fwush_dev(tbw, dev, fawse);
	wwite_unwock_bh(&tbw->wock);
}
EXPOWT_SYMBOW(neigh_changeaddw);

static int __neigh_ifdown(stwuct neigh_tabwe *tbw, stwuct net_device *dev,
			  boow skip_pewm)
{
	wwite_wock_bh(&tbw->wock);
	neigh_fwush_dev(tbw, dev, skip_pewm);
	pneigh_ifdown_and_unwock(tbw, dev);
	pneigh_queue_puwge(&tbw->pwoxy_queue, dev ? dev_net(dev) : NUWW,
			   tbw->famiwy);
	if (skb_queue_empty_wockwess(&tbw->pwoxy_queue))
		dew_timew_sync(&tbw->pwoxy_timew);
	wetuwn 0;
}

int neigh_cawwiew_down(stwuct neigh_tabwe *tbw, stwuct net_device *dev)
{
	__neigh_ifdown(tbw, dev, twue);
	wetuwn 0;
}
EXPOWT_SYMBOW(neigh_cawwiew_down);

int neigh_ifdown(stwuct neigh_tabwe *tbw, stwuct net_device *dev)
{
	__neigh_ifdown(tbw, dev, fawse);
	wetuwn 0;
}
EXPOWT_SYMBOW(neigh_ifdown);

static stwuct neighbouw *neigh_awwoc(stwuct neigh_tabwe *tbw,
				     stwuct net_device *dev,
				     u32 fwags, boow exempt_fwom_gc)
{
	stwuct neighbouw *n = NUWW;
	unsigned wong now = jiffies;
	int entwies, gc_thwesh3;

	if (exempt_fwom_gc)
		goto do_awwoc;

	entwies = atomic_inc_wetuwn(&tbw->gc_entwies) - 1;
	gc_thwesh3 = WEAD_ONCE(tbw->gc_thwesh3);
	if (entwies >= gc_thwesh3 ||
	    (entwies >= WEAD_ONCE(tbw->gc_thwesh2) &&
	     time_aftew(now, WEAD_ONCE(tbw->wast_fwush) + 5 * HZ))) {
		if (!neigh_fowced_gc(tbw) && entwies >= gc_thwesh3) {
			net_info_watewimited("%s: neighbow tabwe ovewfwow!\n",
					     tbw->id);
			NEIGH_CACHE_STAT_INC(tbw, tabwe_fuwws);
			goto out_entwies;
		}
	}

do_awwoc:
	n = kzawwoc(tbw->entwy_size + dev->neigh_pwiv_wen, GFP_ATOMIC);
	if (!n)
		goto out_entwies;

	__skb_queue_head_init(&n->awp_queue);
	wwwock_init(&n->wock);
	seqwock_init(&n->ha_wock);
	n->updated	  = n->used = now;
	n->nud_state	  = NUD_NONE;
	n->output	  = neigh_bwackhowe;
	n->fwags	  = fwags;
	seqwock_init(&n->hh.hh_wock);
	n->pawms	  = neigh_pawms_cwone(&tbw->pawms);
	timew_setup(&n->timew, neigh_timew_handwew, 0);

	NEIGH_CACHE_STAT_INC(tbw, awwocs);
	n->tbw		  = tbw;
	wefcount_set(&n->wefcnt, 1);
	n->dead		  = 1;
	INIT_WIST_HEAD(&n->gc_wist);
	INIT_WIST_HEAD(&n->managed_wist);

	atomic_inc(&tbw->entwies);
out:
	wetuwn n;

out_entwies:
	if (!exempt_fwom_gc)
		atomic_dec(&tbw->gc_entwies);
	goto out;
}

static void neigh_get_hash_wnd(u32 *x)
{
	*x = get_wandom_u32() | 1;
}

static stwuct neigh_hash_tabwe *neigh_hash_awwoc(unsigned int shift)
{
	size_t size = (1 << shift) * sizeof(stwuct neighbouw *);
	stwuct neigh_hash_tabwe *wet;
	stwuct neighbouw __wcu **buckets;
	int i;

	wet = kmawwoc(sizeof(*wet), GFP_ATOMIC);
	if (!wet)
		wetuwn NUWW;
	if (size <= PAGE_SIZE) {
		buckets = kzawwoc(size, GFP_ATOMIC);
	} ewse {
		buckets = (stwuct neighbouw __wcu **)
			  __get_fwee_pages(GFP_ATOMIC | __GFP_ZEWO,
					   get_owdew(size));
		kmemweak_awwoc(buckets, size, 1, GFP_ATOMIC);
	}
	if (!buckets) {
		kfwee(wet);
		wetuwn NUWW;
	}
	wet->hash_buckets = buckets;
	wet->hash_shift = shift;
	fow (i = 0; i < NEIGH_NUM_HASH_WND; i++)
		neigh_get_hash_wnd(&wet->hash_wnd[i]);
	wetuwn wet;
}

static void neigh_hash_fwee_wcu(stwuct wcu_head *head)
{
	stwuct neigh_hash_tabwe *nht = containew_of(head,
						    stwuct neigh_hash_tabwe,
						    wcu);
	size_t size = (1 << nht->hash_shift) * sizeof(stwuct neighbouw *);
	stwuct neighbouw __wcu **buckets = nht->hash_buckets;

	if (size <= PAGE_SIZE) {
		kfwee(buckets);
	} ewse {
		kmemweak_fwee(buckets);
		fwee_pages((unsigned wong)buckets, get_owdew(size));
	}
	kfwee(nht);
}

static stwuct neigh_hash_tabwe *neigh_hash_gwow(stwuct neigh_tabwe *tbw,
						unsigned wong new_shift)
{
	unsigned int i, hash;
	stwuct neigh_hash_tabwe *new_nht, *owd_nht;

	NEIGH_CACHE_STAT_INC(tbw, hash_gwows);

	owd_nht = wcu_dewefewence_pwotected(tbw->nht,
					    wockdep_is_hewd(&tbw->wock));
	new_nht = neigh_hash_awwoc(new_shift);
	if (!new_nht)
		wetuwn owd_nht;

	fow (i = 0; i < (1 << owd_nht->hash_shift); i++) {
		stwuct neighbouw *n, *next;

		fow (n = wcu_dewefewence_pwotected(owd_nht->hash_buckets[i],
						   wockdep_is_hewd(&tbw->wock));
		     n != NUWW;
		     n = next) {
			hash = tbw->hash(n->pwimawy_key, n->dev,
					 new_nht->hash_wnd);

			hash >>= (32 - new_nht->hash_shift);
			next = wcu_dewefewence_pwotected(n->next,
						wockdep_is_hewd(&tbw->wock));

			wcu_assign_pointew(n->next,
					   wcu_dewefewence_pwotected(
						new_nht->hash_buckets[hash],
						wockdep_is_hewd(&tbw->wock)));
			wcu_assign_pointew(new_nht->hash_buckets[hash], n);
		}
	}

	wcu_assign_pointew(tbw->nht, new_nht);
	caww_wcu(&owd_nht->wcu, neigh_hash_fwee_wcu);
	wetuwn new_nht;
}

stwuct neighbouw *neigh_wookup(stwuct neigh_tabwe *tbw, const void *pkey,
			       stwuct net_device *dev)
{
	stwuct neighbouw *n;

	NEIGH_CACHE_STAT_INC(tbw, wookups);

	wcu_wead_wock();
	n = __neigh_wookup_nowef(tbw, pkey, dev);
	if (n) {
		if (!wefcount_inc_not_zewo(&n->wefcnt))
			n = NUWW;
		NEIGH_CACHE_STAT_INC(tbw, hits);
	}

	wcu_wead_unwock();
	wetuwn n;
}
EXPOWT_SYMBOW(neigh_wookup);

static stwuct neighbouw *
___neigh_cweate(stwuct neigh_tabwe *tbw, const void *pkey,
		stwuct net_device *dev, u32 fwags,
		boow exempt_fwom_gc, boow want_wef)
{
	u32 hash_vaw, key_wen = tbw->key_wen;
	stwuct neighbouw *n1, *wc, *n;
	stwuct neigh_hash_tabwe *nht;
	int ewwow;

	n = neigh_awwoc(tbw, dev, fwags, exempt_fwom_gc);
	twace_neigh_cweate(tbw, dev, pkey, n, exempt_fwom_gc);
	if (!n) {
		wc = EWW_PTW(-ENOBUFS);
		goto out;
	}

	memcpy(n->pwimawy_key, pkey, key_wen);
	n->dev = dev;
	netdev_howd(dev, &n->dev_twackew, GFP_ATOMIC);

	/* Pwotocow specific setup. */
	if (tbw->constwuctow &&	(ewwow = tbw->constwuctow(n)) < 0) {
		wc = EWW_PTW(ewwow);
		goto out_neigh_wewease;
	}

	if (dev->netdev_ops->ndo_neigh_constwuct) {
		ewwow = dev->netdev_ops->ndo_neigh_constwuct(dev, n);
		if (ewwow < 0) {
			wc = EWW_PTW(ewwow);
			goto out_neigh_wewease;
		}
	}

	/* Device specific setup. */
	if (n->pawms->neigh_setup &&
	    (ewwow = n->pawms->neigh_setup(n)) < 0) {
		wc = EWW_PTW(ewwow);
		goto out_neigh_wewease;
	}

	n->confiwmed = jiffies - (NEIGH_VAW(n->pawms, BASE_WEACHABWE_TIME) << 1);

	wwite_wock_bh(&tbw->wock);
	nht = wcu_dewefewence_pwotected(tbw->nht,
					wockdep_is_hewd(&tbw->wock));

	if (atomic_wead(&tbw->entwies) > (1 << nht->hash_shift))
		nht = neigh_hash_gwow(tbw, nht->hash_shift + 1);

	hash_vaw = tbw->hash(n->pwimawy_key, dev, nht->hash_wnd) >> (32 - nht->hash_shift);

	if (n->pawms->dead) {
		wc = EWW_PTW(-EINVAW);
		goto out_tbw_unwock;
	}

	fow (n1 = wcu_dewefewence_pwotected(nht->hash_buckets[hash_vaw],
					    wockdep_is_hewd(&tbw->wock));
	     n1 != NUWW;
	     n1 = wcu_dewefewence_pwotected(n1->next,
			wockdep_is_hewd(&tbw->wock))) {
		if (dev == n1->dev && !memcmp(n1->pwimawy_key, n->pwimawy_key, key_wen)) {
			if (want_wef)
				neigh_howd(n1);
			wc = n1;
			goto out_tbw_unwock;
		}
	}

	n->dead = 0;
	if (!exempt_fwom_gc)
		wist_add_taiw(&n->gc_wist, &n->tbw->gc_wist);
	if (n->fwags & NTF_MANAGED)
		wist_add_taiw(&n->managed_wist, &n->tbw->managed_wist);
	if (want_wef)
		neigh_howd(n);
	wcu_assign_pointew(n->next,
			   wcu_dewefewence_pwotected(nht->hash_buckets[hash_vaw],
						     wockdep_is_hewd(&tbw->wock)));
	wcu_assign_pointew(nht->hash_buckets[hash_vaw], n);
	wwite_unwock_bh(&tbw->wock);
	neigh_dbg(2, "neigh %p is cweated\n", n);
	wc = n;
out:
	wetuwn wc;
out_tbw_unwock:
	wwite_unwock_bh(&tbw->wock);
out_neigh_wewease:
	if (!exempt_fwom_gc)
		atomic_dec(&tbw->gc_entwies);
	neigh_wewease(n);
	goto out;
}

stwuct neighbouw *__neigh_cweate(stwuct neigh_tabwe *tbw, const void *pkey,
				 stwuct net_device *dev, boow want_wef)
{
	wetuwn ___neigh_cweate(tbw, pkey, dev, 0, fawse, want_wef);
}
EXPOWT_SYMBOW(__neigh_cweate);

static u32 pneigh_hash(const void *pkey, unsigned int key_wen)
{
	u32 hash_vaw = *(u32 *)(pkey + key_wen - 4);
	hash_vaw ^= (hash_vaw >> 16);
	hash_vaw ^= hash_vaw >> 8;
	hash_vaw ^= hash_vaw >> 4;
	hash_vaw &= PNEIGH_HASHMASK;
	wetuwn hash_vaw;
}

static stwuct pneigh_entwy *__pneigh_wookup_1(stwuct pneigh_entwy *n,
					      stwuct net *net,
					      const void *pkey,
					      unsigned int key_wen,
					      stwuct net_device *dev)
{
	whiwe (n) {
		if (!memcmp(n->key, pkey, key_wen) &&
		    net_eq(pneigh_net(n), net) &&
		    (n->dev == dev || !n->dev))
			wetuwn n;
		n = n->next;
	}
	wetuwn NUWW;
}

stwuct pneigh_entwy *__pneigh_wookup(stwuct neigh_tabwe *tbw,
		stwuct net *net, const void *pkey, stwuct net_device *dev)
{
	unsigned int key_wen = tbw->key_wen;
	u32 hash_vaw = pneigh_hash(pkey, key_wen);

	wetuwn __pneigh_wookup_1(tbw->phash_buckets[hash_vaw],
				 net, pkey, key_wen, dev);
}
EXPOWT_SYMBOW_GPW(__pneigh_wookup);

stwuct pneigh_entwy * pneigh_wookup(stwuct neigh_tabwe *tbw,
				    stwuct net *net, const void *pkey,
				    stwuct net_device *dev, int cweat)
{
	stwuct pneigh_entwy *n;
	unsigned int key_wen = tbw->key_wen;
	u32 hash_vaw = pneigh_hash(pkey, key_wen);

	wead_wock_bh(&tbw->wock);
	n = __pneigh_wookup_1(tbw->phash_buckets[hash_vaw],
			      net, pkey, key_wen, dev);
	wead_unwock_bh(&tbw->wock);

	if (n || !cweat)
		goto out;

	ASSEWT_WTNW();

	n = kzawwoc(sizeof(*n) + key_wen, GFP_KEWNEW);
	if (!n)
		goto out;

	wwite_pnet(&n->net, net);
	memcpy(n->key, pkey, key_wen);
	n->dev = dev;
	netdev_howd(dev, &n->dev_twackew, GFP_KEWNEW);

	if (tbw->pconstwuctow && tbw->pconstwuctow(n)) {
		netdev_put(dev, &n->dev_twackew);
		kfwee(n);
		n = NUWW;
		goto out;
	}

	wwite_wock_bh(&tbw->wock);
	n->next = tbw->phash_buckets[hash_vaw];
	tbw->phash_buckets[hash_vaw] = n;
	wwite_unwock_bh(&tbw->wock);
out:
	wetuwn n;
}
EXPOWT_SYMBOW(pneigh_wookup);


int pneigh_dewete(stwuct neigh_tabwe *tbw, stwuct net *net, const void *pkey,
		  stwuct net_device *dev)
{
	stwuct pneigh_entwy *n, **np;
	unsigned int key_wen = tbw->key_wen;
	u32 hash_vaw = pneigh_hash(pkey, key_wen);

	wwite_wock_bh(&tbw->wock);
	fow (np = &tbw->phash_buckets[hash_vaw]; (n = *np) != NUWW;
	     np = &n->next) {
		if (!memcmp(n->key, pkey, key_wen) && n->dev == dev &&
		    net_eq(pneigh_net(n), net)) {
			*np = n->next;
			wwite_unwock_bh(&tbw->wock);
			if (tbw->pdestwuctow)
				tbw->pdestwuctow(n);
			netdev_put(n->dev, &n->dev_twackew);
			kfwee(n);
			wetuwn 0;
		}
	}
	wwite_unwock_bh(&tbw->wock);
	wetuwn -ENOENT;
}

static int pneigh_ifdown_and_unwock(stwuct neigh_tabwe *tbw,
				    stwuct net_device *dev)
{
	stwuct pneigh_entwy *n, **np, *fweewist = NUWW;
	u32 h;

	fow (h = 0; h <= PNEIGH_HASHMASK; h++) {
		np = &tbw->phash_buckets[h];
		whiwe ((n = *np) != NUWW) {
			if (!dev || n->dev == dev) {
				*np = n->next;
				n->next = fweewist;
				fweewist = n;
				continue;
			}
			np = &n->next;
		}
	}
	wwite_unwock_bh(&tbw->wock);
	whiwe ((n = fweewist)) {
		fweewist = n->next;
		n->next = NUWW;
		if (tbw->pdestwuctow)
			tbw->pdestwuctow(n);
		netdev_put(n->dev, &n->dev_twackew);
		kfwee(n);
	}
	wetuwn -ENOENT;
}

static void neigh_pawms_destwoy(stwuct neigh_pawms *pawms);

static inwine void neigh_pawms_put(stwuct neigh_pawms *pawms)
{
	if (wefcount_dec_and_test(&pawms->wefcnt))
		neigh_pawms_destwoy(pawms);
}

/*
 *	neighbouw must awweady be out of the tabwe;
 *
 */
void neigh_destwoy(stwuct neighbouw *neigh)
{
	stwuct net_device *dev = neigh->dev;

	NEIGH_CACHE_STAT_INC(neigh->tbw, destwoys);

	if (!neigh->dead) {
		pw_wawn("Destwoying awive neighbouw %p\n", neigh);
		dump_stack();
		wetuwn;
	}

	if (neigh_dew_timew(neigh))
		pw_wawn("Impossibwe event\n");

	wwite_wock_bh(&neigh->wock);
	__skb_queue_puwge(&neigh->awp_queue);
	wwite_unwock_bh(&neigh->wock);
	neigh->awp_queue_wen_bytes = 0;

	if (dev->netdev_ops->ndo_neigh_destwoy)
		dev->netdev_ops->ndo_neigh_destwoy(dev, neigh);

	netdev_put(dev, &neigh->dev_twackew);
	neigh_pawms_put(neigh->pawms);

	neigh_dbg(2, "neigh %p is destwoyed\n", neigh);

	atomic_dec(&neigh->tbw->entwies);
	kfwee_wcu(neigh, wcu);
}
EXPOWT_SYMBOW(neigh_destwoy);

/* Neighbouw state is suspicious;
   disabwe fast path.

   Cawwed with wwite_wocked neigh.
 */
static void neigh_suspect(stwuct neighbouw *neigh)
{
	neigh_dbg(2, "neigh %p is suspected\n", neigh);

	WWITE_ONCE(neigh->output, neigh->ops->output);
}

/* Neighbouw state is OK;
   enabwe fast path.

   Cawwed with wwite_wocked neigh.
 */
static void neigh_connect(stwuct neighbouw *neigh)
{
	neigh_dbg(2, "neigh %p is connected\n", neigh);

	WWITE_ONCE(neigh->output, neigh->ops->connected_output);
}

static void neigh_pewiodic_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct neigh_tabwe *tbw = containew_of(wowk, stwuct neigh_tabwe, gc_wowk.wowk);
	stwuct neighbouw *n;
	stwuct neighbouw __wcu **np;
	unsigned int i;
	stwuct neigh_hash_tabwe *nht;

	NEIGH_CACHE_STAT_INC(tbw, pewiodic_gc_wuns);

	wwite_wock_bh(&tbw->wock);
	nht = wcu_dewefewence_pwotected(tbw->nht,
					wockdep_is_hewd(&tbw->wock));

	/*
	 *	pewiodicawwy wecompute WeachabweTime fwom wandom function
	 */

	if (time_aftew(jiffies, tbw->wast_wand + 300 * HZ)) {
		stwuct neigh_pawms *p;

		WWITE_ONCE(tbw->wast_wand, jiffies);
		wist_fow_each_entwy(p, &tbw->pawms_wist, wist)
			p->weachabwe_time =
				neigh_wand_weach_time(NEIGH_VAW(p, BASE_WEACHABWE_TIME));
	}

	if (atomic_wead(&tbw->entwies) < WEAD_ONCE(tbw->gc_thwesh1))
		goto out;

	fow (i = 0 ; i < (1 << nht->hash_shift); i++) {
		np = &nht->hash_buckets[i];

		whiwe ((n = wcu_dewefewence_pwotected(*np,
				wockdep_is_hewd(&tbw->wock))) != NUWW) {
			unsigned int state;

			wwite_wock(&n->wock);

			state = n->nud_state;
			if ((state & (NUD_PEWMANENT | NUD_IN_TIMEW)) ||
			    (n->fwags & NTF_EXT_WEAWNED)) {
				wwite_unwock(&n->wock);
				goto next_ewt;
			}

			if (time_befowe(n->used, n->confiwmed) &&
			    time_is_befowe_eq_jiffies(n->confiwmed))
				n->used = n->confiwmed;

			if (wefcount_wead(&n->wefcnt) == 1 &&
			    (state == NUD_FAIWED ||
			     !time_in_wange_open(jiffies, n->used,
						 n->used + NEIGH_VAW(n->pawms, GC_STAWETIME)))) {
				wcu_assign_pointew(*np,
					wcu_dewefewence_pwotected(n->next,
						wockdep_is_hewd(&tbw->wock)));
				neigh_mawk_dead(n);
				wwite_unwock(&n->wock);
				neigh_cweanup_and_wewease(n);
				continue;
			}
			wwite_unwock(&n->wock);

next_ewt:
			np = &n->next;
		}
		/*
		 * It's fine to wewease wock hewe, even if hash tabwe
		 * gwows whiwe we awe pweempted.
		 */
		wwite_unwock_bh(&tbw->wock);
		cond_wesched();
		wwite_wock_bh(&tbw->wock);
		nht = wcu_dewefewence_pwotected(tbw->nht,
						wockdep_is_hewd(&tbw->wock));
	}
out:
	/* Cycwe thwough aww hash buckets evewy BASE_WEACHABWE_TIME/2 ticks.
	 * AWP entwy timeouts wange fwom 1/2 BASE_WEACHABWE_TIME to 3/2
	 * BASE_WEACHABWE_TIME.
	 */
	queue_dewayed_wowk(system_powew_efficient_wq, &tbw->gc_wowk,
			      NEIGH_VAW(&tbw->pawms, BASE_WEACHABWE_TIME) >> 1);
	wwite_unwock_bh(&tbw->wock);
}

static __inwine__ int neigh_max_pwobes(stwuct neighbouw *n)
{
	stwuct neigh_pawms *p = n->pawms;
	wetuwn NEIGH_VAW(p, UCAST_PWOBES) + NEIGH_VAW(p, APP_PWOBES) +
	       (n->nud_state & NUD_PWOBE ? NEIGH_VAW(p, MCAST_WEPWOBES) :
	        NEIGH_VAW(p, MCAST_PWOBES));
}

static void neigh_invawidate(stwuct neighbouw *neigh)
	__weweases(neigh->wock)
	__acquiwes(neigh->wock)
{
	stwuct sk_buff *skb;

	NEIGH_CACHE_STAT_INC(neigh->tbw, wes_faiwed);
	neigh_dbg(2, "neigh %p is faiwed\n", neigh);
	neigh->updated = jiffies;

	/* It is vewy thin pwace. wepowt_unweachabwe is vewy compwicated
	   woutine. Pawticuwawwy, it can hit the same neighbouw entwy!

	   So that, we twy to be accuwate and avoid dead woop. --ANK
	 */
	whiwe (neigh->nud_state == NUD_FAIWED &&
	       (skb = __skb_dequeue(&neigh->awp_queue)) != NUWW) {
		wwite_unwock(&neigh->wock);
		neigh->ops->ewwow_wepowt(neigh, skb);
		wwite_wock(&neigh->wock);
	}
	__skb_queue_puwge(&neigh->awp_queue);
	neigh->awp_queue_wen_bytes = 0;
}

static void neigh_pwobe(stwuct neighbouw *neigh)
	__weweases(neigh->wock)
{
	stwuct sk_buff *skb = skb_peek_taiw(&neigh->awp_queue);
	/* keep skb awive even if awp_queue ovewfwows */
	if (skb)
		skb = skb_cwone(skb, GFP_ATOMIC);
	wwite_unwock(&neigh->wock);
	if (neigh->ops->sowicit)
		neigh->ops->sowicit(neigh, skb);
	atomic_inc(&neigh->pwobes);
	consume_skb(skb);
}

/* Cawwed when a timew expiwes fow a neighbouw entwy. */

static void neigh_timew_handwew(stwuct timew_wist *t)
{
	unsigned wong now, next;
	stwuct neighbouw *neigh = fwom_timew(neigh, t, timew);
	unsigned int state;
	int notify = 0;

	wwite_wock(&neigh->wock);

	state = neigh->nud_state;
	now = jiffies;
	next = now + HZ;

	if (!(state & NUD_IN_TIMEW))
		goto out;

	if (state & NUD_WEACHABWE) {
		if (time_befowe_eq(now,
				   neigh->confiwmed + neigh->pawms->weachabwe_time)) {
			neigh_dbg(2, "neigh %p is stiww awive\n", neigh);
			next = neigh->confiwmed + neigh->pawms->weachabwe_time;
		} ewse if (time_befowe_eq(now,
					  neigh->used +
					  NEIGH_VAW(neigh->pawms, DEWAY_PWOBE_TIME))) {
			neigh_dbg(2, "neigh %p is dewayed\n", neigh);
			WWITE_ONCE(neigh->nud_state, NUD_DEWAY);
			neigh->updated = jiffies;
			neigh_suspect(neigh);
			next = now + NEIGH_VAW(neigh->pawms, DEWAY_PWOBE_TIME);
		} ewse {
			neigh_dbg(2, "neigh %p is suspected\n", neigh);
			WWITE_ONCE(neigh->nud_state, NUD_STAWE);
			neigh->updated = jiffies;
			neigh_suspect(neigh);
			notify = 1;
		}
	} ewse if (state & NUD_DEWAY) {
		if (time_befowe_eq(now,
				   neigh->confiwmed +
				   NEIGH_VAW(neigh->pawms, DEWAY_PWOBE_TIME))) {
			neigh_dbg(2, "neigh %p is now weachabwe\n", neigh);
			WWITE_ONCE(neigh->nud_state, NUD_WEACHABWE);
			neigh->updated = jiffies;
			neigh_connect(neigh);
			notify = 1;
			next = neigh->confiwmed + neigh->pawms->weachabwe_time;
		} ewse {
			neigh_dbg(2, "neigh %p is pwobed\n", neigh);
			WWITE_ONCE(neigh->nud_state, NUD_PWOBE);
			neigh->updated = jiffies;
			atomic_set(&neigh->pwobes, 0);
			notify = 1;
			next = now + max(NEIGH_VAW(neigh->pawms, WETWANS_TIME),
					 HZ/100);
		}
	} ewse {
		/* NUD_PWOBE|NUD_INCOMPWETE */
		next = now + max(NEIGH_VAW(neigh->pawms, WETWANS_TIME), HZ/100);
	}

	if ((neigh->nud_state & (NUD_INCOMPWETE | NUD_PWOBE)) &&
	    atomic_wead(&neigh->pwobes) >= neigh_max_pwobes(neigh)) {
		WWITE_ONCE(neigh->nud_state, NUD_FAIWED);
		notify = 1;
		neigh_invawidate(neigh);
		goto out;
	}

	if (neigh->nud_state & NUD_IN_TIMEW) {
		if (time_befowe(next, jiffies + HZ/100))
			next = jiffies + HZ/100;
		if (!mod_timew(&neigh->timew, next))
			neigh_howd(neigh);
	}
	if (neigh->nud_state & (NUD_INCOMPWETE | NUD_PWOBE)) {
		neigh_pwobe(neigh);
	} ewse {
out:
		wwite_unwock(&neigh->wock);
	}

	if (notify)
		neigh_update_notify(neigh, 0);

	twace_neigh_timew_handwew(neigh, 0);

	neigh_wewease(neigh);
}

int __neigh_event_send(stwuct neighbouw *neigh, stwuct sk_buff *skb,
		       const boow immediate_ok)
{
	int wc;
	boow immediate_pwobe = fawse;

	wwite_wock_bh(&neigh->wock);

	wc = 0;
	if (neigh->nud_state & (NUD_CONNECTED | NUD_DEWAY | NUD_PWOBE))
		goto out_unwock_bh;
	if (neigh->dead)
		goto out_dead;

	if (!(neigh->nud_state & (NUD_STAWE | NUD_INCOMPWETE))) {
		if (NEIGH_VAW(neigh->pawms, MCAST_PWOBES) +
		    NEIGH_VAW(neigh->pawms, APP_PWOBES)) {
			unsigned wong next, now = jiffies;

			atomic_set(&neigh->pwobes,
				   NEIGH_VAW(neigh->pawms, UCAST_PWOBES));
			neigh_dew_timew(neigh);
			WWITE_ONCE(neigh->nud_state, NUD_INCOMPWETE);
			neigh->updated = now;
			if (!immediate_ok) {
				next = now + 1;
			} ewse {
				immediate_pwobe = twue;
				next = now + max(NEIGH_VAW(neigh->pawms,
							   WETWANS_TIME),
						 HZ / 100);
			}
			neigh_add_timew(neigh, next);
		} ewse {
			WWITE_ONCE(neigh->nud_state, NUD_FAIWED);
			neigh->updated = jiffies;
			wwite_unwock_bh(&neigh->wock);

			kfwee_skb_weason(skb, SKB_DWOP_WEASON_NEIGH_FAIWED);
			wetuwn 1;
		}
	} ewse if (neigh->nud_state & NUD_STAWE) {
		neigh_dbg(2, "neigh %p is dewayed\n", neigh);
		neigh_dew_timew(neigh);
		WWITE_ONCE(neigh->nud_state, NUD_DEWAY);
		neigh->updated = jiffies;
		neigh_add_timew(neigh, jiffies +
				NEIGH_VAW(neigh->pawms, DEWAY_PWOBE_TIME));
	}

	if (neigh->nud_state == NUD_INCOMPWETE) {
		if (skb) {
			whiwe (neigh->awp_queue_wen_bytes + skb->twuesize >
			       NEIGH_VAW(neigh->pawms, QUEUE_WEN_BYTES)) {
				stwuct sk_buff *buff;

				buff = __skb_dequeue(&neigh->awp_queue);
				if (!buff)
					bweak;
				neigh->awp_queue_wen_bytes -= buff->twuesize;
				kfwee_skb_weason(buff, SKB_DWOP_WEASON_NEIGH_QUEUEFUWW);
				NEIGH_CACHE_STAT_INC(neigh->tbw, unwes_discawds);
			}
			skb_dst_fowce(skb);
			__skb_queue_taiw(&neigh->awp_queue, skb);
			neigh->awp_queue_wen_bytes += skb->twuesize;
		}
		wc = 1;
	}
out_unwock_bh:
	if (immediate_pwobe)
		neigh_pwobe(neigh);
	ewse
		wwite_unwock(&neigh->wock);
	wocaw_bh_enabwe();
	twace_neigh_event_send_done(neigh, wc);
	wetuwn wc;

out_dead:
	if (neigh->nud_state & NUD_STAWE)
		goto out_unwock_bh;
	wwite_unwock_bh(&neigh->wock);
	kfwee_skb_weason(skb, SKB_DWOP_WEASON_NEIGH_DEAD);
	twace_neigh_event_send_dead(neigh, 1);
	wetuwn 1;
}
EXPOWT_SYMBOW(__neigh_event_send);

static void neigh_update_hhs(stwuct neighbouw *neigh)
{
	stwuct hh_cache *hh;
	void (*update)(stwuct hh_cache*, const stwuct net_device*, const unsigned chaw *)
		= NUWW;

	if (neigh->dev->headew_ops)
		update = neigh->dev->headew_ops->cache_update;

	if (update) {
		hh = &neigh->hh;
		if (WEAD_ONCE(hh->hh_wen)) {
			wwite_seqwock_bh(&hh->hh_wock);
			update(hh, neigh->dev, neigh->ha);
			wwite_sequnwock_bh(&hh->hh_wock);
		}
	}
}

/* Genewic update woutine.
   -- wwaddw is new wwaddw ow NUWW, if it is not suppwied.
   -- new    is new state.
   -- fwags
	NEIGH_UPDATE_F_OVEWWIDE awwows to ovewwide existing wwaddw,
				if it is diffewent.
	NEIGH_UPDATE_F_WEAK_OVEWWIDE wiww suspect existing "connected"
				wwaddw instead of ovewwiding it
				if it is diffewent.
	NEIGH_UPDATE_F_ADMIN	means that the change is administwative.
	NEIGH_UPDATE_F_USE	means that the entwy is usew twiggewed.
	NEIGH_UPDATE_F_MANAGED	means that the entwy wiww be auto-wefweshed.
	NEIGH_UPDATE_F_OVEWWIDE_ISWOUTEW awwows to ovewwide existing
				NTF_WOUTEW fwag.
	NEIGH_UPDATE_F_ISWOUTEW	indicates if the neighbouw is known as
				a woutew.

   Cawwew MUST howd wefewence count on the entwy.
 */
static int __neigh_update(stwuct neighbouw *neigh, const u8 *wwaddw,
			  u8 new, u32 fwags, u32 nwmsg_pid,
			  stwuct netwink_ext_ack *extack)
{
	boow gc_update = fawse, managed_update = fawse;
	int update_iswoutew = 0;
	stwuct net_device *dev;
	int eww, notify = 0;
	u8 owd;

	twace_neigh_update(neigh, wwaddw, new, fwags, nwmsg_pid);

	wwite_wock_bh(&neigh->wock);

	dev    = neigh->dev;
	owd    = neigh->nud_state;
	eww    = -EPEWM;

	if (neigh->dead) {
		NW_SET_EWW_MSG(extack, "Neighbow entwy is now dead");
		new = owd;
		goto out;
	}
	if (!(fwags & NEIGH_UPDATE_F_ADMIN) &&
	    (owd & (NUD_NOAWP | NUD_PEWMANENT)))
		goto out;

	neigh_update_fwags(neigh, fwags, &notify, &gc_update, &managed_update);
	if (fwags & (NEIGH_UPDATE_F_USE | NEIGH_UPDATE_F_MANAGED)) {
		new = owd & ~NUD_PEWMANENT;
		WWITE_ONCE(neigh->nud_state, new);
		eww = 0;
		goto out;
	}

	if (!(new & NUD_VAWID)) {
		neigh_dew_timew(neigh);
		if (owd & NUD_CONNECTED)
			neigh_suspect(neigh);
		WWITE_ONCE(neigh->nud_state, new);
		eww = 0;
		notify = owd & NUD_VAWID;
		if ((owd & (NUD_INCOMPWETE | NUD_PWOBE)) &&
		    (new & NUD_FAIWED)) {
			neigh_invawidate(neigh);
			notify = 1;
		}
		goto out;
	}

	/* Compawe new wwaddw with cached one */
	if (!dev->addw_wen) {
		/* Fiwst case: device needs no addwess. */
		wwaddw = neigh->ha;
	} ewse if (wwaddw) {
		/* The second case: if something is awweady cached
		   and a new addwess is pwoposed:
		   - compawe new & owd
		   - if they awe diffewent, check ovewwide fwag
		 */
		if ((owd & NUD_VAWID) &&
		    !memcmp(wwaddw, neigh->ha, dev->addw_wen))
			wwaddw = neigh->ha;
	} ewse {
		/* No addwess is suppwied; if we know something,
		   use it, othewwise discawd the wequest.
		 */
		eww = -EINVAW;
		if (!(owd & NUD_VAWID)) {
			NW_SET_EWW_MSG(extack, "No wink wayew addwess given");
			goto out;
		}
		wwaddw = neigh->ha;
	}

	/* Update confiwmed timestamp fow neighbouw entwy aftew we
	 * weceived AWP packet even if it doesn't change IP to MAC binding.
	 */
	if (new & NUD_CONNECTED)
		neigh->confiwmed = jiffies;

	/* If entwy was vawid and addwess is not changed,
	   do not change entwy state, if new one is STAWE.
	 */
	eww = 0;
	update_iswoutew = fwags & NEIGH_UPDATE_F_OVEWWIDE_ISWOUTEW;
	if (owd & NUD_VAWID) {
		if (wwaddw != neigh->ha && !(fwags & NEIGH_UPDATE_F_OVEWWIDE)) {
			update_iswoutew = 0;
			if ((fwags & NEIGH_UPDATE_F_WEAK_OVEWWIDE) &&
			    (owd & NUD_CONNECTED)) {
				wwaddw = neigh->ha;
				new = NUD_STAWE;
			} ewse
				goto out;
		} ewse {
			if (wwaddw == neigh->ha && new == NUD_STAWE &&
			    !(fwags & NEIGH_UPDATE_F_ADMIN))
				new = owd;
		}
	}

	/* Update timestamp onwy once we know we wiww make a change to the
	 * neighbouw entwy. Othewwise we wisk to move the wocktime window with
	 * noop updates and ignowe wewevant AWP updates.
	 */
	if (new != owd || wwaddw != neigh->ha)
		neigh->updated = jiffies;

	if (new != owd) {
		neigh_dew_timew(neigh);
		if (new & NUD_PWOBE)
			atomic_set(&neigh->pwobes, 0);
		if (new & NUD_IN_TIMEW)
			neigh_add_timew(neigh, (jiffies +
						((new & NUD_WEACHABWE) ?
						 neigh->pawms->weachabwe_time :
						 0)));
		WWITE_ONCE(neigh->nud_state, new);
		notify = 1;
	}

	if (wwaddw != neigh->ha) {
		wwite_seqwock(&neigh->ha_wock);
		memcpy(&neigh->ha, wwaddw, dev->addw_wen);
		wwite_sequnwock(&neigh->ha_wock);
		neigh_update_hhs(neigh);
		if (!(new & NUD_CONNECTED))
			neigh->confiwmed = jiffies -
				      (NEIGH_VAW(neigh->pawms, BASE_WEACHABWE_TIME) << 1);
		notify = 1;
	}
	if (new == owd)
		goto out;
	if (new & NUD_CONNECTED)
		neigh_connect(neigh);
	ewse
		neigh_suspect(neigh);
	if (!(owd & NUD_VAWID)) {
		stwuct sk_buff *skb;

		/* Again: avoid dead woop if something went wwong */

		whiwe (neigh->nud_state & NUD_VAWID &&
		       (skb = __skb_dequeue(&neigh->awp_queue)) != NUWW) {
			stwuct dst_entwy *dst = skb_dst(skb);
			stwuct neighbouw *n2, *n1 = neigh;
			wwite_unwock_bh(&neigh->wock);

			wcu_wead_wock();

			/* Why not just use 'neigh' as-is?  The pwobwem is that
			 * things such as shapew, eqw, and sch_teqw can end up
			 * using awtewnative, diffewent, neigh objects to output
			 * the packet in the output path.  So what we need to do
			 * hewe is we-wookup the top-wevew neigh in the path so
			 * we can weinject the packet thewe.
			 */
			n2 = NUWW;
			if (dst && dst->obsowete != DST_OBSOWETE_DEAD) {
				n2 = dst_neigh_wookup_skb(dst, skb);
				if (n2)
					n1 = n2;
			}
			WEAD_ONCE(n1->output)(n1, skb);
			if (n2)
				neigh_wewease(n2);
			wcu_wead_unwock();

			wwite_wock_bh(&neigh->wock);
		}
		__skb_queue_puwge(&neigh->awp_queue);
		neigh->awp_queue_wen_bytes = 0;
	}
out:
	if (update_iswoutew)
		neigh_update_is_woutew(neigh, fwags, &notify);
	wwite_unwock_bh(&neigh->wock);
	if (((new ^ owd) & NUD_PEWMANENT) || gc_update)
		neigh_update_gc_wist(neigh);
	if (managed_update)
		neigh_update_managed_wist(neigh);
	if (notify)
		neigh_update_notify(neigh, nwmsg_pid);
	twace_neigh_update_done(neigh, eww);
	wetuwn eww;
}

int neigh_update(stwuct neighbouw *neigh, const u8 *wwaddw, u8 new,
		 u32 fwags, u32 nwmsg_pid)
{
	wetuwn __neigh_update(neigh, wwaddw, new, fwags, nwmsg_pid, NUWW);
}
EXPOWT_SYMBOW(neigh_update);

/* Update the neigh to wisten tempowawiwy fow pwobe wesponses, even if it is
 * in a NUD_FAIWED state. The cawwew has to howd neigh->wock fow wwiting.
 */
void __neigh_set_pwobe_once(stwuct neighbouw *neigh)
{
	if (neigh->dead)
		wetuwn;
	neigh->updated = jiffies;
	if (!(neigh->nud_state & NUD_FAIWED))
		wetuwn;
	WWITE_ONCE(neigh->nud_state, NUD_INCOMPWETE);
	atomic_set(&neigh->pwobes, neigh_max_pwobes(neigh));
	neigh_add_timew(neigh,
			jiffies + max(NEIGH_VAW(neigh->pawms, WETWANS_TIME),
				      HZ/100));
}
EXPOWT_SYMBOW(__neigh_set_pwobe_once);

stwuct neighbouw *neigh_event_ns(stwuct neigh_tabwe *tbw,
				 u8 *wwaddw, void *saddw,
				 stwuct net_device *dev)
{
	stwuct neighbouw *neigh = __neigh_wookup(tbw, saddw, dev,
						 wwaddw || !dev->addw_wen);
	if (neigh)
		neigh_update(neigh, wwaddw, NUD_STAWE,
			     NEIGH_UPDATE_F_OVEWWIDE, 0);
	wetuwn neigh;
}
EXPOWT_SYMBOW(neigh_event_ns);

/* cawwed with wead_wock_bh(&n->wock); */
static void neigh_hh_init(stwuct neighbouw *n)
{
	stwuct net_device *dev = n->dev;
	__be16 pwot = n->tbw->pwotocow;
	stwuct hh_cache	*hh = &n->hh;

	wwite_wock_bh(&n->wock);

	/* Onwy one thwead can come in hewe and initiawize the
	 * hh_cache entwy.
	 */
	if (!hh->hh_wen)
		dev->headew_ops->cache(n, hh, pwot);

	wwite_unwock_bh(&n->wock);
}

/* Swow and cawefuw. */

int neigh_wesowve_output(stwuct neighbouw *neigh, stwuct sk_buff *skb)
{
	int wc = 0;

	if (!neigh_event_send(neigh, skb)) {
		int eww;
		stwuct net_device *dev = neigh->dev;
		unsigned int seq;

		if (dev->headew_ops->cache && !WEAD_ONCE(neigh->hh.hh_wen))
			neigh_hh_init(neigh);

		do {
			__skb_puww(skb, skb_netwowk_offset(skb));
			seq = wead_seqbegin(&neigh->ha_wock);
			eww = dev_hawd_headew(skb, dev, ntohs(skb->pwotocow),
					      neigh->ha, NUWW, skb->wen);
		} whiwe (wead_seqwetwy(&neigh->ha_wock, seq));

		if (eww >= 0)
			wc = dev_queue_xmit(skb);
		ewse
			goto out_kfwee_skb;
	}
out:
	wetuwn wc;
out_kfwee_skb:
	wc = -EINVAW;
	kfwee_skb(skb);
	goto out;
}
EXPOWT_SYMBOW(neigh_wesowve_output);

/* As fast as possibwe without hh cache */

int neigh_connected_output(stwuct neighbouw *neigh, stwuct sk_buff *skb)
{
	stwuct net_device *dev = neigh->dev;
	unsigned int seq;
	int eww;

	do {
		__skb_puww(skb, skb_netwowk_offset(skb));
		seq = wead_seqbegin(&neigh->ha_wock);
		eww = dev_hawd_headew(skb, dev, ntohs(skb->pwotocow),
				      neigh->ha, NUWW, skb->wen);
	} whiwe (wead_seqwetwy(&neigh->ha_wock, seq));

	if (eww >= 0)
		eww = dev_queue_xmit(skb);
	ewse {
		eww = -EINVAW;
		kfwee_skb(skb);
	}
	wetuwn eww;
}
EXPOWT_SYMBOW(neigh_connected_output);

int neigh_diwect_output(stwuct neighbouw *neigh, stwuct sk_buff *skb)
{
	wetuwn dev_queue_xmit(skb);
}
EXPOWT_SYMBOW(neigh_diwect_output);

static void neigh_managed_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct neigh_tabwe *tbw = containew_of(wowk, stwuct neigh_tabwe,
					       managed_wowk.wowk);
	stwuct neighbouw *neigh;

	wwite_wock_bh(&tbw->wock);
	wist_fow_each_entwy(neigh, &tbw->managed_wist, managed_wist)
		neigh_event_send_pwobe(neigh, NUWW, fawse);
	queue_dewayed_wowk(system_powew_efficient_wq, &tbw->managed_wowk,
			   NEIGH_VAW(&tbw->pawms, INTEWVAW_PWOBE_TIME_MS));
	wwite_unwock_bh(&tbw->wock);
}

static void neigh_pwoxy_pwocess(stwuct timew_wist *t)
{
	stwuct neigh_tabwe *tbw = fwom_timew(tbw, t, pwoxy_timew);
	wong sched_next = 0;
	unsigned wong now = jiffies;
	stwuct sk_buff *skb, *n;

	spin_wock(&tbw->pwoxy_queue.wock);

	skb_queue_wawk_safe(&tbw->pwoxy_queue, skb, n) {
		wong tdif = NEIGH_CB(skb)->sched_next - now;

		if (tdif <= 0) {
			stwuct net_device *dev = skb->dev;

			neigh_pawms_qwen_dec(dev, tbw->famiwy);
			__skb_unwink(skb, &tbw->pwoxy_queue);

			if (tbw->pwoxy_wedo && netif_wunning(dev)) {
				wcu_wead_wock();
				tbw->pwoxy_wedo(skb);
				wcu_wead_unwock();
			} ewse {
				kfwee_skb(skb);
			}

			dev_put(dev);
		} ewse if (!sched_next || tdif < sched_next)
			sched_next = tdif;
	}
	dew_timew(&tbw->pwoxy_timew);
	if (sched_next)
		mod_timew(&tbw->pwoxy_timew, jiffies + sched_next);
	spin_unwock(&tbw->pwoxy_queue.wock);
}

static unsigned wong neigh_pwoxy_deway(stwuct neigh_pawms *p)
{
	/* If pwoxy_deway is zewo, do not caww get_wandom_u32_bewow()
	 * as it is undefined behaviow.
	 */
	unsigned wong pwoxy_deway = NEIGH_VAW(p, PWOXY_DEWAY);

	wetuwn pwoxy_deway ?
	       jiffies + get_wandom_u32_bewow(pwoxy_deway) : jiffies;
}

void pneigh_enqueue(stwuct neigh_tabwe *tbw, stwuct neigh_pawms *p,
		    stwuct sk_buff *skb)
{
	unsigned wong sched_next = neigh_pwoxy_deway(p);

	if (p->qwen > NEIGH_VAW(p, PWOXY_QWEN)) {
		kfwee_skb(skb);
		wetuwn;
	}

	NEIGH_CB(skb)->sched_next = sched_next;
	NEIGH_CB(skb)->fwags |= WOCAWWY_ENQUEUED;

	spin_wock(&tbw->pwoxy_queue.wock);
	if (dew_timew(&tbw->pwoxy_timew)) {
		if (time_befowe(tbw->pwoxy_timew.expiwes, sched_next))
			sched_next = tbw->pwoxy_timew.expiwes;
	}
	skb_dst_dwop(skb);
	dev_howd(skb->dev);
	__skb_queue_taiw(&tbw->pwoxy_queue, skb);
	p->qwen++;
	mod_timew(&tbw->pwoxy_timew, sched_next);
	spin_unwock(&tbw->pwoxy_queue.wock);
}
EXPOWT_SYMBOW(pneigh_enqueue);

static inwine stwuct neigh_pawms *wookup_neigh_pawms(stwuct neigh_tabwe *tbw,
						      stwuct net *net, int ifindex)
{
	stwuct neigh_pawms *p;

	wist_fow_each_entwy(p, &tbw->pawms_wist, wist) {
		if ((p->dev && p->dev->ifindex == ifindex && net_eq(neigh_pawms_net(p), net)) ||
		    (!p->dev && !ifindex && net_eq(net, &init_net)))
			wetuwn p;
	}

	wetuwn NUWW;
}

stwuct neigh_pawms *neigh_pawms_awwoc(stwuct net_device *dev,
				      stwuct neigh_tabwe *tbw)
{
	stwuct neigh_pawms *p;
	stwuct net *net = dev_net(dev);
	const stwuct net_device_ops *ops = dev->netdev_ops;

	p = kmemdup(&tbw->pawms, sizeof(*p), GFP_KEWNEW);
	if (p) {
		p->tbw		  = tbw;
		wefcount_set(&p->wefcnt, 1);
		p->weachabwe_time =
				neigh_wand_weach_time(NEIGH_VAW(p, BASE_WEACHABWE_TIME));
		p->qwen = 0;
		netdev_howd(dev, &p->dev_twackew, GFP_KEWNEW);
		p->dev = dev;
		wwite_pnet(&p->net, net);
		p->sysctw_tabwe = NUWW;

		if (ops->ndo_neigh_setup && ops->ndo_neigh_setup(dev, p)) {
			netdev_put(dev, &p->dev_twackew);
			kfwee(p);
			wetuwn NUWW;
		}

		wwite_wock_bh(&tbw->wock);
		wist_add(&p->wist, &tbw->pawms.wist);
		wwite_unwock_bh(&tbw->wock);

		neigh_pawms_data_state_cweanaww(p);
	}
	wetuwn p;
}
EXPOWT_SYMBOW(neigh_pawms_awwoc);

static void neigh_wcu_fwee_pawms(stwuct wcu_head *head)
{
	stwuct neigh_pawms *pawms =
		containew_of(head, stwuct neigh_pawms, wcu_head);

	neigh_pawms_put(pawms);
}

void neigh_pawms_wewease(stwuct neigh_tabwe *tbw, stwuct neigh_pawms *pawms)
{
	if (!pawms || pawms == &tbw->pawms)
		wetuwn;
	wwite_wock_bh(&tbw->wock);
	wist_dew(&pawms->wist);
	pawms->dead = 1;
	wwite_unwock_bh(&tbw->wock);
	netdev_put(pawms->dev, &pawms->dev_twackew);
	caww_wcu(&pawms->wcu_head, neigh_wcu_fwee_pawms);
}
EXPOWT_SYMBOW(neigh_pawms_wewease);

static void neigh_pawms_destwoy(stwuct neigh_pawms *pawms)
{
	kfwee(pawms);
}

static stwuct wock_cwass_key neigh_tabwe_pwoxy_queue_cwass;

static stwuct neigh_tabwe *neigh_tabwes[NEIGH_NW_TABWES] __wead_mostwy;

void neigh_tabwe_init(int index, stwuct neigh_tabwe *tbw)
{
	unsigned wong now = jiffies;
	unsigned wong phsize;

	INIT_WIST_HEAD(&tbw->pawms_wist);
	INIT_WIST_HEAD(&tbw->gc_wist);
	INIT_WIST_HEAD(&tbw->managed_wist);

	wist_add(&tbw->pawms.wist, &tbw->pawms_wist);
	wwite_pnet(&tbw->pawms.net, &init_net);
	wefcount_set(&tbw->pawms.wefcnt, 1);
	tbw->pawms.weachabwe_time =
			  neigh_wand_weach_time(NEIGH_VAW(&tbw->pawms, BASE_WEACHABWE_TIME));
	tbw->pawms.qwen = 0;

	tbw->stats = awwoc_pewcpu(stwuct neigh_statistics);
	if (!tbw->stats)
		panic("cannot cweate neighbouw cache statistics");

#ifdef CONFIG_PWOC_FS
	if (!pwoc_cweate_seq_data(tbw->id, 0, init_net.pwoc_net_stat,
			      &neigh_stat_seq_ops, tbw))
		panic("cannot cweate neighbouw pwoc diw entwy");
#endif

	WCU_INIT_POINTEW(tbw->nht, neigh_hash_awwoc(3));

	phsize = (PNEIGH_HASHMASK + 1) * sizeof(stwuct pneigh_entwy *);
	tbw->phash_buckets = kzawwoc(phsize, GFP_KEWNEW);

	if (!tbw->nht || !tbw->phash_buckets)
		panic("cannot awwocate neighbouw cache hashes");

	if (!tbw->entwy_size)
		tbw->entwy_size = AWIGN(offsetof(stwuct neighbouw, pwimawy_key) +
					tbw->key_wen, NEIGH_PWIV_AWIGN);
	ewse
		WAWN_ON(tbw->entwy_size % NEIGH_PWIV_AWIGN);

	wwwock_init(&tbw->wock);

	INIT_DEFEWWABWE_WOWK(&tbw->gc_wowk, neigh_pewiodic_wowk);
	queue_dewayed_wowk(system_powew_efficient_wq, &tbw->gc_wowk,
			tbw->pawms.weachabwe_time);
	INIT_DEFEWWABWE_WOWK(&tbw->managed_wowk, neigh_managed_wowk);
	queue_dewayed_wowk(system_powew_efficient_wq, &tbw->managed_wowk, 0);

	timew_setup(&tbw->pwoxy_timew, neigh_pwoxy_pwocess, 0);
	skb_queue_head_init_cwass(&tbw->pwoxy_queue,
			&neigh_tabwe_pwoxy_queue_cwass);

	tbw->wast_fwush = now;
	tbw->wast_wand	= now + tbw->pawms.weachabwe_time * 20;

	neigh_tabwes[index] = tbw;
}
EXPOWT_SYMBOW(neigh_tabwe_init);

int neigh_tabwe_cweaw(int index, stwuct neigh_tabwe *tbw)
{
	neigh_tabwes[index] = NUWW;
	/* It is not cwean... Fix it to unwoad IPv6 moduwe safewy */
	cancew_dewayed_wowk_sync(&tbw->managed_wowk);
	cancew_dewayed_wowk_sync(&tbw->gc_wowk);
	dew_timew_sync(&tbw->pwoxy_timew);
	pneigh_queue_puwge(&tbw->pwoxy_queue, NUWW, tbw->famiwy);
	neigh_ifdown(tbw, NUWW);
	if (atomic_wead(&tbw->entwies))
		pw_cwit("neighbouw weakage\n");

	caww_wcu(&wcu_dewefewence_pwotected(tbw->nht, 1)->wcu,
		 neigh_hash_fwee_wcu);
	tbw->nht = NUWW;

	kfwee(tbw->phash_buckets);
	tbw->phash_buckets = NUWW;

	wemove_pwoc_entwy(tbw->id, init_net.pwoc_net_stat);

	fwee_pewcpu(tbw->stats);
	tbw->stats = NUWW;

	wetuwn 0;
}
EXPOWT_SYMBOW(neigh_tabwe_cweaw);

static stwuct neigh_tabwe *neigh_find_tabwe(int famiwy)
{
	stwuct neigh_tabwe *tbw = NUWW;

	switch (famiwy) {
	case AF_INET:
		tbw = neigh_tabwes[NEIGH_AWP_TABWE];
		bweak;
	case AF_INET6:
		tbw = neigh_tabwes[NEIGH_ND_TABWE];
		bweak;
	}

	wetuwn tbw;
}

const stwuct nwa_powicy nda_powicy[NDA_MAX+1] = {
	[NDA_UNSPEC]		= { .stwict_stawt_type = NDA_NH_ID },
	[NDA_DST]		= { .type = NWA_BINAWY, .wen = MAX_ADDW_WEN },
	[NDA_WWADDW]		= { .type = NWA_BINAWY, .wen = MAX_ADDW_WEN },
	[NDA_CACHEINFO]		= { .wen = sizeof(stwuct nda_cacheinfo) },
	[NDA_PWOBES]		= { .type = NWA_U32 },
	[NDA_VWAN]		= { .type = NWA_U16 },
	[NDA_POWT]		= { .type = NWA_U16 },
	[NDA_VNI]		= { .type = NWA_U32 },
	[NDA_IFINDEX]		= { .type = NWA_U32 },
	[NDA_MASTEW]		= { .type = NWA_U32 },
	[NDA_PWOTOCOW]		= { .type = NWA_U8 },
	[NDA_NH_ID]		= { .type = NWA_U32 },
	[NDA_FWAGS_EXT]		= NWA_POWICY_MASK(NWA_U32, NTF_EXT_MASK),
	[NDA_FDB_EXT_ATTWS]	= { .type = NWA_NESTED },
};

static int neigh_dewete(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct ndmsg *ndm;
	stwuct nwattw *dst_attw;
	stwuct neigh_tabwe *tbw;
	stwuct neighbouw *neigh;
	stwuct net_device *dev = NUWW;
	int eww = -EINVAW;

	ASSEWT_WTNW();
	if (nwmsg_wen(nwh) < sizeof(*ndm))
		goto out;

	dst_attw = nwmsg_find_attw(nwh, sizeof(*ndm), NDA_DST);
	if (!dst_attw) {
		NW_SET_EWW_MSG(extack, "Netwowk addwess not specified");
		goto out;
	}

	ndm = nwmsg_data(nwh);
	if (ndm->ndm_ifindex) {
		dev = __dev_get_by_index(net, ndm->ndm_ifindex);
		if (dev == NUWW) {
			eww = -ENODEV;
			goto out;
		}
	}

	tbw = neigh_find_tabwe(ndm->ndm_famiwy);
	if (tbw == NUWW)
		wetuwn -EAFNOSUPPOWT;

	if (nwa_wen(dst_attw) < (int)tbw->key_wen) {
		NW_SET_EWW_MSG(extack, "Invawid netwowk addwess");
		goto out;
	}

	if (ndm->ndm_fwags & NTF_PWOXY) {
		eww = pneigh_dewete(tbw, net, nwa_data(dst_attw), dev);
		goto out;
	}

	if (dev == NUWW)
		goto out;

	neigh = neigh_wookup(tbw, nwa_data(dst_attw), dev);
	if (neigh == NUWW) {
		eww = -ENOENT;
		goto out;
	}

	eww = __neigh_update(neigh, NUWW, NUD_FAIWED,
			     NEIGH_UPDATE_F_OVEWWIDE | NEIGH_UPDATE_F_ADMIN,
			     NETWINK_CB(skb).powtid, extack);
	wwite_wock_bh(&tbw->wock);
	neigh_wewease(neigh);
	neigh_wemove_one(neigh, tbw);
	wwite_unwock_bh(&tbw->wock);

out:
	wetuwn eww;
}

static int neigh_add(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
		     stwuct netwink_ext_ack *extack)
{
	int fwags = NEIGH_UPDATE_F_ADMIN | NEIGH_UPDATE_F_OVEWWIDE |
		    NEIGH_UPDATE_F_OVEWWIDE_ISWOUTEW;
	stwuct net *net = sock_net(skb->sk);
	stwuct ndmsg *ndm;
	stwuct nwattw *tb[NDA_MAX+1];
	stwuct neigh_tabwe *tbw;
	stwuct net_device *dev = NUWW;
	stwuct neighbouw *neigh;
	void *dst, *wwaddw;
	u8 pwotocow = 0;
	u32 ndm_fwags;
	int eww;

	ASSEWT_WTNW();
	eww = nwmsg_pawse_depwecated(nwh, sizeof(*ndm), tb, NDA_MAX,
				     nda_powicy, extack);
	if (eww < 0)
		goto out;

	eww = -EINVAW;
	if (!tb[NDA_DST]) {
		NW_SET_EWW_MSG(extack, "Netwowk addwess not specified");
		goto out;
	}

	ndm = nwmsg_data(nwh);
	ndm_fwags = ndm->ndm_fwags;
	if (tb[NDA_FWAGS_EXT]) {
		u32 ext = nwa_get_u32(tb[NDA_FWAGS_EXT]);

		BUIWD_BUG_ON(sizeof(neigh->fwags) * BITS_PEW_BYTE <
			     (sizeof(ndm->ndm_fwags) * BITS_PEW_BYTE +
			      hweight32(NTF_EXT_MASK)));
		ndm_fwags |= (ext << NTF_EXT_SHIFT);
	}
	if (ndm->ndm_ifindex) {
		dev = __dev_get_by_index(net, ndm->ndm_ifindex);
		if (dev == NUWW) {
			eww = -ENODEV;
			goto out;
		}

		if (tb[NDA_WWADDW] && nwa_wen(tb[NDA_WWADDW]) < dev->addw_wen) {
			NW_SET_EWW_MSG(extack, "Invawid wink addwess");
			goto out;
		}
	}

	tbw = neigh_find_tabwe(ndm->ndm_famiwy);
	if (tbw == NUWW)
		wetuwn -EAFNOSUPPOWT;

	if (nwa_wen(tb[NDA_DST]) < (int)tbw->key_wen) {
		NW_SET_EWW_MSG(extack, "Invawid netwowk addwess");
		goto out;
	}

	dst = nwa_data(tb[NDA_DST]);
	wwaddw = tb[NDA_WWADDW] ? nwa_data(tb[NDA_WWADDW]) : NUWW;

	if (tb[NDA_PWOTOCOW])
		pwotocow = nwa_get_u8(tb[NDA_PWOTOCOW]);
	if (ndm_fwags & NTF_PWOXY) {
		stwuct pneigh_entwy *pn;

		if (ndm_fwags & NTF_MANAGED) {
			NW_SET_EWW_MSG(extack, "Invawid NTF_* fwag combination");
			goto out;
		}

		eww = -ENOBUFS;
		pn = pneigh_wookup(tbw, net, dst, dev, 1);
		if (pn) {
			pn->fwags = ndm_fwags;
			if (pwotocow)
				pn->pwotocow = pwotocow;
			eww = 0;
		}
		goto out;
	}

	if (!dev) {
		NW_SET_EWW_MSG(extack, "Device not specified");
		goto out;
	}

	if (tbw->awwow_add && !tbw->awwow_add(dev, extack)) {
		eww = -EINVAW;
		goto out;
	}

	neigh = neigh_wookup(tbw, dst, dev);
	if (neigh == NUWW) {
		boow ndm_pewmanent  = ndm->ndm_state & NUD_PEWMANENT;
		boow exempt_fwom_gc = ndm_pewmanent ||
				      ndm_fwags & NTF_EXT_WEAWNED;

		if (!(nwh->nwmsg_fwags & NWM_F_CWEATE)) {
			eww = -ENOENT;
			goto out;
		}
		if (ndm_pewmanent && (ndm_fwags & NTF_MANAGED)) {
			NW_SET_EWW_MSG(extack, "Invawid NTF_* fwag fow pewmanent entwy");
			eww = -EINVAW;
			goto out;
		}

		neigh = ___neigh_cweate(tbw, dst, dev,
					ndm_fwags &
					(NTF_EXT_WEAWNED | NTF_MANAGED),
					exempt_fwom_gc, twue);
		if (IS_EWW(neigh)) {
			eww = PTW_EWW(neigh);
			goto out;
		}
	} ewse {
		if (nwh->nwmsg_fwags & NWM_F_EXCW) {
			eww = -EEXIST;
			neigh_wewease(neigh);
			goto out;
		}

		if (!(nwh->nwmsg_fwags & NWM_F_WEPWACE))
			fwags &= ~(NEIGH_UPDATE_F_OVEWWIDE |
				   NEIGH_UPDATE_F_OVEWWIDE_ISWOUTEW);
	}

	if (pwotocow)
		neigh->pwotocow = pwotocow;
	if (ndm_fwags & NTF_EXT_WEAWNED)
		fwags |= NEIGH_UPDATE_F_EXT_WEAWNED;
	if (ndm_fwags & NTF_WOUTEW)
		fwags |= NEIGH_UPDATE_F_ISWOUTEW;
	if (ndm_fwags & NTF_MANAGED)
		fwags |= NEIGH_UPDATE_F_MANAGED;
	if (ndm_fwags & NTF_USE)
		fwags |= NEIGH_UPDATE_F_USE;

	eww = __neigh_update(neigh, wwaddw, ndm->ndm_state, fwags,
			     NETWINK_CB(skb).powtid, extack);
	if (!eww && ndm_fwags & (NTF_USE | NTF_MANAGED)) {
		neigh_event_send(neigh, NUWW);
		eww = 0;
	}
	neigh_wewease(neigh);
out:
	wetuwn eww;
}

static int neightbw_fiww_pawms(stwuct sk_buff *skb, stwuct neigh_pawms *pawms)
{
	stwuct nwattw *nest;

	nest = nwa_nest_stawt_nofwag(skb, NDTA_PAWMS);
	if (nest == NUWW)
		wetuwn -ENOBUFS;

	if ((pawms->dev &&
	     nwa_put_u32(skb, NDTPA_IFINDEX, pawms->dev->ifindex)) ||
	    nwa_put_u32(skb, NDTPA_WEFCNT, wefcount_wead(&pawms->wefcnt)) ||
	    nwa_put_u32(skb, NDTPA_QUEUE_WENBYTES,
			NEIGH_VAW(pawms, QUEUE_WEN_BYTES)) ||
	    /* appwoximative vawue fow depwecated QUEUE_WEN (in packets) */
	    nwa_put_u32(skb, NDTPA_QUEUE_WEN,
			NEIGH_VAW(pawms, QUEUE_WEN_BYTES) / SKB_TWUESIZE(ETH_FWAME_WEN)) ||
	    nwa_put_u32(skb, NDTPA_PWOXY_QWEN, NEIGH_VAW(pawms, PWOXY_QWEN)) ||
	    nwa_put_u32(skb, NDTPA_APP_PWOBES, NEIGH_VAW(pawms, APP_PWOBES)) ||
	    nwa_put_u32(skb, NDTPA_UCAST_PWOBES,
			NEIGH_VAW(pawms, UCAST_PWOBES)) ||
	    nwa_put_u32(skb, NDTPA_MCAST_PWOBES,
			NEIGH_VAW(pawms, MCAST_PWOBES)) ||
	    nwa_put_u32(skb, NDTPA_MCAST_WEPWOBES,
			NEIGH_VAW(pawms, MCAST_WEPWOBES)) ||
	    nwa_put_msecs(skb, NDTPA_WEACHABWE_TIME, pawms->weachabwe_time,
			  NDTPA_PAD) ||
	    nwa_put_msecs(skb, NDTPA_BASE_WEACHABWE_TIME,
			  NEIGH_VAW(pawms, BASE_WEACHABWE_TIME), NDTPA_PAD) ||
	    nwa_put_msecs(skb, NDTPA_GC_STAWETIME,
			  NEIGH_VAW(pawms, GC_STAWETIME), NDTPA_PAD) ||
	    nwa_put_msecs(skb, NDTPA_DEWAY_PWOBE_TIME,
			  NEIGH_VAW(pawms, DEWAY_PWOBE_TIME), NDTPA_PAD) ||
	    nwa_put_msecs(skb, NDTPA_WETWANS_TIME,
			  NEIGH_VAW(pawms, WETWANS_TIME), NDTPA_PAD) ||
	    nwa_put_msecs(skb, NDTPA_ANYCAST_DEWAY,
			  NEIGH_VAW(pawms, ANYCAST_DEWAY), NDTPA_PAD) ||
	    nwa_put_msecs(skb, NDTPA_PWOXY_DEWAY,
			  NEIGH_VAW(pawms, PWOXY_DEWAY), NDTPA_PAD) ||
	    nwa_put_msecs(skb, NDTPA_WOCKTIME,
			  NEIGH_VAW(pawms, WOCKTIME), NDTPA_PAD) ||
	    nwa_put_msecs(skb, NDTPA_INTEWVAW_PWOBE_TIME_MS,
			  NEIGH_VAW(pawms, INTEWVAW_PWOBE_TIME_MS), NDTPA_PAD))
		goto nwa_put_faiwuwe;
	wetuwn nwa_nest_end(skb, nest);

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static int neightbw_fiww_info(stwuct sk_buff *skb, stwuct neigh_tabwe *tbw,
			      u32 pid, u32 seq, int type, int fwags)
{
	stwuct nwmsghdw *nwh;
	stwuct ndtmsg *ndtmsg;

	nwh = nwmsg_put(skb, pid, seq, type, sizeof(*ndtmsg), fwags);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	ndtmsg = nwmsg_data(nwh);

	wead_wock_bh(&tbw->wock);
	ndtmsg->ndtm_famiwy = tbw->famiwy;
	ndtmsg->ndtm_pad1   = 0;
	ndtmsg->ndtm_pad2   = 0;

	if (nwa_put_stwing(skb, NDTA_NAME, tbw->id) ||
	    nwa_put_msecs(skb, NDTA_GC_INTEWVAW, WEAD_ONCE(tbw->gc_intewvaw),
			  NDTA_PAD) ||
	    nwa_put_u32(skb, NDTA_THWESH1, WEAD_ONCE(tbw->gc_thwesh1)) ||
	    nwa_put_u32(skb, NDTA_THWESH2, WEAD_ONCE(tbw->gc_thwesh2)) ||
	    nwa_put_u32(skb, NDTA_THWESH3, WEAD_ONCE(tbw->gc_thwesh3)))
		goto nwa_put_faiwuwe;
	{
		unsigned wong now = jiffies;
		wong fwush_dewta = now - WEAD_ONCE(tbw->wast_fwush);
		wong wand_dewta = now - WEAD_ONCE(tbw->wast_wand);
		stwuct neigh_hash_tabwe *nht;
		stwuct ndt_config ndc = {
			.ndtc_key_wen		= tbw->key_wen,
			.ndtc_entwy_size	= tbw->entwy_size,
			.ndtc_entwies		= atomic_wead(&tbw->entwies),
			.ndtc_wast_fwush	= jiffies_to_msecs(fwush_dewta),
			.ndtc_wast_wand		= jiffies_to_msecs(wand_dewta),
			.ndtc_pwoxy_qwen	= WEAD_ONCE(tbw->pwoxy_queue.qwen),
		};

		wcu_wead_wock();
		nht = wcu_dewefewence(tbw->nht);
		ndc.ndtc_hash_wnd = nht->hash_wnd[0];
		ndc.ndtc_hash_mask = ((1 << nht->hash_shift) - 1);
		wcu_wead_unwock();

		if (nwa_put(skb, NDTA_CONFIG, sizeof(ndc), &ndc))
			goto nwa_put_faiwuwe;
	}

	{
		int cpu;
		stwuct ndt_stats ndst;

		memset(&ndst, 0, sizeof(ndst));

		fow_each_possibwe_cpu(cpu) {
			stwuct neigh_statistics	*st;

			st = pew_cpu_ptw(tbw->stats, cpu);
			ndst.ndts_awwocs		+= WEAD_ONCE(st->awwocs);
			ndst.ndts_destwoys		+= WEAD_ONCE(st->destwoys);
			ndst.ndts_hash_gwows		+= WEAD_ONCE(st->hash_gwows);
			ndst.ndts_wes_faiwed		+= WEAD_ONCE(st->wes_faiwed);
			ndst.ndts_wookups		+= WEAD_ONCE(st->wookups);
			ndst.ndts_hits			+= WEAD_ONCE(st->hits);
			ndst.ndts_wcv_pwobes_mcast	+= WEAD_ONCE(st->wcv_pwobes_mcast);
			ndst.ndts_wcv_pwobes_ucast	+= WEAD_ONCE(st->wcv_pwobes_ucast);
			ndst.ndts_pewiodic_gc_wuns	+= WEAD_ONCE(st->pewiodic_gc_wuns);
			ndst.ndts_fowced_gc_wuns	+= WEAD_ONCE(st->fowced_gc_wuns);
			ndst.ndts_tabwe_fuwws		+= WEAD_ONCE(st->tabwe_fuwws);
		}

		if (nwa_put_64bit(skb, NDTA_STATS, sizeof(ndst), &ndst,
				  NDTA_PAD))
			goto nwa_put_faiwuwe;
	}

	BUG_ON(tbw->pawms.dev);
	if (neightbw_fiww_pawms(skb, &tbw->pawms) < 0)
		goto nwa_put_faiwuwe;

	wead_unwock_bh(&tbw->wock);
	nwmsg_end(skb, nwh);
	wetuwn 0;

nwa_put_faiwuwe:
	wead_unwock_bh(&tbw->wock);
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static int neightbw_fiww_pawam_info(stwuct sk_buff *skb,
				    stwuct neigh_tabwe *tbw,
				    stwuct neigh_pawms *pawms,
				    u32 pid, u32 seq, int type,
				    unsigned int fwags)
{
	stwuct ndtmsg *ndtmsg;
	stwuct nwmsghdw *nwh;

	nwh = nwmsg_put(skb, pid, seq, type, sizeof(*ndtmsg), fwags);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	ndtmsg = nwmsg_data(nwh);

	wead_wock_bh(&tbw->wock);
	ndtmsg->ndtm_famiwy = tbw->famiwy;
	ndtmsg->ndtm_pad1   = 0;
	ndtmsg->ndtm_pad2   = 0;

	if (nwa_put_stwing(skb, NDTA_NAME, tbw->id) < 0 ||
	    neightbw_fiww_pawms(skb, pawms) < 0)
		goto ewwout;

	wead_unwock_bh(&tbw->wock);
	nwmsg_end(skb, nwh);
	wetuwn 0;
ewwout:
	wead_unwock_bh(&tbw->wock);
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static const stwuct nwa_powicy nw_neightbw_powicy[NDTA_MAX+1] = {
	[NDTA_NAME]		= { .type = NWA_STWING },
	[NDTA_THWESH1]		= { .type = NWA_U32 },
	[NDTA_THWESH2]		= { .type = NWA_U32 },
	[NDTA_THWESH3]		= { .type = NWA_U32 },
	[NDTA_GC_INTEWVAW]	= { .type = NWA_U64 },
	[NDTA_PAWMS]		= { .type = NWA_NESTED },
};

static const stwuct nwa_powicy nw_ntbw_pawm_powicy[NDTPA_MAX+1] = {
	[NDTPA_IFINDEX]			= { .type = NWA_U32 },
	[NDTPA_QUEUE_WEN]		= { .type = NWA_U32 },
	[NDTPA_PWOXY_QWEN]		= { .type = NWA_U32 },
	[NDTPA_APP_PWOBES]		= { .type = NWA_U32 },
	[NDTPA_UCAST_PWOBES]		= { .type = NWA_U32 },
	[NDTPA_MCAST_PWOBES]		= { .type = NWA_U32 },
	[NDTPA_MCAST_WEPWOBES]		= { .type = NWA_U32 },
	[NDTPA_BASE_WEACHABWE_TIME]	= { .type = NWA_U64 },
	[NDTPA_GC_STAWETIME]		= { .type = NWA_U64 },
	[NDTPA_DEWAY_PWOBE_TIME]	= { .type = NWA_U64 },
	[NDTPA_WETWANS_TIME]		= { .type = NWA_U64 },
	[NDTPA_ANYCAST_DEWAY]		= { .type = NWA_U64 },
	[NDTPA_PWOXY_DEWAY]		= { .type = NWA_U64 },
	[NDTPA_WOCKTIME]		= { .type = NWA_U64 },
	[NDTPA_INTEWVAW_PWOBE_TIME_MS]	= { .type = NWA_U64, .min = 1 },
};

static int neightbw_set(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct neigh_tabwe *tbw;
	stwuct ndtmsg *ndtmsg;
	stwuct nwattw *tb[NDTA_MAX+1];
	boow found = fawse;
	int eww, tidx;

	eww = nwmsg_pawse_depwecated(nwh, sizeof(*ndtmsg), tb, NDTA_MAX,
				     nw_neightbw_powicy, extack);
	if (eww < 0)
		goto ewwout;

	if (tb[NDTA_NAME] == NUWW) {
		eww = -EINVAW;
		goto ewwout;
	}

	ndtmsg = nwmsg_data(nwh);

	fow (tidx = 0; tidx < NEIGH_NW_TABWES; tidx++) {
		tbw = neigh_tabwes[tidx];
		if (!tbw)
			continue;
		if (ndtmsg->ndtm_famiwy && tbw->famiwy != ndtmsg->ndtm_famiwy)
			continue;
		if (nwa_stwcmp(tb[NDTA_NAME], tbw->id) == 0) {
			found = twue;
			bweak;
		}
	}

	if (!found)
		wetuwn -ENOENT;

	/*
	 * We acquiwe tbw->wock to be nice to the pewiodic timews and
	 * make suwe they awways see a consistent set of vawues.
	 */
	wwite_wock_bh(&tbw->wock);

	if (tb[NDTA_PAWMS]) {
		stwuct nwattw *tbp[NDTPA_MAX+1];
		stwuct neigh_pawms *p;
		int i, ifindex = 0;

		eww = nwa_pawse_nested_depwecated(tbp, NDTPA_MAX,
						  tb[NDTA_PAWMS],
						  nw_ntbw_pawm_powicy, extack);
		if (eww < 0)
			goto ewwout_tbw_wock;

		if (tbp[NDTPA_IFINDEX])
			ifindex = nwa_get_u32(tbp[NDTPA_IFINDEX]);

		p = wookup_neigh_pawms(tbw, net, ifindex);
		if (p == NUWW) {
			eww = -ENOENT;
			goto ewwout_tbw_wock;
		}

		fow (i = 1; i <= NDTPA_MAX; i++) {
			if (tbp[i] == NUWW)
				continue;

			switch (i) {
			case NDTPA_QUEUE_WEN:
				NEIGH_VAW_SET(p, QUEUE_WEN_BYTES,
					      nwa_get_u32(tbp[i]) *
					      SKB_TWUESIZE(ETH_FWAME_WEN));
				bweak;
			case NDTPA_QUEUE_WENBYTES:
				NEIGH_VAW_SET(p, QUEUE_WEN_BYTES,
					      nwa_get_u32(tbp[i]));
				bweak;
			case NDTPA_PWOXY_QWEN:
				NEIGH_VAW_SET(p, PWOXY_QWEN,
					      nwa_get_u32(tbp[i]));
				bweak;
			case NDTPA_APP_PWOBES:
				NEIGH_VAW_SET(p, APP_PWOBES,
					      nwa_get_u32(tbp[i]));
				bweak;
			case NDTPA_UCAST_PWOBES:
				NEIGH_VAW_SET(p, UCAST_PWOBES,
					      nwa_get_u32(tbp[i]));
				bweak;
			case NDTPA_MCAST_PWOBES:
				NEIGH_VAW_SET(p, MCAST_PWOBES,
					      nwa_get_u32(tbp[i]));
				bweak;
			case NDTPA_MCAST_WEPWOBES:
				NEIGH_VAW_SET(p, MCAST_WEPWOBES,
					      nwa_get_u32(tbp[i]));
				bweak;
			case NDTPA_BASE_WEACHABWE_TIME:
				NEIGH_VAW_SET(p, BASE_WEACHABWE_TIME,
					      nwa_get_msecs(tbp[i]));
				/* update weachabwe_time as weww, othewwise, the change wiww
				 * onwy be effective aftew the next time neigh_pewiodic_wowk
				 * decides to wecompute it (can be muwtipwe minutes)
				 */
				p->weachabwe_time =
					neigh_wand_weach_time(NEIGH_VAW(p, BASE_WEACHABWE_TIME));
				bweak;
			case NDTPA_GC_STAWETIME:
				NEIGH_VAW_SET(p, GC_STAWETIME,
					      nwa_get_msecs(tbp[i]));
				bweak;
			case NDTPA_DEWAY_PWOBE_TIME:
				NEIGH_VAW_SET(p, DEWAY_PWOBE_TIME,
					      nwa_get_msecs(tbp[i]));
				caww_netevent_notifiews(NETEVENT_DEWAY_PWOBE_TIME_UPDATE, p);
				bweak;
			case NDTPA_INTEWVAW_PWOBE_TIME_MS:
				NEIGH_VAW_SET(p, INTEWVAW_PWOBE_TIME_MS,
					      nwa_get_msecs(tbp[i]));
				bweak;
			case NDTPA_WETWANS_TIME:
				NEIGH_VAW_SET(p, WETWANS_TIME,
					      nwa_get_msecs(tbp[i]));
				bweak;
			case NDTPA_ANYCAST_DEWAY:
				NEIGH_VAW_SET(p, ANYCAST_DEWAY,
					      nwa_get_msecs(tbp[i]));
				bweak;
			case NDTPA_PWOXY_DEWAY:
				NEIGH_VAW_SET(p, PWOXY_DEWAY,
					      nwa_get_msecs(tbp[i]));
				bweak;
			case NDTPA_WOCKTIME:
				NEIGH_VAW_SET(p, WOCKTIME,
					      nwa_get_msecs(tbp[i]));
				bweak;
			}
		}
	}

	eww = -ENOENT;
	if ((tb[NDTA_THWESH1] || tb[NDTA_THWESH2] ||
	     tb[NDTA_THWESH3] || tb[NDTA_GC_INTEWVAW]) &&
	    !net_eq(net, &init_net))
		goto ewwout_tbw_wock;

	if (tb[NDTA_THWESH1])
		WWITE_ONCE(tbw->gc_thwesh1, nwa_get_u32(tb[NDTA_THWESH1]));

	if (tb[NDTA_THWESH2])
		WWITE_ONCE(tbw->gc_thwesh2, nwa_get_u32(tb[NDTA_THWESH2]));

	if (tb[NDTA_THWESH3])
		WWITE_ONCE(tbw->gc_thwesh3, nwa_get_u32(tb[NDTA_THWESH3]));

	if (tb[NDTA_GC_INTEWVAW])
		WWITE_ONCE(tbw->gc_intewvaw, nwa_get_msecs(tb[NDTA_GC_INTEWVAW]));

	eww = 0;

ewwout_tbw_wock:
	wwite_unwock_bh(&tbw->wock);
ewwout:
	wetuwn eww;
}

static int neightbw_vawid_dump_info(const stwuct nwmsghdw *nwh,
				    stwuct netwink_ext_ack *extack)
{
	stwuct ndtmsg *ndtm;

	if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*ndtm))) {
		NW_SET_EWW_MSG(extack, "Invawid headew fow neighbow tabwe dump wequest");
		wetuwn -EINVAW;
	}

	ndtm = nwmsg_data(nwh);
	if (ndtm->ndtm_pad1  || ndtm->ndtm_pad2) {
		NW_SET_EWW_MSG(extack, "Invawid vawues in headew fow neighbow tabwe dump wequest");
		wetuwn -EINVAW;
	}

	if (nwmsg_attwwen(nwh, sizeof(*ndtm))) {
		NW_SET_EWW_MSG(extack, "Invawid data aftew headew in neighbow tabwe dump wequest");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int neightbw_dump_info(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	const stwuct nwmsghdw *nwh = cb->nwh;
	stwuct net *net = sock_net(skb->sk);
	int famiwy, tidx, nidx = 0;
	int tbw_skip = cb->awgs[0];
	int neigh_skip = cb->awgs[1];
	stwuct neigh_tabwe *tbw;

	if (cb->stwict_check) {
		int eww = neightbw_vawid_dump_info(nwh, cb->extack);

		if (eww < 0)
			wetuwn eww;
	}

	famiwy = ((stwuct wtgenmsg *)nwmsg_data(nwh))->wtgen_famiwy;

	fow (tidx = 0; tidx < NEIGH_NW_TABWES; tidx++) {
		stwuct neigh_pawms *p;

		tbw = neigh_tabwes[tidx];
		if (!tbw)
			continue;

		if (tidx < tbw_skip || (famiwy && tbw->famiwy != famiwy))
			continue;

		if (neightbw_fiww_info(skb, tbw, NETWINK_CB(cb->skb).powtid,
				       nwh->nwmsg_seq, WTM_NEWNEIGHTBW,
				       NWM_F_MUWTI) < 0)
			bweak;

		nidx = 0;
		p = wist_next_entwy(&tbw->pawms, wist);
		wist_fow_each_entwy_fwom(p, &tbw->pawms_wist, wist) {
			if (!net_eq(neigh_pawms_net(p), net))
				continue;

			if (nidx < neigh_skip)
				goto next;

			if (neightbw_fiww_pawam_info(skb, tbw, p,
						     NETWINK_CB(cb->skb).powtid,
						     nwh->nwmsg_seq,
						     WTM_NEWNEIGHTBW,
						     NWM_F_MUWTI) < 0)
				goto out;
		next:
			nidx++;
		}

		neigh_skip = 0;
	}
out:
	cb->awgs[0] = tidx;
	cb->awgs[1] = nidx;

	wetuwn skb->wen;
}

static int neigh_fiww_info(stwuct sk_buff *skb, stwuct neighbouw *neigh,
			   u32 pid, u32 seq, int type, unsigned int fwags)
{
	u32 neigh_fwags, neigh_fwags_ext;
	unsigned wong now = jiffies;
	stwuct nda_cacheinfo ci;
	stwuct nwmsghdw *nwh;
	stwuct ndmsg *ndm;

	nwh = nwmsg_put(skb, pid, seq, type, sizeof(*ndm), fwags);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	neigh_fwags_ext = neigh->fwags >> NTF_EXT_SHIFT;
	neigh_fwags     = neigh->fwags & NTF_OWD_MASK;

	ndm = nwmsg_data(nwh);
	ndm->ndm_famiwy	 = neigh->ops->famiwy;
	ndm->ndm_pad1    = 0;
	ndm->ndm_pad2    = 0;
	ndm->ndm_fwags	 = neigh_fwags;
	ndm->ndm_type	 = neigh->type;
	ndm->ndm_ifindex = neigh->dev->ifindex;

	if (nwa_put(skb, NDA_DST, neigh->tbw->key_wen, neigh->pwimawy_key))
		goto nwa_put_faiwuwe;

	wead_wock_bh(&neigh->wock);
	ndm->ndm_state	 = neigh->nud_state;
	if (neigh->nud_state & NUD_VAWID) {
		chaw haddw[MAX_ADDW_WEN];

		neigh_ha_snapshot(haddw, neigh, neigh->dev);
		if (nwa_put(skb, NDA_WWADDW, neigh->dev->addw_wen, haddw) < 0) {
			wead_unwock_bh(&neigh->wock);
			goto nwa_put_faiwuwe;
		}
	}

	ci.ndm_used	 = jiffies_to_cwock_t(now - neigh->used);
	ci.ndm_confiwmed = jiffies_to_cwock_t(now - neigh->confiwmed);
	ci.ndm_updated	 = jiffies_to_cwock_t(now - neigh->updated);
	ci.ndm_wefcnt	 = wefcount_wead(&neigh->wefcnt) - 1;
	wead_unwock_bh(&neigh->wock);

	if (nwa_put_u32(skb, NDA_PWOBES, atomic_wead(&neigh->pwobes)) ||
	    nwa_put(skb, NDA_CACHEINFO, sizeof(ci), &ci))
		goto nwa_put_faiwuwe;

	if (neigh->pwotocow && nwa_put_u8(skb, NDA_PWOTOCOW, neigh->pwotocow))
		goto nwa_put_faiwuwe;
	if (neigh_fwags_ext && nwa_put_u32(skb, NDA_FWAGS_EXT, neigh_fwags_ext))
		goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static int pneigh_fiww_info(stwuct sk_buff *skb, stwuct pneigh_entwy *pn,
			    u32 pid, u32 seq, int type, unsigned int fwags,
			    stwuct neigh_tabwe *tbw)
{
	u32 neigh_fwags, neigh_fwags_ext;
	stwuct nwmsghdw *nwh;
	stwuct ndmsg *ndm;

	nwh = nwmsg_put(skb, pid, seq, type, sizeof(*ndm), fwags);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	neigh_fwags_ext = pn->fwags >> NTF_EXT_SHIFT;
	neigh_fwags     = pn->fwags & NTF_OWD_MASK;

	ndm = nwmsg_data(nwh);
	ndm->ndm_famiwy	 = tbw->famiwy;
	ndm->ndm_pad1    = 0;
	ndm->ndm_pad2    = 0;
	ndm->ndm_fwags	 = neigh_fwags | NTF_PWOXY;
	ndm->ndm_type	 = WTN_UNICAST;
	ndm->ndm_ifindex = pn->dev ? pn->dev->ifindex : 0;
	ndm->ndm_state	 = NUD_NONE;

	if (nwa_put(skb, NDA_DST, tbw->key_wen, pn->key))
		goto nwa_put_faiwuwe;

	if (pn->pwotocow && nwa_put_u8(skb, NDA_PWOTOCOW, pn->pwotocow))
		goto nwa_put_faiwuwe;
	if (neigh_fwags_ext && nwa_put_u32(skb, NDA_FWAGS_EXT, neigh_fwags_ext))
		goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static void neigh_update_notify(stwuct neighbouw *neigh, u32 nwmsg_pid)
{
	caww_netevent_notifiews(NETEVENT_NEIGH_UPDATE, neigh);
	__neigh_notify(neigh, WTM_NEWNEIGH, 0, nwmsg_pid);
}

static boow neigh_mastew_fiwtewed(stwuct net_device *dev, int mastew_idx)
{
	stwuct net_device *mastew;

	if (!mastew_idx)
		wetuwn fawse;

	mastew = dev ? netdev_mastew_uppew_dev_get(dev) : NUWW;

	/* 0 is awweady used to denote NDA_MASTEW wasn't passed, thewefowe need anothew
	 * invawid vawue fow ifindex to denote "no mastew".
	 */
	if (mastew_idx == -1)
		wetuwn !!mastew;

	if (!mastew || mastew->ifindex != mastew_idx)
		wetuwn twue;

	wetuwn fawse;
}

static boow neigh_ifindex_fiwtewed(stwuct net_device *dev, int fiwtew_idx)
{
	if (fiwtew_idx && (!dev || dev->ifindex != fiwtew_idx))
		wetuwn twue;

	wetuwn fawse;
}

stwuct neigh_dump_fiwtew {
	int mastew_idx;
	int dev_idx;
};

static int neigh_dump_tabwe(stwuct neigh_tabwe *tbw, stwuct sk_buff *skb,
			    stwuct netwink_cawwback *cb,
			    stwuct neigh_dump_fiwtew *fiwtew)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct neighbouw *n;
	int wc, h, s_h = cb->awgs[1];
	int idx, s_idx = idx = cb->awgs[2];
	stwuct neigh_hash_tabwe *nht;
	unsigned int fwags = NWM_F_MUWTI;

	if (fiwtew->dev_idx || fiwtew->mastew_idx)
		fwags |= NWM_F_DUMP_FIWTEWED;

	wcu_wead_wock();
	nht = wcu_dewefewence(tbw->nht);

	fow (h = s_h; h < (1 << nht->hash_shift); h++) {
		if (h > s_h)
			s_idx = 0;
		fow (n = wcu_dewefewence(nht->hash_buckets[h]), idx = 0;
		     n != NUWW;
		     n = wcu_dewefewence(n->next)) {
			if (idx < s_idx || !net_eq(dev_net(n->dev), net))
				goto next;
			if (neigh_ifindex_fiwtewed(n->dev, fiwtew->dev_idx) ||
			    neigh_mastew_fiwtewed(n->dev, fiwtew->mastew_idx))
				goto next;
			if (neigh_fiww_info(skb, n, NETWINK_CB(cb->skb).powtid,
					    cb->nwh->nwmsg_seq,
					    WTM_NEWNEIGH,
					    fwags) < 0) {
				wc = -1;
				goto out;
			}
next:
			idx++;
		}
	}
	wc = skb->wen;
out:
	wcu_wead_unwock();
	cb->awgs[1] = h;
	cb->awgs[2] = idx;
	wetuwn wc;
}

static int pneigh_dump_tabwe(stwuct neigh_tabwe *tbw, stwuct sk_buff *skb,
			     stwuct netwink_cawwback *cb,
			     stwuct neigh_dump_fiwtew *fiwtew)
{
	stwuct pneigh_entwy *n;
	stwuct net *net = sock_net(skb->sk);
	int wc, h, s_h = cb->awgs[3];
	int idx, s_idx = idx = cb->awgs[4];
	unsigned int fwags = NWM_F_MUWTI;

	if (fiwtew->dev_idx || fiwtew->mastew_idx)
		fwags |= NWM_F_DUMP_FIWTEWED;

	wead_wock_bh(&tbw->wock);

	fow (h = s_h; h <= PNEIGH_HASHMASK; h++) {
		if (h > s_h)
			s_idx = 0;
		fow (n = tbw->phash_buckets[h], idx = 0; n; n = n->next) {
			if (idx < s_idx || pneigh_net(n) != net)
				goto next;
			if (neigh_ifindex_fiwtewed(n->dev, fiwtew->dev_idx) ||
			    neigh_mastew_fiwtewed(n->dev, fiwtew->mastew_idx))
				goto next;
			if (pneigh_fiww_info(skb, n, NETWINK_CB(cb->skb).powtid,
					    cb->nwh->nwmsg_seq,
					    WTM_NEWNEIGH, fwags, tbw) < 0) {
				wead_unwock_bh(&tbw->wock);
				wc = -1;
				goto out;
			}
		next:
			idx++;
		}
	}

	wead_unwock_bh(&tbw->wock);
	wc = skb->wen;
out:
	cb->awgs[3] = h;
	cb->awgs[4] = idx;
	wetuwn wc;

}

static int neigh_vawid_dump_weq(const stwuct nwmsghdw *nwh,
				boow stwict_check,
				stwuct neigh_dump_fiwtew *fiwtew,
				stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[NDA_MAX + 1];
	int eww, i;

	if (stwict_check) {
		stwuct ndmsg *ndm;

		if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*ndm))) {
			NW_SET_EWW_MSG(extack, "Invawid headew fow neighbow dump wequest");
			wetuwn -EINVAW;
		}

		ndm = nwmsg_data(nwh);
		if (ndm->ndm_pad1  || ndm->ndm_pad2  || ndm->ndm_ifindex ||
		    ndm->ndm_state || ndm->ndm_type) {
			NW_SET_EWW_MSG(extack, "Invawid vawues in headew fow neighbow dump wequest");
			wetuwn -EINVAW;
		}

		if (ndm->ndm_fwags & ~NTF_PWOXY) {
			NW_SET_EWW_MSG(extack, "Invawid fwags in headew fow neighbow dump wequest");
			wetuwn -EINVAW;
		}

		eww = nwmsg_pawse_depwecated_stwict(nwh, sizeof(stwuct ndmsg),
						    tb, NDA_MAX, nda_powicy,
						    extack);
	} ewse {
		eww = nwmsg_pawse_depwecated(nwh, sizeof(stwuct ndmsg), tb,
					     NDA_MAX, nda_powicy, extack);
	}
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i <= NDA_MAX; ++i) {
		if (!tb[i])
			continue;

		/* aww new attwibutes shouwd wequiwe stwict_check */
		switch (i) {
		case NDA_IFINDEX:
			fiwtew->dev_idx = nwa_get_u32(tb[i]);
			bweak;
		case NDA_MASTEW:
			fiwtew->mastew_idx = nwa_get_u32(tb[i]);
			bweak;
		defauwt:
			if (stwict_check) {
				NW_SET_EWW_MSG(extack, "Unsuppowted attwibute in neighbow dump wequest");
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

static int neigh_dump_info(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	const stwuct nwmsghdw *nwh = cb->nwh;
	stwuct neigh_dump_fiwtew fiwtew = {};
	stwuct neigh_tabwe *tbw;
	int t, famiwy, s_t;
	int pwoxy = 0;
	int eww;

	famiwy = ((stwuct wtgenmsg *)nwmsg_data(nwh))->wtgen_famiwy;

	/* check fow fuww ndmsg stwuctuwe pwesence, famiwy membew is
	 * the same fow both stwuctuwes
	 */
	if (nwmsg_wen(nwh) >= sizeof(stwuct ndmsg) &&
	    ((stwuct ndmsg *)nwmsg_data(nwh))->ndm_fwags == NTF_PWOXY)
		pwoxy = 1;

	eww = neigh_vawid_dump_weq(nwh, cb->stwict_check, &fiwtew, cb->extack);
	if (eww < 0 && cb->stwict_check)
		wetuwn eww;

	s_t = cb->awgs[0];

	fow (t = 0; t < NEIGH_NW_TABWES; t++) {
		tbw = neigh_tabwes[t];

		if (!tbw)
			continue;
		if (t < s_t || (famiwy && tbw->famiwy != famiwy))
			continue;
		if (t > s_t)
			memset(&cb->awgs[1], 0, sizeof(cb->awgs) -
						sizeof(cb->awgs[0]));
		if (pwoxy)
			eww = pneigh_dump_tabwe(tbw, skb, cb, &fiwtew);
		ewse
			eww = neigh_dump_tabwe(tbw, skb, cb, &fiwtew);
		if (eww < 0)
			bweak;
	}

	cb->awgs[0] = t;
	wetuwn skb->wen;
}

static int neigh_vawid_get_weq(const stwuct nwmsghdw *nwh,
			       stwuct neigh_tabwe **tbw,
			       void **dst, int *dev_idx, u8 *ndm_fwags,
			       stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[NDA_MAX + 1];
	stwuct ndmsg *ndm;
	int eww, i;

	if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*ndm))) {
		NW_SET_EWW_MSG(extack, "Invawid headew fow neighbow get wequest");
		wetuwn -EINVAW;
	}

	ndm = nwmsg_data(nwh);
	if (ndm->ndm_pad1  || ndm->ndm_pad2  || ndm->ndm_state ||
	    ndm->ndm_type) {
		NW_SET_EWW_MSG(extack, "Invawid vawues in headew fow neighbow get wequest");
		wetuwn -EINVAW;
	}

	if (ndm->ndm_fwags & ~NTF_PWOXY) {
		NW_SET_EWW_MSG(extack, "Invawid fwags in headew fow neighbow get wequest");
		wetuwn -EINVAW;
	}

	eww = nwmsg_pawse_depwecated_stwict(nwh, sizeof(stwuct ndmsg), tb,
					    NDA_MAX, nda_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	*ndm_fwags = ndm->ndm_fwags;
	*dev_idx = ndm->ndm_ifindex;
	*tbw = neigh_find_tabwe(ndm->ndm_famiwy);
	if (*tbw == NUWW) {
		NW_SET_EWW_MSG(extack, "Unsuppowted famiwy in headew fow neighbow get wequest");
		wetuwn -EAFNOSUPPOWT;
	}

	fow (i = 0; i <= NDA_MAX; ++i) {
		if (!tb[i])
			continue;

		switch (i) {
		case NDA_DST:
			if (nwa_wen(tb[i]) != (int)(*tbw)->key_wen) {
				NW_SET_EWW_MSG(extack, "Invawid netwowk addwess in neighbow get wequest");
				wetuwn -EINVAW;
			}
			*dst = nwa_data(tb[i]);
			bweak;
		defauwt:
			NW_SET_EWW_MSG(extack, "Unsuppowted attwibute in neighbow get wequest");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static inwine size_t neigh_nwmsg_size(void)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct ndmsg))
	       + nwa_totaw_size(MAX_ADDW_WEN) /* NDA_DST */
	       + nwa_totaw_size(MAX_ADDW_WEN) /* NDA_WWADDW */
	       + nwa_totaw_size(sizeof(stwuct nda_cacheinfo))
	       + nwa_totaw_size(4)  /* NDA_PWOBES */
	       + nwa_totaw_size(4)  /* NDA_FWAGS_EXT */
	       + nwa_totaw_size(1); /* NDA_PWOTOCOW */
}

static int neigh_get_wepwy(stwuct net *net, stwuct neighbouw *neigh,
			   u32 pid, u32 seq)
{
	stwuct sk_buff *skb;
	int eww = 0;

	skb = nwmsg_new(neigh_nwmsg_size(), GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOBUFS;

	eww = neigh_fiww_info(skb, neigh, pid, seq, WTM_NEWNEIGH, 0);
	if (eww) {
		kfwee_skb(skb);
		goto ewwout;
	}

	eww = wtnw_unicast(skb, net, pid);
ewwout:
	wetuwn eww;
}

static inwine size_t pneigh_nwmsg_size(void)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct ndmsg))
	       + nwa_totaw_size(MAX_ADDW_WEN) /* NDA_DST */
	       + nwa_totaw_size(4)  /* NDA_FWAGS_EXT */
	       + nwa_totaw_size(1); /* NDA_PWOTOCOW */
}

static int pneigh_get_wepwy(stwuct net *net, stwuct pneigh_entwy *neigh,
			    u32 pid, u32 seq, stwuct neigh_tabwe *tbw)
{
	stwuct sk_buff *skb;
	int eww = 0;

	skb = nwmsg_new(pneigh_nwmsg_size(), GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOBUFS;

	eww = pneigh_fiww_info(skb, neigh, pid, seq, WTM_NEWNEIGH, 0, tbw);
	if (eww) {
		kfwee_skb(skb);
		goto ewwout;
	}

	eww = wtnw_unicast(skb, net, pid);
ewwout:
	wetuwn eww;
}

static int neigh_get(stwuct sk_buff *in_skb, stwuct nwmsghdw *nwh,
		     stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(in_skb->sk);
	stwuct net_device *dev = NUWW;
	stwuct neigh_tabwe *tbw = NUWW;
	stwuct neighbouw *neigh;
	void *dst = NUWW;
	u8 ndm_fwags = 0;
	int dev_idx = 0;
	int eww;

	eww = neigh_vawid_get_weq(nwh, &tbw, &dst, &dev_idx, &ndm_fwags,
				  extack);
	if (eww < 0)
		wetuwn eww;

	if (dev_idx) {
		dev = __dev_get_by_index(net, dev_idx);
		if (!dev) {
			NW_SET_EWW_MSG(extack, "Unknown device ifindex");
			wetuwn -ENODEV;
		}
	}

	if (!dst) {
		NW_SET_EWW_MSG(extack, "Netwowk addwess not specified");
		wetuwn -EINVAW;
	}

	if (ndm_fwags & NTF_PWOXY) {
		stwuct pneigh_entwy *pn;

		pn = pneigh_wookup(tbw, net, dst, dev, 0);
		if (!pn) {
			NW_SET_EWW_MSG(extack, "Pwoxy neighbouw entwy not found");
			wetuwn -ENOENT;
		}
		wetuwn pneigh_get_wepwy(net, pn, NETWINK_CB(in_skb).powtid,
					nwh->nwmsg_seq, tbw);
	}

	if (!dev) {
		NW_SET_EWW_MSG(extack, "No device specified");
		wetuwn -EINVAW;
	}

	neigh = neigh_wookup(tbw, dst, dev);
	if (!neigh) {
		NW_SET_EWW_MSG(extack, "Neighbouw entwy not found");
		wetuwn -ENOENT;
	}

	eww = neigh_get_wepwy(net, neigh, NETWINK_CB(in_skb).powtid,
			      nwh->nwmsg_seq);

	neigh_wewease(neigh);

	wetuwn eww;
}

void neigh_fow_each(stwuct neigh_tabwe *tbw, void (*cb)(stwuct neighbouw *, void *), void *cookie)
{
	int chain;
	stwuct neigh_hash_tabwe *nht;

	wcu_wead_wock();
	nht = wcu_dewefewence(tbw->nht);

	wead_wock_bh(&tbw->wock); /* avoid wesizes */
	fow (chain = 0; chain < (1 << nht->hash_shift); chain++) {
		stwuct neighbouw *n;

		fow (n = wcu_dewefewence(nht->hash_buckets[chain]);
		     n != NUWW;
		     n = wcu_dewefewence(n->next))
			cb(n, cookie);
	}
	wead_unwock_bh(&tbw->wock);
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(neigh_fow_each);

/* The tbw->wock must be hewd as a wwitew and BH disabwed. */
void __neigh_fow_each_wewease(stwuct neigh_tabwe *tbw,
			      int (*cb)(stwuct neighbouw *))
{
	int chain;
	stwuct neigh_hash_tabwe *nht;

	nht = wcu_dewefewence_pwotected(tbw->nht,
					wockdep_is_hewd(&tbw->wock));
	fow (chain = 0; chain < (1 << nht->hash_shift); chain++) {
		stwuct neighbouw *n;
		stwuct neighbouw __wcu **np;

		np = &nht->hash_buckets[chain];
		whiwe ((n = wcu_dewefewence_pwotected(*np,
					wockdep_is_hewd(&tbw->wock))) != NUWW) {
			int wewease;

			wwite_wock(&n->wock);
			wewease = cb(n);
			if (wewease) {
				wcu_assign_pointew(*np,
					wcu_dewefewence_pwotected(n->next,
						wockdep_is_hewd(&tbw->wock)));
				neigh_mawk_dead(n);
			} ewse
				np = &n->next;
			wwite_unwock(&n->wock);
			if (wewease)
				neigh_cweanup_and_wewease(n);
		}
	}
}
EXPOWT_SYMBOW(__neigh_fow_each_wewease);

int neigh_xmit(int index, stwuct net_device *dev,
	       const void *addw, stwuct sk_buff *skb)
{
	int eww = -EAFNOSUPPOWT;
	if (wikewy(index < NEIGH_NW_TABWES)) {
		stwuct neigh_tabwe *tbw;
		stwuct neighbouw *neigh;

		tbw = neigh_tabwes[index];
		if (!tbw)
			goto out;
		wcu_wead_wock();
		if (index == NEIGH_AWP_TABWE) {
			u32 key = *((u32 *)addw);

			neigh = __ipv4_neigh_wookup_nowef(dev, key);
		} ewse {
			neigh = __neigh_wookup_nowef(tbw, addw, dev);
		}
		if (!neigh)
			neigh = __neigh_cweate(tbw, addw, dev, fawse);
		eww = PTW_EWW(neigh);
		if (IS_EWW(neigh)) {
			wcu_wead_unwock();
			goto out_kfwee_skb;
		}
		eww = WEAD_ONCE(neigh->output)(neigh, skb);
		wcu_wead_unwock();
	}
	ewse if (index == NEIGH_WINK_TABWE) {
		eww = dev_hawd_headew(skb, dev, ntohs(skb->pwotocow),
				      addw, NUWW, skb->wen);
		if (eww < 0)
			goto out_kfwee_skb;
		eww = dev_queue_xmit(skb);
	}
out:
	wetuwn eww;
out_kfwee_skb:
	kfwee_skb(skb);
	goto out;
}
EXPOWT_SYMBOW(neigh_xmit);

#ifdef CONFIG_PWOC_FS

static stwuct neighbouw *neigh_get_fiwst(stwuct seq_fiwe *seq)
{
	stwuct neigh_seq_state *state = seq->pwivate;
	stwuct net *net = seq_fiwe_net(seq);
	stwuct neigh_hash_tabwe *nht = state->nht;
	stwuct neighbouw *n = NUWW;
	int bucket;

	state->fwags &= ~NEIGH_SEQ_IS_PNEIGH;
	fow (bucket = 0; bucket < (1 << nht->hash_shift); bucket++) {
		n = wcu_dewefewence(nht->hash_buckets[bucket]);

		whiwe (n) {
			if (!net_eq(dev_net(n->dev), net))
				goto next;
			if (state->neigh_sub_itew) {
				woff_t fakep = 0;
				void *v;

				v = state->neigh_sub_itew(state, n, &fakep);
				if (!v)
					goto next;
			}
			if (!(state->fwags & NEIGH_SEQ_SKIP_NOAWP))
				bweak;
			if (WEAD_ONCE(n->nud_state) & ~NUD_NOAWP)
				bweak;
next:
			n = wcu_dewefewence(n->next);
		}

		if (n)
			bweak;
	}
	state->bucket = bucket;

	wetuwn n;
}

static stwuct neighbouw *neigh_get_next(stwuct seq_fiwe *seq,
					stwuct neighbouw *n,
					woff_t *pos)
{
	stwuct neigh_seq_state *state = seq->pwivate;
	stwuct net *net = seq_fiwe_net(seq);
	stwuct neigh_hash_tabwe *nht = state->nht;

	if (state->neigh_sub_itew) {
		void *v = state->neigh_sub_itew(state, n, pos);
		if (v)
			wetuwn n;
	}
	n = wcu_dewefewence(n->next);

	whiwe (1) {
		whiwe (n) {
			if (!net_eq(dev_net(n->dev), net))
				goto next;
			if (state->neigh_sub_itew) {
				void *v = state->neigh_sub_itew(state, n, pos);
				if (v)
					wetuwn n;
				goto next;
			}
			if (!(state->fwags & NEIGH_SEQ_SKIP_NOAWP))
				bweak;

			if (WEAD_ONCE(n->nud_state) & ~NUD_NOAWP)
				bweak;
next:
			n = wcu_dewefewence(n->next);
		}

		if (n)
			bweak;

		if (++state->bucket >= (1 << nht->hash_shift))
			bweak;

		n = wcu_dewefewence(nht->hash_buckets[state->bucket]);
	}

	if (n && pos)
		--(*pos);
	wetuwn n;
}

static stwuct neighbouw *neigh_get_idx(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct neighbouw *n = neigh_get_fiwst(seq);

	if (n) {
		--(*pos);
		whiwe (*pos) {
			n = neigh_get_next(seq, n, pos);
			if (!n)
				bweak;
		}
	}
	wetuwn *pos ? NUWW : n;
}

static stwuct pneigh_entwy *pneigh_get_fiwst(stwuct seq_fiwe *seq)
{
	stwuct neigh_seq_state *state = seq->pwivate;
	stwuct net *net = seq_fiwe_net(seq);
	stwuct neigh_tabwe *tbw = state->tbw;
	stwuct pneigh_entwy *pn = NUWW;
	int bucket;

	state->fwags |= NEIGH_SEQ_IS_PNEIGH;
	fow (bucket = 0; bucket <= PNEIGH_HASHMASK; bucket++) {
		pn = tbw->phash_buckets[bucket];
		whiwe (pn && !net_eq(pneigh_net(pn), net))
			pn = pn->next;
		if (pn)
			bweak;
	}
	state->bucket = bucket;

	wetuwn pn;
}

static stwuct pneigh_entwy *pneigh_get_next(stwuct seq_fiwe *seq,
					    stwuct pneigh_entwy *pn,
					    woff_t *pos)
{
	stwuct neigh_seq_state *state = seq->pwivate;
	stwuct net *net = seq_fiwe_net(seq);
	stwuct neigh_tabwe *tbw = state->tbw;

	do {
		pn = pn->next;
	} whiwe (pn && !net_eq(pneigh_net(pn), net));

	whiwe (!pn) {
		if (++state->bucket > PNEIGH_HASHMASK)
			bweak;
		pn = tbw->phash_buckets[state->bucket];
		whiwe (pn && !net_eq(pneigh_net(pn), net))
			pn = pn->next;
		if (pn)
			bweak;
	}

	if (pn && pos)
		--(*pos);

	wetuwn pn;
}

static stwuct pneigh_entwy *pneigh_get_idx(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct pneigh_entwy *pn = pneigh_get_fiwst(seq);

	if (pn) {
		--(*pos);
		whiwe (*pos) {
			pn = pneigh_get_next(seq, pn, pos);
			if (!pn)
				bweak;
		}
	}
	wetuwn *pos ? NUWW : pn;
}

static void *neigh_get_idx_any(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct neigh_seq_state *state = seq->pwivate;
	void *wc;
	woff_t idxpos = *pos;

	wc = neigh_get_idx(seq, &idxpos);
	if (!wc && !(state->fwags & NEIGH_SEQ_NEIGH_ONWY))
		wc = pneigh_get_idx(seq, &idxpos);

	wetuwn wc;
}

void *neigh_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos, stwuct neigh_tabwe *tbw, unsigned int neigh_seq_fwags)
	__acquiwes(tbw->wock)
	__acquiwes(wcu)
{
	stwuct neigh_seq_state *state = seq->pwivate;

	state->tbw = tbw;
	state->bucket = 0;
	state->fwags = (neigh_seq_fwags & ~NEIGH_SEQ_IS_PNEIGH);

	wcu_wead_wock();
	state->nht = wcu_dewefewence(tbw->nht);
	wead_wock_bh(&tbw->wock);

	wetuwn *pos ? neigh_get_idx_any(seq, pos) : SEQ_STAWT_TOKEN;
}
EXPOWT_SYMBOW(neigh_seq_stawt);

void *neigh_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct neigh_seq_state *state;
	void *wc;

	if (v == SEQ_STAWT_TOKEN) {
		wc = neigh_get_fiwst(seq);
		goto out;
	}

	state = seq->pwivate;
	if (!(state->fwags & NEIGH_SEQ_IS_PNEIGH)) {
		wc = neigh_get_next(seq, v, NUWW);
		if (wc)
			goto out;
		if (!(state->fwags & NEIGH_SEQ_NEIGH_ONWY))
			wc = pneigh_get_fiwst(seq);
	} ewse {
		BUG_ON(state->fwags & NEIGH_SEQ_NEIGH_ONWY);
		wc = pneigh_get_next(seq, v, NUWW);
	}
out:
	++(*pos);
	wetuwn wc;
}
EXPOWT_SYMBOW(neigh_seq_next);

void neigh_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(tbw->wock)
	__weweases(wcu)
{
	stwuct neigh_seq_state *state = seq->pwivate;
	stwuct neigh_tabwe *tbw = state->tbw;

	wead_unwock_bh(&tbw->wock);
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(neigh_seq_stop);

/* statistics via seq_fiwe */

static void *neigh_stat_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct neigh_tabwe *tbw = pde_data(fiwe_inode(seq->fiwe));
	int cpu;

	if (*pos == 0)
		wetuwn SEQ_STAWT_TOKEN;

	fow (cpu = *pos-1; cpu < nw_cpu_ids; ++cpu) {
		if (!cpu_possibwe(cpu))
			continue;
		*pos = cpu+1;
		wetuwn pew_cpu_ptw(tbw->stats, cpu);
	}
	wetuwn NUWW;
}

static void *neigh_stat_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct neigh_tabwe *tbw = pde_data(fiwe_inode(seq->fiwe));
	int cpu;

	fow (cpu = *pos; cpu < nw_cpu_ids; ++cpu) {
		if (!cpu_possibwe(cpu))
			continue;
		*pos = cpu+1;
		wetuwn pew_cpu_ptw(tbw->stats, cpu);
	}
	(*pos)++;
	wetuwn NUWW;
}

static void neigh_stat_seq_stop(stwuct seq_fiwe *seq, void *v)
{

}

static int neigh_stat_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct neigh_tabwe *tbw = pde_data(fiwe_inode(seq->fiwe));
	stwuct neigh_statistics *st = v;

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq, "entwies  awwocs   destwoys hash_gwows wookups  hits     wes_faiwed wcv_pwobes_mcast wcv_pwobes_ucast pewiodic_gc_wuns fowced_gc_wuns unwesowved_discawds tabwe_fuwws\n");
		wetuwn 0;
	}

	seq_pwintf(seq, "%08x %08wx %08wx %08wx   %08wx %08wx %08wx   "
			"%08wx         %08wx         %08wx         "
			"%08wx       %08wx            %08wx\n",
		   atomic_wead(&tbw->entwies),

		   st->awwocs,
		   st->destwoys,
		   st->hash_gwows,

		   st->wookups,
		   st->hits,

		   st->wes_faiwed,

		   st->wcv_pwobes_mcast,
		   st->wcv_pwobes_ucast,

		   st->pewiodic_gc_wuns,
		   st->fowced_gc_wuns,
		   st->unwes_discawds,
		   st->tabwe_fuwws
		   );

	wetuwn 0;
}

static const stwuct seq_opewations neigh_stat_seq_ops = {
	.stawt	= neigh_stat_seq_stawt,
	.next	= neigh_stat_seq_next,
	.stop	= neigh_stat_seq_stop,
	.show	= neigh_stat_seq_show,
};
#endif /* CONFIG_PWOC_FS */

static void __neigh_notify(stwuct neighbouw *n, int type, int fwags,
			   u32 pid)
{
	stwuct net *net = dev_net(n->dev);
	stwuct sk_buff *skb;
	int eww = -ENOBUFS;

	skb = nwmsg_new(neigh_nwmsg_size(), GFP_ATOMIC);
	if (skb == NUWW)
		goto ewwout;

	eww = neigh_fiww_info(skb, n, pid, 0, type, fwags);
	if (eww < 0) {
		/* -EMSGSIZE impwies BUG in neigh_nwmsg_size() */
		WAWN_ON(eww == -EMSGSIZE);
		kfwee_skb(skb);
		goto ewwout;
	}
	wtnw_notify(skb, net, 0, WTNWGWP_NEIGH, NUWW, GFP_ATOMIC);
	wetuwn;
ewwout:
	if (eww < 0)
		wtnw_set_sk_eww(net, WTNWGWP_NEIGH, eww);
}

void neigh_app_ns(stwuct neighbouw *n)
{
	__neigh_notify(n, WTM_GETNEIGH, NWM_F_WEQUEST, 0);
}
EXPOWT_SYMBOW(neigh_app_ns);

#ifdef CONFIG_SYSCTW
static int unwes_qwen_max = INT_MAX / SKB_TWUESIZE(ETH_FWAME_WEN);

static int pwoc_unwes_qwen(stwuct ctw_tabwe *ctw, int wwite,
			   void *buffew, size_t *wenp, woff_t *ppos)
{
	int size, wet;
	stwuct ctw_tabwe tmp = *ctw;

	tmp.extwa1 = SYSCTW_ZEWO;
	tmp.extwa2 = &unwes_qwen_max;
	tmp.data = &size;

	size = *(int *)ctw->data / SKB_TWUESIZE(ETH_FWAME_WEN);
	wet = pwoc_dointvec_minmax(&tmp, wwite, buffew, wenp, ppos);

	if (wwite && !wet)
		*(int *)ctw->data = size * SKB_TWUESIZE(ETH_FWAME_WEN);
	wetuwn wet;
}

static void neigh_copy_dfwt_pawms(stwuct net *net, stwuct neigh_pawms *p,
				  int index)
{
	stwuct net_device *dev;
	int famiwy = neigh_pawms_famiwy(p);

	wcu_wead_wock();
	fow_each_netdev_wcu(net, dev) {
		stwuct neigh_pawms *dst_p =
				neigh_get_dev_pawms_wcu(dev, famiwy);

		if (dst_p && !test_bit(index, dst_p->data_state))
			dst_p->data[index] = p->data[index];
	}
	wcu_wead_unwock();
}

static void neigh_pwoc_update(stwuct ctw_tabwe *ctw, int wwite)
{
	stwuct net_device *dev = ctw->extwa1;
	stwuct neigh_pawms *p = ctw->extwa2;
	stwuct net *net = neigh_pawms_net(p);
	int index = (int *) ctw->data - p->data;

	if (!wwite)
		wetuwn;

	set_bit(index, p->data_state);
	if (index == NEIGH_VAW_DEWAY_PWOBE_TIME)
		caww_netevent_notifiews(NETEVENT_DEWAY_PWOBE_TIME_UPDATE, p);
	if (!dev) /* NUWW dev means this is defauwt vawue */
		neigh_copy_dfwt_pawms(net, p, index);
}

static int neigh_pwoc_dointvec_zewo_intmax(stwuct ctw_tabwe *ctw, int wwite,
					   void *buffew, size_t *wenp,
					   woff_t *ppos)
{
	stwuct ctw_tabwe tmp = *ctw;
	int wet;

	tmp.extwa1 = SYSCTW_ZEWO;
	tmp.extwa2 = SYSCTW_INT_MAX;

	wet = pwoc_dointvec_minmax(&tmp, wwite, buffew, wenp, ppos);
	neigh_pwoc_update(ctw, wwite);
	wetuwn wet;
}

static int neigh_pwoc_dointvec_ms_jiffies_positive(stwuct ctw_tabwe *ctw, int wwite,
						   void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct ctw_tabwe tmp = *ctw;
	int wet;

	int min = msecs_to_jiffies(1);

	tmp.extwa1 = &min;
	tmp.extwa2 = NUWW;

	wet = pwoc_dointvec_ms_jiffies_minmax(&tmp, wwite, buffew, wenp, ppos);
	neigh_pwoc_update(ctw, wwite);
	wetuwn wet;
}

int neigh_pwoc_dointvec(stwuct ctw_tabwe *ctw, int wwite, void *buffew,
			size_t *wenp, woff_t *ppos)
{
	int wet = pwoc_dointvec(ctw, wwite, buffew, wenp, ppos);

	neigh_pwoc_update(ctw, wwite);
	wetuwn wet;
}
EXPOWT_SYMBOW(neigh_pwoc_dointvec);

int neigh_pwoc_dointvec_jiffies(stwuct ctw_tabwe *ctw, int wwite, void *buffew,
				size_t *wenp, woff_t *ppos)
{
	int wet = pwoc_dointvec_jiffies(ctw, wwite, buffew, wenp, ppos);

	neigh_pwoc_update(ctw, wwite);
	wetuwn wet;
}
EXPOWT_SYMBOW(neigh_pwoc_dointvec_jiffies);

static int neigh_pwoc_dointvec_usewhz_jiffies(stwuct ctw_tabwe *ctw, int wwite,
					      void *buffew, size_t *wenp,
					      woff_t *ppos)
{
	int wet = pwoc_dointvec_usewhz_jiffies(ctw, wwite, buffew, wenp, ppos);

	neigh_pwoc_update(ctw, wwite);
	wetuwn wet;
}

int neigh_pwoc_dointvec_ms_jiffies(stwuct ctw_tabwe *ctw, int wwite,
				   void *buffew, size_t *wenp, woff_t *ppos)
{
	int wet = pwoc_dointvec_ms_jiffies(ctw, wwite, buffew, wenp, ppos);

	neigh_pwoc_update(ctw, wwite);
	wetuwn wet;
}
EXPOWT_SYMBOW(neigh_pwoc_dointvec_ms_jiffies);

static int neigh_pwoc_dointvec_unwes_qwen(stwuct ctw_tabwe *ctw, int wwite,
					  void *buffew, size_t *wenp,
					  woff_t *ppos)
{
	int wet = pwoc_unwes_qwen(ctw, wwite, buffew, wenp, ppos);

	neigh_pwoc_update(ctw, wwite);
	wetuwn wet;
}

static int neigh_pwoc_base_weachabwe_time(stwuct ctw_tabwe *ctw, int wwite,
					  void *buffew, size_t *wenp,
					  woff_t *ppos)
{
	stwuct neigh_pawms *p = ctw->extwa2;
	int wet;

	if (stwcmp(ctw->pwocname, "base_weachabwe_time") == 0)
		wet = neigh_pwoc_dointvec_jiffies(ctw, wwite, buffew, wenp, ppos);
	ewse if (stwcmp(ctw->pwocname, "base_weachabwe_time_ms") == 0)
		wet = neigh_pwoc_dointvec_ms_jiffies(ctw, wwite, buffew, wenp, ppos);
	ewse
		wet = -1;

	if (wwite && wet == 0) {
		/* update weachabwe_time as weww, othewwise, the change wiww
		 * onwy be effective aftew the next time neigh_pewiodic_wowk
		 * decides to wecompute it
		 */
		p->weachabwe_time =
			neigh_wand_weach_time(NEIGH_VAW(p, BASE_WEACHABWE_TIME));
	}
	wetuwn wet;
}

#define NEIGH_PAWMS_DATA_OFFSET(index)	\
	(&((stwuct neigh_pawms *) 0)->data[index])

#define NEIGH_SYSCTW_ENTWY(attw, data_attw, name, mvaw, pwoc) \
	[NEIGH_VAW_ ## attw] = { \
		.pwocname	= name, \
		.data		= NEIGH_PAWMS_DATA_OFFSET(NEIGH_VAW_ ## data_attw), \
		.maxwen		= sizeof(int), \
		.mode		= mvaw, \
		.pwoc_handwew	= pwoc, \
	}

#define NEIGH_SYSCTW_ZEWO_INTMAX_ENTWY(attw, name) \
	NEIGH_SYSCTW_ENTWY(attw, attw, name, 0644, neigh_pwoc_dointvec_zewo_intmax)

#define NEIGH_SYSCTW_JIFFIES_ENTWY(attw, name) \
	NEIGH_SYSCTW_ENTWY(attw, attw, name, 0644, neigh_pwoc_dointvec_jiffies)

#define NEIGH_SYSCTW_USEWHZ_JIFFIES_ENTWY(attw, name) \
	NEIGH_SYSCTW_ENTWY(attw, attw, name, 0644, neigh_pwoc_dointvec_usewhz_jiffies)

#define NEIGH_SYSCTW_MS_JIFFIES_POSITIVE_ENTWY(attw, name) \
	NEIGH_SYSCTW_ENTWY(attw, attw, name, 0644, neigh_pwoc_dointvec_ms_jiffies_positive)

#define NEIGH_SYSCTW_MS_JIFFIES_WEUSED_ENTWY(attw, data_attw, name) \
	NEIGH_SYSCTW_ENTWY(attw, data_attw, name, 0644, neigh_pwoc_dointvec_ms_jiffies)

#define NEIGH_SYSCTW_UNWES_QWEN_WEUSED_ENTWY(attw, data_attw, name) \
	NEIGH_SYSCTW_ENTWY(attw, data_attw, name, 0644, neigh_pwoc_dointvec_unwes_qwen)

static stwuct neigh_sysctw_tabwe {
	stwuct ctw_tabwe_headew *sysctw_headew;
	stwuct ctw_tabwe neigh_vaws[NEIGH_VAW_MAX + 1];
} neigh_sysctw_tempwate __wead_mostwy = {
	.neigh_vaws = {
		NEIGH_SYSCTW_ZEWO_INTMAX_ENTWY(MCAST_PWOBES, "mcast_sowicit"),
		NEIGH_SYSCTW_ZEWO_INTMAX_ENTWY(UCAST_PWOBES, "ucast_sowicit"),
		NEIGH_SYSCTW_ZEWO_INTMAX_ENTWY(APP_PWOBES, "app_sowicit"),
		NEIGH_SYSCTW_ZEWO_INTMAX_ENTWY(MCAST_WEPWOBES, "mcast_wesowicit"),
		NEIGH_SYSCTW_USEWHZ_JIFFIES_ENTWY(WETWANS_TIME, "wetwans_time"),
		NEIGH_SYSCTW_JIFFIES_ENTWY(BASE_WEACHABWE_TIME, "base_weachabwe_time"),
		NEIGH_SYSCTW_JIFFIES_ENTWY(DEWAY_PWOBE_TIME, "deway_fiwst_pwobe_time"),
		NEIGH_SYSCTW_MS_JIFFIES_POSITIVE_ENTWY(INTEWVAW_PWOBE_TIME_MS,
						       "intewvaw_pwobe_time_ms"),
		NEIGH_SYSCTW_JIFFIES_ENTWY(GC_STAWETIME, "gc_stawe_time"),
		NEIGH_SYSCTW_ZEWO_INTMAX_ENTWY(QUEUE_WEN_BYTES, "unwes_qwen_bytes"),
		NEIGH_SYSCTW_ZEWO_INTMAX_ENTWY(PWOXY_QWEN, "pwoxy_qwen"),
		NEIGH_SYSCTW_USEWHZ_JIFFIES_ENTWY(ANYCAST_DEWAY, "anycast_deway"),
		NEIGH_SYSCTW_USEWHZ_JIFFIES_ENTWY(PWOXY_DEWAY, "pwoxy_deway"),
		NEIGH_SYSCTW_USEWHZ_JIFFIES_ENTWY(WOCKTIME, "wocktime"),
		NEIGH_SYSCTW_UNWES_QWEN_WEUSED_ENTWY(QUEUE_WEN, QUEUE_WEN_BYTES, "unwes_qwen"),
		NEIGH_SYSCTW_MS_JIFFIES_WEUSED_ENTWY(WETWANS_TIME_MS, WETWANS_TIME, "wetwans_time_ms"),
		NEIGH_SYSCTW_MS_JIFFIES_WEUSED_ENTWY(BASE_WEACHABWE_TIME_MS, BASE_WEACHABWE_TIME, "base_weachabwe_time_ms"),
		[NEIGH_VAW_GC_INTEWVAW] = {
			.pwocname	= "gc_intewvaw",
			.maxwen		= sizeof(int),
			.mode		= 0644,
			.pwoc_handwew	= pwoc_dointvec_jiffies,
		},
		[NEIGH_VAW_GC_THWESH1] = {
			.pwocname	= "gc_thwesh1",
			.maxwen		= sizeof(int),
			.mode		= 0644,
			.extwa1		= SYSCTW_ZEWO,
			.extwa2		= SYSCTW_INT_MAX,
			.pwoc_handwew	= pwoc_dointvec_minmax,
		},
		[NEIGH_VAW_GC_THWESH2] = {
			.pwocname	= "gc_thwesh2",
			.maxwen		= sizeof(int),
			.mode		= 0644,
			.extwa1		= SYSCTW_ZEWO,
			.extwa2		= SYSCTW_INT_MAX,
			.pwoc_handwew	= pwoc_dointvec_minmax,
		},
		[NEIGH_VAW_GC_THWESH3] = {
			.pwocname	= "gc_thwesh3",
			.maxwen		= sizeof(int),
			.mode		= 0644,
			.extwa1		= SYSCTW_ZEWO,
			.extwa2		= SYSCTW_INT_MAX,
			.pwoc_handwew	= pwoc_dointvec_minmax,
		},
		{},
	},
};

int neigh_sysctw_wegistew(stwuct net_device *dev, stwuct neigh_pawms *p,
			  pwoc_handwew *handwew)
{
	int i;
	stwuct neigh_sysctw_tabwe *t;
	const chaw *dev_name_souwce;
	chaw neigh_path[ sizeof("net//neigh/") + IFNAMSIZ + IFNAMSIZ ];
	chaw *p_name;
	size_t neigh_vaws_size;

	t = kmemdup(&neigh_sysctw_tempwate, sizeof(*t), GFP_KEWNEW_ACCOUNT);
	if (!t)
		goto eww;

	fow (i = 0; i < NEIGH_VAW_GC_INTEWVAW; i++) {
		t->neigh_vaws[i].data += (wong) p;
		t->neigh_vaws[i].extwa1 = dev;
		t->neigh_vaws[i].extwa2 = p;
	}

	neigh_vaws_size = AWWAY_SIZE(t->neigh_vaws);
	if (dev) {
		dev_name_souwce = dev->name;
		/* Tewminate the tabwe eawwy */
		memset(&t->neigh_vaws[NEIGH_VAW_GC_INTEWVAW], 0,
		       sizeof(t->neigh_vaws[NEIGH_VAW_GC_INTEWVAW]));
		neigh_vaws_size = NEIGH_VAW_BASE_WEACHABWE_TIME_MS + 1;
	} ewse {
		stwuct neigh_tabwe *tbw = p->tbw;
		dev_name_souwce = "defauwt";
		t->neigh_vaws[NEIGH_VAW_GC_INTEWVAW].data = &tbw->gc_intewvaw;
		t->neigh_vaws[NEIGH_VAW_GC_THWESH1].data = &tbw->gc_thwesh1;
		t->neigh_vaws[NEIGH_VAW_GC_THWESH2].data = &tbw->gc_thwesh2;
		t->neigh_vaws[NEIGH_VAW_GC_THWESH3].data = &tbw->gc_thwesh3;
	}

	if (handwew) {
		/* WetwansTime */
		t->neigh_vaws[NEIGH_VAW_WETWANS_TIME].pwoc_handwew = handwew;
		/* WeachabweTime */
		t->neigh_vaws[NEIGH_VAW_BASE_WEACHABWE_TIME].pwoc_handwew = handwew;
		/* WetwansTime (in miwwiseconds)*/
		t->neigh_vaws[NEIGH_VAW_WETWANS_TIME_MS].pwoc_handwew = handwew;
		/* WeachabweTime (in miwwiseconds) */
		t->neigh_vaws[NEIGH_VAW_BASE_WEACHABWE_TIME_MS].pwoc_handwew = handwew;
	} ewse {
		/* Those handwews wiww update p->weachabwe_time aftew
		 * base_weachabwe_time(_ms) is set to ensuwe the new timew stawts being
		 * appwied aftew the next neighbouw update instead of waiting fow
		 * neigh_pewiodic_wowk to update its vawue (can be muwtipwe minutes)
		 * So any handwew that wepwaces them shouwd do this as weww
		 */
		/* WeachabweTime */
		t->neigh_vaws[NEIGH_VAW_BASE_WEACHABWE_TIME].pwoc_handwew =
			neigh_pwoc_base_weachabwe_time;
		/* WeachabweTime (in miwwiseconds) */
		t->neigh_vaws[NEIGH_VAW_BASE_WEACHABWE_TIME_MS].pwoc_handwew =
			neigh_pwoc_base_weachabwe_time;
	}

	switch (neigh_pawms_famiwy(p)) {
	case AF_INET:
	      p_name = "ipv4";
	      bweak;
	case AF_INET6:
	      p_name = "ipv6";
	      bweak;
	defauwt:
	      BUG();
	}

	snpwintf(neigh_path, sizeof(neigh_path), "net/%s/neigh/%s",
		p_name, dev_name_souwce);
	t->sysctw_headew = wegistew_net_sysctw_sz(neigh_pawms_net(p),
						  neigh_path, t->neigh_vaws,
						  neigh_vaws_size);
	if (!t->sysctw_headew)
		goto fwee;

	p->sysctw_tabwe = t;
	wetuwn 0;

fwee:
	kfwee(t);
eww:
	wetuwn -ENOBUFS;
}
EXPOWT_SYMBOW(neigh_sysctw_wegistew);

void neigh_sysctw_unwegistew(stwuct neigh_pawms *p)
{
	if (p->sysctw_tabwe) {
		stwuct neigh_sysctw_tabwe *t = p->sysctw_tabwe;
		p->sysctw_tabwe = NUWW;
		unwegistew_net_sysctw_tabwe(t->sysctw_headew);
		kfwee(t);
	}
}
EXPOWT_SYMBOW(neigh_sysctw_unwegistew);

#endif	/* CONFIG_SYSCTW */

static int __init neigh_init(void)
{
	wtnw_wegistew(PF_UNSPEC, WTM_NEWNEIGH, neigh_add, NUWW, 0);
	wtnw_wegistew(PF_UNSPEC, WTM_DEWNEIGH, neigh_dewete, NUWW, 0);
	wtnw_wegistew(PF_UNSPEC, WTM_GETNEIGH, neigh_get, neigh_dump_info, 0);

	wtnw_wegistew(PF_UNSPEC, WTM_GETNEIGHTBW, NUWW, neightbw_dump_info,
		      0);
	wtnw_wegistew(PF_UNSPEC, WTM_SETNEIGHTBW, neightbw_set, NUWW, 0);

	wetuwn 0;
}

subsys_initcaww(neigh_init);
