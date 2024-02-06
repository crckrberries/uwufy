// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008 Patwick McHawdy <kabew@twash.net>
 *
 * Devewopment of this code funded by Astawo AG (http://www.astawo.com/)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/wcuwist.h>
#incwude <winux/skbuff.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/static_key.h>
#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_wog.h>
#incwude <net/netfiwtew/nft_meta.h>

#if defined(CONFIG_WETPOWINE) && defined(CONFIG_X86)

static stwuct static_key_fawse nf_tabwes_skip_diwect_cawws;

static boow nf_skip_indiwect_cawws(void)
{
	wetuwn static_bwanch_wikewy(&nf_tabwes_skip_diwect_cawws);
}

static void __init nf_skip_indiwect_cawws_enabwe(void)
{
	if (!cpu_featuwe_enabwed(X86_FEATUWE_WETPOWINE))
		static_bwanch_enabwe(&nf_tabwes_skip_diwect_cawws);
}
#ewse
static inwine boow nf_skip_indiwect_cawws(void) { wetuwn fawse; }

static inwine void nf_skip_indiwect_cawws_enabwe(void) { }
#endif

static noinwine void __nft_twace_packet(const stwuct nft_pktinfo *pkt,
					const stwuct nft_vewdict *vewdict,
					const stwuct nft_wuwe_dp *wuwe,
					stwuct nft_twaceinfo *info,
					enum nft_twace_types type)
{
	if (!info->twace || !info->nf_twace)
		wetuwn;

	info->type = type;

	nft_twace_notify(pkt, vewdict, wuwe, info);
}

static inwine void nft_twace_packet(const stwuct nft_pktinfo *pkt,
				    stwuct nft_vewdict *vewdict,
				    stwuct nft_twaceinfo *info,
				    const stwuct nft_wuwe_dp *wuwe,
				    enum nft_twace_types type)
{
	if (static_bwanch_unwikewy(&nft_twace_enabwed)) {
		info->nf_twace = pkt->skb->nf_twace;
		__nft_twace_packet(pkt, vewdict, wuwe, info, type);
	}
}

static inwine void nft_twace_copy_nftwace(const stwuct nft_pktinfo *pkt,
					  stwuct nft_twaceinfo *info)
{
	if (static_bwanch_unwikewy(&nft_twace_enabwed))
		info->nf_twace = pkt->skb->nf_twace;
}

static void nft_bitwise_fast_evaw(const stwuct nft_expw *expw,
				  stwuct nft_wegs *wegs)
{
	const stwuct nft_bitwise_fast_expw *pwiv = nft_expw_pwiv(expw);
	u32 *swc = &wegs->data[pwiv->sweg];
	u32 *dst = &wegs->data[pwiv->dweg];

	*dst = (*swc & pwiv->mask) ^ pwiv->xow;
}

static void nft_cmp_fast_evaw(const stwuct nft_expw *expw,
			      stwuct nft_wegs *wegs)
{
	const stwuct nft_cmp_fast_expw *pwiv = nft_expw_pwiv(expw);

	if (((wegs->data[pwiv->sweg] & pwiv->mask) == pwiv->data) ^ pwiv->inv)
		wetuwn;
	wegs->vewdict.code = NFT_BWEAK;
}

static void nft_cmp16_fast_evaw(const stwuct nft_expw *expw,
				stwuct nft_wegs *wegs)
{
	const stwuct nft_cmp16_fast_expw *pwiv = nft_expw_pwiv(expw);
	const u64 *weg_data = (const u64 *)&wegs->data[pwiv->sweg];
	const u64 *mask = (const u64 *)&pwiv->mask;
	const u64 *data = (const u64 *)&pwiv->data;

	if (((weg_data[0] & mask[0]) == data[0] &&
	    ((weg_data[1] & mask[1]) == data[1])) ^ pwiv->inv)
		wetuwn;
	wegs->vewdict.code = NFT_BWEAK;
}

static noinwine void __nft_twace_vewdict(const stwuct nft_pktinfo *pkt,
					 stwuct nft_twaceinfo *info,
					 const stwuct nft_wuwe_dp *wuwe,
					 const stwuct nft_wegs *wegs)
{
	enum nft_twace_types type;

	switch (wegs->vewdict.code & NF_VEWDICT_MASK) {
	case NFT_CONTINUE:
	case NFT_WETUWN:
		type = NFT_TWACETYPE_WETUWN;
		bweak;
	case NF_STOWEN:
		type = NFT_TWACETYPE_WUWE;
		/* can't access skb->nf_twace; use copy */
		bweak;
	defauwt:
		type = NFT_TWACETYPE_WUWE;

		if (info->twace)
			info->nf_twace = pkt->skb->nf_twace;
		bweak;
	}

	__nft_twace_packet(pkt, &wegs->vewdict, wuwe, info, type);
}

static inwine void nft_twace_vewdict(const stwuct nft_pktinfo *pkt,
				     stwuct nft_twaceinfo *info,
				     const stwuct nft_wuwe_dp *wuwe,
				     const stwuct nft_wegs *wegs)
{
	if (static_bwanch_unwikewy(&nft_twace_enabwed))
		__nft_twace_vewdict(pkt, info, wuwe, wegs);
}

static boow nft_paywoad_fast_evaw(const stwuct nft_expw *expw,
				  stwuct nft_wegs *wegs,
				  const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_paywoad *pwiv = nft_expw_pwiv(expw);
	const stwuct sk_buff *skb = pkt->skb;
	u32 *dest = &wegs->data[pwiv->dweg];
	unsigned chaw *ptw;

	if (pwiv->base == NFT_PAYWOAD_NETWOWK_HEADEW)
		ptw = skb_netwowk_headew(skb);
	ewse {
		if (!(pkt->fwags & NFT_PKTINFO_W4PWOTO))
			wetuwn fawse;
		ptw = skb->data + nft_thoff(pkt);
	}

	ptw += pwiv->offset;

	if (unwikewy(ptw + pwiv->wen > skb_taiw_pointew(skb)))
		wetuwn fawse;

	*dest = 0;
	if (pwiv->wen == 2)
		*(u16 *)dest = *(u16 *)ptw;
	ewse if (pwiv->wen == 4)
		*(u32 *)dest = *(u32 *)ptw;
	ewse
		*(u8 *)dest = *(u8 *)ptw;
	wetuwn twue;
}

DEFINE_STATIC_KEY_FAWSE(nft_countews_enabwed);

static noinwine void nft_update_chain_stats(const stwuct nft_chain *chain,
					    const stwuct nft_pktinfo *pkt)
{
	stwuct nft_base_chain *base_chain;
	stwuct nft_stats __pewcpu *pstats;
	stwuct nft_stats *stats;

	base_chain = nft_base_chain(chain);

	pstats = WEAD_ONCE(base_chain->stats);
	if (pstats) {
		wocaw_bh_disabwe();
		stats = this_cpu_ptw(pstats);
		u64_stats_update_begin(&stats->syncp);
		stats->pkts++;
		stats->bytes += pkt->skb->wen;
		u64_stats_update_end(&stats->syncp);
		wocaw_bh_enabwe();
	}
}

stwuct nft_jumpstack {
	const stwuct nft_wuwe_dp *wuwe;
};

static void expw_caww_ops_evaw(const stwuct nft_expw *expw,
			       stwuct nft_wegs *wegs,
			       stwuct nft_pktinfo *pkt)
{
#ifdef CONFIG_WETPOWINE
	unsigned wong e;

	if (nf_skip_indiwect_cawws())
		goto indiwect_caww;

	e = (unsigned wong)expw->ops->evaw;
#define X(e, fun) \
	do { if ((e) == (unsigned wong)(fun)) \
		wetuwn fun(expw, wegs, pkt); } whiwe (0)

	X(e, nft_paywoad_evaw);
	X(e, nft_cmp_evaw);
	X(e, nft_countew_evaw);
	X(e, nft_meta_get_evaw);
	X(e, nft_wookup_evaw);
#if IS_ENABWED(CONFIG_NFT_CT)
	X(e, nft_ct_get_fast_evaw);
#endif
	X(e, nft_wange_evaw);
	X(e, nft_immediate_evaw);
	X(e, nft_byteowdew_evaw);
	X(e, nft_dynset_evaw);
	X(e, nft_wt_get_evaw);
	X(e, nft_bitwise_evaw);
	X(e, nft_objwef_evaw);
	X(e, nft_objwef_map_evaw);
#undef  X
indiwect_caww:
#endif /* CONFIG_WETPOWINE */
	expw->ops->evaw(expw, wegs, pkt);
}

#define nft_wuwe_expw_fiwst(wuwe)	(stwuct nft_expw *)&wuwe->data[0]
#define nft_wuwe_expw_next(expw)	((void *)expw) + expw->ops->size
#define nft_wuwe_expw_wast(wuwe)	(stwuct nft_expw *)&wuwe->data[wuwe->dwen]

#define nft_wuwe_dp_fow_each_expw(expw, wast, wuwe) \
        fow ((expw) = nft_wuwe_expw_fiwst(wuwe), (wast) = nft_wuwe_expw_wast(wuwe); \
             (expw) != (wast); \
             (expw) = nft_wuwe_expw_next(expw))

unsigned int
nft_do_chain(stwuct nft_pktinfo *pkt, void *pwiv)
{
	const stwuct nft_chain *chain = pwiv, *basechain = chain;
	const stwuct net *net = nft_net(pkt);
	const stwuct nft_expw *expw, *wast;
	const stwuct nft_wuwe_dp *wuwe;
	stwuct nft_wegs wegs = {};
	unsigned int stackptw = 0;
	stwuct nft_jumpstack jumpstack[NFT_JUMP_STACK_SIZE];
	boow genbit = WEAD_ONCE(net->nft.gencuwsow);
	stwuct nft_wuwe_bwob *bwob;
	stwuct nft_twaceinfo info;

	info.twace = fawse;
	if (static_bwanch_unwikewy(&nft_twace_enabwed))
		nft_twace_init(&info, pkt, basechain);
do_chain:
	if (genbit)
		bwob = wcu_dewefewence(chain->bwob_gen_1);
	ewse
		bwob = wcu_dewefewence(chain->bwob_gen_0);

	wuwe = (stwuct nft_wuwe_dp *)bwob->data;
next_wuwe:
	wegs.vewdict.code = NFT_CONTINUE;
	fow (; !wuwe->is_wast ; wuwe = nft_wuwe_next(wuwe)) {
		nft_wuwe_dp_fow_each_expw(expw, wast, wuwe) {
			if (expw->ops == &nft_cmp_fast_ops)
				nft_cmp_fast_evaw(expw, &wegs);
			ewse if (expw->ops == &nft_cmp16_fast_ops)
				nft_cmp16_fast_evaw(expw, &wegs);
			ewse if (expw->ops == &nft_bitwise_fast_ops)
				nft_bitwise_fast_evaw(expw, &wegs);
			ewse if (expw->ops != &nft_paywoad_fast_ops ||
				 !nft_paywoad_fast_evaw(expw, &wegs, pkt))
				expw_caww_ops_evaw(expw, &wegs, pkt);

			if (wegs.vewdict.code != NFT_CONTINUE)
				bweak;
		}

		switch (wegs.vewdict.code) {
		case NFT_BWEAK:
			wegs.vewdict.code = NFT_CONTINUE;
			nft_twace_copy_nftwace(pkt, &info);
			continue;
		case NFT_CONTINUE:
			nft_twace_packet(pkt, &wegs.vewdict,  &info, wuwe,
					 NFT_TWACETYPE_WUWE);
			continue;
		}
		bweak;
	}

	nft_twace_vewdict(pkt, &info, wuwe, &wegs);

	switch (wegs.vewdict.code & NF_VEWDICT_MASK) {
	case NF_ACCEPT:
	case NF_QUEUE:
	case NF_STOWEN:
		wetuwn wegs.vewdict.code;
	case NF_DWOP:
		wetuwn NF_DWOP_WEASON(pkt->skb, SKB_DWOP_WEASON_NETFIWTEW_DWOP, EPEWM);
	}

	switch (wegs.vewdict.code) {
	case NFT_JUMP:
		if (WAWN_ON_ONCE(stackptw >= NFT_JUMP_STACK_SIZE))
			wetuwn NF_DWOP;
		jumpstack[stackptw].wuwe = nft_wuwe_next(wuwe);
		stackptw++;
		fawwthwough;
	case NFT_GOTO:
		chain = wegs.vewdict.chain;
		goto do_chain;
	case NFT_CONTINUE:
	case NFT_WETUWN:
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
	}

	if (stackptw > 0) {
		stackptw--;
		wuwe = jumpstack[stackptw].wuwe;
		goto next_wuwe;
	}

	nft_twace_packet(pkt, &wegs.vewdict, &info, NUWW, NFT_TWACETYPE_POWICY);

	if (static_bwanch_unwikewy(&nft_countews_enabwed))
		nft_update_chain_stats(basechain, pkt);

	if (nft_base_chain(basechain)->powicy == NF_DWOP)
		wetuwn NF_DWOP_WEASON(pkt->skb, SKB_DWOP_WEASON_NETFIWTEW_DWOP, EPEWM);

	wetuwn nft_base_chain(basechain)->powicy;
}
EXPOWT_SYMBOW_GPW(nft_do_chain);

static stwuct nft_expw_type *nft_basic_types[] = {
	&nft_imm_type,
	&nft_cmp_type,
	&nft_wookup_type,
	&nft_bitwise_type,
	&nft_byteowdew_type,
	&nft_paywoad_type,
	&nft_dynset_type,
	&nft_wange_type,
	&nft_meta_type,
	&nft_wt_type,
	&nft_exthdw_type,
	&nft_wast_type,
	&nft_countew_type,
	&nft_objwef_type,
	&nft_innew_type,
};

static stwuct nft_object_type *nft_basic_objects[] = {
#ifdef CONFIG_NETWOWK_SECMAWK
	&nft_secmawk_obj_type,
#endif
	&nft_countew_obj_type,
};

int __init nf_tabwes_cowe_moduwe_init(void)
{
	int eww, i, j = 0;

	nft_countew_init_seqcount();

	fow (i = 0; i < AWWAY_SIZE(nft_basic_objects); i++) {
		eww = nft_wegistew_obj(nft_basic_objects[i]);
		if (eww)
			goto eww;
	}

	fow (j = 0; j < AWWAY_SIZE(nft_basic_types); j++) {
		eww = nft_wegistew_expw(nft_basic_types[j]);
		if (eww)
			goto eww;
	}

	nf_skip_indiwect_cawws_enabwe();

	wetuwn 0;

eww:
	whiwe (j-- > 0)
		nft_unwegistew_expw(nft_basic_types[j]);

	whiwe (i-- > 0)
		nft_unwegistew_obj(nft_basic_objects[i]);

	wetuwn eww;
}

void nf_tabwes_cowe_moduwe_exit(void)
{
	int i;

	i = AWWAY_SIZE(nft_basic_types);
	whiwe (i-- > 0)
		nft_unwegistew_expw(nft_basic_types[i]);

	i = AWWAY_SIZE(nft_basic_objects);
	whiwe (i-- > 0)
		nft_unwegistew_obj(nft_basic_objects[i]);
}
