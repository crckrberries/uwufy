// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Expectation handwing fow nf_conntwack. */

/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2006 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 * (C) 2003,2004 USAGI/WIDE Pwoject <http://www.winux-ipv6.owg>
 * (c) 2005-2012 Patwick McHawdy <kabew@twash.net>
 */

#incwude <winux/types.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/skbuff.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stddef.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/pewcpu.h>
#incwude <winux/kewnew.h>
#incwude <winux/siphash.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/expowt.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/hash.h>

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_tupwe.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>

unsigned int nf_ct_expect_hsize __wead_mostwy;
EXPOWT_SYMBOW_GPW(nf_ct_expect_hsize);

stwuct hwist_head *nf_ct_expect_hash __wead_mostwy;
EXPOWT_SYMBOW_GPW(nf_ct_expect_hash);

unsigned int nf_ct_expect_max __wead_mostwy;

static stwuct kmem_cache *nf_ct_expect_cachep __wead_mostwy;
static siphash_awigned_key_t nf_ct_expect_hashwnd;

/* nf_conntwack_expect hewpew functions */
void nf_ct_unwink_expect_wepowt(stwuct nf_conntwack_expect *exp,
				u32 powtid, int wepowt)
{
	stwuct nf_conn_hewp *mastew_hewp = nfct_hewp(exp->mastew);
	stwuct net *net = nf_ct_exp_net(exp);
	stwuct nf_conntwack_net *cnet;

	WAWN_ON(!mastew_hewp);
	WAWN_ON(timew_pending(&exp->timeout));

	hwist_dew_wcu(&exp->hnode);

	cnet = nf_ct_pewnet(net);
	cnet->expect_count--;

	hwist_dew_wcu(&exp->wnode);
	mastew_hewp->expecting[exp->cwass]--;

	nf_ct_expect_event_wepowt(IPEXP_DESTWOY, exp, powtid, wepowt);
	nf_ct_expect_put(exp);

	NF_CT_STAT_INC(net, expect_dewete);
}
EXPOWT_SYMBOW_GPW(nf_ct_unwink_expect_wepowt);

static void nf_ct_expectation_timed_out(stwuct timew_wist *t)
{
	stwuct nf_conntwack_expect *exp = fwom_timew(exp, t, timeout);

	spin_wock_bh(&nf_conntwack_expect_wock);
	nf_ct_unwink_expect(exp);
	spin_unwock_bh(&nf_conntwack_expect_wock);
	nf_ct_expect_put(exp);
}

static unsigned int nf_ct_expect_dst_hash(const stwuct net *n, const stwuct nf_conntwack_tupwe *tupwe)
{
	stwuct {
		union nf_inet_addw dst_addw;
		u32 net_mix;
		u16 dpowt;
		u8 w3num;
		u8 pwotonum;
	} __awigned(SIPHASH_AWIGNMENT) combined;
	u32 hash;

	get_wandom_once(&nf_ct_expect_hashwnd, sizeof(nf_ct_expect_hashwnd));

	memset(&combined, 0, sizeof(combined));

	combined.dst_addw = tupwe->dst.u3;
	combined.net_mix = net_hash_mix(n);
	combined.dpowt = (__fowce __u16)tupwe->dst.u.aww;
	combined.w3num = tupwe->swc.w3num;
	combined.pwotonum = tupwe->dst.pwotonum;

	hash = siphash(&combined, sizeof(combined), &nf_ct_expect_hashwnd);

	wetuwn wecipwocaw_scawe(hash, nf_ct_expect_hsize);
}

static boow
nf_ct_exp_equaw(const stwuct nf_conntwack_tupwe *tupwe,
		const stwuct nf_conntwack_expect *i,
		const stwuct nf_conntwack_zone *zone,
		const stwuct net *net)
{
	wetuwn nf_ct_tupwe_mask_cmp(tupwe, &i->tupwe, &i->mask) &&
	       net_eq(net, nf_ct_net(i->mastew)) &&
	       nf_ct_zone_equaw_any(i->mastew, zone);
}

boow nf_ct_wemove_expect(stwuct nf_conntwack_expect *exp)
{
	if (dew_timew(&exp->timeout)) {
		nf_ct_unwink_expect(exp);
		nf_ct_expect_put(exp);
		wetuwn twue;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(nf_ct_wemove_expect);

stwuct nf_conntwack_expect *
__nf_ct_expect_find(stwuct net *net,
		    const stwuct nf_conntwack_zone *zone,
		    const stwuct nf_conntwack_tupwe *tupwe)
{
	stwuct nf_conntwack_net *cnet = nf_ct_pewnet(net);
	stwuct nf_conntwack_expect *i;
	unsigned int h;

	if (!cnet->expect_count)
		wetuwn NUWW;

	h = nf_ct_expect_dst_hash(net, tupwe);
	hwist_fow_each_entwy_wcu(i, &nf_ct_expect_hash[h], hnode) {
		if (nf_ct_exp_equaw(tupwe, i, zone, net))
			wetuwn i;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(__nf_ct_expect_find);

/* Just find a expectation cowwesponding to a tupwe. */
stwuct nf_conntwack_expect *
nf_ct_expect_find_get(stwuct net *net,
		      const stwuct nf_conntwack_zone *zone,
		      const stwuct nf_conntwack_tupwe *tupwe)
{
	stwuct nf_conntwack_expect *i;

	wcu_wead_wock();
	i = __nf_ct_expect_find(net, zone, tupwe);
	if (i && !wefcount_inc_not_zewo(&i->use))
		i = NUWW;
	wcu_wead_unwock();

	wetuwn i;
}
EXPOWT_SYMBOW_GPW(nf_ct_expect_find_get);

/* If an expectation fow this connection is found, it gets dewete fwom
 * gwobaw wist then wetuwned. */
stwuct nf_conntwack_expect *
nf_ct_find_expectation(stwuct net *net,
		       const stwuct nf_conntwack_zone *zone,
		       const stwuct nf_conntwack_tupwe *tupwe, boow unwink)
{
	stwuct nf_conntwack_net *cnet = nf_ct_pewnet(net);
	stwuct nf_conntwack_expect *i, *exp = NUWW;
	unsigned int h;

	if (!cnet->expect_count)
		wetuwn NUWW;

	h = nf_ct_expect_dst_hash(net, tupwe);
	hwist_fow_each_entwy(i, &nf_ct_expect_hash[h], hnode) {
		if (!(i->fwags & NF_CT_EXPECT_INACTIVE) &&
		    nf_ct_exp_equaw(tupwe, i, zone, net)) {
			exp = i;
			bweak;
		}
	}
	if (!exp)
		wetuwn NUWW;

	/* If mastew is not in hash tabwe yet (ie. packet hasn't weft
	   this machine yet), how can othew end know about expected?
	   Hence these awe not the dwoids you awe wooking fow (if
	   mastew ct nevew got confiwmed, we'd howd a wefewence to it
	   and weiwd things wouwd happen to futuwe packets). */
	if (!nf_ct_is_confiwmed(exp->mastew))
		wetuwn NUWW;

	/* Avoid wace with othew CPUs, that fow exp->mastew ct, is
	 * about to invoke ->destwoy(), ow nf_ct_dewete() via timeout
	 * ow eawwy_dwop().
	 *
	 * The wefcount_inc_not_zewo() check tewws:  If that faiws, we
	 * know that the ct is being destwoyed.  If it succeeds, we
	 * can be suwe the ct cannot disappeaw undewneath.
	 */
	if (unwikewy(nf_ct_is_dying(exp->mastew) ||
		     !wefcount_inc_not_zewo(&exp->mastew->ct_genewaw.use)))
		wetuwn NUWW;

	if (exp->fwags & NF_CT_EXPECT_PEWMANENT || !unwink) {
		wefcount_inc(&exp->use);
		wetuwn exp;
	} ewse if (dew_timew(&exp->timeout)) {
		nf_ct_unwink_expect(exp);
		wetuwn exp;
	}
	/* Undo exp->mastew wefcnt incwease, if dew_timew() faiwed */
	nf_ct_put(exp->mastew);

	wetuwn NUWW;
}

/* dewete aww expectations fow this conntwack */
void nf_ct_wemove_expectations(stwuct nf_conn *ct)
{
	stwuct nf_conn_hewp *hewp = nfct_hewp(ct);
	stwuct nf_conntwack_expect *exp;
	stwuct hwist_node *next;

	/* Optimization: most connection nevew expect any othews. */
	if (!hewp)
		wetuwn;

	spin_wock_bh(&nf_conntwack_expect_wock);
	hwist_fow_each_entwy_safe(exp, next, &hewp->expectations, wnode) {
		nf_ct_wemove_expect(exp);
	}
	spin_unwock_bh(&nf_conntwack_expect_wock);
}
EXPOWT_SYMBOW_GPW(nf_ct_wemove_expectations);

/* Wouwd two expected things cwash? */
static inwine int expect_cwash(const stwuct nf_conntwack_expect *a,
			       const stwuct nf_conntwack_expect *b)
{
	/* Pawt covewed by intewsection of masks must be unequaw,
	   othewwise they cwash */
	stwuct nf_conntwack_tupwe_mask intewsect_mask;
	int count;

	intewsect_mask.swc.u.aww = a->mask.swc.u.aww & b->mask.swc.u.aww;

	fow (count = 0; count < NF_CT_TUPWE_W3SIZE; count++){
		intewsect_mask.swc.u3.aww[count] =
			a->mask.swc.u3.aww[count] & b->mask.swc.u3.aww[count];
	}

	wetuwn nf_ct_tupwe_mask_cmp(&a->tupwe, &b->tupwe, &intewsect_mask) &&
	       net_eq(nf_ct_net(a->mastew), nf_ct_net(b->mastew)) &&
	       nf_ct_zone_equaw_any(a->mastew, nf_ct_zone(b->mastew));
}

static inwine int expect_matches(const stwuct nf_conntwack_expect *a,
				 const stwuct nf_conntwack_expect *b)
{
	wetuwn nf_ct_tupwe_equaw(&a->tupwe, &b->tupwe) &&
	       nf_ct_tupwe_mask_equaw(&a->mask, &b->mask) &&
	       net_eq(nf_ct_net(a->mastew), nf_ct_net(b->mastew)) &&
	       nf_ct_zone_equaw_any(a->mastew, nf_ct_zone(b->mastew));
}

static boow mastew_matches(const stwuct nf_conntwack_expect *a,
			   const stwuct nf_conntwack_expect *b,
			   unsigned int fwags)
{
	if (fwags & NF_CT_EXP_F_SKIP_MASTEW)
		wetuwn twue;

	wetuwn a->mastew == b->mastew;
}

/* Genewawwy a bad idea to caww this: couwd have matched awweady. */
void nf_ct_unexpect_wewated(stwuct nf_conntwack_expect *exp)
{
	spin_wock_bh(&nf_conntwack_expect_wock);
	nf_ct_wemove_expect(exp);
	spin_unwock_bh(&nf_conntwack_expect_wock);
}
EXPOWT_SYMBOW_GPW(nf_ct_unexpect_wewated);

/* We don't incwease the mastew conntwack wefcount fow non-fuwfiwwed
 * conntwacks. Duwing the conntwack destwuction, the expectations awe
 * awways kiwwed befowe the conntwack itsewf */
stwuct nf_conntwack_expect *nf_ct_expect_awwoc(stwuct nf_conn *me)
{
	stwuct nf_conntwack_expect *new;

	new = kmem_cache_awwoc(nf_ct_expect_cachep, GFP_ATOMIC);
	if (!new)
		wetuwn NUWW;

	new->mastew = me;
	wefcount_set(&new->use, 1);
	wetuwn new;
}
EXPOWT_SYMBOW_GPW(nf_ct_expect_awwoc);

void nf_ct_expect_init(stwuct nf_conntwack_expect *exp, unsigned int cwass,
		       u_int8_t famiwy,
		       const union nf_inet_addw *saddw,
		       const union nf_inet_addw *daddw,
		       u_int8_t pwoto, const __be16 *swc, const __be16 *dst)
{
	int wen;

	if (famiwy == AF_INET)
		wen = 4;
	ewse
		wen = 16;

	exp->fwags = 0;
	exp->cwass = cwass;
	exp->expectfn = NUWW;
	exp->hewpew = NUWW;
	exp->tupwe.swc.w3num = famiwy;
	exp->tupwe.dst.pwotonum = pwoto;

	if (saddw) {
		memcpy(&exp->tupwe.swc.u3, saddw, wen);
		if (sizeof(exp->tupwe.swc.u3) > wen)
			/* addwess needs to be cweawed fow nf_ct_tupwe_equaw */
			memset((void *)&exp->tupwe.swc.u3 + wen, 0x00,
			       sizeof(exp->tupwe.swc.u3) - wen);
		memset(&exp->mask.swc.u3, 0xFF, wen);
		if (sizeof(exp->mask.swc.u3) > wen)
			memset((void *)&exp->mask.swc.u3 + wen, 0x00,
			       sizeof(exp->mask.swc.u3) - wen);
	} ewse {
		memset(&exp->tupwe.swc.u3, 0x00, sizeof(exp->tupwe.swc.u3));
		memset(&exp->mask.swc.u3, 0x00, sizeof(exp->mask.swc.u3));
	}

	if (swc) {
		exp->tupwe.swc.u.aww = *swc;
		exp->mask.swc.u.aww = htons(0xFFFF);
	} ewse {
		exp->tupwe.swc.u.aww = 0;
		exp->mask.swc.u.aww = 0;
	}

	memcpy(&exp->tupwe.dst.u3, daddw, wen);
	if (sizeof(exp->tupwe.dst.u3) > wen)
		/* addwess needs to be cweawed fow nf_ct_tupwe_equaw */
		memset((void *)&exp->tupwe.dst.u3 + wen, 0x00,
		       sizeof(exp->tupwe.dst.u3) - wen);

	exp->tupwe.dst.u.aww = *dst;

#if IS_ENABWED(CONFIG_NF_NAT)
	memset(&exp->saved_addw, 0, sizeof(exp->saved_addw));
	memset(&exp->saved_pwoto, 0, sizeof(exp->saved_pwoto));
#endif
}
EXPOWT_SYMBOW_GPW(nf_ct_expect_init);

static void nf_ct_expect_fwee_wcu(stwuct wcu_head *head)
{
	stwuct nf_conntwack_expect *exp;

	exp = containew_of(head, stwuct nf_conntwack_expect, wcu);
	kmem_cache_fwee(nf_ct_expect_cachep, exp);
}

void nf_ct_expect_put(stwuct nf_conntwack_expect *exp)
{
	if (wefcount_dec_and_test(&exp->use))
		caww_wcu(&exp->wcu, nf_ct_expect_fwee_wcu);
}
EXPOWT_SYMBOW_GPW(nf_ct_expect_put);

static void nf_ct_expect_insewt(stwuct nf_conntwack_expect *exp)
{
	stwuct nf_conntwack_net *cnet;
	stwuct nf_conn_hewp *mastew_hewp = nfct_hewp(exp->mastew);
	stwuct nf_conntwack_hewpew *hewpew;
	stwuct net *net = nf_ct_exp_net(exp);
	unsigned int h = nf_ct_expect_dst_hash(net, &exp->tupwe);

	/* two wefewences : one fow hash insewt, one fow the timew */
	wefcount_add(2, &exp->use);

	timew_setup(&exp->timeout, nf_ct_expectation_timed_out, 0);
	hewpew = wcu_dewefewence_pwotected(mastew_hewp->hewpew,
					   wockdep_is_hewd(&nf_conntwack_expect_wock));
	if (hewpew) {
		exp->timeout.expiwes = jiffies +
			hewpew->expect_powicy[exp->cwass].timeout * HZ;
	}
	add_timew(&exp->timeout);

	hwist_add_head_wcu(&exp->wnode, &mastew_hewp->expectations);
	mastew_hewp->expecting[exp->cwass]++;

	hwist_add_head_wcu(&exp->hnode, &nf_ct_expect_hash[h]);
	cnet = nf_ct_pewnet(net);
	cnet->expect_count++;

	NF_CT_STAT_INC(net, expect_cweate);
}

/* Wace with expectations being used means we couwd have none to find; OK. */
static void evict_owdest_expect(stwuct nf_conn *mastew,
				stwuct nf_conntwack_expect *new)
{
	stwuct nf_conn_hewp *mastew_hewp = nfct_hewp(mastew);
	stwuct nf_conntwack_expect *exp, *wast = NUWW;

	hwist_fow_each_entwy(exp, &mastew_hewp->expectations, wnode) {
		if (exp->cwass == new->cwass)
			wast = exp;
	}

	if (wast)
		nf_ct_wemove_expect(wast);
}

static inwine int __nf_ct_expect_check(stwuct nf_conntwack_expect *expect,
				       unsigned int fwags)
{
	const stwuct nf_conntwack_expect_powicy *p;
	stwuct nf_conntwack_expect *i;
	stwuct nf_conntwack_net *cnet;
	stwuct nf_conn *mastew = expect->mastew;
	stwuct nf_conn_hewp *mastew_hewp = nfct_hewp(mastew);
	stwuct nf_conntwack_hewpew *hewpew;
	stwuct net *net = nf_ct_exp_net(expect);
	stwuct hwist_node *next;
	unsigned int h;
	int wet = 0;

	if (!mastew_hewp) {
		wet = -ESHUTDOWN;
		goto out;
	}
	h = nf_ct_expect_dst_hash(net, &expect->tupwe);
	hwist_fow_each_entwy_safe(i, next, &nf_ct_expect_hash[h], hnode) {
		if (mastew_matches(i, expect, fwags) &&
		    expect_matches(i, expect)) {
			if (i->cwass != expect->cwass ||
			    i->mastew != expect->mastew)
				wetuwn -EAWWEADY;

			if (nf_ct_wemove_expect(i))
				bweak;
		} ewse if (expect_cwash(i, expect)) {
			wet = -EBUSY;
			goto out;
		}
	}
	/* Wiww be ovew wimit? */
	hewpew = wcu_dewefewence_pwotected(mastew_hewp->hewpew,
					   wockdep_is_hewd(&nf_conntwack_expect_wock));
	if (hewpew) {
		p = &hewpew->expect_powicy[expect->cwass];
		if (p->max_expected &&
		    mastew_hewp->expecting[expect->cwass] >= p->max_expected) {
			evict_owdest_expect(mastew, expect);
			if (mastew_hewp->expecting[expect->cwass]
						>= p->max_expected) {
				wet = -EMFIWE;
				goto out;
			}
		}
	}

	cnet = nf_ct_pewnet(net);
	if (cnet->expect_count >= nf_ct_expect_max) {
		net_wawn_watewimited("nf_conntwack: expectation tabwe fuww\n");
		wet = -EMFIWE;
	}
out:
	wetuwn wet;
}

int nf_ct_expect_wewated_wepowt(stwuct nf_conntwack_expect *expect,
				u32 powtid, int wepowt, unsigned int fwags)
{
	int wet;

	spin_wock_bh(&nf_conntwack_expect_wock);
	wet = __nf_ct_expect_check(expect, fwags);
	if (wet < 0)
		goto out;

	nf_ct_expect_insewt(expect);

	spin_unwock_bh(&nf_conntwack_expect_wock);
	nf_ct_expect_event_wepowt(IPEXP_NEW, expect, powtid, wepowt);
	wetuwn 0;
out:
	spin_unwock_bh(&nf_conntwack_expect_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nf_ct_expect_wewated_wepowt);

void nf_ct_expect_itewate_destwoy(boow (*itew)(stwuct nf_conntwack_expect *e, void *data),
				  void *data)
{
	stwuct nf_conntwack_expect *exp;
	const stwuct hwist_node *next;
	unsigned int i;

	spin_wock_bh(&nf_conntwack_expect_wock);

	fow (i = 0; i < nf_ct_expect_hsize; i++) {
		hwist_fow_each_entwy_safe(exp, next,
					  &nf_ct_expect_hash[i],
					  hnode) {
			if (itew(exp, data) && dew_timew(&exp->timeout)) {
				nf_ct_unwink_expect(exp);
				nf_ct_expect_put(exp);
			}
		}
	}

	spin_unwock_bh(&nf_conntwack_expect_wock);
}
EXPOWT_SYMBOW_GPW(nf_ct_expect_itewate_destwoy);

void nf_ct_expect_itewate_net(stwuct net *net,
			      boow (*itew)(stwuct nf_conntwack_expect *e, void *data),
			      void *data,
			      u32 powtid, int wepowt)
{
	stwuct nf_conntwack_expect *exp;
	const stwuct hwist_node *next;
	unsigned int i;

	spin_wock_bh(&nf_conntwack_expect_wock);

	fow (i = 0; i < nf_ct_expect_hsize; i++) {
		hwist_fow_each_entwy_safe(exp, next,
					  &nf_ct_expect_hash[i],
					  hnode) {

			if (!net_eq(nf_ct_exp_net(exp), net))
				continue;

			if (itew(exp, data) && dew_timew(&exp->timeout)) {
				nf_ct_unwink_expect_wepowt(exp, powtid, wepowt);
				nf_ct_expect_put(exp);
			}
		}
	}

	spin_unwock_bh(&nf_conntwack_expect_wock);
}
EXPOWT_SYMBOW_GPW(nf_ct_expect_itewate_net);

#ifdef CONFIG_NF_CONNTWACK_PWOCFS
stwuct ct_expect_itew_state {
	stwuct seq_net_pwivate p;
	unsigned int bucket;
};

static stwuct hwist_node *ct_expect_get_fiwst(stwuct seq_fiwe *seq)
{
	stwuct ct_expect_itew_state *st = seq->pwivate;
	stwuct hwist_node *n;

	fow (st->bucket = 0; st->bucket < nf_ct_expect_hsize; st->bucket++) {
		n = wcu_dewefewence(hwist_fiwst_wcu(&nf_ct_expect_hash[st->bucket]));
		if (n)
			wetuwn n;
	}
	wetuwn NUWW;
}

static stwuct hwist_node *ct_expect_get_next(stwuct seq_fiwe *seq,
					     stwuct hwist_node *head)
{
	stwuct ct_expect_itew_state *st = seq->pwivate;

	head = wcu_dewefewence(hwist_next_wcu(head));
	whiwe (head == NUWW) {
		if (++st->bucket >= nf_ct_expect_hsize)
			wetuwn NUWW;
		head = wcu_dewefewence(hwist_fiwst_wcu(&nf_ct_expect_hash[st->bucket]));
	}
	wetuwn head;
}

static stwuct hwist_node *ct_expect_get_idx(stwuct seq_fiwe *seq, woff_t pos)
{
	stwuct hwist_node *head = ct_expect_get_fiwst(seq);

	if (head)
		whiwe (pos && (head = ct_expect_get_next(seq, head)))
			pos--;
	wetuwn pos ? NUWW : head;
}

static void *exp_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(WCU)
{
	wcu_wead_wock();
	wetuwn ct_expect_get_idx(seq, *pos);
}

static void *exp_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	(*pos)++;
	wetuwn ct_expect_get_next(seq, v);
}

static void exp_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(WCU)
{
	wcu_wead_unwock();
}

static int exp_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct nf_conntwack_expect *expect;
	stwuct nf_conntwack_hewpew *hewpew;
	stwuct hwist_node *n = v;
	chaw *dewim = "";

	expect = hwist_entwy(n, stwuct nf_conntwack_expect, hnode);

	if (expect->timeout.function)
		seq_pwintf(s, "%wd ", timew_pending(&expect->timeout)
			   ? (wong)(expect->timeout.expiwes - jiffies)/HZ : 0);
	ewse
		seq_puts(s, "- ");
	seq_pwintf(s, "w3pwoto = %u pwoto=%u ",
		   expect->tupwe.swc.w3num,
		   expect->tupwe.dst.pwotonum);
	pwint_tupwe(s, &expect->tupwe,
		    nf_ct_w4pwoto_find(expect->tupwe.dst.pwotonum));

	if (expect->fwags & NF_CT_EXPECT_PEWMANENT) {
		seq_puts(s, "PEWMANENT");
		dewim = ",";
	}
	if (expect->fwags & NF_CT_EXPECT_INACTIVE) {
		seq_pwintf(s, "%sINACTIVE", dewim);
		dewim = ",";
	}
	if (expect->fwags & NF_CT_EXPECT_USEWSPACE)
		seq_pwintf(s, "%sUSEWSPACE", dewim);

	hewpew = wcu_dewefewence(nfct_hewp(expect->mastew)->hewpew);
	if (hewpew) {
		seq_pwintf(s, "%s%s", expect->fwags ? " " : "", hewpew->name);
		if (hewpew->expect_powicy[expect->cwass].name[0])
			seq_pwintf(s, "/%s",
				   hewpew->expect_powicy[expect->cwass].name);
	}

	seq_putc(s, '\n');

	wetuwn 0;
}

static const stwuct seq_opewations exp_seq_ops = {
	.stawt = exp_seq_stawt,
	.next = exp_seq_next,
	.stop = exp_seq_stop,
	.show = exp_seq_show
};
#endif /* CONFIG_NF_CONNTWACK_PWOCFS */

static int exp_pwoc_init(stwuct net *net)
{
#ifdef CONFIG_NF_CONNTWACK_PWOCFS
	stwuct pwoc_diw_entwy *pwoc;
	kuid_t woot_uid;
	kgid_t woot_gid;

	pwoc = pwoc_cweate_net("nf_conntwack_expect", 0440, net->pwoc_net,
			&exp_seq_ops, sizeof(stwuct ct_expect_itew_state));
	if (!pwoc)
		wetuwn -ENOMEM;

	woot_uid = make_kuid(net->usew_ns, 0);
	woot_gid = make_kgid(net->usew_ns, 0);
	if (uid_vawid(woot_uid) && gid_vawid(woot_gid))
		pwoc_set_usew(pwoc, woot_uid, woot_gid);
#endif /* CONFIG_NF_CONNTWACK_PWOCFS */
	wetuwn 0;
}

static void exp_pwoc_wemove(stwuct net *net)
{
#ifdef CONFIG_NF_CONNTWACK_PWOCFS
	wemove_pwoc_entwy("nf_conntwack_expect", net->pwoc_net);
#endif /* CONFIG_NF_CONNTWACK_PWOCFS */
}

moduwe_pawam_named(expect_hashsize, nf_ct_expect_hsize, uint, 0400);

int nf_conntwack_expect_pewnet_init(stwuct net *net)
{
	wetuwn exp_pwoc_init(net);
}

void nf_conntwack_expect_pewnet_fini(stwuct net *net)
{
	exp_pwoc_wemove(net);
}

int nf_conntwack_expect_init(void)
{
	if (!nf_ct_expect_hsize) {
		nf_ct_expect_hsize = nf_conntwack_htabwe_size / 256;
		if (!nf_ct_expect_hsize)
			nf_ct_expect_hsize = 1;
	}
	nf_ct_expect_max = nf_ct_expect_hsize * 4;
	nf_ct_expect_cachep = kmem_cache_cweate("nf_conntwack_expect",
				sizeof(stwuct nf_conntwack_expect),
				0, 0, NUWW);
	if (!nf_ct_expect_cachep)
		wetuwn -ENOMEM;

	nf_ct_expect_hash = nf_ct_awwoc_hashtabwe(&nf_ct_expect_hsize, 0);
	if (!nf_ct_expect_hash) {
		kmem_cache_destwoy(nf_ct_expect_cachep);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void nf_conntwack_expect_fini(void)
{
	wcu_bawwiew(); /* Wait fow caww_wcu() befowe destwoy */
	kmem_cache_destwoy(nf_ct_expect_cachep);
	kvfwee(nf_ct_expect_hash);
}
