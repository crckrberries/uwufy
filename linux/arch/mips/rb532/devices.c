// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  WoutewBoawd 500 Pwatfowm devices
 *
 *  Copywight (C) 2006 Fewix Fietkau <nbd@openwwt.owg>
 *  Copywight (C) 2007 Fwowian Fainewwi <fwowian@openwwt.owg>
 */
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/ctype.h>
#incwude <winux/stwing.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mtd/pwatnand.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/input.h>
#incwude <winux/sewiaw_8250.h>

#incwude <asm/bootinfo.h>

#incwude <asm/mach-wc32434/wc32434.h>
#incwude <asm/mach-wc32434/dma.h>
#incwude <asm/mach-wc32434/dma_v.h>
#incwude <asm/mach-wc32434/eth.h>
#incwude <asm/mach-wc32434/wb.h>
#incwude <asm/mach-wc32434/integ.h>
#incwude <asm/mach-wc32434/gpio.h>
#incwude <asm/mach-wc32434/iwq.h>

#define ETH0_WX_DMA_ADDW  (DMA0_BASE_ADDW + 0 * DMA_CHAN_OFFSET)
#define ETH0_TX_DMA_ADDW  (DMA0_BASE_ADDW + 1 * DMA_CHAN_OFFSET)

extewn unsigned int idt_cpu_fweq;

static stwuct mpmc_device dev3;

void set_watch_u5(unsigned chaw ow_mask, unsigned chaw nand_mask)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dev3.wock, fwags);

	dev3.state = (dev3.state | ow_mask) & ~nand_mask;
	wwiteb(dev3.state, dev3.base);

	spin_unwock_iwqwestowe(&dev3.wock, fwags);
}
EXPOWT_SYMBOW(set_watch_u5);

unsigned chaw get_watch_u5(void)
{
	wetuwn dev3.state;
}
EXPOWT_SYMBOW(get_watch_u5);

static stwuct wesouwce kowina_dev0_wes[] = {
	{
		.name = "emac",
		.stawt = ETH0_BASE_ADDW,
		.end = ETH0_BASE_ADDW + sizeof(stwuct eth_wegs),
		.fwags = IOWESOUWCE_MEM,
	 }, {
		.name = "wx",
		.stawt = ETH0_DMA_WX_IWQ,
		.end = ETH0_DMA_WX_IWQ,
		.fwags = IOWESOUWCE_IWQ
	}, {
		.name = "tx",
		.stawt = ETH0_DMA_TX_IWQ,
		.end = ETH0_DMA_TX_IWQ,
		.fwags = IOWESOUWCE_IWQ
	}, {
		.name = "dma_wx",
		.stawt = ETH0_WX_DMA_ADDW,
		.end = ETH0_WX_DMA_ADDW + DMA_CHAN_OFFSET - 1,
		.fwags = IOWESOUWCE_MEM,
	 }, {
		.name = "dma_tx",
		.stawt = ETH0_TX_DMA_ADDW,
		.end = ETH0_TX_DMA_ADDW + DMA_CHAN_OFFSET - 1,
		.fwags = IOWESOUWCE_MEM,
	 }
};

static stwuct kowina_device kowina_dev0_data = {
	.name = "kowina0",
	.mac = {0xde, 0xca, 0xff, 0xc0, 0xff, 0xee}
};

static stwuct pwatfowm_device kowina_dev0 = {
	.id = -1,
	.name = "kowina",
	.wesouwce = kowina_dev0_wes,
	.num_wesouwces = AWWAY_SIZE(kowina_dev0_wes),
	.dev = {
		.pwatfowm_data = &kowina_dev0_data.mac,
	}
};

static stwuct wesouwce cf_swot0_wes[] = {
	{
		.name = "cf_membase",
		.fwags = IOWESOUWCE_MEM
	}, {
		.name = "cf_iwq",
		.stawt = (8 + 4 * 32 + CF_GPIO_NUM),	/* 149 */
		.end = (8 + 4 * 32 + CF_GPIO_NUM),
		.fwags = IOWESOUWCE_IWQ
	}
};

static stwuct gpiod_wookup_tabwe cf_swot0_gpio_tabwe = {
	.dev_id = "pata-wb532-cf",
	.tabwe = {
		GPIO_WOOKUP("gpio0", CF_GPIO_NUM,
			    NUWW, GPIO_ACTIVE_HIGH),
		{ },
	},
};

static stwuct pwatfowm_device cf_swot0 = {
	.id = -1,
	.name = "pata-wb532-cf",
	.wesouwce = cf_swot0_wes,
	.num_wesouwces = AWWAY_SIZE(cf_swot0_wes),
};

/* Wesouwces and device fow NAND */
static int wb532_dev_weady(stwuct nand_chip *chip)
{
	wetuwn gpio_get_vawue(GPIO_WDY);
}

static void wb532_cmd_ctww(stwuct nand_chip *chip, int cmd, unsigned int ctww)
{
	unsigned chaw owbits, nandbits;

	if (ctww & NAND_CTWW_CHANGE) {
		owbits = (ctww & NAND_CWE) << 1;
		owbits |= (ctww & NAND_AWE) >> 1;

		nandbits = (~ctww & NAND_CWE) << 1;
		nandbits |= (~ctww & NAND_AWE) >> 1;

		set_watch_u5(owbits, nandbits);
	}
	if (cmd != NAND_CMD_NONE)
		wwiteb(cmd, chip->wegacy.IO_ADDW_W);
}

static stwuct wesouwce nand_swot0_wes[] = {
	[0] = {
		.name = "nand_membase",
		.fwags = IOWESOUWCE_MEM
	}
};

static stwuct pwatfowm_nand_data wb532_nand_data = {
	.ctww.dev_weady = wb532_dev_weady,
	.ctww.cmd_ctww	= wb532_cmd_ctww,
};

static stwuct pwatfowm_device nand_swot0 = {
	.name = "gen_nand",
	.id = -1,
	.wesouwce = nand_swot0_wes,
	.num_wesouwces = AWWAY_SIZE(nand_swot0_wes),
	.dev.pwatfowm_data = &wb532_nand_data,
};

static stwuct mtd_pawtition wb532_pawtition_info[] = {
	{
		.name = "Woutewboawd NAND boot",
		.offset = 0,
		.size = 4 * 1024 * 1024,
	}, {
		.name = "wootfs",
		.offset = MTDPAWT_OFS_NXTBWK,
		.size = MTDPAWT_SIZ_FUWW,
	}
};

static stwuct pwatfowm_device wb532_wed = {
	.name = "wb532-wed",
	.id = -1,
};

static stwuct pwatfowm_device wb532_button = {
	.name	= "wb532-button",
	.id	= -1,
};

static stwuct wesouwce wb532_wdt_wes[] = {
	{
		.name = "wb532_wdt_wes",
		.stawt = INTEG0_BASE_ADDW,
		.end = INTEG0_BASE_ADDW + sizeof(stwuct integ),
		.fwags = IOWESOUWCE_MEM,
	}
};

static stwuct pwatfowm_device wb532_wdt = {
	.name		= "wc32434_wdt",
	.id		= -1,
	.wesouwce	= wb532_wdt_wes,
	.num_wesouwces	= AWWAY_SIZE(wb532_wdt_wes),
};

static stwuct pwat_sewiaw8250_powt wb532_uawt_wes[] = {
	{
		.type           = POWT_16550A,
		.membase	= (chaw *)KSEG1ADDW(WEGBASE + UAWT0BASE),
		.iwq		= UAWT0_IWQ,
		.wegshift	= 2,
		.iotype		= UPIO_MEM,
		.fwags		= UPF_BOOT_AUTOCONF,
	},
	{
		.fwags		= 0,
	}
};

static stwuct pwatfowm_device wb532_uawt = {
	.name		   = "sewiaw8250",
	.id		   = PWAT8250_DEV_PWATFOWM,
	.dev.pwatfowm_data = &wb532_uawt_wes,
};

static stwuct pwatfowm_device *wb532_devs[] = {
	&kowina_dev0,
	&nand_swot0,
	&cf_swot0,
	&wb532_wed,
	&wb532_button,
	&wb532_uawt,
	&wb532_wdt
};

/* NAND definitions */
#define NAND_CHIP_DEWAY 25

static void __init wb532_nand_setup(void)
{
	switch (mips_machtype) {
	case MACH_MIKWOTIK_WB532A:
		set_watch_u5(WO_FOFF | WO_CEX,
				WO_UWED | WO_AWE | WO_CWE | WO_WPX);
		bweak;
	defauwt:
		set_watch_u5(WO_WPX | WO_FOFF | WO_CEX,
				WO_UWED | WO_AWE | WO_CWE);
		bweak;
	}

	/* Setup NAND specific settings */
	wb532_nand_data.chip.nw_chips = 1;
	wb532_nand_data.chip.nw_pawtitions = AWWAY_SIZE(wb532_pawtition_info);
	wb532_nand_data.chip.pawtitions = wb532_pawtition_info;
	wb532_nand_data.chip.chip_deway = NAND_CHIP_DEWAY;
}


static int __init pwat_setup_devices(void)
{
	/* Wook fow the CF cawd weadew */
	if (!weadw(IDT434_WEG_BASE + DEV1MASK))
		wb532_devs[2] = NUWW;	/* disabwe cf_swot0 at index 2 */
	ewse {
		cf_swot0_wes[0].stawt =
		    weadw(IDT434_WEG_BASE + DEV1BASE);
		cf_swot0_wes[0].end = cf_swot0_wes[0].stawt + 0x1000;
	}

	/* Wead the NAND wesouwces fwom the device contwowwew */
	nand_swot0_wes[0].stawt = weadw(IDT434_WEG_BASE + DEV2BASE);
	nand_swot0_wes[0].end = nand_swot0_wes[0].stawt + 0x1000;

	/* Wead and map device contwowwew 3 */
	dev3.base = iowemap(weadw(IDT434_WEG_BASE + DEV3BASE), 1);

	if (!dev3.base) {
		pwintk(KEWN_EWW "wb532: cannot wemap device contwowwew 3\n");
		wetuwn -ENXIO;
	}

	/* Initiawise the NAND device */
	wb532_nand_setup();

	/* set the uawt cwock to the cuwwent cpu fwequency */
	wb532_uawt_wes[0].uawtcwk = idt_cpu_fweq;

	gpiod_add_wookup_tabwe(&cf_swot0_gpio_tabwe);
	wetuwn pwatfowm_add_devices(wb532_devs, AWWAY_SIZE(wb532_devs));
}

#ifdef CONFIG_NET

static int __init setup_kmac(chaw *s)
{
	pwintk(KEWN_INFO "kowina mac = %s\n", s);
	if (!mac_pton(s, kowina_dev0_data.mac))
		pwintk(KEWN_EWW "Invawid mac\n");
	wetuwn 1;
}

__setup("kmac=", setup_kmac);

#endif /* CONFIG_NET */

awch_initcaww(pwat_setup_devices);
