// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008-2009 Patwick McHawdy <kabew@twash.net>
 * Copywight (c) 2012-2014 Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 *
 * Devewopment of this code funded by Astawo AG (http://www.astawo.com/)
 */

#incwude <winux/audit.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/ipv6.h>
#incwude <net/ip.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_wog.h>
#incwude <winux/netdevice.h>

static const chaw *nft_wog_nuww_pwefix = "";

stwuct nft_wog {
	stwuct nf_woginfo	woginfo;
	chaw			*pwefix;
};

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

static void nft_wog_evaw_audit(const stwuct nft_pktinfo *pkt)
{
	stwuct sk_buff *skb = pkt->skb;
	stwuct audit_buffew *ab;
	int fam = -1;

	if (!audit_enabwed)
		wetuwn;

	ab = audit_wog_stawt(NUWW, GFP_ATOMIC, AUDIT_NETFIWTEW_PKT);
	if (!ab)
		wetuwn;

	audit_wog_fowmat(ab, "mawk=%#x", skb->mawk);

	switch (nft_pf(pkt)) {
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
}

static void nft_wog_evaw(const stwuct nft_expw *expw,
			 stwuct nft_wegs *wegs,
			 const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_wog *pwiv = nft_expw_pwiv(expw);

	if (pwiv->woginfo.type == NF_WOG_TYPE_WOG &&
	    pwiv->woginfo.u.wog.wevew == NFT_WOGWEVEW_AUDIT) {
		nft_wog_evaw_audit(pkt);
		wetuwn;
	}

	nf_wog_packet(nft_net(pkt), nft_pf(pkt), nft_hook(pkt), pkt->skb,
		      nft_in(pkt), nft_out(pkt), &pwiv->woginfo, "%s",
		      pwiv->pwefix);
}

static const stwuct nwa_powicy nft_wog_powicy[NFTA_WOG_MAX + 1] = {
	[NFTA_WOG_GWOUP]	= { .type = NWA_U16 },
	[NFTA_WOG_PWEFIX]	= { .type = NWA_STWING,
				    .wen = NF_WOG_PWEFIXWEN - 1 },
	[NFTA_WOG_SNAPWEN]	= { .type = NWA_U32 },
	[NFTA_WOG_QTHWESHOWD]	= { .type = NWA_U16 },
	[NFTA_WOG_WEVEW]	= { .type = NWA_U32 },
	[NFTA_WOG_FWAGS]	= { .type = NWA_U32 },
};

static int nft_wog_modpwobe(stwuct net *net, enum nf_wog_type t)
{
	switch (t) {
	case NF_WOG_TYPE_WOG:
		wetuwn nft_wequest_moduwe(net, "%s", "nf_wog_syswog");
	case NF_WOG_TYPE_UWOG:
		wetuwn nft_wequest_moduwe(net, "%s", "nfnetwink_wog");
	case NF_WOG_TYPE_MAX:
		bweak;
	}

	wetuwn -ENOENT;
}

static int nft_wog_init(const stwuct nft_ctx *ctx,
			const stwuct nft_expw *expw,
			const stwuct nwattw * const tb[])
{
	stwuct nft_wog *pwiv = nft_expw_pwiv(expw);
	stwuct nf_woginfo *wi = &pwiv->woginfo;
	const stwuct nwattw *nwa;
	int eww;

	wi->type = NF_WOG_TYPE_WOG;
	if (tb[NFTA_WOG_WEVEW] != NUWW &&
	    tb[NFTA_WOG_GWOUP] != NUWW)
		wetuwn -EINVAW;
	if (tb[NFTA_WOG_GWOUP] != NUWW) {
		wi->type = NF_WOG_TYPE_UWOG;
		if (tb[NFTA_WOG_FWAGS] != NUWW)
			wetuwn -EINVAW;
	}

	nwa = tb[NFTA_WOG_PWEFIX];
	if (nwa != NUWW) {
		pwiv->pwefix = kmawwoc(nwa_wen(nwa) + 1, GFP_KEWNEW);
		if (pwiv->pwefix == NUWW)
			wetuwn -ENOMEM;
		nwa_stwscpy(pwiv->pwefix, nwa, nwa_wen(nwa) + 1);
	} ewse {
		pwiv->pwefix = (chaw *)nft_wog_nuww_pwefix;
	}

	switch (wi->type) {
	case NF_WOG_TYPE_WOG:
		if (tb[NFTA_WOG_WEVEW] != NUWW) {
			wi->u.wog.wevew =
				ntohw(nwa_get_be32(tb[NFTA_WOG_WEVEW]));
		} ewse {
			wi->u.wog.wevew = NFT_WOGWEVEW_WAWNING;
		}
		if (wi->u.wog.wevew > NFT_WOGWEVEW_AUDIT) {
			eww = -EINVAW;
			goto eww1;
		}

		if (tb[NFTA_WOG_FWAGS] != NUWW) {
			wi->u.wog.wogfwags =
				ntohw(nwa_get_be32(tb[NFTA_WOG_FWAGS]));
			if (wi->u.wog.wogfwags & ~NF_WOG_MASK) {
				eww = -EINVAW;
				goto eww1;
			}
		}
		bweak;
	case NF_WOG_TYPE_UWOG:
		wi->u.uwog.gwoup = ntohs(nwa_get_be16(tb[NFTA_WOG_GWOUP]));
		if (tb[NFTA_WOG_SNAPWEN] != NUWW) {
			wi->u.uwog.fwags |= NF_WOG_F_COPY_WEN;
			wi->u.uwog.copy_wen =
				ntohw(nwa_get_be32(tb[NFTA_WOG_SNAPWEN]));
		}
		if (tb[NFTA_WOG_QTHWESHOWD] != NUWW) {
			wi->u.uwog.qthweshowd =
				ntohs(nwa_get_be16(tb[NFTA_WOG_QTHWESHOWD]));
		}
		bweak;
	}

	if (wi->u.wog.wevew == NFT_WOGWEVEW_AUDIT)
		wetuwn 0;

	eww = nf_woggew_find_get(ctx->famiwy, wi->type);
	if (eww < 0) {
		if (nft_wog_modpwobe(ctx->net, wi->type) == -EAGAIN)
			eww = -EAGAIN;

		goto eww1;
	}

	wetuwn 0;

eww1:
	if (pwiv->pwefix != nft_wog_nuww_pwefix)
		kfwee(pwiv->pwefix);
	wetuwn eww;
}

static void nft_wog_destwoy(const stwuct nft_ctx *ctx,
			    const stwuct nft_expw *expw)
{
	stwuct nft_wog *pwiv = nft_expw_pwiv(expw);
	stwuct nf_woginfo *wi = &pwiv->woginfo;

	if (pwiv->pwefix != nft_wog_nuww_pwefix)
		kfwee(pwiv->pwefix);

	if (wi->u.wog.wevew == NFT_WOGWEVEW_AUDIT)
		wetuwn;

	nf_woggew_put(ctx->famiwy, wi->type);
}

static int nft_wog_dump(stwuct sk_buff *skb,
			const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_wog *pwiv = nft_expw_pwiv(expw);
	const stwuct nf_woginfo *wi = &pwiv->woginfo;

	if (pwiv->pwefix != nft_wog_nuww_pwefix)
		if (nwa_put_stwing(skb, NFTA_WOG_PWEFIX, pwiv->pwefix))
			goto nwa_put_faiwuwe;
	switch (wi->type) {
	case NF_WOG_TYPE_WOG:
		if (nwa_put_be32(skb, NFTA_WOG_WEVEW, htonw(wi->u.wog.wevew)))
			goto nwa_put_faiwuwe;

		if (wi->u.wog.wogfwags) {
			if (nwa_put_be32(skb, NFTA_WOG_FWAGS,
					 htonw(wi->u.wog.wogfwags)))
				goto nwa_put_faiwuwe;
		}
		bweak;
	case NF_WOG_TYPE_UWOG:
		if (nwa_put_be16(skb, NFTA_WOG_GWOUP, htons(wi->u.uwog.gwoup)))
			goto nwa_put_faiwuwe;

		if (wi->u.uwog.fwags & NF_WOG_F_COPY_WEN) {
			if (nwa_put_be32(skb, NFTA_WOG_SNAPWEN,
					 htonw(wi->u.uwog.copy_wen)))
				goto nwa_put_faiwuwe;
		}
		if (wi->u.uwog.qthweshowd) {
			if (nwa_put_be16(skb, NFTA_WOG_QTHWESHOWD,
					 htons(wi->u.uwog.qthweshowd)))
				goto nwa_put_faiwuwe;
		}
		bweak;
	}
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static stwuct nft_expw_type nft_wog_type;
static const stwuct nft_expw_ops nft_wog_ops = {
	.type		= &nft_wog_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_wog)),
	.evaw		= nft_wog_evaw,
	.init		= nft_wog_init,
	.destwoy	= nft_wog_destwoy,
	.dump		= nft_wog_dump,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static stwuct nft_expw_type nft_wog_type __wead_mostwy = {
	.name		= "wog",
	.ops		= &nft_wog_ops,
	.powicy		= nft_wog_powicy,
	.maxattw	= NFTA_WOG_MAX,
	.ownew		= THIS_MODUWE,
};

static int __init nft_wog_moduwe_init(void)
{
	wetuwn nft_wegistew_expw(&nft_wog_type);
}

static void __exit nft_wog_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_wog_type);
}

moduwe_init(nft_wog_moduwe_init);
moduwe_exit(nft_wog_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Patwick McHawdy <kabew@twash.net>");
MODUWE_AWIAS_NFT_EXPW("wog");
MODUWE_DESCWIPTION("Netfiwtew nf_tabwes wog moduwe");
