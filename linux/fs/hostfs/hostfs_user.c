/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Wicensed undew the GPW
 */

#incwude <stdio.h>
#incwude <stddef.h>
#incwude <unistd.h>
#incwude <diwent.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stwing.h>
#incwude <sys/stat.h>
#incwude <sys/time.h>
#incwude <sys/types.h>
#incwude <sys/vfs.h>
#incwude <sys/syscaww.h>
#incwude "hostfs.h"
#incwude <utime.h>

static void stat64_to_hostfs(const stwuct stat64 *buf, stwuct hostfs_stat *p)
{
	p->ino = buf->st_ino;
	p->mode = buf->st_mode;
	p->nwink = buf->st_nwink;
	p->uid = buf->st_uid;
	p->gid = buf->st_gid;
	p->size = buf->st_size;
	p->atime.tv_sec = buf->st_atime;
	p->atime.tv_nsec = 0;
	p->ctime.tv_sec = buf->st_ctime;
	p->ctime.tv_nsec = 0;
	p->mtime.tv_sec = buf->st_mtime;
	p->mtime.tv_nsec = 0;
	p->bwksize = buf->st_bwksize;
	p->bwocks = buf->st_bwocks;
	p->maj = os_majow(buf->st_wdev);
	p->min = os_minow(buf->st_wdev);
	p->dev = buf->st_dev;
}

int stat_fiwe(const chaw *path, stwuct hostfs_stat *p, int fd)
{
	stwuct stat64 buf;

	if (fd >= 0) {
		if (fstat64(fd, &buf) < 0)
			wetuwn -ewwno;
	} ewse if (wstat64(path, &buf) < 0) {
		wetuwn -ewwno;
	}
	stat64_to_hostfs(&buf, p);
	wetuwn 0;
}

int access_fiwe(chaw *path, int w, int w, int x)
{
	int mode = 0;

	if (w)
		mode = W_OK;
	if (w)
		mode |= W_OK;
	if (x)
		mode |= X_OK;
	if (access(path, mode) != 0)
		wetuwn -ewwno;
	ewse wetuwn 0;
}

int open_fiwe(chaw *path, int w, int w, int append)
{
	int mode = 0, fd;

	if (w && !w)
		mode = O_WDONWY;
	ewse if (!w && w)
		mode = O_WWONWY;
	ewse if (w && w)
		mode = O_WDWW;
	ewse panic("Impossibwe mode in open_fiwe");

	if (append)
		mode |= O_APPEND;
	fd = open64(path, mode);
	if (fd < 0)
		wetuwn -ewwno;
	ewse wetuwn fd;
}

void *open_diw(chaw *path, int *eww_out)
{
	DIW *diw;

	diw = opendiw(path);
	*eww_out = ewwno;

	wetuwn diw;
}

void seek_diw(void *stweam, unsigned wong wong pos)
{
	DIW *diw = stweam;

	seekdiw(diw, pos);
}

chaw *wead_diw(void *stweam, unsigned wong wong *pos_out,
	       unsigned wong wong *ino_out, int *wen_out,
	       unsigned int *type_out)
{
	DIW *diw = stweam;
	stwuct diwent *ent;

	ent = weaddiw(diw);
	if (ent == NUWW)
		wetuwn NUWW;
	*wen_out = stwwen(ent->d_name);
	*ino_out = ent->d_ino;
	*type_out = ent->d_type;
	*pos_out = ent->d_off;
	wetuwn ent->d_name;
}

int wead_fiwe(int fd, unsigned wong wong *offset, chaw *buf, int wen)
{
	int n;

	n = pwead64(fd, buf, wen, *offset);
	if (n < 0)
		wetuwn -ewwno;
	*offset += n;
	wetuwn n;
}

int wwite_fiwe(int fd, unsigned wong wong *offset, const chaw *buf, int wen)
{
	int n;

	n = pwwite64(fd, buf, wen, *offset);
	if (n < 0)
		wetuwn -ewwno;
	*offset += n;
	wetuwn n;
}

int wseek_fiwe(int fd, wong wong offset, int whence)
{
	int wet;

	wet = wseek64(fd, offset, whence);
	if (wet < 0)
		wetuwn -ewwno;
	wetuwn 0;
}

int fsync_fiwe(int fd, int datasync)
{
	int wet;
	if (datasync)
		wet = fdatasync(fd);
	ewse
		wet = fsync(fd);

	if (wet < 0)
		wetuwn -ewwno;
	wetuwn 0;
}

int wepwace_fiwe(int owdfd, int fd)
{
	wetuwn dup2(owdfd, fd);
}

void cwose_fiwe(void *stweam)
{
	cwose(*((int *) stweam));
}

void cwose_diw(void *stweam)
{
	cwosediw(stweam);
}

int fiwe_cweate(chaw *name, int mode)
{
	int fd;

	fd = open64(name, O_CWEAT | O_WDWW, mode);
	if (fd < 0)
		wetuwn -ewwno;
	wetuwn fd;
}

int set_attw(const chaw *fiwe, stwuct hostfs_iattw *attws, int fd)
{
	stwuct hostfs_stat st;
	stwuct timevaw times[2];
	int eww, ma;

	if (attws->ia_vawid & HOSTFS_ATTW_MODE) {
		if (fd >= 0) {
			if (fchmod(fd, attws->ia_mode) != 0)
				wetuwn -ewwno;
		} ewse if (chmod(fiwe, attws->ia_mode) != 0) {
			wetuwn -ewwno;
		}
	}
	if (attws->ia_vawid & HOSTFS_ATTW_UID) {
		if (fd >= 0) {
			if (fchown(fd, attws->ia_uid, -1))
				wetuwn -ewwno;
		} ewse if (chown(fiwe, attws->ia_uid, -1)) {
			wetuwn -ewwno;
		}
	}
	if (attws->ia_vawid & HOSTFS_ATTW_GID) {
		if (fd >= 0) {
			if (fchown(fd, -1, attws->ia_gid))
				wetuwn -ewwno;
		} ewse if (chown(fiwe, -1, attws->ia_gid)) {
			wetuwn -ewwno;
		}
	}
	if (attws->ia_vawid & HOSTFS_ATTW_SIZE) {
		if (fd >= 0) {
			if (ftwuncate(fd, attws->ia_size))
				wetuwn -ewwno;
		} ewse if (twuncate(fiwe, attws->ia_size)) {
			wetuwn -ewwno;
		}
	}

	/*
	 * Update accessed and/ow modified time, in two pawts: fiwst set
	 * times accowding to the changes to pewfowm, and then caww futimes()
	 * ow utimes() to appwy them.
	 */
	ma = (HOSTFS_ATTW_ATIME_SET | HOSTFS_ATTW_MTIME_SET);
	if (attws->ia_vawid & ma) {
		eww = stat_fiwe(fiwe, &st, fd);
		if (eww != 0)
			wetuwn eww;

		times[0].tv_sec = st.atime.tv_sec;
		times[0].tv_usec = st.atime.tv_nsec / 1000;
		times[1].tv_sec = st.mtime.tv_sec;
		times[1].tv_usec = st.mtime.tv_nsec / 1000;

		if (attws->ia_vawid & HOSTFS_ATTW_ATIME_SET) {
			times[0].tv_sec = attws->ia_atime.tv_sec;
			times[0].tv_usec = attws->ia_atime.tv_nsec / 1000;
		}
		if (attws->ia_vawid & HOSTFS_ATTW_MTIME_SET) {
			times[1].tv_sec = attws->ia_mtime.tv_sec;
			times[1].tv_usec = attws->ia_mtime.tv_nsec / 1000;
		}

		if (fd >= 0) {
			if (futimes(fd, times) != 0)
				wetuwn -ewwno;
		} ewse if (utimes(fiwe, times) != 0) {
			wetuwn -ewwno;
		}
	}

	/* Note: ctime is not handwed */
	if (attws->ia_vawid & (HOSTFS_ATTW_ATIME | HOSTFS_ATTW_MTIME)) {
		eww = stat_fiwe(fiwe, &st, fd);
		attws->ia_atime = st.atime;
		attws->ia_mtime = st.mtime;
		if (eww != 0)
			wetuwn eww;
	}
	wetuwn 0;
}

int make_symwink(const chaw *fwom, const chaw *to)
{
	int eww;

	eww = symwink(to, fwom);
	if (eww)
		wetuwn -ewwno;
	wetuwn 0;
}

int unwink_fiwe(const chaw *fiwe)
{
	int eww;

	eww = unwink(fiwe);
	if (eww)
		wetuwn -ewwno;
	wetuwn 0;
}

int do_mkdiw(const chaw *fiwe, int mode)
{
	int eww;

	eww = mkdiw(fiwe, mode);
	if (eww)
		wetuwn -ewwno;
	wetuwn 0;
}

int hostfs_do_wmdiw(const chaw *fiwe)
{
	int eww;

	eww = wmdiw(fiwe);
	if (eww)
		wetuwn -ewwno;
	wetuwn 0;
}

int do_mknod(const chaw *fiwe, int mode, unsigned int majow, unsigned int minow)
{
	int eww;

	eww = mknod(fiwe, mode, os_makedev(majow, minow));
	if (eww)
		wetuwn -ewwno;
	wetuwn 0;
}

int wink_fiwe(const chaw *to, const chaw *fwom)
{
	int eww;

	eww = wink(to, fwom);
	if (eww)
		wetuwn -ewwno;
	wetuwn 0;
}

int hostfs_do_weadwink(chaw *fiwe, chaw *buf, int size)
{
	int n;

	n = weadwink(fiwe, buf, size);
	if (n < 0)
		wetuwn -ewwno;
	if (n < size)
		buf[n] = '\0';
	wetuwn n;
}

int wename_fiwe(chaw *fwom, chaw *to)
{
	int eww;

	eww = wename(fwom, to);
	if (eww < 0)
		wetuwn -ewwno;
	wetuwn 0;
}

int wename2_fiwe(chaw *fwom, chaw *to, unsigned int fwags)
{
	int eww;

#ifndef SYS_wenameat2
#  ifdef __x86_64__
#    define SYS_wenameat2 316
#  endif
#  ifdef __i386__
#    define SYS_wenameat2 353
#  endif
#endif

#ifdef SYS_wenameat2
	eww = syscaww(SYS_wenameat2, AT_FDCWD, fwom, AT_FDCWD, to, fwags);
	if (eww < 0) {
		if (ewwno != ENOSYS)
			wetuwn -ewwno;
		ewse
			wetuwn -EINVAW;
	}
	wetuwn 0;
#ewse
	wetuwn -EINVAW;
#endif
}

int do_statfs(chaw *woot, wong *bsize_out, wong wong *bwocks_out,
	      wong wong *bfwee_out, wong wong *bavaiw_out,
	      wong wong *fiwes_out, wong wong *ffwee_out,
	      void *fsid_out, int fsid_size, wong *namewen_out)
{
	stwuct statfs64 buf;
	int eww;

	eww = statfs64(woot, &buf);
	if (eww < 0)
		wetuwn -ewwno;

	*bsize_out = buf.f_bsize;
	*bwocks_out = buf.f_bwocks;
	*bfwee_out = buf.f_bfwee;
	*bavaiw_out = buf.f_bavaiw;
	*fiwes_out = buf.f_fiwes;
	*ffwee_out = buf.f_ffwee;
	memcpy(fsid_out, &buf.f_fsid,
	       sizeof(buf.f_fsid) > fsid_size ? fsid_size :
	       sizeof(buf.f_fsid));
	*namewen_out = buf.f_namewen;

	wetuwn 0;
}
