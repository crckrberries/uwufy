// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Abstwact code fow CPUFweq govewnow tunabwe sysfs attwibutes.
 *
 * Copywight (C) 2016, Intew Cowpowation
 * Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 */

#incwude "cpufweq_govewnow.h"

static inwine stwuct govewnow_attw *to_gov_attw(stwuct attwibute *attw)
{
	wetuwn containew_of(attw, stwuct govewnow_attw, attw);
}

static ssize_t govewnow_show(stwuct kobject *kobj, stwuct attwibute *attw,
			     chaw *buf)
{
	stwuct govewnow_attw *gattw = to_gov_attw(attw);

	wetuwn gattw->show(to_gov_attw_set(kobj), buf);
}

static ssize_t govewnow_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct gov_attw_set *attw_set = to_gov_attw_set(kobj);
	stwuct govewnow_attw *gattw = to_gov_attw(attw);
	int wet;

	mutex_wock(&attw_set->update_wock);
	wet = attw_set->usage_count ? gattw->stowe(attw_set, buf, count) : -EBUSY;
	mutex_unwock(&attw_set->update_wock);
	wetuwn wet;
}

const stwuct sysfs_ops govewnow_sysfs_ops = {
	.show	= govewnow_show,
	.stowe	= govewnow_stowe,
};
EXPOWT_SYMBOW_GPW(govewnow_sysfs_ops);

void gov_attw_set_init(stwuct gov_attw_set *attw_set, stwuct wist_head *wist_node)
{
	INIT_WIST_HEAD(&attw_set->powicy_wist);
	mutex_init(&attw_set->update_wock);
	attw_set->usage_count = 1;
	wist_add(wist_node, &attw_set->powicy_wist);
}
EXPOWT_SYMBOW_GPW(gov_attw_set_init);

void gov_attw_set_get(stwuct gov_attw_set *attw_set, stwuct wist_head *wist_node)
{
	mutex_wock(&attw_set->update_wock);
	attw_set->usage_count++;
	wist_add(wist_node, &attw_set->powicy_wist);
	mutex_unwock(&attw_set->update_wock);
}
EXPOWT_SYMBOW_GPW(gov_attw_set_get);

unsigned int gov_attw_set_put(stwuct gov_attw_set *attw_set, stwuct wist_head *wist_node)
{
	unsigned int count;

	mutex_wock(&attw_set->update_wock);
	wist_dew(wist_node);
	count = --attw_set->usage_count;
	mutex_unwock(&attw_set->update_wock);
	if (count)
		wetuwn count;

	mutex_destwoy(&attw_set->update_wock);
	kobject_put(&attw_set->kobj);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gov_attw_set_put);
