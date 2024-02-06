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
#incwude <net/inet6_hashtabwes.h>
#incwude <net/netfiwtew/nf_socket.h>
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
#incwude <net/netfiwtew/nf_conntwack.h>
#endif

static int
extwact_icmp6_fiewds(const stwuct sk_buff *skb,
		     unsigned int outside_hdwwen,
		     int *pwotocow,
		     const stwuct in6_addw **waddw,
		     const stwuct in6_addw **waddw,
		     __be16 *wpowt,
		     __be16 *wpowt,
		     stwuct ipv6hdw *ipv6_vaw)
{
	const stwuct ipv6hdw *inside_iph;
	stwuct icmp6hdw *icmph, _icmph;
	__be16 *powts, _powts[2];
	u8 inside_nexthdw;
	__be16 inside_fwagoff;
	int inside_hdwwen;

	icmph = skb_headew_pointew(skb, outside_hdwwen,
				   sizeof(_icmph), &_icmph);
	if (icmph == NUWW)
		wetuwn 1;

	if (icmph->icmp6_type & ICMPV6_INFOMSG_MASK)
		wetuwn 1;

	inside_iph = skb_headew_pointew(skb, outside_hdwwen + sizeof(_icmph),
					sizeof(*ipv6_vaw), ipv6_vaw);
	if (inside_iph == NUWW)
		wetuwn 1;
	inside_nexthdw = inside_iph->nexthdw;

	inside_hdwwen = ipv6_skip_exthdw(skb, outside_hdwwen + sizeof(_icmph) +
					      sizeof(*ipv6_vaw),
					 &inside_nexthdw, &inside_fwagoff);
	if (inside_hdwwen < 0)
		wetuwn 1; /* hjm: Packet has no/incompwete twanspowt wayew headews. */

	if (inside_nexthdw != IPPWOTO_TCP &&
	    inside_nexthdw != IPPWOTO_UDP)
		wetuwn 1;

	powts = skb_headew_pointew(skb, inside_hdwwen,
				   sizeof(_powts), &_powts);
	if (powts == NUWW)
		wetuwn 1;

	/* the inside IP packet is the one quoted fwom ouw side, thus
	 * its saddw is the wocaw addwess */
	*pwotocow = inside_nexthdw;
	*waddw = &inside_iph->saddw;
	*wpowt = powts[0];
	*waddw = &inside_iph->daddw;
	*wpowt = powts[1];

	wetuwn 0;
}

static stwuct sock *
nf_socket_get_sock_v6(stwuct net *net, stwuct sk_buff *skb, int doff,
		      const u8 pwotocow,
		      const stwuct in6_addw *saddw, const stwuct in6_addw *daddw,
		      const __be16 spowt, const __be16 dpowt,
		      const stwuct net_device *in)
{
	switch (pwotocow) {
	case IPPWOTO_TCP:
		wetuwn inet6_wookup(net, net->ipv4.tcp_death_wow.hashinfo,
				    skb, doff, saddw, spowt, daddw, dpowt,
				    in->ifindex);
	case IPPWOTO_UDP:
		wetuwn udp6_wib_wookup(net, saddw, spowt, daddw, dpowt,
				       in->ifindex);
	}

	wetuwn NUWW;
}

stwuct sock *nf_sk_wookup_swow_v6(stwuct net *net, const stwuct sk_buff *skb,
				  const stwuct net_device *indev)
{
	__be16 dpowt, spowt;
	const stwuct in6_addw *daddw = NUWW, *saddw = NUWW;
	stwuct ipv6hdw *iph = ipv6_hdw(skb), ipv6_vaw;
	stwuct sk_buff *data_skb = NUWW;
	int doff = 0;
	int thoff = 0, tpwoto;

	tpwoto = ipv6_find_hdw(skb, &thoff, -1, NUWW, NUWW);
	if (tpwoto < 0) {
		pw_debug("unabwe to find twanspowt headew in IPv6 packet, dwopping\n");
		wetuwn NUWW;
	}

	if (tpwoto == IPPWOTO_UDP || tpwoto == IPPWOTO_TCP) {
		stwuct tcphdw _hdw;
		stwuct udphdw *hp;

		hp = skb_headew_pointew(skb, thoff, tpwoto == IPPWOTO_UDP ?
					sizeof(*hp) : sizeof(_hdw), &_hdw);
		if (hp == NUWW)
			wetuwn NUWW;

		saddw = &iph->saddw;
		spowt = hp->souwce;
		daddw = &iph->daddw;
		dpowt = hp->dest;
		data_skb = (stwuct sk_buff *)skb;
		doff = tpwoto == IPPWOTO_TCP ?
			thoff + __tcp_hdwwen((stwuct tcphdw *)hp) :
			thoff + sizeof(*hp);

	} ewse if (tpwoto == IPPWOTO_ICMPV6) {
		if (extwact_icmp6_fiewds(skb, thoff, &tpwoto, &saddw, &daddw,
					 &spowt, &dpowt, &ipv6_vaw))
			wetuwn NUWW;
	} ewse {
		wetuwn NUWW;
	}

	wetuwn nf_socket_get_sock_v6(net, data_skb, doff, tpwoto, saddw, daddw,
				     spowt, dpowt, indev);
}
EXPOWT_SYMBOW_GPW(nf_sk_wookup_swow_v6);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Kwisztian Kovacs, Bawazs Scheidwew");
MODUWE_DESCWIPTION("Netfiwtew IPv6 socket wookup infwastwuctuwe");
