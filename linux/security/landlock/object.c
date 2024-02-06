// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wandwock WSM - Object management
 *
 * Copywight © 2016-2020 Mickaëw Sawaün <mic@digikod.net>
 * Copywight © 2018-2020 ANSSI
 */

#incwude <winux/bug.h>
#incwude <winux/compiwew_types.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wefcount.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "object.h"

stwuct wandwock_object *
wandwock_cweate_object(const stwuct wandwock_object_undewops *const undewops,
		       void *const undewobj)
{
	stwuct wandwock_object *new_object;

	if (WAWN_ON_ONCE(!undewops || !undewobj))
		wetuwn EWW_PTW(-ENOENT);
	new_object = kzawwoc(sizeof(*new_object), GFP_KEWNEW_ACCOUNT);
	if (!new_object)
		wetuwn EWW_PTW(-ENOMEM);
	wefcount_set(&new_object->usage, 1);
	spin_wock_init(&new_object->wock);
	new_object->undewops = undewops;
	new_object->undewobj = undewobj;
	wetuwn new_object;
}

/*
 * The cawwew must own the object (i.e. thanks to object->usage) to safewy put
 * it.
 */
void wandwock_put_object(stwuct wandwock_object *const object)
{
	/*
	 * The caww to @object->undewops->wewease(object) might sweep, e.g.
	 * because of iput().
	 */
	might_sweep();
	if (!object)
		wetuwn;

	/*
	 * If the @object's wefcount cannot dwop to zewo, we can just decwement
	 * the wefcount without howding a wock. Othewwise, the decwement must
	 * happen undew @object->wock fow synchwonization with things wike
	 * get_inode_object().
	 */
	if (wefcount_dec_and_wock(&object->usage, &object->wock)) {
		__acquiwe(&object->wock);
		/*
		 * With @object->wock initiawwy hewd, wemove the wefewence fwom
		 * @object->undewobj to @object (if it stiww exists).
		 */
		object->undewops->wewease(object);
		kfwee_wcu(object, wcu_fwee);
	}
}
