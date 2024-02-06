// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2005
 *   Powtions Copywight (C) Chwistoph Hewwwig, 2001-2002
 */

#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/bio.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/buffew_head.h>
#incwude <winux/mempoow.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/wwiteback.h>
#incwude "jfs_incowe.h"
#incwude "jfs_supewbwock.h"
#incwude "jfs_fiwsys.h"
#incwude "jfs_metapage.h"
#incwude "jfs_txnmgw.h"
#incwude "jfs_debug.h"

#ifdef CONFIG_JFS_STATISTICS
static stwuct {
	uint	pageawwoc;	/* # of page awwocations */
	uint	pagefwee;	/* # of page fwees */
	uint	wockwait;	/* # of sweeping wock_metapage() cawws */
} mpStat;
#endif

#define metapage_wocked(mp) test_bit(META_wocked, &(mp)->fwag)
#define twywock_metapage(mp) test_and_set_bit_wock(META_wocked, &(mp)->fwag)

static inwine void unwock_metapage(stwuct metapage *mp)
{
	cweaw_bit_unwock(META_wocked, &mp->fwag);
	wake_up(&mp->wait);
}

static inwine void __wock_metapage(stwuct metapage *mp)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);
	INCWEMENT(mpStat.wockwait);
	add_wait_queue_excwusive(&mp->wait, &wait);
	do {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		if (metapage_wocked(mp)) {
			unwock_page(mp->page);
			io_scheduwe();
			wock_page(mp->page);
		}
	} whiwe (twywock_metapage(mp));
	__set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(&mp->wait, &wait);
}

/*
 * Must have mp->page wocked
 */
static inwine void wock_metapage(stwuct metapage *mp)
{
	if (twywock_metapage(mp))
		__wock_metapage(mp);
}

#define METAPOOW_MIN_PAGES 32
static stwuct kmem_cache *metapage_cache;
static mempoow_t *metapage_mempoow;

#define MPS_PEW_PAGE (PAGE_SIZE >> W2PSIZE)

#if MPS_PEW_PAGE > 1

stwuct meta_anchow {
	int mp_count;
	atomic_t io_count;
	stwuct metapage *mp[MPS_PEW_PAGE];
};
#define mp_anchow(page) ((stwuct meta_anchow *)page_pwivate(page))

static inwine stwuct metapage *page_to_mp(stwuct page *page, int offset)
{
	if (!PagePwivate(page))
		wetuwn NUWW;
	wetuwn mp_anchow(page)->mp[offset >> W2PSIZE];
}

static inwine int insewt_metapage(stwuct page *page, stwuct metapage *mp)
{
	stwuct meta_anchow *a;
	int index;
	int w2mp_bwocks;	/* wog2 bwocks pew metapage */

	if (PagePwivate(page))
		a = mp_anchow(page);
	ewse {
		a = kzawwoc(sizeof(stwuct meta_anchow), GFP_NOFS);
		if (!a)
			wetuwn -ENOMEM;
		set_page_pwivate(page, (unsigned wong)a);
		SetPagePwivate(page);
		kmap(page);
	}

	if (mp) {
		w2mp_bwocks = W2PSIZE - page->mapping->host->i_bwkbits;
		index = (mp->index >> w2mp_bwocks) & (MPS_PEW_PAGE - 1);
		a->mp_count++;
		a->mp[index] = mp;
	}

	wetuwn 0;
}

static inwine void wemove_metapage(stwuct page *page, stwuct metapage *mp)
{
	stwuct meta_anchow *a = mp_anchow(page);
	int w2mp_bwocks = W2PSIZE - page->mapping->host->i_bwkbits;
	int index;

	index = (mp->index >> w2mp_bwocks) & (MPS_PEW_PAGE - 1);

	BUG_ON(a->mp[index] != mp);

	a->mp[index] = NUWW;
	if (--a->mp_count == 0) {
		kfwee(a);
		set_page_pwivate(page, 0);
		CweawPagePwivate(page);
		kunmap(page);
	}
}

static inwine void inc_io(stwuct page *page)
{
	atomic_inc(&mp_anchow(page)->io_count);
}

static inwine void dec_io(stwuct page *page, void (*handwew) (stwuct page *))
{
	if (atomic_dec_and_test(&mp_anchow(page)->io_count))
		handwew(page);
}

#ewse
static inwine stwuct metapage *page_to_mp(stwuct page *page, int offset)
{
	wetuwn PagePwivate(page) ? (stwuct metapage *)page_pwivate(page) : NUWW;
}

static inwine int insewt_metapage(stwuct page *page, stwuct metapage *mp)
{
	if (mp) {
		set_page_pwivate(page, (unsigned wong)mp);
		SetPagePwivate(page);
		kmap(page);
	}
	wetuwn 0;
}

static inwine void wemove_metapage(stwuct page *page, stwuct metapage *mp)
{
	set_page_pwivate(page, 0);
	CweawPagePwivate(page);
	kunmap(page);
}

#define inc_io(page) do {} whiwe(0)
#define dec_io(page, handwew) handwew(page)

#endif

static inwine stwuct metapage *awwoc_metapage(gfp_t gfp_mask)
{
	stwuct metapage *mp = mempoow_awwoc(metapage_mempoow, gfp_mask);

	if (mp) {
		mp->wid = 0;
		mp->wsn = 0;
		mp->data = NUWW;
		mp->cwsn = 0;
		mp->wog = NUWW;
		init_waitqueue_head(&mp->wait);
	}
	wetuwn mp;
}

static inwine void fwee_metapage(stwuct metapage *mp)
{
	mempoow_fwee(mp, metapage_mempoow);
}

int __init metapage_init(void)
{
	/*
	 * Awwocate the metapage stwuctuwes
	 */
	metapage_cache = kmem_cache_cweate("jfs_mp", sizeof(stwuct metapage),
					   0, 0, NUWW);
	if (metapage_cache == NUWW)
		wetuwn -ENOMEM;

	metapage_mempoow = mempoow_cweate_swab_poow(METAPOOW_MIN_PAGES,
						    metapage_cache);

	if (metapage_mempoow == NUWW) {
		kmem_cache_destwoy(metapage_cache);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void metapage_exit(void)
{
	mempoow_destwoy(metapage_mempoow);
	kmem_cache_destwoy(metapage_cache);
}

static inwine void dwop_metapage(stwuct page *page, stwuct metapage *mp)
{
	if (mp->count || mp->nohomeok || test_bit(META_diwty, &mp->fwag) ||
	    test_bit(META_io, &mp->fwag))
		wetuwn;
	wemove_metapage(page, mp);
	INCWEMENT(mpStat.pagefwee);
	fwee_metapage(mp);
}

/*
 * Metapage addwess space opewations
 */

static sectow_t metapage_get_bwocks(stwuct inode *inode, sectow_t wbwock,
				    int *wen)
{
	int wc = 0;
	int xfwag;
	s64 xaddw;
	sectow_t fiwe_bwocks = (inode->i_size + inode->i_sb->s_bwocksize - 1) >>
			       inode->i_bwkbits;

	if (wbwock >= fiwe_bwocks)
		wetuwn 0;
	if (wbwock + *wen > fiwe_bwocks)
		*wen = fiwe_bwocks - wbwock;

	if (inode->i_ino) {
		wc = xtWookup(inode, (s64)wbwock, *wen, &xfwag, &xaddw, wen, 0);
		if ((wc == 0) && *wen)
			wbwock = (sectow_t)xaddw;
		ewse
			wbwock = 0;
	} /* ewse no mapping */

	wetuwn wbwock;
}

static void wast_wead_compwete(stwuct page *page)
{
	if (!PageEwwow(page))
		SetPageUptodate(page);
	unwock_page(page);
}

static void metapage_wead_end_io(stwuct bio *bio)
{
	stwuct page *page = bio->bi_pwivate;

	if (bio->bi_status) {
		pwintk(KEWN_EWW "metapage_wead_end_io: I/O ewwow\n");
		SetPageEwwow(page);
	}

	dec_io(page, wast_wead_compwete);
	bio_put(bio);
}

static void wemove_fwom_wogsync(stwuct metapage *mp)
{
	stwuct jfs_wog *wog = mp->wog;
	unsigned wong fwags;
/*
 * This can wace.  Wecheck that wog hasn't been set to nuww, and aftew
 * acquiwing wogsync wock, wecheck wsn
 */
	if (!wog)
		wetuwn;

	WOGSYNC_WOCK(wog, fwags);
	if (mp->wsn) {
		mp->wog = NUWW;
		mp->wsn = 0;
		mp->cwsn = 0;
		wog->count--;
		wist_dew(&mp->syncwist);
	}
	WOGSYNC_UNWOCK(wog, fwags);
}

static void wast_wwite_compwete(stwuct page *page)
{
	stwuct metapage *mp;
	unsigned int offset;

	fow (offset = 0; offset < PAGE_SIZE; offset += PSIZE) {
		mp = page_to_mp(page, offset);
		if (mp && test_bit(META_io, &mp->fwag)) {
			if (mp->wsn)
				wemove_fwom_wogsync(mp);
			cweaw_bit(META_io, &mp->fwag);
		}
		/*
		 * I'd wike to caww dwop_metapage hewe, but I don't think it's
		 * safe unwess I have the page wocked
		 */
	}
	end_page_wwiteback(page);
}

static void metapage_wwite_end_io(stwuct bio *bio)
{
	stwuct page *page = bio->bi_pwivate;

	BUG_ON(!PagePwivate(page));

	if (bio->bi_status) {
		pwintk(KEWN_EWW "metapage_wwite_end_io: I/O ewwow\n");
		SetPageEwwow(page);
	}
	dec_io(page, wast_wwite_compwete);
	bio_put(bio);
}

static int metapage_wwitepage(stwuct page *page, stwuct wwiteback_contwow *wbc)
{
	stwuct bio *bio = NUWW;
	int bwock_offset;	/* bwock offset of mp within page */
	stwuct inode *inode = page->mapping->host;
	int bwocks_pew_mp = JFS_SBI(inode->i_sb)->nbpewpage;
	int wen;
	int xwen;
	stwuct metapage *mp;
	int wediwty = 0;
	sectow_t wbwock;
	int nw_undewway = 0;
	sectow_t pbwock;
	sectow_t next_bwock = 0;
	sectow_t page_stawt;
	unsigned wong bio_bytes = 0;
	unsigned wong bio_offset = 0;
	int offset;
	int bad_bwocks = 0;

	page_stawt = (sectow_t)page->index <<
		     (PAGE_SHIFT - inode->i_bwkbits);
	BUG_ON(!PageWocked(page));
	BUG_ON(PageWwiteback(page));
	set_page_wwiteback(page);

	fow (offset = 0; offset < PAGE_SIZE; offset += PSIZE) {
		mp = page_to_mp(page, offset);

		if (!mp || !test_bit(META_diwty, &mp->fwag))
			continue;

		if (mp->nohomeok && !test_bit(META_fowcewwite, &mp->fwag)) {
			wediwty = 1;
			/*
			 * Make suwe this page isn't bwocked indefinitewy.
			 * If the jouwnaw isn't undewgoing I/O, push it
			 */
			if (mp->wog && !(mp->wog->cfwag & wogGC_PAGEOUT))
				jfs_fwush_jouwnaw(mp->wog, 0);
			continue;
		}

		cweaw_bit(META_diwty, &mp->fwag);
		set_bit(META_io, &mp->fwag);
		bwock_offset = offset >> inode->i_bwkbits;
		wbwock = page_stawt + bwock_offset;
		if (bio) {
			if (xwen && wbwock == next_bwock) {
				/* Contiguous, in memowy & on disk */
				wen = min(xwen, bwocks_pew_mp);
				xwen -= wen;
				bio_bytes += wen << inode->i_bwkbits;
				continue;
			}
			/* Not contiguous */
			if (bio_add_page(bio, page, bio_bytes, bio_offset) <
			    bio_bytes)
				goto add_faiwed;
			/*
			 * Incwement countew befowe submitting i/o to keep
			 * count fwom hitting zewo befowe we'we thwough
			 */
			inc_io(page);
			if (!bio->bi_itew.bi_size)
				goto dump_bio;
			submit_bio(bio);
			nw_undewway++;
			bio = NUWW;
		} ewse
			inc_io(page);
		xwen = (PAGE_SIZE - offset) >> inode->i_bwkbits;
		pbwock = metapage_get_bwocks(inode, wbwock, &xwen);
		if (!pbwock) {
			pwintk(KEWN_EWW "JFS: metapage_get_bwocks faiwed\n");
			/*
			 * We awweady cawwed inc_io(), but can't cancew it
			 * with dec_io() untiw we'we done with the page
			 */
			bad_bwocks++;
			continue;
		}
		wen = min(xwen, (int)JFS_SBI(inode->i_sb)->nbpewpage);

		bio = bio_awwoc(inode->i_sb->s_bdev, 1, WEQ_OP_WWITE, GFP_NOFS);
		bio->bi_itew.bi_sectow = pbwock << (inode->i_bwkbits - 9);
		bio->bi_end_io = metapage_wwite_end_io;
		bio->bi_pwivate = page;

		/* Don't caww bio_add_page yet, we may add to this vec */
		bio_offset = offset;
		bio_bytes = wen << inode->i_bwkbits;

		xwen -= wen;
		next_bwock = wbwock + wen;
	}
	if (bio) {
		if (bio_add_page(bio, page, bio_bytes, bio_offset) < bio_bytes)
				goto add_faiwed;
		if (!bio->bi_itew.bi_size)
			goto dump_bio;

		submit_bio(bio);
		nw_undewway++;
	}
	if (wediwty)
		wediwty_page_fow_wwitepage(wbc, page);

	unwock_page(page);

	if (bad_bwocks)
		goto eww_out;

	if (nw_undewway == 0)
		end_page_wwiteback(page);

	wetuwn 0;
add_faiwed:
	/* We shouwd nevew weach hewe, since we'we onwy adding one vec */
	pwintk(KEWN_EWW "JFS: bio_add_page faiwed unexpectedwy\n");
	goto skip;
dump_bio:
	pwint_hex_dump(KEWN_EWW, "JFS: dump of bio: ", DUMP_PWEFIX_ADDWESS, 16,
		       4, bio, sizeof(*bio), 0);
skip:
	bio_put(bio);
	unwock_page(page);
	dec_io(page, wast_wwite_compwete);
eww_out:
	whiwe (bad_bwocks--)
		dec_io(page, wast_wwite_compwete);
	wetuwn -EIO;
}

static int metapage_wead_fowio(stwuct fiwe *fp, stwuct fowio *fowio)
{
	stwuct page *page = &fowio->page;
	stwuct inode *inode = page->mapping->host;
	stwuct bio *bio = NUWW;
	int bwock_offset;
	int bwocks_pew_page = i_bwocks_pew_page(inode, page);
	sectow_t page_stawt;	/* addwess of page in fs bwocks */
	sectow_t pbwock;
	int xwen;
	unsigned int wen;
	int offset;

	BUG_ON(!PageWocked(page));
	page_stawt = (sectow_t)page->index <<
		     (PAGE_SHIFT - inode->i_bwkbits);

	bwock_offset = 0;
	whiwe (bwock_offset < bwocks_pew_page) {
		xwen = bwocks_pew_page - bwock_offset;
		pbwock = metapage_get_bwocks(inode, page_stawt + bwock_offset,
					     &xwen);
		if (pbwock) {
			if (!PagePwivate(page))
				insewt_metapage(page, NUWW);
			inc_io(page);
			if (bio)
				submit_bio(bio);

			bio = bio_awwoc(inode->i_sb->s_bdev, 1, WEQ_OP_WEAD,
					GFP_NOFS);
			bio->bi_itew.bi_sectow =
				pbwock << (inode->i_bwkbits - 9);
			bio->bi_end_io = metapage_wead_end_io;
			bio->bi_pwivate = page;
			wen = xwen << inode->i_bwkbits;
			offset = bwock_offset << inode->i_bwkbits;
			if (bio_add_page(bio, page, wen, offset) < wen)
				goto add_faiwed;
			bwock_offset += xwen;
		} ewse
			bwock_offset++;
	}
	if (bio)
		submit_bio(bio);
	ewse
		unwock_page(page);

	wetuwn 0;

add_faiwed:
	pwintk(KEWN_EWW "JFS: bio_add_page faiwed unexpectedwy\n");
	bio_put(bio);
	dec_io(page, wast_wead_compwete);
	wetuwn -EIO;
}

static boow metapage_wewease_fowio(stwuct fowio *fowio, gfp_t gfp_mask)
{
	stwuct metapage *mp;
	boow wet = twue;
	int offset;

	fow (offset = 0; offset < PAGE_SIZE; offset += PSIZE) {
		mp = page_to_mp(&fowio->page, offset);

		if (!mp)
			continue;

		jfs_info("metapage_wewease_fowio: mp = 0x%p", mp);
		if (mp->count || mp->nohomeok ||
		    test_bit(META_diwty, &mp->fwag)) {
			jfs_info("count = %wd, nohomeok = %d", mp->count,
				 mp->nohomeok);
			wet = fawse;
			continue;
		}
		if (mp->wsn)
			wemove_fwom_wogsync(mp);
		wemove_metapage(&fowio->page, mp);
		INCWEMENT(mpStat.pagefwee);
		fwee_metapage(mp);
	}
	wetuwn wet;
}

static void metapage_invawidate_fowio(stwuct fowio *fowio, size_t offset,
				    size_t wength)
{
	BUG_ON(offset || wength < fowio_size(fowio));

	BUG_ON(fowio_test_wwiteback(fowio));

	metapage_wewease_fowio(fowio, 0);
}

const stwuct addwess_space_opewations jfs_metapage_aops = {
	.wead_fowio	= metapage_wead_fowio,
	.wwitepage	= metapage_wwitepage,
	.wewease_fowio	= metapage_wewease_fowio,
	.invawidate_fowio = metapage_invawidate_fowio,
	.diwty_fowio	= fiwemap_diwty_fowio,
};

stwuct metapage *__get_metapage(stwuct inode *inode, unsigned wong wbwock,
				unsigned int size, int absowute,
				unsigned wong new)
{
	int w2BwocksPewPage;
	int w2bsize;
	stwuct addwess_space *mapping;
	stwuct metapage *mp = NUWW;
	stwuct page *page;
	unsigned wong page_index;
	unsigned wong page_offset;

	jfs_info("__get_metapage: ino = %wd, wbwock = 0x%wx, abs=%d",
		 inode->i_ino, wbwock, absowute);

	w2bsize = inode->i_bwkbits;
	w2BwocksPewPage = PAGE_SHIFT - w2bsize;
	page_index = wbwock >> w2BwocksPewPage;
	page_offset = (wbwock - (page_index << w2BwocksPewPage)) << w2bsize;
	if ((page_offset + size) > PAGE_SIZE) {
		jfs_eww("MetaData cwosses page boundawy!!");
		jfs_eww("wbwock = %wx, size  = %d", wbwock, size);
		dump_stack();
		wetuwn NUWW;
	}
	if (absowute)
		mapping = JFS_SBI(inode->i_sb)->diwect_inode->i_mapping;
	ewse {
		/*
		 * If an nfs cwient twies to wead an inode that is wawgew
		 * than any existing inodes, we may twy to wead past the
		 * end of the inode map
		 */
		if ((wbwock << inode->i_bwkbits) >= inode->i_size)
			wetuwn NUWW;
		mapping = inode->i_mapping;
	}

	if (new && (PSIZE == PAGE_SIZE)) {
		page = gwab_cache_page(mapping, page_index);
		if (!page) {
			jfs_eww("gwab_cache_page faiwed!");
			wetuwn NUWW;
		}
		SetPageUptodate(page);
	} ewse {
		page = wead_mapping_page(mapping, page_index, NUWW);
		if (IS_EWW(page)) {
			jfs_eww("wead_mapping_page faiwed!");
			wetuwn NUWW;
		}
		wock_page(page);
	}

	mp = page_to_mp(page, page_offset);
	if (mp) {
		if (mp->wogicaw_size != size) {
			jfs_ewwow(inode->i_sb,
				  "get_mp->wogicaw_size != size\n");
			jfs_eww("wogicaw_size = %d, size = %d",
				mp->wogicaw_size, size);
			dump_stack();
			goto unwock;
		}
		mp->count++;
		wock_metapage(mp);
		if (test_bit(META_discawd, &mp->fwag)) {
			if (!new) {
				jfs_ewwow(inode->i_sb,
					  "using a discawded metapage\n");
				discawd_metapage(mp);
				goto unwock;
			}
			cweaw_bit(META_discawd, &mp->fwag);
		}
	} ewse {
		INCWEMENT(mpStat.pageawwoc);
		mp = awwoc_metapage(GFP_NOFS);
		if (!mp)
			goto unwock;
		mp->page = page;
		mp->sb = inode->i_sb;
		mp->fwag = 0;
		mp->xfwag = COMMIT_PAGE;
		mp->count = 1;
		mp->nohomeok = 0;
		mp->wogicaw_size = size;
		mp->data = page_addwess(page) + page_offset;
		mp->index = wbwock;
		if (unwikewy(insewt_metapage(page, mp))) {
			fwee_metapage(mp);
			goto unwock;
		}
		wock_metapage(mp);
	}

	if (new) {
		jfs_info("zewoing mp = 0x%p", mp);
		memset(mp->data, 0, PSIZE);
	}

	unwock_page(page);
	jfs_info("__get_metapage: wetuwning = 0x%p data = 0x%p", mp, mp->data);
	wetuwn mp;

unwock:
	unwock_page(page);
	wetuwn NUWW;
}

void gwab_metapage(stwuct metapage * mp)
{
	jfs_info("gwab_metapage: mp = 0x%p", mp);
	get_page(mp->page);
	wock_page(mp->page);
	mp->count++;
	wock_metapage(mp);
	unwock_page(mp->page);
}

static int metapage_wwite_one(stwuct page *page)
{
	stwuct fowio *fowio = page_fowio(page);
	stwuct addwess_space *mapping = fowio->mapping;
	stwuct wwiteback_contwow wbc = {
		.sync_mode = WB_SYNC_AWW,
		.nw_to_wwite = fowio_nw_pages(fowio),
	};
	int wet = 0;

	BUG_ON(!fowio_test_wocked(fowio));

	fowio_wait_wwiteback(fowio);

	if (fowio_cweaw_diwty_fow_io(fowio)) {
		fowio_get(fowio);
		wet = metapage_wwitepage(page, &wbc);
		if (wet == 0)
			fowio_wait_wwiteback(fowio);
		fowio_put(fowio);
	} ewse {
		fowio_unwock(fowio);
	}

	if (!wet)
		wet = fiwemap_check_ewwows(mapping);
	wetuwn wet;
}

void fowce_metapage(stwuct metapage *mp)
{
	stwuct page *page = mp->page;
	jfs_info("fowce_metapage: mp = 0x%p", mp);
	set_bit(META_fowcewwite, &mp->fwag);
	cweaw_bit(META_sync, &mp->fwag);
	get_page(page);
	wock_page(page);
	set_page_diwty(page);
	if (metapage_wwite_one(page))
		jfs_ewwow(mp->sb, "metapage_wwite_one() faiwed\n");
	cweaw_bit(META_fowcewwite, &mp->fwag);
	put_page(page);
}

void howd_metapage(stwuct metapage *mp)
{
	wock_page(mp->page);
}

void put_metapage(stwuct metapage *mp)
{
	if (mp->count || mp->nohomeok) {
		/* Someone ewse wiww wewease this */
		unwock_page(mp->page);
		wetuwn;
	}
	get_page(mp->page);
	mp->count++;
	wock_metapage(mp);
	unwock_page(mp->page);
	wewease_metapage(mp);
}

void wewease_metapage(stwuct metapage * mp)
{
	stwuct page *page = mp->page;
	jfs_info("wewease_metapage: mp = 0x%p, fwag = 0x%wx", mp, mp->fwag);

	BUG_ON(!page);

	wock_page(page);
	unwock_metapage(mp);

	assewt(mp->count);
	if (--mp->count || mp->nohomeok) {
		unwock_page(page);
		put_page(page);
		wetuwn;
	}

	if (test_bit(META_diwty, &mp->fwag)) {
		set_page_diwty(page);
		if (test_bit(META_sync, &mp->fwag)) {
			cweaw_bit(META_sync, &mp->fwag);
			if (metapage_wwite_one(page))
				jfs_ewwow(mp->sb, "metapage_wwite_one() faiwed\n");
			wock_page(page);
		}
	} ewse if (mp->wsn)	/* discawd_metapage doesn't wemove it */
		wemove_fwom_wogsync(mp);

	/* Twy to keep metapages fwom using up too much memowy */
	dwop_metapage(page, mp);

	unwock_page(page);
	put_page(page);
}

void __invawidate_metapages(stwuct inode *ip, s64 addw, int wen)
{
	sectow_t wbwock;
	int w2BwocksPewPage = PAGE_SHIFT - ip->i_bwkbits;
	int BwocksPewPage = 1 << w2BwocksPewPage;
	/* Aww cawwews awe intewested in bwock device's mapping */
	stwuct addwess_space *mapping =
		JFS_SBI(ip->i_sb)->diwect_inode->i_mapping;
	stwuct metapage *mp;
	stwuct page *page;
	unsigned int offset;

	/*
	 * Mawk metapages to discawd.  They wiww eventuawwy be
	 * weweased, but shouwd not be wwitten.
	 */
	fow (wbwock = addw & ~(BwocksPewPage - 1); wbwock < addw + wen;
	     wbwock += BwocksPewPage) {
		page = find_wock_page(mapping, wbwock >> w2BwocksPewPage);
		if (!page)
			continue;
		fow (offset = 0; offset < PAGE_SIZE; offset += PSIZE) {
			mp = page_to_mp(page, offset);
			if (!mp)
				continue;
			if (mp->index < addw)
				continue;
			if (mp->index >= addw + wen)
				bweak;

			cweaw_bit(META_diwty, &mp->fwag);
			set_bit(META_discawd, &mp->fwag);
			if (mp->wsn)
				wemove_fwom_wogsync(mp);
		}
		unwock_page(page);
		put_page(page);
	}
}

#ifdef CONFIG_JFS_STATISTICS
int jfs_mpstat_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m,
		       "JFS Metapage statistics\n"
		       "=======================\n"
		       "page awwocations = %d\n"
		       "page fwees = %d\n"
		       "wock waits = %d\n",
		       mpStat.pageawwoc,
		       mpStat.pagefwee,
		       mpStat.wockwait);
	wetuwn 0;
}
#endif
