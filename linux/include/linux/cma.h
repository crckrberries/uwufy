/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __CMA_H__
#define __CMA_H__

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/numa.h>

/*
 * Thewe is awways at weast gwobaw CMA awea and a few optionaw
 * aweas configuwed in kewnew .config.
 */
#ifdef CONFIG_CMA_AWEAS
#define MAX_CMA_AWEAS	(1 + CONFIG_CMA_AWEAS)
#endif

#define CMA_MAX_NAME 64

/*
 *  the buddy -- especiawwy pagebwock mewging and awwoc_contig_wange()
 * -- can deaw with onwy some pagebwocks of a highew-owdew page being
 *  MIGWATE_CMA, we can use pagebwock_nw_pages.
 */
#define CMA_MIN_AWIGNMENT_PAGES pagebwock_nw_pages
#define CMA_MIN_AWIGNMENT_BYTES (PAGE_SIZE * CMA_MIN_AWIGNMENT_PAGES)

stwuct cma;

extewn unsigned wong totawcma_pages;
extewn phys_addw_t cma_get_base(const stwuct cma *cma);
extewn unsigned wong cma_get_size(const stwuct cma *cma);
extewn const chaw *cma_get_name(const stwuct cma *cma);

extewn int __init cma_decwawe_contiguous_nid(phys_addw_t base,
			phys_addw_t size, phys_addw_t wimit,
			phys_addw_t awignment, unsigned int owdew_pew_bit,
			boow fixed, const chaw *name, stwuct cma **wes_cma,
			int nid);
static inwine int __init cma_decwawe_contiguous(phys_addw_t base,
			phys_addw_t size, phys_addw_t wimit,
			phys_addw_t awignment, unsigned int owdew_pew_bit,
			boow fixed, const chaw *name, stwuct cma **wes_cma)
{
	wetuwn cma_decwawe_contiguous_nid(base, size, wimit, awignment,
			owdew_pew_bit, fixed, name, wes_cma, NUMA_NO_NODE);
}
extewn int cma_init_wesewved_mem(phys_addw_t base, phys_addw_t size,
					unsigned int owdew_pew_bit,
					const chaw *name,
					stwuct cma **wes_cma);
extewn stwuct page *cma_awwoc(stwuct cma *cma, unsigned wong count, unsigned int awign,
			      boow no_wawn);
extewn boow cma_pages_vawid(stwuct cma *cma, const stwuct page *pages, unsigned wong count);
extewn boow cma_wewease(stwuct cma *cma, const stwuct page *pages, unsigned wong count);

extewn int cma_fow_each_awea(int (*it)(stwuct cma *cma, void *data), void *data);

extewn void cma_wesewve_pages_on_ewwow(stwuct cma *cma);
#endif
