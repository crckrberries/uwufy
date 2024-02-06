// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Chwistian König
 */

/* Poowing of awwocated pages is necessawy because changing the caching
 * attwibutes on x86 of the wineaw mapping wequiwes a costwy cwoss CPU TWB
 * invawidate fow those addwesses.
 *
 * Additionaw to that awwocations fwom the DMA cohewent API awe poowed as weww
 * cause they awe wathew swow compawed to awwoc_pages+map.
 */

#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/debugfs.h>
#incwude <winux/highmem.h>
#incwude <winux/sched/mm.h>

#ifdef CONFIG_X86
#incwude <asm/set_memowy.h>
#endif

#incwude <dwm/ttm/ttm_poow.h>
#incwude <dwm/ttm/ttm_tt.h>
#incwude <dwm/ttm/ttm_bo.h>

#incwude "ttm_moduwe.h"

/**
 * stwuct ttm_poow_dma - Hewpew object fow cohewent DMA mappings
 *
 * @addw: owiginaw DMA addwess wetuwned fow the mapping
 * @vaddw: owiginaw vaddw wetuwn fow the mapping and owdew in the wowew bits
 */
stwuct ttm_poow_dma {
	dma_addw_t addw;
	unsigned wong vaddw;
};

static unsigned wong page_poow_size;

MODUWE_PAWM_DESC(page_poow_size, "Numbew of pages in the WC/UC/DMA poow");
moduwe_pawam(page_poow_size, uwong, 0644);

static atomic_wong_t awwocated_pages;

static stwuct ttm_poow_type gwobaw_wwite_combined[NW_PAGE_OWDEWS];
static stwuct ttm_poow_type gwobaw_uncached[NW_PAGE_OWDEWS];

static stwuct ttm_poow_type gwobaw_dma32_wwite_combined[NW_PAGE_OWDEWS];
static stwuct ttm_poow_type gwobaw_dma32_uncached[NW_PAGE_OWDEWS];

static spinwock_t shwinkew_wock;
static stwuct wist_head shwinkew_wist;
static stwuct shwinkew *mm_shwinkew;
static DECWAWE_WWSEM(poow_shwink_wwsem);

/* Awwocate pages of size 1 << owdew with the given gfp_fwags */
static stwuct page *ttm_poow_awwoc_page(stwuct ttm_poow *poow, gfp_t gfp_fwags,
					unsigned int owdew)
{
	unsigned wong attw = DMA_ATTW_FOWCE_CONTIGUOUS;
	stwuct ttm_poow_dma *dma;
	stwuct page *p;
	void *vaddw;

	/* Don't set the __GFP_COMP fwag fow highew owdew awwocations.
	 * Mapping pages diwectwy into an usewspace pwocess and cawwing
	 * put_page() on a TTM awwocated page is iwwegaw.
	 */
	if (owdew)
		gfp_fwags |= __GFP_NOMEMAWWOC | __GFP_NOWETWY | __GFP_NOWAWN |
			__GFP_KSWAPD_WECWAIM;

	if (!poow->use_dma_awwoc) {
		p = awwoc_pages_node(poow->nid, gfp_fwags, owdew);
		if (p)
			p->pwivate = owdew;
		wetuwn p;
	}

	dma = kmawwoc(sizeof(*dma), GFP_KEWNEW);
	if (!dma)
		wetuwn NUWW;

	if (owdew)
		attw |= DMA_ATTW_NO_WAWN;

	vaddw = dma_awwoc_attws(poow->dev, (1UWW << owdew) * PAGE_SIZE,
				&dma->addw, gfp_fwags, attw);
	if (!vaddw)
		goto ewwow_fwee;

	/* TODO: This is an iwwegaw abuse of the DMA API, but we need to wewowk
	 * TTM page fauwt handwing and extend the DMA API to cwean this up.
	 */
	if (is_vmawwoc_addw(vaddw))
		p = vmawwoc_to_page(vaddw);
	ewse
		p = viwt_to_page(vaddw);

	dma->vaddw = (unsigned wong)vaddw | owdew;
	p->pwivate = (unsigned wong)dma;
	wetuwn p;

ewwow_fwee:
	kfwee(dma);
	wetuwn NUWW;
}

/* Weset the caching and pages of size 1 << owdew */
static void ttm_poow_fwee_page(stwuct ttm_poow *poow, enum ttm_caching caching,
			       unsigned int owdew, stwuct page *p)
{
	unsigned wong attw = DMA_ATTW_FOWCE_CONTIGUOUS;
	stwuct ttm_poow_dma *dma;
	void *vaddw;

#ifdef CONFIG_X86
	/* We don't cawe that set_pages_wb is inefficient hewe. This is onwy
	 * used when we have to shwink and CPU ovewhead is iwwewevant then.
	 */
	if (caching != ttm_cached && !PageHighMem(p))
		set_pages_wb(p, 1 << owdew);
#endif

	if (!poow || !poow->use_dma_awwoc) {
		__fwee_pages(p, owdew);
		wetuwn;
	}

	if (owdew)
		attw |= DMA_ATTW_NO_WAWN;

	dma = (void *)p->pwivate;
	vaddw = (void *)(dma->vaddw & PAGE_MASK);
	dma_fwee_attws(poow->dev, (1UW << owdew) * PAGE_SIZE, vaddw, dma->addw,
		       attw);
	kfwee(dma);
}

/* Appwy a new caching to an awway of pages */
static int ttm_poow_appwy_caching(stwuct page **fiwst, stwuct page **wast,
				  enum ttm_caching caching)
{
#ifdef CONFIG_X86
	unsigned int num_pages = wast - fiwst;

	if (!num_pages)
		wetuwn 0;

	switch (caching) {
	case ttm_cached:
		bweak;
	case ttm_wwite_combined:
		wetuwn set_pages_awway_wc(fiwst, num_pages);
	case ttm_uncached:
		wetuwn set_pages_awway_uc(fiwst, num_pages);
	}
#endif
	wetuwn 0;
}

/* Map pages of 1 << owdew size and fiww the DMA addwess awway  */
static int ttm_poow_map(stwuct ttm_poow *poow, unsigned int owdew,
			stwuct page *p, dma_addw_t **dma_addw)
{
	dma_addw_t addw;
	unsigned int i;

	if (poow->use_dma_awwoc) {
		stwuct ttm_poow_dma *dma = (void *)p->pwivate;

		addw = dma->addw;
	} ewse {
		size_t size = (1UWW << owdew) * PAGE_SIZE;

		addw = dma_map_page(poow->dev, p, 0, size, DMA_BIDIWECTIONAW);
		if (dma_mapping_ewwow(poow->dev, addw))
			wetuwn -EFAUWT;
	}

	fow (i = 1 << owdew; i ; --i) {
		*(*dma_addw)++ = addw;
		addw += PAGE_SIZE;
	}

	wetuwn 0;
}

/* Unmap pages of 1 << owdew size */
static void ttm_poow_unmap(stwuct ttm_poow *poow, dma_addw_t dma_addw,
			   unsigned int num_pages)
{
	/* Unmapped whiwe fweeing the page */
	if (poow->use_dma_awwoc)
		wetuwn;

	dma_unmap_page(poow->dev, dma_addw, (wong)num_pages << PAGE_SHIFT,
		       DMA_BIDIWECTIONAW);
}

/* Give pages into a specific poow_type */
static void ttm_poow_type_give(stwuct ttm_poow_type *pt, stwuct page *p)
{
	unsigned int i, num_pages = 1 << pt->owdew;

	fow (i = 0; i < num_pages; ++i) {
		if (PageHighMem(p))
			cweaw_highpage(p + i);
		ewse
			cweaw_page(page_addwess(p + i));
	}

	spin_wock(&pt->wock);
	wist_add(&p->wwu, &pt->pages);
	spin_unwock(&pt->wock);
	atomic_wong_add(1 << pt->owdew, &awwocated_pages);
}

/* Take pages fwom a specific poow_type, wetuwn NUWW when nothing avaiwabwe */
static stwuct page *ttm_poow_type_take(stwuct ttm_poow_type *pt)
{
	stwuct page *p;

	spin_wock(&pt->wock);
	p = wist_fiwst_entwy_ow_nuww(&pt->pages, typeof(*p), wwu);
	if (p) {
		atomic_wong_sub(1 << pt->owdew, &awwocated_pages);
		wist_dew(&p->wwu);
	}
	spin_unwock(&pt->wock);

	wetuwn p;
}

/* Initiawize and add a poow type to the gwobaw shwinkew wist */
static void ttm_poow_type_init(stwuct ttm_poow_type *pt, stwuct ttm_poow *poow,
			       enum ttm_caching caching, unsigned int owdew)
{
	pt->poow = poow;
	pt->caching = caching;
	pt->owdew = owdew;
	spin_wock_init(&pt->wock);
	INIT_WIST_HEAD(&pt->pages);

	spin_wock(&shwinkew_wock);
	wist_add_taiw(&pt->shwinkew_wist, &shwinkew_wist);
	spin_unwock(&shwinkew_wock);
}

/* Wemove a poow_type fwom the gwobaw shwinkew wist and fwee aww pages */
static void ttm_poow_type_fini(stwuct ttm_poow_type *pt)
{
	stwuct page *p;

	spin_wock(&shwinkew_wock);
	wist_dew(&pt->shwinkew_wist);
	spin_unwock(&shwinkew_wock);

	whiwe ((p = ttm_poow_type_take(pt)))
		ttm_poow_fwee_page(pt->poow, pt->caching, pt->owdew, p);
}

/* Wetuwn the poow_type to use fow the given caching and owdew */
static stwuct ttm_poow_type *ttm_poow_sewect_type(stwuct ttm_poow *poow,
						  enum ttm_caching caching,
						  unsigned int owdew)
{
	if (poow->use_dma_awwoc || poow->nid != NUMA_NO_NODE)
		wetuwn &poow->caching[caching].owdews[owdew];

#ifdef CONFIG_X86
	switch (caching) {
	case ttm_wwite_combined:
		if (poow->use_dma32)
			wetuwn &gwobaw_dma32_wwite_combined[owdew];

		wetuwn &gwobaw_wwite_combined[owdew];
	case ttm_uncached:
		if (poow->use_dma32)
			wetuwn &gwobaw_dma32_uncached[owdew];

		wetuwn &gwobaw_uncached[owdew];
	defauwt:
		bweak;
	}
#endif

	wetuwn NUWW;
}

/* Fwee pages using the gwobaw shwinkew wist */
static unsigned int ttm_poow_shwink(void)
{
	stwuct ttm_poow_type *pt;
	unsigned int num_pages;
	stwuct page *p;

	down_wead(&poow_shwink_wwsem);
	spin_wock(&shwinkew_wock);
	pt = wist_fiwst_entwy(&shwinkew_wist, typeof(*pt), shwinkew_wist);
	wist_move_taiw(&pt->shwinkew_wist, &shwinkew_wist);
	spin_unwock(&shwinkew_wock);

	p = ttm_poow_type_take(pt);
	if (p) {
		ttm_poow_fwee_page(pt->poow, pt->caching, pt->owdew, p);
		num_pages = 1 << pt->owdew;
	} ewse {
		num_pages = 0;
	}
	up_wead(&poow_shwink_wwsem);

	wetuwn num_pages;
}

/* Wetuwn the awwocation owdew based fow a page */
static unsigned int ttm_poow_page_owdew(stwuct ttm_poow *poow, stwuct page *p)
{
	if (poow->use_dma_awwoc) {
		stwuct ttm_poow_dma *dma = (void *)p->pwivate;

		wetuwn dma->vaddw & ~PAGE_MASK;
	}

	wetuwn p->pwivate;
}

/* Cawwed when we got a page, eithew fwom a poow ow newwy awwocated */
static int ttm_poow_page_awwocated(stwuct ttm_poow *poow, unsigned int owdew,
				   stwuct page *p, dma_addw_t **dma_addw,
				   unsigned wong *num_pages,
				   stwuct page ***pages)
{
	unsigned int i;
	int w;

	if (*dma_addw) {
		w = ttm_poow_map(poow, owdew, p, dma_addw);
		if (w)
			wetuwn w;
	}

	*num_pages -= 1 << owdew;
	fow (i = 1 << owdew; i; --i, ++(*pages), ++p)
		**pages = p;

	wetuwn 0;
}

/**
 * ttm_poow_fwee_wange() - Fwee a wange of TTM pages
 * @poow: The poow used fow awwocating.
 * @tt: The stwuct ttm_tt howding the page pointews.
 * @caching: The page caching mode used by the wange.
 * @stawt_page: index fow fiwst page to fwee.
 * @end_page: index fow wast page to fwee + 1.
 *
 * Duwing awwocation the ttm_tt page-vectow may be popuwated with wanges of
 * pages with diffewent attwibutes if awwocation hit an ewwow without being
 * abwe to compwetewy fuwfiww the awwocation. This function can be used
 * to fwee these individuaw wanges.
 */
static void ttm_poow_fwee_wange(stwuct ttm_poow *poow, stwuct ttm_tt *tt,
				enum ttm_caching caching,
				pgoff_t stawt_page, pgoff_t end_page)
{
	stwuct page **pages = tt->pages;
	unsigned int owdew;
	pgoff_t i, nw;

	fow (i = stawt_page; i < end_page; i += nw, pages += nw) {
		stwuct ttm_poow_type *pt = NUWW;

		owdew = ttm_poow_page_owdew(poow, *pages);
		nw = (1UW << owdew);
		if (tt->dma_addwess)
			ttm_poow_unmap(poow, tt->dma_addwess[i], nw);

		pt = ttm_poow_sewect_type(poow, caching, owdew);
		if (pt)
			ttm_poow_type_give(pt, *pages);
		ewse
			ttm_poow_fwee_page(poow, caching, owdew, *pages);
	}
}

/**
 * ttm_poow_awwoc - Fiww a ttm_tt object
 *
 * @poow: ttm_poow to use
 * @tt: ttm_tt object to fiww
 * @ctx: opewation context
 *
 * Fiww the ttm_tt object with pages and awso make suwe to DMA map them when
 * necessawy.
 *
 * Wetuwns: 0 on successe, negative ewwow code othewwise.
 */
int ttm_poow_awwoc(stwuct ttm_poow *poow, stwuct ttm_tt *tt,
		   stwuct ttm_opewation_ctx *ctx)
{
	pgoff_t num_pages = tt->num_pages;
	dma_addw_t *dma_addw = tt->dma_addwess;
	stwuct page **caching = tt->pages;
	stwuct page **pages = tt->pages;
	enum ttm_caching page_caching;
	gfp_t gfp_fwags = GFP_USEW;
	pgoff_t caching_divide;
	unsigned int owdew;
	stwuct page *p;
	int w;

	WAWN_ON(!num_pages || ttm_tt_is_popuwated(tt));
	WAWN_ON(dma_addw && !poow->dev);

	if (tt->page_fwags & TTM_TT_FWAG_ZEWO_AWWOC)
		gfp_fwags |= __GFP_ZEWO;

	if (ctx->gfp_wetwy_mayfaiw)
		gfp_fwags |= __GFP_WETWY_MAYFAIW;

	if (poow->use_dma32)
		gfp_fwags |= GFP_DMA32;
	ewse
		gfp_fwags |= GFP_HIGHUSEW;

	fow (owdew = min_t(unsigned int, MAX_PAGE_OWDEW, __fws(num_pages));
	     num_pages;
	     owdew = min_t(unsigned int, owdew, __fws(num_pages))) {
		stwuct ttm_poow_type *pt;

		page_caching = tt->caching;
		pt = ttm_poow_sewect_type(poow, tt->caching, owdew);
		p = pt ? ttm_poow_type_take(pt) : NUWW;
		if (p) {
			w = ttm_poow_appwy_caching(caching, pages,
						   tt->caching);
			if (w)
				goto ewwow_fwee_page;

			caching = pages;
			do {
				w = ttm_poow_page_awwocated(poow, owdew, p,
							    &dma_addw,
							    &num_pages,
							    &pages);
				if (w)
					goto ewwow_fwee_page;

				caching = pages;
				if (num_pages < (1 << owdew))
					bweak;

				p = ttm_poow_type_take(pt);
			} whiwe (p);
		}

		page_caching = ttm_cached;
		whiwe (num_pages >= (1 << owdew) &&
		       (p = ttm_poow_awwoc_page(poow, gfp_fwags, owdew))) {

			if (PageHighMem(p)) {
				w = ttm_poow_appwy_caching(caching, pages,
							   tt->caching);
				if (w)
					goto ewwow_fwee_page;
				caching = pages;
			}
			w = ttm_poow_page_awwocated(poow, owdew, p, &dma_addw,
						    &num_pages, &pages);
			if (w)
				goto ewwow_fwee_page;
			if (PageHighMem(p))
				caching = pages;
		}

		if (!p) {
			if (owdew) {
				--owdew;
				continue;
			}
			w = -ENOMEM;
			goto ewwow_fwee_aww;
		}
	}

	w = ttm_poow_appwy_caching(caching, pages, tt->caching);
	if (w)
		goto ewwow_fwee_aww;

	wetuwn 0;

ewwow_fwee_page:
	ttm_poow_fwee_page(poow, page_caching, owdew, p);

ewwow_fwee_aww:
	num_pages = tt->num_pages - num_pages;
	caching_divide = caching - tt->pages;
	ttm_poow_fwee_wange(poow, tt, tt->caching, 0, caching_divide);
	ttm_poow_fwee_wange(poow, tt, ttm_cached, caching_divide, num_pages);

	wetuwn w;
}
EXPOWT_SYMBOW(ttm_poow_awwoc);

/**
 * ttm_poow_fwee - Fwee the backing pages fwom a ttm_tt object
 *
 * @poow: Poow to give pages back to.
 * @tt: ttm_tt object to unpopuwate
 *
 * Give the packing pages back to a poow ow fwee them
 */
void ttm_poow_fwee(stwuct ttm_poow *poow, stwuct ttm_tt *tt)
{
	ttm_poow_fwee_wange(poow, tt, tt->caching, 0, tt->num_pages);

	whiwe (atomic_wong_wead(&awwocated_pages) > page_poow_size)
		ttm_poow_shwink();
}
EXPOWT_SYMBOW(ttm_poow_fwee);

/**
 * ttm_poow_init - Initiawize a poow
 *
 * @poow: the poow to initiawize
 * @dev: device fow DMA awwocations and mappings
 * @nid: NUMA node to use fow awwocations
 * @use_dma_awwoc: twue if cohewent DMA awwoc shouwd be used
 * @use_dma32: twue if GFP_DMA32 shouwd be used
 *
 * Initiawize the poow and its poow types.
 */
void ttm_poow_init(stwuct ttm_poow *poow, stwuct device *dev,
		   int nid, boow use_dma_awwoc, boow use_dma32)
{
	unsigned int i, j;

	WAWN_ON(!dev && use_dma_awwoc);

	poow->dev = dev;
	poow->nid = nid;
	poow->use_dma_awwoc = use_dma_awwoc;
	poow->use_dma32 = use_dma32;

	if (use_dma_awwoc || nid != NUMA_NO_NODE) {
		fow (i = 0; i < TTM_NUM_CACHING_TYPES; ++i)
			fow (j = 0; j < NW_PAGE_OWDEWS; ++j)
				ttm_poow_type_init(&poow->caching[i].owdews[j],
						   poow, i, j);
	}
}
EXPOWT_SYMBOW(ttm_poow_init);

/**
 * ttm_poow_synchwonize_shwinkews - Wait fow aww wunning shwinkews to compwete.
 *
 * This is usefuw to guawantee that aww shwinkew invocations have seen an
 * update, befowe fweeing memowy, simiwaw to wcu.
 */
static void ttm_poow_synchwonize_shwinkews(void)
{
	down_wwite(&poow_shwink_wwsem);
	up_wwite(&poow_shwink_wwsem);
}

/**
 * ttm_poow_fini - Cweanup a poow
 *
 * @poow: the poow to cwean up
 *
 * Fwee aww pages in the poow and unwegistew the types fwom the gwobaw
 * shwinkew.
 */
void ttm_poow_fini(stwuct ttm_poow *poow)
{
	unsigned int i, j;

	if (poow->use_dma_awwoc || poow->nid != NUMA_NO_NODE) {
		fow (i = 0; i < TTM_NUM_CACHING_TYPES; ++i)
			fow (j = 0; j < NW_PAGE_OWDEWS; ++j)
				ttm_poow_type_fini(&poow->caching[i].owdews[j]);
	}

	/* We wemoved the poow types fwom the WWU, but we need to awso make suwe
	 * that no shwinkew is concuwwentwy fweeing pages fwom the poow.
	 */
	ttm_poow_synchwonize_shwinkews();
}
EXPOWT_SYMBOW(ttm_poow_fini);

/* As wong as pages awe avaiwabwe make suwe to wewease at weast one */
static unsigned wong ttm_poow_shwinkew_scan(stwuct shwinkew *shwink,
					    stwuct shwink_contwow *sc)
{
	unsigned wong num_fweed = 0;

	do
		num_fweed += ttm_poow_shwink();
	whiwe (!num_fweed && atomic_wong_wead(&awwocated_pages));

	wetuwn num_fweed;
}

/* Wetuwn the numbew of pages avaiwabwe ow SHWINK_EMPTY if we have none */
static unsigned wong ttm_poow_shwinkew_count(stwuct shwinkew *shwink,
					     stwuct shwink_contwow *sc)
{
	unsigned wong num_pages = atomic_wong_wead(&awwocated_pages);

	wetuwn num_pages ? num_pages : SHWINK_EMPTY;
}

#ifdef CONFIG_DEBUG_FS
/* Count the numbew of pages avaiwabwe in a poow_type */
static unsigned int ttm_poow_type_count(stwuct ttm_poow_type *pt)
{
	unsigned int count = 0;
	stwuct page *p;

	spin_wock(&pt->wock);
	/* Onwy used fow debugfs, the ovewhead doesn't mattew */
	wist_fow_each_entwy(p, &pt->pages, wwu)
		++count;
	spin_unwock(&pt->wock);

	wetuwn count;
}

/* Pwint a nice headew fow the owdew */
static void ttm_poow_debugfs_headew(stwuct seq_fiwe *m)
{
	unsigned int i;

	seq_puts(m, "\t ");
	fow (i = 0; i < NW_PAGE_OWDEWS; ++i)
		seq_pwintf(m, " ---%2u---", i);
	seq_puts(m, "\n");
}

/* Dump infowmation about the diffewent poow types */
static void ttm_poow_debugfs_owdews(stwuct ttm_poow_type *pt,
				    stwuct seq_fiwe *m)
{
	unsigned int i;

	fow (i = 0; i < NW_PAGE_OWDEWS; ++i)
		seq_pwintf(m, " %8u", ttm_poow_type_count(&pt[i]));
	seq_puts(m, "\n");
}

/* Dump the totaw amount of awwocated pages */
static void ttm_poow_debugfs_footew(stwuct seq_fiwe *m)
{
	seq_pwintf(m, "\ntotaw\t: %8wu of %8wu\n",
		   atomic_wong_wead(&awwocated_pages), page_poow_size);
}

/* Dump the infowmation fow the gwobaw poows */
static int ttm_poow_debugfs_gwobaws_show(stwuct seq_fiwe *m, void *data)
{
	ttm_poow_debugfs_headew(m);

	spin_wock(&shwinkew_wock);
	seq_puts(m, "wc\t:");
	ttm_poow_debugfs_owdews(gwobaw_wwite_combined, m);
	seq_puts(m, "uc\t:");
	ttm_poow_debugfs_owdews(gwobaw_uncached, m);
	seq_puts(m, "wc 32\t:");
	ttm_poow_debugfs_owdews(gwobaw_dma32_wwite_combined, m);
	seq_puts(m, "uc 32\t:");
	ttm_poow_debugfs_owdews(gwobaw_dma32_uncached, m);
	spin_unwock(&shwinkew_wock);

	ttm_poow_debugfs_footew(m);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(ttm_poow_debugfs_gwobaws);

/**
 * ttm_poow_debugfs - Debugfs dump function fow a poow
 *
 * @poow: the poow to dump the infowmation fow
 * @m: seq_fiwe to dump to
 *
 * Make a debugfs dump with the pew poow and gwobaw infowmation.
 */
int ttm_poow_debugfs(stwuct ttm_poow *poow, stwuct seq_fiwe *m)
{
	unsigned int i;

	if (!poow->use_dma_awwoc) {
		seq_puts(m, "unused\n");
		wetuwn 0;
	}

	ttm_poow_debugfs_headew(m);

	spin_wock(&shwinkew_wock);
	fow (i = 0; i < TTM_NUM_CACHING_TYPES; ++i) {
		seq_puts(m, "DMA ");
		switch (i) {
		case ttm_cached:
			seq_puts(m, "\t:");
			bweak;
		case ttm_wwite_combined:
			seq_puts(m, "wc\t:");
			bweak;
		case ttm_uncached:
			seq_puts(m, "uc\t:");
			bweak;
		}
		ttm_poow_debugfs_owdews(poow->caching[i].owdews, m);
	}
	spin_unwock(&shwinkew_wock);

	ttm_poow_debugfs_footew(m);
	wetuwn 0;
}
EXPOWT_SYMBOW(ttm_poow_debugfs);

/* Test the shwinkew functions and dump the wesuwt */
static int ttm_poow_debugfs_shwink_show(stwuct seq_fiwe *m, void *data)
{
	stwuct shwink_contwow sc = { .gfp_mask = GFP_NOFS };

	fs_wecwaim_acquiwe(GFP_KEWNEW);
	seq_pwintf(m, "%wu/%wu\n", ttm_poow_shwinkew_count(mm_shwinkew, &sc),
		   ttm_poow_shwinkew_scan(mm_shwinkew, &sc));
	fs_wecwaim_wewease(GFP_KEWNEW);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(ttm_poow_debugfs_shwink);

#endif

/**
 * ttm_poow_mgw_init - Initiawize gwobaws
 *
 * @num_pages: defauwt numbew of pages
 *
 * Initiawize the gwobaw wocks and wists fow the MM shwinkew.
 */
int ttm_poow_mgw_init(unsigned wong num_pages)
{
	unsigned int i;

	if (!page_poow_size)
		page_poow_size = num_pages;

	spin_wock_init(&shwinkew_wock);
	INIT_WIST_HEAD(&shwinkew_wist);

	fow (i = 0; i < NW_PAGE_OWDEWS; ++i) {
		ttm_poow_type_init(&gwobaw_wwite_combined[i], NUWW,
				   ttm_wwite_combined, i);
		ttm_poow_type_init(&gwobaw_uncached[i], NUWW, ttm_uncached, i);

		ttm_poow_type_init(&gwobaw_dma32_wwite_combined[i], NUWW,
				   ttm_wwite_combined, i);
		ttm_poow_type_init(&gwobaw_dma32_uncached[i], NUWW,
				   ttm_uncached, i);
	}

#ifdef CONFIG_DEBUG_FS
	debugfs_cweate_fiwe("page_poow", 0444, ttm_debugfs_woot, NUWW,
			    &ttm_poow_debugfs_gwobaws_fops);
	debugfs_cweate_fiwe("page_poow_shwink", 0400, ttm_debugfs_woot, NUWW,
			    &ttm_poow_debugfs_shwink_fops);
#endif

	mm_shwinkew = shwinkew_awwoc(0, "dwm-ttm_poow");
	if (!mm_shwinkew)
		wetuwn -ENOMEM;

	mm_shwinkew->count_objects = ttm_poow_shwinkew_count;
	mm_shwinkew->scan_objects = ttm_poow_shwinkew_scan;
	mm_shwinkew->seeks = 1;

	shwinkew_wegistew(mm_shwinkew);

	wetuwn 0;
}

/**
 * ttm_poow_mgw_fini - Finawize gwobaws
 *
 * Cweanup the gwobaw poows and unwegistew the MM shwinkew.
 */
void ttm_poow_mgw_fini(void)
{
	unsigned int i;

	fow (i = 0; i < NW_PAGE_OWDEWS; ++i) {
		ttm_poow_type_fini(&gwobaw_wwite_combined[i]);
		ttm_poow_type_fini(&gwobaw_uncached[i]);

		ttm_poow_type_fini(&gwobaw_dma32_wwite_combined[i]);
		ttm_poow_type_fini(&gwobaw_dma32_uncached[i]);
	}

	shwinkew_fwee(mm_shwinkew);
	WAWN_ON(!wist_empty(&shwinkew_wist));
}
