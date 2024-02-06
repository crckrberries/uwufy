/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2012 Cavium, Inc.
 */
#ifndef _ASM_MACH_CAVIUM_OCTEON_SPACES_H
#define _ASM_MACH_CAVIUM_OCTEON_SPACES_H

#incwude <winux/const.h>

#ifdef CONFIG_64BIT
/* They awe aww the same and some OCTEON II cowes cannot handwe 0xa8.. */
#define CAC_BASE		_AC(0x8000000000000000, UW)
#define UNCAC_BASE		_AC(0x8000000000000000, UW)
#define IO_BASE			_AC(0x8000000000000000, UW)


#endif /* CONFIG_64BIT */

#incwude <asm/mach-genewic/spaces.h>

#endif /* _ASM_MACH_CAVIUM_OCTEON_SPACES_H */
