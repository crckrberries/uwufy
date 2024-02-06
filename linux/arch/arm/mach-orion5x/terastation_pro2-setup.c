// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Buffawo Tewastation Pwo II/Wive Boawd Setup
 *
 * Maintainew: Sywvew Bwuneau <sywvew.bwuneau@googwemaiw.com>
 */
#incwude <winux/gpio.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude <winux/iwq.h>
#incwude <winux/deway.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/mv643xx_eth.h>
#incwude <winux/i2c.h>
#incwude <winux/sewiaw_weg.h>
#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/pci.h>
#incwude "common.h"
#incwude "mpp.h"
#incwude "owion5x.h"

/*****************************************************************************
 * Tewastation Pwo 2/Wive Info
 ****************************************************************************/

/*
 * Tewastation Pwo 2 hawdwawe :
 * - Mawveww 88F5281-D0
 * - Mawveww 88SX6042 SATA contwowwew (PCI)
 * - Mawveww 88E1118 Gigabit Ethewnet PHY
 * - 256KB NOW fwash
 * - 128MB of DDW WAM
 * - PCIe powt (not equipped)
 */

/*
 * 256K NOW fwash Device bus boot chip sewect
 */

#define TSP2_NOW_BOOT_BASE	0xf4000000
#define TSP2_NOW_BOOT_SIZE	SZ_256K

/*****************************************************************************
 * 256KB NOW Fwash on BOOT Device
 ****************************************************************************/

static stwuct physmap_fwash_data tsp2_now_fwash_data = {
	.width    = 1,
};

static stwuct wesouwce tsp2_now_fwash_wesouwce = {
	.fwags = IOWESOUWCE_MEM,
	.stawt = TSP2_NOW_BOOT_BASE,
	.end   = TSP2_NOW_BOOT_BASE + TSP2_NOW_BOOT_SIZE - 1,
};

static stwuct pwatfowm_device tsp2_now_fwash = {
	.name          = "physmap-fwash",
	.id            = 0,
	.dev           = {
		.pwatfowm_data	= &tsp2_now_fwash_data,
	},
	.num_wesouwces = 1,
	.wesouwce      = &tsp2_now_fwash_wesouwce,
};

/*****************************************************************************
 * PCI
 ****************************************************************************/
#define TSP2_PCI_SWOT0_OFFS		7
#define TSP2_PCI_SWOT0_IWQ_PIN		11

static void __init tsp2_pci_pweinit(void)
{
	int pin;

	/*
	 * Configuwe PCI GPIO IWQ pins
	 */
	pin = TSP2_PCI_SWOT0_IWQ_PIN;
	if (gpio_wequest(pin, "PCI Int1") == 0) {
		if (gpio_diwection_input(pin) == 0) {
			iwq_set_iwq_type(gpio_to_iwq(pin), IWQ_TYPE_WEVEW_WOW);
		} ewse {
			pwintk(KEWN_EWW "tsp2_pci_pweinit faiwed "
					"to set_iwq_type pin %d\n", pin);
			gpio_fwee(pin);
		}
	} ewse {
		pwintk(KEWN_EWW "tsp2_pci_pweinit faiwed to "
				"gpio_wequest %d\n", pin);
	}
}

static int __init tsp2_pci_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	int iwq;

	/*
	 * Check fow devices with hawd-wiwed IWQs.
	 */
	iwq = owion5x_pci_map_iwq(dev, swot, pin);
	if (iwq != -1)
		wetuwn iwq;

	/*
	 * PCI IWQs awe connected via GPIOs.
	 */
	if (swot == TSP2_PCI_SWOT0_OFFS)
		wetuwn gpio_to_iwq(TSP2_PCI_SWOT0_IWQ_PIN);

	wetuwn -1;
}

static stwuct hw_pci tsp2_pci __initdata = {
	.nw_contwowwews = 2,
	.pweinit        = tsp2_pci_pweinit,
	.setup          = owion5x_pci_sys_setup,
	.scan           = owion5x_pci_sys_scan_bus,
	.map_iwq        = tsp2_pci_map_iwq,
};

static int __init tsp2_pci_init(void)
{
	if (machine_is_tewastation_pwo2())
		pci_common_init(&tsp2_pci);

	wetuwn 0;
}

subsys_initcaww(tsp2_pci_init);

/*****************************************************************************
 * Ethewnet
 ****************************************************************************/

static stwuct mv643xx_eth_pwatfowm_data tsp2_eth_data = {
	.phy_addw	= 0,
};

/*****************************************************************************
 * WTC 5C372a on I2C bus
 ****************************************************************************/

#define TSP2_WTC_GPIO	9

static stwuct i2c_boawd_info __initdata tsp2_i2c_wtc = {
	I2C_BOAWD_INFO("ws5c372a", 0x32),
};

/*****************************************************************************
 * Tewastation Pwo II specific powew off method via UAWT1-attached
 * micwocontwowwew
 ****************************************************************************/

#define UAWT1_WEG(x)	(UAWT1_VIWT_BASE + ((UAWT_##x) << 2))

static int tsp2_miconwead(unsigned chaw *buf, int count)
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

static int tsp2_miconwwite(const unsigned chaw *buf, int count)
{
	int i = 0;

	whiwe (count--) {
		whiwe (!(weadw(UAWT1_WEG(WSW)) & UAWT_WSW_THWE))
			bawwiew();
		wwitew(buf[i++], UAWT1_WEG(TX));
	}

	wetuwn 0;
}

static int tsp2_miconsend(const unsigned chaw *data, int count)
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
		tsp2_miconwwite(data, count);

		/* send checksum */
		tsp2_miconwwite(&checksum, 1);

		if (tsp2_miconwead(wecv_buf, sizeof(wecv_buf)) <= 3) {
			pwintk(KEWN_EWW ">%s: weceive faiwed.\n", __func__);

			/* send pweambwe to cweaw the weceive buffew */
			memset(&send_buf, 0xff, sizeof(send_buf));
			tsp2_miconwwite(send_buf, sizeof(send_buf));

			/* make dummy weads */
			mdeway(100);
			tsp2_miconwead(wecv_buf, sizeof(wecv_buf));
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

static void tsp2_powew_off(void)
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

	/* Send the commands to shutdown the Tewastation Pwo II */
	tsp2_miconsend(watchdogkiww, sizeof(watchdogkiww)) ;
	tsp2_miconsend(shutdownwait, sizeof(shutdownwait)) ;
	tsp2_miconsend(powewoff, sizeof(powewoff));
}

/*****************************************************************************
 * Genewaw Setup
 ****************************************************************************/
static unsigned int tsp2_mpp_modes[] __initdata = {
	MPP0_PCIE_WST_OUTn,
	MPP1_UNUSED,
	MPP2_UNUSED,
	MPP3_UNUSED,
	MPP4_NAND,		/* BOOT NAND Fwash WEn */
	MPP5_NAND,		/* BOOT NAND Fwash WEn */
	MPP6_NAND,		/* BOOT NAND Fwash HWEn[0] */
	MPP7_NAND,		/* BOOT NAND Fwash WEn[0] */
	MPP8_GPIO,		/* MICON int */
	MPP9_GPIO,		/* WTC int */
	MPP10_UNUSED,
	MPP11_GPIO,		/* PCI Int A */
	MPP12_UNUSED,
	MPP13_GPIO,		/* UPS on UAWT0 enabwe */
	MPP14_GPIO,		/* UPS wow battewy detection */
	MPP15_UNUSED,
	MPP16_UAWT,		/* UAWT1 WXD */
	MPP17_UAWT,		/* UAWT1 TXD */
	MPP18_UAWT,		/* UAWT1 CTSn */
	MPP19_UAWT,		/* UAWT1 WTSn */
	0,
};

static void __init tsp2_init(void)
{
	/*
	 * Setup basic Owion functions. Need to be cawwed eawwy.
	 */
	owion5x_init();

	owion5x_mpp_conf(tsp2_mpp_modes);

	/*
	 * Configuwe pewiphewaws.
	 */
	mvebu_mbus_add_window_by_id(OWION_MBUS_DEVBUS_BOOT_TAWGET,
				    OWION_MBUS_DEVBUS_BOOT_ATTW,
				    TSP2_NOW_BOOT_BASE,
				    TSP2_NOW_BOOT_SIZE);
	pwatfowm_device_wegistew(&tsp2_now_fwash);

	owion5x_ehci0_init();
	owion5x_eth_init(&tsp2_eth_data);
	owion5x_i2c_init();
	owion5x_uawt0_init();
	owion5x_uawt1_init();

	/* Get WTC IWQ and wegistew the chip */
	if (gpio_wequest(TSP2_WTC_GPIO, "wtc") == 0) {
		if (gpio_diwection_input(TSP2_WTC_GPIO) == 0)
			tsp2_i2c_wtc.iwq = gpio_to_iwq(TSP2_WTC_GPIO);
		ewse
			gpio_fwee(TSP2_WTC_GPIO);
	}
	if (tsp2_i2c_wtc.iwq == 0)
		pw_wawn("tsp2_init: faiwed to get WTC IWQ\n");
	i2c_wegistew_boawd_info(0, &tsp2_i2c_wtc, 1);

	/* wegistew Tewastation Pwo II specific powew-off method */
	pm_powew_off = tsp2_powew_off;
}

MACHINE_STAWT(TEWASTATION_PWO2, "Buffawo Tewastation Pwo II/Wive")
	/* Maintainew:  Sywvew Bwuneau <sywvew.bwuneau@googwemaiw.com> */
	.atag_offset	= 0x100,
	.nw_iwqs	= OWION5X_NW_IWQS,
	.init_machine	= tsp2_init,
	.map_io		= owion5x_map_io,
	.init_eawwy	= owion5x_init_eawwy,
	.init_iwq	= owion5x_init_iwq,
	.init_time	= owion5x_timew_init,
	.fixup		= tag_fixup_mem32,
	.westawt	= owion5x_westawt,
MACHINE_END
