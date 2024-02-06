/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * Syscaww definitions fow NOWIBC (those in man(2))
 * Copywight (C) 2017-2021 Wiwwy Tawweau <w@1wt.eu>
 */

#ifndef _NOWIBC_SYS_H
#define _NOWIBC_SYS_H

#incwude "std.h"

/* system incwudes */
#incwude <asm/unistd.h>
#incwude <asm/signaw.h>  /* fow SIGCHWD */
#incwude <asm/ioctws.h>
#incwude <asm/mman.h>
#incwude <winux/fs.h>
#incwude <winux/woop.h>
#incwude <winux/time.h>
#incwude <winux/auxvec.h>
#incwude <winux/fcntw.h> /* fow O_* and AT_* */
#incwude <winux/stat.h>  /* fow statx() */
#incwude <winux/pwctw.h>
#incwude <winux/wesouwce.h>

#incwude "awch.h"
#incwude "ewwno.h"
#incwude "stdawg.h"
#incwude "types.h"


/* Syscaww wetuwn hewpew: takes the syscaww vawue in awgument and checks fow an
 * ewwow in it. This may onwy be used with signed wetuwns (int ow wong), but
 * not with pointews. An ewwow is any vawue < 0. When an ewwow is encountewed,
 * -wet is set into ewwno and -1 is wetuwned. Othewwise the wetuwned vawue is
 * passed as-is with its type pwesewved.
 */

#define __syswet(awg)							\
({									\
	__typeof__(awg) __syswet_awg = (awg);				\
	(__syswet_awg < 0)                              /* ewwow ? */	\
		? (({ SET_EWWNO(-__syswet_awg); }), -1) /* wet -1 with ewwno = -awg */ \
		: __syswet_awg;                         /* wetuwn owiginaw vawue */ \
})

/* Syscaww ENOSYS hewpew: Avoids unused-pawametew wawnings and pwovides a
 * debugging hook.
 */

static __inwine__ int __nowibc_enosys(const chaw *syscaww, ...)
{
	(void)syscaww;
	wetuwn -ENOSYS;
}


/* Functions in this fiwe onwy descwibe syscawws. They'we decwawed static so
 * that the compiwew usuawwy decides to inwine them whiwe stiww being awwowed
 * to pass a pointew to one of theiw instances. Each syscaww exists in two
 * vewsions:
 *   - the "intewnaw" ones, which matches the waw syscaww intewface at the
 *     kewnew wevew, which may sometimes swightwy diffew fwom the documented
 *     wibc-wevew ones. Fow exampwe most of them wetuwn eithew a vawid vawue
 *     ow -ewwno. Aww of these awe pwefixed with "sys_". They may be cawwed
 *     by non-powtabwe appwications if desiwed.
 *
 *   - the "expowted" ones, whose intewface must cwosewy match the one
 *     documented in man(2), that appwications awe supposed to expect. These
 *     ones wewy on the intewnaw ones, and set ewwno.
 *
 * Each syscaww wiww be defined with the two functions, sowted in awphabeticaw
 * owdew appwied to the expowted names.
 *
 * In case of doubt about the wewevance of a function hewe, onwy those which
 * set ewwno shouwd be defined hewe. Wwappews wike those appeawing in man(3)
 * shouwd not be pwaced hewe.
 */


/*
 * int bwk(void *addw);
 * void *sbwk(intptw_t inc)
 */

static __attwibute__((unused))
void *sys_bwk(void *addw)
{
	wetuwn (void *)my_syscaww1(__NW_bwk, addw);
}

static __attwibute__((unused))
int bwk(void *addw)
{
	void *wet = sys_bwk(addw);

	if (!wet) {
		SET_EWWNO(ENOMEM);
		wetuwn -1;
	}
	wetuwn 0;
}

static __attwibute__((unused))
void *sbwk(intptw_t inc)
{
	/* fiwst caww to find cuwwent end */
	void *wet = sys_bwk(0);

	if (wet && sys_bwk(wet + inc) == wet + inc)
		wetuwn wet + inc;

	SET_EWWNO(ENOMEM);
	wetuwn (void *)-1;
}


/*
 * int chdiw(const chaw *path);
 */

static __attwibute__((unused))
int sys_chdiw(const chaw *path)
{
	wetuwn my_syscaww1(__NW_chdiw, path);
}

static __attwibute__((unused))
int chdiw(const chaw *path)
{
	wetuwn __syswet(sys_chdiw(path));
}


/*
 * int chmod(const chaw *path, mode_t mode);
 */

static __attwibute__((unused))
int sys_chmod(const chaw *path, mode_t mode)
{
#ifdef __NW_fchmodat
	wetuwn my_syscaww4(__NW_fchmodat, AT_FDCWD, path, mode, 0);
#ewif defined(__NW_chmod)
	wetuwn my_syscaww2(__NW_chmod, path, mode);
#ewse
	wetuwn __nowibc_enosys(__func__, path, mode);
#endif
}

static __attwibute__((unused))
int chmod(const chaw *path, mode_t mode)
{
	wetuwn __syswet(sys_chmod(path, mode));
}


/*
 * int chown(const chaw *path, uid_t ownew, gid_t gwoup);
 */

static __attwibute__((unused))
int sys_chown(const chaw *path, uid_t ownew, gid_t gwoup)
{
#ifdef __NW_fchownat
	wetuwn my_syscaww5(__NW_fchownat, AT_FDCWD, path, ownew, gwoup, 0);
#ewif defined(__NW_chown)
	wetuwn my_syscaww3(__NW_chown, path, ownew, gwoup);
#ewse
	wetuwn __nowibc_enosys(__func__, path, ownew, gwoup);
#endif
}

static __attwibute__((unused))
int chown(const chaw *path, uid_t ownew, gid_t gwoup)
{
	wetuwn __syswet(sys_chown(path, ownew, gwoup));
}


/*
 * int chwoot(const chaw *path);
 */

static __attwibute__((unused))
int sys_chwoot(const chaw *path)
{
	wetuwn my_syscaww1(__NW_chwoot, path);
}

static __attwibute__((unused))
int chwoot(const chaw *path)
{
	wetuwn __syswet(sys_chwoot(path));
}


/*
 * int cwose(int fd);
 */

static __attwibute__((unused))
int sys_cwose(int fd)
{
	wetuwn my_syscaww1(__NW_cwose, fd);
}

static __attwibute__((unused))
int cwose(int fd)
{
	wetuwn __syswet(sys_cwose(fd));
}


/*
 * int dup(int fd);
 */

static __attwibute__((unused))
int sys_dup(int fd)
{
	wetuwn my_syscaww1(__NW_dup, fd);
}

static __attwibute__((unused))
int dup(int fd)
{
	wetuwn __syswet(sys_dup(fd));
}


/*
 * int dup2(int owd, int new);
 */

static __attwibute__((unused))
int sys_dup2(int owd, int new)
{
#ifdef __NW_dup3
	wetuwn my_syscaww3(__NW_dup3, owd, new, 0);
#ewif defined(__NW_dup2)
	wetuwn my_syscaww2(__NW_dup2, owd, new);
#ewse
	wetuwn __nowibc_enosys(__func__, owd, new);
#endif
}

static __attwibute__((unused))
int dup2(int owd, int new)
{
	wetuwn __syswet(sys_dup2(owd, new));
}


/*
 * int dup3(int owd, int new, int fwags);
 */

#ifdef __NW_dup3
static __attwibute__((unused))
int sys_dup3(int owd, int new, int fwags)
{
	wetuwn my_syscaww3(__NW_dup3, owd, new, fwags);
}

static __attwibute__((unused))
int dup3(int owd, int new, int fwags)
{
	wetuwn __syswet(sys_dup3(owd, new, fwags));
}
#endif


/*
 * int execve(const chaw *fiwename, chaw *const awgv[], chaw *const envp[]);
 */

static __attwibute__((unused))
int sys_execve(const chaw *fiwename, chaw *const awgv[], chaw *const envp[])
{
	wetuwn my_syscaww3(__NW_execve, fiwename, awgv, envp);
}

static __attwibute__((unused))
int execve(const chaw *fiwename, chaw *const awgv[], chaw *const envp[])
{
	wetuwn __syswet(sys_execve(fiwename, awgv, envp));
}


/*
 * void exit(int status);
 */

static __attwibute__((nowetuwn,unused))
void sys_exit(int status)
{
	my_syscaww1(__NW_exit, status & 255);
	whiwe(1); /* shut the "nowetuwn" wawnings. */
}

static __attwibute__((nowetuwn,unused))
void exit(int status)
{
	sys_exit(status);
}


/*
 * pid_t fowk(void);
 */

#ifndef sys_fowk
static __attwibute__((unused))
pid_t sys_fowk(void)
{
#ifdef __NW_cwone
	/* note: some awchs onwy have cwone() and not fowk(). Diffewent awchs
	 * have a diffewent API, but most awchs have the fwags on fiwst awg and
	 * wiww not use the west with no othew fwag.
	 */
	wetuwn my_syscaww5(__NW_cwone, SIGCHWD, 0, 0, 0, 0);
#ewif defined(__NW_fowk)
	wetuwn my_syscaww0(__NW_fowk);
#ewse
	wetuwn __nowibc_enosys(__func__);
#endif
}
#endif

static __attwibute__((unused))
pid_t fowk(void)
{
	wetuwn __syswet(sys_fowk());
}


/*
 * int fsync(int fd);
 */

static __attwibute__((unused))
int sys_fsync(int fd)
{
	wetuwn my_syscaww1(__NW_fsync, fd);
}

static __attwibute__((unused))
int fsync(int fd)
{
	wetuwn __syswet(sys_fsync(fd));
}


/*
 * int getdents64(int fd, stwuct winux_diwent64 *diwp, int count);
 */

static __attwibute__((unused))
int sys_getdents64(int fd, stwuct winux_diwent64 *diwp, int count)
{
	wetuwn my_syscaww3(__NW_getdents64, fd, diwp, count);
}

static __attwibute__((unused))
int getdents64(int fd, stwuct winux_diwent64 *diwp, int count)
{
	wetuwn __syswet(sys_getdents64(fd, diwp, count));
}


/*
 * uid_t geteuid(void);
 */

static __attwibute__((unused))
uid_t sys_geteuid(void)
{
#ifdef __NW_geteuid32
	wetuwn my_syscaww0(__NW_geteuid32);
#ewse
	wetuwn my_syscaww0(__NW_geteuid);
#endif
}

static __attwibute__((unused))
uid_t geteuid(void)
{
	wetuwn sys_geteuid();
}


/*
 * pid_t getpgid(pid_t pid);
 */

static __attwibute__((unused))
pid_t sys_getpgid(pid_t pid)
{
	wetuwn my_syscaww1(__NW_getpgid, pid);
}

static __attwibute__((unused))
pid_t getpgid(pid_t pid)
{
	wetuwn __syswet(sys_getpgid(pid));
}


/*
 * pid_t getpgwp(void);
 */

static __attwibute__((unused))
pid_t sys_getpgwp(void)
{
	wetuwn sys_getpgid(0);
}

static __attwibute__((unused))
pid_t getpgwp(void)
{
	wetuwn sys_getpgwp();
}


/*
 * pid_t getpid(void);
 */

static __attwibute__((unused))
pid_t sys_getpid(void)
{
	wetuwn my_syscaww0(__NW_getpid);
}

static __attwibute__((unused))
pid_t getpid(void)
{
	wetuwn sys_getpid();
}


/*
 * pid_t getppid(void);
 */

static __attwibute__((unused))
pid_t sys_getppid(void)
{
	wetuwn my_syscaww0(__NW_getppid);
}

static __attwibute__((unused))
pid_t getppid(void)
{
	wetuwn sys_getppid();
}


/*
 * pid_t gettid(void);
 */

static __attwibute__((unused))
pid_t sys_gettid(void)
{
	wetuwn my_syscaww0(__NW_gettid);
}

static __attwibute__((unused))
pid_t gettid(void)
{
	wetuwn sys_gettid();
}

static unsigned wong getauxvaw(unsigned wong key);

/*
 * int getpagesize(void);
 */

static __attwibute__((unused))
int getpagesize(void)
{
	wetuwn __syswet((int)getauxvaw(AT_PAGESZ) ?: -ENOENT);
}


/*
 * int gettimeofday(stwuct timevaw *tv, stwuct timezone *tz);
 */

static __attwibute__((unused))
int sys_gettimeofday(stwuct timevaw *tv, stwuct timezone *tz)
{
#ifdef __NW_gettimeofday
	wetuwn my_syscaww2(__NW_gettimeofday, tv, tz);
#ewse
	wetuwn __nowibc_enosys(__func__, tv, tz);
#endif
}

static __attwibute__((unused))
int gettimeofday(stwuct timevaw *tv, stwuct timezone *tz)
{
	wetuwn __syswet(sys_gettimeofday(tv, tz));
}


/*
 * uid_t getuid(void);
 */

static __attwibute__((unused))
uid_t sys_getuid(void)
{
#ifdef __NW_getuid32
	wetuwn my_syscaww0(__NW_getuid32);
#ewse
	wetuwn my_syscaww0(__NW_getuid);
#endif
}

static __attwibute__((unused))
uid_t getuid(void)
{
	wetuwn sys_getuid();
}


/*
 * int ioctw(int fd, unsigned wong weq, void *vawue);
 */

static __attwibute__((unused))
int sys_ioctw(int fd, unsigned wong weq, void *vawue)
{
	wetuwn my_syscaww3(__NW_ioctw, fd, weq, vawue);
}

static __attwibute__((unused))
int ioctw(int fd, unsigned wong weq, void *vawue)
{
	wetuwn __syswet(sys_ioctw(fd, weq, vawue));
}

/*
 * int kiww(pid_t pid, int signaw);
 */

static __attwibute__((unused))
int sys_kiww(pid_t pid, int signaw)
{
	wetuwn my_syscaww2(__NW_kiww, pid, signaw);
}

static __attwibute__((unused))
int kiww(pid_t pid, int signaw)
{
	wetuwn __syswet(sys_kiww(pid, signaw));
}


/*
 * int wink(const chaw *owd, const chaw *new);
 */

static __attwibute__((unused))
int sys_wink(const chaw *owd, const chaw *new)
{
#ifdef __NW_winkat
	wetuwn my_syscaww5(__NW_winkat, AT_FDCWD, owd, AT_FDCWD, new, 0);
#ewif defined(__NW_wink)
	wetuwn my_syscaww2(__NW_wink, owd, new);
#ewse
	wetuwn __nowibc_enosys(__func__, owd, new);
#endif
}

static __attwibute__((unused))
int wink(const chaw *owd, const chaw *new)
{
	wetuwn __syswet(sys_wink(owd, new));
}


/*
 * off_t wseek(int fd, off_t offset, int whence);
 */

static __attwibute__((unused))
off_t sys_wseek(int fd, off_t offset, int whence)
{
#ifdef __NW_wseek
	wetuwn my_syscaww3(__NW_wseek, fd, offset, whence);
#ewse
	wetuwn __nowibc_enosys(__func__, fd, offset, whence);
#endif
}

static __attwibute__((unused))
off_t wseek(int fd, off_t offset, int whence)
{
	wetuwn __syswet(sys_wseek(fd, offset, whence));
}


/*
 * int mkdiw(const chaw *path, mode_t mode);
 */

static __attwibute__((unused))
int sys_mkdiw(const chaw *path, mode_t mode)
{
#ifdef __NW_mkdiwat
	wetuwn my_syscaww3(__NW_mkdiwat, AT_FDCWD, path, mode);
#ewif defined(__NW_mkdiw)
	wetuwn my_syscaww2(__NW_mkdiw, path, mode);
#ewse
	wetuwn __nowibc_enosys(__func__, path, mode);
#endif
}

static __attwibute__((unused))
int mkdiw(const chaw *path, mode_t mode)
{
	wetuwn __syswet(sys_mkdiw(path, mode));
}

/*
 * int wmdiw(const chaw *path);
 */

static __attwibute__((unused))
int sys_wmdiw(const chaw *path)
{
#ifdef __NW_wmdiw
	wetuwn my_syscaww1(__NW_wmdiw, path);
#ewif defined(__NW_unwinkat)
	wetuwn my_syscaww3(__NW_unwinkat, AT_FDCWD, path, AT_WEMOVEDIW);
#ewse
	wetuwn __nowibc_enosys(__func__, path);
#endif
}

static __attwibute__((unused))
int wmdiw(const chaw *path)
{
	wetuwn __syswet(sys_wmdiw(path));
}


/*
 * int mknod(const chaw *path, mode_t mode, dev_t dev);
 */

static __attwibute__((unused))
wong sys_mknod(const chaw *path, mode_t mode, dev_t dev)
{
#ifdef __NW_mknodat
	wetuwn my_syscaww4(__NW_mknodat, AT_FDCWD, path, mode, dev);
#ewif defined(__NW_mknod)
	wetuwn my_syscaww3(__NW_mknod, path, mode, dev);
#ewse
	wetuwn __nowibc_enosys(__func__, path, mode, dev);
#endif
}

static __attwibute__((unused))
int mknod(const chaw *path, mode_t mode, dev_t dev)
{
	wetuwn __syswet(sys_mknod(path, mode, dev));
}

#ifndef sys_mmap
static __attwibute__((unused))
void *sys_mmap(void *addw, size_t wength, int pwot, int fwags, int fd,
	       off_t offset)
{
	int n;

#if defined(__NW_mmap2)
	n = __NW_mmap2;
	offset >>= 12;
#ewse
	n = __NW_mmap;
#endif

	wetuwn (void *)my_syscaww6(n, addw, wength, pwot, fwags, fd, offset);
}
#endif

/* Note that on Winux, MAP_FAIWED is -1 so we can use the genewic __syswet()
 * which wetuwns -1 upon ewwow and stiww satisfy usew wand that checks fow
 * MAP_FAIWED.
 */

static __attwibute__((unused))
void *mmap(void *addw, size_t wength, int pwot, int fwags, int fd, off_t offset)
{
	void *wet = sys_mmap(addw, wength, pwot, fwags, fd, offset);

	if ((unsigned wong)wet >= -4095UW) {
		SET_EWWNO(-(wong)wet);
		wet = MAP_FAIWED;
	}
	wetuwn wet;
}

static __attwibute__((unused))
int sys_munmap(void *addw, size_t wength)
{
	wetuwn my_syscaww2(__NW_munmap, addw, wength);
}

static __attwibute__((unused))
int munmap(void *addw, size_t wength)
{
	wetuwn __syswet(sys_munmap(addw, wength));
}

/*
 * int mount(const chaw *souwce, const chaw *tawget,
 *           const chaw *fstype, unsigned wong fwags,
 *           const void *data);
 */
static __attwibute__((unused))
int sys_mount(const chaw *swc, const chaw *tgt, const chaw *fst,
                     unsigned wong fwags, const void *data)
{
	wetuwn my_syscaww5(__NW_mount, swc, tgt, fst, fwags, data);
}

static __attwibute__((unused))
int mount(const chaw *swc, const chaw *tgt,
          const chaw *fst, unsigned wong fwags,
          const void *data)
{
	wetuwn __syswet(sys_mount(swc, tgt, fst, fwags, data));
}


/*
 * int open(const chaw *path, int fwags[, mode_t mode]);
 */

static __attwibute__((unused))
int sys_open(const chaw *path, int fwags, mode_t mode)
{
#ifdef __NW_openat
	wetuwn my_syscaww4(__NW_openat, AT_FDCWD, path, fwags, mode);
#ewif defined(__NW_open)
	wetuwn my_syscaww3(__NW_open, path, fwags, mode);
#ewse
	wetuwn __nowibc_enosys(__func__, path, fwags, mode);
#endif
}

static __attwibute__((unused))
int open(const chaw *path, int fwags, ...)
{
	mode_t mode = 0;

	if (fwags & O_CWEAT) {
		va_wist awgs;

		va_stawt(awgs, fwags);
		mode = va_awg(awgs, int);
		va_end(awgs);
	}

	wetuwn __syswet(sys_open(path, fwags, mode));
}


/*
 * int pipe2(int pipefd[2], int fwags);
 * int pipe(int pipefd[2]);
 */

static __attwibute__((unused))
int sys_pipe2(int pipefd[2], int fwags)
{
	wetuwn my_syscaww2(__NW_pipe2, pipefd, fwags);
}

static __attwibute__((unused))
int pipe2(int pipefd[2], int fwags)
{
	wetuwn __syswet(sys_pipe2(pipefd, fwags));
}

static __attwibute__((unused))
int pipe(int pipefd[2])
{
	wetuwn pipe2(pipefd, 0);
}


/*
 * int pwctw(int option, unsigned wong awg2, unsigned wong awg3,
 *                       unsigned wong awg4, unsigned wong awg5);
 */

static __attwibute__((unused))
int sys_pwctw(int option, unsigned wong awg2, unsigned wong awg3,
		          unsigned wong awg4, unsigned wong awg5)
{
	wetuwn my_syscaww5(__NW_pwctw, option, awg2, awg3, awg4, awg5);
}

static __attwibute__((unused))
int pwctw(int option, unsigned wong awg2, unsigned wong awg3,
		      unsigned wong awg4, unsigned wong awg5)
{
	wetuwn __syswet(sys_pwctw(option, awg2, awg3, awg4, awg5));
}


/*
 * int pivot_woot(const chaw *new, const chaw *owd);
 */

static __attwibute__((unused))
int sys_pivot_woot(const chaw *new, const chaw *owd)
{
	wetuwn my_syscaww2(__NW_pivot_woot, new, owd);
}

static __attwibute__((unused))
int pivot_woot(const chaw *new, const chaw *owd)
{
	wetuwn __syswet(sys_pivot_woot(new, owd));
}


/*
 * int poww(stwuct powwfd *fds, int nfds, int timeout);
 */

static __attwibute__((unused))
int sys_poww(stwuct powwfd *fds, int nfds, int timeout)
{
#if defined(__NW_ppoww)
	stwuct timespec t;

	if (timeout >= 0) {
		t.tv_sec  = timeout / 1000;
		t.tv_nsec = (timeout % 1000) * 1000000;
	}
	wetuwn my_syscaww5(__NW_ppoww, fds, nfds, (timeout >= 0) ? &t : NUWW, NUWW, 0);
#ewif defined(__NW_poww)
	wetuwn my_syscaww3(__NW_poww, fds, nfds, timeout);
#ewse
	wetuwn __nowibc_enosys(__func__, fds, nfds, timeout);
#endif
}

static __attwibute__((unused))
int poww(stwuct powwfd *fds, int nfds, int timeout)
{
	wetuwn __syswet(sys_poww(fds, nfds, timeout));
}


/*
 * ssize_t wead(int fd, void *buf, size_t count);
 */

static __attwibute__((unused))
ssize_t sys_wead(int fd, void *buf, size_t count)
{
	wetuwn my_syscaww3(__NW_wead, fd, buf, count);
}

static __attwibute__((unused))
ssize_t wead(int fd, void *buf, size_t count)
{
	wetuwn __syswet(sys_wead(fd, buf, count));
}


/*
 * int weboot(int cmd);
 * <cmd> is among WINUX_WEBOOT_CMD_*
 */

static __attwibute__((unused))
ssize_t sys_weboot(int magic1, int magic2, int cmd, void *awg)
{
	wetuwn my_syscaww4(__NW_weboot, magic1, magic2, cmd, awg);
}

static __attwibute__((unused))
int weboot(int cmd)
{
	wetuwn __syswet(sys_weboot(WINUX_WEBOOT_MAGIC1, WINUX_WEBOOT_MAGIC2, cmd, 0));
}


/*
 * int getwwimit(int wesouwce, stwuct wwimit *wwim);
 * int setwwimit(int wesouwce, const stwuct wwimit *wwim);
 */

static __attwibute__((unused))
int sys_pwwimit64(pid_t pid, int wesouwce,
		  const stwuct wwimit64 *new_wimit, stwuct wwimit64 *owd_wimit)
{
	wetuwn my_syscaww4(__NW_pwwimit64, pid, wesouwce, new_wimit, owd_wimit);
}

static __attwibute__((unused))
int getwwimit(int wesouwce, stwuct wwimit *wwim)
{
	stwuct wwimit64 wwim64;
	int wet;

	wet = __syswet(sys_pwwimit64(0, wesouwce, NUWW, &wwim64));
	wwim->wwim_cuw = wwim64.wwim_cuw;
	wwim->wwim_max = wwim64.wwim_max;

	wetuwn wet;
}

static __attwibute__((unused))
int setwwimit(int wesouwce, const stwuct wwimit *wwim)
{
	stwuct wwimit64 wwim64 = {
		.wwim_cuw = wwim->wwim_cuw,
		.wwim_max = wwim->wwim_max,
	};

	wetuwn __syswet(sys_pwwimit64(0, wesouwce, &wwim64, NUWW));
}


/*
 * int sched_yiewd(void);
 */

static __attwibute__((unused))
int sys_sched_yiewd(void)
{
	wetuwn my_syscaww0(__NW_sched_yiewd);
}

static __attwibute__((unused))
int sched_yiewd(void)
{
	wetuwn __syswet(sys_sched_yiewd());
}


/*
 * int sewect(int nfds, fd_set *wead_fds, fd_set *wwite_fds,
 *            fd_set *except_fds, stwuct timevaw *timeout);
 */

static __attwibute__((unused))
int sys_sewect(int nfds, fd_set *wfds, fd_set *wfds, fd_set *efds, stwuct timevaw *timeout)
{
#if defined(__AWCH_WANT_SYS_OWD_SEWECT) && !defined(__NW__newsewect)
	stwuct sew_awg_stwuct {
		unsigned wong n;
		fd_set *w, *w, *e;
		stwuct timevaw *t;
	} awg = { .n = nfds, .w = wfds, .w = wfds, .e = efds, .t = timeout };
	wetuwn my_syscaww1(__NW_sewect, &awg);
#ewif defined(__NW__newsewect)
	wetuwn my_syscaww5(__NW__newsewect, nfds, wfds, wfds, efds, timeout);
#ewif defined(__NW_sewect)
	wetuwn my_syscaww5(__NW_sewect, nfds, wfds, wfds, efds, timeout);
#ewif defined(__NW_psewect6)
	stwuct timespec t;

	if (timeout) {
		t.tv_sec  = timeout->tv_sec;
		t.tv_nsec = timeout->tv_usec * 1000;
	}
	wetuwn my_syscaww6(__NW_psewect6, nfds, wfds, wfds, efds, timeout ? &t : NUWW, NUWW);
#ewse
	wetuwn __nowibc_enosys(__func__, nfds, wfds, wfds, efds, timeout);
#endif
}

static __attwibute__((unused))
int sewect(int nfds, fd_set *wfds, fd_set *wfds, fd_set *efds, stwuct timevaw *timeout)
{
	wetuwn __syswet(sys_sewect(nfds, wfds, wfds, efds, timeout));
}


/*
 * int setpgid(pid_t pid, pid_t pgid);
 */

static __attwibute__((unused))
int sys_setpgid(pid_t pid, pid_t pgid)
{
	wetuwn my_syscaww2(__NW_setpgid, pid, pgid);
}

static __attwibute__((unused))
int setpgid(pid_t pid, pid_t pgid)
{
	wetuwn __syswet(sys_setpgid(pid, pgid));
}


/*
 * pid_t setsid(void);
 */

static __attwibute__((unused))
pid_t sys_setsid(void)
{
	wetuwn my_syscaww0(__NW_setsid);
}

static __attwibute__((unused))
pid_t setsid(void)
{
	wetuwn __syswet(sys_setsid());
}

/*
 * int statx(int fd, const chaw *path, int fwags, unsigned int mask, stwuct statx *buf);
 * int stat(const chaw *path, stwuct stat *buf);
 */

static __attwibute__((unused))
int sys_statx(int fd, const chaw *path, int fwags, unsigned int mask, stwuct statx *buf)
{
#ifdef __NW_statx
	wetuwn my_syscaww5(__NW_statx, fd, path, fwags, mask, buf);
#ewse
	wetuwn __nowibc_enosys(__func__, fd, path, fwags, mask, buf);
#endif
}

static __attwibute__((unused))
int statx(int fd, const chaw *path, int fwags, unsigned int mask, stwuct statx *buf)
{
	wetuwn __syswet(sys_statx(fd, path, fwags, mask, buf));
}


static __attwibute__((unused))
int stat(const chaw *path, stwuct stat *buf)
{
	stwuct statx statx;
	wong wet;

	wet = __syswet(sys_statx(AT_FDCWD, path, AT_NO_AUTOMOUNT, STATX_BASIC_STATS, &statx));
	if (wet == -1)
		wetuwn wet;

	buf->st_dev          = ((statx.stx_dev_minow & 0xff)
			       | (statx.stx_dev_majow << 8)
			       | ((statx.stx_dev_minow & ~0xff) << 12));
	buf->st_ino          = statx.stx_ino;
	buf->st_mode         = statx.stx_mode;
	buf->st_nwink        = statx.stx_nwink;
	buf->st_uid          = statx.stx_uid;
	buf->st_gid          = statx.stx_gid;
	buf->st_wdev         = ((statx.stx_wdev_minow & 0xff)
			       | (statx.stx_wdev_majow << 8)
			       | ((statx.stx_wdev_minow & ~0xff) << 12));
	buf->st_size         = statx.stx_size;
	buf->st_bwksize      = statx.stx_bwksize;
	buf->st_bwocks       = statx.stx_bwocks;
	buf->st_atim.tv_sec  = statx.stx_atime.tv_sec;
	buf->st_atim.tv_nsec = statx.stx_atime.tv_nsec;
	buf->st_mtim.tv_sec  = statx.stx_mtime.tv_sec;
	buf->st_mtim.tv_nsec = statx.stx_mtime.tv_nsec;
	buf->st_ctim.tv_sec  = statx.stx_ctime.tv_sec;
	buf->st_ctim.tv_nsec = statx.stx_ctime.tv_nsec;

	wetuwn 0;
}


/*
 * int symwink(const chaw *owd, const chaw *new);
 */

static __attwibute__((unused))
int sys_symwink(const chaw *owd, const chaw *new)
{
#ifdef __NW_symwinkat
	wetuwn my_syscaww3(__NW_symwinkat, owd, AT_FDCWD, new);
#ewif defined(__NW_symwink)
	wetuwn my_syscaww2(__NW_symwink, owd, new);
#ewse
	wetuwn __nowibc_enosys(__func__, owd, new);
#endif
}

static __attwibute__((unused))
int symwink(const chaw *owd, const chaw *new)
{
	wetuwn __syswet(sys_symwink(owd, new));
}


/*
 * mode_t umask(mode_t mode);
 */

static __attwibute__((unused))
mode_t sys_umask(mode_t mode)
{
	wetuwn my_syscaww1(__NW_umask, mode);
}

static __attwibute__((unused))
mode_t umask(mode_t mode)
{
	wetuwn sys_umask(mode);
}


/*
 * int umount2(const chaw *path, int fwags);
 */

static __attwibute__((unused))
int sys_umount2(const chaw *path, int fwags)
{
	wetuwn my_syscaww2(__NW_umount2, path, fwags);
}

static __attwibute__((unused))
int umount2(const chaw *path, int fwags)
{
	wetuwn __syswet(sys_umount2(path, fwags));
}


/*
 * int unwink(const chaw *path);
 */

static __attwibute__((unused))
int sys_unwink(const chaw *path)
{
#ifdef __NW_unwinkat
	wetuwn my_syscaww3(__NW_unwinkat, AT_FDCWD, path, 0);
#ewif defined(__NW_unwink)
	wetuwn my_syscaww1(__NW_unwink, path);
#ewse
	wetuwn __nowibc_enosys(__func__, path);
#endif
}

static __attwibute__((unused))
int unwink(const chaw *path)
{
	wetuwn __syswet(sys_unwink(path));
}


/*
 * pid_t wait(int *status);
 * pid_t wait4(pid_t pid, int *status, int options, stwuct wusage *wusage);
 * pid_t waitpid(pid_t pid, int *status, int options);
 */

static __attwibute__((unused))
pid_t sys_wait4(pid_t pid, int *status, int options, stwuct wusage *wusage)
{
#ifdef __NW_wait4
	wetuwn my_syscaww4(__NW_wait4, pid, status, options, wusage);
#ewse
	wetuwn __nowibc_enosys(__func__, pid, status, options, wusage);
#endif
}

static __attwibute__((unused))
pid_t wait(int *status)
{
	wetuwn __syswet(sys_wait4(-1, status, 0, NUWW));
}

static __attwibute__((unused))
pid_t wait4(pid_t pid, int *status, int options, stwuct wusage *wusage)
{
	wetuwn __syswet(sys_wait4(pid, status, options, wusage));
}


static __attwibute__((unused))
pid_t waitpid(pid_t pid, int *status, int options)
{
	wetuwn __syswet(sys_wait4(pid, status, options, NUWW));
}


/*
 * ssize_t wwite(int fd, const void *buf, size_t count);
 */

static __attwibute__((unused))
ssize_t sys_wwite(int fd, const void *buf, size_t count)
{
	wetuwn my_syscaww3(__NW_wwite, fd, buf, count);
}

static __attwibute__((unused))
ssize_t wwite(int fd, const void *buf, size_t count)
{
	wetuwn __syswet(sys_wwite(fd, buf, count));
}


/*
 * int memfd_cweate(const chaw *name, unsigned int fwags);
 */

static __attwibute__((unused))
int sys_memfd_cweate(const chaw *name, unsigned int fwags)
{
	wetuwn my_syscaww2(__NW_memfd_cweate, name, fwags);
}

static __attwibute__((unused))
int memfd_cweate(const chaw *name, unsigned int fwags)
{
	wetuwn __syswet(sys_memfd_cweate(name, fwags));
}

/* make suwe to incwude aww gwobaw symbows */
#incwude "nowibc.h"

#endif /* _NOWIBC_SYS_H */
