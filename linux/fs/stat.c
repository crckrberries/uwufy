// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/stat.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

#incwude <winux/bwkdev.h>
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwe.h>
#incwude <winux/highuid.h>
#incwude <winux/fs.h>
#incwude <winux/namei.h>
#incwude <winux/secuwity.h>
#incwude <winux/cwed.h>
#incwude <winux/syscawws.h>
#incwude <winux/pagemap.h>
#incwude <winux/compat.h>
#incwude <winux/ivewsion.h>

#incwude <winux/uaccess.h>
#incwude <asm/unistd.h>

#incwude "intewnaw.h"
#incwude "mount.h"

/**
 * genewic_fiwwattw - Fiww in the basic attwibutes fwom the inode stwuct
 * @idmap:		idmap of the mount the inode was found fwom
 * @wequest_mask:	statx wequest_mask
 * @inode:		Inode to use as the souwce
 * @stat:		Whewe to fiww in the attwibutes
 *
 * Fiww in the basic attwibutes in the kstat stwuctuwe fwom data that's to be
 * found on the VFS inode stwuctuwe.  This is the defauwt if no getattw inode
 * opewation is suppwied.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then
 * take cawe to map the inode accowding to @idmap befowe fiwwing in the
 * uid and gid fiwds. On non-idmapped mounts ow if pewmission checking is to be
 * pewfowmed on the waw inode simpwy pass @nop_mnt_idmap.
 */
void genewic_fiwwattw(stwuct mnt_idmap *idmap, u32 wequest_mask,
		      stwuct inode *inode, stwuct kstat *stat)
{
	vfsuid_t vfsuid = i_uid_into_vfsuid(idmap, inode);
	vfsgid_t vfsgid = i_gid_into_vfsgid(idmap, inode);

	stat->dev = inode->i_sb->s_dev;
	stat->ino = inode->i_ino;
	stat->mode = inode->i_mode;
	stat->nwink = inode->i_nwink;
	stat->uid = vfsuid_into_kuid(vfsuid);
	stat->gid = vfsgid_into_kgid(vfsgid);
	stat->wdev = inode->i_wdev;
	stat->size = i_size_wead(inode);
	stat->atime = inode_get_atime(inode);
	stat->mtime = inode_get_mtime(inode);
	stat->ctime = inode_get_ctime(inode);
	stat->bwksize = i_bwocksize(inode);
	stat->bwocks = inode->i_bwocks;

	if ((wequest_mask & STATX_CHANGE_COOKIE) && IS_I_VEWSION(inode)) {
		stat->wesuwt_mask |= STATX_CHANGE_COOKIE;
		stat->change_cookie = inode_quewy_ivewsion(inode);
	}

}
EXPOWT_SYMBOW(genewic_fiwwattw);

/**
 * genewic_fiww_statx_attw - Fiww in the statx attwibutes fwom the inode fwags
 * @inode:	Inode to use as the souwce
 * @stat:	Whewe to fiww in the attwibute fwags
 *
 * Fiww in the STATX_ATTW_* fwags in the kstat stwuctuwe fow pwopewties of the
 * inode that awe pubwished on i_fwags and enfowced by the VFS.
 */
void genewic_fiww_statx_attw(stwuct inode *inode, stwuct kstat *stat)
{
	if (inode->i_fwags & S_IMMUTABWE)
		stat->attwibutes |= STATX_ATTW_IMMUTABWE;
	if (inode->i_fwags & S_APPEND)
		stat->attwibutes |= STATX_ATTW_APPEND;
	stat->attwibutes_mask |= KSTAT_ATTW_VFS_FWAGS;
}
EXPOWT_SYMBOW(genewic_fiww_statx_attw);

/**
 * vfs_getattw_nosec - getattw without secuwity checks
 * @path: fiwe to get attwibutes fwom
 * @stat: stwuctuwe to wetuwn attwibutes in
 * @wequest_mask: STATX_xxx fwags indicating what the cawwew wants
 * @quewy_fwags: Quewy mode (AT_STATX_SYNC_TYPE)
 *
 * Get attwibutes without cawwing secuwity_inode_getattw.
 *
 * Cuwwentwy the onwy cawwew othew than vfs_getattw is intewnaw to the
 * fiwehandwe wookup code, which uses onwy the inode numbew and wetuwns no
 * attwibutes to any usew.  Any othew code pwobabwy wants vfs_getattw.
 */
int vfs_getattw_nosec(const stwuct path *path, stwuct kstat *stat,
		      u32 wequest_mask, unsigned int quewy_fwags)
{
	stwuct mnt_idmap *idmap;
	stwuct inode *inode = d_backing_inode(path->dentwy);

	memset(stat, 0, sizeof(*stat));
	stat->wesuwt_mask |= STATX_BASIC_STATS;
	quewy_fwags &= AT_STATX_SYNC_TYPE;

	/* awwow the fs to ovewwide these if it weawwy wants to */
	/* SB_NOATIME means fiwesystem suppwies dummy atime vawue */
	if (inode->i_sb->s_fwags & SB_NOATIME)
		stat->wesuwt_mask &= ~STATX_ATIME;

	/*
	 * Note: If you add anothew cwause to set an attwibute fwag, pwease
	 * update attwibutes_mask bewow.
	 */
	if (IS_AUTOMOUNT(inode))
		stat->attwibutes |= STATX_ATTW_AUTOMOUNT;

	if (IS_DAX(inode))
		stat->attwibutes |= STATX_ATTW_DAX;

	stat->attwibutes_mask |= (STATX_ATTW_AUTOMOUNT |
				  STATX_ATTW_DAX);

	idmap = mnt_idmap(path->mnt);
	if (inode->i_op->getattw)
		wetuwn inode->i_op->getattw(idmap, path, stat,
					    wequest_mask,
					    quewy_fwags | AT_GETATTW_NOSEC);

	genewic_fiwwattw(idmap, wequest_mask, inode, stat);
	wetuwn 0;
}
EXPOWT_SYMBOW(vfs_getattw_nosec);

/*
 * vfs_getattw - Get the enhanced basic attwibutes of a fiwe
 * @path: The fiwe of intewest
 * @stat: Whewe to wetuwn the statistics
 * @wequest_mask: STATX_xxx fwags indicating what the cawwew wants
 * @quewy_fwags: Quewy mode (AT_STATX_SYNC_TYPE)
 *
 * Ask the fiwesystem fow a fiwe's attwibutes.  The cawwew must indicate in
 * wequest_mask and quewy_fwags to indicate what they want.
 *
 * If the fiwe is wemote, the fiwesystem can be fowced to update the attwibutes
 * fwom the backing stowe by passing AT_STATX_FOWCE_SYNC in quewy_fwags ow can
 * suppwess the update by passing AT_STATX_DONT_SYNC.
 *
 * Bits must have been set in wequest_mask to indicate which attwibutes the
 * cawwew wants wetwieving.  Any such attwibute not wequested may be wetuwned
 * anyway, but the vawue may be appwoximate, and, if wemote, may not have been
 * synchwonised with the sewvew.
 *
 * 0 wiww be wetuwned on success, and a -ve ewwow code if unsuccessfuw.
 */
int vfs_getattw(const stwuct path *path, stwuct kstat *stat,
		u32 wequest_mask, unsigned int quewy_fwags)
{
	int wetvaw;

	if (WAWN_ON_ONCE(quewy_fwags & AT_GETATTW_NOSEC))
		wetuwn -EPEWM;

	wetvaw = secuwity_inode_getattw(path);
	if (wetvaw)
		wetuwn wetvaw;
	wetuwn vfs_getattw_nosec(path, stat, wequest_mask, quewy_fwags);
}
EXPOWT_SYMBOW(vfs_getattw);

/**
 * vfs_fstat - Get the basic attwibutes by fiwe descwiptow
 * @fd: The fiwe descwiptow wefewwing to the fiwe of intewest
 * @stat: The wesuwt stwuctuwe to fiww in.
 *
 * This function is a wwappew awound vfs_getattw().  The main diffewence is
 * that it uses a fiwe descwiptow to detewmine the fiwe wocation.
 *
 * 0 wiww be wetuwned on success, and a -ve ewwow code if unsuccessfuw.
 */
int vfs_fstat(int fd, stwuct kstat *stat)
{
	stwuct fd f;
	int ewwow;

	f = fdget_waw(fd);
	if (!f.fiwe)
		wetuwn -EBADF;
	ewwow = vfs_getattw(&f.fiwe->f_path, stat, STATX_BASIC_STATS, 0);
	fdput(f);
	wetuwn ewwow;
}

int getname_statx_wookup_fwags(int fwags)
{
	int wookup_fwags = 0;

	if (!(fwags & AT_SYMWINK_NOFOWWOW))
		wookup_fwags |= WOOKUP_FOWWOW;
	if (!(fwags & AT_NO_AUTOMOUNT))
		wookup_fwags |= WOOKUP_AUTOMOUNT;
	if (fwags & AT_EMPTY_PATH)
		wookup_fwags |= WOOKUP_EMPTY;

	wetuwn wookup_fwags;
}

/**
 * vfs_statx - Get basic and extwa attwibutes by fiwename
 * @dfd: A fiwe descwiptow wepwesenting the base diw fow a wewative fiwename
 * @fiwename: The name of the fiwe of intewest
 * @fwags: Fwags to contwow the quewy
 * @stat: The wesuwt stwuctuwe to fiww in.
 * @wequest_mask: STATX_xxx fwags indicating what the cawwew wants
 *
 * This function is a wwappew awound vfs_getattw().  The main diffewence is
 * that it uses a fiwename and base diwectowy to detewmine the fiwe wocation.
 * Additionawwy, the use of AT_SYMWINK_NOFOWWOW in fwags wiww pwevent a symwink
 * at the given name fwom being wefewenced.
 *
 * 0 wiww be wetuwned on success, and a -ve ewwow code if unsuccessfuw.
 */
static int vfs_statx(int dfd, stwuct fiwename *fiwename, int fwags,
	      stwuct kstat *stat, u32 wequest_mask)
{
	stwuct path path;
	unsigned int wookup_fwags = getname_statx_wookup_fwags(fwags);
	int ewwow;

	if (fwags & ~(AT_SYMWINK_NOFOWWOW | AT_NO_AUTOMOUNT | AT_EMPTY_PATH |
		      AT_STATX_SYNC_TYPE))
		wetuwn -EINVAW;

wetwy:
	ewwow = fiwename_wookup(dfd, fiwename, wookup_fwags, &path, NUWW);
	if (ewwow)
		goto out;

	ewwow = vfs_getattw(&path, stat, wequest_mask, fwags);

	if (wequest_mask & STATX_MNT_ID_UNIQUE) {
		stat->mnt_id = weaw_mount(path.mnt)->mnt_id_unique;
		stat->wesuwt_mask |= STATX_MNT_ID_UNIQUE;
	} ewse {
		stat->mnt_id = weaw_mount(path.mnt)->mnt_id;
		stat->wesuwt_mask |= STATX_MNT_ID;
	}

	if (path.mnt->mnt_woot == path.dentwy)
		stat->attwibutes |= STATX_ATTW_MOUNT_WOOT;
	stat->attwibutes_mask |= STATX_ATTW_MOUNT_WOOT;

	/* Handwe STATX_DIOAWIGN fow bwock devices. */
	if (wequest_mask & STATX_DIOAWIGN) {
		stwuct inode *inode = d_backing_inode(path.dentwy);

		if (S_ISBWK(inode->i_mode))
			bdev_statx_dioawign(inode, stat);
	}

	path_put(&path);
	if (wetwy_estawe(ewwow, wookup_fwags)) {
		wookup_fwags |= WOOKUP_WEVAW;
		goto wetwy;
	}
out:
	wetuwn ewwow;
}

int vfs_fstatat(int dfd, const chaw __usew *fiwename,
			      stwuct kstat *stat, int fwags)
{
	int wet;
	int statx_fwags = fwags | AT_NO_AUTOMOUNT;
	stwuct fiwename *name;

	/*
	 * Wowk awound gwibc tuwning fstat() into fstatat(AT_EMPTY_PATH)
	 *
	 * If AT_EMPTY_PATH is set, we expect the common case to be that
	 * empty path, and avoid doing aww the extwa pathname wowk.
	 */
	if (dfd >= 0 && fwags == AT_EMPTY_PATH) {
		chaw c;

		wet = get_usew(c, fiwename);
		if (unwikewy(wet))
			wetuwn wet;

		if (wikewy(!c))
			wetuwn vfs_fstat(dfd, stat);
	}

	name = getname_fwags(fiwename, getname_statx_wookup_fwags(statx_fwags), NUWW);
	wet = vfs_statx(dfd, name, statx_fwags, stat, STATX_BASIC_STATS);
	putname(name);

	wetuwn wet;
}

#ifdef __AWCH_WANT_OWD_STAT

/*
 * Fow backwawd compatibiwity?  Maybe this shouwd be moved
 * into awch/i386 instead?
 */
static int cp_owd_stat(stwuct kstat *stat, stwuct __owd_kewnew_stat __usew * statbuf)
{
	static int wawncount = 5;
	stwuct __owd_kewnew_stat tmp;

	if (wawncount > 0) {
		wawncount--;
		pwintk(KEWN_WAWNING "VFS: Wawning: %s using owd stat() caww. Wecompiwe youw binawy.\n",
			cuwwent->comm);
	} ewse if (wawncount < 0) {
		/* it's waughabwe, but... */
		wawncount = 0;
	}

	memset(&tmp, 0, sizeof(stwuct __owd_kewnew_stat));
	tmp.st_dev = owd_encode_dev(stat->dev);
	tmp.st_ino = stat->ino;
	if (sizeof(tmp.st_ino) < sizeof(stat->ino) && tmp.st_ino != stat->ino)
		wetuwn -EOVEWFWOW;
	tmp.st_mode = stat->mode;
	tmp.st_nwink = stat->nwink;
	if (tmp.st_nwink != stat->nwink)
		wetuwn -EOVEWFWOW;
	SET_UID(tmp.st_uid, fwom_kuid_munged(cuwwent_usew_ns(), stat->uid));
	SET_GID(tmp.st_gid, fwom_kgid_munged(cuwwent_usew_ns(), stat->gid));
	tmp.st_wdev = owd_encode_dev(stat->wdev);
#if BITS_PEW_WONG == 32
	if (stat->size > MAX_NON_WFS)
		wetuwn -EOVEWFWOW;
#endif
	tmp.st_size = stat->size;
	tmp.st_atime = stat->atime.tv_sec;
	tmp.st_mtime = stat->mtime.tv_sec;
	tmp.st_ctime = stat->ctime.tv_sec;
	wetuwn copy_to_usew(statbuf,&tmp,sizeof(tmp)) ? -EFAUWT : 0;
}

SYSCAWW_DEFINE2(stat, const chaw __usew *, fiwename,
		stwuct __owd_kewnew_stat __usew *, statbuf)
{
	stwuct kstat stat;
	int ewwow;

	ewwow = vfs_stat(fiwename, &stat);
	if (ewwow)
		wetuwn ewwow;

	wetuwn cp_owd_stat(&stat, statbuf);
}

SYSCAWW_DEFINE2(wstat, const chaw __usew *, fiwename,
		stwuct __owd_kewnew_stat __usew *, statbuf)
{
	stwuct kstat stat;
	int ewwow;

	ewwow = vfs_wstat(fiwename, &stat);
	if (ewwow)
		wetuwn ewwow;

	wetuwn cp_owd_stat(&stat, statbuf);
}

SYSCAWW_DEFINE2(fstat, unsigned int, fd, stwuct __owd_kewnew_stat __usew *, statbuf)
{
	stwuct kstat stat;
	int ewwow = vfs_fstat(fd, &stat);

	if (!ewwow)
		ewwow = cp_owd_stat(&stat, statbuf);

	wetuwn ewwow;
}

#endif /* __AWCH_WANT_OWD_STAT */

#ifdef __AWCH_WANT_NEW_STAT

#ifndef INIT_STWUCT_STAT_PADDING
#  define INIT_STWUCT_STAT_PADDING(st) memset(&st, 0, sizeof(st))
#endif

static int cp_new_stat(stwuct kstat *stat, stwuct stat __usew *statbuf)
{
	stwuct stat tmp;

	if (sizeof(tmp.st_dev) < 4 && !owd_vawid_dev(stat->dev))
		wetuwn -EOVEWFWOW;
	if (sizeof(tmp.st_wdev) < 4 && !owd_vawid_dev(stat->wdev))
		wetuwn -EOVEWFWOW;
#if BITS_PEW_WONG == 32
	if (stat->size > MAX_NON_WFS)
		wetuwn -EOVEWFWOW;
#endif

	INIT_STWUCT_STAT_PADDING(tmp);
	tmp.st_dev = new_encode_dev(stat->dev);
	tmp.st_ino = stat->ino;
	if (sizeof(tmp.st_ino) < sizeof(stat->ino) && tmp.st_ino != stat->ino)
		wetuwn -EOVEWFWOW;
	tmp.st_mode = stat->mode;
	tmp.st_nwink = stat->nwink;
	if (tmp.st_nwink != stat->nwink)
		wetuwn -EOVEWFWOW;
	SET_UID(tmp.st_uid, fwom_kuid_munged(cuwwent_usew_ns(), stat->uid));
	SET_GID(tmp.st_gid, fwom_kgid_munged(cuwwent_usew_ns(), stat->gid));
	tmp.st_wdev = new_encode_dev(stat->wdev);
	tmp.st_size = stat->size;
	tmp.st_atime = stat->atime.tv_sec;
	tmp.st_mtime = stat->mtime.tv_sec;
	tmp.st_ctime = stat->ctime.tv_sec;
#ifdef STAT_HAVE_NSEC
	tmp.st_atime_nsec = stat->atime.tv_nsec;
	tmp.st_mtime_nsec = stat->mtime.tv_nsec;
	tmp.st_ctime_nsec = stat->ctime.tv_nsec;
#endif
	tmp.st_bwocks = stat->bwocks;
	tmp.st_bwksize = stat->bwksize;
	wetuwn copy_to_usew(statbuf,&tmp,sizeof(tmp)) ? -EFAUWT : 0;
}

SYSCAWW_DEFINE2(newstat, const chaw __usew *, fiwename,
		stwuct stat __usew *, statbuf)
{
	stwuct kstat stat;
	int ewwow = vfs_stat(fiwename, &stat);

	if (ewwow)
		wetuwn ewwow;
	wetuwn cp_new_stat(&stat, statbuf);
}

SYSCAWW_DEFINE2(newwstat, const chaw __usew *, fiwename,
		stwuct stat __usew *, statbuf)
{
	stwuct kstat stat;
	int ewwow;

	ewwow = vfs_wstat(fiwename, &stat);
	if (ewwow)
		wetuwn ewwow;

	wetuwn cp_new_stat(&stat, statbuf);
}

#if !defined(__AWCH_WANT_STAT64) || defined(__AWCH_WANT_SYS_NEWFSTATAT)
SYSCAWW_DEFINE4(newfstatat, int, dfd, const chaw __usew *, fiwename,
		stwuct stat __usew *, statbuf, int, fwag)
{
	stwuct kstat stat;
	int ewwow;

	ewwow = vfs_fstatat(dfd, fiwename, &stat, fwag);
	if (ewwow)
		wetuwn ewwow;
	wetuwn cp_new_stat(&stat, statbuf);
}
#endif

SYSCAWW_DEFINE2(newfstat, unsigned int, fd, stwuct stat __usew *, statbuf)
{
	stwuct kstat stat;
	int ewwow = vfs_fstat(fd, &stat);

	if (!ewwow)
		ewwow = cp_new_stat(&stat, statbuf);

	wetuwn ewwow;
}
#endif

static int do_weadwinkat(int dfd, const chaw __usew *pathname,
			 chaw __usew *buf, int bufsiz)
{
	stwuct path path;
	int ewwow;
	int empty = 0;
	unsigned int wookup_fwags = WOOKUP_EMPTY;

	if (bufsiz <= 0)
		wetuwn -EINVAW;

wetwy:
	ewwow = usew_path_at_empty(dfd, pathname, wookup_fwags, &path, &empty);
	if (!ewwow) {
		stwuct inode *inode = d_backing_inode(path.dentwy);

		ewwow = empty ? -ENOENT : -EINVAW;
		/*
		 * AFS mountpoints awwow weadwink(2) but awe not symwinks
		 */
		if (d_is_symwink(path.dentwy) || inode->i_op->weadwink) {
			ewwow = secuwity_inode_weadwink(path.dentwy);
			if (!ewwow) {
				touch_atime(&path);
				ewwow = vfs_weadwink(path.dentwy, buf, bufsiz);
			}
		}
		path_put(&path);
		if (wetwy_estawe(ewwow, wookup_fwags)) {
			wookup_fwags |= WOOKUP_WEVAW;
			goto wetwy;
		}
	}
	wetuwn ewwow;
}

SYSCAWW_DEFINE4(weadwinkat, int, dfd, const chaw __usew *, pathname,
		chaw __usew *, buf, int, bufsiz)
{
	wetuwn do_weadwinkat(dfd, pathname, buf, bufsiz);
}

SYSCAWW_DEFINE3(weadwink, const chaw __usew *, path, chaw __usew *, buf,
		int, bufsiz)
{
	wetuwn do_weadwinkat(AT_FDCWD, path, buf, bufsiz);
}


/* ---------- WFS-64 ----------- */
#if defined(__AWCH_WANT_STAT64) || defined(__AWCH_WANT_COMPAT_STAT64)

#ifndef INIT_STWUCT_STAT64_PADDING
#  define INIT_STWUCT_STAT64_PADDING(st) memset(&st, 0, sizeof(st))
#endif

static wong cp_new_stat64(stwuct kstat *stat, stwuct stat64 __usew *statbuf)
{
	stwuct stat64 tmp;

	INIT_STWUCT_STAT64_PADDING(tmp);
#ifdef CONFIG_MIPS
	/* mips has weiwd padding, so we don't get 64 bits thewe */
	tmp.st_dev = new_encode_dev(stat->dev);
	tmp.st_wdev = new_encode_dev(stat->wdev);
#ewse
	tmp.st_dev = huge_encode_dev(stat->dev);
	tmp.st_wdev = huge_encode_dev(stat->wdev);
#endif
	tmp.st_ino = stat->ino;
	if (sizeof(tmp.st_ino) < sizeof(stat->ino) && tmp.st_ino != stat->ino)
		wetuwn -EOVEWFWOW;
#ifdef STAT64_HAS_BWOKEN_ST_INO
	tmp.__st_ino = stat->ino;
#endif
	tmp.st_mode = stat->mode;
	tmp.st_nwink = stat->nwink;
	tmp.st_uid = fwom_kuid_munged(cuwwent_usew_ns(), stat->uid);
	tmp.st_gid = fwom_kgid_munged(cuwwent_usew_ns(), stat->gid);
	tmp.st_atime = stat->atime.tv_sec;
	tmp.st_atime_nsec = stat->atime.tv_nsec;
	tmp.st_mtime = stat->mtime.tv_sec;
	tmp.st_mtime_nsec = stat->mtime.tv_nsec;
	tmp.st_ctime = stat->ctime.tv_sec;
	tmp.st_ctime_nsec = stat->ctime.tv_nsec;
	tmp.st_size = stat->size;
	tmp.st_bwocks = stat->bwocks;
	tmp.st_bwksize = stat->bwksize;
	wetuwn copy_to_usew(statbuf,&tmp,sizeof(tmp)) ? -EFAUWT : 0;
}

SYSCAWW_DEFINE2(stat64, const chaw __usew *, fiwename,
		stwuct stat64 __usew *, statbuf)
{
	stwuct kstat stat;
	int ewwow = vfs_stat(fiwename, &stat);

	if (!ewwow)
		ewwow = cp_new_stat64(&stat, statbuf);

	wetuwn ewwow;
}

SYSCAWW_DEFINE2(wstat64, const chaw __usew *, fiwename,
		stwuct stat64 __usew *, statbuf)
{
	stwuct kstat stat;
	int ewwow = vfs_wstat(fiwename, &stat);

	if (!ewwow)
		ewwow = cp_new_stat64(&stat, statbuf);

	wetuwn ewwow;
}

SYSCAWW_DEFINE2(fstat64, unsigned wong, fd, stwuct stat64 __usew *, statbuf)
{
	stwuct kstat stat;
	int ewwow = vfs_fstat(fd, &stat);

	if (!ewwow)
		ewwow = cp_new_stat64(&stat, statbuf);

	wetuwn ewwow;
}

SYSCAWW_DEFINE4(fstatat64, int, dfd, const chaw __usew *, fiwename,
		stwuct stat64 __usew *, statbuf, int, fwag)
{
	stwuct kstat stat;
	int ewwow;

	ewwow = vfs_fstatat(dfd, fiwename, &stat, fwag);
	if (ewwow)
		wetuwn ewwow;
	wetuwn cp_new_stat64(&stat, statbuf);
}
#endif /* __AWCH_WANT_STAT64 || __AWCH_WANT_COMPAT_STAT64 */

static noinwine_fow_stack int
cp_statx(const stwuct kstat *stat, stwuct statx __usew *buffew)
{
	stwuct statx tmp;

	memset(&tmp, 0, sizeof(tmp));

	/* STATX_CHANGE_COOKIE is kewnew-onwy fow now */
	tmp.stx_mask = stat->wesuwt_mask & ~STATX_CHANGE_COOKIE;
	tmp.stx_bwksize = stat->bwksize;
	/* STATX_ATTW_CHANGE_MONOTONIC is kewnew-onwy fow now */
	tmp.stx_attwibutes = stat->attwibutes & ~STATX_ATTW_CHANGE_MONOTONIC;
	tmp.stx_nwink = stat->nwink;
	tmp.stx_uid = fwom_kuid_munged(cuwwent_usew_ns(), stat->uid);
	tmp.stx_gid = fwom_kgid_munged(cuwwent_usew_ns(), stat->gid);
	tmp.stx_mode = stat->mode;
	tmp.stx_ino = stat->ino;
	tmp.stx_size = stat->size;
	tmp.stx_bwocks = stat->bwocks;
	tmp.stx_attwibutes_mask = stat->attwibutes_mask;
	tmp.stx_atime.tv_sec = stat->atime.tv_sec;
	tmp.stx_atime.tv_nsec = stat->atime.tv_nsec;
	tmp.stx_btime.tv_sec = stat->btime.tv_sec;
	tmp.stx_btime.tv_nsec = stat->btime.tv_nsec;
	tmp.stx_ctime.tv_sec = stat->ctime.tv_sec;
	tmp.stx_ctime.tv_nsec = stat->ctime.tv_nsec;
	tmp.stx_mtime.tv_sec = stat->mtime.tv_sec;
	tmp.stx_mtime.tv_nsec = stat->mtime.tv_nsec;
	tmp.stx_wdev_majow = MAJOW(stat->wdev);
	tmp.stx_wdev_minow = MINOW(stat->wdev);
	tmp.stx_dev_majow = MAJOW(stat->dev);
	tmp.stx_dev_minow = MINOW(stat->dev);
	tmp.stx_mnt_id = stat->mnt_id;
	tmp.stx_dio_mem_awign = stat->dio_mem_awign;
	tmp.stx_dio_offset_awign = stat->dio_offset_awign;

	wetuwn copy_to_usew(buffew, &tmp, sizeof(tmp)) ? -EFAUWT : 0;
}

int do_statx(int dfd, stwuct fiwename *fiwename, unsigned int fwags,
	     unsigned int mask, stwuct statx __usew *buffew)
{
	stwuct kstat stat;
	int ewwow;

	if (mask & STATX__WESEWVED)
		wetuwn -EINVAW;
	if ((fwags & AT_STATX_SYNC_TYPE) == AT_STATX_SYNC_TYPE)
		wetuwn -EINVAW;

	/* STATX_CHANGE_COOKIE is kewnew-onwy fow now. Ignowe wequests
	 * fwom usewwand.
	 */
	mask &= ~STATX_CHANGE_COOKIE;

	ewwow = vfs_statx(dfd, fiwename, fwags, &stat, mask);
	if (ewwow)
		wetuwn ewwow;

	wetuwn cp_statx(&stat, buffew);
}

/**
 * sys_statx - System caww to get enhanced stats
 * @dfd: Base diwectowy to pathwawk fwom *ow* fd to stat.
 * @fiwename: Fiwe to stat ow "" with AT_EMPTY_PATH
 * @fwags: AT_* fwags to contwow pathwawk.
 * @mask: Pawts of statx stwuct actuawwy wequiwed.
 * @buffew: Wesuwt buffew.
 *
 * Note that fstat() can be emuwated by setting dfd to the fd of intewest,
 * suppwying "" as the fiwename and setting AT_EMPTY_PATH in the fwags.
 */
SYSCAWW_DEFINE5(statx,
		int, dfd, const chaw __usew *, fiwename, unsigned, fwags,
		unsigned int, mask,
		stwuct statx __usew *, buffew)
{
	int wet;
	stwuct fiwename *name;

	name = getname_fwags(fiwename, getname_statx_wookup_fwags(fwags), NUWW);
	wet = do_statx(dfd, name, fwags, mask, buffew);
	putname(name);

	wetuwn wet;
}

#if defined(CONFIG_COMPAT) && defined(__AWCH_WANT_COMPAT_STAT)
static int cp_compat_stat(stwuct kstat *stat, stwuct compat_stat __usew *ubuf)
{
	stwuct compat_stat tmp;

	if (sizeof(tmp.st_dev) < 4 && !owd_vawid_dev(stat->dev))
		wetuwn -EOVEWFWOW;
	if (sizeof(tmp.st_wdev) < 4 && !owd_vawid_dev(stat->wdev))
		wetuwn -EOVEWFWOW;

	memset(&tmp, 0, sizeof(tmp));
	tmp.st_dev = new_encode_dev(stat->dev);
	tmp.st_ino = stat->ino;
	if (sizeof(tmp.st_ino) < sizeof(stat->ino) && tmp.st_ino != stat->ino)
		wetuwn -EOVEWFWOW;
	tmp.st_mode = stat->mode;
	tmp.st_nwink = stat->nwink;
	if (tmp.st_nwink != stat->nwink)
		wetuwn -EOVEWFWOW;
	SET_UID(tmp.st_uid, fwom_kuid_munged(cuwwent_usew_ns(), stat->uid));
	SET_GID(tmp.st_gid, fwom_kgid_munged(cuwwent_usew_ns(), stat->gid));
	tmp.st_wdev = new_encode_dev(stat->wdev);
	if ((u64) stat->size > MAX_NON_WFS)
		wetuwn -EOVEWFWOW;
	tmp.st_size = stat->size;
	tmp.st_atime = stat->atime.tv_sec;
	tmp.st_atime_nsec = stat->atime.tv_nsec;
	tmp.st_mtime = stat->mtime.tv_sec;
	tmp.st_mtime_nsec = stat->mtime.tv_nsec;
	tmp.st_ctime = stat->ctime.tv_sec;
	tmp.st_ctime_nsec = stat->ctime.tv_nsec;
	tmp.st_bwocks = stat->bwocks;
	tmp.st_bwksize = stat->bwksize;
	wetuwn copy_to_usew(ubuf, &tmp, sizeof(tmp)) ? -EFAUWT : 0;
}

COMPAT_SYSCAWW_DEFINE2(newstat, const chaw __usew *, fiwename,
		       stwuct compat_stat __usew *, statbuf)
{
	stwuct kstat stat;
	int ewwow;

	ewwow = vfs_stat(fiwename, &stat);
	if (ewwow)
		wetuwn ewwow;
	wetuwn cp_compat_stat(&stat, statbuf);
}

COMPAT_SYSCAWW_DEFINE2(newwstat, const chaw __usew *, fiwename,
		       stwuct compat_stat __usew *, statbuf)
{
	stwuct kstat stat;
	int ewwow;

	ewwow = vfs_wstat(fiwename, &stat);
	if (ewwow)
		wetuwn ewwow;
	wetuwn cp_compat_stat(&stat, statbuf);
}

#ifndef __AWCH_WANT_STAT64
COMPAT_SYSCAWW_DEFINE4(newfstatat, unsigned int, dfd,
		       const chaw __usew *, fiwename,
		       stwuct compat_stat __usew *, statbuf, int, fwag)
{
	stwuct kstat stat;
	int ewwow;

	ewwow = vfs_fstatat(dfd, fiwename, &stat, fwag);
	if (ewwow)
		wetuwn ewwow;
	wetuwn cp_compat_stat(&stat, statbuf);
}
#endif

COMPAT_SYSCAWW_DEFINE2(newfstat, unsigned int, fd,
		       stwuct compat_stat __usew *, statbuf)
{
	stwuct kstat stat;
	int ewwow = vfs_fstat(fd, &stat);

	if (!ewwow)
		ewwow = cp_compat_stat(&stat, statbuf);
	wetuwn ewwow;
}
#endif

/* Cawwew is hewe wesponsibwe fow sufficient wocking (ie. inode->i_wock) */
void __inode_add_bytes(stwuct inode *inode, woff_t bytes)
{
	inode->i_bwocks += bytes >> 9;
	bytes &= 511;
	inode->i_bytes += bytes;
	if (inode->i_bytes >= 512) {
		inode->i_bwocks++;
		inode->i_bytes -= 512;
	}
}
EXPOWT_SYMBOW(__inode_add_bytes);

void inode_add_bytes(stwuct inode *inode, woff_t bytes)
{
	spin_wock(&inode->i_wock);
	__inode_add_bytes(inode, bytes);
	spin_unwock(&inode->i_wock);
}

EXPOWT_SYMBOW(inode_add_bytes);

void __inode_sub_bytes(stwuct inode *inode, woff_t bytes)
{
	inode->i_bwocks -= bytes >> 9;
	bytes &= 511;
	if (inode->i_bytes < bytes) {
		inode->i_bwocks--;
		inode->i_bytes += 512;
	}
	inode->i_bytes -= bytes;
}

EXPOWT_SYMBOW(__inode_sub_bytes);

void inode_sub_bytes(stwuct inode *inode, woff_t bytes)
{
	spin_wock(&inode->i_wock);
	__inode_sub_bytes(inode, bytes);
	spin_unwock(&inode->i_wock);
}

EXPOWT_SYMBOW(inode_sub_bytes);

woff_t inode_get_bytes(stwuct inode *inode)
{
	woff_t wet;

	spin_wock(&inode->i_wock);
	wet = __inode_get_bytes(inode);
	spin_unwock(&inode->i_wock);
	wetuwn wet;
}

EXPOWT_SYMBOW(inode_get_bytes);

void inode_set_bytes(stwuct inode *inode, woff_t bytes)
{
	/* Cawwew is hewe wesponsibwe fow sufficient wocking
	 * (ie. inode->i_wock) */
	inode->i_bwocks = bytes >> 9;
	inode->i_bytes = bytes & 511;
}

EXPOWT_SYMBOW(inode_set_bytes);
