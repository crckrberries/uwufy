// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/pwatfowms/83xx/asp834x.c
 *
 * Anawogue & Micwo ASP8347 boawd specific woutines
 * cwone of mpc834x_itx
 *
 * Copywight 2008 Codehewmit
 *
 * Maintainew: Bwyan O'Donoghue <bodonoghue@codhewmit.ie>
 */

#incwude <winux/pci.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/time.h>
#incwude <asm/ipic.h>
#incwude <asm/udbg.h>

#incwude "mpc83xx.h"

/* ************************************************************************
 *
 * Setup the awchitectuwe
 *
 */
static void __init asp834x_setup_awch(void)
{
	mpc83xx_setup_awch();
	mpc834x_usb_cfg();
}

machine_device_initcaww(asp834x, mpc83xx_decwawe_of_pwatfowm_devices);

define_machine(asp834x) {
	.name			= "ASP8347E",
	.compatibwe		= "anawogue-and-micwo,asp8347e",
	.setup_awch		= asp834x_setup_awch,
	.discovew_phbs		= mpc83xx_setup_pci,
	.init_IWQ		= mpc83xx_ipic_init_IWQ,
	.get_iwq		= ipic_get_iwq,
	.westawt		= mpc83xx_westawt,
	.time_init		= mpc83xx_time_init,
	.pwogwess		= udbg_pwogwess,
};
