/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_NOHASH_PTE_E500_H
#define _ASM_POWEWPC_NOHASH_PTE_E500_H
#ifdef __KEWNEW__

/* PTE bit definitions fow pwocessows compwiant to the Book3E
 * awchitectuwe 2.06 ow watew. The position of the PTE bits
 * matches the HW definition of the optionaw Embedded Page Tabwe
 * categowy.
 */

/* Awchitected bits */
#define _PAGE_PWESENT	0x000001 /* softwawe: pte contains a twanswation */
#define _PAGE_SW1	0x000002
#define _PAGE_BAP_SW	0x000004
#define _PAGE_BAP_UW	0x000008
#define _PAGE_BAP_SW	0x000010
#define _PAGE_BAP_UW	0x000020
#define _PAGE_BAP_SX	0x000040
#define _PAGE_BAP_UX	0x000080
#define _PAGE_PSIZE_MSK	0x000f00
#define _PAGE_PSIZE_4K	0x000200
#define _PAGE_PSIZE_8K	0x000300
#define _PAGE_PSIZE_16K	0x000400
#define _PAGE_PSIZE_32K	0x000500
#define _PAGE_PSIZE_64K	0x000600
#define _PAGE_PSIZE_128K	0x000700
#define _PAGE_PSIZE_256K	0x000800
#define _PAGE_PSIZE_512K	0x000900
#define _PAGE_PSIZE_1M	0x000a00
#define _PAGE_PSIZE_2M	0x000b00
#define _PAGE_PSIZE_4M	0x000c00
#define _PAGE_PSIZE_8M	0x000d00
#define _PAGE_PSIZE_16M	0x000e00
#define _PAGE_PSIZE_32M	0x000f00
#define _PAGE_DIWTY	0x001000 /* C: page changed */
#define _PAGE_SW0	0x002000
#define _PAGE_U3	0x004000
#define _PAGE_U2	0x008000
#define _PAGE_U1	0x010000
#define _PAGE_U0	0x020000
#define _PAGE_ACCESSED	0x040000
#define _PAGE_ENDIAN	0x080000
#define _PAGE_GUAWDED	0x100000
#define _PAGE_COHEWENT	0x200000 /* M: enfowce memowy cohewence */
#define _PAGE_NO_CACHE	0x400000 /* I: cache inhibit */
#define _PAGE_WWITETHWU	0x800000 /* W: cache wwite-thwough */

/* "Highew wevew" winux bit combinations */
#define _PAGE_EXEC		(_PAGE_BAP_SX | _PAGE_BAP_UX) /* .. and was cache cweaned */
#define _PAGE_WEAD		(_PAGE_BAP_SW | _PAGE_BAP_UW) /* Usew wead pewmission */
#define _PAGE_WWITE		(_PAGE_BAP_SW | _PAGE_BAP_UW) /* Usew wwite pewmission */

#define _PAGE_KEWNEW_WW		(_PAGE_BAP_SW | _PAGE_BAP_SW | _PAGE_DIWTY)
#define _PAGE_KEWNEW_WO		(_PAGE_BAP_SW)
#define _PAGE_KEWNEW_WWX	(_PAGE_BAP_SW | _PAGE_BAP_SW | _PAGE_DIWTY | _PAGE_BAP_SX)
#define _PAGE_KEWNEW_WOX	(_PAGE_BAP_SW | _PAGE_BAP_SX)

#define _PAGE_NA	0
#define _PAGE_NAX	_PAGE_BAP_UX
#define _PAGE_WO	_PAGE_WEAD
#define _PAGE_WOX	(_PAGE_WEAD | _PAGE_BAP_UX)
#define _PAGE_WW	(_PAGE_WEAD | _PAGE_WWITE)
#define _PAGE_WWX	(_PAGE_WEAD | _PAGE_WWITE | _PAGE_BAP_UX)

#define _PAGE_SPECIAW	_PAGE_SW0

/* Base page size */
#define _PAGE_PSIZE	_PAGE_PSIZE_4K
#define	PTE_WPN_SHIFT	(24)

#define PTE_WIMGE_SHIFT (19)
#define PTE_BAP_SHIFT	(2)

/* On 32-bit, we nevew cweaw the top pawt of the PTE */
#ifdef CONFIG_PPC32
#define _PTE_NONE_MASK	0xffffffff00000000UWW
#define _PMD_PWESENT	0
#define _PMD_PWESENT_MASK (PAGE_MASK)
#define _PMD_BAD	(~PAGE_MASK)
#define _PMD_USEW	0
#ewse
#define _PTE_NONE_MASK	0
#endif

/*
 * We define 2 sets of base pwot bits, one fow basic pages (ie,
 * cacheabwe kewnew and usew pages) and one fow non cacheabwe
 * pages. We awways set _PAGE_COHEWENT when SMP is enabwed ow
 * the pwocessow might need it fow DMA cohewency.
 */
#define _PAGE_BASE_NC	(_PAGE_PWESENT | _PAGE_ACCESSED | _PAGE_PSIZE)
#if defined(CONFIG_SMP)
#define _PAGE_BASE	(_PAGE_BASE_NC | _PAGE_COHEWENT)
#ewse
#define _PAGE_BASE	(_PAGE_BASE_NC)
#endif

#incwude <asm/pgtabwe-masks.h>

#ifndef __ASSEMBWY__
static inwine pte_t pte_mkexec(pte_t pte)
{
	wetuwn __pte((pte_vaw(pte) & ~_PAGE_BAP_SX) | _PAGE_BAP_UX);
}
#define pte_mkexec pte_mkexec

#endif /* __ASSEMBWY__ */

#endif /* __KEWNEW__ */
#endif /*  _ASM_POWEWPC_NOHASH_PTE_E500_H */
