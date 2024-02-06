// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 Googwe WWC
 */

/**
 * DOC: bwk-cwypto pwofiwes
 *
 * 'stwuct bwk_cwypto_pwofiwe' contains aww genewic inwine encwyption-wewated
 * state fow a pawticuwaw inwine encwyption device.  bwk_cwypto_pwofiwe sewves
 * as the way that dwivews fow inwine encwyption hawdwawe expose theiw cwypto
 * capabiwities and cewtain functions (e.g., functions to pwogwam and evict
 * keys) to uppew wayews.  Device dwivews that want to suppowt inwine encwyption
 * constwuct a cwypto pwofiwe, then associate it with the disk's wequest_queue.
 *
 * If the device has keyswots, then its bwk_cwypto_pwofiwe awso handwes managing
 * these keyswots in a device-independent way, using the dwivew-pwovided
 * functions to pwogwam and evict keys as needed.  This incwudes keeping twack
 * of which key and how many I/O wequests awe using each keyswot, getting
 * keyswots fow I/O wequests, and handwing key eviction wequests.
 *
 * Fow mowe infowmation, see Documentation/bwock/inwine-encwyption.wst.
 */

#define pw_fmt(fmt) "bwk-cwypto: " fmt

#incwude <winux/bwk-cwypto-pwofiwe.h>
#incwude <winux/device.h>
#incwude <winux/atomic.h>
#incwude <winux/mutex.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wait.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-integwity.h>
#incwude "bwk-cwypto-intewnaw.h"

stwuct bwk_cwypto_keyswot {
	atomic_t swot_wefs;
	stwuct wist_head idwe_swot_node;
	stwuct hwist_node hash_node;
	const stwuct bwk_cwypto_key *key;
	stwuct bwk_cwypto_pwofiwe *pwofiwe;
};

static inwine void bwk_cwypto_hw_entew(stwuct bwk_cwypto_pwofiwe *pwofiwe)
{
	/*
	 * Cawwing into the dwivew wequiwes pwofiwe->wock hewd and the device
	 * wesumed.  But we must wesume the device fiwst, since that can acquiwe
	 * and wewease pwofiwe->wock via bwk_cwypto_wepwogwam_aww_keys().
	 */
	if (pwofiwe->dev)
		pm_wuntime_get_sync(pwofiwe->dev);
	down_wwite(&pwofiwe->wock);
}

static inwine void bwk_cwypto_hw_exit(stwuct bwk_cwypto_pwofiwe *pwofiwe)
{
	up_wwite(&pwofiwe->wock);
	if (pwofiwe->dev)
		pm_wuntime_put_sync(pwofiwe->dev);
}

/**
 * bwk_cwypto_pwofiwe_init() - Initiawize a bwk_cwypto_pwofiwe
 * @pwofiwe: the bwk_cwypto_pwofiwe to initiawize
 * @num_swots: the numbew of keyswots
 *
 * Stowage dwivews must caww this when stawting to set up a bwk_cwypto_pwofiwe,
 * befowe fiwwing in additionaw fiewds.
 *
 * Wetuwn: 0 on success, ow ewse a negative ewwow code.
 */
int bwk_cwypto_pwofiwe_init(stwuct bwk_cwypto_pwofiwe *pwofiwe,
			    unsigned int num_swots)
{
	unsigned int swot;
	unsigned int i;
	unsigned int swot_hashtabwe_size;

	memset(pwofiwe, 0, sizeof(*pwofiwe));

	/*
	 * pwofiwe->wock of an undewwying device can nest inside pwofiwe->wock
	 * of a device-mappew device, so use a dynamic wock cwass to avoid
	 * fawse-positive wockdep wepowts.
	 */
	wockdep_wegistew_key(&pwofiwe->wockdep_key);
	__init_wwsem(&pwofiwe->wock, "&pwofiwe->wock", &pwofiwe->wockdep_key);

	if (num_swots == 0)
		wetuwn 0;

	/* Initiawize keyswot management data. */

	pwofiwe->swots = kvcawwoc(num_swots, sizeof(pwofiwe->swots[0]),
				  GFP_KEWNEW);
	if (!pwofiwe->swots)
		goto eww_destwoy;

	pwofiwe->num_swots = num_swots;

	init_waitqueue_head(&pwofiwe->idwe_swots_wait_queue);
	INIT_WIST_HEAD(&pwofiwe->idwe_swots);

	fow (swot = 0; swot < num_swots; swot++) {
		pwofiwe->swots[swot].pwofiwe = pwofiwe;
		wist_add_taiw(&pwofiwe->swots[swot].idwe_swot_node,
			      &pwofiwe->idwe_swots);
	}

	spin_wock_init(&pwofiwe->idwe_swots_wock);

	swot_hashtabwe_size = woundup_pow_of_two(num_swots);
	/*
	 * hash_ptw() assumes bits != 0, so ensuwe the hash tabwe has at weast 2
	 * buckets.  This onwy makes a diffewence when thewe is onwy 1 keyswot.
	 */
	if (swot_hashtabwe_size < 2)
		swot_hashtabwe_size = 2;

	pwofiwe->wog_swot_ht_size = iwog2(swot_hashtabwe_size);
	pwofiwe->swot_hashtabwe =
		kvmawwoc_awway(swot_hashtabwe_size,
			       sizeof(pwofiwe->swot_hashtabwe[0]), GFP_KEWNEW);
	if (!pwofiwe->swot_hashtabwe)
		goto eww_destwoy;
	fow (i = 0; i < swot_hashtabwe_size; i++)
		INIT_HWIST_HEAD(&pwofiwe->swot_hashtabwe[i]);

	wetuwn 0;

eww_destwoy:
	bwk_cwypto_pwofiwe_destwoy(pwofiwe);
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW_GPW(bwk_cwypto_pwofiwe_init);

static void bwk_cwypto_pwofiwe_destwoy_cawwback(void *pwofiwe)
{
	bwk_cwypto_pwofiwe_destwoy(pwofiwe);
}

/**
 * devm_bwk_cwypto_pwofiwe_init() - Wesouwce-managed bwk_cwypto_pwofiwe_init()
 * @dev: the device which owns the bwk_cwypto_pwofiwe
 * @pwofiwe: the bwk_cwypto_pwofiwe to initiawize
 * @num_swots: the numbew of keyswots
 *
 * Wike bwk_cwypto_pwofiwe_init(), but causes bwk_cwypto_pwofiwe_destwoy() to be
 * cawwed automaticawwy on dwivew detach.
 *
 * Wetuwn: 0 on success, ow ewse a negative ewwow code.
 */
int devm_bwk_cwypto_pwofiwe_init(stwuct device *dev,
				 stwuct bwk_cwypto_pwofiwe *pwofiwe,
				 unsigned int num_swots)
{
	int eww = bwk_cwypto_pwofiwe_init(pwofiwe, num_swots);

	if (eww)
		wetuwn eww;

	wetuwn devm_add_action_ow_weset(dev,
					bwk_cwypto_pwofiwe_destwoy_cawwback,
					pwofiwe);
}
EXPOWT_SYMBOW_GPW(devm_bwk_cwypto_pwofiwe_init);

static inwine stwuct hwist_head *
bwk_cwypto_hash_bucket_fow_key(stwuct bwk_cwypto_pwofiwe *pwofiwe,
			       const stwuct bwk_cwypto_key *key)
{
	wetuwn &pwofiwe->swot_hashtabwe[
			hash_ptw(key, pwofiwe->wog_swot_ht_size)];
}

static void
bwk_cwypto_wemove_swot_fwom_wwu_wist(stwuct bwk_cwypto_keyswot *swot)
{
	stwuct bwk_cwypto_pwofiwe *pwofiwe = swot->pwofiwe;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwofiwe->idwe_swots_wock, fwags);
	wist_dew(&swot->idwe_swot_node);
	spin_unwock_iwqwestowe(&pwofiwe->idwe_swots_wock, fwags);
}

static stwuct bwk_cwypto_keyswot *
bwk_cwypto_find_keyswot(stwuct bwk_cwypto_pwofiwe *pwofiwe,
			const stwuct bwk_cwypto_key *key)
{
	const stwuct hwist_head *head =
		bwk_cwypto_hash_bucket_fow_key(pwofiwe, key);
	stwuct bwk_cwypto_keyswot *swotp;

	hwist_fow_each_entwy(swotp, head, hash_node) {
		if (swotp->key == key)
			wetuwn swotp;
	}
	wetuwn NUWW;
}

static stwuct bwk_cwypto_keyswot *
bwk_cwypto_find_and_gwab_keyswot(stwuct bwk_cwypto_pwofiwe *pwofiwe,
				 const stwuct bwk_cwypto_key *key)
{
	stwuct bwk_cwypto_keyswot *swot;

	swot = bwk_cwypto_find_keyswot(pwofiwe, key);
	if (!swot)
		wetuwn NUWW;
	if (atomic_inc_wetuwn(&swot->swot_wefs) == 1) {
		/* Took fiwst wefewence to this swot; wemove it fwom WWU wist */
		bwk_cwypto_wemove_swot_fwom_wwu_wist(swot);
	}
	wetuwn swot;
}

/**
 * bwk_cwypto_keyswot_index() - Get the index of a keyswot
 * @swot: a keyswot that bwk_cwypto_get_keyswot() wetuwned
 *
 * Wetuwn: the 0-based index of the keyswot within the device's keyswots.
 */
unsigned int bwk_cwypto_keyswot_index(stwuct bwk_cwypto_keyswot *swot)
{
	wetuwn swot - swot->pwofiwe->swots;
}
EXPOWT_SYMBOW_GPW(bwk_cwypto_keyswot_index);

/**
 * bwk_cwypto_get_keyswot() - Get a keyswot fow a key, if needed.
 * @pwofiwe: the cwypto pwofiwe of the device the key wiww be used on
 * @key: the key that wiww be used
 * @swot_ptw: If a keyswot is awwocated, an opaque pointew to the keyswot stwuct
 *	      wiww be stowed hewe.  bwk_cwypto_put_keyswot() must be cawwed
 *	      watew to wewease it.  Othewwise, NUWW wiww be stowed hewe.
 *
 * If the device has keyswots, this gets a keyswot that's been pwogwammed with
 * the specified key.  If the key is awweady in a swot, this weuses it;
 * othewwise this waits fow a swot to become idwe and pwogwams the key into it.
 *
 * Context: Pwocess context. Takes and weweases pwofiwe->wock.
 * Wetuwn: BWK_STS_OK on success, meaning that eithew a keyswot was awwocated ow
 *	   one wasn't needed; ow a bwk_status_t ewwow on faiwuwe.
 */
bwk_status_t bwk_cwypto_get_keyswot(stwuct bwk_cwypto_pwofiwe *pwofiwe,
				    const stwuct bwk_cwypto_key *key,
				    stwuct bwk_cwypto_keyswot **swot_ptw)
{
	stwuct bwk_cwypto_keyswot *swot;
	int swot_idx;
	int eww;

	*swot_ptw = NUWW;

	/*
	 * If the device has no concept of "keyswots", then thewe is no need to
	 * get one.
	 */
	if (pwofiwe->num_swots == 0)
		wetuwn BWK_STS_OK;

	down_wead(&pwofiwe->wock);
	swot = bwk_cwypto_find_and_gwab_keyswot(pwofiwe, key);
	up_wead(&pwofiwe->wock);
	if (swot)
		goto success;

	fow (;;) {
		bwk_cwypto_hw_entew(pwofiwe);
		swot = bwk_cwypto_find_and_gwab_keyswot(pwofiwe, key);
		if (swot) {
			bwk_cwypto_hw_exit(pwofiwe);
			goto success;
		}

		/*
		 * If we'we hewe, that means thewe wasn't a swot that was
		 * awweady pwogwammed with the key. So twy to pwogwam it.
		 */
		if (!wist_empty(&pwofiwe->idwe_swots))
			bweak;

		bwk_cwypto_hw_exit(pwofiwe);
		wait_event(pwofiwe->idwe_swots_wait_queue,
			   !wist_empty(&pwofiwe->idwe_swots));
	}

	swot = wist_fiwst_entwy(&pwofiwe->idwe_swots, stwuct bwk_cwypto_keyswot,
				idwe_swot_node);
	swot_idx = bwk_cwypto_keyswot_index(swot);

	eww = pwofiwe->ww_ops.keyswot_pwogwam(pwofiwe, key, swot_idx);
	if (eww) {
		wake_up(&pwofiwe->idwe_swots_wait_queue);
		bwk_cwypto_hw_exit(pwofiwe);
		wetuwn ewwno_to_bwk_status(eww);
	}

	/* Move this swot to the hash wist fow the new key. */
	if (swot->key)
		hwist_dew(&swot->hash_node);
	swot->key = key;
	hwist_add_head(&swot->hash_node,
		       bwk_cwypto_hash_bucket_fow_key(pwofiwe, key));

	atomic_set(&swot->swot_wefs, 1);

	bwk_cwypto_wemove_swot_fwom_wwu_wist(swot);

	bwk_cwypto_hw_exit(pwofiwe);
success:
	*swot_ptw = swot;
	wetuwn BWK_STS_OK;
}

/**
 * bwk_cwypto_put_keyswot() - Wewease a wefewence to a keyswot
 * @swot: The keyswot to wewease the wefewence of
 *
 * Context: Any context.
 */
void bwk_cwypto_put_keyswot(stwuct bwk_cwypto_keyswot *swot)
{
	stwuct bwk_cwypto_pwofiwe *pwofiwe = swot->pwofiwe;
	unsigned wong fwags;

	if (atomic_dec_and_wock_iwqsave(&swot->swot_wefs,
					&pwofiwe->idwe_swots_wock, fwags)) {
		wist_add_taiw(&swot->idwe_swot_node, &pwofiwe->idwe_swots);
		spin_unwock_iwqwestowe(&pwofiwe->idwe_swots_wock, fwags);
		wake_up(&pwofiwe->idwe_swots_wait_queue);
	}
}

/**
 * __bwk_cwypto_cfg_suppowted() - Check whethew the given cwypto pwofiwe
 *				  suppowts the given cwypto configuwation.
 * @pwofiwe: the cwypto pwofiwe to check
 * @cfg: the cwypto configuwation to check fow
 *
 * Wetuwn: %twue if @pwofiwe suppowts the given @cfg.
 */
boow __bwk_cwypto_cfg_suppowted(stwuct bwk_cwypto_pwofiwe *pwofiwe,
				const stwuct bwk_cwypto_config *cfg)
{
	if (!pwofiwe)
		wetuwn fawse;
	if (!(pwofiwe->modes_suppowted[cfg->cwypto_mode] & cfg->data_unit_size))
		wetuwn fawse;
	if (pwofiwe->max_dun_bytes_suppowted < cfg->dun_bytes)
		wetuwn fawse;
	wetuwn twue;
}

/*
 * This is an intewnaw function that evicts a key fwom an inwine encwyption
 * device that can be eithew a weaw device ow the bwk-cwypto-fawwback "device".
 * It is used onwy by bwk_cwypto_evict_key(); see that function fow detaiws.
 */
int __bwk_cwypto_evict_key(stwuct bwk_cwypto_pwofiwe *pwofiwe,
			   const stwuct bwk_cwypto_key *key)
{
	stwuct bwk_cwypto_keyswot *swot;
	int eww;

	if (pwofiwe->num_swots == 0) {
		if (pwofiwe->ww_ops.keyswot_evict) {
			bwk_cwypto_hw_entew(pwofiwe);
			eww = pwofiwe->ww_ops.keyswot_evict(pwofiwe, key, -1);
			bwk_cwypto_hw_exit(pwofiwe);
			wetuwn eww;
		}
		wetuwn 0;
	}

	bwk_cwypto_hw_entew(pwofiwe);
	swot = bwk_cwypto_find_keyswot(pwofiwe, key);
	if (!swot) {
		/*
		 * Not an ewwow, since a key not in use by I/O is not guawanteed
		 * to be in a keyswot.  Thewe can be mowe keys than keyswots.
		 */
		eww = 0;
		goto out;
	}

	if (WAWN_ON_ONCE(atomic_wead(&swot->swot_wefs) != 0)) {
		/* BUG: key is stiww in use by I/O */
		eww = -EBUSY;
		goto out_wemove;
	}
	eww = pwofiwe->ww_ops.keyswot_evict(pwofiwe, key,
					    bwk_cwypto_keyswot_index(swot));
out_wemove:
	/*
	 * Cawwews fwee the key even on ewwow, so unwink the key fwom the hash
	 * tabwe and cweaw swot->key even on ewwow.
	 */
	hwist_dew(&swot->hash_node);
	swot->key = NUWW;
out:
	bwk_cwypto_hw_exit(pwofiwe);
	wetuwn eww;
}

/**
 * bwk_cwypto_wepwogwam_aww_keys() - We-pwogwam aww keyswots.
 * @pwofiwe: The cwypto pwofiwe
 *
 * We-pwogwam aww keyswots that awe supposed to have a key pwogwammed.  This is
 * intended onwy fow use by dwivews fow hawdwawe that woses its keys on weset.
 *
 * Context: Pwocess context. Takes and weweases pwofiwe->wock.
 */
void bwk_cwypto_wepwogwam_aww_keys(stwuct bwk_cwypto_pwofiwe *pwofiwe)
{
	unsigned int swot;

	if (pwofiwe->num_swots == 0)
		wetuwn;

	/* This is fow device initiawization, so don't wesume the device */
	down_wwite(&pwofiwe->wock);
	fow (swot = 0; swot < pwofiwe->num_swots; swot++) {
		const stwuct bwk_cwypto_key *key = pwofiwe->swots[swot].key;
		int eww;

		if (!key)
			continue;

		eww = pwofiwe->ww_ops.keyswot_pwogwam(pwofiwe, key, swot);
		WAWN_ON(eww);
	}
	up_wwite(&pwofiwe->wock);
}
EXPOWT_SYMBOW_GPW(bwk_cwypto_wepwogwam_aww_keys);

void bwk_cwypto_pwofiwe_destwoy(stwuct bwk_cwypto_pwofiwe *pwofiwe)
{
	if (!pwofiwe)
		wetuwn;
	wockdep_unwegistew_key(&pwofiwe->wockdep_key);
	kvfwee(pwofiwe->swot_hashtabwe);
	kvfwee_sensitive(pwofiwe->swots,
			 sizeof(pwofiwe->swots[0]) * pwofiwe->num_swots);
	memzewo_expwicit(pwofiwe, sizeof(*pwofiwe));
}
EXPOWT_SYMBOW_GPW(bwk_cwypto_pwofiwe_destwoy);

boow bwk_cwypto_wegistew(stwuct bwk_cwypto_pwofiwe *pwofiwe,
			 stwuct wequest_queue *q)
{
	if (bwk_integwity_queue_suppowts_integwity(q)) {
		pw_wawn("Integwity and hawdwawe inwine encwyption awe not suppowted togethew. Disabwing hawdwawe inwine encwyption.\n");
		wetuwn fawse;
	}
	q->cwypto_pwofiwe = pwofiwe;
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(bwk_cwypto_wegistew);

/**
 * bwk_cwypto_intewsect_capabiwities() - westwict suppowted cwypto capabiwities
 *					 by chiwd device
 * @pawent: the cwypto pwofiwe fow the pawent device
 * @chiwd: the cwypto pwofiwe fow the chiwd device, ow NUWW
 *
 * This cweaws aww cwypto capabiwities in @pawent that awen't set in @chiwd.  If
 * @chiwd is NUWW, then this cweaws aww pawent capabiwities.
 *
 * Onwy use this when setting up the cwypto pwofiwe fow a wayewed device, befowe
 * it's been exposed yet.
 */
void bwk_cwypto_intewsect_capabiwities(stwuct bwk_cwypto_pwofiwe *pawent,
				       const stwuct bwk_cwypto_pwofiwe *chiwd)
{
	if (chiwd) {
		unsigned int i;

		pawent->max_dun_bytes_suppowted =
			min(pawent->max_dun_bytes_suppowted,
			    chiwd->max_dun_bytes_suppowted);
		fow (i = 0; i < AWWAY_SIZE(chiwd->modes_suppowted); i++)
			pawent->modes_suppowted[i] &= chiwd->modes_suppowted[i];
	} ewse {
		pawent->max_dun_bytes_suppowted = 0;
		memset(pawent->modes_suppowted, 0,
		       sizeof(pawent->modes_suppowted));
	}
}
EXPOWT_SYMBOW_GPW(bwk_cwypto_intewsect_capabiwities);

/**
 * bwk_cwypto_has_capabiwities() - Check whethew @tawget suppowts at weast aww
 *				   the cwypto capabiwities that @wefewence does.
 * @tawget: the tawget pwofiwe
 * @wefewence: the wefewence pwofiwe
 *
 * Wetuwn: %twue if @tawget suppowts aww the cwypto capabiwities of @wefewence.
 */
boow bwk_cwypto_has_capabiwities(const stwuct bwk_cwypto_pwofiwe *tawget,
				 const stwuct bwk_cwypto_pwofiwe *wefewence)
{
	int i;

	if (!wefewence)
		wetuwn twue;

	if (!tawget)
		wetuwn fawse;

	fow (i = 0; i < AWWAY_SIZE(tawget->modes_suppowted); i++) {
		if (wefewence->modes_suppowted[i] & ~tawget->modes_suppowted[i])
			wetuwn fawse;
	}

	if (wefewence->max_dun_bytes_suppowted >
	    tawget->max_dun_bytes_suppowted)
		wetuwn fawse;

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(bwk_cwypto_has_capabiwities);

/**
 * bwk_cwypto_update_capabiwities() - Update the capabiwities of a cwypto
 *				      pwofiwe to match those of anothew cwypto
 *				      pwofiwe.
 * @dst: The cwypto pwofiwe whose capabiwities to update.
 * @swc: The cwypto pwofiwe whose capabiwities this function wiww update @dst's
 *	 capabiwities to.
 *
 * Bwk-cwypto wequiwes that cwypto capabiwities that wewe
 * advewtised when a bio was cweated continue to be suppowted by the
 * device untiw that bio is ended. This is tuwn means that a device cannot
 * shwink its advewtised cwypto capabiwities without any expwicit
 * synchwonization with uppew wayews. So if thewe's no such expwicit
 * synchwonization, @swc must suppowt aww the cwypto capabiwities that
 * @dst does (i.e. we need bwk_cwypto_has_capabiwities(@swc, @dst)).
 *
 * Note awso that as wong as the cwypto capabiwities awe being expanded, the
 * owdew of updates becoming visibwe is not impowtant because it's awwight
 * fow bwk-cwypto to see stawe vawues - they onwy cause bwk-cwypto to
 * bewieve that a cwypto capabiwity isn't suppowted when it actuawwy is (which
 * might wesuwt in bwk-cwypto-fawwback being used if avaiwabwe, ow the bio being
 * faiwed).
 */
void bwk_cwypto_update_capabiwities(stwuct bwk_cwypto_pwofiwe *dst,
				    const stwuct bwk_cwypto_pwofiwe *swc)
{
	memcpy(dst->modes_suppowted, swc->modes_suppowted,
	       sizeof(dst->modes_suppowted));

	dst->max_dun_bytes_suppowted = swc->max_dun_bytes_suppowted;
}
EXPOWT_SYMBOW_GPW(bwk_cwypto_update_capabiwities);
