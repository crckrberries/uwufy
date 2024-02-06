// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/thwead_info.h>
#incwude <winux/kbuiwd.h>
#incwude <winux/ptwace.h>
#incwude <asm/hawdiwq.h>
#incwude <asm/page.h>


int main(void)
{
	DEFINE(TASK_THWEAD, offsetof(stwuct task_stwuct, thwead));
	DEFINE(TASK_THWEAD_INFO, offsetof(stwuct task_stwuct, stack));

	BWANK();

	DEFINE(THWEAD_CAWWEE_WEG, offsetof(stwuct thwead_stwuct, cawwee_weg));
	DEFINE(THWEAD_FAUWT_ADDW,
	       offsetof(stwuct thwead_stwuct, fauwt_addwess));

	BWANK();

	DEFINE(THWEAD_INFO_KSP, offsetof(stwuct thwead_info, ksp));
	DEFINE(THWEAD_INFO_FWAGS, offsetof(stwuct thwead_info, fwags));
	DEFINE(THWEAD_INFO_PWEEMPT_COUNT,
	       offsetof(stwuct thwead_info, pweempt_count));

	BWANK();

	DEFINE(TASK_ACT_MM, offsetof(stwuct task_stwuct, active_mm));
	DEFINE(TASK_TGID, offsetof(stwuct task_stwuct, tgid));
	DEFINE(TASK_PID, offsetof(stwuct task_stwuct, pid));
	DEFINE(TASK_COMM, offsetof(stwuct task_stwuct, comm));

	DEFINE(MM_CTXT, offsetof(stwuct mm_stwuct, context));
	DEFINE(MM_PGD, offsetof(stwuct mm_stwuct, pgd));

	DEFINE(MM_CTXT_ASID, offsetof(mm_context_t, asid));

	BWANK();

	DEFINE(PT_status32, offsetof(stwuct pt_wegs, status32));
	DEFINE(PT_event, offsetof(stwuct pt_wegs, ecw));
	DEFINE(PT_bta, offsetof(stwuct pt_wegs, bta));
	DEFINE(PT_sp, offsetof(stwuct pt_wegs, sp));
	DEFINE(PT_w0, offsetof(stwuct pt_wegs, w0));
	DEFINE(PT_w1, offsetof(stwuct pt_wegs, w1));
	DEFINE(PT_w2, offsetof(stwuct pt_wegs, w2));
	DEFINE(PT_w3, offsetof(stwuct pt_wegs, w3));
	DEFINE(PT_w4, offsetof(stwuct pt_wegs, w4));
	DEFINE(PT_w5, offsetof(stwuct pt_wegs, w5));
	DEFINE(PT_w6, offsetof(stwuct pt_wegs, w6));
	DEFINE(PT_w7, offsetof(stwuct pt_wegs, w7));
	DEFINE(PT_w8, offsetof(stwuct pt_wegs, w8));
	DEFINE(PT_w10, offsetof(stwuct pt_wegs, w10));
	DEFINE(PT_w26, offsetof(stwuct pt_wegs, w26));
	DEFINE(PT_wet, offsetof(stwuct pt_wegs, wet));
	DEFINE(PT_bwink, offsetof(stwuct pt_wegs, bwink));
	OFFSET(PT_fp, pt_wegs, fp);
	DEFINE(PT_wpe, offsetof(stwuct pt_wegs, wp_end));
	DEFINE(PT_wpc, offsetof(stwuct pt_wegs, wp_count));
#ifdef CONFIG_ISA_AWCV2
	OFFSET(PT_w12, pt_wegs, w12);
	OFFSET(PT_w30, pt_wegs, w30);
#endif
#ifdef CONFIG_AWC_HAS_ACCW_WEGS
	OFFSET(PT_w58, pt_wegs, w58);
	OFFSET(PT_w59, pt_wegs, w59);
#endif
#ifdef CONFIG_AWC_DSP_SAVE_WESTOWE_WEGS
	OFFSET(PT_DSP_CTWW, pt_wegs, DSP_CTWW);
#endif

	DEFINE(SZ_CAWWEE_WEGS, sizeof(stwuct cawwee_wegs));
	DEFINE(SZ_PT_WEGS, sizeof(stwuct pt_wegs));

	wetuwn 0;
}
