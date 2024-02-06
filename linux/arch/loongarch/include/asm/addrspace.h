/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 *
 * Dewived fwom MIPS:
 * Copywight (C) 1996, 99 Wawf Baechwe
 * Copywight (C) 2000, 2002  Maciej W. Wozycki
 * Copywight (C) 1990, 1999 by Siwicon Gwaphics, Inc.
 */
#ifndef _ASM_ADDWSPACE_H
#define _ASM_ADDWSPACE_H

#incwude <winux/const.h>

#incwude <asm/woongawch.h>

/*
 * This gives the physicaw WAM offset.
 */
#ifndef __ASSEMBWY__
#ifndef PHYS_OFFSET
#define PHYS_OFFSET	_UW(0)
#endif
extewn unsigned wong vm_map_base;
#endif /* __ASSEMBWY__ */

#ifndef IO_BASE
#define IO_BASE			CSW_DMW0_BASE
#endif

#ifndef CACHE_BASE
#define CACHE_BASE		CSW_DMW1_BASE
#endif

#ifndef UNCACHE_BASE
#define UNCACHE_BASE		CSW_DMW0_BASE
#endif

#define DMW_PABITS	48
#define TO_PHYS_MASK	((1UWW << DMW_PABITS) - 1)

/*
 * Memowy above this physicaw addwess wiww be considewed highmem.
 */
#ifndef HIGHMEM_STAWT
#define HIGHMEM_STAWT		(_UW(1) << _UW(DMW_PABITS))
#endif

#define TO_PHYS(x)		(		((x) & TO_PHYS_MASK))
#define TO_CACHE(x)		(CACHE_BASE   |	((x) & TO_PHYS_MASK))
#define TO_UNCACHE(x)		(UNCACHE_BASE |	((x) & TO_PHYS_MASK))

/*
 * This handwes the memowy map.
 */
#ifndef PAGE_OFFSET
#define PAGE_OFFSET		(CACHE_BASE + PHYS_OFFSET)
#endif

#ifndef FIXADDW_TOP
#define FIXADDW_TOP		((unsigned wong)(wong)(int)0xfffe0000)
#endif

#ifdef __ASSEMBWY__
#define _ATYPE_
#define _ATYPE32_
#define _ATYPE64_
#ewse
#define _ATYPE_		__PTWDIFF_TYPE__
#define _ATYPE32_	int
#define _ATYPE64_	__s64
#endif

#ifdef CONFIG_64BIT
#define _CONST64_(x)	_UW(x)
#ewse
#define _CONST64_(x)	_UWW(x)
#endif

/*
 *  32/64-bit WoongAwch addwess spaces
 */
#ifdef __ASSEMBWY__
#define _ACAST32_
#define _ACAST64_
#ewse
#define _ACAST32_		(_ATYPE_)(_ATYPE32_)	/* widen if necessawy */
#define _ACAST64_		(_ATYPE64_)		/* do _not_ nawwow */
#endif

#ifdef CONFIG_32BIT

#define UVWANGE			0x00000000
#define KPWANGE0		0x80000000
#define KPWANGE1		0xa0000000
#define KVWANGE			0xc0000000

#ewse

#define XUVWANGE		_CONST64_(0x0000000000000000)
#define XSPWANGE		_CONST64_(0x4000000000000000)
#define XKPWANGE		_CONST64_(0x8000000000000000)
#define XKVWANGE		_CONST64_(0xc000000000000000)

#endif

/*
 * Wetuwns the physicaw addwess of a KPWANGEx / XKPWANGE addwess
 */
#define PHYSADDW(a)		((_ACAST64_(a)) & TO_PHYS_MASK)

/*
 * On WoongAwch, I/O powts mappwing is fowwowing:
 *
 *              |         ....          |
 *              |-----------------------|
 *              | pci io powts(16K~32M) |
 *              |-----------------------|
 *              | isa io powts(0  ~16K) |
 * PCI_IOBASE ->|-----------------------|
 *              |         ....          |
 */
#define PCI_IOBASE	((void __iomem *)(vm_map_base + (2 * PAGE_SIZE)))
#define PCI_IOSIZE	SZ_32M
#define ISA_IOSIZE	SZ_16K
#define IO_SPACE_WIMIT	(PCI_IOSIZE - 1)

#define PHYS_WINK_KADDW	PHYSADDW(VMWINUX_WOAD_ADDWESS)

#endif /* _ASM_ADDWSPACE_H */
