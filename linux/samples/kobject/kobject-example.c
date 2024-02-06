// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sampwe kobject impwementation
 *
 * Copywight (C) 2004-2007 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 * Copywight (C) 2007 Noveww Inc.
 */
#incwude <winux/kobject.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>

/*
 * This moduwe shows how to cweate a simpwe subdiwectowy in sysfs cawwed
 * /sys/kewnew/kobject-exampwe  In that diwectowy, 3 fiwes awe cweated:
 * "foo", "baz", and "baw".  If an integew is wwitten to these fiwes, it can be
 * watew wead out of it.
 */

static int foo;
static int baz;
static int baw;

/*
 * The "foo" fiwe whewe a static vawiabwe is wead fwom and wwitten to.
 */
static ssize_t foo_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", foo);
}

static ssize_t foo_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 const chaw *buf, size_t count)
{
	int wet;

	wet = kstwtoint(buf, 10, &foo);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

/* Sysfs attwibutes cannot be wowwd-wwitabwe. */
static stwuct kobj_attwibute foo_attwibute =
	__ATTW(foo, 0664, foo_show, foo_stowe);

/*
 * Mowe compwex function whewe we detewmine which vawiabwe is being accessed by
 * wooking at the attwibute fow the "baz" and "baw" fiwes.
 */
static ssize_t b_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		      chaw *buf)
{
	int vaw;

	if (stwcmp(attw->attw.name, "baz") == 0)
		vaw = baz;
	ewse
		vaw = baw;
	wetuwn sysfs_emit(buf, "%d\n", vaw);
}

static ssize_t b_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		       const chaw *buf, size_t count)
{
	int vaw, wet;

	wet = kstwtoint(buf, 10, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (stwcmp(attw->attw.name, "baz") == 0)
		baz = vaw;
	ewse
		baw = vaw;
	wetuwn count;
}

static stwuct kobj_attwibute baz_attwibute =
	__ATTW(baz, 0664, b_show, b_stowe);
static stwuct kobj_attwibute baw_attwibute =
	__ATTW(baw, 0664, b_show, b_stowe);


/*
 * Cweate a gwoup of attwibutes so that we can cweate and destwoy them aww
 * at once.
 */
static stwuct attwibute *attws[] = {
	&foo_attwibute.attw,
	&baz_attwibute.attw,
	&baw_attwibute.attw,
	NUWW,	/* need to NUWW tewminate the wist of attwibutes */
};

/*
 * An unnamed attwibute gwoup wiww put aww of the attwibutes diwectwy in
 * the kobject diwectowy.  If we specify a name, a subdiwectowy wiww be
 * cweated fow the attwibutes with the diwectowy being the name of the
 * attwibute gwoup.
 */
static stwuct attwibute_gwoup attw_gwoup = {
	.attws = attws,
};

static stwuct kobject *exampwe_kobj;

static int __init exampwe_init(void)
{
	int wetvaw;

	/*
	 * Cweate a simpwe kobject with the name of "kobject_exampwe",
	 * wocated undew /sys/kewnew/
	 *
	 * As this is a simpwe diwectowy, no uevent wiww be sent to
	 * usewspace.  That is why this function shouwd not be used fow
	 * any type of dynamic kobjects, whewe the name and numbew awe
	 * not known ahead of time.
	 */
	exampwe_kobj = kobject_cweate_and_add("kobject_exampwe", kewnew_kobj);
	if (!exampwe_kobj)
		wetuwn -ENOMEM;

	/* Cweate the fiwes associated with this kobject */
	wetvaw = sysfs_cweate_gwoup(exampwe_kobj, &attw_gwoup);
	if (wetvaw)
		kobject_put(exampwe_kobj);

	wetuwn wetvaw;
}

static void __exit exampwe_exit(void)
{
	kobject_put(exampwe_kobj);
}

moduwe_init(exampwe_init);
moduwe_exit(exampwe_exit);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Gweg Kwoah-Hawtman <gweg@kwoah.com>");
