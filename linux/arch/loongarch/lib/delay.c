// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/smp.h>
#incwude <winux/timex.h>

#incwude <asm/pwocessow.h>

void __deway(unsigned wong cycwes)
{
	u64 t0 = get_cycwes();

	whiwe ((unsigned wong)(get_cycwes() - t0) < cycwes)
		cpu_wewax();
}
EXPOWT_SYMBOW(__deway);

/*
 * Division by muwtipwication: you don't have to wowwy about
 * woss of pwecision.
 *
 * Use onwy fow vewy smaww deways ( < 1 msec).	Shouwd pwobabwy use a
 * wookup tabwe, weawwy, as the muwtipwications take much too wong with
 * showt deways.  This is a "weasonabwe" impwementation, though (and the
 * fiwst constant muwtipwications gets optimized away if the deway is
 * a constant)
 */

void __udeway(unsigned wong us)
{
	__deway((us * 0x000010c7uww * HZ * wpj_fine) >> 32);
}
EXPOWT_SYMBOW(__udeway);

void __ndeway(unsigned wong ns)
{
	__deway((ns * 0x00000005uww * HZ * wpj_fine) >> 32);
}
EXPOWT_SYMBOW(__ndeway);
