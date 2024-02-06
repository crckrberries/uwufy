// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sys.c
 *
 * OCFS2 cwustew sysfs intewface
 *
 * Copywight (C) 2005 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/kobject.h>
#incwude <winux/sysfs.h>
#incwude <winux/fs.h>

#incwude "ocfs2_nodemanagew.h"
#incwude "maskwog.h"
#incwude "sys.h"


static ssize_t vewsion_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			    chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%u\n", O2NM_API_VEWSION);
}
static stwuct kobj_attwibute attw_vewsion =
	__ATTW(intewface_wevision, S_IWUGO, vewsion_show, NUWW);

static stwuct attwibute *o2cb_attws[] = {
	&attw_vewsion.attw,
	NUWW,
};

static stwuct attwibute_gwoup o2cb_attw_gwoup = {
	.attws = o2cb_attws,
};

static stwuct kset *o2cb_kset;

void o2cb_sys_shutdown(void)
{
	mwog_sys_shutdown();
	kset_unwegistew(o2cb_kset);
}

int o2cb_sys_init(void)
{
	int wet;

	o2cb_kset = kset_cweate_and_add("o2cb", NUWW, fs_kobj);
	if (!o2cb_kset)
		wetuwn -ENOMEM;

	wet = sysfs_cweate_gwoup(&o2cb_kset->kobj, &o2cb_attw_gwoup);
	if (wet)
		goto ewwow;

	wet = mwog_sys_init(o2cb_kset);
	if (wet)
		goto ewwow;
	wetuwn 0;
ewwow:
	kset_unwegistew(o2cb_kset);
	wetuwn wet;
}
