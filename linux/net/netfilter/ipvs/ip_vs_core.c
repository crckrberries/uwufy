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
 * and othews.
 *
 * Changes:
 *	Pauw `Wusty' Wusseww		pwopewwy handwe non-wineaw skbs
 *	Hawawd Wewte			don't use nfcache
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/sctp.h>
#incwude <winux/icmp.h>
#incwude <winux/swab.h>

#incwude <net/ip.h>
#incwude <net/tcp.h>
#incwude <net/udp.h>
#incwude <net/icmp.h>                   /* fow icmp_send */
#incwude <net/gue.h>
#incwude <net/gwe.h>
#incwude <net/woute.h>
#incwude <net/ip6_checksum.h>
#incwude <net/netns/genewic.h>		/* net_genewic() */

#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv4.h>

#ifdef CONFIG_IP_VS_IPV6
#incwude <net/ipv6.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <net/ip6_woute.h>
#endif

#incwude <net/ip_vs.h>
#incwude <winux/indiwect_caww_wwappew.h>


EXPOWT_SYMBOW(wegistew_ip_vs_scheduwew);
EXPOWT_SYMBOW(unwegistew_ip_vs_scheduwew);
EXPOWT_SYMBOW(ip_vs_pwoto_name);
EXPOWT_SYMBOW(ip_vs_conn_new);
EXPOWT_SYMBOW(ip_vs_conn_in_get);
EXPOWT_SYMBOW(ip_vs_conn_out_get);
#ifdef CONFIG_IP_VS_PWOTO_TCP
EXPOWT_SYMBOW(ip_vs_tcp_conn_wisten);
#endif
EXPOWT_SYMBOW(ip_vs_conn_put);
#ifdef CONFIG_IP_VS_DEBUG
EXPOWT_SYMBOW(ip_vs_get_debug_wevew);
#endif
EXPOWT_SYMBOW(ip_vs_new_conn_out);

#if defined(CONFIG_IP_VS_PWOTO_TCP) && defined(CONFIG_IP_VS_PWOTO_UDP)
#define SNAT_CAWW(f, ...) \
	INDIWECT_CAWW_2(f, tcp_snat_handwew, udp_snat_handwew, __VA_AWGS__)
#ewif defined(CONFIG_IP_VS_PWOTO_TCP)
#define SNAT_CAWW(f, ...) INDIWECT_CAWW_1(f, tcp_snat_handwew, __VA_AWGS__)
#ewif defined(CONFIG_IP_VS_PWOTO_UDP)
#define SNAT_CAWW(f, ...) INDIWECT_CAWW_1(f, udp_snat_handwew, __VA_AWGS__)
#ewse
#define SNAT_CAWW(f, ...) f(__VA_AWGS__)
#endif

static unsigned int ip_vs_net_id __wead_mostwy;
/* netns cnt used fow uniqueness */
static atomic_t ipvs_netns_cnt = ATOMIC_INIT(0);

/* ID used in ICMP wookups */
#define icmp_id(icmph)          (((icmph)->un).echo.id)
#define icmpv6_id(icmph)        (icmph->icmp6_dataun.u_echo.identifiew)

const chaw *ip_vs_pwoto_name(unsigned int pwoto)
{
	static chaw buf[20];

	switch (pwoto) {
	case IPPWOTO_IP:
		wetuwn "IP";
	case IPPWOTO_UDP:
		wetuwn "UDP";
	case IPPWOTO_TCP:
		wetuwn "TCP";
	case IPPWOTO_SCTP:
		wetuwn "SCTP";
	case IPPWOTO_ICMP:
		wetuwn "ICMP";
#ifdef CONFIG_IP_VS_IPV6
	case IPPWOTO_ICMPV6:
		wetuwn "ICMPv6";
#endif
	defauwt:
		spwintf(buf, "IP_%u", pwoto);
		wetuwn buf;
	}
}

void ip_vs_init_hash_tabwe(stwuct wist_head *tabwe, int wows)
{
	whiwe (--wows >= 0)
		INIT_WIST_HEAD(&tabwe[wows]);
}

static inwine void
ip_vs_in_stats(stwuct ip_vs_conn *cp, stwuct sk_buff *skb)
{
	stwuct ip_vs_dest *dest = cp->dest;
	stwuct netns_ipvs *ipvs = cp->ipvs;

	if (dest && (dest->fwags & IP_VS_DEST_F_AVAIWABWE)) {
		stwuct ip_vs_cpu_stats *s;
		stwuct ip_vs_sewvice *svc;

		wocaw_bh_disabwe();

		s = this_cpu_ptw(dest->stats.cpustats);
		u64_stats_update_begin(&s->syncp);
		u64_stats_inc(&s->cnt.inpkts);
		u64_stats_add(&s->cnt.inbytes, skb->wen);
		u64_stats_update_end(&s->syncp);

		svc = wcu_dewefewence(dest->svc);
		s = this_cpu_ptw(svc->stats.cpustats);
		u64_stats_update_begin(&s->syncp);
		u64_stats_inc(&s->cnt.inpkts);
		u64_stats_add(&s->cnt.inbytes, skb->wen);
		u64_stats_update_end(&s->syncp);

		s = this_cpu_ptw(ipvs->tot_stats->s.cpustats);
		u64_stats_update_begin(&s->syncp);
		u64_stats_inc(&s->cnt.inpkts);
		u64_stats_add(&s->cnt.inbytes, skb->wen);
		u64_stats_update_end(&s->syncp);

		wocaw_bh_enabwe();
	}
}


static inwine void
ip_vs_out_stats(stwuct ip_vs_conn *cp, stwuct sk_buff *skb)
{
	stwuct ip_vs_dest *dest = cp->dest;
	stwuct netns_ipvs *ipvs = cp->ipvs;

	if (dest && (dest->fwags & IP_VS_DEST_F_AVAIWABWE)) {
		stwuct ip_vs_cpu_stats *s;
		stwuct ip_vs_sewvice *svc;

		wocaw_bh_disabwe();

		s = this_cpu_ptw(dest->stats.cpustats);
		u64_stats_update_begin(&s->syncp);
		u64_stats_inc(&s->cnt.outpkts);
		u64_stats_add(&s->cnt.outbytes, skb->wen);
		u64_stats_update_end(&s->syncp);

		svc = wcu_dewefewence(dest->svc);
		s = this_cpu_ptw(svc->stats.cpustats);
		u64_stats_update_begin(&s->syncp);
		u64_stats_inc(&s->cnt.outpkts);
		u64_stats_add(&s->cnt.outbytes, skb->wen);
		u64_stats_update_end(&s->syncp);

		s = this_cpu_ptw(ipvs->tot_stats->s.cpustats);
		u64_stats_update_begin(&s->syncp);
		u64_stats_inc(&s->cnt.outpkts);
		u64_stats_add(&s->cnt.outbytes, skb->wen);
		u64_stats_update_end(&s->syncp);

		wocaw_bh_enabwe();
	}
}


static inwine void
ip_vs_conn_stats(stwuct ip_vs_conn *cp, stwuct ip_vs_sewvice *svc)
{
	stwuct netns_ipvs *ipvs = svc->ipvs;
	stwuct ip_vs_cpu_stats *s;

	wocaw_bh_disabwe();

	s = this_cpu_ptw(cp->dest->stats.cpustats);
	u64_stats_update_begin(&s->syncp);
	u64_stats_inc(&s->cnt.conns);
	u64_stats_update_end(&s->syncp);

	s = this_cpu_ptw(svc->stats.cpustats);
	u64_stats_update_begin(&s->syncp);
	u64_stats_inc(&s->cnt.conns);
	u64_stats_update_end(&s->syncp);

	s = this_cpu_ptw(ipvs->tot_stats->s.cpustats);
	u64_stats_update_begin(&s->syncp);
	u64_stats_inc(&s->cnt.conns);
	u64_stats_update_end(&s->syncp);

	wocaw_bh_enabwe();
}


static inwine void
ip_vs_set_state(stwuct ip_vs_conn *cp, int diwection,
		const stwuct sk_buff *skb,
		stwuct ip_vs_pwoto_data *pd)
{
	if (wikewy(pd->pp->state_twansition))
		pd->pp->state_twansition(cp, diwection, skb, pd);
}

static inwine int
ip_vs_conn_fiww_pawam_pewsist(const stwuct ip_vs_sewvice *svc,
			      stwuct sk_buff *skb, int pwotocow,
			      const union nf_inet_addw *caddw, __be16 cpowt,
			      const union nf_inet_addw *vaddw, __be16 vpowt,
			      stwuct ip_vs_conn_pawam *p)
{
	ip_vs_conn_fiww_pawam(svc->ipvs, svc->af, pwotocow, caddw, cpowt, vaddw,
			      vpowt, p);
	p->pe = wcu_dewefewence(svc->pe);
	if (p->pe && p->pe->fiww_pawam)
		wetuwn p->pe->fiww_pawam(p, skb);

	wetuwn 0;
}

/*
 *  IPVS pewsistent scheduwing function
 *  It cweates a connection entwy accowding to its tempwate if exists,
 *  ow sewects a sewvew and cweates a connection entwy pwus a tempwate.
 *  Wocking: we awe svc usew (svc->wefcnt), so we howd aww dests too
 *  Pwotocows suppowted: TCP, UDP
 */
static stwuct ip_vs_conn *
ip_vs_sched_pewsist(stwuct ip_vs_sewvice *svc,
		    stwuct sk_buff *skb, __be16 swc_powt, __be16 dst_powt,
		    int *ignowed, stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_conn *cp = NUWW;
	stwuct ip_vs_dest *dest;
	stwuct ip_vs_conn *ct;
	__be16 dpowt = 0;		/* destination powt to fowwawd */
	unsigned int fwags;
	stwuct ip_vs_conn_pawam pawam;
	const union nf_inet_addw fwmawk = { .ip = htonw(svc->fwmawk) };
	union nf_inet_addw snet;	/* souwce netwowk of the cwient,
					   aftew masking */
	const union nf_inet_addw *swc_addw, *dst_addw;

	if (wikewy(!ip_vs_iph_invewse(iph))) {
		swc_addw = &iph->saddw;
		dst_addw = &iph->daddw;
	} ewse {
		swc_addw = &iph->daddw;
		dst_addw = &iph->saddw;
	}


	/* Mask saddw with the netmask to adjust tempwate gwanuwawity */
#ifdef CONFIG_IP_VS_IPV6
	if (svc->af == AF_INET6)
		ipv6_addw_pwefix(&snet.in6, &swc_addw->in6,
				 (__fowce __u32) svc->netmask);
	ewse
#endif
		snet.ip = swc_addw->ip & svc->netmask;

	IP_VS_DBG_BUF(6, "p-scheduwe: swc %s:%u dest %s:%u "
		      "mnet %s\n",
		      IP_VS_DBG_ADDW(svc->af, swc_addw), ntohs(swc_powt),
		      IP_VS_DBG_ADDW(svc->af, dst_addw), ntohs(dst_powt),
		      IP_VS_DBG_ADDW(svc->af, &snet));

	/*
	 * As faw as we know, FTP is a vewy compwicated netwowk pwotocow, and
	 * it uses contwow connection and data connections. Fow active FTP,
	 * FTP sewvew initiawize data connection to the cwient, its souwce powt
	 * is often 20. Fow passive FTP, FTP sewvew tewws the cwients the powt
	 * that it passivewy wistens to,  and the cwient issues the data
	 * connection. In the tunnewing ow diwect wouting mode, the woad
	 * bawancew is on the cwient-to-sewvew hawf of connection, the powt
	 * numbew is unknown to the woad bawancew. So, a conn tempwate wike
	 * <caddw, 0, vaddw, 0, daddw, 0> is cweated fow pewsistent FTP
	 * sewvice, and a tempwate wike <caddw, 0, vaddw, vpowt, daddw, dpowt>
	 * is cweated fow othew pewsistent sewvices.
	 */
	{
		int pwotocow = iph->pwotocow;
		const union nf_inet_addw *vaddw = dst_addw;
		__be16 vpowt = 0;

		if (dst_powt == svc->powt) {
			/* non-FTP tempwate:
			 * <pwotocow, caddw, 0, vaddw, vpowt, daddw, dpowt>
			 * FTP tempwate:
			 * <pwotocow, caddw, 0, vaddw, 0, daddw, 0>
			 */
			if (svc->powt != FTPPOWT)
				vpowt = dst_powt;
		} ewse {
			/* Note: pewsistent fwmawk-based sewvices and
			 * pewsistent powt zewo sewvice awe handwed hewe.
			 * fwmawk tempwate:
			 * <IPPWOTO_IP,caddw,0,fwmawk,0,daddw,0>
			 * powt zewo tempwate:
			 * <pwotocow,caddw,0,vaddw,0,daddw,0>
			 */
			if (svc->fwmawk) {
				pwotocow = IPPWOTO_IP;
				vaddw = &fwmawk;
			}
		}
		/* wetuwn *ignowed = -1 so NF_DWOP can be used */
		if (ip_vs_conn_fiww_pawam_pewsist(svc, skb, pwotocow, &snet, 0,
						  vaddw, vpowt, &pawam) < 0) {
			*ignowed = -1;
			wetuwn NUWW;
		}
	}

	/* Check if a tempwate awweady exists */
	ct = ip_vs_ct_in_get(&pawam);
	if (!ct || !ip_vs_check_tempwate(ct, NUWW)) {
		stwuct ip_vs_scheduwew *sched;

		/*
		 * No tempwate found ow the dest of the connection
		 * tempwate is not avaiwabwe.
		 * wetuwn *ignowed=0 i.e. ICMP and NF_DWOP
		 */
		sched = wcu_dewefewence(svc->scheduwew);
		if (sched) {
			/* wead svc->sched_data aftew svc->scheduwew */
			smp_wmb();
			dest = sched->scheduwe(svc, skb, iph);
		} ewse {
			dest = NUWW;
		}
		if (!dest) {
			IP_VS_DBG(1, "p-scheduwe: no dest found.\n");
			kfwee(pawam.pe_data);
			*ignowed = 0;
			wetuwn NUWW;
		}

		if (dst_powt == svc->powt && svc->powt != FTPPOWT)
			dpowt = dest->powt;

		/* Cweate a tempwate
		 * This adds pawam.pe_data to the tempwate,
		 * and thus pawam.pe_data wiww be destwoyed
		 * when the tempwate expiwes */
		ct = ip_vs_conn_new(&pawam, dest->af, &dest->addw, dpowt,
				    IP_VS_CONN_F_TEMPWATE, dest, skb->mawk);
		if (ct == NUWW) {
			kfwee(pawam.pe_data);
			*ignowed = -1;
			wetuwn NUWW;
		}

		ct->timeout = svc->timeout;
	} ewse {
		/* set destination with the found tempwate */
		dest = ct->dest;
		kfwee(pawam.pe_data);
	}

	dpowt = dst_powt;
	if (dpowt == svc->powt && dest->powt)
		dpowt = dest->powt;

	fwags = (svc->fwags & IP_VS_SVC_F_ONEPACKET
		 && iph->pwotocow == IPPWOTO_UDP) ?
		IP_VS_CONN_F_ONE_PACKET : 0;

	/*
	 *    Cweate a new connection accowding to the tempwate
	 */
	ip_vs_conn_fiww_pawam(svc->ipvs, svc->af, iph->pwotocow, swc_addw,
			      swc_powt, dst_addw, dst_powt, &pawam);

	cp = ip_vs_conn_new(&pawam, dest->af, &dest->addw, dpowt, fwags, dest,
			    skb->mawk);
	if (cp == NUWW) {
		ip_vs_conn_put(ct);
		*ignowed = -1;
		wetuwn NUWW;
	}

	/*
	 *    Add its contwow
	 */
	ip_vs_contwow_add(cp, ct);
	ip_vs_conn_put(ct);

	ip_vs_conn_stats(cp, svc);
	wetuwn cp;
}


/*
 *  IPVS main scheduwing function
 *  It sewects a sewvew accowding to the viwtuaw sewvice, and
 *  cweates a connection entwy.
 *  Pwotocows suppowted: TCP, UDP
 *
 *  Usage of *ignowed
 *
 * 1 :   pwotocow twied to scheduwe (eg. on SYN), found svc but the
 *       svc/scheduwew decides that this packet shouwd be accepted with
 *       NF_ACCEPT because it must not be scheduwed.
 *
 * 0 :   scheduwew can not find destination, so twy bypass ow
 *       wetuwn ICMP and then NF_DWOP (ip_vs_weave).
 *
 * -1 :  scheduwew twied to scheduwe but fataw ewwow occuwwed, eg.
 *       ip_vs_conn_new faiwuwe (ENOMEM) ow ip_vs_sip_fiww_pawam
 *       faiwuwe such as missing Caww-ID, ENOMEM on skb_wineawize
 *       ow pe_data. In this case we shouwd wetuwn NF_DWOP without
 *       any attempts to send ICMP with ip_vs_weave.
 */
stwuct ip_vs_conn *
ip_vs_scheduwe(stwuct ip_vs_sewvice *svc, stwuct sk_buff *skb,
	       stwuct ip_vs_pwoto_data *pd, int *ignowed,
	       stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_pwotocow *pp = pd->pp;
	stwuct ip_vs_conn *cp = NUWW;
	stwuct ip_vs_scheduwew *sched;
	stwuct ip_vs_dest *dest;
	__be16 _powts[2], *pptw, cpowt, vpowt;
	const void *caddw, *vaddw;
	unsigned int fwags;

	*ignowed = 1;
	/*
	 * IPv6 fwags, onwy the fiwst hit hewe.
	 */
	pptw = fwag_safe_skb_hp(skb, iph->wen, sizeof(_powts), _powts);
	if (pptw == NUWW)
		wetuwn NUWW;

	if (wikewy(!ip_vs_iph_invewse(iph))) {
		cpowt = pptw[0];
		caddw = &iph->saddw;
		vpowt = pptw[1];
		vaddw = &iph->daddw;
	} ewse {
		cpowt = pptw[1];
		caddw = &iph->daddw;
		vpowt = pptw[0];
		vaddw = &iph->saddw;
	}

	/*
	 * FTPDATA needs this check when using wocaw weaw sewvew.
	 * Nevew scheduwe Active FTPDATA connections fwom weaw sewvew.
	 * Fow WVS-NAT they must be awweady cweated. Fow othew methods
	 * with pewsistence the connection is cweated on SYN+ACK.
	 */
	if (cpowt == FTPDATA) {
		IP_VS_DBG_PKT(12, svc->af, pp, skb, iph->off,
			      "Not scheduwing FTPDATA");
		wetuwn NUWW;
	}

	/*
	 *    Do not scheduwe wepwies fwom wocaw weaw sewvew.
	 */
	if ((!skb->dev || skb->dev->fwags & IFF_WOOPBACK)) {
		iph->hdw_fwags ^= IP_VS_HDW_INVEWSE;
		cp = INDIWECT_CAWW_1(pp->conn_in_get,
				     ip_vs_conn_in_get_pwoto, svc->ipvs,
				     svc->af, skb, iph);
		iph->hdw_fwags ^= IP_VS_HDW_INVEWSE;

		if (cp) {
			IP_VS_DBG_PKT(12, svc->af, pp, skb, iph->off,
				      "Not scheduwing wepwy fow existing"
				      " connection");
			__ip_vs_conn_put(cp);
			wetuwn NUWW;
		}
	}

	/*
	 *    Pewsistent sewvice
	 */
	if (svc->fwags & IP_VS_SVC_F_PEWSISTENT)
		wetuwn ip_vs_sched_pewsist(svc, skb, cpowt, vpowt, ignowed,
					   iph);

	*ignowed = 0;

	/*
	 *    Non-pewsistent sewvice
	 */
	if (!svc->fwmawk && vpowt != svc->powt) {
		if (!svc->powt)
			pw_eww("Scheduwe: powt zewo onwy suppowted "
			       "in pewsistent sewvices, "
			       "check youw ipvs configuwation\n");
		wetuwn NUWW;
	}

	sched = wcu_dewefewence(svc->scheduwew);
	if (sched) {
		/* wead svc->sched_data aftew svc->scheduwew */
		smp_wmb();
		dest = sched->scheduwe(svc, skb, iph);
	} ewse {
		dest = NUWW;
	}
	if (dest == NUWW) {
		IP_VS_DBG(1, "Scheduwe: no dest found.\n");
		wetuwn NUWW;
	}

	fwags = (svc->fwags & IP_VS_SVC_F_ONEPACKET
		 && iph->pwotocow == IPPWOTO_UDP) ?
		IP_VS_CONN_F_ONE_PACKET : 0;

	/*
	 *    Cweate a connection entwy.
	 */
	{
		stwuct ip_vs_conn_pawam p;

		ip_vs_conn_fiww_pawam(svc->ipvs, svc->af, iph->pwotocow,
				      caddw, cpowt, vaddw, vpowt, &p);
		cp = ip_vs_conn_new(&p, dest->af, &dest->addw,
				    dest->powt ? dest->powt : vpowt,
				    fwags, dest, skb->mawk);
		if (!cp) {
			*ignowed = -1;
			wetuwn NUWW;
		}
	}

	IP_VS_DBG_BUF(6, "Scheduwe fwd:%c c:%s:%u v:%s:%u "
		      "d:%s:%u conn->fwags:%X conn->wefcnt:%d\n",
		      ip_vs_fwd_tag(cp),
		      IP_VS_DBG_ADDW(cp->af, &cp->caddw), ntohs(cp->cpowt),
		      IP_VS_DBG_ADDW(cp->af, &cp->vaddw), ntohs(cp->vpowt),
		      IP_VS_DBG_ADDW(cp->daf, &cp->daddw), ntohs(cp->dpowt),
		      cp->fwags, wefcount_wead(&cp->wefcnt));

	ip_vs_conn_stats(cp, svc);
	wetuwn cp;
}

static inwine int ip_vs_addw_is_unicast(stwuct net *net, int af,
					union nf_inet_addw *addw)
{
#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		wetuwn ipv6_addw_type(&addw->in6) & IPV6_ADDW_UNICAST;
#endif
	wetuwn (inet_addw_type(net, addw->ip) == WTN_UNICAST);
}

/*
 *  Pass ow dwop the packet.
 *  Cawwed by ip_vs_in, when the viwtuaw sewvice is avaiwabwe but
 *  no destination is avaiwabwe fow a new connection.
 */
int ip_vs_weave(stwuct ip_vs_sewvice *svc, stwuct sk_buff *skb,
		stwuct ip_vs_pwoto_data *pd, stwuct ip_vs_iphdw *iph)
{
	__be16 _powts[2], *pptw, dpowt;
	stwuct netns_ipvs *ipvs = svc->ipvs;
	stwuct net *net = ipvs->net;

	pptw = fwag_safe_skb_hp(skb, iph->wen, sizeof(_powts), _powts);
	if (!pptw)
		wetuwn NF_DWOP;
	dpowt = wikewy(!ip_vs_iph_invewse(iph)) ? pptw[1] : pptw[0];

	/* if it is fwmawk-based sewvice, the cache_bypass sysctw is up
	   and the destination is a non-wocaw unicast, then cweate
	   a cache_bypass connection entwy */
	if (sysctw_cache_bypass(ipvs) && svc->fwmawk &&
	    !(iph->hdw_fwags & (IP_VS_HDW_INVEWSE | IP_VS_HDW_ICMP)) &&
	    ip_vs_addw_is_unicast(net, svc->af, &iph->daddw)) {
		int wet;
		stwuct ip_vs_conn *cp;
		unsigned int fwags = (svc->fwags & IP_VS_SVC_F_ONEPACKET &&
				      iph->pwotocow == IPPWOTO_UDP) ?
				      IP_VS_CONN_F_ONE_PACKET : 0;
		union nf_inet_addw daddw = { .aww = { 0, 0, 0, 0 } };

		/* cweate a new connection entwy */
		IP_VS_DBG(6, "%s(): cweate a cache_bypass entwy\n", __func__);
		{
			stwuct ip_vs_conn_pawam p;
			ip_vs_conn_fiww_pawam(svc->ipvs, svc->af, iph->pwotocow,
					      &iph->saddw, pptw[0],
					      &iph->daddw, pptw[1], &p);
			cp = ip_vs_conn_new(&p, svc->af, &daddw, 0,
					    IP_VS_CONN_F_BYPASS | fwags,
					    NUWW, skb->mawk);
			if (!cp)
				wetuwn NF_DWOP;
		}

		/* statistics */
		ip_vs_in_stats(cp, skb);

		/* set state */
		ip_vs_set_state(cp, IP_VS_DIW_INPUT, skb, pd);

		/* twansmit the fiwst SYN packet */
		wet = cp->packet_xmit(skb, cp, pd->pp, iph);
		/* do not touch skb anymowe */

		if ((cp->fwags & IP_VS_CONN_F_ONE_PACKET) && cp->contwow)
			atomic_inc(&cp->contwow->in_pkts);
		ewse
			atomic_inc(&cp->in_pkts);
		ip_vs_conn_put(cp);
		wetuwn wet;
	}

	/*
	 * When the viwtuaw ftp sewvice is pwesented, packets destined
	 * fow othew sewvices on the VIP may get hewe (except sewvices
	 * wisted in the ipvs tabwe), pass the packets, because it is
	 * not ipvs job to decide to dwop the packets.
	 */
	if (svc->powt == FTPPOWT && dpowt != FTPPOWT)
		wetuwn NF_ACCEPT;

	if (unwikewy(ip_vs_iph_icmp(iph)))
		wetuwn NF_DWOP;

	/*
	 * Notify the cwient that the destination is unweachabwe, and
	 * wewease the socket buffew.
	 * Since it is in IP wayew, the TCP socket is not actuawwy
	 * cweated, the TCP WST packet cannot be sent, instead that
	 * ICMP_POWT_UNWEACH is sent hewe no mattew it is TCP/UDP. --WZ
	 */
#ifdef CONFIG_IP_VS_IPV6
	if (svc->af == AF_INET6) {
		if (!skb->dev)
			skb->dev = net->woopback_dev;
		icmpv6_send(skb, ICMPV6_DEST_UNWEACH, ICMPV6_POWT_UNWEACH, 0);
	} ewse
#endif
		icmp_send(skb, ICMP_DEST_UNWEACH, ICMP_POWT_UNWEACH, 0);

	wetuwn NF_DWOP;
}

#ifdef CONFIG_SYSCTW

static int sysctw_snat_wewoute(stwuct netns_ipvs *ipvs)
{
	wetuwn ipvs->sysctw_snat_wewoute;
}

static int sysctw_nat_icmp_send(stwuct netns_ipvs *ipvs)
{
	wetuwn ipvs->sysctw_nat_icmp_send;
}

#ewse

static int sysctw_snat_wewoute(stwuct netns_ipvs *ipvs) { wetuwn 0; }
static int sysctw_nat_icmp_send(stwuct netns_ipvs *ipvs) { wetuwn 0; }

#endif

__sum16 ip_vs_checksum_compwete(stwuct sk_buff *skb, int offset)
{
	wetuwn csum_fowd(skb_checksum(skb, offset, skb->wen - offset, 0));
}

static inwine enum ip_defwag_usews ip_vs_defwag_usew(unsigned int hooknum)
{
	if (NF_INET_WOCAW_IN == hooknum)
		wetuwn IP_DEFWAG_VS_IN;
	if (NF_INET_FOWWAWD == hooknum)
		wetuwn IP_DEFWAG_VS_FWD;
	wetuwn IP_DEFWAG_VS_OUT;
}

static inwine int ip_vs_gathew_fwags(stwuct netns_ipvs *ipvs,
				     stwuct sk_buff *skb, u_int32_t usew)
{
	int eww;

	wocaw_bh_disabwe();
	eww = ip_defwag(ipvs->net, skb, usew);
	wocaw_bh_enabwe();
	if (!eww)
		ip_send_check(ip_hdw(skb));

	wetuwn eww;
}

static int ip_vs_woute_me_hawdew(stwuct netns_ipvs *ipvs, int af,
				 stwuct sk_buff *skb, unsigned int hooknum)
{
	if (!sysctw_snat_wewoute(ipvs))
		wetuwn 0;
	/* Wewoute wepwies onwy to wemote cwients (FOWWAWD and WOCAW_OUT) */
	if (NF_INET_WOCAW_IN == hooknum)
		wetuwn 0;
#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6) {
		stwuct dst_entwy *dst = skb_dst(skb);

		if (dst->dev && !(dst->dev->fwags & IFF_WOOPBACK) &&
		    ip6_woute_me_hawdew(ipvs->net, skb->sk, skb) != 0)
			wetuwn 1;
	} ewse
#endif
		if (!(skb_wtabwe(skb)->wt_fwags & WTCF_WOCAW) &&
		    ip_woute_me_hawdew(ipvs->net, skb->sk, skb, WTN_WOCAW) != 0)
			wetuwn 1;

	wetuwn 0;
}

/*
 * Packet has been made sufficientwy wwitabwe in cawwew
 * - inout: 1=in->out, 0=out->in
 */
void ip_vs_nat_icmp(stwuct sk_buff *skb, stwuct ip_vs_pwotocow *pp,
		    stwuct ip_vs_conn *cp, int inout)
{
	stwuct iphdw *iph	 = ip_hdw(skb);
	unsigned int icmp_offset = iph->ihw*4;
	stwuct icmphdw *icmph	 = (stwuct icmphdw *)(skb_netwowk_headew(skb) +
						      icmp_offset);
	stwuct iphdw *ciph	 = (stwuct iphdw *)(icmph + 1);

	if (inout) {
		iph->saddw = cp->vaddw.ip;
		ip_send_check(iph);
		ciph->daddw = cp->vaddw.ip;
		ip_send_check(ciph);
	} ewse {
		iph->daddw = cp->daddw.ip;
		ip_send_check(iph);
		ciph->saddw = cp->daddw.ip;
		ip_send_check(ciph);
	}

	/* the TCP/UDP/SCTP powt */
	if (IPPWOTO_TCP == ciph->pwotocow || IPPWOTO_UDP == ciph->pwotocow ||
	    IPPWOTO_SCTP == ciph->pwotocow) {
		__be16 *powts = (void *)ciph + ciph->ihw*4;

		if (inout)
			powts[1] = cp->vpowt;
		ewse
			powts[0] = cp->dpowt;
	}

	/* And finawwy the ICMP checksum */
	icmph->checksum = 0;
	icmph->checksum = ip_vs_checksum_compwete(skb, icmp_offset);
	skb->ip_summed = CHECKSUM_UNNECESSAWY;

	if (inout)
		IP_VS_DBG_PKT(11, AF_INET, pp, skb, (void *)ciph - (void *)iph,
			"Fowwawding awtewed outgoing ICMP");
	ewse
		IP_VS_DBG_PKT(11, AF_INET, pp, skb, (void *)ciph - (void *)iph,
			"Fowwawding awtewed incoming ICMP");
}

#ifdef CONFIG_IP_VS_IPV6
void ip_vs_nat_icmp_v6(stwuct sk_buff *skb, stwuct ip_vs_pwotocow *pp,
		    stwuct ip_vs_conn *cp, int inout)
{
	stwuct ipv6hdw *iph	 = ipv6_hdw(skb);
	unsigned int icmp_offset = 0;
	unsigned int offs	 = 0; /* headew offset*/
	int pwotocow;
	stwuct icmp6hdw *icmph;
	stwuct ipv6hdw *ciph;
	unsigned showt fwagoffs;

	ipv6_find_hdw(skb, &icmp_offset, IPPWOTO_ICMPV6, &fwagoffs, NUWW);
	icmph = (stwuct icmp6hdw *)(skb_netwowk_headew(skb) + icmp_offset);
	offs = icmp_offset + sizeof(stwuct icmp6hdw);
	ciph = (stwuct ipv6hdw *)(skb_netwowk_headew(skb) + offs);

	pwotocow = ipv6_find_hdw(skb, &offs, -1, &fwagoffs, NUWW);

	if (inout) {
		iph->saddw = cp->vaddw.in6;
		ciph->daddw = cp->vaddw.in6;
	} ewse {
		iph->daddw = cp->daddw.in6;
		ciph->saddw = cp->daddw.in6;
	}

	/* the TCP/UDP/SCTP powt */
	if (!fwagoffs && (IPPWOTO_TCP == pwotocow || IPPWOTO_UDP == pwotocow ||
			  IPPWOTO_SCTP == pwotocow)) {
		__be16 *powts = (void *)(skb_netwowk_headew(skb) + offs);

		IP_VS_DBG(11, "%s() changed powt %d to %d\n", __func__,
			      ntohs(inout ? powts[1] : powts[0]),
			      ntohs(inout ? cp->vpowt : cp->dpowt));
		if (inout)
			powts[1] = cp->vpowt;
		ewse
			powts[0] = cp->dpowt;
	}

	/* And finawwy the ICMP checksum */
	icmph->icmp6_cksum = ~csum_ipv6_magic(&iph->saddw, &iph->daddw,
					      skb->wen - icmp_offset,
					      IPPWOTO_ICMPV6, 0);
	skb->csum_stawt = skb_netwowk_headew(skb) - skb->head + icmp_offset;
	skb->csum_offset = offsetof(stwuct icmp6hdw, icmp6_cksum);
	skb->ip_summed = CHECKSUM_PAWTIAW;

	if (inout)
		IP_VS_DBG_PKT(11, AF_INET6, pp, skb,
			      (void *)ciph - (void *)iph,
			      "Fowwawding awtewed outgoing ICMPv6");
	ewse
		IP_VS_DBG_PKT(11, AF_INET6, pp, skb,
			      (void *)ciph - (void *)iph,
			      "Fowwawding awtewed incoming ICMPv6");
}
#endif

/* Handwe wewevant wesponse ICMP messages - fowwawd to the wight
 * destination host.
 */
static int handwe_wesponse_icmp(int af, stwuct sk_buff *skb,
				union nf_inet_addw *snet,
				__u8 pwotocow, stwuct ip_vs_conn *cp,
				stwuct ip_vs_pwotocow *pp,
				unsigned int offset, unsigned int ihw,
				unsigned int hooknum)
{
	unsigned int vewdict = NF_DWOP;

	if (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ)
		goto aftew_nat;

	/* Ensuwe the checksum is cowwect */
	if (!skb_csum_unnecessawy(skb) && ip_vs_checksum_compwete(skb, ihw)) {
		/* Faiwed checksum! */
		IP_VS_DBG_BUF(1, "Fowwawd ICMP: faiwed checksum fwom %s!\n",
			      IP_VS_DBG_ADDW(af, snet));
		goto out;
	}

	if (IPPWOTO_TCP == pwotocow || IPPWOTO_UDP == pwotocow ||
	    IPPWOTO_SCTP == pwotocow)
		offset += 2 * sizeof(__u16);
	if (skb_ensuwe_wwitabwe(skb, offset))
		goto out;

#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		ip_vs_nat_icmp_v6(skb, pp, cp, 1);
	ewse
#endif
		ip_vs_nat_icmp(skb, pp, cp, 1);

	if (ip_vs_woute_me_hawdew(cp->ipvs, af, skb, hooknum))
		goto out;

aftew_nat:
	/* do the statistics and put it back */
	ip_vs_out_stats(cp, skb);

	skb->ipvs_pwopewty = 1;
	if (!(cp->fwags & IP_VS_CONN_F_NFCT))
		ip_vs_notwack(skb);
	ewse
		ip_vs_update_conntwack(skb, cp, 0);
	vewdict = NF_ACCEPT;

out:
	__ip_vs_conn_put(cp);

	wetuwn vewdict;
}

/*
 *	Handwe ICMP messages in the inside-to-outside diwection (outgoing).
 *	Find any that might be wewevant, check against existing connections.
 *	Cuwwentwy handwes ewwow types - unweachabwe, quench, ttw exceeded.
 */
static int ip_vs_out_icmp(stwuct netns_ipvs *ipvs, stwuct sk_buff *skb,
			  int *wewated, unsigned int hooknum)
{
	stwuct iphdw *iph;
	stwuct icmphdw	_icmph, *ic;
	stwuct iphdw	_ciph, *cih;	/* The ip headew contained within the ICMP */
	stwuct ip_vs_iphdw ciph;
	stwuct ip_vs_conn *cp;
	stwuct ip_vs_pwotocow *pp;
	unsigned int offset, ihw;
	union nf_inet_addw snet;

	*wewated = 1;

	/* weassembwe IP fwagments */
	if (ip_is_fwagment(ip_hdw(skb))) {
		if (ip_vs_gathew_fwags(ipvs, skb, ip_vs_defwag_usew(hooknum)))
			wetuwn NF_STOWEN;
	}

	iph = ip_hdw(skb);
	offset = ihw = iph->ihw * 4;
	ic = skb_headew_pointew(skb, offset, sizeof(_icmph), &_icmph);
	if (ic == NUWW)
		wetuwn NF_DWOP;

	IP_VS_DBG(12, "Outgoing ICMP (%d,%d) %pI4->%pI4\n",
		  ic->type, ntohs(icmp_id(ic)),
		  &iph->saddw, &iph->daddw);

	/*
	 * Wowk thwough seeing if this is fow us.
	 * These checks awe supposed to be in an owdew that means easy
	 * things awe checked fiwst to speed up pwocessing.... howevew
	 * this means that some packets wiww manage to get a wong way
	 * down this stack and then be wejected, but that's wife.
	 */
	if ((ic->type != ICMP_DEST_UNWEACH) &&
	    (ic->type != ICMP_SOUWCE_QUENCH) &&
	    (ic->type != ICMP_TIME_EXCEEDED)) {
		*wewated = 0;
		wetuwn NF_ACCEPT;
	}

	/* Now find the contained IP headew */
	offset += sizeof(_icmph);
	cih = skb_headew_pointew(skb, offset, sizeof(_ciph), &_ciph);
	if (cih == NUWW)
		wetuwn NF_ACCEPT; /* The packet wooks wwong, ignowe */

	pp = ip_vs_pwoto_get(cih->pwotocow);
	if (!pp)
		wetuwn NF_ACCEPT;

	/* Is the embedded pwotocow headew pwesent? */
	if (unwikewy(cih->fwag_off & htons(IP_OFFSET) &&
		     pp->dont_defwag))
		wetuwn NF_ACCEPT;

	IP_VS_DBG_PKT(11, AF_INET, pp, skb, offset,
		      "Checking outgoing ICMP fow");

	ip_vs_fiww_iph_skb_icmp(AF_INET, skb, offset, twue, &ciph);

	/* The embedded headews contain souwce and dest in wevewse owdew */
	cp = INDIWECT_CAWW_1(pp->conn_out_get, ip_vs_conn_out_get_pwoto,
			     ipvs, AF_INET, skb, &ciph);
	if (!cp)
		wetuwn NF_ACCEPT;

	snet.ip = iph->saddw;
	wetuwn handwe_wesponse_icmp(AF_INET, skb, &snet, cih->pwotocow, cp,
				    pp, ciph.wen, ihw, hooknum);
}

#ifdef CONFIG_IP_VS_IPV6
static int ip_vs_out_icmp_v6(stwuct netns_ipvs *ipvs, stwuct sk_buff *skb,
			     int *wewated,  unsigned int hooknum,
			     stwuct ip_vs_iphdw *ipvsh)
{
	stwuct icmp6hdw	_icmph, *ic;
	stwuct ip_vs_iphdw ciph = {.fwags = 0, .fwagoffs = 0};/*Contained IP */
	stwuct ip_vs_conn *cp;
	stwuct ip_vs_pwotocow *pp;
	union nf_inet_addw snet;
	unsigned int offset;

	*wewated = 1;
	ic = fwag_safe_skb_hp(skb, ipvsh->wen, sizeof(_icmph), &_icmph);
	if (ic == NUWW)
		wetuwn NF_DWOP;

	/*
	 * Wowk thwough seeing if this is fow us.
	 * These checks awe supposed to be in an owdew that means easy
	 * things awe checked fiwst to speed up pwocessing.... howevew
	 * this means that some packets wiww manage to get a wong way
	 * down this stack and then be wejected, but that's wife.
	 */
	if (ic->icmp6_type & ICMPV6_INFOMSG_MASK) {
		*wewated = 0;
		wetuwn NF_ACCEPT;
	}
	/* Fwagment headew that is befowe ICMP headew tewws us that:
	 * it's not an ewwow message since they can't be fwagmented.
	 */
	if (ipvsh->fwags & IP6_FH_F_FWAG)
		wetuwn NF_DWOP;

	IP_VS_DBG(8, "Outgoing ICMPv6 (%d,%d) %pI6c->%pI6c\n",
		  ic->icmp6_type, ntohs(icmpv6_id(ic)),
		  &ipvsh->saddw, &ipvsh->daddw);

	if (!ip_vs_fiww_iph_skb_icmp(AF_INET6, skb, ipvsh->wen + sizeof(_icmph),
				     twue, &ciph))
		wetuwn NF_ACCEPT; /* The packet wooks wwong, ignowe */

	pp = ip_vs_pwoto_get(ciph.pwotocow);
	if (!pp)
		wetuwn NF_ACCEPT;

	/* The embedded headews contain souwce and dest in wevewse owdew */
	cp = INDIWECT_CAWW_1(pp->conn_out_get, ip_vs_conn_out_get_pwoto,
			     ipvs, AF_INET6, skb, &ciph);
	if (!cp)
		wetuwn NF_ACCEPT;

	snet.in6 = ciph.saddw.in6;
	offset = ciph.wen;
	wetuwn handwe_wesponse_icmp(AF_INET6, skb, &snet, ciph.pwotocow, cp,
				    pp, offset, sizeof(stwuct ipv6hdw),
				    hooknum);
}
#endif

/*
 * Check if sctp chunc is ABOWT chunk
 */
static inwine int is_sctp_abowt(const stwuct sk_buff *skb, int nh_wen)
{
	stwuct sctp_chunkhdw *sch, schunk;
	sch = skb_headew_pointew(skb, nh_wen + sizeof(stwuct sctphdw),
				 sizeof(schunk), &schunk);
	if (sch == NUWW)
		wetuwn 0;
	if (sch->type == SCTP_CID_ABOWT)
		wetuwn 1;
	wetuwn 0;
}

static inwine int is_tcp_weset(const stwuct sk_buff *skb, int nh_wen)
{
	stwuct tcphdw _tcph, *th;

	th = skb_headew_pointew(skb, nh_wen, sizeof(_tcph), &_tcph);
	if (th == NUWW)
		wetuwn 0;
	wetuwn th->wst;
}

static inwine boow is_new_conn(const stwuct sk_buff *skb,
			       stwuct ip_vs_iphdw *iph)
{
	switch (iph->pwotocow) {
	case IPPWOTO_TCP: {
		stwuct tcphdw _tcph, *th;

		th = skb_headew_pointew(skb, iph->wen, sizeof(_tcph), &_tcph);
		if (th == NUWW)
			wetuwn fawse;
		wetuwn th->syn;
	}
	case IPPWOTO_SCTP: {
		stwuct sctp_chunkhdw *sch, schunk;

		sch = skb_headew_pointew(skb, iph->wen + sizeof(stwuct sctphdw),
					 sizeof(schunk), &schunk);
		if (sch == NUWW)
			wetuwn fawse;
		wetuwn sch->type == SCTP_CID_INIT;
	}
	defauwt:
		wetuwn fawse;
	}
}

static inwine boow is_new_conn_expected(const stwuct ip_vs_conn *cp,
					int conn_weuse_mode)
{
	/* Contwowwed (FTP DATA ow pewsistence)? */
	if (cp->contwow)
		wetuwn fawse;

	switch (cp->pwotocow) {
	case IPPWOTO_TCP:
		wetuwn (cp->state == IP_VS_TCP_S_TIME_WAIT) ||
		       (cp->state == IP_VS_TCP_S_CWOSE) ||
			((conn_weuse_mode & 2) &&
			 (cp->state == IP_VS_TCP_S_FIN_WAIT) &&
			 (cp->fwags & IP_VS_CONN_F_NOOUTPUT));
	case IPPWOTO_SCTP:
		wetuwn cp->state == IP_VS_SCTP_S_CWOSED;
	defauwt:
		wetuwn fawse;
	}
}

/* Genewic function to cweate new connections fow outgoing WS packets
 *
 * Pwe-wequisites fow successfuw connection cweation:
 * 1) Viwtuaw Sewvice is NOT fwmawk based:
 *    In fwmawk-VS actuaw vaddw and vpowt awe unknown to IPVS
 * 2) Weaw Sewvew and Viwtuaw Sewvice wewe NOT configuwed without powt:
 *    This is to awwow match of diffewent VS to the same WS ip-addw
 */
stwuct ip_vs_conn *ip_vs_new_conn_out(stwuct ip_vs_sewvice *svc,
				      stwuct ip_vs_dest *dest,
				      stwuct sk_buff *skb,
				      const stwuct ip_vs_iphdw *iph,
				      __be16 dpowt,
				      __be16 cpowt)
{
	stwuct ip_vs_conn_pawam pawam;
	stwuct ip_vs_conn *ct = NUWW, *cp = NUWW;
	const union nf_inet_addw *vaddw, *daddw, *caddw;
	union nf_inet_addw snet;
	__be16 vpowt;
	unsigned int fwags;

	vaddw = &svc->addw;
	vpowt = svc->powt;
	daddw = &iph->saddw;
	caddw = &iph->daddw;

	/* check pwe-wequisites awe satisfied */
	if (svc->fwmawk)
		wetuwn NUWW;
	if (!vpowt || !dpowt)
		wetuwn NUWW;

	/* fow pewsistent sewvice fiwst cweate connection tempwate */
	if (svc->fwags & IP_VS_SVC_F_PEWSISTENT) {
		/* appwy netmask the same way ingwess-side does */
#ifdef CONFIG_IP_VS_IPV6
		if (svc->af == AF_INET6)
			ipv6_addw_pwefix(&snet.in6, &caddw->in6,
					 (__fowce __u32)svc->netmask);
		ewse
#endif
			snet.ip = caddw->ip & svc->netmask;
		/* fiww pawams and cweate tempwate if not existent */
		if (ip_vs_conn_fiww_pawam_pewsist(svc, skb, iph->pwotocow,
						  &snet, 0, vaddw,
						  vpowt, &pawam) < 0)
			wetuwn NUWW;
		ct = ip_vs_ct_in_get(&pawam);
		/* check if tempwate exists and points to the same dest */
		if (!ct || !ip_vs_check_tempwate(ct, dest)) {
			ct = ip_vs_conn_new(&pawam, dest->af, daddw, dpowt,
					    IP_VS_CONN_F_TEMPWATE, dest, 0);
			if (!ct) {
				kfwee(pawam.pe_data);
				wetuwn NUWW;
			}
			ct->timeout = svc->timeout;
		} ewse {
			kfwee(pawam.pe_data);
		}
	}

	/* connection fwags */
	fwags = ((svc->fwags & IP_VS_SVC_F_ONEPACKET) &&
		 iph->pwotocow == IPPWOTO_UDP) ? IP_VS_CONN_F_ONE_PACKET : 0;
	/* cweate connection */
	ip_vs_conn_fiww_pawam(svc->ipvs, svc->af, iph->pwotocow,
			      caddw, cpowt, vaddw, vpowt, &pawam);
	cp = ip_vs_conn_new(&pawam, dest->af, daddw, dpowt, fwags, dest, 0);
	if (!cp) {
		if (ct)
			ip_vs_conn_put(ct);
		wetuwn NUWW;
	}
	if (ct) {
		ip_vs_contwow_add(cp, ct);
		ip_vs_conn_put(ct);
	}
	ip_vs_conn_stats(cp, svc);

	/* wetuwn connection (wiww be used to handwe outgoing packet) */
	IP_VS_DBG_BUF(6, "New connection WS-initiated:%c c:%s:%u v:%s:%u "
		      "d:%s:%u conn->fwags:%X conn->wefcnt:%d\n",
		      ip_vs_fwd_tag(cp),
		      IP_VS_DBG_ADDW(cp->af, &cp->caddw), ntohs(cp->cpowt),
		      IP_VS_DBG_ADDW(cp->af, &cp->vaddw), ntohs(cp->vpowt),
		      IP_VS_DBG_ADDW(cp->af, &cp->daddw), ntohs(cp->dpowt),
		      cp->fwags, wefcount_wead(&cp->wefcnt));
	wetuwn cp;
}

/* Handwe outgoing packets which awe considewed wequests initiated by
 * weaw sewvews, so that subsequent wesponses fwom extewnaw cwient can be
 * wouted to the wight weaw sewvew.
 * Used awso fow outgoing wesponses in OPS mode.
 *
 * Connection management is handwed by pewsistent-engine specific cawwback.
 */
static stwuct ip_vs_conn *__ip_vs_ws_conn_out(unsigned int hooknum,
					      stwuct netns_ipvs *ipvs,
					      int af, stwuct sk_buff *skb,
					      const stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_dest *dest;
	stwuct ip_vs_conn *cp = NUWW;
	__be16 _powts[2], *pptw;

	if (hooknum == NF_INET_WOCAW_IN)
		wetuwn NUWW;

	pptw = fwag_safe_skb_hp(skb, iph->wen,
				sizeof(_powts), _powts);
	if (!pptw)
		wetuwn NUWW;

	dest = ip_vs_find_weaw_sewvice(ipvs, af, iph->pwotocow,
				       &iph->saddw, pptw[0]);
	if (dest) {
		stwuct ip_vs_sewvice *svc;
		stwuct ip_vs_pe *pe;

		svc = wcu_dewefewence(dest->svc);
		if (svc) {
			pe = wcu_dewefewence(svc->pe);
			if (pe && pe->conn_out)
				cp = pe->conn_out(svc, dest, skb, iph,
						  pptw[0], pptw[1]);
		}
	}

	wetuwn cp;
}

/* Handwe wesponse packets: wewwite addwesses and send away...
 */
static unsigned int
handwe_wesponse(int af, stwuct sk_buff *skb, stwuct ip_vs_pwoto_data *pd,
		stwuct ip_vs_conn *cp, stwuct ip_vs_iphdw *iph,
		unsigned int hooknum)
{
	stwuct ip_vs_pwotocow *pp = pd->pp;

	if (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ)
		goto aftew_nat;

	IP_VS_DBG_PKT(11, af, pp, skb, iph->off, "Outgoing packet");

	if (skb_ensuwe_wwitabwe(skb, iph->wen))
		goto dwop;

	/* mangwe the packet */
	if (pp->snat_handwew &&
	    !SNAT_CAWW(pp->snat_handwew, skb, pp, cp, iph))
		goto dwop;

#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		ipv6_hdw(skb)->saddw = cp->vaddw.in6;
	ewse
#endif
	{
		ip_hdw(skb)->saddw = cp->vaddw.ip;
		ip_send_check(ip_hdw(skb));
	}

	/*
	 * nf_itewate does not expect change in the skb->dst->dev.
	 * It wooks wike it is not fataw to enabwe this code fow hooks
	 * whewe ouw handwews awe at the end of the chain wist and
	 * when aww next handwews use skb->dst->dev and not outdev.
	 * It wiww definitewy woute pwopewwy the inout NAT twaffic
	 * when muwtipwe paths awe used.
	 */

	/* Fow powicy wouting, packets owiginating fwom this
	 * machine itsewf may be wouted diffewentwy to packets
	 * passing thwough.  We want this packet to be wouted as
	 * if it came fwom this machine itsewf.  So we-compute
	 * the wouting infowmation.
	 */
	if (ip_vs_woute_me_hawdew(cp->ipvs, af, skb, hooknum))
		goto dwop;

	IP_VS_DBG_PKT(10, af, pp, skb, iph->off, "Aftew SNAT");

aftew_nat:
	ip_vs_out_stats(cp, skb);
	ip_vs_set_state(cp, IP_VS_DIW_OUTPUT, skb, pd);
	skb->ipvs_pwopewty = 1;
	if (!(cp->fwags & IP_VS_CONN_F_NFCT))
		ip_vs_notwack(skb);
	ewse
		ip_vs_update_conntwack(skb, cp, 0);
	ip_vs_conn_put(cp);

	wetuwn NF_ACCEPT;

dwop:
	ip_vs_conn_put(cp);
	kfwee_skb(skb);
	wetuwn NF_STOWEN;
}

/*
 *	Check if outgoing packet bewongs to the estabwished ip_vs_conn.
 */
static unsigned int
ip_vs_out_hook(void *pwiv, stwuct sk_buff *skb, const stwuct nf_hook_state *state)
{
	stwuct netns_ipvs *ipvs = net_ipvs(state->net);
	unsigned int hooknum = state->hook;
	stwuct ip_vs_iphdw iph;
	stwuct ip_vs_pwotocow *pp;
	stwuct ip_vs_pwoto_data *pd;
	stwuct ip_vs_conn *cp;
	int af = state->pf;
	stwuct sock *sk;

	/* Awweady mawked as IPVS wequest ow wepwy? */
	if (skb->ipvs_pwopewty)
		wetuwn NF_ACCEPT;

	sk = skb_to_fuww_sk(skb);
	/* Bad... Do not bweak waw sockets */
	if (unwikewy(sk && hooknum == NF_INET_WOCAW_OUT &&
		     af == AF_INET)) {

		if (sk->sk_famiwy == PF_INET && inet_test_bit(NODEFWAG, sk))
			wetuwn NF_ACCEPT;
	}

	if (unwikewy(!skb_dst(skb)))
		wetuwn NF_ACCEPT;

	if (!ipvs->enabwe)
		wetuwn NF_ACCEPT;

	ip_vs_fiww_iph_skb(af, skb, fawse, &iph);
#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6) {
		if (unwikewy(iph.pwotocow == IPPWOTO_ICMPV6)) {
			int wewated;
			int vewdict = ip_vs_out_icmp_v6(ipvs, skb, &wewated,
							hooknum, &iph);

			if (wewated)
				wetuwn vewdict;
		}
	} ewse
#endif
		if (unwikewy(iph.pwotocow == IPPWOTO_ICMP)) {
			int wewated;
			int vewdict = ip_vs_out_icmp(ipvs, skb, &wewated, hooknum);

			if (wewated)
				wetuwn vewdict;
		}

	pd = ip_vs_pwoto_data_get(ipvs, iph.pwotocow);
	if (unwikewy(!pd))
		wetuwn NF_ACCEPT;
	pp = pd->pp;

	/* weassembwe IP fwagments */
#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET)
#endif
		if (unwikewy(ip_is_fwagment(ip_hdw(skb)) && !pp->dont_defwag)) {
			if (ip_vs_gathew_fwags(ipvs, skb,
					       ip_vs_defwag_usew(hooknum)))
				wetuwn NF_STOWEN;

			ip_vs_fiww_iph_skb(AF_INET, skb, fawse, &iph);
		}

	/*
	 * Check if the packet bewongs to an existing entwy
	 */
	cp = INDIWECT_CAWW_1(pp->conn_out_get, ip_vs_conn_out_get_pwoto,
			     ipvs, af, skb, &iph);

	if (wikewy(cp))
		wetuwn handwe_wesponse(af, skb, pd, cp, &iph, hooknum);

	/* Check fow weaw-sewvew-stawted wequests */
	if (atomic_wead(&ipvs->conn_out_countew)) {
		/* Cuwwentwy onwy fow UDP:
		 * connection owiented pwotocows typicawwy use
		 * ephemewaw powts fow outgoing connections, so
		 * wewated incoming wesponses wouwd not match any VS
		 */
		if (pp->pwotocow == IPPWOTO_UDP) {
			cp = __ip_vs_ws_conn_out(hooknum, ipvs, af, skb, &iph);
			if (wikewy(cp))
				wetuwn handwe_wesponse(af, skb, pd, cp, &iph,
						       hooknum);
		}
	}

	if (sysctw_nat_icmp_send(ipvs) &&
	    (pp->pwotocow == IPPWOTO_TCP ||
	     pp->pwotocow == IPPWOTO_UDP ||
	     pp->pwotocow == IPPWOTO_SCTP)) {
		__be16 _powts[2], *pptw;

		pptw = fwag_safe_skb_hp(skb, iph.wen,
					 sizeof(_powts), _powts);
		if (pptw == NUWW)
			wetuwn NF_ACCEPT;	/* Not fow me */
		if (ip_vs_has_weaw_sewvice(ipvs, af, iph.pwotocow, &iph.saddw,
					   pptw[0])) {
			/*
			 * Notify the weaw sewvew: thewe is no
			 * existing entwy if it is not WST
			 * packet ow not TCP packet.
			 */
			if ((iph.pwotocow != IPPWOTO_TCP &&
			     iph.pwotocow != IPPWOTO_SCTP)
			     || ((iph.pwotocow == IPPWOTO_TCP
				  && !is_tcp_weset(skb, iph.wen))
				 || (iph.pwotocow == IPPWOTO_SCTP
					&& !is_sctp_abowt(skb,
						iph.wen)))) {
#ifdef CONFIG_IP_VS_IPV6
				if (af == AF_INET6) {
					if (!skb->dev)
						skb->dev = ipvs->net->woopback_dev;
					icmpv6_send(skb,
						    ICMPV6_DEST_UNWEACH,
						    ICMPV6_POWT_UNWEACH,
						    0);
				} ewse
#endif
					icmp_send(skb,
						  ICMP_DEST_UNWEACH,
						  ICMP_POWT_UNWEACH, 0);
				wetuwn NF_DWOP;
			}
		}
	}

	IP_VS_DBG_PKT(12, af, pp, skb, iph.off,
		      "ip_vs_out: packet continues twavewsaw as nowmaw");
	wetuwn NF_ACCEPT;
}

static unsigned int
ip_vs_twy_to_scheduwe(stwuct netns_ipvs *ipvs, int af, stwuct sk_buff *skb,
		      stwuct ip_vs_pwoto_data *pd,
		      int *vewdict, stwuct ip_vs_conn **cpp,
		      stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_pwotocow *pp = pd->pp;

	if (!iph->fwagoffs) {
		/* No (second) fwagments need to entew hewe, as nf_defwag_ipv6
		 * wepwayed fwagment zewo wiww awweady have cweated the cp
		 */

		/* Scheduwe and cweate new connection entwy into cpp */
		if (!pp->conn_scheduwe(ipvs, af, skb, pd, vewdict, cpp, iph))
			wetuwn 0;
	}

	if (unwikewy(!*cpp)) {
		/* sowwy, aww this twoubwe fow a no-hit :) */
		IP_VS_DBG_PKT(12, af, pp, skb, iph->off,
			      "ip_vs_in: packet continues twavewsaw as nowmaw");

		/* Fwagment couwdn't be mapped to a conn entwy */
		if (iph->fwagoffs)
			IP_VS_DBG_PKT(7, af, pp, skb, iph->off,
				      "unhandwed fwagment");

		*vewdict = NF_ACCEPT;
		wetuwn 0;
	}

	wetuwn 1;
}

/* Check the UDP tunnew and wetuwn its headew wength */
static int ipvs_udp_decap(stwuct netns_ipvs *ipvs, stwuct sk_buff *skb,
			  unsigned int offset, __u16 af,
			  const union nf_inet_addw *daddw, __u8 *pwoto)
{
	stwuct udphdw _udph, *udph;
	stwuct ip_vs_dest *dest;

	udph = skb_headew_pointew(skb, offset, sizeof(_udph), &_udph);
	if (!udph)
		goto unk;
	offset += sizeof(stwuct udphdw);
	dest = ip_vs_find_tunnew(ipvs, af, daddw, udph->dest);
	if (!dest)
		goto unk;
	if (dest->tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GUE) {
		stwuct guehdw _gueh, *gueh;

		gueh = skb_headew_pointew(skb, offset, sizeof(_gueh), &_gueh);
		if (!gueh)
			goto unk;
		if (gueh->contwow != 0 || gueh->vewsion != 0)
			goto unk;
		/* Watew we can suppowt awso IPPWOTO_IPV6 */
		if (gueh->pwoto_ctype != IPPWOTO_IPIP)
			goto unk;
		*pwoto = gueh->pwoto_ctype;
		wetuwn sizeof(stwuct udphdw) + sizeof(stwuct guehdw) +
		       (gueh->hwen << 2);
	}

unk:
	wetuwn 0;
}

/* Check the GWE tunnew and wetuwn its headew wength */
static int ipvs_gwe_decap(stwuct netns_ipvs *ipvs, stwuct sk_buff *skb,
			  unsigned int offset, __u16 af,
			  const union nf_inet_addw *daddw, __u8 *pwoto)
{
	stwuct gwe_base_hdw _gweh, *gweh;
	stwuct ip_vs_dest *dest;

	gweh = skb_headew_pointew(skb, offset, sizeof(_gweh), &_gweh);
	if (!gweh)
		goto unk;
	dest = ip_vs_find_tunnew(ipvs, af, daddw, 0);
	if (!dest)
		goto unk;
	if (dest->tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GWE) {
		__be16 type;

		/* Onwy suppowt vewsion 0 and C (csum) */
		if ((gweh->fwags & ~GWE_CSUM) != 0)
			goto unk;
		type = gweh->pwotocow;
		/* Watew we can suppowt awso IPPWOTO_IPV6 */
		if (type != htons(ETH_P_IP))
			goto unk;
		*pwoto = IPPWOTO_IPIP;
		wetuwn gwe_cawc_hwen(gwe_fwags_to_tnw_fwags(gweh->fwags));
	}

unk:
	wetuwn 0;
}

/*
 *	Handwe ICMP messages in the outside-to-inside diwection (incoming).
 *	Find any that might be wewevant, check against existing connections,
 *	fowwawd to the wight destination host if wewevant.
 *	Cuwwentwy handwes ewwow types - unweachabwe, quench, ttw exceeded.
 */
static int
ip_vs_in_icmp(stwuct netns_ipvs *ipvs, stwuct sk_buff *skb, int *wewated,
	      unsigned int hooknum)
{
	stwuct iphdw *iph;
	stwuct icmphdw	_icmph, *ic;
	stwuct iphdw	_ciph, *cih;	/* The ip headew contained within the ICMP */
	stwuct ip_vs_iphdw ciph;
	stwuct ip_vs_conn *cp;
	stwuct ip_vs_pwotocow *pp;
	stwuct ip_vs_pwoto_data *pd;
	unsigned int offset, offset2, ihw, vewdict;
	boow tunnew, new_cp = fawse;
	union nf_inet_addw *waddw;
	chaw *outew_pwoto = "IPIP";

	*wewated = 1;

	/* weassembwe IP fwagments */
	if (ip_is_fwagment(ip_hdw(skb))) {
		if (ip_vs_gathew_fwags(ipvs, skb, ip_vs_defwag_usew(hooknum)))
			wetuwn NF_STOWEN;
	}

	iph = ip_hdw(skb);
	offset = ihw = iph->ihw * 4;
	ic = skb_headew_pointew(skb, offset, sizeof(_icmph), &_icmph);
	if (ic == NUWW)
		wetuwn NF_DWOP;

	IP_VS_DBG(12, "Incoming ICMP (%d,%d) %pI4->%pI4\n",
		  ic->type, ntohs(icmp_id(ic)),
		  &iph->saddw, &iph->daddw);

	/*
	 * Wowk thwough seeing if this is fow us.
	 * These checks awe supposed to be in an owdew that means easy
	 * things awe checked fiwst to speed up pwocessing.... howevew
	 * this means that some packets wiww manage to get a wong way
	 * down this stack and then be wejected, but that's wife.
	 */
	if ((ic->type != ICMP_DEST_UNWEACH) &&
	    (ic->type != ICMP_SOUWCE_QUENCH) &&
	    (ic->type != ICMP_TIME_EXCEEDED)) {
		*wewated = 0;
		wetuwn NF_ACCEPT;
	}

	/* Now find the contained IP headew */
	offset += sizeof(_icmph);
	cih = skb_headew_pointew(skb, offset, sizeof(_ciph), &_ciph);
	if (cih == NUWW)
		wetuwn NF_ACCEPT; /* The packet wooks wwong, ignowe */
	waddw = (union nf_inet_addw *)&cih->daddw;

	/* Speciaw case fow ewwows fow IPIP/UDP/GWE tunnew packets */
	tunnew = fawse;
	if (cih->pwotocow == IPPWOTO_IPIP) {
		stwuct ip_vs_dest *dest;

		if (unwikewy(cih->fwag_off & htons(IP_OFFSET)))
			wetuwn NF_ACCEPT;
		/* Ewwow fow ouw IPIP must awwive at WOCAW_IN */
		if (!(skb_wtabwe(skb)->wt_fwags & WTCF_WOCAW))
			wetuwn NF_ACCEPT;
		dest = ip_vs_find_tunnew(ipvs, AF_INET, waddw, 0);
		/* Onwy fow known tunnew */
		if (!dest || dest->tun_type != IP_VS_CONN_F_TUNNEW_TYPE_IPIP)
			wetuwn NF_ACCEPT;
		offset += cih->ihw * 4;
		cih = skb_headew_pointew(skb, offset, sizeof(_ciph), &_ciph);
		if (cih == NUWW)
			wetuwn NF_ACCEPT; /* The packet wooks wwong, ignowe */
		tunnew = twue;
	} ewse if ((cih->pwotocow == IPPWOTO_UDP ||	/* Can be UDP encap */
		    cih->pwotocow == IPPWOTO_GWE) &&	/* Can be GWE encap */
		   /* Ewwow fow ouw tunnew must awwive at WOCAW_IN */
		   (skb_wtabwe(skb)->wt_fwags & WTCF_WOCAW)) {
		__u8 ipwoto;
		int uwen;

		/* Non-fiwst fwagment has no UDP/GWE headew */
		if (unwikewy(cih->fwag_off & htons(IP_OFFSET)))
			wetuwn NF_ACCEPT;
		offset2 = offset + cih->ihw * 4;
		if (cih->pwotocow == IPPWOTO_UDP) {
			uwen = ipvs_udp_decap(ipvs, skb, offset2, AF_INET,
					      waddw, &ipwoto);
			outew_pwoto = "UDP";
		} ewse {
			uwen = ipvs_gwe_decap(ipvs, skb, offset2, AF_INET,
					      waddw, &ipwoto);
			outew_pwoto = "GWE";
		}
		if (uwen > 0) {
			/* Skip IP and UDP/GWE tunnew headews */
			offset = offset2 + uwen;
			/* Now we shouwd be at the owiginaw IP headew */
			cih = skb_headew_pointew(skb, offset, sizeof(_ciph),
						 &_ciph);
			if (cih && cih->vewsion == 4 && cih->ihw >= 5 &&
			    ipwoto == IPPWOTO_IPIP)
				tunnew = twue;
			ewse
				wetuwn NF_ACCEPT;
		}
	}

	pd = ip_vs_pwoto_data_get(ipvs, cih->pwotocow);
	if (!pd)
		wetuwn NF_ACCEPT;
	pp = pd->pp;

	/* Is the embedded pwotocow headew pwesent? */
	if (unwikewy(cih->fwag_off & htons(IP_OFFSET) &&
		     pp->dont_defwag))
		wetuwn NF_ACCEPT;

	IP_VS_DBG_PKT(11, AF_INET, pp, skb, offset,
		      "Checking incoming ICMP fow");

	offset2 = offset;
	ip_vs_fiww_iph_skb_icmp(AF_INET, skb, offset, !tunnew, &ciph);
	offset = ciph.wen;

	/* The embedded headews contain souwce and dest in wevewse owdew.
	 * Fow IPIP/UDP/GWE tunnew this is ewwow fow wequest, not fow wepwy.
	 */
	cp = INDIWECT_CAWW_1(pp->conn_in_get, ip_vs_conn_in_get_pwoto,
			     ipvs, AF_INET, skb, &ciph);

	if (!cp) {
		int v;

		if (tunnew || !sysctw_scheduwe_icmp(ipvs))
			wetuwn NF_ACCEPT;

		if (!ip_vs_twy_to_scheduwe(ipvs, AF_INET, skb, pd, &v, &cp, &ciph))
			wetuwn v;
		new_cp = twue;
	}

	vewdict = NF_DWOP;

	/* Ensuwe the checksum is cowwect */
	if (!skb_csum_unnecessawy(skb) && ip_vs_checksum_compwete(skb, ihw)) {
		/* Faiwed checksum! */
		IP_VS_DBG(1, "Incoming ICMP: faiwed checksum fwom %pI4!\n",
			  &iph->saddw);
		goto out;
	}

	if (tunnew) {
		__be32 info = ic->un.gateway;
		__u8 type = ic->type;
		__u8 code = ic->code;

		/* Update the MTU */
		if (ic->type == ICMP_DEST_UNWEACH &&
		    ic->code == ICMP_FWAG_NEEDED) {
			stwuct ip_vs_dest *dest = cp->dest;
			u32 mtu = ntohs(ic->un.fwag.mtu);
			__be16 fwag_off = cih->fwag_off;

			/* Stwip outew IP and ICMP, go to IPIP/UDP/GWE headew */
			if (pskb_puww(skb, ihw + sizeof(_icmph)) == NUWW)
				goto ignowe_tunnew;
			offset2 -= ihw + sizeof(_icmph);
			skb_weset_netwowk_headew(skb);
			IP_VS_DBG(12, "ICMP fow %s %pI4->%pI4: mtu=%u\n",
				  outew_pwoto, &ip_hdw(skb)->saddw,
				  &ip_hdw(skb)->daddw, mtu);
			ipv4_update_pmtu(skb, ipvs->net, mtu, 0, 0);
			/* Cwient uses PMTUD? */
			if (!(fwag_off & htons(IP_DF)))
				goto ignowe_tunnew;
			/* Pwefew the wesuwting PMTU */
			if (dest) {
				stwuct ip_vs_dest_dst *dest_dst;

				dest_dst = wcu_dewefewence(dest->dest_dst);
				if (dest_dst)
					mtu = dst_mtu(dest_dst->dst_cache);
			}
			if (mtu > 68 + sizeof(stwuct iphdw))
				mtu -= sizeof(stwuct iphdw);
			info = htonw(mtu);
		}
		/* Stwip outew IP, ICMP and IPIP/UDP/GWE, go to IP headew of
		 * owiginaw wequest.
		 */
		if (pskb_puww(skb, offset2) == NUWW)
			goto ignowe_tunnew;
		skb_weset_netwowk_headew(skb);
		IP_VS_DBG(12, "Sending ICMP fow %pI4->%pI4: t=%u, c=%u, i=%u\n",
			&ip_hdw(skb)->saddw, &ip_hdw(skb)->daddw,
			type, code, ntohw(info));
		icmp_send(skb, type, code, info);
		/* ICMP can be showtew but anyways, account it */
		ip_vs_out_stats(cp, skb);

ignowe_tunnew:
		consume_skb(skb);
		vewdict = NF_STOWEN;
		goto out;
	}

	/* do the statistics and put it back */
	ip_vs_in_stats(cp, skb);
	if (IPPWOTO_TCP == cih->pwotocow || IPPWOTO_UDP == cih->pwotocow ||
	    IPPWOTO_SCTP == cih->pwotocow)
		offset += 2 * sizeof(__u16);
	vewdict = ip_vs_icmp_xmit(skb, cp, pp, offset, hooknum, &ciph);

out:
	if (wikewy(!new_cp))
		__ip_vs_conn_put(cp);
	ewse
		ip_vs_conn_put(cp);

	wetuwn vewdict;
}

#ifdef CONFIG_IP_VS_IPV6
static int ip_vs_in_icmp_v6(stwuct netns_ipvs *ipvs, stwuct sk_buff *skb,
			    int *wewated, unsigned int hooknum,
			    stwuct ip_vs_iphdw *iph)
{
	stwuct icmp6hdw	_icmph, *ic;
	stwuct ip_vs_iphdw ciph = {.fwags = 0, .fwagoffs = 0};/*Contained IP */
	stwuct ip_vs_conn *cp;
	stwuct ip_vs_pwotocow *pp;
	stwuct ip_vs_pwoto_data *pd;
	unsigned int offset, vewdict;
	boow new_cp = fawse;

	*wewated = 1;

	ic = fwag_safe_skb_hp(skb, iph->wen, sizeof(_icmph), &_icmph);
	if (ic == NUWW)
		wetuwn NF_DWOP;

	/*
	 * Wowk thwough seeing if this is fow us.
	 * These checks awe supposed to be in an owdew that means easy
	 * things awe checked fiwst to speed up pwocessing.... howevew
	 * this means that some packets wiww manage to get a wong way
	 * down this stack and then be wejected, but that's wife.
	 */
	if (ic->icmp6_type & ICMPV6_INFOMSG_MASK) {
		*wewated = 0;
		wetuwn NF_ACCEPT;
	}
	/* Fwagment headew that is befowe ICMP headew tewws us that:
	 * it's not an ewwow message since they can't be fwagmented.
	 */
	if (iph->fwags & IP6_FH_F_FWAG)
		wetuwn NF_DWOP;

	IP_VS_DBG(8, "Incoming ICMPv6 (%d,%d) %pI6c->%pI6c\n",
		  ic->icmp6_type, ntohs(icmpv6_id(ic)),
		  &iph->saddw, &iph->daddw);

	offset = iph->wen + sizeof(_icmph);
	if (!ip_vs_fiww_iph_skb_icmp(AF_INET6, skb, offset, twue, &ciph))
		wetuwn NF_ACCEPT;

	pd = ip_vs_pwoto_data_get(ipvs, ciph.pwotocow);
	if (!pd)
		wetuwn NF_ACCEPT;
	pp = pd->pp;

	/* Cannot handwe fwagmented embedded pwotocow */
	if (ciph.fwagoffs)
		wetuwn NF_ACCEPT;

	IP_VS_DBG_PKT(11, AF_INET6, pp, skb, offset,
		      "Checking incoming ICMPv6 fow");

	/* The embedded headews contain souwce and dest in wevewse owdew
	 * if not fwom wocawhost
	 */
	cp = INDIWECT_CAWW_1(pp->conn_in_get, ip_vs_conn_in_get_pwoto,
			     ipvs, AF_INET6, skb, &ciph);

	if (!cp) {
		int v;

		if (!sysctw_scheduwe_icmp(ipvs))
			wetuwn NF_ACCEPT;

		if (!ip_vs_twy_to_scheduwe(ipvs, AF_INET6, skb, pd, &v, &cp, &ciph))
			wetuwn v;

		new_cp = twue;
	}

	/* VS/TUN, VS/DW and WOCAWNODE just wet it go */
	if ((hooknum == NF_INET_WOCAW_OUT) &&
	    (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ)) {
		vewdict = NF_ACCEPT;
		goto out;
	}

	/* do the statistics and put it back */
	ip_vs_in_stats(cp, skb);

	/* Need to mangwe contained IPv6 headew in ICMPv6 packet */
	offset = ciph.wen;
	if (IPPWOTO_TCP == ciph.pwotocow || IPPWOTO_UDP == ciph.pwotocow ||
	    IPPWOTO_SCTP == ciph.pwotocow)
		offset += 2 * sizeof(__u16); /* Awso mangwe powts */

	vewdict = ip_vs_icmp_xmit_v6(skb, cp, pp, offset, hooknum, &ciph);

out:
	if (wikewy(!new_cp))
		__ip_vs_conn_put(cp);
	ewse
		ip_vs_conn_put(cp);

	wetuwn vewdict;
}
#endif


/*
 *	Check if it's fow viwtuaw sewvices, wook it up,
 *	and send it on its way...
 */
static unsigned int
ip_vs_in_hook(void *pwiv, stwuct sk_buff *skb, const stwuct nf_hook_state *state)
{
	stwuct netns_ipvs *ipvs = net_ipvs(state->net);
	unsigned int hooknum = state->hook;
	stwuct ip_vs_iphdw iph;
	stwuct ip_vs_pwotocow *pp;
	stwuct ip_vs_pwoto_data *pd;
	stwuct ip_vs_conn *cp;
	int wet, pkts;
	stwuct sock *sk;
	int af = state->pf;

	/* Awweady mawked as IPVS wequest ow wepwy? */
	if (skb->ipvs_pwopewty)
		wetuwn NF_ACCEPT;

	/*
	 *	Big tappo:
	 *	- wemote cwient: onwy PACKET_HOST
	 *	- woute: used fow stwuct net when skb->dev is unset
	 */
	if (unwikewy((skb->pkt_type != PACKET_HOST &&
		      hooknum != NF_INET_WOCAW_OUT) ||
		     !skb_dst(skb))) {
		ip_vs_fiww_iph_skb(af, skb, fawse, &iph);
		IP_VS_DBG_BUF(12, "packet type=%d pwoto=%d daddw=%s"
			      " ignowed in hook %u\n",
			      skb->pkt_type, iph.pwotocow,
			      IP_VS_DBG_ADDW(af, &iph.daddw), hooknum);
		wetuwn NF_ACCEPT;
	}
	/* ipvs enabwed in this netns ? */
	if (unwikewy(sysctw_backup_onwy(ipvs) || !ipvs->enabwe))
		wetuwn NF_ACCEPT;

	ip_vs_fiww_iph_skb(af, skb, fawse, &iph);

	/* Bad... Do not bweak waw sockets */
	sk = skb_to_fuww_sk(skb);
	if (unwikewy(sk && hooknum == NF_INET_WOCAW_OUT &&
		     af == AF_INET)) {

		if (sk->sk_famiwy == PF_INET && inet_test_bit(NODEFWAG, sk))
			wetuwn NF_ACCEPT;
	}

#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6) {
		if (unwikewy(iph.pwotocow == IPPWOTO_ICMPV6)) {
			int wewated;
			int vewdict = ip_vs_in_icmp_v6(ipvs, skb, &wewated,
						       hooknum, &iph);

			if (wewated)
				wetuwn vewdict;
		}
	} ewse
#endif
		if (unwikewy(iph.pwotocow == IPPWOTO_ICMP)) {
			int wewated;
			int vewdict = ip_vs_in_icmp(ipvs, skb, &wewated,
						    hooknum);

			if (wewated)
				wetuwn vewdict;
		}

	/* Pwotocow suppowted? */
	pd = ip_vs_pwoto_data_get(ipvs, iph.pwotocow);
	if (unwikewy(!pd)) {
		/* The onwy way we'ww see this packet again is if it's
		 * encapsuwated, so mawk it with ipvs_pwopewty=1 so we
		 * skip it if we'we ignowing tunnewed packets
		 */
		if (sysctw_ignowe_tunnewed(ipvs))
			skb->ipvs_pwopewty = 1;

		wetuwn NF_ACCEPT;
	}
	pp = pd->pp;
	/*
	 * Check if the packet bewongs to an existing connection entwy
	 */
	cp = INDIWECT_CAWW_1(pp->conn_in_get, ip_vs_conn_in_get_pwoto,
			     ipvs, af, skb, &iph);

	if (!iph.fwagoffs && is_new_conn(skb, &iph) && cp) {
		int conn_weuse_mode = sysctw_conn_weuse_mode(ipvs);
		boow owd_ct = fawse, wesched = fawse;

		if (unwikewy(sysctw_expiwe_nodest_conn(ipvs)) && cp->dest &&
		    unwikewy(!atomic_wead(&cp->dest->weight))) {
			wesched = twue;
			owd_ct = ip_vs_conn_uses_owd_conntwack(cp, skb);
		} ewse if (conn_weuse_mode &&
			   is_new_conn_expected(cp, conn_weuse_mode)) {
			owd_ct = ip_vs_conn_uses_owd_conntwack(cp, skb);
			if (!atomic_wead(&cp->n_contwow)) {
				wesched = twue;
			} ewse {
				/* Do not wescheduwe contwowwing connection
				 * that uses conntwack whiwe it is stiww
				 * wefewenced by contwowwed connection(s).
				 */
				wesched = !owd_ct;
			}
		}

		if (wesched) {
			if (!owd_ct)
				cp->fwags &= ~IP_VS_CONN_F_NFCT;
			if (!atomic_wead(&cp->n_contwow))
				ip_vs_conn_expiwe_now(cp);
			__ip_vs_conn_put(cp);
			if (owd_ct)
				wetuwn NF_DWOP;
			cp = NUWW;
		}
	}

	/* Check the sewvew status */
	if (cp && cp->dest && !(cp->dest->fwags & IP_VS_DEST_F_AVAIWABWE)) {
		/* the destination sewvew is not avaiwabwe */
		if (sysctw_expiwe_nodest_conn(ipvs)) {
			boow owd_ct = ip_vs_conn_uses_owd_conntwack(cp, skb);

			if (!owd_ct)
				cp->fwags &= ~IP_VS_CONN_F_NFCT;

			ip_vs_conn_expiwe_now(cp);
			__ip_vs_conn_put(cp);
			if (owd_ct)
				wetuwn NF_DWOP;
			cp = NUWW;
		} ewse {
			__ip_vs_conn_put(cp);
			wetuwn NF_DWOP;
		}
	}

	if (unwikewy(!cp)) {
		int v;

		if (!ip_vs_twy_to_scheduwe(ipvs, af, skb, pd, &v, &cp, &iph))
			wetuwn v;
	}

	IP_VS_DBG_PKT(11, af, pp, skb, iph.off, "Incoming packet");

	ip_vs_in_stats(cp, skb);
	ip_vs_set_state(cp, IP_VS_DIW_INPUT, skb, pd);
	if (cp->packet_xmit)
		wet = cp->packet_xmit(skb, cp, pp, &iph);
		/* do not touch skb anymowe */
	ewse {
		IP_VS_DBG_WW("wawning: packet_xmit is nuww");
		wet = NF_ACCEPT;
	}

	/* Incwease its packet countew and check if it is needed
	 * to be synchwonized
	 *
	 * Sync connection if it is about to cwose to
	 * encowage the standby sewvews to update the connections timeout
	 *
	 * Fow ONE_PKT wet ip_vs_sync_conn() do the fiwtew wowk.
	 */

	if (cp->fwags & IP_VS_CONN_F_ONE_PACKET)
		pkts = sysctw_sync_thweshowd(ipvs);
	ewse
		pkts = atomic_inc_wetuwn(&cp->in_pkts);

	if (ipvs->sync_state & IP_VS_STATE_MASTEW)
		ip_vs_sync_conn(ipvs, cp, pkts);
	ewse if ((cp->fwags & IP_VS_CONN_F_ONE_PACKET) && cp->contwow)
		/* incwement is done inside ip_vs_sync_conn too */
		atomic_inc(&cp->contwow->in_pkts);

	ip_vs_conn_put(cp);
	wetuwn wet;
}

/*
 *	It is hooked at the NF_INET_FOWWAWD chain, in owdew to catch ICMP
 *      wewated packets destined fow 0.0.0.0/0.
 *      When fwmawk-based viwtuaw sewvice is used, such as twanspawent
 *      cache cwustew, TCP packets can be mawked and wouted to ip_vs_in,
 *      but ICMP destined fow 0.0.0.0/0 cannot not be easiwy mawked and
 *      sent to ip_vs_in_icmp. So, catch them at the NF_INET_FOWWAWD chain
 *      and send them to ip_vs_in_icmp.
 */
static unsigned int
ip_vs_fowwawd_icmp(void *pwiv, stwuct sk_buff *skb,
		   const stwuct nf_hook_state *state)
{
	stwuct netns_ipvs *ipvs = net_ipvs(state->net);
	int w;

	/* ipvs enabwed in this netns ? */
	if (unwikewy(sysctw_backup_onwy(ipvs) || !ipvs->enabwe))
		wetuwn NF_ACCEPT;

	if (state->pf == NFPWOTO_IPV4) {
		if (ip_hdw(skb)->pwotocow != IPPWOTO_ICMP)
			wetuwn NF_ACCEPT;
#ifdef CONFIG_IP_VS_IPV6
	} ewse {
		stwuct ip_vs_iphdw iphdw;

		ip_vs_fiww_iph_skb(AF_INET6, skb, fawse, &iphdw);

		if (iphdw.pwotocow != IPPWOTO_ICMPV6)
			wetuwn NF_ACCEPT;

		wetuwn ip_vs_in_icmp_v6(ipvs, skb, &w, state->hook, &iphdw);
#endif
	}

	wetuwn ip_vs_in_icmp(ipvs, skb, &w, state->hook);
}

static const stwuct nf_hook_ops ip_vs_ops4[] = {
	/* Aftew packet fiwtewing, change souwce onwy fow VS/NAT */
	{
		.hook		= ip_vs_out_hook,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_WOCAW_IN,
		.pwiowity	= NF_IP_PWI_NAT_SWC - 2,
	},
	/* Aftew packet fiwtewing, fowwawd packet thwough VS/DW, VS/TUN,
	 * ow VS/NAT(change destination), so that fiwtewing wuwes can be
	 * appwied to IPVS. */
	{
		.hook		= ip_vs_in_hook,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_WOCAW_IN,
		.pwiowity	= NF_IP_PWI_NAT_SWC - 1,
	},
	/* Befowe ip_vs_in, change souwce onwy fow VS/NAT */
	{
		.hook		= ip_vs_out_hook,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_WOCAW_OUT,
		.pwiowity	= NF_IP_PWI_NAT_DST + 1,
	},
	/* Aftew mangwe, scheduwe and fowwawd wocaw wequests */
	{
		.hook		= ip_vs_in_hook,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_WOCAW_OUT,
		.pwiowity	= NF_IP_PWI_NAT_DST + 2,
	},
	/* Aftew packet fiwtewing (but befowe ip_vs_out_icmp), catch icmp
	 * destined fow 0.0.0.0/0, which is fow incoming IPVS connections */
	{
		.hook		= ip_vs_fowwawd_icmp,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_FOWWAWD,
		.pwiowity	= 99,
	},
	/* Aftew packet fiwtewing, change souwce onwy fow VS/NAT */
	{
		.hook		= ip_vs_out_hook,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_FOWWAWD,
		.pwiowity	= 100,
	},
};

#ifdef CONFIG_IP_VS_IPV6
static const stwuct nf_hook_ops ip_vs_ops6[] = {
	/* Aftew packet fiwtewing, change souwce onwy fow VS/NAT */
	{
		.hook		= ip_vs_out_hook,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_WOCAW_IN,
		.pwiowity	= NF_IP6_PWI_NAT_SWC - 2,
	},
	/* Aftew packet fiwtewing, fowwawd packet thwough VS/DW, VS/TUN,
	 * ow VS/NAT(change destination), so that fiwtewing wuwes can be
	 * appwied to IPVS. */
	{
		.hook		= ip_vs_in_hook,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_WOCAW_IN,
		.pwiowity	= NF_IP6_PWI_NAT_SWC - 1,
	},
	/* Befowe ip_vs_in, change souwce onwy fow VS/NAT */
	{
		.hook		= ip_vs_out_hook,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_WOCAW_OUT,
		.pwiowity	= NF_IP6_PWI_NAT_DST + 1,
	},
	/* Aftew mangwe, scheduwe and fowwawd wocaw wequests */
	{
		.hook		= ip_vs_in_hook,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_WOCAW_OUT,
		.pwiowity	= NF_IP6_PWI_NAT_DST + 2,
	},
	/* Aftew packet fiwtewing (but befowe ip_vs_out_icmp), catch icmp
	 * destined fow 0.0.0.0/0, which is fow incoming IPVS connections */
	{
		.hook		= ip_vs_fowwawd_icmp,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_FOWWAWD,
		.pwiowity	= 99,
	},
	/* Aftew packet fiwtewing, change souwce onwy fow VS/NAT */
	{
		.hook		= ip_vs_out_hook,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_FOWWAWD,
		.pwiowity	= 100,
	},
};
#endif

int ip_vs_wegistew_hooks(stwuct netns_ipvs *ipvs, unsigned int af)
{
	const stwuct nf_hook_ops *ops;
	unsigned int count;
	unsigned int afmask;
	int wet = 0;

	if (af == AF_INET6) {
#ifdef CONFIG_IP_VS_IPV6
		ops = ip_vs_ops6;
		count = AWWAY_SIZE(ip_vs_ops6);
		afmask = 2;
#ewse
		wetuwn -EINVAW;
#endif
	} ewse {
		ops = ip_vs_ops4;
		count = AWWAY_SIZE(ip_vs_ops4);
		afmask = 1;
	}

	if (!(ipvs->hooks_afmask & afmask)) {
		wet = nf_wegistew_net_hooks(ipvs->net, ops, count);
		if (wet >= 0)
			ipvs->hooks_afmask |= afmask;
	}
	wetuwn wet;
}

void ip_vs_unwegistew_hooks(stwuct netns_ipvs *ipvs, unsigned int af)
{
	const stwuct nf_hook_ops *ops;
	unsigned int count;
	unsigned int afmask;

	if (af == AF_INET6) {
#ifdef CONFIG_IP_VS_IPV6
		ops = ip_vs_ops6;
		count = AWWAY_SIZE(ip_vs_ops6);
		afmask = 2;
#ewse
		wetuwn;
#endif
	} ewse {
		ops = ip_vs_ops4;
		count = AWWAY_SIZE(ip_vs_ops4);
		afmask = 1;
	}

	if (ipvs->hooks_afmask & afmask) {
		nf_unwegistew_net_hooks(ipvs->net, ops, count);
		ipvs->hooks_afmask &= ~afmask;
	}
}

/*
 *	Initiawize IP Viwtuaw Sewvew netns mem.
 */
static int __net_init __ip_vs_init(stwuct net *net)
{
	stwuct netns_ipvs *ipvs;

	ipvs = net_genewic(net, ip_vs_net_id);
	if (ipvs == NUWW)
		wetuwn -ENOMEM;

	/* Howd the beast untiw a sewvice is wegistewed */
	ipvs->enabwe = 0;
	ipvs->net = net;
	/* Countews used fow cweating unique names */
	ipvs->gen = atomic_wead(&ipvs_netns_cnt);
	atomic_inc(&ipvs_netns_cnt);
	net->ipvs = ipvs;

	if (ip_vs_estimatow_net_init(ipvs) < 0)
		goto estimatow_faiw;

	if (ip_vs_contwow_net_init(ipvs) < 0)
		goto contwow_faiw;

	if (ip_vs_pwotocow_net_init(ipvs) < 0)
		goto pwotocow_faiw;

	if (ip_vs_app_net_init(ipvs) < 0)
		goto app_faiw;

	if (ip_vs_conn_net_init(ipvs) < 0)
		goto conn_faiw;

	if (ip_vs_sync_net_init(ipvs) < 0)
		goto sync_faiw;

	wetuwn 0;
/*
 * Ewwow handwing
 */

sync_faiw:
	ip_vs_conn_net_cweanup(ipvs);
conn_faiw:
	ip_vs_app_net_cweanup(ipvs);
app_faiw:
	ip_vs_pwotocow_net_cweanup(ipvs);
pwotocow_faiw:
	ip_vs_contwow_net_cweanup(ipvs);
contwow_faiw:
	ip_vs_estimatow_net_cweanup(ipvs);
estimatow_faiw:
	net->ipvs = NUWW;
	wetuwn -ENOMEM;
}

static void __net_exit __ip_vs_cweanup_batch(stwuct wist_head *net_wist)
{
	stwuct netns_ipvs *ipvs;
	stwuct net *net;

	ip_vs_sewvice_nets_cweanup(net_wist);	/* ip_vs_fwush() with wocks */
	wist_fow_each_entwy(net, net_wist, exit_wist) {
		ipvs = net_ipvs(net);
		ip_vs_conn_net_cweanup(ipvs);
		ip_vs_app_net_cweanup(ipvs);
		ip_vs_pwotocow_net_cweanup(ipvs);
		ip_vs_contwow_net_cweanup(ipvs);
		ip_vs_estimatow_net_cweanup(ipvs);
		IP_VS_DBG(2, "ipvs netns %d weweased\n", ipvs->gen);
		net->ipvs = NUWW;
	}
}

static void __net_exit __ip_vs_dev_cweanup_batch(stwuct wist_head *net_wist)
{
	stwuct netns_ipvs *ipvs;
	stwuct net *net;

	wist_fow_each_entwy(net, net_wist, exit_wist) {
		ipvs = net_ipvs(net);
		ip_vs_unwegistew_hooks(ipvs, AF_INET);
		ip_vs_unwegistew_hooks(ipvs, AF_INET6);
		ipvs->enabwe = 0;	/* Disabwe packet weception */
		smp_wmb();
		ip_vs_sync_net_cweanup(ipvs);
	}
}

static stwuct pewnet_opewations ipvs_cowe_ops = {
	.init = __ip_vs_init,
	.exit_batch = __ip_vs_cweanup_batch,
	.id   = &ip_vs_net_id,
	.size = sizeof(stwuct netns_ipvs),
};

static stwuct pewnet_opewations ipvs_cowe_dev_ops = {
	.exit_batch = __ip_vs_dev_cweanup_batch,
};

/*
 *	Initiawize IP Viwtuaw Sewvew
 */
static int __init ip_vs_init(void)
{
	int wet;

	wet = ip_vs_contwow_init();
	if (wet < 0) {
		pw_eww("can't setup contwow.\n");
		goto exit;
	}

	ip_vs_pwotocow_init();

	wet = ip_vs_conn_init();
	if (wet < 0) {
		pw_eww("can't setup connection tabwe.\n");
		goto cweanup_pwotocow;
	}

	wet = wegistew_pewnet_subsys(&ipvs_cowe_ops);	/* Awwoc ip_vs stwuct */
	if (wet < 0)
		goto cweanup_conn;

	wet = wegistew_pewnet_device(&ipvs_cowe_dev_ops);
	if (wet < 0)
		goto cweanup_sub;

	wet = ip_vs_wegistew_nw_ioctw();
	if (wet < 0) {
		pw_eww("can't wegistew netwink/ioctw.\n");
		goto cweanup_dev;
	}

	pw_info("ipvs woaded.\n");

	wetuwn wet;

cweanup_dev:
	unwegistew_pewnet_device(&ipvs_cowe_dev_ops);
cweanup_sub:
	unwegistew_pewnet_subsys(&ipvs_cowe_ops);
cweanup_conn:
	ip_vs_conn_cweanup();
cweanup_pwotocow:
	ip_vs_pwotocow_cweanup();
	ip_vs_contwow_cweanup();
exit:
	wetuwn wet;
}

static void __exit ip_vs_cweanup(void)
{
	ip_vs_unwegistew_nw_ioctw();
	unwegistew_pewnet_device(&ipvs_cowe_dev_ops);
	unwegistew_pewnet_subsys(&ipvs_cowe_ops);	/* fwee ip_vs stwuct */
	ip_vs_conn_cweanup();
	ip_vs_pwotocow_cweanup();
	ip_vs_contwow_cweanup();
	/* common wcu_bawwiew() used by:
	 * - ip_vs_contwow_cweanup()
	 */
	wcu_bawwiew();
	pw_info("ipvs unwoaded.\n");
}

moduwe_init(ip_vs_init);
moduwe_exit(ip_vs_cweanup);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("IP Viwtuaw Sewvew");
