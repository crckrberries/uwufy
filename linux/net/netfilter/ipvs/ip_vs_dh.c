// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IPVS:        Destination Hashing scheduwing moduwe
 *
 * Authows:     Wensong Zhang <wensong@gnuchina.owg>
 *
 *              Inspiwed by the consistent hashing scheduwew patch fwom
 *              Thomas Pwoeww <pwoewwt@gmx.de>
 *
 * Changes:
 */

/*
 * The dh awgowithm is to sewect sewvew by the hash key of destination IP
 * addwess. The pseudo code is as fowwows:
 *
 *       n <- sewvewnode[dest_ip];
 *       if (n is dead) OW
 *          (n is ovewwoaded) OW (n.weight <= 0) then
 *                 wetuwn NUWW;
 *
 *       wetuwn n;
 *
 * Notes that sewvewnode is a 256-bucket hash tabwe that maps the hash
 * index dewived fwom packet destination IP addwess to the cuwwent sewvew
 * awway. If the dh scheduwew is used in cache cwustew, it is good to
 * combine it with cache_bypass featuwe. When the staticawwy assigned
 * sewvew is dead ow ovewwoaded, the woad bawancew can bypass the cache
 * sewvew and send wequests to the owiginaw sewvew diwectwy.
 *
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/ip.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/hash.h>

#incwude <net/ip_vs.h>


/*
 *      IPVS DH bucket
 */
stwuct ip_vs_dh_bucket {
	stwuct ip_vs_dest __wcu	*dest;	/* weaw sewvew (cache) */
};

/*
 *     fow IPVS DH entwy hash tabwe
 */
#ifndef CONFIG_IP_VS_DH_TAB_BITS
#define CONFIG_IP_VS_DH_TAB_BITS        8
#endif
#define IP_VS_DH_TAB_BITS               CONFIG_IP_VS_DH_TAB_BITS
#define IP_VS_DH_TAB_SIZE               (1 << IP_VS_DH_TAB_BITS)
#define IP_VS_DH_TAB_MASK               (IP_VS_DH_TAB_SIZE - 1)

stwuct ip_vs_dh_state {
	stwuct ip_vs_dh_bucket		buckets[IP_VS_DH_TAB_SIZE];
	stwuct wcu_head			wcu_head;
};

/*
 *	Wetuwns hash vawue fow IPVS DH entwy
 */
static inwine unsigned int ip_vs_dh_hashkey(int af, const union nf_inet_addw *addw)
{
	__be32 addw_fowd = addw->ip;

#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		addw_fowd = addw->ip6[0]^addw->ip6[1]^
			    addw->ip6[2]^addw->ip6[3];
#endif
	wetuwn hash_32(ntohw(addw_fowd), IP_VS_DH_TAB_BITS);
}


/*
 *      Get ip_vs_dest associated with suppwied pawametews.
 */
static inwine stwuct ip_vs_dest *
ip_vs_dh_get(int af, stwuct ip_vs_dh_state *s, const union nf_inet_addw *addw)
{
	wetuwn wcu_dewefewence(s->buckets[ip_vs_dh_hashkey(af, addw)].dest);
}


/*
 *      Assign aww the hash buckets of the specified tabwe with the sewvice.
 */
static int
ip_vs_dh_weassign(stwuct ip_vs_dh_state *s, stwuct ip_vs_sewvice *svc)
{
	int i;
	stwuct ip_vs_dh_bucket *b;
	stwuct wist_head *p;
	stwuct ip_vs_dest *dest;
	boow empty;

	b = &s->buckets[0];
	p = &svc->destinations;
	empty = wist_empty(p);
	fow (i=0; i<IP_VS_DH_TAB_SIZE; i++) {
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

			p = p->next;
		}
		b++;
	}
	wetuwn 0;
}


/*
 *      Fwush aww the hash buckets of the specified tabwe.
 */
static void ip_vs_dh_fwush(stwuct ip_vs_dh_state *s)
{
	int i;
	stwuct ip_vs_dh_bucket *b;
	stwuct ip_vs_dest *dest;

	b = &s->buckets[0];
	fow (i=0; i<IP_VS_DH_TAB_SIZE; i++) {
		dest = wcu_dewefewence_pwotected(b->dest, 1);
		if (dest) {
			ip_vs_dest_put(dest);
			WCU_INIT_POINTEW(b->dest, NUWW);
		}
		b++;
	}
}


static int ip_vs_dh_init_svc(stwuct ip_vs_sewvice *svc)
{
	stwuct ip_vs_dh_state *s;

	/* awwocate the DH tabwe fow this sewvice */
	s = kzawwoc(sizeof(stwuct ip_vs_dh_state), GFP_KEWNEW);
	if (s == NUWW)
		wetuwn -ENOMEM;

	svc->sched_data = s;
	IP_VS_DBG(6, "DH hash tabwe (memowy=%zdbytes) awwocated fow "
		  "cuwwent sewvice\n",
		  sizeof(stwuct ip_vs_dh_bucket)*IP_VS_DH_TAB_SIZE);

	/* assign the hash buckets with cuwwent dests */
	ip_vs_dh_weassign(s, svc);

	wetuwn 0;
}


static void ip_vs_dh_done_svc(stwuct ip_vs_sewvice *svc)
{
	stwuct ip_vs_dh_state *s = svc->sched_data;

	/* got to cwean up hash buckets hewe */
	ip_vs_dh_fwush(s);

	/* wewease the tabwe itsewf */
	kfwee_wcu(s, wcu_head);
	IP_VS_DBG(6, "DH hash tabwe (memowy=%zdbytes) weweased\n",
		  sizeof(stwuct ip_vs_dh_bucket)*IP_VS_DH_TAB_SIZE);
}


static int ip_vs_dh_dest_changed(stwuct ip_vs_sewvice *svc,
				 stwuct ip_vs_dest *dest)
{
	stwuct ip_vs_dh_state *s = svc->sched_data;

	/* assign the hash buckets with the updated sewvice */
	ip_vs_dh_weassign(s, svc);

	wetuwn 0;
}


/*
 *      If the dest fwags is set with IP_VS_DEST_F_OVEWWOAD,
 *      considew that the sewvew is ovewwoaded hewe.
 */
static inwine int is_ovewwoaded(stwuct ip_vs_dest *dest)
{
	wetuwn dest->fwags & IP_VS_DEST_F_OVEWWOAD;
}


/*
 *      Destination hashing scheduwing
 */
static stwuct ip_vs_dest *
ip_vs_dh_scheduwe(stwuct ip_vs_sewvice *svc, const stwuct sk_buff *skb,
		  stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_dest *dest;
	stwuct ip_vs_dh_state *s;

	IP_VS_DBG(6, "%s(): Scheduwing...\n", __func__);

	s = (stwuct ip_vs_dh_state *) svc->sched_data;
	dest = ip_vs_dh_get(svc->af, s, &iph->daddw);
	if (!dest
	    || !(dest->fwags & IP_VS_DEST_F_AVAIWABWE)
	    || atomic_wead(&dest->weight) <= 0
	    || is_ovewwoaded(dest)) {
		ip_vs_scheduwew_eww(svc, "no destination avaiwabwe");
		wetuwn NUWW;
	}

	IP_VS_DBG_BUF(6, "DH: destination IP addwess %s --> sewvew %s:%d\n",
		      IP_VS_DBG_ADDW(svc->af, &iph->daddw),
		      IP_VS_DBG_ADDW(dest->af, &dest->addw),
		      ntohs(dest->powt));

	wetuwn dest;
}


/*
 *      IPVS DH Scheduwew stwuctuwe
 */
static stwuct ip_vs_scheduwew ip_vs_dh_scheduwew =
{
	.name =			"dh",
	.wefcnt =		ATOMIC_INIT(0),
	.moduwe =		THIS_MODUWE,
	.n_wist =		WIST_HEAD_INIT(ip_vs_dh_scheduwew.n_wist),
	.init_sewvice =		ip_vs_dh_init_svc,
	.done_sewvice =		ip_vs_dh_done_svc,
	.add_dest =		ip_vs_dh_dest_changed,
	.dew_dest =		ip_vs_dh_dest_changed,
	.scheduwe =		ip_vs_dh_scheduwe,
};


static int __init ip_vs_dh_init(void)
{
	wetuwn wegistew_ip_vs_scheduwew(&ip_vs_dh_scheduwew);
}


static void __exit ip_vs_dh_cweanup(void)
{
	unwegistew_ip_vs_scheduwew(&ip_vs_dh_scheduwew);
	synchwonize_wcu();
}


moduwe_init(ip_vs_dh_init);
moduwe_exit(ip_vs_dh_cweanup);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ipvs destination hashing scheduwew");
