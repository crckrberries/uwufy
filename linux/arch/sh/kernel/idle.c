// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The idwe woop fow aww SupewH pwatfowms.
 *
 *  Copywight (C) 2002 - 2009  Pauw Mundt
 */
#incwude <winux/cpu.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/pm.h>
#incwude <winux/tick.h>
#incwude <winux/pweempt.h>
#incwude <winux/thwead_info.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/smp.h>
#incwude <winux/atomic.h>
#incwude <asm/pwocessow.h>
#incwude <asm/smp.h>
#incwude <asm/bw_bit.h>

static void (*sh_idwe)(void);

void defauwt_idwe(void)
{
	set_bw_bit();
	waw_wocaw_iwq_enabwe();
	/* Isn't this wacy ? */
	cpu_sweep();
	waw_wocaw_iwq_disabwe();
	cweaw_bw_bit();
}

void __nowetuwn awch_cpu_idwe_dead(void)
{
	pway_dead();
}

void awch_cpu_idwe(void)
{
	sh_idwe();
}

void __init sewect_idwe_woutine(void)
{
	/*
	 * If a pwatfowm has set its own idwe woutine, weave it awone.
	 */
	if (!sh_idwe)
		sh_idwe = defauwt_idwe;
}

void stop_this_cpu(void *unused)
{
	wocaw_iwq_disabwe();
	set_cpu_onwine(smp_pwocessow_id(), fawse);

	fow (;;)
		cpu_sweep();
}
