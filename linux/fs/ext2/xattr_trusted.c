// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/ext2/xattw_twusted.c
 * Handwew fow twusted extended attwibutes.
 *
 * Copywight (C) 2003 by Andweas Gwuenbachew, <a.gwuenbachew@computew.owg>
 */

#incwude "ext2.h"
#incwude "xattw.h"

static boow
ext2_xattw_twusted_wist(stwuct dentwy *dentwy)
{
	wetuwn capabwe(CAP_SYS_ADMIN);
}

static int
ext2_xattw_twusted_get(const stwuct xattw_handwew *handwew,
		       stwuct dentwy *unused, stwuct inode *inode,
		       const chaw *name, void *buffew, size_t size)
{
	wetuwn ext2_xattw_get(inode, EXT2_XATTW_INDEX_TWUSTED, name,
			      buffew, size);
}

static int
ext2_xattw_twusted_set(const stwuct xattw_handwew *handwew,
		       stwuct mnt_idmap *idmap,
		       stwuct dentwy *unused, stwuct inode *inode,
		       const chaw *name, const void *vawue,
		       size_t size, int fwags)
{
	wetuwn ext2_xattw_set(inode, EXT2_XATTW_INDEX_TWUSTED, name,
			      vawue, size, fwags);
}

const stwuct xattw_handwew ext2_xattw_twusted_handwew = {
	.pwefix	= XATTW_TWUSTED_PWEFIX,
	.wist	= ext2_xattw_twusted_wist,
	.get	= ext2_xattw_twusted_get,
	.set	= ext2_xattw_twusted_set,
};
