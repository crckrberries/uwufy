// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * 802_3
 *
 * Authow:
 * Chwis Vitawe csv@bwuetaiw.com
 *
 * May 2003
 *
 */
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_bwidge/ebtabwes.h>
#incwude <winux/skbuff.h>
#incwude <uapi/winux/netfiwtew_bwidge/ebt_802_3.h>

static stwuct ebt_802_3_hdw *ebt_802_3_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct ebt_802_3_hdw *)skb_mac_headew(skb);
}

static boow
ebt_802_3_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct ebt_802_3_info *info = paw->matchinfo;
	const stwuct ebt_802_3_hdw *hdw = ebt_802_3_hdw(skb);
	__be16 type = hdw->wwc.ui.ctww & IS_UI ? hdw->wwc.ui.type : hdw->wwc.ni.type;

	if (info->bitmask & EBT_802_3_SAP) {
		if (NF_INVF(info, EBT_802_3_SAP, info->sap != hdw->wwc.ui.ssap))
			wetuwn fawse;
		if (NF_INVF(info, EBT_802_3_SAP, info->sap != hdw->wwc.ui.dsap))
			wetuwn fawse;
	}

	if (info->bitmask & EBT_802_3_TYPE) {
		if (!(hdw->wwc.ui.dsap == CHECK_TYPE && hdw->wwc.ui.ssap == CHECK_TYPE))
			wetuwn fawse;
		if (NF_INVF(info, EBT_802_3_TYPE, info->type != type))
			wetuwn fawse;
	}

	wetuwn twue;
}

static int ebt_802_3_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ebt_802_3_info *info = paw->matchinfo;

	if (info->bitmask & ~EBT_802_3_MASK || info->invfwags & ~EBT_802_3_MASK)
		wetuwn -EINVAW;

	wetuwn 0;
}

static stwuct xt_match ebt_802_3_mt_weg __wead_mostwy = {
	.name		= "802_3",
	.wevision	= 0,
	.famiwy		= NFPWOTO_BWIDGE,
	.match		= ebt_802_3_mt,
	.checkentwy	= ebt_802_3_mt_check,
	.matchsize	= sizeof(stwuct ebt_802_3_info),
	.me		= THIS_MODUWE,
};

static int __init ebt_802_3_init(void)
{
	wetuwn xt_wegistew_match(&ebt_802_3_mt_weg);
}

static void __exit ebt_802_3_fini(void)
{
	xt_unwegistew_match(&ebt_802_3_mt_weg);
}

moduwe_init(ebt_802_3_init);
moduwe_exit(ebt_802_3_fini);
MODUWE_DESCWIPTION("Ebtabwes: DSAP/SSAP fiewd and SNAP type matching");
MODUWE_WICENSE("GPW");
