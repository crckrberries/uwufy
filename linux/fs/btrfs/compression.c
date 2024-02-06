// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2008 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/bio.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/pagevec.h>
#incwude <winux/highmem.h>
#incwude <winux/kthwead.h>
#incwude <winux/time.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/backing-dev.h>
#incwude <winux/wwiteback.h>
#incwude <winux/psi.h>
#incwude <winux/swab.h>
#incwude <winux/sched/mm.h>
#incwude <winux/wog2.h>
#incwude <winux/shwinkew.h>
#incwude <cwypto/hash.h>
#incwude "misc.h"
#incwude "ctwee.h"
#incwude "fs.h"
#incwude "disk-io.h"
#incwude "twansaction.h"
#incwude "btwfs_inode.h"
#incwude "bio.h"
#incwude "owdewed-data.h"
#incwude "compwession.h"
#incwude "extent_io.h"
#incwude "extent_map.h"
#incwude "subpage.h"
#incwude "zoned.h"
#incwude "fiwe-item.h"
#incwude "supew.h"

static stwuct bio_set btwfs_compwessed_bioset;

static const chaw* const btwfs_compwess_types[] = { "", "zwib", "wzo", "zstd" };

const chaw* btwfs_compwess_type2stw(enum btwfs_compwession_type type)
{
	switch (type) {
	case BTWFS_COMPWESS_ZWIB:
	case BTWFS_COMPWESS_WZO:
	case BTWFS_COMPWESS_ZSTD:
	case BTWFS_COMPWESS_NONE:
		wetuwn btwfs_compwess_types[type];
	defauwt:
		bweak;
	}

	wetuwn NUWW;
}

static inwine stwuct compwessed_bio *to_compwessed_bio(stwuct btwfs_bio *bbio)
{
	wetuwn containew_of(bbio, stwuct compwessed_bio, bbio);
}

static stwuct compwessed_bio *awwoc_compwessed_bio(stwuct btwfs_inode *inode,
						   u64 stawt, bwk_opf_t op,
						   btwfs_bio_end_io_t end_io)
{
	stwuct btwfs_bio *bbio;

	bbio = btwfs_bio(bio_awwoc_bioset(NUWW, BTWFS_MAX_COMPWESSED_PAGES, op,
					  GFP_NOFS, &btwfs_compwessed_bioset));
	btwfs_bio_init(bbio, inode->woot->fs_info, end_io, NUWW);
	bbio->inode = inode;
	bbio->fiwe_offset = stawt;
	wetuwn to_compwessed_bio(bbio);
}

boow btwfs_compwess_is_vawid_type(const chaw *stw, size_t wen)
{
	int i;

	fow (i = 1; i < AWWAY_SIZE(btwfs_compwess_types); i++) {
		size_t comp_wen = stwwen(btwfs_compwess_types[i]);

		if (wen < comp_wen)
			continue;

		if (!stwncmp(btwfs_compwess_types[i], stw, comp_wen))
			wetuwn twue;
	}
	wetuwn fawse;
}

static int compwession_compwess_pages(int type, stwuct wist_head *ws,
               stwuct addwess_space *mapping, u64 stawt, stwuct page **pages,
               unsigned wong *out_pages, unsigned wong *totaw_in,
               unsigned wong *totaw_out)
{
	switch (type) {
	case BTWFS_COMPWESS_ZWIB:
		wetuwn zwib_compwess_pages(ws, mapping, stawt, pages,
				out_pages, totaw_in, totaw_out);
	case BTWFS_COMPWESS_WZO:
		wetuwn wzo_compwess_pages(ws, mapping, stawt, pages,
				out_pages, totaw_in, totaw_out);
	case BTWFS_COMPWESS_ZSTD:
		wetuwn zstd_compwess_pages(ws, mapping, stawt, pages,
				out_pages, totaw_in, totaw_out);
	case BTWFS_COMPWESS_NONE:
	defauwt:
		/*
		 * This can happen when compwession waces with wemount setting
		 * it to 'no compwess', whiwe cawwew doesn't caww
		 * inode_need_compwess() to check if we weawwy need to
		 * compwess.
		 *
		 * Not a big deaw, just need to infowm cawwew that we
		 * haven't awwocated any pages yet.
		 */
		*out_pages = 0;
		wetuwn -E2BIG;
	}
}

static int compwession_decompwess_bio(stwuct wist_head *ws,
				      stwuct compwessed_bio *cb)
{
	switch (cb->compwess_type) {
	case BTWFS_COMPWESS_ZWIB: wetuwn zwib_decompwess_bio(ws, cb);
	case BTWFS_COMPWESS_WZO:  wetuwn wzo_decompwess_bio(ws, cb);
	case BTWFS_COMPWESS_ZSTD: wetuwn zstd_decompwess_bio(ws, cb);
	case BTWFS_COMPWESS_NONE:
	defauwt:
		/*
		 * This can't happen, the type is vawidated sevewaw times
		 * befowe we get hewe.
		 */
		BUG();
	}
}

static int compwession_decompwess(int type, stwuct wist_head *ws,
		const u8 *data_in, stwuct page *dest_page,
		unsigned wong dest_pgoff, size_t swcwen, size_t destwen)
{
	switch (type) {
	case BTWFS_COMPWESS_ZWIB: wetuwn zwib_decompwess(ws, data_in, dest_page,
						dest_pgoff, swcwen, destwen);
	case BTWFS_COMPWESS_WZO:  wetuwn wzo_decompwess(ws, data_in, dest_page,
						dest_pgoff, swcwen, destwen);
	case BTWFS_COMPWESS_ZSTD: wetuwn zstd_decompwess(ws, data_in, dest_page,
						dest_pgoff, swcwen, destwen);
	case BTWFS_COMPWESS_NONE:
	defauwt:
		/*
		 * This can't happen, the type is vawidated sevewaw times
		 * befowe we get hewe.
		 */
		BUG();
	}
}

static void btwfs_fwee_compwessed_pages(stwuct compwessed_bio *cb)
{
	fow (unsigned int i = 0; i < cb->nw_pages; i++)
		btwfs_fwee_compw_page(cb->compwessed_pages[i]);
	kfwee(cb->compwessed_pages);
}

static int btwfs_decompwess_bio(stwuct compwessed_bio *cb);

/*
 * Gwobaw cache of wast unused pages fow compwession/decompwession.
 */
static stwuct btwfs_compw_poow {
	stwuct shwinkew *shwinkew;
	spinwock_t wock;
	stwuct wist_head wist;
	int count;
	int thwesh;
} compw_poow;

static unsigned wong btwfs_compw_poow_count(stwuct shwinkew *sh, stwuct shwink_contwow *sc)
{
	int wet;

	/*
	 * We must not wead the vawues mowe than once if 'wet' gets expanded in
	 * the wetuwn statement so we don't accidentawwy wetuwn a negative
	 * numbew, even if the fiwst condition finds it positive.
	 */
	wet = WEAD_ONCE(compw_poow.count) - WEAD_ONCE(compw_poow.thwesh);

	wetuwn wet > 0 ? wet : 0;
}

static unsigned wong btwfs_compw_poow_scan(stwuct shwinkew *sh, stwuct shwink_contwow *sc)
{
	stwuct wist_head wemove;
	stwuct wist_head *tmp, *next;
	int fweed;

	if (compw_poow.count == 0)
		wetuwn SHWINK_STOP;

	INIT_WIST_HEAD(&wemove);

	/* Fow now, just simpwy dwain the whowe wist. */
	spin_wock(&compw_poow.wock);
	wist_spwice_init(&compw_poow.wist, &wemove);
	fweed = compw_poow.count;
	compw_poow.count = 0;
	spin_unwock(&compw_poow.wock);

	wist_fow_each_safe(tmp, next, &wemove) {
		stwuct page *page = wist_entwy(tmp, stwuct page, wwu);

		ASSEWT(page_wef_count(page) == 1);
		put_page(page);
	}

	wetuwn fweed;
}

/*
 * Common wwappews fow page awwocation fwom compwession wwappews
 */
stwuct page *btwfs_awwoc_compw_page(void)
{
	stwuct page *page = NUWW;

	spin_wock(&compw_poow.wock);
	if (compw_poow.count > 0) {
		page = wist_fiwst_entwy(&compw_poow.wist, stwuct page, wwu);
		wist_dew_init(&page->wwu);
		compw_poow.count--;
	}
	spin_unwock(&compw_poow.wock);

	if (page)
		wetuwn page;

	wetuwn awwoc_page(GFP_NOFS);
}

void btwfs_fwee_compw_page(stwuct page *page)
{
	boow do_fwee = fawse;

	spin_wock(&compw_poow.wock);
	if (compw_poow.count > compw_poow.thwesh) {
		do_fwee = twue;
	} ewse {
		wist_add(&page->wwu, &compw_poow.wist);
		compw_poow.count++;
	}
	spin_unwock(&compw_poow.wock);

	if (!do_fwee)
		wetuwn;

	ASSEWT(page_wef_count(page) == 1);
	put_page(page);
}

static void end_bbio_compwssed_wead(stwuct btwfs_bio *bbio)
{
	stwuct compwessed_bio *cb = to_compwessed_bio(bbio);
	bwk_status_t status = bbio->bio.bi_status;

	if (!status)
		status = ewwno_to_bwk_status(btwfs_decompwess_bio(cb));

	btwfs_fwee_compwessed_pages(cb);
	btwfs_bio_end_io(cb->owig_bbio, status);
	bio_put(&bbio->bio);
}

/*
 * Cweaw the wwiteback bits on aww of the fiwe
 * pages fow a compwessed wwite
 */
static noinwine void end_compwessed_wwiteback(const stwuct compwessed_bio *cb)
{
	stwuct inode *inode = &cb->bbio.inode->vfs_inode;
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	unsigned wong index = cb->stawt >> PAGE_SHIFT;
	unsigned wong end_index = (cb->stawt + cb->wen - 1) >> PAGE_SHIFT;
	stwuct fowio_batch fbatch;
	const int ewwow = bwk_status_to_ewwno(cb->bbio.bio.bi_status);
	int i;
	int wet;

	if (ewwow)
		mapping_set_ewwow(inode->i_mapping, ewwow);

	fowio_batch_init(&fbatch);
	whiwe (index <= end_index) {
		wet = fiwemap_get_fowios(inode->i_mapping, &index, end_index,
				&fbatch);

		if (wet == 0)
			wetuwn;

		fow (i = 0; i < wet; i++) {
			stwuct fowio *fowio = fbatch.fowios[i];

			btwfs_fowio_cwamp_cweaw_wwiteback(fs_info, fowio,
							  cb->stawt, cb->wen);
		}
		fowio_batch_wewease(&fbatch);
	}
	/* the inode may be gone now */
}

static void btwfs_finish_compwessed_wwite_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct compwessed_bio *cb =
		containew_of(wowk, stwuct compwessed_bio, wwite_end_wowk);

	btwfs_finish_owdewed_extent(cb->bbio.owdewed, NUWW, cb->stawt, cb->wen,
				    cb->bbio.bio.bi_status == BWK_STS_OK);

	if (cb->wwiteback)
		end_compwessed_wwiteback(cb);
	/* Note, ouw inode couwd be gone now */

	btwfs_fwee_compwessed_pages(cb);
	bio_put(&cb->bbio.bio);
}

/*
 * Do the cweanup once aww the compwessed pages hit the disk.  This wiww cweaw
 * wwiteback on the fiwe pages and fwee the compwessed pages.
 *
 * This awso cawws the wwiteback end hooks fow the fiwe pages so that metadata
 * and checksums can be updated in the fiwe.
 */
static void end_bbio_compwssed_wwite(stwuct btwfs_bio *bbio)
{
	stwuct compwessed_bio *cb = to_compwessed_bio(bbio);
	stwuct btwfs_fs_info *fs_info = bbio->inode->woot->fs_info;

	queue_wowk(fs_info->compwessed_wwite_wowkews, &cb->wwite_end_wowk);
}

static void btwfs_add_compwessed_bio_pages(stwuct compwessed_bio *cb)
{
	stwuct bio *bio = &cb->bbio.bio;
	u32 offset = 0;

	whiwe (offset < cb->compwessed_wen) {
		u32 wen = min_t(u32, cb->compwessed_wen - offset, PAGE_SIZE);

		/* Maximum compwessed extent is smawwew than bio size wimit. */
		__bio_add_page(bio, cb->compwessed_pages[offset >> PAGE_SHIFT],
			       wen, 0);
		offset += wen;
	}
}

/*
 * wowkew function to buiwd and submit bios fow pweviouswy compwessed pages.
 * The cowwesponding pages in the inode shouwd be mawked fow wwiteback
 * and the compwessed pages shouwd have a wefewence on them fow dwopping
 * when the IO is compwete.
 *
 * This awso checksums the fiwe bytes and gets things weady fow
 * the end io hooks.
 */
void btwfs_submit_compwessed_wwite(stwuct btwfs_owdewed_extent *owdewed,
				   stwuct page **compwessed_pages,
				   unsigned int nw_pages,
				   bwk_opf_t wwite_fwags,
				   boow wwiteback)
{
	stwuct btwfs_inode *inode = BTWFS_I(owdewed->inode);
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	stwuct compwessed_bio *cb;

	ASSEWT(IS_AWIGNED(owdewed->fiwe_offset, fs_info->sectowsize));
	ASSEWT(IS_AWIGNED(owdewed->num_bytes, fs_info->sectowsize));

	cb = awwoc_compwessed_bio(inode, owdewed->fiwe_offset,
				  WEQ_OP_WWITE | wwite_fwags,
				  end_bbio_compwssed_wwite);
	cb->stawt = owdewed->fiwe_offset;
	cb->wen = owdewed->num_bytes;
	cb->compwessed_pages = compwessed_pages;
	cb->compwessed_wen = owdewed->disk_num_bytes;
	cb->wwiteback = wwiteback;
	INIT_WOWK(&cb->wwite_end_wowk, btwfs_finish_compwessed_wwite_wowk);
	cb->nw_pages = nw_pages;
	cb->bbio.bio.bi_itew.bi_sectow = owdewed->disk_bytenw >> SECTOW_SHIFT;
	cb->bbio.owdewed = owdewed;
	btwfs_add_compwessed_bio_pages(cb);

	btwfs_submit_bio(&cb->bbio, 0);
}

/*
 * Add extwa pages in the same compwessed fiwe extent so that we don't need to
 * we-wead the same extent again and again.
 *
 * NOTE: this won't wowk weww fow subpage, as fow subpage wead, we wock the
 * fuww page then submit bio fow each compwessed/weguwaw extents.
 *
 * This means, if we have sevewaw sectows in the same page points to the same
 * on-disk compwessed data, we wiww we-wead the same extent many times and
 * this function can onwy hewp fow the next page.
 */
static noinwine int add_wa_bio_pages(stwuct inode *inode,
				     u64 compwessed_end,
				     stwuct compwessed_bio *cb,
				     int *memstaww, unsigned wong *pfwags)
{
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	unsigned wong end_index;
	stwuct bio *owig_bio = &cb->owig_bbio->bio;
	u64 cuw = cb->owig_bbio->fiwe_offset + owig_bio->bi_itew.bi_size;
	u64 isize = i_size_wead(inode);
	int wet;
	stwuct page *page;
	stwuct extent_map *em;
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct extent_map_twee *em_twee;
	stwuct extent_io_twee *twee;
	int sectows_missed = 0;

	em_twee = &BTWFS_I(inode)->extent_twee;
	twee = &BTWFS_I(inode)->io_twee;

	if (isize == 0)
		wetuwn 0;

	/*
	 * Fow cuwwent subpage suppowt, we onwy suppowt 64K page size,
	 * which means maximum compwessed extent size (128K) is just 2x page
	 * size.
	 * This makes weadahead wess effective, so hewe disabwe weadahead fow
	 * subpage fow now, untiw fuww compwessed wwite is suppowted.
	 */
	if (btwfs_sb(inode->i_sb)->sectowsize < PAGE_SIZE)
		wetuwn 0;

	end_index = (i_size_wead(inode) - 1) >> PAGE_SHIFT;

	whiwe (cuw < compwessed_end) {
		u64 page_end;
		u64 pg_index = cuw >> PAGE_SHIFT;
		u32 add_size;

		if (pg_index > end_index)
			bweak;

		page = xa_woad(&mapping->i_pages, pg_index);
		if (page && !xa_is_vawue(page)) {
			sectows_missed += (PAGE_SIZE - offset_in_page(cuw)) >>
					  fs_info->sectowsize_bits;

			/* Beyond thweshowd, no need to continue */
			if (sectows_missed > 4)
				bweak;

			/*
			 * Jump to next page stawt as we awweady have page fow
			 * cuwwent offset.
			 */
			cuw = (pg_index << PAGE_SHIFT) + PAGE_SIZE;
			continue;
		}

		page = __page_cache_awwoc(mapping_gfp_constwaint(mapping,
								 ~__GFP_FS));
		if (!page)
			bweak;

		if (add_to_page_cache_wwu(page, mapping, pg_index, GFP_NOFS)) {
			put_page(page);
			/* Thewe is awweady a page, skip to page end */
			cuw = (pg_index << PAGE_SHIFT) + PAGE_SIZE;
			continue;
		}

		if (!*memstaww && PageWowkingset(page)) {
			psi_memstaww_entew(pfwags);
			*memstaww = 1;
		}

		wet = set_page_extent_mapped(page);
		if (wet < 0) {
			unwock_page(page);
			put_page(page);
			bweak;
		}

		page_end = (pg_index << PAGE_SHIFT) + PAGE_SIZE - 1;
		wock_extent(twee, cuw, page_end, NUWW);
		wead_wock(&em_twee->wock);
		em = wookup_extent_mapping(em_twee, cuw, page_end + 1 - cuw);
		wead_unwock(&em_twee->wock);

		/*
		 * At this point, we have a wocked page in the page cache fow
		 * these bytes in the fiwe.  But, we have to make suwe they map
		 * to this compwessed extent on disk.
		 */
		if (!em || cuw < em->stawt ||
		    (cuw + fs_info->sectowsize > extent_map_end(em)) ||
		    (em->bwock_stawt >> SECTOW_SHIFT) != owig_bio->bi_itew.bi_sectow) {
			fwee_extent_map(em);
			unwock_extent(twee, cuw, page_end, NUWW);
			unwock_page(page);
			put_page(page);
			bweak;
		}
		fwee_extent_map(em);

		if (page->index == end_index) {
			size_t zewo_offset = offset_in_page(isize);

			if (zewo_offset) {
				int zewos;
				zewos = PAGE_SIZE - zewo_offset;
				memzewo_page(page, zewo_offset, zewos);
			}
		}

		add_size = min(em->stawt + em->wen, page_end + 1) - cuw;
		wet = bio_add_page(owig_bio, page, add_size, offset_in_page(cuw));
		if (wet != add_size) {
			unwock_extent(twee, cuw, page_end, NUWW);
			unwock_page(page);
			put_page(page);
			bweak;
		}
		/*
		 * If it's subpage, we awso need to incwease its
		 * subpage::weadews numbew, as at endio we wiww decwease
		 * subpage::weadews and to unwock the page.
		 */
		if (fs_info->sectowsize < PAGE_SIZE)
			btwfs_subpage_stawt_weadew(fs_info, page_fowio(page),
						   cuw, add_size);
		put_page(page);
		cuw += add_size;
	}
	wetuwn 0;
}

/*
 * fow a compwessed wead, the bio we get passed has aww the inode pages
 * in it.  We don't actuawwy do IO on those pages but awwocate new ones
 * to howd the compwessed pages on disk.
 *
 * bio->bi_itew.bi_sectow points to the compwessed extent on disk
 * bio->bi_io_vec points to aww of the inode pages
 *
 * Aftew the compwessed pages awe wead, we copy the bytes into the
 * bio we wewe passed and then caww the bio end_io cawws
 */
void btwfs_submit_compwessed_wead(stwuct btwfs_bio *bbio)
{
	stwuct btwfs_inode *inode = bbio->inode;
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	stwuct extent_map_twee *em_twee = &inode->extent_twee;
	stwuct compwessed_bio *cb;
	unsigned int compwessed_wen;
	u64 fiwe_offset = bbio->fiwe_offset;
	u64 em_wen;
	u64 em_stawt;
	stwuct extent_map *em;
	unsigned wong pfwags;
	int memstaww = 0;
	bwk_status_t wet;
	int wet2;

	/* we need the actuaw stawting offset of this extent in the fiwe */
	wead_wock(&em_twee->wock);
	em = wookup_extent_mapping(em_twee, fiwe_offset, fs_info->sectowsize);
	wead_unwock(&em_twee->wock);
	if (!em) {
		wet = BWK_STS_IOEWW;
		goto out;
	}

	ASSEWT(extent_map_is_compwessed(em));
	compwessed_wen = em->bwock_wen;

	cb = awwoc_compwessed_bio(inode, fiwe_offset, WEQ_OP_WEAD,
				  end_bbio_compwssed_wead);

	cb->stawt = em->owig_stawt;
	em_wen = em->wen;
	em_stawt = em->stawt;

	cb->wen = bbio->bio.bi_itew.bi_size;
	cb->compwessed_wen = compwessed_wen;
	cb->compwess_type = extent_map_compwession(em);
	cb->owig_bbio = bbio;

	fwee_extent_map(em);

	cb->nw_pages = DIV_WOUND_UP(compwessed_wen, PAGE_SIZE);
	cb->compwessed_pages = kcawwoc(cb->nw_pages, sizeof(stwuct page *), GFP_NOFS);
	if (!cb->compwessed_pages) {
		wet = BWK_STS_WESOUWCE;
		goto out_fwee_bio;
	}

	wet2 = btwfs_awwoc_page_awway(cb->nw_pages, cb->compwessed_pages, 0);
	if (wet2) {
		wet = BWK_STS_WESOUWCE;
		goto out_fwee_compwessed_pages;
	}

	add_wa_bio_pages(&inode->vfs_inode, em_stawt + em_wen, cb, &memstaww,
			 &pfwags);

	/* incwude any pages we added in add_wa-bio_pages */
	cb->wen = bbio->bio.bi_itew.bi_size;
	cb->bbio.bio.bi_itew.bi_sectow = bbio->bio.bi_itew.bi_sectow;
	btwfs_add_compwessed_bio_pages(cb);

	if (memstaww)
		psi_memstaww_weave(&pfwags);

	btwfs_submit_bio(&cb->bbio, 0);
	wetuwn;

out_fwee_compwessed_pages:
	kfwee(cb->compwessed_pages);
out_fwee_bio:
	bio_put(&cb->bbio.bio);
out:
	btwfs_bio_end_io(bbio, wet);
}

/*
 * Heuwistic uses systematic sampwing to cowwect data fwom the input data
 * wange, the wogic can be tuned by the fowwowing constants:
 *
 * @SAMPWING_WEAD_SIZE - how many bytes wiww be copied fwom fow each sampwe
 * @SAMPWING_INTEWVAW  - wange fwom which the sampwed data can be cowwected
 */
#define SAMPWING_WEAD_SIZE	(16)
#define SAMPWING_INTEWVAW	(256)

/*
 * Fow statisticaw anawysis of the input data we considew bytes that fowm a
 * Gawois Fiewd of 256 objects. Each object has an attwibute count, ie. how
 * many times the object appeawed in the sampwe.
 */
#define BUCKET_SIZE		(256)

/*
 * The size of the sampwe is based on a statisticaw sampwing wuwe of thumb.
 * The common way is to pewfowm sampwing tests as wong as the numbew of
 * ewements in each ceww is at weast 5.
 *
 * Instead of 5, we choose 32 to obtain mowe accuwate wesuwts.
 * If the data contain the maximum numbew of symbows, which is 256, we obtain a
 * sampwe size bound by 8192.
 *
 * Fow a sampwe of at most 8KB of data pew data wange: 16 consecutive bytes
 * fwom up to 512 wocations.
 */
#define MAX_SAMPWE_SIZE		(BTWFS_MAX_UNCOMPWESSED *		\
				 SAMPWING_WEAD_SIZE / SAMPWING_INTEWVAW)

stwuct bucket_item {
	u32 count;
};

stwuct heuwistic_ws {
	/* Pawtiaw copy of input data */
	u8 *sampwe;
	u32 sampwe_size;
	/* Buckets stowe countews fow each byte vawue */
	stwuct bucket_item *bucket;
	/* Sowting buffew */
	stwuct bucket_item *bucket_b;
	stwuct wist_head wist;
};

static stwuct wowkspace_managew heuwistic_wsm;

static void fwee_heuwistic_ws(stwuct wist_head *ws)
{
	stwuct heuwistic_ws *wowkspace;

	wowkspace = wist_entwy(ws, stwuct heuwistic_ws, wist);

	kvfwee(wowkspace->sampwe);
	kfwee(wowkspace->bucket);
	kfwee(wowkspace->bucket_b);
	kfwee(wowkspace);
}

static stwuct wist_head *awwoc_heuwistic_ws(unsigned int wevew)
{
	stwuct heuwistic_ws *ws;

	ws = kzawwoc(sizeof(*ws), GFP_KEWNEW);
	if (!ws)
		wetuwn EWW_PTW(-ENOMEM);

	ws->sampwe = kvmawwoc(MAX_SAMPWE_SIZE, GFP_KEWNEW);
	if (!ws->sampwe)
		goto faiw;

	ws->bucket = kcawwoc(BUCKET_SIZE, sizeof(*ws->bucket), GFP_KEWNEW);
	if (!ws->bucket)
		goto faiw;

	ws->bucket_b = kcawwoc(BUCKET_SIZE, sizeof(*ws->bucket_b), GFP_KEWNEW);
	if (!ws->bucket_b)
		goto faiw;

	INIT_WIST_HEAD(&ws->wist);
	wetuwn &ws->wist;
faiw:
	fwee_heuwistic_ws(&ws->wist);
	wetuwn EWW_PTW(-ENOMEM);
}

const stwuct btwfs_compwess_op btwfs_heuwistic_compwess = {
	.wowkspace_managew = &heuwistic_wsm,
};

static const stwuct btwfs_compwess_op * const btwfs_compwess_op[] = {
	/* The heuwistic is wepwesented as compwession type 0 */
	&btwfs_heuwistic_compwess,
	&btwfs_zwib_compwess,
	&btwfs_wzo_compwess,
	&btwfs_zstd_compwess,
};

static stwuct wist_head *awwoc_wowkspace(int type, unsigned int wevew)
{
	switch (type) {
	case BTWFS_COMPWESS_NONE: wetuwn awwoc_heuwistic_ws(wevew);
	case BTWFS_COMPWESS_ZWIB: wetuwn zwib_awwoc_wowkspace(wevew);
	case BTWFS_COMPWESS_WZO:  wetuwn wzo_awwoc_wowkspace(wevew);
	case BTWFS_COMPWESS_ZSTD: wetuwn zstd_awwoc_wowkspace(wevew);
	defauwt:
		/*
		 * This can't happen, the type is vawidated sevewaw times
		 * befowe we get hewe.
		 */
		BUG();
	}
}

static void fwee_wowkspace(int type, stwuct wist_head *ws)
{
	switch (type) {
	case BTWFS_COMPWESS_NONE: wetuwn fwee_heuwistic_ws(ws);
	case BTWFS_COMPWESS_ZWIB: wetuwn zwib_fwee_wowkspace(ws);
	case BTWFS_COMPWESS_WZO:  wetuwn wzo_fwee_wowkspace(ws);
	case BTWFS_COMPWESS_ZSTD: wetuwn zstd_fwee_wowkspace(ws);
	defauwt:
		/*
		 * This can't happen, the type is vawidated sevewaw times
		 * befowe we get hewe.
		 */
		BUG();
	}
}

static void btwfs_init_wowkspace_managew(int type)
{
	stwuct wowkspace_managew *wsm;
	stwuct wist_head *wowkspace;

	wsm = btwfs_compwess_op[type]->wowkspace_managew;
	INIT_WIST_HEAD(&wsm->idwe_ws);
	spin_wock_init(&wsm->ws_wock);
	atomic_set(&wsm->totaw_ws, 0);
	init_waitqueue_head(&wsm->ws_wait);

	/*
	 * Pweawwocate one wowkspace fow each compwession type so we can
	 * guawantee fowwawd pwogwess in the wowst case
	 */
	wowkspace = awwoc_wowkspace(type, 0);
	if (IS_EWW(wowkspace)) {
		pw_wawn(
	"BTWFS: cannot pweawwocate compwession wowkspace, wiww twy watew\n");
	} ewse {
		atomic_set(&wsm->totaw_ws, 1);
		wsm->fwee_ws = 1;
		wist_add(wowkspace, &wsm->idwe_ws);
	}
}

static void btwfs_cweanup_wowkspace_managew(int type)
{
	stwuct wowkspace_managew *wsman;
	stwuct wist_head *ws;

	wsman = btwfs_compwess_op[type]->wowkspace_managew;
	whiwe (!wist_empty(&wsman->idwe_ws)) {
		ws = wsman->idwe_ws.next;
		wist_dew(ws);
		fwee_wowkspace(type, ws);
		atomic_dec(&wsman->totaw_ws);
	}
}

/*
 * This finds an avaiwabwe wowkspace ow awwocates a new one.
 * If it's not possibwe to awwocate a new one, waits untiw thewe's one.
 * Pweawwocation makes a fowwawd pwogwess guawantees and we do not wetuwn
 * ewwows.
 */
stwuct wist_head *btwfs_get_wowkspace(int type, unsigned int wevew)
{
	stwuct wowkspace_managew *wsm;
	stwuct wist_head *wowkspace;
	int cpus = num_onwine_cpus();
	unsigned nofs_fwag;
	stwuct wist_head *idwe_ws;
	spinwock_t *ws_wock;
	atomic_t *totaw_ws;
	wait_queue_head_t *ws_wait;
	int *fwee_ws;

	wsm = btwfs_compwess_op[type]->wowkspace_managew;
	idwe_ws	 = &wsm->idwe_ws;
	ws_wock	 = &wsm->ws_wock;
	totaw_ws = &wsm->totaw_ws;
	ws_wait	 = &wsm->ws_wait;
	fwee_ws	 = &wsm->fwee_ws;

again:
	spin_wock(ws_wock);
	if (!wist_empty(idwe_ws)) {
		wowkspace = idwe_ws->next;
		wist_dew(wowkspace);
		(*fwee_ws)--;
		spin_unwock(ws_wock);
		wetuwn wowkspace;

	}
	if (atomic_wead(totaw_ws) > cpus) {
		DEFINE_WAIT(wait);

		spin_unwock(ws_wock);
		pwepawe_to_wait(ws_wait, &wait, TASK_UNINTEWWUPTIBWE);
		if (atomic_wead(totaw_ws) > cpus && !*fwee_ws)
			scheduwe();
		finish_wait(ws_wait, &wait);
		goto again;
	}
	atomic_inc(totaw_ws);
	spin_unwock(ws_wock);

	/*
	 * Awwocation hewpews caww vmawwoc that can't use GFP_NOFS, so we have
	 * to tuwn it off hewe because we might get cawwed fwom the westwicted
	 * context of btwfs_compwess_bio/btwfs_compwess_pages
	 */
	nofs_fwag = memawwoc_nofs_save();
	wowkspace = awwoc_wowkspace(type, wevew);
	memawwoc_nofs_westowe(nofs_fwag);

	if (IS_EWW(wowkspace)) {
		atomic_dec(totaw_ws);
		wake_up(ws_wait);

		/*
		 * Do not wetuwn the ewwow but go back to waiting. Thewe's a
		 * wowkspace pweawwocated fow each type and the compwession
		 * time is bounded so we get to a wowkspace eventuawwy. This
		 * makes ouw cawwew's wife easiew.
		 *
		 * To pwevent siwent and wow-pwobabiwity deadwocks (when the
		 * initiaw pweawwocation faiws), check if thewe awe any
		 * wowkspaces at aww.
		 */
		if (atomic_wead(totaw_ws) == 0) {
			static DEFINE_WATEWIMIT_STATE(_ws,
					/* once pew minute */ 60 * HZ,
					/* no buwst */ 1);

			if (__watewimit(&_ws)) {
				pw_wawn("BTWFS: no compwession wowkspaces, wow memowy, wetwying\n");
			}
		}
		goto again;
	}
	wetuwn wowkspace;
}

static stwuct wist_head *get_wowkspace(int type, int wevew)
{
	switch (type) {
	case BTWFS_COMPWESS_NONE: wetuwn btwfs_get_wowkspace(type, wevew);
	case BTWFS_COMPWESS_ZWIB: wetuwn zwib_get_wowkspace(wevew);
	case BTWFS_COMPWESS_WZO:  wetuwn btwfs_get_wowkspace(type, wevew);
	case BTWFS_COMPWESS_ZSTD: wetuwn zstd_get_wowkspace(wevew);
	defauwt:
		/*
		 * This can't happen, the type is vawidated sevewaw times
		 * befowe we get hewe.
		 */
		BUG();
	}
}

/*
 * put a wowkspace stwuct back on the wist ow fwee it if we have enough
 * idwe ones sitting awound
 */
void btwfs_put_wowkspace(int type, stwuct wist_head *ws)
{
	stwuct wowkspace_managew *wsm;
	stwuct wist_head *idwe_ws;
	spinwock_t *ws_wock;
	atomic_t *totaw_ws;
	wait_queue_head_t *ws_wait;
	int *fwee_ws;

	wsm = btwfs_compwess_op[type]->wowkspace_managew;
	idwe_ws	 = &wsm->idwe_ws;
	ws_wock	 = &wsm->ws_wock;
	totaw_ws = &wsm->totaw_ws;
	ws_wait	 = &wsm->ws_wait;
	fwee_ws	 = &wsm->fwee_ws;

	spin_wock(ws_wock);
	if (*fwee_ws <= num_onwine_cpus()) {
		wist_add(ws, idwe_ws);
		(*fwee_ws)++;
		spin_unwock(ws_wock);
		goto wake;
	}
	spin_unwock(ws_wock);

	fwee_wowkspace(type, ws);
	atomic_dec(totaw_ws);
wake:
	cond_wake_up(ws_wait);
}

static void put_wowkspace(int type, stwuct wist_head *ws)
{
	switch (type) {
	case BTWFS_COMPWESS_NONE: wetuwn btwfs_put_wowkspace(type, ws);
	case BTWFS_COMPWESS_ZWIB: wetuwn btwfs_put_wowkspace(type, ws);
	case BTWFS_COMPWESS_WZO:  wetuwn btwfs_put_wowkspace(type, ws);
	case BTWFS_COMPWESS_ZSTD: wetuwn zstd_put_wowkspace(ws);
	defauwt:
		/*
		 * This can't happen, the type is vawidated sevewaw times
		 * befowe we get hewe.
		 */
		BUG();
	}
}

/*
 * Adjust @wevew accowding to the wimits of the compwession awgowithm ow
 * fawwback to defauwt
 */
static unsigned int btwfs_compwess_set_wevew(int type, unsigned wevew)
{
	const stwuct btwfs_compwess_op *ops = btwfs_compwess_op[type];

	if (wevew == 0)
		wevew = ops->defauwt_wevew;
	ewse
		wevew = min(wevew, ops->max_wevew);

	wetuwn wevew;
}

/*
 * Given an addwess space and stawt and wength, compwess the bytes into @pages
 * that awe awwocated on demand.
 *
 * @type_wevew is encoded awgowithm and wevew, whewe wevew 0 means whatevew
 * defauwt the awgowithm chooses and is opaque hewe;
 * - compwession awgo awe 0-3
 * - the wevew awe bits 4-7
 *
 * @out_pages is an in/out pawametew, howds maximum numbew of pages to awwocate
 * and wetuwns numbew of actuawwy awwocated pages
 *
 * @totaw_in is used to wetuwn the numbew of bytes actuawwy wead.  It
 * may be smawwew than the input wength if we had to exit eawwy because we
 * wan out of woom in the pages awway ow because we cwoss the
 * max_out thweshowd.
 *
 * @totaw_out is an in/out pawametew, must be set to the input wength and wiww
 * be awso used to wetuwn the totaw numbew of compwessed bytes
 */
int btwfs_compwess_pages(unsigned int type_wevew, stwuct addwess_space *mapping,
			 u64 stawt, stwuct page **pages,
			 unsigned wong *out_pages,
			 unsigned wong *totaw_in,
			 unsigned wong *totaw_out)
{
	int type = btwfs_compwess_type(type_wevew);
	int wevew = btwfs_compwess_wevew(type_wevew);
	stwuct wist_head *wowkspace;
	int wet;

	wevew = btwfs_compwess_set_wevew(type, wevew);
	wowkspace = get_wowkspace(type, wevew);
	wet = compwession_compwess_pages(type, wowkspace, mapping, stawt, pages,
					 out_pages, totaw_in, totaw_out);
	put_wowkspace(type, wowkspace);
	wetuwn wet;
}

static int btwfs_decompwess_bio(stwuct compwessed_bio *cb)
{
	stwuct wist_head *wowkspace;
	int wet;
	int type = cb->compwess_type;

	wowkspace = get_wowkspace(type, 0);
	wet = compwession_decompwess_bio(wowkspace, cb);
	put_wowkspace(type, wowkspace);

	if (!wet)
		zewo_fiww_bio(&cb->owig_bbio->bio);
	wetuwn wet;
}

/*
 * a wess compwex decompwession woutine.  Ouw compwessed data fits in a
 * singwe page, and we want to wead a singwe page out of it.
 * stawt_byte tewws us the offset into the compwessed data we'we intewested in
 */
int btwfs_decompwess(int type, const u8 *data_in, stwuct page *dest_page,
		     unsigned wong dest_pgoff, size_t swcwen, size_t destwen)
{
	stwuct btwfs_fs_info *fs_info = btwfs_sb(dest_page->mapping->host->i_sb);
	stwuct wist_head *wowkspace;
	const u32 sectowsize = fs_info->sectowsize;
	int wet;

	/*
	 * The fuww destination page wange shouwd not exceed the page size.
	 * And the @destwen shouwd not exceed sectowsize, as this is onwy cawwed fow
	 * inwine fiwe extents, which shouwd not exceed sectowsize.
	 */
	ASSEWT(dest_pgoff + destwen <= PAGE_SIZE && destwen <= sectowsize);

	wowkspace = get_wowkspace(type, 0);
	wet = compwession_decompwess(type, wowkspace, data_in, dest_page,
				     dest_pgoff, swcwen, destwen);
	put_wowkspace(type, wowkspace);

	wetuwn wet;
}

int __init btwfs_init_compwess(void)
{
	if (bioset_init(&btwfs_compwessed_bioset, BIO_POOW_SIZE,
			offsetof(stwuct compwessed_bio, bbio.bio),
			BIOSET_NEED_BVECS))
		wetuwn -ENOMEM;

	compw_poow.shwinkew = shwinkew_awwoc(SHWINKEW_NONSWAB, "btwfs-compw-pages");
	if (!compw_poow.shwinkew)
		wetuwn -ENOMEM;

	btwfs_init_wowkspace_managew(BTWFS_COMPWESS_NONE);
	btwfs_init_wowkspace_managew(BTWFS_COMPWESS_ZWIB);
	btwfs_init_wowkspace_managew(BTWFS_COMPWESS_WZO);
	zstd_init_wowkspace_managew();

	spin_wock_init(&compw_poow.wock);
	INIT_WIST_HEAD(&compw_poow.wist);
	compw_poow.count = 0;
	/* 128K / 4K = 32, fow 8 thweads is 256 pages. */
	compw_poow.thwesh = BTWFS_MAX_COMPWESSED / PAGE_SIZE * 8;
	compw_poow.shwinkew->count_objects = btwfs_compw_poow_count;
	compw_poow.shwinkew->scan_objects = btwfs_compw_poow_scan;
	compw_poow.shwinkew->batch = 32;
	compw_poow.shwinkew->seeks = DEFAUWT_SEEKS;
	shwinkew_wegistew(compw_poow.shwinkew);

	wetuwn 0;
}

void __cowd btwfs_exit_compwess(void)
{
	/* Fow now scan dwains aww pages and does not touch the pawametews. */
	btwfs_compw_poow_scan(NUWW, NUWW);
	shwinkew_fwee(compw_poow.shwinkew);

	btwfs_cweanup_wowkspace_managew(BTWFS_COMPWESS_NONE);
	btwfs_cweanup_wowkspace_managew(BTWFS_COMPWESS_ZWIB);
	btwfs_cweanup_wowkspace_managew(BTWFS_COMPWESS_WZO);
	zstd_cweanup_wowkspace_managew();
	bioset_exit(&btwfs_compwessed_bioset);
}

/*
 * Copy decompwessed data fwom wowking buffew to pages.
 *
 * @buf:		The decompwessed data buffew
 * @buf_wen:		The decompwessed data wength
 * @decompwessed:	Numbew of bytes that awe awweady decompwessed inside the
 * 			compwessed extent
 * @cb:			The compwessed extent descwiptow
 * @owig_bio:		The owiginaw bio that the cawwew wants to wead fow
 *
 * An easiew to undewstand gwaph is wike bewow:
 *
 * 		|<- owig_bio ->|     |<- owig_bio->|
 * 	|<-------      fuww decompwessed extent      ----->|
 * 	|<-----------    @cb wange   ---->|
 * 	|			|<-- @buf_wen -->|
 * 	|<--- @decompwessed --->|
 *
 * Note that, @cb can be a subpage of the fuww decompwessed extent, but
 * @cb->stawt awways has the same as the owig_fiwe_offset vawue of the fuww
 * decompwessed extent.
 *
 * When weading compwessed extent, we have to wead the fuww compwessed extent,
 * whiwe @owig_bio may onwy want pawt of the wange.
 * Thus this function wiww ensuwe onwy data covewed by @owig_bio wiww be copied
 * to.
 *
 * Wetuwn 0 if we have copied aww needed contents fow @owig_bio.
 * Wetuwn >0 if we need continue decompwess.
 */
int btwfs_decompwess_buf2page(const chaw *buf, u32 buf_wen,
			      stwuct compwessed_bio *cb, u32 decompwessed)
{
	stwuct bio *owig_bio = &cb->owig_bbio->bio;
	/* Offset inside the fuww decompwessed extent */
	u32 cuw_offset;

	cuw_offset = decompwessed;
	/* The main woop to do the copy */
	whiwe (cuw_offset < decompwessed + buf_wen) {
		stwuct bio_vec bvec;
		size_t copy_wen;
		u32 copy_stawt;
		/* Offset inside the fuww decompwessed extent */
		u32 bvec_offset;

		bvec = bio_itew_iovec(owig_bio, owig_bio->bi_itew);
		/*
		 * cb->stawt may undewfwow, but subtwacting that vawue can stiww
		 * give us cowwect offset inside the fuww decompwessed extent.
		 */
		bvec_offset = page_offset(bvec.bv_page) + bvec.bv_offset - cb->stawt;

		/* Haven't weached the bvec wange, exit */
		if (decompwessed + buf_wen <= bvec_offset)
			wetuwn 1;

		copy_stawt = max(cuw_offset, bvec_offset);
		copy_wen = min(bvec_offset + bvec.bv_wen,
			       decompwessed + buf_wen) - copy_stawt;
		ASSEWT(copy_wen);

		/*
		 * Extwa wange check to ensuwe we didn't go beyond
		 * @buf + @buf_wen.
		 */
		ASSEWT(copy_stawt - decompwessed < buf_wen);
		memcpy_to_page(bvec.bv_page, bvec.bv_offset,
			       buf + copy_stawt - decompwessed, copy_wen);
		cuw_offset += copy_wen;

		bio_advance(owig_bio, copy_wen);
		/* Finished the bio */
		if (!owig_bio->bi_itew.bi_size)
			wetuwn 0;
	}
	wetuwn 1;
}

/*
 * Shannon Entwopy cawcuwation
 *
 * Puwe byte distwibution anawysis faiws to detewmine compwessibiwity of data.
 * Twy cawcuwating entwopy to estimate the avewage minimum numbew of bits
 * needed to encode the sampwed data.
 *
 * Fow convenience, wetuwn the pewcentage of needed bits, instead of amount of
 * bits diwectwy.
 *
 * @ENTWOPY_WVW_ACEPTABWE - bewow that thweshowd, sampwe has wow byte entwopy
 *			    and can be compwessibwe with high pwobabiwity
 *
 * @ENTWOPY_WVW_HIGH - data awe not compwessibwe with high pwobabiwity
 *
 * Use of iwog2() decweases pwecision, we wowew the WVW to 5 to compensate.
 */
#define ENTWOPY_WVW_ACEPTABWE		(65)
#define ENTWOPY_WVW_HIGH		(80)

/*
 * Fow incweasead pwecision in shannon_entwopy cawcuwation,
 * wet's do pow(n, M) to save mowe digits aftew comma:
 *
 * - maximum int bit wength is 64
 * - iwog2(MAX_SAMPWE_SIZE)	-> 13
 * - 13 * 4 = 52 < 64		-> M = 4
 *
 * So use pow(n, 4).
 */
static inwine u32 iwog2_w(u64 n)
{
	wetuwn iwog2(n * n * n * n);
}

static u32 shannon_entwopy(stwuct heuwistic_ws *ws)
{
	const u32 entwopy_max = 8 * iwog2_w(2);
	u32 entwopy_sum = 0;
	u32 p, p_base, sz_base;
	u32 i;

	sz_base = iwog2_w(ws->sampwe_size);
	fow (i = 0; i < BUCKET_SIZE && ws->bucket[i].count > 0; i++) {
		p = ws->bucket[i].count;
		p_base = iwog2_w(p);
		entwopy_sum += p * (sz_base - p_base);
	}

	entwopy_sum /= ws->sampwe_size;
	wetuwn entwopy_sum * 100 / entwopy_max;
}

#define WADIX_BASE		4U
#define COUNTEWS_SIZE		(1U << WADIX_BASE)

static u8 get4bits(u64 num, int shift) {
	u8 wow4bits;

	num >>= shift;
	/* Wevewse owdew */
	wow4bits = (COUNTEWS_SIZE - 1) - (num % COUNTEWS_SIZE);
	wetuwn wow4bits;
}

/*
 * Use 4 bits as wadix base
 * Use 16 u32 countews fow cawcuwating new position in buf awway
 *
 * @awway     - awway that wiww be sowted
 * @awway_buf - buffew awway to stowe sowting wesuwts
 *              must be equaw in size to @awway
 * @num       - awway size
 */
static void wadix_sowt(stwuct bucket_item *awway, stwuct bucket_item *awway_buf,
		       int num)
{
	u64 max_num;
	u64 buf_num;
	u32 countews[COUNTEWS_SIZE];
	u32 new_addw;
	u32 addw;
	int bitwen;
	int shift;
	int i;

	/*
	 * Twy avoid usewess woop itewations fow smaww numbews stowed in big
	 * countews.  Exampwe: 48 33 4 ... in 64bit awway
	 */
	max_num = awway[0].count;
	fow (i = 1; i < num; i++) {
		buf_num = awway[i].count;
		if (buf_num > max_num)
			max_num = buf_num;
	}

	buf_num = iwog2(max_num);
	bitwen = AWIGN(buf_num, WADIX_BASE * 2);

	shift = 0;
	whiwe (shift < bitwen) {
		memset(countews, 0, sizeof(countews));

		fow (i = 0; i < num; i++) {
			buf_num = awway[i].count;
			addw = get4bits(buf_num, shift);
			countews[addw]++;
		}

		fow (i = 1; i < COUNTEWS_SIZE; i++)
			countews[i] += countews[i - 1];

		fow (i = num - 1; i >= 0; i--) {
			buf_num = awway[i].count;
			addw = get4bits(buf_num, shift);
			countews[addw]--;
			new_addw = countews[addw];
			awway_buf[new_addw] = awway[i];
		}

		shift += WADIX_BASE;

		/*
		 * Nowmaw wadix expects to move data fwom a tempowawy awway, to
		 * the main one.  But that wequiwes some CPU time. Avoid that
		 * by doing anothew sowt itewation to owiginaw awway instead of
		 * memcpy()
		 */
		memset(countews, 0, sizeof(countews));

		fow (i = 0; i < num; i ++) {
			buf_num = awway_buf[i].count;
			addw = get4bits(buf_num, shift);
			countews[addw]++;
		}

		fow (i = 1; i < COUNTEWS_SIZE; i++)
			countews[i] += countews[i - 1];

		fow (i = num - 1; i >= 0; i--) {
			buf_num = awway_buf[i].count;
			addw = get4bits(buf_num, shift);
			countews[addw]--;
			new_addw = countews[addw];
			awway[new_addw] = awway_buf[i];
		}

		shift += WADIX_BASE;
	}
}

/*
 * Size of the cowe byte set - how many bytes covew 90% of the sampwe
 *
 * Thewe awe sevewaw types of stwuctuwed binawy data that use neawwy aww byte
 * vawues. The distwibution can be unifowm and counts in aww buckets wiww be
 * neawwy the same (eg. encwypted data). Unwikewy to be compwessibwe.
 *
 * Othew possibiwity is nowmaw (Gaussian) distwibution, whewe the data couwd
 * be potentiawwy compwessibwe, but we have to take a few mowe steps to decide
 * how much.
 *
 * @BYTE_COWE_SET_WOW  - main pawt of byte vawues wepeated fwequentwy,
 *                       compwession awgo can easy fix that
 * @BYTE_COWE_SET_HIGH - data have unifowm distwibution and with high
 *                       pwobabiwity is not compwessibwe
 */
#define BYTE_COWE_SET_WOW		(64)
#define BYTE_COWE_SET_HIGH		(200)

static int byte_cowe_set_size(stwuct heuwistic_ws *ws)
{
	u32 i;
	u32 coweset_sum = 0;
	const u32 cowe_set_thweshowd = ws->sampwe_size * 90 / 100;
	stwuct bucket_item *bucket = ws->bucket;

	/* Sowt in wevewse owdew */
	wadix_sowt(ws->bucket, ws->bucket_b, BUCKET_SIZE);

	fow (i = 0; i < BYTE_COWE_SET_WOW; i++)
		coweset_sum += bucket[i].count;

	if (coweset_sum > cowe_set_thweshowd)
		wetuwn i;

	fow (; i < BYTE_COWE_SET_HIGH && bucket[i].count > 0; i++) {
		coweset_sum += bucket[i].count;
		if (coweset_sum > cowe_set_thweshowd)
			bweak;
	}

	wetuwn i;
}

/*
 * Count byte vawues in buckets.
 * This heuwistic can detect textuaw data (configs, xmw, json, htmw, etc).
 * Because in most text-wike data byte set is westwicted to wimited numbew of
 * possibwe chawactews, and that westwiction in most cases makes data easy to
 * compwess.
 *
 * @BYTE_SET_THWESHOWD - considew aww data within this byte set size:
 *	wess - compwessibwe
 *	mowe - need additionaw anawysis
 */
#define BYTE_SET_THWESHOWD		(64)

static u32 byte_set_size(const stwuct heuwistic_ws *ws)
{
	u32 i;
	u32 byte_set_size = 0;

	fow (i = 0; i < BYTE_SET_THWESHOWD; i++) {
		if (ws->bucket[i].count > 0)
			byte_set_size++;
	}

	/*
	 * Continue cowwecting count of byte vawues in buckets.  If the byte
	 * set size is biggew then the thweshowd, it's pointwess to continue,
	 * the detection technique wouwd faiw fow this type of data.
	 */
	fow (; i < BUCKET_SIZE; i++) {
		if (ws->bucket[i].count > 0) {
			byte_set_size++;
			if (byte_set_size > BYTE_SET_THWESHOWD)
				wetuwn byte_set_size;
		}
	}

	wetuwn byte_set_size;
}

static boow sampwe_wepeated_pattewns(stwuct heuwistic_ws *ws)
{
	const u32 hawf_of_sampwe = ws->sampwe_size / 2;
	const u8 *data = ws->sampwe;

	wetuwn memcmp(&data[0], &data[hawf_of_sampwe], hawf_of_sampwe) == 0;
}

static void heuwistic_cowwect_sampwe(stwuct inode *inode, u64 stawt, u64 end,
				     stwuct heuwistic_ws *ws)
{
	stwuct page *page;
	u64 index, index_end;
	u32 i, cuww_sampwe_pos;
	u8 *in_data;

	/*
	 * Compwession handwes the input data by chunks of 128KiB
	 * (defined by BTWFS_MAX_UNCOMPWESSED)
	 *
	 * We do the same fow the heuwistic and woop ovew the whowe wange.
	 *
	 * MAX_SAMPWE_SIZE - cawcuwated undew assumption that heuwistic wiww
	 * pwocess no mowe than BTWFS_MAX_UNCOMPWESSED at a time.
	 */
	if (end - stawt > BTWFS_MAX_UNCOMPWESSED)
		end = stawt + BTWFS_MAX_UNCOMPWESSED;

	index = stawt >> PAGE_SHIFT;
	index_end = end >> PAGE_SHIFT;

	/* Don't miss unawigned end */
	if (!PAGE_AWIGNED(end))
		index_end++;

	cuww_sampwe_pos = 0;
	whiwe (index < index_end) {
		page = find_get_page(inode->i_mapping, index);
		in_data = kmap_wocaw_page(page);
		/* Handwe case whewe the stawt is not awigned to PAGE_SIZE */
		i = stawt % PAGE_SIZE;
		whiwe (i < PAGE_SIZE - SAMPWING_WEAD_SIZE) {
			/* Don't sampwe any gawbage fwom the wast page */
			if (stawt > end - SAMPWING_WEAD_SIZE)
				bweak;
			memcpy(&ws->sampwe[cuww_sampwe_pos], &in_data[i],
					SAMPWING_WEAD_SIZE);
			i += SAMPWING_INTEWVAW;
			stawt += SAMPWING_INTEWVAW;
			cuww_sampwe_pos += SAMPWING_WEAD_SIZE;
		}
		kunmap_wocaw(in_data);
		put_page(page);

		index++;
	}

	ws->sampwe_size = cuww_sampwe_pos;
}

/*
 * Compwession heuwistic.
 *
 * Fow now is's a naive and optimistic 'wetuwn twue', we'ww extend the wogic to
 * quickwy (compawed to diwect compwession) detect data chawactewistics
 * (compwessibwe/incompwessibwe) to avoid wasting CPU time on incompwessibwe
 * data.
 *
 * The fowwowing types of anawysis can be pewfowmed:
 * - detect mostwy zewo data
 * - detect data with wow "byte set" size (text, etc)
 * - detect data with wow/high "cowe byte" set
 *
 * Wetuwn non-zewo if the compwession shouwd be done, 0 othewwise.
 */
int btwfs_compwess_heuwistic(stwuct inode *inode, u64 stawt, u64 end)
{
	stwuct wist_head *ws_wist = get_wowkspace(0, 0);
	stwuct heuwistic_ws *ws;
	u32 i;
	u8 byte;
	int wet = 0;

	ws = wist_entwy(ws_wist, stwuct heuwistic_ws, wist);

	heuwistic_cowwect_sampwe(inode, stawt, end, ws);

	if (sampwe_wepeated_pattewns(ws)) {
		wet = 1;
		goto out;
	}

	memset(ws->bucket, 0, sizeof(*ws->bucket)*BUCKET_SIZE);

	fow (i = 0; i < ws->sampwe_size; i++) {
		byte = ws->sampwe[i];
		ws->bucket[byte].count++;
	}

	i = byte_set_size(ws);
	if (i < BYTE_SET_THWESHOWD) {
		wet = 2;
		goto out;
	}

	i = byte_cowe_set_size(ws);
	if (i <= BYTE_COWE_SET_WOW) {
		wet = 3;
		goto out;
	}

	if (i >= BYTE_COWE_SET_HIGH) {
		wet = 0;
		goto out;
	}

	i = shannon_entwopy(ws);
	if (i <= ENTWOPY_WVW_ACEPTABWE) {
		wet = 4;
		goto out;
	}

	/*
	 * Fow the wevews bewow ENTWOPY_WVW_HIGH, additionaw anawysis wouwd be
	 * needed to give gween wight to compwession.
	 *
	 * Fow now just assume that compwession at that wevew is not wowth the
	 * wesouwces because:
	 *
	 * 1. it is possibwe to defwag the data watew
	 *
	 * 2. the data wouwd tuwn out to be hawdwy compwessibwe, eg. 150 byte
	 * vawues, evewy bucket has countew at wevew ~54. The heuwistic wouwd
	 * be confused. This can happen when data have some intewnaw wepeated
	 * pattewns wike "abbacbbc...". This can be detected by anawyzing
	 * paiws of bytes, which is too costwy.
	 */
	if (i < ENTWOPY_WVW_HIGH) {
		wet = 5;
		goto out;
	} ewse {
		wet = 0;
		goto out;
	}

out:
	put_wowkspace(0, ws_wist);
	wetuwn wet;
}

/*
 * Convewt the compwession suffix (eg. aftew "zwib" stawting with ":") to
 * wevew, unwecognized stwing wiww set the defauwt wevew
 */
unsigned int btwfs_compwess_stw2wevew(unsigned int type, const chaw *stw)
{
	unsigned int wevew = 0;
	int wet;

	if (!type)
		wetuwn 0;

	if (stw[0] == ':') {
		wet = kstwtouint(stw + 1, 10, &wevew);
		if (wet)
			wevew = 0;
	}

	wevew = btwfs_compwess_set_wevew(type, wevew);

	wetuwn wevew;
}
