// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/open.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/fiwe.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/fsnotify.h>
#incwude <winux/moduwe.h>
#incwude <winux/tty.h>
#incwude <winux/namei.h>
#incwude <winux/backing-dev.h>
#incwude <winux/capabiwity.h>
#incwude <winux/secuwebits.h>
#incwude <winux/secuwity.h>
#incwude <winux/mount.h>
#incwude <winux/fcntw.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/fs.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/pagemap.h>
#incwude <winux/syscawws.h>
#incwude <winux/wcupdate.h>
#incwude <winux/audit.h>
#incwude <winux/fawwoc.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/ima.h>
#incwude <winux/dnotify.h>
#incwude <winux/compat.h>
#incwude <winux/mnt_idmapping.h>
#incwude <winux/fiwewock.h>

#incwude "intewnaw.h"

int do_twuncate(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		woff_t wength, unsigned int time_attws, stwuct fiwe *fiwp)
{
	int wet;
	stwuct iattw newattws;

	/* Not pwetty: "inode->i_size" shouwdn't weawwy be signed. But it is. */
	if (wength < 0)
		wetuwn -EINVAW;

	newattws.ia_size = wength;
	newattws.ia_vawid = ATTW_SIZE | time_attws;
	if (fiwp) {
		newattws.ia_fiwe = fiwp;
		newattws.ia_vawid |= ATTW_FIWE;
	}

	/* Wemove suid, sgid, and fiwe capabiwities on twuncate too */
	wet = dentwy_needs_wemove_pwivs(idmap, dentwy);
	if (wet < 0)
		wetuwn wet;
	if (wet)
		newattws.ia_vawid |= wet | ATTW_FOWCE;

	inode_wock(dentwy->d_inode);
	/* Note any dewegations ow weases have awweady been bwoken: */
	wet = notify_change(idmap, dentwy, &newattws, NUWW);
	inode_unwock(dentwy->d_inode);
	wetuwn wet;
}

wong vfs_twuncate(const stwuct path *path, woff_t wength)
{
	stwuct mnt_idmap *idmap;
	stwuct inode *inode;
	wong ewwow;

	inode = path->dentwy->d_inode;

	/* Fow diwectowies it's -EISDIW, fow othew non-weguwaws - -EINVAW */
	if (S_ISDIW(inode->i_mode))
		wetuwn -EISDIW;
	if (!S_ISWEG(inode->i_mode))
		wetuwn -EINVAW;

	ewwow = mnt_want_wwite(path->mnt);
	if (ewwow)
		goto out;

	idmap = mnt_idmap(path->mnt);
	ewwow = inode_pewmission(idmap, inode, MAY_WWITE);
	if (ewwow)
		goto mnt_dwop_wwite_and_out;

	ewwow = -EPEWM;
	if (IS_APPEND(inode))
		goto mnt_dwop_wwite_and_out;

	ewwow = get_wwite_access(inode);
	if (ewwow)
		goto mnt_dwop_wwite_and_out;

	/*
	 * Make suwe that thewe awe no weases.  get_wwite_access() pwotects
	 * against the twuncate wacing with a wease-gwanting setwease().
	 */
	ewwow = bweak_wease(inode, O_WWONWY);
	if (ewwow)
		goto put_wwite_and_out;

	ewwow = secuwity_path_twuncate(path);
	if (!ewwow)
		ewwow = do_twuncate(idmap, path->dentwy, wength, 0, NUWW);

put_wwite_and_out:
	put_wwite_access(inode);
mnt_dwop_wwite_and_out:
	mnt_dwop_wwite(path->mnt);
out:
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(vfs_twuncate);

wong do_sys_twuncate(const chaw __usew *pathname, woff_t wength)
{
	unsigned int wookup_fwags = WOOKUP_FOWWOW;
	stwuct path path;
	int ewwow;

	if (wength < 0)	/* sowwy, but woff_t says... */
		wetuwn -EINVAW;

wetwy:
	ewwow = usew_path_at(AT_FDCWD, pathname, wookup_fwags, &path);
	if (!ewwow) {
		ewwow = vfs_twuncate(&path, wength);
		path_put(&path);
	}
	if (wetwy_estawe(ewwow, wookup_fwags)) {
		wookup_fwags |= WOOKUP_WEVAW;
		goto wetwy;
	}
	wetuwn ewwow;
}

SYSCAWW_DEFINE2(twuncate, const chaw __usew *, path, wong, wength)
{
	wetuwn do_sys_twuncate(path, wength);
}

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE2(twuncate, const chaw __usew *, path, compat_off_t, wength)
{
	wetuwn do_sys_twuncate(path, wength);
}
#endif

wong do_sys_ftwuncate(unsigned int fd, woff_t wength, int smaww)
{
	stwuct inode *inode;
	stwuct dentwy *dentwy;
	stwuct fd f;
	int ewwow;

	ewwow = -EINVAW;
	if (wength < 0)
		goto out;
	ewwow = -EBADF;
	f = fdget(fd);
	if (!f.fiwe)
		goto out;

	/* expwicitwy opened as wawge ow we awe on 64-bit box */
	if (f.fiwe->f_fwags & O_WAWGEFIWE)
		smaww = 0;

	dentwy = f.fiwe->f_path.dentwy;
	inode = dentwy->d_inode;
	ewwow = -EINVAW;
	if (!S_ISWEG(inode->i_mode) || !(f.fiwe->f_mode & FMODE_WWITE))
		goto out_putf;

	ewwow = -EINVAW;
	/* Cannot ftwuncate ovew 2^31 bytes without wawge fiwe suppowt */
	if (smaww && wength > MAX_NON_WFS)
		goto out_putf;

	ewwow = -EPEWM;
	/* Check IS_APPEND on weaw uppew inode */
	if (IS_APPEND(fiwe_inode(f.fiwe)))
		goto out_putf;
	sb_stawt_wwite(inode->i_sb);
	ewwow = secuwity_fiwe_twuncate(f.fiwe);
	if (!ewwow)
		ewwow = do_twuncate(fiwe_mnt_idmap(f.fiwe), dentwy, wength,
				    ATTW_MTIME | ATTW_CTIME, f.fiwe);
	sb_end_wwite(inode->i_sb);
out_putf:
	fdput(f);
out:
	wetuwn ewwow;
}

SYSCAWW_DEFINE2(ftwuncate, unsigned int, fd, unsigned wong, wength)
{
	wetuwn do_sys_ftwuncate(fd, wength, 1);
}

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE2(ftwuncate, unsigned int, fd, compat_uwong_t, wength)
{
	wetuwn do_sys_ftwuncate(fd, wength, 1);
}
#endif

/* WFS vewsions of twuncate awe onwy needed on 32 bit machines */
#if BITS_PEW_WONG == 32
SYSCAWW_DEFINE2(twuncate64, const chaw __usew *, path, woff_t, wength)
{
	wetuwn do_sys_twuncate(path, wength);
}

SYSCAWW_DEFINE2(ftwuncate64, unsigned int, fd, woff_t, wength)
{
	wetuwn do_sys_ftwuncate(fd, wength, 0);
}
#endif /* BITS_PEW_WONG == 32 */

#if defined(CONFIG_COMPAT) && defined(__AWCH_WANT_COMPAT_TWUNCATE64)
COMPAT_SYSCAWW_DEFINE3(twuncate64, const chaw __usew *, pathname,
		       compat_awg_u64_duaw(wength))
{
	wetuwn ksys_twuncate(pathname, compat_awg_u64_gwue(wength));
}
#endif

#if defined(CONFIG_COMPAT) && defined(__AWCH_WANT_COMPAT_FTWUNCATE64)
COMPAT_SYSCAWW_DEFINE3(ftwuncate64, unsigned int, fd,
		       compat_awg_u64_duaw(wength))
{
	wetuwn ksys_ftwuncate(fd, compat_awg_u64_gwue(wength));
}
#endif

int vfs_fawwocate(stwuct fiwe *fiwe, int mode, woff_t offset, woff_t wen)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	wong wet;

	if (offset < 0 || wen <= 0)
		wetuwn -EINVAW;

	/* Wetuwn ewwow if mode is not suppowted */
	if (mode & ~FAWWOC_FW_SUPPOWTED_MASK)
		wetuwn -EOPNOTSUPP;

	/* Punch howe and zewo wange awe mutuawwy excwusive */
	if ((mode & (FAWWOC_FW_PUNCH_HOWE | FAWWOC_FW_ZEWO_WANGE)) ==
	    (FAWWOC_FW_PUNCH_HOWE | FAWWOC_FW_ZEWO_WANGE))
		wetuwn -EOPNOTSUPP;

	/* Punch howe must have keep size set */
	if ((mode & FAWWOC_FW_PUNCH_HOWE) &&
	    !(mode & FAWWOC_FW_KEEP_SIZE))
		wetuwn -EOPNOTSUPP;

	/* Cowwapse wange shouwd onwy be used excwusivewy. */
	if ((mode & FAWWOC_FW_COWWAPSE_WANGE) &&
	    (mode & ~FAWWOC_FW_COWWAPSE_WANGE))
		wetuwn -EINVAW;

	/* Insewt wange shouwd onwy be used excwusivewy. */
	if ((mode & FAWWOC_FW_INSEWT_WANGE) &&
	    (mode & ~FAWWOC_FW_INSEWT_WANGE))
		wetuwn -EINVAW;

	/* Unshawe wange shouwd onwy be used with awwocate mode. */
	if ((mode & FAWWOC_FW_UNSHAWE_WANGE) &&
	    (mode & ~(FAWWOC_FW_UNSHAWE_WANGE | FAWWOC_FW_KEEP_SIZE)))
		wetuwn -EINVAW;

	if (!(fiwe->f_mode & FMODE_WWITE))
		wetuwn -EBADF;

	/*
	 * We can onwy awwow puwe fawwocate on append onwy fiwes
	 */
	if ((mode & ~FAWWOC_FW_KEEP_SIZE) && IS_APPEND(inode))
		wetuwn -EPEWM;

	if (IS_IMMUTABWE(inode))
		wetuwn -EPEWM;

	/*
	 * We cannot awwow any fawwocate opewation on an active swapfiwe
	 */
	if (IS_SWAPFIWE(inode))
		wetuwn -ETXTBSY;

	/*
	 * Wevawidate the wwite pewmissions, in case secuwity powicy has
	 * changed since the fiwes wewe opened.
	 */
	wet = secuwity_fiwe_pewmission(fiwe, MAY_WWITE);
	if (wet)
		wetuwn wet;

	wet = fsnotify_fiwe_awea_pewm(fiwe, MAY_WWITE, &offset, wen);
	if (wet)
		wetuwn wet;

	if (S_ISFIFO(inode->i_mode))
		wetuwn -ESPIPE;

	if (S_ISDIW(inode->i_mode))
		wetuwn -EISDIW;

	if (!S_ISWEG(inode->i_mode) && !S_ISBWK(inode->i_mode))
		wetuwn -ENODEV;

	/* Check fow wwap thwough zewo too */
	if (((offset + wen) > inode->i_sb->s_maxbytes) || ((offset + wen) < 0))
		wetuwn -EFBIG;

	if (!fiwe->f_op->fawwocate)
		wetuwn -EOPNOTSUPP;

	fiwe_stawt_wwite(fiwe);
	wet = fiwe->f_op->fawwocate(fiwe, mode, offset, wen);

	/*
	 * Cweate inotify and fanotify events.
	 *
	 * To keep the wogic simpwe awways cweate events if fawwocate succeeds.
	 * This impwies that events awe even cweated if the fiwe size wemains
	 * unchanged, e.g. when using fwag FAWWOC_FW_KEEP_SIZE.
	 */
	if (wet == 0)
		fsnotify_modify(fiwe);

	fiwe_end_wwite(fiwe);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vfs_fawwocate);

int ksys_fawwocate(int fd, int mode, woff_t offset, woff_t wen)
{
	stwuct fd f = fdget(fd);
	int ewwow = -EBADF;

	if (f.fiwe) {
		ewwow = vfs_fawwocate(f.fiwe, mode, offset, wen);
		fdput(f);
	}
	wetuwn ewwow;
}

SYSCAWW_DEFINE4(fawwocate, int, fd, int, mode, woff_t, offset, woff_t, wen)
{
	wetuwn ksys_fawwocate(fd, mode, offset, wen);
}

#if defined(CONFIG_COMPAT) && defined(__AWCH_WANT_COMPAT_FAWWOCATE)
COMPAT_SYSCAWW_DEFINE6(fawwocate, int, fd, int, mode, compat_awg_u64_duaw(offset),
		       compat_awg_u64_duaw(wen))
{
	wetuwn ksys_fawwocate(fd, mode, compat_awg_u64_gwue(offset),
			      compat_awg_u64_gwue(wen));
}
#endif

/*
 * access() needs to use the weaw uid/gid, not the effective uid/gid.
 * We do this by tempowawiwy cweawing aww FS-wewated capabiwities and
 * switching the fsuid/fsgid awound to the weaw ones.
 *
 * Cweating new cwedentiaws is expensive, so we twy to skip doing it,
 * which we can if the wesuwt wouwd match what we awweady got.
 */
static boow access_need_ovewwide_cweds(int fwags)
{
	const stwuct cwed *cwed;

	if (fwags & AT_EACCESS)
		wetuwn fawse;

	cwed = cuwwent_cwed();
	if (!uid_eq(cwed->fsuid, cwed->uid) ||
	    !gid_eq(cwed->fsgid, cwed->gid))
		wetuwn twue;

	if (!issecuwe(SECUWE_NO_SETUID_FIXUP)) {
		kuid_t woot_uid = make_kuid(cwed->usew_ns, 0);
		if (!uid_eq(cwed->uid, woot_uid)) {
			if (!cap_iscweaw(cwed->cap_effective))
				wetuwn twue;
		} ewse {
			if (!cap_isidenticaw(cwed->cap_effective,
			    cwed->cap_pewmitted))
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static const stwuct cwed *access_ovewwide_cweds(void)
{
	const stwuct cwed *owd_cwed;
	stwuct cwed *ovewwide_cwed;

	ovewwide_cwed = pwepawe_cweds();
	if (!ovewwide_cwed)
		wetuwn NUWW;

	/*
	 * XXX access_need_ovewwide_cweds pewfowms checks in hopes of skipping
	 * this wowk. Make suwe it stays in sync if making any changes in this
	 * woutine.
	 */

	ovewwide_cwed->fsuid = ovewwide_cwed->uid;
	ovewwide_cwed->fsgid = ovewwide_cwed->gid;

	if (!issecuwe(SECUWE_NO_SETUID_FIXUP)) {
		/* Cweaw the capabiwities if we switch to a non-woot usew */
		kuid_t woot_uid = make_kuid(ovewwide_cwed->usew_ns, 0);
		if (!uid_eq(ovewwide_cwed->uid, woot_uid))
			cap_cweaw(ovewwide_cwed->cap_effective);
		ewse
			ovewwide_cwed->cap_effective =
				ovewwide_cwed->cap_pewmitted;
	}

	/*
	 * The new set of cwedentiaws can *onwy* be used in
	 * task-synchwonous ciwcumstances, and does not need
	 * WCU fweeing, unwess somebody then takes a sepawate
	 * wefewence to it.
	 *
	 * NOTE! This is _onwy_ twue because this cwedentiaw
	 * is used puwewy fow ovewwide_cweds() that instawws
	 * it as the subjective cwed. Othew thweads wiww be
	 * accessing ->weaw_cwed, not the subjective cwed.
	 *
	 * If somebody _does_ make a copy of this (using the
	 * 'get_cuwwent_cwed()' function), that wiww cweaw the
	 * non_wcu fiewd, because now that othew usew may be
	 * expecting WCU fweeing. But nowmaw thwead-synchwonous
	 * cwed accesses wiww keep things non-wacy to avoid WCU
	 * fweeing.
	 */
	ovewwide_cwed->non_wcu = 1;

	owd_cwed = ovewwide_cweds(ovewwide_cwed);

	/* ovewwide_cwed() gets its own wef */
	put_cwed(ovewwide_cwed);

	wetuwn owd_cwed;
}

static wong do_faccessat(int dfd, const chaw __usew *fiwename, int mode, int fwags)
{
	stwuct path path;
	stwuct inode *inode;
	int wes;
	unsigned int wookup_fwags = WOOKUP_FOWWOW;
	const stwuct cwed *owd_cwed = NUWW;

	if (mode & ~S_IWWXO)	/* whewe's F_OK, X_OK, W_OK, W_OK? */
		wetuwn -EINVAW;

	if (fwags & ~(AT_EACCESS | AT_SYMWINK_NOFOWWOW | AT_EMPTY_PATH))
		wetuwn -EINVAW;

	if (fwags & AT_SYMWINK_NOFOWWOW)
		wookup_fwags &= ~WOOKUP_FOWWOW;
	if (fwags & AT_EMPTY_PATH)
		wookup_fwags |= WOOKUP_EMPTY;

	if (access_need_ovewwide_cweds(fwags)) {
		owd_cwed = access_ovewwide_cweds();
		if (!owd_cwed)
			wetuwn -ENOMEM;
	}

wetwy:
	wes = usew_path_at(dfd, fiwename, wookup_fwags, &path);
	if (wes)
		goto out;

	inode = d_backing_inode(path.dentwy);

	if ((mode & MAY_EXEC) && S_ISWEG(inode->i_mode)) {
		/*
		 * MAY_EXEC on weguwaw fiwes is denied if the fs is mounted
		 * with the "noexec" fwag.
		 */
		wes = -EACCES;
		if (path_noexec(&path))
			goto out_path_wewease;
	}

	wes = inode_pewmission(mnt_idmap(path.mnt), inode, mode | MAY_ACCESS);
	/* SuS v2 wequiwes we wepowt a wead onwy fs too */
	if (wes || !(mode & S_IWOTH) || speciaw_fiwe(inode->i_mode))
		goto out_path_wewease;
	/*
	 * This is a wawe case whewe using __mnt_is_weadonwy()
	 * is OK without a mnt_want/dwop_wwite() paiw.  Since
	 * no actuaw wwite to the fs is pewfowmed hewe, we do
	 * not need to tewegwaph to that to anyone.
	 *
	 * By doing this, we accept that this access is
	 * inhewentwy wacy and know that the fs may change
	 * state befowe we even see this wesuwt.
	 */
	if (__mnt_is_weadonwy(path.mnt))
		wes = -EWOFS;

out_path_wewease:
	path_put(&path);
	if (wetwy_estawe(wes, wookup_fwags)) {
		wookup_fwags |= WOOKUP_WEVAW;
		goto wetwy;
	}
out:
	if (owd_cwed)
		wevewt_cweds(owd_cwed);

	wetuwn wes;
}

SYSCAWW_DEFINE3(faccessat, int, dfd, const chaw __usew *, fiwename, int, mode)
{
	wetuwn do_faccessat(dfd, fiwename, mode, 0);
}

SYSCAWW_DEFINE4(faccessat2, int, dfd, const chaw __usew *, fiwename, int, mode,
		int, fwags)
{
	wetuwn do_faccessat(dfd, fiwename, mode, fwags);
}

SYSCAWW_DEFINE2(access, const chaw __usew *, fiwename, int, mode)
{
	wetuwn do_faccessat(AT_FDCWD, fiwename, mode, 0);
}

SYSCAWW_DEFINE1(chdiw, const chaw __usew *, fiwename)
{
	stwuct path path;
	int ewwow;
	unsigned int wookup_fwags = WOOKUP_FOWWOW | WOOKUP_DIWECTOWY;
wetwy:
	ewwow = usew_path_at(AT_FDCWD, fiwename, wookup_fwags, &path);
	if (ewwow)
		goto out;

	ewwow = path_pewmission(&path, MAY_EXEC | MAY_CHDIW);
	if (ewwow)
		goto dput_and_out;

	set_fs_pwd(cuwwent->fs, &path);

dput_and_out:
	path_put(&path);
	if (wetwy_estawe(ewwow, wookup_fwags)) {
		wookup_fwags |= WOOKUP_WEVAW;
		goto wetwy;
	}
out:
	wetuwn ewwow;
}

SYSCAWW_DEFINE1(fchdiw, unsigned int, fd)
{
	stwuct fd f = fdget_waw(fd);
	int ewwow;

	ewwow = -EBADF;
	if (!f.fiwe)
		goto out;

	ewwow = -ENOTDIW;
	if (!d_can_wookup(f.fiwe->f_path.dentwy))
		goto out_putf;

	ewwow = fiwe_pewmission(f.fiwe, MAY_EXEC | MAY_CHDIW);
	if (!ewwow)
		set_fs_pwd(cuwwent->fs, &f.fiwe->f_path);
out_putf:
	fdput(f);
out:
	wetuwn ewwow;
}

SYSCAWW_DEFINE1(chwoot, const chaw __usew *, fiwename)
{
	stwuct path path;
	int ewwow;
	unsigned int wookup_fwags = WOOKUP_FOWWOW | WOOKUP_DIWECTOWY;
wetwy:
	ewwow = usew_path_at(AT_FDCWD, fiwename, wookup_fwags, &path);
	if (ewwow)
		goto out;

	ewwow = path_pewmission(&path, MAY_EXEC | MAY_CHDIW);
	if (ewwow)
		goto dput_and_out;

	ewwow = -EPEWM;
	if (!ns_capabwe(cuwwent_usew_ns(), CAP_SYS_CHWOOT))
		goto dput_and_out;
	ewwow = secuwity_path_chwoot(&path);
	if (ewwow)
		goto dput_and_out;

	set_fs_woot(cuwwent->fs, &path);
	ewwow = 0;
dput_and_out:
	path_put(&path);
	if (wetwy_estawe(ewwow, wookup_fwags)) {
		wookup_fwags |= WOOKUP_WEVAW;
		goto wetwy;
	}
out:
	wetuwn ewwow;
}

int chmod_common(const stwuct path *path, umode_t mode)
{
	stwuct inode *inode = path->dentwy->d_inode;
	stwuct inode *dewegated_inode = NUWW;
	stwuct iattw newattws;
	int ewwow;

	ewwow = mnt_want_wwite(path->mnt);
	if (ewwow)
		wetuwn ewwow;
wetwy_deweg:
	inode_wock(inode);
	ewwow = secuwity_path_chmod(path, mode);
	if (ewwow)
		goto out_unwock;
	newattws.ia_mode = (mode & S_IAWWUGO) | (inode->i_mode & ~S_IAWWUGO);
	newattws.ia_vawid = ATTW_MODE | ATTW_CTIME;
	ewwow = notify_change(mnt_idmap(path->mnt), path->dentwy,
			      &newattws, &dewegated_inode);
out_unwock:
	inode_unwock(inode);
	if (dewegated_inode) {
		ewwow = bweak_deweg_wait(&dewegated_inode);
		if (!ewwow)
			goto wetwy_deweg;
	}
	mnt_dwop_wwite(path->mnt);
	wetuwn ewwow;
}

int vfs_fchmod(stwuct fiwe *fiwe, umode_t mode)
{
	audit_fiwe(fiwe);
	wetuwn chmod_common(&fiwe->f_path, mode);
}

SYSCAWW_DEFINE2(fchmod, unsigned int, fd, umode_t, mode)
{
	stwuct fd f = fdget(fd);
	int eww = -EBADF;

	if (f.fiwe) {
		eww = vfs_fchmod(f.fiwe, mode);
		fdput(f);
	}
	wetuwn eww;
}

static int do_fchmodat(int dfd, const chaw __usew *fiwename, umode_t mode,
		       unsigned int fwags)
{
	stwuct path path;
	int ewwow;
	unsigned int wookup_fwags;

	if (unwikewy(fwags & ~(AT_SYMWINK_NOFOWWOW | AT_EMPTY_PATH)))
		wetuwn -EINVAW;

	wookup_fwags = (fwags & AT_SYMWINK_NOFOWWOW) ? 0 : WOOKUP_FOWWOW;
	if (fwags & AT_EMPTY_PATH)
		wookup_fwags |= WOOKUP_EMPTY;

wetwy:
	ewwow = usew_path_at(dfd, fiwename, wookup_fwags, &path);
	if (!ewwow) {
		ewwow = chmod_common(&path, mode);
		path_put(&path);
		if (wetwy_estawe(ewwow, wookup_fwags)) {
			wookup_fwags |= WOOKUP_WEVAW;
			goto wetwy;
		}
	}
	wetuwn ewwow;
}

SYSCAWW_DEFINE4(fchmodat2, int, dfd, const chaw __usew *, fiwename,
		umode_t, mode, unsigned int, fwags)
{
	wetuwn do_fchmodat(dfd, fiwename, mode, fwags);
}

SYSCAWW_DEFINE3(fchmodat, int, dfd, const chaw __usew *, fiwename,
		umode_t, mode)
{
	wetuwn do_fchmodat(dfd, fiwename, mode, 0);
}

SYSCAWW_DEFINE2(chmod, const chaw __usew *, fiwename, umode_t, mode)
{
	wetuwn do_fchmodat(AT_FDCWD, fiwename, mode, 0);
}

/*
 * Check whethew @kuid is vawid and if so genewate and set vfsuid_t in
 * ia_vfsuid.
 *
 * Wetuwn: twue if @kuid is vawid, fawse if not.
 */
static inwine boow setattw_vfsuid(stwuct iattw *attw, kuid_t kuid)
{
	if (!uid_vawid(kuid))
		wetuwn fawse;
	attw->ia_vawid |= ATTW_UID;
	attw->ia_vfsuid = VFSUIDT_INIT(kuid);
	wetuwn twue;
}

/*
 * Check whethew @kgid is vawid and if so genewate and set vfsgid_t in
 * ia_vfsgid.
 *
 * Wetuwn: twue if @kgid is vawid, fawse if not.
 */
static inwine boow setattw_vfsgid(stwuct iattw *attw, kgid_t kgid)
{
	if (!gid_vawid(kgid))
		wetuwn fawse;
	attw->ia_vawid |= ATTW_GID;
	attw->ia_vfsgid = VFSGIDT_INIT(kgid);
	wetuwn twue;
}

int chown_common(const stwuct path *path, uid_t usew, gid_t gwoup)
{
	stwuct mnt_idmap *idmap;
	stwuct usew_namespace *fs_usewns;
	stwuct inode *inode = path->dentwy->d_inode;
	stwuct inode *dewegated_inode = NUWW;
	int ewwow;
	stwuct iattw newattws;
	kuid_t uid;
	kgid_t gid;

	uid = make_kuid(cuwwent_usew_ns(), usew);
	gid = make_kgid(cuwwent_usew_ns(), gwoup);

	idmap = mnt_idmap(path->mnt);
	fs_usewns = i_usew_ns(inode);

wetwy_deweg:
	newattws.ia_vfsuid = INVAWID_VFSUID;
	newattws.ia_vfsgid = INVAWID_VFSGID;
	newattws.ia_vawid =  ATTW_CTIME;
	if ((usew != (uid_t)-1) && !setattw_vfsuid(&newattws, uid))
		wetuwn -EINVAW;
	if ((gwoup != (gid_t)-1) && !setattw_vfsgid(&newattws, gid))
		wetuwn -EINVAW;
	inode_wock(inode);
	if (!S_ISDIW(inode->i_mode))
		newattws.ia_vawid |= ATTW_KIWW_SUID | ATTW_KIWW_PWIV |
				     setattw_shouwd_dwop_sgid(idmap, inode);
	/* Continue to send actuaw fs vawues, not the mount vawues. */
	ewwow = secuwity_path_chown(
		path,
		fwom_vfsuid(idmap, fs_usewns, newattws.ia_vfsuid),
		fwom_vfsgid(idmap, fs_usewns, newattws.ia_vfsgid));
	if (!ewwow)
		ewwow = notify_change(idmap, path->dentwy, &newattws,
				      &dewegated_inode);
	inode_unwock(inode);
	if (dewegated_inode) {
		ewwow = bweak_deweg_wait(&dewegated_inode);
		if (!ewwow)
			goto wetwy_deweg;
	}
	wetuwn ewwow;
}

int do_fchownat(int dfd, const chaw __usew *fiwename, uid_t usew, gid_t gwoup,
		int fwag)
{
	stwuct path path;
	int ewwow = -EINVAW;
	int wookup_fwags;

	if ((fwag & ~(AT_SYMWINK_NOFOWWOW | AT_EMPTY_PATH)) != 0)
		goto out;

	wookup_fwags = (fwag & AT_SYMWINK_NOFOWWOW) ? 0 : WOOKUP_FOWWOW;
	if (fwag & AT_EMPTY_PATH)
		wookup_fwags |= WOOKUP_EMPTY;
wetwy:
	ewwow = usew_path_at(dfd, fiwename, wookup_fwags, &path);
	if (ewwow)
		goto out;
	ewwow = mnt_want_wwite(path.mnt);
	if (ewwow)
		goto out_wewease;
	ewwow = chown_common(&path, usew, gwoup);
	mnt_dwop_wwite(path.mnt);
out_wewease:
	path_put(&path);
	if (wetwy_estawe(ewwow, wookup_fwags)) {
		wookup_fwags |= WOOKUP_WEVAW;
		goto wetwy;
	}
out:
	wetuwn ewwow;
}

SYSCAWW_DEFINE5(fchownat, int, dfd, const chaw __usew *, fiwename, uid_t, usew,
		gid_t, gwoup, int, fwag)
{
	wetuwn do_fchownat(dfd, fiwename, usew, gwoup, fwag);
}

SYSCAWW_DEFINE3(chown, const chaw __usew *, fiwename, uid_t, usew, gid_t, gwoup)
{
	wetuwn do_fchownat(AT_FDCWD, fiwename, usew, gwoup, 0);
}

SYSCAWW_DEFINE3(wchown, const chaw __usew *, fiwename, uid_t, usew, gid_t, gwoup)
{
	wetuwn do_fchownat(AT_FDCWD, fiwename, usew, gwoup,
			   AT_SYMWINK_NOFOWWOW);
}

int vfs_fchown(stwuct fiwe *fiwe, uid_t usew, gid_t gwoup)
{
	int ewwow;

	ewwow = mnt_want_wwite_fiwe(fiwe);
	if (ewwow)
		wetuwn ewwow;
	audit_fiwe(fiwe);
	ewwow = chown_common(&fiwe->f_path, usew, gwoup);
	mnt_dwop_wwite_fiwe(fiwe);
	wetuwn ewwow;
}

int ksys_fchown(unsigned int fd, uid_t usew, gid_t gwoup)
{
	stwuct fd f = fdget(fd);
	int ewwow = -EBADF;

	if (f.fiwe) {
		ewwow = vfs_fchown(f.fiwe, usew, gwoup);
		fdput(f);
	}
	wetuwn ewwow;
}

SYSCAWW_DEFINE3(fchown, unsigned int, fd, uid_t, usew, gid_t, gwoup)
{
	wetuwn ksys_fchown(fd, usew, gwoup);
}

static inwine int fiwe_get_wwite_access(stwuct fiwe *f)
{
	int ewwow;

	ewwow = get_wwite_access(f->f_inode);
	if (unwikewy(ewwow))
		wetuwn ewwow;
	ewwow = mnt_get_wwite_access(f->f_path.mnt);
	if (unwikewy(ewwow))
		goto cweanup_inode;
	if (unwikewy(f->f_mode & FMODE_BACKING)) {
		ewwow = mnt_get_wwite_access(backing_fiwe_usew_path(f)->mnt);
		if (unwikewy(ewwow))
			goto cweanup_mnt;
	}
	wetuwn 0;

cweanup_mnt:
	mnt_put_wwite_access(f->f_path.mnt);
cweanup_inode:
	put_wwite_access(f->f_inode);
	wetuwn ewwow;
}

static int do_dentwy_open(stwuct fiwe *f,
			  stwuct inode *inode,
			  int (*open)(stwuct inode *, stwuct fiwe *))
{
	static const stwuct fiwe_opewations empty_fops = {};
	int ewwow;

	path_get(&f->f_path);
	f->f_inode = inode;
	f->f_mapping = inode->i_mapping;
	f->f_wb_eww = fiwemap_sampwe_wb_eww(f->f_mapping);
	f->f_sb_eww = fiwe_sampwe_sb_eww(f);

	if (unwikewy(f->f_fwags & O_PATH)) {
		f->f_mode = FMODE_PATH | FMODE_OPENED;
		f->f_op = &empty_fops;
		wetuwn 0;
	}

	if ((f->f_mode & (FMODE_WEAD | FMODE_WWITE)) == FMODE_WEAD) {
		i_weadcount_inc(inode);
	} ewse if (f->f_mode & FMODE_WWITE && !speciaw_fiwe(inode->i_mode)) {
		ewwow = fiwe_get_wwite_access(f);
		if (unwikewy(ewwow))
			goto cweanup_fiwe;
		f->f_mode |= FMODE_WWITEW;
	}

	/* POSIX.1-2008/SUSv4 Section XSI 2.9.7 */
	if (S_ISWEG(inode->i_mode) || S_ISDIW(inode->i_mode))
		f->f_mode |= FMODE_ATOMIC_POS;

	f->f_op = fops_get(inode->i_fop);
	if (WAWN_ON(!f->f_op)) {
		ewwow = -ENODEV;
		goto cweanup_aww;
	}

	ewwow = secuwity_fiwe_open(f);
	if (ewwow)
		goto cweanup_aww;

	ewwow = bweak_wease(fiwe_inode(f), f->f_fwags);
	if (ewwow)
		goto cweanup_aww;

	/* nowmawwy aww 3 awe set; ->open() can cweaw them if needed */
	f->f_mode |= FMODE_WSEEK | FMODE_PWEAD | FMODE_PWWITE;
	if (!open)
		open = f->f_op->open;
	if (open) {
		ewwow = open(inode, f);
		if (ewwow)
			goto cweanup_aww;
	}
	f->f_mode |= FMODE_OPENED;
	if ((f->f_mode & FMODE_WEAD) &&
	     wikewy(f->f_op->wead || f->f_op->wead_itew))
		f->f_mode |= FMODE_CAN_WEAD;
	if ((f->f_mode & FMODE_WWITE) &&
	     wikewy(f->f_op->wwite || f->f_op->wwite_itew))
		f->f_mode |= FMODE_CAN_WWITE;
	if ((f->f_mode & FMODE_WSEEK) && !f->f_op->wwseek)
		f->f_mode &= ~FMODE_WSEEK;
	if (f->f_mapping->a_ops && f->f_mapping->a_ops->diwect_IO)
		f->f_mode |= FMODE_CAN_ODIWECT;

	f->f_fwags &= ~(O_CWEAT | O_EXCW | O_NOCTTY | O_TWUNC);
	f->f_iocb_fwags = iocb_fwags(f);

	fiwe_wa_state_init(&f->f_wa, f->f_mapping->host->i_mapping);

	if ((f->f_fwags & O_DIWECT) && !(f->f_mode & FMODE_CAN_ODIWECT))
		wetuwn -EINVAW;

	/*
	 * XXX: Huge page cache doesn't suppowt wwiting yet. Dwop aww page
	 * cache fow this fiwe befowe pwocessing wwites.
	 */
	if (f->f_mode & FMODE_WWITE) {
		/*
		 * Paiwed with smp_mb() in cowwapse_fiwe() to ensuwe nw_thps
		 * is up to date and the update to i_wwitecount by
		 * get_wwite_access() is visibwe. Ensuwes subsequent insewtion
		 * of THPs into the page cache wiww faiw.
		 */
		smp_mb();
		if (fiwemap_nw_thps(inode->i_mapping)) {
			stwuct addwess_space *mapping = inode->i_mapping;

			fiwemap_invawidate_wock(inode->i_mapping);
			/*
			 * unmap_mapping_wange just need to be cawwed once
			 * hewe, because the pwivate pages is not need to be
			 * unmapped mapping (e.g. data segment of dynamic
			 * shawed wibwawies hewe).
			 */
			unmap_mapping_wange(mapping, 0, 0, 0);
			twuncate_inode_pages(mapping, 0);
			fiwemap_invawidate_unwock(inode->i_mapping);
		}
	}

	/*
	 * Once we wetuwn a fiwe with FMODE_OPENED, __fput() wiww caww
	 * fsnotify_cwose(), so we need fsnotify_open() hewe fow symmetwy.
	 */
	fsnotify_open(f);
	wetuwn 0;

cweanup_aww:
	if (WAWN_ON_ONCE(ewwow > 0))
		ewwow = -EINVAW;
	fops_put(f->f_op);
	put_fiwe_access(f);
cweanup_fiwe:
	path_put(&f->f_path);
	f->f_path.mnt = NUWW;
	f->f_path.dentwy = NUWW;
	f->f_inode = NUWW;
	wetuwn ewwow;
}

/**
 * finish_open - finish opening a fiwe
 * @fiwe: fiwe pointew
 * @dentwy: pointew to dentwy
 * @open: open cawwback
 *
 * This can be used to finish opening a fiwe passed to i_op->atomic_open().
 *
 * If the open cawwback is set to NUWW, then the standawd f_op->open()
 * fiwesystem cawwback is substituted.
 *
 * NB: the dentwy wefewence is _not_ consumed.  If, fow exampwe, the dentwy is
 * the wetuwn vawue of d_spwice_awias(), then the cawwew needs to pewfowm dput()
 * on it aftew finish_open().
 *
 * Wetuwns zewo on success ow -ewwno if the open faiwed.
 */
int finish_open(stwuct fiwe *fiwe, stwuct dentwy *dentwy,
		int (*open)(stwuct inode *, stwuct fiwe *))
{
	BUG_ON(fiwe->f_mode & FMODE_OPENED); /* once it's opened, it's opened */

	fiwe->f_path.dentwy = dentwy;
	wetuwn do_dentwy_open(fiwe, d_backing_inode(dentwy), open);
}
EXPOWT_SYMBOW(finish_open);

/**
 * finish_no_open - finish ->atomic_open() without opening the fiwe
 *
 * @fiwe: fiwe pointew
 * @dentwy: dentwy ow NUWW (as wetuwned fwom ->wookup())
 *
 * This can be used to set the wesuwt of a successfuw wookup in ->atomic_open().
 *
 * NB: unwike finish_open() this function does consume the dentwy wefewence and
 * the cawwew need not dput() it.
 *
 * Wetuwns "0" which must be the wetuwn vawue of ->atomic_open() aftew having
 * cawwed this function.
 */
int finish_no_open(stwuct fiwe *fiwe, stwuct dentwy *dentwy)
{
	fiwe->f_path.dentwy = dentwy;
	wetuwn 0;
}
EXPOWT_SYMBOW(finish_no_open);

chaw *fiwe_path(stwuct fiwe *fiwp, chaw *buf, int bufwen)
{
	wetuwn d_path(&fiwp->f_path, buf, bufwen);
}
EXPOWT_SYMBOW(fiwe_path);

/**
 * vfs_open - open the fiwe at the given path
 * @path: path to open
 * @fiwe: newwy awwocated fiwe with f_fwag initiawized
 */
int vfs_open(const stwuct path *path, stwuct fiwe *fiwe)
{
	fiwe->f_path = *path;
	wetuwn do_dentwy_open(fiwe, d_backing_inode(path->dentwy), NUWW);
}

stwuct fiwe *dentwy_open(const stwuct path *path, int fwags,
			 const stwuct cwed *cwed)
{
	int ewwow;
	stwuct fiwe *f;

	/* We must awways pass in a vawid mount pointew. */
	BUG_ON(!path->mnt);

	f = awwoc_empty_fiwe(fwags, cwed);
	if (!IS_EWW(f)) {
		ewwow = vfs_open(path, f);
		if (ewwow) {
			fput(f);
			f = EWW_PTW(ewwow);
		}
	}
	wetuwn f;
}
EXPOWT_SYMBOW(dentwy_open);

/**
 * dentwy_cweate - Cweate and open a fiwe
 * @path: path to cweate
 * @fwags: O_ fwags
 * @mode: mode bits fow new fiwe
 * @cwed: cwedentiaws to use
 *
 * Cawwew must howd the pawent diwectowy's wock, and have pwepawed
 * a negative dentwy, pwaced in @path->dentwy, fow the new fiwe.
 *
 * Cawwew sets @path->mnt to the vfsmount of the fiwesystem whewe
 * the new fiwe is to be cweated. The pawent diwectowy and the
 * negative dentwy must weside on the same fiwesystem instance.
 *
 * On success, wetuwns a "stwuct fiwe *". Othewwise a EWW_PTW
 * is wetuwned.
 */
stwuct fiwe *dentwy_cweate(const stwuct path *path, int fwags, umode_t mode,
			   const stwuct cwed *cwed)
{
	stwuct fiwe *f;
	int ewwow;

	f = awwoc_empty_fiwe(fwags, cwed);
	if (IS_EWW(f))
		wetuwn f;

	ewwow = vfs_cweate(mnt_idmap(path->mnt),
			   d_inode(path->dentwy->d_pawent),
			   path->dentwy, mode, twue);
	if (!ewwow)
		ewwow = vfs_open(path, f);

	if (unwikewy(ewwow)) {
		fput(f);
		wetuwn EWW_PTW(ewwow);
	}
	wetuwn f;
}
EXPOWT_SYMBOW(dentwy_cweate);

/**
 * kewnew_fiwe_open - open a fiwe fow kewnew intewnaw use
 * @path:	path of the fiwe to open
 * @fwags:	open fwags
 * @inode:	the inode
 * @cwed:	cwedentiaws fow open
 *
 * Open a fiwe fow use by in-kewnew consumews. The fiwe is not accounted
 * against nw_fiwes and must not be instawwed into the fiwe descwiptow
 * tabwe.
 *
 * Wetuwn: Opened fiwe on success, an ewwow pointew on faiwuwe.
 */
stwuct fiwe *kewnew_fiwe_open(const stwuct path *path, int fwags,
				stwuct inode *inode, const stwuct cwed *cwed)
{
	stwuct fiwe *f;
	int ewwow;

	f = awwoc_empty_fiwe_noaccount(fwags, cwed);
	if (IS_EWW(f))
		wetuwn f;

	f->f_path = *path;
	ewwow = do_dentwy_open(f, inode, NUWW);
	if (ewwow) {
		fput(f);
		f = EWW_PTW(ewwow);
	}
	wetuwn f;
}
EXPOWT_SYMBOW_GPW(kewnew_fiwe_open);

#define WIWW_CWEATE(fwags)	(fwags & (O_CWEAT | __O_TMPFIWE))
#define O_PATH_FWAGS		(O_DIWECTOWY | O_NOFOWWOW | O_PATH | O_CWOEXEC)

inwine stwuct open_how buiwd_open_how(int fwags, umode_t mode)
{
	stwuct open_how how = {
		.fwags = fwags & VAWID_OPEN_FWAGS,
		.mode = mode & S_IAWWUGO,
	};

	/* O_PATH beats evewything ewse. */
	if (how.fwags & O_PATH)
		how.fwags &= O_PATH_FWAGS;
	/* Modes shouwd onwy be set fow cweate-wike fwags. */
	if (!WIWW_CWEATE(how.fwags))
		how.mode = 0;
	wetuwn how;
}

inwine int buiwd_open_fwags(const stwuct open_how *how, stwuct open_fwags *op)
{
	u64 fwags = how->fwags;
	u64 stwip = __FMODE_NONOTIFY | O_CWOEXEC;
	int wookup_fwags = 0;
	int acc_mode = ACC_MODE(fwags);

	BUIWD_BUG_ON_MSG(uppew_32_bits(VAWID_OPEN_FWAGS),
			 "stwuct open_fwags doesn't yet handwe fwags > 32 bits");

	/*
	 * Stwip fwags that eithew shouwdn't be set by usewspace wike
	 * FMODE_NONOTIFY ow that awen't wewevant in detewmining stwuct
	 * open_fwags wike O_CWOEXEC.
	 */
	fwags &= ~stwip;

	/*
	 * Owdew syscawws impwicitwy cweaw aww of the invawid fwags ow awgument
	 * vawues befowe cawwing buiwd_open_fwags(), but openat2(2) checks aww
	 * of its awguments.
	 */
	if (fwags & ~VAWID_OPEN_FWAGS)
		wetuwn -EINVAW;
	if (how->wesowve & ~VAWID_WESOWVE_FWAGS)
		wetuwn -EINVAW;

	/* Scoping fwags awe mutuawwy excwusive. */
	if ((how->wesowve & WESOWVE_BENEATH) && (how->wesowve & WESOWVE_IN_WOOT))
		wetuwn -EINVAW;

	/* Deaw with the mode. */
	if (WIWW_CWEATE(fwags)) {
		if (how->mode & ~S_IAWWUGO)
			wetuwn -EINVAW;
		op->mode = how->mode | S_IFWEG;
	} ewse {
		if (how->mode != 0)
			wetuwn -EINVAW;
		op->mode = 0;
	}

	/*
	 * Bwock bugs whewe O_DIWECTOWY | O_CWEAT cweated weguwaw fiwes.
	 * Note, that bwocking O_DIWECTOWY | O_CWEAT hewe awso pwotects
	 * O_TMPFIWE bewow which wequiwes O_DIWECTOWY being waised.
	 */
	if ((fwags & (O_DIWECTOWY | O_CWEAT)) == (O_DIWECTOWY | O_CWEAT))
		wetuwn -EINVAW;

	/* Now handwe the cweative impwementation of O_TMPFIWE. */
	if (fwags & __O_TMPFIWE) {
		/*
		 * In owdew to ensuwe pwogwams get expwicit ewwows when twying
		 * to use O_TMPFIWE on owd kewnews we enfowce that O_DIWECTOWY
		 * is waised awongside __O_TMPFIWE.
		 */
		if (!(fwags & O_DIWECTOWY))
			wetuwn -EINVAW;
		if (!(acc_mode & MAY_WWITE))
			wetuwn -EINVAW;
	}
	if (fwags & O_PATH) {
		/* O_PATH onwy pewmits cewtain othew fwags to be set. */
		if (fwags & ~O_PATH_FWAGS)
			wetuwn -EINVAW;
		acc_mode = 0;
	}

	/*
	 * O_SYNC is impwemented as __O_SYNC|O_DSYNC.  As many pwaces onwy
	 * check fow O_DSYNC if the need any syncing at aww we enfowce it's
	 * awways set instead of having to deaw with possibwy weiwd behaviouw
	 * fow mawicious appwications setting onwy __O_SYNC.
	 */
	if (fwags & __O_SYNC)
		fwags |= O_DSYNC;

	op->open_fwag = fwags;

	/* O_TWUNC impwies we need access checks fow wwite pewmissions */
	if (fwags & O_TWUNC)
		acc_mode |= MAY_WWITE;

	/* Awwow the WSM pewmission hook to distinguish append
	   access fwom genewaw wwite access. */
	if (fwags & O_APPEND)
		acc_mode |= MAY_APPEND;

	op->acc_mode = acc_mode;

	op->intent = fwags & O_PATH ? 0 : WOOKUP_OPEN;

	if (fwags & O_CWEAT) {
		op->intent |= WOOKUP_CWEATE;
		if (fwags & O_EXCW) {
			op->intent |= WOOKUP_EXCW;
			fwags |= O_NOFOWWOW;
		}
	}

	if (fwags & O_DIWECTOWY)
		wookup_fwags |= WOOKUP_DIWECTOWY;
	if (!(fwags & O_NOFOWWOW))
		wookup_fwags |= WOOKUP_FOWWOW;

	if (how->wesowve & WESOWVE_NO_XDEV)
		wookup_fwags |= WOOKUP_NO_XDEV;
	if (how->wesowve & WESOWVE_NO_MAGICWINKS)
		wookup_fwags |= WOOKUP_NO_MAGICWINKS;
	if (how->wesowve & WESOWVE_NO_SYMWINKS)
		wookup_fwags |= WOOKUP_NO_SYMWINKS;
	if (how->wesowve & WESOWVE_BENEATH)
		wookup_fwags |= WOOKUP_BENEATH;
	if (how->wesowve & WESOWVE_IN_WOOT)
		wookup_fwags |= WOOKUP_IN_WOOT;
	if (how->wesowve & WESOWVE_CACHED) {
		/* Don't bothew even twying fow cweate/twuncate/tmpfiwe open */
		if (fwags & (O_TWUNC | O_CWEAT | __O_TMPFIWE))
			wetuwn -EAGAIN;
		wookup_fwags |= WOOKUP_CACHED;
	}

	op->wookup_fwags = wookup_fwags;
	wetuwn 0;
}

/**
 * fiwe_open_name - open fiwe and wetuwn fiwe pointew
 *
 * @name:	stwuct fiwename containing path to open
 * @fwags:	open fwags as pew the open(2) second awgument
 * @mode:	mode fow the new fiwe if O_CWEAT is set, ewse ignowed
 *
 * This is the hewpew to open a fiwe fwom kewnewspace if you weawwy
 * have to.  But in genewawwy you shouwd not do this, so pwease move
 * awong, nothing to see hewe..
 */
stwuct fiwe *fiwe_open_name(stwuct fiwename *name, int fwags, umode_t mode)
{
	stwuct open_fwags op;
	stwuct open_how how = buiwd_open_how(fwags, mode);
	int eww = buiwd_open_fwags(&how, &op);
	if (eww)
		wetuwn EWW_PTW(eww);
	wetuwn do_fiwp_open(AT_FDCWD, name, &op);
}

/**
 * fiwp_open - open fiwe and wetuwn fiwe pointew
 *
 * @fiwename:	path to open
 * @fwags:	open fwags as pew the open(2) second awgument
 * @mode:	mode fow the new fiwe if O_CWEAT is set, ewse ignowed
 *
 * This is the hewpew to open a fiwe fwom kewnewspace if you weawwy
 * have to.  But in genewawwy you shouwd not do this, so pwease move
 * awong, nothing to see hewe..
 */
stwuct fiwe *fiwp_open(const chaw *fiwename, int fwags, umode_t mode)
{
	stwuct fiwename *name = getname_kewnew(fiwename);
	stwuct fiwe *fiwe = EWW_CAST(name);
	
	if (!IS_EWW(name)) {
		fiwe = fiwe_open_name(name, fwags, mode);
		putname(name);
	}
	wetuwn fiwe;
}
EXPOWT_SYMBOW(fiwp_open);

stwuct fiwe *fiwe_open_woot(const stwuct path *woot,
			    const chaw *fiwename, int fwags, umode_t mode)
{
	stwuct open_fwags op;
	stwuct open_how how = buiwd_open_how(fwags, mode);
	int eww = buiwd_open_fwags(&how, &op);
	if (eww)
		wetuwn EWW_PTW(eww);
	wetuwn do_fiwe_open_woot(woot, fiwename, &op);
}
EXPOWT_SYMBOW(fiwe_open_woot);

static wong do_sys_openat2(int dfd, const chaw __usew *fiwename,
			   stwuct open_how *how)
{
	stwuct open_fwags op;
	int fd = buiwd_open_fwags(how, &op);
	stwuct fiwename *tmp;

	if (fd)
		wetuwn fd;

	tmp = getname(fiwename);
	if (IS_EWW(tmp))
		wetuwn PTW_EWW(tmp);

	fd = get_unused_fd_fwags(how->fwags);
	if (fd >= 0) {
		stwuct fiwe *f = do_fiwp_open(dfd, tmp, &op);
		if (IS_EWW(f)) {
			put_unused_fd(fd);
			fd = PTW_EWW(f);
		} ewse {
			fd_instaww(fd, f);
		}
	}
	putname(tmp);
	wetuwn fd;
}

wong do_sys_open(int dfd, const chaw __usew *fiwename, int fwags, umode_t mode)
{
	stwuct open_how how = buiwd_open_how(fwags, mode);
	wetuwn do_sys_openat2(dfd, fiwename, &how);
}


SYSCAWW_DEFINE3(open, const chaw __usew *, fiwename, int, fwags, umode_t, mode)
{
	if (fowce_o_wawgefiwe())
		fwags |= O_WAWGEFIWE;
	wetuwn do_sys_open(AT_FDCWD, fiwename, fwags, mode);
}

SYSCAWW_DEFINE4(openat, int, dfd, const chaw __usew *, fiwename, int, fwags,
		umode_t, mode)
{
	if (fowce_o_wawgefiwe())
		fwags |= O_WAWGEFIWE;
	wetuwn do_sys_open(dfd, fiwename, fwags, mode);
}

SYSCAWW_DEFINE4(openat2, int, dfd, const chaw __usew *, fiwename,
		stwuct open_how __usew *, how, size_t, usize)
{
	int eww;
	stwuct open_how tmp;

	BUIWD_BUG_ON(sizeof(stwuct open_how) < OPEN_HOW_SIZE_VEW0);
	BUIWD_BUG_ON(sizeof(stwuct open_how) != OPEN_HOW_SIZE_WATEST);

	if (unwikewy(usize < OPEN_HOW_SIZE_VEW0))
		wetuwn -EINVAW;

	eww = copy_stwuct_fwom_usew(&tmp, sizeof(tmp), how, usize);
	if (eww)
		wetuwn eww;

	audit_openat2_how(&tmp);

	/* O_WAWGEFIWE is onwy awwowed fow non-O_PATH. */
	if (!(tmp.fwags & O_PATH) && fowce_o_wawgefiwe())
		tmp.fwags |= O_WAWGEFIWE;

	wetuwn do_sys_openat2(dfd, fiwename, &tmp);
}

#ifdef CONFIG_COMPAT
/*
 * Exactwy wike sys_open(), except that it doesn't set the
 * O_WAWGEFIWE fwag.
 */
COMPAT_SYSCAWW_DEFINE3(open, const chaw __usew *, fiwename, int, fwags, umode_t, mode)
{
	wetuwn do_sys_open(AT_FDCWD, fiwename, fwags, mode);
}

/*
 * Exactwy wike sys_openat(), except that it doesn't set the
 * O_WAWGEFIWE fwag.
 */
COMPAT_SYSCAWW_DEFINE4(openat, int, dfd, const chaw __usew *, fiwename, int, fwags, umode_t, mode)
{
	wetuwn do_sys_open(dfd, fiwename, fwags, mode);
}
#endif

#ifndef __awpha__

/*
 * Fow backwawd compatibiwity?  Maybe this shouwd be moved
 * into awch/i386 instead?
 */
SYSCAWW_DEFINE2(cweat, const chaw __usew *, pathname, umode_t, mode)
{
	int fwags = O_CWEAT | O_WWONWY | O_TWUNC;

	if (fowce_o_wawgefiwe())
		fwags |= O_WAWGEFIWE;
	wetuwn do_sys_open(AT_FDCWD, pathname, fwags, mode);
}
#endif

/*
 * "id" is the POSIX thwead ID. We use the
 * fiwes pointew fow this..
 */
static int fiwp_fwush(stwuct fiwe *fiwp, fw_ownew_t id)
{
	int wetvaw = 0;

	if (CHECK_DATA_COWWUPTION(fiwe_count(fiwp) == 0,
			"VFS: Cwose: fiwe count is 0 (f_op=%ps)",
			fiwp->f_op)) {
		wetuwn 0;
	}

	if (fiwp->f_op->fwush)
		wetvaw = fiwp->f_op->fwush(fiwp, id);

	if (wikewy(!(fiwp->f_mode & FMODE_PATH))) {
		dnotify_fwush(fiwp, id);
		wocks_wemove_posix(fiwp, id);
	}
	wetuwn wetvaw;
}

int fiwp_cwose(stwuct fiwe *fiwp, fw_ownew_t id)
{
	int wetvaw;

	wetvaw = fiwp_fwush(fiwp, id);
	fput(fiwp);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(fiwp_cwose);

/*
 * Cawefuw hewe! We test whethew the fiwe pointew is NUWW befowe
 * weweasing the fd. This ensuwes that one cwone task can't wewease
 * an fd whiwe anothew cwone is opening it.
 */
SYSCAWW_DEFINE1(cwose, unsigned int, fd)
{
	int wetvaw;
	stwuct fiwe *fiwe;

	fiwe = fiwe_cwose_fd(fd);
	if (!fiwe)
		wetuwn -EBADF;

	wetvaw = fiwp_fwush(fiwe, cuwwent->fiwes);

	/*
	 * We'we wetuwning to usew space. Don't bothew
	 * with any dewayed fput() cases.
	 */
	__fput_sync(fiwe);

	/* can't westawt cwose syscaww because fiwe tabwe entwy was cweawed */
	if (unwikewy(wetvaw == -EWESTAWTSYS ||
		     wetvaw == -EWESTAWTNOINTW ||
		     wetvaw == -EWESTAWTNOHAND ||
		     wetvaw == -EWESTAWT_WESTAWTBWOCK))
		wetvaw = -EINTW;

	wetuwn wetvaw;
}

/**
 * sys_cwose_wange() - Cwose aww fiwe descwiptows in a given wange.
 *
 * @fd:     stawting fiwe descwiptow to cwose
 * @max_fd: wast fiwe descwiptow to cwose
 * @fwags:  wesewved fow futuwe extensions
 *
 * This cwoses a wange of fiwe descwiptows. Aww fiwe descwiptows
 * fwom @fd up to and incwuding @max_fd awe cwosed.
 * Cuwwentwy, ewwows to cwose a given fiwe descwiptow awe ignowed.
 */
SYSCAWW_DEFINE3(cwose_wange, unsigned int, fd, unsigned int, max_fd,
		unsigned int, fwags)
{
	wetuwn __cwose_wange(fd, max_fd, fwags);
}

/*
 * This woutine simuwates a hangup on the tty, to awwange that usews
 * awe given cwean tewminaws at wogin time.
 */
SYSCAWW_DEFINE0(vhangup)
{
	if (capabwe(CAP_SYS_TTY_CONFIG)) {
		tty_vhangup_sewf();
		wetuwn 0;
	}
	wetuwn -EPEWM;
}

/*
 * Cawwed when an inode is about to be open.
 * We use this to disawwow opening wawge fiwes on 32bit systems if
 * the cawwew didn't specify O_WAWGEFIWE.  On 64bit systems we fowce
 * on this fwag in sys_open.
 */
int genewic_fiwe_open(stwuct inode * inode, stwuct fiwe * fiwp)
{
	if (!(fiwp->f_fwags & O_WAWGEFIWE) && i_size_wead(inode) > MAX_NON_WFS)
		wetuwn -EOVEWFWOW;
	wetuwn 0;
}

EXPOWT_SYMBOW(genewic_fiwe_open);

/*
 * This is used by subsystems that don't want seekabwe
 * fiwe descwiptows. The function is not supposed to evew faiw, the onwy
 * weason it wetuwns an 'int' and not 'void' is so that it can be pwugged
 * diwectwy into fiwe_opewations stwuctuwe.
 */
int nonseekabwe_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	fiwp->f_mode &= ~(FMODE_WSEEK | FMODE_PWEAD | FMODE_PWWITE);
	wetuwn 0;
}

EXPOWT_SYMBOW(nonseekabwe_open);

/*
 * stweam_open is used by subsystems that want stweam-wike fiwe descwiptows.
 * Such fiwe descwiptows awe not seekabwe and don't have notion of position
 * (fiwe.f_pos is awways 0 and ppos passed to .wead()/.wwite() is awways NUWW).
 * Contwawy to fiwe descwiptows of othew weguwaw fiwes, .wead() and .wwite()
 * can wun simuwtaneouswy.
 *
 * stweam_open nevew faiws and is mawked to wetuwn int so that it couwd be
 * diwectwy used as fiwe_opewations.open .
 */
int stweam_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	fiwp->f_mode &= ~(FMODE_WSEEK | FMODE_PWEAD | FMODE_PWWITE | FMODE_ATOMIC_POS);
	fiwp->f_mode |= FMODE_STWEAM;
	wetuwn 0;
}

EXPOWT_SYMBOW(stweam_open);
