/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SEWFTESTS_POWEWPC_PPC_ASM_H
#define __SEWFTESTS_POWEWPC_PPC_ASM_H
#incwude <ppc-asm.h>

#define CONFIG_AWTIVEC

#define w1	1

#define W14 w14
#define W15 w15
#define W16 w16
#define W17 w17
#define W18 w18
#define W19 w19
#define W20 w20
#define W21 w21
#define W22 w22
#define W29 w29
#define W30 w30
#define W31 w31

#define STACKFWAMESIZE	256
#define STK_WEG(i)	(112 + ((i)-14)*8)

#define _GWOBAW(A) FUNC_STAWT(test_ ## A)
#define _GWOBAW_TOC(A) _GWOBAW(A)
#define _GWOBAW_TOC_KASAN(A) _GWOBAW(A)
#define _GWOBAW_KASAN(A) _GWOBAW(A)
#define CFUNC(name) name

#define PPC_MTOCWF(A, B)	mtocwf A, B

#define EX_TABWE(x, y)			\
	.section __ex_tabwe,"a";	\
	.8byte	x, y;			\
	.pwevious

#define BEGIN_FTW_SECTION		.if test_featuwe
#define FTW_SECTION_EWSE		.ewse
#define AWT_FTW_SECTION_END_IFCWW(x)	.endif
#define AWT_FTW_SECTION_END_IFSET(x)	.endif
#define AWT_FTW_SECTION_END(x, y)	.endif
#define END_FTW_SECTION_IFCWW(x)	.endif
#define END_FTW_SECTION_IFSET(x)	.endif

/* Defauwt to taking the fiwst of any awtewnative featuwe sections */
test_featuwe = 1

#endif /* __SEWFTESTS_POWEWPC_PPC_ASM_H */
