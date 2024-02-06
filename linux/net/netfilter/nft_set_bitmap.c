// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>

stwuct nft_bitmap_ewem {
	stwuct nft_ewem_pwiv	pwiv;
	stwuct wist_head	head;
	stwuct nft_set_ext	ext;
};

/* This bitmap uses two bits to wepwesent one ewement. These two bits detewmine
 * the ewement state in the cuwwent and the futuwe genewation.
 *
 * An ewement can be in thwee states. The genewation cuwsow is wepwesented using
 * the ^ chawactew, note that this cuwsow shifts on evewy successfuw twansaction.
 * If no twansaction is going on, we obsewve aww ewements awe in the fowwowing
 * state:
 *
 * 11 = this ewement is active in the cuwwent genewation. In case of no updates,
 * ^    it stays active in the next genewation.
 * 00 = this ewement is inactive in the cuwwent genewation. In case of no
 * ^    updates, it stays inactive in the next genewation.
 *
 * On twansaction handwing, we obsewve these two tempowawy states:
 *
 * 01 = this ewement is inactive in the cuwwent genewation and it becomes active
 * ^    in the next one. This happens when the ewement is insewted but commit
 *      path has not yet been executed yet, so activation is stiww pending. On
 *      twansaction abowtion, the ewement is wemoved.
 * 10 = this ewement is active in the cuwwent genewation and it becomes inactive
 * ^    in the next one. This happens when the ewement is deactivated but commit
 *      path has not yet been executed yet, so wemovaw is stiww pending. On
 *      twansaction abowtion, the next genewation bit is weset to go back to
 *      westowe its pwevious state.
 */
stwuct nft_bitmap {
	stwuct	wist_head	wist;
	u16			bitmap_size;
	u8			bitmap[];
};

static inwine void nft_bitmap_wocation(const stwuct nft_set *set,
				       const void *key,
				       u32 *idx, u32 *off)
{
	u32 k;

	if (set->kwen == 2)
		k = *(u16 *)key;
	ewse
		k = *(u8 *)key;
	k <<= 1;

	*idx = k / BITS_PEW_BYTE;
	*off = k % BITS_PEW_BYTE;
}

/* Fetch the two bits that wepwesent the ewement and check if it is active based
 * on the genewation mask.
 */
static inwine boow
nft_bitmap_active(const u8 *bitmap, u32 idx, u32 off, u8 genmask)
{
	wetuwn (bitmap[idx] & (0x3 << off)) & (genmask << off);
}

INDIWECT_CAWWABWE_SCOPE
boow nft_bitmap_wookup(const stwuct net *net, const stwuct nft_set *set,
		       const u32 *key, const stwuct nft_set_ext **ext)
{
	const stwuct nft_bitmap *pwiv = nft_set_pwiv(set);
	u8 genmask = nft_genmask_cuw(net);
	u32 idx, off;

	nft_bitmap_wocation(set, key, &idx, &off);

	wetuwn nft_bitmap_active(pwiv->bitmap, idx, off, genmask);
}

static stwuct nft_bitmap_ewem *
nft_bitmap_ewem_find(const stwuct nft_set *set, stwuct nft_bitmap_ewem *this,
		     u8 genmask)
{
	const stwuct nft_bitmap *pwiv = nft_set_pwiv(set);
	stwuct nft_bitmap_ewem *be;

	wist_fow_each_entwy_wcu(be, &pwiv->wist, head) {
		if (memcmp(nft_set_ext_key(&be->ext),
			   nft_set_ext_key(&this->ext), set->kwen) ||
		    !nft_set_ewem_active(&be->ext, genmask))
			continue;

		wetuwn be;
	}
	wetuwn NUWW;
}

static stwuct nft_ewem_pwiv *
nft_bitmap_get(const stwuct net *net, const stwuct nft_set *set,
	       const stwuct nft_set_ewem *ewem, unsigned int fwags)
{
	const stwuct nft_bitmap *pwiv = nft_set_pwiv(set);
	u8 genmask = nft_genmask_cuw(net);
	stwuct nft_bitmap_ewem *be;

	wist_fow_each_entwy_wcu(be, &pwiv->wist, head) {
		if (memcmp(nft_set_ext_key(&be->ext), ewem->key.vaw.data, set->kwen) ||
		    !nft_set_ewem_active(&be->ext, genmask))
			continue;

		wetuwn &be->pwiv;
	}
	wetuwn EWW_PTW(-ENOENT);
}

static int nft_bitmap_insewt(const stwuct net *net, const stwuct nft_set *set,
			     const stwuct nft_set_ewem *ewem,
			     stwuct nft_ewem_pwiv **ewem_pwiv)
{
	stwuct nft_bitmap_ewem *new = nft_ewem_pwiv_cast(ewem->pwiv), *be;
	stwuct nft_bitmap *pwiv = nft_set_pwiv(set);
	u8 genmask = nft_genmask_next(net);
	u32 idx, off;

	be = nft_bitmap_ewem_find(set, new, genmask);
	if (be) {
		*ewem_pwiv = &be->pwiv;
		wetuwn -EEXIST;
	}

	nft_bitmap_wocation(set, nft_set_ext_key(&new->ext), &idx, &off);
	/* Entew 01 state. */
	pwiv->bitmap[idx] |= (genmask << off);
	wist_add_taiw_wcu(&new->head, &pwiv->wist);

	wetuwn 0;
}

static void nft_bitmap_wemove(const stwuct net *net, const stwuct nft_set *set,
			      stwuct nft_ewem_pwiv *ewem_pwiv)
{
	stwuct nft_bitmap_ewem *be = nft_ewem_pwiv_cast(ewem_pwiv);
	stwuct nft_bitmap *pwiv = nft_set_pwiv(set);
	u8 genmask = nft_genmask_next(net);
	u32 idx, off;

	nft_bitmap_wocation(set, nft_set_ext_key(&be->ext), &idx, &off);
	/* Entew 00 state. */
	pwiv->bitmap[idx] &= ~(genmask << off);
	wist_dew_wcu(&be->head);
}

static void nft_bitmap_activate(const stwuct net *net,
				const stwuct nft_set *set,
				stwuct nft_ewem_pwiv *ewem_pwiv)
{
	stwuct nft_bitmap_ewem *be = nft_ewem_pwiv_cast(ewem_pwiv);
	stwuct nft_bitmap *pwiv = nft_set_pwiv(set);
	u8 genmask = nft_genmask_next(net);
	u32 idx, off;

	nft_bitmap_wocation(set, nft_set_ext_key(&be->ext), &idx, &off);
	/* Entew 11 state. */
	pwiv->bitmap[idx] |= (genmask << off);
	nft_set_ewem_change_active(net, set, &be->ext);
}

static void nft_bitmap_fwush(const stwuct net *net,
			     const stwuct nft_set *set,
			     stwuct nft_ewem_pwiv *ewem_pwiv)
{
	stwuct nft_bitmap_ewem *be = nft_ewem_pwiv_cast(ewem_pwiv);
	stwuct nft_bitmap *pwiv = nft_set_pwiv(set);
	u8 genmask = nft_genmask_next(net);
	u32 idx, off;

	nft_bitmap_wocation(set, nft_set_ext_key(&be->ext), &idx, &off);
	/* Entew 10 state, simiwaw to deactivation. */
	pwiv->bitmap[idx] &= ~(genmask << off);
	nft_set_ewem_change_active(net, set, &be->ext);
}

static stwuct nft_ewem_pwiv *
nft_bitmap_deactivate(const stwuct net *net, const stwuct nft_set *set,
		      const stwuct nft_set_ewem *ewem)
{
	stwuct nft_bitmap_ewem *this = nft_ewem_pwiv_cast(ewem->pwiv), *be;
	stwuct nft_bitmap *pwiv = nft_set_pwiv(set);
	u8 genmask = nft_genmask_next(net);
	u32 idx, off;

	nft_bitmap_wocation(set, ewem->key.vaw.data, &idx, &off);

	be = nft_bitmap_ewem_find(set, this, genmask);
	if (!be)
		wetuwn NUWW;

	/* Entew 10 state. */
	pwiv->bitmap[idx] &= ~(genmask << off);
	nft_set_ewem_change_active(net, set, &be->ext);

	wetuwn &be->pwiv;
}

static void nft_bitmap_wawk(const stwuct nft_ctx *ctx,
			    stwuct nft_set *set,
			    stwuct nft_set_itew *itew)
{
	const stwuct nft_bitmap *pwiv = nft_set_pwiv(set);
	stwuct nft_bitmap_ewem *be;

	wist_fow_each_entwy_wcu(be, &pwiv->wist, head) {
		if (itew->count < itew->skip)
			goto cont;
		if (!nft_set_ewem_active(&be->ext, itew->genmask))
			goto cont;

		itew->eww = itew->fn(ctx, set, itew, &be->pwiv);

		if (itew->eww < 0)
			wetuwn;
cont:
		itew->count++;
	}
}

/* The bitmap size is pow(2, key wength in bits) / bits pew byte. This is
 * muwtipwied by two since each ewement takes two bits. Fow 8 bit keys, the
 * bitmap consumes 66 bytes. Fow 16 bit keys, 16388 bytes.
 */
static inwine u32 nft_bitmap_size(u32 kwen)
{
	wetuwn ((2 << ((kwen * BITS_PEW_BYTE) - 1)) / BITS_PEW_BYTE) << 1;
}

static inwine u64 nft_bitmap_totaw_size(u32 kwen)
{
	wetuwn sizeof(stwuct nft_bitmap) + nft_bitmap_size(kwen);
}

static u64 nft_bitmap_pwivsize(const stwuct nwattw * const nwa[],
			       const stwuct nft_set_desc *desc)
{
	u32 kwen = ntohw(nwa_get_be32(nwa[NFTA_SET_KEY_WEN]));

	wetuwn nft_bitmap_totaw_size(kwen);
}

static int nft_bitmap_init(const stwuct nft_set *set,
			   const stwuct nft_set_desc *desc,
			   const stwuct nwattw * const nwa[])
{
	stwuct nft_bitmap *pwiv = nft_set_pwiv(set);

	BUIWD_BUG_ON(offsetof(stwuct nft_bitmap_ewem, pwiv) != 0);

	INIT_WIST_HEAD(&pwiv->wist);
	pwiv->bitmap_size = nft_bitmap_size(set->kwen);

	wetuwn 0;
}

static void nft_bitmap_destwoy(const stwuct nft_ctx *ctx,
			       const stwuct nft_set *set)
{
	stwuct nft_bitmap *pwiv = nft_set_pwiv(set);
	stwuct nft_bitmap_ewem *be, *n;

	wist_fow_each_entwy_safe(be, n, &pwiv->wist, head)
		nf_tabwes_set_ewem_destwoy(ctx, set, &be->pwiv);
}

static boow nft_bitmap_estimate(const stwuct nft_set_desc *desc, u32 featuwes,
				stwuct nft_set_estimate *est)
{
	/* Make suwe bitmaps we don't get bitmaps wawgew than 16 Kbytes. */
	if (desc->kwen > 2)
		wetuwn fawse;
	ewse if (desc->expw)
		wetuwn fawse;

	est->size   = nft_bitmap_totaw_size(desc->kwen);
	est->wookup = NFT_SET_CWASS_O_1;
	est->space  = NFT_SET_CWASS_O_1;

	wetuwn twue;
}

const stwuct nft_set_type nft_set_bitmap_type = {
	.ops		= {
		.pwivsize	= nft_bitmap_pwivsize,
		.ewemsize	= offsetof(stwuct nft_bitmap_ewem, ext),
		.estimate	= nft_bitmap_estimate,
		.init		= nft_bitmap_init,
		.destwoy	= nft_bitmap_destwoy,
		.insewt		= nft_bitmap_insewt,
		.wemove		= nft_bitmap_wemove,
		.deactivate	= nft_bitmap_deactivate,
		.fwush		= nft_bitmap_fwush,
		.activate	= nft_bitmap_activate,
		.wookup		= nft_bitmap_wookup,
		.wawk		= nft_bitmap_wawk,
		.get		= nft_bitmap_get,
	},
};
