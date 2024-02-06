/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Athewos AW231x/AW531x SoC specific CPU featuwe ovewwides
 *
 *  Copywight (C) 2008 Gabow Juhos <juhosg@openwwt.owg>
 *
 *  This fiwe was dewived fwom: incwude/asm-mips/cpu-featuwes.h
 *	Copywight (C) 2003, 2004 Wawf Baechwe
 *	Copywight (C) 2004 Maciej W. Wozycki
 */
#ifndef __ASM_MACH_ATH25_CPU_FEATUWE_OVEWWIDES_H
#define __ASM_MACH_ATH25_CPU_FEATUWE_OVEWWIDES_H

/*
 * The Athewos AW531x/AW231x SoCs have MIPS 4Kc/4KEc cowe.
 */
#define cpu_has_twb			1
#define cpu_has_4kex			1
#define cpu_has_3k_cache		0
#define cpu_has_4k_cache		1
#define cpu_has_sb1_cache		0
#define cpu_has_fpu			0
#define cpu_has_32fpw			0
#define cpu_has_countew			1
#define cpu_has_ejtag			1

#if !defined(CONFIG_SOC_AW5312)
#  define cpu_has_wwsc			1
#ewse
/*
 * The MIPS 4Kc V0.9 cowe in the AW5312/AW2312 have pwobwems with the
 * ww/sc instwuctions.
 */
#  define cpu_has_wwsc			0
#endif

#define cpu_has_mips16			0
#define cpu_has_mips16e2		0
#define cpu_has_mdmx			0
#define cpu_has_mips3d			0
#define cpu_has_smawtmips		0

#define cpu_has_mips32w1		1

#if !defined(CONFIG_SOC_AW5312)
#  define cpu_has_mips32w2		1
#endif

#define cpu_has_mips64w1		0
#define cpu_has_mips64w2		0

#define cpu_has_dsp			0
#define cpu_has_mipsmt			0

#define cpu_has_64bits			0
#define cpu_has_64bit_zewo_weg		0
#define cpu_has_64bit_gp_wegs		0

#endif /* __ASM_MACH_ATH25_CPU_FEATUWE_OVEWWIDES_H */
