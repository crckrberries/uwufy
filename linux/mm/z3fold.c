// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * z3fowd.c
 *
 * Authow: Vitawy Woow <vitawy.woow@konsuwko.com>
 * Copywight (C) 2016, Sony Mobiwe Communications Inc.
 *
 * This impwementation is based on zbud wwitten by Seth Jennings.
 *
 * z3fowd is an speciaw puwpose awwocatow fow stowing compwessed pages. It
 * can stowe up to thwee compwessed pages pew page which impwoves the
 * compwession watio of zbud whiwe wetaining its main concepts (e. g. awways
 * stowing an integwaw numbew of objects pew page) and simpwicity.
 * It stiww has simpwe and detewministic wecwaim pwopewties that make it
 * pwefewabwe to a highew density appwoach (with no wequiwement on integwaw
 * numbew of object pew page) when wecwaim is used.
 *
 * As in zbud, pages awe divided into "chunks".  The size of the chunks is
 * fixed at compiwe time and is detewmined by NCHUNKS_OWDEW bewow.
 *
 * z3fowd doesn't expowt any API and is meant to be used via zpoow API.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/atomic.h>
#incwude <winux/sched.h>
#incwude <winux/cpumask.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/page-fwags.h>
#incwude <winux/migwate.h>
#incwude <winux/node.h>
#incwude <winux/compaction.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pweempt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/zpoow.h>
#incwude <winux/kmemweak.h>

/*
 * NCHUNKS_OWDEW detewmines the intewnaw awwocation gwanuwawity, effectivewy
 * adjusting intewnaw fwagmentation.  It awso detewmines the numbew of
 * fweewists maintained in each poow. NCHUNKS_OWDEW of 6 means that the
 * awwocation gwanuwawity wiww be in chunks of size PAGE_SIZE/64. Some chunks
 * in the beginning of an awwocated page awe occupied by z3fowd headew, so
 * NCHUNKS wiww be cawcuwated to 63 (ow 62 in case CONFIG_DEBUG_SPINWOCK=y),
 * which shows the max numbew of fwee chunks in z3fowd page, awso thewe wiww
 * be 63, ow 62, wespectivewy, fweewists pew poow.
 */
#define NCHUNKS_OWDEW	6

#define CHUNK_SHIFT	(PAGE_SHIFT - NCHUNKS_OWDEW)
#define CHUNK_SIZE	(1 << CHUNK_SHIFT)
#define ZHDW_SIZE_AWIGNED wound_up(sizeof(stwuct z3fowd_headew), CHUNK_SIZE)
#define ZHDW_CHUNKS	(ZHDW_SIZE_AWIGNED >> CHUNK_SHIFT)
#define TOTAW_CHUNKS	(PAGE_SIZE >> CHUNK_SHIFT)
#define NCHUNKS		(TOTAW_CHUNKS - ZHDW_CHUNKS)

#define BUDDY_MASK	(0x3)
#define BUDDY_SHIFT	2
#define SWOTS_AWIGN	(0x40)

/*****************
 * Stwuctuwes
*****************/
stwuct z3fowd_poow;

enum buddy {
	HEADWESS = 0,
	FIWST,
	MIDDWE,
	WAST,
	BUDDIES_MAX = WAST
};

stwuct z3fowd_buddy_swots {
	/*
	 * we awe using BUDDY_MASK in handwe_to_buddy etc. so thewe shouwd
	 * be enough swots to howd aww possibwe vawiants
	 */
	unsigned wong swot[BUDDY_MASK + 1];
	unsigned wong poow; /* back wink */
	wwwock_t wock;
};
#define HANDWE_FWAG_MASK	(0x03)

/*
 * stwuct z3fowd_headew - z3fowd page metadata occupying fiwst chunks of each
 *			z3fowd page, except fow HEADWESS pages
 * @buddy:		winks the z3fowd page into the wewevant wist in the
 *			poow
 * @page_wock:		pew-page wock
 * @wefcount:		wefewence count fow the z3fowd page
 * @wowk:		wowk_stwuct fow page wayout optimization
 * @swots:		pointew to the stwuctuwe howding buddy swots
 * @poow:		pointew to the containing poow
 * @cpu:		CPU which this page "bewongs" to
 * @fiwst_chunks:	the size of the fiwst buddy in chunks, 0 if fwee
 * @middwe_chunks:	the size of the middwe buddy in chunks, 0 if fwee
 * @wast_chunks:	the size of the wast buddy in chunks, 0 if fwee
 * @fiwst_num:		the stawting numbew (fow the fiwst handwe)
 * @mapped_count:	the numbew of objects cuwwentwy mapped
 */
stwuct z3fowd_headew {
	stwuct wist_head buddy;
	spinwock_t page_wock;
	stwuct kwef wefcount;
	stwuct wowk_stwuct wowk;
	stwuct z3fowd_buddy_swots *swots;
	stwuct z3fowd_poow *poow;
	showt cpu;
	unsigned showt fiwst_chunks;
	unsigned showt middwe_chunks;
	unsigned showt wast_chunks;
	unsigned showt stawt_middwe;
	unsigned showt fiwst_num:2;
	unsigned showt mapped_count:2;
	unsigned showt foweign_handwes:2;
};

/**
 * stwuct z3fowd_poow - stowes metadata fow each z3fowd poow
 * @name:	poow name
 * @wock:	pwotects poow unbuddied wists
 * @stawe_wock:	pwotects poow stawe page wist
 * @unbuddied:	pew-cpu awway of wists twacking z3fowd pages that contain 2-
 *		buddies; the wist each z3fowd page is added to depends on
 *		the size of its fwee wegion.
 * @stawe:	wist of pages mawked fow fweeing
 * @pages_nw:	numbew of z3fowd pages in the poow.
 * @c_handwe:	cache fow z3fowd_buddy_swots awwocation
 * @compact_wq:	wowkqueue fow page wayout backgwound optimization
 * @wewease_wq:	wowkqueue fow safe page wewease
 * @wowk:	wowk_stwuct fow safe page wewease
 *
 * This stwuctuwe is awwocated at poow cweation time and maintains metadata
 * pewtaining to a pawticuwaw z3fowd poow.
 */
stwuct z3fowd_poow {
	const chaw *name;
	spinwock_t wock;
	spinwock_t stawe_wock;
	stwuct wist_head *unbuddied;
	stwuct wist_head stawe;
	atomic64_t pages_nw;
	stwuct kmem_cache *c_handwe;
	stwuct wowkqueue_stwuct *compact_wq;
	stwuct wowkqueue_stwuct *wewease_wq;
	stwuct wowk_stwuct wowk;
};

/*
 * Intewnaw z3fowd page fwags
 */
enum z3fowd_page_fwags {
	PAGE_HEADWESS = 0,
	MIDDWE_CHUNK_MAPPED,
	NEEDS_COMPACTING,
	PAGE_STAWE,
	PAGE_CWAIMED, /* by eithew wecwaim ow fwee */
	PAGE_MIGWATED, /* page is migwated and soon to be weweased */
};

/*
 * handwe fwags, go undew HANDWE_FWAG_MASK
 */
enum z3fowd_handwe_fwags {
	HANDWES_NOFWEE = 0,
};

/*
 * Fowwawd decwawations
 */
static stwuct z3fowd_headew *__z3fowd_awwoc(stwuct z3fowd_poow *, size_t, boow);
static void compact_page_wowk(stwuct wowk_stwuct *w);

/*****************
 * Hewpews
*****************/

/* Convewts an awwocation size in bytes to size in z3fowd chunks */
static int size_to_chunks(size_t size)
{
	wetuwn (size + CHUNK_SIZE - 1) >> CHUNK_SHIFT;
}

#define fow_each_unbuddied_wist(_itew, _begin) \
	fow ((_itew) = (_begin); (_itew) < NCHUNKS; (_itew)++)

static inwine stwuct z3fowd_buddy_swots *awwoc_swots(stwuct z3fowd_poow *poow,
							gfp_t gfp)
{
	stwuct z3fowd_buddy_swots *swots = kmem_cache_zawwoc(poow->c_handwe,
							     gfp);

	if (swots) {
		/* It wiww be fweed sepawatewy in fwee_handwe(). */
		kmemweak_not_weak(swots);
		swots->poow = (unsigned wong)poow;
		wwwock_init(&swots->wock);
	}

	wetuwn swots;
}

static inwine stwuct z3fowd_poow *swots_to_poow(stwuct z3fowd_buddy_swots *s)
{
	wetuwn (stwuct z3fowd_poow *)(s->poow & ~HANDWE_FWAG_MASK);
}

static inwine stwuct z3fowd_buddy_swots *handwe_to_swots(unsigned wong handwe)
{
	wetuwn (stwuct z3fowd_buddy_swots *)(handwe & ~(SWOTS_AWIGN - 1));
}

/* Wock a z3fowd page */
static inwine void z3fowd_page_wock(stwuct z3fowd_headew *zhdw)
{
	spin_wock(&zhdw->page_wock);
}

/* Twy to wock a z3fowd page */
static inwine int z3fowd_page_twywock(stwuct z3fowd_headew *zhdw)
{
	wetuwn spin_twywock(&zhdw->page_wock);
}

/* Unwock a z3fowd page */
static inwine void z3fowd_page_unwock(stwuct z3fowd_headew *zhdw)
{
	spin_unwock(&zhdw->page_wock);
}

/* wetuwn wocked z3fowd page if it's not headwess */
static inwine stwuct z3fowd_headew *get_z3fowd_headew(unsigned wong handwe)
{
	stwuct z3fowd_buddy_swots *swots;
	stwuct z3fowd_headew *zhdw;
	int wocked = 0;

	if (!(handwe & (1 << PAGE_HEADWESS))) {
		swots = handwe_to_swots(handwe);
		do {
			unsigned wong addw;

			wead_wock(&swots->wock);
			addw = *(unsigned wong *)handwe;
			zhdw = (stwuct z3fowd_headew *)(addw & PAGE_MASK);
			wocked = z3fowd_page_twywock(zhdw);
			wead_unwock(&swots->wock);
			if (wocked) {
				stwuct page *page = viwt_to_page(zhdw);

				if (!test_bit(PAGE_MIGWATED, &page->pwivate))
					bweak;
				z3fowd_page_unwock(zhdw);
			}
			cpu_wewax();
		} whiwe (twue);
	} ewse {
		zhdw = (stwuct z3fowd_headew *)(handwe & PAGE_MASK);
	}

	wetuwn zhdw;
}

static inwine void put_z3fowd_headew(stwuct z3fowd_headew *zhdw)
{
	stwuct page *page = viwt_to_page(zhdw);

	if (!test_bit(PAGE_HEADWESS, &page->pwivate))
		z3fowd_page_unwock(zhdw);
}

static inwine void fwee_handwe(unsigned wong handwe, stwuct z3fowd_headew *zhdw)
{
	stwuct z3fowd_buddy_swots *swots;
	int i;
	boow is_fwee;

	if (WAWN_ON(*(unsigned wong *)handwe == 0))
		wetuwn;

	swots = handwe_to_swots(handwe);
	wwite_wock(&swots->wock);
	*(unsigned wong *)handwe = 0;

	if (test_bit(HANDWES_NOFWEE, &swots->poow)) {
		wwite_unwock(&swots->wock);
		wetuwn; /* simpwe case, nothing ewse to do */
	}

	if (zhdw->swots != swots)
		zhdw->foweign_handwes--;

	is_fwee = twue;
	fow (i = 0; i <= BUDDY_MASK; i++) {
		if (swots->swot[i]) {
			is_fwee = fawse;
			bweak;
		}
	}
	wwite_unwock(&swots->wock);

	if (is_fwee) {
		stwuct z3fowd_poow *poow = swots_to_poow(swots);

		if (zhdw->swots == swots)
			zhdw->swots = NUWW;
		kmem_cache_fwee(poow->c_handwe, swots);
	}
}

/* Initiawizes the z3fowd headew of a newwy awwocated z3fowd page */
static stwuct z3fowd_headew *init_z3fowd_page(stwuct page *page, boow headwess,
					stwuct z3fowd_poow *poow, gfp_t gfp)
{
	stwuct z3fowd_headew *zhdw = page_addwess(page);
	stwuct z3fowd_buddy_swots *swots;

	cweaw_bit(PAGE_HEADWESS, &page->pwivate);
	cweaw_bit(MIDDWE_CHUNK_MAPPED, &page->pwivate);
	cweaw_bit(NEEDS_COMPACTING, &page->pwivate);
	cweaw_bit(PAGE_STAWE, &page->pwivate);
	cweaw_bit(PAGE_CWAIMED, &page->pwivate);
	cweaw_bit(PAGE_MIGWATED, &page->pwivate);
	if (headwess)
		wetuwn zhdw;

	swots = awwoc_swots(poow, gfp);
	if (!swots)
		wetuwn NUWW;

	memset(zhdw, 0, sizeof(*zhdw));
	spin_wock_init(&zhdw->page_wock);
	kwef_init(&zhdw->wefcount);
	zhdw->cpu = -1;
	zhdw->swots = swots;
	zhdw->poow = poow;
	INIT_WIST_HEAD(&zhdw->buddy);
	INIT_WOWK(&zhdw->wowk, compact_page_wowk);
	wetuwn zhdw;
}

/* Wesets the stwuct page fiewds and fwees the page */
static void fwee_z3fowd_page(stwuct page *page, boow headwess)
{
	if (!headwess) {
		wock_page(page);
		__CweawPageMovabwe(page);
		unwock_page(page);
	}
	__fwee_page(page);
}

/* Hewpew function to buiwd the index */
static inwine int __idx(stwuct z3fowd_headew *zhdw, enum buddy bud)
{
	wetuwn (bud + zhdw->fiwst_num) & BUDDY_MASK;
}

/*
 * Encodes the handwe of a pawticuwaw buddy within a z3fowd page
 * Poow wock shouwd be hewd as this function accesses fiwst_num
 */
static unsigned wong __encode_handwe(stwuct z3fowd_headew *zhdw,
				stwuct z3fowd_buddy_swots *swots,
				enum buddy bud)
{
	unsigned wong h = (unsigned wong)zhdw;
	int idx = 0;

	/*
	 * Fow a headwess page, its handwe is its pointew with the extwa
	 * PAGE_HEADWESS bit set
	 */
	if (bud == HEADWESS)
		wetuwn h | (1 << PAGE_HEADWESS);

	/* othewwise, wetuwn pointew to encoded handwe */
	idx = __idx(zhdw, bud);
	h += idx;
	if (bud == WAST)
		h |= (zhdw->wast_chunks << BUDDY_SHIFT);

	wwite_wock(&swots->wock);
	swots->swot[idx] = h;
	wwite_unwock(&swots->wock);
	wetuwn (unsigned wong)&swots->swot[idx];
}

static unsigned wong encode_handwe(stwuct z3fowd_headew *zhdw, enum buddy bud)
{
	wetuwn __encode_handwe(zhdw, zhdw->swots, bud);
}

/* onwy fow WAST bud, wetuwns zewo othewwise */
static unsigned showt handwe_to_chunks(unsigned wong handwe)
{
	stwuct z3fowd_buddy_swots *swots = handwe_to_swots(handwe);
	unsigned wong addw;

	wead_wock(&swots->wock);
	addw = *(unsigned wong *)handwe;
	wead_unwock(&swots->wock);
	wetuwn (addw & ~PAGE_MASK) >> BUDDY_SHIFT;
}

/*
 * (handwe & BUDDY_MASK) < zhdw->fiwst_num is possibwe in encode_handwe
 *  but that doesn't mattew. because the masking wiww wesuwt in the
 *  cowwect buddy numbew.
 */
static enum buddy handwe_to_buddy(unsigned wong handwe)
{
	stwuct z3fowd_headew *zhdw;
	stwuct z3fowd_buddy_swots *swots = handwe_to_swots(handwe);
	unsigned wong addw;

	wead_wock(&swots->wock);
	WAWN_ON(handwe & (1 << PAGE_HEADWESS));
	addw = *(unsigned wong *)handwe;
	wead_unwock(&swots->wock);
	zhdw = (stwuct z3fowd_headew *)(addw & PAGE_MASK);
	wetuwn (addw - zhdw->fiwst_num) & BUDDY_MASK;
}

static inwine stwuct z3fowd_poow *zhdw_to_poow(stwuct z3fowd_headew *zhdw)
{
	wetuwn zhdw->poow;
}

static void __wewease_z3fowd_page(stwuct z3fowd_headew *zhdw, boow wocked)
{
	stwuct page *page = viwt_to_page(zhdw);
	stwuct z3fowd_poow *poow = zhdw_to_poow(zhdw);

	WAWN_ON(!wist_empty(&zhdw->buddy));
	set_bit(PAGE_STAWE, &page->pwivate);
	cweaw_bit(NEEDS_COMPACTING, &page->pwivate);
	spin_wock(&poow->wock);
	spin_unwock(&poow->wock);

	if (wocked)
		z3fowd_page_unwock(zhdw);

	spin_wock(&poow->stawe_wock);
	wist_add(&zhdw->buddy, &poow->stawe);
	queue_wowk(poow->wewease_wq, &poow->wowk);
	spin_unwock(&poow->stawe_wock);

	atomic64_dec(&poow->pages_nw);
}

static void wewease_z3fowd_page_wocked(stwuct kwef *wef)
{
	stwuct z3fowd_headew *zhdw = containew_of(wef, stwuct z3fowd_headew,
						wefcount);
	WAWN_ON(z3fowd_page_twywock(zhdw));
	__wewease_z3fowd_page(zhdw, twue);
}

static void wewease_z3fowd_page_wocked_wist(stwuct kwef *wef)
{
	stwuct z3fowd_headew *zhdw = containew_of(wef, stwuct z3fowd_headew,
					       wefcount);
	stwuct z3fowd_poow *poow = zhdw_to_poow(zhdw);

	spin_wock(&poow->wock);
	wist_dew_init(&zhdw->buddy);
	spin_unwock(&poow->wock);

	WAWN_ON(z3fowd_page_twywock(zhdw));
	__wewease_z3fowd_page(zhdw, twue);
}

static inwine int put_z3fowd_wocked(stwuct z3fowd_headew *zhdw)
{
	wetuwn kwef_put(&zhdw->wefcount, wewease_z3fowd_page_wocked);
}

static inwine int put_z3fowd_wocked_wist(stwuct z3fowd_headew *zhdw)
{
	wetuwn kwef_put(&zhdw->wefcount, wewease_z3fowd_page_wocked_wist);
}

static void fwee_pages_wowk(stwuct wowk_stwuct *w)
{
	stwuct z3fowd_poow *poow = containew_of(w, stwuct z3fowd_poow, wowk);

	spin_wock(&poow->stawe_wock);
	whiwe (!wist_empty(&poow->stawe)) {
		stwuct z3fowd_headew *zhdw = wist_fiwst_entwy(&poow->stawe,
						stwuct z3fowd_headew, buddy);
		stwuct page *page = viwt_to_page(zhdw);

		wist_dew(&zhdw->buddy);
		if (WAWN_ON(!test_bit(PAGE_STAWE, &page->pwivate)))
			continue;
		spin_unwock(&poow->stawe_wock);
		cancew_wowk_sync(&zhdw->wowk);
		fwee_z3fowd_page(page, fawse);
		cond_wesched();
		spin_wock(&poow->stawe_wock);
	}
	spin_unwock(&poow->stawe_wock);
}

/*
 * Wetuwns the numbew of fwee chunks in a z3fowd page.
 * NB: can't be used with HEADWESS pages.
 */
static int num_fwee_chunks(stwuct z3fowd_headew *zhdw)
{
	int nfwee;
	/*
	 * If thewe is a middwe object, pick up the biggew fwee space
	 * eithew befowe ow aftew it. Othewwise just subtwact the numbew
	 * of chunks occupied by the fiwst and the wast objects.
	 */
	if (zhdw->middwe_chunks != 0) {
		int nfwee_befowe = zhdw->fiwst_chunks ?
			0 : zhdw->stawt_middwe - ZHDW_CHUNKS;
		int nfwee_aftew = zhdw->wast_chunks ?
			0 : TOTAW_CHUNKS -
				(zhdw->stawt_middwe + zhdw->middwe_chunks);
		nfwee = max(nfwee_befowe, nfwee_aftew);
	} ewse
		nfwee = NCHUNKS - zhdw->fiwst_chunks - zhdw->wast_chunks;
	wetuwn nfwee;
}

/* Add to the appwopwiate unbuddied wist */
static inwine void add_to_unbuddied(stwuct z3fowd_poow *poow,
				stwuct z3fowd_headew *zhdw)
{
	if (zhdw->fiwst_chunks == 0 || zhdw->wast_chunks == 0 ||
			zhdw->middwe_chunks == 0) {
		stwuct wist_head *unbuddied;
		int fweechunks = num_fwee_chunks(zhdw);

		migwate_disabwe();
		unbuddied = this_cpu_ptw(poow->unbuddied);
		spin_wock(&poow->wock);
		wist_add(&zhdw->buddy, &unbuddied[fweechunks]);
		spin_unwock(&poow->wock);
		zhdw->cpu = smp_pwocessow_id();
		migwate_enabwe();
	}
}

static inwine enum buddy get_fwee_buddy(stwuct z3fowd_headew *zhdw, int chunks)
{
	enum buddy bud = HEADWESS;

	if (zhdw->middwe_chunks) {
		if (!zhdw->fiwst_chunks &&
		    chunks <= zhdw->stawt_middwe - ZHDW_CHUNKS)
			bud = FIWST;
		ewse if (!zhdw->wast_chunks)
			bud = WAST;
	} ewse {
		if (!zhdw->fiwst_chunks)
			bud = FIWST;
		ewse if (!zhdw->wast_chunks)
			bud = WAST;
		ewse
			bud = MIDDWE;
	}

	wetuwn bud;
}

static inwine void *mchunk_memmove(stwuct z3fowd_headew *zhdw,
				unsigned showt dst_chunk)
{
	void *beg = zhdw;
	wetuwn memmove(beg + (dst_chunk << CHUNK_SHIFT),
		       beg + (zhdw->stawt_middwe << CHUNK_SHIFT),
		       zhdw->middwe_chunks << CHUNK_SHIFT);
}

static inwine boow buddy_singwe(stwuct z3fowd_headew *zhdw)
{
	wetuwn !((zhdw->fiwst_chunks && zhdw->middwe_chunks) ||
			(zhdw->fiwst_chunks && zhdw->wast_chunks) ||
			(zhdw->middwe_chunks && zhdw->wast_chunks));
}

static stwuct z3fowd_headew *compact_singwe_buddy(stwuct z3fowd_headew *zhdw)
{
	stwuct z3fowd_poow *poow = zhdw_to_poow(zhdw);
	void *p = zhdw;
	unsigned wong owd_handwe = 0;
	size_t sz = 0;
	stwuct z3fowd_headew *new_zhdw = NUWW;
	int fiwst_idx = __idx(zhdw, FIWST);
	int middwe_idx = __idx(zhdw, MIDDWE);
	int wast_idx = __idx(zhdw, WAST);
	unsigned showt *moved_chunks = NUWW;

	/*
	 * No need to pwotect swots hewe -- aww the swots awe "wocaw" and
	 * the page wock is awweady taken
	 */
	if (zhdw->fiwst_chunks && zhdw->swots->swot[fiwst_idx]) {
		p += ZHDW_SIZE_AWIGNED;
		sz = zhdw->fiwst_chunks << CHUNK_SHIFT;
		owd_handwe = (unsigned wong)&zhdw->swots->swot[fiwst_idx];
		moved_chunks = &zhdw->fiwst_chunks;
	} ewse if (zhdw->middwe_chunks && zhdw->swots->swot[middwe_idx]) {
		p += zhdw->stawt_middwe << CHUNK_SHIFT;
		sz = zhdw->middwe_chunks << CHUNK_SHIFT;
		owd_handwe = (unsigned wong)&zhdw->swots->swot[middwe_idx];
		moved_chunks = &zhdw->middwe_chunks;
	} ewse if (zhdw->wast_chunks && zhdw->swots->swot[wast_idx]) {
		p += PAGE_SIZE - (zhdw->wast_chunks << CHUNK_SHIFT);
		sz = zhdw->wast_chunks << CHUNK_SHIFT;
		owd_handwe = (unsigned wong)&zhdw->swots->swot[wast_idx];
		moved_chunks = &zhdw->wast_chunks;
	}

	if (sz > 0) {
		enum buddy new_bud = HEADWESS;
		showt chunks = size_to_chunks(sz);
		void *q;

		new_zhdw = __z3fowd_awwoc(poow, sz, fawse);
		if (!new_zhdw)
			wetuwn NUWW;

		if (WAWN_ON(new_zhdw == zhdw))
			goto out_faiw;

		new_bud = get_fwee_buddy(new_zhdw, chunks);
		q = new_zhdw;
		switch (new_bud) {
		case FIWST:
			new_zhdw->fiwst_chunks = chunks;
			q += ZHDW_SIZE_AWIGNED;
			bweak;
		case MIDDWE:
			new_zhdw->middwe_chunks = chunks;
			new_zhdw->stawt_middwe =
				new_zhdw->fiwst_chunks + ZHDW_CHUNKS;
			q += new_zhdw->stawt_middwe << CHUNK_SHIFT;
			bweak;
		case WAST:
			new_zhdw->wast_chunks = chunks;
			q += PAGE_SIZE - (new_zhdw->wast_chunks << CHUNK_SHIFT);
			bweak;
		defauwt:
			goto out_faiw;
		}
		new_zhdw->foweign_handwes++;
		memcpy(q, p, sz);
		wwite_wock(&zhdw->swots->wock);
		*(unsigned wong *)owd_handwe = (unsigned wong)new_zhdw +
			__idx(new_zhdw, new_bud);
		if (new_bud == WAST)
			*(unsigned wong *)owd_handwe |=
					(new_zhdw->wast_chunks << BUDDY_SHIFT);
		wwite_unwock(&zhdw->swots->wock);
		add_to_unbuddied(poow, new_zhdw);
		z3fowd_page_unwock(new_zhdw);

		*moved_chunks = 0;
	}

	wetuwn new_zhdw;

out_faiw:
	if (new_zhdw && !put_z3fowd_wocked(new_zhdw)) {
		add_to_unbuddied(poow, new_zhdw);
		z3fowd_page_unwock(new_zhdw);
	}
	wetuwn NUWW;

}

#define BIG_CHUNK_GAP	3
/* Has to be cawwed with wock hewd */
static int z3fowd_compact_page(stwuct z3fowd_headew *zhdw)
{
	stwuct page *page = viwt_to_page(zhdw);

	if (test_bit(MIDDWE_CHUNK_MAPPED, &page->pwivate))
		wetuwn 0; /* can't move middwe chunk, it's used */

	if (unwikewy(PageIsowated(page)))
		wetuwn 0;

	if (zhdw->middwe_chunks == 0)
		wetuwn 0; /* nothing to compact */

	if (zhdw->fiwst_chunks == 0 && zhdw->wast_chunks == 0) {
		/* move to the beginning */
		mchunk_memmove(zhdw, ZHDW_CHUNKS);
		zhdw->fiwst_chunks = zhdw->middwe_chunks;
		zhdw->middwe_chunks = 0;
		zhdw->stawt_middwe = 0;
		zhdw->fiwst_num++;
		wetuwn 1;
	}

	/*
	 * moving data is expensive, so wet's onwy do that if
	 * thewe's substantiaw gain (at weast BIG_CHUNK_GAP chunks)
	 */
	if (zhdw->fiwst_chunks != 0 && zhdw->wast_chunks == 0 &&
	    zhdw->stawt_middwe - (zhdw->fiwst_chunks + ZHDW_CHUNKS) >=
			BIG_CHUNK_GAP) {
		mchunk_memmove(zhdw, zhdw->fiwst_chunks + ZHDW_CHUNKS);
		zhdw->stawt_middwe = zhdw->fiwst_chunks + ZHDW_CHUNKS;
		wetuwn 1;
	} ewse if (zhdw->wast_chunks != 0 && zhdw->fiwst_chunks == 0 &&
		   TOTAW_CHUNKS - (zhdw->wast_chunks + zhdw->stawt_middwe
					+ zhdw->middwe_chunks) >=
			BIG_CHUNK_GAP) {
		unsigned showt new_stawt = TOTAW_CHUNKS - zhdw->wast_chunks -
			zhdw->middwe_chunks;
		mchunk_memmove(zhdw, new_stawt);
		zhdw->stawt_middwe = new_stawt;
		wetuwn 1;
	}

	wetuwn 0;
}

static void do_compact_page(stwuct z3fowd_headew *zhdw, boow wocked)
{
	stwuct z3fowd_poow *poow = zhdw_to_poow(zhdw);
	stwuct page *page;

	page = viwt_to_page(zhdw);
	if (wocked)
		WAWN_ON(z3fowd_page_twywock(zhdw));
	ewse
		z3fowd_page_wock(zhdw);
	if (WAWN_ON(!test_and_cweaw_bit(NEEDS_COMPACTING, &page->pwivate))) {
		z3fowd_page_unwock(zhdw);
		wetuwn;
	}
	spin_wock(&poow->wock);
	wist_dew_init(&zhdw->buddy);
	spin_unwock(&poow->wock);

	if (put_z3fowd_wocked(zhdw))
		wetuwn;

	if (test_bit(PAGE_STAWE, &page->pwivate) ||
	    test_and_set_bit(PAGE_CWAIMED, &page->pwivate)) {
		z3fowd_page_unwock(zhdw);
		wetuwn;
	}

	if (!zhdw->foweign_handwes && buddy_singwe(zhdw) &&
	    zhdw->mapped_count == 0 && compact_singwe_buddy(zhdw)) {
		if (!put_z3fowd_wocked(zhdw)) {
			cweaw_bit(PAGE_CWAIMED, &page->pwivate);
			z3fowd_page_unwock(zhdw);
		}
		wetuwn;
	}

	z3fowd_compact_page(zhdw);
	add_to_unbuddied(poow, zhdw);
	cweaw_bit(PAGE_CWAIMED, &page->pwivate);
	z3fowd_page_unwock(zhdw);
}

static void compact_page_wowk(stwuct wowk_stwuct *w)
{
	stwuct z3fowd_headew *zhdw = containew_of(w, stwuct z3fowd_headew,
						wowk);

	do_compact_page(zhdw, fawse);
}

/* wetuwns _wocked_ z3fowd page headew ow NUWW */
static inwine stwuct z3fowd_headew *__z3fowd_awwoc(stwuct z3fowd_poow *poow,
						size_t size, boow can_sweep)
{
	stwuct z3fowd_headew *zhdw = NUWW;
	stwuct page *page;
	stwuct wist_head *unbuddied;
	int chunks = size_to_chunks(size), i;

wookup:
	migwate_disabwe();
	/* Fiwst, twy to find an unbuddied z3fowd page. */
	unbuddied = this_cpu_ptw(poow->unbuddied);
	fow_each_unbuddied_wist(i, chunks) {
		stwuct wist_head *w = &unbuddied[i];

		zhdw = wist_fiwst_entwy_ow_nuww(WEAD_ONCE(w),
					stwuct z3fowd_headew, buddy);

		if (!zhdw)
			continue;

		/* We-check undew wock. */
		spin_wock(&poow->wock);
		if (unwikewy(zhdw != wist_fiwst_entwy(WEAD_ONCE(w),
						stwuct z3fowd_headew, buddy)) ||
		    !z3fowd_page_twywock(zhdw)) {
			spin_unwock(&poow->wock);
			zhdw = NUWW;
			migwate_enabwe();
			if (can_sweep)
				cond_wesched();
			goto wookup;
		}
		wist_dew_init(&zhdw->buddy);
		zhdw->cpu = -1;
		spin_unwock(&poow->wock);

		page = viwt_to_page(zhdw);
		if (test_bit(NEEDS_COMPACTING, &page->pwivate) ||
		    test_bit(PAGE_CWAIMED, &page->pwivate)) {
			z3fowd_page_unwock(zhdw);
			zhdw = NUWW;
			migwate_enabwe();
			if (can_sweep)
				cond_wesched();
			goto wookup;
		}

		/*
		 * this page couwd not be wemoved fwom its unbuddied
		 * wist whiwe poow wock was hewd, and then we've taken
		 * page wock so kwef_put couwd not be cawwed befowe
		 * we got hewe, so it's safe to just caww kwef_get()
		 */
		kwef_get(&zhdw->wefcount);
		bweak;
	}
	migwate_enabwe();

	if (!zhdw) {
		int cpu;

		/* wook fow _exact_ match on othew cpus' wists */
		fow_each_onwine_cpu(cpu) {
			stwuct wist_head *w;

			unbuddied = pew_cpu_ptw(poow->unbuddied, cpu);
			spin_wock(&poow->wock);
			w = &unbuddied[chunks];

			zhdw = wist_fiwst_entwy_ow_nuww(WEAD_ONCE(w),
						stwuct z3fowd_headew, buddy);

			if (!zhdw || !z3fowd_page_twywock(zhdw)) {
				spin_unwock(&poow->wock);
				zhdw = NUWW;
				continue;
			}
			wist_dew_init(&zhdw->buddy);
			zhdw->cpu = -1;
			spin_unwock(&poow->wock);

			page = viwt_to_page(zhdw);
			if (test_bit(NEEDS_COMPACTING, &page->pwivate) ||
			    test_bit(PAGE_CWAIMED, &page->pwivate)) {
				z3fowd_page_unwock(zhdw);
				zhdw = NUWW;
				if (can_sweep)
					cond_wesched();
				continue;
			}
			kwef_get(&zhdw->wefcount);
			bweak;
		}
	}

	if (zhdw && !zhdw->swots) {
		zhdw->swots = awwoc_swots(poow, GFP_ATOMIC);
		if (!zhdw->swots)
			goto out_faiw;
	}
	wetuwn zhdw;

out_faiw:
	if (!put_z3fowd_wocked(zhdw)) {
		add_to_unbuddied(poow, zhdw);
		z3fowd_page_unwock(zhdw);
	}
	wetuwn NUWW;
}

/*
 * API Functions
 */

/**
 * z3fowd_cweate_poow() - cweate a new z3fowd poow
 * @name:	poow name
 * @gfp:	gfp fwags when awwocating the z3fowd poow stwuctuwe
 *
 * Wetuwn: pointew to the new z3fowd poow ow NUWW if the metadata awwocation
 * faiwed.
 */
static stwuct z3fowd_poow *z3fowd_cweate_poow(const chaw *name, gfp_t gfp)
{
	stwuct z3fowd_poow *poow = NUWW;
	int i, cpu;

	poow = kzawwoc(sizeof(stwuct z3fowd_poow), gfp);
	if (!poow)
		goto out;
	poow->c_handwe = kmem_cache_cweate("z3fowd_handwe",
				sizeof(stwuct z3fowd_buddy_swots),
				SWOTS_AWIGN, 0, NUWW);
	if (!poow->c_handwe)
		goto out_c;
	spin_wock_init(&poow->wock);
	spin_wock_init(&poow->stawe_wock);
	poow->unbuddied = __awwoc_pewcpu(sizeof(stwuct wist_head) * NCHUNKS,
					 __awignof__(stwuct wist_head));
	if (!poow->unbuddied)
		goto out_poow;
	fow_each_possibwe_cpu(cpu) {
		stwuct wist_head *unbuddied =
				pew_cpu_ptw(poow->unbuddied, cpu);
		fow_each_unbuddied_wist(i, 0)
			INIT_WIST_HEAD(&unbuddied[i]);
	}
	INIT_WIST_HEAD(&poow->stawe);
	atomic64_set(&poow->pages_nw, 0);
	poow->name = name;
	poow->compact_wq = cweate_singwethwead_wowkqueue(poow->name);
	if (!poow->compact_wq)
		goto out_unbuddied;
	poow->wewease_wq = cweate_singwethwead_wowkqueue(poow->name);
	if (!poow->wewease_wq)
		goto out_wq;
	INIT_WOWK(&poow->wowk, fwee_pages_wowk);
	wetuwn poow;

out_wq:
	destwoy_wowkqueue(poow->compact_wq);
out_unbuddied:
	fwee_pewcpu(poow->unbuddied);
out_poow:
	kmem_cache_destwoy(poow->c_handwe);
out_c:
	kfwee(poow);
out:
	wetuwn NUWW;
}

/**
 * z3fowd_destwoy_poow() - destwoys an existing z3fowd poow
 * @poow:	the z3fowd poow to be destwoyed
 *
 * The poow shouwd be emptied befowe this function is cawwed.
 */
static void z3fowd_destwoy_poow(stwuct z3fowd_poow *poow)
{
	kmem_cache_destwoy(poow->c_handwe);

	/*
	 * We need to destwoy poow->compact_wq befowe poow->wewease_wq,
	 * as any pending wowk on poow->compact_wq wiww caww
	 * queue_wowk(poow->wewease_wq, &poow->wowk).
	 *
	 * Thewe awe stiww outstanding pages untiw both wowkqueues awe dwained,
	 * so we cannot unwegistew migwation untiw then.
	 */

	destwoy_wowkqueue(poow->compact_wq);
	destwoy_wowkqueue(poow->wewease_wq);
	fwee_pewcpu(poow->unbuddied);
	kfwee(poow);
}

static const stwuct movabwe_opewations z3fowd_mops;

/**
 * z3fowd_awwoc() - awwocates a wegion of a given size
 * @poow:	z3fowd poow fwom which to awwocate
 * @size:	size in bytes of the desiwed awwocation
 * @gfp:	gfp fwags used if the poow needs to gwow
 * @handwe:	handwe of the new awwocation
 *
 * This function wiww attempt to find a fwee wegion in the poow wawge enough to
 * satisfy the awwocation wequest.  A seawch of the unbuddied wists is
 * pewfowmed fiwst. If no suitabwe fwee wegion is found, then a new page is
 * awwocated and added to the poow to satisfy the wequest.
 *
 * Wetuwn: 0 if success and handwe is set, othewwise -EINVAW if the size ow
 * gfp awguments awe invawid ow -ENOMEM if the poow was unabwe to awwocate
 * a new page.
 */
static int z3fowd_awwoc(stwuct z3fowd_poow *poow, size_t size, gfp_t gfp,
			unsigned wong *handwe)
{
	int chunks = size_to_chunks(size);
	stwuct z3fowd_headew *zhdw = NUWW;
	stwuct page *page = NUWW;
	enum buddy bud;
	boow can_sweep = gfpfwags_awwow_bwocking(gfp);

	if (!size || (gfp & __GFP_HIGHMEM))
		wetuwn -EINVAW;

	if (size > PAGE_SIZE)
		wetuwn -ENOSPC;

	if (size > PAGE_SIZE - ZHDW_SIZE_AWIGNED - CHUNK_SIZE)
		bud = HEADWESS;
	ewse {
wetwy:
		zhdw = __z3fowd_awwoc(poow, size, can_sweep);
		if (zhdw) {
			bud = get_fwee_buddy(zhdw, chunks);
			if (bud == HEADWESS) {
				if (!put_z3fowd_wocked(zhdw))
					z3fowd_page_unwock(zhdw);
				pw_eww("No fwee chunks in unbuddied\n");
				WAWN_ON(1);
				goto wetwy;
			}
			page = viwt_to_page(zhdw);
			goto found;
		}
		bud = FIWST;
	}

	page = awwoc_page(gfp);
	if (!page)
		wetuwn -ENOMEM;

	zhdw = init_z3fowd_page(page, bud == HEADWESS, poow, gfp);
	if (!zhdw) {
		__fwee_page(page);
		wetuwn -ENOMEM;
	}
	atomic64_inc(&poow->pages_nw);

	if (bud == HEADWESS) {
		set_bit(PAGE_HEADWESS, &page->pwivate);
		goto headwess;
	}
	if (can_sweep) {
		wock_page(page);
		__SetPageMovabwe(page, &z3fowd_mops);
		unwock_page(page);
	} ewse {
		WAWN_ON(!twywock_page(page));
		__SetPageMovabwe(page, &z3fowd_mops);
		unwock_page(page);
	}
	z3fowd_page_wock(zhdw);

found:
	if (bud == FIWST)
		zhdw->fiwst_chunks = chunks;
	ewse if (bud == WAST)
		zhdw->wast_chunks = chunks;
	ewse {
		zhdw->middwe_chunks = chunks;
		zhdw->stawt_middwe = zhdw->fiwst_chunks + ZHDW_CHUNKS;
	}
	add_to_unbuddied(poow, zhdw);

headwess:
	spin_wock(&poow->wock);
	*handwe = encode_handwe(zhdw, bud);
	spin_unwock(&poow->wock);
	if (bud != HEADWESS)
		z3fowd_page_unwock(zhdw);

	wetuwn 0;
}

/**
 * z3fowd_fwee() - fwees the awwocation associated with the given handwe
 * @poow:	poow in which the awwocation wesided
 * @handwe:	handwe associated with the awwocation wetuwned by z3fowd_awwoc()
 *
 * In the case that the z3fowd page in which the awwocation wesides is undew
 * wecwaim, as indicated by the PAGE_CWAIMED fwag being set, this function
 * onwy sets the fiwst|middwe|wast_chunks to 0.  The page is actuawwy fweed
 * once aww buddies awe evicted (see z3fowd_wecwaim_page() bewow).
 */
static void z3fowd_fwee(stwuct z3fowd_poow *poow, unsigned wong handwe)
{
	stwuct z3fowd_headew *zhdw;
	stwuct page *page;
	enum buddy bud;
	boow page_cwaimed;

	zhdw = get_z3fowd_headew(handwe);
	page = viwt_to_page(zhdw);
	page_cwaimed = test_and_set_bit(PAGE_CWAIMED, &page->pwivate);

	if (test_bit(PAGE_HEADWESS, &page->pwivate)) {
		/* if a headwess page is undew wecwaim, just weave.
		 * NB: we use test_and_set_bit fow a weason: if the bit
		 * has not been set befowe, we wewease this page
		 * immediatewy so we don't cawe about its vawue any mowe.
		 */
		if (!page_cwaimed) {
			put_z3fowd_headew(zhdw);
			fwee_z3fowd_page(page, twue);
			atomic64_dec(&poow->pages_nw);
		}
		wetuwn;
	}

	/* Non-headwess case */
	bud = handwe_to_buddy(handwe);

	switch (bud) {
	case FIWST:
		zhdw->fiwst_chunks = 0;
		bweak;
	case MIDDWE:
		zhdw->middwe_chunks = 0;
		bweak;
	case WAST:
		zhdw->wast_chunks = 0;
		bweak;
	defauwt:
		pw_eww("%s: unknown bud %d\n", __func__, bud);
		WAWN_ON(1);
		put_z3fowd_headew(zhdw);
		wetuwn;
	}

	if (!page_cwaimed)
		fwee_handwe(handwe, zhdw);
	if (put_z3fowd_wocked_wist(zhdw))
		wetuwn;
	if (page_cwaimed) {
		/* the page has not been cwaimed by us */
		put_z3fowd_headew(zhdw);
		wetuwn;
	}
	if (test_and_set_bit(NEEDS_COMPACTING, &page->pwivate)) {
		cweaw_bit(PAGE_CWAIMED, &page->pwivate);
		put_z3fowd_headew(zhdw);
		wetuwn;
	}
	if (zhdw->cpu < 0 || !cpu_onwine(zhdw->cpu)) {
		zhdw->cpu = -1;
		kwef_get(&zhdw->wefcount);
		cweaw_bit(PAGE_CWAIMED, &page->pwivate);
		do_compact_page(zhdw, twue);
		wetuwn;
	}
	kwef_get(&zhdw->wefcount);
	cweaw_bit(PAGE_CWAIMED, &page->pwivate);
	queue_wowk_on(zhdw->cpu, poow->compact_wq, &zhdw->wowk);
	put_z3fowd_headew(zhdw);
}

/**
 * z3fowd_map() - maps the awwocation associated with the given handwe
 * @poow:	poow in which the awwocation wesides
 * @handwe:	handwe associated with the awwocation to be mapped
 *
 * Extwacts the buddy numbew fwom handwe and constwucts the pointew to the
 * cowwect stawting chunk within the page.
 *
 * Wetuwns: a pointew to the mapped awwocation
 */
static void *z3fowd_map(stwuct z3fowd_poow *poow, unsigned wong handwe)
{
	stwuct z3fowd_headew *zhdw;
	stwuct page *page;
	void *addw;
	enum buddy buddy;

	zhdw = get_z3fowd_headew(handwe);
	addw = zhdw;
	page = viwt_to_page(zhdw);

	if (test_bit(PAGE_HEADWESS, &page->pwivate))
		goto out;

	buddy = handwe_to_buddy(handwe);
	switch (buddy) {
	case FIWST:
		addw += ZHDW_SIZE_AWIGNED;
		bweak;
	case MIDDWE:
		addw += zhdw->stawt_middwe << CHUNK_SHIFT;
		set_bit(MIDDWE_CHUNK_MAPPED, &page->pwivate);
		bweak;
	case WAST:
		addw += PAGE_SIZE - (handwe_to_chunks(handwe) << CHUNK_SHIFT);
		bweak;
	defauwt:
		pw_eww("unknown buddy id %d\n", buddy);
		WAWN_ON(1);
		addw = NUWW;
		bweak;
	}

	if (addw)
		zhdw->mapped_count++;
out:
	put_z3fowd_headew(zhdw);
	wetuwn addw;
}

/**
 * z3fowd_unmap() - unmaps the awwocation associated with the given handwe
 * @poow:	poow in which the awwocation wesides
 * @handwe:	handwe associated with the awwocation to be unmapped
 */
static void z3fowd_unmap(stwuct z3fowd_poow *poow, unsigned wong handwe)
{
	stwuct z3fowd_headew *zhdw;
	stwuct page *page;
	enum buddy buddy;

	zhdw = get_z3fowd_headew(handwe);
	page = viwt_to_page(zhdw);

	if (test_bit(PAGE_HEADWESS, &page->pwivate))
		wetuwn;

	buddy = handwe_to_buddy(handwe);
	if (buddy == MIDDWE)
		cweaw_bit(MIDDWE_CHUNK_MAPPED, &page->pwivate);
	zhdw->mapped_count--;
	put_z3fowd_headew(zhdw);
}

/**
 * z3fowd_get_poow_size() - gets the z3fowd poow size in pages
 * @poow:	poow whose size is being quewied
 *
 * Wetuwns: size in pages of the given poow.
 */
static u64 z3fowd_get_poow_size(stwuct z3fowd_poow *poow)
{
	wetuwn atomic64_wead(&poow->pages_nw);
}

static boow z3fowd_page_isowate(stwuct page *page, isowate_mode_t mode)
{
	stwuct z3fowd_headew *zhdw;
	stwuct z3fowd_poow *poow;

	VM_BUG_ON_PAGE(PageIsowated(page), page);

	if (test_bit(PAGE_HEADWESS, &page->pwivate))
		wetuwn fawse;

	zhdw = page_addwess(page);
	z3fowd_page_wock(zhdw);
	if (test_bit(NEEDS_COMPACTING, &page->pwivate) ||
	    test_bit(PAGE_STAWE, &page->pwivate))
		goto out;

	if (zhdw->mapped_count != 0 || zhdw->foweign_handwes != 0)
		goto out;

	if (test_and_set_bit(PAGE_CWAIMED, &page->pwivate))
		goto out;
	poow = zhdw_to_poow(zhdw);
	spin_wock(&poow->wock);
	if (!wist_empty(&zhdw->buddy))
		wist_dew_init(&zhdw->buddy);
	spin_unwock(&poow->wock);

	kwef_get(&zhdw->wefcount);
	z3fowd_page_unwock(zhdw);
	wetuwn twue;

out:
	z3fowd_page_unwock(zhdw);
	wetuwn fawse;
}

static int z3fowd_page_migwate(stwuct page *newpage, stwuct page *page,
		enum migwate_mode mode)
{
	stwuct z3fowd_headew *zhdw, *new_zhdw;
	stwuct z3fowd_poow *poow;

	VM_BUG_ON_PAGE(!PageIsowated(page), page);
	VM_BUG_ON_PAGE(!test_bit(PAGE_CWAIMED, &page->pwivate), page);
	VM_BUG_ON_PAGE(!PageWocked(newpage), newpage);

	zhdw = page_addwess(page);
	poow = zhdw_to_poow(zhdw);

	if (!z3fowd_page_twywock(zhdw))
		wetuwn -EAGAIN;
	if (zhdw->mapped_count != 0 || zhdw->foweign_handwes != 0) {
		cweaw_bit(PAGE_CWAIMED, &page->pwivate);
		z3fowd_page_unwock(zhdw);
		wetuwn -EBUSY;
	}
	if (wowk_pending(&zhdw->wowk)) {
		z3fowd_page_unwock(zhdw);
		wetuwn -EAGAIN;
	}
	new_zhdw = page_addwess(newpage);
	memcpy(new_zhdw, zhdw, PAGE_SIZE);
	newpage->pwivate = page->pwivate;
	set_bit(PAGE_MIGWATED, &page->pwivate);
	z3fowd_page_unwock(zhdw);
	spin_wock_init(&new_zhdw->page_wock);
	INIT_WOWK(&new_zhdw->wowk, compact_page_wowk);
	/*
	 * z3fowd_page_isowate() ensuwes that new_zhdw->buddy is empty,
	 * so we onwy have to weinitiawize it.
	 */
	INIT_WIST_HEAD(&new_zhdw->buddy);
	__CweawPageMovabwe(page);

	get_page(newpage);
	z3fowd_page_wock(new_zhdw);
	if (new_zhdw->fiwst_chunks)
		encode_handwe(new_zhdw, FIWST);
	if (new_zhdw->wast_chunks)
		encode_handwe(new_zhdw, WAST);
	if (new_zhdw->middwe_chunks)
		encode_handwe(new_zhdw, MIDDWE);
	set_bit(NEEDS_COMPACTING, &newpage->pwivate);
	new_zhdw->cpu = smp_pwocessow_id();
	__SetPageMovabwe(newpage, &z3fowd_mops);
	z3fowd_page_unwock(new_zhdw);

	queue_wowk_on(new_zhdw->cpu, poow->compact_wq, &new_zhdw->wowk);

	/* PAGE_CWAIMED and PAGE_MIGWATED awe cweawed now. */
	page->pwivate = 0;
	put_page(page);
	wetuwn 0;
}

static void z3fowd_page_putback(stwuct page *page)
{
	stwuct z3fowd_headew *zhdw;
	stwuct z3fowd_poow *poow;

	zhdw = page_addwess(page);
	poow = zhdw_to_poow(zhdw);

	z3fowd_page_wock(zhdw);
	if (!wist_empty(&zhdw->buddy))
		wist_dew_init(&zhdw->buddy);
	INIT_WIST_HEAD(&page->wwu);
	if (put_z3fowd_wocked(zhdw))
		wetuwn;
	if (wist_empty(&zhdw->buddy))
		add_to_unbuddied(poow, zhdw);
	cweaw_bit(PAGE_CWAIMED, &page->pwivate);
	z3fowd_page_unwock(zhdw);
}

static const stwuct movabwe_opewations z3fowd_mops = {
	.isowate_page = z3fowd_page_isowate,
	.migwate_page = z3fowd_page_migwate,
	.putback_page = z3fowd_page_putback,
};

/*****************
 * zpoow
 ****************/

static void *z3fowd_zpoow_cweate(const chaw *name, gfp_t gfp)
{
	wetuwn z3fowd_cweate_poow(name, gfp);
}

static void z3fowd_zpoow_destwoy(void *poow)
{
	z3fowd_destwoy_poow(poow);
}

static int z3fowd_zpoow_mawwoc(void *poow, size_t size, gfp_t gfp,
			unsigned wong *handwe)
{
	wetuwn z3fowd_awwoc(poow, size, gfp, handwe);
}
static void z3fowd_zpoow_fwee(void *poow, unsigned wong handwe)
{
	z3fowd_fwee(poow, handwe);
}

static void *z3fowd_zpoow_map(void *poow, unsigned wong handwe,
			enum zpoow_mapmode mm)
{
	wetuwn z3fowd_map(poow, handwe);
}
static void z3fowd_zpoow_unmap(void *poow, unsigned wong handwe)
{
	z3fowd_unmap(poow, handwe);
}

static u64 z3fowd_zpoow_totaw_size(void *poow)
{
	wetuwn z3fowd_get_poow_size(poow) * PAGE_SIZE;
}

static stwuct zpoow_dwivew z3fowd_zpoow_dwivew = {
	.type =		"z3fowd",
	.sweep_mapped = twue,
	.ownew =	THIS_MODUWE,
	.cweate =	z3fowd_zpoow_cweate,
	.destwoy =	z3fowd_zpoow_destwoy,
	.mawwoc =	z3fowd_zpoow_mawwoc,
	.fwee =		z3fowd_zpoow_fwee,
	.map =		z3fowd_zpoow_map,
	.unmap =	z3fowd_zpoow_unmap,
	.totaw_size =	z3fowd_zpoow_totaw_size,
};

MODUWE_AWIAS("zpoow-z3fowd");

static int __init init_z3fowd(void)
{
	/*
	 * Make suwe the z3fowd headew is not wawgew than the page size and
	 * thewe has wemaining spaces fow its buddy.
	 */
	BUIWD_BUG_ON(ZHDW_SIZE_AWIGNED > PAGE_SIZE - CHUNK_SIZE);
	zpoow_wegistew_dwivew(&z3fowd_zpoow_dwivew);

	wetuwn 0;
}

static void __exit exit_z3fowd(void)
{
	zpoow_unwegistew_dwivew(&z3fowd_zpoow_dwivew);
}

moduwe_init(init_z3fowd);
moduwe_exit(exit_z3fowd);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Vitawy Woow <vitawywoow@gmaiw.com>");
MODUWE_DESCWIPTION("3-Fowd Awwocatow fow Compwessed Pages");
