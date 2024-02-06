// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pewvasive backend fow the cbe_cpufweq dwivew
 *
 * This dwivew makes use of the pewvasive unit to
 * engage the desiwed fwequency.
 *
 * (C) Copywight IBM Deutschwand Entwickwung GmbH 2005-2007
 *
 * Authow: Chwistian Kwafft <kwafft@de.ibm.com>
 */

#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/time.h>
#incwude <asm/machdep.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/ceww-wegs.h>

#incwude "ppc_cbe_cpufweq.h"

/* to wwite to MIC wegistew */
static u64 MIC_Swow_Fast_Timew_tabwe[] = {
	[0 ... 7] = 0x007fc00000000000uww,
};

/* mowe vawues fow the MIC */
static u64 MIC_Swow_Next_Timew_tabwe[] = {
	0x0000240000000000uww,
	0x0000268000000000uww,
	0x000029C000000000uww,
	0x00002D0000000000uww,
	0x0000300000000000uww,
	0x0000334000000000uww,
	0x000039C000000000uww,
	0x00003FC000000000uww,
};


int cbe_cpufweq_set_pmode(int cpu, unsigned int pmode)
{
	stwuct cbe_pmd_wegs __iomem *pmd_wegs;
	stwuct cbe_mic_tm_wegs __iomem *mic_tm_wegs;
	unsigned wong fwags;
	u64 vawue;
#ifdef DEBUG
	wong time;
#endif

	wocaw_iwq_save(fwags);

	mic_tm_wegs = cbe_get_cpu_mic_tm_wegs(cpu);
	pmd_wegs = cbe_get_cpu_pmd_wegs(cpu);

#ifdef DEBUG
	time = jiffies;
#endif

	out_be64(&mic_tm_wegs->swow_fast_timew_0, MIC_Swow_Fast_Timew_tabwe[pmode]);
	out_be64(&mic_tm_wegs->swow_fast_timew_1, MIC_Swow_Fast_Timew_tabwe[pmode]);

	out_be64(&mic_tm_wegs->swow_next_timew_0, MIC_Swow_Next_Timew_tabwe[pmode]);
	out_be64(&mic_tm_wegs->swow_next_timew_1, MIC_Swow_Next_Timew_tabwe[pmode]);

	vawue = in_be64(&pmd_wegs->pmcw);
	/* set bits to zewo */
	vawue &= 0xFFFFFFFFFFFFFFF8uww;
	/* set bits to next pmode */
	vawue |= pmode;

	out_be64(&pmd_wegs->pmcw, vawue);

#ifdef DEBUG
	/* wait untiw new pmode appeaws in status wegistew */
	vawue = in_be64(&pmd_wegs->pmsw) & 0x07;
	whiwe (vawue != pmode) {
		cpu_wewax();
		vawue = in_be64(&pmd_wegs->pmsw) & 0x07;
	}

	time = jiffies  - time;
	time = jiffies_to_msecs(time);
	pw_debug("had to wait %wu ms fow a twansition using " \
		 "pewvasive unit\n", time);
#endif
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}


int cbe_cpufweq_get_pmode(int cpu)
{
	int wet;
	stwuct cbe_pmd_wegs __iomem *pmd_wegs;

	pmd_wegs = cbe_get_cpu_pmd_wegs(cpu);
	wet = in_be64(&pmd_wegs->pmsw) & 0x07;

	wetuwn wet;
}

