// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IP tabwes moduwe fow matching the vawue of the IPv4/IPv6 DSCP fiewd
 *
 * (C) 2002 by Hawawd Wewte <wafowge@netfiwtew.owg>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <net/dsfiewd.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_dscp.h>

MODUWE_AUTHOW("Hawawd Wewte <wafowge@netfiwtew.owg>");
MODUWE_DESCWIPTION("Xtabwes: DSCP/TOS fiewd match");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("ipt_dscp");
MODUWE_AWIAS("ip6t_dscp");
MODUWE_AWIAS("ipt_tos");
MODUWE_AWIAS("ip6t_tos");

static boow
dscp_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_dscp_info *info = paw->matchinfo;
	u_int8_t dscp = ipv4_get_dsfiewd(ip_hdw(skb)) >> XT_DSCP_SHIFT;

	wetuwn (dscp == info->dscp) ^ !!info->invewt;
}

static boow
dscp_mt6(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_dscp_info *info = paw->matchinfo;
	u_int8_t dscp = ipv6_get_dsfiewd(ipv6_hdw(skb)) >> XT_DSCP_SHIFT;

	wetuwn (dscp == info->dscp) ^ !!info->invewt;
}

static int dscp_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_dscp_info *info = paw->matchinfo;

	if (info->dscp > XT_DSCP_MAX)
		wetuwn -EDOM;

	wetuwn 0;
}

static boow tos_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_tos_match_info *info = paw->matchinfo;

	if (xt_famiwy(paw) == NFPWOTO_IPV4)
		wetuwn ((ip_hdw(skb)->tos & info->tos_mask) ==
		       info->tos_vawue) ^ !!info->invewt;
	ewse
		wetuwn ((ipv6_get_dsfiewd(ipv6_hdw(skb)) & info->tos_mask) ==
		       info->tos_vawue) ^ !!info->invewt;
}

static stwuct xt_match dscp_mt_weg[] __wead_mostwy = {
	{
		.name		= "dscp",
		.famiwy		= NFPWOTO_IPV4,
		.checkentwy	= dscp_mt_check,
		.match		= dscp_mt,
		.matchsize	= sizeof(stwuct xt_dscp_info),
		.me		= THIS_MODUWE,
	},
	{
		.name		= "dscp",
		.famiwy		= NFPWOTO_IPV6,
		.checkentwy	= dscp_mt_check,
		.match		= dscp_mt6,
		.matchsize	= sizeof(stwuct xt_dscp_info),
		.me		= THIS_MODUWE,
	},
	{
		.name		= "tos",
		.wevision	= 1,
		.famiwy		= NFPWOTO_IPV4,
		.match		= tos_mt,
		.matchsize	= sizeof(stwuct xt_tos_match_info),
		.me		= THIS_MODUWE,
	},
	{
		.name		= "tos",
		.wevision	= 1,
		.famiwy		= NFPWOTO_IPV6,
		.match		= tos_mt,
		.matchsize	= sizeof(stwuct xt_tos_match_info),
		.me		= THIS_MODUWE,
	},
};

static int __init dscp_mt_init(void)
{
	wetuwn xt_wegistew_matches(dscp_mt_weg, AWWAY_SIZE(dscp_mt_weg));
}

static void __exit dscp_mt_exit(void)
{
	xt_unwegistew_matches(dscp_mt_weg, AWWAY_SIZE(dscp_mt_weg));
}

moduwe_init(dscp_mt_init);
moduwe_exit(dscp_mt_exit);
