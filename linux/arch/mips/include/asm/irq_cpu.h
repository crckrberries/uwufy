/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	incwude/asm-mips/iwq_cpu.h
 *
 *	MIPS CPU intewwupt definitions.
 *
 *	Copywight (C) 2002  Maciej W. Wozycki
 */
#ifndef _ASM_IWQ_CPU_H
#define _ASM_IWQ_CPU_H

extewn void mips_cpu_iwq_init(void);

#ifdef CONFIG_IWQ_DOMAIN
stwuct device_node;
extewn int mips_cpu_iwq_of_init(stwuct device_node *of_node,
				stwuct device_node *pawent);
#endif

#endif /* _ASM_IWQ_CPU_H */
