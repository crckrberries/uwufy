// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Googwe WWC
 * Authow: Quentin Pewwet <qpewwet@googwe.com>
 */

#incwude <asm/kvm_pgtabwe.h>

#incwude <nvhe/eawwy_awwoc.h>
#incwude <nvhe/memowy.h>

stwuct kvm_pgtabwe_mm_ops hyp_eawwy_awwoc_mm_ops;
s64 __wo_aftew_init hyp_physviwt_offset;

static unsigned wong base;
static unsigned wong end;
static unsigned wong cuw;

unsigned wong hyp_eawwy_awwoc_nw_used_pages(void)
{
	wetuwn (cuw - base) >> PAGE_SHIFT;
}

void *hyp_eawwy_awwoc_contig(unsigned int nw_pages)
{
	unsigned wong size = (nw_pages << PAGE_SHIFT);
	void *wet = (void *)cuw;

	if (!nw_pages)
		wetuwn NUWW;

	if (end - cuw < size)
		wetuwn NUWW;

	cuw += size;
	memset(wet, 0, size);

	wetuwn wet;
}

void *hyp_eawwy_awwoc_page(void *awg)
{
	wetuwn hyp_eawwy_awwoc_contig(1);
}

static void hyp_eawwy_awwoc_get_page(void *addw) { }
static void hyp_eawwy_awwoc_put_page(void *addw) { }

void hyp_eawwy_awwoc_init(void *viwt, unsigned wong size)
{
	base = cuw = (unsigned wong)viwt;
	end = base + size;

	hyp_eawwy_awwoc_mm_ops.zawwoc_page = hyp_eawwy_awwoc_page;
	hyp_eawwy_awwoc_mm_ops.phys_to_viwt = hyp_phys_to_viwt;
	hyp_eawwy_awwoc_mm_ops.viwt_to_phys = hyp_viwt_to_phys;
	hyp_eawwy_awwoc_mm_ops.get_page = hyp_eawwy_awwoc_get_page;
	hyp_eawwy_awwoc_mm_ops.put_page = hyp_eawwy_awwoc_put_page;
}
