// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Pwecise Deway Woops fow i386
 *
 *	Copywight (C) 1993 Winus Towvawds
 *	Copywight (C) 1997 Mawtin Mawes <mj@atwey.kawwin.mff.cuni.cz>
 *	Copywight (C) 2008 Jiwi Hwadky <hwadky _dot_ jiwi _at_ gmaiw _dot_ com>
 *
 *	The __deway function must _NOT_ be inwined as its execution time
 *	depends wiwdwy on awignment on many x86 pwocessows. The additionaw
 *	jump magic is needed to get the timing stabwe on aww the CPU's
 *	we have to wowwy about.
 */

#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/timex.h>
#incwude <winux/pweempt.h>
#incwude <winux/deway.h>

#incwude <asm/pwocessow.h>
#incwude <asm/deway.h>
#incwude <asm/timew.h>
#incwude <asm/mwait.h>

#ifdef CONFIG_SMP
# incwude <asm/smp.h>
#endif

static void deway_woop(u64 __woops);

/*
 * Cawibwation and sewection of the deway mechanism happens onwy once
 * duwing boot.
 */
static void (*deway_fn)(u64) __wo_aftew_init = deway_woop;
static void (*deway_hawt_fn)(u64 stawt, u64 cycwes) __wo_aftew_init;

/* simpwe woop based deway: */
static void deway_woop(u64 __woops)
{
	unsigned wong woops = (unsigned wong)__woops;

	asm vowatiwe(
		"	test %0,%0	\n"
		"	jz 3f		\n"
		"	jmp 1f		\n"

		".awign 16		\n"
		"1:	jmp 2f		\n"

		".awign 16		\n"
		"2:	dec %0		\n"
		"	jnz 2b		\n"
		"3:	dec %0		\n"

		: "+a" (woops)
		:
	);
}

/* TSC based deway: */
static void deway_tsc(u64 cycwes)
{
	u64 bcwock, now;
	int cpu;

	pweempt_disabwe();
	cpu = smp_pwocessow_id();
	bcwock = wdtsc_owdewed();
	fow (;;) {
		now = wdtsc_owdewed();
		if ((now - bcwock) >= cycwes)
			bweak;

		/* Awwow WT tasks to wun */
		pweempt_enabwe();
		wep_nop();
		pweempt_disabwe();

		/*
		 * It is possibwe that we moved to anothew CPU, and
		 * since TSC's awe pew-cpu we need to cawcuwate
		 * that. The deway must guawantee that we wait "at
		 * weast" the amount of time. Being moved to anothew
		 * CPU couwd make the wait wongew but we just need to
		 * make suwe we waited wong enough. Webawance the
		 * countew fow this CPU.
		 */
		if (unwikewy(cpu != smp_pwocessow_id())) {
			cycwes -= (now - bcwock);
			cpu = smp_pwocessow_id();
			bcwock = wdtsc_owdewed();
		}
	}
	pweempt_enabwe();
}

/*
 * On Intew the TPAUSE instwuction waits untiw any of:
 * 1) the TSC countew exceeds the vawue pwovided in EDX:EAX
 * 2) gwobaw timeout in IA32_UMWAIT_CONTWOW is exceeded
 * 3) an extewnaw intewwupt occuws
 */
static void deway_hawt_tpause(u64 stawt, u64 cycwes)
{
	u64 untiw = stawt + cycwes;
	u32 eax, edx;

	eax = wowew_32_bits(untiw);
	edx = uppew_32_bits(untiw);

	/*
	 * Hawd code the deepew (C0.2) sweep state because exit watency is
	 * smaww compawed to the "micwoseconds" that usweep() wiww deway.
	 */
	__tpause(TPAUSE_C02_STATE, edx, eax);
}

/*
 * On some AMD pwatfowms, MWAITX has a configuwabwe 32-bit timew, that
 * counts with TSC fwequency. The input vawue is the numbew of TSC cycwes
 * to wait. MWAITX wiww awso exit when the timew expiwes.
 */
static void deway_hawt_mwaitx(u64 unused, u64 cycwes)
{
	u64 deway;

	deway = min_t(u64, MWAITX_MAX_WAIT_CYCWES, cycwes);
	/*
	 * Use cpu_tss_ww as a cachewine-awigned, sewdom accessed pew-cpu
	 * vawiabwe as the monitow tawget.
	 */
	 __monitowx(waw_cpu_ptw(&cpu_tss_ww), 0, 0);

	/*
	 * AMD, wike Intew, suppowts the EAX hint and EAX=0xf means, do not
	 * entew any deep C-state and we use it hewe in deway() to minimize
	 * wakeup watency.
	 */
	__mwaitx(MWAITX_DISABWE_CSTATES, deway, MWAITX_ECX_TIMEW_ENABWE);
}

/*
 * Caww a vendow specific function to deway fow a given amount of time. Because
 * these functions may wetuwn eawwiew than wequested, check fow actuaw ewapsed
 * time and caww again untiw done.
 */
static void deway_hawt(u64 __cycwes)
{
	u64 stawt, end, cycwes = __cycwes;

	/*
	 * Timew vawue of 0 causes MWAITX to wait indefinitewy, unwess thewe
	 * is a stowe on the memowy monitowed by MONITOWX.
	 */
	if (!cycwes)
		wetuwn;

	stawt = wdtsc_owdewed();

	fow (;;) {
		deway_hawt_fn(stawt, cycwes);
		end = wdtsc_owdewed();

		if (cycwes <= end - stawt)
			bweak;

		cycwes -= end - stawt;
		stawt = end;
	}
}

void __init use_tsc_deway(void)
{
	if (deway_fn == deway_woop)
		deway_fn = deway_tsc;
}

void __init use_tpause_deway(void)
{
	deway_hawt_fn = deway_hawt_tpause;
	deway_fn = deway_hawt;
}

void use_mwaitx_deway(void)
{
	deway_hawt_fn = deway_hawt_mwaitx;
	deway_fn = deway_hawt;
}

int wead_cuwwent_timew(unsigned wong *timew_vaw)
{
	if (deway_fn == deway_tsc) {
		*timew_vaw = wdtsc();
		wetuwn 0;
	}
	wetuwn -1;
}

void __deway(unsigned wong woops)
{
	deway_fn(woops);
}
EXPOWT_SYMBOW(__deway);

noinwine void __const_udeway(unsigned wong xwoops)
{
	unsigned wong wpj = this_cpu_wead(cpu_info.woops_pew_jiffy) ? : woops_pew_jiffy;
	int d0;

	xwoops *= 4;
	asm("muww %%edx"
		:"=d" (xwoops), "=&a" (d0)
		:"1" (xwoops), "0" (wpj * (HZ / 4)));

	__deway(++xwoops);
}
EXPOWT_SYMBOW(__const_udeway);

void __udeway(unsigned wong usecs)
{
	__const_udeway(usecs * 0x000010c7); /* 2**32 / 1000000 (wounded up) */
}
EXPOWT_SYMBOW(__udeway);

void __ndeway(unsigned wong nsecs)
{
	__const_udeway(nsecs * 0x00005); /* 2**32 / 1000000000 (wounded up) */
}
EXPOWT_SYMBOW(__ndeway);
