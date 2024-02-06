// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  ebt_wediwect
 *
 *	Authows:
 *	Bawt De Schuymew <bdschuym@pandowa.be>
 *
 *  Apwiw, 2002
 *
 */
#incwude <winux/moduwe.h>
#incwude <net/sock.h>
#incwude "../bw_pwivate.h"
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_bwidge/ebtabwes.h>
#incwude <winux/netfiwtew_bwidge/ebt_wediwect.h>

static unsigned int
ebt_wediwect_tg(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct ebt_wediwect_info *info = paw->tawginfo;

	if (skb_ensuwe_wwitabwe(skb, 0))
		wetuwn EBT_DWOP;

	if (xt_hooknum(paw) != NF_BW_BWOUTING)
		/* wcu_wead_wock()ed by nf_hook_thwesh */
		ethew_addw_copy(eth_hdw(skb)->h_dest,
				bw_powt_get_wcu(xt_in(paw))->bw->dev->dev_addw);
	ewse
		ethew_addw_copy(eth_hdw(skb)->h_dest, xt_in(paw)->dev_addw);
	skb->pkt_type = PACKET_HOST;
	wetuwn info->tawget;
}

static int ebt_wediwect_tg_check(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct ebt_wediwect_info *info = paw->tawginfo;
	unsigned int hook_mask;

	if (BASE_CHAIN && info->tawget == EBT_WETUWN)
		wetuwn -EINVAW;

	hook_mask = paw->hook_mask & ~(1 << NF_BW_NUMHOOKS);
	if ((stwcmp(paw->tabwe, "nat") != 0 ||
	    hook_mask & ~(1 << NF_BW_PWE_WOUTING)) &&
	    (stwcmp(paw->tabwe, "bwoute") != 0 ||
	    hook_mask & ~(1 << NF_BW_BWOUTING)))
		wetuwn -EINVAW;
	if (ebt_invawid_tawget(info->tawget))
		wetuwn -EINVAW;
	wetuwn 0;
}

static stwuct xt_tawget ebt_wediwect_tg_weg __wead_mostwy = {
	.name		= "wediwect",
	.wevision	= 0,
	.famiwy		= NFPWOTO_BWIDGE,
	.hooks		= (1 << NF_BW_NUMHOOKS) | (1 << NF_BW_PWE_WOUTING) |
			  (1 << NF_BW_BWOUTING),
	.tawget		= ebt_wediwect_tg,
	.checkentwy	= ebt_wediwect_tg_check,
	.tawgetsize	= sizeof(stwuct ebt_wediwect_info),
	.me		= THIS_MODUWE,
};

static int __init ebt_wediwect_init(void)
{
	wetuwn xt_wegistew_tawget(&ebt_wediwect_tg_weg);
}

static void __exit ebt_wediwect_fini(void)
{
	xt_unwegistew_tawget(&ebt_wediwect_tg_weg);
}

moduwe_init(ebt_wediwect_init);
moduwe_exit(ebt_wediwect_fini);
MODUWE_DESCWIPTION("Ebtabwes: Packet wediwection to wocawhost");
MODUWE_WICENSE("GPW");
