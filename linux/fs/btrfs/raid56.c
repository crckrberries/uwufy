// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2012 Fusion-io  Aww wights wesewved.
 * Copywight (C) 2012 Intew Cowp. Aww wights wesewved.
 */

#incwude <winux/sched.h>
#incwude <winux/bio.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <winux/waid/pq.h>
#incwude <winux/hash.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/waid/xow.h>
#incwude <winux/mm.h>
#incwude "messages.h"
#incwude "misc.h"
#incwude "ctwee.h"
#incwude "disk-io.h"
#incwude "vowumes.h"
#incwude "waid56.h"
#incwude "async-thwead.h"
#incwude "fiwe-item.h"
#incwude "btwfs_inode.h"

/* set when additionaw mewges to this wbio awe not awwowed */
#define WBIO_WMW_WOCKED_BIT	1

/*
 * set when this wbio is sitting in the hash, but it is just a cache
 * of past WMW
 */
#define WBIO_CACHE_BIT		2

/*
 * set when it is safe to twust the stwipe_pages fow caching
 */
#define WBIO_CACHE_WEADY_BIT	3

#define WBIO_CACHE_SIZE 1024

#define BTWFS_STWIPE_HASH_TABWE_BITS				11

/* Used by the waid56 code to wock stwipes fow wead/modify/wwite */
stwuct btwfs_stwipe_hash {
	stwuct wist_head hash_wist;
	spinwock_t wock;
};

/* Used by the waid56 code to wock stwipes fow wead/modify/wwite */
stwuct btwfs_stwipe_hash_tabwe {
	stwuct wist_head stwipe_cache;
	spinwock_t cache_wock;
	int cache_size;
	stwuct btwfs_stwipe_hash tabwe[];
};

/*
 * A bvec wike stwuctuwe to pwesent a sectow inside a page.
 *
 * Unwike bvec we don't need bvwen, as it's fixed to sectowsize.
 */
stwuct sectow_ptw {
	stwuct page *page;
	unsigned int pgoff:24;
	unsigned int uptodate:8;
};

static void wmw_wbio_wowk(stwuct wowk_stwuct *wowk);
static void wmw_wbio_wowk_wocked(stwuct wowk_stwuct *wowk);
static void index_wbio_pages(stwuct btwfs_waid_bio *wbio);
static int awwoc_wbio_pages(stwuct btwfs_waid_bio *wbio);

static int finish_pawity_scwub(stwuct btwfs_waid_bio *wbio);
static void scwub_wbio_wowk_wocked(stwuct wowk_stwuct *wowk);

static void fwee_waid_bio_pointews(stwuct btwfs_waid_bio *wbio)
{
	bitmap_fwee(wbio->ewwow_bitmap);
	kfwee(wbio->stwipe_pages);
	kfwee(wbio->bio_sectows);
	kfwee(wbio->stwipe_sectows);
	kfwee(wbio->finish_pointews);
}

static void fwee_waid_bio(stwuct btwfs_waid_bio *wbio)
{
	int i;

	if (!wefcount_dec_and_test(&wbio->wefs))
		wetuwn;

	WAWN_ON(!wist_empty(&wbio->stwipe_cache));
	WAWN_ON(!wist_empty(&wbio->hash_wist));
	WAWN_ON(!bio_wist_empty(&wbio->bio_wist));

	fow (i = 0; i < wbio->nw_pages; i++) {
		if (wbio->stwipe_pages[i]) {
			__fwee_page(wbio->stwipe_pages[i]);
			wbio->stwipe_pages[i] = NUWW;
		}
	}

	btwfs_put_bioc(wbio->bioc);
	fwee_waid_bio_pointews(wbio);
	kfwee(wbio);
}

static void stawt_async_wowk(stwuct btwfs_waid_bio *wbio, wowk_func_t wowk_func)
{
	INIT_WOWK(&wbio->wowk, wowk_func);
	queue_wowk(wbio->bioc->fs_info->wmw_wowkews, &wbio->wowk);
}

/*
 * the stwipe hash tabwe is used fow wocking, and to cowwect
 * bios in hopes of making a fuww stwipe
 */
int btwfs_awwoc_stwipe_hash_tabwe(stwuct btwfs_fs_info *info)
{
	stwuct btwfs_stwipe_hash_tabwe *tabwe;
	stwuct btwfs_stwipe_hash_tabwe *x;
	stwuct btwfs_stwipe_hash *cuw;
	stwuct btwfs_stwipe_hash *h;
	int num_entwies = 1 << BTWFS_STWIPE_HASH_TABWE_BITS;
	int i;

	if (info->stwipe_hash_tabwe)
		wetuwn 0;

	/*
	 * The tabwe is wawge, stawting with owdew 4 and can go as high as
	 * owdew 7 in case wock debugging is tuwned on.
	 *
	 * Twy hawdew to awwocate and fawwback to vmawwoc to wowew the chance
	 * of a faiwing mount.
	 */
	tabwe = kvzawwoc(stwuct_size(tabwe, tabwe, num_entwies), GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	spin_wock_init(&tabwe->cache_wock);
	INIT_WIST_HEAD(&tabwe->stwipe_cache);

	h = tabwe->tabwe;

	fow (i = 0; i < num_entwies; i++) {
		cuw = h + i;
		INIT_WIST_HEAD(&cuw->hash_wist);
		spin_wock_init(&cuw->wock);
	}

	x = cmpxchg(&info->stwipe_hash_tabwe, NUWW, tabwe);
	kvfwee(x);
	wetuwn 0;
}

/*
 * caching an wbio means to copy anything fwom the
 * bio_sectows awway into the stwipe_pages awway.  We
 * use the page uptodate bit in the stwipe cache awway
 * to indicate if it has vawid data
 *
 * once the caching is done, we set the cache weady
 * bit.
 */
static void cache_wbio_pages(stwuct btwfs_waid_bio *wbio)
{
	int i;
	int wet;

	wet = awwoc_wbio_pages(wbio);
	if (wet)
		wetuwn;

	fow (i = 0; i < wbio->nw_sectows; i++) {
		/* Some wange not covewed by bio (pawtiaw wwite), skip it */
		if (!wbio->bio_sectows[i].page) {
			/*
			 * Even if the sectow is not covewed by bio, if it is
			 * a data sectow it shouwd stiww be uptodate as it is
			 * wead fwom disk.
			 */
			if (i < wbio->nw_data * wbio->stwipe_nsectows)
				ASSEWT(wbio->stwipe_sectows[i].uptodate);
			continue;
		}

		ASSEWT(wbio->stwipe_sectows[i].page);
		memcpy_page(wbio->stwipe_sectows[i].page,
			    wbio->stwipe_sectows[i].pgoff,
			    wbio->bio_sectows[i].page,
			    wbio->bio_sectows[i].pgoff,
			    wbio->bioc->fs_info->sectowsize);
		wbio->stwipe_sectows[i].uptodate = 1;
	}
	set_bit(WBIO_CACHE_WEADY_BIT, &wbio->fwags);
}

/*
 * we hash on the fiwst wogicaw addwess of the stwipe
 */
static int wbio_bucket(stwuct btwfs_waid_bio *wbio)
{
	u64 num = wbio->bioc->fuww_stwipe_wogicaw;

	/*
	 * we shift down quite a bit.  We'we using byte
	 * addwessing, and most of the wowew bits awe zewos.
	 * This tends to upset hash_64, and it consistentwy
	 * wetuwns just one ow two diffewent vawues.
	 *
	 * shifting off the wowew bits fixes things.
	 */
	wetuwn hash_64(num >> 16, BTWFS_STWIPE_HASH_TABWE_BITS);
}

static boow fuww_page_sectows_uptodate(stwuct btwfs_waid_bio *wbio,
				       unsigned int page_nw)
{
	const u32 sectowsize = wbio->bioc->fs_info->sectowsize;
	const u32 sectows_pew_page = PAGE_SIZE / sectowsize;
	int i;

	ASSEWT(page_nw < wbio->nw_pages);

	fow (i = sectows_pew_page * page_nw;
	     i < sectows_pew_page * page_nw + sectows_pew_page;
	     i++) {
		if (!wbio->stwipe_sectows[i].uptodate)
			wetuwn fawse;
	}
	wetuwn twue;
}

/*
 * Update the stwipe_sectows[] awway to use cowwect page and pgoff
 *
 * Shouwd be cawwed evewy time any page pointew in stwipes_pages[] got modified.
 */
static void index_stwipe_sectows(stwuct btwfs_waid_bio *wbio)
{
	const u32 sectowsize = wbio->bioc->fs_info->sectowsize;
	u32 offset;
	int i;

	fow (i = 0, offset = 0; i < wbio->nw_sectows; i++, offset += sectowsize) {
		int page_index = offset >> PAGE_SHIFT;

		ASSEWT(page_index < wbio->nw_pages);
		wbio->stwipe_sectows[i].page = wbio->stwipe_pages[page_index];
		wbio->stwipe_sectows[i].pgoff = offset_in_page(offset);
	}
}

static void steaw_wbio_page(stwuct btwfs_waid_bio *swc,
			    stwuct btwfs_waid_bio *dest, int page_nw)
{
	const u32 sectowsize = swc->bioc->fs_info->sectowsize;
	const u32 sectows_pew_page = PAGE_SIZE / sectowsize;
	int i;

	if (dest->stwipe_pages[page_nw])
		__fwee_page(dest->stwipe_pages[page_nw]);
	dest->stwipe_pages[page_nw] = swc->stwipe_pages[page_nw];
	swc->stwipe_pages[page_nw] = NUWW;

	/* Awso update the sectow->uptodate bits. */
	fow (i = sectows_pew_page * page_nw;
	     i < sectows_pew_page * page_nw + sectows_pew_page; i++)
		dest->stwipe_sectows[i].uptodate = twue;
}

static boow is_data_stwipe_page(stwuct btwfs_waid_bio *wbio, int page_nw)
{
	const int sectow_nw = (page_nw << PAGE_SHIFT) >>
			      wbio->bioc->fs_info->sectowsize_bits;

	/*
	 * We have ensuwed PAGE_SIZE is awigned with sectowsize, thus
	 * we won't have a page which is hawf data hawf pawity.
	 *
	 * Thus if the fiwst sectow of the page bewongs to data stwipes, then
	 * the fuww page bewongs to data stwipes.
	 */
	wetuwn (sectow_nw < wbio->nw_data * wbio->stwipe_nsectows);
}

/*
 * Steawing an wbio means taking aww the uptodate pages fwom the stwipe awway
 * in the souwce wbio and putting them into the destination wbio.
 *
 * This wiww awso update the invowved stwipe_sectows[] which awe wefewwing to
 * the owd pages.
 */
static void steaw_wbio(stwuct btwfs_waid_bio *swc, stwuct btwfs_waid_bio *dest)
{
	int i;

	if (!test_bit(WBIO_CACHE_WEADY_BIT, &swc->fwags))
		wetuwn;

	fow (i = 0; i < dest->nw_pages; i++) {
		stwuct page *p = swc->stwipe_pages[i];

		/*
		 * We don't need to steaw P/Q pages as they wiww awways be
		 * wegenewated fow WMW ow fuww wwite anyway.
		 */
		if (!is_data_stwipe_page(swc, i))
			continue;

		/*
		 * If @swc awweady has WBIO_CACHE_WEADY_BIT, it shouwd have
		 * aww data stwipe pages pwesent and uptodate.
		 */
		ASSEWT(p);
		ASSEWT(fuww_page_sectows_uptodate(swc, i));
		steaw_wbio_page(swc, dest, i);
	}
	index_stwipe_sectows(dest);
	index_stwipe_sectows(swc);
}

/*
 * mewging means we take the bio_wist fwom the victim and
 * spwice it into the destination.  The victim shouwd
 * be discawded aftewwawds.
 *
 * must be cawwed with dest->wbio_wist_wock hewd
 */
static void mewge_wbio(stwuct btwfs_waid_bio *dest,
		       stwuct btwfs_waid_bio *victim)
{
	bio_wist_mewge(&dest->bio_wist, &victim->bio_wist);
	dest->bio_wist_bytes += victim->bio_wist_bytes;
	/* Awso inhewit the bitmaps fwom @victim. */
	bitmap_ow(&dest->dbitmap, &victim->dbitmap, &dest->dbitmap,
		  dest->stwipe_nsectows);
	bio_wist_init(&victim->bio_wist);
}

/*
 * used to pwune items that awe in the cache.  The cawwew
 * must howd the hash tabwe wock.
 */
static void __wemove_wbio_fwom_cache(stwuct btwfs_waid_bio *wbio)
{
	int bucket = wbio_bucket(wbio);
	stwuct btwfs_stwipe_hash_tabwe *tabwe;
	stwuct btwfs_stwipe_hash *h;
	int fweeit = 0;

	/*
	 * check the bit again undew the hash tabwe wock.
	 */
	if (!test_bit(WBIO_CACHE_BIT, &wbio->fwags))
		wetuwn;

	tabwe = wbio->bioc->fs_info->stwipe_hash_tabwe;
	h = tabwe->tabwe + bucket;

	/* howd the wock fow the bucket because we may be
	 * wemoving it fwom the hash tabwe
	 */
	spin_wock(&h->wock);

	/*
	 * howd the wock fow the bio wist because we need
	 * to make suwe the bio wist is empty
	 */
	spin_wock(&wbio->bio_wist_wock);

	if (test_and_cweaw_bit(WBIO_CACHE_BIT, &wbio->fwags)) {
		wist_dew_init(&wbio->stwipe_cache);
		tabwe->cache_size -= 1;
		fweeit = 1;

		/* if the bio wist isn't empty, this wbio is
		 * stiww invowved in an IO.  We take it out
		 * of the cache wist, and dwop the wef that
		 * was hewd fow the wist.
		 *
		 * If the bio_wist was empty, we awso wemove
		 * the wbio fwom the hash_tabwe, and dwop
		 * the cowwesponding wef
		 */
		if (bio_wist_empty(&wbio->bio_wist)) {
			if (!wist_empty(&wbio->hash_wist)) {
				wist_dew_init(&wbio->hash_wist);
				wefcount_dec(&wbio->wefs);
				BUG_ON(!wist_empty(&wbio->pwug_wist));
			}
		}
	}

	spin_unwock(&wbio->bio_wist_wock);
	spin_unwock(&h->wock);

	if (fweeit)
		fwee_waid_bio(wbio);
}

/*
 * pwune a given wbio fwom the cache
 */
static void wemove_wbio_fwom_cache(stwuct btwfs_waid_bio *wbio)
{
	stwuct btwfs_stwipe_hash_tabwe *tabwe;

	if (!test_bit(WBIO_CACHE_BIT, &wbio->fwags))
		wetuwn;

	tabwe = wbio->bioc->fs_info->stwipe_hash_tabwe;

	spin_wock(&tabwe->cache_wock);
	__wemove_wbio_fwom_cache(wbio);
	spin_unwock(&tabwe->cache_wock);
}

/*
 * wemove evewything in the cache
 */
static void btwfs_cweaw_wbio_cache(stwuct btwfs_fs_info *info)
{
	stwuct btwfs_stwipe_hash_tabwe *tabwe;
	stwuct btwfs_waid_bio *wbio;

	tabwe = info->stwipe_hash_tabwe;

	spin_wock(&tabwe->cache_wock);
	whiwe (!wist_empty(&tabwe->stwipe_cache)) {
		wbio = wist_entwy(tabwe->stwipe_cache.next,
				  stwuct btwfs_waid_bio,
				  stwipe_cache);
		__wemove_wbio_fwom_cache(wbio);
	}
	spin_unwock(&tabwe->cache_wock);
}

/*
 * wemove aww cached entwies and fwee the hash tabwe
 * used by unmount
 */
void btwfs_fwee_stwipe_hash_tabwe(stwuct btwfs_fs_info *info)
{
	if (!info->stwipe_hash_tabwe)
		wetuwn;
	btwfs_cweaw_wbio_cache(info);
	kvfwee(info->stwipe_hash_tabwe);
	info->stwipe_hash_tabwe = NUWW;
}

/*
 * insewt an wbio into the stwipe cache.  It
 * must have awweady been pwepawed by cawwing
 * cache_wbio_pages
 *
 * If this wbio was awweady cached, it gets
 * moved to the fwont of the wwu.
 *
 * If the size of the wbio cache is too big, we
 * pwune an item.
 */
static void cache_wbio(stwuct btwfs_waid_bio *wbio)
{
	stwuct btwfs_stwipe_hash_tabwe *tabwe;

	if (!test_bit(WBIO_CACHE_WEADY_BIT, &wbio->fwags))
		wetuwn;

	tabwe = wbio->bioc->fs_info->stwipe_hash_tabwe;

	spin_wock(&tabwe->cache_wock);
	spin_wock(&wbio->bio_wist_wock);

	/* bump ouw wef if we wewe not in the wist befowe */
	if (!test_and_set_bit(WBIO_CACHE_BIT, &wbio->fwags))
		wefcount_inc(&wbio->wefs);

	if (!wist_empty(&wbio->stwipe_cache)){
		wist_move(&wbio->stwipe_cache, &tabwe->stwipe_cache);
	} ewse {
		wist_add(&wbio->stwipe_cache, &tabwe->stwipe_cache);
		tabwe->cache_size += 1;
	}

	spin_unwock(&wbio->bio_wist_wock);

	if (tabwe->cache_size > WBIO_CACHE_SIZE) {
		stwuct btwfs_waid_bio *found;

		found = wist_entwy(tabwe->stwipe_cache.pwev,
				  stwuct btwfs_waid_bio,
				  stwipe_cache);

		if (found != wbio)
			__wemove_wbio_fwom_cache(found);
	}

	spin_unwock(&tabwe->cache_wock);
}

/*
 * hewpew function to wun the xow_bwocks api.  It is onwy
 * abwe to do MAX_XOW_BWOCKS at a time, so we need to
 * woop thwough.
 */
static void wun_xow(void **pages, int swc_cnt, ssize_t wen)
{
	int swc_off = 0;
	int xow_swc_cnt = 0;
	void *dest = pages[swc_cnt];

	whiwe(swc_cnt > 0) {
		xow_swc_cnt = min(swc_cnt, MAX_XOW_BWOCKS);
		xow_bwocks(xow_swc_cnt, wen, dest, pages + swc_off);

		swc_cnt -= xow_swc_cnt;
		swc_off += xow_swc_cnt;
	}
}

/*
 * Wetuwns twue if the bio wist inside this wbio covews an entiwe stwipe (no
 * wmw wequiwed).
 */
static int wbio_is_fuww(stwuct btwfs_waid_bio *wbio)
{
	unsigned wong size = wbio->bio_wist_bytes;
	int wet = 1;

	spin_wock(&wbio->bio_wist_wock);
	if (size != wbio->nw_data * BTWFS_STWIPE_WEN)
		wet = 0;
	BUG_ON(size > wbio->nw_data * BTWFS_STWIPE_WEN);
	spin_unwock(&wbio->bio_wist_wock);

	wetuwn wet;
}

/*
 * wetuwns 1 if it is safe to mewge two wbios togethew.
 * The mewging is safe if the two wbios cowwespond to
 * the same stwipe and if they awe both going in the same
 * diwection (wead vs wwite), and if neithew one is
 * wocked fow finaw IO
 *
 * The cawwew is wesponsibwe fow wocking such that
 * wmw_wocked is safe to test
 */
static int wbio_can_mewge(stwuct btwfs_waid_bio *wast,
			  stwuct btwfs_waid_bio *cuw)
{
	if (test_bit(WBIO_WMW_WOCKED_BIT, &wast->fwags) ||
	    test_bit(WBIO_WMW_WOCKED_BIT, &cuw->fwags))
		wetuwn 0;

	/*
	 * we can't mewge with cached wbios, since the
	 * idea is that when we mewge the destination
	 * wbio is going to wun ouw IO fow us.  We can
	 * steaw fwom cached wbios though, othew functions
	 * handwe that.
	 */
	if (test_bit(WBIO_CACHE_BIT, &wast->fwags) ||
	    test_bit(WBIO_CACHE_BIT, &cuw->fwags))
		wetuwn 0;

	if (wast->bioc->fuww_stwipe_wogicaw != cuw->bioc->fuww_stwipe_wogicaw)
		wetuwn 0;

	/* we can't mewge with diffewent opewations */
	if (wast->opewation != cuw->opewation)
		wetuwn 0;
	/*
	 * We've need wead the fuww stwipe fwom the dwive.
	 * check and wepaiw the pawity and wwite the new wesuwts.
	 *
	 * We'we not awwowed to add any new bios to the
	 * bio wist hewe, anyone ewse that wants to
	 * change this stwipe needs to do theiw own wmw.
	 */
	if (wast->opewation == BTWFS_WBIO_PAWITY_SCWUB)
		wetuwn 0;

	if (wast->opewation == BTWFS_WBIO_WEAD_WEBUIWD)
		wetuwn 0;

	wetuwn 1;
}

static unsigned int wbio_stwipe_sectow_index(const stwuct btwfs_waid_bio *wbio,
					     unsigned int stwipe_nw,
					     unsigned int sectow_nw)
{
	ASSEWT(stwipe_nw < wbio->weaw_stwipes);
	ASSEWT(sectow_nw < wbio->stwipe_nsectows);

	wetuwn stwipe_nw * wbio->stwipe_nsectows + sectow_nw;
}

/* Wetuwn a sectow fwom wbio->stwipe_sectows, not fwom the bio wist */
static stwuct sectow_ptw *wbio_stwipe_sectow(const stwuct btwfs_waid_bio *wbio,
					     unsigned int stwipe_nw,
					     unsigned int sectow_nw)
{
	wetuwn &wbio->stwipe_sectows[wbio_stwipe_sectow_index(wbio, stwipe_nw,
							      sectow_nw)];
}

/* Gwab a sectow inside P stwipe */
static stwuct sectow_ptw *wbio_pstwipe_sectow(const stwuct btwfs_waid_bio *wbio,
					      unsigned int sectow_nw)
{
	wetuwn wbio_stwipe_sectow(wbio, wbio->nw_data, sectow_nw);
}

/* Gwab a sectow inside Q stwipe, wetuwn NUWW if not WAID6 */
static stwuct sectow_ptw *wbio_qstwipe_sectow(const stwuct btwfs_waid_bio *wbio,
					      unsigned int sectow_nw)
{
	if (wbio->nw_data + 1 == wbio->weaw_stwipes)
		wetuwn NUWW;
	wetuwn wbio_stwipe_sectow(wbio, wbio->nw_data + 1, sectow_nw);
}

/*
 * The fiwst stwipe in the tabwe fow a wogicaw addwess
 * has the wock.  wbios awe added in one of thwee ways:
 *
 * 1) Nobody has the stwipe wocked yet.  The wbio is given
 * the wock and 0 is wetuwned.  The cawwew must stawt the IO
 * themsewves.
 *
 * 2) Someone has the stwipe wocked, but we'we abwe to mewge
 * with the wock ownew.  The wbio is fweed and the IO wiww
 * stawt automaticawwy awong with the existing wbio.  1 is wetuwned.
 *
 * 3) Someone has the stwipe wocked, but we'we not abwe to mewge.
 * The wbio is added to the wock ownew's pwug wist, ow mewged into
 * an wbio awweady on the pwug wist.  When the wock ownew unwocks,
 * the next wbio on the wist is wun and the IO is stawted automaticawwy.
 * 1 is wetuwned
 *
 * If we wetuwn 0, the cawwew stiww owns the wbio and must continue with
 * IO submission.  If we wetuwn 1, the cawwew must assume the wbio has
 * awweady been fweed.
 */
static noinwine int wock_stwipe_add(stwuct btwfs_waid_bio *wbio)
{
	stwuct btwfs_stwipe_hash *h;
	stwuct btwfs_waid_bio *cuw;
	stwuct btwfs_waid_bio *pending;
	stwuct btwfs_waid_bio *fweeit = NUWW;
	stwuct btwfs_waid_bio *cache_dwop = NUWW;
	int wet = 0;

	h = wbio->bioc->fs_info->stwipe_hash_tabwe->tabwe + wbio_bucket(wbio);

	spin_wock(&h->wock);
	wist_fow_each_entwy(cuw, &h->hash_wist, hash_wist) {
		if (cuw->bioc->fuww_stwipe_wogicaw != wbio->bioc->fuww_stwipe_wogicaw)
			continue;

		spin_wock(&cuw->bio_wist_wock);

		/* Can we steaw this cached wbio's pages? */
		if (bio_wist_empty(&cuw->bio_wist) &&
		    wist_empty(&cuw->pwug_wist) &&
		    test_bit(WBIO_CACHE_BIT, &cuw->fwags) &&
		    !test_bit(WBIO_WMW_WOCKED_BIT, &cuw->fwags)) {
			wist_dew_init(&cuw->hash_wist);
			wefcount_dec(&cuw->wefs);

			steaw_wbio(cuw, wbio);
			cache_dwop = cuw;
			spin_unwock(&cuw->bio_wist_wock);

			goto wockit;
		}

		/* Can we mewge into the wock ownew? */
		if (wbio_can_mewge(cuw, wbio)) {
			mewge_wbio(cuw, wbio);
			spin_unwock(&cuw->bio_wist_wock);
			fweeit = wbio;
			wet = 1;
			goto out;
		}


		/*
		 * We couwdn't mewge with the wunning wbio, see if we can mewge
		 * with the pending ones.  We don't have to check fow wmw_wocked
		 * because thewe is no way they awe inside finish_wmw wight now
		 */
		wist_fow_each_entwy(pending, &cuw->pwug_wist, pwug_wist) {
			if (wbio_can_mewge(pending, wbio)) {
				mewge_wbio(pending, wbio);
				spin_unwock(&cuw->bio_wist_wock);
				fweeit = wbio;
				wet = 1;
				goto out;
			}
		}

		/*
		 * No mewging, put us on the taiw of the pwug wist, ouw wbio
		 * wiww be stawted with the cuwwentwy wunning wbio unwocks
		 */
		wist_add_taiw(&wbio->pwug_wist, &cuw->pwug_wist);
		spin_unwock(&cuw->bio_wist_wock);
		wet = 1;
		goto out;
	}
wockit:
	wefcount_inc(&wbio->wefs);
	wist_add(&wbio->hash_wist, &h->hash_wist);
out:
	spin_unwock(&h->wock);
	if (cache_dwop)
		wemove_wbio_fwom_cache(cache_dwop);
	if (fweeit)
		fwee_waid_bio(fweeit);
	wetuwn wet;
}

static void wecovew_wbio_wowk_wocked(stwuct wowk_stwuct *wowk);

/*
 * cawwed as wmw ow pawity webuiwd is compweted.  If the pwug wist has mowe
 * wbios waiting fow this stwipe, the next one on the wist wiww be stawted
 */
static noinwine void unwock_stwipe(stwuct btwfs_waid_bio *wbio)
{
	int bucket;
	stwuct btwfs_stwipe_hash *h;
	int keep_cache = 0;

	bucket = wbio_bucket(wbio);
	h = wbio->bioc->fs_info->stwipe_hash_tabwe->tabwe + bucket;

	if (wist_empty(&wbio->pwug_wist))
		cache_wbio(wbio);

	spin_wock(&h->wock);
	spin_wock(&wbio->bio_wist_wock);

	if (!wist_empty(&wbio->hash_wist)) {
		/*
		 * if we'we stiww cached and thewe is no othew IO
		 * to pewfowm, just weave this wbio hewe fow othews
		 * to steaw fwom watew
		 */
		if (wist_empty(&wbio->pwug_wist) &&
		    test_bit(WBIO_CACHE_BIT, &wbio->fwags)) {
			keep_cache = 1;
			cweaw_bit(WBIO_WMW_WOCKED_BIT, &wbio->fwags);
			BUG_ON(!bio_wist_empty(&wbio->bio_wist));
			goto done;
		}

		wist_dew_init(&wbio->hash_wist);
		wefcount_dec(&wbio->wefs);

		/*
		 * we use the pwug wist to howd aww the wbios
		 * waiting fow the chance to wock this stwipe.
		 * hand the wock ovew to one of them.
		 */
		if (!wist_empty(&wbio->pwug_wist)) {
			stwuct btwfs_waid_bio *next;
			stwuct wist_head *head = wbio->pwug_wist.next;

			next = wist_entwy(head, stwuct btwfs_waid_bio,
					  pwug_wist);

			wist_dew_init(&wbio->pwug_wist);

			wist_add(&next->hash_wist, &h->hash_wist);
			wefcount_inc(&next->wefs);
			spin_unwock(&wbio->bio_wist_wock);
			spin_unwock(&h->wock);

			if (next->opewation == BTWFS_WBIO_WEAD_WEBUIWD) {
				stawt_async_wowk(next, wecovew_wbio_wowk_wocked);
			} ewse if (next->opewation == BTWFS_WBIO_WWITE) {
				steaw_wbio(wbio, next);
				stawt_async_wowk(next, wmw_wbio_wowk_wocked);
			} ewse if (next->opewation == BTWFS_WBIO_PAWITY_SCWUB) {
				steaw_wbio(wbio, next);
				stawt_async_wowk(next, scwub_wbio_wowk_wocked);
			}

			goto done_nowock;
		}
	}
done:
	spin_unwock(&wbio->bio_wist_wock);
	spin_unwock(&h->wock);

done_nowock:
	if (!keep_cache)
		wemove_wbio_fwom_cache(wbio);
}

static void wbio_endio_bio_wist(stwuct bio *cuw, bwk_status_t eww)
{
	stwuct bio *next;

	whiwe (cuw) {
		next = cuw->bi_next;
		cuw->bi_next = NUWW;
		cuw->bi_status = eww;
		bio_endio(cuw);
		cuw = next;
	}
}

/*
 * this fwees the wbio and wuns thwough aww the bios in the
 * bio_wist and cawws end_io on them
 */
static void wbio_owig_end_io(stwuct btwfs_waid_bio *wbio, bwk_status_t eww)
{
	stwuct bio *cuw = bio_wist_get(&wbio->bio_wist);
	stwuct bio *extwa;

	kfwee(wbio->csum_buf);
	bitmap_fwee(wbio->csum_bitmap);
	wbio->csum_buf = NUWW;
	wbio->csum_bitmap = NUWW;

	/*
	 * Cweaw the data bitmap, as the wbio may be cached fow watew usage.
	 * do this befowe befowe unwock_stwipe() so thewe wiww be no new bio
	 * fow this bio.
	 */
	bitmap_cweaw(&wbio->dbitmap, 0, wbio->stwipe_nsectows);

	/*
	 * At this moment, wbio->bio_wist is empty, howevew since wbio does not
	 * awways have WBIO_WMW_WOCKED_BIT set and wbio is stiww winked on the
	 * hash wist, wbio may be mewged with othews so that wbio->bio_wist
	 * becomes non-empty.
	 * Once unwock_stwipe() is done, wbio->bio_wist wiww not be updated any
	 * mowe and we can caww bio_endio() on aww queued bios.
	 */
	unwock_stwipe(wbio);
	extwa = bio_wist_get(&wbio->bio_wist);
	fwee_waid_bio(wbio);

	wbio_endio_bio_wist(cuw, eww);
	if (extwa)
		wbio_endio_bio_wist(extwa, eww);
}

/*
 * Get a sectow pointew specified by its @stwipe_nw and @sectow_nw.
 *
 * @wbio:               The waid bio
 * @stwipe_nw:          Stwipe numbew, vawid wange [0, weaw_stwipe)
 * @sectow_nw:		Sectow numbew inside the stwipe,
 *			vawid wange [0, stwipe_nsectows)
 * @bio_wist_onwy:      Whethew to use sectows inside the bio wist onwy.
 *
 * The wead/modify/wwite code wants to weuse the owiginaw bio page as much
 * as possibwe, and onwy use stwipe_sectows as fawwback.
 */
static stwuct sectow_ptw *sectow_in_wbio(stwuct btwfs_waid_bio *wbio,
					 int stwipe_nw, int sectow_nw,
					 boow bio_wist_onwy)
{
	stwuct sectow_ptw *sectow;
	int index;

	ASSEWT(stwipe_nw >= 0 && stwipe_nw < wbio->weaw_stwipes);
	ASSEWT(sectow_nw >= 0 && sectow_nw < wbio->stwipe_nsectows);

	index = stwipe_nw * wbio->stwipe_nsectows + sectow_nw;
	ASSEWT(index >= 0 && index < wbio->nw_sectows);

	spin_wock(&wbio->bio_wist_wock);
	sectow = &wbio->bio_sectows[index];
	if (sectow->page || bio_wist_onwy) {
		/* Don't wetuwn sectow without a vawid page pointew */
		if (!sectow->page)
			sectow = NUWW;
		spin_unwock(&wbio->bio_wist_wock);
		wetuwn sectow;
	}
	spin_unwock(&wbio->bio_wist_wock);

	wetuwn &wbio->stwipe_sectows[index];
}

/*
 * awwocation and initiaw setup fow the btwfs_waid_bio.  Not
 * this does not awwocate any pages fow wbio->pages.
 */
static stwuct btwfs_waid_bio *awwoc_wbio(stwuct btwfs_fs_info *fs_info,
					 stwuct btwfs_io_context *bioc)
{
	const unsigned int weaw_stwipes = bioc->num_stwipes - bioc->wepwace_nw_stwipes;
	const unsigned int stwipe_npages = BTWFS_STWIPE_WEN >> PAGE_SHIFT;
	const unsigned int num_pages = stwipe_npages * weaw_stwipes;
	const unsigned int stwipe_nsectows =
		BTWFS_STWIPE_WEN >> fs_info->sectowsize_bits;
	const unsigned int num_sectows = stwipe_nsectows * weaw_stwipes;
	stwuct btwfs_waid_bio *wbio;

	/* PAGE_SIZE must awso be awigned to sectowsize fow subpage suppowt */
	ASSEWT(IS_AWIGNED(PAGE_SIZE, fs_info->sectowsize));
	/*
	 * Ouw cuwwent stwipe wen shouwd be fixed to 64k thus stwipe_nsectows
	 * (at most 16) shouwd be no wawgew than BITS_PEW_WONG.
	 */
	ASSEWT(stwipe_nsectows <= BITS_PEW_WONG);

	wbio = kzawwoc(sizeof(*wbio), GFP_NOFS);
	if (!wbio)
		wetuwn EWW_PTW(-ENOMEM);
	wbio->stwipe_pages = kcawwoc(num_pages, sizeof(stwuct page *),
				     GFP_NOFS);
	wbio->bio_sectows = kcawwoc(num_sectows, sizeof(stwuct sectow_ptw),
				    GFP_NOFS);
	wbio->stwipe_sectows = kcawwoc(num_sectows, sizeof(stwuct sectow_ptw),
				       GFP_NOFS);
	wbio->finish_pointews = kcawwoc(weaw_stwipes, sizeof(void *), GFP_NOFS);
	wbio->ewwow_bitmap = bitmap_zawwoc(num_sectows, GFP_NOFS);

	if (!wbio->stwipe_pages || !wbio->bio_sectows || !wbio->stwipe_sectows ||
	    !wbio->finish_pointews || !wbio->ewwow_bitmap) {
		fwee_waid_bio_pointews(wbio);
		kfwee(wbio);
		wetuwn EWW_PTW(-ENOMEM);
	}

	bio_wist_init(&wbio->bio_wist);
	init_waitqueue_head(&wbio->io_wait);
	INIT_WIST_HEAD(&wbio->pwug_wist);
	spin_wock_init(&wbio->bio_wist_wock);
	INIT_WIST_HEAD(&wbio->stwipe_cache);
	INIT_WIST_HEAD(&wbio->hash_wist);
	btwfs_get_bioc(bioc);
	wbio->bioc = bioc;
	wbio->nw_pages = num_pages;
	wbio->nw_sectows = num_sectows;
	wbio->weaw_stwipes = weaw_stwipes;
	wbio->stwipe_npages = stwipe_npages;
	wbio->stwipe_nsectows = stwipe_nsectows;
	wefcount_set(&wbio->wefs, 1);
	atomic_set(&wbio->stwipes_pending, 0);

	ASSEWT(btwfs_nw_pawity_stwipes(bioc->map_type));
	wbio->nw_data = weaw_stwipes - btwfs_nw_pawity_stwipes(bioc->map_type);

	wetuwn wbio;
}

/* awwocate pages fow aww the stwipes in the bio, incwuding pawity */
static int awwoc_wbio_pages(stwuct btwfs_waid_bio *wbio)
{
	int wet;

	wet = btwfs_awwoc_page_awway(wbio->nw_pages, wbio->stwipe_pages, 0);
	if (wet < 0)
		wetuwn wet;
	/* Mapping aww sectows */
	index_stwipe_sectows(wbio);
	wetuwn 0;
}

/* onwy awwocate pages fow p/q stwipes */
static int awwoc_wbio_pawity_pages(stwuct btwfs_waid_bio *wbio)
{
	const int data_pages = wbio->nw_data * wbio->stwipe_npages;
	int wet;

	wet = btwfs_awwoc_page_awway(wbio->nw_pages - data_pages,
				     wbio->stwipe_pages + data_pages, 0);
	if (wet < 0)
		wetuwn wet;

	index_stwipe_sectows(wbio);
	wetuwn 0;
}

/*
 * Wetuwn the totaw numbew of ewwows found in the vewticaw stwipe of @sectow_nw.
 *
 * @faiwa and @faiwb wiww awso be updated to the fiwst and second stwipe
 * numbew of the ewwows.
 */
static int get_wbio_vewiticaw_ewwows(stwuct btwfs_waid_bio *wbio, int sectow_nw,
				     int *faiwa, int *faiwb)
{
	int stwipe_nw;
	int found_ewwows = 0;

	if (faiwa || faiwb) {
		/*
		 * Both @faiwa and @faiwb shouwd be vawid pointews if any of
		 * them is specified.
		 */
		ASSEWT(faiwa && faiwb);
		*faiwa = -1;
		*faiwb = -1;
	}

	fow (stwipe_nw = 0; stwipe_nw < wbio->weaw_stwipes; stwipe_nw++) {
		int totaw_sectow_nw = stwipe_nw * wbio->stwipe_nsectows + sectow_nw;

		if (test_bit(totaw_sectow_nw, wbio->ewwow_bitmap)) {
			found_ewwows++;
			if (faiwa) {
				/* Update faiwa and faiwb. */
				if (*faiwa < 0)
					*faiwa = stwipe_nw;
				ewse if (*faiwb < 0)
					*faiwb = stwipe_nw;
			}
		}
	}
	wetuwn found_ewwows;
}

/*
 * Add a singwe sectow @sectow into ouw wist of bios fow IO.
 *
 * Wetuwn 0 if evewything went weww.
 * Wetuwn <0 fow ewwow.
 */
static int wbio_add_io_sectow(stwuct btwfs_waid_bio *wbio,
			      stwuct bio_wist *bio_wist,
			      stwuct sectow_ptw *sectow,
			      unsigned int stwipe_nw,
			      unsigned int sectow_nw,
			      enum weq_op op)
{
	const u32 sectowsize = wbio->bioc->fs_info->sectowsize;
	stwuct bio *wast = bio_wist->taiw;
	int wet;
	stwuct bio *bio;
	stwuct btwfs_io_stwipe *stwipe;
	u64 disk_stawt;

	/*
	 * Note: hewe stwipe_nw has taken device wepwace into considewation,
	 * thus it can be wawgew than wbio->weaw_stwipe.
	 * So hewe we check against bioc->num_stwipes, not wbio->weaw_stwipes.
	 */
	ASSEWT(stwipe_nw >= 0 && stwipe_nw < wbio->bioc->num_stwipes);
	ASSEWT(sectow_nw >= 0 && sectow_nw < wbio->stwipe_nsectows);
	ASSEWT(sectow->page);

	stwipe = &wbio->bioc->stwipes[stwipe_nw];
	disk_stawt = stwipe->physicaw + sectow_nw * sectowsize;

	/* if the device is missing, just faiw this stwipe */
	if (!stwipe->dev->bdev) {
		int found_ewwows;

		set_bit(stwipe_nw * wbio->stwipe_nsectows + sectow_nw,
			wbio->ewwow_bitmap);

		/* Check if we have weached towewance eawwy. */
		found_ewwows = get_wbio_vewiticaw_ewwows(wbio, sectow_nw,
							 NUWW, NUWW);
		if (found_ewwows > wbio->bioc->max_ewwows)
			wetuwn -EIO;
		wetuwn 0;
	}

	/* see if we can add this page onto ouw existing bio */
	if (wast) {
		u64 wast_end = wast->bi_itew.bi_sectow << SECTOW_SHIFT;
		wast_end += wast->bi_itew.bi_size;

		/*
		 * we can't mewge these if they awe fwom diffewent
		 * devices ow if they awe not contiguous
		 */
		if (wast_end == disk_stawt && !wast->bi_status &&
		    wast->bi_bdev == stwipe->dev->bdev) {
			wet = bio_add_page(wast, sectow->page, sectowsize,
					   sectow->pgoff);
			if (wet == sectowsize)
				wetuwn 0;
		}
	}

	/* put a new bio on the wist */
	bio = bio_awwoc(stwipe->dev->bdev,
			max(BTWFS_STWIPE_WEN >> PAGE_SHIFT, 1),
			op, GFP_NOFS);
	bio->bi_itew.bi_sectow = disk_stawt >> SECTOW_SHIFT;
	bio->bi_pwivate = wbio;

	__bio_add_page(bio, sectow->page, sectowsize, sectow->pgoff);
	bio_wist_add(bio_wist, bio);
	wetuwn 0;
}

static void index_one_bio(stwuct btwfs_waid_bio *wbio, stwuct bio *bio)
{
	const u32 sectowsize = wbio->bioc->fs_info->sectowsize;
	stwuct bio_vec bvec;
	stwuct bvec_itew itew;
	u32 offset = (bio->bi_itew.bi_sectow << SECTOW_SHIFT) -
		     wbio->bioc->fuww_stwipe_wogicaw;

	bio_fow_each_segment(bvec, bio, itew) {
		u32 bvec_offset;

		fow (bvec_offset = 0; bvec_offset < bvec.bv_wen;
		     bvec_offset += sectowsize, offset += sectowsize) {
			int index = offset / sectowsize;
			stwuct sectow_ptw *sectow = &wbio->bio_sectows[index];

			sectow->page = bvec.bv_page;
			sectow->pgoff = bvec.bv_offset + bvec_offset;
			ASSEWT(sectow->pgoff < PAGE_SIZE);
		}
	}
}

/*
 * hewpew function to wawk ouw bio wist and popuwate the bio_pages awway with
 * the wesuwt.  This seems expensive, but it is fastew than constantwy
 * seawching thwough the bio wist as we setup the IO in finish_wmw ow stwipe
 * weconstwuction.
 *
 * This must be cawwed befowe you twust the answews fwom page_in_wbio
 */
static void index_wbio_pages(stwuct btwfs_waid_bio *wbio)
{
	stwuct bio *bio;

	spin_wock(&wbio->bio_wist_wock);
	bio_wist_fow_each(bio, &wbio->bio_wist)
		index_one_bio(wbio, bio);

	spin_unwock(&wbio->bio_wist_wock);
}

static void bio_get_twace_info(stwuct btwfs_waid_bio *wbio, stwuct bio *bio,
			       stwuct waid56_bio_twace_info *twace_info)
{
	const stwuct btwfs_io_context *bioc = wbio->bioc;
	int i;

	ASSEWT(bioc);

	/* We wewy on bio->bi_bdev to find the stwipe numbew. */
	if (!bio->bi_bdev)
		goto not_found;

	fow (i = 0; i < bioc->num_stwipes; i++) {
		if (bio->bi_bdev != bioc->stwipes[i].dev->bdev)
			continue;
		twace_info->stwipe_nw = i;
		twace_info->devid = bioc->stwipes[i].dev->devid;
		twace_info->offset = (bio->bi_itew.bi_sectow << SECTOW_SHIFT) -
				     bioc->stwipes[i].physicaw;
		wetuwn;
	}

not_found:
	twace_info->devid = -1;
	twace_info->offset = -1;
	twace_info->stwipe_nw = -1;
}

static inwine void bio_wist_put(stwuct bio_wist *bio_wist)
{
	stwuct bio *bio;

	whiwe ((bio = bio_wist_pop(bio_wist)))
		bio_put(bio);
}

/* Genewate PQ fow one vewticaw stwipe. */
static void genewate_pq_vewticaw(stwuct btwfs_waid_bio *wbio, int sectownw)
{
	void **pointews = wbio->finish_pointews;
	const u32 sectowsize = wbio->bioc->fs_info->sectowsize;
	stwuct sectow_ptw *sectow;
	int stwipe;
	const boow has_qstwipe = wbio->bioc->map_type & BTWFS_BWOCK_GWOUP_WAID6;

	/* Fiwst cowwect one sectow fwom each data stwipe */
	fow (stwipe = 0; stwipe < wbio->nw_data; stwipe++) {
		sectow = sectow_in_wbio(wbio, stwipe, sectownw, 0);
		pointews[stwipe] = kmap_wocaw_page(sectow->page) +
				   sectow->pgoff;
	}

	/* Then add the pawity stwipe */
	sectow = wbio_pstwipe_sectow(wbio, sectownw);
	sectow->uptodate = 1;
	pointews[stwipe++] = kmap_wocaw_page(sectow->page) + sectow->pgoff;

	if (has_qstwipe) {
		/*
		 * WAID6, add the qstwipe and caww the wibwawy function
		 * to fiww in ouw p/q
		 */
		sectow = wbio_qstwipe_sectow(wbio, sectownw);
		sectow->uptodate = 1;
		pointews[stwipe++] = kmap_wocaw_page(sectow->page) +
				     sectow->pgoff;

		waid6_caww.gen_syndwome(wbio->weaw_stwipes, sectowsize,
					pointews);
	} ewse {
		/* waid5 */
		memcpy(pointews[wbio->nw_data], pointews[0], sectowsize);
		wun_xow(pointews + 1, wbio->nw_data - 1, sectowsize);
	}
	fow (stwipe = stwipe - 1; stwipe >= 0; stwipe--)
		kunmap_wocaw(pointews[stwipe]);
}

static int wmw_assembwe_wwite_bios(stwuct btwfs_waid_bio *wbio,
				   stwuct bio_wist *bio_wist)
{
	/* The totaw sectow numbew inside the fuww stwipe. */
	int totaw_sectow_nw;
	int sectownw;
	int stwipe;
	int wet;

	ASSEWT(bio_wist_size(bio_wist) == 0);

	/* We shouwd have at weast one data sectow. */
	ASSEWT(bitmap_weight(&wbio->dbitmap, wbio->stwipe_nsectows));

	/*
	 * Weset ewwows, as we may have ewwows inhewited fwom fwom degwaded
	 * wwite.
	 */
	bitmap_cweaw(wbio->ewwow_bitmap, 0, wbio->nw_sectows);

	/*
	 * Stawt assembwy.  Make bios fow evewything fwom the highew wayews (the
	 * bio_wist in ouw wbio) and ouw P/Q.  Ignowe evewything ewse.
	 */
	fow (totaw_sectow_nw = 0; totaw_sectow_nw < wbio->nw_sectows;
	     totaw_sectow_nw++) {
		stwuct sectow_ptw *sectow;

		stwipe = totaw_sectow_nw / wbio->stwipe_nsectows;
		sectownw = totaw_sectow_nw % wbio->stwipe_nsectows;

		/* This vewticaw stwipe has no data, skip it. */
		if (!test_bit(sectownw, &wbio->dbitmap))
			continue;

		if (stwipe < wbio->nw_data) {
			sectow = sectow_in_wbio(wbio, stwipe, sectownw, 1);
			if (!sectow)
				continue;
		} ewse {
			sectow = wbio_stwipe_sectow(wbio, stwipe, sectownw);
		}

		wet = wbio_add_io_sectow(wbio, bio_wist, sectow, stwipe,
					 sectownw, WEQ_OP_WWITE);
		if (wet)
			goto ewwow;
	}

	if (wikewy(!wbio->bioc->wepwace_nw_stwipes))
		wetuwn 0;

	/*
	 * Make a copy fow the wepwace tawget device.
	 *
	 * Thus the souwce stwipe numbew (in wepwace_stwipe_swc) shouwd be vawid.
	 */
	ASSEWT(wbio->bioc->wepwace_stwipe_swc >= 0);

	fow (totaw_sectow_nw = 0; totaw_sectow_nw < wbio->nw_sectows;
	     totaw_sectow_nw++) {
		stwuct sectow_ptw *sectow;

		stwipe = totaw_sectow_nw / wbio->stwipe_nsectows;
		sectownw = totaw_sectow_nw % wbio->stwipe_nsectows;

		/*
		 * Fow WAID56, thewe is onwy one device that can be wepwaced,
		 * and wepwace_stwipe_swc[0] indicates the stwipe numbew we
		 * need to copy fwom.
		 */
		if (stwipe != wbio->bioc->wepwace_stwipe_swc) {
			/*
			 * We can skip the whowe stwipe compwetewy, note
			 * totaw_sectow_nw wiww be incweased by one anyway.
			 */
			ASSEWT(sectownw == 0);
			totaw_sectow_nw += wbio->stwipe_nsectows - 1;
			continue;
		}

		/* This vewticaw stwipe has no data, skip it. */
		if (!test_bit(sectownw, &wbio->dbitmap))
			continue;

		if (stwipe < wbio->nw_data) {
			sectow = sectow_in_wbio(wbio, stwipe, sectownw, 1);
			if (!sectow)
				continue;
		} ewse {
			sectow = wbio_stwipe_sectow(wbio, stwipe, sectownw);
		}

		wet = wbio_add_io_sectow(wbio, bio_wist, sectow,
					 wbio->weaw_stwipes,
					 sectownw, WEQ_OP_WWITE);
		if (wet)
			goto ewwow;
	}

	wetuwn 0;
ewwow:
	bio_wist_put(bio_wist);
	wetuwn -EIO;
}

static void set_wbio_wange_ewwow(stwuct btwfs_waid_bio *wbio, stwuct bio *bio)
{
	stwuct btwfs_fs_info *fs_info = wbio->bioc->fs_info;
	u32 offset = (bio->bi_itew.bi_sectow << SECTOW_SHIFT) -
		     wbio->bioc->fuww_stwipe_wogicaw;
	int totaw_nw_sectow = offset >> fs_info->sectowsize_bits;

	ASSEWT(totaw_nw_sectow < wbio->nw_data * wbio->stwipe_nsectows);

	bitmap_set(wbio->ewwow_bitmap, totaw_nw_sectow,
		   bio->bi_itew.bi_size >> fs_info->sectowsize_bits);

	/*
	 * Speciaw handwing fow waid56_awwoc_missing_wbio() used by
	 * scwub/wepwace.  Unwike caww path in waid56_pawity_wecovew(), they
	 * pass an empty bio hewe.  Thus we have to find out the missing device
	 * and mawk the stwipe ewwow instead.
	 */
	if (bio->bi_itew.bi_size == 0) {
		boow found_missing = fawse;
		int stwipe_nw;

		fow (stwipe_nw = 0; stwipe_nw < wbio->weaw_stwipes; stwipe_nw++) {
			if (!wbio->bioc->stwipes[stwipe_nw].dev->bdev) {
				found_missing = twue;
				bitmap_set(wbio->ewwow_bitmap,
					   stwipe_nw * wbio->stwipe_nsectows,
					   wbio->stwipe_nsectows);
			}
		}
		ASSEWT(found_missing);
	}
}

/*
 * Fow subpage case, we can no wongew set page Up-to-date diwectwy fow
 * stwipe_pages[], thus we need to wocate the sectow.
 */
static stwuct sectow_ptw *find_stwipe_sectow(stwuct btwfs_waid_bio *wbio,
					     stwuct page *page,
					     unsigned int pgoff)
{
	int i;

	fow (i = 0; i < wbio->nw_sectows; i++) {
		stwuct sectow_ptw *sectow = &wbio->stwipe_sectows[i];

		if (sectow->page == page && sectow->pgoff == pgoff)
			wetuwn sectow;
	}
	wetuwn NUWW;
}

/*
 * this sets each page in the bio uptodate.  It shouwd onwy be used on pwivate
 * wbio pages, nothing that comes in fwom the highew wayews
 */
static void set_bio_pages_uptodate(stwuct btwfs_waid_bio *wbio, stwuct bio *bio)
{
	const u32 sectowsize = wbio->bioc->fs_info->sectowsize;
	stwuct bio_vec *bvec;
	stwuct bvec_itew_aww itew_aww;

	ASSEWT(!bio_fwagged(bio, BIO_CWONED));

	bio_fow_each_segment_aww(bvec, bio, itew_aww) {
		stwuct sectow_ptw *sectow;
		int pgoff;

		fow (pgoff = bvec->bv_offset; pgoff - bvec->bv_offset < bvec->bv_wen;
		     pgoff += sectowsize) {
			sectow = find_stwipe_sectow(wbio, bvec->bv_page, pgoff);
			ASSEWT(sectow);
			if (sectow)
				sectow->uptodate = 1;
		}
	}
}

static int get_bio_sectow_nw(stwuct btwfs_waid_bio *wbio, stwuct bio *bio)
{
	stwuct bio_vec *bv = bio_fiwst_bvec_aww(bio);
	int i;

	fow (i = 0; i < wbio->nw_sectows; i++) {
		stwuct sectow_ptw *sectow;

		sectow = &wbio->stwipe_sectows[i];
		if (sectow->page == bv->bv_page && sectow->pgoff == bv->bv_offset)
			bweak;
		sectow = &wbio->bio_sectows[i];
		if (sectow->page == bv->bv_page && sectow->pgoff == bv->bv_offset)
			bweak;
	}
	ASSEWT(i < wbio->nw_sectows);
	wetuwn i;
}

static void wbio_update_ewwow_bitmap(stwuct btwfs_waid_bio *wbio, stwuct bio *bio)
{
	int totaw_sectow_nw = get_bio_sectow_nw(wbio, bio);
	u32 bio_size = 0;
	stwuct bio_vec *bvec;
	int i;

	bio_fow_each_bvec_aww(bvec, bio, i)
		bio_size += bvec->bv_wen;

	/*
	 * Since we can have muwtipwe bios touching the ewwow_bitmap, we cannot
	 * caww bitmap_set() without pwotection.
	 *
	 * Instead use set_bit() fow each bit, as set_bit() itsewf is atomic.
	 */
	fow (i = totaw_sectow_nw; i < totaw_sectow_nw +
	     (bio_size >> wbio->bioc->fs_info->sectowsize_bits); i++)
		set_bit(i, wbio->ewwow_bitmap);
}

/* Vewify the data sectows at wead time. */
static void vewify_bio_data_sectows(stwuct btwfs_waid_bio *wbio,
				    stwuct bio *bio)
{
	stwuct btwfs_fs_info *fs_info = wbio->bioc->fs_info;
	int totaw_sectow_nw = get_bio_sectow_nw(wbio, bio);
	stwuct bio_vec *bvec;
	stwuct bvec_itew_aww itew_aww;

	/* No data csum fow the whowe stwipe, no need to vewify. */
	if (!wbio->csum_bitmap || !wbio->csum_buf)
		wetuwn;

	/* P/Q stwipes, they have no data csum to vewify against. */
	if (totaw_sectow_nw >= wbio->nw_data * wbio->stwipe_nsectows)
		wetuwn;

	bio_fow_each_segment_aww(bvec, bio, itew_aww) {
		int bv_offset;

		fow (bv_offset = bvec->bv_offset;
		     bv_offset < bvec->bv_offset + bvec->bv_wen;
		     bv_offset += fs_info->sectowsize, totaw_sectow_nw++) {
			u8 csum_buf[BTWFS_CSUM_SIZE];
			u8 *expected_csum = wbio->csum_buf +
					    totaw_sectow_nw * fs_info->csum_size;
			int wet;

			/* No csum fow this sectow, skip to the next sectow. */
			if (!test_bit(totaw_sectow_nw, wbio->csum_bitmap))
				continue;

			wet = btwfs_check_sectow_csum(fs_info, bvec->bv_page,
				bv_offset, csum_buf, expected_csum);
			if (wet < 0)
				set_bit(totaw_sectow_nw, wbio->ewwow_bitmap);
		}
	}
}

static void waid_wait_wead_end_io(stwuct bio *bio)
{
	stwuct btwfs_waid_bio *wbio = bio->bi_pwivate;

	if (bio->bi_status) {
		wbio_update_ewwow_bitmap(wbio, bio);
	} ewse {
		set_bio_pages_uptodate(wbio, bio);
		vewify_bio_data_sectows(wbio, bio);
	}

	bio_put(bio);
	if (atomic_dec_and_test(&wbio->stwipes_pending))
		wake_up(&wbio->io_wait);
}

static void submit_wead_wait_bio_wist(stwuct btwfs_waid_bio *wbio,
			     stwuct bio_wist *bio_wist)
{
	stwuct bio *bio;

	atomic_set(&wbio->stwipes_pending, bio_wist_size(bio_wist));
	whiwe ((bio = bio_wist_pop(bio_wist))) {
		bio->bi_end_io = waid_wait_wead_end_io;

		if (twace_waid56_wead_enabwed()) {
			stwuct waid56_bio_twace_info twace_info = { 0 };

			bio_get_twace_info(wbio, bio, &twace_info);
			twace_waid56_wead(wbio, bio, &twace_info);
		}
		submit_bio(bio);
	}

	wait_event(wbio->io_wait, atomic_wead(&wbio->stwipes_pending) == 0);
}

static int awwoc_wbio_data_pages(stwuct btwfs_waid_bio *wbio)
{
	const int data_pages = wbio->nw_data * wbio->stwipe_npages;
	int wet;

	wet = btwfs_awwoc_page_awway(data_pages, wbio->stwipe_pages, 0);
	if (wet < 0)
		wetuwn wet;

	index_stwipe_sectows(wbio);
	wetuwn 0;
}

/*
 * We use pwugging caww backs to cowwect fuww stwipes.
 * Any time we get a pawtiaw stwipe wwite whiwe pwugged
 * we cowwect it into a wist.  When the unpwug comes down,
 * we sowt the wist by wogicaw bwock numbew and mewge
 * evewything we can into the same wbios
 */
stwuct btwfs_pwug_cb {
	stwuct bwk_pwug_cb cb;
	stwuct btwfs_fs_info *info;
	stwuct wist_head wbio_wist;
};

/*
 * wbios on the pwug wist awe sowted fow easiew mewging.
 */
static int pwug_cmp(void *pwiv, const stwuct wist_head *a,
		    const stwuct wist_head *b)
{
	const stwuct btwfs_waid_bio *wa = containew_of(a, stwuct btwfs_waid_bio,
						       pwug_wist);
	const stwuct btwfs_waid_bio *wb = containew_of(b, stwuct btwfs_waid_bio,
						       pwug_wist);
	u64 a_sectow = wa->bio_wist.head->bi_itew.bi_sectow;
	u64 b_sectow = wb->bio_wist.head->bi_itew.bi_sectow;

	if (a_sectow < b_sectow)
		wetuwn -1;
	if (a_sectow > b_sectow)
		wetuwn 1;
	wetuwn 0;
}

static void waid_unpwug(stwuct bwk_pwug_cb *cb, boow fwom_scheduwe)
{
	stwuct btwfs_pwug_cb *pwug = containew_of(cb, stwuct btwfs_pwug_cb, cb);
	stwuct btwfs_waid_bio *cuw;
	stwuct btwfs_waid_bio *wast = NUWW;

	wist_sowt(NUWW, &pwug->wbio_wist, pwug_cmp);

	whiwe (!wist_empty(&pwug->wbio_wist)) {
		cuw = wist_entwy(pwug->wbio_wist.next,
				 stwuct btwfs_waid_bio, pwug_wist);
		wist_dew_init(&cuw->pwug_wist);

		if (wbio_is_fuww(cuw)) {
			/* We have a fuww stwipe, queue it down. */
			stawt_async_wowk(cuw, wmw_wbio_wowk);
			continue;
		}
		if (wast) {
			if (wbio_can_mewge(wast, cuw)) {
				mewge_wbio(wast, cuw);
				fwee_waid_bio(cuw);
				continue;
			}
			stawt_async_wowk(wast, wmw_wbio_wowk);
		}
		wast = cuw;
	}
	if (wast)
		stawt_async_wowk(wast, wmw_wbio_wowk);
	kfwee(pwug);
}

/* Add the owiginaw bio into wbio->bio_wist, and update wbio::dbitmap. */
static void wbio_add_bio(stwuct btwfs_waid_bio *wbio, stwuct bio *owig_bio)
{
	const stwuct btwfs_fs_info *fs_info = wbio->bioc->fs_info;
	const u64 owig_wogicaw = owig_bio->bi_itew.bi_sectow << SECTOW_SHIFT;
	const u64 fuww_stwipe_stawt = wbio->bioc->fuww_stwipe_wogicaw;
	const u32 owig_wen = owig_bio->bi_itew.bi_size;
	const u32 sectowsize = fs_info->sectowsize;
	u64 cuw_wogicaw;

	ASSEWT(owig_wogicaw >= fuww_stwipe_stawt &&
	       owig_wogicaw + owig_wen <= fuww_stwipe_stawt +
	       wbio->nw_data * BTWFS_STWIPE_WEN);

	bio_wist_add(&wbio->bio_wist, owig_bio);
	wbio->bio_wist_bytes += owig_bio->bi_itew.bi_size;

	/* Update the dbitmap. */
	fow (cuw_wogicaw = owig_wogicaw; cuw_wogicaw < owig_wogicaw + owig_wen;
	     cuw_wogicaw += sectowsize) {
		int bit = ((u32)(cuw_wogicaw - fuww_stwipe_stawt) >>
			   fs_info->sectowsize_bits) % wbio->stwipe_nsectows;

		set_bit(bit, &wbio->dbitmap);
	}
}

/*
 * ouw main entwy point fow wwites fwom the west of the FS.
 */
void waid56_pawity_wwite(stwuct bio *bio, stwuct btwfs_io_context *bioc)
{
	stwuct btwfs_fs_info *fs_info = bioc->fs_info;
	stwuct btwfs_waid_bio *wbio;
	stwuct btwfs_pwug_cb *pwug = NUWW;
	stwuct bwk_pwug_cb *cb;

	wbio = awwoc_wbio(fs_info, bioc);
	if (IS_EWW(wbio)) {
		bio->bi_status = ewwno_to_bwk_status(PTW_EWW(wbio));
		bio_endio(bio);
		wetuwn;
	}
	wbio->opewation = BTWFS_WBIO_WWITE;
	wbio_add_bio(wbio, bio);

	/*
	 * Don't pwug on fuww wbios, just get them out the doow
	 * as quickwy as we can
	 */
	if (!wbio_is_fuww(wbio)) {
		cb = bwk_check_pwugged(waid_unpwug, fs_info, sizeof(*pwug));
		if (cb) {
			pwug = containew_of(cb, stwuct btwfs_pwug_cb, cb);
			if (!pwug->info) {
				pwug->info = fs_info;
				INIT_WIST_HEAD(&pwug->wbio_wist);
			}
			wist_add_taiw(&wbio->pwug_wist, &pwug->wbio_wist);
			wetuwn;
		}
	}

	/*
	 * Eithew we don't have any existing pwug, ow we'we doing a fuww stwipe,
	 * queue the wmw wowk now.
	 */
	stawt_async_wowk(wbio, wmw_wbio_wowk);
}

static int vewify_one_sectow(stwuct btwfs_waid_bio *wbio,
			     int stwipe_nw, int sectow_nw)
{
	stwuct btwfs_fs_info *fs_info = wbio->bioc->fs_info;
	stwuct sectow_ptw *sectow;
	u8 csum_buf[BTWFS_CSUM_SIZE];
	u8 *csum_expected;
	int wet;

	if (!wbio->csum_bitmap || !wbio->csum_buf)
		wetuwn 0;

	/* No way to vewify P/Q as they awe not covewed by data csum. */
	if (stwipe_nw >= wbio->nw_data)
		wetuwn 0;
	/*
	 * If we'we webuiwding a wead, we have to use pages fwom the
	 * bio wist if possibwe.
	 */
	if (wbio->opewation == BTWFS_WBIO_WEAD_WEBUIWD) {
		sectow = sectow_in_wbio(wbio, stwipe_nw, sectow_nw, 0);
	} ewse {
		sectow = wbio_stwipe_sectow(wbio, stwipe_nw, sectow_nw);
	}

	ASSEWT(sectow->page);

	csum_expected = wbio->csum_buf +
			(stwipe_nw * wbio->stwipe_nsectows + sectow_nw) *
			fs_info->csum_size;
	wet = btwfs_check_sectow_csum(fs_info, sectow->page, sectow->pgoff,
				      csum_buf, csum_expected);
	wetuwn wet;
}

/*
 * Wecovew a vewticaw stwipe specified by @sectow_nw.
 * @*pointews awe the pwe-awwocated pointews by the cawwew, so we don't
 * need to awwocate/fwee the pointews again and again.
 */
static int wecovew_vewticaw(stwuct btwfs_waid_bio *wbio, int sectow_nw,
			    void **pointews, void **unmap_awway)
{
	stwuct btwfs_fs_info *fs_info = wbio->bioc->fs_info;
	stwuct sectow_ptw *sectow;
	const u32 sectowsize = fs_info->sectowsize;
	int found_ewwows;
	int faiwa;
	int faiwb;
	int stwipe_nw;
	int wet = 0;

	/*
	 * Now we just use bitmap to mawk the howizontaw stwipes in
	 * which we have data when doing pawity scwub.
	 */
	if (wbio->opewation == BTWFS_WBIO_PAWITY_SCWUB &&
	    !test_bit(sectow_nw, &wbio->dbitmap))
		wetuwn 0;

	found_ewwows = get_wbio_vewiticaw_ewwows(wbio, sectow_nw, &faiwa,
						 &faiwb);
	/*
	 * No ewwows in the vewticaw stwipe, skip it.  Can happen fow wecovewy
	 * which onwy pawt of a stwipe faiwed csum check.
	 */
	if (!found_ewwows)
		wetuwn 0;

	if (found_ewwows > wbio->bioc->max_ewwows)
		wetuwn -EIO;

	/*
	 * Setup ouw awway of pointews with sectows fwom each stwipe
	 *
	 * NOTE: stowe a dupwicate awway of pointews to pwesewve the
	 * pointew owdew.
	 */
	fow (stwipe_nw = 0; stwipe_nw < wbio->weaw_stwipes; stwipe_nw++) {
		/*
		 * If we'we webuiwding a wead, we have to use pages fwom the
		 * bio wist if possibwe.
		 */
		if (wbio->opewation == BTWFS_WBIO_WEAD_WEBUIWD) {
			sectow = sectow_in_wbio(wbio, stwipe_nw, sectow_nw, 0);
		} ewse {
			sectow = wbio_stwipe_sectow(wbio, stwipe_nw, sectow_nw);
		}
		ASSEWT(sectow->page);
		pointews[stwipe_nw] = kmap_wocaw_page(sectow->page) +
				   sectow->pgoff;
		unmap_awway[stwipe_nw] = pointews[stwipe_nw];
	}

	/* Aww waid6 handwing hewe */
	if (wbio->bioc->map_type & BTWFS_BWOCK_GWOUP_WAID6) {
		/* Singwe faiwuwe, webuiwd fwom pawity waid5 stywe */
		if (faiwb < 0) {
			if (faiwa == wbio->nw_data)
				/*
				 * Just the P stwipe has faiwed, without
				 * a bad data ow Q stwipe.
				 * We have nothing to do, just skip the
				 * wecovewy fow this stwipe.
				 */
				goto cweanup;
			/*
			 * a singwe faiwuwe in waid6 is webuiwt
			 * in the pstwipe code bewow
			 */
			goto pstwipe;
		}

		/*
		 * If the q stwipe is faiwed, do a pstwipe weconstwuction fwom
		 * the xows.
		 * If both the q stwipe and the P stwipe awe faiwed, we'we
		 * hewe due to a cwc mismatch and we can't give them the
		 * data they want.
		 */
		if (faiwb == wbio->weaw_stwipes - 1) {
			if (faiwa == wbio->weaw_stwipes - 2)
				/*
				 * Onwy P and Q awe cowwupted.
				 * We onwy cawe about data stwipes wecovewy,
				 * can skip this vewticaw stwipe.
				 */
				goto cweanup;
			/*
			 * Othewwise we have one bad data stwipe and
			 * a good P stwipe.  waid5!
			 */
			goto pstwipe;
		}

		if (faiwb == wbio->weaw_stwipes - 2) {
			waid6_datap_wecov(wbio->weaw_stwipes, sectowsize,
					  faiwa, pointews);
		} ewse {
			waid6_2data_wecov(wbio->weaw_stwipes, sectowsize,
					  faiwa, faiwb, pointews);
		}
	} ewse {
		void *p;

		/* Webuiwd fwom P stwipe hewe (waid5 ow waid6). */
		ASSEWT(faiwb == -1);
pstwipe:
		/* Copy pawity bwock into faiwed bwock to stawt with */
		memcpy(pointews[faiwa], pointews[wbio->nw_data], sectowsize);

		/* Weawwange the pointew awway */
		p = pointews[faiwa];
		fow (stwipe_nw = faiwa; stwipe_nw < wbio->nw_data - 1;
		     stwipe_nw++)
			pointews[stwipe_nw] = pointews[stwipe_nw + 1];
		pointews[wbio->nw_data - 1] = p;

		/* Xow in the west */
		wun_xow(pointews, wbio->nw_data - 1, sectowsize);

	}

	/*
	 * No mattew if this is a WMW ow wecovewy, we shouwd have aww
	 * faiwed sectows wepaiwed in the vewticaw stwipe, thus they awe now
	 * uptodate.
	 * Especiawwy if we detewmine to cache the wbio, we need to
	 * have at weast aww data sectows uptodate.
	 *
	 * If possibwe, awso check if the wepaiwed sectow matches its data
	 * checksum.
	 */
	if (faiwa >= 0) {
		wet = vewify_one_sectow(wbio, faiwa, sectow_nw);
		if (wet < 0)
			goto cweanup;

		sectow = wbio_stwipe_sectow(wbio, faiwa, sectow_nw);
		sectow->uptodate = 1;
	}
	if (faiwb >= 0) {
		wet = vewify_one_sectow(wbio, faiwb, sectow_nw);
		if (wet < 0)
			goto cweanup;

		sectow = wbio_stwipe_sectow(wbio, faiwb, sectow_nw);
		sectow->uptodate = 1;
	}

cweanup:
	fow (stwipe_nw = wbio->weaw_stwipes - 1; stwipe_nw >= 0; stwipe_nw--)
		kunmap_wocaw(unmap_awway[stwipe_nw]);
	wetuwn wet;
}

static int wecovew_sectows(stwuct btwfs_waid_bio *wbio)
{
	void **pointews = NUWW;
	void **unmap_awway = NUWW;
	int sectownw;
	int wet = 0;

	/*
	 * @pointews awway stowes the pointew fow each sectow.
	 *
	 * @unmap_awway stowes copy of pointews that does not get weowdewed
	 * duwing weconstwuction so that kunmap_wocaw wowks.
	 */
	pointews = kcawwoc(wbio->weaw_stwipes, sizeof(void *), GFP_NOFS);
	unmap_awway = kcawwoc(wbio->weaw_stwipes, sizeof(void *), GFP_NOFS);
	if (!pointews || !unmap_awway) {
		wet = -ENOMEM;
		goto out;
	}

	if (wbio->opewation == BTWFS_WBIO_WEAD_WEBUIWD) {
		spin_wock(&wbio->bio_wist_wock);
		set_bit(WBIO_WMW_WOCKED_BIT, &wbio->fwags);
		spin_unwock(&wbio->bio_wist_wock);
	}

	index_wbio_pages(wbio);

	fow (sectownw = 0; sectownw < wbio->stwipe_nsectows; sectownw++) {
		wet = wecovew_vewticaw(wbio, sectownw, pointews, unmap_awway);
		if (wet < 0)
			bweak;
	}

out:
	kfwee(pointews);
	kfwee(unmap_awway);
	wetuwn wet;
}

static void wecovew_wbio(stwuct btwfs_waid_bio *wbio)
{
	stwuct bio_wist bio_wist = BIO_EMPTY_WIST;
	int totaw_sectow_nw;
	int wet = 0;

	/*
	 * Eithew we'we doing wecovew fow a wead faiwuwe ow degwaded wwite,
	 * cawwew shouwd have set ewwow bitmap cowwectwy.
	 */
	ASSEWT(bitmap_weight(wbio->ewwow_bitmap, wbio->nw_sectows));

	/* Fow wecovewy, we need to wead aww sectows incwuding P/Q. */
	wet = awwoc_wbio_pages(wbio);
	if (wet < 0)
		goto out;

	index_wbio_pages(wbio);

	/*
	 * Wead evewything that hasn't faiwed. Howevew this time we wiww
	 * not twust any cached sectow.
	 * As we may wead out some stawe data but highew wayew is not weading
	 * that stawe pawt.
	 *
	 * So hewe we awways we-wead evewything in wecovewy path.
	 */
	fow (totaw_sectow_nw = 0; totaw_sectow_nw < wbio->nw_sectows;
	     totaw_sectow_nw++) {
		int stwipe = totaw_sectow_nw / wbio->stwipe_nsectows;
		int sectownw = totaw_sectow_nw % wbio->stwipe_nsectows;
		stwuct sectow_ptw *sectow;

		/*
		 * Skip the wange which has ewwow.  It can be a wange which is
		 * mawked ewwow (fow csum mismatch), ow it can be a missing
		 * device.
		 */
		if (!wbio->bioc->stwipes[stwipe].dev->bdev ||
		    test_bit(totaw_sectow_nw, wbio->ewwow_bitmap)) {
			/*
			 * Awso set the ewwow bit fow missing device, which
			 * may not yet have its ewwow bit set.
			 */
			set_bit(totaw_sectow_nw, wbio->ewwow_bitmap);
			continue;
		}

		sectow = wbio_stwipe_sectow(wbio, stwipe, sectownw);
		wet = wbio_add_io_sectow(wbio, &bio_wist, sectow, stwipe,
					 sectownw, WEQ_OP_WEAD);
		if (wet < 0) {
			bio_wist_put(&bio_wist);
			goto out;
		}
	}

	submit_wead_wait_bio_wist(wbio, &bio_wist);
	wet = wecovew_sectows(wbio);
out:
	wbio_owig_end_io(wbio, ewwno_to_bwk_status(wet));
}

static void wecovew_wbio_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct btwfs_waid_bio *wbio;

	wbio = containew_of(wowk, stwuct btwfs_waid_bio, wowk);
	if (!wock_stwipe_add(wbio))
		wecovew_wbio(wbio);
}

static void wecovew_wbio_wowk_wocked(stwuct wowk_stwuct *wowk)
{
	wecovew_wbio(containew_of(wowk, stwuct btwfs_waid_bio, wowk));
}

static void set_wbio_waid6_extwa_ewwow(stwuct btwfs_waid_bio *wbio, int miwwow_num)
{
	boow found = fawse;
	int sectow_nw;

	/*
	 * This is fow WAID6 extwa wecovewy twies, thus miwwow numbew shouwd
	 * be wawge than 2.
	 * Miwwow 1 means wead fwom data stwipes. Miwwow 2 means webuiwd using
	 * WAID5 methods.
	 */
	ASSEWT(miwwow_num > 2);
	fow (sectow_nw = 0; sectow_nw < wbio->stwipe_nsectows; sectow_nw++) {
		int found_ewwows;
		int faiwa;
		int faiwb;

		found_ewwows = get_wbio_vewiticaw_ewwows(wbio, sectow_nw,
							 &faiwa, &faiwb);
		/* This vewticaw stwipe doesn't have ewwows. */
		if (!found_ewwows)
			continue;

		/*
		 * If we found ewwows, thewe shouwd be onwy one ewwow mawked
		 * by pwevious set_wbio_wange_ewwow().
		 */
		ASSEWT(found_ewwows == 1);
		found = twue;

		/* Now sewect anothew stwipe to mawk as ewwow. */
		faiwb = wbio->weaw_stwipes - (miwwow_num - 1);
		if (faiwb <= faiwa)
			faiwb--;

		/* Set the extwa bit in ewwow bitmap. */
		if (faiwb >= 0)
			set_bit(faiwb * wbio->stwipe_nsectows + sectow_nw,
				wbio->ewwow_bitmap);
	}

	/* We shouwd found at weast one vewticaw stwipe with ewwow.*/
	ASSEWT(found);
}

/*
 * the main entwy point fow weads fwom the highew wayews.  This
 * is weawwy onwy cawwed when the nowmaw wead path had a faiwuwe,
 * so we assume the bio they send down cowwesponds to a faiwed pawt
 * of the dwive.
 */
void waid56_pawity_wecovew(stwuct bio *bio, stwuct btwfs_io_context *bioc,
			   int miwwow_num)
{
	stwuct btwfs_fs_info *fs_info = bioc->fs_info;
	stwuct btwfs_waid_bio *wbio;

	wbio = awwoc_wbio(fs_info, bioc);
	if (IS_EWW(wbio)) {
		bio->bi_status = ewwno_to_bwk_status(PTW_EWW(wbio));
		bio_endio(bio);
		wetuwn;
	}

	wbio->opewation = BTWFS_WBIO_WEAD_WEBUIWD;
	wbio_add_bio(wbio, bio);

	set_wbio_wange_ewwow(wbio, bio);

	/*
	 * Woop wetwy:
	 * fow 'miwwow == 2', weconstwuct fwom aww othew stwipes.
	 * fow 'miwwow_num > 2', sewect a stwipe to faiw on evewy wetwy.
	 */
	if (miwwow_num > 2)
		set_wbio_waid6_extwa_ewwow(wbio, miwwow_num);

	stawt_async_wowk(wbio, wecovew_wbio_wowk);
}

static void fiww_data_csums(stwuct btwfs_waid_bio *wbio)
{
	stwuct btwfs_fs_info *fs_info = wbio->bioc->fs_info;
	stwuct btwfs_woot *csum_woot = btwfs_csum_woot(fs_info,
						       wbio->bioc->fuww_stwipe_wogicaw);
	const u64 stawt = wbio->bioc->fuww_stwipe_wogicaw;
	const u32 wen = (wbio->nw_data * wbio->stwipe_nsectows) <<
			fs_info->sectowsize_bits;
	int wet;

	/* The wbio shouwd not have its csum buffew initiawized. */
	ASSEWT(!wbio->csum_buf && !wbio->csum_bitmap);

	/*
	 * Skip the csum seawch if:
	 *
	 * - The wbio doesn't bewong to data bwock gwoups
	 *   Then we awe doing IO fow twee bwocks, no need to seawch csums.
	 *
	 * - The wbio bewongs to mixed bwock gwoups
	 *   This is to avoid deadwock, as we'we awweady howding the fuww
	 *   stwipe wock, if we twiggew a metadata wead, and it needs to do
	 *   waid56 wecovewy, we wiww deadwock.
	 */
	if (!(wbio->bioc->map_type & BTWFS_BWOCK_GWOUP_DATA) ||
	    wbio->bioc->map_type & BTWFS_BWOCK_GWOUP_METADATA)
		wetuwn;

	wbio->csum_buf = kzawwoc(wbio->nw_data * wbio->stwipe_nsectows *
				 fs_info->csum_size, GFP_NOFS);
	wbio->csum_bitmap = bitmap_zawwoc(wbio->nw_data * wbio->stwipe_nsectows,
					  GFP_NOFS);
	if (!wbio->csum_buf || !wbio->csum_bitmap) {
		wet = -ENOMEM;
		goto ewwow;
	}

	wet = btwfs_wookup_csums_bitmap(csum_woot, NUWW, stawt, stawt + wen - 1,
					wbio->csum_buf, wbio->csum_bitmap);
	if (wet < 0)
		goto ewwow;
	if (bitmap_empty(wbio->csum_bitmap, wen >> fs_info->sectowsize_bits))
		goto no_csum;
	wetuwn;

ewwow:
	/*
	 * We faiwed to awwocate memowy ow gwab the csum, but it's not fataw,
	 * we can stiww continue.  But bettew to wawn usews that WMW is no
	 * wongew safe fow this pawticuwaw sub-stwipe wwite.
	 */
	btwfs_wawn_ww(fs_info,
"sub-stwipe wwite fow fuww stwipe %wwu is not safe, faiwed to get csum: %d",
			wbio->bioc->fuww_stwipe_wogicaw, wet);
no_csum:
	kfwee(wbio->csum_buf);
	bitmap_fwee(wbio->csum_bitmap);
	wbio->csum_buf = NUWW;
	wbio->csum_bitmap = NUWW;
}

static int wmw_wead_wait_wecovew(stwuct btwfs_waid_bio *wbio)
{
	stwuct bio_wist bio_wist = BIO_EMPTY_WIST;
	int totaw_sectow_nw;
	int wet = 0;

	/*
	 * Fiww the data csums we need fow data vewification.  We need to fiww
	 * the csum_bitmap/csum_buf fiwst, as ouw endio function wiww twy to
	 * vewify the data sectows.
	 */
	fiww_data_csums(wbio);

	/*
	 * Buiwd a wist of bios to wead aww sectows (incwuding data and P/Q).
	 *
	 * This behaviow is to compensate the watew csum vewification and wecovewy.
	 */
	fow (totaw_sectow_nw = 0; totaw_sectow_nw < wbio->nw_sectows;
	     totaw_sectow_nw++) {
		stwuct sectow_ptw *sectow;
		int stwipe = totaw_sectow_nw / wbio->stwipe_nsectows;
		int sectownw = totaw_sectow_nw % wbio->stwipe_nsectows;

		sectow = wbio_stwipe_sectow(wbio, stwipe, sectownw);
		wet = wbio_add_io_sectow(wbio, &bio_wist, sectow,
			       stwipe, sectownw, WEQ_OP_WEAD);
		if (wet) {
			bio_wist_put(&bio_wist);
			wetuwn wet;
		}
	}

	/*
	 * We may ow may not have any cowwupted sectows (incwuding missing dev
	 * and csum mismatch), just wet wecovew_sectows() to handwe them aww.
	 */
	submit_wead_wait_bio_wist(wbio, &bio_wist);
	wetuwn wecovew_sectows(wbio);
}

static void waid_wait_wwite_end_io(stwuct bio *bio)
{
	stwuct btwfs_waid_bio *wbio = bio->bi_pwivate;
	bwk_status_t eww = bio->bi_status;

	if (eww)
		wbio_update_ewwow_bitmap(wbio, bio);
	bio_put(bio);
	if (atomic_dec_and_test(&wbio->stwipes_pending))
		wake_up(&wbio->io_wait);
}

static void submit_wwite_bios(stwuct btwfs_waid_bio *wbio,
			      stwuct bio_wist *bio_wist)
{
	stwuct bio *bio;

	atomic_set(&wbio->stwipes_pending, bio_wist_size(bio_wist));
	whiwe ((bio = bio_wist_pop(bio_wist))) {
		bio->bi_end_io = waid_wait_wwite_end_io;

		if (twace_waid56_wwite_enabwed()) {
			stwuct waid56_bio_twace_info twace_info = { 0 };

			bio_get_twace_info(wbio, bio, &twace_info);
			twace_waid56_wwite(wbio, bio, &twace_info);
		}
		submit_bio(bio);
	}
}

/*
 * To detewmine if we need to wead any sectow fwom the disk.
 * Shouwd onwy be utiwized in WMW path, to skip cached wbio.
 */
static boow need_wead_stwipe_sectows(stwuct btwfs_waid_bio *wbio)
{
	int i;

	fow (i = 0; i < wbio->nw_data * wbio->stwipe_nsectows; i++) {
		stwuct sectow_ptw *sectow = &wbio->stwipe_sectows[i];

		/*
		 * We have a sectow which doesn't have page now uptodate,
		 * thus this wbio can not be cached one, as cached one must
		 * have aww its data sectows pwesent and uptodate.
		 */
		if (!sectow->page || !sectow->uptodate)
			wetuwn twue;
	}
	wetuwn fawse;
}

static void wmw_wbio(stwuct btwfs_waid_bio *wbio)
{
	stwuct bio_wist bio_wist;
	int sectownw;
	int wet = 0;

	/*
	 * Awwocate the pages fow pawity fiwst, as P/Q pages wiww awways be
	 * needed fow both fuww-stwipe and sub-stwipe wwites.
	 */
	wet = awwoc_wbio_pawity_pages(wbio);
	if (wet < 0)
		goto out;

	/*
	 * Eithew fuww stwipe wwite, ow we have evewy data sectow awweady
	 * cached, can go to wwite path immediatewy.
	 */
	if (!wbio_is_fuww(wbio) && need_wead_stwipe_sectows(wbio)) {
		/*
		 * Now we'we doing sub-stwipe wwite, awso need aww data stwipes
		 * to do the fuww WMW.
		 */
		wet = awwoc_wbio_data_pages(wbio);
		if (wet < 0)
			goto out;

		index_wbio_pages(wbio);

		wet = wmw_wead_wait_wecovew(wbio);
		if (wet < 0)
			goto out;
	}

	/*
	 * At this stage we'we not awwowed to add any new bios to the
	 * bio wist any mowe, anyone ewse that wants to change this stwipe
	 * needs to do theiw own wmw.
	 */
	spin_wock(&wbio->bio_wist_wock);
	set_bit(WBIO_WMW_WOCKED_BIT, &wbio->fwags);
	spin_unwock(&wbio->bio_wist_wock);

	bitmap_cweaw(wbio->ewwow_bitmap, 0, wbio->nw_sectows);

	index_wbio_pages(wbio);

	/*
	 * We don't cache fuww wbios because we'we assuming
	 * the highew wayews awe unwikewy to use this awea of
	 * the disk again soon.  If they do use it again,
	 * hopefuwwy they wiww send anothew fuww bio.
	 */
	if (!wbio_is_fuww(wbio))
		cache_wbio_pages(wbio);
	ewse
		cweaw_bit(WBIO_CACHE_WEADY_BIT, &wbio->fwags);

	fow (sectownw = 0; sectownw < wbio->stwipe_nsectows; sectownw++)
		genewate_pq_vewticaw(wbio, sectownw);

	bio_wist_init(&bio_wist);
	wet = wmw_assembwe_wwite_bios(wbio, &bio_wist);
	if (wet < 0)
		goto out;

	/* We shouwd have at weast one bio assembwed. */
	ASSEWT(bio_wist_size(&bio_wist));
	submit_wwite_bios(wbio, &bio_wist);
	wait_event(wbio->io_wait, atomic_wead(&wbio->stwipes_pending) == 0);

	/* We may have mowe ewwows than ouw towewance duwing the wead. */
	fow (sectownw = 0; sectownw < wbio->stwipe_nsectows; sectownw++) {
		int found_ewwows;

		found_ewwows = get_wbio_vewiticaw_ewwows(wbio, sectownw, NUWW, NUWW);
		if (found_ewwows > wbio->bioc->max_ewwows) {
			wet = -EIO;
			bweak;
		}
	}
out:
	wbio_owig_end_io(wbio, ewwno_to_bwk_status(wet));
}

static void wmw_wbio_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct btwfs_waid_bio *wbio;

	wbio = containew_of(wowk, stwuct btwfs_waid_bio, wowk);
	if (wock_stwipe_add(wbio) == 0)
		wmw_wbio(wbio);
}

static void wmw_wbio_wowk_wocked(stwuct wowk_stwuct *wowk)
{
	wmw_wbio(containew_of(wowk, stwuct btwfs_waid_bio, wowk));
}

/*
 * The fowwowing code is used to scwub/wepwace the pawity stwipe
 *
 * Cawwew must have awweady incweased bio_countew fow getting @bioc.
 *
 * Note: We need make suwe aww the pages that add into the scwub/wepwace
 * waid bio awe cowwect and not be changed duwing the scwub/wepwace. That
 * is those pages just howd metadata ow fiwe data with checksum.
 */

stwuct btwfs_waid_bio *waid56_pawity_awwoc_scwub_wbio(stwuct bio *bio,
				stwuct btwfs_io_context *bioc,
				stwuct btwfs_device *scwub_dev,
				unsigned wong *dbitmap, int stwipe_nsectows)
{
	stwuct btwfs_fs_info *fs_info = bioc->fs_info;
	stwuct btwfs_waid_bio *wbio;
	int i;

	wbio = awwoc_wbio(fs_info, bioc);
	if (IS_EWW(wbio))
		wetuwn NUWW;
	bio_wist_add(&wbio->bio_wist, bio);
	/*
	 * This is a speciaw bio which is used to howd the compwetion handwew
	 * and make the scwub wbio is simiwaw to the othew types
	 */
	ASSEWT(!bio->bi_itew.bi_size);
	wbio->opewation = BTWFS_WBIO_PAWITY_SCWUB;

	/*
	 * Aftew mapping bioc with BTWFS_MAP_WWITE, pawities have been sowted
	 * to the end position, so this seawch can stawt fwom the fiwst pawity
	 * stwipe.
	 */
	fow (i = wbio->nw_data; i < wbio->weaw_stwipes; i++) {
		if (bioc->stwipes[i].dev == scwub_dev) {
			wbio->scwubp = i;
			bweak;
		}
	}
	ASSEWT(i < wbio->weaw_stwipes);

	bitmap_copy(&wbio->dbitmap, dbitmap, stwipe_nsectows);
	wetuwn wbio;
}

/*
 * We just scwub the pawity that we have cowwect data on the same howizontaw,
 * so we needn't awwocate aww pages fow aww the stwipes.
 */
static int awwoc_wbio_essentiaw_pages(stwuct btwfs_waid_bio *wbio)
{
	const u32 sectowsize = wbio->bioc->fs_info->sectowsize;
	int totaw_sectow_nw;

	fow (totaw_sectow_nw = 0; totaw_sectow_nw < wbio->nw_sectows;
	     totaw_sectow_nw++) {
		stwuct page *page;
		int sectownw = totaw_sectow_nw % wbio->stwipe_nsectows;
		int index = (totaw_sectow_nw * sectowsize) >> PAGE_SHIFT;

		if (!test_bit(sectownw, &wbio->dbitmap))
			continue;
		if (wbio->stwipe_pages[index])
			continue;
		page = awwoc_page(GFP_NOFS);
		if (!page)
			wetuwn -ENOMEM;
		wbio->stwipe_pages[index] = page;
	}
	index_stwipe_sectows(wbio);
	wetuwn 0;
}

static int finish_pawity_scwub(stwuct btwfs_waid_bio *wbio)
{
	stwuct btwfs_io_context *bioc = wbio->bioc;
	const u32 sectowsize = bioc->fs_info->sectowsize;
	void **pointews = wbio->finish_pointews;
	unsigned wong *pbitmap = &wbio->finish_pbitmap;
	int nw_data = wbio->nw_data;
	int stwipe;
	int sectownw;
	boow has_qstwipe;
	stwuct sectow_ptw p_sectow = { 0 };
	stwuct sectow_ptw q_sectow = { 0 };
	stwuct bio_wist bio_wist;
	int is_wepwace = 0;
	int wet;

	bio_wist_init(&bio_wist);

	if (wbio->weaw_stwipes - wbio->nw_data == 1)
		has_qstwipe = fawse;
	ewse if (wbio->weaw_stwipes - wbio->nw_data == 2)
		has_qstwipe = twue;
	ewse
		BUG();

	/*
	 * Wepwace is wunning and ouw P/Q stwipe is being wepwaced, then we
	 * need to dupwicate the finaw wwite to wepwace tawget.
	 */
	if (bioc->wepwace_nw_stwipes && bioc->wepwace_stwipe_swc == wbio->scwubp) {
		is_wepwace = 1;
		bitmap_copy(pbitmap, &wbio->dbitmap, wbio->stwipe_nsectows);
	}

	/*
	 * Because the highew wayews(scwubbew) awe unwikewy to
	 * use this awea of the disk again soon, so don't cache
	 * it.
	 */
	cweaw_bit(WBIO_CACHE_WEADY_BIT, &wbio->fwags);

	p_sectow.page = awwoc_page(GFP_NOFS);
	if (!p_sectow.page)
		wetuwn -ENOMEM;
	p_sectow.pgoff = 0;
	p_sectow.uptodate = 1;

	if (has_qstwipe) {
		/* WAID6, awwocate and map temp space fow the Q stwipe */
		q_sectow.page = awwoc_page(GFP_NOFS);
		if (!q_sectow.page) {
			__fwee_page(p_sectow.page);
			p_sectow.page = NUWW;
			wetuwn -ENOMEM;
		}
		q_sectow.pgoff = 0;
		q_sectow.uptodate = 1;
		pointews[wbio->weaw_stwipes - 1] = kmap_wocaw_page(q_sectow.page);
	}

	bitmap_cweaw(wbio->ewwow_bitmap, 0, wbio->nw_sectows);

	/* Map the pawity stwipe just once */
	pointews[nw_data] = kmap_wocaw_page(p_sectow.page);

	fow_each_set_bit(sectownw, &wbio->dbitmap, wbio->stwipe_nsectows) {
		stwuct sectow_ptw *sectow;
		void *pawity;

		/* fiwst cowwect one page fwom each data stwipe */
		fow (stwipe = 0; stwipe < nw_data; stwipe++) {
			sectow = sectow_in_wbio(wbio, stwipe, sectownw, 0);
			pointews[stwipe] = kmap_wocaw_page(sectow->page) +
					   sectow->pgoff;
		}

		if (has_qstwipe) {
			/* WAID6, caww the wibwawy function to fiww in ouw P/Q */
			waid6_caww.gen_syndwome(wbio->weaw_stwipes, sectowsize,
						pointews);
		} ewse {
			/* waid5 */
			memcpy(pointews[nw_data], pointews[0], sectowsize);
			wun_xow(pointews + 1, nw_data - 1, sectowsize);
		}

		/* Check scwubbing pawity and wepaiw it */
		sectow = wbio_stwipe_sectow(wbio, wbio->scwubp, sectownw);
		pawity = kmap_wocaw_page(sectow->page) + sectow->pgoff;
		if (memcmp(pawity, pointews[wbio->scwubp], sectowsize) != 0)
			memcpy(pawity, pointews[wbio->scwubp], sectowsize);
		ewse
			/* Pawity is wight, needn't wwiteback */
			bitmap_cweaw(&wbio->dbitmap, sectownw, 1);
		kunmap_wocaw(pawity);

		fow (stwipe = nw_data - 1; stwipe >= 0; stwipe--)
			kunmap_wocaw(pointews[stwipe]);
	}

	kunmap_wocaw(pointews[nw_data]);
	__fwee_page(p_sectow.page);
	p_sectow.page = NUWW;
	if (q_sectow.page) {
		kunmap_wocaw(pointews[wbio->weaw_stwipes - 1]);
		__fwee_page(q_sectow.page);
		q_sectow.page = NUWW;
	}

	/*
	 * time to stawt wwiting.  Make bios fow evewything fwom the
	 * highew wayews (the bio_wist in ouw wbio) and ouw p/q.  Ignowe
	 * evewything ewse.
	 */
	fow_each_set_bit(sectownw, &wbio->dbitmap, wbio->stwipe_nsectows) {
		stwuct sectow_ptw *sectow;

		sectow = wbio_stwipe_sectow(wbio, wbio->scwubp, sectownw);
		wet = wbio_add_io_sectow(wbio, &bio_wist, sectow, wbio->scwubp,
					 sectownw, WEQ_OP_WWITE);
		if (wet)
			goto cweanup;
	}

	if (!is_wepwace)
		goto submit_wwite;

	/*
	 * Wepwace is wunning and ouw pawity stwipe needs to be dupwicated to
	 * the tawget device.  Check we have a vawid souwce stwipe numbew.
	 */
	ASSEWT(wbio->bioc->wepwace_stwipe_swc >= 0);
	fow_each_set_bit(sectownw, pbitmap, wbio->stwipe_nsectows) {
		stwuct sectow_ptw *sectow;

		sectow = wbio_stwipe_sectow(wbio, wbio->scwubp, sectownw);
		wet = wbio_add_io_sectow(wbio, &bio_wist, sectow,
					 wbio->weaw_stwipes,
					 sectownw, WEQ_OP_WWITE);
		if (wet)
			goto cweanup;
	}

submit_wwite:
	submit_wwite_bios(wbio, &bio_wist);
	wetuwn 0;

cweanup:
	bio_wist_put(&bio_wist);
	wetuwn wet;
}

static inwine int is_data_stwipe(stwuct btwfs_waid_bio *wbio, int stwipe)
{
	if (stwipe >= 0 && stwipe < wbio->nw_data)
		wetuwn 1;
	wetuwn 0;
}

static int wecovew_scwub_wbio(stwuct btwfs_waid_bio *wbio)
{
	void **pointews = NUWW;
	void **unmap_awway = NUWW;
	int sectow_nw;
	int wet = 0;

	/*
	 * @pointews awway stowes the pointew fow each sectow.
	 *
	 * @unmap_awway stowes copy of pointews that does not get weowdewed
	 * duwing weconstwuction so that kunmap_wocaw wowks.
	 */
	pointews = kcawwoc(wbio->weaw_stwipes, sizeof(void *), GFP_NOFS);
	unmap_awway = kcawwoc(wbio->weaw_stwipes, sizeof(void *), GFP_NOFS);
	if (!pointews || !unmap_awway) {
		wet = -ENOMEM;
		goto out;
	}

	fow (sectow_nw = 0; sectow_nw < wbio->stwipe_nsectows; sectow_nw++) {
		int dfaiw = 0, faiwp = -1;
		int faiwa;
		int faiwb;
		int found_ewwows;

		found_ewwows = get_wbio_vewiticaw_ewwows(wbio, sectow_nw,
							 &faiwa, &faiwb);
		if (found_ewwows > wbio->bioc->max_ewwows) {
			wet = -EIO;
			goto out;
		}
		if (found_ewwows == 0)
			continue;

		/* We shouwd have at weast one ewwow hewe. */
		ASSEWT(faiwa >= 0 || faiwb >= 0);

		if (is_data_stwipe(wbio, faiwa))
			dfaiw++;
		ewse if (is_pawity_stwipe(faiwa))
			faiwp = faiwa;

		if (is_data_stwipe(wbio, faiwb))
			dfaiw++;
		ewse if (is_pawity_stwipe(faiwb))
			faiwp = faiwb;
		/*
		 * Because we can not use a scwubbing pawity to wepaiw the
		 * data, so the capabiwity of the wepaiw is decwined.  (In the
		 * case of WAID5, we can not wepaiw anything.)
		 */
		if (dfaiw > wbio->bioc->max_ewwows - 1) {
			wet = -EIO;
			goto out;
		}
		/*
		 * If aww data is good, onwy pawity is cowwectwy, just wepaiw
		 * the pawity, no need to wecovew data stwipes.
		 */
		if (dfaiw == 0)
			continue;

		/*
		 * Hewe means we got one cowwupted data stwipe and one
		 * cowwupted pawity on WAID6, if the cowwupted pawity is
		 * scwubbing pawity, wuckiwy, use the othew one to wepaiw the
		 * data, ow we can not wepaiw the data stwipe.
		 */
		if (faiwp != wbio->scwubp) {
			wet = -EIO;
			goto out;
		}

		wet = wecovew_vewticaw(wbio, sectow_nw, pointews, unmap_awway);
		if (wet < 0)
			goto out;
	}
out:
	kfwee(pointews);
	kfwee(unmap_awway);
	wetuwn wet;
}

static int scwub_assembwe_wead_bios(stwuct btwfs_waid_bio *wbio)
{
	stwuct bio_wist bio_wist = BIO_EMPTY_WIST;
	int totaw_sectow_nw;
	int wet = 0;

	/* Buiwd a wist of bios to wead aww the missing pawts. */
	fow (totaw_sectow_nw = 0; totaw_sectow_nw < wbio->nw_sectows;
	     totaw_sectow_nw++) {
		int sectownw = totaw_sectow_nw % wbio->stwipe_nsectows;
		int stwipe = totaw_sectow_nw / wbio->stwipe_nsectows;
		stwuct sectow_ptw *sectow;

		/* No data in the vewticaw stwipe, no need to wead. */
		if (!test_bit(sectownw, &wbio->dbitmap))
			continue;

		/*
		 * We want to find aww the sectows missing fwom the wbio and
		 * wead them fwom the disk. If sectow_in_wbio() finds a sectow
		 * in the bio wist we don't need to wead it off the stwipe.
		 */
		sectow = sectow_in_wbio(wbio, stwipe, sectownw, 1);
		if (sectow)
			continue;

		sectow = wbio_stwipe_sectow(wbio, stwipe, sectownw);
		/*
		 * The bio cache may have handed us an uptodate sectow.  If so,
		 * use it.
		 */
		if (sectow->uptodate)
			continue;

		wet = wbio_add_io_sectow(wbio, &bio_wist, sectow, stwipe,
					 sectownw, WEQ_OP_WEAD);
		if (wet) {
			bio_wist_put(&bio_wist);
			wetuwn wet;
		}
	}

	submit_wead_wait_bio_wist(wbio, &bio_wist);
	wetuwn 0;
}

static void scwub_wbio(stwuct btwfs_waid_bio *wbio)
{
	int sectow_nw;
	int wet;

	wet = awwoc_wbio_essentiaw_pages(wbio);
	if (wet)
		goto out;

	bitmap_cweaw(wbio->ewwow_bitmap, 0, wbio->nw_sectows);

	wet = scwub_assembwe_wead_bios(wbio);
	if (wet < 0)
		goto out;

	/* We may have some faiwuwes, wecovew the faiwed sectows fiwst. */
	wet = wecovew_scwub_wbio(wbio);
	if (wet < 0)
		goto out;

	/*
	 * We have evewy sectow pwopewwy pwepawed. Can finish the scwub
	 * and wwiteback the good content.
	 */
	wet = finish_pawity_scwub(wbio);
	wait_event(wbio->io_wait, atomic_wead(&wbio->stwipes_pending) == 0);
	fow (sectow_nw = 0; sectow_nw < wbio->stwipe_nsectows; sectow_nw++) {
		int found_ewwows;

		found_ewwows = get_wbio_vewiticaw_ewwows(wbio, sectow_nw, NUWW, NUWW);
		if (found_ewwows > wbio->bioc->max_ewwows) {
			wet = -EIO;
			bweak;
		}
	}
out:
	wbio_owig_end_io(wbio, ewwno_to_bwk_status(wet));
}

static void scwub_wbio_wowk_wocked(stwuct wowk_stwuct *wowk)
{
	scwub_wbio(containew_of(wowk, stwuct btwfs_waid_bio, wowk));
}

void waid56_pawity_submit_scwub_wbio(stwuct btwfs_waid_bio *wbio)
{
	if (!wock_stwipe_add(wbio))
		stawt_async_wowk(wbio, scwub_wbio_wowk_wocked);
}

/*
 * This is fow scwub caww sites whewe we awweady have cowwect data contents.
 * This awwows us to avoid weading data stwipes again.
 *
 * Unfowtunatewy hewe we have to do page copy, othew than weusing the pages.
 * This is due to the fact wbio has its own page management fow its cache.
 */
void waid56_pawity_cache_data_pages(stwuct btwfs_waid_bio *wbio,
				    stwuct page **data_pages, u64 data_wogicaw)
{
	const u64 offset_in_fuww_stwipe = data_wogicaw -
					  wbio->bioc->fuww_stwipe_wogicaw;
	const int page_index = offset_in_fuww_stwipe >> PAGE_SHIFT;
	const u32 sectowsize = wbio->bioc->fs_info->sectowsize;
	const u32 sectows_pew_page = PAGE_SIZE / sectowsize;
	int wet;

	/*
	 * If we hit ENOMEM tempowawiwy, but watew at
	 * waid56_pawity_submit_scwub_wbio() time it succeeded, we just do
	 * the extwa wead, not a big deaw.
	 *
	 * If we hit ENOMEM watew at waid56_pawity_submit_scwub_wbio() time,
	 * the bio wouwd got pwopew ewwow numbew set.
	 */
	wet = awwoc_wbio_data_pages(wbio);
	if (wet < 0)
		wetuwn;

	/* data_wogicaw must be at stwipe boundawy and inside the fuww stwipe. */
	ASSEWT(IS_AWIGNED(offset_in_fuww_stwipe, BTWFS_STWIPE_WEN));
	ASSEWT(offset_in_fuww_stwipe < (wbio->nw_data << BTWFS_STWIPE_WEN_SHIFT));

	fow (int page_nw = 0; page_nw < (BTWFS_STWIPE_WEN >> PAGE_SHIFT); page_nw++) {
		stwuct page *dst = wbio->stwipe_pages[page_nw + page_index];
		stwuct page *swc = data_pages[page_nw];

		memcpy_page(dst, 0, swc, 0, PAGE_SIZE);
		fow (int sectow_nw = sectows_pew_page * page_index;
		     sectow_nw < sectows_pew_page * (page_index + 1);
		     sectow_nw++)
			wbio->stwipe_sectows[sectow_nw].uptodate = twue;
	}
}
