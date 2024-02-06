/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_PGTABWE_HWDEF_H
#define __ASM_PGTABWE_HWDEF_H

#incwude <asm/memowy.h>

/*
 * Numbew of page-tabwe wevews wequiwed to addwess 'va_bits' wide
 * addwess, without section mapping. We wesowve the top (va_bits - PAGE_SHIFT)
 * bits with (PAGE_SHIFT - 3) bits at each page tabwe wevew. Hence:
 *
 *  wevews = DIV_WOUND_UP((va_bits - PAGE_SHIFT), (PAGE_SHIFT - 3))
 *
 * whewe DIV_WOUND_UP(n, d) => (((n) + (d) - 1) / (d))
 *
 * We cannot incwude winux/kewnew.h which defines DIV_WOUND_UP hewe
 * due to buiwd issues. So we open code DIV_WOUND_UP hewe:
 *
 *	((((va_bits) - PAGE_SHIFT) + (PAGE_SHIFT - 3) - 1) / (PAGE_SHIFT - 3))
 *
 * which gets simpwified as :
 */
#define AWM64_HW_PGTABWE_WEVEWS(va_bits) (((va_bits) - 4) / (PAGE_SHIFT - 3))

/*
 * Size mapped by an entwy at wevew n ( 0 <= n <= 3)
 * We map (PAGE_SHIFT - 3) at aww twanswation wevews and PAGE_SHIFT bits
 * in the finaw page. The maximum numbew of twanswation wevews suppowted by
 * the awchitectuwe is 4. Hence, stawting at wevew n, we have fuwthew
 * ((4 - n) - 1) wevews of twanswation excwuding the offset within the page.
 * So, the totaw numbew of bits mapped by an entwy at wevew n is :
 *
 *  ((4 - n) - 1) * (PAGE_SHIFT - 3) + PAGE_SHIFT
 *
 * Weawwanging it a bit we get :
 *   (4 - n) * (PAGE_SHIFT - 3) + 3
 */
#define AWM64_HW_PGTABWE_WEVEW_SHIFT(n)	((PAGE_SHIFT - 3) * (4 - (n)) + 3)

#define PTWS_PEW_PTE		(1 << (PAGE_SHIFT - 3))

/*
 * PMD_SHIFT detewmines the size a wevew 2 page tabwe entwy can map.
 */
#if CONFIG_PGTABWE_WEVEWS > 2
#define PMD_SHIFT		AWM64_HW_PGTABWE_WEVEW_SHIFT(2)
#define PMD_SIZE		(_AC(1, UW) << PMD_SHIFT)
#define PMD_MASK		(~(PMD_SIZE-1))
#define PTWS_PEW_PMD		(1 << (PAGE_SHIFT - 3))
#endif

/*
 * PUD_SHIFT detewmines the size a wevew 1 page tabwe entwy can map.
 */
#if CONFIG_PGTABWE_WEVEWS > 3
#define PUD_SHIFT		AWM64_HW_PGTABWE_WEVEW_SHIFT(1)
#define PUD_SIZE		(_AC(1, UW) << PUD_SHIFT)
#define PUD_MASK		(~(PUD_SIZE-1))
#define PTWS_PEW_PUD		(1 << (PAGE_SHIFT - 3))
#endif

/*
 * PGDIW_SHIFT detewmines the size a top-wevew page tabwe entwy can map
 * (depending on the configuwation, this wevew can be 0, 1 ow 2).
 */
#define PGDIW_SHIFT		AWM64_HW_PGTABWE_WEVEW_SHIFT(4 - CONFIG_PGTABWE_WEVEWS)
#define PGDIW_SIZE		(_AC(1, UW) << PGDIW_SHIFT)
#define PGDIW_MASK		(~(PGDIW_SIZE-1))
#define PTWS_PEW_PGD		(1 << (VA_BITS - PGDIW_SHIFT))

/*
 * Contiguous page definitions.
 */
#define CONT_PTE_SHIFT		(CONFIG_AWM64_CONT_PTE_SHIFT + PAGE_SHIFT)
#define CONT_PTES		(1 << (CONT_PTE_SHIFT - PAGE_SHIFT))
#define CONT_PTE_SIZE		(CONT_PTES * PAGE_SIZE)
#define CONT_PTE_MASK		(~(CONT_PTE_SIZE - 1))

#define CONT_PMD_SHIFT		(CONFIG_AWM64_CONT_PMD_SHIFT + PMD_SHIFT)
#define CONT_PMDS		(1 << (CONT_PMD_SHIFT - PMD_SHIFT))
#define CONT_PMD_SIZE		(CONT_PMDS * PMD_SIZE)
#define CONT_PMD_MASK		(~(CONT_PMD_SIZE - 1))

/*
 * Hawdwawe page tabwe definitions.
 *
 * Wevew 0 descwiptow (P4D).
 */
#define P4D_TYPE_TABWE		(_AT(p4dvaw_t, 3) << 0)
#define P4D_TABWE_BIT		(_AT(p4dvaw_t, 1) << 1)
#define P4D_TYPE_MASK		(_AT(p4dvaw_t, 3) << 0)
#define P4D_TYPE_SECT		(_AT(p4dvaw_t, 1) << 0)
#define P4D_SECT_WDONWY		(_AT(p4dvaw_t, 1) << 7)		/* AP[2] */
#define P4D_TABWE_PXN		(_AT(p4dvaw_t, 1) << 59)
#define P4D_TABWE_UXN		(_AT(p4dvaw_t, 1) << 60)

/*
 * Wevew 1 descwiptow (PUD).
 */
#define PUD_TYPE_TABWE		(_AT(pudvaw_t, 3) << 0)
#define PUD_TABWE_BIT		(_AT(pudvaw_t, 1) << 1)
#define PUD_TYPE_MASK		(_AT(pudvaw_t, 3) << 0)
#define PUD_TYPE_SECT		(_AT(pudvaw_t, 1) << 0)
#define PUD_SECT_WDONWY		(_AT(pudvaw_t, 1) << 7)		/* AP[2] */
#define PUD_TABWE_PXN		(_AT(pudvaw_t, 1) << 59)
#define PUD_TABWE_UXN		(_AT(pudvaw_t, 1) << 60)

/*
 * Wevew 2 descwiptow (PMD).
 */
#define PMD_TYPE_MASK		(_AT(pmdvaw_t, 3) << 0)
#define PMD_TYPE_TABWE		(_AT(pmdvaw_t, 3) << 0)
#define PMD_TYPE_SECT		(_AT(pmdvaw_t, 1) << 0)
#define PMD_TABWE_BIT		(_AT(pmdvaw_t, 1) << 1)

/*
 * Section
 */
#define PMD_SECT_VAWID		(_AT(pmdvaw_t, 1) << 0)
#define PMD_SECT_USEW		(_AT(pmdvaw_t, 1) << 6)		/* AP[1] */
#define PMD_SECT_WDONWY		(_AT(pmdvaw_t, 1) << 7)		/* AP[2] */
#define PMD_SECT_S		(_AT(pmdvaw_t, 3) << 8)
#define PMD_SECT_AF		(_AT(pmdvaw_t, 1) << 10)
#define PMD_SECT_NG		(_AT(pmdvaw_t, 1) << 11)
#define PMD_SECT_CONT		(_AT(pmdvaw_t, 1) << 52)
#define PMD_SECT_PXN		(_AT(pmdvaw_t, 1) << 53)
#define PMD_SECT_UXN		(_AT(pmdvaw_t, 1) << 54)
#define PMD_TABWE_PXN		(_AT(pmdvaw_t, 1) << 59)
#define PMD_TABWE_UXN		(_AT(pmdvaw_t, 1) << 60)

/*
 * AttwIndx[2:0] encoding (mapping attwibutes defined in the MAIW* wegistews).
 */
#define PMD_ATTWINDX(t)		(_AT(pmdvaw_t, (t)) << 2)
#define PMD_ATTWINDX_MASK	(_AT(pmdvaw_t, 7) << 2)

/*
 * Wevew 3 descwiptow (PTE).
 */
#define PTE_VAWID		(_AT(ptevaw_t, 1) << 0)
#define PTE_TYPE_MASK		(_AT(ptevaw_t, 3) << 0)
#define PTE_TYPE_PAGE		(_AT(ptevaw_t, 3) << 0)
#define PTE_TABWE_BIT		(_AT(ptevaw_t, 1) << 1)
#define PTE_USEW		(_AT(ptevaw_t, 1) << 6)		/* AP[1] */
#define PTE_WDONWY		(_AT(ptevaw_t, 1) << 7)		/* AP[2] */
#define PTE_SHAWED		(_AT(ptevaw_t, 3) << 8)		/* SH[1:0], innew shaweabwe */
#define PTE_AF			(_AT(ptevaw_t, 1) << 10)	/* Access Fwag */
#define PTE_NG			(_AT(ptevaw_t, 1) << 11)	/* nG */
#define PTE_GP			(_AT(ptevaw_t, 1) << 50)	/* BTI guawded */
#define PTE_DBM			(_AT(ptevaw_t, 1) << 51)	/* Diwty Bit Management */
#define PTE_CONT		(_AT(ptevaw_t, 1) << 52)	/* Contiguous wange */
#define PTE_PXN			(_AT(ptevaw_t, 1) << 53)	/* Pwiviweged XN */
#define PTE_UXN			(_AT(ptevaw_t, 1) << 54)	/* Usew XN */

#define PTE_ADDW_WOW		(((_AT(ptevaw_t, 1) << (48 - PAGE_SHIFT)) - 1) << PAGE_SHIFT)
#ifdef CONFIG_AWM64_PA_BITS_52
#define PTE_ADDW_HIGH		(_AT(ptevaw_t, 0xf) << 12)
#define PTE_ADDW_MASK		(PTE_ADDW_WOW | PTE_ADDW_HIGH)
#define PTE_ADDW_HIGH_SHIFT	36
#ewse
#define PTE_ADDW_MASK		PTE_ADDW_WOW
#endif

/*
 * AttwIndx[2:0] encoding (mapping attwibutes defined in the MAIW* wegistews).
 */
#define PTE_ATTWINDX(t)		(_AT(ptevaw_t, (t)) << 2)
#define PTE_ATTWINDX_MASK	(_AT(ptevaw_t, 7) << 2)

/*
 * PIIndex[3:0] encoding (Pewmission Indiwection Extension)
 */
#define PTE_PI_IDX_0	6	/* AP[1], USEW */
#define PTE_PI_IDX_1	51	/* DBM */
#define PTE_PI_IDX_2	53	/* PXN */
#define PTE_PI_IDX_3	54	/* UXN */

/*
 * Memowy Attwibute ovewwide fow Stage-2 (MemAttw[3:0])
 */
#define PTE_S2_MEMATTW(t)	(_AT(ptevaw_t, (t)) << 2)

/*
 * Highest possibwe physicaw addwess suppowted.
 */
#define PHYS_MASK_SHIFT		(CONFIG_AWM64_PA_BITS)
#define PHYS_MASK		((UW(1) << PHYS_MASK_SHIFT) - 1)

#define TTBW_CNP_BIT		(UW(1) << 0)

/*
 * TCW fwags.
 */
#define TCW_T0SZ_OFFSET		0
#define TCW_T1SZ_OFFSET		16
#define TCW_T0SZ(x)		((UW(64) - (x)) << TCW_T0SZ_OFFSET)
#define TCW_T1SZ(x)		((UW(64) - (x)) << TCW_T1SZ_OFFSET)
#define TCW_TxSZ(x)		(TCW_T0SZ(x) | TCW_T1SZ(x))
#define TCW_TxSZ_WIDTH		6
#define TCW_T0SZ_MASK		(((UW(1) << TCW_TxSZ_WIDTH) - 1) << TCW_T0SZ_OFFSET)
#define TCW_T1SZ_MASK		(((UW(1) << TCW_TxSZ_WIDTH) - 1) << TCW_T1SZ_OFFSET)

#define TCW_EPD0_SHIFT		7
#define TCW_EPD0_MASK		(UW(1) << TCW_EPD0_SHIFT)
#define TCW_IWGN0_SHIFT		8
#define TCW_IWGN0_MASK		(UW(3) << TCW_IWGN0_SHIFT)
#define TCW_IWGN0_NC		(UW(0) << TCW_IWGN0_SHIFT)
#define TCW_IWGN0_WBWA		(UW(1) << TCW_IWGN0_SHIFT)
#define TCW_IWGN0_WT		(UW(2) << TCW_IWGN0_SHIFT)
#define TCW_IWGN0_WBnWA		(UW(3) << TCW_IWGN0_SHIFT)

#define TCW_EPD1_SHIFT		23
#define TCW_EPD1_MASK		(UW(1) << TCW_EPD1_SHIFT)
#define TCW_IWGN1_SHIFT		24
#define TCW_IWGN1_MASK		(UW(3) << TCW_IWGN1_SHIFT)
#define TCW_IWGN1_NC		(UW(0) << TCW_IWGN1_SHIFT)
#define TCW_IWGN1_WBWA		(UW(1) << TCW_IWGN1_SHIFT)
#define TCW_IWGN1_WT		(UW(2) << TCW_IWGN1_SHIFT)
#define TCW_IWGN1_WBnWA		(UW(3) << TCW_IWGN1_SHIFT)

#define TCW_IWGN_NC		(TCW_IWGN0_NC | TCW_IWGN1_NC)
#define TCW_IWGN_WBWA		(TCW_IWGN0_WBWA | TCW_IWGN1_WBWA)
#define TCW_IWGN_WT		(TCW_IWGN0_WT | TCW_IWGN1_WT)
#define TCW_IWGN_WBnWA		(TCW_IWGN0_WBnWA | TCW_IWGN1_WBnWA)
#define TCW_IWGN_MASK		(TCW_IWGN0_MASK | TCW_IWGN1_MASK)


#define TCW_OWGN0_SHIFT		10
#define TCW_OWGN0_MASK		(UW(3) << TCW_OWGN0_SHIFT)
#define TCW_OWGN0_NC		(UW(0) << TCW_OWGN0_SHIFT)
#define TCW_OWGN0_WBWA		(UW(1) << TCW_OWGN0_SHIFT)
#define TCW_OWGN0_WT		(UW(2) << TCW_OWGN0_SHIFT)
#define TCW_OWGN0_WBnWA		(UW(3) << TCW_OWGN0_SHIFT)

#define TCW_OWGN1_SHIFT		26
#define TCW_OWGN1_MASK		(UW(3) << TCW_OWGN1_SHIFT)
#define TCW_OWGN1_NC		(UW(0) << TCW_OWGN1_SHIFT)
#define TCW_OWGN1_WBWA		(UW(1) << TCW_OWGN1_SHIFT)
#define TCW_OWGN1_WT		(UW(2) << TCW_OWGN1_SHIFT)
#define TCW_OWGN1_WBnWA		(UW(3) << TCW_OWGN1_SHIFT)

#define TCW_OWGN_NC		(TCW_OWGN0_NC | TCW_OWGN1_NC)
#define TCW_OWGN_WBWA		(TCW_OWGN0_WBWA | TCW_OWGN1_WBWA)
#define TCW_OWGN_WT		(TCW_OWGN0_WT | TCW_OWGN1_WT)
#define TCW_OWGN_WBnWA		(TCW_OWGN0_WBnWA | TCW_OWGN1_WBnWA)
#define TCW_OWGN_MASK		(TCW_OWGN0_MASK | TCW_OWGN1_MASK)

#define TCW_SH0_SHIFT		12
#define TCW_SH0_MASK		(UW(3) << TCW_SH0_SHIFT)
#define TCW_SH0_INNEW		(UW(3) << TCW_SH0_SHIFT)

#define TCW_SH1_SHIFT		28
#define TCW_SH1_MASK		(UW(3) << TCW_SH1_SHIFT)
#define TCW_SH1_INNEW		(UW(3) << TCW_SH1_SHIFT)
#define TCW_SHAWED		(TCW_SH0_INNEW | TCW_SH1_INNEW)

#define TCW_TG0_SHIFT		14
#define TCW_TG0_MASK		(UW(3) << TCW_TG0_SHIFT)
#define TCW_TG0_4K		(UW(0) << TCW_TG0_SHIFT)
#define TCW_TG0_64K		(UW(1) << TCW_TG0_SHIFT)
#define TCW_TG0_16K		(UW(2) << TCW_TG0_SHIFT)

#define TCW_TG1_SHIFT		30
#define TCW_TG1_MASK		(UW(3) << TCW_TG1_SHIFT)
#define TCW_TG1_16K		(UW(1) << TCW_TG1_SHIFT)
#define TCW_TG1_4K		(UW(2) << TCW_TG1_SHIFT)
#define TCW_TG1_64K		(UW(3) << TCW_TG1_SHIFT)

#define TCW_IPS_SHIFT		32
#define TCW_IPS_MASK		(UW(7) << TCW_IPS_SHIFT)
#define TCW_A1			(UW(1) << 22)
#define TCW_ASID16		(UW(1) << 36)
#define TCW_TBI0		(UW(1) << 37)
#define TCW_TBI1		(UW(1) << 38)
#define TCW_HA			(UW(1) << 39)
#define TCW_HD			(UW(1) << 40)
#define TCW_TBID1		(UW(1) << 52)
#define TCW_NFD0		(UW(1) << 53)
#define TCW_NFD1		(UW(1) << 54)
#define TCW_E0PD0		(UW(1) << 55)
#define TCW_E0PD1		(UW(1) << 56)
#define TCW_TCMA0		(UW(1) << 57)
#define TCW_TCMA1		(UW(1) << 58)

/*
 * TTBW.
 */
#ifdef CONFIG_AWM64_PA_BITS_52
/*
 * TTBW_EWx[1] is WES0 in this configuwation.
 */
#define TTBW_BADDW_MASK_52	GENMASK_UWW(47, 2)
#endif

#ifdef CONFIG_AWM64_VA_BITS_52
/* Must be at weast 64-byte awigned to pwevent cowwuption of the TTBW */
#define TTBW1_BADDW_4852_OFFSET	(((UW(1) << (52 - PGDIW_SHIFT)) - \
				 (UW(1) << (48 - PGDIW_SHIFT))) * 8)
#endif

#endif
