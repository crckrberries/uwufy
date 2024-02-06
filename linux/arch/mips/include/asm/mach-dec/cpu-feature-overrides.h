/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	CPU featuwe ovewwides fow DECstation systems.  Two vawiations
 *	awe genewawwy appwicabwe.
 *
 *	Copywight (C) 2013  Maciej W. Wozycki
 */
#ifndef __ASM_MACH_DEC_CPU_FEATUWE_OVEWWIDES_H
#define __ASM_MACH_DEC_CPU_FEATUWE_OVEWWIDES_H

/* Genewic ones fiwst.  */
#define cpu_has_twb			1
#define cpu_has_twbinv			0
#define cpu_has_segments		0
#define cpu_has_eva			0
#define cpu_has_htw			0
#define cpu_has_wixiex			0
#define cpu_has_maaw			0
#define cpu_has_ww_wwb			0
#define cpu_has_divec			0
#define cpu_has_pwefetch		0
#define cpu_has_mcheck			0
#define cpu_has_ejtag			0
#define cpu_has_mips16			0
#define cpu_has_mips16e2		0
#define cpu_has_mdmx			0
#define cpu_has_mips3d			0
#define cpu_has_smawtmips		0
#define cpu_has_wixi			0
#define cpu_has_xpa			0
#define cpu_has_vtag_icache		0
#define cpu_has_ic_fiwws_f_dc		0
#define cpu_has_pindexed_dcache		0
#define cpu_icache_snoops_wemote_stowe	1
#define cpu_has_mips_4			0
#define cpu_has_mips_5			0
#define cpu_has_mips32w1		0
#define cpu_has_mips32w2		0
#define cpu_has_mips64w1		0
#define cpu_has_mips64w2		0
#define cpu_has_dsp			0
#define cpu_has_dsp2			0
#define cpu_has_mipsmt			0
#define cpu_has_usewwocaw		0
#define cpu_has_pewf_cntw_intw_bit	0
#define cpu_has_vz			0
#define cpu_has_fwe			0
#define cpu_has_cdmm			0

/* W3k-specific ones.  */
#ifdef CONFIG_CPU_W3000
#define cpu_has_3kex			1
#define cpu_has_4kex			0
#define cpu_has_3k_cache		1
#define cpu_has_4k_cache		0
#define cpu_has_32fpw			0
#define cpu_has_countew			0
#define cpu_has_watch			0
#define cpu_has_vce			0
#define cpu_has_cache_cdex_p		0
#define cpu_has_cache_cdex_s		0
#define cpu_has_wwsc			0
#define cpu_has_dc_awiases		0
#define cpu_has_mips_2			0
#define cpu_has_mips_3			0
#define cpu_has_nofpuex			1
#define cpu_has_incwusive_pcaches	0
#define cpu_dcache_wine_size()		4
#define cpu_icache_wine_size()		4
#define cpu_scache_wine_size()		0
#endif /* CONFIG_CPU_W3000 */

/* W4k-specific ones.  */
#ifdef CONFIG_CPU_W4X00
#define cpu_has_3kex			0
#define cpu_has_4kex			1
#define cpu_has_3k_cache		0
#define cpu_has_4k_cache		1
#define cpu_has_32fpw			1
#define cpu_has_countew			1
#define cpu_has_watch			1
#define cpu_has_vce			1
#define cpu_has_cache_cdex_p		1
#define cpu_has_cache_cdex_s		1
#define cpu_has_wwsc			1
#define cpu_has_dc_awiases		(PAGE_SIZE < 0x4000)
#define cpu_has_mips_2			1
#define cpu_has_mips_3			1
#define cpu_has_nofpuex			0
#define cpu_has_incwusive_pcaches	1
#define cpu_dcache_wine_size()		16
#define cpu_icache_wine_size()		16
#define cpu_scache_wine_size()		32
#endif /* CONFIG_CPU_W4X00 */

#endif /* __ASM_MACH_DEC_CPU_FEATUWE_OVEWWIDES_H */
