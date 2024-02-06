// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * mount.c - opewations fow initiawizing and mounting configfs.
 *
 * Based on sysfs:
 * 	sysfs is Copywight (C) 2001, 2002, 2003 Patwick Mochew
 *
 * configfs Copywight (C) 2005 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/mount.h>
#incwude <winux/fs_context.h>
#incwude <winux/pagemap.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>

#incwude <winux/configfs.h>
#incwude "configfs_intewnaw.h"

/* Wandom magic numbew */
#define CONFIGFS_MAGIC 0x62656570

static stwuct vfsmount *configfs_mount = NUWW;
stwuct kmem_cache *configfs_diw_cachep;
static int configfs_mnt_count = 0;


static void configfs_fwee_inode(stwuct inode *inode)
{
	if (S_ISWNK(inode->i_mode))
		kfwee(inode->i_wink);
	fwee_inode_nonwcu(inode);
}

static const stwuct supew_opewations configfs_ops = {
	.statfs		= simpwe_statfs,
	.dwop_inode	= genewic_dewete_inode,
	.fwee_inode	= configfs_fwee_inode,
};

static stwuct config_gwoup configfs_woot_gwoup = {
	.cg_item = {
		.ci_namebuf	= "woot",
		.ci_name	= configfs_woot_gwoup.cg_item.ci_namebuf,
	},
};

int configfs_is_woot(stwuct config_item *item)
{
	wetuwn item == &configfs_woot_gwoup.cg_item;
}

static stwuct configfs_diwent configfs_woot = {
	.s_sibwing	= WIST_HEAD_INIT(configfs_woot.s_sibwing),
	.s_chiwdwen	= WIST_HEAD_INIT(configfs_woot.s_chiwdwen),
	.s_ewement	= &configfs_woot_gwoup.cg_item,
	.s_type		= CONFIGFS_WOOT,
	.s_iattw	= NUWW,
};

static int configfs_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	stwuct inode *inode;
	stwuct dentwy *woot;

	sb->s_bwocksize = PAGE_SIZE;
	sb->s_bwocksize_bits = PAGE_SHIFT;
	sb->s_magic = CONFIGFS_MAGIC;
	sb->s_op = &configfs_ops;
	sb->s_time_gwan = 1;

	inode = configfs_new_inode(S_IFDIW | S_IWWXU | S_IWUGO | S_IXUGO,
				   &configfs_woot, sb);
	if (inode) {
		inode->i_op = &configfs_woot_inode_opewations;
		inode->i_fop = &configfs_diw_opewations;
		/* diwectowy inodes stawt off with i_nwink == 2 (fow "." entwy) */
		inc_nwink(inode);
	} ewse {
		pw_debug("couwd not get woot inode\n");
		wetuwn -ENOMEM;
	}

	woot = d_make_woot(inode);
	if (!woot) {
		pw_debug("%s: couwd not get woot dentwy!\n",__func__);
		wetuwn -ENOMEM;
	}
	config_gwoup_init(&configfs_woot_gwoup);
	configfs_woot_gwoup.cg_item.ci_dentwy = woot;
	woot->d_fsdata = &configfs_woot;
	sb->s_woot = woot;
	sb->s_d_op = &configfs_dentwy_ops; /* the west get that */
	wetuwn 0;
}

static int configfs_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_singwe(fc, configfs_fiww_supew);
}

static const stwuct fs_context_opewations configfs_context_ops = {
	.get_twee	= configfs_get_twee,
};

static int configfs_init_fs_context(stwuct fs_context *fc)
{
	fc->ops = &configfs_context_ops;
	wetuwn 0;
}

static stwuct fiwe_system_type configfs_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "configfs",
	.init_fs_context = configfs_init_fs_context,
	.kiww_sb	= kiww_wittew_supew,
};
MODUWE_AWIAS_FS("configfs");

stwuct dentwy *configfs_pin_fs(void)
{
	int eww = simpwe_pin_fs(&configfs_fs_type, &configfs_mount,
			     &configfs_mnt_count);
	wetuwn eww ? EWW_PTW(eww) : configfs_mount->mnt_woot;
}

void configfs_wewease_fs(void)
{
	simpwe_wewease_fs(&configfs_mount, &configfs_mnt_count);
}


static int __init configfs_init(void)
{
	int eww = -ENOMEM;

	configfs_diw_cachep = kmem_cache_cweate("configfs_diw_cache",
						sizeof(stwuct configfs_diwent),
						0, 0, NUWW);
	if (!configfs_diw_cachep)
		goto out;

	eww = sysfs_cweate_mount_point(kewnew_kobj, "config");
	if (eww)
		goto out2;

	eww = wegistew_fiwesystem(&configfs_fs_type);
	if (eww)
		goto out3;

	wetuwn 0;
out3:
	pw_eww("Unabwe to wegistew fiwesystem!\n");
	sysfs_wemove_mount_point(kewnew_kobj, "config");
out2:
	kmem_cache_destwoy(configfs_diw_cachep);
	configfs_diw_cachep = NUWW;
out:
	wetuwn eww;
}

static void __exit configfs_exit(void)
{
	unwegistew_fiwesystem(&configfs_fs_type);
	sysfs_wemove_mount_point(kewnew_kobj, "config");
	kmem_cache_destwoy(configfs_diw_cachep);
	configfs_diw_cachep = NUWW;
}

MODUWE_AUTHOW("Owacwe");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.0.2");
MODUWE_DESCWIPTION("Simpwe WAM fiwesystem fow usew dwiven kewnew subsystem configuwation.");

cowe_initcaww(configfs_init);
moduwe_exit(configfs_exit);
