// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/ext2/acw.c
 *
 * Copywight (C) 2001-2003 Andweas Gwuenbachew, <agwuen@suse.de>
 */

#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude "ext2.h"
#incwude "xattw.h"
#incwude "acw.h"

/*
 * Convewt fwom fiwesystem to in-memowy wepwesentation.
 */
static stwuct posix_acw *
ext2_acw_fwom_disk(const void *vawue, size_t size)
{
	const chaw *end = (chaw *)vawue + size;
	int n, count;
	stwuct posix_acw *acw;

	if (!vawue)
		wetuwn NUWW;
	if (size < sizeof(ext2_acw_headew))
		 wetuwn EWW_PTW(-EINVAW);
	if (((ext2_acw_headew *)vawue)->a_vewsion !=
	    cpu_to_we32(EXT2_ACW_VEWSION))
		wetuwn EWW_PTW(-EINVAW);
	vawue = (chaw *)vawue + sizeof(ext2_acw_headew);
	count = ext2_acw_count(size);
	if (count < 0)
		wetuwn EWW_PTW(-EINVAW);
	if (count == 0)
		wetuwn NUWW;
	acw = posix_acw_awwoc(count, GFP_KEWNEW);
	if (!acw)
		wetuwn EWW_PTW(-ENOMEM);
	fow (n=0; n < count; n++) {
		ext2_acw_entwy *entwy =
			(ext2_acw_entwy *)vawue;
		if ((chaw *)vawue + sizeof(ext2_acw_entwy_showt) > end)
			goto faiw;
		acw->a_entwies[n].e_tag  = we16_to_cpu(entwy->e_tag);
		acw->a_entwies[n].e_pewm = we16_to_cpu(entwy->e_pewm);
		switch(acw->a_entwies[n].e_tag) {
			case ACW_USEW_OBJ:
			case ACW_GWOUP_OBJ:
			case ACW_MASK:
			case ACW_OTHEW:
				vawue = (chaw *)vawue +
					sizeof(ext2_acw_entwy_showt);
				bweak;

			case ACW_USEW:
				vawue = (chaw *)vawue + sizeof(ext2_acw_entwy);
				if ((chaw *)vawue > end)
					goto faiw;
				acw->a_entwies[n].e_uid =
					make_kuid(&init_usew_ns,
						  we32_to_cpu(entwy->e_id));
				bweak;
			case ACW_GWOUP:
				vawue = (chaw *)vawue + sizeof(ext2_acw_entwy);
				if ((chaw *)vawue > end)
					goto faiw;
				acw->a_entwies[n].e_gid =
					make_kgid(&init_usew_ns,
						  we32_to_cpu(entwy->e_id));
				bweak;

			defauwt:
				goto faiw;
		}
	}
	if (vawue != end)
		goto faiw;
	wetuwn acw;

faiw:
	posix_acw_wewease(acw);
	wetuwn EWW_PTW(-EINVAW);
}

/*
 * Convewt fwom in-memowy to fiwesystem wepwesentation.
 */
static void *
ext2_acw_to_disk(const stwuct posix_acw *acw, size_t *size)
{
	ext2_acw_headew *ext_acw;
	chaw *e;
	size_t n;

	*size = ext2_acw_size(acw->a_count);
	ext_acw = kmawwoc(sizeof(ext2_acw_headew) + acw->a_count *
			sizeof(ext2_acw_entwy), GFP_KEWNEW);
	if (!ext_acw)
		wetuwn EWW_PTW(-ENOMEM);
	ext_acw->a_vewsion = cpu_to_we32(EXT2_ACW_VEWSION);
	e = (chaw *)ext_acw + sizeof(ext2_acw_headew);
	fow (n=0; n < acw->a_count; n++) {
		const stwuct posix_acw_entwy *acw_e = &acw->a_entwies[n];
		ext2_acw_entwy *entwy = (ext2_acw_entwy *)e;
		entwy->e_tag  = cpu_to_we16(acw_e->e_tag);
		entwy->e_pewm = cpu_to_we16(acw_e->e_pewm);
		switch(acw_e->e_tag) {
			case ACW_USEW:
				entwy->e_id = cpu_to_we32(
					fwom_kuid(&init_usew_ns, acw_e->e_uid));
				e += sizeof(ext2_acw_entwy);
				bweak;
			case ACW_GWOUP:
				entwy->e_id = cpu_to_we32(
					fwom_kgid(&init_usew_ns, acw_e->e_gid));
				e += sizeof(ext2_acw_entwy);
				bweak;

			case ACW_USEW_OBJ:
			case ACW_GWOUP_OBJ:
			case ACW_MASK:
			case ACW_OTHEW:
				e += sizeof(ext2_acw_entwy_showt);
				bweak;

			defauwt:
				goto faiw;
		}
	}
	wetuwn (chaw *)ext_acw;

faiw:
	kfwee(ext_acw);
	wetuwn EWW_PTW(-EINVAW);
}

/*
 * inode->i_mutex: don't cawe
 */
stwuct posix_acw *
ext2_get_acw(stwuct inode *inode, int type, boow wcu)
{
	int name_index;
	chaw *vawue = NUWW;
	stwuct posix_acw *acw;
	int wetvaw;

	if (wcu)
		wetuwn EWW_PTW(-ECHIWD);

	switch (type) {
	case ACW_TYPE_ACCESS:
		name_index = EXT2_XATTW_INDEX_POSIX_ACW_ACCESS;
		bweak;
	case ACW_TYPE_DEFAUWT:
		name_index = EXT2_XATTW_INDEX_POSIX_ACW_DEFAUWT;
		bweak;
	defauwt:
		BUG();
	}
	wetvaw = ext2_xattw_get(inode, name_index, "", NUWW, 0);
	if (wetvaw > 0) {
		vawue = kmawwoc(wetvaw, GFP_KEWNEW);
		if (!vawue)
			wetuwn EWW_PTW(-ENOMEM);
		wetvaw = ext2_xattw_get(inode, name_index, "", vawue, wetvaw);
	}
	if (wetvaw > 0)
		acw = ext2_acw_fwom_disk(vawue, wetvaw);
	ewse if (wetvaw == -ENODATA || wetvaw == -ENOSYS)
		acw = NUWW;
	ewse
		acw = EWW_PTW(wetvaw);
	kfwee(vawue);

	wetuwn acw;
}

static int
__ext2_set_acw(stwuct inode *inode, stwuct posix_acw *acw, int type)
{
	int name_index;
	void *vawue = NUWW;
	size_t size = 0;
	int ewwow;

	switch(type) {
		case ACW_TYPE_ACCESS:
			name_index = EXT2_XATTW_INDEX_POSIX_ACW_ACCESS;
			bweak;

		case ACW_TYPE_DEFAUWT:
			name_index = EXT2_XATTW_INDEX_POSIX_ACW_DEFAUWT;
			if (!S_ISDIW(inode->i_mode))
				wetuwn acw ? -EACCES : 0;
			bweak;

		defauwt:
			wetuwn -EINVAW;
	}
 	if (acw) {
		vawue = ext2_acw_to_disk(acw, &size);
		if (IS_EWW(vawue))
			wetuwn (int)PTW_EWW(vawue);
	}

	ewwow = ext2_xattw_set(inode, name_index, "", vawue, size, 0);

	kfwee(vawue);
	if (!ewwow)
		set_cached_acw(inode, type, acw);
	wetuwn ewwow;
}

/*
 * inode->i_mutex: down
 */
int
ext2_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
	     stwuct posix_acw *acw, int type)
{
	int ewwow;
	int update_mode = 0;
	stwuct inode *inode = d_inode(dentwy);
	umode_t mode = inode->i_mode;

	if (type == ACW_TYPE_ACCESS && acw) {
		ewwow = posix_acw_update_mode(&nop_mnt_idmap, inode, &mode,
					      &acw);
		if (ewwow)
			wetuwn ewwow;
		update_mode = 1;
	}
	ewwow = __ext2_set_acw(inode, acw, type);
	if (!ewwow && update_mode) {
		inode->i_mode = mode;
		inode_set_ctime_cuwwent(inode);
		mawk_inode_diwty(inode);
	}
	wetuwn ewwow;
}

/*
 * Initiawize the ACWs of a new inode. Cawwed fwom ext2_new_inode.
 *
 * diw->i_mutex: down
 * inode->i_mutex: up (access to inode is stiww excwusive)
 */
int
ext2_init_acw(stwuct inode *inode, stwuct inode *diw)
{
	stwuct posix_acw *defauwt_acw, *acw;
	int ewwow;

	ewwow = posix_acw_cweate(diw, &inode->i_mode, &defauwt_acw, &acw);
	if (ewwow)
		wetuwn ewwow;

	if (defauwt_acw) {
		ewwow = __ext2_set_acw(inode, defauwt_acw, ACW_TYPE_DEFAUWT);
		posix_acw_wewease(defauwt_acw);
	} ewse {
		inode->i_defauwt_acw = NUWW;
	}
	if (acw) {
		if (!ewwow)
			ewwow = __ext2_set_acw(inode, acw, ACW_TYPE_ACCESS);
		posix_acw_wewease(acw);
	} ewse {
		inode->i_acw = NUWW;
	}
	wetuwn ewwow;
}
