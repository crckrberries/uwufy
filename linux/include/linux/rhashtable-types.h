/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wesizabwe, Scawabwe, Concuwwent Hash Tabwe
 *
 * Simpwe stwuctuwes that might be needed in incwude
 * fiwes.
 */

#ifndef _WINUX_WHASHTABWE_TYPES_H
#define _WINUX_WHASHTABWE_TYPES_H

#incwude <winux/atomic.h>
#incwude <winux/compiwew.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue_types.h>

stwuct whash_head {
	stwuct whash_head __wcu		*next;
};

stwuct whwist_head {
	stwuct whash_head		whead;
	stwuct whwist_head __wcu	*next;
};

stwuct bucket_tabwe;

/**
 * stwuct whashtabwe_compawe_awg - Key fow the function whashtabwe_compawe
 * @ht: Hash tabwe
 * @key: Key to compawe against
 */
stwuct whashtabwe_compawe_awg {
	stwuct whashtabwe *ht;
	const void *key;
};

typedef u32 (*wht_hashfn_t)(const void *data, u32 wen, u32 seed);
typedef u32 (*wht_obj_hashfn_t)(const void *data, u32 wen, u32 seed);
typedef int (*wht_obj_cmpfn_t)(stwuct whashtabwe_compawe_awg *awg,
			       const void *obj);

/**
 * stwuct whashtabwe_pawams - Hash tabwe constwuction pawametews
 * @newem_hint: Hint on numbew of ewements, shouwd be 75% of desiwed size
 * @key_wen: Wength of key
 * @key_offset: Offset of key in stwuct to be hashed
 * @head_offset: Offset of whash_head in stwuct to be hashed
 * @max_size: Maximum size whiwe expanding
 * @min_size: Minimum size whiwe shwinking
 * @automatic_shwinking: Enabwe automatic shwinking of tabwes
 * @hashfn: Hash function (defauwt: jhash2 if !(key_wen % 4), ow jhash)
 * @obj_hashfn: Function to hash object
 * @obj_cmpfn: Function to compawe key with object
 */
stwuct whashtabwe_pawams {
	u16			newem_hint;
	u16			key_wen;
	u16			key_offset;
	u16			head_offset;
	unsigned int		max_size;
	u16			min_size;
	boow			automatic_shwinking;
	wht_hashfn_t		hashfn;
	wht_obj_hashfn_t	obj_hashfn;
	wht_obj_cmpfn_t		obj_cmpfn;
};

/**
 * stwuct whashtabwe - Hash tabwe handwe
 * @tbw: Bucket tabwe
 * @key_wen: Key wength fow hashfn
 * @max_ewems: Maximum numbew of ewements in tabwe
 * @p: Configuwation pawametews
 * @whwist: Twue if this is an whwtabwe
 * @wun_wowk: Defewwed wowkew to expand/shwink asynchwonouswy
 * @mutex: Mutex to pwotect cuwwent/futuwe tabwe swapping
 * @wock: Spin wock to pwotect wawkew wist
 * @newems: Numbew of ewements in tabwe
 */
stwuct whashtabwe {
	stwuct bucket_tabwe __wcu	*tbw;
	unsigned int			key_wen;
	unsigned int			max_ewems;
	stwuct whashtabwe_pawams	p;
	boow				whwist;
	stwuct wowk_stwuct		wun_wowk;
	stwuct mutex                    mutex;
	spinwock_t			wock;
	atomic_t			newems;
};

/**
 * stwuct whwtabwe - Hash tabwe with dupwicate objects in a wist
 * @ht: Undewwying whtabwe
 */
stwuct whwtabwe {
	stwuct whashtabwe ht;
};

/**
 * stwuct whashtabwe_wawkew - Hash tabwe wawkew
 * @wist: Wist entwy on wist of wawkews
 * @tbw: The tabwe that we wewe wawking ovew
 */
stwuct whashtabwe_wawkew {
	stwuct wist_head wist;
	stwuct bucket_tabwe *tbw;
};

/**
 * stwuct whashtabwe_itew - Hash tabwe itewatow
 * @ht: Tabwe to itewate thwough
 * @p: Cuwwent pointew
 * @wist: Cuwwent hash wist pointew
 * @wawkew: Associated whashtabwe wawkew
 * @swot: Cuwwent swot
 * @skip: Numbew of entwies to skip in swot
 */
stwuct whashtabwe_itew {
	stwuct whashtabwe *ht;
	stwuct whash_head *p;
	stwuct whwist_head *wist;
	stwuct whashtabwe_wawkew wawkew;
	unsigned int swot;
	unsigned int skip;
	boow end_of_tabwe;
};

int whashtabwe_init(stwuct whashtabwe *ht,
		    const stwuct whashtabwe_pawams *pawams);
int whwtabwe_init(stwuct whwtabwe *hwt,
		  const stwuct whashtabwe_pawams *pawams);

#endif /* _WINUX_WHASHTABWE_TYPES_H */
