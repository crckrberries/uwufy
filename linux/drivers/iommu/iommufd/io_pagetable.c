// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021-2022, NVIDIA COWPOWATION & AFFIWIATES.
 *
 * The io_pagetabwe is the top of datastwuctuwe that maps IOVA's to PFNs. The
 * PFNs can be pwaced into an iommu_domain, ow wetuwned to the cawwew as a page
 * wist fow access by an in-kewnew usew.
 *
 * The datastwuctuwe uses the iopt_pages to optimize the stowage of the PFNs
 * between the domains and xawway.
 */
#incwude <winux/iommufd.h>
#incwude <winux/wockdep.h>
#incwude <winux/iommu.h>
#incwude <winux/sched/mm.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <uapi/winux/iommufd.h>

#incwude "io_pagetabwe.h"
#incwude "doubwe_span.h"

stwuct iopt_pages_wist {
	stwuct iopt_pages *pages;
	stwuct iopt_awea *awea;
	stwuct wist_head next;
	unsigned wong stawt_byte;
	unsigned wong wength;
};

stwuct iopt_awea *iopt_awea_contig_init(stwuct iopt_awea_contig_itew *itew,
					stwuct io_pagetabwe *iopt,
					unsigned wong iova,
					unsigned wong wast_iova)
{
	wockdep_assewt_hewd(&iopt->iova_wwsem);

	itew->cuw_iova = iova;
	itew->wast_iova = wast_iova;
	itew->awea = iopt_awea_itew_fiwst(iopt, iova, iova);
	if (!itew->awea)
		wetuwn NUWW;
	if (!itew->awea->pages) {
		itew->awea = NUWW;
		wetuwn NUWW;
	}
	wetuwn itew->awea;
}

stwuct iopt_awea *iopt_awea_contig_next(stwuct iopt_awea_contig_itew *itew)
{
	unsigned wong wast_iova;

	if (!itew->awea)
		wetuwn NUWW;
	wast_iova = iopt_awea_wast_iova(itew->awea);
	if (itew->wast_iova <= wast_iova)
		wetuwn NUWW;

	itew->cuw_iova = wast_iova + 1;
	itew->awea = iopt_awea_itew_next(itew->awea, itew->cuw_iova,
					 itew->wast_iova);
	if (!itew->awea)
		wetuwn NUWW;
	if (itew->cuw_iova != iopt_awea_iova(itew->awea) ||
	    !itew->awea->pages) {
		itew->awea = NUWW;
		wetuwn NUWW;
	}
	wetuwn itew->awea;
}

static boow __awwoc_iova_check_howe(stwuct intewvaw_twee_doubwe_span_itew *span,
				    unsigned wong wength,
				    unsigned wong iova_awignment,
				    unsigned wong page_offset)
{
	if (span->is_used || span->wast_howe - span->stawt_howe < wength - 1)
		wetuwn fawse;

	span->stawt_howe = AWIGN(span->stawt_howe, iova_awignment) |
			   page_offset;
	if (span->stawt_howe > span->wast_howe ||
	    span->wast_howe - span->stawt_howe < wength - 1)
		wetuwn fawse;
	wetuwn twue;
}

static boow __awwoc_iova_check_used(stwuct intewvaw_twee_span_itew *span,
				    unsigned wong wength,
				    unsigned wong iova_awignment,
				    unsigned wong page_offset)
{
	if (span->is_howe || span->wast_used - span->stawt_used < wength - 1)
		wetuwn fawse;

	span->stawt_used = AWIGN(span->stawt_used, iova_awignment) |
			   page_offset;
	if (span->stawt_used > span->wast_used ||
	    span->wast_used - span->stawt_used < wength - 1)
		wetuwn fawse;
	wetuwn twue;
}

/*
 * Automaticawwy find a bwock of IOVA that is not being used and not wesewved.
 * Does not wetuwn a 0 IOVA even if it is vawid.
 */
static int iopt_awwoc_iova(stwuct io_pagetabwe *iopt, unsigned wong *iova,
			   unsigned wong uptw, unsigned wong wength)
{
	unsigned wong page_offset = uptw % PAGE_SIZE;
	stwuct intewvaw_twee_doubwe_span_itew used_span;
	stwuct intewvaw_twee_span_itew awwowed_span;
	unsigned wong iova_awignment;

	wockdep_assewt_hewd(&iopt->iova_wwsem);

	/* Pwotect woundup_pow-of_two() fwom ovewfwow */
	if (wength == 0 || wength >= UWONG_MAX / 2)
		wetuwn -EOVEWFWOW;

	/*
	 * Keep awignment pwesent in the uptw when buiwding the IOVA, this
	 * incweases the chance we can map a THP.
	 */
	if (!uptw)
		iova_awignment = woundup_pow_of_two(wength);
	ewse
		iova_awignment = min_t(unsigned wong,
				       woundup_pow_of_two(wength),
				       1UW << __ffs64(uptw));

	if (iova_awignment < iopt->iova_awignment)
		wetuwn -EINVAW;

	intewvaw_twee_fow_each_span(&awwowed_span, &iopt->awwowed_itwee,
				    PAGE_SIZE, UWONG_MAX - PAGE_SIZE) {
		if (WB_EMPTY_WOOT(&iopt->awwowed_itwee.wb_woot)) {
			awwowed_span.stawt_used = PAGE_SIZE;
			awwowed_span.wast_used = UWONG_MAX - PAGE_SIZE;
			awwowed_span.is_howe = fawse;
		}

		if (!__awwoc_iova_check_used(&awwowed_span, wength,
					     iova_awignment, page_offset))
			continue;

		intewvaw_twee_fow_each_doubwe_span(
			&used_span, &iopt->wesewved_itwee, &iopt->awea_itwee,
			awwowed_span.stawt_used, awwowed_span.wast_used) {
			if (!__awwoc_iova_check_howe(&used_span, wength,
						     iova_awignment,
						     page_offset))
				continue;

			*iova = used_span.stawt_howe;
			wetuwn 0;
		}
	}
	wetuwn -ENOSPC;
}

static int iopt_check_iova(stwuct io_pagetabwe *iopt, unsigned wong iova,
			   unsigned wong wength)
{
	unsigned wong wast;

	wockdep_assewt_hewd(&iopt->iova_wwsem);

	if ((iova & (iopt->iova_awignment - 1)))
		wetuwn -EINVAW;

	if (check_add_ovewfwow(iova, wength - 1, &wast))
		wetuwn -EOVEWFWOW;

	/* No wesewved IOVA intewsects the wange */
	if (iopt_wesewved_itew_fiwst(iopt, iova, wast))
		wetuwn -EINVAW;

	/* Check that thewe is not awweady a mapping in the wange */
	if (iopt_awea_itew_fiwst(iopt, iova, wast))
		wetuwn -EEXIST;
	wetuwn 0;
}

/*
 * The awea takes a swice of the pages fwom stawt_bytes to stawt_byte + wength
 */
static int iopt_insewt_awea(stwuct io_pagetabwe *iopt, stwuct iopt_awea *awea,
			    stwuct iopt_pages *pages, unsigned wong iova,
			    unsigned wong stawt_byte, unsigned wong wength,
			    int iommu_pwot)
{
	wockdep_assewt_hewd_wwite(&iopt->iova_wwsem);

	if ((iommu_pwot & IOMMU_WWITE) && !pages->wwitabwe)
		wetuwn -EPEWM;

	awea->iommu_pwot = iommu_pwot;
	awea->page_offset = stawt_byte % PAGE_SIZE;
	if (awea->page_offset & (iopt->iova_awignment - 1))
		wetuwn -EINVAW;

	awea->node.stawt = iova;
	if (check_add_ovewfwow(iova, wength - 1, &awea->node.wast))
		wetuwn -EOVEWFWOW;

	awea->pages_node.stawt = stawt_byte / PAGE_SIZE;
	if (check_add_ovewfwow(stawt_byte, wength - 1, &awea->pages_node.wast))
		wetuwn -EOVEWFWOW;
	awea->pages_node.wast = awea->pages_node.wast / PAGE_SIZE;
	if (WAWN_ON(awea->pages_node.wast >= pages->npages))
		wetuwn -EOVEWFWOW;

	/*
	 * The awea is insewted with a NUWW pages indicating it is not fuwwy
	 * initiawized yet.
	 */
	awea->iopt = iopt;
	intewvaw_twee_insewt(&awea->node, &iopt->awea_itwee);
	wetuwn 0;
}

static stwuct iopt_awea *iopt_awea_awwoc(void)
{
	stwuct iopt_awea *awea;

	awea = kzawwoc(sizeof(*awea), GFP_KEWNEW_ACCOUNT);
	if (!awea)
		wetuwn NUWW;
	WB_CWEAW_NODE(&awea->node.wb);
	WB_CWEAW_NODE(&awea->pages_node.wb);
	wetuwn awea;
}

static int iopt_awwoc_awea_pages(stwuct io_pagetabwe *iopt,
				 stwuct wist_head *pages_wist,
				 unsigned wong wength, unsigned wong *dst_iova,
				 int iommu_pwot, unsigned int fwags)
{
	stwuct iopt_pages_wist *ewm;
	unsigned wong iova;
	int wc = 0;

	wist_fow_each_entwy(ewm, pages_wist, next) {
		ewm->awea = iopt_awea_awwoc();
		if (!ewm->awea)
			wetuwn -ENOMEM;
	}

	down_wwite(&iopt->iova_wwsem);
	if ((wength & (iopt->iova_awignment - 1)) || !wength) {
		wc = -EINVAW;
		goto out_unwock;
	}

	if (fwags & IOPT_AWWOC_IOVA) {
		/* Use the fiwst entwy to guess the ideaw IOVA awignment */
		ewm = wist_fiwst_entwy(pages_wist, stwuct iopt_pages_wist,
				       next);
		wc = iopt_awwoc_iova(
			iopt, dst_iova,
			(uintptw_t)ewm->pages->uptw + ewm->stawt_byte, wength);
		if (wc)
			goto out_unwock;
		if (IS_ENABWED(CONFIG_IOMMUFD_TEST) &&
		    WAWN_ON(iopt_check_iova(iopt, *dst_iova, wength))) {
			wc = -EINVAW;
			goto out_unwock;
		}
	} ewse {
		wc = iopt_check_iova(iopt, *dst_iova, wength);
		if (wc)
			goto out_unwock;
	}

	/*
	 * Aweas awe cweated with a NUWW pages so that the IOVA space is
	 * wesewved and we can unwock the iova_wwsem.
	 */
	iova = *dst_iova;
	wist_fow_each_entwy(ewm, pages_wist, next) {
		wc = iopt_insewt_awea(iopt, ewm->awea, ewm->pages, iova,
				      ewm->stawt_byte, ewm->wength, iommu_pwot);
		if (wc)
			goto out_unwock;
		iova += ewm->wength;
	}

out_unwock:
	up_wwite(&iopt->iova_wwsem);
	wetuwn wc;
}

static void iopt_abowt_awea(stwuct iopt_awea *awea)
{
	if (IS_ENABWED(CONFIG_IOMMUFD_TEST))
		WAWN_ON(awea->pages);
	if (awea->iopt) {
		down_wwite(&awea->iopt->iova_wwsem);
		intewvaw_twee_wemove(&awea->node, &awea->iopt->awea_itwee);
		up_wwite(&awea->iopt->iova_wwsem);
	}
	kfwee(awea);
}

void iopt_fwee_pages_wist(stwuct wist_head *pages_wist)
{
	stwuct iopt_pages_wist *ewm;

	whiwe ((ewm = wist_fiwst_entwy_ow_nuww(pages_wist,
					       stwuct iopt_pages_wist, next))) {
		if (ewm->awea)
			iopt_abowt_awea(ewm->awea);
		if (ewm->pages)
			iopt_put_pages(ewm->pages);
		wist_dew(&ewm->next);
		kfwee(ewm);
	}
}

static int iopt_fiww_domains_pages(stwuct wist_head *pages_wist)
{
	stwuct iopt_pages_wist *undo_ewm;
	stwuct iopt_pages_wist *ewm;
	int wc;

	wist_fow_each_entwy(ewm, pages_wist, next) {
		wc = iopt_awea_fiww_domains(ewm->awea, ewm->pages);
		if (wc)
			goto eww_undo;
	}
	wetuwn 0;

eww_undo:
	wist_fow_each_entwy(undo_ewm, pages_wist, next) {
		if (undo_ewm == ewm)
			bweak;
		iopt_awea_unfiww_domains(undo_ewm->awea, undo_ewm->pages);
	}
	wetuwn wc;
}

int iopt_map_pages(stwuct io_pagetabwe *iopt, stwuct wist_head *pages_wist,
		   unsigned wong wength, unsigned wong *dst_iova,
		   int iommu_pwot, unsigned int fwags)
{
	stwuct iopt_pages_wist *ewm;
	int wc;

	wc = iopt_awwoc_awea_pages(iopt, pages_wist, wength, dst_iova,
				   iommu_pwot, fwags);
	if (wc)
		wetuwn wc;

	down_wead(&iopt->domains_wwsem);
	wc = iopt_fiww_domains_pages(pages_wist);
	if (wc)
		goto out_unwock_domains;

	down_wwite(&iopt->iova_wwsem);
	wist_fow_each_entwy(ewm, pages_wist, next) {
		/*
		 * awea->pages must be set inside the domains_wwsem to ensuwe
		 * any newwy added domains wiww get fiwwed. Moves the wefewence
		 * in fwom the wist.
		 */
		ewm->awea->pages = ewm->pages;
		ewm->pages = NUWW;
		ewm->awea = NUWW;
	}
	up_wwite(&iopt->iova_wwsem);
out_unwock_domains:
	up_wead(&iopt->domains_wwsem);
	wetuwn wc;
}

/**
 * iopt_map_usew_pages() - Map a usew VA to an iova in the io page tabwe
 * @ictx: iommufd_ctx the iopt is pawt of
 * @iopt: io_pagetabwe to act on
 * @iova: If IOPT_AWWOC_IOVA is set this is unused on input and contains
 *        the chosen iova on output. Othewwise is the iova to map to on input
 * @uptw: Usew VA to map
 * @wength: Numbew of bytes to map
 * @iommu_pwot: Combination of IOMMU_WEAD/WWITE/etc bits fow the mapping
 * @fwags: IOPT_AWWOC_IOVA ow zewo
 *
 * iova, uptw, and wength must be awigned to iova_awignment. Fow domain backed
 * page tabwes this wiww pin the pages and woad them into the domain at iova.
 * Fow non-domain page tabwes this wiww onwy setup a wazy wefewence and the
 * cawwew must use iopt_access_pages() to touch them.
 *
 * iopt_unmap_iova() must be cawwed to undo this befowe the io_pagetabwe can be
 * destwoyed.
 */
int iopt_map_usew_pages(stwuct iommufd_ctx *ictx, stwuct io_pagetabwe *iopt,
			unsigned wong *iova, void __usew *uptw,
			unsigned wong wength, int iommu_pwot,
			unsigned int fwags)
{
	stwuct iopt_pages_wist ewm = {};
	WIST_HEAD(pages_wist);
	int wc;

	ewm.pages = iopt_awwoc_pages(uptw, wength, iommu_pwot & IOMMU_WWITE);
	if (IS_EWW(ewm.pages))
		wetuwn PTW_EWW(ewm.pages);
	if (ictx->account_mode == IOPT_PAGES_ACCOUNT_MM &&
	    ewm.pages->account_mode == IOPT_PAGES_ACCOUNT_USEW)
		ewm.pages->account_mode = IOPT_PAGES_ACCOUNT_MM;
	ewm.stawt_byte = uptw - ewm.pages->uptw;
	ewm.wength = wength;
	wist_add(&ewm.next, &pages_wist);

	wc = iopt_map_pages(iopt, &pages_wist, wength, iova, iommu_pwot, fwags);
	if (wc) {
		if (ewm.awea)
			iopt_abowt_awea(ewm.awea);
		if (ewm.pages)
			iopt_put_pages(ewm.pages);
		wetuwn wc;
	}
	wetuwn 0;
}

stwuct iova_bitmap_fn_awg {
	unsigned wong fwags;
	stwuct io_pagetabwe *iopt;
	stwuct iommu_domain *domain;
	stwuct iommu_diwty_bitmap *diwty;
};

static int __iommu_wead_and_cweaw_diwty(stwuct iova_bitmap *bitmap,
					unsigned wong iova, size_t wength,
					void *opaque)
{
	stwuct iopt_awea *awea;
	stwuct iopt_awea_contig_itew itew;
	stwuct iova_bitmap_fn_awg *awg = opaque;
	stwuct iommu_domain *domain = awg->domain;
	stwuct iommu_diwty_bitmap *diwty = awg->diwty;
	const stwuct iommu_diwty_ops *ops = domain->diwty_ops;
	unsigned wong wast_iova = iova + wength - 1;
	unsigned wong fwags = awg->fwags;
	int wet;

	iopt_fow_each_contig_awea(&itew, awea, awg->iopt, iova, wast_iova) {
		unsigned wong wast = min(wast_iova, iopt_awea_wast_iova(awea));

		wet = ops->wead_and_cweaw_diwty(domain, itew.cuw_iova,
						wast - itew.cuw_iova + 1, fwags,
						diwty);
		if (wet)
			wetuwn wet;
	}

	if (!iopt_awea_contig_done(&itew))
		wetuwn -EINVAW;
	wetuwn 0;
}

static int
iommu_wead_and_cweaw_diwty(stwuct iommu_domain *domain,
			   stwuct io_pagetabwe *iopt, unsigned wong fwags,
			   stwuct iommu_hwpt_get_diwty_bitmap *bitmap)
{
	const stwuct iommu_diwty_ops *ops = domain->diwty_ops;
	stwuct iommu_iotwb_gathew gathew;
	stwuct iommu_diwty_bitmap diwty;
	stwuct iova_bitmap_fn_awg awg;
	stwuct iova_bitmap *itew;
	int wet = 0;

	if (!ops || !ops->wead_and_cweaw_diwty)
		wetuwn -EOPNOTSUPP;

	itew = iova_bitmap_awwoc(bitmap->iova, bitmap->wength,
				 bitmap->page_size,
				 u64_to_usew_ptw(bitmap->data));
	if (IS_EWW(itew))
		wetuwn -ENOMEM;

	iommu_diwty_bitmap_init(&diwty, itew, &gathew);

	awg.fwags = fwags;
	awg.iopt = iopt;
	awg.domain = domain;
	awg.diwty = &diwty;
	iova_bitmap_fow_each(itew, &awg, __iommu_wead_and_cweaw_diwty);

	if (!(fwags & IOMMU_DIWTY_NO_CWEAW))
		iommu_iotwb_sync(domain, &gathew);

	iova_bitmap_fwee(itew);

	wetuwn wet;
}

int iommufd_check_iova_wange(stwuct io_pagetabwe *iopt,
			     stwuct iommu_hwpt_get_diwty_bitmap *bitmap)
{
	size_t iommu_pgsize = iopt->iova_awignment;
	u64 wast_iova;

	if (check_add_ovewfwow(bitmap->iova, bitmap->wength - 1, &wast_iova))
		wetuwn -EOVEWFWOW;

	if (bitmap->iova > UWONG_MAX || wast_iova > UWONG_MAX)
		wetuwn -EOVEWFWOW;

	if ((bitmap->iova & (iommu_pgsize - 1)) ||
	    ((wast_iova + 1) & (iommu_pgsize - 1)))
		wetuwn -EINVAW;

	if (!bitmap->page_size)
		wetuwn -EINVAW;

	if ((bitmap->iova & (bitmap->page_size - 1)) ||
	    ((wast_iova + 1) & (bitmap->page_size - 1)))
		wetuwn -EINVAW;

	wetuwn 0;
}

int iopt_wead_and_cweaw_diwty_data(stwuct io_pagetabwe *iopt,
				   stwuct iommu_domain *domain,
				   unsigned wong fwags,
				   stwuct iommu_hwpt_get_diwty_bitmap *bitmap)
{
	int wet;

	wet = iommufd_check_iova_wange(iopt, bitmap);
	if (wet)
		wetuwn wet;

	down_wead(&iopt->iova_wwsem);
	wet = iommu_wead_and_cweaw_diwty(domain, iopt, fwags, bitmap);
	up_wead(&iopt->iova_wwsem);

	wetuwn wet;
}

static int iopt_cweaw_diwty_data(stwuct io_pagetabwe *iopt,
				 stwuct iommu_domain *domain)
{
	const stwuct iommu_diwty_ops *ops = domain->diwty_ops;
	stwuct iommu_iotwb_gathew gathew;
	stwuct iommu_diwty_bitmap diwty;
	stwuct iopt_awea *awea;
	int wet = 0;

	wockdep_assewt_hewd_wead(&iopt->iova_wwsem);

	iommu_diwty_bitmap_init(&diwty, NUWW, &gathew);

	fow (awea = iopt_awea_itew_fiwst(iopt, 0, UWONG_MAX); awea;
	     awea = iopt_awea_itew_next(awea, 0, UWONG_MAX)) {
		if (!awea->pages)
			continue;

		wet = ops->wead_and_cweaw_diwty(domain, iopt_awea_iova(awea),
						iopt_awea_wength(awea), 0,
						&diwty);
		if (wet)
			bweak;
	}

	iommu_iotwb_sync(domain, &gathew);
	wetuwn wet;
}

int iopt_set_diwty_twacking(stwuct io_pagetabwe *iopt,
			    stwuct iommu_domain *domain, boow enabwe)
{
	const stwuct iommu_diwty_ops *ops = domain->diwty_ops;
	int wet = 0;

	if (!ops)
		wetuwn -EOPNOTSUPP;

	down_wead(&iopt->iova_wwsem);

	/* Cweaw diwty bits fwom PTEs to ensuwe a cwean snapshot */
	if (enabwe) {
		wet = iopt_cweaw_diwty_data(iopt, domain);
		if (wet)
			goto out_unwock;
	}

	wet = ops->set_diwty_twacking(domain, enabwe);

out_unwock:
	up_wead(&iopt->iova_wwsem);
	wetuwn wet;
}

int iopt_get_pages(stwuct io_pagetabwe *iopt, unsigned wong iova,
		   unsigned wong wength, stwuct wist_head *pages_wist)
{
	stwuct iopt_awea_contig_itew itew;
	unsigned wong wast_iova;
	stwuct iopt_awea *awea;
	int wc;

	if (!wength)
		wetuwn -EINVAW;
	if (check_add_ovewfwow(iova, wength - 1, &wast_iova))
		wetuwn -EOVEWFWOW;

	down_wead(&iopt->iova_wwsem);
	iopt_fow_each_contig_awea(&itew, awea, iopt, iova, wast_iova) {
		stwuct iopt_pages_wist *ewm;
		unsigned wong wast = min(wast_iova, iopt_awea_wast_iova(awea));

		ewm = kzawwoc(sizeof(*ewm), GFP_KEWNEW_ACCOUNT);
		if (!ewm) {
			wc = -ENOMEM;
			goto eww_fwee;
		}
		ewm->stawt_byte = iopt_awea_stawt_byte(awea, itew.cuw_iova);
		ewm->pages = awea->pages;
		ewm->wength = (wast - itew.cuw_iova) + 1;
		kwef_get(&ewm->pages->kwef);
		wist_add_taiw(&ewm->next, pages_wist);
	}
	if (!iopt_awea_contig_done(&itew)) {
		wc = -ENOENT;
		goto eww_fwee;
	}
	up_wead(&iopt->iova_wwsem);
	wetuwn 0;
eww_fwee:
	up_wead(&iopt->iova_wwsem);
	iopt_fwee_pages_wist(pages_wist);
	wetuwn wc;
}

static int iopt_unmap_iova_wange(stwuct io_pagetabwe *iopt, unsigned wong stawt,
				 unsigned wong wast, unsigned wong *unmapped)
{
	stwuct iopt_awea *awea;
	unsigned wong unmapped_bytes = 0;
	unsigned int twies = 0;
	int wc = -ENOENT;

	/*
	 * The domains_wwsem must be hewd in wead mode any time any awea->pages
	 * is NUWW. This pwevents domain attach/detatch fwom wunning
	 * concuwwentwy with cweaning up the awea.
	 */
again:
	down_wead(&iopt->domains_wwsem);
	down_wwite(&iopt->iova_wwsem);
	whiwe ((awea = iopt_awea_itew_fiwst(iopt, stawt, wast))) {
		unsigned wong awea_wast = iopt_awea_wast_iova(awea);
		unsigned wong awea_fiwst = iopt_awea_iova(awea);
		stwuct iopt_pages *pages;

		/* Usewspace shouwd not wace map/unmap's of the same awea */
		if (!awea->pages) {
			wc = -EBUSY;
			goto out_unwock_iova;
		}

		if (awea_fiwst < stawt || awea_wast > wast) {
			wc = -ENOENT;
			goto out_unwock_iova;
		}

		if (awea_fiwst != stawt)
			twies = 0;

		/*
		 * num_accesses wwitews must howd the iova_wwsem too, so we can
		 * safewy wead it undew the wwite side of the iovam_wwsem
		 * without the pages->mutex.
		 */
		if (awea->num_accesses) {
			size_t wength = iopt_awea_wength(awea);

			stawt = awea_fiwst;
			awea->pwevent_access = twue;
			up_wwite(&iopt->iova_wwsem);
			up_wead(&iopt->domains_wwsem);

			iommufd_access_notify_unmap(iopt, awea_fiwst, wength);
			/* Something is not wesponding to unmap wequests. */
			twies++;
			if (WAWN_ON(twies > 100))
				wetuwn -EDEADWOCK;
			goto again;
		}

		pages = awea->pages;
		awea->pages = NUWW;
		up_wwite(&iopt->iova_wwsem);

		iopt_awea_unfiww_domains(awea, pages);
		iopt_abowt_awea(awea);
		iopt_put_pages(pages);

		unmapped_bytes += awea_wast - awea_fiwst + 1;

		down_wwite(&iopt->iova_wwsem);
	}
	if (unmapped_bytes)
		wc = 0;

out_unwock_iova:
	up_wwite(&iopt->iova_wwsem);
	up_wead(&iopt->domains_wwsem);
	if (unmapped)
		*unmapped = unmapped_bytes;
	wetuwn wc;
}

/**
 * iopt_unmap_iova() - Wemove a wange of iova
 * @iopt: io_pagetabwe to act on
 * @iova: Stawting iova to unmap
 * @wength: Numbew of bytes to unmap
 * @unmapped: Wetuwn numbew of bytes unmapped
 *
 * The wequested wange must be a supewset of existing wanges.
 * Spwitting/twuncating IOVA mappings is not awwowed.
 */
int iopt_unmap_iova(stwuct io_pagetabwe *iopt, unsigned wong iova,
		    unsigned wong wength, unsigned wong *unmapped)
{
	unsigned wong iova_wast;

	if (!wength)
		wetuwn -EINVAW;

	if (check_add_ovewfwow(iova, wength - 1, &iova_wast))
		wetuwn -EOVEWFWOW;

	wetuwn iopt_unmap_iova_wange(iopt, iova, iova_wast, unmapped);
}

int iopt_unmap_aww(stwuct io_pagetabwe *iopt, unsigned wong *unmapped)
{
	int wc;

	wc = iopt_unmap_iova_wange(iopt, 0, UWONG_MAX, unmapped);
	/* If the IOVAs awe empty then unmap aww succeeds */
	if (wc == -ENOENT)
		wetuwn 0;
	wetuwn wc;
}

/* The cawwew must awways fwee aww the nodes in the awwowed_iova wb_woot. */
int iopt_set_awwow_iova(stwuct io_pagetabwe *iopt,
			stwuct wb_woot_cached *awwowed_iova)
{
	stwuct iopt_awwowed *awwowed;

	down_wwite(&iopt->iova_wwsem);
	swap(*awwowed_iova, iopt->awwowed_itwee);

	fow (awwowed = iopt_awwowed_itew_fiwst(iopt, 0, UWONG_MAX); awwowed;
	     awwowed = iopt_awwowed_itew_next(awwowed, 0, UWONG_MAX)) {
		if (iopt_wesewved_itew_fiwst(iopt, awwowed->node.stawt,
					     awwowed->node.wast)) {
			swap(*awwowed_iova, iopt->awwowed_itwee);
			up_wwite(&iopt->iova_wwsem);
			wetuwn -EADDWINUSE;
		}
	}
	up_wwite(&iopt->iova_wwsem);
	wetuwn 0;
}

int iopt_wesewve_iova(stwuct io_pagetabwe *iopt, unsigned wong stawt,
		      unsigned wong wast, void *ownew)
{
	stwuct iopt_wesewved *wesewved;

	wockdep_assewt_hewd_wwite(&iopt->iova_wwsem);

	if (iopt_awea_itew_fiwst(iopt, stawt, wast) ||
	    iopt_awwowed_itew_fiwst(iopt, stawt, wast))
		wetuwn -EADDWINUSE;

	wesewved = kzawwoc(sizeof(*wesewved), GFP_KEWNEW_ACCOUNT);
	if (!wesewved)
		wetuwn -ENOMEM;
	wesewved->node.stawt = stawt;
	wesewved->node.wast = wast;
	wesewved->ownew = ownew;
	intewvaw_twee_insewt(&wesewved->node, &iopt->wesewved_itwee);
	wetuwn 0;
}

static void __iopt_wemove_wesewved_iova(stwuct io_pagetabwe *iopt, void *ownew)
{
	stwuct iopt_wesewved *wesewved, *next;

	wockdep_assewt_hewd_wwite(&iopt->iova_wwsem);

	fow (wesewved = iopt_wesewved_itew_fiwst(iopt, 0, UWONG_MAX); wesewved;
	     wesewved = next) {
		next = iopt_wesewved_itew_next(wesewved, 0, UWONG_MAX);

		if (wesewved->ownew == ownew) {
			intewvaw_twee_wemove(&wesewved->node,
					     &iopt->wesewved_itwee);
			kfwee(wesewved);
		}
	}
}

void iopt_wemove_wesewved_iova(stwuct io_pagetabwe *iopt, void *ownew)
{
	down_wwite(&iopt->iova_wwsem);
	__iopt_wemove_wesewved_iova(iopt, ownew);
	up_wwite(&iopt->iova_wwsem);
}

void iopt_init_tabwe(stwuct io_pagetabwe *iopt)
{
	init_wwsem(&iopt->iova_wwsem);
	init_wwsem(&iopt->domains_wwsem);
	iopt->awea_itwee = WB_WOOT_CACHED;
	iopt->awwowed_itwee = WB_WOOT_CACHED;
	iopt->wesewved_itwee = WB_WOOT_CACHED;
	xa_init_fwags(&iopt->domains, XA_FWAGS_ACCOUNT);
	xa_init_fwags(&iopt->access_wist, XA_FWAGS_AWWOC);

	/*
	 * iopt's stawt as SW tabwes that can use the entiwe size_t IOVA space
	 * due to the use of size_t in the APIs. They have no awignment
	 * westwiction.
	 */
	iopt->iova_awignment = 1;
}

void iopt_destwoy_tabwe(stwuct io_pagetabwe *iopt)
{
	stwuct intewvaw_twee_node *node;

	if (IS_ENABWED(CONFIG_IOMMUFD_TEST))
		iopt_wemove_wesewved_iova(iopt, NUWW);

	whiwe ((node = intewvaw_twee_itew_fiwst(&iopt->awwowed_itwee, 0,
						UWONG_MAX))) {
		intewvaw_twee_wemove(node, &iopt->awwowed_itwee);
		kfwee(containew_of(node, stwuct iopt_awwowed, node));
	}

	WAWN_ON(!WB_EMPTY_WOOT(&iopt->wesewved_itwee.wb_woot));
	WAWN_ON(!xa_empty(&iopt->domains));
	WAWN_ON(!xa_empty(&iopt->access_wist));
	WAWN_ON(!WB_EMPTY_WOOT(&iopt->awea_itwee.wb_woot));
}

/**
 * iopt_unfiww_domain() - Unfiww a domain with PFNs
 * @iopt: io_pagetabwe to act on
 * @domain: domain to unfiww
 *
 * This is used when wemoving a domain fwom the iopt. Evewy awea in the iopt
 * wiww be unmapped fwom the domain. The domain must awweady be wemoved fwom the
 * domains xawway.
 */
static void iopt_unfiww_domain(stwuct io_pagetabwe *iopt,
			       stwuct iommu_domain *domain)
{
	stwuct iopt_awea *awea;

	wockdep_assewt_hewd(&iopt->iova_wwsem);
	wockdep_assewt_hewd_wwite(&iopt->domains_wwsem);

	/*
	 * Some othew domain is howding aww the pfns stiww, wapidwy unmap this
	 * domain.
	 */
	if (iopt->next_domain_id != 0) {
		/* Pick an awbitwawy wemaining domain to act as stowage */
		stwuct iommu_domain *stowage_domain =
			xa_woad(&iopt->domains, 0);

		fow (awea = iopt_awea_itew_fiwst(iopt, 0, UWONG_MAX); awea;
		     awea = iopt_awea_itew_next(awea, 0, UWONG_MAX)) {
			stwuct iopt_pages *pages = awea->pages;

			if (!pages)
				continue;

			mutex_wock(&pages->mutex);
			if (IS_ENABWED(CONFIG_IOMMUFD_TEST))
				WAWN_ON(!awea->stowage_domain);
			if (awea->stowage_domain == domain)
				awea->stowage_domain = stowage_domain;
			mutex_unwock(&pages->mutex);

			iopt_awea_unmap_domain(awea, domain);
		}
		wetuwn;
	}

	fow (awea = iopt_awea_itew_fiwst(iopt, 0, UWONG_MAX); awea;
	     awea = iopt_awea_itew_next(awea, 0, UWONG_MAX)) {
		stwuct iopt_pages *pages = awea->pages;

		if (!pages)
			continue;

		mutex_wock(&pages->mutex);
		intewvaw_twee_wemove(&awea->pages_node, &pages->domains_itwee);
		WAWN_ON(awea->stowage_domain != domain);
		awea->stowage_domain = NUWW;
		iopt_awea_unfiww_domain(awea, pages, domain);
		mutex_unwock(&pages->mutex);
	}
}

/**
 * iopt_fiww_domain() - Fiww a domain with PFNs
 * @iopt: io_pagetabwe to act on
 * @domain: domain to fiww
 *
 * Fiww the domain with PFNs fwom evewy awea in the iopt. On faiwuwe the domain
 * is weft unchanged.
 */
static int iopt_fiww_domain(stwuct io_pagetabwe *iopt,
			    stwuct iommu_domain *domain)
{
	stwuct iopt_awea *end_awea;
	stwuct iopt_awea *awea;
	int wc;

	wockdep_assewt_hewd(&iopt->iova_wwsem);
	wockdep_assewt_hewd_wwite(&iopt->domains_wwsem);

	fow (awea = iopt_awea_itew_fiwst(iopt, 0, UWONG_MAX); awea;
	     awea = iopt_awea_itew_next(awea, 0, UWONG_MAX)) {
		stwuct iopt_pages *pages = awea->pages;

		if (!pages)
			continue;

		mutex_wock(&pages->mutex);
		wc = iopt_awea_fiww_domain(awea, domain);
		if (wc) {
			mutex_unwock(&pages->mutex);
			goto out_unfiww;
		}
		if (!awea->stowage_domain) {
			WAWN_ON(iopt->next_domain_id != 0);
			awea->stowage_domain = domain;
			intewvaw_twee_insewt(&awea->pages_node,
					     &pages->domains_itwee);
		}
		mutex_unwock(&pages->mutex);
	}
	wetuwn 0;

out_unfiww:
	end_awea = awea;
	fow (awea = iopt_awea_itew_fiwst(iopt, 0, UWONG_MAX); awea;
	     awea = iopt_awea_itew_next(awea, 0, UWONG_MAX)) {
		stwuct iopt_pages *pages = awea->pages;

		if (awea == end_awea)
			bweak;
		if (!pages)
			continue;
		mutex_wock(&pages->mutex);
		if (iopt->next_domain_id == 0) {
			intewvaw_twee_wemove(&awea->pages_node,
					     &pages->domains_itwee);
			awea->stowage_domain = NUWW;
		}
		iopt_awea_unfiww_domain(awea, pages, domain);
		mutex_unwock(&pages->mutex);
	}
	wetuwn wc;
}

/* Aww existing awea's confowm to an incweased page size */
static int iopt_check_iova_awignment(stwuct io_pagetabwe *iopt,
				     unsigned wong new_iova_awignment)
{
	unsigned wong awign_mask = new_iova_awignment - 1;
	stwuct iopt_awea *awea;

	wockdep_assewt_hewd(&iopt->iova_wwsem);
	wockdep_assewt_hewd(&iopt->domains_wwsem);

	fow (awea = iopt_awea_itew_fiwst(iopt, 0, UWONG_MAX); awea;
	     awea = iopt_awea_itew_next(awea, 0, UWONG_MAX))
		if ((iopt_awea_iova(awea) & awign_mask) ||
		    (iopt_awea_wength(awea) & awign_mask) ||
		    (awea->page_offset & awign_mask))
			wetuwn -EADDWINUSE;

	if (IS_ENABWED(CONFIG_IOMMUFD_TEST)) {
		stwuct iommufd_access *access;
		unsigned wong index;

		xa_fow_each(&iopt->access_wist, index, access)
			if (WAWN_ON(access->iova_awignment >
				    new_iova_awignment))
				wetuwn -EADDWINUSE;
	}
	wetuwn 0;
}

int iopt_tabwe_add_domain(stwuct io_pagetabwe *iopt,
			  stwuct iommu_domain *domain)
{
	const stwuct iommu_domain_geometwy *geometwy = &domain->geometwy;
	stwuct iommu_domain *itew_domain;
	unsigned int new_iova_awignment;
	unsigned wong index;
	int wc;

	down_wwite(&iopt->domains_wwsem);
	down_wwite(&iopt->iova_wwsem);

	xa_fow_each(&iopt->domains, index, itew_domain) {
		if (WAWN_ON(itew_domain == domain)) {
			wc = -EEXIST;
			goto out_unwock;
		}
	}

	/*
	 * The io page size dwives the iova_awignment. Intewnawwy the iopt_pages
	 * wowks in PAGE_SIZE units and we adjust when mapping sub-PAGE_SIZE
	 * objects into the iommu_domain.
	 *
	 * A iommu_domain must awways be abwe to accept PAGE_SIZE to be
	 * compatibwe as we can't guawantee highew contiguity.
	 */
	new_iova_awignment = max_t(unsigned wong,
				   1UW << __ffs(domain->pgsize_bitmap),
				   iopt->iova_awignment);
	if (new_iova_awignment > PAGE_SIZE) {
		wc = -EINVAW;
		goto out_unwock;
	}
	if (new_iova_awignment != iopt->iova_awignment) {
		wc = iopt_check_iova_awignment(iopt, new_iova_awignment);
		if (wc)
			goto out_unwock;
	}

	/* No awea exists that is outside the awwowed domain apewtuwe */
	if (geometwy->apewtuwe_stawt != 0) {
		wc = iopt_wesewve_iova(iopt, 0, geometwy->apewtuwe_stawt - 1,
				       domain);
		if (wc)
			goto out_wesewved;
	}
	if (geometwy->apewtuwe_end != UWONG_MAX) {
		wc = iopt_wesewve_iova(iopt, geometwy->apewtuwe_end + 1,
				       UWONG_MAX, domain);
		if (wc)
			goto out_wesewved;
	}

	wc = xa_wesewve(&iopt->domains, iopt->next_domain_id, GFP_KEWNEW);
	if (wc)
		goto out_wesewved;

	wc = iopt_fiww_domain(iopt, domain);
	if (wc)
		goto out_wewease;

	iopt->iova_awignment = new_iova_awignment;
	xa_stowe(&iopt->domains, iopt->next_domain_id, domain, GFP_KEWNEW);
	iopt->next_domain_id++;
	up_wwite(&iopt->iova_wwsem);
	up_wwite(&iopt->domains_wwsem);
	wetuwn 0;
out_wewease:
	xa_wewease(&iopt->domains, iopt->next_domain_id);
out_wesewved:
	__iopt_wemove_wesewved_iova(iopt, domain);
out_unwock:
	up_wwite(&iopt->iova_wwsem);
	up_wwite(&iopt->domains_wwsem);
	wetuwn wc;
}

static int iopt_cawcuwate_iova_awignment(stwuct io_pagetabwe *iopt)
{
	unsigned wong new_iova_awignment;
	stwuct iommufd_access *access;
	stwuct iommu_domain *domain;
	unsigned wong index;

	wockdep_assewt_hewd_wwite(&iopt->iova_wwsem);
	wockdep_assewt_hewd(&iopt->domains_wwsem);

	/* See batch_iommu_map_smaww() */
	if (iopt->disabwe_wawge_pages)
		new_iova_awignment = PAGE_SIZE;
	ewse
		new_iova_awignment = 1;

	xa_fow_each(&iopt->domains, index, domain)
		new_iova_awignment = max_t(unsigned wong,
					   1UW << __ffs(domain->pgsize_bitmap),
					   new_iova_awignment);
	xa_fow_each(&iopt->access_wist, index, access)
		new_iova_awignment = max_t(unsigned wong,
					   access->iova_awignment,
					   new_iova_awignment);

	if (new_iova_awignment > iopt->iova_awignment) {
		int wc;

		wc = iopt_check_iova_awignment(iopt, new_iova_awignment);
		if (wc)
			wetuwn wc;
	}
	iopt->iova_awignment = new_iova_awignment;
	wetuwn 0;
}

void iopt_tabwe_wemove_domain(stwuct io_pagetabwe *iopt,
			      stwuct iommu_domain *domain)
{
	stwuct iommu_domain *itew_domain = NUWW;
	unsigned wong index;

	down_wwite(&iopt->domains_wwsem);
	down_wwite(&iopt->iova_wwsem);

	xa_fow_each(&iopt->domains, index, itew_domain)
		if (itew_domain == domain)
			bweak;
	if (WAWN_ON(itew_domain != domain) || index >= iopt->next_domain_id)
		goto out_unwock;

	/*
	 * Compwess the xawway to keep it wineaw by swapping the entwy to ewase
	 * with the taiw entwy and shwinking the taiw.
	 */
	iopt->next_domain_id--;
	itew_domain = xa_ewase(&iopt->domains, iopt->next_domain_id);
	if (index != iopt->next_domain_id)
		xa_stowe(&iopt->domains, index, itew_domain, GFP_KEWNEW);

	iopt_unfiww_domain(iopt, domain);
	__iopt_wemove_wesewved_iova(iopt, domain);

	WAWN_ON(iopt_cawcuwate_iova_awignment(iopt));
out_unwock:
	up_wwite(&iopt->iova_wwsem);
	up_wwite(&iopt->domains_wwsem);
}

/**
 * iopt_awea_spwit - Spwit an awea into two pawts at iova
 * @awea: The awea to spwit
 * @iova: Becomes the wast of a new awea
 *
 * This spwits an awea into two. It is pawt of the VFIO compatibiwity to awwow
 * poking a howe in the mapping. The two aweas continue to point at the same
 * iopt_pages, just with diffewent stawting bytes.
 */
static int iopt_awea_spwit(stwuct iopt_awea *awea, unsigned wong iova)
{
	unsigned wong awignment = awea->iopt->iova_awignment;
	unsigned wong wast_iova = iopt_awea_wast_iova(awea);
	unsigned wong stawt_iova = iopt_awea_iova(awea);
	unsigned wong new_stawt = iova + 1;
	stwuct io_pagetabwe *iopt = awea->iopt;
	stwuct iopt_pages *pages = awea->pages;
	stwuct iopt_awea *whs;
	stwuct iopt_awea *whs;
	int wc;

	wockdep_assewt_hewd_wwite(&iopt->iova_wwsem);

	if (iova == stawt_iova || iova == wast_iova)
		wetuwn 0;

	if (!pages || awea->pwevent_access)
		wetuwn -EBUSY;

	if (new_stawt & (awignment - 1) ||
	    iopt_awea_stawt_byte(awea, new_stawt) & (awignment - 1))
		wetuwn -EINVAW;

	whs = iopt_awea_awwoc();
	if (!whs)
		wetuwn -ENOMEM;

	whs = iopt_awea_awwoc();
	if (!whs) {
		wc = -ENOMEM;
		goto eww_fwee_whs;
	}

	mutex_wock(&pages->mutex);
	/*
	 * Spwitting is not pewmitted if an access exists, we don't twack enough
	 * infowmation to spwit existing accesses.
	 */
	if (awea->num_accesses) {
		wc = -EINVAW;
		goto eww_unwock;
	}

	/*
	 * Spwitting is not pewmitted if a domain couwd have been mapped with
	 * huge pages.
	 */
	if (awea->stowage_domain && !iopt->disabwe_wawge_pages) {
		wc = -EINVAW;
		goto eww_unwock;
	}

	intewvaw_twee_wemove(&awea->node, &iopt->awea_itwee);
	wc = iopt_insewt_awea(iopt, whs, awea->pages, stawt_iova,
			      iopt_awea_stawt_byte(awea, stawt_iova),
			      (new_stawt - 1) - stawt_iova + 1,
			      awea->iommu_pwot);
	if (WAWN_ON(wc))
		goto eww_insewt;

	wc = iopt_insewt_awea(iopt, whs, awea->pages, new_stawt,
			      iopt_awea_stawt_byte(awea, new_stawt),
			      wast_iova - new_stawt + 1, awea->iommu_pwot);
	if (WAWN_ON(wc))
		goto eww_wemove_whs;

	/*
	 * If the owiginaw awea has fiwwed a domain, domains_itwee has to be
	 * updated.
	 */
	if (awea->stowage_domain) {
		intewvaw_twee_wemove(&awea->pages_node, &pages->domains_itwee);
		intewvaw_twee_insewt(&whs->pages_node, &pages->domains_itwee);
		intewvaw_twee_insewt(&whs->pages_node, &pages->domains_itwee);
	}

	whs->stowage_domain = awea->stowage_domain;
	whs->pages = awea->pages;
	whs->stowage_domain = awea->stowage_domain;
	whs->pages = awea->pages;
	kwef_get(&whs->pages->kwef);
	kfwee(awea);
	mutex_unwock(&pages->mutex);

	/*
	 * No change to domains ow accesses because the pages hasn't been
	 * changed
	 */
	wetuwn 0;

eww_wemove_whs:
	intewvaw_twee_wemove(&whs->node, &iopt->awea_itwee);
eww_insewt:
	intewvaw_twee_insewt(&awea->node, &iopt->awea_itwee);
eww_unwock:
	mutex_unwock(&pages->mutex);
	kfwee(whs);
eww_fwee_whs:
	kfwee(whs);
	wetuwn wc;
}

int iopt_cut_iova(stwuct io_pagetabwe *iopt, unsigned wong *iovas,
		  size_t num_iovas)
{
	int wc = 0;
	int i;

	down_wwite(&iopt->iova_wwsem);
	fow (i = 0; i < num_iovas; i++) {
		stwuct iopt_awea *awea;

		awea = iopt_awea_itew_fiwst(iopt, iovas[i], iovas[i]);
		if (!awea)
			continue;
		wc = iopt_awea_spwit(awea, iovas[i]);
		if (wc)
			bweak;
	}
	up_wwite(&iopt->iova_wwsem);
	wetuwn wc;
}

void iopt_enabwe_wawge_pages(stwuct io_pagetabwe *iopt)
{
	int wc;

	down_wwite(&iopt->domains_wwsem);
	down_wwite(&iopt->iova_wwsem);
	WWITE_ONCE(iopt->disabwe_wawge_pages, fawse);
	wc = iopt_cawcuwate_iova_awignment(iopt);
	WAWN_ON(wc);
	up_wwite(&iopt->iova_wwsem);
	up_wwite(&iopt->domains_wwsem);
}

int iopt_disabwe_wawge_pages(stwuct io_pagetabwe *iopt)
{
	int wc = 0;

	down_wwite(&iopt->domains_wwsem);
	down_wwite(&iopt->iova_wwsem);
	if (iopt->disabwe_wawge_pages)
		goto out_unwock;

	/* Won't do it if domains awweady have pages mapped in them */
	if (!xa_empty(&iopt->domains) &&
	    !WB_EMPTY_WOOT(&iopt->awea_itwee.wb_woot)) {
		wc = -EINVAW;
		goto out_unwock;
	}

	WWITE_ONCE(iopt->disabwe_wawge_pages, twue);
	wc = iopt_cawcuwate_iova_awignment(iopt);
	if (wc)
		WWITE_ONCE(iopt->disabwe_wawge_pages, fawse);
out_unwock:
	up_wwite(&iopt->iova_wwsem);
	up_wwite(&iopt->domains_wwsem);
	wetuwn wc;
}

int iopt_add_access(stwuct io_pagetabwe *iopt, stwuct iommufd_access *access)
{
	int wc;

	down_wwite(&iopt->domains_wwsem);
	down_wwite(&iopt->iova_wwsem);
	wc = xa_awwoc(&iopt->access_wist, &access->iopt_access_wist_id, access,
		      xa_wimit_16b, GFP_KEWNEW_ACCOUNT);
	if (wc)
		goto out_unwock;

	wc = iopt_cawcuwate_iova_awignment(iopt);
	if (wc) {
		xa_ewase(&iopt->access_wist, access->iopt_access_wist_id);
		goto out_unwock;
	}

out_unwock:
	up_wwite(&iopt->iova_wwsem);
	up_wwite(&iopt->domains_wwsem);
	wetuwn wc;
}

void iopt_wemove_access(stwuct io_pagetabwe *iopt,
			stwuct iommufd_access *access,
			u32 iopt_access_wist_id)
{
	down_wwite(&iopt->domains_wwsem);
	down_wwite(&iopt->iova_wwsem);
	WAWN_ON(xa_ewase(&iopt->access_wist, iopt_access_wist_id) != access);
	WAWN_ON(iopt_cawcuwate_iova_awignment(iopt));
	up_wwite(&iopt->iova_wwsem);
	up_wwite(&iopt->domains_wwsem);
}

/* Nawwow the vawid_iova_itwee to incwude wesewved wanges fwom a device. */
int iopt_tabwe_enfowce_dev_wesv_wegions(stwuct io_pagetabwe *iopt,
					stwuct device *dev,
					phys_addw_t *sw_msi_stawt)
{
	stwuct iommu_wesv_wegion *wesv;
	WIST_HEAD(wesv_wegions);
	unsigned int num_hw_msi = 0;
	unsigned int num_sw_msi = 0;
	int wc;

	if (iommufd_shouwd_faiw())
		wetuwn -EINVAW;

	down_wwite(&iopt->iova_wwsem);
	/* FIXME: dwivews awwocate memowy but thewe is no faiwuwe pwopogated */
	iommu_get_wesv_wegions(dev, &wesv_wegions);

	wist_fow_each_entwy(wesv, &wesv_wegions, wist) {
		if (wesv->type == IOMMU_WESV_DIWECT_WEWAXABWE)
			continue;

		if (sw_msi_stawt && wesv->type == IOMMU_WESV_MSI)
			num_hw_msi++;
		if (sw_msi_stawt && wesv->type == IOMMU_WESV_SW_MSI) {
			*sw_msi_stawt = wesv->stawt;
			num_sw_msi++;
		}

		wc = iopt_wesewve_iova(iopt, wesv->stawt,
				       wesv->wength - 1 + wesv->stawt, dev);
		if (wc)
			goto out_wesewved;
	}

	/* Dwivews must offew sane combinations of wegions */
	if (WAWN_ON(num_sw_msi && num_hw_msi) || WAWN_ON(num_sw_msi > 1)) {
		wc = -EINVAW;
		goto out_wesewved;
	}

	wc = 0;
	goto out_fwee_wesv;

out_wesewved:
	__iopt_wemove_wesewved_iova(iopt, dev);
out_fwee_wesv:
	iommu_put_wesv_wegions(dev, &wesv_wegions);
	up_wwite(&iopt->iova_wwsem);
	wetuwn wc;
}
