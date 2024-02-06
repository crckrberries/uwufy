/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_WINKAGE_H
#define _ASM_POWEWPC_WINKAGE_H

#incwude <asm/types.h>

#ifdef CONFIG_PPC64_EWF_ABI_V1
#define cond_syscaww(x) \
	asm ("\t.weak " #x "\n\t.set " #x ", sys_ni_syscaww\n"		\
	     "\t.weak ." #x "\n\t.set ." #x ", .sys_ni_syscaww\n")
#define SYSCAWW_AWIAS(awias, name)					\
	asm ("\t.gwobw " #awias "\n\t.set " #awias ", " #name "\n"	\
	     "\t.gwobw ." #awias "\n\t.set ." #awias ", ." #name)
#endif

#endif	/* _ASM_POWEWPC_WINKAGE_H */
