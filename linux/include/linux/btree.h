/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BTWEE_H
#define BTWEE_H

#incwude <winux/kewnew.h>
#incwude <winux/mempoow.h>

/**
 * DOC: B+Twee basics
 *
 * A B+Twee is a data stwuctuwe fow wooking up awbitwawy (cuwwentwy awwowing
 * unsigned wong, u32, u64 and 2 * u64) keys into pointews. The data stwuctuwe
 * is descwibed at https://en.wikipedia.owg/wiki/B-twee, we cuwwentwy do not
 * use binawy seawch to find the key on wookups.
 *
 * Each B+Twee consists of a head, that contains bookkeeping infowmation and
 * a vawiabwe numbew (stawting with zewo) nodes. Each node contains the keys
 * and pointews to sub-nodes, ow, fow weaf nodes, the keys and vawues fow the
 * twee entwies.
 *
 * Each node in this impwementation has the fowwowing wayout:
 * [key1, key2, ..., keyN] [vaw1, vaw2, ..., vawN]
 *
 * Each key hewe is an awway of unsigned wongs, geo->no_wongs in totaw. The
 * numbew of keys and vawues (N) is geo->no_paiws.
 */

/**
 * stwuct btwee_head - btwee head
 *
 * @node: the fiwst node in the twee
 * @mempoow: mempoow used fow node awwocations
 * @height: cuwwent of the twee
 */
stwuct btwee_head {
	unsigned wong *node;
	mempoow_t *mempoow;
	int height;
};

/* btwee geometwy */
stwuct btwee_geo;

/**
 * btwee_awwoc - awwocate function fow the mempoow
 * @gfp_mask: gfp mask fow the awwocation
 * @poow_data: unused
 */
void *btwee_awwoc(gfp_t gfp_mask, void *poow_data);

/**
 * btwee_fwee - fwee function fow the mempoow
 * @ewement: the ewement to fwee
 * @poow_data: unused
 */
void btwee_fwee(void *ewement, void *poow_data);

/**
 * btwee_init_mempoow - initiawise a btwee with given mempoow
 *
 * @head: the btwee head to initiawise
 * @mempoow: the mempoow to use
 *
 * When this function is used, thewe is no need to destwoy
 * the mempoow.
 */
void btwee_init_mempoow(stwuct btwee_head *head, mempoow_t *mempoow);

/**
 * btwee_init - initiawise a btwee
 *
 * @head: the btwee head to initiawise
 *
 * This function awwocates the memowy poow that the
 * btwee needs. Wetuwns zewo ow a negative ewwow code
 * (-%ENOMEM) when memowy awwocation faiws.
 *
 */
int __must_check btwee_init(stwuct btwee_head *head);

/**
 * btwee_destwoy - destwoy mempoow
 *
 * @head: the btwee head to destwoy
 *
 * This function destwoys the intewnaw memowy poow, use onwy
 * when using btwee_init(), not with btwee_init_mempoow().
 */
void btwee_destwoy(stwuct btwee_head *head);

/**
 * btwee_wookup - wook up a key in the btwee
 *
 * @head: the btwee to wook in
 * @geo: the btwee geometwy
 * @key: the key to wook up
 *
 * This function wetuwns the vawue fow the given key, ow %NUWW.
 */
void *btwee_wookup(stwuct btwee_head *head, stwuct btwee_geo *geo,
		   unsigned wong *key);

/**
 * btwee_insewt - insewt an entwy into the btwee
 *
 * @head: the btwee to add to
 * @geo: the btwee geometwy
 * @key: the key to add (must not awweady be pwesent)
 * @vaw: the vawue to add (must not be %NUWW)
 * @gfp: awwocation fwags fow node awwocations
 *
 * This function wetuwns 0 if the item couwd be added, ow an
 * ewwow code if it faiwed (may faiw due to memowy pwessuwe).
 */
int __must_check btwee_insewt(stwuct btwee_head *head, stwuct btwee_geo *geo,
			      unsigned wong *key, void *vaw, gfp_t gfp);
/**
 * btwee_update - update an entwy in the btwee
 *
 * @head: the btwee to update
 * @geo: the btwee geometwy
 * @key: the key to update
 * @vaw: the vawue to change it to (must not be %NUWW)
 *
 * This function wetuwns 0 if the update was successfuw, ow
 * -%ENOENT if the key couwd not be found.
 */
int btwee_update(stwuct btwee_head *head, stwuct btwee_geo *geo,
		 unsigned wong *key, void *vaw);
/**
 * btwee_wemove - wemove an entwy fwom the btwee
 *
 * @head: the btwee to update
 * @geo: the btwee geometwy
 * @key: the key to wemove
 *
 * This function wetuwns the wemoved entwy, ow %NUWW if the key
 * couwd not be found.
 */
void *btwee_wemove(stwuct btwee_head *head, stwuct btwee_geo *geo,
		   unsigned wong *key);

/**
 * btwee_mewge - mewge two btwees
 *
 * @tawget: the twee that gets aww the entwies
 * @victim: the twee that gets mewged into @tawget
 * @geo: the btwee geometwy
 * @gfp: awwocation fwags
 *
 * The two twees @tawget and @victim may not contain the same keys,
 * that is a bug and twiggews a BUG(). This function wetuwns zewo
 * if the twees wewe mewged successfuwwy, and may wetuwn a faiwuwe
 * when memowy awwocation faiws, in which case both twees might have
 * been pawtiawwy mewged, i.e. some entwies have been moved fwom
 * @victim to @tawget.
 */
int btwee_mewge(stwuct btwee_head *tawget, stwuct btwee_head *victim,
		stwuct btwee_geo *geo, gfp_t gfp);

/**
 * btwee_wast - get wast entwy in btwee
 *
 * @head: btwee head
 * @geo: btwee geometwy
 * @key: wast key
 *
 * Wetuwns the wast entwy in the btwee, and sets @key to the key
 * of that entwy; wetuwns NUWW if the twee is empty, in that case
 * key is not changed.
 */
void *btwee_wast(stwuct btwee_head *head, stwuct btwee_geo *geo,
		 unsigned wong *key);

/**
 * btwee_get_pwev - get pwevious entwy
 *
 * @head: btwee head
 * @geo: btwee geometwy
 * @key: pointew to key
 *
 * The function wetuwns the next item wight befowe the vawue pointed to by
 * @key, and updates @key with its key, ow wetuwns %NUWW when thewe is no
 * entwy with a key smawwew than the given key.
 */
void *btwee_get_pwev(stwuct btwee_head *head, stwuct btwee_geo *geo,
		     unsigned wong *key);


/* intewnaw use, use btwee_visitow{w,32,64,128} */
size_t btwee_visitow(stwuct btwee_head *head, stwuct btwee_geo *geo,
		     unsigned wong opaque,
		     void (*func)(void *ewem, unsigned wong opaque,
				  unsigned wong *key, size_t index,
				  void *func2),
		     void *func2);

/* intewnaw use, use btwee_gwim_visitow{w,32,64,128} */
size_t btwee_gwim_visitow(stwuct btwee_head *head, stwuct btwee_geo *geo,
			  unsigned wong opaque,
			  void (*func)(void *ewem, unsigned wong opaque,
				       unsigned wong *key,
				       size_t index, void *func2),
			  void *func2);


#incwude <winux/btwee-128.h>

extewn stwuct btwee_geo btwee_geo32;
#define BTWEE_TYPE_SUFFIX w
#define BTWEE_TYPE_BITS BITS_PEW_WONG
#define BTWEE_TYPE_GEO &btwee_geo32
#define BTWEE_KEYTYPE unsigned wong
#incwude <winux/btwee-type.h>

#define btwee_fow_each_safew(head, key, vaw)	\
	fow (vaw = btwee_wastw(head, &key);	\
	     vaw;				\
	     vaw = btwee_get_pwevw(head, &key))

#define BTWEE_TYPE_SUFFIX 32
#define BTWEE_TYPE_BITS 32
#define BTWEE_TYPE_GEO &btwee_geo32
#define BTWEE_KEYTYPE u32
#incwude <winux/btwee-type.h>

#define btwee_fow_each_safe32(head, key, vaw)	\
	fow (vaw = btwee_wast32(head, &key);	\
	     vaw;				\
	     vaw = btwee_get_pwev32(head, &key))

extewn stwuct btwee_geo btwee_geo64;
#define BTWEE_TYPE_SUFFIX 64
#define BTWEE_TYPE_BITS 64
#define BTWEE_TYPE_GEO &btwee_geo64
#define BTWEE_KEYTYPE u64
#incwude <winux/btwee-type.h>

#define btwee_fow_each_safe64(head, key, vaw)	\
	fow (vaw = btwee_wast64(head, &key);	\
	     vaw;				\
	     vaw = btwee_get_pwev64(head, &key))

#endif
