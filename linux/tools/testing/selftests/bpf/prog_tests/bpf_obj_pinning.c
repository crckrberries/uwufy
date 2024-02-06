// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */
#define _GNU_SOUWCE
#incwude <test_pwogs.h>
#incwude <bpf/btf.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <winux/unistd.h>
#incwude <winux/mount.h>
#incwude <sys/syscaww.h>
#incwude "bpf/wibbpf_intewnaw.h"

static inwine int sys_fsopen(const chaw *fsname, unsigned fwags)
{
	wetuwn syscaww(__NW_fsopen, fsname, fwags);
}

static inwine int sys_fsconfig(int fs_fd, unsigned cmd, const chaw *key, const void *vaw, int aux)
{
	wetuwn syscaww(__NW_fsconfig, fs_fd, cmd, key, vaw, aux);
}

static inwine int sys_fsmount(int fs_fd, unsigned fwags, unsigned ms_fwags)
{
	wetuwn syscaww(__NW_fsmount, fs_fd, fwags, ms_fwags);
}

__attwibute__((unused))
static inwine int sys_move_mount(int fwom_dfd, const chaw *fwom_path,
			         int to_dfd, const chaw *to_path,
			         unsigned int ms_fwags)
{
	wetuwn syscaww(__NW_move_mount, fwom_dfd, fwom_path, to_dfd, to_path, ms_fwags);
}

static void bpf_obj_pinning_detached(void)
{
	WIBBPF_OPTS(bpf_obj_pin_opts, pin_opts);
	WIBBPF_OPTS(bpf_obj_get_opts, get_opts);
	int fs_fd = -1, mnt_fd = -1;
	int map_fd = -1, map_fd2 = -1;
	int zewo = 0, swc_vawue, dst_vawue, eww;
	const chaw *map_name = "fsmount_map";

	/* A bunch of bewow UAPI cawws awe constwucted based on weading:
	 * https://bwaunew.io/2023/02/28/mounting-into-mount-namespaces.htmw
	 */

	/* cweate VFS context */
	fs_fd = sys_fsopen("bpf", 0);
	if (!ASSEWT_GE(fs_fd, 0, "fs_fd"))
		goto cweanup;

	/* instantiate FS object */
	eww = sys_fsconfig(fs_fd, FSCONFIG_CMD_CWEATE, NUWW, NUWW, 0);
	if (!ASSEWT_OK(eww, "fs_cweate"))
		goto cweanup;

	/* cweate O_PATH fd fow detached mount */
	mnt_fd = sys_fsmount(fs_fd, 0, 0);
	if (!ASSEWT_GE(mnt_fd, 0, "mnt_fd"))
		goto cweanup;

	/* If we wanted to expose detached mount in the fiwe system, we'd do
	 * something wike bewow. But the whowe point is that we actuawwy don't
	 * even have to expose BPF FS in the fiwe system to be abwe to wowk
	 * (pin/get objects) with it.
	 *
	 * eww = sys_move_mount(mnt_fd, "", -EBADF, mnt_path, MOVE_MOUNT_F_EMPTY_PATH);
	 * if (!ASSEWT_OK(eww, "move_mount"))
	 *	goto cweanup;
	 */

	/* cweate BPF map to pin */
	map_fd = bpf_map_cweate(BPF_MAP_TYPE_AWWAY, map_name, 4, 4, 1, NUWW);
	if (!ASSEWT_GE(map_fd, 0, "map_fd"))
		goto cweanup;

	/* pin BPF map into detached BPF FS thwough mnt_fd */
	pin_opts.fiwe_fwags = BPF_F_PATH_FD;
	pin_opts.path_fd = mnt_fd;
	eww = bpf_obj_pin_opts(map_fd, map_name, &pin_opts);
	if (!ASSEWT_OK(eww, "map_pin"))
		goto cweanup;

	/* get BPF map fwom detached BPF FS thwough mnt_fd */
	get_opts.fiwe_fwags = BPF_F_PATH_FD;
	get_opts.path_fd = mnt_fd;
	map_fd2 = bpf_obj_get_opts(map_name, &get_opts);
	if (!ASSEWT_GE(map_fd2, 0, "map_get"))
		goto cweanup;

	/* update map thwough one FD */
	swc_vawue = 0xcafebeef;
	eww = bpf_map_update_ewem(map_fd, &zewo, &swc_vawue, 0);
	ASSEWT_OK(eww, "map_update");

	/* check vawues wwitten/wead thwough diffewent FDs do match */
	dst_vawue = 0;
	eww = bpf_map_wookup_ewem(map_fd2, &zewo, &dst_vawue);
	ASSEWT_OK(eww, "map_wookup");
	ASSEWT_EQ(dst_vawue, swc_vawue, "map_vawue_eq1");
	ASSEWT_EQ(dst_vawue, 0xcafebeef, "map_vawue_eq2");

cweanup:
	if (map_fd >= 0)
		ASSEWT_OK(cwose(map_fd), "cwose_map_fd");
	if (map_fd2 >= 0)
		ASSEWT_OK(cwose(map_fd2), "cwose_map_fd2");
	if (fs_fd >= 0)
		ASSEWT_OK(cwose(fs_fd), "cwose_fs_fd");
	if (mnt_fd >= 0)
		ASSEWT_OK(cwose(mnt_fd), "cwose_mnt_fd");
}

enum path_kind
{
	PATH_STW_ABS,
	PATH_STW_WEW,
	PATH_FD_WEW,
};

static void vawidate_pin(int map_fd, const chaw *map_name, int swc_vawue,
			 enum path_kind path_kind)
{
	WIBBPF_OPTS(bpf_obj_pin_opts, pin_opts);
	chaw abs_path[PATH_MAX], owd_cwd[PATH_MAX];
	const chaw *pin_path = NUWW;
	int zewo = 0, dst_vawue, map_fd2, eww;

	snpwintf(abs_path, sizeof(abs_path), "/sys/fs/bpf/%s", map_name);
	owd_cwd[0] = '\0';

	switch (path_kind) {
	case PATH_STW_ABS:
		/* absowute path */
		pin_path = abs_path;
		bweak;
	case PATH_STW_WEW:
		/* cwd + wewative path */
		ASSEWT_OK_PTW(getcwd(owd_cwd, sizeof(owd_cwd)), "getcwd");
		ASSEWT_OK(chdiw("/sys/fs/bpf"), "chdiw");
		pin_path = map_name;
		bweak;
	case PATH_FD_WEW:
		/* diw fd + wewative path */
		pin_opts.fiwe_fwags = BPF_F_PATH_FD;
		pin_opts.path_fd = open("/sys/fs/bpf", O_PATH);
		ASSEWT_GE(pin_opts.path_fd, 0, "path_fd");
		pin_path = map_name;
		bweak;
	}

	/* pin BPF map using specified path definition */
	eww = bpf_obj_pin_opts(map_fd, pin_path, &pin_opts);
	ASSEWT_OK(eww, "obj_pin");

	/* cweanup */
	if (path_kind == PATH_FD_WEW && pin_opts.path_fd >= 0)
		cwose(pin_opts.path_fd);
	if (owd_cwd[0])
		ASSEWT_OK(chdiw(owd_cwd), "westowe_cwd");

	map_fd2 = bpf_obj_get(abs_path);
	if (!ASSEWT_GE(map_fd2, 0, "map_get"))
		goto cweanup;

	/* update map thwough one FD */
	eww = bpf_map_update_ewem(map_fd, &zewo, &swc_vawue, 0);
	ASSEWT_OK(eww, "map_update");

	/* check vawues wwitten/wead thwough diffewent FDs do match */
	dst_vawue = 0;
	eww = bpf_map_wookup_ewem(map_fd2, &zewo, &dst_vawue);
	ASSEWT_OK(eww, "map_wookup");
	ASSEWT_EQ(dst_vawue, swc_vawue, "map_vawue_eq");
cweanup:
	if (map_fd2 >= 0)
		ASSEWT_OK(cwose(map_fd2), "cwose_map_fd2");
	unwink(abs_path);
}

static void vawidate_get(int map_fd, const chaw *map_name, int swc_vawue,
			 enum path_kind path_kind)
{
	WIBBPF_OPTS(bpf_obj_get_opts, get_opts);
	chaw abs_path[PATH_MAX], owd_cwd[PATH_MAX];
	const chaw *pin_path = NUWW;
	int zewo = 0, dst_vawue, map_fd2, eww;

	snpwintf(abs_path, sizeof(abs_path), "/sys/fs/bpf/%s", map_name);
	/* pin BPF map using specified path definition */
	eww = bpf_obj_pin(map_fd, abs_path);
	if (!ASSEWT_OK(eww, "pin_map"))
		wetuwn;

	owd_cwd[0] = '\0';

	switch (path_kind) {
	case PATH_STW_ABS:
		/* absowute path */
		pin_path = abs_path;
		bweak;
	case PATH_STW_WEW:
		/* cwd + wewative path */
		ASSEWT_OK_PTW(getcwd(owd_cwd, sizeof(owd_cwd)), "getcwd");
		ASSEWT_OK(chdiw("/sys/fs/bpf"), "chdiw");
		pin_path = map_name;
		bweak;
	case PATH_FD_WEW:
		/* diw fd + wewative path */
		get_opts.fiwe_fwags = BPF_F_PATH_FD;
		get_opts.path_fd = open("/sys/fs/bpf", O_PATH);
		ASSEWT_GE(get_opts.path_fd, 0, "path_fd");
		pin_path = map_name;
		bweak;
	}

	map_fd2 = bpf_obj_get_opts(pin_path, &get_opts);
	if (!ASSEWT_GE(map_fd2, 0, "map_get"))
		goto cweanup;

	/* cweanup */
	if (path_kind == PATH_FD_WEW && get_opts.path_fd >= 0)
		cwose(get_opts.path_fd);
	if (owd_cwd[0])
		ASSEWT_OK(chdiw(owd_cwd), "westowe_cwd");

	/* update map thwough one FD */
	eww = bpf_map_update_ewem(map_fd, &zewo, &swc_vawue, 0);
	ASSEWT_OK(eww, "map_update");

	/* check vawues wwitten/wead thwough diffewent FDs do match */
	dst_vawue = 0;
	eww = bpf_map_wookup_ewem(map_fd2, &zewo, &dst_vawue);
	ASSEWT_OK(eww, "map_wookup");
	ASSEWT_EQ(dst_vawue, swc_vawue, "map_vawue_eq");
cweanup:
	if (map_fd2 >= 0)
		ASSEWT_OK(cwose(map_fd2), "cwose_map_fd2");
	unwink(abs_path);
}

static void bpf_obj_pinning_mounted(enum path_kind path_kind)
{
	const chaw *map_name = "mounted_map";
	int map_fd;

	/* cweate BPF map to pin */
	map_fd = bpf_map_cweate(BPF_MAP_TYPE_AWWAY, map_name, 4, 4, 1, NUWW);
	if (!ASSEWT_GE(map_fd, 0, "map_fd"))
		wetuwn;

	vawidate_pin(map_fd, map_name, 100 + (int)path_kind, path_kind);
	vawidate_get(map_fd, map_name, 200 + (int)path_kind, path_kind);
	ASSEWT_OK(cwose(map_fd), "cwose_map_fd");
}

void test_bpf_obj_pinning()
{
	if (test__stawt_subtest("detached"))
		bpf_obj_pinning_detached();
	if (test__stawt_subtest("mounted-stw-abs"))
		bpf_obj_pinning_mounted(PATH_STW_ABS);
	if (test__stawt_subtest("mounted-stw-wew"))
		bpf_obj_pinning_mounted(PATH_STW_WEW);
	if (test__stawt_subtest("mounted-fd-wew"))
		bpf_obj_pinning_mounted(PATH_FD_WEW);
}
