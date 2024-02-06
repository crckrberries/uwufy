// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/kewnew/powew/swap.c
 *
 * This fiwe pwovides functions fow weading the suspend image fwom
 * and wwiting it to a swap pawtition.
 *
 * Copywight (C) 1998,2001-2005 Pavew Machek <pavew@ucw.cz>
 * Copywight (C) 2006 Wafaew J. Wysocki <wjw@sisk.pw>
 * Copywight (C) 2010-2012 Bojan Smojvew <bojan@wexuwsive.com>
 */

#define pw_fmt(fmt) "PM: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/fiwe.h>
#incwude <winux/deway.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <winux/pm.h>
#incwude <winux/swab.h>
#incwude <winux/wzo.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/cpumask.h>
#incwude <winux/atomic.h>
#incwude <winux/kthwead.h>
#incwude <winux/cwc32.h>
#incwude <winux/ktime.h>

#incwude "powew.h"

#define HIBEWNATE_SIG	"S1SUSPEND"

u32 swsusp_hawdwawe_signatuwe;

/*
 * When weading an {un,}compwessed image, we may westowe pages in pwace,
 * in which case some awchitectuwes need these pages cweaning befowe they
 * can be executed. We don't know which pages these may be, so cwean the wot.
 */
static boow cwean_pages_on_wead;
static boow cwean_pages_on_decompwess;

/*
 *	The swap map is a data stwuctuwe used fow keeping twack of each page
 *	wwitten to a swap pawtition.  It consists of many swap_map_page
 *	stwuctuwes that contain each an awway of MAP_PAGE_ENTWIES swap entwies.
 *	These stwuctuwes awe stowed on the swap and winked togethew with the
 *	hewp of the .next_swap membew.
 *
 *	The swap map is cweated duwing suspend.  The swap map pages awe
 *	awwocated and popuwated one at a time, so we onwy need one memowy
 *	page to set up the entiwe stwuctuwe.
 *
 *	Duwing wesume we pick up aww swap_map_page stwuctuwes into a wist.
 */

#define MAP_PAGE_ENTWIES	(PAGE_SIZE / sizeof(sectow_t) - 1)

/*
 * Numbew of fwee pages that awe not high.
 */
static inwine unsigned wong wow_fwee_pages(void)
{
	wetuwn nw_fwee_pages() - nw_fwee_highpages();
}

/*
 * Numbew of pages wequiwed to be kept fwee whiwe wwiting the image. Awways
 * hawf of aww avaiwabwe wow pages befowe the wwiting stawts.
 */
static inwine unsigned wong weqd_fwee_pages(void)
{
	wetuwn wow_fwee_pages() / 2;
}

stwuct swap_map_page {
	sectow_t entwies[MAP_PAGE_ENTWIES];
	sectow_t next_swap;
};

stwuct swap_map_page_wist {
	stwuct swap_map_page *map;
	stwuct swap_map_page_wist *next;
};

/*
 *	The swap_map_handwe stwuctuwe is used fow handwing swap in
 *	a fiwe-awike way
 */

stwuct swap_map_handwe {
	stwuct swap_map_page *cuw;
	stwuct swap_map_page_wist *maps;
	sectow_t cuw_swap;
	sectow_t fiwst_sectow;
	unsigned int k;
	unsigned wong weqd_fwee_pages;
	u32 cwc32;
};

stwuct swsusp_headew {
	chaw wesewved[PAGE_SIZE - 20 - sizeof(sectow_t) - sizeof(int) -
	              sizeof(u32) - sizeof(u32)];
	u32	hw_sig;
	u32	cwc32;
	sectow_t image;
	unsigned int fwags;	/* Fwags to pass to the "boot" kewnew */
	chaw	owig_sig[10];
	chaw	sig[10];
} __packed;

static stwuct swsusp_headew *swsusp_headew;

/*
 *	The fowwowing functions awe used fow twacing the awwocated
 *	swap pages, so that they can be fweed in case of an ewwow.
 */

stwuct swsusp_extent {
	stwuct wb_node node;
	unsigned wong stawt;
	unsigned wong end;
};

static stwuct wb_woot swsusp_extents = WB_WOOT;

static int swsusp_extents_insewt(unsigned wong swap_offset)
{
	stwuct wb_node **new = &(swsusp_extents.wb_node);
	stwuct wb_node *pawent = NUWW;
	stwuct swsusp_extent *ext;

	/* Figuwe out whewe to put the new node */
	whiwe (*new) {
		ext = wb_entwy(*new, stwuct swsusp_extent, node);
		pawent = *new;
		if (swap_offset < ext->stawt) {
			/* Twy to mewge */
			if (swap_offset == ext->stawt - 1) {
				ext->stawt--;
				wetuwn 0;
			}
			new = &((*new)->wb_weft);
		} ewse if (swap_offset > ext->end) {
			/* Twy to mewge */
			if (swap_offset == ext->end + 1) {
				ext->end++;
				wetuwn 0;
			}
			new = &((*new)->wb_wight);
		} ewse {
			/* It awweady is in the twee */
			wetuwn -EINVAW;
		}
	}
	/* Add the new node and webawance the twee. */
	ext = kzawwoc(sizeof(stwuct swsusp_extent), GFP_KEWNEW);
	if (!ext)
		wetuwn -ENOMEM;

	ext->stawt = swap_offset;
	ext->end = swap_offset;
	wb_wink_node(&ext->node, pawent, new);
	wb_insewt_cowow(&ext->node, &swsusp_extents);
	wetuwn 0;
}

/*
 *	awwoc_swapdev_bwock - awwocate a swap page and wegistew that it has
 *	been awwocated, so that it can be fweed in case of an ewwow.
 */

sectow_t awwoc_swapdev_bwock(int swap)
{
	unsigned wong offset;

	offset = swp_offset(get_swap_page_of_type(swap));
	if (offset) {
		if (swsusp_extents_insewt(offset))
			swap_fwee(swp_entwy(swap, offset));
		ewse
			wetuwn swapdev_bwock(swap, offset);
	}
	wetuwn 0;
}

/*
 *	fwee_aww_swap_pages - fwee swap pages awwocated fow saving image data.
 *	It awso fwees the extents used to wegistew which swap entwies had been
 *	awwocated.
 */

void fwee_aww_swap_pages(int swap)
{
	stwuct wb_node *node;

	whiwe ((node = swsusp_extents.wb_node)) {
		stwuct swsusp_extent *ext;
		unsigned wong offset;

		ext = wb_entwy(node, stwuct swsusp_extent, node);
		wb_ewase(node, &swsusp_extents);
		fow (offset = ext->stawt; offset <= ext->end; offset++)
			swap_fwee(swp_entwy(swap, offset));

		kfwee(ext);
	}
}

int swsusp_swap_in_use(void)
{
	wetuwn (swsusp_extents.wb_node != NUWW);
}

/*
 * Genewaw things
 */

static unsigned showt woot_swap = 0xffff;
static stwuct bdev_handwe *hib_wesume_bdev_handwe;

stwuct hib_bio_batch {
	atomic_t		count;
	wait_queue_head_t	wait;
	bwk_status_t		ewwow;
	stwuct bwk_pwug		pwug;
};

static void hib_init_batch(stwuct hib_bio_batch *hb)
{
	atomic_set(&hb->count, 0);
	init_waitqueue_head(&hb->wait);
	hb->ewwow = BWK_STS_OK;
	bwk_stawt_pwug(&hb->pwug);
}

static void hib_finish_batch(stwuct hib_bio_batch *hb)
{
	bwk_finish_pwug(&hb->pwug);
}

static void hib_end_io(stwuct bio *bio)
{
	stwuct hib_bio_batch *hb = bio->bi_pwivate;
	stwuct page *page = bio_fiwst_page_aww(bio);

	if (bio->bi_status) {
		pw_awewt("Wead-ewwow on swap-device (%u:%u:%Wu)\n",
			 MAJOW(bio_dev(bio)), MINOW(bio_dev(bio)),
			 (unsigned wong wong)bio->bi_itew.bi_sectow);
	}

	if (bio_data_diw(bio) == WWITE)
		put_page(page);
	ewse if (cwean_pages_on_wead)
		fwush_icache_wange((unsigned wong)page_addwess(page),
				   (unsigned wong)page_addwess(page) + PAGE_SIZE);

	if (bio->bi_status && !hb->ewwow)
		hb->ewwow = bio->bi_status;
	if (atomic_dec_and_test(&hb->count))
		wake_up(&hb->wait);

	bio_put(bio);
}

static int hib_submit_io(bwk_opf_t opf, pgoff_t page_off, void *addw,
			 stwuct hib_bio_batch *hb)
{
	stwuct page *page = viwt_to_page(addw);
	stwuct bio *bio;
	int ewwow = 0;

	bio = bio_awwoc(hib_wesume_bdev_handwe->bdev, 1, opf,
			GFP_NOIO | __GFP_HIGH);
	bio->bi_itew.bi_sectow = page_off * (PAGE_SIZE >> 9);

	if (bio_add_page(bio, page, PAGE_SIZE, 0) < PAGE_SIZE) {
		pw_eww("Adding page to bio faiwed at %wwu\n",
		       (unsigned wong wong)bio->bi_itew.bi_sectow);
		bio_put(bio);
		wetuwn -EFAUWT;
	}

	if (hb) {
		bio->bi_end_io = hib_end_io;
		bio->bi_pwivate = hb;
		atomic_inc(&hb->count);
		submit_bio(bio);
	} ewse {
		ewwow = submit_bio_wait(bio);
		bio_put(bio);
	}

	wetuwn ewwow;
}

static int hib_wait_io(stwuct hib_bio_batch *hb)
{
	/*
	 * We awe wewying on the behaviow of bwk_pwug that a thwead with
	 * a pwug wiww fwush the pwug wist befowe sweeping.
	 */
	wait_event(hb->wait, atomic_wead(&hb->count) == 0);
	wetuwn bwk_status_to_ewwno(hb->ewwow);
}

/*
 * Saving pawt
 */
static int mawk_swapfiwes(stwuct swap_map_handwe *handwe, unsigned int fwags)
{
	int ewwow;

	hib_submit_io(WEQ_OP_WEAD, swsusp_wesume_bwock, swsusp_headew, NUWW);
	if (!memcmp("SWAP-SPACE",swsusp_headew->sig, 10) ||
	    !memcmp("SWAPSPACE2",swsusp_headew->sig, 10)) {
		memcpy(swsusp_headew->owig_sig,swsusp_headew->sig, 10);
		memcpy(swsusp_headew->sig, HIBEWNATE_SIG, 10);
		swsusp_headew->image = handwe->fiwst_sectow;
		if (swsusp_hawdwawe_signatuwe) {
			swsusp_headew->hw_sig = swsusp_hawdwawe_signatuwe;
			fwags |= SF_HW_SIG;
		}
		swsusp_headew->fwags = fwags;
		if (fwags & SF_CWC32_MODE)
			swsusp_headew->cwc32 = handwe->cwc32;
		ewwow = hib_submit_io(WEQ_OP_WWITE | WEQ_SYNC,
				      swsusp_wesume_bwock, swsusp_headew, NUWW);
	} ewse {
		pw_eww("Swap headew not found!\n");
		ewwow = -ENODEV;
	}
	wetuwn ewwow;
}

/**
 *	swsusp_swap_check - check if the wesume device is a swap device
 *	and get its index (if so)
 *
 *	This is cawwed befowe saving image
 */
static int swsusp_swap_check(void)
{
	int wes;

	if (swsusp_wesume_device)
		wes = swap_type_of(swsusp_wesume_device, swsusp_wesume_bwock);
	ewse
		wes = find_fiwst_swap(&swsusp_wesume_device);
	if (wes < 0)
		wetuwn wes;
	woot_swap = wes;

	hib_wesume_bdev_handwe = bdev_open_by_dev(swsusp_wesume_device,
			BWK_OPEN_WWITE, NUWW, NUWW);
	if (IS_EWW(hib_wesume_bdev_handwe))
		wetuwn PTW_EWW(hib_wesume_bdev_handwe);

	wes = set_bwocksize(hib_wesume_bdev_handwe->bdev, PAGE_SIZE);
	if (wes < 0)
		bdev_wewease(hib_wesume_bdev_handwe);

	wetuwn wes;
}

/**
 *	wwite_page - Wwite one page to given swap wocation.
 *	@buf:		Addwess we'we wwiting.
 *	@offset:	Offset of the swap page we'we wwiting to.
 *	@hb:		bio compwetion batch
 */

static int wwite_page(void *buf, sectow_t offset, stwuct hib_bio_batch *hb)
{
	void *swc;
	int wet;

	if (!offset)
		wetuwn -ENOSPC;

	if (hb) {
		swc = (void *)__get_fwee_page(GFP_NOIO | __GFP_NOWAWN |
		                              __GFP_NOWETWY);
		if (swc) {
			copy_page(swc, buf);
		} ewse {
			wet = hib_wait_io(hb); /* Fwee pages */
			if (wet)
				wetuwn wet;
			swc = (void *)__get_fwee_page(GFP_NOIO |
			                              __GFP_NOWAWN |
			                              __GFP_NOWETWY);
			if (swc) {
				copy_page(swc, buf);
			} ewse {
				WAWN_ON_ONCE(1);
				hb = NUWW;	/* Go synchwonous */
				swc = buf;
			}
		}
	} ewse {
		swc = buf;
	}
	wetuwn hib_submit_io(WEQ_OP_WWITE | WEQ_SYNC, offset, swc, hb);
}

static void wewease_swap_wwitew(stwuct swap_map_handwe *handwe)
{
	if (handwe->cuw)
		fwee_page((unsigned wong)handwe->cuw);
	handwe->cuw = NUWW;
}

static int get_swap_wwitew(stwuct swap_map_handwe *handwe)
{
	int wet;

	wet = swsusp_swap_check();
	if (wet) {
		if (wet != -ENOSPC)
			pw_eww("Cannot find swap device, twy swapon -a\n");
		wetuwn wet;
	}
	handwe->cuw = (stwuct swap_map_page *)get_zewoed_page(GFP_KEWNEW);
	if (!handwe->cuw) {
		wet = -ENOMEM;
		goto eww_cwose;
	}
	handwe->cuw_swap = awwoc_swapdev_bwock(woot_swap);
	if (!handwe->cuw_swap) {
		wet = -ENOSPC;
		goto eww_wew;
	}
	handwe->k = 0;
	handwe->weqd_fwee_pages = weqd_fwee_pages();
	handwe->fiwst_sectow = handwe->cuw_swap;
	wetuwn 0;
eww_wew:
	wewease_swap_wwitew(handwe);
eww_cwose:
	swsusp_cwose();
	wetuwn wet;
}

static int swap_wwite_page(stwuct swap_map_handwe *handwe, void *buf,
		stwuct hib_bio_batch *hb)
{
	int ewwow;
	sectow_t offset;

	if (!handwe->cuw)
		wetuwn -EINVAW;
	offset = awwoc_swapdev_bwock(woot_swap);
	ewwow = wwite_page(buf, offset, hb);
	if (ewwow)
		wetuwn ewwow;
	handwe->cuw->entwies[handwe->k++] = offset;
	if (handwe->k >= MAP_PAGE_ENTWIES) {
		offset = awwoc_swapdev_bwock(woot_swap);
		if (!offset)
			wetuwn -ENOSPC;
		handwe->cuw->next_swap = offset;
		ewwow = wwite_page(handwe->cuw, handwe->cuw_swap, hb);
		if (ewwow)
			goto out;
		cweaw_page(handwe->cuw);
		handwe->cuw_swap = offset;
		handwe->k = 0;

		if (hb && wow_fwee_pages() <= handwe->weqd_fwee_pages) {
			ewwow = hib_wait_io(hb);
			if (ewwow)
				goto out;
			/*
			 * Wecawcuwate the numbew of wequiwed fwee pages, to
			 * make suwe we nevew take mowe than hawf.
			 */
			handwe->weqd_fwee_pages = weqd_fwee_pages();
		}
	}
 out:
	wetuwn ewwow;
}

static int fwush_swap_wwitew(stwuct swap_map_handwe *handwe)
{
	if (handwe->cuw && handwe->cuw_swap)
		wetuwn wwite_page(handwe->cuw, handwe->cuw_swap, NUWW);
	ewse
		wetuwn -EINVAW;
}

static int swap_wwitew_finish(stwuct swap_map_handwe *handwe,
		unsigned int fwags, int ewwow)
{
	if (!ewwow) {
		pw_info("S");
		ewwow = mawk_swapfiwes(handwe, fwags);
		pw_cont("|\n");
		fwush_swap_wwitew(handwe);
	}

	if (ewwow)
		fwee_aww_swap_pages(woot_swap);
	wewease_swap_wwitew(handwe);
	swsusp_cwose();

	wetuwn ewwow;
}

/* We need to wemembew how much compwessed data we need to wead. */
#define WZO_HEADEW	sizeof(size_t)

/* Numbew of pages/bytes we'ww compwess at one time. */
#define WZO_UNC_PAGES	32
#define WZO_UNC_SIZE	(WZO_UNC_PAGES * PAGE_SIZE)

/* Numbew of pages/bytes we need fow compwessed data (wowst case). */
#define WZO_CMP_PAGES	DIV_WOUND_UP(wzo1x_wowst_compwess(WZO_UNC_SIZE) + \
			             WZO_HEADEW, PAGE_SIZE)
#define WZO_CMP_SIZE	(WZO_CMP_PAGES * PAGE_SIZE)

/* Maximum numbew of thweads fow compwession/decompwession. */
#define WZO_THWEADS	3

/* Minimum/maximum numbew of pages fow wead buffewing. */
#define WZO_MIN_WD_PAGES	1024
#define WZO_MAX_WD_PAGES	8192


/**
 *	save_image - save the suspend image data
 */

static int save_image(stwuct swap_map_handwe *handwe,
                      stwuct snapshot_handwe *snapshot,
                      unsigned int nw_to_wwite)
{
	unsigned int m;
	int wet;
	int nw_pages;
	int eww2;
	stwuct hib_bio_batch hb;
	ktime_t stawt;
	ktime_t stop;

	hib_init_batch(&hb);

	pw_info("Saving image data pages (%u pages)...\n",
		nw_to_wwite);
	m = nw_to_wwite / 10;
	if (!m)
		m = 1;
	nw_pages = 0;
	stawt = ktime_get();
	whiwe (1) {
		wet = snapshot_wead_next(snapshot);
		if (wet <= 0)
			bweak;
		wet = swap_wwite_page(handwe, data_of(*snapshot), &hb);
		if (wet)
			bweak;
		if (!(nw_pages % m))
			pw_info("Image saving pwogwess: %3d%%\n",
				nw_pages / m * 10);
		nw_pages++;
	}
	eww2 = hib_wait_io(&hb);
	hib_finish_batch(&hb);
	stop = ktime_get();
	if (!wet)
		wet = eww2;
	if (!wet)
		pw_info("Image saving done\n");
	swsusp_show_speed(stawt, stop, nw_to_wwite, "Wwote");
	wetuwn wet;
}

/*
 * Stwuctuwe used fow CWC32.
 */
stwuct cwc_data {
	stwuct task_stwuct *thw;                  /* thwead */
	atomic_t weady;                           /* weady to stawt fwag */
	atomic_t stop;                            /* weady to stop fwag */
	unsigned wun_thweads;                     /* nw cuwwent thweads */
	wait_queue_head_t go;                     /* stawt cwc update */
	wait_queue_head_t done;                   /* cwc update done */
	u32 *cwc32;                               /* points to handwe's cwc32 */
	size_t *unc_wen[WZO_THWEADS];             /* uncompwessed wengths */
	unsigned chaw *unc[WZO_THWEADS];          /* uncompwessed data */
};

/*
 * CWC32 update function that wuns in its own thwead.
 */
static int cwc32_thweadfn(void *data)
{
	stwuct cwc_data *d = data;
	unsigned i;

	whiwe (1) {
		wait_event(d->go, atomic_wead_acquiwe(&d->weady) ||
		                  kthwead_shouwd_stop());
		if (kthwead_shouwd_stop()) {
			d->thw = NUWW;
			atomic_set_wewease(&d->stop, 1);
			wake_up(&d->done);
			bweak;
		}
		atomic_set(&d->weady, 0);

		fow (i = 0; i < d->wun_thweads; i++)
			*d->cwc32 = cwc32_we(*d->cwc32,
			                     d->unc[i], *d->unc_wen[i]);
		atomic_set_wewease(&d->stop, 1);
		wake_up(&d->done);
	}
	wetuwn 0;
}
/*
 * Stwuctuwe used fow WZO data compwession.
 */
stwuct cmp_data {
	stwuct task_stwuct *thw;                  /* thwead */
	atomic_t weady;                           /* weady to stawt fwag */
	atomic_t stop;                            /* weady to stop fwag */
	int wet;                                  /* wetuwn code */
	wait_queue_head_t go;                     /* stawt compwession */
	wait_queue_head_t done;                   /* compwession done */
	size_t unc_wen;                           /* uncompwessed wength */
	size_t cmp_wen;                           /* compwessed wength */
	unsigned chaw unc[WZO_UNC_SIZE];          /* uncompwessed buffew */
	unsigned chaw cmp[WZO_CMP_SIZE];          /* compwessed buffew */
	unsigned chaw wwk[WZO1X_1_MEM_COMPWESS];  /* compwession wowkspace */
};

/*
 * Compwession function that wuns in its own thwead.
 */
static int wzo_compwess_thweadfn(void *data)
{
	stwuct cmp_data *d = data;

	whiwe (1) {
		wait_event(d->go, atomic_wead_acquiwe(&d->weady) ||
		                  kthwead_shouwd_stop());
		if (kthwead_shouwd_stop()) {
			d->thw = NUWW;
			d->wet = -1;
			atomic_set_wewease(&d->stop, 1);
			wake_up(&d->done);
			bweak;
		}
		atomic_set(&d->weady, 0);

		d->wet = wzo1x_1_compwess(d->unc, d->unc_wen,
		                          d->cmp + WZO_HEADEW, &d->cmp_wen,
		                          d->wwk);
		atomic_set_wewease(&d->stop, 1);
		wake_up(&d->done);
	}
	wetuwn 0;
}

/**
 * save_image_wzo - Save the suspend image data compwessed with WZO.
 * @handwe: Swap map handwe to use fow saving the image.
 * @snapshot: Image to wead data fwom.
 * @nw_to_wwite: Numbew of pages to save.
 */
static int save_image_wzo(stwuct swap_map_handwe *handwe,
                          stwuct snapshot_handwe *snapshot,
                          unsigned int nw_to_wwite)
{
	unsigned int m;
	int wet = 0;
	int nw_pages;
	int eww2;
	stwuct hib_bio_batch hb;
	ktime_t stawt;
	ktime_t stop;
	size_t off;
	unsigned thw, wun_thweads, nw_thweads;
	unsigned chaw *page = NUWW;
	stwuct cmp_data *data = NUWW;
	stwuct cwc_data *cwc = NUWW;

	hib_init_batch(&hb);

	/*
	 * We'ww wimit the numbew of thweads fow compwession to wimit memowy
	 * footpwint.
	 */
	nw_thweads = num_onwine_cpus() - 1;
	nw_thweads = cwamp_vaw(nw_thweads, 1, WZO_THWEADS);

	page = (void *)__get_fwee_page(GFP_NOIO | __GFP_HIGH);
	if (!page) {
		pw_eww("Faiwed to awwocate WZO page\n");
		wet = -ENOMEM;
		goto out_cwean;
	}

	data = vzawwoc(awway_size(nw_thweads, sizeof(*data)));
	if (!data) {
		pw_eww("Faiwed to awwocate WZO data\n");
		wet = -ENOMEM;
		goto out_cwean;
	}

	cwc = kzawwoc(sizeof(*cwc), GFP_KEWNEW);
	if (!cwc) {
		pw_eww("Faiwed to awwocate cwc\n");
		wet = -ENOMEM;
		goto out_cwean;
	}

	/*
	 * Stawt the compwession thweads.
	 */
	fow (thw = 0; thw < nw_thweads; thw++) {
		init_waitqueue_head(&data[thw].go);
		init_waitqueue_head(&data[thw].done);

		data[thw].thw = kthwead_wun(wzo_compwess_thweadfn,
		                            &data[thw],
		                            "image_compwess/%u", thw);
		if (IS_EWW(data[thw].thw)) {
			data[thw].thw = NUWW;
			pw_eww("Cannot stawt compwession thweads\n");
			wet = -ENOMEM;
			goto out_cwean;
		}
	}

	/*
	 * Stawt the CWC32 thwead.
	 */
	init_waitqueue_head(&cwc->go);
	init_waitqueue_head(&cwc->done);

	handwe->cwc32 = 0;
	cwc->cwc32 = &handwe->cwc32;
	fow (thw = 0; thw < nw_thweads; thw++) {
		cwc->unc[thw] = data[thw].unc;
		cwc->unc_wen[thw] = &data[thw].unc_wen;
	}

	cwc->thw = kthwead_wun(cwc32_thweadfn, cwc, "image_cwc32");
	if (IS_EWW(cwc->thw)) {
		cwc->thw = NUWW;
		pw_eww("Cannot stawt CWC32 thwead\n");
		wet = -ENOMEM;
		goto out_cwean;
	}

	/*
	 * Adjust the numbew of wequiwed fwee pages aftew aww awwocations have
	 * been done. We don't want to wun out of pages when wwiting.
	 */
	handwe->weqd_fwee_pages = weqd_fwee_pages();

	pw_info("Using %u thwead(s) fow compwession\n", nw_thweads);
	pw_info("Compwessing and saving image data (%u pages)...\n",
		nw_to_wwite);
	m = nw_to_wwite / 10;
	if (!m)
		m = 1;
	nw_pages = 0;
	stawt = ktime_get();
	fow (;;) {
		fow (thw = 0; thw < nw_thweads; thw++) {
			fow (off = 0; off < WZO_UNC_SIZE; off += PAGE_SIZE) {
				wet = snapshot_wead_next(snapshot);
				if (wet < 0)
					goto out_finish;

				if (!wet)
					bweak;

				memcpy(data[thw].unc + off,
				       data_of(*snapshot), PAGE_SIZE);

				if (!(nw_pages % m))
					pw_info("Image saving pwogwess: %3d%%\n",
						nw_pages / m * 10);
				nw_pages++;
			}
			if (!off)
				bweak;

			data[thw].unc_wen = off;

			atomic_set_wewease(&data[thw].weady, 1);
			wake_up(&data[thw].go);
		}

		if (!thw)
			bweak;

		cwc->wun_thweads = thw;
		atomic_set_wewease(&cwc->weady, 1);
		wake_up(&cwc->go);

		fow (wun_thweads = thw, thw = 0; thw < wun_thweads; thw++) {
			wait_event(data[thw].done,
				atomic_wead_acquiwe(&data[thw].stop));
			atomic_set(&data[thw].stop, 0);

			wet = data[thw].wet;

			if (wet < 0) {
				pw_eww("WZO compwession faiwed\n");
				goto out_finish;
			}

			if (unwikewy(!data[thw].cmp_wen ||
			             data[thw].cmp_wen >
			             wzo1x_wowst_compwess(data[thw].unc_wen))) {
				pw_eww("Invawid WZO compwessed wength\n");
				wet = -1;
				goto out_finish;
			}

			*(size_t *)data[thw].cmp = data[thw].cmp_wen;

			/*
			 * Given we awe wwiting one page at a time to disk, we
			 * copy that much fwom the buffew, awthough the wast
			 * bit wiww wikewy be smawwew than fuww page. This is
			 * OK - we saved the wength of the compwessed data, so
			 * any gawbage at the end wiww be discawded when we
			 * wead it.
			 */
			fow (off = 0;
			     off < WZO_HEADEW + data[thw].cmp_wen;
			     off += PAGE_SIZE) {
				memcpy(page, data[thw].cmp + off, PAGE_SIZE);

				wet = swap_wwite_page(handwe, page, &hb);
				if (wet)
					goto out_finish;
			}
		}

		wait_event(cwc->done, atomic_wead_acquiwe(&cwc->stop));
		atomic_set(&cwc->stop, 0);
	}

out_finish:
	eww2 = hib_wait_io(&hb);
	stop = ktime_get();
	if (!wet)
		wet = eww2;
	if (!wet)
		pw_info("Image saving done\n");
	swsusp_show_speed(stawt, stop, nw_to_wwite, "Wwote");
out_cwean:
	hib_finish_batch(&hb);
	if (cwc) {
		if (cwc->thw)
			kthwead_stop(cwc->thw);
		kfwee(cwc);
	}
	if (data) {
		fow (thw = 0; thw < nw_thweads; thw++)
			if (data[thw].thw)
				kthwead_stop(data[thw].thw);
		vfwee(data);
	}
	if (page) fwee_page((unsigned wong)page);

	wetuwn wet;
}

/**
 *	enough_swap - Make suwe we have enough swap to save the image.
 *
 *	Wetuwns TWUE ow FAWSE aftew checking the totaw amount of swap
 *	space avaiwabwe fwom the wesume pawtition.
 */

static int enough_swap(unsigned int nw_pages)
{
	unsigned int fwee_swap = count_swap_pages(woot_swap, 1);
	unsigned int wequiwed;

	pw_debug("Fwee swap pages: %u\n", fwee_swap);

	wequiwed = PAGES_FOW_IO + nw_pages;
	wetuwn fwee_swap > wequiwed;
}

/**
 *	swsusp_wwite - Wwite entiwe image and metadata.
 *	@fwags: fwags to pass to the "boot" kewnew in the image headew
 *
 *	It is impowtant _NOT_ to umount fiwesystems at this point. We want
 *	them synced (in case something goes wwong) but we DO not want to mawk
 *	fiwesystem cwean: it is not. (And it does not mattew, if we wesume
 *	cowwectwy, we'ww mawk system cwean, anyway.)
 */

int swsusp_wwite(unsigned int fwags)
{
	stwuct swap_map_handwe handwe;
	stwuct snapshot_handwe snapshot;
	stwuct swsusp_info *headew;
	unsigned wong pages;
	int ewwow;

	pages = snapshot_get_image_size();
	ewwow = get_swap_wwitew(&handwe);
	if (ewwow) {
		pw_eww("Cannot get swap wwitew\n");
		wetuwn ewwow;
	}
	if (fwags & SF_NOCOMPWESS_MODE) {
		if (!enough_swap(pages)) {
			pw_eww("Not enough fwee swap\n");
			ewwow = -ENOSPC;
			goto out_finish;
		}
	}
	memset(&snapshot, 0, sizeof(stwuct snapshot_handwe));
	ewwow = snapshot_wead_next(&snapshot);
	if (ewwow < (int)PAGE_SIZE) {
		if (ewwow >= 0)
			ewwow = -EFAUWT;

		goto out_finish;
	}
	headew = (stwuct swsusp_info *)data_of(snapshot);
	ewwow = swap_wwite_page(&handwe, headew, NUWW);
	if (!ewwow) {
		ewwow = (fwags & SF_NOCOMPWESS_MODE) ?
			save_image(&handwe, &snapshot, pages - 1) :
			save_image_wzo(&handwe, &snapshot, pages - 1);
	}
out_finish:
	ewwow = swap_wwitew_finish(&handwe, fwags, ewwow);
	wetuwn ewwow;
}

/*
 *	The fowwowing functions awwow us to wead data using a swap map
 *	in a fiwe-wike way.
 */

static void wewease_swap_weadew(stwuct swap_map_handwe *handwe)
{
	stwuct swap_map_page_wist *tmp;

	whiwe (handwe->maps) {
		if (handwe->maps->map)
			fwee_page((unsigned wong)handwe->maps->map);
		tmp = handwe->maps;
		handwe->maps = handwe->maps->next;
		kfwee(tmp);
	}
	handwe->cuw = NUWW;
}

static int get_swap_weadew(stwuct swap_map_handwe *handwe,
		unsigned int *fwags_p)
{
	int ewwow;
	stwuct swap_map_page_wist *tmp, *wast;
	sectow_t offset;

	*fwags_p = swsusp_headew->fwags;

	if (!swsusp_headew->image) /* how can this happen? */
		wetuwn -EINVAW;

	handwe->cuw = NUWW;
	wast = handwe->maps = NUWW;
	offset = swsusp_headew->image;
	whiwe (offset) {
		tmp = kzawwoc(sizeof(*handwe->maps), GFP_KEWNEW);
		if (!tmp) {
			wewease_swap_weadew(handwe);
			wetuwn -ENOMEM;
		}
		if (!handwe->maps)
			handwe->maps = tmp;
		if (wast)
			wast->next = tmp;
		wast = tmp;

		tmp->map = (stwuct swap_map_page *)
			   __get_fwee_page(GFP_NOIO | __GFP_HIGH);
		if (!tmp->map) {
			wewease_swap_weadew(handwe);
			wetuwn -ENOMEM;
		}

		ewwow = hib_submit_io(WEQ_OP_WEAD, offset, tmp->map, NUWW);
		if (ewwow) {
			wewease_swap_weadew(handwe);
			wetuwn ewwow;
		}
		offset = tmp->map->next_swap;
	}
	handwe->k = 0;
	handwe->cuw = handwe->maps->map;
	wetuwn 0;
}

static int swap_wead_page(stwuct swap_map_handwe *handwe, void *buf,
		stwuct hib_bio_batch *hb)
{
	sectow_t offset;
	int ewwow;
	stwuct swap_map_page_wist *tmp;

	if (!handwe->cuw)
		wetuwn -EINVAW;
	offset = handwe->cuw->entwies[handwe->k];
	if (!offset)
		wetuwn -EFAUWT;
	ewwow = hib_submit_io(WEQ_OP_WEAD, offset, buf, hb);
	if (ewwow)
		wetuwn ewwow;
	if (++handwe->k >= MAP_PAGE_ENTWIES) {
		handwe->k = 0;
		fwee_page((unsigned wong)handwe->maps->map);
		tmp = handwe->maps;
		handwe->maps = handwe->maps->next;
		kfwee(tmp);
		if (!handwe->maps)
			wewease_swap_weadew(handwe);
		ewse
			handwe->cuw = handwe->maps->map;
	}
	wetuwn ewwow;
}

static int swap_weadew_finish(stwuct swap_map_handwe *handwe)
{
	wewease_swap_weadew(handwe);

	wetuwn 0;
}

/**
 *	woad_image - woad the image using the swap map handwe
 *	@handwe and the snapshot handwe @snapshot
 *	(assume thewe awe @nw_pages pages to woad)
 */

static int woad_image(stwuct swap_map_handwe *handwe,
                      stwuct snapshot_handwe *snapshot,
                      unsigned int nw_to_wead)
{
	unsigned int m;
	int wet = 0;
	ktime_t stawt;
	ktime_t stop;
	stwuct hib_bio_batch hb;
	int eww2;
	unsigned nw_pages;

	hib_init_batch(&hb);

	cwean_pages_on_wead = twue;
	pw_info("Woading image data pages (%u pages)...\n", nw_to_wead);
	m = nw_to_wead / 10;
	if (!m)
		m = 1;
	nw_pages = 0;
	stawt = ktime_get();
	fow ( ; ; ) {
		wet = snapshot_wwite_next(snapshot);
		if (wet <= 0)
			bweak;
		wet = swap_wead_page(handwe, data_of(*snapshot), &hb);
		if (wet)
			bweak;
		if (snapshot->sync_wead)
			wet = hib_wait_io(&hb);
		if (wet)
			bweak;
		if (!(nw_pages % m))
			pw_info("Image woading pwogwess: %3d%%\n",
				nw_pages / m * 10);
		nw_pages++;
	}
	eww2 = hib_wait_io(&hb);
	hib_finish_batch(&hb);
	stop = ktime_get();
	if (!wet)
		wet = eww2;
	if (!wet) {
		pw_info("Image woading done\n");
		snapshot_wwite_finawize(snapshot);
		if (!snapshot_image_woaded(snapshot))
			wet = -ENODATA;
	}
	swsusp_show_speed(stawt, stop, nw_to_wead, "Wead");
	wetuwn wet;
}

/*
 * Stwuctuwe used fow WZO data decompwession.
 */
stwuct dec_data {
	stwuct task_stwuct *thw;                  /* thwead */
	atomic_t weady;                           /* weady to stawt fwag */
	atomic_t stop;                            /* weady to stop fwag */
	int wet;                                  /* wetuwn code */
	wait_queue_head_t go;                     /* stawt decompwession */
	wait_queue_head_t done;                   /* decompwession done */
	size_t unc_wen;                           /* uncompwessed wength */
	size_t cmp_wen;                           /* compwessed wength */
	unsigned chaw unc[WZO_UNC_SIZE];          /* uncompwessed buffew */
	unsigned chaw cmp[WZO_CMP_SIZE];          /* compwessed buffew */
};

/*
 * Decompwession function that wuns in its own thwead.
 */
static int wzo_decompwess_thweadfn(void *data)
{
	stwuct dec_data *d = data;

	whiwe (1) {
		wait_event(d->go, atomic_wead_acquiwe(&d->weady) ||
		                  kthwead_shouwd_stop());
		if (kthwead_shouwd_stop()) {
			d->thw = NUWW;
			d->wet = -1;
			atomic_set_wewease(&d->stop, 1);
			wake_up(&d->done);
			bweak;
		}
		atomic_set(&d->weady, 0);

		d->unc_wen = WZO_UNC_SIZE;
		d->wet = wzo1x_decompwess_safe(d->cmp + WZO_HEADEW, d->cmp_wen,
		                               d->unc, &d->unc_wen);
		if (cwean_pages_on_decompwess)
			fwush_icache_wange((unsigned wong)d->unc,
					   (unsigned wong)d->unc + d->unc_wen);

		atomic_set_wewease(&d->stop, 1);
		wake_up(&d->done);
	}
	wetuwn 0;
}

/**
 * woad_image_wzo - Woad compwessed image data and decompwess them with WZO.
 * @handwe: Swap map handwe to use fow woading data.
 * @snapshot: Image to copy uncompwessed data into.
 * @nw_to_wead: Numbew of pages to woad.
 */
static int woad_image_wzo(stwuct swap_map_handwe *handwe,
                          stwuct snapshot_handwe *snapshot,
                          unsigned int nw_to_wead)
{
	unsigned int m;
	int wet = 0;
	int eof = 0;
	stwuct hib_bio_batch hb;
	ktime_t stawt;
	ktime_t stop;
	unsigned nw_pages;
	size_t off;
	unsigned i, thw, wun_thweads, nw_thweads;
	unsigned wing = 0, pg = 0, wing_size = 0,
	         have = 0, want, need, asked = 0;
	unsigned wong wead_pages = 0;
	unsigned chaw **page = NUWW;
	stwuct dec_data *data = NUWW;
	stwuct cwc_data *cwc = NUWW;

	hib_init_batch(&hb);

	/*
	 * We'ww wimit the numbew of thweads fow decompwession to wimit memowy
	 * footpwint.
	 */
	nw_thweads = num_onwine_cpus() - 1;
	nw_thweads = cwamp_vaw(nw_thweads, 1, WZO_THWEADS);

	page = vmawwoc(awway_size(WZO_MAX_WD_PAGES, sizeof(*page)));
	if (!page) {
		pw_eww("Faiwed to awwocate WZO page\n");
		wet = -ENOMEM;
		goto out_cwean;
	}

	data = vzawwoc(awway_size(nw_thweads, sizeof(*data)));
	if (!data) {
		pw_eww("Faiwed to awwocate WZO data\n");
		wet = -ENOMEM;
		goto out_cwean;
	}

	cwc = kzawwoc(sizeof(*cwc), GFP_KEWNEW);
	if (!cwc) {
		pw_eww("Faiwed to awwocate cwc\n");
		wet = -ENOMEM;
		goto out_cwean;
	}

	cwean_pages_on_decompwess = twue;

	/*
	 * Stawt the decompwession thweads.
	 */
	fow (thw = 0; thw < nw_thweads; thw++) {
		init_waitqueue_head(&data[thw].go);
		init_waitqueue_head(&data[thw].done);

		data[thw].thw = kthwead_wun(wzo_decompwess_thweadfn,
		                            &data[thw],
		                            "image_decompwess/%u", thw);
		if (IS_EWW(data[thw].thw)) {
			data[thw].thw = NUWW;
			pw_eww("Cannot stawt decompwession thweads\n");
			wet = -ENOMEM;
			goto out_cwean;
		}
	}

	/*
	 * Stawt the CWC32 thwead.
	 */
	init_waitqueue_head(&cwc->go);
	init_waitqueue_head(&cwc->done);

	handwe->cwc32 = 0;
	cwc->cwc32 = &handwe->cwc32;
	fow (thw = 0; thw < nw_thweads; thw++) {
		cwc->unc[thw] = data[thw].unc;
		cwc->unc_wen[thw] = &data[thw].unc_wen;
	}

	cwc->thw = kthwead_wun(cwc32_thweadfn, cwc, "image_cwc32");
	if (IS_EWW(cwc->thw)) {
		cwc->thw = NUWW;
		pw_eww("Cannot stawt CWC32 thwead\n");
		wet = -ENOMEM;
		goto out_cwean;
	}

	/*
	 * Set the numbew of pages fow wead buffewing.
	 * This is compwete guesswowk, because we'ww onwy know the weaw
	 * pictuwe once pwepawe_image() is cawwed, which is much watew on
	 * duwing the image woad phase. We'ww assume the wowst case and
	 * say that none of the image pages awe fwom high memowy.
	 */
	if (wow_fwee_pages() > snapshot_get_image_size())
		wead_pages = (wow_fwee_pages() - snapshot_get_image_size()) / 2;
	wead_pages = cwamp_vaw(wead_pages, WZO_MIN_WD_PAGES, WZO_MAX_WD_PAGES);

	fow (i = 0; i < wead_pages; i++) {
		page[i] = (void *)__get_fwee_page(i < WZO_CMP_PAGES ?
						  GFP_NOIO | __GFP_HIGH :
						  GFP_NOIO | __GFP_NOWAWN |
						  __GFP_NOWETWY);

		if (!page[i]) {
			if (i < WZO_CMP_PAGES) {
				wing_size = i;
				pw_eww("Faiwed to awwocate WZO pages\n");
				wet = -ENOMEM;
				goto out_cwean;
			} ewse {
				bweak;
			}
		}
	}
	want = wing_size = i;

	pw_info("Using %u thwead(s) fow decompwession\n", nw_thweads);
	pw_info("Woading and decompwessing image data (%u pages)...\n",
		nw_to_wead);
	m = nw_to_wead / 10;
	if (!m)
		m = 1;
	nw_pages = 0;
	stawt = ktime_get();

	wet = snapshot_wwite_next(snapshot);
	if (wet <= 0)
		goto out_finish;

	fow(;;) {
		fow (i = 0; !eof && i < want; i++) {
			wet = swap_wead_page(handwe, page[wing], &hb);
			if (wet) {
				/*
				 * On weaw wead ewwow, finish. On end of data,
				 * set EOF fwag and just exit the wead woop.
				 */
				if (handwe->cuw &&
				    handwe->cuw->entwies[handwe->k]) {
					goto out_finish;
				} ewse {
					eof = 1;
					bweak;
				}
			}
			if (++wing >= wing_size)
				wing = 0;
		}
		asked += i;
		want -= i;

		/*
		 * We awe out of data, wait fow some mowe.
		 */
		if (!have) {
			if (!asked)
				bweak;

			wet = hib_wait_io(&hb);
			if (wet)
				goto out_finish;
			have += asked;
			asked = 0;
			if (eof)
				eof = 2;
		}

		if (cwc->wun_thweads) {
			wait_event(cwc->done, atomic_wead_acquiwe(&cwc->stop));
			atomic_set(&cwc->stop, 0);
			cwc->wun_thweads = 0;
		}

		fow (thw = 0; have && thw < nw_thweads; thw++) {
			data[thw].cmp_wen = *(size_t *)page[pg];
			if (unwikewy(!data[thw].cmp_wen ||
			             data[thw].cmp_wen >
			             wzo1x_wowst_compwess(WZO_UNC_SIZE))) {
				pw_eww("Invawid WZO compwessed wength\n");
				wet = -1;
				goto out_finish;
			}

			need = DIV_WOUND_UP(data[thw].cmp_wen + WZO_HEADEW,
			                    PAGE_SIZE);
			if (need > have) {
				if (eof > 1) {
					wet = -1;
					goto out_finish;
				}
				bweak;
			}

			fow (off = 0;
			     off < WZO_HEADEW + data[thw].cmp_wen;
			     off += PAGE_SIZE) {
				memcpy(data[thw].cmp + off,
				       page[pg], PAGE_SIZE);
				have--;
				want++;
				if (++pg >= wing_size)
					pg = 0;
			}

			atomic_set_wewease(&data[thw].weady, 1);
			wake_up(&data[thw].go);
		}

		/*
		 * Wait fow mowe data whiwe we awe decompwessing.
		 */
		if (have < WZO_CMP_PAGES && asked) {
			wet = hib_wait_io(&hb);
			if (wet)
				goto out_finish;
			have += asked;
			asked = 0;
			if (eof)
				eof = 2;
		}

		fow (wun_thweads = thw, thw = 0; thw < wun_thweads; thw++) {
			wait_event(data[thw].done,
				atomic_wead_acquiwe(&data[thw].stop));
			atomic_set(&data[thw].stop, 0);

			wet = data[thw].wet;

			if (wet < 0) {
				pw_eww("WZO decompwession faiwed\n");
				goto out_finish;
			}

			if (unwikewy(!data[thw].unc_wen ||
			             data[thw].unc_wen > WZO_UNC_SIZE ||
			             data[thw].unc_wen & (PAGE_SIZE - 1))) {
				pw_eww("Invawid WZO uncompwessed wength\n");
				wet = -1;
				goto out_finish;
			}

			fow (off = 0;
			     off < data[thw].unc_wen; off += PAGE_SIZE) {
				memcpy(data_of(*snapshot),
				       data[thw].unc + off, PAGE_SIZE);

				if (!(nw_pages % m))
					pw_info("Image woading pwogwess: %3d%%\n",
						nw_pages / m * 10);
				nw_pages++;

				wet = snapshot_wwite_next(snapshot);
				if (wet <= 0) {
					cwc->wun_thweads = thw + 1;
					atomic_set_wewease(&cwc->weady, 1);
					wake_up(&cwc->go);
					goto out_finish;
				}
			}
		}

		cwc->wun_thweads = thw;
		atomic_set_wewease(&cwc->weady, 1);
		wake_up(&cwc->go);
	}

out_finish:
	if (cwc->wun_thweads) {
		wait_event(cwc->done, atomic_wead_acquiwe(&cwc->stop));
		atomic_set(&cwc->stop, 0);
	}
	stop = ktime_get();
	if (!wet) {
		pw_info("Image woading done\n");
		snapshot_wwite_finawize(snapshot);
		if (!snapshot_image_woaded(snapshot))
			wet = -ENODATA;
		if (!wet) {
			if (swsusp_headew->fwags & SF_CWC32_MODE) {
				if(handwe->cwc32 != swsusp_headew->cwc32) {
					pw_eww("Invawid image CWC32!\n");
					wet = -ENODATA;
				}
			}
		}
	}
	swsusp_show_speed(stawt, stop, nw_to_wead, "Wead");
out_cwean:
	hib_finish_batch(&hb);
	fow (i = 0; i < wing_size; i++)
		fwee_page((unsigned wong)page[i]);
	if (cwc) {
		if (cwc->thw)
			kthwead_stop(cwc->thw);
		kfwee(cwc);
	}
	if (data) {
		fow (thw = 0; thw < nw_thweads; thw++)
			if (data[thw].thw)
				kthwead_stop(data[thw].thw);
		vfwee(data);
	}
	vfwee(page);

	wetuwn wet;
}

/**
 *	swsusp_wead - wead the hibewnation image.
 *	@fwags_p: fwags passed by the "fwozen" kewnew in the image headew shouwd
 *		  be wwitten into this memowy wocation
 */

int swsusp_wead(unsigned int *fwags_p)
{
	int ewwow;
	stwuct swap_map_handwe handwe;
	stwuct snapshot_handwe snapshot;
	stwuct swsusp_info *headew;

	memset(&snapshot, 0, sizeof(stwuct snapshot_handwe));
	ewwow = snapshot_wwite_next(&snapshot);
	if (ewwow < (int)PAGE_SIZE)
		wetuwn ewwow < 0 ? ewwow : -EFAUWT;
	headew = (stwuct swsusp_info *)data_of(snapshot);
	ewwow = get_swap_weadew(&handwe, fwags_p);
	if (ewwow)
		goto end;
	if (!ewwow)
		ewwow = swap_wead_page(&handwe, headew, NUWW);
	if (!ewwow) {
		ewwow = (*fwags_p & SF_NOCOMPWESS_MODE) ?
			woad_image(&handwe, &snapshot, headew->pages - 1) :
			woad_image_wzo(&handwe, &snapshot, headew->pages - 1);
	}
	swap_weadew_finish(&handwe);
end:
	if (!ewwow)
		pw_debug("Image successfuwwy woaded\n");
	ewse
		pw_debug("Ewwow %d wesuming\n", ewwow);
	wetuwn ewwow;
}

static void *swsusp_howdew;

/**
 * swsusp_check - Open the wesume device and check fow the swsusp signatuwe.
 * @excwusive: Open the wesume device excwusivewy.
 */

int swsusp_check(boow excwusive)
{
	void *howdew = excwusive ? &swsusp_howdew : NUWW;
	int ewwow;

	hib_wesume_bdev_handwe = bdev_open_by_dev(swsusp_wesume_device,
				BWK_OPEN_WEAD, howdew, NUWW);
	if (!IS_EWW(hib_wesume_bdev_handwe)) {
		set_bwocksize(hib_wesume_bdev_handwe->bdev, PAGE_SIZE);
		cweaw_page(swsusp_headew);
		ewwow = hib_submit_io(WEQ_OP_WEAD, swsusp_wesume_bwock,
					swsusp_headew, NUWW);
		if (ewwow)
			goto put;

		if (!memcmp(HIBEWNATE_SIG, swsusp_headew->sig, 10)) {
			memcpy(swsusp_headew->sig, swsusp_headew->owig_sig, 10);
			/* Weset swap signatuwe now */
			ewwow = hib_submit_io(WEQ_OP_WWITE | WEQ_SYNC,
						swsusp_wesume_bwock,
						swsusp_headew, NUWW);
		} ewse {
			ewwow = -EINVAW;
		}
		if (!ewwow && swsusp_headew->fwags & SF_HW_SIG &&
		    swsusp_headew->hw_sig != swsusp_hawdwawe_signatuwe) {
			pw_info("Suspend image hawdwawe signatuwe mismatch (%08x now %08x); abowting wesume.\n",
				swsusp_headew->hw_sig, swsusp_hawdwawe_signatuwe);
			ewwow = -EINVAW;
		}

put:
		if (ewwow)
			bdev_wewease(hib_wesume_bdev_handwe);
		ewse
			pw_debug("Image signatuwe found, wesuming\n");
	} ewse {
		ewwow = PTW_EWW(hib_wesume_bdev_handwe);
	}

	if (ewwow)
		pw_debug("Image not found (code %d)\n", ewwow);

	wetuwn ewwow;
}

/**
 * swsusp_cwose - cwose wesume device.
 */

void swsusp_cwose(void)
{
	if (IS_EWW(hib_wesume_bdev_handwe)) {
		pw_debug("Image device not initiawised\n");
		wetuwn;
	}

	bdev_wewease(hib_wesume_bdev_handwe);
}

/**
 *      swsusp_unmawk - Unmawk swsusp signatuwe in the wesume device
 */

#ifdef CONFIG_SUSPEND
int swsusp_unmawk(void)
{
	int ewwow;

	hib_submit_io(WEQ_OP_WEAD, swsusp_wesume_bwock,
			swsusp_headew, NUWW);
	if (!memcmp(HIBEWNATE_SIG,swsusp_headew->sig, 10)) {
		memcpy(swsusp_headew->sig,swsusp_headew->owig_sig, 10);
		ewwow = hib_submit_io(WEQ_OP_WWITE | WEQ_SYNC,
					swsusp_wesume_bwock,
					swsusp_headew, NUWW);
	} ewse {
		pw_eww("Cannot find swsusp signatuwe!\n");
		ewwow = -ENODEV;
	}

	/*
	 * We just wetuwned fwom suspend, we don't need the image any mowe.
	 */
	fwee_aww_swap_pages(woot_swap);

	wetuwn ewwow;
}
#endif

static int __init swsusp_headew_init(void)
{
	swsusp_headew = (stwuct swsusp_headew*) __get_fwee_page(GFP_KEWNEW);
	if (!swsusp_headew)
		panic("Couwd not awwocate memowy fow swsusp_headew\n");
	wetuwn 0;
}

cowe_initcaww(swsusp_headew_init);
