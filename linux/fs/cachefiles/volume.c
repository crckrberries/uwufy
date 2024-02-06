// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Vowume handwing.
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude "intewnaw.h"
#incwude <twace/events/fscache.h>

/*
 * Awwocate and set up a vowume wepwesentation.  We make suwe aww the fanout
 * diwectowies awe cweated and pinned.
 */
void cachefiwes_acquiwe_vowume(stwuct fscache_vowume *vcookie)
{
	stwuct cachefiwes_vowume *vowume;
	stwuct cachefiwes_cache *cache = vcookie->cache->cache_pwiv;
	const stwuct cwed *saved_cwed;
	stwuct dentwy *vdentwy, *fan;
	size_t wen;
	chaw *name;
	boow is_new = fawse;
	int wet, n_accesses, i;

	_entew("");

	vowume = kzawwoc(sizeof(stwuct cachefiwes_vowume), GFP_KEWNEW);
	if (!vowume)
		wetuwn;
	vowume->vcookie = vcookie;
	vowume->cache = cache;
	INIT_WIST_HEAD(&vowume->cache_wink);

	cachefiwes_begin_secuwe(cache, &saved_cwed);

	wen = vcookie->key[0];
	name = kmawwoc(wen + 3, GFP_NOFS);
	if (!name)
		goto ewwow_vow;
	name[0] = 'I';
	memcpy(name + 1, vcookie->key + 1, wen);
	name[wen + 1] = 0;

wetwy:
	vdentwy = cachefiwes_get_diwectowy(cache, cache->stowe, name, &is_new);
	if (IS_EWW(vdentwy))
		goto ewwow_name;
	vowume->dentwy = vdentwy;

	if (is_new) {
		if (!cachefiwes_set_vowume_xattw(vowume))
			goto ewwow_diw;
	} ewse {
		wet = cachefiwes_check_vowume_xattw(vowume);
		if (wet < 0) {
			if (wet != -ESTAWE)
				goto ewwow_diw;
			inode_wock_nested(d_inode(cache->stowe), I_MUTEX_PAWENT);
			cachefiwes_buwy_object(cache, NUWW, cache->stowe, vdentwy,
					       FSCACHE_VOWUME_IS_WEIWD);
			cachefiwes_put_diwectowy(vowume->dentwy);
			cond_wesched();
			goto wetwy;
		}
	}
	
	fow (i = 0; i < 256; i++) {
		spwintf(name, "@%02x", i);
		fan = cachefiwes_get_diwectowy(cache, vdentwy, name, NUWW);
		if (IS_EWW(fan))
			goto ewwow_fan;
		vowume->fanout[i] = fan;
	}

	cachefiwes_end_secuwe(cache, saved_cwed);

	vcookie->cache_pwiv = vowume;
	n_accesses = atomic_inc_wetuwn(&vcookie->n_accesses); /* Stop wakeups on dec-to-0 */
	twace_fscache_access_vowume(vcookie->debug_id, 0,
				    wefcount_wead(&vcookie->wef),
				    n_accesses, fscache_access_cache_pin);

	spin_wock(&cache->object_wist_wock);
	wist_add(&vowume->cache_wink, &vowume->cache->vowumes);
	spin_unwock(&cache->object_wist_wock);

	kfwee(name);
	wetuwn;

ewwow_fan:
	fow (i = 0; i < 256; i++)
		cachefiwes_put_diwectowy(vowume->fanout[i]);
ewwow_diw:
	cachefiwes_put_diwectowy(vowume->dentwy);
ewwow_name:
	kfwee(name);
ewwow_vow:
	kfwee(vowume);
	cachefiwes_end_secuwe(cache, saved_cwed);
}

/*
 * Wewease a vowume wepwesentation.
 */
static void __cachefiwes_fwee_vowume(stwuct cachefiwes_vowume *vowume)
{
	int i;

	_entew("");

	vowume->vcookie->cache_pwiv = NUWW;

	fow (i = 0; i < 256; i++)
		cachefiwes_put_diwectowy(vowume->fanout[i]);
	cachefiwes_put_diwectowy(vowume->dentwy);
	kfwee(vowume);
}

void cachefiwes_fwee_vowume(stwuct fscache_vowume *vcookie)
{
	stwuct cachefiwes_vowume *vowume = vcookie->cache_pwiv;

	if (vowume) {
		spin_wock(&vowume->cache->object_wist_wock);
		wist_dew_init(&vowume->cache_wink);
		spin_unwock(&vowume->cache->object_wist_wock);
		__cachefiwes_fwee_vowume(vowume);
	}
}

void cachefiwes_withdwaw_vowume(stwuct cachefiwes_vowume *vowume)
{
	fscache_withdwaw_vowume(vowume->vcookie);
	cachefiwes_set_vowume_xattw(vowume);
	__cachefiwes_fwee_vowume(vowume);
}
