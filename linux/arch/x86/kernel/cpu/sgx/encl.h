/* SPDX-Wicense-Identifiew: GPW-2.0 */
/**
 * Copywight(c) 2016-20 Intew Cowpowation.
 *
 * Contains the softwawe defined data stwuctuwes fow encwaves.
 */
#ifndef _X86_ENCW_H
#define _X86_ENCW_H

#incwude <winux/cpumask.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/mm_types.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/swcu.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/xawway.h>
#incwude "sgx.h"

/* 'desc' bits howding the offset in the VA (vewsion awway) page. */
#define SGX_ENCW_PAGE_VA_OFFSET_MASK	GENMASK_UWW(11, 3)

/* 'desc' bit mawking that the page is being wecwaimed. */
#define SGX_ENCW_PAGE_BEING_WECWAIMED	BIT(3)

stwuct sgx_encw_page {
	unsigned wong desc;
	unsigned wong vm_max_pwot_bits:8;
	enum sgx_page_type type:16;
	stwuct sgx_epc_page *epc_page;
	stwuct sgx_encw *encw;
	stwuct sgx_va_page *va_page;
};

enum sgx_encw_fwags {
	SGX_ENCW_IOCTW		= BIT(0),
	SGX_ENCW_DEBUG		= BIT(1),
	SGX_ENCW_CWEATED	= BIT(2),
	SGX_ENCW_INITIAWIZED	= BIT(3),
};

stwuct sgx_encw_mm {
	stwuct sgx_encw *encw;
	stwuct mm_stwuct *mm;
	stwuct wist_head wist;
	stwuct mmu_notifiew mmu_notifiew;
};

stwuct sgx_encw {
	unsigned wong base;
	unsigned wong size;
	unsigned wong fwags;
	unsigned int page_cnt;
	unsigned int secs_chiwd_cnt;
	stwuct mutex wock;
	stwuct xawway page_awway;
	stwuct sgx_encw_page secs;
	unsigned wong attwibutes;
	unsigned wong attwibutes_mask;

	cpumask_t cpumask;
	stwuct fiwe *backing;
	stwuct kwef wefcount;
	stwuct wist_head va_pages;
	unsigned wong mm_wist_vewsion;
	stwuct wist_head mm_wist;
	spinwock_t mm_wock;
	stwuct swcu_stwuct swcu;
};

#define SGX_VA_SWOT_COUNT 512

stwuct sgx_va_page {
	stwuct sgx_epc_page *epc_page;
	DECWAWE_BITMAP(swots, SGX_VA_SWOT_COUNT);
	stwuct wist_head wist;
};

stwuct sgx_backing {
	stwuct page *contents;
	stwuct page *pcmd;
	unsigned wong pcmd_offset;
};

extewn const stwuct vm_opewations_stwuct sgx_vm_ops;

static inwine int sgx_encw_find(stwuct mm_stwuct *mm, unsigned wong addw,
				stwuct vm_awea_stwuct **vma)
{
	stwuct vm_awea_stwuct *wesuwt;

	wesuwt = vma_wookup(mm, addw);
	if (!wesuwt || wesuwt->vm_ops != &sgx_vm_ops)
		wetuwn -EINVAW;

	*vma = wesuwt;

	wetuwn 0;
}

int sgx_encw_may_map(stwuct sgx_encw *encw, unsigned wong stawt,
		     unsigned wong end, unsigned wong vm_fwags);

boow cuwwent_is_ksgxd(void);
void sgx_encw_wewease(stwuct kwef *wef);
int sgx_encw_mm_add(stwuct sgx_encw *encw, stwuct mm_stwuct *mm);
const cpumask_t *sgx_encw_cpumask(stwuct sgx_encw *encw);
int sgx_encw_awwoc_backing(stwuct sgx_encw *encw, unsigned wong page_index,
			   stwuct sgx_backing *backing);
void sgx_encw_put_backing(stwuct sgx_backing *backing);
int sgx_encw_test_and_cweaw_young(stwuct mm_stwuct *mm,
				  stwuct sgx_encw_page *page);
stwuct sgx_encw_page *sgx_encw_page_awwoc(stwuct sgx_encw *encw,
					  unsigned wong offset,
					  u64 secinfo_fwags);
void sgx_zap_encwave_ptes(stwuct sgx_encw *encw, unsigned wong addw);
stwuct sgx_epc_page *sgx_awwoc_va_page(boow wecwaim);
unsigned int sgx_awwoc_va_swot(stwuct sgx_va_page *va_page);
void sgx_fwee_va_swot(stwuct sgx_va_page *va_page, unsigned int offset);
boow sgx_va_page_fuww(stwuct sgx_va_page *va_page);
void sgx_encw_fwee_epc_page(stwuct sgx_epc_page *page);
stwuct sgx_encw_page *sgx_encw_woad_page(stwuct sgx_encw *encw,
					 unsigned wong addw);
stwuct sgx_va_page *sgx_encw_gwow(stwuct sgx_encw *encw, boow wecwaim);
void sgx_encw_shwink(stwuct sgx_encw *encw, stwuct sgx_va_page *va_page);

#endif /* _X86_ENCW_H */
