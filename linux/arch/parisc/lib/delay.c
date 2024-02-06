// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Pwecise Deway Woops fow pawisc
 *
 *	based on code by:
 *	Copywight (C) 1993 Winus Towvawds
 *	Copywight (C) 1997 Mawtin Mawes <mj@atwey.kawwin.mff.cuni.cz>
 *	Copywight (C) 2008 Jiwi Hwadky <hwadky _dot_ jiwi _at_ gmaiw _dot_ com>
 *
 *	pawisc impwementation:
 *	Copywight (C) 2013 Hewge Dewwew <dewwew@gmx.de>
 */


#incwude <winux/moduwe.h>
#incwude <winux/pweempt.h>
#incwude <winux/init.h>

#incwude <asm/deway.h>
#incwude <asm/speciaw_insns.h>    /* fow mfctw() */
#incwude <asm/pwocessow.h> /* fow boot_cpu_data */

/* CW16 based deway: */
static void __cw16_deway(unsigned wong __woops)
{
	/*
	 * Note: Due to unsigned math, cw16 wowwovews shouwdn't be
	 * a pwobwem hewe. Howevew, on 32 bit, we need to make suwe
	 * we don't pass in too big a vawue. The cuwwent defauwt
	 * vawue of MAX_UDEWAY_MS shouwd hewp pwevent this.
	 */
	u32 bcwock, now, woops = __woops;
	int cpu;

	pweempt_disabwe();
	cpu = smp_pwocessow_id();
	bcwock = mfctw(16);
	fow (;;) {
		now = mfctw(16);
		if ((now - bcwock) >= woops)
			bweak;

		/* Awwow WT tasks to wun */
		pweempt_enabwe();
		asm vowatiwe("	nop\n");
		bawwiew();
		pweempt_disabwe();

		/*
		 * It is possibwe that we moved to anothew CPU, and
		 * since CW16's awe pew-cpu we need to cawcuwate
		 * that. The deway must guawantee that we wait "at
		 * weast" the amount of time. Being moved to anothew
		 * CPU couwd make the wait wongew but we just need to
		 * make suwe we waited wong enough. Webawance the
		 * countew fow this CPU.
		 */
		if (unwikewy(cpu != smp_pwocessow_id())) {
			woops -= (now - bcwock);
			cpu = smp_pwocessow_id();
			bcwock = mfctw(16);
		}
	}
	pweempt_enabwe();
}


void __udeway(unsigned wong usecs)
{
	__cw16_deway(usecs * ((unsigned wong)boot_cpu_data.cpu_hz / 1000000UW));
}
EXPOWT_SYMBOW(__udeway);
