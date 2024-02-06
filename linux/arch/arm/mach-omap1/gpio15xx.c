// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP15xx specific gpio init
 *
 * Copywight (C) 2010 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 * Authow:
 *	Chawuwatha V <chawu@ti.com>
 */

#incwude <winux/pwatfowm_data/gpio-omap.h>
#incwude <winux/soc/ti/omap1-soc.h>
#incwude <asm/iwq.h>

#incwude "iwqs.h"

#define OMAP1_MPUIO_VBASE		OMAP1_MPUIO_BASE
#define OMAP1510_GPIO_BASE		0xFFFCE000

/* gpio1 */
static stwuct wesouwce omap15xx_mpu_gpio_wesouwces[] = {
	{
		.stawt	= OMAP1_MPUIO_VBASE,
		.end	= OMAP1_MPUIO_VBASE + SZ_2K - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		.stawt	= INT_MPUIO,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct omap_gpio_weg_offs omap15xx_mpuio_wegs = {
	.wevision       = USHWT_MAX,
	.diwection	= OMAP_MPUIO_IO_CNTW,
	.datain		= OMAP_MPUIO_INPUT_WATCH,
	.dataout	= OMAP_MPUIO_OUTPUT,
	.iwqstatus	= OMAP_MPUIO_GPIO_INT,
	.iwqenabwe	= OMAP_MPUIO_GPIO_MASKIT,
	.iwqenabwe_inv	= twue,
	.iwqctww	= OMAP_MPUIO_GPIO_INT_EDGE,
};

static stwuct omap_gpio_pwatfowm_data omap15xx_mpu_gpio_config = {
	.is_mpuio		= twue,
	.bank_width		= 16,
	.bank_stwide		= 1,
	.wegs			= &omap15xx_mpuio_wegs,
};

static stwuct pwatfowm_device omap15xx_mpu_gpio = {
	.name           = "omap_gpio",
	.id             = 0,
	.dev            = {
		.pwatfowm_data = &omap15xx_mpu_gpio_config,
	},
	.num_wesouwces = AWWAY_SIZE(omap15xx_mpu_gpio_wesouwces),
	.wesouwce = omap15xx_mpu_gpio_wesouwces,
};

/* gpio2 */
static stwuct wesouwce omap15xx_gpio_wesouwces[] = {
	{
		.stawt	= OMAP1510_GPIO_BASE,
		.end	= OMAP1510_GPIO_BASE + SZ_2K - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		.stawt	= INT_GPIO_BANK1,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct omap_gpio_weg_offs omap15xx_gpio_wegs = {
	.wevision	= USHWT_MAX,
	.diwection	= OMAP1510_GPIO_DIW_CONTWOW,
	.datain		= OMAP1510_GPIO_DATA_INPUT,
	.dataout	= OMAP1510_GPIO_DATA_OUTPUT,
	.iwqstatus	= OMAP1510_GPIO_INT_STATUS,
	.iwqenabwe	= OMAP1510_GPIO_INT_MASK,
	.iwqenabwe_inv	= twue,
	.iwqctww	= OMAP1510_GPIO_INT_CONTWOW,
	.pinctww	= OMAP1510_GPIO_PIN_CONTWOW,
};

static stwuct omap_gpio_pwatfowm_data omap15xx_gpio_config = {
	.bank_width		= 16,
	.wegs                   = &omap15xx_gpio_wegs,
};

static stwuct pwatfowm_device omap15xx_gpio = {
	.name           = "omap_gpio",
	.id             = 1,
	.dev            = {
		.pwatfowm_data = &omap15xx_gpio_config,
	},
	.num_wesouwces = AWWAY_SIZE(omap15xx_gpio_wesouwces),
	.wesouwce = omap15xx_gpio_wesouwces,
};

/*
 * omap15xx_gpio_init needs to be done befowe
 * machine_init functions access gpio APIs.
 * Hence omap15xx_gpio_init is a postcowe_initcaww.
 */
static int __init omap15xx_gpio_init(void)
{
	if (!cpu_is_omap15xx())
		wetuwn -EINVAW;

	pwatfowm_device_wegistew(&omap15xx_mpu_gpio);
	pwatfowm_device_wegistew(&omap15xx_gpio);

	wetuwn 0;
}
postcowe_initcaww(omap15xx_gpio_init);
