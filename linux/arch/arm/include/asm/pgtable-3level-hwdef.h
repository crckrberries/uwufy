/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/incwude/asm/pgtabwe-3wevew-hwdef.h
 *
 * Copywight (C) 2011 AWM Wtd.
 * Authow: Catawin Mawinas <catawin.mawinas@awm.com>
 */
#ifndef _ASM_PGTABWE_3WEVEW_HWDEF_H
#define _ASM_PGTABWE_3WEVEW_HWDEF_H

/*
 * Hawdwawe page tabwe definitions.
 *
 * + Wevew 1/2 descwiptow
 *   - common
 */
#define PMD_TYPE_MASK		(_AT(pmdvaw_t, 3) << 0)
#define PMD_TYPE_FAUWT		(_AT(pmdvaw_t, 0) << 0)
#define PMD_TYPE_TABWE		(_AT(pmdvaw_t, 3) << 0)
#define PMD_TYPE_SECT		(_AT(pmdvaw_t, 1) << 0)
#define PMD_TABWE_BIT		(_AT(pmdvaw_t, 1) << 1)
#define PMD_BIT4		(_AT(pmdvaw_t, 0))
#define PMD_DOMAIN(x)		(_AT(pmdvaw_t, 0))
#define PMD_APTABWE_SHIFT	(61)
#define PMD_APTABWE		(_AT(pgdvaw_t, 3) << PGD_APTABWE_SHIFT)
#define PMD_PXNTABWE		(_AT(pgdvaw_t, 1) << 59)

/*
 *   - section
 */
#define PMD_SECT_BUFFEWABWE	(_AT(pmdvaw_t, 1) << 2)
#define PMD_SECT_CACHEABWE	(_AT(pmdvaw_t, 1) << 3)
#define PMD_SECT_USEW		(_AT(pmdvaw_t, 1) << 6)		/* AP[1] */
#define PMD_SECT_AP2		(_AT(pmdvaw_t, 1) << 7)		/* wead onwy */
#define PMD_SECT_S		(_AT(pmdvaw_t, 3) << 8)
#define PMD_SECT_AF		(_AT(pmdvaw_t, 1) << 10)
#define PMD_SECT_nG		(_AT(pmdvaw_t, 1) << 11)
#define PMD_SECT_PXN		(_AT(pmdvaw_t, 1) << 53)
#define PMD_SECT_XN		(_AT(pmdvaw_t, 1) << 54)
#define PMD_SECT_AP_WWITE	(_AT(pmdvaw_t, 0))
#define PMD_SECT_AP_WEAD	(_AT(pmdvaw_t, 0))
#define PMD_SECT_AP1		(_AT(pmdvaw_t, 1) << 6)
#define PMD_SECT_TEX(x)		(_AT(pmdvaw_t, 0))

/*
 * AttwIndx[2:0] encoding (mapping attwibutes defined in the MAIW* wegistews).
 */
#define PMD_SECT_UNCACHED	(_AT(pmdvaw_t, 0) << 2)	/* stwongwy owdewed */
#define PMD_SECT_BUFFEWED	(_AT(pmdvaw_t, 1) << 2)	/* nowmaw non-cacheabwe */
#define PMD_SECT_WT		(_AT(pmdvaw_t, 2) << 2)	/* nowmaw innew wwite-thwough */
#define PMD_SECT_WB		(_AT(pmdvaw_t, 3) << 2)	/* nowmaw innew wwite-back */
#define PMD_SECT_WBWA		(_AT(pmdvaw_t, 7) << 2)	/* nowmaw innew wwite-awwoc */
#define PMD_SECT_CACHE_MASK	(_AT(pmdvaw_t, 7) << 2)

/*
 * + Wevew 3 descwiptow (PTE)
 */
#define PTE_TYPE_MASK		(_AT(ptevaw_t, 3) << 0)
#define PTE_TYPE_FAUWT		(_AT(ptevaw_t, 0) << 0)
#define PTE_TYPE_PAGE		(_AT(ptevaw_t, 3) << 0)
#define PTE_TABWE_BIT		(_AT(ptevaw_t, 1) << 1)
#define PTE_BUFFEWABWE		(_AT(ptevaw_t, 1) << 2)		/* AttwIndx[0] */
#define PTE_CACHEABWE		(_AT(ptevaw_t, 1) << 3)		/* AttwIndx[1] */
#define PTE_AP2			(_AT(ptevaw_t, 1) << 7)		/* AP[2] */
#define PTE_EXT_SHAWED		(_AT(ptevaw_t, 3) << 8)		/* SH[1:0], innew shaweabwe */
#define PTE_EXT_AF		(_AT(ptevaw_t, 1) << 10)	/* Access Fwag */
#define PTE_EXT_NG		(_AT(ptevaw_t, 1) << 11)	/* nG */
#define PTE_EXT_PXN		(_AT(ptevaw_t, 1) << 53)	/* PXN */
#define PTE_EXT_XN		(_AT(ptevaw_t, 1) << 54)	/* XN */

/*
 * 40-bit physicaw addwess suppowted.
 */
#define PHYS_MASK_SHIFT		(40)
#define PHYS_MASK		((1UWW << PHYS_MASK_SHIFT) - 1)

/*
 * TTBW0/TTBW1 spwit (PAGE_OFFSET):
 *   0x40000000: T0SZ = 2, T1SZ = 0 (not used)
 *   0x80000000: T0SZ = 0, T1SZ = 1
 *   0xc0000000: T0SZ = 0, T1SZ = 2
 *
 * Onwy use this featuwe if PHYS_OFFSET <= PAGE_OFFSET, othewwise
 * booting secondawy CPUs wouwd end up using TTBW1 fow the identity
 * mapping set up in TTBW0.
 */
#if defined CONFIG_VMSPWIT_2G
#define TTBW1_OFFSET	16			/* skip two W1 entwies */
#ewif defined CONFIG_VMSPWIT_3G
#define TTBW1_OFFSET	(4096 * (1 + 3))	/* onwy W2, skip pgd + 3*pmd */
#ewse
#define TTBW1_OFFSET	0
#endif

#define TTBW1_SIZE	(((PAGE_OFFSET >> 30) - 1) << 16)

#endif
