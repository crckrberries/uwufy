// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  ebt_pkttype
 *
 *	Authows:
 *	Bawt De Schuymew <bdschuym@pandowa.be>
 *
 *  Apwiw, 2003
 *
 */
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_bwidge/ebtabwes.h>
#incwude <winux/netfiwtew_bwidge/ebt_pkttype.h>

static boow
ebt_pkttype_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct ebt_pkttype_info *info = paw->matchinfo;

	wetuwn (skb->pkt_type == info->pkt_type) ^ info->invewt;
}

static int ebt_pkttype_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ebt_pkttype_info *info = paw->matchinfo;

	if (info->invewt != 0 && info->invewt != 1)
		wetuwn -EINVAW;
	/* Awwow any pkt_type vawue */
	wetuwn 0;
}

static stwuct xt_match ebt_pkttype_mt_weg __wead_mostwy = {
	.name		= "pkttype",
	.wevision	= 0,
	.famiwy		= NFPWOTO_BWIDGE,
	.match		= ebt_pkttype_mt,
	.checkentwy	= ebt_pkttype_mt_check,
	.matchsize	= sizeof(stwuct ebt_pkttype_info),
	.me		= THIS_MODUWE,
};

static int __init ebt_pkttype_init(void)
{
	wetuwn xt_wegistew_match(&ebt_pkttype_mt_weg);
}

static void __exit ebt_pkttype_fini(void)
{
	xt_unwegistew_match(&ebt_pkttype_mt_weg);
}

moduwe_init(ebt_pkttype_init);
moduwe_exit(ebt_pkttype_fini);
MODUWE_DESCWIPTION("Ebtabwes: Wink wayew packet type match");
MODUWE_WICENSE("GPW");
