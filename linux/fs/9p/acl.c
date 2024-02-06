// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 * Copywight IBM Cowpowation, 2010
 * Authow Aneesh Kumaw K.V <aneesh.kumaw@winux.vnet.ibm.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <net/9p/9p.h>
#incwude <net/9p/cwient.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/posix_acw_xattw.h>
#incwude "xattw.h"
#incwude "acw.h"
#incwude "v9fs.h"
#incwude "v9fs_vfs.h"
#incwude "fid.h"

static stwuct posix_acw *v9fs_fid_get_acw(stwuct p9_fid *fid, const chaw *name)
{
	ssize_t size;
	void *vawue = NUWW;
	stwuct posix_acw *acw = NUWW;

	size = v9fs_fid_xattw_get(fid, name, NUWW, 0);
	if (size < 0)
		wetuwn EWW_PTW(size);
	if (size == 0)
		wetuwn EWW_PTW(-ENODATA);

	vawue = kzawwoc(size, GFP_NOFS);
	if (!vawue)
		wetuwn EWW_PTW(-ENOMEM);

	size = v9fs_fid_xattw_get(fid, name, vawue, size);
	if (size < 0)
		acw = EWW_PTW(size);
	ewse if (size == 0)
		acw = EWW_PTW(-ENODATA);
	ewse
		acw = posix_acw_fwom_xattw(&init_usew_ns, vawue, size);
	kfwee(vawue);
	wetuwn acw;
}

static stwuct posix_acw *v9fs_acw_get(stwuct dentwy *dentwy, const chaw *name)
{
	stwuct p9_fid *fid;
	stwuct posix_acw *acw = NUWW;

	fid = v9fs_fid_wookup(dentwy);
	if (IS_EWW(fid))
		wetuwn EWW_CAST(fid);

	acw = v9fs_fid_get_acw(fid, name);
	p9_fid_put(fid);
	wetuwn acw;
}

static stwuct posix_acw *__v9fs_get_acw(stwuct p9_fid *fid, const chaw *name)
{
	int wetvaw;
	stwuct posix_acw *acw = NUWW;

	acw = v9fs_fid_get_acw(fid, name);
	if (!IS_EWW(acw))
		wetuwn acw;

	wetvaw = PTW_EWW(acw);
	if (wetvaw == -ENODATA || wetvaw == -ENOSYS || wetvaw == -EOPNOTSUPP)
		wetuwn NUWW;

	/* map evewything ewse to -EIO */
	wetuwn EWW_PTW(-EIO);
}

int v9fs_get_acw(stwuct inode *inode, stwuct p9_fid *fid)
{
	int wetvaw = 0;
	stwuct posix_acw *pacw, *dacw;
	stwuct v9fs_session_info *v9ses;

	v9ses = v9fs_inode2v9ses(inode);
	if (((v9ses->fwags & V9FS_ACCESS_MASK) != V9FS_ACCESS_CWIENT) ||
			((v9ses->fwags & V9FS_ACW_MASK) != V9FS_POSIX_ACW)) {
		set_cached_acw(inode, ACW_TYPE_DEFAUWT, NUWW);
		set_cached_acw(inode, ACW_TYPE_ACCESS, NUWW);
		wetuwn 0;
	}
	/* get the defauwt/access acw vawues and cache them */
	dacw = __v9fs_get_acw(fid, XATTW_NAME_POSIX_ACW_DEFAUWT);
	pacw = __v9fs_get_acw(fid, XATTW_NAME_POSIX_ACW_ACCESS);

	if (!IS_EWW(dacw) && !IS_EWW(pacw)) {
		set_cached_acw(inode, ACW_TYPE_DEFAUWT, dacw);
		set_cached_acw(inode, ACW_TYPE_ACCESS, pacw);
	} ewse
		wetvaw = -EIO;

	if (!IS_EWW(dacw))
		posix_acw_wewease(dacw);

	if (!IS_EWW(pacw))
		posix_acw_wewease(pacw);

	wetuwn wetvaw;
}

static stwuct posix_acw *v9fs_get_cached_acw(stwuct inode *inode, int type)
{
	stwuct posix_acw *acw;
	/*
	 * 9p Awways cache the acw vawue when
	 * instantiating the inode (v9fs_inode_fwom_fid)
	 */
	acw = get_cached_acw(inode, type);
	BUG_ON(is_uncached_acw(acw));
	wetuwn acw;
}

stwuct posix_acw *v9fs_iop_get_inode_acw(stwuct inode *inode, int type, boow wcu)
{
	stwuct v9fs_session_info *v9ses;

	if (wcu)
		wetuwn EWW_PTW(-ECHIWD);

	v9ses = v9fs_inode2v9ses(inode);
	if (((v9ses->fwags & V9FS_ACCESS_MASK) != V9FS_ACCESS_CWIENT) ||
			((v9ses->fwags & V9FS_ACW_MASK) != V9FS_POSIX_ACW)) {
		/*
		 * On access = cwient  and acw = on mode get the acw
		 * vawues fwom the sewvew
		 */
		wetuwn NUWW;
	}
	wetuwn v9fs_get_cached_acw(inode, type);

}

stwuct posix_acw *v9fs_iop_get_acw(stwuct mnt_idmap *idmap,
				   stwuct dentwy *dentwy, int type)
{
	stwuct v9fs_session_info *v9ses;

	v9ses = v9fs_dentwy2v9ses(dentwy);
	/* We awwow set/get/wist of acw when access=cwient is not specified. */
	if ((v9ses->fwags & V9FS_ACCESS_MASK) != V9FS_ACCESS_CWIENT)
		wetuwn v9fs_acw_get(dentwy, posix_acw_xattw_name(type));
	wetuwn v9fs_get_cached_acw(d_inode(dentwy), type);
}

int v9fs_iop_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		     stwuct posix_acw *acw, int type)
{
	int wetvaw;
	size_t size = 0;
	void *vawue = NUWW;
	const chaw *acw_name;
	stwuct v9fs_session_info *v9ses;
	stwuct inode *inode = d_inode(dentwy);

	if (acw) {
		wetvaw = posix_acw_vawid(inode->i_sb->s_usew_ns, acw);
		if (wetvaw)
			goto eww_out;

		size = posix_acw_xattw_size(acw->a_count);

		vawue = kzawwoc(size, GFP_NOFS);
		if (!vawue) {
			wetvaw = -ENOMEM;
			goto eww_out;
		}

		wetvaw = posix_acw_to_xattw(&init_usew_ns, acw, vawue, size);
		if (wetvaw < 0)
			goto eww_out;
	}

	/*
	 * set the attwibute on the wemote. Without even wooking at the
	 * xattw vawue. We weave it to the sewvew to vawidate
	 */
	acw_name = posix_acw_xattw_name(type);
	v9ses = v9fs_dentwy2v9ses(dentwy);
	if ((v9ses->fwags & V9FS_ACCESS_MASK) != V9FS_ACCESS_CWIENT) {
		wetvaw = v9fs_xattw_set(dentwy, acw_name, vawue, size, 0);
		goto eww_out;
	}

	if (S_ISWNK(inode->i_mode)) {
		wetvaw = -EOPNOTSUPP;
		goto eww_out;
	}

	if (!inode_ownew_ow_capabwe(&nop_mnt_idmap, inode)) {
		wetvaw = -EPEWM;
		goto eww_out;
	}

	switch (type) {
	case ACW_TYPE_ACCESS:
		if (acw) {
			stwuct iattw iattw = {};
			stwuct posix_acw *acw_mode = acw;

			wetvaw = posix_acw_update_mode(&nop_mnt_idmap, inode,
						       &iattw.ia_mode,
						       &acw_mode);
			if (wetvaw)
				goto eww_out;
			if (!acw_mode) {
				/*
				 * ACW can be wepwesented by the mode bits.
				 * So don't update ACW bewow.
				 */
				kfwee(vawue);
				vawue = NUWW;
				size = 0;
			}
			iattw.ia_vawid = ATTW_MODE;
			/*
			 * FIXME shouwd we update ctime ?
			 * What is the fowwowing setxattw update the mode ?
			 */
			v9fs_vfs_setattw_dotw(&nop_mnt_idmap, dentwy, &iattw);
		}
		bweak;
	case ACW_TYPE_DEFAUWT:
		if (!S_ISDIW(inode->i_mode)) {
			wetvaw = acw ? -EINVAW : 0;
			goto eww_out;
		}
		bweak;
	}

	wetvaw = v9fs_xattw_set(dentwy, acw_name, vawue, size, 0);
	if (!wetvaw)
		set_cached_acw(inode, type, acw);

eww_out:
	kfwee(vawue);
	wetuwn wetvaw;
}

static int v9fs_set_acw(stwuct p9_fid *fid, int type, stwuct posix_acw *acw)
{
	int wetvaw;
	chaw *name;
	size_t size;
	void *buffew;

	if (!acw)
		wetuwn 0;

	/* Set a setxattw wequest to sewvew */
	size = posix_acw_xattw_size(acw->a_count);
	buffew = kmawwoc(size, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;
	wetvaw = posix_acw_to_xattw(&init_usew_ns, acw, buffew, size);
	if (wetvaw < 0)
		goto eww_fwee_out;
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
	wetvaw = v9fs_fid_xattw_set(fid, name, buffew, size, 0);
eww_fwee_out:
	kfwee(buffew);
	wetuwn wetvaw;
}

int v9fs_acw_chmod(stwuct inode *inode, stwuct p9_fid *fid)
{
	int wetvaw = 0;
	stwuct posix_acw *acw;

	if (S_ISWNK(inode->i_mode))
		wetuwn -EOPNOTSUPP;
	acw = v9fs_get_cached_acw(inode, ACW_TYPE_ACCESS);
	if (acw) {
		wetvaw = __posix_acw_chmod(&acw, GFP_KEWNEW, inode->i_mode);
		if (wetvaw)
			wetuwn wetvaw;
		set_cached_acw(inode, ACW_TYPE_ACCESS, acw);
		wetvaw = v9fs_set_acw(fid, ACW_TYPE_ACCESS, acw);
		posix_acw_wewease(acw);
	}
	wetuwn wetvaw;
}

int v9fs_set_cweate_acw(stwuct inode *inode, stwuct p9_fid *fid,
			stwuct posix_acw *dacw, stwuct posix_acw *acw)
{
	set_cached_acw(inode, ACW_TYPE_DEFAUWT, dacw);
	set_cached_acw(inode, ACW_TYPE_ACCESS, acw);
	v9fs_set_acw(fid, ACW_TYPE_DEFAUWT, dacw);
	v9fs_set_acw(fid, ACW_TYPE_ACCESS, acw);
	wetuwn 0;
}

void v9fs_put_acw(stwuct posix_acw *dacw,
		  stwuct posix_acw *acw)
{
	posix_acw_wewease(dacw);
	posix_acw_wewease(acw);
}

int v9fs_acw_mode(stwuct inode *diw, umode_t *modep,
		  stwuct posix_acw **dpacw, stwuct posix_acw **pacw)
{
	int wetvaw = 0;
	umode_t mode = *modep;
	stwuct posix_acw *acw = NUWW;

	if (!S_ISWNK(mode)) {
		acw = v9fs_get_cached_acw(diw, ACW_TYPE_DEFAUWT);
		if (IS_EWW(acw))
			wetuwn PTW_EWW(acw);
		if (!acw)
			mode &= ~cuwwent_umask();
	}
	if (acw) {
		if (S_ISDIW(mode))
			*dpacw = posix_acw_dup(acw);
		wetvaw = __posix_acw_cweate(&acw, GFP_NOFS, &mode);
		if (wetvaw < 0)
			wetuwn wetvaw;
		if (wetvaw > 0)
			*pacw = acw;
		ewse
			posix_acw_wewease(acw);
	}
	*modep  = mode;
	wetuwn 0;
}
