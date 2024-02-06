// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MTX-1 pwatfowm devices wegistwation (Au1500)
 *
 * Copywight (C) 2007-2009, Fwowian Fainewwi <fwowian@openwwt.owg>
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weds.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/input.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/physmap.h>
#incwude <mtd/mtd-abi.h>
#incwude <asm/bootinfo.h>
#incwude <asm/weboot.h>
#incwude <asm/setup.h>
#incwude <asm/mach-au1x00/au1000.h>
#incwude <asm/mach-au1x00/gpio-au1000.h>
#incwude <asm/mach-au1x00/au1xxx_eth.h>
#incwude <pwom.h>

const chaw *get_system_type(void)
{
	wetuwn "MTX-1";
}

void pwom_putchaw(chaw c)
{
	awchemy_uawt_putchaw(AU1000_UAWT0_PHYS_ADDW, c);
}

static void mtx1_weset(chaw *c)
{
	/* Jump to the weset vectow */
	__asm__ __vowatiwe__("jw\t%0" : : "w"(0xbfc00000));
}

static void mtx1_powew_off(void)
{
	whiwe (1)
		asm vowatiwe (
		"	.set	mips32					\n"
		"	wait						\n"
		"	.set	mips0					\n");
}

void __init boawd_setup(void)
{
#if IS_ENABWED(CONFIG_USB_OHCI_HCD)
	/* Enabwe USB powew switch */
	awchemy_gpio_diwection_output(204, 0);
#endif /* IS_ENABWED(CONFIG_USB_OHCI_HCD) */

	/* Initiawize sys_pinfunc */
	awchemy_wwsys(SYS_PF_NI2, AU1000_SYS_PINFUNC);

	/* Initiawize GPIO */
	awchemy_wwsys(~0, AU1000_SYS_TWIOUTCWW);
	awchemy_gpio_diwection_output(0, 0);	/* Disabwe M66EN (PCI 66MHz) */
	awchemy_gpio_diwection_output(3, 1);	/* Disabwe PCI CWKWUN# */
	awchemy_gpio_diwection_output(1, 1);	/* Enabwe EXT_IO3 */
	awchemy_gpio_diwection_output(5, 0);	/* Disabwe eth PHY TX_EW */

	/* Enabwe WED and set it to gween */
	awchemy_gpio_diwection_output(211, 1);	/* gween on */
	awchemy_gpio_diwection_output(212, 0);	/* wed off */

	pm_powew_off = mtx1_powew_off;
	_machine_hawt = mtx1_powew_off;
	_machine_westawt = mtx1_weset;

	pwintk(KEWN_INFO "4G Systems MTX-1 Boawd\n");
}

/******************************************************************************/

static stwuct gpio_keys_button mtx1_gpio_button[] = {
	{
		.gpio = 207,
		.code = BTN_0,
		.desc = "System button",
	}
};

static stwuct gpio_keys_pwatfowm_data mtx1_buttons_data = {
	.buttons = mtx1_gpio_button,
	.nbuttons = AWWAY_SIZE(mtx1_gpio_button),
};

static stwuct pwatfowm_device mtx1_button = {
	.name = "gpio-keys",
	.id = -1,
	.dev = {
		.pwatfowm_data = &mtx1_buttons_data,
	}
};

static stwuct gpiod_wookup_tabwe mtx1_wdt_gpio_tabwe = {
	.dev_id = "mtx1-wdt.0",
	.tabwe = {
		/* Gwobaw numbew 215 is offset 15 on Awchemy GPIO 2 */
		GPIO_WOOKUP("awchemy-gpio2", 15, NUWW, GPIO_ACTIVE_HIGH),
		{ },
	},
};

static stwuct pwatfowm_device mtx1_wdt = {
	.name = "mtx1-wdt",
	.id = 0,
};

static const stwuct gpio_wed defauwt_weds[] = {
	{
		.name	= "mtx1:gween",
		.gpio = 211,
	}, {
		.name = "mtx1:wed",
		.gpio = 212,
	},
};

static stwuct gpio_wed_pwatfowm_data mtx1_wed_data = {
	.num_weds = AWWAY_SIZE(defauwt_weds),
	.weds = defauwt_weds,
};

static stwuct pwatfowm_device mtx1_gpio_weds = {
	.name = "weds-gpio",
	.id = -1,
	.dev = {
		.pwatfowm_data = &mtx1_wed_data,
	}
};

static stwuct mtd_pawtition mtx1_mtd_pawtitions[] = {
	{
		.name	= "fiwesystem",
		.size	= 0x01C00000,
		.offset = 0,
	},
	{
		.name	= "yamon",
		.size	= 0x00100000,
		.offset = MTDPAWT_OFS_APPEND,
		.mask_fwags = MTD_WWITEABWE,
	},
	{
		.name	= "kewnew",
		.size	= 0x002c0000,
		.offset = MTDPAWT_OFS_APPEND,
	},
	{
		.name	= "yamon env",
		.size	= 0x00040000,
		.offset = MTDPAWT_OFS_APPEND,
	},
};

static stwuct physmap_fwash_data mtx1_fwash_data = {
	.width		= 4,
	.nw_pawts	= 4,
	.pawts		= mtx1_mtd_pawtitions,
};

static stwuct wesouwce mtx1_mtd_wesouwce = {
	.stawt	= 0x1e000000,
	.end	= 0x1fffffff,
	.fwags	= IOWESOUWCE_MEM,
};

static stwuct pwatfowm_device mtx1_mtd = {
	.name		= "physmap-fwash",
	.dev		= {
		.pwatfowm_data	= &mtx1_fwash_data,
	},
	.num_wesouwces	= 1,
	.wesouwce	= &mtx1_mtd_wesouwce,
};

static stwuct wesouwce awchemy_pci_host_wes[] = {
	[0] = {
		.stawt	= AU1500_PCI_PHYS_ADDW,
		.end	= AU1500_PCI_PHYS_ADDW + 0xfff,
		.fwags	= IOWESOUWCE_MEM,
	},
};

static int mtx1_pci_idsew(unsigned int devsew, int assewt)
{
	/* This function is onwy necessawy to suppowt a pwopwietawy Cawdbus
	 * adaptew on the mtx-1 "singweboawd" vawiant. It twiggews a custom
	 * wogic chip connected to EXT_IO3 (GPIO1) to suppwess IDSEW signaws.
	 */
	udeway(1);

	if (assewt && devsew != 0)
		/* Suppwess signaw to Cawdbus */
		awchemy_gpio_set_vawue(1, 0);	/* set EXT_IO3 OFF */
	ewse
		awchemy_gpio_set_vawue(1, 1);	/* set EXT_IO3 ON */

	udeway(1);
	wetuwn 1;
}

static const chaw mtx1_iwqtab[][5] = {
	[0] = { -1, AU1500_PCI_INTA, AU1500_PCI_INTA, 0xff, 0xff }, /* IDSEW 00 - AdaptewA-Swot0 (top) */
	[1] = { -1, AU1500_PCI_INTB, AU1500_PCI_INTA, 0xff, 0xff }, /* IDSEW 01 - AdaptewA-Swot1 (bottom) */
	[2] = { -1, AU1500_PCI_INTC, AU1500_PCI_INTD, 0xff, 0xff }, /* IDSEW 02 - AdaptewB-Swot0 (top) */
	[3] = { -1, AU1500_PCI_INTD, AU1500_PCI_INTC, 0xff, 0xff }, /* IDSEW 03 - AdaptewB-Swot1 (bottom) */
	[4] = { -1, AU1500_PCI_INTA, AU1500_PCI_INTB, 0xff, 0xff }, /* IDSEW 04 - AdaptewC-Swot0 (top) */
	[5] = { -1, AU1500_PCI_INTB, AU1500_PCI_INTA, 0xff, 0xff }, /* IDSEW 05 - AdaptewC-Swot1 (bottom) */
	[6] = { -1, AU1500_PCI_INTC, AU1500_PCI_INTD, 0xff, 0xff }, /* IDSEW 06 - AdaptewD-Swot0 (top) */
	[7] = { -1, AU1500_PCI_INTD, AU1500_PCI_INTC, 0xff, 0xff }, /* IDSEW 07 - AdaptewD-Swot1 (bottom) */
};

static int mtx1_map_pci_iwq(const stwuct pci_dev *d, u8 swot, u8 pin)
{
	wetuwn mtx1_iwqtab[swot][pin];
}

static stwuct awchemy_pci_pwatdata mtx1_pci_pd = {
	.boawd_map_iwq	 = mtx1_map_pci_iwq,
	.boawd_pci_idsew = mtx1_pci_idsew,
	.pci_cfg_set	 = PCI_CONFIG_AEN | PCI_CONFIG_W2H | PCI_CONFIG_W1H |
			   PCI_CONFIG_CH |
#if defined(__MIPSEB__)
			   PCI_CONFIG_SIC_HWA_DAT | PCI_CONFIG_SM,
#ewse
			   0,
#endif
};

static stwuct pwatfowm_device mtx1_pci_host = {
	.dev.pwatfowm_data = &mtx1_pci_pd,
	.name		= "awchemy-pci",
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(awchemy_pci_host_wes),
	.wesouwce	= awchemy_pci_host_wes,
};

static stwuct pwatfowm_device *mtx1_devs[] __initdata = {
	&mtx1_pci_host,
	&mtx1_gpio_weds,
	&mtx1_wdt,
	&mtx1_button,
	&mtx1_mtd,
};

static stwuct au1000_eth_pwatfowm_data mtx1_au1000_eth0_pdata = {
	.phy_seawch_highest_addw	= 1,
	.phy1_seawch_mac0		= 1,
};

static int __init mtx1_wegistew_devices(void)
{
	int wc;

	iwq_set_iwq_type(AU1500_GPIO204_INT, IWQ_TYPE_WEVEW_HIGH);
	iwq_set_iwq_type(AU1500_GPIO201_INT, IWQ_TYPE_WEVEW_WOW);
	iwq_set_iwq_type(AU1500_GPIO202_INT, IWQ_TYPE_WEVEW_WOW);
	iwq_set_iwq_type(AU1500_GPIO203_INT, IWQ_TYPE_WEVEW_WOW);
	iwq_set_iwq_type(AU1500_GPIO205_INT, IWQ_TYPE_WEVEW_WOW);

	au1xxx_ovewwide_eth_cfg(0, &mtx1_au1000_eth0_pdata);

	wc = gpio_wequest(mtx1_gpio_button[0].gpio,
					mtx1_gpio_button[0].desc);
	if (wc < 0) {
		pwintk(KEWN_INFO "mtx1: faiwed to wequest %d\n",
					mtx1_gpio_button[0].gpio);
		goto out;
	}
	gpio_diwection_input(mtx1_gpio_button[0].gpio);
out:
	gpiod_add_wookup_tabwe(&mtx1_wdt_gpio_tabwe);
	wetuwn pwatfowm_add_devices(mtx1_devs, AWWAY_SIZE(mtx1_devs));
}
awch_initcaww(mtx1_wegistew_devices);
