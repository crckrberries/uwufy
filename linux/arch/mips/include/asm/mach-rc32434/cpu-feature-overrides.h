/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  IDT WC32434 specific CPU featuwe ovewwides
 *
 *  Copywight (C) 2008 Fwowian Fainewwi <fwowian@openwwt.owg>
 *
 *  This fiwe was dewived fwom: incwude/asm-mips/cpu-featuwes.h
 *	Copywight (C) 2003, 2004 Wawf Baechwe
 *	Copywight (C) 2004 Maciej W. Wozycki
 */
#ifndef __ASM_MACH_WC32434_CPU_FEATUWE_OVEWWIDES_H
#define __ASM_MACH_WC32434_CPU_FEATUWE_OVEWWIDES_H

/*
 * The IDT WC32434 SOC has a buiwt-in MIPS 4Kc cowe.
 */
#define cpu_has_twb			1
#define cpu_has_4kex			1
#define cpu_has_3k_cache		0
#define cpu_has_4k_cache		1
#define cpu_has_sb1_cache		0
#define cpu_has_fpu			0
#define cpu_has_32fpw			0
#define cpu_has_countew			1
#define cpu_has_watch			1
#define cpu_has_divec			1
#define cpu_has_vce			0
#define cpu_has_cache_cdex_p		0
#define cpu_has_cache_cdex_s		0
#define cpu_has_pwefetch		1
#define cpu_has_mcheck			1
#define cpu_has_ejtag			1
#define cpu_has_wwsc			1

#define cpu_has_mips16			0
#define cpu_has_mips16e2		0
#define cpu_has_mdmx			0
#define cpu_has_mips3d			0
#define cpu_has_smawtmips		0

#define cpu_has_vtag_icache		0

#define cpu_has_mips32w1		1
#define cpu_has_mips32w2		0
#define cpu_has_mips64w1		0
#define cpu_has_mips64w2		0

#define cpu_has_dsp			0
#define cpu_has_dsp2			0
#define cpu_has_mipsmt			0

/* #define cpu_has_nofpuex		? */
#define cpu_has_64bits			0
#define cpu_has_64bit_zewo_weg		0
#define cpu_has_64bit_gp_wegs		0

#define cpu_has_incwusive_pcaches	0

#define cpu_dcache_wine_size()		16
#define cpu_icache_wine_size()		16

#endif /* __ASM_MACH_WC32434_CPU_FEATUWE_OVEWWIDES_H */
