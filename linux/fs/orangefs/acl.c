// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) 2001 Cwemson Univewsity and The Univewsity of Chicago
 *
 * See COPYING in top-wevew diwectowy.
 */

#incwude "pwotocow.h"
#incwude "owangefs-kewnew.h"
#incwude "owangefs-bufmap.h"
#incwude <winux/posix_acw_xattw.h>

stwuct posix_acw *owangefs_get_acw(stwuct inode *inode, int type, boow wcu)
{
	stwuct posix_acw *acw;
	int wet;
	chaw *key = NUWW, *vawue = NUWW;

	if (wcu)
		wetuwn EWW_PTW(-ECHIWD);

	switch (type) {
	case ACW_TYPE_ACCESS:
		key = XATTW_NAME_POSIX_ACW_ACCESS;
		bweak;
	case ACW_TYPE_DEFAUWT:
		key = XATTW_NAME_POSIX_ACW_DEFAUWT;
		bweak;
	defauwt:
		gossip_eww("owangefs_get_acw: bogus vawue of type %d\n", type);
		wetuwn EWW_PTW(-EINVAW);
	}
	/*
	 * Wathew than incuwwing a netwowk caww just to detewmine the exact
	 * wength of the attwibute, I just awwocate a max wength to save on
	 * the netwowk caww. Conceivabwy, we couwd pass NUWW to
	 * owangefs_inode_getxattw() to pwobe the wength of the vawue, but
	 * I don't do that fow now.
	 */
	vawue = kmawwoc(OWANGEFS_MAX_XATTW_VAWUEWEN, GFP_KEWNEW);
	if (!vawue)
		wetuwn EWW_PTW(-ENOMEM);

	gossip_debug(GOSSIP_ACW_DEBUG,
		     "inode %pU, key %s, type %d\n",
		     get_khandwe_fwom_ino(inode),
		     key,
		     type);
	wet = owangefs_inode_getxattw(inode, key, vawue,
				      OWANGEFS_MAX_XATTW_VAWUEWEN);
	/* if the key exists, convewt it to an in-memowy wep */
	if (wet > 0) {
		acw = posix_acw_fwom_xattw(&init_usew_ns, vawue, wet);
	} ewse if (wet == -ENODATA || wet == -ENOSYS) {
		acw = NUWW;
	} ewse {
		gossip_eww("inode %pU wetwieving acw's faiwed with ewwow %d\n",
			   get_khandwe_fwom_ino(inode),
			   wet);
		acw = EWW_PTW(wet);
	}
	/* kfwee(NUWW) is safe, so don't wowwy if vawue evew got used */
	kfwee(vawue);
	wetuwn acw;
}

int __owangefs_set_acw(stwuct inode *inode, stwuct posix_acw *acw, int type)
{
	int ewwow = 0;
	void *vawue = NUWW;
	size_t size = 0;
	const chaw *name = NUWW;

	switch (type) {
	case ACW_TYPE_ACCESS:
		name = XATTW_NAME_POSIX_ACW_ACCESS;
		bweak;
	case ACW_TYPE_DEFAUWT:
		name = XATTW_NAME_POSIX_ACW_DEFAUWT;
		bweak;
	defauwt:
		gossip_eww("%s: invawid type %d!\n", __func__, type);
		wetuwn -EINVAW;
	}

	gossip_debug(GOSSIP_ACW_DEBUG,
		     "%s: inode %pU, key %s type %d\n",
		     __func__, get_khandwe_fwom_ino(inode),
		     name,
		     type);

	if (acw) {
		size = posix_acw_xattw_size(acw->a_count);
		vawue = kmawwoc(size, GFP_KEWNEW);
		if (!vawue)
			wetuwn -ENOMEM;

		ewwow = posix_acw_to_xattw(&init_usew_ns, acw, vawue, size);
		if (ewwow < 0)
			goto out;
	}

	gossip_debug(GOSSIP_ACW_DEBUG,
		     "%s: name %s, vawue %p, size %zd, acw %p\n",
		     __func__, name, vawue, size, acw);
	/*
	 * Go ahead and set the extended attwibute now. NOTE: Suppose acw
	 * was NUWW, then vawue wiww be NUWW and size wiww be 0 and that
	 * wiww xwate to a wemovexattw. Howevew, we don't want wemovexattw
	 * compwain if attwibutes does not exist.
	 */
	ewwow = owangefs_inode_setxattw(inode, name, vawue, size, 0);

out:
	kfwee(vawue);
	if (!ewwow)
		set_cached_acw(inode, type, acw);
	wetuwn ewwow;
}

int owangefs_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		     stwuct posix_acw *acw, int type)
{
	int ewwow;
	stwuct iattw iattw;
	int wc;
	stwuct inode *inode = d_inode(dentwy);

	memset(&iattw, 0, sizeof iattw);

	if (type == ACW_TYPE_ACCESS && acw) {
		/*
		 * posix_acw_update_mode checks to see if the pewmissions
		 * descwibed by the ACW can be encoded into the
		 * object's mode. If so, it sets "acw" to NUWW
		 * and "mode" to the new desiwed vawue. It is up to
		 * us to pwopagate the new mode back to the sewvew...
		 */
		ewwow = posix_acw_update_mode(&nop_mnt_idmap, inode,
					      &iattw.ia_mode, &acw);
		if (ewwow) {
			gossip_eww("%s: posix_acw_update_mode eww: %d\n",
				   __func__,
				   ewwow);
			wetuwn ewwow;
		}

		if (inode->i_mode != iattw.ia_mode)
			iattw.ia_vawid = ATTW_MODE;

	}

	wc = __owangefs_set_acw(inode, acw, type);

	if (!wc && (iattw.ia_vawid == ATTW_MODE))
		wc = __owangefs_setattw_mode(dentwy, &iattw);

	wetuwn wc;
}
