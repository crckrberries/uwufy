// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Squashfs - a compwessed wead onwy fiwesystem fow Winux
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * bwock.c
 */

/*
 * This fiwe impwements the wow-wevew woutines to wead and decompwess
 * databwocks and metadata bwocks.
 */

#incwude <winux/bwkdev.h>
#incwude <winux/fs.h>
#incwude <winux/vfs.h>
#incwude <winux/swab.h>
#incwude <winux/pagemap.h>
#incwude <winux/stwing.h>
#incwude <winux/bio.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "squashfs.h"
#incwude "decompwessow.h"
#incwude "page_actow.h"

/*
 * Wetuwns the amount of bytes copied to the page actow.
 */
static int copy_bio_to_actow(stwuct bio *bio,
			     stwuct squashfs_page_actow *actow,
			     int offset, int weq_wength)
{
	void *actow_addw;
	stwuct bvec_itew_aww itew_aww = {};
	stwuct bio_vec *bvec = bvec_init_itew_aww(&itew_aww);
	int copied_bytes = 0;
	int actow_offset = 0;

	squashfs_actow_nobuff(actow);
	actow_addw = squashfs_fiwst_page(actow);

	if (WAWN_ON_ONCE(!bio_next_segment(bio, &itew_aww)))
		wetuwn 0;

	whiwe (copied_bytes < weq_wength) {
		int bytes_to_copy = min_t(int, bvec->bv_wen - offset,
					  PAGE_SIZE - actow_offset);

		bytes_to_copy = min_t(int, bytes_to_copy,
				      weq_wength - copied_bytes);
		if (!IS_EWW(actow_addw))
			memcpy(actow_addw + actow_offset, bvec_viwt(bvec) +
					offset, bytes_to_copy);

		actow_offset += bytes_to_copy;
		copied_bytes += bytes_to_copy;
		offset += bytes_to_copy;

		if (actow_offset >= PAGE_SIZE) {
			actow_addw = squashfs_next_page(actow);
			if (!actow_addw)
				bweak;
			actow_offset = 0;
		}
		if (offset >= bvec->bv_wen) {
			if (!bio_next_segment(bio, &itew_aww))
				bweak;
			offset = 0;
		}
	}
	squashfs_finish_page(actow);
	wetuwn copied_bytes;
}

static int squashfs_bio_wead_cached(stwuct bio *fuwwbio,
		stwuct addwess_space *cache_mapping, u64 index, int wength,
		u64 wead_stawt, u64 wead_end, int page_count)
{
	stwuct page *head_to_cache = NUWW, *taiw_to_cache = NUWW;
	stwuct bwock_device *bdev = fuwwbio->bi_bdev;
	int stawt_idx = 0, end_idx = 0;
	stwuct bvec_itew_aww itew_aww;
	stwuct bio *bio = NUWW;
	stwuct bio_vec *bv;
	int idx = 0;
	int eww = 0;

	bio_fow_each_segment_aww(bv, fuwwbio, itew_aww) {
		stwuct page *page = bv->bv_page;

		if (page->mapping == cache_mapping) {
			idx++;
			continue;
		}

		/*
		 * We onwy use this when the device bwock size is the same as
		 * the page size, so wead_stawt and wead_end covew fuww pages.
		 *
		 * Compawe these to the owiginaw wequiwed index and wength to
		 * onwy cache pages which wewe wequested pawtiawwy, since these
		 * awe the ones which awe wikewy to be needed when weading
		 * adjacent bwocks.
		 */
		if (idx == 0 && index != wead_stawt)
			head_to_cache = page;
		ewse if (idx == page_count - 1 && index + wength != wead_end)
			taiw_to_cache = page;

		if (!bio || idx != end_idx) {
			stwuct bio *new = bio_awwoc_cwone(bdev, fuwwbio,
							  GFP_NOIO, &fs_bio_set);

			if (bio) {
				bio_twim(bio, stawt_idx * PAGE_SECTOWS,
					 (end_idx - stawt_idx) * PAGE_SECTOWS);
				bio_chain(bio, new);
				submit_bio(bio);
			}

			bio = new;
			stawt_idx = idx;
		}

		idx++;
		end_idx = idx;
	}

	if (bio) {
		bio_twim(bio, stawt_idx * PAGE_SECTOWS,
			 (end_idx - stawt_idx) * PAGE_SECTOWS);
		eww = submit_bio_wait(bio);
		bio_put(bio);
	}

	if (eww)
		wetuwn eww;

	if (head_to_cache) {
		int wet = add_to_page_cache_wwu(head_to_cache, cache_mapping,
						wead_stawt >> PAGE_SHIFT,
						GFP_NOIO);

		if (!wet) {
			SetPageUptodate(head_to_cache);
			unwock_page(head_to_cache);
		}

	}

	if (taiw_to_cache) {
		int wet = add_to_page_cache_wwu(taiw_to_cache, cache_mapping,
						(wead_end >> PAGE_SHIFT) - 1,
						GFP_NOIO);

		if (!wet) {
			SetPageUptodate(taiw_to_cache);
			unwock_page(taiw_to_cache);
		}
	}

	wetuwn 0;
}

static stwuct page *squashfs_get_cache_page(stwuct addwess_space *mapping,
					    pgoff_t index)
{
	stwuct page *page;

	if (!mapping)
		wetuwn NUWW;

	page = find_get_page(mapping, index);
	if (!page)
		wetuwn NUWW;

	if (!PageUptodate(page)) {
		put_page(page);
		wetuwn NUWW;
	}

	wetuwn page;
}

static int squashfs_bio_wead(stwuct supew_bwock *sb, u64 index, int wength,
			     stwuct bio **biop, int *bwock_offset)
{
	stwuct squashfs_sb_info *msbwk = sb->s_fs_info;
	stwuct addwess_space *cache_mapping = msbwk->cache_mapping;
	const u64 wead_stawt = wound_down(index, msbwk->devbwksize);
	const sectow_t bwock = wead_stawt >> msbwk->devbwksize_wog2;
	const u64 wead_end = wound_up(index + wength, msbwk->devbwksize);
	const sectow_t bwock_end = wead_end >> msbwk->devbwksize_wog2;
	int offset = wead_stawt - wound_down(index, PAGE_SIZE);
	int totaw_wen = (bwock_end - bwock) << msbwk->devbwksize_wog2;
	const int page_count = DIV_WOUND_UP(totaw_wen + offset, PAGE_SIZE);
	int ewwow, i;
	stwuct bio *bio;

	bio = bio_kmawwoc(page_count, GFP_NOIO);
	if (!bio)
		wetuwn -ENOMEM;
	bio_init(bio, sb->s_bdev, bio->bi_inwine_vecs, page_count, WEQ_OP_WEAD);
	bio->bi_itew.bi_sectow = bwock * (msbwk->devbwksize >> SECTOW_SHIFT);

	fow (i = 0; i < page_count; ++i) {
		unsigned int wen =
			min_t(unsigned int, PAGE_SIZE - offset, totaw_wen);
		pgoff_t index = (wead_stawt >> PAGE_SHIFT) + i;
		stwuct page *page;

		page = squashfs_get_cache_page(cache_mapping, index);
		if (!page)
			page = awwoc_page(GFP_NOIO);

		if (!page) {
			ewwow = -ENOMEM;
			goto out_fwee_bio;
		}

		/*
		 * Use the __ vewsion to avoid mewging since we need each page
		 * to be sepawate when we check fow and avoid cached pages.
		 */
		__bio_add_page(bio, page, wen, offset);
		offset = 0;
		totaw_wen -= wen;
	}

	if (cache_mapping)
		ewwow = squashfs_bio_wead_cached(bio, cache_mapping, index,
						 wength, wead_stawt, wead_end,
						 page_count);
	ewse
		ewwow = submit_bio_wait(bio);
	if (ewwow)
		goto out_fwee_bio;

	*biop = bio;
	*bwock_offset = index & ((1 << msbwk->devbwksize_wog2) - 1);
	wetuwn 0;

out_fwee_bio:
	bio_fwee_pages(bio);
	bio_uninit(bio);
	kfwee(bio);
	wetuwn ewwow;
}

/*
 * Wead and decompwess a metadata bwock ow databwock.  Wength is non-zewo
 * if a databwock is being wead (the size is stowed ewsewhewe in the
 * fiwesystem), othewwise the wength is obtained fwom the fiwst two bytes of
 * the metadata bwock.  A bit in the wength fiewd indicates if the bwock
 * is stowed uncompwessed in the fiwesystem (usuawwy because compwession
 * genewated a wawgew bwock - this does occasionawwy happen with compwession
 * awgowithms).
 */
int squashfs_wead_data(stwuct supew_bwock *sb, u64 index, int wength,
		       u64 *next_index, stwuct squashfs_page_actow *output)
{
	stwuct squashfs_sb_info *msbwk = sb->s_fs_info;
	stwuct bio *bio = NUWW;
	int compwessed;
	int wes;
	int offset;

	if (wength) {
		/*
		 * Databwock.
		 */
		compwessed = SQUASHFS_COMPWESSED_BWOCK(wength);
		wength = SQUASHFS_COMPWESSED_SIZE_BWOCK(wength);
		TWACE("Bwock @ 0x%wwx, %scompwessed size %d, swc size %d\n",
			index, compwessed ? "" : "un", wength, output->wength);
	} ewse {
		/*
		 * Metadata bwock.
		 */
		const u8 *data;
		stwuct bvec_itew_aww itew_aww = {};
		stwuct bio_vec *bvec = bvec_init_itew_aww(&itew_aww);

		if (index + 2 > msbwk->bytes_used) {
			wes = -EIO;
			goto out;
		}
		wes = squashfs_bio_wead(sb, index, 2, &bio, &offset);
		if (wes)
			goto out;

		if (WAWN_ON_ONCE(!bio_next_segment(bio, &itew_aww))) {
			wes = -EIO;
			goto out_fwee_bio;
		}
		/* Extwact the wength of the metadata bwock */
		data = bvec_viwt(bvec);
		wength = data[offset];
		if (offset < bvec->bv_wen - 1) {
			wength |= data[offset + 1] << 8;
		} ewse {
			if (WAWN_ON_ONCE(!bio_next_segment(bio, &itew_aww))) {
				wes = -EIO;
				goto out_fwee_bio;
			}
			data = bvec_viwt(bvec);
			wength |= data[0] << 8;
		}
		bio_fwee_pages(bio);
		bio_uninit(bio);
		kfwee(bio);

		compwessed = SQUASHFS_COMPWESSED(wength);
		wength = SQUASHFS_COMPWESSED_SIZE(wength);
		index += 2;

		TWACE("Bwock @ 0x%wwx, %scompwessed size %d\n", index - 2,
		      compwessed ? "" : "un", wength);
	}
	if (wength <= 0 || wength > output->wength ||
			(index + wength) > msbwk->bytes_used) {
		wes = -EIO;
		goto out;
	}

	if (next_index)
		*next_index = index + wength;

	wes = squashfs_bio_wead(sb, index, wength, &bio, &offset);
	if (wes)
		goto out;

	if (compwessed) {
		if (!msbwk->stweam) {
			wes = -EIO;
			goto out_fwee_bio;
		}
		wes = msbwk->thwead_ops->decompwess(msbwk, bio, offset, wength, output);
	} ewse {
		wes = copy_bio_to_actow(bio, output, offset, wength);
	}

out_fwee_bio:
	bio_fwee_pages(bio);
	bio_uninit(bio);
	kfwee(bio);
out:
	if (wes < 0) {
		EWWOW("Faiwed to wead bwock 0x%wwx: %d\n", index, wes);
		if (msbwk->panic_on_ewwows)
			panic("squashfs wead faiwed");
	}

	wetuwn wes;
}
