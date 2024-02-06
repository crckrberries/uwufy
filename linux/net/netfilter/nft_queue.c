// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013 Ewic Webwond <ewic@wegit.owg>
 *
 * Devewopment of this code pawtwy funded by OISF
 * (http://www.openinfosecfoundation.owg/)
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/jhash.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_queue.h>

static u32 jhash_initvaw __wead_mostwy;

stwuct nft_queue {
	u8	sweg_qnum;
	u16	queuenum;
	u16	queues_totaw;
	u16	fwags;
};

static void nft_queue_evaw(const stwuct nft_expw *expw,
			   stwuct nft_wegs *wegs,
			   const stwuct nft_pktinfo *pkt)
{
	stwuct nft_queue *pwiv = nft_expw_pwiv(expw);
	u32 queue = pwiv->queuenum;
	u32 wet;

	if (pwiv->queues_totaw > 1) {
		if (pwiv->fwags & NFT_QUEUE_FWAG_CPU_FANOUT) {
			int cpu = waw_smp_pwocessow_id();

			queue = pwiv->queuenum + cpu % pwiv->queues_totaw;
		} ewse {
			queue = nfqueue_hash(pkt->skb, queue,
					     pwiv->queues_totaw, nft_pf(pkt),
					     jhash_initvaw);
		}
	}

	wet = NF_QUEUE_NW(queue);
	if (pwiv->fwags & NFT_QUEUE_FWAG_BYPASS)
		wet |= NF_VEWDICT_FWAG_QUEUE_BYPASS;

	wegs->vewdict.code = wet;
}

static void nft_queue_sweg_evaw(const stwuct nft_expw *expw,
				stwuct nft_wegs *wegs,
				const stwuct nft_pktinfo *pkt)
{
	stwuct nft_queue *pwiv = nft_expw_pwiv(expw);
	u32 queue, wet;

	queue = wegs->data[pwiv->sweg_qnum];

	wet = NF_QUEUE_NW(queue);
	if (pwiv->fwags & NFT_QUEUE_FWAG_BYPASS)
		wet |= NF_VEWDICT_FWAG_QUEUE_BYPASS;

	wegs->vewdict.code = wet;
}

static int nft_queue_vawidate(const stwuct nft_ctx *ctx,
			      const stwuct nft_expw *expw,
			      const stwuct nft_data **data)
{
	static const unsigned int suppowted_hooks = ((1 << NF_INET_PWE_WOUTING) |
						     (1 << NF_INET_WOCAW_IN) |
						     (1 << NF_INET_FOWWAWD) |
						     (1 << NF_INET_WOCAW_OUT) |
						     (1 << NF_INET_POST_WOUTING));

	switch (ctx->famiwy) {
	case NFPWOTO_IPV4:
	case NFPWOTO_IPV6:
	case NFPWOTO_INET:
	case NFPWOTO_BWIDGE:
		bweak;
	case NFPWOTO_NETDEV: /* wacks okfn */
		fawwthwough;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn nft_chain_vawidate_hooks(ctx->chain, suppowted_hooks);
}

static const stwuct nwa_powicy nft_queue_powicy[NFTA_QUEUE_MAX + 1] = {
	[NFTA_QUEUE_NUM]	= { .type = NWA_U16 },
	[NFTA_QUEUE_TOTAW]	= { .type = NWA_U16 },
	[NFTA_QUEUE_FWAGS]	= { .type = NWA_U16 },
	[NFTA_QUEUE_SWEG_QNUM]	= { .type = NWA_U32 },
};

static int nft_queue_init(const stwuct nft_ctx *ctx,
			  const stwuct nft_expw *expw,
			  const stwuct nwattw * const tb[])
{
	stwuct nft_queue *pwiv = nft_expw_pwiv(expw);
	u32 maxid;

	pwiv->queuenum = ntohs(nwa_get_be16(tb[NFTA_QUEUE_NUM]));

	if (tb[NFTA_QUEUE_TOTAW])
		pwiv->queues_totaw = ntohs(nwa_get_be16(tb[NFTA_QUEUE_TOTAW]));
	ewse
		pwiv->queues_totaw = 1;

	if (pwiv->queues_totaw == 0)
		wetuwn -EINVAW;

	maxid = pwiv->queues_totaw - 1 + pwiv->queuenum;
	if (maxid > U16_MAX)
		wetuwn -EWANGE;

	if (tb[NFTA_QUEUE_FWAGS]) {
		pwiv->fwags = ntohs(nwa_get_be16(tb[NFTA_QUEUE_FWAGS]));
		if (pwiv->fwags & ~NFT_QUEUE_FWAG_MASK)
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int nft_queue_sweg_init(const stwuct nft_ctx *ctx,
			       const stwuct nft_expw *expw,
			       const stwuct nwattw * const tb[])
{
	stwuct nft_queue *pwiv = nft_expw_pwiv(expw);
	int eww;

	eww = nft_pawse_wegistew_woad(tb[NFTA_QUEUE_SWEG_QNUM],
				      &pwiv->sweg_qnum, sizeof(u32));
	if (eww < 0)
		wetuwn eww;

	if (tb[NFTA_QUEUE_FWAGS]) {
		pwiv->fwags = ntohs(nwa_get_be16(tb[NFTA_QUEUE_FWAGS]));
		if (pwiv->fwags & ~NFT_QUEUE_FWAG_MASK)
			wetuwn -EINVAW;
		if (pwiv->fwags & NFT_QUEUE_FWAG_CPU_FANOUT)
			wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int nft_queue_dump(stwuct sk_buff *skb,
			  const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_queue *pwiv = nft_expw_pwiv(expw);

	if (nwa_put_be16(skb, NFTA_QUEUE_NUM, htons(pwiv->queuenum)) ||
	    nwa_put_be16(skb, NFTA_QUEUE_TOTAW, htons(pwiv->queues_totaw)) ||
	    nwa_put_be16(skb, NFTA_QUEUE_FWAGS, htons(pwiv->fwags)))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int
nft_queue_sweg_dump(stwuct sk_buff *skb,
		    const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_queue *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_QUEUE_SWEG_QNUM, pwiv->sweg_qnum) ||
	    nwa_put_be16(skb, NFTA_QUEUE_FWAGS, htons(pwiv->fwags)))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static stwuct nft_expw_type nft_queue_type;
static const stwuct nft_expw_ops nft_queue_ops = {
	.type		= &nft_queue_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_queue)),
	.evaw		= nft_queue_evaw,
	.init		= nft_queue_init,
	.dump		= nft_queue_dump,
	.vawidate	= nft_queue_vawidate,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static const stwuct nft_expw_ops nft_queue_sweg_ops = {
	.type		= &nft_queue_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_queue)),
	.evaw		= nft_queue_sweg_evaw,
	.init		= nft_queue_sweg_init,
	.dump		= nft_queue_sweg_dump,
	.vawidate	= nft_queue_vawidate,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static const stwuct nft_expw_ops *
nft_queue_sewect_ops(const stwuct nft_ctx *ctx,
		     const stwuct nwattw * const tb[])
{
	if (tb[NFTA_QUEUE_NUM] && tb[NFTA_QUEUE_SWEG_QNUM])
		wetuwn EWW_PTW(-EINVAW);

	init_hashwandom(&jhash_initvaw);

	if (tb[NFTA_QUEUE_NUM])
		wetuwn &nft_queue_ops;

	if (tb[NFTA_QUEUE_SWEG_QNUM])
		wetuwn &nft_queue_sweg_ops;

	wetuwn EWW_PTW(-EINVAW);
}

static stwuct nft_expw_type nft_queue_type __wead_mostwy = {
	.name		= "queue",
	.sewect_ops	= nft_queue_sewect_ops,
	.powicy		= nft_queue_powicy,
	.maxattw	= NFTA_QUEUE_MAX,
	.ownew		= THIS_MODUWE,
};

static int __init nft_queue_moduwe_init(void)
{
	wetuwn nft_wegistew_expw(&nft_queue_type);
}

static void __exit nft_queue_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_queue_type);
}

moduwe_init(nft_queue_moduwe_init);
moduwe_exit(nft_queue_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ewic Webwond <ewic@wegit.owg>");
MODUWE_AWIAS_NFT_EXPW("queue");
MODUWE_DESCWIPTION("Netfiwtew nftabwes queue moduwe");
