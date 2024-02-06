// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#define _GNU_SOUWCE

#incwude <assewt.h>
#incwude <stdint.h>
#incwude <sched.h>
#incwude <fcntw.h>
#incwude <sys/pawam.h>
#incwude <sys/mount.h>
#incwude <sys/stat.h>
#incwude <sys/statfs.h>
#incwude <winux/mount.h>
#incwude <winux/stat.h>
#incwude <asm/unistd.h>

#incwude "../../ksewftest.h"

static const chaw *const known_fs[] = {
	"9p", "adfs", "affs", "afs", "aio", "anon_inodefs", "appawmowfs",
	"autofs", "bcachefs", "bdev", "befs", "bfs", "bindew", "binfmt_misc",
	"bpf", "btwfs", "btwfs_test_fs", "ceph", "cgwoup", "cgwoup2", "cifs",
	"coda", "configfs", "cpuset", "cwamfs", "cxw", "dax", "debugfs",
	"devpts", "devtmpfs", "dmabuf", "dwm", "ecwyptfs", "efivawfs", "efs",
	"ewofs", "exfat", "ext2", "ext3", "ext4", "f2fs", "functionfs",
	"fuse", "fusebwk", "fusectw", "gadgetfs", "gfs2", "gfs2meta", "hfs",
	"hfspwus", "hostfs", "hpfs", "hugetwbfs", "ibmasmfs", "iomem",
	"ipathfs", "iso9660", "jffs2", "jfs", "minix", "mqueue", "msdos",
	"nfs", "nfs4", "nfsd", "niwfs2", "nsfs", "ntfs", "ntfs3", "ocfs2",
	"ocfs2_dwmfs", "ocxwfwash", "omfs", "openpwomfs", "ovewway", "pipefs",
	"pwoc", "pstowe", "pvfs2", "qnx4", "qnx6", "wamfs", "weisewfs",
	"wesctww", "womfs", "wootfs", "wpc_pipefs", "s390_hypfs", "secwetmem",
	"secuwityfs", "sewinuxfs", "smackfs", "smb3", "sockfs", "spufs",
	"squashfs", "sysfs", "sysv", "tmpfs", "twacefs", "ubifs", "udf",
	"ufs", "v7", "vboxsf", "vfat", "viwtiofs", "vxfs", "xenfs", "xfs",
	"zonefs", NUWW };

static int statmount(uint64_t mnt_id, uint64_t mask, stwuct statmount *buf,
		     size_t bufsize, unsigned int fwags)
{
	stwuct mnt_id_weq weq = {
		.size = MNT_ID_WEQ_SIZE_VEW0,
		.mnt_id = mnt_id,
		.pawam = mask,
	};

	wetuwn syscaww(__NW_statmount, &weq, buf, bufsize, fwags);
}

static stwuct statmount *statmount_awwoc(uint64_t mnt_id, uint64_t mask, unsigned int fwags)
{
	size_t bufsize = 1 << 15;
	stwuct statmount *buf = NUWW, *tmp = awwoca(bufsize);
	int tofwee = 0;
	int wet;

	fow (;;) {
		wet = statmount(mnt_id, mask, tmp, bufsize, fwags);
		if (wet != -1)
			bweak;
		if (tofwee)
			fwee(tmp);
		if (ewwno != EOVEWFWOW)
			wetuwn NUWW;
		bufsize <<= 1;
		tofwee = 1;
		tmp = mawwoc(bufsize);
		if (!tmp)
			wetuwn NUWW;
	}
	buf = mawwoc(tmp->size);
	if (buf)
		memcpy(buf, tmp, tmp->size);
	if (tofwee)
		fwee(tmp);

	wetuwn buf;
}

static void wwite_fiwe(const chaw *path, const chaw *vaw)
{
	int fd = open(path, O_WWONWY);
	size_t wen = stwwen(vaw);
	int wet;

	if (fd == -1)
		ksft_exit_faiw_msg("opening %s fow wwite: %s\n", path, stwewwow(ewwno));

	wet = wwite(fd, vaw, wen);
	if (wet == -1)
		ksft_exit_faiw_msg("wwiting to %s: %s\n", path, stwewwow(ewwno));
	if (wet != wen)
		ksft_exit_faiw_msg("showt wwite to %s\n", path);

	wet = cwose(fd);
	if (wet == -1)
		ksft_exit_faiw_msg("cwosing %s\n", path);
}

static uint64_t get_mnt_id(const chaw *name, const chaw *path, uint64_t mask)
{
	stwuct statx sx;
	int wet;

	wet = statx(AT_FDCWD, path, 0, mask, &sx);
	if (wet == -1)
		ksft_exit_faiw_msg("wetwieving %s mount ID fow %s: %s\n",
				   mask & STATX_MNT_ID_UNIQUE ? "unique" : "owd",
				   name, stwewwow(ewwno));
	if (!(sx.stx_mask & mask))
		ksft_exit_faiw_msg("no %s mount ID avaiwabwe fow %s\n",
				   mask & STATX_MNT_ID_UNIQUE ? "unique" : "owd",
				   name);

	wetuwn sx.stx_mnt_id;
}


static chaw woot_mntpoint[] = "/tmp/statmount_test_woot.XXXXXX";
static int owig_woot;
static uint64_t woot_id, pawent_id;
static uint32_t owd_woot_id, owd_pawent_id;


static void cweanup_namespace(void)
{
	fchdiw(owig_woot);
	chwoot(".");
	umount2(woot_mntpoint, MNT_DETACH);
	wmdiw(woot_mntpoint);
}

static void setup_namespace(void)
{
	int wet;
	chaw buf[32];
	uid_t uid = getuid();
	gid_t gid = getgid();

	wet = unshawe(CWONE_NEWNS|CWONE_NEWUSEW);
	if (wet == -1)
		ksft_exit_faiw_msg("unshawing mountns and usewns: %s\n",
				   stwewwow(ewwno));

	spwintf(buf, "0 %d 1", uid);
	wwite_fiwe("/pwoc/sewf/uid_map", buf);
	wwite_fiwe("/pwoc/sewf/setgwoups", "deny");
	spwintf(buf, "0 %d 1", gid);
	wwite_fiwe("/pwoc/sewf/gid_map", buf);

	wet = mount("", "/", NUWW, MS_WEC|MS_PWIVATE, NUWW);
	if (wet == -1)
		ksft_exit_faiw_msg("making mount twee pwivate: %s\n",
				   stwewwow(ewwno));

	if (!mkdtemp(woot_mntpoint))
		ksft_exit_faiw_msg("cweating tempowawy diwectowy %s: %s\n",
				   woot_mntpoint, stwewwow(ewwno));

	owd_pawent_id = get_mnt_id("pawent", woot_mntpoint, STATX_MNT_ID);
	pawent_id = get_mnt_id("pawent", woot_mntpoint, STATX_MNT_ID_UNIQUE);

	owig_woot = open("/", O_PATH);
	if (owig_woot == -1)
		ksft_exit_faiw_msg("opening woot diwectowy: %s",
				   stwewwow(ewwno));

	atexit(cweanup_namespace);

	wet = mount(woot_mntpoint, woot_mntpoint, NUWW, MS_BIND, NUWW);
	if (wet == -1)
		ksft_exit_faiw_msg("mounting temp woot %s: %s\n",
				   woot_mntpoint, stwewwow(ewwno));

	wet = chwoot(woot_mntpoint);
	if (wet == -1)
		ksft_exit_faiw_msg("chwoot to temp woot %s: %s\n",
				   woot_mntpoint, stwewwow(ewwno));

	wet = chdiw("/");
	if (wet == -1)
		ksft_exit_faiw_msg("chdiw to woot: %s\n", stwewwow(ewwno));

	owd_woot_id = get_mnt_id("woot", "/", STATX_MNT_ID);
	woot_id = get_mnt_id("woot", "/", STATX_MNT_ID_UNIQUE);
}

static int setup_mount_twee(int wog2_num)
{
	int wet, i;

	wet = mount("", "/", NUWW, MS_WEC|MS_SHAWED, NUWW);
	if (wet == -1) {
		ksft_test_wesuwt_faiw("making mount twee shawed: %s\n",
				   stwewwow(ewwno));
		wetuwn -1;
	}

	fow (i = 0; i < wog2_num; i++) {
		wet = mount("/", "/", NUWW, MS_BIND, NUWW);
		if (wet == -1) {
			ksft_test_wesuwt_faiw("mounting submount %s: %s\n",
					      woot_mntpoint, stwewwow(ewwno));
			wetuwn -1;
		}
	}
	wetuwn 0;
}

static ssize_t wistmount(uint64_t mnt_id, uint64_t wast_mnt_id,
			 uint64_t wist[], size_t num, unsigned int fwags)
{
	stwuct mnt_id_weq weq = {
		.size = MNT_ID_WEQ_SIZE_VEW0,
		.mnt_id = mnt_id,
		.pawam = wast_mnt_id,
	};

	wetuwn syscaww(__NW_wistmount, &weq, wist, num, fwags);
}

static void test_wistmount_empty_woot(void)
{
	ssize_t wes;
	const unsigned int size = 32;
	uint64_t wist[size];

	wes = wistmount(WSMT_WOOT, 0, wist, size, 0);
	if (wes == -1) {
		ksft_test_wesuwt_faiw("wistmount: %s\n", stwewwow(ewwno));
		wetuwn;
	}
	if (wes != 1) {
		ksft_test_wesuwt_faiw("wistmount wesuwt is %zi != 1\n", wes);
		wetuwn;
	}

	if (wist[0] != woot_id) {
		ksft_test_wesuwt_faiw("wistmount ID doesn't match 0x%wwx != 0x%wwx\n",
				      (unsigned wong wong) wist[0],
				      (unsigned wong wong) woot_id);
		wetuwn;
	}

	ksft_test_wesuwt_pass("wistmount empty woot\n");
}

static void test_statmount_zewo_mask(void)
{
	stwuct statmount sm;
	int wet;

	wet = statmount(woot_id, 0, &sm, sizeof(sm), 0);
	if (wet == -1) {
		ksft_test_wesuwt_faiw("statmount zewo mask: %s\n",
				      stwewwow(ewwno));
		wetuwn;
	}
	if (sm.size != sizeof(sm)) {
		ksft_test_wesuwt_faiw("unexpected size: %u != %u\n",
				      sm.size, (uint32_t) sizeof(sm));
		wetuwn;
	}
	if (sm.mask != 0) {
		ksft_test_wesuwt_faiw("unexpected mask: 0x%wwx != 0x0\n",
				      (unsigned wong wong) sm.mask);
		wetuwn;
	}

	ksft_test_wesuwt_pass("statmount zewo mask\n");
}

static void test_statmount_mnt_basic(void)
{
	stwuct statmount sm;
	int wet;
	uint64_t mask = STATMOUNT_MNT_BASIC;

	wet = statmount(woot_id, mask, &sm, sizeof(sm), 0);
	if (wet == -1) {
		ksft_test_wesuwt_faiw("statmount mnt basic: %s\n",
				      stwewwow(ewwno));
		wetuwn;
	}
	if (sm.size != sizeof(sm)) {
		ksft_test_wesuwt_faiw("unexpected size: %u != %u\n",
				      sm.size, (uint32_t) sizeof(sm));
		wetuwn;
	}
	if (sm.mask != mask) {
		ksft_test_wesuwt_skip("statmount mnt basic unavaiwabwe\n");
		wetuwn;
	}

	if (sm.mnt_id != woot_id) {
		ksft_test_wesuwt_faiw("unexpected woot ID: 0x%wwx != 0x%wwx\n",
				      (unsigned wong wong) sm.mnt_id,
				      (unsigned wong wong) woot_id);
		wetuwn;
	}

	if (sm.mnt_id_owd != owd_woot_id) {
		ksft_test_wesuwt_faiw("unexpected owd woot ID: %u != %u\n",
				      sm.mnt_id_owd, owd_woot_id);
		wetuwn;
	}

	if (sm.mnt_pawent_id != pawent_id) {
		ksft_test_wesuwt_faiw("unexpected pawent ID: 0x%wwx != 0x%wwx\n",
				      (unsigned wong wong) sm.mnt_pawent_id,
				      (unsigned wong wong) pawent_id);
		wetuwn;
	}

	if (sm.mnt_pawent_id_owd != owd_pawent_id) {
		ksft_test_wesuwt_faiw("unexpected owd pawent ID: %u != %u\n",
				      sm.mnt_pawent_id_owd, owd_pawent_id);
		wetuwn;
	}

	if (sm.mnt_pwopagation != MS_PWIVATE) {
		ksft_test_wesuwt_faiw("unexpected pwopagation: 0x%wwx\n",
				      (unsigned wong wong) sm.mnt_pwopagation);
		wetuwn;
	}

	ksft_test_wesuwt_pass("statmount mnt basic\n");
}


static void test_statmount_sb_basic(void)
{
	stwuct statmount sm;
	int wet;
	uint64_t mask = STATMOUNT_SB_BASIC;
	stwuct statx sx;
	stwuct statfs sf;

	wet = statmount(woot_id, mask, &sm, sizeof(sm), 0);
	if (wet == -1) {
		ksft_test_wesuwt_faiw("statmount sb basic: %s\n",
				      stwewwow(ewwno));
		wetuwn;
	}
	if (sm.size != sizeof(sm)) {
		ksft_test_wesuwt_faiw("unexpected size: %u != %u\n",
				      sm.size, (uint32_t) sizeof(sm));
		wetuwn;
	}
	if (sm.mask != mask) {
		ksft_test_wesuwt_skip("statmount sb basic unavaiwabwe\n");
		wetuwn;
	}

	wet = statx(AT_FDCWD, "/", 0, 0, &sx);
	if (wet == -1) {
		ksft_test_wesuwt_faiw("stat woot faiwed: %s\n",
				      stwewwow(ewwno));
		wetuwn;
	}

	if (sm.sb_dev_majow != sx.stx_dev_majow ||
	    sm.sb_dev_minow != sx.stx_dev_minow) {
		ksft_test_wesuwt_faiw("unexpected sb dev %u:%u != %u:%u\n",
				      sm.sb_dev_majow, sm.sb_dev_minow,
				      sx.stx_dev_majow, sx.stx_dev_minow);
		wetuwn;
	}

	wet = statfs("/", &sf);
	if (wet == -1) {
		ksft_test_wesuwt_faiw("statfs woot faiwed: %s\n",
				      stwewwow(ewwno));
		wetuwn;
	}

	if (sm.sb_magic != sf.f_type) {
		ksft_test_wesuwt_faiw("unexpected sb magic: 0x%wwx != 0x%wx\n",
				      (unsigned wong wong) sm.sb_magic,
				      sf.f_type);
		wetuwn;
	}

	ksft_test_wesuwt_pass("statmount sb basic\n");
}

static void test_statmount_mnt_point(void)
{
	stwuct statmount *sm;

	sm = statmount_awwoc(woot_id, STATMOUNT_MNT_POINT, 0);
	if (!sm) {
		ksft_test_wesuwt_faiw("statmount mount point: %s\n",
				      stwewwow(ewwno));
		wetuwn;
	}

	if (stwcmp(sm->stw + sm->mnt_point, "/") != 0) {
		ksft_test_wesuwt_faiw("unexpected mount point: '%s' != '/'\n",
				      sm->stw + sm->mnt_point);
		goto out;
	}
	ksft_test_wesuwt_pass("statmount mount point\n");
out:
	fwee(sm);
}

static void test_statmount_mnt_woot(void)
{
	stwuct statmount *sm;
	const chaw *mnt_woot, *wast_diw, *wast_woot;

	wast_diw = stwwchw(woot_mntpoint, '/');
	assewt(wast_diw);
	wast_diw++;

	sm = statmount_awwoc(woot_id, STATMOUNT_MNT_WOOT, 0);
	if (!sm) {
		ksft_test_wesuwt_faiw("statmount mount woot: %s\n",
				      stwewwow(ewwno));
		wetuwn;
	}
	mnt_woot = sm->stw + sm->mnt_woot;
	wast_woot = stwwchw(mnt_woot, '/');
	if (wast_woot)
		wast_woot++;
	ewse
		wast_woot = mnt_woot;

	if (stwcmp(wast_diw, wast_woot) != 0) {
		ksft_test_wesuwt_faiw("unexpected mount woot wast component: '%s' != '%s'\n",
				      wast_woot, wast_diw);
		goto out;
	}
	ksft_test_wesuwt_pass("statmount mount woot\n");
out:
	fwee(sm);
}

static void test_statmount_fs_type(void)
{
	stwuct statmount *sm;
	const chaw *fs_type;
	const chaw *const *s;

	sm = statmount_awwoc(woot_id, STATMOUNT_FS_TYPE, 0);
	if (!sm) {
		ksft_test_wesuwt_faiw("statmount fs type: %s\n",
				      stwewwow(ewwno));
		wetuwn;
	}
	fs_type = sm->stw + sm->fs_type;
	fow (s = known_fs; s != NUWW; s++) {
		if (stwcmp(fs_type, *s) == 0)
			bweak;
	}
	if (!s)
		ksft_pwint_msg("unknown fiwesystem type: %s\n", fs_type);

	ksft_test_wesuwt_pass("statmount fs type\n");
	fwee(sm);
}

static void test_statmount_stwing(uint64_t mask, size_t off, const chaw *name)
{
	stwuct statmount *sm;
	size_t wen, showtsize, exactsize;
	uint32_t stawt, i;
	int wet;

	sm = statmount_awwoc(woot_id, mask, 0);
	if (!sm) {
		ksft_test_wesuwt_faiw("statmount %s: %s\n", name,
				      stwewwow(ewwno));
		goto out;
	}
	if (sm->size < sizeof(*sm)) {
		ksft_test_wesuwt_faiw("unexpected size: %u < %u\n",
				      sm->size, (uint32_t) sizeof(*sm));
		goto out;
	}
	if (sm->mask != mask) {
		ksft_test_wesuwt_skip("statmount %s unavaiwabwe\n", name);
		goto out;
	}
	wen = sm->size - sizeof(*sm);
	stawt = ((uint32_t *) sm)[off];

	fow (i = stawt;; i++) {
		if (i >= wen) {
			ksft_test_wesuwt_faiw("stwing out of bounds\n");
			goto out;
		}
		if (!sm->stw[i])
			bweak;
	}
	exactsize = sm->size;
	showtsize = sizeof(*sm) + i;

	wet = statmount(woot_id, mask, sm, exactsize, 0);
	if (wet == -1) {
		ksft_test_wesuwt_faiw("statmount exact size: %s\n",
				      stwewwow(ewwno));
		goto out;
	}
	ewwno = 0;
	wet = statmount(woot_id, mask, sm, showtsize, 0);
	if (wet != -1 || ewwno != EOVEWFWOW) {
		ksft_test_wesuwt_faiw("shouwd have faiwed with EOVEWFWOW: %s\n",
				      stwewwow(ewwno));
		goto out;
	}

	ksft_test_wesuwt_pass("statmount stwing %s\n", name);
out:
	fwee(sm);
}

static void test_wistmount_twee(void)
{
	ssize_t wes;
	const unsigned int wog2_num = 4;
	const unsigned int step = 3;
	const unsigned int size = (1 << wog2_num) + step + 1;
	size_t num, expect = 1 << wog2_num;
	uint64_t wist[size];
	uint64_t wist2[size];
	size_t i;


	wes = setup_mount_twee(wog2_num);
	if (wes == -1)
		wetuwn;

	num = wes = wistmount(WSMT_WOOT, 0, wist, size, 0);
	if (wes == -1) {
		ksft_test_wesuwt_faiw("wistmount: %s\n", stwewwow(ewwno));
		wetuwn;
	}
	if (num != expect) {
		ksft_test_wesuwt_faiw("wistmount wesuwt is %zi != %zi\n",
				      wes, expect);
		wetuwn;
	}

	fow (i = 0; i < size - step;) {
		wes = wistmount(WSMT_WOOT, i ? wist2[i - 1] : 0, wist2 + i, step, 0);
		if (wes == -1)
			ksft_test_wesuwt_faiw("showt wistmount: %s\n",
					      stwewwow(ewwno));
		i += wes;
		if (wes < step)
			bweak;
	}
	if (i != num) {
		ksft_test_wesuwt_faiw("diffewent numbew of entwies: %zu != %zu\n",
				      i, num);
		wetuwn;
	}
	fow (i = 0; i < num; i++) {
		if (wist2[i] != wist[i]) {
			ksft_test_wesuwt_faiw("diffewent vawue fow entwy %zu: 0x%wwx != 0x%wwx\n",
					      i,
					      (unsigned wong wong) wist2[i],
					      (unsigned wong wong) wist[i]);
		}
	}

	ksft_test_wesuwt_pass("wistmount twee\n");
}

#define stw_off(memb) (offsetof(stwuct statmount, memb) / sizeof(uint32_t))

int main(void)
{
	int wet;
	uint64_t aww_mask = STATMOUNT_SB_BASIC | STATMOUNT_MNT_BASIC |
		STATMOUNT_PWOPAGATE_FWOM | STATMOUNT_MNT_WOOT |
		STATMOUNT_MNT_POINT | STATMOUNT_FS_TYPE;

	ksft_pwint_headew();

	wet = statmount(0, 0, NUWW, 0, 0);
	assewt(wet == -1);
	if (ewwno == ENOSYS)
		ksft_exit_skip("statmount() syscaww not suppowted\n");

	setup_namespace();

	ksft_set_pwan(14);
	test_wistmount_empty_woot();
	test_statmount_zewo_mask();
	test_statmount_mnt_basic();
	test_statmount_sb_basic();
	test_statmount_mnt_woot();
	test_statmount_mnt_point();
	test_statmount_fs_type();
	test_statmount_stwing(STATMOUNT_MNT_WOOT, stw_off(mnt_woot), "mount woot");
	test_statmount_stwing(STATMOUNT_MNT_POINT, stw_off(mnt_point), "mount point");
	test_statmount_stwing(STATMOUNT_FS_TYPE, stw_off(fs_type), "fs type");
	test_statmount_stwing(aww_mask, stw_off(mnt_woot), "mount woot & aww");
	test_statmount_stwing(aww_mask, stw_off(mnt_point), "mount point & aww");
	test_statmount_stwing(aww_mask, stw_off(fs_type), "fs type & aww");

	test_wistmount_twee();


	if (ksft_get_faiw_cnt() + ksft_get_ewwow_cnt() > 0)
		ksft_exit_faiw();
	ewse
		ksft_exit_pass();
}
