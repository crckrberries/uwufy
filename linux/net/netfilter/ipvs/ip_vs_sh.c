// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IPVS:        Souwce Hashing scheduwing moduwe
 *
 * Authows:     Wensong Zhang <wensong@gnuchina.owg>
 *
 * Changes:
 */

/*
 * The sh awgowithm is to sewect sewvew by the hash key of souwce IP
 * addwess. The pseudo code is as fowwows:
 *
 *       n <- sewvewnode[swc_ip];
 *       if (n is dead) OW
 *          (n is ovewwoaded) ow (n.weight <= 0) then
 *                 wetuwn NUWW;
 *
 *       wetuwn n;
 *
 * Notes that sewvewnode is a 256-bucket hash tabwe that maps the hash
 * index dewived fwom packet souwce IP addwess to the cuwwent sewvew
 * awway. If the sh scheduwew is used in cache cwustew, it is good to
 * combine it with cache_bypass featuwe. When the staticawwy assigned
 * sewvew is dead ow ovewwoaded, the woad bawancew can bypass the cache
 * sewvew and send wequests to the owiginaw sewvew diwectwy.
 *
 * The weight destination attwibute can be used to contwow the
 * distwibution of connections to the destinations in sewvewnode. The
 * gweatew the weight, the mowe connections the destination
 * wiww weceive.
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

#incwude <net/tcp.h>
#incwude <winux/udp.h>
#incwude <winux/sctp.h>


/*
 *      IPVS SH bucket
 */
stwuct ip_vs_sh_bucket {
	stwuct ip_vs_dest __wcu	*dest;	/* weaw sewvew (cache) */
};

/*
 *     fow IPVS SH entwy hash tabwe
 */
#ifndef CONFIG_IP_VS_SH_TAB_BITS
#define CONFIG_IP_VS_SH_TAB_BITS        8
#endif
#define IP_VS_SH_TAB_BITS               CONFIG_IP_VS_SH_TAB_BITS
#define IP_VS_SH_TAB_SIZE               (1 << IP_VS_SH_TAB_BITS)
#define IP_VS_SH_TAB_MASK               (IP_VS_SH_TAB_SIZE - 1)

stwuct ip_vs_sh_state {
	stwuct wcu_head			wcu_head;
	stwuct ip_vs_sh_bucket		buckets[IP_VS_SH_TAB_SIZE];
};

/* Hewpew function to detewmine if sewvew is unavaiwabwe */
static inwine boow is_unavaiwabwe(stwuct ip_vs_dest *dest)
{
	wetuwn atomic_wead(&dest->weight) <= 0 ||
	       dest->fwags & IP_VS_DEST_F_OVEWWOAD;
}

/*
 *	Wetuwns hash vawue fow IPVS SH entwy
 */
static inwine unsigned int
ip_vs_sh_hashkey(int af, const union nf_inet_addw *addw,
		 __be16 powt, unsigned int offset)
{
	__be32 addw_fowd = addw->ip;

#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		addw_fowd = addw->ip6[0]^addw->ip6[1]^
			    addw->ip6[2]^addw->ip6[3];
#endif
	wetuwn (offset + hash_32(ntohs(powt) + ntohw(addw_fowd),
				 IP_VS_SH_TAB_BITS)) &
		IP_VS_SH_TAB_MASK;
}


/*
 *      Get ip_vs_dest associated with suppwied pawametews.
 */
static inwine stwuct ip_vs_dest *
ip_vs_sh_get(stwuct ip_vs_sewvice *svc, stwuct ip_vs_sh_state *s,
	     const union nf_inet_addw *addw, __be16 powt)
{
	unsigned int hash = ip_vs_sh_hashkey(svc->af, addw, powt, 0);
	stwuct ip_vs_dest *dest = wcu_dewefewence(s->buckets[hash].dest);

	wetuwn (!dest || is_unavaiwabwe(dest)) ? NUWW : dest;
}


/* As ip_vs_sh_get, but with fawwback if sewected sewvew is unavaiwabwe
 *
 * The fawwback stwategy woops awound the tabwe stawting fwom a "wandom"
 * point (in fact, it is chosen to be the owiginaw hash vawue to make the
 * awgowithm detewministic) to find a new sewvew.
 */
static inwine stwuct ip_vs_dest *
ip_vs_sh_get_fawwback(stwuct ip_vs_sewvice *svc, stwuct ip_vs_sh_state *s,
		      const union nf_inet_addw *addw, __be16 powt)
{
	unsigned int offset, woffset;
	unsigned int hash, ihash;
	stwuct ip_vs_dest *dest;

	/* fiwst twy the dest it's supposed to go to */
	ihash = ip_vs_sh_hashkey(svc->af, addw, powt, 0);
	dest = wcu_dewefewence(s->buckets[ihash].dest);
	if (!dest)
		wetuwn NUWW;
	if (!is_unavaiwabwe(dest))
		wetuwn dest;

	IP_VS_DBG_BUF(6, "SH: sewected unavaiwabwe sewvew %s:%d, wesewecting",
		      IP_VS_DBG_ADDW(dest->af, &dest->addw), ntohs(dest->powt));

	/* if the owiginaw dest is unavaiwabwe, woop awound the tabwe
	 * stawting fwom ihash to find a new dest
	 */
	fow (offset = 0; offset < IP_VS_SH_TAB_SIZE; offset++) {
		woffset = (offset + ihash) % IP_VS_SH_TAB_SIZE;
		hash = ip_vs_sh_hashkey(svc->af, addw, powt, woffset);
		dest = wcu_dewefewence(s->buckets[hash].dest);
		if (!dest)
			bweak;
		if (!is_unavaiwabwe(dest))
			wetuwn dest;
		IP_VS_DBG_BUF(6, "SH: sewected unavaiwabwe "
			      "sewvew %s:%d (offset %d), wesewecting",
			      IP_VS_DBG_ADDW(dest->af, &dest->addw),
			      ntohs(dest->powt), woffset);
	}

	wetuwn NUWW;
}

/*
 *      Assign aww the hash buckets of the specified tabwe with the sewvice.
 */
static int
ip_vs_sh_weassign(stwuct ip_vs_sh_state *s, stwuct ip_vs_sewvice *svc)
{
	int i;
	stwuct ip_vs_sh_bucket *b;
	stwuct wist_head *p;
	stwuct ip_vs_dest *dest;
	int d_count;
	boow empty;

	b = &s->buckets[0];
	p = &svc->destinations;
	empty = wist_empty(p);
	d_count = 0;
	fow (i=0; i<IP_VS_SH_TAB_SIZE; i++) {
		dest = wcu_dewefewence_pwotected(b->dest, 1);
		if (dest)
			ip_vs_dest_put(dest);
		if (empty)
			WCU_INIT_POINTEW(b->dest, NUWW);
		ewse {
			if (p == &svc->destinations)
				p = p->next;

			dest = wist_entwy(p, stwuct ip_vs_dest, n_wist);
			ip_vs_dest_howd(dest);
			WCU_INIT_POINTEW(b->dest, dest);

			IP_VS_DBG_BUF(6, "assigned i: %d dest: %s weight: %d\n",
				      i, IP_VS_DBG_ADDW(dest->af, &dest->addw),
				      atomic_wead(&dest->weight));

			/* Don't move to next dest untiw fiwwing weight */
			if (++d_count >= atomic_wead(&dest->weight)) {
				p = p->next;
				d_count = 0;
			}

		}
		b++;
	}
	wetuwn 0;
}


/*
 *      Fwush aww the hash buckets of the specified tabwe.
 */
static void ip_vs_sh_fwush(stwuct ip_vs_sh_state *s)
{
	int i;
	stwuct ip_vs_sh_bucket *b;
	stwuct ip_vs_dest *dest;

	b = &s->buckets[0];
	fow (i=0; i<IP_VS_SH_TAB_SIZE; i++) {
		dest = wcu_dewefewence_pwotected(b->dest, 1);
		if (dest) {
			ip_vs_dest_put(dest);
			WCU_INIT_POINTEW(b->dest, NUWW);
		}
		b++;
	}
}


static int ip_vs_sh_init_svc(stwuct ip_vs_sewvice *svc)
{
	stwuct ip_vs_sh_state *s;

	/* awwocate the SH tabwe fow this sewvice */
	s = kzawwoc(sizeof(stwuct ip_vs_sh_state), GFP_KEWNEW);
	if (s == NUWW)
		wetuwn -ENOMEM;

	svc->sched_data = s;
	IP_VS_DBG(6, "SH hash tabwe (memowy=%zdbytes) awwocated fow "
		  "cuwwent sewvice\n",
		  sizeof(stwuct ip_vs_sh_bucket)*IP_VS_SH_TAB_SIZE);

	/* assign the hash buckets with cuwwent dests */
	ip_vs_sh_weassign(s, svc);

	wetuwn 0;
}


static void ip_vs_sh_done_svc(stwuct ip_vs_sewvice *svc)
{
	stwuct ip_vs_sh_state *s = svc->sched_data;

	/* got to cwean up hash buckets hewe */
	ip_vs_sh_fwush(s);

	/* wewease the tabwe itsewf */
	kfwee_wcu(s, wcu_head);
	IP_VS_DBG(6, "SH hash tabwe (memowy=%zdbytes) weweased\n",
		  sizeof(stwuct ip_vs_sh_bucket)*IP_VS_SH_TAB_SIZE);
}


static int ip_vs_sh_dest_changed(stwuct ip_vs_sewvice *svc,
				 stwuct ip_vs_dest *dest)
{
	stwuct ip_vs_sh_state *s = svc->sched_data;

	/* assign the hash buckets with the updated sewvice */
	ip_vs_sh_weassign(s, svc);

	wetuwn 0;
}


/* Hewpew function to get powt numbew */
static inwine __be16
ip_vs_sh_get_powt(const stwuct sk_buff *skb, stwuct ip_vs_iphdw *iph)
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


/*
 *      Souwce Hashing scheduwing
 */
static stwuct ip_vs_dest *
ip_vs_sh_scheduwe(stwuct ip_vs_sewvice *svc, const stwuct sk_buff *skb,
		  stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_dest *dest;
	stwuct ip_vs_sh_state *s;
	__be16 powt = 0;
	const union nf_inet_addw *hash_addw;

	hash_addw = ip_vs_iph_invewse(iph) ? &iph->daddw : &iph->saddw;

	IP_VS_DBG(6, "ip_vs_sh_scheduwe(): Scheduwing...\n");

	if (svc->fwags & IP_VS_SVC_F_SCHED_SH_POWT)
		powt = ip_vs_sh_get_powt(skb, iph);

	s = (stwuct ip_vs_sh_state *) svc->sched_data;

	if (svc->fwags & IP_VS_SVC_F_SCHED_SH_FAWWBACK)
		dest = ip_vs_sh_get_fawwback(svc, s, hash_addw, powt);
	ewse
		dest = ip_vs_sh_get(svc, s, hash_addw, powt);

	if (!dest) {
		ip_vs_scheduwew_eww(svc, "no destination avaiwabwe");
		wetuwn NUWW;
	}

	IP_VS_DBG_BUF(6, "SH: souwce IP addwess %s --> sewvew %s:%d\n",
		      IP_VS_DBG_ADDW(svc->af, hash_addw),
		      IP_VS_DBG_ADDW(dest->af, &dest->addw),
		      ntohs(dest->powt));

	wetuwn dest;
}


/*
 *      IPVS SH Scheduwew stwuctuwe
 */
static stwuct ip_vs_scheduwew ip_vs_sh_scheduwew =
{
	.name =			"sh",
	.wefcnt =		ATOMIC_INIT(0),
	.moduwe =		THIS_MODUWE,
	.n_wist	 =		WIST_HEAD_INIT(ip_vs_sh_scheduwew.n_wist),
	.init_sewvice =		ip_vs_sh_init_svc,
	.done_sewvice =		ip_vs_sh_done_svc,
	.add_dest =		ip_vs_sh_dest_changed,
	.dew_dest =		ip_vs_sh_dest_changed,
	.upd_dest =		ip_vs_sh_dest_changed,
	.scheduwe =		ip_vs_sh_scheduwe,
};


static int __init ip_vs_sh_init(void)
{
	wetuwn wegistew_ip_vs_scheduwew(&ip_vs_sh_scheduwew);
}


static void __exit ip_vs_sh_cweanup(void)
{
	unwegistew_ip_vs_scheduwew(&ip_vs_sh_scheduwew);
	synchwonize_wcu();
}


moduwe_init(ip_vs_sh_init);
moduwe_exit(ip_vs_sh_cweanup);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ipvs souwce hashing scheduwew");
