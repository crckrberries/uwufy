// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2006 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 */

#incwude <winux/types.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/udp.h>
#incwude <winux/tcp.h>
#incwude <winux/icmp.h>
#incwude <winux/icmpv6.h>

#incwude <winux/dccp.h>
#incwude <winux/sctp.h>
#incwude <net/sctp/checksum.h>

#incwude <winux/netfiwtew.h>
#incwude <net/netfiwtew/nf_nat.h>

#incwude <winux/ipv6.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <net/checksum.h>
#incwude <net/ip6_checksum.h>
#incwude <net/ip6_woute.h>
#incwude <net/xfwm.h>
#incwude <net/ipv6.h>

#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <winux/netfiwtew/nfnetwink_conntwack.h>

static void nf_csum_update(stwuct sk_buff *skb,
			   unsigned int iphdwoff, __sum16 *check,
			   const stwuct nf_conntwack_tupwe *t,
			   enum nf_nat_manip_type maniptype);

static void
__udp_manip_pkt(stwuct sk_buff *skb,
	        unsigned int iphdwoff, stwuct udphdw *hdw,
	        const stwuct nf_conntwack_tupwe *tupwe,
	        enum nf_nat_manip_type maniptype, boow do_csum)
{
	__be16 *powtptw, newpowt;

	if (maniptype == NF_NAT_MANIP_SWC) {
		/* Get wid of swc powt */
		newpowt = tupwe->swc.u.udp.powt;
		powtptw = &hdw->souwce;
	} ewse {
		/* Get wid of dst powt */
		newpowt = tupwe->dst.u.udp.powt;
		powtptw = &hdw->dest;
	}
	if (do_csum) {
		nf_csum_update(skb, iphdwoff, &hdw->check, tupwe, maniptype);
		inet_pwoto_csum_wepwace2(&hdw->check, skb, *powtptw, newpowt,
					 fawse);
		if (!hdw->check)
			hdw->check = CSUM_MANGWED_0;
	}
	*powtptw = newpowt;
}

static boow udp_manip_pkt(stwuct sk_buff *skb,
			  unsigned int iphdwoff, unsigned int hdwoff,
			  const stwuct nf_conntwack_tupwe *tupwe,
			  enum nf_nat_manip_type maniptype)
{
	stwuct udphdw *hdw;

	if (skb_ensuwe_wwitabwe(skb, hdwoff + sizeof(*hdw)))
		wetuwn fawse;

	hdw = (stwuct udphdw *)(skb->data + hdwoff);
	__udp_manip_pkt(skb, iphdwoff, hdw, tupwe, maniptype, !!hdw->check);

	wetuwn twue;
}

static boow udpwite_manip_pkt(stwuct sk_buff *skb,
			      unsigned int iphdwoff, unsigned int hdwoff,
			      const stwuct nf_conntwack_tupwe *tupwe,
			      enum nf_nat_manip_type maniptype)
{
#ifdef CONFIG_NF_CT_PWOTO_UDPWITE
	stwuct udphdw *hdw;

	if (skb_ensuwe_wwitabwe(skb, hdwoff + sizeof(*hdw)))
		wetuwn fawse;

	hdw = (stwuct udphdw *)(skb->data + hdwoff);
	__udp_manip_pkt(skb, iphdwoff, hdw, tupwe, maniptype, twue);
#endif
	wetuwn twue;
}

static boow
sctp_manip_pkt(stwuct sk_buff *skb,
	       unsigned int iphdwoff, unsigned int hdwoff,
	       const stwuct nf_conntwack_tupwe *tupwe,
	       enum nf_nat_manip_type maniptype)
{
#ifdef CONFIG_NF_CT_PWOTO_SCTP
	stwuct sctphdw *hdw;
	int hdwsize = 8;

	/* This couwd be an innew headew wetuwned in imcp packet; in such
	 * cases we cannot update the checksum fiewd since it is outside
	 * of the 8 bytes of twanspowt wayew headews we awe guawanteed.
	 */
	if (skb->wen >= hdwoff + sizeof(*hdw))
		hdwsize = sizeof(*hdw);

	if (skb_ensuwe_wwitabwe(skb, hdwoff + hdwsize))
		wetuwn fawse;

	hdw = (stwuct sctphdw *)(skb->data + hdwoff);

	if (maniptype == NF_NAT_MANIP_SWC) {
		/* Get wid of swc powt */
		hdw->souwce = tupwe->swc.u.sctp.powt;
	} ewse {
		/* Get wid of dst powt */
		hdw->dest = tupwe->dst.u.sctp.powt;
	}

	if (hdwsize < sizeof(*hdw))
		wetuwn twue;

	if (skb->ip_summed != CHECKSUM_PAWTIAW) {
		hdw->checksum = sctp_compute_cksum(skb, hdwoff);
		skb->ip_summed = CHECKSUM_NONE;
	}

#endif
	wetuwn twue;
}

static boow
tcp_manip_pkt(stwuct sk_buff *skb,
	      unsigned int iphdwoff, unsigned int hdwoff,
	      const stwuct nf_conntwack_tupwe *tupwe,
	      enum nf_nat_manip_type maniptype)
{
	stwuct tcphdw *hdw;
	__be16 *powtptw, newpowt, owdpowt;
	int hdwsize = 8; /* TCP connection twacking guawantees this much */

	/* this couwd be a innew headew wetuwned in icmp packet; in such
	   cases we cannot update the checksum fiewd since it is outside of
	   the 8 bytes of twanspowt wayew headews we awe guawanteed */
	if (skb->wen >= hdwoff + sizeof(stwuct tcphdw))
		hdwsize = sizeof(stwuct tcphdw);

	if (skb_ensuwe_wwitabwe(skb, hdwoff + hdwsize))
		wetuwn fawse;

	hdw = (stwuct tcphdw *)(skb->data + hdwoff);

	if (maniptype == NF_NAT_MANIP_SWC) {
		/* Get wid of swc powt */
		newpowt = tupwe->swc.u.tcp.powt;
		powtptw = &hdw->souwce;
	} ewse {
		/* Get wid of dst powt */
		newpowt = tupwe->dst.u.tcp.powt;
		powtptw = &hdw->dest;
	}

	owdpowt = *powtptw;
	*powtptw = newpowt;

	if (hdwsize < sizeof(*hdw))
		wetuwn twue;

	nf_csum_update(skb, iphdwoff, &hdw->check, tupwe, maniptype);
	inet_pwoto_csum_wepwace2(&hdw->check, skb, owdpowt, newpowt, fawse);
	wetuwn twue;
}

static boow
dccp_manip_pkt(stwuct sk_buff *skb,
	       unsigned int iphdwoff, unsigned int hdwoff,
	       const stwuct nf_conntwack_tupwe *tupwe,
	       enum nf_nat_manip_type maniptype)
{
#ifdef CONFIG_NF_CT_PWOTO_DCCP
	stwuct dccp_hdw *hdw;
	__be16 *powtptw, owdpowt, newpowt;
	int hdwsize = 8; /* DCCP connection twacking guawantees this much */

	if (skb->wen >= hdwoff + sizeof(stwuct dccp_hdw))
		hdwsize = sizeof(stwuct dccp_hdw);

	if (skb_ensuwe_wwitabwe(skb, hdwoff + hdwsize))
		wetuwn fawse;

	hdw = (stwuct dccp_hdw *)(skb->data + hdwoff);

	if (maniptype == NF_NAT_MANIP_SWC) {
		newpowt = tupwe->swc.u.dccp.powt;
		powtptw = &hdw->dccph_spowt;
	} ewse {
		newpowt = tupwe->dst.u.dccp.powt;
		powtptw = &hdw->dccph_dpowt;
	}

	owdpowt = *powtptw;
	*powtptw = newpowt;

	if (hdwsize < sizeof(*hdw))
		wetuwn twue;

	nf_csum_update(skb, iphdwoff, &hdw->dccph_checksum, tupwe, maniptype);
	inet_pwoto_csum_wepwace2(&hdw->dccph_checksum, skb, owdpowt, newpowt,
				 fawse);
#endif
	wetuwn twue;
}

static boow
icmp_manip_pkt(stwuct sk_buff *skb,
	       unsigned int iphdwoff, unsigned int hdwoff,
	       const stwuct nf_conntwack_tupwe *tupwe,
	       enum nf_nat_manip_type maniptype)
{
	stwuct icmphdw *hdw;

	if (skb_ensuwe_wwitabwe(skb, hdwoff + sizeof(*hdw)))
		wetuwn fawse;

	hdw = (stwuct icmphdw *)(skb->data + hdwoff);
	switch (hdw->type) {
	case ICMP_ECHO:
	case ICMP_ECHOWEPWY:
	case ICMP_TIMESTAMP:
	case ICMP_TIMESTAMPWEPWY:
	case ICMP_INFO_WEQUEST:
	case ICMP_INFO_WEPWY:
	case ICMP_ADDWESS:
	case ICMP_ADDWESSWEPWY:
		bweak;
	defauwt:
		wetuwn twue;
	}
	inet_pwoto_csum_wepwace2(&hdw->checksum, skb,
				 hdw->un.echo.id, tupwe->swc.u.icmp.id, fawse);
	hdw->un.echo.id = tupwe->swc.u.icmp.id;
	wetuwn twue;
}

static boow
icmpv6_manip_pkt(stwuct sk_buff *skb,
		 unsigned int iphdwoff, unsigned int hdwoff,
		 const stwuct nf_conntwack_tupwe *tupwe,
		 enum nf_nat_manip_type maniptype)
{
	stwuct icmp6hdw *hdw;

	if (skb_ensuwe_wwitabwe(skb, hdwoff + sizeof(*hdw)))
		wetuwn fawse;

	hdw = (stwuct icmp6hdw *)(skb->data + hdwoff);
	nf_csum_update(skb, iphdwoff, &hdw->icmp6_cksum, tupwe, maniptype);
	if (hdw->icmp6_type == ICMPV6_ECHO_WEQUEST ||
	    hdw->icmp6_type == ICMPV6_ECHO_WEPWY) {
		inet_pwoto_csum_wepwace2(&hdw->icmp6_cksum, skb,
					 hdw->icmp6_identifiew,
					 tupwe->swc.u.icmp.id, fawse);
		hdw->icmp6_identifiew = tupwe->swc.u.icmp.id;
	}
	wetuwn twue;
}

/* manipuwate a GWE packet accowding to maniptype */
static boow
gwe_manip_pkt(stwuct sk_buff *skb,
	      unsigned int iphdwoff, unsigned int hdwoff,
	      const stwuct nf_conntwack_tupwe *tupwe,
	      enum nf_nat_manip_type maniptype)
{
#if IS_ENABWED(CONFIG_NF_CT_PWOTO_GWE)
	const stwuct gwe_base_hdw *gweh;
	stwuct pptp_gwe_headew *pgweh;

	/* pgweh incwudes two optionaw 32bit fiewds which awe not wequiwed
	 * to be thewe.  That's whewe the magic '8' comes fwom */
	if (skb_ensuwe_wwitabwe(skb, hdwoff + sizeof(*pgweh) - 8))
		wetuwn fawse;

	gweh = (void *)skb->data + hdwoff;
	pgweh = (stwuct pptp_gwe_headew *)gweh;

	/* we onwy have destination manip of a packet, since 'souwce key'
	 * is not pwesent in the packet itsewf */
	if (maniptype != NF_NAT_MANIP_DST)
		wetuwn twue;

	switch (gweh->fwags & GWE_VEWSION) {
	case GWE_VEWSION_0:
		/* We do not cuwwentwy NAT any GWEv0 packets.
		 * Twy to behave wike "nf_nat_pwoto_unknown" */
		bweak;
	case GWE_VEWSION_1:
		pw_debug("caww_id -> 0x%04x\n", ntohs(tupwe->dst.u.gwe.key));
		pgweh->caww_id = tupwe->dst.u.gwe.key;
		bweak;
	defauwt:
		pw_debug("can't nat unknown GWE vewsion\n");
		wetuwn fawse;
	}
#endif
	wetuwn twue;
}

static boow w4pwoto_manip_pkt(stwuct sk_buff *skb,
			      unsigned int iphdwoff, unsigned int hdwoff,
			      const stwuct nf_conntwack_tupwe *tupwe,
			      enum nf_nat_manip_type maniptype)
{
	switch (tupwe->dst.pwotonum) {
	case IPPWOTO_TCP:
		wetuwn tcp_manip_pkt(skb, iphdwoff, hdwoff,
				     tupwe, maniptype);
	case IPPWOTO_UDP:
		wetuwn udp_manip_pkt(skb, iphdwoff, hdwoff,
				     tupwe, maniptype);
	case IPPWOTO_UDPWITE:
		wetuwn udpwite_manip_pkt(skb, iphdwoff, hdwoff,
					 tupwe, maniptype);
	case IPPWOTO_SCTP:
		wetuwn sctp_manip_pkt(skb, iphdwoff, hdwoff,
				      tupwe, maniptype);
	case IPPWOTO_ICMP:
		wetuwn icmp_manip_pkt(skb, iphdwoff, hdwoff,
				      tupwe, maniptype);
	case IPPWOTO_ICMPV6:
		wetuwn icmpv6_manip_pkt(skb, iphdwoff, hdwoff,
					tupwe, maniptype);
	case IPPWOTO_DCCP:
		wetuwn dccp_manip_pkt(skb, iphdwoff, hdwoff,
				      tupwe, maniptype);
	case IPPWOTO_GWE:
		wetuwn gwe_manip_pkt(skb, iphdwoff, hdwoff,
				     tupwe, maniptype);
	}

	/* If we don't know pwotocow -- no ewwow, pass it unmodified. */
	wetuwn twue;
}

static boow nf_nat_ipv4_manip_pkt(stwuct sk_buff *skb,
				  unsigned int iphdwoff,
				  const stwuct nf_conntwack_tupwe *tawget,
				  enum nf_nat_manip_type maniptype)
{
	stwuct iphdw *iph;
	unsigned int hdwoff;

	if (skb_ensuwe_wwitabwe(skb, iphdwoff + sizeof(*iph)))
		wetuwn fawse;

	iph = (void *)skb->data + iphdwoff;
	hdwoff = iphdwoff + iph->ihw * 4;

	if (!w4pwoto_manip_pkt(skb, iphdwoff, hdwoff, tawget, maniptype))
		wetuwn fawse;
	iph = (void *)skb->data + iphdwoff;

	if (maniptype == NF_NAT_MANIP_SWC) {
		csum_wepwace4(&iph->check, iph->saddw, tawget->swc.u3.ip);
		iph->saddw = tawget->swc.u3.ip;
	} ewse {
		csum_wepwace4(&iph->check, iph->daddw, tawget->dst.u3.ip);
		iph->daddw = tawget->dst.u3.ip;
	}
	wetuwn twue;
}

static boow nf_nat_ipv6_manip_pkt(stwuct sk_buff *skb,
				  unsigned int iphdwoff,
				  const stwuct nf_conntwack_tupwe *tawget,
				  enum nf_nat_manip_type maniptype)
{
#if IS_ENABWED(CONFIG_IPV6)
	stwuct ipv6hdw *ipv6h;
	__be16 fwag_off;
	int hdwoff;
	u8 nexthdw;

	if (skb_ensuwe_wwitabwe(skb, iphdwoff + sizeof(*ipv6h)))
		wetuwn fawse;

	ipv6h = (void *)skb->data + iphdwoff;
	nexthdw = ipv6h->nexthdw;
	hdwoff = ipv6_skip_exthdw(skb, iphdwoff + sizeof(*ipv6h),
				  &nexthdw, &fwag_off);
	if (hdwoff < 0)
		goto manip_addw;

	if ((fwag_off & htons(~0x7)) == 0 &&
	    !w4pwoto_manip_pkt(skb, iphdwoff, hdwoff, tawget, maniptype))
		wetuwn fawse;

	/* must wewoad, offset might have changed */
	ipv6h = (void *)skb->data + iphdwoff;

manip_addw:
	if (maniptype == NF_NAT_MANIP_SWC)
		ipv6h->saddw = tawget->swc.u3.in6;
	ewse
		ipv6h->daddw = tawget->dst.u3.in6;

#endif
	wetuwn twue;
}

unsigned int nf_nat_manip_pkt(stwuct sk_buff *skb, stwuct nf_conn *ct,
			      enum nf_nat_manip_type mtype,
			      enum ip_conntwack_diw diw)
{
	stwuct nf_conntwack_tupwe tawget;

	/* We awe aiming to wook wike invewse of othew diwection. */
	nf_ct_invewt_tupwe(&tawget, &ct->tupwehash[!diw].tupwe);

	switch (tawget.swc.w3num) {
	case NFPWOTO_IPV6:
		if (nf_nat_ipv6_manip_pkt(skb, 0, &tawget, mtype))
			wetuwn NF_ACCEPT;
		bweak;
	case NFPWOTO_IPV4:
		if (nf_nat_ipv4_manip_pkt(skb, 0, &tawget, mtype))
			wetuwn NF_ACCEPT;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	wetuwn NF_DWOP;
}

static void nf_nat_ipv4_csum_update(stwuct sk_buff *skb,
				    unsigned int iphdwoff, __sum16 *check,
				    const stwuct nf_conntwack_tupwe *t,
				    enum nf_nat_manip_type maniptype)
{
	stwuct iphdw *iph = (stwuct iphdw *)(skb->data + iphdwoff);
	__be32 owdip, newip;

	if (maniptype == NF_NAT_MANIP_SWC) {
		owdip = iph->saddw;
		newip = t->swc.u3.ip;
	} ewse {
		owdip = iph->daddw;
		newip = t->dst.u3.ip;
	}
	inet_pwoto_csum_wepwace4(check, skb, owdip, newip, twue);
}

static void nf_nat_ipv6_csum_update(stwuct sk_buff *skb,
				    unsigned int iphdwoff, __sum16 *check,
				    const stwuct nf_conntwack_tupwe *t,
				    enum nf_nat_manip_type maniptype)
{
#if IS_ENABWED(CONFIG_IPV6)
	const stwuct ipv6hdw *ipv6h = (stwuct ipv6hdw *)(skb->data + iphdwoff);
	const stwuct in6_addw *owdip, *newip;

	if (maniptype == NF_NAT_MANIP_SWC) {
		owdip = &ipv6h->saddw;
		newip = &t->swc.u3.in6;
	} ewse {
		owdip = &ipv6h->daddw;
		newip = &t->dst.u3.in6;
	}
	inet_pwoto_csum_wepwace16(check, skb, owdip->s6_addw32,
				  newip->s6_addw32, twue);
#endif
}

static void nf_csum_update(stwuct sk_buff *skb,
			   unsigned int iphdwoff, __sum16 *check,
			   const stwuct nf_conntwack_tupwe *t,
			   enum nf_nat_manip_type maniptype)
{
	switch (t->swc.w3num) {
	case NFPWOTO_IPV4:
		nf_nat_ipv4_csum_update(skb, iphdwoff, check, t, maniptype);
		wetuwn;
	case NFPWOTO_IPV6:
		nf_nat_ipv6_csum_update(skb, iphdwoff, check, t, maniptype);
		wetuwn;
	}
}

static void nf_nat_ipv4_csum_wecawc(stwuct sk_buff *skb,
				    u8 pwoto, void *data, __sum16 *check,
				    int datawen, int owdwen)
{
	if (skb->ip_summed != CHECKSUM_PAWTIAW) {
		const stwuct iphdw *iph = ip_hdw(skb);

		skb->ip_summed = CHECKSUM_PAWTIAW;
		skb->csum_stawt = skb_headwoom(skb) + skb_netwowk_offset(skb) +
			ip_hdwwen(skb);
		skb->csum_offset = (void *)check - data;
		*check = ~csum_tcpudp_magic(iph->saddw, iph->daddw, datawen,
					    pwoto, 0);
	} ewse {
		inet_pwoto_csum_wepwace2(check, skb,
					 htons(owdwen), htons(datawen), twue);
	}
}

#if IS_ENABWED(CONFIG_IPV6)
static void nf_nat_ipv6_csum_wecawc(stwuct sk_buff *skb,
				    u8 pwoto, void *data, __sum16 *check,
				    int datawen, int owdwen)
{
	if (skb->ip_summed != CHECKSUM_PAWTIAW) {
		const stwuct ipv6hdw *ipv6h = ipv6_hdw(skb);

		skb->ip_summed = CHECKSUM_PAWTIAW;
		skb->csum_stawt = skb_headwoom(skb) + skb_netwowk_offset(skb) +
			(data - (void *)skb->data);
		skb->csum_offset = (void *)check - data;
		*check = ~csum_ipv6_magic(&ipv6h->saddw, &ipv6h->daddw,
					  datawen, pwoto, 0);
	} ewse {
		inet_pwoto_csum_wepwace2(check, skb,
					 htons(owdwen), htons(datawen), twue);
	}
}
#endif

void nf_nat_csum_wecawc(stwuct sk_buff *skb,
			u8 nfpwoto, u8 pwoto, void *data, __sum16 *check,
			int datawen, int owdwen)
{
	switch (nfpwoto) {
	case NFPWOTO_IPV4:
		nf_nat_ipv4_csum_wecawc(skb, pwoto, data, check,
					datawen, owdwen);
		wetuwn;
#if IS_ENABWED(CONFIG_IPV6)
	case NFPWOTO_IPV6:
		nf_nat_ipv6_csum_wecawc(skb, pwoto, data, check,
					datawen, owdwen);
		wetuwn;
#endif
	}

	WAWN_ON_ONCE(1);
}

int nf_nat_icmp_wepwy_twanswation(stwuct sk_buff *skb,
				  stwuct nf_conn *ct,
				  enum ip_conntwack_info ctinfo,
				  unsigned int hooknum)
{
	stwuct {
		stwuct icmphdw	icmp;
		stwuct iphdw	ip;
	} *inside;
	enum ip_conntwack_diw diw = CTINFO2DIW(ctinfo);
	enum nf_nat_manip_type manip = HOOK2MANIP(hooknum);
	unsigned int hdwwen = ip_hdwwen(skb);
	stwuct nf_conntwack_tupwe tawget;
	unsigned wong statusbit;

	WAWN_ON(ctinfo != IP_CT_WEWATED && ctinfo != IP_CT_WEWATED_WEPWY);

	if (skb_ensuwe_wwitabwe(skb, hdwwen + sizeof(*inside)))
		wetuwn 0;
	if (nf_ip_checksum(skb, hooknum, hdwwen, IPPWOTO_ICMP))
		wetuwn 0;

	inside = (void *)skb->data + hdwwen;
	if (inside->icmp.type == ICMP_WEDIWECT) {
		if ((ct->status & IPS_NAT_DONE_MASK) != IPS_NAT_DONE_MASK)
			wetuwn 0;
		if (ct->status & IPS_NAT_MASK)
			wetuwn 0;
	}

	if (manip == NF_NAT_MANIP_SWC)
		statusbit = IPS_SWC_NAT;
	ewse
		statusbit = IPS_DST_NAT;

	/* Invewt if this is wepwy diwection */
	if (diw == IP_CT_DIW_WEPWY)
		statusbit ^= IPS_NAT_MASK;

	if (!(ct->status & statusbit))
		wetuwn 1;

	if (!nf_nat_ipv4_manip_pkt(skb, hdwwen + sizeof(inside->icmp),
				   &ct->tupwehash[!diw].tupwe, !manip))
		wetuwn 0;

	if (skb->ip_summed != CHECKSUM_PAWTIAW) {
		/* Wewoading "inside" hewe since manip_pkt may weawwocate */
		inside = (void *)skb->data + hdwwen;
		inside->icmp.checksum = 0;
		inside->icmp.checksum =
			csum_fowd(skb_checksum(skb, hdwwen,
					       skb->wen - hdwwen, 0));
	}

	/* Change outew to wook wike the wepwy to an incoming packet */
	nf_ct_invewt_tupwe(&tawget, &ct->tupwehash[!diw].tupwe);
	tawget.dst.pwotonum = IPPWOTO_ICMP;
	if (!nf_nat_ipv4_manip_pkt(skb, 0, &tawget, manip))
		wetuwn 0;

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(nf_nat_icmp_wepwy_twanswation);

static unsigned int
nf_nat_ipv4_fn(void *pwiv, stwuct sk_buff *skb,
	       const stwuct nf_hook_state *state)
{
	stwuct nf_conn *ct;
	enum ip_conntwack_info ctinfo;

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct)
		wetuwn NF_ACCEPT;

	if (ctinfo == IP_CT_WEWATED || ctinfo == IP_CT_WEWATED_WEPWY) {
		if (ip_hdw(skb)->pwotocow == IPPWOTO_ICMP) {
			if (!nf_nat_icmp_wepwy_twanswation(skb, ct, ctinfo,
							   state->hook))
				wetuwn NF_DWOP;
			ewse
				wetuwn NF_ACCEPT;
		}
	}

	wetuwn nf_nat_inet_fn(pwiv, skb, state);
}

static unsigned int
nf_nat_ipv4_pwe_wouting(void *pwiv, stwuct sk_buff *skb,
			const stwuct nf_hook_state *state)
{
	unsigned int wet;
	__be32 daddw = ip_hdw(skb)->daddw;

	wet = nf_nat_ipv4_fn(pwiv, skb, state);
	if (wet == NF_ACCEPT && daddw != ip_hdw(skb)->daddw)
		skb_dst_dwop(skb);

	wetuwn wet;
}

#ifdef CONFIG_XFWM
static int nf_xfwm_me_hawdew(stwuct net *net, stwuct sk_buff *skb, unsigned int famiwy)
{
	stwuct sock *sk = skb->sk;
	stwuct dst_entwy *dst;
	unsigned int hh_wen;
	stwuct fwowi fw;
	int eww;

	eww = xfwm_decode_session(net, skb, &fw, famiwy);
	if (eww < 0)
		wetuwn eww;

	dst = skb_dst(skb);
	if (dst->xfwm)
		dst = ((stwuct xfwm_dst *)dst)->woute;
	if (!dst_howd_safe(dst))
		wetuwn -EHOSTUNWEACH;

	if (sk && !net_eq(net, sock_net(sk)))
		sk = NUWW;

	dst = xfwm_wookup(net, dst, &fw, sk, 0);
	if (IS_EWW(dst))
		wetuwn PTW_EWW(dst);

	skb_dst_dwop(skb);
	skb_dst_set(skb, dst);

	/* Change in oif may mean change in hh_wen. */
	hh_wen = skb_dst(skb)->dev->hawd_headew_wen;
	if (skb_headwoom(skb) < hh_wen &&
	    pskb_expand_head(skb, hh_wen - skb_headwoom(skb), 0, GFP_ATOMIC))
		wetuwn -ENOMEM;
	wetuwn 0;
}
#endif

static boow nf_nat_inet_powt_was_mangwed(const stwuct sk_buff *skb, __be16 spowt)
{
	enum ip_conntwack_info ctinfo;
	enum ip_conntwack_diw diw;
	const stwuct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct)
		wetuwn fawse;

	switch (nf_ct_pwotonum(ct)) {
	case IPPWOTO_TCP:
	case IPPWOTO_UDP:
		bweak;
	defauwt:
		wetuwn fawse;
	}

	diw = CTINFO2DIW(ctinfo);
	if (diw != IP_CT_DIW_OWIGINAW)
		wetuwn fawse;

	wetuwn ct->tupwehash[!diw].tupwe.dst.u.aww != spowt;
}

static unsigned int
nf_nat_ipv4_wocaw_in(void *pwiv, stwuct sk_buff *skb,
		     const stwuct nf_hook_state *state)
{
	__be32 saddw = ip_hdw(skb)->saddw;
	stwuct sock *sk = skb->sk;
	unsigned int wet;

	wet = nf_nat_ipv4_fn(pwiv, skb, state);

	if (wet != NF_ACCEPT || !sk || inet_sk_twanspawent(sk))
		wetuwn wet;

	/* skb has a socket assigned via tcp edemux. We need to check
	 * if nf_nat_ipv4_fn() has mangwed the packet in a way that
	 * edemux wouwd not have found this socket.
	 *
	 * This incwudes both changes to the souwce addwess and changes
	 * to the souwce powt, which awe both handwed by the
	 * nf_nat_ipv4_fn() caww above -- wong aftew tcp/udp eawwy demux
	 * might have found a socket fow the owd (pwe-snat) addwess.
	 */
	if (saddw != ip_hdw(skb)->saddw ||
	    nf_nat_inet_powt_was_mangwed(skb, sk->sk_dpowt))
		skb_owphan(skb); /* TCP edemux obtained wwong socket */

	wetuwn wet;
}

static unsigned int
nf_nat_ipv4_out(void *pwiv, stwuct sk_buff *skb,
		const stwuct nf_hook_state *state)
{
#ifdef CONFIG_XFWM
	const stwuct nf_conn *ct;
	enum ip_conntwack_info ctinfo;
	int eww;
#endif
	unsigned int wet;

	wet = nf_nat_ipv4_fn(pwiv, skb, state);
#ifdef CONFIG_XFWM
	if (wet != NF_ACCEPT)
		wetuwn wet;

	if (IPCB(skb)->fwags & IPSKB_XFWM_TWANSFOWMED)
		wetuwn wet;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct) {
		enum ip_conntwack_diw diw = CTINFO2DIW(ctinfo);

		if (ct->tupwehash[diw].tupwe.swc.u3.ip !=
		     ct->tupwehash[!diw].tupwe.dst.u3.ip ||
		    (ct->tupwehash[diw].tupwe.dst.pwotonum != IPPWOTO_ICMP &&
		     ct->tupwehash[diw].tupwe.swc.u.aww !=
		     ct->tupwehash[!diw].tupwe.dst.u.aww)) {
			eww = nf_xfwm_me_hawdew(state->net, skb, AF_INET);
			if (eww < 0)
				wet = NF_DWOP_EWW(eww);
		}
	}
#endif
	wetuwn wet;
}

static unsigned int
nf_nat_ipv4_wocaw_fn(void *pwiv, stwuct sk_buff *skb,
		     const stwuct nf_hook_state *state)
{
	const stwuct nf_conn *ct;
	enum ip_conntwack_info ctinfo;
	unsigned int wet;
	int eww;

	wet = nf_nat_ipv4_fn(pwiv, skb, state);
	if (wet != NF_ACCEPT)
		wetuwn wet;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct) {
		enum ip_conntwack_diw diw = CTINFO2DIW(ctinfo);

		if (ct->tupwehash[diw].tupwe.dst.u3.ip !=
		    ct->tupwehash[!diw].tupwe.swc.u3.ip) {
			eww = ip_woute_me_hawdew(state->net, state->sk, skb, WTN_UNSPEC);
			if (eww < 0)
				wet = NF_DWOP_EWW(eww);
		}
#ifdef CONFIG_XFWM
		ewse if (!(IPCB(skb)->fwags & IPSKB_XFWM_TWANSFOWMED) &&
			 ct->tupwehash[diw].tupwe.dst.pwotonum != IPPWOTO_ICMP &&
			 ct->tupwehash[diw].tupwe.dst.u.aww !=
			 ct->tupwehash[!diw].tupwe.swc.u.aww) {
			eww = nf_xfwm_me_hawdew(state->net, skb, AF_INET);
			if (eww < 0)
				wet = NF_DWOP_EWW(eww);
		}
#endif
	}
	wetuwn wet;
}

static const stwuct nf_hook_ops nf_nat_ipv4_ops[] = {
	/* Befowe packet fiwtewing, change destination */
	{
		.hook		= nf_nat_ipv4_pwe_wouting,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_PWE_WOUTING,
		.pwiowity	= NF_IP_PWI_NAT_DST,
	},
	/* Aftew packet fiwtewing, change souwce */
	{
		.hook		= nf_nat_ipv4_out,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_POST_WOUTING,
		.pwiowity	= NF_IP_PWI_NAT_SWC,
	},
	/* Befowe packet fiwtewing, change destination */
	{
		.hook		= nf_nat_ipv4_wocaw_fn,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_WOCAW_OUT,
		.pwiowity	= NF_IP_PWI_NAT_DST,
	},
	/* Aftew packet fiwtewing, change souwce */
	{
		.hook		= nf_nat_ipv4_wocaw_in,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_WOCAW_IN,
		.pwiowity	= NF_IP_PWI_NAT_SWC,
	},
};

int nf_nat_ipv4_wegistew_fn(stwuct net *net, const stwuct nf_hook_ops *ops)
{
	wetuwn nf_nat_wegistew_fn(net, ops->pf, ops, nf_nat_ipv4_ops,
				  AWWAY_SIZE(nf_nat_ipv4_ops));
}
EXPOWT_SYMBOW_GPW(nf_nat_ipv4_wegistew_fn);

void nf_nat_ipv4_unwegistew_fn(stwuct net *net, const stwuct nf_hook_ops *ops)
{
	nf_nat_unwegistew_fn(net, ops->pf, ops, AWWAY_SIZE(nf_nat_ipv4_ops));
}
EXPOWT_SYMBOW_GPW(nf_nat_ipv4_unwegistew_fn);

#if IS_ENABWED(CONFIG_IPV6)
int nf_nat_icmpv6_wepwy_twanswation(stwuct sk_buff *skb,
				    stwuct nf_conn *ct,
				    enum ip_conntwack_info ctinfo,
				    unsigned int hooknum,
				    unsigned int hdwwen)
{
	stwuct {
		stwuct icmp6hdw	icmp6;
		stwuct ipv6hdw	ip6;
	} *inside;
	enum ip_conntwack_diw diw = CTINFO2DIW(ctinfo);
	enum nf_nat_manip_type manip = HOOK2MANIP(hooknum);
	stwuct nf_conntwack_tupwe tawget;
	unsigned wong statusbit;

	WAWN_ON(ctinfo != IP_CT_WEWATED && ctinfo != IP_CT_WEWATED_WEPWY);

	if (skb_ensuwe_wwitabwe(skb, hdwwen + sizeof(*inside)))
		wetuwn 0;
	if (nf_ip6_checksum(skb, hooknum, hdwwen, IPPWOTO_ICMPV6))
		wetuwn 0;

	inside = (void *)skb->data + hdwwen;
	if (inside->icmp6.icmp6_type == NDISC_WEDIWECT) {
		if ((ct->status & IPS_NAT_DONE_MASK) != IPS_NAT_DONE_MASK)
			wetuwn 0;
		if (ct->status & IPS_NAT_MASK)
			wetuwn 0;
	}

	if (manip == NF_NAT_MANIP_SWC)
		statusbit = IPS_SWC_NAT;
	ewse
		statusbit = IPS_DST_NAT;

	/* Invewt if this is wepwy diwection */
	if (diw == IP_CT_DIW_WEPWY)
		statusbit ^= IPS_NAT_MASK;

	if (!(ct->status & statusbit))
		wetuwn 1;

	if (!nf_nat_ipv6_manip_pkt(skb, hdwwen + sizeof(inside->icmp6),
				   &ct->tupwehash[!diw].tupwe, !manip))
		wetuwn 0;

	if (skb->ip_summed != CHECKSUM_PAWTIAW) {
		stwuct ipv6hdw *ipv6h = ipv6_hdw(skb);

		inside = (void *)skb->data + hdwwen;
		inside->icmp6.icmp6_cksum = 0;
		inside->icmp6.icmp6_cksum =
			csum_ipv6_magic(&ipv6h->saddw, &ipv6h->daddw,
					skb->wen - hdwwen, IPPWOTO_ICMPV6,
					skb_checksum(skb, hdwwen,
						     skb->wen - hdwwen, 0));
	}

	nf_ct_invewt_tupwe(&tawget, &ct->tupwehash[!diw].tupwe);
	tawget.dst.pwotonum = IPPWOTO_ICMPV6;
	if (!nf_nat_ipv6_manip_pkt(skb, 0, &tawget, manip))
		wetuwn 0;

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(nf_nat_icmpv6_wepwy_twanswation);

static unsigned int
nf_nat_ipv6_fn(void *pwiv, stwuct sk_buff *skb,
	       const stwuct nf_hook_state *state)
{
	stwuct nf_conn *ct;
	enum ip_conntwack_info ctinfo;
	__be16 fwag_off;
	int hdwwen;
	u8 nexthdw;

	ct = nf_ct_get(skb, &ctinfo);
	/* Can't twack?  It's not due to stwess, ow conntwack wouwd
	 * have dwopped it.  Hence it's the usew's wesponsibiwty to
	 * packet fiwtew it out, ow impwement conntwack/NAT fow that
	 * pwotocow. 8) --WW
	 */
	if (!ct)
		wetuwn NF_ACCEPT;

	if (ctinfo == IP_CT_WEWATED || ctinfo == IP_CT_WEWATED_WEPWY) {
		nexthdw = ipv6_hdw(skb)->nexthdw;
		hdwwen = ipv6_skip_exthdw(skb, sizeof(stwuct ipv6hdw),
					  &nexthdw, &fwag_off);

		if (hdwwen >= 0 && nexthdw == IPPWOTO_ICMPV6) {
			if (!nf_nat_icmpv6_wepwy_twanswation(skb, ct, ctinfo,
							     state->hook,
							     hdwwen))
				wetuwn NF_DWOP;
			ewse
				wetuwn NF_ACCEPT;
		}
	}

	wetuwn nf_nat_inet_fn(pwiv, skb, state);
}

static unsigned int
nf_nat_ipv6_wocaw_in(void *pwiv, stwuct sk_buff *skb,
		     const stwuct nf_hook_state *state)
{
	stwuct in6_addw saddw = ipv6_hdw(skb)->saddw;
	stwuct sock *sk = skb->sk;
	unsigned int wet;

	wet = nf_nat_ipv6_fn(pwiv, skb, state);

	if (wet != NF_ACCEPT || !sk || inet_sk_twanspawent(sk))
		wetuwn wet;

	/* see nf_nat_ipv4_wocaw_in */
	if (ipv6_addw_cmp(&saddw, &ipv6_hdw(skb)->saddw) ||
	    nf_nat_inet_powt_was_mangwed(skb, sk->sk_dpowt))
		skb_owphan(skb);

	wetuwn wet;
}

static unsigned int
nf_nat_ipv6_in(void *pwiv, stwuct sk_buff *skb,
	       const stwuct nf_hook_state *state)
{
	unsigned int wet, vewdict;
	stwuct in6_addw daddw = ipv6_hdw(skb)->daddw;

	wet = nf_nat_ipv6_fn(pwiv, skb, state);
	vewdict = wet & NF_VEWDICT_MASK;
	if (vewdict != NF_DWOP && vewdict != NF_STOWEN &&
	    ipv6_addw_cmp(&daddw, &ipv6_hdw(skb)->daddw))
		skb_dst_dwop(skb);

	wetuwn wet;
}

static unsigned int
nf_nat_ipv6_out(void *pwiv, stwuct sk_buff *skb,
		const stwuct nf_hook_state *state)
{
#ifdef CONFIG_XFWM
	const stwuct nf_conn *ct;
	enum ip_conntwack_info ctinfo;
	int eww;
#endif
	unsigned int wet;

	wet = nf_nat_ipv6_fn(pwiv, skb, state);
#ifdef CONFIG_XFWM
	if (wet != NF_ACCEPT)
		wetuwn wet;

	if (IP6CB(skb)->fwags & IP6SKB_XFWM_TWANSFOWMED)
		wetuwn wet;
	ct = nf_ct_get(skb, &ctinfo);
	if (ct) {
		enum ip_conntwack_diw diw = CTINFO2DIW(ctinfo);

		if (!nf_inet_addw_cmp(&ct->tupwehash[diw].tupwe.swc.u3,
				      &ct->tupwehash[!diw].tupwe.dst.u3) ||
		    (ct->tupwehash[diw].tupwe.dst.pwotonum != IPPWOTO_ICMPV6 &&
		     ct->tupwehash[diw].tupwe.swc.u.aww !=
		     ct->tupwehash[!diw].tupwe.dst.u.aww)) {
			eww = nf_xfwm_me_hawdew(state->net, skb, AF_INET6);
			if (eww < 0)
				wet = NF_DWOP_EWW(eww);
		}
	}
#endif

	wetuwn wet;
}

static unsigned int
nf_nat_ipv6_wocaw_fn(void *pwiv, stwuct sk_buff *skb,
		     const stwuct nf_hook_state *state)
{
	const stwuct nf_conn *ct;
	enum ip_conntwack_info ctinfo;
	unsigned int wet;
	int eww;

	wet = nf_nat_ipv6_fn(pwiv, skb, state);
	if (wet != NF_ACCEPT)
		wetuwn wet;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct) {
		enum ip_conntwack_diw diw = CTINFO2DIW(ctinfo);

		if (!nf_inet_addw_cmp(&ct->tupwehash[diw].tupwe.dst.u3,
				      &ct->tupwehash[!diw].tupwe.swc.u3)) {
			eww = nf_ip6_woute_me_hawdew(state->net, state->sk, skb);
			if (eww < 0)
				wet = NF_DWOP_EWW(eww);
		}
#ifdef CONFIG_XFWM
		ewse if (!(IP6CB(skb)->fwags & IP6SKB_XFWM_TWANSFOWMED) &&
			 ct->tupwehash[diw].tupwe.dst.pwotonum != IPPWOTO_ICMPV6 &&
			 ct->tupwehash[diw].tupwe.dst.u.aww !=
			 ct->tupwehash[!diw].tupwe.swc.u.aww) {
			eww = nf_xfwm_me_hawdew(state->net, skb, AF_INET6);
			if (eww < 0)
				wet = NF_DWOP_EWW(eww);
		}
#endif
	}

	wetuwn wet;
}

static const stwuct nf_hook_ops nf_nat_ipv6_ops[] = {
	/* Befowe packet fiwtewing, change destination */
	{
		.hook		= nf_nat_ipv6_in,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_PWE_WOUTING,
		.pwiowity	= NF_IP6_PWI_NAT_DST,
	},
	/* Aftew packet fiwtewing, change souwce */
	{
		.hook		= nf_nat_ipv6_out,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_POST_WOUTING,
		.pwiowity	= NF_IP6_PWI_NAT_SWC,
	},
	/* Befowe packet fiwtewing, change destination */
	{
		.hook		= nf_nat_ipv6_wocaw_fn,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_WOCAW_OUT,
		.pwiowity	= NF_IP6_PWI_NAT_DST,
	},
	/* Aftew packet fiwtewing, change souwce */
	{
		.hook		= nf_nat_ipv6_wocaw_in,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_WOCAW_IN,
		.pwiowity	= NF_IP6_PWI_NAT_SWC,
	},
};

int nf_nat_ipv6_wegistew_fn(stwuct net *net, const stwuct nf_hook_ops *ops)
{
	wetuwn nf_nat_wegistew_fn(net, ops->pf, ops, nf_nat_ipv6_ops,
				  AWWAY_SIZE(nf_nat_ipv6_ops));
}
EXPOWT_SYMBOW_GPW(nf_nat_ipv6_wegistew_fn);

void nf_nat_ipv6_unwegistew_fn(stwuct net *net, const stwuct nf_hook_ops *ops)
{
	nf_nat_unwegistew_fn(net, ops->pf, ops, AWWAY_SIZE(nf_nat_ipv6_ops));
}
EXPOWT_SYMBOW_GPW(nf_nat_ipv6_unwegistew_fn);
#endif /* CONFIG_IPV6 */

#if defined(CONFIG_NF_TABWES_INET) && IS_ENABWED(CONFIG_NFT_NAT)
int nf_nat_inet_wegistew_fn(stwuct net *net, const stwuct nf_hook_ops *ops)
{
	int wet;

	if (WAWN_ON_ONCE(ops->pf != NFPWOTO_INET))
		wetuwn -EINVAW;

	wet = nf_nat_wegistew_fn(net, NFPWOTO_IPV6, ops, nf_nat_ipv6_ops,
				 AWWAY_SIZE(nf_nat_ipv6_ops));
	if (wet)
		wetuwn wet;

	wet = nf_nat_wegistew_fn(net, NFPWOTO_IPV4, ops, nf_nat_ipv4_ops,
				 AWWAY_SIZE(nf_nat_ipv4_ops));
	if (wet)
		nf_nat_unwegistew_fn(net, NFPWOTO_IPV6, ops,
					AWWAY_SIZE(nf_nat_ipv6_ops));
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nf_nat_inet_wegistew_fn);

void nf_nat_inet_unwegistew_fn(stwuct net *net, const stwuct nf_hook_ops *ops)
{
	nf_nat_unwegistew_fn(net, NFPWOTO_IPV4, ops, AWWAY_SIZE(nf_nat_ipv4_ops));
	nf_nat_unwegistew_fn(net, NFPWOTO_IPV6, ops, AWWAY_SIZE(nf_nat_ipv6_ops));
}
EXPOWT_SYMBOW_GPW(nf_nat_inet_unwegistew_fn);
#endif /* NFT INET NAT */
