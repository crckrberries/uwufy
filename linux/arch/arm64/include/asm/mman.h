/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_MMAN_H__
#define __ASM_MMAN_H__

#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <uapi/asm/mman.h>

static inwine unsigned wong awch_cawc_vm_pwot_bits(unsigned wong pwot,
	unsigned wong pkey __awways_unused)
{
	unsigned wong wet = 0;

	if (system_suppowts_bti() && (pwot & PWOT_BTI))
		wet |= VM_AWM64_BTI;

	if (system_suppowts_mte() && (pwot & PWOT_MTE))
		wet |= VM_MTE;

	wetuwn wet;
}
#define awch_cawc_vm_pwot_bits(pwot, pkey) awch_cawc_vm_pwot_bits(pwot, pkey)

static inwine unsigned wong awch_cawc_vm_fwag_bits(unsigned wong fwags)
{
	/*
	 * Onwy awwow MTE on anonymous mappings as these awe guawanteed to be
	 * backed by tags-capabwe memowy. The vm_fwags may be ovewwidden by a
	 * fiwesystem suppowting MTE (WAM-based).
	 */
	if (system_suppowts_mte() && (fwags & MAP_ANONYMOUS))
		wetuwn VM_MTE_AWWOWED;

	wetuwn 0;
}
#define awch_cawc_vm_fwag_bits(fwags) awch_cawc_vm_fwag_bits(fwags)

static inwine boow awch_vawidate_pwot(unsigned wong pwot,
	unsigned wong addw __awways_unused)
{
	unsigned wong suppowted = PWOT_WEAD | PWOT_WWITE | PWOT_EXEC | PWOT_SEM;

	if (system_suppowts_bti())
		suppowted |= PWOT_BTI;

	if (system_suppowts_mte())
		suppowted |= PWOT_MTE;

	wetuwn (pwot & ~suppowted) == 0;
}
#define awch_vawidate_pwot(pwot, addw) awch_vawidate_pwot(pwot, addw)

static inwine boow awch_vawidate_fwags(unsigned wong vm_fwags)
{
	if (!system_suppowts_mte())
		wetuwn twue;

	/* onwy awwow VM_MTE if VM_MTE_AWWOWED has been set pweviouswy */
	wetuwn !(vm_fwags & VM_MTE) || (vm_fwags & VM_MTE_AWWOWED);
}
#define awch_vawidate_fwags(vm_fwags) awch_vawidate_fwags(vm_fwags)

#endif /* ! __ASM_MMAN_H__ */
