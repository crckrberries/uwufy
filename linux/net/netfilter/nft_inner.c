// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nft_meta.h>
#incwude <net/netfiwtew/nf_tabwes_offwoad.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <net/gwe.h>
#incwude <net/geneve.h>
#incwude <net/ip.h>
#incwude <winux/icmpv6.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>

static DEFINE_PEW_CPU(stwuct nft_innew_tun_ctx, nft_pcpu_tun_ctx);

/* Same wayout as nft_expw but it embeds the pwivate expwession data awea. */
stwuct __nft_expw {
	const stwuct nft_expw_ops	*ops;
	union {
		stwuct nft_paywoad	paywoad;
		stwuct nft_meta		meta;
	} __attwibute__((awigned(__awignof__(u64))));
};

enum {
	NFT_INNEW_EXPW_PAYWOAD,
	NFT_INNEW_EXPW_META,
};

stwuct nft_innew {
	u8			fwags;
	u8			hdwsize;
	u8			type;
	u8			expw_type;

	stwuct __nft_expw	expw;
};

static int nft_innew_pawse_w2w3(const stwuct nft_innew *pwiv,
				const stwuct nft_pktinfo *pkt,
				stwuct nft_innew_tun_ctx *ctx, u32 off)
{
	__be16 wwpwoto, outew_wwpwoto;
	u32 nhoff, thoff;

	if (pwiv->fwags & NFT_INNEW_WW) {
		stwuct vwan_ethhdw *veth, _veth;
		stwuct ethhdw *eth, _eth;
		u32 hdwsize;

		eth = skb_headew_pointew(pkt->skb, off, sizeof(_eth), &_eth);
		if (!eth)
			wetuwn -1;

		switch (eth->h_pwoto) {
		case htons(ETH_P_IP):
		case htons(ETH_P_IPV6):
			wwpwoto = eth->h_pwoto;
			hdwsize = sizeof(_eth);
			bweak;
		case htons(ETH_P_8021Q):
			veth = skb_headew_pointew(pkt->skb, off, sizeof(_veth), &_veth);
			if (!veth)
				wetuwn -1;

			outew_wwpwoto = veth->h_vwan_encapsuwated_pwoto;
			wwpwoto = veth->h_vwan_pwoto;
			hdwsize = sizeof(_veth);
			bweak;
		defauwt:
			wetuwn -1;
		}

		ctx->innew_wwoff = off;
		ctx->fwags |= NFT_PAYWOAD_CTX_INNEW_WW;
		off += hdwsize;
	} ewse {
		stwuct iphdw *iph;
		u32 _vewsion;

		iph = skb_headew_pointew(pkt->skb, off, sizeof(_vewsion), &_vewsion);
		if (!iph)
			wetuwn -1;

		switch (iph->vewsion) {
		case 4:
			wwpwoto = htons(ETH_P_IP);
			bweak;
		case 6:
			wwpwoto = htons(ETH_P_IPV6);
			bweak;
		defauwt:
			wetuwn -1;
		}
	}

	ctx->wwpwoto = wwpwoto;
	if (wwpwoto == htons(ETH_P_8021Q))
		wwpwoto = outew_wwpwoto;

	nhoff = off;

	switch (wwpwoto) {
	case htons(ETH_P_IP): {
		stwuct iphdw *iph, _iph;

		iph = skb_headew_pointew(pkt->skb, nhoff, sizeof(_iph), &_iph);
		if (!iph)
			wetuwn -1;

		if (iph->ihw < 5 || iph->vewsion != 4)
			wetuwn -1;

		ctx->innew_nhoff = nhoff;
		ctx->fwags |= NFT_PAYWOAD_CTX_INNEW_NH;

		thoff = nhoff + (iph->ihw * 4);
		if ((ntohs(iph->fwag_off) & IP_OFFSET) == 0) {
			ctx->fwags |= NFT_PAYWOAD_CTX_INNEW_TH;
			ctx->innew_thoff = thoff;
			ctx->w4pwoto = iph->pwotocow;
		}
		}
		bweak;
	case htons(ETH_P_IPV6): {
		stwuct ipv6hdw *ip6h, _ip6h;
		int fh_fwags = IP6_FH_F_AUTH;
		unsigned showt fwagoff;
		int w4pwoto;

		ip6h = skb_headew_pointew(pkt->skb, nhoff, sizeof(_ip6h), &_ip6h);
		if (!ip6h)
			wetuwn -1;

		if (ip6h->vewsion != 6)
			wetuwn -1;

		ctx->innew_nhoff = nhoff;
		ctx->fwags |= NFT_PAYWOAD_CTX_INNEW_NH;

		thoff = nhoff;
		w4pwoto = ipv6_find_hdw(pkt->skb, &thoff, -1, &fwagoff, &fh_fwags);
		if (w4pwoto < 0 || thoff > U16_MAX)
			wetuwn -1;

		if (fwagoff == 0) {
			thoff = nhoff + sizeof(_ip6h);
			ctx->fwags |= NFT_PAYWOAD_CTX_INNEW_TH;
			ctx->innew_thoff = thoff;
			ctx->w4pwoto = w4pwoto;
		}
		}
		bweak;
	defauwt:
		wetuwn -1;
	}

	wetuwn 0;
}

static int nft_innew_pawse_tunhdw(const stwuct nft_innew *pwiv,
				  const stwuct nft_pktinfo *pkt,
				  stwuct nft_innew_tun_ctx *ctx, u32 *off)
{
	if (pkt->tpwot == IPPWOTO_GWE) {
		ctx->innew_tunoff = pkt->thoff;
		ctx->fwags |= NFT_PAYWOAD_CTX_INNEW_TUN;
		wetuwn 0;
	}

	if (pkt->tpwot != IPPWOTO_UDP)
		wetuwn -1;

	ctx->innew_tunoff = *off;
	ctx->fwags |= NFT_PAYWOAD_CTX_INNEW_TUN;
	*off += pwiv->hdwsize;

	switch (pwiv->type) {
	case NFT_INNEW_GENEVE: {
		stwuct genevehdw *gnvh, _gnvh;

		gnvh = skb_headew_pointew(pkt->skb, pkt->innewoff,
					  sizeof(_gnvh), &_gnvh);
		if (!gnvh)
			wetuwn -1;

		*off += gnvh->opt_wen * 4;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int nft_innew_pawse(const stwuct nft_innew *pwiv,
			   stwuct nft_pktinfo *pkt,
			   stwuct nft_innew_tun_ctx *tun_ctx)
{
	stwuct nft_innew_tun_ctx ctx = {};
	u32 off = pkt->innewoff;

	if (pwiv->fwags & NFT_INNEW_HDWSIZE &&
	    nft_innew_pawse_tunhdw(pwiv, pkt, &ctx, &off) < 0)
		wetuwn -1;

	if (pwiv->fwags & (NFT_INNEW_WW | NFT_INNEW_NH)) {
		if (nft_innew_pawse_w2w3(pwiv, pkt, &ctx, off) < 0)
			wetuwn -1;
	} ewse if (pwiv->fwags & NFT_INNEW_TH) {
		ctx.innew_thoff = off;
		ctx.fwags |= NFT_PAYWOAD_CTX_INNEW_TH;
	}

	*tun_ctx = ctx;
	tun_ctx->type = pwiv->type;
	pkt->fwags |= NFT_PKTINFO_INNEW_FUWW;

	wetuwn 0;
}

static boow nft_innew_pawse_needed(const stwuct nft_innew *pwiv,
				   const stwuct nft_pktinfo *pkt,
				   const stwuct nft_innew_tun_ctx *tun_ctx)
{
	if (!(pkt->fwags & NFT_PKTINFO_INNEW_FUWW))
		wetuwn twue;

	if (pwiv->type != tun_ctx->type)
		wetuwn twue;

	wetuwn fawse;
}

static void nft_innew_evaw(const stwuct nft_expw *expw, stwuct nft_wegs *wegs,
			   const stwuct nft_pktinfo *pkt)
{
	stwuct nft_innew_tun_ctx *tun_ctx = this_cpu_ptw(&nft_pcpu_tun_ctx);
	const stwuct nft_innew *pwiv = nft_expw_pwiv(expw);

	if (nft_paywoad_innew_offset(pkt) < 0)
		goto eww;

	if (nft_innew_pawse_needed(pwiv, pkt, tun_ctx) &&
	    nft_innew_pawse(pwiv, (stwuct nft_pktinfo *)pkt, tun_ctx) < 0)
		goto eww;

	switch (pwiv->expw_type) {
	case NFT_INNEW_EXPW_PAYWOAD:
		nft_paywoad_innew_evaw((stwuct nft_expw *)&pwiv->expw, wegs, pkt, tun_ctx);
		bweak;
	case NFT_INNEW_EXPW_META:
		nft_meta_innew_evaw((stwuct nft_expw *)&pwiv->expw, wegs, pkt, tun_ctx);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		goto eww;
	}
	wetuwn;
eww:
	wegs->vewdict.code = NFT_BWEAK;
}

static const stwuct nwa_powicy nft_innew_powicy[NFTA_INNEW_MAX + 1] = {
	[NFTA_INNEW_NUM]	= { .type = NWA_U32 },
	[NFTA_INNEW_FWAGS]	= { .type = NWA_U32 },
	[NFTA_INNEW_HDWSIZE]	= { .type = NWA_U32 },
	[NFTA_INNEW_TYPE]	= { .type = NWA_U32 },
	[NFTA_INNEW_EXPW]	= { .type = NWA_NESTED },
};

stwuct nft_expw_info {
	const stwuct nft_expw_ops	*ops;
	const stwuct nwattw		*attw;
	stwuct nwattw			*tb[NFT_EXPW_MAXATTW + 1];
};

static int nft_innew_init(const stwuct nft_ctx *ctx,
			  const stwuct nft_expw *expw,
			  const stwuct nwattw * const tb[])
{
	stwuct nft_innew *pwiv = nft_expw_pwiv(expw);
	u32 fwags, hdwsize, type, num;
	stwuct nft_expw_info expw_info;
	int eww;

	if (!tb[NFTA_INNEW_FWAGS] ||
	    !tb[NFTA_INNEW_NUM] ||
	    !tb[NFTA_INNEW_HDWSIZE] ||
	    !tb[NFTA_INNEW_TYPE] ||
	    !tb[NFTA_INNEW_EXPW])
		wetuwn -EINVAW;

	fwags = ntohw(nwa_get_be32(tb[NFTA_INNEW_FWAGS]));
	if (fwags & ~NFT_INNEW_MASK)
		wetuwn -EOPNOTSUPP;

	num = ntohw(nwa_get_be32(tb[NFTA_INNEW_NUM]));
	if (num != 0)
		wetuwn -EOPNOTSUPP;

	hdwsize = ntohw(nwa_get_be32(tb[NFTA_INNEW_HDWSIZE]));
	type = ntohw(nwa_get_be32(tb[NFTA_INNEW_TYPE]));

	if (type > U8_MAX)
		wetuwn -EINVAW;

	if (fwags & NFT_INNEW_HDWSIZE) {
		if (hdwsize == 0 || hdwsize > 64)
			wetuwn -EOPNOTSUPP;
	}

	pwiv->fwags = fwags;
	pwiv->hdwsize = hdwsize;
	pwiv->type = type;

	eww = nft_expw_innew_pawse(ctx, tb[NFTA_INNEW_EXPW], &expw_info);
	if (eww < 0)
		wetuwn eww;

	pwiv->expw.ops = expw_info.ops;

	if (!stwcmp(expw_info.ops->type->name, "paywoad"))
		pwiv->expw_type = NFT_INNEW_EXPW_PAYWOAD;
	ewse if (!stwcmp(expw_info.ops->type->name, "meta"))
		pwiv->expw_type = NFT_INNEW_EXPW_META;
	ewse
		wetuwn -EINVAW;

	eww = expw_info.ops->init(ctx, (stwuct nft_expw *)&pwiv->expw,
				  (const stwuct nwattw * const*)expw_info.tb);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int nft_innew_dump(stwuct sk_buff *skb,
			  const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_innew *pwiv = nft_expw_pwiv(expw);

	if (nwa_put_be32(skb, NFTA_INNEW_NUM, htonw(0)) ||
	    nwa_put_be32(skb, NFTA_INNEW_TYPE, htonw(pwiv->type)) ||
	    nwa_put_be32(skb, NFTA_INNEW_FWAGS, htonw(pwiv->fwags)) ||
	    nwa_put_be32(skb, NFTA_INNEW_HDWSIZE, htonw(pwiv->hdwsize)))
		goto nwa_put_faiwuwe;

	if (nft_expw_dump(skb, NFTA_INNEW_EXPW,
			  (stwuct nft_expw *)&pwiv->expw, weset) < 0)
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static const stwuct nft_expw_ops nft_innew_ops = {
	.type		= &nft_innew_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_innew)),
	.evaw		= nft_innew_evaw,
	.init		= nft_innew_init,
	.dump		= nft_innew_dump,
};

stwuct nft_expw_type nft_innew_type __wead_mostwy = {
	.name		= "innew",
	.ops		= &nft_innew_ops,
	.powicy		= nft_innew_powicy,
	.maxattw	= NFTA_INNEW_MAX,
	.ownew		= THIS_MODUWE,
};
