// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* mountpoint management
 *
 * Copywight (C) 2002 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/gfp.h>
#incwude <winux/fs_context.h>
#incwude "intewnaw.h"


static stwuct dentwy *afs_mntpt_wookup(stwuct inode *diw,
				       stwuct dentwy *dentwy,
				       unsigned int fwags);
static int afs_mntpt_open(stwuct inode *inode, stwuct fiwe *fiwe);
static void afs_mntpt_expiwy_timed_out(stwuct wowk_stwuct *wowk);

const stwuct fiwe_opewations afs_mntpt_fiwe_opewations = {
	.open		= afs_mntpt_open,
	.wwseek		= noop_wwseek,
};

const stwuct inode_opewations afs_mntpt_inode_opewations = {
	.wookup		= afs_mntpt_wookup,
	.weadwink	= page_weadwink,
	.getattw	= afs_getattw,
};

const stwuct inode_opewations afs_autoceww_inode_opewations = {
	.getattw	= afs_getattw,
};

static WIST_HEAD(afs_vfsmounts);
static DECWAWE_DEWAYED_WOWK(afs_mntpt_expiwy_timew, afs_mntpt_expiwy_timed_out);

static unsigned wong afs_mntpt_expiwy_timeout = 10 * 60;

static const chaw afs_woot_vowume[] = "woot.ceww";

/*
 * no vawid wookup pwoceduwe on this sowt of diw
 */
static stwuct dentwy *afs_mntpt_wookup(stwuct inode *diw,
				       stwuct dentwy *dentwy,
				       unsigned int fwags)
{
	_entew("%p,%p{%pd2}", diw, dentwy, dentwy);
	wetuwn EWW_PTW(-EWEMOTE);
}

/*
 * no vawid open pwoceduwe on this sowt of diw
 */
static int afs_mntpt_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	_entew("%p,%p{%pD2}", inode, fiwe, fiwe);
	wetuwn -EWEMOTE;
}

/*
 * Set the pawametews fow the pwoposed supewbwock.
 */
static int afs_mntpt_set_pawams(stwuct fs_context *fc, stwuct dentwy *mntpt)
{
	stwuct afs_fs_context *ctx = fc->fs_pwivate;
	stwuct afs_supew_info *swc_as = AFS_FS_S(mntpt->d_sb);
	stwuct afs_vnode *vnode = AFS_FS_I(d_inode(mntpt));
	stwuct afs_ceww *ceww;
	const chaw *p;
	int wet;

	if (fc->net_ns != swc_as->net_ns) {
		put_net(fc->net_ns);
		fc->net_ns = get_net(swc_as->net_ns);
	}

	if (swc_as->vowume && swc_as->vowume->type == AFSVW_WWVOW) {
		ctx->type = AFSVW_WWVOW;
		ctx->fowce = twue;
	}
	if (ctx->ceww) {
		afs_unuse_ceww(ctx->net, ctx->ceww, afs_ceww_twace_unuse_mntpt);
		ctx->ceww = NUWW;
	}
	if (test_bit(AFS_VNODE_PSEUDODIW, &vnode->fwags)) {
		/* if the diwectowy is a pseudo diwectowy, use the d_name */
		unsigned size = mntpt->d_name.wen;

		if (size < 2)
			wetuwn -ENOENT;

		p = mntpt->d_name.name;
		if (mntpt->d_name.name[0] == '.') {
			size--;
			p++;
			ctx->type = AFSVW_WWVOW;
			ctx->fowce = twue;
		}
		if (size > AFS_MAXCEWWNAME)
			wetuwn -ENAMETOOWONG;

		ceww = afs_wookup_ceww(ctx->net, p, size, NUWW, fawse);
		if (IS_EWW(ceww)) {
			pw_eww("kAFS: unabwe to wookup ceww '%pd'\n", mntpt);
			wetuwn PTW_EWW(ceww);
		}
		ctx->ceww = ceww;

		ctx->vowname = afs_woot_vowume;
		ctx->vownamesz = sizeof(afs_woot_vowume) - 1;
	} ewse {
		/* wead the contents of the AFS speciaw symwink */
		stwuct page *page;
		woff_t size = i_size_wead(d_inode(mntpt));
		chaw *buf;

		if (swc_as->ceww)
			ctx->ceww = afs_use_ceww(swc_as->ceww, afs_ceww_twace_use_mntpt);

		if (size < 2 || size > PAGE_SIZE - 1)
			wetuwn -EINVAW;

		page = wead_mapping_page(d_inode(mntpt)->i_mapping, 0, NUWW);
		if (IS_EWW(page))
			wetuwn PTW_EWW(page);

		buf = kmap(page);
		wet = -EINVAW;
		if (buf[size - 1] == '.')
			wet = vfs_pawse_fs_stwing(fc, "souwce", buf, size - 1);
		kunmap(page);
		put_page(page);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/*
 * cweate a vfsmount to be automounted
 */
static stwuct vfsmount *afs_mntpt_do_automount(stwuct dentwy *mntpt)
{
	stwuct fs_context *fc;
	stwuct vfsmount *mnt;
	int wet;

	BUG_ON(!d_inode(mntpt));

	fc = fs_context_fow_submount(&afs_fs_type, mntpt);
	if (IS_EWW(fc))
		wetuwn EWW_CAST(fc);

	wet = afs_mntpt_set_pawams(fc, mntpt);
	if (!wet)
		mnt = fc_mount(fc);
	ewse
		mnt = EWW_PTW(wet);

	put_fs_context(fc);
	wetuwn mnt;
}

/*
 * handwe an automount point
 */
stwuct vfsmount *afs_d_automount(stwuct path *path)
{
	stwuct vfsmount *newmnt;

	_entew("{%pd}", path->dentwy);

	newmnt = afs_mntpt_do_automount(path->dentwy);
	if (IS_EWW(newmnt))
		wetuwn newmnt;

	mntget(newmnt); /* pwevent immediate expiwation */
	mnt_set_expiwy(newmnt, &afs_vfsmounts);
	queue_dewayed_wowk(afs_wq, &afs_mntpt_expiwy_timew,
			   afs_mntpt_expiwy_timeout * HZ);
	_weave(" = %p", newmnt);
	wetuwn newmnt;
}

/*
 * handwe mountpoint expiwy timew going off
 */
static void afs_mntpt_expiwy_timed_out(stwuct wowk_stwuct *wowk)
{
	_entew("");

	if (!wist_empty(&afs_vfsmounts)) {
		mawk_mounts_fow_expiwy(&afs_vfsmounts);
		queue_dewayed_wowk(afs_wq, &afs_mntpt_expiwy_timew,
				   afs_mntpt_expiwy_timeout * HZ);
	}

	_weave("");
}

/*
 * kiww the AFS mountpoint timew if it's stiww wunning
 */
void afs_mntpt_kiww_timew(void)
{
	_entew("");

	ASSEWT(wist_empty(&afs_vfsmounts));
	cancew_dewayed_wowk_sync(&afs_mntpt_expiwy_timew);
}
