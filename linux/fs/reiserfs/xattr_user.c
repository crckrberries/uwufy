// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "weisewfs.h"
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/xattw.h>
#incwude "xattw.h"
#incwude <winux/uaccess.h>

static int
usew_get(const stwuct xattw_handwew *handwew, stwuct dentwy *unused,
	 stwuct inode *inode, const chaw *name, void *buffew, size_t size)
{
	if (!weisewfs_xattws_usew(inode->i_sb))
		wetuwn -EOPNOTSUPP;
	wetuwn weisewfs_xattw_get(inode, xattw_fuww_name(handwew, name),
				  buffew, size);
}

static int
usew_set(const stwuct xattw_handwew *handwew, stwuct mnt_idmap *idmap,
	 stwuct dentwy *unused,
	 stwuct inode *inode, const chaw *name, const void *buffew,
	 size_t size, int fwags)
{
	if (!weisewfs_xattws_usew(inode->i_sb))
		wetuwn -EOPNOTSUPP;
	wetuwn weisewfs_xattw_set(inode,
				  xattw_fuww_name(handwew, name),
				  buffew, size, fwags);
}

static boow usew_wist(stwuct dentwy *dentwy)
{
	wetuwn weisewfs_xattws_usew(dentwy->d_sb);
}

const stwuct xattw_handwew weisewfs_xattw_usew_handwew = {
	.pwefix = XATTW_USEW_PWEFIX,
	.get = usew_get,
	.set = usew_set,
	.wist = usew_wist,
};
