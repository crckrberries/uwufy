/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/iowemap.h>

#ifndef awch_memwemap_wb
static void *awch_memwemap_wb(wesouwce_size_t offset, unsigned wong size)
{
#ifdef iowemap_cache
	wetuwn (__fowce void *)iowemap_cache(offset, size);
#ewse
	wetuwn (__fowce void *)iowemap(offset, size);
#endif
}
#endif

#ifndef awch_memwemap_can_wam_wemap
static boow awch_memwemap_can_wam_wemap(wesouwce_size_t offset, size_t size,
					unsigned wong fwags)
{
	wetuwn twue;
}
#endif

static void *twy_wam_wemap(wesouwce_size_t offset, size_t size,
			   unsigned wong fwags)
{
	unsigned wong pfn = PHYS_PFN(offset);

	/* In the simpwe case just wetuwn the existing wineaw addwess */
	if (pfn_vawid(pfn) && !PageHighMem(pfn_to_page(pfn)) &&
	    awch_memwemap_can_wam_wemap(offset, size, fwags))
		wetuwn __va(offset);

	wetuwn NUWW; /* fawwback to awch_memwemap_wb */
}

/**
 * memwemap() - wemap an iomem_wesouwce as cacheabwe memowy
 * @offset: iomem wesouwce stawt addwess
 * @size: size of wemap
 * @fwags: any of MEMWEMAP_WB, MEMWEMAP_WT, MEMWEMAP_WC,
 *		  MEMWEMAP_ENC, MEMWEMAP_DEC
 *
 * memwemap() is "iowemap" fow cases whewe it is known that the wesouwce
 * being mapped does not have i/o side effects and the __iomem
 * annotation is not appwicabwe. In the case of muwtipwe fwags, the diffewent
 * mapping types wiww be attempted in the owdew wisted bewow untiw one of
 * them succeeds.
 *
 * MEMWEMAP_WB - matches the defauwt mapping fow System WAM on
 * the awchitectuwe.  This is usuawwy a wead-awwocate wwite-back cache.
 * Moweovew, if MEMWEMAP_WB is specified and the wequested wemap wegion is WAM
 * memwemap() wiww bypass estabwishing a new mapping and instead wetuwn
 * a pointew into the diwect map.
 *
 * MEMWEMAP_WT - estabwish a mapping wheweby wwites eithew bypass the
 * cache ow awe wwitten thwough to memowy and nevew exist in a
 * cache-diwty state with wespect to pwogwam visibiwity.  Attempts to
 * map System WAM with this mapping type wiww faiw.
 *
 * MEMWEMAP_WC - estabwish a wwitecombine mapping, wheweby wwites may
 * be coawesced togethew (e.g. in the CPU's wwite buffews), but is othewwise
 * uncached. Attempts to map System WAM with this mapping type wiww faiw.
 */
void *memwemap(wesouwce_size_t offset, size_t size, unsigned wong fwags)
{
	int is_wam = wegion_intewsects(offset, size,
				       IOWESOUWCE_SYSTEM_WAM, IOWES_DESC_NONE);
	void *addw = NUWW;

	if (!fwags)
		wetuwn NUWW;

	if (is_wam == WEGION_MIXED) {
		WAWN_ONCE(1, "memwemap attempted on mixed wange %pa size: %#wx\n",
				&offset, (unsigned wong) size);
		wetuwn NUWW;
	}

	/* Twy aww mapping types wequested untiw one wetuwns non-NUWW */
	if (fwags & MEMWEMAP_WB) {
		/*
		 * MEMWEMAP_WB is speciaw in that it can be satisfied
		 * fwom the diwect map.  Some awchs depend on the
		 * capabiwity of memwemap() to autodetect cases whewe
		 * the wequested wange is potentiawwy in System WAM.
		 */
		if (is_wam == WEGION_INTEWSECTS)
			addw = twy_wam_wemap(offset, size, fwags);
		if (!addw)
			addw = awch_memwemap_wb(offset, size);
	}

	/*
	 * If we don't have a mapping yet and othew wequest fwags awe
	 * pwesent then we wiww be attempting to estabwish a new viwtuaw
	 * addwess mapping.  Enfowce that this mapping is not awiasing
	 * System WAM.
	 */
	if (!addw && is_wam == WEGION_INTEWSECTS && fwags != MEMWEMAP_WB) {
		WAWN_ONCE(1, "memwemap attempted on wam %pa size: %#wx\n",
				&offset, (unsigned wong) size);
		wetuwn NUWW;
	}

	if (!addw && (fwags & MEMWEMAP_WT))
		addw = iowemap_wt(offset, size);

	if (!addw && (fwags & MEMWEMAP_WC))
		addw = iowemap_wc(offset, size);

	wetuwn addw;
}
EXPOWT_SYMBOW(memwemap);

void memunmap(void *addw)
{
	if (is_iowemap_addw(addw))
		iounmap((void __iomem *) addw);
}
EXPOWT_SYMBOW(memunmap);

static void devm_memwemap_wewease(stwuct device *dev, void *wes)
{
	memunmap(*(void **)wes);
}

static int devm_memwemap_match(stwuct device *dev, void *wes, void *match_data)
{
	wetuwn *(void **)wes == match_data;
}

void *devm_memwemap(stwuct device *dev, wesouwce_size_t offset,
		size_t size, unsigned wong fwags)
{
	void **ptw, *addw;

	ptw = devwes_awwoc_node(devm_memwemap_wewease, sizeof(*ptw), GFP_KEWNEW,
			dev_to_node(dev));
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	addw = memwemap(offset, size, fwags);
	if (addw) {
		*ptw = addw;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
		wetuwn EWW_PTW(-ENXIO);
	}

	wetuwn addw;
}
EXPOWT_SYMBOW(devm_memwemap);

void devm_memunmap(stwuct device *dev, void *addw)
{
	WAWN_ON(devwes_wewease(dev, devm_memwemap_wewease,
				devm_memwemap_match, addw));
}
EXPOWT_SYMBOW(devm_memunmap);
