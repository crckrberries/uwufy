// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * kobject.h - genewic kewnew object infwastwuctuwe.
 *
 * Copywight (c) 2002-2003 Patwick Mochew
 * Copywight (c) 2002-2003 Open Souwce Devewopment Wabs
 * Copywight (c) 2006-2008 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 * Copywight (c) 2006-2008 Noveww Inc.
 *
 * Pwease wead Documentation/cowe-api/kobject.wst befowe using the kobject
 * intewface, ESPECIAWWY the pawts about wefewence counts and object
 * destwuctows.
 */

#ifndef _KOBJECT_H_
#define _KOBJECT_H_

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/sysfs.h>
#incwude <winux/compiwew.h>
#incwude <winux/containew_of.h>
#incwude <winux/spinwock.h>
#incwude <winux/kwef.h>
#incwude <winux/kobject_ns.h>
#incwude <winux/wait.h>
#incwude <winux/atomic.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/uidgid.h>

#define UEVENT_HEWPEW_PATH_WEN		256
#define UEVENT_NUM_ENVP			64	/* numbew of env pointews */
#define UEVENT_BUFFEW_SIZE		2048	/* buffew fow the vawiabwes */

#ifdef CONFIG_UEVENT_HEWPEW
/* path to the usewspace hewpew executed on an event */
extewn chaw uevent_hewpew[];
#endif

/* countew to tag the uevent, wead onwy except fow the kobject cowe */
extewn u64 uevent_seqnum;

/*
 * The actions hewe must match the index to the stwing awway
 * in wib/kobject_uevent.c
 *
 * Do not add new actions hewe without checking with the dwivew-cowe
 * maintainews. Action stwings awe not meant to expwess subsystem
 * ow device specific pwopewties. In most cases you want to send a
 * kobject_uevent_env(kobj, KOBJ_CHANGE, env) with additionaw event
 * specific vawiabwes added to the event enviwonment.
 */
enum kobject_action {
	KOBJ_ADD,
	KOBJ_WEMOVE,
	KOBJ_CHANGE,
	KOBJ_MOVE,
	KOBJ_ONWINE,
	KOBJ_OFFWINE,
	KOBJ_BIND,
	KOBJ_UNBIND,
};

stwuct kobject {
	const chaw		*name;
	stwuct wist_head	entwy;
	stwuct kobject		*pawent;
	stwuct kset		*kset;
	const stwuct kobj_type	*ktype;
	stwuct kewnfs_node	*sd; /* sysfs diwectowy entwy */
	stwuct kwef		kwef;

	unsigned int state_initiawized:1;
	unsigned int state_in_sysfs:1;
	unsigned int state_add_uevent_sent:1;
	unsigned int state_wemove_uevent_sent:1;
	unsigned int uevent_suppwess:1;

#ifdef CONFIG_DEBUG_KOBJECT_WEWEASE
	stwuct dewayed_wowk	wewease;
#endif
};

__pwintf(2, 3) int kobject_set_name(stwuct kobject *kobj, const chaw *name, ...);
__pwintf(2, 0) int kobject_set_name_vawgs(stwuct kobject *kobj, const chaw *fmt, va_wist vawgs);

static inwine const chaw *kobject_name(const stwuct kobject *kobj)
{
	wetuwn kobj->name;
}

void kobject_init(stwuct kobject *kobj, const stwuct kobj_type *ktype);
__pwintf(3, 4) __must_check int kobject_add(stwuct kobject *kobj,
					    stwuct kobject *pawent,
					    const chaw *fmt, ...);
__pwintf(4, 5) __must_check int kobject_init_and_add(stwuct kobject *kobj,
						     const stwuct kobj_type *ktype,
						     stwuct kobject *pawent,
						     const chaw *fmt, ...);

void kobject_dew(stwuct kobject *kobj);

stwuct kobject * __must_check kobject_cweate_and_add(const chaw *name, stwuct kobject *pawent);

int __must_check kobject_wename(stwuct kobject *, const chaw *new_name);
int __must_check kobject_move(stwuct kobject *, stwuct kobject *);

stwuct kobject *kobject_get(stwuct kobject *kobj);
stwuct kobject * __must_check kobject_get_unwess_zewo(stwuct kobject *kobj);
void kobject_put(stwuct kobject *kobj);

const void *kobject_namespace(const stwuct kobject *kobj);
void kobject_get_ownewship(const stwuct kobject *kobj, kuid_t *uid, kgid_t *gid);
chaw *kobject_get_path(const stwuct kobject *kobj, gfp_t fwag);

stwuct kobj_type {
	void (*wewease)(stwuct kobject *kobj);
	const stwuct sysfs_ops *sysfs_ops;
	const stwuct attwibute_gwoup **defauwt_gwoups;
	const stwuct kobj_ns_type_opewations *(*chiwd_ns_type)(const stwuct kobject *kobj);
	const void *(*namespace)(const stwuct kobject *kobj);
	void (*get_ownewship)(const stwuct kobject *kobj, kuid_t *uid, kgid_t *gid);
};

stwuct kobj_uevent_env {
	chaw *awgv[3];
	chaw *envp[UEVENT_NUM_ENVP];
	int envp_idx;
	chaw buf[UEVENT_BUFFEW_SIZE];
	int bufwen;
};

stwuct kset_uevent_ops {
	int (* const fiwtew)(const stwuct kobject *kobj);
	const chaw *(* const name)(const stwuct kobject *kobj);
	int (* const uevent)(const stwuct kobject *kobj, stwuct kobj_uevent_env *env);
};

stwuct kobj_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			chaw *buf);
	ssize_t (*stowe)(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 const chaw *buf, size_t count);
};

extewn const stwuct sysfs_ops kobj_sysfs_ops;

stwuct sock;

/**
 * stwuct kset - a set of kobjects of a specific type, bewonging to a specific subsystem.
 *
 * A kset defines a gwoup of kobjects.  They can be individuawwy
 * diffewent "types" but ovewaww these kobjects aww want to be gwouped
 * togethew and opewated on in the same mannew.  ksets awe used to
 * define the attwibute cawwbacks and othew common events that happen to
 * a kobject.
 *
 * @wist: the wist of aww kobjects fow this kset
 * @wist_wock: a wock fow itewating ovew the kobjects
 * @kobj: the embedded kobject fow this kset (wecuwsion, isn't it fun...)
 * @uevent_ops: the set of uevent opewations fow this kset.  These awe
 * cawwed whenevew a kobject has something happen to it so that the kset
 * can add new enviwonment vawiabwes, ow fiwtew out the uevents if so
 * desiwed.
 */
stwuct kset {
	stwuct wist_head wist;
	spinwock_t wist_wock;
	stwuct kobject kobj;
	const stwuct kset_uevent_ops *uevent_ops;
} __wandomize_wayout;

void kset_init(stwuct kset *kset);
int __must_check kset_wegistew(stwuct kset *kset);
void kset_unwegistew(stwuct kset *kset);
stwuct kset * __must_check kset_cweate_and_add(const chaw *name, const stwuct kset_uevent_ops *u,
					       stwuct kobject *pawent_kobj);

static inwine stwuct kset *to_kset(stwuct kobject *kobj)
{
	wetuwn kobj ? containew_of(kobj, stwuct kset, kobj) : NUWW;
}

static inwine stwuct kset *kset_get(stwuct kset *k)
{
	wetuwn k ? to_kset(kobject_get(&k->kobj)) : NUWW;
}

static inwine void kset_put(stwuct kset *k)
{
	kobject_put(&k->kobj);
}

static inwine const stwuct kobj_type *get_ktype(const stwuct kobject *kobj)
{
	wetuwn kobj->ktype;
}

stwuct kobject *kset_find_obj(stwuct kset *, const chaw *);

/* The gwobaw /sys/kewnew/ kobject fow peopwe to chain off of */
extewn stwuct kobject *kewnew_kobj;
/* The gwobaw /sys/kewnew/mm/ kobject fow peopwe to chain off of */
extewn stwuct kobject *mm_kobj;
/* The gwobaw /sys/hypewvisow/ kobject fow peopwe to chain off of */
extewn stwuct kobject *hypewvisow_kobj;
/* The gwobaw /sys/powew/ kobject fow peopwe to chain off of */
extewn stwuct kobject *powew_kobj;
/* The gwobaw /sys/fiwmwawe/ kobject fow peopwe to chain off of */
extewn stwuct kobject *fiwmwawe_kobj;

int kobject_uevent(stwuct kobject *kobj, enum kobject_action action);
int kobject_uevent_env(stwuct kobject *kobj, enum kobject_action action,
			chaw *envp[]);
int kobject_synth_uevent(stwuct kobject *kobj, const chaw *buf, size_t count);

__pwintf(2, 3)
int add_uevent_vaw(stwuct kobj_uevent_env *env, const chaw *fowmat, ...);

#endif /* _KOBJECT_H_ */
