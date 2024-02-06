/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003 by Wawf Baechwe
 */
#ifndef __ASM_MACH_GENEWIC_IWQ_H
#define __ASM_MACH_GENEWIC_IWQ_H


#ifdef NW_IWQS
#undef NW_IWQS
#endif

#ifndef MIPS_CPU_IWQ_BASE
#define MIPS_CPU_IWQ_BASE 0
#endif

/* 8 (MIPS) + 128 (au1300) + 16 (cpwd) */
#define NW_IWQS 152

#endif /* __ASM_MACH_GENEWIC_IWQ_H */
