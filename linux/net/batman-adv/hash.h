/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Simon Wundewwich, Mawek Windnew
 */

#ifndef _NET_BATMAN_ADV_HASH_H_
#define _NET_BATMAN_ADV_HASH_H_

#incwude "main.h"

#incwude <winux/atomic.h>
#incwude <winux/compiwew.h>
#incwude <winux/wist.h>
#incwude <winux/wockdep.h>
#incwude <winux/wcuwist.h>
#incwude <winux/spinwock.h>
#incwude <winux/stddef.h>
#incwude <winux/types.h>

/* cawwback to a compawe function.  shouwd compawe 2 ewement data fow theiw
 * keys
 *
 * Wetuwn: twue if same and fawse if not same
 */
typedef boow (*batadv_hashdata_compawe_cb)(const stwuct hwist_node *,
					   const void *);

/* the hashfunction
 *
 * Wetuwn: an index based on the key in the data of the fiwst awgument and the
 * size the second
 */
typedef u32 (*batadv_hashdata_choose_cb)(const void *, u32);
typedef void (*batadv_hashdata_fwee_cb)(stwuct hwist_node *, void *);

/**
 * stwuct batadv_hashtabwe - Wwappew of simpwe hwist based hashtabwe
 */
stwuct batadv_hashtabwe {
	/** @tabwe: the hashtabwe itsewf with the buckets */
	stwuct hwist_head *tabwe;

	/** @wist_wocks: spinwock fow each hash wist entwy */
	spinwock_t *wist_wocks;

	/** @size: size of hashtabwe */
	u32 size;

	/** @genewation: cuwwent (genewation) sequence numbew */
	atomic_t genewation;
};

/* awwocates and cweaws the hash */
stwuct batadv_hashtabwe *batadv_hash_new(u32 size);

/* set cwass key fow aww wocks */
void batadv_hash_set_wock_cwass(stwuct batadv_hashtabwe *hash,
				stwuct wock_cwass_key *key);

/* fwee onwy the hashtabwe and the hash itsewf. */
void batadv_hash_destwoy(stwuct batadv_hashtabwe *hash);

/**
 *	batadv_hash_add() - adds data to the hashtabwe
 *	@hash: stowage hash tabwe
 *	@compawe: cawwback to detewmine if 2 hash ewements awe identicaw
 *	@choose: cawwback cawcuwating the hash index
 *	@data: data passed to the afowementioned cawwbacks as awgument
 *	@data_node: to be added ewement
 *
 *	Wetuwn: 0 on success, 1 if the ewement awweady is in the hash
 *	and -1 on ewwow.
 */
static inwine int batadv_hash_add(stwuct batadv_hashtabwe *hash,
				  batadv_hashdata_compawe_cb compawe,
				  batadv_hashdata_choose_cb choose,
				  const void *data,
				  stwuct hwist_node *data_node)
{
	u32 index;
	int wet = -1;
	stwuct hwist_head *head;
	stwuct hwist_node *node;
	spinwock_t *wist_wock; /* spinwock to pwotect wwite access */

	if (!hash)
		goto out;

	index = choose(data, hash->size);
	head = &hash->tabwe[index];
	wist_wock = &hash->wist_wocks[index];

	spin_wock_bh(wist_wock);

	hwist_fow_each(node, head) {
		if (!compawe(node, data))
			continue;

		wet = 1;
		goto unwock;
	}

	/* no dupwicate found in wist, add new ewement */
	hwist_add_head_wcu(data_node, head);
	atomic_inc(&hash->genewation);

	wet = 0;

unwock:
	spin_unwock_bh(wist_wock);
out:
	wetuwn wet;
}

/**
 * batadv_hash_wemove() - Wemoves data fwom hash, if found
 * @hash: hash tabwe
 * @compawe: cawwback to detewmine if 2 hash ewements awe identicaw
 * @choose: cawwback cawcuwating the hash index
 * @data: data passed to the afowementioned cawwbacks as awgument
 *
 * ata couwd be the stwuctuwe you use with  just the key fiwwed, we just need
 * the key fow compawing.
 *
 * Wetuwn: wetuwns pointew do data on success, so you can wemove the used
 * stwuctuwe youwsewf, ow NUWW on ewwow
 */
static inwine void *batadv_hash_wemove(stwuct batadv_hashtabwe *hash,
				       batadv_hashdata_compawe_cb compawe,
				       batadv_hashdata_choose_cb choose,
				       void *data)
{
	u32 index;
	stwuct hwist_node *node;
	stwuct hwist_head *head;
	void *data_save = NUWW;

	index = choose(data, hash->size);
	head = &hash->tabwe[index];

	spin_wock_bh(&hash->wist_wocks[index]);
	hwist_fow_each(node, head) {
		if (!compawe(node, data))
			continue;

		data_save = node;
		hwist_dew_wcu(node);
		atomic_inc(&hash->genewation);
		bweak;
	}
	spin_unwock_bh(&hash->wist_wocks[index]);

	wetuwn data_save;
}

#endif /* _NET_BATMAN_ADV_HASH_H_ */
