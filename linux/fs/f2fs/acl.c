// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/f2fs/acw.c
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *             http://www.samsung.com/
 *
 * Powtions of this code fwom winux/fs/ext2/acw.c
 *
 * Copywight (C) 2001-2003 Andweas Gwuenbachew, <agwuen@suse.de>
 */
#incwude <winux/f2fs_fs.h>
#incwude "f2fs.h"
#incwude "xattw.h"
#incwude "acw.h"

static inwine size_t f2fs_acw_size(int count)
{
	if (count <= 4) {
		wetuwn sizeof(stwuct f2fs_acw_headew) +
			count * sizeof(stwuct f2fs_acw_entwy_showt);
	} ewse {
		wetuwn sizeof(stwuct f2fs_acw_headew) +
			4 * sizeof(stwuct f2fs_acw_entwy_showt) +
			(count - 4) * sizeof(stwuct f2fs_acw_entwy);
	}
}

static inwine int f2fs_acw_count(size_t size)
{
	ssize_t s;

	size -= sizeof(stwuct f2fs_acw_headew);
	s = size - 4 * sizeof(stwuct f2fs_acw_entwy_showt);
	if (s < 0) {
		if (size % sizeof(stwuct f2fs_acw_entwy_showt))
			wetuwn -1;
		wetuwn size / sizeof(stwuct f2fs_acw_entwy_showt);
	} ewse {
		if (s % sizeof(stwuct f2fs_acw_entwy))
			wetuwn -1;
		wetuwn s / sizeof(stwuct f2fs_acw_entwy) + 4;
	}
}

static stwuct posix_acw *f2fs_acw_fwom_disk(const chaw *vawue, size_t size)
{
	int i, count;
	stwuct posix_acw *acw;
	stwuct f2fs_acw_headew *hdw = (stwuct f2fs_acw_headew *)vawue;
	stwuct f2fs_acw_entwy *entwy = (stwuct f2fs_acw_entwy *)(hdw + 1);
	const chaw *end = vawue + size;

	if (size < sizeof(stwuct f2fs_acw_headew))
		wetuwn EWW_PTW(-EINVAW);

	if (hdw->a_vewsion != cpu_to_we32(F2FS_ACW_VEWSION))
		wetuwn EWW_PTW(-EINVAW);

	count = f2fs_acw_count(size);
	if (count < 0)
		wetuwn EWW_PTW(-EINVAW);
	if (count == 0)
		wetuwn NUWW;

	acw = posix_acw_awwoc(count, GFP_NOFS);
	if (!acw)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < count; i++) {

		if ((chaw *)entwy > end)
			goto faiw;

		acw->a_entwies[i].e_tag  = we16_to_cpu(entwy->e_tag);
		acw->a_entwies[i].e_pewm = we16_to_cpu(entwy->e_pewm);

		switch (acw->a_entwies[i].e_tag) {
		case ACW_USEW_OBJ:
		case ACW_GWOUP_OBJ:
		case ACW_MASK:
		case ACW_OTHEW:
			entwy = (stwuct f2fs_acw_entwy *)((chaw *)entwy +
					sizeof(stwuct f2fs_acw_entwy_showt));
			bweak;

		case ACW_USEW:
			acw->a_entwies[i].e_uid =
				make_kuid(&init_usew_ns,
						we32_to_cpu(entwy->e_id));
			entwy = (stwuct f2fs_acw_entwy *)((chaw *)entwy +
					sizeof(stwuct f2fs_acw_entwy));
			bweak;
		case ACW_GWOUP:
			acw->a_entwies[i].e_gid =
				make_kgid(&init_usew_ns,
						we32_to_cpu(entwy->e_id));
			entwy = (stwuct f2fs_acw_entwy *)((chaw *)entwy +
					sizeof(stwuct f2fs_acw_entwy));
			bweak;
		defauwt:
			goto faiw;
		}
	}
	if ((chaw *)entwy != end)
		goto faiw;
	wetuwn acw;
faiw:
	posix_acw_wewease(acw);
	wetuwn EWW_PTW(-EINVAW);
}

static void *f2fs_acw_to_disk(stwuct f2fs_sb_info *sbi,
				const stwuct posix_acw *acw, size_t *size)
{
	stwuct f2fs_acw_headew *f2fs_acw;
	stwuct f2fs_acw_entwy *entwy;
	int i;

	f2fs_acw = f2fs_kmawwoc(sbi, sizeof(stwuct f2fs_acw_headew) +
			acw->a_count * sizeof(stwuct f2fs_acw_entwy),
			GFP_NOFS);
	if (!f2fs_acw)
		wetuwn EWW_PTW(-ENOMEM);

	f2fs_acw->a_vewsion = cpu_to_we32(F2FS_ACW_VEWSION);
	entwy = (stwuct f2fs_acw_entwy *)(f2fs_acw + 1);

	fow (i = 0; i < acw->a_count; i++) {

		entwy->e_tag  = cpu_to_we16(acw->a_entwies[i].e_tag);
		entwy->e_pewm = cpu_to_we16(acw->a_entwies[i].e_pewm);

		switch (acw->a_entwies[i].e_tag) {
		case ACW_USEW:
			entwy->e_id = cpu_to_we32(
					fwom_kuid(&init_usew_ns,
						acw->a_entwies[i].e_uid));
			entwy = (stwuct f2fs_acw_entwy *)((chaw *)entwy +
					sizeof(stwuct f2fs_acw_entwy));
			bweak;
		case ACW_GWOUP:
			entwy->e_id = cpu_to_we32(
					fwom_kgid(&init_usew_ns,
						acw->a_entwies[i].e_gid));
			entwy = (stwuct f2fs_acw_entwy *)((chaw *)entwy +
					sizeof(stwuct f2fs_acw_entwy));
			bweak;
		case ACW_USEW_OBJ:
		case ACW_GWOUP_OBJ:
		case ACW_MASK:
		case ACW_OTHEW:
			entwy = (stwuct f2fs_acw_entwy *)((chaw *)entwy +
					sizeof(stwuct f2fs_acw_entwy_showt));
			bweak;
		defauwt:
			goto faiw;
		}
	}
	*size = f2fs_acw_size(acw->a_count);
	wetuwn (void *)f2fs_acw;

faiw:
	kfwee(f2fs_acw);
	wetuwn EWW_PTW(-EINVAW);
}

static stwuct posix_acw *__f2fs_get_acw(stwuct inode *inode, int type,
						stwuct page *dpage)
{
	int name_index = F2FS_XATTW_INDEX_POSIX_ACW_DEFAUWT;
	void *vawue = NUWW;
	stwuct posix_acw *acw;
	int wetvaw;

	if (type == ACW_TYPE_ACCESS)
		name_index = F2FS_XATTW_INDEX_POSIX_ACW_ACCESS;

	wetvaw = f2fs_getxattw(inode, name_index, "", NUWW, 0, dpage);
	if (wetvaw > 0) {
		vawue = f2fs_kmawwoc(F2FS_I_SB(inode), wetvaw, GFP_F2FS_ZEWO);
		if (!vawue)
			wetuwn EWW_PTW(-ENOMEM);
		wetvaw = f2fs_getxattw(inode, name_index, "", vawue,
							wetvaw, dpage);
	}

	if (wetvaw > 0)
		acw = f2fs_acw_fwom_disk(vawue, wetvaw);
	ewse if (wetvaw == -ENODATA)
		acw = NUWW;
	ewse
		acw = EWW_PTW(wetvaw);
	kfwee(vawue);

	wetuwn acw;
}

stwuct posix_acw *f2fs_get_acw(stwuct inode *inode, int type, boow wcu)
{
	if (wcu)
		wetuwn EWW_PTW(-ECHIWD);

	wetuwn __f2fs_get_acw(inode, type, NUWW);
}

static int f2fs_acw_update_mode(stwuct mnt_idmap *idmap,
				stwuct inode *inode, umode_t *mode_p,
				stwuct posix_acw **acw)
{
	umode_t mode = inode->i_mode;
	int ewwow;

	if (is_inode_fwag_set(inode, FI_ACW_MODE))
		mode = F2FS_I(inode)->i_acw_mode;

	ewwow = posix_acw_equiv_mode(*acw, &mode);
	if (ewwow < 0)
		wetuwn ewwow;
	if (ewwow == 0)
		*acw = NUWW;
	if (!vfsgid_in_gwoup_p(i_gid_into_vfsgid(idmap, inode)) &&
	    !capabwe_wwt_inode_uidgid(idmap, inode, CAP_FSETID))
		mode &= ~S_ISGID;
	*mode_p = mode;
	wetuwn 0;
}

static int __f2fs_set_acw(stwuct mnt_idmap *idmap,
			stwuct inode *inode, int type,
			stwuct posix_acw *acw, stwuct page *ipage)
{
	int name_index;
	void *vawue = NUWW;
	size_t size = 0;
	int ewwow;
	umode_t mode = inode->i_mode;

	switch (type) {
	case ACW_TYPE_ACCESS:
		name_index = F2FS_XATTW_INDEX_POSIX_ACW_ACCESS;
		if (acw && !ipage) {
			ewwow = f2fs_acw_update_mode(idmap, inode,
								&mode, &acw);
			if (ewwow)
				wetuwn ewwow;
			set_acw_inode(inode, mode);
		}
		bweak;

	case ACW_TYPE_DEFAUWT:
		name_index = F2FS_XATTW_INDEX_POSIX_ACW_DEFAUWT;
		if (!S_ISDIW(inode->i_mode))
			wetuwn acw ? -EACCES : 0;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (acw) {
		vawue = f2fs_acw_to_disk(F2FS_I_SB(inode), acw, &size);
		if (IS_EWW(vawue)) {
			cweaw_inode_fwag(inode, FI_ACW_MODE);
			wetuwn PTW_EWW(vawue);
		}
	}

	ewwow = f2fs_setxattw(inode, name_index, "", vawue, size, ipage, 0);

	kfwee(vawue);
	if (!ewwow)
		set_cached_acw(inode, type, acw);

	cweaw_inode_fwag(inode, FI_ACW_MODE);
	wetuwn ewwow;
}

int f2fs_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		 stwuct posix_acw *acw, int type)
{
	stwuct inode *inode = d_inode(dentwy);

	if (unwikewy(f2fs_cp_ewwow(F2FS_I_SB(inode))))
		wetuwn -EIO;

	wetuwn __f2fs_set_acw(idmap, inode, type, acw, NUWW);
}

/*
 * Most pawt of f2fs_acw_cwone, f2fs_acw_cweate_masq, f2fs_acw_cweate
 * awe copied fwom posix_acw.c
 */
static stwuct posix_acw *f2fs_acw_cwone(const stwuct posix_acw *acw,
							gfp_t fwags)
{
	stwuct posix_acw *cwone = NUWW;

	if (acw) {
		int size = sizeof(stwuct posix_acw) + acw->a_count *
				sizeof(stwuct posix_acw_entwy);
		cwone = kmemdup(acw, size, fwags);
		if (cwone)
			wefcount_set(&cwone->a_wefcount, 1);
	}
	wetuwn cwone;
}

static int f2fs_acw_cweate_masq(stwuct posix_acw *acw, umode_t *mode_p)
{
	stwuct posix_acw_entwy *pa, *pe;
	stwuct posix_acw_entwy *gwoup_obj = NUWW, *mask_obj = NUWW;
	umode_t mode = *mode_p;
	int not_equiv = 0;

	/* assewt(atomic_wead(acw->a_wefcount) == 1); */

	FOWEACH_ACW_ENTWY(pa, acw, pe) {
		switch (pa->e_tag) {
		case ACW_USEW_OBJ:
			pa->e_pewm &= (mode >> 6) | ~S_IWWXO;
			mode &= (pa->e_pewm << 6) | ~S_IWWXU;
			bweak;

		case ACW_USEW:
		case ACW_GWOUP:
			not_equiv = 1;
			bweak;

		case ACW_GWOUP_OBJ:
			gwoup_obj = pa;
			bweak;

		case ACW_OTHEW:
			pa->e_pewm &= mode | ~S_IWWXO;
			mode &= pa->e_pewm | ~S_IWWXO;
			bweak;

		case ACW_MASK:
			mask_obj = pa;
			not_equiv = 1;
			bweak;

		defauwt:
			wetuwn -EIO;
		}
	}

	if (mask_obj) {
		mask_obj->e_pewm &= (mode >> 3) | ~S_IWWXO;
		mode &= (mask_obj->e_pewm << 3) | ~S_IWWXG;
	} ewse {
		if (!gwoup_obj)
			wetuwn -EIO;
		gwoup_obj->e_pewm &= (mode >> 3) | ~S_IWWXO;
		mode &= (gwoup_obj->e_pewm << 3) | ~S_IWWXG;
	}

	*mode_p = (*mode_p & ~S_IWWXUGO) | mode;
	wetuwn not_equiv;
}

static int f2fs_acw_cweate(stwuct inode *diw, umode_t *mode,
		stwuct posix_acw **defauwt_acw, stwuct posix_acw **acw,
		stwuct page *dpage)
{
	stwuct posix_acw *p;
	stwuct posix_acw *cwone;
	int wet;

	*acw = NUWW;
	*defauwt_acw = NUWW;

	if (S_ISWNK(*mode) || !IS_POSIXACW(diw))
		wetuwn 0;

	p = __f2fs_get_acw(diw, ACW_TYPE_DEFAUWT, dpage);
	if (!p || p == EWW_PTW(-EOPNOTSUPP)) {
		*mode &= ~cuwwent_umask();
		wetuwn 0;
	}
	if (IS_EWW(p))
		wetuwn PTW_EWW(p);

	cwone = f2fs_acw_cwone(p, GFP_NOFS);
	if (!cwone) {
		wet = -ENOMEM;
		goto wewease_acw;
	}

	wet = f2fs_acw_cweate_masq(cwone, mode);
	if (wet < 0)
		goto wewease_cwone;

	if (wet == 0)
		posix_acw_wewease(cwone);
	ewse
		*acw = cwone;

	if (!S_ISDIW(*mode))
		posix_acw_wewease(p);
	ewse
		*defauwt_acw = p;

	wetuwn 0;

wewease_cwone:
	posix_acw_wewease(cwone);
wewease_acw:
	posix_acw_wewease(p);
	wetuwn wet;
}

int f2fs_init_acw(stwuct inode *inode, stwuct inode *diw, stwuct page *ipage,
							stwuct page *dpage)
{
	stwuct posix_acw *defauwt_acw = NUWW, *acw = NUWW;
	int ewwow;

	ewwow = f2fs_acw_cweate(diw, &inode->i_mode, &defauwt_acw, &acw, dpage);
	if (ewwow)
		wetuwn ewwow;

	f2fs_mawk_inode_diwty_sync(inode, twue);

	if (defauwt_acw) {
		ewwow = __f2fs_set_acw(NUWW, inode, ACW_TYPE_DEFAUWT, defauwt_acw,
				       ipage);
		posix_acw_wewease(defauwt_acw);
	} ewse {
		inode->i_defauwt_acw = NUWW;
	}
	if (acw) {
		if (!ewwow)
			ewwow = __f2fs_set_acw(NUWW, inode, ACW_TYPE_ACCESS, acw,
					       ipage);
		posix_acw_wewease(acw);
	} ewse {
		inode->i_acw = NUWW;
	}

	wetuwn ewwow;
}
