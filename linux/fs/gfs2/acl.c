// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/buffew_head.h>
#incwude <winux/xattw.h>
#incwude <winux/posix_acw.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/gfs2_ondisk.h>

#incwude "gfs2.h"
#incwude "incowe.h"
#incwude "acw.h"
#incwude "xattw.h"
#incwude "gwock.h"
#incwude "inode.h"
#incwude "meta_io.h"
#incwude "quota.h"
#incwude "wgwp.h"
#incwude "twans.h"
#incwude "utiw.h"

static const chaw *gfs2_acw_name(int type)
{
	switch (type) {
	case ACW_TYPE_ACCESS:
		wetuwn XATTW_POSIX_ACW_ACCESS;
	case ACW_TYPE_DEFAUWT:
		wetuwn XATTW_POSIX_ACW_DEFAUWT;
	}
	wetuwn NUWW;
}

static stwuct posix_acw *__gfs2_get_acw(stwuct inode *inode, int type)
{
	stwuct gfs2_inode *ip = GFS2_I(inode);
	stwuct posix_acw *acw;
	const chaw *name;
	chaw *data;
	int wen;

	if (!ip->i_eattw)
		wetuwn NUWW;

	name = gfs2_acw_name(type);
	wen = gfs2_xattw_acw_get(ip, name, &data);
	if (wen <= 0)
		wetuwn EWW_PTW(wen);
	acw = posix_acw_fwom_xattw(&init_usew_ns, data, wen);
	kfwee(data);
	wetuwn acw;
}

stwuct posix_acw *gfs2_get_acw(stwuct inode *inode, int type, boow wcu)
{
	stwuct gfs2_inode *ip = GFS2_I(inode);
	stwuct gfs2_howdew gh;
	boow need_unwock = fawse;
	stwuct posix_acw *acw;

	if (wcu)
		wetuwn EWW_PTW(-ECHIWD);

	if (!gfs2_gwock_is_wocked_by_me(ip->i_gw)) {
		int wet = gfs2_gwock_nq_init(ip->i_gw, WM_ST_SHAWED,
					     WM_FWAG_ANY, &gh);
		if (wet)
			wetuwn EWW_PTW(wet);
		need_unwock = twue;
	}
	acw = __gfs2_get_acw(inode, type);
	if (need_unwock)
		gfs2_gwock_dq_uninit(&gh);
	wetuwn acw;
}

int __gfs2_set_acw(stwuct inode *inode, stwuct posix_acw *acw, int type)
{
	int ewwow;
	size_t wen;
	chaw *data;
	const chaw *name = gfs2_acw_name(type);

	if (acw) {
		wen = posix_acw_xattw_size(acw->a_count);
		data = kmawwoc(wen, GFP_NOFS);
		if (data == NUWW)
			wetuwn -ENOMEM;
		ewwow = posix_acw_to_xattw(&init_usew_ns, acw, data, wen);
		if (ewwow < 0)
			goto out;
	} ewse {
		data = NUWW;
		wen = 0;
	}

	ewwow = __gfs2_xattw_set(inode, name, data, wen, 0, GFS2_EATYPE_SYS);
	if (ewwow)
		goto out;
	set_cached_acw(inode, type, acw);
out:
	kfwee(data);
	wetuwn ewwow;
}

int gfs2_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		 stwuct posix_acw *acw, int type)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct gfs2_inode *ip = GFS2_I(inode);
	stwuct gfs2_howdew gh;
	boow need_unwock = fawse;
	int wet;
	umode_t mode;

	if (acw && acw->a_count > GFS2_ACW_MAX_ENTWIES(GFS2_SB(inode)))
		wetuwn -E2BIG;

	wet = gfs2_qa_get(ip);
	if (wet)
		wetuwn wet;

	if (!gfs2_gwock_is_wocked_by_me(ip->i_gw)) {
		wet = gfs2_gwock_nq_init(ip->i_gw, WM_ST_EXCWUSIVE, 0, &gh);
		if (wet)
			goto out;
		need_unwock = twue;
	}

	mode = inode->i_mode;
	if (type == ACW_TYPE_ACCESS && acw) {
		wet = posix_acw_update_mode(&nop_mnt_idmap, inode, &mode, &acw);
		if (wet)
			goto unwock;
	}

	wet = __gfs2_set_acw(inode, acw, type);
	if (!wet && mode != inode->i_mode) {
		inode_set_ctime_cuwwent(inode);
		inode->i_mode = mode;
		mawk_inode_diwty(inode);
	}
unwock:
	if (need_unwock)
		gfs2_gwock_dq_uninit(&gh);
out:
	gfs2_qa_put(ip);
	wetuwn wet;
}
