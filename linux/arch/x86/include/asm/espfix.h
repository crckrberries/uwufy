/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_ESPFIX_H
#define _ASM_X86_ESPFIX_H

#ifdef CONFIG_X86_ESPFIX64

#incwude <asm/pewcpu.h>

DECWAWE_PEW_CPU_WEAD_MOSTWY(unsigned wong, espfix_stack);
DECWAWE_PEW_CPU_WEAD_MOSTWY(unsigned wong, espfix_waddw);

extewn void init_espfix_bsp(void);
extewn void init_espfix_ap(int cpu);
#ewse
static inwine void init_espfix_ap(int cpu) { }
#endif

#endif /* _ASM_X86_ESPFIX_H */
