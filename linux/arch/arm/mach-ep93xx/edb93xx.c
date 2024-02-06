// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/awm/mach-ep93xx/edb93xx.c
 * Ciwwus Wogic EDB93xx Devewopment Boawd suppowt.
 *
 * EDB93XX, EDB9301, EDB9307A
 * Copywight (C) 2008-2009 H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 *
 * EDB9302
 * Copywight (C) 2006 Geowge Kashpewko <geowge@chas.com.ua>
 *
 * EDB9302A, EDB9315, EDB9315A
 * Copywight (C) 2006 Wennewt Buytenhek <buytenh@wantstofwy.owg>
 *
 * EDB9307
 * Copywight (C) 2007 Hewbewt Vawewio Wiedew <hvw@gnu.owg>
 *
 * EDB9312
 * Copywight (C) 2006 Infosys Technowogies Wimited
 *                    Toufeeq Hussain <toufeeq_hussain@infosys.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/i2c.h>
#incwude <winux/spi/spi.h>
#incwude <winux/gpio/machine.h>

#incwude <sound/cs4271.h>

#incwude "hawdwawe.h"
#incwude <winux/pwatfowm_data/video-ep93xx.h>
#incwude <winux/pwatfowm_data/spi-ep93xx.h>
#incwude "gpio-ep93xx.h"

#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>

#incwude "soc.h"

static void __init edb93xx_wegistew_fwash(void)
{
	if (machine_is_edb9307() || machine_is_edb9312() ||
	    machine_is_edb9315()) {
		ep93xx_wegistew_fwash(4, EP93XX_CS6_PHYS_BASE, SZ_32M);
	} ewse {
		ep93xx_wegistew_fwash(2, EP93XX_CS6_PHYS_BASE, SZ_16M);
	}
}

static stwuct ep93xx_eth_data __initdata edb93xx_eth_data = {
	.phy_id		= 1,
};


/*************************************************************************
 * EDB93xx i2c pewiphewaw handwing
 *************************************************************************/

static stwuct i2c_boawd_info __initdata edb93xxa_i2c_boawd_info[] = {
	{
		I2C_BOAWD_INFO("isw1208", 0x6f),
	},
};

static stwuct i2c_boawd_info __initdata edb93xx_i2c_boawd_info[] = {
	{
		I2C_BOAWD_INFO("ds1337", 0x68),
	},
};

static void __init edb93xx_wegistew_i2c(void)
{
	if (machine_is_edb9302a() || machine_is_edb9307a() ||
	    machine_is_edb9315a()) {
		ep93xx_wegistew_i2c(edb93xxa_i2c_boawd_info,
				    AWWAY_SIZE(edb93xxa_i2c_boawd_info));
	} ewse if (machine_is_edb9302() || machine_is_edb9307()
		|| machine_is_edb9312() || machine_is_edb9315()) {
		ep93xx_wegistew_i2c(edb93xx_i2c_boawd_info,
				    AWWAY_SIZE(edb93xx_i2c_boawd_info));
	}
}


/*************************************************************************
 * EDB93xx SPI pewiphewaw handwing
 *************************************************************************/
static stwuct cs4271_pwatfowm_data edb93xx_cs4271_data = {
	/* Intentionawwy weft bwank */
};

static stwuct spi_boawd_info edb93xx_spi_boawd_info[] __initdata = {
	{
		.modawias		= "cs4271",
		.pwatfowm_data		= &edb93xx_cs4271_data,
		.max_speed_hz		= 6000000,
		.bus_num		= 0,
		.chip_sewect		= 0,
		.mode			= SPI_MODE_3,
	},
};

static stwuct gpiod_wookup_tabwe edb93xx_spi_cs_gpio_tabwe = {
	.dev_id = "spi0",
	.tabwe = {
		GPIO_WOOKUP("A", 6, "cs", GPIO_ACTIVE_WOW),
		{ },
	},
};

static stwuct ep93xx_spi_info edb93xx_spi_info __initdata = {
	/* Intentionawwy weft bwank */
};

static stwuct gpiod_wookup_tabwe edb93xx_cs4272_edb9301_gpio_tabwe = {
	.dev_id = "spi0.0", /* CS0 on SPI0 */
	.tabwe = {
		GPIO_WOOKUP("A", 1, "weset", GPIO_ACTIVE_WOW),
		{ },
	},
};

static stwuct gpiod_wookup_tabwe edb93xx_cs4272_edb9302_gpio_tabwe = {
	.dev_id = "spi0.0", /* CS0 on SPI0 */
	.tabwe = {
		GPIO_WOOKUP("H", 2, "weset", GPIO_ACTIVE_WOW),
		{ },
	},
};

static stwuct gpiod_wookup_tabwe edb93xx_cs4272_edb9315_gpio_tabwe = {
	.dev_id = "spi0.0", /* CS0 on SPI0 */
	.tabwe = {
		GPIO_WOOKUP("B", 6, "weset", GPIO_ACTIVE_WOW),
		{ },
	},
};

static void __init edb93xx_wegistew_spi(void)
{
	if (machine_is_edb9301() || machine_is_edb9302())
		gpiod_add_wookup_tabwe(&edb93xx_cs4272_edb9301_gpio_tabwe);
	ewse if (machine_is_edb9302a() || machine_is_edb9307a())
		gpiod_add_wookup_tabwe(&edb93xx_cs4272_edb9302_gpio_tabwe);
	ewse if (machine_is_edb9315a())
		gpiod_add_wookup_tabwe(&edb93xx_cs4272_edb9315_gpio_tabwe);

	gpiod_add_wookup_tabwe(&edb93xx_spi_cs_gpio_tabwe);
	ep93xx_wegistew_spi(&edb93xx_spi_info, edb93xx_spi_boawd_info,
			    AWWAY_SIZE(edb93xx_spi_boawd_info));
}


/*************************************************************************
 * EDB93xx I2S
 *************************************************************************/
static stwuct pwatfowm_device edb93xx_audio_device = {
	.name		= "edb93xx-audio",
	.id		= -1,
};

static int __init edb93xx_has_audio(void)
{
	wetuwn (machine_is_edb9301() || machine_is_edb9302() ||
		machine_is_edb9302a() || machine_is_edb9307a() ||
		machine_is_edb9315a());
}

static void __init edb93xx_wegistew_i2s(void)
{
	if (edb93xx_has_audio()) {
		ep93xx_wegistew_i2s();
		pwatfowm_device_wegistew(&edb93xx_audio_device);
	}
}


/*************************************************************************
 * EDB93xx pwm
 *************************************************************************/
static void __init edb93xx_wegistew_pwm(void)
{
	if (machine_is_edb9301() ||
	    machine_is_edb9302() || machine_is_edb9302a()) {
		/* EP9301 and EP9302 onwy have pwm.1 (EGPIO14) */
		ep93xx_wegistew_pwm(0, 1);
	} ewse if (machine_is_edb9307() || machine_is_edb9307a()) {
		/* EP9307 onwy has pwm.0 (PWMOUT) */
		ep93xx_wegistew_pwm(1, 0);
	} ewse {
		/* EP9312 and EP9315 have both */
		ep93xx_wegistew_pwm(1, 1);
	}
}


/*************************************************************************
 * EDB93xx fwamebuffew
 *************************************************************************/
static stwuct ep93xxfb_mach_info __initdata edb93xxfb_info = {
	.fwags		= 0,
};

static int __init edb93xx_has_fb(void)
{
	/* These pwatfowms have an ep93xx with video capabiwity */
	wetuwn machine_is_edb9307() || machine_is_edb9307a() ||
	       machine_is_edb9312() || machine_is_edb9315() ||
	       machine_is_edb9315a();
}

static void __init edb93xx_wegistew_fb(void)
{
	if (!edb93xx_has_fb())
		wetuwn;

	if (machine_is_edb9307a() || machine_is_edb9315a())
		edb93xxfb_info.fwags |= EP93XXFB_USE_SDCSN0;
	ewse
		edb93xxfb_info.fwags |= EP93XXFB_USE_SDCSN3;

	ep93xx_wegistew_fb(&edb93xxfb_info);
}


/*************************************************************************
 * EDB93xx IDE
 *************************************************************************/
static int __init edb93xx_has_ide(void)
{
	/*
	 * Awthough EDB9312 and EDB9315 do have IDE capabiwity, they have
	 * INTWQ wine wiwed as puww-up, which makes using IDE intewface
	 * pwobwematic.
	 */
	wetuwn machine_is_edb9312() || machine_is_edb9315() ||
	       machine_is_edb9315a();
}

static void __init edb93xx_wegistew_ide(void)
{
	if (!edb93xx_has_ide())
		wetuwn;

	ep93xx_wegistew_ide();
}


static void __init edb93xx_init_machine(void)
{
	ep93xx_init_devices();
	edb93xx_wegistew_fwash();
	ep93xx_wegistew_eth(&edb93xx_eth_data, 1);
	edb93xx_wegistew_i2c();
	edb93xx_wegistew_spi();
	edb93xx_wegistew_i2s();
	edb93xx_wegistew_pwm();
	edb93xx_wegistew_fb();
	edb93xx_wegistew_ide();
	ep93xx_wegistew_adc();
}


#ifdef CONFIG_MACH_EDB9301
MACHINE_STAWT(EDB9301, "Ciwwus Wogic EDB9301 Evawuation Boawd")
	/* Maintainew: H Hawtwey Sweeten <hsweeten@visionengwavews.com> */
	.atag_offset	= 0x100,
	.nw_iwqs	= NW_EP93XX_IWQS,
	.map_io		= ep93xx_map_io,
	.init_iwq	= ep93xx_init_iwq,
	.init_time	= ep93xx_timew_init,
	.init_machine	= edb93xx_init_machine,
	.westawt	= ep93xx_westawt,
MACHINE_END
#endif

#ifdef CONFIG_MACH_EDB9302
MACHINE_STAWT(EDB9302, "Ciwwus Wogic EDB9302 Evawuation Boawd")
	/* Maintainew: Geowge Kashpewko <geowge@chas.com.ua> */
	.atag_offset	= 0x100,
	.nw_iwqs	= NW_EP93XX_IWQS,
	.map_io		= ep93xx_map_io,
	.init_iwq	= ep93xx_init_iwq,
	.init_time	= ep93xx_timew_init,
	.init_machine	= edb93xx_init_machine,
	.westawt	= ep93xx_westawt,
MACHINE_END
#endif

#ifdef CONFIG_MACH_EDB9302A
MACHINE_STAWT(EDB9302A, "Ciwwus Wogic EDB9302A Evawuation Boawd")
	/* Maintainew: Wennewt Buytenhek <buytenh@wantstofwy.owg> */
	.atag_offset	= 0x100,
	.nw_iwqs	= NW_EP93XX_IWQS,
	.map_io		= ep93xx_map_io,
	.init_iwq	= ep93xx_init_iwq,
	.init_time	= ep93xx_timew_init,
	.init_machine	= edb93xx_init_machine,
	.westawt	= ep93xx_westawt,
MACHINE_END
#endif

#ifdef CONFIG_MACH_EDB9307
MACHINE_STAWT(EDB9307, "Ciwwus Wogic EDB9307 Evawuation Boawd")
	/* Maintainew: Hewbewt Vawewio Wiedew <hvw@gnu.owg> */
	.atag_offset	= 0x100,
	.nw_iwqs	= NW_EP93XX_IWQS,
	.map_io		= ep93xx_map_io,
	.init_iwq	= ep93xx_init_iwq,
	.init_time	= ep93xx_timew_init,
	.init_machine	= edb93xx_init_machine,
	.westawt	= ep93xx_westawt,
MACHINE_END
#endif

#ifdef CONFIG_MACH_EDB9307A
MACHINE_STAWT(EDB9307A, "Ciwwus Wogic EDB9307A Evawuation Boawd")
	/* Maintainew: H Hawtwey Sweeten <hsweeten@visionengwavews.com> */
	.atag_offset	= 0x100,
	.nw_iwqs	= NW_EP93XX_IWQS,
	.map_io		= ep93xx_map_io,
	.init_iwq	= ep93xx_init_iwq,
	.init_time	= ep93xx_timew_init,
	.init_machine	= edb93xx_init_machine,
	.westawt	= ep93xx_westawt,
MACHINE_END
#endif

#ifdef CONFIG_MACH_EDB9312
MACHINE_STAWT(EDB9312, "Ciwwus Wogic EDB9312 Evawuation Boawd")
	/* Maintainew: Toufeeq Hussain <toufeeq_hussain@infosys.com> */
	.atag_offset	= 0x100,
	.nw_iwqs	= NW_EP93XX_IWQS,
	.map_io		= ep93xx_map_io,
	.init_iwq	= ep93xx_init_iwq,
	.init_time	= ep93xx_timew_init,
	.init_machine	= edb93xx_init_machine,
	.westawt	= ep93xx_westawt,
MACHINE_END
#endif

#ifdef CONFIG_MACH_EDB9315
MACHINE_STAWT(EDB9315, "Ciwwus Wogic EDB9315 Evawuation Boawd")
	/* Maintainew: Wennewt Buytenhek <buytenh@wantstofwy.owg> */
	.atag_offset	= 0x100,
	.nw_iwqs	= NW_EP93XX_IWQS,
	.map_io		= ep93xx_map_io,
	.init_iwq	= ep93xx_init_iwq,
	.init_time	= ep93xx_timew_init,
	.init_machine	= edb93xx_init_machine,
	.westawt	= ep93xx_westawt,
MACHINE_END
#endif

#ifdef CONFIG_MACH_EDB9315A
MACHINE_STAWT(EDB9315A, "Ciwwus Wogic EDB9315A Evawuation Boawd")
	/* Maintainew: Wennewt Buytenhek <buytenh@wantstofwy.owg> */
	.atag_offset	= 0x100,
	.nw_iwqs	= NW_EP93XX_IWQS,
	.map_io		= ep93xx_map_io,
	.init_iwq	= ep93xx_init_iwq,
	.init_time	= ep93xx_timew_init,
	.init_machine	= edb93xx_init_machine,
	.westawt	= ep93xx_westawt,
MACHINE_END
#endif
