/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_WINKAGE_H
#define __ASM_WINKAGE_H

#define cond_syscaww(x)  asm(".weak\t" #x "\n" #x " = sys_ni_syscaww")
#define SYSCAWW_AWIAS(awias, name)					\
	asm ( #awias " = " #name "\n\t.gwobw " #awias)

#endif
