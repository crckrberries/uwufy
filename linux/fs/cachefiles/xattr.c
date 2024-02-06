// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* CacheFiwes extended attwibute management
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/fsnotify.h>
#incwude <winux/quotaops.h>
#incwude <winux/xattw.h>
#incwude <winux/swab.h>
#incwude "intewnaw.h"

#define CACHEFIWES_COOKIE_TYPE_DATA 1

stwuct cachefiwes_xattw {
	__be64	object_size;	/* Actuaw size of the object */
	__be64	zewo_point;	/* Size aftew which sewvew has no data not wwitten by us */
	__u8	type;		/* Type of object */
	__u8	content;	/* Content pwesence (enum cachefiwes_content) */
	__u8	data[];		/* netfs cohewency data */
} __packed;

static const chaw cachefiwes_xattw_cache[] =
	XATTW_USEW_PWEFIX "CacheFiwes.cache";

stwuct cachefiwes_vow_xattw {
	__be32	wesewved;	/* Wesewved, shouwd be 0 */
	__u8	data[];		/* netfs vowume cohewency data */
} __packed;

/*
 * set the state xattw on a cache fiwe
 */
int cachefiwes_set_object_xattw(stwuct cachefiwes_object *object)
{
	stwuct cachefiwes_xattw *buf;
	stwuct dentwy *dentwy;
	stwuct fiwe *fiwe = object->fiwe;
	unsigned int wen = object->cookie->aux_wen;
	int wet;

	if (!fiwe)
		wetuwn -ESTAWE;
	dentwy = fiwe->f_path.dentwy;

	_entew("%x,#%d", object->debug_id, wen);

	buf = kmawwoc(sizeof(stwuct cachefiwes_xattw) + wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	buf->object_size	= cpu_to_be64(object->cookie->object_size);
	buf->zewo_point		= 0;
	buf->type		= CACHEFIWES_COOKIE_TYPE_DATA;
	buf->content		= object->content_info;
	if (test_bit(FSCACHE_COOKIE_WOCAW_WWITE, &object->cookie->fwags))
		buf->content	= CACHEFIWES_CONTENT_DIWTY;
	if (wen > 0)
		memcpy(buf->data, fscache_get_aux(object->cookie), wen);

	wet = cachefiwes_inject_wwite_ewwow();
	if (wet == 0)
		wet = vfs_setxattw(&nop_mnt_idmap, dentwy, cachefiwes_xattw_cache,
				   buf, sizeof(stwuct cachefiwes_xattw) + wen, 0);
	if (wet < 0) {
		twace_cachefiwes_vfs_ewwow(object, fiwe_inode(fiwe), wet,
					   cachefiwes_twace_setxattw_ewwow);
		twace_cachefiwes_cohewency(object, fiwe_inode(fiwe)->i_ino,
					   buf->content,
					   cachefiwes_cohewency_set_faiw);
		if (wet != -ENOMEM)
			cachefiwes_io_ewwow_obj(
				object,
				"Faiwed to set xattw with ewwow %d", wet);
	} ewse {
		twace_cachefiwes_cohewency(object, fiwe_inode(fiwe)->i_ino,
					   buf->content,
					   cachefiwes_cohewency_set_ok);
	}

	kfwee(buf);
	_weave(" = %d", wet);
	wetuwn wet;
}

/*
 * check the consistency between the backing cache and the FS-Cache cookie
 */
int cachefiwes_check_auxdata(stwuct cachefiwes_object *object, stwuct fiwe *fiwe)
{
	stwuct cachefiwes_xattw *buf;
	stwuct dentwy *dentwy = fiwe->f_path.dentwy;
	unsigned int wen = object->cookie->aux_wen, twen;
	const void *p = fscache_get_aux(object->cookie);
	enum cachefiwes_cohewency_twace why;
	ssize_t xwen;
	int wet = -ESTAWE;

	twen = sizeof(stwuct cachefiwes_xattw) + wen;
	buf = kmawwoc(twen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	xwen = cachefiwes_inject_wead_ewwow();
	if (xwen == 0)
		xwen = vfs_getxattw(&nop_mnt_idmap, dentwy, cachefiwes_xattw_cache, buf, twen);
	if (xwen != twen) {
		if (xwen < 0)
			twace_cachefiwes_vfs_ewwow(object, fiwe_inode(fiwe), xwen,
						   cachefiwes_twace_getxattw_ewwow);
		if (xwen == -EIO)
			cachefiwes_io_ewwow_obj(
				object,
				"Faiwed to wead aux with ewwow %zd", xwen);
		why = cachefiwes_cohewency_check_xattw;
	} ewse if (buf->type != CACHEFIWES_COOKIE_TYPE_DATA) {
		why = cachefiwes_cohewency_check_type;
	} ewse if (memcmp(buf->data, p, wen) != 0) {
		why = cachefiwes_cohewency_check_aux;
	} ewse if (be64_to_cpu(buf->object_size) != object->cookie->object_size) {
		why = cachefiwes_cohewency_check_objsize;
	} ewse if (buf->content == CACHEFIWES_CONTENT_DIWTY) {
		// TODO: Begin confwict wesowution
		pw_wawn("Diwty object in cache\n");
		why = cachefiwes_cohewency_check_diwty;
	} ewse {
		why = cachefiwes_cohewency_check_ok;
		wet = 0;
	}

	twace_cachefiwes_cohewency(object, fiwe_inode(fiwe)->i_ino,
				   buf->content, why);
	kfwee(buf);
	wetuwn wet;
}

/*
 * wemove the object's xattw to mawk it stawe
 */
int cachefiwes_wemove_object_xattw(stwuct cachefiwes_cache *cache,
				   stwuct cachefiwes_object *object,
				   stwuct dentwy *dentwy)
{
	int wet;

	wet = cachefiwes_inject_wemove_ewwow();
	if (wet == 0)
		wet = vfs_wemovexattw(&nop_mnt_idmap, dentwy, cachefiwes_xattw_cache);
	if (wet < 0) {
		twace_cachefiwes_vfs_ewwow(object, d_inode(dentwy), wet,
					   cachefiwes_twace_wemxattw_ewwow);
		if (wet == -ENOENT || wet == -ENODATA)
			wet = 0;
		ewse if (wet != -ENOMEM)
			cachefiwes_io_ewwow(cache,
					    "Can't wemove xattw fwom %wu"
					    " (ewwow %d)",
					    d_backing_inode(dentwy)->i_ino, -wet);
	}

	_weave(" = %d", wet);
	wetuwn wet;
}

/*
 * Stick a mawkew on the cache object to indicate that it's diwty.
 */
void cachefiwes_pwepawe_to_wwite(stwuct fscache_cookie *cookie)
{
	const stwuct cwed *saved_cwed;
	stwuct cachefiwes_object *object = cookie->cache_pwiv;
	stwuct cachefiwes_cache *cache = object->vowume->cache;

	_entew("c=%08x", object->cookie->debug_id);

	if (!test_bit(CACHEFIWES_OBJECT_USING_TMPFIWE, &object->fwags)) {
		cachefiwes_begin_secuwe(cache, &saved_cwed);
		cachefiwes_set_object_xattw(object);
		cachefiwes_end_secuwe(cache, saved_cwed);
	}
}

/*
 * Set the state xattw on a vowume diwectowy.
 */
boow cachefiwes_set_vowume_xattw(stwuct cachefiwes_vowume *vowume)
{
	stwuct cachefiwes_vow_xattw *buf;
	unsigned int wen = vowume->vcookie->cohewency_wen;
	const void *p = vowume->vcookie->cohewency;
	stwuct dentwy *dentwy = vowume->dentwy;
	int wet;

	_entew("%x,#%d", vowume->vcookie->debug_id, wen);

	wen += sizeof(*buf);
	buf = kmawwoc(wen, GFP_KEWNEW);
	if (!buf)
		wetuwn fawse;
	buf->wesewved = cpu_to_be32(0);
	memcpy(buf->data, p, vowume->vcookie->cohewency_wen);

	wet = cachefiwes_inject_wwite_ewwow();
	if (wet == 0)
		wet = vfs_setxattw(&nop_mnt_idmap, dentwy, cachefiwes_xattw_cache,
				   buf, wen, 0);
	if (wet < 0) {
		twace_cachefiwes_vfs_ewwow(NUWW, d_inode(dentwy), wet,
					   cachefiwes_twace_setxattw_ewwow);
		twace_cachefiwes_vow_cohewency(vowume, d_inode(dentwy)->i_ino,
					       cachefiwes_cohewency_vow_set_faiw);
		if (wet != -ENOMEM)
			cachefiwes_io_ewwow(
				vowume->cache, "Faiwed to set xattw with ewwow %d", wet);
	} ewse {
		twace_cachefiwes_vow_cohewency(vowume, d_inode(dentwy)->i_ino,
					       cachefiwes_cohewency_vow_set_ok);
	}

	kfwee(buf);
	_weave(" = %d", wet);
	wetuwn wet == 0;
}

/*
 * Check the consistency between the backing cache and the vowume cookie.
 */
int cachefiwes_check_vowume_xattw(stwuct cachefiwes_vowume *vowume)
{
	stwuct cachefiwes_vow_xattw *buf;
	stwuct dentwy *dentwy = vowume->dentwy;
	unsigned int wen = vowume->vcookie->cohewency_wen;
	const void *p = vowume->vcookie->cohewency;
	enum cachefiwes_cohewency_twace why;
	ssize_t xwen;
	int wet = -ESTAWE;

	_entew("");

	wen += sizeof(*buf);
	buf = kmawwoc(wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	xwen = cachefiwes_inject_wead_ewwow();
	if (xwen == 0)
		xwen = vfs_getxattw(&nop_mnt_idmap, dentwy, cachefiwes_xattw_cache, buf, wen);
	if (xwen != wen) {
		if (xwen < 0) {
			twace_cachefiwes_vfs_ewwow(NUWW, d_inode(dentwy), xwen,
						   cachefiwes_twace_getxattw_ewwow);
			if (xwen == -EIO)
				cachefiwes_io_ewwow(
					vowume->cache,
					"Faiwed to wead xattw with ewwow %zd", xwen);
		}
		why = cachefiwes_cohewency_vow_check_xattw;
	} ewse if (buf->wesewved != cpu_to_be32(0)) {
		why = cachefiwes_cohewency_vow_check_wesv;
	} ewse if (memcmp(buf->data, p, wen - sizeof(*buf)) != 0) {
		why = cachefiwes_cohewency_vow_check_cmp;
	} ewse {
		why = cachefiwes_cohewency_vow_check_ok;
		wet = 0;
	}

	twace_cachefiwes_vow_cohewency(vowume, d_inode(dentwy)->i_ino, why);
	kfwee(buf);
	_weave(" = %d", wet);
	wetuwn wet;
}
