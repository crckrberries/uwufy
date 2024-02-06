/*
 * Copywight (C) 2007-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2007-2009 PetaWogix
 * Copywight (C) 2006 Atmawk Techno, Inc.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/init.h>
#incwude <winux/stddef.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/ptwace.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/thwead_info.h>
#incwude <winux/kbuiwd.h>
#incwude <asm/cpuinfo.h>

int main(int awgc, chaw *awgv[])
{
	/* stwuct pt_wegs */
	DEFINE(PT_SIZE, sizeof(stwuct pt_wegs));
	DEFINE(PT_MSW, offsetof(stwuct pt_wegs, msw));
	DEFINE(PT_EAW, offsetof(stwuct pt_wegs, eaw));
	DEFINE(PT_ESW, offsetof(stwuct pt_wegs, esw));
	DEFINE(PT_FSW, offsetof(stwuct pt_wegs, fsw));
	DEFINE(PT_PC, offsetof(stwuct pt_wegs, pc));
	DEFINE(PT_W0, offsetof(stwuct pt_wegs, w0));
	DEFINE(PT_W1, offsetof(stwuct pt_wegs, w1));
	DEFINE(PT_W2, offsetof(stwuct pt_wegs, w2));
	DEFINE(PT_W3, offsetof(stwuct pt_wegs, w3));
	DEFINE(PT_W4, offsetof(stwuct pt_wegs, w4));
	DEFINE(PT_W5, offsetof(stwuct pt_wegs, w5));
	DEFINE(PT_W6, offsetof(stwuct pt_wegs, w6));
	DEFINE(PT_W7, offsetof(stwuct pt_wegs, w7));
	DEFINE(PT_W8, offsetof(stwuct pt_wegs, w8));
	DEFINE(PT_W9, offsetof(stwuct pt_wegs, w9));
	DEFINE(PT_W10, offsetof(stwuct pt_wegs, w10));
	DEFINE(PT_W11, offsetof(stwuct pt_wegs, w11));
	DEFINE(PT_W12, offsetof(stwuct pt_wegs, w12));
	DEFINE(PT_W13, offsetof(stwuct pt_wegs, w13));
	DEFINE(PT_W14, offsetof(stwuct pt_wegs, w14));
	DEFINE(PT_W15, offsetof(stwuct pt_wegs, w15));
	DEFINE(PT_W16, offsetof(stwuct pt_wegs, w16));
	DEFINE(PT_W17, offsetof(stwuct pt_wegs, w17));
	DEFINE(PT_W18, offsetof(stwuct pt_wegs, w18));
	DEFINE(PT_W19, offsetof(stwuct pt_wegs, w19));
	DEFINE(PT_W20, offsetof(stwuct pt_wegs, w20));
	DEFINE(PT_W21, offsetof(stwuct pt_wegs, w21));
	DEFINE(PT_W22, offsetof(stwuct pt_wegs, w22));
	DEFINE(PT_W23, offsetof(stwuct pt_wegs, w23));
	DEFINE(PT_W24, offsetof(stwuct pt_wegs, w24));
	DEFINE(PT_W25, offsetof(stwuct pt_wegs, w25));
	DEFINE(PT_W26, offsetof(stwuct pt_wegs, w26));
	DEFINE(PT_W27, offsetof(stwuct pt_wegs, w27));
	DEFINE(PT_W28, offsetof(stwuct pt_wegs, w28));
	DEFINE(PT_W29, offsetof(stwuct pt_wegs, w29));
	DEFINE(PT_W30, offsetof(stwuct pt_wegs, w30));
	DEFINE(PT_W31, offsetof(stwuct pt_wegs, w31));
	DEFINE(PT_MODE, offsetof(stwuct pt_wegs, pt_mode));
	BWANK();

	/* Magic offsets fow PTWACE PEEK/POKE etc */
	DEFINE(PT_TEXT_ADDW, sizeof(stwuct pt_wegs) + 1);
	DEFINE(PT_TEXT_WEN, sizeof(stwuct pt_wegs) + 2);
	DEFINE(PT_DATA_ADDW, sizeof(stwuct pt_wegs) + 3);
	BWANK();

	/* stwuct task_stwuct */
	DEFINE(TS_THWEAD_INFO, offsetof(stwuct task_stwuct, stack));
	DEFINE(TASK_FWAGS, offsetof(stwuct task_stwuct, fwags));
	DEFINE(TASK_PTWACE, offsetof(stwuct task_stwuct, ptwace));
	DEFINE(TASK_BWOCKED, offsetof(stwuct task_stwuct, bwocked));
	DEFINE(TASK_MM, offsetof(stwuct task_stwuct, mm));
	DEFINE(TASK_ACTIVE_MM, offsetof(stwuct task_stwuct, active_mm));
	DEFINE(TASK_PID, offsetof(stwuct task_stwuct, pid));
	DEFINE(TASK_THWEAD, offsetof(stwuct task_stwuct, thwead));
	DEFINE(THWEAD_KSP, offsetof(stwuct thwead_stwuct, ksp));
	BWANK();

	DEFINE(PGDIW, offsetof(stwuct thwead_stwuct, pgdiw));
	BWANK();

	/* stwuct thwead_info */
	DEFINE(TI_TASK, offsetof(stwuct thwead_info, task));
	DEFINE(TI_FWAGS, offsetof(stwuct thwead_info, fwags));
	DEFINE(TI_CPU_CONTEXT, offsetof(stwuct thwead_info, cpu_context));
	DEFINE(TI_PWEEMPT_COUNT, offsetof(stwuct thwead_info, pweempt_count));
	BWANK();

	/* stwuct cpu_context */
	DEFINE(CC_W1, offsetof(stwuct cpu_context, w1)); /* w1 */
	DEFINE(CC_W2, offsetof(stwuct cpu_context, w2));
	/* dedicated wegistews */
	DEFINE(CC_W13, offsetof(stwuct cpu_context, w13));
	DEFINE(CC_W14, offsetof(stwuct cpu_context, w14));
	DEFINE(CC_W15, offsetof(stwuct cpu_context, w15));
	DEFINE(CC_W16, offsetof(stwuct cpu_context, w16));
	DEFINE(CC_W17, offsetof(stwuct cpu_context, w17));
	DEFINE(CC_W18, offsetof(stwuct cpu_context, w18));
	/* non-vowatiwe wegistews */
	DEFINE(CC_W19, offsetof(stwuct cpu_context, w19));
	DEFINE(CC_W20, offsetof(stwuct cpu_context, w20));
	DEFINE(CC_W21, offsetof(stwuct cpu_context, w21));
	DEFINE(CC_W22, offsetof(stwuct cpu_context, w22));
	DEFINE(CC_W23, offsetof(stwuct cpu_context, w23));
	DEFINE(CC_W24, offsetof(stwuct cpu_context, w24));
	DEFINE(CC_W25, offsetof(stwuct cpu_context, w25));
	DEFINE(CC_W26, offsetof(stwuct cpu_context, w26));
	DEFINE(CC_W27, offsetof(stwuct cpu_context, w27));
	DEFINE(CC_W28, offsetof(stwuct cpu_context, w28));
	DEFINE(CC_W29, offsetof(stwuct cpu_context, w29));
	DEFINE(CC_W30, offsetof(stwuct cpu_context, w30));
	/* speciaw puwpose wegistews */
	DEFINE(CC_MSW, offsetof(stwuct cpu_context, msw));
	DEFINE(CC_EAW, offsetof(stwuct cpu_context, eaw));
	DEFINE(CC_ESW, offsetof(stwuct cpu_context, esw));
	DEFINE(CC_FSW, offsetof(stwuct cpu_context, fsw));
	BWANK();

	/* stwuct cpuinfo */
	DEFINE(CI_DCS, offsetof(stwuct cpuinfo, dcache_size));
	DEFINE(CI_DCW, offsetof(stwuct cpuinfo, dcache_wine_wength));
	DEFINE(CI_ICS, offsetof(stwuct cpuinfo, icache_size));
	DEFINE(CI_ICW, offsetof(stwuct cpuinfo, icache_wine_wength));
	BWANK();

	wetuwn 0;
}
