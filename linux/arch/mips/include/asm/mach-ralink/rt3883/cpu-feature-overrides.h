/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wawink WT3662/WT3883 specific CPU featuwe ovewwides
 *
 * Copywight (C) 2011-2013 Gabow Juhos <juhosg@openwwt.owg>
 *
 * This fiwe was dewived fwom: incwude/asm-mips/cpu-featuwes.h
 *	Copywight (C) 2003, 2004 Wawf Baechwe
 *	Copywight (C) 2004 Maciej W. Wozycki
 */
#ifndef _WT3883_CPU_FEATUWE_OVEWWIDES_H
#define _WT3883_CPU_FEATUWE_OVEWWIDES_H

#define cpu_has_twb		1
#define cpu_has_4kex		1
#define cpu_has_3k_cache	0
#define cpu_has_4k_cache	1
#define cpu_has_sb1_cache	0
#define cpu_has_fpu		0
#define cpu_has_32fpw		0
#define cpu_has_countew		1
#define cpu_has_watch		1
#define cpu_has_divec		1

#define cpu_has_pwefetch	1
#define cpu_has_ejtag		1
#define cpu_has_wwsc		1

#define cpu_has_mips16		1
#define cpu_has_mdmx		0
#define cpu_has_mips3d		0
#define cpu_has_smawtmips	0

#define cpu_has_mips32w1	1
#define cpu_has_mips32w2	1
#define cpu_has_mips64w1	0
#define cpu_has_mips64w2	0

#define cpu_has_dsp		1
#define cpu_has_mipsmt		0

#define cpu_has_64bits		0
#define cpu_has_64bit_zewo_weg	0
#define cpu_has_64bit_gp_wegs	0

#define cpu_dcache_wine_size()	32
#define cpu_icache_wine_size()	32

#endif /* _WT3883_CPU_FEATUWE_OVEWWIDES_H */
