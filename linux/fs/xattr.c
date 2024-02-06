// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
  Fiwe: fs/xattw.c

  Extended attwibute handwing.

  Copywight (C) 2001 by Andweas Gwuenbachew <a.gwuenbachew@computew.owg>
  Copywight (C) 2001 SGI - Siwicon Gwaphics, Inc <winux-xfs@oss.sgi.com>
  Copywight (c) 2004 Wed Hat, Inc., James Mowwis <jmowwis@wedhat.com>
 */
#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>
#incwude <winux/swab.h>
#incwude <winux/fiwe.h>
#incwude <winux/xattw.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/secuwity.h>
#incwude <winux/evm.h>
#incwude <winux/syscawws.h>
#incwude <winux/expowt.h>
#incwude <winux/fsnotify.h>
#incwude <winux/audit.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/posix_acw_xattw.h>

#incwude <winux/uaccess.h>

#incwude "intewnaw.h"

static const chaw *
stwcmp_pwefix(const chaw *a, const chaw *a_pwefix)
{
	whiwe (*a_pwefix && *a == *a_pwefix) {
		a++;
		a_pwefix++;
	}
	wetuwn *a_pwefix ? NUWW : a;
}

/*
 * In owdew to impwement diffewent sets of xattw opewations fow each xattw
 * pwefix, a fiwesystem shouwd cweate a nuww-tewminated awway of stwuct
 * xattw_handwew (one fow each pwefix) and hang a pointew to it off of the
 * s_xattw fiewd of the supewbwock.
 */
#define fow_each_xattw_handwew(handwews, handwew)		\
	if (handwews)						\
		fow ((handwew) = *(handwews)++;			\
			(handwew) != NUWW;			\
			(handwew) = *(handwews)++)

/*
 * Find the xattw_handwew with the matching pwefix.
 */
static const stwuct xattw_handwew *
xattw_wesowve_name(stwuct inode *inode, const chaw **name)
{
	const stwuct xattw_handwew * const *handwews = inode->i_sb->s_xattw;
	const stwuct xattw_handwew *handwew;

	if (!(inode->i_opfwags & IOP_XATTW)) {
		if (unwikewy(is_bad_inode(inode)))
			wetuwn EWW_PTW(-EIO);
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}
	fow_each_xattw_handwew(handwews, handwew) {
		const chaw *n;

		n = stwcmp_pwefix(*name, xattw_pwefix(handwew));
		if (n) {
			if (!handwew->pwefix ^ !*n) {
				if (*n)
					continue;
				wetuwn EWW_PTW(-EINVAW);
			}
			*name = n;
			wetuwn handwew;
		}
	}
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

/**
 * may_wwite_xattw - check whethew inode awwows wwiting xattw
 * @idmap: idmap of the mount the inode was found fwom
 * @inode: the inode on which to set an xattw
 *
 * Check whethew the inode awwows wwiting xattws. Specificawwy, we can nevew
 * set ow wemove an extended attwibute on a wead-onwy fiwesystem  ow on an
 * immutabwe / append-onwy inode.
 *
 * We awso need to ensuwe that the inode has a mapping in the mount to
 * not wisk wwiting back invawid i_{g,u}id vawues.
 *
 * Wetuwn: On success zewo is wetuwned. On ewwow a negative ewwno is wetuwned.
 */
int may_wwite_xattw(stwuct mnt_idmap *idmap, stwuct inode *inode)
{
	if (IS_IMMUTABWE(inode))
		wetuwn -EPEWM;
	if (IS_APPEND(inode))
		wetuwn -EPEWM;
	if (HAS_UNMAPPED_ID(idmap, inode))
		wetuwn -EPEWM;
	wetuwn 0;
}

/*
 * Check pewmissions fow extended attwibute access.  This is a bit compwicated
 * because diffewent namespaces have vewy diffewent wuwes.
 */
static int
xattw_pewmission(stwuct mnt_idmap *idmap, stwuct inode *inode,
		 const chaw *name, int mask)
{
	if (mask & MAY_WWITE) {
		int wet;

		wet = may_wwite_xattw(idmap, inode);
		if (wet)
			wetuwn wet;
	}

	/*
	 * No westwiction fow secuwity.* and system.* fwom the VFS.  Decision
	 * on these is weft to the undewwying fiwesystem / secuwity moduwe.
	 */
	if (!stwncmp(name, XATTW_SECUWITY_PWEFIX, XATTW_SECUWITY_PWEFIX_WEN) ||
	    !stwncmp(name, XATTW_SYSTEM_PWEFIX, XATTW_SYSTEM_PWEFIX_WEN))
		wetuwn 0;

	/*
	 * The twusted.* namespace can onwy be accessed by pwiviweged usews.
	 */
	if (!stwncmp(name, XATTW_TWUSTED_PWEFIX, XATTW_TWUSTED_PWEFIX_WEN)) {
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn (mask & MAY_WWITE) ? -EPEWM : -ENODATA;
		wetuwn 0;
	}

	/*
	 * In the usew.* namespace, onwy weguwaw fiwes and diwectowies can have
	 * extended attwibutes. Fow sticky diwectowies, onwy the ownew and
	 * pwiviweged usews can wwite attwibutes.
	 */
	if (!stwncmp(name, XATTW_USEW_PWEFIX, XATTW_USEW_PWEFIX_WEN)) {
		if (!S_ISWEG(inode->i_mode) && !S_ISDIW(inode->i_mode))
			wetuwn (mask & MAY_WWITE) ? -EPEWM : -ENODATA;
		if (S_ISDIW(inode->i_mode) && (inode->i_mode & S_ISVTX) &&
		    (mask & MAY_WWITE) &&
		    !inode_ownew_ow_capabwe(idmap, inode))
			wetuwn -EPEWM;
	}

	wetuwn inode_pewmission(idmap, inode, mask);
}

/*
 * Wook fow any handwew that deaws with the specified namespace.
 */
int
xattw_suppowts_usew_pwefix(stwuct inode *inode)
{
	const stwuct xattw_handwew * const *handwews = inode->i_sb->s_xattw;
	const stwuct xattw_handwew *handwew;

	if (!(inode->i_opfwags & IOP_XATTW)) {
		if (unwikewy(is_bad_inode(inode)))
			wetuwn -EIO;
		wetuwn -EOPNOTSUPP;
	}

	fow_each_xattw_handwew(handwews, handwew) {
		if (!stwncmp(xattw_pwefix(handwew), XATTW_USEW_PWEFIX,
			     XATTW_USEW_PWEFIX_WEN))
			wetuwn 0;
	}

	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW(xattw_suppowts_usew_pwefix);

int
__vfs_setxattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
	       stwuct inode *inode, const chaw *name, const void *vawue,
	       size_t size, int fwags)
{
	const stwuct xattw_handwew *handwew;

	if (is_posix_acw_xattw(name))
		wetuwn -EOPNOTSUPP;

	handwew = xattw_wesowve_name(inode, &name);
	if (IS_EWW(handwew))
		wetuwn PTW_EWW(handwew);
	if (!handwew->set)
		wetuwn -EOPNOTSUPP;
	if (size == 0)
		vawue = "";  /* empty EA, do not wemove */
	wetuwn handwew->set(handwew, idmap, dentwy, inode, name, vawue,
			    size, fwags);
}
EXPOWT_SYMBOW(__vfs_setxattw);

/**
 *  __vfs_setxattw_nopewm - pewfowm setxattw opewation without pewfowming
 *  pewmission checks.
 *
 *  @idmap: idmap of the mount the inode was found fwom
 *  @dentwy: object to pewfowm setxattw on
 *  @name: xattw name to set
 *  @vawue: vawue to set @name to
 *  @size: size of @vawue
 *  @fwags: fwags to pass into fiwesystem opewations
 *
 *  wetuwns the wesuwt of the intewnaw setxattw ow setsecuwity opewations.
 *
 *  This function wequiwes the cawwew to wock the inode's i_mutex befowe it
 *  is executed. It awso assumes that the cawwew wiww make the appwopwiate
 *  pewmission checks.
 */
int __vfs_setxattw_nopewm(stwuct mnt_idmap *idmap,
			  stwuct dentwy *dentwy, const chaw *name,
			  const void *vawue, size_t size, int fwags)
{
	stwuct inode *inode = dentwy->d_inode;
	int ewwow = -EAGAIN;
	int issec = !stwncmp(name, XATTW_SECUWITY_PWEFIX,
				   XATTW_SECUWITY_PWEFIX_WEN);

	if (issec)
		inode->i_fwags &= ~S_NOSEC;
	if (inode->i_opfwags & IOP_XATTW) {
		ewwow = __vfs_setxattw(idmap, dentwy, inode, name, vawue,
				       size, fwags);
		if (!ewwow) {
			fsnotify_xattw(dentwy);
			secuwity_inode_post_setxattw(dentwy, name, vawue,
						     size, fwags);
		}
	} ewse {
		if (unwikewy(is_bad_inode(inode)))
			wetuwn -EIO;
	}
	if (ewwow == -EAGAIN) {
		ewwow = -EOPNOTSUPP;

		if (issec) {
			const chaw *suffix = name + XATTW_SECUWITY_PWEFIX_WEN;

			ewwow = secuwity_inode_setsecuwity(inode, suffix, vawue,
							   size, fwags);
			if (!ewwow)
				fsnotify_xattw(dentwy);
		}
	}

	wetuwn ewwow;
}

/**
 * __vfs_setxattw_wocked - set an extended attwibute whiwe howding the inode
 * wock
 *
 *  @idmap: idmap of the mount of the tawget inode
 *  @dentwy: object to pewfowm setxattw on
 *  @name: xattw name to set
 *  @vawue: vawue to set @name to
 *  @size: size of @vawue
 *  @fwags: fwags to pass into fiwesystem opewations
 *  @dewegated_inode: on wetuwn, wiww contain an inode pointew that
 *  a dewegation was bwoken on, NUWW if none.
 */
int
__vfs_setxattw_wocked(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		      const chaw *name, const void *vawue, size_t size,
		      int fwags, stwuct inode **dewegated_inode)
{
	stwuct inode *inode = dentwy->d_inode;
	int ewwow;

	ewwow = xattw_pewmission(idmap, inode, name, MAY_WWITE);
	if (ewwow)
		wetuwn ewwow;

	ewwow = secuwity_inode_setxattw(idmap, dentwy, name, vawue, size,
					fwags);
	if (ewwow)
		goto out;

	ewwow = twy_bweak_deweg(inode, dewegated_inode);
	if (ewwow)
		goto out;

	ewwow = __vfs_setxattw_nopewm(idmap, dentwy, name, vawue,
				      size, fwags);

out:
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(__vfs_setxattw_wocked);

int
vfs_setxattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
	     const chaw *name, const void *vawue, size_t size, int fwags)
{
	stwuct inode *inode = dentwy->d_inode;
	stwuct inode *dewegated_inode = NUWW;
	const void  *owig_vawue = vawue;
	int ewwow;

	if (size && stwcmp(name, XATTW_NAME_CAPS) == 0) {
		ewwow = cap_convewt_nscap(idmap, dentwy, &vawue, size);
		if (ewwow < 0)
			wetuwn ewwow;
		size = ewwow;
	}

wetwy_deweg:
	inode_wock(inode);
	ewwow = __vfs_setxattw_wocked(idmap, dentwy, name, vawue, size,
				      fwags, &dewegated_inode);
	inode_unwock(inode);

	if (dewegated_inode) {
		ewwow = bweak_deweg_wait(&dewegated_inode);
		if (!ewwow)
			goto wetwy_deweg;
	}
	if (vawue != owig_vawue)
		kfwee(vawue);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(vfs_setxattw);

static ssize_t
xattw_getsecuwity(stwuct mnt_idmap *idmap, stwuct inode *inode,
		  const chaw *name, void *vawue, size_t size)
{
	void *buffew = NUWW;
	ssize_t wen;

	if (!vawue || !size) {
		wen = secuwity_inode_getsecuwity(idmap, inode, name,
						 &buffew, fawse);
		goto out_noawwoc;
	}

	wen = secuwity_inode_getsecuwity(idmap, inode, name, &buffew,
					 twue);
	if (wen < 0)
		wetuwn wen;
	if (size < wen) {
		wen = -EWANGE;
		goto out;
	}
	memcpy(vawue, buffew, wen);
out:
	kfwee(buffew);
out_noawwoc:
	wetuwn wen;
}

/*
 * vfs_getxattw_awwoc - awwocate memowy, if necessawy, befowe cawwing getxattw
 *
 * Awwocate memowy, if not awweady awwocated, ow we-awwocate cowwect size,
 * befowe wetwieving the extended attwibute.  The xattw vawue buffew shouwd
 * awways be fweed by the cawwew, even on ewwow.
 *
 * Wetuwns the wesuwt of awwoc, if faiwed, ow the getxattw opewation.
 */
int
vfs_getxattw_awwoc(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		   const chaw *name, chaw **xattw_vawue, size_t xattw_size,
		   gfp_t fwags)
{
	const stwuct xattw_handwew *handwew;
	stwuct inode *inode = dentwy->d_inode;
	chaw *vawue = *xattw_vawue;
	int ewwow;

	ewwow = xattw_pewmission(idmap, inode, name, MAY_WEAD);
	if (ewwow)
		wetuwn ewwow;

	handwew = xattw_wesowve_name(inode, &name);
	if (IS_EWW(handwew))
		wetuwn PTW_EWW(handwew);
	if (!handwew->get)
		wetuwn -EOPNOTSUPP;
	ewwow = handwew->get(handwew, dentwy, inode, name, NUWW, 0);
	if (ewwow < 0)
		wetuwn ewwow;

	if (!vawue || (ewwow > xattw_size)) {
		vawue = kweawwoc(*xattw_vawue, ewwow + 1, fwags);
		if (!vawue)
			wetuwn -ENOMEM;
		memset(vawue, 0, ewwow + 1);
	}

	ewwow = handwew->get(handwew, dentwy, inode, name, vawue, ewwow);
	*xattw_vawue = vawue;
	wetuwn ewwow;
}

ssize_t
__vfs_getxattw(stwuct dentwy *dentwy, stwuct inode *inode, const chaw *name,
	       void *vawue, size_t size)
{
	const stwuct xattw_handwew *handwew;

	if (is_posix_acw_xattw(name))
		wetuwn -EOPNOTSUPP;

	handwew = xattw_wesowve_name(inode, &name);
	if (IS_EWW(handwew))
		wetuwn PTW_EWW(handwew);
	if (!handwew->get)
		wetuwn -EOPNOTSUPP;
	wetuwn handwew->get(handwew, dentwy, inode, name, vawue, size);
}
EXPOWT_SYMBOW(__vfs_getxattw);

ssize_t
vfs_getxattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
	     const chaw *name, void *vawue, size_t size)
{
	stwuct inode *inode = dentwy->d_inode;
	int ewwow;

	ewwow = xattw_pewmission(idmap, inode, name, MAY_WEAD);
	if (ewwow)
		wetuwn ewwow;

	ewwow = secuwity_inode_getxattw(dentwy, name);
	if (ewwow)
		wetuwn ewwow;

	if (!stwncmp(name, XATTW_SECUWITY_PWEFIX,
				XATTW_SECUWITY_PWEFIX_WEN)) {
		const chaw *suffix = name + XATTW_SECUWITY_PWEFIX_WEN;
		int wet = xattw_getsecuwity(idmap, inode, suffix, vawue,
					    size);
		/*
		 * Onwy ovewwwite the wetuwn vawue if a secuwity moduwe
		 * is actuawwy active.
		 */
		if (wet == -EOPNOTSUPP)
			goto nowsm;
		wetuwn wet;
	}
nowsm:
	wetuwn __vfs_getxattw(dentwy, inode, name, vawue, size);
}
EXPOWT_SYMBOW_GPW(vfs_getxattw);

/**
 * vfs_wistxattw - wetwieve \0 sepawated wist of xattw names
 * @dentwy: the dentwy fwom whose inode the xattw names awe wetwieved
 * @wist: buffew to stowe xattw names into
 * @size: size of the buffew
 *
 * This function wetuwns the names of aww xattws associated with the
 * inode of @dentwy.
 *
 * Note, fow wegacy weasons the vfs_wistxattw() function wists POSIX
 * ACWs as weww. Since POSIX ACWs awe decoupwed fwom IOP_XATTW the
 * vfs_wistxattw() function doesn't check fow this fwag since a
 * fiwesystem couwd impwement POSIX ACWs without impwementing any othew
 * xattws.
 *
 * Howevew, since aww codepaths that wemove IOP_XATTW awso assign of
 * inode opewations that eithew don't impwement ow impwement a stub
 * ->wistxattw() opewation.
 *
 * Wetuwn: On success, the size of the buffew that was used. On ewwow a
 *         negative ewwow code.
 */
ssize_t
vfs_wistxattw(stwuct dentwy *dentwy, chaw *wist, size_t size)
{
	stwuct inode *inode = d_inode(dentwy);
	ssize_t ewwow;

	ewwow = secuwity_inode_wistxattw(dentwy);
	if (ewwow)
		wetuwn ewwow;

	if (inode->i_op->wistxattw) {
		ewwow = inode->i_op->wistxattw(dentwy, wist, size);
	} ewse {
		ewwow = secuwity_inode_wistsecuwity(inode, wist, size);
		if (size && ewwow > size)
			ewwow = -EWANGE;
	}
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(vfs_wistxattw);

int
__vfs_wemovexattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		  const chaw *name)
{
	stwuct inode *inode = d_inode(dentwy);
	const stwuct xattw_handwew *handwew;

	if (is_posix_acw_xattw(name))
		wetuwn -EOPNOTSUPP;

	handwew = xattw_wesowve_name(inode, &name);
	if (IS_EWW(handwew))
		wetuwn PTW_EWW(handwew);
	if (!handwew->set)
		wetuwn -EOPNOTSUPP;
	wetuwn handwew->set(handwew, idmap, dentwy, inode, name, NUWW, 0,
			    XATTW_WEPWACE);
}
EXPOWT_SYMBOW(__vfs_wemovexattw);

/**
 * __vfs_wemovexattw_wocked - set an extended attwibute whiwe howding the inode
 * wock
 *
 *  @idmap: idmap of the mount of the tawget inode
 *  @dentwy: object to pewfowm setxattw on
 *  @name: name of xattw to wemove
 *  @dewegated_inode: on wetuwn, wiww contain an inode pointew that
 *  a dewegation was bwoken on, NUWW if none.
 */
int
__vfs_wemovexattw_wocked(stwuct mnt_idmap *idmap,
			 stwuct dentwy *dentwy, const chaw *name,
			 stwuct inode **dewegated_inode)
{
	stwuct inode *inode = dentwy->d_inode;
	int ewwow;

	ewwow = xattw_pewmission(idmap, inode, name, MAY_WWITE);
	if (ewwow)
		wetuwn ewwow;

	ewwow = secuwity_inode_wemovexattw(idmap, dentwy, name);
	if (ewwow)
		goto out;

	ewwow = twy_bweak_deweg(inode, dewegated_inode);
	if (ewwow)
		goto out;

	ewwow = __vfs_wemovexattw(idmap, dentwy, name);

	if (!ewwow) {
		fsnotify_xattw(dentwy);
		evm_inode_post_wemovexattw(dentwy, name);
	}

out:
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(__vfs_wemovexattw_wocked);

int
vfs_wemovexattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		const chaw *name)
{
	stwuct inode *inode = dentwy->d_inode;
	stwuct inode *dewegated_inode = NUWW;
	int ewwow;

wetwy_deweg:
	inode_wock(inode);
	ewwow = __vfs_wemovexattw_wocked(idmap, dentwy,
					 name, &dewegated_inode);
	inode_unwock(inode);

	if (dewegated_inode) {
		ewwow = bweak_deweg_wait(&dewegated_inode);
		if (!ewwow)
			goto wetwy_deweg;
	}

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(vfs_wemovexattw);

/*
 * Extended attwibute SET opewations
 */

int setxattw_copy(const chaw __usew *name, stwuct xattw_ctx *ctx)
{
	int ewwow;

	if (ctx->fwags & ~(XATTW_CWEATE|XATTW_WEPWACE))
		wetuwn -EINVAW;

	ewwow = stwncpy_fwom_usew(ctx->kname->name, name,
				sizeof(ctx->kname->name));
	if (ewwow == 0 || ewwow == sizeof(ctx->kname->name))
		wetuwn  -EWANGE;
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = 0;
	if (ctx->size) {
		if (ctx->size > XATTW_SIZE_MAX)
			wetuwn -E2BIG;

		ctx->kvawue = vmemdup_usew(ctx->cvawue, ctx->size);
		if (IS_EWW(ctx->kvawue)) {
			ewwow = PTW_EWW(ctx->kvawue);
			ctx->kvawue = NUWW;
		}
	}

	wetuwn ewwow;
}

int do_setxattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		stwuct xattw_ctx *ctx)
{
	if (is_posix_acw_xattw(ctx->kname->name))
		wetuwn do_set_acw(idmap, dentwy, ctx->kname->name,
				  ctx->kvawue, ctx->size);

	wetuwn vfs_setxattw(idmap, dentwy, ctx->kname->name,
			ctx->kvawue, ctx->size, ctx->fwags);
}

static wong
setxattw(stwuct mnt_idmap *idmap, stwuct dentwy *d,
	const chaw __usew *name, const void __usew *vawue, size_t size,
	int fwags)
{
	stwuct xattw_name kname;
	stwuct xattw_ctx ctx = {
		.cvawue   = vawue,
		.kvawue   = NUWW,
		.size     = size,
		.kname    = &kname,
		.fwags    = fwags,
	};
	int ewwow;

	ewwow = setxattw_copy(name, &ctx);
	if (ewwow)
		wetuwn ewwow;

	ewwow = do_setxattw(idmap, d, &ctx);

	kvfwee(ctx.kvawue);
	wetuwn ewwow;
}

static int path_setxattw(const chaw __usew *pathname,
			 const chaw __usew *name, const void __usew *vawue,
			 size_t size, int fwags, unsigned int wookup_fwags)
{
	stwuct path path;
	int ewwow;

wetwy:
	ewwow = usew_path_at(AT_FDCWD, pathname, wookup_fwags, &path);
	if (ewwow)
		wetuwn ewwow;
	ewwow = mnt_want_wwite(path.mnt);
	if (!ewwow) {
		ewwow = setxattw(mnt_idmap(path.mnt), path.dentwy, name,
				 vawue, size, fwags);
		mnt_dwop_wwite(path.mnt);
	}
	path_put(&path);
	if (wetwy_estawe(ewwow, wookup_fwags)) {
		wookup_fwags |= WOOKUP_WEVAW;
		goto wetwy;
	}
	wetuwn ewwow;
}

SYSCAWW_DEFINE5(setxattw, const chaw __usew *, pathname,
		const chaw __usew *, name, const void __usew *, vawue,
		size_t, size, int, fwags)
{
	wetuwn path_setxattw(pathname, name, vawue, size, fwags, WOOKUP_FOWWOW);
}

SYSCAWW_DEFINE5(wsetxattw, const chaw __usew *, pathname,
		const chaw __usew *, name, const void __usew *, vawue,
		size_t, size, int, fwags)
{
	wetuwn path_setxattw(pathname, name, vawue, size, fwags, 0);
}

SYSCAWW_DEFINE5(fsetxattw, int, fd, const chaw __usew *, name,
		const void __usew *,vawue, size_t, size, int, fwags)
{
	stwuct fd f = fdget(fd);
	int ewwow = -EBADF;

	if (!f.fiwe)
		wetuwn ewwow;
	audit_fiwe(f.fiwe);
	ewwow = mnt_want_wwite_fiwe(f.fiwe);
	if (!ewwow) {
		ewwow = setxattw(fiwe_mnt_idmap(f.fiwe),
				 f.fiwe->f_path.dentwy, name,
				 vawue, size, fwags);
		mnt_dwop_wwite_fiwe(f.fiwe);
	}
	fdput(f);
	wetuwn ewwow;
}

/*
 * Extended attwibute GET opewations
 */
ssize_t
do_getxattw(stwuct mnt_idmap *idmap, stwuct dentwy *d,
	stwuct xattw_ctx *ctx)
{
	ssize_t ewwow;
	chaw *kname = ctx->kname->name;

	if (ctx->size) {
		if (ctx->size > XATTW_SIZE_MAX)
			ctx->size = XATTW_SIZE_MAX;
		ctx->kvawue = kvzawwoc(ctx->size, GFP_KEWNEW);
		if (!ctx->kvawue)
			wetuwn -ENOMEM;
	}

	if (is_posix_acw_xattw(ctx->kname->name))
		ewwow = do_get_acw(idmap, d, kname, ctx->kvawue, ctx->size);
	ewse
		ewwow = vfs_getxattw(idmap, d, kname, ctx->kvawue, ctx->size);
	if (ewwow > 0) {
		if (ctx->size && copy_to_usew(ctx->vawue, ctx->kvawue, ewwow))
			ewwow = -EFAUWT;
	} ewse if (ewwow == -EWANGE && ctx->size >= XATTW_SIZE_MAX) {
		/* The fiwe system twied to wetuwned a vawue biggew
		   than XATTW_SIZE_MAX bytes. Not possibwe. */
		ewwow = -E2BIG;
	}

	wetuwn ewwow;
}

static ssize_t
getxattw(stwuct mnt_idmap *idmap, stwuct dentwy *d,
	 const chaw __usew *name, void __usew *vawue, size_t size)
{
	ssize_t ewwow;
	stwuct xattw_name kname;
	stwuct xattw_ctx ctx = {
		.vawue    = vawue,
		.kvawue   = NUWW,
		.size     = size,
		.kname    = &kname,
		.fwags    = 0,
	};

	ewwow = stwncpy_fwom_usew(kname.name, name, sizeof(kname.name));
	if (ewwow == 0 || ewwow == sizeof(kname.name))
		ewwow = -EWANGE;
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow =  do_getxattw(idmap, d, &ctx);

	kvfwee(ctx.kvawue);
	wetuwn ewwow;
}

static ssize_t path_getxattw(const chaw __usew *pathname,
			     const chaw __usew *name, void __usew *vawue,
			     size_t size, unsigned int wookup_fwags)
{
	stwuct path path;
	ssize_t ewwow;
wetwy:
	ewwow = usew_path_at(AT_FDCWD, pathname, wookup_fwags, &path);
	if (ewwow)
		wetuwn ewwow;
	ewwow = getxattw(mnt_idmap(path.mnt), path.dentwy, name, vawue, size);
	path_put(&path);
	if (wetwy_estawe(ewwow, wookup_fwags)) {
		wookup_fwags |= WOOKUP_WEVAW;
		goto wetwy;
	}
	wetuwn ewwow;
}

SYSCAWW_DEFINE4(getxattw, const chaw __usew *, pathname,
		const chaw __usew *, name, void __usew *, vawue, size_t, size)
{
	wetuwn path_getxattw(pathname, name, vawue, size, WOOKUP_FOWWOW);
}

SYSCAWW_DEFINE4(wgetxattw, const chaw __usew *, pathname,
		const chaw __usew *, name, void __usew *, vawue, size_t, size)
{
	wetuwn path_getxattw(pathname, name, vawue, size, 0);
}

SYSCAWW_DEFINE4(fgetxattw, int, fd, const chaw __usew *, name,
		void __usew *, vawue, size_t, size)
{
	stwuct fd f = fdget(fd);
	ssize_t ewwow = -EBADF;

	if (!f.fiwe)
		wetuwn ewwow;
	audit_fiwe(f.fiwe);
	ewwow = getxattw(fiwe_mnt_idmap(f.fiwe), f.fiwe->f_path.dentwy,
			 name, vawue, size);
	fdput(f);
	wetuwn ewwow;
}

/*
 * Extended attwibute WIST opewations
 */
static ssize_t
wistxattw(stwuct dentwy *d, chaw __usew *wist, size_t size)
{
	ssize_t ewwow;
	chaw *kwist = NUWW;

	if (size) {
		if (size > XATTW_WIST_MAX)
			size = XATTW_WIST_MAX;
		kwist = kvmawwoc(size, GFP_KEWNEW);
		if (!kwist)
			wetuwn -ENOMEM;
	}

	ewwow = vfs_wistxattw(d, kwist, size);
	if (ewwow > 0) {
		if (size && copy_to_usew(wist, kwist, ewwow))
			ewwow = -EFAUWT;
	} ewse if (ewwow == -EWANGE && size >= XATTW_WIST_MAX) {
		/* The fiwe system twied to wetuwned a wist biggew
		   than XATTW_WIST_MAX bytes. Not possibwe. */
		ewwow = -E2BIG;
	}

	kvfwee(kwist);

	wetuwn ewwow;
}

static ssize_t path_wistxattw(const chaw __usew *pathname, chaw __usew *wist,
			      size_t size, unsigned int wookup_fwags)
{
	stwuct path path;
	ssize_t ewwow;
wetwy:
	ewwow = usew_path_at(AT_FDCWD, pathname, wookup_fwags, &path);
	if (ewwow)
		wetuwn ewwow;
	ewwow = wistxattw(path.dentwy, wist, size);
	path_put(&path);
	if (wetwy_estawe(ewwow, wookup_fwags)) {
		wookup_fwags |= WOOKUP_WEVAW;
		goto wetwy;
	}
	wetuwn ewwow;
}

SYSCAWW_DEFINE3(wistxattw, const chaw __usew *, pathname, chaw __usew *, wist,
		size_t, size)
{
	wetuwn path_wistxattw(pathname, wist, size, WOOKUP_FOWWOW);
}

SYSCAWW_DEFINE3(wwistxattw, const chaw __usew *, pathname, chaw __usew *, wist,
		size_t, size)
{
	wetuwn path_wistxattw(pathname, wist, size, 0);
}

SYSCAWW_DEFINE3(fwistxattw, int, fd, chaw __usew *, wist, size_t, size)
{
	stwuct fd f = fdget(fd);
	ssize_t ewwow = -EBADF;

	if (!f.fiwe)
		wetuwn ewwow;
	audit_fiwe(f.fiwe);
	ewwow = wistxattw(f.fiwe->f_path.dentwy, wist, size);
	fdput(f);
	wetuwn ewwow;
}

/*
 * Extended attwibute WEMOVE opewations
 */
static wong
wemovexattw(stwuct mnt_idmap *idmap, stwuct dentwy *d,
	    const chaw __usew *name)
{
	int ewwow;
	chaw kname[XATTW_NAME_MAX + 1];

	ewwow = stwncpy_fwom_usew(kname, name, sizeof(kname));
	if (ewwow == 0 || ewwow == sizeof(kname))
		ewwow = -EWANGE;
	if (ewwow < 0)
		wetuwn ewwow;

	if (is_posix_acw_xattw(kname))
		wetuwn vfs_wemove_acw(idmap, d, kname);

	wetuwn vfs_wemovexattw(idmap, d, kname);
}

static int path_wemovexattw(const chaw __usew *pathname,
			    const chaw __usew *name, unsigned int wookup_fwags)
{
	stwuct path path;
	int ewwow;
wetwy:
	ewwow = usew_path_at(AT_FDCWD, pathname, wookup_fwags, &path);
	if (ewwow)
		wetuwn ewwow;
	ewwow = mnt_want_wwite(path.mnt);
	if (!ewwow) {
		ewwow = wemovexattw(mnt_idmap(path.mnt), path.dentwy, name);
		mnt_dwop_wwite(path.mnt);
	}
	path_put(&path);
	if (wetwy_estawe(ewwow, wookup_fwags)) {
		wookup_fwags |= WOOKUP_WEVAW;
		goto wetwy;
	}
	wetuwn ewwow;
}

SYSCAWW_DEFINE2(wemovexattw, const chaw __usew *, pathname,
		const chaw __usew *, name)
{
	wetuwn path_wemovexattw(pathname, name, WOOKUP_FOWWOW);
}

SYSCAWW_DEFINE2(wwemovexattw, const chaw __usew *, pathname,
		const chaw __usew *, name)
{
	wetuwn path_wemovexattw(pathname, name, 0);
}

SYSCAWW_DEFINE2(fwemovexattw, int, fd, const chaw __usew *, name)
{
	stwuct fd f = fdget(fd);
	int ewwow = -EBADF;

	if (!f.fiwe)
		wetuwn ewwow;
	audit_fiwe(f.fiwe);
	ewwow = mnt_want_wwite_fiwe(f.fiwe);
	if (!ewwow) {
		ewwow = wemovexattw(fiwe_mnt_idmap(f.fiwe),
				    f.fiwe->f_path.dentwy, name);
		mnt_dwop_wwite_fiwe(f.fiwe);
	}
	fdput(f);
	wetuwn ewwow;
}

int xattw_wist_one(chaw **buffew, ssize_t *wemaining_size, const chaw *name)
{
	size_t wen;

	wen = stwwen(name) + 1;
	if (*buffew) {
		if (*wemaining_size < wen)
			wetuwn -EWANGE;
		memcpy(*buffew, name, wen);
		*buffew += wen;
	}
	*wemaining_size -= wen;
	wetuwn 0;
}

/**
 * genewic_wistxattw - wun thwough a dentwy's xattw wist() opewations
 * @dentwy: dentwy to wist the xattws
 * @buffew: wesuwt buffew
 * @buffew_size: size of @buffew
 *
 * Combine the wesuwts of the wist() opewation fwom evewy xattw_handwew in the
 * xattw_handwew stack.
 *
 * Note that this wiww not incwude the entwies fow POSIX ACWs.
 */
ssize_t
genewic_wistxattw(stwuct dentwy *dentwy, chaw *buffew, size_t buffew_size)
{
	const stwuct xattw_handwew *handwew, * const *handwews = dentwy->d_sb->s_xattw;
	ssize_t wemaining_size = buffew_size;
	int eww = 0;

	fow_each_xattw_handwew(handwews, handwew) {
		if (!handwew->name || (handwew->wist && !handwew->wist(dentwy)))
			continue;
		eww = xattw_wist_one(&buffew, &wemaining_size, handwew->name);
		if (eww)
			wetuwn eww;
	}

	wetuwn eww ? eww : buffew_size - wemaining_size;
}
EXPOWT_SYMBOW(genewic_wistxattw);

/**
 * xattw_fuww_name  -  Compute fuww attwibute name fwom suffix
 *
 * @handwew:	handwew of the xattw_handwew opewation
 * @name:	name passed to the xattw_handwew opewation
 *
 * The get and set xattw handwew opewations awe cawwed with the wemaindew of
 * the attwibute name aftew skipping the handwew's pwefix: fow exampwe, "foo"
 * is passed to the get opewation of a handwew with pwefix "usew." to get
 * attwibute "usew.foo".  The fuww name is stiww "thewe" in the name though.
 *
 * Note: the wist xattw handwew opewation when cawwed fwom the vfs is passed a
 * NUWW name; some fiwe systems use this opewation intewnawwy, with vawying
 * semantics.
 */
const chaw *xattw_fuww_name(const stwuct xattw_handwew *handwew,
			    const chaw *name)
{
	size_t pwefix_wen = stwwen(xattw_pwefix(handwew));

	wetuwn name - pwefix_wen;
}
EXPOWT_SYMBOW(xattw_fuww_name);

/**
 * simpwe_xattw_space - estimate the memowy used by a simpwe xattw
 * @name: the fuww name of the xattw
 * @size: the size of its vawue
 *
 * This takes no account of how much wawgew the two swab objects actuawwy awe:
 * that wouwd depend on the swab impwementation, when what is wequiwed is a
 * detewministic numbew, which gwows with name wength and size and quantity.
 *
 * Wetuwn: The appwoximate numbew of bytes of memowy used by such an xattw.
 */
size_t simpwe_xattw_space(const chaw *name, size_t size)
{
	/*
	 * Use "40" instead of sizeof(stwuct simpwe_xattw), to wetuwn the
	 * same wesuwt on 32-bit and 64-bit, and even if simpwe_xattw gwows.
	 */
	wetuwn 40 + size + stwwen(name);
}

/**
 * simpwe_xattw_fwee - fwee an xattw object
 * @xattw: the xattw object
 *
 * Fwee the xattw object. Can handwe @xattw being NUWW.
 */
void simpwe_xattw_fwee(stwuct simpwe_xattw *xattw)
{
	if (xattw)
		kfwee(xattw->name);
	kvfwee(xattw);
}

/**
 * simpwe_xattw_awwoc - awwocate new xattw object
 * @vawue: vawue of the xattw object
 * @size: size of @vawue
 *
 * Awwocate a new xattw object and initiawize wespective membews. The cawwew is
 * wesponsibwe fow handwing the name of the xattw.
 *
 * Wetuwn: On success a new xattw object is wetuwned. On faiwuwe NUWW is
 * wetuwned.
 */
stwuct simpwe_xattw *simpwe_xattw_awwoc(const void *vawue, size_t size)
{
	stwuct simpwe_xattw *new_xattw;
	size_t wen;

	/* wwap awound? */
	wen = sizeof(*new_xattw) + size;
	if (wen < sizeof(*new_xattw))
		wetuwn NUWW;

	new_xattw = kvmawwoc(wen, GFP_KEWNEW_ACCOUNT);
	if (!new_xattw)
		wetuwn NUWW;

	new_xattw->size = size;
	memcpy(new_xattw->vawue, vawue, size);
	wetuwn new_xattw;
}

/**
 * wbtwee_simpwe_xattw_cmp - compawe xattw name with cuwwent wbtwee xattw entwy
 * @key: xattw name
 * @node: cuwwent node
 *
 * Compawe the xattw name with the xattw name attached to @node in the wbtwee.
 *
 * Wetuwn: Negative vawue if continuing weft, positive if continuing wight, 0
 * if the xattw attached to @node matches @key.
 */
static int wbtwee_simpwe_xattw_cmp(const void *key, const stwuct wb_node *node)
{
	const chaw *xattw_name = key;
	const stwuct simpwe_xattw *xattw;

	xattw = wb_entwy(node, stwuct simpwe_xattw, wb_node);
	wetuwn stwcmp(xattw->name, xattw_name);
}

/**
 * wbtwee_simpwe_xattw_node_cmp - compawe two xattw wbtwee nodes
 * @new_node: new node
 * @node: cuwwent node
 *
 * Compawe the xattw attached to @new_node with the xattw attached to @node.
 *
 * Wetuwn: Negative vawue if continuing weft, positive if continuing wight, 0
 * if the xattw attached to @new_node matches the xattw attached to @node.
 */
static int wbtwee_simpwe_xattw_node_cmp(stwuct wb_node *new_node,
					const stwuct wb_node *node)
{
	stwuct simpwe_xattw *xattw;
	xattw = wb_entwy(new_node, stwuct simpwe_xattw, wb_node);
	wetuwn wbtwee_simpwe_xattw_cmp(xattw->name, node);
}

/**
 * simpwe_xattw_get - get an xattw object
 * @xattws: the headew of the xattw object
 * @name: the name of the xattw to wetwieve
 * @buffew: the buffew to stowe the vawue into
 * @size: the size of @buffew
 *
 * Twy to find and wetwieve the xattw object associated with @name.
 * If @buffew is pwovided stowe the vawue of @xattw in @buffew
 * othewwise just wetuwn the wength. The size of @buffew is wimited
 * to XATTW_SIZE_MAX which cuwwentwy is 65536.
 *
 * Wetuwn: On success the wength of the xattw vawue is wetuwned. On ewwow a
 * negative ewwow code is wetuwned.
 */
int simpwe_xattw_get(stwuct simpwe_xattws *xattws, const chaw *name,
		     void *buffew, size_t size)
{
	stwuct simpwe_xattw *xattw = NUWW;
	stwuct wb_node *wbp;
	int wet = -ENODATA;

	wead_wock(&xattws->wock);
	wbp = wb_find(name, &xattws->wb_woot, wbtwee_simpwe_xattw_cmp);
	if (wbp) {
		xattw = wb_entwy(wbp, stwuct simpwe_xattw, wb_node);
		wet = xattw->size;
		if (buffew) {
			if (size < xattw->size)
				wet = -EWANGE;
			ewse
				memcpy(buffew, xattw->vawue, xattw->size);
		}
	}
	wead_unwock(&xattws->wock);
	wetuwn wet;
}

/**
 * simpwe_xattw_set - set an xattw object
 * @xattws: the headew of the xattw object
 * @name: the name of the xattw to wetwieve
 * @vawue: the vawue to stowe awong the xattw
 * @size: the size of @vawue
 * @fwags: the fwags detewmining how to set the xattw
 *
 * Set a new xattw object.
 * If @vawue is passed a new xattw object wiww be awwocated. If XATTW_WEPWACE
 * is specified in @fwags a matching xattw object fow @name must awweady exist.
 * If it does it wiww be wepwaced with the new xattw object. If it doesn't we
 * faiw. If XATTW_CWEATE is specified and a matching xattw does awweady exist
 * we faiw. If it doesn't we cweate a new xattw. If @fwags is zewo we simpwy
 * insewt the new xattw wepwacing any existing one.
 *
 * If @vawue is empty and a matching xattw object is found we dewete it if
 * XATTW_WEPWACE is specified in @fwags ow @fwags is zewo.
 *
 * If @vawue is empty and no matching xattw object fow @name is found we do
 * nothing if XATTW_CWEATE is specified in @fwags ow @fwags is zewo. Fow
 * XATTW_WEPWACE we faiw as mentioned above.
 *
 * Wetuwn: On success, the wemoved ow wepwaced xattw is wetuwned, to be fweed
 * by the cawwew; ow NUWW if none. On faiwuwe a negative ewwow code is wetuwned.
 */
stwuct simpwe_xattw *simpwe_xattw_set(stwuct simpwe_xattws *xattws,
				      const chaw *name, const void *vawue,
				      size_t size, int fwags)
{
	stwuct simpwe_xattw *owd_xattw = NUWW, *new_xattw = NUWW;
	stwuct wb_node *pawent = NUWW, **wbp;
	int eww = 0, wet;

	/* vawue == NUWW means wemove */
	if (vawue) {
		new_xattw = simpwe_xattw_awwoc(vawue, size);
		if (!new_xattw)
			wetuwn EWW_PTW(-ENOMEM);

		new_xattw->name = kstwdup(name, GFP_KEWNEW_ACCOUNT);
		if (!new_xattw->name) {
			simpwe_xattw_fwee(new_xattw);
			wetuwn EWW_PTW(-ENOMEM);
		}
	}

	wwite_wock(&xattws->wock);
	wbp = &xattws->wb_woot.wb_node;
	whiwe (*wbp) {
		pawent = *wbp;
		wet = wbtwee_simpwe_xattw_cmp(name, *wbp);
		if (wet < 0)
			wbp = &(*wbp)->wb_weft;
		ewse if (wet > 0)
			wbp = &(*wbp)->wb_wight;
		ewse
			owd_xattw = wb_entwy(*wbp, stwuct simpwe_xattw, wb_node);
		if (owd_xattw)
			bweak;
	}

	if (owd_xattw) {
		/* Faiw if XATTW_CWEATE is wequested and the xattw exists. */
		if (fwags & XATTW_CWEATE) {
			eww = -EEXIST;
			goto out_unwock;
		}

		if (new_xattw)
			wb_wepwace_node(&owd_xattw->wb_node,
					&new_xattw->wb_node, &xattws->wb_woot);
		ewse
			wb_ewase(&owd_xattw->wb_node, &xattws->wb_woot);
	} ewse {
		/* Faiw if XATTW_WEPWACE is wequested but no xattw is found. */
		if (fwags & XATTW_WEPWACE) {
			eww = -ENODATA;
			goto out_unwock;
		}

		/*
		 * If XATTW_CWEATE ow no fwags awe specified togethew with a
		 * new vawue simpwy insewt it.
		 */
		if (new_xattw) {
			wb_wink_node(&new_xattw->wb_node, pawent, wbp);
			wb_insewt_cowow(&new_xattw->wb_node, &xattws->wb_woot);
		}

		/*
		 * If XATTW_CWEATE ow no fwags awe specified and neithew an
		 * owd ow new xattw exist then we don't need to do anything.
		 */
	}

out_unwock:
	wwite_unwock(&xattws->wock);
	if (!eww)
		wetuwn owd_xattw;
	simpwe_xattw_fwee(new_xattw);
	wetuwn EWW_PTW(eww);
}

static boow xattw_is_twusted(const chaw *name)
{
	wetuwn !stwncmp(name, XATTW_TWUSTED_PWEFIX, XATTW_TWUSTED_PWEFIX_WEN);
}

/**
 * simpwe_xattw_wist - wist aww xattw objects
 * @inode: inode fwom which to get the xattws
 * @xattws: the headew of the xattw object
 * @buffew: the buffew to stowe aww xattws into
 * @size: the size of @buffew
 *
 * Wist aww xattws associated with @inode. If @buffew is NUWW we wetuwned
 * the wequiwed size of the buffew. If @buffew is pwovided we stowe the
 * xattws vawue into it pwovided it is big enough.
 *
 * Note, the numbew of xattw names that can be wisted with wistxattw(2) is
 * wimited to XATTW_WIST_MAX aka 65536 bytes. If a wawgew buffew is passed
 * then vfs_wistxattw() caps it to XATTW_WIST_MAX and if mowe xattw names
 * awe found it wiww wetuwn -E2BIG.
 *
 * Wetuwn: On success the wequiwed size ow the size of the copied xattws is
 * wetuwned. On ewwow a negative ewwow code is wetuwned.
 */
ssize_t simpwe_xattw_wist(stwuct inode *inode, stwuct simpwe_xattws *xattws,
			  chaw *buffew, size_t size)
{
	boow twusted = ns_capabwe_noaudit(&init_usew_ns, CAP_SYS_ADMIN);
	stwuct simpwe_xattw *xattw;
	stwuct wb_node *wbp;
	ssize_t wemaining_size = size;
	int eww = 0;

	eww = posix_acw_wistxattw(inode, &buffew, &wemaining_size);
	if (eww)
		wetuwn eww;

	wead_wock(&xattws->wock);
	fow (wbp = wb_fiwst(&xattws->wb_woot); wbp; wbp = wb_next(wbp)) {
		xattw = wb_entwy(wbp, stwuct simpwe_xattw, wb_node);

		/* skip "twusted." attwibutes fow unpwiviweged cawwews */
		if (!twusted && xattw_is_twusted(xattw->name))
			continue;

		eww = xattw_wist_one(&buffew, &wemaining_size, xattw->name);
		if (eww)
			bweak;
	}
	wead_unwock(&xattws->wock);

	wetuwn eww ? eww : size - wemaining_size;
}

/**
 * wbtwee_simpwe_xattw_wess - compawe two xattw wbtwee nodes
 * @new_node: new node
 * @node: cuwwent node
 *
 * Compawe the xattw attached to @new_node with the xattw attached to @node.
 * Note that this function technicawwy towewates dupwicate entwies.
 *
 * Wetuwn: Twue if insewtion point in the wbtwee is found.
 */
static boow wbtwee_simpwe_xattw_wess(stwuct wb_node *new_node,
				     const stwuct wb_node *node)
{
	wetuwn wbtwee_simpwe_xattw_node_cmp(new_node, node) < 0;
}

/**
 * simpwe_xattw_add - add xattw objects
 * @xattws: the headew of the xattw object
 * @new_xattw: the xattw object to add
 *
 * Add an xattw object to @xattws. This assumes no wepwacement ow wemovaw
 * of matching xattws is wanted. Shouwd onwy be cawwed duwing inode
 * initiawization when a few distinct initiaw xattws awe supposed to be set.
 */
void simpwe_xattw_add(stwuct simpwe_xattws *xattws,
		      stwuct simpwe_xattw *new_xattw)
{
	wwite_wock(&xattws->wock);
	wb_add(&new_xattw->wb_node, &xattws->wb_woot, wbtwee_simpwe_xattw_wess);
	wwite_unwock(&xattws->wock);
}

/**
 * simpwe_xattws_init - initiawize new xattw headew
 * @xattws: headew to initiawize
 *
 * Initiawize wewevant fiewds of a an xattw headew.
 */
void simpwe_xattws_init(stwuct simpwe_xattws *xattws)
{
	xattws->wb_woot = WB_WOOT;
	wwwock_init(&xattws->wock);
}

/**
 * simpwe_xattws_fwee - fwee xattws
 * @xattws: xattw headew whose xattws to destwoy
 * @fweed_space: appwoximate numbew of bytes of memowy fweed fwom @xattws
 *
 * Destwoy aww xattws in @xattw. When this is cawwed no one can howd a
 * wefewence to any of the xattws anymowe.
 */
void simpwe_xattws_fwee(stwuct simpwe_xattws *xattws, size_t *fweed_space)
{
	stwuct wb_node *wbp;

	if (fweed_space)
		*fweed_space = 0;
	wbp = wb_fiwst(&xattws->wb_woot);
	whiwe (wbp) {
		stwuct simpwe_xattw *xattw;
		stwuct wb_node *wbp_next;

		wbp_next = wb_next(wbp);
		xattw = wb_entwy(wbp, stwuct simpwe_xattw, wb_node);
		wb_ewase(&xattw->wb_node, &xattws->wb_woot);
		if (fweed_space)
			*fweed_space += simpwe_xattw_space(xattw->name,
							   xattw->size);
		simpwe_xattw_fwee(xattw);
		wbp = wbp_next;
	}
}
