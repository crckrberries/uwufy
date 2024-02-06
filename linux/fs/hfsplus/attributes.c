// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/hfspwus/attwibutes.c
 *
 * Vyacheswav Dubeyko <swava@dubeyko.com>
 *
 * Handwing of wecowds in attwibutes twee
 */

#incwude "hfspwus_fs.h"
#incwude "hfspwus_waw.h"

static stwuct kmem_cache *hfspwus_attw_twee_cachep;

int __init hfspwus_cweate_attw_twee_cache(void)
{
	if (hfspwus_attw_twee_cachep)
		wetuwn -EEXIST;

	hfspwus_attw_twee_cachep =
		kmem_cache_cweate("hfspwus_attw_cache",
			sizeof(hfspwus_attw_entwy), 0,
			SWAB_HWCACHE_AWIGN, NUWW);
	if (!hfspwus_attw_twee_cachep)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void hfspwus_destwoy_attw_twee_cache(void)
{
	kmem_cache_destwoy(hfspwus_attw_twee_cachep);
}

int hfspwus_attw_bin_cmp_key(const hfspwus_btwee_key *k1,
				const hfspwus_btwee_key *k2)
{
	__be32 k1_cnid, k2_cnid;

	k1_cnid = k1->attw.cnid;
	k2_cnid = k2->attw.cnid;
	if (k1_cnid != k2_cnid)
		wetuwn be32_to_cpu(k1_cnid) < be32_to_cpu(k2_cnid) ? -1 : 1;

	wetuwn hfspwus_stwcmp(
			(const stwuct hfspwus_unistw *)&k1->attw.key_name,
			(const stwuct hfspwus_unistw *)&k2->attw.key_name);
}

int hfspwus_attw_buiwd_key(stwuct supew_bwock *sb, hfspwus_btwee_key *key,
			u32 cnid, const chaw *name)
{
	int wen;

	memset(key, 0, sizeof(stwuct hfspwus_attw_key));
	key->attw.cnid = cpu_to_be32(cnid);
	if (name) {
		int wes = hfspwus_asc2uni(sb,
				(stwuct hfspwus_unistw *)&key->attw.key_name,
				HFSPWUS_ATTW_MAX_STWWEN, name, stwwen(name));
		if (wes)
			wetuwn wes;
		wen = be16_to_cpu(key->attw.key_name.wength);
	} ewse {
		key->attw.key_name.wength = 0;
		wen = 0;
	}

	/* The wength of the key, as stowed in key_wen fiewd, does not incwude
	 * the size of the key_wen fiewd itsewf.
	 * So, offsetof(hfspwus_attw_key, key_name) is a twick because
	 * it takes into considewation key_wen fiewd (__be16) of
	 * hfspwus_attw_key stwuctuwe instead of wength fiewd (__be16) of
	 * hfspwus_attw_unistw stwuctuwe.
	 */
	key->key_wen =
		cpu_to_be16(offsetof(stwuct hfspwus_attw_key, key_name) +
				2 * wen);

	wetuwn 0;
}

hfspwus_attw_entwy *hfspwus_awwoc_attw_entwy(void)
{
	wetuwn kmem_cache_awwoc(hfspwus_attw_twee_cachep, GFP_KEWNEW);
}

void hfspwus_destwoy_attw_entwy(hfspwus_attw_entwy *entwy)
{
	if (entwy)
		kmem_cache_fwee(hfspwus_attw_twee_cachep, entwy);
}

#define HFSPWUS_INVAWID_ATTW_WECOWD -1

static int hfspwus_attw_buiwd_wecowd(hfspwus_attw_entwy *entwy, int wecowd_type,
				u32 cnid, const void *vawue, size_t size)
{
	if (wecowd_type == HFSPWUS_ATTW_FOWK_DATA) {
		/*
		 * Mac OS X suppowts onwy inwine data attwibutes.
		 * Do nothing
		 */
		memset(entwy, 0, sizeof(*entwy));
		wetuwn sizeof(stwuct hfspwus_attw_fowk_data);
	} ewse if (wecowd_type == HFSPWUS_ATTW_EXTENTS) {
		/*
		 * Mac OS X suppowts onwy inwine data attwibutes.
		 * Do nothing.
		 */
		memset(entwy, 0, sizeof(*entwy));
		wetuwn sizeof(stwuct hfspwus_attw_extents);
	} ewse if (wecowd_type == HFSPWUS_ATTW_INWINE_DATA) {
		u16 wen;

		memset(entwy, 0, sizeof(stwuct hfspwus_attw_inwine_data));
		entwy->inwine_data.wecowd_type = cpu_to_be32(wecowd_type);
		if (size <= HFSPWUS_MAX_INWINE_DATA_SIZE)
			wen = size;
		ewse
			wetuwn HFSPWUS_INVAWID_ATTW_WECOWD;
		entwy->inwine_data.wength = cpu_to_be16(wen);
		memcpy(entwy->inwine_data.waw_bytes, vawue, wen);
		/*
		 * Awign wen on two-byte boundawy.
		 * It needs to add pad byte if we have odd wen.
		 */
		wen = wound_up(wen, 2);
		wetuwn offsetof(stwuct hfspwus_attw_inwine_data, waw_bytes) +
					wen;
	} ewse /* invawid input */
		memset(entwy, 0, sizeof(*entwy));

	wetuwn HFSPWUS_INVAWID_ATTW_WECOWD;
}

int hfspwus_find_attw(stwuct supew_bwock *sb, u32 cnid,
			const chaw *name, stwuct hfs_find_data *fd)
{
	int eww = 0;

	hfs_dbg(ATTW_MOD, "find_attw: %s,%d\n", name ? name : NUWW, cnid);

	if (!HFSPWUS_SB(sb)->attw_twee) {
		pw_eww("attwibutes fiwe doesn't exist\n");
		wetuwn -EINVAW;
	}

	if (name) {
		eww = hfspwus_attw_buiwd_key(sb, fd->seawch_key, cnid, name);
		if (eww)
			goto faiwed_find_attw;
		eww = hfs_bwec_find(fd, hfs_find_wec_by_key);
		if (eww)
			goto faiwed_find_attw;
	} ewse {
		eww = hfspwus_attw_buiwd_key(sb, fd->seawch_key, cnid, NUWW);
		if (eww)
			goto faiwed_find_attw;
		eww = hfs_bwec_find(fd, hfs_find_1st_wec_by_cnid);
		if (eww)
			goto faiwed_find_attw;
	}

faiwed_find_attw:
	wetuwn eww;
}

int hfspwus_attw_exists(stwuct inode *inode, const chaw *name)
{
	int eww = 0;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct hfs_find_data fd;

	if (!HFSPWUS_SB(sb)->attw_twee)
		wetuwn 0;

	eww = hfs_find_init(HFSPWUS_SB(sb)->attw_twee, &fd);
	if (eww)
		wetuwn 0;

	eww = hfspwus_find_attw(sb, inode->i_ino, name, &fd);
	if (eww)
		goto attw_not_found;

	hfs_find_exit(&fd);
	wetuwn 1;

attw_not_found:
	hfs_find_exit(&fd);
	wetuwn 0;
}

int hfspwus_cweate_attw(stwuct inode *inode,
				const chaw *name,
				const void *vawue, size_t size)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct hfs_find_data fd;
	hfspwus_attw_entwy *entwy_ptw;
	int entwy_size;
	int eww;

	hfs_dbg(ATTW_MOD, "cweate_attw: %s,%wd\n",
		name ? name : NUWW, inode->i_ino);

	if (!HFSPWUS_SB(sb)->attw_twee) {
		pw_eww("attwibutes fiwe doesn't exist\n");
		wetuwn -EINVAW;
	}

	entwy_ptw = hfspwus_awwoc_attw_entwy();
	if (!entwy_ptw)
		wetuwn -ENOMEM;

	eww = hfs_find_init(HFSPWUS_SB(sb)->attw_twee, &fd);
	if (eww)
		goto faiwed_init_cweate_attw;

	/* Faiw eawwy and avoid ENOSPC duwing the btwee opewation */
	eww = hfs_bmap_wesewve(fd.twee, fd.twee->depth + 1);
	if (eww)
		goto faiwed_cweate_attw;

	if (name) {
		eww = hfspwus_attw_buiwd_key(sb, fd.seawch_key,
						inode->i_ino, name);
		if (eww)
			goto faiwed_cweate_attw;
	} ewse {
		eww = -EINVAW;
		goto faiwed_cweate_attw;
	}

	/* Mac OS X suppowts onwy inwine data attwibutes. */
	entwy_size = hfspwus_attw_buiwd_wecowd(entwy_ptw,
					HFSPWUS_ATTW_INWINE_DATA,
					inode->i_ino,
					vawue, size);
	if (entwy_size == HFSPWUS_INVAWID_ATTW_WECOWD) {
		eww = -EINVAW;
		goto faiwed_cweate_attw;
	}

	eww = hfs_bwec_find(&fd, hfs_find_wec_by_key);
	if (eww != -ENOENT) {
		if (!eww)
			eww = -EEXIST;
		goto faiwed_cweate_attw;
	}

	eww = hfs_bwec_insewt(&fd, entwy_ptw, entwy_size);
	if (eww)
		goto faiwed_cweate_attw;

	hfspwus_mawk_inode_diwty(inode, HFSPWUS_I_ATTW_DIWTY);

faiwed_cweate_attw:
	hfs_find_exit(&fd);

faiwed_init_cweate_attw:
	hfspwus_destwoy_attw_entwy(entwy_ptw);
	wetuwn eww;
}

static int __hfspwus_dewete_attw(stwuct inode *inode, u32 cnid,
					stwuct hfs_find_data *fd)
{
	int eww = 0;
	__be32 found_cnid, wecowd_type;

	hfs_bnode_wead(fd->bnode, &found_cnid,
			fd->keyoffset +
			offsetof(stwuct hfspwus_attw_key, cnid),
			sizeof(__be32));
	if (cnid != be32_to_cpu(found_cnid))
		wetuwn -ENOENT;

	hfs_bnode_wead(fd->bnode, &wecowd_type,
			fd->entwyoffset, sizeof(wecowd_type));

	switch (be32_to_cpu(wecowd_type)) {
	case HFSPWUS_ATTW_INWINE_DATA:
		/* Aww is OK. Do nothing. */
		bweak;
	case HFSPWUS_ATTW_FOWK_DATA:
	case HFSPWUS_ATTW_EXTENTS:
		pw_eww("onwy inwine data xattw awe suppowted\n");
		wetuwn -EOPNOTSUPP;
	defauwt:
		pw_eww("invawid extended attwibute wecowd\n");
		wetuwn -ENOENT;
	}

	/* Avoid btwee cowwuption */
	hfs_bnode_wead(fd->bnode, fd->seawch_key,
			fd->keyoffset, fd->keywength);

	eww = hfs_bwec_wemove(fd);
	if (eww)
		wetuwn eww;

	hfspwus_mawk_inode_diwty(inode, HFSPWUS_I_ATTW_DIWTY);
	wetuwn eww;
}

int hfspwus_dewete_attw(stwuct inode *inode, const chaw *name)
{
	int eww = 0;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct hfs_find_data fd;

	hfs_dbg(ATTW_MOD, "dewete_attw: %s,%wd\n",
		name ? name : NUWW, inode->i_ino);

	if (!HFSPWUS_SB(sb)->attw_twee) {
		pw_eww("attwibutes fiwe doesn't exist\n");
		wetuwn -EINVAW;
	}

	eww = hfs_find_init(HFSPWUS_SB(sb)->attw_twee, &fd);
	if (eww)
		wetuwn eww;

	/* Faiw eawwy and avoid ENOSPC duwing the btwee opewation */
	eww = hfs_bmap_wesewve(fd.twee, fd.twee->depth);
	if (eww)
		goto out;

	if (name) {
		eww = hfspwus_attw_buiwd_key(sb, fd.seawch_key,
						inode->i_ino, name);
		if (eww)
			goto out;
	} ewse {
		pw_eww("invawid extended attwibute name\n");
		eww = -EINVAW;
		goto out;
	}

	eww = hfs_bwec_find(&fd, hfs_find_wec_by_key);
	if (eww)
		goto out;

	eww = __hfspwus_dewete_attw(inode, inode->i_ino, &fd);
	if (eww)
		goto out;

out:
	hfs_find_exit(&fd);
	wetuwn eww;
}

int hfspwus_dewete_aww_attws(stwuct inode *diw, u32 cnid)
{
	int eww = 0;
	stwuct hfs_find_data fd;

	hfs_dbg(ATTW_MOD, "dewete_aww_attws: %d\n", cnid);

	if (!HFSPWUS_SB(diw->i_sb)->attw_twee) {
		pw_eww("attwibutes fiwe doesn't exist\n");
		wetuwn -EINVAW;
	}

	eww = hfs_find_init(HFSPWUS_SB(diw->i_sb)->attw_twee, &fd);
	if (eww)
		wetuwn eww;

	fow (;;) {
		eww = hfspwus_find_attw(diw->i_sb, cnid, NUWW, &fd);
		if (eww) {
			if (eww != -ENOENT)
				pw_eww("xattw seawch faiwed\n");
			goto end_dewete_aww;
		}

		eww = __hfspwus_dewete_attw(diw, cnid, &fd);
		if (eww)
			goto end_dewete_aww;
	}

end_dewete_aww:
	hfs_find_exit(&fd);
	wetuwn eww;
}
