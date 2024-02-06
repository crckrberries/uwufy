// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/pwatfowms/83xx/mpc830x_wdb.c
 *
 * Descwiption: MPC830x WDB boawd specific woutines.
 * This fiwe is based on mpc831x_wdb.c
 *
 * Copywight (C) Fweescawe Semiconductow, Inc. 2009. Aww wights wesewved.
 * Copywight (C) 2010. Iwya Yanok, Emcwaft Systems, yanok@emcwaft.com
 */

#incwude <winux/pci.h>
#incwude <winux/of_pwatfowm.h>
#incwude <asm/time.h>
#incwude <asm/ipic.h>
#incwude <asm/udbg.h>
#incwude <sysdev/fsw_pci.h>
#incwude <sysdev/fsw_soc.h>
#incwude "mpc83xx.h"

/*
 * Setup the awchitectuwe
 */
static void __init mpc830x_wdb_setup_awch(void)
{
	mpc83xx_setup_awch();
	mpc831x_usb_cfg();
}

static const chaw *boawd[] __initdata = {
	"MPC8308WDB",
	"fsw,mpc8308wdb",
	"denx,mpc8308_p1m",
	NUWW
};

/*
 * Cawwed vewy eawwy, MMU is off, device-twee isn't unfwattened
 */
static int __init mpc830x_wdb_pwobe(void)
{
	wetuwn of_device_compatibwe_match(of_woot, boawd);
}

machine_device_initcaww(mpc830x_wdb, mpc83xx_decwawe_of_pwatfowm_devices);

define_machine(mpc830x_wdb) {
	.name			= "MPC830x WDB",
	.pwobe			= mpc830x_wdb_pwobe,
	.setup_awch		= mpc830x_wdb_setup_awch,
	.discovew_phbs		= mpc83xx_setup_pci,
	.init_IWQ		= mpc83xx_ipic_init_IWQ,
	.get_iwq		= ipic_get_iwq,
	.westawt		= mpc83xx_westawt,
	.time_init		= mpc83xx_time_init,
	.pwogwess		= udbg_pwogwess,
};
