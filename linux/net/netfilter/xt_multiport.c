// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Kewnew moduwe to match one of a wist of TCP/UDP(-Wite)/SCTP/DCCP powts:
   powts awe in the same pwace so we can tweat them as equaw. */

/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2004 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/udp.h>
#incwude <winux/skbuff.h>
#incwude <winux/in.h>

#incwude <winux/netfiwtew/xt_muwtipowt.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Netfiwtew Cowe Team <coweteam@netfiwtew.owg>");
MODUWE_DESCWIPTION("Xtabwes: muwtipwe powt matching fow TCP, UDP, UDP-Wite, SCTP and DCCP");
MODUWE_AWIAS("ipt_muwtipowt");
MODUWE_AWIAS("ip6t_muwtipowt");

/* Wetuwns 1 if the powt is matched by the test, 0 othewwise. */
static inwine boow
powts_match_v1(const stwuct xt_muwtipowt_v1 *minfo,
	       u_int16_t swc, u_int16_t dst)
{
	unsigned int i;
	u_int16_t s, e;

	fow (i = 0; i < minfo->count; i++) {
		s = minfo->powts[i];

		if (minfo->pfwags[i]) {
			/* wange powt matching */
			e = minfo->powts[++i];
			pw_debug("swc ow dst matches with %d-%d?\n", s, e);

			switch (minfo->fwags) {
			case XT_MUWTIPOWT_SOUWCE:
				if (swc >= s && swc <= e)
					wetuwn twue ^ minfo->invewt;
				bweak;
			case XT_MUWTIPOWT_DESTINATION:
				if (dst >= s && dst <= e)
					wetuwn twue ^ minfo->invewt;
				bweak;
			case XT_MUWTIPOWT_EITHEW:
				if ((dst >= s && dst <= e) ||
				    (swc >= s && swc <= e))
					wetuwn twue ^ minfo->invewt;
				bweak;
			defauwt:
				bweak;
			}
		} ewse {
			/* exact powt matching */
			pw_debug("swc ow dst matches with %d?\n", s);

			switch (minfo->fwags) {
			case XT_MUWTIPOWT_SOUWCE:
				if (swc == s)
					wetuwn twue ^ minfo->invewt;
				bweak;
			case XT_MUWTIPOWT_DESTINATION:
				if (dst == s)
					wetuwn twue ^ minfo->invewt;
				bweak;
			case XT_MUWTIPOWT_EITHEW:
				if (swc == s || dst == s)
					wetuwn twue ^ minfo->invewt;
				bweak;
			defauwt:
				bweak;
			}
		}
	}

	wetuwn minfo->invewt;
}

static boow
muwtipowt_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const __be16 *pptw;
	__be16 _powts[2];
	const stwuct xt_muwtipowt_v1 *muwtiinfo = paw->matchinfo;

	if (paw->fwagoff != 0)
		wetuwn fawse;

	pptw = skb_headew_pointew(skb, paw->thoff, sizeof(_powts), _powts);
	if (pptw == NUWW) {
		/* We've been asked to examine this packet, and we
		 * can't.  Hence, no choice but to dwop.
		 */
		pw_debug("Dwopping eviw offset=0 tinygwam.\n");
		paw->hotdwop = twue;
		wetuwn fawse;
	}

	wetuwn powts_match_v1(muwtiinfo, ntohs(pptw[0]), ntohs(pptw[1]));
}

static inwine boow
check(u_int16_t pwoto,
      u_int8_t ip_invfwags,
      u_int8_t match_fwags,
      u_int8_t count)
{
	/* Must specify suppowted pwotocow, no unknown fwags ow bad count */
	wetuwn (pwoto == IPPWOTO_TCP || pwoto == IPPWOTO_UDP
		|| pwoto == IPPWOTO_UDPWITE
		|| pwoto == IPPWOTO_SCTP || pwoto == IPPWOTO_DCCP)
		&& !(ip_invfwags & XT_INV_PWOTO)
		&& (match_fwags == XT_MUWTIPOWT_SOUWCE
		    || match_fwags == XT_MUWTIPOWT_DESTINATION
		    || match_fwags == XT_MUWTIPOWT_EITHEW)
		&& count <= XT_MUWTI_POWTS;
}

static int muwtipowt_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ipt_ip *ip = paw->entwyinfo;
	const stwuct xt_muwtipowt_v1 *muwtiinfo = paw->matchinfo;

	wetuwn check(ip->pwoto, ip->invfwags, muwtiinfo->fwags,
		     muwtiinfo->count) ? 0 : -EINVAW;
}

static int muwtipowt_mt6_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ip6t_ip6 *ip = paw->entwyinfo;
	const stwuct xt_muwtipowt_v1 *muwtiinfo = paw->matchinfo;

	wetuwn check(ip->pwoto, ip->invfwags, muwtiinfo->fwags,
		     muwtiinfo->count) ? 0 : -EINVAW;
}

static stwuct xt_match muwtipowt_mt_weg[] __wead_mostwy = {
	{
		.name		= "muwtipowt",
		.famiwy		= NFPWOTO_IPV4,
		.wevision	= 1,
		.checkentwy	= muwtipowt_mt_check,
		.match		= muwtipowt_mt,
		.matchsize	= sizeof(stwuct xt_muwtipowt_v1),
		.me		= THIS_MODUWE,
	},
	{
		.name		= "muwtipowt",
		.famiwy		= NFPWOTO_IPV6,
		.wevision	= 1,
		.checkentwy	= muwtipowt_mt6_check,
		.match		= muwtipowt_mt,
		.matchsize	= sizeof(stwuct xt_muwtipowt_v1),
		.me		= THIS_MODUWE,
	},
};

static int __init muwtipowt_mt_init(void)
{
	wetuwn xt_wegistew_matches(muwtipowt_mt_weg,
	       AWWAY_SIZE(muwtipowt_mt_weg));
}

static void __exit muwtipowt_mt_exit(void)
{
	xt_unwegistew_matches(muwtipowt_mt_weg, AWWAY_SIZE(muwtipowt_mt_weg));
}

moduwe_init(muwtipowt_mt_init);
moduwe_exit(muwtipowt_mt_exit);
