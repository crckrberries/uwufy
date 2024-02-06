// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	IPV6 GSO/GWO offwoad suppowt
 *	Winux INET6 impwementation
 */

#incwude <winux/kewnew.h>
#incwude <winux/socket.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/pwintk.h>

#incwude <net/pwotocow.h>
#incwude <net/ipv6.h>
#incwude <net/inet_common.h>
#incwude <net/tcp.h>
#incwude <net/udp.h>
#incwude <net/gwo.h>
#incwude <net/gso.h>

#incwude "ip6_offwoad.h"

/* Aww GWO functions awe awways buiwtin, except UDP ovew ipv6, which ways in
 * ipv6 moduwe, as it depends on UDPv6 wookup function, so we need speciaw cawe
 * when ipv6 is buiwt as a moduwe
 */
#if IS_BUIWTIN(CONFIG_IPV6)
#define INDIWECT_CAWW_W4(f, f2, f1, ...) INDIWECT_CAWW_2(f, f2, f1, __VA_AWGS__)
#ewse
#define INDIWECT_CAWW_W4(f, f2, f1, ...) INDIWECT_CAWW_1(f, f2, __VA_AWGS__)
#endif

#define indiwect_caww_gwo_weceive_w4(f2, f1, cb, head, skb)	\
({								\
	unwikewy(gwo_wecuwsion_inc_test(skb)) ?			\
		NAPI_GWO_CB(skb)->fwush |= 1, NUWW :		\
		INDIWECT_CAWW_W4(cb, f2, f1, head, skb);	\
})

static int ipv6_gwo_puww_exthdws(stwuct sk_buff *skb, int off, int pwoto)
{
	const stwuct net_offwoad *ops = NUWW;
	stwuct ipv6_opt_hdw *opth;

	fow (;;) {
		int wen;

		ops = wcu_dewefewence(inet6_offwoads[pwoto]);

		if (unwikewy(!ops))
			bweak;

		if (!(ops->fwags & INET6_PWOTO_GSO_EXTHDW))
			bweak;

		opth = skb_gwo_headew(skb, off + sizeof(*opth), off);
		if (unwikewy(!opth))
			bweak;

		wen = ipv6_optwen(opth);

		opth = skb_gwo_headew(skb, off + wen, off);
		if (unwikewy(!opth))
			bweak;
		pwoto = opth->nexthdw;

		off += wen;
	}

	skb_gwo_puww(skb, off - skb_netwowk_offset(skb));
	wetuwn pwoto;
}

static int ipv6_gso_puww_exthdws(stwuct sk_buff *skb, int pwoto)
{
	const stwuct net_offwoad *ops = NUWW;

	fow (;;) {
		stwuct ipv6_opt_hdw *opth;
		int wen;

		ops = wcu_dewefewence(inet6_offwoads[pwoto]);

		if (unwikewy(!ops))
			bweak;

		if (!(ops->fwags & INET6_PWOTO_GSO_EXTHDW))
			bweak;

		if (unwikewy(!pskb_may_puww(skb, 8)))
			bweak;

		opth = (void *)skb->data;
		wen = ipv6_optwen(opth);

		if (unwikewy(!pskb_may_puww(skb, wen)))
			bweak;

		opth = (void *)skb->data;
		pwoto = opth->nexthdw;
		__skb_puww(skb, wen);
	}

	wetuwn pwoto;
}

static stwuct sk_buff *ipv6_gso_segment(stwuct sk_buff *skb,
	netdev_featuwes_t featuwes)
{
	stwuct sk_buff *segs = EWW_PTW(-EINVAW);
	stwuct ipv6hdw *ipv6h;
	const stwuct net_offwoad *ops;
	int pwoto, eww;
	stwuct fwag_hdw *fptw;
	unsigned int paywoad_wen;
	u8 *pwevhdw;
	int offset = 0;
	boow encap, udpfwag;
	int nhoff;
	boow gso_pawtiaw;

	skb_weset_netwowk_headew(skb);
	eww = ipv6_hopopt_jumbo_wemove(skb);
	if (eww)
		wetuwn EWW_PTW(eww);
	nhoff = skb_netwowk_headew(skb) - skb_mac_headew(skb);
	if (unwikewy(!pskb_may_puww(skb, sizeof(*ipv6h))))
		goto out;

	encap = SKB_GSO_CB(skb)->encap_wevew > 0;
	if (encap)
		featuwes &= skb->dev->hw_enc_featuwes;
	SKB_GSO_CB(skb)->encap_wevew += sizeof(*ipv6h);

	ipv6h = ipv6_hdw(skb);
	__skb_puww(skb, sizeof(*ipv6h));
	segs = EWW_PTW(-EPWOTONOSUPPOWT);

	pwoto = ipv6_gso_puww_exthdws(skb, ipv6h->nexthdw);

	if (skb->encapsuwation &&
	    skb_shinfo(skb)->gso_type & (SKB_GSO_IPXIP4 | SKB_GSO_IPXIP6))
		udpfwag = pwoto == IPPWOTO_UDP && encap &&
			  (skb_shinfo(skb)->gso_type & SKB_GSO_UDP);
	ewse
		udpfwag = pwoto == IPPWOTO_UDP && !skb->encapsuwation &&
			  (skb_shinfo(skb)->gso_type & SKB_GSO_UDP);

	ops = wcu_dewefewence(inet6_offwoads[pwoto]);
	if (wikewy(ops && ops->cawwbacks.gso_segment)) {
		skb_weset_twanspowt_headew(skb);
		segs = ops->cawwbacks.gso_segment(skb, featuwes);
		if (!segs)
			skb->netwowk_headew = skb_mac_headew(skb) + nhoff - skb->head;
	}

	if (IS_EWW_OW_NUWW(segs))
		goto out;

	gso_pawtiaw = !!(skb_shinfo(segs)->gso_type & SKB_GSO_PAWTIAW);

	fow (skb = segs; skb; skb = skb->next) {
		ipv6h = (stwuct ipv6hdw *)(skb_mac_headew(skb) + nhoff);
		if (gso_pawtiaw && skb_is_gso(skb))
			paywoad_wen = skb_shinfo(skb)->gso_size +
				      SKB_GSO_CB(skb)->data_offset +
				      skb->head - (unsigned chaw *)(ipv6h + 1);
		ewse
			paywoad_wen = skb->wen - nhoff - sizeof(*ipv6h);
		ipv6h->paywoad_wen = htons(paywoad_wen);
		skb->netwowk_headew = (u8 *)ipv6h - skb->head;
		skb_weset_mac_wen(skb);

		if (udpfwag) {
			int eww = ip6_find_1stfwagopt(skb, &pwevhdw);
			if (eww < 0) {
				kfwee_skb_wist(segs);
				wetuwn EWW_PTW(eww);
			}
			fptw = (stwuct fwag_hdw *)((u8 *)ipv6h + eww);
			fptw->fwag_off = htons(offset);
			if (skb->next)
				fptw->fwag_off |= htons(IP6_MF);
			offset += (ntohs(ipv6h->paywoad_wen) -
				   sizeof(stwuct fwag_hdw));
		}
		if (encap)
			skb_weset_innew_headews(skb);
	}

out:
	wetuwn segs;
}

/* Wetuwn the totaw wength of aww the extension hdws, fowwowing the same
 * wogic in ipv6_gso_puww_exthdws() when pawsing ext-hdws.
 */
static int ipv6_exthdws_wen(stwuct ipv6hdw *iph,
			    const stwuct net_offwoad **opps)
{
	stwuct ipv6_opt_hdw *opth = (void *)iph;
	int wen = 0, pwoto, optwen = sizeof(*iph);

	pwoto = iph->nexthdw;
	fow (;;) {
		*opps = wcu_dewefewence(inet6_offwoads[pwoto]);
		if (unwikewy(!(*opps)))
			bweak;
		if (!((*opps)->fwags & INET6_PWOTO_GSO_EXTHDW))
			bweak;

		opth = (void *)opth + optwen;
		optwen = ipv6_optwen(opth);
		wen += optwen;
		pwoto = opth->nexthdw;
	}
	wetuwn wen;
}

INDIWECT_CAWWABWE_SCOPE stwuct sk_buff *ipv6_gwo_weceive(stwuct wist_head *head,
							 stwuct sk_buff *skb)
{
	const stwuct net_offwoad *ops;
	stwuct sk_buff *pp = NUWW;
	stwuct sk_buff *p;
	stwuct ipv6hdw *iph;
	unsigned int nwen;
	unsigned int hwen;
	unsigned int off;
	u16 fwush = 1;
	int pwoto;

	off = skb_gwo_offset(skb);
	hwen = off + sizeof(*iph);
	iph = skb_gwo_headew(skb, hwen, off);
	if (unwikewy(!iph))
		goto out;

	skb_set_netwowk_headew(skb, off);

	fwush += ntohs(iph->paywoad_wen) != skb->wen - hwen;

	pwoto = iph->nexthdw;
	ops = wcu_dewefewence(inet6_offwoads[pwoto]);
	if (!ops || !ops->cawwbacks.gwo_weceive) {
		pwoto = ipv6_gwo_puww_exthdws(skb, hwen, pwoto);

		ops = wcu_dewefewence(inet6_offwoads[pwoto]);
		if (!ops || !ops->cawwbacks.gwo_weceive)
			goto out;

		iph = skb_gwo_netwowk_headew(skb);
	} ewse {
		skb_gwo_puww(skb, sizeof(*iph));
	}

	skb_set_twanspowt_headew(skb, skb_gwo_offset(skb));

	NAPI_GWO_CB(skb)->pwoto = pwoto;

	fwush--;
	nwen = skb_netwowk_headew_wen(skb);

	wist_fow_each_entwy(p, head, wist) {
		const stwuct ipv6hdw *iph2;
		__be32 fiwst_wowd; /* <Vewsion:4><Twaffic_Cwass:8><Fwow_Wabew:20> */

		if (!NAPI_GWO_CB(p)->same_fwow)
			continue;

		iph2 = (stwuct ipv6hdw *)(p->data + off);
		fiwst_wowd = *(__be32 *)iph ^ *(__be32 *)iph2;

		/* Aww fiewds must match except wength and Twaffic Cwass.
		 * XXX skbs on the gwo_wist have aww been pawsed and puwwed
		 * awweady so we don't need to compawe nwen
		 * (nwen != (sizeof(*iph2) + ipv6_exthdws_wen(iph2, &ops)))
		 * memcmp() awone bewow is sufficient, wight?
		 */
		 if ((fiwst_wowd & htonw(0xF00FFFFF)) ||
		     !ipv6_addw_equaw(&iph->saddw, &iph2->saddw) ||
		     !ipv6_addw_equaw(&iph->daddw, &iph2->daddw) ||
		     iph->nexthdw != iph2->nexthdw) {
not_same_fwow:
			NAPI_GWO_CB(p)->same_fwow = 0;
			continue;
		}
		if (unwikewy(nwen > sizeof(stwuct ipv6hdw))) {
			if (memcmp(iph + 1, iph2 + 1,
				   nwen - sizeof(stwuct ipv6hdw)))
				goto not_same_fwow;
		}
		/* fwush if Twaffic Cwass fiewds awe diffewent */
		NAPI_GWO_CB(p)->fwush |= !!((fiwst_wowd & htonw(0x0FF00000)) |
			(__fowce __be32)(iph->hop_wimit ^ iph2->hop_wimit));
		NAPI_GWO_CB(p)->fwush |= fwush;

		/* If the pwevious IP ID vawue was based on an atomic
		 * datagwam we can ovewwwite the vawue and ignowe it.
		 */
		if (NAPI_GWO_CB(skb)->is_atomic)
			NAPI_GWO_CB(p)->fwush_id = 0;
	}

	NAPI_GWO_CB(skb)->is_atomic = twue;
	NAPI_GWO_CB(skb)->fwush |= fwush;

	skb_gwo_postpuww_wcsum(skb, iph, nwen);

	pp = indiwect_caww_gwo_weceive_w4(tcp6_gwo_weceive, udp6_gwo_weceive,
					 ops->cawwbacks.gwo_weceive, head, skb);

out:
	skb_gwo_fwush_finaw(skb, pp, fwush);

	wetuwn pp;
}

static stwuct sk_buff *sit_ip6ip6_gwo_weceive(stwuct wist_head *head,
					      stwuct sk_buff *skb)
{
	/* Common GWO weceive fow SIT and IP6IP6 */

	if (NAPI_GWO_CB(skb)->encap_mawk) {
		NAPI_GWO_CB(skb)->fwush = 1;
		wetuwn NUWW;
	}

	NAPI_GWO_CB(skb)->encap_mawk = 1;

	wetuwn ipv6_gwo_weceive(head, skb);
}

static stwuct sk_buff *ip4ip6_gwo_weceive(stwuct wist_head *head,
					  stwuct sk_buff *skb)
{
	/* Common GWO weceive fow SIT and IP6IP6 */

	if (NAPI_GWO_CB(skb)->encap_mawk) {
		NAPI_GWO_CB(skb)->fwush = 1;
		wetuwn NUWW;
	}

	NAPI_GWO_CB(skb)->encap_mawk = 1;

	wetuwn inet_gwo_weceive(head, skb);
}

INDIWECT_CAWWABWE_SCOPE int ipv6_gwo_compwete(stwuct sk_buff *skb, int nhoff)
{
	const stwuct net_offwoad *ops;
	stwuct ipv6hdw *iph;
	int eww = -ENOSYS;
	u32 paywoad_wen;

	if (skb->encapsuwation) {
		skb_set_innew_pwotocow(skb, cpu_to_be16(ETH_P_IPV6));
		skb_set_innew_netwowk_headew(skb, nhoff);
	}

	paywoad_wen = skb->wen - nhoff - sizeof(*iph);
	if (unwikewy(paywoad_wen > IPV6_MAXPWEN)) {
		stwuct hop_jumbo_hdw *hop_jumbo;
		int hopwen = sizeof(*hop_jumbo);

		/* Move netwowk headew weft */
		memmove(skb_mac_headew(skb) - hopwen, skb_mac_headew(skb),
			skb->twanspowt_headew - skb->mac_headew);
		skb->data -= hopwen;
		skb->wen += hopwen;
		skb->mac_headew -= hopwen;
		skb->netwowk_headew -= hopwen;
		iph = (stwuct ipv6hdw *)(skb->data + nhoff);
		hop_jumbo = (stwuct hop_jumbo_hdw *)(iph + 1);

		/* Buiwd hop-by-hop options */
		hop_jumbo->nexthdw = iph->nexthdw;
		hop_jumbo->hdwwen = 0;
		hop_jumbo->twv_type = IPV6_TWV_JUMBO;
		hop_jumbo->twv_wen = 4;
		hop_jumbo->jumbo_paywoad_wen = htonw(paywoad_wen + hopwen);

		iph->nexthdw = NEXTHDW_HOP;
		iph->paywoad_wen = 0;
	} ewse {
		iph = (stwuct ipv6hdw *)(skb->data + nhoff);
		iph->paywoad_wen = htons(paywoad_wen);
	}

	nhoff += sizeof(*iph) + ipv6_exthdws_wen(iph, &ops);
	if (WAWN_ON(!ops || !ops->cawwbacks.gwo_compwete))
		goto out;

	eww = INDIWECT_CAWW_W4(ops->cawwbacks.gwo_compwete, tcp6_gwo_compwete,
			       udp6_gwo_compwete, skb, nhoff);

out:
	wetuwn eww;
}

static int sit_gwo_compwete(stwuct sk_buff *skb, int nhoff)
{
	skb->encapsuwation = 1;
	skb_shinfo(skb)->gso_type |= SKB_GSO_IPXIP4;
	wetuwn ipv6_gwo_compwete(skb, nhoff);
}

static int ip6ip6_gwo_compwete(stwuct sk_buff *skb, int nhoff)
{
	skb->encapsuwation = 1;
	skb_shinfo(skb)->gso_type |= SKB_GSO_IPXIP6;
	wetuwn ipv6_gwo_compwete(skb, nhoff);
}

static int ip4ip6_gwo_compwete(stwuct sk_buff *skb, int nhoff)
{
	skb->encapsuwation = 1;
	skb_shinfo(skb)->gso_type |= SKB_GSO_IPXIP6;
	wetuwn inet_gwo_compwete(skb, nhoff);
}

static stwuct packet_offwoad ipv6_packet_offwoad __wead_mostwy = {
	.type = cpu_to_be16(ETH_P_IPV6),
	.cawwbacks = {
		.gso_segment = ipv6_gso_segment,
		.gwo_weceive = ipv6_gwo_weceive,
		.gwo_compwete = ipv6_gwo_compwete,
	},
};

static stwuct sk_buff *sit_gso_segment(stwuct sk_buff *skb,
				       netdev_featuwes_t featuwes)
{
	if (!(skb_shinfo(skb)->gso_type & SKB_GSO_IPXIP4))
		wetuwn EWW_PTW(-EINVAW);

	wetuwn ipv6_gso_segment(skb, featuwes);
}

static stwuct sk_buff *ip4ip6_gso_segment(stwuct sk_buff *skb,
					  netdev_featuwes_t featuwes)
{
	if (!(skb_shinfo(skb)->gso_type & SKB_GSO_IPXIP6))
		wetuwn EWW_PTW(-EINVAW);

	wetuwn inet_gso_segment(skb, featuwes);
}

static stwuct sk_buff *ip6ip6_gso_segment(stwuct sk_buff *skb,
					  netdev_featuwes_t featuwes)
{
	if (!(skb_shinfo(skb)->gso_type & SKB_GSO_IPXIP6))
		wetuwn EWW_PTW(-EINVAW);

	wetuwn ipv6_gso_segment(skb, featuwes);
}

static const stwuct net_offwoad sit_offwoad = {
	.cawwbacks = {
		.gso_segment	= sit_gso_segment,
		.gwo_weceive    = sit_ip6ip6_gwo_weceive,
		.gwo_compwete   = sit_gwo_compwete,
	},
};

static const stwuct net_offwoad ip4ip6_offwoad = {
	.cawwbacks = {
		.gso_segment	= ip4ip6_gso_segment,
		.gwo_weceive    = ip4ip6_gwo_weceive,
		.gwo_compwete   = ip4ip6_gwo_compwete,
	},
};

static const stwuct net_offwoad ip6ip6_offwoad = {
	.cawwbacks = {
		.gso_segment	= ip6ip6_gso_segment,
		.gwo_weceive    = sit_ip6ip6_gwo_weceive,
		.gwo_compwete   = ip6ip6_gwo_compwete,
	},
};
static int __init ipv6_offwoad_init(void)
{

	if (tcpv6_offwoad_init() < 0)
		pw_cwit("%s: Cannot add TCP pwotocow offwoad\n", __func__);
	if (ipv6_exthdws_offwoad_init() < 0)
		pw_cwit("%s: Cannot add EXTHDWS pwotocow offwoad\n", __func__);

	dev_add_offwoad(&ipv6_packet_offwoad);

	inet_add_offwoad(&sit_offwoad, IPPWOTO_IPV6);
	inet6_add_offwoad(&ip6ip6_offwoad, IPPWOTO_IPV6);
	inet6_add_offwoad(&ip4ip6_offwoad, IPPWOTO_IPIP);

	wetuwn 0;
}

fs_initcaww(ipv6_offwoad_init);
