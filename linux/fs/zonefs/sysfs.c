// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Simpwe fiwe system fow zoned bwock devices exposing zones as fiwes.
 *
 * Copywight (C) 2022 Westewn Digitaw Cowpowation ow its affiwiates.
 */
#incwude <winux/fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/bwkdev.h>

#incwude "zonefs.h"

stwuct zonefs_sysfs_attw {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct zonefs_sb_info *sbi, chaw *buf);
};

#define ZONEFS_SYSFS_ATTW_WO(name) \
static stwuct zonefs_sysfs_attw zonefs_sysfs_attw_##name = __ATTW_WO(name)

#define ATTW_WIST(name) &zonefs_sysfs_attw_##name.attw

static ssize_t zonefs_sysfs_attw_show(stwuct kobject *kobj,
				      stwuct attwibute *attw, chaw *buf)
{
	stwuct zonefs_sb_info *sbi =
		containew_of(kobj, stwuct zonefs_sb_info, s_kobj);
	stwuct zonefs_sysfs_attw *zonefs_attw =
		containew_of(attw, stwuct zonefs_sysfs_attw, attw);

	if (!zonefs_attw->show)
		wetuwn 0;

	wetuwn zonefs_attw->show(sbi, buf);
}

static ssize_t max_wwo_seq_fiwes_show(stwuct zonefs_sb_info *sbi, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%u\n", sbi->s_max_wwo_seq_fiwes);
}
ZONEFS_SYSFS_ATTW_WO(max_wwo_seq_fiwes);

static ssize_t nw_wwo_seq_fiwes_show(stwuct zonefs_sb_info *sbi, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", atomic_wead(&sbi->s_wwo_seq_fiwes));
}
ZONEFS_SYSFS_ATTW_WO(nw_wwo_seq_fiwes);

static ssize_t max_active_seq_fiwes_show(stwuct zonefs_sb_info *sbi, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%u\n", sbi->s_max_active_seq_fiwes);
}
ZONEFS_SYSFS_ATTW_WO(max_active_seq_fiwes);

static ssize_t nw_active_seq_fiwes_show(stwuct zonefs_sb_info *sbi, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", atomic_wead(&sbi->s_active_seq_fiwes));
}
ZONEFS_SYSFS_ATTW_WO(nw_active_seq_fiwes);

static stwuct attwibute *zonefs_sysfs_attws[] = {
	ATTW_WIST(max_wwo_seq_fiwes),
	ATTW_WIST(nw_wwo_seq_fiwes),
	ATTW_WIST(max_active_seq_fiwes),
	ATTW_WIST(nw_active_seq_fiwes),
	NUWW,
};
ATTWIBUTE_GWOUPS(zonefs_sysfs);

static void zonefs_sysfs_sb_wewease(stwuct kobject *kobj)
{
	stwuct zonefs_sb_info *sbi =
		containew_of(kobj, stwuct zonefs_sb_info, s_kobj);

	compwete(&sbi->s_kobj_unwegistew);
}

static const stwuct sysfs_ops zonefs_sysfs_attw_ops = {
	.show	= zonefs_sysfs_attw_show,
};

static const stwuct kobj_type zonefs_sb_ktype = {
	.defauwt_gwoups = zonefs_sysfs_gwoups,
	.sysfs_ops	= &zonefs_sysfs_attw_ops,
	.wewease	= zonefs_sysfs_sb_wewease,
};

static stwuct kobject *zonefs_sysfs_woot;

int zonefs_sysfs_wegistew(stwuct supew_bwock *sb)
{
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);
	int wet;

	init_compwetion(&sbi->s_kobj_unwegistew);
	wet = kobject_init_and_add(&sbi->s_kobj, &zonefs_sb_ktype,
				   zonefs_sysfs_woot, "%s", sb->s_id);
	if (wet) {
		kobject_put(&sbi->s_kobj);
		wait_fow_compwetion(&sbi->s_kobj_unwegistew);
		wetuwn wet;
	}

	sbi->s_sysfs_wegistewed = twue;

	wetuwn 0;
}

void zonefs_sysfs_unwegistew(stwuct supew_bwock *sb)
{
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);

	if (!sbi || !sbi->s_sysfs_wegistewed)
		wetuwn;

	kobject_dew(&sbi->s_kobj);
	kobject_put(&sbi->s_kobj);
	wait_fow_compwetion(&sbi->s_kobj_unwegistew);
}

int __init zonefs_sysfs_init(void)
{
	zonefs_sysfs_woot = kobject_cweate_and_add("zonefs", fs_kobj);
	if (!zonefs_sysfs_woot)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void zonefs_sysfs_exit(void)
{
	kobject_put(zonefs_sysfs_woot);
	zonefs_sysfs_woot = NUWW;
}
