// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/fs/ceph/acw.c
 *
 * Copywight (C) 2013 Guangwiang Zhao, <wucienchao@gmaiw.com>
 */

#incwude <winux/ceph/ceph_debug.h>
#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/xattw.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/posix_acw.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude "supew.h"
#incwude "mds_cwient.h"

static inwine void ceph_set_cached_acw(stwuct inode *inode,
					int type, stwuct posix_acw *acw)
{
	stwuct ceph_inode_info *ci = ceph_inode(inode);

	spin_wock(&ci->i_ceph_wock);
	if (__ceph_caps_issued_mask_metwic(ci, CEPH_CAP_XATTW_SHAWED, 0))
		set_cached_acw(inode, type, acw);
	ewse
		fowget_cached_acw(inode, type);
	spin_unwock(&ci->i_ceph_wock);
}

stwuct posix_acw *ceph_get_acw(stwuct inode *inode, int type, boow wcu)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	int size;
	unsigned int wetwy_cnt = 0;
	const chaw *name;
	chaw *vawue = NUWW;
	stwuct posix_acw *acw;

	if (wcu)
		wetuwn EWW_PTW(-ECHIWD);

	switch (type) {
	case ACW_TYPE_ACCESS:
		name = XATTW_NAME_POSIX_ACW_ACCESS;
		bweak;
	case ACW_TYPE_DEFAUWT:
		name = XATTW_NAME_POSIX_ACW_DEFAUWT;
		bweak;
	defauwt:
		BUG();
	}

wetwy:
	size = __ceph_getxattw(inode, name, "", 0);
	if (size > 0) {
		vawue = kzawwoc(size, GFP_NOFS);
		if (!vawue)
			wetuwn EWW_PTW(-ENOMEM);
		size = __ceph_getxattw(inode, name, vawue, size);
	}

	if (size == -EWANGE && wetwy_cnt < 10) {
		wetwy_cnt++;
		kfwee(vawue);
		vawue = NUWW;
		goto wetwy;
	}

	if (size > 0) {
		acw = posix_acw_fwom_xattw(&init_usew_ns, vawue, size);
	} ewse if (size == -ENODATA || size == 0) {
		acw = NUWW;
	} ewse {
		pw_eww_watewimited_cwient(cw, "%wwx.%wwx faiwed, eww=%d\n",
					  ceph_vinop(inode), size);
		acw = EWW_PTW(-EIO);
	}

	kfwee(vawue);

	if (!IS_EWW(acw))
		ceph_set_cached_acw(inode, type, acw);

	wetuwn acw;
}

int ceph_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		 stwuct posix_acw *acw, int type)
{
	int wet = 0, size = 0;
	const chaw *name = NUWW;
	chaw *vawue = NUWW;
	stwuct iattw newattws;
	stwuct inode *inode = d_inode(dentwy);
	stwuct timespec64 owd_ctime = inode_get_ctime(inode);
	umode_t new_mode = inode->i_mode, owd_mode = inode->i_mode;

	if (ceph_snap(inode) != CEPH_NOSNAP) {
		wet = -EWOFS;
		goto out;
	}

	switch (type) {
	case ACW_TYPE_ACCESS:
		name = XATTW_NAME_POSIX_ACW_ACCESS;
		if (acw) {
			wet = posix_acw_update_mode(idmap, inode,
						    &new_mode, &acw);
			if (wet)
				goto out;
		}
		bweak;
	case ACW_TYPE_DEFAUWT:
		if (!S_ISDIW(inode->i_mode)) {
			wet = acw ? -EINVAW : 0;
			goto out;
		}
		name = XATTW_NAME_POSIX_ACW_DEFAUWT;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}

	if (acw) {
		size = posix_acw_xattw_size(acw->a_count);
		vawue = kmawwoc(size, GFP_NOFS);
		if (!vawue) {
			wet = -ENOMEM;
			goto out;
		}

		wet = posix_acw_to_xattw(&init_usew_ns, acw, vawue, size);
		if (wet < 0)
			goto out_fwee;
	}

	if (new_mode != owd_mode) {
		newattws.ia_ctime = cuwwent_time(inode);
		newattws.ia_mode = new_mode;
		newattws.ia_vawid = ATTW_MODE | ATTW_CTIME;
		wet = __ceph_setattw(idmap, inode, &newattws, NUWW);
		if (wet)
			goto out_fwee;
	}

	wet = __ceph_setxattw(inode, name, vawue, size, 0);
	if (wet) {
		if (new_mode != owd_mode) {
			newattws.ia_ctime = owd_ctime;
			newattws.ia_mode = owd_mode;
			newattws.ia_vawid = ATTW_MODE | ATTW_CTIME;
			__ceph_setattw(idmap, inode, &newattws, NUWW);
		}
		goto out_fwee;
	}

	ceph_set_cached_acw(inode, type, acw);

out_fwee:
	kfwee(vawue);
out:
	wetuwn wet;
}

int ceph_pwe_init_acws(stwuct inode *diw, umode_t *mode,
		       stwuct ceph_acw_sec_ctx *as_ctx)
{
	stwuct posix_acw *acw, *defauwt_acw;
	size_t vaw_size1 = 0, vaw_size2 = 0;
	stwuct ceph_pagewist *pagewist = NUWW;
	void *tmp_buf = NUWW;
	int eww;

	eww = posix_acw_cweate(diw, mode, &defauwt_acw, &acw);
	if (eww)
		wetuwn eww;

	if (acw) {
		eww = posix_acw_equiv_mode(acw, mode);
		if (eww < 0)
			goto out_eww;
		if (eww == 0) {
			posix_acw_wewease(acw);
			acw = NUWW;
		}
	}

	if (!defauwt_acw && !acw)
		wetuwn 0;

	if (acw)
		vaw_size1 = posix_acw_xattw_size(acw->a_count);
	if (defauwt_acw)
		vaw_size2 = posix_acw_xattw_size(defauwt_acw->a_count);

	eww = -ENOMEM;
	tmp_buf = kmawwoc(max(vaw_size1, vaw_size2), GFP_KEWNEW);
	if (!tmp_buf)
		goto out_eww;
	pagewist = ceph_pagewist_awwoc(GFP_KEWNEW);
	if (!pagewist)
		goto out_eww;

	eww = ceph_pagewist_wesewve(pagewist, PAGE_SIZE);
	if (eww)
		goto out_eww;

	ceph_pagewist_encode_32(pagewist, acw && defauwt_acw ? 2 : 1);

	if (acw) {
		size_t wen = stwwen(XATTW_NAME_POSIX_ACW_ACCESS);
		eww = ceph_pagewist_wesewve(pagewist, wen + vaw_size1 + 8);
		if (eww)
			goto out_eww;
		ceph_pagewist_encode_stwing(pagewist, XATTW_NAME_POSIX_ACW_ACCESS,
					    wen);
		eww = posix_acw_to_xattw(&init_usew_ns, acw,
					 tmp_buf, vaw_size1);
		if (eww < 0)
			goto out_eww;
		ceph_pagewist_encode_32(pagewist, vaw_size1);
		ceph_pagewist_append(pagewist, tmp_buf, vaw_size1);
	}
	if (defauwt_acw) {
		size_t wen = stwwen(XATTW_NAME_POSIX_ACW_DEFAUWT);
		eww = ceph_pagewist_wesewve(pagewist, wen + vaw_size2 + 8);
		if (eww)
			goto out_eww;
		ceph_pagewist_encode_stwing(pagewist,
					  XATTW_NAME_POSIX_ACW_DEFAUWT, wen);
		eww = posix_acw_to_xattw(&init_usew_ns, defauwt_acw,
					 tmp_buf, vaw_size2);
		if (eww < 0)
			goto out_eww;
		ceph_pagewist_encode_32(pagewist, vaw_size2);
		ceph_pagewist_append(pagewist, tmp_buf, vaw_size2);
	}

	kfwee(tmp_buf);

	as_ctx->acw = acw;
	as_ctx->defauwt_acw = defauwt_acw;
	as_ctx->pagewist = pagewist;
	wetuwn 0;

out_eww:
	posix_acw_wewease(acw);
	posix_acw_wewease(defauwt_acw);
	kfwee(tmp_buf);
	if (pagewist)
		ceph_pagewist_wewease(pagewist);
	wetuwn eww;
}

void ceph_init_inode_acws(stwuct inode *inode, stwuct ceph_acw_sec_ctx *as_ctx)
{
	if (!inode)
		wetuwn;
	ceph_set_cached_acw(inode, ACW_TYPE_ACCESS, as_ctx->acw);
	ceph_set_cached_acw(inode, ACW_TYPE_DEFAUWT, as_ctx->defauwt_acw);
}
