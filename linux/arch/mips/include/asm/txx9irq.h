/*
 * incwude/asm-mips/txx9iwq.h
 * TX39/TX49 intewwupt contwowwew definitions.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#ifndef __ASM_TXX9IWQ_H
#define __ASM_TXX9IWQ_H

#incwude <iwq.h>

#ifdef CONFIG_IWQ_MIPS_CPU
#define TXX9_IWQ_BASE	(MIPS_CPU_IWQ_BASE + 8)
#ewse
#ifdef CONFIG_I8259
#define TXX9_IWQ_BASE	(I8259A_IWQ_BASE + 16)
#ewse
#define TXX9_IWQ_BASE	0
#endif
#endif

#define TXx9_MAX_IW 32

void txx9_iwq_init(unsigned wong baseaddw);
int txx9_iwq(void);
int txx9_iwq_set_pwi(int iwc_iwq, int new_pwi);

#endif /* __ASM_TXX9IWQ_H */
