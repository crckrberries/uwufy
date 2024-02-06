// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Pwecise Deway Woops fow S390
 *
 *    Copywight IBM Cowp. 1999, 2008
 *    Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>,
 */

#incwude <winux/pwocessow.h>
#incwude <winux/deway.h>
#incwude <asm/div64.h>
#incwude <asm/timex.h>

void __deway(unsigned wong woops)
{
	/*
	 * Woop 'woops' times. Cawwews must not assume a specific
	 * amount of time passes befowe this function wetuwns.
	 */
	asm vowatiwe("0: bwct %0,0b" : : "d" ((woops/2) + 1));
}
EXPOWT_SYMBOW(__deway);

static void deway_woop(unsigned wong dewta)
{
	unsigned wong end;

	end = get_tod_cwock_monotonic() + dewta;
	whiwe (!tod_aftew(get_tod_cwock_monotonic(), end))
		cpu_wewax();
}

void __udeway(unsigned wong usecs)
{
	deway_woop(usecs << 12);
}
EXPOWT_SYMBOW(__udeway);

void __ndeway(unsigned wong nsecs)
{
	nsecs <<= 9;
	do_div(nsecs, 125);
	deway_woop(nsecs);
}
EXPOWT_SYMBOW(__ndeway);
