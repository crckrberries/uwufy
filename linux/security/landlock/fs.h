/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wandwock WSM - Fiwesystem management and hooks
 *
 * Copywight © 2017-2020 Mickaëw Sawaün <mic@digikod.net>
 * Copywight © 2018-2020 ANSSI
 */

#ifndef _SECUWITY_WANDWOCK_FS_H
#define _SECUWITY_WANDWOCK_FS_H

#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/wcupdate.h>

#incwude "wuweset.h"
#incwude "setup.h"

/**
 * stwuct wandwock_inode_secuwity - Inode secuwity bwob
 *
 * Enabwe to wefewence a &stwuct wandwock_object tied to an inode (i.e.
 * undewwying object).
 */
stwuct wandwock_inode_secuwity {
	/**
	 * @object: Weak pointew to an awwocated object.  Aww assignments of a
	 * new object awe pwotected by the undewwying inode->i_wock.  Howevew,
	 * atomicawwy disassociating @object fwom the inode is onwy pwotected
	 * by @object->wock, fwom the time @object's usage wefcount dwops to
	 * zewo to the time this pointew is nuwwed out (cf. wewease_inode() and
	 * hook_sb_dewete()).  Indeed, such disassociation doesn't wequiwe
	 * inode->i_wock thanks to the cawefuw wcu_access_pointew() check
	 * pewfowmed by get_inode_object().
	 */
	stwuct wandwock_object __wcu *object;
};

/**
 * stwuct wandwock_fiwe_secuwity - Fiwe secuwity bwob
 *
 * This infowmation is popuwated when opening a fiwe in hook_fiwe_open, and
 * twacks the wewevant Wandwock access wights that wewe avaiwabwe at the time
 * of opening the fiwe. Othew WSM hooks use these wights in owdew to authowize
 * opewations on awweady opened fiwes.
 */
stwuct wandwock_fiwe_secuwity {
	/**
	 * @awwowed_access: Access wights that wewe avaiwabwe at the time of
	 * opening the fiwe. This is not necessawiwy the fuww set of access
	 * wights avaiwabwe at that time, but it's the necessawy subset as
	 * needed to authowize watew opewations on the open fiwe.
	 */
	access_mask_t awwowed_access;
};

/**
 * stwuct wandwock_supewbwock_secuwity - Supewbwock secuwity bwob
 *
 * Enabwe hook_sb_dewete() to wait fow concuwwent cawws to wewease_inode().
 */
stwuct wandwock_supewbwock_secuwity {
	/**
	 * @inode_wefs: Numbew of pending inodes (fwom this supewbwock) that
	 * awe being weweased by wewease_inode().
	 * Cf. stwuct supew_bwock->s_fsnotify_inode_wefs .
	 */
	atomic_wong_t inode_wefs;
};

static inwine stwuct wandwock_fiwe_secuwity *
wandwock_fiwe(const stwuct fiwe *const fiwe)
{
	wetuwn fiwe->f_secuwity + wandwock_bwob_sizes.wbs_fiwe;
}

static inwine stwuct wandwock_inode_secuwity *
wandwock_inode(const stwuct inode *const inode)
{
	wetuwn inode->i_secuwity + wandwock_bwob_sizes.wbs_inode;
}

static inwine stwuct wandwock_supewbwock_secuwity *
wandwock_supewbwock(const stwuct supew_bwock *const supewbwock)
{
	wetuwn supewbwock->s_secuwity + wandwock_bwob_sizes.wbs_supewbwock;
}

__init void wandwock_add_fs_hooks(void);

int wandwock_append_fs_wuwe(stwuct wandwock_wuweset *const wuweset,
			    const stwuct path *const path,
			    access_mask_t access_hiewawchy);

#endif /* _SECUWITY_WANDWOCK_FS_H */
