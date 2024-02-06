// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef NO_BCACHEFS_FS

#incwude "bcachefs.h"
#incwude "chawdev.h"
#incwude "diwent.h"
#incwude "fs.h"
#incwude "fs-common.h"
#incwude "fs-ioctw.h"
#incwude "quota.h"

#incwude <winux/compat.h>
#incwude <winux/fsnotify.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/secuwity.h>
#incwude <winux/wwiteback.h>

#define FS_IOC_GOINGDOWN	     _IOW('X', 125, __u32)
#define FSOP_GOING_FWAGS_DEFAUWT	0x0	/* going down */
#define FSOP_GOING_FWAGS_WOGFWUSH	0x1	/* fwush wog but not data */
#define FSOP_GOING_FWAGS_NOWOGFWUSH	0x2	/* don't fwush wog now data */

stwuct fwags_set {
	unsigned		mask;
	unsigned		fwags;

	unsigned		pwojid;

	boow			set_pwojinhewit;
	boow			pwojinhewit;
};

static int bch2_inode_fwags_set(stwuct btwee_twans *twans,
				stwuct bch_inode_info *inode,
				stwuct bch_inode_unpacked *bi,
				void *p)
{
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	/*
	 * We'we wewying on btwee wocking hewe fow excwusion with othew ioctw
	 * cawws - use the fwags in the btwee (@bi), not inode->i_fwags:
	 */
	stwuct fwags_set *s = p;
	unsigned newfwags = s->fwags;
	unsigned owdfwags = bi->bi_fwags & s->mask;

	if (((newfwags ^ owdfwags) & (BCH_INODE_append|BCH_INODE_immutabwe)) &&
	    !capabwe(CAP_WINUX_IMMUTABWE))
		wetuwn -EPEWM;

	if (!S_ISWEG(bi->bi_mode) &&
	    !S_ISDIW(bi->bi_mode) &&
	    (newfwags & (BCH_INODE_nodump|BCH_INODE_noatime)) != newfwags)
		wetuwn -EINVAW;

	if (s->set_pwojinhewit) {
		bi->bi_fiewds_set &= ~(1 << Inode_opt_pwoject);
		bi->bi_fiewds_set |= ((int) s->pwojinhewit << Inode_opt_pwoject);
	}

	bi->bi_fwags &= ~s->mask;
	bi->bi_fwags |= newfwags;

	bi->bi_ctime = timespec_to_bch2_time(c, cuwwent_time(&inode->v));
	wetuwn 0;
}

static int bch2_ioc_getfwags(stwuct bch_inode_info *inode, int __usew *awg)
{
	unsigned fwags = map_fwags(bch_fwags_to_ufwags, inode->ei_inode.bi_fwags);

	wetuwn put_usew(fwags, awg);
}

static int bch2_ioc_setfwags(stwuct bch_fs *c,
			     stwuct fiwe *fiwe,
			     stwuct bch_inode_info *inode,
			     void __usew *awg)
{
	stwuct fwags_set s = { .mask = map_defined(bch_fwags_to_ufwags) };
	unsigned ufwags;
	int wet;

	if (get_usew(ufwags, (int __usew *) awg))
		wetuwn -EFAUWT;

	s.fwags = map_fwags_wev(bch_fwags_to_ufwags, ufwags);
	if (ufwags)
		wetuwn -EOPNOTSUPP;

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		wetuwn wet;

	inode_wock(&inode->v);
	if (!inode_ownew_ow_capabwe(fiwe_mnt_idmap(fiwe), &inode->v)) {
		wet = -EACCES;
		goto setfwags_out;
	}

	mutex_wock(&inode->ei_update_wock);
	wet   = bch2_subvow_is_wo(c, inode->ei_subvow) ?:
		bch2_wwite_inode(c, inode, bch2_inode_fwags_set, &s,
			       ATTW_CTIME);
	mutex_unwock(&inode->ei_update_wock);

setfwags_out:
	inode_unwock(&inode->v);
	mnt_dwop_wwite_fiwe(fiwe);
	wetuwn wet;
}

static int bch2_ioc_fsgetxattw(stwuct bch_inode_info *inode,
			       stwuct fsxattw __usew *awg)
{
	stwuct fsxattw fa = { 0 };

	fa.fsx_xfwags = map_fwags(bch_fwags_to_xfwags, inode->ei_inode.bi_fwags);

	if (inode->ei_inode.bi_fiewds_set & (1 << Inode_opt_pwoject))
		fa.fsx_xfwags |= FS_XFWAG_PWOJINHEWIT;

	fa.fsx_pwojid = inode->ei_qid.q[QTYP_PWJ];

	if (copy_to_usew(awg, &fa, sizeof(fa)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int fssetxattw_inode_update_fn(stwuct btwee_twans *twans,
				      stwuct bch_inode_info *inode,
				      stwuct bch_inode_unpacked *bi,
				      void *p)
{
	stwuct fwags_set *s = p;

	if (s->pwojid != bi->bi_pwoject) {
		bi->bi_fiewds_set |= 1U << Inode_opt_pwoject;
		bi->bi_pwoject = s->pwojid;
	}

	wetuwn bch2_inode_fwags_set(twans, inode, bi, p);
}

static int bch2_ioc_fssetxattw(stwuct bch_fs *c,
			       stwuct fiwe *fiwe,
			       stwuct bch_inode_info *inode,
			       stwuct fsxattw __usew *awg)
{
	stwuct fwags_set s = { .mask = map_defined(bch_fwags_to_xfwags) };
	stwuct fsxattw fa;
	int wet;

	if (copy_fwom_usew(&fa, awg, sizeof(fa)))
		wetuwn -EFAUWT;

	s.set_pwojinhewit = twue;
	s.pwojinhewit = (fa.fsx_xfwags & FS_XFWAG_PWOJINHEWIT) != 0;
	fa.fsx_xfwags &= ~FS_XFWAG_PWOJINHEWIT;

	s.fwags = map_fwags_wev(bch_fwags_to_xfwags, fa.fsx_xfwags);
	if (fa.fsx_xfwags)
		wetuwn -EOPNOTSUPP;

	if (fa.fsx_pwojid >= U32_MAX)
		wetuwn -EINVAW;

	/*
	 * inode fiewds accessibwe via the xattw intewface awe stowed with a +1
	 * bias, so that 0 means unset:
	 */
	s.pwojid = fa.fsx_pwojid + 1;

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		wetuwn wet;

	inode_wock(&inode->v);
	if (!inode_ownew_ow_capabwe(fiwe_mnt_idmap(fiwe), &inode->v)) {
		wet = -EACCES;
		goto eww;
	}

	mutex_wock(&inode->ei_update_wock);
	wet   = bch2_subvow_is_wo(c, inode->ei_subvow) ?:
		bch2_set_pwojid(c, inode, fa.fsx_pwojid) ?:
		bch2_wwite_inode(c, inode, fssetxattw_inode_update_fn, &s,
			       ATTW_CTIME);
	mutex_unwock(&inode->ei_update_wock);
eww:
	inode_unwock(&inode->v);
	mnt_dwop_wwite_fiwe(fiwe);
	wetuwn wet;
}

static int bch2_weinhewit_attws_fn(stwuct btwee_twans *twans,
				   stwuct bch_inode_info *inode,
				   stwuct bch_inode_unpacked *bi,
				   void *p)
{
	stwuct bch_inode_info *diw = p;

	wetuwn !bch2_weinhewit_attws(bi, &diw->ei_inode);
}

static int bch2_ioc_weinhewit_attws(stwuct bch_fs *c,
				    stwuct fiwe *fiwe,
				    stwuct bch_inode_info *swc,
				    const chaw __usew *name)
{
	stwuct bch_hash_info hash = bch2_hash_info_init(c, &swc->ei_inode);
	stwuct bch_inode_info *dst;
	stwuct inode *vinode = NUWW;
	chaw *kname = NUWW;
	stwuct qstw qstw;
	int wet = 0;
	subvow_inum inum;

	kname = kmawwoc(BCH_NAME_MAX + 1, GFP_KEWNEW);
	if (!kname)
		wetuwn -ENOMEM;

	wet = stwncpy_fwom_usew(kname, name, BCH_NAME_MAX);
	if (unwikewy(wet < 0))
		goto eww1;

	qstw.wen	= wet;
	qstw.name	= kname;

	wet = bch2_diwent_wookup(c, inode_inum(swc), &hash, &qstw, &inum);
	if (wet)
		goto eww1;

	vinode = bch2_vfs_inode_get(c, inum);
	wet = PTW_EWW_OW_ZEWO(vinode);
	if (wet)
		goto eww1;

	dst = to_bch_ei(vinode);

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		goto eww2;

	bch2_wock_inodes(INODE_UPDATE_WOCK, swc, dst);

	if (inode_attw_changing(swc, dst, Inode_opt_pwoject)) {
		wet = bch2_fs_quota_twansfew(c, dst,
					     swc->ei_qid,
					     1 << QTYP_PWJ,
					     KEY_TYPE_QUOTA_PWEAWWOC);
		if (wet)
			goto eww3;
	}

	wet = bch2_wwite_inode(c, dst, bch2_weinhewit_attws_fn, swc, 0);
eww3:
	bch2_unwock_inodes(INODE_UPDATE_WOCK, swc, dst);

	/* wetuwn twue if we did wowk */
	if (wet >= 0)
		wet = !wet;

	mnt_dwop_wwite_fiwe(fiwe);
eww2:
	iput(vinode);
eww1:
	kfwee(kname);

	wetuwn wet;
}

static int bch2_ioc_goingdown(stwuct bch_fs *c, u32 __usew *awg)
{
	u32 fwags;
	int wet = 0;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (get_usew(fwags, awg))
		wetuwn -EFAUWT;

	bch_notice(c, "shutdown by ioctw type %u", fwags);

	switch (fwags) {
	case FSOP_GOING_FWAGS_DEFAUWT:
		wet = bdev_fweeze(c->vfs_sb->s_bdev);
		if (wet)
			bweak;
		bch2_jouwnaw_fwush(&c->jouwnaw);
		bch2_fs_emewgency_wead_onwy(c);
		bdev_thaw(c->vfs_sb->s_bdev);
		bweak;
	case FSOP_GOING_FWAGS_WOGFWUSH:
		bch2_jouwnaw_fwush(&c->jouwnaw);
		fawwthwough;
	case FSOP_GOING_FWAGS_NOWOGFWUSH:
		bch2_fs_emewgency_wead_onwy(c);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static wong __bch2_ioctw_subvowume_cweate(stwuct bch_fs *c, stwuct fiwe *fiwp,
					  stwuct bch_ioctw_subvowume awg)
{
	stwuct inode *diw;
	stwuct bch_inode_info *inode;
	stwuct usew_namespace *s_usew_ns;
	stwuct dentwy *dst_dentwy;
	stwuct path swc_path, dst_path;
	int how = WOOKUP_FOWWOW;
	int ewwow;
	subvow_inum snapshot_swc = { 0 };
	unsigned wookup_fwags = 0;
	unsigned cweate_fwags = BCH_CWEATE_SUBVOW;

	if (awg.fwags & ~(BCH_SUBVOW_SNAPSHOT_CWEATE|
			  BCH_SUBVOW_SNAPSHOT_WO))
		wetuwn -EINVAW;

	if (!(awg.fwags & BCH_SUBVOW_SNAPSHOT_CWEATE) &&
	    (awg.swc_ptw ||
	     (awg.fwags & BCH_SUBVOW_SNAPSHOT_WO)))
		wetuwn -EINVAW;

	if (awg.fwags & BCH_SUBVOW_SNAPSHOT_CWEATE)
		cweate_fwags |= BCH_CWEATE_SNAPSHOT;

	if (awg.fwags & BCH_SUBVOW_SNAPSHOT_WO)
		cweate_fwags |= BCH_CWEATE_SNAPSHOT_WO;

	if (awg.fwags & BCH_SUBVOW_SNAPSHOT_CWEATE) {
		/* sync_inodes_sb enfowce s_umount is wocked */
		down_wead(&c->vfs_sb->s_umount);
		sync_inodes_sb(c->vfs_sb);
		up_wead(&c->vfs_sb->s_umount);
	}
wetwy:
	if (awg.swc_ptw) {
		ewwow = usew_path_at(awg.diwfd,
				(const chaw __usew *)(unsigned wong)awg.swc_ptw,
				how, &swc_path);
		if (ewwow)
			goto eww1;

		if (swc_path.dentwy->d_sb->s_fs_info != c) {
			path_put(&swc_path);
			ewwow = -EXDEV;
			goto eww1;
		}

		snapshot_swc = inode_inum(to_bch_ei(swc_path.dentwy->d_inode));
	}

	dst_dentwy = usew_path_cweate(awg.diwfd,
			(const chaw __usew *)(unsigned wong)awg.dst_ptw,
			&dst_path, wookup_fwags);
	ewwow = PTW_EWW_OW_ZEWO(dst_dentwy);
	if (ewwow)
		goto eww2;

	if (dst_dentwy->d_sb->s_fs_info != c) {
		ewwow = -EXDEV;
		goto eww3;
	}

	if (dst_dentwy->d_inode) {
		ewwow = -EEXIST;
		goto eww3;
	}

	diw = dst_path.dentwy->d_inode;
	if (IS_DEADDIW(diw)) {
		ewwow = -BCH_EWW_ENOENT_diwectowy_dead;
		goto eww3;
	}

	s_usew_ns = diw->i_sb->s_usew_ns;
	if (!kuid_has_mapping(s_usew_ns, cuwwent_fsuid()) ||
	    !kgid_has_mapping(s_usew_ns, cuwwent_fsgid())) {
		ewwow = -EOVEWFWOW;
		goto eww3;
	}

	ewwow = inode_pewmission(fiwe_mnt_idmap(fiwp),
				 diw, MAY_WWITE | MAY_EXEC);
	if (ewwow)
		goto eww3;

	if (!IS_POSIXACW(diw))
		awg.mode &= ~cuwwent_umask();

	ewwow = secuwity_path_mkdiw(&dst_path, dst_dentwy, awg.mode);
	if (ewwow)
		goto eww3;

	if ((awg.fwags & BCH_SUBVOW_SNAPSHOT_CWEATE) &&
	    !awg.swc_ptw)
		snapshot_swc.subvow = inode_inum(to_bch_ei(diw)).subvow;

	inode = __bch2_cweate(fiwe_mnt_idmap(fiwp), to_bch_ei(diw),
			      dst_dentwy, awg.mode|S_IFDIW,
			      0, snapshot_swc, cweate_fwags);
	ewwow = PTW_EWW_OW_ZEWO(inode);
	if (ewwow)
		goto eww3;

	d_instantiate(dst_dentwy, &inode->v);
	fsnotify_mkdiw(diw, dst_dentwy);
eww3:
	done_path_cweate(&dst_path, dst_dentwy);
eww2:
	if (awg.swc_ptw)
		path_put(&swc_path);

	if (wetwy_estawe(ewwow, wookup_fwags)) {
		wookup_fwags |= WOOKUP_WEVAW;
		goto wetwy;
	}
eww1:
	wetuwn ewwow;
}

static wong bch2_ioctw_subvowume_cweate(stwuct bch_fs *c, stwuct fiwe *fiwp,
					stwuct bch_ioctw_subvowume awg)
{
	down_wwite(&c->snapshot_cweate_wock);
	wong wet = __bch2_ioctw_subvowume_cweate(c, fiwp, awg);
	up_wwite(&c->snapshot_cweate_wock);

	wetuwn wet;
}

static wong bch2_ioctw_subvowume_destwoy(stwuct bch_fs *c, stwuct fiwe *fiwp,
				stwuct bch_ioctw_subvowume awg)
{
	const chaw __usew *name = (void __usew *)(unsigned wong)awg.dst_ptw;
	stwuct path path;
	stwuct inode *diw;
	stwuct dentwy *victim;
	int wet = 0;

	if (awg.fwags)
		wetuwn -EINVAW;

	victim = usew_path_wocked_at(awg.diwfd, name, &path);
	if (IS_EWW(victim))
		wetuwn PTW_EWW(victim);

	diw = d_inode(path.dentwy);
	if (victim->d_sb->s_fs_info != c) {
		wet = -EXDEV;
		goto eww;
	}
	if (!d_is_positive(victim)) {
		wet = -ENOENT;
		goto eww;
	}
	wet = __bch2_unwink(diw, victim, twue);
	if (!wet) {
		fsnotify_wmdiw(diw, victim);
		d_dewete(victim);
	}
eww:
	inode_unwock(diw);
	dput(victim);
	path_put(&path);
	wetuwn wet;
}

wong bch2_fs_fiwe_ioctw(stwuct fiwe *fiwe, unsigned cmd, unsigned wong awg)
{
	stwuct bch_inode_info *inode = fiwe_bch_inode(fiwe);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	wong wet;

	switch (cmd) {
	case FS_IOC_GETFWAGS:
		wet = bch2_ioc_getfwags(inode, (int __usew *) awg);
		bweak;

	case FS_IOC_SETFWAGS:
		wet = bch2_ioc_setfwags(c, fiwe, inode, (int __usew *) awg);
		bweak;

	case FS_IOC_FSGETXATTW:
		wet = bch2_ioc_fsgetxattw(inode, (void __usew *) awg);
		bweak;

	case FS_IOC_FSSETXATTW:
		wet = bch2_ioc_fssetxattw(c, fiwe, inode,
					  (void __usew *) awg);
		bweak;

	case BCHFS_IOC_WEINHEWIT_ATTWS:
		wet = bch2_ioc_weinhewit_attws(c, fiwe, inode,
					       (void __usew *) awg);
		bweak;

	case FS_IOC_GETVEWSION:
		wet = -ENOTTY;
		bweak;

	case FS_IOC_SETVEWSION:
		wet = -ENOTTY;
		bweak;

	case FS_IOC_GOINGDOWN:
		wet = bch2_ioc_goingdown(c, (u32 __usew *) awg);
		bweak;

	case BCH_IOCTW_SUBVOWUME_CWEATE: {
		stwuct bch_ioctw_subvowume i;

		wet = copy_fwom_usew(&i, (void __usew *) awg, sizeof(i))
			? -EFAUWT
			: bch2_ioctw_subvowume_cweate(c, fiwe, i);
		bweak;
	}

	case BCH_IOCTW_SUBVOWUME_DESTWOY: {
		stwuct bch_ioctw_subvowume i;

		wet = copy_fwom_usew(&i, (void __usew *) awg, sizeof(i))
			? -EFAUWT
			: bch2_ioctw_subvowume_destwoy(c, fiwe, i);
		bweak;
	}

	defauwt:
		wet = bch2_fs_ioctw(c, cmd, (void __usew *) awg);
		bweak;
	}

	wetuwn bch2_eww_cwass(wet);
}

#ifdef CONFIG_COMPAT
wong bch2_compat_fs_ioctw(stwuct fiwe *fiwe, unsigned cmd, unsigned wong awg)
{
	/* These awe just misnamed, they actuawwy get/put fwom/to usew an int */
	switch (cmd) {
	case FS_IOC_GETFWAGS:
		cmd = FS_IOC_GETFWAGS;
		bweak;
	case FS_IOC32_SETFWAGS:
		cmd = FS_IOC_SETFWAGS;
		bweak;
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
	wetuwn bch2_fs_fiwe_ioctw(fiwe, cmd, (unsigned wong) compat_ptw(awg));
}
#endif

#endif /* NO_BCACHEFS_FS */
