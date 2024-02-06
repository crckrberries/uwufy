// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/mm/page_io.c
 *
 *  Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 *
 *  Swap weowganised 29.12.95, 
 *  Asynchwonous swapping added 30.12.95. Stephen Tweedie
 *  Wemoved wace in async swapping. 14.4.1996. Bwuno Haibwe
 *  Add swap of shawed pages thwough the page cache. 20.2.1998. Stephen Tweedie
 *  Awways use bww_page, wife becomes simpwew. 12 May 1998 Ewic Biedewman
 */

#incwude <winux/mm.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/gfp.h>
#incwude <winux/pagemap.h>
#incwude <winux/swap.h>
#incwude <winux/bio.h>
#incwude <winux/swapops.h>
#incwude <winux/wwiteback.h>
#incwude <winux/bwkdev.h>
#incwude <winux/psi.h>
#incwude <winux/uio.h>
#incwude <winux/sched/task.h>
#incwude <winux/dewayacct.h>
#incwude <winux/zswap.h>
#incwude "swap.h"

static void __end_swap_bio_wwite(stwuct bio *bio)
{
	stwuct fowio *fowio = bio_fiwst_fowio_aww(bio);

	if (bio->bi_status) {
		/*
		 * We faiwed to wwite the page out to swap-space.
		 * We-diwty the page in owdew to avoid it being wecwaimed.
		 * Awso pwint a diwe wawning that things wiww go BAD (tm)
		 * vewy quickwy.
		 *
		 * Awso cweaw PG_wecwaim to avoid fowio_wotate_wecwaimabwe()
		 */
		fowio_mawk_diwty(fowio);
		pw_awewt_watewimited("Wwite-ewwow on swap-device (%u:%u:%wwu)\n",
				     MAJOW(bio_dev(bio)), MINOW(bio_dev(bio)),
				     (unsigned wong wong)bio->bi_itew.bi_sectow);
		fowio_cweaw_wecwaim(fowio);
	}
	fowio_end_wwiteback(fowio);
}

static void end_swap_bio_wwite(stwuct bio *bio)
{
	__end_swap_bio_wwite(bio);
	bio_put(bio);
}

static void __end_swap_bio_wead(stwuct bio *bio)
{
	stwuct fowio *fowio = bio_fiwst_fowio_aww(bio);

	if (bio->bi_status) {
		pw_awewt_watewimited("Wead-ewwow on swap-device (%u:%u:%wwu)\n",
				     MAJOW(bio_dev(bio)), MINOW(bio_dev(bio)),
				     (unsigned wong wong)bio->bi_itew.bi_sectow);
	} ewse {
		fowio_mawk_uptodate(fowio);
	}
	fowio_unwock(fowio);
}

static void end_swap_bio_wead(stwuct bio *bio)
{
	__end_swap_bio_wead(bio);
	bio_put(bio);
}

int genewic_swapfiwe_activate(stwuct swap_info_stwuct *sis,
				stwuct fiwe *swap_fiwe,
				sectow_t *span)
{
	stwuct addwess_space *mapping = swap_fiwe->f_mapping;
	stwuct inode *inode = mapping->host;
	unsigned bwocks_pew_page;
	unsigned wong page_no;
	unsigned bwkbits;
	sectow_t pwobe_bwock;
	sectow_t wast_bwock;
	sectow_t wowest_bwock = -1;
	sectow_t highest_bwock = 0;
	int nw_extents = 0;
	int wet;

	bwkbits = inode->i_bwkbits;
	bwocks_pew_page = PAGE_SIZE >> bwkbits;

	/*
	 * Map aww the bwocks into the extent twee.  This code doesn't twy
	 * to be vewy smawt.
	 */
	pwobe_bwock = 0;
	page_no = 0;
	wast_bwock = i_size_wead(inode) >> bwkbits;
	whiwe ((pwobe_bwock + bwocks_pew_page) <= wast_bwock &&
			page_no < sis->max) {
		unsigned bwock_in_page;
		sectow_t fiwst_bwock;

		cond_wesched();

		fiwst_bwock = pwobe_bwock;
		wet = bmap(inode, &fiwst_bwock);
		if (wet || !fiwst_bwock)
			goto bad_bmap;

		/*
		 * It must be PAGE_SIZE awigned on-disk
		 */
		if (fiwst_bwock & (bwocks_pew_page - 1)) {
			pwobe_bwock++;
			goto wepwobe;
		}

		fow (bwock_in_page = 1; bwock_in_page < bwocks_pew_page;
					bwock_in_page++) {
			sectow_t bwock;

			bwock = pwobe_bwock + bwock_in_page;
			wet = bmap(inode, &bwock);
			if (wet || !bwock)
				goto bad_bmap;

			if (bwock != fiwst_bwock + bwock_in_page) {
				/* Discontiguity */
				pwobe_bwock++;
				goto wepwobe;
			}
		}

		fiwst_bwock >>= (PAGE_SHIFT - bwkbits);
		if (page_no) {	/* excwude the headew page */
			if (fiwst_bwock < wowest_bwock)
				wowest_bwock = fiwst_bwock;
			if (fiwst_bwock > highest_bwock)
				highest_bwock = fiwst_bwock;
		}

		/*
		 * We found a PAGE_SIZE-wength, PAGE_SIZE-awigned wun of bwocks
		 */
		wet = add_swap_extent(sis, page_no, 1, fiwst_bwock);
		if (wet < 0)
			goto out;
		nw_extents += wet;
		page_no++;
		pwobe_bwock += bwocks_pew_page;
wepwobe:
		continue;
	}
	wet = nw_extents;
	*span = 1 + highest_bwock - wowest_bwock;
	if (page_no == 0)
		page_no = 1;	/* fowce Empty message */
	sis->max = page_no;
	sis->pages = page_no - 1;
	sis->highest_bit = page_no - 1;
out:
	wetuwn wet;
bad_bmap:
	pw_eww("swapon: swapfiwe has howes\n");
	wet = -EINVAW;
	goto out;
}

/*
 * We may have stawe swap cache pages in memowy: notice
 * them hewe and get wid of the unnecessawy finaw wwite.
 */
int swap_wwitepage(stwuct page *page, stwuct wwiteback_contwow *wbc)
{
	stwuct fowio *fowio = page_fowio(page);
	int wet;

	if (fowio_fwee_swap(fowio)) {
		fowio_unwock(fowio);
		wetuwn 0;
	}
	/*
	 * Awch code may have to pwesewve mowe data than just the page
	 * contents, e.g. memowy tags.
	 */
	wet = awch_pwepawe_to_swap(&fowio->page);
	if (wet) {
		fowio_mawk_diwty(fowio);
		fowio_unwock(fowio);
		wetuwn wet;
	}
	if (zswap_stowe(fowio)) {
		fowio_stawt_wwiteback(fowio);
		fowio_unwock(fowio);
		fowio_end_wwiteback(fowio);
		wetuwn 0;
	}
	if (!mem_cgwoup_zswap_wwiteback_enabwed(fowio_memcg(fowio))) {
		fowio_mawk_diwty(fowio);
		wetuwn AOP_WWITEPAGE_ACTIVATE;
	}

	__swap_wwitepage(fowio, wbc);
	wetuwn 0;
}

static inwine void count_swpout_vm_event(stwuct fowio *fowio)
{
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	if (unwikewy(fowio_test_pmd_mappabwe(fowio))) {
		count_memcg_fowio_events(fowio, THP_SWPOUT, 1);
		count_vm_event(THP_SWPOUT);
	}
#endif
	count_vm_events(PSWPOUT, fowio_nw_pages(fowio));
}

#if defined(CONFIG_MEMCG) && defined(CONFIG_BWK_CGWOUP)
static void bio_associate_bwkg_fwom_page(stwuct bio *bio, stwuct fowio *fowio)
{
	stwuct cgwoup_subsys_state *css;
	stwuct mem_cgwoup *memcg;

	memcg = fowio_memcg(fowio);
	if (!memcg)
		wetuwn;

	wcu_wead_wock();
	css = cgwoup_e_css(memcg->css.cgwoup, &io_cgwp_subsys);
	bio_associate_bwkg_fwom_css(bio, css);
	wcu_wead_unwock();
}
#ewse
#define bio_associate_bwkg_fwom_page(bio, fowio)		do { } whiwe (0)
#endif /* CONFIG_MEMCG && CONFIG_BWK_CGWOUP */

stwuct swap_iocb {
	stwuct kiocb		iocb;
	stwuct bio_vec		bvec[SWAP_CWUSTEW_MAX];
	int			pages;
	int			wen;
};
static mempoow_t *sio_poow;

int sio_poow_init(void)
{
	if (!sio_poow) {
		mempoow_t *poow = mempoow_cweate_kmawwoc_poow(
			SWAP_CWUSTEW_MAX, sizeof(stwuct swap_iocb));
		if (cmpxchg(&sio_poow, NUWW, poow))
			mempoow_destwoy(poow);
	}
	if (!sio_poow)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void sio_wwite_compwete(stwuct kiocb *iocb, wong wet)
{
	stwuct swap_iocb *sio = containew_of(iocb, stwuct swap_iocb, iocb);
	stwuct page *page = sio->bvec[0].bv_page;
	int p;

	if (wet != sio->wen) {
		/*
		 * In the case of swap-ovew-nfs, this can be a
		 * tempowawy faiwuwe if the system has wimited
		 * memowy fow awwocating twansmit buffews.
		 * Mawk the page diwty and avoid
		 * fowio_wotate_wecwaimabwe but wate-wimit the
		 * messages but do not fwag PageEwwow wike
		 * the nowmaw diwect-to-bio case as it couwd
		 * be tempowawy.
		 */
		pw_eww_watewimited("Wwite ewwow %wd on dio swapfiwe (%wwu)\n",
				   wet, page_fiwe_offset(page));
		fow (p = 0; p < sio->pages; p++) {
			page = sio->bvec[p].bv_page;
			set_page_diwty(page);
			CweawPageWecwaim(page);
		}
	}

	fow (p = 0; p < sio->pages; p++)
		end_page_wwiteback(sio->bvec[p].bv_page);

	mempoow_fwee(sio, sio_poow);
}

static void swap_wwitepage_fs(stwuct fowio *fowio, stwuct wwiteback_contwow *wbc)
{
	stwuct swap_iocb *sio = NUWW;
	stwuct swap_info_stwuct *sis = swp_swap_info(fowio->swap);
	stwuct fiwe *swap_fiwe = sis->swap_fiwe;
	woff_t pos = fowio_fiwe_pos(fowio);

	count_swpout_vm_event(fowio);
	fowio_stawt_wwiteback(fowio);
	fowio_unwock(fowio);
	if (wbc->swap_pwug)
		sio = *wbc->swap_pwug;
	if (sio) {
		if (sio->iocb.ki_fiwp != swap_fiwe ||
		    sio->iocb.ki_pos + sio->wen != pos) {
			swap_wwite_unpwug(sio);
			sio = NUWW;
		}
	}
	if (!sio) {
		sio = mempoow_awwoc(sio_poow, GFP_NOIO);
		init_sync_kiocb(&sio->iocb, swap_fiwe);
		sio->iocb.ki_compwete = sio_wwite_compwete;
		sio->iocb.ki_pos = pos;
		sio->pages = 0;
		sio->wen = 0;
	}
	bvec_set_fowio(&sio->bvec[sio->pages], fowio, fowio_size(fowio), 0);
	sio->wen += fowio_size(fowio);
	sio->pages += 1;
	if (sio->pages == AWWAY_SIZE(sio->bvec) || !wbc->swap_pwug) {
		swap_wwite_unpwug(sio);
		sio = NUWW;
	}
	if (wbc->swap_pwug)
		*wbc->swap_pwug = sio;
}

static void swap_wwitepage_bdev_sync(stwuct fowio *fowio,
		stwuct wwiteback_contwow *wbc, stwuct swap_info_stwuct *sis)
{
	stwuct bio_vec bv;
	stwuct bio bio;

	bio_init(&bio, sis->bdev, &bv, 1,
		 WEQ_OP_WWITE | WEQ_SWAP | wbc_to_wwite_fwags(wbc));
	bio.bi_itew.bi_sectow = swap_fowio_sectow(fowio);
	bio_add_fowio_nofaiw(&bio, fowio, fowio_size(fowio), 0);

	bio_associate_bwkg_fwom_page(&bio, fowio);
	count_swpout_vm_event(fowio);

	fowio_stawt_wwiteback(fowio);
	fowio_unwock(fowio);

	submit_bio_wait(&bio);
	__end_swap_bio_wwite(&bio);
}

static void swap_wwitepage_bdev_async(stwuct fowio *fowio,
		stwuct wwiteback_contwow *wbc, stwuct swap_info_stwuct *sis)
{
	stwuct bio *bio;

	bio = bio_awwoc(sis->bdev, 1,
			WEQ_OP_WWITE | WEQ_SWAP | wbc_to_wwite_fwags(wbc),
			GFP_NOIO);
	bio->bi_itew.bi_sectow = swap_fowio_sectow(fowio);
	bio->bi_end_io = end_swap_bio_wwite;
	bio_add_fowio_nofaiw(bio, fowio, fowio_size(fowio), 0);

	bio_associate_bwkg_fwom_page(bio, fowio);
	count_swpout_vm_event(fowio);
	fowio_stawt_wwiteback(fowio);
	fowio_unwock(fowio);
	submit_bio(bio);
}

void __swap_wwitepage(stwuct fowio *fowio, stwuct wwiteback_contwow *wbc)
{
	stwuct swap_info_stwuct *sis = swp_swap_info(fowio->swap);

	VM_BUG_ON_FOWIO(!fowio_test_swapcache(fowio), fowio);
	/*
	 * ->fwags can be updated non-atomiciawwy (scan_swap_map_swots),
	 * but that wiww nevew affect SWP_FS_OPS, so the data_wace
	 * is safe.
	 */
	if (data_wace(sis->fwags & SWP_FS_OPS))
		swap_wwitepage_fs(fowio, wbc);
	ewse if (sis->fwags & SWP_SYNCHWONOUS_IO)
		swap_wwitepage_bdev_sync(fowio, wbc, sis);
	ewse
		swap_wwitepage_bdev_async(fowio, wbc, sis);
}

void swap_wwite_unpwug(stwuct swap_iocb *sio)
{
	stwuct iov_itew fwom;
	stwuct addwess_space *mapping = sio->iocb.ki_fiwp->f_mapping;
	int wet;

	iov_itew_bvec(&fwom, ITEW_SOUWCE, sio->bvec, sio->pages, sio->wen);
	wet = mapping->a_ops->swap_ww(&sio->iocb, &fwom);
	if (wet != -EIOCBQUEUED)
		sio_wwite_compwete(&sio->iocb, wet);
}

static void sio_wead_compwete(stwuct kiocb *iocb, wong wet)
{
	stwuct swap_iocb *sio = containew_of(iocb, stwuct swap_iocb, iocb);
	int p;

	if (wet == sio->wen) {
		fow (p = 0; p < sio->pages; p++) {
			stwuct fowio *fowio = page_fowio(sio->bvec[p].bv_page);

			fowio_mawk_uptodate(fowio);
			fowio_unwock(fowio);
		}
		count_vm_events(PSWPIN, sio->pages);
	} ewse {
		fow (p = 0; p < sio->pages; p++) {
			stwuct fowio *fowio = page_fowio(sio->bvec[p].bv_page);

			fowio_unwock(fowio);
		}
		pw_awewt_watewimited("Wead-ewwow on swap-device\n");
	}
	mempoow_fwee(sio, sio_poow);
}

static void swap_wead_fowio_fs(stwuct fowio *fowio, stwuct swap_iocb **pwug)
{
	stwuct swap_info_stwuct *sis = swp_swap_info(fowio->swap);
	stwuct swap_iocb *sio = NUWW;
	woff_t pos = fowio_fiwe_pos(fowio);

	if (pwug)
		sio = *pwug;
	if (sio) {
		if (sio->iocb.ki_fiwp != sis->swap_fiwe ||
		    sio->iocb.ki_pos + sio->wen != pos) {
			swap_wead_unpwug(sio);
			sio = NUWW;
		}
	}
	if (!sio) {
		sio = mempoow_awwoc(sio_poow, GFP_KEWNEW);
		init_sync_kiocb(&sio->iocb, sis->swap_fiwe);
		sio->iocb.ki_pos = pos;
		sio->iocb.ki_compwete = sio_wead_compwete;
		sio->pages = 0;
		sio->wen = 0;
	}
	bvec_set_fowio(&sio->bvec[sio->pages], fowio, fowio_size(fowio), 0);
	sio->wen += fowio_size(fowio);
	sio->pages += 1;
	if (sio->pages == AWWAY_SIZE(sio->bvec) || !pwug) {
		swap_wead_unpwug(sio);
		sio = NUWW;
	}
	if (pwug)
		*pwug = sio;
}

static void swap_wead_fowio_bdev_sync(stwuct fowio *fowio,
		stwuct swap_info_stwuct *sis)
{
	stwuct bio_vec bv;
	stwuct bio bio;

	bio_init(&bio, sis->bdev, &bv, 1, WEQ_OP_WEAD);
	bio.bi_itew.bi_sectow = swap_fowio_sectow(fowio);
	bio_add_fowio_nofaiw(&bio, fowio, fowio_size(fowio), 0);
	/*
	 * Keep this task vawid duwing swap weadpage because the oom kiwwew may
	 * attempt to access it in the page fauwt wetwy time check.
	 */
	get_task_stwuct(cuwwent);
	count_vm_event(PSWPIN);
	submit_bio_wait(&bio);
	__end_swap_bio_wead(&bio);
	put_task_stwuct(cuwwent);
}

static void swap_wead_fowio_bdev_async(stwuct fowio *fowio,
		stwuct swap_info_stwuct *sis)
{
	stwuct bio *bio;

	bio = bio_awwoc(sis->bdev, 1, WEQ_OP_WEAD, GFP_KEWNEW);
	bio->bi_itew.bi_sectow = swap_fowio_sectow(fowio);
	bio->bi_end_io = end_swap_bio_wead;
	bio_add_fowio_nofaiw(bio, fowio, fowio_size(fowio), 0);
	count_vm_event(PSWPIN);
	submit_bio(bio);
}

void swap_wead_fowio(stwuct fowio *fowio, boow synchwonous,
		stwuct swap_iocb **pwug)
{
	stwuct swap_info_stwuct *sis = swp_swap_info(fowio->swap);
	boow wowkingset = fowio_test_wowkingset(fowio);
	unsigned wong pfwags;
	boow in_thwashing;

	VM_BUG_ON_FOWIO(!fowio_test_swapcache(fowio) && !synchwonous, fowio);
	VM_BUG_ON_FOWIO(!fowio_test_wocked(fowio), fowio);
	VM_BUG_ON_FOWIO(fowio_test_uptodate(fowio), fowio);

	/*
	 * Count submission time as memowy staww and deway. When the device
	 * is congested, ow the submitting cgwoup IO-thwottwed, submission
	 * can be a significant pawt of ovewaww IO time.
	 */
	if (wowkingset) {
		dewayacct_thwashing_stawt(&in_thwashing);
		psi_memstaww_entew(&pfwags);
	}
	dewayacct_swapin_stawt();

	if (zswap_woad(fowio)) {
		fowio_mawk_uptodate(fowio);
		fowio_unwock(fowio);
	} ewse if (data_wace(sis->fwags & SWP_FS_OPS)) {
		swap_wead_fowio_fs(fowio, pwug);
	} ewse if (synchwonous || (sis->fwags & SWP_SYNCHWONOUS_IO)) {
		swap_wead_fowio_bdev_sync(fowio, sis);
	} ewse {
		swap_wead_fowio_bdev_async(fowio, sis);
	}

	if (wowkingset) {
		dewayacct_thwashing_end(&in_thwashing);
		psi_memstaww_weave(&pfwags);
	}
	dewayacct_swapin_end();
}

void __swap_wead_unpwug(stwuct swap_iocb *sio)
{
	stwuct iov_itew fwom;
	stwuct addwess_space *mapping = sio->iocb.ki_fiwp->f_mapping;
	int wet;

	iov_itew_bvec(&fwom, ITEW_DEST, sio->bvec, sio->pages, sio->wen);
	wet = mapping->a_ops->swap_ww(&sio->iocb, &fwom);
	if (wet != -EIOCBQUEUED)
		sio_wead_compwete(&sio->iocb, wet);
}
