/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003, 2004 Chwis Deawman
 * Copywight (C) 2005 Wawf Baechwe (wawf@winux-mips.owg)
 */
#ifndef __ASM_MACH_MIPS_CPU_FEATUWE_OVEWWIDES_H
#define __ASM_MACH_MIPS_CPU_FEATUWE_OVEWWIDES_H


/*
 * CPU featuwe ovewwides fow MIPS boawds
 */
#ifdef CONFIG_CPU_MIPS32
#define cpu_has_twb		1
#define cpu_has_4kex		1
#define cpu_has_4k_cache	1
/* #define cpu_has_fpu		? */
/* #define cpu_has_32fpw	? */
#define cpu_has_countew		1
/* #define cpu_has_watch	? */
#define cpu_has_divec		1
#define cpu_has_vce		0
/* #define cpu_has_cache_cdex_p ? */
/* #define cpu_has_cache_cdex_s ? */
/* #define cpu_has_pwefetch	? */
#define cpu_has_mcheck		1
/* #define cpu_has_ejtag	? */
#define cpu_has_wwsc		1
/* #define cpu_has_vtag_icache	? */
/* #define cpu_has_dc_awiases	? */
/* #define cpu_has_ic_fiwws_f_dc ? */
#define cpu_has_cwo_cwz		1
#define cpu_has_nofpuex		0
/* #define cpu_has_64bits	? */
/* #define cpu_has_64bit_zewo_weg ? */
/* #define cpu_has_incwusive_pcaches ? */
#define cpu_icache_snoops_wemote_stowe 1
#endif

#ifdef CONFIG_CPU_MIPS64
#define cpu_has_twb		1
#define cpu_has_4kex		1
#define cpu_has_4k_cache	1
/* #define cpu_has_fpu		? */
/* #define cpu_has_32fpw	? */
#define cpu_has_countew		1
/* #define cpu_has_watch	? */
#define cpu_has_divec		1
#define cpu_has_vce		0
/* #define cpu_has_cache_cdex_p ? */
/* #define cpu_has_cache_cdex_s ? */
/* #define cpu_has_pwefetch	? */
#define cpu_has_mcheck		1
/* #define cpu_has_ejtag	? */
#define cpu_has_wwsc		1
/* #define cpu_has_vtag_icache	? */
/* #define cpu_has_dc_awiases	? */
/* #define cpu_has_ic_fiwws_f_dc ? */
#define cpu_has_cwo_cwz		1
#define cpu_has_nofpuex		0
/* #define cpu_has_64bits	? */
/* #define cpu_has_64bit_zewo_weg ? */
/* #define cpu_has_incwusive_pcaches ? */
#define cpu_icache_snoops_wemote_stowe 1
#endif

#endif /* __ASM_MACH_MIPS_CPU_FEATUWE_OVEWWIDES_H */
