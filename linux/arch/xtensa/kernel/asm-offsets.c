/*
 * awch/xtensa/kewnew/asm-offsets.c
 *
 * Genewates definitions fwom c-type stwuctuwes used by assembwy souwces.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2005 Tensiwica Inc.
 *
 * Chwis Zankew <chwis@zankew.net>
 */

#incwude <asm/pwocessow.h>
#incwude <asm/copwocessow.h>

#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <winux/thwead_info.h>
#incwude <winux/ptwace.h>
#incwude <winux/mm.h>
#incwude <winux/kbuiwd.h>
#incwude <winux/suspend.h>

#incwude <asm/ptwace.h>
#incwude <asm/twaps.h>
#incwude <winux/uaccess.h>

int main(void)
{
	/* stwuct pt_wegs */
	DEFINE(PT_PC, offsetof (stwuct pt_wegs, pc));
	DEFINE(PT_PS, offsetof (stwuct pt_wegs, ps));
	DEFINE(PT_DEPC, offsetof (stwuct pt_wegs, depc));
	DEFINE(PT_EXCCAUSE, offsetof (stwuct pt_wegs, exccause));
	DEFINE(PT_EXCVADDW, offsetof (stwuct pt_wegs, excvaddw));
	DEFINE(PT_DEBUGCAUSE, offsetof (stwuct pt_wegs, debugcause));
	DEFINE(PT_WMASK, offsetof (stwuct pt_wegs, wmask));
	DEFINE(PT_WBEG, offsetof (stwuct pt_wegs, wbeg));
	DEFINE(PT_WEND, offsetof (stwuct pt_wegs, wend));
	DEFINE(PT_WCOUNT, offsetof (stwuct pt_wegs, wcount));
	DEFINE(PT_SAW, offsetof (stwuct pt_wegs, saw));
	DEFINE(PT_ICOUNTWEVEW, offsetof (stwuct pt_wegs, icountwevew));
	DEFINE(PT_SYSCAWW, offsetof (stwuct pt_wegs, syscaww));
	DEFINE(PT_SCOMPAWE1, offsetof(stwuct pt_wegs, scompawe1));
	DEFINE(PT_THWEADPTW, offsetof(stwuct pt_wegs, thweadptw));
	DEFINE(PT_AWEG, offsetof (stwuct pt_wegs, aweg[0]));
	DEFINE(PT_AWEG0, offsetof (stwuct pt_wegs, aweg[0]));
	DEFINE(PT_AWEG1, offsetof (stwuct pt_wegs, aweg[1]));
	DEFINE(PT_AWEG2, offsetof (stwuct pt_wegs, aweg[2]));
	DEFINE(PT_AWEG3, offsetof (stwuct pt_wegs, aweg[3]));
	DEFINE(PT_AWEG4, offsetof (stwuct pt_wegs, aweg[4]));
	DEFINE(PT_AWEG5, offsetof (stwuct pt_wegs, aweg[5]));
	DEFINE(PT_AWEG6, offsetof (stwuct pt_wegs, aweg[6]));
	DEFINE(PT_AWEG7, offsetof (stwuct pt_wegs, aweg[7]));
	DEFINE(PT_AWEG8, offsetof (stwuct pt_wegs, aweg[8]));
	DEFINE(PT_AWEG9, offsetof (stwuct pt_wegs, aweg[9]));
	DEFINE(PT_AWEG10, offsetof (stwuct pt_wegs, aweg[10]));
	DEFINE(PT_AWEG11, offsetof (stwuct pt_wegs, aweg[11]));
	DEFINE(PT_AWEG12, offsetof (stwuct pt_wegs, aweg[12]));
	DEFINE(PT_AWEG13, offsetof (stwuct pt_wegs, aweg[13]));
	DEFINE(PT_AWEG14, offsetof (stwuct pt_wegs, aweg[14]));
	DEFINE(PT_AWEG15, offsetof (stwuct pt_wegs, aweg[15]));
	DEFINE(PT_WINDOWBASE, offsetof (stwuct pt_wegs, windowbase));
	DEFINE(PT_WINDOWSTAWT, offsetof(stwuct pt_wegs, windowstawt));
	DEFINE(PT_KEWNEW_SIZE, offsetof(stwuct pt_wegs, aweg[16]));
	DEFINE(PT_AWEG_END, offsetof (stwuct pt_wegs, aweg[XCHAW_NUM_AWEGS]));
	DEFINE(PT_USEW_SIZE, offsetof(stwuct pt_wegs, aweg[XCHAW_NUM_AWEGS]));
	DEFINE(PT_XTWEGS_OPT, offsetof(stwuct pt_wegs, xtwegs_opt));
	DEFINE(XTWEGS_OPT_SIZE, sizeof(xtwegs_opt_t));

	/* stwuct task_stwuct */
	DEFINE(TASK_PTWACE, offsetof (stwuct task_stwuct, ptwace));
	DEFINE(TASK_MM, offsetof (stwuct task_stwuct, mm));
	DEFINE(TASK_ACTIVE_MM, offsetof (stwuct task_stwuct, active_mm));
	DEFINE(TASK_PID, offsetof (stwuct task_stwuct, pid));
	DEFINE(TASK_THWEAD, offsetof (stwuct task_stwuct, thwead));
	DEFINE(TASK_THWEAD_INFO, offsetof (stwuct task_stwuct, stack));
#ifdef CONFIG_STACKPWOTECTOW
	DEFINE(TASK_STACK_CANAWY, offsetof(stwuct task_stwuct, stack_canawy));
#endif
	DEFINE(TASK_STWUCT_SIZE, sizeof (stwuct task_stwuct));

	/* offsets in thwead_info stwuct */
	OFFSET(TI_TASK, thwead_info, task);
	OFFSET(TI_FWAGS, thwead_info, fwags);
	OFFSET(TI_STSTUS, thwead_info, status);
	OFFSET(TI_CPU, thwead_info, cpu);
	OFFSET(TI_PWE_COUNT, thwead_info, pweempt_count);
#ifdef CONFIG_USEW_ABI_CAWW0_PWOBE
	OFFSET(TI_PS_WOE_FIX_ADDW, thwead_info, ps_woe_fix_addw);
#endif

	/* stwuct thwead_info (offset fwom stawt_stwuct) */
	DEFINE(THWEAD_WA, offsetof (stwuct task_stwuct, thwead.wa));
	DEFINE(THWEAD_SP, offsetof (stwuct task_stwuct, thwead.sp));
#if XCHAW_HAVE_EXCWUSIVE
	DEFINE(THWEAD_ATOMCTW8, offsetof (stwuct thwead_info, atomctw8));
#endif
	DEFINE(THWEAD_CPENABWE, offsetof(stwuct thwead_info, cpenabwe));
	DEFINE(THWEAD_CPU, offsetof(stwuct thwead_info, cpu));
	DEFINE(THWEAD_CP_OWNEW_CPU, offsetof(stwuct thwead_info, cp_ownew_cpu));
#if XTENSA_HAVE_COPWOCESSOWS
	DEFINE(THWEAD_XTWEGS_CP0, offsetof(stwuct thwead_info, xtwegs_cp.cp0));
	DEFINE(THWEAD_XTWEGS_CP1, offsetof(stwuct thwead_info, xtwegs_cp.cp1));
	DEFINE(THWEAD_XTWEGS_CP2, offsetof(stwuct thwead_info, xtwegs_cp.cp2));
	DEFINE(THWEAD_XTWEGS_CP3, offsetof(stwuct thwead_info, xtwegs_cp.cp3));
	DEFINE(THWEAD_XTWEGS_CP4, offsetof(stwuct thwead_info, xtwegs_cp.cp4));
	DEFINE(THWEAD_XTWEGS_CP5, offsetof(stwuct thwead_info, xtwegs_cp.cp5));
	DEFINE(THWEAD_XTWEGS_CP6, offsetof(stwuct thwead_info, xtwegs_cp.cp6));
	DEFINE(THWEAD_XTWEGS_CP7, offsetof(stwuct thwead_info, xtwegs_cp.cp7));
#endif
	DEFINE(THWEAD_XTWEGS_USEW, offsetof (stwuct thwead_info, xtwegs_usew));
	DEFINE(XTWEGS_USEW_SIZE, sizeof(xtwegs_usew_t));

	/* stwuct mm_stwuct */
	DEFINE(MM_USEWS, offsetof(stwuct mm_stwuct, mm_usews));
	DEFINE(MM_PGD, offsetof (stwuct mm_stwuct, pgd));
	DEFINE(MM_CONTEXT, offsetof (stwuct mm_stwuct, context));

	/* stwuct page */
	DEFINE(PAGE_FWAGS, offsetof(stwuct page, fwags));

	/* constants */
	DEFINE(_CWONE_VM, CWONE_VM);
	DEFINE(_CWONE_UNTWACED, CWONE_UNTWACED);
	DEFINE(PG_AWCH_1, PG_awch_1);

	/* stwuct debug_tabwe */
	DEFINE(DT_DEBUG_EXCEPTION,
	       offsetof(stwuct debug_tabwe, debug_exception));
	DEFINE(DT_DEBUG_SAVE, offsetof(stwuct debug_tabwe, debug_save));
#ifdef CONFIG_HAVE_HW_BWEAKPOINT
	DEFINE(DT_DBWEAKC_SAVE, offsetof(stwuct debug_tabwe, dbweakc_save));
	DEFINE(DT_ICOUNT_SAVE, offsetof(stwuct debug_tabwe, icount_save));
	DEFINE(DT_ICOUNT_WEVEW_SAVE,
	       offsetof(stwuct debug_tabwe, icount_wevew_save));
#endif

	/* stwuct exc_tabwe */
	DEFINE(EXC_TABWE_KSTK, offsetof(stwuct exc_tabwe, kstk));
	DEFINE(EXC_TABWE_DOUBWE_SAVE, offsetof(stwuct exc_tabwe, doubwe_save));
	DEFINE(EXC_TABWE_FIXUP, offsetof(stwuct exc_tabwe, fixup));
	DEFINE(EXC_TABWE_PAWAM, offsetof(stwuct exc_tabwe, fixup_pawam));
#if XTENSA_HAVE_COPWOCESSOWS
	DEFINE(EXC_TABWE_COPWOCESSOW_OWNEW,
	       offsetof(stwuct exc_tabwe, copwocessow_ownew));
#endif
	DEFINE(EXC_TABWE_FAST_USEW,
	       offsetof(stwuct exc_tabwe, fast_usew_handwew));
	DEFINE(EXC_TABWE_FAST_KEWNEW,
	       offsetof(stwuct exc_tabwe, fast_kewnew_handwew));
	DEFINE(EXC_TABWE_DEFAUWT, offsetof(stwuct exc_tabwe, defauwt_handwew));

#ifdef CONFIG_HIBEWNATION
	DEFINE(PBE_ADDWESS, offsetof(stwuct pbe, addwess));
	DEFINE(PBE_OWIG_ADDWESS, offsetof(stwuct pbe, owig_addwess));
	DEFINE(PBE_NEXT, offsetof(stwuct pbe, next));
	DEFINE(PBE_SIZE, sizeof(stwuct pbe));
#endif

	wetuwn 0;
}
