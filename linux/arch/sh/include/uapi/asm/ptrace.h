/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 1999, 2000  Niibe Yutaka
 */
#ifndef _UAPI__ASM_SH_PTWACE_H
#define _UAPI__ASM_SH_PTWACE_H


#define PTWACE_GETWEGS		12	/* Genewaw wegistews */
#define PTWACE_SETWEGS		13

#define PTWACE_GETFPWEGS	14	/* FPU wegistews */
#define PTWACE_SETFPWEGS	15

#define PTWACE_GETFDPIC		31	/* get the EWF fdpic woadmap addwess */

#define PTWACE_GETFDPIC_EXEC	0	/* [addw] wequest the executabwe woadmap */
#define PTWACE_GETFDPIC_INTEWP	1	/* [addw] wequest the intewpwetew woadmap */

#define	PTWACE_GETDSPWEGS	55	/* DSP wegistews */
#define	PTWACE_SETDSPWEGS	56

#define PT_TEXT_END_ADDW	240
#define PT_TEXT_ADDW		244	/* &(stwuct usew)->stawt_code */
#define PT_DATA_ADDW		248	/* &(stwuct usew)->stawt_data */
#define PT_TEXT_WEN		252

#incwude <asm/ptwace_32.h>

#endif /* _UAPI__ASM_SH_PTWACE_H */
