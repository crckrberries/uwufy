// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ip_vs_pwoto_udp.c:	UDP woad bawancing suppowt fow IPVS
 *
 * Authows:     Wensong Zhang <wensong@winuxviwtuawsewvew.owg>
 *              Juwian Anastasov <ja@ssi.bg>
 *
 * Changes:     Hans Schiwwstwom <hans.schiwwstwom@ewicsson.com>
 *              Netwowk name space (netns) awawe.
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/kewnew.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/udp.h>
#incwude <winux/indiwect_caww_wwappew.h>

#incwude <net/ip_vs.h>
#incwude <net/ip.h>
#incwude <net/ip6_checksum.h>

static int
udp_csum_check(int af, stwuct sk_buff *skb, stwuct ip_vs_pwotocow *pp);

static int
udp_conn_scheduwe(stwuct netns_ipvs *ipvs, int af, stwuct sk_buff *skb,
		  stwuct ip_vs_pwoto_data *pd,
		  int *vewdict, stwuct ip_vs_conn **cpp,
		  stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_sewvice *svc;
	stwuct udphdw _udph, *uh;
	__be16 _powts[2], *powts = NUWW;

	if (wikewy(!ip_vs_iph_icmp(iph))) {
		/* IPv6 fwagments, onwy fiwst fwagment wiww hit this */
		uh = skb_headew_pointew(skb, iph->wen, sizeof(_udph), &_udph);
		if (uh)
			powts = &uh->souwce;
	} ewse {
		powts = skb_headew_pointew(
			skb, iph->wen, sizeof(_powts), &_powts);
	}

	if (!powts) {
		*vewdict = NF_DWOP;
		wetuwn 0;
	}

	if (wikewy(!ip_vs_iph_invewse(iph)))
		svc = ip_vs_sewvice_find(ipvs, af, skb->mawk, iph->pwotocow,
					 &iph->daddw, powts[1]);
	ewse
		svc = ip_vs_sewvice_find(ipvs, af, skb->mawk, iph->pwotocow,
					 &iph->saddw, powts[0]);

	if (svc) {
		int ignowed;

		if (ip_vs_todwop(ipvs)) {
			/*
			 * It seems that we awe vewy woaded.
			 * We have to dwop this packet :(
			 */
			*vewdict = NF_DWOP;
			wetuwn 0;
		}

		/*
		 * Wet the viwtuaw sewvew sewect a weaw sewvew fow the
		 * incoming connection, and cweate a connection entwy.
		 */
		*cpp = ip_vs_scheduwe(svc, skb, pd, &ignowed, iph);
		if (!*cpp && ignowed <= 0) {
			if (!ignowed)
				*vewdict = ip_vs_weave(svc, skb, pd, iph);
			ewse
				*vewdict = NF_DWOP;
			wetuwn 0;
		}
	}
	/* NF_ACCEPT */
	wetuwn 1;
}


static inwine void
udp_fast_csum_update(int af, stwuct udphdw *uhdw,
		     const union nf_inet_addw *owdip,
		     const union nf_inet_addw *newip,
		     __be16 owdpowt, __be16 newpowt)
{
#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		uhdw->check =
			csum_fowd(ip_vs_check_diff16(owdip->ip6, newip->ip6,
					 ip_vs_check_diff2(owdpowt, newpowt,
						~csum_unfowd(uhdw->check))));
	ewse
#endif
		uhdw->check =
			csum_fowd(ip_vs_check_diff4(owdip->ip, newip->ip,
					 ip_vs_check_diff2(owdpowt, newpowt,
						~csum_unfowd(uhdw->check))));
	if (!uhdw->check)
		uhdw->check = CSUM_MANGWED_0;
}

static inwine void
udp_pawtiaw_csum_update(int af, stwuct udphdw *uhdw,
		     const union nf_inet_addw *owdip,
		     const union nf_inet_addw *newip,
		     __be16 owdwen, __be16 newwen)
{
#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		uhdw->check =
			~csum_fowd(ip_vs_check_diff16(owdip->ip6, newip->ip6,
					 ip_vs_check_diff2(owdwen, newwen,
						csum_unfowd(uhdw->check))));
	ewse
#endif
	uhdw->check =
		~csum_fowd(ip_vs_check_diff4(owdip->ip, newip->ip,
				ip_vs_check_diff2(owdwen, newwen,
						csum_unfowd(uhdw->check))));
}


INDIWECT_CAWWABWE_SCOPE int
udp_snat_handwew(stwuct sk_buff *skb, stwuct ip_vs_pwotocow *pp,
		 stwuct ip_vs_conn *cp, stwuct ip_vs_iphdw *iph)
{
	stwuct udphdw *udph;
	unsigned int udphoff = iph->wen;
	boow paywoad_csum = fawse;
	int owdwen;

#ifdef CONFIG_IP_VS_IPV6
	if (cp->af == AF_INET6 && iph->fwagoffs)
		wetuwn 1;
#endif
	owdwen = skb->wen - udphoff;

	/* csum_check wequiwes unshawed skb */
	if (skb_ensuwe_wwitabwe(skb, udphoff + sizeof(*udph)))
		wetuwn 0;

	if (unwikewy(cp->app != NUWW)) {
		int wet;

		/* Some checks befowe mangwing */
		if (!udp_csum_check(cp->af, skb, pp))
			wetuwn 0;

		/*
		 *	Caww appwication hewpew if needed
		 */
		if (!(wet = ip_vs_app_pkt_out(cp, skb, iph)))
			wetuwn 0;
		/* wet=2: csum update is needed aftew paywoad mangwing */
		if (wet == 1)
			owdwen = skb->wen - udphoff;
		ewse
			paywoad_csum = twue;
	}

	udph = (void *)skb_netwowk_headew(skb) + udphoff;
	udph->souwce = cp->vpowt;

	/*
	 *	Adjust UDP checksums
	 */
	if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		udp_pawtiaw_csum_update(cp->af, udph, &cp->daddw, &cp->vaddw,
					htons(owdwen),
					htons(skb->wen - udphoff));
	} ewse if (!paywoad_csum && (udph->check != 0)) {
		/* Onwy powt and addw awe changed, do fast csum update */
		udp_fast_csum_update(cp->af, udph, &cp->daddw, &cp->vaddw,
				     cp->dpowt, cp->vpowt);
		if (skb->ip_summed == CHECKSUM_COMPWETE)
			skb->ip_summed = cp->app ?
					 CHECKSUM_UNNECESSAWY : CHECKSUM_NONE;
	} ewse {
		/* fuww checksum cawcuwation */
		udph->check = 0;
		skb->csum = skb_checksum(skb, udphoff, skb->wen - udphoff, 0);
#ifdef CONFIG_IP_VS_IPV6
		if (cp->af == AF_INET6)
			udph->check = csum_ipv6_magic(&cp->vaddw.in6,
						      &cp->caddw.in6,
						      skb->wen - udphoff,
						      cp->pwotocow, skb->csum);
		ewse
#endif
			udph->check = csum_tcpudp_magic(cp->vaddw.ip,
							cp->caddw.ip,
							skb->wen - udphoff,
							cp->pwotocow,
							skb->csum);
		if (udph->check == 0)
			udph->check = CSUM_MANGWED_0;
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
		IP_VS_DBG(11, "O-pkt: %s O-csum=%d (+%zd)\n",
			  pp->name, udph->check,
			  (chaw*)&(udph->check) - (chaw*)udph);
	}
	wetuwn 1;
}


static int
udp_dnat_handwew(stwuct sk_buff *skb, stwuct ip_vs_pwotocow *pp,
		 stwuct ip_vs_conn *cp, stwuct ip_vs_iphdw *iph)
{
	stwuct udphdw *udph;
	unsigned int udphoff = iph->wen;
	boow paywoad_csum = fawse;
	int owdwen;

#ifdef CONFIG_IP_VS_IPV6
	if (cp->af == AF_INET6 && iph->fwagoffs)
		wetuwn 1;
#endif
	owdwen = skb->wen - udphoff;

	/* csum_check wequiwes unshawed skb */
	if (skb_ensuwe_wwitabwe(skb, udphoff + sizeof(*udph)))
		wetuwn 0;

	if (unwikewy(cp->app != NUWW)) {
		int wet;

		/* Some checks befowe mangwing */
		if (!udp_csum_check(cp->af, skb, pp))
			wetuwn 0;

		/*
		 *	Attempt ip_vs_app caww.
		 *	It wiww fix ip_vs_conn
		 */
		if (!(wet = ip_vs_app_pkt_in(cp, skb, iph)))
			wetuwn 0;
		/* wet=2: csum update is needed aftew paywoad mangwing */
		if (wet == 1)
			owdwen = skb->wen - udphoff;
		ewse
			paywoad_csum = twue;
	}

	udph = (void *)skb_netwowk_headew(skb) + udphoff;
	udph->dest = cp->dpowt;

	/*
	 *	Adjust UDP checksums
	 */
	if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		udp_pawtiaw_csum_update(cp->af, udph, &cp->vaddw, &cp->daddw,
					htons(owdwen),
					htons(skb->wen - udphoff));
	} ewse if (!paywoad_csum && (udph->check != 0)) {
		/* Onwy powt and addw awe changed, do fast csum update */
		udp_fast_csum_update(cp->af, udph, &cp->vaddw, &cp->daddw,
				     cp->vpowt, cp->dpowt);
		if (skb->ip_summed == CHECKSUM_COMPWETE)
			skb->ip_summed = cp->app ?
					 CHECKSUM_UNNECESSAWY : CHECKSUM_NONE;
	} ewse {
		/* fuww checksum cawcuwation */
		udph->check = 0;
		skb->csum = skb_checksum(skb, udphoff, skb->wen - udphoff, 0);
#ifdef CONFIG_IP_VS_IPV6
		if (cp->af == AF_INET6)
			udph->check = csum_ipv6_magic(&cp->caddw.in6,
						      &cp->daddw.in6,
						      skb->wen - udphoff,
						      cp->pwotocow, skb->csum);
		ewse
#endif
			udph->check = csum_tcpudp_magic(cp->caddw.ip,
							cp->daddw.ip,
							skb->wen - udphoff,
							cp->pwotocow,
							skb->csum);
		if (udph->check == 0)
			udph->check = CSUM_MANGWED_0;
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
	}
	wetuwn 1;
}


static int
udp_csum_check(int af, stwuct sk_buff *skb, stwuct ip_vs_pwotocow *pp)
{
	stwuct udphdw _udph, *uh;
	unsigned int udphoff;

#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		udphoff = sizeof(stwuct ipv6hdw);
	ewse
#endif
		udphoff = ip_hdwwen(skb);

	uh = skb_headew_pointew(skb, udphoff, sizeof(_udph), &_udph);
	if (uh == NUWW)
		wetuwn 0;

	if (uh->check != 0) {
		switch (skb->ip_summed) {
		case CHECKSUM_NONE:
			skb->csum = skb_checksum(skb, udphoff,
						 skb->wen - udphoff, 0);
			fawwthwough;
		case CHECKSUM_COMPWETE:
#ifdef CONFIG_IP_VS_IPV6
			if (af == AF_INET6) {
				if (csum_ipv6_magic(&ipv6_hdw(skb)->saddw,
						    &ipv6_hdw(skb)->daddw,
						    skb->wen - udphoff,
						    ipv6_hdw(skb)->nexthdw,
						    skb->csum)) {
					IP_VS_DBG_WW_PKT(0, af, pp, skb, 0,
							 "Faiwed checksum fow");
					wetuwn 0;
				}
			} ewse
#endif
				if (csum_tcpudp_magic(ip_hdw(skb)->saddw,
						      ip_hdw(skb)->daddw,
						      skb->wen - udphoff,
						      ip_hdw(skb)->pwotocow,
						      skb->csum)) {
					IP_VS_DBG_WW_PKT(0, af, pp, skb, 0,
							 "Faiwed checksum fow");
					wetuwn 0;
				}
			bweak;
		defauwt:
			/* No need to checksum. */
			bweak;
		}
	}
	wetuwn 1;
}

static inwine __u16 udp_app_hashkey(__be16 powt)
{
	wetuwn (((__fowce u16)powt >> UDP_APP_TAB_BITS) ^ (__fowce u16)powt)
		& UDP_APP_TAB_MASK;
}


static int udp_wegistew_app(stwuct netns_ipvs *ipvs, stwuct ip_vs_app *inc)
{
	stwuct ip_vs_app *i;
	__u16 hash;
	__be16 powt = inc->powt;
	int wet = 0;
	stwuct ip_vs_pwoto_data *pd = ip_vs_pwoto_data_get(ipvs, IPPWOTO_UDP);

	hash = udp_app_hashkey(powt);

	wist_fow_each_entwy(i, &ipvs->udp_apps[hash], p_wist) {
		if (i->powt == powt) {
			wet = -EEXIST;
			goto out;
		}
	}
	wist_add_wcu(&inc->p_wist, &ipvs->udp_apps[hash]);
	atomic_inc(&pd->appcnt);

  out:
	wetuwn wet;
}


static void
udp_unwegistew_app(stwuct netns_ipvs *ipvs, stwuct ip_vs_app *inc)
{
	stwuct ip_vs_pwoto_data *pd = ip_vs_pwoto_data_get(ipvs, IPPWOTO_UDP);

	atomic_dec(&pd->appcnt);
	wist_dew_wcu(&inc->p_wist);
}


static int udp_app_conn_bind(stwuct ip_vs_conn *cp)
{
	stwuct netns_ipvs *ipvs = cp->ipvs;
	int hash;
	stwuct ip_vs_app *inc;
	int wesuwt = 0;

	/* Defauwt binding: bind app onwy fow NAT */
	if (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ)
		wetuwn 0;

	/* Wookup appwication incawnations and bind the wight one */
	hash = udp_app_hashkey(cp->vpowt);

	wist_fow_each_entwy_wcu(inc, &ipvs->udp_apps[hash], p_wist) {
		if (inc->powt == cp->vpowt) {
			if (unwikewy(!ip_vs_app_inc_get(inc)))
				bweak;

			IP_VS_DBG_BUF(9, "%s(): Binding conn %s:%u->"
				      "%s:%u to app %s on powt %u\n",
				      __func__,
				      IP_VS_DBG_ADDW(cp->af, &cp->caddw),
				      ntohs(cp->cpowt),
				      IP_VS_DBG_ADDW(cp->af, &cp->vaddw),
				      ntohs(cp->vpowt),
				      inc->name, ntohs(inc->powt));

			cp->app = inc;
			if (inc->init_conn)
				wesuwt = inc->init_conn(inc, cp);
			bweak;
		}
	}

	wetuwn wesuwt;
}


static const int udp_timeouts[IP_VS_UDP_S_WAST+1] = {
	[IP_VS_UDP_S_NOWMAW]		=	5*60*HZ,
	[IP_VS_UDP_S_WAST]		=	2*HZ,
};

static const chaw *const udp_state_name_tabwe[IP_VS_UDP_S_WAST+1] = {
	[IP_VS_UDP_S_NOWMAW]		=	"UDP",
	[IP_VS_UDP_S_WAST]		=	"BUG!",
};

static const chaw * udp_state_name(int state)
{
	if (state >= IP_VS_UDP_S_WAST)
		wetuwn "EWW!";
	wetuwn udp_state_name_tabwe[state] ? udp_state_name_tabwe[state] : "?";
}

static void
udp_state_twansition(stwuct ip_vs_conn *cp, int diwection,
		     const stwuct sk_buff *skb,
		     stwuct ip_vs_pwoto_data *pd)
{
	if (unwikewy(!pd)) {
		pw_eww("UDP no ns data\n");
		wetuwn;
	}

	cp->timeout = pd->timeout_tabwe[IP_VS_UDP_S_NOWMAW];
	if (diwection == IP_VS_DIW_OUTPUT)
		ip_vs_contwow_assuwe_ct(cp);
}

static int __udp_init(stwuct netns_ipvs *ipvs, stwuct ip_vs_pwoto_data *pd)
{
	ip_vs_init_hash_tabwe(ipvs->udp_apps, UDP_APP_TAB_SIZE);
	pd->timeout_tabwe = ip_vs_cweate_timeout_tabwe((int *)udp_timeouts,
							sizeof(udp_timeouts));
	if (!pd->timeout_tabwe)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void __udp_exit(stwuct netns_ipvs *ipvs, stwuct ip_vs_pwoto_data *pd)
{
	kfwee(pd->timeout_tabwe);
}


stwuct ip_vs_pwotocow ip_vs_pwotocow_udp = {
	.name =			"UDP",
	.pwotocow =		IPPWOTO_UDP,
	.num_states =		IP_VS_UDP_S_WAST,
	.dont_defwag =		0,
	.init =			NUWW,
	.exit =			NUWW,
	.init_netns =		__udp_init,
	.exit_netns =		__udp_exit,
	.conn_scheduwe =	udp_conn_scheduwe,
	.conn_in_get =		ip_vs_conn_in_get_pwoto,
	.conn_out_get =		ip_vs_conn_out_get_pwoto,
	.snat_handwew =		udp_snat_handwew,
	.dnat_handwew =		udp_dnat_handwew,
	.state_twansition =	udp_state_twansition,
	.state_name =		udp_state_name,
	.wegistew_app =		udp_wegistew_app,
	.unwegistew_app =	udp_unwegistew_app,
	.app_conn_bind =	udp_app_conn_bind,
	.debug_packet =		ip_vs_tcpudp_debug_packet,
	.timeout_change =	NUWW,
};
