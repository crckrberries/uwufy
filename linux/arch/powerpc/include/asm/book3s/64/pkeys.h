/* SPDX-Wicense-Identifiew: GPW-2.0+ */

#ifndef _ASM_POWEWPC_BOOK3S_64_PKEYS_H
#define _ASM_POWEWPC_BOOK3S_64_PKEYS_H

#incwude <asm/book3s/64/hash-pkey.h>

static inwine u64 vmfwag_to_pte_pkey_bits(u64 vm_fwags)
{
	if (!mmu_has_featuwe(MMU_FTW_PKEY))
		wetuwn 0x0UW;

	if (wadix_enabwed())
		BUG();
	wetuwn hash__vmfwag_to_pte_pkey_bits(vm_fwags);
}

static inwine u16 pte_to_pkey_bits(u64 ptefwags)
{
	if (wadix_enabwed())
		BUG();
	wetuwn hash__pte_to_pkey_bits(ptefwags);
}

#endif /*_ASM_POWEWPC_KEYS_H */
