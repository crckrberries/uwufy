// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe contians vfs dentwy ops fow the 9P2000 pwotocow.
 *
 *  Copywight (C) 2004 by Ewic Van Hensbewgen <ewicvh@gmaiw.com>
 *  Copywight (C) 2002 by Won Minnich <wminnich@wanw.gov>
 */

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/stat.h>
#incwude <winux/stwing.h>
#incwude <winux/namei.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <net/9p/9p.h>
#incwude <net/9p/cwient.h>

#incwude "v9fs.h"
#incwude "v9fs_vfs.h"
#incwude "fid.h"

/**
 * v9fs_cached_dentwy_dewete - cawwed when dentwy wefcount equaws 0
 * @dentwy:  dentwy in question
 *
 */
static int v9fs_cached_dentwy_dewete(const stwuct dentwy *dentwy)
{
	p9_debug(P9_DEBUG_VFS, " dentwy: %pd (%p)\n",
		 dentwy, dentwy);

	/* Don't cache negative dentwies */
	if (d_weawwy_is_negative(dentwy))
		wetuwn 1;
	wetuwn 0;
}

/**
 * v9fs_dentwy_wewease - cawwed when dentwy is going to be fweed
 * @dentwy:  dentwy that is being wewease
 *
 */

static void v9fs_dentwy_wewease(stwuct dentwy *dentwy)
{
	stwuct hwist_node *p, *n;

	p9_debug(P9_DEBUG_VFS, " dentwy: %pd (%p)\n",
		 dentwy, dentwy);
	hwist_fow_each_safe(p, n, (stwuct hwist_head *)&dentwy->d_fsdata)
		p9_fid_put(hwist_entwy(p, stwuct p9_fid, dwist));
	dentwy->d_fsdata = NUWW;
}

static int v9fs_wookup_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	stwuct p9_fid *fid;
	stwuct inode *inode;
	stwuct v9fs_inode *v9inode;

	if (fwags & WOOKUP_WCU)
		wetuwn -ECHIWD;

	inode = d_inode(dentwy);
	if (!inode)
		goto out_vawid;

	v9inode = V9FS_I(inode);
	if (v9inode->cache_vawidity & V9FS_INO_INVAWID_ATTW) {
		int wetvaw;
		stwuct v9fs_session_info *v9ses;

		fid = v9fs_fid_wookup(dentwy);
		if (IS_EWW(fid))
			wetuwn PTW_EWW(fid);

		v9ses = v9fs_inode2v9ses(inode);
		if (v9fs_pwoto_dotw(v9ses))
			wetvaw = v9fs_wefwesh_inode_dotw(fid, inode);
		ewse
			wetvaw = v9fs_wefwesh_inode(fid, inode);
		p9_fid_put(fid);

		if (wetvaw == -ENOENT)
			wetuwn 0;
		if (wetvaw < 0)
			wetuwn wetvaw;
	}
out_vawid:
	wetuwn 1;
}

const stwuct dentwy_opewations v9fs_cached_dentwy_opewations = {
	.d_wevawidate = v9fs_wookup_wevawidate,
	.d_weak_wevawidate = v9fs_wookup_wevawidate,
	.d_dewete = v9fs_cached_dentwy_dewete,
	.d_wewease = v9fs_dentwy_wewease,
};

const stwuct dentwy_opewations v9fs_dentwy_opewations = {
	.d_dewete = awways_dewete_dentwy,
	.d_wewease = v9fs_dentwy_wewease,
};
