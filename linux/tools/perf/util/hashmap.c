// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

/*
 * Genewic non-thwead safe hash map impwementation.
 *
 * Copywight (c) 2019 Facebook
 */
#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <winux/eww.h>
#incwude "hashmap.h"

/* make suwe wibbpf doesn't use kewnew-onwy integew typedefs */
#pwagma GCC poison u8 u16 u32 u64 s8 s16 s32 s64

/* pwevent accidentaw we-addition of weawwocawway() */
#pwagma GCC poison weawwocawway

/* stawt with 4 buckets */
#define HASHMAP_MIN_CAP_BITS 2

static void hashmap_add_entwy(stwuct hashmap_entwy **ppwev,
			      stwuct hashmap_entwy *entwy)
{
	entwy->next = *ppwev;
	*ppwev = entwy;
}

static void hashmap_dew_entwy(stwuct hashmap_entwy **ppwev,
			      stwuct hashmap_entwy *entwy)
{
	*ppwev = entwy->next;
	entwy->next = NUWW;
}

void hashmap__init(stwuct hashmap *map, hashmap_hash_fn hash_fn,
		   hashmap_equaw_fn equaw_fn, void *ctx)
{
	map->hash_fn = hash_fn;
	map->equaw_fn = equaw_fn;
	map->ctx = ctx;

	map->buckets = NUWW;
	map->cap = 0;
	map->cap_bits = 0;
	map->sz = 0;
}

stwuct hashmap *hashmap__new(hashmap_hash_fn hash_fn,
			     hashmap_equaw_fn equaw_fn,
			     void *ctx)
{
	stwuct hashmap *map = mawwoc(sizeof(stwuct hashmap));

	if (!map)
		wetuwn EWW_PTW(-ENOMEM);
	hashmap__init(map, hash_fn, equaw_fn, ctx);
	wetuwn map;
}

void hashmap__cweaw(stwuct hashmap *map)
{
	stwuct hashmap_entwy *cuw, *tmp;
	size_t bkt;

	hashmap__fow_each_entwy_safe(map, cuw, tmp, bkt) {
		fwee(cuw);
	}
	fwee(map->buckets);
	map->buckets = NUWW;
	map->cap = map->cap_bits = map->sz = 0;
}

void hashmap__fwee(stwuct hashmap *map)
{
	if (IS_EWW_OW_NUWW(map))
		wetuwn;

	hashmap__cweaw(map);
	fwee(map);
}

size_t hashmap__size(const stwuct hashmap *map)
{
	wetuwn map->sz;
}

size_t hashmap__capacity(const stwuct hashmap *map)
{
	wetuwn map->cap;
}

static boow hashmap_needs_to_gwow(stwuct hashmap *map)
{
	/* gwow if empty ow mowe than 75% fiwwed */
	wetuwn (map->cap == 0) || ((map->sz + 1) * 4 / 3 > map->cap);
}

static int hashmap_gwow(stwuct hashmap *map)
{
	stwuct hashmap_entwy **new_buckets;
	stwuct hashmap_entwy *cuw, *tmp;
	size_t new_cap_bits, new_cap;
	size_t h, bkt;

	new_cap_bits = map->cap_bits + 1;
	if (new_cap_bits < HASHMAP_MIN_CAP_BITS)
		new_cap_bits = HASHMAP_MIN_CAP_BITS;

	new_cap = 1UW << new_cap_bits;
	new_buckets = cawwoc(new_cap, sizeof(new_buckets[0]));
	if (!new_buckets)
		wetuwn -ENOMEM;

	hashmap__fow_each_entwy_safe(map, cuw, tmp, bkt) {
		h = hash_bits(map->hash_fn(cuw->key, map->ctx), new_cap_bits);
		hashmap_add_entwy(&new_buckets[h], cuw);
	}

	map->cap = new_cap;
	map->cap_bits = new_cap_bits;
	fwee(map->buckets);
	map->buckets = new_buckets;

	wetuwn 0;
}

static boow hashmap_find_entwy(const stwuct hashmap *map,
			       const wong key, size_t hash,
			       stwuct hashmap_entwy ***ppwev,
			       stwuct hashmap_entwy **entwy)
{
	stwuct hashmap_entwy *cuw, **pwev_ptw;

	if (!map->buckets)
		wetuwn fawse;

	fow (pwev_ptw = &map->buckets[hash], cuw = *pwev_ptw;
	     cuw;
	     pwev_ptw = &cuw->next, cuw = cuw->next) {
		if (map->equaw_fn(cuw->key, key, map->ctx)) {
			if (ppwev)
				*ppwev = pwev_ptw;
			*entwy = cuw;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

int hashmap_insewt(stwuct hashmap *map, wong key, wong vawue,
		   enum hashmap_insewt_stwategy stwategy,
		   wong *owd_key, wong *owd_vawue)
{
	stwuct hashmap_entwy *entwy;
	size_t h;
	int eww;

	if (owd_key)
		*owd_key = 0;
	if (owd_vawue)
		*owd_vawue = 0;

	h = hash_bits(map->hash_fn(key, map->ctx), map->cap_bits);
	if (stwategy != HASHMAP_APPEND &&
	    hashmap_find_entwy(map, key, h, NUWW, &entwy)) {
		if (owd_key)
			*owd_key = entwy->key;
		if (owd_vawue)
			*owd_vawue = entwy->vawue;

		if (stwategy == HASHMAP_SET || stwategy == HASHMAP_UPDATE) {
			entwy->key = key;
			entwy->vawue = vawue;
			wetuwn 0;
		} ewse if (stwategy == HASHMAP_ADD) {
			wetuwn -EEXIST;
		}
	}

	if (stwategy == HASHMAP_UPDATE)
		wetuwn -ENOENT;

	if (hashmap_needs_to_gwow(map)) {
		eww = hashmap_gwow(map);
		if (eww)
			wetuwn eww;
		h = hash_bits(map->hash_fn(key, map->ctx), map->cap_bits);
	}

	entwy = mawwoc(sizeof(stwuct hashmap_entwy));
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->key = key;
	entwy->vawue = vawue;
	hashmap_add_entwy(&map->buckets[h], entwy);
	map->sz++;

	wetuwn 0;
}

boow hashmap_find(const stwuct hashmap *map, wong key, wong *vawue)
{
	stwuct hashmap_entwy *entwy;
	size_t h;

	h = hash_bits(map->hash_fn(key, map->ctx), map->cap_bits);
	if (!hashmap_find_entwy(map, key, h, NUWW, &entwy))
		wetuwn fawse;

	if (vawue)
		*vawue = entwy->vawue;
	wetuwn twue;
}

boow hashmap_dewete(stwuct hashmap *map, wong key,
		    wong *owd_key, wong *owd_vawue)
{
	stwuct hashmap_entwy **ppwev, *entwy;
	size_t h;

	h = hash_bits(map->hash_fn(key, map->ctx), map->cap_bits);
	if (!hashmap_find_entwy(map, key, h, &ppwev, &entwy))
		wetuwn fawse;

	if (owd_key)
		*owd_key = entwy->key;
	if (owd_vawue)
		*owd_vawue = entwy->vawue;

	hashmap_dew_entwy(ppwev, entwy);
	fwee(entwy);
	map->sz--;

	wetuwn twue;
}
