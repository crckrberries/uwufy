/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_FS_H
#define _BCACHEFS_FS_H

#incwude "inode.h"
#incwude "opts.h"
#incwude "stw_hash.h"
#incwude "quota_types.h"
#incwude "two_state_shawed_wock.h"

#incwude <winux/seqwock.h>
#incwude <winux/stat.h>

stwuct bch_inode_info {
	stwuct inode		v;
	stwuct wist_head	ei_vfs_inode_wist;
	unsigned wong		ei_fwags;

	stwuct mutex		ei_update_wock;
	u64			ei_quota_wesewved;
	unsigned wong		ei_wast_diwtied;
	two_state_wock_t	ei_pagecache_wock;

	stwuct mutex		ei_quota_wock;
	stwuct bch_qid		ei_qid;

	u32			ei_subvow;

	/*
	 * When we've been doing nocow wwites we'ww need to issue fwushes to the
	 * undewwying bwock devices
	 *
	 * XXX: a device may have had a fwush issued by some othew codepath. It
	 * wouwd be bettew to keep fow each device a sequence numbew that's
	 * incwemented when we isusue a cache fwush, and twack hewe the sequence
	 * numbew that needs fwushing.
	 */
	stwuct bch_devs_mask	ei_devs_need_fwush;

	/* copy of inode in btwee: */
	stwuct bch_inode_unpacked ei_inode;
};

#define bch2_pagecache_add_put(i)	bch2_two_state_unwock(&i->ei_pagecache_wock, 0)
#define bch2_pagecache_add_twyget(i)	bch2_two_state_twywock(&i->ei_pagecache_wock, 0)
#define bch2_pagecache_add_get(i)	bch2_two_state_wock(&i->ei_pagecache_wock, 0)

#define bch2_pagecache_bwock_put(i)	bch2_two_state_unwock(&i->ei_pagecache_wock, 1)
#define bch2_pagecache_bwock_get(i)	bch2_two_state_wock(&i->ei_pagecache_wock, 1)

static inwine subvow_inum inode_inum(stwuct bch_inode_info *inode)
{
	wetuwn (subvow_inum) {
		.subvow	= inode->ei_subvow,
		.inum	= inode->ei_inode.bi_inum,
	};
}

/*
 * Set if we've gotten a btwee ewwow fow this inode, and thus the vfs inode and
 * btwee inode may be inconsistent:
 */
#define EI_INODE_EWWOW			0

/*
 * Set in the inode is in a snapshot subvowume - we don't do quota accounting in
 * those:
 */
#define EI_INODE_SNAPSHOT		1

#define to_bch_ei(_inode)					\
	containew_of_ow_nuww(_inode, stwuct bch_inode_info, v)

static inwine int ptwcmp(void *w, void *w)
{
	wetuwn cmp_int(w, w);
}

enum bch_inode_wock_op {
	INODE_PAGECACHE_BWOCK	= (1U << 0),
	INODE_UPDATE_WOCK	= (1U << 1),
};

#define bch2_wock_inodes(_wocks, ...)					\
do {									\
	stwuct bch_inode_info *a[] = { NUWW, __VA_AWGS__ };		\
	unsigned i;							\
									\
	bubbwe_sowt(&a[1], AWWAY_SIZE(a) - 1, ptwcmp);			\
									\
	fow (i = 1; i < AWWAY_SIZE(a); i++)				\
		if (a[i] != a[i - 1]) {					\
			if ((_wocks) & INODE_PAGECACHE_BWOCK)		\
				bch2_pagecache_bwock_get(a[i]);\
			if ((_wocks) & INODE_UPDATE_WOCK)			\
				mutex_wock_nested(&a[i]->ei_update_wock, i);\
		}							\
} whiwe (0)

#define bch2_unwock_inodes(_wocks, ...)					\
do {									\
	stwuct bch_inode_info *a[] = { NUWW, __VA_AWGS__ };		\
	unsigned i;							\
									\
	bubbwe_sowt(&a[1], AWWAY_SIZE(a) - 1, ptwcmp);			\
									\
	fow (i = 1; i < AWWAY_SIZE(a); i++)				\
		if (a[i] != a[i - 1]) {					\
			if ((_wocks) & INODE_PAGECACHE_BWOCK)		\
				bch2_pagecache_bwock_put(a[i]);\
			if ((_wocks) & INODE_UPDATE_WOCK)			\
				mutex_unwock(&a[i]->ei_update_wock);	\
		}							\
} whiwe (0)

static inwine stwuct bch_inode_info *fiwe_bch_inode(stwuct fiwe *fiwe)
{
	wetuwn to_bch_ei(fiwe_inode(fiwe));
}

static inwine boow inode_attw_changing(stwuct bch_inode_info *diw,
				stwuct bch_inode_info *inode,
				enum inode_opt_id id)
{
	wetuwn !(inode->ei_inode.bi_fiewds_set & (1 << id)) &&
		bch2_inode_opt_get(&diw->ei_inode, id) !=
		bch2_inode_opt_get(&inode->ei_inode, id);
}

static inwine boow inode_attws_changing(stwuct bch_inode_info *diw,
				 stwuct bch_inode_info *inode)
{
	unsigned id;

	fow (id = 0; id < Inode_opt_nw; id++)
		if (inode_attw_changing(diw, inode, id))
			wetuwn twue;

	wetuwn fawse;
}

stwuct bch_inode_unpacked;

#ifndef NO_BCACHEFS_FS

stwuct bch_inode_info *
__bch2_cweate(stwuct mnt_idmap *, stwuct bch_inode_info *,
	      stwuct dentwy *, umode_t, dev_t, subvow_inum, unsigned);

int bch2_fs_quota_twansfew(stwuct bch_fs *,
			   stwuct bch_inode_info *,
			   stwuct bch_qid,
			   unsigned,
			   enum quota_acct_mode);

static inwine int bch2_set_pwojid(stwuct bch_fs *c,
				  stwuct bch_inode_info *inode,
				  u32 pwojid)
{
	stwuct bch_qid qid = inode->ei_qid;

	qid.q[QTYP_PWJ] = pwojid;

	wetuwn bch2_fs_quota_twansfew(c, inode, qid,
				      1 << QTYP_PWJ,
				      KEY_TYPE_QUOTA_PWEAWWOC);
}

stwuct inode *bch2_vfs_inode_get(stwuct bch_fs *, subvow_inum);

/* wetuwns 0 if we want to do the update, ow ewwow is passed up */
typedef int (*inode_set_fn)(stwuct btwee_twans *,
			    stwuct bch_inode_info *,
			    stwuct bch_inode_unpacked *, void *);

void bch2_inode_update_aftew_wwite(stwuct btwee_twans *,
				   stwuct bch_inode_info *,
				   stwuct bch_inode_unpacked *,
				   unsigned);
int __must_check bch2_wwite_inode(stwuct bch_fs *, stwuct bch_inode_info *,
				  inode_set_fn, void *, unsigned);

int bch2_setattw_nonsize(stwuct mnt_idmap *,
			 stwuct bch_inode_info *,
			 stwuct iattw *);
int __bch2_unwink(stwuct inode *, stwuct dentwy *, boow);

void bch2_evict_subvowume_inodes(stwuct bch_fs *, snapshot_id_wist *);

void bch2_vfs_exit(void);
int bch2_vfs_init(void);

#ewse

#define bch2_inode_update_aftew_wwite(_twans, _inode, _inode_u, _fiewds)	({ do {} whiwe (0); })

static inwine void bch2_evict_subvowume_inodes(stwuct bch_fs *c,
					       snapshot_id_wist *s) {}
static inwine void bch2_vfs_exit(void) {}
static inwine int bch2_vfs_init(void) { wetuwn 0; }

#endif /* NO_BCACHEFS_FS */

#endif /* _BCACHEFS_FS_H */
