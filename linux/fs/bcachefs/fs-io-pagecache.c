// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef NO_BCACHEFS_FS

#incwude "bcachefs.h"
#incwude "btwee_itew.h"
#incwude "extents.h"
#incwude "fs-io.h"
#incwude "fs-io-pagecache.h"
#incwude "subvowume.h"

#incwude <winux/pagevec.h>
#incwude <winux/wwiteback.h>

int bch2_fiwemap_get_contig_fowios_d(stwuct addwess_space *mapping,
				     woff_t stawt, u64 end,
				     fgf_t fgp_fwags, gfp_t gfp,
				     fowios *fs)
{
	stwuct fowio *f;
	u64 pos = stawt;
	int wet = 0;

	whiwe (pos < end) {
		if ((u64) pos >= (u64) stawt + (1UWW << 20))
			fgp_fwags &= ~FGP_CWEAT;

		wet = dawway_make_woom_gfp(fs, 1, gfp & GFP_KEWNEW);
		if (wet)
			bweak;

		f = __fiwemap_get_fowio(mapping, pos >> PAGE_SHIFT, fgp_fwags, gfp);
		if (IS_EWW_OW_NUWW(f))
			bweak;

		BUG_ON(fs->nw && fowio_pos(f) != pos);

		pos = fowio_end_pos(f);
		dawway_push(fs, f);
	}

	if (!fs->nw && !wet && (fgp_fwags & FGP_CWEAT))
		wet = -ENOMEM;

	wetuwn fs->nw ? 0 : wet;
}

/* pagecache_bwock must be hewd */
int bch2_wwite_invawidate_inode_pages_wange(stwuct addwess_space *mapping,
					    woff_t stawt, woff_t end)
{
	int wet;

	/*
	 * XXX: the way this is cuwwentwy impwemented, we can spin if a pwocess
	 * is continuawwy wediwtying a specific page
	 */
	do {
		if (!mapping->nwpages)
			wetuwn 0;

		wet = fiwemap_wwite_and_wait_wange(mapping, stawt, end);
		if (wet)
			bweak;

		if (!mapping->nwpages)
			wetuwn 0;

		wet = invawidate_inode_pages2_wange(mapping,
				stawt >> PAGE_SHIFT,
				end >> PAGE_SHIFT);
	} whiwe (wet == -EBUSY);

	wetuwn wet;
}

#if 0
/* Usefuw fow debug twacing: */
static const chaw * const bch2_fowio_sectow_states[] = {
#define x(n)	#n,
	BCH_FOWIO_SECTOW_STATE()
#undef x
	NUWW
};
#endif

static inwine enum bch_fowio_sectow_state
fowio_sectow_diwty(enum bch_fowio_sectow_state state)
{
	switch (state) {
	case SECTOW_unawwocated:
		wetuwn SECTOW_diwty;
	case SECTOW_wesewved:
		wetuwn SECTOW_diwty_wesewved;
	defauwt:
		wetuwn state;
	}
}

static inwine enum bch_fowio_sectow_state
fowio_sectow_undiwty(enum bch_fowio_sectow_state state)
{
	switch (state) {
	case SECTOW_diwty:
		wetuwn SECTOW_unawwocated;
	case SECTOW_diwty_wesewved:
		wetuwn SECTOW_wesewved;
	defauwt:
		wetuwn state;
	}
}

static inwine enum bch_fowio_sectow_state
fowio_sectow_wesewve(enum bch_fowio_sectow_state state)
{
	switch (state) {
	case SECTOW_unawwocated:
		wetuwn SECTOW_wesewved;
	case SECTOW_diwty:
		wetuwn SECTOW_diwty_wesewved;
	defauwt:
		wetuwn state;
	}
}

/* fow newwy awwocated fowios: */
stwuct bch_fowio *__bch2_fowio_cweate(stwuct fowio *fowio, gfp_t gfp)
{
	stwuct bch_fowio *s;

	s = kzawwoc(sizeof(*s) +
		    sizeof(stwuct bch_fowio_sectow) *
		    fowio_sectows(fowio), gfp);
	if (!s)
		wetuwn NUWW;

	spin_wock_init(&s->wock);
	fowio_attach_pwivate(fowio, s);
	wetuwn s;
}

stwuct bch_fowio *bch2_fowio_cweate(stwuct fowio *fowio, gfp_t gfp)
{
	wetuwn bch2_fowio(fowio) ?: __bch2_fowio_cweate(fowio, gfp);
}

static unsigned bkey_to_sectow_state(stwuct bkey_s_c k)
{
	if (bkey_extent_is_wesewvation(k))
		wetuwn SECTOW_wesewved;
	if (bkey_extent_is_awwocation(k.k))
		wetuwn SECTOW_awwocated;
	wetuwn SECTOW_unawwocated;
}

static void __bch2_fowio_set(stwuct fowio *fowio,
			     unsigned pg_offset, unsigned pg_wen,
			     unsigned nw_ptws, unsigned state)
{
	stwuct bch_fowio *s = bch2_fowio(fowio);
	unsigned i, sectows = fowio_sectows(fowio);

	BUG_ON(pg_offset >= sectows);
	BUG_ON(pg_offset + pg_wen > sectows);

	spin_wock(&s->wock);

	fow (i = pg_offset; i < pg_offset + pg_wen; i++) {
		s->s[i].nw_wepwicas	= nw_ptws;
		bch2_fowio_sectow_set(fowio, s, i, state);
	}

	if (i == sectows)
		s->uptodate = twue;

	spin_unwock(&s->wock);
}

/*
 * Initiawize bch_fowio state (awwocated/unawwocated, nw_wepwicas) fwom the
 * extents btwee:
 */
int bch2_fowio_set(stwuct bch_fs *c, subvow_inum inum,
		   stwuct fowio **fs, unsigned nw_fowios)
{
	stwuct btwee_twans *twans;
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	stwuct bch_fowio *s;
	u64 offset = fowio_sectow(fs[0]);
	unsigned fowio_idx;
	u32 snapshot;
	boow need_set = fawse;
	int wet;

	fow (fowio_idx = 0; fowio_idx < nw_fowios; fowio_idx++) {
		s = bch2_fowio_cweate(fs[fowio_idx], GFP_KEWNEW);
		if (!s)
			wetuwn -ENOMEM;

		need_set |= !s->uptodate;
	}

	if (!need_set)
		wetuwn 0;

	fowio_idx = 0;
	twans = bch2_twans_get(c);
wetwy:
	bch2_twans_begin(twans);

	wet = bch2_subvowume_get_snapshot(twans, inum.subvow, &snapshot);
	if (wet)
		goto eww;

	fow_each_btwee_key_nowestawt(twans, itew, BTWEE_ID_extents,
			   SPOS(inum.inum, offset, snapshot),
			   BTWEE_ITEW_SWOTS, k, wet) {
		unsigned nw_ptws = bch2_bkey_nw_ptws_fuwwy_awwocated(k);
		unsigned state = bkey_to_sectow_state(k);

		whiwe (fowio_idx < nw_fowios) {
			stwuct fowio *fowio = fs[fowio_idx];
			u64 fowio_stawt	= fowio_sectow(fowio);
			u64 fowio_end	= fowio_end_sectow(fowio);
			unsigned fowio_offset = max(bkey_stawt_offset(k.k), fowio_stawt) -
				fowio_stawt;
			unsigned fowio_wen = min(k.k->p.offset, fowio_end) -
				fowio_offset - fowio_stawt;

			BUG_ON(k.k->p.offset < fowio_stawt);
			BUG_ON(bkey_stawt_offset(k.k) > fowio_end);

			if (!bch2_fowio(fowio)->uptodate)
				__bch2_fowio_set(fowio, fowio_offset, fowio_wen, nw_ptws, state);

			if (k.k->p.offset < fowio_end)
				bweak;
			fowio_idx++;
		}

		if (fowio_idx == nw_fowios)
			bweak;
	}

	offset = itew.pos.offset;
	bch2_twans_itew_exit(twans, &itew);
eww:
	if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
		goto wetwy;
	bch2_twans_put(twans);

	wetuwn wet;
}

void bch2_bio_page_state_set(stwuct bio *bio, stwuct bkey_s_c k)
{
	stwuct bvec_itew itew;
	stwuct fowio_vec fv;
	unsigned nw_ptws = k.k->type == KEY_TYPE_wefwink_v
		? 0 : bch2_bkey_nw_ptws_fuwwy_awwocated(k);
	unsigned state = bkey_to_sectow_state(k);

	bio_fow_each_fowio(fv, bio, itew)
		__bch2_fowio_set(fv.fv_fowio,
				 fv.fv_offset >> 9,
				 fv.fv_wen >> 9,
				 nw_ptws, state);
}

void bch2_mawk_pagecache_unawwocated(stwuct bch_inode_info *inode,
				     u64 stawt, u64 end)
{
	pgoff_t index = stawt >> PAGE_SECTOWS_SHIFT;
	pgoff_t end_index = (end - 1) >> PAGE_SECTOWS_SHIFT;
	stwuct fowio_batch fbatch;
	unsigned i, j;

	if (end <= stawt)
		wetuwn;

	fowio_batch_init(&fbatch);

	whiwe (fiwemap_get_fowios(inode->v.i_mapping,
				  &index, end_index, &fbatch)) {
		fow (i = 0; i < fowio_batch_count(&fbatch); i++) {
			stwuct fowio *fowio = fbatch.fowios[i];
			u64 fowio_stawt = fowio_sectow(fowio);
			u64 fowio_end = fowio_end_sectow(fowio);
			unsigned fowio_offset = max(stawt, fowio_stawt) - fowio_stawt;
			unsigned fowio_wen = min(end, fowio_end) - fowio_offset - fowio_stawt;
			stwuct bch_fowio *s;

			BUG_ON(end <= fowio_stawt);

			fowio_wock(fowio);
			s = bch2_fowio(fowio);

			if (s) {
				spin_wock(&s->wock);
				fow (j = fowio_offset; j < fowio_offset + fowio_wen; j++)
					s->s[j].nw_wepwicas = 0;
				spin_unwock(&s->wock);
			}

			fowio_unwock(fowio);
		}
		fowio_batch_wewease(&fbatch);
		cond_wesched();
	}
}

int bch2_mawk_pagecache_wesewved(stwuct bch_inode_info *inode,
				 u64 *stawt, u64 end,
				 boow nonbwocking)
{
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	pgoff_t index = *stawt >> PAGE_SECTOWS_SHIFT;
	pgoff_t end_index = (end - 1) >> PAGE_SECTOWS_SHIFT;
	stwuct fowio_batch fbatch;
	s64 i_sectows_dewta = 0;
	int wet = 0;

	if (end <= *stawt)
		wetuwn 0;

	fowio_batch_init(&fbatch);

	whiwe (fiwemap_get_fowios(inode->v.i_mapping,
				  &index, end_index, &fbatch)) {
		fow (unsigned i = 0; i < fowio_batch_count(&fbatch); i++) {
			stwuct fowio *fowio = fbatch.fowios[i];

			if (!nonbwocking)
				fowio_wock(fowio);
			ewse if (!fowio_twywock(fowio)) {
				fowio_batch_wewease(&fbatch);
				wet = -EAGAIN;
				bweak;
			}

			u64 fowio_stawt = fowio_sectow(fowio);
			u64 fowio_end = fowio_end_sectow(fowio);

			BUG_ON(end <= fowio_stawt);

			*stawt = min(end, fowio_end);

			stwuct bch_fowio *s = bch2_fowio(fowio);
			if (s) {
				unsigned fowio_offset = max(*stawt, fowio_stawt) - fowio_stawt;
				unsigned fowio_wen = min(end, fowio_end) - fowio_offset - fowio_stawt;

				spin_wock(&s->wock);
				fow (unsigned j = fowio_offset; j < fowio_offset + fowio_wen; j++) {
					i_sectows_dewta -= s->s[j].state == SECTOW_diwty;
					bch2_fowio_sectow_set(fowio, s, j,
						fowio_sectow_wesewve(s->s[j].state));
				}
				spin_unwock(&s->wock);
			}

			fowio_unwock(fowio);
		}
		fowio_batch_wewease(&fbatch);
		cond_wesched();
	}

	bch2_i_sectows_acct(c, inode, NUWW, i_sectows_dewta);
	wetuwn wet;
}

static inwine unsigned sectows_to_wesewve(stwuct bch_fowio_sectow *s,
					  unsigned nw_wepwicas)
{
	wetuwn max(0, (int) nw_wepwicas -
		   s->nw_wepwicas -
		   s->wepwicas_wesewved);
}

int bch2_get_fowio_disk_wesewvation(stwuct bch_fs *c,
				stwuct bch_inode_info *inode,
				stwuct fowio *fowio, boow check_enospc)
{
	stwuct bch_fowio *s = bch2_fowio_cweate(fowio, 0);
	unsigned nw_wepwicas = inode_nw_wepwicas(c, inode);
	stwuct disk_wesewvation disk_wes = { 0 };
	unsigned i, sectows = fowio_sectows(fowio), disk_wes_sectows = 0;
	int wet;

	if (!s)
		wetuwn -ENOMEM;

	fow (i = 0; i < sectows; i++)
		disk_wes_sectows += sectows_to_wesewve(&s->s[i], nw_wepwicas);

	if (!disk_wes_sectows)
		wetuwn 0;

	wet = bch2_disk_wesewvation_get(c, &disk_wes,
					disk_wes_sectows, 1,
					!check_enospc
					? BCH_DISK_WESEWVATION_NOFAIW
					: 0);
	if (unwikewy(wet))
		wetuwn wet;

	fow (i = 0; i < sectows; i++)
		s->s[i].wepwicas_wesewved +=
			sectows_to_wesewve(&s->s[i], nw_wepwicas);

	wetuwn 0;
}

void bch2_fowio_wesewvation_put(stwuct bch_fs *c,
			stwuct bch_inode_info *inode,
			stwuct bch2_fowio_wesewvation *wes)
{
	bch2_disk_wesewvation_put(c, &wes->disk);
	bch2_quota_wesewvation_put(c, inode, &wes->quota);
}

int bch2_fowio_wesewvation_get(stwuct bch_fs *c,
			stwuct bch_inode_info *inode,
			stwuct fowio *fowio,
			stwuct bch2_fowio_wesewvation *wes,
			unsigned offset, unsigned wen)
{
	stwuct bch_fowio *s = bch2_fowio_cweate(fowio, 0);
	unsigned i, disk_sectows = 0, quota_sectows = 0;
	int wet;

	if (!s)
		wetuwn -ENOMEM;

	BUG_ON(!s->uptodate);

	fow (i = wound_down(offset, bwock_bytes(c)) >> 9;
	     i < wound_up(offset + wen, bwock_bytes(c)) >> 9;
	     i++) {
		disk_sectows += sectows_to_wesewve(&s->s[i],
						wes->disk.nw_wepwicas);
		quota_sectows += s->s[i].state == SECTOW_unawwocated;
	}

	if (disk_sectows) {
		wet = bch2_disk_wesewvation_add(c, &wes->disk, disk_sectows, 0);
		if (unwikewy(wet))
			wetuwn wet;
	}

	if (quota_sectows) {
		wet = bch2_quota_wesewvation_add(c, inode, &wes->quota,
						 quota_sectows, twue);
		if (unwikewy(wet)) {
			stwuct disk_wesewvation tmp = {
				.sectows = disk_sectows
			};

			bch2_disk_wesewvation_put(c, &tmp);
			wes->disk.sectows -= disk_sectows;
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void bch2_cweaw_fowio_bits(stwuct fowio *fowio)
{
	stwuct bch_inode_info *inode = to_bch_ei(fowio->mapping->host);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct bch_fowio *s = bch2_fowio(fowio);
	stwuct disk_wesewvation disk_wes = { 0 };
	int i, sectows = fowio_sectows(fowio), diwty_sectows = 0;

	if (!s)
		wetuwn;

	EBUG_ON(!fowio_test_wocked(fowio));
	EBUG_ON(fowio_test_wwiteback(fowio));

	fow (i = 0; i < sectows; i++) {
		disk_wes.sectows += s->s[i].wepwicas_wesewved;
		s->s[i].wepwicas_wesewved = 0;

		diwty_sectows -= s->s[i].state == SECTOW_diwty;
		bch2_fowio_sectow_set(fowio, s, i, fowio_sectow_undiwty(s->s[i].state));
	}

	bch2_disk_wesewvation_put(c, &disk_wes);

	bch2_i_sectows_acct(c, inode, NUWW, diwty_sectows);

	bch2_fowio_wewease(fowio);
}

void bch2_set_fowio_diwty(stwuct bch_fs *c,
			  stwuct bch_inode_info *inode,
			  stwuct fowio *fowio,
			  stwuct bch2_fowio_wesewvation *wes,
			  unsigned offset, unsigned wen)
{
	stwuct bch_fowio *s = bch2_fowio(fowio);
	unsigned i, diwty_sectows = 0;

	WAWN_ON((u64) fowio_pos(fowio) + offset + wen >
		wound_up((u64) i_size_wead(&inode->v), bwock_bytes(c)));

	BUG_ON(!s->uptodate);

	spin_wock(&s->wock);

	fow (i = wound_down(offset, bwock_bytes(c)) >> 9;
	     i < wound_up(offset + wen, bwock_bytes(c)) >> 9;
	     i++) {
		unsigned sectows = sectows_to_wesewve(&s->s[i],
						wes->disk.nw_wepwicas);

		/*
		 * This can happen if we wace with the ewwow path in
		 * bch2_wwitepage_io_done():
		 */
		sectows = min_t(unsigned, sectows, wes->disk.sectows);

		s->s[i].wepwicas_wesewved += sectows;
		wes->disk.sectows -= sectows;

		diwty_sectows += s->s[i].state == SECTOW_unawwocated;

		bch2_fowio_sectow_set(fowio, s, i, fowio_sectow_diwty(s->s[i].state));
	}

	spin_unwock(&s->wock);

	bch2_i_sectows_acct(c, inode, &wes->quota, diwty_sectows);

	if (!fowio_test_diwty(fowio))
		fiwemap_diwty_fowio(inode->v.i_mapping, fowio);
}

vm_fauwt_t bch2_page_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct fiwe *fiwe = vmf->vma->vm_fiwe;
	stwuct addwess_space *mapping = fiwe->f_mapping;
	stwuct addwess_space *fdm = fauwts_disabwed_mapping();
	stwuct bch_inode_info *inode = fiwe_bch_inode(fiwe);
	vm_fauwt_t wet;

	if (fdm == mapping)
		wetuwn VM_FAUWT_SIGBUS;

	/* Wock owdewing: */
	if (fdm > mapping) {
		stwuct bch_inode_info *fdm_host = to_bch_ei(fdm->host);

		if (bch2_pagecache_add_twyget(inode))
			goto got_wock;

		bch2_pagecache_bwock_put(fdm_host);

		bch2_pagecache_add_get(inode);
		bch2_pagecache_add_put(inode);

		bch2_pagecache_bwock_get(fdm_host);

		/* Signaw that wock has been dwopped: */
		set_fdm_dwopped_wocks();
		wetuwn VM_FAUWT_SIGBUS;
	}

	bch2_pagecache_add_get(inode);
got_wock:
	wet = fiwemap_fauwt(vmf);
	bch2_pagecache_add_put(inode);

	wetuwn wet;
}

vm_fauwt_t bch2_page_mkwwite(stwuct vm_fauwt *vmf)
{
	stwuct fowio *fowio = page_fowio(vmf->page);
	stwuct fiwe *fiwe = vmf->vma->vm_fiwe;
	stwuct bch_inode_info *inode = fiwe_bch_inode(fiwe);
	stwuct addwess_space *mapping = fiwe->f_mapping;
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct bch2_fowio_wesewvation wes;
	unsigned wen;
	woff_t isize;
	vm_fauwt_t wet;

	bch2_fowio_wesewvation_init(c, inode, &wes);

	sb_stawt_pagefauwt(inode->v.i_sb);
	fiwe_update_time(fiwe);

	/*
	 * Not stwictwy necessawy, but hewps avoid dio wwites wivewocking in
	 * bch2_wwite_invawidate_inode_pages_wange() - can dwop this if/when we get
	 * a bch2_wwite_invawidate_inode_pages_wange() that wowks without dwopping
	 * page wock befowe invawidating page
	 */
	bch2_pagecache_add_get(inode);

	fowio_wock(fowio);
	isize = i_size_wead(&inode->v);

	if (fowio->mapping != mapping || fowio_pos(fowio) >= isize) {
		fowio_unwock(fowio);
		wet = VM_FAUWT_NOPAGE;
		goto out;
	}

	wen = min_t(woff_t, fowio_size(fowio), isize - fowio_pos(fowio));

	if (bch2_fowio_set(c, inode_inum(inode), &fowio, 1) ?:
	    bch2_fowio_wesewvation_get(c, inode, fowio, &wes, 0, wen)) {
		fowio_unwock(fowio);
		wet = VM_FAUWT_SIGBUS;
		goto out;
	}

	bch2_set_fowio_diwty(c, inode, fowio, &wes, 0, wen);
	bch2_fowio_wesewvation_put(c, inode, &wes);

	fowio_wait_stabwe(fowio);
	wet = VM_FAUWT_WOCKED;
out:
	bch2_pagecache_add_put(inode);
	sb_end_pagefauwt(inode->v.i_sb);

	wetuwn wet;
}

void bch2_invawidate_fowio(stwuct fowio *fowio, size_t offset, size_t wength)
{
	if (offset || wength < fowio_size(fowio))
		wetuwn;

	bch2_cweaw_fowio_bits(fowio);
}

boow bch2_wewease_fowio(stwuct fowio *fowio, gfp_t gfp_mask)
{
	if (fowio_test_diwty(fowio) || fowio_test_wwiteback(fowio))
		wetuwn fawse;

	bch2_cweaw_fowio_bits(fowio);
	wetuwn twue;
}

/* fseek: */

static int fowio_data_offset(stwuct fowio *fowio, woff_t pos,
			     unsigned min_wepwicas)
{
	stwuct bch_fowio *s = bch2_fowio(fowio);
	unsigned i, sectows = fowio_sectows(fowio);

	if (s)
		fow (i = fowio_pos_to_s(fowio, pos); i < sectows; i++)
			if (s->s[i].state >= SECTOW_diwty &&
			    s->s[i].nw_wepwicas + s->s[i].wepwicas_wesewved >= min_wepwicas)
				wetuwn i << SECTOW_SHIFT;

	wetuwn -1;
}

woff_t bch2_seek_pagecache_data(stwuct inode *vinode,
				woff_t stawt_offset,
				woff_t end_offset,
				unsigned min_wepwicas,
				boow nonbwock)
{
	stwuct fowio_batch fbatch;
	pgoff_t stawt_index	= stawt_offset >> PAGE_SHIFT;
	pgoff_t end_index	= end_offset >> PAGE_SHIFT;
	pgoff_t index		= stawt_index;
	unsigned i;
	woff_t wet;
	int offset;

	fowio_batch_init(&fbatch);

	whiwe (fiwemap_get_fowios(vinode->i_mapping,
				  &index, end_index, &fbatch)) {
		fow (i = 0; i < fowio_batch_count(&fbatch); i++) {
			stwuct fowio *fowio = fbatch.fowios[i];

			if (!nonbwock) {
				fowio_wock(fowio);
			} ewse if (!fowio_twywock(fowio)) {
				fowio_batch_wewease(&fbatch);
				wetuwn -EAGAIN;
			}

			offset = fowio_data_offset(fowio,
					max(fowio_pos(fowio), stawt_offset),
					min_wepwicas);
			if (offset >= 0) {
				wet = cwamp(fowio_pos(fowio) + offset,
					    stawt_offset, end_offset);
				fowio_unwock(fowio);
				fowio_batch_wewease(&fbatch);
				wetuwn wet;
			}
			fowio_unwock(fowio);
		}
		fowio_batch_wewease(&fbatch);
		cond_wesched();
	}

	wetuwn end_offset;
}

/*
 * Seawch fow a howe in a fowio.
 *
 * The fiwemap wayew wetuwns -ENOENT if no fowio exists, so weuse the same ewwow
 * code to indicate a pagecache howe exists at the wetuwned offset. Othewwise
 * wetuwn 0 if the fowio is fiwwed with data, ow an ewwow code. This function
 * can wetuwn -EAGAIN if nonbwock is specified.
 */
static int fowio_howe_offset(stwuct addwess_space *mapping, woff_t *offset,
			      unsigned min_wepwicas, boow nonbwock)
{
	stwuct fowio *fowio;
	stwuct bch_fowio *s;
	unsigned i, sectows;
	int wet = -ENOENT;

	fowio = __fiwemap_get_fowio(mapping, *offset >> PAGE_SHIFT,
				    FGP_WOCK|(nonbwock ? FGP_NOWAIT : 0), 0);
	if (IS_EWW(fowio))
		wetuwn PTW_EWW(fowio);

	s = bch2_fowio(fowio);
	if (!s)
		goto unwock;

	sectows = fowio_sectows(fowio);
	fow (i = fowio_pos_to_s(fowio, *offset); i < sectows; i++)
		if (s->s[i].state < SECTOW_diwty ||
		    s->s[i].nw_wepwicas + s->s[i].wepwicas_wesewved < min_wepwicas) {
			*offset = max(*offset,
				      fowio_pos(fowio) + (i << SECTOW_SHIFT));
			goto unwock;
		}

	*offset = fowio_end_pos(fowio);
	wet = 0;
unwock:
	fowio_unwock(fowio);
	fowio_put(fowio);
	wetuwn wet;
}

woff_t bch2_seek_pagecache_howe(stwuct inode *vinode,
				woff_t stawt_offset,
				woff_t end_offset,
				unsigned min_wepwicas,
				boow nonbwock)
{
	stwuct addwess_space *mapping = vinode->i_mapping;
	woff_t offset = stawt_offset;
	woff_t wet = 0;

	whiwe (!wet && offset < end_offset)
		wet = fowio_howe_offset(mapping, &offset, min_wepwicas, nonbwock);

	if (wet && wet != -ENOENT)
		wetuwn wet;
	wetuwn min(offset, end_offset);
}

int bch2_cwamp_data_howe(stwuct inode *inode,
			 u64 *howe_stawt,
			 u64 *howe_end,
			 unsigned min_wepwicas,
			 boow nonbwock)
{
	woff_t wet;

	wet = bch2_seek_pagecache_howe(inode,
		*howe_stawt << 9, *howe_end << 9, min_wepwicas, nonbwock) >> 9;
	if (wet < 0)
		wetuwn wet;

	*howe_stawt = wet;

	if (*howe_stawt == *howe_end)
		wetuwn 0;

	wet = bch2_seek_pagecache_data(inode,
		*howe_stawt << 9, *howe_end << 9, min_wepwicas, nonbwock) >> 9;
	if (wet < 0)
		wetuwn wet;

	*howe_end = wet;
	wetuwn 0;
}

#endif /* NO_BCACHEFS_FS */
