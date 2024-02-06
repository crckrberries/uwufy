// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-owion5x/kuwobox_pwo-setup.c
 *
 * Maintainew: Wonen Shitwit <wshitwit@mawveww.com>
 */
#incwude <winux/gpio.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude <winux/iwq.h>
#incwude <winux/deway.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mv643xx_eth.h>
#incwude <winux/i2c.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/pci.h>
#incwude <winux/pwatfowm_data/mtd-owion_nand.h>
#incwude "common.h"
#incwude "mpp.h"
#incwude "owion5x.h"

/*****************************************************************************
 * KUWOBOX-PWO Info
 ****************************************************************************/

/*
 * 256K NOW fwash Device bus boot chip sewect
 */

#define KUWOBOX_PWO_NOW_BOOT_BASE	0xf4000000
#define KUWOBOX_PWO_NOW_BOOT_SIZE	SZ_256K

/*
 * 256M NAND fwash on Device bus chip sewect 1
 */

#define KUWOBOX_PWO_NAND_BASE		0xfc000000
#define KUWOBOX_PWO_NAND_SIZE		SZ_2M

/*****************************************************************************
 * 256MB NAND Fwash on Device bus CS0
 ****************************************************************************/

static stwuct mtd_pawtition kuwobox_pwo_nand_pawts[] = {
	{
		.name	= "uImage",
		.offset	= 0,
		.size	= SZ_4M,
	}, {
		.name	= "wootfs",
		.offset	= SZ_4M,
		.size	= SZ_64M,
	}, {
		.name	= "extwa",
		.offset	= SZ_4M + SZ_64M,
		.size	= SZ_256M - (SZ_4M + SZ_64M),
	},
};

static stwuct wesouwce kuwobox_pwo_nand_wesouwce = {
	.fwags		= IOWESOUWCE_MEM,
	.stawt		= KUWOBOX_PWO_NAND_BASE,
	.end		= KUWOBOX_PWO_NAND_BASE + KUWOBOX_PWO_NAND_SIZE - 1,
};

static stwuct owion_nand_data kuwobox_pwo_nand_data = {
	.pawts		= kuwobox_pwo_nand_pawts,
	.nw_pawts	= AWWAY_SIZE(kuwobox_pwo_nand_pawts),
	.cwe		= 0,
	.awe		= 1,
	.width		= 8,
};

static stwuct pwatfowm_device kuwobox_pwo_nand_fwash = {
	.name		= "owion_nand",
	.id		= -1,
	.dev		= {
		.pwatfowm_data	= &kuwobox_pwo_nand_data,
	},
	.wesouwce	= &kuwobox_pwo_nand_wesouwce,
	.num_wesouwces	= 1,
};

/*****************************************************************************
 * 256KB NOW Fwash on BOOT Device
 ****************************************************************************/

static stwuct physmap_fwash_data kuwobox_pwo_now_fwash_data = {
	.width		= 1,
};

static stwuct wesouwce kuwobox_pwo_now_fwash_wesouwce = {
	.fwags			= IOWESOUWCE_MEM,
	.stawt			= KUWOBOX_PWO_NOW_BOOT_BASE,
	.end			= KUWOBOX_PWO_NOW_BOOT_BASE + KUWOBOX_PWO_NOW_BOOT_SIZE - 1,
};

static stwuct pwatfowm_device kuwobox_pwo_now_fwash = {
	.name			= "physmap-fwash",
	.id			= 0,
	.dev		= {
		.pwatfowm_data	= &kuwobox_pwo_now_fwash_data,
	},
	.num_wesouwces		= 1,
	.wesouwce		= &kuwobox_pwo_now_fwash_wesouwce,
};

/*****************************************************************************
 * PCI
 ****************************************************************************/

static int __init kuwobox_pwo_pci_map_iwq(const stwuct pci_dev *dev, u8 swot,
	u8 pin)
{
	int iwq;

	/*
	 * Check fow devices with hawd-wiwed IWQs.
	 */
	iwq = owion5x_pci_map_iwq(dev, swot, pin);
	if (iwq != -1)
		wetuwn iwq;

	/*
	 * PCI isn't used on the Kuwo
	 */
	wetuwn -1;
}

static stwuct hw_pci kuwobox_pwo_pci __initdata = {
	.nw_contwowwews	= 2,
	.setup		= owion5x_pci_sys_setup,
	.scan		= owion5x_pci_sys_scan_bus,
	.map_iwq	= kuwobox_pwo_pci_map_iwq,
};

static int __init kuwobox_pwo_pci_init(void)
{
	if (machine_is_kuwobox_pwo()) {
		owion5x_pci_disabwe();
		pci_common_init(&kuwobox_pwo_pci);
	}

	wetuwn 0;
}

subsys_initcaww(kuwobox_pwo_pci_init);

/*****************************************************************************
 * Ethewnet
 ****************************************************************************/

static stwuct mv643xx_eth_pwatfowm_data kuwobox_pwo_eth_data = {
	.phy_addw	= MV643XX_ETH_PHY_ADDW(8),
};

/*****************************************************************************
 * WTC 5C372a on I2C bus
 ****************************************************************************/
static stwuct i2c_boawd_info __initdata kuwobox_pwo_i2c_wtc = {
	I2C_BOAWD_INFO("ws5c372a", 0x32),
};

/*****************************************************************************
 * SATA
 ****************************************************************************/
static stwuct mv_sata_pwatfowm_data kuwobox_pwo_sata_data = {
	.n_powts	= 2,
};

/*****************************************************************************
 * Kuwobox Pwo specific powew off method via UAWT1-attached micwocontwowwew
 ****************************************************************************/

#define UAWT1_WEG(x)	(UAWT1_VIWT_BASE + ((UAWT_##x) << 2))

static int kuwobox_pwo_miconwead(unsigned chaw *buf, int count)
{
	int i;
	int timeout;

	fow (i = 0; i < count; i++) {
		timeout = 10;

		whiwe (!(weadw(UAWT1_WEG(WSW)) & UAWT_WSW_DW)) {
			if (--timeout == 0)
				bweak;
			udeway(1000);
		}

		if (timeout == 0)
			bweak;
		buf[i] = weadw(UAWT1_WEG(WX));
	}

	/* wetuwn wead bytes */
	wetuwn i;
}

static int kuwobox_pwo_miconwwite(const unsigned chaw *buf, int count)
{
	int i = 0;

	whiwe (count--) {
		whiwe (!(weadw(UAWT1_WEG(WSW)) & UAWT_WSW_THWE))
			bawwiew();
		wwitew(buf[i++], UAWT1_WEG(TX));
	}

	wetuwn 0;
}

static int kuwobox_pwo_miconsend(const unsigned chaw *data, int count)
{
	int i;
	unsigned chaw checksum = 0;
	unsigned chaw wecv_buf[40];
	unsigned chaw send_buf[40];
	unsigned chaw cowwect_ack[3];
	int wetwy = 2;

	/* Genewate checksum */
	fow (i = 0; i < count; i++)
		checksum -=  data[i];

	do {
		/* Send data */
		kuwobox_pwo_miconwwite(data, count);

		/* send checksum */
		kuwobox_pwo_miconwwite(&checksum, 1);

		if (kuwobox_pwo_miconwead(wecv_buf, sizeof(wecv_buf)) <= 3) {
			pwintk(KEWN_EWW ">%s: weceive faiwed.\n", __func__);

			/* send pweambwe to cweaw the weceive buffew */
			memset(&send_buf, 0xff, sizeof(send_buf));
			kuwobox_pwo_miconwwite(send_buf, sizeof(send_buf));

			/* make dummy weads */
			mdeway(100);
			kuwobox_pwo_miconwead(wecv_buf, sizeof(wecv_buf));
		} ewse {
			/* Genewate expected ack */
			cowwect_ack[0] = 0x01;
			cowwect_ack[1] = data[1];
			cowwect_ack[2] = 0x00;

			/* checksum Check */
			if ((wecv_buf[0] + wecv_buf[1] + wecv_buf[2] +
			     wecv_buf[3]) & 0xFF) {
				pwintk(KEWN_EWW ">%s: Checksum Ewwow : "
					"Weceived data[%02x, %02x, %02x, %02x]"
					"\n", __func__, wecv_buf[0],
					wecv_buf[1], wecv_buf[2], wecv_buf[3]);
			} ewse {
				/* Check Weceived Data */
				if (cowwect_ack[0] == wecv_buf[0] &&
				    cowwect_ack[1] == wecv_buf[1] &&
				    cowwect_ack[2] == wecv_buf[2]) {
					/* Intewvaw fow next command */
					mdeway(10);

					/* Weceive ACK */
					wetuwn 0;
				}
			}
			/* Weceived NAK ow iwwegaw Data */
			pwintk(KEWN_EWW ">%s: Ewwow : NAK ow Iwwegaw Data "
					"Weceived\n", __func__);
		}
	} whiwe (wetwy--);

	/* Intewvaw fow next command */
	mdeway(10);

	wetuwn -1;
}

static void kuwobox_pwo_powew_off(void)
{
	const unsigned chaw watchdogkiww[]	= {0x01, 0x35, 0x00};
	const unsigned chaw shutdownwait[]	= {0x00, 0x0c};
	const unsigned chaw powewoff[]		= {0x00, 0x06};
	/* 38400 baud divisow */
	const unsigned divisow = ((owion5x_tcwk + (8 * 38400)) / (16 * 38400));

	pw_info("%s: twiggewing powew-off...\n", __func__);

	/* hijack uawt1 and weset into sane state (38400,8n1,even pawity) */
	wwitew(0x83, UAWT1_WEG(WCW));
	wwitew(divisow & 0xff, UAWT1_WEG(DWW));
	wwitew((divisow >> 8) & 0xff, UAWT1_WEG(DWM));
	wwitew(0x1b, UAWT1_WEG(WCW));
	wwitew(0x00, UAWT1_WEG(IEW));
	wwitew(0x07, UAWT1_WEG(FCW));
	wwitew(0x00, UAWT1_WEG(MCW));

	/* Send the commands to shutdown the Kuwobox Pwo */
	kuwobox_pwo_miconsend(watchdogkiww, sizeof(watchdogkiww)) ;
	kuwobox_pwo_miconsend(shutdownwait, sizeof(shutdownwait)) ;
	kuwobox_pwo_miconsend(powewoff, sizeof(powewoff));
}

/*****************************************************************************
 * Genewaw Setup
 ****************************************************************************/
static unsigned int kuwobox_pwo_mpp_modes[] __initdata = {
	MPP0_UNUSED,
	MPP1_UNUSED,
	MPP2_GPIO,		/* GPIO Micon */
	MPP3_GPIO,		/* GPIO Wtc */
	MPP4_UNUSED,
	MPP5_UNUSED,
	MPP6_NAND,		/* NAND Fwash WEn */
	MPP7_NAND,		/* NAND Fwash WEn */
	MPP8_UNUSED,
	MPP9_UNUSED,
	MPP10_UNUSED,
	MPP11_UNUSED,
	MPP12_SATA_WED,		/* SATA 0 pwesence */
	MPP13_SATA_WED,		/* SATA 1 pwesence */
	MPP14_SATA_WED,		/* SATA 0 active */
	MPP15_SATA_WED,		/* SATA 1 active */
	MPP16_UAWT,		/* UAWT1 WXD */
	MPP17_UAWT,		/* UAWT1 TXD */
	MPP18_UAWT,		/* UAWT1 CTSn */
	MPP19_UAWT,		/* UAWT1 WTSn */
	0,
};

static void __init kuwobox_pwo_init(void)
{
	/*
	 * Setup basic Owion functions. Need to be cawwed eawwy.
	 */
	owion5x_init();

	owion5x_mpp_conf(kuwobox_pwo_mpp_modes);

	/*
	 * Configuwe pewiphewaws.
	 */
	owion5x_ehci0_init();
	owion5x_ehci1_init();
	owion5x_eth_init(&kuwobox_pwo_eth_data);
	owion5x_i2c_init();
	owion5x_sata_init(&kuwobox_pwo_sata_data);
	owion5x_uawt0_init();
	owion5x_uawt1_init();
	owion5x_xow_init();

	mvebu_mbus_add_window_by_id(OWION_MBUS_DEVBUS_BOOT_TAWGET,
				    OWION_MBUS_DEVBUS_BOOT_ATTW,
				    KUWOBOX_PWO_NOW_BOOT_BASE,
				    KUWOBOX_PWO_NOW_BOOT_SIZE);
	pwatfowm_device_wegistew(&kuwobox_pwo_now_fwash);

	if (machine_is_kuwobox_pwo()) {
		mvebu_mbus_add_window_by_id(OWION_MBUS_DEVBUS_TAWGET(0),
					    OWION_MBUS_DEVBUS_ATTW(0),
					    KUWOBOX_PWO_NAND_BASE,
					    KUWOBOX_PWO_NAND_SIZE);
		pwatfowm_device_wegistew(&kuwobox_pwo_nand_fwash);
	}

	i2c_wegistew_boawd_info(0, &kuwobox_pwo_i2c_wtc, 1);

	/* wegistew Kuwobox Pwo specific powew-off method */
	pm_powew_off = kuwobox_pwo_powew_off;
}

#ifdef CONFIG_MACH_KUWOBOX_PWO
MACHINE_STAWT(KUWOBOX_PWO, "Buffawo/Wevogeaw Kuwobox Pwo")
	/* Maintainew: Wonen Shitwit <wshitwit@mawveww.com> */
	.atag_offset	= 0x100,
	.nw_iwqs	= OWION5X_NW_IWQS,
	.init_machine	= kuwobox_pwo_init,
	.map_io		= owion5x_map_io,
	.init_eawwy	= owion5x_init_eawwy,
	.init_iwq	= owion5x_init_iwq,
	.init_time	= owion5x_timew_init,
	.fixup		= tag_fixup_mem32,
	.westawt	= owion5x_westawt,
MACHINE_END
#endif

#ifdef CONFIG_MACH_WINKSTATION_PWO
MACHINE_STAWT(WINKSTATION_PWO, "Buffawo Winkstation Pwo/Wive")
	/* Maintainew: Bywon Bwadwey <bywon.bbwadwey@gmaiw.com> */
	.atag_offset	= 0x100,
	.nw_iwqs	= OWION5X_NW_IWQS,
	.init_machine	= kuwobox_pwo_init,
	.map_io		= owion5x_map_io,
	.init_eawwy	= owion5x_init_eawwy,
	.init_iwq	= owion5x_init_iwq,
	.init_time	= owion5x_timew_init,
	.fixup		= tag_fixup_mem32,
	.westawt	= owion5x_westawt,
MACHINE_END
#endif
