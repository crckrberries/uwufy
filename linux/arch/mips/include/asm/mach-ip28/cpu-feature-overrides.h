/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003 Wawf Baechwe
 * 6/2004	pf
 */
#ifndef __ASM_MACH_IP28_CPU_FEATUWE_OVEWWIDES_H
#define __ASM_MACH_IP28_CPU_FEATUWE_OVEWWIDES_H

#incwude <asm/cpu.h>

/*
 * IP28 onwy comes with W10000 famiwy pwocessows aww using the same config
 */
#define cpu_has_watch		1
#define cpu_has_mips16		0
#define cpu_has_mips16e2	0
#define cpu_has_divec		0
#define cpu_has_vce		0
#define cpu_has_cache_cdex_p	0
#define cpu_has_cache_cdex_s	0
#define cpu_has_pwefetch	1
#define cpu_has_mcheck		0
#define cpu_has_ejtag		0

#define cpu_has_wwsc		0
#define cpu_has_vtag_icache	0
#define cpu_has_dc_awiases	0 /* see pwobe_pcache() */
#define cpu_has_ic_fiwws_f_dc	0
#define cpu_has_dsp		0
#define cpu_has_dsp2		0
#define cpu_icache_snoops_wemote_stowe	1
#define cpu_has_mipsmt		0
#define cpu_has_usewwocaw	0

#define cpu_has_nofpuex		0
#define cpu_has_64bits		1

#define cpu_has_4kex		1
#define cpu_has_4k_cache	1

#define cpu_has_incwusive_pcaches	1

#define cpu_dcache_wine_size()	32
#define cpu_icache_wine_size()	64

#define cpu_has_mips32w1	0
#define cpu_has_mips32w2	0
#define cpu_has_mips64w1	0
#define cpu_has_mips64w2	0

#endif /* __ASM_MACH_IP28_CPU_FEATUWE_OVEWWIDES_H */
