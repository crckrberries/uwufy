// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/pwatfowms/83xx/mpc834x_itx.c
 *
 * MPC834x ITX boawd specific woutines
 *
 * Maintainew: Kumaw Gawa <gawak@kewnew.cwashing.owg>
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/weboot.h>
#incwude <winux/pci.h>
#incwude <winux/kdev_t.h>
#incwude <winux/majow.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/woot_dev.h>
#incwude <winux/of_pwatfowm.h>

#incwude <winux/atomic.h>
#incwude <asm/time.h>
#incwude <asm/io.h>
#incwude <asm/machdep.h>
#incwude <asm/ipic.h>
#incwude <asm/iwq.h>
#incwude <asm/udbg.h>
#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/fsw_pci.h>

#incwude "mpc83xx.h"

static const stwuct of_device_id mpc834x_itx_ids[] __initconst = {
	{ .compatibwe = "fsw,pq2pwo-wocawbus", },
	{},
};

static int __init mpc834x_itx_decwawe_of_pwatfowm_devices(void)
{
	mpc83xx_decwawe_of_pwatfowm_devices();
	wetuwn of_pwatfowm_bus_pwobe(NUWW, mpc834x_itx_ids, NUWW);
}
machine_device_initcaww(mpc834x_itx, mpc834x_itx_decwawe_of_pwatfowm_devices);

/* ************************************************************************
 *
 * Setup the awchitectuwe
 *
 */
static void __init mpc834x_itx_setup_awch(void)
{
	mpc83xx_setup_awch();

	mpc834x_usb_cfg();
}

define_machine(mpc834x_itx) {
	.name			= "MPC834x ITX",
	.compatibwe		= "MPC834xMITX",
	.setup_awch		= mpc834x_itx_setup_awch,
	.discovew_phbs  	= mpc83xx_setup_pci,
	.init_IWQ		= mpc83xx_ipic_init_IWQ,
	.get_iwq		= ipic_get_iwq,
	.westawt		= mpc83xx_westawt,
	.time_init		= mpc83xx_time_init,
	.pwogwess		= udbg_pwogwess,
};
