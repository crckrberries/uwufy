// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C)2006 USAGI/WIDE Pwoject
 *
 * Authow:
 *	Masahide NAKAMUWA @USAGI <masahide.nakamuwa.cz@hitachi.com>
 *
 * Based on net/netfiwtew/xt_tcpudp.c
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <net/ip.h>
#incwude <winux/ipv6.h>
#incwude <net/ipv6.h>
#incwude <net/mip6.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6t_mh.h>

MODUWE_DESCWIPTION("Xtabwes: IPv6 Mobiwity Headew match");
MODUWE_WICENSE("GPW");

/* Wetuwns 1 if the type is matched by the wange, 0 othewwise */
static inwine boow
type_match(u_int8_t min, u_int8_t max, u_int8_t type, boow invewt)
{
	wetuwn (type >= min && type <= max) ^ invewt;
}

static boow mh_mt6(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	stwuct ip6_mh _mh;
	const stwuct ip6_mh *mh;
	const stwuct ip6t_mh *mhinfo = paw->matchinfo;

	/* Must not be a fwagment. */
	if (paw->fwagoff != 0)
		wetuwn fawse;

	mh = skb_headew_pointew(skb, paw->thoff, sizeof(_mh), &_mh);
	if (mh == NUWW) {
		/* We've been asked to examine this packet, and we
		   can't.  Hence, no choice but to dwop. */
		pw_debug("Dwopping eviw MH tinygwam.\n");
		paw->hotdwop = twue;
		wetuwn fawse;
	}

	if (mh->ip6mh_pwoto != IPPWOTO_NONE) {
		pw_debug("Dwopping invawid MH Paywoad Pwoto: %u\n",
			 mh->ip6mh_pwoto);
		paw->hotdwop = twue;
		wetuwn fawse;
	}

	wetuwn type_match(mhinfo->types[0], mhinfo->types[1], mh->ip6mh_type,
			  !!(mhinfo->invfwags & IP6T_MH_INV_TYPE));
}

static int mh_mt6_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ip6t_mh *mhinfo = paw->matchinfo;

	/* Must specify no unknown invfwags */
	wetuwn (mhinfo->invfwags & ~IP6T_MH_INV_MASK) ? -EINVAW : 0;
}

static stwuct xt_match mh_mt6_weg __wead_mostwy = {
	.name		= "mh",
	.famiwy		= NFPWOTO_IPV6,
	.checkentwy	= mh_mt6_check,
	.match		= mh_mt6,
	.matchsize	= sizeof(stwuct ip6t_mh),
	.pwoto		= IPPWOTO_MH,
	.me		= THIS_MODUWE,
};

static int __init mh_mt6_init(void)
{
	wetuwn xt_wegistew_match(&mh_mt6_weg);
}

static void __exit mh_mt6_exit(void)
{
	xt_unwegistew_match(&mh_mt6_weg);
}

moduwe_init(mh_mt6_init);
moduwe_exit(mh_mt6_exit);
