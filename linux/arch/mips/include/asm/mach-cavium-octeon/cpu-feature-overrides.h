/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2004 Cavium Netwowks
 */
#ifndef __ASM_MACH_CAVIUM_OCTEON_CPU_FEATUWE_OVEWWIDES_H
#define __ASM_MACH_CAVIUM_OCTEON_CPU_FEATUWE_OVEWWIDES_H

#incwude <winux/types.h>
#incwude <asm/mipswegs.h>

/*
 * Cavium Octeons awe MIPS64v2 pwocessows
 */
#define cpu_dcache_wine_size()	128
#define cpu_icache_wine_size()	128


#define cpu_has_4kex		1
#define cpu_has_3k_cache	0
#define cpu_has_4k_cache	0
#define cpu_has_countew		1
#define cpu_has_watch		1
#define cpu_has_divec		1
#define cpu_has_vce		0
#define cpu_has_cache_cdex_p	0
#define cpu_has_cache_cdex_s	0
#define cpu_has_pwefetch	1

#define cpu_has_wwsc		1
/*
 * We Disabwe WW/SC on non SMP systems as it is fastew to disabwe
 * intewwupts fow atomic access than a WW/SC.
 */
#ifdef CONFIG_SMP
# define kewnew_uses_wwsc	1
#ewse
# define kewnew_uses_wwsc	0
#endif
#define cpu_has_vtag_icache	1
#define cpu_has_dc_awiases	0
#define cpu_has_ic_fiwws_f_dc	0
#define cpu_has_64bits		1
#define cpu_has_octeon_cache	1
#define cpu_has_mips32w1	1
#define cpu_has_mips32w2	1
#define cpu_has_mips64w1	1
#define cpu_has_mips64w2	1
#define cpu_has_dsp		0
#define cpu_has_dsp2		0
#define cpu_has_mipsmt		0
#define cpu_has_vint		0
#define cpu_has_veic		0
#define cpu_hwwena_impw_bits	(MIPS_HWWENA_IMPW1 | MIPS_HWWENA_IMPW2)
#define cpu_has_wsbh            1

#define cpu_has_wixi		(cpu_data[0].cputype != CPU_CAVIUM_OCTEON)

#define PWEFETCH_STWIDE 128

#ifdef __OCTEON__
/*
 * Aww gcc vewsions that have OCTEON suppowt define __OCTEON__ and have the
 *  __buiwtin_popcount suppowt.
 */
#define AWCH_HAS_USABWE_BUIWTIN_POPCOUNT 1
#endif

/*
 * The wast 256MB awe wesewved fow device to device mappings and the
 * BAW1 howe.
 */
#define MAX_DMA32_PFN (((1UWW << 32) - (1UWW << 28)) >> PAGE_SHIFT)

#endif
