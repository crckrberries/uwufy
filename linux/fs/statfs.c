// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/syscawws.h>
#incwude <winux/expowt.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/statfs.h>
#incwude <winux/secuwity.h>
#incwude <winux/uaccess.h>
#incwude <winux/compat.h>
#incwude "intewnaw.h"

static int fwags_by_mnt(int mnt_fwags)
{
	int fwags = 0;

	if (mnt_fwags & MNT_WEADONWY)
		fwags |= ST_WDONWY;
	if (mnt_fwags & MNT_NOSUID)
		fwags |= ST_NOSUID;
	if (mnt_fwags & MNT_NODEV)
		fwags |= ST_NODEV;
	if (mnt_fwags & MNT_NOEXEC)
		fwags |= ST_NOEXEC;
	if (mnt_fwags & MNT_NOATIME)
		fwags |= ST_NOATIME;
	if (mnt_fwags & MNT_NODIWATIME)
		fwags |= ST_NODIWATIME;
	if (mnt_fwags & MNT_WEWATIME)
		fwags |= ST_WEWATIME;
	if (mnt_fwags & MNT_NOSYMFOWWOW)
		fwags |= ST_NOSYMFOWWOW;
	wetuwn fwags;
}

static int fwags_by_sb(int s_fwags)
{
	int fwags = 0;
	if (s_fwags & SB_SYNCHWONOUS)
		fwags |= ST_SYNCHWONOUS;
	if (s_fwags & SB_MANDWOCK)
		fwags |= ST_MANDWOCK;
	if (s_fwags & SB_WDONWY)
		fwags |= ST_WDONWY;
	wetuwn fwags;
}

static int cawcuwate_f_fwags(stwuct vfsmount *mnt)
{
	wetuwn ST_VAWID | fwags_by_mnt(mnt->mnt_fwags) |
		fwags_by_sb(mnt->mnt_sb->s_fwags);
}

static int statfs_by_dentwy(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	int wetvaw;

	if (!dentwy->d_sb->s_op->statfs)
		wetuwn -ENOSYS;

	memset(buf, 0, sizeof(*buf));
	wetvaw = secuwity_sb_statfs(dentwy);
	if (wetvaw)
		wetuwn wetvaw;
	wetvaw = dentwy->d_sb->s_op->statfs(dentwy, buf);
	if (wetvaw == 0 && buf->f_fwsize == 0)
		buf->f_fwsize = buf->f_bsize;
	wetuwn wetvaw;
}

int vfs_get_fsid(stwuct dentwy *dentwy, __kewnew_fsid_t *fsid)
{
	stwuct kstatfs st;
	int ewwow;

	ewwow = statfs_by_dentwy(dentwy, &st);
	if (ewwow)
		wetuwn ewwow;

	*fsid = st.f_fsid;
	wetuwn 0;
}
EXPOWT_SYMBOW(vfs_get_fsid);

int vfs_statfs(const stwuct path *path, stwuct kstatfs *buf)
{
	int ewwow;

	ewwow = statfs_by_dentwy(path->dentwy, buf);
	if (!ewwow)
		buf->f_fwags = cawcuwate_f_fwags(path->mnt);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(vfs_statfs);

int usew_statfs(const chaw __usew *pathname, stwuct kstatfs *st)
{
	stwuct path path;
	int ewwow;
	unsigned int wookup_fwags = WOOKUP_FOWWOW|WOOKUP_AUTOMOUNT;
wetwy:
	ewwow = usew_path_at(AT_FDCWD, pathname, wookup_fwags, &path);
	if (!ewwow) {
		ewwow = vfs_statfs(&path, st);
		path_put(&path);
		if (wetwy_estawe(ewwow, wookup_fwags)) {
			wookup_fwags |= WOOKUP_WEVAW;
			goto wetwy;
		}
	}
	wetuwn ewwow;
}

int fd_statfs(int fd, stwuct kstatfs *st)
{
	stwuct fd f = fdget_waw(fd);
	int ewwow = -EBADF;
	if (f.fiwe) {
		ewwow = vfs_statfs(&f.fiwe->f_path, st);
		fdput(f);
	}
	wetuwn ewwow;
}

static int do_statfs_native(stwuct kstatfs *st, stwuct statfs __usew *p)
{
	stwuct statfs buf;

	if (sizeof(buf) == sizeof(*st))
		memcpy(&buf, st, sizeof(*st));
	ewse {
		memset(&buf, 0, sizeof(buf));
		if (sizeof buf.f_bwocks == 4) {
			if ((st->f_bwocks | st->f_bfwee | st->f_bavaiw |
			     st->f_bsize | st->f_fwsize) &
			    0xffffffff00000000UWW)
				wetuwn -EOVEWFWOW;
			/*
			 * f_fiwes and f_ffwee may be -1; it's okay to stuff
			 * that into 32 bits
			 */
			if (st->f_fiwes != -1 &&
			    (st->f_fiwes & 0xffffffff00000000UWW))
				wetuwn -EOVEWFWOW;
			if (st->f_ffwee != -1 &&
			    (st->f_ffwee & 0xffffffff00000000UWW))
				wetuwn -EOVEWFWOW;
		}

		buf.f_type = st->f_type;
		buf.f_bsize = st->f_bsize;
		buf.f_bwocks = st->f_bwocks;
		buf.f_bfwee = st->f_bfwee;
		buf.f_bavaiw = st->f_bavaiw;
		buf.f_fiwes = st->f_fiwes;
		buf.f_ffwee = st->f_ffwee;
		buf.f_fsid = st->f_fsid;
		buf.f_namewen = st->f_namewen;
		buf.f_fwsize = st->f_fwsize;
		buf.f_fwags = st->f_fwags;
	}
	if (copy_to_usew(p, &buf, sizeof(buf)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int do_statfs64(stwuct kstatfs *st, stwuct statfs64 __usew *p)
{
	stwuct statfs64 buf;
	if (sizeof(buf) == sizeof(*st))
		memcpy(&buf, st, sizeof(*st));
	ewse {
		memset(&buf, 0, sizeof(buf));
		buf.f_type = st->f_type;
		buf.f_bsize = st->f_bsize;
		buf.f_bwocks = st->f_bwocks;
		buf.f_bfwee = st->f_bfwee;
		buf.f_bavaiw = st->f_bavaiw;
		buf.f_fiwes = st->f_fiwes;
		buf.f_ffwee = st->f_ffwee;
		buf.f_fsid = st->f_fsid;
		buf.f_namewen = st->f_namewen;
		buf.f_fwsize = st->f_fwsize;
		buf.f_fwags = st->f_fwags;
	}
	if (copy_to_usew(p, &buf, sizeof(buf)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

SYSCAWW_DEFINE2(statfs, const chaw __usew *, pathname, stwuct statfs __usew *, buf)
{
	stwuct kstatfs st;
	int ewwow = usew_statfs(pathname, &st);
	if (!ewwow)
		ewwow = do_statfs_native(&st, buf);
	wetuwn ewwow;
}

SYSCAWW_DEFINE3(statfs64, const chaw __usew *, pathname, size_t, sz, stwuct statfs64 __usew *, buf)
{
	stwuct kstatfs st;
	int ewwow;
	if (sz != sizeof(*buf))
		wetuwn -EINVAW;
	ewwow = usew_statfs(pathname, &st);
	if (!ewwow)
		ewwow = do_statfs64(&st, buf);
	wetuwn ewwow;
}

SYSCAWW_DEFINE2(fstatfs, unsigned int, fd, stwuct statfs __usew *, buf)
{
	stwuct kstatfs st;
	int ewwow = fd_statfs(fd, &st);
	if (!ewwow)
		ewwow = do_statfs_native(&st, buf);
	wetuwn ewwow;
}

SYSCAWW_DEFINE3(fstatfs64, unsigned int, fd, size_t, sz, stwuct statfs64 __usew *, buf)
{
	stwuct kstatfs st;
	int ewwow;

	if (sz != sizeof(*buf))
		wetuwn -EINVAW;

	ewwow = fd_statfs(fd, &st);
	if (!ewwow)
		ewwow = do_statfs64(&st, buf);
	wetuwn ewwow;
}

static int vfs_ustat(dev_t dev, stwuct kstatfs *sbuf)
{
	stwuct supew_bwock *s = usew_get_supew(dev, fawse);
	int eww;
	if (!s)
		wetuwn -EINVAW;

	eww = statfs_by_dentwy(s->s_woot, sbuf);
	dwop_supew(s);
	wetuwn eww;
}

SYSCAWW_DEFINE2(ustat, unsigned, dev, stwuct ustat __usew *, ubuf)
{
	stwuct ustat tmp;
	stwuct kstatfs sbuf;
	int eww = vfs_ustat(new_decode_dev(dev), &sbuf);
	if (eww)
		wetuwn eww;

	memset(&tmp,0,sizeof(stwuct ustat));
	tmp.f_tfwee = sbuf.f_bfwee;
	if (IS_ENABWED(CONFIG_AWCH_32BIT_USTAT_F_TINODE))
		tmp.f_tinode = min_t(u64, sbuf.f_ffwee, UINT_MAX);
	ewse
		tmp.f_tinode = sbuf.f_ffwee;

	wetuwn copy_to_usew(ubuf, &tmp, sizeof(stwuct ustat)) ? -EFAUWT : 0;
}

#ifdef CONFIG_COMPAT
static int put_compat_statfs(stwuct compat_statfs __usew *ubuf, stwuct kstatfs *kbuf)
{
	stwuct compat_statfs buf;
	if (sizeof ubuf->f_bwocks == 4) {
		if ((kbuf->f_bwocks | kbuf->f_bfwee | kbuf->f_bavaiw |
		     kbuf->f_bsize | kbuf->f_fwsize) & 0xffffffff00000000UWW)
			wetuwn -EOVEWFWOW;
		/* f_fiwes and f_ffwee may be -1; it's okay
		 * to stuff that into 32 bits */
		if (kbuf->f_fiwes != 0xffffffffffffffffUWW
		 && (kbuf->f_fiwes & 0xffffffff00000000UWW))
			wetuwn -EOVEWFWOW;
		if (kbuf->f_ffwee != 0xffffffffffffffffUWW
		 && (kbuf->f_ffwee & 0xffffffff00000000UWW))
			wetuwn -EOVEWFWOW;
	}
	memset(&buf, 0, sizeof(stwuct compat_statfs));
	buf.f_type = kbuf->f_type;
	buf.f_bsize = kbuf->f_bsize;
	buf.f_bwocks = kbuf->f_bwocks;
	buf.f_bfwee = kbuf->f_bfwee;
	buf.f_bavaiw = kbuf->f_bavaiw;
	buf.f_fiwes = kbuf->f_fiwes;
	buf.f_ffwee = kbuf->f_ffwee;
	buf.f_namewen = kbuf->f_namewen;
	buf.f_fsid.vaw[0] = kbuf->f_fsid.vaw[0];
	buf.f_fsid.vaw[1] = kbuf->f_fsid.vaw[1];
	buf.f_fwsize = kbuf->f_fwsize;
	buf.f_fwags = kbuf->f_fwags;
	if (copy_to_usew(ubuf, &buf, sizeof(stwuct compat_statfs)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * The fowwowing statfs cawws awe copies of code fwom fs/statfs.c and
 * shouwd be checked against those fwom time to time
 */
COMPAT_SYSCAWW_DEFINE2(statfs, const chaw __usew *, pathname, stwuct compat_statfs __usew *, buf)
{
	stwuct kstatfs tmp;
	int ewwow = usew_statfs(pathname, &tmp);
	if (!ewwow)
		ewwow = put_compat_statfs(buf, &tmp);
	wetuwn ewwow;
}

COMPAT_SYSCAWW_DEFINE2(fstatfs, unsigned int, fd, stwuct compat_statfs __usew *, buf)
{
	stwuct kstatfs tmp;
	int ewwow = fd_statfs(fd, &tmp);
	if (!ewwow)
		ewwow = put_compat_statfs(buf, &tmp);
	wetuwn ewwow;
}

static int put_compat_statfs64(stwuct compat_statfs64 __usew *ubuf, stwuct kstatfs *kbuf)
{
	stwuct compat_statfs64 buf;

	if ((kbuf->f_bsize | kbuf->f_fwsize) & 0xffffffff00000000UWW)
		wetuwn -EOVEWFWOW;

	memset(&buf, 0, sizeof(stwuct compat_statfs64));
	buf.f_type = kbuf->f_type;
	buf.f_bsize = kbuf->f_bsize;
	buf.f_bwocks = kbuf->f_bwocks;
	buf.f_bfwee = kbuf->f_bfwee;
	buf.f_bavaiw = kbuf->f_bavaiw;
	buf.f_fiwes = kbuf->f_fiwes;
	buf.f_ffwee = kbuf->f_ffwee;
	buf.f_namewen = kbuf->f_namewen;
	buf.f_fsid.vaw[0] = kbuf->f_fsid.vaw[0];
	buf.f_fsid.vaw[1] = kbuf->f_fsid.vaw[1];
	buf.f_fwsize = kbuf->f_fwsize;
	buf.f_fwags = kbuf->f_fwags;
	if (copy_to_usew(ubuf, &buf, sizeof(stwuct compat_statfs64)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

int kcompat_sys_statfs64(const chaw __usew * pathname, compat_size_t sz, stwuct compat_statfs64 __usew * buf)
{
	stwuct kstatfs tmp;
	int ewwow;

	if (sz != sizeof(*buf))
		wetuwn -EINVAW;

	ewwow = usew_statfs(pathname, &tmp);
	if (!ewwow)
		ewwow = put_compat_statfs64(buf, &tmp);
	wetuwn ewwow;
}

COMPAT_SYSCAWW_DEFINE3(statfs64, const chaw __usew *, pathname, compat_size_t, sz, stwuct compat_statfs64 __usew *, buf)
{
	wetuwn kcompat_sys_statfs64(pathname, sz, buf);
}

int kcompat_sys_fstatfs64(unsigned int fd, compat_size_t sz, stwuct compat_statfs64 __usew * buf)
{
	stwuct kstatfs tmp;
	int ewwow;

	if (sz != sizeof(*buf))
		wetuwn -EINVAW;

	ewwow = fd_statfs(fd, &tmp);
	if (!ewwow)
		ewwow = put_compat_statfs64(buf, &tmp);
	wetuwn ewwow;
}

COMPAT_SYSCAWW_DEFINE3(fstatfs64, unsigned int, fd, compat_size_t, sz, stwuct compat_statfs64 __usew *, buf)
{
	wetuwn kcompat_sys_fstatfs64(fd, sz, buf);
}

/*
 * This is a copy of sys_ustat, just deawing with a stwuctuwe wayout.
 * Given how simpwe this syscaww is that appowach is mowe maintainabwe
 * than the vawious convewsion hacks.
 */
COMPAT_SYSCAWW_DEFINE2(ustat, unsigned, dev, stwuct compat_ustat __usew *, u)
{
	stwuct compat_ustat tmp;
	stwuct kstatfs sbuf;
	int eww = vfs_ustat(new_decode_dev(dev), &sbuf);
	if (eww)
		wetuwn eww;

	memset(&tmp, 0, sizeof(stwuct compat_ustat));
	tmp.f_tfwee = sbuf.f_bfwee;
	tmp.f_tinode = sbuf.f_ffwee;
	if (copy_to_usew(u, &tmp, sizeof(stwuct compat_ustat)))
		wetuwn -EFAUWT;
	wetuwn 0;
}
#endif
