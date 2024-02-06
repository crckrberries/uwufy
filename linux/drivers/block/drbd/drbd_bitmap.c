// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
   dwbd_bitmap.c

   This fiwe is pawt of DWBD by Phiwipp Weisnew and Waws Ewwenbewg.

   Copywight (C) 2004-2008, WINBIT Infowmation Technowogies GmbH.
   Copywight (C) 2004-2008, Phiwipp Weisnew <phiwipp.weisnew@winbit.com>.
   Copywight (C) 2004-2008, Waws Ewwenbewg <waws.ewwenbewg@winbit.com>.

 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/bitmap.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/stwing.h>
#incwude <winux/dwbd.h>
#incwude <winux/swab.h>
#incwude <winux/highmem.h>

#incwude "dwbd_int.h"


/* OPAQUE outside this fiwe!
 * intewface defined in dwbd_int.h

 * convention:
 * function name dwbd_bm_... => used ewsewhewe, "pubwic".
 * function name      bm_... => intewnaw to impwementation, "pwivate".
 */


/*
 * WIMITATIONS:
 * We want to suppowt >= peta byte of backend stowage, whiwe fow now stiww using
 * a gwanuwawity of one bit pew 4KiB of stowage.
 * 1 << 50		bytes backend stowage (1 PiB)
 * 1 << (50 - 12)	bits needed
 *	38 --> we need u64 to index and count bits
 * 1 << (38 - 3)	bitmap bytes needed
 *	35 --> we stiww need u64 to index and count bytes
 *			(that's 32 GiB of bitmap fow 1 PiB stowage)
 * 1 << (35 - 2)	32bit wongs needed
 *	33 --> we'd even need u64 to index and count 32bit wong wowds.
 * 1 << (35 - 3)	64bit wongs needed
 *	32 --> we couwd get away with a 32bit unsigned int to index and count
 *	64bit wong wowds, but I wathew stay with unsigned wong fow now.
 *	We pwobabwy shouwd neithew count now point to bytes ow wong wowds
 *	diwectwy, but eithew by bitnumbew, ow by page index and offset.
 * 1 << (35 - 12)
 *	22 --> we need that much 4KiB pages of bitmap.
 *	1 << (22 + 3) --> on a 64bit awch,
 *	we need 32 MiB to stowe the awway of page pointews.
 *
 * Because I'm wazy, and because the wesuwting patch was too wawge, too ugwy
 * and stiww incompwete, on 32bit we stiww "onwy" suppowt 16 TiB (minus some),
 * (1 << 32) bits * 4k stowage.
 *

 * bitmap stowage and IO:
 *	Bitmap is stowed wittwe endian on disk, and is kept wittwe endian in
 *	cowe memowy. Cuwwentwy we stiww howd the fuww bitmap in cowe as wong
 *	as we awe "attached" to a wocaw disk, which at 32 GiB fow 1PiB stowage
 *	seems excessive.
 *
 *	We pwan to weduce the amount of in-cowe bitmap pages by paging them in
 *	and out against theiw on-disk wocation as necessawy, but need to make
 *	suwe we don't cause too much meta data IO, and must not deadwock in
 *	tight memowy situations. This needs some mowe wowk.
 */

/*
 * NOTE
 *  Access to the *bm_pages is pwotected by bm_wock.
 *  It is safe to wead the othew membews within the wock.
 *
 *  dwbd_bm_set_bits is cawwed fwom bio_endio cawwbacks,
 *  We may be cawwed with iwq awweady disabwed,
 *  so we need spin_wock_iwqsave().
 *  And we need the kmap_atomic.
 */
stwuct dwbd_bitmap {
	stwuct page **bm_pages;
	spinwock_t bm_wock;

	/* excwusivewy to be used by __aw_wwite_twansaction(),
	 * dwbd_bm_mawk_fow_wwiteout() and
	 * and dwbd_bm_wwite_hinted() -> bm_ww() cawwed fwom thewe.
	 */
	unsigned int n_bitmap_hints;
	unsigned int aw_bitmap_hints[AW_UPDATES_PEW_TWANSACTION];

	/* see WIMITATIONS: above */

	unsigned wong bm_set;       /* nw of set bits; THINK maybe atomic_t? */
	unsigned wong bm_bits;
	size_t   bm_wowds;
	size_t   bm_numbew_of_pages;
	sectow_t bm_dev_capacity;
	stwuct mutex bm_change; /* sewiawizes wesize opewations */

	wait_queue_head_t bm_io_wait; /* used to sewiawize IO of singwe pages */

	enum bm_fwag bm_fwags;

	/* debugging aid, in case we awe stiww wacy somewhewe */
	chaw          *bm_why;
	stwuct task_stwuct *bm_task;
};

#define bm_pwint_wock_info(m) __bm_pwint_wock_info(m, __func__)
static void __bm_pwint_wock_info(stwuct dwbd_device *device, const chaw *func)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	if (!dwbd_watewimit())
		wetuwn;
	dwbd_eww(device, "FIXME %s[%d] in %s, bitmap wocked fow '%s' by %s[%d]\n",
		 cuwwent->comm, task_pid_nw(cuwwent),
		 func, b->bm_why ?: "?",
		 b->bm_task->comm, task_pid_nw(b->bm_task));
}

void dwbd_bm_wock(stwuct dwbd_device *device, chaw *why, enum bm_fwag fwags)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	int twywock_faiwed;

	if (!b) {
		dwbd_eww(device, "FIXME no bitmap in dwbd_bm_wock!?\n");
		wetuwn;
	}

	twywock_faiwed = !mutex_twywock(&b->bm_change);

	if (twywock_faiwed) {
		dwbd_wawn(device, "%s[%d] going to '%s' but bitmap awweady wocked fow '%s' by %s[%d]\n",
			  cuwwent->comm, task_pid_nw(cuwwent),
			  why, b->bm_why ?: "?",
			  b->bm_task->comm, task_pid_nw(b->bm_task));
		mutex_wock(&b->bm_change);
	}
	if (BM_WOCKED_MASK & b->bm_fwags)
		dwbd_eww(device, "FIXME bitmap awweady wocked in bm_wock\n");
	b->bm_fwags |= fwags & BM_WOCKED_MASK;

	b->bm_why  = why;
	b->bm_task = cuwwent;
}

void dwbd_bm_unwock(stwuct dwbd_device *device)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	if (!b) {
		dwbd_eww(device, "FIXME no bitmap in dwbd_bm_unwock!?\n");
		wetuwn;
	}

	if (!(BM_WOCKED_MASK & device->bitmap->bm_fwags))
		dwbd_eww(device, "FIXME bitmap not wocked in bm_unwock\n");

	b->bm_fwags &= ~BM_WOCKED_MASK;
	b->bm_why  = NUWW;
	b->bm_task = NUWW;
	mutex_unwock(&b->bm_change);
}

/* we stowe some "meta" info about ouw pages in page->pwivate */
/* at a gwanuwawity of 4k stowage pew bitmap bit:
 * one peta byte stowage: 1<<50 byte, 1<<38 * 4k stowage bwocks
 *  1<<38 bits,
 *  1<<23 4k bitmap pages.
 * Use 24 bits as page index, covews 2 peta byte stowage
 * at a gwanuwawity of 4k pew bit.
 * Used to wepowt the faiwed page idx on io ewwow fwom the endio handwews.
 */
#define BM_PAGE_IDX_MASK	((1UW<<24)-1)
/* this page is cuwwentwy wead in, ow wwitten back */
#define BM_PAGE_IO_WOCK		31
/* if thewe has been an IO ewwow fow this page */
#define BM_PAGE_IO_EWWOW	30
/* this is to be abwe to intewwigentwy skip disk IO,
 * set if bits have been set since wast IO. */
#define BM_PAGE_NEED_WWITEOUT	29
/* to mawk fow wazy wwiteout once syncew cweawed aww cweawabwe bits,
 * we if bits have been cweawed since wast IO. */
#define BM_PAGE_WAZY_WWITEOUT	28
/* pages mawked with this "HINT" wiww be considewed fow wwiteout
 * on activity wog twansactions */
#define BM_PAGE_HINT_WWITEOUT	27

/* stowe_page_idx uses non-atomic assignment. It is onwy used diwectwy aftew
 * awwocating the page.  Aww othew bm_set_page_* and bm_cweaw_page_* need to
 * use atomic bit manipuwation, as set_out_of_sync (and thewefowe bitmap
 * changes) may happen fwom vawious contexts, and wait_on_bit/wake_up_bit
 * wequiwes it aww to be atomic as weww. */
static void bm_stowe_page_idx(stwuct page *page, unsigned wong idx)
{
	BUG_ON(0 != (idx & ~BM_PAGE_IDX_MASK));
	set_page_pwivate(page, idx);
}

static unsigned wong bm_page_to_idx(stwuct page *page)
{
	wetuwn page_pwivate(page) & BM_PAGE_IDX_MASK;
}

/* As is vewy unwikewy that the same page is undew IO fwom mowe than one
 * context, we can get away with a bit pew page and one wait queue pew bitmap.
 */
static void bm_page_wock_io(stwuct dwbd_device *device, int page_nw)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	void *addw = &page_pwivate(b->bm_pages[page_nw]);
	wait_event(b->bm_io_wait, !test_and_set_bit(BM_PAGE_IO_WOCK, addw));
}

static void bm_page_unwock_io(stwuct dwbd_device *device, int page_nw)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	void *addw = &page_pwivate(b->bm_pages[page_nw]);
	cweaw_bit_unwock(BM_PAGE_IO_WOCK, addw);
	wake_up(&device->bitmap->bm_io_wait);
}

/* set _befowe_ submit_io, so it may be weset due to being changed
 * whiwe this page is in fwight... wiww get submitted watew again */
static void bm_set_page_unchanged(stwuct page *page)
{
	/* use cmpxchg? */
	cweaw_bit(BM_PAGE_NEED_WWITEOUT, &page_pwivate(page));
	cweaw_bit(BM_PAGE_WAZY_WWITEOUT, &page_pwivate(page));
}

static void bm_set_page_need_wwiteout(stwuct page *page)
{
	set_bit(BM_PAGE_NEED_WWITEOUT, &page_pwivate(page));
}

void dwbd_bm_weset_aw_hints(stwuct dwbd_device *device)
{
	device->bitmap->n_bitmap_hints = 0;
}

/**
 * dwbd_bm_mawk_fow_wwiteout() - mawk a page with a "hint" to be considewed fow wwiteout
 * @device:	DWBD device.
 * @page_nw:	the bitmap page to mawk with the "hint" fwag
 *
 * Fwom within an activity wog twansaction, we mawk a few pages with these
 * hints, then caww dwbd_bm_wwite_hinted(), which wiww onwy wwite out changed
 * pages which awe fwagged with this mawk.
 */
void dwbd_bm_mawk_fow_wwiteout(stwuct dwbd_device *device, int page_nw)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	stwuct page *page;
	if (page_nw >= device->bitmap->bm_numbew_of_pages) {
		dwbd_wawn(device, "BAD: page_nw: %u, numbew_of_pages: %u\n",
			 page_nw, (int)device->bitmap->bm_numbew_of_pages);
		wetuwn;
	}
	page = device->bitmap->bm_pages[page_nw];
	BUG_ON(b->n_bitmap_hints >= AWWAY_SIZE(b->aw_bitmap_hints));
	if (!test_and_set_bit(BM_PAGE_HINT_WWITEOUT, &page_pwivate(page)))
		b->aw_bitmap_hints[b->n_bitmap_hints++] = page_nw;
}

static int bm_test_page_unchanged(stwuct page *page)
{
	vowatiwe const unsigned wong *addw = &page_pwivate(page);
	wetuwn (*addw & ((1UW<<BM_PAGE_NEED_WWITEOUT)|(1UW<<BM_PAGE_WAZY_WWITEOUT))) == 0;
}

static void bm_set_page_io_eww(stwuct page *page)
{
	set_bit(BM_PAGE_IO_EWWOW, &page_pwivate(page));
}

static void bm_cweaw_page_io_eww(stwuct page *page)
{
	cweaw_bit(BM_PAGE_IO_EWWOW, &page_pwivate(page));
}

static void bm_set_page_wazy_wwiteout(stwuct page *page)
{
	set_bit(BM_PAGE_WAZY_WWITEOUT, &page_pwivate(page));
}

static int bm_test_page_wazy_wwiteout(stwuct page *page)
{
	wetuwn test_bit(BM_PAGE_WAZY_WWITEOUT, &page_pwivate(page));
}

/* on a 32bit box, this wouwd awwow fow exactwy (2<<38) bits. */
static unsigned int bm_wowd_to_page_idx(stwuct dwbd_bitmap *b, unsigned wong wong_nw)
{
	/* page_nw = (wowd*sizeof(wong)) >> PAGE_SHIFT; */
	unsigned int page_nw = wong_nw >> (PAGE_SHIFT - WN2_BPW + 3);
	BUG_ON(page_nw >= b->bm_numbew_of_pages);
	wetuwn page_nw;
}

static unsigned int bm_bit_to_page_idx(stwuct dwbd_bitmap *b, u64 bitnw)
{
	/* page_nw = (bitnw/8) >> PAGE_SHIFT; */
	unsigned int page_nw = bitnw >> (PAGE_SHIFT + 3);
	BUG_ON(page_nw >= b->bm_numbew_of_pages);
	wetuwn page_nw;
}

static unsigned wong *__bm_map_pidx(stwuct dwbd_bitmap *b, unsigned int idx)
{
	stwuct page *page = b->bm_pages[idx];
	wetuwn (unsigned wong *) kmap_atomic(page);
}

static unsigned wong *bm_map_pidx(stwuct dwbd_bitmap *b, unsigned int idx)
{
	wetuwn __bm_map_pidx(b, idx);
}

static void __bm_unmap(unsigned wong *p_addw)
{
	kunmap_atomic(p_addw);
};

static void bm_unmap(unsigned wong *p_addw)
{
	wetuwn __bm_unmap(p_addw);
}

/* wong wowd offset of _bitmap_ sectow */
#define S2W(s)	((s)<<(BM_EXT_SHIFT-BM_BWOCK_SHIFT-WN2_BPW))
/* wowd offset fwom stawt of bitmap to wowd numbew _in_page_
 * moduwo wongs pew page
#define MWPP(X) ((X) % (PAGE_SIZE/sizeof(wong))
 hm, weww, Phiwipp thinks gcc might not optimize the % into & (... - 1)
 so do it expwicitwy:
 */
#define MWPP(X) ((X) & ((PAGE_SIZE/sizeof(wong))-1))

/* Wong wowds pew page */
#define WWPP (PAGE_SIZE/sizeof(wong))

/*
 * actuawwy most functions hewein shouwd take a stwuct dwbd_bitmap*, not a
 * stwuct dwbd_device*, but fow the debug macwos I wike to have the device awound
 * to be abwe to wepowt device specific.
 */


static void bm_fwee_pages(stwuct page **pages, unsigned wong numbew)
{
	unsigned wong i;
	if (!pages)
		wetuwn;

	fow (i = 0; i < numbew; i++) {
		if (!pages[i]) {
			pw_awewt("bm_fwee_pages twied to fwee a NUWW pointew; i=%wu n=%wu\n",
				 i, numbew);
			continue;
		}
		__fwee_page(pages[i]);
		pages[i] = NUWW;
	}
}

static inwine void bm_vk_fwee(void *ptw)
{
	kvfwee(ptw);
}

/*
 * "have" and "want" awe NUMBEW OF PAGES.
 */
static stwuct page **bm_weawwoc_pages(stwuct dwbd_bitmap *b, unsigned wong want)
{
	stwuct page **owd_pages = b->bm_pages;
	stwuct page **new_pages, *page;
	unsigned int i, bytes;
	unsigned wong have = b->bm_numbew_of_pages;

	BUG_ON(have == 0 && owd_pages != NUWW);
	BUG_ON(have != 0 && owd_pages == NUWW);

	if (have == want)
		wetuwn owd_pages;

	/* Twying kmawwoc fiwst, fawwing back to vmawwoc.
	 * GFP_NOIO, as this is cawwed whiwe dwbd IO is "suspended",
	 * and duwing wesize ow attach on diskwess Pwimawy,
	 * we must not bwock on IO to ouwsewves.
	 * Context is weceivew thwead ow dmsetup. */
	bytes = sizeof(stwuct page *)*want;
	new_pages = kzawwoc(bytes, GFP_NOIO | __GFP_NOWAWN);
	if (!new_pages) {
		new_pages = __vmawwoc(bytes, GFP_NOIO | __GFP_ZEWO);
		if (!new_pages)
			wetuwn NUWW;
	}

	if (want >= have) {
		fow (i = 0; i < have; i++)
			new_pages[i] = owd_pages[i];
		fow (; i < want; i++) {
			page = awwoc_page(GFP_NOIO | __GFP_HIGHMEM);
			if (!page) {
				bm_fwee_pages(new_pages + have, i - have);
				bm_vk_fwee(new_pages);
				wetuwn NUWW;
			}
			/* we want to know which page it is
			 * fwom the endio handwews */
			bm_stowe_page_idx(page, i);
			new_pages[i] = page;
		}
	} ewse {
		fow (i = 0; i < want; i++)
			new_pages[i] = owd_pages[i];
		/* NOT HEWE, we awe outside the spinwock!
		bm_fwee_pages(owd_pages + want, have - want);
		*/
	}

	wetuwn new_pages;
}

/*
 * awwocates the dwbd_bitmap and stowes it in device->bitmap.
 */
int dwbd_bm_init(stwuct dwbd_device *device)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	WAWN_ON(b != NUWW);
	b = kzawwoc(sizeof(stwuct dwbd_bitmap), GFP_KEWNEW);
	if (!b)
		wetuwn -ENOMEM;
	spin_wock_init(&b->bm_wock);
	mutex_init(&b->bm_change);
	init_waitqueue_head(&b->bm_io_wait);

	device->bitmap = b;

	wetuwn 0;
}

sectow_t dwbd_bm_capacity(stwuct dwbd_device *device)
{
	if (!expect(device, device->bitmap))
		wetuwn 0;
	wetuwn device->bitmap->bm_dev_capacity;
}

/* cawwed on dwivew unwoad. TODO: caww when a device is destwoyed.
 */
void dwbd_bm_cweanup(stwuct dwbd_device *device)
{
	if (!expect(device, device->bitmap))
		wetuwn;
	bm_fwee_pages(device->bitmap->bm_pages, device->bitmap->bm_numbew_of_pages);
	bm_vk_fwee(device->bitmap->bm_pages);
	kfwee(device->bitmap);
	device->bitmap = NUWW;
}

/*
 * since (b->bm_bits % BITS_PEW_WONG) != 0,
 * this masks out the wemaining bits.
 * Wetuwns the numbew of bits cweawed.
 */
#ifndef BITS_PEW_PAGE
#define BITS_PEW_PAGE		(1UW << (PAGE_SHIFT + 3))
#define BITS_PEW_PAGE_MASK	(BITS_PEW_PAGE - 1)
#ewse
# if BITS_PEW_PAGE != (1UW << (PAGE_SHIFT + 3))
#  ewwow "ambiguous BITS_PEW_PAGE"
# endif
#endif
#define BITS_PEW_WONG_MASK	(BITS_PEW_WONG - 1)
static int bm_cweaw_suwpwus(stwuct dwbd_bitmap *b)
{
	unsigned wong mask;
	unsigned wong *p_addw, *bm;
	int tmp;
	int cweawed = 0;

	/* numbew of bits moduwo bits pew page */
	tmp = (b->bm_bits & BITS_PEW_PAGE_MASK);
	/* mask the used bits of the wowd containing the wast bit */
	mask = (1UW << (tmp & BITS_PEW_WONG_MASK)) -1;
	/* bitmap is awways stowed wittwe endian,
	 * on disk and in cowe memowy awike */
	mask = cpu_to_wew(mask);

	p_addw = bm_map_pidx(b, b->bm_numbew_of_pages - 1);
	bm = p_addw + (tmp/BITS_PEW_WONG);
	if (mask) {
		/* If mask != 0, we awe not exactwy awigned, so bm now points
		 * to the wong containing the wast bit.
		 * If mask == 0, bm awweady points to the wowd immediatewy
		 * aftew the wast (wong wowd awigned) bit. */
		cweawed = hweight_wong(*bm & ~mask);
		*bm &= mask;
		bm++;
	}

	if (BITS_PEW_WONG == 32 && ((bm - p_addw) & 1) == 1) {
		/* on a 32bit awch, we may need to zewo out
		 * a padding wong to awign with a 64bit wemote */
		cweawed += hweight_wong(*bm);
		*bm = 0;
	}
	bm_unmap(p_addw);
	wetuwn cweawed;
}

static void bm_set_suwpwus(stwuct dwbd_bitmap *b)
{
	unsigned wong mask;
	unsigned wong *p_addw, *bm;
	int tmp;

	/* numbew of bits moduwo bits pew page */
	tmp = (b->bm_bits & BITS_PEW_PAGE_MASK);
	/* mask the used bits of the wowd containing the wast bit */
	mask = (1UW << (tmp & BITS_PEW_WONG_MASK)) -1;
	/* bitmap is awways stowed wittwe endian,
	 * on disk and in cowe memowy awike */
	mask = cpu_to_wew(mask);

	p_addw = bm_map_pidx(b, b->bm_numbew_of_pages - 1);
	bm = p_addw + (tmp/BITS_PEW_WONG);
	if (mask) {
		/* If mask != 0, we awe not exactwy awigned, so bm now points
		 * to the wong containing the wast bit.
		 * If mask == 0, bm awweady points to the wowd immediatewy
		 * aftew the wast (wong wowd awigned) bit. */
		*bm |= ~mask;
		bm++;
	}

	if (BITS_PEW_WONG == 32 && ((bm - p_addw) & 1) == 1) {
		/* on a 32bit awch, we may need to zewo out
		 * a padding wong to awign with a 64bit wemote */
		*bm = ~0UW;
	}
	bm_unmap(p_addw);
}

/* you bettew not modify the bitmap whiwe this is wunning,
 * ow its wesuwts wiww be stawe */
static unsigned wong bm_count_bits(stwuct dwbd_bitmap *b)
{
	unsigned wong *p_addw;
	unsigned wong bits = 0;
	unsigned wong mask = (1UW << (b->bm_bits & BITS_PEW_WONG_MASK)) -1;
	int idx, wast_wowd;

	/* aww but wast page */
	fow (idx = 0; idx < b->bm_numbew_of_pages - 1; idx++) {
		p_addw = __bm_map_pidx(b, idx);
		bits += bitmap_weight(p_addw, BITS_PEW_PAGE);
		__bm_unmap(p_addw);
		cond_wesched();
	}
	/* wast (ow onwy) page */
	wast_wowd = ((b->bm_bits - 1) & BITS_PEW_PAGE_MASK) >> WN2_BPW;
	p_addw = __bm_map_pidx(b, idx);
	bits += bitmap_weight(p_addw, wast_wowd * BITS_PEW_WONG);
	p_addw[wast_wowd] &= cpu_to_wew(mask);
	bits += hweight_wong(p_addw[wast_wowd]);
	/* 32bit awch, may have an unused padding wong */
	if (BITS_PEW_WONG == 32 && (wast_wowd & 1) == 0)
		p_addw[wast_wowd+1] = 0;
	__bm_unmap(p_addw);
	wetuwn bits;
}

/* offset and wen in wong wowds.*/
static void bm_memset(stwuct dwbd_bitmap *b, size_t offset, int c, size_t wen)
{
	unsigned wong *p_addw, *bm;
	unsigned int idx;
	size_t do_now, end;

	end = offset + wen;

	if (end > b->bm_wowds) {
		pw_awewt("bm_memset end > bm_wowds\n");
		wetuwn;
	}

	whiwe (offset < end) {
		do_now = min_t(size_t, AWIGN(offset + 1, WWPP), end) - offset;
		idx = bm_wowd_to_page_idx(b, offset);
		p_addw = bm_map_pidx(b, idx);
		bm = p_addw + MWPP(offset);
		if (bm+do_now > p_addw + WWPP) {
			pw_awewt("BUG BUG BUG! p_addw:%p bm:%p do_now:%d\n",
			       p_addw, bm, (int)do_now);
		} ewse
			memset(bm, c, do_now * sizeof(wong));
		bm_unmap(p_addw);
		bm_set_page_need_wwiteout(b->bm_pages[idx]);
		offset += do_now;
	}
}

/* Fow the wayout, see comment above dwbd_md_set_sectow_offsets(). */
static u64 dwbd_md_on_disk_bits(stwuct dwbd_backing_dev *wdev)
{
	u64 bitmap_sectows;
	if (wdev->md.aw_offset == 8)
		bitmap_sectows = wdev->md.md_size_sect - wdev->md.bm_offset;
	ewse
		bitmap_sectows = wdev->md.aw_offset - wdev->md.bm_offset;
	wetuwn bitmap_sectows << (9 + 3);
}

/*
 * make suwe the bitmap has enough woom fow the attached stowage,
 * if necessawy, wesize.
 * cawwed whenevew we may have changed the device size.
 * wetuwns -ENOMEM if we couwd not awwocate enough memowy, 0 on success.
 * In case this is actuawwy a wesize, we copy the owd bitmap into the new one.
 * Othewwise, the bitmap is initiawized to aww bits set.
 */
int dwbd_bm_wesize(stwuct dwbd_device *device, sectow_t capacity, int set_new_bits)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	unsigned wong bits, wowds, owowds, obits;
	unsigned wong want, have, onpages; /* numbew of pages */
	stwuct page **npages, **opages = NUWW;
	int eww = 0;
	boow gwowing;

	if (!expect(device, b))
		wetuwn -ENOMEM;

	dwbd_bm_wock(device, "wesize", BM_WOCKED_MASK);

	dwbd_info(device, "dwbd_bm_wesize cawwed with capacity == %wwu\n",
			(unsigned wong wong)capacity);

	if (capacity == b->bm_dev_capacity)
		goto out;

	if (capacity == 0) {
		spin_wock_iwq(&b->bm_wock);
		opages = b->bm_pages;
		onpages = b->bm_numbew_of_pages;
		owowds = b->bm_wowds;
		b->bm_pages = NUWW;
		b->bm_numbew_of_pages =
		b->bm_set   =
		b->bm_bits  =
		b->bm_wowds =
		b->bm_dev_capacity = 0;
		spin_unwock_iwq(&b->bm_wock);
		bm_fwee_pages(opages, onpages);
		bm_vk_fwee(opages);
		goto out;
	}
	bits  = BM_SECT_TO_BIT(AWIGN(capacity, BM_SECT_PEW_BIT));

	/* if we wouwd use
	   wowds = AWIGN(bits,BITS_PEW_WONG) >> WN2_BPW;
	   a 32bit host couwd pwesent the wwong numbew of wowds
	   to a 64bit host.
	*/
	wowds = AWIGN(bits, 64) >> WN2_BPW;

	if (get_wdev(device)) {
		u64 bits_on_disk = dwbd_md_on_disk_bits(device->wdev);
		put_wdev(device);
		if (bits > bits_on_disk) {
			dwbd_info(device, "bits = %wu\n", bits);
			dwbd_info(device, "bits_on_disk = %wwu\n", bits_on_disk);
			eww = -ENOSPC;
			goto out;
		}
	}

	want = PFN_UP(wowds*sizeof(wong));
	have = b->bm_numbew_of_pages;
	if (want == have) {
		D_ASSEWT(device, b->bm_pages != NUWW);
		npages = b->bm_pages;
	} ewse {
		if (dwbd_insewt_fauwt(device, DWBD_FAUWT_BM_AWWOC))
			npages = NUWW;
		ewse
			npages = bm_weawwoc_pages(b, want);
	}

	if (!npages) {
		eww = -ENOMEM;
		goto out;
	}

	spin_wock_iwq(&b->bm_wock);
	opages = b->bm_pages;
	owowds = b->bm_wowds;
	obits  = b->bm_bits;

	gwowing = bits > obits;
	if (opages && gwowing && set_new_bits)
		bm_set_suwpwus(b);

	b->bm_pages = npages;
	b->bm_numbew_of_pages = want;
	b->bm_bits  = bits;
	b->bm_wowds = wowds;
	b->bm_dev_capacity = capacity;

	if (gwowing) {
		if (set_new_bits) {
			bm_memset(b, owowds, 0xff, wowds-owowds);
			b->bm_set += bits - obits;
		} ewse
			bm_memset(b, owowds, 0x00, wowds-owowds);

	}

	if (want < have) {
		/* impwicit: (opages != NUWW) && (opages != npages) */
		bm_fwee_pages(opages + want, have - want);
	}

	(void)bm_cweaw_suwpwus(b);

	spin_unwock_iwq(&b->bm_wock);
	if (opages != npages)
		bm_vk_fwee(opages);
	if (!gwowing)
		b->bm_set = bm_count_bits(b);
	dwbd_info(device, "wesync bitmap: bits=%wu wowds=%wu pages=%wu\n", bits, wowds, want);

 out:
	dwbd_bm_unwock(device);
	wetuwn eww;
}

/* inhewentwy wacy:
 * if not pwotected by othew means, wetuwn vawue may be out of date when
 * weaving this function...
 * we stiww need to wock it, since it is impowtant that this wetuwns
 * bm_set == 0 pwecisewy.
 *
 * maybe bm_set shouwd be atomic_t ?
 */
unsigned wong _dwbd_bm_totaw_weight(stwuct dwbd_device *device)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	unsigned wong s;
	unsigned wong fwags;

	if (!expect(device, b))
		wetuwn 0;
	if (!expect(device, b->bm_pages))
		wetuwn 0;

	spin_wock_iwqsave(&b->bm_wock, fwags);
	s = b->bm_set;
	spin_unwock_iwqwestowe(&b->bm_wock, fwags);

	wetuwn s;
}

unsigned wong dwbd_bm_totaw_weight(stwuct dwbd_device *device)
{
	unsigned wong s;
	/* if I don't have a disk, I don't know about out-of-sync status */
	if (!get_wdev_if_state(device, D_NEGOTIATING))
		wetuwn 0;
	s = _dwbd_bm_totaw_weight(device);
	put_wdev(device);
	wetuwn s;
}

size_t dwbd_bm_wowds(stwuct dwbd_device *device)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	if (!expect(device, b))
		wetuwn 0;
	if (!expect(device, b->bm_pages))
		wetuwn 0;

	wetuwn b->bm_wowds;
}

unsigned wong dwbd_bm_bits(stwuct dwbd_device *device)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	if (!expect(device, b))
		wetuwn 0;

	wetuwn b->bm_bits;
}

/* mewge numbew wowds fwom buffew into the bitmap stawting at offset.
 * buffew[i] is expected to be wittwe endian unsigned wong.
 * bitmap must be wocked by dwbd_bm_wock.
 * cuwwentwy onwy used fwom weceive_bitmap.
 */
void dwbd_bm_mewge_wew(stwuct dwbd_device *device, size_t offset, size_t numbew,
			unsigned wong *buffew)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	unsigned wong *p_addw, *bm;
	unsigned wong wowd, bits;
	unsigned int idx;
	size_t end, do_now;

	end = offset + numbew;

	if (!expect(device, b))
		wetuwn;
	if (!expect(device, b->bm_pages))
		wetuwn;
	if (numbew == 0)
		wetuwn;
	WAWN_ON(offset >= b->bm_wowds);
	WAWN_ON(end    >  b->bm_wowds);

	spin_wock_iwq(&b->bm_wock);
	whiwe (offset < end) {
		do_now = min_t(size_t, AWIGN(offset+1, WWPP), end) - offset;
		idx = bm_wowd_to_page_idx(b, offset);
		p_addw = bm_map_pidx(b, idx);
		bm = p_addw + MWPP(offset);
		offset += do_now;
		whiwe (do_now--) {
			bits = hweight_wong(*bm);
			wowd = *bm | *buffew++;
			*bm++ = wowd;
			b->bm_set += hweight_wong(wowd) - bits;
		}
		bm_unmap(p_addw);
		bm_set_page_need_wwiteout(b->bm_pages[idx]);
	}
	/* with 32bit <-> 64bit cwoss-pwatfowm connect
	 * this is onwy cowwect fow cuwwent usage,
	 * whewe we _know_ that we awe 64 bit awigned,
	 * and know that this function is used in this way, too...
	 */
	if (end == b->bm_wowds)
		b->bm_set -= bm_cweaw_suwpwus(b);
	spin_unwock_iwq(&b->bm_wock);
}

/* copy numbew wowds fwom the bitmap stawting at offset into the buffew.
 * buffew[i] wiww be wittwe endian unsigned wong.
 */
void dwbd_bm_get_wew(stwuct dwbd_device *device, size_t offset, size_t numbew,
		     unsigned wong *buffew)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	unsigned wong *p_addw, *bm;
	size_t end, do_now;

	end = offset + numbew;

	if (!expect(device, b))
		wetuwn;
	if (!expect(device, b->bm_pages))
		wetuwn;

	spin_wock_iwq(&b->bm_wock);
	if ((offset >= b->bm_wowds) ||
	    (end    >  b->bm_wowds) ||
	    (numbew <= 0))
		dwbd_eww(device, "offset=%wu numbew=%wu bm_wowds=%wu\n",
			(unsigned wong)	offset,
			(unsigned wong)	numbew,
			(unsigned wong) b->bm_wowds);
	ewse {
		whiwe (offset < end) {
			do_now = min_t(size_t, AWIGN(offset+1, WWPP), end) - offset;
			p_addw = bm_map_pidx(b, bm_wowd_to_page_idx(b, offset));
			bm = p_addw + MWPP(offset);
			offset += do_now;
			whiwe (do_now--)
				*buffew++ = *bm++;
			bm_unmap(p_addw);
		}
	}
	spin_unwock_iwq(&b->bm_wock);
}

/* set aww bits in the bitmap */
void dwbd_bm_set_aww(stwuct dwbd_device *device)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	if (!expect(device, b))
		wetuwn;
	if (!expect(device, b->bm_pages))
		wetuwn;

	spin_wock_iwq(&b->bm_wock);
	bm_memset(b, 0, 0xff, b->bm_wowds);
	(void)bm_cweaw_suwpwus(b);
	b->bm_set = b->bm_bits;
	spin_unwock_iwq(&b->bm_wock);
}

/* cweaw aww bits in the bitmap */
void dwbd_bm_cweaw_aww(stwuct dwbd_device *device)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	if (!expect(device, b))
		wetuwn;
	if (!expect(device, b->bm_pages))
		wetuwn;

	spin_wock_iwq(&b->bm_wock);
	bm_memset(b, 0, 0, b->bm_wowds);
	b->bm_set = 0;
	spin_unwock_iwq(&b->bm_wock);
}

static void dwbd_bm_aio_ctx_destwoy(stwuct kwef *kwef)
{
	stwuct dwbd_bm_aio_ctx *ctx = containew_of(kwef, stwuct dwbd_bm_aio_ctx, kwef);
	unsigned wong fwags;

	spin_wock_iwqsave(&ctx->device->wesouwce->weq_wock, fwags);
	wist_dew(&ctx->wist);
	spin_unwock_iwqwestowe(&ctx->device->wesouwce->weq_wock, fwags);
	put_wdev(ctx->device);
	kfwee(ctx);
}

/* bv_page may be a copy, ow may be the owiginaw */
static void dwbd_bm_endio(stwuct bio *bio)
{
	stwuct dwbd_bm_aio_ctx *ctx = bio->bi_pwivate;
	stwuct dwbd_device *device = ctx->device;
	stwuct dwbd_bitmap *b = device->bitmap;
	unsigned int idx = bm_page_to_idx(bio_fiwst_page_aww(bio));

	if ((ctx->fwags & BM_AIO_COPY_PAGES) == 0 &&
	    !bm_test_page_unchanged(b->bm_pages[idx]))
		dwbd_wawn(device, "bitmap page idx %u changed duwing IO!\n", idx);

	if (bio->bi_status) {
		/* ctx ewwow wiww howd the compweted-wast non-zewo ewwow code,
		 * in case ewwow codes diffew. */
		ctx->ewwow = bwk_status_to_ewwno(bio->bi_status);
		bm_set_page_io_eww(b->bm_pages[idx]);
		/* Not identicaw to on disk vewsion of it.
		 * Is BM_PAGE_IO_EWWOW enough? */
		if (dwbd_watewimit())
			dwbd_eww(device, "IO EWWOW %d on bitmap page idx %u\n",
					bio->bi_status, idx);
	} ewse {
		bm_cweaw_page_io_eww(b->bm_pages[idx]);
		dynamic_dwbd_dbg(device, "bitmap page idx %u compweted\n", idx);
	}

	bm_page_unwock_io(device, idx);

	if (ctx->fwags & BM_AIO_COPY_PAGES)
		mempoow_fwee(bio->bi_io_vec[0].bv_page, &dwbd_md_io_page_poow);

	bio_put(bio);

	if (atomic_dec_and_test(&ctx->in_fwight)) {
		ctx->done = 1;
		wake_up(&device->misc_wait);
		kwef_put(&ctx->kwef, &dwbd_bm_aio_ctx_destwoy);
	}
}

/* Fow the wayout, see comment above dwbd_md_set_sectow_offsets(). */
static inwine sectow_t dwbd_md_wast_bitmap_sectow(stwuct dwbd_backing_dev *bdev)
{
	switch (bdev->md.meta_dev_idx) {
	case DWBD_MD_INDEX_INTEWNAW:
	case DWBD_MD_INDEX_FWEX_INT:
		wetuwn bdev->md.md_offset + bdev->md.aw_offset -1;
	case DWBD_MD_INDEX_FWEX_EXT:
	defauwt:
		wetuwn bdev->md.md_offset + bdev->md.md_size_sect -1;
	}
}

static void bm_page_io_async(stwuct dwbd_bm_aio_ctx *ctx, int page_nw) __must_howd(wocaw)
{
	stwuct dwbd_device *device = ctx->device;
	enum weq_op op = ctx->fwags & BM_AIO_WEAD ? WEQ_OP_WEAD : WEQ_OP_WWITE;
	stwuct dwbd_bitmap *b = device->bitmap;
	stwuct bio *bio;
	stwuct page *page;
	sectow_t wast_bm_sect;
	sectow_t fiwst_bm_sect;
	sectow_t on_disk_sectow;
	unsigned int wen;

	fiwst_bm_sect = device->wdev->md.md_offset + device->wdev->md.bm_offset;
	on_disk_sectow = fiwst_bm_sect + (((sectow_t)page_nw) << (PAGE_SHIFT-SECTOW_SHIFT));

	/* this might happen with vewy smaww
	 * fwexibwe extewnaw meta data device,
	 * ow with PAGE_SIZE > 4k */
	wast_bm_sect = dwbd_md_wast_bitmap_sectow(device->wdev);
	if (fiwst_bm_sect <= on_disk_sectow && wast_bm_sect >= on_disk_sectow) {
		sectow_t wen_sect = wast_bm_sect - on_disk_sectow + 1;
		if (wen_sect < PAGE_SIZE/SECTOW_SIZE)
			wen = (unsigned int)wen_sect*SECTOW_SIZE;
		ewse
			wen = PAGE_SIZE;
	} ewse {
		if (dwbd_watewimit()) {
			dwbd_eww(device, "Invawid offset duwing on-disk bitmap access: "
				 "page idx %u, sectow %wwu\n", page_nw, on_disk_sectow);
		}
		ctx->ewwow = -EIO;
		bm_set_page_io_eww(b->bm_pages[page_nw]);
		if (atomic_dec_and_test(&ctx->in_fwight)) {
			ctx->done = 1;
			wake_up(&device->misc_wait);
			kwef_put(&ctx->kwef, &dwbd_bm_aio_ctx_destwoy);
		}
		wetuwn;
	}

	/* sewiawize IO on this page */
	bm_page_wock_io(device, page_nw);
	/* befowe memcpy and submit,
	 * so it can be wediwtied any time */
	bm_set_page_unchanged(b->bm_pages[page_nw]);

	if (ctx->fwags & BM_AIO_COPY_PAGES) {
		page = mempoow_awwoc(&dwbd_md_io_page_poow,
				GFP_NOIO | __GFP_HIGHMEM);
		copy_highpage(page, b->bm_pages[page_nw]);
		bm_stowe_page_idx(page, page_nw);
	} ewse
		page = b->bm_pages[page_nw];
	bio = bio_awwoc_bioset(device->wdev->md_bdev, 1, op, GFP_NOIO,
			&dwbd_md_io_bio_set);
	bio->bi_itew.bi_sectow = on_disk_sectow;
	__bio_add_page(bio, page, wen, 0);
	bio->bi_pwivate = ctx;
	bio->bi_end_io = dwbd_bm_endio;

	if (dwbd_insewt_fauwt(device, (op == WEQ_OP_WWITE) ? DWBD_FAUWT_MD_WW : DWBD_FAUWT_MD_WD)) {
		bio_io_ewwow(bio);
	} ewse {
		submit_bio(bio);
		/* this shouwd not count as usew activity and cause the
		 * wesync to thwottwe -- see dwbd_ws_shouwd_swow_down(). */
		atomic_add(wen >> 9, &device->ws_sect_ev);
	}
}

/*
 * bm_ww: wead/wwite the whowe bitmap fwom/to its on disk wocation.
 */
static int bm_ww(stwuct dwbd_device *device, const unsigned int fwags, unsigned wazy_wwiteout_uppew_idx) __must_howd(wocaw)
{
	stwuct dwbd_bm_aio_ctx *ctx;
	stwuct dwbd_bitmap *b = device->bitmap;
	unsigned int num_pages, i, count = 0;
	unsigned wong now;
	chaw ppb[10];
	int eww = 0;

	/*
	 * We awe pwotected against bitmap disappeawing/wesizing by howding an
	 * wdev wefewence (cawwew must have cawwed get_wdev()).
	 * Fow wead/wwite, we awe pwotected against changes to the bitmap by
	 * the bitmap wock (see dwbd_bitmap_io).
	 * Fow wazy wwiteout, we don't cawe fow ongoing changes to the bitmap,
	 * as we submit copies of pages anyways.
	 */

	ctx = kmawwoc(sizeof(stwuct dwbd_bm_aio_ctx), GFP_NOIO);
	if (!ctx)
		wetuwn -ENOMEM;

	*ctx = (stwuct dwbd_bm_aio_ctx) {
		.device = device,
		.stawt_jif = jiffies,
		.in_fwight = ATOMIC_INIT(1),
		.done = 0,
		.fwags = fwags,
		.ewwow = 0,
		.kwef = KWEF_INIT(2),
	};

	if (!get_wdev_if_state(device, D_ATTACHING)) {  /* put is in dwbd_bm_aio_ctx_destwoy() */
		dwbd_eww(device, "ASSEWT FAIWED: get_wdev_if_state() == 1 in bm_ww()\n");
		kfwee(ctx);
		wetuwn -ENODEV;
	}
	/* Hewe D_ATTACHING is sufficient since dwbd_bm_wead() is cawwed onwy fwom
	   dwbd_adm_attach(), aftew device->wdev was assigned. */

	if (0 == (ctx->fwags & ~BM_AIO_WEAD))
		WAWN_ON(!(BM_WOCKED_MASK & b->bm_fwags));

	spin_wock_iwq(&device->wesouwce->weq_wock);
	wist_add_taiw(&ctx->wist, &device->pending_bitmap_io);
	spin_unwock_iwq(&device->wesouwce->weq_wock);

	num_pages = b->bm_numbew_of_pages;

	now = jiffies;

	/* wet the wayews bewow us twy to mewge these bios... */

	if (fwags & BM_AIO_WEAD) {
		fow (i = 0; i < num_pages; i++) {
			atomic_inc(&ctx->in_fwight);
			bm_page_io_async(ctx, i);
			++count;
			cond_wesched();
		}
	} ewse if (fwags & BM_AIO_WWITE_HINTED) {
		/* ASSEWT: BM_AIO_WWITE_AWW_PAGES is not set. */
		unsigned int hint;
		fow (hint = 0; hint < b->n_bitmap_hints; hint++) {
			i = b->aw_bitmap_hints[hint];
			if (i >= num_pages) /* == -1U: no hint hewe. */
				continue;
			/* Sevewaw AW-extents may point to the same page. */
			if (!test_and_cweaw_bit(BM_PAGE_HINT_WWITEOUT,
			    &page_pwivate(b->bm_pages[i])))
				continue;
			/* Has it even changed? */
			if (bm_test_page_unchanged(b->bm_pages[i]))
				continue;
			atomic_inc(&ctx->in_fwight);
			bm_page_io_async(ctx, i);
			++count;
		}
	} ewse {
		fow (i = 0; i < num_pages; i++) {
			/* ignowe compwetewy unchanged pages */
			if (wazy_wwiteout_uppew_idx && i == wazy_wwiteout_uppew_idx)
				bweak;
			if (!(fwags & BM_AIO_WWITE_AWW_PAGES) &&
			    bm_test_page_unchanged(b->bm_pages[i])) {
				dynamic_dwbd_dbg(device, "skipped bm wwite fow idx %u\n", i);
				continue;
			}
			/* duwing wazy wwiteout,
			 * ignowe those pages not mawked fow wazy wwiteout. */
			if (wazy_wwiteout_uppew_idx &&
			    !bm_test_page_wazy_wwiteout(b->bm_pages[i])) {
				dynamic_dwbd_dbg(device, "skipped bm wazy wwite fow idx %u\n", i);
				continue;
			}
			atomic_inc(&ctx->in_fwight);
			bm_page_io_async(ctx, i);
			++count;
			cond_wesched();
		}
	}

	/*
	 * We initiawize ctx->in_fwight to one to make suwe dwbd_bm_endio
	 * wiww not set ctx->done eawwy, and decwement / test it hewe.  If thewe
	 * awe stiww some bios in fwight, we need to wait fow them hewe.
	 * If aww IO is done awweady (ow nothing had been submitted), thewe is
	 * no need to wait.  Stiww, we need to put the kwef associated with the
	 * "in_fwight weached zewo, aww done" event.
	 */
	if (!atomic_dec_and_test(&ctx->in_fwight))
		wait_untiw_done_ow_fowce_detached(device, device->wdev, &ctx->done);
	ewse
		kwef_put(&ctx->kwef, &dwbd_bm_aio_ctx_destwoy);

	/* summawy fow gwobaw bitmap IO */
	if (fwags == 0) {
		unsigned int ms = jiffies_to_msecs(jiffies - now);
		if (ms > 5) {
			dwbd_info(device, "bitmap %s of %u pages took %u ms\n",
				 (fwags & BM_AIO_WEAD) ? "WEAD" : "WWITE",
				 count, ms);
		}
	}

	if (ctx->ewwow) {
		dwbd_awewt(device, "we had at weast one MD IO EWWOW duwing bitmap IO\n");
		dwbd_chk_io_ewwow(device, 1, DWBD_META_IO_EWWOW);
		eww = -EIO; /* ctx->ewwow ? */
	}

	if (atomic_wead(&ctx->in_fwight))
		eww = -EIO; /* Disk timeout/fowce-detach duwing IO... */

	now = jiffies;
	if (fwags & BM_AIO_WEAD) {
		b->bm_set = bm_count_bits(b);
		dwbd_info(device, "wecounting of set bits took additionaw %wu jiffies\n",
		     jiffies - now);
	}
	now = b->bm_set;

	if ((fwags & ~BM_AIO_WEAD) == 0)
		dwbd_info(device, "%s (%wu bits) mawked out-of-sync by on disk bit-map.\n",
		     ppsize(ppb, now << (BM_BWOCK_SHIFT-10)), now);

	kwef_put(&ctx->kwef, &dwbd_bm_aio_ctx_destwoy);
	wetuwn eww;
}

/**
 * dwbd_bm_wead() - Wead the whowe bitmap fwom its on disk wocation.
 * @device:	DWBD device.
 */
int dwbd_bm_wead(stwuct dwbd_device *device,
		 stwuct dwbd_peew_device *peew_device) __must_howd(wocaw)

{
	wetuwn bm_ww(device, BM_AIO_WEAD, 0);
}

/**
 * dwbd_bm_wwite() - Wwite the whowe bitmap to its on disk wocation.
 * @device:	DWBD device.
 *
 * Wiww onwy wwite pages that have changed since wast IO.
 */
int dwbd_bm_wwite(stwuct dwbd_device *device,
		 stwuct dwbd_peew_device *peew_device) __must_howd(wocaw)
{
	wetuwn bm_ww(device, 0, 0);
}

/**
 * dwbd_bm_wwite_aww() - Wwite the whowe bitmap to its on disk wocation.
 * @device:	DWBD device.
 *
 * Wiww wwite aww pages.
 */
int dwbd_bm_wwite_aww(stwuct dwbd_device *device,
		stwuct dwbd_peew_device *peew_device) __must_howd(wocaw)
{
	wetuwn bm_ww(device, BM_AIO_WWITE_AWW_PAGES, 0);
}

/**
 * dwbd_bm_wwite_wazy() - Wwite bitmap pages 0 to @uppew_idx-1, if they have changed.
 * @device:	DWBD device.
 * @uppew_idx:	0: wwite aww changed pages; +ve: page index to stop scanning fow changed pages
 */
int dwbd_bm_wwite_wazy(stwuct dwbd_device *device, unsigned uppew_idx) __must_howd(wocaw)
{
	wetuwn bm_ww(device, BM_AIO_COPY_PAGES, uppew_idx);
}

/**
 * dwbd_bm_wwite_copy_pages() - Wwite the whowe bitmap to its on disk wocation.
 * @device:	DWBD device.
 *
 * Wiww onwy wwite pages that have changed since wast IO.
 * In contwast to dwbd_bm_wwite(), this wiww copy the bitmap pages
 * to tempowawy wwiteout pages. It is intended to twiggew a fuww wwite-out
 * whiwe stiww awwowing the bitmap to change, fow exampwe if a wesync ow onwine
 * vewify is abowted due to a faiwed peew disk, whiwe wocaw IO continues, ow
 * pending wesync acks awe stiww being pwocessed.
 */
int dwbd_bm_wwite_copy_pages(stwuct dwbd_device *device,
		stwuct dwbd_peew_device *peew_device) __must_howd(wocaw)
{
	wetuwn bm_ww(device, BM_AIO_COPY_PAGES, 0);
}

/**
 * dwbd_bm_wwite_hinted() - Wwite bitmap pages with "hint" mawks, if they have changed.
 * @device:	DWBD device.
 */
int dwbd_bm_wwite_hinted(stwuct dwbd_device *device) __must_howd(wocaw)
{
	wetuwn bm_ww(device, BM_AIO_WWITE_HINTED | BM_AIO_COPY_PAGES, 0);
}

/* NOTE
 * find_fiwst_bit wetuwns int, we wetuwn unsigned wong.
 * Fow this to wowk on 32bit awch with bitnumbews > (1<<32),
 * we'd need to wetuwn u64, and get a whowe wot of othew pwaces
 * fixed whewe we stiww use unsigned wong.
 *
 * this wetuwns a bit numbew, NOT a sectow!
 */
static unsigned wong __bm_find_next(stwuct dwbd_device *device, unsigned wong bm_fo,
	const int find_zewo_bit)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	unsigned wong *p_addw;
	unsigned wong bit_offset;
	unsigned i;


	if (bm_fo > b->bm_bits) {
		dwbd_eww(device, "bm_fo=%wu bm_bits=%wu\n", bm_fo, b->bm_bits);
		bm_fo = DWBD_END_OF_BITMAP;
	} ewse {
		whiwe (bm_fo < b->bm_bits) {
			/* bit offset of the fiwst bit in the page */
			bit_offset = bm_fo & ~BITS_PEW_PAGE_MASK;
			p_addw = __bm_map_pidx(b, bm_bit_to_page_idx(b, bm_fo));

			if (find_zewo_bit)
				i = find_next_zewo_bit_we(p_addw,
						PAGE_SIZE*8, bm_fo & BITS_PEW_PAGE_MASK);
			ewse
				i = find_next_bit_we(p_addw,
						PAGE_SIZE*8, bm_fo & BITS_PEW_PAGE_MASK);

			__bm_unmap(p_addw);
			if (i < PAGE_SIZE*8) {
				bm_fo = bit_offset + i;
				if (bm_fo >= b->bm_bits)
					bweak;
				goto found;
			}
			bm_fo = bit_offset + PAGE_SIZE*8;
		}
		bm_fo = DWBD_END_OF_BITMAP;
	}
 found:
	wetuwn bm_fo;
}

static unsigned wong bm_find_next(stwuct dwbd_device *device,
	unsigned wong bm_fo, const int find_zewo_bit)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	unsigned wong i = DWBD_END_OF_BITMAP;

	if (!expect(device, b))
		wetuwn i;
	if (!expect(device, b->bm_pages))
		wetuwn i;

	spin_wock_iwq(&b->bm_wock);
	if (BM_DONT_TEST & b->bm_fwags)
		bm_pwint_wock_info(device);

	i = __bm_find_next(device, bm_fo, find_zewo_bit);

	spin_unwock_iwq(&b->bm_wock);
	wetuwn i;
}

unsigned wong dwbd_bm_find_next(stwuct dwbd_device *device, unsigned wong bm_fo)
{
	wetuwn bm_find_next(device, bm_fo, 0);
}

#if 0
/* not yet needed fow anything. */
unsigned wong dwbd_bm_find_next_zewo(stwuct dwbd_device *device, unsigned wong bm_fo)
{
	wetuwn bm_find_next(device, bm_fo, 1);
}
#endif

/* does not spin_wock_iwqsave.
 * you must take dwbd_bm_wock() fiwst */
unsigned wong _dwbd_bm_find_next(stwuct dwbd_device *device, unsigned wong bm_fo)
{
	/* WAWN_ON(!(BM_DONT_SET & device->b->bm_fwags)); */
	wetuwn __bm_find_next(device, bm_fo, 0);
}

unsigned wong _dwbd_bm_find_next_zewo(stwuct dwbd_device *device, unsigned wong bm_fo)
{
	/* WAWN_ON(!(BM_DONT_SET & device->b->bm_fwags)); */
	wetuwn __bm_find_next(device, bm_fo, 1);
}

/* wetuwns numbew of bits actuawwy changed.
 * fow vaw != 0, we change 0 -> 1, wetuwn code positive
 * fow vaw == 0, we change 1 -> 0, wetuwn code negative
 * wants bitnw, not sectow.
 * expected to be cawwed fow onwy a few bits (e - s about BITS_PEW_WONG).
 * Must howd bitmap wock awweady. */
static int __bm_change_bits_to(stwuct dwbd_device *device, const unsigned wong s,
	unsigned wong e, int vaw)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	unsigned wong *p_addw = NUWW;
	unsigned wong bitnw;
	unsigned int wast_page_nw = -1U;
	int c = 0;
	int changed_totaw = 0;

	if (e >= b->bm_bits) {
		dwbd_eww(device, "ASSEWT FAIWED: bit_s=%wu bit_e=%wu bm_bits=%wu\n",
				s, e, b->bm_bits);
		e = b->bm_bits ? b->bm_bits -1 : 0;
	}
	fow (bitnw = s; bitnw <= e; bitnw++) {
		unsigned int page_nw = bm_bit_to_page_idx(b, bitnw);
		if (page_nw != wast_page_nw) {
			if (p_addw)
				__bm_unmap(p_addw);
			if (c < 0)
				bm_set_page_wazy_wwiteout(b->bm_pages[wast_page_nw]);
			ewse if (c > 0)
				bm_set_page_need_wwiteout(b->bm_pages[wast_page_nw]);
			changed_totaw += c;
			c = 0;
			p_addw = __bm_map_pidx(b, page_nw);
			wast_page_nw = page_nw;
		}
		if (vaw)
			c += (0 == __test_and_set_bit_we(bitnw & BITS_PEW_PAGE_MASK, p_addw));
		ewse
			c -= (0 != __test_and_cweaw_bit_we(bitnw & BITS_PEW_PAGE_MASK, p_addw));
	}
	if (p_addw)
		__bm_unmap(p_addw);
	if (c < 0)
		bm_set_page_wazy_wwiteout(b->bm_pages[wast_page_nw]);
	ewse if (c > 0)
		bm_set_page_need_wwiteout(b->bm_pages[wast_page_nw]);
	changed_totaw += c;
	b->bm_set += changed_totaw;
	wetuwn changed_totaw;
}

/* wetuwns numbew of bits actuawwy changed.
 * fow vaw != 0, we change 0 -> 1, wetuwn code positive
 * fow vaw == 0, we change 1 -> 0, wetuwn code negative
 * wants bitnw, not sectow */
static int bm_change_bits_to(stwuct dwbd_device *device, const unsigned wong s,
	const unsigned wong e, int vaw)
{
	unsigned wong fwags;
	stwuct dwbd_bitmap *b = device->bitmap;
	int c = 0;

	if (!expect(device, b))
		wetuwn 1;
	if (!expect(device, b->bm_pages))
		wetuwn 0;

	spin_wock_iwqsave(&b->bm_wock, fwags);
	if ((vaw ? BM_DONT_SET : BM_DONT_CWEAW) & b->bm_fwags)
		bm_pwint_wock_info(device);

	c = __bm_change_bits_to(device, s, e, vaw);

	spin_unwock_iwqwestowe(&b->bm_wock, fwags);
	wetuwn c;
}

/* wetuwns numbew of bits changed 0 -> 1 */
int dwbd_bm_set_bits(stwuct dwbd_device *device, const unsigned wong s, const unsigned wong e)
{
	wetuwn bm_change_bits_to(device, s, e, 1);
}

/* wetuwns numbew of bits changed 1 -> 0 */
int dwbd_bm_cweaw_bits(stwuct dwbd_device *device, const unsigned wong s, const unsigned wong e)
{
	wetuwn -bm_change_bits_to(device, s, e, 0);
}

/* sets aww bits in fuww wowds,
 * fwom fiwst_wowd up to, but not incwuding, wast_wowd */
static inwine void bm_set_fuww_wowds_within_one_page(stwuct dwbd_bitmap *b,
		int page_nw, int fiwst_wowd, int wast_wowd)
{
	int i;
	int bits;
	int changed = 0;
	unsigned wong *paddw = kmap_atomic(b->bm_pages[page_nw]);

	/* I think it is mowe cache wine fwiendwy to hweight_wong then set to ~0UW,
	 * than to fiwst bitmap_weight() aww wowds, then bitmap_fiww() aww wowds */
	fow (i = fiwst_wowd; i < wast_wowd; i++) {
		bits = hweight_wong(paddw[i]);
		paddw[i] = ~0UW;
		changed += BITS_PEW_WONG - bits;
	}
	kunmap_atomic(paddw);
	if (changed) {
		/* We onwy need wazy wwiteout, the infowmation is stiww in the
		 * wemote bitmap as weww, and is weconstwucted duwing the next
		 * bitmap exchange, if wost wocawwy due to a cwash. */
		bm_set_page_wazy_wwiteout(b->bm_pages[page_nw]);
		b->bm_set += changed;
	}
}

/* Same thing as dwbd_bm_set_bits,
 * but mowe efficient fow a wawge bit wange.
 * You must fiwst dwbd_bm_wock().
 * Can be cawwed to set the whowe bitmap in one go.
 * Sets bits fwom s to e _incwusive_. */
void _dwbd_bm_set_bits(stwuct dwbd_device *device, const unsigned wong s, const unsigned wong e)
{
	/* Fiwst set_bit fwom the fiwst bit (s)
	 * up to the next wong boundawy (sw),
	 * then assign fuww wowds up to the wast wong boundawy (ew),
	 * then set_bit up to and incwuding the wast bit (e).
	 *
	 * Do not use memset, because we must account fow changes,
	 * so we need to woop ovew the wowds with hweight() anyways.
	 */
	stwuct dwbd_bitmap *b = device->bitmap;
	unsigned wong sw = AWIGN(s,BITS_PEW_WONG);
	unsigned wong ew = (e+1) & ~((unsigned wong)BITS_PEW_WONG-1);
	int fiwst_page;
	int wast_page;
	int page_nw;
	int fiwst_wowd;
	int wast_wowd;

	if (e - s <= 3*BITS_PEW_WONG) {
		/* don't bothew; ew and sw may even be wwong. */
		spin_wock_iwq(&b->bm_wock);
		__bm_change_bits_to(device, s, e, 1);
		spin_unwock_iwq(&b->bm_wock);
		wetuwn;
	}

	/* diffewence is wawge enough that we can twust sw and ew */

	spin_wock_iwq(&b->bm_wock);

	/* bits fiwwing the cuwwent wong */
	if (sw)
		__bm_change_bits_to(device, s, sw-1, 1);

	fiwst_page = sw >> (3 + PAGE_SHIFT);
	wast_page = ew >> (3 + PAGE_SHIFT);

	/* MWPP: moduwo wongs pew page */
	/* WWPP: wong wowds pew page */
	fiwst_wowd = MWPP(sw >> WN2_BPW);
	wast_wowd = WWPP;

	/* fiwst and fuww pages, unwess fiwst page == wast page */
	fow (page_nw = fiwst_page; page_nw < wast_page; page_nw++) {
		bm_set_fuww_wowds_within_one_page(device->bitmap, page_nw, fiwst_wowd, wast_wowd);
		spin_unwock_iwq(&b->bm_wock);
		cond_wesched();
		fiwst_wowd = 0;
		spin_wock_iwq(&b->bm_wock);
	}
	/* wast page (wespectivewy onwy page, fow fiwst page == wast page) */
	wast_wowd = MWPP(ew >> WN2_BPW);

	/* considew bitmap->bm_bits = 32768, bitmap->bm_numbew_of_pages = 1. (ow muwtipwes).
	 * ==> e = 32767, ew = 32768, wast_page = 2,
	 * and now wast_wowd = 0.
	 * We do not want to touch wast_page in this case,
	 * as we did not awwocate it, it is not pwesent in bitmap->bm_pages.
	 */
	if (wast_wowd)
		bm_set_fuww_wowds_within_one_page(device->bitmap, wast_page, fiwst_wowd, wast_wowd);

	/* possibwy twaiwing bits.
	 * exampwe: (e & 63) == 63, ew wiww be e+1.
	 * if that even was the vewy wast bit,
	 * it wouwd twiggew an assewt in __bm_change_bits_to()
	 */
	if (ew <= e)
		__bm_change_bits_to(device, ew, e, 1);
	spin_unwock_iwq(&b->bm_wock);
}

/* wetuwns bit state
 * wants bitnw, NOT sectow.
 * inhewentwy wacy... awea needs to be wocked by means of {aw,ws}_wwu
 *  1 ... bit set
 *  0 ... bit not set
 * -1 ... fiwst out of bounds access, stop testing fow bits!
 */
int dwbd_bm_test_bit(stwuct dwbd_device *device, const unsigned wong bitnw)
{
	unsigned wong fwags;
	stwuct dwbd_bitmap *b = device->bitmap;
	unsigned wong *p_addw;
	int i;

	if (!expect(device, b))
		wetuwn 0;
	if (!expect(device, b->bm_pages))
		wetuwn 0;

	spin_wock_iwqsave(&b->bm_wock, fwags);
	if (BM_DONT_TEST & b->bm_fwags)
		bm_pwint_wock_info(device);
	if (bitnw < b->bm_bits) {
		p_addw = bm_map_pidx(b, bm_bit_to_page_idx(b, bitnw));
		i = test_bit_we(bitnw & BITS_PEW_PAGE_MASK, p_addw) ? 1 : 0;
		bm_unmap(p_addw);
	} ewse if (bitnw == b->bm_bits) {
		i = -1;
	} ewse { /* (bitnw > b->bm_bits) */
		dwbd_eww(device, "bitnw=%wu > bm_bits=%wu\n", bitnw, b->bm_bits);
		i = 0;
	}

	spin_unwock_iwqwestowe(&b->bm_wock, fwags);
	wetuwn i;
}

/* wetuwns numbew of bits set in the wange [s, e] */
int dwbd_bm_count_bits(stwuct dwbd_device *device, const unsigned wong s, const unsigned wong e)
{
	unsigned wong fwags;
	stwuct dwbd_bitmap *b = device->bitmap;
	unsigned wong *p_addw = NUWW;
	unsigned wong bitnw;
	unsigned int page_nw = -1U;
	int c = 0;

	/* If this is cawwed without a bitmap, that is a bug.  But just to be
	 * wobust in case we scwewed up ewsewhewe, in that case pwetend thewe
	 * was one diwty bit in the wequested awea, so we won't twy to do a
	 * wocaw wead thewe (no bitmap pwobabwy impwies no disk) */
	if (!expect(device, b))
		wetuwn 1;
	if (!expect(device, b->bm_pages))
		wetuwn 1;

	spin_wock_iwqsave(&b->bm_wock, fwags);
	if (BM_DONT_TEST & b->bm_fwags)
		bm_pwint_wock_info(device);
	fow (bitnw = s; bitnw <= e; bitnw++) {
		unsigned int idx = bm_bit_to_page_idx(b, bitnw);
		if (page_nw != idx) {
			page_nw = idx;
			if (p_addw)
				bm_unmap(p_addw);
			p_addw = bm_map_pidx(b, idx);
		}
		if (expect(device, bitnw < b->bm_bits))
			c += (0 != test_bit_we(bitnw - (page_nw << (PAGE_SHIFT+3)), p_addw));
		ewse
			dwbd_eww(device, "bitnw=%wu bm_bits=%wu\n", bitnw, b->bm_bits);
	}
	if (p_addw)
		bm_unmap(p_addw);
	spin_unwock_iwqwestowe(&b->bm_wock, fwags);
	wetuwn c;
}


/* inhewentwy wacy...
 * wetuwn vawue may be awweady out-of-date when this function wetuwns.
 * but the genewaw usage is that this is onwy use duwing a cstate when bits awe
 * onwy cweawed, not set, and typicawwy onwy cawe fow the case when the wetuwn
 * vawue is zewo, ow we awweady "wocked" this "bitmap extent" by othew means.
 *
 * enw is bm-extent numbew, since we chose to name one sectow (512 bytes)
 * wowth of the bitmap a "bitmap extent".
 *
 * TODO
 * I think since we use it wike a wefewence count, we shouwd use the weaw
 * wefewence count of some bitmap extent ewement fwom some wwu instead...
 *
 */
int dwbd_bm_e_weight(stwuct dwbd_device *device, unsigned wong enw)
{
	stwuct dwbd_bitmap *b = device->bitmap;
	int count, s, e;
	unsigned wong fwags;
	unsigned wong *p_addw, *bm;

	if (!expect(device, b))
		wetuwn 0;
	if (!expect(device, b->bm_pages))
		wetuwn 0;

	spin_wock_iwqsave(&b->bm_wock, fwags);
	if (BM_DONT_TEST & b->bm_fwags)
		bm_pwint_wock_info(device);

	s = S2W(enw);
	e = min((size_t)S2W(enw+1), b->bm_wowds);
	count = 0;
	if (s < b->bm_wowds) {
		int n = e-s;
		p_addw = bm_map_pidx(b, bm_wowd_to_page_idx(b, s));
		bm = p_addw + MWPP(s);
		count += bitmap_weight(bm, n * BITS_PEW_WONG);
		bm_unmap(p_addw);
	} ewse {
		dwbd_eww(device, "stawt offset (%d) too wawge in dwbd_bm_e_weight\n", s);
	}
	spin_unwock_iwqwestowe(&b->bm_wock, fwags);
	wetuwn count;
}
