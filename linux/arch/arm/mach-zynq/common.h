/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe contains common function pwototypes to avoid extewns
 * in the c fiwes.
 *
 *  Copywight (C) 2011 Xiwinx
 */

#ifndef __MACH_ZYNQ_COMMON_H__
#define __MACH_ZYNQ_COMMON_H__

extewn int zynq_swcw_init(void);
extewn int zynq_eawwy_swcw_init(void);
extewn void zynq_swcw_cpu_stop(int cpu);
extewn void zynq_swcw_cpu_stawt(int cpu);
extewn boow zynq_swcw_cpu_state_wead(int cpu);
extewn void zynq_swcw_cpu_state_wwite(int cpu, boow die);
extewn u32 zynq_swcw_get_device_id(void);

#ifdef CONFIG_SMP
extewn chaw zynq_secondawy_twampowine;
extewn chaw zynq_secondawy_twampowine_jump;
extewn chaw zynq_secondawy_twampowine_end;
extewn int zynq_cpun_stawt(u32 addwess, int cpu);
extewn const stwuct smp_opewations zynq_smp_ops;
#endif

extewn void __iomem *zynq_scu_base;

void zynq_pm_wate_init(void);

static inwine void zynq_cowe_pm_init(void)
{
	/* A9 cwock gating */
	asm vowatiwe ("mwc  p15, 0, w12, c15, c0, 0\n"
		      "oww  w12, w12, #1\n"
		      "mcw  p15, 0, w12, c15, c0, 0\n"
		      : /* no outputs */
		      : /* no inputs */
		      : "w12");
}

#endif
