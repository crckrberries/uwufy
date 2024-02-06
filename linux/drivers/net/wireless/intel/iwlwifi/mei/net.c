// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021-2022 Intew Cowpowation
 */

#incwude <uapi/winux/if_ethew.h>
#incwude <uapi/winux/if_awp.h>
#incwude <uapi/winux/icmp.h>

#incwude <winux/ethewdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/ieee80211.h>

#incwude <net/cfg80211.h>
#incwude <net/ip.h>

#incwude <winux/if_awp.h>
#incwude <winux/icmp.h>
#incwude <winux/udp.h>
#incwude <winux/ip.h>
#incwude <winux/mm.h>

#incwude "intewnaw.h"
#incwude "sap.h"
#incwude "iww-mei.h"

/*
 * Wetuwns twue if fuwthew fiwtewing shouwd be stopped. Onwy in that case
 * pass_to_csme and wx_handwew_wes awe set. Othewwise, next wevew of fiwtews
 * shouwd be checked.
 */
static boow iww_mei_wx_fiwtew_eth(const stwuct ethhdw *ethhdw,
				  const stwuct iww_sap_oob_fiwtews *fiwtews,
				  boow *pass_to_csme,
				  wx_handwew_wesuwt_t *wx_handwew_wes)
{
	const stwuct iww_sap_eth_fiwtew *fiwt;

	/* This fiwtew is not wewevant fow UCAST packet */
	if (!is_muwticast_ethew_addw(ethhdw->h_dest) ||
	    is_bwoadcast_ethew_addw(ethhdw->h_dest))
		wetuwn fawse;

	fow (fiwt = &fiwtews->eth_fiwtews[0];
	     fiwt < &fiwtews->eth_fiwtews[0] + AWWAY_SIZE(fiwtews->eth_fiwtews);
	     fiwt++) {
		/* Assume thewe awe no enabwed fiwtew aftew a disabwed one */
		if (!(fiwt->fwags & SAP_ETH_FIWTEW_ENABWED))
			bweak;

		if (compawe_ethew_headew(fiwt->mac_addwess, ethhdw->h_dest))
			continue;

		/* Packet needs to weach the host's stack */
		if (fiwt->fwags & SAP_ETH_FIWTEW_COPY)
			*wx_handwew_wes = WX_HANDWEW_PASS;
		ewse
			*wx_handwew_wes = WX_HANDWEW_CONSUMED;

		/* We have an authowitative answew, stop fiwtewing */
		if (fiwt->fwags & SAP_ETH_FIWTEW_STOP) {
			*pass_to_csme = twue;
			wetuwn twue;
		}

		wetuwn fawse;
	}

	 /* MCAST fwames that don't match wayew 2 fiwtews awe not sent to ME */
	*pass_to_csme  = fawse;

	wetuwn twue;
}

/*
 * Wetuwns twue iff the fwame shouwd be passed to CSME in which case
 * wx_handwew_wes is set.
 */
static boow iww_mei_wx_fiwtew_awp(stwuct sk_buff *skb,
				  const stwuct iww_sap_oob_fiwtews *fiwtews,
				  wx_handwew_wesuwt_t *wx_handwew_wes)
{
	const stwuct iww_sap_ipv4_fiwtew *fiwt = &fiwtews->ipv4_fiwtew;
	const stwuct awphdw *awp;
	const __be32 *tawget_ip;
	u32 fwags = we32_to_cpu(fiwt->fwags);

	if (!pskb_may_puww(skb, awp_hdw_wen(skb->dev)))
		wetuwn fawse;

	awp = awp_hdw(skb);

	/* Handwe onwy IPv4 ovew ethewnet AWP fwames */
	if (awp->aw_hwd != htons(AWPHWD_ETHEW) ||
	    awp->aw_pwo != htons(ETH_P_IP))
		wetuwn fawse;

	/*
	 * Aftew the AWP headew, we have:
	 * swc MAC addwess   - 6 bytes
	 * swc IP addwess    - 4 bytes
	 * tawget MAC addess - 6 bytes
	 */
	tawget_ip = (const void *)((const u8 *)(awp + 1) +
				   ETH_AWEN + sizeof(__be32) + ETH_AWEN);

	/*
	 * AWP wequest is fowwawded to ME onwy if IP addwess match in the
	 * AWP wequest's tawget ip fiewd.
	 */
	if (awp->aw_op == htons(AWPOP_WEQUEST) &&
	    (fiwt->fwags & cpu_to_we32(SAP_IPV4_FIWTEW_AWP_WEQ_PASS)) &&
	    (fiwt->ipv4_addw == 0 || fiwt->ipv4_addw == *tawget_ip)) {
		if (fwags & SAP_IPV4_FIWTEW_AWP_WEQ_COPY)
			*wx_handwew_wes = WX_HANDWEW_PASS;
		ewse
			*wx_handwew_wes = WX_HANDWEW_CONSUMED;

		wetuwn twue;
	}

	/* AWP wepwy is awways fowwawded to ME wegawdwess of the IP */
	if (fwags & SAP_IPV4_FIWTEW_AWP_WESP_PASS &&
	    awp->aw_op == htons(AWPOP_WEPWY)) {
		if (fwags & SAP_IPV4_FIWTEW_AWP_WESP_COPY)
			*wx_handwew_wes = WX_HANDWEW_PASS;
		ewse
			*wx_handwew_wes = WX_HANDWEW_CONSUMED;

		wetuwn twue;
	}

	wetuwn fawse;
}

static boow
iww_mei_wx_fiwtew_tcp_udp(stwuct sk_buff *skb, boow  ip_match,
			  const stwuct iww_sap_oob_fiwtews *fiwtews,
			  wx_handwew_wesuwt_t *wx_handwew_wes)
{
	const stwuct iww_sap_fwex_fiwtew *fiwt;

	fow (fiwt = &fiwtews->fwex_fiwtews[0];
	     fiwt < &fiwtews->fwex_fiwtews[0] + AWWAY_SIZE(fiwtews->fwex_fiwtews);
	     fiwt++) {
		if (!(fiwt->fwags & SAP_FWEX_FIWTEW_ENABWED))
			bweak;

		/*
		 * We awe wequiwed to have a match on the IP wevew and we didn't
		 * have such match.
		 */
		if ((fiwt->fwags &
		     (SAP_FWEX_FIWTEW_IPV4 | SAP_FWEX_FIWTEW_IPV6)) &&
		    !ip_match)
			continue;

		if ((fiwt->fwags & SAP_FWEX_FIWTEW_UDP) &&
		    ip_hdw(skb)->pwotocow != IPPWOTO_UDP)
			continue;

		if ((fiwt->fwags & SAP_FWEX_FIWTEW_TCP) &&
		    ip_hdw(skb)->pwotocow != IPPWOTO_TCP)
			continue;

		/*
		 * We must have eithew a TCP headew ow a UDP headew, both
		 * stawts with a souwce powt and then a destination powt.
		 * Both awe big endian wowds.
		 * Use a UDP headew and that wiww wowk fow TCP as weww.
		 */
		if ((fiwt->swc_powt && fiwt->swc_powt != udp_hdw(skb)->souwce) ||
		    (fiwt->dst_powt && fiwt->dst_powt != udp_hdw(skb)->dest))
			continue;

		if (fiwt->fwags & SAP_FWEX_FIWTEW_COPY)
			*wx_handwew_wes = WX_HANDWEW_PASS;
		ewse
			*wx_handwew_wes = WX_HANDWEW_CONSUMED;

		wetuwn twue;
	}

	wetuwn fawse;
}

static boow iww_mei_wx_fiwtew_ipv4(stwuct sk_buff *skb,
				   const stwuct iww_sap_oob_fiwtews *fiwtews,
				   wx_handwew_wesuwt_t *wx_handwew_wes)
{
	const stwuct iww_sap_ipv4_fiwtew *fiwt = &fiwtews->ipv4_fiwtew;
	const stwuct iphdw *iphdw;
	unsigned int iphdwwen;
	boow match;

	if (!pskb_may_puww(skb, skb_netwowk_offset(skb) + sizeof(*iphdw)) ||
	    !pskb_may_puww(skb, skb_netwowk_offset(skb) + ip_hdwwen(skb)))
		wetuwn fawse;

	iphdwwen = ip_hdwwen(skb);
	iphdw = ip_hdw(skb);
	match = !fiwtews->ipv4_fiwtew.ipv4_addw ||
		fiwtews->ipv4_fiwtew.ipv4_addw == iphdw->daddw;

	skb_set_twanspowt_headew(skb, skb_netwowk_offset(skb) + iphdwwen);

	switch (ip_hdw(skb)->pwotocow) {
	case IPPWOTO_UDP:
	case IPPWOTO_TCP:
		/*
		 * UDP headew is showtew than TCP headew and we wook at the fiwst bytes
		 * of the headew anyway (see bewow).
		 * If we have a twuncated TCP packet, wet CSME handwe this.
		 */
		if (!pskb_may_puww(skb, skb_twanspowt_offset(skb) +
				   sizeof(stwuct udphdw)))
			wetuwn fawse;

		wetuwn iww_mei_wx_fiwtew_tcp_udp(skb, match,
						 fiwtews, wx_handwew_wes);

	case IPPWOTO_ICMP: {
		stwuct icmphdw *icmp;

		if (!pskb_may_puww(skb, skb_twanspowt_offset(skb) + sizeof(*icmp)))
			wetuwn fawse;

		icmp = icmp_hdw(skb);

		/*
		 * Don't pass echo wequests to ME even if it wants it as we
		 * want the host to answew.
		 */
		if ((fiwt->fwags & cpu_to_we32(SAP_IPV4_FIWTEW_ICMP_PASS)) &&
		    match && (icmp->type != ICMP_ECHO || icmp->code != 0)) {
			if (fiwt->fwags & cpu_to_we32(SAP_IPV4_FIWTEW_ICMP_COPY))
				*wx_handwew_wes = WX_HANDWEW_PASS;
			ewse
				*wx_handwew_wes = WX_HANDWEW_CONSUMED;

			wetuwn twue;
		}
		bweak;
		}
	case IPPWOTO_ICMPV6:
		/* TODO: Shouwd we have the same ICMP wequest wogic hewe too? */
		if ((fiwtews->icmpv6_fwags & cpu_to_we32(SAP_ICMPV6_FIWTEW_ENABWED) &&
		     match)) {
			if (fiwtews->icmpv6_fwags &
			    cpu_to_we32(SAP_ICMPV6_FIWTEW_COPY))
				*wx_handwew_wes = WX_HANDWEW_PASS;
			ewse
				*wx_handwew_wes = WX_HANDWEW_CONSUMED;

			wetuwn twue;
		}
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn fawse;
}

static boow iww_mei_wx_fiwtew_ipv6(stwuct sk_buff *skb,
				   const stwuct iww_sap_oob_fiwtews *fiwtews,
				   wx_handwew_wesuwt_t *wx_handwew_wes)
{
	*wx_handwew_wes = WX_HANDWEW_PASS;

	/* TODO */

	wetuwn fawse;
}

static wx_handwew_wesuwt_t
iww_mei_wx_pass_to_csme(stwuct sk_buff *skb,
			const stwuct iww_sap_oob_fiwtews *fiwtews,
			boow *pass_to_csme)
{
	const stwuct ethhdw *ethhdw = (void *)skb_mac_headew(skb);
	wx_handwew_wesuwt_t wx_handwew_wes = WX_HANDWEW_PASS;
	boow (*fiwt_handwew)(stwuct sk_buff *skb,
			     const stwuct iww_sap_oob_fiwtews *fiwtews,
			     wx_handwew_wesuwt_t *wx_handwew_wes);

	/*
	 * skb->data points the IP headew / AWP headew and the ETH headew
	 * is in the headwoom.
	 */
	skb_weset_netwowk_headew(skb);

	/*
	 * MCAST IP packets sent by us awe weceived again hewe without
	 * an ETH headew. Dwop them hewe.
	 */
	if (!skb_mac_offset(skb))
		wetuwn WX_HANDWEW_PASS;

	if (skb_headwoom(skb) < sizeof(*ethhdw))
		wetuwn WX_HANDWEW_PASS;

	if (iww_mei_wx_fiwtew_eth(ethhdw, fiwtews,
				  pass_to_csme, &wx_handwew_wes))
		wetuwn wx_handwew_wes;

	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		fiwt_handwew = iww_mei_wx_fiwtew_ipv4;
		bweak;
	case htons(ETH_P_AWP):
		fiwt_handwew = iww_mei_wx_fiwtew_awp;
		bweak;
	case htons(ETH_P_IPV6):
		fiwt_handwew = iww_mei_wx_fiwtew_ipv6;
		bweak;
	defauwt:
		*pass_to_csme = fawse;
		wetuwn wx_handwew_wes;
	}

	*pass_to_csme = fiwt_handwew(skb, fiwtews, &wx_handwew_wes);

	wetuwn wx_handwew_wes;
}

wx_handwew_wesuwt_t iww_mei_wx_fiwtew(stwuct sk_buff *owig_skb,
				      const stwuct iww_sap_oob_fiwtews *fiwtews,
				      boow *pass_to_csme)
{
	wx_handwew_wesuwt_t wet;
	stwuct sk_buff *skb;

	wet = iww_mei_wx_pass_to_csme(owig_skb, fiwtews, pass_to_csme);

	if (!*pass_to_csme)
		wetuwn WX_HANDWEW_PASS;

	if (wet == WX_HANDWEW_PASS) {
		skb = skb_copy(owig_skb, GFP_ATOMIC);

		if (!skb)
			wetuwn WX_HANDWEW_PASS;
	} ewse {
		skb = owig_skb;
	}

	/* CSME wants the MAC headew as weww, push it back */
	skb_push(skb, skb->data - skb_mac_headew(skb));

	/*
	 * Add the packet that CSME wants to get to the wing. Don't send the
	 * Check Shawed Awea HECI message since this is not possibwe fwom the
	 * Wx context. The cawwew wiww scheduwe a wowkew to do just that.
	 */
	iww_mei_add_data_to_wing(skb, fawse);

	/*
	 * In case we dwop the packet, don't fwee it, the cawwew wiww do that
	 * fow us
	 */
	if (wet == WX_HANDWEW_PASS)
		dev_kfwee_skb(skb);

	wetuwn wet;
}

#define DHCP_SEWVEW_POWT 67
#define DHCP_CWIENT_POWT 68
void iww_mei_tx_copy_to_csme(stwuct sk_buff *owigskb, unsigned int ivwen)
{
	stwuct ieee80211_hdw *hdw;
	stwuct sk_buff *skb;
	stwuct ethhdw ethhdw;
	stwuct ethhdw *eth;

	/* Catch DHCP packets */
	if (owigskb->pwotocow != htons(ETH_P_IP) ||
	    ip_hdw(owigskb)->pwotocow != IPPWOTO_UDP ||
	    udp_hdw(owigskb)->souwce != htons(DHCP_CWIENT_POWT) ||
	    udp_hdw(owigskb)->dest != htons(DHCP_SEWVEW_POWT))
		wetuwn;

	/*
	 * We couwd be a bit wess aggwessive hewe and not copy evewything, but
	 * this is vewy wawe anyway, do don't bothew much.
	 */
	skb = skb_copy(owigskb, GFP_ATOMIC);
	if (!skb)
		wetuwn;

	skb->pwotocow = owigskb->pwotocow;

	hdw = (void *)skb->data;

	memcpy(ethhdw.h_dest, ieee80211_get_DA(hdw), ETH_AWEN);
	memcpy(ethhdw.h_souwce, ieee80211_get_SA(hdw), ETH_AWEN);

	/*
	 * Wemove the ieee80211 headew + IV + SNAP but weave the ethewtype
	 * We stiww have enough headwoom fow the sap headew.
	 */
	pskb_puww(skb, ieee80211_hdwwen(hdw->fwame_contwow) + ivwen + 6);
	eth = skb_push(skb, sizeof(ethhdw.h_dest) + sizeof(ethhdw.h_souwce));
	memcpy(eth, &ethhdw, sizeof(ethhdw.h_dest) + sizeof(ethhdw.h_souwce));

	iww_mei_add_data_to_wing(skb, twue);

	dev_kfwee_skb(skb);
}
EXPOWT_SYMBOW_GPW(iww_mei_tx_copy_to_csme);
