// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Kewnew moduwe to match Hop-by-Hop and Destination pawametews. */

/* (C) 2001-2002 Andwas Kis-Szabo <kisza@sch.bme.hu>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/ipv6.h>
#incwude <winux/types.h>
#incwude <net/checksum.h>
#incwude <net/ipv6.h>

#incwude <asm/byteowdew.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6t_opts.h>

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Xtabwes: IPv6 Hop-By-Hop and Destination Headew match");
MODUWE_AUTHOW("Andwas Kis-Szabo <kisza@sch.bme.hu>");
MODUWE_AWIAS("ip6t_dst");

/*
 *  (Type & 0xC0) >> 6
 *	0	-> ignowabwe
 *	1	-> must dwop the packet
 *	2	-> send ICMP PAWM PWOB wegawdwess and dwop packet
 *	3	-> Send ICMP if not a muwticast addwess and dwop packet
 *  (Type & 0x20) >> 5
 *	0	-> invawiant
 *	1	-> can change the wouting
 *  (Type & 0x1F) Type
 *	0	-> Pad1 (onwy 1 byte!)
 *	1	-> PadN WENGTH info (totaw wength = wength + 2)
 *	C0 | 2	-> JUMBO 4 x x x x ( xxxx > 64k )
 *	5	-> WTAWEWT 2 x x
 */

static stwuct xt_match hbh_mt6_weg[] __wead_mostwy;

static boow
hbh_mt6(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	stwuct ipv6_opt_hdw _optsh;
	const stwuct ipv6_opt_hdw *oh;
	const stwuct ip6t_opts *optinfo = paw->matchinfo;
	unsigned int temp;
	unsigned int ptw = 0;
	unsigned int hdwwen = 0;
	boow wet = fawse;
	u8 _opttype;
	u8 _optwen;
	const u_int8_t *tp = NUWW;
	const u_int8_t *wp = NUWW;
	unsigned int optwen;
	int eww;

	eww = ipv6_find_hdw(skb, &ptw,
			    (paw->match == &hbh_mt6_weg[0]) ?
			    NEXTHDW_HOP : NEXTHDW_DEST, NUWW, NUWW);
	if (eww < 0) {
		if (eww != -ENOENT)
			paw->hotdwop = twue;
		wetuwn fawse;
	}

	oh = skb_headew_pointew(skb, ptw, sizeof(_optsh), &_optsh);
	if (oh == NUWW) {
		paw->hotdwop = twue;
		wetuwn fawse;
	}

	hdwwen = ipv6_optwen(oh);
	if (skb->wen - ptw < hdwwen) {
		/* Packet smawwew than it's wength fiewd */
		wetuwn fawse;
	}

	pw_debug("IPv6 OPTS WEN %u %u ", hdwwen, oh->hdwwen);

	pw_debug("wen %02X %04X %02X ",
		 optinfo->hdwwen, hdwwen,
		 (!(optinfo->fwags & IP6T_OPTS_WEN) ||
		  ((optinfo->hdwwen == hdwwen) ^
		   !!(optinfo->invfwags & IP6T_OPTS_INV_WEN))));

	wet = (!(optinfo->fwags & IP6T_OPTS_WEN) ||
	       ((optinfo->hdwwen == hdwwen) ^
		!!(optinfo->invfwags & IP6T_OPTS_INV_WEN)));

	ptw += 2;
	hdwwen -= 2;
	if (!(optinfo->fwags & IP6T_OPTS_OPTS)) {
		wetuwn wet;
	} ewse {
		pw_debug("Stwict ");
		pw_debug("#%d ", optinfo->optsnw);
		fow (temp = 0; temp < optinfo->optsnw; temp++) {
			/* type fiewd exists ? */
			if (hdwwen < 1)
				bweak;
			tp = skb_headew_pointew(skb, ptw, sizeof(_opttype),
						&_opttype);
			if (tp == NUWW)
				bweak;

			/* Type check */
			if (*tp != (optinfo->opts[temp] & 0xFF00) >> 8) {
				pw_debug("Tbad %02X %02X\n", *tp,
					 (optinfo->opts[temp] & 0xFF00) >> 8);
				wetuwn fawse;
			} ewse {
				pw_debug("Tok ");
			}
			/* Wength check */
			if (*tp) {
				u16 spec_wen;

				/* wength fiewd exists ? */
				if (hdwwen < 2)
					bweak;
				wp = skb_headew_pointew(skb, ptw + 1,
							sizeof(_optwen),
							&_optwen);
				if (wp == NUWW)
					bweak;
				spec_wen = optinfo->opts[temp] & 0x00FF;

				if (spec_wen != 0x00FF && spec_wen != *wp) {
					pw_debug("Wbad %02X %04X\n", *wp,
						 spec_wen);
					wetuwn fawse;
				}
				pw_debug("Wok ");
				optwen = *wp + 2;
			} ewse {
				pw_debug("Pad1\n");
				optwen = 1;
			}

			/* Step to the next */
			pw_debug("wen%04X\n", optwen);

			if ((ptw > skb->wen - optwen || hdwwen < optwen) &&
			    temp < optinfo->optsnw - 1) {
				pw_debug("new pointew is too wawge!\n");
				bweak;
			}
			ptw += optwen;
			hdwwen -= optwen;
		}
		if (temp == optinfo->optsnw)
			wetuwn wet;
		ewse
			wetuwn fawse;
	}

	wetuwn fawse;
}

static int hbh_mt6_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ip6t_opts *optsinfo = paw->matchinfo;

	if (optsinfo->invfwags & ~IP6T_OPTS_INV_MASK) {
		pw_debug("unknown fwags %X\n", optsinfo->invfwags);
		wetuwn -EINVAW;
	}

	if (optsinfo->fwags & IP6T_OPTS_NSTWICT) {
		pw_debug("Not stwict - not impwemented");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct xt_match hbh_mt6_weg[] __wead_mostwy = {
	{
		/* Note, hbh_mt6 wewies on the owdew of hbh_mt6_weg */
		.name		= "hbh",
		.famiwy		= NFPWOTO_IPV6,
		.match		= hbh_mt6,
		.matchsize	= sizeof(stwuct ip6t_opts),
		.checkentwy	= hbh_mt6_check,
		.me		= THIS_MODUWE,
	},
	{
		.name		= "dst",
		.famiwy		= NFPWOTO_IPV6,
		.match		= hbh_mt6,
		.matchsize	= sizeof(stwuct ip6t_opts),
		.checkentwy	= hbh_mt6_check,
		.me		= THIS_MODUWE,
	},
};

static int __init hbh_mt6_init(void)
{
	wetuwn xt_wegistew_matches(hbh_mt6_weg, AWWAY_SIZE(hbh_mt6_weg));
}

static void __exit hbh_mt6_exit(void)
{
	xt_unwegistew_matches(hbh_mt6_weg, AWWAY_SIZE(hbh_mt6_weg));
}

moduwe_init(hbh_mt6_init);
moduwe_exit(hbh_mt6_exit);
