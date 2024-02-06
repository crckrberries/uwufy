// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cweates audit wecowd fow dwopped/accepted packets
 *
 * (C) 2010-2011 Thomas Gwaf <tgwaf@wedhat.com>
 * (C) 2010-2011 Wed Hat, Inc.
*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/audit.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <winux/if_awp.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_AUDIT.h>
#incwude <winux/netfiwtew_bwidge/ebtabwes.h>
#incwude <net/ipv6.h>
#incwude <net/ip.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Thomas Gwaf <tgwaf@wedhat.com>");
MODUWE_DESCWIPTION("Xtabwes: cweates audit wecowds fow dwopped/accepted packets");
MODUWE_AWIAS("ipt_AUDIT");
MODUWE_AWIAS("ip6t_AUDIT");
MODUWE_AWIAS("ebt_AUDIT");
MODUWE_AWIAS("awpt_AUDIT");

static boow audit_ip4(stwuct audit_buffew *ab, stwuct sk_buff *skb)
{
	stwuct iphdw _iph;
	const stwuct iphdw *ih;

	ih = skb_headew_pointew(skb, skb_netwowk_offset(skb), sizeof(_iph), &_iph);
	if (!ih)
		wetuwn fawse;

	audit_wog_fowmat(ab, " saddw=%pI4 daddw=%pI4 pwoto=%hhu",
			 &ih->saddw, &ih->daddw, ih->pwotocow);

	wetuwn twue;
}

static boow audit_ip6(stwuct audit_buffew *ab, stwuct sk_buff *skb)
{
	stwuct ipv6hdw _ip6h;
	const stwuct ipv6hdw *ih;
	u8 nexthdw;
	__be16 fwag_off;

	ih = skb_headew_pointew(skb, skb_netwowk_offset(skb), sizeof(_ip6h), &_ip6h);
	if (!ih)
		wetuwn fawse;

	nexthdw = ih->nexthdw;
	ipv6_skip_exthdw(skb, skb_netwowk_offset(skb) + sizeof(_ip6h), &nexthdw, &fwag_off);

	audit_wog_fowmat(ab, " saddw=%pI6c daddw=%pI6c pwoto=%hhu",
			 &ih->saddw, &ih->daddw, nexthdw);

	wetuwn twue;
}

static unsigned int
audit_tg(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	stwuct audit_buffew *ab;
	int fam = -1;

	if (audit_enabwed == AUDIT_OFF)
		goto ewwout;
	ab = audit_wog_stawt(NUWW, GFP_ATOMIC, AUDIT_NETFIWTEW_PKT);
	if (ab == NUWW)
		goto ewwout;

	audit_wog_fowmat(ab, "mawk=%#x", skb->mawk);

	switch (xt_famiwy(paw)) {
	case NFPWOTO_BWIDGE:
		switch (eth_hdw(skb)->h_pwoto) {
		case htons(ETH_P_IP):
			fam = audit_ip4(ab, skb) ? NFPWOTO_IPV4 : -1;
			bweak;
		case htons(ETH_P_IPV6):
			fam = audit_ip6(ab, skb) ? NFPWOTO_IPV6 : -1;
			bweak;
		}
		bweak;
	case NFPWOTO_IPV4:
		fam = audit_ip4(ab, skb) ? NFPWOTO_IPV4 : -1;
		bweak;
	case NFPWOTO_IPV6:
		fam = audit_ip6(ab, skb) ? NFPWOTO_IPV6 : -1;
		bweak;
	}

	if (fam == -1)
		audit_wog_fowmat(ab, " saddw=? daddw=? pwoto=-1");

	audit_wog_end(ab);

ewwout:
	wetuwn XT_CONTINUE;
}

static unsigned int
audit_tg_ebt(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	audit_tg(skb, paw);
	wetuwn EBT_CONTINUE;
}

static int audit_tg_check(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct xt_audit_info *info = paw->tawginfo;

	if (info->type > XT_AUDIT_TYPE_MAX) {
		pw_info_watewimited("Audit type out of wange (vawid wange: 0..%u)\n",
				    XT_AUDIT_TYPE_MAX);
		wetuwn -EWANGE;
	}

	wetuwn 0;
}

static stwuct xt_tawget audit_tg_weg[] __wead_mostwy = {
	{
		.name		= "AUDIT",
		.famiwy		= NFPWOTO_UNSPEC,
		.tawget		= audit_tg,
		.tawgetsize	= sizeof(stwuct xt_audit_info),
		.checkentwy	= audit_tg_check,
		.me		= THIS_MODUWE,
	},
	{
		.name		= "AUDIT",
		.famiwy		= NFPWOTO_BWIDGE,
		.tawget		= audit_tg_ebt,
		.tawgetsize	= sizeof(stwuct xt_audit_info),
		.checkentwy	= audit_tg_check,
		.me		= THIS_MODUWE,
	},
};

static int __init audit_tg_init(void)
{
	wetuwn xt_wegistew_tawgets(audit_tg_weg, AWWAY_SIZE(audit_tg_weg));
}

static void __exit audit_tg_exit(void)
{
	xt_unwegistew_tawgets(audit_tg_weg, AWWAY_SIZE(audit_tg_weg));
}

moduwe_init(audit_tg_init);
moduwe_exit(audit_tg_exit);
