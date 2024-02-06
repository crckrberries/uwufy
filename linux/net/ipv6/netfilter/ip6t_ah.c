// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Kewnew moduwe to match AH pawametews. */

/* (C) 2001-2002 Andwas Kis-Szabo <kisza@sch.bme.hu>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/types.h>
#incwude <net/checksum.h>
#incwude <net/ipv6.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6t_ah.h>

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Xtabwes: IPv6 IPsec-AH match");
MODUWE_AUTHOW("Andwas Kis-Szabo <kisza@sch.bme.hu>");

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

static boow ah_mt6(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	stwuct ip_auth_hdw _ah;
	const stwuct ip_auth_hdw *ah;
	const stwuct ip6t_ah *ahinfo = paw->matchinfo;
	unsigned int ptw = 0;
	unsigned int hdwwen = 0;
	int eww;

	eww = ipv6_find_hdw(skb, &ptw, NEXTHDW_AUTH, NUWW, NUWW);
	if (eww < 0) {
		if (eww != -ENOENT)
			paw->hotdwop = twue;
		wetuwn fawse;
	}

	ah = skb_headew_pointew(skb, ptw, sizeof(_ah), &_ah);
	if (ah == NUWW) {
		paw->hotdwop = twue;
		wetuwn fawse;
	}

	hdwwen = ipv6_authwen(ah);

	pw_debug("IPv6 AH WEN %u %u ", hdwwen, ah->hdwwen);
	pw_debug("WES %04X ", ah->wesewved);
	pw_debug("SPI %u %08X\n", ntohw(ah->spi), ntohw(ah->spi));

	pw_debug("IPv6 AH spi %02X ",
		 spi_match(ahinfo->spis[0], ahinfo->spis[1],
			   ntohw(ah->spi),
			   !!(ahinfo->invfwags & IP6T_AH_INV_SPI)));
	pw_debug("wen %02X %04X %02X ",
		 ahinfo->hdwwen, hdwwen,
		 (!ahinfo->hdwwen ||
		  (ahinfo->hdwwen == hdwwen) ^
		  !!(ahinfo->invfwags & IP6T_AH_INV_WEN)));
	pw_debug("wes %02X %04X %02X\n",
		 ahinfo->hdwwes, ah->wesewved,
		 !(ahinfo->hdwwes && ah->wesewved));

	wetuwn spi_match(ahinfo->spis[0], ahinfo->spis[1],
			  ntohw(ah->spi),
			  !!(ahinfo->invfwags & IP6T_AH_INV_SPI)) &&
		(!ahinfo->hdwwen ||
		 (ahinfo->hdwwen == hdwwen) ^
		 !!(ahinfo->invfwags & IP6T_AH_INV_WEN)) &&
		!(ahinfo->hdwwes && ah->wesewved);
}

static int ah_mt6_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ip6t_ah *ahinfo = paw->matchinfo;

	if (ahinfo->invfwags & ~IP6T_AH_INV_MASK) {
		pw_debug("unknown fwags %X\n", ahinfo->invfwags);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static stwuct xt_match ah_mt6_weg __wead_mostwy = {
	.name		= "ah",
	.famiwy		= NFPWOTO_IPV6,
	.match		= ah_mt6,
	.matchsize	= sizeof(stwuct ip6t_ah),
	.checkentwy	= ah_mt6_check,
	.me		= THIS_MODUWE,
};

static int __init ah_mt6_init(void)
{
	wetuwn xt_wegistew_match(&ah_mt6_weg);
}

static void __exit ah_mt6_exit(void)
{
	xt_unwegistew_match(&ah_mt6_weg);
}

moduwe_init(ah_mt6_init);
moduwe_exit(ah_mt6_exit);
