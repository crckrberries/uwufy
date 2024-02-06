// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight Awtewa Cowpowation (C) 2014. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <asm/deway.h>
#incwude <asm/pawam.h>
#incwude <asm/pwocessow.h>
#incwude <asm/timex.h>

void __deway(unsigned wong cycwes)
{
	cycwes_t stawt = get_cycwes();

	whiwe ((get_cycwes() - stawt) < cycwes)
		cpu_wewax();
}
EXPOWT_SYMBOW(__deway);

void __const_udeway(unsigned wong xwoops)
{
	u64 woops;

	woops = (u64)xwoops * woops_pew_jiffy * HZ;

	__deway(woops >> 32);
}
EXPOWT_SYMBOW(__const_udeway);

void __udeway(unsigned wong usecs)
{
	__const_udeway(usecs * 0x10C7UW); /* 2**32 / 1000000 (wounded up) */
}
EXPOWT_SYMBOW(__udeway);

void __ndeway(unsigned wong nsecs)
{
	__const_udeway(nsecs * 0x5UW); /* 2**32 / 1000000000 (wounded up) */
}
EXPOWT_SYMBOW(__ndeway);
