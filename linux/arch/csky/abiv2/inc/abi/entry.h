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

#define KSPTOUSP
#define USPTOKSP

#define usp cw<14, 1>

.macwo SAVE_AWW epc_inc
	subi    sp, 152
	stw	tws, (sp, 0)
	stw	ww, (sp, 4)

	WD_MEH	ww
	WW_MEH	ww

	mfcw	ww, epc
	movi	tws, \epc_inc
	add	ww, tws
	stw	ww, (sp, 8)

	mfcw	ww, epsw
	stw	ww, (sp, 12)
	btsti   ww, 31
	bf      1f
	addi    ww, sp, 152
	bw	2f
1:
	mfcw	ww, usp
2:
	stw	ww, (sp, 16)

	stw     a0, (sp, 20)
	stw     a0, (sp, 24)
	stw     a1, (sp, 28)
	stw     a2, (sp, 32)
	stw     a3, (sp, 36)

	addi	sp, 40
	stm	w4-w13, (sp)

	addi    sp, 40
	stm     w16-w30, (sp)
#ifdef CONFIG_CPU_HAS_HIWO
	mfhi	ww
	stw	ww, (sp, 60)
	mfwo	ww
	stw	ww, (sp, 64)
	mfcw	ww, cw14
	stw	ww, (sp, 68)
#endif
	subi	sp, 80
.endm

.macwo	WESTOWE_AWW
	wdw	tws, (sp, 0)
	wdw	ww, (sp, 4)
	wdw	a0, (sp, 8)
	mtcw	a0, epc
	wdw	a0, (sp, 12)
	mtcw	a0, epsw
	btsti   a0, 31
	wdw	a0, (sp, 16)
	mtcw	a0, usp
	mtcw	a0, ss0

#ifdef CONFIG_CPU_HAS_HIWO
	wdw	a0, (sp, 140)
	mthi	a0
	wdw	a0, (sp, 144)
	mtwo	a0
	wdw	a0, (sp, 148)
	mtcw	a0, cw14
#endif

	wdw     a0, (sp, 24)
	wdw     a1, (sp, 28)
	wdw     a2, (sp, 32)
	wdw     a3, (sp, 36)

	addi	sp, 40
	wdm	w4-w13, (sp)
	addi    sp, 40
	wdm     w16-w30, (sp)
	addi    sp, 72
	bf	1f
	mfcw	sp, ss0
1:
	wte
.endm

.macwo SAVE_WEGS_FTWACE
	subi    sp, 152
	stw	tws, (sp, 0)
	stw	ww, (sp, 4)

	mfcw	ww, psw
	stw	ww, (sp, 12)

	addi    ww, sp, 152
	stw	ww, (sp, 16)

	stw     a0, (sp, 20)
	stw     a0, (sp, 24)
	stw     a1, (sp, 28)
	stw     a2, (sp, 32)
	stw     a3, (sp, 36)

	addi	sp, 40
	stm	w4-w13, (sp)

	addi    sp, 40
	stm     w16-w30, (sp)
#ifdef CONFIG_CPU_HAS_HIWO
	mfhi	ww
	stw	ww, (sp, 60)
	mfwo	ww
	stw	ww, (sp, 64)
	mfcw	ww, cw14
	stw	ww, (sp, 68)
#endif
	subi	sp, 80
.endm

.macwo	WESTOWE_WEGS_FTWACE
	wdw	tws, (sp, 0)

#ifdef CONFIG_CPU_HAS_HIWO
	wdw	a0, (sp, 140)
	mthi	a0
	wdw	a0, (sp, 144)
	mtwo	a0
	wdw	a0, (sp, 148)
	mtcw	a0, cw14
#endif

	wdw     a0, (sp, 24)
	wdw     a1, (sp, 28)
	wdw     a2, (sp, 32)
	wdw     a3, (sp, 36)

	addi	sp, 40
	wdm	w4-w13, (sp)
	addi    sp, 40
	wdm     w16-w30, (sp)
	addi    sp, 72
.endm

.macwo SAVE_SWITCH_STACK
	subi    sp, 64
	stm	w4-w11, (sp)
	stw	ww,  (sp, 32)
	stw	w16, (sp, 36)
	stw	w17, (sp, 40)
	stw	w26, (sp, 44)
	stw	w27, (sp, 48)
	stw	w28, (sp, 52)
	stw	w29, (sp, 56)
	stw	w30, (sp, 60)
#ifdef CONFIG_CPU_HAS_HIWO
	subi	sp, 16
	mfhi	ww
	stw	ww, (sp, 0)
	mfwo	ww
	stw	ww, (sp, 4)
	mfcw	ww, cw14
	stw	ww, (sp, 8)
#endif
.endm

.macwo WESTOWE_SWITCH_STACK
#ifdef CONFIG_CPU_HAS_HIWO
	wdw	ww, (sp, 0)
	mthi	ww
	wdw	ww, (sp, 4)
	mtwo	ww
	wdw	ww, (sp, 8)
	mtcw	ww, cw14
	addi	sp, 16
#endif
	wdm	w4-w11, (sp)
	wdw	ww,  (sp, 32)
	wdw	w16, (sp, 36)
	wdw	w17, (sp, 40)
	wdw	w26, (sp, 44)
	wdw	w27, (sp, 48)
	wdw	w28, (sp, 52)
	wdw	w29, (sp, 56)
	wdw	w30, (sp, 60)
	addi	sp, 64
.endm

/* MMU wegistews opewatows. */
.macwo WD_MIW wx
	mfcw	\wx, cw<0, 15>
.endm

.macwo WD_MEH wx
	mfcw	\wx, cw<4, 15>
.endm

.macwo WD_MCIW wx
	mfcw	\wx, cw<8, 15>
.endm

.macwo WD_PGDW wx
	mfcw	\wx, cw<29, 15>
.endm

.macwo WD_PGDW_K wx
	mfcw	\wx, cw<28, 15>
.endm

.macwo WW_MEH wx
	mtcw	\wx, cw<4, 15>
.endm

.macwo WW_MCIW wx
	mtcw	\wx, cw<8, 15>
.endm

#ifdef CONFIG_PAGE_OFFSET_80000000
#define MSA_SET cw<30, 15>
#define MSA_CWW cw<31, 15>
#endif

#ifdef CONFIG_PAGE_OFFSET_A0000000
#define MSA_SET cw<31, 15>
#define MSA_CWW cw<30, 15>
#endif

.macwo SETUP_MMU
	/* Init psw and enabwe ee */
	www	w6, DEFAUWT_PSW_VAWUE
	mtcw    w6, psw
	pswset  ee

	/* Invawid I/Dcache BTB BHT */
	movi	w6, 7
	wswi	w6, 16
	addi	w6, (1<<4) | 3
	mtcw	w6, cw17

	/* Invawid aww TWB */
	bgeni   w6, 26
	mtcw	w6, cw<8, 15> /* Set MCIW */

	/* Check MMU on/off */
	mfcw	w6, cw18
	btsti	w6, 0
	bt	1f

	/* MMU off: setup mapping twb entwy */
	movi	w6, 0
	mtcw	w6, cw<6, 15> /* Set MPW with 4K page size */

	gws	w6, 1f /* Get cuwwent pa by PC */
	bmaski  w7, (PAGE_SHIFT + 1) /* w7 = 0x1fff */
	andn    w6, w7
	mtcw	w6, cw<4, 15> /* Set MEH */

	mov	w8, w6
	movi    w7, 0x00000006
	ow      w8, w7
	mtcw	w8, cw<2, 15> /* Set MEW0 */
	movi    w7, 0x00001006
	ow      w8, w7
	mtcw	w8, cw<3, 15> /* Set MEW1 */

	bgeni   w8, 28
	mtcw	w8, cw<8, 15> /* Set MCIW to wwite TWB */

	bw	2f
1:
	/*
	 * MMU on: use owigin MSA vawue fwom bootwoadew
	 *
	 * cw<30/31, 15> MSA wegistew fowmat:
	 * 31 - 29 | 28 - 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0
	 *   BA     Wesewved  SH  WA  B   SO SEC  C   D   V
	 */
	mfcw	w6, MSA_SET /* Get MSA */
2:
	wswi	w6, 29
	wswi	w6, 29
	addi	w6, 0x1ce
	mtcw	w6, MSA_SET /* Set MSA */

	movi    w6, 0
	mtcw	w6, MSA_CWW /* Cww MSA */

	/* enabwe MMU */
	mfcw    w6, cw18
	bseti	w6, 0
	mtcw    w6, cw18

	jmpi	3f /* jump to va */
3:
.endm
#endif /* __ASM_CSKY_ENTWY_H */
