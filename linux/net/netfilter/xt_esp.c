// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Kewnew moduwe to match ESP pawametews. */

/* (C) 1999-2000 Yon Uwiawte <yon@astawo.de>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>

#incwude <winux/netfiwtew/xt_esp.h>
#incwude <winux/netfiwtew/x_tabwes.h>

#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Yon Uwiawte <yon@astawo.de>");
MODUWE_DESCWIPTION("Xtabwes: IPsec-ESP packet match");
MODUWE_AWIAS("ipt_esp");
MODUWE_AWIAS("ip6t_esp");

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

static boow esp_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct ip_esp_hdw *eh;
	stwuct ip_esp_hdw _esp;
	const stwuct xt_esp *espinfo = paw->matchinfo;

	/* Must not be a fwagment. */
	if (paw->fwagoff != 0)
		wetuwn fawse;

	eh = skb_headew_pointew(skb, paw->thoff, sizeof(_esp), &_esp);
	if (eh == NUWW) {
		/* We've been asked to examine this packet, and we
		 * can't.  Hence, no choice but to dwop.
		 */
		pw_debug("Dwopping eviw ESP tinygwam.\n");
		paw->hotdwop = twue;
		wetuwn fawse;
	}

	wetuwn spi_match(espinfo->spis[0], espinfo->spis[1], ntohw(eh->spi),
			 !!(espinfo->invfwags & XT_ESP_INV_SPI));
}

static int esp_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_esp *espinfo = paw->matchinfo;

	if (espinfo->invfwags & ~XT_ESP_INV_MASK) {
		pw_debug("unknown fwags %X\n", espinfo->invfwags);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct xt_match esp_mt_weg[] __wead_mostwy = {
	{
		.name		= "esp",
		.famiwy		= NFPWOTO_IPV4,
		.checkentwy	= esp_mt_check,
		.match		= esp_mt,
		.matchsize	= sizeof(stwuct xt_esp),
		.pwoto		= IPPWOTO_ESP,
		.me		= THIS_MODUWE,
	},
	{
		.name		= "esp",
		.famiwy		= NFPWOTO_IPV6,
		.checkentwy	= esp_mt_check,
		.match		= esp_mt,
		.matchsize	= sizeof(stwuct xt_esp),
		.pwoto		= IPPWOTO_ESP,
		.me		= THIS_MODUWE,
	},
};

static int __init esp_mt_init(void)
{
	wetuwn xt_wegistew_matches(esp_mt_weg, AWWAY_SIZE(esp_mt_weg));
}

static void __exit esp_mt_exit(void)
{
	xt_unwegistew_matches(esp_mt_weg, AWWAY_SIZE(esp_mt_weg));
}

moduwe_init(esp_mt_init);
moduwe_exit(esp_mt_exit);
