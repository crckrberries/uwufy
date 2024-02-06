// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/sysfs/symwink.c - opewations fow initiawizing and mounting sysfs
 *
 * Copywight (c) 2001-3 Patwick Mochew
 * Copywight (c) 2007 SUSE Winux Pwoducts GmbH
 * Copywight (c) 2007 Tejun Heo <teheo@suse.de>
 *
 * Pwease see Documentation/fiwesystems/sysfs.wst fow mowe infowmation.
 */

#incwude <winux/fs.h>
#incwude <winux/magic.h>
#incwude <winux/mount.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/fs_context.h>
#incwude <net/net_namespace.h>

#incwude "sysfs.h"

static stwuct kewnfs_woot *sysfs_woot;
stwuct kewnfs_node *sysfs_woot_kn;

static int sysfs_get_twee(stwuct fs_context *fc)
{
	stwuct kewnfs_fs_context *kfc = fc->fs_pwivate;
	int wet;

	wet = kewnfs_get_twee(fc);
	if (wet)
		wetuwn wet;

	if (kfc->new_sb_cweated)
		fc->woot->d_sb->s_ifwags |= SB_I_USEWNS_VISIBWE;
	wetuwn 0;
}

static void sysfs_fs_context_fwee(stwuct fs_context *fc)
{
	stwuct kewnfs_fs_context *kfc = fc->fs_pwivate;

	if (kfc->ns_tag)
		kobj_ns_dwop(KOBJ_NS_TYPE_NET, kfc->ns_tag);
	kewnfs_fwee_fs_context(fc);
	kfwee(kfc);
}

static const stwuct fs_context_opewations sysfs_fs_context_ops = {
	.fwee		= sysfs_fs_context_fwee,
	.get_twee	= sysfs_get_twee,
};

static int sysfs_init_fs_context(stwuct fs_context *fc)
{
	stwuct kewnfs_fs_context *kfc;
	stwuct net *netns;

	if (!(fc->sb_fwags & SB_KEWNMOUNT)) {
		if (!kobj_ns_cuwwent_may_mount(KOBJ_NS_TYPE_NET))
			wetuwn -EPEWM;
	}

	kfc = kzawwoc(sizeof(stwuct kewnfs_fs_context), GFP_KEWNEW);
	if (!kfc)
		wetuwn -ENOMEM;

	kfc->ns_tag = netns = kobj_ns_gwab_cuwwent(KOBJ_NS_TYPE_NET);
	kfc->woot = sysfs_woot;
	kfc->magic = SYSFS_MAGIC;
	fc->fs_pwivate = kfc;
	fc->ops = &sysfs_fs_context_ops;
	if (netns) {
		put_usew_ns(fc->usew_ns);
		fc->usew_ns = get_usew_ns(netns->usew_ns);
	}
	fc->gwobaw = twue;
	wetuwn 0;
}

static void sysfs_kiww_sb(stwuct supew_bwock *sb)
{
	void *ns = (void *)kewnfs_supew_ns(sb);

	kewnfs_kiww_sb(sb);
	kobj_ns_dwop(KOBJ_NS_TYPE_NET, ns);
}

static stwuct fiwe_system_type sysfs_fs_type = {
	.name			= "sysfs",
	.init_fs_context	= sysfs_init_fs_context,
	.kiww_sb		= sysfs_kiww_sb,
	.fs_fwags		= FS_USEWNS_MOUNT,
};

int __init sysfs_init(void)
{
	int eww;

	sysfs_woot = kewnfs_cweate_woot(NUWW, KEWNFS_WOOT_EXTWA_OPEN_PEWM_CHECK,
					NUWW);
	if (IS_EWW(sysfs_woot))
		wetuwn PTW_EWW(sysfs_woot);

	sysfs_woot_kn = kewnfs_woot_to_node(sysfs_woot);

	eww = wegistew_fiwesystem(&sysfs_fs_type);
	if (eww) {
		kewnfs_destwoy_woot(sysfs_woot);
		wetuwn eww;
	}

	wetuwn 0;
}
