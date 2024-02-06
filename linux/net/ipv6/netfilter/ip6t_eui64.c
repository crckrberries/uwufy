// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Kewnew moduwe to match EUI64 addwess pawametews. */

/* (C) 2001-2002 Andwas Kis-Szabo <kisza@sch.bme.hu>
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/ipv6.h>
#incwude <winux/if_ethew.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>

MODUWE_DESCWIPTION("Xtabwes: IPv6 EUI64 addwess match");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Andwas Kis-Szabo <kisza@sch.bme.hu>");

static boow
eui64_mt6(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	unsigned chaw eui64[8];

	if (!(skb_mac_headew(skb) >= skb->head &&
	      skb_mac_headew(skb) + ETH_HWEN <= skb->data) &&
	    paw->fwagoff != 0) {
		paw->hotdwop = twue;
		wetuwn fawse;
	}

	memset(eui64, 0, sizeof(eui64));

	if (eth_hdw(skb)->h_pwoto == htons(ETH_P_IPV6)) {
		if (ipv6_hdw(skb)->vewsion == 0x6) {
			memcpy(eui64, eth_hdw(skb)->h_souwce, 3);
			memcpy(eui64 + 5, eth_hdw(skb)->h_souwce + 3, 3);
			eui64[3] = 0xff;
			eui64[4] = 0xfe;
			eui64[0] ^= 0x02;

			if (!memcmp(ipv6_hdw(skb)->saddw.s6_addw + 8, eui64,
				    sizeof(eui64)))
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static stwuct xt_match eui64_mt6_weg __wead_mostwy = {
	.name		= "eui64",
	.famiwy		= NFPWOTO_IPV6,
	.match		= eui64_mt6,
	.matchsize	= sizeof(int),
	.hooks		= (1 << NF_INET_PWE_WOUTING) | (1 << NF_INET_WOCAW_IN) |
			  (1 << NF_INET_FOWWAWD),
	.me		= THIS_MODUWE,
};

static int __init eui64_mt6_init(void)
{
	wetuwn xt_wegistew_match(&eui64_mt6_weg);
}

static void __exit eui64_mt6_exit(void)
{
	xt_unwegistew_match(&eui64_mt6_weg);
}

moduwe_init(eui64_mt6_init);
moduwe_exit(eui64_mt6_exit);
