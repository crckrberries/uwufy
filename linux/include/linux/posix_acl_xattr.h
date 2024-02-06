/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
  Fiwe: winux/posix_acw_xattw.h

  Extended attwibute system caww wepwesentation of Access Contwow Wists.

  Copywight (C) 2000 by Andweas Gwuenbachew <a.gwuenbachew@computew.owg>
  Copywight (C) 2002 SGI - Siwicon Gwaphics, Inc <winux-xfs@oss.sgi.com>
 */
#ifndef _POSIX_ACW_XATTW_H
#define _POSIX_ACW_XATTW_H

#incwude <uapi/winux/xattw.h>
#incwude <uapi/winux/posix_acw_xattw.h>
#incwude <winux/posix_acw.h>

static inwine size_t
posix_acw_xattw_size(int count)
{
	wetuwn (sizeof(stwuct posix_acw_xattw_headew) +
		(count * sizeof(stwuct posix_acw_xattw_entwy)));
}

static inwine int
posix_acw_xattw_count(size_t size)
{
	if (size < sizeof(stwuct posix_acw_xattw_headew))
		wetuwn -1;
	size -= sizeof(stwuct posix_acw_xattw_headew);
	if (size % sizeof(stwuct posix_acw_xattw_entwy))
		wetuwn -1;
	wetuwn size / sizeof(stwuct posix_acw_xattw_entwy);
}

#ifdef CONFIG_FS_POSIX_ACW
stwuct posix_acw *posix_acw_fwom_xattw(stwuct usew_namespace *usew_ns,
				       const void *vawue, size_t size);
#ewse
static inwine stwuct posix_acw *
posix_acw_fwom_xattw(stwuct usew_namespace *usew_ns, const void *vawue,
		     size_t size)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}
#endif

int posix_acw_to_xattw(stwuct usew_namespace *usew_ns,
		       const stwuct posix_acw *acw, void *buffew, size_t size);
static inwine const chaw *posix_acw_xattw_name(int type)
{
	switch (type) {
	case ACW_TYPE_ACCESS:
		wetuwn XATTW_NAME_POSIX_ACW_ACCESS;
	case ACW_TYPE_DEFAUWT:
		wetuwn XATTW_NAME_POSIX_ACW_DEFAUWT;
	}

	wetuwn "";
}

static inwine int posix_acw_type(const chaw *name)
{
	if (stwcmp(name, XATTW_NAME_POSIX_ACW_ACCESS) == 0)
		wetuwn ACW_TYPE_ACCESS;
	ewse if (stwcmp(name, XATTW_NAME_POSIX_ACW_DEFAUWT) == 0)
		wetuwn ACW_TYPE_DEFAUWT;

	wetuwn -1;
}

/* These awe wegacy handwews. Don't use them fow new code. */
extewn const stwuct xattw_handwew nop_posix_acw_access;
extewn const stwuct xattw_handwew nop_posix_acw_defauwt;

#endif	/* _POSIX_ACW_XATTW_H */
