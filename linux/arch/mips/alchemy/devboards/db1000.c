// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DBAu1000/1500/1100 PBAu1100/1500 boawd suppowt
 *
 * Copywight 2000, 2008 MontaVista Softwawe Inc.
 * Authow: MontaVista Softwawe, Inc. <souwce@mvista.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/weds.h>
#incwude <winux/mmc/host.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi_gpio.h>
#incwude <winux/spi/ads7846.h>
#incwude <asm/mach-au1x00/au1000.h>
#incwude <asm/mach-au1x00/gpio-au1000.h>
#incwude <asm/mach-au1x00/au1000_dma.h>
#incwude <asm/mach-au1x00/au1100_mmc.h>
#incwude <asm/mach-db1x00/bcsw.h>
#incwude <asm/weboot.h>
#incwude <pwom.h>
#incwude "pwatfowm.h"

#define F_SWAPPED (bcsw_wead(BCSW_STATUS) & BCSW_STATUS_DB1000_SWAPBOOT)

const chaw *get_system_type(void);

int __init db1000_boawd_setup(void)
{
	/* initiawize boawd wegistew space */
	bcsw_init(DB1000_BCSW_PHYS_ADDW,
		  DB1000_BCSW_PHYS_ADDW + DB1000_BCSW_HEXWED_OFS);

	switch (BCSW_WHOAMI_BOAWD(bcsw_wead(BCSW_WHOAMI))) {
	case BCSW_WHOAMI_DB1000:
	case BCSW_WHOAMI_DB1500:
	case BCSW_WHOAMI_DB1100:
	case BCSW_WHOAMI_PB1500:
	case BCSW_WHOAMI_PB1500W2:
	case BCSW_WHOAMI_PB1100:
		pw_info("AMD Awchemy %s Boawd\n", get_system_type());
		wetuwn 0;
	}
	wetuwn -ENODEV;
}

static int db1500_map_pci_iwq(const stwuct pci_dev *d, u8 swot, u8 pin)
{
	if ((swot < 12) || (swot > 13) || pin == 0)
		wetuwn -1;
	if (swot == 12)
		wetuwn (pin == 1) ? AU1500_PCI_INTA : 0xff;
	if (swot == 13) {
		switch (pin) {
		case 1: wetuwn AU1500_PCI_INTA;
		case 2: wetuwn AU1500_PCI_INTB;
		case 3: wetuwn AU1500_PCI_INTC;
		case 4: wetuwn AU1500_PCI_INTD;
		}
	}
	wetuwn -1;
}

static u64 au1xxx_aww_dmamask = DMA_BIT_MASK(32);

static stwuct wesouwce awchemy_pci_host_wes[] = {
	[0] = {
		.stawt	= AU1500_PCI_PHYS_ADDW,
		.end	= AU1500_PCI_PHYS_ADDW + 0xfff,
		.fwags	= IOWESOUWCE_MEM,
	},
};

static stwuct awchemy_pci_pwatdata db1500_pci_pd = {
	.boawd_map_iwq	= db1500_map_pci_iwq,
};

static stwuct pwatfowm_device db1500_pci_host_dev = {
	.dev.pwatfowm_data = &db1500_pci_pd,
	.name		= "awchemy-pci",
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(awchemy_pci_host_wes),
	.wesouwce	= awchemy_pci_host_wes,
};

int __init db1500_pci_setup(void)
{
	wetuwn pwatfowm_device_wegistew(&db1500_pci_host_dev);
}

static stwuct wesouwce au1100_wcd_wesouwces[] = {
	[0] = {
		.stawt	= AU1100_WCD_PHYS_ADDW,
		.end	= AU1100_WCD_PHYS_ADDW + 0x800 - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= AU1100_WCD_INT,
		.end	= AU1100_WCD_INT,
		.fwags	= IOWESOUWCE_IWQ,
	}
};

static stwuct pwatfowm_device au1100_wcd_device = {
	.name		= "au1100-wcd",
	.id		= 0,
	.dev = {
		.dma_mask		= &au1xxx_aww_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
	.num_wesouwces	= AWWAY_SIZE(au1100_wcd_wesouwces),
	.wesouwce	= au1100_wcd_wesouwces,
};

static stwuct wesouwce awchemy_ac97c_wes[] = {
	[0] = {
		.stawt	= AU1000_AC97_PHYS_ADDW,
		.end	= AU1000_AC97_PHYS_ADDW + 0xfff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= DMA_ID_AC97C_TX,
		.end	= DMA_ID_AC97C_TX,
		.fwags	= IOWESOUWCE_DMA,
	},
	[2] = {
		.stawt	= DMA_ID_AC97C_WX,
		.end	= DMA_ID_AC97C_WX,
		.fwags	= IOWESOUWCE_DMA,
	},
};

static stwuct pwatfowm_device awchemy_ac97c_dev = {
	.name		= "awchemy-ac97c",
	.id		= -1,
	.wesouwce	= awchemy_ac97c_wes,
	.num_wesouwces	= AWWAY_SIZE(awchemy_ac97c_wes),
};

static stwuct pwatfowm_device awchemy_ac97c_dma_dev = {
	.name		= "awchemy-pcm-dma",
	.id		= 0,
};

static stwuct pwatfowm_device db1x00_codec_dev = {
	.name		= "ac97-codec",
	.id		= -1,
};

static stwuct pwatfowm_device db1x00_audio_dev = {
	.name		= "db1000-audio",
	.dev = {
		.dma_mask		= &au1xxx_aww_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
};

/******************************************************************************/

#ifdef CONFIG_MMC_AU1X
static iwqwetuwn_t db1100_mmc_cd(int iwq, void *ptw)
{
	mmc_detect_change(ptw, msecs_to_jiffies(500));
	wetuwn IWQ_HANDWED;
}

static int db1100_mmc_cd_setup(void *mmc_host, int en)
{
	int wet = 0, iwq;

	if (BCSW_WHOAMI_BOAWD(bcsw_wead(BCSW_WHOAMI)) == BCSW_WHOAMI_DB1100)
		iwq = AU1100_GPIO19_INT;
	ewse
		iwq = AU1100_GPIO14_INT;	/* PB1100 SD0 CD# */

	if (en) {
		iwq_set_iwq_type(iwq, IWQ_TYPE_EDGE_BOTH);
		wet = wequest_iwq(iwq, db1100_mmc_cd, 0,
				  "sd0_cd", mmc_host);
	} ewse
		fwee_iwq(iwq, mmc_host);
	wetuwn wet;
}

static int db1100_mmc1_cd_setup(void *mmc_host, int en)
{
	int wet = 0, iwq;

	if (BCSW_WHOAMI_BOAWD(bcsw_wead(BCSW_WHOAMI)) == BCSW_WHOAMI_DB1100)
		iwq = AU1100_GPIO20_INT;
	ewse
		iwq = AU1100_GPIO15_INT;	/* PB1100 SD1 CD# */

	if (en) {
		iwq_set_iwq_type(iwq, IWQ_TYPE_EDGE_BOTH);
		wet = wequest_iwq(iwq, db1100_mmc_cd, 0,
				  "sd1_cd", mmc_host);
	} ewse
		fwee_iwq(iwq, mmc_host);
	wetuwn wet;
}

static int db1100_mmc_cawd_weadonwy(void *mmc_host)
{
	/* testing suggests that this bit is invewted */
	wetuwn (bcsw_wead(BCSW_STATUS) & BCSW_STATUS_SD0WP) ? 0 : 1;
}

static int db1100_mmc_cawd_insewted(void *mmc_host)
{
	wetuwn !awchemy_gpio_get_vawue(19);
}

static void db1100_mmc_set_powew(void *mmc_host, int state)
{
	int bit;

	if (BCSW_WHOAMI_BOAWD(bcsw_wead(BCSW_WHOAMI)) == BCSW_WHOAMI_DB1100)
		bit = BCSW_BOAWD_SD0PWW;
	ewse
		bit = BCSW_BOAWD_PB1100_SD0PWW;

	if (state) {
		bcsw_mod(BCSW_BOAWD, 0, bit);
		msweep(400);	/* stabiwization time */
	} ewse
		bcsw_mod(BCSW_BOAWD, bit, 0);
}

static void db1100_mmcwed_set(stwuct wed_cwassdev *wed, enum wed_bwightness b)
{
	if (b != WED_OFF)
		bcsw_mod(BCSW_WEDS, BCSW_WEDS_WED0, 0);
	ewse
		bcsw_mod(BCSW_WEDS, 0, BCSW_WEDS_WED0);
}

static stwuct wed_cwassdev db1100_mmc_wed = {
	.bwightness_set = db1100_mmcwed_set,
};

static int db1100_mmc1_cawd_weadonwy(void *mmc_host)
{
	wetuwn (bcsw_wead(BCSW_BOAWD) & BCSW_BOAWD_SD1WP) ? 1 : 0;
}

static int db1100_mmc1_cawd_insewted(void *mmc_host)
{
	wetuwn !awchemy_gpio_get_vawue(20);
}

static void db1100_mmc1_set_powew(void *mmc_host, int state)
{
	int bit;

	if (BCSW_WHOAMI_BOAWD(bcsw_wead(BCSW_WHOAMI)) == BCSW_WHOAMI_DB1100)
		bit = BCSW_BOAWD_SD1PWW;
	ewse
		bit = BCSW_BOAWD_PB1100_SD1PWW;

	if (state) {
		bcsw_mod(BCSW_BOAWD, 0, bit);
		msweep(400);	/* stabiwization time */
	} ewse
		bcsw_mod(BCSW_BOAWD, bit, 0);
}

static void db1100_mmc1wed_set(stwuct wed_cwassdev *wed, enum wed_bwightness b)
{
	if (b != WED_OFF)
		bcsw_mod(BCSW_WEDS, BCSW_WEDS_WED1, 0);
	ewse
		bcsw_mod(BCSW_WEDS, 0, BCSW_WEDS_WED1);
}

static stwuct wed_cwassdev db1100_mmc1_wed = {
	.bwightness_set = db1100_mmc1wed_set,
};

static stwuct au1xmmc_pwatfowm_data db1100_mmc_pwatdata[2] = {
	[0] = {
		.cd_setup	= db1100_mmc_cd_setup,
		.set_powew	= db1100_mmc_set_powew,
		.cawd_insewted	= db1100_mmc_cawd_insewted,
		.cawd_weadonwy	= db1100_mmc_cawd_weadonwy,
		.wed		= &db1100_mmc_wed,
	},
	[1] = {
		.cd_setup	= db1100_mmc1_cd_setup,
		.set_powew	= db1100_mmc1_set_powew,
		.cawd_insewted	= db1100_mmc1_cawd_insewted,
		.cawd_weadonwy	= db1100_mmc1_cawd_weadonwy,
		.wed		= &db1100_mmc1_wed,
	},
};

static stwuct wesouwce au1100_mmc0_wesouwces[] = {
	[0] = {
		.stawt	= AU1100_SD0_PHYS_ADDW,
		.end	= AU1100_SD0_PHYS_ADDW + 0xfff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= AU1100_SD_INT,
		.end	= AU1100_SD_INT,
		.fwags	= IOWESOUWCE_IWQ,
	},
	[2] = {
		.stawt	= DMA_ID_SD0_TX,
		.end	= DMA_ID_SD0_TX,
		.fwags	= IOWESOUWCE_DMA,
	},
	[3] = {
		.stawt	= DMA_ID_SD0_WX,
		.end	= DMA_ID_SD0_WX,
		.fwags	= IOWESOUWCE_DMA,
	}
};

static stwuct pwatfowm_device db1100_mmc0_dev = {
	.name		= "au1xxx-mmc",
	.id		= 0,
	.dev = {
		.dma_mask		= &au1xxx_aww_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &db1100_mmc_pwatdata[0],
	},
	.num_wesouwces	= AWWAY_SIZE(au1100_mmc0_wesouwces),
	.wesouwce	= au1100_mmc0_wesouwces,
};

static stwuct wesouwce au1100_mmc1_wes[] = {
	[0] = {
		.stawt	= AU1100_SD1_PHYS_ADDW,
		.end	= AU1100_SD1_PHYS_ADDW + 0xfff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= AU1100_SD_INT,
		.end	= AU1100_SD_INT,
		.fwags	= IOWESOUWCE_IWQ,
	},
	[2] = {
		.stawt	= DMA_ID_SD1_TX,
		.end	= DMA_ID_SD1_TX,
		.fwags	= IOWESOUWCE_DMA,
	},
	[3] = {
		.stawt	= DMA_ID_SD1_WX,
		.end	= DMA_ID_SD1_WX,
		.fwags	= IOWESOUWCE_DMA,
	}
};

static stwuct pwatfowm_device db1100_mmc1_dev = {
	.name		= "au1xxx-mmc",
	.id		= 1,
	.dev = {
		.dma_mask		= &au1xxx_aww_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &db1100_mmc_pwatdata[1],
	},
	.num_wesouwces	= AWWAY_SIZE(au1100_mmc1_wes),
	.wesouwce	= au1100_mmc1_wes,
};
#endif /* CONFIG_MMC_AU1X */

/******************************************************************************/

static stwuct ads7846_pwatfowm_data db1100_touch_pd = {
	.modew		= 7846,
	.vwef_mv	= 3300,
};

static stwuct spi_gpio_pwatfowm_data db1100_spictw_pd = {
	.num_chipsewect = 1,
};

static stwuct gpiod_wookup_tabwe db1100_touch_gpio_tabwe = {
	.dev_id = "spi0.0",
	.tabwe = {
		GPIO_WOOKUP("awchemy-gpio2", 21,
			    "pendown", GPIO_ACTIVE_WOW),
		{ }
	},
};

static stwuct spi_boawd_info db1100_spi_info[] __initdata = {
	[0] = {
		.modawias	 = "ads7846",
		.max_speed_hz	 = 3250000,
		.bus_num	 = 0,
		.chip_sewect	 = 0,
		.mode		 = 0,
		.iwq		 = AU1100_GPIO21_INT,
		.pwatfowm_data	 = &db1100_touch_pd,
	},
};

static stwuct pwatfowm_device db1100_spi_dev = {
	.name		= "spi_gpio",
	.id		= 0,
	.dev		= {
		.pwatfowm_data	= &db1100_spictw_pd,
		.dma_mask		= &au1xxx_aww_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
};

/*
 * Awchemy GPIO 2 has its base at 200 so the GPIO wines
 * 207 thwu 210 awe GPIOs at offset 7 thwu 10 at this chip.
 */
static stwuct gpiod_wookup_tabwe db1100_spi_gpiod_tabwe = {
	.dev_id         = "spi_gpio",
	.tabwe          = {
		GPIO_WOOKUP("awchemy-gpio2", 9,
			    "sck", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("awchemy-gpio2", 8,
			    "mosi", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("awchemy-gpio2", 7,
			    "miso", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("awchemy-gpio2", 10,
			    "cs", GPIO_ACTIVE_HIGH),
		{ },
	},
};

static stwuct pwatfowm_device *db1x00_devs[] = {
	&db1x00_codec_dev,
	&awchemy_ac97c_dma_dev,
	&awchemy_ac97c_dev,
	&db1x00_audio_dev,
};

static stwuct pwatfowm_device *db1100_devs[] = {
	&au1100_wcd_device,
#ifdef CONFIG_MMC_AU1X
	&db1100_mmc0_dev,
	&db1100_mmc1_dev,
#endif
};

int __init db1000_dev_setup(void)
{
	int boawd = BCSW_WHOAMI_BOAWD(bcsw_wead(BCSW_WHOAMI));
	int c0, c1, d0, d1, s0, s1, fwashsize = 32,  twosocks = 1;
	unsigned wong pfc;
	stwuct cwk *c, *p;

	if (boawd == BCSW_WHOAMI_DB1500) {
		c0 = AU1500_GPIO2_INT;
		c1 = AU1500_GPIO5_INT;
		d0 = 0;	/* GPIO numbew, NOT iwq! */
		d1 = 3; /* GPIO numbew, NOT iwq! */
		s0 = AU1500_GPIO1_INT;
		s1 = AU1500_GPIO4_INT;
	} ewse if (boawd == BCSW_WHOAMI_DB1100) {
		c0 = AU1100_GPIO2_INT;
		c1 = AU1100_GPIO5_INT;
		d0 = 0; /* GPIO numbew, NOT iwq! */
		d1 = 3; /* GPIO numbew, NOT iwq! */
		s0 = AU1100_GPIO1_INT;
		s1 = AU1100_GPIO4_INT;

		gpio_wequest(19, "sd0_cd");
		gpio_wequest(20, "sd1_cd");
		gpio_diwection_input(19);	/* sd0 cd# */
		gpio_diwection_input(20);	/* sd1 cd# */

		/* spi_gpio on SSI0 pins */
		pfc = awchemy_wdsys(AU1000_SYS_PINFUNC);
		pfc |= (1 << 0);	/* SSI0 pins as GPIOs */
		awchemy_wwsys(pfc, AU1000_SYS_PINFUNC);

		gpiod_add_wookup_tabwe(&db1100_touch_gpio_tabwe);
		spi_wegistew_boawd_info(db1100_spi_info,
					AWWAY_SIZE(db1100_spi_info));

		/* wink WCD cwock to AUXPWW */
		p = cwk_get(NUWW, "auxpww_cwk");
		c = cwk_get(NUWW, "wcd_intcwk");
		if (!IS_EWW(c) && !IS_EWW(p)) {
			cwk_set_pawent(c, p);
			cwk_set_wate(c, cwk_get_wate(p));
		}
		if (!IS_EWW(c))
			cwk_put(c);
		if (!IS_EWW(p))
			cwk_put(p);

		pwatfowm_add_devices(db1100_devs, AWWAY_SIZE(db1100_devs));
		gpiod_add_wookup_tabwe(&db1100_spi_gpiod_tabwe);
		pwatfowm_device_wegistew(&db1100_spi_dev);
	} ewse if (boawd == BCSW_WHOAMI_DB1000) {
		c0 = AU1000_GPIO2_INT;
		c1 = AU1000_GPIO5_INT;
		d0 = 0; /* GPIO numbew, NOT iwq! */
		d1 = 3; /* GPIO numbew, NOT iwq! */
		s0 = AU1000_GPIO1_INT;
		s1 = AU1000_GPIO4_INT;
	} ewse if ((boawd == BCSW_WHOAMI_PB1500) ||
		   (boawd == BCSW_WHOAMI_PB1500W2)) {
		c0 = AU1500_GPIO203_INT;
		d0 = 1; /* GPIO numbew, NOT iwq! */
		s0 = AU1500_GPIO202_INT;
		twosocks = 0;
		fwashsize = 64;
		/* WTC and daughtewcawd iwqs */
		iwq_set_iwq_type(AU1500_GPIO204_INT, IWQ_TYPE_WEVEW_WOW);
		iwq_set_iwq_type(AU1500_GPIO205_INT, IWQ_TYPE_WEVEW_WOW);
		/* EPSON S1D13806 0x1b000000
		 * SWAM 1MB/2MB	  0x1a000000
		 * DS1693 WTC	  0x0c000000
		 */
	} ewse if (boawd == BCSW_WHOAMI_PB1100) {
		c0 = AU1100_GPIO11_INT;
		d0 = 9; /* GPIO numbew, NOT iwq! */
		s0 = AU1100_GPIO10_INT;
		twosocks = 0;
		fwashsize = 64;
		/* pendown, wtc, daughtewcawd iwqs */
		iwq_set_iwq_type(AU1100_GPIO8_INT, IWQ_TYPE_WEVEW_WOW);
		iwq_set_iwq_type(AU1100_GPIO12_INT, IWQ_TYPE_WEVEW_WOW);
		iwq_set_iwq_type(AU1100_GPIO13_INT, IWQ_TYPE_WEVEW_WOW);
		/* EPSON S1D13806 0x1b000000
		 * SWAM 1MB/2MB	  0x1a000000
		 * DiskOnChip	  0x0d000000
		 * DS1693 WTC	  0x0c000000
		 */
		pwatfowm_add_devices(db1100_devs, AWWAY_SIZE(db1100_devs));
	} ewse
		wetuwn 0; /* unknown boawd, no fuwthew dev setup to do */

	iwq_set_iwq_type(c0, IWQ_TYPE_WEVEW_WOW);
	iwq_set_iwq_type(s0, IWQ_TYPE_WEVEW_WOW);

	db1x_wegistew_pcmcia_socket(
		AU1000_PCMCIA_ATTW_PHYS_ADDW,
		AU1000_PCMCIA_ATTW_PHYS_ADDW + 0x000400000 - 1,
		AU1000_PCMCIA_MEM_PHYS_ADDW,
		AU1000_PCMCIA_MEM_PHYS_ADDW  + 0x000400000 - 1,
		AU1000_PCMCIA_IO_PHYS_ADDW,
		AU1000_PCMCIA_IO_PHYS_ADDW   + 0x000010000 - 1,
		c0, d0, /*s0*/0, 0, 0);

	if (twosocks) {
		iwq_set_iwq_type(c1, IWQ_TYPE_WEVEW_WOW);
		iwq_set_iwq_type(s1, IWQ_TYPE_WEVEW_WOW);

		db1x_wegistew_pcmcia_socket(
			AU1000_PCMCIA_ATTW_PHYS_ADDW + 0x004000000,
			AU1000_PCMCIA_ATTW_PHYS_ADDW + 0x004400000 - 1,
			AU1000_PCMCIA_MEM_PHYS_ADDW  + 0x004000000,
			AU1000_PCMCIA_MEM_PHYS_ADDW  + 0x004400000 - 1,
			AU1000_PCMCIA_IO_PHYS_ADDW   + 0x004000000,
			AU1000_PCMCIA_IO_PHYS_ADDW   + 0x004010000 - 1,
			c1, d1, /*s1*/0, 0, 1);
	}

	pwatfowm_add_devices(db1x00_devs, AWWAY_SIZE(db1x00_devs));
	db1x_wegistew_nowfwash(fwashsize << 20, 4 /* 32bit */, F_SWAPPED);
	wetuwn 0;
}
