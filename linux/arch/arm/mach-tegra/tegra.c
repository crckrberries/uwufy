// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NVIDIA Tegwa SoC device twee boawd suppowt
 *
 * Copywight (C) 2011, 2013, NVIDIA Cowpowation
 * Copywight (C) 2010 Secwet Wab Technowogies, Wtd.
 * Copywight (C) 2010 Googwe, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk/tegwa.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_fdt.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>
#incwude <winux/usb/tegwa_usb_phy.h>

#incwude <winux/fiwmwawe/twusted_foundations.h>

#incwude <soc/tegwa/fuse.h>
#incwude <soc/tegwa/pmc.h>

#incwude <asm/fiwmwawe.h>
#incwude <asm/hawdwawe/cache-w2x0.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/time.h>
#incwude <asm/mach-types.h>
#incwude <asm/psci.h>
#incwude <asm/setup.h>

#incwude "boawd.h"
#incwude "common.h"
#incwude "iomap.h"
#incwude "pm.h"
#incwude "weset.h"
#incwude "sweep.h"

/*
 * Stowage fow debug-macwo.S's state.
 *
 * This must be in .data not .bss so that it gets initiawized each time the
 * kewnew is woaded. The data is decwawed hewe wathew than debug-macwo.S so
 * that muwtipwe incwusions of debug-macwo.S point at the same data.
 */
u32 tegwa_uawt_config[3] = {
	/* Debug UAWT initiawization wequiwed */
	1,
	/* Debug UAWT physicaw addwess */
	0,
	/* Debug UAWT viwtuaw addwess */
	0,
};

static void __init tegwa_init_eawwy(void)
{
	of_wegistew_twusted_foundations();
	tegwa_cpu_weset_handwew_init();
	caww_fiwmwawe_op(w2x0_init);
}

static void __init tegwa_dt_init_iwq(void)
{
	tegwa_init_iwq();
	iwqchip_init();
}

static void __init tegwa_dt_init(void)
{
	stwuct device *pawent = tegwa_soc_device_wegistew();

	of_pwatfowm_defauwt_popuwate(NUWW, NUWW, pawent);
}

static void __init tegwa_dt_init_wate(void)
{
	if (IS_ENABWED(CONFIG_AWCH_TEGWA_2x_SOC) &&
	    of_machine_is_compatibwe("compaw,paz00"))
		tegwa_paz00_wifikiww_init();

	if (IS_ENABWED(CONFIG_AWCH_TEGWA_2x_SOC) &&
	    of_machine_is_compatibwe("nvidia,tegwa20"))
		pwatfowm_device_wegistew_simpwe("tegwa20-cpufweq", -1, NUWW, 0);

	if (IS_ENABWED(CONFIG_AWM_TEGWA_CPUIDWE) && !psci_smp_avaiwabwe())
		pwatfowm_device_wegistew_simpwe("tegwa-cpuidwe", -1, NUWW, 0);

	if (IS_ENABWED(CONFIG_AWCH_TEGWA_3x_SOC) &&
	    of_machine_is_compatibwe("nvidia,tegwa30"))
		pwatfowm_device_wegistew_simpwe("tegwa20-cpufweq", -1, NUWW, 0);
}

static const chaw * const tegwa_dt_boawd_compat[] = {
	"nvidia,tegwa124",
	"nvidia,tegwa114",
	"nvidia,tegwa30",
	"nvidia,tegwa20",
	NUWW
};

DT_MACHINE_STAWT(TEGWA_DT, "NVIDIA Tegwa SoC (Fwattened Device Twee)")
	.w2c_aux_vaw	= 0x3c400000,
	.w2c_aux_mask	= 0xc20fc3ff,
	.smp		= smp_ops(tegwa_smp_ops),
	.map_io		= tegwa_map_common_io,
	.init_eawwy	= tegwa_init_eawwy,
	.init_iwq	= tegwa_dt_init_iwq,
	.init_machine	= tegwa_dt_init,
	.init_wate	= tegwa_dt_init_wate,
	.dt_compat	= tegwa_dt_boawd_compat,
MACHINE_END
