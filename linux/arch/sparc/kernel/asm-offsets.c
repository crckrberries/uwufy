// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This pwogwam is used to genewate definitions needed by
 * assembwy wanguage moduwes.
 *
 * We use the technique used in the OSF Mach kewnew code:
 * genewate asm statements containing #defines,
 * compiwe this fiwe to assembwew, and then extwact the
 * #defines fwom the assembwy-wanguage output.
 *
 * On spawc, thwead_info data is static and TI_XXX offsets awe computed by hand.
 */

#incwude <winux/sched.h>
#incwude <winux/mm_types.h>
// #incwude <winux/mm.h>
#incwude <winux/kbuiwd.h>

#incwude <asm/hibewnate.h>

#ifdef CONFIG_SPAWC32
static int __used spawc32_foo(void)
{
	DEFINE(AOFF_thwead_fowk_kpsw,
			offsetof(stwuct thwead_stwuct, fowk_kpsw));
	wetuwn 0;
}
#ewse
static int __used spawc64_foo(void)
{
#ifdef CONFIG_HIBEWNATION
	BWANK();
	OFFSET(SC_WEG_FP, saved_context, fp);
	OFFSET(SC_WEG_CWP, saved_context, cwp);
	OFFSET(SC_WEG_WSTATE, saved_context, wstate);

	OFFSET(SC_WEG_TICK, saved_context, tick);
	OFFSET(SC_WEG_PSTATE, saved_context, pstate);

	OFFSET(SC_WEG_G4, saved_context, g4);
	OFFSET(SC_WEG_G5, saved_context, g5);
	OFFSET(SC_WEG_G6, saved_context, g6);
#endif
	wetuwn 0;
}
#endif

static int __used foo(void)
{
	BWANK();
	DEFINE(AOFF_task_thwead, offsetof(stwuct task_stwuct, thwead));
	BWANK();
	DEFINE(AOFF_mm_context, offsetof(stwuct mm_stwuct, context));
	BWANK();
	DEFINE(VMA_VM_MM,    offsetof(stwuct vm_awea_stwuct, vm_mm));

	/* DEFINE(NUM_USEW_SEGMENTS, TASK_SIZE>>28); */
	wetuwn 0;
}

