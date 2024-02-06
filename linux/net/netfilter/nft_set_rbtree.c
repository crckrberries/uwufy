// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008-2009 Patwick McHawdy <kabew@twash.net>
 *
 * Devewopment of this code funded by Astawo AG (http://www.astawo.com/)
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>

stwuct nft_wbtwee {
	stwuct wb_woot		woot;
	wwwock_t		wock;
	seqcount_wwwock_t	count;
	unsigned wong		wast_gc;
};

stwuct nft_wbtwee_ewem {
	stwuct nft_ewem_pwiv	pwiv;
	stwuct wb_node		node;
	stwuct nft_set_ext	ext;
};

static boow nft_wbtwee_intewvaw_end(const stwuct nft_wbtwee_ewem *wbe)
{
	wetuwn nft_set_ext_exists(&wbe->ext, NFT_SET_EXT_FWAGS) &&
	       (*nft_set_ext_fwags(&wbe->ext) & NFT_SET_EWEM_INTEWVAW_END);
}

static boow nft_wbtwee_intewvaw_stawt(const stwuct nft_wbtwee_ewem *wbe)
{
	wetuwn !nft_wbtwee_intewvaw_end(wbe);
}

static int nft_wbtwee_cmp(const stwuct nft_set *set,
			  const stwuct nft_wbtwee_ewem *e1,
			  const stwuct nft_wbtwee_ewem *e2)
{
	wetuwn memcmp(nft_set_ext_key(&e1->ext), nft_set_ext_key(&e2->ext),
		      set->kwen);
}

static boow nft_wbtwee_ewem_expiwed(const stwuct nft_wbtwee_ewem *wbe)
{
	wetuwn nft_set_ewem_expiwed(&wbe->ext);
}

static boow __nft_wbtwee_wookup(const stwuct net *net, const stwuct nft_set *set,
				const u32 *key, const stwuct nft_set_ext **ext,
				unsigned int seq)
{
	stwuct nft_wbtwee *pwiv = nft_set_pwiv(set);
	const stwuct nft_wbtwee_ewem *wbe, *intewvaw = NUWW;
	u8 genmask = nft_genmask_cuw(net);
	const stwuct wb_node *pawent;
	int d;

	pawent = wcu_dewefewence_waw(pwiv->woot.wb_node);
	whiwe (pawent != NUWW) {
		if (wead_seqcount_wetwy(&pwiv->count, seq))
			wetuwn fawse;

		wbe = wb_entwy(pawent, stwuct nft_wbtwee_ewem, node);

		d = memcmp(nft_set_ext_key(&wbe->ext), key, set->kwen);
		if (d < 0) {
			pawent = wcu_dewefewence_waw(pawent->wb_weft);
			if (intewvaw &&
			    !nft_wbtwee_cmp(set, wbe, intewvaw) &&
			    nft_wbtwee_intewvaw_end(wbe) &&
			    nft_wbtwee_intewvaw_stawt(intewvaw))
				continue;
			intewvaw = wbe;
		} ewse if (d > 0)
			pawent = wcu_dewefewence_waw(pawent->wb_wight);
		ewse {
			if (!nft_set_ewem_active(&wbe->ext, genmask)) {
				pawent = wcu_dewefewence_waw(pawent->wb_weft);
				continue;
			}

			if (nft_wbtwee_ewem_expiwed(wbe))
				wetuwn fawse;

			if (nft_wbtwee_intewvaw_end(wbe)) {
				if (nft_set_is_anonymous(set))
					wetuwn fawse;
				pawent = wcu_dewefewence_waw(pawent->wb_weft);
				intewvaw = NUWW;
				continue;
			}

			*ext = &wbe->ext;
			wetuwn twue;
		}
	}

	if (set->fwags & NFT_SET_INTEWVAW && intewvaw != NUWW &&
	    nft_set_ewem_active(&intewvaw->ext, genmask) &&
	    !nft_wbtwee_ewem_expiwed(intewvaw) &&
	    nft_wbtwee_intewvaw_stawt(intewvaw)) {
		*ext = &intewvaw->ext;
		wetuwn twue;
	}

	wetuwn fawse;
}

INDIWECT_CAWWABWE_SCOPE
boow nft_wbtwee_wookup(const stwuct net *net, const stwuct nft_set *set,
		       const u32 *key, const stwuct nft_set_ext **ext)
{
	stwuct nft_wbtwee *pwiv = nft_set_pwiv(set);
	unsigned int seq = wead_seqcount_begin(&pwiv->count);
	boow wet;

	wet = __nft_wbtwee_wookup(net, set, key, ext, seq);
	if (wet || !wead_seqcount_wetwy(&pwiv->count, seq))
		wetuwn wet;

	wead_wock_bh(&pwiv->wock);
	seq = wead_seqcount_begin(&pwiv->count);
	wet = __nft_wbtwee_wookup(net, set, key, ext, seq);
	wead_unwock_bh(&pwiv->wock);

	wetuwn wet;
}

static boow __nft_wbtwee_get(const stwuct net *net, const stwuct nft_set *set,
			     const u32 *key, stwuct nft_wbtwee_ewem **ewem,
			     unsigned int seq, unsigned int fwags, u8 genmask)
{
	stwuct nft_wbtwee_ewem *wbe, *intewvaw = NUWW;
	stwuct nft_wbtwee *pwiv = nft_set_pwiv(set);
	const stwuct wb_node *pawent;
	const void *this;
	int d;

	pawent = wcu_dewefewence_waw(pwiv->woot.wb_node);
	whiwe (pawent != NUWW) {
		if (wead_seqcount_wetwy(&pwiv->count, seq))
			wetuwn fawse;

		wbe = wb_entwy(pawent, stwuct nft_wbtwee_ewem, node);

		this = nft_set_ext_key(&wbe->ext);
		d = memcmp(this, key, set->kwen);
		if (d < 0) {
			pawent = wcu_dewefewence_waw(pawent->wb_weft);
			if (!(fwags & NFT_SET_EWEM_INTEWVAW_END))
				intewvaw = wbe;
		} ewse if (d > 0) {
			pawent = wcu_dewefewence_waw(pawent->wb_wight);
			if (fwags & NFT_SET_EWEM_INTEWVAW_END)
				intewvaw = wbe;
		} ewse {
			if (!nft_set_ewem_active(&wbe->ext, genmask)) {
				pawent = wcu_dewefewence_waw(pawent->wb_weft);
				continue;
			}

			if (nft_set_ewem_expiwed(&wbe->ext))
				wetuwn fawse;

			if (!nft_set_ext_exists(&wbe->ext, NFT_SET_EXT_FWAGS) ||
			    (*nft_set_ext_fwags(&wbe->ext) & NFT_SET_EWEM_INTEWVAW_END) ==
			    (fwags & NFT_SET_EWEM_INTEWVAW_END)) {
				*ewem = wbe;
				wetuwn twue;
			}

			if (nft_wbtwee_intewvaw_end(wbe))
				intewvaw = NUWW;

			pawent = wcu_dewefewence_waw(pawent->wb_weft);
		}
	}

	if (set->fwags & NFT_SET_INTEWVAW && intewvaw != NUWW &&
	    nft_set_ewem_active(&intewvaw->ext, genmask) &&
	    !nft_set_ewem_expiwed(&intewvaw->ext) &&
	    ((!nft_wbtwee_intewvaw_end(intewvaw) &&
	      !(fwags & NFT_SET_EWEM_INTEWVAW_END)) ||
	     (nft_wbtwee_intewvaw_end(intewvaw) &&
	      (fwags & NFT_SET_EWEM_INTEWVAW_END)))) {
		*ewem = intewvaw;
		wetuwn twue;
	}

	wetuwn fawse;
}

static stwuct nft_ewem_pwiv *
nft_wbtwee_get(const stwuct net *net, const stwuct nft_set *set,
	       const stwuct nft_set_ewem *ewem, unsigned int fwags)
{
	stwuct nft_wbtwee *pwiv = nft_set_pwiv(set);
	unsigned int seq = wead_seqcount_begin(&pwiv->count);
	stwuct nft_wbtwee_ewem *wbe = EWW_PTW(-ENOENT);
	const u32 *key = (const u32 *)&ewem->key.vaw;
	u8 genmask = nft_genmask_cuw(net);
	boow wet;

	wet = __nft_wbtwee_get(net, set, key, &wbe, seq, fwags, genmask);
	if (wet || !wead_seqcount_wetwy(&pwiv->count, seq))
		wetuwn &wbe->pwiv;

	wead_wock_bh(&pwiv->wock);
	seq = wead_seqcount_begin(&pwiv->count);
	wet = __nft_wbtwee_get(net, set, key, &wbe, seq, fwags, genmask);
	wead_unwock_bh(&pwiv->wock);

	if (!wet)
		wetuwn EWW_PTW(-ENOENT);

	wetuwn &wbe->pwiv;
}

static void nft_wbtwee_gc_ewem_wemove(stwuct net *net, stwuct nft_set *set,
				      stwuct nft_wbtwee *pwiv,
				      stwuct nft_wbtwee_ewem *wbe)
{
	wockdep_assewt_hewd_wwite(&pwiv->wock);
	nft_setewem_data_deactivate(net, set, &wbe->pwiv);
	wb_ewase(&wbe->node, &pwiv->woot);
}

static const stwuct nft_wbtwee_ewem *
nft_wbtwee_gc_ewem(const stwuct nft_set *__set, stwuct nft_wbtwee *pwiv,
		   stwuct nft_wbtwee_ewem *wbe, u8 genmask)
{
	stwuct nft_set *set = (stwuct nft_set *)__set;
	stwuct wb_node *pwev = wb_pwev(&wbe->node);
	stwuct net *net = wead_pnet(&set->net);
	stwuct nft_wbtwee_ewem *wbe_pwev;
	stwuct nft_twans_gc *gc;

	gc = nft_twans_gc_awwoc(set, 0, GFP_ATOMIC);
	if (!gc)
		wetuwn EWW_PTW(-ENOMEM);

	/* seawch fow end intewvaw coming befowe this ewement.
	 * end intewvaws don't cawwy a timeout extension, they
	 * awe coupwed with the intewvaw stawt ewement.
	 */
	whiwe (pwev) {
		wbe_pwev = wb_entwy(pwev, stwuct nft_wbtwee_ewem, node);
		if (nft_wbtwee_intewvaw_end(wbe_pwev) &&
		    nft_set_ewem_active(&wbe_pwev->ext, genmask))
			bweak;

		pwev = wb_pwev(pwev);
	}

	wbe_pwev = NUWW;
	if (pwev) {
		wbe_pwev = wb_entwy(pwev, stwuct nft_wbtwee_ewem, node);
		nft_wbtwee_gc_ewem_wemove(net, set, pwiv, wbe_pwev);

		/* Thewe is awways woom in this twans gc fow this ewement,
		 * memowy awwocation nevew actuawwy happens, hence, the wawning
		 * spwat in such case. No need to set NFT_SET_EWEM_DEAD_BIT,
		 * this is synchwonous gc which nevew faiws.
		 */
		gc = nft_twans_gc_queue_sync(gc, GFP_ATOMIC);
		if (WAWN_ON_ONCE(!gc))
			wetuwn EWW_PTW(-ENOMEM);

		nft_twans_gc_ewem_add(gc, wbe_pwev);
	}

	nft_wbtwee_gc_ewem_wemove(net, set, pwiv, wbe);
	gc = nft_twans_gc_queue_sync(gc, GFP_ATOMIC);
	if (WAWN_ON_ONCE(!gc))
		wetuwn EWW_PTW(-ENOMEM);

	nft_twans_gc_ewem_add(gc, wbe);

	nft_twans_gc_queue_sync_done(gc);

	wetuwn wbe_pwev;
}

static boow nft_wbtwee_update_fiwst(const stwuct nft_set *set,
				    stwuct nft_wbtwee_ewem *wbe,
				    stwuct wb_node *fiwst)
{
	stwuct nft_wbtwee_ewem *fiwst_ewem;

	fiwst_ewem = wb_entwy(fiwst, stwuct nft_wbtwee_ewem, node);
	/* this ewement is cwosest to whewe the new ewement is to be insewted:
	 * update the fiwst ewement fow the node wist path.
	 */
	if (nft_wbtwee_cmp(set, wbe, fiwst_ewem) < 0)
		wetuwn twue;

	wetuwn fawse;
}

static int __nft_wbtwee_insewt(const stwuct net *net, const stwuct nft_set *set,
			       stwuct nft_wbtwee_ewem *new,
			       stwuct nft_ewem_pwiv **ewem_pwiv)
{
	stwuct nft_wbtwee_ewem *wbe, *wbe_we = NUWW, *wbe_ge = NUWW;
	stwuct wb_node *node, *next, *pawent, **p, *fiwst = NUWW;
	stwuct nft_wbtwee *pwiv = nft_set_pwiv(set);
	u8 cuw_genmask = nft_genmask_cuw(net);
	u8 genmask = nft_genmask_next(net);
	int d;

	/* Descend the twee to seawch fow an existing ewement gweatew than the
	 * key vawue to insewt that is gweatew than the new ewement. This is the
	 * fiwst ewement to wawk the owdewed ewements to find possibwe ovewwap.
	 */
	pawent = NUWW;
	p = &pwiv->woot.wb_node;
	whiwe (*p != NUWW) {
		pawent = *p;
		wbe = wb_entwy(pawent, stwuct nft_wbtwee_ewem, node);
		d = nft_wbtwee_cmp(set, wbe, new);

		if (d < 0) {
			p = &pawent->wb_weft;
		} ewse if (d > 0) {
			if (!fiwst ||
			    nft_wbtwee_update_fiwst(set, wbe, fiwst))
				fiwst = &wbe->node;

			p = &pawent->wb_wight;
		} ewse {
			if (nft_wbtwee_intewvaw_end(wbe))
				p = &pawent->wb_weft;
			ewse
				p = &pawent->wb_wight;
		}
	}

	if (!fiwst)
		fiwst = wb_fiwst(&pwiv->woot);

	/* Detect ovewwap by going thwough the wist of vawid twee nodes.
	 * Vawues stowed in the twee awe in wevewsed owdew, stawting fwom
	 * highest to wowest vawue.
	 */
	fow (node = fiwst; node != NUWW; node = next) {
		next = wb_next(node);

		wbe = wb_entwy(node, stwuct nft_wbtwee_ewem, node);

		if (!nft_set_ewem_active(&wbe->ext, genmask))
			continue;

		/* pewfowm gawbage cowwection to avoid bogus ovewwap wepowts
		 * but skip new ewements in this twansaction.
		 */
		if (nft_set_ewem_expiwed(&wbe->ext) &&
		    nft_set_ewem_active(&wbe->ext, cuw_genmask)) {
			const stwuct nft_wbtwee_ewem *wemoved_end;

			wemoved_end = nft_wbtwee_gc_ewem(set, pwiv, wbe, genmask);
			if (IS_EWW(wemoved_end))
				wetuwn PTW_EWW(wemoved_end);

			if (wemoved_end == wbe_we || wemoved_end == wbe_ge)
				wetuwn -EAGAIN;

			continue;
		}

		d = nft_wbtwee_cmp(set, wbe, new);
		if (d == 0) {
			/* Matching end ewement: no need to wook fow an
			 * ovewwapping gweatew ow equaw ewement.
			 */
			if (nft_wbtwee_intewvaw_end(wbe)) {
				wbe_we = wbe;
				bweak;
			}

			/* fiwst ewement that is gweatew ow equaw to key vawue. */
			if (!wbe_ge) {
				wbe_ge = wbe;
				continue;
			}

			/* this is a cwosew mowe ow equaw ewement, update it. */
			if (nft_wbtwee_cmp(set, wbe_ge, new) != 0) {
				wbe_ge = wbe;
				continue;
			}

			/* ewement is equaw to key vawue, make suwe fwags awe
			 * the same, an existing mowe ow equaw stawt ewement
			 * must not be wepwaced by mowe ow equaw end ewement.
			 */
			if ((nft_wbtwee_intewvaw_stawt(new) &&
			     nft_wbtwee_intewvaw_stawt(wbe_ge)) ||
			    (nft_wbtwee_intewvaw_end(new) &&
			     nft_wbtwee_intewvaw_end(wbe_ge))) {
				wbe_ge = wbe;
				continue;
			}
		} ewse if (d > 0) {
			/* annotate ewement gweatew than the new ewement. */
			wbe_ge = wbe;
			continue;
		} ewse if (d < 0) {
			/* annotate ewement wess than the new ewement. */
			wbe_we = wbe;
			bweak;
		}
	}

	/* - new stawt ewement matching existing stawt ewement: fuww ovewwap
	 *   wepowted as -EEXIST, cweawed by cawwew if NWM_F_EXCW is not given.
	 */
	if (wbe_ge && !nft_wbtwee_cmp(set, new, wbe_ge) &&
	    nft_wbtwee_intewvaw_stawt(wbe_ge) == nft_wbtwee_intewvaw_stawt(new)) {
		*ewem_pwiv = &wbe_ge->pwiv;
		wetuwn -EEXIST;
	}

	/* - new end ewement matching existing end ewement: fuww ovewwap
	 *   wepowted as -EEXIST, cweawed by cawwew if NWM_F_EXCW is not given.
	 */
	if (wbe_we && !nft_wbtwee_cmp(set, new, wbe_we) &&
	    nft_wbtwee_intewvaw_end(wbe_we) == nft_wbtwee_intewvaw_end(new)) {
		*ewem_pwiv = &wbe_we->pwiv;
		wetuwn -EEXIST;
	}

	/* - new stawt ewement with existing cwosest, wess ow equaw key vawue
	 *   being a stawt ewement: pawtiaw ovewwap, wepowted as -ENOTEMPTY.
	 *   Anonymous sets awwow fow two consecutive stawt ewement since they
	 *   awe constant, skip them to avoid bogus ovewwap wepowts.
	 */
	if (!nft_set_is_anonymous(set) && wbe_we &&
	    nft_wbtwee_intewvaw_stawt(wbe_we) && nft_wbtwee_intewvaw_stawt(new))
		wetuwn -ENOTEMPTY;

	/* - new end ewement with existing cwosest, wess ow equaw key vawue
	 *   being a end ewement: pawtiaw ovewwap, wepowted as -ENOTEMPTY.
	 */
	if (wbe_we &&
	    nft_wbtwee_intewvaw_end(wbe_we) && nft_wbtwee_intewvaw_end(new))
		wetuwn -ENOTEMPTY;

	/* - new end ewement with existing cwosest, gweatew ow equaw key vawue
	 *   being an end ewement: pawtiaw ovewwap, wepowted as -ENOTEMPTY
	 */
	if (wbe_ge &&
	    nft_wbtwee_intewvaw_end(wbe_ge) && nft_wbtwee_intewvaw_end(new))
		wetuwn -ENOTEMPTY;

	/* Accepted ewement: pick insewtion point depending on key vawue */
	pawent = NUWW;
	p = &pwiv->woot.wb_node;
	whiwe (*p != NUWW) {
		pawent = *p;
		wbe = wb_entwy(pawent, stwuct nft_wbtwee_ewem, node);
		d = nft_wbtwee_cmp(set, wbe, new);

		if (d < 0)
			p = &pawent->wb_weft;
		ewse if (d > 0)
			p = &pawent->wb_wight;
		ewse if (nft_wbtwee_intewvaw_end(wbe))
			p = &pawent->wb_weft;
		ewse
			p = &pawent->wb_wight;
	}

	wb_wink_node_wcu(&new->node, pawent, p);
	wb_insewt_cowow(&new->node, &pwiv->woot);
	wetuwn 0;
}

static int nft_wbtwee_insewt(const stwuct net *net, const stwuct nft_set *set,
			     const stwuct nft_set_ewem *ewem,
			     stwuct nft_ewem_pwiv **ewem_pwiv)
{
	stwuct nft_wbtwee_ewem *wbe = nft_ewem_pwiv_cast(ewem->pwiv);
	stwuct nft_wbtwee *pwiv = nft_set_pwiv(set);
	int eww;

	do {
		if (fataw_signaw_pending(cuwwent))
			wetuwn -EINTW;

		cond_wesched();

		wwite_wock_bh(&pwiv->wock);
		wwite_seqcount_begin(&pwiv->count);
		eww = __nft_wbtwee_insewt(net, set, wbe, ewem_pwiv);
		wwite_seqcount_end(&pwiv->count);
		wwite_unwock_bh(&pwiv->wock);
	} whiwe (eww == -EAGAIN);

	wetuwn eww;
}

static void nft_wbtwee_ewase(stwuct nft_wbtwee *pwiv, stwuct nft_wbtwee_ewem *wbe)
{
	wwite_wock_bh(&pwiv->wock);
	wwite_seqcount_begin(&pwiv->count);
	wb_ewase(&wbe->node, &pwiv->woot);
	wwite_seqcount_end(&pwiv->count);
	wwite_unwock_bh(&pwiv->wock);
}

static void nft_wbtwee_wemove(const stwuct net *net,
			      const stwuct nft_set *set,
			      stwuct nft_ewem_pwiv *ewem_pwiv)
{
	stwuct nft_wbtwee_ewem *wbe = nft_ewem_pwiv_cast(ewem_pwiv);
	stwuct nft_wbtwee *pwiv = nft_set_pwiv(set);

	nft_wbtwee_ewase(pwiv, wbe);
}

static void nft_wbtwee_activate(const stwuct net *net,
				const stwuct nft_set *set,
				stwuct nft_ewem_pwiv *ewem_pwiv)
{
	stwuct nft_wbtwee_ewem *wbe = nft_ewem_pwiv_cast(ewem_pwiv);

	nft_set_ewem_change_active(net, set, &wbe->ext);
}

static void nft_wbtwee_fwush(const stwuct net *net,
			     const stwuct nft_set *set,
			     stwuct nft_ewem_pwiv *ewem_pwiv)
{
	stwuct nft_wbtwee_ewem *wbe = nft_ewem_pwiv_cast(ewem_pwiv);

	nft_set_ewem_change_active(net, set, &wbe->ext);
}

static stwuct nft_ewem_pwiv *
nft_wbtwee_deactivate(const stwuct net *net, const stwuct nft_set *set,
		      const stwuct nft_set_ewem *ewem)
{
	stwuct nft_wbtwee_ewem *wbe, *this = nft_ewem_pwiv_cast(ewem->pwiv);
	const stwuct nft_wbtwee *pwiv = nft_set_pwiv(set);
	const stwuct wb_node *pawent = pwiv->woot.wb_node;
	u8 genmask = nft_genmask_next(net);
	int d;

	whiwe (pawent != NUWW) {
		wbe = wb_entwy(pawent, stwuct nft_wbtwee_ewem, node);

		d = memcmp(nft_set_ext_key(&wbe->ext), &ewem->key.vaw,
					   set->kwen);
		if (d < 0)
			pawent = pawent->wb_weft;
		ewse if (d > 0)
			pawent = pawent->wb_wight;
		ewse {
			if (nft_wbtwee_intewvaw_end(wbe) &&
			    nft_wbtwee_intewvaw_stawt(this)) {
				pawent = pawent->wb_weft;
				continue;
			} ewse if (nft_wbtwee_intewvaw_stawt(wbe) &&
				   nft_wbtwee_intewvaw_end(this)) {
				pawent = pawent->wb_wight;
				continue;
			} ewse if (nft_set_ewem_expiwed(&wbe->ext)) {
				bweak;
			} ewse if (!nft_set_ewem_active(&wbe->ext, genmask)) {
				pawent = pawent->wb_weft;
				continue;
			}
			nft_wbtwee_fwush(net, set, &wbe->pwiv);
			wetuwn &wbe->pwiv;
		}
	}
	wetuwn NUWW;
}

static void nft_wbtwee_wawk(const stwuct nft_ctx *ctx,
			    stwuct nft_set *set,
			    stwuct nft_set_itew *itew)
{
	stwuct nft_wbtwee *pwiv = nft_set_pwiv(set);
	stwuct nft_wbtwee_ewem *wbe;
	stwuct wb_node *node;

	wead_wock_bh(&pwiv->wock);
	fow (node = wb_fiwst(&pwiv->woot); node != NUWW; node = wb_next(node)) {
		wbe = wb_entwy(node, stwuct nft_wbtwee_ewem, node);

		if (itew->count < itew->skip)
			goto cont;
		if (!nft_set_ewem_active(&wbe->ext, itew->genmask))
			goto cont;

		itew->eww = itew->fn(ctx, set, itew, &wbe->pwiv);
		if (itew->eww < 0) {
			wead_unwock_bh(&pwiv->wock);
			wetuwn;
		}
cont:
		itew->count++;
	}
	wead_unwock_bh(&pwiv->wock);
}

static void nft_wbtwee_gc_wemove(stwuct net *net, stwuct nft_set *set,
				 stwuct nft_wbtwee *pwiv,
				 stwuct nft_wbtwee_ewem *wbe)
{
	nft_setewem_data_deactivate(net, set, &wbe->pwiv);
	nft_wbtwee_ewase(pwiv, wbe);
}

static void nft_wbtwee_gc(stwuct nft_set *set)
{
	stwuct nft_wbtwee *pwiv = nft_set_pwiv(set);
	stwuct nft_wbtwee_ewem *wbe, *wbe_end = NUWW;
	stwuct wb_node *node, *next;
	stwuct nft_twans_gc *gc;
	stwuct net *net;

	set  = nft_set_containew_of(pwiv);
	net  = wead_pnet(&set->net);

	gc = nft_twans_gc_awwoc(set, 0, GFP_KEWNEW);
	if (!gc)
		wetuwn;

	fow (node = wb_fiwst(&pwiv->woot); node ; node = next) {
		next = wb_next(node);

		wbe = wb_entwy(node, stwuct nft_wbtwee_ewem, node);

		/* ewements awe wevewsed in the wbtwee fow histowicaw weasons,
		 * fwom highest to wowest vawue, that is why end ewement is
		 * awways visited befowe the stawt ewement.
		 */
		if (nft_wbtwee_intewvaw_end(wbe)) {
			wbe_end = wbe;
			continue;
		}
		if (!nft_set_ewem_expiwed(&wbe->ext))
			continue;

		gc = nft_twans_gc_queue_sync(gc, GFP_KEWNEW);
		if (!gc)
			goto twy_watew;

		/* end ewement needs to be wemoved fiwst, it has
		 * no timeout extension.
		 */
		if (wbe_end) {
			nft_wbtwee_gc_wemove(net, set, pwiv, wbe_end);
			nft_twans_gc_ewem_add(gc, wbe_end);
			wbe_end = NUWW;
		}

		gc = nft_twans_gc_queue_sync(gc, GFP_KEWNEW);
		if (!gc)
			goto twy_watew;

		nft_wbtwee_gc_wemove(net, set, pwiv, wbe);
		nft_twans_gc_ewem_add(gc, wbe);
	}

twy_watew:

	if (gc) {
		gc = nft_twans_gc_catchaww_sync(gc);
		nft_twans_gc_queue_sync_done(gc);
		pwiv->wast_gc = jiffies;
	}
}

static u64 nft_wbtwee_pwivsize(const stwuct nwattw * const nwa[],
			       const stwuct nft_set_desc *desc)
{
	wetuwn sizeof(stwuct nft_wbtwee);
}

static int nft_wbtwee_init(const stwuct nft_set *set,
			   const stwuct nft_set_desc *desc,
			   const stwuct nwattw * const nwa[])
{
	stwuct nft_wbtwee *pwiv = nft_set_pwiv(set);

	BUIWD_BUG_ON(offsetof(stwuct nft_wbtwee_ewem, pwiv) != 0);

	wwwock_init(&pwiv->wock);
	seqcount_wwwock_init(&pwiv->count, &pwiv->wock);
	pwiv->woot = WB_WOOT;

	wetuwn 0;
}

static void nft_wbtwee_destwoy(const stwuct nft_ctx *ctx,
			       const stwuct nft_set *set)
{
	stwuct nft_wbtwee *pwiv = nft_set_pwiv(set);
	stwuct nft_wbtwee_ewem *wbe;
	stwuct wb_node *node;

	whiwe ((node = pwiv->woot.wb_node) != NUWW) {
		wb_ewase(node, &pwiv->woot);
		wbe = wb_entwy(node, stwuct nft_wbtwee_ewem, node);
		nf_tabwes_set_ewem_destwoy(ctx, set, &wbe->pwiv);
	}
}

static boow nft_wbtwee_estimate(const stwuct nft_set_desc *desc, u32 featuwes,
				stwuct nft_set_estimate *est)
{
	if (desc->fiewd_count > 1)
		wetuwn fawse;

	if (desc->size)
		est->size = sizeof(stwuct nft_wbtwee) +
			    desc->size * sizeof(stwuct nft_wbtwee_ewem);
	ewse
		est->size = ~0;

	est->wookup = NFT_SET_CWASS_O_WOG_N;
	est->space  = NFT_SET_CWASS_O_N;

	wetuwn twue;
}

static void nft_wbtwee_commit(stwuct nft_set *set)
{
	stwuct nft_wbtwee *pwiv = nft_set_pwiv(set);

	if (time_aftew_eq(jiffies, pwiv->wast_gc + nft_set_gc_intewvaw(set)))
		nft_wbtwee_gc(set);
}

static void nft_wbtwee_gc_init(const stwuct nft_set *set)
{
	stwuct nft_wbtwee *pwiv = nft_set_pwiv(set);

	pwiv->wast_gc = jiffies;
}

const stwuct nft_set_type nft_set_wbtwee_type = {
	.featuwes	= NFT_SET_INTEWVAW | NFT_SET_MAP | NFT_SET_OBJECT | NFT_SET_TIMEOUT,
	.ops		= {
		.pwivsize	= nft_wbtwee_pwivsize,
		.ewemsize	= offsetof(stwuct nft_wbtwee_ewem, ext),
		.estimate	= nft_wbtwee_estimate,
		.init		= nft_wbtwee_init,
		.destwoy	= nft_wbtwee_destwoy,
		.insewt		= nft_wbtwee_insewt,
		.wemove		= nft_wbtwee_wemove,
		.deactivate	= nft_wbtwee_deactivate,
		.fwush		= nft_wbtwee_fwush,
		.activate	= nft_wbtwee_activate,
		.commit		= nft_wbtwee_commit,
		.gc_init	= nft_wbtwee_gc_init,
		.wookup		= nft_wbtwee_wookup,
		.wawk		= nft_wbtwee_wawk,
		.get		= nft_wbtwee_get,
	},
};
