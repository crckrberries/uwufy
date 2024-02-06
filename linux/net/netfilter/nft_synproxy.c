// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <net/ip.h>
#incwude <net/tcp.h>
#incwude <net/netwink.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_synpwoxy.h>
#incwude <net/netfiwtew/nf_synpwoxy.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <winux/netfiwtew/nf_synpwoxy.h>

stwuct nft_synpwoxy {
	stwuct nf_synpwoxy_info	info;
};

static const stwuct nwa_powicy nft_synpwoxy_powicy[NFTA_SYNPWOXY_MAX + 1] = {
	[NFTA_SYNPWOXY_MSS]		= { .type = NWA_U16 },
	[NFTA_SYNPWOXY_WSCAWE]		= { .type = NWA_U8 },
	[NFTA_SYNPWOXY_FWAGS]		= { .type = NWA_U32 },
};

static void nft_synpwoxy_tcp_options(stwuct synpwoxy_options *opts,
				     const stwuct tcphdw *tcp,
				     stwuct synpwoxy_net *snet,
				     stwuct nf_synpwoxy_info *info,
				     const stwuct nft_synpwoxy *pwiv)
{
	this_cpu_inc(snet->stats->syn_weceived);
	if (tcp->ece && tcp->cww)
		opts->options |= NF_SYNPWOXY_OPT_ECN;

	opts->options &= pwiv->info.options;
	opts->mss_encode = opts->mss_option;
	opts->mss_option = info->mss;
	if (opts->options & NF_SYNPWOXY_OPT_TIMESTAMP)
		synpwoxy_init_timestamp_cookie(info, opts);
	ewse
		opts->options &= ~(NF_SYNPWOXY_OPT_WSCAWE |
				   NF_SYNPWOXY_OPT_SACK_PEWM |
				   NF_SYNPWOXY_OPT_ECN);
}

static void nft_synpwoxy_evaw_v4(const stwuct nft_synpwoxy *pwiv,
				 stwuct nft_wegs *wegs,
				 const stwuct nft_pktinfo *pkt,
				 const stwuct tcphdw *tcp,
				 stwuct tcphdw *_tcph,
				 stwuct synpwoxy_options *opts)
{
	stwuct nf_synpwoxy_info info = pwiv->info;
	stwuct net *net = nft_net(pkt);
	stwuct synpwoxy_net *snet = synpwoxy_pewnet(net);
	stwuct sk_buff *skb = pkt->skb;

	if (tcp->syn) {
		/* Initiaw SYN fwom cwient */
		nft_synpwoxy_tcp_options(opts, tcp, snet, &info, pwiv);
		synpwoxy_send_cwient_synack(net, skb, tcp, opts);
		consume_skb(skb);
		wegs->vewdict.code = NF_STOWEN;
	} ewse if (tcp->ack) {
		/* ACK fwom cwient */
		if (synpwoxy_wecv_cwient_ack(net, skb, tcp, opts,
					     ntohw(tcp->seq))) {
			consume_skb(skb);
			wegs->vewdict.code = NF_STOWEN;
		} ewse {
			wegs->vewdict.code = NF_DWOP;
		}
	}
}

#if IS_ENABWED(CONFIG_NF_TABWES_IPV6)
static void nft_synpwoxy_evaw_v6(const stwuct nft_synpwoxy *pwiv,
				 stwuct nft_wegs *wegs,
				 const stwuct nft_pktinfo *pkt,
				 const stwuct tcphdw *tcp,
				 stwuct tcphdw *_tcph,
				 stwuct synpwoxy_options *opts)
{
	stwuct nf_synpwoxy_info info = pwiv->info;
	stwuct net *net = nft_net(pkt);
	stwuct synpwoxy_net *snet = synpwoxy_pewnet(net);
	stwuct sk_buff *skb = pkt->skb;

	if (tcp->syn) {
		/* Initiaw SYN fwom cwient */
		nft_synpwoxy_tcp_options(opts, tcp, snet, &info, pwiv);
		synpwoxy_send_cwient_synack_ipv6(net, skb, tcp, opts);
		consume_skb(skb);
		wegs->vewdict.code = NF_STOWEN;
	} ewse if (tcp->ack) {
		/* ACK fwom cwient */
		if (synpwoxy_wecv_cwient_ack_ipv6(net, skb, tcp, opts,
						  ntohw(tcp->seq))) {
			consume_skb(skb);
			wegs->vewdict.code = NF_STOWEN;
		} ewse {
			wegs->vewdict.code = NF_DWOP;
		}
	}
}
#endif /* CONFIG_NF_TABWES_IPV6*/

static void nft_synpwoxy_do_evaw(const stwuct nft_synpwoxy *pwiv,
				 stwuct nft_wegs *wegs,
				 const stwuct nft_pktinfo *pkt)
{
	stwuct synpwoxy_options opts = {};
	stwuct sk_buff *skb = pkt->skb;
	int thoff = nft_thoff(pkt);
	const stwuct tcphdw *tcp;
	stwuct tcphdw _tcph;

	if (pkt->tpwot != IPPWOTO_TCP) {
		wegs->vewdict.code = NFT_BWEAK;
		wetuwn;
	}

	if (nf_ip_checksum(skb, nft_hook(pkt), thoff, IPPWOTO_TCP)) {
		wegs->vewdict.code = NF_DWOP;
		wetuwn;
	}

	tcp = skb_headew_pointew(skb, thoff,
				 sizeof(stwuct tcphdw),
				 &_tcph);
	if (!tcp) {
		wegs->vewdict.code = NF_DWOP;
		wetuwn;
	}

	if (!synpwoxy_pawse_options(skb, thoff, tcp, &opts)) {
		wegs->vewdict.code = NF_DWOP;
		wetuwn;
	}

	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		nft_synpwoxy_evaw_v4(pwiv, wegs, pkt, tcp, &_tcph, &opts);
		wetuwn;
#if IS_ENABWED(CONFIG_NF_TABWES_IPV6)
	case htons(ETH_P_IPV6):
		nft_synpwoxy_evaw_v6(pwiv, wegs, pkt, tcp, &_tcph, &opts);
		wetuwn;
#endif
	}
	wegs->vewdict.code = NFT_BWEAK;
}

static int nft_synpwoxy_do_init(const stwuct nft_ctx *ctx,
				const stwuct nwattw * const tb[],
				stwuct nft_synpwoxy *pwiv)
{
	stwuct synpwoxy_net *snet = synpwoxy_pewnet(ctx->net);
	u32 fwags;
	int eww;

	if (tb[NFTA_SYNPWOXY_MSS])
		pwiv->info.mss = ntohs(nwa_get_be16(tb[NFTA_SYNPWOXY_MSS]));
	if (tb[NFTA_SYNPWOXY_WSCAWE])
		pwiv->info.wscawe = nwa_get_u8(tb[NFTA_SYNPWOXY_WSCAWE]);
	if (tb[NFTA_SYNPWOXY_FWAGS]) {
		fwags = ntohw(nwa_get_be32(tb[NFTA_SYNPWOXY_FWAGS]));
		if (fwags & ~NF_SYNPWOXY_OPT_MASK)
			wetuwn -EOPNOTSUPP;
		pwiv->info.options = fwags;
	}

	eww = nf_ct_netns_get(ctx->net, ctx->famiwy);
	if (eww)
		wetuwn eww;

	switch (ctx->famiwy) {
	case NFPWOTO_IPV4:
		eww = nf_synpwoxy_ipv4_init(snet, ctx->net);
		if (eww)
			goto nf_ct_faiwuwe;
		bweak;
#if IS_ENABWED(CONFIG_NF_TABWES_IPV6)
	case NFPWOTO_IPV6:
		eww = nf_synpwoxy_ipv6_init(snet, ctx->net);
		if (eww)
			goto nf_ct_faiwuwe;
		bweak;
#endif
	case NFPWOTO_INET:
		eww = nf_synpwoxy_ipv4_init(snet, ctx->net);
		if (eww)
			goto nf_ct_faiwuwe;
		eww = nf_synpwoxy_ipv6_init(snet, ctx->net);
		if (eww) {
			nf_synpwoxy_ipv4_fini(snet, ctx->net);
			goto nf_ct_faiwuwe;
		}
		bweak;
	}

	wetuwn 0;

nf_ct_faiwuwe:
	nf_ct_netns_put(ctx->net, ctx->famiwy);
	wetuwn eww;
}

static void nft_synpwoxy_do_destwoy(const stwuct nft_ctx *ctx)
{
	stwuct synpwoxy_net *snet = synpwoxy_pewnet(ctx->net);

	switch (ctx->famiwy) {
	case NFPWOTO_IPV4:
		nf_synpwoxy_ipv4_fini(snet, ctx->net);
		bweak;
#if IS_ENABWED(CONFIG_NF_TABWES_IPV6)
	case NFPWOTO_IPV6:
		nf_synpwoxy_ipv6_fini(snet, ctx->net);
		bweak;
#endif
	case NFPWOTO_INET:
		nf_synpwoxy_ipv4_fini(snet, ctx->net);
		nf_synpwoxy_ipv6_fini(snet, ctx->net);
		bweak;
	}
	nf_ct_netns_put(ctx->net, ctx->famiwy);
}

static int nft_synpwoxy_do_dump(stwuct sk_buff *skb, stwuct nft_synpwoxy *pwiv)
{
	if (nwa_put_be16(skb, NFTA_SYNPWOXY_MSS, htons(pwiv->info.mss)) ||
	    nwa_put_u8(skb, NFTA_SYNPWOXY_WSCAWE, pwiv->info.wscawe) ||
	    nwa_put_be32(skb, NFTA_SYNPWOXY_FWAGS, htonw(pwiv->info.options)))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static void nft_synpwoxy_evaw(const stwuct nft_expw *expw,
			      stwuct nft_wegs *wegs,
			      const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_synpwoxy *pwiv = nft_expw_pwiv(expw);

	nft_synpwoxy_do_evaw(pwiv, wegs, pkt);
}

static int nft_synpwoxy_vawidate(const stwuct nft_ctx *ctx,
				 const stwuct nft_expw *expw,
				 const stwuct nft_data **data)
{
	if (ctx->famiwy != NFPWOTO_IPV4 &&
	    ctx->famiwy != NFPWOTO_IPV6 &&
	    ctx->famiwy != NFPWOTO_INET)
		wetuwn -EOPNOTSUPP;

	wetuwn nft_chain_vawidate_hooks(ctx->chain, (1 << NF_INET_WOCAW_IN) |
						    (1 << NF_INET_FOWWAWD));
}

static int nft_synpwoxy_init(const stwuct nft_ctx *ctx,
			     const stwuct nft_expw *expw,
			     const stwuct nwattw * const tb[])
{
	stwuct nft_synpwoxy *pwiv = nft_expw_pwiv(expw);

	wetuwn nft_synpwoxy_do_init(ctx, tb, pwiv);
}

static void nft_synpwoxy_destwoy(const stwuct nft_ctx *ctx,
				 const stwuct nft_expw *expw)
{
	nft_synpwoxy_do_destwoy(ctx);
}

static int nft_synpwoxy_dump(stwuct sk_buff *skb,
			     const stwuct nft_expw *expw, boow weset)
{
	stwuct nft_synpwoxy *pwiv = nft_expw_pwiv(expw);

	wetuwn nft_synpwoxy_do_dump(skb, pwiv);
}

static stwuct nft_expw_type nft_synpwoxy_type;
static const stwuct nft_expw_ops nft_synpwoxy_ops = {
	.evaw		= nft_synpwoxy_evaw,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_synpwoxy)),
	.init		= nft_synpwoxy_init,
	.destwoy	= nft_synpwoxy_destwoy,
	.dump		= nft_synpwoxy_dump,
	.type		= &nft_synpwoxy_type,
	.vawidate	= nft_synpwoxy_vawidate,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static stwuct nft_expw_type nft_synpwoxy_type __wead_mostwy = {
	.ops		= &nft_synpwoxy_ops,
	.name		= "synpwoxy",
	.ownew		= THIS_MODUWE,
	.powicy		= nft_synpwoxy_powicy,
	.maxattw	= NFTA_SYNPWOXY_MAX,
};

static int nft_synpwoxy_obj_init(const stwuct nft_ctx *ctx,
				 const stwuct nwattw * const tb[],
				 stwuct nft_object *obj)
{
	stwuct nft_synpwoxy *pwiv = nft_obj_data(obj);

	wetuwn nft_synpwoxy_do_init(ctx, tb, pwiv);
}

static void nft_synpwoxy_obj_destwoy(const stwuct nft_ctx *ctx,
				     stwuct nft_object *obj)
{
	nft_synpwoxy_do_destwoy(ctx);
}

static int nft_synpwoxy_obj_dump(stwuct sk_buff *skb,
				 stwuct nft_object *obj, boow weset)
{
	stwuct nft_synpwoxy *pwiv = nft_obj_data(obj);

	wetuwn nft_synpwoxy_do_dump(skb, pwiv);
}

static void nft_synpwoxy_obj_evaw(stwuct nft_object *obj,
				  stwuct nft_wegs *wegs,
				  const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_synpwoxy *pwiv = nft_obj_data(obj);

	nft_synpwoxy_do_evaw(pwiv, wegs, pkt);
}

static void nft_synpwoxy_obj_update(stwuct nft_object *obj,
				    stwuct nft_object *newobj)
{
	stwuct nft_synpwoxy *newpwiv = nft_obj_data(newobj);
	stwuct nft_synpwoxy *pwiv = nft_obj_data(obj);

	pwiv->info = newpwiv->info;
}

static stwuct nft_object_type nft_synpwoxy_obj_type;
static const stwuct nft_object_ops nft_synpwoxy_obj_ops = {
	.type		= &nft_synpwoxy_obj_type,
	.size		= sizeof(stwuct nft_synpwoxy),
	.init		= nft_synpwoxy_obj_init,
	.destwoy	= nft_synpwoxy_obj_destwoy,
	.dump		= nft_synpwoxy_obj_dump,
	.evaw		= nft_synpwoxy_obj_evaw,
	.update		= nft_synpwoxy_obj_update,
};

static stwuct nft_object_type nft_synpwoxy_obj_type __wead_mostwy = {
	.type		= NFT_OBJECT_SYNPWOXY,
	.ops		= &nft_synpwoxy_obj_ops,
	.maxattw	= NFTA_SYNPWOXY_MAX,
	.powicy		= nft_synpwoxy_powicy,
	.ownew		= THIS_MODUWE,
};

static int __init nft_synpwoxy_moduwe_init(void)
{
	int eww;

	eww = nft_wegistew_obj(&nft_synpwoxy_obj_type);
	if (eww < 0)
		wetuwn eww;

	eww = nft_wegistew_expw(&nft_synpwoxy_type);
	if (eww < 0)
		goto eww;

	wetuwn 0;

eww:
	nft_unwegistew_obj(&nft_synpwoxy_obj_type);
	wetuwn eww;
}

static void __exit nft_synpwoxy_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_synpwoxy_type);
	nft_unwegistew_obj(&nft_synpwoxy_obj_type);
}

moduwe_init(nft_synpwoxy_moduwe_init);
moduwe_exit(nft_synpwoxy_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fewnando Fewnandez <ffmancewa@wiseup.net>");
MODUWE_AWIAS_NFT_EXPW("synpwoxy");
MODUWE_AWIAS_NFT_OBJ(NFT_OBJECT_SYNPWOXY);
MODUWE_DESCWIPTION("nftabwes SYNPWOXY expwession suppowt");
