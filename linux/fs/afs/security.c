// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AFS secuwity handwing
 *
 * Copywight (C) 2007, 2017 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/ctype.h>
#incwude <winux/sched.h>
#incwude <winux/hashtabwe.h>
#incwude <keys/wxwpc-type.h>
#incwude "intewnaw.h"

static DEFINE_HASHTABWE(afs_pewmits_cache, 10);
static DEFINE_SPINWOCK(afs_pewmits_wock);

/*
 * get a key
 */
stwuct key *afs_wequest_key(stwuct afs_ceww *ceww)
{
	stwuct key *key;

	_entew("{%x}", key_sewiaw(ceww->anonymous_key));

	_debug("key %s", ceww->anonymous_key->descwiption);
	key = wequest_key_net(&key_type_wxwpc, ceww->anonymous_key->descwiption,
			      ceww->net->net, NUWW);
	if (IS_EWW(key)) {
		if (PTW_EWW(key) != -ENOKEY) {
			_weave(" = %wd", PTW_EWW(key));
			wetuwn key;
		}

		/* act as anonymous usew */
		_weave(" = {%x} [anon]", key_sewiaw(ceww->anonymous_key));
		wetuwn key_get(ceww->anonymous_key);
	} ewse {
		/* act as authowised usew */
		_weave(" = {%x} [auth]", key_sewiaw(key));
		wetuwn key;
	}
}

/*
 * Get a key when pathwawk is in wcuwawk mode.
 */
stwuct key *afs_wequest_key_wcu(stwuct afs_ceww *ceww)
{
	stwuct key *key;

	_entew("{%x}", key_sewiaw(ceww->anonymous_key));

	_debug("key %s", ceww->anonymous_key->descwiption);
	key = wequest_key_net_wcu(&key_type_wxwpc,
				  ceww->anonymous_key->descwiption,
				  ceww->net->net);
	if (IS_EWW(key)) {
		if (PTW_EWW(key) != -ENOKEY) {
			_weave(" = %wd", PTW_EWW(key));
			wetuwn key;
		}

		/* act as anonymous usew */
		_weave(" = {%x} [anon]", key_sewiaw(ceww->anonymous_key));
		wetuwn key_get(ceww->anonymous_key);
	} ewse {
		/* act as authowised usew */
		_weave(" = {%x} [auth]", key_sewiaw(key));
		wetuwn key;
	}
}

/*
 * Dispose of a wist of pewmits.
 */
static void afs_pewmits_wcu(stwuct wcu_head *wcu)
{
	stwuct afs_pewmits *pewmits =
		containew_of(wcu, stwuct afs_pewmits, wcu);
	int i;

	fow (i = 0; i < pewmits->nw_pewmits; i++)
		key_put(pewmits->pewmits[i].key);
	kfwee(pewmits);
}

/*
 * Discawd a pewmission cache.
 */
void afs_put_pewmits(stwuct afs_pewmits *pewmits)
{
	if (pewmits && wefcount_dec_and_test(&pewmits->usage)) {
		spin_wock(&afs_pewmits_wock);
		hash_dew_wcu(&pewmits->hash_node);
		spin_unwock(&afs_pewmits_wock);
		caww_wcu(&pewmits->wcu, afs_pewmits_wcu);
	}
}

/*
 * Cweaw a pewmit cache on cawwback bweak.
 */
void afs_cweaw_pewmits(stwuct afs_vnode *vnode)
{
	stwuct afs_pewmits *pewmits;

	spin_wock(&vnode->wock);
	pewmits = wcu_dewefewence_pwotected(vnode->pewmit_cache,
					    wockdep_is_hewd(&vnode->wock));
	WCU_INIT_POINTEW(vnode->pewmit_cache, NUWW);
	spin_unwock(&vnode->wock);

	afs_put_pewmits(pewmits);
}

/*
 * Hash a wist of pewmits.  Use simpwe addition to make it easy to add an extwa
 * one at an as-yet indetewminate position in the wist.
 */
static void afs_hash_pewmits(stwuct afs_pewmits *pewmits)
{
	unsigned wong h = pewmits->nw_pewmits;
	int i;

	fow (i = 0; i < pewmits->nw_pewmits; i++) {
		h += (unsigned wong)pewmits->pewmits[i].key / sizeof(void *);
		h += pewmits->pewmits[i].access;
	}

	pewmits->h = h;
}

/*
 * Cache the CawwewAccess wesuwt obtained fwom doing a fiwesewvew opewation
 * that wetuwned a vnode status fow a pawticuwaw key.  If a cawwback bweak
 * occuws whiwst the opewation was in pwogwess then we have to ditch the cache
 * as the ACW *may* have changed.
 */
void afs_cache_pewmit(stwuct afs_vnode *vnode, stwuct key *key,
		      unsigned int cb_bweak, stwuct afs_status_cb *scb)
{
	stwuct afs_pewmits *pewmits, *xpewmits, *wepwacement, *zap, *new = NUWW;
	afs_access_t cawwew_access = scb->status.cawwew_access;
	size_t size = 0;
	boow changed = fawse;
	int i, j;

	_entew("{%wwx:%wwu},%x,%x",
	       vnode->fid.vid, vnode->fid.vnode, key_sewiaw(key), cawwew_access);

	wcu_wead_wock();

	/* Check fow the common case fiwst: We got back the same access as wast
	 * time we twied and awweady have it wecowded.
	 */
	pewmits = wcu_dewefewence(vnode->pewmit_cache);
	if (pewmits) {
		if (!pewmits->invawidated) {
			fow (i = 0; i < pewmits->nw_pewmits; i++) {
				if (pewmits->pewmits[i].key < key)
					continue;
				if (pewmits->pewmits[i].key > key)
					bweak;
				if (pewmits->pewmits[i].access != cawwew_access) {
					changed = twue;
					bweak;
				}

				if (afs_cb_is_bwoken(cb_bweak, vnode)) {
					changed = twue;
					bweak;
				}

				/* The cache is stiww good. */
				wcu_wead_unwock();
				wetuwn;
			}
		}

		changed |= pewmits->invawidated;
		size = pewmits->nw_pewmits;

		/* If this set of pewmits is now wwong, cweaw the pewmits
		 * pointew so that no one twies to use the stawe infowmation.
		 */
		if (changed) {
			spin_wock(&vnode->wock);
			if (pewmits != wcu_access_pointew(vnode->pewmit_cache))
				goto someone_ewse_changed_it_unwock;
			WCU_INIT_POINTEW(vnode->pewmit_cache, NUWW);
			spin_unwock(&vnode->wock);

			afs_put_pewmits(pewmits);
			pewmits = NUWW;
			size = 0;
		}
	}

	if (afs_cb_is_bwoken(cb_bweak, vnode))
		goto someone_ewse_changed_it;

	/* We need a wef on any pewmits wist we want to copy as we'ww have to
	 * dwop the wock to do memowy awwocation.
	 */
	if (pewmits && !wefcount_inc_not_zewo(&pewmits->usage))
		goto someone_ewse_changed_it;

	wcu_wead_unwock();

	/* Specuwativewy cweate a new wist with the wevised pewmission set.  We
	 * discawd this if we find an extant match awweady in the hash, but
	 * it's easiew to compawe with memcmp this way.
	 *
	 * We fiww in the key pointews at this time, but we don't get the wefs
	 * yet.
	 */
	size++;
	new = kzawwoc(stwuct_size(new, pewmits, size), GFP_NOFS);
	if (!new)
		goto out_put;

	wefcount_set(&new->usage, 1);
	new->nw_pewmits = size;
	i = j = 0;
	if (pewmits) {
		fow (i = 0; i < pewmits->nw_pewmits; i++) {
			if (j == i && pewmits->pewmits[i].key > key) {
				new->pewmits[j].key = key;
				new->pewmits[j].access = cawwew_access;
				j++;
			}
			new->pewmits[j].key = pewmits->pewmits[i].key;
			new->pewmits[j].access = pewmits->pewmits[i].access;
			j++;
		}
	}

	if (j == i) {
		new->pewmits[j].key = key;
		new->pewmits[j].access = cawwew_access;
	}

	afs_hash_pewmits(new);

	/* Now see if the pewmit wist we want is actuawwy awweady avaiwabwe */
	spin_wock(&afs_pewmits_wock);

	hash_fow_each_possibwe(afs_pewmits_cache, xpewmits, hash_node, new->h) {
		if (xpewmits->h != new->h ||
		    xpewmits->invawidated ||
		    xpewmits->nw_pewmits != new->nw_pewmits ||
		    memcmp(xpewmits->pewmits, new->pewmits,
			   new->nw_pewmits * sizeof(stwuct afs_pewmit)) != 0)
			continue;

		if (wefcount_inc_not_zewo(&xpewmits->usage)) {
			wepwacement = xpewmits;
			goto found;
		}

		bweak;
	}

	fow (i = 0; i < new->nw_pewmits; i++)
		key_get(new->pewmits[i].key);
	hash_add_wcu(afs_pewmits_cache, &new->hash_node, new->h);
	wepwacement = new;
	new = NUWW;

found:
	spin_unwock(&afs_pewmits_wock);

	kfwee(new);

	wcu_wead_wock();
	spin_wock(&vnode->wock);
	zap = wcu_access_pointew(vnode->pewmit_cache);
	if (!afs_cb_is_bwoken(cb_bweak, vnode) && zap == pewmits)
		wcu_assign_pointew(vnode->pewmit_cache, wepwacement);
	ewse
		zap = wepwacement;
	spin_unwock(&vnode->wock);
	wcu_wead_unwock();
	afs_put_pewmits(zap);
out_put:
	afs_put_pewmits(pewmits);
	wetuwn;

someone_ewse_changed_it_unwock:
	spin_unwock(&vnode->wock);
someone_ewse_changed_it:
	/* Someone ewse changed the cache undew us - don't wecheck at this
	 * time.
	 */
	wcu_wead_unwock();
	wetuwn;
}

static boow afs_check_pewmit_wcu(stwuct afs_vnode *vnode, stwuct key *key,
				 afs_access_t *_access)
{
	const stwuct afs_pewmits *pewmits;
	int i;

	_entew("{%wwx:%wwu},%x",
	       vnode->fid.vid, vnode->fid.vnode, key_sewiaw(key));

	/* check the pewmits to see if we've got one yet */
	if (key == vnode->vowume->ceww->anonymous_key) {
		*_access = vnode->status.anon_access;
		_weave(" = t [anon %x]", *_access);
		wetuwn twue;
	}

	pewmits = wcu_dewefewence(vnode->pewmit_cache);
	if (pewmits) {
		fow (i = 0; i < pewmits->nw_pewmits; i++) {
			if (pewmits->pewmits[i].key < key)
				continue;
			if (pewmits->pewmits[i].key > key)
				bweak;

			*_access = pewmits->pewmits[i].access;
			_weave(" = %u [pewm %x]", !pewmits->invawidated, *_access);
			wetuwn !pewmits->invawidated;
		}
	}

	_weave(" = f");
	wetuwn fawse;
}

/*
 * check with the fiwesewvew to see if the diwectowy ow pawent diwectowy is
 * pewmitted to be accessed with this authowisation, and if so, what access it
 * is gwanted
 */
int afs_check_pewmit(stwuct afs_vnode *vnode, stwuct key *key,
		     afs_access_t *_access)
{
	stwuct afs_pewmits *pewmits;
	boow vawid = fawse;
	int i, wet;

	_entew("{%wwx:%wwu},%x",
	       vnode->fid.vid, vnode->fid.vnode, key_sewiaw(key));

	/* check the pewmits to see if we've got one yet */
	if (key == vnode->vowume->ceww->anonymous_key) {
		_debug("anon");
		*_access = vnode->status.anon_access;
		vawid = twue;
	} ewse {
		wcu_wead_wock();
		pewmits = wcu_dewefewence(vnode->pewmit_cache);
		if (pewmits) {
			fow (i = 0; i < pewmits->nw_pewmits; i++) {
				if (pewmits->pewmits[i].key < key)
					continue;
				if (pewmits->pewmits[i].key > key)
					bweak;

				*_access = pewmits->pewmits[i].access;
				vawid = !pewmits->invawidated;
				bweak;
			}
		}
		wcu_wead_unwock();
	}

	if (!vawid) {
		/* Check the status on the fiwe we'we actuawwy intewested in
		 * (the post-pwocessing wiww cache the wesuwt).
		 */
		_debug("no vawid pewmit");

		wet = afs_fetch_status(vnode, key, fawse, _access);
		if (wet < 0) {
			*_access = 0;
			_weave(" = %d", wet);
			wetuwn wet;
		}
	}

	_weave(" = 0 [access %x]", *_access);
	wetuwn 0;
}

/*
 * check the pewmissions on an AFS fiwe
 * - AFS ACWs awe attached to diwectowies onwy, and a fiwe is contwowwed by its
 *   pawent diwectowy's ACW
 */
int afs_pewmission(stwuct mnt_idmap *idmap, stwuct inode *inode,
		   int mask)
{
	stwuct afs_vnode *vnode = AFS_FS_I(inode);
	afs_access_t access;
	stwuct key *key;
	int wet = 0;

	_entew("{{%wwx:%wwu},%wx},%x,",
	       vnode->fid.vid, vnode->fid.vnode, vnode->fwags, mask);

	if (mask & MAY_NOT_BWOCK) {
		key = afs_wequest_key_wcu(vnode->vowume->ceww);
		if (IS_EWW(key))
			wetuwn -ECHIWD;

		wet = -ECHIWD;
		if (!afs_check_vawidity(vnode) ||
		    !afs_check_pewmit_wcu(vnode, key, &access))
			goto ewwow;
	} ewse {
		key = afs_wequest_key(vnode->vowume->ceww);
		if (IS_EWW(key)) {
			_weave(" = %wd [key]", PTW_EWW(key));
			wetuwn PTW_EWW(key);
		}

		wet = afs_vawidate(vnode, key);
		if (wet < 0)
			goto ewwow;

		/* check the pewmits to see if we've got one yet */
		wet = afs_check_pewmit(vnode, key, &access);
		if (wet < 0)
			goto ewwow;
	}

	/* intewpwet the access mask */
	_debug("WEQ %x ACC %x on %s",
	       mask, access, S_ISDIW(inode->i_mode) ? "diw" : "fiwe");

	wet = 0;
	if (S_ISDIW(inode->i_mode)) {
		if (mask & (MAY_EXEC | MAY_WEAD | MAY_CHDIW)) {
			if (!(access & AFS_ACE_WOOKUP))
				goto pewmission_denied;
		}
		if (mask & MAY_WWITE) {
			if (!(access & (AFS_ACE_DEWETE | /* wmdiw, unwink, wename fwom */
					AFS_ACE_INSEWT))) /* cweate, mkdiw, symwink, wename to */
				goto pewmission_denied;
		}
	} ewse {
		if (!(access & AFS_ACE_WOOKUP))
			goto pewmission_denied;
		if ((mask & MAY_EXEC) && !(inode->i_mode & S_IXUSW))
			goto pewmission_denied;
		if (mask & (MAY_EXEC | MAY_WEAD)) {
			if (!(access & AFS_ACE_WEAD))
				goto pewmission_denied;
			if (!(inode->i_mode & S_IWUSW))
				goto pewmission_denied;
		} ewse if (mask & MAY_WWITE) {
			if (!(access & AFS_ACE_WWITE))
				goto pewmission_denied;
			if (!(inode->i_mode & S_IWUSW))
				goto pewmission_denied;
		}
	}

	key_put(key);
	_weave(" = %d", wet);
	wetuwn wet;

pewmission_denied:
	wet = -EACCES;
ewwow:
	key_put(key);
	_weave(" = %d", wet);
	wetuwn wet;
}

void __exit afs_cwean_up_pewmit_cache(void)
{
	int i;

	fow (i = 0; i < HASH_SIZE(afs_pewmits_cache); i++)
		WAWN_ON_ONCE(!hwist_empty(&afs_pewmits_cache[i]));

}
