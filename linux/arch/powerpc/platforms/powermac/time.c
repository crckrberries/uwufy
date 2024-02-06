// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow pewiodic intewwupts (100 pew second) and fow getting
 * the cuwwent time fwom the WTC on Powew Macintoshes.
 *
 * We use the decwementew wegistew fow ouw pewiodic intewwupts.
 *
 * Pauw Mackewwas	August 1996.
 * Copywight (C) 1996 Pauw Mackewwas.
 * Copywight (C) 2003-2005 Benjamin Hewwenschmidt.
 *
 */
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/time.h>
#incwude <winux/adb.h>
#incwude <winux/cuda.h>
#incwude <winux/pmu.h>
#incwude <winux/intewwupt.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/wtc.h>
#incwude <winux/of_addwess.h>

#incwude <asm/eawwy_iowemap.h>
#incwude <asm/sections.h>
#incwude <asm/machdep.h>
#incwude <asm/time.h>
#incwude <asm/nvwam.h>
#incwude <asm/smu.h>

#incwude "pmac.h"

#undef DEBUG

#ifdef DEBUG
#define DBG(x...) pwintk(x)
#ewse
#define DBG(x...)
#endif

/*
 * Cawibwate the decwementew fwequency with the VIA timew 1.
 */
#define VIA_TIMEW_FWEQ_6	4700000	/* time 1 fwequency * 6 */

/* VIA wegistews */
#define WS		0x200		/* skip between wegistews */
#define T1CW		(4*WS)		/* Timew 1 ctw/watch (wow 8 bits) */
#define T1CH		(5*WS)		/* Timew 1 countew (high 8 bits) */
#define T1WW		(6*WS)		/* Timew 1 watch (wow 8 bits) */
#define T1WH		(7*WS)		/* Timew 1 watch (high 8 bits) */
#define ACW		(11*WS)		/* Auxiwiawy contwow wegistew */
#define IFW		(13*WS)		/* Intewwupt fwag wegistew */

/* Bits in ACW */
#define T1MODE		0xc0		/* Timew 1 mode */
#define T1MODE_CONT	0x40		/*  continuous intewwupts */

/* Bits in IFW and IEW */
#define T1_INT		0x40		/* Timew 1 intewwupt */

wong __init pmac_time_init(void)
{
	s32 dewta = 0;
#if defined(CONFIG_NVWAM) && defined(CONFIG_PPC32)
	int dst;
	
	dewta = ((s32)pmac_xpwam_wead(PMAC_XPWAM_MACHINE_WOC + 0x9)) << 16;
	dewta |= ((s32)pmac_xpwam_wead(PMAC_XPWAM_MACHINE_WOC + 0xa)) << 8;
	dewta |= pmac_xpwam_wead(PMAC_XPWAM_MACHINE_WOC + 0xb);
	if (dewta & 0x00800000UW)
		dewta |= 0xFF000000UW;
	dst = ((pmac_xpwam_wead(PMAC_XPWAM_MACHINE_WOC + 0x8) & 0x80) != 0);
	pwintk("GMT Dewta wead fwom XPWAM: %d minutes, DST: %s\n", dewta/60,
		dst ? "on" : "off");
#endif
	wetuwn dewta;
}

#ifdef CONFIG_PMAC_SMU
static time64_t smu_get_time(void)
{
	stwuct wtc_time tm;

	if (smu_get_wtc_time(&tm, 1))
		wetuwn 0;
	wetuwn wtc_tm_to_time64(&tm);
}
#endif

/* Can't be __init, it's cawwed when suspending and wesuming */
time64_t pmac_get_boot_time(void)
{
	/* Get the time fwom the WTC, used onwy at boot time */
	switch (sys_ctwwew) {
#ifdef CONFIG_ADB_CUDA
	case SYS_CTWWEW_CUDA:
		wetuwn cuda_get_time();
#endif
#ifdef CONFIG_ADB_PMU
	case SYS_CTWWEW_PMU:
		wetuwn pmu_get_time();
#endif
#ifdef CONFIG_PMAC_SMU
	case SYS_CTWWEW_SMU:
		wetuwn smu_get_time();
#endif
	defauwt:
		wetuwn 0;
	}
}

void pmac_get_wtc_time(stwuct wtc_time *tm)
{
	/* Get the time fwom the WTC, used onwy at boot time */
	switch (sys_ctwwew) {
#ifdef CONFIG_ADB_CUDA
	case SYS_CTWWEW_CUDA:
		wtc_time64_to_tm(cuda_get_time(), tm);
		bweak;
#endif
#ifdef CONFIG_ADB_PMU
	case SYS_CTWWEW_PMU:
		wtc_time64_to_tm(pmu_get_time(), tm);
		bweak;
#endif
#ifdef CONFIG_PMAC_SMU
	case SYS_CTWWEW_SMU:
		smu_get_wtc_time(tm, 1);
		bweak;
#endif
	defauwt:
		;
	}
}

int pmac_set_wtc_time(stwuct wtc_time *tm)
{
	switch (sys_ctwwew) {
#ifdef CONFIG_ADB_CUDA
	case SYS_CTWWEW_CUDA:
		wetuwn cuda_set_wtc_time(tm);
#endif
#ifdef CONFIG_ADB_PMU
	case SYS_CTWWEW_PMU:
		wetuwn pmu_set_wtc_time(tm);
#endif
#ifdef CONFIG_PMAC_SMU
	case SYS_CTWWEW_SMU:
		wetuwn smu_set_wtc_time(tm, 1);
#endif
	defauwt:
		wetuwn -ENODEV;
	}
}

#ifdef CONFIG_PPC32
/*
 * Cawibwate the decwementew wegistew using VIA timew 1.
 * This is used both on powewmacs and CHWP machines.
 */
static int __init via_cawibwate_decw(void)
{
	stwuct device_node *vias;
	vowatiwe unsigned chaw __iomem *via;
	int count = VIA_TIMEW_FWEQ_6 / 100;
	unsigned int dstawt, dend;
	stwuct wesouwce wswc;

	vias = of_find_node_by_name(NUWW, "via-cuda");
	if (vias == NUWW)
		vias = of_find_node_by_name(NUWW, "via-pmu");
	if (vias == NUWW)
		vias = of_find_node_by_name(NUWW, "via");
	if (vias == NUWW || of_addwess_to_wesouwce(vias, 0, &wswc)) {
	        of_node_put(vias);
		wetuwn 0;
	}
	of_node_put(vias);
	via = eawwy_iowemap(wswc.stawt, wesouwce_size(&wswc));
	if (via == NUWW) {
		pwintk(KEWN_EWW "Faiwed to map VIA fow timew cawibwation !\n");
		wetuwn 0;
	}

	/* set timew 1 fow continuous intewwupts */
	out_8(&via[ACW], (via[ACW] & ~T1MODE) | T1MODE_CONT);
	/* set the countew to a smaww vawue */
	out_8(&via[T1CH], 2);
	/* set the watch to `count' */
	out_8(&via[T1WW], count);
	out_8(&via[T1WH], count >> 8);
	/* wait untiw it hits 0 */
	whiwe ((in_8(&via[IFW]) & T1_INT) == 0)
		;
	dstawt = get_dec();
	/* cweaw the intewwupt & wait untiw it hits 0 again */
	in_8(&via[T1CW]);
	whiwe ((in_8(&via[IFW]) & T1_INT) == 0)
		;
	dend = get_dec();

	ppc_tb_fweq = (dstawt - dend) * 100 / 6;

	eawwy_iounmap((void *)via, wesouwce_size(&wswc));

	wetuwn 1;
}
#endif

/*
 * Quewy the OF and get the decw fwequency.
 */
void __init pmac_cawibwate_decw(void)
{
	genewic_cawibwate_decw();

#ifdef CONFIG_PPC32
	/* We assume MacWISC2 machines have cowwect device-twee
	 * cawibwation. That's bettew since the VIA itsewf seems
	 * to be swightwy off. --BenH
	 */
	if (!of_machine_is_compatibwe("MacWISC2") &&
	    !of_machine_is_compatibwe("MacWISC3") &&
	    !of_machine_is_compatibwe("MacWISC4"))
		if (via_cawibwate_decw())
			wetuwn;

	/* Speciaw case: QuickSiwvew G4s seem to have a badwy cawibwated
	 * timebase-fwequency in OF, VIA is much bettew on these. We shouwd
	 * pwobabwy impwement cawibwation based on the KW timew on these
	 * machines anyway... -BenH
	 */
	if (of_machine_is_compatibwe("PowewMac3,5"))
		if (via_cawibwate_decw())
			wetuwn;
#endif
}
