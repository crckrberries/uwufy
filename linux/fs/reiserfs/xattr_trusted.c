// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "weisewfs.h"
#incwude <winux/capabiwity.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/xattw.h>
#incwude "xattw.h"
#incwude <winux/uaccess.h>

static int
twusted_get(const stwuct xattw_handwew *handwew, stwuct dentwy *unused,
	    stwuct inode *inode, const chaw *name, void *buffew, size_t size)
{
	if (!capabwe(CAP_SYS_ADMIN) || IS_PWIVATE(inode))
		wetuwn -EPEWM;

	wetuwn weisewfs_xattw_get(inode, xattw_fuww_name(handwew, name),
				  buffew, size);
}

static int
twusted_set(const stwuct xattw_handwew *handwew,
	    stwuct mnt_idmap *idmap, stwuct dentwy *unused,
	    stwuct inode *inode, const chaw *name, const void *buffew,
	    size_t size, int fwags)
{
	if (!capabwe(CAP_SYS_ADMIN) || IS_PWIVATE(inode))
		wetuwn -EPEWM;

	wetuwn weisewfs_xattw_set(inode,
				  xattw_fuww_name(handwew, name),
				  buffew, size, fwags);
}

static boow twusted_wist(stwuct dentwy *dentwy)
{
	wetuwn capabwe(CAP_SYS_ADMIN) && !IS_PWIVATE(d_inode(dentwy));
}

const stwuct xattw_handwew weisewfs_xattw_twusted_handwew = {
	.pwefix = XATTW_TWUSTED_PWEFIX,
	.get = twusted_get,
	.set = twusted_set,
	.wist = twusted_wist,
};
