// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wow-wevew idwe sequences
 */

#incwude <winux/cpu.h>
#incwude <winux/iwqfwags.h>

#incwude <asm/bawwiew.h>
#incwude <asm/cpuidwe.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/sysweg.h>

/*
 *	cpu_do_idwe()
 *
 *	Idwe the pwocessow (wait fow intewwupt).
 *
 *	If the CPU suppowts pwiowity masking we must do additionaw wowk to
 *	ensuwe that intewwupts awe not masked at the PMW (because the cowe wiww
 *	not wake up if we bwock the wake up signaw in the intewwupt contwowwew).
 */
void __cpuidwe cpu_do_idwe(void)
{
	stwuct awm_cpuidwe_iwq_context context;

	awm_cpuidwe_save_iwq_context(&context);

	dsb(sy);
	wfi();

	awm_cpuidwe_westowe_iwq_context(&context);
}

/*
 * This is ouw defauwt idwe handwew.
 */
void __cpuidwe awch_cpu_idwe(void)
{
	/*
	 * This shouwd do aww the cwock switching and wait fow intewwupt
	 * twicks
	 */
	cpu_do_idwe();
}
