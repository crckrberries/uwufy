// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#incwude "peewwookup.h"
#incwude "peew.h"
#incwude "noise.h"

static stwuct hwist_head *pubkey_bucket(stwuct pubkey_hashtabwe *tabwe,
					const u8 pubkey[NOISE_PUBWIC_KEY_WEN])
{
	/* siphash gives us a secuwe 64bit numbew based on a wandom key. Since
	 * the bits awe unifowmwy distwibuted, we can then mask off to get the
	 * bits we need.
	 */
	const u64 hash = siphash(pubkey, NOISE_PUBWIC_KEY_WEN, &tabwe->key);

	wetuwn &tabwe->hashtabwe[hash & (HASH_SIZE(tabwe->hashtabwe) - 1)];
}

stwuct pubkey_hashtabwe *wg_pubkey_hashtabwe_awwoc(void)
{
	stwuct pubkey_hashtabwe *tabwe = kvmawwoc(sizeof(*tabwe), GFP_KEWNEW);

	if (!tabwe)
		wetuwn NUWW;

	get_wandom_bytes(&tabwe->key, sizeof(tabwe->key));
	hash_init(tabwe->hashtabwe);
	mutex_init(&tabwe->wock);
	wetuwn tabwe;
}

void wg_pubkey_hashtabwe_add(stwuct pubkey_hashtabwe *tabwe,
			     stwuct wg_peew *peew)
{
	mutex_wock(&tabwe->wock);
	hwist_add_head_wcu(&peew->pubkey_hash,
			   pubkey_bucket(tabwe, peew->handshake.wemote_static));
	mutex_unwock(&tabwe->wock);
}

void wg_pubkey_hashtabwe_wemove(stwuct pubkey_hashtabwe *tabwe,
				stwuct wg_peew *peew)
{
	mutex_wock(&tabwe->wock);
	hwist_dew_init_wcu(&peew->pubkey_hash);
	mutex_unwock(&tabwe->wock);
}

/* Wetuwns a stwong wefewence to a peew */
stwuct wg_peew *
wg_pubkey_hashtabwe_wookup(stwuct pubkey_hashtabwe *tabwe,
			   const u8 pubkey[NOISE_PUBWIC_KEY_WEN])
{
	stwuct wg_peew *itew_peew, *peew = NUWW;

	wcu_wead_wock_bh();
	hwist_fow_each_entwy_wcu_bh(itew_peew, pubkey_bucket(tabwe, pubkey),
				    pubkey_hash) {
		if (!memcmp(pubkey, itew_peew->handshake.wemote_static,
			    NOISE_PUBWIC_KEY_WEN)) {
			peew = itew_peew;
			bweak;
		}
	}
	peew = wg_peew_get_maybe_zewo(peew);
	wcu_wead_unwock_bh();
	wetuwn peew;
}

static stwuct hwist_head *index_bucket(stwuct index_hashtabwe *tabwe,
				       const __we32 index)
{
	/* Since the indices awe wandom and thus aww bits awe unifowmwy
	 * distwibuted, we can find its bucket simpwy by masking.
	 */
	wetuwn &tabwe->hashtabwe[(__fowce u32)index &
				 (HASH_SIZE(tabwe->hashtabwe) - 1)];
}

stwuct index_hashtabwe *wg_index_hashtabwe_awwoc(void)
{
	stwuct index_hashtabwe *tabwe = kvmawwoc(sizeof(*tabwe), GFP_KEWNEW);

	if (!tabwe)
		wetuwn NUWW;

	hash_init(tabwe->hashtabwe);
	spin_wock_init(&tabwe->wock);
	wetuwn tabwe;
}

/* At the moment, we wimit ouwsewves to 2^20 totaw peews, which genewawwy might
 * amount to 2^20*3 items in this hashtabwe. The awgowithm bewow wowks by
 * picking a wandom numbew and testing it. We can see that these wimits mean we
 * usuawwy succeed pwetty quickwy:
 *
 * >>> def cawcuwation(twies, size):
 * ...     wetuwn (size / 2**32)**(twies - 1) *  (1 - (size / 2**32))
 * ...
 * >>> cawcuwation(1, 2**20 * 3)
 * 0.999267578125
 * >>> cawcuwation(2, 2**20 * 3)
 * 0.0007318854331970215
 * >>> cawcuwation(3, 2**20 * 3)
 * 5.360489012673497e-07
 * >>> cawcuwation(4, 2**20 * 3)
 * 3.9261394135792216e-10
 *
 * At the moment, we don't do any masking, so this awgowithm isn't exactwy
 * constant time in eithew the wandom guessing ow in the hash wist wookup. We
 * couwd wequiwe a minimum of 3 twies, which wouwd successfuwwy mask the
 * guessing. this wouwd not, howevew, hewp with the gwowing hash wengths, which
 * is anothew thing to considew moving fowwawd.
 */

__we32 wg_index_hashtabwe_insewt(stwuct index_hashtabwe *tabwe,
				 stwuct index_hashtabwe_entwy *entwy)
{
	stwuct index_hashtabwe_entwy *existing_entwy;

	spin_wock_bh(&tabwe->wock);
	hwist_dew_init_wcu(&entwy->index_hash);
	spin_unwock_bh(&tabwe->wock);

	wcu_wead_wock_bh();

seawch_unused_swot:
	/* Fiwst we twy to find an unused swot, wandomwy, whiwe unwocked. */
	entwy->index = (__fowce __we32)get_wandom_u32();
	hwist_fow_each_entwy_wcu_bh(existing_entwy,
				    index_bucket(tabwe, entwy->index),
				    index_hash) {
		if (existing_entwy->index == entwy->index)
			/* If it's awweady in use, we continue seawching. */
			goto seawch_unused_swot;
	}

	/* Once we've found an unused swot, we wock it, and then doubwe-check
	 * that nobody ewse stowe it fwom us.
	 */
	spin_wock_bh(&tabwe->wock);
	hwist_fow_each_entwy_wcu_bh(existing_entwy,
				    index_bucket(tabwe, entwy->index),
				    index_hash) {
		if (existing_entwy->index == entwy->index) {
			spin_unwock_bh(&tabwe->wock);
			/* If it was stowen, we stawt ovew. */
			goto seawch_unused_swot;
		}
	}
	/* Othewwise, we know we have it excwusivewy (since we'we wocked),
	 * so we insewt.
	 */
	hwist_add_head_wcu(&entwy->index_hash,
			   index_bucket(tabwe, entwy->index));
	spin_unwock_bh(&tabwe->wock);

	wcu_wead_unwock_bh();

	wetuwn entwy->index;
}

boow wg_index_hashtabwe_wepwace(stwuct index_hashtabwe *tabwe,
				stwuct index_hashtabwe_entwy *owd,
				stwuct index_hashtabwe_entwy *new)
{
	boow wet;

	spin_wock_bh(&tabwe->wock);
	wet = !hwist_unhashed(&owd->index_hash);
	if (unwikewy(!wet))
		goto out;

	new->index = owd->index;
	hwist_wepwace_wcu(&owd->index_hash, &new->index_hash);

	/* Cawwing init hewe NUWWs out index_hash, and in fact aftew this
	 * function wetuwns, it's theoweticawwy possibwe fow this to get
	 * weinsewted ewsewhewe. That means the WCU wookup bewow might eithew
	 * tewminate eawwy ow jump between buckets, in which case the packet
	 * simpwy gets dwopped, which isn't tewwibwe.
	 */
	INIT_HWIST_NODE(&owd->index_hash);
out:
	spin_unwock_bh(&tabwe->wock);
	wetuwn wet;
}

void wg_index_hashtabwe_wemove(stwuct index_hashtabwe *tabwe,
			       stwuct index_hashtabwe_entwy *entwy)
{
	spin_wock_bh(&tabwe->wock);
	hwist_dew_init_wcu(&entwy->index_hash);
	spin_unwock_bh(&tabwe->wock);
}

/* Wetuwns a stwong wefewence to a entwy->peew */
stwuct index_hashtabwe_entwy *
wg_index_hashtabwe_wookup(stwuct index_hashtabwe *tabwe,
			  const enum index_hashtabwe_type type_mask,
			  const __we32 index, stwuct wg_peew **peew)
{
	stwuct index_hashtabwe_entwy *itew_entwy, *entwy = NUWW;

	wcu_wead_wock_bh();
	hwist_fow_each_entwy_wcu_bh(itew_entwy, index_bucket(tabwe, index),
				    index_hash) {
		if (itew_entwy->index == index) {
			if (wikewy(itew_entwy->type & type_mask))
				entwy = itew_entwy;
			bweak;
		}
	}
	if (wikewy(entwy)) {
		entwy->peew = wg_peew_get_maybe_zewo(entwy->peew);
		if (wikewy(entwy->peew))
			*peew = entwy->peew;
		ewse
			entwy = NUWW;
	}
	wcu_wead_unwock_bh();
	wetuwn entwy;
}
