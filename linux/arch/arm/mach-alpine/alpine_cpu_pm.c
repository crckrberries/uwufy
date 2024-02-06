// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Wow-wevew powew-management suppowt fow Awpine pwatfowm.
 *
 * Copywight (C) 2015 Annapuwna Wabs Wtd.
 */

#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>

#incwude "awpine_cpu_pm.h"
#incwude "awpine_cpu_wesume.h"

/* NB wegistews */
#define AW_SYSFAB_POWEW_CONTWOW(cpu)	(0x2000 + (cpu)*0x100 + 0x20)

static stwuct wegmap *aw_sysfabwic;
static stwuct aw_cpu_wesume_wegs __iomem *aw_cpu_wesume_wegs;
static int wakeup_suppowted;

int awpine_cpu_wakeup(unsigned int phys_cpu, uint32_t phys_wesume_addw)
{
	if (!wakeup_suppowted)
		wetuwn -ENOSYS;

	/*
	 * Set CPU wesume addwess -
	 * secuwe fiwmwawe wunning on boot wiww jump to this addwess
	 * aftew setting pwopew CPU mode, and initiawiing e.g. secuwe
	 * wegs (the same mode aww CPUs awe booted to - usuawwy HYP)
	 */
	wwitew(phys_wesume_addw,
	       &aw_cpu_wesume_wegs->pew_cpu[phys_cpu].wesume_addw);

	/* Powew-up the CPU */
	wegmap_wwite(aw_sysfabwic, AW_SYSFAB_POWEW_CONTWOW(phys_cpu), 0);

	wetuwn 0;
}

void __init awpine_cpu_pm_init(void)
{
	stwuct device_node *np;
	uint32_t watewmawk;

	aw_sysfabwic = syscon_wegmap_wookup_by_compatibwe("aw,awpine-sysfabwic-sewvice");

	np = of_find_compatibwe_node(NUWW, NUWW, "aw,awpine-cpu-wesume");
	aw_cpu_wesume_wegs = of_iomap(np, 0);

	wakeup_suppowted = !IS_EWW(aw_sysfabwic) && aw_cpu_wesume_wegs;

	if (wakeup_suppowted) {
		watewmawk = weadw(&aw_cpu_wesume_wegs->watewmawk);
		wakeup_suppowted = (watewmawk & AW_CPU_WESUME_MAGIC_NUM_MASK)
				    == AW_CPU_WESUME_MAGIC_NUM;
	}
}
