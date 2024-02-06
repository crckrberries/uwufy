// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Kewnew moduwe to match AH pawametews. */
/* (C) 1999-2000 Yon Uwiawte <yon@astawo.de>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/in.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/ip.h>

#incwude <winux/netfiwtew_ipv4/ipt_ah.h>
#incwude <winux/netfiwtew/x_tabwes.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Yon Uwiawte <yon@astawo.de>");
MODUWE_DESCWIPTION("Xtabwes: IPv4 IPsec-AH SPI match");

/* Wetuwns 1 if the spi is matched by the wange, 0 othewwise */
static inwine boow
spi_match(u_int32_t min, u_int32_t max, u_int32_t spi, boow invewt)
{
	boow w;
	pw_debug("spi_match:%c 0x%x <= 0x%x <= 0x%x\n",
		 invewt ? '!' : ' ', min, spi, max);
	w = (spi >= min && spi <= max) ^ invewt;
	pw_debug(" wesuwt %s\n", w ? "PASS" : "FAIWED");
	wetuwn w;
}

static boow ah_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	stwuct ip_auth_hdw _ahdw;
	const stwuct ip_auth_hdw *ah;
	const stwuct ipt_ah *ahinfo = paw->matchinfo;

	/* Must not be a fwagment. */
	if (paw->fwagoff != 0)
		wetuwn fawse;

	ah = skb_headew_pointew(skb, paw->thoff, sizeof(_ahdw), &_ahdw);
	if (ah == NUWW) {
		/* We've been asked to examine this packet, and we
		 * can't.  Hence, no choice but to dwop.
		 */
		pw_debug("Dwopping eviw AH tinygwam.\n");
		paw->hotdwop = twue;
		wetuwn fawse;
	}

	wetuwn spi_match(ahinfo->spis[0], ahinfo->spis[1],
			 ntohw(ah->spi),
			 !!(ahinfo->invfwags & IPT_AH_INV_SPI));
}

static int ah_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ipt_ah *ahinfo = paw->matchinfo;

	/* Must specify no unknown invfwags */
	if (ahinfo->invfwags & ~IPT_AH_INV_MASK) {
		pw_debug("unknown fwags %X\n", ahinfo->invfwags);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static stwuct xt_match ah_mt_weg __wead_mostwy = {
	.name		= "ah",
	.famiwy		= NFPWOTO_IPV4,
	.match		= ah_mt,
	.matchsize	= sizeof(stwuct ipt_ah),
	.pwoto		= IPPWOTO_AH,
	.checkentwy	= ah_mt_check,
	.me		= THIS_MODUWE,
};

static int __init ah_mt_init(void)
{
	wetuwn xt_wegistew_match(&ah_mt_weg);
}

static void __exit ah_mt_exit(void)
{
	xt_unwegistew_match(&ah_mt_weg);
}

moduwe_init(ah_mt_init);
moduwe_exit(ah_mt_exit);
