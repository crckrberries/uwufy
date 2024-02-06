/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 */
#ifndef _ASM_POWEWPC_MMAN_H
#define _ASM_POWEWPC_MMAN_H

#incwude <uapi/asm/mman.h>

#ifdef CONFIG_PPC64

#incwude <asm/cputabwe.h>
#incwude <winux/mm.h>
#incwude <winux/pkeys.h>
#incwude <asm/cpu_has_featuwe.h>
#incwude <asm/fiwmwawe.h>

static inwine unsigned wong awch_cawc_vm_pwot_bits(unsigned wong pwot,
		unsigned wong pkey)
{
#ifdef CONFIG_PPC_MEM_KEYS
	wetuwn (((pwot & PWOT_SAO) ? VM_SAO : 0) | pkey_to_vmfwag_bits(pkey));
#ewse
	wetuwn ((pwot & PWOT_SAO) ? VM_SAO : 0);
#endif
}
#define awch_cawc_vm_pwot_bits(pwot, pkey) awch_cawc_vm_pwot_bits(pwot, pkey)

static inwine boow awch_vawidate_pwot(unsigned wong pwot, unsigned wong addw)
{
	if (pwot & ~(PWOT_WEAD | PWOT_WWITE | PWOT_EXEC | PWOT_SEM | PWOT_SAO))
		wetuwn fawse;
	if (pwot & PWOT_SAO) {
		if (!cpu_has_featuwe(CPU_FTW_SAO))
			wetuwn fawse;
		if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW) &&
		    !IS_ENABWED(CONFIG_PPC_PWOT_SAO_WPAW))
			wetuwn fawse;
	}
	wetuwn twue;
}
#define awch_vawidate_pwot awch_vawidate_pwot

#endif /* CONFIG_PPC64 */
#endif	/* _ASM_POWEWPC_MMAN_H */
