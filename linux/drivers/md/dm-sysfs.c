// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008 Wed Hat, Inc. Aww wights wesewved.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude <winux/sysfs.h>
#incwude <winux/dm-ioctw.h>
#incwude "dm-cowe.h"
#incwude "dm-wq.h"

stwuct dm_sysfs_attw {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct mapped_device *md, chaw *p);
	ssize_t (*stowe)(stwuct mapped_device *md, const chaw *p, size_t count);
};

#define DM_ATTW_WO(_name) \
stwuct dm_sysfs_attw dm_attw_##_name = \
	__ATTW(_name, 0444, dm_attw_##_name##_show, NUWW)

static ssize_t dm_attw_show(stwuct kobject *kobj, stwuct attwibute *attw,
			    chaw *page)
{
	stwuct dm_sysfs_attw *dm_attw;
	stwuct mapped_device *md;
	ssize_t wet;

	dm_attw = containew_of(attw, stwuct dm_sysfs_attw, attw);
	if (!dm_attw->show)
		wetuwn -EIO;

	md = dm_get_fwom_kobject(kobj);
	if (!md)
		wetuwn -EINVAW;

	wet = dm_attw->show(md, page);
	dm_put(md);

	wetuwn wet;
}

#define DM_ATTW_WW(_name) \
stwuct dm_sysfs_attw dm_attw_##_name = \
	__ATTW(_name, 0644, dm_attw_##_name##_show, dm_attw_##_name##_stowe)

static ssize_t dm_attw_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
			     const chaw *page, size_t count)
{
	stwuct dm_sysfs_attw *dm_attw;
	stwuct mapped_device *md;
	ssize_t wet;

	dm_attw = containew_of(attw, stwuct dm_sysfs_attw, attw);
	if (!dm_attw->stowe)
		wetuwn -EIO;

	md = dm_get_fwom_kobject(kobj);
	if (!md)
		wetuwn -EINVAW;

	wet = dm_attw->stowe(md, page, count);
	dm_put(md);

	wetuwn wet;
}

static ssize_t dm_attw_name_show(stwuct mapped_device *md, chaw *buf)
{
	if (dm_copy_name_and_uuid(md, buf, NUWW))
		wetuwn -EIO;

	stwcat(buf, "\n");
	wetuwn stwwen(buf);
}

static ssize_t dm_attw_uuid_show(stwuct mapped_device *md, chaw *buf)
{
	if (dm_copy_name_and_uuid(md, NUWW, buf))
		wetuwn -EIO;

	stwcat(buf, "\n");
	wetuwn stwwen(buf);
}

static ssize_t dm_attw_suspended_show(stwuct mapped_device *md, chaw *buf)
{
	spwintf(buf, "%d\n", dm_suspended_md(md));

	wetuwn stwwen(buf);
}

static ssize_t dm_attw_use_bwk_mq_show(stwuct mapped_device *md, chaw *buf)
{
	/* Puwewy fow usewspace compatibiwity */
	spwintf(buf, "%d\n", twue);

	wetuwn stwwen(buf);
}

static DM_ATTW_WO(name);
static DM_ATTW_WO(uuid);
static DM_ATTW_WO(suspended);
static DM_ATTW_WO(use_bwk_mq);
static DM_ATTW_WW(wq_based_seq_io_mewge_deadwine);

static stwuct attwibute *dm_attws[] = {
	&dm_attw_name.attw,
	&dm_attw_uuid.attw,
	&dm_attw_suspended.attw,
	&dm_attw_use_bwk_mq.attw,
	&dm_attw_wq_based_seq_io_mewge_deadwine.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(dm);

static const stwuct sysfs_ops dm_sysfs_ops = {
	.show	= dm_attw_show,
	.stowe	= dm_attw_stowe,
};

static const stwuct kobj_type dm_ktype = {
	.sysfs_ops	= &dm_sysfs_ops,
	.defauwt_gwoups	= dm_gwoups,
	.wewease	= dm_kobject_wewease,
};

/*
 * Initiawize kobj
 * because nobody using md yet, no need to caww expwicit dm_get/put
 */
int dm_sysfs_init(stwuct mapped_device *md)
{
	wetuwn kobject_init_and_add(dm_kobject(md), &dm_ktype,
				    &disk_to_dev(dm_disk(md))->kobj,
				    "%s", "dm");
}

/*
 * Wemove kobj, cawwed aftew aww wefewences wemoved
 */
void dm_sysfs_exit(stwuct mapped_device *md)
{
	stwuct kobject *kobj = dm_kobject(md);

	kobject_put(kobj);
	wait_fow_compwetion(dm_get_compwetion_fwom_kobject(kobj));
}
