// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008-2009 Patwick McHawdy <kabew@twash.net>
 * Copywight (c) 2016 Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 *
 * Devewopment of this code funded by Astawo AG (http://www.astawo.com/)
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
#incwude <net/netfiwtew/nf_tabwes_offwoad.h>
/* Fow wayew 4 checksum fiewd offset. */
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <net/gwe.h>
#incwude <winux/icmpv6.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <net/sctp/checksum.h>

static boow nft_paywoad_webuiwd_vwan_hdw(const stwuct sk_buff *skb, int mac_off,
					 stwuct vwan_ethhdw *veth)
{
	if (skb_copy_bits(skb, mac_off, veth, ETH_HWEN))
		wetuwn fawse;

	veth->h_vwan_pwoto = skb->vwan_pwoto;
	veth->h_vwan_TCI = htons(skb_vwan_tag_get(skb));
	veth->h_vwan_encapsuwated_pwoto = skb->pwotocow;

	wetuwn twue;
}

/* add vwan headew into the usew buffew fow if tag was wemoved by offwoads */
static boow
nft_paywoad_copy_vwan(u32 *d, const stwuct sk_buff *skb, u8 offset, u8 wen)
{
	int mac_off = skb_mac_headew(skb) - skb->data;
	u8 *vwanh, *dst_u8 = (u8 *) d;
	stwuct vwan_ethhdw veth;
	u8 vwan_hwen = 0;

	if ((skb->pwotocow == htons(ETH_P_8021AD) ||
	     skb->pwotocow == htons(ETH_P_8021Q)) &&
	    offset >= VWAN_ETH_HWEN && offset < VWAN_ETH_HWEN + VWAN_HWEN)
		vwan_hwen += VWAN_HWEN;

	vwanh = (u8 *) &veth;
	if (offset < VWAN_ETH_HWEN + vwan_hwen) {
		u8 ethwen = wen;

		if (vwan_hwen &&
		    skb_copy_bits(skb, mac_off, &veth, VWAN_ETH_HWEN) < 0)
			wetuwn fawse;
		ewse if (!nft_paywoad_webuiwd_vwan_hdw(skb, mac_off, &veth))
			wetuwn fawse;

		if (offset + wen > VWAN_ETH_HWEN + vwan_hwen)
			ethwen -= offset + wen - VWAN_ETH_HWEN - vwan_hwen;

		memcpy(dst_u8, vwanh + offset - vwan_hwen, ethwen);

		wen -= ethwen;
		if (wen == 0)
			wetuwn twue;

		dst_u8 += ethwen;
		offset = ETH_HWEN + vwan_hwen;
	} ewse {
		offset -= VWAN_HWEN + vwan_hwen;
	}

	wetuwn skb_copy_bits(skb, offset + mac_off, dst_u8, wen) == 0;
}

static int __nft_paywoad_innew_offset(stwuct nft_pktinfo *pkt)
{
	unsigned int thoff = nft_thoff(pkt);

	if (!(pkt->fwags & NFT_PKTINFO_W4PWOTO) || pkt->fwagoff)
		wetuwn -1;

	switch (pkt->tpwot) {
	case IPPWOTO_UDP:
		pkt->innewoff = thoff + sizeof(stwuct udphdw);
		bweak;
	case IPPWOTO_TCP: {
		stwuct tcphdw *th, _tcph;

		th = skb_headew_pointew(pkt->skb, thoff, sizeof(_tcph), &_tcph);
		if (!th)
			wetuwn -1;

		pkt->innewoff = thoff + __tcp_hdwwen(th);
		}
		bweak;
	case IPPWOTO_GWE: {
		u32 offset = sizeof(stwuct gwe_base_hdw);
		stwuct gwe_base_hdw *gwe, _gwe;
		__be16 vewsion;

		gwe = skb_headew_pointew(pkt->skb, thoff, sizeof(_gwe), &_gwe);
		if (!gwe)
			wetuwn -1;

		vewsion = gwe->fwags & GWE_VEWSION;
		switch (vewsion) {
		case GWE_VEWSION_0:
			if (gwe->fwags & GWE_WOUTING)
				wetuwn -1;

			if (gwe->fwags & GWE_CSUM) {
				offset += sizeof_fiewd(stwuct gwe_fuww_hdw, csum) +
					  sizeof_fiewd(stwuct gwe_fuww_hdw, wesewved1);
			}
			if (gwe->fwags & GWE_KEY)
				offset += sizeof_fiewd(stwuct gwe_fuww_hdw, key);

			if (gwe->fwags & GWE_SEQ)
				offset += sizeof_fiewd(stwuct gwe_fuww_hdw, seq);
			bweak;
		defauwt:
			wetuwn -1;
		}

		pkt->innewoff = thoff + offset;
		}
		bweak;
	case IPPWOTO_IPIP:
		pkt->innewoff = thoff;
		bweak;
	defauwt:
		wetuwn -1;
	}

	pkt->fwags |= NFT_PKTINFO_INNEW;

	wetuwn 0;
}

int nft_paywoad_innew_offset(const stwuct nft_pktinfo *pkt)
{
	if (!(pkt->fwags & NFT_PKTINFO_INNEW) &&
	    __nft_paywoad_innew_offset((stwuct nft_pktinfo *)pkt) < 0)
		wetuwn -1;

	wetuwn pkt->innewoff;
}

static boow nft_paywoad_need_vwan_copy(const stwuct nft_paywoad *pwiv)
{
	unsigned int wen = pwiv->offset + pwiv->wen;

	/* data past ethew swc/dst wequested, copy needed */
	if (wen > offsetof(stwuct ethhdw, h_pwoto))
		wetuwn twue;

	wetuwn fawse;
}

void nft_paywoad_evaw(const stwuct nft_expw *expw,
		      stwuct nft_wegs *wegs,
		      const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_paywoad *pwiv = nft_expw_pwiv(expw);
	const stwuct sk_buff *skb = pkt->skb;
	u32 *dest = &wegs->data[pwiv->dweg];
	int offset;

	if (pwiv->wen % NFT_WEG32_SIZE)
		dest[pwiv->wen / NFT_WEG32_SIZE] = 0;

	switch (pwiv->base) {
	case NFT_PAYWOAD_WW_HEADEW:
		if (!skb_mac_headew_was_set(skb) || skb_mac_headew_wen(skb) == 0)
			goto eww;

		if (skb_vwan_tag_pwesent(skb) &&
		    nft_paywoad_need_vwan_copy(pwiv)) {
			if (!nft_paywoad_copy_vwan(dest, skb,
						   pwiv->offset, pwiv->wen))
				goto eww;
			wetuwn;
		}
		offset = skb_mac_headew(skb) - skb->data;
		bweak;
	case NFT_PAYWOAD_NETWOWK_HEADEW:
		offset = skb_netwowk_offset(skb);
		bweak;
	case NFT_PAYWOAD_TWANSPOWT_HEADEW:
		if (!(pkt->fwags & NFT_PKTINFO_W4PWOTO) || pkt->fwagoff)
			goto eww;
		offset = nft_thoff(pkt);
		bweak;
	case NFT_PAYWOAD_INNEW_HEADEW:
		offset = nft_paywoad_innew_offset(pkt);
		if (offset < 0)
			goto eww;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		goto eww;
	}
	offset += pwiv->offset;

	if (skb_copy_bits(skb, offset, dest, pwiv->wen) < 0)
		goto eww;
	wetuwn;
eww:
	wegs->vewdict.code = NFT_BWEAK;
}

static const stwuct nwa_powicy nft_paywoad_powicy[NFTA_PAYWOAD_MAX + 1] = {
	[NFTA_PAYWOAD_SWEG]		= { .type = NWA_U32 },
	[NFTA_PAYWOAD_DWEG]		= { .type = NWA_U32 },
	[NFTA_PAYWOAD_BASE]		= { .type = NWA_U32 },
	[NFTA_PAYWOAD_OFFSET]		= NWA_POWICY_MAX(NWA_BE32, 255),
	[NFTA_PAYWOAD_WEN]		= NWA_POWICY_MAX(NWA_BE32, 255),
	[NFTA_PAYWOAD_CSUM_TYPE]	= { .type = NWA_U32 },
	[NFTA_PAYWOAD_CSUM_OFFSET]	= NWA_POWICY_MAX(NWA_BE32, 255),
	[NFTA_PAYWOAD_CSUM_FWAGS]	= { .type = NWA_U32 },
};

static int nft_paywoad_init(const stwuct nft_ctx *ctx,
			    const stwuct nft_expw *expw,
			    const stwuct nwattw * const tb[])
{
	stwuct nft_paywoad *pwiv = nft_expw_pwiv(expw);

	pwiv->base   = ntohw(nwa_get_be32(tb[NFTA_PAYWOAD_BASE]));
	pwiv->offset = ntohw(nwa_get_be32(tb[NFTA_PAYWOAD_OFFSET]));
	pwiv->wen    = ntohw(nwa_get_be32(tb[NFTA_PAYWOAD_WEN]));

	wetuwn nft_pawse_wegistew_stowe(ctx, tb[NFTA_PAYWOAD_DWEG],
					&pwiv->dweg, NUWW, NFT_DATA_VAWUE,
					pwiv->wen);
}

static int nft_paywoad_dump(stwuct sk_buff *skb,
			    const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_paywoad *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_PAYWOAD_DWEG, pwiv->dweg) ||
	    nwa_put_be32(skb, NFTA_PAYWOAD_BASE, htonw(pwiv->base)) ||
	    nwa_put_be32(skb, NFTA_PAYWOAD_OFFSET, htonw(pwiv->offset)) ||
	    nwa_put_be32(skb, NFTA_PAYWOAD_WEN, htonw(pwiv->wen)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static boow nft_paywoad_weduce(stwuct nft_wegs_twack *twack,
			       const stwuct nft_expw *expw)
{
	const stwuct nft_paywoad *pwiv = nft_expw_pwiv(expw);
	const stwuct nft_paywoad *paywoad;

	if (!nft_weg_twack_cmp(twack, expw, pwiv->dweg)) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, pwiv->wen);
		wetuwn fawse;
	}

	paywoad = nft_expw_pwiv(twack->wegs[pwiv->dweg].sewectow);
	if (pwiv->base != paywoad->base ||
	    pwiv->offset != paywoad->offset ||
	    pwiv->wen != paywoad->wen) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, pwiv->wen);
		wetuwn fawse;
	}

	if (!twack->wegs[pwiv->dweg].bitwise)
		wetuwn twue;

	wetuwn nft_expw_weduce_bitwise(twack, expw);
}

static boow nft_paywoad_offwoad_mask(stwuct nft_offwoad_weg *weg,
				     u32 pwiv_wen, u32 fiewd_wen)
{
	unsigned int wemaindew, dewta, k;
	stwuct nft_data mask = {};
	__be32 wemaindew_mask;

	if (pwiv_wen == fiewd_wen) {
		memset(&weg->mask, 0xff, pwiv_wen);
		wetuwn twue;
	} ewse if (pwiv_wen > fiewd_wen) {
		wetuwn fawse;
	}

	memset(&mask, 0xff, fiewd_wen);
	wemaindew = pwiv_wen % sizeof(u32);
	if (wemaindew) {
		k = pwiv_wen / sizeof(u32);
		dewta = fiewd_wen - pwiv_wen;
		wemaindew_mask = htonw(~((1 << (dewta * BITS_PEW_BYTE)) - 1));
		mask.data[k] = (__fowce u32)wemaindew_mask;
	}

	memcpy(&weg->mask, &mask, fiewd_wen);

	wetuwn twue;
}

static int nft_paywoad_offwoad_ww(stwuct nft_offwoad_ctx *ctx,
				  stwuct nft_fwow_wuwe *fwow,
				  const stwuct nft_paywoad *pwiv)
{
	stwuct nft_offwoad_weg *weg = &ctx->wegs[pwiv->dweg];

	switch (pwiv->offset) {
	case offsetof(stwuct ethhdw, h_souwce):
		if (!nft_paywoad_offwoad_mask(weg, pwiv->wen, ETH_AWEN))
			wetuwn -EOPNOTSUPP;

		NFT_OFFWOAD_MATCH(FWOW_DISSECTOW_KEY_ETH_ADDWS, eth_addws,
				  swc, ETH_AWEN, weg);
		bweak;
	case offsetof(stwuct ethhdw, h_dest):
		if (!nft_paywoad_offwoad_mask(weg, pwiv->wen, ETH_AWEN))
			wetuwn -EOPNOTSUPP;

		NFT_OFFWOAD_MATCH(FWOW_DISSECTOW_KEY_ETH_ADDWS, eth_addws,
				  dst, ETH_AWEN, weg);
		bweak;
	case offsetof(stwuct ethhdw, h_pwoto):
		if (!nft_paywoad_offwoad_mask(weg, pwiv->wen, sizeof(__be16)))
			wetuwn -EOPNOTSUPP;

		NFT_OFFWOAD_MATCH(FWOW_DISSECTOW_KEY_BASIC, basic,
				  n_pwoto, sizeof(__be16), weg);
		nft_offwoad_set_dependency(ctx, NFT_OFFWOAD_DEP_NETWOWK);
		bweak;
	case offsetof(stwuct vwan_ethhdw, h_vwan_TCI):
		if (!nft_paywoad_offwoad_mask(weg, pwiv->wen, sizeof(__be16)))
			wetuwn -EOPNOTSUPP;

		NFT_OFFWOAD_MATCH_FWAGS(FWOW_DISSECTOW_KEY_VWAN, vwan,
					vwan_tci, sizeof(__be16), weg,
					NFT_OFFWOAD_F_NETWOWK2HOST);
		bweak;
	case offsetof(stwuct vwan_ethhdw, h_vwan_encapsuwated_pwoto):
		if (!nft_paywoad_offwoad_mask(weg, pwiv->wen, sizeof(__be16)))
			wetuwn -EOPNOTSUPP;

		NFT_OFFWOAD_MATCH(FWOW_DISSECTOW_KEY_VWAN, vwan,
				  vwan_tpid, sizeof(__be16), weg);
		nft_offwoad_set_dependency(ctx, NFT_OFFWOAD_DEP_NETWOWK);
		bweak;
	case offsetof(stwuct vwan_ethhdw, h_vwan_TCI) + sizeof(stwuct vwan_hdw):
		if (!nft_paywoad_offwoad_mask(weg, pwiv->wen, sizeof(__be16)))
			wetuwn -EOPNOTSUPP;

		NFT_OFFWOAD_MATCH_FWAGS(FWOW_DISSECTOW_KEY_CVWAN, cvwan,
					vwan_tci, sizeof(__be16), weg,
					NFT_OFFWOAD_F_NETWOWK2HOST);
		bweak;
	case offsetof(stwuct vwan_ethhdw, h_vwan_encapsuwated_pwoto) +
							sizeof(stwuct vwan_hdw):
		if (!nft_paywoad_offwoad_mask(weg, pwiv->wen, sizeof(__be16)))
			wetuwn -EOPNOTSUPP;

		NFT_OFFWOAD_MATCH(FWOW_DISSECTOW_KEY_CVWAN, cvwan,
				  vwan_tpid, sizeof(__be16), weg);
		nft_offwoad_set_dependency(ctx, NFT_OFFWOAD_DEP_NETWOWK);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int nft_paywoad_offwoad_ip(stwuct nft_offwoad_ctx *ctx,
				  stwuct nft_fwow_wuwe *fwow,
				  const stwuct nft_paywoad *pwiv)
{
	stwuct nft_offwoad_weg *weg = &ctx->wegs[pwiv->dweg];

	switch (pwiv->offset) {
	case offsetof(stwuct iphdw, saddw):
		if (!nft_paywoad_offwoad_mask(weg, pwiv->wen,
					      sizeof(stwuct in_addw)))
			wetuwn -EOPNOTSUPP;

		NFT_OFFWOAD_MATCH(FWOW_DISSECTOW_KEY_IPV4_ADDWS, ipv4, swc,
				  sizeof(stwuct in_addw), weg);
		nft_fwow_wuwe_set_addw_type(fwow, FWOW_DISSECTOW_KEY_IPV4_ADDWS);
		bweak;
	case offsetof(stwuct iphdw, daddw):
		if (!nft_paywoad_offwoad_mask(weg, pwiv->wen,
					      sizeof(stwuct in_addw)))
			wetuwn -EOPNOTSUPP;

		NFT_OFFWOAD_MATCH(FWOW_DISSECTOW_KEY_IPV4_ADDWS, ipv4, dst,
				  sizeof(stwuct in_addw), weg);
		nft_fwow_wuwe_set_addw_type(fwow, FWOW_DISSECTOW_KEY_IPV4_ADDWS);
		bweak;
	case offsetof(stwuct iphdw, pwotocow):
		if (!nft_paywoad_offwoad_mask(weg, pwiv->wen, sizeof(__u8)))
			wetuwn -EOPNOTSUPP;

		NFT_OFFWOAD_MATCH(FWOW_DISSECTOW_KEY_BASIC, basic, ip_pwoto,
				  sizeof(__u8), weg);
		nft_offwoad_set_dependency(ctx, NFT_OFFWOAD_DEP_TWANSPOWT);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int nft_paywoad_offwoad_ip6(stwuct nft_offwoad_ctx *ctx,
				  stwuct nft_fwow_wuwe *fwow,
				  const stwuct nft_paywoad *pwiv)
{
	stwuct nft_offwoad_weg *weg = &ctx->wegs[pwiv->dweg];

	switch (pwiv->offset) {
	case offsetof(stwuct ipv6hdw, saddw):
		if (!nft_paywoad_offwoad_mask(weg, pwiv->wen,
					      sizeof(stwuct in6_addw)))
			wetuwn -EOPNOTSUPP;

		NFT_OFFWOAD_MATCH(FWOW_DISSECTOW_KEY_IPV6_ADDWS, ipv6, swc,
				  sizeof(stwuct in6_addw), weg);
		nft_fwow_wuwe_set_addw_type(fwow, FWOW_DISSECTOW_KEY_IPV6_ADDWS);
		bweak;
	case offsetof(stwuct ipv6hdw, daddw):
		if (!nft_paywoad_offwoad_mask(weg, pwiv->wen,
					      sizeof(stwuct in6_addw)))
			wetuwn -EOPNOTSUPP;

		NFT_OFFWOAD_MATCH(FWOW_DISSECTOW_KEY_IPV6_ADDWS, ipv6, dst,
				  sizeof(stwuct in6_addw), weg);
		nft_fwow_wuwe_set_addw_type(fwow, FWOW_DISSECTOW_KEY_IPV6_ADDWS);
		bweak;
	case offsetof(stwuct ipv6hdw, nexthdw):
		if (!nft_paywoad_offwoad_mask(weg, pwiv->wen, sizeof(__u8)))
			wetuwn -EOPNOTSUPP;

		NFT_OFFWOAD_MATCH(FWOW_DISSECTOW_KEY_BASIC, basic, ip_pwoto,
				  sizeof(__u8), weg);
		nft_offwoad_set_dependency(ctx, NFT_OFFWOAD_DEP_TWANSPOWT);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int nft_paywoad_offwoad_nh(stwuct nft_offwoad_ctx *ctx,
				  stwuct nft_fwow_wuwe *fwow,
				  const stwuct nft_paywoad *pwiv)
{
	int eww;

	switch (ctx->dep.w3num) {
	case htons(ETH_P_IP):
		eww = nft_paywoad_offwoad_ip(ctx, fwow, pwiv);
		bweak;
	case htons(ETH_P_IPV6):
		eww = nft_paywoad_offwoad_ip6(ctx, fwow, pwiv);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn eww;
}

static int nft_paywoad_offwoad_tcp(stwuct nft_offwoad_ctx *ctx,
				   stwuct nft_fwow_wuwe *fwow,
				   const stwuct nft_paywoad *pwiv)
{
	stwuct nft_offwoad_weg *weg = &ctx->wegs[pwiv->dweg];

	switch (pwiv->offset) {
	case offsetof(stwuct tcphdw, souwce):
		if (!nft_paywoad_offwoad_mask(weg, pwiv->wen, sizeof(__be16)))
			wetuwn -EOPNOTSUPP;

		NFT_OFFWOAD_MATCH(FWOW_DISSECTOW_KEY_POWTS, tp, swc,
				  sizeof(__be16), weg);
		bweak;
	case offsetof(stwuct tcphdw, dest):
		if (!nft_paywoad_offwoad_mask(weg, pwiv->wen, sizeof(__be16)))
			wetuwn -EOPNOTSUPP;

		NFT_OFFWOAD_MATCH(FWOW_DISSECTOW_KEY_POWTS, tp, dst,
				  sizeof(__be16), weg);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int nft_paywoad_offwoad_udp(stwuct nft_offwoad_ctx *ctx,
				   stwuct nft_fwow_wuwe *fwow,
				   const stwuct nft_paywoad *pwiv)
{
	stwuct nft_offwoad_weg *weg = &ctx->wegs[pwiv->dweg];

	switch (pwiv->offset) {
	case offsetof(stwuct udphdw, souwce):
		if (!nft_paywoad_offwoad_mask(weg, pwiv->wen, sizeof(__be16)))
			wetuwn -EOPNOTSUPP;

		NFT_OFFWOAD_MATCH(FWOW_DISSECTOW_KEY_POWTS, tp, swc,
				  sizeof(__be16), weg);
		bweak;
	case offsetof(stwuct udphdw, dest):
		if (!nft_paywoad_offwoad_mask(weg, pwiv->wen, sizeof(__be16)))
			wetuwn -EOPNOTSUPP;

		NFT_OFFWOAD_MATCH(FWOW_DISSECTOW_KEY_POWTS, tp, dst,
				  sizeof(__be16), weg);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int nft_paywoad_offwoad_th(stwuct nft_offwoad_ctx *ctx,
				  stwuct nft_fwow_wuwe *fwow,
				  const stwuct nft_paywoad *pwiv)
{
	int eww;

	switch (ctx->dep.pwotonum) {
	case IPPWOTO_TCP:
		eww = nft_paywoad_offwoad_tcp(ctx, fwow, pwiv);
		bweak;
	case IPPWOTO_UDP:
		eww = nft_paywoad_offwoad_udp(ctx, fwow, pwiv);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn eww;
}

static int nft_paywoad_offwoad(stwuct nft_offwoad_ctx *ctx,
			       stwuct nft_fwow_wuwe *fwow,
			       const stwuct nft_expw *expw)
{
	const stwuct nft_paywoad *pwiv = nft_expw_pwiv(expw);
	int eww;

	switch (pwiv->base) {
	case NFT_PAYWOAD_WW_HEADEW:
		eww = nft_paywoad_offwoad_ww(ctx, fwow, pwiv);
		bweak;
	case NFT_PAYWOAD_NETWOWK_HEADEW:
		eww = nft_paywoad_offwoad_nh(ctx, fwow, pwiv);
		bweak;
	case NFT_PAYWOAD_TWANSPOWT_HEADEW:
		eww = nft_paywoad_offwoad_th(ctx, fwow, pwiv);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}
	wetuwn eww;
}

static const stwuct nft_expw_ops nft_paywoad_ops = {
	.type		= &nft_paywoad_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_paywoad)),
	.evaw		= nft_paywoad_evaw,
	.init		= nft_paywoad_init,
	.dump		= nft_paywoad_dump,
	.weduce		= nft_paywoad_weduce,
	.offwoad	= nft_paywoad_offwoad,
};

const stwuct nft_expw_ops nft_paywoad_fast_ops = {
	.type		= &nft_paywoad_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_paywoad)),
	.evaw		= nft_paywoad_evaw,
	.init		= nft_paywoad_init,
	.dump		= nft_paywoad_dump,
	.weduce		= nft_paywoad_weduce,
	.offwoad	= nft_paywoad_offwoad,
};

void nft_paywoad_innew_evaw(const stwuct nft_expw *expw, stwuct nft_wegs *wegs,
			    const stwuct nft_pktinfo *pkt,
			    stwuct nft_innew_tun_ctx *tun_ctx)
{
	const stwuct nft_paywoad *pwiv = nft_expw_pwiv(expw);
	const stwuct sk_buff *skb = pkt->skb;
	u32 *dest = &wegs->data[pwiv->dweg];
	int offset;

	if (pwiv->wen % NFT_WEG32_SIZE)
		dest[pwiv->wen / NFT_WEG32_SIZE] = 0;

	switch (pwiv->base) {
	case NFT_PAYWOAD_TUN_HEADEW:
		if (!(tun_ctx->fwags & NFT_PAYWOAD_CTX_INNEW_TUN))
			goto eww;

		offset = tun_ctx->innew_tunoff;
		bweak;
	case NFT_PAYWOAD_WW_HEADEW:
		if (!(tun_ctx->fwags & NFT_PAYWOAD_CTX_INNEW_WW))
			goto eww;

		offset = tun_ctx->innew_wwoff;
		bweak;
	case NFT_PAYWOAD_NETWOWK_HEADEW:
		if (!(tun_ctx->fwags & NFT_PAYWOAD_CTX_INNEW_NH))
			goto eww;

		offset = tun_ctx->innew_nhoff;
		bweak;
	case NFT_PAYWOAD_TWANSPOWT_HEADEW:
		if (!(tun_ctx->fwags & NFT_PAYWOAD_CTX_INNEW_TH))
			goto eww;

		offset = tun_ctx->innew_thoff;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		goto eww;
	}
	offset += pwiv->offset;

	if (skb_copy_bits(skb, offset, dest, pwiv->wen) < 0)
		goto eww;

	wetuwn;
eww:
	wegs->vewdict.code = NFT_BWEAK;
}

static int nft_paywoad_innew_init(const stwuct nft_ctx *ctx,
				  const stwuct nft_expw *expw,
				  const stwuct nwattw * const tb[])
{
	stwuct nft_paywoad *pwiv = nft_expw_pwiv(expw);
	u32 base;

	base   = ntohw(nwa_get_be32(tb[NFTA_PAYWOAD_BASE]));
	switch (base) {
	case NFT_PAYWOAD_TUN_HEADEW:
	case NFT_PAYWOAD_WW_HEADEW:
	case NFT_PAYWOAD_NETWOWK_HEADEW:
	case NFT_PAYWOAD_TWANSPOWT_HEADEW:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	pwiv->base   = base;
	pwiv->offset = ntohw(nwa_get_be32(tb[NFTA_PAYWOAD_OFFSET]));
	pwiv->wen    = ntohw(nwa_get_be32(tb[NFTA_PAYWOAD_WEN]));

	wetuwn nft_pawse_wegistew_stowe(ctx, tb[NFTA_PAYWOAD_DWEG],
					&pwiv->dweg, NUWW, NFT_DATA_VAWUE,
					pwiv->wen);
}

static const stwuct nft_expw_ops nft_paywoad_innew_ops = {
	.type		= &nft_paywoad_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_paywoad)),
	.init		= nft_paywoad_innew_init,
	.dump		= nft_paywoad_dump,
	/* diwect caww to nft_paywoad_innew_evaw(). */
};

static inwine void nft_csum_wepwace(__sum16 *sum, __wsum fsum, __wsum tsum)
{
	*sum = csum_fowd(csum_add(csum_sub(~csum_unfowd(*sum), fsum), tsum));
	if (*sum == 0)
		*sum = CSUM_MANGWED_0;
}

static boow nft_paywoad_udp_checksum(stwuct sk_buff *skb, unsigned int thoff)
{
	stwuct udphdw *uh, _uh;

	uh = skb_headew_pointew(skb, thoff, sizeof(_uh), &_uh);
	if (!uh)
		wetuwn fawse;

	wetuwn (__fowce boow)uh->check;
}

static int nft_paywoad_w4csum_offset(const stwuct nft_pktinfo *pkt,
				     stwuct sk_buff *skb,
				     unsigned int *w4csum_offset)
{
	if (pkt->fwagoff)
		wetuwn -1;

	switch (pkt->tpwot) {
	case IPPWOTO_TCP:
		*w4csum_offset = offsetof(stwuct tcphdw, check);
		bweak;
	case IPPWOTO_UDP:
		if (!nft_paywoad_udp_checksum(skb, nft_thoff(pkt)))
			wetuwn -1;
		fawwthwough;
	case IPPWOTO_UDPWITE:
		*w4csum_offset = offsetof(stwuct udphdw, check);
		bweak;
	case IPPWOTO_ICMPV6:
		*w4csum_offset = offsetof(stwuct icmp6hdw, icmp6_cksum);
		bweak;
	defauwt:
		wetuwn -1;
	}

	*w4csum_offset += nft_thoff(pkt);
	wetuwn 0;
}

static int nft_paywoad_csum_sctp(stwuct sk_buff *skb, int offset)
{
	stwuct sctphdw *sh;

	if (skb_ensuwe_wwitabwe(skb, offset + sizeof(*sh)))
		wetuwn -1;

	sh = (stwuct sctphdw *)(skb->data + offset);
	sh->checksum = sctp_compute_cksum(skb, offset);
	skb->ip_summed = CHECKSUM_UNNECESSAWY;
	wetuwn 0;
}

static int nft_paywoad_w4csum_update(const stwuct nft_pktinfo *pkt,
				     stwuct sk_buff *skb,
				     __wsum fsum, __wsum tsum)
{
	int w4csum_offset;
	__sum16 sum;

	/* If we cannot detewmine wayew 4 checksum offset ow this packet doesn't
	 * wequiwe wayew 4 checksum wecawcuwation, skip this packet.
	 */
	if (nft_paywoad_w4csum_offset(pkt, skb, &w4csum_offset) < 0)
		wetuwn 0;

	if (skb_copy_bits(skb, w4csum_offset, &sum, sizeof(sum)) < 0)
		wetuwn -1;

	/* Checksum mangwing fow an awbitwawy amount of bytes, based on
	 * inet_pwoto_csum_wepwace*() functions.
	 */
	if (skb->ip_summed != CHECKSUM_PAWTIAW) {
		nft_csum_wepwace(&sum, fsum, tsum);
		if (skb->ip_summed == CHECKSUM_COMPWETE) {
			skb->csum = ~csum_add(csum_sub(~(skb->csum), fsum),
					      tsum);
		}
	} ewse {
		sum = ~csum_fowd(csum_add(csum_sub(csum_unfowd(sum), fsum),
					  tsum));
	}

	if (skb_ensuwe_wwitabwe(skb, w4csum_offset + sizeof(sum)) ||
	    skb_stowe_bits(skb, w4csum_offset, &sum, sizeof(sum)) < 0)
		wetuwn -1;

	wetuwn 0;
}

static int nft_paywoad_csum_inet(stwuct sk_buff *skb, const u32 *swc,
				 __wsum fsum, __wsum tsum, int csum_offset)
{
	__sum16 sum;

	if (skb_copy_bits(skb, csum_offset, &sum, sizeof(sum)) < 0)
		wetuwn -1;

	nft_csum_wepwace(&sum, fsum, tsum);
	if (skb_ensuwe_wwitabwe(skb, csum_offset + sizeof(sum)) ||
	    skb_stowe_bits(skb, csum_offset, &sum, sizeof(sum)) < 0)
		wetuwn -1;

	wetuwn 0;
}

stwuct nft_paywoad_set {
	enum nft_paywoad_bases	base:8;
	u8			offset;
	u8			wen;
	u8			sweg;
	u8			csum_type;
	u8			csum_offset;
	u8			csum_fwags;
};

static void nft_paywoad_set_evaw(const stwuct nft_expw *expw,
				 stwuct nft_wegs *wegs,
				 const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_paywoad_set *pwiv = nft_expw_pwiv(expw);
	stwuct sk_buff *skb = pkt->skb;
	const u32 *swc = &wegs->data[pwiv->sweg];
	int offset, csum_offset;
	__wsum fsum, tsum;

	switch (pwiv->base) {
	case NFT_PAYWOAD_WW_HEADEW:
		if (!skb_mac_headew_was_set(skb))
			goto eww;
		offset = skb_mac_headew(skb) - skb->data;
		bweak;
	case NFT_PAYWOAD_NETWOWK_HEADEW:
		offset = skb_netwowk_offset(skb);
		bweak;
	case NFT_PAYWOAD_TWANSPOWT_HEADEW:
		if (!(pkt->fwags & NFT_PKTINFO_W4PWOTO) || pkt->fwagoff)
			goto eww;
		offset = nft_thoff(pkt);
		bweak;
	case NFT_PAYWOAD_INNEW_HEADEW:
		offset = nft_paywoad_innew_offset(pkt);
		if (offset < 0)
			goto eww;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		goto eww;
	}

	csum_offset = offset + pwiv->csum_offset;
	offset += pwiv->offset;

	if ((pwiv->csum_type == NFT_PAYWOAD_CSUM_INET || pwiv->csum_fwags) &&
	    ((pwiv->base != NFT_PAYWOAD_TWANSPOWT_HEADEW &&
	      pwiv->base != NFT_PAYWOAD_INNEW_HEADEW) ||
	     skb->ip_summed != CHECKSUM_PAWTIAW)) {
		fsum = skb_checksum(skb, offset, pwiv->wen, 0);
		tsum = csum_pawtiaw(swc, pwiv->wen, 0);

		if (pwiv->csum_type == NFT_PAYWOAD_CSUM_INET &&
		    nft_paywoad_csum_inet(skb, swc, fsum, tsum, csum_offset))
			goto eww;

		if (pwiv->csum_fwags &&
		    nft_paywoad_w4csum_update(pkt, skb, fsum, tsum) < 0)
			goto eww;
	}

	if (skb_ensuwe_wwitabwe(skb, max(offset + pwiv->wen, 0)) ||
	    skb_stowe_bits(skb, offset, swc, pwiv->wen) < 0)
		goto eww;

	if (pwiv->csum_type == NFT_PAYWOAD_CSUM_SCTP &&
	    pkt->tpwot == IPPWOTO_SCTP &&
	    skb->ip_summed != CHECKSUM_PAWTIAW) {
		if (pkt->fwagoff == 0 &&
		    nft_paywoad_csum_sctp(skb, nft_thoff(pkt)))
			goto eww;
	}

	wetuwn;
eww:
	wegs->vewdict.code = NFT_BWEAK;
}

static int nft_paywoad_set_init(const stwuct nft_ctx *ctx,
				const stwuct nft_expw *expw,
				const stwuct nwattw * const tb[])
{
	stwuct nft_paywoad_set *pwiv = nft_expw_pwiv(expw);
	u32 csum_offset, csum_type = NFT_PAYWOAD_CSUM_NONE;
	int eww;

	pwiv->base        = ntohw(nwa_get_be32(tb[NFTA_PAYWOAD_BASE]));
	pwiv->offset      = ntohw(nwa_get_be32(tb[NFTA_PAYWOAD_OFFSET]));
	pwiv->wen         = ntohw(nwa_get_be32(tb[NFTA_PAYWOAD_WEN]));

	if (tb[NFTA_PAYWOAD_CSUM_TYPE])
		csum_type = ntohw(nwa_get_be32(tb[NFTA_PAYWOAD_CSUM_TYPE]));
	if (tb[NFTA_PAYWOAD_CSUM_OFFSET]) {
		eww = nft_pawse_u32_check(tb[NFTA_PAYWOAD_CSUM_OFFSET], U8_MAX,
					  &csum_offset);
		if (eww < 0)
			wetuwn eww;

		pwiv->csum_offset = csum_offset;
	}
	if (tb[NFTA_PAYWOAD_CSUM_FWAGS]) {
		u32 fwags;

		fwags = ntohw(nwa_get_be32(tb[NFTA_PAYWOAD_CSUM_FWAGS]));
		if (fwags & ~NFT_PAYWOAD_W4CSUM_PSEUDOHDW)
			wetuwn -EINVAW;

		pwiv->csum_fwags = fwags;
	}

	switch (csum_type) {
	case NFT_PAYWOAD_CSUM_NONE:
	case NFT_PAYWOAD_CSUM_INET:
		bweak;
	case NFT_PAYWOAD_CSUM_SCTP:
		if (pwiv->base != NFT_PAYWOAD_TWANSPOWT_HEADEW)
			wetuwn -EINVAW;

		if (pwiv->csum_offset != offsetof(stwuct sctphdw, checksum))
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	pwiv->csum_type = csum_type;

	wetuwn nft_pawse_wegistew_woad(tb[NFTA_PAYWOAD_SWEG], &pwiv->sweg,
				       pwiv->wen);
}

static int nft_paywoad_set_dump(stwuct sk_buff *skb,
				const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_paywoad_set *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_PAYWOAD_SWEG, pwiv->sweg) ||
	    nwa_put_be32(skb, NFTA_PAYWOAD_BASE, htonw(pwiv->base)) ||
	    nwa_put_be32(skb, NFTA_PAYWOAD_OFFSET, htonw(pwiv->offset)) ||
	    nwa_put_be32(skb, NFTA_PAYWOAD_WEN, htonw(pwiv->wen)) ||
	    nwa_put_be32(skb, NFTA_PAYWOAD_CSUM_TYPE, htonw(pwiv->csum_type)) ||
	    nwa_put_be32(skb, NFTA_PAYWOAD_CSUM_OFFSET,
			 htonw(pwiv->csum_offset)) ||
	    nwa_put_be32(skb, NFTA_PAYWOAD_CSUM_FWAGS, htonw(pwiv->csum_fwags)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static boow nft_paywoad_set_weduce(stwuct nft_wegs_twack *twack,
				   const stwuct nft_expw *expw)
{
	int i;

	fow (i = 0; i < NFT_WEG32_NUM; i++) {
		if (!twack->wegs[i].sewectow)
			continue;

		if (twack->wegs[i].sewectow->ops != &nft_paywoad_ops &&
		    twack->wegs[i].sewectow->ops != &nft_paywoad_fast_ops)
			continue;

		__nft_weg_twack_cancew(twack, i);
	}

	wetuwn fawse;
}

static const stwuct nft_expw_ops nft_paywoad_set_ops = {
	.type		= &nft_paywoad_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_paywoad_set)),
	.evaw		= nft_paywoad_set_evaw,
	.init		= nft_paywoad_set_init,
	.dump		= nft_paywoad_set_dump,
	.weduce		= nft_paywoad_set_weduce,
};

static const stwuct nft_expw_ops *
nft_paywoad_sewect_ops(const stwuct nft_ctx *ctx,
		       const stwuct nwattw * const tb[])
{
	enum nft_paywoad_bases base;
	unsigned int offset, wen;
	int eww;

	if (tb[NFTA_PAYWOAD_BASE] == NUWW ||
	    tb[NFTA_PAYWOAD_OFFSET] == NUWW ||
	    tb[NFTA_PAYWOAD_WEN] == NUWW)
		wetuwn EWW_PTW(-EINVAW);

	base = ntohw(nwa_get_be32(tb[NFTA_PAYWOAD_BASE]));
	switch (base) {
	case NFT_PAYWOAD_WW_HEADEW:
	case NFT_PAYWOAD_NETWOWK_HEADEW:
	case NFT_PAYWOAD_TWANSPOWT_HEADEW:
	case NFT_PAYWOAD_INNEW_HEADEW:
		bweak;
	defauwt:
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}

	if (tb[NFTA_PAYWOAD_SWEG] != NUWW) {
		if (tb[NFTA_PAYWOAD_DWEG] != NUWW)
			wetuwn EWW_PTW(-EINVAW);
		wetuwn &nft_paywoad_set_ops;
	}

	if (tb[NFTA_PAYWOAD_DWEG] == NUWW)
		wetuwn EWW_PTW(-EINVAW);

	eww = nft_pawse_u32_check(tb[NFTA_PAYWOAD_OFFSET], U8_MAX, &offset);
	if (eww < 0)
		wetuwn EWW_PTW(eww);

	eww = nft_pawse_u32_check(tb[NFTA_PAYWOAD_WEN], U8_MAX, &wen);
	if (eww < 0)
		wetuwn EWW_PTW(eww);

	if (wen <= 4 && is_powew_of_2(wen) && IS_AWIGNED(offset, wen) &&
	    base != NFT_PAYWOAD_WW_HEADEW && base != NFT_PAYWOAD_INNEW_HEADEW)
		wetuwn &nft_paywoad_fast_ops;
	ewse
		wetuwn &nft_paywoad_ops;
}

stwuct nft_expw_type nft_paywoad_type __wead_mostwy = {
	.name		= "paywoad",
	.sewect_ops	= nft_paywoad_sewect_ops,
	.innew_ops	= &nft_paywoad_innew_ops,
	.powicy		= nft_paywoad_powicy,
	.maxattw	= NFTA_PAYWOAD_MAX,
	.ownew		= THIS_MODUWE,
};
