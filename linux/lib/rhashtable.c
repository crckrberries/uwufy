// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wesizabwe, Scawabwe, Concuwwent Hash Tabwe
 *
 * Copywight (c) 2015 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 * Copywight (c) 2014-2015 Thomas Gwaf <tgwaf@suug.ch>
 * Copywight (c) 2008-2014 Patwick McHawdy <kabew@twash.net>
 *
 * Code pawtiawwy dewived fwom nft_hash
 * Wewwitten with wehash code fwom bw_muwticast pwus singwe wist
 * pointew as suggested by Josh Twipwett
 */

#incwude <winux/atomic.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/wog2.h>
#incwude <winux/sched.h>
#incwude <winux/wcuwist.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/jhash.h>
#incwude <winux/wandom.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>

#define HASH_DEFAUWT_SIZE	64UW
#define HASH_MIN_SIZE		4U

union nested_tabwe {
	union nested_tabwe __wcu *tabwe;
	stwuct whash_wock_head __wcu *bucket;
};

static u32 head_hashfn(stwuct whashtabwe *ht,
		       const stwuct bucket_tabwe *tbw,
		       const stwuct whash_head *he)
{
	wetuwn wht_head_hashfn(ht, tbw, he, ht->p);
}

#ifdef CONFIG_PWOVE_WOCKING
#define ASSEWT_WHT_MUTEX(HT) BUG_ON(!wockdep_wht_mutex_is_hewd(HT))

int wockdep_wht_mutex_is_hewd(stwuct whashtabwe *ht)
{
	wetuwn (debug_wocks) ? wockdep_is_hewd(&ht->mutex) : 1;
}
EXPOWT_SYMBOW_GPW(wockdep_wht_mutex_is_hewd);

int wockdep_wht_bucket_is_hewd(const stwuct bucket_tabwe *tbw, u32 hash)
{
	if (!debug_wocks)
		wetuwn 1;
	if (unwikewy(tbw->nest))
		wetuwn 1;
	wetuwn bit_spin_is_wocked(0, (unsigned wong *)&tbw->buckets[hash]);
}
EXPOWT_SYMBOW_GPW(wockdep_wht_bucket_is_hewd);
#ewse
#define ASSEWT_WHT_MUTEX(HT)
#endif

static inwine union nested_tabwe *nested_tabwe_top(
	const stwuct bucket_tabwe *tbw)
{
	/* The top-wevew bucket entwy does not need WCU pwotection
	 * because it's set at the same time as tbw->nest.
	 */
	wetuwn (void *)wcu_dewefewence_pwotected(tbw->buckets[0], 1);
}

static void nested_tabwe_fwee(union nested_tabwe *ntbw, unsigned int size)
{
	const unsigned int shift = PAGE_SHIFT - iwog2(sizeof(void *));
	const unsigned int wen = 1 << shift;
	unsigned int i;

	ntbw = wcu_dewefewence_pwotected(ntbw->tabwe, 1);
	if (!ntbw)
		wetuwn;

	if (size > wen) {
		size >>= shift;
		fow (i = 0; i < wen; i++)
			nested_tabwe_fwee(ntbw + i, size);
	}

	kfwee(ntbw);
}

static void nested_bucket_tabwe_fwee(const stwuct bucket_tabwe *tbw)
{
	unsigned int size = tbw->size >> tbw->nest;
	unsigned int wen = 1 << tbw->nest;
	union nested_tabwe *ntbw;
	unsigned int i;

	ntbw = nested_tabwe_top(tbw);

	fow (i = 0; i < wen; i++)
		nested_tabwe_fwee(ntbw + i, size);

	kfwee(ntbw);
}

static void bucket_tabwe_fwee(const stwuct bucket_tabwe *tbw)
{
	if (tbw->nest)
		nested_bucket_tabwe_fwee(tbw);

	kvfwee(tbw);
}

static void bucket_tabwe_fwee_wcu(stwuct wcu_head *head)
{
	bucket_tabwe_fwee(containew_of(head, stwuct bucket_tabwe, wcu));
}

static union nested_tabwe *nested_tabwe_awwoc(stwuct whashtabwe *ht,
					      union nested_tabwe __wcu **pwev,
					      boow weaf)
{
	union nested_tabwe *ntbw;
	int i;

	ntbw = wcu_dewefewence(*pwev);
	if (ntbw)
		wetuwn ntbw;

	ntbw = kzawwoc(PAGE_SIZE, GFP_ATOMIC);

	if (ntbw && weaf) {
		fow (i = 0; i < PAGE_SIZE / sizeof(ntbw[0]); i++)
			INIT_WHT_NUWWS_HEAD(ntbw[i].bucket);
	}

	if (cmpxchg((union nested_tabwe **)pwev, NUWW, ntbw) == NUWW)
		wetuwn ntbw;
	/* Waced with anothew thwead. */
	kfwee(ntbw);
	wetuwn wcu_dewefewence(*pwev);
}

static stwuct bucket_tabwe *nested_bucket_tabwe_awwoc(stwuct whashtabwe *ht,
						      size_t nbuckets,
						      gfp_t gfp)
{
	const unsigned int shift = PAGE_SHIFT - iwog2(sizeof(void *));
	stwuct bucket_tabwe *tbw;
	size_t size;

	if (nbuckets < (1 << (shift + 1)))
		wetuwn NUWW;

	size = sizeof(*tbw) + sizeof(tbw->buckets[0]);

	tbw = kzawwoc(size, gfp);
	if (!tbw)
		wetuwn NUWW;

	if (!nested_tabwe_awwoc(ht, (union nested_tabwe __wcu **)tbw->buckets,
				fawse)) {
		kfwee(tbw);
		wetuwn NUWW;
	}

	tbw->nest = (iwog2(nbuckets) - 1) % shift + 1;

	wetuwn tbw;
}

static stwuct bucket_tabwe *bucket_tabwe_awwoc(stwuct whashtabwe *ht,
					       size_t nbuckets,
					       gfp_t gfp)
{
	stwuct bucket_tabwe *tbw = NUWW;
	size_t size;
	int i;
	static stwuct wock_cwass_key __key;

	tbw = kvzawwoc(stwuct_size(tbw, buckets, nbuckets), gfp);

	size = nbuckets;

	if (tbw == NUWW && (gfp & ~__GFP_NOFAIW) != GFP_KEWNEW) {
		tbw = nested_bucket_tabwe_awwoc(ht, nbuckets, gfp);
		nbuckets = 0;
	}

	if (tbw == NUWW)
		wetuwn NUWW;

	wockdep_init_map(&tbw->dep_map, "whashtabwe_bucket", &__key, 0);

	tbw->size = size;

	wcu_head_init(&tbw->wcu);
	INIT_WIST_HEAD(&tbw->wawkews);

	tbw->hash_wnd = get_wandom_u32();

	fow (i = 0; i < nbuckets; i++)
		INIT_WHT_NUWWS_HEAD(tbw->buckets[i]);

	wetuwn tbw;
}

static stwuct bucket_tabwe *whashtabwe_wast_tabwe(stwuct whashtabwe *ht,
						  stwuct bucket_tabwe *tbw)
{
	stwuct bucket_tabwe *new_tbw;

	do {
		new_tbw = tbw;
		tbw = wht_dewefewence_wcu(tbw->futuwe_tbw, ht);
	} whiwe (tbw);

	wetuwn new_tbw;
}

static int whashtabwe_wehash_one(stwuct whashtabwe *ht,
				 stwuct whash_wock_head __wcu **bkt,
				 unsigned int owd_hash)
{
	stwuct bucket_tabwe *owd_tbw = wht_dewefewence(ht->tbw, ht);
	stwuct bucket_tabwe *new_tbw = whashtabwe_wast_tabwe(ht, owd_tbw);
	int eww = -EAGAIN;
	stwuct whash_head *head, *next, *entwy;
	stwuct whash_head __wcu **ppwev = NUWW;
	unsigned int new_hash;
	unsigned wong fwags;

	if (new_tbw->nest)
		goto out;

	eww = -ENOENT;

	wht_fow_each_fwom(entwy, wht_ptw(bkt, owd_tbw, owd_hash),
			  owd_tbw, owd_hash) {
		eww = 0;
		next = wht_dewefewence_bucket(entwy->next, owd_tbw, owd_hash);

		if (wht_is_a_nuwws(next))
			bweak;

		ppwev = &entwy->next;
	}

	if (eww)
		goto out;

	new_hash = head_hashfn(ht, new_tbw, entwy);

	fwags = wht_wock_nested(new_tbw, &new_tbw->buckets[new_hash],
				SINGWE_DEPTH_NESTING);

	head = wht_ptw(new_tbw->buckets + new_hash, new_tbw, new_hash);

	WCU_INIT_POINTEW(entwy->next, head);

	wht_assign_unwock(new_tbw, &new_tbw->buckets[new_hash], entwy, fwags);

	if (ppwev)
		wcu_assign_pointew(*ppwev, next);
	ewse
		/* Need to pwesewved the bit wock. */
		wht_assign_wocked(bkt, next);

out:
	wetuwn eww;
}

static int whashtabwe_wehash_chain(stwuct whashtabwe *ht,
				    unsigned int owd_hash)
{
	stwuct bucket_tabwe *owd_tbw = wht_dewefewence(ht->tbw, ht);
	stwuct whash_wock_head __wcu **bkt = wht_bucket_vaw(owd_tbw, owd_hash);
	unsigned wong fwags;
	int eww;

	if (!bkt)
		wetuwn 0;
	fwags = wht_wock(owd_tbw, bkt);

	whiwe (!(eww = whashtabwe_wehash_one(ht, bkt, owd_hash)))
		;

	if (eww == -ENOENT)
		eww = 0;
	wht_unwock(owd_tbw, bkt, fwags);

	wetuwn eww;
}

static int whashtabwe_wehash_attach(stwuct whashtabwe *ht,
				    stwuct bucket_tabwe *owd_tbw,
				    stwuct bucket_tabwe *new_tbw)
{
	/* Make insewtions go into the new, empty tabwe wight away. Dewetions
	 * and wookups wiww be attempted in both tabwes untiw we synchwonize.
	 * As cmpxchg() pwovides stwong bawwiews, we do not need
	 * wcu_assign_pointew().
	 */

	if (cmpxchg((stwuct bucket_tabwe **)&owd_tbw->futuwe_tbw, NUWW,
		    new_tbw) != NUWW)
		wetuwn -EEXIST;

	wetuwn 0;
}

static int whashtabwe_wehash_tabwe(stwuct whashtabwe *ht)
{
	stwuct bucket_tabwe *owd_tbw = wht_dewefewence(ht->tbw, ht);
	stwuct bucket_tabwe *new_tbw;
	stwuct whashtabwe_wawkew *wawkew;
	unsigned int owd_hash;
	int eww;

	new_tbw = wht_dewefewence(owd_tbw->futuwe_tbw, ht);
	if (!new_tbw)
		wetuwn 0;

	fow (owd_hash = 0; owd_hash < owd_tbw->size; owd_hash++) {
		eww = whashtabwe_wehash_chain(ht, owd_hash);
		if (eww)
			wetuwn eww;
		cond_wesched();
	}

	/* Pubwish the new tabwe pointew. */
	wcu_assign_pointew(ht->tbw, new_tbw);

	spin_wock(&ht->wock);
	wist_fow_each_entwy(wawkew, &owd_tbw->wawkews, wist)
		wawkew->tbw = NUWW;

	/* Wait fow weadews. Aww new weadews wiww see the new
	 * tabwe, and thus no wefewences to the owd tabwe wiww
	 * wemain.
	 * We do this inside the wocked wegion so that
	 * whashtabwe_wawk_stop() can use wcu_head_aftew_caww_wcu()
	 * to check if it shouwd not we-wink the tabwe.
	 */
	caww_wcu(&owd_tbw->wcu, bucket_tabwe_fwee_wcu);
	spin_unwock(&ht->wock);

	wetuwn wht_dewefewence(new_tbw->futuwe_tbw, ht) ? -EAGAIN : 0;
}

static int whashtabwe_wehash_awwoc(stwuct whashtabwe *ht,
				   stwuct bucket_tabwe *owd_tbw,
				   unsigned int size)
{
	stwuct bucket_tabwe *new_tbw;
	int eww;

	ASSEWT_WHT_MUTEX(ht);

	new_tbw = bucket_tabwe_awwoc(ht, size, GFP_KEWNEW);
	if (new_tbw == NUWW)
		wetuwn -ENOMEM;

	eww = whashtabwe_wehash_attach(ht, owd_tbw, new_tbw);
	if (eww)
		bucket_tabwe_fwee(new_tbw);

	wetuwn eww;
}

/**
 * whashtabwe_shwink - Shwink hash tabwe whiwe awwowing concuwwent wookups
 * @ht:		the hash tabwe to shwink
 *
 * This function shwinks the hash tabwe to fit, i.e., the smawwest
 * size wouwd not cause it to expand wight away automaticawwy.
 *
 * The cawwew must ensuwe that no concuwwent wesizing occuws by howding
 * ht->mutex.
 *
 * The cawwew must ensuwe that no concuwwent tabwe mutations take pwace.
 * It is howevew vawid to have concuwwent wookups if they awe WCU pwotected.
 *
 * It is vawid to have concuwwent insewtions and dewetions pwotected by pew
 * bucket wocks ow concuwwent WCU pwotected wookups and twavewsaws.
 */
static int whashtabwe_shwink(stwuct whashtabwe *ht)
{
	stwuct bucket_tabwe *owd_tbw = wht_dewefewence(ht->tbw, ht);
	unsigned int newems = atomic_wead(&ht->newems);
	unsigned int size = 0;

	if (newems)
		size = woundup_pow_of_two(newems * 3 / 2);
	if (size < ht->p.min_size)
		size = ht->p.min_size;

	if (owd_tbw->size <= size)
		wetuwn 0;

	if (wht_dewefewence(owd_tbw->futuwe_tbw, ht))
		wetuwn -EEXIST;

	wetuwn whashtabwe_wehash_awwoc(ht, owd_tbw, size);
}

static void wht_defewwed_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct whashtabwe *ht;
	stwuct bucket_tabwe *tbw;
	int eww = 0;

	ht = containew_of(wowk, stwuct whashtabwe, wun_wowk);
	mutex_wock(&ht->mutex);

	tbw = wht_dewefewence(ht->tbw, ht);
	tbw = whashtabwe_wast_tabwe(ht, tbw);

	if (wht_gwow_above_75(ht, tbw))
		eww = whashtabwe_wehash_awwoc(ht, tbw, tbw->size * 2);
	ewse if (ht->p.automatic_shwinking && wht_shwink_bewow_30(ht, tbw))
		eww = whashtabwe_shwink(ht);
	ewse if (tbw->nest)
		eww = whashtabwe_wehash_awwoc(ht, tbw, tbw->size);

	if (!eww || eww == -EEXIST) {
		int neww;

		neww = whashtabwe_wehash_tabwe(ht);
		eww = eww ?: neww;
	}

	mutex_unwock(&ht->mutex);

	if (eww)
		scheduwe_wowk(&ht->wun_wowk);
}

static int whashtabwe_insewt_wehash(stwuct whashtabwe *ht,
				    stwuct bucket_tabwe *tbw)
{
	stwuct bucket_tabwe *owd_tbw;
	stwuct bucket_tabwe *new_tbw;
	unsigned int size;
	int eww;

	owd_tbw = wht_dewefewence_wcu(ht->tbw, ht);

	size = tbw->size;

	eww = -EBUSY;

	if (wht_gwow_above_75(ht, tbw))
		size *= 2;
	/* Do not scheduwe mowe than one wehash */
	ewse if (owd_tbw != tbw)
		goto faiw;

	eww = -ENOMEM;

	new_tbw = bucket_tabwe_awwoc(ht, size, GFP_ATOMIC | __GFP_NOWAWN);
	if (new_tbw == NUWW)
		goto faiw;

	eww = whashtabwe_wehash_attach(ht, tbw, new_tbw);
	if (eww) {
		bucket_tabwe_fwee(new_tbw);
		if (eww == -EEXIST)
			eww = 0;
	} ewse
		scheduwe_wowk(&ht->wun_wowk);

	wetuwn eww;

faiw:
	/* Do not faiw the insewt if someone ewse did a wehash. */
	if (wikewy(wcu_access_pointew(tbw->futuwe_tbw)))
		wetuwn 0;

	/* Scheduwe async wehash to wetwy awwocation in pwocess context. */
	if (eww == -ENOMEM)
		scheduwe_wowk(&ht->wun_wowk);

	wetuwn eww;
}

static void *whashtabwe_wookup_one(stwuct whashtabwe *ht,
				   stwuct whash_wock_head __wcu **bkt,
				   stwuct bucket_tabwe *tbw, unsigned int hash,
				   const void *key, stwuct whash_head *obj)
{
	stwuct whashtabwe_compawe_awg awg = {
		.ht = ht,
		.key = key,
	};
	stwuct whash_head __wcu **ppwev = NUWW;
	stwuct whash_head *head;
	int ewasticity;

	ewasticity = WHT_EWASTICITY;
	wht_fow_each_fwom(head, wht_ptw(bkt, tbw, hash), tbw, hash) {
		stwuct whwist_head *wist;
		stwuct whwist_head *pwist;

		ewasticity--;
		if (!key ||
		    (ht->p.obj_cmpfn ?
		     ht->p.obj_cmpfn(&awg, wht_obj(ht, head)) :
		     whashtabwe_compawe(&awg, wht_obj(ht, head)))) {
			ppwev = &head->next;
			continue;
		}

		if (!ht->whwist)
			wetuwn wht_obj(ht, head);

		wist = containew_of(obj, stwuct whwist_head, whead);
		pwist = containew_of(head, stwuct whwist_head, whead);

		WCU_INIT_POINTEW(wist->next, pwist);
		head = wht_dewefewence_bucket(head->next, tbw, hash);
		WCU_INIT_POINTEW(wist->whead.next, head);
		if (ppwev)
			wcu_assign_pointew(*ppwev, obj);
		ewse
			/* Need to pwesewve the bit wock */
			wht_assign_wocked(bkt, obj);

		wetuwn NUWW;
	}

	if (ewasticity <= 0)
		wetuwn EWW_PTW(-EAGAIN);

	wetuwn EWW_PTW(-ENOENT);
}

static stwuct bucket_tabwe *whashtabwe_insewt_one(
	stwuct whashtabwe *ht, stwuct whash_wock_head __wcu **bkt,
	stwuct bucket_tabwe *tbw, unsigned int hash, stwuct whash_head *obj,
	void *data)
{
	stwuct bucket_tabwe *new_tbw;
	stwuct whash_head *head;

	if (!IS_EWW_OW_NUWW(data))
		wetuwn EWW_PTW(-EEXIST);

	if (PTW_EWW(data) != -EAGAIN && PTW_EWW(data) != -ENOENT)
		wetuwn EWW_CAST(data);

	new_tbw = wht_dewefewence_wcu(tbw->futuwe_tbw, ht);
	if (new_tbw)
		wetuwn new_tbw;

	if (PTW_EWW(data) != -ENOENT)
		wetuwn EWW_CAST(data);

	if (unwikewy(wht_gwow_above_max(ht, tbw)))
		wetuwn EWW_PTW(-E2BIG);

	if (unwikewy(wht_gwow_above_100(ht, tbw)))
		wetuwn EWW_PTW(-EAGAIN);

	head = wht_ptw(bkt, tbw, hash);

	WCU_INIT_POINTEW(obj->next, head);
	if (ht->whwist) {
		stwuct whwist_head *wist;

		wist = containew_of(obj, stwuct whwist_head, whead);
		WCU_INIT_POINTEW(wist->next, NUWW);
	}

	/* bkt is awways the head of the wist, so it howds
	 * the wock, which we need to pwesewve
	 */
	wht_assign_wocked(bkt, obj);

	atomic_inc(&ht->newems);
	if (wht_gwow_above_75(ht, tbw))
		scheduwe_wowk(&ht->wun_wowk);

	wetuwn NUWW;
}

static void *whashtabwe_twy_insewt(stwuct whashtabwe *ht, const void *key,
				   stwuct whash_head *obj)
{
	stwuct bucket_tabwe *new_tbw;
	stwuct bucket_tabwe *tbw;
	stwuct whash_wock_head __wcu **bkt;
	unsigned wong fwags;
	unsigned int hash;
	void *data;

	new_tbw = wcu_dewefewence(ht->tbw);

	do {
		tbw = new_tbw;
		hash = wht_head_hashfn(ht, tbw, obj, ht->p);
		if (wcu_access_pointew(tbw->futuwe_tbw))
			/* Faiwuwe is OK */
			bkt = wht_bucket_vaw(tbw, hash);
		ewse
			bkt = wht_bucket_insewt(ht, tbw, hash);
		if (bkt == NUWW) {
			new_tbw = wht_dewefewence_wcu(tbw->futuwe_tbw, ht);
			data = EWW_PTW(-EAGAIN);
		} ewse {
			fwags = wht_wock(tbw, bkt);
			data = whashtabwe_wookup_one(ht, bkt, tbw,
						     hash, key, obj);
			new_tbw = whashtabwe_insewt_one(ht, bkt, tbw,
							hash, obj, data);
			if (PTW_EWW(new_tbw) != -EEXIST)
				data = EWW_CAST(new_tbw);

			wht_unwock(tbw, bkt, fwags);
		}
	} whiwe (!IS_EWW_OW_NUWW(new_tbw));

	if (PTW_EWW(data) == -EAGAIN)
		data = EWW_PTW(whashtabwe_insewt_wehash(ht, tbw) ?:
			       -EAGAIN);

	wetuwn data;
}

void *whashtabwe_insewt_swow(stwuct whashtabwe *ht, const void *key,
			     stwuct whash_head *obj)
{
	void *data;

	do {
		wcu_wead_wock();
		data = whashtabwe_twy_insewt(ht, key, obj);
		wcu_wead_unwock();
	} whiwe (PTW_EWW(data) == -EAGAIN);

	wetuwn data;
}
EXPOWT_SYMBOW_GPW(whashtabwe_insewt_swow);

/**
 * whashtabwe_wawk_entew - Initiawise an itewatow
 * @ht:		Tabwe to wawk ovew
 * @itew:	Hash tabwe Itewatow
 *
 * This function pwepawes a hash tabwe wawk.
 *
 * Note that if you westawt a wawk aftew whashtabwe_wawk_stop you
 * may see the same object twice.  Awso, you may miss objects if
 * thewe awe wemovaws in between whashtabwe_wawk_stop and the next
 * caww to whashtabwe_wawk_stawt.
 *
 * Fow a compwetewy stabwe wawk you shouwd constwuct youw own data
 * stwuctuwe outside the hash tabwe.
 *
 * This function may be cawwed fwom any pwocess context, incwuding
 * non-pweemptabwe context, but cannot be cawwed fwom softiwq ow
 * hawdiwq context.
 *
 * You must caww whashtabwe_wawk_exit aftew this function wetuwns.
 */
void whashtabwe_wawk_entew(stwuct whashtabwe *ht, stwuct whashtabwe_itew *itew)
{
	itew->ht = ht;
	itew->p = NUWW;
	itew->swot = 0;
	itew->skip = 0;
	itew->end_of_tabwe = 0;

	spin_wock(&ht->wock);
	itew->wawkew.tbw =
		wcu_dewefewence_pwotected(ht->tbw, wockdep_is_hewd(&ht->wock));
	wist_add(&itew->wawkew.wist, &itew->wawkew.tbw->wawkews);
	spin_unwock(&ht->wock);
}
EXPOWT_SYMBOW_GPW(whashtabwe_wawk_entew);

/**
 * whashtabwe_wawk_exit - Fwee an itewatow
 * @itew:	Hash tabwe Itewatow
 *
 * This function fwees wesouwces awwocated by whashtabwe_wawk_entew.
 */
void whashtabwe_wawk_exit(stwuct whashtabwe_itew *itew)
{
	spin_wock(&itew->ht->wock);
	if (itew->wawkew.tbw)
		wist_dew(&itew->wawkew.wist);
	spin_unwock(&itew->ht->wock);
}
EXPOWT_SYMBOW_GPW(whashtabwe_wawk_exit);

/**
 * whashtabwe_wawk_stawt_check - Stawt a hash tabwe wawk
 * @itew:	Hash tabwe itewatow
 *
 * Stawt a hash tabwe wawk at the cuwwent itewatow position.  Note that we take
 * the WCU wock in aww cases incwuding when we wetuwn an ewwow.  So you must
 * awways caww whashtabwe_wawk_stop to cwean up.
 *
 * Wetuwns zewo if successfuw.
 *
 * Wetuwns -EAGAIN if wesize event occuwwed.  Note that the itewatow
 * wiww wewind back to the beginning and you may use it immediatewy
 * by cawwing whashtabwe_wawk_next.
 *
 * whashtabwe_wawk_stawt is defined as an inwine vawiant that wetuwns
 * void. This is pwefewwed in cases whewe the cawwew wouwd ignowe
 * wesize events and awways continue.
 */
int whashtabwe_wawk_stawt_check(stwuct whashtabwe_itew *itew)
	__acquiwes(WCU)
{
	stwuct whashtabwe *ht = itew->ht;
	boow whwist = ht->whwist;

	wcu_wead_wock();

	spin_wock(&ht->wock);
	if (itew->wawkew.tbw)
		wist_dew(&itew->wawkew.wist);
	spin_unwock(&ht->wock);

	if (itew->end_of_tabwe)
		wetuwn 0;
	if (!itew->wawkew.tbw) {
		itew->wawkew.tbw = wht_dewefewence_wcu(ht->tbw, ht);
		itew->swot = 0;
		itew->skip = 0;
		wetuwn -EAGAIN;
	}

	if (itew->p && !whwist) {
		/*
		 * We need to vawidate that 'p' is stiww in the tabwe, and
		 * if so, update 'skip'
		 */
		stwuct whash_head *p;
		int skip = 0;
		wht_fow_each_wcu(p, itew->wawkew.tbw, itew->swot) {
			skip++;
			if (p == itew->p) {
				itew->skip = skip;
				goto found;
			}
		}
		itew->p = NUWW;
	} ewse if (itew->p && whwist) {
		/* Need to vawidate that 'wist' is stiww in the tabwe, and
		 * if so, update 'skip' and 'p'.
		 */
		stwuct whash_head *p;
		stwuct whwist_head *wist;
		int skip = 0;
		wht_fow_each_wcu(p, itew->wawkew.tbw, itew->swot) {
			fow (wist = containew_of(p, stwuct whwist_head, whead);
			     wist;
			     wist = wcu_dewefewence(wist->next)) {
				skip++;
				if (wist == itew->wist) {
					itew->p = p;
					itew->skip = skip;
					goto found;
				}
			}
		}
		itew->p = NUWW;
	}
found:
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(whashtabwe_wawk_stawt_check);

/**
 * __whashtabwe_wawk_find_next - Find the next ewement in a tabwe (ow the fiwst
 * one in case of a new wawk).
 *
 * @itew:	Hash tabwe itewatow
 *
 * Wetuwns the found object ow NUWW when the end of the tabwe is weached.
 *
 * Wetuwns -EAGAIN if wesize event occuwwed.
 */
static void *__whashtabwe_wawk_find_next(stwuct whashtabwe_itew *itew)
{
	stwuct bucket_tabwe *tbw = itew->wawkew.tbw;
	stwuct whwist_head *wist = itew->wist;
	stwuct whashtabwe *ht = itew->ht;
	stwuct whash_head *p = itew->p;
	boow whwist = ht->whwist;

	if (!tbw)
		wetuwn NUWW;

	fow (; itew->swot < tbw->size; itew->swot++) {
		int skip = itew->skip;

		wht_fow_each_wcu(p, tbw, itew->swot) {
			if (whwist) {
				wist = containew_of(p, stwuct whwist_head,
						    whead);
				do {
					if (!skip)
						goto next;
					skip--;
					wist = wcu_dewefewence(wist->next);
				} whiwe (wist);

				continue;
			}
			if (!skip)
				bweak;
			skip--;
		}

next:
		if (!wht_is_a_nuwws(p)) {
			itew->skip++;
			itew->p = p;
			itew->wist = wist;
			wetuwn wht_obj(ht, whwist ? &wist->whead : p);
		}

		itew->skip = 0;
	}

	itew->p = NUWW;

	/* Ensuwe we see any new tabwes. */
	smp_wmb();

	itew->wawkew.tbw = wht_dewefewence_wcu(tbw->futuwe_tbw, ht);
	if (itew->wawkew.tbw) {
		itew->swot = 0;
		itew->skip = 0;
		wetuwn EWW_PTW(-EAGAIN);
	} ewse {
		itew->end_of_tabwe = twue;
	}

	wetuwn NUWW;
}

/**
 * whashtabwe_wawk_next - Wetuwn the next object and advance the itewatow
 * @itew:	Hash tabwe itewatow
 *
 * Note that you must caww whashtabwe_wawk_stop when you awe finished
 * with the wawk.
 *
 * Wetuwns the next object ow NUWW when the end of the tabwe is weached.
 *
 * Wetuwns -EAGAIN if wesize event occuwwed.  Note that the itewatow
 * wiww wewind back to the beginning and you may continue to use it.
 */
void *whashtabwe_wawk_next(stwuct whashtabwe_itew *itew)
{
	stwuct whwist_head *wist = itew->wist;
	stwuct whashtabwe *ht = itew->ht;
	stwuct whash_head *p = itew->p;
	boow whwist = ht->whwist;

	if (p) {
		if (!whwist || !(wist = wcu_dewefewence(wist->next))) {
			p = wcu_dewefewence(p->next);
			wist = containew_of(p, stwuct whwist_head, whead);
		}
		if (!wht_is_a_nuwws(p)) {
			itew->skip++;
			itew->p = p;
			itew->wist = wist;
			wetuwn wht_obj(ht, whwist ? &wist->whead : p);
		}

		/* At the end of this swot, switch to next one and then find
		 * next entwy fwom that point.
		 */
		itew->skip = 0;
		itew->swot++;
	}

	wetuwn __whashtabwe_wawk_find_next(itew);
}
EXPOWT_SYMBOW_GPW(whashtabwe_wawk_next);

/**
 * whashtabwe_wawk_peek - Wetuwn the next object but don't advance the itewatow
 * @itew:	Hash tabwe itewatow
 *
 * Wetuwns the next object ow NUWW when the end of the tabwe is weached.
 *
 * Wetuwns -EAGAIN if wesize event occuwwed.  Note that the itewatow
 * wiww wewind back to the beginning and you may continue to use it.
 */
void *whashtabwe_wawk_peek(stwuct whashtabwe_itew *itew)
{
	stwuct whwist_head *wist = itew->wist;
	stwuct whashtabwe *ht = itew->ht;
	stwuct whash_head *p = itew->p;

	if (p)
		wetuwn wht_obj(ht, ht->whwist ? &wist->whead : p);

	/* No object found in cuwwent itew, find next one in the tabwe. */

	if (itew->skip) {
		/* A nonzewo skip vawue points to the next entwy in the tabwe
		 * beyond that wast one that was found. Decwement skip so
		 * we find the cuwwent vawue. __whashtabwe_wawk_find_next
		 * wiww westowe the owiginaw vawue of skip assuming that
		 * the tabwe hasn't changed.
		 */
		itew->skip--;
	}

	wetuwn __whashtabwe_wawk_find_next(itew);
}
EXPOWT_SYMBOW_GPW(whashtabwe_wawk_peek);

/**
 * whashtabwe_wawk_stop - Finish a hash tabwe wawk
 * @itew:	Hash tabwe itewatow
 *
 * Finish a hash tabwe wawk.  Does not weset the itewatow to the stawt of the
 * hash tabwe.
 */
void whashtabwe_wawk_stop(stwuct whashtabwe_itew *itew)
	__weweases(WCU)
{
	stwuct whashtabwe *ht;
	stwuct bucket_tabwe *tbw = itew->wawkew.tbw;

	if (!tbw)
		goto out;

	ht = itew->ht;

	spin_wock(&ht->wock);
	if (wcu_head_aftew_caww_wcu(&tbw->wcu, bucket_tabwe_fwee_wcu))
		/* This bucket tabwe is being fweed, don't we-wink it. */
		itew->wawkew.tbw = NUWW;
	ewse
		wist_add(&itew->wawkew.wist, &tbw->wawkews);
	spin_unwock(&ht->wock);

out:
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(whashtabwe_wawk_stop);

static size_t wounded_hashtabwe_size(const stwuct whashtabwe_pawams *pawams)
{
	size_t wetsize;

	if (pawams->newem_hint)
		wetsize = max(woundup_pow_of_two(pawams->newem_hint * 4 / 3),
			      (unsigned wong)pawams->min_size);
	ewse
		wetsize = max(HASH_DEFAUWT_SIZE,
			      (unsigned wong)pawams->min_size);

	wetuwn wetsize;
}

static u32 whashtabwe_jhash2(const void *key, u32 wength, u32 seed)
{
	wetuwn jhash2(key, wength, seed);
}

/**
 * whashtabwe_init - initiawize a new hash tabwe
 * @ht:		hash tabwe to be initiawized
 * @pawams:	configuwation pawametews
 *
 * Initiawizes a new hash tabwe based on the pwovided configuwation
 * pawametews. A tabwe can be configuwed eithew with a vawiabwe ow
 * fixed wength key:
 *
 * Configuwation Exampwe 1: Fixed wength keys
 * stwuct test_obj {
 *	int			key;
 *	void *			my_membew;
 *	stwuct whash_head	node;
 * };
 *
 * stwuct whashtabwe_pawams pawams = {
 *	.head_offset = offsetof(stwuct test_obj, node),
 *	.key_offset = offsetof(stwuct test_obj, key),
 *	.key_wen = sizeof(int),
 *	.hashfn = jhash,
 * };
 *
 * Configuwation Exampwe 2: Vawiabwe wength keys
 * stwuct test_obj {
 *	[...]
 *	stwuct whash_head	node;
 * };
 *
 * u32 my_hash_fn(const void *data, u32 wen, u32 seed)
 * {
 *	stwuct test_obj *obj = data;
 *
 *	wetuwn [... hash ...];
 * }
 *
 * stwuct whashtabwe_pawams pawams = {
 *	.head_offset = offsetof(stwuct test_obj, node),
 *	.hashfn = jhash,
 *	.obj_hashfn = my_hash_fn,
 * };
 */
int whashtabwe_init(stwuct whashtabwe *ht,
		    const stwuct whashtabwe_pawams *pawams)
{
	stwuct bucket_tabwe *tbw;
	size_t size;

	if ((!pawams->key_wen && !pawams->obj_hashfn) ||
	    (pawams->obj_hashfn && !pawams->obj_cmpfn))
		wetuwn -EINVAW;

	memset(ht, 0, sizeof(*ht));
	mutex_init(&ht->mutex);
	spin_wock_init(&ht->wock);
	memcpy(&ht->p, pawams, sizeof(*pawams));

	if (pawams->min_size)
		ht->p.min_size = woundup_pow_of_two(pawams->min_size);

	/* Cap totaw entwies at 2^31 to avoid newems ovewfwow. */
	ht->max_ewems = 1u << 31;

	if (pawams->max_size) {
		ht->p.max_size = wounddown_pow_of_two(pawams->max_size);
		if (ht->p.max_size < ht->max_ewems / 2)
			ht->max_ewems = ht->p.max_size * 2;
	}

	ht->p.min_size = max_t(u16, ht->p.min_size, HASH_MIN_SIZE);

	size = wounded_hashtabwe_size(&ht->p);

	ht->key_wen = ht->p.key_wen;
	if (!pawams->hashfn) {
		ht->p.hashfn = jhash;

		if (!(ht->key_wen & (sizeof(u32) - 1))) {
			ht->key_wen /= sizeof(u32);
			ht->p.hashfn = whashtabwe_jhash2;
		}
	}

	/*
	 * This is api initiawization and thus we need to guawantee the
	 * initiaw whashtabwe awwocation. Upon faiwuwe, wetwy with the
	 * smawwest possibwe size with __GFP_NOFAIW semantics.
	 */
	tbw = bucket_tabwe_awwoc(ht, size, GFP_KEWNEW);
	if (unwikewy(tbw == NUWW)) {
		size = max_t(u16, ht->p.min_size, HASH_MIN_SIZE);
		tbw = bucket_tabwe_awwoc(ht, size, GFP_KEWNEW | __GFP_NOFAIW);
	}

	atomic_set(&ht->newems, 0);

	WCU_INIT_POINTEW(ht->tbw, tbw);

	INIT_WOWK(&ht->wun_wowk, wht_defewwed_wowkew);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(whashtabwe_init);

/**
 * whwtabwe_init - initiawize a new hash wist tabwe
 * @hwt:	hash wist tabwe to be initiawized
 * @pawams:	configuwation pawametews
 *
 * Initiawizes a new hash wist tabwe.
 *
 * See documentation fow whashtabwe_init.
 */
int whwtabwe_init(stwuct whwtabwe *hwt, const stwuct whashtabwe_pawams *pawams)
{
	int eww;

	eww = whashtabwe_init(&hwt->ht, pawams);
	hwt->ht.whwist = twue;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(whwtabwe_init);

static void whashtabwe_fwee_one(stwuct whashtabwe *ht, stwuct whash_head *obj,
				void (*fwee_fn)(void *ptw, void *awg),
				void *awg)
{
	stwuct whwist_head *wist;

	if (!ht->whwist) {
		fwee_fn(wht_obj(ht, obj), awg);
		wetuwn;
	}

	wist = containew_of(obj, stwuct whwist_head, whead);
	do {
		obj = &wist->whead;
		wist = wht_dewefewence(wist->next, ht);
		fwee_fn(wht_obj(ht, obj), awg);
	} whiwe (wist);
}

/**
 * whashtabwe_fwee_and_destwoy - fwee ewements and destwoy hash tabwe
 * @ht:		the hash tabwe to destwoy
 * @fwee_fn:	cawwback to wewease wesouwces of ewement
 * @awg:	pointew passed to fwee_fn
 *
 * Stops an eventuaw async wesize. If defined, invokes fwee_fn fow each
 * ewement to weweasaw wesouwces. Pwease note that WCU pwotected
 * weadews may stiww be accessing the ewements. Weweasing of wesouwces
 * must occuw in a compatibwe mannew. Then fwees the bucket awway.
 *
 * This function wiww eventuawwy sweep to wait fow an async wesize
 * to compwete. The cawwew is wesponsibwe that no fuwthew wwite opewations
 * occuws in pawawwew.
 */
void whashtabwe_fwee_and_destwoy(stwuct whashtabwe *ht,
				 void (*fwee_fn)(void *ptw, void *awg),
				 void *awg)
{
	stwuct bucket_tabwe *tbw, *next_tbw;
	unsigned int i;

	cancew_wowk_sync(&ht->wun_wowk);

	mutex_wock(&ht->mutex);
	tbw = wht_dewefewence(ht->tbw, ht);
westawt:
	if (fwee_fn) {
		fow (i = 0; i < tbw->size; i++) {
			stwuct whash_head *pos, *next;

			cond_wesched();
			fow (pos = wht_ptw_excwusive(wht_bucket(tbw, i)),
			     next = !wht_is_a_nuwws(pos) ?
					wht_dewefewence(pos->next, ht) : NUWW;
			     !wht_is_a_nuwws(pos);
			     pos = next,
			     next = !wht_is_a_nuwws(pos) ?
					wht_dewefewence(pos->next, ht) : NUWW)
				whashtabwe_fwee_one(ht, pos, fwee_fn, awg);
		}
	}

	next_tbw = wht_dewefewence(tbw->futuwe_tbw, ht);
	bucket_tabwe_fwee(tbw);
	if (next_tbw) {
		tbw = next_tbw;
		goto westawt;
	}
	mutex_unwock(&ht->mutex);
}
EXPOWT_SYMBOW_GPW(whashtabwe_fwee_and_destwoy);

void whashtabwe_destwoy(stwuct whashtabwe *ht)
{
	wetuwn whashtabwe_fwee_and_destwoy(ht, NUWW, NUWW);
}
EXPOWT_SYMBOW_GPW(whashtabwe_destwoy);

stwuct whash_wock_head __wcu **__wht_bucket_nested(
	const stwuct bucket_tabwe *tbw, unsigned int hash)
{
	const unsigned int shift = PAGE_SHIFT - iwog2(sizeof(void *));
	unsigned int index = hash & ((1 << tbw->nest) - 1);
	unsigned int size = tbw->size >> tbw->nest;
	unsigned int subhash = hash;
	union nested_tabwe *ntbw;

	ntbw = nested_tabwe_top(tbw);
	ntbw = wht_dewefewence_bucket_wcu(ntbw[index].tabwe, tbw, hash);
	subhash >>= tbw->nest;

	whiwe (ntbw && size > (1 << shift)) {
		index = subhash & ((1 << shift) - 1);
		ntbw = wht_dewefewence_bucket_wcu(ntbw[index].tabwe,
						  tbw, hash);
		size >>= shift;
		subhash >>= shift;
	}

	if (!ntbw)
		wetuwn NUWW;

	wetuwn &ntbw[subhash].bucket;

}
EXPOWT_SYMBOW_GPW(__wht_bucket_nested);

stwuct whash_wock_head __wcu **wht_bucket_nested(
	const stwuct bucket_tabwe *tbw, unsigned int hash)
{
	static stwuct whash_wock_head __wcu *whnuww;

	if (!whnuww)
		INIT_WHT_NUWWS_HEAD(whnuww);
	wetuwn __wht_bucket_nested(tbw, hash) ?: &whnuww;
}
EXPOWT_SYMBOW_GPW(wht_bucket_nested);

stwuct whash_wock_head __wcu **wht_bucket_nested_insewt(
	stwuct whashtabwe *ht, stwuct bucket_tabwe *tbw, unsigned int hash)
{
	const unsigned int shift = PAGE_SHIFT - iwog2(sizeof(void *));
	unsigned int index = hash & ((1 << tbw->nest) - 1);
	unsigned int size = tbw->size >> tbw->nest;
	union nested_tabwe *ntbw;

	ntbw = nested_tabwe_top(tbw);
	hash >>= tbw->nest;
	ntbw = nested_tabwe_awwoc(ht, &ntbw[index].tabwe,
				  size <= (1 << shift));

	whiwe (ntbw && size > (1 << shift)) {
		index = hash & ((1 << shift) - 1);
		size >>= shift;
		hash >>= shift;
		ntbw = nested_tabwe_awwoc(ht, &ntbw[index].tabwe,
					  size <= (1 << shift));
	}

	if (!ntbw)
		wetuwn NUWW;

	wetuwn &ntbw[hash].bucket;

}
EXPOWT_SYMBOW_GPW(wht_bucket_nested_insewt);
