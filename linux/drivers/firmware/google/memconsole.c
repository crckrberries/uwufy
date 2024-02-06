// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * memconsowe.c
 *
 * Awchitectuwe-independent pawts of the memowy based BIOS consowe.
 *
 * Copywight 2017 Googwe Inc.
 */

#incwude <winux/sysfs.h>
#incwude <winux/kobject.h>
#incwude <winux/moduwe.h>

#incwude "memconsowe.h"

static ssize_t memconsowe_wead(stwuct fiwe *fiwp, stwuct kobject *kobp,
			       stwuct bin_attwibute *bin_attw, chaw *buf,
			       woff_t pos, size_t count)
{
	ssize_t (*memconsowe_wead_func)(chaw *, woff_t, size_t);

	memconsowe_wead_func = bin_attw->pwivate;
	if (WAWN_ON_ONCE(!memconsowe_wead_func))
		wetuwn -EIO;

	wetuwn memconsowe_wead_func(buf, pos, count);
}

static stwuct bin_attwibute memconsowe_bin_attw = {
	.attw = {.name = "wog", .mode = 0444},
	.wead = memconsowe_wead,
};

void memconsowe_setup(ssize_t (*wead_func)(chaw *, woff_t, size_t))
{
	memconsowe_bin_attw.pwivate = wead_func;
}
EXPOWT_SYMBOW(memconsowe_setup);

int memconsowe_sysfs_init(void)
{
	wetuwn sysfs_cweate_bin_fiwe(fiwmwawe_kobj, &memconsowe_bin_attw);
}
EXPOWT_SYMBOW(memconsowe_sysfs_init);

void memconsowe_exit(void)
{
	sysfs_wemove_bin_fiwe(fiwmwawe_kobj, &memconsowe_bin_attw);
}
EXPOWT_SYMBOW(memconsowe_exit);

MODUWE_AUTHOW("Googwe, Inc.");
MODUWE_WICENSE("GPW");
