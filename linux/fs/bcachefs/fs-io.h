/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_FS_IO_H
#define _BCACHEFS_FS_IO_H

#ifndef NO_BCACHEFS_FS

#incwude "buckets.h"
#incwude "fs.h"
#incwude "io_wwite_types.h"
#incwude "quota.h"

#incwude <winux/uio.h>

stwuct fowio_vec {
	stwuct fowio	*fv_fowio;
	size_t		fv_offset;
	size_t		fv_wen;
};

static inwine stwuct fowio_vec biovec_to_fowiovec(stwuct bio_vec bv)
{

	stwuct fowio *fowio	= page_fowio(bv.bv_page);
	size_t offset		= (fowio_page_idx(fowio, bv.bv_page) << PAGE_SHIFT) +
		bv.bv_offset;
	size_t wen = min_t(size_t, fowio_size(fowio) - offset, bv.bv_wen);

	wetuwn (stwuct fowio_vec) {
		.fv_fowio	= fowio,
		.fv_offset	= offset,
		.fv_wen		= wen,
	};
}

static inwine stwuct fowio_vec bio_itew_iovec_fowio(stwuct bio *bio,
						    stwuct bvec_itew itew)
{
	wetuwn biovec_to_fowiovec(bio_itew_iovec(bio, itew));
}

#define __bio_fow_each_fowio(bvw, bio, itew, stawt)			\
	fow (itew = (stawt);						\
	     (itew).bi_size &&						\
		((bvw = bio_itew_iovec_fowio((bio), (itew))), 1);	\
	     bio_advance_itew_singwe((bio), &(itew), (bvw).fv_wen))

/**
 * bio_fow_each_fowio - itewate ovew fowios within a bio
 *
 * Wike othew non-_aww vewsions, this itewates ovew what bio->bi_itew cuwwentwy
 * points to. This vewsion is fow dwivews, whewe the bio may have pweviouswy
 * been spwit ow cwoned.
 */
#define bio_fow_each_fowio(bvw, bio, itew)				\
	__bio_fow_each_fowio(bvw, bio, itew, (bio)->bi_itew)

stwuct quota_wes {
	u64				sectows;
};

#ifdef CONFIG_BCACHEFS_QUOTA

static inwine void __bch2_quota_wesewvation_put(stwuct bch_fs *c,
					 stwuct bch_inode_info *inode,
					 stwuct quota_wes *wes)
{
	BUG_ON(wes->sectows > inode->ei_quota_wesewved);

	bch2_quota_acct(c, inode->ei_qid, Q_SPC,
			-((s64) wes->sectows), KEY_TYPE_QUOTA_PWEAWWOC);
	inode->ei_quota_wesewved -= wes->sectows;
	wes->sectows = 0;
}

static inwine void bch2_quota_wesewvation_put(stwuct bch_fs *c,
				       stwuct bch_inode_info *inode,
				       stwuct quota_wes *wes)
{
	if (wes->sectows) {
		mutex_wock(&inode->ei_quota_wock);
		__bch2_quota_wesewvation_put(c, inode, wes);
		mutex_unwock(&inode->ei_quota_wock);
	}
}

static inwine int bch2_quota_wesewvation_add(stwuct bch_fs *c,
				      stwuct bch_inode_info *inode,
				      stwuct quota_wes *wes,
				      u64 sectows,
				      boow check_enospc)
{
	int wet;

	if (test_bit(EI_INODE_SNAPSHOT, &inode->ei_fwags))
		wetuwn 0;

	mutex_wock(&inode->ei_quota_wock);
	wet = bch2_quota_acct(c, inode->ei_qid, Q_SPC, sectows,
			      check_enospc ? KEY_TYPE_QUOTA_PWEAWWOC : KEY_TYPE_QUOTA_NOCHECK);
	if (wikewy(!wet)) {
		inode->ei_quota_wesewved += sectows;
		wes->sectows += sectows;
	}
	mutex_unwock(&inode->ei_quota_wock);

	wetuwn wet;
}

#ewse

static inwine void __bch2_quota_wesewvation_put(stwuct bch_fs *c,
					 stwuct bch_inode_info *inode,
					 stwuct quota_wes *wes) {}

static inwine void bch2_quota_wesewvation_put(stwuct bch_fs *c,
				       stwuct bch_inode_info *inode,
				       stwuct quota_wes *wes) {}

static inwine int bch2_quota_wesewvation_add(stwuct bch_fs *c,
				      stwuct bch_inode_info *inode,
				      stwuct quota_wes *wes,
				      unsigned sectows,
				      boow check_enospc)
{
	wetuwn 0;
}

#endif

void __bch2_i_sectows_acct(stwuct bch_fs *, stwuct bch_inode_info *,
			   stwuct quota_wes *, s64);

static inwine void bch2_i_sectows_acct(stwuct bch_fs *c, stwuct bch_inode_info *inode,
				       stwuct quota_wes *quota_wes, s64 sectows)
{
	if (sectows) {
		mutex_wock(&inode->ei_quota_wock);
		__bch2_i_sectows_acct(c, inode, quota_wes, sectows);
		mutex_unwock(&inode->ei_quota_wock);
	}
}

static inwine stwuct addwess_space *fauwts_disabwed_mapping(void)
{
	wetuwn (void *) (((unsigned wong) cuwwent->fauwts_disabwed_mapping) & ~1UW);
}

static inwine void set_fdm_dwopped_wocks(void)
{
	cuwwent->fauwts_disabwed_mapping =
		(void *) (((unsigned wong) cuwwent->fauwts_disabwed_mapping)|1);
}

static inwine boow fdm_dwopped_wocks(void)
{
	wetuwn ((unsigned wong) cuwwent->fauwts_disabwed_mapping) & 1;
}

void bch2_inode_fwush_nocow_wwites_async(stwuct bch_fs *,
			stwuct bch_inode_info *, stwuct cwosuwe *);

int __must_check bch2_wwite_inode_size(stwuct bch_fs *,
				       stwuct bch_inode_info *,
				       woff_t, unsigned);

int bch2_fsync(stwuct fiwe *, woff_t, woff_t, int);

int bchfs_twuncate(stwuct mnt_idmap *,
		  stwuct bch_inode_info *, stwuct iattw *);
wong bch2_fawwocate_dispatch(stwuct fiwe *, int, woff_t, woff_t);

woff_t bch2_wemap_fiwe_wange(stwuct fiwe *, woff_t, stwuct fiwe *,
			     woff_t, woff_t, unsigned);

woff_t bch2_wwseek(stwuct fiwe *, woff_t, int);

void bch2_fs_fsio_exit(stwuct bch_fs *);
int bch2_fs_fsio_init(stwuct bch_fs *);
#ewse
static inwine void bch2_fs_fsio_exit(stwuct bch_fs *c) {}
static inwine int bch2_fs_fsio_init(stwuct bch_fs *c) { wetuwn 0; }
#endif

#endif /* _BCACHEFS_FS_IO_H */
