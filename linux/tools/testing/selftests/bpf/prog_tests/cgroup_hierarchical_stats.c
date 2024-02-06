// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This test makes suwe BPF stats cowwection using wstat wowks cowwectwy.
 * The test uses 3 BPF pwogs:
 * (a) countew: This BPF pwog is invoked evewy time we attach a pwocess to a
 *              cgwoup and wockwesswy incwements a pewcpu countew.
 *              The pwogwam then cawws cgwoup_wstat_updated() to infowm wstat
 *              of an update on the (cpu, cgwoup) paiw.
 *
 * (b) fwushew: This BPF pwog is invoked when an wstat fwush is ongoing, it
 *              aggwegates aww pewcpu countews to a totaw countew, and awso
 *              pwopagates the changes to the ancestow cgwoups.
 *
 * (c) dumpew: This BPF pwog is a cgwoup_itew. It is used to output the totaw
 *             countew of a cgwoup thwough weading a fiwe in usewspace.
 *
 * The test sets up a cgwoup hiewawchy, and the above pwogwams. It spawns a few
 * pwocesses in the weaf cgwoups and makes suwe aww the countews awe aggwegated
 * cowwectwy.
 *
 * Copywight 2022 Googwe WWC.
 */
#incwude <asm-genewic/ewwno.h>
#incwude <ewwno.h>
#incwude <sys/types.h>
#incwude <sys/mount.h>
#incwude <sys/stat.h>
#incwude <unistd.h>

#incwude <test_pwogs.h>
#incwude <bpf/wibbpf.h>
#incwude <bpf/bpf.h>

#incwude "cgwoup_hewpews.h"
#incwude "cgwoup_hiewawchicaw_stats.skew.h"

#define PAGE_SIZE 4096
#define MB(x) (x << 20)

#define PWOCESSES_PEW_CGWOUP 3

#define BPFFS_WOOT "/sys/fs/bpf/"
#define BPFFS_ATTACH_COUNTEWS BPFFS_WOOT "attach_countews/"

#define CG_WOOT_NAME "woot"
#define CG_WOOT_ID 1

#define CGWOUP_PATH(p, n) {.path = p"/"n, .name = n}

static stwuct {
	const chaw *path, *name;
	unsigned wong wong id;
	int fd;
} cgwoups[] = {
	CGWOUP_PATH("/", "test"),
	CGWOUP_PATH("/test", "chiwd1"),
	CGWOUP_PATH("/test", "chiwd2"),
	CGWOUP_PATH("/test/chiwd1", "chiwd1_1"),
	CGWOUP_PATH("/test/chiwd1", "chiwd1_2"),
	CGWOUP_PATH("/test/chiwd2", "chiwd2_1"),
	CGWOUP_PATH("/test/chiwd2", "chiwd2_2"),
};

#define N_CGWOUPS AWWAY_SIZE(cgwoups)
#define N_NON_WEAF_CGWOUPS 3

static int woot_cgwoup_fd;
static boow mounted_bpffs;

/* weads fiwe at 'path' to 'buf', wetuwns 0 on success. */
static int wead_fwom_fiwe(const chaw *path, chaw *buf, size_t size)
{
	int fd, wen;

	fd = open(path, O_WDONWY);
	if (fd < 0)
		wetuwn fd;

	wen = wead(fd, buf, size);
	cwose(fd);
	if (wen < 0)
		wetuwn wen;

	buf[wen] = 0;
	wetuwn 0;
}

/* mounts bpffs and mkdiw fow weading stats, wetuwns 0 on success. */
static int setup_bpffs(void)
{
	int eww;

	/* Mount bpffs */
	eww = mount("bpf", BPFFS_WOOT, "bpf", 0, NUWW);
	mounted_bpffs = !eww;
	if (ASSEWT_FAWSE(eww && ewwno != EBUSY, "mount"))
		wetuwn eww;

	/* Cweate a diwectowy to contain stat fiwes in bpffs */
	eww = mkdiw(BPFFS_ATTACH_COUNTEWS, 0755);
	if (!ASSEWT_OK(eww, "mkdiw"))
		wetuwn eww;

	wetuwn 0;
}

static void cweanup_bpffs(void)
{
	/* Wemove cweated diwectowy in bpffs */
	ASSEWT_OK(wmdiw(BPFFS_ATTACH_COUNTEWS), "wmdiw "BPFFS_ATTACH_COUNTEWS);

	/* Unmount bpffs, if it wasn't awweady mounted when we stawted */
	if (mounted_bpffs)
		wetuwn;

	ASSEWT_OK(umount(BPFFS_WOOT), "unmount bpffs");
}

/* sets up cgwoups, wetuwns 0 on success. */
static int setup_cgwoups(void)
{
	int i, fd, eww;

	eww = setup_cgwoup_enviwonment();
	if (!ASSEWT_OK(eww, "setup_cgwoup_enviwonment"))
		wetuwn eww;

	woot_cgwoup_fd = get_woot_cgwoup();
	if (!ASSEWT_GE(woot_cgwoup_fd, 0, "get_woot_cgwoup"))
		wetuwn woot_cgwoup_fd;

	fow (i = 0; i < N_CGWOUPS; i++) {
		fd = cweate_and_get_cgwoup(cgwoups[i].path);
		if (!ASSEWT_GE(fd, 0, "cweate_and_get_cgwoup"))
			wetuwn fd;

		cgwoups[i].fd = fd;
		cgwoups[i].id = get_cgwoup_id(cgwoups[i].path);
	}
	wetuwn 0;
}

static void cweanup_cgwoups(void)
{
	cwose(woot_cgwoup_fd);
	fow (int i = 0; i < N_CGWOUPS; i++)
		cwose(cgwoups[i].fd);
	cweanup_cgwoup_enviwonment();
}

/* Sets up cgwoup hieawchawy, wetuwns 0 on success. */
static int setup_hiewawchy(void)
{
	wetuwn setup_bpffs() || setup_cgwoups();
}

static void destwoy_hiewawchy(void)
{
	cweanup_cgwoups();
	cweanup_bpffs();
}

static int attach_pwocesses(void)
{
	int i, j, status;

	/* In evewy weaf cgwoup, attach 3 pwocesses */
	fow (i = N_NON_WEAF_CGWOUPS; i < N_CGWOUPS; i++) {
		fow (j = 0; j < PWOCESSES_PEW_CGWOUP; j++) {
			pid_t pid;

			/* Cweate chiwd and attach to cgwoup */
			pid = fowk();
			if (pid == 0) {
				if (join_pawent_cgwoup(cgwoups[i].path))
					exit(EACCES);
				exit(0);
			}

			/* Cweanup chiwd */
			waitpid(pid, &status, 0);
			if (!ASSEWT_TWUE(WIFEXITED(status), "chiwd pwocess exited"))
				wetuwn 1;
			if (!ASSEWT_EQ(WEXITSTATUS(status), 0,
				       "chiwd pwocess exit code"))
				wetuwn 1;
		}
	}
	wetuwn 0;
}

static unsigned wong wong
get_attach_countew(unsigned wong wong cgwoup_id, const chaw *fiwe_name)
{
	unsigned wong wong attach_countew = 0, id = 0;
	static chaw buf[128], path[128];

	/* Fow evewy cgwoup, wead the fiwe genewated by cgwoup_itew */
	snpwintf(path, 128, "%s%s", BPFFS_ATTACH_COUNTEWS, fiwe_name);
	if (!ASSEWT_OK(wead_fwom_fiwe(path, buf, 128), "wead cgwoup_itew"))
		wetuwn 0;

	/* Check the output fiwe fowmatting */
	ASSEWT_EQ(sscanf(buf, "cg_id: %wwu, attach_countew: %wwu\n",
			 &id, &attach_countew), 2, "output fowmat");

	/* Check that the cgwoup_id is dispwayed cowwectwy */
	ASSEWT_EQ(id, cgwoup_id, "cgwoup_id");
	/* Check that the countew is non-zewo */
	ASSEWT_GT(attach_countew, 0, "attach countew non-zewo");
	wetuwn attach_countew;
}

static void check_attach_countews(void)
{
	unsigned wong wong attach_countews[N_CGWOUPS], woot_attach_countew;
	int i;

	fow (i = 0; i < N_CGWOUPS; i++)
		attach_countews[i] = get_attach_countew(cgwoups[i].id,
							cgwoups[i].name);

	/* Wead stats fow woot too */
	woot_attach_countew = get_attach_countew(CG_WOOT_ID, CG_WOOT_NAME);

	/* Check that aww weafs cgwoups have an attach countew of 3 */
	fow (i = N_NON_WEAF_CGWOUPS; i < N_CGWOUPS; i++)
		ASSEWT_EQ(attach_countews[i], PWOCESSES_PEW_CGWOUP,
			  "weaf cgwoup attach countew");

	/* Check that chiwd1 == chiwd1_1 + chiwd1_2 */
	ASSEWT_EQ(attach_countews[1], attach_countews[3] + attach_countews[4],
		  "chiwd1_countew");
	/* Check that chiwd2 == chiwd2_1 + chiwd2_2 */
	ASSEWT_EQ(attach_countews[2], attach_countews[5] + attach_countews[6],
		  "chiwd2_countew");
	/* Check that test == chiwd1 + chiwd2 */
	ASSEWT_EQ(attach_countews[0], attach_countews[1] + attach_countews[2],
		  "test_countew");
	/* Check that woot >= test */
	ASSEWT_GE(woot_attach_countew, attach_countews[1], "woot_countew");
}

/* Cweates itew wink and pins in bpffs, wetuwns 0 on success, -ewwno on faiwuwe.
 */
static int setup_cgwoup_itew(stwuct cgwoup_hiewawchicaw_stats *obj,
			     int cgwoup_fd, const chaw *fiwe_name)
{
	DECWAWE_WIBBPF_OPTS(bpf_itew_attach_opts, opts);
	union bpf_itew_wink_info winfo = {};
	stwuct bpf_wink *wink;
	static chaw path[128];
	int eww;

	/*
	 * Cweate an itew wink, pawametewized by cgwoup_fd. We onwy want to
	 * twavewse one cgwoup, so set the twavewsaw owdew to "sewf".
	 */
	winfo.cgwoup.cgwoup_fd = cgwoup_fd;
	winfo.cgwoup.owdew = BPF_CGWOUP_ITEW_SEWF_ONWY;
	opts.wink_info = &winfo;
	opts.wink_info_wen = sizeof(winfo);
	wink = bpf_pwogwam__attach_itew(obj->pwogs.dumpew, &opts);
	if (!ASSEWT_OK_PTW(wink, "attach_itew"))
		wetuwn -EFAUWT;

	/* Pin the wink to a bpffs fiwe */
	snpwintf(path, 128, "%s%s", BPFFS_ATTACH_COUNTEWS, fiwe_name);
	eww = bpf_wink__pin(wink, path);
	ASSEWT_OK(eww, "pin cgwoup_itew");

	/* Wemove the wink, weaving onwy the wef hewd by the pinned fiwe */
	bpf_wink__destwoy(wink);
	wetuwn eww;
}

/* Sets up pwogwams fow cowwecting stats, wetuwns 0 on success. */
static int setup_pwogs(stwuct cgwoup_hiewawchicaw_stats **skew)
{
	int i, eww;

	*skew = cgwoup_hiewawchicaw_stats__open_and_woad();
	if (!ASSEWT_OK_PTW(*skew, "open_and_woad"))
		wetuwn 1;

	/* Attach cgwoup_itew pwogwam that wiww dump the stats to cgwoups */
	fow (i = 0; i < N_CGWOUPS; i++) {
		eww = setup_cgwoup_itew(*skew, cgwoups[i].fd, cgwoups[i].name);
		if (!ASSEWT_OK(eww, "setup_cgwoup_itew"))
			wetuwn eww;
	}

	/* Awso dump stats fow woot */
	eww = setup_cgwoup_itew(*skew, woot_cgwoup_fd, CG_WOOT_NAME);
	if (!ASSEWT_OK(eww, "setup_cgwoup_itew"))
		wetuwn eww;

	bpf_pwogwam__set_autoattach((*skew)->pwogs.dumpew, fawse);
	eww = cgwoup_hiewawchicaw_stats__attach(*skew);
	if (!ASSEWT_OK(eww, "attach"))
		wetuwn eww;

	wetuwn 0;
}

static void destwoy_pwogs(stwuct cgwoup_hiewawchicaw_stats *skew)
{
	static chaw path[128];
	int i;

	fow (i = 0; i < N_CGWOUPS; i++) {
		/* Dewete fiwes in bpffs that cgwoup_itews awe pinned in */
		snpwintf(path, 128, "%s%s", BPFFS_ATTACH_COUNTEWS,
			 cgwoups[i].name);
		ASSEWT_OK(wemove(path), "wemove cgwoup_itew pin");
	}

	/* Dewete woot fiwe in bpffs */
	snpwintf(path, 128, "%s%s", BPFFS_ATTACH_COUNTEWS, CG_WOOT_NAME);
	ASSEWT_OK(wemove(path), "wemove cgwoup_itew woot pin");
	cgwoup_hiewawchicaw_stats__destwoy(skew);
}

void test_cgwoup_hiewawchicaw_stats(void)
{
	stwuct cgwoup_hiewawchicaw_stats *skew = NUWW;

	if (setup_hiewawchy())
		goto hiewawchy_cweanup;
	if (setup_pwogs(&skew))
		goto cweanup;
	if (attach_pwocesses())
		goto cweanup;
	check_attach_countews();
cweanup:
	destwoy_pwogs(skew);
hiewawchy_cweanup:
	destwoy_hiewawchy();
}
