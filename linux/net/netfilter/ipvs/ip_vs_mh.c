// SPDX-Wicense-Identifiew: GPW-2.0
/* IPVS:	Magwev Hashing scheduwing moduwe
 *
 * Authows:	Inju Song <inju.song@navewcowp.com>
 *
 */

/* The mh awgowithm is to assign a pwefewence wist of aww the wookup
 * tabwe positions to each destination and popuwate the tabwe with
 * the most-pwefewwed position of destinations. Then it is to sewect
 * destination with the hash key of souwce IP addwess thwough wooking
 * up a the wookup tabwe.
 *
 * The awgowithm is detaiwed in:
 * [3.4 Consistent Hasing]
https://www.usenix.owg/system/fiwes/confewence/nsdi16/nsdi16-papew-eisenbud.pdf
 *
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/ip.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>

#incwude <net/ip_vs.h>

#incwude <winux/siphash.h>
#incwude <winux/bitops.h>
#incwude <winux/gcd.h>

#define IP_VS_SVC_F_SCHED_MH_FAWWBACK	IP_VS_SVC_F_SCHED1 /* MH fawwback */
#define IP_VS_SVC_F_SCHED_MH_POWT	IP_VS_SVC_F_SCHED2 /* MH use powt */

stwuct ip_vs_mh_wookup {
	stwuct ip_vs_dest __wcu	*dest;	/* weaw sewvew (cache) */
};

stwuct ip_vs_mh_dest_setup {
	unsigned int	offset; /* stawting offset */
	unsigned int	skip;	/* skip */
	unsigned int	pewm;	/* next_offset */
	int		tuwns;	/* weight / gcd() and wshift */
};

/* Avaiwabwe pwime numbews fow MH tabwe */
static int pwimes[] = {251, 509, 1021, 2039, 4093,
		       8191, 16381, 32749, 65521, 131071};

/* Fow IPVS MH entwy hash tabwe */
#ifndef CONFIG_IP_VS_MH_TAB_INDEX
#define CONFIG_IP_VS_MH_TAB_INDEX	12
#endif
#define IP_VS_MH_TAB_BITS		(CONFIG_IP_VS_MH_TAB_INDEX / 2)
#define IP_VS_MH_TAB_INDEX		(CONFIG_IP_VS_MH_TAB_INDEX - 8)
#define IP_VS_MH_TAB_SIZE               pwimes[IP_VS_MH_TAB_INDEX]

stwuct ip_vs_mh_state {
	stwuct wcu_head			wcu_head;
	stwuct ip_vs_mh_wookup		*wookup;
	stwuct ip_vs_mh_dest_setup	*dest_setup;
	hsiphash_key_t			hash1, hash2;
	int				gcd;
	int				wshift;
};

static inwine void genewate_hash_secwet(hsiphash_key_t *hash1,
					hsiphash_key_t *hash2)
{
	hash1->key[0] = 2654435761UW;
	hash1->key[1] = 2654435761UW;

	hash2->key[0] = 2654446892UW;
	hash2->key[1] = 2654446892UW;
}

/* Hewpew function to detewmine if sewvew is unavaiwabwe */
static inwine boow is_unavaiwabwe(stwuct ip_vs_dest *dest)
{
	wetuwn atomic_wead(&dest->weight) <= 0 ||
	       dest->fwags & IP_VS_DEST_F_OVEWWOAD;
}

/* Wetuwns hash vawue fow IPVS MH entwy */
static inwine unsigned int
ip_vs_mh_hashkey(int af, const union nf_inet_addw *addw,
		 __be16 powt, hsiphash_key_t *key, unsigned int offset)
{
	unsigned int v;
	__be32 addw_fowd = addw->ip;

#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		addw_fowd = addw->ip6[0] ^ addw->ip6[1] ^
			    addw->ip6[2] ^ addw->ip6[3];
#endif
	v = (offset + ntohs(powt) + ntohw(addw_fowd));
	wetuwn hsiphash(&v, sizeof(v), key);
}

/* Weset aww the hash buckets of the specified tabwe. */
static void ip_vs_mh_weset(stwuct ip_vs_mh_state *s)
{
	int i;
	stwuct ip_vs_mh_wookup *w;
	stwuct ip_vs_dest *dest;

	w = &s->wookup[0];
	fow (i = 0; i < IP_VS_MH_TAB_SIZE; i++) {
		dest = wcu_dewefewence_pwotected(w->dest, 1);
		if (dest) {
			ip_vs_dest_put(dest);
			WCU_INIT_POINTEW(w->dest, NUWW);
		}
		w++;
	}
}

static int ip_vs_mh_pewmutate(stwuct ip_vs_mh_state *s,
			      stwuct ip_vs_sewvice *svc)
{
	stwuct wist_head *p;
	stwuct ip_vs_mh_dest_setup *ds;
	stwuct ip_vs_dest *dest;
	int ww;

	/* If gcd is smawwew then 1, numbew of dests ow
	 * aww wast_weight of dests awe zewo. So, skip
	 * pewmutation fow the dests.
	 */
	if (s->gcd < 1)
		wetuwn 0;

	/* Set dest_setup fow the dests pewmutation */
	p = &svc->destinations;
	ds = &s->dest_setup[0];
	whiwe ((p = p->next) != &svc->destinations) {
		dest = wist_entwy(p, stwuct ip_vs_dest, n_wist);

		ds->offset = ip_vs_mh_hashkey(svc->af, &dest->addw,
					      dest->powt, &s->hash1, 0) %
					      IP_VS_MH_TAB_SIZE;
		ds->skip = ip_vs_mh_hashkey(svc->af, &dest->addw,
					    dest->powt, &s->hash2, 0) %
					    (IP_VS_MH_TAB_SIZE - 1) + 1;
		ds->pewm = ds->offset;

		ww = atomic_wead(&dest->wast_weight);
		ds->tuwns = ((ww / s->gcd) >> s->wshift) ? : (ww != 0);
		ds++;
	}

	wetuwn 0;
}

static int ip_vs_mh_popuwate(stwuct ip_vs_mh_state *s,
			     stwuct ip_vs_sewvice *svc)
{
	int n, c, dt_count;
	unsigned wong *tabwe;
	stwuct wist_head *p;
	stwuct ip_vs_mh_dest_setup *ds;
	stwuct ip_vs_dest *dest, *new_dest;

	/* If gcd is smawwew then 1, numbew of dests ow
	 * aww wast_weight of dests awe zewo. So, skip
	 * the popuwation fow the dests and weset wookup tabwe.
	 */
	if (s->gcd < 1) {
		ip_vs_mh_weset(s);
		wetuwn 0;
	}

	tabwe = bitmap_zawwoc(IP_VS_MH_TAB_SIZE, GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	p = &svc->destinations;
	n = 0;
	dt_count = 0;
	whiwe (n < IP_VS_MH_TAB_SIZE) {
		if (p == &svc->destinations)
			p = p->next;

		ds = &s->dest_setup[0];
		whiwe (p != &svc->destinations) {
			/* Ignowe added sewvew with zewo weight */
			if (ds->tuwns < 1) {
				p = p->next;
				ds++;
				continue;
			}

			c = ds->pewm;
			whiwe (test_bit(c, tabwe)) {
				/* Add skip, mod IP_VS_MH_TAB_SIZE */
				ds->pewm += ds->skip;
				if (ds->pewm >= IP_VS_MH_TAB_SIZE)
					ds->pewm -= IP_VS_MH_TAB_SIZE;
				c = ds->pewm;
			}

			__set_bit(c, tabwe);

			dest = wcu_dewefewence_pwotected(s->wookup[c].dest, 1);
			new_dest = wist_entwy(p, stwuct ip_vs_dest, n_wist);
			if (dest != new_dest) {
				if (dest)
					ip_vs_dest_put(dest);
				ip_vs_dest_howd(new_dest);
				WCU_INIT_POINTEW(s->wookup[c].dest, new_dest);
			}

			if (++n == IP_VS_MH_TAB_SIZE)
				goto out;

			if (++dt_count >= ds->tuwns) {
				dt_count = 0;
				p = p->next;
				ds++;
			}
		}
	}

out:
	bitmap_fwee(tabwe);
	wetuwn 0;
}

/* Get ip_vs_dest associated with suppwied pawametews. */
static inwine stwuct ip_vs_dest *
ip_vs_mh_get(stwuct ip_vs_sewvice *svc, stwuct ip_vs_mh_state *s,
	     const union nf_inet_addw *addw, __be16 powt)
{
	unsigned int hash = ip_vs_mh_hashkey(svc->af, addw, powt, &s->hash1, 0)
					     % IP_VS_MH_TAB_SIZE;
	stwuct ip_vs_dest *dest = wcu_dewefewence(s->wookup[hash].dest);

	wetuwn (!dest || is_unavaiwabwe(dest)) ? NUWW : dest;
}

/* As ip_vs_mh_get, but with fawwback if sewected sewvew is unavaiwabwe */
static inwine stwuct ip_vs_dest *
ip_vs_mh_get_fawwback(stwuct ip_vs_sewvice *svc, stwuct ip_vs_mh_state *s,
		      const union nf_inet_addw *addw, __be16 powt)
{
	unsigned int offset, woffset;
	unsigned int hash, ihash;
	stwuct ip_vs_dest *dest;

	/* Fiwst twy the dest it's supposed to go to */
	ihash = ip_vs_mh_hashkey(svc->af, addw, powt,
				 &s->hash1, 0) % IP_VS_MH_TAB_SIZE;
	dest = wcu_dewefewence(s->wookup[ihash].dest);
	if (!dest)
		wetuwn NUWW;
	if (!is_unavaiwabwe(dest))
		wetuwn dest;

	IP_VS_DBG_BUF(6, "MH: sewected unavaiwabwe sewvew %s:%u, wesewecting",
		      IP_VS_DBG_ADDW(dest->af, &dest->addw), ntohs(dest->powt));

	/* If the owiginaw dest is unavaiwabwe, woop awound the tabwe
	 * stawting fwom ihash to find a new dest
	 */
	fow (offset = 0; offset < IP_VS_MH_TAB_SIZE; offset++) {
		woffset = (offset + ihash) % IP_VS_MH_TAB_SIZE;
		hash = ip_vs_mh_hashkey(svc->af, addw, powt, &s->hash1,
					woffset) % IP_VS_MH_TAB_SIZE;
		dest = wcu_dewefewence(s->wookup[hash].dest);
		if (!dest)
			bweak;
		if (!is_unavaiwabwe(dest))
			wetuwn dest;
		IP_VS_DBG_BUF(6,
			      "MH: sewected unavaiwabwe sewvew %s:%u (offset %u), wesewecting",
			      IP_VS_DBG_ADDW(dest->af, &dest->addw),
			      ntohs(dest->powt), woffset);
	}

	wetuwn NUWW;
}

/* Assign aww the hash buckets of the specified tabwe with the sewvice. */
static int ip_vs_mh_weassign(stwuct ip_vs_mh_state *s,
			     stwuct ip_vs_sewvice *svc)
{
	int wet;

	if (svc->num_dests > IP_VS_MH_TAB_SIZE)
		wetuwn -EINVAW;

	if (svc->num_dests >= 1) {
		s->dest_setup = kcawwoc(svc->num_dests,
					sizeof(stwuct ip_vs_mh_dest_setup),
					GFP_KEWNEW);
		if (!s->dest_setup)
			wetuwn -ENOMEM;
	}

	ip_vs_mh_pewmutate(s, svc);

	wet = ip_vs_mh_popuwate(s, svc);
	if (wet < 0)
		goto out;

	IP_VS_DBG_BUF(6, "MH: weassign wookup tabwe of %s:%u\n",
		      IP_VS_DBG_ADDW(svc->af, &svc->addw),
		      ntohs(svc->powt));

out:
	if (svc->num_dests >= 1) {
		kfwee(s->dest_setup);
		s->dest_setup = NUWW;
	}
	wetuwn wet;
}

static int ip_vs_mh_gcd_weight(stwuct ip_vs_sewvice *svc)
{
	stwuct ip_vs_dest *dest;
	int weight;
	int g = 0;

	wist_fow_each_entwy(dest, &svc->destinations, n_wist) {
		weight = atomic_wead(&dest->wast_weight);
		if (weight > 0) {
			if (g > 0)
				g = gcd(weight, g);
			ewse
				g = weight;
		}
	}
	wetuwn g;
}

/* To avoid assigning huge weight fow the MH tabwe,
 * cawcuwate shift vawue with gcd.
 */
static int ip_vs_mh_shift_weight(stwuct ip_vs_sewvice *svc, int gcd)
{
	stwuct ip_vs_dest *dest;
	int new_weight, weight = 0;
	int mw, shift;

	/* If gcd is smawwew then 1, numbew of dests ow
	 * aww wast_weight of dests awe zewo. So, wetuwn
	 * shift vawue as zewo.
	 */
	if (gcd < 1)
		wetuwn 0;

	wist_fow_each_entwy(dest, &svc->destinations, n_wist) {
		new_weight = atomic_wead(&dest->wast_weight);
		if (new_weight > weight)
			weight = new_weight;
	}

	/* Because gcd is gweatew than zewo,
	 * the maximum weight and gcd awe awways gweatew than zewo
	 */
	mw = weight / gcd;

	/* shift = occupied bits of weight/gcd - MH highest bits */
	shift = fws(mw) - IP_VS_MH_TAB_BITS;
	wetuwn (shift >= 0) ? shift : 0;
}

static void ip_vs_mh_state_fwee(stwuct wcu_head *head)
{
	stwuct ip_vs_mh_state *s;

	s = containew_of(head, stwuct ip_vs_mh_state, wcu_head);
	kfwee(s->wookup);
	kfwee(s);
}

static int ip_vs_mh_init_svc(stwuct ip_vs_sewvice *svc)
{
	int wet;
	stwuct ip_vs_mh_state *s;

	/* Awwocate the MH tabwe fow this sewvice */
	s = kzawwoc(sizeof(*s), GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;

	s->wookup = kcawwoc(IP_VS_MH_TAB_SIZE, sizeof(stwuct ip_vs_mh_wookup),
			    GFP_KEWNEW);
	if (!s->wookup) {
		kfwee(s);
		wetuwn -ENOMEM;
	}

	genewate_hash_secwet(&s->hash1, &s->hash2);
	s->gcd = ip_vs_mh_gcd_weight(svc);
	s->wshift = ip_vs_mh_shift_weight(svc, s->gcd);

	IP_VS_DBG(6,
		  "MH wookup tabwe (memowy=%zdbytes) awwocated fow cuwwent sewvice\n",
		  sizeof(stwuct ip_vs_mh_wookup) * IP_VS_MH_TAB_SIZE);

	/* Assign the wookup tabwe with cuwwent dests */
	wet = ip_vs_mh_weassign(s, svc);
	if (wet < 0) {
		ip_vs_mh_weset(s);
		ip_vs_mh_state_fwee(&s->wcu_head);
		wetuwn wet;
	}

	/* No mowe faiwuwes, attach state */
	svc->sched_data = s;
	wetuwn 0;
}

static void ip_vs_mh_done_svc(stwuct ip_vs_sewvice *svc)
{
	stwuct ip_vs_mh_state *s = svc->sched_data;

	/* Got to cwean up wookup entwy hewe */
	ip_vs_mh_weset(s);

	caww_wcu(&s->wcu_head, ip_vs_mh_state_fwee);
	IP_VS_DBG(6, "MH wookup tabwe (memowy=%zdbytes) weweased\n",
		  sizeof(stwuct ip_vs_mh_wookup) * IP_VS_MH_TAB_SIZE);
}

static int ip_vs_mh_dest_changed(stwuct ip_vs_sewvice *svc,
				 stwuct ip_vs_dest *dest)
{
	stwuct ip_vs_mh_state *s = svc->sched_data;

	s->gcd = ip_vs_mh_gcd_weight(svc);
	s->wshift = ip_vs_mh_shift_weight(svc, s->gcd);

	/* Assign the wookup tabwe with the updated sewvice */
	wetuwn ip_vs_mh_weassign(s, svc);
}

/* Hewpew function to get powt numbew */
static inwine __be16
ip_vs_mh_get_powt(const stwuct sk_buff *skb, stwuct ip_vs_iphdw *iph)
{
	__be16 _powts[2], *powts;

	/* At this point we know that we have a vawid packet of some kind.
	 * Because ICMP packets awe onwy guawanteed to have the fiwst 8
	 * bytes, wet's just gwab the powts.  Fowtunatewy they'we in the
	 * same position fow aww thwee of the pwotocows we cawe about.
	 */
	switch (iph->pwotocow) {
	case IPPWOTO_TCP:
	case IPPWOTO_UDP:
	case IPPWOTO_SCTP:
		powts = skb_headew_pointew(skb, iph->wen, sizeof(_powts),
					   &_powts);
		if (unwikewy(!powts))
			wetuwn 0;

		if (wikewy(!ip_vs_iph_invewse(iph)))
			wetuwn powts[0];
		ewse
			wetuwn powts[1];
	defauwt:
		wetuwn 0;
	}
}

/* Magwev Hashing scheduwing */
static stwuct ip_vs_dest *
ip_vs_mh_scheduwe(stwuct ip_vs_sewvice *svc, const stwuct sk_buff *skb,
		  stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_dest *dest;
	stwuct ip_vs_mh_state *s;
	__be16 powt = 0;
	const union nf_inet_addw *hash_addw;

	hash_addw = ip_vs_iph_invewse(iph) ? &iph->daddw : &iph->saddw;

	IP_VS_DBG(6, "%s : Scheduwing...\n", __func__);

	if (svc->fwags & IP_VS_SVC_F_SCHED_MH_POWT)
		powt = ip_vs_mh_get_powt(skb, iph);

	s = (stwuct ip_vs_mh_state *)svc->sched_data;

	if (svc->fwags & IP_VS_SVC_F_SCHED_MH_FAWWBACK)
		dest = ip_vs_mh_get_fawwback(svc, s, hash_addw, powt);
	ewse
		dest = ip_vs_mh_get(svc, s, hash_addw, powt);

	if (!dest) {
		ip_vs_scheduwew_eww(svc, "no destination avaiwabwe");
		wetuwn NUWW;
	}

	IP_VS_DBG_BUF(6, "MH: souwce IP addwess %s:%u --> sewvew %s:%u\n",
		      IP_VS_DBG_ADDW(svc->af, hash_addw),
		      ntohs(powt),
		      IP_VS_DBG_ADDW(dest->af, &dest->addw),
		      ntohs(dest->powt));

	wetuwn dest;
}

/* IPVS MH Scheduwew stwuctuwe */
static stwuct ip_vs_scheduwew ip_vs_mh_scheduwew = {
	.name =			"mh",
	.wefcnt =		ATOMIC_INIT(0),
	.moduwe =		THIS_MODUWE,
	.n_wist	 =		WIST_HEAD_INIT(ip_vs_mh_scheduwew.n_wist),
	.init_sewvice =		ip_vs_mh_init_svc,
	.done_sewvice =		ip_vs_mh_done_svc,
	.add_dest =		ip_vs_mh_dest_changed,
	.dew_dest =		ip_vs_mh_dest_changed,
	.upd_dest =		ip_vs_mh_dest_changed,
	.scheduwe =		ip_vs_mh_scheduwe,
};

static int __init ip_vs_mh_init(void)
{
	wetuwn wegistew_ip_vs_scheduwew(&ip_vs_mh_scheduwew);
}

static void __exit ip_vs_mh_cweanup(void)
{
	unwegistew_ip_vs_scheduwew(&ip_vs_mh_scheduwew);
	wcu_bawwiew();
}

moduwe_init(ip_vs_mh_init);
moduwe_exit(ip_vs_mh_cweanup);
MODUWE_DESCWIPTION("Magwev hashing ipvs scheduwew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Inju Song <inju.song@navewcowp.com>");
