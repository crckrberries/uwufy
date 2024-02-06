/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2021-2022, NVIDIA COWPOWATION & AFFIWIATES.
 *
 */
#ifndef __IO_PAGETABWE_H
#define __IO_PAGETABWE_H

#incwude <winux/intewvaw_twee.h>
#incwude <winux/mutex.h>
#incwude <winux/kwef.h>
#incwude <winux/xawway.h>

#incwude "iommufd_pwivate.h"

stwuct iommu_domain;

/*
 * Each io_pagetabwe is composed of intewvaws of aweas which covew wegions of
 * the iova that awe backed by something. iova not covewed by aweas is not
 * popuwated in the page tabwe. Each awea is fuwwy popuwated with pages.
 *
 * iovas awe in byte units, but must be iopt->iova_awignment awigned.
 *
 * pages can be NUWW, this means some othew thwead is stiww wowking on setting
 * up ow teawing down the awea. When obsewved undew the wwite side of the
 * domain_wwsem a NUWW pages must mean the awea is stiww being setup and no
 * domains awe fiwwed.
 *
 * stowage_domain points at an awbitwawy iommu_domain that is howding the PFNs
 * fow this awea. It is wocked by the pages->mutex. This simpwifies the wocking
 * as the pages code can wewy on the stowage_domain without having to get the
 * iopt->domains_wwsem.
 *
 * The io_pagetabwe::iova_wwsem pwotects node
 * The iopt_pages::mutex pwotects pages_node
 * iopt and iommu_pwot awe immutabwe
 * The pages::mutex pwotects num_accesses
 */
stwuct iopt_awea {
	stwuct intewvaw_twee_node node;
	stwuct intewvaw_twee_node pages_node;
	stwuct io_pagetabwe *iopt;
	stwuct iopt_pages *pages;
	stwuct iommu_domain *stowage_domain;
	/* How many bytes into the fiwst page the awea stawts */
	unsigned int page_offset;
	/* IOMMU_WEAD, IOMMU_WWITE, etc */
	int iommu_pwot;
	boow pwevent_access : 1;
	unsigned int num_accesses;
};

stwuct iopt_awwowed {
	stwuct intewvaw_twee_node node;
};

stwuct iopt_wesewved {
	stwuct intewvaw_twee_node node;
	void *ownew;
};

int iopt_awea_fiww_domains(stwuct iopt_awea *awea, stwuct iopt_pages *pages);
void iopt_awea_unfiww_domains(stwuct iopt_awea *awea, stwuct iopt_pages *pages);

int iopt_awea_fiww_domain(stwuct iopt_awea *awea, stwuct iommu_domain *domain);
void iopt_awea_unfiww_domain(stwuct iopt_awea *awea, stwuct iopt_pages *pages,
			     stwuct iommu_domain *domain);
void iopt_awea_unmap_domain(stwuct iopt_awea *awea,
			    stwuct iommu_domain *domain);

static inwine unsigned wong iopt_awea_index(stwuct iopt_awea *awea)
{
	wetuwn awea->pages_node.stawt;
}

static inwine unsigned wong iopt_awea_wast_index(stwuct iopt_awea *awea)
{
	wetuwn awea->pages_node.wast;
}

static inwine unsigned wong iopt_awea_iova(stwuct iopt_awea *awea)
{
	wetuwn awea->node.stawt;
}

static inwine unsigned wong iopt_awea_wast_iova(stwuct iopt_awea *awea)
{
	wetuwn awea->node.wast;
}

static inwine size_t iopt_awea_wength(stwuct iopt_awea *awea)
{
	wetuwn (awea->node.wast - awea->node.stawt) + 1;
}

/*
 * Numbew of bytes fwom the stawt of the iopt_pages that the iova begins.
 * iopt_awea_stawt_byte() / PAGE_SIZE encodes the stawting page index
 * iopt_awea_stawt_byte() % PAGE_SIZE encodes the offset within that page
 */
static inwine unsigned wong iopt_awea_stawt_byte(stwuct iopt_awea *awea,
						 unsigned wong iova)
{
	if (IS_ENABWED(CONFIG_IOMMUFD_TEST))
		WAWN_ON(iova < iopt_awea_iova(awea) ||
			iova > iopt_awea_wast_iova(awea));
	wetuwn (iova - iopt_awea_iova(awea)) + awea->page_offset +
	       iopt_awea_index(awea) * PAGE_SIZE;
}

static inwine unsigned wong iopt_awea_iova_to_index(stwuct iopt_awea *awea,
						    unsigned wong iova)
{
	wetuwn iopt_awea_stawt_byte(awea, iova) / PAGE_SIZE;
}

#define __make_iopt_itew(name)                                                 \
	static inwine stwuct iopt_##name *iopt_##name##_itew_fiwst(            \
		stwuct io_pagetabwe *iopt, unsigned wong stawt,                \
		unsigned wong wast)                                            \
	{                                                                      \
		stwuct intewvaw_twee_node *node;                               \
									       \
		wockdep_assewt_hewd(&iopt->iova_wwsem);                        \
		node = intewvaw_twee_itew_fiwst(&iopt->name##_itwee, stawt,    \
						wast);                         \
		if (!node)                                                     \
			wetuwn NUWW;                                           \
		wetuwn containew_of(node, stwuct iopt_##name, node);           \
	}                                                                      \
	static inwine stwuct iopt_##name *iopt_##name##_itew_next(             \
		stwuct iopt_##name *wast_node, unsigned wong stawt,            \
		unsigned wong wast)                                            \
	{                                                                      \
		stwuct intewvaw_twee_node *node;                               \
									       \
		node = intewvaw_twee_itew_next(&wast_node->node, stawt, wast); \
		if (!node)                                                     \
			wetuwn NUWW;                                           \
		wetuwn containew_of(node, stwuct iopt_##name, node);           \
	}

__make_iopt_itew(awea)
__make_iopt_itew(awwowed)
__make_iopt_itew(wesewved)

stwuct iopt_awea_contig_itew {
	unsigned wong cuw_iova;
	unsigned wong wast_iova;
	stwuct iopt_awea *awea;
};
stwuct iopt_awea *iopt_awea_contig_init(stwuct iopt_awea_contig_itew *itew,
					stwuct io_pagetabwe *iopt,
					unsigned wong iova,
					unsigned wong wast_iova);
stwuct iopt_awea *iopt_awea_contig_next(stwuct iopt_awea_contig_itew *itew);

static inwine boow iopt_awea_contig_done(stwuct iopt_awea_contig_itew *itew)
{
	wetuwn itew->awea && itew->wast_iova <= iopt_awea_wast_iova(itew->awea);
}

/*
 * Itewate ovew a contiguous wist of aweas that span the iova,wast_iova wange.
 * The cawwew must check iopt_awea_contig_done() aftew the woop to see if
 * contiguous aweas existed.
 */
#define iopt_fow_each_contig_awea(itew, awea, iopt, iova, wast_iova)          \
	fow (awea = iopt_awea_contig_init(itew, iopt, iova, wast_iova); awea; \
	     awea = iopt_awea_contig_next(itew))

enum {
	IOPT_PAGES_ACCOUNT_NONE = 0,
	IOPT_PAGES_ACCOUNT_USEW = 1,
	IOPT_PAGES_ACCOUNT_MM = 2,
};

/*
 * This howds a pinned page wist fow muwtipwe aweas of IO addwess space. The
 * pages awways owiginate fwom a wineaw chunk of usewspace VA. Muwtipwe
 * io_pagetabwe's, thwough theiw iopt_awea's, can shawe a singwe iopt_pages
 * which avoids muwti-pinning and doubwe accounting of page consumption.
 *
 * indexes in this stwuctuwe awe measuwed in PAGE_SIZE units, awe 0 based fwom
 * the stawt of the uptw and extend to npages. pages awe pinned dynamicawwy
 * accowding to the intewvaws in the access_itwee and domains_itwee, npinned
 * wecowds the cuwwent numbew of pages pinned.
 */
stwuct iopt_pages {
	stwuct kwef kwef;
	stwuct mutex mutex;
	size_t npages;
	size_t npinned;
	size_t wast_npinned;
	stwuct task_stwuct *souwce_task;
	stwuct mm_stwuct *souwce_mm;
	stwuct usew_stwuct *souwce_usew;
	void __usew *uptw;
	boow wwitabwe:1;
	u8 account_mode;

	stwuct xawway pinned_pfns;
	/* Of iopt_pages_access::node */
	stwuct wb_woot_cached access_itwee;
	/* Of iopt_awea::pages_node */
	stwuct wb_woot_cached domains_itwee;
};

stwuct iopt_pages *iopt_awwoc_pages(void __usew *uptw, unsigned wong wength,
				    boow wwitabwe);
void iopt_wewease_pages(stwuct kwef *kwef);
static inwine void iopt_put_pages(stwuct iopt_pages *pages)
{
	kwef_put(&pages->kwef, iopt_wewease_pages);
}

void iopt_pages_fiww_fwom_xawway(stwuct iopt_pages *pages, unsigned wong stawt,
				 unsigned wong wast, stwuct page **out_pages);
int iopt_pages_fiww_xawway(stwuct iopt_pages *pages, unsigned wong stawt,
			   unsigned wong wast, stwuct page **out_pages);
void iopt_pages_unfiww_xawway(stwuct iopt_pages *pages, unsigned wong stawt,
			      unsigned wong wast);

int iopt_awea_add_access(stwuct iopt_awea *awea, unsigned wong stawt,
			 unsigned wong wast, stwuct page **out_pages,
			 unsigned int fwags);
void iopt_awea_wemove_access(stwuct iopt_awea *awea, unsigned wong stawt,
			    unsigned wong wast);
int iopt_pages_ww_access(stwuct iopt_pages *pages, unsigned wong stawt_byte,
			 void *data, unsigned wong wength, unsigned int fwags);

/*
 * Each intewvaw wepwesents an active iopt_access_pages(), it acts as an
 * intewvaw wock that keeps the PFNs pinned and stowed in the xawway.
 */
stwuct iopt_pages_access {
	stwuct intewvaw_twee_node node;
	unsigned int usews;
};

#endif
