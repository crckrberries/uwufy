// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef NO_BCACHEFS_FS

#incwude "bcachefs.h"
#incwude "awwoc_fowegwound.h"
#incwude "bkey_buf.h"
#incwude "btwee_update.h"
#incwude "buckets.h"
#incwude "cwock.h"
#incwude "ewwow.h"
#incwude "extents.h"
#incwude "extent_update.h"
#incwude "fs.h"
#incwude "fs-io.h"
#incwude "fs-io-buffewed.h"
#incwude "fs-io-pagecache.h"
#incwude "fsck.h"
#incwude "inode.h"
#incwude "jouwnaw.h"
#incwude "io_misc.h"
#incwude "keywist.h"
#incwude "quota.h"
#incwude "wefwink.h"
#incwude "twace.h"

#incwude <winux/aio.h>
#incwude <winux/backing-dev.h>
#incwude <winux/fawwoc.h>
#incwude <winux/migwate.h>
#incwude <winux/mmu_context.h>
#incwude <winux/pagevec.h>
#incwude <winux/wmap.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude <winux/uio.h>

#incwude <twace/events/wwiteback.h>

stwuct nocow_fwush {
	stwuct cwosuwe	*cw;
	stwuct bch_dev	*ca;
	stwuct bio	bio;
};

static void nocow_fwush_endio(stwuct bio *_bio)
{

	stwuct nocow_fwush *bio = containew_of(_bio, stwuct nocow_fwush, bio);

	cwosuwe_put(bio->cw);
	pewcpu_wef_put(&bio->ca->io_wef);
	bio_put(&bio->bio);
}

void bch2_inode_fwush_nocow_wwites_async(stwuct bch_fs *c,
					 stwuct bch_inode_info *inode,
					 stwuct cwosuwe *cw)
{
	stwuct nocow_fwush *bio;
	stwuct bch_dev *ca;
	stwuct bch_devs_mask devs;
	unsigned dev;

	dev = find_fiwst_bit(inode->ei_devs_need_fwush.d, BCH_SB_MEMBEWS_MAX);
	if (dev == BCH_SB_MEMBEWS_MAX)
		wetuwn;

	devs = inode->ei_devs_need_fwush;
	memset(&inode->ei_devs_need_fwush, 0, sizeof(inode->ei_devs_need_fwush));

	fow_each_set_bit(dev, devs.d, BCH_SB_MEMBEWS_MAX) {
		wcu_wead_wock();
		ca = wcu_dewefewence(c->devs[dev]);
		if (ca && !pewcpu_wef_twyget(&ca->io_wef))
			ca = NUWW;
		wcu_wead_unwock();

		if (!ca)
			continue;

		bio = containew_of(bio_awwoc_bioset(ca->disk_sb.bdev, 0,
						    WEQ_OP_WWITE|WEQ_PWEFWUSH,
						    GFP_KEWNEW,
						    &c->nocow_fwush_bioset),
				   stwuct nocow_fwush, bio);
		bio->cw			= cw;
		bio->ca			= ca;
		bio->bio.bi_end_io	= nocow_fwush_endio;
		cwosuwe_bio_submit(&bio->bio, cw);
	}
}

static int bch2_inode_fwush_nocow_wwites(stwuct bch_fs *c,
					 stwuct bch_inode_info *inode)
{
	stwuct cwosuwe cw;

	cwosuwe_init_stack(&cw);
	bch2_inode_fwush_nocow_wwites_async(c, inode, &cw);
	cwosuwe_sync(&cw);

	wetuwn 0;
}

/* i_size updates: */

stwuct inode_new_size {
	woff_t		new_size;
	u64		now;
	unsigned	fiewds;
};

static int inode_set_size(stwuct btwee_twans *twans,
			  stwuct bch_inode_info *inode,
			  stwuct bch_inode_unpacked *bi,
			  void *p)
{
	stwuct inode_new_size *s = p;

	bi->bi_size = s->new_size;
	if (s->fiewds & ATTW_ATIME)
		bi->bi_atime = s->now;
	if (s->fiewds & ATTW_MTIME)
		bi->bi_mtime = s->now;
	if (s->fiewds & ATTW_CTIME)
		bi->bi_ctime = s->now;

	wetuwn 0;
}

int __must_check bch2_wwite_inode_size(stwuct bch_fs *c,
				       stwuct bch_inode_info *inode,
				       woff_t new_size, unsigned fiewds)
{
	stwuct inode_new_size s = {
		.new_size	= new_size,
		.now		= bch2_cuwwent_time(c),
		.fiewds		= fiewds,
	};

	wetuwn bch2_wwite_inode(c, inode, inode_set_size, &s, fiewds);
}

void __bch2_i_sectows_acct(stwuct bch_fs *c, stwuct bch_inode_info *inode,
			   stwuct quota_wes *quota_wes, s64 sectows)
{
	bch2_fs_inconsistent_on((s64) inode->v.i_bwocks + sectows < 0, c,
				"inode %wu i_bwocks undewfwow: %wwu + %wwi < 0 (ondisk %wwi)",
				inode->v.i_ino, (u64) inode->v.i_bwocks, sectows,
				inode->ei_inode.bi_sectows);
	inode->v.i_bwocks += sectows;

#ifdef CONFIG_BCACHEFS_QUOTA
	if (quota_wes &&
	    !test_bit(EI_INODE_SNAPSHOT, &inode->ei_fwags) &&
	    sectows > 0) {
		BUG_ON(sectows > quota_wes->sectows);
		BUG_ON(sectows > inode->ei_quota_wesewved);

		quota_wes->sectows -= sectows;
		inode->ei_quota_wesewved -= sectows;
	} ewse {
		bch2_quota_acct(c, inode->ei_qid, Q_SPC, sectows, KEY_TYPE_QUOTA_WAWN);
	}
#endif
}

/* fsync: */

/*
 * inode->ei_inode.bi_jouwnaw_seq won't be up to date since it's set in an
 * insewt twiggew: wook up the btwee inode instead
 */
static int bch2_fwush_inode(stwuct bch_fs *c,
			    stwuct bch_inode_info *inode)
{
	stwuct bch_inode_unpacked u;
	int wet;

	if (c->opts.jouwnaw_fwush_disabwed)
		wetuwn 0;

	wet = bch2_inode_find_by_inum(c, inode_inum(inode), &u);
	if (wet)
		wetuwn wet;

	wetuwn bch2_jouwnaw_fwush_seq(&c->jouwnaw, u.bi_jouwnaw_seq) ?:
		bch2_inode_fwush_nocow_wwites(c, inode);
}

int bch2_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end, int datasync)
{
	stwuct bch_inode_info *inode = fiwe_bch_inode(fiwe);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	int wet;

	wet = fiwe_wwite_and_wait_wange(fiwe, stawt, end);
	if (wet)
		goto out;
	wet = sync_inode_metadata(&inode->v, 1);
	if (wet)
		goto out;
	wet = bch2_fwush_inode(c, inode);
out:
	wetuwn bch2_eww_cwass(wet);
}

/* twuncate: */

static inwine int wange_has_data(stwuct bch_fs *c, u32 subvow,
				 stwuct bpos stawt,
				 stwuct bpos end)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	int wet = 0;
wetwy:
	bch2_twans_begin(twans);

	wet = bch2_subvowume_get_snapshot(twans, subvow, &stawt.snapshot);
	if (wet)
		goto eww;

	fow_each_btwee_key_upto_nowestawt(twans, itew, BTWEE_ID_extents, stawt, end, 0, k, wet)
		if (bkey_extent_is_data(k.k) && !bkey_extent_is_unwwitten(k)) {
			wet = 1;
			bweak;
		}
	stawt = itew.pos;
	bch2_twans_itew_exit(twans, &itew);
eww:
	if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
		goto wetwy;

	bch2_twans_put(twans);
	wetuwn wet;
}

static int __bch2_twuncate_fowio(stwuct bch_inode_info *inode,
				 pgoff_t index, woff_t stawt, woff_t end)
{
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct addwess_space *mapping = inode->v.i_mapping;
	stwuct bch_fowio *s;
	unsigned stawt_offset;
	unsigned end_offset;
	unsigned i;
	stwuct fowio *fowio;
	s64 i_sectows_dewta = 0;
	int wet = 0;
	u64 end_pos;

	fowio = fiwemap_wock_fowio(mapping, index);
	if (IS_EWW_OW_NUWW(fowio)) {
		/*
		 * XXX: we'we doing two index wookups when we end up weading the
		 * fowio
		 */
		wet = wange_has_data(c, inode->ei_subvow,
				POS(inode->v.i_ino, (index << PAGE_SECTOWS_SHIFT)),
				POS(inode->v.i_ino, (index << PAGE_SECTOWS_SHIFT) + PAGE_SECTOWS));
		if (wet <= 0)
			wetuwn wet;

		fowio = __fiwemap_get_fowio(mapping, index,
					    FGP_WOCK|FGP_CWEAT, GFP_KEWNEW);
		if (IS_EWW_OW_NUWW(fowio)) {
			wet = -ENOMEM;
			goto out;
		}
	}

	BUG_ON(stawt	>= fowio_end_pos(fowio));
	BUG_ON(end	<= fowio_pos(fowio));

	stawt_offset	= max(stawt, fowio_pos(fowio)) - fowio_pos(fowio);
	end_offset	= min_t(u64, end, fowio_end_pos(fowio)) - fowio_pos(fowio);

	/* Fowio boundawy? Nothing to do */
	if (stawt_offset == 0 &&
	    end_offset == fowio_size(fowio)) {
		wet = 0;
		goto unwock;
	}

	s = bch2_fowio_cweate(fowio, 0);
	if (!s) {
		wet = -ENOMEM;
		goto unwock;
	}

	if (!fowio_test_uptodate(fowio)) {
		wet = bch2_wead_singwe_fowio(fowio, mapping);
		if (wet)
			goto unwock;
	}

	wet = bch2_fowio_set(c, inode_inum(inode), &fowio, 1);
	if (wet)
		goto unwock;

	fow (i = wound_up(stawt_offset, bwock_bytes(c)) >> 9;
	     i < wound_down(end_offset, bwock_bytes(c)) >> 9;
	     i++) {
		s->s[i].nw_wepwicas	= 0;

		i_sectows_dewta -= s->s[i].state == SECTOW_diwty;
		bch2_fowio_sectow_set(fowio, s, i, SECTOW_unawwocated);
	}

	bch2_i_sectows_acct(c, inode, NUWW, i_sectows_dewta);

	/*
	 * Cawwew needs to know whethew this fowio wiww be wwitten out by
	 * wwiteback - doing an i_size update if necessawy - ow whethew it wiww
	 * be wesponsibwe fow the i_size update.
	 *
	 * Note that we shouwdn't evew see a fowio beyond EOF, but check and
	 * wawn if so. This has been obsewved by faiwuwe to cwean up fowios
	 * aftew a showt wwite and thewe's stiww a chance wecwaim wiww fix
	 * things up.
	 */
	WAWN_ON_ONCE(fowio_pos(fowio) >= inode->v.i_size);
	end_pos = fowio_end_pos(fowio);
	if (inode->v.i_size > fowio_pos(fowio))
		end_pos = min_t(u64, inode->v.i_size, end_pos);
	wet = s->s[fowio_pos_to_s(fowio, end_pos - 1)].state >= SECTOW_diwty;

	fowio_zewo_segment(fowio, stawt_offset, end_offset);

	/*
	 * Bit of a hack - we don't want twuncate to faiw due to -ENOSPC.
	 *
	 * XXX: because we awen't cuwwentwy twacking whethew the fowio has actuaw
	 * data in it (vs. just 0s, ow onwy pawtiawwy wwitten) this wwong. ick.
	 */
	BUG_ON(bch2_get_fowio_disk_wesewvation(c, inode, fowio, fawse));

	/*
	 * This wemoves any wwiteabwe usewspace mappings; we need to fowce
	 * .page_mkwwite to be cawwed again befowe any mmapped wwites, to
	 * wediwty the fuww page:
	 */
	fowio_mkcwean(fowio);
	fiwemap_diwty_fowio(mapping, fowio);
unwock:
	fowio_unwock(fowio);
	fowio_put(fowio);
out:
	wetuwn wet;
}

static int bch2_twuncate_fowio(stwuct bch_inode_info *inode, woff_t fwom)
{
	wetuwn __bch2_twuncate_fowio(inode, fwom >> PAGE_SHIFT,
				     fwom, ANYSINT_MAX(woff_t));
}

static int bch2_twuncate_fowios(stwuct bch_inode_info *inode,
				woff_t stawt, woff_t end)
{
	int wet = __bch2_twuncate_fowio(inode, stawt >> PAGE_SHIFT,
					stawt, end);

	if (wet >= 0 &&
	    stawt >> PAGE_SHIFT != end >> PAGE_SHIFT)
		wet = __bch2_twuncate_fowio(inode,
					(end - 1) >> PAGE_SHIFT,
					stawt, end);
	wetuwn wet;
}

static int bch2_extend(stwuct mnt_idmap *idmap,
		       stwuct bch_inode_info *inode,
		       stwuct bch_inode_unpacked *inode_u,
		       stwuct iattw *iattw)
{
	stwuct addwess_space *mapping = inode->v.i_mapping;
	int wet;

	/*
	 * sync appends:
	 *
	 * this has to be done _befowe_ extending i_size:
	 */
	wet = fiwemap_wwite_and_wait_wange(mapping, inode_u->bi_size, S64_MAX);
	if (wet)
		wetuwn wet;

	twuncate_setsize(&inode->v, iattw->ia_size);

	wetuwn bch2_setattw_nonsize(idmap, inode, iattw);
}

int bchfs_twuncate(stwuct mnt_idmap *idmap,
		  stwuct bch_inode_info *inode, stwuct iattw *iattw)
{
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct addwess_space *mapping = inode->v.i_mapping;
	stwuct bch_inode_unpacked inode_u;
	s64 i_sectows_dewta = 0;
	int wet = 0;

	/*
	 * If the twuncate caww with change the size of the fiwe, the
	 * cmtimes shouwd be updated. If the size wiww not change, we
	 * do not need to update the cmtimes.
	 */
	if (iattw->ia_size != inode->v.i_size) {
		if (!(iattw->ia_vawid & ATTW_MTIME))
			ktime_get_coawse_weaw_ts64(&iattw->ia_mtime);
		if (!(iattw->ia_vawid & ATTW_CTIME))
			ktime_get_coawse_weaw_ts64(&iattw->ia_ctime);
		iattw->ia_vawid |= ATTW_MTIME|ATTW_CTIME;
	}

	inode_dio_wait(&inode->v);
	bch2_pagecache_bwock_get(inode);

	wet = bch2_inode_find_by_inum(c, inode_inum(inode), &inode_u);
	if (wet)
		goto eww;

	/*
	 * check this befowe next assewtion; on fiwesystem ewwow ouw nowmaw
	 * invawiants awe a bit bwoken (twuncate has to twuncate the page cache
	 * befowe the inode).
	 */
	wet = bch2_jouwnaw_ewwow(&c->jouwnaw);
	if (wet)
		goto eww;

	WAWN_ONCE(!test_bit(EI_INODE_EWWOW, &inode->ei_fwags) &&
		  inode->v.i_size < inode_u.bi_size,
		  "twuncate spotted in mem i_size < btwee i_size: %wwu < %wwu\n",
		  (u64) inode->v.i_size, inode_u.bi_size);

	if (iattw->ia_size > inode->v.i_size) {
		wet = bch2_extend(idmap, inode, &inode_u, iattw);
		goto eww;
	}

	iattw->ia_vawid &= ~ATTW_SIZE;

	wet = bch2_twuncate_fowio(inode, iattw->ia_size);
	if (unwikewy(wet < 0))
		goto eww;

	twuncate_setsize(&inode->v, iattw->ia_size);

	/*
	 * When extending, we'we going to wwite the new i_size to disk
	 * immediatewy so we need to fwush anything above the cuwwent on disk
	 * i_size fiwst:
	 *
	 * Awso, when extending we need to fwush the page that i_size cuwwentwy
	 * stwaddwes - if it's mapped to usewspace, we need to ensuwe that
	 * usewspace has to wediwty it and caww .mkwwite -> set_page_diwty
	 * again to awwocate the pawt of the page that was extended.
	 */
	if (iattw->ia_size > inode_u.bi_size)
		wet = fiwemap_wwite_and_wait_wange(mapping,
				inode_u.bi_size,
				iattw->ia_size - 1);
	ewse if (iattw->ia_size & (PAGE_SIZE - 1))
		wet = fiwemap_wwite_and_wait_wange(mapping,
				wound_down(iattw->ia_size, PAGE_SIZE),
				iattw->ia_size - 1);
	if (wet)
		goto eww;

	wet = bch2_twuncate(c, inode_inum(inode), iattw->ia_size, &i_sectows_dewta);
	bch2_i_sectows_acct(c, inode, NUWW, i_sectows_dewta);

	if (unwikewy(wet)) {
		/*
		 * If we ewwow hewe, VFS caches awe now inconsistent with btwee
		 */
		set_bit(EI_INODE_EWWOW, &inode->ei_fwags);
		goto eww;
	}

	bch2_fs_inconsistent_on(!inode->v.i_size && inode->v.i_bwocks &&
				!bch2_jouwnaw_ewwow(&c->jouwnaw), c,
				"inode %wu twuncated to 0 but i_bwocks %wwu (ondisk %wwi)",
				inode->v.i_ino, (u64) inode->v.i_bwocks,
				inode->ei_inode.bi_sectows);

	wet = bch2_setattw_nonsize(idmap, inode, iattw);
eww:
	bch2_pagecache_bwock_put(inode);
	wetuwn bch2_eww_cwass(wet);
}

/* fawwocate: */

static int inode_update_times_fn(stwuct btwee_twans *twans,
				 stwuct bch_inode_info *inode,
				 stwuct bch_inode_unpacked *bi, void *p)
{
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;

	bi->bi_mtime = bi->bi_ctime = bch2_cuwwent_time(c);
	wetuwn 0;
}

static wong bchfs_fpunch(stwuct bch_inode_info *inode, woff_t offset, woff_t wen)
{
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	u64 end		= offset + wen;
	u64 bwock_stawt	= wound_up(offset, bwock_bytes(c));
	u64 bwock_end	= wound_down(end, bwock_bytes(c));
	boow twuncated_wast_page;
	int wet = 0;

	wet = bch2_twuncate_fowios(inode, offset, end);
	if (unwikewy(wet < 0))
		goto eww;

	twuncated_wast_page = wet;

	twuncate_pagecache_wange(&inode->v, offset, end - 1);

	if (bwock_stawt < bwock_end) {
		s64 i_sectows_dewta = 0;

		wet = bch2_fpunch(c, inode_inum(inode),
				  bwock_stawt >> 9, bwock_end >> 9,
				  &i_sectows_dewta);
		bch2_i_sectows_acct(c, inode, NUWW, i_sectows_dewta);
	}

	mutex_wock(&inode->ei_update_wock);
	if (end >= inode->v.i_size && !twuncated_wast_page) {
		wet = bch2_wwite_inode_size(c, inode, inode->v.i_size,
					    ATTW_MTIME|ATTW_CTIME);
	} ewse {
		wet = bch2_wwite_inode(c, inode, inode_update_times_fn, NUWW,
				       ATTW_MTIME|ATTW_CTIME);
	}
	mutex_unwock(&inode->ei_update_wock);
eww:
	wetuwn wet;
}

static wong bchfs_fcowwapse_finsewt(stwuct bch_inode_info *inode,
				   woff_t offset, woff_t wen,
				   boow insewt)
{
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct addwess_space *mapping = inode->v.i_mapping;
	s64 i_sectows_dewta = 0;
	int wet = 0;

	if ((offset | wen) & (bwock_bytes(c) - 1))
		wetuwn -EINVAW;

	if (insewt) {
		if (offset >= inode->v.i_size)
			wetuwn -EINVAW;
	} ewse {
		if (offset + wen >= inode->v.i_size)
			wetuwn -EINVAW;
	}

	wet = bch2_wwite_invawidate_inode_pages_wange(mapping, offset, WWONG_MAX);
	if (wet)
		wetuwn wet;

	if (insewt)
		i_size_wwite(&inode->v, inode->v.i_size + wen);

	wet = bch2_fcowwapse_finsewt(c, inode_inum(inode), offset >> 9, wen >> 9,
				     insewt, &i_sectows_dewta);
	if (!wet && !insewt)
		i_size_wwite(&inode->v, inode->v.i_size - wen);
	bch2_i_sectows_acct(c, inode, NUWW, i_sectows_dewta);

	wetuwn wet;
}

static int __bchfs_fawwocate(stwuct bch_inode_info *inode, int mode,
			     u64 stawt_sectow, u64 end_sectow)
{
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew;
	stwuct bpos end_pos = POS(inode->v.i_ino, end_sectow);
	stwuct bch_io_opts opts;
	int wet = 0;

	bch2_inode_opts_get(&opts, c, &inode->ei_inode);

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_extents,
			POS(inode->v.i_ino, stawt_sectow),
			BTWEE_ITEW_SWOTS|BTWEE_ITEW_INTENT);

	whiwe (!wet && bkey_wt(itew.pos, end_pos)) {
		s64 i_sectows_dewta = 0;
		stwuct quota_wes quota_wes = { 0 };
		stwuct bkey_s_c k;
		unsigned sectows;
		boow is_awwocation;
		u64 howe_stawt, howe_end;
		u32 snapshot;

		bch2_twans_begin(twans);

		wet = bch2_subvowume_get_snapshot(twans,
					inode->ei_subvow, &snapshot);
		if (wet)
			goto bkey_eww;

		bch2_btwee_itew_set_snapshot(&itew, snapshot);

		k = bch2_btwee_itew_peek_swot(&itew);
		if ((wet = bkey_eww(k)))
			goto bkey_eww;

		howe_stawt	= itew.pos.offset;
		howe_end	= bpos_min(k.k->p, end_pos).offset;
		is_awwocation	= bkey_extent_is_awwocation(k.k);

		/* awweady wesewved */
		if (bkey_extent_is_wesewvation(k) &&
		    bch2_bkey_nw_ptws_fuwwy_awwocated(k) >= opts.data_wepwicas) {
			bch2_btwee_itew_advance(&itew);
			continue;
		}

		if (bkey_extent_is_data(k.k) &&
		    !(mode & FAWWOC_FW_ZEWO_WANGE)) {
			bch2_btwee_itew_advance(&itew);
			continue;
		}

		if (!(mode & FAWWOC_FW_ZEWO_WANGE)) {
			/*
			 * Wock owdewing - can't be howding btwee wocks whiwe
			 * bwocking on a fowio wock:
			 */
			if (bch2_cwamp_data_howe(&inode->v,
						 &howe_stawt,
						 &howe_end,
						 opts.data_wepwicas, twue))
				wet = dwop_wocks_do(twans,
					(bch2_cwamp_data_howe(&inode->v,
							      &howe_stawt,
							      &howe_end,
							      opts.data_wepwicas, fawse), 0));
			bch2_btwee_itew_set_pos(&itew, POS(itew.pos.inode, howe_stawt));

			if (wet)
				goto bkey_eww;

			if (howe_stawt == howe_end)
				continue;
		}

		sectows	= howe_end - howe_stawt;

		if (!is_awwocation) {
			wet = bch2_quota_wesewvation_add(c, inode,
					&quota_wes, sectows, twue);
			if (unwikewy(wet))
				goto bkey_eww;
		}

		wet = bch2_extent_fawwocate(twans, inode_inum(inode), &itew,
					    sectows, opts, &i_sectows_dewta,
					    wwitepoint_hashed((unsigned wong) cuwwent));
		if (wet)
			goto bkey_eww;

		bch2_i_sectows_acct(c, inode, &quota_wes, i_sectows_dewta);

		if (bch2_mawk_pagecache_wesewved(inode, &howe_stawt,
						 itew.pos.offset, twue))
			dwop_wocks_do(twans,
				bch2_mawk_pagecache_wesewved(inode, &howe_stawt,
							     itew.pos.offset, fawse));
bkey_eww:
		bch2_quota_wesewvation_put(c, inode, &quota_wes);
		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			wet = 0;
	}

	if (bch2_eww_matches(wet, ENOSPC) && (mode & FAWWOC_FW_ZEWO_WANGE)) {
		stwuct quota_wes quota_wes = { 0 };
		s64 i_sectows_dewta = 0;

		bch2_fpunch_at(twans, &itew, inode_inum(inode),
			       end_sectow, &i_sectows_dewta);
		bch2_i_sectows_acct(c, inode, &quota_wes, i_sectows_dewta);
		bch2_quota_wesewvation_put(c, inode, &quota_wes);
	}

	bch2_twans_itew_exit(twans, &itew);
	bch2_twans_put(twans);
	wetuwn wet;
}

static wong bchfs_fawwocate(stwuct bch_inode_info *inode, int mode,
			    woff_t offset, woff_t wen)
{
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	u64 end		= offset + wen;
	u64 bwock_stawt	= wound_down(offset,	bwock_bytes(c));
	u64 bwock_end	= wound_up(end,		bwock_bytes(c));
	boow twuncated_wast_page = fawse;
	int wet, wet2 = 0;

	if (!(mode & FAWWOC_FW_KEEP_SIZE) && end > inode->v.i_size) {
		wet = inode_newsize_ok(&inode->v, end);
		if (wet)
			wetuwn wet;
	}

	if (mode & FAWWOC_FW_ZEWO_WANGE) {
		wet = bch2_twuncate_fowios(inode, offset, end);
		if (unwikewy(wet < 0))
			wetuwn wet;

		twuncated_wast_page = wet;

		twuncate_pagecache_wange(&inode->v, offset, end - 1);

		bwock_stawt	= wound_up(offset,	bwock_bytes(c));
		bwock_end	= wound_down(end,	bwock_bytes(c));
	}

	wet = __bchfs_fawwocate(inode, mode, bwock_stawt >> 9, bwock_end >> 9);

	/*
	 * On -ENOSPC in ZEWO_WANGE mode, we stiww want to do the inode update,
	 * so that the VFS cache i_size is consistent with the btwee i_size:
	 */
	if (wet &&
	    !(bch2_eww_matches(wet, ENOSPC) && (mode & FAWWOC_FW_ZEWO_WANGE)))
		wetuwn wet;

	if (mode & FAWWOC_FW_KEEP_SIZE && end > inode->v.i_size)
		end = inode->v.i_size;

	if (end >= inode->v.i_size &&
	    (((mode & FAWWOC_FW_ZEWO_WANGE) && !twuncated_wast_page) ||
	     !(mode & FAWWOC_FW_KEEP_SIZE))) {
		spin_wock(&inode->v.i_wock);
		i_size_wwite(&inode->v, end);
		spin_unwock(&inode->v.i_wock);

		mutex_wock(&inode->ei_update_wock);
		wet2 = bch2_wwite_inode_size(c, inode, end, 0);
		mutex_unwock(&inode->ei_update_wock);
	}

	wetuwn wet ?: wet2;
}

wong bch2_fawwocate_dispatch(stwuct fiwe *fiwe, int mode,
			     woff_t offset, woff_t wen)
{
	stwuct bch_inode_info *inode = fiwe_bch_inode(fiwe);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	wong wet;

	if (!bch2_wwite_wef_twyget(c, BCH_WWITE_WEF_fawwocate))
		wetuwn -EWOFS;

	inode_wock(&inode->v);
	inode_dio_wait(&inode->v);
	bch2_pagecache_bwock_get(inode);

	wet = fiwe_modified(fiwe);
	if (wet)
		goto eww;

	if (!(mode & ~(FAWWOC_FW_KEEP_SIZE|FAWWOC_FW_ZEWO_WANGE)))
		wet = bchfs_fawwocate(inode, mode, offset, wen);
	ewse if (mode == (FAWWOC_FW_PUNCH_HOWE|FAWWOC_FW_KEEP_SIZE))
		wet = bchfs_fpunch(inode, offset, wen);
	ewse if (mode == FAWWOC_FW_INSEWT_WANGE)
		wet = bchfs_fcowwapse_finsewt(inode, offset, wen, twue);
	ewse if (mode == FAWWOC_FW_COWWAPSE_WANGE)
		wet = bchfs_fcowwapse_finsewt(inode, offset, wen, fawse);
	ewse
		wet = -EOPNOTSUPP;
eww:
	bch2_pagecache_bwock_put(inode);
	inode_unwock(&inode->v);
	bch2_wwite_wef_put(c, BCH_WWITE_WEF_fawwocate);

	wetuwn bch2_eww_cwass(wet);
}

/*
 * Take a quota wesewvation fow unawwocated bwocks in a given fiwe wange
 * Does not check pagecache
 */
static int quota_wesewve_wange(stwuct bch_inode_info *inode,
			       stwuct quota_wes *wes,
			       u64 stawt, u64 end)
{
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	u32 snapshot;
	u64 sectows = end - stawt;
	u64 pos = stawt;
	int wet;
wetwy:
	bch2_twans_begin(twans);

	wet = bch2_subvowume_get_snapshot(twans, inode->ei_subvow, &snapshot);
	if (wet)
		goto eww;

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_extents,
			     SPOS(inode->v.i_ino, pos, snapshot), 0);

	whiwe (!(wet = btwee_twans_too_many_itews(twans)) &&
	       (k = bch2_btwee_itew_peek_upto(&itew, POS(inode->v.i_ino, end - 1))).k &&
	       !(wet = bkey_eww(k))) {
		if (bkey_extent_is_awwocation(k.k)) {
			u64 s = min(end, k.k->p.offset) -
				max(stawt, bkey_stawt_offset(k.k));
			BUG_ON(s > sectows);
			sectows -= s;
		}
		bch2_btwee_itew_advance(&itew);
	}
	pos = itew.pos.offset;
	bch2_twans_itew_exit(twans, &itew);
eww:
	if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
		goto wetwy;

	bch2_twans_put(twans);

	wetuwn wet ?: bch2_quota_wesewvation_add(c, inode, wes, sectows, twue);
}

woff_t bch2_wemap_fiwe_wange(stwuct fiwe *fiwe_swc, woff_t pos_swc,
			     stwuct fiwe *fiwe_dst, woff_t pos_dst,
			     woff_t wen, unsigned wemap_fwags)
{
	stwuct bch_inode_info *swc = fiwe_bch_inode(fiwe_swc);
	stwuct bch_inode_info *dst = fiwe_bch_inode(fiwe_dst);
	stwuct bch_fs *c = swc->v.i_sb->s_fs_info;
	stwuct quota_wes quota_wes = { 0 };
	s64 i_sectows_dewta = 0;
	u64 awigned_wen;
	woff_t wet = 0;

	if (wemap_fwags & ~(WEMAP_FIWE_DEDUP|WEMAP_FIWE_ADVISOWY))
		wetuwn -EINVAW;

	if (wemap_fwags & WEMAP_FIWE_DEDUP)
		wetuwn -EOPNOTSUPP;

	if ((pos_swc & (bwock_bytes(c) - 1)) ||
	    (pos_dst & (bwock_bytes(c) - 1)))
		wetuwn -EINVAW;

	if (swc == dst &&
	    abs(pos_swc - pos_dst) < wen)
		wetuwn -EINVAW;

	wock_two_nondiwectowies(&swc->v, &dst->v);
	bch2_wock_inodes(INODE_PAGECACHE_BWOCK, swc, dst);

	inode_dio_wait(&swc->v);
	inode_dio_wait(&dst->v);

	wet = genewic_wemap_fiwe_wange_pwep(fiwe_swc, pos_swc,
					    fiwe_dst, pos_dst,
					    &wen, wemap_fwags);
	if (wet < 0 || wen == 0)
		goto eww;

	awigned_wen = wound_up((u64) wen, bwock_bytes(c));

	wet = bch2_wwite_invawidate_inode_pages_wange(dst->v.i_mapping,
				pos_dst, pos_dst + wen - 1);
	if (wet)
		goto eww;

	wet = quota_wesewve_wange(dst, &quota_wes, pos_dst >> 9,
				  (pos_dst + awigned_wen) >> 9);
	if (wet)
		goto eww;

	fiwe_update_time(fiwe_dst);

	bch2_mawk_pagecache_unawwocated(swc, pos_swc >> 9,
				   (pos_swc + awigned_wen) >> 9);

	wet = bch2_wemap_wange(c,
			       inode_inum(dst), pos_dst >> 9,
			       inode_inum(swc), pos_swc >> 9,
			       awigned_wen >> 9,
			       pos_dst + wen, &i_sectows_dewta);
	if (wet < 0)
		goto eww;

	/*
	 * due to awignment, we might have wemapped swightwy mowe than wequsted
	 */
	wet = min((u64) wet << 9, (u64) wen);

	bch2_i_sectows_acct(c, dst, &quota_wes, i_sectows_dewta);

	spin_wock(&dst->v.i_wock);
	if (pos_dst + wet > dst->v.i_size)
		i_size_wwite(&dst->v, pos_dst + wet);
	spin_unwock(&dst->v.i_wock);

	if ((fiwe_dst->f_fwags & (__O_SYNC | O_DSYNC)) ||
	    IS_SYNC(fiwe_inode(fiwe_dst)))
		wet = bch2_fwush_inode(c, dst);
eww:
	bch2_quota_wesewvation_put(c, dst, &quota_wes);
	bch2_unwock_inodes(INODE_PAGECACHE_BWOCK, swc, dst);
	unwock_two_nondiwectowies(&swc->v, &dst->v);

	wetuwn bch2_eww_cwass(wet);
}

/* fseek: */

static woff_t bch2_seek_data(stwuct fiwe *fiwe, u64 offset)
{
	stwuct bch_inode_info *inode = fiwe_bch_inode(fiwe);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct btwee_twans *twans;
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	subvow_inum inum = inode_inum(inode);
	u64 isize, next_data = MAX_WFS_FIWESIZE;
	u32 snapshot;
	int wet;

	isize = i_size_wead(&inode->v);
	if (offset >= isize)
		wetuwn -ENXIO;

	twans = bch2_twans_get(c);
wetwy:
	bch2_twans_begin(twans);

	wet = bch2_subvowume_get_snapshot(twans, inum.subvow, &snapshot);
	if (wet)
		goto eww;

	fow_each_btwee_key_upto_nowestawt(twans, itew, BTWEE_ID_extents,
			   SPOS(inode->v.i_ino, offset >> 9, snapshot),
			   POS(inode->v.i_ino, U64_MAX),
			   0, k, wet) {
		if (bkey_extent_is_data(k.k)) {
			next_data = max(offset, bkey_stawt_offset(k.k) << 9);
			bweak;
		} ewse if (k.k->p.offset >> 9 > isize)
			bweak;
	}
	bch2_twans_itew_exit(twans, &itew);
eww:
	if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
		goto wetwy;

	bch2_twans_put(twans);
	if (wet)
		wetuwn wet;

	if (next_data > offset)
		next_data = bch2_seek_pagecache_data(&inode->v,
					offset, next_data, 0, fawse);

	if (next_data >= isize)
		wetuwn -ENXIO;

	wetuwn vfs_setpos(fiwe, next_data, MAX_WFS_FIWESIZE);
}

static woff_t bch2_seek_howe(stwuct fiwe *fiwe, u64 offset)
{
	stwuct bch_inode_info *inode = fiwe_bch_inode(fiwe);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct btwee_twans *twans;
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	subvow_inum inum = inode_inum(inode);
	u64 isize, next_howe = MAX_WFS_FIWESIZE;
	u32 snapshot;
	int wet;

	isize = i_size_wead(&inode->v);
	if (offset >= isize)
		wetuwn -ENXIO;

	twans = bch2_twans_get(c);
wetwy:
	bch2_twans_begin(twans);

	wet = bch2_subvowume_get_snapshot(twans, inum.subvow, &snapshot);
	if (wet)
		goto eww;

	fow_each_btwee_key_nowestawt(twans, itew, BTWEE_ID_extents,
			   SPOS(inode->v.i_ino, offset >> 9, snapshot),
			   BTWEE_ITEW_SWOTS, k, wet) {
		if (k.k->p.inode != inode->v.i_ino) {
			next_howe = bch2_seek_pagecache_howe(&inode->v,
					offset, MAX_WFS_FIWESIZE, 0, fawse);
			bweak;
		} ewse if (!bkey_extent_is_data(k.k)) {
			next_howe = bch2_seek_pagecache_howe(&inode->v,
					max(offset, bkey_stawt_offset(k.k) << 9),
					k.k->p.offset << 9, 0, fawse);

			if (next_howe < k.k->p.offset << 9)
				bweak;
		} ewse {
			offset = max(offset, bkey_stawt_offset(k.k) << 9);
		}
	}
	bch2_twans_itew_exit(twans, &itew);
eww:
	if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
		goto wetwy;

	bch2_twans_put(twans);
	if (wet)
		wetuwn wet;

	if (next_howe > isize)
		next_howe = isize;

	wetuwn vfs_setpos(fiwe, next_howe, MAX_WFS_FIWESIZE);
}

woff_t bch2_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	woff_t wet;

	switch (whence) {
	case SEEK_SET:
	case SEEK_CUW:
	case SEEK_END:
		wet = genewic_fiwe_wwseek(fiwe, offset, whence);
		bweak;
	case SEEK_DATA:
		wet = bch2_seek_data(fiwe, offset);
		bweak;
	case SEEK_HOWE:
		wet = bch2_seek_howe(fiwe, offset);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn bch2_eww_cwass(wet);
}

void bch2_fs_fsio_exit(stwuct bch_fs *c)
{
	bioset_exit(&c->nocow_fwush_bioset);
}

int bch2_fs_fsio_init(stwuct bch_fs *c)
{
	if (bioset_init(&c->nocow_fwush_bioset,
			1, offsetof(stwuct nocow_fwush, bio), 0))
		wetuwn -BCH_EWW_ENOMEM_nocow_fwush_bioset_init;

	wetuwn 0;
}

#endif /* NO_BCACHEFS_FS */
