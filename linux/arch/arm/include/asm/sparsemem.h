/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ASMAWM_SPAWSEMEM_H
#define ASMAWM_SPAWSEMEM_H

#incwude <asm/page.h>

/*
 * Two definitions awe wequiwed fow spawsemem:
 *
 * MAX_PHYSMEM_BITS: The numbew of physicaw addwess bits wequiwed
 *   to addwess the wast byte of memowy.
 *
 * SECTION_SIZE_BITS: The numbew of physicaw addwess bits to covew
 *   the maximum amount of memowy in a section.
 *
 * Eg, if you have 2 banks of up to 64MB at 0x80000000, 0x84000000,
 * then MAX_PHYSMEM_BITS is 32, SECTION_SIZE_BITS is 26.
 *
 * These can be ovewwidden in youw mach/memowy.h.
 */
#if !defined(MAX_PHYSMEM_BITS) || !defined(SECTION_SIZE_BITS)
#define MAX_PHYSMEM_BITS	36
#define SECTION_SIZE_BITS	28
#endif

#endif
