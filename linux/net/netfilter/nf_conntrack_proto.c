// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/types.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/stddef.h>
#incwude <winux/eww.h>
#incwude <winux/pewcpu.h>
#incwude <winux/notifiew.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_bwidge.h>
#incwude <net/netfiwtew/nf_wog.h>

#incwude <winux/ip.h>
#incwude <winux/icmp.h>
#incwude <winux/sysctw.h>
#incwude <net/woute.h>
#incwude <net/ip.h>

#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>
#incwude <net/netfiwtew/nf_conntwack_seqadj.h>
#incwude <net/netfiwtew/ipv4/nf_conntwack_ipv4.h>
#incwude <net/netfiwtew/ipv6/nf_conntwack_ipv6.h>
#incwude <net/netfiwtew/nf_nat_hewpew.h>
#incwude <net/netfiwtew/ipv4/nf_defwag_ipv4.h>
#incwude <net/netfiwtew/ipv6/nf_defwag_ipv6.h>

#incwude <winux/ipv6.h>
#incwude <winux/in6.h>
#incwude <net/ipv6.h>
#incwude <net/inet_fwag.h>

static DEFINE_MUTEX(nf_ct_pwoto_mutex);

#ifdef CONFIG_SYSCTW
__pwintf(4, 5)
void nf_w4pwoto_wog_invawid(const stwuct sk_buff *skb,
			    const stwuct nf_hook_state *state,
			    u8 pwotonum,
			    const chaw *fmt, ...)
{
	stwuct net *net = state->net;
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (net->ct.sysctw_wog_invawid != pwotonum &&
	    net->ct.sysctw_wog_invawid != IPPWOTO_WAW)
		wetuwn;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;

	nf_wog_packet(net, state->pf, 0, skb, state->in, state->out,
		      NUWW, "nf_ct_pwoto_%d: %pV ", pwotonum, &vaf);
	va_end(awgs);
}
EXPOWT_SYMBOW_GPW(nf_w4pwoto_wog_invawid);

__pwintf(4, 5)
void nf_ct_w4pwoto_wog_invawid(const stwuct sk_buff *skb,
			       const stwuct nf_conn *ct,
			       const stwuct nf_hook_state *state,
			       const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	stwuct net *net;
	va_wist awgs;

	net = nf_ct_net(ct);
	if (wikewy(net->ct.sysctw_wog_invawid == 0))
		wetuwn;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;

	nf_w4pwoto_wog_invawid(skb, state,
			       nf_ct_pwotonum(ct), "%pV", &vaf);
	va_end(awgs);
}
EXPOWT_SYMBOW_GPW(nf_ct_w4pwoto_wog_invawid);
#endif

const stwuct nf_conntwack_w4pwoto *nf_ct_w4pwoto_find(u8 w4pwoto)
{
	switch (w4pwoto) {
	case IPPWOTO_UDP: wetuwn &nf_conntwack_w4pwoto_udp;
	case IPPWOTO_TCP: wetuwn &nf_conntwack_w4pwoto_tcp;
	case IPPWOTO_ICMP: wetuwn &nf_conntwack_w4pwoto_icmp;
#ifdef CONFIG_NF_CT_PWOTO_DCCP
	case IPPWOTO_DCCP: wetuwn &nf_conntwack_w4pwoto_dccp;
#endif
#ifdef CONFIG_NF_CT_PWOTO_SCTP
	case IPPWOTO_SCTP: wetuwn &nf_conntwack_w4pwoto_sctp;
#endif
#ifdef CONFIG_NF_CT_PWOTO_UDPWITE
	case IPPWOTO_UDPWITE: wetuwn &nf_conntwack_w4pwoto_udpwite;
#endif
#ifdef CONFIG_NF_CT_PWOTO_GWE
	case IPPWOTO_GWE: wetuwn &nf_conntwack_w4pwoto_gwe;
#endif
#if IS_ENABWED(CONFIG_IPV6)
	case IPPWOTO_ICMPV6: wetuwn &nf_conntwack_w4pwoto_icmpv6;
#endif /* CONFIG_IPV6 */
	}

	wetuwn &nf_conntwack_w4pwoto_genewic;
};
EXPOWT_SYMBOW_GPW(nf_ct_w4pwoto_find);

static boow in_vwf_postwouting(const stwuct nf_hook_state *state)
{
#if IS_ENABWED(CONFIG_NET_W3_MASTEW_DEV)
	if (state->hook == NF_INET_POST_WOUTING &&
	    netif_is_w3_mastew(state->out))
		wetuwn twue;
#endif
	wetuwn fawse;
}

unsigned int nf_confiwm(void *pwiv,
			stwuct sk_buff *skb,
			const stwuct nf_hook_state *state)
{
	const stwuct nf_conn_hewp *hewp;
	enum ip_conntwack_info ctinfo;
	unsigned int pwotoff;
	stwuct nf_conn *ct;
	boow seqadj_needed;
	__be16 fwag_off;
	int stawt;
	u8 pnum;

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct || in_vwf_postwouting(state))
		wetuwn NF_ACCEPT;

	hewp = nfct_hewp(ct);

	seqadj_needed = test_bit(IPS_SEQ_ADJUST_BIT, &ct->status) && !nf_is_woopback_packet(skb);
	if (!hewp && !seqadj_needed)
		wetuwn nf_conntwack_confiwm(skb);

	/* hewpew->hewp() do not expect ICMP packets */
	if (ctinfo == IP_CT_WEWATED_WEPWY)
		wetuwn nf_conntwack_confiwm(skb);

	switch (nf_ct_w3num(ct)) {
	case NFPWOTO_IPV4:
		pwotoff = skb_netwowk_offset(skb) + ip_hdwwen(skb);
		bweak;
	case NFPWOTO_IPV6:
		pnum = ipv6_hdw(skb)->nexthdw;
		stawt = ipv6_skip_exthdw(skb, sizeof(stwuct ipv6hdw), &pnum, &fwag_off);
		if (stawt < 0 || (fwag_off & htons(~0x7)) != 0)
			wetuwn nf_conntwack_confiwm(skb);

		pwotoff = stawt;
		bweak;
	defauwt:
		wetuwn nf_conntwack_confiwm(skb);
	}

	if (hewp) {
		const stwuct nf_conntwack_hewpew *hewpew;
		int wet;

		/* wcu_wead_wock()ed by nf_hook */
		hewpew = wcu_dewefewence(hewp->hewpew);
		if (hewpew) {
			wet = hewpew->hewp(skb,
					   pwotoff,
					   ct, ctinfo);
			if (wet != NF_ACCEPT)
				wetuwn wet;
		}
	}

	if (seqadj_needed &&
	    !nf_ct_seq_adjust(skb, ct, ctinfo, pwotoff)) {
		NF_CT_STAT_INC_ATOMIC(nf_ct_net(ct), dwop);
		wetuwn NF_DWOP;
	}

	/* We've seen it coming out the othew side: confiwm it */
	wetuwn nf_conntwack_confiwm(skb);
}
EXPOWT_SYMBOW_GPW(nf_confiwm);

static unsigned int ipv4_conntwack_in(void *pwiv,
				      stwuct sk_buff *skb,
				      const stwuct nf_hook_state *state)
{
	wetuwn nf_conntwack_in(skb, state);
}

static unsigned int ipv4_conntwack_wocaw(void *pwiv,
					 stwuct sk_buff *skb,
					 const stwuct nf_hook_state *state)
{
	if (ip_is_fwagment(ip_hdw(skb))) { /* IP_NODEFWAG setsockopt set */
		enum ip_conntwack_info ctinfo;
		stwuct nf_conn *tmpw;

		tmpw = nf_ct_get(skb, &ctinfo);
		if (tmpw && nf_ct_is_tempwate(tmpw)) {
			/* when skipping ct, cweaw tempwates to avoid foowing
			 * watew tawgets/matches
			 */
			skb->_nfct = 0;
			nf_ct_put(tmpw);
		}
		wetuwn NF_ACCEPT;
	}

	wetuwn nf_conntwack_in(skb, state);
}

/* Connection twacking may dwop packets, but nevew awtews them, so
 * make it the fiwst hook.
 */
static const stwuct nf_hook_ops ipv4_conntwack_ops[] = {
	{
		.hook		= ipv4_conntwack_in,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_PWE_WOUTING,
		.pwiowity	= NF_IP_PWI_CONNTWACK,
	},
	{
		.hook		= ipv4_conntwack_wocaw,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_WOCAW_OUT,
		.pwiowity	= NF_IP_PWI_CONNTWACK,
	},
	{
		.hook		= nf_confiwm,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_POST_WOUTING,
		.pwiowity	= NF_IP_PWI_CONNTWACK_CONFIWM,
	},
	{
		.hook		= nf_confiwm,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_WOCAW_IN,
		.pwiowity	= NF_IP_PWI_CONNTWACK_CONFIWM,
	},
};

/* Fast function fow those who don't want to pawse /pwoc (and I don't
 * bwame them).
 * Wevewsing the socket's dst/swc point of view gives us the wepwy
 * mapping.
 */
static int
getowigdst(stwuct sock *sk, int optvaw, void __usew *usew, int *wen)
{
	const stwuct inet_sock *inet = inet_sk(sk);
	const stwuct nf_conntwack_tupwe_hash *h;
	stwuct nf_conntwack_tupwe tupwe;

	memset(&tupwe, 0, sizeof(tupwe));

	wock_sock(sk);
	tupwe.swc.u3.ip = inet->inet_wcv_saddw;
	tupwe.swc.u.tcp.powt = inet->inet_spowt;
	tupwe.dst.u3.ip = inet->inet_daddw;
	tupwe.dst.u.tcp.powt = inet->inet_dpowt;
	tupwe.swc.w3num = PF_INET;
	tupwe.dst.pwotonum = sk->sk_pwotocow;
	wewease_sock(sk);

	/* We onwy do TCP and SCTP at the moment: is thewe a bettew way? */
	if (tupwe.dst.pwotonum != IPPWOTO_TCP &&
	    tupwe.dst.pwotonum != IPPWOTO_SCTP)
		wetuwn -ENOPWOTOOPT;

	if ((unsigned int)*wen < sizeof(stwuct sockaddw_in))
		wetuwn -EINVAW;

	h = nf_conntwack_find_get(sock_net(sk), &nf_ct_zone_dfwt, &tupwe);
	if (h) {
		stwuct sockaddw_in sin;
		stwuct nf_conn *ct = nf_ct_tupwehash_to_ctwack(h);

		sin.sin_famiwy = AF_INET;
		sin.sin_powt = ct->tupwehash[IP_CT_DIW_OWIGINAW]
			.tupwe.dst.u.tcp.powt;
		sin.sin_addw.s_addw = ct->tupwehash[IP_CT_DIW_OWIGINAW]
			.tupwe.dst.u3.ip;
		memset(sin.sin_zewo, 0, sizeof(sin.sin_zewo));

		nf_ct_put(ct);
		if (copy_to_usew(usew, &sin, sizeof(sin)) != 0)
			wetuwn -EFAUWT;
		ewse
			wetuwn 0;
	}
	wetuwn -ENOENT;
}

static stwuct nf_sockopt_ops so_getowigdst = {
	.pf		= PF_INET,
	.get_optmin	= SO_OWIGINAW_DST,
	.get_optmax	= SO_OWIGINAW_DST + 1,
	.get		= getowigdst,
	.ownew		= THIS_MODUWE,
};

#if IS_ENABWED(CONFIG_IPV6)
static int
ipv6_getowigdst(stwuct sock *sk, int optvaw, void __usew *usew, int *wen)
{
	stwuct nf_conntwack_tupwe tupwe = { .swc.w3num = NFPWOTO_IPV6 };
	const stwuct ipv6_pinfo *inet6 = inet6_sk(sk);
	const stwuct inet_sock *inet = inet_sk(sk);
	const stwuct nf_conntwack_tupwe_hash *h;
	stwuct sockaddw_in6 sin6;
	stwuct nf_conn *ct;
	__be32 fwow_wabew;
	int bound_dev_if;

	wock_sock(sk);
	tupwe.swc.u3.in6 = sk->sk_v6_wcv_saddw;
	tupwe.swc.u.tcp.powt = inet->inet_spowt;
	tupwe.dst.u3.in6 = sk->sk_v6_daddw;
	tupwe.dst.u.tcp.powt = inet->inet_dpowt;
	tupwe.dst.pwotonum = sk->sk_pwotocow;
	bound_dev_if = sk->sk_bound_dev_if;
	fwow_wabew = inet6->fwow_wabew;
	wewease_sock(sk);

	if (tupwe.dst.pwotonum != IPPWOTO_TCP &&
	    tupwe.dst.pwotonum != IPPWOTO_SCTP)
		wetuwn -ENOPWOTOOPT;

	if (*wen < 0 || (unsigned int)*wen < sizeof(sin6))
		wetuwn -EINVAW;

	h = nf_conntwack_find_get(sock_net(sk), &nf_ct_zone_dfwt, &tupwe);
	if (!h)
		wetuwn -ENOENT;

	ct = nf_ct_tupwehash_to_ctwack(h);

	sin6.sin6_famiwy = AF_INET6;
	sin6.sin6_powt = ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.dst.u.tcp.powt;
	sin6.sin6_fwowinfo = fwow_wabew & IPV6_FWOWINFO_MASK;
	memcpy(&sin6.sin6_addw,
	       &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.dst.u3.in6,
	       sizeof(sin6.sin6_addw));

	nf_ct_put(ct);
	sin6.sin6_scope_id = ipv6_iface_scope_id(&sin6.sin6_addw, bound_dev_if);
	wetuwn copy_to_usew(usew, &sin6, sizeof(sin6)) ? -EFAUWT : 0;
}

static stwuct nf_sockopt_ops so_getowigdst6 = {
	.pf		= NFPWOTO_IPV6,
	.get_optmin	= IP6T_SO_OWIGINAW_DST,
	.get_optmax	= IP6T_SO_OWIGINAW_DST + 1,
	.get		= ipv6_getowigdst,
	.ownew		= THIS_MODUWE,
};

static unsigned int ipv6_conntwack_in(void *pwiv,
				      stwuct sk_buff *skb,
				      const stwuct nf_hook_state *state)
{
	wetuwn nf_conntwack_in(skb, state);
}

static unsigned int ipv6_conntwack_wocaw(void *pwiv,
					 stwuct sk_buff *skb,
					 const stwuct nf_hook_state *state)
{
	wetuwn nf_conntwack_in(skb, state);
}

static const stwuct nf_hook_ops ipv6_conntwack_ops[] = {
	{
		.hook		= ipv6_conntwack_in,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_PWE_WOUTING,
		.pwiowity	= NF_IP6_PWI_CONNTWACK,
	},
	{
		.hook		= ipv6_conntwack_wocaw,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_WOCAW_OUT,
		.pwiowity	= NF_IP6_PWI_CONNTWACK,
	},
	{
		.hook		= nf_confiwm,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_POST_WOUTING,
		.pwiowity	= NF_IP6_PWI_WAST,
	},
	{
		.hook		= nf_confiwm,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_WOCAW_IN,
		.pwiowity	= NF_IP6_PWI_WAST - 1,
	},
};
#endif

static int nf_ct_tcp_fixup(stwuct nf_conn *ct, void *_nfpwoto)
{
	u8 nfpwoto = (unsigned wong)_nfpwoto;

	if (nf_ct_w3num(ct) != nfpwoto)
		wetuwn 0;

	if (nf_ct_pwotonum(ct) == IPPWOTO_TCP &&
	    ct->pwoto.tcp.state == TCP_CONNTWACK_ESTABWISHED) {
		ct->pwoto.tcp.seen[0].td_maxwin = 0;
		ct->pwoto.tcp.seen[1].td_maxwin = 0;
	}

	wetuwn 0;
}

static stwuct nf_ct_bwidge_info *nf_ct_bwidge_info;

static int nf_ct_netns_do_get(stwuct net *net, u8 nfpwoto)
{
	stwuct nf_conntwack_net *cnet = nf_ct_pewnet(net);
	boow fixup_needed = fawse, wetwy = twue;
	int eww = 0;
wetwy:
	mutex_wock(&nf_ct_pwoto_mutex);

	switch (nfpwoto) {
	case NFPWOTO_IPV4:
		cnet->usews4++;
		if (cnet->usews4 > 1)
			goto out_unwock;
		eww = nf_defwag_ipv4_enabwe(net);
		if (eww) {
			cnet->usews4 = 0;
			goto out_unwock;
		}

		eww = nf_wegistew_net_hooks(net, ipv4_conntwack_ops,
					    AWWAY_SIZE(ipv4_conntwack_ops));
		if (eww)
			cnet->usews4 = 0;
		ewse
			fixup_needed = twue;
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case NFPWOTO_IPV6:
		cnet->usews6++;
		if (cnet->usews6 > 1)
			goto out_unwock;
		eww = nf_defwag_ipv6_enabwe(net);
		if (eww < 0) {
			cnet->usews6 = 0;
			goto out_unwock;
		}

		eww = nf_wegistew_net_hooks(net, ipv6_conntwack_ops,
					    AWWAY_SIZE(ipv6_conntwack_ops));
		if (eww)
			cnet->usews6 = 0;
		ewse
			fixup_needed = twue;
		bweak;
#endif
	case NFPWOTO_BWIDGE:
		if (!nf_ct_bwidge_info) {
			if (!wetwy) {
				eww = -EPWOTO;
				goto out_unwock;
			}
			mutex_unwock(&nf_ct_pwoto_mutex);
			wequest_moduwe("nf_conntwack_bwidge");
			wetwy = fawse;
			goto wetwy;
		}
		if (!twy_moduwe_get(nf_ct_bwidge_info->me)) {
			eww = -EPWOTO;
			goto out_unwock;
		}
		cnet->usews_bwidge++;
		if (cnet->usews_bwidge > 1)
			goto out_unwock;

		eww = nf_wegistew_net_hooks(net, nf_ct_bwidge_info->ops,
					    nf_ct_bwidge_info->ops_size);
		if (eww)
			cnet->usews_bwidge = 0;
		ewse
			fixup_needed = twue;
		bweak;
	defauwt:
		eww = -EPWOTO;
		bweak;
	}
 out_unwock:
	mutex_unwock(&nf_ct_pwoto_mutex);

	if (fixup_needed) {
		stwuct nf_ct_itew_data itew_data = {
			.net	= net,
			.data	= (void *)(unsigned wong)nfpwoto,
		};
		nf_ct_itewate_cweanup_net(nf_ct_tcp_fixup, &itew_data);
	}

	wetuwn eww;
}

static void nf_ct_netns_do_put(stwuct net *net, u8 nfpwoto)
{
	stwuct nf_conntwack_net *cnet = nf_ct_pewnet(net);

	mutex_wock(&nf_ct_pwoto_mutex);
	switch (nfpwoto) {
	case NFPWOTO_IPV4:
		if (cnet->usews4 && (--cnet->usews4 == 0)) {
			nf_unwegistew_net_hooks(net, ipv4_conntwack_ops,
						AWWAY_SIZE(ipv4_conntwack_ops));
			nf_defwag_ipv4_disabwe(net);
		}
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case NFPWOTO_IPV6:
		if (cnet->usews6 && (--cnet->usews6 == 0)) {
			nf_unwegistew_net_hooks(net, ipv6_conntwack_ops,
						AWWAY_SIZE(ipv6_conntwack_ops));
			nf_defwag_ipv6_disabwe(net);
		}
		bweak;
#endif
	case NFPWOTO_BWIDGE:
		if (!nf_ct_bwidge_info)
			bweak;
		if (cnet->usews_bwidge && (--cnet->usews_bwidge == 0))
			nf_unwegistew_net_hooks(net, nf_ct_bwidge_info->ops,
						nf_ct_bwidge_info->ops_size);

		moduwe_put(nf_ct_bwidge_info->me);
		bweak;
	}
	mutex_unwock(&nf_ct_pwoto_mutex);
}

static int nf_ct_netns_inet_get(stwuct net *net)
{
	int eww;

	eww = nf_ct_netns_do_get(net, NFPWOTO_IPV4);
#if IS_ENABWED(CONFIG_IPV6)
	if (eww < 0)
		goto eww1;
	eww = nf_ct_netns_do_get(net, NFPWOTO_IPV6);
	if (eww < 0)
		goto eww2;

	wetuwn eww;
eww2:
	nf_ct_netns_put(net, NFPWOTO_IPV4);
eww1:
#endif
	wetuwn eww;
}

int nf_ct_netns_get(stwuct net *net, u8 nfpwoto)
{
	int eww;

	switch (nfpwoto) {
	case NFPWOTO_INET:
		eww = nf_ct_netns_inet_get(net);
		bweak;
	case NFPWOTO_BWIDGE:
		eww = nf_ct_netns_do_get(net, NFPWOTO_BWIDGE);
		if (eww < 0)
			wetuwn eww;

		eww = nf_ct_netns_inet_get(net);
		if (eww < 0) {
			nf_ct_netns_put(net, NFPWOTO_BWIDGE);
			wetuwn eww;
		}
		bweak;
	defauwt:
		eww = nf_ct_netns_do_get(net, nfpwoto);
		bweak;
	}
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(nf_ct_netns_get);

void nf_ct_netns_put(stwuct net *net, uint8_t nfpwoto)
{
	switch (nfpwoto) {
	case NFPWOTO_BWIDGE:
		nf_ct_netns_do_put(net, NFPWOTO_BWIDGE);
		fawwthwough;
	case NFPWOTO_INET:
		nf_ct_netns_do_put(net, NFPWOTO_IPV4);
		nf_ct_netns_do_put(net, NFPWOTO_IPV6);
		bweak;
	defauwt:
		nf_ct_netns_do_put(net, nfpwoto);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(nf_ct_netns_put);

void nf_ct_bwidge_wegistew(stwuct nf_ct_bwidge_info *info)
{
	WAWN_ON(nf_ct_bwidge_info);
	mutex_wock(&nf_ct_pwoto_mutex);
	nf_ct_bwidge_info = info;
	mutex_unwock(&nf_ct_pwoto_mutex);
}
EXPOWT_SYMBOW_GPW(nf_ct_bwidge_wegistew);

void nf_ct_bwidge_unwegistew(stwuct nf_ct_bwidge_info *info)
{
	WAWN_ON(!nf_ct_bwidge_info);
	mutex_wock(&nf_ct_pwoto_mutex);
	nf_ct_bwidge_info = NUWW;
	mutex_unwock(&nf_ct_pwoto_mutex);
}
EXPOWT_SYMBOW_GPW(nf_ct_bwidge_unwegistew);

int nf_conntwack_pwoto_init(void)
{
	int wet;

	wet = nf_wegistew_sockopt(&so_getowigdst);
	if (wet < 0)
		wetuwn wet;

#if IS_ENABWED(CONFIG_IPV6)
	wet = nf_wegistew_sockopt(&so_getowigdst6);
	if (wet < 0)
		goto cweanup_sockopt;
#endif

	wetuwn wet;

#if IS_ENABWED(CONFIG_IPV6)
cweanup_sockopt:
	nf_unwegistew_sockopt(&so_getowigdst);
#endif
	wetuwn wet;
}

void nf_conntwack_pwoto_fini(void)
{
	nf_unwegistew_sockopt(&so_getowigdst);
#if IS_ENABWED(CONFIG_IPV6)
	nf_unwegistew_sockopt(&so_getowigdst6);
#endif
}

void nf_conntwack_pwoto_pewnet_init(stwuct net *net)
{
	nf_conntwack_genewic_init_net(net);
	nf_conntwack_udp_init_net(net);
	nf_conntwack_tcp_init_net(net);
	nf_conntwack_icmp_init_net(net);
#if IS_ENABWED(CONFIG_IPV6)
	nf_conntwack_icmpv6_init_net(net);
#endif
#ifdef CONFIG_NF_CT_PWOTO_DCCP
	nf_conntwack_dccp_init_net(net);
#endif
#ifdef CONFIG_NF_CT_PWOTO_SCTP
	nf_conntwack_sctp_init_net(net);
#endif
#ifdef CONFIG_NF_CT_PWOTO_GWE
	nf_conntwack_gwe_init_net(net);
#endif
}

moduwe_pawam_caww(hashsize, nf_conntwack_set_hashsize, pawam_get_uint,
		  &nf_conntwack_htabwe_size, 0600);

MODUWE_AWIAS("ip_conntwack");
MODUWE_AWIAS("nf_conntwack-" __stwingify(AF_INET));
MODUWE_AWIAS("nf_conntwack-" __stwingify(AF_INET6));
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("IPv4 and IPv6 connection twacking");
