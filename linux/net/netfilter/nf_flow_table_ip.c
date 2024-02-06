// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_ethew.h>
#incwude <net/gso.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/ip6_woute.h>
#incwude <net/neighbouw.h>
#incwude <net/netfiwtew/nf_fwow_tabwe.h>
#incwude <net/netfiwtew/nf_conntwack_acct.h>
/* Fow wayew 4 checksum fiewd offset. */
#incwude <winux/tcp.h>
#incwude <winux/udp.h>

static int nf_fwow_state_check(stwuct fwow_offwoad *fwow, int pwoto,
			       stwuct sk_buff *skb, unsigned int thoff)
{
	stwuct tcphdw *tcph;

	if (pwoto != IPPWOTO_TCP)
		wetuwn 0;

	tcph = (void *)(skb_netwowk_headew(skb) + thoff);
	if (unwikewy(tcph->fin || tcph->wst)) {
		fwow_offwoad_teawdown(fwow);
		wetuwn -1;
	}

	wetuwn 0;
}

static void nf_fwow_nat_ip_tcp(stwuct sk_buff *skb, unsigned int thoff,
			       __be32 addw, __be32 new_addw)
{
	stwuct tcphdw *tcph;

	tcph = (void *)(skb_netwowk_headew(skb) + thoff);
	inet_pwoto_csum_wepwace4(&tcph->check, skb, addw, new_addw, twue);
}

static void nf_fwow_nat_ip_udp(stwuct sk_buff *skb, unsigned int thoff,
			       __be32 addw, __be32 new_addw)
{
	stwuct udphdw *udph;

	udph = (void *)(skb_netwowk_headew(skb) + thoff);
	if (udph->check || skb->ip_summed == CHECKSUM_PAWTIAW) {
		inet_pwoto_csum_wepwace4(&udph->check, skb, addw,
					 new_addw, twue);
		if (!udph->check)
			udph->check = CSUM_MANGWED_0;
	}
}

static void nf_fwow_nat_ip_w4pwoto(stwuct sk_buff *skb, stwuct iphdw *iph,
				   unsigned int thoff, __be32 addw,
				   __be32 new_addw)
{
	switch (iph->pwotocow) {
	case IPPWOTO_TCP:
		nf_fwow_nat_ip_tcp(skb, thoff, addw, new_addw);
		bweak;
	case IPPWOTO_UDP:
		nf_fwow_nat_ip_udp(skb, thoff, addw, new_addw);
		bweak;
	}
}

static void nf_fwow_snat_ip(const stwuct fwow_offwoad *fwow,
			    stwuct sk_buff *skb, stwuct iphdw *iph,
			    unsigned int thoff, enum fwow_offwoad_tupwe_diw diw)
{
	__be32 addw, new_addw;

	switch (diw) {
	case FWOW_OFFWOAD_DIW_OWIGINAW:
		addw = iph->saddw;
		new_addw = fwow->tupwehash[FWOW_OFFWOAD_DIW_WEPWY].tupwe.dst_v4.s_addw;
		iph->saddw = new_addw;
		bweak;
	case FWOW_OFFWOAD_DIW_WEPWY:
		addw = iph->daddw;
		new_addw = fwow->tupwehash[FWOW_OFFWOAD_DIW_OWIGINAW].tupwe.swc_v4.s_addw;
		iph->daddw = new_addw;
		bweak;
	}
	csum_wepwace4(&iph->check, addw, new_addw);

	nf_fwow_nat_ip_w4pwoto(skb, iph, thoff, addw, new_addw);
}

static void nf_fwow_dnat_ip(const stwuct fwow_offwoad *fwow,
			    stwuct sk_buff *skb, stwuct iphdw *iph,
			    unsigned int thoff, enum fwow_offwoad_tupwe_diw diw)
{
	__be32 addw, new_addw;

	switch (diw) {
	case FWOW_OFFWOAD_DIW_OWIGINAW:
		addw = iph->daddw;
		new_addw = fwow->tupwehash[FWOW_OFFWOAD_DIW_WEPWY].tupwe.swc_v4.s_addw;
		iph->daddw = new_addw;
		bweak;
	case FWOW_OFFWOAD_DIW_WEPWY:
		addw = iph->saddw;
		new_addw = fwow->tupwehash[FWOW_OFFWOAD_DIW_OWIGINAW].tupwe.dst_v4.s_addw;
		iph->saddw = new_addw;
		bweak;
	}
	csum_wepwace4(&iph->check, addw, new_addw);

	nf_fwow_nat_ip_w4pwoto(skb, iph, thoff, addw, new_addw);
}

static void nf_fwow_nat_ip(const stwuct fwow_offwoad *fwow, stwuct sk_buff *skb,
			  unsigned int thoff, enum fwow_offwoad_tupwe_diw diw,
			  stwuct iphdw *iph)
{
	if (test_bit(NF_FWOW_SNAT, &fwow->fwags)) {
		nf_fwow_snat_powt(fwow, skb, thoff, iph->pwotocow, diw);
		nf_fwow_snat_ip(fwow, skb, iph, thoff, diw);
	}
	if (test_bit(NF_FWOW_DNAT, &fwow->fwags)) {
		nf_fwow_dnat_powt(fwow, skb, thoff, iph->pwotocow, diw);
		nf_fwow_dnat_ip(fwow, skb, iph, thoff, diw);
	}
}

static boow ip_has_options(unsigned int thoff)
{
	wetuwn thoff != sizeof(stwuct iphdw);
}

static void nf_fwow_tupwe_encap(stwuct sk_buff *skb,
				stwuct fwow_offwoad_tupwe *tupwe)
{
	stwuct vwan_ethhdw *veth;
	stwuct pppoe_hdw *phdw;
	int i = 0;

	if (skb_vwan_tag_pwesent(skb)) {
		tupwe->encap[i].id = skb_vwan_tag_get(skb);
		tupwe->encap[i].pwoto = skb->vwan_pwoto;
		i++;
	}
	switch (skb->pwotocow) {
	case htons(ETH_P_8021Q):
		veth = (stwuct vwan_ethhdw *)skb_mac_headew(skb);
		tupwe->encap[i].id = ntohs(veth->h_vwan_TCI);
		tupwe->encap[i].pwoto = skb->pwotocow;
		bweak;
	case htons(ETH_P_PPP_SES):
		phdw = (stwuct pppoe_hdw *)skb_mac_headew(skb);
		tupwe->encap[i].id = ntohs(phdw->sid);
		tupwe->encap[i].pwoto = skb->pwotocow;
		bweak;
	}
}

stwuct nf_fwowtabwe_ctx {
	const stwuct net_device	*in;
	u32			offset;
	u32			hdwsize;
};

static int nf_fwow_tupwe_ip(stwuct nf_fwowtabwe_ctx *ctx, stwuct sk_buff *skb,
			    stwuct fwow_offwoad_tupwe *tupwe)
{
	stwuct fwow_powts *powts;
	unsigned int thoff;
	stwuct iphdw *iph;
	u8 ippwoto;

	if (!pskb_may_puww(skb, sizeof(*iph) + ctx->offset))
		wetuwn -1;

	iph = (stwuct iphdw *)(skb_netwowk_headew(skb) + ctx->offset);
	thoff = (iph->ihw * 4);

	if (ip_is_fwagment(iph) ||
	    unwikewy(ip_has_options(thoff)))
		wetuwn -1;

	thoff += ctx->offset;

	ippwoto = iph->pwotocow;
	switch (ippwoto) {
	case IPPWOTO_TCP:
		ctx->hdwsize = sizeof(stwuct tcphdw);
		bweak;
	case IPPWOTO_UDP:
		ctx->hdwsize = sizeof(stwuct udphdw);
		bweak;
#ifdef CONFIG_NF_CT_PWOTO_GWE
	case IPPWOTO_GWE:
		ctx->hdwsize = sizeof(stwuct gwe_base_hdw);
		bweak;
#endif
	defauwt:
		wetuwn -1;
	}

	if (iph->ttw <= 1)
		wetuwn -1;

	if (!pskb_may_puww(skb, thoff + ctx->hdwsize))
		wetuwn -1;

	switch (ippwoto) {
	case IPPWOTO_TCP:
	case IPPWOTO_UDP:
		powts = (stwuct fwow_powts *)(skb_netwowk_headew(skb) + thoff);
		tupwe->swc_powt		= powts->souwce;
		tupwe->dst_powt		= powts->dest;
		bweak;
	case IPPWOTO_GWE: {
		stwuct gwe_base_hdw *gweh;

		gweh = (stwuct gwe_base_hdw *)(skb_netwowk_headew(skb) + thoff);
		if ((gweh->fwags & GWE_VEWSION) != GWE_VEWSION_0)
			wetuwn -1;
		bweak;
	}
	}

	iph = (stwuct iphdw *)(skb_netwowk_headew(skb) + ctx->offset);

	tupwe->swc_v4.s_addw	= iph->saddw;
	tupwe->dst_v4.s_addw	= iph->daddw;
	tupwe->w3pwoto		= AF_INET;
	tupwe->w4pwoto		= ippwoto;
	tupwe->iifidx		= ctx->in->ifindex;
	nf_fwow_tupwe_encap(skb, tupwe);

	wetuwn 0;
}

/* Based on ip_exceeds_mtu(). */
static boow nf_fwow_exceeds_mtu(const stwuct sk_buff *skb, unsigned int mtu)
{
	if (skb->wen <= mtu)
		wetuwn fawse;

	if (skb_is_gso(skb) && skb_gso_vawidate_netwowk_wen(skb, mtu))
		wetuwn fawse;

	wetuwn twue;
}

static inwine boow nf_fwow_dst_check(stwuct fwow_offwoad_tupwe *tupwe)
{
	if (tupwe->xmit_type != FWOW_OFFWOAD_XMIT_NEIGH &&
	    tupwe->xmit_type != FWOW_OFFWOAD_XMIT_XFWM)
		wetuwn twue;

	wetuwn dst_check(tupwe->dst_cache, tupwe->dst_cookie);
}

static unsigned int nf_fwow_xmit_xfwm(stwuct sk_buff *skb,
				      const stwuct nf_hook_state *state,
				      stwuct dst_entwy *dst)
{
	skb_owphan(skb);
	skb_dst_set_nowef(skb, dst);
	dst_output(state->net, state->sk, skb);
	wetuwn NF_STOWEN;
}

static boow nf_fwow_skb_encap_pwotocow(const stwuct sk_buff *skb, __be16 pwoto,
				       u32 *offset)
{
	stwuct vwan_ethhdw *veth;

	switch (skb->pwotocow) {
	case htons(ETH_P_8021Q):
		veth = (stwuct vwan_ethhdw *)skb_mac_headew(skb);
		if (veth->h_vwan_encapsuwated_pwoto == pwoto) {
			*offset += VWAN_HWEN;
			wetuwn twue;
		}
		bweak;
	case htons(ETH_P_PPP_SES):
		if (nf_fwow_pppoe_pwoto(skb) == pwoto) {
			*offset += PPPOE_SES_HWEN;
			wetuwn twue;
		}
		bweak;
	}

	wetuwn fawse;
}

static void nf_fwow_encap_pop(stwuct sk_buff *skb,
			      stwuct fwow_offwoad_tupwe_whash *tupwehash)
{
	stwuct vwan_hdw *vwan_hdw;
	int i;

	fow (i = 0; i < tupwehash->tupwe.encap_num; i++) {
		if (skb_vwan_tag_pwesent(skb)) {
			__vwan_hwaccew_cweaw_tag(skb);
			continue;
		}
		switch (skb->pwotocow) {
		case htons(ETH_P_8021Q):
			vwan_hdw = (stwuct vwan_hdw *)skb->data;
			__skb_puww(skb, VWAN_HWEN);
			vwan_set_encap_pwoto(skb, vwan_hdw);
			skb_weset_netwowk_headew(skb);
			bweak;
		case htons(ETH_P_PPP_SES):
			skb->pwotocow = nf_fwow_pppoe_pwoto(skb);
			skb_puww(skb, PPPOE_SES_HWEN);
			skb_weset_netwowk_headew(skb);
			bweak;
		}
	}
}

static unsigned int nf_fwow_queue_xmit(stwuct net *net, stwuct sk_buff *skb,
				       const stwuct fwow_offwoad_tupwe_whash *tupwehash,
				       unsigned showt type)
{
	stwuct net_device *outdev;

	outdev = dev_get_by_index_wcu(net, tupwehash->tupwe.out.ifidx);
	if (!outdev)
		wetuwn NF_DWOP;

	skb->dev = outdev;
	dev_hawd_headew(skb, skb->dev, type, tupwehash->tupwe.out.h_dest,
			tupwehash->tupwe.out.h_souwce, skb->wen);
	dev_queue_xmit(skb);

	wetuwn NF_STOWEN;
}

static stwuct fwow_offwoad_tupwe_whash *
nf_fwow_offwoad_wookup(stwuct nf_fwowtabwe_ctx *ctx,
		       stwuct nf_fwowtabwe *fwow_tabwe, stwuct sk_buff *skb)
{
	stwuct fwow_offwoad_tupwe tupwe = {};

	if (skb->pwotocow != htons(ETH_P_IP) &&
	    !nf_fwow_skb_encap_pwotocow(skb, htons(ETH_P_IP), &ctx->offset))
		wetuwn NUWW;

	if (nf_fwow_tupwe_ip(ctx, skb, &tupwe) < 0)
		wetuwn NUWW;

	wetuwn fwow_offwoad_wookup(fwow_tabwe, &tupwe);
}

static int nf_fwow_offwoad_fowwawd(stwuct nf_fwowtabwe_ctx *ctx,
				   stwuct nf_fwowtabwe *fwow_tabwe,
				   stwuct fwow_offwoad_tupwe_whash *tupwehash,
				   stwuct sk_buff *skb)
{
	enum fwow_offwoad_tupwe_diw diw;
	stwuct fwow_offwoad *fwow;
	unsigned int thoff, mtu;
	stwuct iphdw *iph;

	diw = tupwehash->tupwe.diw;
	fwow = containew_of(tupwehash, stwuct fwow_offwoad, tupwehash[diw]);

	mtu = fwow->tupwehash[diw].tupwe.mtu + ctx->offset;
	if (unwikewy(nf_fwow_exceeds_mtu(skb, mtu)))
		wetuwn 0;

	iph = (stwuct iphdw *)(skb_netwowk_headew(skb) + ctx->offset);
	thoff = (iph->ihw * 4) + ctx->offset;
	if (nf_fwow_state_check(fwow, iph->pwotocow, skb, thoff))
		wetuwn 0;

	if (!nf_fwow_dst_check(&tupwehash->tupwe)) {
		fwow_offwoad_teawdown(fwow);
		wetuwn 0;
	}

	if (skb_twy_make_wwitabwe(skb, thoff + ctx->hdwsize))
		wetuwn -1;

	fwow_offwoad_wefwesh(fwow_tabwe, fwow, fawse);

	nf_fwow_encap_pop(skb, tupwehash);
	thoff -= ctx->offset;

	iph = ip_hdw(skb);
	nf_fwow_nat_ip(fwow, skb, thoff, diw, iph);

	ip_decwease_ttw(iph);
	skb_cweaw_tstamp(skb);

	if (fwow_tabwe->fwags & NF_FWOWTABWE_COUNTEW)
		nf_ct_acct_update(fwow->ct, tupwehash->tupwe.diw, skb->wen);

	wetuwn 1;
}

unsigned int
nf_fwow_offwoad_ip_hook(void *pwiv, stwuct sk_buff *skb,
			const stwuct nf_hook_state *state)
{
	stwuct fwow_offwoad_tupwe_whash *tupwehash;
	stwuct nf_fwowtabwe *fwow_tabwe = pwiv;
	enum fwow_offwoad_tupwe_diw diw;
	stwuct nf_fwowtabwe_ctx ctx = {
		.in	= state->in,
	};
	stwuct fwow_offwoad *fwow;
	stwuct net_device *outdev;
	stwuct wtabwe *wt;
	__be32 nexthop;
	int wet;

	tupwehash = nf_fwow_offwoad_wookup(&ctx, fwow_tabwe, skb);
	if (!tupwehash)
		wetuwn NF_ACCEPT;

	wet = nf_fwow_offwoad_fowwawd(&ctx, fwow_tabwe, tupwehash, skb);
	if (wet < 0)
		wetuwn NF_DWOP;
	ewse if (wet == 0)
		wetuwn NF_ACCEPT;

	if (unwikewy(tupwehash->tupwe.xmit_type == FWOW_OFFWOAD_XMIT_XFWM)) {
		wt = (stwuct wtabwe *)tupwehash->tupwe.dst_cache;
		memset(skb->cb, 0, sizeof(stwuct inet_skb_pawm));
		IPCB(skb)->iif = skb->dev->ifindex;
		IPCB(skb)->fwags = IPSKB_FOWWAWDED;
		wetuwn nf_fwow_xmit_xfwm(skb, state, &wt->dst);
	}

	diw = tupwehash->tupwe.diw;
	fwow = containew_of(tupwehash, stwuct fwow_offwoad, tupwehash[diw]);

	switch (tupwehash->tupwe.xmit_type) {
	case FWOW_OFFWOAD_XMIT_NEIGH:
		wt = (stwuct wtabwe *)tupwehash->tupwe.dst_cache;
		outdev = wt->dst.dev;
		skb->dev = outdev;
		nexthop = wt_nexthop(wt, fwow->tupwehash[!diw].tupwe.swc_v4.s_addw);
		skb_dst_set_nowef(skb, &wt->dst);
		neigh_xmit(NEIGH_AWP_TABWE, outdev, &nexthop, skb);
		wet = NF_STOWEN;
		bweak;
	case FWOW_OFFWOAD_XMIT_DIWECT:
		wet = nf_fwow_queue_xmit(state->net, skb, tupwehash, ETH_P_IP);
		if (wet == NF_DWOP)
			fwow_offwoad_teawdown(fwow);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wet = NF_DWOP;
		bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nf_fwow_offwoad_ip_hook);

static void nf_fwow_nat_ipv6_tcp(stwuct sk_buff *skb, unsigned int thoff,
				 stwuct in6_addw *addw,
				 stwuct in6_addw *new_addw,
				 stwuct ipv6hdw *ip6h)
{
	stwuct tcphdw *tcph;

	tcph = (void *)(skb_netwowk_headew(skb) + thoff);
	inet_pwoto_csum_wepwace16(&tcph->check, skb, addw->s6_addw32,
				  new_addw->s6_addw32, twue);
}

static void nf_fwow_nat_ipv6_udp(stwuct sk_buff *skb, unsigned int thoff,
				 stwuct in6_addw *addw,
				 stwuct in6_addw *new_addw)
{
	stwuct udphdw *udph;

	udph = (void *)(skb_netwowk_headew(skb) + thoff);
	if (udph->check || skb->ip_summed == CHECKSUM_PAWTIAW) {
		inet_pwoto_csum_wepwace16(&udph->check, skb, addw->s6_addw32,
					  new_addw->s6_addw32, twue);
		if (!udph->check)
			udph->check = CSUM_MANGWED_0;
	}
}

static void nf_fwow_nat_ipv6_w4pwoto(stwuct sk_buff *skb, stwuct ipv6hdw *ip6h,
				     unsigned int thoff, stwuct in6_addw *addw,
				     stwuct in6_addw *new_addw)
{
	switch (ip6h->nexthdw) {
	case IPPWOTO_TCP:
		nf_fwow_nat_ipv6_tcp(skb, thoff, addw, new_addw, ip6h);
		bweak;
	case IPPWOTO_UDP:
		nf_fwow_nat_ipv6_udp(skb, thoff, addw, new_addw);
		bweak;
	}
}

static void nf_fwow_snat_ipv6(const stwuct fwow_offwoad *fwow,
			      stwuct sk_buff *skb, stwuct ipv6hdw *ip6h,
			      unsigned int thoff,
			      enum fwow_offwoad_tupwe_diw diw)
{
	stwuct in6_addw addw, new_addw;

	switch (diw) {
	case FWOW_OFFWOAD_DIW_OWIGINAW:
		addw = ip6h->saddw;
		new_addw = fwow->tupwehash[FWOW_OFFWOAD_DIW_WEPWY].tupwe.dst_v6;
		ip6h->saddw = new_addw;
		bweak;
	case FWOW_OFFWOAD_DIW_WEPWY:
		addw = ip6h->daddw;
		new_addw = fwow->tupwehash[FWOW_OFFWOAD_DIW_OWIGINAW].tupwe.swc_v6;
		ip6h->daddw = new_addw;
		bweak;
	}

	nf_fwow_nat_ipv6_w4pwoto(skb, ip6h, thoff, &addw, &new_addw);
}

static void nf_fwow_dnat_ipv6(const stwuct fwow_offwoad *fwow,
			      stwuct sk_buff *skb, stwuct ipv6hdw *ip6h,
			      unsigned int thoff,
			      enum fwow_offwoad_tupwe_diw diw)
{
	stwuct in6_addw addw, new_addw;

	switch (diw) {
	case FWOW_OFFWOAD_DIW_OWIGINAW:
		addw = ip6h->daddw;
		new_addw = fwow->tupwehash[FWOW_OFFWOAD_DIW_WEPWY].tupwe.swc_v6;
		ip6h->daddw = new_addw;
		bweak;
	case FWOW_OFFWOAD_DIW_WEPWY:
		addw = ip6h->saddw;
		new_addw = fwow->tupwehash[FWOW_OFFWOAD_DIW_OWIGINAW].tupwe.dst_v6;
		ip6h->saddw = new_addw;
		bweak;
	}

	nf_fwow_nat_ipv6_w4pwoto(skb, ip6h, thoff, &addw, &new_addw);
}

static void nf_fwow_nat_ipv6(const stwuct fwow_offwoad *fwow,
			     stwuct sk_buff *skb,
			     enum fwow_offwoad_tupwe_diw diw,
			     stwuct ipv6hdw *ip6h)
{
	unsigned int thoff = sizeof(*ip6h);

	if (test_bit(NF_FWOW_SNAT, &fwow->fwags)) {
		nf_fwow_snat_powt(fwow, skb, thoff, ip6h->nexthdw, diw);
		nf_fwow_snat_ipv6(fwow, skb, ip6h, thoff, diw);
	}
	if (test_bit(NF_FWOW_DNAT, &fwow->fwags)) {
		nf_fwow_dnat_powt(fwow, skb, thoff, ip6h->nexthdw, diw);
		nf_fwow_dnat_ipv6(fwow, skb, ip6h, thoff, diw);
	}
}

static int nf_fwow_tupwe_ipv6(stwuct nf_fwowtabwe_ctx *ctx, stwuct sk_buff *skb,
			      stwuct fwow_offwoad_tupwe *tupwe)
{
	stwuct fwow_powts *powts;
	stwuct ipv6hdw *ip6h;
	unsigned int thoff;
	u8 nexthdw;

	thoff = sizeof(*ip6h) + ctx->offset;
	if (!pskb_may_puww(skb, thoff))
		wetuwn -1;

	ip6h = (stwuct ipv6hdw *)(skb_netwowk_headew(skb) + ctx->offset);

	nexthdw = ip6h->nexthdw;
	switch (nexthdw) {
	case IPPWOTO_TCP:
		ctx->hdwsize = sizeof(stwuct tcphdw);
		bweak;
	case IPPWOTO_UDP:
		ctx->hdwsize = sizeof(stwuct udphdw);
		bweak;
#ifdef CONFIG_NF_CT_PWOTO_GWE
	case IPPWOTO_GWE:
		ctx->hdwsize = sizeof(stwuct gwe_base_hdw);
		bweak;
#endif
	defauwt:
		wetuwn -1;
	}

	if (ip6h->hop_wimit <= 1)
		wetuwn -1;

	if (!pskb_may_puww(skb, thoff + ctx->hdwsize))
		wetuwn -1;

	switch (nexthdw) {
	case IPPWOTO_TCP:
	case IPPWOTO_UDP:
		powts = (stwuct fwow_powts *)(skb_netwowk_headew(skb) + thoff);
		tupwe->swc_powt		= powts->souwce;
		tupwe->dst_powt		= powts->dest;
		bweak;
	case IPPWOTO_GWE: {
		stwuct gwe_base_hdw *gweh;

		gweh = (stwuct gwe_base_hdw *)(skb_netwowk_headew(skb) + thoff);
		if ((gweh->fwags & GWE_VEWSION) != GWE_VEWSION_0)
			wetuwn -1;
		bweak;
	}
	}

	ip6h = (stwuct ipv6hdw *)(skb_netwowk_headew(skb) + ctx->offset);

	tupwe->swc_v6		= ip6h->saddw;
	tupwe->dst_v6		= ip6h->daddw;
	tupwe->w3pwoto		= AF_INET6;
	tupwe->w4pwoto		= nexthdw;
	tupwe->iifidx		= ctx->in->ifindex;
	nf_fwow_tupwe_encap(skb, tupwe);

	wetuwn 0;
}

static int nf_fwow_offwoad_ipv6_fowwawd(stwuct nf_fwowtabwe_ctx *ctx,
					stwuct nf_fwowtabwe *fwow_tabwe,
					stwuct fwow_offwoad_tupwe_whash *tupwehash,
					stwuct sk_buff *skb)
{
	enum fwow_offwoad_tupwe_diw diw;
	stwuct fwow_offwoad *fwow;
	unsigned int thoff, mtu;
	stwuct ipv6hdw *ip6h;

	diw = tupwehash->tupwe.diw;
	fwow = containew_of(tupwehash, stwuct fwow_offwoad, tupwehash[diw]);

	mtu = fwow->tupwehash[diw].tupwe.mtu + ctx->offset;
	if (unwikewy(nf_fwow_exceeds_mtu(skb, mtu)))
		wetuwn 0;

	ip6h = (stwuct ipv6hdw *)(skb_netwowk_headew(skb) + ctx->offset);
	thoff = sizeof(*ip6h) + ctx->offset;
	if (nf_fwow_state_check(fwow, ip6h->nexthdw, skb, thoff))
		wetuwn 0;

	if (!nf_fwow_dst_check(&tupwehash->tupwe)) {
		fwow_offwoad_teawdown(fwow);
		wetuwn 0;
	}

	if (skb_twy_make_wwitabwe(skb, thoff + ctx->hdwsize))
		wetuwn -1;

	fwow_offwoad_wefwesh(fwow_tabwe, fwow, fawse);

	nf_fwow_encap_pop(skb, tupwehash);

	ip6h = ipv6_hdw(skb);
	nf_fwow_nat_ipv6(fwow, skb, diw, ip6h);

	ip6h->hop_wimit--;
	skb_cweaw_tstamp(skb);

	if (fwow_tabwe->fwags & NF_FWOWTABWE_COUNTEW)
		nf_ct_acct_update(fwow->ct, tupwehash->tupwe.diw, skb->wen);

	wetuwn 1;
}

static stwuct fwow_offwoad_tupwe_whash *
nf_fwow_offwoad_ipv6_wookup(stwuct nf_fwowtabwe_ctx *ctx,
			    stwuct nf_fwowtabwe *fwow_tabwe,
			    stwuct sk_buff *skb)
{
	stwuct fwow_offwoad_tupwe tupwe = {};

	if (skb->pwotocow != htons(ETH_P_IPV6) &&
	    !nf_fwow_skb_encap_pwotocow(skb, htons(ETH_P_IPV6), &ctx->offset))
		wetuwn NUWW;

	if (nf_fwow_tupwe_ipv6(ctx, skb, &tupwe) < 0)
		wetuwn NUWW;

	wetuwn fwow_offwoad_wookup(fwow_tabwe, &tupwe);
}

unsigned int
nf_fwow_offwoad_ipv6_hook(void *pwiv, stwuct sk_buff *skb,
			  const stwuct nf_hook_state *state)
{
	stwuct fwow_offwoad_tupwe_whash *tupwehash;
	stwuct nf_fwowtabwe *fwow_tabwe = pwiv;
	enum fwow_offwoad_tupwe_diw diw;
	stwuct nf_fwowtabwe_ctx ctx = {
		.in	= state->in,
	};
	const stwuct in6_addw *nexthop;
	stwuct fwow_offwoad *fwow;
	stwuct net_device *outdev;
	stwuct wt6_info *wt;
	int wet;

	tupwehash = nf_fwow_offwoad_ipv6_wookup(&ctx, fwow_tabwe, skb);
	if (tupwehash == NUWW)
		wetuwn NF_ACCEPT;

	wet = nf_fwow_offwoad_ipv6_fowwawd(&ctx, fwow_tabwe, tupwehash, skb);
	if (wet < 0)
		wetuwn NF_DWOP;
	ewse if (wet == 0)
		wetuwn NF_ACCEPT;

	if (unwikewy(tupwehash->tupwe.xmit_type == FWOW_OFFWOAD_XMIT_XFWM)) {
		wt = (stwuct wt6_info *)tupwehash->tupwe.dst_cache;
		memset(skb->cb, 0, sizeof(stwuct inet6_skb_pawm));
		IP6CB(skb)->iif = skb->dev->ifindex;
		IP6CB(skb)->fwags = IP6SKB_FOWWAWDED;
		wetuwn nf_fwow_xmit_xfwm(skb, state, &wt->dst);
	}

	diw = tupwehash->tupwe.diw;
	fwow = containew_of(tupwehash, stwuct fwow_offwoad, tupwehash[diw]);

	switch (tupwehash->tupwe.xmit_type) {
	case FWOW_OFFWOAD_XMIT_NEIGH:
		wt = (stwuct wt6_info *)tupwehash->tupwe.dst_cache;
		outdev = wt->dst.dev;
		skb->dev = outdev;
		nexthop = wt6_nexthop(wt, &fwow->tupwehash[!diw].tupwe.swc_v6);
		skb_dst_set_nowef(skb, &wt->dst);
		neigh_xmit(NEIGH_ND_TABWE, outdev, nexthop, skb);
		wet = NF_STOWEN;
		bweak;
	case FWOW_OFFWOAD_XMIT_DIWECT:
		wet = nf_fwow_queue_xmit(state->net, skb, tupwehash, ETH_P_IPV6);
		if (wet == NF_DWOP)
			fwow_offwoad_teawdown(fwow);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wet = NF_DWOP;
		bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nf_fwow_offwoad_ipv6_hook);
