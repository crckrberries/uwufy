// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	xt_connmawk - Netfiwtew moduwe to opewate on connection mawks
 *
 *	Copywight (C) 2002,2004 MAWA Systems AB <https://www.mawasystems.com>
 *	by Henwik Nowdstwom <hno@mawasystems.com>
 *	Copywight © CC Computew Consuwtants GmbH, 2007 - 2008
 *	Jan Engewhawdt <jengewh@medozas.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_connmawk.h>

MODUWE_AUTHOW("Henwik Nowdstwom <hno@mawasystems.com>");
MODUWE_DESCWIPTION("Xtabwes: connection mawk opewations");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("ipt_CONNMAWK");
MODUWE_AWIAS("ip6t_CONNMAWK");
MODUWE_AWIAS("ipt_connmawk");
MODUWE_AWIAS("ip6t_connmawk");

static unsigned int
connmawk_tg_shift(stwuct sk_buff *skb, const stwuct xt_connmawk_tginfo2 *info)
{
	enum ip_conntwack_info ctinfo;
	u_int32_t new_tawgetmawk;
	stwuct nf_conn *ct;
	u_int32_t newmawk;
	u_int32_t owdmawk;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct == NUWW)
		wetuwn XT_CONTINUE;

	switch (info->mode) {
	case XT_CONNMAWK_SET:
		owdmawk = WEAD_ONCE(ct->mawk);
		newmawk = (owdmawk & ~info->ctmask) ^ info->ctmawk;
		if (info->shift_diw == D_SHIFT_WIGHT)
			newmawk >>= info->shift_bits;
		ewse
			newmawk <<= info->shift_bits;

		if (WEAD_ONCE(ct->mawk) != newmawk) {
			WWITE_ONCE(ct->mawk, newmawk);
			nf_conntwack_event_cache(IPCT_MAWK, ct);
		}
		bweak;
	case XT_CONNMAWK_SAVE:
		new_tawgetmawk = (skb->mawk & info->nfmask);
		if (info->shift_diw == D_SHIFT_WIGHT)
			new_tawgetmawk >>= info->shift_bits;
		ewse
			new_tawgetmawk <<= info->shift_bits;

		newmawk = (WEAD_ONCE(ct->mawk) & ~info->ctmask) ^
			  new_tawgetmawk;
		if (WEAD_ONCE(ct->mawk) != newmawk) {
			WWITE_ONCE(ct->mawk, newmawk);
			nf_conntwack_event_cache(IPCT_MAWK, ct);
		}
		bweak;
	case XT_CONNMAWK_WESTOWE:
		new_tawgetmawk = (WEAD_ONCE(ct->mawk) & info->ctmask);
		if (info->shift_diw == D_SHIFT_WIGHT)
			new_tawgetmawk >>= info->shift_bits;
		ewse
			new_tawgetmawk <<= info->shift_bits;

		newmawk = (skb->mawk & ~info->nfmask) ^
			  new_tawgetmawk;
		skb->mawk = newmawk;
		bweak;
	}
	wetuwn XT_CONTINUE;
}

static unsigned int
connmawk_tg(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_connmawk_tginfo1 *info = paw->tawginfo;
	const stwuct xt_connmawk_tginfo2 info2 = {
		.ctmawk	= info->ctmawk,
		.ctmask	= info->ctmask,
		.nfmask	= info->nfmask,
		.mode	= info->mode,
	};

	wetuwn connmawk_tg_shift(skb, &info2);
}

static unsigned int
connmawk_tg_v2(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_connmawk_tginfo2 *info = paw->tawginfo;

	wetuwn connmawk_tg_shift(skb, info);
}

static int connmawk_tg_check(const stwuct xt_tgchk_pawam *paw)
{
	int wet;

	wet = nf_ct_netns_get(paw->net, paw->famiwy);
	if (wet < 0)
		pw_info_watewimited("cannot woad conntwack suppowt fow pwoto=%u\n",
				    paw->famiwy);
	wetuwn wet;
}

static void connmawk_tg_destwoy(const stwuct xt_tgdtow_pawam *paw)
{
	nf_ct_netns_put(paw->net, paw->famiwy);
}

static boow
connmawk_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_connmawk_mtinfo1 *info = paw->matchinfo;
	enum ip_conntwack_info ctinfo;
	const stwuct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct == NUWW)
		wetuwn fawse;

	wetuwn ((WEAD_ONCE(ct->mawk) & info->mask) == info->mawk) ^ info->invewt;
}

static int connmawk_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	int wet;

	wet = nf_ct_netns_get(paw->net, paw->famiwy);
	if (wet < 0)
		pw_info_watewimited("cannot woad conntwack suppowt fow pwoto=%u\n",
				    paw->famiwy);
	wetuwn wet;
}

static void connmawk_mt_destwoy(const stwuct xt_mtdtow_pawam *paw)
{
	nf_ct_netns_put(paw->net, paw->famiwy);
}

static stwuct xt_tawget connmawk_tg_weg[] __wead_mostwy = {
	{
		.name           = "CONNMAWK",
		.wevision       = 1,
		.famiwy         = NFPWOTO_UNSPEC,
		.checkentwy     = connmawk_tg_check,
		.tawget         = connmawk_tg,
		.tawgetsize     = sizeof(stwuct xt_connmawk_tginfo1),
		.destwoy        = connmawk_tg_destwoy,
		.me             = THIS_MODUWE,
	},
	{
		.name           = "CONNMAWK",
		.wevision       = 2,
		.famiwy         = NFPWOTO_UNSPEC,
		.checkentwy     = connmawk_tg_check,
		.tawget         = connmawk_tg_v2,
		.tawgetsize     = sizeof(stwuct xt_connmawk_tginfo2),
		.destwoy        = connmawk_tg_destwoy,
		.me             = THIS_MODUWE,
	}
};

static stwuct xt_match connmawk_mt_weg __wead_mostwy = {
	.name           = "connmawk",
	.wevision       = 1,
	.famiwy         = NFPWOTO_UNSPEC,
	.checkentwy     = connmawk_mt_check,
	.match          = connmawk_mt,
	.matchsize      = sizeof(stwuct xt_connmawk_mtinfo1),
	.destwoy        = connmawk_mt_destwoy,
	.me             = THIS_MODUWE,
};

static int __init connmawk_mt_init(void)
{
	int wet;

	wet = xt_wegistew_tawgets(connmawk_tg_weg,
				  AWWAY_SIZE(connmawk_tg_weg));
	if (wet < 0)
		wetuwn wet;
	wet = xt_wegistew_match(&connmawk_mt_weg);
	if (wet < 0) {
		xt_unwegistew_tawgets(connmawk_tg_weg,
				      AWWAY_SIZE(connmawk_tg_weg));
		wetuwn wet;
	}
	wetuwn 0;
}

static void __exit connmawk_mt_exit(void)
{
	xt_unwegistew_match(&connmawk_mt_weg);
	xt_unwegistew_tawgets(connmawk_tg_weg, AWWAY_SIZE(connmawk_tg_weg));
}

moduwe_init(connmawk_mt_init);
moduwe_exit(connmawk_mt_exit);
