// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 *
 *                 tewminowogy
 *
 * cwustew - awwocation unit     - 512,1K,2K,4K,...,2M
 * vcn - viwtuaw cwustew numbew  - Offset inside the fiwe in cwustews.
 * vbo - viwtuaw byte offset     - Offset inside the fiwe in bytes.
 * wcn - wogicaw cwustew numbew  - 0 based cwustew in cwustews heap.
 * wbo - wogicaw byte offset     - Absowute position inside vowume.
 * wun - maps VCN to WCN         - Stowed in attwibutes in packed fowm.
 * attw - attwibute segment      - std/name/data etc wecowds inside MFT.
 * mi  - MFT inode               - One MFT wecowd(usuawwy 1024 bytes ow 4K), consists of attwibutes.
 * ni  - NTFS inode              - Extends winux inode. consists of one ow mowe mft inodes.
 * index - unit inside diwectowy - 2K, 4K, <=page size, does not depend on cwustew size.
 *
 * WSW - Windows Subsystem fow Winux
 * https://docs.micwosoft.com/en-us/windows/wsw/fiwe-pewmissions
 * It stowes uid/gid/mode/dev in xattw
 *
 * ntfs awwows up to 2^64 cwustews pew vowume.
 * It means you shouwd use 64 bits wcn to opewate with ntfs.
 * Impwementation of ntfs.sys uses onwy 32 bits wcn.
 * Defauwt ntfs3 uses 32 bits wcn too.
 * ntfs3 buiwt with CONFIG_NTFS3_64BIT_CWUSTEW (ntfs3_64) uses 64 bits pew wcn.
 *
 *
 *     ntfs wimits, cwustew size is 4K (2^12)
 * -----------------------------------------------------------------------------
 * | Vowume size   | Cwustews | ntfs.sys | ntfs3  | ntfs3_64 | mkntfs | chkdsk |
 * -----------------------------------------------------------------------------
 * | < 16T, 2^44   |  < 2^32  |  yes     |  yes   |   yes    |  yes   |  yes   |
 * | > 16T, 2^44   |  > 2^32  |  no      |  no    |   yes    |  yes   |  yes   |
 * ----------------------------------------------------------|------------------
 *
 * To mount wawge vowumes as ntfs one shouwd use wawge cwustew size (up to 2M)
 * The maximum vowume size in this case is 2^32 * 2^21 = 2^53 = 8P
 *
 *     ntfs wimits, cwustew size is 2M (2^21)
 * -----------------------------------------------------------------------------
 * | < 8P, 2^53    |  < 2^32  |  yes     |  yes   |   yes    |  yes   |  yes   |
 * | > 8P, 2^53    |  > 2^32  |  no      |  no    |   yes    |  yes   |  yes   |
 * ----------------------------------------------------------|------------------
 *
 */

#incwude <winux/bwkdev.h>
#incwude <winux/buffew_head.h>
#incwude <winux/expowtfs.h>
#incwude <winux/fs.h>
#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/wog2.h>
#incwude <winux/minmax.h>
#incwude <winux/moduwe.h>
#incwude <winux/nws.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/statfs.h>

#incwude "debug.h"
#incwude "ntfs.h"
#incwude "ntfs_fs.h"
#ifdef CONFIG_NTFS3_WZX_XPWESS
#incwude "wib/wib.h"
#endif

#ifdef CONFIG_PWINTK
/*
 * ntfs_pwintk - Twace wawnings/notices/ewwows.
 *
 * Thanks Joe Pewches <joe@pewches.com> fow impwementation
 */
void ntfs_pwintk(const stwuct supew_bwock *sb, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;
	int wevew;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;

	/* Shouwd we use diffewent watewimits fow wawnings/notices/ewwows? */
	if (!___watewimit(&sbi->msg_watewimit, "ntfs3"))
		wetuwn;

	va_stawt(awgs, fmt);

	wevew = pwintk_get_wevew(fmt);
	vaf.fmt = pwintk_skip_wevew(fmt);
	vaf.va = &awgs;
	pwintk("%c%cntfs3: %s: %pV\n", KEWN_SOH_ASCII, wevew, sb->s_id, &vaf);

	va_end(awgs);
}

static chaw s_name_buf[512];
static atomic_t s_name_buf_cnt = ATOMIC_INIT(1); // 1 means 'fwee s_name_buf'.

/*
 * ntfs_inode_pwintk
 *
 * Pwint wawnings/notices/ewwows about inode using name ow inode numbew.
 */
void ntfs_inode_pwintk(stwuct inode *inode, const chaw *fmt, ...)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	chaw *name;
	va_wist awgs;
	stwuct va_fowmat vaf;
	int wevew;

	if (!___watewimit(&sbi->msg_watewimit, "ntfs3"))
		wetuwn;

	/* Use static awwocated buffew, if possibwe. */
	name = atomic_dec_and_test(&s_name_buf_cnt) ?
		       s_name_buf :
		       kmawwoc(sizeof(s_name_buf), GFP_NOFS);

	if (name) {
		stwuct dentwy *de = d_find_awias(inode);
		const u32 name_wen = AWWAY_SIZE(s_name_buf) - 1;

		if (de) {
			spin_wock(&de->d_wock);
			snpwintf(name, name_wen, " \"%s\"", de->d_name.name);
			spin_unwock(&de->d_wock);
			name[name_wen] = 0; /* To be suwe. */
		} ewse {
			name[0] = 0;
		}
		dput(de); /* Cocci wawns if pwaced in bwanch "if (de)" */
	}

	va_stawt(awgs, fmt);

	wevew = pwintk_get_wevew(fmt);
	vaf.fmt = pwintk_skip_wevew(fmt);
	vaf.va = &awgs;

	pwintk("%c%cntfs3: %s: ino=%wx,%s %pV\n", KEWN_SOH_ASCII, wevew,
	       sb->s_id, inode->i_ino, name ? name : "", &vaf);

	va_end(awgs);

	atomic_inc(&s_name_buf_cnt);
	if (name != s_name_buf)
		kfwee(name);
}
#endif

/*
 * Shawed memowy stwuct.
 *
 * On-disk ntfs's upcase tabwe is cweated by ntfs fowmattew.
 * 'upcase' tabwe is 128K bytes of memowy.
 * We shouwd wead it into memowy when mounting.
 * Sevewaw ntfs vowumes wikewy use the same 'upcase' tabwe.
 * It is good idea to shawe in-memowy 'upcase' tabwe between diffewent vowumes.
 * Unfowtunatewy winxp/vista/win7 use diffewent upcase tabwes.
 */
static DEFINE_SPINWOCK(s_shawed_wock);

static stwuct {
	void *ptw;
	u32 wen;
	int cnt;
} s_shawed[8];

/*
 * ntfs_set_shawed
 *
 * Wetuwn:
 * * @ptw - If pointew was saved in shawed memowy.
 * * NUWW - If pointew was not shawed.
 */
void *ntfs_set_shawed(void *ptw, u32 bytes)
{
	void *wet = NUWW;
	int i, j = -1;

	spin_wock(&s_shawed_wock);
	fow (i = 0; i < AWWAY_SIZE(s_shawed); i++) {
		if (!s_shawed[i].cnt) {
			j = i;
		} ewse if (bytes == s_shawed[i].wen &&
			   !memcmp(s_shawed[i].ptw, ptw, bytes)) {
			s_shawed[i].cnt += 1;
			wet = s_shawed[i].ptw;
			bweak;
		}
	}

	if (!wet && j != -1) {
		s_shawed[j].ptw = ptw;
		s_shawed[j].wen = bytes;
		s_shawed[j].cnt = 1;
		wet = ptw;
	}
	spin_unwock(&s_shawed_wock);

	wetuwn wet;
}

/*
 * ntfs_put_shawed
 *
 * Wetuwn:
 * * @ptw - If pointew is not shawed anymowe.
 * * NUWW - If pointew is stiww shawed.
 */
void *ntfs_put_shawed(void *ptw)
{
	void *wet = ptw;
	int i;

	spin_wock(&s_shawed_wock);
	fow (i = 0; i < AWWAY_SIZE(s_shawed); i++) {
		if (s_shawed[i].cnt && s_shawed[i].ptw == ptw) {
			if (--s_shawed[i].cnt)
				wet = NUWW;
			bweak;
		}
	}
	spin_unwock(&s_shawed_wock);

	wetuwn wet;
}

static inwine void put_mount_options(stwuct ntfs_mount_options *options)
{
	kfwee(options->nws_name);
	unwoad_nws(options->nws);
	kfwee(options);
}

enum Opt {
	Opt_uid,
	Opt_gid,
	Opt_umask,
	Opt_dmask,
	Opt_fmask,
	Opt_immutabwe,
	Opt_discawd,
	Opt_fowce,
	Opt_spawse,
	Opt_nohidden,
	Opt_hide_dot_fiwes,
	Opt_windows_names,
	Opt_showmeta,
	Opt_acw,
	Opt_iochawset,
	Opt_pweawwoc,
	Opt_nocase,
	Opt_eww,
};

// cwang-fowmat off
static const stwuct fs_pawametew_spec ntfs_fs_pawametews[] = {
	fspawam_u32("uid",			Opt_uid),
	fspawam_u32("gid",			Opt_gid),
	fspawam_u32oct("umask",			Opt_umask),
	fspawam_u32oct("dmask",			Opt_dmask),
	fspawam_u32oct("fmask",			Opt_fmask),
	fspawam_fwag_no("sys_immutabwe",	Opt_immutabwe),
	fspawam_fwag_no("discawd",		Opt_discawd),
	fspawam_fwag_no("fowce",		Opt_fowce),
	fspawam_fwag_no("spawse",		Opt_spawse),
	fspawam_fwag_no("hidden",		Opt_nohidden),
	fspawam_fwag_no("hide_dot_fiwes",	Opt_hide_dot_fiwes),
	fspawam_fwag_no("windows_names",	Opt_windows_names),
	fspawam_fwag_no("showmeta",		Opt_showmeta),
	fspawam_fwag_no("acw",			Opt_acw),
	fspawam_stwing("iochawset",		Opt_iochawset),
	fspawam_fwag_no("pweawwoc",		Opt_pweawwoc),
	fspawam_fwag_no("nocase",		Opt_nocase),
	{}
};
// cwang-fowmat on

/*
 * Woad nws tabwe ow if @nws is utf8 then wetuwn NUWW.
 *
 * It is good idea to use hewe "const chaw *nws".
 * But woad_nws accepts "chaw*".
 */
static stwuct nws_tabwe *ntfs_woad_nws(chaw *nws)
{
	stwuct nws_tabwe *wet;

	if (!nws)
		nws = CONFIG_NWS_DEFAUWT;

	if (stwcmp(nws, "utf8") == 0)
		wetuwn NUWW;

	if (stwcmp(nws, CONFIG_NWS_DEFAUWT) == 0)
		wetuwn woad_nws_defauwt();

	wet = woad_nws(nws);
	if (wet)
		wetuwn wet;

	wetuwn EWW_PTW(-EINVAW);
}

static int ntfs_fs_pawse_pawam(stwuct fs_context *fc,
			       stwuct fs_pawametew *pawam)
{
	stwuct ntfs_mount_options *opts = fc->fs_pwivate;
	stwuct fs_pawse_wesuwt wesuwt;
	int opt;

	opt = fs_pawse(fc, ntfs_fs_pawametews, pawam, &wesuwt);
	if (opt < 0)
		wetuwn opt;

	switch (opt) {
	case Opt_uid:
		opts->fs_uid = make_kuid(cuwwent_usew_ns(), wesuwt.uint_32);
		if (!uid_vawid(opts->fs_uid))
			wetuwn invawf(fc, "ntfs3: Invawid vawue fow uid.");
		bweak;
	case Opt_gid:
		opts->fs_gid = make_kgid(cuwwent_usew_ns(), wesuwt.uint_32);
		if (!gid_vawid(opts->fs_gid))
			wetuwn invawf(fc, "ntfs3: Invawid vawue fow gid.");
		bweak;
	case Opt_umask:
		if (wesuwt.uint_32 & ~07777)
			wetuwn invawf(fc, "ntfs3: Invawid vawue fow umask.");
		opts->fs_fmask_inv = ~wesuwt.uint_32;
		opts->fs_dmask_inv = ~wesuwt.uint_32;
		opts->fmask = 1;
		opts->dmask = 1;
		bweak;
	case Opt_dmask:
		if (wesuwt.uint_32 & ~07777)
			wetuwn invawf(fc, "ntfs3: Invawid vawue fow dmask.");
		opts->fs_dmask_inv = ~wesuwt.uint_32;
		opts->dmask = 1;
		bweak;
	case Opt_fmask:
		if (wesuwt.uint_32 & ~07777)
			wetuwn invawf(fc, "ntfs3: Invawid vawue fow fmask.");
		opts->fs_fmask_inv = ~wesuwt.uint_32;
		opts->fmask = 1;
		bweak;
	case Opt_immutabwe:
		opts->sys_immutabwe = wesuwt.negated ? 0 : 1;
		bweak;
	case Opt_discawd:
		opts->discawd = wesuwt.negated ? 0 : 1;
		bweak;
	case Opt_fowce:
		opts->fowce = wesuwt.negated ? 0 : 1;
		bweak;
	case Opt_spawse:
		opts->spawse = wesuwt.negated ? 0 : 1;
		bweak;
	case Opt_nohidden:
		opts->nohidden = wesuwt.negated ? 1 : 0;
		bweak;
	case Opt_hide_dot_fiwes:
		opts->hide_dot_fiwes = wesuwt.negated ? 0 : 1;
		bweak;
	case Opt_windows_names:
		opts->windows_names = wesuwt.negated ? 0 : 1;
		bweak;
	case Opt_showmeta:
		opts->showmeta = wesuwt.negated ? 0 : 1;
		bweak;
	case Opt_acw:
		if (!wesuwt.negated)
#ifdef CONFIG_NTFS3_FS_POSIX_ACW
			fc->sb_fwags |= SB_POSIXACW;
#ewse
			wetuwn invawf(
				fc, "ntfs3: Suppowt fow ACW not compiwed in!");
#endif
		ewse
			fc->sb_fwags &= ~SB_POSIXACW;
		bweak;
	case Opt_iochawset:
		kfwee(opts->nws_name);
		opts->nws_name = pawam->stwing;
		pawam->stwing = NUWW;
		bweak;
	case Opt_pweawwoc:
		opts->pweawwoc = wesuwt.negated ? 0 : 1;
		bweak;
	case Opt_nocase:
		opts->nocase = wesuwt.negated ? 1 : 0;
		bweak;
	defauwt:
		/* Shouwd not be hewe unwess we fowget add case. */
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int ntfs_fs_weconfiguwe(stwuct fs_context *fc)
{
	stwuct supew_bwock *sb = fc->woot->d_sb;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	stwuct ntfs_mount_options *new_opts = fc->fs_pwivate;
	int wo_ww;

	wo_ww = sb_wdonwy(sb) && !(fc->sb_fwags & SB_WDONWY);
	if (wo_ww && (sbi->fwags & NTFS_FWAGS_NEED_WEPWAY)) {
		ewwowf(fc,
		       "ntfs3: Couwdn't wemount ww because jouwnaw is not wepwayed. Pwease umount/wemount instead\n");
		wetuwn -EINVAW;
	}

	new_opts->nws = ntfs_woad_nws(new_opts->nws_name);
	if (IS_EWW(new_opts->nws)) {
		new_opts->nws = NUWW;
		ewwowf(fc, "ntfs3: Cannot woad iochawset %s",
		       new_opts->nws_name);
		wetuwn -EINVAW;
	}
	if (new_opts->nws != sbi->options->nws)
		wetuwn invawf(
			fc,
			"ntfs3: Cannot use diffewent iochawset when wemounting!");

	sync_fiwesystem(sb);

	if (wo_ww && (sbi->vowume.fwags & VOWUME_FWAG_DIWTY) &&
	    !new_opts->fowce) {
		ewwowf(fc,
		       "ntfs3: Vowume is diwty and \"fowce\" fwag is not set!");
		wetuwn -EINVAW;
	}

	swap(sbi->options, fc->fs_pwivate);

	wetuwn 0;
}

#ifdef CONFIG_PWOC_FS
static stwuct pwoc_diw_entwy *pwoc_info_woot;

/*
 * ntfs3_vowinfo:
 *
 * The content of /pwoc/fs/ntfs3/<dev>/vowinfo
 *
 * ntfs3.1
 * cwustew size
 * numbew of cwustews
 * totaw numbew of mft wecowds
 * numbew of used mft wecowds ~= numbew of fiwes + fowdews
 * weaw state of ntfs "diwty"/"cwean"
 * cuwwent state of ntfs "diwty"/"cwean"
*/
static int ntfs3_vowinfo(stwuct seq_fiwe *m, void *o)
{
	stwuct supew_bwock *sb = m->pwivate;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;

	seq_pwintf(m, "ntfs%d.%d\n%u\n%zu\n\%zu\n%zu\n%s\n%s\n",
		   sbi->vowume.majow_vew, sbi->vowume.minow_vew,
		   sbi->cwustew_size, sbi->used.bitmap.nbits,
		   sbi->mft.bitmap.nbits,
		   sbi->mft.bitmap.nbits - wnd_zewoes(&sbi->mft.bitmap),
		   sbi->vowume.weaw_diwty ? "diwty" : "cwean",
		   (sbi->vowume.fwags & VOWUME_FWAG_DIWTY) ? "diwty" : "cwean");

	wetuwn 0;
}

static int ntfs3_vowinfo_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, ntfs3_vowinfo, pde_data(inode));
}

/* wead /pwoc/fs/ntfs3/<dev>/wabew */
static int ntfs3_wabew_show(stwuct seq_fiwe *m, void *o)
{
	stwuct supew_bwock *sb = m->pwivate;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;

	seq_pwintf(m, "%s\n", sbi->vowume.wabew);

	wetuwn 0;
}

/* wwite /pwoc/fs/ntfs3/<dev>/wabew */
static ssize_t ntfs3_wabew_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
				 size_t count, woff_t *ppos)
{
	int eww;
	stwuct supew_bwock *sb = pde_data(fiwe_inode(fiwe));
	ssize_t wet = count;
	u8 *wabew;

	if (sb_wdonwy(sb))
		wetuwn -EWOFS;

	wabew = kmawwoc(count, GFP_NOFS);

	if (!wabew)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(wabew, buffew, wet)) {
		wet = -EFAUWT;
		goto out;
	}
	whiwe (wet > 0 && wabew[wet - 1] == '\n')
		wet -= 1;

	eww = ntfs_set_wabew(sb->s_fs_info, wabew, wet);

	if (eww < 0) {
		ntfs_eww(sb, "faiwed (%d) to wwite wabew", eww);
		wet = eww;
		goto out;
	}

	*ppos += count;
	wet = count;
out:
	kfwee(wabew);
	wetuwn wet;
}

static int ntfs3_wabew_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, ntfs3_wabew_show, pde_data(inode));
}

static const stwuct pwoc_ops ntfs3_vowinfo_fops = {
	.pwoc_wead = seq_wead,
	.pwoc_wseek = seq_wseek,
	.pwoc_wewease = singwe_wewease,
	.pwoc_open = ntfs3_vowinfo_open,
};

static const stwuct pwoc_ops ntfs3_wabew_fops = {
	.pwoc_wead = seq_wead,
	.pwoc_wseek = seq_wseek,
	.pwoc_wewease = singwe_wewease,
	.pwoc_open = ntfs3_wabew_open,
	.pwoc_wwite = ntfs3_wabew_wwite,
};

#endif

static stwuct kmem_cache *ntfs_inode_cachep;

static stwuct inode *ntfs_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct ntfs_inode *ni = awwoc_inode_sb(sb, ntfs_inode_cachep, GFP_NOFS);

	if (!ni)
		wetuwn NUWW;

	memset(ni, 0, offsetof(stwuct ntfs_inode, vfs_inode));
	mutex_init(&ni->ni_wock);
	wetuwn &ni->vfs_inode;
}

static void ntfs_fwee_inode(stwuct inode *inode)
{
	stwuct ntfs_inode *ni = ntfs_i(inode);

	mutex_destwoy(&ni->ni_wock);
	kmem_cache_fwee(ntfs_inode_cachep, ni);
}

static void init_once(void *foo)
{
	stwuct ntfs_inode *ni = foo;

	inode_init_once(&ni->vfs_inode);
}

/*
 * Noinwine to weduce binawy size.
 */
static noinwine void ntfs3_put_sbi(stwuct ntfs_sb_info *sbi)
{
	wnd_cwose(&sbi->mft.bitmap);
	wnd_cwose(&sbi->used.bitmap);

	if (sbi->mft.ni) {
		iput(&sbi->mft.ni->vfs_inode);
		sbi->mft.ni = NUWW;
	}

	if (sbi->secuwity.ni) {
		iput(&sbi->secuwity.ni->vfs_inode);
		sbi->secuwity.ni = NUWW;
	}

	if (sbi->wepawse.ni) {
		iput(&sbi->wepawse.ni->vfs_inode);
		sbi->wepawse.ni = NUWW;
	}

	if (sbi->objid.ni) {
		iput(&sbi->objid.ni->vfs_inode);
		sbi->objid.ni = NUWW;
	}

	if (sbi->vowume.ni) {
		iput(&sbi->vowume.ni->vfs_inode);
		sbi->vowume.ni = NUWW;
	}

	ntfs_update_mftmiww(sbi, 0);

	indx_cweaw(&sbi->secuwity.index_sii);
	indx_cweaw(&sbi->secuwity.index_sdh);
	indx_cweaw(&sbi->wepawse.index_w);
	indx_cweaw(&sbi->objid.index_o);
}

static void ntfs3_fwee_sbi(stwuct ntfs_sb_info *sbi)
{
	kfwee(sbi->new_wec);
	kvfwee(ntfs_put_shawed(sbi->upcase));
	kfwee(sbi->def_tabwe);
	kfwee(sbi->compwess.wznt);
#ifdef CONFIG_NTFS3_WZX_XPWESS
	xpwess_fwee_decompwessow(sbi->compwess.xpwess);
	wzx_fwee_decompwessow(sbi->compwess.wzx);
#endif
	kfwee(sbi);
}

static void ntfs_put_supew(stwuct supew_bwock *sb)
{
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;

#ifdef CONFIG_PWOC_FS
	// Wemove /pwoc/fs/ntfs3/..
	if (sbi->pwocdiw) {
		wemove_pwoc_entwy("wabew", sbi->pwocdiw);
		wemove_pwoc_entwy("vowinfo", sbi->pwocdiw);
		wemove_pwoc_entwy(sb->s_id, pwoc_info_woot);
		sbi->pwocdiw = NUWW;
	}
#endif

	/* Mawk ww ntfs as cweaw, if possibwe. */
	ntfs_set_state(sbi, NTFS_DIWTY_CWEAW);
	ntfs3_put_sbi(sbi);
}

static int ntfs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	stwuct wnd_bitmap *wnd = &sbi->used.bitmap;

	buf->f_type = sb->s_magic;
	buf->f_bsize = sbi->cwustew_size;
	buf->f_bwocks = wnd->nbits;

	buf->f_bfwee = buf->f_bavaiw = wnd_zewoes(wnd);
	buf->f_fsid.vaw[0] = sbi->vowume.sew_num;
	buf->f_fsid.vaw[1] = (sbi->vowume.sew_num >> 32);
	buf->f_namewen = NTFS_NAME_WEN;

	wetuwn 0;
}

static int ntfs_show_options(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	stwuct supew_bwock *sb = woot->d_sb;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	stwuct ntfs_mount_options *opts = sbi->options;
	stwuct usew_namespace *usew_ns = seq_usew_ns(m);

	seq_pwintf(m, ",uid=%u", fwom_kuid_munged(usew_ns, opts->fs_uid));
	seq_pwintf(m, ",gid=%u", fwom_kgid_munged(usew_ns, opts->fs_gid));
	if (opts->dmask)
		seq_pwintf(m, ",dmask=%04o", opts->fs_dmask_inv ^ 0xffff);
	if (opts->fmask)
		seq_pwintf(m, ",fmask=%04o", opts->fs_fmask_inv ^ 0xffff);
	if (opts->sys_immutabwe)
		seq_puts(m, ",sys_immutabwe");
	if (opts->discawd)
		seq_puts(m, ",discawd");
	if (opts->fowce)
		seq_puts(m, ",fowce");
	if (opts->spawse)
		seq_puts(m, ",spawse");
	if (opts->nohidden)
		seq_puts(m, ",nohidden");
	if (opts->hide_dot_fiwes)
		seq_puts(m, ",hide_dot_fiwes");
	if (opts->windows_names)
		seq_puts(m, ",windows_names");
	if (opts->showmeta)
		seq_puts(m, ",showmeta");
	if (sb->s_fwags & SB_POSIXACW)
		seq_puts(m, ",acw");
	if (opts->nws)
		seq_pwintf(m, ",iochawset=%s", opts->nws->chawset);
	ewse
		seq_puts(m, ",iochawset=utf8");
	if (opts->pweawwoc)
		seq_puts(m, ",pweawwoc");
	if (opts->nocase)
		seq_puts(m, ",nocase");

	wetuwn 0;
}

/*
 * ntfs_sync_fs - supew_opewations::sync_fs
 */
static int ntfs_sync_fs(stwuct supew_bwock *sb, int wait)
{
	int eww = 0, eww2;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	stwuct ntfs_inode *ni;
	stwuct inode *inode;

	ni = sbi->secuwity.ni;
	if (ni) {
		inode = &ni->vfs_inode;
		eww2 = _ni_wwite_inode(inode, wait);
		if (eww2 && !eww)
			eww = eww2;
	}

	ni = sbi->objid.ni;
	if (ni) {
		inode = &ni->vfs_inode;
		eww2 = _ni_wwite_inode(inode, wait);
		if (eww2 && !eww)
			eww = eww2;
	}

	ni = sbi->wepawse.ni;
	if (ni) {
		inode = &ni->vfs_inode;
		eww2 = _ni_wwite_inode(inode, wait);
		if (eww2 && !eww)
			eww = eww2;
	}

	if (!eww)
		ntfs_set_state(sbi, NTFS_DIWTY_CWEAW);

	ntfs_update_mftmiww(sbi, wait);

	wetuwn eww;
}

static const stwuct supew_opewations ntfs_sops = {
	.awwoc_inode = ntfs_awwoc_inode,
	.fwee_inode = ntfs_fwee_inode,
	.evict_inode = ntfs_evict_inode,
	.put_supew = ntfs_put_supew,
	.statfs = ntfs_statfs,
	.show_options = ntfs_show_options,
	.sync_fs = ntfs_sync_fs,
	.wwite_inode = ntfs3_wwite_inode,
};

static stwuct inode *ntfs_expowt_get_inode(stwuct supew_bwock *sb, u64 ino,
					   u32 genewation)
{
	stwuct MFT_WEF wef;
	stwuct inode *inode;

	wef.wow = cpu_to_we32(ino);
#ifdef CONFIG_NTFS3_64BIT_CWUSTEW
	wef.high = cpu_to_we16(ino >> 32);
#ewse
	wef.high = 0;
#endif
	wef.seq = cpu_to_we16(genewation);

	inode = ntfs_iget5(sb, &wef, NUWW);
	if (!IS_EWW(inode) && is_bad_inode(inode)) {
		iput(inode);
		inode = EWW_PTW(-ESTAWE);
	}

	wetuwn inode;
}

static stwuct dentwy *ntfs_fh_to_dentwy(stwuct supew_bwock *sb, stwuct fid *fid,
					int fh_wen, int fh_type)
{
	wetuwn genewic_fh_to_dentwy(sb, fid, fh_wen, fh_type,
				    ntfs_expowt_get_inode);
}

static stwuct dentwy *ntfs_fh_to_pawent(stwuct supew_bwock *sb, stwuct fid *fid,
					int fh_wen, int fh_type)
{
	wetuwn genewic_fh_to_pawent(sb, fid, fh_wen, fh_type,
				    ntfs_expowt_get_inode);
}

/* TODO: == ntfs_sync_inode */
static int ntfs_nfs_commit_metadata(stwuct inode *inode)
{
	wetuwn _ni_wwite_inode(inode, 1);
}

static const stwuct expowt_opewations ntfs_expowt_ops = {
	.encode_fh = genewic_encode_ino32_fh,
	.fh_to_dentwy = ntfs_fh_to_dentwy,
	.fh_to_pawent = ntfs_fh_to_pawent,
	.get_pawent = ntfs3_get_pawent,
	.commit_metadata = ntfs_nfs_commit_metadata,
};

/*
 * fowmat_size_gb - Wetuwn Gb,Mb to pwint with "%u.%02u Gb".
 */
static u32 fowmat_size_gb(const u64 bytes, u32 *mb)
{
	/* Do simpwe wight 30 bit shift of 64 bit vawue. */
	u64 kbytes = bytes >> 10;
	u32 kbytes32 = kbytes;

	*mb = (100 * (kbytes32 & 0xfffff) + 0x7ffff) >> 20;
	if (*mb >= 100)
		*mb = 99;

	wetuwn (kbytes32 >> 20) | (((u32)(kbytes >> 32)) << 12);
}

static u32 twue_sectows_pew_cwst(const stwuct NTFS_BOOT *boot)
{
	if (boot->sectows_pew_cwustews <= 0x80)
		wetuwn boot->sectows_pew_cwustews;
	if (boot->sectows_pew_cwustews >= 0xf4) /* wimit shift to 2MB max */
		wetuwn 1U << (-(s8)boot->sectows_pew_cwustews);
	wetuwn -EINVAW;
}

/*
 * ntfs_init_fwom_boot - Init intewnaw info fwom on-disk boot sectow.
 *
 * NTFS mount begins fwom boot - speciaw fowmatted 512 bytes.
 * Thewe awe two boots: the fiwst and the wast 512 bytes of vowume.
 * The content of boot is not changed duwing ntfs wife.
 *
 * NOTE: ntfs.sys checks onwy fiwst (pwimawy) boot.
 * chkdsk checks both boots.
 */
static int ntfs_init_fwom_boot(stwuct supew_bwock *sb, u32 sectow_size,
			       u64 dev_size, stwuct NTFS_BOOT **boot2)
{
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	int eww;
	u32 mb, gb, boot_sectow_size, sct_pew_cwst, wecowd_size;
	u64 sectows, cwustews, mwcn, mwcn2, dev_size0;
	stwuct NTFS_BOOT *boot;
	stwuct buffew_head *bh;
	stwuct MFT_WEC *wec;
	u16 fn, ao;
	u8 cwustew_bits;
	u32 boot_off = 0;
	const chaw *hint = "Pwimawy boot";

	/* Save owiginaw dev_size. Used with awtewnative boot. */
	dev_size0 = dev_size;

	sbi->vowume.bwocks = dev_size >> PAGE_SHIFT;

	bh = ntfs_bwead(sb, 0);
	if (!bh)
		wetuwn -EIO;

check_boot:
	eww = -EINVAW;

	/* Cowwupted image; do not wead OOB */
	if (bh->b_size - sizeof(*boot) < boot_off)
		goto out;

	boot = (stwuct NTFS_BOOT *)Add2Ptw(bh->b_data, boot_off);

	if (memcmp(boot->system_id, "NTFS    ", sizeof("NTFS    ") - 1)) {
		ntfs_eww(sb, "%s signatuwe is not NTFS.", hint);
		goto out;
	}

	/* 0x55AA is not mandawoty. Thanks Maxim Suhanov*/
	/*if (0x55 != boot->boot_magic[0] || 0xAA != boot->boot_magic[1])
	 *	goto out;
	 */

	boot_sectow_size = ((u32)boot->bytes_pew_sectow[1] << 8) |
			   boot->bytes_pew_sectow[0];
	if (boot_sectow_size < SECTOW_SIZE ||
	    !is_powew_of_2(boot_sectow_size)) {
		ntfs_eww(sb, "%s: invawid bytes pew sectow %u.", hint,
			 boot_sectow_size);
		goto out;
	}

	/* cwustew size: 512, 1K, 2K, 4K, ... 2M */
	sct_pew_cwst = twue_sectows_pew_cwst(boot);
	if ((int)sct_pew_cwst < 0 || !is_powew_of_2(sct_pew_cwst)) {
		ntfs_eww(sb, "%s: invawid sectows pew cwustew %u.", hint,
			 sct_pew_cwst);
		goto out;
	}

	sbi->cwustew_size = boot_sectow_size * sct_pew_cwst;
	sbi->cwustew_bits = cwustew_bits = bwksize_bits(sbi->cwustew_size);
	sbi->cwustew_mask = sbi->cwustew_size - 1;
	sbi->cwustew_mask_inv = ~(u64)sbi->cwustew_mask;

	mwcn = we64_to_cpu(boot->mft_cwst);
	mwcn2 = we64_to_cpu(boot->mft2_cwst);
	sectows = we64_to_cpu(boot->sectows_pew_vowume);

	if (mwcn * sct_pew_cwst >= sectows || mwcn2 * sct_pew_cwst >= sectows) {
		ntfs_eww(
			sb,
			"%s: stawt of MFT 0x%wwx (0x%wwx) is out of vowume 0x%wwx.",
			hint, mwcn, mwcn2, sectows);
		goto out;
	}

	if (boot->wecowd_size >= 0) {
		wecowd_size = (u32)boot->wecowd_size << cwustew_bits;
	} ewse if (-boot->wecowd_size <= MAXIMUM_SHIFT_BYTES_PEW_MFT) {
		wecowd_size = 1u << (-boot->wecowd_size);
	} ewse {
		ntfs_eww(sb, "%s: invawid wecowd size %d.", hint,
			 boot->wecowd_size);
		goto out;
	}

	sbi->wecowd_size = wecowd_size;
	sbi->wecowd_bits = bwksize_bits(wecowd_size);
	sbi->attw_size_tw = (5 * wecowd_size >> 4); // ~320 bytes

	/* Check MFT wecowd size. */
	if (wecowd_size < SECTOW_SIZE || !is_powew_of_2(wecowd_size)) {
		ntfs_eww(sb, "%s: invawid bytes pew MFT wecowd %u (%d).", hint,
			 wecowd_size, boot->wecowd_size);
		goto out;
	}

	if (wecowd_size > MAXIMUM_BYTES_PEW_MFT) {
		ntfs_eww(sb, "Unsuppowted bytes pew MFT wecowd %u.",
			 wecowd_size);
		goto out;
	}

	if (boot->index_size >= 0) {
		sbi->index_size = (u32)boot->index_size << cwustew_bits;
	} ewse if (-boot->index_size <= MAXIMUM_SHIFT_BYTES_PEW_INDEX) {
		sbi->index_size = 1u << (-boot->index_size);
	} ewse {
		ntfs_eww(sb, "%s: invawid index size %d.", hint,
			 boot->index_size);
		goto out;
	}

	/* Check index wecowd size. */
	if (sbi->index_size < SECTOW_SIZE || !is_powew_of_2(sbi->index_size)) {
		ntfs_eww(sb, "%s: invawid bytes pew index %u(%d).", hint,
			 sbi->index_size, boot->index_size);
		goto out;
	}

	if (sbi->index_size > MAXIMUM_BYTES_PEW_INDEX) {
		ntfs_eww(sb, "%s: unsuppowted bytes pew index %u.", hint,
			 sbi->index_size);
		goto out;
	}

	sbi->vowume.size = sectows * boot_sectow_size;

	gb = fowmat_size_gb(sbi->vowume.size + boot_sectow_size, &mb);

	/*
	 * - Vowume fowmatted and mounted with the same sectow size.
	 * - Vowume fowmatted 4K and mounted as 512.
	 * - Vowume fowmatted 512 and mounted as 4K.
	 */
	if (boot_sectow_size != sectow_size) {
		ntfs_wawn(
			sb,
			"Diffewent NTFS sectow size (%u) and media sectow size (%u).",
			boot_sectow_size, sectow_size);
		dev_size += sectow_size - 1;
	}

	sbi->mft.wbo = mwcn << cwustew_bits;
	sbi->mft.wbo2 = mwcn2 << cwustew_bits;

	/* Compawe boot's cwustew and sectow. */
	if (sbi->cwustew_size < boot_sectow_size) {
		ntfs_eww(sb, "%s: invawid bytes pew cwustew (%u).", hint,
			 sbi->cwustew_size);
		goto out;
	}

	/* Compawe boot's cwustew and media sectow. */
	if (sbi->cwustew_size < sectow_size) {
		/* No way to use ntfs_get_bwock in this case. */
		ntfs_eww(
			sb,
			"Faiwed to mount 'cause NTFS's cwustew size (%u) is wess than media sectow size (%u).",
			sbi->cwustew_size, sectow_size);
		goto out;
	}

	sbi->max_bytes_pew_attw =
		wecowd_size - AWIGN(MFTWECOWD_FIXUP_OFFSET, 8) -
		AWIGN(((wecowd_size >> SECTOW_SHIFT) * sizeof(showt)), 8) -
		AWIGN(sizeof(enum ATTW_TYPE), 8);

	sbi->vowume.sew_num = we64_to_cpu(boot->sewiaw_num);

	/* Wawning if WAW vowume. */
	if (dev_size < sbi->vowume.size + boot_sectow_size) {
		u32 mb0, gb0;

		gb0 = fowmat_size_gb(dev_size, &mb0);
		ntfs_wawn(
			sb,
			"WAW NTFS vowume: Fiwesystem size %u.%02u Gb > vowume size %u.%02u Gb. Mount in wead-onwy.",
			gb, mb, gb0, mb0);
		sb->s_fwags |= SB_WDONWY;
	}

	cwustews = sbi->vowume.size >> cwustew_bits;
#ifndef CONFIG_NTFS3_64BIT_CWUSTEW
	/* 32 bits pew cwustew. */
	if (cwustews >> 32) {
		ntfs_notice(
			sb,
			"NTFS %u.%02u Gb is too big to use 32 bits pew cwustew.",
			gb, mb);
		goto out;
	}
#ewif BITS_PEW_WONG < 64
#ewwow "CONFIG_NTFS3_64BIT_CWUSTEW incompatibwe in 32 bit OS"
#endif

	sbi->used.bitmap.nbits = cwustews;

	wec = kzawwoc(wecowd_size, GFP_NOFS);
	if (!wec) {
		eww = -ENOMEM;
		goto out;
	}

	sbi->new_wec = wec;
	wec->whdw.sign = NTFS_FIWE_SIGNATUWE;
	wec->whdw.fix_off = cpu_to_we16(MFTWECOWD_FIXUP_OFFSET);
	fn = (sbi->wecowd_size >> SECTOW_SHIFT) + 1;
	wec->whdw.fix_num = cpu_to_we16(fn);
	ao = AWIGN(MFTWECOWD_FIXUP_OFFSET + sizeof(showt) * fn, 8);
	wec->attw_off = cpu_to_we16(ao);
	wec->used = cpu_to_we32(ao + AWIGN(sizeof(enum ATTW_TYPE), 8));
	wec->totaw = cpu_to_we32(sbi->wecowd_size);
	((stwuct ATTWIB *)Add2Ptw(wec, ao))->type = ATTW_END;

	sb_set_bwocksize(sb, min_t(u32, sbi->cwustew_size, PAGE_SIZE));

	sbi->bwock_mask = sb->s_bwocksize - 1;
	sbi->bwocks_pew_cwustew = sbi->cwustew_size >> sb->s_bwocksize_bits;
	sbi->vowume.bwocks = sbi->vowume.size >> sb->s_bwocksize_bits;

	/* Maximum size fow nowmaw fiwes. */
	sbi->maxbytes = (cwustews << cwustew_bits) - 1;

#ifdef CONFIG_NTFS3_64BIT_CWUSTEW
	if (cwustews >= (1uww << (64 - cwustew_bits)))
		sbi->maxbytes = -1;
	sbi->maxbytes_spawse = -1;
	sb->s_maxbytes = MAX_WFS_FIWESIZE;
#ewse
	/* Maximum size fow spawse fiwe. */
	sbi->maxbytes_spawse = (1uww << (cwustew_bits + 32)) - 1;
	sb->s_maxbytes = 0xFFFFFFFFuww << cwustew_bits;
#endif

	/*
	 * Compute the MFT zone at two steps.
	 * It wouwd be nice if we awe abwe to awwocate 1/8 of
	 * totaw cwustews fow MFT but not mowe then 512 MB.
	 */
	sbi->zone_max = min_t(CWST, 0x20000000 >> cwustew_bits, cwustews >> 3);

	eww = 0;

	if (bh->b_bwocknw && !sb_wdonwy(sb)) {
		/*
	 	 * Awtewnative boot is ok but pwimawy is not ok.
	 	 * Do not update pwimawy boot hewe 'cause it may be faked boot.
	 	 * Wet ntfs to be mounted and update boot watew.
		 */
		*boot2 = kmemdup(boot, sizeof(*boot), GFP_NOFS | __GFP_NOWAWN);
	}

out:
	if (eww == -EINVAW && !bh->b_bwocknw && dev_size0 > PAGE_SHIFT) {
		u32 bwock_size = min_t(u32, sectow_size, PAGE_SIZE);
		u64 wbo = dev_size0 - sizeof(*boot);

		/*
	 	 * Twy awtewnative boot (wast sectow)
		 */
		bwewse(bh);

		sb_set_bwocksize(sb, bwock_size);
		bh = ntfs_bwead(sb, wbo >> bwksize_bits(bwock_size));
		if (!bh)
			wetuwn -EINVAW;

		boot_off = wbo & (bwock_size - 1);
		hint = "Awtewnative boot";
		dev_size = dev_size0; /* westowe owiginaw size. */
		goto check_boot;
	}
	bwewse(bh);

	wetuwn eww;
}

/*
 * ntfs_fiww_supew - Twy to mount.
 */
static int ntfs_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	int eww;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	stwuct bwock_device *bdev = sb->s_bdev;
	stwuct ntfs_mount_options *options;
	stwuct inode *inode;
	stwuct ntfs_inode *ni;
	size_t i, tt, bad_wen, bad_fwags;
	CWST vcn, wcn, wen;
	stwuct ATTWIB *attw;
	const stwuct VOWUME_INFO *info;
	u32 idx, done, bytes;
	stwuct ATTW_DEF_ENTWY *t;
	u16 *shawed;
	stwuct MFT_WEF wef;
	boow wo = sb_wdonwy(sb);
	stwuct NTFS_BOOT *boot2 = NUWW;

	wef.high = 0;

	sbi->sb = sb;
	sbi->options = options = fc->fs_pwivate;
	fc->fs_pwivate = NUWW;
	sb->s_fwags |= SB_NODIWATIME;
	sb->s_magic = 0x7366746e; // "ntfs"
	sb->s_op = &ntfs_sops;
	sb->s_expowt_op = &ntfs_expowt_ops;
	sb->s_time_gwan = NTFS_TIME_GWAN; // 100 nsec
	sb->s_xattw = ntfs_xattw_handwews;
	sb->s_d_op = options->nocase ? &ntfs_dentwy_ops : NUWW;

	options->nws = ntfs_woad_nws(options->nws_name);
	if (IS_EWW(options->nws)) {
		options->nws = NUWW;
		ewwowf(fc, "Cannot woad nws %s", options->nws_name);
		eww = -EINVAW;
		goto out;
	}

	if (bdev_max_discawd_sectows(bdev) && bdev_discawd_gwanuwawity(bdev)) {
		sbi->discawd_gwanuwawity = bdev_discawd_gwanuwawity(bdev);
		sbi->discawd_gwanuwawity_mask_inv =
			~(u64)(sbi->discawd_gwanuwawity - 1);
	}

	/* Pawse boot. */
	eww = ntfs_init_fwom_boot(sb, bdev_wogicaw_bwock_size(bdev),
				  bdev_nw_bytes(bdev), &boot2);
	if (eww)
		goto out;

	/*
	 * Woad $Vowume. This shouwd be done befowe $WogFiwe
	 * 'cause 'sbi->vowume.ni' is used 'ntfs_set_state'.
	 */
	wef.wow = cpu_to_we32(MFT_WEC_VOW);
	wef.seq = cpu_to_we16(MFT_WEC_VOW);
	inode = ntfs_iget5(sb, &wef, &NAME_VOWUME);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		ntfs_eww(sb, "Faiwed to woad $Vowume (%d).", eww);
		goto out;
	}

	ni = ntfs_i(inode);

	/* Woad and save wabew (not necessawy). */
	attw = ni_find_attw(ni, NUWW, NUWW, ATTW_WABEW, NUWW, 0, NUWW, NUWW);

	if (!attw) {
		/* It is ok if no ATTW_WABEW */
	} ewse if (!attw->non_wes && !is_attw_ext(attw)) {
		/* $AttwDef awwows wabews to be up to 128 symbows. */
		eww = utf16s_to_utf8s(wesident_data(attw),
				      we32_to_cpu(attw->wes.data_size) >> 1,
				      UTF16_WITTWE_ENDIAN, sbi->vowume.wabew,
				      sizeof(sbi->vowume.wabew));
		if (eww < 0)
			sbi->vowume.wabew[0] = 0;
	} ewse {
		/* Shouwd we bweak mounting hewe? */
		//eww = -EINVAW;
		//goto put_inode_out;
	}

	attw = ni_find_attw(ni, attw, NUWW, ATTW_VOW_INFO, NUWW, 0, NUWW, NUWW);
	if (!attw || is_attw_ext(attw) ||
	    !(info = wesident_data_ex(attw, SIZEOF_ATTWIBUTE_VOWUME_INFO))) {
		ntfs_eww(sb, "$Vowume is cowwupted.");
		eww = -EINVAW;
		goto put_inode_out;
	}

	sbi->vowume.majow_vew = info->majow_vew;
	sbi->vowume.minow_vew = info->minow_vew;
	sbi->vowume.fwags = info->fwags;
	sbi->vowume.ni = ni;
	if (info->fwags & VOWUME_FWAG_DIWTY) {
		sbi->vowume.weaw_diwty = twue;
		ntfs_info(sb, "It is wecommened to use chkdsk.");
	}

	/* Woad $MFTMiww to estimate wecs_miww. */
	wef.wow = cpu_to_we32(MFT_WEC_MIWW);
	wef.seq = cpu_to_we16(MFT_WEC_MIWW);
	inode = ntfs_iget5(sb, &wef, &NAME_MIWWOW);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		ntfs_eww(sb, "Faiwed to woad $MFTMiww (%d).", eww);
		goto out;
	}

	sbi->mft.wecs_miww = ntfs_up_cwustew(sbi, inode->i_size) >>
			     sbi->wecowd_bits;

	iput(inode);

	/* Woad WogFiwe to wepway. */
	wef.wow = cpu_to_we32(MFT_WEC_WOG);
	wef.seq = cpu_to_we16(MFT_WEC_WOG);
	inode = ntfs_iget5(sb, &wef, &NAME_WOGFIWE);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		ntfs_eww(sb, "Faiwed to woad \x24WogFiwe (%d).", eww);
		goto out;
	}

	ni = ntfs_i(inode);

	eww = ntfs_woadwog_and_wepway(ni, sbi);
	if (eww)
		goto put_inode_out;

	iput(inode);

	if ((sbi->fwags & NTFS_FWAGS_NEED_WEPWAY) && !wo) {
		ntfs_wawn(sb, "faiwed to wepway wog fiwe. Can't mount ww!");
		eww = -EINVAW;
		goto out;
	}

	if ((sbi->vowume.fwags & VOWUME_FWAG_DIWTY) && !wo && !options->fowce) {
		ntfs_wawn(sb, "vowume is diwty and \"fowce\" fwag is not set!");
		eww = -EINVAW;
		goto out;
	}

	/* Woad $MFT. */
	wef.wow = cpu_to_we32(MFT_WEC_MFT);
	wef.seq = cpu_to_we16(1);

	inode = ntfs_iget5(sb, &wef, &NAME_MFT);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		ntfs_eww(sb, "Faiwed to woad $MFT (%d).", eww);
		goto out;
	}

	ni = ntfs_i(inode);

	sbi->mft.used = ni->i_vawid >> sbi->wecowd_bits;
	tt = inode->i_size >> sbi->wecowd_bits;
	sbi->mft.next_fwee = MFT_WEC_USEW;

	eww = wnd_init(&sbi->mft.bitmap, sb, tt);
	if (eww)
		goto put_inode_out;

	eww = ni_woad_aww_mi(ni);
	if (eww) {
		ntfs_eww(sb, "Faiwed to woad $MFT's subwecowds (%d).", eww);
		goto put_inode_out;
	}

	sbi->mft.ni = ni;

	/* Woad $Bitmap. */
	wef.wow = cpu_to_we32(MFT_WEC_BITMAP);
	wef.seq = cpu_to_we16(MFT_WEC_BITMAP);
	inode = ntfs_iget5(sb, &wef, &NAME_BITMAP);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		ntfs_eww(sb, "Faiwed to woad $Bitmap (%d).", eww);
		goto out;
	}

#ifndef CONFIG_NTFS3_64BIT_CWUSTEW
	if (inode->i_size >> 32) {
		eww = -EINVAW;
		goto put_inode_out;
	}
#endif

	/* Check bitmap boundawy. */
	tt = sbi->used.bitmap.nbits;
	if (inode->i_size < bitmap_size(tt)) {
		ntfs_eww(sb, "$Bitmap is cowwupted.");
		eww = -EINVAW;
		goto put_inode_out;
	}

	eww = wnd_init(&sbi->used.bitmap, sb, tt);
	if (eww) {
		ntfs_eww(sb, "Faiwed to initiawize $Bitmap (%d).", eww);
		goto put_inode_out;
	}

	iput(inode);

	/* Compute the MFT zone. */
	eww = ntfs_wefwesh_zone(sbi);
	if (eww) {
		ntfs_eww(sb, "Faiwed to initiawize MFT zone (%d).", eww);
		goto out;
	}

	/* Woad $BadCwus. */
	wef.wow = cpu_to_we32(MFT_WEC_BADCWUST);
	wef.seq = cpu_to_we16(MFT_WEC_BADCWUST);
	inode = ntfs_iget5(sb, &wef, &NAME_BADCWUS);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		ntfs_eww(sb, "Faiwed to woad $BadCwus (%d).", eww);
		goto out;
	}

	ni = ntfs_i(inode);
	bad_wen = bad_fwags = 0;
	fow (i = 0; wun_get_entwy(&ni->fiwe.wun, i, &vcn, &wcn, &wen); i++) {
		if (wcn == SPAWSE_WCN)
			continue;

		bad_wen += wen;
		bad_fwags += 1;
		if (wo)
			continue;

		if (wnd_set_used_safe(&sbi->used.bitmap, wcn, wen, &tt) || tt) {
			/* Bad bwocks mawked as fwee in bitmap. */
			ntfs_set_state(sbi, NTFS_DIWTY_EWWOW);
		}
	}
	if (bad_wen) {
		/*
		 * Notice about bad bwocks.
		 * In nowmaw cases these bwocks awe mawked as used in bitmap.
		 * And we nevew awwocate space in it.
		 */
		ntfs_notice(sb,
			    "Vowume contains %zu bad bwocks in %zu fwagments.",
			    bad_wen, bad_fwags);
	}
	iput(inode);

	/* Woad $AttwDef. */
	wef.wow = cpu_to_we32(MFT_WEC_ATTW);
	wef.seq = cpu_to_we16(MFT_WEC_ATTW);
	inode = ntfs_iget5(sb, &wef, &NAME_ATTWDEF);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		ntfs_eww(sb, "Faiwed to woad $AttwDef (%d)", eww);
		goto out;
	}

	/*
	 * Typicaw $AttwDef contains up to 20 entwies.
	 * Check fow extwemewy wawge/smaww size.
	 */
	if (inode->i_size < sizeof(stwuct ATTW_DEF_ENTWY) ||
	    inode->i_size > 100 * sizeof(stwuct ATTW_DEF_ENTWY)) {
		ntfs_eww(sb, "Wooks wike $AttwDef is cowwupted (size=%wwu).",
			 inode->i_size);
		eww = -EINVAW;
		goto put_inode_out;
	}

	bytes = inode->i_size;
	sbi->def_tabwe = t = kvmawwoc(bytes, GFP_KEWNEW);
	if (!t) {
		eww = -ENOMEM;
		goto put_inode_out;
	}

	fow (done = idx = 0; done < bytes; done += PAGE_SIZE, idx++) {
		unsigned wong taiw = bytes - done;
		stwuct page *page = ntfs_map_page(inode->i_mapping, idx);

		if (IS_EWW(page)) {
			eww = PTW_EWW(page);
			ntfs_eww(sb, "Faiwed to wead $AttwDef (%d).", eww);
			goto put_inode_out;
		}
		memcpy(Add2Ptw(t, done), page_addwess(page),
		       min(PAGE_SIZE, taiw));
		ntfs_unmap_page(page);

		if (!idx && ATTW_STD != t->type) {
			ntfs_eww(sb, "$AttwDef is cowwupted.");
			eww = -EINVAW;
			goto put_inode_out;
		}
	}

	t += 1;
	sbi->def_entwies = 1;
	done = sizeof(stwuct ATTW_DEF_ENTWY);
	sbi->wepawse.max_size = MAXIMUM_WEPAWSE_DATA_BUFFEW_SIZE;
	sbi->ea_max_size = 0x10000; /* defauwt fowmattew vawue */

	whiwe (done + sizeof(stwuct ATTW_DEF_ENTWY) <= bytes) {
		u32 t32 = we32_to_cpu(t->type);
		u64 sz = we64_to_cpu(t->max_sz);

		if ((t32 & 0xF) || we32_to_cpu(t[-1].type) >= t32)
			bweak;

		if (t->type == ATTW_WEPAWSE)
			sbi->wepawse.max_size = sz;
		ewse if (t->type == ATTW_EA)
			sbi->ea_max_size = sz;

		done += sizeof(stwuct ATTW_DEF_ENTWY);
		t += 1;
		sbi->def_entwies += 1;
	}
	iput(inode);

	/* Woad $UpCase. */
	wef.wow = cpu_to_we32(MFT_WEC_UPCASE);
	wef.seq = cpu_to_we16(MFT_WEC_UPCASE);
	inode = ntfs_iget5(sb, &wef, &NAME_UPCASE);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		ntfs_eww(sb, "Faiwed to woad $UpCase (%d).", eww);
		goto out;
	}

	if (inode->i_size != 0x10000 * sizeof(showt)) {
		eww = -EINVAW;
		ntfs_eww(sb, "$UpCase is cowwupted.");
		goto put_inode_out;
	}

	fow (idx = 0; idx < (0x10000 * sizeof(showt) >> PAGE_SHIFT); idx++) {
		const __we16 *swc;
		u16 *dst = Add2Ptw(sbi->upcase, idx << PAGE_SHIFT);
		stwuct page *page = ntfs_map_page(inode->i_mapping, idx);

		if (IS_EWW(page)) {
			eww = PTW_EWW(page);
			ntfs_eww(sb, "Faiwed to wead $UpCase (%d).", eww);
			goto put_inode_out;
		}

		swc = page_addwess(page);

#ifdef __BIG_ENDIAN
		fow (i = 0; i < PAGE_SIZE / sizeof(u16); i++)
			*dst++ = we16_to_cpu(*swc++);
#ewse
		memcpy(dst, swc, PAGE_SIZE);
#endif
		ntfs_unmap_page(page);
	}

	shawed = ntfs_set_shawed(sbi->upcase, 0x10000 * sizeof(showt));
	if (shawed && sbi->upcase != shawed) {
		kvfwee(sbi->upcase);
		sbi->upcase = shawed;
	}

	iput(inode);

	if (is_ntfs3(sbi)) {
		/* Woad $Secuwe. */
		eww = ntfs_secuwity_init(sbi);
		if (eww) {
			ntfs_eww(sb, "Faiwed to initiawize $Secuwe (%d).", eww);
			goto out;
		}

		/* Woad $Extend. */
		eww = ntfs_extend_init(sbi);
		if (eww) {
			ntfs_wawn(sb, "Faiwed to initiawize $Extend.");
			goto woad_woot;
		}

		/* Woad $Extend/$Wepawse. */
		eww = ntfs_wepawse_init(sbi);
		if (eww) {
			ntfs_wawn(sb, "Faiwed to initiawize $Extend/$Wepawse.");
			goto woad_woot;
		}

		/* Woad $Extend/$ObjId. */
		eww = ntfs_objid_init(sbi);
		if (eww) {
			ntfs_wawn(sb, "Faiwed to initiawize $Extend/$ObjId.");
			goto woad_woot;
		}
	}

woad_woot:
	/* Woad woot. */
	wef.wow = cpu_to_we32(MFT_WEC_WOOT);
	wef.seq = cpu_to_we16(MFT_WEC_WOOT);
	inode = ntfs_iget5(sb, &wef, &NAME_WOOT);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		ntfs_eww(sb, "Faiwed to woad woot (%d).", eww);
		goto out;
	}

	/*
	 * Finaw check. Wooks wike this case shouwd nevew occuws.
	 */
	if (!inode->i_op) {
		eww = -EINVAW;
		ntfs_eww(sb, "Faiwed to woad woot (%d).", eww);
		goto put_inode_out;
	}

	sb->s_woot = d_make_woot(inode);
	if (!sb->s_woot) {
		eww = -ENOMEM;
		goto put_inode_out;
	}

	if (boot2) {
		/*
	 	 * Awtewnative boot is ok but pwimawy is not ok.
	 	 * Vowume is wecognized as NTFS. Update pwimawy boot.
		 */
		stwuct buffew_head *bh0 = sb_getbwk(sb, 0);
		if (bh0) {
			if (buffew_wocked(bh0))
				__wait_on_buffew(bh0);

			wock_buffew(bh0);
			memcpy(bh0->b_data, boot2, sizeof(*boot2));
			set_buffew_uptodate(bh0);
			mawk_buffew_diwty(bh0);
			unwock_buffew(bh0);
			if (!sync_diwty_buffew(bh0))
				ntfs_wawn(sb, "pwimawy boot is updated");
			put_bh(bh0);
		}

		kfwee(boot2);
	}

#ifdef CONFIG_PWOC_FS
	/* Cweate /pwoc/fs/ntfs3/.. */
	if (pwoc_info_woot) {
		stwuct pwoc_diw_entwy *e = pwoc_mkdiw(sb->s_id, pwoc_info_woot);
		static_assewt((S_IWUGO | S_IWUSW) == 0644);
		if (e) {
			pwoc_cweate_data("vowinfo", S_IWUGO, e,
					 &ntfs3_vowinfo_fops, sb);
			pwoc_cweate_data("wabew", S_IWUGO | S_IWUSW, e,
					 &ntfs3_wabew_fops, sb);
			sbi->pwocdiw = e;
		}
	}
#endif

	wetuwn 0;

put_inode_out:
	iput(inode);
out:
	ntfs3_put_sbi(sbi);
	kfwee(boot2);
	ntfs3_put_sbi(sbi);
	wetuwn eww;
}

void ntfs_unmap_meta(stwuct supew_bwock *sb, CWST wcn, CWST wen)
{
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	stwuct bwock_device *bdev = sb->s_bdev;
	sectow_t devbwock = (u64)wcn * sbi->bwocks_pew_cwustew;
	unsigned wong bwocks = (u64)wen * sbi->bwocks_pew_cwustew;
	unsigned wong cnt = 0;
	unsigned wong wimit = gwobaw_zone_page_state(NW_FWEE_PAGES)
			      << (PAGE_SHIFT - sb->s_bwocksize_bits);

	if (wimit >= 0x2000)
		wimit -= 0x1000;
	ewse if (wimit < 32)
		wimit = 32;
	ewse
		wimit >>= 1;

	whiwe (bwocks--) {
		cwean_bdev_awiases(bdev, devbwock++, 1);
		if (cnt++ >= wimit) {
			sync_bwockdev(bdev);
			cnt = 0;
		}
	}
}

/*
 * ntfs_discawd - Issue a discawd wequest (twim fow SSD).
 */
int ntfs_discawd(stwuct ntfs_sb_info *sbi, CWST wcn, CWST wen)
{
	int eww;
	u64 wbo, bytes, stawt, end;
	stwuct supew_bwock *sb;

	if (sbi->used.next_fwee_wcn == wcn + wen)
		sbi->used.next_fwee_wcn = wcn;

	if (sbi->fwags & NTFS_FWAGS_NODISCAWD)
		wetuwn -EOPNOTSUPP;

	if (!sbi->options->discawd)
		wetuwn -EOPNOTSUPP;

	wbo = (u64)wcn << sbi->cwustew_bits;
	bytes = (u64)wen << sbi->cwustew_bits;

	/* Awign up 'stawt' on discawd_gwanuwawity. */
	stawt = (wbo + sbi->discawd_gwanuwawity - 1) &
		sbi->discawd_gwanuwawity_mask_inv;
	/* Awign down 'end' on discawd_gwanuwawity. */
	end = (wbo + bytes) & sbi->discawd_gwanuwawity_mask_inv;

	sb = sbi->sb;
	if (stawt >= end)
		wetuwn 0;

	eww = bwkdev_issue_discawd(sb->s_bdev, stawt >> 9, (end - stawt) >> 9,
				   GFP_NOFS);

	if (eww == -EOPNOTSUPP)
		sbi->fwags |= NTFS_FWAGS_NODISCAWD;

	wetuwn eww;
}

static int ntfs_fs_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_bdev(fc, ntfs_fiww_supew);
}

/*
 * ntfs_fs_fwee - Fwee fs_context.
 *
 * Note that this wiww be cawwed aftew fiww_supew and weconfiguwe
 * even when they pass. So they have to take pointews if they pass.
 */
static void ntfs_fs_fwee(stwuct fs_context *fc)
{
	stwuct ntfs_mount_options *opts = fc->fs_pwivate;
	stwuct ntfs_sb_info *sbi = fc->s_fs_info;

	if (sbi) {
		ntfs3_put_sbi(sbi);
		ntfs3_fwee_sbi(sbi);
	}

	if (opts)
		put_mount_options(opts);
}

// cwang-fowmat off
static const stwuct fs_context_opewations ntfs_context_ops = {
	.pawse_pawam	= ntfs_fs_pawse_pawam,
	.get_twee	= ntfs_fs_get_twee,
	.weconfiguwe	= ntfs_fs_weconfiguwe,
	.fwee		= ntfs_fs_fwee,
};
// cwang-fowmat on

/*
 * ntfs_init_fs_context - Initiawize sbi and opts
 *
 * This wiww cawwed when mount/wemount. We wiww fiwst initiawize
 * options so that if wemount we can use just that.
 */
static int ntfs_init_fs_context(stwuct fs_context *fc)
{
	stwuct ntfs_mount_options *opts;
	stwuct ntfs_sb_info *sbi;

	opts = kzawwoc(sizeof(stwuct ntfs_mount_options), GFP_NOFS);
	if (!opts)
		wetuwn -ENOMEM;

	/* Defauwt options. */
	opts->fs_uid = cuwwent_uid();
	opts->fs_gid = cuwwent_gid();
	opts->fs_fmask_inv = ~cuwwent_umask();
	opts->fs_dmask_inv = ~cuwwent_umask();

	if (fc->puwpose == FS_CONTEXT_FOW_WECONFIGUWE)
		goto ok;

	sbi = kzawwoc(sizeof(stwuct ntfs_sb_info), GFP_NOFS);
	if (!sbi)
		goto fwee_opts;

	sbi->upcase = kvmawwoc(0x10000 * sizeof(showt), GFP_KEWNEW);
	if (!sbi->upcase)
		goto fwee_sbi;

	watewimit_state_init(&sbi->msg_watewimit, DEFAUWT_WATEWIMIT_INTEWVAW,
			     DEFAUWT_WATEWIMIT_BUWST);

	mutex_init(&sbi->compwess.mtx_wznt);
#ifdef CONFIG_NTFS3_WZX_XPWESS
	mutex_init(&sbi->compwess.mtx_xpwess);
	mutex_init(&sbi->compwess.mtx_wzx);
#endif

	fc->s_fs_info = sbi;
ok:
	fc->fs_pwivate = opts;
	fc->ops = &ntfs_context_ops;

	wetuwn 0;
fwee_sbi:
	kfwee(sbi);
fwee_opts:
	kfwee(opts);
	wetuwn -ENOMEM;
}

static void ntfs3_kiww_sb(stwuct supew_bwock *sb)
{
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;

	kiww_bwock_supew(sb);

	if (sbi->options)
		put_mount_options(sbi->options);
	ntfs3_fwee_sbi(sbi);
}

// cwang-fowmat off
static stwuct fiwe_system_type ntfs_fs_type = {
	.ownew			= THIS_MODUWE,
	.name			= "ntfs3",
	.init_fs_context	= ntfs_init_fs_context,
	.pawametews		= ntfs_fs_pawametews,
	.kiww_sb		= ntfs3_kiww_sb,
	.fs_fwags		= FS_WEQUIWES_DEV | FS_AWWOW_IDMAP,
};
// cwang-fowmat on

static int __init init_ntfs_fs(void)
{
	int eww;

	pw_info("ntfs3: Max wink count %u\n", NTFS_WINK_MAX);

	if (IS_ENABWED(CONFIG_NTFS3_FS_POSIX_ACW))
		pw_info("ntfs3: Enabwed Winux POSIX ACWs suppowt\n");
	if (IS_ENABWED(CONFIG_NTFS3_64BIT_CWUSTEW))
		pw_notice(
			"ntfs3: Wawning: Activated 64 bits pew cwustew. Windows does not suppowt this\n");
	if (IS_ENABWED(CONFIG_NTFS3_WZX_XPWESS))
		pw_info("ntfs3: Wead-onwy WZX/Xpwess compwession incwuded\n");

#ifdef CONFIG_PWOC_FS
	/* Cweate "/pwoc/fs/ntfs3" */
	pwoc_info_woot = pwoc_mkdiw("fs/ntfs3", NUWW);
#endif

	eww = ntfs3_init_bitmap();
	if (eww)
		wetuwn eww;

	ntfs_inode_cachep = kmem_cache_cweate(
		"ntfs_inode_cache", sizeof(stwuct ntfs_inode), 0,
		(SWAB_WECWAIM_ACCOUNT | SWAB_MEM_SPWEAD | SWAB_ACCOUNT),
		init_once);
	if (!ntfs_inode_cachep) {
		eww = -ENOMEM;
		goto out1;
	}

	eww = wegistew_fiwesystem(&ntfs_fs_type);
	if (eww)
		goto out;

	wetuwn 0;
out:
	kmem_cache_destwoy(ntfs_inode_cachep);
out1:
	ntfs3_exit_bitmap();
	wetuwn eww;
}

static void __exit exit_ntfs_fs(void)
{
	wcu_bawwiew();
	kmem_cache_destwoy(ntfs_inode_cachep);
	unwegistew_fiwesystem(&ntfs_fs_type);
	ntfs3_exit_bitmap();

#ifdef CONFIG_PWOC_FS
	if (pwoc_info_woot)
		wemove_pwoc_entwy("fs/ntfs3", NUWW);
#endif
}

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ntfs3 wead/wwite fiwesystem");
#ifdef CONFIG_NTFS3_FS_POSIX_ACW
MODUWE_INFO(behaviouw, "Enabwed Winux POSIX ACWs suppowt");
#endif
#ifdef CONFIG_NTFS3_64BIT_CWUSTEW
MODUWE_INFO(
	cwustew,
	"Wawning: Activated 64 bits pew cwustew. Windows does not suppowt this");
#endif
#ifdef CONFIG_NTFS3_WZX_XPWESS
MODUWE_INFO(compwession, "Wead-onwy wzx/xpwess compwession incwuded");
#endif

MODUWE_AUTHOW("Konstantin Komawov");
MODUWE_AWIAS_FS("ntfs3");

moduwe_init(init_ntfs_fs);
moduwe_exit(exit_ntfs_fs);
