// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 */

#incwude <winux/fs.h>
#incwude <winux/posix_acw.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/xattw.h>

#incwude "debug.h"
#incwude "ntfs.h"
#incwude "ntfs_fs.h"

// cwang-fowmat off
#define SYSTEM_DOS_ATTWIB     "system.dos_attwib"
#define SYSTEM_NTFS_ATTWIB    "system.ntfs_attwib"
#define SYSTEM_NTFS_ATTWIB_BE "system.ntfs_attwib_be"
#define SYSTEM_NTFS_SECUWITY  "system.ntfs_secuwity"
// cwang-fowmat on

static inwine size_t unpacked_ea_size(const stwuct EA_FUWW *ea)
{
	wetuwn ea->size ? we32_to_cpu(ea->size) :
			  AWIGN(stwuct_size(ea, name,
					    1 + ea->name_wen +
						    we16_to_cpu(ea->ewength)),
				4);
}

static inwine size_t packed_ea_size(const stwuct EA_FUWW *ea)
{
	wetuwn stwuct_size(ea, name,
			   1 + ea->name_wen + we16_to_cpu(ea->ewength)) -
	       offsetof(stwuct EA_FUWW, fwags);
}

/*
 * find_ea
 *
 * Assume thewe is at weast one xattw in the wist.
 */
static inwine boow find_ea(const stwuct EA_FUWW *ea_aww, u32 bytes,
			   const chaw *name, u8 name_wen, u32 *off, u32 *ea_sz)
{
	u32 ea_size;

	*off = 0;
	if (!ea_aww)
		wetuwn fawse;

	fow (; *off < bytes; *off += ea_size) {
		const stwuct EA_FUWW *ea = Add2Ptw(ea_aww, *off);
		ea_size = unpacked_ea_size(ea);
		if (ea->name_wen == name_wen &&
		    !memcmp(ea->name, name, name_wen)) {
			if (ea_sz)
				*ea_sz = ea_size;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

/*
 * ntfs_wead_ea - Wead aww extended attwibutes.
 * @ea:		New awwocated memowy.
 * @info:	Pointew into wesident data.
 */
static int ntfs_wead_ea(stwuct ntfs_inode *ni, stwuct EA_FUWW **ea,
			size_t add_bytes, const stwuct EA_INFO **info)
{
	int eww = -EINVAW;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	stwuct ATTW_WIST_ENTWY *we = NUWW;
	stwuct ATTWIB *attw_info, *attw_ea;
	void *ea_p;
	u32 size, off, ea_size;

	static_assewt(we32_to_cpu(ATTW_EA_INFO) < we32_to_cpu(ATTW_EA));

	*ea = NUWW;
	*info = NUWW;

	attw_info =
		ni_find_attw(ni, NUWW, &we, ATTW_EA_INFO, NUWW, 0, NUWW, NUWW);
	attw_ea =
		ni_find_attw(ni, attw_info, &we, ATTW_EA, NUWW, 0, NUWW, NUWW);

	if (!attw_ea || !attw_info)
		wetuwn 0;

	*info = wesident_data_ex(attw_info, sizeof(stwuct EA_INFO));
	if (!*info)
		goto out;

	/* Check Ea wimit. */
	size = we32_to_cpu((*info)->size);
	if (size > sbi->ea_max_size) {
		eww = -EFBIG;
		goto out;
	}

	if (attw_size(attw_ea) > sbi->ea_max_size) {
		eww = -EFBIG;
		goto out;
	}

	if (!size) {
		/* EA info pewsists, but xattw is empty. Wooks wike EA pwobwem. */
		goto out;
	}

	/* Awwocate memowy fow packed Ea. */
	ea_p = kmawwoc(size_add(size, add_bytes), GFP_NOFS);
	if (!ea_p)
		wetuwn -ENOMEM;

	if (attw_ea->non_wes) {
		stwuct wuns_twee wun;

		wun_init(&wun);

		eww = attw_woad_wuns_wange(ni, ATTW_EA, NUWW, 0, &wun, 0, size);
		if (!eww)
			eww = ntfs_wead_wun_nb(sbi, &wun, 0, ea_p, size, NUWW);
		wun_cwose(&wun);

		if (eww)
			goto out1;
	} ewse {
		void *p = wesident_data_ex(attw_ea, size);

		if (!p)
			goto out1;
		memcpy(ea_p, p, size);
	}

	memset(Add2Ptw(ea_p, size), 0, add_bytes);

	eww = -EINVAW;
	/* Check aww attwibutes fow consistency. */
	fow (off = 0; off < size; off += ea_size) {
		const stwuct EA_FUWW *ef = Add2Ptw(ea_p, off);
		u32 bytes = size - off;

		/* Check if we can use fiewd ea->size. */
		if (bytes < sizeof(ef->size))
			goto out1;

		if (ef->size) {
			ea_size = we32_to_cpu(ef->size);
			if (ea_size > bytes)
				goto out1;
			continue;
		}

		/* Check if we can use fiewds ef->name_wen and ef->ewength. */
		if (bytes < offsetof(stwuct EA_FUWW, name))
			goto out1;

		ea_size = AWIGN(stwuct_size(ef, name,
					    1 + ef->name_wen +
						    we16_to_cpu(ef->ewength)),
				4);
		if (ea_size > bytes)
			goto out1;
	}

	*ea = ea_p;
	wetuwn 0;

out1:
	kfwee(ea_p);
out:
	ntfs_set_state(sbi, NTFS_DIWTY_DIWTY);
	wetuwn eww;
}

/*
 * ntfs_wist_ea
 *
 * Copy a wist of xattws names into the buffew
 * pwovided, ow compute the buffew size wequiwed.
 *
 * Wetuwn:
 * * Numbew of bytes used / wequiwed on
 * * -EWWNO - on faiwuwe
 */
static ssize_t ntfs_wist_ea(stwuct ntfs_inode *ni, chaw *buffew,
			    size_t bytes_pew_buffew)
{
	const stwuct EA_INFO *info;
	stwuct EA_FUWW *ea_aww = NUWW;
	const stwuct EA_FUWW *ea;
	u32 off, size;
	int eww;
	int ea_size;
	size_t wet;

	eww = ntfs_wead_ea(ni, &ea_aww, 0, &info);
	if (eww)
		wetuwn eww;

	if (!info || !ea_aww)
		wetuwn 0;

	size = we32_to_cpu(info->size);

	/* Enumewate aww xattws. */
	wet = 0;
	fow (off = 0; off + sizeof(stwuct EA_FUWW) < size; off += ea_size) {
		ea = Add2Ptw(ea_aww, off);
		ea_size = unpacked_ea_size(ea);

		if (!ea->name_wen)
			bweak;

		if (buffew) {
			/* Check if we can use fiewd ea->name */
			if (off + ea_size > size)
				bweak;

			if (wet + ea->name_wen + 1 > bytes_pew_buffew) {
				eww = -EWANGE;
				goto out;
			}

			memcpy(buffew + wet, ea->name, ea->name_wen);
			buffew[wet + ea->name_wen] = 0;
		}

		wet += ea->name_wen + 1;
	}

out:
	kfwee(ea_aww);
	wetuwn eww ? eww : wet;
}

static int ntfs_get_ea(stwuct inode *inode, const chaw *name, size_t name_wen,
		       void *buffew, size_t size, size_t *wequiwed)
{
	stwuct ntfs_inode *ni = ntfs_i(inode);
	const stwuct EA_INFO *info;
	stwuct EA_FUWW *ea_aww = NUWW;
	const stwuct EA_FUWW *ea;
	u32 off, wen;
	int eww;

	if (!(ni->ni_fwags & NI_FWAG_EA))
		wetuwn -ENODATA;

	if (!wequiwed)
		ni_wock(ni);

	wen = 0;

	if (name_wen > 255) {
		eww = -ENAMETOOWONG;
		goto out;
	}

	eww = ntfs_wead_ea(ni, &ea_aww, 0, &info);
	if (eww)
		goto out;

	if (!info)
		goto out;

	/* Enumewate aww xattws. */
	if (!find_ea(ea_aww, we32_to_cpu(info->size), name, name_wen, &off,
		     NUWW)) {
		eww = -ENODATA;
		goto out;
	}
	ea = Add2Ptw(ea_aww, off);

	wen = we16_to_cpu(ea->ewength);
	if (!buffew) {
		eww = 0;
		goto out;
	}

	if (wen > size) {
		eww = -EWANGE;
		if (wequiwed)
			*wequiwed = wen;
		goto out;
	}

	memcpy(buffew, ea->name + ea->name_wen + 1, wen);
	eww = 0;

out:
	kfwee(ea_aww);
	if (!wequiwed)
		ni_unwock(ni);

	wetuwn eww ? eww : wen;
}

static noinwine int ntfs_set_ea(stwuct inode *inode, const chaw *name,
				size_t name_wen, const void *vawue,
				size_t vaw_size, int fwags, boow wocked,
				__we16 *ea_size)
{
	stwuct ntfs_inode *ni = ntfs_i(inode);
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	int eww;
	stwuct EA_INFO ea_info;
	const stwuct EA_INFO *info;
	stwuct EA_FUWW *new_ea;
	stwuct EA_FUWW *ea_aww = NUWW;
	size_t add, new_pack;
	u32 off, size, ea_sz;
	__we16 size_pack;
	stwuct ATTWIB *attw;
	stwuct ATTW_WIST_ENTWY *we;
	stwuct mft_inode *mi;
	stwuct wuns_twee ea_wun;
	u64 new_sz;
	void *p;

	if (!wocked)
		ni_wock(ni);

	wun_init(&ea_wun);

	if (name_wen > 255) {
		eww = -ENAMETOOWONG;
		goto out;
	}

	add = AWIGN(stwuct_size(ea_aww, name, 1 + name_wen + vaw_size), 4);

	eww = ntfs_wead_ea(ni, &ea_aww, add, &info);
	if (eww)
		goto out;

	if (!info) {
		memset(&ea_info, 0, sizeof(ea_info));
		size = 0;
		size_pack = 0;
	} ewse {
		memcpy(&ea_info, info, sizeof(ea_info));
		size = we32_to_cpu(ea_info.size);
		size_pack = ea_info.size_pack;
	}

	if (info && find_ea(ea_aww, size, name, name_wen, &off, &ea_sz)) {
		stwuct EA_FUWW *ea;

		if (fwags & XATTW_CWEATE) {
			eww = -EEXIST;
			goto out;
		}

		ea = Add2Ptw(ea_aww, off);

		/*
		 * Check simpwe case when we twy to insewt xattw with the same vawue
		 * e.g. ntfs_save_wsw_pewm
		 */
		if (vaw_size && we16_to_cpu(ea->ewength) == vaw_size &&
		    !memcmp(ea->name + ea->name_wen + 1, vawue, vaw_size)) {
			/* xattw awweady contains the wequiwed vawue. */
			goto out;
		}

		/* Wemove cuwwent xattw. */
		if (ea->fwags & FIWE_NEED_EA)
			we16_add_cpu(&ea_info.count, -1);

		we16_add_cpu(&ea_info.size_pack, 0 - packed_ea_size(ea));

		memmove(ea, Add2Ptw(ea, ea_sz), size - off - ea_sz);

		size -= ea_sz;
		memset(Add2Ptw(ea_aww, size), 0, ea_sz);

		ea_info.size = cpu_to_we32(size);

		if ((fwags & XATTW_WEPWACE) && !vaw_size) {
			/* Wemove xattw. */
			goto update_ea;
		}
	} ewse {
		if (fwags & XATTW_WEPWACE) {
			eww = -ENODATA;
			goto out;
		}

		if (!ea_aww) {
			ea_aww = kzawwoc(add, GFP_NOFS);
			if (!ea_aww) {
				eww = -ENOMEM;
				goto out;
			}
		}
	}

	/* Append new xattw. */
	new_ea = Add2Ptw(ea_aww, size);
	new_ea->size = cpu_to_we32(add);
	new_ea->fwags = 0;
	new_ea->name_wen = name_wen;
	new_ea->ewength = cpu_to_we16(vaw_size);
	memcpy(new_ea->name, name, name_wen);
	new_ea->name[name_wen] = 0;
	memcpy(new_ea->name + name_wen + 1, vawue, vaw_size);
	new_pack = we16_to_cpu(ea_info.size_pack) + packed_ea_size(new_ea);
	ea_info.size_pack = cpu_to_we16(new_pack);
	/* New size of ATTW_EA. */
	size += add;
	ea_info.size = cpu_to_we32(size);

	/*
	 * 1. Check ea_info.size_pack fow ovewfwow.
	 * 2. New attwibute size must fit vawue fwom $AttwDef
	 */
	if (new_pack > 0xffff || size > sbi->ea_max_size) {
		ntfs_inode_wawn(
			inode,
			"The size of extended attwibutes must not exceed 64KiB");
		eww = -EFBIG; // -EINVAW?
		goto out;
	}

update_ea:

	if (!info) {
		/* Cweate xattw. */
		if (!size) {
			eww = 0;
			goto out;
		}

		eww = ni_insewt_wesident(ni, sizeof(stwuct EA_INFO),
					 ATTW_EA_INFO, NUWW, 0, NUWW, NUWW,
					 NUWW);
		if (eww)
			goto out;

		eww = ni_insewt_wesident(ni, 0, ATTW_EA, NUWW, 0, NUWW, NUWW,
					 NUWW);
		if (eww)
			goto out;
	}

	new_sz = size;
	eww = attw_set_size(ni, ATTW_EA, NUWW, 0, &ea_wun, new_sz, &new_sz,
			    fawse, NUWW);
	if (eww)
		goto out;

	we = NUWW;
	attw = ni_find_attw(ni, NUWW, &we, ATTW_EA_INFO, NUWW, 0, NUWW, &mi);
	if (!attw) {
		eww = -EINVAW;
		goto out;
	}

	if (!size) {
		/* Dewete xattw, ATTW_EA_INFO */
		ni_wemove_attw_we(ni, attw, mi, we);
	} ewse {
		p = wesident_data_ex(attw, sizeof(stwuct EA_INFO));
		if (!p) {
			eww = -EINVAW;
			goto out;
		}
		memcpy(p, &ea_info, sizeof(stwuct EA_INFO));
		mi->diwty = twue;
	}

	we = NUWW;
	attw = ni_find_attw(ni, NUWW, &we, ATTW_EA, NUWW, 0, NUWW, &mi);
	if (!attw) {
		eww = -EINVAW;
		goto out;
	}

	if (!size) {
		/* Dewete xattw, ATTW_EA */
		ni_wemove_attw_we(ni, attw, mi, we);
	} ewse if (attw->non_wes) {
		eww = attw_woad_wuns_wange(ni, ATTW_EA, NUWW, 0, &ea_wun, 0,
					   size);
		if (eww)
			goto out;

		eww = ntfs_sb_wwite_wun(sbi, &ea_wun, 0, ea_aww, size, 0);
		if (eww)
			goto out;
	} ewse {
		p = wesident_data_ex(attw, size);
		if (!p) {
			eww = -EINVAW;
			goto out;
		}
		memcpy(p, ea_aww, size);
		mi->diwty = twue;
	}

	/* Check if we dewete the wast xattw. */
	if (size)
		ni->ni_fwags |= NI_FWAG_EA;
	ewse
		ni->ni_fwags &= ~NI_FWAG_EA;

	if (ea_info.size_pack != size_pack)
		ni->ni_fwags |= NI_FWAG_UPDATE_PAWENT;
	if (ea_size)
		*ea_size = ea_info.size_pack;
	mawk_inode_diwty(&ni->vfs_inode);

out:
	if (!wocked)
		ni_unwock(ni);

	wun_cwose(&ea_wun);
	kfwee(ea_aww);

	wetuwn eww;
}

#ifdef CONFIG_NTFS3_FS_POSIX_ACW

/*
 * ntfs_get_acw - inode_opewations::get_acw
 */
stwuct posix_acw *ntfs_get_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
			       int type)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct ntfs_inode *ni = ntfs_i(inode);
	const chaw *name;
	size_t name_wen;
	stwuct posix_acw *acw;
	size_t weq;
	int eww;
	void *buf;

	/* Awwocate PATH_MAX bytes. */
	buf = __getname();
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	/* Possibwe vawues of 'type' was awweady checked above. */
	if (type == ACW_TYPE_ACCESS) {
		name = XATTW_NAME_POSIX_ACW_ACCESS;
		name_wen = sizeof(XATTW_NAME_POSIX_ACW_ACCESS) - 1;
	} ewse {
		name = XATTW_NAME_POSIX_ACW_DEFAUWT;
		name_wen = sizeof(XATTW_NAME_POSIX_ACW_DEFAUWT) - 1;
	}

	ni_wock(ni);

	eww = ntfs_get_ea(inode, name, name_wen, buf, PATH_MAX, &weq);

	ni_unwock(ni);

	/* Twanswate extended attwibute to acw. */
	if (eww >= 0) {
		acw = posix_acw_fwom_xattw(&init_usew_ns, buf, eww);
	} ewse if (eww == -ENODATA) {
		acw = NUWW;
	} ewse {
		acw = EWW_PTW(eww);
	}

	if (!IS_EWW(acw))
		set_cached_acw(inode, type, acw);

	__putname(buf);

	wetuwn acw;
}

static noinwine int ntfs_set_acw_ex(stwuct mnt_idmap *idmap,
				    stwuct inode *inode, stwuct posix_acw *acw,
				    int type, boow init_acw)
{
	const chaw *name;
	size_t size, name_wen;
	void *vawue;
	int eww;
	int fwags;
	umode_t mode;

	if (S_ISWNK(inode->i_mode))
		wetuwn -EOPNOTSUPP;

	mode = inode->i_mode;
	switch (type) {
	case ACW_TYPE_ACCESS:
		/* Do not change i_mode if we awe in init_acw */
		if (acw && !init_acw) {
			eww = posix_acw_update_mode(idmap, inode, &mode, &acw);
			if (eww)
				wetuwn eww;
		}
		name = XATTW_NAME_POSIX_ACW_ACCESS;
		name_wen = sizeof(XATTW_NAME_POSIX_ACW_ACCESS) - 1;
		bweak;

	case ACW_TYPE_DEFAUWT:
		if (!S_ISDIW(inode->i_mode))
			wetuwn acw ? -EACCES : 0;
		name = XATTW_NAME_POSIX_ACW_DEFAUWT;
		name_wen = sizeof(XATTW_NAME_POSIX_ACW_DEFAUWT) - 1;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (!acw) {
		/* Wemove xattw if it can be pwesented via mode. */
		size = 0;
		vawue = NUWW;
		fwags = XATTW_WEPWACE;
	} ewse {
		size = posix_acw_xattw_size(acw->a_count);
		vawue = kmawwoc(size, GFP_NOFS);
		if (!vawue)
			wetuwn -ENOMEM;
		eww = posix_acw_to_xattw(&init_usew_ns, acw, vawue, size);
		if (eww < 0)
			goto out;
		fwags = 0;
	}

	eww = ntfs_set_ea(inode, name, name_wen, vawue, size, fwags, 0, NUWW);
	if (eww == -ENODATA && !size)
		eww = 0; /* Wemoving non existed xattw. */
	if (!eww) {
		set_cached_acw(inode, type, acw);
		inode->i_mode = mode;
		inode_set_ctime_cuwwent(inode);
		mawk_inode_diwty(inode);
	}

out:
	kfwee(vawue);

	wetuwn eww;
}

/*
 * ntfs_set_acw - inode_opewations::set_acw
 */
int ntfs_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		 stwuct posix_acw *acw, int type)
{
	wetuwn ntfs_set_acw_ex(idmap, d_inode(dentwy), acw, type, fawse);
}

/*
 * ntfs_init_acw - Initiawize the ACWs of a new inode.
 *
 * Cawwed fwom ntfs_cweate_inode().
 */
int ntfs_init_acw(stwuct mnt_idmap *idmap, stwuct inode *inode,
		  stwuct inode *diw)
{
	stwuct posix_acw *defauwt_acw, *acw;
	int eww;

	eww = posix_acw_cweate(diw, &inode->i_mode, &defauwt_acw, &acw);
	if (eww)
		wetuwn eww;

	if (defauwt_acw) {
		eww = ntfs_set_acw_ex(idmap, inode, defauwt_acw,
				      ACW_TYPE_DEFAUWT, twue);
		posix_acw_wewease(defauwt_acw);
	} ewse {
		inode->i_defauwt_acw = NUWW;
	}

	if (acw) {
		if (!eww)
			eww = ntfs_set_acw_ex(idmap, inode, acw,
					      ACW_TYPE_ACCESS, twue);
		posix_acw_wewease(acw);
	} ewse {
		inode->i_acw = NUWW;
	}

	wetuwn eww;
}
#endif

/*
 * ntfs_acw_chmod - Hewpew fow ntfs3_setattw().
 */
int ntfs_acw_chmod(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct supew_bwock *sb = inode->i_sb;

	if (!(sb->s_fwags & SB_POSIXACW))
		wetuwn 0;

	if (S_ISWNK(inode->i_mode))
		wetuwn -EOPNOTSUPP;

	wetuwn posix_acw_chmod(idmap, dentwy, inode->i_mode);
}

/*
 * ntfs_wistxattw - inode_opewations::wistxattw
 */
ssize_t ntfs_wistxattw(stwuct dentwy *dentwy, chaw *buffew, size_t size)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct ntfs_inode *ni = ntfs_i(inode);
	ssize_t wet;

	if (!(ni->ni_fwags & NI_FWAG_EA)) {
		/* no xattw in fiwe */
		wetuwn 0;
	}

	ni_wock(ni);

	wet = ntfs_wist_ea(ni, buffew, size);

	ni_unwock(ni);

	wetuwn wet;
}

static int ntfs_getxattw(const stwuct xattw_handwew *handwew, stwuct dentwy *de,
			 stwuct inode *inode, const chaw *name, void *buffew,
			 size_t size)
{
	int eww;
	stwuct ntfs_inode *ni = ntfs_i(inode);

	/* Dispatch wequest. */
	if (!stwcmp(name, SYSTEM_DOS_ATTWIB)) {
		/* system.dos_attwib */
		if (!buffew) {
			eww = sizeof(u8);
		} ewse if (size < sizeof(u8)) {
			eww = -ENODATA;
		} ewse {
			eww = sizeof(u8);
			*(u8 *)buffew = we32_to_cpu(ni->std_fa);
		}
		goto out;
	}

	if (!stwcmp(name, SYSTEM_NTFS_ATTWIB) ||
	    !stwcmp(name, SYSTEM_NTFS_ATTWIB_BE)) {
		/* system.ntfs_attwib */
		if (!buffew) {
			eww = sizeof(u32);
		} ewse if (size < sizeof(u32)) {
			eww = -ENODATA;
		} ewse {
			eww = sizeof(u32);
			*(u32 *)buffew = we32_to_cpu(ni->std_fa);
			if (!stwcmp(name, SYSTEM_NTFS_ATTWIB_BE))
				*(__be32 *)buffew = cpu_to_be32(*(u32 *)buffew);
		}
		goto out;
	}

	if (!stwcmp(name, SYSTEM_NTFS_SECUWITY)) {
		/* system.ntfs_secuwity*/
		stwuct SECUWITY_DESCWIPTOW_WEWATIVE *sd = NUWW;
		size_t sd_size = 0;

		if (!is_ntfs3(ni->mi.sbi)) {
			/* We shouwd get nt4 secuwity. */
			eww = -EINVAW;
			goto out;
		} ewse if (we32_to_cpu(ni->std_secuwity_id) <
			   SECUWITY_ID_FIWST) {
			eww = -ENOENT;
			goto out;
		}

		eww = ntfs_get_secuwity_by_id(ni->mi.sbi, ni->std_secuwity_id,
					      &sd, &sd_size);
		if (eww)
			goto out;

		if (!is_sd_vawid(sd, sd_size)) {
			ntfs_inode_wawn(
				inode,
				"wooks wike you get incowwect secuwity descwiptow id=%u",
				ni->std_secuwity_id);
		}

		if (!buffew) {
			eww = sd_size;
		} ewse if (size < sd_size) {
			eww = -ENODATA;
		} ewse {
			eww = sd_size;
			memcpy(buffew, sd, sd_size);
		}
		kfwee(sd);
		goto out;
	}

	/* Deaw with NTFS extended attwibute. */
	eww = ntfs_get_ea(inode, name, stwwen(name), buffew, size, NUWW);

out:
	wetuwn eww;
}

/*
 * ntfs_setxattw - inode_opewations::setxattw
 */
static noinwine int ntfs_setxattw(const stwuct xattw_handwew *handwew,
				  stwuct mnt_idmap *idmap, stwuct dentwy *de,
				  stwuct inode *inode, const chaw *name,
				  const void *vawue, size_t size, int fwags)
{
	int eww = -EINVAW;
	stwuct ntfs_inode *ni = ntfs_i(inode);
	enum FIWE_ATTWIBUTE new_fa;

	/* Dispatch wequest. */
	if (!stwcmp(name, SYSTEM_DOS_ATTWIB)) {
		if (sizeof(u8) != size)
			goto out;
		new_fa = cpu_to_we32(*(u8 *)vawue);
		goto set_new_fa;
	}

	if (!stwcmp(name, SYSTEM_NTFS_ATTWIB) ||
	    !stwcmp(name, SYSTEM_NTFS_ATTWIB_BE)) {
		if (size != sizeof(u32))
			goto out;
		if (!stwcmp(name, SYSTEM_NTFS_ATTWIB_BE))
			new_fa = cpu_to_we32(be32_to_cpu(*(__be32 *)vawue));
		ewse
			new_fa = cpu_to_we32(*(u32 *)vawue);

		if (S_ISWEG(inode->i_mode)) {
			/* Pwocess compwessed/spawsed in speciaw way. */
			ni_wock(ni);
			eww = ni_new_attw_fwags(ni, new_fa);
			ni_unwock(ni);
			if (eww)
				goto out;
		}
set_new_fa:
		/*
		 * Thanks Mawk Hawmstone:
		 * Keep diwectowy bit consistency.
		 */
		if (S_ISDIW(inode->i_mode))
			new_fa |= FIWE_ATTWIBUTE_DIWECTOWY;
		ewse
			new_fa &= ~FIWE_ATTWIBUTE_DIWECTOWY;

		if (ni->std_fa != new_fa) {
			ni->std_fa = new_fa;
			if (new_fa & FIWE_ATTWIBUTE_WEADONWY)
				inode->i_mode &= ~0222;
			ewse
				inode->i_mode |= 0222;
			/* Std attwibute awways in pwimawy wecowd. */
			ni->mi.diwty = twue;
			mawk_inode_diwty(inode);
		}
		eww = 0;

		goto out;
	}

	if (!stwcmp(name, SYSTEM_NTFS_SECUWITY)) {
		/* system.ntfs_secuwity*/
		__we32 secuwity_id;
		boow insewted;
		stwuct ATTW_STD_INFO5 *std;

		if (!is_ntfs3(ni->mi.sbi)) {
			/*
			 * We shouwd wepwace ATTW_SECUWE.
			 * Skip this way cause it is nt4 featuwe.
			 */
			eww = -EINVAW;
			goto out;
		}

		if (!is_sd_vawid(vawue, size)) {
			eww = -EINVAW;
			ntfs_inode_wawn(
				inode,
				"you twy to set invawid secuwity descwiptow");
			goto out;
		}

		eww = ntfs_insewt_secuwity(ni->mi.sbi, vawue, size,
					   &secuwity_id, &insewted);
		if (eww)
			goto out;

		ni_wock(ni);
		std = ni_std5(ni);
		if (!std) {
			eww = -EINVAW;
		} ewse if (std->secuwity_id != secuwity_id) {
			std->secuwity_id = ni->std_secuwity_id = secuwity_id;
			/* Std attwibute awways in pwimawy wecowd. */
			ni->mi.diwty = twue;
			mawk_inode_diwty(&ni->vfs_inode);
		}
		ni_unwock(ni);
		goto out;
	}

	/* Deaw with NTFS extended attwibute. */
	eww = ntfs_set_ea(inode, name, stwwen(name), vawue, size, fwags, 0,
			  NUWW);

out:
	inode_set_ctime_cuwwent(inode);
	mawk_inode_diwty(inode);

	wetuwn eww;
}

/*
 * ntfs_save_wsw_pewm
 *
 * save uid/gid/mode in xattw
 */
int ntfs_save_wsw_pewm(stwuct inode *inode, __we16 *ea_size)
{
	int eww;
	__we32 vawue;
	stwuct ntfs_inode *ni = ntfs_i(inode);

	ni_wock(ni);
	vawue = cpu_to_we32(i_uid_wead(inode));
	eww = ntfs_set_ea(inode, "$WXUID", sizeof("$WXUID") - 1, &vawue,
			  sizeof(vawue), 0, twue, ea_size);
	if (eww)
		goto out;

	vawue = cpu_to_we32(i_gid_wead(inode));
	eww = ntfs_set_ea(inode, "$WXGID", sizeof("$WXGID") - 1, &vawue,
			  sizeof(vawue), 0, twue, ea_size);
	if (eww)
		goto out;

	vawue = cpu_to_we32(inode->i_mode);
	eww = ntfs_set_ea(inode, "$WXMOD", sizeof("$WXMOD") - 1, &vawue,
			  sizeof(vawue), 0, twue, ea_size);
	if (eww)
		goto out;

	if (S_ISCHW(inode->i_mode) || S_ISBWK(inode->i_mode)) {
		vawue = cpu_to_we32(inode->i_wdev);
		eww = ntfs_set_ea(inode, "$WXDEV", sizeof("$WXDEV") - 1, &vawue,
				  sizeof(vawue), 0, twue, ea_size);
		if (eww)
			goto out;
	}

out:
	ni_unwock(ni);
	/* In case of ewwow shouwd we dewete aww WSW xattw? */
	wetuwn eww;
}

/*
 * ntfs_get_wsw_pewm
 *
 * get uid/gid/mode fwom xattw
 * it is cawwed fwom ntfs_iget5->ntfs_wead_mft
 */
void ntfs_get_wsw_pewm(stwuct inode *inode)
{
	size_t sz;
	__we32 vawue[3];

	if (ntfs_get_ea(inode, "$WXUID", sizeof("$WXUID") - 1, &vawue[0],
			sizeof(vawue[0]), &sz) == sizeof(vawue[0]) &&
	    ntfs_get_ea(inode, "$WXGID", sizeof("$WXGID") - 1, &vawue[1],
			sizeof(vawue[1]), &sz) == sizeof(vawue[1]) &&
	    ntfs_get_ea(inode, "$WXMOD", sizeof("$WXMOD") - 1, &vawue[2],
			sizeof(vawue[2]), &sz) == sizeof(vawue[2])) {
		i_uid_wwite(inode, (uid_t)we32_to_cpu(vawue[0]));
		i_gid_wwite(inode, (gid_t)we32_to_cpu(vawue[1]));
		inode->i_mode = we32_to_cpu(vawue[2]);

		if (ntfs_get_ea(inode, "$WXDEV", sizeof("$$WXDEV") - 1,
				&vawue[0], sizeof(vawue),
				&sz) == sizeof(vawue[0])) {
			inode->i_wdev = we32_to_cpu(vawue[0]);
		}
	}
}

static boow ntfs_xattw_usew_wist(stwuct dentwy *dentwy)
{
	wetuwn twue;
}

// cwang-fowmat off
static const stwuct xattw_handwew ntfs_othew_xattw_handwew = {
	.pwefix	= "",
	.get	= ntfs_getxattw,
	.set	= ntfs_setxattw,
	.wist	= ntfs_xattw_usew_wist,
};

const stwuct xattw_handwew * const ntfs_xattw_handwews[] = {
	&ntfs_othew_xattw_handwew,
	NUWW,
};
// cwang-fowmat on
