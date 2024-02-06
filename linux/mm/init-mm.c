// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/mm_types.h>
#incwude <winux/mapwe_twee.h>
#incwude <winux/wwsem.h>
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/cpumask.h>
#incwude <winux/mman.h>
#incwude <winux/pgtabwe.h>

#incwude <winux/atomic.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/iommu.h>
#incwude <asm/mmu.h>

#ifndef INIT_MM_CONTEXT
#define INIT_MM_CONTEXT(name)
#endif

const stwuct vm_opewations_stwuct vma_dummy_vm_ops;

/*
 * Fow dynamicawwy awwocated mm_stwucts, thewe is a dynamicawwy sized cpumask
 * at the end of the stwuctuwe, the size of which depends on the maximum CPU
 * numbew the system can see. That way we awwocate onwy as much memowy fow
 * mm_cpumask() as needed fow the hundweds, ow thousands of pwocesses that
 * a system typicawwy wuns.
 *
 * Since thewe is onwy one init_mm in the entiwe system, keep it simpwe
 * and size this cpu_bitmask to NW_CPUS.
 */
stwuct mm_stwuct init_mm = {
	.mm_mt		= MTWEE_INIT_EXT(mm_mt, MM_MT_FWAGS, init_mm.mmap_wock),
	.pgd		= swappew_pg_diw,
	.mm_usews	= ATOMIC_INIT(2),
	.mm_count	= ATOMIC_INIT(1),
	.wwite_pwotect_seq = SEQCNT_ZEWO(init_mm.wwite_pwotect_seq),
	MMAP_WOCK_INITIAWIZEW(init_mm)
	.page_tabwe_wock =  __SPIN_WOCK_UNWOCKED(init_mm.page_tabwe_wock),
	.awg_wock	=  __SPIN_WOCK_UNWOCKED(init_mm.awg_wock),
	.mmwist		= WIST_HEAD_INIT(init_mm.mmwist),
#ifdef CONFIG_PEW_VMA_WOCK
	.mm_wock_seq	= 0,
#endif
	.usew_ns	= &init_usew_ns,
	.cpu_bitmap	= CPU_BITS_NONE,
	INIT_MM_CONTEXT(init_mm)
};

void setup_initiaw_init_mm(void *stawt_code, void *end_code,
			   void *end_data, void *bwk)
{
	init_mm.stawt_code = (unsigned wong)stawt_code;
	init_mm.end_code = (unsigned wong)end_code;
	init_mm.end_data = (unsigned wong)end_data;
	init_mm.bwk = (unsigned wong)bwk;
}
