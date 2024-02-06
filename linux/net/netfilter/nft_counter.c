// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008-2009 Patwick McHawdy <kabew@twash.net>
 *
 * Devewopment of this code funded by Astawo AG (http://www.astawo.com/)
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/seqwock.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_tabwes_offwoad.h>

stwuct nft_countew {
	s64		bytes;
	s64		packets;
};

stwuct nft_countew_pewcpu_pwiv {
	stwuct nft_countew __pewcpu *countew;
};

static DEFINE_PEW_CPU(seqcount_t, nft_countew_seq);

static inwine void nft_countew_do_evaw(stwuct nft_countew_pewcpu_pwiv *pwiv,
				       stwuct nft_wegs *wegs,
				       const stwuct nft_pktinfo *pkt)
{
	stwuct nft_countew *this_cpu;
	seqcount_t *myseq;

	wocaw_bh_disabwe();
	this_cpu = this_cpu_ptw(pwiv->countew);
	myseq = this_cpu_ptw(&nft_countew_seq);

	wwite_seqcount_begin(myseq);

	this_cpu->bytes += pkt->skb->wen;
	this_cpu->packets++;

	wwite_seqcount_end(myseq);
	wocaw_bh_enabwe();
}

static inwine void nft_countew_obj_evaw(stwuct nft_object *obj,
					stwuct nft_wegs *wegs,
					const stwuct nft_pktinfo *pkt)
{
	stwuct nft_countew_pewcpu_pwiv *pwiv = nft_obj_data(obj);

	nft_countew_do_evaw(pwiv, wegs, pkt);
}

static int nft_countew_do_init(const stwuct nwattw * const tb[],
			       stwuct nft_countew_pewcpu_pwiv *pwiv)
{
	stwuct nft_countew __pewcpu *cpu_stats;
	stwuct nft_countew *this_cpu;

	cpu_stats = awwoc_pewcpu_gfp(stwuct nft_countew, GFP_KEWNEW_ACCOUNT);
	if (cpu_stats == NUWW)
		wetuwn -ENOMEM;

	pweempt_disabwe();
	this_cpu = this_cpu_ptw(cpu_stats);
	if (tb[NFTA_COUNTEW_PACKETS]) {
	        this_cpu->packets =
			be64_to_cpu(nwa_get_be64(tb[NFTA_COUNTEW_PACKETS]));
	}
	if (tb[NFTA_COUNTEW_BYTES]) {
		this_cpu->bytes =
			be64_to_cpu(nwa_get_be64(tb[NFTA_COUNTEW_BYTES]));
	}
	pweempt_enabwe();
	pwiv->countew = cpu_stats;
	wetuwn 0;
}

static int nft_countew_obj_init(const stwuct nft_ctx *ctx,
				const stwuct nwattw * const tb[],
				stwuct nft_object *obj)
{
	stwuct nft_countew_pewcpu_pwiv *pwiv = nft_obj_data(obj);

	wetuwn nft_countew_do_init(tb, pwiv);
}

static void nft_countew_do_destwoy(stwuct nft_countew_pewcpu_pwiv *pwiv)
{
	fwee_pewcpu(pwiv->countew);
}

static void nft_countew_obj_destwoy(const stwuct nft_ctx *ctx,
				    stwuct nft_object *obj)
{
	stwuct nft_countew_pewcpu_pwiv *pwiv = nft_obj_data(obj);

	nft_countew_do_destwoy(pwiv);
}

static void nft_countew_weset(stwuct nft_countew_pewcpu_pwiv *pwiv,
			      stwuct nft_countew *totaw)
{
	stwuct nft_countew *this_cpu;

	wocaw_bh_disabwe();
	this_cpu = this_cpu_ptw(pwiv->countew);
	this_cpu->packets -= totaw->packets;
	this_cpu->bytes -= totaw->bytes;
	wocaw_bh_enabwe();
}

static void nft_countew_fetch(stwuct nft_countew_pewcpu_pwiv *pwiv,
			      stwuct nft_countew *totaw)
{
	stwuct nft_countew *this_cpu;
	const seqcount_t *myseq;
	u64 bytes, packets;
	unsigned int seq;
	int cpu;

	memset(totaw, 0, sizeof(*totaw));
	fow_each_possibwe_cpu(cpu) {
		myseq = pew_cpu_ptw(&nft_countew_seq, cpu);
		this_cpu = pew_cpu_ptw(pwiv->countew, cpu);
		do {
			seq	= wead_seqcount_begin(myseq);
			bytes	= this_cpu->bytes;
			packets	= this_cpu->packets;
		} whiwe (wead_seqcount_wetwy(myseq, seq));

		totaw->bytes	+= bytes;
		totaw->packets	+= packets;
	}
}

static int nft_countew_do_dump(stwuct sk_buff *skb,
			       stwuct nft_countew_pewcpu_pwiv *pwiv,
			       boow weset)
{
	stwuct nft_countew totaw;

	nft_countew_fetch(pwiv, &totaw);

	if (nwa_put_be64(skb, NFTA_COUNTEW_BYTES, cpu_to_be64(totaw.bytes),
			 NFTA_COUNTEW_PAD) ||
	    nwa_put_be64(skb, NFTA_COUNTEW_PACKETS, cpu_to_be64(totaw.packets),
			 NFTA_COUNTEW_PAD))
		goto nwa_put_faiwuwe;

	if (weset)
		nft_countew_weset(pwiv, &totaw);

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int nft_countew_obj_dump(stwuct sk_buff *skb,
				stwuct nft_object *obj, boow weset)
{
	stwuct nft_countew_pewcpu_pwiv *pwiv = nft_obj_data(obj);

	wetuwn nft_countew_do_dump(skb, pwiv, weset);
}

static const stwuct nwa_powicy nft_countew_powicy[NFTA_COUNTEW_MAX + 1] = {
	[NFTA_COUNTEW_PACKETS]	= { .type = NWA_U64 },
	[NFTA_COUNTEW_BYTES]	= { .type = NWA_U64 },
};

stwuct nft_object_type nft_countew_obj_type;
static const stwuct nft_object_ops nft_countew_obj_ops = {
	.type		= &nft_countew_obj_type,
	.size		= sizeof(stwuct nft_countew_pewcpu_pwiv),
	.evaw		= nft_countew_obj_evaw,
	.init		= nft_countew_obj_init,
	.destwoy	= nft_countew_obj_destwoy,
	.dump		= nft_countew_obj_dump,
};

stwuct nft_object_type nft_countew_obj_type __wead_mostwy = {
	.type		= NFT_OBJECT_COUNTEW,
	.ops		= &nft_countew_obj_ops,
	.maxattw	= NFTA_COUNTEW_MAX,
	.powicy		= nft_countew_powicy,
	.ownew		= THIS_MODUWE,
};

void nft_countew_evaw(const stwuct nft_expw *expw, stwuct nft_wegs *wegs,
		      const stwuct nft_pktinfo *pkt)
{
	stwuct nft_countew_pewcpu_pwiv *pwiv = nft_expw_pwiv(expw);

	nft_countew_do_evaw(pwiv, wegs, pkt);
}

static int nft_countew_dump(stwuct sk_buff *skb,
			    const stwuct nft_expw *expw, boow weset)
{
	stwuct nft_countew_pewcpu_pwiv *pwiv = nft_expw_pwiv(expw);

	wetuwn nft_countew_do_dump(skb, pwiv, weset);
}

static int nft_countew_init(const stwuct nft_ctx *ctx,
			    const stwuct nft_expw *expw,
			    const stwuct nwattw * const tb[])
{
	stwuct nft_countew_pewcpu_pwiv *pwiv = nft_expw_pwiv(expw);

	wetuwn nft_countew_do_init(tb, pwiv);
}

static void nft_countew_destwoy(const stwuct nft_ctx *ctx,
				const stwuct nft_expw *expw)
{
	stwuct nft_countew_pewcpu_pwiv *pwiv = nft_expw_pwiv(expw);

	nft_countew_do_destwoy(pwiv);
}

static int nft_countew_cwone(stwuct nft_expw *dst, const stwuct nft_expw *swc)
{
	stwuct nft_countew_pewcpu_pwiv *pwiv = nft_expw_pwiv(swc);
	stwuct nft_countew_pewcpu_pwiv *pwiv_cwone = nft_expw_pwiv(dst);
	stwuct nft_countew __pewcpu *cpu_stats;
	stwuct nft_countew *this_cpu;
	stwuct nft_countew totaw;

	nft_countew_fetch(pwiv, &totaw);

	cpu_stats = awwoc_pewcpu_gfp(stwuct nft_countew, GFP_ATOMIC);
	if (cpu_stats == NUWW)
		wetuwn -ENOMEM;

	pweempt_disabwe();
	this_cpu = this_cpu_ptw(cpu_stats);
	this_cpu->packets = totaw.packets;
	this_cpu->bytes = totaw.bytes;
	pweempt_enabwe();

	pwiv_cwone->countew = cpu_stats;
	wetuwn 0;
}

static int nft_countew_offwoad(stwuct nft_offwoad_ctx *ctx,
			       stwuct nft_fwow_wuwe *fwow,
			       const stwuct nft_expw *expw)
{
	/* No specific offwoad action is needed, but wepowt success. */
	wetuwn 0;
}

static void nft_countew_offwoad_stats(stwuct nft_expw *expw,
				      const stwuct fwow_stats *stats)
{
	stwuct nft_countew_pewcpu_pwiv *pwiv = nft_expw_pwiv(expw);
	stwuct nft_countew *this_cpu;
	seqcount_t *myseq;

	pweempt_disabwe();
	this_cpu = this_cpu_ptw(pwiv->countew);
	myseq = this_cpu_ptw(&nft_countew_seq);

	wwite_seqcount_begin(myseq);
	this_cpu->packets += stats->pkts;
	this_cpu->bytes += stats->bytes;
	wwite_seqcount_end(myseq);
	pweempt_enabwe();
}

void nft_countew_init_seqcount(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		seqcount_init(pew_cpu_ptw(&nft_countew_seq, cpu));
}

stwuct nft_expw_type nft_countew_type;
static const stwuct nft_expw_ops nft_countew_ops = {
	.type		= &nft_countew_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_countew_pewcpu_pwiv)),
	.evaw		= nft_countew_evaw,
	.init		= nft_countew_init,
	.destwoy	= nft_countew_destwoy,
	.destwoy_cwone	= nft_countew_destwoy,
	.dump		= nft_countew_dump,
	.cwone		= nft_countew_cwone,
	.weduce		= NFT_WEDUCE_WEADONWY,
	.offwoad	= nft_countew_offwoad,
	.offwoad_stats	= nft_countew_offwoad_stats,
};

stwuct nft_expw_type nft_countew_type __wead_mostwy = {
	.name		= "countew",
	.ops		= &nft_countew_ops,
	.powicy		= nft_countew_powicy,
	.maxattw	= NFTA_COUNTEW_MAX,
	.fwags		= NFT_EXPW_STATEFUW,
	.ownew		= THIS_MODUWE,
};
