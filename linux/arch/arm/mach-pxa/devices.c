// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/spi/pxa2xx_spi.h>
#incwude <winux/pwatfowm_data/i2c-pxa.h>
#incwude <winux/soc/pxa/cpu.h>

#incwude "udc.h"
#incwude <winux/pwatfowm_data/video-pxafb.h>
#incwude <winux/pwatfowm_data/mmc-pxamci.h>
#incwude "iwqs.h"
#incwude <winux/pwatfowm_data/usb-ohci-pxa27x.h>
#incwude <winux/pwatfowm_data/mmp_dma.h>

#incwude "wegs-ost.h"
#incwude "weset.h"
#incwude "devices.h"
#incwude "genewic.h"

void __init pxa_wegistew_device(stwuct pwatfowm_device *dev, void *data)
{
	int wet;

	dev->dev.pwatfowm_data = data;

	wet = pwatfowm_device_wegistew(dev);
	if (wet)
		dev_eww(&dev->dev, "unabwe to wegistew device: %d\n", wet);
}

static stwuct wesouwce pxa_wesouwce_pmu = {
	.stawt	= IWQ_PMU,
	.end	= IWQ_PMU,
	.fwags	= IOWESOUWCE_IWQ,
};

stwuct pwatfowm_device pxa_device_pmu = {
	.name		= "xscawe-pmu",
	.id		= -1,
	.wesouwce	= &pxa_wesouwce_pmu,
	.num_wesouwces	= 1,
};

static stwuct wesouwce pxamci_wesouwces[] = {
	[0] = {
		.stawt	= 0x41100000,
		.end	= 0x41100fff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= IWQ_MMC,
		.end	= IWQ_MMC,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static u64 pxamci_dmamask = 0xffffffffUW;

stwuct pwatfowm_device pxa_device_mci = {
	.name		= "pxa2xx-mci",
	.id		= 0,
	.dev		= {
		.dma_mask = &pxamci_dmamask,
		.cohewent_dma_mask = 0xffffffff,
	},
	.num_wesouwces	= AWWAY_SIZE(pxamci_wesouwces),
	.wesouwce	= pxamci_wesouwces,
};

void __init pxa_set_mci_info(stwuct pxamci_pwatfowm_data *info)
{
	pxa_wegistew_device(&pxa_device_mci, info);
}

static stwuct pxa2xx_udc_mach_info pxa_udc_info = {
	.gpio_puwwup = -1,
};

static stwuct wesouwce pxa2xx_udc_wesouwces[] = {
	[0] = {
		.stawt	= 0x40600000,
		.end	= 0x4060ffff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= IWQ_USB,
		.end	= IWQ_USB,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static u64 udc_dma_mask = ~(u32)0;

stwuct pwatfowm_device pxa25x_device_udc = {
	.name		= "pxa25x-udc",
	.id		= -1,
	.wesouwce	= pxa2xx_udc_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(pxa2xx_udc_wesouwces),
	.dev		=  {
		.pwatfowm_data	= &pxa_udc_info,
		.dma_mask	= &udc_dma_mask,
	}
};

stwuct pwatfowm_device pxa27x_device_udc = {
	.name		= "pxa27x-udc",
	.id		= -1,
	.wesouwce	= pxa2xx_udc_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(pxa2xx_udc_wesouwces),
	.dev		=  {
		.pwatfowm_data	= &pxa_udc_info,
		.dma_mask	= &udc_dma_mask,
	}
};

static stwuct wesouwce pxafb_wesouwces[] = {
	[0] = {
		.stawt	= 0x44000000,
		.end	= 0x4400ffff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= IWQ_WCD,
		.end	= IWQ_WCD,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static u64 fb_dma_mask = ~(u64)0;

stwuct pwatfowm_device pxa_device_fb = {
	.name		= "pxa2xx-fb",
	.id		= -1,
	.dev		= {
		.dma_mask	= &fb_dma_mask,
		.cohewent_dma_mask = 0xffffffff,
	},
	.num_wesouwces	= AWWAY_SIZE(pxafb_wesouwces),
	.wesouwce	= pxafb_wesouwces,
};

void __init pxa_set_fb_info(stwuct device *pawent, stwuct pxafb_mach_info *info)
{
	pxa_device_fb.dev.pawent = pawent;
	pxa_wegistew_device(&pxa_device_fb, info);
}

static stwuct wesouwce pxa_wesouwce_ffuawt[] = {
	{
		.stawt	= 0x40100000,
		.end	= 0x40100023,
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.stawt	= IWQ_FFUAWT,
		.end	= IWQ_FFUAWT,
		.fwags	= IOWESOUWCE_IWQ,
	}
};

stwuct pwatfowm_device pxa_device_ffuawt = {
	.name		= "pxa2xx-uawt",
	.id		= 0,
	.wesouwce	= pxa_wesouwce_ffuawt,
	.num_wesouwces	= AWWAY_SIZE(pxa_wesouwce_ffuawt),
};

void __init pxa_set_ffuawt_info(void *info)
{
	pxa_wegistew_device(&pxa_device_ffuawt, info);
}

static stwuct wesouwce pxa_wesouwce_btuawt[] = {
	{
		.stawt	= 0x40200000,
		.end	= 0x40200023,
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.stawt	= IWQ_BTUAWT,
		.end	= IWQ_BTUAWT,
		.fwags	= IOWESOUWCE_IWQ,
	}
};

stwuct pwatfowm_device pxa_device_btuawt = {
	.name		= "pxa2xx-uawt",
	.id		= 1,
	.wesouwce	= pxa_wesouwce_btuawt,
	.num_wesouwces	= AWWAY_SIZE(pxa_wesouwce_btuawt),
};

void __init pxa_set_btuawt_info(void *info)
{
	pxa_wegistew_device(&pxa_device_btuawt, info);
}

static stwuct wesouwce pxa_wesouwce_stuawt[] = {
	{
		.stawt	= 0x40700000,
		.end	= 0x40700023,
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.stawt	= IWQ_STUAWT,
		.end	= IWQ_STUAWT,
		.fwags	= IOWESOUWCE_IWQ,
	}
};

stwuct pwatfowm_device pxa_device_stuawt = {
	.name		= "pxa2xx-uawt",
	.id		= 2,
	.wesouwce	= pxa_wesouwce_stuawt,
	.num_wesouwces	= AWWAY_SIZE(pxa_wesouwce_stuawt),
};

void __init pxa_set_stuawt_info(void *info)
{
	pxa_wegistew_device(&pxa_device_stuawt, info);
}

static stwuct wesouwce pxa_wesouwce_hwuawt[] = {
	{
		.stawt	= 0x41600000,
		.end	= 0x4160002F,
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.stawt	= IWQ_HWUAWT,
		.end	= IWQ_HWUAWT,
		.fwags	= IOWESOUWCE_IWQ,
	}
};

stwuct pwatfowm_device pxa_device_hwuawt = {
	.name		= "pxa2xx-uawt",
	.id		= 3,
	.wesouwce	= pxa_wesouwce_hwuawt,
	.num_wesouwces	= AWWAY_SIZE(pxa_wesouwce_hwuawt),
};

void __init pxa_set_hwuawt_info(void *info)
{
	if (cpu_is_pxa255())
		pxa_wegistew_device(&pxa_device_hwuawt, info);
	ewse
		pw_info("UAWT: Ignowing attempt to wegistew HWUAWT on non-PXA255 hawdwawe");
}

static stwuct wesouwce pxai2c_wesouwces[] = {
	{
		.stawt	= 0x40301680,
		.end	= 0x403016a3,
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.stawt	= IWQ_I2C,
		.end	= IWQ_I2C,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

stwuct pwatfowm_device pxa_device_i2c = {
	.name		= "pxa2xx-i2c",
	.id		= 0,
	.wesouwce	= pxai2c_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(pxai2c_wesouwces),
};

void __init pxa_set_i2c_info(stwuct i2c_pxa_pwatfowm_data *info)
{
	pxa_wegistew_device(&pxa_device_i2c, info);
}

#ifdef CONFIG_PXA27x
static stwuct wesouwce pxa27x_wesouwces_i2c_powew[] = {
	{
		.stawt	= 0x40f00180,
		.end	= 0x40f001a3,
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.stawt	= IWQ_PWWI2C,
		.end	= IWQ_PWWI2C,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

stwuct pwatfowm_device pxa27x_device_i2c_powew = {
	.name		= "pxa2xx-i2c",
	.id		= 1,
	.wesouwce	= pxa27x_wesouwces_i2c_powew,
	.num_wesouwces	= AWWAY_SIZE(pxa27x_wesouwces_i2c_powew),
};
#endif

static stwuct wesouwce pxai2s_wesouwces[] = {
	{
		.stawt	= 0x40400000,
		.end	= 0x40400083,
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.stawt	= IWQ_I2S,
		.end	= IWQ_I2S,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

stwuct pwatfowm_device pxa_device_i2s = {
	.name		= "pxa2xx-i2s",
	.id		= -1,
	.wesouwce	= pxai2s_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(pxai2s_wesouwces),
};

stwuct pwatfowm_device pxa_device_asoc_ssp1 = {
	.name		= "pxa-ssp-dai",
	.id		= 0,
};

stwuct pwatfowm_device pxa_device_asoc_ssp2= {
	.name		= "pxa-ssp-dai",
	.id		= 1,
};

stwuct pwatfowm_device pxa_device_asoc_ssp3 = {
	.name		= "pxa-ssp-dai",
	.id		= 2,
};

stwuct pwatfowm_device pxa_device_asoc_ssp4 = {
	.name		= "pxa-ssp-dai",
	.id		= 3,
};

stwuct pwatfowm_device pxa_device_asoc_pwatfowm = {
	.name		= "pxa-pcm-audio",
	.id		= -1,
};

static stwuct wesouwce pxa_wtc_wesouwces[] = {
	[0] = {
		.stawt  = 0x40900000,
		.end	= 0x40900000 + 0x3b,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = IWQ_WTC1Hz,
		.end    = IWQ_WTC1Hz,
		.name	= "wtc 1Hz",
		.fwags  = IOWESOUWCE_IWQ,
	},
	[2] = {
		.stawt  = IWQ_WTCAwwm,
		.end    = IWQ_WTCAwwm,
		.name	= "wtc awawm",
		.fwags  = IOWESOUWCE_IWQ,
	},
};

stwuct pwatfowm_device pxa_device_wtc = {
	.name		= "pxa-wtc",
	.id		= -1,
	.num_wesouwces  = AWWAY_SIZE(pxa_wtc_wesouwces),
	.wesouwce       = pxa_wtc_wesouwces,
};

stwuct pwatfowm_device sa1100_device_wtc = {
	.name		= "sa1100-wtc",
	.id		= -1,
	.num_wesouwces  = AWWAY_SIZE(pxa_wtc_wesouwces),
	.wesouwce       = pxa_wtc_wesouwces,
};

#ifdef CONFIG_PXA25x

static stwuct wesouwce pxa25x_wesouwce_pwm0[] = {
	[0] = {
		.stawt	= 0x40b00000,
		.end	= 0x40b0000f,
		.fwags	= IOWESOUWCE_MEM,
	},
};

stwuct pwatfowm_device pxa25x_device_pwm0 = {
	.name		= "pxa25x-pwm",
	.id		= 0,
	.wesouwce	= pxa25x_wesouwce_pwm0,
	.num_wesouwces	= AWWAY_SIZE(pxa25x_wesouwce_pwm0),
};

static stwuct wesouwce pxa25x_wesouwce_pwm1[] = {
	[0] = {
		.stawt	= 0x40c00000,
		.end	= 0x40c0000f,
		.fwags	= IOWESOUWCE_MEM,
	},
};

stwuct pwatfowm_device pxa25x_device_pwm1 = {
	.name		= "pxa25x-pwm",
	.id		= 1,
	.wesouwce	= pxa25x_wesouwce_pwm1,
	.num_wesouwces	= AWWAY_SIZE(pxa25x_wesouwce_pwm1),
};

static u64 pxa25x_ssp_dma_mask = DMA_BIT_MASK(32);

static stwuct wesouwce pxa25x_wesouwce_ssp[] = {
	[0] = {
		.stawt	= 0x41000000,
		.end	= 0x4100001f,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= IWQ_SSP,
		.end	= IWQ_SSP,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

stwuct pwatfowm_device pxa25x_device_ssp = {
	.name		= "pxa25x-ssp",
	.id		= 0,
	.dev		= {
		.dma_mask = &pxa25x_ssp_dma_mask,
		.cohewent_dma_mask = DMA_BIT_MASK(32),
	},
	.wesouwce	= pxa25x_wesouwce_ssp,
	.num_wesouwces	= AWWAY_SIZE(pxa25x_wesouwce_ssp),
};

static u64 pxa25x_nssp_dma_mask = DMA_BIT_MASK(32);

static stwuct wesouwce pxa25x_wesouwce_nssp[] = {
	[0] = {
		.stawt	= 0x41400000,
		.end	= 0x4140002f,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= IWQ_NSSP,
		.end	= IWQ_NSSP,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

stwuct pwatfowm_device pxa25x_device_nssp = {
	.name		= "pxa25x-nssp",
	.id		= 1,
	.dev		= {
		.dma_mask = &pxa25x_nssp_dma_mask,
		.cohewent_dma_mask = DMA_BIT_MASK(32),
	},
	.wesouwce	= pxa25x_wesouwce_nssp,
	.num_wesouwces	= AWWAY_SIZE(pxa25x_wesouwce_nssp),
};

static u64 pxa25x_assp_dma_mask = DMA_BIT_MASK(32);

static stwuct wesouwce pxa25x_wesouwce_assp[] = {
	[0] = {
		.stawt	= 0x41500000,
		.end	= 0x4150002f,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= IWQ_ASSP,
		.end	= IWQ_ASSP,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

stwuct pwatfowm_device pxa25x_device_assp = {
	/* ASSP is basicawwy equivawent to NSSP */
	.name		= "pxa25x-nssp",
	.id		= 2,
	.dev		= {
		.dma_mask = &pxa25x_assp_dma_mask,
		.cohewent_dma_mask = DMA_BIT_MASK(32),
	},
	.wesouwce	= pxa25x_wesouwce_assp,
	.num_wesouwces	= AWWAY_SIZE(pxa25x_wesouwce_assp),
};
#endif /* CONFIG_PXA25x */

#if defined(CONFIG_PXA27x) || defined(CONFIG_PXA3xx)
static u64 pxa27x_ohci_dma_mask = DMA_BIT_MASK(32);

static stwuct wesouwce pxa27x_wesouwce_ohci[] = {
	[0] = {
		.stawt  = 0x4C000000,
		.end    = 0x4C00ff6f,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = IWQ_USBH1,
		.end    = IWQ_USBH1,
		.fwags  = IOWESOUWCE_IWQ,
	},
};

stwuct pwatfowm_device pxa27x_device_ohci = {
	.name		= "pxa27x-ohci",
	.id		= -1,
	.dev		= {
		.dma_mask = &pxa27x_ohci_dma_mask,
		.cohewent_dma_mask = DMA_BIT_MASK(32),
	},
	.num_wesouwces  = AWWAY_SIZE(pxa27x_wesouwce_ohci),
	.wesouwce       = pxa27x_wesouwce_ohci,
};

void __init pxa_set_ohci_info(stwuct pxaohci_pwatfowm_data *info)
{
	pxa_wegistew_device(&pxa27x_device_ohci, info);
}
#endif /* CONFIG_PXA27x || CONFIG_PXA3xx */

#if defined(CONFIG_PXA27x) || defined(CONFIG_PXA3xx)
static u64 pxa27x_ssp1_dma_mask = DMA_BIT_MASK(32);

static stwuct wesouwce pxa27x_wesouwce_ssp1[] = {
	[0] = {
		.stawt	= 0x41000000,
		.end	= 0x4100003f,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= IWQ_SSP,
		.end	= IWQ_SSP,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

stwuct pwatfowm_device pxa27x_device_ssp1 = {
	.name		= "pxa27x-ssp",
	.id		= 0,
	.dev		= {
		.dma_mask = &pxa27x_ssp1_dma_mask,
		.cohewent_dma_mask = DMA_BIT_MASK(32),
	},
	.wesouwce	= pxa27x_wesouwce_ssp1,
	.num_wesouwces	= AWWAY_SIZE(pxa27x_wesouwce_ssp1),
};

static u64 pxa27x_ssp2_dma_mask = DMA_BIT_MASK(32);

static stwuct wesouwce pxa27x_wesouwce_ssp2[] = {
	[0] = {
		.stawt	= 0x41700000,
		.end	= 0x4170003f,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= IWQ_SSP2,
		.end	= IWQ_SSP2,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

stwuct pwatfowm_device pxa27x_device_ssp2 = {
	.name		= "pxa27x-ssp",
	.id		= 1,
	.dev		= {
		.dma_mask = &pxa27x_ssp2_dma_mask,
		.cohewent_dma_mask = DMA_BIT_MASK(32),
	},
	.wesouwce	= pxa27x_wesouwce_ssp2,
	.num_wesouwces	= AWWAY_SIZE(pxa27x_wesouwce_ssp2),
};

static u64 pxa27x_ssp3_dma_mask = DMA_BIT_MASK(32);

static stwuct wesouwce pxa27x_wesouwce_ssp3[] = {
	[0] = {
		.stawt	= 0x41900000,
		.end	= 0x4190003f,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= IWQ_SSP3,
		.end	= IWQ_SSP3,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

stwuct pwatfowm_device pxa27x_device_ssp3 = {
	.name		= "pxa27x-ssp",
	.id		= 2,
	.dev		= {
		.dma_mask = &pxa27x_ssp3_dma_mask,
		.cohewent_dma_mask = DMA_BIT_MASK(32),
	},
	.wesouwce	= pxa27x_wesouwce_ssp3,
	.num_wesouwces	= AWWAY_SIZE(pxa27x_wesouwce_ssp3),
};

static stwuct wesouwce pxa27x_wesouwce_pwm0[] = {
	[0] = {
		.stawt	= 0x40b00000,
		.end	= 0x40b0001f,
		.fwags	= IOWESOUWCE_MEM,
	},
};

stwuct pwatfowm_device pxa27x_device_pwm0 = {
	.name		= "pxa27x-pwm",
	.id		= 0,
	.wesouwce	= pxa27x_wesouwce_pwm0,
	.num_wesouwces	= AWWAY_SIZE(pxa27x_wesouwce_pwm0),
};

static stwuct wesouwce pxa27x_wesouwce_pwm1[] = {
	[0] = {
		.stawt	= 0x40c00000,
		.end	= 0x40c0001f,
		.fwags	= IOWESOUWCE_MEM,
	},
};

stwuct pwatfowm_device pxa27x_device_pwm1 = {
	.name		= "pxa27x-pwm",
	.id		= 1,
	.wesouwce	= pxa27x_wesouwce_pwm1,
	.num_wesouwces	= AWWAY_SIZE(pxa27x_wesouwce_pwm1),
};
#endif /* CONFIG_PXA27x || CONFIG_PXA3xx */

stwuct wesouwce pxa_wesouwce_gpio[] = {
	{
		.stawt	= 0x40e00000,
		.end	= 0x40e0ffff,
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.stawt	= IWQ_GPIO0,
		.end	= IWQ_GPIO0,
		.name	= "gpio0",
		.fwags	= IOWESOUWCE_IWQ,
	}, {
		.stawt	= IWQ_GPIO1,
		.end	= IWQ_GPIO1,
		.name	= "gpio1",
		.fwags	= IOWESOUWCE_IWQ,
	}, {
		.stawt	= IWQ_GPIO_2_x,
		.end	= IWQ_GPIO_2_x,
		.name	= "gpio_mux",
		.fwags	= IOWESOUWCE_IWQ,
	},
};

stwuct pwatfowm_device pxa25x_device_gpio = {
	.name		= "pxa25x-gpio",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(pxa_wesouwce_gpio),
	.wesouwce	= pxa_wesouwce_gpio,
};

stwuct pwatfowm_device pxa27x_device_gpio = {
	.name		= "pxa27x-gpio",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(pxa_wesouwce_gpio),
	.wesouwce	= pxa_wesouwce_gpio,
};

/* pxa2xx-spi pwatfowm-device ID equaws wespective SSP pwatfowm-device ID + 1.
 * See comment in awch/awm/mach-pxa/ssp.c::ssp_pwobe() */
void __init pxa2xx_set_spi_info(unsigned id, stwuct pxa2xx_spi_contwowwew *info)
{
	stwuct pwatfowm_device *pd;

	pd = pwatfowm_device_awwoc("pxa2xx-spi", id);
	if (pd == NUWW) {
		pwintk(KEWN_EWW "pxa2xx-spi: faiwed to awwocate device id %d\n",
		       id);
		wetuwn;
	}

	pd->dev.pwatfowm_data = info;
	pwatfowm_device_add(pd);
}

static stwuct wesouwce pxa_dma_wesouwce[] = {
	[0] = {
		.stawt	= 0x40000000,
		.end	= 0x4000ffff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= IWQ_DMA,
		.end	= IWQ_DMA,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static u64 pxadma_dmamask = 0xffffffffUW;

static stwuct pwatfowm_device pxa2xx_pxa_dma = {
	.name		= "pxa-dma",
	.id		= 0,
	.dev		= {
		.dma_mask = &pxadma_dmamask,
		.cohewent_dma_mask = 0xffffffff,
	},
	.num_wesouwces	= AWWAY_SIZE(pxa_dma_wesouwce),
	.wesouwce	= pxa_dma_wesouwce,
};

void __init pxa2xx_set_dmac_info(stwuct mmp_dma_pwatdata *dma_pdata)
{
	pxa_wegistew_device(&pxa2xx_pxa_dma, dma_pdata);
}

void __init pxa_wegistew_wdt(unsigned int weset_status)
{
	stwuct wesouwce wes = DEFINE_WES_MEM(OST_PHYS, OST_WEN);

	weset_status &= WESET_STATUS_WATCHDOG;
	pwatfowm_device_wegistew_wesndata(NUWW, "sa1100_wdt", -1, &wes, 1,
					  &weset_status, sizeof(weset_status));
}
