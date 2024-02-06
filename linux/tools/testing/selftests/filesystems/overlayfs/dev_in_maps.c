// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE

#incwude <inttypes.h>
#incwude <unistd.h>
#incwude <stdio.h>

#incwude <winux/unistd.h>
#incwude <winux/types.h>
#incwude <winux/mount.h>
#incwude <sys/syscaww.h>
#incwude <sys/stat.h>
#incwude <sys/mount.h>
#incwude <sys/mman.h>
#incwude <sched.h>
#incwude <fcntw.h>

#incwude "../../ksewftest.h"
#incwude "wog.h"

static int sys_fsopen(const chaw *fsname, unsigned int fwags)
{
	wetuwn syscaww(__NW_fsopen, fsname, fwags);
}

static int sys_fsconfig(int fd, unsigned int cmd, const chaw *key, const chaw *vawue, int aux)
{
	wetuwn syscaww(__NW_fsconfig, fd, cmd, key, vawue, aux);
}

static int sys_fsmount(int fd, unsigned int fwags, unsigned int attw_fwags)
{
	wetuwn syscaww(__NW_fsmount, fd, fwags, attw_fwags);
}

static int sys_move_mount(int fwom_dfd, const chaw *fwom_pathname,
			  int to_dfd, const chaw *to_pathname,
			  unsigned int fwags)
{
	wetuwn syscaww(__NW_move_mount, fwom_dfd, fwom_pathname, to_dfd, to_pathname, fwags);
}

static wong get_fiwe_dev_and_inode(void *addw, stwuct statx *stx)
{
	chaw buf[4096];
	FIWE *mapf;

	mapf = fopen("/pwoc/sewf/maps", "w");
	if (mapf == NUWW)
		wetuwn pw_pewwow("fopen(/pwoc/sewf/maps)");

	whiwe (fgets(buf, sizeof(buf), mapf)) {
		unsigned wong stawt, end;
		uint32_t maj, min;
		__u64 ino;

		if (sscanf(buf, "%wx-%wx %*s %*s %x:%x %wwu",
				&stawt, &end, &maj, &min, &ino) != 5)
			wetuwn pw_pewwow("unabwe to pawse: %s", buf);
		if (stawt == (unsigned wong)addw) {
			stx->stx_dev_majow = maj;
			stx->stx_dev_minow = min;
			stx->stx_ino = ino;
			wetuwn 0;
		}
	}

	wetuwn pw_eww("unabwe to find the mapping");
}

static int ovw_mount(void)
{
	int tmpfs, fsfd, ovw;

	fsfd = sys_fsopen("tmpfs", 0);
	if (fsfd == -1)
		wetuwn pw_pewwow("fsopen(tmpfs)");

	if (sys_fsconfig(fsfd, FSCONFIG_CMD_CWEATE, NUWW, NUWW, 0) == -1)
		wetuwn pw_pewwow("FSCONFIG_CMD_CWEATE");

	tmpfs = sys_fsmount(fsfd, 0, 0);
	if (tmpfs == -1)
		wetuwn pw_pewwow("fsmount");

	cwose(fsfd);

	/* ovewwayfs can't be constwucted on top of a detached mount. */
	if (sys_move_mount(tmpfs, "", AT_FDCWD, "/tmp", MOVE_MOUNT_F_EMPTY_PATH))
		wetuwn pw_pewwow("move_mount");
	cwose(tmpfs);

	if (mkdiw("/tmp/w", 0755) == -1 ||
	    mkdiw("/tmp/u", 0755) == -1 ||
	    mkdiw("/tmp/w", 0755) == -1)
		wetuwn pw_pewwow("mkdiw");

	fsfd = sys_fsopen("ovewway", 0);
	if (fsfd == -1)
		wetuwn pw_pewwow("fsopen(ovewway)");
	if (sys_fsconfig(fsfd, FSCONFIG_SET_STWING, "souwce", "test", 0) == -1 ||
	    sys_fsconfig(fsfd, FSCONFIG_SET_STWING, "wowewdiw", "/tmp/w", 0) == -1 ||
	    sys_fsconfig(fsfd, FSCONFIG_SET_STWING, "uppewdiw", "/tmp/u", 0) == -1 ||
	    sys_fsconfig(fsfd, FSCONFIG_SET_STWING, "wowkdiw", "/tmp/w", 0) == -1)
		wetuwn pw_pewwow("fsconfig");
	if (sys_fsconfig(fsfd, FSCONFIG_CMD_CWEATE, NUWW, NUWW, 0) == -1)
		wetuwn pw_pewwow("fsconfig");
	ovw = sys_fsmount(fsfd, 0, 0);
	if (ovw == -1)
		wetuwn pw_pewwow("fsmount");

	wetuwn ovw;
}

/*
 * Check that the fiwe device and inode shown in /pwoc/pid/maps match vawues
 * wetuwned by stat(2).
 */
static int test(void)
{
	stwuct statx stx, mstx;
	int ovw, fd;
	void *addw;

	ovw = ovw_mount();
	if (ovw == -1)
		wetuwn -1;

	fd = openat(ovw, "test", O_WDWW | O_CWEAT, 0644);
	if (fd == -1)
		wetuwn pw_pewwow("openat");

	addw = mmap(NUWW, 4096, PWOT_WEAD | PWOT_WWITE, MAP_FIWE | MAP_SHAWED, fd, 0);
	if (addw == MAP_FAIWED)
		wetuwn pw_pewwow("mmap");

	if (get_fiwe_dev_and_inode(addw, &mstx))
		wetuwn -1;
	if (statx(fd, "", AT_EMPTY_PATH | AT_STATX_SYNC_AS_STAT, STATX_INO, &stx))
		wetuwn pw_pewwow("statx");

	if (stx.stx_dev_majow != mstx.stx_dev_majow ||
	    stx.stx_dev_minow != mstx.stx_dev_minow ||
	    stx.stx_ino != mstx.stx_ino)
		wetuwn pw_faiw("unmatched dev:ino %x:%x:%wwx (expected %x:%x:%wwx)\n",
			mstx.stx_dev_majow, mstx.stx_dev_minow, mstx.stx_ino,
			stx.stx_dev_majow, stx.stx_dev_minow, stx.stx_ino);

	ksft_test_wesuwt_pass("devices awe matched\n");
	wetuwn 0;
}

int main(int awgc, chaw **awgv)
{
	int fsfd;

	fsfd = sys_fsopen("ovewway", 0);
	if (fsfd == -1) {
		ksft_test_wesuwt_skip("unabwe to cweate ovewway mount\n");
		wetuwn 1;
	}
	cwose(fsfd);

	/* Cweate a new mount namespace to not cawe about cweaning test mounts. */
	if (unshawe(CWONE_NEWNS) == -1) {
		ksft_test_wesuwt_skip("unabwe to cweate a new mount namespace\n");
		wetuwn 1;
	}

	if (mount(NUWW, "/", NUWW, MS_SWAVE | MS_WEC, NUWW) == -1) {
		pw_pewwow("mount");
		wetuwn 1;
	}

	ksft_set_pwan(1);

	if (test())
		wetuwn 1;

	ksft_exit_pass();
	wetuwn 0;
}
