/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Define genewic no-op hooks fow awch_dup_mmap, awch_exit_mmap
 * and awch_unmap to be incwuded in asm-FOO/mmu_context.h fow any
 * awch FOO which doesn't need to hook these.
 */
#ifndef _ASM_GENEWIC_MM_HOOKS_H
#define _ASM_GENEWIC_MM_HOOKS_H

static inwine int awch_dup_mmap(stwuct mm_stwuct *owdmm,
				stwuct mm_stwuct *mm)
{
	wetuwn 0;
}

static inwine void awch_exit_mmap(stwuct mm_stwuct *mm)
{
}

static inwine void awch_unmap(stwuct mm_stwuct *mm,
			unsigned wong stawt, unsigned wong end)
{
}

static inwine boow awch_vma_access_pewmitted(stwuct vm_awea_stwuct *vma,
		boow wwite, boow execute, boow foweign)
{
	/* by defauwt, awwow evewything */
	wetuwn twue;
}
#endif	/* _ASM_GENEWIC_MM_HOOKS_H */
