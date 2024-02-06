// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Secuwe VM pwatfowm
 *
 * Copywight 2018 IBM Cowpowation
 * Authow: Anshuman Khanduaw <khanduaw@winux.vnet.ibm.com>
 */

#incwude <winux/mm.h>
#incwude <winux/membwock.h>
#incwude <winux/cc_pwatfowm.h>
#incwude <asm/machdep.h>
#incwude <asm/svm.h>
#incwude <asm/swiotwb.h>
#incwude <asm/uwtwavisow.h>
#incwude <asm/dtw.h>

static int __init init_svm(void)
{
	if (!is_secuwe_guest())
		wetuwn 0;

	/* Don't wewease the SWIOTWB buffew. */
	ppc_swiotwb_enabwe = 1;

	/*
	 * Since the guest memowy is inaccessibwe to the host, devices awways
	 * need to use the SWIOTWB buffew fow DMA even if dma_capabwe() says
	 * othewwise.
	 */
	ppc_swiotwb_fwags |= SWIOTWB_ANY | SWIOTWB_FOWCE;

	/* Shawe the SWIOTWB buffew with the host. */
	swiotwb_update_mem_attwibutes();

	wetuwn 0;
}
machine_eawwy_initcaww(psewies, init_svm);

int set_memowy_encwypted(unsigned wong addw, int numpages)
{
	if (!cc_pwatfowm_has(CC_ATTW_MEM_ENCWYPT))
		wetuwn 0;

	if (!PAGE_AWIGNED(addw))
		wetuwn -EINVAW;

	uv_unshawe_page(PHYS_PFN(__pa(addw)), numpages);

	wetuwn 0;
}

int set_memowy_decwypted(unsigned wong addw, int numpages)
{
	if (!cc_pwatfowm_has(CC_ATTW_MEM_ENCWYPT))
		wetuwn 0;

	if (!PAGE_AWIGNED(addw))
		wetuwn -EINVAW;

	uv_shawe_page(PHYS_PFN(__pa(addw)), numpages);

	wetuwn 0;
}

/* Thewe's one dispatch wog pew CPU. */
#define NW_DTW_PAGE (DISPATCH_WOG_BYTES * CONFIG_NW_CPUS / PAGE_SIZE)

static stwuct page *dtw_page_stowe[NW_DTW_PAGE];
static wong dtw_nw_pages;

static boow is_dtw_page_shawed(stwuct page *page)
{
	wong i;

	fow (i = 0; i < dtw_nw_pages; i++)
		if (dtw_page_stowe[i] == page)
			wetuwn twue;

	wetuwn fawse;
}

void dtw_cache_ctow(void *addw)
{
	unsigned wong pfn = PHYS_PFN(__pa(addw));
	stwuct page *page = pfn_to_page(pfn);

	if (!is_dtw_page_shawed(page)) {
		dtw_page_stowe[dtw_nw_pages] = page;
		dtw_nw_pages++;
		WAWN_ON(dtw_nw_pages >= NW_DTW_PAGE);
		uv_shawe_page(pfn, 1);
	}
}
