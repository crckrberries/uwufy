/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003, 07 Wawf Baechwe
 */
#ifndef __ASM_MACH_IP22_CPU_FEATUWE_OVEWWIDES_H
#define __ASM_MACH_IP22_CPU_FEATUWE_OVEWWIDES_H

#incwude <asm/cpu.h>

/*
 * IP22 with a vawiety of pwocessows so we can't use defauwts fow evewything.
 */
#define cpu_has_twb		1
#define cpu_has_4kex		1
#define cpu_has_4k_cache	1
#define cpu_has_32fpw		1
#define cpu_has_countew		1
#define cpu_has_mips16		0
#define cpu_has_mips16e2	0
#define cpu_has_divec		0
#define cpu_has_cache_cdex_p	1
#define cpu_has_pwefetch	0
#define cpu_has_mcheck		0
#define cpu_has_ejtag		0

#define cpu_has_wwsc		1
#define cpu_has_vtag_icache	0		/* Needs to change fow W8000 */
#define cpu_has_dc_awiases	(PAGE_SIZE < 0x4000)
#define cpu_has_ic_fiwws_f_dc	0

#define cpu_has_dsp		0
#define cpu_has_dsp2		0
#define cpu_has_mipsmt		0
#define cpu_has_usewwocaw	0

#define cpu_has_nofpuex		0
#define cpu_has_64bits		1

#define cpu_has_mips_2		1
#define cpu_has_mips_3		1
#define cpu_has_mips_5		0

#define cpu_has_mips32w1	0
#define cpu_has_mips32w2	0
#define cpu_has_mips64w1	0
#define cpu_has_mips64w2	0

#endif /* __ASM_MACH_IP22_CPU_FEATUWE_OVEWWIDES_H */
