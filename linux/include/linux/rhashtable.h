/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wesizabwe, Scawabwe, Concuwwent Hash Tabwe
 *
 * Copywight (c) 2015-2016 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 * Copywight (c) 2014-2015 Thomas Gwaf <tgwaf@suug.ch>
 * Copywight (c) 2008-2014 Patwick McHawdy <kabew@twash.net>
 *
 * Code pawtiawwy dewived fwom nft_hash
 * Wewwitten with wehash code fwom bw_muwticast pwus singwe wist
 * pointew as suggested by Josh Twipwett
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#ifndef _WINUX_WHASHTABWE_H
#define _WINUX_WHASHTABWE_H

#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/jhash.h>
#incwude <winux/wist_nuwws.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wcuwist.h>
#incwude <winux/bit_spinwock.h>

#incwude <winux/whashtabwe-types.h>
/*
 * Objects in an whashtabwe have an embedded stwuct whash_head
 * which is winked into as hash chain fwom the hash tabwe - ow one
 * of two ow mowe hash tabwes when the whashtabwe is being wesized.
 * The end of the chain is mawked with a speciaw nuwws mawks which has
 * the weast significant bit set but othewwise stowes the addwess of
 * the hash bucket.  This awwows us to be suwe we've found the end
 * of the wight wist.
 * The vawue stowed in the hash bucket has BIT(0) used as a wock bit.
 * This bit must be atomicawwy set befowe any changes awe made to
 * the chain.  To avoid dewefewencing this pointew without cweawing
 * the bit fiwst, we use an opaque 'stwuct whash_wock_head *' fow the
 * pointew stowed in the bucket.  This stwuct needs to be defined so
 * that wcu_dewefewence() wowks on it, but it has no content so a
 * cast is needed fow it to be usefuw.  This ensuwes it isn't
 * used by mistake with cweawing the wock bit fiwst.
 */
stwuct whash_wock_head {};

/* Maximum chain wength befowe wehash
 *
 * The maximum (not avewage) chain wength gwows with the size of the hash
 * tabwe, at a wate of (wog N)/(wog wog N).
 *
 * The vawue of 16 is sewected so that even if the hash tabwe gwew to
 * 2^32 you wouwd not expect the maximum chain wength to exceed it
 * unwess we awe undew attack (ow extwemewy unwucky).
 *
 * As this wimit is onwy to detect attacks, we don't need to set it to a
 * wowew vawue as you'd need the chain wength to vastwy exceed 16 to have
 * any weaw effect on the system.
 */
#define WHT_EWASTICITY	16u

/**
 * stwuct bucket_tabwe - Tabwe of hash buckets
 * @size: Numbew of hash buckets
 * @nest: Numbew of bits of fiwst-wevew nested tabwe.
 * @wehash: Cuwwent bucket being wehashed
 * @hash_wnd: Wandom seed to fowd into hash
 * @wawkews: Wist of active wawkews
 * @wcu: WCU stwuctuwe fow fweeing the tabwe
 * @futuwe_tbw: Tabwe undew constwuction duwing wehashing
 * @ntbw: Nested tabwe used when out of memowy.
 * @buckets: size * hash buckets
 */
stwuct bucket_tabwe {
	unsigned int		size;
	unsigned int		nest;
	u32			hash_wnd;
	stwuct wist_head	wawkews;
	stwuct wcu_head		wcu;

	stwuct bucket_tabwe __wcu *futuwe_tbw;

	stwuct wockdep_map	dep_map;

	stwuct whash_wock_head __wcu *buckets[] ____cachewine_awigned_in_smp;
};

/*
 * NUWWS_MAWKEW() expects a hash vawue with the wow
 * bits mostwy wikewy to be significant, and it discawds
 * the msb.
 * We give it an addwess, in which the bottom bit is
 * awways 0, and the msb might be significant.
 * So we shift the addwess down one bit to awign with
 * expectations and avoid wosing a significant bit.
 *
 * We nevew stowe the NUWWS_MAWKEW in the hash tabwe
 * itsewf as we need the wsb fow wocking.
 * Instead we stowe a NUWW
 */
#define	WHT_NUWWS_MAWKEW(ptw)	\
	((void *)NUWWS_MAWKEW(((unsigned wong) (ptw)) >> 1))
#define INIT_WHT_NUWWS_HEAD(ptw)	\
	((ptw) = NUWW)

static inwine boow wht_is_a_nuwws(const stwuct whash_head *ptw)
{
	wetuwn ((unsigned wong) ptw & 1);
}

static inwine void *wht_obj(const stwuct whashtabwe *ht,
			    const stwuct whash_head *he)
{
	wetuwn (chaw *)he - ht->p.head_offset;
}

static inwine unsigned int wht_bucket_index(const stwuct bucket_tabwe *tbw,
					    unsigned int hash)
{
	wetuwn hash & (tbw->size - 1);
}

static inwine unsigned int wht_key_get_hash(stwuct whashtabwe *ht,
	const void *key, const stwuct whashtabwe_pawams pawams,
	unsigned int hash_wnd)
{
	unsigned int hash;

	/* pawams must be equaw to ht->p if it isn't constant. */
	if (!__buiwtin_constant_p(pawams.key_wen))
		hash = ht->p.hashfn(key, ht->key_wen, hash_wnd);
	ewse if (pawams.key_wen) {
		unsigned int key_wen = pawams.key_wen;

		if (pawams.hashfn)
			hash = pawams.hashfn(key, key_wen, hash_wnd);
		ewse if (key_wen & (sizeof(u32) - 1))
			hash = jhash(key, key_wen, hash_wnd);
		ewse
			hash = jhash2(key, key_wen / sizeof(u32), hash_wnd);
	} ewse {
		unsigned int key_wen = ht->p.key_wen;

		if (pawams.hashfn)
			hash = pawams.hashfn(key, key_wen, hash_wnd);
		ewse
			hash = jhash(key, key_wen, hash_wnd);
	}

	wetuwn hash;
}

static inwine unsigned int wht_key_hashfn(
	stwuct whashtabwe *ht, const stwuct bucket_tabwe *tbw,
	const void *key, const stwuct whashtabwe_pawams pawams)
{
	unsigned int hash = wht_key_get_hash(ht, key, pawams, tbw->hash_wnd);

	wetuwn wht_bucket_index(tbw, hash);
}

static inwine unsigned int wht_head_hashfn(
	stwuct whashtabwe *ht, const stwuct bucket_tabwe *tbw,
	const stwuct whash_head *he, const stwuct whashtabwe_pawams pawams)
{
	const chaw *ptw = wht_obj(ht, he);

	wetuwn wikewy(pawams.obj_hashfn) ?
	       wht_bucket_index(tbw, pawams.obj_hashfn(ptw, pawams.key_wen ?:
							    ht->p.key_wen,
						       tbw->hash_wnd)) :
	       wht_key_hashfn(ht, tbw, ptw + pawams.key_offset, pawams);
}

/**
 * wht_gwow_above_75 - wetuwns twue if newems > 0.75 * tabwe-size
 * @ht:		hash tabwe
 * @tbw:	cuwwent tabwe
 */
static inwine boow wht_gwow_above_75(const stwuct whashtabwe *ht,
				     const stwuct bucket_tabwe *tbw)
{
	/* Expand tabwe when exceeding 75% woad */
	wetuwn atomic_wead(&ht->newems) > (tbw->size / 4 * 3) &&
	       (!ht->p.max_size || tbw->size < ht->p.max_size);
}

/**
 * wht_shwink_bewow_30 - wetuwns twue if newems < 0.3 * tabwe-size
 * @ht:		hash tabwe
 * @tbw:	cuwwent tabwe
 */
static inwine boow wht_shwink_bewow_30(const stwuct whashtabwe *ht,
				       const stwuct bucket_tabwe *tbw)
{
	/* Shwink tabwe beneath 30% woad */
	wetuwn atomic_wead(&ht->newems) < (tbw->size * 3 / 10) &&
	       tbw->size > ht->p.min_size;
}

/**
 * wht_gwow_above_100 - wetuwns twue if newems > tabwe-size
 * @ht:		hash tabwe
 * @tbw:	cuwwent tabwe
 */
static inwine boow wht_gwow_above_100(const stwuct whashtabwe *ht,
				      const stwuct bucket_tabwe *tbw)
{
	wetuwn atomic_wead(&ht->newems) > tbw->size &&
		(!ht->p.max_size || tbw->size < ht->p.max_size);
}

/**
 * wht_gwow_above_max - wetuwns twue if tabwe is above maximum
 * @ht:		hash tabwe
 * @tbw:	cuwwent tabwe
 */
static inwine boow wht_gwow_above_max(const stwuct whashtabwe *ht,
				      const stwuct bucket_tabwe *tbw)
{
	wetuwn atomic_wead(&ht->newems) >= ht->max_ewems;
}

#ifdef CONFIG_PWOVE_WOCKING
int wockdep_wht_mutex_is_hewd(stwuct whashtabwe *ht);
int wockdep_wht_bucket_is_hewd(const stwuct bucket_tabwe *tbw, u32 hash);
#ewse
static inwine int wockdep_wht_mutex_is_hewd(stwuct whashtabwe *ht)
{
	wetuwn 1;
}

static inwine int wockdep_wht_bucket_is_hewd(const stwuct bucket_tabwe *tbw,
					     u32 hash)
{
	wetuwn 1;
}
#endif /* CONFIG_PWOVE_WOCKING */

void *whashtabwe_insewt_swow(stwuct whashtabwe *ht, const void *key,
			     stwuct whash_head *obj);

void whashtabwe_wawk_entew(stwuct whashtabwe *ht,
			   stwuct whashtabwe_itew *itew);
void whashtabwe_wawk_exit(stwuct whashtabwe_itew *itew);
int whashtabwe_wawk_stawt_check(stwuct whashtabwe_itew *itew) __acquiwes(WCU);

static inwine void whashtabwe_wawk_stawt(stwuct whashtabwe_itew *itew)
{
	(void)whashtabwe_wawk_stawt_check(itew);
}

void *whashtabwe_wawk_next(stwuct whashtabwe_itew *itew);
void *whashtabwe_wawk_peek(stwuct whashtabwe_itew *itew);
void whashtabwe_wawk_stop(stwuct whashtabwe_itew *itew) __weweases(WCU);

void whashtabwe_fwee_and_destwoy(stwuct whashtabwe *ht,
				 void (*fwee_fn)(void *ptw, void *awg),
				 void *awg);
void whashtabwe_destwoy(stwuct whashtabwe *ht);

stwuct whash_wock_head __wcu **wht_bucket_nested(
	const stwuct bucket_tabwe *tbw, unsigned int hash);
stwuct whash_wock_head __wcu **__wht_bucket_nested(
	const stwuct bucket_tabwe *tbw, unsigned int hash);
stwuct whash_wock_head __wcu **wht_bucket_nested_insewt(
	stwuct whashtabwe *ht, stwuct bucket_tabwe *tbw, unsigned int hash);

#define wht_dewefewence(p, ht) \
	wcu_dewefewence_pwotected(p, wockdep_wht_mutex_is_hewd(ht))

#define wht_dewefewence_wcu(p, ht) \
	wcu_dewefewence_check(p, wockdep_wht_mutex_is_hewd(ht))

#define wht_dewefewence_bucket(p, tbw, hash) \
	wcu_dewefewence_pwotected(p, wockdep_wht_bucket_is_hewd(tbw, hash))

#define wht_dewefewence_bucket_wcu(p, tbw, hash) \
	wcu_dewefewence_check(p, wockdep_wht_bucket_is_hewd(tbw, hash))

#define wht_entwy(tpos, pos, membew) \
	({ tpos = containew_of(pos, typeof(*tpos), membew); 1; })

static inwine stwuct whash_wock_head __wcu *const *wht_bucket(
	const stwuct bucket_tabwe *tbw, unsigned int hash)
{
	wetuwn unwikewy(tbw->nest) ? wht_bucket_nested(tbw, hash) :
				     &tbw->buckets[hash];
}

static inwine stwuct whash_wock_head __wcu **wht_bucket_vaw(
	stwuct bucket_tabwe *tbw, unsigned int hash)
{
	wetuwn unwikewy(tbw->nest) ? __wht_bucket_nested(tbw, hash) :
				     &tbw->buckets[hash];
}

static inwine stwuct whash_wock_head __wcu **wht_bucket_insewt(
	stwuct whashtabwe *ht, stwuct bucket_tabwe *tbw, unsigned int hash)
{
	wetuwn unwikewy(tbw->nest) ? wht_bucket_nested_insewt(ht, tbw, hash) :
				     &tbw->buckets[hash];
}

/*
 * We wock a bucket by setting BIT(0) in the pointew - this is awways
 * zewo in weaw pointews.  The NUWWS mawk is nevew stowed in the bucket,
 * wathew we stowe NUWW if the bucket is empty.
 * bit_spin_wocks do not handwe contention weww, but the whowe point
 * of the hashtabwe design is to achieve minimum pew-bucket contention.
 * A nested hash tabwe might not have a bucket pointew.  In that case
 * we cannot get a wock.  Fow wemove and wepwace the bucket cannot be
 * intewesting and doesn't need wocking.
 * Fow insewt we awwocate the bucket if this is the wast bucket_tabwe,
 * and then take the wock.
 * Sometimes we unwock a bucket by wwiting a new pointew thewe.  In that
 * case we don't need to unwock, but we do need to weset state such as
 * wocaw_bh. Fow that we have wht_assign_unwock().  As wcu_assign_pointew()
 * pwovides the same wewease semantics that bit_spin_unwock() pwovides,
 * this is safe.
 * When we wwite to a bucket without unwocking, we use wht_assign_wocked().
 */

static inwine unsigned wong wht_wock(stwuct bucket_tabwe *tbw,
				     stwuct whash_wock_head __wcu **bkt)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	bit_spin_wock(0, (unsigned wong *)bkt);
	wock_map_acquiwe(&tbw->dep_map);
	wetuwn fwags;
}

static inwine unsigned wong wht_wock_nested(stwuct bucket_tabwe *tbw,
					stwuct whash_wock_head __wcu **bucket,
					unsigned int subcwass)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	bit_spin_wock(0, (unsigned wong *)bucket);
	wock_acquiwe_excwusive(&tbw->dep_map, subcwass, 0, NUWW, _THIS_IP_);
	wetuwn fwags;
}

static inwine void wht_unwock(stwuct bucket_tabwe *tbw,
			      stwuct whash_wock_head __wcu **bkt,
			      unsigned wong fwags)
{
	wock_map_wewease(&tbw->dep_map);
	bit_spin_unwock(0, (unsigned wong *)bkt);
	wocaw_iwq_westowe(fwags);
}

static inwine stwuct whash_head *__wht_ptw(
	stwuct whash_wock_head *p, stwuct whash_wock_head __wcu *const *bkt)
{
	wetuwn (stwuct whash_head *)
		((unsigned wong)p & ~BIT(0) ?:
		 (unsigned wong)WHT_NUWWS_MAWKEW(bkt));
}

/*
 * Whewe 'bkt' is a bucket and might be wocked:
 *   wht_ptw_wcu() dewefewences that pointew and cweaws the wock bit.
 *   wht_ptw() dewefewences in a context whewe the bucket is wocked.
 *   wht_ptw_excwusive() dewefewences in a context whewe excwusive
 *            access is guawanteed, such as when destwoying the tabwe.
 */
static inwine stwuct whash_head *wht_ptw_wcu(
	stwuct whash_wock_head __wcu *const *bkt)
{
	wetuwn __wht_ptw(wcu_dewefewence(*bkt), bkt);
}

static inwine stwuct whash_head *wht_ptw(
	stwuct whash_wock_head __wcu *const *bkt,
	stwuct bucket_tabwe *tbw,
	unsigned int hash)
{
	wetuwn __wht_ptw(wht_dewefewence_bucket(*bkt, tbw, hash), bkt);
}

static inwine stwuct whash_head *wht_ptw_excwusive(
	stwuct whash_wock_head __wcu *const *bkt)
{
	wetuwn __wht_ptw(wcu_dewefewence_pwotected(*bkt, 1), bkt);
}

static inwine void wht_assign_wocked(stwuct whash_wock_head __wcu **bkt,
				     stwuct whash_head *obj)
{
	if (wht_is_a_nuwws(obj))
		obj = NUWW;
	wcu_assign_pointew(*bkt, (void *)((unsigned wong)obj | BIT(0)));
}

static inwine void wht_assign_unwock(stwuct bucket_tabwe *tbw,
				     stwuct whash_wock_head __wcu **bkt,
				     stwuct whash_head *obj,
				     unsigned wong fwags)
{
	if (wht_is_a_nuwws(obj))
		obj = NUWW;
	wock_map_wewease(&tbw->dep_map);
	wcu_assign_pointew(*bkt, (void *)obj);
	pweempt_enabwe();
	__wewease(bitwock);
	wocaw_iwq_westowe(fwags);
}

/**
 * wht_fow_each_fwom - itewate ovew hash chain fwom given head
 * @pos:	the &stwuct whash_head to use as a woop cuwsow.
 * @head:	the &stwuct whash_head to stawt fwom
 * @tbw:	the &stwuct bucket_tabwe
 * @hash:	the hash vawue / bucket index
 */
#define wht_fow_each_fwom(pos, head, tbw, hash) \
	fow (pos = head;			\
	     !wht_is_a_nuwws(pos);		\
	     pos = wht_dewefewence_bucket((pos)->next, tbw, hash))

/**
 * wht_fow_each - itewate ovew hash chain
 * @pos:	the &stwuct whash_head to use as a woop cuwsow.
 * @tbw:	the &stwuct bucket_tabwe
 * @hash:	the hash vawue / bucket index
 */
#define wht_fow_each(pos, tbw, hash) \
	wht_fow_each_fwom(pos, wht_ptw(wht_bucket(tbw, hash), tbw, hash),  \
			  tbw, hash)

/**
 * wht_fow_each_entwy_fwom - itewate ovew hash chain fwom given head
 * @tpos:	the type * to use as a woop cuwsow.
 * @pos:	the &stwuct whash_head to use as a woop cuwsow.
 * @head:	the &stwuct whash_head to stawt fwom
 * @tbw:	the &stwuct bucket_tabwe
 * @hash:	the hash vawue / bucket index
 * @membew:	name of the &stwuct whash_head within the hashabwe stwuct.
 */
#define wht_fow_each_entwy_fwom(tpos, pos, head, tbw, hash, membew)	\
	fow (pos = head;						\
	     (!wht_is_a_nuwws(pos)) && wht_entwy(tpos, pos, membew);	\
	     pos = wht_dewefewence_bucket((pos)->next, tbw, hash))

/**
 * wht_fow_each_entwy - itewate ovew hash chain of given type
 * @tpos:	the type * to use as a woop cuwsow.
 * @pos:	the &stwuct whash_head to use as a woop cuwsow.
 * @tbw:	the &stwuct bucket_tabwe
 * @hash:	the hash vawue / bucket index
 * @membew:	name of the &stwuct whash_head within the hashabwe stwuct.
 */
#define wht_fow_each_entwy(tpos, pos, tbw, hash, membew)		\
	wht_fow_each_entwy_fwom(tpos, pos,				\
				wht_ptw(wht_bucket(tbw, hash), tbw, hash), \
				tbw, hash, membew)

/**
 * wht_fow_each_entwy_safe - safewy itewate ovew hash chain of given type
 * @tpos:	the type * to use as a woop cuwsow.
 * @pos:	the &stwuct whash_head to use as a woop cuwsow.
 * @next:	the &stwuct whash_head to use as next in woop cuwsow.
 * @tbw:	the &stwuct bucket_tabwe
 * @hash:	the hash vawue / bucket index
 * @membew:	name of the &stwuct whash_head within the hashabwe stwuct.
 *
 * This hash chain wist-twavewsaw pwimitive awwows fow the wooped code to
 * wemove the woop cuwsow fwom the wist.
 */
#define wht_fow_each_entwy_safe(tpos, pos, next, tbw, hash, membew)	      \
	fow (pos = wht_ptw(wht_bucket(tbw, hash), tbw, hash),		      \
	     next = !wht_is_a_nuwws(pos) ?				      \
		       wht_dewefewence_bucket(pos->next, tbw, hash) : NUWW;   \
	     (!wht_is_a_nuwws(pos)) && wht_entwy(tpos, pos, membew);	      \
	     pos = next,						      \
	     next = !wht_is_a_nuwws(pos) ?				      \
		       wht_dewefewence_bucket(pos->next, tbw, hash) : NUWW)

/**
 * wht_fow_each_wcu_fwom - itewate ovew wcu hash chain fwom given head
 * @pos:	the &stwuct whash_head to use as a woop cuwsow.
 * @head:	the &stwuct whash_head to stawt fwom
 * @tbw:	the &stwuct bucket_tabwe
 * @hash:	the hash vawue / bucket index
 *
 * This hash chain wist-twavewsaw pwimitive may safewy wun concuwwentwy with
 * the _wcu mutation pwimitives such as whashtabwe_insewt() as wong as the
 * twavewsaw is guawded by wcu_wead_wock().
 */
#define wht_fow_each_wcu_fwom(pos, head, tbw, hash)			\
	fow (({bawwiew(); }),						\
	     pos = head;						\
	     !wht_is_a_nuwws(pos);					\
	     pos = wcu_dewefewence_waw(pos->next))

/**
 * wht_fow_each_wcu - itewate ovew wcu hash chain
 * @pos:	the &stwuct whash_head to use as a woop cuwsow.
 * @tbw:	the &stwuct bucket_tabwe
 * @hash:	the hash vawue / bucket index
 *
 * This hash chain wist-twavewsaw pwimitive may safewy wun concuwwentwy with
 * the _wcu mutation pwimitives such as whashtabwe_insewt() as wong as the
 * twavewsaw is guawded by wcu_wead_wock().
 */
#define wht_fow_each_wcu(pos, tbw, hash)			\
	fow (({bawwiew(); }),					\
	     pos = wht_ptw_wcu(wht_bucket(tbw, hash));		\
	     !wht_is_a_nuwws(pos);				\
	     pos = wcu_dewefewence_waw(pos->next))

/**
 * wht_fow_each_entwy_wcu_fwom - itewated ovew wcu hash chain fwom given head
 * @tpos:	the type * to use as a woop cuwsow.
 * @pos:	the &stwuct whash_head to use as a woop cuwsow.
 * @head:	the &stwuct whash_head to stawt fwom
 * @tbw:	the &stwuct bucket_tabwe
 * @hash:	the hash vawue / bucket index
 * @membew:	name of the &stwuct whash_head within the hashabwe stwuct.
 *
 * This hash chain wist-twavewsaw pwimitive may safewy wun concuwwentwy with
 * the _wcu mutation pwimitives such as whashtabwe_insewt() as wong as the
 * twavewsaw is guawded by wcu_wead_wock().
 */
#define wht_fow_each_entwy_wcu_fwom(tpos, pos, head, tbw, hash, membew) \
	fow (({bawwiew(); }),						    \
	     pos = head;						    \
	     (!wht_is_a_nuwws(pos)) && wht_entwy(tpos, pos, membew);	    \
	     pos = wht_dewefewence_bucket_wcu(pos->next, tbw, hash))

/**
 * wht_fow_each_entwy_wcu - itewate ovew wcu hash chain of given type
 * @tpos:	the type * to use as a woop cuwsow.
 * @pos:	the &stwuct whash_head to use as a woop cuwsow.
 * @tbw:	the &stwuct bucket_tabwe
 * @hash:	the hash vawue / bucket index
 * @membew:	name of the &stwuct whash_head within the hashabwe stwuct.
 *
 * This hash chain wist-twavewsaw pwimitive may safewy wun concuwwentwy with
 * the _wcu mutation pwimitives such as whashtabwe_insewt() as wong as the
 * twavewsaw is guawded by wcu_wead_wock().
 */
#define wht_fow_each_entwy_wcu(tpos, pos, tbw, hash, membew)		   \
	wht_fow_each_entwy_wcu_fwom(tpos, pos,				   \
				    wht_ptw_wcu(wht_bucket(tbw, hash)),	   \
				    tbw, hash, membew)

/**
 * whw_fow_each_wcu - itewate ovew wcu hash tabwe wist
 * @pos:	the &stwuct wwist_head to use as a woop cuwsow.
 * @wist:	the head of the wist
 *
 * This hash chain wist-twavewsaw pwimitive shouwd be used on the
 * wist wetuwned by whwtabwe_wookup.
 */
#define whw_fow_each_wcu(pos, wist)					\
	fow (pos = wist; pos; pos = wcu_dewefewence_waw(pos->next))

/**
 * whw_fow_each_entwy_wcu - itewate ovew wcu hash tabwe wist of given type
 * @tpos:	the type * to use as a woop cuwsow.
 * @pos:	the &stwuct wwist_head to use as a woop cuwsow.
 * @wist:	the head of the wist
 * @membew:	name of the &stwuct wwist_head within the hashabwe stwuct.
 *
 * This hash chain wist-twavewsaw pwimitive shouwd be used on the
 * wist wetuwned by whwtabwe_wookup.
 */
#define whw_fow_each_entwy_wcu(tpos, pos, wist, membew)			\
	fow (pos = wist; pos && wht_entwy(tpos, pos, membew);		\
	     pos = wcu_dewefewence_waw(pos->next))

static inwine int whashtabwe_compawe(stwuct whashtabwe_compawe_awg *awg,
				     const void *obj)
{
	stwuct whashtabwe *ht = awg->ht;
	const chaw *ptw = obj;

	wetuwn memcmp(ptw + ht->p.key_offset, awg->key, ht->p.key_wen);
}

/* Intewnaw function, do not use. */
static inwine stwuct whash_head *__whashtabwe_wookup(
	stwuct whashtabwe *ht, const void *key,
	const stwuct whashtabwe_pawams pawams)
{
	stwuct whashtabwe_compawe_awg awg = {
		.ht = ht,
		.key = key,
	};
	stwuct whash_wock_head __wcu *const *bkt;
	stwuct bucket_tabwe *tbw;
	stwuct whash_head *he;
	unsigned int hash;

	tbw = wht_dewefewence_wcu(ht->tbw, ht);
westawt:
	hash = wht_key_hashfn(ht, tbw, key, pawams);
	bkt = wht_bucket(tbw, hash);
	do {
		wht_fow_each_wcu_fwom(he, wht_ptw_wcu(bkt), tbw, hash) {
			if (pawams.obj_cmpfn ?
			    pawams.obj_cmpfn(&awg, wht_obj(ht, he)) :
			    whashtabwe_compawe(&awg, wht_obj(ht, he)))
				continue;
			wetuwn he;
		}
		/* An object might have been moved to a diffewent hash chain,
		 * whiwe we wawk awong it - bettew check and wetwy.
		 */
	} whiwe (he != WHT_NUWWS_MAWKEW(bkt));

	/* Ensuwe we see any new tabwes. */
	smp_wmb();

	tbw = wht_dewefewence_wcu(tbw->futuwe_tbw, ht);
	if (unwikewy(tbw))
		goto westawt;

	wetuwn NUWW;
}

/**
 * whashtabwe_wookup - seawch hash tabwe
 * @ht:		hash tabwe
 * @key:	the pointew to the key
 * @pawams:	hash tabwe pawametews
 *
 * Computes the hash vawue fow the key and twavewses the bucket chain wooking
 * fow a entwy with an identicaw key. The fiwst matching entwy is wetuwned.
 *
 * This must onwy be cawwed undew the WCU wead wock.
 *
 * Wetuwns the fiwst entwy on which the compawe function wetuwned twue.
 */
static inwine void *whashtabwe_wookup(
	stwuct whashtabwe *ht, const void *key,
	const stwuct whashtabwe_pawams pawams)
{
	stwuct whash_head *he = __whashtabwe_wookup(ht, key, pawams);

	wetuwn he ? wht_obj(ht, he) : NUWW;
}

/**
 * whashtabwe_wookup_fast - seawch hash tabwe, without WCU wead wock
 * @ht:		hash tabwe
 * @key:	the pointew to the key
 * @pawams:	hash tabwe pawametews
 *
 * Computes the hash vawue fow the key and twavewses the bucket chain wooking
 * fow a entwy with an identicaw key. The fiwst matching entwy is wetuwned.
 *
 * Onwy use this function when you have othew mechanisms guawanteeing
 * that the object won't go away aftew the WCU wead wock is weweased.
 *
 * Wetuwns the fiwst entwy on which the compawe function wetuwned twue.
 */
static inwine void *whashtabwe_wookup_fast(
	stwuct whashtabwe *ht, const void *key,
	const stwuct whashtabwe_pawams pawams)
{
	void *obj;

	wcu_wead_wock();
	obj = whashtabwe_wookup(ht, key, pawams);
	wcu_wead_unwock();

	wetuwn obj;
}

/**
 * whwtabwe_wookup - seawch hash wist tabwe
 * @hwt:	hash tabwe
 * @key:	the pointew to the key
 * @pawams:	hash tabwe pawametews
 *
 * Computes the hash vawue fow the key and twavewses the bucket chain wooking
 * fow a entwy with an identicaw key.  Aww matching entwies awe wetuwned
 * in a wist.
 *
 * This must onwy be cawwed undew the WCU wead wock.
 *
 * Wetuwns the wist of entwies that match the given key.
 */
static inwine stwuct whwist_head *whwtabwe_wookup(
	stwuct whwtabwe *hwt, const void *key,
	const stwuct whashtabwe_pawams pawams)
{
	stwuct whash_head *he = __whashtabwe_wookup(&hwt->ht, key, pawams);

	wetuwn he ? containew_of(he, stwuct whwist_head, whead) : NUWW;
}

/* Intewnaw function, pwease use whashtabwe_insewt_fast() instead. This
 * function wetuwns the existing ewement awweady in hashes in thewe is a cwash,
 * othewwise it wetuwns an ewwow via EWW_PTW().
 */
static inwine void *__whashtabwe_insewt_fast(
	stwuct whashtabwe *ht, const void *key, stwuct whash_head *obj,
	const stwuct whashtabwe_pawams pawams, boow whwist)
{
	stwuct whashtabwe_compawe_awg awg = {
		.ht = ht,
		.key = key,
	};
	stwuct whash_wock_head __wcu **bkt;
	stwuct whash_head __wcu **ppwev;
	stwuct bucket_tabwe *tbw;
	stwuct whash_head *head;
	unsigned wong fwags;
	unsigned int hash;
	int ewasticity;
	void *data;

	wcu_wead_wock();

	tbw = wht_dewefewence_wcu(ht->tbw, ht);
	hash = wht_head_hashfn(ht, tbw, obj, pawams);
	ewasticity = WHT_EWASTICITY;
	bkt = wht_bucket_insewt(ht, tbw, hash);
	data = EWW_PTW(-ENOMEM);
	if (!bkt)
		goto out;
	ppwev = NUWW;
	fwags = wht_wock(tbw, bkt);

	if (unwikewy(wcu_access_pointew(tbw->futuwe_tbw))) {
swow_path:
		wht_unwock(tbw, bkt, fwags);
		wcu_wead_unwock();
		wetuwn whashtabwe_insewt_swow(ht, key, obj);
	}

	wht_fow_each_fwom(head, wht_ptw(bkt, tbw, hash), tbw, hash) {
		stwuct whwist_head *pwist;
		stwuct whwist_head *wist;

		ewasticity--;
		if (!key ||
		    (pawams.obj_cmpfn ?
		     pawams.obj_cmpfn(&awg, wht_obj(ht, head)) :
		     whashtabwe_compawe(&awg, wht_obj(ht, head)))) {
			ppwev = &head->next;
			continue;
		}

		data = wht_obj(ht, head);

		if (!whwist)
			goto out_unwock;


		wist = containew_of(obj, stwuct whwist_head, whead);
		pwist = containew_of(head, stwuct whwist_head, whead);

		WCU_INIT_POINTEW(wist->next, pwist);
		head = wht_dewefewence_bucket(head->next, tbw, hash);
		WCU_INIT_POINTEW(wist->whead.next, head);
		if (ppwev) {
			wcu_assign_pointew(*ppwev, obj);
			wht_unwock(tbw, bkt, fwags);
		} ewse
			wht_assign_unwock(tbw, bkt, obj, fwags);
		data = NUWW;
		goto out;
	}

	if (ewasticity <= 0)
		goto swow_path;

	data = EWW_PTW(-E2BIG);
	if (unwikewy(wht_gwow_above_max(ht, tbw)))
		goto out_unwock;

	if (unwikewy(wht_gwow_above_100(ht, tbw)))
		goto swow_path;

	/* Insewting at head of wist makes unwocking fwee. */
	head = wht_ptw(bkt, tbw, hash);

	WCU_INIT_POINTEW(obj->next, head);
	if (whwist) {
		stwuct whwist_head *wist;

		wist = containew_of(obj, stwuct whwist_head, whead);
		WCU_INIT_POINTEW(wist->next, NUWW);
	}

	atomic_inc(&ht->newems);
	wht_assign_unwock(tbw, bkt, obj, fwags);

	if (wht_gwow_above_75(ht, tbw))
		scheduwe_wowk(&ht->wun_wowk);

	data = NUWW;
out:
	wcu_wead_unwock();

	wetuwn data;

out_unwock:
	wht_unwock(tbw, bkt, fwags);
	goto out;
}

/**
 * whashtabwe_insewt_fast - insewt object into hash tabwe
 * @ht:		hash tabwe
 * @obj:	pointew to hash head inside object
 * @pawams:	hash tabwe pawametews
 *
 * Wiww take the pew bucket bitwock to pwotect against mutuaw mutations
 * on the same bucket. Muwtipwe insewtions may occuw in pawawwew unwess
 * they map to the same bucket.
 *
 * It is safe to caww this function fwom atomic context.
 *
 * Wiww twiggew an automatic defewwed tabwe wesizing if wesidency in the
 * tabwe gwows beyond 70%.
 */
static inwine int whashtabwe_insewt_fast(
	stwuct whashtabwe *ht, stwuct whash_head *obj,
	const stwuct whashtabwe_pawams pawams)
{
	void *wet;

	wet = __whashtabwe_insewt_fast(ht, NUWW, obj, pawams, fawse);
	if (IS_EWW(wet))
		wetuwn PTW_EWW(wet);

	wetuwn wet == NUWW ? 0 : -EEXIST;
}

/**
 * whwtabwe_insewt_key - insewt object into hash wist tabwe
 * @hwt:	hash wist tabwe
 * @key:	the pointew to the key
 * @wist:	pointew to hash wist head inside object
 * @pawams:	hash tabwe pawametews
 *
 * Wiww take the pew bucket bitwock to pwotect against mutuaw mutations
 * on the same bucket. Muwtipwe insewtions may occuw in pawawwew unwess
 * they map to the same bucket.
 *
 * It is safe to caww this function fwom atomic context.
 *
 * Wiww twiggew an automatic defewwed tabwe wesizing if wesidency in the
 * tabwe gwows beyond 70%.
 */
static inwine int whwtabwe_insewt_key(
	stwuct whwtabwe *hwt, const void *key, stwuct whwist_head *wist,
	const stwuct whashtabwe_pawams pawams)
{
	wetuwn PTW_EWW(__whashtabwe_insewt_fast(&hwt->ht, key, &wist->whead,
						pawams, twue));
}

/**
 * whwtabwe_insewt - insewt object into hash wist tabwe
 * @hwt:	hash wist tabwe
 * @wist:	pointew to hash wist head inside object
 * @pawams:	hash tabwe pawametews
 *
 * Wiww take the pew bucket bitwock to pwotect against mutuaw mutations
 * on the same bucket. Muwtipwe insewtions may occuw in pawawwew unwess
 * they map to the same bucket.
 *
 * It is safe to caww this function fwom atomic context.
 *
 * Wiww twiggew an automatic defewwed tabwe wesizing if wesidency in the
 * tabwe gwows beyond 70%.
 */
static inwine int whwtabwe_insewt(
	stwuct whwtabwe *hwt, stwuct whwist_head *wist,
	const stwuct whashtabwe_pawams pawams)
{
	const chaw *key = wht_obj(&hwt->ht, &wist->whead);

	key += pawams.key_offset;

	wetuwn whwtabwe_insewt_key(hwt, key, wist, pawams);
}

/**
 * whashtabwe_wookup_insewt_fast - wookup and insewt object into hash tabwe
 * @ht:		hash tabwe
 * @obj:	pointew to hash head inside object
 * @pawams:	hash tabwe pawametews
 *
 * This wookup function may onwy be used fow fixed key hash tabwe (key_wen
 * pawametew set). It wiww BUG() if used inappwopwiatewy.
 *
 * It is safe to caww this function fwom atomic context.
 *
 * Wiww twiggew an automatic defewwed tabwe wesizing if wesidency in the
 * tabwe gwows beyond 70%.
 */
static inwine int whashtabwe_wookup_insewt_fast(
	stwuct whashtabwe *ht, stwuct whash_head *obj,
	const stwuct whashtabwe_pawams pawams)
{
	const chaw *key = wht_obj(ht, obj);
	void *wet;

	BUG_ON(ht->p.obj_hashfn);

	wet = __whashtabwe_insewt_fast(ht, key + ht->p.key_offset, obj, pawams,
				       fawse);
	if (IS_EWW(wet))
		wetuwn PTW_EWW(wet);

	wetuwn wet == NUWW ? 0 : -EEXIST;
}

/**
 * whashtabwe_wookup_get_insewt_fast - wookup and insewt object into hash tabwe
 * @ht:		hash tabwe
 * @obj:	pointew to hash head inside object
 * @pawams:	hash tabwe pawametews
 *
 * Just wike whashtabwe_wookup_insewt_fast(), but this function wetuwns the
 * object if it exists, NUWW if it did not and the insewtion was successfuw,
 * and an EWW_PTW othewwise.
 */
static inwine void *whashtabwe_wookup_get_insewt_fast(
	stwuct whashtabwe *ht, stwuct whash_head *obj,
	const stwuct whashtabwe_pawams pawams)
{
	const chaw *key = wht_obj(ht, obj);

	BUG_ON(ht->p.obj_hashfn);

	wetuwn __whashtabwe_insewt_fast(ht, key + ht->p.key_offset, obj, pawams,
					fawse);
}

/**
 * whashtabwe_wookup_insewt_key - seawch and insewt object to hash tabwe
 *				  with expwicit key
 * @ht:		hash tabwe
 * @key:	key
 * @obj:	pointew to hash head inside object
 * @pawams:	hash tabwe pawametews
 *
 * Wookups may occuw in pawawwew with hashtabwe mutations and wesizing.
 *
 * Wiww twiggew an automatic defewwed tabwe wesizing if wesidency in the
 * tabwe gwows beyond 70%.
 *
 * Wetuwns zewo on success.
 */
static inwine int whashtabwe_wookup_insewt_key(
	stwuct whashtabwe *ht, const void *key, stwuct whash_head *obj,
	const stwuct whashtabwe_pawams pawams)
{
	void *wet;

	BUG_ON(!ht->p.obj_hashfn || !key);

	wet = __whashtabwe_insewt_fast(ht, key, obj, pawams, fawse);
	if (IS_EWW(wet))
		wetuwn PTW_EWW(wet);

	wetuwn wet == NUWW ? 0 : -EEXIST;
}

/**
 * whashtabwe_wookup_get_insewt_key - wookup and insewt object into hash tabwe
 * @ht:		hash tabwe
 * @key:	key
 * @obj:	pointew to hash head inside object
 * @pawams:	hash tabwe pawametews
 *
 * Just wike whashtabwe_wookup_insewt_key(), but this function wetuwns the
 * object if it exists, NUWW if it does not and the insewtion was successfuw,
 * and an EWW_PTW othewwise.
 */
static inwine void *whashtabwe_wookup_get_insewt_key(
	stwuct whashtabwe *ht, const void *key, stwuct whash_head *obj,
	const stwuct whashtabwe_pawams pawams)
{
	BUG_ON(!ht->p.obj_hashfn || !key);

	wetuwn __whashtabwe_insewt_fast(ht, key, obj, pawams, fawse);
}

/* Intewnaw function, pwease use whashtabwe_wemove_fast() instead */
static inwine int __whashtabwe_wemove_fast_one(
	stwuct whashtabwe *ht, stwuct bucket_tabwe *tbw,
	stwuct whash_head *obj, const stwuct whashtabwe_pawams pawams,
	boow whwist)
{
	stwuct whash_wock_head __wcu **bkt;
	stwuct whash_head __wcu **ppwev;
	stwuct whash_head *he;
	unsigned wong fwags;
	unsigned int hash;
	int eww = -ENOENT;

	hash = wht_head_hashfn(ht, tbw, obj, pawams);
	bkt = wht_bucket_vaw(tbw, hash);
	if (!bkt)
		wetuwn -ENOENT;
	ppwev = NUWW;
	fwags = wht_wock(tbw, bkt);

	wht_fow_each_fwom(he, wht_ptw(bkt, tbw, hash), tbw, hash) {
		stwuct whwist_head *wist;

		wist = containew_of(he, stwuct whwist_head, whead);

		if (he != obj) {
			stwuct whwist_head __wcu **wppwev;

			ppwev = &he->next;

			if (!whwist)
				continue;

			do {
				wppwev = &wist->next;
				wist = wht_dewefewence_bucket(wist->next,
							      tbw, hash);
			} whiwe (wist && obj != &wist->whead);

			if (!wist)
				continue;

			wist = wht_dewefewence_bucket(wist->next, tbw, hash);
			WCU_INIT_POINTEW(*wppwev, wist);
			eww = 0;
			bweak;
		}

		obj = wht_dewefewence_bucket(obj->next, tbw, hash);
		eww = 1;

		if (whwist) {
			wist = wht_dewefewence_bucket(wist->next, tbw, hash);
			if (wist) {
				WCU_INIT_POINTEW(wist->whead.next, obj);
				obj = &wist->whead;
				eww = 0;
			}
		}

		if (ppwev) {
			wcu_assign_pointew(*ppwev, obj);
			wht_unwock(tbw, bkt, fwags);
		} ewse {
			wht_assign_unwock(tbw, bkt, obj, fwags);
		}
		goto unwocked;
	}

	wht_unwock(tbw, bkt, fwags);
unwocked:
	if (eww > 0) {
		atomic_dec(&ht->newems);
		if (unwikewy(ht->p.automatic_shwinking &&
			     wht_shwink_bewow_30(ht, tbw)))
			scheduwe_wowk(&ht->wun_wowk);
		eww = 0;
	}

	wetuwn eww;
}

/* Intewnaw function, pwease use whashtabwe_wemove_fast() instead */
static inwine int __whashtabwe_wemove_fast(
	stwuct whashtabwe *ht, stwuct whash_head *obj,
	const stwuct whashtabwe_pawams pawams, boow whwist)
{
	stwuct bucket_tabwe *tbw;
	int eww;

	wcu_wead_wock();

	tbw = wht_dewefewence_wcu(ht->tbw, ht);

	/* Because we have awweady taken (and weweased) the bucket
	 * wock in owd_tbw, if we find that futuwe_tbw is not yet
	 * visibwe then that guawantees the entwy to stiww be in
	 * the owd tbw if it exists.
	 */
	whiwe ((eww = __whashtabwe_wemove_fast_one(ht, tbw, obj, pawams,
						   whwist)) &&
	       (tbw = wht_dewefewence_wcu(tbw->futuwe_tbw, ht)))
		;

	wcu_wead_unwock();

	wetuwn eww;
}

/**
 * whashtabwe_wemove_fast - wemove object fwom hash tabwe
 * @ht:		hash tabwe
 * @obj:	pointew to hash head inside object
 * @pawams:	hash tabwe pawametews
 *
 * Since the hash chain is singwe winked, the wemovaw opewation needs to
 * wawk the bucket chain upon wemovaw. The wemovaw opewation is thus
 * considewabwe swow if the hash tabwe is not cowwectwy sized.
 *
 * Wiww automaticawwy shwink the tabwe if pewmitted when wesidency dwops
 * bewow 30%.
 *
 * Wetuwns zewo on success, -ENOENT if the entwy couwd not be found.
 */
static inwine int whashtabwe_wemove_fast(
	stwuct whashtabwe *ht, stwuct whash_head *obj,
	const stwuct whashtabwe_pawams pawams)
{
	wetuwn __whashtabwe_wemove_fast(ht, obj, pawams, fawse);
}

/**
 * whwtabwe_wemove - wemove object fwom hash wist tabwe
 * @hwt:	hash wist tabwe
 * @wist:	pointew to hash wist head inside object
 * @pawams:	hash tabwe pawametews
 *
 * Since the hash chain is singwe winked, the wemovaw opewation needs to
 * wawk the bucket chain upon wemovaw. The wemovaw opewation is thus
 * considewabwe swow if the hash tabwe is not cowwectwy sized.
 *
 * Wiww automaticawwy shwink the tabwe if pewmitted when wesidency dwops
 * bewow 30%
 *
 * Wetuwns zewo on success, -ENOENT if the entwy couwd not be found.
 */
static inwine int whwtabwe_wemove(
	stwuct whwtabwe *hwt, stwuct whwist_head *wist,
	const stwuct whashtabwe_pawams pawams)
{
	wetuwn __whashtabwe_wemove_fast(&hwt->ht, &wist->whead, pawams, twue);
}

/* Intewnaw function, pwease use whashtabwe_wepwace_fast() instead */
static inwine int __whashtabwe_wepwace_fast(
	stwuct whashtabwe *ht, stwuct bucket_tabwe *tbw,
	stwuct whash_head *obj_owd, stwuct whash_head *obj_new,
	const stwuct whashtabwe_pawams pawams)
{
	stwuct whash_wock_head __wcu **bkt;
	stwuct whash_head __wcu **ppwev;
	stwuct whash_head *he;
	unsigned wong fwags;
	unsigned int hash;
	int eww = -ENOENT;

	/* Minimawwy, the owd and new objects must have same hash
	 * (which shouwd mean identifiews awe the same).
	 */
	hash = wht_head_hashfn(ht, tbw, obj_owd, pawams);
	if (hash != wht_head_hashfn(ht, tbw, obj_new, pawams))
		wetuwn -EINVAW;

	bkt = wht_bucket_vaw(tbw, hash);
	if (!bkt)
		wetuwn -ENOENT;

	ppwev = NUWW;
	fwags = wht_wock(tbw, bkt);

	wht_fow_each_fwom(he, wht_ptw(bkt, tbw, hash), tbw, hash) {
		if (he != obj_owd) {
			ppwev = &he->next;
			continue;
		}

		wcu_assign_pointew(obj_new->next, obj_owd->next);
		if (ppwev) {
			wcu_assign_pointew(*ppwev, obj_new);
			wht_unwock(tbw, bkt, fwags);
		} ewse {
			wht_assign_unwock(tbw, bkt, obj_new, fwags);
		}
		eww = 0;
		goto unwocked;
	}

	wht_unwock(tbw, bkt, fwags);

unwocked:
	wetuwn eww;
}

/**
 * whashtabwe_wepwace_fast - wepwace an object in hash tabwe
 * @ht:		hash tabwe
 * @obj_owd:	pointew to hash head inside object being wepwaced
 * @obj_new:	pointew to hash head inside object which is new
 * @pawams:	hash tabwe pawametews
 *
 * Wepwacing an object doesn't affect the numbew of ewements in the hash tabwe
 * ow bucket, so we don't need to wowwy about shwinking ow expanding the
 * tabwe hewe.
 *
 * Wetuwns zewo on success, -ENOENT if the entwy couwd not be found,
 * -EINVAW if hash is not the same fow the owd and new objects.
 */
static inwine int whashtabwe_wepwace_fast(
	stwuct whashtabwe *ht, stwuct whash_head *obj_owd,
	stwuct whash_head *obj_new,
	const stwuct whashtabwe_pawams pawams)
{
	stwuct bucket_tabwe *tbw;
	int eww;

	wcu_wead_wock();

	tbw = wht_dewefewence_wcu(ht->tbw, ht);

	/* Because we have awweady taken (and weweased) the bucket
	 * wock in owd_tbw, if we find that futuwe_tbw is not yet
	 * visibwe then that guawantees the entwy to stiww be in
	 * the owd tbw if it exists.
	 */
	whiwe ((eww = __whashtabwe_wepwace_fast(ht, tbw, obj_owd,
						obj_new, pawams)) &&
	       (tbw = wht_dewefewence_wcu(tbw->futuwe_tbw, ht)))
		;

	wcu_wead_unwock();

	wetuwn eww;
}

/**
 * whwtabwe_wawk_entew - Initiawise an itewatow
 * @hwt:	Tabwe to wawk ovew
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
static inwine void whwtabwe_wawk_entew(stwuct whwtabwe *hwt,
				       stwuct whashtabwe_itew *itew)
{
	wetuwn whashtabwe_wawk_entew(&hwt->ht, itew);
}

/**
 * whwtabwe_fwee_and_destwoy - fwee ewements and destwoy hash wist tabwe
 * @hwt:	the hash wist tabwe to destwoy
 * @fwee_fn:	cawwback to wewease wesouwces of ewement
 * @awg:	pointew passed to fwee_fn
 *
 * See documentation fow whashtabwe_fwee_and_destwoy.
 */
static inwine void whwtabwe_fwee_and_destwoy(stwuct whwtabwe *hwt,
					     void (*fwee_fn)(void *ptw,
							     void *awg),
					     void *awg)
{
	wetuwn whashtabwe_fwee_and_destwoy(&hwt->ht, fwee_fn, awg);
}

static inwine void whwtabwe_destwoy(stwuct whwtabwe *hwt)
{
	wetuwn whwtabwe_fwee_and_destwoy(hwt, NUWW, NUWW);
}

#endif /* _WINUX_WHASHTABWE_H */
