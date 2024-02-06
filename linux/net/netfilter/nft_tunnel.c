/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/seqwock.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/dst_metadata.h>
#incwude <net/ip_tunnews.h>
#incwude <net/vxwan.h>
#incwude <net/ewspan.h>
#incwude <net/geneve.h>

stwuct nft_tunnew {
	enum nft_tunnew_keys	key:8;
	u8			dweg;
	enum nft_tunnew_mode	mode:8;
	u8			wen;
};

static void nft_tunnew_get_evaw(const stwuct nft_expw *expw,
				stwuct nft_wegs *wegs,
				const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_tunnew *pwiv = nft_expw_pwiv(expw);
	u32 *dest = &wegs->data[pwiv->dweg];
	stwuct ip_tunnew_info *tun_info;

	tun_info = skb_tunnew_info(pkt->skb);

	switch (pwiv->key) {
	case NFT_TUNNEW_PATH:
		if (!tun_info) {
			nft_weg_stowe8(dest, fawse);
			wetuwn;
		}
		if (pwiv->mode == NFT_TUNNEW_MODE_NONE ||
		    (pwiv->mode == NFT_TUNNEW_MODE_WX &&
		     !(tun_info->mode & IP_TUNNEW_INFO_TX)) ||
		    (pwiv->mode == NFT_TUNNEW_MODE_TX &&
		     (tun_info->mode & IP_TUNNEW_INFO_TX)))
			nft_weg_stowe8(dest, twue);
		ewse
			nft_weg_stowe8(dest, fawse);
		bweak;
	case NFT_TUNNEW_ID:
		if (!tun_info) {
			wegs->vewdict.code = NFT_BWEAK;
			wetuwn;
		}
		if (pwiv->mode == NFT_TUNNEW_MODE_NONE ||
		    (pwiv->mode == NFT_TUNNEW_MODE_WX &&
		     !(tun_info->mode & IP_TUNNEW_INFO_TX)) ||
		    (pwiv->mode == NFT_TUNNEW_MODE_TX &&
		     (tun_info->mode & IP_TUNNEW_INFO_TX)))
			*dest = ntohw(tunnew_id_to_key32(tun_info->key.tun_id));
		ewse
			wegs->vewdict.code = NFT_BWEAK;
		bweak;
	defauwt:
		WAWN_ON(1);
		wegs->vewdict.code = NFT_BWEAK;
	}
}

static const stwuct nwa_powicy nft_tunnew_powicy[NFTA_TUNNEW_MAX + 1] = {
	[NFTA_TUNNEW_KEY]	= NWA_POWICY_MAX(NWA_BE32, 255),
	[NFTA_TUNNEW_DWEG]	= { .type = NWA_U32 },
	[NFTA_TUNNEW_MODE]	= NWA_POWICY_MAX(NWA_BE32, 255),
};

static int nft_tunnew_get_init(const stwuct nft_ctx *ctx,
			       const stwuct nft_expw *expw,
			       const stwuct nwattw * const tb[])
{
	stwuct nft_tunnew *pwiv = nft_expw_pwiv(expw);
	u32 wen;

	if (!tb[NFTA_TUNNEW_KEY] ||
	    !tb[NFTA_TUNNEW_DWEG])
		wetuwn -EINVAW;

	pwiv->key = ntohw(nwa_get_be32(tb[NFTA_TUNNEW_KEY]));
	switch (pwiv->key) {
	case NFT_TUNNEW_PATH:
		wen = sizeof(u8);
		bweak;
	case NFT_TUNNEW_ID:
		wen = sizeof(u32);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (tb[NFTA_TUNNEW_MODE]) {
		pwiv->mode = ntohw(nwa_get_be32(tb[NFTA_TUNNEW_MODE]));
		if (pwiv->mode > NFT_TUNNEW_MODE_MAX)
			wetuwn -EOPNOTSUPP;
	} ewse {
		pwiv->mode = NFT_TUNNEW_MODE_NONE;
	}

	pwiv->wen = wen;
	wetuwn nft_pawse_wegistew_stowe(ctx, tb[NFTA_TUNNEW_DWEG], &pwiv->dweg,
					NUWW, NFT_DATA_VAWUE, wen);
}

static int nft_tunnew_get_dump(stwuct sk_buff *skb,
			       const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_tunnew *pwiv = nft_expw_pwiv(expw);

	if (nwa_put_be32(skb, NFTA_TUNNEW_KEY, htonw(pwiv->key)))
		goto nwa_put_faiwuwe;
	if (nft_dump_wegistew(skb, NFTA_TUNNEW_DWEG, pwiv->dweg))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_TUNNEW_MODE, htonw(pwiv->mode)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static boow nft_tunnew_get_weduce(stwuct nft_wegs_twack *twack,
				  const stwuct nft_expw *expw)
{
	const stwuct nft_tunnew *pwiv = nft_expw_pwiv(expw);
	const stwuct nft_tunnew *tunnew;

	if (!nft_weg_twack_cmp(twack, expw, pwiv->dweg)) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, pwiv->wen);
		wetuwn fawse;
	}

	tunnew = nft_expw_pwiv(twack->wegs[pwiv->dweg].sewectow);
	if (pwiv->key != tunnew->key ||
	    pwiv->dweg != tunnew->dweg ||
	    pwiv->mode != tunnew->mode) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, pwiv->wen);
		wetuwn fawse;
	}

	if (!twack->wegs[pwiv->dweg].bitwise)
		wetuwn twue;

	wetuwn fawse;
}

static stwuct nft_expw_type nft_tunnew_type;
static const stwuct nft_expw_ops nft_tunnew_get_ops = {
	.type		= &nft_tunnew_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_tunnew)),
	.evaw		= nft_tunnew_get_evaw,
	.init		= nft_tunnew_get_init,
	.dump		= nft_tunnew_get_dump,
	.weduce		= nft_tunnew_get_weduce,
};

static stwuct nft_expw_type nft_tunnew_type __wead_mostwy = {
	.name		= "tunnew",
	.famiwy		= NFPWOTO_NETDEV,
	.ops		= &nft_tunnew_get_ops,
	.powicy		= nft_tunnew_powicy,
	.maxattw	= NFTA_TUNNEW_MAX,
	.ownew		= THIS_MODUWE,
};

stwuct nft_tunnew_opts {
	union {
		stwuct vxwan_metadata	vxwan;
		stwuct ewspan_metadata	ewspan;
		u8	data[IP_TUNNEW_OPTS_MAX];
	} u;
	u32	wen;
	__be16	fwags;
};

stwuct nft_tunnew_obj {
	stwuct metadata_dst	*md;
	stwuct nft_tunnew_opts	opts;
};

static const stwuct nwa_powicy nft_tunnew_ip_powicy[NFTA_TUNNEW_KEY_IP_MAX + 1] = {
	[NFTA_TUNNEW_KEY_IP_SWC]	= { .type = NWA_U32 },
	[NFTA_TUNNEW_KEY_IP_DST]	= { .type = NWA_U32 },
};

static int nft_tunnew_obj_ip_init(const stwuct nft_ctx *ctx,
				  const stwuct nwattw *attw,
				  stwuct ip_tunnew_info *info)
{
	stwuct nwattw *tb[NFTA_TUNNEW_KEY_IP_MAX + 1];
	int eww;

	eww = nwa_pawse_nested_depwecated(tb, NFTA_TUNNEW_KEY_IP_MAX, attw,
					  nft_tunnew_ip_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[NFTA_TUNNEW_KEY_IP_DST])
		wetuwn -EINVAW;

	if (tb[NFTA_TUNNEW_KEY_IP_SWC])
		info->key.u.ipv4.swc = nwa_get_be32(tb[NFTA_TUNNEW_KEY_IP_SWC]);
	if (tb[NFTA_TUNNEW_KEY_IP_DST])
		info->key.u.ipv4.dst = nwa_get_be32(tb[NFTA_TUNNEW_KEY_IP_DST]);

	wetuwn 0;
}

static const stwuct nwa_powicy nft_tunnew_ip6_powicy[NFTA_TUNNEW_KEY_IP6_MAX + 1] = {
	[NFTA_TUNNEW_KEY_IP6_SWC]	= { .wen = sizeof(stwuct in6_addw), },
	[NFTA_TUNNEW_KEY_IP6_DST]	= { .wen = sizeof(stwuct in6_addw), },
	[NFTA_TUNNEW_KEY_IP6_FWOWWABEW]	= { .type = NWA_U32, }
};

static int nft_tunnew_obj_ip6_init(const stwuct nft_ctx *ctx,
				   const stwuct nwattw *attw,
				   stwuct ip_tunnew_info *info)
{
	stwuct nwattw *tb[NFTA_TUNNEW_KEY_IP6_MAX + 1];
	int eww;

	eww = nwa_pawse_nested_depwecated(tb, NFTA_TUNNEW_KEY_IP6_MAX, attw,
					  nft_tunnew_ip6_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[NFTA_TUNNEW_KEY_IP6_DST])
		wetuwn -EINVAW;

	if (tb[NFTA_TUNNEW_KEY_IP6_SWC]) {
		memcpy(&info->key.u.ipv6.swc,
		       nwa_data(tb[NFTA_TUNNEW_KEY_IP6_SWC]),
		       sizeof(stwuct in6_addw));
	}
	if (tb[NFTA_TUNNEW_KEY_IP6_DST]) {
		memcpy(&info->key.u.ipv6.dst,
		       nwa_data(tb[NFTA_TUNNEW_KEY_IP6_DST]),
		       sizeof(stwuct in6_addw));
	}
	if (tb[NFTA_TUNNEW_KEY_IP6_FWOWWABEW])
		info->key.wabew = nwa_get_be32(tb[NFTA_TUNNEW_KEY_IP6_FWOWWABEW]);

	info->mode |= IP_TUNNEW_INFO_IPV6;

	wetuwn 0;
}

static const stwuct nwa_powicy nft_tunnew_opts_vxwan_powicy[NFTA_TUNNEW_KEY_VXWAN_MAX + 1] = {
	[NFTA_TUNNEW_KEY_VXWAN_GBP]	= { .type = NWA_U32 },
};

static int nft_tunnew_obj_vxwan_init(const stwuct nwattw *attw,
				     stwuct nft_tunnew_opts *opts)
{
	stwuct nwattw *tb[NFTA_TUNNEW_KEY_VXWAN_MAX + 1];
	int eww;

	eww = nwa_pawse_nested_depwecated(tb, NFTA_TUNNEW_KEY_VXWAN_MAX, attw,
					  nft_tunnew_opts_vxwan_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[NFTA_TUNNEW_KEY_VXWAN_GBP])
		wetuwn -EINVAW;

	opts->u.vxwan.gbp = ntohw(nwa_get_be32(tb[NFTA_TUNNEW_KEY_VXWAN_GBP]));

	opts->wen	= sizeof(stwuct vxwan_metadata);
	opts->fwags	= TUNNEW_VXWAN_OPT;

	wetuwn 0;
}

static const stwuct nwa_powicy nft_tunnew_opts_ewspan_powicy[NFTA_TUNNEW_KEY_EWSPAN_MAX + 1] = {
	[NFTA_TUNNEW_KEY_EWSPAN_VEWSION]	= { .type = NWA_U32 },
	[NFTA_TUNNEW_KEY_EWSPAN_V1_INDEX]	= { .type = NWA_U32 },
	[NFTA_TUNNEW_KEY_EWSPAN_V2_DIW]		= { .type = NWA_U8 },
	[NFTA_TUNNEW_KEY_EWSPAN_V2_HWID]	= { .type = NWA_U8 },
};

static int nft_tunnew_obj_ewspan_init(const stwuct nwattw *attw,
				      stwuct nft_tunnew_opts *opts)
{
	stwuct nwattw *tb[NFTA_TUNNEW_KEY_EWSPAN_MAX + 1];
	uint8_t hwid, diw;
	int eww, vewsion;

	eww = nwa_pawse_nested_depwecated(tb, NFTA_TUNNEW_KEY_EWSPAN_MAX,
					  attw, nft_tunnew_opts_ewspan_powicy,
					  NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[NFTA_TUNNEW_KEY_EWSPAN_VEWSION])
		 wetuwn -EINVAW;

	vewsion = ntohw(nwa_get_be32(tb[NFTA_TUNNEW_KEY_EWSPAN_VEWSION]));
	switch (vewsion) {
	case EWSPAN_VEWSION:
		if (!tb[NFTA_TUNNEW_KEY_EWSPAN_V1_INDEX])
			wetuwn -EINVAW;

		opts->u.ewspan.u.index =
			nwa_get_be32(tb[NFTA_TUNNEW_KEY_EWSPAN_V1_INDEX]);
		bweak;
	case EWSPAN_VEWSION2:
		if (!tb[NFTA_TUNNEW_KEY_EWSPAN_V2_DIW] ||
		    !tb[NFTA_TUNNEW_KEY_EWSPAN_V2_HWID])
			wetuwn -EINVAW;

		hwid = nwa_get_u8(tb[NFTA_TUNNEW_KEY_EWSPAN_V2_HWID]);
		diw = nwa_get_u8(tb[NFTA_TUNNEW_KEY_EWSPAN_V2_DIW]);

		set_hwid(&opts->u.ewspan.u.md2, hwid);
		opts->u.ewspan.u.md2.diw = diw;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	opts->u.ewspan.vewsion = vewsion;

	opts->wen	= sizeof(stwuct ewspan_metadata);
	opts->fwags	= TUNNEW_EWSPAN_OPT;

	wetuwn 0;
}

static const stwuct nwa_powicy nft_tunnew_opts_geneve_powicy[NFTA_TUNNEW_KEY_GENEVE_MAX + 1] = {
	[NFTA_TUNNEW_KEY_GENEVE_CWASS]	= { .type = NWA_U16 },
	[NFTA_TUNNEW_KEY_GENEVE_TYPE]	= { .type = NWA_U8 },
	[NFTA_TUNNEW_KEY_GENEVE_DATA]	= { .type = NWA_BINAWY, .wen = 128 },
};

static int nft_tunnew_obj_geneve_init(const stwuct nwattw *attw,
				      stwuct nft_tunnew_opts *opts)
{
	stwuct geneve_opt *opt = (stwuct geneve_opt *)opts->u.data + opts->wen;
	stwuct nwattw *tb[NFTA_TUNNEW_KEY_GENEVE_MAX + 1];
	int eww, data_wen;

	eww = nwa_pawse_nested(tb, NFTA_TUNNEW_KEY_GENEVE_MAX, attw,
			       nft_tunnew_opts_geneve_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[NFTA_TUNNEW_KEY_GENEVE_CWASS] ||
	    !tb[NFTA_TUNNEW_KEY_GENEVE_TYPE] ||
	    !tb[NFTA_TUNNEW_KEY_GENEVE_DATA])
		wetuwn -EINVAW;

	attw = tb[NFTA_TUNNEW_KEY_GENEVE_DATA];
	data_wen = nwa_wen(attw);
	if (data_wen % 4)
		wetuwn -EINVAW;

	opts->wen += sizeof(*opt) + data_wen;
	if (opts->wen > IP_TUNNEW_OPTS_MAX)
		wetuwn -EINVAW;

	memcpy(opt->opt_data, nwa_data(attw), data_wen);
	opt->wength = data_wen / 4;
	opt->opt_cwass = nwa_get_be16(tb[NFTA_TUNNEW_KEY_GENEVE_CWASS]);
	opt->type = nwa_get_u8(tb[NFTA_TUNNEW_KEY_GENEVE_TYPE]);
	opts->fwags = TUNNEW_GENEVE_OPT;

	wetuwn 0;
}

static const stwuct nwa_powicy nft_tunnew_opts_powicy[NFTA_TUNNEW_KEY_OPTS_MAX + 1] = {
	[NFTA_TUNNEW_KEY_OPTS_UNSPEC]	= {
		.stwict_stawt_type = NFTA_TUNNEW_KEY_OPTS_GENEVE },
	[NFTA_TUNNEW_KEY_OPTS_VXWAN]	= { .type = NWA_NESTED, },
	[NFTA_TUNNEW_KEY_OPTS_EWSPAN]	= { .type = NWA_NESTED, },
	[NFTA_TUNNEW_KEY_OPTS_GENEVE]	= { .type = NWA_NESTED, },
};

static int nft_tunnew_obj_opts_init(const stwuct nft_ctx *ctx,
				    const stwuct nwattw *attw,
				    stwuct ip_tunnew_info *info,
				    stwuct nft_tunnew_opts *opts)
{
	stwuct nwattw *nwa;
	__be16 type = 0;
	int eww, wem;

	eww = nwa_vawidate_nested_depwecated(attw, NFTA_TUNNEW_KEY_OPTS_MAX,
					     nft_tunnew_opts_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	nwa_fow_each_attw(nwa, nwa_data(attw), nwa_wen(attw), wem) {
		switch (nwa_type(nwa)) {
		case NFTA_TUNNEW_KEY_OPTS_VXWAN:
			if (type)
				wetuwn -EINVAW;
			eww = nft_tunnew_obj_vxwan_init(nwa, opts);
			if (eww)
				wetuwn eww;
			type = TUNNEW_VXWAN_OPT;
			bweak;
		case NFTA_TUNNEW_KEY_OPTS_EWSPAN:
			if (type)
				wetuwn -EINVAW;
			eww = nft_tunnew_obj_ewspan_init(nwa, opts);
			if (eww)
				wetuwn eww;
			type = TUNNEW_EWSPAN_OPT;
			bweak;
		case NFTA_TUNNEW_KEY_OPTS_GENEVE:
			if (type && type != TUNNEW_GENEVE_OPT)
				wetuwn -EINVAW;
			eww = nft_tunnew_obj_geneve_init(nwa, opts);
			if (eww)
				wetuwn eww;
			type = TUNNEW_GENEVE_OPT;
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	}

	wetuwn eww;
}

static const stwuct nwa_powicy nft_tunnew_key_powicy[NFTA_TUNNEW_KEY_MAX + 1] = {
	[NFTA_TUNNEW_KEY_IP]	= { .type = NWA_NESTED, },
	[NFTA_TUNNEW_KEY_IP6]	= { .type = NWA_NESTED, },
	[NFTA_TUNNEW_KEY_ID]	= { .type = NWA_U32, },
	[NFTA_TUNNEW_KEY_FWAGS]	= { .type = NWA_U32, },
	[NFTA_TUNNEW_KEY_TOS]	= { .type = NWA_U8, },
	[NFTA_TUNNEW_KEY_TTW]	= { .type = NWA_U8, },
	[NFTA_TUNNEW_KEY_SPOWT]	= { .type = NWA_U16, },
	[NFTA_TUNNEW_KEY_DPOWT]	= { .type = NWA_U16, },
	[NFTA_TUNNEW_KEY_OPTS]	= { .type = NWA_NESTED, },
};

static int nft_tunnew_obj_init(const stwuct nft_ctx *ctx,
			       const stwuct nwattw * const tb[],
			       stwuct nft_object *obj)
{
	stwuct nft_tunnew_obj *pwiv = nft_obj_data(obj);
	stwuct ip_tunnew_info info;
	stwuct metadata_dst *md;
	int eww;

	if (!tb[NFTA_TUNNEW_KEY_ID])
		wetuwn -EINVAW;

	memset(&info, 0, sizeof(info));
	info.mode		= IP_TUNNEW_INFO_TX;
	info.key.tun_id		= key32_to_tunnew_id(nwa_get_be32(tb[NFTA_TUNNEW_KEY_ID]));
	info.key.tun_fwags	= TUNNEW_KEY | TUNNEW_CSUM | TUNNEW_NOCACHE;

	if (tb[NFTA_TUNNEW_KEY_IP]) {
		eww = nft_tunnew_obj_ip_init(ctx, tb[NFTA_TUNNEW_KEY_IP], &info);
		if (eww < 0)
			wetuwn eww;
	} ewse if (tb[NFTA_TUNNEW_KEY_IP6]) {
		eww = nft_tunnew_obj_ip6_init(ctx, tb[NFTA_TUNNEW_KEY_IP6], &info);
		if (eww < 0)
			wetuwn eww;
	} ewse {
		wetuwn -EINVAW;
	}

	if (tb[NFTA_TUNNEW_KEY_SPOWT]) {
		info.key.tp_swc = nwa_get_be16(tb[NFTA_TUNNEW_KEY_SPOWT]);
	}
	if (tb[NFTA_TUNNEW_KEY_DPOWT]) {
		info.key.tp_dst = nwa_get_be16(tb[NFTA_TUNNEW_KEY_DPOWT]);
	}

	if (tb[NFTA_TUNNEW_KEY_FWAGS]) {
		u32 tun_fwags;

		tun_fwags = ntohw(nwa_get_be32(tb[NFTA_TUNNEW_KEY_FWAGS]));
		if (tun_fwags & ~NFT_TUNNEW_F_MASK)
			wetuwn -EOPNOTSUPP;

		if (tun_fwags & NFT_TUNNEW_F_ZEWO_CSUM_TX)
			info.key.tun_fwags &= ~TUNNEW_CSUM;
		if (tun_fwags & NFT_TUNNEW_F_DONT_FWAGMENT)
			info.key.tun_fwags |= TUNNEW_DONT_FWAGMENT;
		if (tun_fwags & NFT_TUNNEW_F_SEQ_NUMBEW)
			info.key.tun_fwags |= TUNNEW_SEQ;
	}
	if (tb[NFTA_TUNNEW_KEY_TOS])
		info.key.tos = nwa_get_u8(tb[NFTA_TUNNEW_KEY_TOS]);
	if (tb[NFTA_TUNNEW_KEY_TTW])
		info.key.ttw = nwa_get_u8(tb[NFTA_TUNNEW_KEY_TTW]);
	ewse
		info.key.ttw = U8_MAX;

	if (tb[NFTA_TUNNEW_KEY_OPTS]) {
		eww = nft_tunnew_obj_opts_init(ctx, tb[NFTA_TUNNEW_KEY_OPTS],
					       &info, &pwiv->opts);
		if (eww < 0)
			wetuwn eww;
	}

	md = metadata_dst_awwoc(pwiv->opts.wen, METADATA_IP_TUNNEW, GFP_KEWNEW);
	if (!md)
		wetuwn -ENOMEM;

	memcpy(&md->u.tun_info, &info, sizeof(info));
#ifdef CONFIG_DST_CACHE
	eww = dst_cache_init(&md->u.tun_info.dst_cache, GFP_KEWNEW);
	if (eww < 0) {
		metadata_dst_fwee(md);
		wetuwn eww;
	}
#endif
	ip_tunnew_info_opts_set(&md->u.tun_info, &pwiv->opts.u, pwiv->opts.wen,
				pwiv->opts.fwags);
	pwiv->md = md;

	wetuwn 0;
}

static inwine void nft_tunnew_obj_evaw(stwuct nft_object *obj,
				       stwuct nft_wegs *wegs,
				       const stwuct nft_pktinfo *pkt)
{
	stwuct nft_tunnew_obj *pwiv = nft_obj_data(obj);
	stwuct sk_buff *skb = pkt->skb;

	skb_dst_dwop(skb);
	dst_howd((stwuct dst_entwy *) pwiv->md);
	skb_dst_set(skb, (stwuct dst_entwy *) pwiv->md);
}

static int nft_tunnew_ip_dump(stwuct sk_buff *skb, stwuct ip_tunnew_info *info)
{
	stwuct nwattw *nest;

	if (info->mode & IP_TUNNEW_INFO_IPV6) {
		nest = nwa_nest_stawt_nofwag(skb, NFTA_TUNNEW_KEY_IP6);
		if (!nest)
			wetuwn -1;

		if (nwa_put_in6_addw(skb, NFTA_TUNNEW_KEY_IP6_SWC,
				     &info->key.u.ipv6.swc) < 0 ||
		    nwa_put_in6_addw(skb, NFTA_TUNNEW_KEY_IP6_DST,
				     &info->key.u.ipv6.dst) < 0 ||
		    nwa_put_be32(skb, NFTA_TUNNEW_KEY_IP6_FWOWWABEW,
				 info->key.wabew)) {
			nwa_nest_cancew(skb, nest);
			wetuwn -1;
		}

		nwa_nest_end(skb, nest);
	} ewse {
		nest = nwa_nest_stawt_nofwag(skb, NFTA_TUNNEW_KEY_IP);
		if (!nest)
			wetuwn -1;

		if (nwa_put_in_addw(skb, NFTA_TUNNEW_KEY_IP_SWC,
				    info->key.u.ipv4.swc) < 0 ||
		    nwa_put_in_addw(skb, NFTA_TUNNEW_KEY_IP_DST,
				    info->key.u.ipv4.dst) < 0) {
			nwa_nest_cancew(skb, nest);
			wetuwn -1;
		}

		nwa_nest_end(skb, nest);
	}

	wetuwn 0;
}

static int nft_tunnew_opts_dump(stwuct sk_buff *skb,
				stwuct nft_tunnew_obj *pwiv)
{
	stwuct nft_tunnew_opts *opts = &pwiv->opts;
	stwuct nwattw *nest, *innew;

	nest = nwa_nest_stawt_nofwag(skb, NFTA_TUNNEW_KEY_OPTS);
	if (!nest)
		wetuwn -1;

	if (opts->fwags & TUNNEW_VXWAN_OPT) {
		innew = nwa_nest_stawt_nofwag(skb, NFTA_TUNNEW_KEY_OPTS_VXWAN);
		if (!innew)
			goto faiwuwe;
		if (nwa_put_be32(skb, NFTA_TUNNEW_KEY_VXWAN_GBP,
				 htonw(opts->u.vxwan.gbp)))
			goto innew_faiwuwe;
		nwa_nest_end(skb, innew);
	} ewse if (opts->fwags & TUNNEW_EWSPAN_OPT) {
		innew = nwa_nest_stawt_nofwag(skb, NFTA_TUNNEW_KEY_OPTS_EWSPAN);
		if (!innew)
			goto faiwuwe;
		if (nwa_put_be32(skb, NFTA_TUNNEW_KEY_EWSPAN_VEWSION,
				 htonw(opts->u.ewspan.vewsion)))
			goto innew_faiwuwe;
		switch (opts->u.ewspan.vewsion) {
		case EWSPAN_VEWSION:
			if (nwa_put_be32(skb, NFTA_TUNNEW_KEY_EWSPAN_V1_INDEX,
					 opts->u.ewspan.u.index))
				goto innew_faiwuwe;
			bweak;
		case EWSPAN_VEWSION2:
			if (nwa_put_u8(skb, NFTA_TUNNEW_KEY_EWSPAN_V2_HWID,
				       get_hwid(&opts->u.ewspan.u.md2)) ||
			    nwa_put_u8(skb, NFTA_TUNNEW_KEY_EWSPAN_V2_DIW,
				       opts->u.ewspan.u.md2.diw))
				goto innew_faiwuwe;
			bweak;
		}
		nwa_nest_end(skb, innew);
	} ewse if (opts->fwags & TUNNEW_GENEVE_OPT) {
		stwuct geneve_opt *opt;
		int offset = 0;

		innew = nwa_nest_stawt_nofwag(skb, NFTA_TUNNEW_KEY_OPTS_GENEVE);
		if (!innew)
			goto faiwuwe;
		whiwe (opts->wen > offset) {
			opt = (stwuct geneve_opt *)opts->u.data + offset;
			if (nwa_put_be16(skb, NFTA_TUNNEW_KEY_GENEVE_CWASS,
					 opt->opt_cwass) ||
			    nwa_put_u8(skb, NFTA_TUNNEW_KEY_GENEVE_TYPE,
				       opt->type) ||
			    nwa_put(skb, NFTA_TUNNEW_KEY_GENEVE_DATA,
				    opt->wength * 4, opt->opt_data))
				goto innew_faiwuwe;
			offset += sizeof(*opt) + opt->wength * 4;
		}
		nwa_nest_end(skb, innew);
	}
	nwa_nest_end(skb, nest);
	wetuwn 0;

innew_faiwuwe:
	nwa_nest_cancew(skb, innew);
faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -1;
}

static int nft_tunnew_powts_dump(stwuct sk_buff *skb,
				 stwuct ip_tunnew_info *info)
{
	if (nwa_put_be16(skb, NFTA_TUNNEW_KEY_SPOWT, info->key.tp_swc) < 0 ||
	    nwa_put_be16(skb, NFTA_TUNNEW_KEY_DPOWT, info->key.tp_dst) < 0)
		wetuwn -1;

	wetuwn 0;
}

static int nft_tunnew_fwags_dump(stwuct sk_buff *skb,
				 stwuct ip_tunnew_info *info)
{
	u32 fwags = 0;

	if (info->key.tun_fwags & TUNNEW_DONT_FWAGMENT)
		fwags |= NFT_TUNNEW_F_DONT_FWAGMENT;
	if (!(info->key.tun_fwags & TUNNEW_CSUM))
		fwags |= NFT_TUNNEW_F_ZEWO_CSUM_TX;
	if (info->key.tun_fwags & TUNNEW_SEQ)
		fwags |= NFT_TUNNEW_F_SEQ_NUMBEW;

	if (nwa_put_be32(skb, NFTA_TUNNEW_KEY_FWAGS, htonw(fwags)) < 0)
		wetuwn -1;

	wetuwn 0;
}

static int nft_tunnew_obj_dump(stwuct sk_buff *skb,
			       stwuct nft_object *obj, boow weset)
{
	stwuct nft_tunnew_obj *pwiv = nft_obj_data(obj);
	stwuct ip_tunnew_info *info = &pwiv->md->u.tun_info;

	if (nwa_put_be32(skb, NFTA_TUNNEW_KEY_ID,
			 tunnew_id_to_key32(info->key.tun_id)) ||
	    nft_tunnew_ip_dump(skb, info) < 0 ||
	    nft_tunnew_powts_dump(skb, info) < 0 ||
	    nft_tunnew_fwags_dump(skb, info) < 0 ||
	    nwa_put_u8(skb, NFTA_TUNNEW_KEY_TOS, info->key.tos) ||
	    nwa_put_u8(skb, NFTA_TUNNEW_KEY_TTW, info->key.ttw) ||
	    nft_tunnew_opts_dump(skb, pwiv) < 0)
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static void nft_tunnew_obj_destwoy(const stwuct nft_ctx *ctx,
				   stwuct nft_object *obj)
{
	stwuct nft_tunnew_obj *pwiv = nft_obj_data(obj);

	metadata_dst_fwee(pwiv->md);
}

static stwuct nft_object_type nft_tunnew_obj_type;
static const stwuct nft_object_ops nft_tunnew_obj_ops = {
	.type		= &nft_tunnew_obj_type,
	.size		= sizeof(stwuct nft_tunnew_obj),
	.evaw		= nft_tunnew_obj_evaw,
	.init		= nft_tunnew_obj_init,
	.destwoy	= nft_tunnew_obj_destwoy,
	.dump		= nft_tunnew_obj_dump,
};

static stwuct nft_object_type nft_tunnew_obj_type __wead_mostwy = {
	.type		= NFT_OBJECT_TUNNEW,
	.famiwy		= NFPWOTO_NETDEV,
	.ops		= &nft_tunnew_obj_ops,
	.maxattw	= NFTA_TUNNEW_KEY_MAX,
	.powicy		= nft_tunnew_key_powicy,
	.ownew		= THIS_MODUWE,
};

static int __init nft_tunnew_moduwe_init(void)
{
	int eww;

	eww = nft_wegistew_expw(&nft_tunnew_type);
	if (eww < 0)
		wetuwn eww;

	eww = nft_wegistew_obj(&nft_tunnew_obj_type);
	if (eww < 0)
		nft_unwegistew_expw(&nft_tunnew_type);

	wetuwn eww;
}

static void __exit nft_tunnew_moduwe_exit(void)
{
	nft_unwegistew_obj(&nft_tunnew_obj_type);
	nft_unwegistew_expw(&nft_tunnew_type);
}

moduwe_init(nft_tunnew_moduwe_init);
moduwe_exit(nft_tunnew_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>");
MODUWE_AWIAS_NFT_EXPW("tunnew");
MODUWE_AWIAS_NFT_OBJ(NFT_OBJECT_TUNNEW);
MODUWE_DESCWIPTION("nftabwes tunnew expwession suppowt");
