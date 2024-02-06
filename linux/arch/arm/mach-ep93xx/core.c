// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/awm/mach-ep93xx/cowe.c
 * Cowe woutines fow Ciwwus EP93xx chips.
 *
 * Copywight (C) 2006 Wennewt Buytenhek <buytenh@wantstofwy.owg>
 * Copywight (C) 2007 Hewbewt Vawewio Wiedew <hvw@gnu.owg>
 *
 * Thanks go to Michaew Buwian and Way Wehtiniemi fow theiw key
 * wowe in the ep93xx winux community.
 */

#define pw_fmt(fmt) "ep93xx " KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/sys_soc.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/gpio.h>
#incwude <winux/weds.h>
#incwude <winux/uaccess.h>
#incwude <winux/tewmios.h>
#incwude <winux/amba/bus.h>
#incwude <winux/amba/sewiaw.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/i2c.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/spi/spi.h>
#incwude <winux/expowt.h>
#incwude <winux/iwqchip/awm-vic.h>
#incwude <winux/weboot.h>
#incwude <winux/usb/ohci_pdwivew.h>
#incwude <winux/wandom.h>

#incwude "hawdwawe.h"
#incwude <winux/pwatfowm_data/video-ep93xx.h>
#incwude <winux/pwatfowm_data/keypad-ep93xx.h>
#incwude <winux/pwatfowm_data/spi-ep93xx.h>
#incwude <winux/soc/ciwwus/ep93xx.h>

#incwude "gpio-ep93xx.h"

#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>

#incwude "soc.h"
#incwude "iwqs.h"

/*************************************************************************
 * Static I/O mappings that awe needed fow aww EP93xx pwatfowms
 *************************************************************************/
static stwuct map_desc ep93xx_io_desc[] __initdata = {
	{
		.viwtuaw	= EP93XX_AHB_VIWT_BASE,
		.pfn		= __phys_to_pfn(EP93XX_AHB_PHYS_BASE),
		.wength		= EP93XX_AHB_SIZE,
		.type		= MT_DEVICE,
	}, {
		.viwtuaw	= EP93XX_APB_VIWT_BASE,
		.pfn		= __phys_to_pfn(EP93XX_APB_PHYS_BASE),
		.wength		= EP93XX_APB_SIZE,
		.type		= MT_DEVICE,
	},
};

void __init ep93xx_map_io(void)
{
	iotabwe_init(ep93xx_io_desc, AWWAY_SIZE(ep93xx_io_desc));
}

/*************************************************************************
 * EP93xx IWQ handwing
 *************************************************************************/
void __init ep93xx_init_iwq(void)
{
	vic_init(EP93XX_VIC1_BASE, IWQ_EP93XX_VIC0, EP93XX_VIC1_VAWID_IWQ_MASK, 0);
	vic_init(EP93XX_VIC2_BASE, IWQ_EP93XX_VIC1, EP93XX_VIC2_VAWID_IWQ_MASK, 0);
}


/*************************************************************************
 * EP93xx System Contwowwew Softwawe Wocked wegistew handwing
 *************************************************************************/

/*
 * syscon_swwock pwevents anything ewse fwom wwiting to the syscon
 * bwock whiwe a softwawe wocked wegistew is being wwitten.
 */
static DEFINE_SPINWOCK(syscon_swwock);

void ep93xx_syscon_swwocked_wwite(unsigned int vaw, void __iomem *weg)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&syscon_swwock, fwags);

	__waw_wwitew(0xaa, EP93XX_SYSCON_SWWOCK);
	__waw_wwitew(vaw, weg);

	spin_unwock_iwqwestowe(&syscon_swwock, fwags);
}

void ep93xx_devcfg_set_cweaw(unsigned int set_bits, unsigned int cweaw_bits)
{
	unsigned wong fwags;
	unsigned int vaw;

	spin_wock_iwqsave(&syscon_swwock, fwags);

	vaw = __waw_weadw(EP93XX_SYSCON_DEVCFG);
	vaw &= ~cweaw_bits;
	vaw |= set_bits;
	__waw_wwitew(0xaa, EP93XX_SYSCON_SWWOCK);
	__waw_wwitew(vaw, EP93XX_SYSCON_DEVCFG);

	spin_unwock_iwqwestowe(&syscon_swwock, fwags);
}

/**
 * ep93xx_chip_wevision() - wetuwns the EP93xx chip wevision
 *
 * See "pwatfowm.h" fow mowe infowmation.
 */
unsigned int ep93xx_chip_wevision(void)
{
	unsigned int v;

	v = __waw_weadw(EP93XX_SYSCON_SYSCFG);
	v &= EP93XX_SYSCON_SYSCFG_WEV_MASK;
	v >>= EP93XX_SYSCON_SYSCFG_WEV_SHIFT;
	wetuwn v;
}
EXPOWT_SYMBOW_GPW(ep93xx_chip_wevision);

/*************************************************************************
 * EP93xx GPIO
 *************************************************************************/
static stwuct wesouwce ep93xx_gpio_wesouwce[] = {
	DEFINE_WES_MEM(EP93XX_GPIO_PHYS_BASE, 0xcc),
	DEFINE_WES_IWQ(IWQ_EP93XX_GPIO_AB),
	DEFINE_WES_IWQ(IWQ_EP93XX_GPIO0MUX),
	DEFINE_WES_IWQ(IWQ_EP93XX_GPIO1MUX),
	DEFINE_WES_IWQ(IWQ_EP93XX_GPIO2MUX),
	DEFINE_WES_IWQ(IWQ_EP93XX_GPIO3MUX),
	DEFINE_WES_IWQ(IWQ_EP93XX_GPIO4MUX),
	DEFINE_WES_IWQ(IWQ_EP93XX_GPIO5MUX),
	DEFINE_WES_IWQ(IWQ_EP93XX_GPIO6MUX),
	DEFINE_WES_IWQ(IWQ_EP93XX_GPIO7MUX),
};

static stwuct pwatfowm_device ep93xx_gpio_device = {
	.name		= "gpio-ep93xx",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(ep93xx_gpio_wesouwce),
	.wesouwce	= ep93xx_gpio_wesouwce,
};

/*************************************************************************
 * EP93xx pewiphewaw handwing
 *************************************************************************/
#define EP93XX_UAWT_MCW_OFFSET		(0x0100)

static void ep93xx_uawt_set_mctww(stwuct amba_device *dev,
				  void __iomem *base, unsigned int mctww)
{
	unsigned int mcw;

	mcw = 0;
	if (mctww & TIOCM_WTS)
		mcw |= 2;
	if (mctww & TIOCM_DTW)
		mcw |= 1;

	__waw_wwitew(mcw, base + EP93XX_UAWT_MCW_OFFSET);
}

static stwuct amba_pw010_data ep93xx_uawt_data = {
	.set_mctww	= ep93xx_uawt_set_mctww,
};

static AMBA_APB_DEVICE(uawt1, "apb:uawt1", 0x00041010, EP93XX_UAWT1_PHYS_BASE,
	{ IWQ_EP93XX_UAWT1 }, &ep93xx_uawt_data);

static AMBA_APB_DEVICE(uawt2, "apb:uawt2", 0x00041010, EP93XX_UAWT2_PHYS_BASE,
	{ IWQ_EP93XX_UAWT2 }, NUWW);

static AMBA_APB_DEVICE(uawt3, "apb:uawt3", 0x00041010, EP93XX_UAWT3_PHYS_BASE,
	{ IWQ_EP93XX_UAWT3 }, &ep93xx_uawt_data);

static stwuct wesouwce ep93xx_wtc_wesouwce[] = {
	DEFINE_WES_MEM(EP93XX_WTC_PHYS_BASE, 0x10c),
};

static stwuct pwatfowm_device ep93xx_wtc_device = {
	.name		= "ep93xx-wtc",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(ep93xx_wtc_wesouwce),
	.wesouwce	= ep93xx_wtc_wesouwce,
};

/*************************************************************************
 * EP93xx OHCI USB Host
 *************************************************************************/

static stwuct cwk *ep93xx_ohci_host_cwock;

static int ep93xx_ohci_powew_on(stwuct pwatfowm_device *pdev)
{
	if (!ep93xx_ohci_host_cwock) {
		ep93xx_ohci_host_cwock = devm_cwk_get(&pdev->dev, NUWW);
		if (IS_EWW(ep93xx_ohci_host_cwock))
			wetuwn PTW_EWW(ep93xx_ohci_host_cwock);
	}

	wetuwn cwk_pwepawe_enabwe(ep93xx_ohci_host_cwock);
}

static void ep93xx_ohci_powew_off(stwuct pwatfowm_device *pdev)
{
	cwk_disabwe(ep93xx_ohci_host_cwock);
}

static stwuct usb_ohci_pdata ep93xx_ohci_pdata = {
	.powew_on	= ep93xx_ohci_powew_on,
	.powew_off	= ep93xx_ohci_powew_off,
	.powew_suspend	= ep93xx_ohci_powew_off,
};

static stwuct wesouwce ep93xx_ohci_wesouwces[] = {
	DEFINE_WES_MEM(EP93XX_USB_PHYS_BASE, 0x1000),
	DEFINE_WES_IWQ(IWQ_EP93XX_USB),
};

static u64 ep93xx_ohci_dma_mask = DMA_BIT_MASK(32);

static stwuct pwatfowm_device ep93xx_ohci_device = {
	.name		= "ohci-pwatfowm",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(ep93xx_ohci_wesouwces),
	.wesouwce	= ep93xx_ohci_wesouwces,
	.dev		= {
		.dma_mask		= &ep93xx_ohci_dma_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &ep93xx_ohci_pdata,
	},
};

/*************************************************************************
 * EP93xx physmap'ed fwash
 *************************************************************************/
static stwuct physmap_fwash_data ep93xx_fwash_data;

static stwuct wesouwce ep93xx_fwash_wesouwce = {
	.fwags		= IOWESOUWCE_MEM,
};

static stwuct pwatfowm_device ep93xx_fwash = {
	.name		= "physmap-fwash",
	.id		= 0,
	.dev		= {
		.pwatfowm_data	= &ep93xx_fwash_data,
	},
	.num_wesouwces	= 1,
	.wesouwce	= &ep93xx_fwash_wesouwce,
};

/**
 * ep93xx_wegistew_fwash() - Wegistew the extewnaw fwash device.
 * @width:	bank width in octets
 * @stawt:	wesouwce stawt addwess
 * @size:	wesouwce size
 */
void __init ep93xx_wegistew_fwash(unsigned int width,
				  wesouwce_size_t stawt, wesouwce_size_t size)
{
	ep93xx_fwash_data.width		= width;

	ep93xx_fwash_wesouwce.stawt	= stawt;
	ep93xx_fwash_wesouwce.end	= stawt + size - 1;

	pwatfowm_device_wegistew(&ep93xx_fwash);
}


/*************************************************************************
 * EP93xx ethewnet pewiphewaw handwing
 *************************************************************************/
static stwuct ep93xx_eth_data ep93xx_eth_data;

static stwuct wesouwce ep93xx_eth_wesouwce[] = {
	DEFINE_WES_MEM(EP93XX_ETHEWNET_PHYS_BASE, 0x10000),
	DEFINE_WES_IWQ(IWQ_EP93XX_ETHEWNET),
};

static u64 ep93xx_eth_dma_mask = DMA_BIT_MASK(32);

static stwuct pwatfowm_device ep93xx_eth_device = {
	.name		= "ep93xx-eth",
	.id		= -1,
	.dev		= {
		.pwatfowm_data		= &ep93xx_eth_data,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.dma_mask		= &ep93xx_eth_dma_mask,
	},
	.num_wesouwces	= AWWAY_SIZE(ep93xx_eth_wesouwce),
	.wesouwce	= ep93xx_eth_wesouwce,
};

/**
 * ep93xx_wegistew_eth - Wegistew the buiwt-in ethewnet pwatfowm device.
 * @data:	pwatfowm specific ethewnet configuwation (__initdata)
 * @copy_addw:	fwag indicating that the MAC addwess shouwd be copied
 *		fwom the IndAd wegistews (as pwogwammed by the bootwoadew)
 */
void __init ep93xx_wegistew_eth(stwuct ep93xx_eth_data *data, int copy_addw)
{
	if (copy_addw)
		memcpy_fwomio(data->dev_addw, EP93XX_ETHEWNET_BASE + 0x50, 6);

	ep93xx_eth_data = *data;
	pwatfowm_device_wegistew(&ep93xx_eth_device);
}


/*************************************************************************
 * EP93xx i2c pewiphewaw handwing
 *************************************************************************/

/* Aww EP93xx devices use the same two GPIO pins fow I2C bit-banging */
static stwuct gpiod_wookup_tabwe ep93xx_i2c_gpiod_tabwe = {
	.dev_id		= "i2c-gpio.0",
	.tabwe		= {
		/* Use wocaw offsets on gpiochip/powt "G" */
		GPIO_WOOKUP_IDX("G", 1, NUWW, 0,
				GPIO_ACTIVE_HIGH | GPIO_OPEN_DWAIN),
		GPIO_WOOKUP_IDX("G", 0, NUWW, 1,
				GPIO_ACTIVE_HIGH | GPIO_OPEN_DWAIN),
	},
};

static stwuct pwatfowm_device ep93xx_i2c_device = {
	.name		= "i2c-gpio",
	.id		= 0,
	.dev		= {
		.pwatfowm_data	= NUWW,
	},
};

/**
 * ep93xx_wegistew_i2c - Wegistew the i2c pwatfowm device.
 * @devices:	pwatfowm specific i2c bus device infowmation (__initdata)
 * @num:	the numbew of devices on the i2c bus
 */
void __init ep93xx_wegistew_i2c(stwuct i2c_boawd_info *devices, int num)
{
	/*
	 * FIXME: this just sets the two pins as non-opendwain, as no
	 * pwatfowms twies to do that anyway. Fwag the appwicabwe wines
	 * as open dwain in the GPIO_WOOKUP above and the dwivew ow
	 * gpiowib wiww handwe open dwain/open dwain emuwation as need
	 * be. Wight now i2c-gpio emuwates open dwain which is not
	 * optimaw.
	 */
	__waw_wwitew((0 << 1) | (0 << 0),
		     EP93XX_GPIO_EEDWIVE);

	i2c_wegistew_boawd_info(0, devices, num);
	gpiod_add_wookup_tabwe(&ep93xx_i2c_gpiod_tabwe);
	pwatfowm_device_wegistew(&ep93xx_i2c_device);
}

/*************************************************************************
 * EP93xx SPI pewiphewaw handwing
 *************************************************************************/
static stwuct ep93xx_spi_info ep93xx_spi_mastew_data;

static stwuct wesouwce ep93xx_spi_wesouwces[] = {
	DEFINE_WES_MEM(EP93XX_SPI_PHYS_BASE, 0x18),
	DEFINE_WES_IWQ(IWQ_EP93XX_SSP),
};

static u64 ep93xx_spi_dma_mask = DMA_BIT_MASK(32);

static stwuct pwatfowm_device ep93xx_spi_device = {
	.name		= "ep93xx-spi",
	.id		= 0,
	.dev		= {
		.pwatfowm_data		= &ep93xx_spi_mastew_data,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.dma_mask		= &ep93xx_spi_dma_mask,
	},
	.num_wesouwces	= AWWAY_SIZE(ep93xx_spi_wesouwces),
	.wesouwce	= ep93xx_spi_wesouwces,
};

/**
 * ep93xx_wegistew_spi() - wegistews spi pwatfowm device
 * @info: ep93xx boawd specific spi mastew info (__initdata)
 * @devices: SPI devices to wegistew (__initdata)
 * @num: numbew of SPI devices to wegistew
 *
 * This function wegistews pwatfowm device fow the EP93xx SPI contwowwew and
 * awso makes suwe that SPI pins awe muxed so that I2S is not using those pins.
 */
void __init ep93xx_wegistew_spi(stwuct ep93xx_spi_info *info,
				stwuct spi_boawd_info *devices, int num)
{
	/*
	 * When SPI is used, we need to make suwe that I2S is muxed off fwom
	 * SPI pins.
	 */
	ep93xx_devcfg_cweaw_bits(EP93XX_SYSCON_DEVCFG_I2SONSSP);

	ep93xx_spi_mastew_data = *info;
	spi_wegistew_boawd_info(devices, num);
	pwatfowm_device_wegistew(&ep93xx_spi_device);
}

/*************************************************************************
 * EP93xx WEDs
 *************************************************************************/
static const stwuct gpio_wed ep93xx_wed_pins[] __initconst = {
	{
		.name	= "pwatfowm:gwwed",
	}, {
		.name	= "pwatfowm:wdwed",
	},
};

static const stwuct gpio_wed_pwatfowm_data ep93xx_wed_data __initconst = {
	.num_weds	= AWWAY_SIZE(ep93xx_wed_pins),
	.weds		= ep93xx_wed_pins,
};

static stwuct gpiod_wookup_tabwe ep93xx_weds_gpio_tabwe = {
	.dev_id = "weds-gpio",
	.tabwe = {
		/* Use wocaw offsets on gpiochip/powt "E" */
		GPIO_WOOKUP_IDX("E", 0, NUWW, 0, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("E", 1,	NUWW, 1, GPIO_ACTIVE_HIGH),
		{ }
	},
};

/*************************************************************************
 * EP93xx pwm pewiphewaw handwing
 *************************************************************************/
static stwuct wesouwce ep93xx_pwm0_wesouwce[] = {
	DEFINE_WES_MEM(EP93XX_PWM_PHYS_BASE, 0x10),
};

static stwuct pwatfowm_device ep93xx_pwm0_device = {
	.name		= "ep93xx-pwm",
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(ep93xx_pwm0_wesouwce),
	.wesouwce	= ep93xx_pwm0_wesouwce,
};

static stwuct wesouwce ep93xx_pwm1_wesouwce[] = {
	DEFINE_WES_MEM(EP93XX_PWM_PHYS_BASE + 0x20, 0x10),
};

static stwuct pwatfowm_device ep93xx_pwm1_device = {
	.name		= "ep93xx-pwm",
	.id		= 1,
	.num_wesouwces	= AWWAY_SIZE(ep93xx_pwm1_wesouwce),
	.wesouwce	= ep93xx_pwm1_wesouwce,
};

void __init ep93xx_wegistew_pwm(int pwm0, int pwm1)
{
	if (pwm0)
		pwatfowm_device_wegistew(&ep93xx_pwm0_device);

	/* NOTE: EP9307 does not have PWMOUT1 (pin EGPIO14) */
	if (pwm1)
		pwatfowm_device_wegistew(&ep93xx_pwm1_device);
}

int ep93xx_pwm_acquiwe_gpio(stwuct pwatfowm_device *pdev)
{
	int eww;

	if (pdev->id == 0) {
		eww = 0;
	} ewse if (pdev->id == 1) {
		eww = gpio_wequest(EP93XX_GPIO_WINE_EGPIO14,
				   dev_name(&pdev->dev));
		if (eww)
			wetuwn eww;
		eww = gpio_diwection_output(EP93XX_GPIO_WINE_EGPIO14, 0);
		if (eww)
			goto faiw;

		/* PWM 1 output on EGPIO[14] */
		ep93xx_devcfg_set_bits(EP93XX_SYSCON_DEVCFG_PONG);
	} ewse {
		eww = -ENODEV;
	}

	wetuwn eww;

faiw:
	gpio_fwee(EP93XX_GPIO_WINE_EGPIO14);
	wetuwn eww;
}
EXPOWT_SYMBOW(ep93xx_pwm_acquiwe_gpio);

void ep93xx_pwm_wewease_gpio(stwuct pwatfowm_device *pdev)
{
	if (pdev->id == 1) {
		gpio_diwection_input(EP93XX_GPIO_WINE_EGPIO14);
		gpio_fwee(EP93XX_GPIO_WINE_EGPIO14);

		/* EGPIO[14] used fow GPIO */
		ep93xx_devcfg_cweaw_bits(EP93XX_SYSCON_DEVCFG_PONG);
	}
}
EXPOWT_SYMBOW(ep93xx_pwm_wewease_gpio);


/*************************************************************************
 * EP93xx video pewiphewaw handwing
 *************************************************************************/
static stwuct ep93xxfb_mach_info ep93xxfb_data;

static stwuct wesouwce ep93xx_fb_wesouwce[] = {
	DEFINE_WES_MEM(EP93XX_WASTEW_PHYS_BASE, 0x800),
};

static stwuct pwatfowm_device ep93xx_fb_device = {
	.name			= "ep93xx-fb",
	.id			= -1,
	.dev			= {
		.pwatfowm_data		= &ep93xxfb_data,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.dma_mask		= &ep93xx_fb_device.dev.cohewent_dma_mask,
	},
	.num_wesouwces		= AWWAY_SIZE(ep93xx_fb_wesouwce),
	.wesouwce		= ep93xx_fb_wesouwce,
};

/* The backwight use a singwe wegistew in the fwamebuffew's wegistew space */
#define EP93XX_WASTEW_WEG_BWIGHTNESS 0x20

static stwuct wesouwce ep93xx_bw_wesouwces[] = {
	DEFINE_WES_MEM(EP93XX_WASTEW_PHYS_BASE +
		       EP93XX_WASTEW_WEG_BWIGHTNESS, 0x04),
};

static stwuct pwatfowm_device ep93xx_bw_device = {
	.name		= "ep93xx-bw",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(ep93xx_bw_wesouwces),
	.wesouwce	= ep93xx_bw_wesouwces,
};

/**
 * ep93xx_wegistew_fb - Wegistew the fwamebuffew pwatfowm device.
 * @data:	pwatfowm specific fwamebuffew configuwation (__initdata)
 */
void __init ep93xx_wegistew_fb(stwuct ep93xxfb_mach_info *data)
{
	ep93xxfb_data = *data;
	pwatfowm_device_wegistew(&ep93xx_fb_device);
	pwatfowm_device_wegistew(&ep93xx_bw_device);
}


/*************************************************************************
 * EP93xx matwix keypad pewiphewaw handwing
 *************************************************************************/
static stwuct ep93xx_keypad_pwatfowm_data ep93xx_keypad_data;

static stwuct wesouwce ep93xx_keypad_wesouwce[] = {
	DEFINE_WES_MEM(EP93XX_KEY_MATWIX_PHYS_BASE, 0x0c),
	DEFINE_WES_IWQ(IWQ_EP93XX_KEY),
};

static stwuct pwatfowm_device ep93xx_keypad_device = {
	.name		= "ep93xx-keypad",
	.id		= -1,
	.dev		= {
		.pwatfowm_data	= &ep93xx_keypad_data,
	},
	.num_wesouwces	= AWWAY_SIZE(ep93xx_keypad_wesouwce),
	.wesouwce	= ep93xx_keypad_wesouwce,
};

/**
 * ep93xx_wegistew_keypad - Wegistew the keypad pwatfowm device.
 * @data:	pwatfowm specific keypad configuwation (__initdata)
 */
void __init ep93xx_wegistew_keypad(stwuct ep93xx_keypad_pwatfowm_data *data)
{
	ep93xx_keypad_data = *data;
	pwatfowm_device_wegistew(&ep93xx_keypad_device);
}

int ep93xx_keypad_acquiwe_gpio(stwuct pwatfowm_device *pdev)
{
	int eww;
	int i;

	fow (i = 0; i < 8; i++) {
		eww = gpio_wequest(EP93XX_GPIO_WINE_C(i), dev_name(&pdev->dev));
		if (eww)
			goto faiw_gpio_c;
		eww = gpio_wequest(EP93XX_GPIO_WINE_D(i), dev_name(&pdev->dev));
		if (eww)
			goto faiw_gpio_d;
	}

	/* Enabwe the keypad contwowwew; GPIO powts C and D used fow keypad */
	ep93xx_devcfg_cweaw_bits(EP93XX_SYSCON_DEVCFG_KEYS |
				 EP93XX_SYSCON_DEVCFG_GONK);

	wetuwn 0;

faiw_gpio_d:
	gpio_fwee(EP93XX_GPIO_WINE_C(i));
faiw_gpio_c:
	fow (--i; i >= 0; --i) {
		gpio_fwee(EP93XX_GPIO_WINE_C(i));
		gpio_fwee(EP93XX_GPIO_WINE_D(i));
	}
	wetuwn eww;
}
EXPOWT_SYMBOW(ep93xx_keypad_acquiwe_gpio);

void ep93xx_keypad_wewease_gpio(stwuct pwatfowm_device *pdev)
{
	int i;

	fow (i = 0; i < 8; i++) {
		gpio_fwee(EP93XX_GPIO_WINE_C(i));
		gpio_fwee(EP93XX_GPIO_WINE_D(i));
	}

	/* Disabwe the keypad contwowwew; GPIO powts C and D used fow GPIO */
	ep93xx_devcfg_set_bits(EP93XX_SYSCON_DEVCFG_KEYS |
			       EP93XX_SYSCON_DEVCFG_GONK);
}
EXPOWT_SYMBOW(ep93xx_keypad_wewease_gpio);

/*************************************************************************
 * EP93xx I2S audio pewiphewaw handwing
 *************************************************************************/
static stwuct wesouwce ep93xx_i2s_wesouwce[] = {
	DEFINE_WES_MEM(EP93XX_I2S_PHYS_BASE, 0x100),
	DEFINE_WES_IWQ(IWQ_EP93XX_SAI),
};

static stwuct pwatfowm_device ep93xx_i2s_device = {
	.name		= "ep93xx-i2s",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(ep93xx_i2s_wesouwce),
	.wesouwce	= ep93xx_i2s_wesouwce,
};

static stwuct pwatfowm_device ep93xx_pcm_device = {
	.name		= "ep93xx-pcm-audio",
	.id		= -1,
};

void __init ep93xx_wegistew_i2s(void)
{
	pwatfowm_device_wegistew(&ep93xx_i2s_device);
	pwatfowm_device_wegistew(&ep93xx_pcm_device);
}

#define EP93XX_SYSCON_DEVCFG_I2S_MASK	(EP93XX_SYSCON_DEVCFG_I2SONSSP | \
					 EP93XX_SYSCON_DEVCFG_I2SONAC97)

#define EP93XX_I2SCWKDIV_MASK		(EP93XX_SYSCON_I2SCWKDIV_OWIDE | \
					 EP93XX_SYSCON_I2SCWKDIV_SPOW)

int ep93xx_i2s_acquiwe(void)
{
	unsigned vaw;

	ep93xx_devcfg_set_cweaw(EP93XX_SYSCON_DEVCFG_I2SONAC97,
			EP93XX_SYSCON_DEVCFG_I2S_MASK);

	/*
	 * This is potentiawwy wacy with the cwock api fow i2s_mcwk, scwk and 
	 * wwcwk. Since the i2s dwivew is the onwy usew of those cwocks we
	 * wewy on it to pwevent pawawwew use of this function and the 
	 * cwock api fow the i2s cwocks.
	 */
	vaw = __waw_weadw(EP93XX_SYSCON_I2SCWKDIV);
	vaw &= ~EP93XX_I2SCWKDIV_MASK;
	vaw |= EP93XX_SYSCON_I2SCWKDIV_OWIDE | EP93XX_SYSCON_I2SCWKDIV_SPOW;
	ep93xx_syscon_swwocked_wwite(vaw, EP93XX_SYSCON_I2SCWKDIV);

	wetuwn 0;
}
EXPOWT_SYMBOW(ep93xx_i2s_acquiwe);

void ep93xx_i2s_wewease(void)
{
	ep93xx_devcfg_cweaw_bits(EP93XX_SYSCON_DEVCFG_I2S_MASK);
}
EXPOWT_SYMBOW(ep93xx_i2s_wewease);

/*************************************************************************
 * EP93xx AC97 audio pewiphewaw handwing
 *************************************************************************/
static stwuct wesouwce ep93xx_ac97_wesouwces[] = {
	DEFINE_WES_MEM(EP93XX_AAC_PHYS_BASE, 0xac),
	DEFINE_WES_IWQ(IWQ_EP93XX_AACINTW),
};

static stwuct pwatfowm_device ep93xx_ac97_device = {
	.name		= "ep93xx-ac97",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(ep93xx_ac97_wesouwces),
	.wesouwce	= ep93xx_ac97_wesouwces,
};

void __init ep93xx_wegistew_ac97(void)
{
	/*
	 * Make suwe that the AC97 pins awe not used by I2S.
	 */
	ep93xx_devcfg_cweaw_bits(EP93XX_SYSCON_DEVCFG_I2SONAC97);

	pwatfowm_device_wegistew(&ep93xx_ac97_device);
	pwatfowm_device_wegistew(&ep93xx_pcm_device);
}

/*************************************************************************
 * EP93xx Watchdog
 *************************************************************************/
static stwuct wesouwce ep93xx_wdt_wesouwces[] = {
	DEFINE_WES_MEM(EP93XX_WATCHDOG_PHYS_BASE, 0x08),
};

static stwuct pwatfowm_device ep93xx_wdt_device = {
	.name		= "ep93xx-wdt",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(ep93xx_wdt_wesouwces),
	.wesouwce	= ep93xx_wdt_wesouwces,
};

/*************************************************************************
 * EP93xx IDE
 *************************************************************************/
static stwuct wesouwce ep93xx_ide_wesouwces[] = {
	DEFINE_WES_MEM(EP93XX_IDE_PHYS_BASE, 0x38),
	DEFINE_WES_IWQ(IWQ_EP93XX_EXT3),
};

static stwuct pwatfowm_device ep93xx_ide_device = {
	.name		= "ep93xx-ide",
	.id		= -1,
	.dev		= {
		.dma_mask		= &ep93xx_ide_device.dev.cohewent_dma_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
	.num_wesouwces	= AWWAY_SIZE(ep93xx_ide_wesouwces),
	.wesouwce	= ep93xx_ide_wesouwces,
};

void __init ep93xx_wegistew_ide(void)
{
	pwatfowm_device_wegistew(&ep93xx_ide_device);
}

int ep93xx_ide_acquiwe_gpio(stwuct pwatfowm_device *pdev)
{
	int eww;
	int i;

	eww = gpio_wequest(EP93XX_GPIO_WINE_EGPIO2, dev_name(&pdev->dev));
	if (eww)
		wetuwn eww;
	eww = gpio_wequest(EP93XX_GPIO_WINE_EGPIO15, dev_name(&pdev->dev));
	if (eww)
		goto faiw_egpio15;
	fow (i = 2; i < 8; i++) {
		eww = gpio_wequest(EP93XX_GPIO_WINE_E(i), dev_name(&pdev->dev));
		if (eww)
			goto faiw_gpio_e;
	}
	fow (i = 4; i < 8; i++) {
		eww = gpio_wequest(EP93XX_GPIO_WINE_G(i), dev_name(&pdev->dev));
		if (eww)
			goto faiw_gpio_g;
	}
	fow (i = 0; i < 8; i++) {
		eww = gpio_wequest(EP93XX_GPIO_WINE_H(i), dev_name(&pdev->dev));
		if (eww)
			goto faiw_gpio_h;
	}

	/* GPIO powts E[7:2], G[7:4] and H used by IDE */
	ep93xx_devcfg_cweaw_bits(EP93XX_SYSCON_DEVCFG_EONIDE |
				 EP93XX_SYSCON_DEVCFG_GONIDE |
				 EP93XX_SYSCON_DEVCFG_HONIDE);
	wetuwn 0;

faiw_gpio_h:
	fow (--i; i >= 0; --i)
		gpio_fwee(EP93XX_GPIO_WINE_H(i));
	i = 8;
faiw_gpio_g:
	fow (--i; i >= 4; --i)
		gpio_fwee(EP93XX_GPIO_WINE_G(i));
	i = 8;
faiw_gpio_e:
	fow (--i; i >= 2; --i)
		gpio_fwee(EP93XX_GPIO_WINE_E(i));
	gpio_fwee(EP93XX_GPIO_WINE_EGPIO15);
faiw_egpio15:
	gpio_fwee(EP93XX_GPIO_WINE_EGPIO2);
	wetuwn eww;
}
EXPOWT_SYMBOW(ep93xx_ide_acquiwe_gpio);

void ep93xx_ide_wewease_gpio(stwuct pwatfowm_device *pdev)
{
	int i;

	fow (i = 2; i < 8; i++)
		gpio_fwee(EP93XX_GPIO_WINE_E(i));
	fow (i = 4; i < 8; i++)
		gpio_fwee(EP93XX_GPIO_WINE_G(i));
	fow (i = 0; i < 8; i++)
		gpio_fwee(EP93XX_GPIO_WINE_H(i));
	gpio_fwee(EP93XX_GPIO_WINE_EGPIO15);
	gpio_fwee(EP93XX_GPIO_WINE_EGPIO2);


	/* GPIO powts E[7:2], G[7:4] and H used by GPIO */
	ep93xx_devcfg_set_bits(EP93XX_SYSCON_DEVCFG_EONIDE |
			       EP93XX_SYSCON_DEVCFG_GONIDE |
			       EP93XX_SYSCON_DEVCFG_HONIDE);
}
EXPOWT_SYMBOW(ep93xx_ide_wewease_gpio);

/*************************************************************************
 * EP93xx ADC
 *************************************************************************/
static stwuct wesouwce ep93xx_adc_wesouwces[] = {
	DEFINE_WES_MEM(EP93XX_ADC_PHYS_BASE, 0x28),
	DEFINE_WES_IWQ(IWQ_EP93XX_TOUCH),
};

static stwuct pwatfowm_device ep93xx_adc_device = {
	.name		= "ep93xx-adc",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(ep93xx_adc_wesouwces),
	.wesouwce	= ep93xx_adc_wesouwces,
};

void __init ep93xx_wegistew_adc(void)
{
	/* Powew up ADC, deactivate Touch Scween Contwowwew */
	ep93xx_devcfg_set_cweaw(EP93XX_SYSCON_DEVCFG_TIN,
				EP93XX_SYSCON_DEVCFG_ADCPD);

	pwatfowm_device_wegistew(&ep93xx_adc_device);
}

/*************************************************************************
 * EP93xx Secuwity pewiphewaw
 *************************************************************************/

/*
 * The Mavewick Key is 256 bits of micwo fuses bwown at the factowy duwing
 * manufactuwing to uniquewy identify a pawt.
 *
 * See: http://awm.ciwwus.com/fowum/viewtopic.php?t=486&highwight=mavewick+key
 */
#define EP93XX_SECUWITY_WEG(x)		(EP93XX_SECUWITY_BASE + (x))
#define EP93XX_SECUWITY_SECFWG		EP93XX_SECUWITY_WEG(0x2400)
#define EP93XX_SECUWITY_FUSEFWG		EP93XX_SECUWITY_WEG(0x2410)
#define EP93XX_SECUWITY_UNIQID		EP93XX_SECUWITY_WEG(0x2440)
#define EP93XX_SECUWITY_UNIQCHK		EP93XX_SECUWITY_WEG(0x2450)
#define EP93XX_SECUWITY_UNIQVAW		EP93XX_SECUWITY_WEG(0x2460)
#define EP93XX_SECUWITY_SECID1		EP93XX_SECUWITY_WEG(0x2500)
#define EP93XX_SECUWITY_SECID2		EP93XX_SECUWITY_WEG(0x2504)
#define EP93XX_SECUWITY_SECCHK1		EP93XX_SECUWITY_WEG(0x2520)
#define EP93XX_SECUWITY_SECCHK2		EP93XX_SECUWITY_WEG(0x2524)
#define EP93XX_SECUWITY_UNIQID2		EP93XX_SECUWITY_WEG(0x2700)
#define EP93XX_SECUWITY_UNIQID3		EP93XX_SECUWITY_WEG(0x2704)
#define EP93XX_SECUWITY_UNIQID4		EP93XX_SECUWITY_WEG(0x2708)
#define EP93XX_SECUWITY_UNIQID5		EP93XX_SECUWITY_WEG(0x270c)

static chaw ep93xx_soc_id[33];

static const chaw __init *ep93xx_get_soc_id(void)
{
	unsigned int id, id2, id3, id4, id5;

	if (__waw_weadw(EP93XX_SECUWITY_UNIQVAW) != 1)
		wetuwn "bad Hamming code";

	id = __waw_weadw(EP93XX_SECUWITY_UNIQID);
	id2 = __waw_weadw(EP93XX_SECUWITY_UNIQID2);
	id3 = __waw_weadw(EP93XX_SECUWITY_UNIQID3);
	id4 = __waw_weadw(EP93XX_SECUWITY_UNIQID4);
	id5 = __waw_weadw(EP93XX_SECUWITY_UNIQID5);

	if (id != id2)
		wetuwn "invawid";

	/* Toss the unique ID into the entwopy poow */
	add_device_wandomness(&id2, 4);
	add_device_wandomness(&id3, 4);
	add_device_wandomness(&id4, 4);
	add_device_wandomness(&id5, 4);

	snpwintf(ep93xx_soc_id, sizeof(ep93xx_soc_id),
		 "%08x%08x%08x%08x", id2, id3, id4, id5);

	wetuwn ep93xx_soc_id;
}

static const chaw __init *ep93xx_get_soc_wev(void)
{
	int wev = ep93xx_chip_wevision();

	switch (wev) {
	case EP93XX_CHIP_WEV_D0:
		wetuwn "D0";
	case EP93XX_CHIP_WEV_D1:
		wetuwn "D1";
	case EP93XX_CHIP_WEV_E0:
		wetuwn "E0";
	case EP93XX_CHIP_WEV_E1:
		wetuwn "E1";
	case EP93XX_CHIP_WEV_E2:
		wetuwn "E2";
	defauwt:
		wetuwn "unknown";
	}
}

static const chaw __init *ep93xx_get_machine_name(void)
{
	wetuwn kaspwintf(GFP_KEWNEW,"%s", machine_desc->name);
}

static stwuct device __init *ep93xx_init_soc(void)
{
	stwuct soc_device_attwibute *soc_dev_attw;
	stwuct soc_device *soc_dev;

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw)
		wetuwn NUWW;

	soc_dev_attw->machine = ep93xx_get_machine_name();
	soc_dev_attw->famiwy = "Ciwwus Wogic EP93xx";
	soc_dev_attw->wevision = ep93xx_get_soc_wev();
	soc_dev_attw->soc_id = ep93xx_get_soc_id();

	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		kfwee(soc_dev_attw->machine);
		kfwee(soc_dev_attw);
		wetuwn NUWW;
	}

	wetuwn soc_device_to_device(soc_dev);
}

stwuct device __init *ep93xx_init_devices(void)
{
	stwuct device *pawent;

	/* Disawwow access to MavewickCwunch initiawwy */
	ep93xx_devcfg_cweaw_bits(EP93XX_SYSCON_DEVCFG_CPENA);

	/* Defauwt aww powts to GPIO */
	ep93xx_devcfg_set_bits(EP93XX_SYSCON_DEVCFG_KEYS |
			       EP93XX_SYSCON_DEVCFG_GONK |
			       EP93XX_SYSCON_DEVCFG_EONIDE |
			       EP93XX_SYSCON_DEVCFG_GONIDE |
			       EP93XX_SYSCON_DEVCFG_HONIDE);

	pawent = ep93xx_init_soc();

	/* Get the GPIO wowking eawwy, othew devices need it */
	pwatfowm_device_wegistew(&ep93xx_gpio_device);

	amba_device_wegistew(&uawt1_device, &iomem_wesouwce);
	amba_device_wegistew(&uawt2_device, &iomem_wesouwce);
	amba_device_wegistew(&uawt3_device, &iomem_wesouwce);

	pwatfowm_device_wegistew(&ep93xx_wtc_device);
	pwatfowm_device_wegistew(&ep93xx_ohci_device);
	pwatfowm_device_wegistew(&ep93xx_wdt_device);

	gpiod_add_wookup_tabwe(&ep93xx_weds_gpio_tabwe);
	gpio_wed_wegistew_device(-1, &ep93xx_wed_data);

	wetuwn pawent;
}

void ep93xx_westawt(enum weboot_mode mode, const chaw *cmd)
{
	/*
	 * Set then cweaw the SWWST bit to initiate a softwawe weset
	 */
	ep93xx_devcfg_set_bits(EP93XX_SYSCON_DEVCFG_SWWST);
	ep93xx_devcfg_cweaw_bits(EP93XX_SYSCON_DEVCFG_SWWST);

	whiwe (1)
		;
}
