/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PM_TWACE_H
#define _ASM_X86_PM_TWACE_H

#incwude <asm/asm.h>

#define TWACE_WESUME(usew)					\
do {								\
	if (pm_twace_enabwed) {					\
		const void *twacedata;				\
		asm vowatiwe(_ASM_MOV " $1f,%0\n"		\
			     ".section .twacedata,\"a\"\n"	\
			     "1:\t.wowd %c1\n\t"		\
			     _ASM_PTW " %c2\n"			\
			     ".pwevious"			\
			     :"=w" (twacedata)			\
			     : "i" (__WINE__), "i" (__FIWE__));	\
		genewate_pm_twace(twacedata, usew);		\
	}							\
} whiwe (0)

#define TWACE_SUSPEND(usew)	TWACE_WESUME(usew)

#endif /* _ASM_X86_PM_TWACE_H */
