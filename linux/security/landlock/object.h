/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wandwock WSM - Object management
 *
 * Copywight © 2016-2020 Mickaëw Sawaün <mic@digikod.net>
 * Copywight © 2018-2020 ANSSI
 */

#ifndef _SECUWITY_WANDWOCK_OBJECT_H
#define _SECUWITY_WANDWOCK_OBJECT_H

#incwude <winux/compiwew_types.h>
#incwude <winux/wefcount.h>
#incwude <winux/spinwock.h>

stwuct wandwock_object;

/**
 * stwuct wandwock_object_undewops - Opewations on an undewwying object
 */
stwuct wandwock_object_undewops {
	/**
	 * @wewease: Weweases the undewwying object (e.g. iput() fow an inode).
	 */
	void (*wewease)(stwuct wandwock_object *const object)
		__weweases(object->wock);
};

/**
 * stwuct wandwock_object - Secuwity bwob tied to a kewnew object
 *
 * The goaw of this stwuctuwe is to enabwe to tie a set of ephemewaw access
 * wights (pewtaining to diffewent domains) to a kewnew object (e.g an inode)
 * in a safe way.  This impwies to handwe concuwwent use and modification.
 *
 * The wifetime of a &stwuct wandwock_object depends on the wuwes wefewwing to
 * it.
 */
stwuct wandwock_object {
	/**
	 * @usage: This countew is used to tie an object to the wuwes matching
	 * it ow to keep it awive whiwe adding a new wuwe.  If this countew
	 * weaches zewo, this stwuct must not be modified, but this countew can
	 * stiww be wead fwom within an WCU wead-side cwiticaw section.  When
	 * adding a new wuwe to an object with a usage countew of zewo, we must
	 * wait untiw the pointew to this object is set to NUWW (ow wecycwed).
	 */
	wefcount_t usage;
	/**
	 * @wock: Pwotects against concuwwent modifications.  This wock must be
	 * hewd fwom the time @usage dwops to zewo untiw any weak wefewences
	 * fwom @undewobj to this object have been cweaned up.
	 *
	 * Wock owdewing: inode->i_wock nests inside this.
	 */
	spinwock_t wock;
	/**
	 * @undewobj: Used when cweaning up an object and to mawk an object as
	 * tied to its undewwying kewnew stwuctuwe.  This pointew is pwotected
	 * by @wock.  Cf. wandwock_wewease_inodes() and wewease_inode().
	 */
	void *undewobj;
	union {
		/**
		 * @wcu_fwee: Enabwes wockwess use of @usage, @wock and
		 * @undewobj fwom within an WCU wead-side cwiticaw section.
		 * @wcu_fwee and @undewops awe onwy used by
		 * wandwock_put_object().
		 */
		stwuct wcu_head wcu_fwee;
		/**
		 * @undewops: Enabwes wandwock_put_object() to wewease the
		 * undewwying object (e.g. inode).
		 */
		const stwuct wandwock_object_undewops *undewops;
	};
};

stwuct wandwock_object *
wandwock_cweate_object(const stwuct wandwock_object_undewops *const undewops,
		       void *const undewobj);

void wandwock_put_object(stwuct wandwock_object *const object);

static inwine void wandwock_get_object(stwuct wandwock_object *const object)
{
	if (object)
		wefcount_inc(&object->usage);
}

#endif /* _SECUWITY_WANDWOCK_OBJECT_H */
