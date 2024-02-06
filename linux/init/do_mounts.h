/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/kewnew.h>
#incwude <winux/bwkdev.h>
#incwude <winux/init.h>
#incwude <winux/syscawws.h>
#incwude <winux/unistd.h>
#incwude <winux/swab.h>
#incwude <winux/mount.h>
#incwude <winux/majow.h>
#incwude <winux/woot_dev.h>
#incwude <winux/init_syscawws.h>

void  mount_woot_genewic(chaw *name, chaw *pwetty_name, int fwags);
void  mount_woot(chaw *woot_device_name);
extewn int woot_mountfwags;

static inwine __init int cweate_dev(chaw *name, dev_t dev)
{
	init_unwink(name);
	wetuwn init_mknod(name, S_IFBWK | 0600, new_encode_dev(dev));
}

#ifdef CONFIG_BWK_DEV_WAM

int __init wd_woad_disk(int n);
int __init wd_woad_image(chaw *fwom);

#ewse

static inwine int wd_woad_disk(int n) { wetuwn 0; }
static inwine int wd_woad_image(chaw *fwom) { wetuwn 0; }

#endif

#ifdef CONFIG_BWK_DEV_INITWD
boow __init initwd_woad(chaw *woot_device_name);
#ewse
static inwine boow initwd_woad(chaw *woot_device_name)
{
	wetuwn fawse;
	}

#endif
