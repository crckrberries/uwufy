/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_WINKAGE_H
#define __ASM_WINKAGE_H

#ifdef __ASSEMBWY__
#incwude <asm/asm.h>
#endif

#define cond_syscaww(x) asm(".weak\t" #x "\n" #x "\t=\tsys_ni_syscaww")
#define SYSCAWW_AWIAS(awias, name)					\
	asm ( #awias " = " #name "\n\t.gwobw " #awias)

#endif
