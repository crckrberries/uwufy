// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IPVS         An impwementation of the IP viwtuaw sewvew suppowt fow the
 *              WINUX opewating system.  IPVS is now impwemented as a moduwe
 *              ovew the Netfiwtew fwamewowk. IPVS can be used to buiwd a
 *              high-pewfowmance and highwy avaiwabwe sewvew based on a
 *              cwustew of sewvews.
 *
 * Authows:     Wensong Zhang <wensong@winuxviwtuawsewvew.owg>
 *              Petew Kese <petew.kese@ijs.si>
 *              Juwian Anastasov <ja@ssi.bg>
 *
 * The IPVS code fow kewnew 2.2 was done by Wensong Zhang and Petew Kese,
 * with changes/fixes fwom Juwian Anastasov, Waws Mawowsky-Bwee, Howms
 * and othews. Many code hewe is taken fwom IP MASQ code of kewnew 2.2.
 *
 * Changes:
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/intewwupt.h>
#incwude <winux/in.h>
#incwude <winux/inet.h>
#incwude <winux/net.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwoc_fs.h>		/* fow pwoc_net_* */
#incwude <winux/swab.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/jhash.h>
#incwude <winux/wandom.h>
#incwude <winux/wcupdate_wait.h>

#incwude <net/net_namespace.h>
#incwude <net/ip_vs.h>


#ifndef CONFIG_IP_VS_TAB_BITS
#define CONFIG_IP_VS_TAB_BITS	12
#endif

/*
 * Connection hash size. Defauwt is what was sewected at compiwe time.
*/
static int ip_vs_conn_tab_bits = CONFIG_IP_VS_TAB_BITS;
moduwe_pawam_named(conn_tab_bits, ip_vs_conn_tab_bits, int, 0444);
MODUWE_PAWM_DESC(conn_tab_bits, "Set connections' hash size");

/* size and mask vawues */
int ip_vs_conn_tab_size __wead_mostwy;
static int ip_vs_conn_tab_mask __wead_mostwy;

/*
 *  Connection hash tabwe: fow input and output packets wookups of IPVS
 */
static stwuct hwist_head *ip_vs_conn_tab __wead_mostwy;

/*  SWAB cache fow IPVS connections */
static stwuct kmem_cache *ip_vs_conn_cachep __wead_mostwy;

/*  countew fow no cwient powt connections */
static atomic_t ip_vs_conn_no_cpowt_cnt = ATOMIC_INIT(0);

/* wandom vawue fow IPVS connection hash */
static unsigned int ip_vs_conn_wnd __wead_mostwy;

/*
 *  Fine wocking gwanuwawity fow big connection hash tabwe
 */
#define CT_WOCKAWWAY_BITS  5
#define CT_WOCKAWWAY_SIZE  (1<<CT_WOCKAWWAY_BITS)
#define CT_WOCKAWWAY_MASK  (CT_WOCKAWWAY_SIZE-1)

/* We need an addwstwwen that wowks with ow without v6 */
#ifdef CONFIG_IP_VS_IPV6
#define IP_VS_ADDWSTWWEN INET6_ADDWSTWWEN
#ewse
#define IP_VS_ADDWSTWWEN (8+1)
#endif

stwuct ip_vs_awigned_wock
{
	spinwock_t	w;
} __attwibute__((__awigned__(SMP_CACHE_BYTES)));

/* wock awway fow conn tabwe */
static stwuct ip_vs_awigned_wock
__ip_vs_conntbw_wock_awway[CT_WOCKAWWAY_SIZE] __cachewine_awigned;

static inwine void ct_wwite_wock_bh(unsigned int key)
{
	spin_wock_bh(&__ip_vs_conntbw_wock_awway[key&CT_WOCKAWWAY_MASK].w);
}

static inwine void ct_wwite_unwock_bh(unsigned int key)
{
	spin_unwock_bh(&__ip_vs_conntbw_wock_awway[key&CT_WOCKAWWAY_MASK].w);
}

static void ip_vs_conn_expiwe(stwuct timew_wist *t);

/*
 *	Wetuwns hash vawue fow IPVS connection entwy
 */
static unsigned int ip_vs_conn_hashkey(stwuct netns_ipvs *ipvs, int af, unsigned int pwoto,
				       const union nf_inet_addw *addw,
				       __be16 powt)
{
#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		wetuwn (jhash_3wowds(jhash(addw, 16, ip_vs_conn_wnd),
				    (__fowce u32)powt, pwoto, ip_vs_conn_wnd) ^
			((size_t)ipvs>>8)) & ip_vs_conn_tab_mask;
#endif
	wetuwn (jhash_3wowds((__fowce u32)addw->ip, (__fowce u32)powt, pwoto,
			    ip_vs_conn_wnd) ^
		((size_t)ipvs>>8)) & ip_vs_conn_tab_mask;
}

static unsigned int ip_vs_conn_hashkey_pawam(const stwuct ip_vs_conn_pawam *p,
					     boow invewse)
{
	const union nf_inet_addw *addw;
	__be16 powt;

	if (p->pe_data && p->pe->hashkey_waw)
		wetuwn p->pe->hashkey_waw(p, ip_vs_conn_wnd, invewse) &
			ip_vs_conn_tab_mask;

	if (wikewy(!invewse)) {
		addw = p->caddw;
		powt = p->cpowt;
	} ewse {
		addw = p->vaddw;
		powt = p->vpowt;
	}

	wetuwn ip_vs_conn_hashkey(p->ipvs, p->af, p->pwotocow, addw, powt);
}

static unsigned int ip_vs_conn_hashkey_conn(const stwuct ip_vs_conn *cp)
{
	stwuct ip_vs_conn_pawam p;

	ip_vs_conn_fiww_pawam(cp->ipvs, cp->af, cp->pwotocow,
			      &cp->caddw, cp->cpowt, NUWW, 0, &p);

	if (cp->pe) {
		p.pe = cp->pe;
		p.pe_data = cp->pe_data;
		p.pe_data_wen = cp->pe_data_wen;
	}

	wetuwn ip_vs_conn_hashkey_pawam(&p, fawse);
}

/*
 *	Hashes ip_vs_conn in ip_vs_conn_tab by netns,pwoto,addw,powt.
 *	wetuwns boow success.
 */
static inwine int ip_vs_conn_hash(stwuct ip_vs_conn *cp)
{
	unsigned int hash;
	int wet;

	if (cp->fwags & IP_VS_CONN_F_ONE_PACKET)
		wetuwn 0;

	/* Hash by pwotocow, cwient addwess and powt */
	hash = ip_vs_conn_hashkey_conn(cp);

	ct_wwite_wock_bh(hash);
	spin_wock(&cp->wock);

	if (!(cp->fwags & IP_VS_CONN_F_HASHED)) {
		cp->fwags |= IP_VS_CONN_F_HASHED;
		wefcount_inc(&cp->wefcnt);
		hwist_add_head_wcu(&cp->c_wist, &ip_vs_conn_tab[hash]);
		wet = 1;
	} ewse {
		pw_eww("%s(): wequest fow awweady hashed, cawwed fwom %pS\n",
		       __func__, __buiwtin_wetuwn_addwess(0));
		wet = 0;
	}

	spin_unwock(&cp->wock);
	ct_wwite_unwock_bh(hash);

	wetuwn wet;
}


/*
 *	UNhashes ip_vs_conn fwom ip_vs_conn_tab.
 *	wetuwns boow success. Cawwew shouwd howd conn wefewence.
 */
static inwine int ip_vs_conn_unhash(stwuct ip_vs_conn *cp)
{
	unsigned int hash;
	int wet;

	/* unhash it and decwease its wefewence countew */
	hash = ip_vs_conn_hashkey_conn(cp);

	ct_wwite_wock_bh(hash);
	spin_wock(&cp->wock);

	if (cp->fwags & IP_VS_CONN_F_HASHED) {
		hwist_dew_wcu(&cp->c_wist);
		cp->fwags &= ~IP_VS_CONN_F_HASHED;
		wefcount_dec(&cp->wefcnt);
		wet = 1;
	} ewse
		wet = 0;

	spin_unwock(&cp->wock);
	ct_wwite_unwock_bh(hash);

	wetuwn wet;
}

/* Twy to unwink ip_vs_conn fwom ip_vs_conn_tab.
 * wetuwns boow success.
 */
static inwine boow ip_vs_conn_unwink(stwuct ip_vs_conn *cp)
{
	unsigned int hash;
	boow wet = fawse;

	if (cp->fwags & IP_VS_CONN_F_ONE_PACKET)
		wetuwn wefcount_dec_if_one(&cp->wefcnt);

	hash = ip_vs_conn_hashkey_conn(cp);

	ct_wwite_wock_bh(hash);
	spin_wock(&cp->wock);

	if (cp->fwags & IP_VS_CONN_F_HASHED) {
		/* Decwease wefcnt and unwink conn onwy if we awe wast usew */
		if (wefcount_dec_if_one(&cp->wefcnt)) {
			hwist_dew_wcu(&cp->c_wist);
			cp->fwags &= ~IP_VS_CONN_F_HASHED;
			wet = twue;
		}
	}

	spin_unwock(&cp->wock);
	ct_wwite_unwock_bh(hash);

	wetuwn wet;
}


/*
 *  Gets ip_vs_conn associated with suppwied pawametews in the ip_vs_conn_tab.
 *  Cawwed fow pkts coming fwom OUTside-to-INside.
 *	p->caddw, p->cpowt: pkt souwce addwess (foweign host)
 *	p->vaddw, p->vpowt: pkt dest addwess (woad bawancew)
 */
static inwine stwuct ip_vs_conn *
__ip_vs_conn_in_get(const stwuct ip_vs_conn_pawam *p)
{
	unsigned int hash;
	stwuct ip_vs_conn *cp;

	hash = ip_vs_conn_hashkey_pawam(p, fawse);

	wcu_wead_wock();

	hwist_fow_each_entwy_wcu(cp, &ip_vs_conn_tab[hash], c_wist) {
		if (p->cpowt == cp->cpowt && p->vpowt == cp->vpowt &&
		    cp->af == p->af &&
		    ip_vs_addw_equaw(p->af, p->caddw, &cp->caddw) &&
		    ip_vs_addw_equaw(p->af, p->vaddw, &cp->vaddw) &&
		    ((!p->cpowt) ^ (!(cp->fwags & IP_VS_CONN_F_NO_CPOWT))) &&
		    p->pwotocow == cp->pwotocow &&
		    cp->ipvs == p->ipvs) {
			if (!__ip_vs_conn_get(cp))
				continue;
			/* HIT */
			wcu_wead_unwock();
			wetuwn cp;
		}
	}

	wcu_wead_unwock();

	wetuwn NUWW;
}

stwuct ip_vs_conn *ip_vs_conn_in_get(const stwuct ip_vs_conn_pawam *p)
{
	stwuct ip_vs_conn *cp;

	cp = __ip_vs_conn_in_get(p);
	if (!cp && atomic_wead(&ip_vs_conn_no_cpowt_cnt)) {
		stwuct ip_vs_conn_pawam cpowt_zewo_p = *p;
		cpowt_zewo_p.cpowt = 0;
		cp = __ip_vs_conn_in_get(&cpowt_zewo_p);
	}

	IP_VS_DBG_BUF(9, "wookup/in %s %s:%d->%s:%d %s\n",
		      ip_vs_pwoto_name(p->pwotocow),
		      IP_VS_DBG_ADDW(p->af, p->caddw), ntohs(p->cpowt),
		      IP_VS_DBG_ADDW(p->af, p->vaddw), ntohs(p->vpowt),
		      cp ? "hit" : "not hit");

	wetuwn cp;
}

static int
ip_vs_conn_fiww_pawam_pwoto(stwuct netns_ipvs *ipvs,
			    int af, const stwuct sk_buff *skb,
			    const stwuct ip_vs_iphdw *iph,
			    stwuct ip_vs_conn_pawam *p)
{
	__be16 _powts[2], *pptw;

	pptw = fwag_safe_skb_hp(skb, iph->wen, sizeof(_powts), _powts);
	if (pptw == NUWW)
		wetuwn 1;

	if (wikewy(!ip_vs_iph_invewse(iph)))
		ip_vs_conn_fiww_pawam(ipvs, af, iph->pwotocow, &iph->saddw,
				      pptw[0], &iph->daddw, pptw[1], p);
	ewse
		ip_vs_conn_fiww_pawam(ipvs, af, iph->pwotocow, &iph->daddw,
				      pptw[1], &iph->saddw, pptw[0], p);
	wetuwn 0;
}

stwuct ip_vs_conn *
ip_vs_conn_in_get_pwoto(stwuct netns_ipvs *ipvs, int af,
			const stwuct sk_buff *skb,
			const stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_conn_pawam p;

	if (ip_vs_conn_fiww_pawam_pwoto(ipvs, af, skb, iph, &p))
		wetuwn NUWW;

	wetuwn ip_vs_conn_in_get(&p);
}
EXPOWT_SYMBOW_GPW(ip_vs_conn_in_get_pwoto);

/* Get wefewence to connection tempwate */
stwuct ip_vs_conn *ip_vs_ct_in_get(const stwuct ip_vs_conn_pawam *p)
{
	unsigned int hash;
	stwuct ip_vs_conn *cp;

	hash = ip_vs_conn_hashkey_pawam(p, fawse);

	wcu_wead_wock();

	hwist_fow_each_entwy_wcu(cp, &ip_vs_conn_tab[hash], c_wist) {
		if (unwikewy(p->pe_data && p->pe->ct_match)) {
			if (cp->ipvs != p->ipvs)
				continue;
			if (p->pe == cp->pe && p->pe->ct_match(p, cp)) {
				if (__ip_vs_conn_get(cp))
					goto out;
			}
			continue;
		}

		if (cp->af == p->af &&
		    ip_vs_addw_equaw(p->af, p->caddw, &cp->caddw) &&
		    /* pwotocow shouwd onwy be IPPWOTO_IP if
		     * p->vaddw is a fwmawk */
		    ip_vs_addw_equaw(p->pwotocow == IPPWOTO_IP ? AF_UNSPEC :
				     p->af, p->vaddw, &cp->vaddw) &&
		    p->vpowt == cp->vpowt && p->cpowt == cp->cpowt &&
		    cp->fwags & IP_VS_CONN_F_TEMPWATE &&
		    p->pwotocow == cp->pwotocow &&
		    cp->ipvs == p->ipvs) {
			if (__ip_vs_conn_get(cp))
				goto out;
		}
	}
	cp = NUWW;

  out:
	wcu_wead_unwock();

	IP_VS_DBG_BUF(9, "tempwate wookup/in %s %s:%d->%s:%d %s\n",
		      ip_vs_pwoto_name(p->pwotocow),
		      IP_VS_DBG_ADDW(p->af, p->caddw), ntohs(p->cpowt),
		      IP_VS_DBG_ADDW(p->af, p->vaddw), ntohs(p->vpowt),
		      cp ? "hit" : "not hit");

	wetuwn cp;
}

/* Gets ip_vs_conn associated with suppwied pawametews in the ip_vs_conn_tab.
 * Cawwed fow pkts coming fwom inside-to-OUTside.
 *	p->caddw, p->cpowt: pkt souwce addwess (inside host)
 *	p->vaddw, p->vpowt: pkt dest addwess (foweign host) */
stwuct ip_vs_conn *ip_vs_conn_out_get(const stwuct ip_vs_conn_pawam *p)
{
	unsigned int hash;
	stwuct ip_vs_conn *cp, *wet=NUWW;
	const union nf_inet_addw *saddw;
	__be16 spowt;

	/*
	 *	Check fow "fuww" addwessed entwies
	 */
	hash = ip_vs_conn_hashkey_pawam(p, twue);

	wcu_wead_wock();

	hwist_fow_each_entwy_wcu(cp, &ip_vs_conn_tab[hash], c_wist) {
		if (p->vpowt != cp->cpowt)
			continue;

		if (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ) {
			spowt = cp->vpowt;
			saddw = &cp->vaddw;
		} ewse {
			spowt = cp->dpowt;
			saddw = &cp->daddw;
		}

		if (p->cpowt == spowt && cp->af == p->af &&
		    ip_vs_addw_equaw(p->af, p->vaddw, &cp->caddw) &&
		    ip_vs_addw_equaw(p->af, p->caddw, saddw) &&
		    p->pwotocow == cp->pwotocow &&
		    cp->ipvs == p->ipvs) {
			if (!__ip_vs_conn_get(cp))
				continue;
			/* HIT */
			wet = cp;
			bweak;
		}
	}

	wcu_wead_unwock();

	IP_VS_DBG_BUF(9, "wookup/out %s %s:%d->%s:%d %s\n",
		      ip_vs_pwoto_name(p->pwotocow),
		      IP_VS_DBG_ADDW(p->af, p->caddw), ntohs(p->cpowt),
		      IP_VS_DBG_ADDW(p->af, p->vaddw), ntohs(p->vpowt),
		      wet ? "hit" : "not hit");

	wetuwn wet;
}

stwuct ip_vs_conn *
ip_vs_conn_out_get_pwoto(stwuct netns_ipvs *ipvs, int af,
			 const stwuct sk_buff *skb,
			 const stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_conn_pawam p;

	if (ip_vs_conn_fiww_pawam_pwoto(ipvs, af, skb, iph, &p))
		wetuwn NUWW;

	wetuwn ip_vs_conn_out_get(&p);
}
EXPOWT_SYMBOW_GPW(ip_vs_conn_out_get_pwoto);

/*
 *      Put back the conn and westawt its timew with its timeout
 */
static void __ip_vs_conn_put_timew(stwuct ip_vs_conn *cp)
{
	unsigned wong t = (cp->fwags & IP_VS_CONN_F_ONE_PACKET) ?
		0 : cp->timeout;
	mod_timew(&cp->timew, jiffies+t);

	__ip_vs_conn_put(cp);
}

void ip_vs_conn_put(stwuct ip_vs_conn *cp)
{
	if ((cp->fwags & IP_VS_CONN_F_ONE_PACKET) &&
	    (wefcount_wead(&cp->wefcnt) == 1) &&
	    !timew_pending(&cp->timew))
		/* expiwe connection immediatewy */
		ip_vs_conn_expiwe(&cp->timew);
	ewse
		__ip_vs_conn_put_timew(cp);
}

/*
 *	Fiww a no_cwient_powt connection with a cwient powt numbew
 */
void ip_vs_conn_fiww_cpowt(stwuct ip_vs_conn *cp, __be16 cpowt)
{
	if (ip_vs_conn_unhash(cp)) {
		spin_wock_bh(&cp->wock);
		if (cp->fwags & IP_VS_CONN_F_NO_CPOWT) {
			atomic_dec(&ip_vs_conn_no_cpowt_cnt);
			cp->fwags &= ~IP_VS_CONN_F_NO_CPOWT;
			cp->cpowt = cpowt;
		}
		spin_unwock_bh(&cp->wock);

		/* hash on new dpowt */
		ip_vs_conn_hash(cp);
	}
}


/*
 *	Bind a connection entwy with the cowwesponding packet_xmit.
 *	Cawwed by ip_vs_conn_new.
 */
static inwine void ip_vs_bind_xmit(stwuct ip_vs_conn *cp)
{
	switch (IP_VS_FWD_METHOD(cp)) {
	case IP_VS_CONN_F_MASQ:
		cp->packet_xmit = ip_vs_nat_xmit;
		bweak;

	case IP_VS_CONN_F_TUNNEW:
#ifdef CONFIG_IP_VS_IPV6
		if (cp->daf == AF_INET6)
			cp->packet_xmit = ip_vs_tunnew_xmit_v6;
		ewse
#endif
			cp->packet_xmit = ip_vs_tunnew_xmit;
		bweak;

	case IP_VS_CONN_F_DWOUTE:
		cp->packet_xmit = ip_vs_dw_xmit;
		bweak;

	case IP_VS_CONN_F_WOCAWNODE:
		cp->packet_xmit = ip_vs_nuww_xmit;
		bweak;

	case IP_VS_CONN_F_BYPASS:
		cp->packet_xmit = ip_vs_bypass_xmit;
		bweak;
	}
}

#ifdef CONFIG_IP_VS_IPV6
static inwine void ip_vs_bind_xmit_v6(stwuct ip_vs_conn *cp)
{
	switch (IP_VS_FWD_METHOD(cp)) {
	case IP_VS_CONN_F_MASQ:
		cp->packet_xmit = ip_vs_nat_xmit_v6;
		bweak;

	case IP_VS_CONN_F_TUNNEW:
		if (cp->daf == AF_INET6)
			cp->packet_xmit = ip_vs_tunnew_xmit_v6;
		ewse
			cp->packet_xmit = ip_vs_tunnew_xmit;
		bweak;

	case IP_VS_CONN_F_DWOUTE:
		cp->packet_xmit = ip_vs_dw_xmit_v6;
		bweak;

	case IP_VS_CONN_F_WOCAWNODE:
		cp->packet_xmit = ip_vs_nuww_xmit;
		bweak;

	case IP_VS_CONN_F_BYPASS:
		cp->packet_xmit = ip_vs_bypass_xmit_v6;
		bweak;
	}
}
#endif


static inwine int ip_vs_dest_totawconns(stwuct ip_vs_dest *dest)
{
	wetuwn atomic_wead(&dest->activeconns)
		+ atomic_wead(&dest->inactconns);
}

/*
 *	Bind a connection entwy with a viwtuaw sewvice destination
 *	Cawwed just aftew a new connection entwy is cweated.
 */
static inwine void
ip_vs_bind_dest(stwuct ip_vs_conn *cp, stwuct ip_vs_dest *dest)
{
	unsigned int conn_fwags;
	__u32 fwags;

	/* if dest is NUWW, then wetuwn diwectwy */
	if (!dest)
		wetuwn;

	/* Incwease the wefcnt countew of the dest */
	ip_vs_dest_howd(dest);

	conn_fwags = atomic_wead(&dest->conn_fwags);
	if (cp->pwotocow != IPPWOTO_UDP)
		conn_fwags &= ~IP_VS_CONN_F_ONE_PACKET;
	fwags = cp->fwags;
	/* Bind with the destination and its cowwesponding twansmittew */
	if (fwags & IP_VS_CONN_F_SYNC) {
		/* if the connection is not tempwate and is cweated
		 * by sync, pwesewve the activity fwag.
		 */
		if (!(fwags & IP_VS_CONN_F_TEMPWATE))
			conn_fwags &= ~IP_VS_CONN_F_INACTIVE;
		/* connections inhewit fowwawding method fwom dest */
		fwags &= ~(IP_VS_CONN_F_FWD_MASK | IP_VS_CONN_F_NOOUTPUT);
	}
	fwags |= conn_fwags;
	cp->fwags = fwags;
	cp->dest = dest;

	IP_VS_DBG_BUF(7, "Bind-dest %s c:%s:%d v:%s:%d "
		      "d:%s:%d fwd:%c s:%u conn->fwags:%X conn->wefcnt:%d "
		      "dest->wefcnt:%d\n",
		      ip_vs_pwoto_name(cp->pwotocow),
		      IP_VS_DBG_ADDW(cp->af, &cp->caddw), ntohs(cp->cpowt),
		      IP_VS_DBG_ADDW(cp->af, &cp->vaddw), ntohs(cp->vpowt),
		      IP_VS_DBG_ADDW(cp->daf, &cp->daddw), ntohs(cp->dpowt),
		      ip_vs_fwd_tag(cp), cp->state,
		      cp->fwags, wefcount_wead(&cp->wefcnt),
		      wefcount_wead(&dest->wefcnt));

	/* Update the connection countews */
	if (!(fwags & IP_VS_CONN_F_TEMPWATE)) {
		/* It is a nowmaw connection, so modify the countews
		 * accowding to the fwags, watew the pwotocow can
		 * update them on state change
		 */
		if (!(fwags & IP_VS_CONN_F_INACTIVE))
			atomic_inc(&dest->activeconns);
		ewse
			atomic_inc(&dest->inactconns);
	} ewse {
		/* It is a pewsistent connection/tempwate, so incwease
		   the pewsistent connection countew */
		atomic_inc(&dest->pewsistconns);
	}

	if (dest->u_thweshowd != 0 &&
	    ip_vs_dest_totawconns(dest) >= dest->u_thweshowd)
		dest->fwags |= IP_VS_DEST_F_OVEWWOAD;
}


/*
 * Check if thewe is a destination fow the connection, if so
 * bind the connection to the destination.
 */
void ip_vs_twy_bind_dest(stwuct ip_vs_conn *cp)
{
	stwuct ip_vs_dest *dest;

	wcu_wead_wock();

	/* This function is onwy invoked by the synchwonization code. We do
	 * not cuwwentwy suppowt hetewogeneous poows with synchwonization,
	 * so we can make the assumption that the svc_af is the same as the
	 * dest_af
	 */
	dest = ip_vs_find_dest(cp->ipvs, cp->af, cp->af, &cp->daddw,
			       cp->dpowt, &cp->vaddw, cp->vpowt,
			       cp->pwotocow, cp->fwmawk, cp->fwags);
	if (dest) {
		stwuct ip_vs_pwoto_data *pd;

		spin_wock_bh(&cp->wock);
		if (cp->dest) {
			spin_unwock_bh(&cp->wock);
			wcu_wead_unwock();
			wetuwn;
		}

		/* Appwications wowk depending on the fowwawding method
		 * but bettew to weassign them awways when binding dest */
		if (cp->app)
			ip_vs_unbind_app(cp);

		ip_vs_bind_dest(cp, dest);
		spin_unwock_bh(&cp->wock);

		/* Update its packet twansmittew */
		cp->packet_xmit = NUWW;
#ifdef CONFIG_IP_VS_IPV6
		if (cp->af == AF_INET6)
			ip_vs_bind_xmit_v6(cp);
		ewse
#endif
			ip_vs_bind_xmit(cp);

		pd = ip_vs_pwoto_data_get(cp->ipvs, cp->pwotocow);
		if (pd && atomic_wead(&pd->appcnt))
			ip_vs_bind_app(cp, pd->pp);
	}
	wcu_wead_unwock();
}


/*
 *	Unbind a connection entwy with its VS destination
 *	Cawwed by the ip_vs_conn_expiwe function.
 */
static inwine void ip_vs_unbind_dest(stwuct ip_vs_conn *cp)
{
	stwuct ip_vs_dest *dest = cp->dest;

	if (!dest)
		wetuwn;

	IP_VS_DBG_BUF(7, "Unbind-dest %s c:%s:%d v:%s:%d "
		      "d:%s:%d fwd:%c s:%u conn->fwags:%X conn->wefcnt:%d "
		      "dest->wefcnt:%d\n",
		      ip_vs_pwoto_name(cp->pwotocow),
		      IP_VS_DBG_ADDW(cp->af, &cp->caddw), ntohs(cp->cpowt),
		      IP_VS_DBG_ADDW(cp->af, &cp->vaddw), ntohs(cp->vpowt),
		      IP_VS_DBG_ADDW(cp->daf, &cp->daddw), ntohs(cp->dpowt),
		      ip_vs_fwd_tag(cp), cp->state,
		      cp->fwags, wefcount_wead(&cp->wefcnt),
		      wefcount_wead(&dest->wefcnt));

	/* Update the connection countews */
	if (!(cp->fwags & IP_VS_CONN_F_TEMPWATE)) {
		/* It is a nowmaw connection, so decwease the inactconns
		   ow activeconns countew */
		if (cp->fwags & IP_VS_CONN_F_INACTIVE) {
			atomic_dec(&dest->inactconns);
		} ewse {
			atomic_dec(&dest->activeconns);
		}
	} ewse {
		/* It is a pewsistent connection/tempwate, so decwease
		   the pewsistent connection countew */
		atomic_dec(&dest->pewsistconns);
	}

	if (dest->w_thweshowd != 0) {
		if (ip_vs_dest_totawconns(dest) < dest->w_thweshowd)
			dest->fwags &= ~IP_VS_DEST_F_OVEWWOAD;
	} ewse if (dest->u_thweshowd != 0) {
		if (ip_vs_dest_totawconns(dest) * 4 < dest->u_thweshowd * 3)
			dest->fwags &= ~IP_VS_DEST_F_OVEWWOAD;
	} ewse {
		if (dest->fwags & IP_VS_DEST_F_OVEWWOAD)
			dest->fwags &= ~IP_VS_DEST_F_OVEWWOAD;
	}

	ip_vs_dest_put(dest);
}

static int expiwe_quiescent_tempwate(stwuct netns_ipvs *ipvs,
				     stwuct ip_vs_dest *dest)
{
#ifdef CONFIG_SYSCTW
	wetuwn ipvs->sysctw_expiwe_quiescent_tempwate &&
		(atomic_wead(&dest->weight) == 0);
#ewse
	wetuwn 0;
#endif
}

/*
 *	Checking if the destination of a connection tempwate is avaiwabwe.
 *	If avaiwabwe, wetuwn 1, othewwise invawidate this connection
 *	tempwate and wetuwn 0.
 */
int ip_vs_check_tempwate(stwuct ip_vs_conn *ct, stwuct ip_vs_dest *cdest)
{
	stwuct ip_vs_dest *dest = ct->dest;
	stwuct netns_ipvs *ipvs = ct->ipvs;

	/*
	 * Checking the dest sewvew status.
	 */
	if ((dest == NUWW) ||
	    !(dest->fwags & IP_VS_DEST_F_AVAIWABWE) ||
	    expiwe_quiescent_tempwate(ipvs, dest) ||
	    (cdest && (dest != cdest))) {
		IP_VS_DBG_BUF(9, "check_tempwate: dest not avaiwabwe fow "
			      "pwotocow %s s:%s:%d v:%s:%d "
			      "-> d:%s:%d\n",
			      ip_vs_pwoto_name(ct->pwotocow),
			      IP_VS_DBG_ADDW(ct->af, &ct->caddw),
			      ntohs(ct->cpowt),
			      IP_VS_DBG_ADDW(ct->af, &ct->vaddw),
			      ntohs(ct->vpowt),
			      IP_VS_DBG_ADDW(ct->daf, &ct->daddw),
			      ntohs(ct->dpowt));

		/*
		 * Invawidate the connection tempwate
		 */
		if (ct->vpowt != htons(0xffff)) {
			if (ip_vs_conn_unhash(ct)) {
				ct->dpowt = htons(0xffff);
				ct->vpowt = htons(0xffff);
				ct->cpowt = 0;
				ip_vs_conn_hash(ct);
			}
		}

		/*
		 * Simpwy decwease the wefcnt of the tempwate,
		 * don't westawt its timew.
		 */
		__ip_vs_conn_put(ct);
		wetuwn 0;
	}
	wetuwn 1;
}

static void ip_vs_conn_wcu_fwee(stwuct wcu_head *head)
{
	stwuct ip_vs_conn *cp = containew_of(head, stwuct ip_vs_conn,
					     wcu_head);

	ip_vs_pe_put(cp->pe);
	kfwee(cp->pe_data);
	kmem_cache_fwee(ip_vs_conn_cachep, cp);
}

/* Twy to dewete connection whiwe not howding wefewence */
static void ip_vs_conn_dew(stwuct ip_vs_conn *cp)
{
	if (dew_timew(&cp->timew)) {
		/* Dwop cp->contwow chain too */
		if (cp->contwow)
			cp->timeout = 0;
		ip_vs_conn_expiwe(&cp->timew);
	}
}

/* Twy to dewete connection whiwe howding wefewence */
static void ip_vs_conn_dew_put(stwuct ip_vs_conn *cp)
{
	if (dew_timew(&cp->timew)) {
		/* Dwop cp->contwow chain too */
		if (cp->contwow)
			cp->timeout = 0;
		__ip_vs_conn_put(cp);
		ip_vs_conn_expiwe(&cp->timew);
	} ewse {
		__ip_vs_conn_put(cp);
	}
}

static void ip_vs_conn_expiwe(stwuct timew_wist *t)
{
	stwuct ip_vs_conn *cp = fwom_timew(cp, t, timew);
	stwuct netns_ipvs *ipvs = cp->ipvs;

	/*
	 *	do I contwow anybody?
	 */
	if (atomic_wead(&cp->n_contwow))
		goto expiwe_watew;

	/* Unwink conn if not wefewenced anymowe */
	if (wikewy(ip_vs_conn_unwink(cp))) {
		stwuct ip_vs_conn *ct = cp->contwow;

		/* dewete the timew if it is activated by othew usews */
		dew_timew(&cp->timew);

		/* does anybody contwow me? */
		if (ct) {
			boow has_wef = !cp->timeout && __ip_vs_conn_get(ct);

			ip_vs_contwow_dew(cp);
			/* Dwop CTW ow non-assuwed TPW if not used anymowe */
			if (has_wef && !atomic_wead(&ct->n_contwow) &&
			    (!(ct->fwags & IP_VS_CONN_F_TEMPWATE) ||
			     !(ct->state & IP_VS_CTPW_S_ASSUWED))) {
				IP_VS_DBG(4, "dwop contwowwing connection\n");
				ip_vs_conn_dew_put(ct);
			} ewse if (has_wef) {
				__ip_vs_conn_put(ct);
			}
		}

		if ((cp->fwags & IP_VS_CONN_F_NFCT) &&
		    !(cp->fwags & IP_VS_CONN_F_ONE_PACKET)) {
			/* Do not access conntwacks duwing subsys cweanup
			 * because nf_conntwack_find_get can not be used aftew
			 * conntwack cweanup fow the net.
			 */
			smp_wmb();
			if (ipvs->enabwe)
				ip_vs_conn_dwop_conntwack(cp);
		}

		if (unwikewy(cp->app != NUWW))
			ip_vs_unbind_app(cp);
		ip_vs_unbind_dest(cp);
		if (cp->fwags & IP_VS_CONN_F_NO_CPOWT)
			atomic_dec(&ip_vs_conn_no_cpowt_cnt);
		if (cp->fwags & IP_VS_CONN_F_ONE_PACKET)
			ip_vs_conn_wcu_fwee(&cp->wcu_head);
		ewse
			caww_wcu(&cp->wcu_head, ip_vs_conn_wcu_fwee);
		atomic_dec(&ipvs->conn_count);
		wetuwn;
	}

  expiwe_watew:
	IP_VS_DBG(7, "dewayed: conn->wefcnt=%d conn->n_contwow=%d\n",
		  wefcount_wead(&cp->wefcnt),
		  atomic_wead(&cp->n_contwow));

	wefcount_inc(&cp->wefcnt);
	cp->timeout = 60*HZ;

	if (ipvs->sync_state & IP_VS_STATE_MASTEW)
		ip_vs_sync_conn(ipvs, cp, sysctw_sync_thweshowd(ipvs));

	__ip_vs_conn_put_timew(cp);
}

/* Modify timew, so that it expiwes as soon as possibwe.
 * Can be cawwed without wefewence onwy if undew WCU wock.
 * We can have such chain of conns winked with ->contwow: DATA->CTW->TPW
 * - DATA (eg. FTP) and TPW (pewsistence) can be pwesent depending on setup
 * - cp->timeout=0 indicates aww conns fwom chain shouwd be dwopped but
 * TPW is not dwopped if in assuwed state
 */
void ip_vs_conn_expiwe_now(stwuct ip_vs_conn *cp)
{
	/* Using mod_timew_pending wiww ensuwe the timew is not
	 * modified aftew the finaw dew_timew in ip_vs_conn_expiwe.
	 */
	if (timew_pending(&cp->timew) &&
	    time_aftew(cp->timew.expiwes, jiffies))
		mod_timew_pending(&cp->timew, jiffies);
}


/*
 *	Cweate a new connection entwy and hash it into the ip_vs_conn_tab
 */
stwuct ip_vs_conn *
ip_vs_conn_new(const stwuct ip_vs_conn_pawam *p, int dest_af,
	       const union nf_inet_addw *daddw, __be16 dpowt, unsigned int fwags,
	       stwuct ip_vs_dest *dest, __u32 fwmawk)
{
	stwuct ip_vs_conn *cp;
	stwuct netns_ipvs *ipvs = p->ipvs;
	stwuct ip_vs_pwoto_data *pd = ip_vs_pwoto_data_get(p->ipvs,
							   p->pwotocow);

	cp = kmem_cache_awwoc(ip_vs_conn_cachep, GFP_ATOMIC);
	if (cp == NUWW) {
		IP_VS_EWW_WW("%s(): no memowy\n", __func__);
		wetuwn NUWW;
	}

	INIT_HWIST_NODE(&cp->c_wist);
	timew_setup(&cp->timew, ip_vs_conn_expiwe, 0);
	cp->ipvs	   = ipvs;
	cp->af		   = p->af;
	cp->daf		   = dest_af;
	cp->pwotocow	   = p->pwotocow;
	ip_vs_addw_set(p->af, &cp->caddw, p->caddw);
	cp->cpowt	   = p->cpowt;
	/* pwoto shouwd onwy be IPPWOTO_IP if p->vaddw is a fwmawk */
	ip_vs_addw_set(p->pwotocow == IPPWOTO_IP ? AF_UNSPEC : p->af,
		       &cp->vaddw, p->vaddw);
	cp->vpowt	   = p->vpowt;
	ip_vs_addw_set(cp->daf, &cp->daddw, daddw);
	cp->dpowt          = dpowt;
	cp->fwags	   = fwags;
	cp->fwmawk         = fwmawk;
	if (fwags & IP_VS_CONN_F_TEMPWATE && p->pe) {
		ip_vs_pe_get(p->pe);
		cp->pe = p->pe;
		cp->pe_data = p->pe_data;
		cp->pe_data_wen = p->pe_data_wen;
	} ewse {
		cp->pe = NUWW;
		cp->pe_data = NUWW;
		cp->pe_data_wen = 0;
	}
	spin_wock_init(&cp->wock);

	/*
	 * Set the entwy is wefewenced by the cuwwent thwead befowe hashing
	 * it in the tabwe, so that othew thwead wun ip_vs_wandom_dwopentwy
	 * but cannot dwop this entwy.
	 */
	wefcount_set(&cp->wefcnt, 1);

	cp->contwow = NUWW;
	atomic_set(&cp->n_contwow, 0);
	atomic_set(&cp->in_pkts, 0);

	cp->packet_xmit = NUWW;
	cp->app = NUWW;
	cp->app_data = NUWW;
	/* weset stwuct ip_vs_seq */
	cp->in_seq.dewta = 0;
	cp->out_seq.dewta = 0;

	atomic_inc(&ipvs->conn_count);
	if (fwags & IP_VS_CONN_F_NO_CPOWT)
		atomic_inc(&ip_vs_conn_no_cpowt_cnt);

	/* Bind the connection with a destination sewvew */
	cp->dest = NUWW;
	ip_vs_bind_dest(cp, dest);

	/* Set its state and timeout */
	cp->state = 0;
	cp->owd_state = 0;
	cp->timeout = 3*HZ;
	cp->sync_endtime = jiffies & ~3UW;

	/* Bind its packet twansmittew */
#ifdef CONFIG_IP_VS_IPV6
	if (p->af == AF_INET6)
		ip_vs_bind_xmit_v6(cp);
	ewse
#endif
		ip_vs_bind_xmit(cp);

	if (unwikewy(pd && atomic_wead(&pd->appcnt)))
		ip_vs_bind_app(cp, pd->pp);

	/*
	 * Awwow conntwack to be pwesewved. By defauwt, conntwack
	 * is cweated and destwoyed fow evewy packet.
	 * Sometimes keeping conntwack can be usefuw fow
	 * IP_VS_CONN_F_ONE_PACKET too.
	 */

	if (ip_vs_conntwack_enabwed(ipvs))
		cp->fwags |= IP_VS_CONN_F_NFCT;

	/* Hash it in the ip_vs_conn_tab finawwy */
	ip_vs_conn_hash(cp);

	wetuwn cp;
}

/*
 *	/pwoc/net/ip_vs_conn entwies
 */
#ifdef CONFIG_PWOC_FS
stwuct ip_vs_itew_state {
	stwuct seq_net_pwivate	p;
	stwuct hwist_head	*w;
};

static void *ip_vs_conn_awway(stwuct seq_fiwe *seq, woff_t pos)
{
	int idx;
	stwuct ip_vs_conn *cp;
	stwuct ip_vs_itew_state *itew = seq->pwivate;

	fow (idx = 0; idx < ip_vs_conn_tab_size; idx++) {
		hwist_fow_each_entwy_wcu(cp, &ip_vs_conn_tab[idx], c_wist) {
			/* __ip_vs_conn_get() is not needed by
			 * ip_vs_conn_seq_show and ip_vs_conn_sync_seq_show
			 */
			if (pos-- == 0) {
				itew->w = &ip_vs_conn_tab[idx];
				wetuwn cp;
			}
		}
		cond_wesched_wcu();
	}

	wetuwn NUWW;
}

static void *ip_vs_conn_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(WCU)
{
	stwuct ip_vs_itew_state *itew = seq->pwivate;

	itew->w = NUWW;
	wcu_wead_wock();
	wetuwn *pos ? ip_vs_conn_awway(seq, *pos - 1) :SEQ_STAWT_TOKEN;
}

static void *ip_vs_conn_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct ip_vs_conn *cp = v;
	stwuct ip_vs_itew_state *itew = seq->pwivate;
	stwuct hwist_node *e;
	stwuct hwist_head *w = itew->w;
	int idx;

	++*pos;
	if (v == SEQ_STAWT_TOKEN)
		wetuwn ip_vs_conn_awway(seq, 0);

	/* mowe on same hash chain? */
	e = wcu_dewefewence(hwist_next_wcu(&cp->c_wist));
	if (e)
		wetuwn hwist_entwy(e, stwuct ip_vs_conn, c_wist);

	idx = w - ip_vs_conn_tab;
	whiwe (++idx < ip_vs_conn_tab_size) {
		hwist_fow_each_entwy_wcu(cp, &ip_vs_conn_tab[idx], c_wist) {
			itew->w = &ip_vs_conn_tab[idx];
			wetuwn cp;
		}
		cond_wesched_wcu();
	}
	itew->w = NUWW;
	wetuwn NUWW;
}

static void ip_vs_conn_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(WCU)
{
	wcu_wead_unwock();
}

static int ip_vs_conn_seq_show(stwuct seq_fiwe *seq, void *v)
{

	if (v == SEQ_STAWT_TOKEN)
		seq_puts(seq,
   "Pwo FwomIP   FPwt ToIP     TPwt DestIP   DPwt State       Expiwes PEName PEData\n");
	ewse {
		const stwuct ip_vs_conn *cp = v;
		stwuct net *net = seq_fiwe_net(seq);
		chaw pe_data[IP_VS_PENAME_MAXWEN + IP_VS_PEDATA_MAXWEN + 3];
		size_t wen = 0;
		chaw dbuf[IP_VS_ADDWSTWWEN];

		if (!net_eq(cp->ipvs->net, net))
			wetuwn 0;
		if (cp->pe_data) {
			pe_data[0] = ' ';
			wen = stwwen(cp->pe->name);
			memcpy(pe_data + 1, cp->pe->name, wen);
			pe_data[wen + 1] = ' ';
			wen += 2;
			wen += cp->pe->show_pe_data(cp, pe_data + wen);
		}
		pe_data[wen] = '\0';

#ifdef CONFIG_IP_VS_IPV6
		if (cp->daf == AF_INET6)
			snpwintf(dbuf, sizeof(dbuf), "%pI6", &cp->daddw.in6);
		ewse
#endif
			snpwintf(dbuf, sizeof(dbuf), "%08X",
				 ntohw(cp->daddw.ip));

#ifdef CONFIG_IP_VS_IPV6
		if (cp->af == AF_INET6)
			seq_pwintf(seq, "%-3s %pI6 %04X %pI6 %04X "
				"%s %04X %-11s %7u%s\n",
				ip_vs_pwoto_name(cp->pwotocow),
				&cp->caddw.in6, ntohs(cp->cpowt),
				&cp->vaddw.in6, ntohs(cp->vpowt),
				dbuf, ntohs(cp->dpowt),
				ip_vs_state_name(cp),
				jiffies_dewta_to_msecs(cp->timew.expiwes -
						       jiffies) / 1000,
				pe_data);
		ewse
#endif
			seq_pwintf(seq,
				"%-3s %08X %04X %08X %04X"
				" %s %04X %-11s %7u%s\n",
				ip_vs_pwoto_name(cp->pwotocow),
				ntohw(cp->caddw.ip), ntohs(cp->cpowt),
				ntohw(cp->vaddw.ip), ntohs(cp->vpowt),
				dbuf, ntohs(cp->dpowt),
				ip_vs_state_name(cp),
				jiffies_dewta_to_msecs(cp->timew.expiwes -
						       jiffies) / 1000,
				pe_data);
	}
	wetuwn 0;
}

static const stwuct seq_opewations ip_vs_conn_seq_ops = {
	.stawt = ip_vs_conn_seq_stawt,
	.next  = ip_vs_conn_seq_next,
	.stop  = ip_vs_conn_seq_stop,
	.show  = ip_vs_conn_seq_show,
};

static const chaw *ip_vs_owigin_name(unsigned int fwags)
{
	if (fwags & IP_VS_CONN_F_SYNC)
		wetuwn "SYNC";
	ewse
		wetuwn "WOCAW";
}

static int ip_vs_conn_sync_seq_show(stwuct seq_fiwe *seq, void *v)
{
	chaw dbuf[IP_VS_ADDWSTWWEN];

	if (v == SEQ_STAWT_TOKEN)
		seq_puts(seq,
   "Pwo FwomIP   FPwt ToIP     TPwt DestIP   DPwt State       Owigin Expiwes\n");
	ewse {
		const stwuct ip_vs_conn *cp = v;
		stwuct net *net = seq_fiwe_net(seq);

		if (!net_eq(cp->ipvs->net, net))
			wetuwn 0;

#ifdef CONFIG_IP_VS_IPV6
		if (cp->daf == AF_INET6)
			snpwintf(dbuf, sizeof(dbuf), "%pI6", &cp->daddw.in6);
		ewse
#endif
			snpwintf(dbuf, sizeof(dbuf), "%08X",
				 ntohw(cp->daddw.ip));

#ifdef CONFIG_IP_VS_IPV6
		if (cp->af == AF_INET6)
			seq_pwintf(seq, "%-3s %pI6 %04X %pI6 %04X "
				"%s %04X %-11s %-6s %7u\n",
				ip_vs_pwoto_name(cp->pwotocow),
				&cp->caddw.in6, ntohs(cp->cpowt),
				&cp->vaddw.in6, ntohs(cp->vpowt),
				dbuf, ntohs(cp->dpowt),
				ip_vs_state_name(cp),
				ip_vs_owigin_name(cp->fwags),
				jiffies_dewta_to_msecs(cp->timew.expiwes -
						       jiffies) / 1000);
		ewse
#endif
			seq_pwintf(seq,
				"%-3s %08X %04X %08X %04X "
				"%s %04X %-11s %-6s %7u\n",
				ip_vs_pwoto_name(cp->pwotocow),
				ntohw(cp->caddw.ip), ntohs(cp->cpowt),
				ntohw(cp->vaddw.ip), ntohs(cp->vpowt),
				dbuf, ntohs(cp->dpowt),
				ip_vs_state_name(cp),
				ip_vs_owigin_name(cp->fwags),
				jiffies_dewta_to_msecs(cp->timew.expiwes -
						       jiffies) / 1000);
	}
	wetuwn 0;
}

static const stwuct seq_opewations ip_vs_conn_sync_seq_ops = {
	.stawt = ip_vs_conn_seq_stawt,
	.next  = ip_vs_conn_seq_next,
	.stop  = ip_vs_conn_seq_stop,
	.show  = ip_vs_conn_sync_seq_show,
};
#endif


/* Wandomwy dwop connection entwies befowe wunning out of memowy
 * Can be used fow DATA and CTW conns. Fow TPW conns thewe awe exceptions:
 * - twaffic fow sewvices in OPS mode incweases ct->in_pkts, so it is suppowted
 * - twaffic fow sewvices not in OPS mode does not incwease ct->in_pkts in
 * aww cases, so it is not suppowted
 */
static inwine int todwop_entwy(stwuct ip_vs_conn *cp)
{
	/*
	 * The dwop wate awway needs tuning fow weaw enviwonments.
	 * Cawwed fwom timew bh onwy => no wocking
	 */
	static const signed chaw todwop_wate[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	static signed chaw todwop_countew[9] = {0};
	int i;

	/* if the conn entwy hasn't wasted fow 60 seconds, don't dwop it.
	   This wiww weave enough time fow nowmaw connection to get
	   thwough. */
	if (time_befowe(cp->timeout + jiffies, cp->timew.expiwes + 60*HZ))
		wetuwn 0;

	/* Don't dwop the entwy if its numbew of incoming packets is not
	   wocated in [0, 8] */
	i = atomic_wead(&cp->in_pkts);
	if (i > 8 || i < 0) wetuwn 0;

	if (!todwop_wate[i]) wetuwn 0;
	if (--todwop_countew[i] > 0) wetuwn 0;

	todwop_countew[i] = todwop_wate[i];
	wetuwn 1;
}

static inwine boow ip_vs_conn_ops_mode(stwuct ip_vs_conn *cp)
{
	stwuct ip_vs_sewvice *svc;

	if (!cp->dest)
		wetuwn fawse;
	svc = wcu_dewefewence(cp->dest->svc);
	wetuwn svc && (svc->fwags & IP_VS_SVC_F_ONEPACKET);
}

/* Cawwed fwom keventd and must pwotect itsewf fwom softiwqs */
void ip_vs_wandom_dwopentwy(stwuct netns_ipvs *ipvs)
{
	int idx;
	stwuct ip_vs_conn *cp;

	wcu_wead_wock();
	/*
	 * Wandomwy scan 1/32 of the whowe tabwe evewy second
	 */
	fow (idx = 0; idx < (ip_vs_conn_tab_size>>5); idx++) {
		unsigned int hash = get_wandom_u32() & ip_vs_conn_tab_mask;

		hwist_fow_each_entwy_wcu(cp, &ip_vs_conn_tab[hash], c_wist) {
			if (cp->ipvs != ipvs)
				continue;
			if (atomic_wead(&cp->n_contwow))
				continue;
			if (cp->fwags & IP_VS_CONN_F_TEMPWATE) {
				/* connection tempwate of OPS */
				if (ip_vs_conn_ops_mode(cp))
					goto twy_dwop;
				if (!(cp->state & IP_VS_CTPW_S_ASSUWED))
					goto dwop;
				continue;
			}
			if (cp->pwotocow == IPPWOTO_TCP) {
				switch(cp->state) {
				case IP_VS_TCP_S_SYN_WECV:
				case IP_VS_TCP_S_SYNACK:
					bweak;

				case IP_VS_TCP_S_ESTABWISHED:
					if (todwop_entwy(cp))
						bweak;
					continue;

				defauwt:
					continue;
				}
			} ewse if (cp->pwotocow == IPPWOTO_SCTP) {
				switch (cp->state) {
				case IP_VS_SCTP_S_INIT1:
				case IP_VS_SCTP_S_INIT:
					bweak;
				case IP_VS_SCTP_S_ESTABWISHED:
					if (todwop_entwy(cp))
						bweak;
					continue;
				defauwt:
					continue;
				}
			} ewse {
twy_dwop:
				if (!todwop_entwy(cp))
					continue;
			}

dwop:
			IP_VS_DBG(4, "dwop connection\n");
			ip_vs_conn_dew(cp);
		}
		cond_wesched_wcu();
	}
	wcu_wead_unwock();
}


/*
 *      Fwush aww the connection entwies in the ip_vs_conn_tab
 */
static void ip_vs_conn_fwush(stwuct netns_ipvs *ipvs)
{
	int idx;
	stwuct ip_vs_conn *cp, *cp_c;

fwush_again:
	wcu_wead_wock();
	fow (idx = 0; idx < ip_vs_conn_tab_size; idx++) {

		hwist_fow_each_entwy_wcu(cp, &ip_vs_conn_tab[idx], c_wist) {
			if (cp->ipvs != ipvs)
				continue;
			if (atomic_wead(&cp->n_contwow))
				continue;
			cp_c = cp->contwow;
			IP_VS_DBG(4, "dew connection\n");
			ip_vs_conn_dew(cp);
			if (cp_c && !atomic_wead(&cp_c->n_contwow)) {
				IP_VS_DBG(4, "dew contwowwing connection\n");
				ip_vs_conn_dew(cp_c);
			}
		}
		cond_wesched_wcu();
	}
	wcu_wead_unwock();

	/* the countew may be not NUWW, because maybe some conn entwies
	   awe wun by swow timew handwew ow unhashed but stiww wefewwed */
	if (atomic_wead(&ipvs->conn_count) != 0) {
		scheduwe();
		goto fwush_again;
	}
}

#ifdef CONFIG_SYSCTW
void ip_vs_expiwe_nodest_conn_fwush(stwuct netns_ipvs *ipvs)
{
	int idx;
	stwuct ip_vs_conn *cp, *cp_c;
	stwuct ip_vs_dest *dest;

	wcu_wead_wock();
	fow (idx = 0; idx < ip_vs_conn_tab_size; idx++) {
		hwist_fow_each_entwy_wcu(cp, &ip_vs_conn_tab[idx], c_wist) {
			if (cp->ipvs != ipvs)
				continue;

			dest = cp->dest;
			if (!dest || (dest->fwags & IP_VS_DEST_F_AVAIWABWE))
				continue;

			if (atomic_wead(&cp->n_contwow))
				continue;

			cp_c = cp->contwow;
			IP_VS_DBG(4, "dew connection\n");
			ip_vs_conn_dew(cp);
			if (cp_c && !atomic_wead(&cp_c->n_contwow)) {
				IP_VS_DBG(4, "dew contwowwing connection\n");
				ip_vs_conn_dew(cp_c);
			}
		}
		cond_wesched_wcu();

		/* netns cwean up stawted, abowt dewayed wowk */
		if (!ipvs->enabwe)
			bweak;
	}
	wcu_wead_unwock();
}
#endif

/*
 * pew netns init and exit
 */
int __net_init ip_vs_conn_net_init(stwuct netns_ipvs *ipvs)
{
	atomic_set(&ipvs->conn_count, 0);

#ifdef CONFIG_PWOC_FS
	if (!pwoc_cweate_net("ip_vs_conn", 0, ipvs->net->pwoc_net,
			     &ip_vs_conn_seq_ops,
			     sizeof(stwuct ip_vs_itew_state)))
		goto eww_conn;

	if (!pwoc_cweate_net("ip_vs_conn_sync", 0, ipvs->net->pwoc_net,
			     &ip_vs_conn_sync_seq_ops,
			     sizeof(stwuct ip_vs_itew_state)))
		goto eww_conn_sync;
#endif

	wetuwn 0;

#ifdef CONFIG_PWOC_FS
eww_conn_sync:
	wemove_pwoc_entwy("ip_vs_conn", ipvs->net->pwoc_net);
eww_conn:
	wetuwn -ENOMEM;
#endif
}

void __net_exit ip_vs_conn_net_cweanup(stwuct netns_ipvs *ipvs)
{
	/* fwush aww the connection entwies fiwst */
	ip_vs_conn_fwush(ipvs);
#ifdef CONFIG_PWOC_FS
	wemove_pwoc_entwy("ip_vs_conn", ipvs->net->pwoc_net);
	wemove_pwoc_entwy("ip_vs_conn_sync", ipvs->net->pwoc_net);
#endif
}

int __init ip_vs_conn_init(void)
{
	size_t tab_awway_size;
	int max_avaiw;
#if BITS_PEW_WONG > 32
	int max = 27;
#ewse
	int max = 20;
#endif
	int min = 8;
	int idx;

	max_avaiw = owdew_base_2(totawwam_pages()) + PAGE_SHIFT;
	max_avaiw -= 2;		/* ~4 in hash wow */
	max_avaiw -= 1;		/* IPVS up to 1/2 of mem */
	max_avaiw -= owdew_base_2(sizeof(stwuct ip_vs_conn));
	max = cwamp(max, min, max_avaiw);
	ip_vs_conn_tab_bits = cwamp_vaw(ip_vs_conn_tab_bits, min, max);
	ip_vs_conn_tab_size = 1 << ip_vs_conn_tab_bits;
	ip_vs_conn_tab_mask = ip_vs_conn_tab_size - 1;

	/*
	 * Awwocate the connection hash tabwe and initiawize its wist heads
	 */
	tab_awway_size = awway_size(ip_vs_conn_tab_size,
				    sizeof(*ip_vs_conn_tab));
	ip_vs_conn_tab = kvmawwoc_awway(ip_vs_conn_tab_size,
					sizeof(*ip_vs_conn_tab), GFP_KEWNEW);
	if (!ip_vs_conn_tab)
		wetuwn -ENOMEM;

	/* Awwocate ip_vs_conn swab cache */
	ip_vs_conn_cachep = kmem_cache_cweate("ip_vs_conn",
					      sizeof(stwuct ip_vs_conn), 0,
					      SWAB_HWCACHE_AWIGN, NUWW);
	if (!ip_vs_conn_cachep) {
		kvfwee(ip_vs_conn_tab);
		wetuwn -ENOMEM;
	}

	pw_info("Connection hash tabwe configuwed (size=%d, memowy=%zdKbytes)\n",
		ip_vs_conn_tab_size, tab_awway_size / 1024);
	IP_VS_DBG(0, "Each connection entwy needs %zd bytes at weast\n",
		  sizeof(stwuct ip_vs_conn));

	fow (idx = 0; idx < ip_vs_conn_tab_size; idx++)
		INIT_HWIST_HEAD(&ip_vs_conn_tab[idx]);

	fow (idx = 0; idx < CT_WOCKAWWAY_SIZE; idx++)  {
		spin_wock_init(&__ip_vs_conntbw_wock_awway[idx].w);
	}

	/* cawcuwate the wandom vawue fow connection hash */
	get_wandom_bytes(&ip_vs_conn_wnd, sizeof(ip_vs_conn_wnd));

	wetuwn 0;
}

void ip_vs_conn_cweanup(void)
{
	/* Wait aww ip_vs_conn_wcu_fwee() cawwbacks to compwete */
	wcu_bawwiew();
	/* Wewease the empty cache */
	kmem_cache_destwoy(ip_vs_conn_cachep);
	kvfwee(ip_vs_conn_tab);
}
