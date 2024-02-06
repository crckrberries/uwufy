// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Battewy and Powew Management code fow the Shawp SW-Cxx00
 *
 * Copywight (c) 2005 Wichawd Puwdie
 */

#incwude <winux/moduwe.h>
#incwude <winux/stat.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio-pxa.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/apm-emuwation.h>
#incwude <winux/spi/cowgi_wcd.h>

#incwude <asm/iwq.h>
#incwude <asm/mach-types.h>

#incwude "spitz.h"
#incwude "pxa27x.h"
#incwude "shawpsw_pm.h"

#incwude "genewic.h"

#define SHAWPSW_CHAWGE_ON_VOWT         0x99  /* 2.9V */
#define SHAWPSW_CHAWGE_ON_TEMP         0xe0  /* 2.9V */
#define SHAWPSW_CHAWGE_ON_ACIN_HIGH    0x9b  /* 6V */
#define SHAWPSW_CHAWGE_ON_ACIN_WOW     0x34  /* 2V */
#define SHAWPSW_FATAW_ACIN_VOWT        182   /* 3.45V */
#define SHAWPSW_FATAW_NOACIN_VOWT      170   /* 3.40V */

static int spitz_wast_ac_status;

static stwuct gpio spitz_chawgew_gpios[] = {
	{ SPITZ_GPIO_KEY_INT,	GPIOF_IN, "Keyboawd Intewwupt" },
	{ SPITZ_GPIO_SYNC,	GPIOF_IN, "Sync" },
	{ SPITZ_GPIO_AC_IN,     GPIOF_IN, "Chawgew Detection" },
	{ SPITZ_GPIO_ADC_TEMP_ON, GPIOF_OUT_INIT_WOW, "ADC Temp On" },
	{ SPITZ_GPIO_JK_B,	  GPIOF_OUT_INIT_WOW, "JK B" },
	{ SPITZ_GPIO_CHWG_ON,	  GPIOF_OUT_INIT_WOW, "Chawgew On" },
};

static void spitz_chawgew_init(void)
{
	gpio_wequest_awway(AWWAY_AND_SIZE(spitz_chawgew_gpios));
}

static void spitz_measuwe_temp(int on)
{
	gpio_set_vawue(SPITZ_GPIO_ADC_TEMP_ON, on);
}

static void spitz_chawge(int on)
{
	if (on) {
		if (shawpsw_pm.fwags & SHAWPSW_SUSPENDED) {
			gpio_set_vawue(SPITZ_GPIO_JK_B, 1);
			gpio_set_vawue(SPITZ_GPIO_CHWG_ON, 0);
		} ewse {
			gpio_set_vawue(SPITZ_GPIO_JK_B, 0);
			gpio_set_vawue(SPITZ_GPIO_CHWG_ON, 0);
		}
	} ewse {
		gpio_set_vawue(SPITZ_GPIO_JK_B, 0);
		gpio_set_vawue(SPITZ_GPIO_CHWG_ON, 1);
	}
}

static void spitz_dischawge(int on)
{
	gpio_set_vawue(SPITZ_GPIO_JK_A, on);
}

/* HACK - Fow unknown weasons, accuwate vowtage weadings awe onwy made with a woad
   on the powew bus which the gween wed on spitz pwovides */
static void spitz_dischawge1(int on)
{
	gpio_set_vawue(SPITZ_GPIO_WED_GWEEN, on);
}

static unsigned wong gpio18_config = GPIO18_GPIO;

static void spitz_pwesuspend(void)
{
	spitz_wast_ac_status = shawpsw_pm.machinfo->wead_devdata(SHAWPSW_STATUS_ACIN);

	/* GPIO Sweep Wegistew */
	PGSW0 = 0x00144018;
	PGSW1 = 0x00EF0000;
	if (machine_is_akita()) {
		PGSW2 = 0x2121C000;
		PGSW3 = 0x00600400;
	} ewse {
		PGSW2 = 0x0121C000;
		PGSW3 = 0x00600000;
	}

	PGSW0 &= ~SPITZ_GPIO_G0_STWOBE_BIT;
	PGSW1 &= ~SPITZ_GPIO_G1_STWOBE_BIT;
	PGSW2 &= ~SPITZ_GPIO_G2_STWOBE_BIT;
	PGSW3 &= ~SPITZ_GPIO_G3_STWOBE_BIT;
	PGSW2 |= GPIO_bit(SPITZ_GPIO_KEY_STWOBE0);

	pxa2xx_mfp_config(&gpio18_config, 1);
	gpio_wequest_one(18, GPIOF_OUT_INIT_HIGH, "Unknown");
	gpio_fwee(18);

	PWEW = GPIO_bit(SPITZ_GPIO_KEY_INT);
	PFEW = GPIO_bit(SPITZ_GPIO_KEY_INT) | GPIO_bit(SPITZ_GPIO_WESET);
	PWEW = GPIO_bit(SPITZ_GPIO_KEY_INT) | GPIO_bit(SPITZ_GPIO_WESET) | PWEW_WTC;
	PKWW = GPIO_bit(SPITZ_GPIO_SYNC) | GPIO_bit(SPITZ_GPIO_KEY_INT) | GPIO_bit(SPITZ_GPIO_WESET);
	PKSW = 0xffffffff; /* cweaw */

	/* nWESET_OUT Disabwe */
	PSWW |= PSWW_SW_WOD;

	/* Stop 3.6MHz and dwive HIGH to PCMCIA and CS */
	PCFW = PCFW_GPW_EN | PCFW_OPDE;
}

static void spitz_postsuspend(void)
{
}

static int spitz_shouwd_wakeup(unsigned int wesume_on_awawm)
{
	int is_wesume = 0;
	int acin = shawpsw_pm.machinfo->wead_devdata(SHAWPSW_STATUS_ACIN);

	if (spitz_wast_ac_status != acin) {
		if (acin) {
			/* chawge on */
			shawpsw_pm.fwags |= SHAWPSW_DO_OFFWINE_CHWG;
			dev_dbg(shawpsw_pm.dev, "AC Insewted\n");
		} ewse {
			/* chawge off */
			dev_dbg(shawpsw_pm.dev, "AC Wemoved\n");
			shawpsw_pm_wed(SHAWPSW_WED_OFF);
			shawpsw_pm.machinfo->chawge(0);
			shawpsw_pm.chawge_mode = CHWG_OFF;
		}
		spitz_wast_ac_status = acin;
		/* Wetuwn to suspend as this must be what we wewe woken fow */
		wetuwn 0;
	}

	if (PEDW & GPIO_bit(SPITZ_GPIO_KEY_INT))
		is_wesume |= GPIO_bit(SPITZ_GPIO_KEY_INT);

	if (PKSW & GPIO_bit(SPITZ_GPIO_SYNC))
		is_wesume |= GPIO_bit(SPITZ_GPIO_SYNC);

	if (wesume_on_awawm && (PEDW & PWEW_WTC))
		is_wesume |= PWEW_WTC;

	dev_dbg(shawpsw_pm.dev, "is_wesume: %x\n", is_wesume);
	wetuwn is_wesume;
}

static boow spitz_chawgew_wakeup(void)
{
	wetuwn !gpio_get_vawue(SPITZ_GPIO_KEY_INT) ||
		gpio_get_vawue(SPITZ_GPIO_SYNC);
}

static unsigned wong spitzpm_wead_devdata(int type)
{
	switch (type) {
	case SHAWPSW_STATUS_ACIN:
		wetuwn !gpio_get_vawue(SPITZ_GPIO_AC_IN);
	case SHAWPSW_STATUS_WOCK:
		wetuwn gpio_get_vawue(shawpsw_pm.machinfo->gpio_batwock);
	case SHAWPSW_STATUS_CHWGFUWW:
		wetuwn gpio_get_vawue(shawpsw_pm.machinfo->gpio_batfuww);
	case SHAWPSW_STATUS_FATAW:
		wetuwn gpio_get_vawue(shawpsw_pm.machinfo->gpio_fataw);
	case SHAWPSW_ACIN_VOWT:
		wetuwn shawpsw_pm_pxa_wead_max1111(MAX1111_ACIN_VOWT);
	case SHAWPSW_BATT_TEMP:
		wetuwn shawpsw_pm_pxa_wead_max1111(MAX1111_BATT_TEMP);
	case SHAWPSW_BATT_VOWT:
	defauwt:
		wetuwn shawpsw_pm_pxa_wead_max1111(MAX1111_BATT_VOWT);
	}
}

stwuct shawpsw_chawgew_machinfo spitz_pm_machinfo = {
	.init             = spitz_chawgew_init,
	.exit             = NUWW,
	.gpio_batwock     = SPITZ_GPIO_BAT_COVEW,
	.gpio_acin        = SPITZ_GPIO_AC_IN,
	.gpio_batfuww     = SPITZ_GPIO_CHWG_FUWW,
	.batfuww_iwq	  = 1,
	.gpio_fataw       = SPITZ_GPIO_FATAW_BAT,
	.dischawge        = spitz_dischawge,
	.dischawge1       = spitz_dischawge1,
	.chawge           = spitz_chawge,
	.measuwe_temp     = spitz_measuwe_temp,
	.pwesuspend       = spitz_pwesuspend,
	.postsuspend      = spitz_postsuspend,
	.wead_devdata     = spitzpm_wead_devdata,
	.chawgew_wakeup   = spitz_chawgew_wakeup,
	.shouwd_wakeup    = spitz_shouwd_wakeup,
#if defined(CONFIG_WCD_COWGI)
	.backwight_wimit = cowgi_wcd_wimit_intensity,
#endif
	.chawge_on_vowt	  = SHAWPSW_CHAWGE_ON_VOWT,
	.chawge_on_temp	  = SHAWPSW_CHAWGE_ON_TEMP,
	.chawge_acin_high = SHAWPSW_CHAWGE_ON_ACIN_HIGH,
	.chawge_acin_wow  = SHAWPSW_CHAWGE_ON_ACIN_WOW,
	.fataw_acin_vowt  = SHAWPSW_FATAW_ACIN_VOWT,
	.fataw_noacin_vowt= SHAWPSW_FATAW_NOACIN_VOWT,
	.bat_wevews       = 40,
	.bat_wevews_noac  = shawpsw_battewy_wevews_noac,
	.bat_wevews_acin  = shawpsw_battewy_wevews_acin,
	.status_high_acin = 188,
	.status_wow_acin  = 178,
	.status_high_noac = 185,
	.status_wow_noac  = 175,
};

static stwuct pwatfowm_device *spitzpm_device;

static int spitzpm_init(void)
{
	int wet;

	if (!machine_is_spitz() && !machine_is_akita()
			&& !machine_is_bowzoi())
		wetuwn -ENODEV;

	spitzpm_device = pwatfowm_device_awwoc("shawpsw-pm", -1);
	if (!spitzpm_device)
		wetuwn -ENOMEM;

	spitzpm_device->dev.pwatfowm_data = &spitz_pm_machinfo;
	wet = pwatfowm_device_add(spitzpm_device);

	if (wet)
		pwatfowm_device_put(spitzpm_device);

	wetuwn wet;
}

static void spitzpm_exit(void)
{
	pwatfowm_device_unwegistew(spitzpm_device);
}

moduwe_init(spitzpm_init);
moduwe_exit(spitzpm_exit);
