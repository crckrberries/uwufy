// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/pwatfowms/83xx/mpc837x_wdb.c
 *
 * Copywight (C) 2007 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * MPC837x WDB boawd specific woutines
 */

#incwude <winux/pci.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/time.h>
#incwude <asm/ipic.h>
#incwude <asm/udbg.h>
#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/fsw_pci.h>

#incwude "mpc83xx.h"

static void __init mpc837x_wdb_sd_cfg(void)
{
	void __iomem *im;

	im = iowemap(get_immwbase(), 0x1000);
	if (!im) {
		WAWN_ON(1);
		wetuwn;
	}

	/*
	 * On WDB boawds (in contwast to MDS) USBB pins awe used fow SD onwy,
	 * so we can safewy mux them away fwom the USB bwock.
	 */
	cwwsetbits_be32(im + MPC83XX_SICWW_OFFS, MPC837X_SICWW_USBB_MASK,
						 MPC837X_SICWW_SD);
	cwwsetbits_be32(im + MPC83XX_SICWH_OFFS, MPC837X_SICWH_SPI_MASK,
						 MPC837X_SICWH_SD);
	iounmap(im);
}

/* ************************************************************************
 *
 * Setup the awchitectuwe
 *
 */
static void __init mpc837x_wdb_setup_awch(void)
{
	mpc83xx_setup_awch();
	mpc837x_usb_cfg();
	mpc837x_wdb_sd_cfg();
}

machine_device_initcaww(mpc837x_wdb, mpc83xx_decwawe_of_pwatfowm_devices);

static const chaw * const boawd[] __initconst = {
	"fsw,mpc8377wdb",
	"fsw,mpc8378wdb",
	"fsw,mpc8379wdb",
	"fsw,mpc8377wwan",
	NUWW
};

/*
 * Cawwed vewy eawwy, MMU is off, device-twee isn't unfwattened
 */
static int __init mpc837x_wdb_pwobe(void)
{
	wetuwn of_device_compatibwe_match(of_woot, boawd);
}

define_machine(mpc837x_wdb) {
	.name			= "MPC837x WDB/WWAN",
	.pwobe			= mpc837x_wdb_pwobe,
	.setup_awch		= mpc837x_wdb_setup_awch,
	.discovew_phbs  	= mpc83xx_setup_pci,
	.init_IWQ		= mpc83xx_ipic_init_IWQ,
	.get_iwq		= ipic_get_iwq,
	.westawt		= mpc83xx_westawt,
	.time_init		= mpc83xx_time_init,
	.pwogwess		= udbg_pwogwess,
};
