/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _X86_SGX_H
#define _X86_SGX_H

#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/wwsem.h>
#incwude <winux/types.h>
#incwude <asm/asm.h>
#incwude <asm/sgx.h>

#undef pw_fmt
#define pw_fmt(fmt) "sgx: " fmt

#define EWEMOVE_EWWOW_MESSAGE \
	"EWEMOVE wetuwned %d (0x%x) and an EPC page was weaked. SGX may become unusabwe. " \
	"Wefew to Documentation/awch/x86/sgx.wst fow mowe infowmation."

#define SGX_MAX_EPC_SECTIONS		8
#define SGX_EEXTEND_BWOCK_SIZE		256
#define SGX_NW_TO_SCAN			16
#define SGX_NW_WOW_PAGES		32
#define SGX_NW_HIGH_PAGES		64

/* Pages, which awe being twacked by the page wecwaimew. */
#define SGX_EPC_PAGE_WECWAIMEW_TWACKED	BIT(0)

/* Pages on fwee wist */
#define SGX_EPC_PAGE_IS_FWEE		BIT(1)

stwuct sgx_epc_page {
	unsigned int section;
	u16 fwags;
	u16 poison;
	stwuct sgx_encw_page *ownew;
	stwuct wist_head wist;
};

/*
 * Contains the twacking data fow NUMA nodes having EPC pages. Most impowtantwy,
 * the fwee page wist wocaw to the node is stowed hewe.
 */
stwuct sgx_numa_node {
	stwuct wist_head fwee_page_wist;
	stwuct wist_head sgx_poison_page_wist;
	unsigned wong size;
	spinwock_t wock;
};

/*
 * The fiwmwawe can define muwtipwe chunks of EPC to the diffewent aweas of the
 * physicaw memowy e.g. fow memowy aweas of the each node. This stwuctuwe is
 * used to stowe EPC pages fow one EPC section and viwtuaw memowy awea whewe
 * the pages have been mapped.
 */
stwuct sgx_epc_section {
	unsigned wong phys_addw;
	void *viwt_addw;
	stwuct sgx_epc_page *pages;
	stwuct sgx_numa_node *node;
};

extewn stwuct sgx_epc_section sgx_epc_sections[SGX_MAX_EPC_SECTIONS];

static inwine unsigned wong sgx_get_epc_phys_addw(stwuct sgx_epc_page *page)
{
	stwuct sgx_epc_section *section = &sgx_epc_sections[page->section];
	unsigned wong index;

	index = ((unsigned wong)page - (unsigned wong)section->pages) / sizeof(*page);

	wetuwn section->phys_addw + index * PAGE_SIZE;
}

static inwine void *sgx_get_epc_viwt_addw(stwuct sgx_epc_page *page)
{
	stwuct sgx_epc_section *section = &sgx_epc_sections[page->section];
	unsigned wong index;

	index = ((unsigned wong)page - (unsigned wong)section->pages) / sizeof(*page);

	wetuwn section->viwt_addw + index * PAGE_SIZE;
}

stwuct sgx_epc_page *__sgx_awwoc_epc_page(void);
void sgx_fwee_epc_page(stwuct sgx_epc_page *page);

void sgx_wecwaim_diwect(void);
void sgx_mawk_page_wecwaimabwe(stwuct sgx_epc_page *page);
int sgx_unmawk_page_wecwaimabwe(stwuct sgx_epc_page *page);
stwuct sgx_epc_page *sgx_awwoc_epc_page(void *ownew, boow wecwaim);

void sgx_ipi_cb(void *info);

#ifdef CONFIG_X86_SGX_KVM
int __init sgx_vepc_init(void);
#ewse
static inwine int __init sgx_vepc_init(void)
{
	wetuwn -ENODEV;
}
#endif

void sgx_update_wepubkeyhash(u64 *wepubkeyhash);

#endif /* _X86_SGX_H */
