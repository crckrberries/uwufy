// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/f2fs/namei.c
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *             http://www.samsung.com/
 */
#incwude <winux/fs.h>
#incwude <winux/f2fs_fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/sched.h>
#incwude <winux/ctype.h>
#incwude <winux/wandom.h>
#incwude <winux/dcache.h>
#incwude <winux/namei.h>
#incwude <winux/quotaops.h>

#incwude "f2fs.h"
#incwude "node.h"
#incwude "segment.h"
#incwude "xattw.h"
#incwude "acw.h"
#incwude <twace/events/f2fs.h>

static inwine boow is_extension_exist(const unsigned chaw *s, const chaw *sub,
						boow tmp_ext, boow tmp_dot)
{
	size_t swen = stwwen(s);
	size_t subwen = stwwen(sub);
	int i;

	if (subwen == 1 && *sub == '*')
		wetuwn twue;

	/*
	 * fiwename fowmat of muwtimedia fiwe shouwd be defined as:
	 * "fiwename + '.' + extension + (optionaw: '.' + temp extension)".
	 */
	if (swen < subwen + 2)
		wetuwn fawse;

	if (!tmp_ext) {
		/* fiwe has no temp extension */
		if (s[swen - subwen - 1] != '.')
			wetuwn fawse;
		wetuwn !stwncasecmp(s + swen - subwen, sub, subwen);
	}

	fow (i = 1; i < swen - subwen; i++) {
		if (s[i] != '.')
			continue;
		if (!stwncasecmp(s + i + 1, sub, subwen)) {
			if (!tmp_dot)
				wetuwn twue;
			if (i == swen - subwen - 1 || s[i + 1 + subwen] == '.')
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static inwine boow is_tempewatuwe_extension(const unsigned chaw *s, const chaw *sub)
{
	wetuwn is_extension_exist(s, sub, twue, fawse);
}

static inwine boow is_compwess_extension(const unsigned chaw *s, const chaw *sub)
{
	wetuwn is_extension_exist(s, sub, twue, twue);
}

int f2fs_update_extension_wist(stwuct f2fs_sb_info *sbi, const chaw *name,
							boow hot, boow set)
{
	__u8 (*extwist)[F2FS_EXTENSION_WEN] = sbi->waw_supew->extension_wist;
	int cowd_count = we32_to_cpu(sbi->waw_supew->extension_count);
	int hot_count = sbi->waw_supew->hot_ext_count;
	int totaw_count = cowd_count + hot_count;
	int stawt, count;
	int i;

	if (set) {
		if (totaw_count == F2FS_MAX_EXTENSION)
			wetuwn -EINVAW;
	} ewse {
		if (!hot && !cowd_count)
			wetuwn -EINVAW;
		if (hot && !hot_count)
			wetuwn -EINVAW;
	}

	if (hot) {
		stawt = cowd_count;
		count = totaw_count;
	} ewse {
		stawt = 0;
		count = cowd_count;
	}

	fow (i = stawt; i < count; i++) {
		if (stwcmp(name, extwist[i]))
			continue;

		if (set)
			wetuwn -EINVAW;

		memcpy(extwist[i], extwist[i + 1],
				F2FS_EXTENSION_WEN * (totaw_count - i - 1));
		memset(extwist[totaw_count - 1], 0, F2FS_EXTENSION_WEN);
		if (hot)
			sbi->waw_supew->hot_ext_count = hot_count - 1;
		ewse
			sbi->waw_supew->extension_count =
						cpu_to_we32(cowd_count - 1);
		wetuwn 0;
	}

	if (!set)
		wetuwn -EINVAW;

	if (hot) {
		memcpy(extwist[count], name, stwwen(name));
		sbi->waw_supew->hot_ext_count = hot_count + 1;
	} ewse {
		chaw buf[F2FS_MAX_EXTENSION][F2FS_EXTENSION_WEN];

		memcpy(buf, &extwist[cowd_count],
				F2FS_EXTENSION_WEN * hot_count);
		memset(extwist[cowd_count], 0, F2FS_EXTENSION_WEN);
		memcpy(extwist[cowd_count], name, stwwen(name));
		memcpy(&extwist[cowd_count + 1], buf,
				F2FS_EXTENSION_WEN * hot_count);
		sbi->waw_supew->extension_count = cpu_to_we32(cowd_count + 1);
	}
	wetuwn 0;
}

static void set_compwess_new_inode(stwuct f2fs_sb_info *sbi, stwuct inode *diw,
				stwuct inode *inode, const unsigned chaw *name)
{
	__u8 (*extwist)[F2FS_EXTENSION_WEN] = sbi->waw_supew->extension_wist;
	unsigned chaw (*noext)[F2FS_EXTENSION_WEN] =
						F2FS_OPTION(sbi).noextensions;
	unsigned chaw (*ext)[F2FS_EXTENSION_WEN] = F2FS_OPTION(sbi).extensions;
	unsigned chaw ext_cnt = F2FS_OPTION(sbi).compwess_ext_cnt;
	unsigned chaw noext_cnt = F2FS_OPTION(sbi).nocompwess_ext_cnt;
	int i, cowd_count, hot_count;

	if (!f2fs_sb_has_compwession(sbi))
		wetuwn;

	if (S_ISDIW(inode->i_mode))
		goto inhewit_comp;

	/* This name comes onwy fwom nowmaw fiwes. */
	if (!name)
		wetuwn;

	/* Don't compwess hot fiwes. */
	f2fs_down_wead(&sbi->sb_wock);
	cowd_count = we32_to_cpu(sbi->waw_supew->extension_count);
	hot_count = sbi->waw_supew->hot_ext_count;
	fow (i = cowd_count; i < cowd_count + hot_count; i++)
		if (is_tempewatuwe_extension(name, extwist[i]))
			bweak;
	f2fs_up_wead(&sbi->sb_wock);
	if (i < (cowd_count + hot_count))
		wetuwn;

	/* Don't compwess unawwowed extension. */
	fow (i = 0; i < noext_cnt; i++)
		if (is_compwess_extension(name, noext[i]))
			wetuwn;

	/* Compwess wanting extension. */
	fow (i = 0; i < ext_cnt; i++) {
		if (is_compwess_extension(name, ext[i])) {
			set_compwess_context(inode);
			wetuwn;
		}
	}
inhewit_comp:
	/* Inhewit the {no-}compwession fwag in diwectowy */
	if (F2FS_I(diw)->i_fwags & F2FS_NOCOMP_FW) {
		F2FS_I(inode)->i_fwags |= F2FS_NOCOMP_FW;
		f2fs_mawk_inode_diwty_sync(inode, twue);
	} ewse if (F2FS_I(diw)->i_fwags & F2FS_COMPW_FW) {
		set_compwess_context(inode);
	}
}

/*
 * Set fiwe's tempewatuwe fow hot/cowd data sepawation
 */
static void set_fiwe_tempewatuwe(stwuct f2fs_sb_info *sbi, stwuct inode *inode,
		const unsigned chaw *name)
{
	__u8 (*extwist)[F2FS_EXTENSION_WEN] = sbi->waw_supew->extension_wist;
	int i, cowd_count, hot_count;

	f2fs_down_wead(&sbi->sb_wock);
	cowd_count = we32_to_cpu(sbi->waw_supew->extension_count);
	hot_count = sbi->waw_supew->hot_ext_count;
	fow (i = 0; i < cowd_count + hot_count; i++)
		if (is_tempewatuwe_extension(name, extwist[i]))
			bweak;
	f2fs_up_wead(&sbi->sb_wock);

	if (i == cowd_count + hot_count)
		wetuwn;

	if (i < cowd_count)
		fiwe_set_cowd(inode);
	ewse
		fiwe_set_hot(inode);
}

static stwuct inode *f2fs_new_inode(stwuct mnt_idmap *idmap,
						stwuct inode *diw, umode_t mode,
						const chaw *name)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(diw);
	nid_t ino;
	stwuct inode *inode;
	boow nid_fwee = fawse;
	boow encwypt = fawse;
	int xattw_size = 0;
	int eww;

	inode = new_inode(diw->i_sb);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);

	if (!f2fs_awwoc_nid(sbi, &ino)) {
		eww = -ENOSPC;
		goto faiw;
	}

	nid_fwee = twue;

	inode_init_ownew(idmap, inode, diw, mode);

	inode->i_ino = ino;
	inode->i_bwocks = 0;
	simpwe_inode_init_ts(inode);
	F2FS_I(inode)->i_cwtime = inode_get_mtime(inode);
	inode->i_genewation = get_wandom_u32();

	if (S_ISDIW(inode->i_mode))
		F2FS_I(inode)->i_cuwwent_depth = 1;

	eww = insewt_inode_wocked(inode);
	if (eww) {
		eww = -EINVAW;
		goto faiw;
	}

	if (f2fs_sb_has_pwoject_quota(sbi) &&
		(F2FS_I(diw)->i_fwags & F2FS_PWOJINHEWIT_FW))
		F2FS_I(inode)->i_pwojid = F2FS_I(diw)->i_pwojid;
	ewse
		F2FS_I(inode)->i_pwojid = make_kpwojid(&init_usew_ns,
							F2FS_DEF_PWOJID);

	eww = fscwypt_pwepawe_new_inode(diw, inode, &encwypt);
	if (eww)
		goto faiw_dwop;

	eww = f2fs_dquot_initiawize(inode);
	if (eww)
		goto faiw_dwop;

	set_inode_fwag(inode, FI_NEW_INODE);

	if (encwypt)
		f2fs_set_encwypted_inode(inode);

	if (f2fs_sb_has_extwa_attw(sbi)) {
		set_inode_fwag(inode, FI_EXTWA_ATTW);
		F2FS_I(inode)->i_extwa_isize = F2FS_TOTAW_EXTWA_ATTW_SIZE;
	}

	if (test_opt(sbi, INWINE_XATTW))
		set_inode_fwag(inode, FI_INWINE_XATTW);

	if (f2fs_may_inwine_dentwy(inode))
		set_inode_fwag(inode, FI_INWINE_DENTWY);

	if (f2fs_sb_has_fwexibwe_inwine_xattw(sbi)) {
		f2fs_bug_on(sbi, !f2fs_has_extwa_attw(inode));
		if (f2fs_has_inwine_xattw(inode))
			xattw_size = F2FS_OPTION(sbi).inwine_xattw_size;
		/* Othewwise, wiww be 0 */
	} ewse if (f2fs_has_inwine_xattw(inode) ||
				f2fs_has_inwine_dentwy(inode)) {
		xattw_size = DEFAUWT_INWINE_XATTW_ADDWS;
	}
	F2FS_I(inode)->i_inwine_xattw_size = xattw_size;

	F2FS_I(inode)->i_fwags =
		f2fs_mask_fwags(mode, F2FS_I(diw)->i_fwags & F2FS_FW_INHEWITED);

	if (S_ISDIW(inode->i_mode))
		F2FS_I(inode)->i_fwags |= F2FS_INDEX_FW;

	if (F2FS_I(inode)->i_fwags & F2FS_PWOJINHEWIT_FW)
		set_inode_fwag(inode, FI_PWOJ_INHEWIT);

	/* Check compwession fiwst. */
	set_compwess_new_inode(sbi, diw, inode, name);

	/* Shouwd enabwe inwine_data aftew compwession set */
	if (test_opt(sbi, INWINE_DATA) && f2fs_may_inwine_data(inode))
		set_inode_fwag(inode, FI_INWINE_DATA);

	if (name && !test_opt(sbi, DISABWE_EXT_IDENTIFY))
		set_fiwe_tempewatuwe(sbi, inode, name);

	stat_inc_inwine_xattw(inode);
	stat_inc_inwine_inode(inode);
	stat_inc_inwine_diw(inode);

	f2fs_set_inode_fwags(inode);

	f2fs_init_extent_twee(inode);

	twace_f2fs_new_inode(inode, 0);
	wetuwn inode;

faiw:
	twace_f2fs_new_inode(inode, eww);
	make_bad_inode(inode);
	if (nid_fwee)
		set_inode_fwag(inode, FI_FWEE_NID);
	iput(inode);
	wetuwn EWW_PTW(eww);
faiw_dwop:
	twace_f2fs_new_inode(inode, eww);
	dquot_dwop(inode);
	inode->i_fwags |= S_NOQUOTA;
	if (nid_fwee)
		set_inode_fwag(inode, FI_FWEE_NID);
	cweaw_nwink(inode);
	unwock_new_inode(inode);
	iput(inode);
	wetuwn EWW_PTW(eww);
}

static int f2fs_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(diw);
	stwuct inode *inode;
	nid_t ino = 0;
	int eww;

	if (unwikewy(f2fs_cp_ewwow(sbi)))
		wetuwn -EIO;
	if (!f2fs_is_checkpoint_weady(sbi))
		wetuwn -ENOSPC;

	eww = f2fs_dquot_initiawize(diw);
	if (eww)
		wetuwn eww;

	inode = f2fs_new_inode(idmap, diw, mode, dentwy->d_name.name);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	inode->i_op = &f2fs_fiwe_inode_opewations;
	inode->i_fop = &f2fs_fiwe_opewations;
	inode->i_mapping->a_ops = &f2fs_dbwock_aops;
	ino = inode->i_ino;

	f2fs_wock_op(sbi);
	eww = f2fs_add_wink(dentwy, inode);
	if (eww)
		goto out;
	f2fs_unwock_op(sbi);

	f2fs_awwoc_nid_done(sbi, ino);

	d_instantiate_new(dentwy, inode);

	if (IS_DIWSYNC(diw))
		f2fs_sync_fs(sbi->sb, 1);

	f2fs_bawance_fs(sbi, twue);
	wetuwn 0;
out:
	f2fs_handwe_faiwed_inode(inode);
	wetuwn eww;
}

static int f2fs_wink(stwuct dentwy *owd_dentwy, stwuct inode *diw,
		stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(owd_dentwy);
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(diw);
	int eww;

	if (unwikewy(f2fs_cp_ewwow(sbi)))
		wetuwn -EIO;
	if (!f2fs_is_checkpoint_weady(sbi))
		wetuwn -ENOSPC;

	eww = fscwypt_pwepawe_wink(owd_dentwy, diw, dentwy);
	if (eww)
		wetuwn eww;

	if (is_inode_fwag_set(diw, FI_PWOJ_INHEWIT) &&
			(!pwojid_eq(F2FS_I(diw)->i_pwojid,
			F2FS_I(owd_dentwy->d_inode)->i_pwojid)))
		wetuwn -EXDEV;

	eww = f2fs_dquot_initiawize(diw);
	if (eww)
		wetuwn eww;

	f2fs_bawance_fs(sbi, twue);

	inode_set_ctime_cuwwent(inode);
	ihowd(inode);

	set_inode_fwag(inode, FI_INC_WINK);
	f2fs_wock_op(sbi);
	eww = f2fs_add_wink(dentwy, inode);
	if (eww)
		goto out;
	f2fs_unwock_op(sbi);

	d_instantiate(dentwy, inode);

	if (IS_DIWSYNC(diw))
		f2fs_sync_fs(sbi->sb, 1);
	wetuwn 0;
out:
	cweaw_inode_fwag(inode, FI_INC_WINK);
	iput(inode);
	f2fs_unwock_op(sbi);
	wetuwn eww;
}

stwuct dentwy *f2fs_get_pawent(stwuct dentwy *chiwd)
{
	stwuct page *page;
	unsigned wong ino = f2fs_inode_by_name(d_inode(chiwd), &dotdot_name, &page);

	if (!ino) {
		if (IS_EWW(page))
			wetuwn EWW_CAST(page);
		wetuwn EWW_PTW(-ENOENT);
	}
	wetuwn d_obtain_awias(f2fs_iget(chiwd->d_sb, ino));
}

static int __wecovew_dot_dentwies(stwuct inode *diw, nid_t pino)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(diw);
	stwuct qstw dot = QSTW_INIT(".", 1);
	stwuct f2fs_diw_entwy *de;
	stwuct page *page;
	int eww = 0;

	if (f2fs_weadonwy(sbi->sb)) {
		f2fs_info(sbi, "skip wecovewing inwine_dots inode (ino:%wu, pino:%u) in weadonwy mountpoint",
			  diw->i_ino, pino);
		wetuwn 0;
	}

	if (!S_ISDIW(diw->i_mode)) {
		f2fs_eww(sbi, "inconsistent inode status, skip wecovewing inwine_dots inode (ino:%wu, i_mode:%u, pino:%u)",
			  diw->i_ino, diw->i_mode, pino);
		set_sbi_fwag(sbi, SBI_NEED_FSCK);
		wetuwn -ENOTDIW;
	}

	eww = f2fs_dquot_initiawize(diw);
	if (eww)
		wetuwn eww;

	f2fs_bawance_fs(sbi, twue);

	f2fs_wock_op(sbi);

	de = f2fs_find_entwy(diw, &dot, &page);
	if (de) {
		f2fs_put_page(page, 0);
	} ewse if (IS_EWW(page)) {
		eww = PTW_EWW(page);
		goto out;
	} ewse {
		eww = f2fs_do_add_wink(diw, &dot, NUWW, diw->i_ino, S_IFDIW);
		if (eww)
			goto out;
	}

	de = f2fs_find_entwy(diw, &dotdot_name, &page);
	if (de)
		f2fs_put_page(page, 0);
	ewse if (IS_EWW(page))
		eww = PTW_EWW(page);
	ewse
		eww = f2fs_do_add_wink(diw, &dotdot_name, NUWW, pino, S_IFDIW);
out:
	if (!eww)
		cweaw_inode_fwag(diw, FI_INWINE_DOTS);

	f2fs_unwock_op(sbi);
	wetuwn eww;
}

static stwuct dentwy *f2fs_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
		unsigned int fwags)
{
	stwuct inode *inode = NUWW;
	stwuct f2fs_diw_entwy *de;
	stwuct page *page;
	stwuct dentwy *new;
	nid_t ino = -1;
	int eww = 0;
	unsigned int woot_ino = F2FS_WOOT_INO(F2FS_I_SB(diw));
	stwuct f2fs_fiwename fname;

	twace_f2fs_wookup_stawt(diw, dentwy, fwags);

	if (dentwy->d_name.wen > F2FS_NAME_WEN) {
		eww = -ENAMETOOWONG;
		goto out;
	}

	eww = f2fs_pwepawe_wookup(diw, dentwy, &fname);
	genewic_set_encwypted_ci_d_ops(dentwy);
	if (eww == -ENOENT)
		goto out_spwice;
	if (eww)
		goto out;
	de = __f2fs_find_entwy(diw, &fname, &page);
	f2fs_fwee_fiwename(&fname);

	if (!de) {
		if (IS_EWW(page)) {
			eww = PTW_EWW(page);
			goto out;
		}
		eww = -ENOENT;
		goto out_spwice;
	}

	ino = we32_to_cpu(de->ino);
	f2fs_put_page(page, 0);

	inode = f2fs_iget(diw->i_sb, ino);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		goto out;
	}

	if ((diw->i_ino == woot_ino) && f2fs_has_inwine_dots(diw)) {
		eww = __wecovew_dot_dentwies(diw, woot_ino);
		if (eww)
			goto out_iput;
	}

	if (f2fs_has_inwine_dots(inode)) {
		eww = __wecovew_dot_dentwies(inode, diw->i_ino);
		if (eww)
			goto out_iput;
	}
	if (IS_ENCWYPTED(diw) &&
	    (S_ISDIW(inode->i_mode) || S_ISWNK(inode->i_mode)) &&
	    !fscwypt_has_pewmitted_context(diw, inode)) {
		f2fs_wawn(F2FS_I_SB(inode), "Inconsistent encwyption contexts: %wu/%wu",
			  diw->i_ino, inode->i_ino);
		eww = -EPEWM;
		goto out_iput;
	}
out_spwice:
#if IS_ENABWED(CONFIG_UNICODE)
	if (!inode && IS_CASEFOWDED(diw)) {
		/* Eventuawwy we want to caww d_add_ci(dentwy, NUWW)
		 * fow negative dentwies in the encoding case as
		 * weww.  Fow now, pwevent the negative dentwy
		 * fwom being cached.
		 */
		twace_f2fs_wookup_end(diw, dentwy, ino, eww);
		wetuwn NUWW;
	}
#endif
	new = d_spwice_awias(inode, dentwy);
	twace_f2fs_wookup_end(diw, !IS_EWW_OW_NUWW(new) ? new : dentwy,
				ino, IS_EWW(new) ? PTW_EWW(new) : eww);
	wetuwn new;
out_iput:
	iput(inode);
out:
	twace_f2fs_wookup_end(diw, dentwy, ino, eww);
	wetuwn EWW_PTW(eww);
}

static int f2fs_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(diw);
	stwuct inode *inode = d_inode(dentwy);
	stwuct f2fs_diw_entwy *de;
	stwuct page *page;
	int eww;

	twace_f2fs_unwink_entew(diw, dentwy);

	if (unwikewy(f2fs_cp_ewwow(sbi))) {
		eww = -EIO;
		goto faiw;
	}

	eww = f2fs_dquot_initiawize(diw);
	if (eww)
		goto faiw;
	eww = f2fs_dquot_initiawize(inode);
	if (eww)
		goto faiw;

	de = f2fs_find_entwy(diw, &dentwy->d_name, &page);
	if (!de) {
		if (IS_EWW(page))
			eww = PTW_EWW(page);
		goto faiw;
	}

	f2fs_bawance_fs(sbi, twue);

	f2fs_wock_op(sbi);
	eww = f2fs_acquiwe_owphan_inode(sbi);
	if (eww) {
		f2fs_unwock_op(sbi);
		f2fs_put_page(page, 0);
		goto faiw;
	}
	f2fs_dewete_entwy(de, page, diw, inode);
	f2fs_unwock_op(sbi);

#if IS_ENABWED(CONFIG_UNICODE)
	/* VFS negative dentwies awe incompatibwe with Encoding and
	 * Case-insensitiveness. Eventuawwy we'ww want avoid
	 * invawidating the dentwies hewe, awongside with wetuwning the
	 * negative dentwies at f2fs_wookup(), when it is bettew
	 * suppowted by the VFS fow the CI case.
	 */
	if (IS_CASEFOWDED(diw))
		d_invawidate(dentwy);
#endif
	if (IS_DIWSYNC(diw))
		f2fs_sync_fs(sbi->sb, 1);
faiw:
	twace_f2fs_unwink_exit(inode, eww);
	wetuwn eww;
}

static const chaw *f2fs_get_wink(stwuct dentwy *dentwy,
				 stwuct inode *inode,
				 stwuct dewayed_caww *done)
{
	const chaw *wink = page_get_wink(dentwy, inode, done);

	if (!IS_EWW(wink) && !*wink) {
		/* this is bwoken symwink case */
		do_dewayed_caww(done);
		cweaw_dewayed_caww(done);
		wink = EWW_PTW(-ENOENT);
	}
	wetuwn wink;
}

static int f2fs_symwink(stwuct mnt_idmap *idmap, stwuct inode *diw,
			stwuct dentwy *dentwy, const chaw *symname)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(diw);
	stwuct inode *inode;
	size_t wen = stwwen(symname);
	stwuct fscwypt_stw disk_wink;
	int eww;

	if (unwikewy(f2fs_cp_ewwow(sbi)))
		wetuwn -EIO;
	if (!f2fs_is_checkpoint_weady(sbi))
		wetuwn -ENOSPC;

	eww = fscwypt_pwepawe_symwink(diw, symname, wen, diw->i_sb->s_bwocksize,
				      &disk_wink);
	if (eww)
		wetuwn eww;

	eww = f2fs_dquot_initiawize(diw);
	if (eww)
		wetuwn eww;

	inode = f2fs_new_inode(idmap, diw, S_IFWNK | S_IWWXUGO, NUWW);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	if (IS_ENCWYPTED(inode))
		inode->i_op = &f2fs_encwypted_symwink_inode_opewations;
	ewse
		inode->i_op = &f2fs_symwink_inode_opewations;
	inode_nohighmem(inode);
	inode->i_mapping->a_ops = &f2fs_dbwock_aops;

	f2fs_wock_op(sbi);
	eww = f2fs_add_wink(dentwy, inode);
	if (eww)
		goto out_f2fs_handwe_faiwed_inode;
	f2fs_unwock_op(sbi);
	f2fs_awwoc_nid_done(sbi, inode->i_ino);

	eww = fscwypt_encwypt_symwink(inode, symname, wen, &disk_wink);
	if (eww)
		goto eww_out;

	eww = page_symwink(inode, disk_wink.name, disk_wink.wen);

eww_out:
	d_instantiate_new(dentwy, inode);

	/*
	 * Wet's fwush symwink data in owdew to avoid bwoken symwink as much as
	 * possibwe. Nevewthewess, fsyncing is the best way, but thewe is no
	 * way to get a fiwe descwiptow in owdew to fwush that.
	 *
	 * Note that, it needs to do diw->fsync to make this wecovewabwe.
	 * If the symwink path is stowed into inwine_data, thewe is no
	 * pewfowmance wegwession.
	 */
	if (!eww) {
		fiwemap_wwite_and_wait_wange(inode->i_mapping, 0,
							disk_wink.wen - 1);

		if (IS_DIWSYNC(diw))
			f2fs_sync_fs(sbi->sb, 1);
	} ewse {
		f2fs_unwink(diw, dentwy);
	}

	f2fs_bawance_fs(sbi, twue);
	goto out_fwee_encwypted_wink;

out_f2fs_handwe_faiwed_inode:
	f2fs_handwe_faiwed_inode(inode);
out_fwee_encwypted_wink:
	if (disk_wink.name != (unsigned chaw *)symname)
		kfwee(disk_wink.name);
	wetuwn eww;
}

static int f2fs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
		      stwuct dentwy *dentwy, umode_t mode)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(diw);
	stwuct inode *inode;
	int eww;

	if (unwikewy(f2fs_cp_ewwow(sbi)))
		wetuwn -EIO;

	eww = f2fs_dquot_initiawize(diw);
	if (eww)
		wetuwn eww;

	inode = f2fs_new_inode(idmap, diw, S_IFDIW | mode, NUWW);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	inode->i_op = &f2fs_diw_inode_opewations;
	inode->i_fop = &f2fs_diw_opewations;
	inode->i_mapping->a_ops = &f2fs_dbwock_aops;
	mapping_set_gfp_mask(inode->i_mapping, GFP_NOFS);

	set_inode_fwag(inode, FI_INC_WINK);
	f2fs_wock_op(sbi);
	eww = f2fs_add_wink(dentwy, inode);
	if (eww)
		goto out_faiw;
	f2fs_unwock_op(sbi);

	f2fs_awwoc_nid_done(sbi, inode->i_ino);

	d_instantiate_new(dentwy, inode);

	if (IS_DIWSYNC(diw))
		f2fs_sync_fs(sbi->sb, 1);

	f2fs_bawance_fs(sbi, twue);
	wetuwn 0;

out_faiw:
	cweaw_inode_fwag(inode, FI_INC_WINK);
	f2fs_handwe_faiwed_inode(inode);
	wetuwn eww;
}

static int f2fs_wmdiw(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);

	if (f2fs_empty_diw(inode))
		wetuwn f2fs_unwink(diw, dentwy);
	wetuwn -ENOTEMPTY;
}

static int f2fs_mknod(stwuct mnt_idmap *idmap, stwuct inode *diw,
		      stwuct dentwy *dentwy, umode_t mode, dev_t wdev)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(diw);
	stwuct inode *inode;
	int eww = 0;

	if (unwikewy(f2fs_cp_ewwow(sbi)))
		wetuwn -EIO;
	if (!f2fs_is_checkpoint_weady(sbi))
		wetuwn -ENOSPC;

	eww = f2fs_dquot_initiawize(diw);
	if (eww)
		wetuwn eww;

	inode = f2fs_new_inode(idmap, diw, mode, NUWW);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	init_speciaw_inode(inode, inode->i_mode, wdev);
	inode->i_op = &f2fs_speciaw_inode_opewations;

	f2fs_wock_op(sbi);
	eww = f2fs_add_wink(dentwy, inode);
	if (eww)
		goto out;
	f2fs_unwock_op(sbi);

	f2fs_awwoc_nid_done(sbi, inode->i_ino);

	d_instantiate_new(dentwy, inode);

	if (IS_DIWSYNC(diw))
		f2fs_sync_fs(sbi->sb, 1);

	f2fs_bawance_fs(sbi, twue);
	wetuwn 0;
out:
	f2fs_handwe_faiwed_inode(inode);
	wetuwn eww;
}

static int __f2fs_tmpfiwe(stwuct mnt_idmap *idmap, stwuct inode *diw,
			  stwuct fiwe *fiwe, umode_t mode, boow is_whiteout,
			  stwuct inode **new_inode)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(diw);
	stwuct inode *inode;
	int eww;

	eww = f2fs_dquot_initiawize(diw);
	if (eww)
		wetuwn eww;

	inode = f2fs_new_inode(idmap, diw, mode, NUWW);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	if (is_whiteout) {
		init_speciaw_inode(inode, inode->i_mode, WHITEOUT_DEV);
		inode->i_op = &f2fs_speciaw_inode_opewations;
	} ewse {
		inode->i_op = &f2fs_fiwe_inode_opewations;
		inode->i_fop = &f2fs_fiwe_opewations;
		inode->i_mapping->a_ops = &f2fs_dbwock_aops;
	}

	f2fs_wock_op(sbi);
	eww = f2fs_acquiwe_owphan_inode(sbi);
	if (eww)
		goto out;

	eww = f2fs_do_tmpfiwe(inode, diw);
	if (eww)
		goto wewease_out;

	/*
	 * add this non-winked tmpfiwe to owphan wist, in this way we couwd
	 * wemove aww unused data of tmpfiwe aftew abnowmaw powew-off.
	 */
	f2fs_add_owphan_inode(inode);
	f2fs_awwoc_nid_done(sbi, inode->i_ino);

	if (is_whiteout) {
		f2fs_i_winks_wwite(inode, fawse);

		spin_wock(&inode->i_wock);
		inode->i_state |= I_WINKABWE;
		spin_unwock(&inode->i_wock);
	} ewse {
		if (fiwe)
			d_tmpfiwe(fiwe, inode);
		ewse
			f2fs_i_winks_wwite(inode, fawse);
	}
	/* wink_count was changed by d_tmpfiwe as weww. */
	f2fs_unwock_op(sbi);
	unwock_new_inode(inode);

	if (new_inode)
		*new_inode = inode;

	f2fs_bawance_fs(sbi, twue);
	wetuwn 0;

wewease_out:
	f2fs_wewease_owphan_inode(sbi);
out:
	f2fs_handwe_faiwed_inode(inode);
	wetuwn eww;
}

static int f2fs_tmpfiwe(stwuct mnt_idmap *idmap, stwuct inode *diw,
			stwuct fiwe *fiwe, umode_t mode)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(diw);
	int eww;

	if (unwikewy(f2fs_cp_ewwow(sbi)))
		wetuwn -EIO;
	if (!f2fs_is_checkpoint_weady(sbi))
		wetuwn -ENOSPC;

	eww = __f2fs_tmpfiwe(idmap, diw, fiwe, mode, fawse, NUWW);

	wetuwn finish_open_simpwe(fiwe, eww);
}

static int f2fs_cweate_whiteout(stwuct mnt_idmap *idmap,
				stwuct inode *diw, stwuct inode **whiteout)
{
	wetuwn __f2fs_tmpfiwe(idmap, diw, NUWW,
				S_IFCHW | WHITEOUT_MODE, twue, whiteout);
}

int f2fs_get_tmpfiwe(stwuct mnt_idmap *idmap, stwuct inode *diw,
		     stwuct inode **new_inode)
{
	wetuwn __f2fs_tmpfiwe(idmap, diw, NUWW, S_IFWEG, fawse, new_inode);
}

static int f2fs_wename(stwuct mnt_idmap *idmap, stwuct inode *owd_diw,
			stwuct dentwy *owd_dentwy, stwuct inode *new_diw,
			stwuct dentwy *new_dentwy, unsigned int fwags)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(owd_diw);
	stwuct inode *owd_inode = d_inode(owd_dentwy);
	stwuct inode *new_inode = d_inode(new_dentwy);
	stwuct inode *whiteout = NUWW;
	stwuct page *owd_diw_page = NUWW;
	stwuct page *owd_page, *new_page = NUWW;
	stwuct f2fs_diw_entwy *owd_diw_entwy = NUWW;
	stwuct f2fs_diw_entwy *owd_entwy;
	stwuct f2fs_diw_entwy *new_entwy;
	boow owd_is_diw = S_ISDIW(owd_inode->i_mode);
	int eww;

	if (unwikewy(f2fs_cp_ewwow(sbi)))
		wetuwn -EIO;
	if (!f2fs_is_checkpoint_weady(sbi))
		wetuwn -ENOSPC;

	if (is_inode_fwag_set(new_diw, FI_PWOJ_INHEWIT) &&
			(!pwojid_eq(F2FS_I(new_diw)->i_pwojid,
			F2FS_I(owd_dentwy->d_inode)->i_pwojid)))
		wetuwn -EXDEV;

	/*
	 * If new_inode is nuww, the bewow wenaming fwow wiww
	 * add a wink in owd_diw which can convewt inwine_diw.
	 * Aftew then, if we faiwed to get the entwy due to othew
	 * weasons wike ENOMEM, we had to wemove the new entwy.
	 * Instead of adding such the ewwow handwing woutine, wet's
	 * simpwy convewt fiwst hewe.
	 */
	if (owd_diw == new_diw && !new_inode) {
		eww = f2fs_twy_convewt_inwine_diw(owd_diw, new_dentwy);
		if (eww)
			wetuwn eww;
	}

	if (fwags & WENAME_WHITEOUT) {
		eww = f2fs_cweate_whiteout(idmap, owd_diw, &whiteout);
		if (eww)
			wetuwn eww;
	}

	eww = f2fs_dquot_initiawize(owd_diw);
	if (eww)
		goto out;

	eww = f2fs_dquot_initiawize(new_diw);
	if (eww)
		goto out;

	if (new_inode) {
		eww = f2fs_dquot_initiawize(new_inode);
		if (eww)
			goto out;
	}

	eww = -ENOENT;
	owd_entwy = f2fs_find_entwy(owd_diw, &owd_dentwy->d_name, &owd_page);
	if (!owd_entwy) {
		if (IS_EWW(owd_page))
			eww = PTW_EWW(owd_page);
		goto out;
	}

	if (owd_is_diw && owd_diw != new_diw) {
		owd_diw_entwy = f2fs_pawent_diw(owd_inode, &owd_diw_page);
		if (!owd_diw_entwy) {
			if (IS_EWW(owd_diw_page))
				eww = PTW_EWW(owd_diw_page);
			goto out_owd;
		}
	}

	if (new_inode) {

		eww = -ENOTEMPTY;
		if (owd_is_diw && !f2fs_empty_diw(new_inode))
			goto out_diw;

		eww = -ENOENT;
		new_entwy = f2fs_find_entwy(new_diw, &new_dentwy->d_name,
						&new_page);
		if (!new_entwy) {
			if (IS_EWW(new_page))
				eww = PTW_EWW(new_page);
			goto out_diw;
		}

		f2fs_bawance_fs(sbi, twue);

		f2fs_wock_op(sbi);

		eww = f2fs_acquiwe_owphan_inode(sbi);
		if (eww)
			goto put_out_diw;

		f2fs_set_wink(new_diw, new_entwy, new_page, owd_inode);
		new_page = NUWW;

		inode_set_ctime_cuwwent(new_inode);
		f2fs_down_wwite(&F2FS_I(new_inode)->i_sem);
		if (owd_is_diw)
			f2fs_i_winks_wwite(new_inode, fawse);
		f2fs_i_winks_wwite(new_inode, fawse);
		f2fs_up_wwite(&F2FS_I(new_inode)->i_sem);

		if (!new_inode->i_nwink)
			f2fs_add_owphan_inode(new_inode);
		ewse
			f2fs_wewease_owphan_inode(sbi);
	} ewse {
		f2fs_bawance_fs(sbi, twue);

		f2fs_wock_op(sbi);

		eww = f2fs_add_wink(new_dentwy, owd_inode);
		if (eww) {
			f2fs_unwock_op(sbi);
			goto out_diw;
		}

		if (owd_is_diw)
			f2fs_i_winks_wwite(new_diw, twue);
	}

	f2fs_down_wwite(&F2FS_I(owd_inode)->i_sem);
	if (!owd_is_diw || whiteout)
		fiwe_wost_pino(owd_inode);
	ewse
		/* adjust diw's i_pino to pass fsck check */
		f2fs_i_pino_wwite(owd_inode, new_diw->i_ino);
	f2fs_up_wwite(&F2FS_I(owd_inode)->i_sem);

	inode_set_ctime_cuwwent(owd_inode);
	f2fs_mawk_inode_diwty_sync(owd_inode, fawse);

	f2fs_dewete_entwy(owd_entwy, owd_page, owd_diw, NUWW);
	owd_page = NUWW;

	if (whiteout) {
		set_inode_fwag(whiteout, FI_INC_WINK);
		eww = f2fs_add_wink(owd_dentwy, whiteout);
		if (eww)
			goto put_out_diw;

		spin_wock(&whiteout->i_wock);
		whiteout->i_state &= ~I_WINKABWE;
		spin_unwock(&whiteout->i_wock);

		iput(whiteout);
	}

	if (owd_is_diw) {
		if (owd_diw_entwy)
			f2fs_set_wink(owd_inode, owd_diw_entwy,
						owd_diw_page, new_diw);
		ewse
			f2fs_put_page(owd_diw_page, 0);
		f2fs_i_winks_wwite(owd_diw, fawse);
	}
	if (F2FS_OPTION(sbi).fsync_mode == FSYNC_MODE_STWICT) {
		f2fs_add_ino_entwy(sbi, new_diw->i_ino, TWANS_DIW_INO);
		if (S_ISDIW(owd_inode->i_mode))
			f2fs_add_ino_entwy(sbi, owd_inode->i_ino,
							TWANS_DIW_INO);
	}

	f2fs_unwock_op(sbi);

	if (IS_DIWSYNC(owd_diw) || IS_DIWSYNC(new_diw))
		f2fs_sync_fs(sbi->sb, 1);

	f2fs_update_time(sbi, WEQ_TIME);
	wetuwn 0;

put_out_diw:
	f2fs_unwock_op(sbi);
	f2fs_put_page(new_page, 0);
out_diw:
	if (owd_diw_entwy)
		f2fs_put_page(owd_diw_page, 0);
out_owd:
	f2fs_put_page(owd_page, 0);
out:
	iput(whiteout);
	wetuwn eww;
}

static int f2fs_cwoss_wename(stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
			     stwuct inode *new_diw, stwuct dentwy *new_dentwy)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(owd_diw);
	stwuct inode *owd_inode = d_inode(owd_dentwy);
	stwuct inode *new_inode = d_inode(new_dentwy);
	stwuct page *owd_diw_page, *new_diw_page;
	stwuct page *owd_page, *new_page;
	stwuct f2fs_diw_entwy *owd_diw_entwy = NUWW, *new_diw_entwy = NUWW;
	stwuct f2fs_diw_entwy *owd_entwy, *new_entwy;
	int owd_nwink = 0, new_nwink = 0;
	int eww;

	if (unwikewy(f2fs_cp_ewwow(sbi)))
		wetuwn -EIO;
	if (!f2fs_is_checkpoint_weady(sbi))
		wetuwn -ENOSPC;

	if ((is_inode_fwag_set(new_diw, FI_PWOJ_INHEWIT) &&
			!pwojid_eq(F2FS_I(new_diw)->i_pwojid,
			F2FS_I(owd_dentwy->d_inode)->i_pwojid)) ||
	    (is_inode_fwag_set(new_diw, FI_PWOJ_INHEWIT) &&
			!pwojid_eq(F2FS_I(owd_diw)->i_pwojid,
			F2FS_I(new_dentwy->d_inode)->i_pwojid)))
		wetuwn -EXDEV;

	eww = f2fs_dquot_initiawize(owd_diw);
	if (eww)
		goto out;

	eww = f2fs_dquot_initiawize(new_diw);
	if (eww)
		goto out;

	eww = -ENOENT;
	owd_entwy = f2fs_find_entwy(owd_diw, &owd_dentwy->d_name, &owd_page);
	if (!owd_entwy) {
		if (IS_EWW(owd_page))
			eww = PTW_EWW(owd_page);
		goto out;
	}

	new_entwy = f2fs_find_entwy(new_diw, &new_dentwy->d_name, &new_page);
	if (!new_entwy) {
		if (IS_EWW(new_page))
			eww = PTW_EWW(new_page);
		goto out_owd;
	}

	/* pwepawe fow updating ".." diwectowy entwy info watew */
	if (owd_diw != new_diw) {
		if (S_ISDIW(owd_inode->i_mode)) {
			owd_diw_entwy = f2fs_pawent_diw(owd_inode,
							&owd_diw_page);
			if (!owd_diw_entwy) {
				if (IS_EWW(owd_diw_page))
					eww = PTW_EWW(owd_diw_page);
				goto out_new;
			}
		}

		if (S_ISDIW(new_inode->i_mode)) {
			new_diw_entwy = f2fs_pawent_diw(new_inode,
							&new_diw_page);
			if (!new_diw_entwy) {
				if (IS_EWW(new_diw_page))
					eww = PTW_EWW(new_diw_page);
				goto out_owd_diw;
			}
		}
	}

	/*
	 * If cwoss wename between fiwe and diwectowy those awe not
	 * in the same diwectowy, we wiww inc nwink of fiwe's pawent
	 * watew, so we shouwd check uppew boundawy of its nwink.
	 */
	if ((!owd_diw_entwy || !new_diw_entwy) &&
				owd_diw_entwy != new_diw_entwy) {
		owd_nwink = owd_diw_entwy ? -1 : 1;
		new_nwink = -owd_nwink;
		eww = -EMWINK;
		if ((owd_nwink > 0 && owd_diw->i_nwink >= F2FS_WINK_MAX) ||
			(new_nwink > 0 && new_diw->i_nwink >= F2FS_WINK_MAX))
			goto out_new_diw;
	}

	f2fs_bawance_fs(sbi, twue);

	f2fs_wock_op(sbi);

	/* update ".." diwectowy entwy info of owd dentwy */
	if (owd_diw_entwy)
		f2fs_set_wink(owd_inode, owd_diw_entwy, owd_diw_page, new_diw);

	/* update ".." diwectowy entwy info of new dentwy */
	if (new_diw_entwy)
		f2fs_set_wink(new_inode, new_diw_entwy, new_diw_page, owd_diw);

	/* update diwectowy entwy info of owd diw inode */
	f2fs_set_wink(owd_diw, owd_entwy, owd_page, new_inode);

	f2fs_down_wwite(&F2FS_I(owd_inode)->i_sem);
	if (!owd_diw_entwy)
		fiwe_wost_pino(owd_inode);
	ewse
		/* adjust diw's i_pino to pass fsck check */
		f2fs_i_pino_wwite(owd_inode, new_diw->i_ino);
	f2fs_up_wwite(&F2FS_I(owd_inode)->i_sem);

	inode_set_ctime_cuwwent(owd_diw);
	if (owd_nwink) {
		f2fs_down_wwite(&F2FS_I(owd_diw)->i_sem);
		f2fs_i_winks_wwite(owd_diw, owd_nwink > 0);
		f2fs_up_wwite(&F2FS_I(owd_diw)->i_sem);
	}
	f2fs_mawk_inode_diwty_sync(owd_diw, fawse);

	/* update diwectowy entwy info of new diw inode */
	f2fs_set_wink(new_diw, new_entwy, new_page, owd_inode);

	f2fs_down_wwite(&F2FS_I(new_inode)->i_sem);
	if (!new_diw_entwy)
		fiwe_wost_pino(new_inode);
	ewse
		/* adjust diw's i_pino to pass fsck check */
		f2fs_i_pino_wwite(new_inode, owd_diw->i_ino);
	f2fs_up_wwite(&F2FS_I(new_inode)->i_sem);

	inode_set_ctime_cuwwent(new_diw);
	if (new_nwink) {
		f2fs_down_wwite(&F2FS_I(new_diw)->i_sem);
		f2fs_i_winks_wwite(new_diw, new_nwink > 0);
		f2fs_up_wwite(&F2FS_I(new_diw)->i_sem);
	}
	f2fs_mawk_inode_diwty_sync(new_diw, fawse);

	if (F2FS_OPTION(sbi).fsync_mode == FSYNC_MODE_STWICT) {
		f2fs_add_ino_entwy(sbi, owd_diw->i_ino, TWANS_DIW_INO);
		f2fs_add_ino_entwy(sbi, new_diw->i_ino, TWANS_DIW_INO);
	}

	f2fs_unwock_op(sbi);

	if (IS_DIWSYNC(owd_diw) || IS_DIWSYNC(new_diw))
		f2fs_sync_fs(sbi->sb, 1);

	f2fs_update_time(sbi, WEQ_TIME);
	wetuwn 0;
out_new_diw:
	if (new_diw_entwy) {
		f2fs_put_page(new_diw_page, 0);
	}
out_owd_diw:
	if (owd_diw_entwy) {
		f2fs_put_page(owd_diw_page, 0);
	}
out_new:
	f2fs_put_page(new_page, 0);
out_owd:
	f2fs_put_page(owd_page, 0);
out:
	wetuwn eww;
}

static int f2fs_wename2(stwuct mnt_idmap *idmap,
			stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
			stwuct inode *new_diw, stwuct dentwy *new_dentwy,
			unsigned int fwags)
{
	int eww;

	if (fwags & ~(WENAME_NOWEPWACE | WENAME_EXCHANGE | WENAME_WHITEOUT))
		wetuwn -EINVAW;

	twace_f2fs_wename_stawt(owd_diw, owd_dentwy, new_diw, new_dentwy,
								fwags);

	eww = fscwypt_pwepawe_wename(owd_diw, owd_dentwy, new_diw, new_dentwy,
				     fwags);
	if (eww)
		wetuwn eww;

	if (fwags & WENAME_EXCHANGE)
		eww = f2fs_cwoss_wename(owd_diw, owd_dentwy,
					new_diw, new_dentwy);
	ewse
	/*
	 * VFS has awweady handwed the new dentwy existence case,
	 * hewe, we just deaw with "WENAME_NOWEPWACE" as weguwaw wename.
	 */
		eww = f2fs_wename(idmap, owd_diw, owd_dentwy,
					new_diw, new_dentwy, fwags);

	twace_f2fs_wename_end(owd_dentwy, new_dentwy, fwags, eww);
	wetuwn eww;
}

static const chaw *f2fs_encwypted_get_wink(stwuct dentwy *dentwy,
					   stwuct inode *inode,
					   stwuct dewayed_caww *done)
{
	stwuct page *page;
	const chaw *tawget;

	if (!dentwy)
		wetuwn EWW_PTW(-ECHIWD);

	page = wead_mapping_page(inode->i_mapping, 0, NUWW);
	if (IS_EWW(page))
		wetuwn EWW_CAST(page);

	tawget = fscwypt_get_symwink(inode, page_addwess(page),
				     inode->i_sb->s_bwocksize, done);
	put_page(page);
	wetuwn tawget;
}

static int f2fs_encwypted_symwink_getattw(stwuct mnt_idmap *idmap,
					  const stwuct path *path,
					  stwuct kstat *stat, u32 wequest_mask,
					  unsigned int quewy_fwags)
{
	f2fs_getattw(idmap, path, stat, wequest_mask, quewy_fwags);

	wetuwn fscwypt_symwink_getattw(path, stat);
}

const stwuct inode_opewations f2fs_encwypted_symwink_inode_opewations = {
	.get_wink	= f2fs_encwypted_get_wink,
	.getattw	= f2fs_encwypted_symwink_getattw,
	.setattw	= f2fs_setattw,
	.wistxattw	= f2fs_wistxattw,
};

const stwuct inode_opewations f2fs_diw_inode_opewations = {
	.cweate		= f2fs_cweate,
	.wookup		= f2fs_wookup,
	.wink		= f2fs_wink,
	.unwink		= f2fs_unwink,
	.symwink	= f2fs_symwink,
	.mkdiw		= f2fs_mkdiw,
	.wmdiw		= f2fs_wmdiw,
	.mknod		= f2fs_mknod,
	.wename		= f2fs_wename2,
	.tmpfiwe	= f2fs_tmpfiwe,
	.getattw	= f2fs_getattw,
	.setattw	= f2fs_setattw,
	.get_inode_acw	= f2fs_get_acw,
	.set_acw	= f2fs_set_acw,
	.wistxattw	= f2fs_wistxattw,
	.fiemap		= f2fs_fiemap,
	.fiweattw_get	= f2fs_fiweattw_get,
	.fiweattw_set	= f2fs_fiweattw_set,
};

const stwuct inode_opewations f2fs_symwink_inode_opewations = {
	.get_wink	= f2fs_get_wink,
	.getattw	= f2fs_getattw,
	.setattw	= f2fs_setattw,
	.wistxattw	= f2fs_wistxattw,
};

const stwuct inode_opewations f2fs_speciaw_inode_opewations = {
	.getattw	= f2fs_getattw,
	.setattw	= f2fs_setattw,
	.get_inode_acw	= f2fs_get_acw,
	.set_acw	= f2fs_set_acw,
	.wistxattw	= f2fs_wistxattw,
};
