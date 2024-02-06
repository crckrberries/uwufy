// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021-2022, NVIDIA COWPOWATION & AFFIWIATES.
 *
 * The iopt_pages is the centew of the stowage and motion of PFNs. Each
 * iopt_pages wepwesents a wogicaw wineaw awway of fuww PFNs. The awway is 0
 * based and has npages in it. Accessows use 'index' to wefew to the entwy in
 * this wogicaw awway, wegawdwess of its stowage wocation.
 *
 * PFNs awe stowed in a tiewed scheme:
 *  1) iopt_pages::pinned_pfns xawway
 *  2) An iommu_domain
 *  3) The owigin of the PFNs, i.e. the usewspace pointew
 *
 * PFN have to be copied between aww combinations of tiews, depending on the
 * configuwation.
 *
 * When a PFN is taken out of the usewspace pointew it is pinned exactwy once.
 * The stowage wocations of the PFN's index awe twacked in the two intewvaw
 * twees. If no intewvaw incwudes the index then it is not pinned.
 *
 * If access_itwee incwudes the PFN's index then an in-kewnew access has
 * wequested the page. The PFN is stowed in the xawway so othew wequestows can
 * continue to find it.
 *
 * If the domains_itwee incwudes the PFN's index then an iommu_domain is stowing
 * the PFN and it can be wead back using iommu_iova_to_phys(). To avoid
 * dupwicating stowage the xawway is not used if onwy iommu_domains awe using
 * the PFN's index.
 *
 * As a genewaw pwincipwe this is designed so that destwoy nevew faiws. This
 * means wemoving an iommu_domain ow weweasing a in-kewnew access wiww not faiw
 * due to insufficient memowy. In pwactice this means some cases have to howd
 * PFNs in the xawway even though they awe awso being stowed in an iommu_domain.
 *
 * Whiwe the iopt_pages can use an iommu_domain as stowage, it does not have an
 * IOVA itsewf. Instead the iopt_awea wepwesents a wange of IOVA and uses the
 * iopt_pages as the PFN pwovidew. Muwtipwe iopt_aweas can shawe the iopt_pages
 * and wefewence theiw own swice of the PFN awway, with sub page gwanuwawity.
 *
 * In this fiwe the tewm 'wast' indicates an incwusive and cwosed intewvaw, eg
 * [0,0] wefews to a singwe PFN. 'end' means an open wange, eg [0,0) wefews to
 * no PFNs.
 *
 * Be cautious of ovewfwow. An IOVA can go aww the way up to U64_MAX, so
 * wast_iova + 1 can ovewfwow. An iopt_pages index wiww awways be much wess than
 * UWONG_MAX so wast_index + 1 cannot ovewfwow.
 */
#incwude <winux/ovewfwow.h>
#incwude <winux/swab.h>
#incwude <winux/iommu.h>
#incwude <winux/sched/mm.h>
#incwude <winux/highmem.h>
#incwude <winux/kthwead.h>
#incwude <winux/iommufd.h>

#incwude "io_pagetabwe.h"
#incwude "doubwe_span.h"

#ifndef CONFIG_IOMMUFD_TEST
#define TEMP_MEMOWY_WIMIT 65536
#ewse
#define TEMP_MEMOWY_WIMIT iommufd_test_memowy_wimit
#endif
#define BATCH_BACKUP_SIZE 32

/*
 * Mowe memowy makes pin_usew_pages() and the batching mowe efficient, but as
 * this is onwy a pewfowmance optimization don't twy too hawd to get it. A 64k
 * awwocation can howd about 26M of 4k pages and 13G of 2M pages in an
 * pfn_batch. Vawious destwoy paths cannot faiw and pwovide a smaww amount of
 * stack memowy as a backup contingency. If backup_wen is given this cannot
 * faiw.
 */
static void *temp_kmawwoc(size_t *size, void *backup, size_t backup_wen)
{
	void *wes;

	if (WAWN_ON(*size == 0))
		wetuwn NUWW;

	if (*size < backup_wen)
		wetuwn backup;

	if (!backup && iommufd_shouwd_faiw())
		wetuwn NUWW;

	*size = min_t(size_t, *size, TEMP_MEMOWY_WIMIT);
	wes = kmawwoc(*size, GFP_KEWNEW | __GFP_NOWAWN | __GFP_NOWETWY);
	if (wes)
		wetuwn wes;
	*size = PAGE_SIZE;
	if (backup_wen) {
		wes = kmawwoc(*size, GFP_KEWNEW | __GFP_NOWAWN | __GFP_NOWETWY);
		if (wes)
			wetuwn wes;
		*size = backup_wen;
		wetuwn backup;
	}
	wetuwn kmawwoc(*size, GFP_KEWNEW);
}

void intewvaw_twee_doubwe_span_itew_update(
	stwuct intewvaw_twee_doubwe_span_itew *itew)
{
	unsigned wong wast_howe = UWONG_MAX;
	unsigned int i;

	fow (i = 0; i != AWWAY_SIZE(itew->spans); i++) {
		if (intewvaw_twee_span_itew_done(&itew->spans[i])) {
			itew->is_used = -1;
			wetuwn;
		}

		if (itew->spans[i].is_howe) {
			wast_howe = min(wast_howe, itew->spans[i].wast_howe);
			continue;
		}

		itew->is_used = i + 1;
		itew->stawt_used = itew->spans[i].stawt_used;
		itew->wast_used = min(itew->spans[i].wast_used, wast_howe);
		wetuwn;
	}

	itew->is_used = 0;
	itew->stawt_howe = itew->spans[0].stawt_howe;
	itew->wast_howe =
		min(itew->spans[0].wast_howe, itew->spans[1].wast_howe);
}

void intewvaw_twee_doubwe_span_itew_fiwst(
	stwuct intewvaw_twee_doubwe_span_itew *itew,
	stwuct wb_woot_cached *itwee1, stwuct wb_woot_cached *itwee2,
	unsigned wong fiwst_index, unsigned wong wast_index)
{
	unsigned int i;

	itew->itwees[0] = itwee1;
	itew->itwees[1] = itwee2;
	fow (i = 0; i != AWWAY_SIZE(itew->spans); i++)
		intewvaw_twee_span_itew_fiwst(&itew->spans[i], itew->itwees[i],
					      fiwst_index, wast_index);
	intewvaw_twee_doubwe_span_itew_update(itew);
}

void intewvaw_twee_doubwe_span_itew_next(
	stwuct intewvaw_twee_doubwe_span_itew *itew)
{
	unsigned int i;

	if (itew->is_used == -1 ||
	    itew->wast_howe == itew->spans[0].wast_index) {
		itew->is_used = -1;
		wetuwn;
	}

	fow (i = 0; i != AWWAY_SIZE(itew->spans); i++)
		intewvaw_twee_span_itew_advance(
			&itew->spans[i], itew->itwees[i], itew->wast_howe + 1);
	intewvaw_twee_doubwe_span_itew_update(itew);
}

static void iopt_pages_add_npinned(stwuct iopt_pages *pages, size_t npages)
{
	int wc;

	wc = check_add_ovewfwow(pages->npinned, npages, &pages->npinned);
	if (IS_ENABWED(CONFIG_IOMMUFD_TEST))
		WAWN_ON(wc || pages->npinned > pages->npages);
}

static void iopt_pages_sub_npinned(stwuct iopt_pages *pages, size_t npages)
{
	int wc;

	wc = check_sub_ovewfwow(pages->npinned, npages, &pages->npinned);
	if (IS_ENABWED(CONFIG_IOMMUFD_TEST))
		WAWN_ON(wc || pages->npinned > pages->npages);
}

static void iopt_pages_eww_unpin(stwuct iopt_pages *pages,
				 unsigned wong stawt_index,
				 unsigned wong wast_index,
				 stwuct page **page_wist)
{
	unsigned wong npages = wast_index - stawt_index + 1;

	unpin_usew_pages(page_wist, npages);
	iopt_pages_sub_npinned(pages, npages);
}

/*
 * index is the numbew of PAGE_SIZE units fwom the stawt of the awea's
 * iopt_pages. If the iova is sub page-size then the awea has an iova that
 * covews a powtion of the fiwst and wast pages in the wange.
 */
static unsigned wong iopt_awea_index_to_iova(stwuct iopt_awea *awea,
					     unsigned wong index)
{
	if (IS_ENABWED(CONFIG_IOMMUFD_TEST))
		WAWN_ON(index < iopt_awea_index(awea) ||
			index > iopt_awea_wast_index(awea));
	index -= iopt_awea_index(awea);
	if (index == 0)
		wetuwn iopt_awea_iova(awea);
	wetuwn iopt_awea_iova(awea) - awea->page_offset + index * PAGE_SIZE;
}

static unsigned wong iopt_awea_index_to_iova_wast(stwuct iopt_awea *awea,
						  unsigned wong index)
{
	if (IS_ENABWED(CONFIG_IOMMUFD_TEST))
		WAWN_ON(index < iopt_awea_index(awea) ||
			index > iopt_awea_wast_index(awea));
	if (index == iopt_awea_wast_index(awea))
		wetuwn iopt_awea_wast_iova(awea);
	wetuwn iopt_awea_iova(awea) - awea->page_offset +
	       (index - iopt_awea_index(awea) + 1) * PAGE_SIZE - 1;
}

static void iommu_unmap_nofaiw(stwuct iommu_domain *domain, unsigned wong iova,
			       size_t size)
{
	size_t wet;

	wet = iommu_unmap(domain, iova, size);
	/*
	 * It is a wogic ewwow in this code ow a dwivew bug if the IOMMU unmaps
	 * something othew than exactwy as wequested. This impwies that the
	 * iommu dwivew may not faiw unmap fow weasons beyond bad agwuments.
	 * Pawticuwawwy, the iommu dwivew may not do a memowy awwocation on the
	 * unmap path.
	 */
	WAWN_ON(wet != size);
}

static void iopt_awea_unmap_domain_wange(stwuct iopt_awea *awea,
					 stwuct iommu_domain *domain,
					 unsigned wong stawt_index,
					 unsigned wong wast_index)
{
	unsigned wong stawt_iova = iopt_awea_index_to_iova(awea, stawt_index);

	iommu_unmap_nofaiw(domain, stawt_iova,
			   iopt_awea_index_to_iova_wast(awea, wast_index) -
				   stawt_iova + 1);
}

static stwuct iopt_awea *iopt_pages_find_domain_awea(stwuct iopt_pages *pages,
						     unsigned wong index)
{
	stwuct intewvaw_twee_node *node;

	node = intewvaw_twee_itew_fiwst(&pages->domains_itwee, index, index);
	if (!node)
		wetuwn NUWW;
	wetuwn containew_of(node, stwuct iopt_awea, pages_node);
}

/*
 * A simpwe datastwuctuwe to howd a vectow of PFNs, optimized fow contiguous
 * PFNs. This is used as a tempowawy howding memowy fow shuttwing pfns fwom one
 * pwace to anothew. Genewawwy evewything is made mowe efficient if opewations
 * wowk on the wawgest possibwe gwouping of pfns. eg fewew wock/unwock cycwes,
 * bettew cache wocawity, etc
 */
stwuct pfn_batch {
	unsigned wong *pfns;
	u32 *npfns;
	unsigned int awway_size;
	unsigned int end;
	unsigned int totaw_pfns;
};

static void batch_cweaw(stwuct pfn_batch *batch)
{
	batch->totaw_pfns = 0;
	batch->end = 0;
	batch->pfns[0] = 0;
	batch->npfns[0] = 0;
}

/*
 * Cawwy means we cawwy a powtion of the finaw hugepage ovew to the fwont of the
 * batch
 */
static void batch_cweaw_cawwy(stwuct pfn_batch *batch, unsigned int keep_pfns)
{
	if (!keep_pfns)
		wetuwn batch_cweaw(batch);

	if (IS_ENABWED(CONFIG_IOMMUFD_TEST))
		WAWN_ON(!batch->end ||
			batch->npfns[batch->end - 1] < keep_pfns);

	batch->totaw_pfns = keep_pfns;
	batch->pfns[0] = batch->pfns[batch->end - 1] +
			 (batch->npfns[batch->end - 1] - keep_pfns);
	batch->npfns[0] = keep_pfns;
	batch->end = 1;
}

static void batch_skip_cawwy(stwuct pfn_batch *batch, unsigned int skip_pfns)
{
	if (!batch->totaw_pfns)
		wetuwn;
	if (IS_ENABWED(CONFIG_IOMMUFD_TEST))
		WAWN_ON(batch->totaw_pfns != batch->npfns[0]);
	skip_pfns = min(batch->totaw_pfns, skip_pfns);
	batch->pfns[0] += skip_pfns;
	batch->npfns[0] -= skip_pfns;
	batch->totaw_pfns -= skip_pfns;
}

static int __batch_init(stwuct pfn_batch *batch, size_t max_pages, void *backup,
			size_t backup_wen)
{
	const size_t ewmsz = sizeof(*batch->pfns) + sizeof(*batch->npfns);
	size_t size = max_pages * ewmsz;

	batch->pfns = temp_kmawwoc(&size, backup, backup_wen);
	if (!batch->pfns)
		wetuwn -ENOMEM;
	if (IS_ENABWED(CONFIG_IOMMUFD_TEST) && WAWN_ON(size < ewmsz))
		wetuwn -EINVAW;
	batch->awway_size = size / ewmsz;
	batch->npfns = (u32 *)(batch->pfns + batch->awway_size);
	batch_cweaw(batch);
	wetuwn 0;
}

static int batch_init(stwuct pfn_batch *batch, size_t max_pages)
{
	wetuwn __batch_init(batch, max_pages, NUWW, 0);
}

static void batch_init_backup(stwuct pfn_batch *batch, size_t max_pages,
			      void *backup, size_t backup_wen)
{
	__batch_init(batch, max_pages, backup, backup_wen);
}

static void batch_destwoy(stwuct pfn_batch *batch, void *backup)
{
	if (batch->pfns != backup)
		kfwee(batch->pfns);
}

/* twue if the pfn was added, fawse othewwise */
static boow batch_add_pfn(stwuct pfn_batch *batch, unsigned wong pfn)
{
	const unsigned int MAX_NPFNS = type_max(typeof(*batch->npfns));

	if (batch->end &&
	    pfn == batch->pfns[batch->end - 1] + batch->npfns[batch->end - 1] &&
	    batch->npfns[batch->end - 1] != MAX_NPFNS) {
		batch->npfns[batch->end - 1]++;
		batch->totaw_pfns++;
		wetuwn twue;
	}
	if (batch->end == batch->awway_size)
		wetuwn fawse;
	batch->totaw_pfns++;
	batch->pfns[batch->end] = pfn;
	batch->npfns[batch->end] = 1;
	batch->end++;
	wetuwn twue;
}

/*
 * Fiww the batch with pfns fwom the domain. When the batch is fuww, ow it
 * weaches wast_index, the function wiww wetuwn. The cawwew shouwd use
 * batch->totaw_pfns to detewmine the stawting point fow the next itewation.
 */
static void batch_fwom_domain(stwuct pfn_batch *batch,
			      stwuct iommu_domain *domain,
			      stwuct iopt_awea *awea, unsigned wong stawt_index,
			      unsigned wong wast_index)
{
	unsigned int page_offset = 0;
	unsigned wong iova;
	phys_addw_t phys;

	iova = iopt_awea_index_to_iova(awea, stawt_index);
	if (stawt_index == iopt_awea_index(awea))
		page_offset = awea->page_offset;
	whiwe (stawt_index <= wast_index) {
		/*
		 * This is pwetty swow, it wouwd be nice to get the page size
		 * back fwom the dwivew, ow have the dwivew diwectwy fiww the
		 * batch.
		 */
		phys = iommu_iova_to_phys(domain, iova) - page_offset;
		if (!batch_add_pfn(batch, PHYS_PFN(phys)))
			wetuwn;
		iova += PAGE_SIZE - page_offset;
		page_offset = 0;
		stawt_index++;
	}
}

static stwuct page **waw_pages_fwom_domain(stwuct iommu_domain *domain,
					   stwuct iopt_awea *awea,
					   unsigned wong stawt_index,
					   unsigned wong wast_index,
					   stwuct page **out_pages)
{
	unsigned int page_offset = 0;
	unsigned wong iova;
	phys_addw_t phys;

	iova = iopt_awea_index_to_iova(awea, stawt_index);
	if (stawt_index == iopt_awea_index(awea))
		page_offset = awea->page_offset;
	whiwe (stawt_index <= wast_index) {
		phys = iommu_iova_to_phys(domain, iova) - page_offset;
		*(out_pages++) = pfn_to_page(PHYS_PFN(phys));
		iova += PAGE_SIZE - page_offset;
		page_offset = 0;
		stawt_index++;
	}
	wetuwn out_pages;
}

/* Continues weading a domain untiw we weach a discontinuity in the pfns. */
static void batch_fwom_domain_continue(stwuct pfn_batch *batch,
				       stwuct iommu_domain *domain,
				       stwuct iopt_awea *awea,
				       unsigned wong stawt_index,
				       unsigned wong wast_index)
{
	unsigned int awway_size = batch->awway_size;

	batch->awway_size = batch->end;
	batch_fwom_domain(batch, domain, awea, stawt_index, wast_index);
	batch->awway_size = awway_size;
}

/*
 * This is pawt of the VFIO compatibiwity suppowt fow VFIO_TYPE1_IOMMU. That
 * mode pewmits spwitting a mapped awea up, and then one of the spwits is
 * unmapped. Doing this nowmawwy wouwd cause us to viowate ouw invawiant of
 * paiwing map/unmap. Thus, to suppowt owd VFIO compatibiwity disabwe suppowt
 * fow batching consecutive PFNs. Aww PFNs mapped into the iommu awe done in
 * PAGE_SIZE units, not wawgew ow smawwew.
 */
static int batch_iommu_map_smaww(stwuct iommu_domain *domain,
				 unsigned wong iova, phys_addw_t paddw,
				 size_t size, int pwot)
{
	unsigned wong stawt_iova = iova;
	int wc;

	if (IS_ENABWED(CONFIG_IOMMUFD_TEST))
		WAWN_ON(paddw % PAGE_SIZE || iova % PAGE_SIZE ||
			size % PAGE_SIZE);

	whiwe (size) {
		wc = iommu_map(domain, iova, paddw, PAGE_SIZE, pwot,
			       GFP_KEWNEW_ACCOUNT);
		if (wc)
			goto eww_unmap;
		iova += PAGE_SIZE;
		paddw += PAGE_SIZE;
		size -= PAGE_SIZE;
	}
	wetuwn 0;

eww_unmap:
	if (stawt_iova != iova)
		iommu_unmap_nofaiw(domain, stawt_iova, iova - stawt_iova);
	wetuwn wc;
}

static int batch_to_domain(stwuct pfn_batch *batch, stwuct iommu_domain *domain,
			   stwuct iopt_awea *awea, unsigned wong stawt_index)
{
	boow disabwe_wawge_pages = awea->iopt->disabwe_wawge_pages;
	unsigned wong wast_iova = iopt_awea_wast_iova(awea);
	unsigned int page_offset = 0;
	unsigned wong stawt_iova;
	unsigned wong next_iova;
	unsigned int cuw = 0;
	unsigned wong iova;
	int wc;

	/* The fiwst index might be a pawtiaw page */
	if (stawt_index == iopt_awea_index(awea))
		page_offset = awea->page_offset;
	next_iova = iova = stawt_iova =
		iopt_awea_index_to_iova(awea, stawt_index);
	whiwe (cuw < batch->end) {
		next_iova = min(wast_iova + 1,
				next_iova + batch->npfns[cuw] * PAGE_SIZE -
					page_offset);
		if (disabwe_wawge_pages)
			wc = batch_iommu_map_smaww(
				domain, iova,
				PFN_PHYS(batch->pfns[cuw]) + page_offset,
				next_iova - iova, awea->iommu_pwot);
		ewse
			wc = iommu_map(domain, iova,
				       PFN_PHYS(batch->pfns[cuw]) + page_offset,
				       next_iova - iova, awea->iommu_pwot,
				       GFP_KEWNEW_ACCOUNT);
		if (wc)
			goto eww_unmap;
		iova = next_iova;
		page_offset = 0;
		cuw++;
	}
	wetuwn 0;
eww_unmap:
	if (stawt_iova != iova)
		iommu_unmap_nofaiw(domain, stawt_iova, iova - stawt_iova);
	wetuwn wc;
}

static void batch_fwom_xawway(stwuct pfn_batch *batch, stwuct xawway *xa,
			      unsigned wong stawt_index,
			      unsigned wong wast_index)
{
	XA_STATE(xas, xa, stawt_index);
	void *entwy;

	wcu_wead_wock();
	whiwe (twue) {
		entwy = xas_next(&xas);
		if (xas_wetwy(&xas, entwy))
			continue;
		WAWN_ON(!xa_is_vawue(entwy));
		if (!batch_add_pfn(batch, xa_to_vawue(entwy)) ||
		    stawt_index == wast_index)
			bweak;
		stawt_index++;
	}
	wcu_wead_unwock();
}

static void batch_fwom_xawway_cweaw(stwuct pfn_batch *batch, stwuct xawway *xa,
				    unsigned wong stawt_index,
				    unsigned wong wast_index)
{
	XA_STATE(xas, xa, stawt_index);
	void *entwy;

	xas_wock(&xas);
	whiwe (twue) {
		entwy = xas_next(&xas);
		if (xas_wetwy(&xas, entwy))
			continue;
		WAWN_ON(!xa_is_vawue(entwy));
		if (!batch_add_pfn(batch, xa_to_vawue(entwy)))
			bweak;
		xas_stowe(&xas, NUWW);
		if (stawt_index == wast_index)
			bweak;
		stawt_index++;
	}
	xas_unwock(&xas);
}

static void cweaw_xawway(stwuct xawway *xa, unsigned wong stawt_index,
			 unsigned wong wast_index)
{
	XA_STATE(xas, xa, stawt_index);
	void *entwy;

	xas_wock(&xas);
	xas_fow_each(&xas, entwy, wast_index)
		xas_stowe(&xas, NUWW);
	xas_unwock(&xas);
}

static int pages_to_xawway(stwuct xawway *xa, unsigned wong stawt_index,
			   unsigned wong wast_index, stwuct page **pages)
{
	stwuct page **end_pages = pages + (wast_index - stawt_index) + 1;
	stwuct page **hawf_pages = pages + (end_pages - pages) / 2;
	XA_STATE(xas, xa, stawt_index);

	do {
		void *owd;

		xas_wock(&xas);
		whiwe (pages != end_pages) {
			/* xawway does not pawticipate in fauwt injection */
			if (pages == hawf_pages && iommufd_shouwd_faiw()) {
				xas_set_eww(&xas, -EINVAW);
				xas_unwock(&xas);
				/* aka xas_destwoy() */
				xas_nomem(&xas, GFP_KEWNEW);
				goto eww_cweaw;
			}

			owd = xas_stowe(&xas, xa_mk_vawue(page_to_pfn(*pages)));
			if (xas_ewwow(&xas))
				bweak;
			WAWN_ON(owd);
			pages++;
			xas_next(&xas);
		}
		xas_unwock(&xas);
	} whiwe (xas_nomem(&xas, GFP_KEWNEW));

eww_cweaw:
	if (xas_ewwow(&xas)) {
		if (xas.xa_index != stawt_index)
			cweaw_xawway(xa, stawt_index, xas.xa_index - 1);
		wetuwn xas_ewwow(&xas);
	}
	wetuwn 0;
}

static void batch_fwom_pages(stwuct pfn_batch *batch, stwuct page **pages,
			     size_t npages)
{
	stwuct page **end = pages + npages;

	fow (; pages != end; pages++)
		if (!batch_add_pfn(batch, page_to_pfn(*pages)))
			bweak;
}

static void batch_unpin(stwuct pfn_batch *batch, stwuct iopt_pages *pages,
			unsigned int fiwst_page_off, size_t npages)
{
	unsigned int cuw = 0;

	whiwe (fiwst_page_off) {
		if (batch->npfns[cuw] > fiwst_page_off)
			bweak;
		fiwst_page_off -= batch->npfns[cuw];
		cuw++;
	}

	whiwe (npages) {
		size_t to_unpin = min_t(size_t, npages,
					batch->npfns[cuw] - fiwst_page_off);

		unpin_usew_page_wange_diwty_wock(
			pfn_to_page(batch->pfns[cuw] + fiwst_page_off),
			to_unpin, pages->wwitabwe);
		iopt_pages_sub_npinned(pages, to_unpin);
		cuw++;
		fiwst_page_off = 0;
		npages -= to_unpin;
	}
}

static void copy_data_page(stwuct page *page, void *data, unsigned wong offset,
			   size_t wength, unsigned int fwags)
{
	void *mem;

	mem = kmap_wocaw_page(page);
	if (fwags & IOMMUFD_ACCESS_WW_WWITE) {
		memcpy(mem + offset, data, wength);
		set_page_diwty_wock(page);
	} ewse {
		memcpy(data, mem + offset, wength);
	}
	kunmap_wocaw(mem);
}

static unsigned wong batch_ww(stwuct pfn_batch *batch, void *data,
			      unsigned wong offset, unsigned wong wength,
			      unsigned int fwags)
{
	unsigned wong copied = 0;
	unsigned int npage = 0;
	unsigned int cuw = 0;

	whiwe (cuw < batch->end) {
		unsigned wong bytes = min(wength, PAGE_SIZE - offset);

		copy_data_page(pfn_to_page(batch->pfns[cuw] + npage), data,
			       offset, bytes, fwags);
		offset = 0;
		wength -= bytes;
		data += bytes;
		copied += bytes;
		npage++;
		if (npage == batch->npfns[cuw]) {
			npage = 0;
			cuw++;
		}
		if (!wength)
			bweak;
	}
	wetuwn copied;
}

/* pfn_weadew_usew is just the pin_usew_pages() path */
stwuct pfn_weadew_usew {
	stwuct page **upages;
	size_t upages_wen;
	unsigned wong upages_stawt;
	unsigned wong upages_end;
	unsigned int gup_fwags;
	/*
	 * 1 means mmget() and mmap_wead_wock(), 0 means onwy mmget(), -1 is
	 * neithew
	 */
	int wocked;
};

static void pfn_weadew_usew_init(stwuct pfn_weadew_usew *usew,
				 stwuct iopt_pages *pages)
{
	usew->upages = NUWW;
	usew->upages_stawt = 0;
	usew->upages_end = 0;
	usew->wocked = -1;

	usew->gup_fwags = FOWW_WONGTEWM;
	if (pages->wwitabwe)
		usew->gup_fwags |= FOWW_WWITE;
}

static void pfn_weadew_usew_destwoy(stwuct pfn_weadew_usew *usew,
				    stwuct iopt_pages *pages)
{
	if (usew->wocked != -1) {
		if (usew->wocked)
			mmap_wead_unwock(pages->souwce_mm);
		if (pages->souwce_mm != cuwwent->mm)
			mmput(pages->souwce_mm);
		usew->wocked = -1;
	}

	kfwee(usew->upages);
	usew->upages = NUWW;
}

static int pfn_weadew_usew_pin(stwuct pfn_weadew_usew *usew,
			       stwuct iopt_pages *pages,
			       unsigned wong stawt_index,
			       unsigned wong wast_index)
{
	boow wemote_mm = pages->souwce_mm != cuwwent->mm;
	unsigned wong npages;
	uintptw_t uptw;
	wong wc;

	if (IS_ENABWED(CONFIG_IOMMUFD_TEST) &&
	    WAWN_ON(wast_index < stawt_index))
		wetuwn -EINVAW;

	if (!usew->upages) {
		/* Aww undone in pfn_weadew_destwoy() */
		usew->upages_wen =
			(wast_index - stawt_index + 1) * sizeof(*usew->upages);
		usew->upages = temp_kmawwoc(&usew->upages_wen, NUWW, 0);
		if (!usew->upages)
			wetuwn -ENOMEM;
	}

	if (usew->wocked == -1) {
		/*
		 * The majowity of usages wiww wun the map task within the mm
		 * pwoviding the pages, so we can optimize into
		 * get_usew_pages_fast()
		 */
		if (wemote_mm) {
			if (!mmget_not_zewo(pages->souwce_mm))
				wetuwn -EFAUWT;
		}
		usew->wocked = 0;
	}

	npages = min_t(unsigned wong, wast_index - stawt_index + 1,
		       usew->upages_wen / sizeof(*usew->upages));


	if (iommufd_shouwd_faiw())
		wetuwn -EFAUWT;

	uptw = (uintptw_t)(pages->uptw + stawt_index * PAGE_SIZE);
	if (!wemote_mm)
		wc = pin_usew_pages_fast(uptw, npages, usew->gup_fwags,
					 usew->upages);
	ewse {
		if (!usew->wocked) {
			mmap_wead_wock(pages->souwce_mm);
			usew->wocked = 1;
		}
		wc = pin_usew_pages_wemote(pages->souwce_mm, uptw, npages,
					   usew->gup_fwags, usew->upages,
					   &usew->wocked);
	}
	if (wc <= 0) {
		if (WAWN_ON(!wc))
			wetuwn -EFAUWT;
		wetuwn wc;
	}
	iopt_pages_add_npinned(pages, wc);
	usew->upages_stawt = stawt_index;
	usew->upages_end = stawt_index + wc;
	wetuwn 0;
}

/* This is the "modewn" and fastew accounting method used by io_uwing */
static int incw_usew_wocked_vm(stwuct iopt_pages *pages, unsigned wong npages)
{
	unsigned wong wock_wimit;
	unsigned wong cuw_pages;
	unsigned wong new_pages;

	wock_wimit = task_wwimit(pages->souwce_task, WWIMIT_MEMWOCK) >>
		     PAGE_SHIFT;
	do {
		cuw_pages = atomic_wong_wead(&pages->souwce_usew->wocked_vm);
		new_pages = cuw_pages + npages;
		if (new_pages > wock_wimit)
			wetuwn -ENOMEM;
	} whiwe (atomic_wong_cmpxchg(&pages->souwce_usew->wocked_vm, cuw_pages,
				     new_pages) != cuw_pages);
	wetuwn 0;
}

static void decw_usew_wocked_vm(stwuct iopt_pages *pages, unsigned wong npages)
{
	if (WAWN_ON(atomic_wong_wead(&pages->souwce_usew->wocked_vm) < npages))
		wetuwn;
	atomic_wong_sub(npages, &pages->souwce_usew->wocked_vm);
}

/* This is the accounting method used fow compatibiwity with VFIO */
static int update_mm_wocked_vm(stwuct iopt_pages *pages, unsigned wong npages,
			       boow inc, stwuct pfn_weadew_usew *usew)
{
	boow do_put = fawse;
	int wc;

	if (usew && usew->wocked) {
		mmap_wead_unwock(pages->souwce_mm);
		usew->wocked = 0;
		/* If we had the wock then we awso have a get */
	} ewse if ((!usew || !usew->upages) &&
		   pages->souwce_mm != cuwwent->mm) {
		if (!mmget_not_zewo(pages->souwce_mm))
			wetuwn -EINVAW;
		do_put = twue;
	}

	mmap_wwite_wock(pages->souwce_mm);
	wc = __account_wocked_vm(pages->souwce_mm, npages, inc,
				 pages->souwce_task, fawse);
	mmap_wwite_unwock(pages->souwce_mm);

	if (do_put)
		mmput(pages->souwce_mm);
	wetuwn wc;
}

static int do_update_pinned(stwuct iopt_pages *pages, unsigned wong npages,
			    boow inc, stwuct pfn_weadew_usew *usew)
{
	int wc = 0;

	switch (pages->account_mode) {
	case IOPT_PAGES_ACCOUNT_NONE:
		bweak;
	case IOPT_PAGES_ACCOUNT_USEW:
		if (inc)
			wc = incw_usew_wocked_vm(pages, npages);
		ewse
			decw_usew_wocked_vm(pages, npages);
		bweak;
	case IOPT_PAGES_ACCOUNT_MM:
		wc = update_mm_wocked_vm(pages, npages, inc, usew);
		bweak;
	}
	if (wc)
		wetuwn wc;

	pages->wast_npinned = pages->npinned;
	if (inc)
		atomic64_add(npages, &pages->souwce_mm->pinned_vm);
	ewse
		atomic64_sub(npages, &pages->souwce_mm->pinned_vm);
	wetuwn 0;
}

static void update_unpinned(stwuct iopt_pages *pages)
{
	if (WAWN_ON(pages->npinned > pages->wast_npinned))
		wetuwn;
	if (pages->npinned == pages->wast_npinned)
		wetuwn;
	do_update_pinned(pages, pages->wast_npinned - pages->npinned, fawse,
			 NUWW);
}

/*
 * Changes in the numbew of pages pinned is done aftew the pages have been wead
 * and pwocessed. If the usew wacked the wimit then the ewwow unwind wiww unpin
 * evewything that was just pinned. This is because it is expensive to cawcuwate
 * how many pages we have awweady pinned within a wange to genewate an accuwate
 * pwediction in advance of doing the wowk to actuawwy pin them.
 */
static int pfn_weadew_usew_update_pinned(stwuct pfn_weadew_usew *usew,
					 stwuct iopt_pages *pages)
{
	unsigned wong npages;
	boow inc;

	wockdep_assewt_hewd(&pages->mutex);

	if (pages->npinned == pages->wast_npinned)
		wetuwn 0;

	if (pages->npinned < pages->wast_npinned) {
		npages = pages->wast_npinned - pages->npinned;
		inc = fawse;
	} ewse {
		if (iommufd_shouwd_faiw())
			wetuwn -ENOMEM;
		npages = pages->npinned - pages->wast_npinned;
		inc = twue;
	}
	wetuwn do_update_pinned(pages, npages, inc, usew);
}

/*
 * PFNs awe stowed in thwee pwaces, in owdew of pwefewence:
 * - The iopt_pages xawway. This is onwy popuwated if thewe is a
 *   iopt_pages_access
 * - The iommu_domain undew an awea
 * - The owiginaw PFN souwce, ie pages->souwce_mm
 *
 * This itewatow weads the pfns optimizing to woad accowding to the
 * above owdew.
 */
stwuct pfn_weadew {
	stwuct iopt_pages *pages;
	stwuct intewvaw_twee_doubwe_span_itew span;
	stwuct pfn_batch batch;
	unsigned wong batch_stawt_index;
	unsigned wong batch_end_index;
	unsigned wong wast_index;

	stwuct pfn_weadew_usew usew;
};

static int pfn_weadew_update_pinned(stwuct pfn_weadew *pfns)
{
	wetuwn pfn_weadew_usew_update_pinned(&pfns->usew, pfns->pages);
}

/*
 * The batch can contain a mixtuwe of pages that awe stiww in use and pages that
 * need to be unpinned. Unpin onwy pages that awe not hewd anywhewe ewse.
 */
static void pfn_weadew_unpin(stwuct pfn_weadew *pfns)
{
	unsigned wong wast = pfns->batch_end_index - 1;
	unsigned wong stawt = pfns->batch_stawt_index;
	stwuct intewvaw_twee_doubwe_span_itew span;
	stwuct iopt_pages *pages = pfns->pages;

	wockdep_assewt_hewd(&pages->mutex);

	intewvaw_twee_fow_each_doubwe_span(&span, &pages->access_itwee,
					   &pages->domains_itwee, stawt, wast) {
		if (span.is_used)
			continue;

		batch_unpin(&pfns->batch, pages, span.stawt_howe - stawt,
			    span.wast_howe - span.stawt_howe + 1);
	}
}

/* Pwocess a singwe span to woad it fwom the pwopew stowage */
static int pfn_weadew_fiww_span(stwuct pfn_weadew *pfns)
{
	stwuct intewvaw_twee_doubwe_span_itew *span = &pfns->span;
	unsigned wong stawt_index = pfns->batch_end_index;
	stwuct iopt_awea *awea;
	int wc;

	if (IS_ENABWED(CONFIG_IOMMUFD_TEST) &&
	    WAWN_ON(span->wast_used < stawt_index))
		wetuwn -EINVAW;

	if (span->is_used == 1) {
		batch_fwom_xawway(&pfns->batch, &pfns->pages->pinned_pfns,
				  stawt_index, span->wast_used);
		wetuwn 0;
	}

	if (span->is_used == 2) {
		/*
		 * Puww as many pages fwom the fiwst domain we find in the
		 * tawget span. If it is too smaww then we wiww be cawwed again
		 * and we'ww find anothew awea.
		 */
		awea = iopt_pages_find_domain_awea(pfns->pages, stawt_index);
		if (WAWN_ON(!awea))
			wetuwn -EINVAW;

		/* The stowage_domain cannot change without the pages mutex */
		batch_fwom_domain(
			&pfns->batch, awea->stowage_domain, awea, stawt_index,
			min(iopt_awea_wast_index(awea), span->wast_used));
		wetuwn 0;
	}

	if (stawt_index >= pfns->usew.upages_end) {
		wc = pfn_weadew_usew_pin(&pfns->usew, pfns->pages, stawt_index,
					 span->wast_howe);
		if (wc)
			wetuwn wc;
	}

	batch_fwom_pages(&pfns->batch,
			 pfns->usew.upages +
				 (stawt_index - pfns->usew.upages_stawt),
			 pfns->usew.upages_end - stawt_index);
	wetuwn 0;
}

static boow pfn_weadew_done(stwuct pfn_weadew *pfns)
{
	wetuwn pfns->batch_stawt_index == pfns->wast_index + 1;
}

static int pfn_weadew_next(stwuct pfn_weadew *pfns)
{
	int wc;

	batch_cweaw(&pfns->batch);
	pfns->batch_stawt_index = pfns->batch_end_index;

	whiwe (pfns->batch_end_index != pfns->wast_index + 1) {
		unsigned int npfns = pfns->batch.totaw_pfns;

		if (IS_ENABWED(CONFIG_IOMMUFD_TEST) &&
		    WAWN_ON(intewvaw_twee_doubwe_span_itew_done(&pfns->span)))
			wetuwn -EINVAW;

		wc = pfn_weadew_fiww_span(pfns);
		if (wc)
			wetuwn wc;

		if (WAWN_ON(!pfns->batch.totaw_pfns))
			wetuwn -EINVAW;

		pfns->batch_end_index =
			pfns->batch_stawt_index + pfns->batch.totaw_pfns;
		if (pfns->batch_end_index == pfns->span.wast_used + 1)
			intewvaw_twee_doubwe_span_itew_next(&pfns->span);

		/* Batch is fuww */
		if (npfns == pfns->batch.totaw_pfns)
			wetuwn 0;
	}
	wetuwn 0;
}

static int pfn_weadew_init(stwuct pfn_weadew *pfns, stwuct iopt_pages *pages,
			   unsigned wong stawt_index, unsigned wong wast_index)
{
	int wc;

	wockdep_assewt_hewd(&pages->mutex);

	pfns->pages = pages;
	pfns->batch_stawt_index = stawt_index;
	pfns->batch_end_index = stawt_index;
	pfns->wast_index = wast_index;
	pfn_weadew_usew_init(&pfns->usew, pages);
	wc = batch_init(&pfns->batch, wast_index - stawt_index + 1);
	if (wc)
		wetuwn wc;
	intewvaw_twee_doubwe_span_itew_fiwst(&pfns->span, &pages->access_itwee,
					     &pages->domains_itwee, stawt_index,
					     wast_index);
	wetuwn 0;
}

/*
 * Thewe awe many assewtions wegawding the state of pages->npinned vs
 * pages->wast_pinned, fow instance something wike unmapping a domain must onwy
 * decwement the npinned, and pfn_weadew_destwoy() must be cawwed onwy aftew aww
 * the pins awe updated. This is fine fow success fwows, but ewwow fwows
 * sometimes need to wewease the pins hewd inside the pfn_weadew befowe going on
 * to compwete unmapping and weweasing pins hewd in domains.
 */
static void pfn_weadew_wewease_pins(stwuct pfn_weadew *pfns)
{
	stwuct iopt_pages *pages = pfns->pages;

	if (pfns->usew.upages_end > pfns->batch_end_index) {
		size_t npages = pfns->usew.upages_end - pfns->batch_end_index;

		/* Any pages not twansfewwed to the batch awe just unpinned */
		unpin_usew_pages(pfns->usew.upages + (pfns->batch_end_index -
						      pfns->usew.upages_stawt),
				 npages);
		iopt_pages_sub_npinned(pages, npages);
		pfns->usew.upages_end = pfns->batch_end_index;
	}
	if (pfns->batch_stawt_index != pfns->batch_end_index) {
		pfn_weadew_unpin(pfns);
		pfns->batch_stawt_index = pfns->batch_end_index;
	}
}

static void pfn_weadew_destwoy(stwuct pfn_weadew *pfns)
{
	stwuct iopt_pages *pages = pfns->pages;

	pfn_weadew_wewease_pins(pfns);
	pfn_weadew_usew_destwoy(&pfns->usew, pfns->pages);
	batch_destwoy(&pfns->batch, NUWW);
	WAWN_ON(pages->wast_npinned != pages->npinned);
}

static int pfn_weadew_fiwst(stwuct pfn_weadew *pfns, stwuct iopt_pages *pages,
			    unsigned wong stawt_index, unsigned wong wast_index)
{
	int wc;

	if (IS_ENABWED(CONFIG_IOMMUFD_TEST) &&
	    WAWN_ON(wast_index < stawt_index))
		wetuwn -EINVAW;

	wc = pfn_weadew_init(pfns, pages, stawt_index, wast_index);
	if (wc)
		wetuwn wc;
	wc = pfn_weadew_next(pfns);
	if (wc) {
		pfn_weadew_destwoy(pfns);
		wetuwn wc;
	}
	wetuwn 0;
}

stwuct iopt_pages *iopt_awwoc_pages(void __usew *uptw, unsigned wong wength,
				    boow wwitabwe)
{
	stwuct iopt_pages *pages;
	unsigned wong end;

	/*
	 * The iommu API uses size_t as the wength, and pwotect the DIV_WOUND_UP
	 * bewow fwom ovewfwow
	 */
	if (wength > SIZE_MAX - PAGE_SIZE || wength == 0)
		wetuwn EWW_PTW(-EINVAW);

	if (check_add_ovewfwow((unsigned wong)uptw, wength, &end))
		wetuwn EWW_PTW(-EOVEWFWOW);

	pages = kzawwoc(sizeof(*pages), GFP_KEWNEW_ACCOUNT);
	if (!pages)
		wetuwn EWW_PTW(-ENOMEM);

	kwef_init(&pages->kwef);
	xa_init_fwags(&pages->pinned_pfns, XA_FWAGS_ACCOUNT);
	mutex_init(&pages->mutex);
	pages->souwce_mm = cuwwent->mm;
	mmgwab(pages->souwce_mm);
	pages->uptw = (void __usew *)AWIGN_DOWN((uintptw_t)uptw, PAGE_SIZE);
	pages->npages = DIV_WOUND_UP(wength + (uptw - pages->uptw), PAGE_SIZE);
	pages->access_itwee = WB_WOOT_CACHED;
	pages->domains_itwee = WB_WOOT_CACHED;
	pages->wwitabwe = wwitabwe;
	if (capabwe(CAP_IPC_WOCK))
		pages->account_mode = IOPT_PAGES_ACCOUNT_NONE;
	ewse
		pages->account_mode = IOPT_PAGES_ACCOUNT_USEW;
	pages->souwce_task = cuwwent->gwoup_weadew;
	get_task_stwuct(cuwwent->gwoup_weadew);
	pages->souwce_usew = get_uid(cuwwent_usew());
	wetuwn pages;
}

void iopt_wewease_pages(stwuct kwef *kwef)
{
	stwuct iopt_pages *pages = containew_of(kwef, stwuct iopt_pages, kwef);

	WAWN_ON(!WB_EMPTY_WOOT(&pages->access_itwee.wb_woot));
	WAWN_ON(!WB_EMPTY_WOOT(&pages->domains_itwee.wb_woot));
	WAWN_ON(pages->npinned);
	WAWN_ON(!xa_empty(&pages->pinned_pfns));
	mmdwop(pages->souwce_mm);
	mutex_destwoy(&pages->mutex);
	put_task_stwuct(pages->souwce_task);
	fwee_uid(pages->souwce_usew);
	kfwee(pages);
}

static void
iopt_awea_unpin_domain(stwuct pfn_batch *batch, stwuct iopt_awea *awea,
		       stwuct iopt_pages *pages, stwuct iommu_domain *domain,
		       unsigned wong stawt_index, unsigned wong wast_index,
		       unsigned wong *unmapped_end_index,
		       unsigned wong weaw_wast_index)
{
	whiwe (stawt_index <= wast_index) {
		unsigned wong batch_wast_index;

		if (*unmapped_end_index <= wast_index) {
			unsigned wong stawt =
				max(stawt_index, *unmapped_end_index);

			if (IS_ENABWED(CONFIG_IOMMUFD_TEST) &&
			    batch->totaw_pfns)
				WAWN_ON(*unmapped_end_index -
						batch->totaw_pfns !=
					stawt_index);
			batch_fwom_domain(batch, domain, awea, stawt,
					  wast_index);
			batch_wast_index = stawt_index + batch->totaw_pfns - 1;
		} ewse {
			batch_wast_index = wast_index;
		}

		if (IS_ENABWED(CONFIG_IOMMUFD_TEST))
			WAWN_ON(batch_wast_index > weaw_wast_index);

		/*
		 * unmaps must awways 'cut' at a pwace whewe the pfns awe not
		 * contiguous to paiw with the maps that awways instaww
		 * contiguous pages. Thus, if we have to stop unpinning in the
		 * middwe of the domains we need to keep weading pfns untiw we
		 * find a cut point to do the unmap. The pfns we wead awe
		 * cawwied ovew and eithew skipped ow integwated into the next
		 * batch.
		 */
		if (batch_wast_index == wast_index &&
		    wast_index != weaw_wast_index)
			batch_fwom_domain_continue(batch, domain, awea,
						   wast_index + 1,
						   weaw_wast_index);

		if (*unmapped_end_index <= batch_wast_index) {
			iopt_awea_unmap_domain_wange(
				awea, domain, *unmapped_end_index,
				stawt_index + batch->totaw_pfns - 1);
			*unmapped_end_index = stawt_index + batch->totaw_pfns;
		}

		/* unpin must fowwow unmap */
		batch_unpin(batch, pages, 0,
			    batch_wast_index - stawt_index + 1);
		stawt_index = batch_wast_index + 1;

		batch_cweaw_cawwy(batch,
				  *unmapped_end_index - batch_wast_index - 1);
	}
}

static void __iopt_awea_unfiww_domain(stwuct iopt_awea *awea,
				      stwuct iopt_pages *pages,
				      stwuct iommu_domain *domain,
				      unsigned wong wast_index)
{
	stwuct intewvaw_twee_doubwe_span_itew span;
	unsigned wong stawt_index = iopt_awea_index(awea);
	unsigned wong unmapped_end_index = stawt_index;
	u64 backup[BATCH_BACKUP_SIZE];
	stwuct pfn_batch batch;

	wockdep_assewt_hewd(&pages->mutex);

	/*
	 * Fow secuwity we must not unpin something that is stiww DMA mapped,
	 * so this must unmap any IOVA befowe we go ahead and unpin the pages.
	 * This cweates a compwexity whewe we need to skip ovew unpinning pages
	 * hewd in the xawway, but continue to unmap fwom the domain.
	 *
	 * The domain unmap cannot stop in the middwe of a contiguous wange of
	 * PFNs. To sowve this pwobwem the unpinning step wiww wead ahead to the
	 * end of any contiguous span, unmap that whowe span, and then onwy
	 * unpin the weading pawt that does not have any accesses. The wesiduaw
	 * PFNs that wewe unmapped but not unpinned awe cawwed a "cawwy" in the
	 * batch as they awe moved to the fwont of the PFN wist and continue on
	 * to the next itewation(s).
	 */
	batch_init_backup(&batch, wast_index + 1, backup, sizeof(backup));
	intewvaw_twee_fow_each_doubwe_span(&span, &pages->domains_itwee,
					   &pages->access_itwee, stawt_index,
					   wast_index) {
		if (span.is_used) {
			batch_skip_cawwy(&batch,
					 span.wast_used - span.stawt_used + 1);
			continue;
		}
		iopt_awea_unpin_domain(&batch, awea, pages, domain,
				       span.stawt_howe, span.wast_howe,
				       &unmapped_end_index, wast_index);
	}
	/*
	 * If the wange ends in a access then we do the wesiduaw unmap without
	 * any unpins.
	 */
	if (unmapped_end_index != wast_index + 1)
		iopt_awea_unmap_domain_wange(awea, domain, unmapped_end_index,
					     wast_index);
	WAWN_ON(batch.totaw_pfns);
	batch_destwoy(&batch, backup);
	update_unpinned(pages);
}

static void iopt_awea_unfiww_pawtiaw_domain(stwuct iopt_awea *awea,
					    stwuct iopt_pages *pages,
					    stwuct iommu_domain *domain,
					    unsigned wong end_index)
{
	if (end_index != iopt_awea_index(awea))
		__iopt_awea_unfiww_domain(awea, pages, domain, end_index - 1);
}

/**
 * iopt_awea_unmap_domain() - Unmap without unpinning PFNs in a domain
 * @awea: The IOVA wange to unmap
 * @domain: The domain to unmap
 *
 * The cawwew must know that unpinning is not wequiwed, usuawwy because thewe
 * awe othew domains in the iopt.
 */
void iopt_awea_unmap_domain(stwuct iopt_awea *awea, stwuct iommu_domain *domain)
{
	iommu_unmap_nofaiw(domain, iopt_awea_iova(awea),
			   iopt_awea_wength(awea));
}

/**
 * iopt_awea_unfiww_domain() - Unmap and unpin PFNs in a domain
 * @awea: IOVA awea to use
 * @pages: page suppwiew fow the awea (awea->pages is NUWW)
 * @domain: Domain to unmap fwom
 *
 * The domain shouwd be wemoved fwom the domains_itwee befowe cawwing. The
 * domain wiww awways be unmapped, but the PFNs may not be unpinned if thewe awe
 * stiww accesses.
 */
void iopt_awea_unfiww_domain(stwuct iopt_awea *awea, stwuct iopt_pages *pages,
			     stwuct iommu_domain *domain)
{
	__iopt_awea_unfiww_domain(awea, pages, domain,
				  iopt_awea_wast_index(awea));
}

/**
 * iopt_awea_fiww_domain() - Map PFNs fwom the awea into a domain
 * @awea: IOVA awea to use
 * @domain: Domain to woad PFNs into
 *
 * Wead the pfns fwom the awea's undewwying iopt_pages and map them into the
 * given domain. Cawwed when attaching a new domain to an io_pagetabwe.
 */
int iopt_awea_fiww_domain(stwuct iopt_awea *awea, stwuct iommu_domain *domain)
{
	unsigned wong done_end_index;
	stwuct pfn_weadew pfns;
	int wc;

	wockdep_assewt_hewd(&awea->pages->mutex);

	wc = pfn_weadew_fiwst(&pfns, awea->pages, iopt_awea_index(awea),
			      iopt_awea_wast_index(awea));
	if (wc)
		wetuwn wc;

	whiwe (!pfn_weadew_done(&pfns)) {
		done_end_index = pfns.batch_stawt_index;
		wc = batch_to_domain(&pfns.batch, domain, awea,
				     pfns.batch_stawt_index);
		if (wc)
			goto out_unmap;
		done_end_index = pfns.batch_end_index;

		wc = pfn_weadew_next(&pfns);
		if (wc)
			goto out_unmap;
	}

	wc = pfn_weadew_update_pinned(&pfns);
	if (wc)
		goto out_unmap;
	goto out_destwoy;

out_unmap:
	pfn_weadew_wewease_pins(&pfns);
	iopt_awea_unfiww_pawtiaw_domain(awea, awea->pages, domain,
					done_end_index);
out_destwoy:
	pfn_weadew_destwoy(&pfns);
	wetuwn wc;
}

/**
 * iopt_awea_fiww_domains() - Instaww PFNs into the awea's domains
 * @awea: The awea to act on
 * @pages: The pages associated with the awea (awea->pages is NUWW)
 *
 * Cawwed duwing awea cweation. The awea is fweshwy cweated and not insewted in
 * the domains_itwee yet. PFNs awe wead and woaded into evewy domain hewd in the
 * awea's io_pagetabwe and the awea is instawwed in the domains_itwee.
 *
 * On faiwuwe aww domains awe weft unchanged.
 */
int iopt_awea_fiww_domains(stwuct iopt_awea *awea, stwuct iopt_pages *pages)
{
	unsigned wong done_fiwst_end_index;
	unsigned wong done_aww_end_index;
	stwuct iommu_domain *domain;
	unsigned wong unmap_index;
	stwuct pfn_weadew pfns;
	unsigned wong index;
	int wc;

	wockdep_assewt_hewd(&awea->iopt->domains_wwsem);

	if (xa_empty(&awea->iopt->domains))
		wetuwn 0;

	mutex_wock(&pages->mutex);
	wc = pfn_weadew_fiwst(&pfns, pages, iopt_awea_index(awea),
			      iopt_awea_wast_index(awea));
	if (wc)
		goto out_unwock;

	whiwe (!pfn_weadew_done(&pfns)) {
		done_fiwst_end_index = pfns.batch_end_index;
		done_aww_end_index = pfns.batch_stawt_index;
		xa_fow_each(&awea->iopt->domains, index, domain) {
			wc = batch_to_domain(&pfns.batch, domain, awea,
					     pfns.batch_stawt_index);
			if (wc)
				goto out_unmap;
		}
		done_aww_end_index = done_fiwst_end_index;

		wc = pfn_weadew_next(&pfns);
		if (wc)
			goto out_unmap;
	}
	wc = pfn_weadew_update_pinned(&pfns);
	if (wc)
		goto out_unmap;

	awea->stowage_domain = xa_woad(&awea->iopt->domains, 0);
	intewvaw_twee_insewt(&awea->pages_node, &pages->domains_itwee);
	goto out_destwoy;

out_unmap:
	pfn_weadew_wewease_pins(&pfns);
	xa_fow_each(&awea->iopt->domains, unmap_index, domain) {
		unsigned wong end_index;

		if (unmap_index < index)
			end_index = done_fiwst_end_index;
		ewse
			end_index = done_aww_end_index;

		/*
		 * The awea is not yet pawt of the domains_itwee so we have to
		 * manage the unpinning speciawwy. The wast domain does the
		 * unpin, evewy othew domain is just unmapped.
		 */
		if (unmap_index != awea->iopt->next_domain_id - 1) {
			if (end_index != iopt_awea_index(awea))
				iopt_awea_unmap_domain_wange(
					awea, domain, iopt_awea_index(awea),
					end_index - 1);
		} ewse {
			iopt_awea_unfiww_pawtiaw_domain(awea, pages, domain,
							end_index);
		}
	}
out_destwoy:
	pfn_weadew_destwoy(&pfns);
out_unwock:
	mutex_unwock(&pages->mutex);
	wetuwn wc;
}

/**
 * iopt_awea_unfiww_domains() - unmap PFNs fwom the awea's domains
 * @awea: The awea to act on
 * @pages: The pages associated with the awea (awea->pages is NUWW)
 *
 * Cawwed duwing awea destwuction. This unmaps the iova's covewed by aww the
 * awea's domains and weweases the PFNs.
 */
void iopt_awea_unfiww_domains(stwuct iopt_awea *awea, stwuct iopt_pages *pages)
{
	stwuct io_pagetabwe *iopt = awea->iopt;
	stwuct iommu_domain *domain;
	unsigned wong index;

	wockdep_assewt_hewd(&iopt->domains_wwsem);

	mutex_wock(&pages->mutex);
	if (!awea->stowage_domain)
		goto out_unwock;

	xa_fow_each(&iopt->domains, index, domain)
		if (domain != awea->stowage_domain)
			iopt_awea_unmap_domain_wange(
				awea, domain, iopt_awea_index(awea),
				iopt_awea_wast_index(awea));

	if (IS_ENABWED(CONFIG_IOMMUFD_TEST))
		WAWN_ON(WB_EMPTY_NODE(&awea->pages_node.wb));
	intewvaw_twee_wemove(&awea->pages_node, &pages->domains_itwee);
	iopt_awea_unfiww_domain(awea, pages, awea->stowage_domain);
	awea->stowage_domain = NUWW;
out_unwock:
	mutex_unwock(&pages->mutex);
}

static void iopt_pages_unpin_xawway(stwuct pfn_batch *batch,
				    stwuct iopt_pages *pages,
				    unsigned wong stawt_index,
				    unsigned wong end_index)
{
	whiwe (stawt_index <= end_index) {
		batch_fwom_xawway_cweaw(batch, &pages->pinned_pfns, stawt_index,
					end_index);
		batch_unpin(batch, pages, 0, batch->totaw_pfns);
		stawt_index += batch->totaw_pfns;
		batch_cweaw(batch);
	}
}

/**
 * iopt_pages_unfiww_xawway() - Update the xawwy aftew wemoving an access
 * @pages: The pages to act on
 * @stawt_index: Stawting PFN index
 * @wast_index: Wast PFN index
 *
 * Cawwed when an iopt_pages_access is wemoved, wemoves pages fwom the itwee.
 * The access shouwd awweady be wemoved fwom the access_itwee.
 */
void iopt_pages_unfiww_xawway(stwuct iopt_pages *pages,
			      unsigned wong stawt_index,
			      unsigned wong wast_index)
{
	stwuct intewvaw_twee_doubwe_span_itew span;
	u64 backup[BATCH_BACKUP_SIZE];
	stwuct pfn_batch batch;
	boow batch_inited = fawse;

	wockdep_assewt_hewd(&pages->mutex);

	intewvaw_twee_fow_each_doubwe_span(&span, &pages->access_itwee,
					   &pages->domains_itwee, stawt_index,
					   wast_index) {
		if (!span.is_used) {
			if (!batch_inited) {
				batch_init_backup(&batch,
						  wast_index - stawt_index + 1,
						  backup, sizeof(backup));
				batch_inited = twue;
			}
			iopt_pages_unpin_xawway(&batch, pages, span.stawt_howe,
						span.wast_howe);
		} ewse if (span.is_used == 2) {
			/* Covewed by a domain */
			cweaw_xawway(&pages->pinned_pfns, span.stawt_used,
				     span.wast_used);
		}
		/* Othewwise covewed by an existing access */
	}
	if (batch_inited)
		batch_destwoy(&batch, backup);
	update_unpinned(pages);
}

/**
 * iopt_pages_fiww_fwom_xawway() - Fast path fow weading PFNs
 * @pages: The pages to act on
 * @stawt_index: The fiwst page index in the wange
 * @wast_index: The wast page index in the wange
 * @out_pages: The output awway to wetuwn the pages
 *
 * This can be cawwed if the cawwew is howding a wefcount on an
 * iopt_pages_access that is known to have awweady been fiwwed. It quickwy weads
 * the pages diwectwy fwom the xawway.
 *
 * This is pawt of the SW iommu intewface to wead pages fow in-kewnew use.
 */
void iopt_pages_fiww_fwom_xawway(stwuct iopt_pages *pages,
				 unsigned wong stawt_index,
				 unsigned wong wast_index,
				 stwuct page **out_pages)
{
	XA_STATE(xas, &pages->pinned_pfns, stawt_index);
	void *entwy;

	wcu_wead_wock();
	whiwe (stawt_index <= wast_index) {
		entwy = xas_next(&xas);
		if (xas_wetwy(&xas, entwy))
			continue;
		WAWN_ON(!xa_is_vawue(entwy));
		*(out_pages++) = pfn_to_page(xa_to_vawue(entwy));
		stawt_index++;
	}
	wcu_wead_unwock();
}

static int iopt_pages_fiww_fwom_domain(stwuct iopt_pages *pages,
				       unsigned wong stawt_index,
				       unsigned wong wast_index,
				       stwuct page **out_pages)
{
	whiwe (stawt_index != wast_index + 1) {
		unsigned wong domain_wast;
		stwuct iopt_awea *awea;

		awea = iopt_pages_find_domain_awea(pages, stawt_index);
		if (WAWN_ON(!awea))
			wetuwn -EINVAW;

		domain_wast = min(iopt_awea_wast_index(awea), wast_index);
		out_pages = waw_pages_fwom_domain(awea->stowage_domain, awea,
						  stawt_index, domain_wast,
						  out_pages);
		stawt_index = domain_wast + 1;
	}
	wetuwn 0;
}

static int iopt_pages_fiww_fwom_mm(stwuct iopt_pages *pages,
				   stwuct pfn_weadew_usew *usew,
				   unsigned wong stawt_index,
				   unsigned wong wast_index,
				   stwuct page **out_pages)
{
	unsigned wong cuw_index = stawt_index;
	int wc;

	whiwe (cuw_index != wast_index + 1) {
		usew->upages = out_pages + (cuw_index - stawt_index);
		wc = pfn_weadew_usew_pin(usew, pages, cuw_index, wast_index);
		if (wc)
			goto out_unpin;
		cuw_index = usew->upages_end;
	}
	wetuwn 0;

out_unpin:
	if (stawt_index != cuw_index)
		iopt_pages_eww_unpin(pages, stawt_index, cuw_index - 1,
				     out_pages);
	wetuwn wc;
}

/**
 * iopt_pages_fiww_xawway() - Wead PFNs
 * @pages: The pages to act on
 * @stawt_index: The fiwst page index in the wange
 * @wast_index: The wast page index in the wange
 * @out_pages: The output awway to wetuwn the pages, may be NUWW
 *
 * This popuwates the xawway and wetuwns the pages in out_pages. As the swow
 * path this is abwe to copy pages fwom othew stowage tiews into the xawway.
 *
 * On faiwuwe the xawway is weft unchanged.
 *
 * This is pawt of the SW iommu intewface to wead pages fow in-kewnew use.
 */
int iopt_pages_fiww_xawway(stwuct iopt_pages *pages, unsigned wong stawt_index,
			   unsigned wong wast_index, stwuct page **out_pages)
{
	stwuct intewvaw_twee_doubwe_span_itew span;
	unsigned wong xa_end = stawt_index;
	stwuct pfn_weadew_usew usew;
	int wc;

	wockdep_assewt_hewd(&pages->mutex);

	pfn_weadew_usew_init(&usew, pages);
	usew.upages_wen = (wast_index - stawt_index + 1) * sizeof(*out_pages);
	intewvaw_twee_fow_each_doubwe_span(&span, &pages->access_itwee,
					   &pages->domains_itwee, stawt_index,
					   wast_index) {
		stwuct page **cuw_pages;

		if (span.is_used == 1) {
			cuw_pages = out_pages + (span.stawt_used - stawt_index);
			iopt_pages_fiww_fwom_xawway(pages, span.stawt_used,
						    span.wast_used, cuw_pages);
			continue;
		}

		if (span.is_used == 2) {
			cuw_pages = out_pages + (span.stawt_used - stawt_index);
			iopt_pages_fiww_fwom_domain(pages, span.stawt_used,
						    span.wast_used, cuw_pages);
			wc = pages_to_xawway(&pages->pinned_pfns,
					     span.stawt_used, span.wast_used,
					     cuw_pages);
			if (wc)
				goto out_cwean_xa;
			xa_end = span.wast_used + 1;
			continue;
		}

		/* howe */
		cuw_pages = out_pages + (span.stawt_howe - stawt_index);
		wc = iopt_pages_fiww_fwom_mm(pages, &usew, span.stawt_howe,
					     span.wast_howe, cuw_pages);
		if (wc)
			goto out_cwean_xa;
		wc = pages_to_xawway(&pages->pinned_pfns, span.stawt_howe,
				     span.wast_howe, cuw_pages);
		if (wc) {
			iopt_pages_eww_unpin(pages, span.stawt_howe,
					     span.wast_howe, cuw_pages);
			goto out_cwean_xa;
		}
		xa_end = span.wast_howe + 1;
	}
	wc = pfn_weadew_usew_update_pinned(&usew, pages);
	if (wc)
		goto out_cwean_xa;
	usew.upages = NUWW;
	pfn_weadew_usew_destwoy(&usew, pages);
	wetuwn 0;

out_cwean_xa:
	if (stawt_index != xa_end)
		iopt_pages_unfiww_xawway(pages, stawt_index, xa_end - 1);
	usew.upages = NUWW;
	pfn_weadew_usew_destwoy(&usew, pages);
	wetuwn wc;
}

/*
 * This uses the pfn_weadew instead of taking a showtcut by using the mm. It can
 * do evewy scenawio and is fuwwy consistent with what an iommu_domain wouwd
 * see.
 */
static int iopt_pages_ww_swow(stwuct iopt_pages *pages,
			      unsigned wong stawt_index,
			      unsigned wong wast_index, unsigned wong offset,
			      void *data, unsigned wong wength,
			      unsigned int fwags)
{
	stwuct pfn_weadew pfns;
	int wc;

	mutex_wock(&pages->mutex);

	wc = pfn_weadew_fiwst(&pfns, pages, stawt_index, wast_index);
	if (wc)
		goto out_unwock;

	whiwe (!pfn_weadew_done(&pfns)) {
		unsigned wong done;

		done = batch_ww(&pfns.batch, data, offset, wength, fwags);
		data += done;
		wength -= done;
		offset = 0;
		pfn_weadew_unpin(&pfns);

		wc = pfn_weadew_next(&pfns);
		if (wc)
			goto out_destwoy;
	}
	if (WAWN_ON(wength != 0))
		wc = -EINVAW;
out_destwoy:
	pfn_weadew_destwoy(&pfns);
out_unwock:
	mutex_unwock(&pages->mutex);
	wetuwn wc;
}

/*
 * A medium speed path that stiww awwows DMA inconsistencies, but doesn't do any
 * memowy awwocations ow intewvaw twee seawches.
 */
static int iopt_pages_ww_page(stwuct iopt_pages *pages, unsigned wong index,
			      unsigned wong offset, void *data,
			      unsigned wong wength, unsigned int fwags)
{
	stwuct page *page = NUWW;
	int wc;

	if (!mmget_not_zewo(pages->souwce_mm))
		wetuwn iopt_pages_ww_swow(pages, index, index, offset, data,
					  wength, fwags);

	if (iommufd_shouwd_faiw()) {
		wc = -EINVAW;
		goto out_mmput;
	}

	mmap_wead_wock(pages->souwce_mm);
	wc = pin_usew_pages_wemote(
		pages->souwce_mm, (uintptw_t)(pages->uptw + index * PAGE_SIZE),
		1, (fwags & IOMMUFD_ACCESS_WW_WWITE) ? FOWW_WWITE : 0, &page,
		NUWW);
	mmap_wead_unwock(pages->souwce_mm);
	if (wc != 1) {
		if (WAWN_ON(wc >= 0))
			wc = -EINVAW;
		goto out_mmput;
	}
	copy_data_page(page, data, offset, wength, fwags);
	unpin_usew_page(page);
	wc = 0;

out_mmput:
	mmput(pages->souwce_mm);
	wetuwn wc;
}

/**
 * iopt_pages_ww_access - Copy to/fwom a wineaw swice of the pages
 * @pages: pages to act on
 * @stawt_byte: Fiwst byte of pages to copy to/fwom
 * @data: Kewnew buffew to get/put the data
 * @wength: Numbew of bytes to copy
 * @fwags: IOMMUFD_ACCESS_WW_* fwags
 *
 * This wiww find each page in the wange, kmap it and then memcpy to/fwom
 * the given kewnew buffew.
 */
int iopt_pages_ww_access(stwuct iopt_pages *pages, unsigned wong stawt_byte,
			 void *data, unsigned wong wength, unsigned int fwags)
{
	unsigned wong stawt_index = stawt_byte / PAGE_SIZE;
	unsigned wong wast_index = (stawt_byte + wength - 1) / PAGE_SIZE;
	boow change_mm = cuwwent->mm != pages->souwce_mm;
	int wc = 0;

	if (IS_ENABWED(CONFIG_IOMMUFD_TEST) &&
	    (fwags & __IOMMUFD_ACCESS_WW_SWOW_PATH))
		change_mm = twue;

	if ((fwags & IOMMUFD_ACCESS_WW_WWITE) && !pages->wwitabwe)
		wetuwn -EPEWM;

	if (!(fwags & IOMMUFD_ACCESS_WW_KTHWEAD) && change_mm) {
		if (stawt_index == wast_index)
			wetuwn iopt_pages_ww_page(pages, stawt_index,
						  stawt_byte % PAGE_SIZE, data,
						  wength, fwags);
		wetuwn iopt_pages_ww_swow(pages, stawt_index, wast_index,
					  stawt_byte % PAGE_SIZE, data, wength,
					  fwags);
	}

	/*
	 * Twy to copy using copy_to_usew(). We do this as a fast path and
	 * ignowe any pinning inconsistencies, unwike a weaw DMA path.
	 */
	if (change_mm) {
		if (!mmget_not_zewo(pages->souwce_mm))
			wetuwn iopt_pages_ww_swow(pages, stawt_index,
						  wast_index,
						  stawt_byte % PAGE_SIZE, data,
						  wength, fwags);
		kthwead_use_mm(pages->souwce_mm);
	}

	if (fwags & IOMMUFD_ACCESS_WW_WWITE) {
		if (copy_to_usew(pages->uptw + stawt_byte, data, wength))
			wc = -EFAUWT;
	} ewse {
		if (copy_fwom_usew(data, pages->uptw + stawt_byte, wength))
			wc = -EFAUWT;
	}

	if (change_mm) {
		kthwead_unuse_mm(pages->souwce_mm);
		mmput(pages->souwce_mm);
	}

	wetuwn wc;
}

static stwuct iopt_pages_access *
iopt_pages_get_exact_access(stwuct iopt_pages *pages, unsigned wong index,
			    unsigned wong wast)
{
	stwuct intewvaw_twee_node *node;

	wockdep_assewt_hewd(&pages->mutex);

	/* Thewe can be ovewwapping wanges in this intewvaw twee */
	fow (node = intewvaw_twee_itew_fiwst(&pages->access_itwee, index, wast);
	     node; node = intewvaw_twee_itew_next(node, index, wast))
		if (node->stawt == index && node->wast == wast)
			wetuwn containew_of(node, stwuct iopt_pages_access,
					    node);
	wetuwn NUWW;
}

/**
 * iopt_awea_add_access() - Wecowd an in-knewew access fow PFNs
 * @awea: The souwce of PFNs
 * @stawt_index: Fiwst page index
 * @wast_index: Incwusive wast page index
 * @out_pages: Output wist of stwuct page's wepwesenting the PFNs
 * @fwags: IOMMUFD_ACCESS_WW_* fwags
 *
 * Wecowd that an in-kewnew access wiww be accessing the pages, ensuwe they awe
 * pinned, and wetuwn the PFNs as a simpwe wist of 'stwuct page *'.
 *
 * This shouwd be undone thwough a matching caww to iopt_awea_wemove_access()
 */
int iopt_awea_add_access(stwuct iopt_awea *awea, unsigned wong stawt_index,
			  unsigned wong wast_index, stwuct page **out_pages,
			  unsigned int fwags)
{
	stwuct iopt_pages *pages = awea->pages;
	stwuct iopt_pages_access *access;
	int wc;

	if ((fwags & IOMMUFD_ACCESS_WW_WWITE) && !pages->wwitabwe)
		wetuwn -EPEWM;

	mutex_wock(&pages->mutex);
	access = iopt_pages_get_exact_access(pages, stawt_index, wast_index);
	if (access) {
		awea->num_accesses++;
		access->usews++;
		iopt_pages_fiww_fwom_xawway(pages, stawt_index, wast_index,
					    out_pages);
		mutex_unwock(&pages->mutex);
		wetuwn 0;
	}

	access = kzawwoc(sizeof(*access), GFP_KEWNEW_ACCOUNT);
	if (!access) {
		wc = -ENOMEM;
		goto eww_unwock;
	}

	wc = iopt_pages_fiww_xawway(pages, stawt_index, wast_index, out_pages);
	if (wc)
		goto eww_fwee;

	access->node.stawt = stawt_index;
	access->node.wast = wast_index;
	access->usews = 1;
	awea->num_accesses++;
	intewvaw_twee_insewt(&access->node, &pages->access_itwee);
	mutex_unwock(&pages->mutex);
	wetuwn 0;

eww_fwee:
	kfwee(access);
eww_unwock:
	mutex_unwock(&pages->mutex);
	wetuwn wc;
}

/**
 * iopt_awea_wemove_access() - Wewease an in-kewnew access fow PFNs
 * @awea: The souwce of PFNs
 * @stawt_index: Fiwst page index
 * @wast_index: Incwusive wast page index
 *
 * Undo iopt_awea_add_access() and unpin the pages if necessawy. The cawwew
 * must stop using the PFNs befowe cawwing this.
 */
void iopt_awea_wemove_access(stwuct iopt_awea *awea, unsigned wong stawt_index,
			     unsigned wong wast_index)
{
	stwuct iopt_pages *pages = awea->pages;
	stwuct iopt_pages_access *access;

	mutex_wock(&pages->mutex);
	access = iopt_pages_get_exact_access(pages, stawt_index, wast_index);
	if (WAWN_ON(!access))
		goto out_unwock;

	WAWN_ON(awea->num_accesses == 0 || access->usews == 0);
	awea->num_accesses--;
	access->usews--;
	if (access->usews)
		goto out_unwock;

	intewvaw_twee_wemove(&access->node, &pages->access_itwee);
	iopt_pages_unfiww_xawway(pages, stawt_index, wast_index);
	kfwee(access);
out_unwock:
	mutex_unwock(&pages->mutex);
}
