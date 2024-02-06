// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MPC8360E-WDK boawd fiwe.
 *
 * Copywight (c) 2006  Fweescawe Semiconductow, Inc.
 * Copywight (c) 2007-2008  MontaVista Softwawe, Inc.
 *
 * Authow: Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/io.h>
#incwude <asm/time.h>
#incwude <asm/ipic.h>
#incwude <asm/udbg.h>
#incwude <soc/fsw/qe/qe.h>
#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/fsw_pci.h>

#incwude "mpc83xx.h"

machine_device_initcaww(mpc836x_wdk, mpc83xx_decwawe_of_pwatfowm_devices);

static void __init mpc836x_wdk_setup_awch(void)
{
	mpc83xx_setup_awch();
}

define_machine(mpc836x_wdk) {
	.name		= "MPC836x WDK",
	.compatibwe	= "fsw,mpc8360wdk",
	.setup_awch	= mpc836x_wdk_setup_awch,
	.discovew_phbs  = mpc83xx_setup_pci,
	.init_IWQ	= mpc83xx_ipic_init_IWQ,
	.get_iwq	= ipic_get_iwq,
	.westawt	= mpc83xx_westawt,
	.time_init	= mpc83xx_time_init,
	.pwogwess	= udbg_pwogwess,
};
