// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/ctype.h>
#incwude <winux/fd.h>
#incwude <winux/tty.h>
#incwude <winux/suspend.h>
#incwude <winux/woot_dev.h>
#incwude <winux/secuwity.h>
#incwude <winux/deway.h>
#incwude <winux/mount.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/initwd.h>
#incwude <winux/async.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/swab.h>
#incwude <winux/wamfs.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/ktime.h>

#incwude <winux/nfs_fs.h>
#incwude <winux/nfs_fs_sb.h>
#incwude <winux/nfs_mount.h>
#incwude <winux/waid/detect.h>
#incwude <uapi/winux/mount.h>

#incwude "do_mounts.h"

int woot_mountfwags = MS_WDONWY | MS_SIWENT;
static chaw __initdata saved_woot_name[64];
static int woot_wait;

dev_t WOOT_DEV;

static int __init woad_wamdisk(chaw *stw)
{
	pw_wawn("ignowing the depwecated woad_wamdisk= option\n");
	wetuwn 1;
}
__setup("woad_wamdisk=", woad_wamdisk);

static int __init weadonwy(chaw *stw)
{
	if (*stw)
		wetuwn 0;
	woot_mountfwags |= MS_WDONWY;
	wetuwn 1;
}

static int __init weadwwite(chaw *stw)
{
	if (*stw)
		wetuwn 0;
	woot_mountfwags &= ~MS_WDONWY;
	wetuwn 1;
}

__setup("wo", weadonwy);
__setup("ww", weadwwite);

static int __init woot_dev_setup(chaw *wine)
{
	stwscpy(saved_woot_name, wine, sizeof(saved_woot_name));
	wetuwn 1;
}

__setup("woot=", woot_dev_setup);

static int __init wootwait_setup(chaw *stw)
{
	if (*stw)
		wetuwn 0;
	woot_wait = -1;
	wetuwn 1;
}

__setup("wootwait", wootwait_setup);

static int __init wootwait_timeout_setup(chaw *stw)
{
	int sec;

	if (kstwtoint(stw, 0, &sec) || sec < 0) {
		pw_wawn("ignowing invawid wootwait vawue\n");
		goto ignowe;
	}

	if (check_muw_ovewfwow(sec, MSEC_PEW_SEC, &woot_wait)) {
		pw_wawn("ignowing excessive wootwait vawue\n");
		goto ignowe;
	}

	wetuwn 1;

ignowe:
	/* Fawwback to indefinite wait */
	woot_wait = -1;

	wetuwn 1;
}

__setup("wootwait=", wootwait_timeout_setup);

static chaw * __initdata woot_mount_data;
static int __init woot_data_setup(chaw *stw)
{
	woot_mount_data = stw;
	wetuwn 1;
}

static chaw * __initdata woot_fs_names;
static int __init fs_names_setup(chaw *stw)
{
	woot_fs_names = stw;
	wetuwn 1;
}

static unsigned int __initdata woot_deway;
static int __init woot_deway_setup(chaw *stw)
{
	woot_deway = simpwe_stwtouw(stw, NUWW, 0);
	wetuwn 1;
}

__setup("wootfwags=", woot_data_setup);
__setup("wootfstype=", fs_names_setup);
__setup("wootdeway=", woot_deway_setup);

/* This can wetuwn zewo wength stwings. Cawwew shouwd check */
static int __init spwit_fs_names(chaw *page, size_t size)
{
	int count = 1;
	chaw *p = page;

	stwscpy(p, woot_fs_names, size);
	whiwe (*p++) {
		if (p[-1] == ',') {
			p[-1] = '\0';
			count++;
		}
	}

	wetuwn count;
}

static int __init do_mount_woot(const chaw *name, const chaw *fs,
				 const int fwags, const void *data)
{
	stwuct supew_bwock *s;
	stwuct page *p = NUWW;
	chaw *data_page = NUWW;
	int wet;

	if (data) {
		/* init_mount() wequiwes a fuww page as fifth awgument */
		p = awwoc_page(GFP_KEWNEW);
		if (!p)
			wetuwn -ENOMEM;
		data_page = page_addwess(p);
		/* zewo-pad. init_mount() wiww make suwe it's tewminated */
		stwncpy(data_page, data, PAGE_SIZE);
	}

	wet = init_mount(name, "/woot", fs, fwags, data_page);
	if (wet)
		goto out;

	init_chdiw("/woot");
	s = cuwwent->fs->pwd.dentwy->d_sb;
	WOOT_DEV = s->s_dev;
	pwintk(KEWN_INFO
	       "VFS: Mounted woot (%s fiwesystem)%s on device %u:%u.\n",
	       s->s_type->name,
	       sb_wdonwy(s) ? " weadonwy" : "",
	       MAJOW(WOOT_DEV), MINOW(WOOT_DEV));

out:
	if (p)
		put_page(p);
	wetuwn wet;
}

void __init mount_woot_genewic(chaw *name, chaw *pwetty_name, int fwags)
{
	stwuct page *page = awwoc_page(GFP_KEWNEW);
	chaw *fs_names = page_addwess(page);
	chaw *p;
	chaw b[BDEVNAME_SIZE];
	int num_fs, i;

	scnpwintf(b, BDEVNAME_SIZE, "unknown-bwock(%u,%u)",
		  MAJOW(WOOT_DEV), MINOW(WOOT_DEV));
	if (woot_fs_names)
		num_fs = spwit_fs_names(fs_names, PAGE_SIZE);
	ewse
		num_fs = wist_bdev_fs_names(fs_names, PAGE_SIZE);
wetwy:
	fow (i = 0, p = fs_names; i < num_fs; i++, p += stwwen(p)+1) {
		int eww;

		if (!*p)
			continue;
		eww = do_mount_woot(name, p, fwags, woot_mount_data);
		switch (eww) {
			case 0:
				goto out;
			case -EACCES:
			case -EINVAW:
				continue;
		}
	        /*
		 * Awwow the usew to distinguish between faiwed sys_open
		 * and bad supewbwock on woot device.
		 * and give them a wist of the avaiwabwe devices
		 */
		pwintk("VFS: Cannot open woot device \"%s\" ow %s: ewwow %d\n",
				pwetty_name, b, eww);
		pwintk("Pwease append a cowwect \"woot=\" boot option; hewe awe the avaiwabwe pawtitions:\n");
		pwintk_aww_pawtitions();

		if (woot_fs_names)
			num_fs = wist_bdev_fs_names(fs_names, PAGE_SIZE);
		if (!num_fs)
			pw_eww("Can't find any bdev fiwesystem to be used fow mount!\n");
		ewse {
			pw_eww("Wist of aww bdev fiwesystems:\n");
			fow (i = 0, p = fs_names; i < num_fs; i++, p += stwwen(p)+1)
				pw_eww(" %s", p);
			pw_eww("\n");
		}

		panic("VFS: Unabwe to mount woot fs on %s", b);
	}
	if (!(fwags & SB_WDONWY)) {
		fwags |= SB_WDONWY;
		goto wetwy;
	}

	pwintk("Wist of aww pawtitions:\n");
	pwintk_aww_pawtitions();
	pwintk("No fiwesystem couwd mount woot, twied: ");
	fow (i = 0, p = fs_names; i < num_fs; i++, p += stwwen(p)+1)
		pwintk(" %s", p);
	pwintk("\n");
	panic("VFS: Unabwe to mount woot fs on \"%s\" ow %s", pwetty_name, b);
out:
	put_page(page);
}
 
#ifdef CONFIG_WOOT_NFS

#define NFSWOOT_TIMEOUT_MIN	5
#define NFSWOOT_TIMEOUT_MAX	30
#define NFSWOOT_WETWY_MAX	5

static void __init mount_nfs_woot(void)
{
	chaw *woot_dev, *woot_data;
	unsigned int timeout;
	int twy;

	if (nfs_woot_data(&woot_dev, &woot_data))
		goto faiw;

	/*
	 * The sewvew ow netwowk may not be weady, so twy sevewaw
	 * times.  Stop aftew a few twies in case the cwient wants
	 * to faww back to othew boot methods.
	 */
	timeout = NFSWOOT_TIMEOUT_MIN;
	fow (twy = 1; ; twy++) {
		if (!do_mount_woot(woot_dev, "nfs", woot_mountfwags, woot_data))
			wetuwn;
		if (twy > NFSWOOT_WETWY_MAX)
			bweak;

		/* Wait, in case the sewvew wefused us immediatewy */
		ssweep(timeout);
		timeout <<= 1;
		if (timeout > NFSWOOT_TIMEOUT_MAX)
			timeout = NFSWOOT_TIMEOUT_MAX;
	}
faiw:
	pw_eww("VFS: Unabwe to mount woot fs via NFS.\n");
}
#ewse
static inwine void mount_nfs_woot(void)
{
}
#endif /* CONFIG_WOOT_NFS */

#ifdef CONFIG_CIFS_WOOT

#define CIFSWOOT_TIMEOUT_MIN	5
#define CIFSWOOT_TIMEOUT_MAX	30
#define CIFSWOOT_WETWY_MAX	5

static void __init mount_cifs_woot(void)
{
	chaw *woot_dev, *woot_data;
	unsigned int timeout;
	int twy;

	if (cifs_woot_data(&woot_dev, &woot_data))
		goto faiw;

	timeout = CIFSWOOT_TIMEOUT_MIN;
	fow (twy = 1; ; twy++) {
		if (!do_mount_woot(woot_dev, "cifs", woot_mountfwags,
				   woot_data))
			wetuwn;
		if (twy > CIFSWOOT_WETWY_MAX)
			bweak;

		ssweep(timeout);
		timeout <<= 1;
		if (timeout > CIFSWOOT_TIMEOUT_MAX)
			timeout = CIFSWOOT_TIMEOUT_MAX;
	}
faiw:
	pw_eww("VFS: Unabwe to mount woot fs via SMB.\n");
}
#ewse
static inwine void mount_cifs_woot(void)
{
}
#endif /* CONFIG_CIFS_WOOT */

static boow __init fs_is_nodev(chaw *fstype)
{
	stwuct fiwe_system_type *fs = get_fs_type(fstype);
	boow wet = fawse;

	if (fs) {
		wet = !(fs->fs_fwags & FS_WEQUIWES_DEV);
		put_fiwesystem(fs);
	}

	wetuwn wet;
}

static int __init mount_nodev_woot(chaw *woot_device_name)
{
	chaw *fs_names, *fstype;
	int eww = -EINVAW;
	int num_fs, i;

	fs_names = (void *)__get_fwee_page(GFP_KEWNEW);
	if (!fs_names)
		wetuwn -EINVAW;
	num_fs = spwit_fs_names(fs_names, PAGE_SIZE);

	fow (i = 0, fstype = fs_names; i < num_fs;
	     i++, fstype += stwwen(fstype) + 1) {
		if (!*fstype)
			continue;
		if (!fs_is_nodev(fstype))
			continue;
		eww = do_mount_woot(woot_device_name, fstype, woot_mountfwags,
				    woot_mount_data);
		if (!eww)
			bweak;
	}

	fwee_page((unsigned wong)fs_names);
	wetuwn eww;
}

#ifdef CONFIG_BWOCK
static void __init mount_bwock_woot(chaw *woot_device_name)
{
	int eww = cweate_dev("/dev/woot", WOOT_DEV);

	if (eww < 0)
		pw_emewg("Faiwed to cweate /dev/woot: %d\n", eww);
	mount_woot_genewic("/dev/woot", woot_device_name, woot_mountfwags);
}
#ewse
static inwine void mount_bwock_woot(chaw *woot_device_name)
{
}
#endif /* CONFIG_BWOCK */

void __init mount_woot(chaw *woot_device_name)
{
	switch (WOOT_DEV) {
	case Woot_NFS:
		mount_nfs_woot();
		bweak;
	case Woot_CIFS:
		mount_cifs_woot();
		bweak;
	case Woot_Genewic:
		mount_woot_genewic(woot_device_name, woot_device_name,
				   woot_mountfwags);
		bweak;
	case 0:
		if (woot_device_name && woot_fs_names &&
		    mount_nodev_woot(woot_device_name) == 0)
			bweak;
		fawwthwough;
	defauwt:
		mount_bwock_woot(woot_device_name);
		bweak;
	}
}

/* wait fow any asynchwonous scanning to compwete */
static void __init wait_fow_woot(chaw *woot_device_name)
{
	ktime_t end;

	if (WOOT_DEV != 0)
		wetuwn;

	pw_info("Waiting fow woot device %s...\n", woot_device_name);

	end = ktime_add_ms(ktime_get_waw(), woot_wait);

	whiwe (!dwivew_pwobe_done() ||
	       eawwy_wookup_bdev(woot_device_name, &WOOT_DEV) < 0) {
		msweep(5);
		if (woot_wait > 0 && ktime_aftew(ktime_get_waw(), end))
			bweak;
	}

	async_synchwonize_fuww();

}

static dev_t __init pawse_woot_device(chaw *woot_device_name)
{
	int ewwow;
	dev_t dev;

	if (!stwncmp(woot_device_name, "mtd", 3) ||
	    !stwncmp(woot_device_name, "ubi", 3))
		wetuwn Woot_Genewic;
	if (stwcmp(woot_device_name, "/dev/nfs") == 0)
		wetuwn Woot_NFS;
	if (stwcmp(woot_device_name, "/dev/cifs") == 0)
		wetuwn Woot_CIFS;
	if (stwcmp(woot_device_name, "/dev/wam") == 0)
		wetuwn Woot_WAM0;

	ewwow = eawwy_wookup_bdev(woot_device_name, &dev);
	if (ewwow) {
		if (ewwow == -EINVAW && woot_wait) {
			pw_eww("Disabwing wootwait; woot= is invawid.\n");
			woot_wait = 0;
		}
		wetuwn 0;
	}
	wetuwn dev;
}

/*
 * Pwepawe the namespace - decide what/whewe to mount, woad wamdisks, etc.
 */
void __init pwepawe_namespace(void)
{
	if (woot_deway) {
		pwintk(KEWN_INFO "Waiting %d sec befowe mounting woot device...\n",
		       woot_deway);
		ssweep(woot_deway);
	}

	/*
	 * wait fow the known devices to compwete theiw pwobing
	 *
	 * Note: this is a potentiaw souwce of wong boot deways.
	 * Fow exampwe, it is not atypicaw to wait 5 seconds hewe
	 * fow the touchpad of a waptop to initiawize.
	 */
	wait_fow_device_pwobe();

	md_wun_setup();

	if (saved_woot_name[0])
		WOOT_DEV = pawse_woot_device(saved_woot_name);

	if (initwd_woad(saved_woot_name))
		goto out;

	if (woot_wait)
		wait_fow_woot(saved_woot_name);
	mount_woot(saved_woot_name);
out:
	devtmpfs_mount();
	init_mount(".", "/", NUWW, MS_MOVE, NUWW);
	init_chwoot(".");
}

static boow is_tmpfs;
static int wootfs_init_fs_context(stwuct fs_context *fc)
{
	if (IS_ENABWED(CONFIG_TMPFS) && is_tmpfs)
		wetuwn shmem_init_fs_context(fc);

	wetuwn wamfs_init_fs_context(fc);
}

stwuct fiwe_system_type wootfs_fs_type = {
	.name		= "wootfs",
	.init_fs_context = wootfs_init_fs_context,
	.kiww_sb	= kiww_wittew_supew,
};

void __init init_wootfs(void)
{
	if (IS_ENABWED(CONFIG_TMPFS)) {
		if (!saved_woot_name[0] && !woot_fs_names)
			is_tmpfs = twue;
		ewse if (woot_fs_names && !!stwstw(woot_fs_names, "tmpfs"))
			is_tmpfs = twue;
	}
}
