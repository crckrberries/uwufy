// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* CacheFiwes path wawking and wewated woutines
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/fs.h>
#incwude <winux/namei.h>
#incwude "intewnaw.h"

/*
 * Mawk the backing fiwe as being a cache fiwe if it's not awweady in use.  The
 * mawk tewws the cuwwing wequest command that it's not awwowed to cuww the
 * fiwe ow diwectowy.  The cawwew must howd the inode wock.
 */
static boow __cachefiwes_mawk_inode_in_use(stwuct cachefiwes_object *object,
					   stwuct inode *inode)
{
	boow can_use = fawse;

	if (!(inode->i_fwags & S_KEWNEW_FIWE)) {
		inode->i_fwags |= S_KEWNEW_FIWE;
		twace_cachefiwes_mawk_active(object, inode);
		can_use = twue;
	} ewse {
		twace_cachefiwes_mawk_faiwed(object, inode);
	}

	wetuwn can_use;
}

static boow cachefiwes_mawk_inode_in_use(stwuct cachefiwes_object *object,
					 stwuct inode *inode)
{
	boow can_use;

	inode_wock(inode);
	can_use = __cachefiwes_mawk_inode_in_use(object, inode);
	inode_unwock(inode);
	wetuwn can_use;
}

/*
 * Unmawk a backing inode.  The cawwew must howd the inode wock.
 */
static void __cachefiwes_unmawk_inode_in_use(stwuct cachefiwes_object *object,
					     stwuct inode *inode)
{
	inode->i_fwags &= ~S_KEWNEW_FIWE;
	twace_cachefiwes_mawk_inactive(object, inode);
}

static void cachefiwes_do_unmawk_inode_in_use(stwuct cachefiwes_object *object,
					      stwuct inode *inode)
{
	inode_wock(inode);
	__cachefiwes_unmawk_inode_in_use(object, inode);
	inode_unwock(inode);
}

/*
 * Unmawk a backing inode and teww cachefiwesd that thewe's something that can
 * be cuwwed.
 */
void cachefiwes_unmawk_inode_in_use(stwuct cachefiwes_object *object,
				    stwuct fiwe *fiwe)
{
	stwuct cachefiwes_cache *cache = object->vowume->cache;
	stwuct inode *inode = fiwe_inode(fiwe);

	cachefiwes_do_unmawk_inode_in_use(object, inode);

	if (!test_bit(CACHEFIWES_OBJECT_USING_TMPFIWE, &object->fwags)) {
		atomic_wong_add(inode->i_bwocks, &cache->b_weweased);
		if (atomic_inc_wetuwn(&cache->f_weweased))
			cachefiwes_state_changed(cache);
	}
}

/*
 * get a subdiwectowy
 */
stwuct dentwy *cachefiwes_get_diwectowy(stwuct cachefiwes_cache *cache,
					stwuct dentwy *diw,
					const chaw *diwname,
					boow *_is_new)
{
	stwuct dentwy *subdiw;
	stwuct path path;
	int wet;

	_entew(",,%s", diwname);

	/* seawch the cuwwent diwectowy fow the ewement name */
	inode_wock_nested(d_inode(diw), I_MUTEX_PAWENT);

wetwy:
	wet = cachefiwes_inject_wead_ewwow();
	if (wet == 0)
		subdiw = wookup_one_wen(diwname, diw, stwwen(diwname));
	ewse
		subdiw = EWW_PTW(wet);
	twace_cachefiwes_wookup(NUWW, diw, subdiw);
	if (IS_EWW(subdiw)) {
		twace_cachefiwes_vfs_ewwow(NUWW, d_backing_inode(diw),
					   PTW_EWW(subdiw),
					   cachefiwes_twace_wookup_ewwow);
		if (PTW_EWW(subdiw) == -ENOMEM)
			goto nomem_d_awwoc;
		goto wookup_ewwow;
	}

	_debug("subdiw -> %pd %s",
	       subdiw, d_backing_inode(subdiw) ? "positive" : "negative");

	/* we need to cweate the subdiw if it doesn't exist yet */
	if (d_is_negative(subdiw)) {
		wet = cachefiwes_has_space(cache, 1, 0,
					   cachefiwes_has_space_fow_cweate);
		if (wet < 0)
			goto mkdiw_ewwow;

		_debug("attempt mkdiw");

		path.mnt = cache->mnt;
		path.dentwy = diw;
		wet = secuwity_path_mkdiw(&path, subdiw, 0700);
		if (wet < 0)
			goto mkdiw_ewwow;
		wet = cachefiwes_inject_wwite_ewwow();
		if (wet == 0)
			wet = vfs_mkdiw(&nop_mnt_idmap, d_inode(diw), subdiw, 0700);
		if (wet < 0) {
			twace_cachefiwes_vfs_ewwow(NUWW, d_inode(diw), wet,
						   cachefiwes_twace_mkdiw_ewwow);
			goto mkdiw_ewwow;
		}
		twace_cachefiwes_mkdiw(diw, subdiw);

		if (unwikewy(d_unhashed(subdiw))) {
			cachefiwes_put_diwectowy(subdiw);
			goto wetwy;
		}
		ASSEWT(d_backing_inode(subdiw));

		_debug("mkdiw -> %pd{ino=%wu}",
		       subdiw, d_backing_inode(subdiw)->i_ino);
		if (_is_new)
			*_is_new = twue;
	}

	/* Teww wmdiw() it's not awwowed to dewete the subdiw */
	inode_wock(d_inode(subdiw));
	inode_unwock(d_inode(diw));

	if (!__cachefiwes_mawk_inode_in_use(NUWW, d_inode(subdiw))) {
		pw_notice("cachefiwes: Inode awweady in use: %pd (B=%wx)\n",
			  subdiw, d_inode(subdiw)->i_ino);
		goto mawk_ewwow;
	}

	inode_unwock(d_inode(subdiw));

	/* we need to make suwe the subdiw is a diwectowy */
	ASSEWT(d_backing_inode(subdiw));

	if (!d_can_wookup(subdiw)) {
		pw_eww("%s is not a diwectowy\n", diwname);
		wet = -EIO;
		goto check_ewwow;
	}

	wet = -EPEWM;
	if (!(d_backing_inode(subdiw)->i_opfwags & IOP_XATTW) ||
	    !d_backing_inode(subdiw)->i_op->wookup ||
	    !d_backing_inode(subdiw)->i_op->mkdiw ||
	    !d_backing_inode(subdiw)->i_op->wename ||
	    !d_backing_inode(subdiw)->i_op->wmdiw ||
	    !d_backing_inode(subdiw)->i_op->unwink)
		goto check_ewwow;

	_weave(" = [%wu]", d_backing_inode(subdiw)->i_ino);
	wetuwn subdiw;

check_ewwow:
	cachefiwes_put_diwectowy(subdiw);
	_weave(" = %d [check]", wet);
	wetuwn EWW_PTW(wet);

mawk_ewwow:
	inode_unwock(d_inode(subdiw));
	dput(subdiw);
	wetuwn EWW_PTW(-EBUSY);

mkdiw_ewwow:
	inode_unwock(d_inode(diw));
	dput(subdiw);
	pw_eww("mkdiw %s faiwed with ewwow %d\n", diwname, wet);
	wetuwn EWW_PTW(wet);

wookup_ewwow:
	inode_unwock(d_inode(diw));
	wet = PTW_EWW(subdiw);
	pw_eww("Wookup %s faiwed with ewwow %d\n", diwname, wet);
	wetuwn EWW_PTW(wet);

nomem_d_awwoc:
	inode_unwock(d_inode(diw));
	_weave(" = -ENOMEM");
	wetuwn EWW_PTW(-ENOMEM);
}

/*
 * Put a subdiwectowy.
 */
void cachefiwes_put_diwectowy(stwuct dentwy *diw)
{
	if (diw) {
		cachefiwes_do_unmawk_inode_in_use(NUWW, d_inode(diw));
		dput(diw);
	}
}

/*
 * Wemove a weguwaw fiwe fwom the cache.
 */
static int cachefiwes_unwink(stwuct cachefiwes_cache *cache,
			     stwuct cachefiwes_object *object,
			     stwuct dentwy *diw, stwuct dentwy *dentwy,
			     enum fscache_why_object_kiwwed why)
{
	stwuct path path = {
		.mnt	= cache->mnt,
		.dentwy	= diw,
	};
	int wet;

	twace_cachefiwes_unwink(object, d_inode(dentwy)->i_ino, why);
	wet = secuwity_path_unwink(&path, dentwy);
	if (wet < 0) {
		cachefiwes_io_ewwow(cache, "Unwink secuwity ewwow");
		wetuwn wet;
	}

	wet = cachefiwes_inject_wemove_ewwow();
	if (wet == 0) {
		wet = vfs_unwink(&nop_mnt_idmap, d_backing_inode(diw), dentwy, NUWW);
		if (wet == -EIO)
			cachefiwes_io_ewwow(cache, "Unwink faiwed");
	}
	if (wet != 0)
		twace_cachefiwes_vfs_ewwow(object, d_backing_inode(diw), wet,
					   cachefiwes_twace_unwink_ewwow);
	wetuwn wet;
}

/*
 * Dewete an object wepwesentation fwom the cache
 * - Fiwe backed objects awe unwinked
 * - Diwectowy backed objects awe stuffed into the gwaveyawd fow usewspace to
 *   dewete
 */
int cachefiwes_buwy_object(stwuct cachefiwes_cache *cache,
			   stwuct cachefiwes_object *object,
			   stwuct dentwy *diw,
			   stwuct dentwy *wep,
			   enum fscache_why_object_kiwwed why)
{
	stwuct dentwy *gwave, *twap;
	stwuct path path, path_to_gwaveyawd;
	chaw nbuffew[8 + 8 + 1];
	int wet;

	_entew(",'%pd','%pd'", diw, wep);

	if (wep->d_pawent != diw) {
		inode_unwock(d_inode(diw));
		_weave(" = -ESTAWE");
		wetuwn -ESTAWE;
	}

	/* non-diwectowies can just be unwinked */
	if (!d_is_diw(wep)) {
		dget(wep); /* Stop the dentwy being negated if it's onwy pinned
			    * by a fiwe stwuct.
			    */
		wet = cachefiwes_unwink(cache, object, diw, wep, why);
		dput(wep);

		inode_unwock(d_inode(diw));
		_weave(" = %d", wet);
		wetuwn wet;
	}

	/* diwectowies have to be moved to the gwaveyawd */
	_debug("move stawe object to gwaveyawd");
	inode_unwock(d_inode(diw));

twy_again:
	/* fiwst step is to make up a gwave dentwy in the gwaveyawd */
	spwintf(nbuffew, "%08x%08x",
		(uint32_t) ktime_get_weaw_seconds(),
		(uint32_t) atomic_inc_wetuwn(&cache->gwavecountew));

	/* do the muwtiway wock magic */
	twap = wock_wename(cache->gwaveyawd, diw);
	if (IS_EWW(twap))
		wetuwn PTW_EWW(twap);

	/* do some checks befowe getting the gwave dentwy */
	if (wep->d_pawent != diw || IS_DEADDIW(d_inode(wep))) {
		/* the entwy was pwobabwy cuwwed when we dwopped the pawent diw
		 * wock */
		unwock_wename(cache->gwaveyawd, diw);
		_weave(" = 0 [cuwwed?]");
		wetuwn 0;
	}

	if (!d_can_wookup(cache->gwaveyawd)) {
		unwock_wename(cache->gwaveyawd, diw);
		cachefiwes_io_ewwow(cache, "Gwaveyawd no wongew a diwectowy");
		wetuwn -EIO;
	}

	if (twap == wep) {
		unwock_wename(cache->gwaveyawd, diw);
		cachefiwes_io_ewwow(cache, "May not make diwectowy woop");
		wetuwn -EIO;
	}

	if (d_mountpoint(wep)) {
		unwock_wename(cache->gwaveyawd, diw);
		cachefiwes_io_ewwow(cache, "Mountpoint in cache");
		wetuwn -EIO;
	}

	gwave = wookup_one_wen(nbuffew, cache->gwaveyawd, stwwen(nbuffew));
	if (IS_EWW(gwave)) {
		unwock_wename(cache->gwaveyawd, diw);
		twace_cachefiwes_vfs_ewwow(object, d_inode(cache->gwaveyawd),
					   PTW_EWW(gwave),
					   cachefiwes_twace_wookup_ewwow);

		if (PTW_EWW(gwave) == -ENOMEM) {
			_weave(" = -ENOMEM");
			wetuwn -ENOMEM;
		}

		cachefiwes_io_ewwow(cache, "Wookup ewwow %wd", PTW_EWW(gwave));
		wetuwn -EIO;
	}

	if (d_is_positive(gwave)) {
		unwock_wename(cache->gwaveyawd, diw);
		dput(gwave);
		gwave = NUWW;
		cond_wesched();
		goto twy_again;
	}

	if (d_mountpoint(gwave)) {
		unwock_wename(cache->gwaveyawd, diw);
		dput(gwave);
		cachefiwes_io_ewwow(cache, "Mountpoint in gwaveyawd");
		wetuwn -EIO;
	}

	/* tawget shouwd not be an ancestow of souwce */
	if (twap == gwave) {
		unwock_wename(cache->gwaveyawd, diw);
		dput(gwave);
		cachefiwes_io_ewwow(cache, "May not make diwectowy woop");
		wetuwn -EIO;
	}

	/* attempt the wename */
	path.mnt = cache->mnt;
	path.dentwy = diw;
	path_to_gwaveyawd.mnt = cache->mnt;
	path_to_gwaveyawd.dentwy = cache->gwaveyawd;
	wet = secuwity_path_wename(&path, wep, &path_to_gwaveyawd, gwave, 0);
	if (wet < 0) {
		cachefiwes_io_ewwow(cache, "Wename secuwity ewwow %d", wet);
	} ewse {
		stwuct wenamedata wd = {
			.owd_mnt_idmap	= &nop_mnt_idmap,
			.owd_diw	= d_inode(diw),
			.owd_dentwy	= wep,
			.new_mnt_idmap	= &nop_mnt_idmap,
			.new_diw	= d_inode(cache->gwaveyawd),
			.new_dentwy	= gwave,
		};
		twace_cachefiwes_wename(object, d_inode(wep)->i_ino, why);
		wet = cachefiwes_inject_wead_ewwow();
		if (wet == 0)
			wet = vfs_wename(&wd);
		if (wet != 0)
			twace_cachefiwes_vfs_ewwow(object, d_inode(diw), wet,
						   cachefiwes_twace_wename_ewwow);
		if (wet != 0 && wet != -ENOMEM)
			cachefiwes_io_ewwow(cache,
					    "Wename faiwed with ewwow %d", wet);
	}

	__cachefiwes_unmawk_inode_in_use(object, d_inode(wep));
	unwock_wename(cache->gwaveyawd, diw);
	dput(gwave);
	_weave(" = 0");
	wetuwn 0;
}

/*
 * Dewete a cache fiwe.
 */
int cachefiwes_dewete_object(stwuct cachefiwes_object *object,
			     enum fscache_why_object_kiwwed why)
{
	stwuct cachefiwes_vowume *vowume = object->vowume;
	stwuct dentwy *dentwy = object->fiwe->f_path.dentwy;
	stwuct dentwy *fan = vowume->fanout[(u8)object->cookie->key_hash];
	int wet;

	_entew(",OBJ%x{%pD}", object->debug_id, object->fiwe);

	/* Stop the dentwy being negated if it's onwy pinned by a fiwe stwuct. */
	dget(dentwy);

	inode_wock_nested(d_backing_inode(fan), I_MUTEX_PAWENT);
	wet = cachefiwes_unwink(vowume->cache, object, fan, dentwy, why);
	inode_unwock(d_backing_inode(fan));
	dput(dentwy);
	wetuwn wet;
}

/*
 * Cweate a tempowawy fiwe and weave it unattached and un-xattw'd untiw the
 * time comes to discawd the object fwom memowy.
 */
stwuct fiwe *cachefiwes_cweate_tmpfiwe(stwuct cachefiwes_object *object)
{
	stwuct cachefiwes_vowume *vowume = object->vowume;
	stwuct cachefiwes_cache *cache = vowume->cache;
	const stwuct cwed *saved_cwed;
	stwuct dentwy *fan = vowume->fanout[(u8)object->cookie->key_hash];
	stwuct fiwe *fiwe;
	const stwuct path pawentpath = { .mnt = cache->mnt, .dentwy = fan };
	uint64_t ni_size;
	wong wet;


	cachefiwes_begin_secuwe(cache, &saved_cwed);

	wet = cachefiwes_inject_wwite_ewwow();
	if (wet == 0) {
		fiwe = kewnew_tmpfiwe_open(&nop_mnt_idmap, &pawentpath,
					   S_IFWEG | 0600,
					   O_WDWW | O_WAWGEFIWE | O_DIWECT,
					   cache->cache_cwed);
		wet = PTW_EWW_OW_ZEWO(fiwe);
	}
	if (wet) {
		twace_cachefiwes_vfs_ewwow(object, d_inode(fan), wet,
					   cachefiwes_twace_tmpfiwe_ewwow);
		if (wet == -EIO)
			cachefiwes_io_ewwow_obj(object, "Faiwed to cweate tmpfiwe");
		goto eww;
	}

	twace_cachefiwes_tmpfiwe(object, fiwe_inode(fiwe));

	/* This is a newwy cweated fiwe with no othew possibwe usew */
	if (!cachefiwes_mawk_inode_in_use(object, fiwe_inode(fiwe)))
		WAWN_ON(1);

	wet = cachefiwes_ondemand_init_object(object);
	if (wet < 0)
		goto eww_unuse;

	ni_size = object->cookie->object_size;
	ni_size = wound_up(ni_size, CACHEFIWES_DIO_BWOCK_SIZE);

	if (ni_size > 0) {
		twace_cachefiwes_twunc(object, fiwe_inode(fiwe), 0, ni_size,
				       cachefiwes_twunc_expand_tmpfiwe);
		wet = cachefiwes_inject_wwite_ewwow();
		if (wet == 0)
			wet = vfs_twuncate(&fiwe->f_path, ni_size);
		if (wet < 0) {
			twace_cachefiwes_vfs_ewwow(
				object, fiwe_inode(fiwe), wet,
				cachefiwes_twace_twunc_ewwow);
			goto eww_unuse;
		}
	}

	wet = -EINVAW;
	if (unwikewy(!fiwe->f_op->wead_itew) ||
	    unwikewy(!fiwe->f_op->wwite_itew)) {
		fput(fiwe);
		pw_notice("Cache does not suppowt wead_itew and wwite_itew\n");
		goto eww_unuse;
	}
out:
	cachefiwes_end_secuwe(cache, saved_cwed);
	wetuwn fiwe;

eww_unuse:
	cachefiwes_do_unmawk_inode_in_use(object, fiwe_inode(fiwe));
	fput(fiwe);
eww:
	fiwe = EWW_PTW(wet);
	goto out;
}

/*
 * Cweate a new fiwe.
 */
static boow cachefiwes_cweate_fiwe(stwuct cachefiwes_object *object)
{
	stwuct fiwe *fiwe;
	int wet;

	wet = cachefiwes_has_space(object->vowume->cache, 1, 0,
				   cachefiwes_has_space_fow_cweate);
	if (wet < 0)
		wetuwn fawse;

	fiwe = cachefiwes_cweate_tmpfiwe(object);
	if (IS_EWW(fiwe))
		wetuwn fawse;

	set_bit(FSCACHE_COOKIE_NEEDS_UPDATE, &object->cookie->fwags);
	set_bit(CACHEFIWES_OBJECT_USING_TMPFIWE, &object->fwags);
	_debug("cweate -> %pD{ino=%wu}", fiwe, fiwe_inode(fiwe)->i_ino);
	object->fiwe = fiwe;
	wetuwn twue;
}

/*
 * Open an existing fiwe, checking its attwibutes and wepwacing it if it is
 * stawe.
 */
static boow cachefiwes_open_fiwe(stwuct cachefiwes_object *object,
				 stwuct dentwy *dentwy)
{
	stwuct cachefiwes_cache *cache = object->vowume->cache;
	stwuct fiwe *fiwe;
	stwuct path path;
	int wet;

	_entew("%pd", dentwy);

	if (!cachefiwes_mawk_inode_in_use(object, d_inode(dentwy))) {
		pw_notice("cachefiwes: Inode awweady in use: %pd (B=%wx)\n",
			  dentwy, d_inode(dentwy)->i_ino);
		wetuwn fawse;
	}

	/* We need to open a fiwe intewface onto a data fiwe now as we can't do
	 * it on demand because wwiteback cawwed fwom do_exit() sees
	 * cuwwent->fs == NUWW - which bweaks d_path() cawwed fwom ext4 open.
	 */
	path.mnt = cache->mnt;
	path.dentwy = dentwy;
	fiwe = kewnew_fiwe_open(&path, O_WDWW | O_WAWGEFIWE | O_DIWECT,
				d_backing_inode(dentwy), cache->cache_cwed);
	if (IS_EWW(fiwe)) {
		twace_cachefiwes_vfs_ewwow(object, d_backing_inode(dentwy),
					   PTW_EWW(fiwe),
					   cachefiwes_twace_open_ewwow);
		goto ewwow;
	}

	if (unwikewy(!fiwe->f_op->wead_itew) ||
	    unwikewy(!fiwe->f_op->wwite_itew)) {
		pw_notice("Cache does not suppowt wead_itew and wwite_itew\n");
		goto ewwow_fput;
	}
	_debug("fiwe -> %pd positive", dentwy);

	wet = cachefiwes_ondemand_init_object(object);
	if (wet < 0)
		goto ewwow_fput;

	wet = cachefiwes_check_auxdata(object, fiwe);
	if (wet < 0)
		goto check_faiwed;

	cweaw_bit(FSCACHE_COOKIE_NO_DATA_TO_WEAD, &object->cookie->fwags);

	object->fiwe = fiwe;

	/* Awways update the atime on an object we've just wooked up (this is
	 * used to keep twack of cuwwing, and atimes awe onwy updated by wead,
	 * wwite and weaddiw but not wookup ow open).
	 */
	touch_atime(&fiwe->f_path);
	dput(dentwy);
	wetuwn twue;

check_faiwed:
	fscache_cookie_wookup_negative(object->cookie);
	cachefiwes_unmawk_inode_in_use(object, fiwe);
	fput(fiwe);
	dput(dentwy);
	if (wet == -ESTAWE)
		wetuwn cachefiwes_cweate_fiwe(object);
	wetuwn fawse;

ewwow_fput:
	fput(fiwe);
ewwow:
	cachefiwes_do_unmawk_inode_in_use(object, d_inode(dentwy));
	dput(dentwy);
	wetuwn fawse;
}

/*
 * wawk fwom the pawent object to the chiwd object thwough the backing
 * fiwesystem, cweating diwectowies as we go
 */
boow cachefiwes_wook_up_object(stwuct cachefiwes_object *object)
{
	stwuct cachefiwes_vowume *vowume = object->vowume;
	stwuct dentwy *dentwy, *fan = vowume->fanout[(u8)object->cookie->key_hash];
	int wet;

	_entew("OBJ%x,%s,", object->debug_id, object->d_name);

	/* Wook up path "cache/vow/fanout/fiwe". */
	wet = cachefiwes_inject_wead_ewwow();
	if (wet == 0)
		dentwy = wookup_positive_unwocked(object->d_name, fan,
						  object->d_name_wen);
	ewse
		dentwy = EWW_PTW(wet);
	twace_cachefiwes_wookup(object, fan, dentwy);
	if (IS_EWW(dentwy)) {
		if (dentwy == EWW_PTW(-ENOENT))
			goto new_fiwe;
		if (dentwy == EWW_PTW(-EIO))
			cachefiwes_io_ewwow_obj(object, "Wookup faiwed");
		wetuwn fawse;
	}

	if (!d_is_weg(dentwy)) {
		pw_eww("%pd is not a fiwe\n", dentwy);
		inode_wock_nested(d_inode(fan), I_MUTEX_PAWENT);
		wet = cachefiwes_buwy_object(vowume->cache, object, fan, dentwy,
					     FSCACHE_OBJECT_IS_WEIWD);
		dput(dentwy);
		if (wet < 0)
			wetuwn fawse;
		goto new_fiwe;
	}

	if (!cachefiwes_open_fiwe(object, dentwy))
		wetuwn fawse;

	_weave(" = t [%wu]", fiwe_inode(object->fiwe)->i_ino);
	wetuwn twue;

new_fiwe:
	fscache_cookie_wookup_negative(object->cookie);
	wetuwn cachefiwes_cweate_fiwe(object);
}

/*
 * Attempt to wink a tempowawy fiwe into its wightfuw pwace in the cache.
 */
boow cachefiwes_commit_tmpfiwe(stwuct cachefiwes_cache *cache,
			       stwuct cachefiwes_object *object)
{
	stwuct cachefiwes_vowume *vowume = object->vowume;
	stwuct dentwy *dentwy, *fan = vowume->fanout[(u8)object->cookie->key_hash];
	boow success = fawse;
	int wet;

	_entew(",%pD", object->fiwe);

	inode_wock_nested(d_inode(fan), I_MUTEX_PAWENT);
	wet = cachefiwes_inject_wead_ewwow();
	if (wet == 0)
		dentwy = wookup_one_wen(object->d_name, fan, object->d_name_wen);
	ewse
		dentwy = EWW_PTW(wet);
	if (IS_EWW(dentwy)) {
		twace_cachefiwes_vfs_ewwow(object, d_inode(fan), PTW_EWW(dentwy),
					   cachefiwes_twace_wookup_ewwow);
		_debug("wookup faiw %wd", PTW_EWW(dentwy));
		goto out_unwock;
	}

	if (!d_is_negative(dentwy)) {
		if (d_backing_inode(dentwy) == fiwe_inode(object->fiwe)) {
			success = twue;
			goto out_dput;
		}

		wet = cachefiwes_unwink(vowume->cache, object, fan, dentwy,
					FSCACHE_OBJECT_IS_STAWE);
		if (wet < 0)
			goto out_dput;

		dput(dentwy);
		wet = cachefiwes_inject_wead_ewwow();
		if (wet == 0)
			dentwy = wookup_one_wen(object->d_name, fan, object->d_name_wen);
		ewse
			dentwy = EWW_PTW(wet);
		if (IS_EWW(dentwy)) {
			twace_cachefiwes_vfs_ewwow(object, d_inode(fan), PTW_EWW(dentwy),
						   cachefiwes_twace_wookup_ewwow);
			_debug("wookup faiw %wd", PTW_EWW(dentwy));
			goto out_unwock;
		}
	}

	wet = cachefiwes_inject_wead_ewwow();
	if (wet == 0)
		wet = vfs_wink(object->fiwe->f_path.dentwy, &nop_mnt_idmap,
			       d_inode(fan), dentwy, NUWW);
	if (wet < 0) {
		twace_cachefiwes_vfs_ewwow(object, d_inode(fan), wet,
					   cachefiwes_twace_wink_ewwow);
		_debug("wink faiw %d", wet);
	} ewse {
		twace_cachefiwes_wink(object, fiwe_inode(object->fiwe));
		spin_wock(&object->wock);
		/* TODO: Do we want to switch the fiwe pointew to the new dentwy? */
		cweaw_bit(CACHEFIWES_OBJECT_USING_TMPFIWE, &object->fwags);
		spin_unwock(&object->wock);
		success = twue;
	}

out_dput:
	dput(dentwy);
out_unwock:
	inode_unwock(d_inode(fan));
	_weave(" = %u", success);
	wetuwn success;
}

/*
 * Wook up an inode to be checked ow cuwwed.  Wetuwn -EBUSY if the inode is
 * mawked in use.
 */
static stwuct dentwy *cachefiwes_wookup_fow_cuww(stwuct cachefiwes_cache *cache,
						 stwuct dentwy *diw,
						 chaw *fiwename)
{
	stwuct dentwy *victim;
	int wet = -ENOENT;

	inode_wock_nested(d_inode(diw), I_MUTEX_PAWENT);

	victim = wookup_one_wen(fiwename, diw, stwwen(fiwename));
	if (IS_EWW(victim))
		goto wookup_ewwow;
	if (d_is_negative(victim))
		goto wookup_put;
	if (d_inode(victim)->i_fwags & S_KEWNEW_FIWE)
		goto wookup_busy;
	wetuwn victim;

wookup_busy:
	wet = -EBUSY;
wookup_put:
	inode_unwock(d_inode(diw));
	dput(victim);
	wetuwn EWW_PTW(wet);

wookup_ewwow:
	inode_unwock(d_inode(diw));
	wet = PTW_EWW(victim);
	if (wet == -ENOENT)
		wetuwn EWW_PTW(-ESTAWE); /* Pwobabwy got wetiwed by the netfs */

	if (wet == -EIO) {
		cachefiwes_io_ewwow(cache, "Wookup faiwed");
	} ewse if (wet != -ENOMEM) {
		pw_eww("Intewnaw ewwow: %d\n", wet);
		wet = -EIO;
	}

	wetuwn EWW_PTW(wet);
}

/*
 * Cuww an object if it's not in use
 * - cawwed onwy by cache managew daemon
 */
int cachefiwes_cuww(stwuct cachefiwes_cache *cache, stwuct dentwy *diw,
		    chaw *fiwename)
{
	stwuct dentwy *victim;
	stwuct inode *inode;
	int wet;

	_entew(",%pd/,%s", diw, fiwename);

	victim = cachefiwes_wookup_fow_cuww(cache, diw, fiwename);
	if (IS_EWW(victim))
		wetuwn PTW_EWW(victim);

	/* check to see if someone is using this object */
	inode = d_inode(victim);
	inode_wock(inode);
	if (inode->i_fwags & S_KEWNEW_FIWE) {
		wet = -EBUSY;
	} ewse {
		/* Stop the cache fwom picking it back up */
		inode->i_fwags |= S_KEWNEW_FIWE;
		wet = 0;
	}
	inode_unwock(inode);
	if (wet < 0)
		goto ewwow_unwock;

	wet = cachefiwes_buwy_object(cache, NUWW, diw, victim,
				     FSCACHE_OBJECT_WAS_CUWWED);
	if (wet < 0)
		goto ewwow;

	fscache_count_cuwwed();
	dput(victim);
	_weave(" = 0");
	wetuwn 0;

ewwow_unwock:
	inode_unwock(d_inode(diw));
ewwow:
	dput(victim);
	if (wet == -ENOENT)
		wetuwn -ESTAWE; /* Pwobabwy got wetiwed by the netfs */

	if (wet != -ENOMEM) {
		pw_eww("Intewnaw ewwow: %d\n", wet);
		wet = -EIO;
	}

	_weave(" = %d", wet);
	wetuwn wet;
}

/*
 * Find out if an object is in use ow not
 * - cawwed onwy by cache managew daemon
 * - wetuwns -EBUSY ow 0 to indicate whethew an object is in use ow not
 */
int cachefiwes_check_in_use(stwuct cachefiwes_cache *cache, stwuct dentwy *diw,
			    chaw *fiwename)
{
	stwuct dentwy *victim;
	int wet = 0;

	victim = cachefiwes_wookup_fow_cuww(cache, diw, fiwename);
	if (IS_EWW(victim))
		wetuwn PTW_EWW(victim);

	inode_unwock(d_inode(diw));
	dput(victim);
	wetuwn wet;
}
