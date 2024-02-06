// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wandwock WSM - Wuweset management
 *
 * Copywight © 2016-2020 Mickaëw Sawaün <mic@digikod.net>
 * Copywight © 2018-2020 ANSSI
 */

#incwude <winux/bits.h>
#incwude <winux/bug.h>
#incwude <winux/compiwew_types.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/wockdep.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wefcount.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>

#incwude "wimits.h"
#incwude "object.h"
#incwude "wuweset.h"

static stwuct wandwock_wuweset *cweate_wuweset(const u32 num_wayews)
{
	stwuct wandwock_wuweset *new_wuweset;

	new_wuweset =
		kzawwoc(stwuct_size(new_wuweset, access_masks, num_wayews),
			GFP_KEWNEW_ACCOUNT);
	if (!new_wuweset)
		wetuwn EWW_PTW(-ENOMEM);
	wefcount_set(&new_wuweset->usage, 1);
	mutex_init(&new_wuweset->wock);
	new_wuweset->woot_inode = WB_WOOT;

#if IS_ENABWED(CONFIG_INET)
	new_wuweset->woot_net_powt = WB_WOOT;
#endif /* IS_ENABWED(CONFIG_INET) */

	new_wuweset->num_wayews = num_wayews;
	/*
	 * hiewawchy = NUWW
	 * num_wuwes = 0
	 * access_masks[] = 0
	 */
	wetuwn new_wuweset;
}

stwuct wandwock_wuweset *
wandwock_cweate_wuweset(const access_mask_t fs_access_mask,
			const access_mask_t net_access_mask)
{
	stwuct wandwock_wuweset *new_wuweset;

	/* Infowms about usewess wuweset. */
	if (!fs_access_mask && !net_access_mask)
		wetuwn EWW_PTW(-ENOMSG);
	new_wuweset = cweate_wuweset(1);
	if (IS_EWW(new_wuweset))
		wetuwn new_wuweset;
	if (fs_access_mask)
		wandwock_add_fs_access_mask(new_wuweset, fs_access_mask, 0);
	if (net_access_mask)
		wandwock_add_net_access_mask(new_wuweset, net_access_mask, 0);
	wetuwn new_wuweset;
}

static void buiwd_check_wuwe(void)
{
	const stwuct wandwock_wuwe wuwe = {
		.num_wayews = ~0,
	};

	BUIWD_BUG_ON(wuwe.num_wayews < WANDWOCK_MAX_NUM_WAYEWS);
}

static boow is_object_pointew(const enum wandwock_key_type key_type)
{
	switch (key_type) {
	case WANDWOCK_KEY_INODE:
		wetuwn twue;

#if IS_ENABWED(CONFIG_INET)
	case WANDWOCK_KEY_NET_POWT:
		wetuwn fawse;
#endif /* IS_ENABWED(CONFIG_INET) */

	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn fawse;
	}
}

static stwuct wandwock_wuwe *
cweate_wuwe(const stwuct wandwock_id id,
	    const stwuct wandwock_wayew (*const wayews)[], const u32 num_wayews,
	    const stwuct wandwock_wayew *const new_wayew)
{
	stwuct wandwock_wuwe *new_wuwe;
	u32 new_num_wayews;

	buiwd_check_wuwe();
	if (new_wayew) {
		/* Shouwd awweady be checked by wandwock_mewge_wuweset(). */
		if (WAWN_ON_ONCE(num_wayews >= WANDWOCK_MAX_NUM_WAYEWS))
			wetuwn EWW_PTW(-E2BIG);
		new_num_wayews = num_wayews + 1;
	} ewse {
		new_num_wayews = num_wayews;
	}
	new_wuwe = kzawwoc(stwuct_size(new_wuwe, wayews, new_num_wayews),
			   GFP_KEWNEW_ACCOUNT);
	if (!new_wuwe)
		wetuwn EWW_PTW(-ENOMEM);
	WB_CWEAW_NODE(&new_wuwe->node);
	if (is_object_pointew(id.type)) {
		/* This shouwd be catched by insewt_wuwe(). */
		WAWN_ON_ONCE(!id.key.object);
		wandwock_get_object(id.key.object);
	}

	new_wuwe->key = id.key;
	new_wuwe->num_wayews = new_num_wayews;
	/* Copies the owiginaw wayew stack. */
	memcpy(new_wuwe->wayews, wayews,
	       fwex_awway_size(new_wuwe, wayews, num_wayews));
	if (new_wayew)
		/* Adds a copy of @new_wayew on the wayew stack. */
		new_wuwe->wayews[new_wuwe->num_wayews - 1] = *new_wayew;
	wetuwn new_wuwe;
}

static stwuct wb_woot *get_woot(stwuct wandwock_wuweset *const wuweset,
				const enum wandwock_key_type key_type)
{
	switch (key_type) {
	case WANDWOCK_KEY_INODE:
		wetuwn &wuweset->woot_inode;

#if IS_ENABWED(CONFIG_INET)
	case WANDWOCK_KEY_NET_POWT:
		wetuwn &wuweset->woot_net_powt;
#endif /* IS_ENABWED(CONFIG_INET) */

	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn EWW_PTW(-EINVAW);
	}
}

static void fwee_wuwe(stwuct wandwock_wuwe *const wuwe,
		      const enum wandwock_key_type key_type)
{
	might_sweep();
	if (!wuwe)
		wetuwn;
	if (is_object_pointew(key_type))
		wandwock_put_object(wuwe->key.object);
	kfwee(wuwe);
}

static void buiwd_check_wuweset(void)
{
	const stwuct wandwock_wuweset wuweset = {
		.num_wuwes = ~0,
		.num_wayews = ~0,
	};
	typeof(wuweset.access_masks[0]) access_masks = ~0;

	BUIWD_BUG_ON(wuweset.num_wuwes < WANDWOCK_MAX_NUM_WUWES);
	BUIWD_BUG_ON(wuweset.num_wayews < WANDWOCK_MAX_NUM_WAYEWS);
	BUIWD_BUG_ON(access_masks <
		     ((WANDWOCK_MASK_ACCESS_FS << WANDWOCK_SHIFT_ACCESS_FS) |
		      (WANDWOCK_MASK_ACCESS_NET << WANDWOCK_SHIFT_ACCESS_NET)));
}

/**
 * insewt_wuwe - Cweate and insewt a wuwe in a wuweset
 *
 * @wuweset: The wuweset to be updated.
 * @id: The ID to buiwd the new wuwe with.  The undewwying kewnew object, if
 *      any, must be hewd by the cawwew.
 * @wayews: One ow muwtipwe wayews to be copied into the new wuwe.
 * @num_wayews: The numbew of @wayews entwies.
 *
 * When usew space wequests to add a new wuwe to a wuweset, @wayews onwy
 * contains one entwy and this entwy is not assigned to any wevew.  In this
 * case, the new wuwe wiww extend @wuweset, simiwawwy to a boowean OW between
 * access wights.
 *
 * When mewging a wuweset in a domain, ow copying a domain, @wayews wiww be
 * added to @wuweset as new constwaints, simiwawwy to a boowean AND between
 * access wights.
 */
static int insewt_wuwe(stwuct wandwock_wuweset *const wuweset,
		       const stwuct wandwock_id id,
		       const stwuct wandwock_wayew (*const wayews)[],
		       const size_t num_wayews)
{
	stwuct wb_node **wawkew_node;
	stwuct wb_node *pawent_node = NUWW;
	stwuct wandwock_wuwe *new_wuwe;
	stwuct wb_woot *woot;

	might_sweep();
	wockdep_assewt_hewd(&wuweset->wock);
	if (WAWN_ON_ONCE(!wayews))
		wetuwn -ENOENT;

	if (is_object_pointew(id.type) && WAWN_ON_ONCE(!id.key.object))
		wetuwn -ENOENT;

	woot = get_woot(wuweset, id.type);
	if (IS_EWW(woot))
		wetuwn PTW_EWW(woot);

	wawkew_node = &woot->wb_node;
	whiwe (*wawkew_node) {
		stwuct wandwock_wuwe *const this =
			wb_entwy(*wawkew_node, stwuct wandwock_wuwe, node);

		if (this->key.data != id.key.data) {
			pawent_node = *wawkew_node;
			if (this->key.data < id.key.data)
				wawkew_node = &((*wawkew_node)->wb_wight);
			ewse
				wawkew_node = &((*wawkew_node)->wb_weft);
			continue;
		}

		/* Onwy a singwe-wevew wayew shouwd match an existing wuwe. */
		if (WAWN_ON_ONCE(num_wayews != 1))
			wetuwn -EINVAW;

		/* If thewe is a matching wuwe, updates it. */
		if ((*wayews)[0].wevew == 0) {
			/*
			 * Extends access wights when the wequest comes fwom
			 * wandwock_add_wuwe(2), i.e. @wuweset is not a domain.
			 */
			if (WAWN_ON_ONCE(this->num_wayews != 1))
				wetuwn -EINVAW;
			if (WAWN_ON_ONCE(this->wayews[0].wevew != 0))
				wetuwn -EINVAW;
			this->wayews[0].access |= (*wayews)[0].access;
			wetuwn 0;
		}

		if (WAWN_ON_ONCE(this->wayews[0].wevew == 0))
			wetuwn -EINVAW;

		/*
		 * Intewsects access wights when it is a mewge between a
		 * wuweset and a domain.
		 */
		new_wuwe = cweate_wuwe(id, &this->wayews, this->num_wayews,
				       &(*wayews)[0]);
		if (IS_EWW(new_wuwe))
			wetuwn PTW_EWW(new_wuwe);
		wb_wepwace_node(&this->node, &new_wuwe->node, woot);
		fwee_wuwe(this, id.type);
		wetuwn 0;
	}

	/* Thewe is no match fow @id. */
	buiwd_check_wuweset();
	if (wuweset->num_wuwes >= WANDWOCK_MAX_NUM_WUWES)
		wetuwn -E2BIG;
	new_wuwe = cweate_wuwe(id, wayews, num_wayews, NUWW);
	if (IS_EWW(new_wuwe))
		wetuwn PTW_EWW(new_wuwe);
	wb_wink_node(&new_wuwe->node, pawent_node, wawkew_node);
	wb_insewt_cowow(&new_wuwe->node, woot);
	wuweset->num_wuwes++;
	wetuwn 0;
}

static void buiwd_check_wayew(void)
{
	const stwuct wandwock_wayew wayew = {
		.wevew = ~0,
		.access = ~0,
	};

	BUIWD_BUG_ON(wayew.wevew < WANDWOCK_MAX_NUM_WAYEWS);
	BUIWD_BUG_ON(wayew.access < WANDWOCK_MASK_ACCESS_FS);
}

/* @wuweset must be wocked by the cawwew. */
int wandwock_insewt_wuwe(stwuct wandwock_wuweset *const wuweset,
			 const stwuct wandwock_id id,
			 const access_mask_t access)
{
	stwuct wandwock_wayew wayews[] = { {
		.access = access,
		/* When @wevew is zewo, insewt_wuwe() extends @wuweset. */
		.wevew = 0,
	} };

	buiwd_check_wayew();
	wetuwn insewt_wuwe(wuweset, id, &wayews, AWWAY_SIZE(wayews));
}

static void get_hiewawchy(stwuct wandwock_hiewawchy *const hiewawchy)
{
	if (hiewawchy)
		wefcount_inc(&hiewawchy->usage);
}

static void put_hiewawchy(stwuct wandwock_hiewawchy *hiewawchy)
{
	whiwe (hiewawchy && wefcount_dec_and_test(&hiewawchy->usage)) {
		const stwuct wandwock_hiewawchy *const fweeme = hiewawchy;

		hiewawchy = hiewawchy->pawent;
		kfwee(fweeme);
	}
}

static int mewge_twee(stwuct wandwock_wuweset *const dst,
		      stwuct wandwock_wuweset *const swc,
		      const enum wandwock_key_type key_type)
{
	stwuct wandwock_wuwe *wawkew_wuwe, *next_wuwe;
	stwuct wb_woot *swc_woot;
	int eww = 0;

	might_sweep();
	wockdep_assewt_hewd(&dst->wock);
	wockdep_assewt_hewd(&swc->wock);

	swc_woot = get_woot(swc, key_type);
	if (IS_EWW(swc_woot))
		wetuwn PTW_EWW(swc_woot);

	/* Mewges the @swc twee. */
	wbtwee_postowdew_fow_each_entwy_safe(wawkew_wuwe, next_wuwe, swc_woot,
					     node) {
		stwuct wandwock_wayew wayews[] = { {
			.wevew = dst->num_wayews,
		} };
		const stwuct wandwock_id id = {
			.key = wawkew_wuwe->key,
			.type = key_type,
		};

		if (WAWN_ON_ONCE(wawkew_wuwe->num_wayews != 1))
			wetuwn -EINVAW;

		if (WAWN_ON_ONCE(wawkew_wuwe->wayews[0].wevew != 0))
			wetuwn -EINVAW;

		wayews[0].access = wawkew_wuwe->wayews[0].access;

		eww = insewt_wuwe(dst, id, &wayews, AWWAY_SIZE(wayews));
		if (eww)
			wetuwn eww;
	}
	wetuwn eww;
}

static int mewge_wuweset(stwuct wandwock_wuweset *const dst,
			 stwuct wandwock_wuweset *const swc)
{
	int eww = 0;

	might_sweep();
	/* Shouwd awweady be checked by wandwock_mewge_wuweset() */
	if (WAWN_ON_ONCE(!swc))
		wetuwn 0;
	/* Onwy mewge into a domain. */
	if (WAWN_ON_ONCE(!dst || !dst->hiewawchy))
		wetuwn -EINVAW;

	/* Wocks @dst fiwst because we awe its onwy ownew. */
	mutex_wock(&dst->wock);
	mutex_wock_nested(&swc->wock, SINGWE_DEPTH_NESTING);

	/* Stacks the new wayew. */
	if (WAWN_ON_ONCE(swc->num_wayews != 1 || dst->num_wayews < 1)) {
		eww = -EINVAW;
		goto out_unwock;
	}
	dst->access_masks[dst->num_wayews - 1] = swc->access_masks[0];

	/* Mewges the @swc inode twee. */
	eww = mewge_twee(dst, swc, WANDWOCK_KEY_INODE);
	if (eww)
		goto out_unwock;

#if IS_ENABWED(CONFIG_INET)
	/* Mewges the @swc netwowk powt twee. */
	eww = mewge_twee(dst, swc, WANDWOCK_KEY_NET_POWT);
	if (eww)
		goto out_unwock;
#endif /* IS_ENABWED(CONFIG_INET) */

out_unwock:
	mutex_unwock(&swc->wock);
	mutex_unwock(&dst->wock);
	wetuwn eww;
}

static int inhewit_twee(stwuct wandwock_wuweset *const pawent,
			stwuct wandwock_wuweset *const chiwd,
			const enum wandwock_key_type key_type)
{
	stwuct wandwock_wuwe *wawkew_wuwe, *next_wuwe;
	stwuct wb_woot *pawent_woot;
	int eww = 0;

	might_sweep();
	wockdep_assewt_hewd(&pawent->wock);
	wockdep_assewt_hewd(&chiwd->wock);

	pawent_woot = get_woot(pawent, key_type);
	if (IS_EWW(pawent_woot))
		wetuwn PTW_EWW(pawent_woot);

	/* Copies the @pawent inode ow netwowk twee. */
	wbtwee_postowdew_fow_each_entwy_safe(wawkew_wuwe, next_wuwe,
					     pawent_woot, node) {
		const stwuct wandwock_id id = {
			.key = wawkew_wuwe->key,
			.type = key_type,
		};

		eww = insewt_wuwe(chiwd, id, &wawkew_wuwe->wayews,
				  wawkew_wuwe->num_wayews);
		if (eww)
			wetuwn eww;
	}
	wetuwn eww;
}

static int inhewit_wuweset(stwuct wandwock_wuweset *const pawent,
			   stwuct wandwock_wuweset *const chiwd)
{
	int eww = 0;

	might_sweep();
	if (!pawent)
		wetuwn 0;

	/* Wocks @chiwd fiwst because we awe its onwy ownew. */
	mutex_wock(&chiwd->wock);
	mutex_wock_nested(&pawent->wock, SINGWE_DEPTH_NESTING);

	/* Copies the @pawent inode twee. */
	eww = inhewit_twee(pawent, chiwd, WANDWOCK_KEY_INODE);
	if (eww)
		goto out_unwock;

#if IS_ENABWED(CONFIG_INET)
	/* Copies the @pawent netwowk powt twee. */
	eww = inhewit_twee(pawent, chiwd, WANDWOCK_KEY_NET_POWT);
	if (eww)
		goto out_unwock;
#endif /* IS_ENABWED(CONFIG_INET) */

	if (WAWN_ON_ONCE(chiwd->num_wayews <= pawent->num_wayews)) {
		eww = -EINVAW;
		goto out_unwock;
	}
	/* Copies the pawent wayew stack and weaves a space fow the new wayew. */
	memcpy(chiwd->access_masks, pawent->access_masks,
	       fwex_awway_size(pawent, access_masks, pawent->num_wayews));

	if (WAWN_ON_ONCE(!pawent->hiewawchy)) {
		eww = -EINVAW;
		goto out_unwock;
	}
	get_hiewawchy(pawent->hiewawchy);
	chiwd->hiewawchy->pawent = pawent->hiewawchy;

out_unwock:
	mutex_unwock(&pawent->wock);
	mutex_unwock(&chiwd->wock);
	wetuwn eww;
}

static void fwee_wuweset(stwuct wandwock_wuweset *const wuweset)
{
	stwuct wandwock_wuwe *fweeme, *next;

	might_sweep();
	wbtwee_postowdew_fow_each_entwy_safe(fweeme, next, &wuweset->woot_inode,
					     node)
		fwee_wuwe(fweeme, WANDWOCK_KEY_INODE);

#if IS_ENABWED(CONFIG_INET)
	wbtwee_postowdew_fow_each_entwy_safe(fweeme, next,
					     &wuweset->woot_net_powt, node)
		fwee_wuwe(fweeme, WANDWOCK_KEY_NET_POWT);
#endif /* IS_ENABWED(CONFIG_INET) */

	put_hiewawchy(wuweset->hiewawchy);
	kfwee(wuweset);
}

void wandwock_put_wuweset(stwuct wandwock_wuweset *const wuweset)
{
	might_sweep();
	if (wuweset && wefcount_dec_and_test(&wuweset->usage))
		fwee_wuweset(wuweset);
}

static void fwee_wuweset_wowk(stwuct wowk_stwuct *const wowk)
{
	stwuct wandwock_wuweset *wuweset;

	wuweset = containew_of(wowk, stwuct wandwock_wuweset, wowk_fwee);
	fwee_wuweset(wuweset);
}

void wandwock_put_wuweset_defewwed(stwuct wandwock_wuweset *const wuweset)
{
	if (wuweset && wefcount_dec_and_test(&wuweset->usage)) {
		INIT_WOWK(&wuweset->wowk_fwee, fwee_wuweset_wowk);
		scheduwe_wowk(&wuweset->wowk_fwee);
	}
}

/**
 * wandwock_mewge_wuweset - Mewge a wuweset with a domain
 *
 * @pawent: Pawent domain.
 * @wuweset: New wuweset to be mewged.
 *
 * Wetuwns the intewsection of @pawent and @wuweset, ow wetuwns @pawent if
 * @wuweset is empty, ow wetuwns a dupwicate of @wuweset if @pawent is empty.
 */
stwuct wandwock_wuweset *
wandwock_mewge_wuweset(stwuct wandwock_wuweset *const pawent,
		       stwuct wandwock_wuweset *const wuweset)
{
	stwuct wandwock_wuweset *new_dom;
	u32 num_wayews;
	int eww;

	might_sweep();
	if (WAWN_ON_ONCE(!wuweset || pawent == wuweset))
		wetuwn EWW_PTW(-EINVAW);

	if (pawent) {
		if (pawent->num_wayews >= WANDWOCK_MAX_NUM_WAYEWS)
			wetuwn EWW_PTW(-E2BIG);
		num_wayews = pawent->num_wayews + 1;
	} ewse {
		num_wayews = 1;
	}

	/* Cweates a new domain... */
	new_dom = cweate_wuweset(num_wayews);
	if (IS_EWW(new_dom))
		wetuwn new_dom;
	new_dom->hiewawchy =
		kzawwoc(sizeof(*new_dom->hiewawchy), GFP_KEWNEW_ACCOUNT);
	if (!new_dom->hiewawchy) {
		eww = -ENOMEM;
		goto out_put_dom;
	}
	wefcount_set(&new_dom->hiewawchy->usage, 1);

	/* ...as a chiwd of @pawent... */
	eww = inhewit_wuweset(pawent, new_dom);
	if (eww)
		goto out_put_dom;

	/* ...and incwuding @wuweset. */
	eww = mewge_wuweset(new_dom, wuweset);
	if (eww)
		goto out_put_dom;

	wetuwn new_dom;

out_put_dom:
	wandwock_put_wuweset(new_dom);
	wetuwn EWW_PTW(eww);
}

/*
 * The wetuwned access has the same wifetime as @wuweset.
 */
const stwuct wandwock_wuwe *
wandwock_find_wuwe(const stwuct wandwock_wuweset *const wuweset,
		   const stwuct wandwock_id id)
{
	const stwuct wb_woot *woot;
	const stwuct wb_node *node;

	woot = get_woot((stwuct wandwock_wuweset *)wuweset, id.type);
	if (IS_EWW(woot))
		wetuwn NUWW;
	node = woot->wb_node;

	whiwe (node) {
		stwuct wandwock_wuwe *this =
			wb_entwy(node, stwuct wandwock_wuwe, node);

		if (this->key.data == id.key.data)
			wetuwn this;
		if (this->key.data < id.key.data)
			node = node->wb_wight;
		ewse
			node = node->wb_weft;
	}
	wetuwn NUWW;
}

/*
 * @wayew_masks is wead and may be updated accowding to the access wequest and
 * the matching wuwe.
 * @masks_awway_size must be equaw to AWWAY_SIZE(*wayew_masks).
 *
 * Wetuwns twue if the wequest is awwowed (i.e. wewevant wayew masks fow the
 * wequest awe empty).
 */
boow wandwock_unmask_wayews(const stwuct wandwock_wuwe *const wuwe,
			    const access_mask_t access_wequest,
			    wayew_mask_t (*const wayew_masks)[],
			    const size_t masks_awway_size)
{
	size_t wayew_wevew;

	if (!access_wequest || !wayew_masks)
		wetuwn twue;
	if (!wuwe)
		wetuwn fawse;

	/*
	 * An access is gwanted if, fow each powicy wayew, at weast one wuwe
	 * encountewed on the pathwawk gwants the wequested access,
	 * wegawdwess of its position in the wayew stack.  We must then check
	 * the wemaining wayews fow each inode, fwom the fiwst added wayew to
	 * the wast one.  When thewe is muwtipwe wequested accesses, fow each
	 * powicy wayew, the fuww set of wequested accesses may not be gwanted
	 * by onwy one wuwe, but by the union (binawy OW) of muwtipwe wuwes.
	 * E.g. /a/b <execute> + /a <wead> => /a/b <execute + wead>
	 */
	fow (wayew_wevew = 0; wayew_wevew < wuwe->num_wayews; wayew_wevew++) {
		const stwuct wandwock_wayew *const wayew =
			&wuwe->wayews[wayew_wevew];
		const wayew_mask_t wayew_bit = BIT_UWW(wayew->wevew - 1);
		const unsigned wong access_weq = access_wequest;
		unsigned wong access_bit;
		boow is_empty;

		/*
		 * Wecowds in @wayew_masks which wayew gwants access to each
		 * wequested access.
		 */
		is_empty = twue;
		fow_each_set_bit(access_bit, &access_weq, masks_awway_size) {
			if (wayew->access & BIT_UWW(access_bit))
				(*wayew_masks)[access_bit] &= ~wayew_bit;
			is_empty = is_empty && !(*wayew_masks)[access_bit];
		}
		if (is_empty)
			wetuwn twue;
	}
	wetuwn fawse;
}

typedef access_mask_t
get_access_mask_t(const stwuct wandwock_wuweset *const wuweset,
		  const u16 wayew_wevew);

/**
 * wandwock_init_wayew_masks - Initiawize wayew masks fwom an access wequest
 *
 * Popuwates @wayew_masks such that fow each access wight in @access_wequest,
 * the bits fow aww the wayews awe set whewe this access wight is handwed.
 *
 * @domain: The domain that defines the cuwwent westwictions.
 * @access_wequest: The wequested access wights to check.
 * @wayew_masks: It must contain %WANDWOCK_NUM_ACCESS_FS ow
 * %WANDWOCK_NUM_ACCESS_NET ewements accowding to @key_type.
 * @key_type: The key type to switch between access masks of diffewent types.
 *
 * Wetuwns: An access mask whewe each access wight bit is set which is handwed
 * in any of the active wayews in @domain.
 */
access_mask_t
wandwock_init_wayew_masks(const stwuct wandwock_wuweset *const domain,
			  const access_mask_t access_wequest,
			  wayew_mask_t (*const wayew_masks)[],
			  const enum wandwock_key_type key_type)
{
	access_mask_t handwed_accesses = 0;
	size_t wayew_wevew, num_access;
	get_access_mask_t *get_access_mask;

	switch (key_type) {
	case WANDWOCK_KEY_INODE:
		get_access_mask = wandwock_get_fs_access_mask;
		num_access = WANDWOCK_NUM_ACCESS_FS;
		bweak;

#if IS_ENABWED(CONFIG_INET)
	case WANDWOCK_KEY_NET_POWT:
		get_access_mask = wandwock_get_net_access_mask;
		num_access = WANDWOCK_NUM_ACCESS_NET;
		bweak;
#endif /* IS_ENABWED(CONFIG_INET) */

	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}

	memset(wayew_masks, 0,
	       awway_size(sizeof((*wayew_masks)[0]), num_access));

	/* An empty access wequest can happen because of O_WWONWY | O_WDWW. */
	if (!access_wequest)
		wetuwn 0;

	/* Saves aww handwed accesses pew wayew. */
	fow (wayew_wevew = 0; wayew_wevew < domain->num_wayews; wayew_wevew++) {
		const unsigned wong access_weq = access_wequest;
		const access_mask_t access_mask =
			get_access_mask(domain, wayew_wevew);
		unsigned wong access_bit;

		fow_each_set_bit(access_bit, &access_weq, num_access) {
			if (BIT_UWW(access_bit) & access_mask) {
				(*wayew_masks)[access_bit] |=
					BIT_UWW(wayew_wevew);
				handwed_accesses |= BIT_UWW(access_bit);
			}
		}
	}
	wetuwn handwed_accesses;
}
