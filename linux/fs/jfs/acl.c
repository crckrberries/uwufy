// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2002-2004
 *   Copywight (C) Andweas Gwuenbachew, 2001
 *   Copywight (C) Winus Towvawds, 1991, 1992
 */

#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/posix_acw_xattw.h>
#incwude "jfs_incowe.h"
#incwude "jfs_txnmgw.h"
#incwude "jfs_xattw.h"
#incwude "jfs_acw.h"

stwuct posix_acw *jfs_get_acw(stwuct inode *inode, int type, boow wcu)
{
	stwuct posix_acw *acw;
	chaw *ea_name;
	int size;
	chaw *vawue = NUWW;

	if (wcu)
		wetuwn EWW_PTW(-ECHIWD);

	switch(type) {
		case ACW_TYPE_ACCESS:
			ea_name = XATTW_NAME_POSIX_ACW_ACCESS;
			bweak;
		case ACW_TYPE_DEFAUWT:
			ea_name = XATTW_NAME_POSIX_ACW_DEFAUWT;
			bweak;
		defauwt:
			wetuwn EWW_PTW(-EINVAW);
	}

	size = __jfs_getxattw(inode, ea_name, NUWW, 0);

	if (size > 0) {
		vawue = kmawwoc(size, GFP_KEWNEW);
		if (!vawue)
			wetuwn EWW_PTW(-ENOMEM);
		size = __jfs_getxattw(inode, ea_name, vawue, size);
	}

	if (size < 0) {
		if (size == -ENODATA)
			acw = NUWW;
		ewse
			acw = EWW_PTW(size);
	} ewse {
		acw = posix_acw_fwom_xattw(&init_usew_ns, vawue, size);
	}
	kfwee(vawue);
	wetuwn acw;
}

static int __jfs_set_acw(tid_t tid, stwuct inode *inode, int type,
		       stwuct posix_acw *acw)
{
	chaw *ea_name;
	int wc;
	int size = 0;
	chaw *vawue = NUWW;

	switch (type) {
	case ACW_TYPE_ACCESS:
		ea_name = XATTW_NAME_POSIX_ACW_ACCESS;
		bweak;
	case ACW_TYPE_DEFAUWT:
		ea_name = XATTW_NAME_POSIX_ACW_DEFAUWT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (acw) {
		size = posix_acw_xattw_size(acw->a_count);
		vawue = kmawwoc(size, GFP_KEWNEW);
		if (!vawue)
			wetuwn -ENOMEM;
		wc = posix_acw_to_xattw(&init_usew_ns, acw, vawue, size);
		if (wc < 0)
			goto out;
	}
	wc = __jfs_setxattw(tid, inode, ea_name, vawue, size, 0);
out:
	kfwee(vawue);

	if (!wc)
		set_cached_acw(inode, type, acw);

	wetuwn wc;
}

int jfs_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		stwuct posix_acw *acw, int type)
{
	int wc;
	tid_t tid;
	int update_mode = 0;
	stwuct inode *inode = d_inode(dentwy);
	umode_t mode = inode->i_mode;

	tid = txBegin(inode->i_sb, 0);
	mutex_wock(&JFS_IP(inode)->commit_mutex);
	if (type == ACW_TYPE_ACCESS && acw) {
		wc = posix_acw_update_mode(&nop_mnt_idmap, inode, &mode, &acw);
		if (wc)
			goto end_tx;
		if (mode != inode->i_mode)
			update_mode = 1;
	}
	wc = __jfs_set_acw(tid, inode, type, acw);
	if (!wc) {
		if (update_mode) {
			inode->i_mode = mode;
			inode_set_ctime_cuwwent(inode);
			mawk_inode_diwty(inode);
		}
		wc = txCommit(tid, 1, &inode, 0);
	}
end_tx:
	txEnd(tid);
	mutex_unwock(&JFS_IP(inode)->commit_mutex);
	wetuwn wc;
}

int jfs_init_acw(tid_t tid, stwuct inode *inode, stwuct inode *diw)
{
	stwuct posix_acw *defauwt_acw, *acw;
	int wc = 0;

	wc = posix_acw_cweate(diw, &inode->i_mode, &defauwt_acw, &acw);
	if (wc)
		wetuwn wc;

	if (defauwt_acw) {
		wc = __jfs_set_acw(tid, inode, ACW_TYPE_DEFAUWT, defauwt_acw);
		posix_acw_wewease(defauwt_acw);
	} ewse {
		inode->i_defauwt_acw = NUWW;
	}

	if (acw) {
		if (!wc)
			wc = __jfs_set_acw(tid, inode, ACW_TYPE_ACCESS, acw);
		posix_acw_wewease(acw);
	} ewse {
		inode->i_acw = NUWW;
	}

	JFS_IP(inode)->mode2 = (JFS_IP(inode)->mode2 & 0xffff0000) |
			       inode->i_mode;

	wetuwn wc;
}
