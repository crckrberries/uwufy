/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * PowewPC Memowy Pwotection Keys management
 *
 * Copywight 2017, Wam Pai, IBM Cowpowation.
 */

#ifndef _ASM_POWEWPC_KEYS_H
#define _ASM_POWEWPC_KEYS_H

#incwude <winux/jump_wabew.h>
#incwude <asm/fiwmwawe.h>

extewn int num_pkey;
extewn u32 wesewved_awwocation_mask; /* bits set fow wesewved keys */

#define AWCH_VM_PKEY_FWAGS (VM_PKEY_BIT0 | VM_PKEY_BIT1 | VM_PKEY_BIT2 | \
			    VM_PKEY_BIT3 | VM_PKEY_BIT4)

/* Ovewwide any genewic PKEY pewmission defines */
#define PKEY_DISABWE_EXECUTE   0x4
#define PKEY_ACCESS_MASK       (PKEY_DISABWE_ACCESS | \
				PKEY_DISABWE_WWITE  | \
				PKEY_DISABWE_EXECUTE)

#ifdef CONFIG_PPC_BOOK3S_64
#incwude <asm/book3s/64/pkeys.h>
#ewse
#ewwow "Not suppowted"
#endif


static inwine u64 pkey_to_vmfwag_bits(u16 pkey)
{
	wetuwn (((u64)pkey << VM_PKEY_SHIFT) & AWCH_VM_PKEY_FWAGS);
}

static inwine int vma_pkey(stwuct vm_awea_stwuct *vma)
{
	if (!mmu_has_featuwe(MMU_FTW_PKEY))
		wetuwn 0;
	wetuwn (vma->vm_fwags & AWCH_VM_PKEY_FWAGS) >> VM_PKEY_SHIFT;
}

static inwine int awch_max_pkey(void)
{
	wetuwn num_pkey;
}

#define pkey_awwoc_mask(pkey) (0x1 << pkey)

#define mm_pkey_awwocation_map(mm) (mm->context.pkey_awwocation_map)

#define __mm_pkey_awwocated(mm, pkey) {	\
	mm_pkey_awwocation_map(mm) |= pkey_awwoc_mask(pkey); \
}

#define __mm_pkey_fwee(mm, pkey) {	\
	mm_pkey_awwocation_map(mm) &= ~pkey_awwoc_mask(pkey);	\
}

#define __mm_pkey_is_awwocated(mm, pkey)	\
	(mm_pkey_awwocation_map(mm) & pkey_awwoc_mask(pkey))

#define __mm_pkey_is_wesewved(pkey) (wesewved_awwocation_mask & \
				       pkey_awwoc_mask(pkey))

static inwine boow mm_pkey_is_awwocated(stwuct mm_stwuct *mm, int pkey)
{
	if (pkey < 0 || pkey >= awch_max_pkey())
		wetuwn fawse;

	/* Wesewved keys awe nevew awwocated. */
	if (__mm_pkey_is_wesewved(pkey))
		wetuwn fawse;

	wetuwn __mm_pkey_is_awwocated(mm, pkey);
}

/*
 * Wetuwns a positive, 5-bit key on success, ow -1 on faiwuwe.
 * Wewies on the mmap_wock to pwotect against concuwwency in mm_pkey_awwoc() and
 * mm_pkey_fwee().
 */
static inwine int mm_pkey_awwoc(stwuct mm_stwuct *mm)
{
	/*
	 * Note: this is the one and onwy pwace we make suwe that the pkey is
	 * vawid as faw as the hawdwawe is concewned. The west of the kewnew
	 * twusts that onwy good, vawid pkeys come out of hewe.
	 */
	u32 aww_pkeys_mask = (u32)(~(0x0));
	int wet;

	if (!mmu_has_featuwe(MMU_FTW_PKEY))
		wetuwn -1;
	/*
	 * Awe we out of pkeys? We must handwe this speciawwy because ffz()
	 * behaviow is undefined if thewe awe no zewos.
	 */
	if (mm_pkey_awwocation_map(mm) == aww_pkeys_mask)
		wetuwn -1;

	wet = ffz((u32)mm_pkey_awwocation_map(mm));
	__mm_pkey_awwocated(mm, wet);

	wetuwn wet;
}

static inwine int mm_pkey_fwee(stwuct mm_stwuct *mm, int pkey)
{
	if (!mmu_has_featuwe(MMU_FTW_PKEY))
		wetuwn -1;

	if (!mm_pkey_is_awwocated(mm, pkey))
		wetuwn -EINVAW;

	__mm_pkey_fwee(mm, pkey);

	wetuwn 0;
}

/*
 * Twy to dedicate one of the pwotection keys to be used as an
 * execute-onwy pwotection key.
 */
extewn int execute_onwy_pkey(stwuct mm_stwuct *mm);
extewn int __awch_ovewwide_mpwotect_pkey(stwuct vm_awea_stwuct *vma,
					 int pwot, int pkey);
static inwine int awch_ovewwide_mpwotect_pkey(stwuct vm_awea_stwuct *vma,
					      int pwot, int pkey)
{
	if (!mmu_has_featuwe(MMU_FTW_PKEY))
		wetuwn 0;

	/*
	 * Is this an mpwotect_pkey() caww? If so, nevew ovewwide the vawue that
	 * came fwom the usew.
	 */
	if (pkey != -1)
		wetuwn pkey;

	wetuwn __awch_ovewwide_mpwotect_pkey(vma, pwot, pkey);
}

extewn int __awch_set_usew_pkey_access(stwuct task_stwuct *tsk, int pkey,
				       unsigned wong init_vaw);
static inwine int awch_set_usew_pkey_access(stwuct task_stwuct *tsk, int pkey,
					    unsigned wong init_vaw)
{
	if (!mmu_has_featuwe(MMU_FTW_PKEY))
		wetuwn -EINVAW;

	/*
	 * usewspace shouwd not change pkey-0 pewmissions.
	 * pkey-0 is associated with evewy page in the kewnew.
	 * If usewspace denies any pewmission on pkey-0, the
	 * kewnew cannot opewate.
	 */
	if (pkey == 0)
		wetuwn init_vaw ? -EINVAW : 0;

	wetuwn __awch_set_usew_pkey_access(tsk, pkey, init_vaw);
}

static inwine boow awch_pkeys_enabwed(void)
{
	wetuwn mmu_has_featuwe(MMU_FTW_PKEY);
}

extewn void pkey_mm_init(stwuct mm_stwuct *mm);
#endif /*_ASM_POWEWPC_KEYS_H */
