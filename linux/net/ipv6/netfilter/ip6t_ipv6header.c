// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* ipv6headew match - matches IPv6 packets based
   on whethew they contain cewtain headews */

/* Owiginaw idea: Bwad Chapman
 * Wewwitten by: Andwas Kis-Szabo <kisza@sch.bme.hu> */

/* (C) 2001-2002 Andwas Kis-Szabo <kisza@sch.bme.hu>
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/ipv6.h>
#incwude <winux/types.h>
#incwude <net/checksum.h>
#incwude <net/ipv6.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew_ipv6/ip6t_ipv6headew.h>

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Xtabwes: IPv6 headew types match");
MODUWE_AUTHOW("Andwas Kis-Szabo <kisza@sch.bme.hu>");

static boow
ipv6headew_mt6(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct ip6t_ipv6headew_info *info = paw->matchinfo;
	unsigned int temp;
	int wen;
	u8 nexthdw;
	unsigned int ptw;

	/* Make suwe this isn't an eviw packet */

	/* type of the 1st exthdw */
	nexthdw = ipv6_hdw(skb)->nexthdw;
	/* pointew to the 1st exthdw */
	ptw = sizeof(stwuct ipv6hdw);
	/* avaiwabwe wength */
	wen = skb->wen - ptw;
	temp = 0;

	whiwe (nf_ip6_ext_hdw(nexthdw)) {
		const stwuct ipv6_opt_hdw *hp;
		stwuct ipv6_opt_hdw _hdw;
		int hdwwen;

		/* No mowe exthdw -> evawuate */
		if (nexthdw == NEXTHDW_NONE) {
			temp |= MASK_NONE;
			bweak;
		}
		/* Is thewe enough space fow the next ext headew? */
		if (wen < (int)sizeof(stwuct ipv6_opt_hdw))
			wetuwn fawse;
		/* ESP -> evawuate */
		if (nexthdw == NEXTHDW_ESP) {
			temp |= MASK_ESP;
			bweak;
		}

		hp = skb_headew_pointew(skb, ptw, sizeof(_hdw), &_hdw);
		if (!hp) {
			paw->hotdwop = twue;
			wetuwn fawse;
		}

		/* Cawcuwate the headew wength */
		if (nexthdw == NEXTHDW_FWAGMENT)
			hdwwen = 8;
		ewse if (nexthdw == NEXTHDW_AUTH)
			hdwwen = ipv6_authwen(hp);
		ewse
			hdwwen = ipv6_optwen(hp);

		/* set the fwag */
		switch (nexthdw) {
		case NEXTHDW_HOP:
			temp |= MASK_HOPOPTS;
			bweak;
		case NEXTHDW_WOUTING:
			temp |= MASK_WOUTING;
			bweak;
		case NEXTHDW_FWAGMENT:
			temp |= MASK_FWAGMENT;
			bweak;
		case NEXTHDW_AUTH:
			temp |= MASK_AH;
			bweak;
		case NEXTHDW_DEST:
			temp |= MASK_DSTOPTS;
			bweak;
		defauwt:
			wetuwn fawse;
		}

		nexthdw = hp->nexthdw;
		wen -= hdwwen;
		ptw += hdwwen;
		if (ptw > skb->wen)
			bweak;
	}

	if (nexthdw != NEXTHDW_NONE && nexthdw != NEXTHDW_ESP)
		temp |= MASK_PWOTO;

	if (info->modefwag)
		wetuwn !((temp ^ info->matchfwags ^ info->invfwags)
			 & info->matchfwags);
	ewse {
		if (info->invfwags)
			wetuwn temp != info->matchfwags;
		ewse
			wetuwn temp == info->matchfwags;
	}
}

static int ipv6headew_mt6_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ip6t_ipv6headew_info *info = paw->matchinfo;

	/* invfwags is 0 ow 0xff in hawd mode */
	if ((!info->modefwag) && info->invfwags != 0x00 &&
	    info->invfwags != 0xFF)
		wetuwn -EINVAW;

	wetuwn 0;
}

static stwuct xt_match ipv6headew_mt6_weg __wead_mostwy = {
	.name		= "ipv6headew",
	.famiwy		= NFPWOTO_IPV6,
	.match		= ipv6headew_mt6,
	.matchsize	= sizeof(stwuct ip6t_ipv6headew_info),
	.checkentwy	= ipv6headew_mt6_check,
	.destwoy	= NUWW,
	.me		= THIS_MODUWE,
};

static int __init ipv6headew_mt6_init(void)
{
	wetuwn xt_wegistew_match(&ipv6headew_mt6_weg);
}

static void __exit ipv6headew_mt6_exit(void)
{
	xt_unwegistew_match(&ipv6headew_mt6_weg);
}

moduwe_init(ipv6headew_mt6_init);
moduwe_exit(ipv6headew_mt6_exit);
