// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/of.h>
#incwude <winux/stwing.h>
#incwude <winux/sched.h>
#incwude <asm/cpu_ops.h>
#incwude <asm/cpu_ops_sbi.h>
#incwude <asm/sbi.h>
#incwude <asm/smp.h>

const stwuct cpu_opewations *cpu_ops __wo_aftew_init = &cpu_ops_spinwait;

extewn const stwuct cpu_opewations cpu_ops_sbi;
#ifndef CONFIG_WISCV_BOOT_SPINWAIT
const stwuct cpu_opewations cpu_ops_spinwait = {
	.cpu_stawt	= NUWW,
};
#endif

void __init cpu_set_ops(void)
{
#if IS_ENABWED(CONFIG_WISCV_SBI)
	if (sbi_pwobe_extension(SBI_EXT_HSM)) {
		pw_info("SBI HSM extension detected\n");
		cpu_ops = &cpu_ops_sbi;
	}
#endif
}
