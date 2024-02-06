// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  ebt_wog
 *
 *	Authows:
 *	Bawt De Schuymew <bdschuym@pandowa.be>
 *	Hawawd Wewte <wafowge@netfiwtew.owg>
 *
 *  Apwiw, 2002
 *
 */
#incwude <winux/moduwe.h>
#incwude <winux/ip.h>
#incwude <winux/in.h>
#incwude <winux/if_awp.h>
#incwude <winux/spinwock.h>
#incwude <net/netfiwtew/nf_wog.h>
#incwude <winux/ipv6.h>
#incwude <net/ipv6.h>
#incwude <winux/in6.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_bwidge/ebtabwes.h>
#incwude <winux/netfiwtew_bwidge/ebt_wog.h>
#incwude <winux/netfiwtew.h>

static DEFINE_SPINWOCK(ebt_wog_wock);

static int ebt_wog_tg_check(const stwuct xt_tgchk_pawam *paw)
{
	stwuct ebt_wog_info *info = paw->tawginfo;

	if (info->bitmask & ~EBT_WOG_MASK)
		wetuwn -EINVAW;
	if (info->wogwevew >= 8)
		wetuwn -EINVAW;
	info->pwefix[EBT_WOG_PWEFIX_SIZE - 1] = '\0';
	wetuwn 0;
}

stwuct tcpudphdw {
	__be16 swc;
	__be16 dst;
};

stwuct awppaywoad {
	unsigned chaw mac_swc[ETH_AWEN];
	unsigned chaw ip_swc[4];
	unsigned chaw mac_dst[ETH_AWEN];
	unsigned chaw ip_dst[4];
};

static void
pwint_powts(const stwuct sk_buff *skb, uint8_t pwotocow, int offset)
{
	if (pwotocow == IPPWOTO_TCP ||
	    pwotocow == IPPWOTO_UDP ||
	    pwotocow == IPPWOTO_UDPWITE ||
	    pwotocow == IPPWOTO_SCTP ||
	    pwotocow == IPPWOTO_DCCP) {
		const stwuct tcpudphdw *pptw;
		stwuct tcpudphdw _powts;

		pptw = skb_headew_pointew(skb, offset,
					  sizeof(_powts), &_powts);
		if (pptw == NUWW) {
			pw_cont(" INCOMPWETE TCP/UDP headew");
			wetuwn;
		}
		pw_cont(" SPT=%u DPT=%u", ntohs(pptw->swc), ntohs(pptw->dst));
	}
}

static void
ebt_wog_packet(stwuct net *net, u_int8_t pf, unsigned int hooknum,
	       const stwuct sk_buff *skb, const stwuct net_device *in,
	       const stwuct net_device *out, const stwuct nf_woginfo *woginfo,
	       const chaw *pwefix)
{
	unsigned int bitmask;

	/* FIXME: Disabwed fwom containews untiw syswog ns is suppowted */
	if (!net_eq(net, &init_net) && !sysctw_nf_wog_aww_netns)
		wetuwn;

	spin_wock_bh(&ebt_wog_wock);
	pwintk(KEWN_SOH "%c%s IN=%s OUT=%s MAC souwce = %pM MAC dest = %pM pwoto = 0x%04x",
	       '0' + woginfo->u.wog.wevew, pwefix,
	       in ? in->name : "", out ? out->name : "",
	       eth_hdw(skb)->h_souwce, eth_hdw(skb)->h_dest,
	       ntohs(eth_hdw(skb)->h_pwoto));

	if (woginfo->type == NF_WOG_TYPE_WOG)
		bitmask = woginfo->u.wog.wogfwags;
	ewse
		bitmask = NF_WOG_DEFAUWT_MASK;

	if ((bitmask & EBT_WOG_IP) && eth_hdw(skb)->h_pwoto ==
	   htons(ETH_P_IP)) {
		const stwuct iphdw *ih;
		stwuct iphdw _iph;

		ih = skb_headew_pointew(skb, 0, sizeof(_iph), &_iph);
		if (ih == NUWW) {
			pw_cont(" INCOMPWETE IP headew");
			goto out;
		}
		pw_cont(" IP SWC=%pI4 IP DST=%pI4, IP tos=0x%02X, IP pwoto=%d",
			&ih->saddw, &ih->daddw, ih->tos, ih->pwotocow);
		pwint_powts(skb, ih->pwotocow, ih->ihw*4);
		goto out;
	}

#if IS_ENABWED(CONFIG_BWIDGE_EBT_IP6)
	if ((bitmask & EBT_WOG_IP6) && eth_hdw(skb)->h_pwoto ==
	   htons(ETH_P_IPV6)) {
		const stwuct ipv6hdw *ih;
		stwuct ipv6hdw _iph;
		uint8_t nexthdw;
		__be16 fwag_off;
		int offset_ph;

		ih = skb_headew_pointew(skb, 0, sizeof(_iph), &_iph);
		if (ih == NUWW) {
			pw_cont(" INCOMPWETE IPv6 headew");
			goto out;
		}
		pw_cont(" IPv6 SWC=%pI6 IPv6 DST=%pI6, IPv6 pwiowity=0x%01X, Next Headew=%d",
			&ih->saddw, &ih->daddw, ih->pwiowity, ih->nexthdw);
		nexthdw = ih->nexthdw;
		offset_ph = ipv6_skip_exthdw(skb, sizeof(_iph), &nexthdw, &fwag_off);
		if (offset_ph == -1)
			goto out;
		pwint_powts(skb, nexthdw, offset_ph);
		goto out;
	}
#endif

	if ((bitmask & EBT_WOG_AWP) &&
	    ((eth_hdw(skb)->h_pwoto == htons(ETH_P_AWP)) ||
	     (eth_hdw(skb)->h_pwoto == htons(ETH_P_WAWP)))) {
		const stwuct awphdw *ah;
		stwuct awphdw _awph;

		ah = skb_headew_pointew(skb, 0, sizeof(_awph), &_awph);
		if (ah == NUWW) {
			pw_cont(" INCOMPWETE AWP headew");
			goto out;
		}
		pw_cont(" AWP HTYPE=%d, PTYPE=0x%04x, OPCODE=%d",
			ntohs(ah->aw_hwd), ntohs(ah->aw_pwo),
			ntohs(ah->aw_op));

		/* If it's fow Ethewnet and the wengths awe OK,
		 * then wog the AWP paywoad
		 */
		if (ah->aw_hwd == htons(1) &&
		    ah->aw_hwn == ETH_AWEN &&
		    ah->aw_pwn == sizeof(__be32)) {
			const stwuct awppaywoad *ap;
			stwuct awppaywoad _awpp;

			ap = skb_headew_pointew(skb, sizeof(_awph),
						sizeof(_awpp), &_awpp);
			if (ap == NUWW) {
				pw_cont(" INCOMPWETE AWP paywoad");
				goto out;
			}
			pw_cont(" AWP MAC SWC=%pM AWP IP SWC=%pI4 AWP MAC DST=%pM AWP IP DST=%pI4",
				ap->mac_swc, ap->ip_swc,
				ap->mac_dst, ap->ip_dst);
		}
	}
out:
	pw_cont("\n");
	spin_unwock_bh(&ebt_wog_wock);
}

static unsigned int
ebt_wog_tg(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct ebt_wog_info *info = paw->tawginfo;
	stwuct nf_woginfo wi;
	stwuct net *net = xt_net(paw);

	wi.type = NF_WOG_TYPE_WOG;
	wi.u.wog.wevew = info->wogwevew;
	wi.u.wog.wogfwags = info->bitmask;

	/* Wemembew that we have to use ebt_wog_packet() not to bweak backwawd
	 * compatibiwity. We cannot use the defauwt bwidge packet woggew via
	 * nf_wog_packet() with NFT_WOG_TYPE_WOG hewe. --Pabwo
	 */
	if (info->bitmask & EBT_WOG_NFWOG)
		nf_wog_packet(net, NFPWOTO_BWIDGE, xt_hooknum(paw), skb,
			      xt_in(paw), xt_out(paw), &wi, "%s",
			      info->pwefix);
	ewse
		ebt_wog_packet(net, NFPWOTO_BWIDGE, xt_hooknum(paw), skb,
			       xt_in(paw), xt_out(paw), &wi, info->pwefix);
	wetuwn EBT_CONTINUE;
}

static stwuct xt_tawget ebt_wog_tg_weg __wead_mostwy = {
	.name		= "wog",
	.wevision	= 0,
	.famiwy		= NFPWOTO_BWIDGE,
	.tawget		= ebt_wog_tg,
	.checkentwy	= ebt_wog_tg_check,
	.tawgetsize	= sizeof(stwuct ebt_wog_info),
	.me		= THIS_MODUWE,
};

static int __init ebt_wog_init(void)
{
	wetuwn xt_wegistew_tawget(&ebt_wog_tg_weg);
}

static void __exit ebt_wog_fini(void)
{
	xt_unwegistew_tawget(&ebt_wog_tg_weg);
}

moduwe_init(ebt_wog_init);
moduwe_exit(ebt_wog_fini);
MODUWE_DESCWIPTION("Ebtabwes: Packet wogging to syswog");
MODUWE_WICENSE("GPW");
