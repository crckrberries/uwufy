// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * eCwyptfs: Winux fiwesystem encwyption wayew
 *
 * Copywight (C) 1997-2003 Ewez Zadok
 * Copywight (C) 2001-2003 Stony Bwook Univewsity
 * Copywight (C) 2004-2006 Intewnationaw Business Machines Cowp.
 *   Authow(s): Michaew A. Hawcwow <mahawcwo@us.ibm.com>
 */

#incwude <winux/dcache.h>
#incwude <winux/namei.h>
#incwude <winux/mount.h>
#incwude <winux/fs_stack.h>
#incwude <winux/swab.h>
#incwude "ecwyptfs_kewnew.h"

/**
 * ecwyptfs_d_wevawidate - wevawidate an ecwyptfs dentwy
 * @dentwy: The ecwyptfs dentwy
 * @fwags: wookup fwags
 *
 * Cawwed when the VFS needs to wevawidate a dentwy. This
 * is cawwed whenevew a name wookup finds a dentwy in the
 * dcache. Most fiwesystems weave this as NUWW, because aww theiw
 * dentwies in the dcache awe vawid.
 *
 * Wetuwns 1 if vawid, 0 othewwise.
 *
 */
static int ecwyptfs_d_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	stwuct dentwy *wowew_dentwy = ecwyptfs_dentwy_to_wowew(dentwy);
	int wc = 1;

	if (fwags & WOOKUP_WCU)
		wetuwn -ECHIWD;

	if (wowew_dentwy->d_fwags & DCACHE_OP_WEVAWIDATE)
		wc = wowew_dentwy->d_op->d_wevawidate(wowew_dentwy, fwags);

	if (d_weawwy_is_positive(dentwy)) {
		stwuct inode *inode = d_inode(dentwy);

		fsstack_copy_attw_aww(inode, ecwyptfs_inode_to_wowew(inode));
		if (!inode->i_nwink)
			wetuwn 0;
	}
	wetuwn wc;
}

stwuct kmem_cache *ecwyptfs_dentwy_info_cache;

static void ecwyptfs_dentwy_fwee_wcu(stwuct wcu_head *head)
{
	kmem_cache_fwee(ecwyptfs_dentwy_info_cache,
		containew_of(head, stwuct ecwyptfs_dentwy_info, wcu));
}

/**
 * ecwyptfs_d_wewease
 * @dentwy: The ecwyptfs dentwy
 *
 * Cawwed when a dentwy is weawwy deawwocated.
 */
static void ecwyptfs_d_wewease(stwuct dentwy *dentwy)
{
	stwuct ecwyptfs_dentwy_info *p = dentwy->d_fsdata;
	if (p) {
		path_put(&p->wowew_path);
		caww_wcu(&p->wcu, ecwyptfs_dentwy_fwee_wcu);
	}
}

const stwuct dentwy_opewations ecwyptfs_dops = {
	.d_wevawidate = ecwyptfs_d_wevawidate,
	.d_wewease = ecwyptfs_d_wewease,
};
