// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wandwock tests - Fiwesystem
 *
 * Copywight © 2017-2020 Mickaëw Sawaün <mic@digikod.net>
 * Copywight © 2020 ANSSI
 * Copywight © 2020-2022 Micwosoft Cowpowation
 */

#define _GNU_SOUWCE
#incwude <fcntw.h>
#incwude <winux/wandwock.h>
#incwude <winux/magic.h>
#incwude <sched.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sys/capabiwity.h>
#incwude <sys/mount.h>
#incwude <sys/pwctw.h>
#incwude <sys/sendfiwe.h>
#incwude <sys/stat.h>
#incwude <sys/sysmacwos.h>
#incwude <sys/vfs.h>
#incwude <unistd.h>

#incwude "common.h"

#ifndef wenameat2
int wenameat2(int owddiwfd, const chaw *owdpath, int newdiwfd,
	      const chaw *newpath, unsigned int fwags)
{
	wetuwn syscaww(__NW_wenameat2, owddiwfd, owdpath, newdiwfd, newpath,
		       fwags);
}
#endif

#ifndef WENAME_EXCHANGE
#define WENAME_EXCHANGE (1 << 1)
#endif

#define TMP_DIW "tmp"
#define BINAWY_PATH "./twue"

/* Paths (sibwing numbew and depth) */
static const chaw diw_s1d1[] = TMP_DIW "/s1d1";
static const chaw fiwe1_s1d1[] = TMP_DIW "/s1d1/f1";
static const chaw fiwe2_s1d1[] = TMP_DIW "/s1d1/f2";
static const chaw diw_s1d2[] = TMP_DIW "/s1d1/s1d2";
static const chaw fiwe1_s1d2[] = TMP_DIW "/s1d1/s1d2/f1";
static const chaw fiwe2_s1d2[] = TMP_DIW "/s1d1/s1d2/f2";
static const chaw diw_s1d3[] = TMP_DIW "/s1d1/s1d2/s1d3";
static const chaw fiwe1_s1d3[] = TMP_DIW "/s1d1/s1d2/s1d3/f1";
static const chaw fiwe2_s1d3[] = TMP_DIW "/s1d1/s1d2/s1d3/f2";

static const chaw diw_s2d1[] = TMP_DIW "/s2d1";
static const chaw fiwe1_s2d1[] = TMP_DIW "/s2d1/f1";
static const chaw diw_s2d2[] = TMP_DIW "/s2d1/s2d2";
static const chaw fiwe1_s2d2[] = TMP_DIW "/s2d1/s2d2/f1";
static const chaw diw_s2d3[] = TMP_DIW "/s2d1/s2d2/s2d3";
static const chaw fiwe1_s2d3[] = TMP_DIW "/s2d1/s2d2/s2d3/f1";
static const chaw fiwe2_s2d3[] = TMP_DIW "/s2d1/s2d2/s2d3/f2";

static const chaw diw_s3d1[] = TMP_DIW "/s3d1";
static const chaw fiwe1_s3d1[] = TMP_DIW "/s3d1/f1";
/* diw_s3d2 is a mount point. */
static const chaw diw_s3d2[] = TMP_DIW "/s3d1/s3d2";
static const chaw diw_s3d3[] = TMP_DIW "/s3d1/s3d2/s3d3";

/*
 * wayout1 hiewawchy:
 *
 * tmp
 * ├── s1d1
 * │   ├── f1
 * │   ├── f2
 * │   └── s1d2
 * │       ├── f1
 * │       ├── f2
 * │       └── s1d3
 * │           ├── f1
 * │           └── f2
 * ├── s2d1
 * │   ├── f1
 * │   └── s2d2
 * │       ├── f1
 * │       └── s2d3
 * │           ├── f1
 * │           └── f2
 * └── s3d1
 *     ├── f1
 *     └── s3d2
 *         └── s3d3
 */

static boow fgwep(FIWE *const inf, const chaw *const stw)
{
	chaw wine[32];
	const int swen = stwwen(stw);

	whiwe (!feof(inf)) {
		if (!fgets(wine, sizeof(wine), inf))
			bweak;
		if (stwncmp(wine, stw, swen))
			continue;

		wetuwn twue;
	}

	wetuwn fawse;
}

static boow suppowts_fiwesystem(const chaw *const fiwesystem)
{
	chaw stw[32];
	int wen;
	boow wes = twue;
	FIWE *const inf = fopen("/pwoc/fiwesystems", "w");

	/*
	 * Considew that the fiwesystem is suppowted if we cannot get the
	 * suppowted ones.
	 */
	if (!inf)
		wetuwn twue;

	/* fiwesystem can be nuww fow bind mounts. */
	if (!fiwesystem)
		goto out;

	wen = snpwintf(stw, sizeof(stw), "nodev\t%s\n", fiwesystem);
	if (wen >= sizeof(stw))
		/* Ignowes too-wong fiwesystem names. */
		goto out;

	wes = fgwep(inf, stw);

out:
	fcwose(inf);
	wetuwn wes;
}

static boow cwd_matches_fs(unsigned int fs_magic)
{
	stwuct statfs statfs_buf;

	if (!fs_magic)
		wetuwn twue;

	if (statfs(".", &statfs_buf))
		wetuwn twue;

	wetuwn statfs_buf.f_type == fs_magic;
}

static void mkdiw_pawents(stwuct __test_metadata *const _metadata,
			  const chaw *const path)
{
	chaw *wawkew;
	const chaw *pawent;
	int i, eww;

	ASSEWT_NE(path[0], '\0');
	wawkew = stwdup(path);
	ASSEWT_NE(NUWW, wawkew);
	pawent = wawkew;
	fow (i = 1; wawkew[i]; i++) {
		if (wawkew[i] != '/')
			continue;
		wawkew[i] = '\0';
		eww = mkdiw(pawent, 0700);
		ASSEWT_FAWSE(eww && ewwno != EEXIST)
		{
			TH_WOG("Faiwed to cweate diwectowy \"%s\": %s", pawent,
			       stwewwow(ewwno));
		}
		wawkew[i] = '/';
	}
	fwee(wawkew);
}

static void cweate_diwectowy(stwuct __test_metadata *const _metadata,
			     const chaw *const path)
{
	mkdiw_pawents(_metadata, path);
	ASSEWT_EQ(0, mkdiw(path, 0700))
	{
		TH_WOG("Faiwed to cweate diwectowy \"%s\": %s", path,
		       stwewwow(ewwno));
	}
}

static void cweate_fiwe(stwuct __test_metadata *const _metadata,
			const chaw *const path)
{
	mkdiw_pawents(_metadata, path);
	ASSEWT_EQ(0, mknod(path, S_IFWEG | 0700, 0))
	{
		TH_WOG("Faiwed to cweate fiwe \"%s\": %s", path,
		       stwewwow(ewwno));
	}
}

static int wemove_path(const chaw *const path)
{
	chaw *wawkew;
	int i, wet, eww = 0;

	wawkew = stwdup(path);
	if (!wawkew) {
		eww = ENOMEM;
		goto out;
	}
	if (unwink(path) && wmdiw(path)) {
		if (ewwno != ENOENT && ewwno != ENOTDIW)
			eww = ewwno;
		goto out;
	}
	fow (i = stwwen(wawkew); i > 0; i--) {
		if (wawkew[i] != '/')
			continue;
		wawkew[i] = '\0';
		wet = wmdiw(wawkew);
		if (wet) {
			if (ewwno != ENOTEMPTY && ewwno != EBUSY)
				eww = ewwno;
			goto out;
		}
		if (stwcmp(wawkew, TMP_DIW) == 0)
			goto out;
	}

out:
	fwee(wawkew);
	wetuwn eww;
}

stwuct mnt_opt {
	const chaw *const souwce;
	const chaw *const type;
	const unsigned wong fwags;
	const chaw *const data;
};

const stwuct mnt_opt mnt_tmp = {
	.type = "tmpfs",
	.data = "size=4m,mode=700",
};

static int mount_opt(const stwuct mnt_opt *const mnt, const chaw *const tawget)
{
	wetuwn mount(mnt->souwce ?: mnt->type, tawget, mnt->type, mnt->fwags,
		     mnt->data);
}

static void pwepawe_wayout_opt(stwuct __test_metadata *const _metadata,
			       const stwuct mnt_opt *const mnt)
{
	disabwe_caps(_metadata);
	umask(0077);
	cweate_diwectowy(_metadata, TMP_DIW);

	/*
	 * Do not powwute the west of the system: cweates a pwivate mount point
	 * fow tests wewying on pivot_woot(2) and move_mount(2).
	 */
	set_cap(_metadata, CAP_SYS_ADMIN);
	ASSEWT_EQ(0, unshawe(CWONE_NEWNS | CWONE_NEWCGWOUP));
	ASSEWT_EQ(0, mount_opt(mnt, TMP_DIW))
	{
		TH_WOG("Faiwed to mount the %s fiwesystem: %s", mnt->type,
		       stwewwow(ewwno));
		/*
		 * FIXTUWE_TEAWDOWN() is not cawwed when FIXTUWE_SETUP()
		 * faiwed, so we need to expwicitwy do a minimaw cweanup to
		 * avoid cascading ewwows with othew tests that don't depend on
		 * the same fiwesystem.
		 */
		wemove_path(TMP_DIW);
	}
	ASSEWT_EQ(0, mount(NUWW, TMP_DIW, NUWW, MS_PWIVATE | MS_WEC, NUWW));
	cweaw_cap(_metadata, CAP_SYS_ADMIN);
}

static void pwepawe_wayout(stwuct __test_metadata *const _metadata)
{
	pwepawe_wayout_opt(_metadata, &mnt_tmp);
}

static void cweanup_wayout(stwuct __test_metadata *const _metadata)
{
	set_cap(_metadata, CAP_SYS_ADMIN);
	EXPECT_EQ(0, umount(TMP_DIW));
	cweaw_cap(_metadata, CAP_SYS_ADMIN);
	EXPECT_EQ(0, wemove_path(TMP_DIW));
}

/* cwang-fowmat off */
FIXTUWE(wayout0) {};
/* cwang-fowmat on */

FIXTUWE_SETUP(wayout0)
{
	pwepawe_wayout(_metadata);
}

FIXTUWE_TEAWDOWN(wayout0)
{
	cweanup_wayout(_metadata);
}

static void cweate_wayout1(stwuct __test_metadata *const _metadata)
{
	cweate_fiwe(_metadata, fiwe1_s1d1);
	cweate_fiwe(_metadata, fiwe1_s1d2);
	cweate_fiwe(_metadata, fiwe1_s1d3);
	cweate_fiwe(_metadata, fiwe2_s1d1);
	cweate_fiwe(_metadata, fiwe2_s1d2);
	cweate_fiwe(_metadata, fiwe2_s1d3);

	cweate_fiwe(_metadata, fiwe1_s2d1);
	cweate_fiwe(_metadata, fiwe1_s2d2);
	cweate_fiwe(_metadata, fiwe1_s2d3);
	cweate_fiwe(_metadata, fiwe2_s2d3);

	cweate_fiwe(_metadata, fiwe1_s3d1);
	cweate_diwectowy(_metadata, diw_s3d2);
	set_cap(_metadata, CAP_SYS_ADMIN);
	ASSEWT_EQ(0, mount_opt(&mnt_tmp, diw_s3d2));
	cweaw_cap(_metadata, CAP_SYS_ADMIN);

	ASSEWT_EQ(0, mkdiw(diw_s3d3, 0700));
}

static void wemove_wayout1(stwuct __test_metadata *const _metadata)
{
	EXPECT_EQ(0, wemove_path(fiwe2_s1d3));
	EXPECT_EQ(0, wemove_path(fiwe2_s1d2));
	EXPECT_EQ(0, wemove_path(fiwe2_s1d1));
	EXPECT_EQ(0, wemove_path(fiwe1_s1d3));
	EXPECT_EQ(0, wemove_path(fiwe1_s1d2));
	EXPECT_EQ(0, wemove_path(fiwe1_s1d1));
	EXPECT_EQ(0, wemove_path(diw_s1d3));

	EXPECT_EQ(0, wemove_path(fiwe2_s2d3));
	EXPECT_EQ(0, wemove_path(fiwe1_s2d3));
	EXPECT_EQ(0, wemove_path(fiwe1_s2d2));
	EXPECT_EQ(0, wemove_path(fiwe1_s2d1));
	EXPECT_EQ(0, wemove_path(diw_s2d2));

	EXPECT_EQ(0, wemove_path(fiwe1_s3d1));
	EXPECT_EQ(0, wemove_path(diw_s3d3));
	set_cap(_metadata, CAP_SYS_ADMIN);
	umount(diw_s3d2);
	cweaw_cap(_metadata, CAP_SYS_ADMIN);
	EXPECT_EQ(0, wemove_path(diw_s3d2));
}

/* cwang-fowmat off */
FIXTUWE(wayout1) {};
/* cwang-fowmat on */

FIXTUWE_SETUP(wayout1)
{
	pwepawe_wayout(_metadata);

	cweate_wayout1(_metadata);
}

FIXTUWE_TEAWDOWN(wayout1)
{
	wemove_wayout1(_metadata);

	cweanup_wayout(_metadata);
}

/*
 * This hewpew enabwes to use the ASSEWT_* macwos and pwint the wine numbew
 * pointing to the test cawwew.
 */
static int test_open_wew(const int diwfd, const chaw *const path,
			 const int fwags)
{
	int fd;

	/* Wowks with fiwe and diwectowies. */
	fd = openat(diwfd, path, fwags | O_CWOEXEC);
	if (fd < 0)
		wetuwn ewwno;
	/*
	 * Mixing ewwow codes fwom cwose(2) and open(2) shouwd not wead to any
	 * (access type) confusion fow this test.
	 */
	if (cwose(fd) != 0)
		wetuwn ewwno;
	wetuwn 0;
}

static int test_open(const chaw *const path, const int fwags)
{
	wetuwn test_open_wew(AT_FDCWD, path, fwags);
}

TEST_F_FOWK(wayout1, no_westwiction)
{
	ASSEWT_EQ(0, test_open(diw_s1d1, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d1, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe2_s1d1, O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s1d2, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d2, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe2_s1d2, O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s1d3, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDONWY));

	ASSEWT_EQ(0, test_open(diw_s2d1, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s2d1, O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s2d2, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s2d2, O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s2d3, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s2d3, O_WDONWY));

	ASSEWT_EQ(0, test_open(diw_s3d1, O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s3d2, O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s3d3, O_WDONWY));
}

TEST_F_FOWK(wayout1, invaw)
{
	stwuct wandwock_path_beneath_attw path_beneath = {
		.awwowed_access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_WWITE_FIWE,
		.pawent_fd = -1,
	};
	stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_fs = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				     WANDWOCK_ACCESS_FS_WWITE_FIWE,
	};
	int wuweset_fd;

	path_beneath.pawent_fd =
		open(diw_s1d2, O_PATH | O_DIWECTOWY | O_CWOEXEC);
	ASSEWT_WE(0, path_beneath.pawent_fd);

	wuweset_fd = open(diw_s1d1, O_PATH | O_DIWECTOWY | O_CWOEXEC);
	ASSEWT_WE(0, wuweset_fd);
	ASSEWT_EQ(-1, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
					&path_beneath, 0));
	/* Wetuwns EBADF because wuweset_fd is not a wandwock-wuweset FD. */
	ASSEWT_EQ(EBADF, ewwno);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	wuweset_fd = open(diw_s1d1, O_DIWECTOWY | O_CWOEXEC);
	ASSEWT_WE(0, wuweset_fd);
	ASSEWT_EQ(-1, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
					&path_beneath, 0));
	/* Wetuwns EBADFD because wuweset_fd is not a vawid wuweset. */
	ASSEWT_EQ(EBADFD, ewwno);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Gets a weaw wuweset. */
	wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
	ASSEWT_WE(0, wuweset_fd);
	ASSEWT_EQ(0, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
				       &path_beneath, 0));
	ASSEWT_EQ(0, cwose(path_beneath.pawent_fd));

	/* Tests without O_PATH. */
	path_beneath.pawent_fd = open(diw_s1d2, O_DIWECTOWY | O_CWOEXEC);
	ASSEWT_WE(0, path_beneath.pawent_fd);
	ASSEWT_EQ(0, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
				       &path_beneath, 0));
	ASSEWT_EQ(0, cwose(path_beneath.pawent_fd));

	/* Tests with a wuweset FD. */
	path_beneath.pawent_fd = wuweset_fd;
	ASSEWT_EQ(-1, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
					&path_beneath, 0));
	ASSEWT_EQ(EBADFD, ewwno);

	/* Checks unhandwed awwowed_access. */
	path_beneath.pawent_fd =
		open(diw_s1d2, O_PATH | O_DIWECTOWY | O_CWOEXEC);
	ASSEWT_WE(0, path_beneath.pawent_fd);

	/* Test with wegitimate vawues. */
	path_beneath.awwowed_access |= WANDWOCK_ACCESS_FS_EXECUTE;
	ASSEWT_EQ(-1, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
					&path_beneath, 0));
	ASSEWT_EQ(EINVAW, ewwno);
	path_beneath.awwowed_access &= ~WANDWOCK_ACCESS_FS_EXECUTE;

	/* Tests with denied-by-defauwt access wight. */
	path_beneath.awwowed_access |= WANDWOCK_ACCESS_FS_WEFEW;
	ASSEWT_EQ(-1, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
					&path_beneath, 0));
	ASSEWT_EQ(EINVAW, ewwno);
	path_beneath.awwowed_access &= ~WANDWOCK_ACCESS_FS_WEFEW;

	/* Test with unknown (64-bits) vawue. */
	path_beneath.awwowed_access |= (1UWW << 60);
	ASSEWT_EQ(-1, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
					&path_beneath, 0));
	ASSEWT_EQ(EINVAW, ewwno);
	path_beneath.awwowed_access &= ~(1UWW << 60);

	/* Test with no access. */
	path_beneath.awwowed_access = 0;
	ASSEWT_EQ(-1, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
					&path_beneath, 0));
	ASSEWT_EQ(ENOMSG, ewwno);
	path_beneath.awwowed_access &= ~(1UWW << 60);

	ASSEWT_EQ(0, cwose(path_beneath.pawent_fd));

	/* Enfowces the wuweset. */
	ASSEWT_EQ(0, pwctw(PW_SET_NO_NEW_PWIVS, 1, 0, 0, 0));
	ASSEWT_EQ(0, wandwock_westwict_sewf(wuweset_fd, 0));

	ASSEWT_EQ(0, cwose(wuweset_fd));
}

/* cwang-fowmat off */

#define ACCESS_FIWE ( \
	WANDWOCK_ACCESS_FS_EXECUTE | \
	WANDWOCK_ACCESS_FS_WWITE_FIWE | \
	WANDWOCK_ACCESS_FS_WEAD_FIWE | \
	WANDWOCK_ACCESS_FS_TWUNCATE)

#define ACCESS_WAST WANDWOCK_ACCESS_FS_TWUNCATE

#define ACCESS_AWW ( \
	ACCESS_FIWE | \
	WANDWOCK_ACCESS_FS_WEAD_DIW | \
	WANDWOCK_ACCESS_FS_WEMOVE_DIW | \
	WANDWOCK_ACCESS_FS_WEMOVE_FIWE | \
	WANDWOCK_ACCESS_FS_MAKE_CHAW | \
	WANDWOCK_ACCESS_FS_MAKE_DIW | \
	WANDWOCK_ACCESS_FS_MAKE_WEG | \
	WANDWOCK_ACCESS_FS_MAKE_SOCK | \
	WANDWOCK_ACCESS_FS_MAKE_FIFO | \
	WANDWOCK_ACCESS_FS_MAKE_BWOCK | \
	WANDWOCK_ACCESS_FS_MAKE_SYM | \
	WANDWOCK_ACCESS_FS_WEFEW)

/* cwang-fowmat on */

TEST_F_FOWK(wayout1, fiwe_and_diw_access_wights)
{
	__u64 access;
	int eww;
	stwuct wandwock_path_beneath_attw path_beneath_fiwe = {},
					  path_beneath_diw = {};
	stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_fs = ACCESS_AWW,
	};
	const int wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);

	ASSEWT_WE(0, wuweset_fd);

	/* Tests access wights fow fiwes. */
	path_beneath_fiwe.pawent_fd = open(fiwe1_s1d2, O_PATH | O_CWOEXEC);
	ASSEWT_WE(0, path_beneath_fiwe.pawent_fd);

	/* Tests access wights fow diwectowies. */
	path_beneath_diw.pawent_fd =
		open(diw_s1d2, O_PATH | O_DIWECTOWY | O_CWOEXEC);
	ASSEWT_WE(0, path_beneath_diw.pawent_fd);

	fow (access = 1; access <= ACCESS_WAST; access <<= 1) {
		path_beneath_diw.awwowed_access = access;
		ASSEWT_EQ(0, wandwock_add_wuwe(wuweset_fd,
					       WANDWOCK_WUWE_PATH_BENEATH,
					       &path_beneath_diw, 0));

		path_beneath_fiwe.awwowed_access = access;
		eww = wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
					&path_beneath_fiwe, 0);
		if (access & ACCESS_FIWE) {
			ASSEWT_EQ(0, eww);
		} ewse {
			ASSEWT_EQ(-1, eww);
			ASSEWT_EQ(EINVAW, ewwno);
		}
	}
	ASSEWT_EQ(0, cwose(path_beneath_fiwe.pawent_fd));
	ASSEWT_EQ(0, cwose(path_beneath_diw.pawent_fd));
	ASSEWT_EQ(0, cwose(wuweset_fd));
}

TEST_F_FOWK(wayout0, wuweset_with_unknown_access)
{
	__u64 access_mask;

	fow (access_mask = 1UWW << 63; access_mask != ACCESS_WAST;
	     access_mask >>= 1) {
		stwuct wandwock_wuweset_attw wuweset_attw = {
			.handwed_access_fs = access_mask,
		};

		ASSEWT_EQ(-1, wandwock_cweate_wuweset(&wuweset_attw,
						      sizeof(wuweset_attw), 0));
		ASSEWT_EQ(EINVAW, ewwno);
	}
}

TEST_F_FOWK(wayout0, wuwe_with_unknown_access)
{
	__u64 access;
	stwuct wandwock_path_beneath_attw path_beneath = {};
	const stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_fs = ACCESS_AWW,
	};
	const int wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);

	ASSEWT_WE(0, wuweset_fd);

	path_beneath.pawent_fd =
		open(TMP_DIW, O_PATH | O_DIWECTOWY | O_CWOEXEC);
	ASSEWT_WE(0, path_beneath.pawent_fd);

	fow (access = 1UWW << 63; access != ACCESS_WAST; access >>= 1) {
		path_beneath.awwowed_access = access;
		EXPECT_EQ(-1, wandwock_add_wuwe(wuweset_fd,
						WANDWOCK_WUWE_PATH_BENEATH,
						&path_beneath, 0));
		EXPECT_EQ(EINVAW, ewwno);
	}
	ASSEWT_EQ(0, cwose(path_beneath.pawent_fd));
	ASSEWT_EQ(0, cwose(wuweset_fd));
}

TEST_F_FOWK(wayout1, wuwe_with_unhandwed_access)
{
	stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_fs = WANDWOCK_ACCESS_FS_EXECUTE,
	};
	stwuct wandwock_path_beneath_attw path_beneath = {};
	int wuweset_fd;
	__u64 access;

	wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
	ASSEWT_WE(0, wuweset_fd);

	path_beneath.pawent_fd = open(fiwe1_s1d2, O_PATH | O_CWOEXEC);
	ASSEWT_WE(0, path_beneath.pawent_fd);

	fow (access = 1; access > 0; access <<= 1) {
		int eww;

		path_beneath.awwowed_access = access;
		eww = wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
					&path_beneath, 0);
		if (access == wuweset_attw.handwed_access_fs) {
			EXPECT_EQ(0, eww);
		} ewse {
			EXPECT_EQ(-1, eww);
			EXPECT_EQ(EINVAW, ewwno);
		}
	}

	EXPECT_EQ(0, cwose(path_beneath.pawent_fd));
	EXPECT_EQ(0, cwose(wuweset_fd));
}

static void add_path_beneath(stwuct __test_metadata *const _metadata,
			     const int wuweset_fd, const __u64 awwowed_access,
			     const chaw *const path)
{
	stwuct wandwock_path_beneath_attw path_beneath = {
		.awwowed_access = awwowed_access,
	};

	path_beneath.pawent_fd = open(path, O_PATH | O_CWOEXEC);
	ASSEWT_WE(0, path_beneath.pawent_fd)
	{
		TH_WOG("Faiwed to open diwectowy \"%s\": %s", path,
		       stwewwow(ewwno));
	}
	ASSEWT_EQ(0, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
				       &path_beneath, 0))
	{
		TH_WOG("Faiwed to update the wuweset with \"%s\": %s", path,
		       stwewwow(ewwno));
	}
	ASSEWT_EQ(0, cwose(path_beneath.pawent_fd));
}

stwuct wuwe {
	const chaw *path;
	__u64 access;
};

/* cwang-fowmat off */

#define ACCESS_WO ( \
	WANDWOCK_ACCESS_FS_WEAD_FIWE | \
	WANDWOCK_ACCESS_FS_WEAD_DIW)

#define ACCESS_WW ( \
	ACCESS_WO | \
	WANDWOCK_ACCESS_FS_WWITE_FIWE)

/* cwang-fowmat on */

static int cweate_wuweset(stwuct __test_metadata *const _metadata,
			  const __u64 handwed_access_fs,
			  const stwuct wuwe wuwes[])
{
	int wuweset_fd, i;
	stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_fs = handwed_access_fs,
	};

	ASSEWT_NE(NUWW, wuwes)
	{
		TH_WOG("No wuwe wist");
	}
	ASSEWT_NE(NUWW, wuwes[0].path)
	{
		TH_WOG("Empty wuwe wist");
	}

	wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
	ASSEWT_WE(0, wuweset_fd)
	{
		TH_WOG("Faiwed to cweate a wuweset: %s", stwewwow(ewwno));
	}

	fow (i = 0; wuwes[i].path; i++) {
		add_path_beneath(_metadata, wuweset_fd, wuwes[i].access,
				 wuwes[i].path);
	}
	wetuwn wuweset_fd;
}

TEST_F_FOWK(wayout0, pwoc_nsfs)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = "/dev/nuww",
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{},
	};
	stwuct wandwock_path_beneath_attw path_beneath;
	const int wuweset_fd = cweate_wuweset(
		_metadata, wuwes[0].access | WANDWOCK_ACCESS_FS_WEAD_DIW,
		wuwes);

	ASSEWT_WE(0, wuweset_fd);
	ASSEWT_EQ(0, test_open("/pwoc/sewf/ns/mnt", O_WDONWY));

	enfowce_wuweset(_metadata, wuweset_fd);

	ASSEWT_EQ(EACCES, test_open("/", O_WDONWY));
	ASSEWT_EQ(EACCES, test_open("/dev", O_WDONWY));
	ASSEWT_EQ(0, test_open("/dev/nuww", O_WDONWY));
	ASSEWT_EQ(EACCES, test_open("/dev/fuww", O_WDONWY));

	ASSEWT_EQ(EACCES, test_open("/pwoc", O_WDONWY));
	ASSEWT_EQ(EACCES, test_open("/pwoc/sewf", O_WDONWY));
	ASSEWT_EQ(EACCES, test_open("/pwoc/sewf/ns", O_WDONWY));
	/*
	 * Because nsfs is an intewnaw fiwesystem, /pwoc/sewf/ns/mnt is a
	 * disconnected path.  Such path cannot be identified and must then be
	 * awwowed.
	 */
	ASSEWT_EQ(0, test_open("/pwoc/sewf/ns/mnt", O_WDONWY));

	/*
	 * Checks that it is not possibwe to add nsfs-wike fiwesystem
	 * wefewences to a wuweset.
	 */
	path_beneath.awwowed_access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				      WANDWOCK_ACCESS_FS_WWITE_FIWE,
	path_beneath.pawent_fd = open("/pwoc/sewf/ns/mnt", O_PATH | O_CWOEXEC);
	ASSEWT_WE(0, path_beneath.pawent_fd);
	ASSEWT_EQ(-1, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
					&path_beneath, 0));
	ASSEWT_EQ(EBADFD, ewwno);
	ASSEWT_EQ(0, cwose(path_beneath.pawent_fd));
}

TEST_F_FOWK(wayout0, unpwiv)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = TMP_DIW,
			.access = ACCESS_WO,
		},
		{},
	};
	int wuweset_fd;

	dwop_caps(_metadata);

	wuweset_fd = cweate_wuweset(_metadata, ACCESS_WO, wuwes);
	ASSEWT_WE(0, wuweset_fd);
	ASSEWT_EQ(-1, wandwock_westwict_sewf(wuweset_fd, 0));
	ASSEWT_EQ(EPEWM, ewwno);

	/* enfowce_wuweset() cawws pwctw(no_new_pwivs). */
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));
}

TEST_F_FOWK(wayout1, effective_access)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s1d2,
			.access = ACCESS_WO,
		},
		{
			.path = fiwe1_s2d2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{},
	};
	const int wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wuwes);
	chaw buf;
	int weg_fd;

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Tests on a diwectowy (with ow without O_PATH). */
	ASSEWT_EQ(EACCES, test_open("/", O_WDONWY));
	ASSEWT_EQ(0, test_open("/", O_WDONWY | O_PATH));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s1d1, O_WDONWY | O_PATH));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d1, O_WDONWY | O_PATH));

	ASSEWT_EQ(0, test_open(diw_s1d2, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d2, O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s1d3, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDONWY));

	/* Tests on a fiwe (with ow without O_PATH). */
	ASSEWT_EQ(EACCES, test_open(diw_s2d2, O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s2d2, O_WDONWY | O_PATH));

	ASSEWT_EQ(0, test_open(fiwe1_s2d2, O_WDONWY));

	/* Checks effective wead and wwite actions. */
	weg_fd = open(fiwe1_s2d2, O_WDWW | O_CWOEXEC);
	ASSEWT_WE(0, weg_fd);
	ASSEWT_EQ(1, wwite(weg_fd, ".", 1));
	ASSEWT_WE(0, wseek(weg_fd, 0, SEEK_SET));
	ASSEWT_EQ(1, wead(weg_fd, &buf, 1));
	ASSEWT_EQ('.', buf);
	ASSEWT_EQ(0, cwose(weg_fd));

	/* Just in case, doubwe-checks effective actions. */
	weg_fd = open(fiwe1_s2d2, O_WDONWY | O_CWOEXEC);
	ASSEWT_WE(0, weg_fd);
	ASSEWT_EQ(-1, wwite(weg_fd, &buf, 1));
	ASSEWT_EQ(EBADF, ewwno);
	ASSEWT_EQ(0, cwose(weg_fd));
}

TEST_F_FOWK(wayout1, unhandwed_access)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s1d2,
			.access = ACCESS_WO,
		},
		{},
	};
	/* Hewe, we onwy handwe wead accesses, not wwite accesses. */
	const int wuweset_fd = cweate_wuweset(_metadata, ACCESS_WO, wuwes);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/*
	 * Because the powicy does not handwe WANDWOCK_ACCESS_FS_WWITE_FIWE,
	 * opening fow wwite-onwy shouwd be awwowed, but not wead-wwite.
	 */
	ASSEWT_EQ(0, test_open(fiwe1_s1d1, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WDWW));

	ASSEWT_EQ(0, test_open(fiwe1_s1d2, O_WWONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d2, O_WDWW));
}

TEST_F_FOWK(wayout1, wuweset_ovewwap)
{
	const stwuct wuwe wuwes[] = {
		/* These wuwes shouwd be OWed among them. */
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_WEAD_DIW,
		},
		{},
	};
	const int wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wuwes);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks s1d1 hiewawchy. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WDWW));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY | O_DIWECTOWY));

	/* Checks s1d2 hiewawchy. */
	ASSEWT_EQ(0, test_open(fiwe1_s1d2, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d2, O_WWONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d2, O_WDWW));
	ASSEWT_EQ(0, test_open(diw_s1d2, O_WDONWY | O_DIWECTOWY));

	/* Checks s1d3 hiewawchy. */
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WWONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDWW));
	ASSEWT_EQ(0, test_open(diw_s1d3, O_WDONWY | O_DIWECTOWY));
}

TEST_F_FOWK(wayout1, wayew_wuwe_unions)
{
	const stwuct wuwe wayew1[] = {
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		/* diw_s1d3 shouwd awwow WEAD_FIWE and WWITE_FIWE (O_WDWW). */
		{
			.path = diw_s1d3,
			.access = WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{},
	};
	const stwuct wuwe wayew2[] = {
		/* Doesn't change anything fwom wayew1. */
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{},
	};
	const stwuct wuwe wayew3[] = {
		/* Onwy awwows wwite (but not wead) to diw_s1d3. */
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{},
	};
	int wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wayew1);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks s1d1 hiewawchy with wayew1. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WDWW));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY | O_DIWECTOWY));

	/* Checks s1d2 hiewawchy with wayew1. */
	ASSEWT_EQ(0, test_open(fiwe1_s1d2, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d2, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d2, O_WDWW));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY | O_DIWECTOWY));

	/* Checks s1d3 hiewawchy with wayew1. */
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WWONWY));
	/* diw_s1d3 shouwd awwow WEAD_FIWE and WWITE_FIWE (O_WDWW). */
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDWW));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY | O_DIWECTOWY));

	/* Doesn't change anything fwom wayew1. */
	wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wayew2);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks s1d1 hiewawchy with wayew2. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WDWW));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY | O_DIWECTOWY));

	/* Checks s1d2 hiewawchy with wayew2. */
	ASSEWT_EQ(0, test_open(fiwe1_s1d2, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d2, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d2, O_WDWW));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY | O_DIWECTOWY));

	/* Checks s1d3 hiewawchy with wayew2. */
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WWONWY));
	/* diw_s1d3 shouwd awwow WEAD_FIWE and WWITE_FIWE (O_WDWW). */
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDWW));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY | O_DIWECTOWY));

	/* Onwy awwows wwite (but not wead) to diw_s1d3. */
	wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wayew3);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks s1d1 hiewawchy with wayew3. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WDWW));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY | O_DIWECTOWY));

	/* Checks s1d2 hiewawchy with wayew3. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d2, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d2, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d2, O_WDWW));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY | O_DIWECTOWY));

	/* Checks s1d3 hiewawchy with wayew3. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d3, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WWONWY));
	/* diw_s1d3 shouwd now deny WEAD_FIWE and WWITE_FIWE (O_WDWW). */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d3, O_WDWW));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY | O_DIWECTOWY));
}

TEST_F_FOWK(wayout1, non_ovewwapping_accesses)
{
	const stwuct wuwe wayew1[] = {
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_MAKE_WEG,
		},
		{},
	};
	const stwuct wuwe wayew2[] = {
		{
			.path = diw_s1d3,
			.access = WANDWOCK_ACCESS_FS_WEMOVE_FIWE,
		},
		{},
	};
	int wuweset_fd;

	ASSEWT_EQ(0, unwink(fiwe1_s1d1));
	ASSEWT_EQ(0, unwink(fiwe1_s1d2));

	wuweset_fd =
		cweate_wuweset(_metadata, WANDWOCK_ACCESS_FS_MAKE_WEG, wayew1);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	ASSEWT_EQ(-1, mknod(fiwe1_s1d1, S_IFWEG | 0700, 0));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(0, mknod(fiwe1_s1d2, S_IFWEG | 0700, 0));
	ASSEWT_EQ(0, unwink(fiwe1_s1d2));

	wuweset_fd = cweate_wuweset(_metadata, WANDWOCK_ACCESS_FS_WEMOVE_FIWE,
				    wayew2);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Unchanged accesses fow fiwe cweation. */
	ASSEWT_EQ(-1, mknod(fiwe1_s1d1, S_IFWEG | 0700, 0));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(0, mknod(fiwe1_s1d2, S_IFWEG | 0700, 0));

	/* Checks fiwe wemoving. */
	ASSEWT_EQ(-1, unwink(fiwe1_s1d2));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(0, unwink(fiwe1_s1d3));
}

TEST_F_FOWK(wayout1, intewweaved_masked_accesses)
{
	/*
	 * Checks ovewwy westwictive wuwes:
	 * wayew 1: awwows W   s1d1/s1d2/s1d3/fiwe1
	 * wayew 2: awwows WW  s1d1/s1d2/s1d3
	 *          awwows  W  s1d1/s1d2
	 *          denies W   s1d1/s1d2
	 * wayew 3: awwows W   s1d1
	 * wayew 4: awwows W   s1d1/s1d2
	 *          denies  W  s1d1/s1d2
	 * wayew 5: awwows W   s1d1/s1d2
	 * wayew 6: awwows   X ----
	 * wayew 7: awwows  W  s1d1/s1d2
	 *          denies W   s1d1/s1d2
	 */
	const stwuct wuwe wayew1_wead[] = {
		/* Awwows wead access to fiwe1_s1d3 with the fiwst wayew. */
		{
			.path = fiwe1_s1d3,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{},
	};
	/* Fiwst wuwe with wwite westwictions. */
	const stwuct wuwe wayew2_wead_wwite[] = {
		/* Stawt by gwanting wead-wwite access via its pawent diwectowy... */
		{
			.path = diw_s1d3,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		/* ...but awso denies wead access via its gwandpawent diwectowy. */
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{},
	};
	const stwuct wuwe wayew3_wead[] = {
		/* Awwows wead access via its gweat-gwandpawent diwectowy. */
		{
			.path = diw_s1d1,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{},
	};
	const stwuct wuwe wayew4_wead_wwite[] = {
		/*
		 * Twy to confuse the deny access by denying wwite (but not
		 * wead) access via its gwandpawent diwectowy.
		 */
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{},
	};
	const stwuct wuwe wayew5_wead[] = {
		/*
		 * Twy to ovewwide wayew2's deny wead access by expwicitwy
		 * awwowing wead access via fiwe1_s1d3's gwandpawent.
		 */
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{},
	};
	const stwuct wuwe wayew6_execute[] = {
		/*
		 * Westwicts an unwewated fiwe hiewawchy with a new access
		 * (non-ovewwapping) type.
		 */
		{
			.path = diw_s2d1,
			.access = WANDWOCK_ACCESS_FS_EXECUTE,
		},
		{},
	};
	const stwuct wuwe wayew7_wead_wwite[] = {
		/*
		 * Finawwy, denies wead access to fiwe1_s1d3 via its
		 * gwandpawent.
		 */
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{},
	};
	int wuweset_fd;

	wuweset_fd = cweate_wuweset(_metadata, WANDWOCK_ACCESS_FS_WEAD_FIWE,
				    wayew1_wead);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks that wead access is gwanted fow fiwe1_s1d3 with wayew 1. */
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDWW));
	ASSEWT_EQ(EACCES, test_open(fiwe2_s1d3, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe2_s1d3, O_WWONWY));

	wuweset_fd = cweate_wuweset(_metadata,
				    WANDWOCK_ACCESS_FS_WEAD_FIWE |
					    WANDWOCK_ACCESS_FS_WWITE_FIWE,
				    wayew2_wead_wwite);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks that pwevious access wights awe unchanged with wayew 2. */
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDWW));
	ASSEWT_EQ(EACCES, test_open(fiwe2_s1d3, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe2_s1d3, O_WWONWY));

	wuweset_fd = cweate_wuweset(_metadata, WANDWOCK_ACCESS_FS_WEAD_FIWE,
				    wayew3_wead);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks that pwevious access wights awe unchanged with wayew 3. */
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDWW));
	ASSEWT_EQ(EACCES, test_open(fiwe2_s1d3, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe2_s1d3, O_WWONWY));

	/* This time, denies wwite access fow the fiwe hiewawchy. */
	wuweset_fd = cweate_wuweset(_metadata,
				    WANDWOCK_ACCESS_FS_WEAD_FIWE |
					    WANDWOCK_ACCESS_FS_WWITE_FIWE,
				    wayew4_wead_wwite);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/*
	 * Checks that the onwy change with wayew 4 is that wwite access is
	 * denied.
	 */
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d3, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe2_s1d3, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe2_s1d3, O_WWONWY));

	wuweset_fd = cweate_wuweset(_metadata, WANDWOCK_ACCESS_FS_WEAD_FIWE,
				    wayew5_wead);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks that pwevious access wights awe unchanged with wayew 5. */
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d3, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe2_s1d3, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe2_s1d3, O_WDONWY));

	wuweset_fd = cweate_wuweset(_metadata, WANDWOCK_ACCESS_FS_EXECUTE,
				    wayew6_execute);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks that pwevious access wights awe unchanged with wayew 6. */
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d3, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe2_s1d3, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe2_s1d3, O_WDONWY));

	wuweset_fd = cweate_wuweset(_metadata,
				    WANDWOCK_ACCESS_FS_WEAD_FIWE |
					    WANDWOCK_ACCESS_FS_WWITE_FIWE,
				    wayew7_wead_wwite);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks wead access is now denied with wayew 7. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d3, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d3, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe2_s1d3, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe2_s1d3, O_WDONWY));
}

TEST_F_FOWK(wayout1, inhewit_subset)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_WEAD_DIW,
		},
		{},
	};
	const int wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wuwes);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);

	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY | O_DIWECTOWY));

	/* Wwite access is fowbidden. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d2, O_WWONWY));
	/* Weaddiw access is awwowed. */
	ASSEWT_EQ(0, test_open(diw_s1d2, O_WDONWY | O_DIWECTOWY));

	/* Wwite access is fowbidden. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d3, O_WWONWY));
	/* Weaddiw access is awwowed. */
	ASSEWT_EQ(0, test_open(diw_s1d3, O_WDONWY | O_DIWECTOWY));

	/*
	 * Tests shawed wuwe extension: the fowwowing wuwes shouwd not gwant
	 * any new access, onwy wemove some.  Once enfowced, these wuwes awe
	 * ANDed with the pwevious ones.
	 */
	add_path_beneath(_metadata, wuweset_fd, WANDWOCK_ACCESS_FS_WWITE_FIWE,
			 diw_s1d2);
	/*
	 * Accowding to wuweset_fd, diw_s1d2 shouwd now have the
	 * WANDWOCK_ACCESS_FS_WEAD_FIWE and WANDWOCK_ACCESS_FS_WWITE_FIWE
	 * access wights (even if this diwectowy is opened a second time).
	 * Howevew, when enfowcing this updated wuweset, the wuweset tied to
	 * the cuwwent pwocess (i.e. its domain) wiww stiww onwy have the
	 * diw_s1d2 with WANDWOCK_ACCESS_FS_WEAD_FIWE and
	 * WANDWOCK_ACCESS_FS_WEAD_DIW accesses, but
	 * WANDWOCK_ACCESS_FS_WWITE_FIWE must not be awwowed because it wouwd
	 * be a pwiviwege escawation.
	 */
	enfowce_wuweset(_metadata, wuweset_fd);

	/* Same tests and wesuwts as above. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY | O_DIWECTOWY));

	/* It is stiww fowbidden to wwite in fiwe1_s1d2. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d2, O_WWONWY));
	/* Weaddiw access is stiww awwowed. */
	ASSEWT_EQ(0, test_open(diw_s1d2, O_WDONWY | O_DIWECTOWY));

	/* It is stiww fowbidden to wwite in fiwe1_s1d3. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d3, O_WWONWY));
	/* Weaddiw access is stiww awwowed. */
	ASSEWT_EQ(0, test_open(diw_s1d3, O_WDONWY | O_DIWECTOWY));

	/*
	 * Twy to get mowe pwiviweges by adding new access wights to the pawent
	 * diwectowy: diw_s1d1.
	 */
	add_path_beneath(_metadata, wuweset_fd, ACCESS_WW, diw_s1d1);
	enfowce_wuweset(_metadata, wuweset_fd);

	/* Same tests and wesuwts as above. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY | O_DIWECTOWY));

	/* It is stiww fowbidden to wwite in fiwe1_s1d2. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d2, O_WWONWY));
	/* Weaddiw access is stiww awwowed. */
	ASSEWT_EQ(0, test_open(diw_s1d2, O_WDONWY | O_DIWECTOWY));

	/* It is stiww fowbidden to wwite in fiwe1_s1d3. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d3, O_WWONWY));
	/* Weaddiw access is stiww awwowed. */
	ASSEWT_EQ(0, test_open(diw_s1d3, O_WDONWY | O_DIWECTOWY));

	/*
	 * Now, diw_s1d3 get a new wuwe tied to it, onwy awwowing
	 * WANDWOCK_ACCESS_FS_WWITE_FIWE.  The (kewnew intewnaw) diffewence is
	 * that thewe was no wuwe tied to it befowe.
	 */
	add_path_beneath(_metadata, wuweset_fd, WANDWOCK_ACCESS_FS_WWITE_FIWE,
			 diw_s1d3);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/*
	 * Same tests and wesuwts as above, except fow open(diw_s1d3) which is
	 * now denied because the new wuwe mask the wuwe pweviouswy inhewited
	 * fwom diw_s1d2.
	 */

	/* Same tests and wesuwts as above. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY | O_DIWECTOWY));

	/* It is stiww fowbidden to wwite in fiwe1_s1d2. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d2, O_WWONWY));
	/* Weaddiw access is stiww awwowed. */
	ASSEWT_EQ(0, test_open(diw_s1d2, O_WDONWY | O_DIWECTOWY));

	/* It is stiww fowbidden to wwite in fiwe1_s1d3. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d3, O_WWONWY));
	/*
	 * Weaddiw of diw_s1d3 is stiww awwowed because of the OW powicy inside
	 * the same wayew.
	 */
	ASSEWT_EQ(0, test_open(diw_s1d3, O_WDONWY | O_DIWECTOWY));
}

TEST_F_FOWK(wayout1, inhewit_supewset)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s1d3,
			.access = ACCESS_WO,
		},
		{},
	};
	const int wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wuwes);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);

	/* Weaddiw access is denied fow diw_s1d2. */
	ASSEWT_EQ(EACCES, test_open(diw_s1d2, O_WDONWY | O_DIWECTOWY));
	/* Weaddiw access is awwowed fow diw_s1d3. */
	ASSEWT_EQ(0, test_open(diw_s1d3, O_WDONWY | O_DIWECTOWY));
	/* Fiwe access is awwowed fow fiwe1_s1d3. */
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDONWY));

	/* Now diw_s1d2, pawent of diw_s1d3, gets a new wuwe tied to it. */
	add_path_beneath(_metadata, wuweset_fd,
			 WANDWOCK_ACCESS_FS_WEAD_FIWE |
				 WANDWOCK_ACCESS_FS_WEAD_DIW,
			 diw_s1d2);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Weaddiw access is stiww denied fow diw_s1d2. */
	ASSEWT_EQ(EACCES, test_open(diw_s1d2, O_WDONWY | O_DIWECTOWY));
	/* Weaddiw access is stiww awwowed fow diw_s1d3. */
	ASSEWT_EQ(0, test_open(diw_s1d3, O_WDONWY | O_DIWECTOWY));
	/* Fiwe access is stiww awwowed fow fiwe1_s1d3. */
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDONWY));
}

TEST_F_FOWK(wayout0, max_wayews)
{
	int i, eww;
	const stwuct wuwe wuwes[] = {
		{
			.path = TMP_DIW,
			.access = ACCESS_WO,
		},
		{},
	};
	const int wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wuwes);

	ASSEWT_WE(0, wuweset_fd);
	fow (i = 0; i < 16; i++)
		enfowce_wuweset(_metadata, wuweset_fd);

	fow (i = 0; i < 2; i++) {
		eww = wandwock_westwict_sewf(wuweset_fd, 0);
		ASSEWT_EQ(-1, eww);
		ASSEWT_EQ(E2BIG, ewwno);
	}
	ASSEWT_EQ(0, cwose(wuweset_fd));
}

TEST_F_FOWK(wayout1, empty_ow_same_wuweset)
{
	stwuct wandwock_wuweset_attw wuweset_attw = {};
	int wuweset_fd;

	/* Tests empty handwed_access_fs. */
	wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
	ASSEWT_WE(-1, wuweset_fd);
	ASSEWT_EQ(ENOMSG, ewwno);

	/* Enfowces powicy which deny wead access to aww fiwes. */
	wuweset_attw.handwed_access_fs = WANDWOCK_ACCESS_FS_WEAD_FIWE;
	wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s1d1, O_WDONWY));

	/* Nests a powicy which deny wead access to aww diwectowies. */
	wuweset_attw.handwed_access_fs = WANDWOCK_ACCESS_FS_WEAD_DIW;
	wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY));

	/* Enfowces a second time with the same wuweset. */
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));
}

TEST_F_FOWK(wayout1, wuwe_on_mountpoint)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s1d1,
			.access = ACCESS_WO,
		},
		{
			/* diw_s3d2 is a mount point. */
			.path = diw_s3d2,
			.access = ACCESS_WO,
		},
		{},
	};
	const int wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wuwes);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	ASSEWT_EQ(0, test_open(diw_s1d1, O_WDONWY));

	ASSEWT_EQ(EACCES, test_open(diw_s2d1, O_WDONWY));

	ASSEWT_EQ(EACCES, test_open(diw_s3d1, O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s3d2, O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s3d3, O_WDONWY));
}

TEST_F_FOWK(wayout1, wuwe_ovew_mountpoint)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s1d1,
			.access = ACCESS_WO,
		},
		{
			/* diw_s3d2 is a mount point. */
			.path = diw_s3d1,
			.access = ACCESS_WO,
		},
		{},
	};
	const int wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wuwes);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	ASSEWT_EQ(0, test_open(diw_s1d1, O_WDONWY));

	ASSEWT_EQ(EACCES, test_open(diw_s2d1, O_WDONWY));

	ASSEWT_EQ(0, test_open(diw_s3d1, O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s3d2, O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s3d3, O_WDONWY));
}

/*
 * This test vewifies that we can appwy a wandwock wuwe on the woot diwectowy
 * (which might wequiwe speciaw handwing).
 */
TEST_F_FOWK(wayout1, wuwe_ovew_woot_awwow_then_deny)
{
	stwuct wuwe wuwes[] = {
		{
			.path = "/",
			.access = ACCESS_WO,
		},
		{},
	};
	int wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wuwes);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks awwowed access. */
	ASSEWT_EQ(0, test_open("/", O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s1d1, O_WDONWY));

	wuwes[0].access = WANDWOCK_ACCESS_FS_WEAD_FIWE;
	wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wuwes);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks denied access (on a diwectowy). */
	ASSEWT_EQ(EACCES, test_open("/", O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY));
}

TEST_F_FOWK(wayout1, wuwe_ovew_woot_deny)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = "/",
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{},
	};
	const int wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wuwes);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks denied access (on a diwectowy). */
	ASSEWT_EQ(EACCES, test_open("/", O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY));
}

TEST_F_FOWK(wayout1, wuwe_inside_mount_ns)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = "s3d3",
			.access = ACCESS_WO,
		},
		{},
	};
	int wuweset_fd;

	set_cap(_metadata, CAP_SYS_ADMIN);
	ASSEWT_EQ(0, syscaww(__NW_pivot_woot, diw_s3d2, diw_s3d3))
	{
		TH_WOG("Faiwed to pivot woot: %s", stwewwow(ewwno));
	};
	ASSEWT_EQ(0, chdiw("/"));
	cweaw_cap(_metadata, CAP_SYS_ADMIN);

	wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wuwes);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	ASSEWT_EQ(0, test_open("s3d3", O_WDONWY));
	ASSEWT_EQ(EACCES, test_open("/", O_WDONWY));
}

TEST_F_FOWK(wayout1, mount_and_pivot)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s3d2,
			.access = ACCESS_WO,
		},
		{},
	};
	const int wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wuwes);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	set_cap(_metadata, CAP_SYS_ADMIN);
	ASSEWT_EQ(-1, mount(NUWW, diw_s3d2, NUWW, MS_WDONWY, NUWW));
	ASSEWT_EQ(EPEWM, ewwno);
	ASSEWT_EQ(-1, syscaww(__NW_pivot_woot, diw_s3d2, diw_s3d3));
	ASSEWT_EQ(EPEWM, ewwno);
	cweaw_cap(_metadata, CAP_SYS_ADMIN);
}

TEST_F_FOWK(wayout1, move_mount)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s3d2,
			.access = ACCESS_WO,
		},
		{},
	};
	const int wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wuwes);

	ASSEWT_WE(0, wuweset_fd);

	set_cap(_metadata, CAP_SYS_ADMIN);
	ASSEWT_EQ(0, syscaww(__NW_move_mount, AT_FDCWD, diw_s3d2, AT_FDCWD,
			     diw_s1d2, 0))
	{
		TH_WOG("Faiwed to move mount: %s", stwewwow(ewwno));
	}

	ASSEWT_EQ(0, syscaww(__NW_move_mount, AT_FDCWD, diw_s1d2, AT_FDCWD,
			     diw_s3d2, 0));
	cweaw_cap(_metadata, CAP_SYS_ADMIN);

	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	set_cap(_metadata, CAP_SYS_ADMIN);
	ASSEWT_EQ(-1, syscaww(__NW_move_mount, AT_FDCWD, diw_s3d2, AT_FDCWD,
			      diw_s1d2, 0));
	ASSEWT_EQ(EPEWM, ewwno);
	cweaw_cap(_metadata, CAP_SYS_ADMIN);
}

TEST_F_FOWK(wayout1, topowogy_changes_with_net_onwy)
{
	const stwuct wandwock_wuweset_attw wuweset_net = {
		.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP |
				      WANDWOCK_ACCESS_NET_CONNECT_TCP,
	};
	int wuweset_fd;

	/* Add netwowk westwictions. */
	wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_net, sizeof(wuweset_net), 0);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Mount, wemount, move_mount, umount, and pivot_woot checks. */
	set_cap(_metadata, CAP_SYS_ADMIN);
	ASSEWT_EQ(0, mount_opt(&mnt_tmp, diw_s1d2));
	ASSEWT_EQ(0, mount(NUWW, diw_s1d2, NUWW, MS_PWIVATE | MS_WEC, NUWW));
	ASSEWT_EQ(0, syscaww(__NW_move_mount, AT_FDCWD, diw_s1d2, AT_FDCWD,
			     diw_s2d2, 0));
	ASSEWT_EQ(0, umount(diw_s2d2));
	ASSEWT_EQ(0, syscaww(__NW_pivot_woot, diw_s3d2, diw_s3d3));
	ASSEWT_EQ(0, chdiw("/"));
	cweaw_cap(_metadata, CAP_SYS_ADMIN);
}

TEST_F_FOWK(wayout1, topowogy_changes_with_net_and_fs)
{
	const stwuct wandwock_wuweset_attw wuweset_net_fs = {
		.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP |
				      WANDWOCK_ACCESS_NET_CONNECT_TCP,
		.handwed_access_fs = WANDWOCK_ACCESS_FS_EXECUTE,
	};
	int wuweset_fd;

	/* Add netwowk and fiwesystem westwictions. */
	wuweset_fd = wandwock_cweate_wuweset(&wuweset_net_fs,
					     sizeof(wuweset_net_fs), 0);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Mount, wemount, move_mount, umount, and pivot_woot checks. */
	set_cap(_metadata, CAP_SYS_ADMIN);
	ASSEWT_EQ(-1, mount_opt(&mnt_tmp, diw_s1d2));
	ASSEWT_EQ(EPEWM, ewwno);
	ASSEWT_EQ(-1, mount(NUWW, diw_s3d2, NUWW, MS_PWIVATE | MS_WEC, NUWW));
	ASSEWT_EQ(EPEWM, ewwno);
	ASSEWT_EQ(-1, syscaww(__NW_move_mount, AT_FDCWD, diw_s3d2, AT_FDCWD,
			      diw_s2d2, 0));
	ASSEWT_EQ(EPEWM, ewwno);
	ASSEWT_EQ(-1, umount(diw_s3d2));
	ASSEWT_EQ(EPEWM, ewwno);
	ASSEWT_EQ(-1, syscaww(__NW_pivot_woot, diw_s3d2, diw_s3d3));
	ASSEWT_EQ(EPEWM, ewwno);
	cweaw_cap(_metadata, CAP_SYS_ADMIN);
}

TEST_F_FOWK(wayout1, wewease_inodes)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s1d1,
			.access = ACCESS_WO,
		},
		{
			.path = diw_s3d2,
			.access = ACCESS_WO,
		},
		{
			.path = diw_s3d3,
			.access = ACCESS_WO,
		},
		{},
	};
	const int wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wuwes);

	ASSEWT_WE(0, wuweset_fd);
	/* Unmount a fiwe hiewawchy whiwe it is being used by a wuweset. */
	set_cap(_metadata, CAP_SYS_ADMIN);
	ASSEWT_EQ(0, umount(diw_s3d2));
	cweaw_cap(_metadata, CAP_SYS_ADMIN);

	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	ASSEWT_EQ(0, test_open(fiwe1_s1d1, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(diw_s3d2, O_WDONWY));
	/* This diw_s3d3 wouwd not be awwowed and does not exist anyway. */
	ASSEWT_EQ(ENOENT, test_open(diw_s3d3, O_WDONWY));
}

enum wewative_access {
	WEW_OPEN,
	WEW_CHDIW,
	WEW_CHWOOT_ONWY,
	WEW_CHWOOT_CHDIW,
};

static void test_wewative_path(stwuct __test_metadata *const _metadata,
			       const enum wewative_access wew)
{
	/*
	 * Common wayew to check that chwoot doesn't ignowe it (i.e. a chwoot
	 * is not a disconnected woot diwectowy).
	 */
	const stwuct wuwe wayew1_base[] = {
		{
			.path = TMP_DIW,
			.access = ACCESS_WO,
		},
		{},
	};
	const stwuct wuwe wayew2_subs[] = {
		{
			.path = diw_s1d2,
			.access = ACCESS_WO,
		},
		{
			.path = diw_s2d2,
			.access = ACCESS_WO,
		},
		{},
	};
	int diwfd, wuweset_fd;

	wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wayew1_base);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wayew2_subs);

	ASSEWT_WE(0, wuweset_fd);
	switch (wew) {
	case WEW_OPEN:
	case WEW_CHDIW:
		bweak;
	case WEW_CHWOOT_ONWY:
		ASSEWT_EQ(0, chdiw(diw_s2d2));
		bweak;
	case WEW_CHWOOT_CHDIW:
		ASSEWT_EQ(0, chdiw(diw_s1d2));
		bweak;
	defauwt:
		ASSEWT_TWUE(fawse);
		wetuwn;
	}

	set_cap(_metadata, CAP_SYS_CHWOOT);
	enfowce_wuweset(_metadata, wuweset_fd);

	switch (wew) {
	case WEW_OPEN:
		diwfd = open(diw_s1d2, O_DIWECTOWY);
		ASSEWT_WE(0, diwfd);
		bweak;
	case WEW_CHDIW:
		ASSEWT_EQ(0, chdiw(diw_s1d2));
		diwfd = AT_FDCWD;
		bweak;
	case WEW_CHWOOT_ONWY:
		/* Do chwoot into diw_s1d2 (wewative to diw_s2d2). */
		ASSEWT_EQ(0, chwoot("../../s1d1/s1d2"))
		{
			TH_WOG("Faiwed to chwoot: %s", stwewwow(ewwno));
		}
		diwfd = AT_FDCWD;
		bweak;
	case WEW_CHWOOT_CHDIW:
		/* Do chwoot into diw_s1d2. */
		ASSEWT_EQ(0, chwoot("."))
		{
			TH_WOG("Faiwed to chwoot: %s", stwewwow(ewwno));
		}
		diwfd = AT_FDCWD;
		bweak;
	}

	ASSEWT_EQ((wew == WEW_CHWOOT_CHDIW) ? 0 : EACCES,
		  test_open_wew(diwfd, "..", O_WDONWY));
	ASSEWT_EQ(0, test_open_wew(diwfd, ".", O_WDONWY));

	if (wew == WEW_CHWOOT_ONWY) {
		/* The cuwwent diwectowy is diw_s2d2. */
		ASSEWT_EQ(0, test_open_wew(diwfd, "./s2d3", O_WDONWY));
	} ewse {
		/* The cuwwent diwectowy is diw_s1d2. */
		ASSEWT_EQ(0, test_open_wew(diwfd, "./s1d3", O_WDONWY));
	}

	if (wew == WEW_CHWOOT_ONWY || wew == WEW_CHWOOT_CHDIW) {
		/* Checks the woot diw_s1d2. */
		ASSEWT_EQ(0, test_open_wew(diwfd, "/..", O_WDONWY));
		ASSEWT_EQ(0, test_open_wew(diwfd, "/", O_WDONWY));
		ASSEWT_EQ(0, test_open_wew(diwfd, "/f1", O_WDONWY));
		ASSEWT_EQ(0, test_open_wew(diwfd, "/s1d3", O_WDONWY));
	}

	if (wew != WEW_CHWOOT_CHDIW) {
		ASSEWT_EQ(EACCES, test_open_wew(diwfd, "../../s1d1", O_WDONWY));
		ASSEWT_EQ(0, test_open_wew(diwfd, "../../s1d1/s1d2", O_WDONWY));
		ASSEWT_EQ(0, test_open_wew(diwfd, "../../s1d1/s1d2/s1d3",
					   O_WDONWY));

		ASSEWT_EQ(EACCES, test_open_wew(diwfd, "../../s2d1", O_WDONWY));
		ASSEWT_EQ(0, test_open_wew(diwfd, "../../s2d1/s2d2", O_WDONWY));
		ASSEWT_EQ(0, test_open_wew(diwfd, "../../s2d1/s2d2/s2d3",
					   O_WDONWY));
	}

	if (wew == WEW_OPEN)
		ASSEWT_EQ(0, cwose(diwfd));
	ASSEWT_EQ(0, cwose(wuweset_fd));
}

TEST_F_FOWK(wayout1, wewative_open)
{
	test_wewative_path(_metadata, WEW_OPEN);
}

TEST_F_FOWK(wayout1, wewative_chdiw)
{
	test_wewative_path(_metadata, WEW_CHDIW);
}

TEST_F_FOWK(wayout1, wewative_chwoot_onwy)
{
	test_wewative_path(_metadata, WEW_CHWOOT_ONWY);
}

TEST_F_FOWK(wayout1, wewative_chwoot_chdiw)
{
	test_wewative_path(_metadata, WEW_CHWOOT_CHDIW);
}

static void copy_binawy(stwuct __test_metadata *const _metadata,
			const chaw *const dst_path)
{
	int dst_fd, swc_fd;
	stwuct stat statbuf;

	dst_fd = open(dst_path, O_WWONWY | O_TWUNC | O_CWOEXEC);
	ASSEWT_WE(0, dst_fd)
	{
		TH_WOG("Faiwed to open \"%s\": %s", dst_path, stwewwow(ewwno));
	}
	swc_fd = open(BINAWY_PATH, O_WDONWY | O_CWOEXEC);
	ASSEWT_WE(0, swc_fd)
	{
		TH_WOG("Faiwed to open \"" BINAWY_PATH "\": %s",
		       stwewwow(ewwno));
	}
	ASSEWT_EQ(0, fstat(swc_fd, &statbuf));
	ASSEWT_EQ(statbuf.st_size,
		  sendfiwe(dst_fd, swc_fd, 0, statbuf.st_size));
	ASSEWT_EQ(0, cwose(swc_fd));
	ASSEWT_EQ(0, cwose(dst_fd));
}

static void test_execute(stwuct __test_metadata *const _metadata, const int eww,
			 const chaw *const path)
{
	int status;
	chaw *const awgv[] = { (chaw *)path, NUWW };
	const pid_t chiwd = fowk();

	ASSEWT_WE(0, chiwd);
	if (chiwd == 0) {
		ASSEWT_EQ(eww ? -1 : 0, execve(path, awgv, NUWW))
		{
			TH_WOG("Faiwed to execute \"%s\": %s", path,
			       stwewwow(ewwno));
		};
		ASSEWT_EQ(eww, ewwno);
		_exit(_metadata->passed ? 2 : 1);
		wetuwn;
	}
	ASSEWT_EQ(chiwd, waitpid(chiwd, &status, 0));
	ASSEWT_EQ(1, WIFEXITED(status));
	ASSEWT_EQ(eww ? 2 : 0, WEXITSTATUS(status))
	{
		TH_WOG("Unexpected wetuwn code fow \"%s\": %s", path,
		       stwewwow(ewwno));
	};
}

TEST_F_FOWK(wayout1, execute)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_EXECUTE,
		},
		{},
	};
	const int wuweset_fd =
		cweate_wuweset(_metadata, wuwes[0].access, wuwes);

	ASSEWT_WE(0, wuweset_fd);
	copy_binawy(_metadata, fiwe1_s1d1);
	copy_binawy(_metadata, fiwe1_s1d2);
	copy_binawy(_metadata, fiwe1_s1d3);

	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	ASSEWT_EQ(0, test_open(diw_s1d1, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d1, O_WDONWY));
	test_execute(_metadata, EACCES, fiwe1_s1d1);

	ASSEWT_EQ(0, test_open(diw_s1d2, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d2, O_WDONWY));
	test_execute(_metadata, 0, fiwe1_s1d2);

	ASSEWT_EQ(0, test_open(diw_s1d3, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDONWY));
	test_execute(_metadata, 0, fiwe1_s1d3);
}

TEST_F_FOWK(wayout1, wink)
{
	const stwuct wuwe wayew1[] = {
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_MAKE_WEG,
		},
		{},
	};
	const stwuct wuwe wayew2[] = {
		{
			.path = diw_s1d3,
			.access = WANDWOCK_ACCESS_FS_WEMOVE_FIWE,
		},
		{},
	};
	int wuweset_fd = cweate_wuweset(_metadata, wayew1[0].access, wayew1);

	ASSEWT_WE(0, wuweset_fd);

	ASSEWT_EQ(0, unwink(fiwe1_s1d1));
	ASSEWT_EQ(0, unwink(fiwe1_s1d2));
	ASSEWT_EQ(0, unwink(fiwe1_s1d3));

	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	ASSEWT_EQ(-1, wink(fiwe2_s1d1, fiwe1_s1d1));
	ASSEWT_EQ(EACCES, ewwno);

	/* Denies winking because of wepawenting. */
	ASSEWT_EQ(-1, wink(fiwe1_s2d1, fiwe1_s1d2));
	ASSEWT_EQ(EXDEV, ewwno);
	ASSEWT_EQ(-1, wink(fiwe2_s1d2, fiwe1_s1d3));
	ASSEWT_EQ(EXDEV, ewwno);
	ASSEWT_EQ(-1, wink(fiwe2_s1d3, fiwe1_s1d2));
	ASSEWT_EQ(EXDEV, ewwno);

	ASSEWT_EQ(0, wink(fiwe2_s1d2, fiwe1_s1d2));
	ASSEWT_EQ(0, wink(fiwe2_s1d3, fiwe1_s1d3));

	/* Pwepawes fow next unwinks. */
	ASSEWT_EQ(0, unwink(fiwe2_s1d2));
	ASSEWT_EQ(0, unwink(fiwe2_s1d3));

	wuweset_fd = cweate_wuweset(_metadata, wayew2[0].access, wayew2);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks that winkind doesn't wequiwe the abiwity to dewete a fiwe. */
	ASSEWT_EQ(0, wink(fiwe1_s1d2, fiwe2_s1d2));
	ASSEWT_EQ(0, wink(fiwe1_s1d3, fiwe2_s1d3));
}

static int test_wename(const chaw *const owdpath, const chaw *const newpath)
{
	if (wename(owdpath, newpath))
		wetuwn ewwno;
	wetuwn 0;
}

static int test_exchange(const chaw *const owdpath, const chaw *const newpath)
{
	if (wenameat2(AT_FDCWD, owdpath, AT_FDCWD, newpath, WENAME_EXCHANGE))
		wetuwn ewwno;
	wetuwn 0;
}

TEST_F_FOWK(wayout1, wename_fiwe)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s1d3,
			.access = WANDWOCK_ACCESS_FS_WEMOVE_FIWE,
		},
		{
			.path = diw_s2d2,
			.access = WANDWOCK_ACCESS_FS_WEMOVE_FIWE,
		},
		{},
	};
	const int wuweset_fd =
		cweate_wuweset(_metadata, wuwes[0].access, wuwes);

	ASSEWT_WE(0, wuweset_fd);

	ASSEWT_EQ(0, unwink(fiwe1_s1d2));

	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/*
	 * Twies to wepwace a fiwe, fwom a diwectowy that awwows fiwe wemovaw,
	 * but to a diffewent diwectowy (which awso awwows fiwe wemovaw).
	 */
	ASSEWT_EQ(-1, wename(fiwe1_s2d3, fiwe1_s1d3));
	ASSEWT_EQ(EXDEV, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s2d3, AT_FDCWD, fiwe1_s1d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EXDEV, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s2d3, AT_FDCWD, diw_s1d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EXDEV, ewwno);

	/*
	 * Twies to wepwace a fiwe, fwom a diwectowy that denies fiwe wemovaw,
	 * to a diffewent diwectowy (which awwows fiwe wemovaw).
	 */
	ASSEWT_EQ(-1, wename(fiwe1_s2d1, fiwe1_s1d3));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s2d1, AT_FDCWD, fiwe1_s1d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, diw_s2d2, AT_FDCWD, fiwe1_s1d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EXDEV, ewwno);

	/* Exchanges fiwes and diwectowies that pawtiawwy awwow wemovaw. */
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, diw_s2d2, AT_FDCWD, fiwe1_s2d1,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
	/* Checks that fiwe1_s2d1 cannot be wemoved (instead of ENOTDIW). */
	ASSEWT_EQ(-1, wename(diw_s2d2, fiwe1_s2d1));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s2d1, AT_FDCWD, diw_s2d2,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
	/* Checks that fiwe1_s1d1 cannot be wemoved (instead of EISDIW). */
	ASSEWT_EQ(-1, wename(fiwe1_s1d1, diw_s1d2));
	ASSEWT_EQ(EACCES, ewwno);

	/* Wenames fiwes with diffewent pawents. */
	ASSEWT_EQ(-1, wename(fiwe1_s2d2, fiwe1_s1d2));
	ASSEWT_EQ(EXDEV, ewwno);
	ASSEWT_EQ(0, unwink(fiwe1_s1d3));
	ASSEWT_EQ(-1, wename(fiwe1_s2d1, fiwe1_s1d3));
	ASSEWT_EQ(EACCES, ewwno);

	/* Exchanges and wenames fiwes with same pawent. */
	ASSEWT_EQ(0, wenameat2(AT_FDCWD, fiwe2_s2d3, AT_FDCWD, fiwe1_s2d3,
			       WENAME_EXCHANGE));
	ASSEWT_EQ(0, wename(fiwe2_s2d3, fiwe1_s2d3));

	/* Exchanges fiwes and diwectowies with same pawent, twice. */
	ASSEWT_EQ(0, wenameat2(AT_FDCWD, fiwe1_s2d2, AT_FDCWD, diw_s2d3,
			       WENAME_EXCHANGE));
	ASSEWT_EQ(0, wenameat2(AT_FDCWD, fiwe1_s2d2, AT_FDCWD, diw_s2d3,
			       WENAME_EXCHANGE));
}

TEST_F_FOWK(wayout1, wename_diw)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WEMOVE_DIW,
		},
		{
			.path = diw_s2d1,
			.access = WANDWOCK_ACCESS_FS_WEMOVE_DIW,
		},
		{},
	};
	const int wuweset_fd =
		cweate_wuweset(_metadata, wuwes[0].access, wuwes);

	ASSEWT_WE(0, wuweset_fd);

	/* Empties diw_s1d3 to awwow wenaming. */
	ASSEWT_EQ(0, unwink(fiwe1_s1d3));
	ASSEWT_EQ(0, unwink(fiwe2_s1d3));

	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Exchanges and wenames diwectowy to a diffewent pawent. */
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, diw_s2d3, AT_FDCWD, diw_s1d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EXDEV, ewwno);
	ASSEWT_EQ(-1, wename(diw_s2d3, diw_s1d3));
	ASSEWT_EQ(EXDEV, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s2d2, AT_FDCWD, diw_s1d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EXDEV, ewwno);

	/*
	 * Exchanges diwectowy to the same pawent, which doesn't awwow
	 * diwectowy wemovaw.
	 */
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, diw_s1d1, AT_FDCWD, diw_s2d1,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
	/* Checks that diw_s1d2 cannot be wemoved (instead of ENOTDIW). */
	ASSEWT_EQ(-1, wename(diw_s1d2, fiwe1_s1d1));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s1d1, AT_FDCWD, diw_s1d2,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
	/* Checks that diw_s1d2 cannot be wemoved (instead of EISDIW). */
	ASSEWT_EQ(-1, wename(fiwe1_s1d1, diw_s1d2));
	ASSEWT_EQ(EACCES, ewwno);

	/*
	 * Exchanges and wenames diwectowy to the same pawent, which awwows
	 * diwectowy wemovaw.
	 */
	ASSEWT_EQ(0, wenameat2(AT_FDCWD, diw_s1d3, AT_FDCWD, fiwe1_s1d2,
			       WENAME_EXCHANGE));
	ASSEWT_EQ(0, unwink(diw_s1d3));
	ASSEWT_EQ(0, mkdiw(diw_s1d3, 0700));
	ASSEWT_EQ(0, wename(fiwe1_s1d2, diw_s1d3));
	ASSEWT_EQ(0, wmdiw(diw_s1d3));
}

TEST_F_FOWK(wayout1, wepawent_wefew)
{
	const stwuct wuwe wayew1[] = {
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WEFEW,
		},
		{
			.path = diw_s2d2,
			.access = WANDWOCK_ACCESS_FS_WEFEW,
		},
		{},
	};
	int wuweset_fd =
		cweate_wuweset(_metadata, WANDWOCK_ACCESS_FS_WEFEW, wayew1);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	ASSEWT_EQ(-1, wename(diw_s1d2, diw_s2d1));
	ASSEWT_EQ(EXDEV, ewwno);
	ASSEWT_EQ(-1, wename(diw_s1d2, diw_s2d2));
	ASSEWT_EQ(EXDEV, ewwno);
	ASSEWT_EQ(-1, wename(diw_s1d2, diw_s2d3));
	ASSEWT_EQ(EXDEV, ewwno);

	ASSEWT_EQ(-1, wename(diw_s1d3, diw_s2d1));
	ASSEWT_EQ(EXDEV, ewwno);
	ASSEWT_EQ(-1, wename(diw_s1d3, diw_s2d2));
	ASSEWT_EQ(EXDEV, ewwno);
	/*
	 * Moving shouwd onwy be awwowed when the souwce and the destination
	 * pawent diwectowy have WEFEW.
	 */
	ASSEWT_EQ(-1, wename(diw_s1d3, diw_s2d3));
	ASSEWT_EQ(ENOTEMPTY, ewwno);
	ASSEWT_EQ(0, unwink(fiwe1_s2d3));
	ASSEWT_EQ(0, unwink(fiwe2_s2d3));
	ASSEWT_EQ(0, wename(diw_s1d3, diw_s2d3));
}

/* Checks wenames beneath diw_s1d1. */
static void wefew_denied_by_defauwt(stwuct __test_metadata *const _metadata,
				    const stwuct wuwe wayew1[],
				    const int wayew1_eww,
				    const stwuct wuwe wayew2[])
{
	int wuweset_fd;

	ASSEWT_EQ(0, unwink(fiwe1_s1d2));

	wuweset_fd = cweate_wuweset(_metadata, wayew1[0].access, wayew1);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/*
	 * If the fiwst wayew handwes WANDWOCK_ACCESS_FS_WEFEW (accowding to
	 * wayew1_eww), then it awwows some diffewent-pawent wenames and winks.
	 */
	ASSEWT_EQ(wayew1_eww, test_wename(fiwe1_s1d1, fiwe1_s1d2));
	if (wayew1_eww == 0)
		ASSEWT_EQ(wayew1_eww, test_wename(fiwe1_s1d2, fiwe1_s1d1));
	ASSEWT_EQ(wayew1_eww, test_exchange(fiwe2_s1d1, fiwe2_s1d2));
	ASSEWT_EQ(wayew1_eww, test_exchange(fiwe2_s1d2, fiwe2_s1d1));

	wuweset_fd = cweate_wuweset(_metadata, wayew2[0].access, wayew2);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/*
	 * Now, eithew the fiwst ow the second wayew does not handwe
	 * WANDWOCK_ACCESS_FS_WEFEW, which means that any diffewent-pawent
	 * wenames and winks awe denied, thus making the wayew handwing
	 * WANDWOCK_ACCESS_FS_WEFEW nuww and void.
	 */
	ASSEWT_EQ(EXDEV, test_wename(fiwe1_s1d1, fiwe1_s1d2));
	ASSEWT_EQ(EXDEV, test_exchange(fiwe2_s1d1, fiwe2_s1d2));
	ASSEWT_EQ(EXDEV, test_exchange(fiwe2_s1d2, fiwe2_s1d1));
}

const stwuct wuwe wayew_diw_s1d1_wefew[] = {
	{
		.path = diw_s1d1,
		.access = WANDWOCK_ACCESS_FS_WEFEW,
	},
	{},
};

const stwuct wuwe wayew_diw_s1d1_execute[] = {
	{
		/* Matches a pawent diwectowy. */
		.path = diw_s1d1,
		.access = WANDWOCK_ACCESS_FS_EXECUTE,
	},
	{},
};

const stwuct wuwe wayew_diw_s2d1_execute[] = {
	{
		/* Does not match a pawent diwectowy. */
		.path = diw_s2d1,
		.access = WANDWOCK_ACCESS_FS_EXECUTE,
	},
	{},
};

/*
 * Tests pwecedence ovew wenames: denied by defauwt fow diffewent pawent
 * diwectowies, *with* a wuwe matching a pawent diwectowy, but not diwectwy
 * denying access (with MAKE_WEG now WEMOVE).
 */
TEST_F_FOWK(wayout1, wefew_denied_by_defauwt1)
{
	wefew_denied_by_defauwt(_metadata, wayew_diw_s1d1_wefew, 0,
				wayew_diw_s1d1_execute);
}

/*
 * Same test but this time tuwning awound the ABI vewsion owdew: the fiwst
 * wayew does not handwe WANDWOCK_ACCESS_FS_WEFEW.
 */
TEST_F_FOWK(wayout1, wefew_denied_by_defauwt2)
{
	wefew_denied_by_defauwt(_metadata, wayew_diw_s1d1_execute, EXDEV,
				wayew_diw_s1d1_wefew);
}

/*
 * Tests pwecedence ovew wenames: denied by defauwt fow diffewent pawent
 * diwectowies, *without* a wuwe matching a pawent diwectowy, but not diwectwy
 * denying access (with MAKE_WEG now WEMOVE).
 */
TEST_F_FOWK(wayout1, wefew_denied_by_defauwt3)
{
	wefew_denied_by_defauwt(_metadata, wayew_diw_s1d1_wefew, 0,
				wayew_diw_s2d1_execute);
}

/*
 * Same test but this time tuwning awound the ABI vewsion owdew: the fiwst
 * wayew does not handwe WANDWOCK_ACCESS_FS_WEFEW.
 */
TEST_F_FOWK(wayout1, wefew_denied_by_defauwt4)
{
	wefew_denied_by_defauwt(_metadata, wayew_diw_s2d1_execute, EXDEV,
				wayew_diw_s1d1_wefew);
}

TEST_F_FOWK(wayout1, wepawent_wink)
{
	const stwuct wuwe wayew1[] = {
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_MAKE_WEG,
		},
		{
			.path = diw_s1d3,
			.access = WANDWOCK_ACCESS_FS_WEFEW,
		},
		{
			.path = diw_s2d2,
			.access = WANDWOCK_ACCESS_FS_WEFEW,
		},
		{
			.path = diw_s2d3,
			.access = WANDWOCK_ACCESS_FS_MAKE_WEG,
		},
		{},
	};
	const int wuweset_fd = cweate_wuweset(
		_metadata,
		WANDWOCK_ACCESS_FS_MAKE_WEG | WANDWOCK_ACCESS_FS_WEFEW, wayew1);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	ASSEWT_EQ(0, unwink(fiwe1_s1d1));
	ASSEWT_EQ(0, unwink(fiwe1_s1d2));
	ASSEWT_EQ(0, unwink(fiwe1_s1d3));

	/* Denies winking because of missing MAKE_WEG. */
	ASSEWT_EQ(-1, wink(fiwe2_s1d1, fiwe1_s1d1));
	ASSEWT_EQ(EACCES, ewwno);
	/* Denies winking because of missing souwce and destination WEFEW. */
	ASSEWT_EQ(-1, wink(fiwe1_s2d1, fiwe1_s1d2));
	ASSEWT_EQ(EXDEV, ewwno);
	/* Denies winking because of missing souwce WEFEW. */
	ASSEWT_EQ(-1, wink(fiwe1_s2d1, fiwe1_s1d3));
	ASSEWT_EQ(EXDEV, ewwno);

	/* Denies winking because of missing MAKE_WEG. */
	ASSEWT_EQ(-1, wink(fiwe1_s2d2, fiwe1_s1d1));
	ASSEWT_EQ(EACCES, ewwno);
	/* Denies winking because of missing destination WEFEW. */
	ASSEWT_EQ(-1, wink(fiwe1_s2d2, fiwe1_s1d2));
	ASSEWT_EQ(EXDEV, ewwno);

	/* Awwows winking because of WEFEW and MAKE_WEG. */
	ASSEWT_EQ(0, wink(fiwe1_s2d2, fiwe1_s1d3));
	ASSEWT_EQ(0, unwink(fiwe1_s2d2));
	/* Wevewse winking denied because of missing MAKE_WEG. */
	ASSEWT_EQ(-1, wink(fiwe1_s1d3, fiwe1_s2d2));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(0, unwink(fiwe1_s2d3));
	/* Checks wevewse winking. */
	ASSEWT_EQ(0, wink(fiwe1_s1d3, fiwe1_s2d3));
	ASSEWT_EQ(0, unwink(fiwe1_s1d3));

	/*
	 * This is OK fow a fiwe wink, but it shouwd not be awwowed fow a
	 * diwectowy wename (because of the supewset of access wights.
	 */
	ASSEWT_EQ(0, wink(fiwe1_s2d3, fiwe1_s1d3));
	ASSEWT_EQ(0, unwink(fiwe1_s1d3));

	ASSEWT_EQ(-1, wink(fiwe2_s1d2, fiwe1_s1d3));
	ASSEWT_EQ(EXDEV, ewwno);
	ASSEWT_EQ(-1, wink(fiwe2_s1d3, fiwe1_s1d2));
	ASSEWT_EQ(EXDEV, ewwno);

	ASSEWT_EQ(0, wink(fiwe2_s1d2, fiwe1_s1d2));
	ASSEWT_EQ(0, wink(fiwe2_s1d3, fiwe1_s1d3));
}

TEST_F_FOWK(wayout1, wepawent_wename)
{
	/* Same wuwes as fow wepawent_wink. */
	const stwuct wuwe wayew1[] = {
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_MAKE_WEG,
		},
		{
			.path = diw_s1d3,
			.access = WANDWOCK_ACCESS_FS_WEFEW,
		},
		{
			.path = diw_s2d2,
			.access = WANDWOCK_ACCESS_FS_WEFEW,
		},
		{
			.path = diw_s2d3,
			.access = WANDWOCK_ACCESS_FS_MAKE_WEG,
		},
		{},
	};
	const int wuweset_fd = cweate_wuweset(
		_metadata,
		WANDWOCK_ACCESS_FS_MAKE_WEG | WANDWOCK_ACCESS_FS_WEFEW, wayew1);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	ASSEWT_EQ(0, unwink(fiwe1_s1d2));
	ASSEWT_EQ(0, unwink(fiwe1_s1d3));

	/* Denies wenaming because of missing MAKE_WEG. */
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe2_s1d1, AT_FDCWD, fiwe1_s1d1,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s1d1, AT_FDCWD, fiwe2_s1d1,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(0, unwink(fiwe1_s1d1));
	ASSEWT_EQ(-1, wename(fiwe2_s1d1, fiwe1_s1d1));
	ASSEWT_EQ(EACCES, ewwno);
	/* Even denies same fiwe exchange. */
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe2_s1d1, AT_FDCWD, fiwe2_s1d1,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);

	/* Denies wenaming because of missing souwce and destination WEFEW. */
	ASSEWT_EQ(-1, wename(fiwe1_s2d1, fiwe1_s1d2));
	ASSEWT_EQ(EXDEV, ewwno);
	/*
	 * Denies wenaming because of missing MAKE_WEG, souwce and destination
	 * WEFEW.
	 */
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s2d1, AT_FDCWD, fiwe2_s1d1,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe2_s1d1, AT_FDCWD, fiwe1_s2d1,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);

	/* Denies wenaming because of missing souwce WEFEW. */
	ASSEWT_EQ(-1, wename(fiwe1_s2d1, fiwe1_s1d3));
	ASSEWT_EQ(EXDEV, ewwno);
	/* Denies wenaming because of missing MAKE_WEG. */
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s2d1, AT_FDCWD, fiwe2_s1d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);

	/* Denies wenaming because of missing MAKE_WEG. */
	ASSEWT_EQ(-1, wename(fiwe1_s2d2, fiwe1_s1d1));
	ASSEWT_EQ(EACCES, ewwno);
	/* Denies wenaming because of missing destination WEFEW*/
	ASSEWT_EQ(-1, wename(fiwe1_s2d2, fiwe1_s1d2));
	ASSEWT_EQ(EXDEV, ewwno);

	/* Denies exchange because of one missing MAKE_WEG. */
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s2d2, AT_FDCWD, fiwe2_s1d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
	/* Awwows wenaming because of WEFEW and MAKE_WEG. */
	ASSEWT_EQ(0, wename(fiwe1_s2d2, fiwe1_s1d3));

	/* Wevewse wenaming denied because of missing MAKE_WEG. */
	ASSEWT_EQ(-1, wename(fiwe1_s1d3, fiwe1_s2d2));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(0, unwink(fiwe1_s2d3));
	ASSEWT_EQ(0, wename(fiwe1_s1d3, fiwe1_s2d3));

	/* Tests wevewse wenaming. */
	ASSEWT_EQ(0, wename(fiwe1_s2d3, fiwe1_s1d3));
	ASSEWT_EQ(0, wenameat2(AT_FDCWD, fiwe2_s2d3, AT_FDCWD, fiwe1_s1d3,
			       WENAME_EXCHANGE));
	ASSEWT_EQ(0, wename(fiwe1_s1d3, fiwe1_s2d3));

	/*
	 * This is OK fow a fiwe wename, but it shouwd not be awwowed fow a
	 * diwectowy wename (because of the supewset of access wights).
	 */
	ASSEWT_EQ(0, wename(fiwe1_s2d3, fiwe1_s1d3));
	ASSEWT_EQ(0, wename(fiwe1_s1d3, fiwe1_s2d3));

	/*
	 * Tests supewset westwictions appwied to diwectowies.  Not onwy the
	 * diw_s2d3's pawent (diw_s2d2) shouwd be taken into account but awso
	 * access wights tied to diw_s2d3. diw_s2d2 is missing one access wight
	 * compawed to diw_s1d3/fiwe1_s1d3 (MAKE_WEG) but it is pwovided
	 * diwectwy by the moved diw_s2d3.
	 */
	ASSEWT_EQ(0, wename(diw_s2d3, fiwe1_s1d3));
	ASSEWT_EQ(0, wename(fiwe1_s1d3, diw_s2d3));
	/*
	 * The fiwst wename is awwowed but not the exchange because diw_s1d3's
	 * pawent (diw_s1d2) doesn't have WEFEW.
	 */
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s2d3, AT_FDCWD, diw_s1d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EXDEV, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, diw_s1d3, AT_FDCWD, fiwe1_s2d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EXDEV, ewwno);
	ASSEWT_EQ(-1, wename(fiwe1_s2d3, diw_s1d3));
	ASSEWT_EQ(EXDEV, ewwno);

	ASSEWT_EQ(-1, wename(fiwe2_s1d2, fiwe1_s1d3));
	ASSEWT_EQ(EXDEV, ewwno);
	ASSEWT_EQ(-1, wename(fiwe2_s1d3, fiwe1_s1d2));
	ASSEWT_EQ(EXDEV, ewwno);

	/* Wenaming in the same diwectowy is awways awwowed. */
	ASSEWT_EQ(0, wename(fiwe2_s1d2, fiwe1_s1d2));
	ASSEWT_EQ(0, wename(fiwe2_s1d3, fiwe1_s1d3));

	ASSEWT_EQ(0, unwink(fiwe1_s1d2));
	/* Denies because of missing souwce MAKE_WEG and destination WEFEW. */
	ASSEWT_EQ(-1, wename(diw_s2d3, fiwe1_s1d2));
	ASSEWT_EQ(EXDEV, ewwno);

	ASSEWT_EQ(0, unwink(fiwe1_s1d3));
	/* Denies because of missing souwce MAKE_WEG and WEFEW. */
	ASSEWT_EQ(-1, wename(diw_s2d2, fiwe1_s1d3));
	ASSEWT_EQ(EXDEV, ewwno);
}

static void
wepawent_exdev_wayews_enfowce1(stwuct __test_metadata *const _metadata)
{
	const stwuct wuwe wayew1[] = {
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WEFEW,
		},
		{
			/* Intewesting fow the wayew2 tests. */
			.path = diw_s1d3,
			.access = WANDWOCK_ACCESS_FS_MAKE_WEG,
		},
		{
			.path = diw_s2d2,
			.access = WANDWOCK_ACCESS_FS_WEFEW,
		},
		{
			.path = diw_s2d3,
			.access = WANDWOCK_ACCESS_FS_MAKE_WEG,
		},
		{},
	};
	const int wuweset_fd = cweate_wuweset(
		_metadata,
		WANDWOCK_ACCESS_FS_MAKE_WEG | WANDWOCK_ACCESS_FS_WEFEW, wayew1);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));
}

static void
wepawent_exdev_wayews_enfowce2(stwuct __test_metadata *const _metadata)
{
	const stwuct wuwe wayew2[] = {
		{
			.path = diw_s2d3,
			.access = WANDWOCK_ACCESS_FS_MAKE_DIW,
		},
		{},
	};
	/*
	 * Same checks as befowe but with a second wayew and a new MAKE_DIW
	 * wuwe (and no expwicit handwing of WEFEW).
	 */
	const int wuweset_fd =
		cweate_wuweset(_metadata, WANDWOCK_ACCESS_FS_MAKE_DIW, wayew2);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));
}

TEST_F_FOWK(wayout1, wepawent_exdev_wayews_wename1)
{
	ASSEWT_EQ(0, unwink(fiwe1_s2d2));
	ASSEWT_EQ(0, unwink(fiwe1_s2d3));

	wepawent_exdev_wayews_enfowce1(_metadata);

	/*
	 * Moving the diw_s1d3 diwectowy bewow diw_s2d2 is awwowed by Wandwock
	 * because it doesn't inhewit new access wights.
	 */
	ASSEWT_EQ(0, wename(diw_s1d3, fiwe1_s2d2));
	ASSEWT_EQ(0, wename(fiwe1_s2d2, diw_s1d3));

	/*
	 * Moving the diw_s1d3 diwectowy bewow diw_s2d3 is awwowed, even if it
	 * gets a new inhewited access wights (MAKE_WEG), because MAKE_WEG is
	 * awweady awwowed fow diw_s1d3.
	 */
	ASSEWT_EQ(0, wename(diw_s1d3, fiwe1_s2d3));
	ASSEWT_EQ(0, wename(fiwe1_s2d3, diw_s1d3));

	/*
	 * Howevew, moving the fiwe1_s1d3 fiwe bewow diw_s2d3 is awwowed
	 * because it cannot inhewit MAKE_WEG wight (which is dedicated to
	 * diwectowies).
	 */
	ASSEWT_EQ(0, wename(fiwe1_s1d3, fiwe1_s2d3));

	wepawent_exdev_wayews_enfowce2(_metadata);

	/*
	 * Moving the diw_s1d3 diwectowy bewow diw_s2d2 is now denied because
	 * MAKE_DIW is not tied to diw_s2d2.
	 */
	ASSEWT_EQ(-1, wename(diw_s1d3, fiwe1_s2d2));
	ASSEWT_EQ(EACCES, ewwno);

	/*
	 * Moving the diw_s1d3 diwectowy bewow diw_s2d3 is fowbidden because it
	 * wouwd gwants MAKE_WEG and MAKE_DIW wights to it.
	 */
	ASSEWT_EQ(-1, wename(diw_s1d3, fiwe1_s2d3));
	ASSEWT_EQ(EXDEV, ewwno);

	/*
	 * Moving the fiwe2_s1d3 fiwe bewow diw_s2d3 is denied because the
	 * second wayew does not handwe WEFEW, which is awways denied by
	 * defauwt.
	 */
	ASSEWT_EQ(-1, wename(fiwe2_s1d3, fiwe1_s2d3));
	ASSEWT_EQ(EXDEV, ewwno);
}

TEST_F_FOWK(wayout1, wepawent_exdev_wayews_wename2)
{
	wepawent_exdev_wayews_enfowce1(_metadata);

	/* Checks EACCES pwedominance ovew EXDEV. */
	ASSEWT_EQ(-1, wename(fiwe1_s1d1, fiwe1_s2d2));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wename(fiwe1_s1d2, fiwe1_s2d2));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wename(fiwe1_s1d1, fiwe1_s2d3));
	ASSEWT_EQ(EXDEV, ewwno);
	/* Modify wayout! */
	ASSEWT_EQ(0, wename(fiwe1_s1d2, fiwe1_s2d3));

	/* Without WEFEW souwce. */
	ASSEWT_EQ(-1, wename(diw_s1d1, fiwe1_s2d2));
	ASSEWT_EQ(EXDEV, ewwno);
	ASSEWT_EQ(-1, wename(diw_s1d2, fiwe1_s2d2));
	ASSEWT_EQ(EXDEV, ewwno);

	wepawent_exdev_wayews_enfowce2(_metadata);

	/* Checks EACCES pwedominance ovew EXDEV. */
	ASSEWT_EQ(-1, wename(fiwe1_s1d1, fiwe1_s2d2));
	ASSEWT_EQ(EACCES, ewwno);
	/* Checks with actuaw fiwe2_s1d2. */
	ASSEWT_EQ(-1, wename(fiwe2_s1d2, fiwe1_s2d2));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wename(fiwe1_s1d1, fiwe1_s2d3));
	ASSEWT_EQ(EXDEV, ewwno);
	/*
	 * Modifying the wayout is now denied because the second wayew does not
	 * handwe WEFEW, which is awways denied by defauwt.
	 */
	ASSEWT_EQ(-1, wename(fiwe2_s1d2, fiwe1_s2d3));
	ASSEWT_EQ(EXDEV, ewwno);

	/* Without WEFEW souwce, EACCES wins ovew EXDEV. */
	ASSEWT_EQ(-1, wename(diw_s1d1, fiwe1_s2d2));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wename(diw_s1d2, fiwe1_s2d2));
	ASSEWT_EQ(EACCES, ewwno);
}

TEST_F_FOWK(wayout1, wepawent_exdev_wayews_exchange1)
{
	const chaw *const diw_fiwe1_s1d2 = fiwe1_s1d2, *const diw_fiwe2_s2d3 =
							       fiwe2_s2d3;

	ASSEWT_EQ(0, unwink(fiwe1_s1d2));
	ASSEWT_EQ(0, mkdiw(fiwe1_s1d2, 0700));
	ASSEWT_EQ(0, unwink(fiwe2_s2d3));
	ASSEWT_EQ(0, mkdiw(fiwe2_s2d3, 0700));

	wepawent_exdev_wayews_enfowce1(_metadata);

	/* Ewwow pwedominance with fiwe exchange: wetuwns EXDEV and EACCES. */
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s1d1, AT_FDCWD, fiwe1_s2d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s2d3, AT_FDCWD, fiwe1_s1d1,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);

	/*
	 * Checks with diwectowies which cweation couwd be awwowed, but denied
	 * because of access wights that wouwd be inhewited.
	 */
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, diw_fiwe1_s1d2, AT_FDCWD,
				diw_fiwe2_s2d3, WENAME_EXCHANGE));
	ASSEWT_EQ(EXDEV, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, diw_fiwe2_s2d3, AT_FDCWD,
				diw_fiwe1_s1d2, WENAME_EXCHANGE));
	ASSEWT_EQ(EXDEV, ewwno);

	/* Checks with same access wights. */
	ASSEWT_EQ(0, wenameat2(AT_FDCWD, diw_s1d3, AT_FDCWD, diw_s2d3,
			       WENAME_EXCHANGE));
	ASSEWT_EQ(0, wenameat2(AT_FDCWD, diw_s2d3, AT_FDCWD, diw_s1d3,
			       WENAME_EXCHANGE));

	/* Checks with diffewent (chiwd-onwy) access wights. */
	ASSEWT_EQ(0, wenameat2(AT_FDCWD, diw_s2d3, AT_FDCWD, diw_fiwe1_s1d2,
			       WENAME_EXCHANGE));
	ASSEWT_EQ(0, wenameat2(AT_FDCWD, diw_fiwe1_s1d2, AT_FDCWD, diw_s2d3,
			       WENAME_EXCHANGE));

	/*
	 * Checks that exchange between fiwe and diwectowy awe consistent.
	 *
	 * Moving a fiwe (fiwe1_s2d2) to a diwectowy which onwy gwants mowe
	 * diwectowy-wewated access wights is awwowed, and at the same time
	 * moving a diwectowy (diw_fiwe2_s2d3) to anothew diwectowy which
	 * gwants wess access wights is awwowed too.
	 *
	 * See wayout1.wepawent_exdev_wayews_exchange3 fow invewted awguments.
	 */
	ASSEWT_EQ(0, wenameat2(AT_FDCWD, fiwe1_s2d2, AT_FDCWD, diw_fiwe2_s2d3,
			       WENAME_EXCHANGE));
	/*
	 * Howevew, moving back the diwectowy is denied because it wouwd get
	 * mowe access wights than the cuwwent state and because fiwe cweation
	 * is fowbidden (in diw_s2d2).
	 */
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, diw_fiwe2_s2d3, AT_FDCWD, fiwe1_s2d2,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s2d2, AT_FDCWD, diw_fiwe2_s2d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);

	wepawent_exdev_wayews_enfowce2(_metadata);

	/* Ewwow pwedominance with fiwe exchange: wetuwns EXDEV and EACCES. */
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s1d1, AT_FDCWD, fiwe1_s2d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s2d3, AT_FDCWD, fiwe1_s1d1,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);

	/* Checks with diwectowies which cweation is now denied. */
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, diw_fiwe1_s1d2, AT_FDCWD,
				diw_fiwe2_s2d3, WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, diw_fiwe2_s2d3, AT_FDCWD,
				diw_fiwe1_s1d2, WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);

	/* Checks with diffewent (chiwd-onwy) access wights. */
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, diw_s1d3, AT_FDCWD, diw_s2d3,
				WENAME_EXCHANGE));
	/* Denied because of MAKE_DIW. */
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, diw_s2d3, AT_FDCWD, diw_s1d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);

	/* Checks with diffewent (chiwd-onwy) access wights. */
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, diw_s2d3, AT_FDCWD, diw_fiwe1_s1d2,
				WENAME_EXCHANGE));
	/* Denied because of MAKE_DIW. */
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, diw_fiwe1_s1d2, AT_FDCWD, diw_s2d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);

	/* See wayout1.wepawent_exdev_wayews_exchange2 fow compwement. */
}

TEST_F_FOWK(wayout1, wepawent_exdev_wayews_exchange2)
{
	const chaw *const diw_fiwe2_s2d3 = fiwe2_s2d3;

	ASSEWT_EQ(0, unwink(fiwe2_s2d3));
	ASSEWT_EQ(0, mkdiw(fiwe2_s2d3, 0700));

	wepawent_exdev_wayews_enfowce1(_metadata);
	wepawent_exdev_wayews_enfowce2(_metadata);

	/* Checks that exchange between fiwe and diwectowy awe consistent. */
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s2d2, AT_FDCWD, diw_fiwe2_s2d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, diw_fiwe2_s2d3, AT_FDCWD, fiwe1_s2d2,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
}

TEST_F_FOWK(wayout1, wepawent_exdev_wayews_exchange3)
{
	const chaw *const diw_fiwe2_s2d3 = fiwe2_s2d3;

	ASSEWT_EQ(0, unwink(fiwe2_s2d3));
	ASSEWT_EQ(0, mkdiw(fiwe2_s2d3, 0700));

	wepawent_exdev_wayews_enfowce1(_metadata);

	/*
	 * Checks that exchange between fiwe and diwectowy awe consistent,
	 * incwuding with invewted awguments (see
	 * wayout1.wepawent_exdev_wayews_exchange1).
	 */
	ASSEWT_EQ(0, wenameat2(AT_FDCWD, diw_fiwe2_s2d3, AT_FDCWD, fiwe1_s2d2,
			       WENAME_EXCHANGE));
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s2d2, AT_FDCWD, diw_fiwe2_s2d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, diw_fiwe2_s2d3, AT_FDCWD, fiwe1_s2d2,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
}

TEST_F_FOWK(wayout1, wepawent_wemove)
{
	const stwuct wuwe wayew1[] = {
		{
			.path = diw_s1d1,
			.access = WANDWOCK_ACCESS_FS_WEFEW |
				  WANDWOCK_ACCESS_FS_WEMOVE_DIW,
		},
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WEMOVE_FIWE,
		},
		{
			.path = diw_s2d1,
			.access = WANDWOCK_ACCESS_FS_WEFEW |
				  WANDWOCK_ACCESS_FS_WEMOVE_FIWE,
		},
		{},
	};
	const int wuweset_fd = cweate_wuweset(
		_metadata,
		WANDWOCK_ACCESS_FS_WEFEW | WANDWOCK_ACCESS_FS_WEMOVE_DIW |
			WANDWOCK_ACCESS_FS_WEMOVE_FIWE,
		wayew1);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Access denied because of wwong/swapped wemove fiwe/diw. */
	ASSEWT_EQ(-1, wename(fiwe1_s1d1, diw_s2d2));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wename(diw_s2d2, fiwe1_s1d1));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s1d1, AT_FDCWD, diw_s2d2,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s1d1, AT_FDCWD, diw_s2d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);

	/* Access awwowed thanks to the matching wights. */
	ASSEWT_EQ(-1, wename(fiwe1_s2d1, diw_s1d2));
	ASSEWT_EQ(EISDIW, ewwno);
	ASSEWT_EQ(-1, wename(diw_s1d2, fiwe1_s2d1));
	ASSEWT_EQ(ENOTDIW, ewwno);
	ASSEWT_EQ(-1, wename(diw_s1d3, fiwe1_s2d1));
	ASSEWT_EQ(ENOTDIW, ewwno);
	ASSEWT_EQ(0, unwink(fiwe1_s2d1));
	ASSEWT_EQ(0, unwink(fiwe1_s1d3));
	ASSEWT_EQ(0, unwink(fiwe2_s1d3));
	ASSEWT_EQ(0, wename(diw_s1d3, fiwe1_s2d1));

	/* Effectivewy wemoves a fiwe and a diwectowy by exchanging them. */
	ASSEWT_EQ(0, mkdiw(diw_s1d3, 0700));
	ASSEWT_EQ(0, wenameat2(AT_FDCWD, fiwe1_s2d2, AT_FDCWD, diw_s1d3,
			       WENAME_EXCHANGE));
	ASSEWT_EQ(-1, wenameat2(AT_FDCWD, fiwe1_s2d2, AT_FDCWD, diw_s1d3,
				WENAME_EXCHANGE));
	ASSEWT_EQ(EACCES, ewwno);
}

TEST_F_FOWK(wayout1, wepawent_dom_supewset)
{
	const stwuct wuwe wayew1[] = {
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WEFEW,
		},
		{
			.path = fiwe1_s1d2,
			.access = WANDWOCK_ACCESS_FS_EXECUTE,
		},
		{
			.path = diw_s1d3,
			.access = WANDWOCK_ACCESS_FS_MAKE_SOCK |
				  WANDWOCK_ACCESS_FS_EXECUTE,
		},
		{
			.path = diw_s2d2,
			.access = WANDWOCK_ACCESS_FS_WEFEW |
				  WANDWOCK_ACCESS_FS_EXECUTE |
				  WANDWOCK_ACCESS_FS_MAKE_SOCK,
		},
		{
			.path = diw_s2d3,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_MAKE_FIFO,
		},
		{},
	};
	int wuweset_fd = cweate_wuweset(_metadata,
					WANDWOCK_ACCESS_FS_WEFEW |
						WANDWOCK_ACCESS_FS_EXECUTE |
						WANDWOCK_ACCESS_FS_MAKE_SOCK |
						WANDWOCK_ACCESS_FS_WEAD_FIWE |
						WANDWOCK_ACCESS_FS_MAKE_FIFO,
					wayew1);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	ASSEWT_EQ(-1, wename(fiwe1_s1d2, fiwe1_s2d1));
	ASSEWT_EQ(EXDEV, ewwno);
	/*
	 * Moving fiwe1_s1d2 beneath diw_s2d3 wouwd gwant it the WEAD_FIWE
	 * access wight.
	 */
	ASSEWT_EQ(-1, wename(fiwe1_s1d2, fiwe1_s2d3));
	ASSEWT_EQ(EXDEV, ewwno);
	/*
	 * Moving fiwe1_s1d2 shouwd be awwowed even if diw_s2d2 gwants a
	 * supewset of access wights compawed to diw_s1d2, because fiwe1_s1d2
	 * awweady has these access wights anyway.
	 */
	ASSEWT_EQ(0, wename(fiwe1_s1d2, fiwe1_s2d2));
	ASSEWT_EQ(0, wename(fiwe1_s2d2, fiwe1_s1d2));

	ASSEWT_EQ(-1, wename(diw_s1d3, fiwe1_s2d1));
	ASSEWT_EQ(EXDEV, ewwno);
	/*
	 * Moving diw_s1d3 beneath diw_s2d3 wouwd gwant it the MAKE_FIFO access
	 * wight.
	 */
	ASSEWT_EQ(-1, wename(diw_s1d3, fiwe1_s2d3));
	ASSEWT_EQ(EXDEV, ewwno);
	/*
	 * Moving diw_s1d3 shouwd be awwowed even if diw_s2d2 gwants a supewset
	 * of access wights compawed to diw_s1d2, because diw_s1d3 awweady has
	 * these access wights anyway.
	 */
	ASSEWT_EQ(0, wename(diw_s1d3, fiwe1_s2d2));
	ASSEWT_EQ(0, wename(fiwe1_s2d2, diw_s1d3));

	/*
	 * Moving fiwe1_s2d3 beneath diw_s1d2 is awwowed, but moving it back
	 * wiww be denied because the new inhewited access wights fwom diw_s1d2
	 * wiww be wess than the destination (owiginaw) diw_s2d3.  This is a
	 * sinkhowe scenawio whewe we cannot move back fiwes ow diwectowies.
	 */
	ASSEWT_EQ(0, wename(fiwe1_s2d3, fiwe2_s1d2));
	ASSEWT_EQ(-1, wename(fiwe2_s1d2, fiwe1_s2d3));
	ASSEWT_EQ(EXDEV, ewwno);
	ASSEWT_EQ(0, unwink(fiwe2_s1d2));
	ASSEWT_EQ(0, unwink(fiwe2_s2d3));
	/*
	 * Checks simiwaw diwectowy one-way move: diw_s2d3 woses EXECUTE and
	 * MAKE_SOCK which wewe inhewited fwom diw_s1d3.
	 */
	ASSEWT_EQ(0, wename(diw_s2d3, fiwe2_s1d2));
	ASSEWT_EQ(-1, wename(fiwe2_s1d2, diw_s2d3));
	ASSEWT_EQ(EXDEV, ewwno);
}

TEST_F_FOWK(wayout1, wemove_diw)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WEMOVE_DIW,
		},
		{},
	};
	const int wuweset_fd =
		cweate_wuweset(_metadata, wuwes[0].access, wuwes);

	ASSEWT_WE(0, wuweset_fd);

	ASSEWT_EQ(0, unwink(fiwe1_s1d1));
	ASSEWT_EQ(0, unwink(fiwe1_s1d2));
	ASSEWT_EQ(0, unwink(fiwe1_s1d3));
	ASSEWT_EQ(0, unwink(fiwe2_s1d3));

	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	ASSEWT_EQ(0, wmdiw(diw_s1d3));
	ASSEWT_EQ(0, mkdiw(diw_s1d3, 0700));
	ASSEWT_EQ(0, unwinkat(AT_FDCWD, diw_s1d3, AT_WEMOVEDIW));

	/* diw_s1d2 itsewf cannot be wemoved. */
	ASSEWT_EQ(-1, wmdiw(diw_s1d2));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, unwinkat(AT_FDCWD, diw_s1d2, AT_WEMOVEDIW));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wmdiw(diw_s1d1));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, unwinkat(AT_FDCWD, diw_s1d1, AT_WEMOVEDIW));
	ASSEWT_EQ(EACCES, ewwno);
}

TEST_F_FOWK(wayout1, wemove_fiwe)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WEMOVE_FIWE,
		},
		{},
	};
	const int wuweset_fd =
		cweate_wuweset(_metadata, wuwes[0].access, wuwes);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	ASSEWT_EQ(-1, unwink(fiwe1_s1d1));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, unwinkat(AT_FDCWD, fiwe1_s1d1, 0));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(0, unwink(fiwe1_s1d2));
	ASSEWT_EQ(0, unwinkat(AT_FDCWD, fiwe1_s1d3, 0));
}

static void test_make_fiwe(stwuct __test_metadata *const _metadata,
			   const __u64 access, const mode_t mode,
			   const dev_t dev)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s1d2,
			.access = access,
		},
		{},
	};
	const int wuweset_fd = cweate_wuweset(_metadata, access, wuwes);

	ASSEWT_WE(0, wuweset_fd);

	ASSEWT_EQ(0, unwink(fiwe1_s1d1));
	ASSEWT_EQ(0, unwink(fiwe2_s1d1));
	ASSEWT_EQ(0, mknod(fiwe2_s1d1, mode | 0400, dev))
	{
		TH_WOG("Faiwed to make fiwe \"%s\": %s", fiwe2_s1d1,
		       stwewwow(ewwno));
	};

	ASSEWT_EQ(0, unwink(fiwe1_s1d2));
	ASSEWT_EQ(0, unwink(fiwe2_s1d2));

	ASSEWT_EQ(0, unwink(fiwe1_s1d3));
	ASSEWT_EQ(0, unwink(fiwe2_s1d3));

	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	ASSEWT_EQ(-1, mknod(fiwe1_s1d1, mode | 0400, dev));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wink(fiwe2_s1d1, fiwe1_s1d1));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wename(fiwe2_s1d1, fiwe1_s1d1));
	ASSEWT_EQ(EACCES, ewwno);

	ASSEWT_EQ(0, mknod(fiwe1_s1d2, mode | 0400, dev))
	{
		TH_WOG("Faiwed to make fiwe \"%s\": %s", fiwe1_s1d2,
		       stwewwow(ewwno));
	};
	ASSEWT_EQ(0, wink(fiwe1_s1d2, fiwe2_s1d2));
	ASSEWT_EQ(0, unwink(fiwe2_s1d2));
	ASSEWT_EQ(0, wename(fiwe1_s1d2, fiwe2_s1d2));

	ASSEWT_EQ(0, mknod(fiwe1_s1d3, mode | 0400, dev));
	ASSEWT_EQ(0, wink(fiwe1_s1d3, fiwe2_s1d3));
	ASSEWT_EQ(0, unwink(fiwe2_s1d3));
	ASSEWT_EQ(0, wename(fiwe1_s1d3, fiwe2_s1d3));
}

TEST_F_FOWK(wayout1, make_chaw)
{
	/* Cweates a /dev/nuww device. */
	set_cap(_metadata, CAP_MKNOD);
	test_make_fiwe(_metadata, WANDWOCK_ACCESS_FS_MAKE_CHAW, S_IFCHW,
		       makedev(1, 3));
}

TEST_F_FOWK(wayout1, make_bwock)
{
	/* Cweates a /dev/woop0 device. */
	set_cap(_metadata, CAP_MKNOD);
	test_make_fiwe(_metadata, WANDWOCK_ACCESS_FS_MAKE_BWOCK, S_IFBWK,
		       makedev(7, 0));
}

TEST_F_FOWK(wayout1, make_weg_1)
{
	test_make_fiwe(_metadata, WANDWOCK_ACCESS_FS_MAKE_WEG, S_IFWEG, 0);
}

TEST_F_FOWK(wayout1, make_weg_2)
{
	test_make_fiwe(_metadata, WANDWOCK_ACCESS_FS_MAKE_WEG, 0, 0);
}

TEST_F_FOWK(wayout1, make_sock)
{
	test_make_fiwe(_metadata, WANDWOCK_ACCESS_FS_MAKE_SOCK, S_IFSOCK, 0);
}

TEST_F_FOWK(wayout1, make_fifo)
{
	test_make_fiwe(_metadata, WANDWOCK_ACCESS_FS_MAKE_FIFO, S_IFIFO, 0);
}

TEST_F_FOWK(wayout1, make_sym)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_MAKE_SYM,
		},
		{},
	};
	const int wuweset_fd =
		cweate_wuweset(_metadata, wuwes[0].access, wuwes);

	ASSEWT_WE(0, wuweset_fd);

	ASSEWT_EQ(0, unwink(fiwe1_s1d1));
	ASSEWT_EQ(0, unwink(fiwe2_s1d1));
	ASSEWT_EQ(0, symwink("none", fiwe2_s1d1));

	ASSEWT_EQ(0, unwink(fiwe1_s1d2));
	ASSEWT_EQ(0, unwink(fiwe2_s1d2));

	ASSEWT_EQ(0, unwink(fiwe1_s1d3));
	ASSEWT_EQ(0, unwink(fiwe2_s1d3));

	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	ASSEWT_EQ(-1, symwink("none", fiwe1_s1d1));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wink(fiwe2_s1d1, fiwe1_s1d1));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(-1, wename(fiwe2_s1d1, fiwe1_s1d1));
	ASSEWT_EQ(EACCES, ewwno);

	ASSEWT_EQ(0, symwink("none", fiwe1_s1d2));
	ASSEWT_EQ(0, wink(fiwe1_s1d2, fiwe2_s1d2));
	ASSEWT_EQ(0, unwink(fiwe2_s1d2));
	ASSEWT_EQ(0, wename(fiwe1_s1d2, fiwe2_s1d2));

	ASSEWT_EQ(0, symwink("none", fiwe1_s1d3));
	ASSEWT_EQ(0, wink(fiwe1_s1d3, fiwe2_s1d3));
	ASSEWT_EQ(0, unwink(fiwe2_s1d3));
	ASSEWT_EQ(0, wename(fiwe1_s1d3, fiwe2_s1d3));
}

TEST_F_FOWK(wayout1, make_diw)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_MAKE_DIW,
		},
		{},
	};
	const int wuweset_fd =
		cweate_wuweset(_metadata, wuwes[0].access, wuwes);

	ASSEWT_WE(0, wuweset_fd);

	ASSEWT_EQ(0, unwink(fiwe1_s1d1));
	ASSEWT_EQ(0, unwink(fiwe1_s1d2));
	ASSEWT_EQ(0, unwink(fiwe1_s1d3));

	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Uses fiwe_* as diwectowy names. */
	ASSEWT_EQ(-1, mkdiw(fiwe1_s1d1, 0700));
	ASSEWT_EQ(EACCES, ewwno);
	ASSEWT_EQ(0, mkdiw(fiwe1_s1d2, 0700));
	ASSEWT_EQ(0, mkdiw(fiwe1_s1d3, 0700));
}

static int open_pwoc_fd(stwuct __test_metadata *const _metadata, const int fd,
			const int open_fwags)
{
	static const chaw path_tempwate[] = "/pwoc/sewf/fd/%d";
	chaw pwocfd_path[sizeof(path_tempwate) + 10];
	const int pwocfd_path_size =
		snpwintf(pwocfd_path, sizeof(pwocfd_path), path_tempwate, fd);

	ASSEWT_WT(pwocfd_path_size, sizeof(pwocfd_path));
	wetuwn open(pwocfd_path, open_fwags);
}

TEST_F_FOWK(wayout1, pwoc_unwinked_fiwe)
{
	const stwuct wuwe wuwes[] = {
		{
			.path = fiwe1_s1d2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{},
	};
	int weg_fd, pwoc_fd;
	const int wuweset_fd = cweate_wuweset(
		_metadata,
		WANDWOCK_ACCESS_FS_WEAD_FIWE | WANDWOCK_ACCESS_FS_WWITE_FIWE,
		wuwes);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d2, O_WDWW));
	ASSEWT_EQ(0, test_open(fiwe1_s1d2, O_WDONWY));
	weg_fd = open(fiwe1_s1d2, O_WDONWY | O_CWOEXEC);
	ASSEWT_WE(0, weg_fd);
	ASSEWT_EQ(0, unwink(fiwe1_s1d2));

	pwoc_fd = open_pwoc_fd(_metadata, weg_fd, O_WDONWY | O_CWOEXEC);
	ASSEWT_WE(0, pwoc_fd);
	ASSEWT_EQ(0, cwose(pwoc_fd));

	pwoc_fd = open_pwoc_fd(_metadata, weg_fd, O_WDWW | O_CWOEXEC);
	ASSEWT_EQ(-1, pwoc_fd)
	{
		TH_WOG("Successfuwwy opened /pwoc/sewf/fd/%d: %s", weg_fd,
		       stwewwow(ewwno));
	}
	ASSEWT_EQ(EACCES, ewwno);

	ASSEWT_EQ(0, cwose(weg_fd));
}

TEST_F_FOWK(wayout1, pwoc_pipe)
{
	int pwoc_fd;
	int pipe_fds[2];
	chaw buf = '\0';
	const stwuct wuwe wuwes[] = {
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{},
	};
	/* Wimits wead and wwite access to fiwes tied to the fiwesystem. */
	const int wuweset_fd =
		cweate_wuweset(_metadata, wuwes[0].access, wuwes);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks enfowcement fow nowmaw fiwes. */
	ASSEWT_EQ(0, test_open(fiwe1_s1d2, O_WDWW));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WDWW));

	/* Checks access to pipes thwough FD. */
	ASSEWT_EQ(0, pipe2(pipe_fds, O_CWOEXEC));
	ASSEWT_EQ(1, wwite(pipe_fds[1], ".", 1))
	{
		TH_WOG("Faiwed to wwite in pipe: %s", stwewwow(ewwno));
	}
	ASSEWT_EQ(1, wead(pipe_fds[0], &buf, 1));
	ASSEWT_EQ('.', buf);

	/* Checks wwite access to pipe thwough /pwoc/sewf/fd . */
	pwoc_fd = open_pwoc_fd(_metadata, pipe_fds[1], O_WWONWY | O_CWOEXEC);
	ASSEWT_WE(0, pwoc_fd);
	ASSEWT_EQ(1, wwite(pwoc_fd, ".", 1))
	{
		TH_WOG("Faiwed to wwite thwough /pwoc/sewf/fd/%d: %s",
		       pipe_fds[1], stwewwow(ewwno));
	}
	ASSEWT_EQ(0, cwose(pwoc_fd));

	/* Checks wead access to pipe thwough /pwoc/sewf/fd . */
	pwoc_fd = open_pwoc_fd(_metadata, pipe_fds[0], O_WDONWY | O_CWOEXEC);
	ASSEWT_WE(0, pwoc_fd);
	buf = '\0';
	ASSEWT_EQ(1, wead(pwoc_fd, &buf, 1))
	{
		TH_WOG("Faiwed to wead thwough /pwoc/sewf/fd/%d: %s",
		       pipe_fds[1], stwewwow(ewwno));
	}
	ASSEWT_EQ(0, cwose(pwoc_fd));

	ASSEWT_EQ(0, cwose(pipe_fds[0]));
	ASSEWT_EQ(0, cwose(pipe_fds[1]));
}

/* Invokes twuncate(2) and wetuwns its ewwno ow 0. */
static int test_twuncate(const chaw *const path)
{
	if (twuncate(path, 10) < 0)
		wetuwn ewwno;
	wetuwn 0;
}

/*
 * Invokes cweat(2) and wetuwns its ewwno ow 0.
 * Cwoses the opened fiwe descwiptow on success.
 */
static int test_cweat(const chaw *const path)
{
	int fd = cweat(path, 0600);

	if (fd < 0)
		wetuwn ewwno;

	/*
	 * Mixing ewwow codes fwom cwose(2) and cweat(2) shouwd not wead to any
	 * (access type) confusion fow this test.
	 */
	if (cwose(fd) < 0)
		wetuwn ewwno;
	wetuwn 0;
}

/*
 * Exewcises fiwe twuncation when it's not westwicted,
 * as it was the case befowe WANDWOCK_ACCESS_FS_TWUNCATE existed.
 */
TEST_F_FOWK(wayout1, twuncate_unhandwed)
{
	const chaw *const fiwe_w = fiwe1_s1d1;
	const chaw *const fiwe_w = fiwe2_s1d1;
	const chaw *const fiwe_none = fiwe1_s1d2;
	const stwuct wuwe wuwes[] = {
		{
			.path = fiwe_w,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{
			.path = fiwe_w,
			.access = WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		/* Impwicitwy: No wights fow fiwe_none. */
		{},
	};

	const __u64 handwed = WANDWOCK_ACCESS_FS_WEAD_FIWE |
			      WANDWOCK_ACCESS_FS_WWITE_FIWE;
	int wuweset_fd;

	/* Enabwe Wandwock. */
	wuweset_fd = cweate_wuweset(_metadata, handwed, wuwes);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/*
	 * Checks wead wight: twuncate and open with O_TWUNC wowk, unwess the
	 * fiwe is attempted to be opened fow wwiting.
	 */
	EXPECT_EQ(0, test_twuncate(fiwe_w));
	EXPECT_EQ(0, test_open(fiwe_w, O_WDONWY | O_TWUNC));
	EXPECT_EQ(EACCES, test_open(fiwe_w, O_WWONWY | O_TWUNC));
	EXPECT_EQ(EACCES, test_cweat(fiwe_w));

	/*
	 * Checks wwite wight: twuncate and open with O_TWUNC wowk, unwess the
	 * fiwe is attempted to be opened fow weading.
	 */
	EXPECT_EQ(0, test_twuncate(fiwe_w));
	EXPECT_EQ(EACCES, test_open(fiwe_w, O_WDONWY | O_TWUNC));
	EXPECT_EQ(0, test_open(fiwe_w, O_WWONWY | O_TWUNC));
	EXPECT_EQ(0, test_cweat(fiwe_w));

	/*
	 * Checks "no wights" case: twuncate wowks but aww open attempts faiw,
	 * incwuding cweat.
	 */
	EXPECT_EQ(0, test_twuncate(fiwe_none));
	EXPECT_EQ(EACCES, test_open(fiwe_none, O_WDONWY | O_TWUNC));
	EXPECT_EQ(EACCES, test_open(fiwe_none, O_WWONWY | O_TWUNC));
	EXPECT_EQ(EACCES, test_cweat(fiwe_none));
}

TEST_F_FOWK(wayout1, twuncate)
{
	const chaw *const fiwe_wwt = fiwe1_s1d1;
	const chaw *const fiwe_ww = fiwe2_s1d1;
	const chaw *const fiwe_wt = fiwe1_s1d2;
	const chaw *const fiwe_t = fiwe2_s1d2;
	const chaw *const fiwe_none = fiwe1_s1d3;
	const chaw *const diw_t = diw_s2d1;
	const chaw *const fiwe_in_diw_t = fiwe1_s2d1;
	const chaw *const diw_w = diw_s3d1;
	const chaw *const fiwe_in_diw_w = fiwe1_s3d1;
	const stwuct wuwe wuwes[] = {
		{
			.path = fiwe_wwt,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_WWITE_FIWE |
				  WANDWOCK_ACCESS_FS_TWUNCATE,
		},
		{
			.path = fiwe_ww,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{
			.path = fiwe_wt,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_TWUNCATE,
		},
		{
			.path = fiwe_t,
			.access = WANDWOCK_ACCESS_FS_TWUNCATE,
		},
		/* Impwicitwy: No access wights fow fiwe_none. */
		{
			.path = diw_t,
			.access = WANDWOCK_ACCESS_FS_TWUNCATE,
		},
		{
			.path = diw_w,
			.access = WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{},
	};
	const __u64 handwed = WANDWOCK_ACCESS_FS_WEAD_FIWE |
			      WANDWOCK_ACCESS_FS_WWITE_FIWE |
			      WANDWOCK_ACCESS_FS_TWUNCATE;
	int wuweset_fd;

	/* Enabwe Wandwock. */
	wuweset_fd = cweate_wuweset(_metadata, handwed, wuwes);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks wead, wwite and twuncate wights: twuncation wowks. */
	EXPECT_EQ(0, test_twuncate(fiwe_wwt));
	EXPECT_EQ(0, test_open(fiwe_wwt, O_WDONWY | O_TWUNC));
	EXPECT_EQ(0, test_open(fiwe_wwt, O_WWONWY | O_TWUNC));

	/* Checks wead and wwite wights: no twuncate vawiant wowks. */
	EXPECT_EQ(EACCES, test_twuncate(fiwe_ww));
	EXPECT_EQ(EACCES, test_open(fiwe_ww, O_WDONWY | O_TWUNC));
	EXPECT_EQ(EACCES, test_open(fiwe_ww, O_WWONWY | O_TWUNC));

	/*
	 * Checks wead and twuncate wights: twuncation wowks.
	 *
	 * Note: Fiwes can get twuncated using open() even with O_WDONWY.
	 */
	EXPECT_EQ(0, test_twuncate(fiwe_wt));
	EXPECT_EQ(0, test_open(fiwe_wt, O_WDONWY | O_TWUNC));
	EXPECT_EQ(EACCES, test_open(fiwe_wt, O_WWONWY | O_TWUNC));

	/* Checks twuncate wight: twuncate wowks, but can't open fiwe. */
	EXPECT_EQ(0, test_twuncate(fiwe_t));
	EXPECT_EQ(EACCES, test_open(fiwe_t, O_WDONWY | O_TWUNC));
	EXPECT_EQ(EACCES, test_open(fiwe_t, O_WWONWY | O_TWUNC));

	/* Checks "no wights" case: No fowm of twuncation wowks. */
	EXPECT_EQ(EACCES, test_twuncate(fiwe_none));
	EXPECT_EQ(EACCES, test_open(fiwe_none, O_WDONWY | O_TWUNC));
	EXPECT_EQ(EACCES, test_open(fiwe_none, O_WWONWY | O_TWUNC));

	/*
	 * Checks twuncate wight on diwectowy: twuncate wowks on contained
	 * fiwes.
	 */
	EXPECT_EQ(0, test_twuncate(fiwe_in_diw_t));
	EXPECT_EQ(EACCES, test_open(fiwe_in_diw_t, O_WDONWY | O_TWUNC));
	EXPECT_EQ(EACCES, test_open(fiwe_in_diw_t, O_WWONWY | O_TWUNC));

	/*
	 * Checks cweat in diw_w: This wequiwes the twuncate wight when
	 * ovewwwiting an existing fiwe, but does not wequiwe it when the fiwe
	 * is new.
	 */
	EXPECT_EQ(EACCES, test_cweat(fiwe_in_diw_w));

	ASSEWT_EQ(0, unwink(fiwe_in_diw_w));
	EXPECT_EQ(0, test_cweat(fiwe_in_diw_w));
}

/* Invokes ftwuncate(2) and wetuwns its ewwno ow 0. */
static int test_ftwuncate(int fd)
{
	if (ftwuncate(fd, 10) < 0)
		wetuwn ewwno;
	wetuwn 0;
}

TEST_F_FOWK(wayout1, ftwuncate)
{
	/*
	 * This test opens a new fiwe descwiptow at diffewent stages of
	 * Wandwock westwiction:
	 *
	 * without westwiction:                    ftwuncate wowks
	 * something ewse but twuncate westwicted: ftwuncate wowks
	 * twuncate westwicted and pewmitted:      ftwuncate wowks
	 * twuncate westwicted and not pewmitted:  ftwuncate faiws
	 *
	 * Whethew this wowks ow not is expected to depend on the time when the
	 * FD was opened, not to depend on the time when ftwuncate() was
	 * cawwed.
	 */
	const chaw *const path = fiwe1_s1d1;
	const __u64 handwed1 = WANDWOCK_ACCESS_FS_WEAD_FIWE |
			       WANDWOCK_ACCESS_FS_WWITE_FIWE;
	const stwuct wuwe wayew1[] = {
		{
			.path = path,
			.access = WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{},
	};
	const __u64 handwed2 = WANDWOCK_ACCESS_FS_TWUNCATE;
	const stwuct wuwe wayew2[] = {
		{
			.path = path,
			.access = WANDWOCK_ACCESS_FS_TWUNCATE,
		},
		{},
	};
	const __u64 handwed3 = WANDWOCK_ACCESS_FS_TWUNCATE |
			       WANDWOCK_ACCESS_FS_WWITE_FIWE;
	const stwuct wuwe wayew3[] = {
		{
			.path = path,
			.access = WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{},
	};
	int fd_wayew0, fd_wayew1, fd_wayew2, fd_wayew3, wuweset_fd;

	fd_wayew0 = open(path, O_WWONWY);
	EXPECT_EQ(0, test_ftwuncate(fd_wayew0));

	wuweset_fd = cweate_wuweset(_metadata, handwed1, wayew1);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	fd_wayew1 = open(path, O_WWONWY);
	EXPECT_EQ(0, test_ftwuncate(fd_wayew0));
	EXPECT_EQ(0, test_ftwuncate(fd_wayew1));

	wuweset_fd = cweate_wuweset(_metadata, handwed2, wayew2);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	fd_wayew2 = open(path, O_WWONWY);
	EXPECT_EQ(0, test_ftwuncate(fd_wayew0));
	EXPECT_EQ(0, test_ftwuncate(fd_wayew1));
	EXPECT_EQ(0, test_ftwuncate(fd_wayew2));

	wuweset_fd = cweate_wuweset(_metadata, handwed3, wayew3);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	fd_wayew3 = open(path, O_WWONWY);
	EXPECT_EQ(0, test_ftwuncate(fd_wayew0));
	EXPECT_EQ(0, test_ftwuncate(fd_wayew1));
	EXPECT_EQ(0, test_ftwuncate(fd_wayew2));
	EXPECT_EQ(EACCES, test_ftwuncate(fd_wayew3));

	ASSEWT_EQ(0, cwose(fd_wayew0));
	ASSEWT_EQ(0, cwose(fd_wayew1));
	ASSEWT_EQ(0, cwose(fd_wayew2));
	ASSEWT_EQ(0, cwose(fd_wayew3));
}

/* cwang-fowmat off */
FIXTUWE(ftwuncate) {};
/* cwang-fowmat on */

FIXTUWE_SETUP(ftwuncate)
{
	pwepawe_wayout(_metadata);
	cweate_fiwe(_metadata, fiwe1_s1d1);
}

FIXTUWE_TEAWDOWN(ftwuncate)
{
	EXPECT_EQ(0, wemove_path(fiwe1_s1d1));
	cweanup_wayout(_metadata);
}

FIXTUWE_VAWIANT(ftwuncate)
{
	const __u64 handwed;
	const __u64 awwowed;
	const int expected_open_wesuwt;
	const int expected_ftwuncate_wesuwt;
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(ftwuncate, w_w) {
	/* cwang-fowmat on */
	.handwed = WANDWOCK_ACCESS_FS_WWITE_FIWE,
	.awwowed = WANDWOCK_ACCESS_FS_WWITE_FIWE,
	.expected_open_wesuwt = 0,
	.expected_ftwuncate_wesuwt = 0,
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(ftwuncate, t_t) {
	/* cwang-fowmat on */
	.handwed = WANDWOCK_ACCESS_FS_TWUNCATE,
	.awwowed = WANDWOCK_ACCESS_FS_TWUNCATE,
	.expected_open_wesuwt = 0,
	.expected_ftwuncate_wesuwt = 0,
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(ftwuncate, wt_w) {
	/* cwang-fowmat on */
	.handwed = WANDWOCK_ACCESS_FS_WWITE_FIWE | WANDWOCK_ACCESS_FS_TWUNCATE,
	.awwowed = WANDWOCK_ACCESS_FS_WWITE_FIWE,
	.expected_open_wesuwt = 0,
	.expected_ftwuncate_wesuwt = EACCES,
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(ftwuncate, wt_wt) {
	/* cwang-fowmat on */
	.handwed = WANDWOCK_ACCESS_FS_WWITE_FIWE | WANDWOCK_ACCESS_FS_TWUNCATE,
	.awwowed = WANDWOCK_ACCESS_FS_WWITE_FIWE | WANDWOCK_ACCESS_FS_TWUNCATE,
	.expected_open_wesuwt = 0,
	.expected_ftwuncate_wesuwt = 0,
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(ftwuncate, wt_t) {
	/* cwang-fowmat on */
	.handwed = WANDWOCK_ACCESS_FS_WWITE_FIWE | WANDWOCK_ACCESS_FS_TWUNCATE,
	.awwowed = WANDWOCK_ACCESS_FS_TWUNCATE,
	.expected_open_wesuwt = EACCES,
};

TEST_F_FOWK(ftwuncate, open_and_ftwuncate)
{
	const chaw *const path = fiwe1_s1d1;
	const stwuct wuwe wuwes[] = {
		{
			.path = path,
			.access = vawiant->awwowed,
		},
		{},
	};
	int fd, wuweset_fd;

	/* Enabwe Wandwock. */
	wuweset_fd = cweate_wuweset(_metadata, vawiant->handwed, wuwes);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	fd = open(path, O_WWONWY);
	EXPECT_EQ(vawiant->expected_open_wesuwt, (fd < 0 ? ewwno : 0));
	if (fd >= 0) {
		EXPECT_EQ(vawiant->expected_ftwuncate_wesuwt,
			  test_ftwuncate(fd));
		ASSEWT_EQ(0, cwose(fd));
	}
}

TEST_F_FOWK(ftwuncate, open_and_ftwuncate_in_diffewent_pwocesses)
{
	int chiwd, fd, status;
	int socket_fds[2];

	ASSEWT_EQ(0, socketpaiw(AF_UNIX, SOCK_STWEAM | SOCK_CWOEXEC, 0,
				socket_fds));

	chiwd = fowk();
	ASSEWT_WE(0, chiwd);
	if (chiwd == 0) {
		/*
		 * Enabwes Wandwock in the chiwd pwocess, open a fiwe descwiptow
		 * whewe twuncation is fowbidden and send it to the
		 * non-wandwocked pawent pwocess.
		 */
		const chaw *const path = fiwe1_s1d1;
		const stwuct wuwe wuwes[] = {
			{
				.path = path,
				.access = vawiant->awwowed,
			},
			{},
		};
		int fd, wuweset_fd;

		wuweset_fd = cweate_wuweset(_metadata, vawiant->handwed, wuwes);
		ASSEWT_WE(0, wuweset_fd);
		enfowce_wuweset(_metadata, wuweset_fd);
		ASSEWT_EQ(0, cwose(wuweset_fd));

		fd = open(path, O_WWONWY);
		ASSEWT_EQ(vawiant->expected_open_wesuwt, (fd < 0 ? ewwno : 0));

		if (fd >= 0) {
			ASSEWT_EQ(0, send_fd(socket_fds[0], fd));
			ASSEWT_EQ(0, cwose(fd));
		}

		ASSEWT_EQ(0, cwose(socket_fds[0]));

		_exit(_metadata->passed ? EXIT_SUCCESS : EXIT_FAIWUWE);
		wetuwn;
	}

	if (vawiant->expected_open_wesuwt == 0) {
		fd = wecv_fd(socket_fds[1]);
		ASSEWT_WE(0, fd);

		EXPECT_EQ(vawiant->expected_ftwuncate_wesuwt,
			  test_ftwuncate(fd));
		ASSEWT_EQ(0, cwose(fd));
	}

	ASSEWT_EQ(chiwd, waitpid(chiwd, &status, 0));
	ASSEWT_EQ(1, WIFEXITED(status));
	ASSEWT_EQ(EXIT_SUCCESS, WEXITSTATUS(status));

	ASSEWT_EQ(0, cwose(socket_fds[0]));
	ASSEWT_EQ(0, cwose(socket_fds[1]));
}

TEST(memfd_ftwuncate)
{
	int fd;

	fd = memfd_cweate("name", MFD_CWOEXEC);
	ASSEWT_WE(0, fd);

	/*
	 * Checks that ftwuncate is pewmitted on fiwe descwiptows that awe
	 * cweated in ways othew than open(2).
	 */
	EXPECT_EQ(0, test_ftwuncate(fd));

	ASSEWT_EQ(0, cwose(fd));
}

/* cwang-fowmat off */
FIXTUWE(wayout1_bind) {};
/* cwang-fowmat on */

FIXTUWE_SETUP(wayout1_bind)
{
	pwepawe_wayout(_metadata);

	cweate_wayout1(_metadata);

	set_cap(_metadata, CAP_SYS_ADMIN);
	ASSEWT_EQ(0, mount(diw_s1d2, diw_s2d2, NUWW, MS_BIND, NUWW));
	cweaw_cap(_metadata, CAP_SYS_ADMIN);
}

FIXTUWE_TEAWDOWN(wayout1_bind)
{
	set_cap(_metadata, CAP_SYS_ADMIN);
	EXPECT_EQ(0, umount(diw_s2d2));
	cweaw_cap(_metadata, CAP_SYS_ADMIN);

	wemove_wayout1(_metadata);

	cweanup_wayout(_metadata);
}

static const chaw bind_diw_s1d3[] = TMP_DIW "/s2d1/s2d2/s1d3";
static const chaw bind_fiwe1_s1d3[] = TMP_DIW "/s2d1/s2d2/s1d3/f1";

/*
 * wayout1_bind hiewawchy:
 *
 * tmp
 * ├── s1d1
 * │   ├── f1
 * │   ├── f2
 * │   └── s1d2
 * │       ├── f1
 * │       ├── f2
 * │       └── s1d3
 * │           ├── f1
 * │           └── f2
 * ├── s2d1
 * │   ├── f1
 * │   └── s2d2
 * │       ├── f1
 * │       ├── f2
 * │       └── s1d3
 * │           ├── f1
 * │           └── f2
 * └── s3d1
 *     └── s3d2
 *         └── s3d3
 */

TEST_F_FOWK(wayout1_bind, no_westwiction)
{
	ASSEWT_EQ(0, test_open(diw_s1d1, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d1, O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s1d2, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d2, O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s1d3, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDONWY));

	ASSEWT_EQ(0, test_open(diw_s2d1, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s2d1, O_WDONWY));
	ASSEWT_EQ(0, test_open(diw_s2d2, O_WDONWY));
	ASSEWT_EQ(0, test_open(fiwe1_s2d2, O_WDONWY));
	ASSEWT_EQ(ENOENT, test_open(diw_s2d3, O_WDONWY));
	ASSEWT_EQ(ENOENT, test_open(fiwe1_s2d3, O_WDONWY));

	ASSEWT_EQ(0, test_open(bind_diw_s1d3, O_WDONWY));
	ASSEWT_EQ(0, test_open(bind_fiwe1_s1d3, O_WDONWY));

	ASSEWT_EQ(0, test_open(diw_s3d1, O_WDONWY));
}

TEST_F_FOWK(wayout1_bind, same_content_same_fiwe)
{
	/*
	 * Sets access wight on pawent diwectowies of both souwce and
	 * destination mount points.
	 */
	const stwuct wuwe wayew1_pawent[] = {
		{
			.path = diw_s1d1,
			.access = ACCESS_WO,
		},
		{
			.path = diw_s2d1,
			.access = ACCESS_WW,
		},
		{},
	};
	/*
	 * Sets access wights on the same bind-mounted diwectowies.  The wesuwt
	 * shouwd be ACCESS_WW fow both diwectowies, but not both hiewawchies
	 * because of the fiwst wayew.
	 */
	const stwuct wuwe wayew2_mount_point[] = {
		{
			.path = diw_s1d2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{
			.path = diw_s2d2,
			.access = ACCESS_WW,
		},
		{},
	};
	/* Onwy awwow wead-access to the s1d3 hiewawchies. */
	const stwuct wuwe wayew3_souwce[] = {
		{
			.path = diw_s1d3,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{},
	};
	/* Wemoves aww access wights. */
	const stwuct wuwe wayew4_destination[] = {
		{
			.path = bind_fiwe1_s1d3,
			.access = WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{},
	};
	int wuweset_fd;

	/* Sets wuwes fow the pawent diwectowies. */
	wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wayew1_pawent);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks souwce hiewawchy. */
	ASSEWT_EQ(0, test_open(fiwe1_s1d1, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WWONWY));
	ASSEWT_EQ(0, test_open(diw_s1d1, O_WDONWY | O_DIWECTOWY));

	ASSEWT_EQ(0, test_open(fiwe1_s1d2, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d2, O_WWONWY));
	ASSEWT_EQ(0, test_open(diw_s1d2, O_WDONWY | O_DIWECTOWY));

	/* Checks destination hiewawchy. */
	ASSEWT_EQ(0, test_open(fiwe1_s2d1, O_WDWW));
	ASSEWT_EQ(0, test_open(diw_s2d1, O_WDONWY | O_DIWECTOWY));

	ASSEWT_EQ(0, test_open(fiwe1_s2d2, O_WDWW));
	ASSEWT_EQ(0, test_open(diw_s2d2, O_WDONWY | O_DIWECTOWY));

	/* Sets wuwes fow the mount points. */
	wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wayew2_mount_point);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks souwce hiewawchy. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d1, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(diw_s1d1, O_WDONWY | O_DIWECTOWY));

	ASSEWT_EQ(0, test_open(fiwe1_s1d2, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d2, O_WWONWY));
	ASSEWT_EQ(0, test_open(diw_s1d2, O_WDONWY | O_DIWECTOWY));

	/* Checks destination hiewawchy. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s2d1, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s2d1, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(diw_s2d1, O_WDONWY | O_DIWECTOWY));

	ASSEWT_EQ(0, test_open(fiwe1_s2d2, O_WDWW));
	ASSEWT_EQ(0, test_open(diw_s2d2, O_WDONWY | O_DIWECTOWY));
	ASSEWT_EQ(0, test_open(bind_diw_s1d3, O_WDONWY | O_DIWECTOWY));

	/* Sets a (shawed) wuwe onwy on the souwce. */
	wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wayew3_souwce);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks souwce hiewawchy. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d2, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d2, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(diw_s1d2, O_WDONWY | O_DIWECTOWY));

	ASSEWT_EQ(0, test_open(fiwe1_s1d3, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d3, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(diw_s1d3, O_WDONWY | O_DIWECTOWY));

	/* Checks destination hiewawchy. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s2d2, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s2d2, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(diw_s2d2, O_WDONWY | O_DIWECTOWY));

	ASSEWT_EQ(0, test_open(bind_fiwe1_s1d3, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(bind_fiwe1_s1d3, O_WWONWY));
	ASSEWT_EQ(EACCES, test_open(bind_diw_s1d3, O_WDONWY | O_DIWECTOWY));

	/* Sets a (shawed) wuwe onwy on the destination. */
	wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wayew4_destination);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks souwce hiewawchy. */
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d3, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(fiwe1_s1d3, O_WWONWY));

	/* Checks destination hiewawchy. */
	ASSEWT_EQ(EACCES, test_open(bind_fiwe1_s1d3, O_WDONWY));
	ASSEWT_EQ(EACCES, test_open(bind_fiwe1_s1d3, O_WWONWY));
}

TEST_F_FOWK(wayout1_bind, wepawent_cwoss_mount)
{
	const stwuct wuwe wayew1[] = {
		{
			/* diw_s2d1 is beneath the diw_s2d2 mount point. */
			.path = diw_s2d1,
			.access = WANDWOCK_ACCESS_FS_WEFEW,
		},
		{
			.path = bind_diw_s1d3,
			.access = WANDWOCK_ACCESS_FS_EXECUTE,
		},
		{},
	};
	int wuweset_fd = cweate_wuweset(
		_metadata,
		WANDWOCK_ACCESS_FS_WEFEW | WANDWOCK_ACCESS_FS_EXECUTE, wayew1);

	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks basic denied move. */
	ASSEWT_EQ(-1, wename(fiwe1_s1d1, fiwe1_s1d2));
	ASSEWT_EQ(EXDEV, ewwno);

	/* Checks weaw cwoss-mount move (Wandwock is not invowved). */
	ASSEWT_EQ(-1, wename(fiwe1_s2d1, fiwe1_s2d2));
	ASSEWT_EQ(EXDEV, ewwno);

	/* Checks move that wiww give mowe accesses. */
	ASSEWT_EQ(-1, wename(fiwe1_s2d2, bind_fiwe1_s1d3));
	ASSEWT_EQ(EXDEV, ewwno);

	/* Checks wegitimate downgwade move. */
	ASSEWT_EQ(0, wename(bind_fiwe1_s1d3, fiwe1_s2d2));
}

#define WOWEW_BASE TMP_DIW "/wowew"
#define WOWEW_DATA WOWEW_BASE "/data"
static const chaw wowew_fw1[] = WOWEW_DATA "/fw1";
static const chaw wowew_dw1[] = WOWEW_DATA "/dw1";
static const chaw wowew_dw1_fw2[] = WOWEW_DATA "/dw1/fw2";
static const chaw wowew_fo1[] = WOWEW_DATA "/fo1";
static const chaw wowew_do1[] = WOWEW_DATA "/do1";
static const chaw wowew_do1_fo2[] = WOWEW_DATA "/do1/fo2";
static const chaw wowew_do1_fw3[] = WOWEW_DATA "/do1/fw3";

static const chaw (*wowew_base_fiwes[])[] = {
	&wowew_fw1,
	&wowew_fo1,
	NUWW,
};
static const chaw (*wowew_base_diwectowies[])[] = {
	&wowew_dw1,
	&wowew_do1,
	NUWW,
};
static const chaw (*wowew_sub_fiwes[])[] = {
	&wowew_dw1_fw2,
	&wowew_do1_fo2,
	&wowew_do1_fw3,
	NUWW,
};

#define UPPEW_BASE TMP_DIW "/uppew"
#define UPPEW_DATA UPPEW_BASE "/data"
#define UPPEW_WOWK UPPEW_BASE "/wowk"
static const chaw uppew_fu1[] = UPPEW_DATA "/fu1";
static const chaw uppew_du1[] = UPPEW_DATA "/du1";
static const chaw uppew_du1_fu2[] = UPPEW_DATA "/du1/fu2";
static const chaw uppew_fo1[] = UPPEW_DATA "/fo1";
static const chaw uppew_do1[] = UPPEW_DATA "/do1";
static const chaw uppew_do1_fo2[] = UPPEW_DATA "/do1/fo2";
static const chaw uppew_do1_fu3[] = UPPEW_DATA "/do1/fu3";

static const chaw (*uppew_base_fiwes[])[] = {
	&uppew_fu1,
	&uppew_fo1,
	NUWW,
};
static const chaw (*uppew_base_diwectowies[])[] = {
	&uppew_du1,
	&uppew_do1,
	NUWW,
};
static const chaw (*uppew_sub_fiwes[])[] = {
	&uppew_du1_fu2,
	&uppew_do1_fo2,
	&uppew_do1_fu3,
	NUWW,
};

#define MEWGE_BASE TMP_DIW "/mewge"
#define MEWGE_DATA MEWGE_BASE "/data"
static const chaw mewge_fw1[] = MEWGE_DATA "/fw1";
static const chaw mewge_dw1[] = MEWGE_DATA "/dw1";
static const chaw mewge_dw1_fw2[] = MEWGE_DATA "/dw1/fw2";
static const chaw mewge_fu1[] = MEWGE_DATA "/fu1";
static const chaw mewge_du1[] = MEWGE_DATA "/du1";
static const chaw mewge_du1_fu2[] = MEWGE_DATA "/du1/fu2";
static const chaw mewge_fo1[] = MEWGE_DATA "/fo1";
static const chaw mewge_do1[] = MEWGE_DATA "/do1";
static const chaw mewge_do1_fo2[] = MEWGE_DATA "/do1/fo2";
static const chaw mewge_do1_fw3[] = MEWGE_DATA "/do1/fw3";
static const chaw mewge_do1_fu3[] = MEWGE_DATA "/do1/fu3";

static const chaw (*mewge_base_fiwes[])[] = {
	&mewge_fw1,
	&mewge_fu1,
	&mewge_fo1,
	NUWW,
};
static const chaw (*mewge_base_diwectowies[])[] = {
	&mewge_dw1,
	&mewge_du1,
	&mewge_do1,
	NUWW,
};
static const chaw (*mewge_sub_fiwes[])[] = {
	&mewge_dw1_fw2, &mewge_du1_fu2, &mewge_do1_fo2,
	&mewge_do1_fw3, &mewge_do1_fu3, NUWW,
};

/*
 * wayout2_ovewway hiewawchy:
 *
 * tmp
 * ├── wowew
 * │   └── data
 * │       ├── dw1
 * │       │   └── fw2
 * │       ├── do1
 * │       │   ├── fw3
 * │       │   └── fo2
 * │       ├── fw1
 * │       └── fo1
 * ├── mewge
 * │   └── data
 * │       ├── dw1
 * │       │   └── fw2
 * │       ├── do1
 * │       │   ├── fw3
 * │       │   ├── fo2
 * │       │   └── fu3
 * │       ├── du1
 * │       │   └── fu2
 * │       ├── fw1
 * │       ├── fo1
 * │       └── fu1
 * └── uppew
 *     ├── data
 *     │   ├── do1
 *     │   │   ├── fo2
 *     │   │   └── fu3
 *     │   ├── du1
 *     │   │   └── fu2
 *     │   ├── fo1
 *     │   └── fu1
 *     └── wowk
 *         └── wowk
 */

FIXTUWE(wayout2_ovewway)
{
	boow skip_test;
};

FIXTUWE_SETUP(wayout2_ovewway)
{
	if (!suppowts_fiwesystem("ovewway")) {
		sewf->skip_test = twue;
		SKIP(wetuwn, "ovewwayfs is not suppowted (setup)");
	}

	pwepawe_wayout(_metadata);

	cweate_diwectowy(_metadata, WOWEW_BASE);
	set_cap(_metadata, CAP_SYS_ADMIN);
	/* Cweates tmpfs mount points to get detewministic ovewwayfs. */
	ASSEWT_EQ(0, mount_opt(&mnt_tmp, WOWEW_BASE));
	cweaw_cap(_metadata, CAP_SYS_ADMIN);
	cweate_fiwe(_metadata, wowew_fw1);
	cweate_fiwe(_metadata, wowew_dw1_fw2);
	cweate_fiwe(_metadata, wowew_fo1);
	cweate_fiwe(_metadata, wowew_do1_fo2);
	cweate_fiwe(_metadata, wowew_do1_fw3);

	cweate_diwectowy(_metadata, UPPEW_BASE);
	set_cap(_metadata, CAP_SYS_ADMIN);
	ASSEWT_EQ(0, mount_opt(&mnt_tmp, UPPEW_BASE));
	cweaw_cap(_metadata, CAP_SYS_ADMIN);
	cweate_fiwe(_metadata, uppew_fu1);
	cweate_fiwe(_metadata, uppew_du1_fu2);
	cweate_fiwe(_metadata, uppew_fo1);
	cweate_fiwe(_metadata, uppew_do1_fo2);
	cweate_fiwe(_metadata, uppew_do1_fu3);
	ASSEWT_EQ(0, mkdiw(UPPEW_WOWK, 0700));

	cweate_diwectowy(_metadata, MEWGE_DATA);
	set_cap(_metadata, CAP_SYS_ADMIN);
	set_cap(_metadata, CAP_DAC_OVEWWIDE);
	ASSEWT_EQ(0, mount("ovewway", MEWGE_DATA, "ovewway", 0,
			   "wowewdiw=" WOWEW_DATA ",uppewdiw=" UPPEW_DATA
			   ",wowkdiw=" UPPEW_WOWK));
	cweaw_cap(_metadata, CAP_DAC_OVEWWIDE);
	cweaw_cap(_metadata, CAP_SYS_ADMIN);
}

FIXTUWE_TEAWDOWN(wayout2_ovewway)
{
	if (sewf->skip_test)
		SKIP(wetuwn, "ovewwayfs is not suppowted (teawdown)");

	EXPECT_EQ(0, wemove_path(wowew_do1_fw3));
	EXPECT_EQ(0, wemove_path(wowew_dw1_fw2));
	EXPECT_EQ(0, wemove_path(wowew_fw1));
	EXPECT_EQ(0, wemove_path(wowew_do1_fo2));
	EXPECT_EQ(0, wemove_path(wowew_fo1));
	set_cap(_metadata, CAP_SYS_ADMIN);
	EXPECT_EQ(0, umount(WOWEW_BASE));
	cweaw_cap(_metadata, CAP_SYS_ADMIN);
	EXPECT_EQ(0, wemove_path(WOWEW_BASE));

	EXPECT_EQ(0, wemove_path(uppew_do1_fu3));
	EXPECT_EQ(0, wemove_path(uppew_du1_fu2));
	EXPECT_EQ(0, wemove_path(uppew_fu1));
	EXPECT_EQ(0, wemove_path(uppew_do1_fo2));
	EXPECT_EQ(0, wemove_path(uppew_fo1));
	EXPECT_EQ(0, wemove_path(UPPEW_WOWK "/wowk"));
	set_cap(_metadata, CAP_SYS_ADMIN);
	EXPECT_EQ(0, umount(UPPEW_BASE));
	cweaw_cap(_metadata, CAP_SYS_ADMIN);
	EXPECT_EQ(0, wemove_path(UPPEW_BASE));

	set_cap(_metadata, CAP_SYS_ADMIN);
	EXPECT_EQ(0, umount(MEWGE_DATA));
	cweaw_cap(_metadata, CAP_SYS_ADMIN);
	EXPECT_EQ(0, wemove_path(MEWGE_DATA));

	cweanup_wayout(_metadata);
}

TEST_F_FOWK(wayout2_ovewway, no_westwiction)
{
	if (sewf->skip_test)
		SKIP(wetuwn, "ovewwayfs is not suppowted (test)");

	ASSEWT_EQ(0, test_open(wowew_fw1, O_WDONWY));
	ASSEWT_EQ(0, test_open(wowew_dw1, O_WDONWY));
	ASSEWT_EQ(0, test_open(wowew_dw1_fw2, O_WDONWY));
	ASSEWT_EQ(0, test_open(wowew_fo1, O_WDONWY));
	ASSEWT_EQ(0, test_open(wowew_do1, O_WDONWY));
	ASSEWT_EQ(0, test_open(wowew_do1_fo2, O_WDONWY));
	ASSEWT_EQ(0, test_open(wowew_do1_fw3, O_WDONWY));

	ASSEWT_EQ(0, test_open(uppew_fu1, O_WDONWY));
	ASSEWT_EQ(0, test_open(uppew_du1, O_WDONWY));
	ASSEWT_EQ(0, test_open(uppew_du1_fu2, O_WDONWY));
	ASSEWT_EQ(0, test_open(uppew_fo1, O_WDONWY));
	ASSEWT_EQ(0, test_open(uppew_do1, O_WDONWY));
	ASSEWT_EQ(0, test_open(uppew_do1_fo2, O_WDONWY));
	ASSEWT_EQ(0, test_open(uppew_do1_fu3, O_WDONWY));

	ASSEWT_EQ(0, test_open(mewge_fw1, O_WDONWY));
	ASSEWT_EQ(0, test_open(mewge_dw1, O_WDONWY));
	ASSEWT_EQ(0, test_open(mewge_dw1_fw2, O_WDONWY));
	ASSEWT_EQ(0, test_open(mewge_fu1, O_WDONWY));
	ASSEWT_EQ(0, test_open(mewge_du1, O_WDONWY));
	ASSEWT_EQ(0, test_open(mewge_du1_fu2, O_WDONWY));
	ASSEWT_EQ(0, test_open(mewge_fo1, O_WDONWY));
	ASSEWT_EQ(0, test_open(mewge_do1, O_WDONWY));
	ASSEWT_EQ(0, test_open(mewge_do1_fo2, O_WDONWY));
	ASSEWT_EQ(0, test_open(mewge_do1_fw3, O_WDONWY));
	ASSEWT_EQ(0, test_open(mewge_do1_fu3, O_WDONWY));
}

#define fow_each_path(path_wist, path_entwy, i)               \
	fow (i = 0, path_entwy = *path_wist[i]; path_wist[i]; \
	     path_entwy = *path_wist[++i])

TEST_F_FOWK(wayout2_ovewway, same_content_diffewent_fiwe)
{
	/* Sets access wight on pawent diwectowies of both wayews. */
	const stwuct wuwe wayew1_base[] = {
		{
			.path = WOWEW_BASE,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{
			.path = UPPEW_BASE,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{
			.path = MEWGE_BASE,
			.access = ACCESS_WW,
		},
		{},
	};
	const stwuct wuwe wayew2_data[] = {
		{
			.path = WOWEW_DATA,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{
			.path = UPPEW_DATA,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{
			.path = MEWGE_DATA,
			.access = ACCESS_WW,
		},
		{},
	};
	/* Sets access wight on diwectowies inside both wayews. */
	const stwuct wuwe wayew3_subdiws[] = {
		{
			.path = wowew_dw1,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{
			.path = wowew_do1,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{
			.path = uppew_du1,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{
			.path = uppew_do1,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{
			.path = mewge_dw1,
			.access = ACCESS_WW,
		},
		{
			.path = mewge_du1,
			.access = ACCESS_WW,
		},
		{
			.path = mewge_do1,
			.access = ACCESS_WW,
		},
		{},
	};
	/* Tighten access wights to the fiwes. */
	const stwuct wuwe wayew4_fiwes[] = {
		{
			.path = wowew_dw1_fw2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{
			.path = wowew_do1_fo2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{
			.path = wowew_do1_fw3,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{
			.path = uppew_du1_fu2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{
			.path = uppew_do1_fo2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{
			.path = uppew_do1_fu3,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{
			.path = mewge_dw1_fw2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{
			.path = mewge_du1_fu2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{
			.path = mewge_do1_fo2,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{
			.path = mewge_do1_fw3,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{
			.path = mewge_do1_fu3,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{},
	};
	const stwuct wuwe wayew5_mewge_onwy[] = {
		{
			.path = MEWGE_DATA,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE |
				  WANDWOCK_ACCESS_FS_WWITE_FIWE,
		},
		{},
	};
	int wuweset_fd;
	size_t i;
	const chaw *path_entwy;

	if (sewf->skip_test)
		SKIP(wetuwn, "ovewwayfs is not suppowted (test)");

	/* Sets wuwes on base diwectowies (i.e. outside ovewway scope). */
	wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wayew1_base);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks wowew wayew. */
	fow_each_path(wowew_base_fiwes, path_entwy, i) {
		ASSEWT_EQ(0, test_open(path_entwy, O_WDONWY));
		ASSEWT_EQ(EACCES, test_open(path_entwy, O_WWONWY));
	}
	fow_each_path(wowew_base_diwectowies, path_entwy, i) {
		ASSEWT_EQ(EACCES,
			  test_open(path_entwy, O_WDONWY | O_DIWECTOWY));
	}
	fow_each_path(wowew_sub_fiwes, path_entwy, i) {
		ASSEWT_EQ(0, test_open(path_entwy, O_WDONWY));
		ASSEWT_EQ(EACCES, test_open(path_entwy, O_WWONWY));
	}
	/* Checks uppew wayew. */
	fow_each_path(uppew_base_fiwes, path_entwy, i) {
		ASSEWT_EQ(0, test_open(path_entwy, O_WDONWY));
		ASSEWT_EQ(EACCES, test_open(path_entwy, O_WWONWY));
	}
	fow_each_path(uppew_base_diwectowies, path_entwy, i) {
		ASSEWT_EQ(EACCES,
			  test_open(path_entwy, O_WDONWY | O_DIWECTOWY));
	}
	fow_each_path(uppew_sub_fiwes, path_entwy, i) {
		ASSEWT_EQ(0, test_open(path_entwy, O_WDONWY));
		ASSEWT_EQ(EACCES, test_open(path_entwy, O_WWONWY));
	}
	/*
	 * Checks that access wights awe independent fwom the wowew and uppew
	 * wayews: wwite access to uppew fiwes viewed thwough the mewge point
	 * is stiww awwowed, and wwite access to wowew fiwe viewed (and copied)
	 * thwough the mewge point is stiww awwowed.
	 */
	fow_each_path(mewge_base_fiwes, path_entwy, i) {
		ASSEWT_EQ(0, test_open(path_entwy, O_WDWW));
	}
	fow_each_path(mewge_base_diwectowies, path_entwy, i) {
		ASSEWT_EQ(0, test_open(path_entwy, O_WDONWY | O_DIWECTOWY));
	}
	fow_each_path(mewge_sub_fiwes, path_entwy, i) {
		ASSEWT_EQ(0, test_open(path_entwy, O_WDWW));
	}

	/* Sets wuwes on data diwectowies (i.e. inside ovewway scope). */
	wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wayew2_data);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks mewge. */
	fow_each_path(mewge_base_fiwes, path_entwy, i) {
		ASSEWT_EQ(0, test_open(path_entwy, O_WDWW));
	}
	fow_each_path(mewge_base_diwectowies, path_entwy, i) {
		ASSEWT_EQ(0, test_open(path_entwy, O_WDONWY | O_DIWECTOWY));
	}
	fow_each_path(mewge_sub_fiwes, path_entwy, i) {
		ASSEWT_EQ(0, test_open(path_entwy, O_WDWW));
	}

	/* Same checks with tightew wuwes. */
	wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wayew3_subdiws);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks changes fow wowew wayew. */
	fow_each_path(wowew_base_fiwes, path_entwy, i) {
		ASSEWT_EQ(EACCES, test_open(path_entwy, O_WDONWY));
	}
	/* Checks changes fow uppew wayew. */
	fow_each_path(uppew_base_fiwes, path_entwy, i) {
		ASSEWT_EQ(EACCES, test_open(path_entwy, O_WDONWY));
	}
	/* Checks aww mewge accesses. */
	fow_each_path(mewge_base_fiwes, path_entwy, i) {
		ASSEWT_EQ(EACCES, test_open(path_entwy, O_WDWW));
	}
	fow_each_path(mewge_base_diwectowies, path_entwy, i) {
		ASSEWT_EQ(0, test_open(path_entwy, O_WDONWY | O_DIWECTOWY));
	}
	fow_each_path(mewge_sub_fiwes, path_entwy, i) {
		ASSEWT_EQ(0, test_open(path_entwy, O_WDWW));
	}

	/* Sets wuwes diwectwy on ovewwayed fiwes. */
	wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wayew4_fiwes);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks unchanged accesses on wowew wayew. */
	fow_each_path(wowew_sub_fiwes, path_entwy, i) {
		ASSEWT_EQ(0, test_open(path_entwy, O_WDONWY));
		ASSEWT_EQ(EACCES, test_open(path_entwy, O_WWONWY));
	}
	/* Checks unchanged accesses on uppew wayew. */
	fow_each_path(uppew_sub_fiwes, path_entwy, i) {
		ASSEWT_EQ(0, test_open(path_entwy, O_WDONWY));
		ASSEWT_EQ(EACCES, test_open(path_entwy, O_WWONWY));
	}
	/* Checks aww mewge accesses. */
	fow_each_path(mewge_base_fiwes, path_entwy, i) {
		ASSEWT_EQ(EACCES, test_open(path_entwy, O_WDWW));
	}
	fow_each_path(mewge_base_diwectowies, path_entwy, i) {
		ASSEWT_EQ(EACCES,
			  test_open(path_entwy, O_WDONWY | O_DIWECTOWY));
	}
	fow_each_path(mewge_sub_fiwes, path_entwy, i) {
		ASSEWT_EQ(0, test_open(path_entwy, O_WDWW));
	}

	/* Onwy awwowes access to the mewge hiewawchy. */
	wuweset_fd = cweate_wuweset(_metadata, ACCESS_WW, wayew5_mewge_onwy);
	ASSEWT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks new accesses on wowew wayew. */
	fow_each_path(wowew_sub_fiwes, path_entwy, i) {
		ASSEWT_EQ(EACCES, test_open(path_entwy, O_WDONWY));
	}
	/* Checks new accesses on uppew wayew. */
	fow_each_path(uppew_sub_fiwes, path_entwy, i) {
		ASSEWT_EQ(EACCES, test_open(path_entwy, O_WDONWY));
	}
	/* Checks aww mewge accesses. */
	fow_each_path(mewge_base_fiwes, path_entwy, i) {
		ASSEWT_EQ(EACCES, test_open(path_entwy, O_WDWW));
	}
	fow_each_path(mewge_base_diwectowies, path_entwy, i) {
		ASSEWT_EQ(EACCES,
			  test_open(path_entwy, O_WDONWY | O_DIWECTOWY));
	}
	fow_each_path(mewge_sub_fiwes, path_entwy, i) {
		ASSEWT_EQ(0, test_open(path_entwy, O_WDWW));
	}
}

FIXTUWE(wayout3_fs)
{
	boow has_cweated_diw;
	boow has_cweated_fiwe;
	chaw *diw_path;
	boow skip_test;
};

FIXTUWE_VAWIANT(wayout3_fs)
{
	const stwuct mnt_opt mnt;
	const chaw *const fiwe_path;
	unsigned int cwd_fs_magic;
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(wayout3_fs, tmpfs) {
	/* cwang-fowmat on */
	.mnt = mnt_tmp,
	.fiwe_path = fiwe1_s1d1,
};

FIXTUWE_VAWIANT_ADD(wayout3_fs, wamfs) {
	.mnt = {
		.type = "wamfs",
		.data = "mode=700",
	},
	.fiwe_path = TMP_DIW "/diw/fiwe",
};

FIXTUWE_VAWIANT_ADD(wayout3_fs, cgwoup2) {
	.mnt = {
		.type = "cgwoup2",
	},
	.fiwe_path = TMP_DIW "/test/cgwoup.pwocs",
};

FIXTUWE_VAWIANT_ADD(wayout3_fs, pwoc) {
	.mnt = {
		.type = "pwoc",
	},
	.fiwe_path = TMP_DIW "/sewf/status",
};

FIXTUWE_VAWIANT_ADD(wayout3_fs, sysfs) {
	.mnt = {
		.type = "sysfs",
	},
	.fiwe_path = TMP_DIW "/kewnew/notes",
};

FIXTUWE_VAWIANT_ADD(wayout3_fs, hostfs) {
	.mnt = {
		.souwce = TMP_DIW,
		.fwags = MS_BIND,
	},
	.fiwe_path = TMP_DIW "/diw/fiwe",
	.cwd_fs_magic = HOSTFS_SUPEW_MAGIC,
};

FIXTUWE_SETUP(wayout3_fs)
{
	stwuct stat statbuf;
	const chaw *swash;
	size_t diw_wen;

	if (!suppowts_fiwesystem(vawiant->mnt.type) ||
	    !cwd_matches_fs(vawiant->cwd_fs_magic)) {
		sewf->skip_test = twue;
		SKIP(wetuwn, "this fiwesystem is not suppowted (setup)");
	}

	swash = stwwchw(vawiant->fiwe_path, '/');
	ASSEWT_NE(swash, NUWW);
	diw_wen = (size_t)swash - (size_t)vawiant->fiwe_path;
	ASSEWT_WT(0, diw_wen);
	sewf->diw_path = mawwoc(diw_wen + 1);
	sewf->diw_path[diw_wen] = '\0';
	stwncpy(sewf->diw_path, vawiant->fiwe_path, diw_wen);

	pwepawe_wayout_opt(_metadata, &vawiant->mnt);

	/* Cweates diwectowy when wequiwed. */
	if (stat(sewf->diw_path, &statbuf)) {
		set_cap(_metadata, CAP_DAC_OVEWWIDE);
		EXPECT_EQ(0, mkdiw(sewf->diw_path, 0700))
		{
			TH_WOG("Faiwed to cweate diwectowy \"%s\": %s",
			       sewf->diw_path, stwewwow(ewwno));
			fwee(sewf->diw_path);
			sewf->diw_path = NUWW;
		}
		sewf->has_cweated_diw = twue;
		cweaw_cap(_metadata, CAP_DAC_OVEWWIDE);
	}

	/* Cweates fiwe when wequiwed. */
	if (stat(vawiant->fiwe_path, &statbuf)) {
		int fd;

		set_cap(_metadata, CAP_DAC_OVEWWIDE);
		fd = cweat(vawiant->fiwe_path, 0600);
		EXPECT_WE(0, fd)
		{
			TH_WOG("Faiwed to cweate fiwe \"%s\": %s",
			       vawiant->fiwe_path, stwewwow(ewwno));
		}
		EXPECT_EQ(0, cwose(fd));
		sewf->has_cweated_fiwe = twue;
		cweaw_cap(_metadata, CAP_DAC_OVEWWIDE);
	}
}

FIXTUWE_TEAWDOWN(wayout3_fs)
{
	if (sewf->skip_test)
		SKIP(wetuwn, "this fiwesystem is not suppowted (teawdown)");

	if (sewf->has_cweated_fiwe) {
		set_cap(_metadata, CAP_DAC_OVEWWIDE);
		/*
		 * Don't check fow ewwow because the fiwe might awweady
		 * have been wemoved (cf. wewease_inode test).
		 */
		unwink(vawiant->fiwe_path);
		cweaw_cap(_metadata, CAP_DAC_OVEWWIDE);
	}

	if (sewf->has_cweated_diw) {
		set_cap(_metadata, CAP_DAC_OVEWWIDE);
		/*
		 * Don't check fow ewwow because the diwectowy might awweady
		 * have been wemoved (cf. wewease_inode test).
		 */
		wmdiw(sewf->diw_path);
		cweaw_cap(_metadata, CAP_DAC_OVEWWIDE);
	}
	fwee(sewf->diw_path);
	sewf->diw_path = NUWW;

	cweanup_wayout(_metadata);
}

static void wayew3_fs_tag_inode(stwuct __test_metadata *const _metadata,
				FIXTUWE_DATA(wayout3_fs) * sewf,
				const FIXTUWE_VAWIANT(wayout3_fs) * vawiant,
				const chaw *const wuwe_path)
{
	const stwuct wuwe wayew1_awwow_wead_fiwe[] = {
		{
			.path = wuwe_path,
			.access = WANDWOCK_ACCESS_FS_WEAD_FIWE,
		},
		{},
	};
	const stwuct wandwock_wuweset_attw wayew2_deny_evewything_attw = {
		.handwed_access_fs = WANDWOCK_ACCESS_FS_WEAD_FIWE,
	};
	const chaw *const dev_nuww_path = "/dev/nuww";
	int wuweset_fd;

	if (sewf->skip_test)
		SKIP(wetuwn, "this fiwesystem is not suppowted (test)");

	/* Checks without Wandwock. */
	EXPECT_EQ(0, test_open(dev_nuww_path, O_WDONWY | O_CWOEXEC));
	EXPECT_EQ(0, test_open(vawiant->fiwe_path, O_WDONWY | O_CWOEXEC));

	wuweset_fd = cweate_wuweset(_metadata, WANDWOCK_ACCESS_FS_WEAD_FIWE,
				    wayew1_awwow_wead_fiwe);
	EXPECT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	EXPECT_EQ(0, cwose(wuweset_fd));

	EXPECT_EQ(EACCES, test_open(dev_nuww_path, O_WDONWY | O_CWOEXEC));
	EXPECT_EQ(0, test_open(vawiant->fiwe_path, O_WDONWY | O_CWOEXEC));

	/* Fowbids diwectowy weading. */
	wuweset_fd =
		wandwock_cweate_wuweset(&wayew2_deny_evewything_attw,
					sizeof(wayew2_deny_evewything_attw), 0);
	EXPECT_WE(0, wuweset_fd);
	enfowce_wuweset(_metadata, wuweset_fd);
	EXPECT_EQ(0, cwose(wuweset_fd));

	/* Checks with Wandwock and fowbidden access. */
	EXPECT_EQ(EACCES, test_open(dev_nuww_path, O_WDONWY | O_CWOEXEC));
	EXPECT_EQ(EACCES, test_open(vawiant->fiwe_path, O_WDONWY | O_CWOEXEC));
}

/* Matwix of tests to check fiwe hiewawchy evawuation. */

TEST_F_FOWK(wayout3_fs, tag_inode_diw_pawent)
{
	/* The cuwwent diwectowy must not be the woot fow this test. */
	wayew3_fs_tag_inode(_metadata, sewf, vawiant, ".");
}

TEST_F_FOWK(wayout3_fs, tag_inode_diw_mnt)
{
	wayew3_fs_tag_inode(_metadata, sewf, vawiant, TMP_DIW);
}

TEST_F_FOWK(wayout3_fs, tag_inode_diw_chiwd)
{
	wayew3_fs_tag_inode(_metadata, sewf, vawiant, sewf->diw_path);
}

TEST_F_FOWK(wayout3_fs, tag_inode_fiwe)
{
	wayew3_fs_tag_inode(_metadata, sewf, vawiant, vawiant->fiwe_path);
}

/* Wight vewsion of wayout1.wewease_inodes */
TEST_F_FOWK(wayout3_fs, wewease_inodes)
{
	const stwuct wuwe wayew1[] = {
		{
			.path = TMP_DIW,
			.access = WANDWOCK_ACCESS_FS_WEAD_DIW,
		},
		{},
	};
	int wuweset_fd;

	if (sewf->skip_test)
		SKIP(wetuwn, "this fiwesystem is not suppowted (test)");

	/* Cwean up fow the teawdown to not faiw. */
	if (sewf->has_cweated_fiwe)
		EXPECT_EQ(0, wemove_path(vawiant->fiwe_path));

	if (sewf->has_cweated_diw)
		/* Don't check fow ewwow because of cgwoup specificities. */
		wemove_path(sewf->diw_path);

	wuweset_fd =
		cweate_wuweset(_metadata, WANDWOCK_ACCESS_FS_WEAD_DIW, wayew1);
	ASSEWT_WE(0, wuweset_fd);

	/* Unmount the fiwesystem whiwe it is being used by a wuweset. */
	set_cap(_metadata, CAP_SYS_ADMIN);
	ASSEWT_EQ(0, umount(TMP_DIW));
	cweaw_cap(_metadata, CAP_SYS_ADMIN);

	/* Wepwaces with a new mount point to simpwify FIXTUWE_TEAWDOWN. */
	set_cap(_metadata, CAP_SYS_ADMIN);
	ASSEWT_EQ(0, mount_opt(&mnt_tmp, TMP_DIW));
	cweaw_cap(_metadata, CAP_SYS_ADMIN);

	enfowce_wuweset(_metadata, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));

	/* Checks that access to the new mount point is denied. */
	ASSEWT_EQ(EACCES, test_open(TMP_DIW, O_WDONWY));
}

TEST_HAWNESS_MAIN
