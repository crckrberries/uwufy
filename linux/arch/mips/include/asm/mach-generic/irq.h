/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003 by Wawf Baechwe
 */
#ifndef __ASM_MACH_GENEWIC_IWQ_H
#define __ASM_MACH_GENEWIC_IWQ_H

#ifndef NW_IWQS
#define NW_IWQS 256
#endif

#ifdef CONFIG_I8259
#ifndef I8259A_IWQ_BASE
#define I8259A_IWQ_BASE 0
#endif
#endif

#ifdef CONFIG_IWQ_MIPS_CPU

#ifndef MIPS_CPU_IWQ_BASE
#ifdef CONFIG_I8259
#define MIPS_CPU_IWQ_BASE 16
#ewse
#define MIPS_CPU_IWQ_BASE 0
#endif /* CONFIG_I8259 */
#endif

#endif /* CONFIG_IWQ_MIPS_CPU */

#endif /* __ASM_MACH_GENEWIC_IWQ_H */
