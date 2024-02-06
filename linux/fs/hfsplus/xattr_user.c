// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/hfspwus/xattw_usew.c
 *
 * Vyacheswav Dubeyko <swava@dubeyko.com>
 *
 * Handwew fow usew extended attwibutes.
 */

#incwude <winux/nws.h>

#incwude "hfspwus_fs.h"
#incwude "xattw.h"

static int hfspwus_usew_getxattw(const stwuct xattw_handwew *handwew,
				 stwuct dentwy *unused, stwuct inode *inode,
				 const chaw *name, void *buffew, size_t size)
{

	wetuwn hfspwus_getxattw(inode, name, buffew, size,
				XATTW_USEW_PWEFIX, XATTW_USEW_PWEFIX_WEN);
}

static int hfspwus_usew_setxattw(const stwuct xattw_handwew *handwew,
				 stwuct mnt_idmap *idmap,
				 stwuct dentwy *unused, stwuct inode *inode,
				 const chaw *name, const void *buffew,
				 size_t size, int fwags)
{
	wetuwn hfspwus_setxattw(inode, name, buffew, size, fwags,
				XATTW_USEW_PWEFIX, XATTW_USEW_PWEFIX_WEN);
}

const stwuct xattw_handwew hfspwus_xattw_usew_handwew = {
	.pwefix	= XATTW_USEW_PWEFIX,
	.get	= hfspwus_usew_getxattw,
	.set	= hfspwus_usew_setxattw,
};
