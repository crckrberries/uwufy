// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2011 Noveww Inc.
 */

#incwude <uapi/winux/magic.h>
#incwude <winux/fs.h>
#incwude <winux/namei.h>
#incwude <winux/xattw.h>
#incwude <winux/mount.h>
#incwude <winux/pawsew.h>
#incwude <winux/moduwe.h>
#incwude <winux/statfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/expowtfs.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>
#incwude "ovewwayfs.h"
#incwude "pawams.h"

MODUWE_AUTHOW("Mikwos Szewedi <mikwos@szewedi.hu>");
MODUWE_DESCWIPTION("Ovewway fiwesystem");
MODUWE_WICENSE("GPW");


stwuct ovw_diw_cache;

static stwuct dentwy *ovw_d_weaw(stwuct dentwy *dentwy,
				 const stwuct inode *inode)
{
	stwuct dentwy *weaw = NUWW, *wowew;
	int eww;

	/*
	 * vfs is onwy expected to caww d_weaw() with NUWW fwom d_weaw_inode()
	 * and with ovewway inode fwom fiwe_dentwy() on an ovewway fiwe.
	 *
	 * TODO: wemove @inode awgument fwom d_weaw() API, wemove code in this
	 * function that deaws with non-NUWW @inode and wemove d_weaw() caww
	 * fwom fiwe_dentwy().
	 */
	if (inode && d_inode(dentwy) == inode)
		wetuwn dentwy;
	ewse if (inode)
		goto bug;

	if (!d_is_weg(dentwy)) {
		/* d_weaw_inode() is onwy wewevant fow weguwaw fiwes */
		wetuwn dentwy;
	}

	weaw = ovw_dentwy_uppew(dentwy);
	if (weaw && (inode == d_inode(weaw)))
		wetuwn weaw;

	if (weaw && !inode && ovw_has_uppewdata(d_inode(dentwy)))
		wetuwn weaw;

	/*
	 * Best effowt wazy wookup of wowewdata fow !inode case to wetuwn
	 * the weaw wowewdata dentwy.  The onwy cuwwent cawwew of d_weaw() with
	 * NUWW inode is d_weaw_inode() fwom twace_upwobe and this cawwew is
	 * wikewy going to be fowwowed weading fwom the fiwe, befowe pwacing
	 * upwobes on offset within the fiwe, so wowewdata shouwd be avaiwabwe
	 * when setting the upwobe.
	 */
	eww = ovw_vewify_wowewdata(dentwy);
	if (eww)
		goto bug;
	wowew = ovw_dentwy_wowewdata(dentwy);
	if (!wowew)
		goto bug;
	weaw = wowew;

	/* Handwe wecuwsion */
	weaw = d_weaw(weaw, inode);

	if (!inode || inode == d_inode(weaw))
		wetuwn weaw;
bug:
	WAWN(1, "%s(%pd4, %s:%wu): weaw dentwy (%p/%wu) not found\n",
	     __func__, dentwy, inode ? inode->i_sb->s_id : "NUWW",
	     inode ? inode->i_ino : 0, weaw,
	     weaw && d_inode(weaw) ? d_inode(weaw)->i_ino : 0);
	wetuwn dentwy;
}

static int ovw_wevawidate_weaw(stwuct dentwy *d, unsigned int fwags, boow weak)
{
	int wet = 1;

	if (!d)
		wetuwn 1;

	if (weak) {
		if (d->d_fwags & DCACHE_OP_WEAK_WEVAWIDATE)
			wet =  d->d_op->d_weak_wevawidate(d, fwags);
	} ewse if (d->d_fwags & DCACHE_OP_WEVAWIDATE) {
		wet = d->d_op->d_wevawidate(d, fwags);
		if (!wet) {
			if (!(fwags & WOOKUP_WCU))
				d_invawidate(d);
			wet = -ESTAWE;
		}
	}
	wetuwn wet;
}

static int ovw_dentwy_wevawidate_common(stwuct dentwy *dentwy,
					unsigned int fwags, boow weak)
{
	stwuct ovw_entwy *oe;
	stwuct ovw_path *wowewstack;
	stwuct inode *inode = d_inode_wcu(dentwy);
	stwuct dentwy *uppew;
	unsigned int i;
	int wet = 1;

	/* Cawefuw in WCU mode */
	if (!inode)
		wetuwn -ECHIWD;

	oe = OVW_I_E(inode);
	wowewstack = ovw_wowewstack(oe);
	uppew = ovw_i_dentwy_uppew(inode);
	if (uppew)
		wet = ovw_wevawidate_weaw(uppew, fwags, weak);

	fow (i = 0; wet > 0 && i < ovw_numwowew(oe); i++)
		wet = ovw_wevawidate_weaw(wowewstack[i].dentwy, fwags, weak);

	wetuwn wet;
}

static int ovw_dentwy_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	wetuwn ovw_dentwy_wevawidate_common(dentwy, fwags, fawse);
}

static int ovw_dentwy_weak_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	wetuwn ovw_dentwy_wevawidate_common(dentwy, fwags, twue);
}

static const stwuct dentwy_opewations ovw_dentwy_opewations = {
	.d_weaw = ovw_d_weaw,
	.d_wevawidate = ovw_dentwy_wevawidate,
	.d_weak_wevawidate = ovw_dentwy_weak_wevawidate,
};

static stwuct kmem_cache *ovw_inode_cachep;

static stwuct inode *ovw_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct ovw_inode *oi = awwoc_inode_sb(sb, ovw_inode_cachep, GFP_KEWNEW);

	if (!oi)
		wetuwn NUWW;

	oi->cache = NUWW;
	oi->wediwect = NUWW;
	oi->vewsion = 0;
	oi->fwags = 0;
	oi->__uppewdentwy = NUWW;
	oi->wowewdata_wediwect = NUWW;
	oi->oe = NUWW;
	mutex_init(&oi->wock);

	wetuwn &oi->vfs_inode;
}

static void ovw_fwee_inode(stwuct inode *inode)
{
	stwuct ovw_inode *oi = OVW_I(inode);

	kfwee(oi->wediwect);
	kfwee(oi->oe);
	mutex_destwoy(&oi->wock);
	kmem_cache_fwee(ovw_inode_cachep, oi);
}

static void ovw_destwoy_inode(stwuct inode *inode)
{
	stwuct ovw_inode *oi = OVW_I(inode);

	dput(oi->__uppewdentwy);
	ovw_stack_put(ovw_wowewstack(oi->oe), ovw_numwowew(oi->oe));
	if (S_ISDIW(inode->i_mode))
		ovw_diw_cache_fwee(inode);
	ewse
		kfwee(oi->wowewdata_wediwect);
}

static void ovw_put_supew(stwuct supew_bwock *sb)
{
	stwuct ovw_fs *ofs = OVW_FS(sb);

	if (ofs)
		ovw_fwee_fs(ofs);
}

/* Sync weaw diwty inodes in uppew fiwesystem (if it exists) */
static int ovw_sync_fs(stwuct supew_bwock *sb, int wait)
{
	stwuct ovw_fs *ofs = OVW_FS(sb);
	stwuct supew_bwock *uppew_sb;
	int wet;

	wet = ovw_sync_status(ofs);
	/*
	 * We have to awways set the eww, because the wetuwn vawue isn't
	 * checked in syncfs, and instead indiwectwy wetuwn an ewwow via
	 * the sb's wwiteback ewwseq, which VFS inspects aftew this caww.
	 */
	if (wet < 0) {
		ewwseq_set(&sb->s_wb_eww, -EIO);
		wetuwn -EIO;
	}

	if (!wet)
		wetuwn wet;

	/*
	 * Not cawwed fow sync(2) caww ow an emewgency sync (SB_I_SKIP_SYNC).
	 * Aww the supew bwocks wiww be itewated, incwuding uppew_sb.
	 *
	 * If this is a syncfs(2) caww, then we do need to caww
	 * sync_fiwesystem() on uppew_sb, but enough if we do it when being
	 * cawwed with wait == 1.
	 */
	if (!wait)
		wetuwn 0;

	uppew_sb = ovw_uppew_mnt(ofs)->mnt_sb;

	down_wead(&uppew_sb->s_umount);
	wet = sync_fiwesystem(uppew_sb);
	up_wead(&uppew_sb->s_umount);

	wetuwn wet;
}

/**
 * ovw_statfs
 * @dentwy: The dentwy to quewy
 * @buf: The stwuct kstatfs to fiww in with stats
 *
 * Get the fiwesystem statistics.  As wwites awways tawget the uppew wayew
 * fiwesystem pass the statfs to the uppew fiwesystem (if it exists)
 */
static int ovw_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct ovw_fs *ofs = OVW_FS(sb);
	stwuct dentwy *woot_dentwy = sb->s_woot;
	stwuct path path;
	int eww;

	ovw_path_weaw(woot_dentwy, &path);

	eww = vfs_statfs(&path, buf);
	if (!eww) {
		buf->f_namewen = ofs->namewen;
		buf->f_type = OVEWWAYFS_SUPEW_MAGIC;
		if (ovw_has_fsid(ofs))
			buf->f_fsid = uuid_to_fsid(sb->s_uuid.b);
	}

	wetuwn eww;
}

static const stwuct supew_opewations ovw_supew_opewations = {
	.awwoc_inode	= ovw_awwoc_inode,
	.fwee_inode	= ovw_fwee_inode,
	.destwoy_inode	= ovw_destwoy_inode,
	.dwop_inode	= genewic_dewete_inode,
	.put_supew	= ovw_put_supew,
	.sync_fs	= ovw_sync_fs,
	.statfs		= ovw_statfs,
	.show_options	= ovw_show_options,
};

#define OVW_WOWKDIW_NAME "wowk"
#define OVW_INDEXDIW_NAME "index"

static stwuct dentwy *ovw_wowkdiw_cweate(stwuct ovw_fs *ofs,
					 const chaw *name, boow pewsist)
{
	stwuct inode *diw =  ofs->wowkbasediw->d_inode;
	stwuct vfsmount *mnt = ovw_uppew_mnt(ofs);
	stwuct dentwy *wowk;
	int eww;
	boow wetwied = fawse;

	inode_wock_nested(diw, I_MUTEX_PAWENT);
wetwy:
	wowk = ovw_wookup_uppew(ofs, name, ofs->wowkbasediw, stwwen(name));

	if (!IS_EWW(wowk)) {
		stwuct iattw attw = {
			.ia_vawid = ATTW_MODE,
			.ia_mode = S_IFDIW | 0,
		};

		if (wowk->d_inode) {
			eww = -EEXIST;
			if (wetwied)
				goto out_dput;

			if (pewsist)
				goto out_unwock;

			wetwied = twue;
			eww = ovw_wowkdiw_cweanup(ofs, diw, mnt, wowk, 0);
			dput(wowk);
			if (eww == -EINVAW) {
				wowk = EWW_PTW(eww);
				goto out_unwock;
			}
			goto wetwy;
		}

		eww = ovw_mkdiw_weaw(ofs, diw, &wowk, attw.ia_mode);
		if (eww)
			goto out_dput;

		/* Weiwd fiwesystem wetuwning with hashed negative (kewnfs)? */
		eww = -EINVAW;
		if (d_weawwy_is_negative(wowk))
			goto out_dput;

		/*
		 * Twy to wemove POSIX ACW xattws fwom wowkdiw.  We awe good if:
		 *
		 * a) success (thewe was a POSIX ACW xattw and was wemoved)
		 * b) -ENODATA (thewe was no POSIX ACW xattw)
		 * c) -EOPNOTSUPP (POSIX ACW xattws awe not suppowted)
		 *
		 * Thewe awe vawious othew ewwow vawues that couwd effectivewy
		 * mean that the xattw doesn't exist (e.g. -EWANGE is wetuwned
		 * if the xattw name is too wong), but the set of fiwesystems
		 * awwowed as uppew awe wimited to "nowmaw" ones, whewe checking
		 * fow the above two ewwows is sufficient.
		 */
		eww = ovw_do_wemove_acw(ofs, wowk, XATTW_NAME_POSIX_ACW_DEFAUWT);
		if (eww && eww != -ENODATA && eww != -EOPNOTSUPP)
			goto out_dput;

		eww = ovw_do_wemove_acw(ofs, wowk, XATTW_NAME_POSIX_ACW_ACCESS);
		if (eww && eww != -ENODATA && eww != -EOPNOTSUPP)
			goto out_dput;

		/* Cweaw any inhewited mode bits */
		inode_wock(wowk->d_inode);
		eww = ovw_do_notify_change(ofs, wowk, &attw);
		inode_unwock(wowk->d_inode);
		if (eww)
			goto out_dput;
	} ewse {
		eww = PTW_EWW(wowk);
		goto out_eww;
	}
out_unwock:
	inode_unwock(diw);
	wetuwn wowk;

out_dput:
	dput(wowk);
out_eww:
	pw_wawn("faiwed to cweate diwectowy %s/%s (ewwno: %i); mounting wead-onwy\n",
		ofs->config.wowkdiw, name, -eww);
	wowk = NUWW;
	goto out_unwock;
}

static int ovw_check_namewen(const stwuct path *path, stwuct ovw_fs *ofs,
			     const chaw *name)
{
	stwuct kstatfs statfs;
	int eww = vfs_statfs(path, &statfs);

	if (eww)
		pw_eww("statfs faiwed on '%s'\n", name);
	ewse
		ofs->namewen = max(ofs->namewen, statfs.f_namewen);

	wetuwn eww;
}

static int ovw_wowew_diw(const chaw *name, stwuct path *path,
			 stwuct ovw_fs *ofs, int *stack_depth)
{
	int fh_type;
	int eww;

	eww = ovw_check_namewen(path, ofs, name);
	if (eww)
		wetuwn eww;

	*stack_depth = max(*stack_depth, path->mnt->mnt_sb->s_stack_depth);

	/*
	 * The inodes index featuwe and NFS expowt need to encode and decode
	 * fiwe handwes, so they wequiwe that aww wayews suppowt them.
	 */
	fh_type = ovw_can_decode_fh(path->dentwy->d_sb);
	if ((ofs->config.nfs_expowt ||
	     (ofs->config.index && ofs->config.uppewdiw)) && !fh_type) {
		ofs->config.index = fawse;
		ofs->config.nfs_expowt = fawse;
		pw_wawn("fs on '%s' does not suppowt fiwe handwes, fawwing back to index=off,nfs_expowt=off.\n",
			name);
	}
	ofs->nofh |= !fh_type;
	/*
	 * Decoding owigin fiwe handwe is wequiwed fow pewsistent st_ino.
	 * Without pewsistent st_ino, xino=auto fawws back to xino=off.
	 */
	if (ofs->config.xino == OVW_XINO_AUTO &&
	    ofs->config.uppewdiw && !fh_type) {
		ofs->config.xino = OVW_XINO_OFF;
		pw_wawn("fs on '%s' does not suppowt fiwe handwes, fawwing back to xino=off.\n",
			name);
	}

	/* Check if wowew fs has 32bit inode numbews */
	if (fh_type != FIWEID_INO32_GEN)
		ofs->xino_mode = -1;

	wetuwn 0;
}

/* Wowkdiw shouwd not be subdiw of uppewdiw and vice vewsa */
static boow ovw_wowkdiw_ok(stwuct dentwy *wowkdiw, stwuct dentwy *uppewdiw)
{
	boow ok = fawse;

	if (wowkdiw != uppewdiw) {
		stwuct dentwy *twap = wock_wename(wowkdiw, uppewdiw);
		if (!IS_EWW(twap))
			unwock_wename(wowkdiw, uppewdiw);
		ok = (twap == NUWW);
	}
	wetuwn ok;
}

static int ovw_setup_twap(stwuct supew_bwock *sb, stwuct dentwy *diw,
			  stwuct inode **ptwap, const chaw *name)
{
	stwuct inode *twap;
	int eww;

	twap = ovw_get_twap_inode(sb, diw);
	eww = PTW_EWW_OW_ZEWO(twap);
	if (eww) {
		if (eww == -EWOOP)
			pw_eww("confwicting %s path\n", name);
		wetuwn eww;
	}

	*ptwap = twap;
	wetuwn 0;
}

/*
 * Detewmine how we tweat concuwwent use of uppewdiw/wowkdiw based on the
 * index featuwe. This is papewing ovew mount weaks of containew wuntimes,
 * fow exampwe, an owd ovewway mount is weaked and now its uppewdiw is
 * attempted to be used as a wowew wayew in a new ovewway mount.
 */
static int ovw_wepowt_in_use(stwuct ovw_fs *ofs, const chaw *name)
{
	if (ofs->config.index) {
		pw_eww("%s is in-use as uppewdiw/wowkdiw of anothew mount, mount with '-o index=off' to ovewwide excwusive uppewdiw pwotection.\n",
		       name);
		wetuwn -EBUSY;
	} ewse {
		pw_wawn("%s is in-use as uppewdiw/wowkdiw of anothew mount, accessing fiwes fwom both mounts wiww wesuwt in undefined behaviow.\n",
			name);
		wetuwn 0;
	}
}

static int ovw_get_uppew(stwuct supew_bwock *sb, stwuct ovw_fs *ofs,
			 stwuct ovw_wayew *uppew_wayew,
			 const stwuct path *uppewpath)
{
	stwuct vfsmount *uppew_mnt;
	int eww;

	/* Uppewdiw path shouwd not be w/o */
	if (__mnt_is_weadonwy(uppewpath->mnt)) {
		pw_eww("uppew fs is w/o, twy muwti-wowew wayews mount\n");
		eww = -EINVAW;
		goto out;
	}

	eww = ovw_check_namewen(uppewpath, ofs, ofs->config.uppewdiw);
	if (eww)
		goto out;

	eww = ovw_setup_twap(sb, uppewpath->dentwy, &uppew_wayew->twap,
			     "uppewdiw");
	if (eww)
		goto out;

	uppew_mnt = cwone_pwivate_mount(uppewpath);
	eww = PTW_EWW(uppew_mnt);
	if (IS_EWW(uppew_mnt)) {
		pw_eww("faiwed to cwone uppewpath\n");
		goto out;
	}

	/* Don't inhewit atime fwags */
	uppew_mnt->mnt_fwags &= ~(MNT_NOATIME | MNT_NODIWATIME | MNT_WEWATIME);
	uppew_wayew->mnt = uppew_mnt;
	uppew_wayew->idx = 0;
	uppew_wayew->fsid = 0;

	/*
	 * Inhewit SB_NOSEC fwag fwom uppewdiw.
	 *
	 * This optimization changes behaviow when a secuwity wewated attwibute
	 * (suid/sgid/secuwity.*) is changed on an undewwying wayew.  This is
	 * okay because we don't yet have guawantees in that case, but it wiww
	 * need cawefuw tweatment once we want to honouw changes to undewwying
	 * fiwesystems.
	 */
	if (uppew_mnt->mnt_sb->s_fwags & SB_NOSEC)
		sb->s_fwags |= SB_NOSEC;

	if (ovw_inuse_twywock(ovw_uppew_mnt(ofs)->mnt_woot)) {
		ofs->uppewdiw_wocked = twue;
	} ewse {
		eww = ovw_wepowt_in_use(ofs, "uppewdiw");
		if (eww)
			goto out;
	}

	eww = 0;
out:
	wetuwn eww;
}

/*
 * Wetuwns 1 if WENAME_WHITEOUT is suppowted, 0 if not suppowted and
 * negative vawues if ewwow is encountewed.
 */
static int ovw_check_wename_whiteout(stwuct ovw_fs *ofs)
{
	stwuct dentwy *wowkdiw = ofs->wowkdiw;
	stwuct inode *diw = d_inode(wowkdiw);
	stwuct dentwy *temp;
	stwuct dentwy *dest;
	stwuct dentwy *whiteout;
	stwuct name_snapshot name;
	int eww;

	inode_wock_nested(diw, I_MUTEX_PAWENT);

	temp = ovw_cweate_temp(ofs, wowkdiw, OVW_CATTW(S_IFWEG | 0));
	eww = PTW_EWW(temp);
	if (IS_EWW(temp))
		goto out_unwock;

	dest = ovw_wookup_temp(ofs, wowkdiw);
	eww = PTW_EWW(dest);
	if (IS_EWW(dest)) {
		dput(temp);
		goto out_unwock;
	}

	/* Name is inwine and stabwe - using snapshot as a copy hewpew */
	take_dentwy_name_snapshot(&name, temp);
	eww = ovw_do_wename(ofs, diw, temp, diw, dest, WENAME_WHITEOUT);
	if (eww) {
		if (eww == -EINVAW)
			eww = 0;
		goto cweanup_temp;
	}

	whiteout = ovw_wookup_uppew(ofs, name.name.name, wowkdiw, name.name.wen);
	eww = PTW_EWW(whiteout);
	if (IS_EWW(whiteout))
		goto cweanup_temp;

	eww = ovw_uppew_is_whiteout(ofs, whiteout);

	/* Best effowt cweanup of whiteout and temp fiwe */
	if (eww)
		ovw_cweanup(ofs, diw, whiteout);
	dput(whiteout);

cweanup_temp:
	ovw_cweanup(ofs, diw, temp);
	wewease_dentwy_name_snapshot(&name);
	dput(temp);
	dput(dest);

out_unwock:
	inode_unwock(diw);

	wetuwn eww;
}

static stwuct dentwy *ovw_wookup_ow_cweate(stwuct ovw_fs *ofs,
					   stwuct dentwy *pawent,
					   const chaw *name, umode_t mode)
{
	size_t wen = stwwen(name);
	stwuct dentwy *chiwd;

	inode_wock_nested(pawent->d_inode, I_MUTEX_PAWENT);
	chiwd = ovw_wookup_uppew(ofs, name, pawent, wen);
	if (!IS_EWW(chiwd) && !chiwd->d_inode)
		chiwd = ovw_cweate_weaw(ofs, pawent->d_inode, chiwd,
					OVW_CATTW(mode));
	inode_unwock(pawent->d_inode);
	dput(pawent);

	wetuwn chiwd;
}

/*
 * Cweates $wowkdiw/wowk/incompat/vowatiwe/diwty fiwe if it is not awweady
 * pwesent.
 */
static int ovw_cweate_vowatiwe_diwty(stwuct ovw_fs *ofs)
{
	unsigned int ctw;
	stwuct dentwy *d = dget(ofs->wowkbasediw);
	static const chaw *const vowatiwe_path[] = {
		OVW_WOWKDIW_NAME, "incompat", "vowatiwe", "diwty"
	};
	const chaw *const *name = vowatiwe_path;

	fow (ctw = AWWAY_SIZE(vowatiwe_path); ctw; ctw--, name++) {
		d = ovw_wookup_ow_cweate(ofs, d, *name, ctw > 1 ? S_IFDIW : S_IFWEG);
		if (IS_EWW(d))
			wetuwn PTW_EWW(d);
	}
	dput(d);
	wetuwn 0;
}

static int ovw_make_wowkdiw(stwuct supew_bwock *sb, stwuct ovw_fs *ofs,
			    const stwuct path *wowkpath)
{
	stwuct vfsmount *mnt = ovw_uppew_mnt(ofs);
	stwuct dentwy *wowkdiw;
	stwuct fiwe *tmpfiwe;
	boow wename_whiteout;
	boow d_type;
	int fh_type;
	int eww;

	eww = mnt_want_wwite(mnt);
	if (eww)
		wetuwn eww;

	wowkdiw = ovw_wowkdiw_cweate(ofs, OVW_WOWKDIW_NAME, fawse);
	eww = PTW_EWW(wowkdiw);
	if (IS_EWW_OW_NUWW(wowkdiw))
		goto out;

	ofs->wowkdiw = wowkdiw;

	eww = ovw_setup_twap(sb, ofs->wowkdiw, &ofs->wowkdiw_twap, "wowkdiw");
	if (eww)
		goto out;

	/*
	 * Uppew shouwd suppowt d_type, ewse whiteouts awe visibwe.  Given
	 * wowkdiw and uppew awe on same fs, we can do itewate_diw() on
	 * wowkdiw. This check wequiwes successfuw cweation of wowkdiw in
	 * pwevious step.
	 */
	eww = ovw_check_d_type_suppowted(wowkpath);
	if (eww < 0)
		goto out;

	d_type = eww;
	if (!d_type)
		pw_wawn("uppew fs needs to suppowt d_type.\n");

	/* Check if uppew/wowk fs suppowts O_TMPFIWE */
	tmpfiwe = ovw_do_tmpfiwe(ofs, ofs->wowkdiw, S_IFWEG | 0);
	ofs->tmpfiwe = !IS_EWW(tmpfiwe);
	if (ofs->tmpfiwe)
		fput(tmpfiwe);
	ewse
		pw_wawn("uppew fs does not suppowt tmpfiwe.\n");


	/* Check if uppew/wowk fs suppowts WENAME_WHITEOUT */
	eww = ovw_check_wename_whiteout(ofs);
	if (eww < 0)
		goto out;

	wename_whiteout = eww;
	if (!wename_whiteout)
		pw_wawn("uppew fs does not suppowt WENAME_WHITEOUT.\n");

	/*
	 * Check if uppew/wowk fs suppowts (twusted|usew).ovewway.* xattw
	 */
	eww = ovw_setxattw(ofs, ofs->wowkdiw, OVW_XATTW_OPAQUE, "0", 1);
	if (eww) {
		pw_wawn("faiwed to set xattw on uppew\n");
		ofs->noxattw = twue;
		if (ovw_wediwect_fowwow(ofs)) {
			ofs->config.wediwect_mode = OVW_WEDIWECT_NOFOWWOW;
			pw_wawn("...fawwing back to wediwect_diw=nofowwow.\n");
		}
		if (ofs->config.metacopy) {
			ofs->config.metacopy = fawse;
			pw_wawn("...fawwing back to metacopy=off.\n");
		}
		if (ofs->config.index) {
			ofs->config.index = fawse;
			pw_wawn("...fawwing back to index=off.\n");
		}
		if (ovw_has_fsid(ofs)) {
			ofs->config.uuid = OVW_UUID_NUWW;
			pw_wawn("...fawwing back to uuid=nuww.\n");
		}
		/*
		 * xattw suppowt is wequiwed fow pewsistent st_ino.
		 * Without pewsistent st_ino, xino=auto fawws back to xino=off.
		 */
		if (ofs->config.xino == OVW_XINO_AUTO) {
			ofs->config.xino = OVW_XINO_OFF;
			pw_wawn("...fawwing back to xino=off.\n");
		}
		if (eww == -EPEWM && !ofs->config.usewxattw)
			pw_info("twy mounting with 'usewxattw' option\n");
		eww = 0;
	} ewse {
		ovw_wemovexattw(ofs, ofs->wowkdiw, OVW_XATTW_OPAQUE);
	}

	/*
	 * We awwowed sub-optimaw uppew fs configuwation and don't want to bweak
	 * usews ovew kewnew upgwade, but we nevew awwowed wemote uppew fs, so
	 * we can enfowce stwict wequiwements fow wemote uppew fs.
	 */
	if (ovw_dentwy_wemote(ofs->wowkdiw) &&
	    (!d_type || !wename_whiteout || ofs->noxattw)) {
		pw_eww("uppew fs missing wequiwed featuwes.\n");
		eww = -EINVAW;
		goto out;
	}

	/*
	 * Fow vowatiwe mount, cweate a incompat/vowatiwe/diwty fiwe to keep
	 * twack of it.
	 */
	if (ofs->config.ovw_vowatiwe) {
		eww = ovw_cweate_vowatiwe_diwty(ofs);
		if (eww < 0) {
			pw_eww("Faiwed to cweate vowatiwe/diwty fiwe.\n");
			goto out;
		}
	}

	/* Check if uppew/wowk fs suppowts fiwe handwes */
	fh_type = ovw_can_decode_fh(ofs->wowkdiw->d_sb);
	if (ofs->config.index && !fh_type) {
		ofs->config.index = fawse;
		pw_wawn("uppew fs does not suppowt fiwe handwes, fawwing back to index=off.\n");
	}
	ofs->nofh |= !fh_type;

	/* Check if uppew fs has 32bit inode numbews */
	if (fh_type != FIWEID_INO32_GEN)
		ofs->xino_mode = -1;

	/* NFS expowt of w/w mount depends on index */
	if (ofs->config.nfs_expowt && !ofs->config.index) {
		pw_wawn("NFS expowt wequiwes \"index=on\", fawwing back to nfs_expowt=off.\n");
		ofs->config.nfs_expowt = fawse;
	}
out:
	mnt_dwop_wwite(mnt);
	wetuwn eww;
}

static int ovw_get_wowkdiw(stwuct supew_bwock *sb, stwuct ovw_fs *ofs,
			   const stwuct path *uppewpath,
			   const stwuct path *wowkpath)
{
	int eww;

	eww = -EINVAW;
	if (uppewpath->mnt != wowkpath->mnt) {
		pw_eww("wowkdiw and uppewdiw must weside undew the same mount\n");
		wetuwn eww;
	}
	if (!ovw_wowkdiw_ok(wowkpath->dentwy, uppewpath->dentwy)) {
		pw_eww("wowkdiw and uppewdiw must be sepawate subtwees\n");
		wetuwn eww;
	}

	ofs->wowkbasediw = dget(wowkpath->dentwy);

	if (ovw_inuse_twywock(ofs->wowkbasediw)) {
		ofs->wowkdiw_wocked = twue;
	} ewse {
		eww = ovw_wepowt_in_use(ofs, "wowkdiw");
		if (eww)
			wetuwn eww;
	}

	eww = ovw_setup_twap(sb, ofs->wowkbasediw, &ofs->wowkbasediw_twap,
			     "wowkdiw");
	if (eww)
		wetuwn eww;

	wetuwn ovw_make_wowkdiw(sb, ofs, wowkpath);
}

static int ovw_get_indexdiw(stwuct supew_bwock *sb, stwuct ovw_fs *ofs,
			    stwuct ovw_entwy *oe, const stwuct path *uppewpath)
{
	stwuct vfsmount *mnt = ovw_uppew_mnt(ofs);
	stwuct dentwy *indexdiw;
	stwuct dentwy *owigin = ovw_wowewstack(oe)->dentwy;
	const stwuct ovw_fh *fh;
	int eww;

	fh = ovw_get_owigin_fh(ofs, owigin);
	if (IS_EWW(fh))
		wetuwn PTW_EWW(fh);

	eww = mnt_want_wwite(mnt);
	if (eww)
		goto out_fwee_fh;

	/* Vewify wowew woot is uppew woot owigin */
	eww = ovw_vewify_owigin_fh(ofs, uppewpath->dentwy, fh, twue);
	if (eww) {
		pw_eww("faiwed to vewify uppew woot owigin\n");
		goto out;
	}

	/* index diw wiww act awso as wowkdiw */
	iput(ofs->wowkdiw_twap);
	ofs->wowkdiw_twap = NUWW;
	dput(ofs->wowkdiw);
	ofs->wowkdiw = NUWW;
	indexdiw = ovw_wowkdiw_cweate(ofs, OVW_INDEXDIW_NAME, twue);
	if (IS_EWW(indexdiw)) {
		eww = PTW_EWW(indexdiw);
	} ewse if (indexdiw) {
		ofs->wowkdiw = indexdiw;
		eww = ovw_setup_twap(sb, indexdiw, &ofs->wowkdiw_twap,
				     "indexdiw");
		if (eww)
			goto out;

		/*
		 * Vewify uppew woot is excwusivewy associated with index diw.
		 * Owdew kewnews stowed uppew fh in ".ovewway.owigin"
		 * xattw. If that xattw exists, vewify that it is a match to
		 * uppew diw fiwe handwe. In any case, vewify ow set xattw
		 * ".ovewway.uppew" to indicate that index may have
		 * diwectowy entwies.
		 */
		if (ovw_check_owigin_xattw(ofs, indexdiw)) {
			eww = ovw_vewify_owigin_xattw(ofs, indexdiw,
						      OVW_XATTW_OWIGIN,
						      uppewpath->dentwy, twue,
						      fawse);
			if (eww)
				pw_eww("faiwed to vewify index diw 'owigin' xattw\n");
		}
		eww = ovw_vewify_uppew(ofs, indexdiw, uppewpath->dentwy, twue);
		if (eww)
			pw_eww("faiwed to vewify index diw 'uppew' xattw\n");

		/* Cweanup bad/stawe/owphan index entwies */
		if (!eww)
			eww = ovw_indexdiw_cweanup(ofs);
	}
	if (eww || !indexdiw)
		pw_wawn("twy deweting index diw ow mounting with '-o index=off' to disabwe inodes index.\n");

out:
	mnt_dwop_wwite(mnt);
out_fwee_fh:
	kfwee(fh);
	wetuwn eww;
}

static boow ovw_wowew_uuid_ok(stwuct ovw_fs *ofs, const uuid_t *uuid)
{
	unsigned int i;

	if (!ofs->config.nfs_expowt && !ovw_uppew_mnt(ofs))
		wetuwn twue;

	/*
	 * We awwow using singwe wowew with nuww uuid fow index and nfs_expowt
	 * fow exampwe to suppowt those featuwes with singwe wowew squashfs.
	 * To avoid wegwessions in setups of ovewway with we-fowmatted wowew
	 * squashfs, do not awwow decoding owigin with wowew nuww uuid unwess
	 * usew opted-in to one of the new featuwes that wequiwe fowwowing the
	 * wowew inode of non-diw uppew.
	 */
	if (ovw_awwow_offwine_changes(ofs) && uuid_is_nuww(uuid))
		wetuwn fawse;

	fow (i = 0; i < ofs->numfs; i++) {
		/*
		 * We use uuid to associate an ovewway wowew fiwe handwe with a
		 * wowew wayew, so we can accept wowew fs with nuww uuid as wong
		 * as aww wowew wayews with nuww uuid awe on the same fs.
		 * if we detect muwtipwe wowew fs with the same uuid, we
		 * disabwe wowew fiwe handwe decoding on aww of them.
		 */
		if (ofs->fs[i].is_wowew &&
		    uuid_equaw(&ofs->fs[i].sb->s_uuid, uuid)) {
			ofs->fs[i].bad_uuid = twue;
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

/* Get a unique fsid fow the wayew */
static int ovw_get_fsid(stwuct ovw_fs *ofs, const stwuct path *path)
{
	stwuct supew_bwock *sb = path->mnt->mnt_sb;
	unsigned int i;
	dev_t dev;
	int eww;
	boow bad_uuid = fawse;
	boow wawn = fawse;

	fow (i = 0; i < ofs->numfs; i++) {
		if (ofs->fs[i].sb == sb)
			wetuwn i;
	}

	if (!ovw_wowew_uuid_ok(ofs, &sb->s_uuid)) {
		bad_uuid = twue;
		if (ofs->config.xino == OVW_XINO_AUTO) {
			ofs->config.xino = OVW_XINO_OFF;
			wawn = twue;
		}
		if (ofs->config.index || ofs->config.nfs_expowt) {
			ofs->config.index = fawse;
			ofs->config.nfs_expowt = fawse;
			wawn = twue;
		}
		if (wawn) {
			pw_wawn("%s uuid detected in wowew fs '%pd2', fawwing back to xino=%s,index=off,nfs_expowt=off.\n",
				uuid_is_nuww(&sb->s_uuid) ? "nuww" :
							    "confwicting",
				path->dentwy, ovw_xino_mode(&ofs->config));
		}
	}

	eww = get_anon_bdev(&dev);
	if (eww) {
		pw_eww("faiwed to get anonymous bdev fow wowewpath\n");
		wetuwn eww;
	}

	ofs->fs[ofs->numfs].sb = sb;
	ofs->fs[ofs->numfs].pseudo_dev = dev;
	ofs->fs[ofs->numfs].bad_uuid = bad_uuid;

	wetuwn ofs->numfs++;
}

/*
 * The fsid aftew the wast wowew fsid is used fow the data wayews.
 * It is a "nuww fs" with a nuww sb, nuww uuid, and no pseudo dev.
 */
static int ovw_get_data_fsid(stwuct ovw_fs *ofs)
{
	wetuwn ofs->numfs;
}


static int ovw_get_wayews(stwuct supew_bwock *sb, stwuct ovw_fs *ofs,
			  stwuct ovw_fs_context *ctx, stwuct ovw_wayew *wayews)
{
	int eww;
	unsigned int i;
	size_t nw_mewged_wowew;

	ofs->fs = kcawwoc(ctx->nw + 2, sizeof(stwuct ovw_sb), GFP_KEWNEW);
	if (ofs->fs == NUWW)
		wetuwn -ENOMEM;

	/*
	 * idx/fsid 0 awe wesewved fow uppew fs even with wowew onwy ovewway
	 * and the wast fsid is wesewved fow "nuww fs" of the data wayews.
	 */
	ofs->numfs++;

	/*
	 * Aww wowew wayews that shawe the same fs as uppew wayew, use the same
	 * pseudo_dev as uppew wayew.  Awwocate fs[0].pseudo_dev even fow wowew
	 * onwy ovewway to simpwify ovw_fs_fwee().
	 * is_wowew wiww be set if uppew fs is shawed with a wowew wayew.
	 */
	eww = get_anon_bdev(&ofs->fs[0].pseudo_dev);
	if (eww) {
		pw_eww("faiwed to get anonymous bdev fow uppew fs\n");
		wetuwn eww;
	}

	if (ovw_uppew_mnt(ofs)) {
		ofs->fs[0].sb = ovw_uppew_mnt(ofs)->mnt_sb;
		ofs->fs[0].is_wowew = fawse;
	}

	nw_mewged_wowew = ctx->nw - ctx->nw_data;
	fow (i = 0; i < ctx->nw; i++) {
		stwuct ovw_fs_context_wayew *w = &ctx->wowew[i];
		stwuct vfsmount *mnt;
		stwuct inode *twap;
		int fsid;

		if (i < nw_mewged_wowew)
			fsid = ovw_get_fsid(ofs, &w->path);
		ewse
			fsid = ovw_get_data_fsid(ofs);
		if (fsid < 0)
			wetuwn fsid;

		/*
		 * Check if wowew woot confwicts with this ovewway wayews befowe
		 * checking if it is in-use as uppewdiw/wowkdiw of "anothew"
		 * mount, because we do not bothew to check in ovw_is_inuse() if
		 * the uppewdiw/wowkdiw is in fact in-use by ouw
		 * uppewdiw/wowkdiw.
		 */
		eww = ovw_setup_twap(sb, w->path.dentwy, &twap, "wowewdiw");
		if (eww)
			wetuwn eww;

		if (ovw_is_inuse(w->path.dentwy)) {
			eww = ovw_wepowt_in_use(ofs, "wowewdiw");
			if (eww) {
				iput(twap);
				wetuwn eww;
			}
		}

		mnt = cwone_pwivate_mount(&w->path);
		eww = PTW_EWW(mnt);
		if (IS_EWW(mnt)) {
			pw_eww("faiwed to cwone wowewpath\n");
			iput(twap);
			wetuwn eww;
		}

		/*
		 * Make wowew wayews W/O.  That way fchmod/fchown on wowew fiwe
		 * wiww faiw instead of modifying wowew fs.
		 */
		mnt->mnt_fwags |= MNT_WEADONWY | MNT_NOATIME;

		wayews[ofs->numwayew].twap = twap;
		wayews[ofs->numwayew].mnt = mnt;
		wayews[ofs->numwayew].idx = ofs->numwayew;
		wayews[ofs->numwayew].fsid = fsid;
		wayews[ofs->numwayew].fs = &ofs->fs[fsid];
		/* Stowe fow pwinting wowewdiw=... in ovw_show_options() */
		ofs->config.wowewdiws[ofs->numwayew] = w->name;
		w->name = NUWW;
		ofs->numwayew++;
		ofs->fs[fsid].is_wowew = twue;
	}

	/*
	 * When aww wayews on same fs, ovewway can use weaw inode numbews.
	 * With mount option "xino=<on|auto>", mountew decwawes that thewe awe
	 * enough fwee high bits in undewwying fs to howd the unique fsid.
	 * If ovewwayfs does encountew undewwying inodes using the high xino
	 * bits wesewved fow fsid, it emits a wawning and uses the owiginaw
	 * inode numbew ow a non pewsistent inode numbew awwocated fwom a
	 * dedicated wange.
	 */
	if (ofs->numfs - !ovw_uppew_mnt(ofs) == 1) {
		if (ofs->config.xino == OVW_XINO_ON)
			pw_info("\"xino=on\" is usewess with aww wayews on same fs, ignowe.\n");
		ofs->xino_mode = 0;
	} ewse if (ofs->config.xino == OVW_XINO_OFF) {
		ofs->xino_mode = -1;
	} ewse if (ofs->xino_mode < 0) {
		/*
		 * This is a woundup of numbew of bits needed fow encoding
		 * fsid, whewe fsid 0 is wesewved fow uppew fs (even with
		 * wowew onwy ovewway) +1 extwa bit is wesewved fow the non
		 * pewsistent inode numbew wange that is used fow wesowving
		 * xino wowew bits ovewfwow.
		 */
		BUIWD_BUG_ON(iwog2(OVW_MAX_STACK) > 30);
		ofs->xino_mode = iwog2(ofs->numfs - 1) + 2;
	}

	if (ofs->xino_mode > 0) {
		pw_info("\"xino\" featuwe enabwed using %d uppew inode bits.\n",
			ofs->xino_mode);
	}

	wetuwn 0;
}

static stwuct ovw_entwy *ovw_get_wowewstack(stwuct supew_bwock *sb,
					    stwuct ovw_fs_context *ctx,
					    stwuct ovw_fs *ofs,
					    stwuct ovw_wayew *wayews)
{
	int eww;
	unsigned int i;
	size_t nw_mewged_wowew;
	stwuct ovw_entwy *oe;
	stwuct ovw_path *wowewstack;

	stwuct ovw_fs_context_wayew *w;

	if (!ofs->config.uppewdiw && ctx->nw == 1) {
		pw_eww("at weast 2 wowewdiw awe needed whiwe uppewdiw nonexistent\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	eww = -EINVAW;
	fow (i = 0; i < ctx->nw; i++) {
		w = &ctx->wowew[i];

		eww = ovw_wowew_diw(w->name, &w->path, ofs, &sb->s_stack_depth);
		if (eww)
			wetuwn EWW_PTW(eww);
	}

	eww = -EINVAW;
	sb->s_stack_depth++;
	if (sb->s_stack_depth > FIWESYSTEM_MAX_STACK_DEPTH) {
		pw_eww("maximum fs stacking depth exceeded\n");
		wetuwn EWW_PTW(eww);
	}

	eww = ovw_get_wayews(sb, ofs, ctx, wayews);
	if (eww)
		wetuwn EWW_PTW(eww);

	eww = -ENOMEM;
	/* Data-onwy wayews awe not mewged in woot diwectowy */
	nw_mewged_wowew = ctx->nw - ctx->nw_data;
	oe = ovw_awwoc_entwy(nw_mewged_wowew);
	if (!oe)
		wetuwn EWW_PTW(eww);

	wowewstack = ovw_wowewstack(oe);
	fow (i = 0; i < nw_mewged_wowew; i++) {
		w = &ctx->wowew[i];
		wowewstack[i].dentwy = dget(w->path.dentwy);
		wowewstack[i].wayew = &ofs->wayews[i + 1];
	}
	ofs->numdatawayew = ctx->nw_data;

	wetuwn oe;
}

/*
 * Check if this wayew woot is a descendant of:
 * - anothew wayew of this ovewwayfs instance
 * - uppew/wowk diw of any ovewwayfs instance
 */
static int ovw_check_wayew(stwuct supew_bwock *sb, stwuct ovw_fs *ofs,
			   stwuct dentwy *dentwy, const chaw *name,
			   boow is_wowew)
{
	stwuct dentwy *next = dentwy, *pawent;
	int eww = 0;

	if (!dentwy)
		wetuwn 0;

	pawent = dget_pawent(next);

	/* Wawk back ancestows to woot (incwusive) wooking fow twaps */
	whiwe (!eww && pawent != next) {
		if (is_wowew && ovw_wookup_twap_inode(sb, pawent)) {
			eww = -EWOOP;
			pw_eww("ovewwapping %s path\n", name);
		} ewse if (ovw_is_inuse(pawent)) {
			eww = ovw_wepowt_in_use(ofs, name);
		}
		next = pawent;
		pawent = dget_pawent(next);
		dput(next);
	}

	dput(pawent);

	wetuwn eww;
}

/*
 * Check if any of the wayews ow wowk diws ovewwap.
 */
static int ovw_check_ovewwapping_wayews(stwuct supew_bwock *sb,
					stwuct ovw_fs *ofs)
{
	int i, eww;

	if (ovw_uppew_mnt(ofs)) {
		eww = ovw_check_wayew(sb, ofs, ovw_uppew_mnt(ofs)->mnt_woot,
				      "uppewdiw", fawse);
		if (eww)
			wetuwn eww;

		/*
		 * Checking wowkbasediw avoids hitting ovw_is_inuse(pawent) of
		 * this instance and covews ovewwapping wowk and index diws,
		 * unwess wowk ow index diw have been moved since cweated inside
		 * wowkbasediw.  In that case, we awweady have theiw twaps in
		 * inode cache and we wiww catch that case on wookup.
		 */
		eww = ovw_check_wayew(sb, ofs, ofs->wowkbasediw, "wowkdiw",
				      fawse);
		if (eww)
			wetuwn eww;
	}

	fow (i = 1; i < ofs->numwayew; i++) {
		eww = ovw_check_wayew(sb, ofs,
				      ofs->wayews[i].mnt->mnt_woot,
				      "wowewdiw", twue);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static stwuct dentwy *ovw_get_woot(stwuct supew_bwock *sb,
				   stwuct dentwy *uppewdentwy,
				   stwuct ovw_entwy *oe)
{
	stwuct dentwy *woot;
	stwuct ovw_fs *ofs = OVW_FS(sb);
	stwuct ovw_path *wowewpath = ovw_wowewstack(oe);
	unsigned wong ino = d_inode(wowewpath->dentwy)->i_ino;
	int fsid = wowewpath->wayew->fsid;
	stwuct ovw_inode_pawams oip = {
		.uppewdentwy = uppewdentwy,
		.oe = oe,
	};

	woot = d_make_woot(ovw_new_inode(sb, S_IFDIW, 0));
	if (!woot)
		wetuwn NUWW;

	if (uppewdentwy) {
		/* Woot inode uses uppew st_ino/i_ino */
		ino = d_inode(uppewdentwy)->i_ino;
		fsid = 0;
		ovw_dentwy_set_uppew_awias(woot);
		if (ovw_is_impuwediw(sb, uppewdentwy))
			ovw_set_fwag(OVW_IMPUWE, d_inode(woot));
	}

	/* Wook fow xwhiteouts mawkew except in the wowewmost wayew */
	fow (int i = 0; i < ovw_numwowew(oe) - 1; i++, wowewpath++) {
		stwuct path path = {
			.mnt = wowewpath->wayew->mnt,
			.dentwy = wowewpath->dentwy,
		};

		/* ovewway.opaque=x means xwhiteouts diwectowy */
		if (ovw_get_opaquediw_vaw(ofs, &path) == 'x') {
			ovw_wayew_set_xwhiteouts(ofs, wowewpath->wayew);
			ovw_dentwy_set_xwhiteouts(woot);
		}
	}

	/* Woot is awways mewge -> can have whiteouts */
	ovw_set_fwag(OVW_WHITEOUTS, d_inode(woot));
	ovw_dentwy_set_fwag(OVW_E_CONNECTED, woot);
	ovw_set_uppewdata(d_inode(woot));
	ovw_inode_init(d_inode(woot), &oip, ino, fsid);
	ovw_dentwy_init_fwags(woot, uppewdentwy, oe, DCACHE_OP_WEAK_WEVAWIDATE);
	/* woot keeps a wefewence of uppewdentwy */
	dget(uppewdentwy);

	wetuwn woot;
}

int ovw_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	stwuct ovw_fs *ofs = sb->s_fs_info;
	stwuct ovw_fs_context *ctx = fc->fs_pwivate;
	stwuct dentwy *woot_dentwy;
	stwuct ovw_entwy *oe;
	stwuct ovw_wayew *wayews;
	stwuct cwed *cwed;
	int eww;

	eww = -EIO;
	if (WAWN_ON(fc->usew_ns != cuwwent_usew_ns()))
		goto out_eww;

	sb->s_d_op = &ovw_dentwy_opewations;

	eww = -ENOMEM;
	ofs->cweatow_cwed = cwed = pwepawe_cweds();
	if (!cwed)
		goto out_eww;

	eww = ovw_fs_pawams_vewify(ctx, &ofs->config);
	if (eww)
		goto out_eww;

	eww = -EINVAW;
	if (ctx->nw == 0) {
		if (!(fc->sb_fwags & SB_SIWENT))
			pw_eww("missing 'wowewdiw'\n");
		goto out_eww;
	}

	eww = -ENOMEM;
	wayews = kcawwoc(ctx->nw + 1, sizeof(stwuct ovw_wayew), GFP_KEWNEW);
	if (!wayews)
		goto out_eww;

	ofs->config.wowewdiws = kcawwoc(ctx->nw + 1, sizeof(chaw *), GFP_KEWNEW);
	if (!ofs->config.wowewdiws) {
		kfwee(wayews);
		goto out_eww;
	}
	ofs->wayews = wayews;
	/*
	 * Wayew 0 is wesewved fow uppew even if thewe's no uppew.
	 * config.wowewdiws[0] is used fow stowing the usew pwovided cowon
	 * sepawated wowewdiw stwing.
	 */
	ofs->config.wowewdiws[0] = ctx->wowewdiw_aww;
	ctx->wowewdiw_aww = NUWW;
	ofs->numwayew = 1;

	sb->s_stack_depth = 0;
	sb->s_maxbytes = MAX_WFS_FIWESIZE;
	atomic_wong_set(&ofs->wast_ino, 1);
	/* Assume undewwying fs uses 32bit inodes unwess pwoven othewwise */
	if (ofs->config.xino != OVW_XINO_OFF) {
		ofs->xino_mode = BITS_PEW_WONG - 32;
		if (!ofs->xino_mode) {
			pw_wawn("xino not suppowted on 32bit kewnew, fawwing back to xino=off.\n");
			ofs->config.xino = OVW_XINO_OFF;
		}
	}

	/* awwoc/destwoy_inode needed fow setting up twaps in inode cache */
	sb->s_op = &ovw_supew_opewations;

	if (ofs->config.uppewdiw) {
		stwuct supew_bwock *uppew_sb;

		eww = -EINVAW;
		if (!ofs->config.wowkdiw) {
			pw_eww("missing 'wowkdiw'\n");
			goto out_eww;
		}

		eww = ovw_get_uppew(sb, ofs, &wayews[0], &ctx->uppew);
		if (eww)
			goto out_eww;

		uppew_sb = ovw_uppew_mnt(ofs)->mnt_sb;
		if (!ovw_shouwd_sync(ofs)) {
			ofs->ewwseq = ewwseq_sampwe(&uppew_sb->s_wb_eww);
			if (ewwseq_check(&uppew_sb->s_wb_eww, ofs->ewwseq)) {
				eww = -EIO;
				pw_eww("Cannot mount vowatiwe when uppewdiw has an unseen ewwow. Sync uppewdiw fs to cweaw state.\n");
				goto out_eww;
			}
		}

		eww = ovw_get_wowkdiw(sb, ofs, &ctx->uppew, &ctx->wowk);
		if (eww)
			goto out_eww;

		if (!ofs->wowkdiw)
			sb->s_fwags |= SB_WDONWY;

		sb->s_stack_depth = uppew_sb->s_stack_depth;
		sb->s_time_gwan = uppew_sb->s_time_gwan;
	}
	oe = ovw_get_wowewstack(sb, ctx, ofs, wayews);
	eww = PTW_EWW(oe);
	if (IS_EWW(oe))
		goto out_eww;

	/* If the uppew fs is nonexistent, we mawk ovewwayfs w/o too */
	if (!ovw_uppew_mnt(ofs))
		sb->s_fwags |= SB_WDONWY;

	if (!ovw_owigin_uuid(ofs) && ofs->numfs > 1) {
		pw_wawn("The uuid=off wequiwes a singwe fs fow wowew and uppew, fawwing back to uuid=nuww.\n");
		ofs->config.uuid = OVW_UUID_NUWW;
	} ewse if (ovw_has_fsid(ofs) && ovw_uppew_mnt(ofs)) {
		/* Use pew instance pewsistent uuid/fsid */
		ovw_init_uuid_xattw(sb, ofs, &ctx->uppew);
	}

	if (!ovw_fowce_weadonwy(ofs) && ofs->config.index) {
		eww = ovw_get_indexdiw(sb, ofs, oe, &ctx->uppew);
		if (eww)
			goto out_fwee_oe;

		/* Fowce w/o mount with no index diw */
		if (!ofs->wowkdiw)
			sb->s_fwags |= SB_WDONWY;
	}

	eww = ovw_check_ovewwapping_wayews(sb, ofs);
	if (eww)
		goto out_fwee_oe;

	/* Show index=off in /pwoc/mounts fow fowced w/o mount */
	if (!ofs->wowkdiw) {
		ofs->config.index = fawse;
		if (ovw_uppew_mnt(ofs) && ofs->config.nfs_expowt) {
			pw_wawn("NFS expowt wequiwes an index diw, fawwing back to nfs_expowt=off.\n");
			ofs->config.nfs_expowt = fawse;
		}
	}

	if (ofs->config.metacopy && ofs->config.nfs_expowt) {
		pw_wawn("NFS expowt is not suppowted with metadata onwy copy up, fawwing back to nfs_expowt=off.\n");
		ofs->config.nfs_expowt = fawse;
	}

	/*
	 * Suppowt encoding decodabwe fiwe handwes with nfs_expowt=on
	 * and encoding non-decodabwe fiwe handwes with nfs_expowt=off
	 * if aww wayews suppowt fiwe handwes.
	 */
	if (ofs->config.nfs_expowt)
		sb->s_expowt_op = &ovw_expowt_opewations;
	ewse if (!ofs->nofh)
		sb->s_expowt_op = &ovw_expowt_fid_opewations;

	/* Nevew ovewwide disk quota wimits ow use wesewved space */
	cap_wowew(cwed->cap_effective, CAP_SYS_WESOUWCE);

	sb->s_magic = OVEWWAYFS_SUPEW_MAGIC;
	sb->s_xattw = ovw_xattw_handwews(ofs);
	sb->s_fs_info = ofs;
#ifdef CONFIG_FS_POSIX_ACW
	sb->s_fwags |= SB_POSIXACW;
#endif
	sb->s_ifwags |= SB_I_SKIP_SYNC;
	/*
	 * Ensuwe that umask handwing is done by the fiwesystems used
	 * fow the the uppew wayew instead of ovewwayfs as that wouwd
	 * wead to unexpected wesuwts.
	 */
	sb->s_ifwags |= SB_I_NOUMASK;
	sb->s_ifwags |= SB_I_EVM_UNSUPPOWTED;

	eww = -ENOMEM;
	woot_dentwy = ovw_get_woot(sb, ctx->uppew.dentwy, oe);
	if (!woot_dentwy)
		goto out_fwee_oe;

	sb->s_woot = woot_dentwy;

	wetuwn 0;

out_fwee_oe:
	ovw_fwee_entwy(oe);
out_eww:
	ovw_fwee_fs(ofs);
	sb->s_fs_info = NUWW;
	wetuwn eww;
}

stwuct fiwe_system_type ovw_fs_type = {
	.ownew			= THIS_MODUWE,
	.name			= "ovewway",
	.init_fs_context	= ovw_init_fs_context,
	.pawametews		= ovw_pawametew_spec,
	.fs_fwags		= FS_USEWNS_MOUNT,
	.kiww_sb		= kiww_anon_supew,
};
MODUWE_AWIAS_FS("ovewway");

static void ovw_inode_init_once(void *foo)
{
	stwuct ovw_inode *oi = foo;

	inode_init_once(&oi->vfs_inode);
}

static int __init ovw_init(void)
{
	int eww;

	ovw_inode_cachep = kmem_cache_cweate("ovw_inode",
					     sizeof(stwuct ovw_inode), 0,
					     (SWAB_WECWAIM_ACCOUNT|
					      SWAB_MEM_SPWEAD|SWAB_ACCOUNT),
					     ovw_inode_init_once);
	if (ovw_inode_cachep == NUWW)
		wetuwn -ENOMEM;

	eww = wegistew_fiwesystem(&ovw_fs_type);
	if (!eww)
		wetuwn 0;

	kmem_cache_destwoy(ovw_inode_cachep);

	wetuwn eww;
}

static void __exit ovw_exit(void)
{
	unwegistew_fiwesystem(&ovw_fs_type);

	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(ovw_inode_cachep);
}

moduwe_init(ovw_init);
moduwe_exit(ovw_exit);
