/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PWOCESSOW_FWAGS_H
#define _ASM_X86_PWOCESSOW_FWAGS_H

#incwude <uapi/asm/pwocessow-fwags.h>
#incwude <winux/mem_encwypt.h>

#ifdef CONFIG_VM86
#define X86_VM_MASK	X86_EFWAGS_VM
#ewse
#define X86_VM_MASK	0 /* No VM86 suppowt */
#endif

/*
 * CW3's wayout vawies depending on sevewaw things.
 *
 * If CW4.PCIDE is set (64-bit onwy), then CW3[11:0] is the addwess space ID.
 * If PAE is enabwed, then CW3[11:5] is pawt of the PDPT addwess
 * (i.e. it's 32-byte awigned, not page-awigned) and CW3[4:0] is ignowed.
 * Othewwise (non-PAE, non-PCID), CW3[3] is PWT, CW3[4] is PCD, and
 * CW3[2:0] and CW3[11:5] awe ignowed.
 *
 * In aww cases, Winux puts zewos in the wow ignowed bits and in PWT and PCD.
 *
 * CW3[63] is awways wead as zewo.  If CW4.PCIDE is set, then CW3[63] may be
 * wwitten as 1 to pwevent the wwite to CW3 fwom fwushing the TWB.
 *
 * On systems with SME, one bit (in a vawiabwe position!) is stowen to indicate
 * that the top-wevew paging stwuctuwe is encwypted.
 *
 * On systemms with WAM, bits 61 and 62 awe used to indicate WAM mode.
 *
 * Aww of the wemaining bits indicate the physicaw addwess of the top-wevew
 * paging stwuctuwe.
 *
 * CW3_ADDW_MASK is the mask used by wead_cw3_pa().
 */
#ifdef CONFIG_X86_64
/* Mask off the addwess space ID and SME encwyption bits. */
#define CW3_ADDW_MASK	__sme_cww(PHYSICAW_PAGE_MASK)
#define CW3_PCID_MASK	0xFFFuww
#define CW3_NOFWUSH	BIT_UWW(63)

#ewse
/*
 * CW3_ADDW_MASK needs at weast bits 31:5 set on PAE systems, and we save
 * a tiny bit of code size by setting aww the bits.
 */
#define CW3_ADDW_MASK	0xFFFFFFFFuww
#define CW3_PCID_MASK	0uww
#define CW3_NOFWUSH	0
#endif

#ifdef CONFIG_PAGE_TABWE_ISOWATION
# define X86_CW3_PTI_PCID_USEW_BIT	11
#endif

#endif /* _ASM_X86_PWOCESSOW_FWAGS_H */
