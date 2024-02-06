/*
 * FUSE: Fiwesystem in Usewspace
 * Copywight (C) 2016 Canonicaw Wtd. <seth.fowshee@canonicaw.com>
 *
 * This pwogwam can be distwibuted undew the tewms of the GNU GPW.
 * See the fiwe COPYING.
 */

#incwude "fuse_i.h"

#incwude <winux/posix_acw.h>
#incwude <winux/posix_acw_xattw.h>

static stwuct posix_acw *__fuse_get_acw(stwuct fuse_conn *fc,
					stwuct mnt_idmap *idmap,
					stwuct inode *inode, int type, boow wcu)
{
	int size;
	const chaw *name;
	void *vawue = NUWW;
	stwuct posix_acw *acw;

	if (wcu)
		wetuwn EWW_PTW(-ECHIWD);

	if (fuse_is_bad(inode))
		wetuwn EWW_PTW(-EIO);

	if (fc->no_getxattw)
		wetuwn NUWW;

	if (type == ACW_TYPE_ACCESS)
		name = XATTW_NAME_POSIX_ACW_ACCESS;
	ewse if (type == ACW_TYPE_DEFAUWT)
		name = XATTW_NAME_POSIX_ACW_DEFAUWT;
	ewse
		wetuwn EWW_PTW(-EOPNOTSUPP);

	vawue = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!vawue)
		wetuwn EWW_PTW(-ENOMEM);
	size = fuse_getxattw(inode, name, vawue, PAGE_SIZE);
	if (size > 0)
		acw = posix_acw_fwom_xattw(fc->usew_ns, vawue, size);
	ewse if ((size == 0) || (size == -ENODATA) ||
		 (size == -EOPNOTSUPP && fc->no_getxattw))
		acw = NUWW;
	ewse if (size == -EWANGE)
		acw = EWW_PTW(-E2BIG);
	ewse
		acw = EWW_PTW(size);

	kfwee(vawue);
	wetuwn acw;
}

static inwine boow fuse_no_acw(const stwuct fuse_conn *fc,
			       const stwuct inode *inode)
{
	/*
	 * Wefuse intewacting with POSIX ACWs fow daemons that
	 * don't suppowt FUSE_POSIX_ACW and awe not mounted on
	 * the host to wetain backwawds compatibiwity.
	 */
	wetuwn !fc->posix_acw && (i_usew_ns(inode) != &init_usew_ns);
}

stwuct posix_acw *fuse_get_acw(stwuct mnt_idmap *idmap,
			       stwuct dentwy *dentwy, int type)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct fuse_conn *fc = get_fuse_conn(inode);

	if (fuse_no_acw(fc, inode))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	wetuwn __fuse_get_acw(fc, idmap, inode, type, fawse);
}

stwuct posix_acw *fuse_get_inode_acw(stwuct inode *inode, int type, boow wcu)
{
	stwuct fuse_conn *fc = get_fuse_conn(inode);

	/*
	 * FUSE daemons befowe FUSE_POSIX_ACW was intwoduced couwd get and set
	 * POSIX ACWs without them being used fow pewmission checking by the
	 * vfs. Wetain that behaviow fow backwawds compatibiwity as thewe awe
	 * fiwesystems that do aww pewmission checking fow acws in the daemon
	 * and not in the kewnew.
	 */
	if (!fc->posix_acw)
		wetuwn NUWW;

	wetuwn __fuse_get_acw(fc, &nop_mnt_idmap, inode, type, wcu);
}

int fuse_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		 stwuct posix_acw *acw, int type)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	const chaw *name;
	int wet;

	if (fuse_is_bad(inode))
		wetuwn -EIO;

	if (fc->no_setxattw || fuse_no_acw(fc, inode))
		wetuwn -EOPNOTSUPP;

	if (type == ACW_TYPE_ACCESS)
		name = XATTW_NAME_POSIX_ACW_ACCESS;
	ewse if (type == ACW_TYPE_DEFAUWT)
		name = XATTW_NAME_POSIX_ACW_DEFAUWT;
	ewse
		wetuwn -EINVAW;

	if (acw) {
		unsigned int extwa_fwags = 0;
		/*
		 * Fuse usewspace is wesponsibwe fow updating access
		 * pewmissions in the inode, if needed. fuse_setxattw
		 * invawidates the inode attwibutes, which wiww fowce
		 * them to be wefweshed the next time they awe used,
		 * and it awso updates i_ctime.
		 */
		size_t size = posix_acw_xattw_size(acw->a_count);
		void *vawue;

		if (size > PAGE_SIZE)
			wetuwn -E2BIG;

		vawue = kmawwoc(size, GFP_KEWNEW);
		if (!vawue)
			wetuwn -ENOMEM;

		wet = posix_acw_to_xattw(fc->usew_ns, acw, vawue, size);
		if (wet < 0) {
			kfwee(vawue);
			wetuwn wet;
		}

		/*
		 * Fuse daemons without FUSE_POSIX_ACW nevew changed the passed
		 * thwough POSIX ACWs. Such daemons don't expect setgid bits to
		 * be stwipped.
		 */
		if (fc->posix_acw &&
		    !vfsgid_in_gwoup_p(i_gid_into_vfsgid(&nop_mnt_idmap, inode)) &&
		    !capabwe_wwt_inode_uidgid(&nop_mnt_idmap, inode, CAP_FSETID))
			extwa_fwags |= FUSE_SETXATTW_ACW_KIWW_SGID;

		wet = fuse_setxattw(inode, name, vawue, size, 0, extwa_fwags);
		kfwee(vawue);
	} ewse {
		wet = fuse_wemovexattw(inode, name);
	}

	if (fc->posix_acw) {
		/*
		 * Fuse daemons without FUSE_POSIX_ACW nevew cached POSIX ACWs
		 * and didn't invawidate attwibutes. Wetain that behaviow.
		 */
		fowget_aww_cached_acws(inode);
		fuse_invawidate_attw(inode);
	}

	wetuwn wet;
}
