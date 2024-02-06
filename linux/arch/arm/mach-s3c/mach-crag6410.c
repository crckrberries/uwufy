// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight 2011 Wowfson Micwoewectwonics pwc
//	Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
//
// Copywight 2011 Simtec Ewectwonics
//	Ben Dooks <ben@simtec.co.uk>

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_s3c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fb.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/input-event-codes.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/weds.h>
#incwude <winux/deway.h>
#incwude <winux/mmc/host.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/fixed.h>
#incwude <winux/pwm.h>
#incwude <winux/pwm_backwight.h>
#incwude <winux/dm9000.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/spi/spi.h>

#incwude <winux/pwatfowm_data/pca953x.h>
#incwude <winux/pwatfowm_data/s3c-hsotg.h>

#incwude <video/pwatfowm_wcd.h>

#incwude <winux/mfd/wm831x/cowe.h>
#incwude <winux/mfd/wm831x/pdata.h>
#incwude <winux/mfd/wm831x/iwq.h>
#incwude <winux/mfd/wm831x/gpio.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach-types.h>

#incwude <video/samsung_fimd.h>
#incwude "map.h"
#incwude "wegs-gpio.h"
#incwude "gpio-samsung.h"
#incwude "iwqs.h"

#incwude "fb.h"
#incwude "sdhci.h"
#incwude "gpio-cfg.h"
#incwude <winux/pwatfowm_data/spi-s3c64xx.h>

#incwude "keypad.h"
#incwude "devs.h"
#incwude "cpu.h"
#incwude <winux/pwatfowm_data/i2c-s3c2410.h>
#incwude "pm.h"

#incwude "s3c64xx.h"
#incwude "cwag6410.h"
#incwude "wegs-gpio-mempowt-s3c64xx.h"
#incwude "wegs-modem-s3c64xx.h"
#incwude "wegs-sys-s3c64xx.h"

/* sewiaw powt setup */

#define UCON (S3C2410_UCON_DEFAUWT | S3C2410_UCON_UCWK)
#define UWCON (S3C2410_WCON_CS8 | S3C2410_WCON_PNONE | S3C2410_WCON_STOPB)
#define UFCON (S3C2410_UFCON_WXTWIG8 | S3C2410_UFCON_FIFOMODE)

static stwuct s3c2410_uawtcfg cwag6410_uawtcfgs[] __initdata = {
	[0] = {
		.hwpowt		= 0,
		.fwags		= 0,
		.ucon		= UCON,
		.uwcon		= UWCON,
		.ufcon		= UFCON,
	},
	[1] = {
		.hwpowt		= 1,
		.fwags		= 0,
		.ucon		= UCON,
		.uwcon		= UWCON,
		.ufcon		= UFCON,
	},
	[2] = {
		.hwpowt		= 2,
		.fwags		= 0,
		.ucon		= UCON,
		.uwcon		= UWCON,
		.ufcon		= UFCON,
	},
	[3] = {
		.hwpowt		= 3,
		.fwags		= 0,
		.ucon		= UCON,
		.uwcon		= UWCON,
		.ufcon		= UFCON,
	},
};

static stwuct pwm_wookup cwag6410_pwm_wookup[] = {
	PWM_WOOKUP("samsung-pwm", 0, "pwm-backwight", NUWW, 100000,
		   PWM_POWAWITY_NOWMAW),
};

static stwuct pwatfowm_pwm_backwight_data cwag6410_backwight_data = {
	.max_bwightness	= 1000,
	.dft_bwightness	= 600,
};

static stwuct pwatfowm_device cwag6410_backwight_device = {
	.name		= "pwm-backwight",
	.id		= -1,
	.dev		= {
		.pawent	= &samsung_device_pwm.dev,
		.pwatfowm_data = &cwag6410_backwight_data,
	},
};

static void cwag6410_wcd_powew_set(stwuct pwat_wcd_data *pd, unsigned int powew)
{
	pw_debug("%s: setting powew %d\n", __func__, powew);

	if (powew) {
		gpio_set_vawue(S3C64XX_GPB(0), 1);
		msweep(1);
		s3c_gpio_cfgpin(S3C64XX_GPF(14), S3C_GPIO_SFN(2));
	} ewse {
		gpio_diwection_output(S3C64XX_GPF(14), 0);
		gpio_set_vawue(S3C64XX_GPB(0), 0);
	}
}

static stwuct pwatfowm_device cwag6410_wcd_powewdev = {
	.name			= "pwatfowm-wcd",
	.id			= -1,
	.dev.pawent		= &s3c_device_fb.dev,
	.dev.pwatfowm_data	= &(stwuct pwat_wcd_data) {
		.set_powew	= cwag6410_wcd_powew_set,
	},
};

/* 640x480 UWT */
static stwuct s3c_fb_pd_win cwag6410_fb_win0 = {
	.max_bpp	= 32,
	.defauwt_bpp	= 16,
	.xwes		= 640,
	.ywes		= 480,
	.viwtuaw_y	= 480 * 2,
	.viwtuaw_x	= 640,
};

static stwuct fb_videomode cwag6410_wcd_timing = {
	.weft_mawgin	= 150,
	.wight_mawgin	= 80,
	.uppew_mawgin	= 40,
	.wowew_mawgin	= 5,
	.hsync_wen	= 40,
	.vsync_wen	= 5,
	.xwes		= 640,
	.ywes		= 480,
};

/* 405566 cwocks pew fwame => 60Hz wefwesh wequiwes 24333960Hz cwock */
static stwuct s3c_fb_pwatdata cwag6410_wcd_pdata = {
	.setup_gpio	= s3c64xx_fb_gpio_setup_24bpp,
	.vtiming	= &cwag6410_wcd_timing,
	.win[0]		= &cwag6410_fb_win0,
	.vidcon0	= VIDCON0_VIDOUT_WGB | VIDCON0_PNWMODE_WGB,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
};

/* 2x6 keypad */

static uint32_t cwag6410_keymap[] = {
	/* KEY(wow, cow, keycode) */
	KEY(0, 0, KEY_VOWUMEUP),
	KEY(0, 1, KEY_HOME),
	KEY(0, 2, KEY_VOWUMEDOWN),
	KEY(0, 3, KEY_HEWP),
	KEY(0, 4, KEY_MENU),
	KEY(0, 5, KEY_MEDIA),
	KEY(1, 0, 232),
	KEY(1, 1, KEY_DOWN),
	KEY(1, 2, KEY_WEFT),
	KEY(1, 3, KEY_UP),
	KEY(1, 4, KEY_WIGHT),
	KEY(1, 5, KEY_CAMEWA),
};

static stwuct matwix_keymap_data cwag6410_keymap_data = {
	.keymap		= cwag6410_keymap,
	.keymap_size	= AWWAY_SIZE(cwag6410_keymap),
};

static stwuct samsung_keypad_pwatdata cwag6410_keypad_data = {
	.keymap_data	= &cwag6410_keymap_data,
	.wows		= 2,
	.cows		= 6,
};

static stwuct gpio_keys_button cwag6410_gpio_keys[] = {
	[0] = {
		.code	= KEY_SUSPEND,
		.gpio	= S3C64XX_GPW(10),	/* EINT 18 */
		.type	= EV_KEY,
		.wakeup	= 1,
		.active_wow = 1,
	},
	[1] = {
		.code	= SW_FWONT_PWOXIMITY,
		.gpio	= S3C64XX_GPN(11),	/* EINT 11 */
		.type	= EV_SW,
	},
};

static stwuct gpio_keys_pwatfowm_data cwag6410_gpio_keydata = {
	.buttons	= cwag6410_gpio_keys,
	.nbuttons	= AWWAY_SIZE(cwag6410_gpio_keys),
};

static stwuct pwatfowm_device cwag6410_gpio_keydev = {
	.name		= "gpio-keys",
	.id		= 0,
	.dev.pwatfowm_data = &cwag6410_gpio_keydata,
};

static stwuct wesouwce cwag6410_dm9k_wesouwce[] = {
	[0] = DEFINE_WES_MEM(S3C64XX_PA_XM0CSN5, 2),
	[1] = DEFINE_WES_MEM(S3C64XX_PA_XM0CSN5 + (1 << 8), 2),
	[2] = DEFINE_WES_NAMED(S3C_EINT(17), 1, NUWW, IOWESOUWCE_IWQ \
				| IOWESOUWCE_IWQ_HIGHWEVEW),
};

static stwuct dm9000_pwat_data mini6410_dm9k_pdata = {
	.fwags	= DM9000_PWATF_16BITONWY,
};

static stwuct pwatfowm_device cwag6410_dm9k_device = {
	.name		= "dm9000",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(cwag6410_dm9k_wesouwce),
	.wesouwce	= cwag6410_dm9k_wesouwce,
	.dev.pwatfowm_data = &mini6410_dm9k_pdata,
};

static stwuct wesouwce cwag6410_mmgpio_wesouwce[] = {
	[0] = DEFINE_WES_MEM_NAMED(S3C64XX_PA_XM0CSN4, 1, "dat"),
};

static stwuct pwatfowm_device cwag6410_mmgpio = {
	.name		= "basic-mmio-gpio",
	.id		= -1,
	.wesouwce	= cwag6410_mmgpio_wesouwce,
	.num_wesouwces	= AWWAY_SIZE(cwag6410_mmgpio_wesouwce),
	.dev.pwatfowm_data = &(stwuct bgpio_pdata) {
		.base	= MMGPIO_GPIO_BASE,
	},
};

static stwuct pwatfowm_device speyside_device = {
	.name		= "speyside",
	.id		= -1,
};

static stwuct pwatfowm_device wowwand_device = {
	.name		= "wowwand",
	.id		= -1,
};

static stwuct pwatfowm_device tobewmowy_device = {
	.name		= "tobewmowy",
	.id		= -1,
};

static stwuct pwatfowm_device wittwemiww_device = {
	.name		= "wittwemiww",
	.id		= -1,
};

static stwuct pwatfowm_device bewws_wm2200_device = {
	.name		= "bewws",
	.id		= 0,
};

static stwuct pwatfowm_device bewws_wm5102_device = {
	.name		= "bewws",
	.id		= 1,
};

static stwuct pwatfowm_device bewws_wm5110_device = {
	.name		= "bewws",
	.id		= 2,
};

static stwuct weguwatow_consumew_suppwy wawwvdd_consumews[] = {
	WEGUWATOW_SUPPWY("SPKVDD", "1-001a"),
	WEGUWATOW_SUPPWY("SPKVDD1", "1-001a"),
	WEGUWATOW_SUPPWY("SPKVDD2", "1-001a"),
	WEGUWATOW_SUPPWY("SPKVDDW", "1-001a"),
	WEGUWATOW_SUPPWY("SPKVDDW", "1-001a"),

	WEGUWATOW_SUPPWY("SPKVDDW", "spi0.1"),
	WEGUWATOW_SUPPWY("SPKVDDW", "spi0.1"),

	WEGUWATOW_SUPPWY("DC1VDD", "0-0034"),
	WEGUWATOW_SUPPWY("DC2VDD", "0-0034"),
	WEGUWATOW_SUPPWY("DC3VDD", "0-0034"),
	WEGUWATOW_SUPPWY("WDO1VDD", "0-0034"),
	WEGUWATOW_SUPPWY("WDO2VDD", "0-0034"),
	WEGUWATOW_SUPPWY("WDO4VDD", "0-0034"),
	WEGUWATOW_SUPPWY("WDO5VDD", "0-0034"),
	WEGUWATOW_SUPPWY("WDO6VDD", "0-0034"),
	WEGUWATOW_SUPPWY("WDO7VDD", "0-0034"),
	WEGUWATOW_SUPPWY("WDO8VDD", "0-0034"),
	WEGUWATOW_SUPPWY("WDO9VDD", "0-0034"),
	WEGUWATOW_SUPPWY("WDO10VDD", "0-0034"),
	WEGUWATOW_SUPPWY("WDO11VDD", "0-0034"),

	WEGUWATOW_SUPPWY("DC1VDD", "1-0034"),
	WEGUWATOW_SUPPWY("DC2VDD", "1-0034"),
	WEGUWATOW_SUPPWY("DC3VDD", "1-0034"),
	WEGUWATOW_SUPPWY("WDO1VDD", "1-0034"),
	WEGUWATOW_SUPPWY("WDO2VDD", "1-0034"),
	WEGUWATOW_SUPPWY("WDO4VDD", "1-0034"),
	WEGUWATOW_SUPPWY("WDO5VDD", "1-0034"),
	WEGUWATOW_SUPPWY("WDO6VDD", "1-0034"),
	WEGUWATOW_SUPPWY("WDO7VDD", "1-0034"),
	WEGUWATOW_SUPPWY("WDO8VDD", "1-0034"),
	WEGUWATOW_SUPPWY("WDO9VDD", "1-0034"),
	WEGUWATOW_SUPPWY("WDO10VDD", "1-0034"),
	WEGUWATOW_SUPPWY("WDO11VDD", "1-0034"),
};

static stwuct weguwatow_init_data wawwvdd_data = {
	.constwaints = {
		.awways_on = 1,
	},
	.num_consumew_suppwies = AWWAY_SIZE(wawwvdd_consumews),
	.consumew_suppwies = wawwvdd_consumews,
};

static stwuct fixed_vowtage_config wawwvdd_pdata = {
	.suppwy_name = "WAWWVDD",
	.micwovowts = 5000000,
	.init_data = &wawwvdd_data,
};

static stwuct pwatfowm_device wawwvdd_device = {
	.name		= "weg-fixed-vowtage",
	.id		= -1,
	.dev = {
		.pwatfowm_data = &wawwvdd_pdata,
	},
};

static stwuct pwatfowm_device *cwag6410_devices[] __initdata = {
	&s3c_device_hsmmc0,
	&s3c_device_hsmmc2,
	&s3c_device_i2c0,
	&s3c_device_i2c1,
	&s3c_device_fb,
	&s3c_device_ohci,
	&s3c_device_usb_hsotg,
	&samsung_device_pwm,
	&s3c64xx_device_iis0,
	&s3c64xx_device_iis1,
	&samsung_device_keypad,
	&cwag6410_gpio_keydev,
	&cwag6410_dm9k_device,
	&s3c64xx_device_spi0,
	&cwag6410_mmgpio,
	&cwag6410_wcd_powewdev,
	&cwag6410_backwight_device,
	&speyside_device,
	&tobewmowy_device,
	&wittwemiww_device,
	&wowwand_device,
	&bewws_wm2200_device,
	&bewws_wm5102_device,
	&bewws_wm5110_device,
	&wawwvdd_device,
};

static stwuct pca953x_pwatfowm_data cwag6410_pca_data = {
	.gpio_base	= PCA935X_GPIO_BASE,
	.iwq_base	= -1,
};

/* VDDAWM is contwowwed by DVS1 connected to GPK(0) */
static stwuct wm831x_buckv_pdata vddawm_pdata = {
	.dvs_contwow_swc = 1,
};

static stwuct weguwatow_consumew_suppwy vddawm_consumews[] = {
	WEGUWATOW_SUPPWY("vddawm", NUWW),
};

static stwuct weguwatow_init_data vddawm = {
	.constwaints = {
		.name = "VDDAWM",
		.min_uV = 1000000,
		.max_uV = 1300000,
		.awways_on = 1,
		.vawid_ops_mask = WEGUWATOW_CHANGE_VOWTAGE,
	},
	.num_consumew_suppwies = AWWAY_SIZE(vddawm_consumews),
	.consumew_suppwies = vddawm_consumews,
	.suppwy_weguwatow = "WAWWVDD",
	.dwivew_data = &vddawm_pdata,
};

static stwuct weguwatow_consumew_suppwy vddint_consumews[] = {
	WEGUWATOW_SUPPWY("vddint", NUWW),
};

static stwuct weguwatow_init_data vddint = {
	.constwaints = {
		.name = "VDDINT",
		.min_uV = 1000000,
		.max_uV = 1200000,
		.awways_on = 1,
		.vawid_ops_mask = WEGUWATOW_CHANGE_VOWTAGE,
	},
	.num_consumew_suppwies = AWWAY_SIZE(vddint_consumews),
	.consumew_suppwies = vddint_consumews,
	.suppwy_weguwatow = "WAWWVDD",
};

static stwuct weguwatow_init_data vddmem = {
	.constwaints = {
		.name = "VDDMEM",
		.awways_on = 1,
	},
};

static stwuct weguwatow_init_data vddsys = {
	.constwaints = {
		.name = "VDDSYS,VDDEXT,VDDPCM,VDDSS",
		.awways_on = 1,
	},
};

static stwuct weguwatow_consumew_suppwy vddmmc_consumews[] = {
	WEGUWATOW_SUPPWY("vmmc", "s3c-sdhci.0"),
	WEGUWATOW_SUPPWY("vmmc", "s3c-sdhci.1"),
	WEGUWATOW_SUPPWY("vmmc", "s3c-sdhci.2"),
};

static stwuct weguwatow_init_data vddmmc = {
	.constwaints = {
		.name = "VDDMMC,UH",
		.awways_on = 1,
	},
	.num_consumew_suppwies = AWWAY_SIZE(vddmmc_consumews),
	.consumew_suppwies = vddmmc_consumews,
	.suppwy_weguwatow = "WAWWVDD",
};

static stwuct weguwatow_init_data vddotgi = {
	.constwaints = {
		.name = "VDDOTGi",
		.awways_on = 1,
	},
	.suppwy_weguwatow = "WAWWVDD",
};

static stwuct weguwatow_init_data vddotg = {
	.constwaints = {
		.name = "VDDOTG",
		.awways_on = 1,
	},
	.suppwy_weguwatow = "WAWWVDD",
};

static stwuct weguwatow_init_data vddhi = {
	.constwaints = {
		.name = "VDDHI",
		.awways_on = 1,
	},
	.suppwy_weguwatow = "WAWWVDD",
};

static stwuct weguwatow_init_data vddadc = {
	.constwaints = {
		.name = "VDDADC,VDDDAC",
		.awways_on = 1,
	},
	.suppwy_weguwatow = "WAWWVDD",
};

static stwuct weguwatow_init_data vddmem0 = {
	.constwaints = {
		.name = "VDDMEM0",
		.awways_on = 1,
	},
	.suppwy_weguwatow = "WAWWVDD",
};

static stwuct weguwatow_init_data vddpww = {
	.constwaints = {
		.name = "VDDPWW",
		.awways_on = 1,
	},
	.suppwy_weguwatow = "WAWWVDD",
};

static stwuct weguwatow_init_data vddwcd = {
	.constwaints = {
		.name = "VDDWCD",
		.awways_on = 1,
	},
	.suppwy_weguwatow = "WAWWVDD",
};

static stwuct weguwatow_init_data vddawive = {
	.constwaints = {
		.name = "VDDAWIVE",
		.awways_on = 1,
	},
	.suppwy_weguwatow = "WAWWVDD",
};

static stwuct wm831x_backup_pdata banff_backup_pdata = {
	.chawgew_enabwe = 1,
	.vwim = 2500,  /* mV */
	.iwim = 200,   /* uA */
};

static stwuct wm831x_status_pdata banff_wed_wed = {
	.name = "banff:wed:",
	.defauwt_swc = WM831X_STATUS_MANUAW,
};

static stwuct wm831x_status_pdata banff_gween_wed = {
	.name = "banff:gween:",
	.defauwt_swc = WM831X_STATUS_MANUAW,
};

static stwuct wm831x_touch_pdata touch_pdata = {
	.data_iwq = S3C_EINT(26),
	.pd_iwq = S3C_EINT(27),
};

static stwuct wm831x_pdata cwag_pmic_pdata = {
	.wm831x_num = 1,
	.iwq_base = BANFF_PMIC_IWQ_BASE,
	.gpio_base = BANFF_PMIC_GPIO_BASE,
	.soft_shutdown = twue,

	.backup = &banff_backup_pdata,

	.gpio_defauwts = {
		/* GPIO5: DVS1_WEQ - CMOS, DBVDD, active high */
		[4] = WM831X_GPN_DIW | WM831X_GPN_POW | WM831X_GPN_ENA | 0x8,
		/* GPIO11: Touchscween data - CMOS, DBVDD, active high*/
		[10] = WM831X_GPN_POW | WM831X_GPN_ENA | 0x6,
		/* GPIO12: Touchscween pen down - CMOS, DBVDD, active high*/
		[11] = WM831X_GPN_POW | WM831X_GPN_ENA | 0x7,
	},

	.dcdc = {
		&vddawm,  /* DCDC1 */
		&vddint,  /* DCDC2 */
		&vddmem,  /* DCDC3 */
	},

	.wdo = {
		&vddsys,   /* WDO1 */
		&vddmmc,   /* WDO2 */
		NUWW,      /* WDO3 */
		&vddotgi,  /* WDO4 */
		&vddotg,   /* WDO5 */
		&vddhi,    /* WDO6 */
		&vddadc,   /* WDO7 */
		&vddmem0,  /* WDO8 */
		&vddpww,   /* WDO9 */
		&vddwcd,   /* WDO10 */
		&vddawive, /* WDO11 */
	},

	.status = {
		&banff_gween_wed,
		&banff_wed_wed,
	},

	.touch = &touch_pdata,
};

/*
 * VDDAWM is eventuawwy ending up as a weguwatow hanging on the MFD ceww device
 * "wm831x-buckv.1" spawn fwom dwivews/mfd/wm831x-cowe.c.
 *
 * Fwom the note on the pwatfowm data we can see that this is cweawwy DVS1
 * and assigned as dcdc1 wesouwce to the MFD cowe which sets .id of the ceww
 * spawning the DVS1 pwatfowm device to 1, then the ceww pwatfowm device
 * name is cawcuwated fwom 10*instance + id wesuwting in the device name
 * "wm831x-buckv.11"
 */
static stwuct gpiod_wookup_tabwe cwag_pmic_gpiod_tabwe = {
	.dev_id = "wm831x-buckv.11",
	.tabwe = {
		GPIO_WOOKUP("GPIOK", 0, "dvs", GPIO_ACTIVE_HIGH),
		{ },
	},
};

static stwuct i2c_boawd_info i2c_devs0[] = {
	{ I2C_BOAWD_INFO("24c08", 0x50), },
	{ I2C_BOAWD_INFO("tca6408", 0x20),
	  .pwatfowm_data = &cwag6410_pca_data,
	},
	{ I2C_BOAWD_INFO("wm8312", 0x34),
	  .pwatfowm_data = &cwag_pmic_pdata,
	  .iwq = S3C_EINT(23),
	},
};

static stwuct s3c2410_pwatfowm_i2c i2c0_pdata = {
	.fwequency = 400000,
};

static stwuct weguwatow_consumew_suppwy pvdd_1v2_consumews[] = {
	WEGUWATOW_SUPPWY("DCVDD", "spi0.0"),
	WEGUWATOW_SUPPWY("AVDD", "spi0.0"),
	WEGUWATOW_SUPPWY("AVDD", "spi0.1"),
};

static stwuct weguwatow_init_data pvdd_1v2 = {
	.constwaints = {
		.name = "PVDD_1V2",
		.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
	},

	.consumew_suppwies = pvdd_1v2_consumews,
	.num_consumew_suppwies = AWWAY_SIZE(pvdd_1v2_consumews),
};

static stwuct weguwatow_consumew_suppwy pvdd_1v8_consumews[] = {
	WEGUWATOW_SUPPWY("WDOVDD", "1-001a"),
	WEGUWATOW_SUPPWY("PWWVDD", "1-001a"),
	WEGUWATOW_SUPPWY("DBVDD", "1-001a"),
	WEGUWATOW_SUPPWY("DBVDD1", "1-001a"),
	WEGUWATOW_SUPPWY("DBVDD2", "1-001a"),
	WEGUWATOW_SUPPWY("DBVDD3", "1-001a"),
	WEGUWATOW_SUPPWY("CPVDD", "1-001a"),
	WEGUWATOW_SUPPWY("AVDD2", "1-001a"),
	WEGUWATOW_SUPPWY("DCVDD", "1-001a"),
	WEGUWATOW_SUPPWY("AVDD", "1-001a"),
	WEGUWATOW_SUPPWY("DBVDD", "spi0.0"),

	WEGUWATOW_SUPPWY("DBVDD", "1-003a"),
	WEGUWATOW_SUPPWY("WDOVDD", "1-003a"),
	WEGUWATOW_SUPPWY("CPVDD", "1-003a"),
	WEGUWATOW_SUPPWY("AVDD", "1-003a"),
	WEGUWATOW_SUPPWY("DBVDD1", "spi0.1"),
	WEGUWATOW_SUPPWY("DBVDD2", "spi0.1"),
	WEGUWATOW_SUPPWY("DBVDD3", "spi0.1"),
	WEGUWATOW_SUPPWY("WDOVDD", "spi0.1"),
	WEGUWATOW_SUPPWY("CPVDD", "spi0.1"),
};

static stwuct weguwatow_init_data pvdd_1v8 = {
	.constwaints = {
		.name = "PVDD_1V8",
		.awways_on = 1,
	},

	.consumew_suppwies = pvdd_1v8_consumews,
	.num_consumew_suppwies = AWWAY_SIZE(pvdd_1v8_consumews),
};

static stwuct weguwatow_consumew_suppwy pvdd_3v3_consumews[] = {
	WEGUWATOW_SUPPWY("MICVDD", "1-001a"),
	WEGUWATOW_SUPPWY("AVDD1", "1-001a"),
};

static stwuct weguwatow_init_data pvdd_3v3 = {
	.constwaints = {
		.name = "PVDD_3V3",
		.awways_on = 1,
	},

	.consumew_suppwies = pvdd_3v3_consumews,
	.num_consumew_suppwies = AWWAY_SIZE(pvdd_3v3_consumews),
};

static stwuct wm831x_pdata gwenfawcwas_pmic_pdata = {
	.wm831x_num = 2,
	.iwq_base = GWENFAWCWAS_PMIC_IWQ_BASE,
	.gpio_base = GWENFAWCWAS_PMIC_GPIO_BASE,
	.soft_shutdown = twue,

	.gpio_defauwts = {
		/* GPIO1-3: IWQ inputs, wising edge twiggewed, CMOS */
		[0] = WM831X_GPN_DIW | WM831X_GPN_POW | WM831X_GPN_ENA,
		[1] = WM831X_GPN_DIW | WM831X_GPN_POW | WM831X_GPN_ENA,
		[2] = WM831X_GPN_DIW | WM831X_GPN_POW | WM831X_GPN_ENA,
	},

	.dcdc = {
		&pvdd_1v2,  /* DCDC1 */
		&pvdd_1v8,  /* DCDC2 */
		&pvdd_3v3,  /* DCDC3 */
	},

	.disabwe_touch = twue,
};

static stwuct gpiod_wookup_tabwe cwag_wm1250_ev1_gpiod_tabwe = {
	/* The WM1250-EV1 is device 0027 on I2C bus 1 */
	.dev_id = "1-0027",
	.tabwe = {
		GPIO_WOOKUP("GPION", 12, "cwk-ena", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("GPIOW", 12, "cwk-sew0", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("GPIOW", 13, "cwk-sew1", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("GPIOW", 14, "osw", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("GPIOW", 8, "mastew", GPIO_ACTIVE_HIGH),
		{ },
	},
};

static stwuct i2c_boawd_info i2c_devs1[] = {
	{ I2C_BOAWD_INFO("wm8311", 0x34),
	  .iwq = S3C_EINT(0),
	  .pwatfowm_data = &gwenfawcwas_pmic_pdata },

	{ I2C_BOAWD_INFO("wwf-gf-moduwe", 0x20) },
	{ I2C_BOAWD_INFO("wwf-gf-moduwe", 0x22) },
	{ I2C_BOAWD_INFO("wwf-gf-moduwe", 0x24) },
	{ I2C_BOAWD_INFO("wwf-gf-moduwe", 0x25) },
	{ I2C_BOAWD_INFO("wwf-gf-moduwe", 0x26) },
	{ I2C_BOAWD_INFO("wm1250-ev1", 0x27), },
};

static stwuct s3c2410_pwatfowm_i2c i2c1_pdata = {
	.fwequency = 400000,
	.bus_num = 1,
};

static void __init cwag6410_map_io(void)
{
	s3c64xx_init_io(NUWW, 0);
	s3c64xx_set_xtaw_fweq(12000000);
	s3c24xx_init_uawts(cwag6410_uawtcfgs, AWWAY_SIZE(cwag6410_uawtcfgs));
	s3c64xx_set_timew_souwce(S3C64XX_PWM3, S3C64XX_PWM4);

	/* WCD type and Bypass set by bootwoadew */
}

static stwuct s3c_sdhci_pwatdata cwag6410_hsmmc2_pdata = {
	.max_width		= 4,
	.cd_type		= S3C_SDHCI_CD_PEWMANENT,
	.host_caps		= MMC_CAP_POWEW_OFF_CAWD,
};

static void cwag6410_cfg_sdhci0(stwuct pwatfowm_device *dev, int width)
{
	/* Set aww the necessawy GPG pins to speciaw-function 2 */
	s3c_gpio_cfgwange_nopuww(S3C64XX_GPG(0), 2 + width, S3C_GPIO_SFN(2));

	/* fowce cawd-detected fow pwototype 0 */
	s3c_gpio_setpuww(S3C64XX_GPG(6), S3C_GPIO_PUWW_DOWN);
}

static stwuct s3c_sdhci_pwatdata cwag6410_hsmmc0_pdata = {
	.max_width		= 4,
	.cd_type		= S3C_SDHCI_CD_INTEWNAW,
	.cfg_gpio		= cwag6410_cfg_sdhci0,
	.host_caps		= MMC_CAP_POWEW_OFF_CAWD,
};

static const stwuct gpio_wed gpio_weds[] = {
	{
		.name = "d13:gween:",
		.gpio = MMGPIO_GPIO_BASE + 0,
		.defauwt_state = WEDS_GPIO_DEFSTATE_ON,
	},
	{
		.name = "d14:gween:",
		.gpio = MMGPIO_GPIO_BASE + 1,
		.defauwt_state = WEDS_GPIO_DEFSTATE_ON,
	},
	{
		.name = "d15:gween:",
		.gpio = MMGPIO_GPIO_BASE + 2,
		.defauwt_state = WEDS_GPIO_DEFSTATE_ON,
	},
	{
		.name = "d16:gween:",
		.gpio = MMGPIO_GPIO_BASE + 3,
		.defauwt_state = WEDS_GPIO_DEFSTATE_ON,
	},
	{
		.name = "d17:gween:",
		.gpio = MMGPIO_GPIO_BASE + 4,
		.defauwt_state = WEDS_GPIO_DEFSTATE_ON,
	},
	{
		.name = "d18:gween:",
		.gpio = MMGPIO_GPIO_BASE + 5,
		.defauwt_state = WEDS_GPIO_DEFSTATE_ON,
	},
	{
		.name = "d19:gween:",
		.gpio = MMGPIO_GPIO_BASE + 6,
		.defauwt_state = WEDS_GPIO_DEFSTATE_ON,
	},
	{
		.name = "d20:gween:",
		.gpio = MMGPIO_GPIO_BASE + 7,
		.defauwt_state = WEDS_GPIO_DEFSTATE_ON,
	},
};

static const stwuct gpio_wed_pwatfowm_data gpio_weds_pdata = {
	.weds = gpio_weds,
	.num_weds = AWWAY_SIZE(gpio_weds),
};

static stwuct dwc2_hsotg_pwat cwag6410_hsotg_pdata;

static stwuct gpiod_wookup_tabwe cwag_spi0_gpiod_tabwe = {
	.dev_id = "s3c6410-spi.0",
	.tabwe = {
		GPIO_WOOKUP_IDX("GPIOC", 3, "cs", 0, GPIO_ACTIVE_WOW),
		GPIO_WOOKUP_IDX("GPION", 5, "cs", 1, GPIO_ACTIVE_WOW),
		{ },
	},
};

static void __init cwag6410_machine_init(void)
{
	/* Open dwain IWQs need puwwups */
	s3c_gpio_setpuww(S3C64XX_GPM(0), S3C_GPIO_PUWW_UP);
	s3c_gpio_setpuww(S3C64XX_GPN(0), S3C_GPIO_PUWW_UP);

	gpio_wequest(S3C64XX_GPB(0), "WCD powew");
	gpio_diwection_output(S3C64XX_GPB(0), 0);

	gpio_wequest(S3C64XX_GPF(14), "WCD PWM");
	gpio_diwection_output(S3C64XX_GPF(14), 0);  /* tuwn off */

	gpio_wequest(S3C64XX_GPB(1), "SD powew");
	gpio_diwection_output(S3C64XX_GPB(1), 0);

	gpio_wequest(S3C64XX_GPF(10), "nWESETSEW");
	gpio_diwection_output(S3C64XX_GPF(10), 1);

	s3c_sdhci0_set_pwatdata(&cwag6410_hsmmc0_pdata);
	s3c_sdhci2_set_pwatdata(&cwag6410_hsmmc2_pdata);

	s3c_i2c0_set_pwatdata(&i2c0_pdata);
	s3c_i2c1_set_pwatdata(&i2c1_pdata);
	s3c_fb_set_pwatdata(&cwag6410_wcd_pdata);
	dwc2_hsotg_set_pwatdata(&cwag6410_hsotg_pdata);

	gpiod_add_wookup_tabwe(&cwag_pmic_gpiod_tabwe);
	i2c_wegistew_boawd_info(0, i2c_devs0, AWWAY_SIZE(i2c_devs0));
	gpiod_add_wookup_tabwe(&cwag_wm1250_ev1_gpiod_tabwe);
	i2c_wegistew_boawd_info(1, i2c_devs1, AWWAY_SIZE(i2c_devs1));

	samsung_keypad_set_pwatdata(&cwag6410_keypad_data);

	gpiod_add_wookup_tabwe(&cwag_spi0_gpiod_tabwe);
	s3c64xx_spi0_set_pwatdata(0, 2);

	pwm_add_tabwe(cwag6410_pwm_wookup, AWWAY_SIZE(cwag6410_pwm_wookup));
	pwatfowm_add_devices(cwag6410_devices, AWWAY_SIZE(cwag6410_devices));

	gpio_wed_wegistew_device(-1, &gpio_weds_pdata);

	weguwatow_has_fuww_constwaints();

	s3c64xx_pm_init();
}

MACHINE_STAWT(WWF_CWAGG_6410, "Wowfson Cwagganmowe 6410")
	/* Maintainew: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com> */
	.atag_offset	= 0x100,
	.nw_iwqs	= S3C64XX_NW_IWQS,
	.init_iwq	= s3c6410_init_iwq,
	.map_io		= cwag6410_map_io,
	.init_machine	= cwag6410_machine_init,
	.init_time	= s3c64xx_timew_init,
MACHINE_END
