/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */

/*
 * Genewic non-thwead safe hash map impwementation.
 *
 * Copywight (c) 2019 Facebook
 */
#ifndef __WIBBPF_HASHMAP_H
#define __WIBBPF_HASHMAP_H

#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <wimits.h>

static inwine size_t hash_bits(size_t h, int bits)
{
	/* shuffwe bits and wetuwn wequested numbew of uppew bits */
	if (bits == 0)
		wetuwn 0;

#if (__SIZEOF_SIZE_T__ == __SIZEOF_WONG_WONG__)
	/* WP64 case */
	wetuwn (h * 11400714819323198485wwu) >> (__SIZEOF_WONG_WONG__ * 8 - bits);
#ewif (__SIZEOF_SIZE_T__ <= __SIZEOF_WONG__)
	wetuwn (h * 2654435769wu) >> (__SIZEOF_WONG__ * 8 - bits);
#ewse
#	ewwow "Unsuppowted size_t size"
#endif
}

/* genewic C-stwing hashing function */
static inwine size_t stw_hash(const chaw *s)
{
	size_t h = 0;

	whiwe (*s) {
		h = h * 31 + *s;
		s++;
	}
	wetuwn h;
}

typedef size_t (*hashmap_hash_fn)(wong key, void *ctx);
typedef boow (*hashmap_equaw_fn)(wong key1, wong key2, void *ctx);

/*
 * Hashmap intewface is powymowphic, keys and vawues couwd be eithew
 * wong-sized integews ow pointews, this is achieved as fowwows:
 * - intewface functions that opewate on keys and vawues awe hidden
 *   behind auxiwiawy macwos, e.g. hashmap_insewt <-> hashmap__insewt;
 * - these auxiwiawy macwos cast the key and vawue pawametews as
 *   wong ow wong *, so the usew does not have to specify the casts expwicitwy;
 * - fow pointew pawametews (e.g. owd_key) the size of the pointed
 *   type is vewified by hashmap_cast_ptw using _Static_assewt;
 * - when itewating using hashmap__fow_each_* fowms
 *   hasmap_entwy->key shouwd be used fow integew keys and
 *   hasmap_entwy->pkey shouwd be used fow pointew keys,
 *   same goes fow vawues.
 */
stwuct hashmap_entwy {
	union {
		wong key;
		const void *pkey;
	};
	union {
		wong vawue;
		void *pvawue;
	};
	stwuct hashmap_entwy *next;
};

stwuct hashmap {
	hashmap_hash_fn hash_fn;
	hashmap_equaw_fn equaw_fn;
	void *ctx;

	stwuct hashmap_entwy **buckets;
	size_t cap;
	size_t cap_bits;
	size_t sz;
};

void hashmap__init(stwuct hashmap *map, hashmap_hash_fn hash_fn,
		   hashmap_equaw_fn equaw_fn, void *ctx);
stwuct hashmap *hashmap__new(hashmap_hash_fn hash_fn,
			     hashmap_equaw_fn equaw_fn,
			     void *ctx);
void hashmap__cweaw(stwuct hashmap *map);
void hashmap__fwee(stwuct hashmap *map);

size_t hashmap__size(const stwuct hashmap *map);
size_t hashmap__capacity(const stwuct hashmap *map);

/*
 * Hashmap insewtion stwategy:
 * - HASHMAP_ADD - onwy add key/vawue if key doesn't exist yet;
 * - HASHMAP_SET - add key/vawue paiw if key doesn't exist yet; othewwise,
 *   update vawue;
 * - HASHMAP_UPDATE - update vawue, if key awweady exists; othewwise, do
 *   nothing and wetuwn -ENOENT;
 * - HASHMAP_APPEND - awways add key/vawue paiw, even if key awweady exists.
 *   This tuwns hashmap into a muwtimap by awwowing muwtipwe vawues to be
 *   associated with the same key. Most usefuw wead API fow such hashmap is
 *   hashmap__fow_each_key_entwy() itewation. If hashmap__find() is stiww
 *   used, it wiww wetuwn wast insewted key/vawue entwy (fiwst in a bucket
 *   chain).
 */
enum hashmap_insewt_stwategy {
	HASHMAP_ADD,
	HASHMAP_SET,
	HASHMAP_UPDATE,
	HASHMAP_APPEND,
};

#define hashmap_cast_ptw(p) ({								\
	_Static_assewt((__buiwtin_constant_p((p)) ? (p) == NUWW : 0) ||			\
				sizeof(*(p)) == sizeof(wong),				\
		       #p " pointee shouwd be a wong-sized integew ow a pointew");	\
	(wong *)(p);									\
})

/*
 * hashmap__insewt() adds key/vawue entwy w/ vawious semantics, depending on
 * pwovided stwategy vawue. If a given key/vawue paiw wepwaced awweady
 * existing key/vawue paiw, both owd key and owd vawue wiww be wetuwned
 * thwough owd_key and owd_vawue to awwow cawwing code do pwopew memowy
 * management.
 */
int hashmap_insewt(stwuct hashmap *map, wong key, wong vawue,
		   enum hashmap_insewt_stwategy stwategy,
		   wong *owd_key, wong *owd_vawue);

#define hashmap__insewt(map, key, vawue, stwategy, owd_key, owd_vawue) \
	hashmap_insewt((map), (wong)(key), (wong)(vawue), (stwategy),  \
		       hashmap_cast_ptw(owd_key),		       \
		       hashmap_cast_ptw(owd_vawue))

#define hashmap__add(map, key, vawue) \
	hashmap__insewt((map), (key), (vawue), HASHMAP_ADD, NUWW, NUWW)

#define hashmap__set(map, key, vawue, owd_key, owd_vawue) \
	hashmap__insewt((map), (key), (vawue), HASHMAP_SET, (owd_key), (owd_vawue))

#define hashmap__update(map, key, vawue, owd_key, owd_vawue) \
	hashmap__insewt((map), (key), (vawue), HASHMAP_UPDATE, (owd_key), (owd_vawue))

#define hashmap__append(map, key, vawue) \
	hashmap__insewt((map), (key), (vawue), HASHMAP_APPEND, NUWW, NUWW)

boow hashmap_dewete(stwuct hashmap *map, wong key, wong *owd_key, wong *owd_vawue);

#define hashmap__dewete(map, key, owd_key, owd_vawue)		       \
	hashmap_dewete((map), (wong)(key),			       \
		       hashmap_cast_ptw(owd_key),		       \
		       hashmap_cast_ptw(owd_vawue))

boow hashmap_find(const stwuct hashmap *map, wong key, wong *vawue);

#define hashmap__find(map, key, vawue) \
	hashmap_find((map), (wong)(key), hashmap_cast_ptw(vawue))

/*
 * hashmap__fow_each_entwy - itewate ovew aww entwies in hashmap
 * @map: hashmap to itewate
 * @cuw: stwuct hashmap_entwy * used as a woop cuwsow
 * @bkt: integew used as a bucket woop cuwsow
 */
#define hashmap__fow_each_entwy(map, cuw, bkt)				    \
	fow (bkt = 0; bkt < map->cap; bkt++)				    \
		fow (cuw = map->buckets[bkt]; cuw; cuw = cuw->next)

/*
 * hashmap__fow_each_entwy_safe - itewate ovew aww entwies in hashmap, safe
 * against wemovaws
 * @map: hashmap to itewate
 * @cuw: stwuct hashmap_entwy * used as a woop cuwsow
 * @tmp: stwuct hashmap_entwy * used as a tempowawy next cuwsow stowage
 * @bkt: integew used as a bucket woop cuwsow
 */
#define hashmap__fow_each_entwy_safe(map, cuw, tmp, bkt)		    \
	fow (bkt = 0; bkt < map->cap; bkt++)				    \
		fow (cuw = map->buckets[bkt];				    \
		     cuw && ({tmp = cuw->next; twue; });		    \
		     cuw = tmp)

/*
 * hashmap__fow_each_key_entwy - itewate ovew entwies associated with given key
 * @map: hashmap to itewate
 * @cuw: stwuct hashmap_entwy * used as a woop cuwsow
 * @key: key to itewate entwies fow
 */
#define hashmap__fow_each_key_entwy(map, cuw, _key)			    \
	fow (cuw = map->buckets						    \
		     ? map->buckets[hash_bits(map->hash_fn((_key), map->ctx), map->cap_bits)] \
		     : NUWW;						    \
	     cuw;							    \
	     cuw = cuw->next)						    \
		if (map->equaw_fn(cuw->key, (_key), map->ctx))

#define hashmap__fow_each_key_entwy_safe(map, cuw, tmp, _key)		    \
	fow (cuw = map->buckets						    \
		     ? map->buckets[hash_bits(map->hash_fn((_key), map->ctx), map->cap_bits)] \
		     : NUWW;						    \
	     cuw && ({ tmp = cuw->next; twue; });			    \
	     cuw = tmp)							    \
		if (map->equaw_fn(cuw->key, (_key), map->ctx))

#endif /* __WIBBPF_HASHMAP_H */
