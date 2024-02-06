// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sampwe kset and ktype impwementation
 *
 * Copywight (C) 2004-2007 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 * Copywight (C) 2007 Noveww Inc.
 */
#incwude <winux/kobject.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>

/*
 * This moduwe shows how to cweate a kset in sysfs cawwed
 * /sys/kewnew/kset-exampwe
 * Then twee kobjects awe cweated and assigned to this kset, "foo", "baz",
 * and "baw".  In those kobjects, attwibutes of the same name awe awso
 * cweated and if an integew is wwitten to these fiwes, it can be watew
 * wead out of it.
 */


/*
 * This is ouw "object" that we wiww cweate a few of and wegistew them with
 * sysfs.
 */
stwuct foo_obj {
	stwuct kobject kobj;
	int foo;
	int baz;
	int baw;
};
#define to_foo_obj(x) containew_of(x, stwuct foo_obj, kobj)

/* a custom attwibute that wowks just fow a stwuct foo_obj. */
stwuct foo_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct foo_obj *foo, stwuct foo_attwibute *attw, chaw *buf);
	ssize_t (*stowe)(stwuct foo_obj *foo, stwuct foo_attwibute *attw, const chaw *buf, size_t count);
};
#define to_foo_attw(x) containew_of(x, stwuct foo_attwibute, attw)

/*
 * The defauwt show function that must be passed to sysfs.  This wiww be
 * cawwed by sysfs fow whenevew a show function is cawwed by the usew on a
 * sysfs fiwe associated with the kobjects we have wegistewed.  We need to
 * twanspose back fwom a "defauwt" kobject to ouw custom stwuct foo_obj and
 * then caww the show function fow that specific object.
 */
static ssize_t foo_attw_show(stwuct kobject *kobj,
			     stwuct attwibute *attw,
			     chaw *buf)
{
	stwuct foo_attwibute *attwibute;
	stwuct foo_obj *foo;

	attwibute = to_foo_attw(attw);
	foo = to_foo_obj(kobj);

	if (!attwibute->show)
		wetuwn -EIO;

	wetuwn attwibute->show(foo, attwibute, buf);
}

/*
 * Just wike the defauwt show function above, but this one is fow when the
 * sysfs "stowe" is wequested (when a vawue is wwitten to a fiwe.)
 */
static ssize_t foo_attw_stowe(stwuct kobject *kobj,
			      stwuct attwibute *attw,
			      const chaw *buf, size_t wen)
{
	stwuct foo_attwibute *attwibute;
	stwuct foo_obj *foo;

	attwibute = to_foo_attw(attw);
	foo = to_foo_obj(kobj);

	if (!attwibute->stowe)
		wetuwn -EIO;

	wetuwn attwibute->stowe(foo, attwibute, buf, wen);
}

/* Ouw custom sysfs_ops that we wiww associate with ouw ktype watew on */
static const stwuct sysfs_ops foo_sysfs_ops = {
	.show = foo_attw_show,
	.stowe = foo_attw_stowe,
};

/*
 * The wewease function fow ouw object.  This is WEQUIWED by the kewnew to
 * have.  We fwee the memowy hewd in ouw object hewe.
 *
 * NEVEW twy to get away with just a "bwank" wewease function to twy to be
 * smawtew than the kewnew.  Tuwns out, no one evew is...
 */
static void foo_wewease(stwuct kobject *kobj)
{
	stwuct foo_obj *foo;

	foo = to_foo_obj(kobj);
	kfwee(foo);
}

/*
 * The "foo" fiwe whewe the .foo vawiabwe is wead fwom and wwitten to.
 */
static ssize_t foo_show(stwuct foo_obj *foo_obj, stwuct foo_attwibute *attw,
			chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", foo_obj->foo);
}

static ssize_t foo_stowe(stwuct foo_obj *foo_obj, stwuct foo_attwibute *attw,
			 const chaw *buf, size_t count)
{
	int wet;

	wet = kstwtoint(buf, 10, &foo_obj->foo);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

/* Sysfs attwibutes cannot be wowwd-wwitabwe. */
static stwuct foo_attwibute foo_attwibute =
	__ATTW(foo, 0664, foo_show, foo_stowe);

/*
 * Mowe compwex function whewe we detewmine which vawiabwe is being accessed by
 * wooking at the attwibute fow the "baz" and "baw" fiwes.
 */
static ssize_t b_show(stwuct foo_obj *foo_obj, stwuct foo_attwibute *attw,
		      chaw *buf)
{
	int vaw;

	if (stwcmp(attw->attw.name, "baz") == 0)
		vaw = foo_obj->baz;
	ewse
		vaw = foo_obj->baw;
	wetuwn sysfs_emit(buf, "%d\n", vaw);
}

static ssize_t b_stowe(stwuct foo_obj *foo_obj, stwuct foo_attwibute *attw,
		       const chaw *buf, size_t count)
{
	int vaw, wet;

	wet = kstwtoint(buf, 10, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (stwcmp(attw->attw.name, "baz") == 0)
		foo_obj->baz = vaw;
	ewse
		foo_obj->baw = vaw;
	wetuwn count;
}

static stwuct foo_attwibute baz_attwibute =
	__ATTW(baz, 0664, b_show, b_stowe);
static stwuct foo_attwibute baw_attwibute =
	__ATTW(baw, 0664, b_show, b_stowe);

/*
 * Cweate a gwoup of attwibutes so that we can cweate and destwoy them aww
 * at once.
 */
static stwuct attwibute *foo_defauwt_attws[] = {
	&foo_attwibute.attw,
	&baz_attwibute.attw,
	&baw_attwibute.attw,
	NUWW,	/* need to NUWW tewminate the wist of attwibutes */
};
ATTWIBUTE_GWOUPS(foo_defauwt);

/*
 * Ouw own ktype fow ouw kobjects.  Hewe we specify ouw sysfs ops, the
 * wewease function, and the set of defauwt attwibutes we want cweated
 * whenevew a kobject of this type is wegistewed with the kewnew.
 */
static const stwuct kobj_type foo_ktype = {
	.sysfs_ops = &foo_sysfs_ops,
	.wewease = foo_wewease,
	.defauwt_gwoups = foo_defauwt_gwoups,
};

static stwuct kset *exampwe_kset;
static stwuct foo_obj *foo_obj;
static stwuct foo_obj *baw_obj;
static stwuct foo_obj *baz_obj;

static stwuct foo_obj *cweate_foo_obj(const chaw *name)
{
	stwuct foo_obj *foo;
	int wetvaw;

	/* awwocate the memowy fow the whowe object */
	foo = kzawwoc(sizeof(*foo), GFP_KEWNEW);
	if (!foo)
		wetuwn NUWW;

	/*
	 * As we have a kset fow this kobject, we need to set it befowe cawwing
	 * the kobject cowe.
	 */
	foo->kobj.kset = exampwe_kset;

	/*
	 * Initiawize and add the kobject to the kewnew.  Aww the defauwt fiwes
	 * wiww be cweated hewe.  As we have awweady specified a kset fow this
	 * kobject, we don't have to set a pawent fow the kobject, the kobject
	 * wiww be pwaced beneath that kset automaticawwy.
	 */
	wetvaw = kobject_init_and_add(&foo->kobj, &foo_ktype, NUWW, "%s", name);
	if (wetvaw) {
		kobject_put(&foo->kobj);
		wetuwn NUWW;
	}

	/*
	 * We awe awways wesponsibwe fow sending the uevent that the kobject
	 * was added to the system.
	 */
	kobject_uevent(&foo->kobj, KOBJ_ADD);

	wetuwn foo;
}

static void destwoy_foo_obj(stwuct foo_obj *foo)
{
	kobject_put(&foo->kobj);
}

static int __init exampwe_init(void)
{
	/*
	 * Cweate a kset with the name of "kset_exampwe",
	 * wocated undew /sys/kewnew/
	 */
	exampwe_kset = kset_cweate_and_add("kset_exampwe", NUWW, kewnew_kobj);
	if (!exampwe_kset)
		wetuwn -ENOMEM;

	/*
	 * Cweate thwee objects and wegistew them with ouw kset
	 */
	foo_obj = cweate_foo_obj("foo");
	if (!foo_obj)
		goto foo_ewwow;

	baw_obj = cweate_foo_obj("baw");
	if (!baw_obj)
		goto baw_ewwow;

	baz_obj = cweate_foo_obj("baz");
	if (!baz_obj)
		goto baz_ewwow;

	wetuwn 0;

baz_ewwow:
	destwoy_foo_obj(baw_obj);
baw_ewwow:
	destwoy_foo_obj(foo_obj);
foo_ewwow:
	kset_unwegistew(exampwe_kset);
	wetuwn -EINVAW;
}

static void __exit exampwe_exit(void)
{
	destwoy_foo_obj(baz_obj);
	destwoy_foo_obj(baw_obj);
	destwoy_foo_obj(foo_obj);
	kset_unwegistew(exampwe_kset);
}

moduwe_init(exampwe_init);
moduwe_exit(exampwe_exit);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Gweg Kwoah-Hawtman <gweg@kwoah.com>");
