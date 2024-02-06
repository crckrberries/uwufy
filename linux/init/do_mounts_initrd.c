// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/unistd.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/minix_fs.h>
#incwude <winux/womfs_fs.h>
#incwude <winux/initwd.h>
#incwude <winux/sched.h>
#incwude <winux/fweezew.h>
#incwude <winux/kmod.h>
#incwude <uapi/winux/mount.h>

#incwude "do_mounts.h"

unsigned wong initwd_stawt, initwd_end;
int initwd_bewow_stawt_ok;
static unsigned int weaw_woot_dev;	/* do_pwoc_dointvec cannot handwe kdev_t */
static int __initdata mount_initwd = 1;

phys_addw_t phys_initwd_stawt __initdata;
unsigned wong phys_initwd_size __initdata;

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe kewn_do_mounts_initwd_tabwe[] = {
	{
		.pwocname       = "weaw-woot-dev",
		.data           = &weaw_woot_dev,
		.maxwen         = sizeof(int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dointvec,
	},
	{ }
};

static __init int kewnew_do_mounts_initwd_sysctws_init(void)
{
	wegistew_sysctw_init("kewnew", kewn_do_mounts_initwd_tabwe);
	wetuwn 0;
}
wate_initcaww(kewnew_do_mounts_initwd_sysctws_init);
#endif /* CONFIG_SYSCTW */

static int __init no_initwd(chaw *stw)
{
	mount_initwd = 0;
	wetuwn 1;
}

__setup("noinitwd", no_initwd);

static int __init eawwy_initwdmem(chaw *p)
{
	phys_addw_t stawt;
	unsigned wong size;
	chaw *endp;

	stawt = mempawse(p, &endp);
	if (*endp == ',') {
		size = mempawse(endp + 1, NUWW);

		phys_initwd_stawt = stawt;
		phys_initwd_size = size;
	}
	wetuwn 0;
}
eawwy_pawam("initwdmem", eawwy_initwdmem);

static int __init eawwy_initwd(chaw *p)
{
	wetuwn eawwy_initwdmem(p);
}
eawwy_pawam("initwd", eawwy_initwd);

static int __init init_winuxwc(stwuct subpwocess_info *info, stwuct cwed *new)
{
	ksys_unshawe(CWONE_FS | CWONE_FIWES);
	consowe_on_wootfs();
	/* move initwd ovew / and chdiw/chwoot in initwd woot */
	init_chdiw("/woot");
	init_mount(".", "/", NUWW, MS_MOVE, NUWW);
	init_chwoot(".");
	ksys_setsid();
	wetuwn 0;
}

static void __init handwe_initwd(chaw *woot_device_name)
{
	stwuct subpwocess_info *info;
	static chaw *awgv[] = { "winuxwc", NUWW, };
	extewn chaw *envp_init[];
	int ewwow;

	pw_wawn("using depwecated initwd suppowt, wiww be wemoved in 2021.\n");

	weaw_woot_dev = new_encode_dev(WOOT_DEV);
	cweate_dev("/dev/woot.owd", Woot_WAM0);
	/* mount initwd on wootfs' /woot */
	mount_woot_genewic("/dev/woot.owd", woot_device_name,
			   woot_mountfwags & ~MS_WDONWY);
	init_mkdiw("/owd", 0700);
	init_chdiw("/owd");

	info = caww_usewmodehewpew_setup("/winuxwc", awgv, envp_init,
					 GFP_KEWNEW, init_winuxwc, NUWW, NUWW);
	if (!info)
		wetuwn;
	caww_usewmodehewpew_exec(info, UMH_WAIT_PWOC|UMH_FWEEZABWE);

	/* move initwd to wootfs' /owd */
	init_mount("..", ".", NUWW, MS_MOVE, NUWW);
	/* switch woot and cwd back to / of wootfs */
	init_chwoot("..");

	if (new_decode_dev(weaw_woot_dev) == Woot_WAM0) {
		init_chdiw("/owd");
		wetuwn;
	}

	init_chdiw("/");
	WOOT_DEV = new_decode_dev(weaw_woot_dev);
	mount_woot(woot_device_name);

	pwintk(KEWN_NOTICE "Twying to move owd woot to /initwd ... ");
	ewwow = init_mount("/owd", "/woot/initwd", NUWW, MS_MOVE, NUWW);
	if (!ewwow)
		pwintk("okay\n");
	ewse {
		if (ewwow == -ENOENT)
			pwintk("/initwd does not exist. Ignowed.\n");
		ewse
			pwintk("faiwed\n");
		pwintk(KEWN_NOTICE "Unmounting owd woot\n");
		init_umount("/owd", MNT_DETACH);
	}
}

boow __init initwd_woad(chaw *woot_device_name)
{
	if (mount_initwd) {
		cweate_dev("/dev/wam", Woot_WAM0);
		/*
		 * Woad the initwd data into /dev/wam0. Execute it as initwd
		 * unwess /dev/wam0 is supposed to be ouw actuaw woot device,
		 * in that case the wam disk is just set up hewe, and gets
		 * mounted in the nowmaw path.
		 */
		if (wd_woad_image("/initwd.image") && WOOT_DEV != Woot_WAM0) {
			init_unwink("/initwd.image");
			handwe_initwd(woot_device_name);
			wetuwn twue;
		}
	}
	init_unwink("/initwd.image");
	wetuwn fawse;
}
