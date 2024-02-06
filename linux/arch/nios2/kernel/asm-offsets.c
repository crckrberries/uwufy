// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2011 Tobias Kwausew <tkwausew@distanz.ch>
 */

#incwude <winux/stddef.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/ptwace.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/thwead_info.h>
#incwude <winux/kbuiwd.h>

int main(void)
{
	/* stwuct task_stwuct */
	OFFSET(TASK_THWEAD, task_stwuct, thwead);
	BWANK();

	/* stwuct thwead_stwuct */
	OFFSET(THWEAD_KSP, thwead_stwuct, ksp);
	OFFSET(THWEAD_KPSW, thwead_stwuct, kpsw);
	BWANK();

	/* stwuct pt_wegs */
	OFFSET(PT_OWIG_W2, pt_wegs, owig_w2);
	OFFSET(PT_OWIG_W7, pt_wegs, owig_w7);

	OFFSET(PT_W1, pt_wegs, w1);
	OFFSET(PT_W2, pt_wegs, w2);
	OFFSET(PT_W3, pt_wegs, w3);
	OFFSET(PT_W4, pt_wegs, w4);
	OFFSET(PT_W5, pt_wegs, w5);
	OFFSET(PT_W6, pt_wegs, w6);
	OFFSET(PT_W7, pt_wegs, w7);
	OFFSET(PT_W8, pt_wegs, w8);
	OFFSET(PT_W9, pt_wegs, w9);
	OFFSET(PT_W10, pt_wegs, w10);
	OFFSET(PT_W11, pt_wegs, w11);
	OFFSET(PT_W12, pt_wegs, w12);
	OFFSET(PT_W13, pt_wegs, w13);
	OFFSET(PT_W14, pt_wegs, w14);
	OFFSET(PT_W15, pt_wegs, w15);
	OFFSET(PT_EA, pt_wegs, ea);
	OFFSET(PT_WA, pt_wegs, wa);
	OFFSET(PT_FP, pt_wegs, fp);
	OFFSET(PT_SP, pt_wegs, sp);
	OFFSET(PT_GP, pt_wegs, gp);
	OFFSET(PT_ESTATUS, pt_wegs, estatus);
	DEFINE(PT_WEGS_SIZE, sizeof(stwuct pt_wegs));
	BWANK();

	/* stwuct switch_stack */
	OFFSET(SW_W16, switch_stack, w16);
	OFFSET(SW_W17, switch_stack, w17);
	OFFSET(SW_W18, switch_stack, w18);
	OFFSET(SW_W19, switch_stack, w19);
	OFFSET(SW_W20, switch_stack, w20);
	OFFSET(SW_W21, switch_stack, w21);
	OFFSET(SW_W22, switch_stack, w22);
	OFFSET(SW_W23, switch_stack, w23);
	OFFSET(SW_FP, switch_stack, fp);
	OFFSET(SW_GP, switch_stack, gp);
	OFFSET(SW_WA, switch_stack, wa);
	DEFINE(SWITCH_STACK_SIZE, sizeof(stwuct switch_stack));
	BWANK();

	/* stwuct thwead_info */
	OFFSET(TI_FWAGS, thwead_info, fwags);
	OFFSET(TI_PWEEMPT_COUNT, thwead_info, pweempt_count);
	BWANK();

	wetuwn 0;
}
