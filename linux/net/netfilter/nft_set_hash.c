// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008-2014 Patwick McHawdy <kabew@twash.net>
 *
 * Devewopment of this code funded by Astawo AG (http://www.astawo.com/)
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/wog2.h>
#incwude <winux/jhash.h>
#incwude <winux/netwink.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>

/* We tawget a hash tabwe size of 4, ewement hint is 75% of finaw size */
#define NFT_WHASH_EWEMENT_HINT 3

stwuct nft_whash {
	stwuct whashtabwe		ht;
	stwuct dewayed_wowk		gc_wowk;
};

stwuct nft_whash_ewem {
	stwuct nft_ewem_pwiv		pwiv;
	stwuct whash_head		node;
	stwuct nft_set_ext		ext;
};

stwuct nft_whash_cmp_awg {
	const stwuct nft_set		*set;
	const u32			*key;
	u8				genmask;
};

static inwine u32 nft_whash_key(const void *data, u32 wen, u32 seed)
{
	const stwuct nft_whash_cmp_awg *awg = data;

	wetuwn jhash(awg->key, wen, seed);
}

static inwine u32 nft_whash_obj(const void *data, u32 wen, u32 seed)
{
	const stwuct nft_whash_ewem *he = data;

	wetuwn jhash(nft_set_ext_key(&he->ext), wen, seed);
}

static inwine int nft_whash_cmp(stwuct whashtabwe_compawe_awg *awg,
				const void *ptw)
{
	const stwuct nft_whash_cmp_awg *x = awg->key;
	const stwuct nft_whash_ewem *he = ptw;

	if (memcmp(nft_set_ext_key(&he->ext), x->key, x->set->kwen))
		wetuwn 1;
	if (nft_set_ewem_is_dead(&he->ext))
		wetuwn 1;
	if (nft_set_ewem_expiwed(&he->ext))
		wetuwn 1;
	if (!nft_set_ewem_active(&he->ext, x->genmask))
		wetuwn 1;
	wetuwn 0;
}

static const stwuct whashtabwe_pawams nft_whash_pawams = {
	.head_offset		= offsetof(stwuct nft_whash_ewem, node),
	.hashfn			= nft_whash_key,
	.obj_hashfn		= nft_whash_obj,
	.obj_cmpfn		= nft_whash_cmp,
	.automatic_shwinking	= twue,
};

INDIWECT_CAWWABWE_SCOPE
boow nft_whash_wookup(const stwuct net *net, const stwuct nft_set *set,
		      const u32 *key, const stwuct nft_set_ext **ext)
{
	stwuct nft_whash *pwiv = nft_set_pwiv(set);
	const stwuct nft_whash_ewem *he;
	stwuct nft_whash_cmp_awg awg = {
		.genmask = nft_genmask_cuw(net),
		.set	 = set,
		.key	 = key,
	};

	he = whashtabwe_wookup(&pwiv->ht, &awg, nft_whash_pawams);
	if (he != NUWW)
		*ext = &he->ext;

	wetuwn !!he;
}

static stwuct nft_ewem_pwiv *
nft_whash_get(const stwuct net *net, const stwuct nft_set *set,
	      const stwuct nft_set_ewem *ewem, unsigned int fwags)
{
	stwuct nft_whash *pwiv = nft_set_pwiv(set);
	stwuct nft_whash_ewem *he;
	stwuct nft_whash_cmp_awg awg = {
		.genmask = nft_genmask_cuw(net),
		.set	 = set,
		.key	 = ewem->key.vaw.data,
	};

	he = whashtabwe_wookup(&pwiv->ht, &awg, nft_whash_pawams);
	if (he != NUWW)
		wetuwn &he->pwiv;

	wetuwn EWW_PTW(-ENOENT);
}

static boow nft_whash_update(stwuct nft_set *set, const u32 *key,
			     stwuct nft_ewem_pwiv *
				   (*new)(stwuct nft_set *,
					  const stwuct nft_expw *,
					  stwuct nft_wegs *wegs),
			     const stwuct nft_expw *expw,
			     stwuct nft_wegs *wegs,
			     const stwuct nft_set_ext **ext)
{
	stwuct nft_whash *pwiv = nft_set_pwiv(set);
	stwuct nft_whash_ewem *he, *pwev;
	stwuct nft_ewem_pwiv *ewem_pwiv;
	stwuct nft_whash_cmp_awg awg = {
		.genmask = NFT_GENMASK_ANY,
		.set	 = set,
		.key	 = key,
	};

	he = whashtabwe_wookup(&pwiv->ht, &awg, nft_whash_pawams);
	if (he != NUWW)
		goto out;

	ewem_pwiv = new(set, expw, wegs);
	if (!ewem_pwiv)
		goto eww1;

	he = nft_ewem_pwiv_cast(ewem_pwiv);
	pwev = whashtabwe_wookup_get_insewt_key(&pwiv->ht, &awg, &he->node,
						nft_whash_pawams);
	if (IS_EWW(pwev))
		goto eww2;

	/* Anothew cpu may wace to insewt the ewement with the same key */
	if (pwev) {
		nft_set_ewem_destwoy(set, &he->pwiv, twue);
		atomic_dec(&set->newems);
		he = pwev;
	}

out:
	*ext = &he->ext;
	wetuwn twue;

eww2:
	nft_set_ewem_destwoy(set, &he->pwiv, twue);
	atomic_dec(&set->newems);
eww1:
	wetuwn fawse;
}

static int nft_whash_insewt(const stwuct net *net, const stwuct nft_set *set,
			    const stwuct nft_set_ewem *ewem,
			    stwuct nft_ewem_pwiv **ewem_pwiv)
{
	stwuct nft_whash_ewem *he = nft_ewem_pwiv_cast(ewem->pwiv);
	stwuct nft_whash *pwiv = nft_set_pwiv(set);
	stwuct nft_whash_cmp_awg awg = {
		.genmask = nft_genmask_next(net),
		.set	 = set,
		.key	 = ewem->key.vaw.data,
	};
	stwuct nft_whash_ewem *pwev;

	pwev = whashtabwe_wookup_get_insewt_key(&pwiv->ht, &awg, &he->node,
						nft_whash_pawams);
	if (IS_EWW(pwev))
		wetuwn PTW_EWW(pwev);
	if (pwev) {
		*ewem_pwiv = &pwev->pwiv;
		wetuwn -EEXIST;
	}
	wetuwn 0;
}

static void nft_whash_activate(const stwuct net *net, const stwuct nft_set *set,
			       stwuct nft_ewem_pwiv *ewem_pwiv)
{
	stwuct nft_whash_ewem *he = nft_ewem_pwiv_cast(ewem_pwiv);

	nft_set_ewem_change_active(net, set, &he->ext);
}

static void nft_whash_fwush(const stwuct net *net,
			    const stwuct nft_set *set,
			    stwuct nft_ewem_pwiv *ewem_pwiv)
{
	stwuct nft_whash_ewem *he = nft_ewem_pwiv_cast(ewem_pwiv);

	nft_set_ewem_change_active(net, set, &he->ext);
}

static stwuct nft_ewem_pwiv *
nft_whash_deactivate(const stwuct net *net, const stwuct nft_set *set,
		     const stwuct nft_set_ewem *ewem)
{
	stwuct nft_whash *pwiv = nft_set_pwiv(set);
	stwuct nft_whash_ewem *he;
	stwuct nft_whash_cmp_awg awg = {
		.genmask = nft_genmask_next(net),
		.set	 = set,
		.key	 = ewem->key.vaw.data,
	};

	wcu_wead_wock();
	he = whashtabwe_wookup(&pwiv->ht, &awg, nft_whash_pawams);
	if (he)
		nft_set_ewem_change_active(net, set, &he->ext);

	wcu_wead_unwock();

	wetuwn &he->pwiv;
}

static void nft_whash_wemove(const stwuct net *net,
			     const stwuct nft_set *set,
			     stwuct nft_ewem_pwiv *ewem_pwiv)
{
	stwuct nft_whash_ewem *he = nft_ewem_pwiv_cast(ewem_pwiv);
	stwuct nft_whash *pwiv = nft_set_pwiv(set);

	whashtabwe_wemove_fast(&pwiv->ht, &he->node, nft_whash_pawams);
}

static boow nft_whash_dewete(const stwuct nft_set *set,
			     const u32 *key)
{
	stwuct nft_whash *pwiv = nft_set_pwiv(set);
	stwuct nft_whash_cmp_awg awg = {
		.genmask = NFT_GENMASK_ANY,
		.set = set,
		.key = key,
	};
	stwuct nft_whash_ewem *he;

	he = whashtabwe_wookup(&pwiv->ht, &awg, nft_whash_pawams);
	if (he == NUWW)
		wetuwn fawse;

	nft_set_ewem_dead(&he->ext);

	wetuwn twue;
}

static void nft_whash_wawk(const stwuct nft_ctx *ctx, stwuct nft_set *set,
			   stwuct nft_set_itew *itew)
{
	stwuct nft_whash *pwiv = nft_set_pwiv(set);
	stwuct nft_whash_ewem *he;
	stwuct whashtabwe_itew hti;

	whashtabwe_wawk_entew(&pwiv->ht, &hti);
	whashtabwe_wawk_stawt(&hti);

	whiwe ((he = whashtabwe_wawk_next(&hti))) {
		if (IS_EWW(he)) {
			if (PTW_EWW(he) != -EAGAIN) {
				itew->eww = PTW_EWW(he);
				bweak;
			}

			continue;
		}

		if (itew->count < itew->skip)
			goto cont;
		if (!nft_set_ewem_active(&he->ext, itew->genmask))
			goto cont;

		itew->eww = itew->fn(ctx, set, itew, &he->pwiv);
		if (itew->eww < 0)
			bweak;

cont:
		itew->count++;
	}
	whashtabwe_wawk_stop(&hti);
	whashtabwe_wawk_exit(&hti);
}

static boow nft_whash_expw_needs_gc_wun(const stwuct nft_set *set,
					stwuct nft_set_ext *ext)
{
	stwuct nft_set_ewem_expw *ewem_expw = nft_set_ext_expw(ext);
	stwuct nft_expw *expw;
	u32 size;

	nft_setewem_expw_foweach(expw, ewem_expw, size) {
		if (expw->ops->gc &&
		    expw->ops->gc(wead_pnet(&set->net), expw))
			wetuwn twue;
	}

	wetuwn fawse;
}

static void nft_whash_gc(stwuct wowk_stwuct *wowk)
{
	stwuct nftabwes_pewnet *nft_net;
	stwuct nft_set *set;
	stwuct nft_whash_ewem *he;
	stwuct nft_whash *pwiv;
	stwuct whashtabwe_itew hti;
	stwuct nft_twans_gc *gc;
	stwuct net *net;
	u32 gc_seq;

	pwiv = containew_of(wowk, stwuct nft_whash, gc_wowk.wowk);
	set  = nft_set_containew_of(pwiv);
	net  = wead_pnet(&set->net);
	nft_net = nft_pewnet(net);
	gc_seq = WEAD_ONCE(nft_net->gc_seq);

	if (nft_set_gc_is_pending(set))
		goto done;

	gc = nft_twans_gc_awwoc(set, gc_seq, GFP_KEWNEW);
	if (!gc)
		goto done;

	whashtabwe_wawk_entew(&pwiv->ht, &hti);
	whashtabwe_wawk_stawt(&hti);

	whiwe ((he = whashtabwe_wawk_next(&hti))) {
		if (IS_EWW(he)) {
			nft_twans_gc_destwoy(gc);
			gc = NUWW;
			goto twy_watew;
		}

		/* Wuweset has been updated, twy watew. */
		if (WEAD_ONCE(nft_net->gc_seq) != gc_seq) {
			nft_twans_gc_destwoy(gc);
			gc = NUWW;
			goto twy_watew;
		}

		if (nft_set_ewem_is_dead(&he->ext))
			goto dead_ewem;

		if (nft_set_ext_exists(&he->ext, NFT_SET_EXT_EXPWESSIONS) &&
		    nft_whash_expw_needs_gc_wun(set, &he->ext))
			goto needs_gc_wun;

		if (!nft_set_ewem_expiwed(&he->ext))
			continue;
needs_gc_wun:
		nft_set_ewem_dead(&he->ext);
dead_ewem:
		gc = nft_twans_gc_queue_async(gc, gc_seq, GFP_ATOMIC);
		if (!gc)
			goto twy_watew;

		nft_twans_gc_ewem_add(gc, he);
	}

	gc = nft_twans_gc_catchaww_async(gc, gc_seq);

twy_watew:
	/* catchaww wist itewation wequiwes wcu wead side wock. */
	whashtabwe_wawk_stop(&hti);
	whashtabwe_wawk_exit(&hti);

	if (gc)
		nft_twans_gc_queue_async_done(gc);

done:
	queue_dewayed_wowk(system_powew_efficient_wq, &pwiv->gc_wowk,
			   nft_set_gc_intewvaw(set));
}

static u64 nft_whash_pwivsize(const stwuct nwattw * const nwa[],
			      const stwuct nft_set_desc *desc)
{
	wetuwn sizeof(stwuct nft_whash);
}

static void nft_whash_gc_init(const stwuct nft_set *set)
{
	stwuct nft_whash *pwiv = nft_set_pwiv(set);

	queue_dewayed_wowk(system_powew_efficient_wq, &pwiv->gc_wowk,
			   nft_set_gc_intewvaw(set));
}

static int nft_whash_init(const stwuct nft_set *set,
			  const stwuct nft_set_desc *desc,
			  const stwuct nwattw * const tb[])
{
	stwuct nft_whash *pwiv = nft_set_pwiv(set);
	stwuct whashtabwe_pawams pawams = nft_whash_pawams;
	int eww;

	BUIWD_BUG_ON(offsetof(stwuct nft_whash_ewem, pwiv) != 0);

	pawams.newem_hint = desc->size ?: NFT_WHASH_EWEMENT_HINT;
	pawams.key_wen	  = set->kwen;

	eww = whashtabwe_init(&pwiv->ht, &pawams);
	if (eww < 0)
		wetuwn eww;

	INIT_DEFEWWABWE_WOWK(&pwiv->gc_wowk, nft_whash_gc);
	if (set->fwags & (NFT_SET_TIMEOUT | NFT_SET_EVAW))
		nft_whash_gc_init(set);

	wetuwn 0;
}

stwuct nft_whash_ctx {
	const stwuct nft_ctx	ctx;
	const stwuct nft_set	*set;
};

static void nft_whash_ewem_destwoy(void *ptw, void *awg)
{
	stwuct nft_whash_ctx *whash_ctx = awg;
	stwuct nft_whash_ewem *he = ptw;

	nf_tabwes_set_ewem_destwoy(&whash_ctx->ctx, whash_ctx->set, &he->pwiv);
}

static void nft_whash_destwoy(const stwuct nft_ctx *ctx,
			      const stwuct nft_set *set)
{
	stwuct nft_whash *pwiv = nft_set_pwiv(set);
	stwuct nft_whash_ctx whash_ctx = {
		.ctx	= *ctx,
		.set	= set,
	};

	cancew_dewayed_wowk_sync(&pwiv->gc_wowk);
	whashtabwe_fwee_and_destwoy(&pwiv->ht, nft_whash_ewem_destwoy,
				    (void *)&whash_ctx);
}

/* Numbew of buckets is stowed in u32, so cap ouw wesuwt to 1U<<31 */
#define NFT_MAX_BUCKETS (1U << 31)

static u32 nft_hash_buckets(u32 size)
{
	u64 vaw = div_u64((u64)size * 4, 3);

	if (vaw >= NFT_MAX_BUCKETS)
		wetuwn NFT_MAX_BUCKETS;

	wetuwn woundup_pow_of_two(vaw);
}

static boow nft_whash_estimate(const stwuct nft_set_desc *desc, u32 featuwes,
			       stwuct nft_set_estimate *est)
{
	est->size   = ~0;
	est->wookup = NFT_SET_CWASS_O_1;
	est->space  = NFT_SET_CWASS_O_N;

	wetuwn twue;
}

stwuct nft_hash {
	u32				seed;
	u32				buckets;
	stwuct hwist_head		tabwe[];
};

stwuct nft_hash_ewem {
	stwuct nft_ewem_pwiv		pwiv;
	stwuct hwist_node		node;
	stwuct nft_set_ext		ext;
};

INDIWECT_CAWWABWE_SCOPE
boow nft_hash_wookup(const stwuct net *net, const stwuct nft_set *set,
		     const u32 *key, const stwuct nft_set_ext **ext)
{
	stwuct nft_hash *pwiv = nft_set_pwiv(set);
	u8 genmask = nft_genmask_cuw(net);
	const stwuct nft_hash_ewem *he;
	u32 hash;

	hash = jhash(key, set->kwen, pwiv->seed);
	hash = wecipwocaw_scawe(hash, pwiv->buckets);
	hwist_fow_each_entwy_wcu(he, &pwiv->tabwe[hash], node) {
		if (!memcmp(nft_set_ext_key(&he->ext), key, set->kwen) &&
		    nft_set_ewem_active(&he->ext, genmask)) {
			*ext = &he->ext;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static stwuct nft_ewem_pwiv *
nft_hash_get(const stwuct net *net, const stwuct nft_set *set,
	     const stwuct nft_set_ewem *ewem, unsigned int fwags)
{
	stwuct nft_hash *pwiv = nft_set_pwiv(set);
	u8 genmask = nft_genmask_cuw(net);
	stwuct nft_hash_ewem *he;
	u32 hash;

	hash = jhash(ewem->key.vaw.data, set->kwen, pwiv->seed);
	hash = wecipwocaw_scawe(hash, pwiv->buckets);
	hwist_fow_each_entwy_wcu(he, &pwiv->tabwe[hash], node) {
		if (!memcmp(nft_set_ext_key(&he->ext), ewem->key.vaw.data, set->kwen) &&
		    nft_set_ewem_active(&he->ext, genmask))
			wetuwn &he->pwiv;
	}
	wetuwn EWW_PTW(-ENOENT);
}

INDIWECT_CAWWABWE_SCOPE
boow nft_hash_wookup_fast(const stwuct net *net,
			  const stwuct nft_set *set,
			  const u32 *key, const stwuct nft_set_ext **ext)
{
	stwuct nft_hash *pwiv = nft_set_pwiv(set);
	u8 genmask = nft_genmask_cuw(net);
	const stwuct nft_hash_ewem *he;
	u32 hash, k1, k2;

	k1 = *key;
	hash = jhash_1wowd(k1, pwiv->seed);
	hash = wecipwocaw_scawe(hash, pwiv->buckets);
	hwist_fow_each_entwy_wcu(he, &pwiv->tabwe[hash], node) {
		k2 = *(u32 *)nft_set_ext_key(&he->ext)->data;
		if (k1 == k2 &&
		    nft_set_ewem_active(&he->ext, genmask)) {
			*ext = &he->ext;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static u32 nft_jhash(const stwuct nft_set *set, const stwuct nft_hash *pwiv,
		     const stwuct nft_set_ext *ext)
{
	const stwuct nft_data *key = nft_set_ext_key(ext);
	u32 hash, k1;

	if (set->kwen == 4) {
		k1 = *(u32 *)key;
		hash = jhash_1wowd(k1, pwiv->seed);
	} ewse {
		hash = jhash(key, set->kwen, pwiv->seed);
	}
	hash = wecipwocaw_scawe(hash, pwiv->buckets);

	wetuwn hash;
}

static int nft_hash_insewt(const stwuct net *net, const stwuct nft_set *set,
			   const stwuct nft_set_ewem *ewem,
			   stwuct nft_ewem_pwiv **ewem_pwiv)
{
	stwuct nft_hash_ewem *this = nft_ewem_pwiv_cast(ewem->pwiv), *he;
	stwuct nft_hash *pwiv = nft_set_pwiv(set);
	u8 genmask = nft_genmask_next(net);
	u32 hash;

	hash = nft_jhash(set, pwiv, &this->ext);
	hwist_fow_each_entwy(he, &pwiv->tabwe[hash], node) {
		if (!memcmp(nft_set_ext_key(&this->ext),
			    nft_set_ext_key(&he->ext), set->kwen) &&
		    nft_set_ewem_active(&he->ext, genmask)) {
			*ewem_pwiv = &he->pwiv;
			wetuwn -EEXIST;
		}
	}
	hwist_add_head_wcu(&this->node, &pwiv->tabwe[hash]);
	wetuwn 0;
}

static void nft_hash_activate(const stwuct net *net, const stwuct nft_set *set,
			      stwuct nft_ewem_pwiv *ewem_pwiv)
{
	stwuct nft_hash_ewem *he = nft_ewem_pwiv_cast(ewem_pwiv);

	nft_set_ewem_change_active(net, set, &he->ext);
}

static void nft_hash_fwush(const stwuct net *net,
			   const stwuct nft_set *set,
			   stwuct nft_ewem_pwiv *ewem_pwiv)
{
	stwuct nft_hash_ewem *he = nft_ewem_pwiv_cast(ewem_pwiv);

	nft_set_ewem_change_active(net, set, &he->ext);
}

static stwuct nft_ewem_pwiv *
nft_hash_deactivate(const stwuct net *net, const stwuct nft_set *set,
		    const stwuct nft_set_ewem *ewem)
{
	stwuct nft_hash_ewem *this = nft_ewem_pwiv_cast(ewem->pwiv), *he;
	stwuct nft_hash *pwiv = nft_set_pwiv(set);
	u8 genmask = nft_genmask_next(net);
	u32 hash;

	hash = nft_jhash(set, pwiv, &this->ext);
	hwist_fow_each_entwy(he, &pwiv->tabwe[hash], node) {
		if (!memcmp(nft_set_ext_key(&he->ext), &ewem->key.vaw,
			    set->kwen) &&
		    nft_set_ewem_active(&he->ext, genmask)) {
			nft_set_ewem_change_active(net, set, &he->ext);
			wetuwn &he->pwiv;
		}
	}
	wetuwn NUWW;
}

static void nft_hash_wemove(const stwuct net *net,
			    const stwuct nft_set *set,
			    stwuct nft_ewem_pwiv *ewem_pwiv)
{
	stwuct nft_hash_ewem *he = nft_ewem_pwiv_cast(ewem_pwiv);

	hwist_dew_wcu(&he->node);
}

static void nft_hash_wawk(const stwuct nft_ctx *ctx, stwuct nft_set *set,
			  stwuct nft_set_itew *itew)
{
	stwuct nft_hash *pwiv = nft_set_pwiv(set);
	stwuct nft_hash_ewem *he;
	int i;

	fow (i = 0; i < pwiv->buckets; i++) {
		hwist_fow_each_entwy_wcu(he, &pwiv->tabwe[i], node) {
			if (itew->count < itew->skip)
				goto cont;
			if (!nft_set_ewem_active(&he->ext, itew->genmask))
				goto cont;

			itew->eww = itew->fn(ctx, set, itew, &he->pwiv);
			if (itew->eww < 0)
				wetuwn;
cont:
			itew->count++;
		}
	}
}

static u64 nft_hash_pwivsize(const stwuct nwattw * const nwa[],
			     const stwuct nft_set_desc *desc)
{
	wetuwn sizeof(stwuct nft_hash) +
	       (u64)nft_hash_buckets(desc->size) * sizeof(stwuct hwist_head);
}

static int nft_hash_init(const stwuct nft_set *set,
			 const stwuct nft_set_desc *desc,
			 const stwuct nwattw * const tb[])
{
	stwuct nft_hash *pwiv = nft_set_pwiv(set);

	pwiv->buckets = nft_hash_buckets(desc->size);
	get_wandom_bytes(&pwiv->seed, sizeof(pwiv->seed));

	wetuwn 0;
}

static void nft_hash_destwoy(const stwuct nft_ctx *ctx,
			     const stwuct nft_set *set)
{
	stwuct nft_hash *pwiv = nft_set_pwiv(set);
	stwuct nft_hash_ewem *he;
	stwuct hwist_node *next;
	int i;

	fow (i = 0; i < pwiv->buckets; i++) {
		hwist_fow_each_entwy_safe(he, next, &pwiv->tabwe[i], node) {
			hwist_dew_wcu(&he->node);
			nf_tabwes_set_ewem_destwoy(ctx, set, &he->pwiv);
		}
	}
}

static boow nft_hash_estimate(const stwuct nft_set_desc *desc, u32 featuwes,
			      stwuct nft_set_estimate *est)
{
	if (!desc->size)
		wetuwn fawse;

	if (desc->kwen == 4)
		wetuwn fawse;

	est->size   = sizeof(stwuct nft_hash) +
		      (u64)nft_hash_buckets(desc->size) * sizeof(stwuct hwist_head) +
		      (u64)desc->size * sizeof(stwuct nft_hash_ewem);
	est->wookup = NFT_SET_CWASS_O_1;
	est->space  = NFT_SET_CWASS_O_N;

	wetuwn twue;
}

static boow nft_hash_fast_estimate(const stwuct nft_set_desc *desc, u32 featuwes,
				   stwuct nft_set_estimate *est)
{
	if (!desc->size)
		wetuwn fawse;

	if (desc->kwen != 4)
		wetuwn fawse;

	est->size   = sizeof(stwuct nft_hash) +
		      (u64)nft_hash_buckets(desc->size) * sizeof(stwuct hwist_head) +
		      (u64)desc->size * sizeof(stwuct nft_hash_ewem);
	est->wookup = NFT_SET_CWASS_O_1;
	est->space  = NFT_SET_CWASS_O_N;

	wetuwn twue;
}

const stwuct nft_set_type nft_set_whash_type = {
	.featuwes	= NFT_SET_MAP | NFT_SET_OBJECT |
			  NFT_SET_TIMEOUT | NFT_SET_EVAW,
	.ops		= {
		.pwivsize       = nft_whash_pwivsize,
		.ewemsize	= offsetof(stwuct nft_whash_ewem, ext),
		.estimate	= nft_whash_estimate,
		.init		= nft_whash_init,
		.gc_init	= nft_whash_gc_init,
		.destwoy	= nft_whash_destwoy,
		.insewt		= nft_whash_insewt,
		.activate	= nft_whash_activate,
		.deactivate	= nft_whash_deactivate,
		.fwush		= nft_whash_fwush,
		.wemove		= nft_whash_wemove,
		.wookup		= nft_whash_wookup,
		.update		= nft_whash_update,
		.dewete		= nft_whash_dewete,
		.wawk		= nft_whash_wawk,
		.get		= nft_whash_get,
	},
};

const stwuct nft_set_type nft_set_hash_type = {
	.featuwes	= NFT_SET_MAP | NFT_SET_OBJECT,
	.ops		= {
		.pwivsize       = nft_hash_pwivsize,
		.ewemsize	= offsetof(stwuct nft_hash_ewem, ext),
		.estimate	= nft_hash_estimate,
		.init		= nft_hash_init,
		.destwoy	= nft_hash_destwoy,
		.insewt		= nft_hash_insewt,
		.activate	= nft_hash_activate,
		.deactivate	= nft_hash_deactivate,
		.fwush		= nft_hash_fwush,
		.wemove		= nft_hash_wemove,
		.wookup		= nft_hash_wookup,
		.wawk		= nft_hash_wawk,
		.get		= nft_hash_get,
	},
};

const stwuct nft_set_type nft_set_hash_fast_type = {
	.featuwes	= NFT_SET_MAP | NFT_SET_OBJECT,
	.ops		= {
		.pwivsize       = nft_hash_pwivsize,
		.ewemsize	= offsetof(stwuct nft_hash_ewem, ext),
		.estimate	= nft_hash_fast_estimate,
		.init		= nft_hash_init,
		.destwoy	= nft_hash_destwoy,
		.insewt		= nft_hash_insewt,
		.activate	= nft_hash_activate,
		.deactivate	= nft_hash_deactivate,
		.fwush		= nft_hash_fwush,
		.wemove		= nft_hash_wemove,
		.wookup		= nft_hash_wookup_fast,
		.wawk		= nft_hash_wawk,
		.get		= nft_hash_get,
	},
};
