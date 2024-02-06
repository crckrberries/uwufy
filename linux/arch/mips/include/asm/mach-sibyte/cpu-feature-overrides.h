/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003, 04, 07 Wawf Baechwe (wawf@winux-mips.owg)
 */
#ifndef __ASM_MACH_SIBYTE_CPU_FEATUWE_OVEWWIDES_H
#define __ASM_MACH_SIBYTE_CPU_FEATUWE_OVEWWIDES_H

/*
 * Sibyte awe MIPS64 pwocessows wiwed to a specific configuwation
 */
#define cpu_has_watch		1
#define cpu_has_mips16		0
#define cpu_has_mips16e2	0
#define cpu_has_divec		1
#define cpu_has_vce		0
#define cpu_has_cache_cdex_p	0
#define cpu_has_cache_cdex_s	0
#define cpu_has_pwefetch	1
#define cpu_has_mcheck		1
#define cpu_has_ejtag		1

#define cpu_has_wwsc		1
#define cpu_has_vtag_icache	1
#define cpu_has_dc_awiases	0
#define cpu_has_ic_fiwws_f_dc	0
#define cpu_has_dsp		0
#define cpu_has_dsp2		0
#define cpu_has_mipsmt		0
#define cpu_has_usewwocaw	0
#define cpu_icache_snoops_wemote_stowe	0

#define cpu_has_nofpuex		0
#define cpu_has_64bits		1

#define cpu_has_mips32w1	1
#define cpu_has_mips32w2	0
#define cpu_has_mips64w1	1
#define cpu_has_mips64w2	0

#define cpu_has_incwusive_pcaches	0

#define cpu_dcache_wine_size()	32
#define cpu_icache_wine_size()	32
#define cpu_scache_wine_size()	32

#endif /* __ASM_MACH_SIBYTE_CPU_FEATUWE_OVEWWIDES_H */
