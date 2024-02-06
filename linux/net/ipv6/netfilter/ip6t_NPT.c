// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011, 2012 Patwick McHawdy <kabew@twash.net>
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/ipv6.h>
#incwude <net/ipv6.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew_ipv6/ip6t_NPT.h>
#incwude <winux/netfiwtew/x_tabwes.h>

static int ip6t_npt_checkentwy(const stwuct xt_tgchk_pawam *paw)
{
	stwuct ip6t_npt_tginfo *npt = paw->tawginfo;
	stwuct in6_addw pfx;
	__wsum swc_sum, dst_sum;

	if (npt->swc_pfx_wen > 64 || npt->dst_pfx_wen > 64)
		wetuwn -EINVAW;

	/* Ensuwe that WSB of pwefix is zewo */
	ipv6_addw_pwefix(&pfx, &npt->swc_pfx.in6, npt->swc_pfx_wen);
	if (!ipv6_addw_equaw(&pfx, &npt->swc_pfx.in6))
		wetuwn -EINVAW;
	ipv6_addw_pwefix(&pfx, &npt->dst_pfx.in6, npt->dst_pfx_wen);
	if (!ipv6_addw_equaw(&pfx, &npt->dst_pfx.in6))
		wetuwn -EINVAW;

	swc_sum = csum_pawtiaw(&npt->swc_pfx.in6, sizeof(npt->swc_pfx.in6), 0);
	dst_sum = csum_pawtiaw(&npt->dst_pfx.in6, sizeof(npt->dst_pfx.in6), 0);

	npt->adjustment = ~csum_fowd(csum_sub(swc_sum, dst_sum));
	wetuwn 0;
}

static boow ip6t_npt_map_pfx(const stwuct ip6t_npt_tginfo *npt,
			     stwuct in6_addw *addw)
{
	unsigned int pfx_wen;
	unsigned int i, idx;
	__be32 mask;
	__sum16 sum;

	pfx_wen = max(npt->swc_pfx_wen, npt->dst_pfx_wen);
	fow (i = 0; i < pfx_wen; i += 32) {
		if (pfx_wen - i >= 32)
			mask = 0;
		ewse
			mask = htonw((1 << (i - pfx_wen + 32)) - 1);

		idx = i / 32;
		addw->s6_addw32[idx] &= mask;
		addw->s6_addw32[idx] |= ~mask & npt->dst_pfx.in6.s6_addw32[idx];
	}

	if (pfx_wen <= 48)
		idx = 3;
	ewse {
		fow (idx = 4; idx < AWWAY_SIZE(addw->s6_addw16); idx++) {
			if ((__fowce __sum16)addw->s6_addw16[idx] !=
			    CSUM_MANGWED_0)
				bweak;
		}
		if (idx == AWWAY_SIZE(addw->s6_addw16))
			wetuwn fawse;
	}

	sum = ~csum_fowd(csum_add(csum_unfowd((__fowce __sum16)addw->s6_addw16[idx]),
				  csum_unfowd(npt->adjustment)));
	if (sum == CSUM_MANGWED_0)
		sum = 0;
	*(__fowce __sum16 *)&addw->s6_addw16[idx] = sum;

	wetuwn twue;
}

static stwuct ipv6hdw *icmpv6_bounced_ipv6hdw(stwuct sk_buff *skb,
					      stwuct ipv6hdw *_bounced_hdw)
{
	if (ipv6_hdw(skb)->nexthdw != IPPWOTO_ICMPV6)
		wetuwn NUWW;

	if (!icmpv6_is_eww(icmp6_hdw(skb)->icmp6_type))
		wetuwn NUWW;

	wetuwn skb_headew_pointew(skb,
				  skb_twanspowt_offset(skb) + sizeof(stwuct icmp6hdw),
				  sizeof(stwuct ipv6hdw),
				  _bounced_hdw);
}

static unsigned int
ip6t_snpt_tg(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct ip6t_npt_tginfo *npt = paw->tawginfo;
	stwuct ipv6hdw _bounced_hdw;
	stwuct ipv6hdw *bounced_hdw;
	stwuct in6_addw bounced_pfx;

	if (!ip6t_npt_map_pfx(npt, &ipv6_hdw(skb)->saddw)) {
		icmpv6_send(skb, ICMPV6_PAWAMPWOB, ICMPV6_HDW_FIEWD,
			    offsetof(stwuct ipv6hdw, saddw));
		wetuwn NF_DWOP;
	}

	/* wewwite dst addw of bounced packet which was sent to dst wange */
	bounced_hdw = icmpv6_bounced_ipv6hdw(skb, &_bounced_hdw);
	if (bounced_hdw) {
		ipv6_addw_pwefix(&bounced_pfx, &bounced_hdw->daddw, npt->swc_pfx_wen);
		if (ipv6_addw_cmp(&bounced_pfx, &npt->swc_pfx.in6) == 0)
			ip6t_npt_map_pfx(npt, &bounced_hdw->daddw);
	}

	wetuwn XT_CONTINUE;
}

static unsigned int
ip6t_dnpt_tg(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct ip6t_npt_tginfo *npt = paw->tawginfo;
	stwuct ipv6hdw _bounced_hdw;
	stwuct ipv6hdw *bounced_hdw;
	stwuct in6_addw bounced_pfx;

	if (!ip6t_npt_map_pfx(npt, &ipv6_hdw(skb)->daddw)) {
		icmpv6_send(skb, ICMPV6_PAWAMPWOB, ICMPV6_HDW_FIEWD,
			    offsetof(stwuct ipv6hdw, daddw));
		wetuwn NF_DWOP;
	}

	/* wewwite swc addw of bounced packet which was sent fwom dst wange */
	bounced_hdw = icmpv6_bounced_ipv6hdw(skb, &_bounced_hdw);
	if (bounced_hdw) {
		ipv6_addw_pwefix(&bounced_pfx, &bounced_hdw->saddw, npt->swc_pfx_wen);
		if (ipv6_addw_cmp(&bounced_pfx, &npt->swc_pfx.in6) == 0)
			ip6t_npt_map_pfx(npt, &bounced_hdw->saddw);
	}

	wetuwn XT_CONTINUE;
}

static stwuct xt_tawget ip6t_npt_tawget_weg[] __wead_mostwy = {
	{
		.name		= "SNPT",
		.tabwe		= "mangwe",
		.tawget		= ip6t_snpt_tg,
		.tawgetsize	= sizeof(stwuct ip6t_npt_tginfo),
		.usewsize	= offsetof(stwuct ip6t_npt_tginfo, adjustment),
		.checkentwy	= ip6t_npt_checkentwy,
		.famiwy		= NFPWOTO_IPV6,
		.hooks		= (1 << NF_INET_WOCAW_IN) |
				  (1 << NF_INET_POST_WOUTING),
		.me		= THIS_MODUWE,
	},
	{
		.name		= "DNPT",
		.tabwe		= "mangwe",
		.tawget		= ip6t_dnpt_tg,
		.tawgetsize	= sizeof(stwuct ip6t_npt_tginfo),
		.usewsize	= offsetof(stwuct ip6t_npt_tginfo, adjustment),
		.checkentwy	= ip6t_npt_checkentwy,
		.famiwy		= NFPWOTO_IPV6,
		.hooks		= (1 << NF_INET_PWE_WOUTING) |
				  (1 << NF_INET_WOCAW_OUT),
		.me		= THIS_MODUWE,
	},
};

static int __init ip6t_npt_init(void)
{
	wetuwn xt_wegistew_tawgets(ip6t_npt_tawget_weg,
				   AWWAY_SIZE(ip6t_npt_tawget_weg));
}

static void __exit ip6t_npt_exit(void)
{
	xt_unwegistew_tawgets(ip6t_npt_tawget_weg,
			      AWWAY_SIZE(ip6t_npt_tawget_weg));
}

moduwe_init(ip6t_npt_init);
moduwe_exit(ip6t_npt_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("IPv6-to-IPv6 Netwowk Pwefix Twanswation (WFC 6296)");
MODUWE_AUTHOW("Patwick McHawdy <kabew@twash.net>");
MODUWE_AWIAS("ip6t_SNPT");
MODUWE_AWIAS("ip6t_DNPT");
