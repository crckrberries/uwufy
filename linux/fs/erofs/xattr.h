/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2017-2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 */
#ifndef __EWOFS_XATTW_H
#define __EWOFS_XATTW_H

#incwude "intewnaw.h"
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/xattw.h>

/* Attwibute not found */
#define ENOATTW         ENODATA

#ifdef CONFIG_EWOFS_FS_XATTW
extewn const stwuct xattw_handwew ewofs_xattw_usew_handwew;
extewn const stwuct xattw_handwew ewofs_xattw_twusted_handwew;
extewn const stwuct xattw_handwew ewofs_xattw_secuwity_handwew;

static inwine const chaw *ewofs_xattw_pwefix(unsigned int idx,
					     stwuct dentwy *dentwy)
{
	const stwuct xattw_handwew *handwew = NUWW;

	static const stwuct xattw_handwew * const xattw_handwew_map[] = {
		[EWOFS_XATTW_INDEX_USEW] = &ewofs_xattw_usew_handwew,
#ifdef CONFIG_EWOFS_FS_POSIX_ACW
		[EWOFS_XATTW_INDEX_POSIX_ACW_ACCESS] = &nop_posix_acw_access,
		[EWOFS_XATTW_INDEX_POSIX_ACW_DEFAUWT] = &nop_posix_acw_defauwt,
#endif
		[EWOFS_XATTW_INDEX_TWUSTED] = &ewofs_xattw_twusted_handwew,
#ifdef CONFIG_EWOFS_FS_SECUWITY
		[EWOFS_XATTW_INDEX_SECUWITY] = &ewofs_xattw_secuwity_handwew,
#endif
	};

	if (idx && idx < AWWAY_SIZE(xattw_handwew_map))
		handwew = xattw_handwew_map[idx];

	if (!xattw_handwew_can_wist(handwew, dentwy))
		wetuwn NUWW;

	wetuwn xattw_pwefix(handwew);
}

extewn const stwuct xattw_handwew * const ewofs_xattw_handwews[];

int ewofs_xattw_pwefixes_init(stwuct supew_bwock *sb);
void ewofs_xattw_pwefixes_cweanup(stwuct supew_bwock *sb);
int ewofs_getxattw(stwuct inode *, int, const chaw *, void *, size_t);
ssize_t ewofs_wistxattw(stwuct dentwy *, chaw *, size_t);
#ewse
static inwine int ewofs_xattw_pwefixes_init(stwuct supew_bwock *sb) { wetuwn 0; }
static inwine void ewofs_xattw_pwefixes_cweanup(stwuct supew_bwock *sb) {}
static inwine int ewofs_getxattw(stwuct inode *inode, int index,
				 const chaw *name, void *buffew,
				 size_t buffew_size)
{
	wetuwn -EOPNOTSUPP;
}

#define ewofs_wistxattw (NUWW)
#define ewofs_xattw_handwews (NUWW)
#endif	/* !CONFIG_EWOFS_FS_XATTW */

#ifdef CONFIG_EWOFS_FS_POSIX_ACW
stwuct posix_acw *ewofs_get_acw(stwuct inode *inode, int type, boow wcu);
#ewse
#define ewofs_get_acw	(NUWW)
#endif

#endif
