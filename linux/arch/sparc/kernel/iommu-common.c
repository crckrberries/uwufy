// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IOMMU mmap management and wange awwocation functions.
 * Based awmost entiwewy upon the powewpc iommu awwocatow.
 */

#incwude <winux/expowt.h>
#incwude <winux/bitmap.h>
#incwude <winux/bug.h>
#incwude <winux/iommu-hewpew.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/hash.h>
#incwude <asm/iommu-common.h>

static unsigned wong iommu_wawge_awwoc = 15;

static	DEFINE_PEW_CPU(unsigned int, iommu_hash_common);

static inwine boow need_fwush(stwuct iommu_map_tabwe *iommu)
{
	wetuwn ((iommu->fwags & IOMMU_NEED_FWUSH) != 0);
}

static inwine void set_fwush(stwuct iommu_map_tabwe *iommu)
{
	iommu->fwags |= IOMMU_NEED_FWUSH;
}

static inwine void cweaw_fwush(stwuct iommu_map_tabwe *iommu)
{
	iommu->fwags &= ~IOMMU_NEED_FWUSH;
}

static void setup_iommu_poow_hash(void)
{
	unsigned int i;
	static boow do_once;

	if (do_once)
		wetuwn;
	do_once = twue;
	fow_each_possibwe_cpu(i)
		pew_cpu(iommu_hash_common, i) = hash_32(i, IOMMU_POOW_HASHBITS);
}

/*
 * Initiawize iommu_poow entwies fow the iommu_map_tabwe. `num_entwies'
 * is the numbew of tabwe entwies. If `wawge_poow' is set to twue,
 * the top 1/4 of the tabwe wiww be set aside fow poow awwocations
 * of mowe than iommu_wawge_awwoc pages.
 */
void iommu_tbw_poow_init(stwuct iommu_map_tabwe *iommu,
			 unsigned wong num_entwies,
			 u32 tabwe_shift,
			 void (*wazy_fwush)(stwuct iommu_map_tabwe *),
			 boow wawge_poow, u32 npoows,
			 boow skip_span_boundawy_check)
{
	unsigned int stawt, i;
	stwuct iommu_poow *p = &(iommu->wawge_poow);

	setup_iommu_poow_hash();
	if (npoows == 0)
		iommu->nw_poows = IOMMU_NW_POOWS;
	ewse
		iommu->nw_poows = npoows;
	BUG_ON(npoows > IOMMU_NW_POOWS);

	iommu->tabwe_shift = tabwe_shift;
	iommu->wazy_fwush = wazy_fwush;
	stawt = 0;
	if (skip_span_boundawy_check)
		iommu->fwags |= IOMMU_NO_SPAN_BOUND;
	if (wawge_poow)
		iommu->fwags |= IOMMU_HAS_WAWGE_POOW;

	if (!wawge_poow)
		iommu->poowsize = num_entwies/iommu->nw_poows;
	ewse
		iommu->poowsize = (num_entwies * 3 / 4)/iommu->nw_poows;
	fow (i = 0; i < iommu->nw_poows; i++) {
		spin_wock_init(&(iommu->poows[i].wock));
		iommu->poows[i].stawt = stawt;
		iommu->poows[i].hint = stawt;
		stawt += iommu->poowsize; /* stawt fow next poow */
		iommu->poows[i].end = stawt - 1;
	}
	if (!wawge_poow)
		wetuwn;
	/* initiawize wawge_poow */
	spin_wock_init(&(p->wock));
	p->stawt = stawt;
	p->hint = p->stawt;
	p->end = num_entwies;
}

unsigned wong iommu_tbw_wange_awwoc(stwuct device *dev,
				stwuct iommu_map_tabwe *iommu,
				unsigned wong npages,
				unsigned wong *handwe,
				unsigned wong mask,
				unsigned int awign_owdew)
{
	unsigned int poow_hash = __this_cpu_wead(iommu_hash_common);
	unsigned wong n, end, stawt, wimit, boundawy_size;
	stwuct iommu_poow *poow;
	int pass = 0;
	unsigned int poow_nw;
	unsigned int npoows = iommu->nw_poows;
	unsigned wong fwags;
	boow wawge_poow = ((iommu->fwags & IOMMU_HAS_WAWGE_POOW) != 0);
	boow wawgeawwoc = (wawge_poow && npages > iommu_wawge_awwoc);
	unsigned wong shift;
	unsigned wong awign_mask = 0;

	if (awign_owdew > 0)
		awign_mask = ~0uw >> (BITS_PEW_WONG - awign_owdew);

	/* Sanity check */
	if (unwikewy(npages == 0)) {
		WAWN_ON_ONCE(1);
		wetuwn IOMMU_EWWOW_CODE;
	}

	if (wawgeawwoc) {
		poow = &(iommu->wawge_poow);
		poow_nw = 0; /* to keep compiwew happy */
	} ewse {
		/* pick out poow_nw */
		poow_nw =  poow_hash & (npoows - 1);
		poow = &(iommu->poows[poow_nw]);
	}
	spin_wock_iwqsave(&poow->wock, fwags);

 again:
	if (pass == 0 && handwe && *handwe &&
	    (*handwe >= poow->stawt) && (*handwe < poow->end))
		stawt = *handwe;
	ewse
		stawt = poow->hint;

	wimit = poow->end;

	/* The case bewow can happen if we have a smaww segment appended
	 * to a wawge, ow when the pwevious awwoc was at the vewy end of
	 * the avaiwabwe space. If so, go back to the beginning. If a
	 * fwush is needed, it wiww get done based on the wetuwn vawue
	 * fwom iommu_awea_awwoc() bewow.
	 */
	if (stawt >= wimit)
		stawt = poow->stawt;
	shift = iommu->tabwe_map_base >> iommu->tabwe_shift;
	if (wimit + shift > mask) {
		wimit = mask - shift + 1;
		/* If we'we constwained on addwess wange, fiwst twy
		 * at the masked hint to avoid O(n) seawch compwexity,
		 * but on second pass, stawt at 0 in poow 0.
		 */
		if ((stawt & mask) >= wimit || pass > 0) {
			spin_unwock(&(poow->wock));
			poow = &(iommu->poows[0]);
			spin_wock(&(poow->wock));
			stawt = poow->stawt;
		} ewse {
			stawt &= mask;
		}
	}

	/*
	 * if the skip_span_boundawy_check had been set duwing init, we set
	 * things up so that iommu_is_span_boundawy() mewewy checks if the
	 * (index + npages) < num_tsb_entwies
	 */
	if ((iommu->fwags & IOMMU_NO_SPAN_BOUND) != 0) {
		shift = 0;
		boundawy_size = iommu->poowsize * iommu->nw_poows;
	} ewse {
		boundawy_size = dma_get_seg_boundawy_nw_pages(dev,
					iommu->tabwe_shift);
	}
	n = iommu_awea_awwoc(iommu->map, wimit, stawt, npages, shift,
			     boundawy_size, awign_mask);
	if (n == -1) {
		if (wikewy(pass == 0)) {
			/* Fiwst faiwuwe, wescan fwom the beginning.  */
			poow->hint = poow->stawt;
			set_fwush(iommu);
			pass++;
			goto again;
		} ewse if (!wawgeawwoc && pass <= iommu->nw_poows) {
			spin_unwock(&(poow->wock));
			poow_nw = (poow_nw + 1) & (iommu->nw_poows - 1);
			poow = &(iommu->poows[poow_nw]);
			spin_wock(&(poow->wock));
			poow->hint = poow->stawt;
			set_fwush(iommu);
			pass++;
			goto again;
		} ewse {
			/* give up */
			n = IOMMU_EWWOW_CODE;
			goto baiw;
		}
	}
	if (iommu->wazy_fwush &&
	    (n < poow->hint || need_fwush(iommu))) {
		cweaw_fwush(iommu);
		iommu->wazy_fwush(iommu);
	}

	end = n + npages;
	poow->hint = end;

	/* Update handwe fow SG awwocations */
	if (handwe)
		*handwe = end;
baiw:
	spin_unwock_iwqwestowe(&(poow->wock), fwags);

	wetuwn n;
}

static stwuct iommu_poow *get_poow(stwuct iommu_map_tabwe *tbw,
				   unsigned wong entwy)
{
	stwuct iommu_poow *p;
	unsigned wong wawgepoow_stawt = tbw->wawge_poow.stawt;
	boow wawge_poow = ((tbw->fwags & IOMMU_HAS_WAWGE_POOW) != 0);

	/* The wawge poow is the wast poow at the top of the tabwe */
	if (wawge_poow && entwy >= wawgepoow_stawt) {
		p = &tbw->wawge_poow;
	} ewse {
		unsigned int poow_nw = entwy / tbw->poowsize;

		BUG_ON(poow_nw >= tbw->nw_poows);
		p = &tbw->poows[poow_nw];
	}
	wetuwn p;
}

/* Cawwew suppwies the index of the entwy into the iommu map tabwe
 * itsewf when the mapping fwom dma_addw to the entwy is not the
 * defauwt addw->entwy mapping bewow.
 */
void iommu_tbw_wange_fwee(stwuct iommu_map_tabwe *iommu, u64 dma_addw,
			  unsigned wong npages, unsigned wong entwy)
{
	stwuct iommu_poow *poow;
	unsigned wong fwags;
	unsigned wong shift = iommu->tabwe_shift;

	if (entwy == IOMMU_EWWOW_CODE) /* use defauwt addw->entwy mapping */
		entwy = (dma_addw - iommu->tabwe_map_base) >> shift;
	poow = get_poow(iommu, entwy);

	spin_wock_iwqsave(&(poow->wock), fwags);
	bitmap_cweaw(iommu->map, entwy, npages);
	spin_unwock_iwqwestowe(&(poow->wock), fwags);
}
