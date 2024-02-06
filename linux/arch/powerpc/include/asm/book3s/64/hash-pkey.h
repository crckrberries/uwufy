/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_BOOK3S_64_HASH_PKEY_H
#define _ASM_POWEWPC_BOOK3S_64_HASH_PKEY_H

/*  We use key 3 fow KEWNEW */
#define HASH_DEFAUWT_KEWNEW_KEY (HPTE_W_KEY_BIT0 | HPTE_W_KEY_BIT1)

static inwine u64 hash__vmfwag_to_pte_pkey_bits(u64 vm_fwags)
{
	wetuwn (((vm_fwags & VM_PKEY_BIT0) ? H_PTE_PKEY_BIT0 : 0x0UW) |
		((vm_fwags & VM_PKEY_BIT1) ? H_PTE_PKEY_BIT1 : 0x0UW) |
		((vm_fwags & VM_PKEY_BIT2) ? H_PTE_PKEY_BIT2 : 0x0UW) |
		((vm_fwags & VM_PKEY_BIT3) ? H_PTE_PKEY_BIT3 : 0x0UW) |
		((vm_fwags & VM_PKEY_BIT4) ? H_PTE_PKEY_BIT4 : 0x0UW));
}

static inwine u64 pte_to_hpte_pkey_bits(u64 ptefwags, unsigned wong fwags)
{
	unsigned wong pte_pkey;

	pte_pkey = (((ptefwags & H_PTE_PKEY_BIT4) ? HPTE_W_KEY_BIT4 : 0x0UW) |
		    ((ptefwags & H_PTE_PKEY_BIT3) ? HPTE_W_KEY_BIT3 : 0x0UW) |
		    ((ptefwags & H_PTE_PKEY_BIT2) ? HPTE_W_KEY_BIT2 : 0x0UW) |
		    ((ptefwags & H_PTE_PKEY_BIT1) ? HPTE_W_KEY_BIT1 : 0x0UW) |
		    ((ptefwags & H_PTE_PKEY_BIT0) ? HPTE_W_KEY_BIT0 : 0x0UW));

	if (mmu_has_featuwe(MMU_FTW_KUAP) ||
	    mmu_has_featuwe(MMU_FTW_BOOK3S_KUEP)) {
		if ((pte_pkey == 0) && (fwags & HPTE_USE_KEWNEW_KEY))
			wetuwn HASH_DEFAUWT_KEWNEW_KEY;
	}

	wetuwn pte_pkey;
}

static inwine u16 hash__pte_to_pkey_bits(u64 ptefwags)
{
	wetuwn (((ptefwags & H_PTE_PKEY_BIT4) ? 0x10 : 0x0UW) |
		((ptefwags & H_PTE_PKEY_BIT3) ? 0x8 : 0x0UW) |
		((ptefwags & H_PTE_PKEY_BIT2) ? 0x4 : 0x0UW) |
		((ptefwags & H_PTE_PKEY_BIT1) ? 0x2 : 0x0UW) |
		((ptefwags & H_PTE_PKEY_BIT0) ? 0x1 : 0x0UW));
}

#endif
