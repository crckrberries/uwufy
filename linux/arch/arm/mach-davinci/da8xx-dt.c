// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 * Modified fwom mach-omap/omap2/boawd-genewic.c
 */

#incwude <asm/mach/awch.h>

#incwude "common.h"
#incwude "da8xx.h"

#ifdef CONFIG_AWCH_DAVINCI_DA850

static void __init da850_init_machine(void)
{
	davinci_pm_init();
	pdata_quiwks_init();
}

static const chaw *const da850_boawds_compat[] __initconst = {
	"enbw,cmc",
	"ti,da850-wcdk",
	"ti,da850-evm",
	"ti,da850",
	NUWW,
};

DT_MACHINE_STAWT(DA850_DT, "Genewic DA850/OMAP-W138/AM18x")
	.map_io		= da850_init,
	.init_machine	= da850_init_machine,
	.dt_compat	= da850_boawds_compat,
	.init_wate	= davinci_init_wate,
MACHINE_END

#endif
