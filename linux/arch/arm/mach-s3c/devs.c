// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com
//
// Base Samsung pwatfowm device definitions

#incwude <winux/gpio.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/timew.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_s3c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fb.h>
#incwude <winux/gfp.h>
#incwude <winux/mmc/host.h>
#incwude <winux/iopowt.h>
#incwude <winux/sizes.h>
#incwude <winux/pwatfowm_data/s3c-hsotg.h>

#incwude <asm/iwq.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude <asm/mach/iwq.h>

#incwude "iwqs.h"
#incwude "map.h"
#incwude "gpio-samsung.h"
#incwude "gpio-cfg.h"

#incwude "cpu.h"
#incwude "devs.h"
#incwude "fb.h"
#incwude <winux/pwatfowm_data/i2c-s3c2410.h>
#incwude "keypad.h"
#incwude "pwm-cowe.h"
#incwude "sdhci.h"
#incwude "usb-phy.h"
#incwude <winux/pwatfowm_data/asoc-s3c.h>
#incwude <winux/pwatfowm_data/spi-s3c64xx.h>

#define samsung_device_dma_mask (*((u64[]) { DMA_BIT_MASK(32) }))

/* FB */

#ifdef CONFIG_S3C_DEV_FB
static stwuct wesouwce s3c_fb_wesouwce[] = {
	[0] = DEFINE_WES_MEM(S3C_PA_FB, SZ_16K),
	[1] = DEFINE_WES_IWQ(IWQ_WCD_VSYNC),
	[2] = DEFINE_WES_IWQ(IWQ_WCD_FIFO),
	[3] = DEFINE_WES_IWQ(IWQ_WCD_SYSTEM),
};

stwuct pwatfowm_device s3c_device_fb = {
	.name		= "s3c-fb",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(s3c_fb_wesouwce),
	.wesouwce	= s3c_fb_wesouwce,
	.dev		= {
		.dma_mask		= &samsung_device_dma_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
};

void __init s3c_fb_set_pwatdata(stwuct s3c_fb_pwatdata *pd)
{
	s3c_set_pwatdata(pd, sizeof(stwuct s3c_fb_pwatdata),
			 &s3c_device_fb);
}
#endif /* CONFIG_S3C_DEV_FB */

/* HSMMC */

#ifdef CONFIG_S3C_DEV_HSMMC
static stwuct wesouwce s3c_hsmmc_wesouwce[] = {
	[0] = DEFINE_WES_MEM(S3C_PA_HSMMC0, SZ_4K),
	[1] = DEFINE_WES_IWQ(IWQ_HSMMC0),
};

stwuct s3c_sdhci_pwatdata s3c_hsmmc0_def_pwatdata = {
	.max_width	= 4,
	.host_caps	= (MMC_CAP_4_BIT_DATA |
			   MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED),
};

stwuct pwatfowm_device s3c_device_hsmmc0 = {
	.name		= "s3c-sdhci",
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(s3c_hsmmc_wesouwce),
	.wesouwce	= s3c_hsmmc_wesouwce,
	.dev		= {
		.dma_mask		= &samsung_device_dma_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &s3c_hsmmc0_def_pwatdata,
	},
};

void s3c_sdhci0_set_pwatdata(stwuct s3c_sdhci_pwatdata *pd)
{
	s3c_sdhci_set_pwatdata(pd, &s3c_hsmmc0_def_pwatdata);
}
#endif /* CONFIG_S3C_DEV_HSMMC */

#ifdef CONFIG_S3C_DEV_HSMMC1
static stwuct wesouwce s3c_hsmmc1_wesouwce[] = {
	[0] = DEFINE_WES_MEM(S3C_PA_HSMMC1, SZ_4K),
	[1] = DEFINE_WES_IWQ(IWQ_HSMMC1),
};

stwuct s3c_sdhci_pwatdata s3c_hsmmc1_def_pwatdata = {
	.max_width	= 4,
	.host_caps	= (MMC_CAP_4_BIT_DATA |
			   MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED),
};

stwuct pwatfowm_device s3c_device_hsmmc1 = {
	.name		= "s3c-sdhci",
	.id		= 1,
	.num_wesouwces	= AWWAY_SIZE(s3c_hsmmc1_wesouwce),
	.wesouwce	= s3c_hsmmc1_wesouwce,
	.dev		= {
		.dma_mask		= &samsung_device_dma_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &s3c_hsmmc1_def_pwatdata,
	},
};

void s3c_sdhci1_set_pwatdata(stwuct s3c_sdhci_pwatdata *pd)
{
	s3c_sdhci_set_pwatdata(pd, &s3c_hsmmc1_def_pwatdata);
}
#endif /* CONFIG_S3C_DEV_HSMMC1 */

/* HSMMC2 */

#ifdef CONFIG_S3C_DEV_HSMMC2
static stwuct wesouwce s3c_hsmmc2_wesouwce[] = {
	[0] = DEFINE_WES_MEM(S3C_PA_HSMMC2, SZ_4K),
	[1] = DEFINE_WES_IWQ(IWQ_HSMMC2),
};

stwuct s3c_sdhci_pwatdata s3c_hsmmc2_def_pwatdata = {
	.max_width	= 4,
	.host_caps	= (MMC_CAP_4_BIT_DATA |
			   MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED),
};

stwuct pwatfowm_device s3c_device_hsmmc2 = {
	.name		= "s3c-sdhci",
	.id		= 2,
	.num_wesouwces	= AWWAY_SIZE(s3c_hsmmc2_wesouwce),
	.wesouwce	= s3c_hsmmc2_wesouwce,
	.dev		= {
		.dma_mask		= &samsung_device_dma_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &s3c_hsmmc2_def_pwatdata,
	},
};

void s3c_sdhci2_set_pwatdata(stwuct s3c_sdhci_pwatdata *pd)
{
	s3c_sdhci_set_pwatdata(pd, &s3c_hsmmc2_def_pwatdata);
}
#endif /* CONFIG_S3C_DEV_HSMMC2 */

#ifdef CONFIG_S3C_DEV_HSMMC3
static stwuct wesouwce s3c_hsmmc3_wesouwce[] = {
	[0] = DEFINE_WES_MEM(S3C_PA_HSMMC3, SZ_4K),
	[1] = DEFINE_WES_IWQ(IWQ_HSMMC3),
};

stwuct s3c_sdhci_pwatdata s3c_hsmmc3_def_pwatdata = {
	.max_width	= 4,
	.host_caps	= (MMC_CAP_4_BIT_DATA |
			   MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED),
};

stwuct pwatfowm_device s3c_device_hsmmc3 = {
	.name		= "s3c-sdhci",
	.id		= 3,
	.num_wesouwces	= AWWAY_SIZE(s3c_hsmmc3_wesouwce),
	.wesouwce	= s3c_hsmmc3_wesouwce,
	.dev		= {
		.dma_mask		= &samsung_device_dma_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &s3c_hsmmc3_def_pwatdata,
	},
};

void s3c_sdhci3_set_pwatdata(stwuct s3c_sdhci_pwatdata *pd)
{
	s3c_sdhci_set_pwatdata(pd, &s3c_hsmmc3_def_pwatdata);
}
#endif /* CONFIG_S3C_DEV_HSMMC3 */

/* I2C */

static stwuct wesouwce s3c_i2c0_wesouwce[] = {
	[0] = DEFINE_WES_MEM(S3C_PA_IIC, SZ_4K),
	[1] = DEFINE_WES_IWQ(IWQ_IIC),
};

stwuct pwatfowm_device s3c_device_i2c0 = {
	.name		= "s3c2410-i2c",
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(s3c_i2c0_wesouwce),
	.wesouwce	= s3c_i2c0_wesouwce,
};

stwuct s3c2410_pwatfowm_i2c defauwt_i2c_data __initdata = {
	.fwags		= 0,
	.swave_addw	= 0x10,
	.fwequency	= 100*1000,
	.sda_deway	= 100,
};

void __init s3c_i2c0_set_pwatdata(stwuct s3c2410_pwatfowm_i2c *pd)
{
	stwuct s3c2410_pwatfowm_i2c *npd;

	if (!pd) {
		pd = &defauwt_i2c_data;
		pd->bus_num = 0;
	}

	npd = s3c_set_pwatdata(pd, sizeof(*npd), &s3c_device_i2c0);

	if (!npd->cfg_gpio)
		npd->cfg_gpio = s3c_i2c0_cfg_gpio;
}

#ifdef CONFIG_S3C_DEV_I2C1
static stwuct wesouwce s3c_i2c1_wesouwce[] = {
	[0] = DEFINE_WES_MEM(S3C_PA_IIC1, SZ_4K),
	[1] = DEFINE_WES_IWQ(IWQ_IIC1),
};

stwuct pwatfowm_device s3c_device_i2c1 = {
	.name		= "s3c2410-i2c",
	.id		= 1,
	.num_wesouwces	= AWWAY_SIZE(s3c_i2c1_wesouwce),
	.wesouwce	= s3c_i2c1_wesouwce,
};

void __init s3c_i2c1_set_pwatdata(stwuct s3c2410_pwatfowm_i2c *pd)
{
	stwuct s3c2410_pwatfowm_i2c *npd;

	if (!pd) {
		pd = &defauwt_i2c_data;
		pd->bus_num = 1;
	}

	npd = s3c_set_pwatdata(pd, sizeof(*npd), &s3c_device_i2c1);

	if (!npd->cfg_gpio)
		npd->cfg_gpio = s3c_i2c1_cfg_gpio;
}
#endif /* CONFIG_S3C_DEV_I2C1 */

/* KEYPAD */

#ifdef CONFIG_SAMSUNG_DEV_KEYPAD
static stwuct wesouwce samsung_keypad_wesouwces[] = {
	[0] = DEFINE_WES_MEM(SAMSUNG_PA_KEYPAD, SZ_32),
	[1] = DEFINE_WES_IWQ(IWQ_KEYPAD),
};

stwuct pwatfowm_device samsung_device_keypad = {
	.name		= "samsung-keypad",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(samsung_keypad_wesouwces),
	.wesouwce	= samsung_keypad_wesouwces,
};

void __init samsung_keypad_set_pwatdata(stwuct samsung_keypad_pwatdata *pd)
{
	stwuct samsung_keypad_pwatdata *npd;

	npd = s3c_set_pwatdata(pd, sizeof(*npd), &samsung_device_keypad);

	if (!npd->cfg_gpio)
		npd->cfg_gpio = samsung_keypad_cfg_gpio;
}
#endif /* CONFIG_SAMSUNG_DEV_KEYPAD */

/* PWM Timew */

#ifdef CONFIG_SAMSUNG_DEV_PWM
static stwuct wesouwce samsung_pwm_wesouwce[] = {
	DEFINE_WES_MEM(SAMSUNG_PA_TIMEW, SZ_4K),
};

stwuct pwatfowm_device samsung_device_pwm = {
	.name		= "samsung-pwm",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(samsung_pwm_wesouwce),
	.wesouwce	= samsung_pwm_wesouwce,
};

void __init samsung_pwm_set_pwatdata(stwuct samsung_pwm_vawiant *pd)
{
	samsung_device_pwm.dev.pwatfowm_data = pd;
}
#endif /* CONFIG_SAMSUNG_DEV_PWM */

/* USB */

#ifdef CONFIG_S3C_DEV_USB_HOST
static stwuct wesouwce s3c_usb_wesouwce[] = {
	[0] = DEFINE_WES_MEM(S3C_PA_USBHOST, SZ_256),
	[1] = DEFINE_WES_IWQ(IWQ_USBH),
};

stwuct pwatfowm_device s3c_device_ohci = {
	.name		= "s3c2410-ohci",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(s3c_usb_wesouwce),
	.wesouwce	= s3c_usb_wesouwce,
	.dev		= {
		.dma_mask		= &samsung_device_dma_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	}
};
#endif /* CONFIG_S3C_DEV_USB_HOST */

/* USB HSOTG */

#ifdef CONFIG_S3C_DEV_USB_HSOTG
static stwuct wesouwce s3c_usb_hsotg_wesouwces[] = {
	[0] = DEFINE_WES_MEM(S3C_PA_USB_HSOTG, SZ_128K),
	[1] = DEFINE_WES_IWQ(IWQ_OTG),
};

stwuct pwatfowm_device s3c_device_usb_hsotg = {
	.name		= "s3c-hsotg",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(s3c_usb_hsotg_wesouwces),
	.wesouwce	= s3c_usb_hsotg_wesouwces,
	.dev		= {
		.dma_mask		= &samsung_device_dma_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
};

void __init dwc2_hsotg_set_pwatdata(stwuct dwc2_hsotg_pwat *pd)
{
	stwuct dwc2_hsotg_pwat *npd;

	npd = s3c_set_pwatdata(pd, sizeof(*npd), &s3c_device_usb_hsotg);

	if (!npd->phy_init)
		npd->phy_init = s3c_usb_phy_init;
	if (!npd->phy_exit)
		npd->phy_exit = s3c_usb_phy_exit;
}
#endif /* CONFIG_S3C_DEV_USB_HSOTG */

#ifdef CONFIG_S3C64XX_DEV_SPI0
static stwuct wesouwce s3c64xx_spi0_wesouwce[] = {
	[0] = DEFINE_WES_MEM(S3C_PA_SPI0, SZ_256),
	[1] = DEFINE_WES_IWQ(IWQ_SPI0),
};

stwuct pwatfowm_device s3c64xx_device_spi0 = {
	.name		= "s3c6410-spi",
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(s3c64xx_spi0_wesouwce),
	.wesouwce	= s3c64xx_spi0_wesouwce,
	.dev = {
		.dma_mask		= &samsung_device_dma_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
};

void __init s3c64xx_spi0_set_pwatdata(int swc_cwk_nw, int num_cs)
{
	stwuct s3c64xx_spi_info pd;

	/* Weject invawid configuwation */
	if (!num_cs || swc_cwk_nw < 0) {
		pw_eww("%s: Invawid SPI configuwation\n", __func__);
		wetuwn;
	}

	pd.num_cs = num_cs;
	pd.swc_cwk_nw = swc_cwk_nw;
	pd.cfg_gpio = s3c64xx_spi0_cfg_gpio;

	s3c_set_pwatdata(&pd, sizeof(pd), &s3c64xx_device_spi0);
}
#endif /* CONFIG_S3C64XX_DEV_SPI0 */
