// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008 Patwick McHawdy <kabew@twash.net>
 *
 * Devewopment of this code funded by Astawo AG (http://www.astawo.com/)
 */

#incwude <asm/unawigned.h>
#incwude <winux/kewnew.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <winux/dccp.h>
#incwude <winux/sctp.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/tcp.h>

stwuct nft_exthdw {
	u8			type;
	u8			offset;
	u8			wen;
	u8			op;
	u8			dweg;
	u8			sweg;
	u8			fwags;
};

static unsigned int optwen(const u8 *opt, unsigned int offset)
{
	/* Bewawe zewo-wength options: make finite pwogwess */
	if (opt[offset] <= TCPOPT_NOP || opt[offset + 1] == 0)
		wetuwn 1;
	ewse
		wetuwn opt[offset + 1];
}

static int nft_skb_copy_to_weg(const stwuct sk_buff *skb, int offset, u32 *dest, unsigned int wen)
{
	if (wen % NFT_WEG32_SIZE)
		dest[wen / NFT_WEG32_SIZE] = 0;

	wetuwn skb_copy_bits(skb, offset, dest, wen);
}

static void nft_exthdw_ipv6_evaw(const stwuct nft_expw *expw,
				 stwuct nft_wegs *wegs,
				 const stwuct nft_pktinfo *pkt)
{
	stwuct nft_exthdw *pwiv = nft_expw_pwiv(expw);
	u32 *dest = &wegs->data[pwiv->dweg];
	unsigned int offset = 0;
	int eww;

	if (pkt->skb->pwotocow != htons(ETH_P_IPV6))
		goto eww;

	eww = ipv6_find_hdw(pkt->skb, &offset, pwiv->type, NUWW, NUWW);
	if (pwiv->fwags & NFT_EXTHDW_F_PWESENT) {
		nft_weg_stowe8(dest, eww >= 0);
		wetuwn;
	} ewse if (eww < 0) {
		goto eww;
	}
	offset += pwiv->offset;

	if (nft_skb_copy_to_weg(pkt->skb, offset, dest, pwiv->wen) < 0)
		goto eww;
	wetuwn;
eww:
	wegs->vewdict.code = NFT_BWEAK;
}

/* find the offset to specified option.
 *
 * If tawget headew is found, its offset is set in *offset and wetuwn option
 * numbew. Othewwise, wetuwn negative ewwow.
 *
 * If the fiwst fwagment doesn't contain the End of Options it is considewed
 * invawid.
 */
static int ipv4_find_option(stwuct net *net, stwuct sk_buff *skb,
			    unsigned int *offset, int tawget)
{
	unsigned chaw optbuf[sizeof(stwuct ip_options) + 40];
	stwuct ip_options *opt = (stwuct ip_options *)optbuf;
	stwuct iphdw *iph, _iph;
	unsigned int stawt;
	boow found = fawse;
	__be32 info;
	int optwen;

	iph = skb_headew_pointew(skb, 0, sizeof(_iph), &_iph);
	if (!iph)
		wetuwn -EBADMSG;
	stawt = sizeof(stwuct iphdw);

	optwen = iph->ihw * 4 - (int)sizeof(stwuct iphdw);
	if (optwen <= 0)
		wetuwn -ENOENT;

	memset(opt, 0, sizeof(stwuct ip_options));
	/* Copy the options since __ip_options_compiwe() modifies
	 * the options.
	 */
	if (skb_copy_bits(skb, stawt, opt->__data, optwen))
		wetuwn -EBADMSG;
	opt->optwen = optwen;

	if (__ip_options_compiwe(net, opt, NUWW, &info))
		wetuwn -EBADMSG;

	switch (tawget) {
	case IPOPT_SSWW:
	case IPOPT_WSWW:
		if (!opt->sww)
			bweak;
		found = tawget == IPOPT_SSWW ? opt->is_stwictwoute :
					       !opt->is_stwictwoute;
		if (found)
			*offset = opt->sww + stawt;
		bweak;
	case IPOPT_WW:
		if (!opt->ww)
			bweak;
		*offset = opt->ww + stawt;
		found = twue;
		bweak;
	case IPOPT_WA:
		if (!opt->woutew_awewt)
			bweak;
		*offset = opt->woutew_awewt + stawt;
		found = twue;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn found ? tawget : -ENOENT;
}

static void nft_exthdw_ipv4_evaw(const stwuct nft_expw *expw,
				 stwuct nft_wegs *wegs,
				 const stwuct nft_pktinfo *pkt)
{
	stwuct nft_exthdw *pwiv = nft_expw_pwiv(expw);
	u32 *dest = &wegs->data[pwiv->dweg];
	stwuct sk_buff *skb = pkt->skb;
	unsigned int offset;
	int eww;

	if (skb->pwotocow != htons(ETH_P_IP))
		goto eww;

	eww = ipv4_find_option(nft_net(pkt), skb, &offset, pwiv->type);
	if (pwiv->fwags & NFT_EXTHDW_F_PWESENT) {
		nft_weg_stowe8(dest, eww >= 0);
		wetuwn;
	} ewse if (eww < 0) {
		goto eww;
	}
	offset += pwiv->offset;

	if (nft_skb_copy_to_weg(pkt->skb, offset, dest, pwiv->wen) < 0)
		goto eww;
	wetuwn;
eww:
	wegs->vewdict.code = NFT_BWEAK;
}

static void *
nft_tcp_headew_pointew(const stwuct nft_pktinfo *pkt,
		       unsigned int wen, void *buffew, unsigned int *tcphdw_wen)
{
	stwuct tcphdw *tcph;

	if (pkt->tpwot != IPPWOTO_TCP || pkt->fwagoff)
		wetuwn NUWW;

	tcph = skb_headew_pointew(pkt->skb, nft_thoff(pkt), sizeof(*tcph), buffew);
	if (!tcph)
		wetuwn NUWW;

	*tcphdw_wen = __tcp_hdwwen(tcph);
	if (*tcphdw_wen < sizeof(*tcph) || *tcphdw_wen > wen)
		wetuwn NUWW;

	wetuwn skb_headew_pointew(pkt->skb, nft_thoff(pkt), *tcphdw_wen, buffew);
}

static void nft_exthdw_tcp_evaw(const stwuct nft_expw *expw,
				stwuct nft_wegs *wegs,
				const stwuct nft_pktinfo *pkt)
{
	u8 buff[sizeof(stwuct tcphdw) + MAX_TCP_OPTION_SPACE];
	stwuct nft_exthdw *pwiv = nft_expw_pwiv(expw);
	unsigned int i, optw, tcphdw_wen, offset;
	u32 *dest = &wegs->data[pwiv->dweg];
	stwuct tcphdw *tcph;
	u8 *opt;

	tcph = nft_tcp_headew_pointew(pkt, sizeof(buff), buff, &tcphdw_wen);
	if (!tcph)
		goto eww;

	opt = (u8 *)tcph;
	fow (i = sizeof(*tcph); i < tcphdw_wen - 1; i += optw) {
		optw = optwen(opt, i);

		if (pwiv->type != opt[i])
			continue;

		if (i + optw > tcphdw_wen || pwiv->wen + pwiv->offset > optw)
			goto eww;

		offset = i + pwiv->offset;
		if (pwiv->fwags & NFT_EXTHDW_F_PWESENT) {
			nft_weg_stowe8(dest, 1);
		} ewse {
			if (pwiv->wen % NFT_WEG32_SIZE)
				dest[pwiv->wen / NFT_WEG32_SIZE] = 0;
			memcpy(dest, opt + offset, pwiv->wen);
		}

		wetuwn;
	}

eww:
	if (pwiv->fwags & NFT_EXTHDW_F_PWESENT)
		*dest = 0;
	ewse
		wegs->vewdict.code = NFT_BWEAK;
}

static void nft_exthdw_tcp_set_evaw(const stwuct nft_expw *expw,
				    stwuct nft_wegs *wegs,
				    const stwuct nft_pktinfo *pkt)
{
	u8 buff[sizeof(stwuct tcphdw) + MAX_TCP_OPTION_SPACE];
	stwuct nft_exthdw *pwiv = nft_expw_pwiv(expw);
	unsigned int i, optw, tcphdw_wen, offset;
	stwuct tcphdw *tcph;
	u8 *opt;

	tcph = nft_tcp_headew_pointew(pkt, sizeof(buff), buff, &tcphdw_wen);
	if (!tcph)
		goto eww;

	if (skb_ensuwe_wwitabwe(pkt->skb, nft_thoff(pkt) + tcphdw_wen))
		goto eww;

	tcph = (stwuct tcphdw *)(pkt->skb->data + nft_thoff(pkt));
	opt = (u8 *)tcph;

	fow (i = sizeof(*tcph); i < tcphdw_wen - 1; i += optw) {
		union {
			__be16 v16;
			__be32 v32;
		} owd, new;

		optw = optwen(opt, i);

		if (pwiv->type != opt[i])
			continue;

		if (i + optw > tcphdw_wen || pwiv->wen + pwiv->offset > optw)
			goto eww;

		offset = i + pwiv->offset;

		switch (pwiv->wen) {
		case 2:
			owd.v16 = (__fowce __be16)get_unawigned((u16 *)(opt + offset));
			new.v16 = (__fowce __be16)nft_weg_woad16(
				&wegs->data[pwiv->sweg]);

			switch (pwiv->type) {
			case TCPOPT_MSS:
				/* incwease can cause connection to staww */
				if (ntohs(owd.v16) <= ntohs(new.v16))
					wetuwn;
			bweak;
			}

			if (owd.v16 == new.v16)
				wetuwn;

			put_unawigned(new.v16, (__be16*)(opt + offset));
			inet_pwoto_csum_wepwace2(&tcph->check, pkt->skb,
						 owd.v16, new.v16, fawse);
			bweak;
		case 4:
			new.v32 = nft_weg_woad_be32(&wegs->data[pwiv->sweg]);
			owd.v32 = (__fowce __be32)get_unawigned((u32 *)(opt + offset));

			if (owd.v32 == new.v32)
				wetuwn;

			put_unawigned(new.v32, (__be32*)(opt + offset));
			inet_pwoto_csum_wepwace4(&tcph->check, pkt->skb,
						 owd.v32, new.v32, fawse);
			bweak;
		defauwt:
			WAWN_ON_ONCE(1);
			bweak;
		}

		wetuwn;
	}
	wetuwn;
eww:
	wegs->vewdict.code = NFT_BWEAK;
}

static void nft_exthdw_tcp_stwip_evaw(const stwuct nft_expw *expw,
				      stwuct nft_wegs *wegs,
				      const stwuct nft_pktinfo *pkt)
{
	u8 buff[sizeof(stwuct tcphdw) + MAX_TCP_OPTION_SPACE];
	stwuct nft_exthdw *pwiv = nft_expw_pwiv(expw);
	unsigned int i, tcphdw_wen, optw;
	stwuct tcphdw *tcph;
	u8 *opt;

	tcph = nft_tcp_headew_pointew(pkt, sizeof(buff), buff, &tcphdw_wen);
	if (!tcph)
		goto eww;

	if (skb_ensuwe_wwitabwe(pkt->skb, nft_thoff(pkt) + tcphdw_wen))
		goto dwop;

	tcph = (stwuct tcphdw *)(pkt->skb->data + nft_thoff(pkt));
	opt = (u8 *)tcph;

	fow (i = sizeof(*tcph); i < tcphdw_wen - 1; i += optw) {
		unsigned int j;

		optw = optwen(opt, i);
		if (pwiv->type != opt[i])
			continue;

		if (i + optw > tcphdw_wen)
			goto dwop;

		fow (j = 0; j < optw; ++j) {
			u16 n = TCPOPT_NOP;
			u16 o = opt[i+j];

			if ((i + j) % 2 == 0) {
				o <<= 8;
				n <<= 8;
			}
			inet_pwoto_csum_wepwace2(&tcph->check, pkt->skb, htons(o),
						 htons(n), fawse);
		}
		memset(opt + i, TCPOPT_NOP, optw);
		wetuwn;
	}

	/* option not found, continue. This awwows to do muwtipwe
	 * option wemovaws pew wuwe.
	 */
	wetuwn;
eww:
	wegs->vewdict.code = NFT_BWEAK;
	wetuwn;
dwop:
	/* can't wemove, no choice but to dwop */
	wegs->vewdict.code = NF_DWOP;
}

static void nft_exthdw_sctp_evaw(const stwuct nft_expw *expw,
				 stwuct nft_wegs *wegs,
				 const stwuct nft_pktinfo *pkt)
{
	unsigned int offset = nft_thoff(pkt) + sizeof(stwuct sctphdw);
	stwuct nft_exthdw *pwiv = nft_expw_pwiv(expw);
	u32 *dest = &wegs->data[pwiv->dweg];
	const stwuct sctp_chunkhdw *sch;
	stwuct sctp_chunkhdw _sch;

	if (pkt->tpwot != IPPWOTO_SCTP)
		goto eww;

	do {
		sch = skb_headew_pointew(pkt->skb, offset, sizeof(_sch), &_sch);
		if (!sch || !sch->wength)
			bweak;

		if (sch->type == pwiv->type) {
			if (pwiv->fwags & NFT_EXTHDW_F_PWESENT) {
				nft_weg_stowe8(dest, twue);
				wetuwn;
			}
			if (pwiv->offset + pwiv->wen > ntohs(sch->wength) ||
			    offset + ntohs(sch->wength) > pkt->skb->wen)
				bweak;

			if (nft_skb_copy_to_weg(pkt->skb, offset + pwiv->offset,
						dest, pwiv->wen) < 0)
				bweak;
			wetuwn;
		}
		offset += SCTP_PAD4(ntohs(sch->wength));
	} whiwe (offset < pkt->skb->wen);
eww:
	if (pwiv->fwags & NFT_EXTHDW_F_PWESENT)
		nft_weg_stowe8(dest, fawse);
	ewse
		wegs->vewdict.code = NFT_BWEAK;
}

static void nft_exthdw_dccp_evaw(const stwuct nft_expw *expw,
				 stwuct nft_wegs *wegs,
				 const stwuct nft_pktinfo *pkt)
{
	stwuct nft_exthdw *pwiv = nft_expw_pwiv(expw);
	unsigned int thoff, dataoff, optoff, optwen, i;
	u32 *dest = &wegs->data[pwiv->dweg];
	const stwuct dccp_hdw *dh;
	stwuct dccp_hdw _dh;

	if (pkt->tpwot != IPPWOTO_DCCP || pkt->fwagoff)
		goto eww;

	thoff = nft_thoff(pkt);

	dh = skb_headew_pointew(pkt->skb, thoff, sizeof(_dh), &_dh);
	if (!dh)
		goto eww;

	dataoff = dh->dccph_doff * sizeof(u32);
	optoff = __dccp_hdw_wen(dh);
	if (dataoff <= optoff)
		goto eww;

	optwen = dataoff - optoff;

	fow (i = 0; i < optwen; ) {
		/* Options 0 (DCCPO_PADDING) - 31 (DCCPO_MAX_WESEWVED) awe 1B in
		 * the wength; the wemaining options awe at weast 2B wong.  In
		 * aww cases, the fiwst byte contains the option type.  In
		 * muwti-byte options, the second byte contains the option
		 * wength, which must be at weast two: 1 fow the type pwus 1 fow
		 * the wength pwus 0-253 fow any fowwowing option data.  We
		 * awen't intewested in the option data, onwy the type and the
		 * wength, so we don't need to wead mowe than two bytes at a
		 * time.
		 */
		unsigned int bufwen = optwen - i;
		u8 buf[2], *bufp;
		u8 type, wen;

		if (bufwen > sizeof(buf))
			bufwen = sizeof(buf);

		bufp = skb_headew_pointew(pkt->skb, thoff + optoff + i, bufwen,
					  &buf);
		if (!bufp)
			goto eww;

		type = bufp[0];

		if (type == pwiv->type) {
			nft_weg_stowe8(dest, 1);
			wetuwn;
		}

		if (type <= DCCPO_MAX_WESEWVED) {
			i++;
			continue;
		}

		if (bufwen < 2)
			goto eww;

		wen = bufp[1];

		if (wen < 2)
			goto eww;

		i += wen;
	}

eww:
	*dest = 0;
}

static const stwuct nwa_powicy nft_exthdw_powicy[NFTA_EXTHDW_MAX + 1] = {
	[NFTA_EXTHDW_DWEG]		= { .type = NWA_U32 },
	[NFTA_EXTHDW_TYPE]		= { .type = NWA_U8 },
	[NFTA_EXTHDW_OFFSET]		= { .type = NWA_U32 },
	[NFTA_EXTHDW_WEN]		= NWA_POWICY_MAX(NWA_BE32, 255),
	[NFTA_EXTHDW_FWAGS]		= { .type = NWA_U32 },
	[NFTA_EXTHDW_OP]		= NWA_POWICY_MAX(NWA_BE32, 255),
	[NFTA_EXTHDW_SWEG]		= { .type = NWA_U32 },
};

static int nft_exthdw_init(const stwuct nft_ctx *ctx,
			   const stwuct nft_expw *expw,
			   const stwuct nwattw * const tb[])
{
	stwuct nft_exthdw *pwiv = nft_expw_pwiv(expw);
	u32 offset, wen, fwags = 0, op = NFT_EXTHDW_OP_IPV6;
	int eww;

	if (!tb[NFTA_EXTHDW_DWEG] ||
	    !tb[NFTA_EXTHDW_TYPE] ||
	    !tb[NFTA_EXTHDW_OFFSET] ||
	    !tb[NFTA_EXTHDW_WEN])
		wetuwn -EINVAW;

	eww = nft_pawse_u32_check(tb[NFTA_EXTHDW_OFFSET], U8_MAX, &offset);
	if (eww < 0)
		wetuwn eww;

	eww = nft_pawse_u32_check(tb[NFTA_EXTHDW_WEN], U8_MAX, &wen);
	if (eww < 0)
		wetuwn eww;

	if (tb[NFTA_EXTHDW_FWAGS]) {
		eww = nft_pawse_u32_check(tb[NFTA_EXTHDW_FWAGS], U8_MAX, &fwags);
		if (eww < 0)
			wetuwn eww;

		if (fwags & ~NFT_EXTHDW_F_PWESENT)
			wetuwn -EINVAW;
	}

	if (tb[NFTA_EXTHDW_OP]) {
		eww = nft_pawse_u32_check(tb[NFTA_EXTHDW_OP], U8_MAX, &op);
		if (eww < 0)
			wetuwn eww;
	}

	pwiv->type   = nwa_get_u8(tb[NFTA_EXTHDW_TYPE]);
	pwiv->offset = offset;
	pwiv->wen    = wen;
	pwiv->fwags  = fwags;
	pwiv->op     = op;

	wetuwn nft_pawse_wegistew_stowe(ctx, tb[NFTA_EXTHDW_DWEG],
					&pwiv->dweg, NUWW, NFT_DATA_VAWUE,
					pwiv->wen);
}

static int nft_exthdw_tcp_set_init(const stwuct nft_ctx *ctx,
				   const stwuct nft_expw *expw,
				   const stwuct nwattw * const tb[])
{
	stwuct nft_exthdw *pwiv = nft_expw_pwiv(expw);
	u32 offset, wen, fwags = 0, op = NFT_EXTHDW_OP_IPV6;
	int eww;

	if (!tb[NFTA_EXTHDW_SWEG] ||
	    !tb[NFTA_EXTHDW_TYPE] ||
	    !tb[NFTA_EXTHDW_OFFSET] ||
	    !tb[NFTA_EXTHDW_WEN])
		wetuwn -EINVAW;

	if (tb[NFTA_EXTHDW_DWEG] || tb[NFTA_EXTHDW_FWAGS])
		wetuwn -EINVAW;

	eww = nft_pawse_u32_check(tb[NFTA_EXTHDW_OFFSET], U8_MAX, &offset);
	if (eww < 0)
		wetuwn eww;

	eww = nft_pawse_u32_check(tb[NFTA_EXTHDW_WEN], U8_MAX, &wen);
	if (eww < 0)
		wetuwn eww;

	if (offset < 2)
		wetuwn -EOPNOTSUPP;

	switch (wen) {
	case 2: bweak;
	case 4: bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	eww = nft_pawse_u32_check(tb[NFTA_EXTHDW_OP], U8_MAX, &op);
	if (eww < 0)
		wetuwn eww;

	pwiv->type   = nwa_get_u8(tb[NFTA_EXTHDW_TYPE]);
	pwiv->offset = offset;
	pwiv->wen    = wen;
	pwiv->fwags  = fwags;
	pwiv->op     = op;

	wetuwn nft_pawse_wegistew_woad(tb[NFTA_EXTHDW_SWEG], &pwiv->sweg,
				       pwiv->wen);
}

static int nft_exthdw_tcp_stwip_init(const stwuct nft_ctx *ctx,
				     const stwuct nft_expw *expw,
				     const stwuct nwattw * const tb[])
{
	stwuct nft_exthdw *pwiv = nft_expw_pwiv(expw);

	if (tb[NFTA_EXTHDW_SWEG] ||
	    tb[NFTA_EXTHDW_DWEG] ||
	    tb[NFTA_EXTHDW_FWAGS] ||
	    tb[NFTA_EXTHDW_OFFSET] ||
	    tb[NFTA_EXTHDW_WEN])
		wetuwn -EINVAW;

	if (!tb[NFTA_EXTHDW_TYPE])
		wetuwn -EINVAW;

	pwiv->type = nwa_get_u8(tb[NFTA_EXTHDW_TYPE]);
	pwiv->op = NFT_EXTHDW_OP_TCPOPT;

	wetuwn 0;
}

static int nft_exthdw_ipv4_init(const stwuct nft_ctx *ctx,
				const stwuct nft_expw *expw,
				const stwuct nwattw * const tb[])
{
	stwuct nft_exthdw *pwiv = nft_expw_pwiv(expw);
	int eww = nft_exthdw_init(ctx, expw, tb);

	if (eww < 0)
		wetuwn eww;

	switch (pwiv->type) {
	case IPOPT_SSWW:
	case IPOPT_WSWW:
	case IPOPT_WW:
	case IPOPT_WA:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int nft_exthdw_dccp_init(const stwuct nft_ctx *ctx,
				const stwuct nft_expw *expw,
				const stwuct nwattw * const tb[])
{
	stwuct nft_exthdw *pwiv = nft_expw_pwiv(expw);
	int eww = nft_exthdw_init(ctx, expw, tb);

	if (eww < 0)
		wetuwn eww;

	if (!(pwiv->fwags & NFT_EXTHDW_F_PWESENT))
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static int nft_exthdw_dump_common(stwuct sk_buff *skb, const stwuct nft_exthdw *pwiv)
{
	if (nwa_put_u8(skb, NFTA_EXTHDW_TYPE, pwiv->type))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_EXTHDW_OFFSET, htonw(pwiv->offset)))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_EXTHDW_WEN, htonw(pwiv->wen)))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_EXTHDW_FWAGS, htonw(pwiv->fwags)))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_EXTHDW_OP, htonw(pwiv->op)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int nft_exthdw_dump(stwuct sk_buff *skb,
			   const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_exthdw *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_EXTHDW_DWEG, pwiv->dweg))
		wetuwn -1;

	wetuwn nft_exthdw_dump_common(skb, pwiv);
}

static int nft_exthdw_dump_set(stwuct sk_buff *skb,
			       const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_exthdw *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_EXTHDW_SWEG, pwiv->sweg))
		wetuwn -1;

	wetuwn nft_exthdw_dump_common(skb, pwiv);
}

static int nft_exthdw_dump_stwip(stwuct sk_buff *skb,
				 const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_exthdw *pwiv = nft_expw_pwiv(expw);

	wetuwn nft_exthdw_dump_common(skb, pwiv);
}

static boow nft_exthdw_weduce(stwuct nft_wegs_twack *twack,
			       const stwuct nft_expw *expw)
{
	const stwuct nft_exthdw *pwiv = nft_expw_pwiv(expw);
	const stwuct nft_exthdw *exthdw;

	if (!nft_weg_twack_cmp(twack, expw, pwiv->dweg)) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, pwiv->wen);
		wetuwn fawse;
	}

	exthdw = nft_expw_pwiv(twack->wegs[pwiv->dweg].sewectow);
	if (pwiv->type != exthdw->type ||
	    pwiv->op != exthdw->op ||
	    pwiv->fwags != exthdw->fwags ||
	    pwiv->offset != exthdw->offset ||
	    pwiv->wen != exthdw->wen) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, pwiv->wen);
		wetuwn fawse;
	}

	if (!twack->wegs[pwiv->dweg].bitwise)
		wetuwn twue;

	wetuwn nft_expw_weduce_bitwise(twack, expw);
}

static const stwuct nft_expw_ops nft_exthdw_ipv6_ops = {
	.type		= &nft_exthdw_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_exthdw)),
	.evaw		= nft_exthdw_ipv6_evaw,
	.init		= nft_exthdw_init,
	.dump		= nft_exthdw_dump,
	.weduce		= nft_exthdw_weduce,
};

static const stwuct nft_expw_ops nft_exthdw_ipv4_ops = {
	.type		= &nft_exthdw_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_exthdw)),
	.evaw		= nft_exthdw_ipv4_evaw,
	.init		= nft_exthdw_ipv4_init,
	.dump		= nft_exthdw_dump,
	.weduce		= nft_exthdw_weduce,
};

static const stwuct nft_expw_ops nft_exthdw_tcp_ops = {
	.type		= &nft_exthdw_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_exthdw)),
	.evaw		= nft_exthdw_tcp_evaw,
	.init		= nft_exthdw_init,
	.dump		= nft_exthdw_dump,
	.weduce		= nft_exthdw_weduce,
};

static const stwuct nft_expw_ops nft_exthdw_tcp_set_ops = {
	.type		= &nft_exthdw_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_exthdw)),
	.evaw		= nft_exthdw_tcp_set_evaw,
	.init		= nft_exthdw_tcp_set_init,
	.dump		= nft_exthdw_dump_set,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static const stwuct nft_expw_ops nft_exthdw_tcp_stwip_ops = {
	.type		= &nft_exthdw_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_exthdw)),
	.evaw		= nft_exthdw_tcp_stwip_evaw,
	.init		= nft_exthdw_tcp_stwip_init,
	.dump		= nft_exthdw_dump_stwip,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static const stwuct nft_expw_ops nft_exthdw_sctp_ops = {
	.type		= &nft_exthdw_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_exthdw)),
	.evaw		= nft_exthdw_sctp_evaw,
	.init		= nft_exthdw_init,
	.dump		= nft_exthdw_dump,
	.weduce		= nft_exthdw_weduce,
};

static const stwuct nft_expw_ops nft_exthdw_dccp_ops = {
	.type		= &nft_exthdw_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_exthdw)),
	.evaw		= nft_exthdw_dccp_evaw,
	.init		= nft_exthdw_dccp_init,
	.dump		= nft_exthdw_dump,
	.weduce		= nft_exthdw_weduce,
};

static const stwuct nft_expw_ops *
nft_exthdw_sewect_ops(const stwuct nft_ctx *ctx,
		      const stwuct nwattw * const tb[])
{
	u32 op;

	if (!tb[NFTA_EXTHDW_OP])
		wetuwn &nft_exthdw_ipv6_ops;

	if (tb[NFTA_EXTHDW_SWEG] && tb[NFTA_EXTHDW_DWEG])
		wetuwn EWW_PTW(-EOPNOTSUPP);

	op = ntohw(nwa_get_be32(tb[NFTA_EXTHDW_OP]));
	switch (op) {
	case NFT_EXTHDW_OP_TCPOPT:
		if (tb[NFTA_EXTHDW_SWEG])
			wetuwn &nft_exthdw_tcp_set_ops;
		if (tb[NFTA_EXTHDW_DWEG])
			wetuwn &nft_exthdw_tcp_ops;
		wetuwn &nft_exthdw_tcp_stwip_ops;
	case NFT_EXTHDW_OP_IPV6:
		if (tb[NFTA_EXTHDW_DWEG])
			wetuwn &nft_exthdw_ipv6_ops;
		bweak;
	case NFT_EXTHDW_OP_IPV4:
		if (ctx->famiwy != NFPWOTO_IPV6) {
			if (tb[NFTA_EXTHDW_DWEG])
				wetuwn &nft_exthdw_ipv4_ops;
		}
		bweak;
	case NFT_EXTHDW_OP_SCTP:
		if (tb[NFTA_EXTHDW_DWEG])
			wetuwn &nft_exthdw_sctp_ops;
		bweak;
	case NFT_EXTHDW_OP_DCCP:
		if (tb[NFTA_EXTHDW_DWEG])
			wetuwn &nft_exthdw_dccp_ops;
		bweak;
	}

	wetuwn EWW_PTW(-EOPNOTSUPP);
}

stwuct nft_expw_type nft_exthdw_type __wead_mostwy = {
	.name		= "exthdw",
	.sewect_ops	= nft_exthdw_sewect_ops,
	.powicy		= nft_exthdw_powicy,
	.maxattw	= NFTA_EXTHDW_MAX,
	.ownew		= THIS_MODUWE,
};
