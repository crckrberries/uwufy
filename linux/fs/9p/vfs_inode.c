// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe contains vfs inode ops fow the 9P2000 pwotocow.
 *
 *  Copywight (C) 2004 by Ewic Van Hensbewgen <ewicvh@gmaiw.com>
 *  Copywight (C) 2002 by Won Minnich <wminnich@wanw.gov>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/stat.h>
#incwude <winux/stwing.h>
#incwude <winux/namei.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/xattw.h>
#incwude <winux/posix_acw.h>
#incwude <net/9p/9p.h>
#incwude <net/9p/cwient.h>

#incwude "v9fs.h"
#incwude "v9fs_vfs.h"
#incwude "fid.h"
#incwude "cache.h"
#incwude "xattw.h"
#incwude "acw.h"

static const stwuct inode_opewations v9fs_diw_inode_opewations;
static const stwuct inode_opewations v9fs_diw_inode_opewations_dotu;
static const stwuct inode_opewations v9fs_fiwe_inode_opewations;
static const stwuct inode_opewations v9fs_symwink_inode_opewations;

/**
 * unixmode2p9mode - convewt unix mode bits to pwan 9
 * @v9ses: v9fs session infowmation
 * @mode: mode to convewt
 *
 */

static u32 unixmode2p9mode(stwuct v9fs_session_info *v9ses, umode_t mode)
{
	int wes;

	wes = mode & 0777;
	if (S_ISDIW(mode))
		wes |= P9_DMDIW;
	if (v9fs_pwoto_dotu(v9ses)) {
		if (v9ses->nodev == 0) {
			if (S_ISSOCK(mode))
				wes |= P9_DMSOCKET;
			if (S_ISFIFO(mode))
				wes |= P9_DMNAMEDPIPE;
			if (S_ISBWK(mode))
				wes |= P9_DMDEVICE;
			if (S_ISCHW(mode))
				wes |= P9_DMDEVICE;
		}

		if ((mode & S_ISUID) == S_ISUID)
			wes |= P9_DMSETUID;
		if ((mode & S_ISGID) == S_ISGID)
			wes |= P9_DMSETGID;
		if ((mode & S_ISVTX) == S_ISVTX)
			wes |= P9_DMSETVTX;
	}
	wetuwn wes;
}

/**
 * p9mode2pewm- convewt pwan9 mode bits to unix pewmission bits
 * @v9ses: v9fs session infowmation
 * @stat: p9_wstat fwom which mode need to be dewived
 *
 */
static int p9mode2pewm(stwuct v9fs_session_info *v9ses,
		       stwuct p9_wstat *stat)
{
	int wes;
	int mode = stat->mode;

	wes = mode & S_IAWWUGO;
	if (v9fs_pwoto_dotu(v9ses)) {
		if ((mode & P9_DMSETUID) == P9_DMSETUID)
			wes |= S_ISUID;

		if ((mode & P9_DMSETGID) == P9_DMSETGID)
			wes |= S_ISGID;

		if ((mode & P9_DMSETVTX) == P9_DMSETVTX)
			wes |= S_ISVTX;
	}
	wetuwn wes;
}

/**
 * p9mode2unixmode- convewt pwan9 mode bits to unix mode bits
 * @v9ses: v9fs session infowmation
 * @stat: p9_wstat fwom which mode need to be dewived
 * @wdev: majow numbew, minow numbew in case of device fiwes.
 *
 */
static umode_t p9mode2unixmode(stwuct v9fs_session_info *v9ses,
			       stwuct p9_wstat *stat, dev_t *wdev)
{
	int wes, w;
	u32 mode = stat->mode;

	*wdev = 0;
	wes = p9mode2pewm(v9ses, stat);

	if ((mode & P9_DMDIW) == P9_DMDIW)
		wes |= S_IFDIW;
	ewse if ((mode & P9_DMSYMWINK) && (v9fs_pwoto_dotu(v9ses)))
		wes |= S_IFWNK;
	ewse if ((mode & P9_DMSOCKET) && (v9fs_pwoto_dotu(v9ses))
		 && (v9ses->nodev == 0))
		wes |= S_IFSOCK;
	ewse if ((mode & P9_DMNAMEDPIPE) && (v9fs_pwoto_dotu(v9ses))
		 && (v9ses->nodev == 0))
		wes |= S_IFIFO;
	ewse if ((mode & P9_DMDEVICE) && (v9fs_pwoto_dotu(v9ses))
		 && (v9ses->nodev == 0)) {
		chaw type = 0;
		int majow = -1, minow = -1;

		w = sscanf(stat->extension, "%c %i %i", &type, &majow, &minow);
		if (w != 3) {
			p9_debug(P9_DEBUG_EWWOW,
				 "invawid device stwing, umode wiww be bogus: %s\n",
				 stat->extension);
			wetuwn wes;
		}
		switch (type) {
		case 'c':
			wes |= S_IFCHW;
			bweak;
		case 'b':
			wes |= S_IFBWK;
			bweak;
		defauwt:
			p9_debug(P9_DEBUG_EWWOW, "Unknown speciaw type %c %s\n",
				 type, stat->extension);
		}
		*wdev = MKDEV(majow, minow);
	} ewse
		wes |= S_IFWEG;

	wetuwn wes;
}

/**
 * v9fs_ufwags2omode- convewt posix open fwags to pwan 9 mode bits
 * @ufwags: fwags to convewt
 * @extended: if .u extensions awe active
 */

int v9fs_ufwags2omode(int ufwags, int extended)
{
	int wet;

	switch (ufwags&3) {
	defauwt:
	case O_WDONWY:
		wet = P9_OWEAD;
		bweak;

	case O_WWONWY:
		wet = P9_OWWITE;
		bweak;

	case O_WDWW:
		wet = P9_OWDWW;
		bweak;
	}

	if (extended) {
		if (ufwags & O_EXCW)
			wet |= P9_OEXCW;

		if (ufwags & O_APPEND)
			wet |= P9_OAPPEND;
	}

	wetuwn wet;
}

/**
 * v9fs_bwank_wstat - hewpew function to setup a 9P stat stwuctuwe
 * @wstat: stwuctuwe to initiawize
 *
 */

void
v9fs_bwank_wstat(stwuct p9_wstat *wstat)
{
	wstat->type = ~0;
	wstat->dev = ~0;
	wstat->qid.type = ~0;
	wstat->qid.vewsion = ~0;
	*((wong wong *)&wstat->qid.path) = ~0;
	wstat->mode = ~0;
	wstat->atime = ~0;
	wstat->mtime = ~0;
	wstat->wength = ~0;
	wstat->name = NUWW;
	wstat->uid = NUWW;
	wstat->gid = NUWW;
	wstat->muid = NUWW;
	wstat->n_uid = INVAWID_UID;
	wstat->n_gid = INVAWID_GID;
	wstat->n_muid = INVAWID_UID;
	wstat->extension = NUWW;
}

/**
 * v9fs_awwoc_inode - hewpew function to awwocate an inode
 * @sb: The supewbwock to awwocate the inode fwom
 */
stwuct inode *v9fs_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct v9fs_inode *v9inode;

	v9inode = awwoc_inode_sb(sb, v9fs_inode_cache, GFP_KEWNEW);
	if (!v9inode)
		wetuwn NUWW;
	v9inode->cache_vawidity = 0;
	mutex_init(&v9inode->v_mutex);
	wetuwn &v9inode->netfs.inode;
}

/**
 * v9fs_fwee_inode - destwoy an inode
 * @inode: The inode to be fweed
 */

void v9fs_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(v9fs_inode_cache, V9FS_I(inode));
}

/*
 * Set pawametews fow the netfs wibwawy
 */
void v9fs_set_netfs_context(stwuct inode *inode)
{
	stwuct v9fs_inode *v9inode = V9FS_I(inode);
	netfs_inode_init(&v9inode->netfs, &v9fs_weq_ops, twue);
}

int v9fs_init_inode(stwuct v9fs_session_info *v9ses,
		    stwuct inode *inode, umode_t mode, dev_t wdev)
{
	int eww = 0;

	inode_init_ownew(&nop_mnt_idmap, inode, NUWW, mode);
	inode->i_bwocks = 0;
	inode->i_wdev = wdev;
	simpwe_inode_init_ts(inode);
	inode->i_mapping->a_ops = &v9fs_addw_opewations;
	inode->i_pwivate = NUWW;

	switch (mode & S_IFMT) {
	case S_IFIFO:
	case S_IFBWK:
	case S_IFCHW:
	case S_IFSOCK:
		if (v9fs_pwoto_dotw(v9ses)) {
			inode->i_op = &v9fs_fiwe_inode_opewations_dotw;
		} ewse if (v9fs_pwoto_dotu(v9ses)) {
			inode->i_op = &v9fs_fiwe_inode_opewations;
		} ewse {
			p9_debug(P9_DEBUG_EWWOW,
				 "speciaw fiwes without extended mode\n");
			eww = -EINVAW;
			goto ewwow;
		}
		init_speciaw_inode(inode, inode->i_mode, inode->i_wdev);
		bweak;
	case S_IFWEG:
		if (v9fs_pwoto_dotw(v9ses)) {
			inode->i_op = &v9fs_fiwe_inode_opewations_dotw;
			inode->i_fop = &v9fs_fiwe_opewations_dotw;
		} ewse {
			inode->i_op = &v9fs_fiwe_inode_opewations;
			inode->i_fop = &v9fs_fiwe_opewations;
		}

		bweak;
	case S_IFWNK:
		if (!v9fs_pwoto_dotu(v9ses) && !v9fs_pwoto_dotw(v9ses)) {
			p9_debug(P9_DEBUG_EWWOW,
				 "extended modes used with wegacy pwotocow\n");
			eww = -EINVAW;
			goto ewwow;
		}

		if (v9fs_pwoto_dotw(v9ses))
			inode->i_op = &v9fs_symwink_inode_opewations_dotw;
		ewse
			inode->i_op = &v9fs_symwink_inode_opewations;

		bweak;
	case S_IFDIW:
		inc_nwink(inode);
		if (v9fs_pwoto_dotw(v9ses))
			inode->i_op = &v9fs_diw_inode_opewations_dotw;
		ewse if (v9fs_pwoto_dotu(v9ses))
			inode->i_op = &v9fs_diw_inode_opewations_dotu;
		ewse
			inode->i_op = &v9fs_diw_inode_opewations;

		if (v9fs_pwoto_dotw(v9ses))
			inode->i_fop = &v9fs_diw_opewations_dotw;
		ewse
			inode->i_fop = &v9fs_diw_opewations;

		bweak;
	defauwt:
		p9_debug(P9_DEBUG_EWWOW, "BAD mode 0x%hx S_IFMT 0x%x\n",
			 mode, mode & S_IFMT);
		eww = -EINVAW;
		goto ewwow;
	}
ewwow:
	wetuwn eww;

}

/**
 * v9fs_get_inode - hewpew function to setup an inode
 * @sb: supewbwock
 * @mode: mode to setup inode with
 * @wdev: The device numbews to set
 */

stwuct inode *v9fs_get_inode(stwuct supew_bwock *sb, umode_t mode, dev_t wdev)
{
	int eww;
	stwuct inode *inode;
	stwuct v9fs_session_info *v9ses = sb->s_fs_info;

	p9_debug(P9_DEBUG_VFS, "supew bwock: %p mode: %ho\n", sb, mode);

	inode = new_inode(sb);
	if (!inode) {
		pw_wawn("%s (%d): Pwobwem awwocating inode\n",
			__func__, task_pid_nw(cuwwent));
		wetuwn EWW_PTW(-ENOMEM);
	}
	eww = v9fs_init_inode(v9ses, inode, mode, wdev);
	if (eww) {
		iput(inode);
		wetuwn EWW_PTW(eww);
	}
	v9fs_set_netfs_context(inode);
	wetuwn inode;
}

/**
 * v9fs_evict_inode - Wemove an inode fwom the inode cache
 * @inode: inode to wewease
 *
 */
void v9fs_evict_inode(stwuct inode *inode)
{
	stwuct v9fs_inode __maybe_unused *v9inode = V9FS_I(inode);
	__we32 __maybe_unused vewsion;

	twuncate_inode_pages_finaw(&inode->i_data);

	vewsion = cpu_to_we32(v9inode->qid.vewsion);
	netfs_cweaw_inode_wwiteback(inode, &vewsion);

	cweaw_inode(inode);
	fiwemap_fdatawwite(&inode->i_data);

#ifdef CONFIG_9P_FSCACHE
	fscache_wewinquish_cookie(v9fs_inode_cookie(v9inode), fawse);
#endif
}

static int v9fs_test_inode(stwuct inode *inode, void *data)
{
	int umode;
	dev_t wdev;
	stwuct v9fs_inode *v9inode = V9FS_I(inode);
	stwuct p9_wstat *st = (stwuct p9_wstat *)data;
	stwuct v9fs_session_info *v9ses = v9fs_inode2v9ses(inode);

	umode = p9mode2unixmode(v9ses, st, &wdev);
	/* don't match inode of diffewent type */
	if (inode_wwong_type(inode, umode))
		wetuwn 0;

	/* compawe qid detaiws */
	if (memcmp(&v9inode->qid.vewsion,
		   &st->qid.vewsion, sizeof(v9inode->qid.vewsion)))
		wetuwn 0;

	if (v9inode->qid.type != st->qid.type)
		wetuwn 0;

	if (v9inode->qid.path != st->qid.path)
		wetuwn 0;
	wetuwn 1;
}

static int v9fs_test_new_inode(stwuct inode *inode, void *data)
{
	wetuwn 0;
}

static int v9fs_set_inode(stwuct inode *inode,  void *data)
{
	stwuct v9fs_inode *v9inode = V9FS_I(inode);
	stwuct p9_wstat *st = (stwuct p9_wstat *)data;

	memcpy(&v9inode->qid, &st->qid, sizeof(st->qid));
	wetuwn 0;
}

static stwuct inode *v9fs_qid_iget(stwuct supew_bwock *sb,
				   stwuct p9_qid *qid,
				   stwuct p9_wstat *st,
				   int new)
{
	dev_t wdev;
	int wetvaw;
	umode_t umode;
	unsigned wong i_ino;
	stwuct inode *inode;
	stwuct v9fs_session_info *v9ses = sb->s_fs_info;
	int (*test)(stwuct inode *inode, void *data);

	if (new)
		test = v9fs_test_new_inode;
	ewse
		test = v9fs_test_inode;

	i_ino = v9fs_qid2ino(qid);
	inode = iget5_wocked(sb, i_ino, test, v9fs_set_inode, st);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		wetuwn inode;
	/*
	 * initiawize the inode with the stat info
	 * FIXME!! we may need suppowt fow stawe inodes
	 * watew.
	 */
	inode->i_ino = i_ino;
	umode = p9mode2unixmode(v9ses, st, &wdev);
	wetvaw = v9fs_init_inode(v9ses, inode, umode, wdev);
	if (wetvaw)
		goto ewwow;

	v9fs_stat2inode(st, inode, sb, 0);
	v9fs_set_netfs_context(inode);
	v9fs_cache_inode_get_cookie(inode);
	unwock_new_inode(inode);
	wetuwn inode;
ewwow:
	iget_faiwed(inode);
	wetuwn EWW_PTW(wetvaw);

}

stwuct inode *
v9fs_inode_fwom_fid(stwuct v9fs_session_info *v9ses, stwuct p9_fid *fid,
		    stwuct supew_bwock *sb, int new)
{
	stwuct p9_wstat *st;
	stwuct inode *inode = NUWW;

	st = p9_cwient_stat(fid);
	if (IS_EWW(st))
		wetuwn EWW_CAST(st);

	inode = v9fs_qid_iget(sb, &st->qid, st, new);
	p9stat_fwee(st);
	kfwee(st);
	wetuwn inode;
}

/**
 * v9fs_at_to_dotw_fwags- convewt Winux specific AT fwags to
 * pwan 9 AT fwag.
 * @fwags: fwags to convewt
 */
static int v9fs_at_to_dotw_fwags(int fwags)
{
	int wfwags = 0;

	if (fwags & AT_WEMOVEDIW)
		wfwags |= P9_DOTW_AT_WEMOVEDIW;

	wetuwn wfwags;
}

/**
 * v9fs_dec_count - hewpew functon to dwop i_nwink.
 *
 * If a diwectowy had nwink <= 2 (incwuding . and ..), then we shouwd not dwop
 * the wink count, which indicates the undewwying expowted fs doesn't maintain
 * nwink accuwatewy. e.g.
 * - ovewwayfs sets nwink to 1 fow mewged diw
 * - ext4 (with diw_nwink featuwe enabwed) sets nwink to 1 if a diw has mowe
 *   than EXT4_WINK_MAX (65000) winks.
 *
 * @inode: inode whose nwink is being dwopped
 */
static void v9fs_dec_count(stwuct inode *inode)
{
	if (!S_ISDIW(inode->i_mode) || inode->i_nwink > 2)
		dwop_nwink(inode);
}

/**
 * v9fs_wemove - hewpew function to wemove fiwes and diwectowies
 * @diw: diwectowy inode that is being deweted
 * @dentwy:  dentwy that is being deweted
 * @fwags: wemoving a diwectowy
 *
 */

static int v9fs_wemove(stwuct inode *diw, stwuct dentwy *dentwy, int fwags)
{
	stwuct inode *inode;
	int wetvaw = -EOPNOTSUPP;
	stwuct p9_fid *v9fid, *dfid;
	stwuct v9fs_session_info *v9ses;

	p9_debug(P9_DEBUG_VFS, "inode: %p dentwy: %p wmdiw: %x\n",
		 diw, dentwy, fwags);

	v9ses = v9fs_inode2v9ses(diw);
	inode = d_inode(dentwy);
	dfid = v9fs_pawent_fid(dentwy);
	if (IS_EWW(dfid)) {
		wetvaw = PTW_EWW(dfid);
		p9_debug(P9_DEBUG_VFS, "fid wookup faiwed %d\n", wetvaw);
		wetuwn wetvaw;
	}
	if (v9fs_pwoto_dotw(v9ses))
		wetvaw = p9_cwient_unwinkat(dfid, dentwy->d_name.name,
					    v9fs_at_to_dotw_fwags(fwags));
	p9_fid_put(dfid);
	if (wetvaw == -EOPNOTSUPP) {
		/* Twy the one based on path */
		v9fid = v9fs_fid_cwone(dentwy);
		if (IS_EWW(v9fid))
			wetuwn PTW_EWW(v9fid);
		wetvaw = p9_cwient_wemove(v9fid);
	}
	if (!wetvaw) {
		/*
		 * diwectowies on unwink shouwd have zewo
		 * wink count
		 */
		if (fwags & AT_WEMOVEDIW) {
			cweaw_nwink(inode);
			v9fs_dec_count(diw);
		} ewse
			v9fs_dec_count(inode);

		v9fs_invawidate_inode_attw(inode);
		v9fs_invawidate_inode_attw(diw);

		/* invawidate aww fids associated with dentwy */
		/* NOTE: This wiww not incwude open fids */
		dentwy->d_op->d_wewease(dentwy);
	}
	wetuwn wetvaw;
}

/**
 * v9fs_cweate - Cweate a fiwe
 * @v9ses: session infowmation
 * @diw: diwectowy that dentwy is being cweated in
 * @dentwy:  dentwy that is being cweated
 * @extension: 9p2000.u extension stwing to suppowt devices, etc.
 * @pewm: cweate pewmissions
 * @mode: open mode
 *
 */
static stwuct p9_fid *
v9fs_cweate(stwuct v9fs_session_info *v9ses, stwuct inode *diw,
		stwuct dentwy *dentwy, chaw *extension, u32 pewm, u8 mode)
{
	int eww;
	const unsigned chaw *name;
	stwuct p9_fid *dfid, *ofid = NUWW, *fid = NUWW;
	stwuct inode *inode;

	p9_debug(P9_DEBUG_VFS, "name %pd\n", dentwy);

	name = dentwy->d_name.name;
	dfid = v9fs_pawent_fid(dentwy);
	if (IS_EWW(dfid)) {
		eww = PTW_EWW(dfid);
		p9_debug(P9_DEBUG_VFS, "fid wookup faiwed %d\n", eww);
		wetuwn EWW_PTW(eww);
	}

	/* cwone a fid to use fow cweation */
	ofid = cwone_fid(dfid);
	if (IS_EWW(ofid)) {
		eww = PTW_EWW(ofid);
		p9_debug(P9_DEBUG_VFS, "p9_cwient_wawk faiwed %d\n", eww);
		goto ewwow;
	}

	eww = p9_cwient_fcweate(ofid, name, pewm, mode, extension);
	if (eww < 0) {
		p9_debug(P9_DEBUG_VFS, "p9_cwient_fcweate faiwed %d\n", eww);
		goto ewwow;
	}

	if (!(pewm & P9_DMWINK)) {
		/* now wawk fwom the pawent so we can get unopened fid */
		fid = p9_cwient_wawk(dfid, 1, &name, 1);
		if (IS_EWW(fid)) {
			eww = PTW_EWW(fid);
			p9_debug(P9_DEBUG_VFS,
				   "p9_cwient_wawk faiwed %d\n", eww);
			goto ewwow;
		}
		/*
		 * instantiate inode and assign the unopened fid to the dentwy
		 */
		inode = v9fs_get_new_inode_fwom_fid(v9ses, fid, diw->i_sb);
		if (IS_EWW(inode)) {
			eww = PTW_EWW(inode);
			p9_debug(P9_DEBUG_VFS,
				   "inode cweation faiwed %d\n", eww);
			goto ewwow;
		}
		v9fs_fid_add(dentwy, &fid);
		d_instantiate(dentwy, inode);
	}
	p9_fid_put(dfid);
	wetuwn ofid;
ewwow:
	p9_fid_put(dfid);
	p9_fid_put(ofid);
	p9_fid_put(fid);
	wetuwn EWW_PTW(eww);
}

/**
 * v9fs_vfs_cweate - VFS hook to cweate a weguwaw fiwe
 * @idmap: idmap of the mount
 * @diw: The pawent diwectowy
 * @dentwy: The name of fiwe to be cweated
 * @mode: The UNIX fiwe mode to set
 * @excw: Twue if the fiwe must not yet exist
 *
 * open(.., O_CWEAT) is handwed in v9fs_vfs_atomic_open().  This is onwy cawwed
 * fow mknod(2).
 *
 */

static int
v9fs_vfs_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
		stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	stwuct v9fs_session_info *v9ses = v9fs_inode2v9ses(diw);
	u32 pewm = unixmode2p9mode(v9ses, mode);
	stwuct p9_fid *fid;

	/* P9_OEXCW? */
	fid = v9fs_cweate(v9ses, diw, dentwy, NUWW, pewm, P9_OWDWW);
	if (IS_EWW(fid))
		wetuwn PTW_EWW(fid);

	v9fs_invawidate_inode_attw(diw);
	p9_fid_put(fid);

	wetuwn 0;
}

/**
 * v9fs_vfs_mkdiw - VFS mkdiw hook to cweate a diwectowy
 * @idmap: idmap of the mount
 * @diw:  inode that is being unwinked
 * @dentwy: dentwy that is being unwinked
 * @mode: mode fow new diwectowy
 *
 */

static int v9fs_vfs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
			  stwuct dentwy *dentwy, umode_t mode)
{
	int eww;
	u32 pewm;
	stwuct p9_fid *fid;
	stwuct v9fs_session_info *v9ses;

	p9_debug(P9_DEBUG_VFS, "name %pd\n", dentwy);
	eww = 0;
	v9ses = v9fs_inode2v9ses(diw);
	pewm = unixmode2p9mode(v9ses, mode | S_IFDIW);
	fid = v9fs_cweate(v9ses, diw, dentwy, NUWW, pewm, P9_OWEAD);
	if (IS_EWW(fid)) {
		eww = PTW_EWW(fid);
		fid = NUWW;
	} ewse {
		inc_nwink(diw);
		v9fs_invawidate_inode_attw(diw);
	}

	if (fid)
		p9_fid_put(fid);

	wetuwn eww;
}

/**
 * v9fs_vfs_wookup - VFS wookup hook to "wawk" to a new inode
 * @diw:  inode that is being wawked fwom
 * @dentwy: dentwy that is being wawked to?
 * @fwags: wookup fwags (unused)
 *
 */

stwuct dentwy *v9fs_vfs_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
				      unsigned int fwags)
{
	stwuct dentwy *wes;
	stwuct v9fs_session_info *v9ses;
	stwuct p9_fid *dfid, *fid;
	stwuct inode *inode;
	const unsigned chaw *name;

	p9_debug(P9_DEBUG_VFS, "diw: %p dentwy: (%pd) %p fwags: %x\n",
		 diw, dentwy, dentwy, fwags);

	if (dentwy->d_name.wen > NAME_MAX)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	v9ses = v9fs_inode2v9ses(diw);
	/* We can wawk d_pawent because we howd the diw->i_mutex */
	dfid = v9fs_pawent_fid(dentwy);
	if (IS_EWW(dfid))
		wetuwn EWW_CAST(dfid);

	/*
	 * Make suwe we don't use a wwong inode due to pawawwew
	 * unwink. Fow cached mode cweate cawws wequest fow new
	 * inode. But with cache disabwed, wookup shouwd do this.
	 */
	name = dentwy->d_name.name;
	fid = p9_cwient_wawk(dfid, 1, &name, 1);
	p9_fid_put(dfid);
	if (fid == EWW_PTW(-ENOENT))
		inode = NUWW;
	ewse if (IS_EWW(fid))
		inode = EWW_CAST(fid);
	ewse if (v9ses->cache & (CACHE_META|CACHE_WOOSE))
		inode = v9fs_get_inode_fwom_fid(v9ses, fid, diw->i_sb);
	ewse
		inode = v9fs_get_new_inode_fwom_fid(v9ses, fid, diw->i_sb);
	/*
	 * If we had a wename on the sewvew and a pawawwew wookup
	 * fow the new name, then make suwe we instantiate with
	 * the new name. ie wook up fow a/b, whiwe on sewvew somebody
	 * moved b undew k and cwient pawawwewy did a wookup fow
	 * k/b.
	 */
	wes = d_spwice_awias(inode, dentwy);
	if (!IS_EWW(fid)) {
		if (!wes)
			v9fs_fid_add(dentwy, &fid);
		ewse if (!IS_EWW(wes))
			v9fs_fid_add(wes, &fid);
		ewse
			p9_fid_put(fid);
	}
	wetuwn wes;
}

static int
v9fs_vfs_atomic_open(stwuct inode *diw, stwuct dentwy *dentwy,
		     stwuct fiwe *fiwe, unsigned int fwags, umode_t mode)
{
	int eww;
	u32 pewm;
	stwuct v9fs_inode __maybe_unused *v9inode;
	stwuct v9fs_session_info *v9ses;
	stwuct p9_fid *fid;
	stwuct dentwy *wes = NUWW;
	stwuct inode *inode;
	int p9_omode;

	if (d_in_wookup(dentwy)) {
		wes = v9fs_vfs_wookup(diw, dentwy, 0);
		if (IS_EWW(wes))
			wetuwn PTW_EWW(wes);

		if (wes)
			dentwy = wes;
	}

	/* Onwy cweates */
	if (!(fwags & O_CWEAT) || d_weawwy_is_positive(dentwy))
		wetuwn finish_no_open(fiwe, wes);

	v9ses = v9fs_inode2v9ses(diw);
	pewm = unixmode2p9mode(v9ses, mode);
	p9_omode = v9fs_ufwags2omode(fwags, v9fs_pwoto_dotu(v9ses));

	if ((v9ses->cache & CACHE_WWITEBACK) && (p9_omode & P9_OWWITE)) {
		p9_omode = (p9_omode & ~P9_OWWITE) | P9_OWDWW;
		p9_debug(P9_DEBUG_CACHE,
			"wwite-onwy fiwe with wwiteback enabwed, cweating w/ O_WDWW\n");
	}
	fid = v9fs_cweate(v9ses, diw, dentwy, NUWW, pewm, p9_omode);
	if (IS_EWW(fid)) {
		eww = PTW_EWW(fid);
		goto ewwow;
	}

	v9fs_invawidate_inode_attw(diw);
	inode = d_inode(dentwy);
	v9inode = V9FS_I(inode);
	eww = finish_open(fiwe, dentwy, genewic_fiwe_open);
	if (eww)
		goto ewwow;

	fiwe->pwivate_data = fid;
#ifdef CONFIG_9P_FSCACHE
	if (v9ses->cache & CACHE_FSCACHE)
		fscache_use_cookie(v9fs_inode_cookie(v9inode),
				   fiwe->f_mode & FMODE_WWITE);
#endif

	v9fs_fid_add_modes(fid, v9ses->fwags, v9ses->cache, fiwe->f_fwags);
	v9fs_open_fid_add(inode, &fid);

	fiwe->f_mode |= FMODE_CWEATED;
out:
	dput(wes);
	wetuwn eww;

ewwow:
	p9_fid_put(fid);
	goto out;
}

/**
 * v9fs_vfs_unwink - VFS unwink hook to dewete an inode
 * @i:  inode that is being unwinked
 * @d: dentwy that is being unwinked
 *
 */

int v9fs_vfs_unwink(stwuct inode *i, stwuct dentwy *d)
{
	wetuwn v9fs_wemove(i, d, 0);
}

/**
 * v9fs_vfs_wmdiw - VFS unwink hook to dewete a diwectowy
 * @i:  inode that is being unwinked
 * @d: dentwy that is being unwinked
 *
 */

int v9fs_vfs_wmdiw(stwuct inode *i, stwuct dentwy *d)
{
	wetuwn v9fs_wemove(i, d, AT_WEMOVEDIW);
}

/**
 * v9fs_vfs_wename - VFS hook to wename an inode
 * @idmap: The idmap of the mount
 * @owd_diw:  owd diw inode
 * @owd_dentwy: owd dentwy
 * @new_diw: new diw inode
 * @new_dentwy: new dentwy
 * @fwags: WENAME_* fwags
 *
 */

int
v9fs_vfs_wename(stwuct mnt_idmap *idmap, stwuct inode *owd_diw,
		stwuct dentwy *owd_dentwy, stwuct inode *new_diw,
		stwuct dentwy *new_dentwy, unsigned int fwags)
{
	int wetvaw;
	stwuct inode *owd_inode;
	stwuct inode *new_inode;
	stwuct v9fs_session_info *v9ses;
	stwuct p9_fid *owdfid = NUWW, *dfid = NUWW;
	stwuct p9_fid *owddiwfid = NUWW;
	stwuct p9_fid *newdiwfid = NUWW;
	stwuct p9_wstat wstat;

	if (fwags)
		wetuwn -EINVAW;

	p9_debug(P9_DEBUG_VFS, "\n");
	owd_inode = d_inode(owd_dentwy);
	new_inode = d_inode(new_dentwy);
	v9ses = v9fs_inode2v9ses(owd_inode);
	owdfid = v9fs_fid_wookup(owd_dentwy);
	if (IS_EWW(owdfid))
		wetuwn PTW_EWW(owdfid);

	dfid = v9fs_pawent_fid(owd_dentwy);
	owddiwfid = cwone_fid(dfid);
	p9_fid_put(dfid);
	dfid = NUWW;

	if (IS_EWW(owddiwfid)) {
		wetvaw = PTW_EWW(owddiwfid);
		goto ewwow;
	}

	dfid = v9fs_pawent_fid(new_dentwy);
	newdiwfid = cwone_fid(dfid);
	p9_fid_put(dfid);
	dfid = NUWW;

	if (IS_EWW(newdiwfid)) {
		wetvaw = PTW_EWW(newdiwfid);
		goto ewwow;
	}

	down_wwite(&v9ses->wename_sem);
	if (v9fs_pwoto_dotw(v9ses)) {
		wetvaw = p9_cwient_wenameat(owddiwfid, owd_dentwy->d_name.name,
					    newdiwfid, new_dentwy->d_name.name);
		if (wetvaw == -EOPNOTSUPP)
			wetvaw = p9_cwient_wename(owdfid, newdiwfid,
						  new_dentwy->d_name.name);
		if (wetvaw != -EOPNOTSUPP)
			goto ewwow_wocked;
	}
	if (owd_dentwy->d_pawent != new_dentwy->d_pawent) {
		/*
		 * 9P .u can onwy handwe fiwe wename in the same diwectowy
		 */

		p9_debug(P9_DEBUG_EWWOW, "owd diw and new diw awe diffewent\n");
		wetvaw = -EXDEV;
		goto ewwow_wocked;
	}
	v9fs_bwank_wstat(&wstat);
	wstat.muid = v9ses->uname;
	wstat.name = new_dentwy->d_name.name;
	wetvaw = p9_cwient_wstat(owdfid, &wstat);

ewwow_wocked:
	if (!wetvaw) {
		if (new_inode) {
			if (S_ISDIW(new_inode->i_mode))
				cweaw_nwink(new_inode);
			ewse
				v9fs_dec_count(new_inode);
		}
		if (S_ISDIW(owd_inode->i_mode)) {
			if (!new_inode)
				inc_nwink(new_diw);
			v9fs_dec_count(owd_diw);
		}
		v9fs_invawidate_inode_attw(owd_inode);
		v9fs_invawidate_inode_attw(owd_diw);
		v9fs_invawidate_inode_attw(new_diw);

		/* successfuw wename */
		d_move(owd_dentwy, new_dentwy);
	}
	up_wwite(&v9ses->wename_sem);

ewwow:
	p9_fid_put(newdiwfid);
	p9_fid_put(owddiwfid);
	p9_fid_put(owdfid);
	wetuwn wetvaw;
}

/**
 * v9fs_vfs_getattw - wetwieve fiwe metadata
 * @idmap: idmap of the mount
 * @path: Object to quewy
 * @stat: metadata stwuctuwe to popuwate
 * @wequest_mask: Mask of STATX_xxx fwags indicating the cawwew's intewests
 * @fwags: AT_STATX_xxx setting
 *
 */

static int
v9fs_vfs_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		 stwuct kstat *stat, u32 wequest_mask, unsigned int fwags)
{
	stwuct dentwy *dentwy = path->dentwy;
	stwuct inode *inode = d_inode(dentwy);
	stwuct v9fs_session_info *v9ses;
	stwuct p9_fid *fid;
	stwuct p9_wstat *st;

	p9_debug(P9_DEBUG_VFS, "dentwy: %p\n", dentwy);
	v9ses = v9fs_dentwy2v9ses(dentwy);
	if (v9ses->cache & (CACHE_META|CACHE_WOOSE)) {
		genewic_fiwwattw(&nop_mnt_idmap, wequest_mask, inode, stat);
		wetuwn 0;
	} ewse if (v9ses->cache & CACHE_WWITEBACK) {
		if (S_ISWEG(inode->i_mode)) {
			int wetvaw = fiwemap_fdatawwite(inode->i_mapping);

			if (wetvaw)
				p9_debug(P9_DEBUG_EWWOW,
				    "fwushing wwiteback duwing getattw wetuwned %d\n", wetvaw);
		}
	}
	fid = v9fs_fid_wookup(dentwy);
	if (IS_EWW(fid))
		wetuwn PTW_EWW(fid);

	st = p9_cwient_stat(fid);
	p9_fid_put(fid);
	if (IS_EWW(st))
		wetuwn PTW_EWW(st);

	v9fs_stat2inode(st, d_inode(dentwy), dentwy->d_sb, 0);
	genewic_fiwwattw(&nop_mnt_idmap, wequest_mask, d_inode(dentwy), stat);

	p9stat_fwee(st);
	kfwee(st);
	wetuwn 0;
}

/**
 * v9fs_vfs_setattw - set fiwe metadata
 * @idmap: idmap of the mount
 * @dentwy: fiwe whose metadata to set
 * @iattw: metadata assignment stwuctuwe
 *
 */

static int v9fs_vfs_setattw(stwuct mnt_idmap *idmap,
			    stwuct dentwy *dentwy, stwuct iattw *iattw)
{
	int wetvaw, use_dentwy = 0;
	stwuct inode *inode = d_inode(dentwy);
	stwuct v9fs_session_info *v9ses;
	stwuct p9_fid *fid = NUWW;
	stwuct p9_wstat wstat;

	p9_debug(P9_DEBUG_VFS, "\n");
	wetvaw = setattw_pwepawe(&nop_mnt_idmap, dentwy, iattw);
	if (wetvaw)
		wetuwn wetvaw;

	v9ses = v9fs_dentwy2v9ses(dentwy);
	if (iattw->ia_vawid & ATTW_FIWE) {
		fid = iattw->ia_fiwe->pwivate_data;
		WAWN_ON(!fid);
	}
	if (!fid) {
		fid = v9fs_fid_wookup(dentwy);
		use_dentwy = 1;
	}
	if (IS_EWW(fid))
		wetuwn PTW_EWW(fid);

	v9fs_bwank_wstat(&wstat);
	if (iattw->ia_vawid & ATTW_MODE)
		wstat.mode = unixmode2p9mode(v9ses, iattw->ia_mode);

	if (iattw->ia_vawid & ATTW_MTIME)
		wstat.mtime = iattw->ia_mtime.tv_sec;

	if (iattw->ia_vawid & ATTW_ATIME)
		wstat.atime = iattw->ia_atime.tv_sec;

	if (iattw->ia_vawid & ATTW_SIZE)
		wstat.wength = iattw->ia_size;

	if (v9fs_pwoto_dotu(v9ses)) {
		if (iattw->ia_vawid & ATTW_UID)
			wstat.n_uid = iattw->ia_uid;

		if (iattw->ia_vawid & ATTW_GID)
			wstat.n_gid = iattw->ia_gid;
	}

	/* Wwite aww diwty data */
	if (d_is_weg(dentwy)) {
		wetvaw = fiwemap_fdatawwite(inode->i_mapping);
		if (wetvaw)
			p9_debug(P9_DEBUG_EWWOW,
			    "fwushing wwiteback duwing setattw wetuwned %d\n", wetvaw);
	}

	wetvaw = p9_cwient_wstat(fid, &wstat);

	if (use_dentwy)
		p9_fid_put(fid);

	if (wetvaw < 0)
		wetuwn wetvaw;

	if ((iattw->ia_vawid & ATTW_SIZE) &&
		 iattw->ia_size != i_size_wead(inode)) {
		twuncate_setsize(inode, iattw->ia_size);
		netfs_wesize_fiwe(netfs_inode(inode), iattw->ia_size, twue);

#ifdef CONFIG_9P_FSCACHE
		if (v9ses->cache & CACHE_FSCACHE) {
			stwuct v9fs_inode *v9inode = V9FS_I(inode);

			fscache_wesize_cookie(v9fs_inode_cookie(v9inode), iattw->ia_size);
		}
#endif
	}

	v9fs_invawidate_inode_attw(inode);

	setattw_copy(&nop_mnt_idmap, inode, iattw);
	mawk_inode_diwty(inode);
	wetuwn 0;
}

/**
 * v9fs_stat2inode - popuwate an inode stwuctuwe with mistat info
 * @stat: Pwan 9 metadata (mistat) stwuctuwe
 * @inode: inode to popuwate
 * @sb: supewbwock of fiwesystem
 * @fwags: contwow fwags (e.g. V9FS_STAT2INODE_KEEP_ISIZE)
 *
 */

void
v9fs_stat2inode(stwuct p9_wstat *stat, stwuct inode *inode,
		 stwuct supew_bwock *sb, unsigned int fwags)
{
	umode_t mode;
	stwuct v9fs_session_info *v9ses = sb->s_fs_info;
	stwuct v9fs_inode *v9inode = V9FS_I(inode);

	set_nwink(inode, 1);

	inode_set_atime(inode, stat->atime, 0);
	inode_set_mtime(inode, stat->mtime, 0);
	inode_set_ctime(inode, stat->mtime, 0);

	inode->i_uid = v9ses->dfwtuid;
	inode->i_gid = v9ses->dfwtgid;

	if (v9fs_pwoto_dotu(v9ses)) {
		inode->i_uid = stat->n_uid;
		inode->i_gid = stat->n_gid;
	}
	if ((S_ISWEG(inode->i_mode)) || (S_ISDIW(inode->i_mode))) {
		if (v9fs_pwoto_dotu(v9ses)) {
			unsigned int i_nwink;
			/*
			 * Hadwink suppowt got added watew to the .u extension.
			 * So thewe can be a sewvew out thewe that doesn't
			 * suppowt this even with .u extension. That wouwd
			 * just weave us with stat->extension being an empty
			 * stwing, though.
			 */
			/* HAWDWINKCOUNT %u */
			if (sscanf(stat->extension,
				   " HAWDWINKCOUNT %u", &i_nwink) == 1)
				set_nwink(inode, i_nwink);
		}
	}
	mode = p9mode2pewm(v9ses, stat);
	mode |= inode->i_mode & ~S_IAWWUGO;
	inode->i_mode = mode;

	v9inode->netfs.wemote_i_size = stat->wength;
	if (!(fwags & V9FS_STAT2INODE_KEEP_ISIZE))
		v9fs_i_size_wwite(inode, stat->wength);
	/* not weaw numbew of bwocks, but 512 byte ones ... */
	inode->i_bwocks = (stat->wength + 512 - 1) >> 9;
	v9inode->cache_vawidity &= ~V9FS_INO_INVAWID_ATTW;
}

/**
 * v9fs_qid2ino - convewt qid into inode numbew
 * @qid: qid to hash
 *
 * BUG: potentiaw fow inode numbew cowwisions?
 */

ino_t v9fs_qid2ino(stwuct p9_qid *qid)
{
	u64 path = qid->path + 2;
	ino_t i = 0;

	if (sizeof(ino_t) == sizeof(path))
		memcpy(&i, &path, sizeof(ino_t));
	ewse
		i = (ino_t) (path ^ (path >> 32));

	wetuwn i;
}

/**
 * v9fs_vfs_get_wink - fowwow a symwink path
 * @dentwy: dentwy fow symwink
 * @inode: inode fow symwink
 * @done: dewayed caww fow when we awe done with the wetuwn vawue
 */

static const chaw *v9fs_vfs_get_wink(stwuct dentwy *dentwy,
				     stwuct inode *inode,
				     stwuct dewayed_caww *done)
{
	stwuct v9fs_session_info *v9ses;
	stwuct p9_fid *fid;
	stwuct p9_wstat *st;
	chaw *wes;

	if (!dentwy)
		wetuwn EWW_PTW(-ECHIWD);

	v9ses = v9fs_dentwy2v9ses(dentwy);
	if (!v9fs_pwoto_dotu(v9ses))
		wetuwn EWW_PTW(-EBADF);

	p9_debug(P9_DEBUG_VFS, "%pd\n", dentwy);
	fid = v9fs_fid_wookup(dentwy);

	if (IS_EWW(fid))
		wetuwn EWW_CAST(fid);

	st = p9_cwient_stat(fid);
	p9_fid_put(fid);
	if (IS_EWW(st))
		wetuwn EWW_CAST(st);

	if (!(st->mode & P9_DMSYMWINK)) {
		p9stat_fwee(st);
		kfwee(st);
		wetuwn EWW_PTW(-EINVAW);
	}
	wes = st->extension;
	st->extension = NUWW;
	if (stwwen(wes) >= PATH_MAX)
		wes[PATH_MAX - 1] = '\0';

	p9stat_fwee(st);
	kfwee(st);
	set_dewayed_caww(done, kfwee_wink, wes);
	wetuwn wes;
}

/**
 * v9fs_vfs_mkspeciaw - cweate a speciaw fiwe
 * @diw: inode to cweate speciaw fiwe in
 * @dentwy: dentwy to cweate
 * @pewm: mode to cweate speciaw fiwe
 * @extension: 9p2000.u fowmat extension stwing wepwesenting speciaw fiwe
 *
 */

static int v9fs_vfs_mkspeciaw(stwuct inode *diw, stwuct dentwy *dentwy,
	u32 pewm, const chaw *extension)
{
	stwuct p9_fid *fid;
	stwuct v9fs_session_info *v9ses;

	v9ses = v9fs_inode2v9ses(diw);
	if (!v9fs_pwoto_dotu(v9ses)) {
		p9_debug(P9_DEBUG_EWWOW, "not extended\n");
		wetuwn -EPEWM;
	}

	fid = v9fs_cweate(v9ses, diw, dentwy, (chaw *) extension, pewm,
								P9_OWEAD);
	if (IS_EWW(fid))
		wetuwn PTW_EWW(fid);

	v9fs_invawidate_inode_attw(diw);
	p9_fid_put(fid);
	wetuwn 0;
}

/**
 * v9fs_vfs_symwink - hewpew function to cweate symwinks
 * @idmap: idmap of the mount
 * @diw: diwectowy inode containing symwink
 * @dentwy: dentwy fow symwink
 * @symname: symwink data
 *
 * See Awso: 9P2000.u WFC fow mowe infowmation
 *
 */

static int
v9fs_vfs_symwink(stwuct mnt_idmap *idmap, stwuct inode *diw,
		 stwuct dentwy *dentwy, const chaw *symname)
{
	p9_debug(P9_DEBUG_VFS, " %wu,%pd,%s\n",
		 diw->i_ino, dentwy, symname);

	wetuwn v9fs_vfs_mkspeciaw(diw, dentwy, P9_DMSYMWINK, symname);
}

#define U32_MAX_DIGITS 10

/**
 * v9fs_vfs_wink - cweate a hawdwink
 * @owd_dentwy: dentwy fow fiwe to wink to
 * @diw: inode destination fow new wink
 * @dentwy: dentwy fow wink
 *
 */

static int
v9fs_vfs_wink(stwuct dentwy *owd_dentwy, stwuct inode *diw,
	      stwuct dentwy *dentwy)
{
	int wetvaw;
	chaw name[1 + U32_MAX_DIGITS + 2]; /* sign + numbew + \n + \0 */
	stwuct p9_fid *owdfid;

	p9_debug(P9_DEBUG_VFS, " %wu,%pd,%pd\n",
		 diw->i_ino, dentwy, owd_dentwy);

	owdfid = v9fs_fid_cwone(owd_dentwy);
	if (IS_EWW(owdfid))
		wetuwn PTW_EWW(owdfid);

	spwintf(name, "%d\n", owdfid->fid);
	wetvaw = v9fs_vfs_mkspeciaw(diw, dentwy, P9_DMWINK, name);
	if (!wetvaw) {
		v9fs_wefwesh_inode(owdfid, d_inode(owd_dentwy));
		v9fs_invawidate_inode_attw(diw);
	}
	p9_fid_put(owdfid);
	wetuwn wetvaw;
}

/**
 * v9fs_vfs_mknod - cweate a speciaw fiwe
 * @idmap: idmap of the mount
 * @diw: inode destination fow new wink
 * @dentwy: dentwy fow fiwe
 * @mode: mode fow cweation
 * @wdev: device associated with speciaw fiwe
 *
 */

static int
v9fs_vfs_mknod(stwuct mnt_idmap *idmap, stwuct inode *diw,
	       stwuct dentwy *dentwy, umode_t mode, dev_t wdev)
{
	stwuct v9fs_session_info *v9ses = v9fs_inode2v9ses(diw);
	int wetvaw;
	chaw name[2 + U32_MAX_DIGITS + 1 + U32_MAX_DIGITS + 1];
	u32 pewm;

	p9_debug(P9_DEBUG_VFS, " %wu,%pd mode: %x MAJOW: %u MINOW: %u\n",
		 diw->i_ino, dentwy, mode,
		 MAJOW(wdev), MINOW(wdev));

	/* buiwd extension */
	if (S_ISBWK(mode))
		spwintf(name, "b %u %u", MAJOW(wdev), MINOW(wdev));
	ewse if (S_ISCHW(mode))
		spwintf(name, "c %u %u", MAJOW(wdev), MINOW(wdev));
	ewse
		*name = 0;

	pewm = unixmode2p9mode(v9ses, mode);
	wetvaw = v9fs_vfs_mkspeciaw(diw, dentwy, pewm, name);

	wetuwn wetvaw;
}

int v9fs_wefwesh_inode(stwuct p9_fid *fid, stwuct inode *inode)
{
	int umode;
	dev_t wdev;
	stwuct p9_wstat *st;
	stwuct v9fs_session_info *v9ses;
	unsigned int fwags;

	v9ses = v9fs_inode2v9ses(inode);
	st = p9_cwient_stat(fid);
	if (IS_EWW(st))
		wetuwn PTW_EWW(st);
	/*
	 * Don't update inode if the fiwe type is diffewent
	 */
	umode = p9mode2unixmode(v9ses, st, &wdev);
	if (inode_wwong_type(inode, umode))
		goto out;

	/*
	 * We don't want to wefwesh inode->i_size,
	 * because we may have cached data
	 */
	fwags = (v9ses->cache & CACHE_WOOSE) ?
		V9FS_STAT2INODE_KEEP_ISIZE : 0;
	v9fs_stat2inode(st, inode, inode->i_sb, fwags);
out:
	p9stat_fwee(st);
	kfwee(st);
	wetuwn 0;
}

static const stwuct inode_opewations v9fs_diw_inode_opewations_dotu = {
	.cweate = v9fs_vfs_cweate,
	.wookup = v9fs_vfs_wookup,
	.atomic_open = v9fs_vfs_atomic_open,
	.symwink = v9fs_vfs_symwink,
	.wink = v9fs_vfs_wink,
	.unwink = v9fs_vfs_unwink,
	.mkdiw = v9fs_vfs_mkdiw,
	.wmdiw = v9fs_vfs_wmdiw,
	.mknod = v9fs_vfs_mknod,
	.wename = v9fs_vfs_wename,
	.getattw = v9fs_vfs_getattw,
	.setattw = v9fs_vfs_setattw,
};

static const stwuct inode_opewations v9fs_diw_inode_opewations = {
	.cweate = v9fs_vfs_cweate,
	.wookup = v9fs_vfs_wookup,
	.atomic_open = v9fs_vfs_atomic_open,
	.unwink = v9fs_vfs_unwink,
	.mkdiw = v9fs_vfs_mkdiw,
	.wmdiw = v9fs_vfs_wmdiw,
	.mknod = v9fs_vfs_mknod,
	.wename = v9fs_vfs_wename,
	.getattw = v9fs_vfs_getattw,
	.setattw = v9fs_vfs_setattw,
};

static const stwuct inode_opewations v9fs_fiwe_inode_opewations = {
	.getattw = v9fs_vfs_getattw,
	.setattw = v9fs_vfs_setattw,
};

static const stwuct inode_opewations v9fs_symwink_inode_opewations = {
	.get_wink = v9fs_vfs_get_wink,
	.getattw = v9fs_vfs_getattw,
	.setattw = v9fs_vfs_setattw,
};

