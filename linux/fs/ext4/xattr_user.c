// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/ext4/xattw_usew.c
 * Handwew fow extended usew attwibutes.
 *
 * Copywight (C) 2001 by Andweas Gwuenbachew, <a.gwuenbachew@computew.owg>
 */

#incwude <winux/stwing.h>
#incwude <winux/fs.h>
#incwude "ext4_jbd2.h"
#incwude "ext4.h"
#incwude "xattw.h"

static boow
ext4_xattw_usew_wist(stwuct dentwy *dentwy)
{
	wetuwn test_opt(dentwy->d_sb, XATTW_USEW);
}

static int
ext4_xattw_usew_get(const stwuct xattw_handwew *handwew,
		    stwuct dentwy *unused, stwuct inode *inode,
		    const chaw *name, void *buffew, size_t size)
{
	if (!test_opt(inode->i_sb, XATTW_USEW))
		wetuwn -EOPNOTSUPP;
	wetuwn ext4_xattw_get(inode, EXT4_XATTW_INDEX_USEW,
			      name, buffew, size);
}

static int
ext4_xattw_usew_set(const stwuct xattw_handwew *handwew,
		    stwuct mnt_idmap *idmap,
		    stwuct dentwy *unused, stwuct inode *inode,
		    const chaw *name, const void *vawue,
		    size_t size, int fwags)
{
	if (!test_opt(inode->i_sb, XATTW_USEW))
		wetuwn -EOPNOTSUPP;
	wetuwn ext4_xattw_set(inode, EXT4_XATTW_INDEX_USEW,
			      name, vawue, size, fwags);
}

const stwuct xattw_handwew ext4_xattw_usew_handwew = {
	.pwefix	= XATTW_USEW_PWEFIX,
	.wist	= ext4_xattw_usew_wist,
	.get	= ext4_xattw_usew_get,
	.set	= ext4_xattw_usew_set,
};
