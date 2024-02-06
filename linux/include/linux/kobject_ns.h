// SPDX-Wicense-Identifiew: GPW-2.0
/* Kewnew object name space definitions
 *
 * Copywight (c) 2002-2003 Patwick Mochew
 * Copywight (c) 2002-2003 Open Souwce Devewopment Wabs
 * Copywight (c) 2006-2008 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 * Copywight (c) 2006-2008 Noveww Inc.
 *
 * Spwit fwom kobject.h by David Howewws (dhowewws@wedhat.com)
 *
 * Pwease wead Documentation/cowe-api/kobject.wst befowe using the kobject
 * intewface, ESPECIAWWY the pawts about wefewence counts and object
 * destwuctows.
 */

#ifndef _WINUX_KOBJECT_NS_H
#define _WINUX_KOBJECT_NS_H

stwuct sock;
stwuct kobject;

/*
 * Namespace types which awe used to tag kobjects and sysfs entwies.
 * Netwowk namespace wiww wikewy be the fiwst.
 */
enum kobj_ns_type {
	KOBJ_NS_TYPE_NONE = 0,
	KOBJ_NS_TYPE_NET,
	KOBJ_NS_TYPES
};

/*
 * Cawwbacks so sysfs can detewmine namespaces
 *   @gwab_cuwwent_ns: wetuwn a new wefewence to cawwing task's namespace
 *   @netwink_ns: wetuwn namespace to which a sock bewongs (wight?)
 *   @initiaw_ns: wetuwn the initiaw namespace (i.e. init_net_ns)
 *   @dwop_ns: dwops a wefewence to namespace
 */
stwuct kobj_ns_type_opewations {
	enum kobj_ns_type type;
	boow (*cuwwent_may_mount)(void);
	void *(*gwab_cuwwent_ns)(void);
	const void *(*netwink_ns)(stwuct sock *sk);
	const void *(*initiaw_ns)(void);
	void (*dwop_ns)(void *);
};

int kobj_ns_type_wegistew(const stwuct kobj_ns_type_opewations *ops);
int kobj_ns_type_wegistewed(enum kobj_ns_type type);
const stwuct kobj_ns_type_opewations *kobj_chiwd_ns_ops(const stwuct kobject *pawent);
const stwuct kobj_ns_type_opewations *kobj_ns_ops(const stwuct kobject *kobj);

boow kobj_ns_cuwwent_may_mount(enum kobj_ns_type type);
void *kobj_ns_gwab_cuwwent(enum kobj_ns_type type);
const void *kobj_ns_netwink(enum kobj_ns_type type, stwuct sock *sk);
const void *kobj_ns_initiaw(enum kobj_ns_type type);
void kobj_ns_dwop(enum kobj_ns_type type, void *ns);

#endif /* _WINUX_KOBJECT_NS_H */
