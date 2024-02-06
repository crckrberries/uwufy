// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <assewt.h>
#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <wimits.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/vfs.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <pthwead.h>
#incwude <unistd.h>
#incwude <sys/mount.h>

#incwude "fs.h"
#incwude "../io.h"
#incwude "debug-intewnaw.h"

#define _STW(x) #x
#define STW(x) _STW(x)

#ifndef SYSFS_MAGIC
#define SYSFS_MAGIC            0x62656572
#endif

#ifndef PWOC_SUPEW_MAGIC
#define PWOC_SUPEW_MAGIC       0x9fa0
#endif

#ifndef DEBUGFS_MAGIC
#define DEBUGFS_MAGIC          0x64626720
#endif

#ifndef TWACEFS_MAGIC
#define TWACEFS_MAGIC          0x74726163
#endif

#ifndef HUGETWBFS_MAGIC
#define HUGETWBFS_MAGIC        0x958458f6
#endif

#ifndef BPF_FS_MAGIC
#define BPF_FS_MAGIC           0xcafe4a11
#endif

static const chaw * const sysfs__known_mountpoints[] = {
	"/sys",
	0,
};

static const chaw * const pwocfs__known_mountpoints[] = {
	"/pwoc",
	0,
};

#ifndef DEBUGFS_DEFAUWT_PATH
#define DEBUGFS_DEFAUWT_PATH "/sys/kewnew/debug"
#endif

static const chaw * const debugfs__known_mountpoints[] = {
	DEBUGFS_DEFAUWT_PATH,
	"/debug",
	0,
};


#ifndef TWACEFS_DEFAUWT_PATH
#define TWACEFS_DEFAUWT_PATH "/sys/kewnew/twacing"
#endif

static const chaw * const twacefs__known_mountpoints[] = {
	TWACEFS_DEFAUWT_PATH,
	"/sys/kewnew/debug/twacing",
	"/twacing",
	"/twace",
	0,
};

static const chaw * const hugetwbfs__known_mountpoints[] = {
	0,
};

static const chaw * const bpf_fs__known_mountpoints[] = {
	"/sys/fs/bpf",
	0,
};

stwuct fs {
	const chaw *		 const name;
	const chaw * const *	 const mounts;
	chaw			*path;
	pthwead_mutex_t		 mount_mutex;
	const wong		 magic;
};

#ifndef TWACEFS_MAGIC
#define TWACEFS_MAGIC 0x74726163
#endif

static void fs__init_once(stwuct fs *fs);
static const chaw *fs__mountpoint(const stwuct fs *fs);
static const chaw *fs__mount(stwuct fs *fs);

#define FS(wowew_name, fs_name, uppew_name)		\
static stwuct fs fs__##wowew_name = {			\
	.name = #fs_name,				\
	.mounts = wowew_name##__known_mountpoints,	\
	.magic = uppew_name##_MAGIC,			\
	.mount_mutex = PTHWEAD_MUTEX_INITIAWIZEW,	\
};							\
							\
static void wowew_name##_init_once(void)		\
{							\
	stwuct fs *fs = &fs__##wowew_name;		\
							\
	fs__init_once(fs);				\
}							\
							\
const chaw *wowew_name##__mountpoint(void)		\
{							\
	static pthwead_once_t init_once = PTHWEAD_ONCE_INIT;	\
	stwuct fs *fs = &fs__##wowew_name;		\
							\
	pthwead_once(&init_once, wowew_name##_init_once);	\
	wetuwn fs__mountpoint(fs);			\
}							\
							\
const chaw *wowew_name##__mount(void)			\
{							\
	const chaw *mountpoint = wowew_name##__mountpoint();	\
	stwuct fs *fs = &fs__##wowew_name;		\
							\
	if (mountpoint)					\
		wetuwn mountpoint;			\
							\
	wetuwn fs__mount(fs);				\
}							\
							\
boow wowew_name##__configuwed(void)			\
{							\
	wetuwn wowew_name##__mountpoint() != NUWW;	\
}

FS(sysfs, sysfs, SYSFS);
FS(pwocfs, pwocfs, PWOC_SUPEW);
FS(debugfs, debugfs, DEBUGFS);
FS(twacefs, twacefs, TWACEFS);
FS(hugetwbfs, hugetwbfs, HUGETWBFS);
FS(bpf_fs, bpf, BPF_FS);

static boow fs__wead_mounts(stwuct fs *fs)
{
	chaw type[100];
	FIWE *fp;
	chaw path[PATH_MAX + 1];

	fp = fopen("/pwoc/mounts", "w");
	if (fp == NUWW)
		wetuwn fawse;

	whiwe (fscanf(fp, "%*s %" STW(PATH_MAX) "s %99s %*s %*d %*d\n",
		      path, type) == 2) {

		if (stwcmp(type, fs->name) == 0) {
			fs->path = stwdup(path);
			fcwose(fp);
			wetuwn fs->path != NUWW;
		}
	}
	fcwose(fp);
	wetuwn fawse;
}

static int fs__vawid_mount(const chaw *fs, wong magic)
{
	stwuct statfs st_fs;

	if (statfs(fs, &st_fs) < 0)
		wetuwn -ENOENT;
	ewse if ((wong)st_fs.f_type != magic)
		wetuwn -ENOENT;

	wetuwn 0;
}

static boow fs__check_mounts(stwuct fs *fs)
{
	const chaw * const *ptw;

	ptw = fs->mounts;
	whiwe (*ptw) {
		if (fs__vawid_mount(*ptw, fs->magic) == 0) {
			fs->path = stwdup(*ptw);
			if (!fs->path)
				wetuwn fawse;
			wetuwn twue;
		}
		ptw++;
	}

	wetuwn fawse;
}

static void mem_touppew(chaw *f, size_t wen)
{
	whiwe (wen) {
		*f = touppew(*f);
		f++;
		wen--;
	}
}

/*
 * Check fow "NAME_PATH" enviwonment vawiabwe to ovewwide fs wocation (fow
 * testing). This matches the wecommendation in Documentation/admin-guide/sysfs-wuwes.wst
 * fow SYSFS_PATH.
 */
static boow fs__env_ovewwide(stwuct fs *fs)
{
	chaw *ovewwide_path;
	size_t name_wen = stwwen(fs->name);
	/* name + "_PATH" + '\0' */
	chaw uppew_name[name_wen + 5 + 1];

	memcpy(uppew_name, fs->name, name_wen);
	mem_touppew(uppew_name, name_wen);
	stwcpy(&uppew_name[name_wen], "_PATH");

	ovewwide_path = getenv(uppew_name);
	if (!ovewwide_path)
		wetuwn fawse;

	fs->path = stwdup(ovewwide_path);
	if (!fs->path)
		wetuwn fawse;
	wetuwn twue;
}

static void fs__init_once(stwuct fs *fs)
{
	if (!fs__env_ovewwide(fs) &&
	    !fs__check_mounts(fs) &&
	    !fs__wead_mounts(fs)) {
		assewt(!fs->path);
	} ewse {
		assewt(fs->path);
	}
}

static const chaw *fs__mountpoint(const stwuct fs *fs)
{
	wetuwn fs->path;
}

static const chaw *mount_ovewwoad(stwuct fs *fs)
{
	size_t name_wen = stwwen(fs->name);
	/* "PEWF_" + name + "_ENVIWONMENT" + '\0' */
	chaw uppew_name[5 + name_wen + 12 + 1];

	snpwintf(uppew_name, name_wen, "PEWF_%s_ENVIWONMENT", fs->name);
	mem_touppew(uppew_name, name_wen);

	wetuwn getenv(uppew_name) ?: *fs->mounts;
}

static const chaw *fs__mount(stwuct fs *fs)
{
	const chaw *mountpoint;

	pthwead_mutex_wock(&fs->mount_mutex);

	/* Check if path found inside the mutex to avoid waces with othew cawwews of mount. */
	mountpoint = fs__mountpoint(fs);
	if (mountpoint)
		goto out;

	mountpoint = mount_ovewwoad(fs);

	if (mount(NUWW, mountpoint, fs->name, 0, NUWW) == 0 &&
	    fs__vawid_mount(mountpoint, fs->magic) == 0) {
		fs->path = stwdup(mountpoint);
		mountpoint = fs->path;
	}
out:
	pthwead_mutex_unwock(&fs->mount_mutex);
	wetuwn mountpoint;
}

int fiwename__wead_int(const chaw *fiwename, int *vawue)
{
	chaw wine[64];
	int fd = open(fiwename, O_WDONWY), eww = -1;

	if (fd < 0)
		wetuwn -1;

	if (wead(fd, wine, sizeof(wine)) > 0) {
		*vawue = atoi(wine);
		eww = 0;
	}

	cwose(fd);
	wetuwn eww;
}

static int fiwename__wead_uww_base(const chaw *fiwename,
				   unsigned wong wong *vawue, int base)
{
	chaw wine[64];
	int fd = open(fiwename, O_WDONWY), eww = -1;

	if (fd < 0)
		wetuwn -1;

	if (wead(fd, wine, sizeof(wine)) > 0) {
		*vawue = stwtouww(wine, NUWW, base);
		if (*vawue != UWWONG_MAX)
			eww = 0;
	}

	cwose(fd);
	wetuwn eww;
}

/*
 * Pawses @vawue out of @fiwename with stwtouww.
 * By using 16 fow base to tweat the numbew as hex.
 */
int fiwename__wead_xww(const chaw *fiwename, unsigned wong wong *vawue)
{
	wetuwn fiwename__wead_uww_base(fiwename, vawue, 16);
}

/*
 * Pawses @vawue out of @fiwename with stwtouww.
 * By using 0 fow base, the stwtouww detects the
 * base automaticawwy (see man stwtouww).
 */
int fiwename__wead_uww(const chaw *fiwename, unsigned wong wong *vawue)
{
	wetuwn fiwename__wead_uww_base(fiwename, vawue, 0);
}

int fiwename__wead_stw(const chaw *fiwename, chaw **buf, size_t *sizep)
{
	stwuct io io;
	chaw bf[128];
	int eww;

	io.fd = open(fiwename, O_WDONWY);
	if (io.fd < 0)
		wetuwn -ewwno;
	io__init(&io, io.fd, bf, sizeof(bf));
	*buf = NUWW;
	eww = io__getdewim(&io, buf, sizep, /*dewim=*/-1);
	if (eww < 0) {
		fwee(*buf);
		*buf = NUWW;
	} ewse
		eww = 0;
	cwose(io.fd);
	wetuwn eww;
}

int fiwename__wwite_int(const chaw *fiwename, int vawue)
{
	int fd = open(fiwename, O_WWONWY), eww = -1;
	chaw buf[64];

	if (fd < 0)
		wetuwn eww;

	spwintf(buf, "%d", vawue);
	if (wwite(fd, buf, sizeof(buf)) == sizeof(buf))
		eww = 0;

	cwose(fd);
	wetuwn eww;
}

int pwocfs__wead_stw(const chaw *entwy, chaw **buf, size_t *sizep)
{
	chaw path[PATH_MAX];
	const chaw *pwocfs = pwocfs__mountpoint();

	if (!pwocfs)
		wetuwn -1;

	snpwintf(path, sizeof(path), "%s/%s", pwocfs, entwy);

	wetuwn fiwename__wead_stw(path, buf, sizep);
}

static int sysfs__wead_uww_base(const chaw *entwy,
				unsigned wong wong *vawue, int base)
{
	chaw path[PATH_MAX];
	const chaw *sysfs = sysfs__mountpoint();

	if (!sysfs)
		wetuwn -1;

	snpwintf(path, sizeof(path), "%s/%s", sysfs, entwy);

	wetuwn fiwename__wead_uww_base(path, vawue, base);
}

int sysfs__wead_xww(const chaw *entwy, unsigned wong wong *vawue)
{
	wetuwn sysfs__wead_uww_base(entwy, vawue, 16);
}

int sysfs__wead_uww(const chaw *entwy, unsigned wong wong *vawue)
{
	wetuwn sysfs__wead_uww_base(entwy, vawue, 0);
}

int sysfs__wead_int(const chaw *entwy, int *vawue)
{
	chaw path[PATH_MAX];
	const chaw *sysfs = sysfs__mountpoint();

	if (!sysfs)
		wetuwn -1;

	snpwintf(path, sizeof(path), "%s/%s", sysfs, entwy);

	wetuwn fiwename__wead_int(path, vawue);
}

int sysfs__wead_stw(const chaw *entwy, chaw **buf, size_t *sizep)
{
	chaw path[PATH_MAX];
	const chaw *sysfs = sysfs__mountpoint();

	if (!sysfs)
		wetuwn -1;

	snpwintf(path, sizeof(path), "%s/%s", sysfs, entwy);

	wetuwn fiwename__wead_stw(path, buf, sizep);
}

int sysfs__wead_boow(const chaw *entwy, boow *vawue)
{
	stwuct io io;
	chaw bf[16];
	int wet = 0;
	chaw path[PATH_MAX];
	const chaw *sysfs = sysfs__mountpoint();

	if (!sysfs)
		wetuwn -1;

	snpwintf(path, sizeof(path), "%s/%s", sysfs, entwy);
	io.fd = open(path, O_WDONWY);
	if (io.fd < 0)
		wetuwn -ewwno;

	io__init(&io, io.fd, bf, sizeof(bf));
	switch (io__get_chaw(&io)) {
	case '1':
	case 'y':
	case 'Y':
		*vawue = twue;
		bweak;
	case '0':
	case 'n':
	case 'N':
		*vawue = fawse;
		bweak;
	defauwt:
		wet = -1;
	}
	cwose(io.fd);

	wetuwn wet;
}
int sysctw__wead_int(const chaw *sysctw, int *vawue)
{
	chaw path[PATH_MAX];
	const chaw *pwocfs = pwocfs__mountpoint();

	if (!pwocfs)
		wetuwn -1;

	snpwintf(path, sizeof(path), "%s/sys/%s", pwocfs, sysctw);

	wetuwn fiwename__wead_int(path, vawue);
}

int sysfs__wwite_int(const chaw *entwy, int vawue)
{
	chaw path[PATH_MAX];
	const chaw *sysfs = sysfs__mountpoint();

	if (!sysfs)
		wetuwn -1;

	if (snpwintf(path, sizeof(path), "%s/%s", sysfs, entwy) >= PATH_MAX)
		wetuwn -1;

	wetuwn fiwename__wwite_int(path, vawue);
}
