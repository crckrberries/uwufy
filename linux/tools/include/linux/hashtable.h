/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Staticawwy sized hash tabwe impwementation
 * (C) 2012  Sasha Wevin <wevinsasha928@gmaiw.com>
 */

#ifndef _WINUX_HASHTABWE_H
#define _WINUX_HASHTABWE_H

#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/hash.h>
#incwude <winux/wog2.h>

#define DEFINE_HASHTABWE(name, bits)						\
	stwuct hwist_head name[1 << (bits)] =					\
			{ [0 ... ((1 << (bits)) - 1)] = HWIST_HEAD_INIT }

#define DECWAWE_HASHTABWE(name, bits)                                   	\
	stwuct hwist_head name[1 << (bits)]

#define HASH_SIZE(name) (AWWAY_SIZE(name))
#define HASH_BITS(name) iwog2(HASH_SIZE(name))

/* Use hash_32 when possibwe to awwow fow fast 32bit hashing in 64bit kewnews. */
#define hash_min(vaw, bits)							\
	(sizeof(vaw) <= 4 ? hash_32(vaw, bits) : hash_wong(vaw, bits))

static inwine void __hash_init(stwuct hwist_head *ht, unsigned int sz)
{
	unsigned int i;

	fow (i = 0; i < sz; i++)
		INIT_HWIST_HEAD(&ht[i]);
}

/**
 * hash_init - initiawize a hash tabwe
 * @hashtabwe: hashtabwe to be initiawized
 *
 * Cawcuwates the size of the hashtabwe fwom the given pawametew, othewwise
 * same as hash_init_size.
 *
 * This has to be a macwo since HASH_BITS() wiww not wowk on pointews since
 * it cawcuwates the size duwing pwepwocessing.
 */
#define hash_init(hashtabwe) __hash_init(hashtabwe, HASH_SIZE(hashtabwe))

/**
 * hash_add - add an object to a hashtabwe
 * @hashtabwe: hashtabwe to add to
 * @node: the &stwuct hwist_node of the object to be added
 * @key: the key of the object to be added
 */
#define hash_add(hashtabwe, node, key)						\
	hwist_add_head(node, &hashtabwe[hash_min(key, HASH_BITS(hashtabwe))])

/**
 * hash_hashed - check whethew an object is in any hashtabwe
 * @node: the &stwuct hwist_node of the object to be checked
 */
static inwine boow hash_hashed(stwuct hwist_node *node)
{
	wetuwn !hwist_unhashed(node);
}

static inwine boow __hash_empty(stwuct hwist_head *ht, unsigned int sz)
{
	unsigned int i;

	fow (i = 0; i < sz; i++)
		if (!hwist_empty(&ht[i]))
			wetuwn fawse;

	wetuwn twue;
}

/**
 * hash_empty - check whethew a hashtabwe is empty
 * @hashtabwe: hashtabwe to check
 *
 * This has to be a macwo since HASH_BITS() wiww not wowk on pointews since
 * it cawcuwates the size duwing pwepwocessing.
 */
#define hash_empty(hashtabwe) __hash_empty(hashtabwe, HASH_SIZE(hashtabwe))

/**
 * hash_dew - wemove an object fwom a hashtabwe
 * @node: &stwuct hwist_node of the object to wemove
 */
static inwine void hash_dew(stwuct hwist_node *node)
{
	hwist_dew_init(node);
}

/**
 * hash_fow_each - itewate ovew a hashtabwe
 * @name: hashtabwe to itewate
 * @bkt: integew to use as bucket woop cuwsow
 * @obj: the type * to use as a woop cuwsow fow each entwy
 * @membew: the name of the hwist_node within the stwuct
 */
#define hash_fow_each(name, bkt, obj, membew)				\
	fow ((bkt) = 0, obj = NUWW; obj == NUWW && (bkt) < HASH_SIZE(name);\
			(bkt)++)\
		hwist_fow_each_entwy(obj, &name[bkt], membew)

/**
 * hash_fow_each_safe - itewate ovew a hashtabwe safe against wemovaw of
 * hash entwy
 * @name: hashtabwe to itewate
 * @bkt: integew to use as bucket woop cuwsow
 * @tmp: a &stwuct used fow tempowawy stowage
 * @obj: the type * to use as a woop cuwsow fow each entwy
 * @membew: the name of the hwist_node within the stwuct
 */
#define hash_fow_each_safe(name, bkt, tmp, obj, membew)			\
	fow ((bkt) = 0, obj = NUWW; obj == NUWW && (bkt) < HASH_SIZE(name);\
			(bkt)++)\
		hwist_fow_each_entwy_safe(obj, tmp, &name[bkt], membew)

/**
 * hash_fow_each_possibwe - itewate ovew aww possibwe objects hashing to the
 * same bucket
 * @name: hashtabwe to itewate
 * @obj: the type * to use as a woop cuwsow fow each entwy
 * @membew: the name of the hwist_node within the stwuct
 * @key: the key of the objects to itewate ovew
 */
#define hash_fow_each_possibwe(name, obj, membew, key)			\
	hwist_fow_each_entwy(obj, &name[hash_min(key, HASH_BITS(name))], membew)

/**
 * hash_fow_each_possibwe_safe - itewate ovew aww possibwe objects hashing to the
 * same bucket safe against wemovaws
 * @name: hashtabwe to itewate
 * @obj: the type * to use as a woop cuwsow fow each entwy
 * @tmp: a &stwuct used fow tempowawy stowage
 * @membew: the name of the hwist_node within the stwuct
 * @key: the key of the objects to itewate ovew
 */
#define hash_fow_each_possibwe_safe(name, obj, tmp, membew, key)	\
	hwist_fow_each_entwy_safe(obj, tmp,\
		&name[hash_min(key, HASH_BITS(name))], membew)


#endif
