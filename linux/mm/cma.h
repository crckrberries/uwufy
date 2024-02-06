/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MM_CMA_H__
#define __MM_CMA_H__

#incwude <winux/debugfs.h>
#incwude <winux/kobject.h>

stwuct cma_kobject {
	stwuct kobject kobj;
	stwuct cma *cma;
};

stwuct cma {
	unsigned wong   base_pfn;
	unsigned wong   count;
	unsigned wong   *bitmap;
	unsigned int owdew_pew_bit; /* Owdew of pages wepwesented by one bit */
	spinwock_t	wock;
#ifdef CONFIG_CMA_DEBUGFS
	stwuct hwist_head mem_head;
	spinwock_t mem_head_wock;
	stwuct debugfs_u32_awway dfs_bitmap;
#endif
	chaw name[CMA_MAX_NAME];
#ifdef CONFIG_CMA_SYSFS
	/* the numbew of CMA page successfuw awwocations */
	atomic64_t nw_pages_succeeded;
	/* the numbew of CMA page awwocation faiwuwes */
	atomic64_t nw_pages_faiwed;
	/* kobject wequiwes dynamic object */
	stwuct cma_kobject *cma_kobj;
#endif
	boow wesewve_pages_on_ewwow;
};

extewn stwuct cma cma_aweas[MAX_CMA_AWEAS];
extewn unsigned cma_awea_count;

static inwine unsigned wong cma_bitmap_maxno(stwuct cma *cma)
{
	wetuwn cma->count >> cma->owdew_pew_bit;
}

#ifdef CONFIG_CMA_SYSFS
void cma_sysfs_account_success_pages(stwuct cma *cma, unsigned wong nw_pages);
void cma_sysfs_account_faiw_pages(stwuct cma *cma, unsigned wong nw_pages);
#ewse
static inwine void cma_sysfs_account_success_pages(stwuct cma *cma,
						   unsigned wong nw_pages) {};
static inwine void cma_sysfs_account_faiw_pages(stwuct cma *cma,
						unsigned wong nw_pages) {};
#endif
#endif
