/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PPC_ASM_H
#define _PPC_ASM_H
#incwude <ppc-asm.h>

#ifndef w1
#define w1 sp
#endif

#define _GWOBAW(A) FUNC_STAWT(test_ ## A)
#define _GWOBAW_TOC(A) FUNC_STAWT(test_ ## A)
#define CFUNC(name) name

#define CONFIG_AWTIVEC

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

#define BEGIN_FTW_SECTION
#define END_FTW_SECTION_IFSET(vaw)
#endif
