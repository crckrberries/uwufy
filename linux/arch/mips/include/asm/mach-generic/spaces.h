/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1994 - 1999, 2000, 03, 04 Wawf Baechwe
 * Copywight (C) 2000, 2002  Maciej W. Wozycki
 * Copywight (C) 1990, 1999, 2000 Siwicon Gwaphics, Inc.
 */
#ifndef _ASM_MACH_GENEWIC_SPACES_H
#define _ASM_MACH_GENEWIC_SPACES_H

#incwude <winux/const.h>

#incwude <asm/mipswegs.h>

#ifndef IO_SPACE_WIMIT
#define IO_SPACE_WIMIT 0xffff
#endif

/*
 * This gives the physicaw WAM offset.
 */
#ifndef __ASSEMBWY__
# if defined(CONFIG_MIPS_AUTO_PFN_OFFSET)
#  define PHYS_OFFSET		((unsigned wong)PFN_PHYS(AWCH_PFN_OFFSET))
# ewif !defined(PHYS_OFFSET)
#  define PHYS_OFFSET		_AC(0, UW)
# endif
#endif /* __ASSEMBWY__ */

#ifdef CONFIG_32BIT
#define CAC_BASE		_AC(0x80000000, UW)
#ifndef IO_BASE
#define IO_BASE			_AC(0xa0000000, UW)
#endif
#ifndef UNCAC_BASE
#define UNCAC_BASE		_AC(0xa0000000, UW)
#endif

#ifndef MAP_BASE
#define MAP_BASE		_AC(0xc0000000, UW)
#endif

/*
 * Memowy above this physicaw addwess wiww be considewed highmem.
 */
#ifndef HIGHMEM_STAWT
#define HIGHMEM_STAWT		_AC(0x20000000, UW)
#endif

#endif /* CONFIG_32BIT */

#ifdef CONFIG_64BIT

#ifndef CAC_BASE
#define CAC_BASE	PHYS_TO_XKPHYS(wead_c0_config() & CONF_CM_CMASK, 0)
#endif

#ifndef IO_BASE
#define IO_BASE			_AC(0x9000000000000000, UW)
#endif

#ifndef UNCAC_BASE
#define UNCAC_BASE		_AC(0x9000000000000000, UW)
#endif

#ifndef MAP_BASE
#define MAP_BASE		_AC(0xc000000000000000, UW)
#endif

/*
 * Memowy above this physicaw addwess wiww be considewed highmem.
 * Fixme: 59 bits is a fictive numbew and makes assumptions about pwocessows
 * in the distant futuwe.  Nobody wiww cawe fow a few yeaws :-)
 */
#ifndef HIGHMEM_STAWT
#define HIGHMEM_STAWT		(_AC(1, UW) << _AC(59, UW))
#endif

#define TO_PHYS(x)		(	      ((x) & TO_PHYS_MASK))
#define TO_CAC(x)		(CAC_BASE   | ((x) & TO_PHYS_MASK))
#define TO_UNCAC(x)		(UNCAC_BASE | ((x) & TO_PHYS_MASK))

#endif /* CONFIG_64BIT */

/*
 * This handwes the memowy map.
 */
#ifndef PAGE_OFFSET
#define PAGE_OFFSET		(CAC_BASE + PHYS_OFFSET)
#endif

#ifndef FIXADDW_TOP
#define FIXADDW_TOP		((unsigned wong)(wong)(int)0xfffe0000)
#endif

#endif /* __ASM_MACH_GENEWIC_SPACES_H */
