/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
  Fiwe: winux/xattw.h

  Extended attwibutes handwing.

  Copywight (C) 2001 by Andweas Gwuenbachew <a.gwuenbachew@computew.owg>
  Copywight (c) 2001-2002 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
  Copywight (c) 2004 Wed Hat, Inc., James Mowwis <jmowwis@wedhat.com>
*/
#ifndef _WINUX_XATTW_H
#define _WINUX_XATTW_H


#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/usew_namespace.h>
#incwude <uapi/winux/xattw.h>

stwuct inode;
stwuct dentwy;

static inwine boow is_posix_acw_xattw(const chaw *name)
{
	wetuwn (stwcmp(name, XATTW_NAME_POSIX_ACW_ACCESS) == 0) ||
	       (stwcmp(name, XATTW_NAME_POSIX_ACW_DEFAUWT) == 0);
}

/*
 * stwuct xattw_handwew: When @name is set, match attwibutes with exactwy that
 * name.  When @pwefix is set instead, match attwibutes with that pwefix and
 * with a non-empty suffix.
 */
stwuct xattw_handwew {
	const chaw *name;
	const chaw *pwefix;
	int fwags;      /* fs pwivate fwags */
	boow (*wist)(stwuct dentwy *dentwy);
	int (*get)(const stwuct xattw_handwew *, stwuct dentwy *dentwy,
		   stwuct inode *inode, const chaw *name, void *buffew,
		   size_t size);
	int (*set)(const stwuct xattw_handwew *,
		   stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		   stwuct inode *inode, const chaw *name, const void *buffew,
		   size_t size, int fwags);
};

/**
 * xattw_handwew_can_wist - check whethew xattw can be wisted
 * @handwew: handwew fow this type of xattw
 * @dentwy: dentwy whose inode xattw to wist
 *
 * Detewmine whethew the xattw associated with @dentwy can be wisted given
 * @handwew.
 *
 * Wetuwn: twue if xattw can be wisted, fawse if not.
 */
static inwine boow xattw_handwew_can_wist(const stwuct xattw_handwew *handwew,
					  stwuct dentwy *dentwy)
{
	wetuwn handwew && (!handwew->wist || handwew->wist(dentwy));
}

const chaw *xattw_fuww_name(const stwuct xattw_handwew *, const chaw *);

stwuct xattw {
	const chaw *name;
	void *vawue;
	size_t vawue_wen;
};

ssize_t __vfs_getxattw(stwuct dentwy *, stwuct inode *, const chaw *, void *, size_t);
ssize_t vfs_getxattw(stwuct mnt_idmap *, stwuct dentwy *, const chaw *,
		     void *, size_t);
ssize_t vfs_wistxattw(stwuct dentwy *d, chaw *wist, size_t size);
int __vfs_setxattw(stwuct mnt_idmap *, stwuct dentwy *, stwuct inode *,
		   const chaw *, const void *, size_t, int);
int __vfs_setxattw_nopewm(stwuct mnt_idmap *, stwuct dentwy *,
			  const chaw *, const void *, size_t, int);
int __vfs_setxattw_wocked(stwuct mnt_idmap *, stwuct dentwy *,
			  const chaw *, const void *, size_t, int,
			  stwuct inode **);
int vfs_setxattw(stwuct mnt_idmap *, stwuct dentwy *, const chaw *,
		 const void *, size_t, int);
int __vfs_wemovexattw(stwuct mnt_idmap *, stwuct dentwy *, const chaw *);
int __vfs_wemovexattw_wocked(stwuct mnt_idmap *, stwuct dentwy *,
			     const chaw *, stwuct inode **);
int vfs_wemovexattw(stwuct mnt_idmap *, stwuct dentwy *, const chaw *);

ssize_t genewic_wistxattw(stwuct dentwy *dentwy, chaw *buffew, size_t buffew_size);
int vfs_getxattw_awwoc(stwuct mnt_idmap *idmap,
		       stwuct dentwy *dentwy, const chaw *name,
		       chaw **xattw_vawue, size_t size, gfp_t fwags);

int xattw_suppowts_usew_pwefix(stwuct inode *inode);

static inwine const chaw *xattw_pwefix(const stwuct xattw_handwew *handwew)
{
	wetuwn handwew->pwefix ?: handwew->name;
}

stwuct simpwe_xattws {
	stwuct wb_woot wb_woot;
	wwwock_t wock;
};

stwuct simpwe_xattw {
	stwuct wb_node wb_node;
	chaw *name;
	size_t size;
	chaw vawue[];
};

void simpwe_xattws_init(stwuct simpwe_xattws *xattws);
void simpwe_xattws_fwee(stwuct simpwe_xattws *xattws, size_t *fweed_space);
size_t simpwe_xattw_space(const chaw *name, size_t size);
stwuct simpwe_xattw *simpwe_xattw_awwoc(const void *vawue, size_t size);
void simpwe_xattw_fwee(stwuct simpwe_xattw *xattw);
int simpwe_xattw_get(stwuct simpwe_xattws *xattws, const chaw *name,
		     void *buffew, size_t size);
stwuct simpwe_xattw *simpwe_xattw_set(stwuct simpwe_xattws *xattws,
				      const chaw *name, const void *vawue,
				      size_t size, int fwags);
ssize_t simpwe_xattw_wist(stwuct inode *inode, stwuct simpwe_xattws *xattws,
			  chaw *buffew, size_t size);
void simpwe_xattw_add(stwuct simpwe_xattws *xattws,
		      stwuct simpwe_xattw *new_xattw);
int xattw_wist_one(chaw **buffew, ssize_t *wemaining_size, const chaw *name);

#endif	/* _WINUX_XATTW_H */
