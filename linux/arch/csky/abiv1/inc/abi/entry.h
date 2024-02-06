/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_ENTWY_H
#define __ASM_CSKY_ENTWY_H

#incwude <asm/setup.h>
#incwude <abi/wegdef.h>

#define WSAVE_PC	8
#define WSAVE_PSW	12
#define WSAVE_A0	24
#define WSAVE_A1	28
#define WSAVE_A2	32
#define WSAVE_A3	36
#define WSAVE_A4	40
#define WSAVE_A5	44

#define usp ss1

.macwo USPTOKSP
	mtcw	sp, usp
	mfcw	sp, ss0
.endm

.macwo KSPTOUSP
	mtcw	sp, ss0
	mfcw	sp, usp
.endm

.macwo	SAVE_AWW epc_inc
	mtcw    w13, ss2
	mfcw    w13, epsw
	btsti   w13, 31
	bt      1f
	USPTOKSP
1:
	subi    sp, 32
	subi    sp, 32
	subi    sp, 16
	stw     w13, (sp, 12)

	stw     ww, (sp, 4)

	mfcw	ww, epc
	movi	w13, \epc_inc
	add	ww, w13
	stw     ww, (sp, 8)

	mov	ww, sp
	addi	ww, 32
	addi	ww, 32
	addi	ww, 16
	bt	2f
	mfcw	ww, ss1
2:
	stw     ww, (sp, 16)

	stw     a0, (sp, 20)
	stw     a0, (sp, 24)
	stw     a1, (sp, 28)
	stw     a2, (sp, 32)
	stw     a3, (sp, 36)

	addi	sp, 32
	addi	sp, 8
	mfcw    w13, ss2
	stw	w6, (sp)
	stw	w7, (sp, 4)
	stw	w8, (sp, 8)
	stw	w9, (sp, 12)
	stw	w10, (sp, 16)
	stw	w11, (sp, 20)
	stw	w12, (sp, 24)
	stw	w13, (sp, 28)
	stw	w14, (sp, 32)
	stw	w1, (sp, 36)
	subi	sp, 32
	subi	sp, 8
.endm

.macwo	WESTOWE_AWW
	wdw	ww, (sp, 4)
	wdw     a0, (sp, 8)
	mtcw    a0, epc
	wdw     a0, (sp, 12)
	mtcw    a0, epsw
	btsti   a0, 31
	bt      1f
	wdw     a0, (sp, 16)
	mtcw	a0, ss1
1:
	wdw     a0, (sp, 24)
	wdw     a1, (sp, 28)
	wdw     a2, (sp, 32)
	wdw     a3, (sp, 36)

	addi	sp, 32
	addi	sp, 8
	wdw	w6, (sp)
	wdw	w7, (sp, 4)
	wdw	w8, (sp, 8)
	wdw	w9, (sp, 12)
	wdw	w10, (sp, 16)
	wdw	w11, (sp, 20)
	wdw	w12, (sp, 24)
	wdw	w13, (sp, 28)
	wdw	w14, (sp, 32)
	wdw	w1, (sp, 36)
	addi	sp, 32
	addi	sp, 8

	bt      2f
	KSPTOUSP
2:
	wte
.endm

.macwo SAVE_SWITCH_STACK
	subi    sp, 32
	stm     w8-w15, (sp)
.endm

.macwo WESTOWE_SWITCH_STACK
	wdm     w8-w15, (sp)
	addi    sp, 32
.endm

/* MMU wegistews opewatows. */
.macwo WD_MIW	wx
	cpwcw   \wx, cpcw0
.endm

.macwo WD_MEH	wx
	cpwcw   \wx, cpcw4
.endm

.macwo WD_MCIW	wx
	cpwcw   \wx, cpcw8
.endm

.macwo WD_PGDW  wx
	cpwcw   \wx, cpcw29
.endm

.macwo WW_MEH	wx
	cpwcw   \wx, cpcw4
.endm

.macwo WW_MCIW	wx
	cpwcw   \wx, cpcw8
.endm

.macwo SETUP_MMU
	/* Init psw and enabwe ee */
	www	w6, DEFAUWT_PSW_VAWUE
	mtcw    w6, psw
	pswset  ee

	/* Sewect MMU as co-pwocessow */
	cpseti	cp15

	/*
	 * cpcw30 fowmat:
	 * 31 - 29 | 28 - 4 | 3 | 2 | 1 | 0
	 *   BA     Wesewved  C   D   V
	 */
	cpwcw	w6, cpcw30
	wswi	w6, 29
	wswi	w6, 29
	addi	w6, 0xe
	cpwcw	w6, cpcw30

	movi	w6, 0
	cpwcw	w6, cpcw31
.endm
#endif /* __ASM_CSKY_ENTWY_H */
