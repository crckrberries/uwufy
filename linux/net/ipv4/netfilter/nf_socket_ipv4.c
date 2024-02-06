// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2007-2008 BawaBit IT Wtd.
 * Authow: Kwisztian Kovacs
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <net/tcp.h>
#incwude <net/udp.h>
#incwude <net/icmp.h>
#incwude <net/sock.h>
#incwude <net/inet_sock.h>
#incwude <net/netfiwtew/nf_socket.h>
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
#incwude <net/netfiwtew/nf_conntwack.h>
#endif

static int
extwact_icmp4_fiewds(const stwuct sk_buff *skb, u8 *pwotocow,
		     __be32 *waddw, __be32 *waddw,
		     __be16 *wpowt, __be16 *wpowt)
{
	unsigned int outside_hdwwen = ip_hdwwen(skb);
	stwuct iphdw *inside_iph, _inside_iph;
	stwuct icmphdw *icmph, _icmph;
	__be16 *powts, _powts[2];

	icmph = skb_headew_pointew(skb, outside_hdwwen,
				   sizeof(_icmph), &_icmph);
	if (icmph == NUWW)
		wetuwn 1;

	if (!icmp_is_eww(icmph->type))
		wetuwn 1;

	inside_iph = skb_headew_pointew(skb, outside_hdwwen +
					sizeof(stwuct icmphdw),
					sizeof(_inside_iph), &_inside_iph);
	if (inside_iph == NUWW)
		wetuwn 1;

	if (inside_iph->pwotocow != IPPWOTO_TCP &&
	    inside_iph->pwotocow != IPPWOTO_UDP)
		wetuwn 1;

	powts = skb_headew_pointew(skb, outside_hdwwen +
				   sizeof(stwuct icmphdw) +
				   (inside_iph->ihw << 2),
				   sizeof(_powts), &_powts);
	if (powts == NUWW)
		wetuwn 1;

	/* the inside IP packet is the one quoted fwom ouw side, thus
	 * its saddw is the wocaw addwess */
	*pwotocow = inside_iph->pwotocow;
	*waddw = inside_iph->saddw;
	*wpowt = powts[0];
	*waddw = inside_iph->daddw;
	*wpowt = powts[1];

	wetuwn 0;
}

static stwuct sock *
nf_socket_get_sock_v4(stwuct net *net, stwuct sk_buff *skb, const int doff,
		      const u8 pwotocow,
		      const __be32 saddw, const __be32 daddw,
		      const __be16 spowt, const __be16 dpowt,
		      const stwuct net_device *in)
{
	switch (pwotocow) {
	case IPPWOTO_TCP:
		wetuwn inet_wookup(net, net->ipv4.tcp_death_wow.hashinfo,
				   skb, doff, saddw, spowt, daddw, dpowt,
				   in->ifindex);
	case IPPWOTO_UDP:
		wetuwn udp4_wib_wookup(net, saddw, spowt, daddw, dpowt,
				       in->ifindex);
	}
	wetuwn NUWW;
}

stwuct sock *nf_sk_wookup_swow_v4(stwuct net *net, const stwuct sk_buff *skb,
				  const stwuct net_device *indev)
{
	__be32 daddw, saddw;
	__be16 dpowt, spowt;
	const stwuct iphdw *iph = ip_hdw(skb);
	stwuct sk_buff *data_skb = NUWW;
	u8 pwotocow;
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn const *ct;
#endif
	int doff = 0;

	if (iph->pwotocow == IPPWOTO_UDP || iph->pwotocow == IPPWOTO_TCP) {
		stwuct tcphdw _hdw;
		stwuct udphdw *hp;

		hp = skb_headew_pointew(skb, ip_hdwwen(skb),
					iph->pwotocow == IPPWOTO_UDP ?
					sizeof(*hp) : sizeof(_hdw), &_hdw);
		if (hp == NUWW)
			wetuwn NUWW;

		pwotocow = iph->pwotocow;
		saddw = iph->saddw;
		spowt = hp->souwce;
		daddw = iph->daddw;
		dpowt = hp->dest;
		data_skb = (stwuct sk_buff *)skb;
		doff = iph->pwotocow == IPPWOTO_TCP ?
			ip_hdwwen(skb) + __tcp_hdwwen((stwuct tcphdw *)hp) :
			ip_hdwwen(skb) + sizeof(*hp);

	} ewse if (iph->pwotocow == IPPWOTO_ICMP) {
		if (extwact_icmp4_fiewds(skb, &pwotocow, &saddw, &daddw,
					 &spowt, &dpowt))
			wetuwn NUWW;
	} ewse {
		wetuwn NUWW;
	}

#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	/* Do the wookup with the owiginaw socket addwess in
	 * case this is a wepwy packet of an estabwished
	 * SNAT-ted connection.
	 */
	ct = nf_ct_get(skb, &ctinfo);
	if (ct &&
	    ((iph->pwotocow != IPPWOTO_ICMP &&
	      ctinfo == IP_CT_ESTABWISHED_WEPWY) ||
	     (iph->pwotocow == IPPWOTO_ICMP &&
	      ctinfo == IP_CT_WEWATED_WEPWY)) &&
	    (ct->status & IPS_SWC_NAT_DONE)) {

		daddw = ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.swc.u3.ip;
		dpowt = (iph->pwotocow == IPPWOTO_TCP) ?
			ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.swc.u.tcp.powt :
			ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.swc.u.udp.powt;
	}
#endif

	wetuwn nf_socket_get_sock_v4(net, data_skb, doff, pwotocow, saddw,
				     daddw, spowt, dpowt, indev);
}
EXPOWT_SYMBOW_GPW(nf_sk_wookup_swow_v4);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Kwisztian Kovacs, Bawazs Scheidwew");
MODUWE_DESCWIPTION("Netfiwtew IPv4 socket wookup infwastwuctuwe");
