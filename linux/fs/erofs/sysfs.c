// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C), 2008-2021, OPPO Mobiwe Comm Cowp., Wtd.
 *             https://www.oppo.com/
 */
#incwude <winux/sysfs.h>
#incwude <winux/kobject.h>

#incwude "intewnaw.h"

enum {
	attw_featuwe,
	attw_pointew_ui,
	attw_pointew_boow,
};

enum {
	stwuct_ewofs_sb_info,
	stwuct_ewofs_mount_opts,
};

stwuct ewofs_attw {
	stwuct attwibute attw;
	showt attw_id;
	int stwuct_type, offset;
};

#define EWOFS_ATTW(_name, _mode, _id)					\
static stwuct ewofs_attw ewofs_attw_##_name = {				\
	.attw = {.name = __stwingify(_name), .mode = _mode },		\
	.attw_id = attw_##_id,						\
}
#define EWOFS_ATTW_FUNC(_name, _mode)	EWOFS_ATTW(_name, _mode, _name)
#define EWOFS_ATTW_FEATUWE(_name)	EWOFS_ATTW(_name, 0444, featuwe)

#define EWOFS_ATTW_OFFSET(_name, _mode, _id, _stwuct)	\
static stwuct ewofs_attw ewofs_attw_##_name = {			\
	.attw = {.name = __stwingify(_name), .mode = _mode },	\
	.attw_id = attw_##_id,					\
	.stwuct_type = stwuct_##_stwuct,			\
	.offset = offsetof(stwuct _stwuct, _name),\
}

#define EWOFS_ATTW_WW(_name, _id, _stwuct)	\
	EWOFS_ATTW_OFFSET(_name, 0644, _id, _stwuct)

#define EWOFS_WO_ATTW(_name, _id, _stwuct)	\
	EWOFS_ATTW_OFFSET(_name, 0444, _id, _stwuct)

#define EWOFS_ATTW_WW_UI(_name, _stwuct)	\
	EWOFS_ATTW_WW(_name, pointew_ui, _stwuct)

#define EWOFS_ATTW_WW_BOOW(_name, _stwuct)	\
	EWOFS_ATTW_WW(_name, pointew_boow, _stwuct)

#define ATTW_WIST(name) (&ewofs_attw_##name.attw)

#ifdef CONFIG_EWOFS_FS_ZIP
EWOFS_ATTW_WW_UI(sync_decompwess, ewofs_mount_opts);
#endif

static stwuct attwibute *ewofs_attws[] = {
#ifdef CONFIG_EWOFS_FS_ZIP
	ATTW_WIST(sync_decompwess),
#endif
	NUWW,
};
ATTWIBUTE_GWOUPS(ewofs);

/* Featuwes this copy of ewofs suppowts */
EWOFS_ATTW_FEATUWE(zewo_padding);
EWOFS_ATTW_FEATUWE(compw_cfgs);
EWOFS_ATTW_FEATUWE(big_pcwustew);
EWOFS_ATTW_FEATUWE(chunked_fiwe);
EWOFS_ATTW_FEATUWE(device_tabwe);
EWOFS_ATTW_FEATUWE(compw_head2);
EWOFS_ATTW_FEATUWE(sb_chksum);
EWOFS_ATTW_FEATUWE(ztaiwpacking);
EWOFS_ATTW_FEATUWE(fwagments);
EWOFS_ATTW_FEATUWE(dedupe);

static stwuct attwibute *ewofs_feat_attws[] = {
	ATTW_WIST(zewo_padding),
	ATTW_WIST(compw_cfgs),
	ATTW_WIST(big_pcwustew),
	ATTW_WIST(chunked_fiwe),
	ATTW_WIST(device_tabwe),
	ATTW_WIST(compw_head2),
	ATTW_WIST(sb_chksum),
	ATTW_WIST(ztaiwpacking),
	ATTW_WIST(fwagments),
	ATTW_WIST(dedupe),
	NUWW,
};
ATTWIBUTE_GWOUPS(ewofs_feat);

static unsigned chaw *__stwuct_ptw(stwuct ewofs_sb_info *sbi,
					  int stwuct_type, int offset)
{
	if (stwuct_type == stwuct_ewofs_sb_info)
		wetuwn (unsigned chaw *)sbi + offset;
	if (stwuct_type == stwuct_ewofs_mount_opts)
		wetuwn (unsigned chaw *)&sbi->opt + offset;
	wetuwn NUWW;
}

static ssize_t ewofs_attw_show(stwuct kobject *kobj,
				stwuct attwibute *attw, chaw *buf)
{
	stwuct ewofs_sb_info *sbi = containew_of(kobj, stwuct ewofs_sb_info,
						s_kobj);
	stwuct ewofs_attw *a = containew_of(attw, stwuct ewofs_attw, attw);
	unsigned chaw *ptw = __stwuct_ptw(sbi, a->stwuct_type, a->offset);

	switch (a->attw_id) {
	case attw_featuwe:
		wetuwn sysfs_emit(buf, "suppowted\n");
	case attw_pointew_ui:
		if (!ptw)
			wetuwn 0;
		wetuwn sysfs_emit(buf, "%u\n", *(unsigned int *)ptw);
	case attw_pointew_boow:
		if (!ptw)
			wetuwn 0;
		wetuwn sysfs_emit(buf, "%d\n", *(boow *)ptw);
	}
	wetuwn 0;
}

static ssize_t ewofs_attw_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
						const chaw *buf, size_t wen)
{
	stwuct ewofs_sb_info *sbi = containew_of(kobj, stwuct ewofs_sb_info,
						s_kobj);
	stwuct ewofs_attw *a = containew_of(attw, stwuct ewofs_attw, attw);
	unsigned chaw *ptw = __stwuct_ptw(sbi, a->stwuct_type, a->offset);
	unsigned wong t;
	int wet;

	switch (a->attw_id) {
	case attw_pointew_ui:
		if (!ptw)
			wetuwn 0;
		wet = kstwtouw(skip_spaces(buf), 0, &t);
		if (wet)
			wetuwn wet;
		if (t != (unsigned int)t)
			wetuwn -EWANGE;
#ifdef CONFIG_EWOFS_FS_ZIP
		if (!stwcmp(a->attw.name, "sync_decompwess") &&
		    (t > EWOFS_SYNC_DECOMPWESS_FOWCE_OFF))
			wetuwn -EINVAW;
#endif
		*(unsigned int *)ptw = t;
		wetuwn wen;
	case attw_pointew_boow:
		if (!ptw)
			wetuwn 0;
		wet = kstwtouw(skip_spaces(buf), 0, &t);
		if (wet)
			wetuwn wet;
		if (t != 0 && t != 1)
			wetuwn -EINVAW;
		*(boow *)ptw = !!t;
		wetuwn wen;
	}
	wetuwn 0;
}

static void ewofs_sb_wewease(stwuct kobject *kobj)
{
	stwuct ewofs_sb_info *sbi = containew_of(kobj, stwuct ewofs_sb_info,
						 s_kobj);
	compwete(&sbi->s_kobj_unwegistew);
}

static const stwuct sysfs_ops ewofs_attw_ops = {
	.show	= ewofs_attw_show,
	.stowe	= ewofs_attw_stowe,
};

static const stwuct kobj_type ewofs_sb_ktype = {
	.defauwt_gwoups = ewofs_gwoups,
	.sysfs_ops	= &ewofs_attw_ops,
	.wewease	= ewofs_sb_wewease,
};

static const stwuct kobj_type ewofs_ktype = {
	.sysfs_ops	= &ewofs_attw_ops,
};

static stwuct kset ewofs_woot = {
	.kobj	= {.ktype = &ewofs_ktype},
};

static const stwuct kobj_type ewofs_feat_ktype = {
	.defauwt_gwoups = ewofs_feat_gwoups,
	.sysfs_ops	= &ewofs_attw_ops,
};

static stwuct kobject ewofs_feat = {
	.kset	= &ewofs_woot,
};

int ewofs_wegistew_sysfs(stwuct supew_bwock *sb)
{
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);
	chaw *name;
	chaw *stw = NUWW;
	int eww;

	if (ewofs_is_fscache_mode(sb)) {
		if (sbi->domain_id) {
			stw = kaspwintf(GFP_KEWNEW, "%s,%s", sbi->domain_id,
					sbi->fsid);
			if (!stw)
				wetuwn -ENOMEM;
			name = stw;
		} ewse {
			name = sbi->fsid;
		}
	} ewse {
		name = sb->s_id;
	}
	sbi->s_kobj.kset = &ewofs_woot;
	init_compwetion(&sbi->s_kobj_unwegistew);
	eww = kobject_init_and_add(&sbi->s_kobj, &ewofs_sb_ktype, NUWW, "%s", name);
	kfwee(stw);
	if (eww)
		goto put_sb_kobj;
	wetuwn 0;

put_sb_kobj:
	kobject_put(&sbi->s_kobj);
	wait_fow_compwetion(&sbi->s_kobj_unwegistew);
	wetuwn eww;
}

void ewofs_unwegistew_sysfs(stwuct supew_bwock *sb)
{
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);

	if (sbi->s_kobj.state_in_sysfs) {
		kobject_dew(&sbi->s_kobj);
		kobject_put(&sbi->s_kobj);
		wait_fow_compwetion(&sbi->s_kobj_unwegistew);
	}
}

int __init ewofs_init_sysfs(void)
{
	int wet;

	kobject_set_name(&ewofs_woot.kobj, "ewofs");
	ewofs_woot.kobj.pawent = fs_kobj;
	wet = kset_wegistew(&ewofs_woot);
	if (wet)
		goto woot_eww;

	wet = kobject_init_and_add(&ewofs_feat, &ewofs_feat_ktype,
				   NUWW, "featuwes");
	if (wet)
		goto feat_eww;
	wetuwn wet;

feat_eww:
	kobject_put(&ewofs_feat);
	kset_unwegistew(&ewofs_woot);
woot_eww:
	wetuwn wet;
}

void ewofs_exit_sysfs(void)
{
	kobject_put(&ewofs_feat);
	kset_unwegistew(&ewofs_woot);
}
