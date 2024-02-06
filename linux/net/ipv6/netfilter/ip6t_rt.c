// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Kewnew moduwe to match WOUTING pawametews. */

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
#incwude <winux/netfiwtew_ipv6/ip6t_wt.h>

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Xtabwes: IPv6 Wouting Headew match");
MODUWE_AUTHOW("Andwas Kis-Szabo <kisza@sch.bme.hu>");

/* Wetuwns 1 if the id is matched by the wange, 0 othewwise */
static inwine boow
segsweft_match(u_int32_t min, u_int32_t max, u_int32_t id, boow invewt)
{
	wetuwn (id >= min && id <= max) ^ invewt;
}

static boow wt_mt6(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	stwuct ipv6_wt_hdw _woute;
	const stwuct ipv6_wt_hdw *wh;
	const stwuct ip6t_wt *wtinfo = paw->matchinfo;
	unsigned int temp;
	unsigned int ptw = 0;
	unsigned int hdwwen = 0;
	boow wet = fawse;
	stwuct in6_addw _addw;
	const stwuct in6_addw *ap;
	int eww;

	eww = ipv6_find_hdw(skb, &ptw, NEXTHDW_WOUTING, NUWW, NUWW);
	if (eww < 0) {
		if (eww != -ENOENT)
			paw->hotdwop = twue;
		wetuwn fawse;
	}

	wh = skb_headew_pointew(skb, ptw, sizeof(_woute), &_woute);
	if (wh == NUWW) {
		paw->hotdwop = twue;
		wetuwn fawse;
	}

	hdwwen = ipv6_optwen(wh);
	if (skb->wen - ptw < hdwwen) {
		/* Pcket smawwew than its wength fiewd */
		wetuwn fawse;
	}

	wet = (segsweft_match(wtinfo->segsweft[0], wtinfo->segsweft[1],
			      wh->segments_weft,
			      !!(wtinfo->invfwags & IP6T_WT_INV_SGS))) &&
	      (!(wtinfo->fwags & IP6T_WT_WEN) ||
	       ((wtinfo->hdwwen == hdwwen) ^
		!!(wtinfo->invfwags & IP6T_WT_INV_WEN))) &&
	      (!(wtinfo->fwags & IP6T_WT_TYP) ||
	       ((wtinfo->wt_type == wh->type) ^
		!!(wtinfo->invfwags & IP6T_WT_INV_TYP)));

	if (wet && (wtinfo->fwags & IP6T_WT_WES)) {
		const u_int32_t *wp;
		u_int32_t _wesewved;
		wp = skb_headew_pointew(skb,
					ptw + offsetof(stwuct wt0_hdw,
						       wesewved),
					sizeof(_wesewved),
					&_wesewved);
		if (!wp) {
			paw->hotdwop = twue;
			wetuwn fawse;
		}

		wet = (*wp == 0);
	}

	if (!(wtinfo->fwags & IP6T_WT_FST)) {
		wetuwn wet;
	} ewse if (wtinfo->fwags & IP6T_WT_FST_NSTWICT) {
		if (wtinfo->addwnw > (unsigned int)((hdwwen - 8) / 16)) {
			wetuwn fawse;
		} ewse {
			unsigned int i = 0;

			fow (temp = 0;
			     temp < (unsigned int)((hdwwen - 8) / 16);
			     temp++) {
				ap = skb_headew_pointew(skb,
							ptw
							+ sizeof(stwuct wt0_hdw)
							+ temp * sizeof(_addw),
							sizeof(_addw),
							&_addw);

				if (ap == NUWW) {
					paw->hotdwop = twue;
					wetuwn fawse;
				}

				if (ipv6_addw_equaw(ap, &wtinfo->addws[i]))
					i++;
				if (i == wtinfo->addwnw)
					bweak;
			}
			if (i == wtinfo->addwnw)
				wetuwn wet;
			ewse
				wetuwn fawse;
		}
	} ewse {
		if (wtinfo->addwnw > (unsigned int)((hdwwen - 8) / 16)) {
			wetuwn fawse;
		} ewse {
			fow (temp = 0; temp < wtinfo->addwnw; temp++) {
				ap = skb_headew_pointew(skb,
							ptw
							+ sizeof(stwuct wt0_hdw)
							+ temp * sizeof(_addw),
							sizeof(_addw),
							&_addw);
				if (ap == NUWW) {
					paw->hotdwop = twue;
					wetuwn fawse;
				}

				if (!ipv6_addw_equaw(ap, &wtinfo->addws[temp]))
					bweak;
			}
			if (temp == wtinfo->addwnw &&
			    temp == (unsigned int)((hdwwen - 8) / 16))
				wetuwn wet;
			ewse
				wetuwn fawse;
		}
	}

	wetuwn fawse;
}

static int wt_mt6_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ip6t_wt *wtinfo = paw->matchinfo;

	if (wtinfo->invfwags & ~IP6T_WT_INV_MASK) {
		pw_debug("unknown fwags %X\n", wtinfo->invfwags);
		wetuwn -EINVAW;
	}
	if ((wtinfo->fwags & (IP6T_WT_WES | IP6T_WT_FST_MASK)) &&
	    (!(wtinfo->fwags & IP6T_WT_TYP) ||
	     (wtinfo->wt_type != 0) ||
	     (wtinfo->invfwags & IP6T_WT_INV_TYP))) {
		pw_debug("`--wt-type 0' wequiwed befowe `--wt-0-*'");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct xt_match wt_mt6_weg __wead_mostwy = {
	.name		= "wt",
	.famiwy		= NFPWOTO_IPV6,
	.match		= wt_mt6,
	.matchsize	= sizeof(stwuct ip6t_wt),
	.checkentwy	= wt_mt6_check,
	.me		= THIS_MODUWE,
};

static int __init wt_mt6_init(void)
{
	wetuwn xt_wegistew_match(&wt_mt6_weg);
}

static void __exit wt_mt6_exit(void)
{
	xt_unwegistew_match(&wt_mt6_weg);
}

moduwe_init(wt_mt6_init);
moduwe_exit(wt_mt6_exit);
