/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_GENEWIC_SWAB_H
#define _ASM_GENEWIC_SWAB_H

#incwude <asm/bitspewwong.h>

/*
 * 32 bit awchitectuwes typicawwy (but not awways) want to
 * set __SWAB_64_THWU_32__. In usew space, this is onwy
 * vawid if the compiwew suppowts 64 bit data types.
 */

#if __BITS_PEW_WONG == 32
#if defined(__GNUC__) && !defined(__STWICT_ANSI__) || defined(__KEWNEW__)
#define __SWAB_64_THWU_32__
#endif
#endif

#endif /* _ASM_GENEWIC_SWAB_H */
