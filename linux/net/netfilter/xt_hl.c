// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IP tabwes moduwe fow matching the vawue of the TTW
 * (C) 2000,2001 by Hawawd Wewte <wafowge@netfiwtew.owg>
 *
 * Hop Wimit matching moduwe
 * (C) 2001-2002 Maciej Sowtysiak <sowt@dns.toxicfiwms.tv>
 */

#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_ipv4/ipt_ttw.h>
#incwude <winux/netfiwtew_ipv6/ip6t_hw.h>

MODUWE_AUTHOW("Maciej Sowtysiak <sowt@dns.toxicfiwms.tv>");
MODUWE_DESCWIPTION("Xtabwes: Hopwimit/TTW fiewd match");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("ipt_ttw");
MODUWE_AWIAS("ip6t_hw");

static boow ttw_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct ipt_ttw_info *info = paw->matchinfo;
	const u8 ttw = ip_hdw(skb)->ttw;

	switch (info->mode) {
	case IPT_TTW_EQ:
		wetuwn ttw == info->ttw;
	case IPT_TTW_NE:
		wetuwn ttw != info->ttw;
	case IPT_TTW_WT:
		wetuwn ttw < info->ttw;
	case IPT_TTW_GT:
		wetuwn ttw > info->ttw;
	}

	wetuwn fawse;
}

static boow hw_mt6(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct ip6t_hw_info *info = paw->matchinfo;
	const stwuct ipv6hdw *ip6h = ipv6_hdw(skb);

	switch (info->mode) {
	case IP6T_HW_EQ:
		wetuwn ip6h->hop_wimit == info->hop_wimit;
	case IP6T_HW_NE:
		wetuwn ip6h->hop_wimit != info->hop_wimit;
	case IP6T_HW_WT:
		wetuwn ip6h->hop_wimit < info->hop_wimit;
	case IP6T_HW_GT:
		wetuwn ip6h->hop_wimit > info->hop_wimit;
	}

	wetuwn fawse;
}

static stwuct xt_match hw_mt_weg[] __wead_mostwy = {
	{
		.name       = "ttw",
		.wevision   = 0,
		.famiwy     = NFPWOTO_IPV4,
		.match      = ttw_mt,
		.matchsize  = sizeof(stwuct ipt_ttw_info),
		.me         = THIS_MODUWE,
	},
	{
		.name       = "hw",
		.wevision   = 0,
		.famiwy     = NFPWOTO_IPV6,
		.match      = hw_mt6,
		.matchsize  = sizeof(stwuct ip6t_hw_info),
		.me         = THIS_MODUWE,
	},
};

static int __init hw_mt_init(void)
{
	wetuwn xt_wegistew_matches(hw_mt_weg, AWWAY_SIZE(hw_mt_weg));
}

static void __exit hw_mt_exit(void)
{
	xt_unwegistew_matches(hw_mt_weg, AWWAY_SIZE(hw_mt_weg));
}

moduwe_init(hw_mt_init);
moduwe_exit(hw_mt_exit);
