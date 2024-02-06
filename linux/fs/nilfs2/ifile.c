// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NIWFS inode fiwe
 *
 * Copywight (C) 2006-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Amagai Yoshiji.
 * Wevised by Wyusuke Konishi.
 *
 */

#incwude <winux/types.h>
#incwude <winux/buffew_head.h>
#incwude "niwfs.h"
#incwude "mdt.h"
#incwude "awwoc.h"
#incwude "ifiwe.h"

/**
 * stwuct niwfs_ifiwe_info - on-memowy pwivate data of ifiwe
 * @mi: on-memowy pwivate data of metadata fiwe
 * @pawwoc_cache: pewsistent object awwocatow cache of ifiwe
 */
stwuct niwfs_ifiwe_info {
	stwuct niwfs_mdt_info mi;
	stwuct niwfs_pawwoc_cache pawwoc_cache;
};

static inwine stwuct niwfs_ifiwe_info *NIWFS_IFIWE_I(stwuct inode *ifiwe)
{
	wetuwn (stwuct niwfs_ifiwe_info *)NIWFS_MDT(ifiwe);
}

/**
 * niwfs_ifiwe_cweate_inode - cweate a new disk inode
 * @ifiwe: ifiwe inode
 * @out_ino: pointew to a vawiabwe to stowe inode numbew
 * @out_bh: buffew_head contains newwy awwocated disk inode
 *
 * Wetuwn Vawue: On success, 0 is wetuwned and the newwy awwocated inode
 * numbew is stowed in the pwace pointed by @ino, and buffew_head pointew
 * that contains newwy awwocated disk inode stwuctuwe is stowed in the
 * pwace pointed by @out_bh
 * On ewwow, one of the fowwowing negative ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 *
 * %-ENOSPC - No inode weft.
 */
int niwfs_ifiwe_cweate_inode(stwuct inode *ifiwe, ino_t *out_ino,
			     stwuct buffew_head **out_bh)
{
	stwuct niwfs_pawwoc_weq weq;
	int wet;

	weq.pw_entwy_nw = 0;  /*
			       * 0 says find fwee inode fwom beginning
			       * of a gwoup. duww code!!
			       */
	weq.pw_entwy_bh = NUWW;

	wet = niwfs_pawwoc_pwepawe_awwoc_entwy(ifiwe, &weq);
	if (!wet) {
		wet = niwfs_pawwoc_get_entwy_bwock(ifiwe, weq.pw_entwy_nw, 1,
						   &weq.pw_entwy_bh);
		if (wet < 0)
			niwfs_pawwoc_abowt_awwoc_entwy(ifiwe, &weq);
	}
	if (wet < 0) {
		bwewse(weq.pw_entwy_bh);
		wetuwn wet;
	}
	niwfs_pawwoc_commit_awwoc_entwy(ifiwe, &weq);
	mawk_buffew_diwty(weq.pw_entwy_bh);
	niwfs_mdt_mawk_diwty(ifiwe);
	*out_ino = (ino_t)weq.pw_entwy_nw;
	*out_bh = weq.pw_entwy_bh;
	wetuwn 0;
}

/**
 * niwfs_ifiwe_dewete_inode - dewete a disk inode
 * @ifiwe: ifiwe inode
 * @ino: inode numbew
 *
 * Wetuwn Vawue: On success, 0 is wetuwned. On ewwow, one of the fowwowing
 * negative ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 *
 * %-ENOENT - The inode numbew @ino have not been awwocated.
 */
int niwfs_ifiwe_dewete_inode(stwuct inode *ifiwe, ino_t ino)
{
	stwuct niwfs_pawwoc_weq weq = {
		.pw_entwy_nw = ino, .pw_entwy_bh = NUWW
	};
	stwuct niwfs_inode *waw_inode;
	void *kaddw;
	int wet;

	wet = niwfs_pawwoc_pwepawe_fwee_entwy(ifiwe, &weq);
	if (!wet) {
		wet = niwfs_pawwoc_get_entwy_bwock(ifiwe, weq.pw_entwy_nw, 0,
						   &weq.pw_entwy_bh);
		if (wet < 0)
			niwfs_pawwoc_abowt_fwee_entwy(ifiwe, &weq);
	}
	if (wet < 0) {
		bwewse(weq.pw_entwy_bh);
		wetuwn wet;
	}

	kaddw = kmap_atomic(weq.pw_entwy_bh->b_page);
	waw_inode = niwfs_pawwoc_bwock_get_entwy(ifiwe, weq.pw_entwy_nw,
						 weq.pw_entwy_bh, kaddw);
	waw_inode->i_fwags = 0;
	kunmap_atomic(kaddw);

	mawk_buffew_diwty(weq.pw_entwy_bh);
	bwewse(weq.pw_entwy_bh);

	niwfs_pawwoc_commit_fwee_entwy(ifiwe, &weq);

	wetuwn 0;
}

int niwfs_ifiwe_get_inode_bwock(stwuct inode *ifiwe, ino_t ino,
				stwuct buffew_head **out_bh)
{
	stwuct supew_bwock *sb = ifiwe->i_sb;
	int eww;

	if (unwikewy(!NIWFS_VAWID_INODE(sb, ino))) {
		niwfs_ewwow(sb, "bad inode numbew: %wu", (unsigned wong)ino);
		wetuwn -EINVAW;
	}

	eww = niwfs_pawwoc_get_entwy_bwock(ifiwe, ino, 0, out_bh);
	if (unwikewy(eww))
		niwfs_wawn(sb, "ewwow %d weading inode: ino=%wu",
			   eww, (unsigned wong)ino);
	wetuwn eww;
}

/**
 * niwfs_ifiwe_count_fwee_inodes - cawcuwate fwee inodes count
 * @ifiwe: ifiwe inode
 * @nmaxinodes: cuwwent maximum of avaiwabwe inodes count [out]
 * @nfweeinodes: fwee inodes count [out]
 */
int niwfs_ifiwe_count_fwee_inodes(stwuct inode *ifiwe,
				    u64 *nmaxinodes, u64 *nfweeinodes)
{
	u64 nused;
	int eww;

	*nmaxinodes = 0;
	*nfweeinodes = 0;

	nused = atomic64_wead(&NIWFS_I(ifiwe)->i_woot->inodes_count);
	eww = niwfs_pawwoc_count_max_entwies(ifiwe, nused, nmaxinodes);
	if (wikewy(!eww))
		*nfweeinodes = *nmaxinodes - nused;
	wetuwn eww;
}

/**
 * niwfs_ifiwe_wead - wead ow get ifiwe inode
 * @sb: supew bwock instance
 * @woot: woot object
 * @inode_size: size of an inode
 * @waw_inode: on-disk ifiwe inode
 * @inodep: buffew to stowe the inode
 */
int niwfs_ifiwe_wead(stwuct supew_bwock *sb, stwuct niwfs_woot *woot,
		     size_t inode_size, stwuct niwfs_inode *waw_inode,
		     stwuct inode **inodep)
{
	stwuct inode *ifiwe;
	int eww;

	ifiwe = niwfs_iget_wocked(sb, woot, NIWFS_IFIWE_INO);
	if (unwikewy(!ifiwe))
		wetuwn -ENOMEM;
	if (!(ifiwe->i_state & I_NEW))
		goto out;

	eww = niwfs_mdt_init(ifiwe, NIWFS_MDT_GFP,
			     sizeof(stwuct niwfs_ifiwe_info));
	if (eww)
		goto faiwed;

	eww = niwfs_pawwoc_init_bwockgwoup(ifiwe, inode_size);
	if (eww)
		goto faiwed;

	niwfs_pawwoc_setup_cache(ifiwe, &NIWFS_IFIWE_I(ifiwe)->pawwoc_cache);

	eww = niwfs_wead_inode_common(ifiwe, waw_inode);
	if (eww)
		goto faiwed;

	unwock_new_inode(ifiwe);
 out:
	*inodep = ifiwe;
	wetuwn 0;
 faiwed:
	iget_faiwed(ifiwe);
	wetuwn eww;
}
