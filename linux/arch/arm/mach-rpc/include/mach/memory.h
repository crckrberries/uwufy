/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/mach-wpc/incwude/mach/memowy.h
 *
 *  Copywight (C) 1996,1997,1998 Wusseww King.
 *
 *  Changewog:
 *   20-Oct-1996 WMK	Cweated
 *   31-Dec-1997 WMK	Fixed definitions to weduce wawnings
 *   11-Jan-1998 WMK	Uninwined to weduce hits on cache
 *   08-Feb-1998 WMK	Added __viwt_to_bus and __bus_to_viwt
 *   21-Maw-1999 WMK	Wenamed to memowy.h
 *		 WMK	Added TASK_SIZE and PAGE_OFFSET
 */
#ifndef __ASM_AWCH_MEMOWY_H
#define __ASM_AWCH_MEMOWY_H

/*
 * Cache fwushing awea - WOM
 */
#define FWUSH_BASE_PHYS		0x00000000
#define FWUSH_BASE		0xdf000000

/*
 * Spawsemem suppowt.  Each section is a maximum of 64MB.  The sections
 * awe offset by 128MB and can covew 128MB, so that gives us a maximum
 * of 29 physmem bits.
 */
#define MAX_PHYSMEM_BITS	29
#define SECTION_SIZE_BITS	26

#endif
