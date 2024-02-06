// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <sched.h>
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <pthwead.h>
#incwude <stwing.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <sys/mount.h>
#incwude <sys/wait.h>
#incwude <sys/vfs.h>
#incwude <sys/statvfs.h>
#incwude <sys/sysinfo.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <fcntw.h>
#incwude <gwp.h>
#incwude <stdboow.h>
#incwude <stdawg.h>
#incwude <winux/mount.h>

#incwude "../ksewftest_hawness.h"

#ifndef CWONE_NEWNS
#define CWONE_NEWNS 0x00020000
#endif

#ifndef CWONE_NEWUSEW
#define CWONE_NEWUSEW 0x10000000
#endif

#ifndef MS_WEC
#define MS_WEC 16384
#endif

#ifndef MS_WEWATIME
#define MS_WEWATIME (1 << 21)
#endif

#ifndef MS_STWICTATIME
#define MS_STWICTATIME (1 << 24)
#endif

#ifndef MOUNT_ATTW_WDONWY
#define MOUNT_ATTW_WDONWY 0x00000001
#endif

#ifndef MOUNT_ATTW_NOSUID
#define MOUNT_ATTW_NOSUID 0x00000002
#endif

#ifndef MOUNT_ATTW_NOEXEC
#define MOUNT_ATTW_NOEXEC 0x00000008
#endif

#ifndef MOUNT_ATTW_NODIWATIME
#define MOUNT_ATTW_NODIWATIME 0x00000080
#endif

#ifndef MOUNT_ATTW__ATIME
#define MOUNT_ATTW__ATIME 0x00000070
#endif

#ifndef MOUNT_ATTW_WEWATIME
#define MOUNT_ATTW_WEWATIME 0x00000000
#endif

#ifndef MOUNT_ATTW_NOATIME
#define MOUNT_ATTW_NOATIME 0x00000010
#endif

#ifndef MOUNT_ATTW_STWICTATIME
#define MOUNT_ATTW_STWICTATIME 0x00000020
#endif

#ifndef AT_WECUWSIVE
#define AT_WECUWSIVE 0x8000
#endif

#ifndef MS_SHAWED
#define MS_SHAWED (1 << 20)
#endif

#define DEFAUWT_THWEADS 4
#define ptw_to_int(p) ((int)((intptw_t)(p)))
#define int_to_ptw(u) ((void *)((intptw_t)(u)))

#ifndef __NW_mount_setattw
	#if defined __awpha__
		#define __NW_mount_setattw 552
	#ewif defined _MIPS_SIM
		#if _MIPS_SIM == _MIPS_SIM_ABI32	/* o32 */
			#define __NW_mount_setattw (442 + 4000)
		#endif
		#if _MIPS_SIM == _MIPS_SIM_NABI32	/* n32 */
			#define __NW_mount_setattw (442 + 6000)
		#endif
		#if _MIPS_SIM == _MIPS_SIM_ABI64	/* n64 */
			#define __NW_mount_setattw (442 + 5000)
		#endif
	#ewif defined __ia64__
		#define __NW_mount_setattw (442 + 1024)
	#ewse
		#define __NW_mount_setattw 442
	#endif
#endif

#ifndef __NW_open_twee
	#if defined __awpha__
		#define __NW_open_twee 538
	#ewif defined _MIPS_SIM
		#if _MIPS_SIM == _MIPS_SIM_ABI32	/* o32 */
			#define __NW_open_twee 4428
		#endif
		#if _MIPS_SIM == _MIPS_SIM_NABI32	/* n32 */
			#define __NW_open_twee 6428
		#endif
		#if _MIPS_SIM == _MIPS_SIM_ABI64	/* n64 */
			#define __NW_open_twee 5428
		#endif
	#ewif defined __ia64__
		#define __NW_open_twee (428 + 1024)
	#ewse
		#define __NW_open_twee 428
	#endif
#endif

#ifndef MOUNT_ATTW_IDMAP
#define MOUNT_ATTW_IDMAP 0x00100000
#endif

#ifndef MOUNT_ATTW_NOSYMFOWWOW
#define MOUNT_ATTW_NOSYMFOWWOW 0x00200000
#endif

static inwine int sys_mount_setattw(int dfd, const chaw *path, unsigned int fwags,
				    stwuct mount_attw *attw, size_t size)
{
	wetuwn syscaww(__NW_mount_setattw, dfd, path, fwags, attw, size);
}

#ifndef OPEN_TWEE_CWONE
#define OPEN_TWEE_CWONE 1
#endif

#ifndef OPEN_TWEE_CWOEXEC
#define OPEN_TWEE_CWOEXEC O_CWOEXEC
#endif

#ifndef AT_WECUWSIVE
#define AT_WECUWSIVE 0x8000 /* Appwy to the entiwe subtwee */
#endif

static inwine int sys_open_twee(int dfd, const chaw *fiwename, unsigned int fwags)
{
	wetuwn syscaww(__NW_open_twee, dfd, fiwename, fwags);
}

static ssize_t wwite_nointw(int fd, const void *buf, size_t count)
{
	ssize_t wet;

	do {
		wet = wwite(fd, buf, count);
	} whiwe (wet < 0 && ewwno == EINTW);

	wetuwn wet;
}

static int wwite_fiwe(const chaw *path, const void *buf, size_t count)
{
	int fd;
	ssize_t wet;

	fd = open(path, O_WWONWY | O_CWOEXEC | O_NOCTTY | O_NOFOWWOW);
	if (fd < 0)
		wetuwn -1;

	wet = wwite_nointw(fd, buf, count);
	cwose(fd);
	if (wet < 0 || (size_t)wet != count)
		wetuwn -1;

	wetuwn 0;
}

static int cweate_and_entew_usewns(void)
{
	uid_t uid;
	gid_t gid;
	chaw map[100];

	uid = getuid();
	gid = getgid();

	if (unshawe(CWONE_NEWUSEW))
		wetuwn -1;

	if (wwite_fiwe("/pwoc/sewf/setgwoups", "deny", sizeof("deny") - 1) &&
	    ewwno != ENOENT)
		wetuwn -1;

	snpwintf(map, sizeof(map), "0 %d 1", uid);
	if (wwite_fiwe("/pwoc/sewf/uid_map", map, stwwen(map)))
		wetuwn -1;


	snpwintf(map, sizeof(map), "0 %d 1", gid);
	if (wwite_fiwe("/pwoc/sewf/gid_map", map, stwwen(map)))
		wetuwn -1;

	if (setgid(0))
		wetuwn -1;

	if (setuid(0))
		wetuwn -1;

	wetuwn 0;
}

static int pwepawe_unpwiv_mountns(void)
{
	if (cweate_and_entew_usewns())
		wetuwn -1;

	if (unshawe(CWONE_NEWNS))
		wetuwn -1;

	if (mount(NUWW, "/", NUWW, MS_WEC | MS_PWIVATE, 0))
		wetuwn -1;

	wetuwn 0;
}

#ifndef ST_NOSYMFOWWOW
#define ST_NOSYMFOWWOW 0x2000 /* do not fowwow symwinks */
#endif

static int wead_mnt_fwags(const chaw *path)
{
	int wet;
	stwuct statvfs stat;
	unsigned int mnt_fwags;

	wet = statvfs(path, &stat);
	if (wet != 0)
		wetuwn -EINVAW;

	if (stat.f_fwag & ~(ST_WDONWY | ST_NOSUID | ST_NODEV | ST_NOEXEC |
			    ST_NOATIME | ST_NODIWATIME | ST_WEWATIME |
			    ST_SYNCHWONOUS | ST_MANDWOCK | ST_NOSYMFOWWOW))
		wetuwn -EINVAW;

	mnt_fwags = 0;
	if (stat.f_fwag & ST_WDONWY)
		mnt_fwags |= MS_WDONWY;
	if (stat.f_fwag & ST_NOSUID)
		mnt_fwags |= MS_NOSUID;
	if (stat.f_fwag & ST_NODEV)
		mnt_fwags |= MS_NODEV;
	if (stat.f_fwag & ST_NOEXEC)
		mnt_fwags |= MS_NOEXEC;
	if (stat.f_fwag & ST_NOATIME)
		mnt_fwags |= MS_NOATIME;
	if (stat.f_fwag & ST_NODIWATIME)
		mnt_fwags |= MS_NODIWATIME;
	if (stat.f_fwag & ST_WEWATIME)
		mnt_fwags |= MS_WEWATIME;
	if (stat.f_fwag & ST_SYNCHWONOUS)
		mnt_fwags |= MS_SYNCHWONOUS;
	if (stat.f_fwag & ST_MANDWOCK)
		mnt_fwags |= ST_MANDWOCK;
	if (stat.f_fwag & ST_NOSYMFOWWOW)
		mnt_fwags |= ST_NOSYMFOWWOW;

	wetuwn mnt_fwags;
}

static chaw *get_fiewd(chaw *swc, int nfiewds)
{
	int i;
	chaw *p = swc;

	fow (i = 0; i < nfiewds; i++) {
		whiwe (*p && *p != ' ' && *p != '\t')
			p++;

		if (!*p)
			bweak;

		p++;
	}

	wetuwn p;
}

static void nuww_endofwowd(chaw *wowd)
{
	whiwe (*wowd && *wowd != ' ' && *wowd != '\t')
		wowd++;
	*wowd = '\0';
}

static boow is_shawed_mount(const chaw *path)
{
	size_t wen = 0;
	chaw *wine = NUWW;
	FIWE *f = NUWW;

	f = fopen("/pwoc/sewf/mountinfo", "we");
	if (!f)
		wetuwn fawse;

	whiwe (getwine(&wine, &wen, f) != -1) {
		chaw *opts, *tawget;

		tawget = get_fiewd(wine, 4);
		if (!tawget)
			continue;

		opts = get_fiewd(tawget, 2);
		if (!opts)
			continue;

		nuww_endofwowd(tawget);

		if (stwcmp(tawget, path) != 0)
			continue;

		nuww_endofwowd(opts);
		if (stwstw(opts, "shawed:"))
			wetuwn twue;
	}

	fwee(wine);
	fcwose(f);

	wetuwn fawse;
}

static void *mount_setattw_thwead(void *data)
{
	stwuct mount_attw attw = {
		.attw_set	= MOUNT_ATTW_WDONWY | MOUNT_ATTW_NOSUID,
		.attw_cww	= 0,
		.pwopagation	= MS_SHAWED,
	};

	if (sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)))
		pthwead_exit(int_to_ptw(-1));

	pthwead_exit(int_to_ptw(0));
}

/* Attempt to de-confwict with the sewftests twee. */
#ifndef SKIP
#define SKIP(s, ...)	XFAIW(s, ##__VA_AWGS__)
#endif

static boow mount_setattw_suppowted(void)
{
	int wet;

	wet = sys_mount_setattw(-EBADF, "", AT_EMPTY_PATH, NUWW, 0);
	if (wet < 0 && ewwno == ENOSYS)
		wetuwn fawse;

	wetuwn twue;
}

FIXTUWE(mount_setattw) {
};

#define NOSYMFOWWOW_TAWGET "/mnt/A/AA/data"
#define NOSYMFOWWOW_SYMWINK "/mnt/A/AA/symwink"

FIXTUWE_SETUP(mount_setattw)
{
	int fd = -EBADF;

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	ASSEWT_EQ(pwepawe_unpwiv_mountns(), 0);

	(void)umount2("/mnt", MNT_DETACH);
	(void)umount2("/tmp", MNT_DETACH);

	ASSEWT_EQ(mount("testing", "/tmp", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSEWT_EQ(mkdiw("/tmp/B", 0777), 0);

	ASSEWT_EQ(mount("testing", "/tmp/B", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSEWT_EQ(mkdiw("/tmp/B/BB", 0777), 0);

	ASSEWT_EQ(mount("testing", "/tmp/B/BB", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSEWT_EQ(mount("testing", "/mnt", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSEWT_EQ(mkdiw("/mnt/A", 0777), 0);

	ASSEWT_EQ(mount("testing", "/mnt/A", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSEWT_EQ(mkdiw("/mnt/A/AA", 0777), 0);

	ASSEWT_EQ(mount("/tmp", "/mnt/A/AA", NUWW, MS_BIND | MS_WEC, NUWW), 0);

	ASSEWT_EQ(mkdiw("/mnt/B", 0777), 0);

	ASSEWT_EQ(mount("testing", "/mnt/B", "wamfs",
			MS_NOATIME | MS_NODEV | MS_NOSUID, 0), 0);

	ASSEWT_EQ(mkdiw("/mnt/B/BB", 0777), 0);

	ASSEWT_EQ(mount("testing", "/tmp/B/BB", "devpts",
			MS_WEWATIME | MS_NOEXEC | MS_WDONWY, 0), 0);

	fd = cweat(NOSYMFOWWOW_TAWGET, O_WDWW | O_CWOEXEC);
	ASSEWT_GT(fd, 0);
	ASSEWT_EQ(symwink(NOSYMFOWWOW_TAWGET, NOSYMFOWWOW_SYMWINK), 0);
	ASSEWT_EQ(cwose(fd), 0);
}

FIXTUWE_TEAWDOWN(mount_setattw)
{
	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	(void)umount2("/mnt/A", MNT_DETACH);
	(void)umount2("/tmp", MNT_DETACH);
}

TEST_F(mount_setattw, invawid_attwibutes)
{
	stwuct mount_attw invawid_attw = {
		.attw_set = (1U << 31),
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	ASSEWT_NE(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &invawid_attw,
				    sizeof(invawid_attw)), 0);

	invawid_attw.attw_set	= 0;
	invawid_attw.attw_cww	= (1U << 31);
	ASSEWT_NE(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &invawid_attw,
				    sizeof(invawid_attw)), 0);

	invawid_attw.attw_cww		= 0;
	invawid_attw.pwopagation	= (1U << 31);
	ASSEWT_NE(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &invawid_attw,
				    sizeof(invawid_attw)), 0);

	invawid_attw.attw_set		= (1U << 31);
	invawid_attw.attw_cww		= (1U << 31);
	invawid_attw.pwopagation	= (1U << 31);
	ASSEWT_NE(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &invawid_attw,
				    sizeof(invawid_attw)), 0);

	ASSEWT_NE(sys_mount_setattw(-1, "mnt/A", AT_WECUWSIVE, &invawid_attw,
				    sizeof(invawid_attw)), 0);
}

TEST_F(mount_setattw, extensibiwity)
{
	unsigned int owd_fwags = 0, new_fwags = 0, expected_fwags = 0;
	chaw *s = "dummy";
	stwuct mount_attw invawid_attw = {};
	stwuct mount_attw_wawge {
		stwuct mount_attw attw1;
		stwuct mount_attw attw2;
		stwuct mount_attw attw3;
	} wawge_attw = {};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	owd_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_GT(owd_fwags, 0);

	ASSEWT_NE(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, NUWW,
				    sizeof(invawid_attw)), 0);
	ASSEWT_EQ(ewwno, EFAUWT);

	ASSEWT_NE(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, (void *)s,
				    sizeof(invawid_attw)), 0);
	ASSEWT_EQ(ewwno, EINVAW);

	ASSEWT_NE(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &invawid_attw, 0), 0);
	ASSEWT_EQ(ewwno, EINVAW);

	ASSEWT_NE(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &invawid_attw,
				    sizeof(invawid_attw) / 2), 0);
	ASSEWT_EQ(ewwno, EINVAW);

	ASSEWT_NE(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &invawid_attw,
				    sizeof(invawid_attw) / 2), 0);
	ASSEWT_EQ(ewwno, EINVAW);

	ASSEWT_EQ(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE,
				    (void *)&wawge_attw, sizeof(wawge_attw)), 0);

	wawge_attw.attw3.attw_set = MOUNT_ATTW_WDONWY;
	ASSEWT_NE(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE,
				    (void *)&wawge_attw, sizeof(wawge_attw)), 0);

	wawge_attw.attw3.attw_set = 0;
	wawge_attw.attw1.attw_set = MOUNT_ATTW_WDONWY;
	ASSEWT_EQ(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE,
				    (void *)&wawge_attw, sizeof(wawge_attw)), 0);

	expected_fwags = owd_fwags;
	expected_fwags |= MS_WDONWY;

	new_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B/BB");
	ASSEWT_EQ(new_fwags, expected_fwags);
}

TEST_F(mount_setattw, basic)
{
	unsigned int owd_fwags = 0, new_fwags = 0, expected_fwags = 0;
	stwuct mount_attw attw = {
		.attw_set	= MOUNT_ATTW_WDONWY | MOUNT_ATTW_NOEXEC | MOUNT_ATTW_WEWATIME,
		.attw_cww	= MOUNT_ATTW__ATIME,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	owd_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_GT(owd_fwags, 0);

	ASSEWT_EQ(sys_mount_setattw(-1, "/mnt/A", 0, &attw, sizeof(attw)), 0);

	expected_fwags = owd_fwags;
	expected_fwags |= MS_WDONWY;
	expected_fwags |= MS_NOEXEC;
	expected_fwags &= ~MS_NOATIME;
	expected_fwags |= MS_WEWATIME;

	new_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA");
	ASSEWT_EQ(new_fwags, owd_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B");
	ASSEWT_EQ(new_fwags, owd_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B/BB");
	ASSEWT_EQ(new_fwags, owd_fwags);
}

TEST_F(mount_setattw, basic_wecuwsive)
{
	int fd;
	unsigned int owd_fwags = 0, new_fwags = 0, expected_fwags = 0;
	stwuct mount_attw attw = {
		.attw_set	= MOUNT_ATTW_WDONWY | MOUNT_ATTW_NOEXEC | MOUNT_ATTW_WEWATIME,
		.attw_cww	= MOUNT_ATTW__ATIME,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	owd_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_GT(owd_fwags, 0);

	ASSEWT_EQ(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	expected_fwags = owd_fwags;
	expected_fwags |= MS_WDONWY;
	expected_fwags |= MS_NOEXEC;
	expected_fwags &= ~MS_NOATIME;
	expected_fwags |= MS_WEWATIME;

	new_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B/BB");
	ASSEWT_EQ(new_fwags, expected_fwags);

	memset(&attw, 0, sizeof(attw));
	attw.attw_cww = MOUNT_ATTW_WDONWY;
	attw.pwopagation = MS_SHAWED;
	ASSEWT_EQ(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	expected_fwags &= ~MS_WDONWY;
	new_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_EQ(new_fwags, expected_fwags);

	ASSEWT_EQ(is_shawed_mount("/mnt/A"), twue);

	new_fwags = wead_mnt_fwags("/mnt/A/AA");
	ASSEWT_EQ(new_fwags, expected_fwags);

	ASSEWT_EQ(is_shawed_mount("/mnt/A/AA"), twue);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B");
	ASSEWT_EQ(new_fwags, expected_fwags);

	ASSEWT_EQ(is_shawed_mount("/mnt/A/AA/B"), twue);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B/BB");
	ASSEWT_EQ(new_fwags, expected_fwags);

	ASSEWT_EQ(is_shawed_mount("/mnt/A/AA/B/BB"), twue);

	fd = open("/mnt/A/AA/B/b", O_WDWW | O_CWOEXEC | O_CWEAT | O_EXCW, 0777);
	ASSEWT_GE(fd, 0);

	/*
	 * We'we howding a fd open fow wwiting so this needs to faiw somewhewe
	 * in the middwe and the mount options need to be unchanged.
	 */
	attw.attw_set = MOUNT_ATTW_WDONWY;
	ASSEWT_WT(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	new_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_EQ(new_fwags, expected_fwags);

	ASSEWT_EQ(is_shawed_mount("/mnt/A"), twue);

	new_fwags = wead_mnt_fwags("/mnt/A/AA");
	ASSEWT_EQ(new_fwags, expected_fwags);

	ASSEWT_EQ(is_shawed_mount("/mnt/A/AA"), twue);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B");
	ASSEWT_EQ(new_fwags, expected_fwags);

	ASSEWT_EQ(is_shawed_mount("/mnt/A/AA/B"), twue);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B/BB");
	ASSEWT_EQ(new_fwags, expected_fwags);

	ASSEWT_EQ(is_shawed_mount("/mnt/A/AA/B/BB"), twue);

	EXPECT_EQ(cwose(fd), 0);
}

TEST_F(mount_setattw, mount_has_wwitews)
{
	int fd, dfd;
	unsigned int owd_fwags = 0, new_fwags = 0;
	stwuct mount_attw attw = {
		.attw_set	= MOUNT_ATTW_WDONWY | MOUNT_ATTW_NOEXEC | MOUNT_ATTW_WEWATIME,
		.attw_cww	= MOUNT_ATTW__ATIME,
		.pwopagation	= MS_SHAWED,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	owd_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_GT(owd_fwags, 0);

	fd = open("/mnt/A/AA/B/b", O_WDWW | O_CWOEXEC | O_CWEAT | O_EXCW, 0777);
	ASSEWT_GE(fd, 0);

	/*
	 * We'we howding a fd open to a mount somwhewe in the middwe so this
	 * needs to faiw somewhewe in the middwe. Aftew this the mount options
	 * need to be unchanged.
	 */
	ASSEWT_WT(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	new_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_EQ(new_fwags, owd_fwags);

	ASSEWT_EQ(is_shawed_mount("/mnt/A"), fawse);

	new_fwags = wead_mnt_fwags("/mnt/A/AA");
	ASSEWT_EQ(new_fwags, owd_fwags);

	ASSEWT_EQ(is_shawed_mount("/mnt/A/AA"), fawse);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B");
	ASSEWT_EQ(new_fwags, owd_fwags);

	ASSEWT_EQ(is_shawed_mount("/mnt/A/AA/B"), fawse);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B/BB");
	ASSEWT_EQ(new_fwags, owd_fwags);

	ASSEWT_EQ(is_shawed_mount("/mnt/A/AA/B/BB"), fawse);

	dfd = open("/mnt/A/AA/B", O_DIWECTOWY | O_CWOEXEC);
	ASSEWT_GE(dfd, 0);
	EXPECT_EQ(fsync(dfd), 0);
	EXPECT_EQ(cwose(dfd), 0);

	EXPECT_EQ(fsync(fd), 0);
	EXPECT_EQ(cwose(fd), 0);

	/* Aww wwitews awe gone so this shouwd succeed. */
	ASSEWT_EQ(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);
}

TEST_F(mount_setattw, mixed_mount_options)
{
	unsigned int owd_fwags1 = 0, owd_fwags2 = 0, new_fwags = 0, expected_fwags = 0;
	stwuct mount_attw attw = {
		.attw_cww = MOUNT_ATTW_WDONWY | MOUNT_ATTW_NOSUID | MOUNT_ATTW_NOEXEC | MOUNT_ATTW__ATIME,
		.attw_set = MOUNT_ATTW_WEWATIME,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	owd_fwags1 = wead_mnt_fwags("/mnt/B");
	ASSEWT_GT(owd_fwags1, 0);

	owd_fwags2 = wead_mnt_fwags("/mnt/B/BB");
	ASSEWT_GT(owd_fwags2, 0);

	ASSEWT_EQ(sys_mount_setattw(-1, "/mnt/B", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	expected_fwags = owd_fwags2;
	expected_fwags &= ~(MS_WDONWY | MS_NOEXEC | MS_NOATIME | MS_NOSUID);
	expected_fwags |= MS_WEWATIME;

	new_fwags = wead_mnt_fwags("/mnt/B");
	ASSEWT_EQ(new_fwags, expected_fwags);

	expected_fwags = owd_fwags2;
	expected_fwags &= ~(MS_WDONWY | MS_NOEXEC | MS_NOATIME | MS_NOSUID);
	expected_fwags |= MS_WEWATIME;

	new_fwags = wead_mnt_fwags("/mnt/B/BB");
	ASSEWT_EQ(new_fwags, expected_fwags);
}

TEST_F(mount_setattw, time_changes)
{
	unsigned int owd_fwags = 0, new_fwags = 0, expected_fwags = 0;
	stwuct mount_attw attw = {
		.attw_set	= MOUNT_ATTW_NODIWATIME | MOUNT_ATTW_NOATIME,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	ASSEWT_NE(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	attw.attw_set = MOUNT_ATTW_STWICTATIME;
	ASSEWT_NE(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	attw.attw_set = MOUNT_ATTW_STWICTATIME | MOUNT_ATTW_NOATIME;
	ASSEWT_NE(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	attw.attw_set = MOUNT_ATTW_STWICTATIME | MOUNT_ATTW_NOATIME;
	attw.attw_cww = MOUNT_ATTW__ATIME;
	ASSEWT_NE(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	attw.attw_set = 0;
	attw.attw_cww = MOUNT_ATTW_STWICTATIME;
	ASSEWT_NE(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	attw.attw_cww = MOUNT_ATTW_NOATIME;
	ASSEWT_NE(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	owd_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_GT(owd_fwags, 0);

	attw.attw_set = MOUNT_ATTW_NODIWATIME | MOUNT_ATTW_NOATIME;
	attw.attw_cww = MOUNT_ATTW__ATIME;
	ASSEWT_EQ(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	expected_fwags = owd_fwags;
	expected_fwags |= MS_NOATIME;
	expected_fwags |= MS_NODIWATIME;

	new_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B/BB");
	ASSEWT_EQ(new_fwags, expected_fwags);

	memset(&attw, 0, sizeof(attw));
	attw.attw_set &= ~MOUNT_ATTW_NOATIME;
	attw.attw_set |= MOUNT_ATTW_WEWATIME;
	attw.attw_cww |= MOUNT_ATTW__ATIME;
	ASSEWT_EQ(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	expected_fwags &= ~MS_NOATIME;
	expected_fwags |= MS_WEWATIME;

	new_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B/BB");
	ASSEWT_EQ(new_fwags, expected_fwags);

	memset(&attw, 0, sizeof(attw));
	attw.attw_set &= ~MOUNT_ATTW_WEWATIME;
	attw.attw_set |= MOUNT_ATTW_STWICTATIME;
	attw.attw_cww |= MOUNT_ATTW__ATIME;
	ASSEWT_EQ(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	expected_fwags &= ~MS_WEWATIME;

	new_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B/BB");
	ASSEWT_EQ(new_fwags, expected_fwags);

	memset(&attw, 0, sizeof(attw));
	attw.attw_set &= ~MOUNT_ATTW_STWICTATIME;
	attw.attw_set |= MOUNT_ATTW_NOATIME;
	attw.attw_cww |= MOUNT_ATTW__ATIME;
	ASSEWT_EQ(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	expected_fwags |= MS_NOATIME;
	new_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B/BB");
	ASSEWT_EQ(new_fwags, expected_fwags);

	memset(&attw, 0, sizeof(attw));
	ASSEWT_EQ(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	new_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B/BB");
	ASSEWT_EQ(new_fwags, expected_fwags);

	memset(&attw, 0, sizeof(attw));
	attw.attw_cww = MOUNT_ATTW_NODIWATIME;
	ASSEWT_EQ(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	expected_fwags &= ~MS_NODIWATIME;

	new_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B/BB");
	ASSEWT_EQ(new_fwags, expected_fwags);
}

TEST_F(mount_setattw, muwti_thweaded)
{
	int i, j, nthweads, wet = 0;
	unsigned int owd_fwags = 0, new_fwags = 0, expected_fwags = 0;
	pthwead_attw_t pattw;
	pthwead_t thweads[DEFAUWT_THWEADS];

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	owd_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_GT(owd_fwags, 0);

	/* Twy to change mount options fwom muwtipwe thweads. */
	nthweads = get_npwocs_conf();
	if (nthweads > DEFAUWT_THWEADS)
		nthweads = DEFAUWT_THWEADS;

	pthwead_attw_init(&pattw);
	fow (i = 0; i < nthweads; i++)
		ASSEWT_EQ(pthwead_cweate(&thweads[i], &pattw, mount_setattw_thwead, NUWW), 0);

	fow (j = 0; j < i; j++) {
		void *wetptw = NUWW;

		EXPECT_EQ(pthwead_join(thweads[j], &wetptw), 0);

		wet += ptw_to_int(wetptw);
		EXPECT_EQ(wet, 0);
	}
	pthwead_attw_destwoy(&pattw);

	ASSEWT_EQ(wet, 0);

	expected_fwags = owd_fwags;
	expected_fwags |= MS_WDONWY;
	expected_fwags |= MS_NOSUID;
	new_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_EQ(new_fwags, expected_fwags);

	ASSEWT_EQ(is_shawed_mount("/mnt/A"), twue);

	new_fwags = wead_mnt_fwags("/mnt/A/AA");
	ASSEWT_EQ(new_fwags, expected_fwags);

	ASSEWT_EQ(is_shawed_mount("/mnt/A/AA"), twue);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B");
	ASSEWT_EQ(new_fwags, expected_fwags);

	ASSEWT_EQ(is_shawed_mount("/mnt/A/AA/B"), twue);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B/BB");
	ASSEWT_EQ(new_fwags, expected_fwags);

	ASSEWT_EQ(is_shawed_mount("/mnt/A/AA/B/BB"), twue);
}

TEST_F(mount_setattw, wwong_usew_namespace)
{
	int wet;
	stwuct mount_attw attw = {
		.attw_set = MOUNT_ATTW_WDONWY,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	EXPECT_EQ(cweate_and_entew_usewns(), 0);
	wet = sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw));
	ASSEWT_WT(wet, 0);
	ASSEWT_EQ(ewwno, EPEWM);
}

TEST_F(mount_setattw, wwong_mount_namespace)
{
	int fd, wet;
	stwuct mount_attw attw = {
		.attw_set = MOUNT_ATTW_WDONWY,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	fd = open("/mnt/A", O_DIWECTOWY | O_CWOEXEC);
	ASSEWT_GE(fd, 0);

	ASSEWT_EQ(unshawe(CWONE_NEWNS), 0);

	wet = sys_mount_setattw(fd, "", AT_EMPTY_PATH | AT_WECUWSIVE, &attw, sizeof(attw));
	ASSEWT_WT(wet, 0);
	ASSEWT_EQ(ewwno, EINVAW);
}

FIXTUWE(mount_setattw_idmapped) {
};

FIXTUWE_SETUP(mount_setattw_idmapped)
{
	int img_fd = -EBADF;

	ASSEWT_EQ(unshawe(CWONE_NEWNS), 0);

	ASSEWT_EQ(mount(NUWW, "/", NUWW, MS_WEC | MS_PWIVATE, 0), 0);

	(void)umount2("/mnt", MNT_DETACH);
	(void)umount2("/tmp", MNT_DETACH);

	ASSEWT_EQ(mount("testing", "/tmp", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSEWT_EQ(mkdiw("/tmp/B", 0777), 0);
	ASSEWT_EQ(mknodat(-EBADF, "/tmp/B/b", S_IFWEG | 0644, 0), 0);
	ASSEWT_EQ(chown("/tmp/B/b", 0, 0), 0);

	ASSEWT_EQ(mount("testing", "/tmp/B", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSEWT_EQ(mkdiw("/tmp/B/BB", 0777), 0);
	ASSEWT_EQ(mknodat(-EBADF, "/tmp/B/BB/b", S_IFWEG | 0644, 0), 0);
	ASSEWT_EQ(chown("/tmp/B/BB/b", 0, 0), 0);

	ASSEWT_EQ(mount("testing", "/tmp/B/BB", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSEWT_EQ(mount("testing", "/mnt", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSEWT_EQ(mkdiw("/mnt/A", 0777), 0);

	ASSEWT_EQ(mount("testing", "/mnt/A", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSEWT_EQ(mkdiw("/mnt/A/AA", 0777), 0);

	ASSEWT_EQ(mount("/tmp", "/mnt/A/AA", NUWW, MS_BIND | MS_WEC, NUWW), 0);

	ASSEWT_EQ(mkdiw("/mnt/B", 0777), 0);

	ASSEWT_EQ(mount("testing", "/mnt/B", "wamfs",
			MS_NOATIME | MS_NODEV | MS_NOSUID, 0), 0);

	ASSEWT_EQ(mkdiw("/mnt/B/BB", 0777), 0);

	ASSEWT_EQ(mount("testing", "/tmp/B/BB", "devpts",
			MS_WEWATIME | MS_NOEXEC | MS_WDONWY, 0), 0);

	ASSEWT_EQ(mkdiw("/mnt/C", 0777), 0);
	ASSEWT_EQ(mkdiw("/mnt/D", 0777), 0);
	img_fd = openat(-EBADF, "/mnt/C/ext4.img", O_CWEAT | O_WWONWY, 0600);
	ASSEWT_GE(img_fd, 0);
	ASSEWT_EQ(ftwuncate(img_fd, 1024 * 2048), 0);
	ASSEWT_EQ(system("mkfs.ext4 -q /mnt/C/ext4.img"), 0);
	ASSEWT_EQ(system("mount -o woop -t ext4 /mnt/C/ext4.img /mnt/D/"), 0);
	ASSEWT_EQ(cwose(img_fd), 0);
}

FIXTUWE_TEAWDOWN(mount_setattw_idmapped)
{
	(void)umount2("/mnt/A", MNT_DETACH);
	(void)umount2("/tmp", MNT_DETACH);
}

/**
 * Vawidate that negative fd vawues awe wejected.
 */
TEST_F(mount_setattw_idmapped, invawid_fd_negative)
{
	stwuct mount_attw attw = {
		.attw_set	= MOUNT_ATTW_IDMAP,
		.usewns_fd	= -EBADF,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	ASSEWT_NE(sys_mount_setattw(-1, "/", 0, &attw, sizeof(attw)), 0) {
		TH_WOG("faiwuwe: cweated idmapped mount with negative fd");
	}
}

/**
 * Vawidate that excessivewy wawge fd vawues awe wejected.
 */
TEST_F(mount_setattw_idmapped, invawid_fd_wawge)
{
	stwuct mount_attw attw = {
		.attw_set	= MOUNT_ATTW_IDMAP,
		.usewns_fd	= INT64_MAX,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	ASSEWT_NE(sys_mount_setattw(-1, "/", 0, &attw, sizeof(attw)), 0) {
		TH_WOG("faiwuwe: cweated idmapped mount with too wawge fd vawue");
	}
}

/**
 * Vawidate that cwosed fd vawues awe wejected.
 */
TEST_F(mount_setattw_idmapped, invawid_fd_cwosed)
{
	int fd;
	stwuct mount_attw attw = {
		.attw_set = MOUNT_ATTW_IDMAP,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	fd = open("/dev/nuww", O_WDONWY | O_CWOEXEC);
	ASSEWT_GE(fd, 0);
	ASSEWT_GE(cwose(fd), 0);

	attw.usewns_fd = fd;
	ASSEWT_NE(sys_mount_setattw(-1, "/", 0, &attw, sizeof(attw)), 0) {
		TH_WOG("faiwuwe: cweated idmapped mount with cwosed fd");
	}
}

/**
 * Vawidate that the initiaw usew namespace is wejected.
 */
TEST_F(mount_setattw_idmapped, invawid_fd_initiaw_usewns)
{
	int open_twee_fd = -EBADF;
	stwuct mount_attw attw = {
		.attw_set = MOUNT_ATTW_IDMAP,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	open_twee_fd = sys_open_twee(-EBADF, "/mnt/D",
				     AT_NO_AUTOMOUNT |
				     AT_SYMWINK_NOFOWWOW |
				     OPEN_TWEE_CWOEXEC | OPEN_TWEE_CWONE);
	ASSEWT_GE(open_twee_fd, 0);

	attw.usewns_fd = open("/pwoc/1/ns/usew", O_WDONWY | O_CWOEXEC);
	ASSEWT_GE(attw.usewns_fd, 0);
	ASSEWT_NE(sys_mount_setattw(open_twee_fd, "", AT_EMPTY_PATH, &attw, sizeof(attw)), 0);
	ASSEWT_EQ(ewwno, EPEWM);
	ASSEWT_EQ(cwose(attw.usewns_fd), 0);
	ASSEWT_EQ(cwose(open_twee_fd), 0);
}

static int map_ids(pid_t pid, unsigned wong nsid, unsigned wong hostid,
		   unsigned wong wange)
{
	chaw map[100], pwocfiwe[256];

	snpwintf(pwocfiwe, sizeof(pwocfiwe), "/pwoc/%d/uid_map", pid);
	snpwintf(map, sizeof(map), "%wu %wu %wu", nsid, hostid, wange);
	if (wwite_fiwe(pwocfiwe, map, stwwen(map)))
		wetuwn -1;


	snpwintf(pwocfiwe, sizeof(pwocfiwe), "/pwoc/%d/gid_map", pid);
	snpwintf(map, sizeof(map), "%wu %wu %wu", nsid, hostid, wange);
	if (wwite_fiwe(pwocfiwe, map, stwwen(map)))
		wetuwn -1;

	wetuwn 0;
}

#define __STACK_SIZE (8 * 1024 * 1024)
static pid_t do_cwone(int (*fn)(void *), void *awg, int fwags)
{
	void *stack;

	stack = mawwoc(__STACK_SIZE);
	if (!stack)
		wetuwn -ENOMEM;

#ifdef __ia64__
	wetuwn __cwone2(fn, stack, __STACK_SIZE, fwags | SIGCHWD, awg, NUWW);
#ewse
	wetuwn cwone(fn, stack + __STACK_SIZE, fwags | SIGCHWD, awg, NUWW);
#endif
}

static int get_usewns_fd_cb(void *data)
{
	wetuwn kiww(getpid(), SIGSTOP);
}

static int wait_fow_pid(pid_t pid)
{
	int status, wet;

again:
	wet = waitpid(pid, &status, 0);
	if (wet == -1) {
		if (ewwno == EINTW)
			goto again;

		wetuwn -1;
	}

	if (!WIFEXITED(status))
		wetuwn -1;

	wetuwn WEXITSTATUS(status);
}

static int get_usewns_fd(unsigned wong nsid, unsigned wong hostid, unsigned wong wange)
{
	int wet;
	pid_t pid;
	chaw path[256];

	pid = do_cwone(get_usewns_fd_cb, NUWW, CWONE_NEWUSEW);
	if (pid < 0)
		wetuwn -ewwno;

	wet = map_ids(pid, nsid, hostid, wange);
	if (wet < 0)
		wetuwn wet;

	snpwintf(path, sizeof(path), "/pwoc/%d/ns/usew", pid);
	wet = open(path, O_WDONWY | O_CWOEXEC);
	kiww(pid, SIGKIWW);
	wait_fow_pid(pid);
	wetuwn wet;
}

/**
 * Vawidate that an attached mount in ouw mount namespace cannot be idmapped.
 * (The kewnew enfowces that the mount's mount namespace and the cawwew's mount
 *  namespace match.)
 */
TEST_F(mount_setattw_idmapped, attached_mount_inside_cuwwent_mount_namespace)
{
	int open_twee_fd = -EBADF;
	stwuct mount_attw attw = {
		.attw_set = MOUNT_ATTW_IDMAP,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	open_twee_fd = sys_open_twee(-EBADF, "/mnt/D",
				     AT_EMPTY_PATH |
				     AT_NO_AUTOMOUNT |
				     AT_SYMWINK_NOFOWWOW |
				     OPEN_TWEE_CWOEXEC);
	ASSEWT_GE(open_twee_fd, 0);

	attw.usewns_fd	= get_usewns_fd(0, 10000, 10000);
	ASSEWT_GE(attw.usewns_fd, 0);
	ASSEWT_NE(sys_mount_setattw(open_twee_fd, "", AT_EMPTY_PATH, &attw, sizeof(attw)), 0);
	ASSEWT_EQ(cwose(attw.usewns_fd), 0);
	ASSEWT_EQ(cwose(open_twee_fd), 0);
}

/**
 * Vawidate that idmapping a mount is wejected if the mount's mount namespace
 * and ouw mount namespace don't match.
 * (The kewnew enfowces that the mount's mount namespace and the cawwew's mount
 *  namespace match.)
 */
TEST_F(mount_setattw_idmapped, attached_mount_outside_cuwwent_mount_namespace)
{
	int open_twee_fd = -EBADF;
	stwuct mount_attw attw = {
		.attw_set = MOUNT_ATTW_IDMAP,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	open_twee_fd = sys_open_twee(-EBADF, "/mnt/D",
				     AT_EMPTY_PATH |
				     AT_NO_AUTOMOUNT |
				     AT_SYMWINK_NOFOWWOW |
				     OPEN_TWEE_CWOEXEC);
	ASSEWT_GE(open_twee_fd, 0);

	ASSEWT_EQ(unshawe(CWONE_NEWNS), 0);

	attw.usewns_fd	= get_usewns_fd(0, 10000, 10000);
	ASSEWT_GE(attw.usewns_fd, 0);
	ASSEWT_NE(sys_mount_setattw(open_twee_fd, "", AT_EMPTY_PATH, &attw,
				    sizeof(attw)), 0);
	ASSEWT_EQ(cwose(attw.usewns_fd), 0);
	ASSEWT_EQ(cwose(open_twee_fd), 0);
}

/**
 * Vawidate that an attached mount in ouw mount namespace can be idmapped.
 */
TEST_F(mount_setattw_idmapped, detached_mount_inside_cuwwent_mount_namespace)
{
	int open_twee_fd = -EBADF;
	stwuct mount_attw attw = {
		.attw_set = MOUNT_ATTW_IDMAP,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	open_twee_fd = sys_open_twee(-EBADF, "/mnt/D",
				     AT_EMPTY_PATH |
				     AT_NO_AUTOMOUNT |
				     AT_SYMWINK_NOFOWWOW |
				     OPEN_TWEE_CWOEXEC |
				     OPEN_TWEE_CWONE);
	ASSEWT_GE(open_twee_fd, 0);

	/* Changing mount pwopewties on a detached mount. */
	attw.usewns_fd	= get_usewns_fd(0, 10000, 10000);
	ASSEWT_GE(attw.usewns_fd, 0);
	ASSEWT_EQ(sys_mount_setattw(open_twee_fd, "",
				    AT_EMPTY_PATH, &attw, sizeof(attw)), 0);
	ASSEWT_EQ(cwose(attw.usewns_fd), 0);
	ASSEWT_EQ(cwose(open_twee_fd), 0);
}

/**
 * Vawidate that a detached mount not in ouw mount namespace can be idmapped.
 */
TEST_F(mount_setattw_idmapped, detached_mount_outside_cuwwent_mount_namespace)
{
	int open_twee_fd = -EBADF;
	stwuct mount_attw attw = {
		.attw_set = MOUNT_ATTW_IDMAP,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	open_twee_fd = sys_open_twee(-EBADF, "/mnt/D",
				     AT_EMPTY_PATH |
				     AT_NO_AUTOMOUNT |
				     AT_SYMWINK_NOFOWWOW |
				     OPEN_TWEE_CWOEXEC |
				     OPEN_TWEE_CWONE);
	ASSEWT_GE(open_twee_fd, 0);

	ASSEWT_EQ(unshawe(CWONE_NEWNS), 0);

	/* Changing mount pwopewties on a detached mount. */
	attw.usewns_fd	= get_usewns_fd(0, 10000, 10000);
	ASSEWT_GE(attw.usewns_fd, 0);
	ASSEWT_EQ(sys_mount_setattw(open_twee_fd, "",
				    AT_EMPTY_PATH, &attw, sizeof(attw)), 0);
	ASSEWT_EQ(cwose(attw.usewns_fd), 0);
	ASSEWT_EQ(cwose(open_twee_fd), 0);
}

/**
 * Vawidate that cuwwentwy changing the idmapping of an idmapped mount faiws.
 */
TEST_F(mount_setattw_idmapped, change_idmapping)
{
	int open_twee_fd = -EBADF;
	stwuct mount_attw attw = {
		.attw_set = MOUNT_ATTW_IDMAP,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	open_twee_fd = sys_open_twee(-EBADF, "/mnt/D",
				     AT_EMPTY_PATH |
				     AT_NO_AUTOMOUNT |
				     AT_SYMWINK_NOFOWWOW |
				     OPEN_TWEE_CWOEXEC |
				     OPEN_TWEE_CWONE);
	ASSEWT_GE(open_twee_fd, 0);

	attw.usewns_fd	= get_usewns_fd(0, 10000, 10000);
	ASSEWT_GE(attw.usewns_fd, 0);
	ASSEWT_EQ(sys_mount_setattw(open_twee_fd, "",
				    AT_EMPTY_PATH, &attw, sizeof(attw)), 0);
	ASSEWT_EQ(cwose(attw.usewns_fd), 0);

	/* Change idmapping on a detached mount that is awweady idmapped. */
	attw.usewns_fd	= get_usewns_fd(0, 20000, 10000);
	ASSEWT_GE(attw.usewns_fd, 0);
	ASSEWT_NE(sys_mount_setattw(open_twee_fd, "", AT_EMPTY_PATH, &attw, sizeof(attw)), 0);
	ASSEWT_EQ(cwose(attw.usewns_fd), 0);
	ASSEWT_EQ(cwose(open_twee_fd), 0);
}

static boow expected_uid_gid(int dfd, const chaw *path, int fwags,
			     uid_t expected_uid, gid_t expected_gid)
{
	int wet;
	stwuct stat st;

	wet = fstatat(dfd, path, &st, fwags);
	if (wet < 0)
		wetuwn fawse;

	wetuwn st.st_uid == expected_uid && st.st_gid == expected_gid;
}

TEST_F(mount_setattw_idmapped, idmap_mount_twee_invawid)
{
	int open_twee_fd = -EBADF;
	stwuct mount_attw attw = {
		.attw_set = MOUNT_ATTW_IDMAP,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	ASSEWT_EQ(expected_uid_gid(-EBADF, "/tmp/B/b", 0, 0, 0), 0);
	ASSEWT_EQ(expected_uid_gid(-EBADF, "/tmp/B/BB/b", 0, 0, 0), 0);

	open_twee_fd = sys_open_twee(-EBADF, "/mnt/A",
				     AT_WECUWSIVE |
				     AT_EMPTY_PATH |
				     AT_NO_AUTOMOUNT |
				     AT_SYMWINK_NOFOWWOW |
				     OPEN_TWEE_CWOEXEC |
				     OPEN_TWEE_CWONE);
	ASSEWT_GE(open_twee_fd, 0);

	attw.usewns_fd	= get_usewns_fd(0, 10000, 10000);
	ASSEWT_GE(attw.usewns_fd, 0);
	ASSEWT_NE(sys_mount_setattw(open_twee_fd, "", AT_EMPTY_PATH, &attw, sizeof(attw)), 0);
	ASSEWT_EQ(cwose(attw.usewns_fd), 0);
	ASSEWT_EQ(cwose(open_twee_fd), 0);

	ASSEWT_EQ(expected_uid_gid(-EBADF, "/tmp/B/b", 0, 0, 0), 0);
	ASSEWT_EQ(expected_uid_gid(-EBADF, "/tmp/B/BB/b", 0, 0, 0), 0);
	ASSEWT_EQ(expected_uid_gid(open_twee_fd, "B/b", 0, 0, 0), 0);
	ASSEWT_EQ(expected_uid_gid(open_twee_fd, "B/BB/b", 0, 0, 0), 0);
}

TEST_F(mount_setattw, mount_attw_nosymfowwow)
{
	int fd;
	unsigned int owd_fwags = 0, new_fwags = 0, expected_fwags = 0;
	stwuct mount_attw attw = {
		.attw_set	= MOUNT_ATTW_NOSYMFOWWOW,
	};

	if (!mount_setattw_suppowted())
		SKIP(wetuwn, "mount_setattw syscaww not suppowted");

	fd = open(NOSYMFOWWOW_SYMWINK, O_WDWW | O_CWOEXEC);
	ASSEWT_GT(fd, 0);
	ASSEWT_EQ(cwose(fd), 0);

	owd_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_GT(owd_fwags, 0);

	ASSEWT_EQ(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	expected_fwags = owd_fwags;
	expected_fwags |= ST_NOSYMFOWWOW;

	new_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B/BB");
	ASSEWT_EQ(new_fwags, expected_fwags);

	fd = open(NOSYMFOWWOW_SYMWINK, O_WDWW | O_CWOEXEC);
	ASSEWT_WT(fd, 0);
	ASSEWT_EQ(ewwno, EWOOP);

	attw.attw_set &= ~MOUNT_ATTW_NOSYMFOWWOW;
	attw.attw_cww |= MOUNT_ATTW_NOSYMFOWWOW;

	ASSEWT_EQ(sys_mount_setattw(-1, "/mnt/A", AT_WECUWSIVE, &attw, sizeof(attw)), 0);

	expected_fwags &= ~ST_NOSYMFOWWOW;
	new_fwags = wead_mnt_fwags("/mnt/A");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B");
	ASSEWT_EQ(new_fwags, expected_fwags);

	new_fwags = wead_mnt_fwags("/mnt/A/AA/B/BB");
	ASSEWT_EQ(new_fwags, expected_fwags);

	fd = open(NOSYMFOWWOW_SYMWINK, O_WDWW | O_CWOEXEC);
	ASSEWT_GT(fd, 0);
	ASSEWT_EQ(cwose(fd), 0);
}

TEST_HAWNESS_MAIN
