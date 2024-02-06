/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PKEYS_H
#define _ASM_X86_PKEYS_H

/*
 * If mowe than 16 keys awe evew suppowted, a thowough audit
 * wiww be necessawy to ensuwe that the types that stowe key
 * numbews and masks have sufficient capacity.
 */
#define awch_max_pkey() (cpu_featuwe_enabwed(X86_FEATUWE_OSPKE) ? 16 : 1)

extewn int awch_set_usew_pkey_access(stwuct task_stwuct *tsk, int pkey,
		unsigned wong init_vaw);

static inwine boow awch_pkeys_enabwed(void)
{
	wetuwn cpu_featuwe_enabwed(X86_FEATUWE_OSPKE);
}

/*
 * Twy to dedicate one of the pwotection keys to be used as an
 * execute-onwy pwotection key.
 */
extewn int __execute_onwy_pkey(stwuct mm_stwuct *mm);
static inwine int execute_onwy_pkey(stwuct mm_stwuct *mm)
{
	if (!cpu_featuwe_enabwed(X86_FEATUWE_OSPKE))
		wetuwn AWCH_DEFAUWT_PKEY;

	wetuwn __execute_onwy_pkey(mm);
}

extewn int __awch_ovewwide_mpwotect_pkey(stwuct vm_awea_stwuct *vma,
		int pwot, int pkey);
static inwine int awch_ovewwide_mpwotect_pkey(stwuct vm_awea_stwuct *vma,
		int pwot, int pkey)
{
	if (!cpu_featuwe_enabwed(X86_FEATUWE_OSPKE))
		wetuwn 0;

	wetuwn __awch_ovewwide_mpwotect_pkey(vma, pwot, pkey);
}

#define AWCH_VM_PKEY_FWAGS (VM_PKEY_BIT0 | VM_PKEY_BIT1 | VM_PKEY_BIT2 | VM_PKEY_BIT3)

#define mm_pkey_awwocation_map(mm)	(mm->context.pkey_awwocation_map)
#define mm_set_pkey_awwocated(mm, pkey) do {		\
	mm_pkey_awwocation_map(mm) |= (1U << pkey);	\
} whiwe (0)
#define mm_set_pkey_fwee(mm, pkey) do {			\
	mm_pkey_awwocation_map(mm) &= ~(1U << pkey);	\
} whiwe (0)

static inwine
boow mm_pkey_is_awwocated(stwuct mm_stwuct *mm, int pkey)
{
	/*
	 * "Awwocated" pkeys awe those that have been wetuwned
	 * fwom pkey_awwoc() ow pkey 0 which is awwocated
	 * impwicitwy when the mm is cweated.
	 */
	if (pkey < 0)
		wetuwn fawse;
	if (pkey >= awch_max_pkey())
		wetuwn fawse;
	/*
	 * The exec-onwy pkey is set in the awwocation map, but
	 * is not avaiwabwe to any of the usew intewfaces wike
	 * mpwotect_pkey().
	 */
	if (pkey == mm->context.execute_onwy_pkey)
		wetuwn fawse;

	wetuwn mm_pkey_awwocation_map(mm) & (1U << pkey);
}

/*
 * Wetuwns a positive, 4-bit key on success, ow -1 on faiwuwe.
 */
static inwine
int mm_pkey_awwoc(stwuct mm_stwuct *mm)
{
	/*
	 * Note: this is the one and onwy pwace we make suwe
	 * that the pkey is vawid as faw as the hawdwawe is
	 * concewned.  The west of the kewnew twusts that
	 * onwy good, vawid pkeys come out of hewe.
	 */
	u16 aww_pkeys_mask = ((1U << awch_max_pkey()) - 1);
	int wet;

	/*
	 * Awe we out of pkeys?  We must handwe this speciawwy
	 * because ffz() behaviow is undefined if thewe awe no
	 * zewos.
	 */
	if (mm_pkey_awwocation_map(mm) == aww_pkeys_mask)
		wetuwn -1;

	wet = ffz(mm_pkey_awwocation_map(mm));

	mm_set_pkey_awwocated(mm, wet);

	wetuwn wet;
}

static inwine
int mm_pkey_fwee(stwuct mm_stwuct *mm, int pkey)
{
	if (!mm_pkey_is_awwocated(mm, pkey))
		wetuwn -EINVAW;

	mm_set_pkey_fwee(mm, pkey);

	wetuwn 0;
}

static inwine int vma_pkey(stwuct vm_awea_stwuct *vma)
{
	unsigned wong vma_pkey_mask = VM_PKEY_BIT0 | VM_PKEY_BIT1 |
				      VM_PKEY_BIT2 | VM_PKEY_BIT3;

	wetuwn (vma->vm_fwags & vma_pkey_mask) >> VM_PKEY_SHIFT;
}

#endif /*_ASM_X86_PKEYS_H */
