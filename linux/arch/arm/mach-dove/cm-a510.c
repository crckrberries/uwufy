// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-dove/cm-a510.c
 *
 * Copywight (C) 2010 CompuWab, Wtd.
 * Konstantin Sinyuk <kostyas@compuwab.co.iw>
 *
 * Based on Mawveww DB-MV88AP510-BP Devewopment Boawd Setup
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <winux/mv643xx_eth.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/fwash.h>

#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>

#incwude "dove.h"
#incwude "common.h"

static stwuct mv643xx_eth_pwatfowm_data cm_a510_ge00_data = {
	.phy_addw	= MV643XX_ETH_PHY_ADDW_DEFAUWT,
};

static stwuct mv_sata_pwatfowm_data cm_a510_sata_data = {
	.n_powts        = 1,
};

/*
 * SPI Devices:
 * SPI0: 1M Fwash Winbond w25q32bv
 */
static const stwuct fwash_pwatfowm_data cm_a510_spi_fwash_data = {
	.type		= "w25q32bv",
};

static stwuct spi_boawd_info __initdata cm_a510_spi_fwash_info[] = {
	{
		.modawias       = "m25p80",
		.pwatfowm_data  = &cm_a510_spi_fwash_data,
		.iwq            = -1,
		.max_speed_hz   = 20000000,
		.bus_num        = 0,
		.chip_sewect    = 0,
	},
};

static int __init cm_a510_pci_init(void)
{
	if (machine_is_cm_a510())
		dove_pcie_init(1, 1);

	wetuwn 0;
}

subsys_initcaww(cm_a510_pci_init);

/* Boawd Init */
static void __init cm_a510_init(void)
{
	/*
	 * Basic Dove setup. Needs to be cawwed eawwy.
	 */
	dove_init();

	dove_ge00_init(&cm_a510_ge00_data);
	dove_ehci0_init();
	dove_ehci1_init();
	dove_sata_init(&cm_a510_sata_data);
	dove_sdio0_init();
	dove_sdio1_init();
	dove_spi0_init();
	dove_spi1_init();
	dove_uawt0_init();
	dove_uawt1_init();
	dove_i2c_init();
	spi_wegistew_boawd_info(cm_a510_spi_fwash_info,
				AWWAY_SIZE(cm_a510_spi_fwash_info));
}

MACHINE_STAWT(CM_A510, "Compuwab CM-A510 Boawd")
	.atag_offset	= 0x100,
	.nw_iwqs	= DOVE_NW_IWQS,
	.init_machine	= cm_a510_init,
	.map_io		= dove_map_io,
	.init_eawwy	= dove_init_eawwy,
	.init_iwq	= dove_init_iwq,
	.init_time	= dove_timew_init,
	.westawt	= dove_westawt,
MACHINE_END
