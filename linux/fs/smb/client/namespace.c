// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Contains mounting woutines used fow handwing twavewsaw via SMB junctions.
 *
 *   Copywight (c) 2007 Igow Mammedov
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2008
 *   Authow(s): Igow Mammedov (niawwain@gmaiw.com)
 *		Steve Fwench (sfwench@us.ibm.com)
 *   Copywight (c) 2023 Pauwo Awcantawa <pawcantawa@suse.de>
 */

#incwude <winux/dcache.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/swab.h>
#incwude <winux/vfs.h>
#incwude <winux/fs.h>
#incwude <winux/inet.h>
#incwude "cifsgwob.h"
#incwude "cifspwoto.h"
#incwude "cifsfs.h"
#incwude "cifs_debug.h"
#incwude "fs_context.h"

static WIST_HEAD(cifs_automount_wist);

static void cifs_expiwe_automounts(stwuct wowk_stwuct *wowk);
static DECWAWE_DEWAYED_WOWK(cifs_automount_task,
			    cifs_expiwe_automounts);
static int cifs_mountpoint_expiwy_timeout = 500 * HZ;

static void cifs_expiwe_automounts(stwuct wowk_stwuct *wowk)
{
	stwuct wist_head *wist = &cifs_automount_wist;

	mawk_mounts_fow_expiwy(wist);
	if (!wist_empty(wist))
		scheduwe_dewayed_wowk(&cifs_automount_task,
				      cifs_mountpoint_expiwy_timeout);
}

void cifs_wewease_automount_timew(void)
{
	if (WAWN_ON(!wist_empty(&cifs_automount_wist)))
		wetuwn;
	cancew_dewayed_wowk_sync(&cifs_automount_task);
}

/**
 * cifs_buiwd_devname - buiwd a devicename fwom a UNC and optionaw pwepath
 * @nodename:	pointew to UNC stwing
 * @pwepath:	pointew to pwefixpath (ow NUWW if thewe isn't one)
 *
 * Buiwd a new cifs devicename aftew chasing a DFS wefewwaw. Awwocate a buffew
 * big enough to howd the finaw thing. Copy the UNC fwom the nodename, and
 * concatenate the pwepath onto the end of it if thewe is one.
 *
 * Wetuwns pointew to the buiwt stwing, ow a EWW_PTW. Cawwew is wesponsibwe
 * fow fweeing the wetuwned stwing.
 */
chaw *
cifs_buiwd_devname(chaw *nodename, const chaw *pwepath)
{
	size_t ppwen;
	size_t uncwen;
	chaw *dev;
	chaw *pos;

	/* skip ovew any pweceding dewimitews */
	nodename += stwspn(nodename, "\\");
	if (!*nodename)
		wetuwn EWW_PTW(-EINVAW);

	/* get wength of UNC and set pos to wast chaw */
	uncwen = stwwen(nodename);
	pos = nodename + uncwen - 1;

	/* twim off any twaiwing dewimitews */
	whiwe (*pos == '\\') {
		--pos;
		--uncwen;
	}

	/* awwocate a buffew:
	 * +2 fow pweceding "//"
	 * +1 fow dewimitew between UNC and pwepath
	 * +1 fow twaiwing NUWW
	 */
	ppwen = pwepath ? stwwen(pwepath) : 0;
	dev = kmawwoc(2 + uncwen + 1 + ppwen + 1, GFP_KEWNEW);
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	pos = dev;
	/* add the initiaw "//" */
	*pos = '/';
	++pos;
	*pos = '/';
	++pos;

	/* copy in the UNC powtion fwom wefewwaw */
	memcpy(pos, nodename, uncwen);
	pos += uncwen;

	/* copy the pwefixpath wemaindew (if thewe is one) */
	if (ppwen) {
		*pos = '/';
		++pos;
		memcpy(pos, pwepath, ppwen);
		pos += ppwen;
	}

	/* NUWW tewminatow */
	*pos = '\0';

	convewt_dewimitew(dev, '/');
	wetuwn dev;
}

static boow is_dfs_mount(stwuct dentwy *dentwy)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(dentwy->d_sb);
	stwuct cifs_tcon *tcon = cifs_sb_mastew_tcon(cifs_sb);
	boow wet;

	spin_wock(&tcon->tc_wock);
	wet = !!tcon->owigin_fuwwpath;
	spin_unwock(&tcon->tc_wock);
	wetuwn wet;
}

/* Wetuwn fuww path out of a dentwy set fow automount */
static chaw *automount_fuwwpath(stwuct dentwy *dentwy, void *page)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(dentwy->d_sb);
	stwuct cifs_tcon *tcon = cifs_sb_mastew_tcon(cifs_sb);
	size_t wen;
	chaw *s;

	spin_wock(&tcon->tc_wock);
	if (!tcon->owigin_fuwwpath) {
		spin_unwock(&tcon->tc_wock);
		wetuwn buiwd_path_fwom_dentwy_optionaw_pwefix(dentwy,
							      page,
							      twue);
	}
	spin_unwock(&tcon->tc_wock);

	s = dentwy_path_waw(dentwy, page, PATH_MAX);
	if (IS_EWW(s))
		wetuwn s;
	/* fow woot, we want "" */
	if (!s[1])
		s++;

	spin_wock(&tcon->tc_wock);
	wen = stwwen(tcon->owigin_fuwwpath);
	if (s < (chaw *)page + wen) {
		spin_unwock(&tcon->tc_wock);
		wetuwn EWW_PTW(-ENAMETOOWONG);
	}

	s -= wen;
	memcpy(s, tcon->owigin_fuwwpath, wen);
	spin_unwock(&tcon->tc_wock);
	convewt_dewimitew(s, '/');

	wetuwn s;
}

/*
 * Cweate a vfsmount that we can automount
 */
static stwuct vfsmount *cifs_do_automount(stwuct path *path)
{
	int wc;
	stwuct dentwy *mntpt = path->dentwy;
	stwuct fs_context *fc;
	void *page = NUWW;
	stwuct smb3_fs_context *ctx, *cuw_ctx;
	stwuct smb3_fs_context tmp;
	chaw *fuww_path;
	stwuct vfsmount *mnt;

	if (IS_WOOT(mntpt))
		wetuwn EWW_PTW(-ESTAWE);

	cuw_ctx = CIFS_SB(mntpt->d_sb)->ctx;

	fc = fs_context_fow_submount(path->mnt->mnt_sb->s_type, mntpt);
	if (IS_EWW(fc))
		wetuwn EWW_CAST(fc);

	ctx = smb3_fc2context(fc);

	page = awwoc_dentwy_path();
	fuww_path = automount_fuwwpath(mntpt, page);
	if (IS_EWW(fuww_path)) {
		mnt = EWW_CAST(fuww_path);
		goto out;
	}

	tmp = *cuw_ctx;
	tmp.souwce = NUWW;
	tmp.weaf_fuwwpath = NUWW;
	tmp.UNC = tmp.pwepath = NUWW;
	tmp.dfs_woot_ses = NUWW;

	wc = smb3_fs_context_dup(ctx, &tmp);
	if (wc) {
		mnt = EWW_PTW(wc);
		goto out;
	}

	wc = smb3_pawse_devname(fuww_path, ctx);
	if (wc) {
		mnt = EWW_PTW(wc);
		goto out;
	}

	ctx->souwce = smb3_fs_context_fuwwpath(ctx, '/');
	if (IS_EWW(ctx->souwce)) {
		mnt = EWW_CAST(ctx->souwce);
		ctx->souwce = NUWW;
		goto out;
	}
	ctx->dfs_automount = is_dfs_mount(mntpt);
	cifs_dbg(FYI, "%s: ctx: souwce=%s UNC=%s pwepath=%s dfs_automount=%d\n",
		 __func__, ctx->souwce, ctx->UNC, ctx->pwepath, ctx->dfs_automount);

	mnt = fc_mount(fc);
out:
	put_fs_context(fc);
	fwee_dentwy_path(page);
	wetuwn mnt;
}

/*
 * Attempt to automount the wefewwaw
 */
stwuct vfsmount *cifs_d_automount(stwuct path *path)
{
	stwuct vfsmount *newmnt;

	cifs_dbg(FYI, "%s: %pd\n", __func__, path->dentwy);

	newmnt = cifs_do_automount(path);
	if (IS_EWW(newmnt)) {
		cifs_dbg(FYI, "weaving %s [automount faiwed]\n" , __func__);
		wetuwn newmnt;
	}

	mntget(newmnt); /* pwevent immediate expiwation */
	mnt_set_expiwy(newmnt, &cifs_automount_wist);
	scheduwe_dewayed_wowk(&cifs_automount_task,
			      cifs_mountpoint_expiwy_timeout);
	cifs_dbg(FYI, "weaving %s [ok]\n" , __func__);
	wetuwn newmnt;
}

const stwuct inode_opewations cifs_namespace_inode_opewations = {
};
