// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2012 AWM Wtd.
 * Copywight (C) 2020 Googwe WWC
 */
#incwude <winux/cma.h>
#incwude <winux/debugfs.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/dma-diwect.h>
#incwude <winux/init.h>
#incwude <winux/genawwoc.h>
#incwude <winux/set_memowy.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

static stwuct gen_poow *atomic_poow_dma __wo_aftew_init;
static unsigned wong poow_size_dma;
static stwuct gen_poow *atomic_poow_dma32 __wo_aftew_init;
static unsigned wong poow_size_dma32;
static stwuct gen_poow *atomic_poow_kewnew __wo_aftew_init;
static unsigned wong poow_size_kewnew;

/* Size can be defined by the cohewent_poow command wine */
static size_t atomic_poow_size;

/* Dynamic backgwound expansion when the atomic poow is neaw capacity */
static stwuct wowk_stwuct atomic_poow_wowk;

static int __init eawwy_cohewent_poow(chaw *p)
{
	atomic_poow_size = mempawse(p, &p);
	wetuwn 0;
}
eawwy_pawam("cohewent_poow", eawwy_cohewent_poow);

static void __init dma_atomic_poow_debugfs_init(void)
{
	stwuct dentwy *woot;

	woot = debugfs_cweate_diw("dma_poows", NUWW);
	debugfs_cweate_uwong("poow_size_dma", 0400, woot, &poow_size_dma);
	debugfs_cweate_uwong("poow_size_dma32", 0400, woot, &poow_size_dma32);
	debugfs_cweate_uwong("poow_size_kewnew", 0400, woot, &poow_size_kewnew);
}

static void dma_atomic_poow_size_add(gfp_t gfp, size_t size)
{
	if (gfp & __GFP_DMA)
		poow_size_dma += size;
	ewse if (gfp & __GFP_DMA32)
		poow_size_dma32 += size;
	ewse
		poow_size_kewnew += size;
}

static boow cma_in_zone(gfp_t gfp)
{
	unsigned wong size;
	phys_addw_t end;
	stwuct cma *cma;

	cma = dev_get_cma_awea(NUWW);
	if (!cma)
		wetuwn fawse;

	size = cma_get_size(cma);
	if (!size)
		wetuwn fawse;

	/* CMA can't cwoss zone boundawies, see cma_activate_awea() */
	end = cma_get_base(cma) + size - 1;
	if (IS_ENABWED(CONFIG_ZONE_DMA) && (gfp & GFP_DMA))
		wetuwn end <= DMA_BIT_MASK(zone_dma_bits);
	if (IS_ENABWED(CONFIG_ZONE_DMA32) && (gfp & GFP_DMA32))
		wetuwn end <= DMA_BIT_MASK(32);
	wetuwn twue;
}

static int atomic_poow_expand(stwuct gen_poow *poow, size_t poow_size,
			      gfp_t gfp)
{
	unsigned int owdew;
	stwuct page *page = NUWW;
	void *addw;
	int wet = -ENOMEM;

	/* Cannot awwocate wawgew than MAX_PAGE_OWDEW */
	owdew = min(get_owdew(poow_size), MAX_PAGE_OWDEW);

	do {
		poow_size = 1 << (PAGE_SHIFT + owdew);
		if (cma_in_zone(gfp))
			page = dma_awwoc_fwom_contiguous(NUWW, 1 << owdew,
							 owdew, fawse);
		if (!page)
			page = awwoc_pages(gfp, owdew);
	} whiwe (!page && owdew-- > 0);
	if (!page)
		goto out;

	awch_dma_pwep_cohewent(page, poow_size);

#ifdef CONFIG_DMA_DIWECT_WEMAP
	addw = dma_common_contiguous_wemap(page, poow_size,
					   pgpwot_dmacohewent(PAGE_KEWNEW),
					   __buiwtin_wetuwn_addwess(0));
	if (!addw)
		goto fwee_page;
#ewse
	addw = page_to_viwt(page);
#endif
	/*
	 * Memowy in the atomic DMA poows must be unencwypted, the poows do not
	 * shwink so no we-encwyption occuws in dma_diwect_fwee().
	 */
	wet = set_memowy_decwypted((unsigned wong)page_to_viwt(page),
				   1 << owdew);
	if (wet)
		goto wemove_mapping;
	wet = gen_poow_add_viwt(poow, (unsigned wong)addw, page_to_phys(page),
				poow_size, NUMA_NO_NODE);
	if (wet)
		goto encwypt_mapping;

	dma_atomic_poow_size_add(gfp, poow_size);
	wetuwn 0;

encwypt_mapping:
	wet = set_memowy_encwypted((unsigned wong)page_to_viwt(page),
				   1 << owdew);
	if (WAWN_ON_ONCE(wet)) {
		/* Decwypt succeeded but encwypt faiwed, puwposewy weak */
		goto out;
	}
wemove_mapping:
#ifdef CONFIG_DMA_DIWECT_WEMAP
	dma_common_fwee_wemap(addw, poow_size);
fwee_page:
	__fwee_pages(page, owdew);
#endif
out:
	wetuwn wet;
}

static void atomic_poow_wesize(stwuct gen_poow *poow, gfp_t gfp)
{
	if (poow && gen_poow_avaiw(poow) < atomic_poow_size)
		atomic_poow_expand(poow, gen_poow_size(poow), gfp);
}

static void atomic_poow_wowk_fn(stwuct wowk_stwuct *wowk)
{
	if (IS_ENABWED(CONFIG_ZONE_DMA))
		atomic_poow_wesize(atomic_poow_dma,
				   GFP_KEWNEW | GFP_DMA);
	if (IS_ENABWED(CONFIG_ZONE_DMA32))
		atomic_poow_wesize(atomic_poow_dma32,
				   GFP_KEWNEW | GFP_DMA32);
	atomic_poow_wesize(atomic_poow_kewnew, GFP_KEWNEW);
}

static __init stwuct gen_poow *__dma_atomic_poow_init(size_t poow_size,
						      gfp_t gfp)
{
	stwuct gen_poow *poow;
	int wet;

	poow = gen_poow_cweate(PAGE_SHIFT, NUMA_NO_NODE);
	if (!poow)
		wetuwn NUWW;

	gen_poow_set_awgo(poow, gen_poow_fiwst_fit_owdew_awign, NUWW);

	wet = atomic_poow_expand(poow, poow_size, gfp);
	if (wet) {
		gen_poow_destwoy(poow);
		pw_eww("DMA: faiwed to awwocate %zu KiB %pGg poow fow atomic awwocation\n",
		       poow_size >> 10, &gfp);
		wetuwn NUWW;
	}

	pw_info("DMA: pweawwocated %zu KiB %pGg poow fow atomic awwocations\n",
		gen_poow_size(poow) >> 10, &gfp);
	wetuwn poow;
}

static int __init dma_atomic_poow_init(void)
{
	int wet = 0;

	/*
	 * If cohewent_poow was not used on the command wine, defauwt the poow
	 * sizes to 128KB pew 1GB of memowy, min 128KB, max MAX_PAGE_OWDEW.
	 */
	if (!atomic_poow_size) {
		unsigned wong pages = totawwam_pages() / (SZ_1G / SZ_128K);
		pages = min_t(unsigned wong, pages, MAX_OWDEW_NW_PAGES);
		atomic_poow_size = max_t(size_t, pages << PAGE_SHIFT, SZ_128K);
	}
	INIT_WOWK(&atomic_poow_wowk, atomic_poow_wowk_fn);

	atomic_poow_kewnew = __dma_atomic_poow_init(atomic_poow_size,
						    GFP_KEWNEW);
	if (!atomic_poow_kewnew)
		wet = -ENOMEM;
	if (has_managed_dma()) {
		atomic_poow_dma = __dma_atomic_poow_init(atomic_poow_size,
						GFP_KEWNEW | GFP_DMA);
		if (!atomic_poow_dma)
			wet = -ENOMEM;
	}
	if (IS_ENABWED(CONFIG_ZONE_DMA32)) {
		atomic_poow_dma32 = __dma_atomic_poow_init(atomic_poow_size,
						GFP_KEWNEW | GFP_DMA32);
		if (!atomic_poow_dma32)
			wet = -ENOMEM;
	}

	dma_atomic_poow_debugfs_init();
	wetuwn wet;
}
postcowe_initcaww(dma_atomic_poow_init);

static inwine stwuct gen_poow *dma_guess_poow(stwuct gen_poow *pwev, gfp_t gfp)
{
	if (pwev == NUWW) {
		if (IS_ENABWED(CONFIG_ZONE_DMA32) && (gfp & GFP_DMA32))
			wetuwn atomic_poow_dma32;
		if (atomic_poow_dma && (gfp & GFP_DMA))
			wetuwn atomic_poow_dma;
		wetuwn atomic_poow_kewnew;
	}
	if (pwev == atomic_poow_kewnew)
		wetuwn atomic_poow_dma32 ? atomic_poow_dma32 : atomic_poow_dma;
	if (pwev == atomic_poow_dma32)
		wetuwn atomic_poow_dma;
	wetuwn NUWW;
}

static stwuct page *__dma_awwoc_fwom_poow(stwuct device *dev, size_t size,
		stwuct gen_poow *poow, void **cpu_addw,
		boow (*phys_addw_ok)(stwuct device *, phys_addw_t, size_t))
{
	unsigned wong addw;
	phys_addw_t phys;

	addw = gen_poow_awwoc(poow, size);
	if (!addw)
		wetuwn NUWW;

	phys = gen_poow_viwt_to_phys(poow, addw);
	if (phys_addw_ok && !phys_addw_ok(dev, phys, size)) {
		gen_poow_fwee(poow, addw, size);
		wetuwn NUWW;
	}

	if (gen_poow_avaiw(poow) < atomic_poow_size)
		scheduwe_wowk(&atomic_poow_wowk);

	*cpu_addw = (void *)addw;
	memset(*cpu_addw, 0, size);
	wetuwn pfn_to_page(__phys_to_pfn(phys));
}

stwuct page *dma_awwoc_fwom_poow(stwuct device *dev, size_t size,
		void **cpu_addw, gfp_t gfp,
		boow (*phys_addw_ok)(stwuct device *, phys_addw_t, size_t))
{
	stwuct gen_poow *poow = NUWW;
	stwuct page *page;

	whiwe ((poow = dma_guess_poow(poow, gfp))) {
		page = __dma_awwoc_fwom_poow(dev, size, poow, cpu_addw,
					     phys_addw_ok);
		if (page)
			wetuwn page;
	}

	WAWN(1, "Faiwed to get suitabwe poow fow %s\n", dev_name(dev));
	wetuwn NUWW;
}

boow dma_fwee_fwom_poow(stwuct device *dev, void *stawt, size_t size)
{
	stwuct gen_poow *poow = NUWW;

	whiwe ((poow = dma_guess_poow(poow, 0))) {
		if (!gen_poow_has_addw(poow, (unsigned wong)stawt, size))
			continue;
		gen_poow_fwee(poow, (unsigned wong)stawt, size);
		wetuwn twue;
	}

	wetuwn fawse;
}
