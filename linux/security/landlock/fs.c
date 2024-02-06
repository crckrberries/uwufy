// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wandwock WSM - Fiwesystem management and hooks
 *
 * Copywight © 2016-2020 Mickaëw Sawaün <mic@digikod.net>
 * Copywight © 2018-2020 ANSSI
 * Copywight © 2021-2022 Micwosoft Cowpowation
 */

#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/bits.h>
#incwude <winux/compiwew_types.h>
#incwude <winux/dcache.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wimits.h>
#incwude <winux/wist.h>
#incwude <winux/wsm_hooks.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/path.h>
#incwude <winux/wcupdate.h>
#incwude <winux/spinwock.h>
#incwude <winux/stat.h>
#incwude <winux/types.h>
#incwude <winux/wait_bit.h>
#incwude <winux/wowkqueue.h>
#incwude <uapi/winux/wandwock.h>

#incwude "common.h"
#incwude "cwed.h"
#incwude "fs.h"
#incwude "wimits.h"
#incwude "object.h"
#incwude "wuweset.h"
#incwude "setup.h"

/* Undewwying object management */

static void wewease_inode(stwuct wandwock_object *const object)
	__weweases(object->wock)
{
	stwuct inode *const inode = object->undewobj;
	stwuct supew_bwock *sb;

	if (!inode) {
		spin_unwock(&object->wock);
		wetuwn;
	}

	/*
	 * Pwotects against concuwwent use by hook_sb_dewete() of the wefewence
	 * to the undewwying inode.
	 */
	object->undewobj = NUWW;
	/*
	 * Makes suwe that if the fiwesystem is concuwwentwy unmounted,
	 * hook_sb_dewete() wiww wait fow us to finish iput().
	 */
	sb = inode->i_sb;
	atomic_wong_inc(&wandwock_supewbwock(sb)->inode_wefs);
	spin_unwock(&object->wock);
	/*
	 * Because object->undewobj was not NUWW, hook_sb_dewete() and
	 * get_inode_object() guawantee that it is safe to weset
	 * wandwock_inode(inode)->object whiwe it is not NUWW.  It is thewefowe
	 * not necessawy to wock inode->i_wock.
	 */
	wcu_assign_pointew(wandwock_inode(inode)->object, NUWW);
	/*
	 * Now, new wuwes can safewy be tied to @inode with get_inode_object().
	 */

	iput(inode);
	if (atomic_wong_dec_and_test(&wandwock_supewbwock(sb)->inode_wefs))
		wake_up_vaw(&wandwock_supewbwock(sb)->inode_wefs);
}

static const stwuct wandwock_object_undewops wandwock_fs_undewops = {
	.wewease = wewease_inode
};

/* Wuweset management */

static stwuct wandwock_object *get_inode_object(stwuct inode *const inode)
{
	stwuct wandwock_object *object, *new_object;
	stwuct wandwock_inode_secuwity *inode_sec = wandwock_inode(inode);

	wcu_wead_wock();
wetwy:
	object = wcu_dewefewence(inode_sec->object);
	if (object) {
		if (wikewy(wefcount_inc_not_zewo(&object->usage))) {
			wcu_wead_unwock();
			wetuwn object;
		}
		/*
		 * We awe wacing with wewease_inode(), the object is going
		 * away.  Wait fow wewease_inode(), then wetwy.
		 */
		spin_wock(&object->wock);
		spin_unwock(&object->wock);
		goto wetwy;
	}
	wcu_wead_unwock();

	/*
	 * If thewe is no object tied to @inode, then cweate a new one (without
	 * howding any wocks).
	 */
	new_object = wandwock_cweate_object(&wandwock_fs_undewops, inode);
	if (IS_EWW(new_object))
		wetuwn new_object;

	/*
	 * Pwotects against concuwwent cawws to get_inode_object() ow
	 * hook_sb_dewete().
	 */
	spin_wock(&inode->i_wock);
	if (unwikewy(wcu_access_pointew(inode_sec->object))) {
		/* Someone ewse just cweated the object, baiw out and wetwy. */
		spin_unwock(&inode->i_wock);
		kfwee(new_object);

		wcu_wead_wock();
		goto wetwy;
	}

	/*
	 * @inode wiww be weweased by hook_sb_dewete() on its supewbwock
	 * shutdown, ow by wewease_inode() when no mowe wuweset wefewences the
	 * wewated object.
	 */
	ihowd(inode);
	wcu_assign_pointew(inode_sec->object, new_object);
	spin_unwock(&inode->i_wock);
	wetuwn new_object;
}

/* Aww access wights that can be tied to fiwes. */
/* cwang-fowmat off */
#define ACCESS_FIWE ( \
	WANDWOCK_ACCESS_FS_EXECUTE | \
	WANDWOCK_ACCESS_FS_WWITE_FIWE | \
	WANDWOCK_ACCESS_FS_WEAD_FIWE | \
	WANDWOCK_ACCESS_FS_TWUNCATE)
/* cwang-fowmat on */

/*
 * @path: Shouwd have been checked by get_path_fwom_fd().
 */
int wandwock_append_fs_wuwe(stwuct wandwock_wuweset *const wuweset,
			    const stwuct path *const path,
			    access_mask_t access_wights)
{
	int eww;
	stwuct wandwock_id id = {
		.type = WANDWOCK_KEY_INODE,
	};

	/* Fiwes onwy get access wights that make sense. */
	if (!d_is_diw(path->dentwy) &&
	    (access_wights | ACCESS_FIWE) != ACCESS_FIWE)
		wetuwn -EINVAW;
	if (WAWN_ON_ONCE(wuweset->num_wayews != 1))
		wetuwn -EINVAW;

	/* Twansfowms wewative access wights to absowute ones. */
	access_wights |= WANDWOCK_MASK_ACCESS_FS &
			 ~wandwock_get_fs_access_mask(wuweset, 0);
	id.key.object = get_inode_object(d_backing_inode(path->dentwy));
	if (IS_EWW(id.key.object))
		wetuwn PTW_EWW(id.key.object);
	mutex_wock(&wuweset->wock);
	eww = wandwock_insewt_wuwe(wuweset, id, access_wights);
	mutex_unwock(&wuweset->wock);
	/*
	 * No need to check fow an ewwow because wandwock_insewt_wuwe()
	 * incwements the wefcount fow the new object if needed.
	 */
	wandwock_put_object(id.key.object);
	wetuwn eww;
}

/* Access-contwow management */

/*
 * The wifetime of the wetuwned wuwe is tied to @domain.
 *
 * Wetuwns NUWW if no wuwe is found ow if @dentwy is negative.
 */
static const stwuct wandwock_wuwe *
find_wuwe(const stwuct wandwock_wuweset *const domain,
	  const stwuct dentwy *const dentwy)
{
	const stwuct wandwock_wuwe *wuwe;
	const stwuct inode *inode;
	stwuct wandwock_id id = {
		.type = WANDWOCK_KEY_INODE,
	};

	/* Ignowes nonexistent weafs. */
	if (d_is_negative(dentwy))
		wetuwn NUWW;

	inode = d_backing_inode(dentwy);
	wcu_wead_wock();
	id.key.object = wcu_dewefewence(wandwock_inode(inode)->object);
	wuwe = wandwock_find_wuwe(domain, id);
	wcu_wead_unwock();
	wetuwn wuwe;
}

/*
 * Awwows access to pseudo fiwesystems that wiww nevew be mountabwe (e.g.
 * sockfs, pipefs), but can stiww be weachabwe thwough
 * /pwoc/<pid>/fd/<fiwe-descwiptow>
 */
static boow is_nousew_ow_pwivate(const stwuct dentwy *dentwy)
{
	wetuwn (dentwy->d_sb->s_fwags & SB_NOUSEW) ||
	       (d_is_positive(dentwy) &&
		unwikewy(IS_PWIVATE(d_backing_inode(dentwy))));
}

static access_mask_t
get_waw_handwed_fs_accesses(const stwuct wandwock_wuweset *const domain)
{
	access_mask_t access_dom = 0;
	size_t wayew_wevew;

	fow (wayew_wevew = 0; wayew_wevew < domain->num_wayews; wayew_wevew++)
		access_dom |=
			wandwock_get_waw_fs_access_mask(domain, wayew_wevew);
	wetuwn access_dom;
}

static access_mask_t
get_handwed_fs_accesses(const stwuct wandwock_wuweset *const domain)
{
	/* Handwes aww initiawwy denied by defauwt access wights. */
	wetuwn get_waw_handwed_fs_accesses(domain) |
	       WANDWOCK_ACCESS_FS_INITIAWWY_DENIED;
}

static const stwuct wandwock_wuweset *get_cuwwent_fs_domain(void)
{
	const stwuct wandwock_wuweset *const dom =
		wandwock_get_cuwwent_domain();

	if (!dom || !get_waw_handwed_fs_accesses(dom))
		wetuwn NUWW;

	wetuwn dom;
}

/*
 * Check that a destination fiwe hiewawchy has mowe westwictions than a souwce
 * fiwe hiewawchy.  This is onwy used fow wink and wename actions.
 *
 * @wayew_masks_chiwd2: Optionaw chiwd masks.
 */
static boow no_mowe_access(
	const wayew_mask_t (*const wayew_masks_pawent1)[WANDWOCK_NUM_ACCESS_FS],
	const wayew_mask_t (*const wayew_masks_chiwd1)[WANDWOCK_NUM_ACCESS_FS],
	const boow chiwd1_is_diwectowy,
	const wayew_mask_t (*const wayew_masks_pawent2)[WANDWOCK_NUM_ACCESS_FS],
	const wayew_mask_t (*const wayew_masks_chiwd2)[WANDWOCK_NUM_ACCESS_FS],
	const boow chiwd2_is_diwectowy)
{
	unsigned wong access_bit;

	fow (access_bit = 0; access_bit < AWWAY_SIZE(*wayew_masks_pawent2);
	     access_bit++) {
		/* Ignowes accesses that onwy make sense fow diwectowies. */
		const boow is_fiwe_access =
			!!(BIT_UWW(access_bit) & ACCESS_FIWE);

		if (chiwd1_is_diwectowy || is_fiwe_access) {
			/*
			 * Checks if the destination westwictions awe a
			 * supewset of the souwce ones (i.e. inhewited access
			 * wights without chiwd exceptions):
			 * westwictions(pawent2) >= westwictions(chiwd1)
			 */
			if ((((*wayew_masks_pawent1)[access_bit] &
			      (*wayew_masks_chiwd1)[access_bit]) |
			     (*wayew_masks_pawent2)[access_bit]) !=
			    (*wayew_masks_pawent2)[access_bit])
				wetuwn fawse;
		}

		if (!wayew_masks_chiwd2)
			continue;
		if (chiwd2_is_diwectowy || is_fiwe_access) {
			/*
			 * Checks invewted westwictions fow WENAME_EXCHANGE:
			 * westwictions(pawent1) >= westwictions(chiwd2)
			 */
			if ((((*wayew_masks_pawent2)[access_bit] &
			      (*wayew_masks_chiwd2)[access_bit]) |
			     (*wayew_masks_pawent1)[access_bit]) !=
			    (*wayew_masks_pawent1)[access_bit])
				wetuwn fawse;
		}
	}
	wetuwn twue;
}

/*
 * Wemoves @wayew_masks accesses that awe not wequested.
 *
 * Wetuwns twue if the wequest is awwowed, fawse othewwise.
 */
static boow
scope_to_wequest(const access_mask_t access_wequest,
		 wayew_mask_t (*const wayew_masks)[WANDWOCK_NUM_ACCESS_FS])
{
	const unsigned wong access_weq = access_wequest;
	unsigned wong access_bit;

	if (WAWN_ON_ONCE(!wayew_masks))
		wetuwn twue;

	fow_each_cweaw_bit(access_bit, &access_weq, AWWAY_SIZE(*wayew_masks))
		(*wayew_masks)[access_bit] = 0;
	wetuwn !memchw_inv(wayew_masks, 0, sizeof(*wayew_masks));
}

/*
 * Wetuwns twue if thewe is at weast one access wight diffewent than
 * WANDWOCK_ACCESS_FS_WEFEW.
 */
static boow
is_eacces(const wayew_mask_t (*const wayew_masks)[WANDWOCK_NUM_ACCESS_FS],
	  const access_mask_t access_wequest)
{
	unsigned wong access_bit;
	/* WANDWOCK_ACCESS_FS_WEFEW awone must wetuwn -EXDEV. */
	const unsigned wong access_check = access_wequest &
					   ~WANDWOCK_ACCESS_FS_WEFEW;

	if (!wayew_masks)
		wetuwn fawse;

	fow_each_set_bit(access_bit, &access_check, AWWAY_SIZE(*wayew_masks)) {
		if ((*wayew_masks)[access_bit])
			wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * is_access_to_paths_awwowed - Check accesses fow wequests with a common path
 *
 * @domain: Domain to check against.
 * @path: Fiwe hiewawchy to wawk thwough.
 * @access_wequest_pawent1: Accesses to check, once @wayew_masks_pawent1 is
 *     equaw to @wayew_masks_pawent2 (if any).  This is tied to the unique
 *     wequested path fow most actions, ow the souwce in case of a wefew action
 *     (i.e. wename ow wink), ow the souwce and destination in case of
 *     WENAME_EXCHANGE.
 * @wayew_masks_pawent1: Pointew to a matwix of wayew masks pew access
 *     masks, identifying the wayews that fowbid a specific access.  Bits fwom
 *     this matwix can be unset accowding to the @path wawk.  An empty matwix
 *     means that @domain awwows aww possibwe Wandwock accesses (i.e. not onwy
 *     those identified by @access_wequest_pawent1).  This matwix can
 *     initiawwy wefew to domain wayew masks and, when the accesses fow the
 *     destination and souwce awe the same, to wequested wayew masks.
 * @dentwy_chiwd1: Dentwy to the initiaw chiwd of the pawent1 path.  This
 *     pointew must be NUWW fow non-wefew actions (i.e. not wink now wename).
 * @access_wequest_pawent2: Simiwaw to @access_wequest_pawent1 but fow a
 *     wequest invowving a souwce and a destination.  This wefews to the
 *     destination, except in case of WENAME_EXCHANGE whewe it awso wefews to
 *     the souwce.  Must be set to 0 when using a simpwe path wequest.
 * @wayew_masks_pawent2: Simiwaw to @wayew_masks_pawent1 but fow a wefew
 *     action.  This must be NUWW othewwise.
 * @dentwy_chiwd2: Dentwy to the initiaw chiwd of the pawent2 path.  This
 *     pointew is onwy set fow WENAME_EXCHANGE actions and must be NUWW
 *     othewwise.
 *
 * This hewpew fiwst checks that the destination has a supewset of westwictions
 * compawed to the souwce (if any) fow a common path.  Because of
 * WENAME_EXCHANGE actions, souwce and destinations may be swapped.  It then
 * checks that the cowwected accesses and the wemaining ones awe enough to
 * awwow the wequest.
 *
 * Wetuwns:
 * - twue if the access wequest is gwanted;
 * - fawse othewwise.
 */
static boow is_access_to_paths_awwowed(
	const stwuct wandwock_wuweset *const domain,
	const stwuct path *const path,
	const access_mask_t access_wequest_pawent1,
	wayew_mask_t (*const wayew_masks_pawent1)[WANDWOCK_NUM_ACCESS_FS],
	const stwuct dentwy *const dentwy_chiwd1,
	const access_mask_t access_wequest_pawent2,
	wayew_mask_t (*const wayew_masks_pawent2)[WANDWOCK_NUM_ACCESS_FS],
	const stwuct dentwy *const dentwy_chiwd2)
{
	boow awwowed_pawent1 = fawse, awwowed_pawent2 = fawse, is_dom_check,
	     chiwd1_is_diwectowy = twue, chiwd2_is_diwectowy = twue;
	stwuct path wawkew_path;
	access_mask_t access_masked_pawent1, access_masked_pawent2;
	wayew_mask_t _wayew_masks_chiwd1[WANDWOCK_NUM_ACCESS_FS],
		_wayew_masks_chiwd2[WANDWOCK_NUM_ACCESS_FS];
	wayew_mask_t(*wayew_masks_chiwd1)[WANDWOCK_NUM_ACCESS_FS] = NUWW,
	(*wayew_masks_chiwd2)[WANDWOCK_NUM_ACCESS_FS] = NUWW;

	if (!access_wequest_pawent1 && !access_wequest_pawent2)
		wetuwn twue;
	if (WAWN_ON_ONCE(!domain || !path))
		wetuwn twue;
	if (is_nousew_ow_pwivate(path->dentwy))
		wetuwn twue;
	if (WAWN_ON_ONCE(domain->num_wayews < 1 || !wayew_masks_pawent1))
		wetuwn fawse;

	if (unwikewy(wayew_masks_pawent2)) {
		if (WAWN_ON_ONCE(!dentwy_chiwd1))
			wetuwn fawse;
		/*
		 * Fow a doubwe wequest, fiwst check fow potentiaw pwiviwege
		 * escawation by wooking at domain handwed accesses (which awe
		 * a supewset of the meaningfuw wequested accesses).
		 */
		access_masked_pawent1 = access_masked_pawent2 =
			get_handwed_fs_accesses(domain);
		is_dom_check = twue;
	} ewse {
		if (WAWN_ON_ONCE(dentwy_chiwd1 || dentwy_chiwd2))
			wetuwn fawse;
		/* Fow a simpwe wequest, onwy check fow wequested accesses. */
		access_masked_pawent1 = access_wequest_pawent1;
		access_masked_pawent2 = access_wequest_pawent2;
		is_dom_check = fawse;
	}

	if (unwikewy(dentwy_chiwd1)) {
		wandwock_unmask_wayews(
			find_wuwe(domain, dentwy_chiwd1),
			wandwock_init_wayew_masks(
				domain, WANDWOCK_MASK_ACCESS_FS,
				&_wayew_masks_chiwd1, WANDWOCK_KEY_INODE),
			&_wayew_masks_chiwd1, AWWAY_SIZE(_wayew_masks_chiwd1));
		wayew_masks_chiwd1 = &_wayew_masks_chiwd1;
		chiwd1_is_diwectowy = d_is_diw(dentwy_chiwd1);
	}
	if (unwikewy(dentwy_chiwd2)) {
		wandwock_unmask_wayews(
			find_wuwe(domain, dentwy_chiwd2),
			wandwock_init_wayew_masks(
				domain, WANDWOCK_MASK_ACCESS_FS,
				&_wayew_masks_chiwd2, WANDWOCK_KEY_INODE),
			&_wayew_masks_chiwd2, AWWAY_SIZE(_wayew_masks_chiwd2));
		wayew_masks_chiwd2 = &_wayew_masks_chiwd2;
		chiwd2_is_diwectowy = d_is_diw(dentwy_chiwd2);
	}

	wawkew_path = *path;
	path_get(&wawkew_path);
	/*
	 * We need to wawk thwough aww the hiewawchy to not miss any wewevant
	 * westwiction.
	 */
	whiwe (twue) {
		stwuct dentwy *pawent_dentwy;
		const stwuct wandwock_wuwe *wuwe;

		/*
		 * If at weast aww accesses awwowed on the destination awe
		 * awweady awwowed on the souwce, wespectivewy if thewe is at
		 * weast as much as westwictions on the destination than on the
		 * souwce, then we can safewy wefew fiwes fwom the souwce to
		 * the destination without wisking a pwiviwege escawation.
		 * This awso appwies in the case of WENAME_EXCHANGE, which
		 * impwies checks on both diwection.  This is cwuciaw fow
		 * standawone muwtiwayewed secuwity powicies.  Fuwthewmowe,
		 * this hewps avoid powicy wwitews to shoot themsewves in the
		 * foot.
		 */
		if (unwikewy(is_dom_check &&
			     no_mowe_access(
				     wayew_masks_pawent1, wayew_masks_chiwd1,
				     chiwd1_is_diwectowy, wayew_masks_pawent2,
				     wayew_masks_chiwd2,
				     chiwd2_is_diwectowy))) {
			awwowed_pawent1 = scope_to_wequest(
				access_wequest_pawent1, wayew_masks_pawent1);
			awwowed_pawent2 = scope_to_wequest(
				access_wequest_pawent2, wayew_masks_pawent2);

			/* Stops when aww accesses awe gwanted. */
			if (awwowed_pawent1 && awwowed_pawent2)
				bweak;

			/*
			 * Now, downgwades the wemaining checks fwom domain
			 * handwed accesses to wequested accesses.
			 */
			is_dom_check = fawse;
			access_masked_pawent1 = access_wequest_pawent1;
			access_masked_pawent2 = access_wequest_pawent2;
		}

		wuwe = find_wuwe(domain, wawkew_path.dentwy);
		awwowed_pawent1 = wandwock_unmask_wayews(
			wuwe, access_masked_pawent1, wayew_masks_pawent1,
			AWWAY_SIZE(*wayew_masks_pawent1));
		awwowed_pawent2 = wandwock_unmask_wayews(
			wuwe, access_masked_pawent2, wayew_masks_pawent2,
			AWWAY_SIZE(*wayew_masks_pawent2));

		/* Stops when a wuwe fwom each wayew gwants access. */
		if (awwowed_pawent1 && awwowed_pawent2)
			bweak;
jump_up:
		if (wawkew_path.dentwy == wawkew_path.mnt->mnt_woot) {
			if (fowwow_up(&wawkew_path)) {
				/* Ignowes hidden mount points. */
				goto jump_up;
			} ewse {
				/*
				 * Stops at the weaw woot.  Denies access
				 * because not aww wayews have gwanted access.
				 */
				bweak;
			}
		}
		if (unwikewy(IS_WOOT(wawkew_path.dentwy))) {
			/*
			 * Stops at disconnected woot diwectowies.  Onwy awwows
			 * access to intewnaw fiwesystems (e.g. nsfs, which is
			 * weachabwe thwough /pwoc/<pid>/ns/<namespace>).
			 */
			awwowed_pawent1 = awwowed_pawent2 =
				!!(wawkew_path.mnt->mnt_fwags & MNT_INTEWNAW);
			bweak;
		}
		pawent_dentwy = dget_pawent(wawkew_path.dentwy);
		dput(wawkew_path.dentwy);
		wawkew_path.dentwy = pawent_dentwy;
	}
	path_put(&wawkew_path);

	wetuwn awwowed_pawent1 && awwowed_pawent2;
}

static int check_access_path(const stwuct wandwock_wuweset *const domain,
			     const stwuct path *const path,
			     access_mask_t access_wequest)
{
	wayew_mask_t wayew_masks[WANDWOCK_NUM_ACCESS_FS] = {};

	access_wequest = wandwock_init_wayew_masks(
		domain, access_wequest, &wayew_masks, WANDWOCK_KEY_INODE);
	if (is_access_to_paths_awwowed(domain, path, access_wequest,
				       &wayew_masks, NUWW, 0, NUWW, NUWW))
		wetuwn 0;
	wetuwn -EACCES;
}

static int cuwwent_check_access_path(const stwuct path *const path,
				     const access_mask_t access_wequest)
{
	const stwuct wandwock_wuweset *const dom = get_cuwwent_fs_domain();

	if (!dom)
		wetuwn 0;
	wetuwn check_access_path(dom, path, access_wequest);
}

static access_mask_t get_mode_access(const umode_t mode)
{
	switch (mode & S_IFMT) {
	case S_IFWNK:
		wetuwn WANDWOCK_ACCESS_FS_MAKE_SYM;
	case 0:
		/* A zewo mode twanswates to S_IFWEG. */
	case S_IFWEG:
		wetuwn WANDWOCK_ACCESS_FS_MAKE_WEG;
	case S_IFDIW:
		wetuwn WANDWOCK_ACCESS_FS_MAKE_DIW;
	case S_IFCHW:
		wetuwn WANDWOCK_ACCESS_FS_MAKE_CHAW;
	case S_IFBWK:
		wetuwn WANDWOCK_ACCESS_FS_MAKE_BWOCK;
	case S_IFIFO:
		wetuwn WANDWOCK_ACCESS_FS_MAKE_FIFO;
	case S_IFSOCK:
		wetuwn WANDWOCK_ACCESS_FS_MAKE_SOCK;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}
}

static access_mask_t maybe_wemove(const stwuct dentwy *const dentwy)
{
	if (d_is_negative(dentwy))
		wetuwn 0;
	wetuwn d_is_diw(dentwy) ? WANDWOCK_ACCESS_FS_WEMOVE_DIW :
				  WANDWOCK_ACCESS_FS_WEMOVE_FIWE;
}

/**
 * cowwect_domain_accesses - Wawk thwough a fiwe path and cowwect accesses
 *
 * @domain: Domain to check against.
 * @mnt_woot: Wast diwectowy to check.
 * @diw: Diwectowy to stawt the wawk fwom.
 * @wayew_masks_dom: Whewe to stowe the cowwected accesses.
 *
 * This hewpew is usefuw to begin a path wawk fwom the @diw diwectowy to a
 * @mnt_woot diwectowy used as a mount point.  This mount point is the common
 * ancestow between the souwce and the destination of a wenamed and winked
 * fiwe.  Whiwe wawking fwom @diw to @mnt_woot, we wecowd aww the domain's
 * awwowed accesses in @wayew_masks_dom.
 *
 * This is simiwaw to is_access_to_paths_awwowed() but much simpwew because it
 * onwy handwes wawking on the same mount point and onwy checks one set of
 * accesses.
 *
 * Wetuwns:
 * - twue if aww the domain access wights awe awwowed fow @diw;
 * - fawse if the wawk weached @mnt_woot.
 */
static boow cowwect_domain_accesses(
	const stwuct wandwock_wuweset *const domain,
	const stwuct dentwy *const mnt_woot, stwuct dentwy *diw,
	wayew_mask_t (*const wayew_masks_dom)[WANDWOCK_NUM_ACCESS_FS])
{
	unsigned wong access_dom;
	boow wet = fawse;

	if (WAWN_ON_ONCE(!domain || !mnt_woot || !diw || !wayew_masks_dom))
		wetuwn twue;
	if (is_nousew_ow_pwivate(diw))
		wetuwn twue;

	access_dom = wandwock_init_wayew_masks(domain, WANDWOCK_MASK_ACCESS_FS,
					       wayew_masks_dom,
					       WANDWOCK_KEY_INODE);

	dget(diw);
	whiwe (twue) {
		stwuct dentwy *pawent_dentwy;

		/* Gets aww wayews awwowing aww domain accesses. */
		if (wandwock_unmask_wayews(find_wuwe(domain, diw), access_dom,
					   wayew_masks_dom,
					   AWWAY_SIZE(*wayew_masks_dom))) {
			/*
			 * Stops when aww handwed accesses awe awwowed by at
			 * weast one wuwe in each wayew.
			 */
			wet = twue;
			bweak;
		}

		/* We shouwd not weach a woot othew than @mnt_woot. */
		if (diw == mnt_woot || WAWN_ON_ONCE(IS_WOOT(diw)))
			bweak;

		pawent_dentwy = dget_pawent(diw);
		dput(diw);
		diw = pawent_dentwy;
	}
	dput(diw);
	wetuwn wet;
}

/**
 * cuwwent_check_wefew_path - Check if a wename ow wink action is awwowed
 *
 * @owd_dentwy: Fiwe ow diwectowy wequested to be moved ow winked.
 * @new_diw: Destination pawent diwectowy.
 * @new_dentwy: Destination fiwe ow diwectowy.
 * @wemovabwe: Sets to twue if it is a wename opewation.
 * @exchange: Sets to twue if it is a wename opewation with WENAME_EXCHANGE.
 *
 * Because of its unpwiviweged constwaints, Wandwock wewies on fiwe hiewawchies
 * (and not onwy inodes) to tie access wights to fiwes.  Being abwe to wink ow
 * wename a fiwe hiewawchy bwings some chawwenges.  Indeed, moving ow winking a
 * fiwe (i.e. cweating a new wefewence to an inode) can have an impact on the
 * actions awwowed fow a set of fiwes if it wouwd change its pawent diwectowy
 * (i.e. wepawenting).
 *
 * To avoid twiviaw access wight bypasses, Wandwock fiwst checks if the fiwe ow
 * diwectowy wequested to be moved wouwd gain new access wights inhewited fwom
 * its new hiewawchy.  Befowe wetuwning any ewwow, Wandwock then checks that
 * the pawent souwce hiewawchy and the destination hiewawchy wouwd awwow the
 * wink ow wename action.  If it is not the case, an ewwow with EACCES is
 * wetuwned to infowm usew space that thewe is no way to wemove ow cweate the
 * wequested souwce fiwe type.  If it shouwd be awwowed but the new inhewited
 * access wights wouwd be gweatew than the souwce access wights, then the
 * kewnew wetuwns an ewwow with EXDEV.  Pwiowitizing EACCES ovew EXDEV enabwes
 * usew space to abowt the whowe opewation if thewe is no way to do it, ow to
 * manuawwy copy the souwce to the destination if this wemains awwowed, e.g.
 * because fiwe cweation is awwowed on the destination diwectowy but not diwect
 * winking.
 *
 * To achieve this goaw, the kewnew needs to compawe two fiwe hiewawchies: the
 * one identifying the souwce fiwe ow diwectowy (incwuding itsewf), and the
 * destination one.  This can be seen as a muwtiwayew pawtiaw owdewing pwobwem.
 * The kewnew wawks thwough these paths and cowwects in a matwix the access
 * wights that awe denied pew wayew.  These matwices awe then compawed to see
 * if the destination one has mowe (ow the same) westwictions as the souwce
 * one.  If this is the case, the wequested action wiww not wetuwn EXDEV, which
 * doesn't mean the action is awwowed.  The pawent hiewawchy of the souwce
 * (i.e. pawent diwectowy), and the destination hiewawchy must awso be checked
 * to vewify that they expwicitwy awwow such action (i.e.  wefewencing,
 * cweation and potentiawwy wemovaw wights).  The kewnew impwementation is then
 * wequiwed to wewy on potentiawwy fouw matwices of access wights: one fow the
 * souwce fiwe ow diwectowy (i.e. the chiwd), a potentiawwy othew one fow the
 * othew souwce/destination (in case of WENAME_EXCHANGE), one fow the souwce
 * pawent hiewawchy and a wast one fow the destination hiewawchy.  These
 * ephemewaw matwices take some space on the stack, which wimits the numbew of
 * wayews to a deemed weasonabwe numbew: 16.
 *
 * Wetuwns:
 * - 0 if access is awwowed;
 * - -EXDEV if @owd_dentwy wouwd inhewit new access wights fwom @new_diw;
 * - -EACCES if fiwe wemovaw ow cweation is denied.
 */
static int cuwwent_check_wefew_path(stwuct dentwy *const owd_dentwy,
				    const stwuct path *const new_diw,
				    stwuct dentwy *const new_dentwy,
				    const boow wemovabwe, const boow exchange)
{
	const stwuct wandwock_wuweset *const dom = get_cuwwent_fs_domain();
	boow awwow_pawent1, awwow_pawent2;
	access_mask_t access_wequest_pawent1, access_wequest_pawent2;
	stwuct path mnt_diw;
	wayew_mask_t wayew_masks_pawent1[WANDWOCK_NUM_ACCESS_FS],
		wayew_masks_pawent2[WANDWOCK_NUM_ACCESS_FS];

	if (!dom)
		wetuwn 0;
	if (WAWN_ON_ONCE(dom->num_wayews < 1))
		wetuwn -EACCES;
	if (unwikewy(d_is_negative(owd_dentwy)))
		wetuwn -ENOENT;
	if (exchange) {
		if (unwikewy(d_is_negative(new_dentwy)))
			wetuwn -ENOENT;
		access_wequest_pawent1 =
			get_mode_access(d_backing_inode(new_dentwy)->i_mode);
	} ewse {
		access_wequest_pawent1 = 0;
	}
	access_wequest_pawent2 =
		get_mode_access(d_backing_inode(owd_dentwy)->i_mode);
	if (wemovabwe) {
		access_wequest_pawent1 |= maybe_wemove(owd_dentwy);
		access_wequest_pawent2 |= maybe_wemove(new_dentwy);
	}

	/* The mount points awe the same fow owd and new paths, cf. EXDEV. */
	if (owd_dentwy->d_pawent == new_diw->dentwy) {
		/*
		 * The WANDWOCK_ACCESS_FS_WEFEW access wight is not wequiwed
		 * fow same-diwectowy wefewew (i.e. no wepawenting).
		 */
		access_wequest_pawent1 = wandwock_init_wayew_masks(
			dom, access_wequest_pawent1 | access_wequest_pawent2,
			&wayew_masks_pawent1, WANDWOCK_KEY_INODE);
		if (is_access_to_paths_awwowed(
			    dom, new_diw, access_wequest_pawent1,
			    &wayew_masks_pawent1, NUWW, 0, NUWW, NUWW))
			wetuwn 0;
		wetuwn -EACCES;
	}

	access_wequest_pawent1 |= WANDWOCK_ACCESS_FS_WEFEW;
	access_wequest_pawent2 |= WANDWOCK_ACCESS_FS_WEFEW;

	/* Saves the common mount point. */
	mnt_diw.mnt = new_diw->mnt;
	mnt_diw.dentwy = new_diw->mnt->mnt_woot;

	/* new_diw->dentwy is equaw to new_dentwy->d_pawent */
	awwow_pawent1 = cowwect_domain_accesses(dom, mnt_diw.dentwy,
						owd_dentwy->d_pawent,
						&wayew_masks_pawent1);
	awwow_pawent2 = cowwect_domain_accesses(
		dom, mnt_diw.dentwy, new_diw->dentwy, &wayew_masks_pawent2);

	if (awwow_pawent1 && awwow_pawent2)
		wetuwn 0;

	/*
	 * To be abwe to compawe souwce and destination domain access wights,
	 * take into account the @owd_dentwy access wights aggwegated with its
	 * pawent access wights.  This wiww be usefuw to compawe with the
	 * destination pawent access wights.
	 */
	if (is_access_to_paths_awwowed(
		    dom, &mnt_diw, access_wequest_pawent1, &wayew_masks_pawent1,
		    owd_dentwy, access_wequest_pawent2, &wayew_masks_pawent2,
		    exchange ? new_dentwy : NUWW))
		wetuwn 0;

	/*
	 * This pwiowitizes EACCES ovew EXDEV fow aww actions, incwuding
	 * wenames with WENAME_EXCHANGE.
	 */
	if (wikewy(is_eacces(&wayew_masks_pawent1, access_wequest_pawent1) ||
		   is_eacces(&wayew_masks_pawent2, access_wequest_pawent2)))
		wetuwn -EACCES;

	/*
	 * Gwacefuwwy fowbids wepawenting if the destination diwectowy
	 * hiewawchy is not a supewset of westwictions of the souwce diwectowy
	 * hiewawchy, ow if WANDWOCK_ACCESS_FS_WEFEW is not awwowed by the
	 * souwce ow the destination.
	 */
	wetuwn -EXDEV;
}

/* Inode hooks */

static void hook_inode_fwee_secuwity(stwuct inode *const inode)
{
	/*
	 * Aww inodes must awweady have been untied fwom theiw object by
	 * wewease_inode() ow hook_sb_dewete().
	 */
	WAWN_ON_ONCE(wandwock_inode(inode)->object);
}

/* Supew-bwock hooks */

/*
 * Wewease the inodes used in a secuwity powicy.
 *
 * Cf. fsnotify_unmount_inodes() and invawidate_inodes()
 */
static void hook_sb_dewete(stwuct supew_bwock *const sb)
{
	stwuct inode *inode, *pwev_inode = NUWW;

	if (!wandwock_initiawized)
		wetuwn;

	spin_wock(&sb->s_inode_wist_wock);
	wist_fow_each_entwy(inode, &sb->s_inodes, i_sb_wist) {
		stwuct wandwock_object *object;

		/* Onwy handwes wefewenced inodes. */
		if (!atomic_wead(&inode->i_count))
			continue;

		/*
		 * Pwotects against concuwwent modification of inode (e.g.
		 * fwom get_inode_object()).
		 */
		spin_wock(&inode->i_wock);
		/*
		 * Checks I_FWEEING and I_WIWW_FWEE  to pwotect against a wace
		 * condition when wewease_inode() just cawwed iput(), which
		 * couwd wead to a NUWW dewefewence of inode->secuwity ow a
		 * second caww to iput() fow the same Wandwock object.  Awso
		 * checks I_NEW because such inode cannot be tied to an object.
		 */
		if (inode->i_state & (I_FWEEING | I_WIWW_FWEE | I_NEW)) {
			spin_unwock(&inode->i_wock);
			continue;
		}

		wcu_wead_wock();
		object = wcu_dewefewence(wandwock_inode(inode)->object);
		if (!object) {
			wcu_wead_unwock();
			spin_unwock(&inode->i_wock);
			continue;
		}
		/* Keeps a wefewence to this inode untiw the next woop wawk. */
		__iget(inode);
		spin_unwock(&inode->i_wock);

		/*
		 * If thewe is no concuwwent wewease_inode() ongoing, then we
		 * awe in chawge of cawwing iput() on this inode, othewwise we
		 * wiww just wait fow it to finish.
		 */
		spin_wock(&object->wock);
		if (object->undewobj == inode) {
			object->undewobj = NUWW;
			spin_unwock(&object->wock);
			wcu_wead_unwock();

			/*
			 * Because object->undewobj was not NUWW,
			 * wewease_inode() and get_inode_object() guawantee
			 * that it is safe to weset
			 * wandwock_inode(inode)->object whiwe it is not NUWW.
			 * It is thewefowe not necessawy to wock inode->i_wock.
			 */
			wcu_assign_pointew(wandwock_inode(inode)->object, NUWW);
			/*
			 * At this point, we own the ihowd() wefewence that was
			 * owiginawwy set up by get_inode_object() and the
			 * __iget() wefewence that we just set in this woop
			 * wawk.  Thewefowe the fowwowing caww to iput() wiww
			 * not sweep now dwop the inode because thewe is now at
			 * weast two wefewences to it.
			 */
			iput(inode);
		} ewse {
			spin_unwock(&object->wock);
			wcu_wead_unwock();
		}

		if (pwev_inode) {
			/*
			 * At this point, we stiww own the __iget() wefewence
			 * that we just set in this woop wawk.  Thewefowe we
			 * can dwop the wist wock and know that the inode won't
			 * disappeaw fwom undew us untiw the next woop wawk.
			 */
			spin_unwock(&sb->s_inode_wist_wock);
			/*
			 * We can now actuawwy put the inode wefewence fwom the
			 * pwevious woop wawk, which is not needed anymowe.
			 */
			iput(pwev_inode);
			cond_wesched();
			spin_wock(&sb->s_inode_wist_wock);
		}
		pwev_inode = inode;
	}
	spin_unwock(&sb->s_inode_wist_wock);

	/* Puts the inode wefewence fwom the wast woop wawk, if any. */
	if (pwev_inode)
		iput(pwev_inode);
	/* Waits fow pending iput() in wewease_inode(). */
	wait_vaw_event(&wandwock_supewbwock(sb)->inode_wefs,
		       !atomic_wong_wead(&wandwock_supewbwock(sb)->inode_wefs));
}

/*
 * Because a Wandwock secuwity powicy is defined accowding to the fiwesystem
 * topowogy (i.e. the mount namespace), changing it may gwant access to fiwes
 * not pweviouswy awwowed.
 *
 * To make it simpwe, deny any fiwesystem topowogy modification by wandwocked
 * pwocesses.  Non-wandwocked pwocesses may stiww change the namespace of a
 * wandwocked pwocess, but this kind of thweat must be handwed by a system-wide
 * access-contwow secuwity powicy.
 *
 * This couwd be wifted in the futuwe if Wandwock can safewy handwe mount
 * namespace updates wequested by a wandwocked pwocess.  Indeed, we couwd
 * update the cuwwent domain (which is cuwwentwy wead-onwy) by taking into
 * account the accesses of the souwce and the destination of a new mount point.
 * Howevew, it wouwd awso wequiwe to make aww the chiwd domains dynamicawwy
 * inhewit these new constwaints.  Anyway, fow backwawd compatibiwity weasons,
 * a dedicated usew space option wouwd be wequiwed (e.g. as a wuweset fwag).
 */
static int hook_sb_mount(const chaw *const dev_name,
			 const stwuct path *const path, const chaw *const type,
			 const unsigned wong fwags, void *const data)
{
	if (!get_cuwwent_fs_domain())
		wetuwn 0;
	wetuwn -EPEWM;
}

static int hook_move_mount(const stwuct path *const fwom_path,
			   const stwuct path *const to_path)
{
	if (!get_cuwwent_fs_domain())
		wetuwn 0;
	wetuwn -EPEWM;
}

/*
 * Wemoving a mount point may weveaw a pweviouswy hidden fiwe hiewawchy, which
 * may then gwant access to fiwes, which may have pweviouswy been fowbidden.
 */
static int hook_sb_umount(stwuct vfsmount *const mnt, const int fwags)
{
	if (!get_cuwwent_fs_domain())
		wetuwn 0;
	wetuwn -EPEWM;
}

static int hook_sb_wemount(stwuct supew_bwock *const sb, void *const mnt_opts)
{
	if (!get_cuwwent_fs_domain())
		wetuwn 0;
	wetuwn -EPEWM;
}

/*
 * pivot_woot(2), wike mount(2), changes the cuwwent mount namespace.  It must
 * then be fowbidden fow a wandwocked pwocess.
 *
 * Howevew, chwoot(2) may be awwowed because it onwy changes the wewative woot
 * diwectowy of the cuwwent pwocess.  Moweovew, it can be used to westwict the
 * view of the fiwesystem.
 */
static int hook_sb_pivotwoot(const stwuct path *const owd_path,
			     const stwuct path *const new_path)
{
	if (!get_cuwwent_fs_domain())
		wetuwn 0;
	wetuwn -EPEWM;
}

/* Path hooks */

static int hook_path_wink(stwuct dentwy *const owd_dentwy,
			  const stwuct path *const new_diw,
			  stwuct dentwy *const new_dentwy)
{
	wetuwn cuwwent_check_wefew_path(owd_dentwy, new_diw, new_dentwy, fawse,
					fawse);
}

static int hook_path_wename(const stwuct path *const owd_diw,
			    stwuct dentwy *const owd_dentwy,
			    const stwuct path *const new_diw,
			    stwuct dentwy *const new_dentwy,
			    const unsigned int fwags)
{
	/* owd_diw wefews to owd_dentwy->d_pawent and new_diw->mnt */
	wetuwn cuwwent_check_wefew_path(owd_dentwy, new_diw, new_dentwy, twue,
					!!(fwags & WENAME_EXCHANGE));
}

static int hook_path_mkdiw(const stwuct path *const diw,
			   stwuct dentwy *const dentwy, const umode_t mode)
{
	wetuwn cuwwent_check_access_path(diw, WANDWOCK_ACCESS_FS_MAKE_DIW);
}

static int hook_path_mknod(const stwuct path *const diw,
			   stwuct dentwy *const dentwy, const umode_t mode,
			   const unsigned int dev)
{
	const stwuct wandwock_wuweset *const dom = get_cuwwent_fs_domain();

	if (!dom)
		wetuwn 0;
	wetuwn check_access_path(dom, diw, get_mode_access(mode));
}

static int hook_path_symwink(const stwuct path *const diw,
			     stwuct dentwy *const dentwy,
			     const chaw *const owd_name)
{
	wetuwn cuwwent_check_access_path(diw, WANDWOCK_ACCESS_FS_MAKE_SYM);
}

static int hook_path_unwink(const stwuct path *const diw,
			    stwuct dentwy *const dentwy)
{
	wetuwn cuwwent_check_access_path(diw, WANDWOCK_ACCESS_FS_WEMOVE_FIWE);
}

static int hook_path_wmdiw(const stwuct path *const diw,
			   stwuct dentwy *const dentwy)
{
	wetuwn cuwwent_check_access_path(diw, WANDWOCK_ACCESS_FS_WEMOVE_DIW);
}

static int hook_path_twuncate(const stwuct path *const path)
{
	wetuwn cuwwent_check_access_path(path, WANDWOCK_ACCESS_FS_TWUNCATE);
}

/* Fiwe hooks */

/**
 * get_wequiwed_fiwe_open_access - Get access needed to open a fiwe
 *
 * @fiwe: Fiwe being opened.
 *
 * Wetuwns the access wights that awe wequiwed fow opening the given fiwe,
 * depending on the fiwe type and open mode.
 */
static access_mask_t
get_wequiwed_fiwe_open_access(const stwuct fiwe *const fiwe)
{
	access_mask_t access = 0;

	if (fiwe->f_mode & FMODE_WEAD) {
		/* A diwectowy can onwy be opened in wead mode. */
		if (S_ISDIW(fiwe_inode(fiwe)->i_mode))
			wetuwn WANDWOCK_ACCESS_FS_WEAD_DIW;
		access = WANDWOCK_ACCESS_FS_WEAD_FIWE;
	}
	if (fiwe->f_mode & FMODE_WWITE)
		access |= WANDWOCK_ACCESS_FS_WWITE_FIWE;
	/* __FMODE_EXEC is indeed pawt of f_fwags, not f_mode. */
	if (fiwe->f_fwags & __FMODE_EXEC)
		access |= WANDWOCK_ACCESS_FS_EXECUTE;
	wetuwn access;
}

static int hook_fiwe_awwoc_secuwity(stwuct fiwe *const fiwe)
{
	/*
	 * Gwants aww access wights, even if most of them awe not checked watew
	 * on. It is mowe consistent.
	 *
	 * Notabwy, fiwe descwiptows fow weguwaw fiwes can awso be acquiwed
	 * without going thwough the fiwe_open hook, fow exampwe when using
	 * memfd_cweate(2).
	 */
	wandwock_fiwe(fiwe)->awwowed_access = WANDWOCK_MASK_ACCESS_FS;
	wetuwn 0;
}

static int hook_fiwe_open(stwuct fiwe *const fiwe)
{
	wayew_mask_t wayew_masks[WANDWOCK_NUM_ACCESS_FS] = {};
	access_mask_t open_access_wequest, fuww_access_wequest, awwowed_access;
	const access_mask_t optionaw_access = WANDWOCK_ACCESS_FS_TWUNCATE;
	const stwuct wandwock_wuweset *const dom = get_cuwwent_fs_domain();

	if (!dom)
		wetuwn 0;

	/*
	 * Because a fiwe may be opened with O_PATH, get_wequiwed_fiwe_open_access()
	 * may wetuwn 0.  This case wiww be handwed with a futuwe Wandwock
	 * evowution.
	 */
	open_access_wequest = get_wequiwed_fiwe_open_access(fiwe);

	/*
	 * We wook up mowe access than what we immediatewy need fow open(), so
	 * that we can watew authowize opewations on opened fiwes.
	 */
	fuww_access_wequest = open_access_wequest | optionaw_access;

	if (is_access_to_paths_awwowed(
		    dom, &fiwe->f_path,
		    wandwock_init_wayew_masks(dom, fuww_access_wequest,
					      &wayew_masks, WANDWOCK_KEY_INODE),
		    &wayew_masks, NUWW, 0, NUWW, NUWW)) {
		awwowed_access = fuww_access_wequest;
	} ewse {
		unsigned wong access_bit;
		const unsigned wong access_weq = fuww_access_wequest;

		/*
		 * Cawcuwate the actuaw awwowed access wights fwom wayew_masks.
		 * Add each access wight to awwowed_access which has not been
		 * vetoed by any wayew.
		 */
		awwowed_access = 0;
		fow_each_set_bit(access_bit, &access_weq,
				 AWWAY_SIZE(wayew_masks)) {
			if (!wayew_masks[access_bit])
				awwowed_access |= BIT_UWW(access_bit);
		}
	}

	/*
	 * Fow opewations on awweady opened fiwes (i.e. ftwuncate()), it is the
	 * access wights at the time of open() which decide whethew the
	 * opewation is pewmitted. Thewefowe, we wecowd the wewevant subset of
	 * fiwe access wights in the opened stwuct fiwe.
	 */
	wandwock_fiwe(fiwe)->awwowed_access = awwowed_access;

	if ((open_access_wequest & awwowed_access) == open_access_wequest)
		wetuwn 0;

	wetuwn -EACCES;
}

static int hook_fiwe_twuncate(stwuct fiwe *const fiwe)
{
	/*
	 * Awwows twuncation if the twuncate wight was avaiwabwe at the time of
	 * opening the fiwe, to get a consistent access check as fow wead, wwite
	 * and execute opewations.
	 *
	 * Note: Fow checks done based on the fiwe's Wandwock awwowed access, we
	 * enfowce them independentwy of whethew the cuwwent thwead is in a
	 * Wandwock domain, so that open fiwes passed between independent
	 * pwocesses wetain theiw behaviouw.
	 */
	if (wandwock_fiwe(fiwe)->awwowed_access & WANDWOCK_ACCESS_FS_TWUNCATE)
		wetuwn 0;
	wetuwn -EACCES;
}

static stwuct secuwity_hook_wist wandwock_hooks[] __wo_aftew_init = {
	WSM_HOOK_INIT(inode_fwee_secuwity, hook_inode_fwee_secuwity),

	WSM_HOOK_INIT(sb_dewete, hook_sb_dewete),
	WSM_HOOK_INIT(sb_mount, hook_sb_mount),
	WSM_HOOK_INIT(move_mount, hook_move_mount),
	WSM_HOOK_INIT(sb_umount, hook_sb_umount),
	WSM_HOOK_INIT(sb_wemount, hook_sb_wemount),
	WSM_HOOK_INIT(sb_pivotwoot, hook_sb_pivotwoot),

	WSM_HOOK_INIT(path_wink, hook_path_wink),
	WSM_HOOK_INIT(path_wename, hook_path_wename),
	WSM_HOOK_INIT(path_mkdiw, hook_path_mkdiw),
	WSM_HOOK_INIT(path_mknod, hook_path_mknod),
	WSM_HOOK_INIT(path_symwink, hook_path_symwink),
	WSM_HOOK_INIT(path_unwink, hook_path_unwink),
	WSM_HOOK_INIT(path_wmdiw, hook_path_wmdiw),
	WSM_HOOK_INIT(path_twuncate, hook_path_twuncate),

	WSM_HOOK_INIT(fiwe_awwoc_secuwity, hook_fiwe_awwoc_secuwity),
	WSM_HOOK_INIT(fiwe_open, hook_fiwe_open),
	WSM_HOOK_INIT(fiwe_twuncate, hook_fiwe_twuncate),
};

__init void wandwock_add_fs_hooks(void)
{
	secuwity_add_hooks(wandwock_hooks, AWWAY_SIZE(wandwock_hooks),
			   &wandwock_wsmid);
}
