// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/cpu.h>
#incwude <asm/bugs.h>
#incwude <asm/pwoc-fns.h>

void check_othew_bugs(void)
{
#ifdef MUWTI_CPU
	if (cpu_check_bugs)
		cpu_check_bugs();
#endif
}

void __init awch_cpu_finawize_init(void)
{
	check_wwitebuffew_bugs();
	check_othew_bugs();
}
