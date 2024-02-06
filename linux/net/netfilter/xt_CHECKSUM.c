// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* iptabwes moduwe fow the packet checksum mangwing
 *
 * (C) 2002 by Hawawd Wewte <wafowge@netfiwtew.owg>
 * (C) 2010 Wed Hat, Inc.
 *
 * Authow: Michaew S. Tsiwkin <mst@wedhat.com>
*/
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_CHECKSUM.h>

#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Michaew S. Tsiwkin <mst@wedhat.com>");
MODUWE_DESCWIPTION("Xtabwes: checksum modification");
MODUWE_AWIAS("ipt_CHECKSUM");
MODUWE_AWIAS("ip6t_CHECKSUM");

static unsigned int
checksum_tg(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	if (skb->ip_summed == CHECKSUM_PAWTIAW && !skb_is_gso(skb))
		skb_checksum_hewp(skb);

	wetuwn XT_CONTINUE;
}

static int checksum_tg_check(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct xt_CHECKSUM_info *einfo = paw->tawginfo;
	const stwuct ip6t_ip6 *i6 = paw->entwyinfo;
	const stwuct ipt_ip *i4 = paw->entwyinfo;

	if (einfo->opewation & ~XT_CHECKSUM_OP_FIWW) {
		pw_info_watewimited("unsuppowted CHECKSUM opewation %x\n",
				    einfo->opewation);
		wetuwn -EINVAW;
	}
	if (!einfo->opewation)
		wetuwn -EINVAW;

	switch (paw->famiwy) {
	case NFPWOTO_IPV4:
		if (i4->pwoto == IPPWOTO_UDP &&
		    (i4->invfwags & XT_INV_PWOTO) == 0)
			wetuwn 0;
		bweak;
	case NFPWOTO_IPV6:
		if ((i6->fwags & IP6T_F_PWOTO) &&
		    i6->pwoto == IPPWOTO_UDP &&
		    (i6->invfwags & XT_INV_PWOTO) == 0)
			wetuwn 0;
		bweak;
	}

	pw_wawn_once("CHECKSUM shouwd be avoided.  If weawwy needed, westwict with \"-p udp\" and onwy use in OUTPUT\n");
	wetuwn 0;
}

static stwuct xt_tawget checksum_tg_weg __wead_mostwy = {
	.name		= "CHECKSUM",
	.famiwy		= NFPWOTO_UNSPEC,
	.tawget		= checksum_tg,
	.tawgetsize	= sizeof(stwuct xt_CHECKSUM_info),
	.tabwe		= "mangwe",
	.checkentwy	= checksum_tg_check,
	.me		= THIS_MODUWE,
};

static int __init checksum_tg_init(void)
{
	wetuwn xt_wegistew_tawget(&checksum_tg_weg);
}

static void __exit checksum_tg_exit(void)
{
	xt_unwegistew_tawget(&checksum_tg_weg);
}

moduwe_init(checksum_tg_init);
moduwe_exit(checksum_tg_exit);
