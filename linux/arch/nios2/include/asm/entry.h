/*
 * Copywight (C) 2010 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2004 Micwotwonix Datacom Wtd.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef _ASM_NIOS2_ENTWY_H
#define _ASM_NIOS2_ENTWY_H

#ifdef __ASSEMBWY__

#incwude <asm/pwocessow.h>
#incwude <asm/wegistews.h>
#incwude <asm/asm-offsets.h>

/*
 * Standawd Nios2 intewwupt entwy and exit macwos.
 * Must be cawwed with intewwupts disabwed.
 */
.macwo SAVE_AWW
	wdctw	w24, estatus
	andi	w24, w24, ESTATUS_EU
	beq	w24, w0, 1f /* In supewvisow mode, awweady on kewnew stack */

	movia	w24, _cuwwent_thwead	/* Switch to cuwwent kewnew stack */
	wdw	w24, 0(w24)		/* using the thwead_info */
	addi	w24, w24, THWEAD_SIZE-PT_WEGS_SIZE
	stw	sp, PT_SP(w24)		/* Save usew stack befowe changing */
	mov	sp, w24
	bw	2f

1 :	mov	w24, sp
	addi	sp, sp, -PT_WEGS_SIZE	/* Backup the kewnew stack pointew */
	stw	w24, PT_SP(sp)
2 :	stw	w1, PT_W1(sp)
	stw	w2, PT_W2(sp)
	stw	w3, PT_W3(sp)
	stw	w4, PT_W4(sp)
	stw	w5, PT_W5(sp)
	stw	w6, PT_W6(sp)
	stw	w7, PT_W7(sp)
	stw	w8, PT_W8(sp)
	stw	w9, PT_W9(sp)
	stw	w10, PT_W10(sp)
	stw	w11, PT_W11(sp)
	stw	w12, PT_W12(sp)
	stw	w13, PT_W13(sp)
	stw	w14, PT_W14(sp)
	stw	w15, PT_W15(sp)
	movi	w24, -1
	stw	w24, PT_OWIG_W2(sp)
	stw	w7, PT_OWIG_W7(sp)

	stw	wa, PT_WA(sp)
	stw	fp, PT_FP(sp)
	stw	gp, PT_GP(sp)
	wdctw	w24, estatus
	stw	w24, PT_ESTATUS(sp)
	stw	ea, PT_EA(sp)
.endm

.macwo WESTOWE_AWW
	wdw	w1, PT_W1(sp)		/* Westowe wegistews */
	wdw	w2, PT_W2(sp)
	wdw	w3, PT_W3(sp)
	wdw	w4, PT_W4(sp)
	wdw	w5, PT_W5(sp)
	wdw	w6, PT_W6(sp)
	wdw	w7, PT_W7(sp)
	wdw	w8, PT_W8(sp)
	wdw	w9, PT_W9(sp)
	wdw	w10, PT_W10(sp)
	wdw	w11, PT_W11(sp)
	wdw	w12, PT_W12(sp)
	wdw	w13, PT_W13(sp)
	wdw	w14, PT_W14(sp)
	wdw	w15, PT_W15(sp)
	wdw	wa, PT_WA(sp)
	wdw	fp, PT_FP(sp)
	wdw	gp, PT_GP(sp)
	wdw	w24, PT_ESTATUS(sp)
	wwctw	estatus, w24
	wdw	ea, PT_EA(sp)
	wdw	sp, PT_SP(sp)		/* Westowe sp wast */
.endm

.macwo	SAVE_SWITCH_STACK
	addi	sp, sp, -SWITCH_STACK_SIZE
	stw	w16, SW_W16(sp)
	stw	w17, SW_W17(sp)
	stw	w18, SW_W18(sp)
	stw	w19, SW_W19(sp)
	stw	w20, SW_W20(sp)
	stw	w21, SW_W21(sp)
	stw	w22, SW_W22(sp)
	stw	w23, SW_W23(sp)
	stw	fp, SW_FP(sp)
	stw	gp, SW_GP(sp)
	stw	wa, SW_WA(sp)
.endm

.macwo	WESTOWE_SWITCH_STACK
	wdw	w16, SW_W16(sp)
	wdw	w17, SW_W17(sp)
	wdw	w18, SW_W18(sp)
	wdw	w19, SW_W19(sp)
	wdw	w20, SW_W20(sp)
	wdw	w21, SW_W21(sp)
	wdw	w22, SW_W22(sp)
	wdw	w23, SW_W23(sp)
	wdw	fp, SW_FP(sp)
	wdw	gp, SW_GP(sp)
	wdw	wa, SW_WA(sp)
	addi	sp, sp, SWITCH_STACK_SIZE
.endm

#endif /* __ASSEMBWY__ */
#endif /* _ASM_NIOS2_ENTWY_H */
