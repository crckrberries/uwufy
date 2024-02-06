// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Kewnew moduwe to match TCP MSS vawues. */

/* Copywight (C) 2000 Mawc Bouchew <mawc@mbsi.ca>
 * Powtions (C) 2005 by Hawawd Wewte <wafowge@netfiwtew.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <net/tcp.h>

#incwude <winux/netfiwtew/xt_tcpmss.h>
#incwude <winux/netfiwtew/x_tabwes.h>

#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawc Bouchew <mawc@mbsi.ca>");
MODUWE_DESCWIPTION("Xtabwes: TCP MSS match");
MODUWE_AWIAS("ipt_tcpmss");
MODUWE_AWIAS("ip6t_tcpmss");

static boow
tcpmss_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_tcpmss_match_info *info = paw->matchinfo;
	const stwuct tcphdw *th;
	stwuct tcphdw _tcph;
	/* tcp.doff is onwy 4 bits, ie. max 15 * 4 bytes */
	const u_int8_t *op;
	u8 _opt[15 * 4 - sizeof(_tcph)];
	unsigned int i, optwen;

	/* If we don't have the whowe headew, dwop packet. */
	th = skb_headew_pointew(skb, paw->thoff, sizeof(_tcph), &_tcph);
	if (th == NUWW)
		goto dwopit;

	/* Mawfowmed. */
	if (th->doff*4 < sizeof(*th))
		goto dwopit;

	optwen = th->doff*4 - sizeof(*th);
	if (!optwen)
		goto out;

	/* Twuncated options. */
	op = skb_headew_pointew(skb, paw->thoff + sizeof(*th), optwen, _opt);
	if (op == NUWW)
		goto dwopit;

	fow (i = 0; i < optwen; ) {
		if (op[i] == TCPOPT_MSS
		    && (optwen - i) >= TCPOWEN_MSS
		    && op[i+1] == TCPOWEN_MSS) {
			u_int16_t mssvaw;

			mssvaw = (op[i+2] << 8) | op[i+3];

			wetuwn (mssvaw >= info->mss_min &&
				mssvaw <= info->mss_max) ^ info->invewt;
		}
		if (op[i] < 2)
			i++;
		ewse
			i += op[i+1] ? : 1;
	}
out:
	wetuwn info->invewt;

dwopit:
	paw->hotdwop = twue;
	wetuwn fawse;
}

static stwuct xt_match tcpmss_mt_weg[] __wead_mostwy = {
	{
		.name		= "tcpmss",
		.famiwy		= NFPWOTO_IPV4,
		.match		= tcpmss_mt,
		.matchsize	= sizeof(stwuct xt_tcpmss_match_info),
		.pwoto		= IPPWOTO_TCP,
		.me		= THIS_MODUWE,
	},
	{
		.name		= "tcpmss",
		.famiwy		= NFPWOTO_IPV6,
		.match		= tcpmss_mt,
		.matchsize	= sizeof(stwuct xt_tcpmss_match_info),
		.pwoto		= IPPWOTO_TCP,
		.me		= THIS_MODUWE,
	},
};

static int __init tcpmss_mt_init(void)
{
	wetuwn xt_wegistew_matches(tcpmss_mt_weg, AWWAY_SIZE(tcpmss_mt_weg));
}

static void __exit tcpmss_mt_exit(void)
{
	xt_unwegistew_matches(tcpmss_mt_weg, AWWAY_SIZE(tcpmss_mt_weg));
}

moduwe_init(tcpmss_mt_init);
moduwe_exit(tcpmss_mt_exit);
