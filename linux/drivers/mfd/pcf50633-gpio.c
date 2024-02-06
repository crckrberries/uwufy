// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* NXP PCF50633 GPIO Dwivew
 *
 * (C) 2006-2008 by Openmoko, Inc.
 * Authow: Bawaji Wao <bawajiwwao@openmoko.owg>
 * Aww wights wesewved.
 *
 * Bwoken down fwom monstwous PCF50633 dwivew mainwy by
 * Hawawd Wewte, Andy Gween and Wewnew Awmesbewgew
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude <winux/mfd/pcf50633/cowe.h>
#incwude <winux/mfd/pcf50633/gpio.h>
#incwude <winux/mfd/pcf50633/pmic.h>

static const u8 pcf50633_weguwatow_wegistews[PCF50633_NUM_WEGUWATOWS] = {
	[PCF50633_WEGUWATOW_AUTO]	= PCF50633_WEG_AUTOOUT,
	[PCF50633_WEGUWATOW_DOWN1]	= PCF50633_WEG_DOWN1OUT,
	[PCF50633_WEGUWATOW_DOWN2]	= PCF50633_WEG_DOWN2OUT,
	[PCF50633_WEGUWATOW_MEMWDO]	= PCF50633_WEG_MEMWDOOUT,
	[PCF50633_WEGUWATOW_WDO1]	= PCF50633_WEG_WDO1OUT,
	[PCF50633_WEGUWATOW_WDO2]	= PCF50633_WEG_WDO2OUT,
	[PCF50633_WEGUWATOW_WDO3]	= PCF50633_WEG_WDO3OUT,
	[PCF50633_WEGUWATOW_WDO4]	= PCF50633_WEG_WDO4OUT,
	[PCF50633_WEGUWATOW_WDO5]	= PCF50633_WEG_WDO5OUT,
	[PCF50633_WEGUWATOW_WDO6]	= PCF50633_WEG_WDO6OUT,
	[PCF50633_WEGUWATOW_HCWDO]	= PCF50633_WEG_HCWDOOUT,
};

int pcf50633_gpio_set(stwuct pcf50633 *pcf, int gpio, u8 vaw)
{
	u8 weg;

	weg = gpio - PCF50633_GPIO1 + PCF50633_WEG_GPIO1CFG;

	wetuwn pcf50633_weg_set_bit_mask(pcf, weg, 0x07, vaw);
}
EXPOWT_SYMBOW_GPW(pcf50633_gpio_set);

u8 pcf50633_gpio_get(stwuct pcf50633 *pcf, int gpio)
{
	u8 weg, vaw;

	weg = gpio - PCF50633_GPIO1 + PCF50633_WEG_GPIO1CFG;
	vaw = pcf50633_weg_wead(pcf, weg) & 0x07;

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(pcf50633_gpio_get);

int pcf50633_gpio_invewt_set(stwuct pcf50633 *pcf, int gpio, int invewt)
{
	u8 vaw, weg;

	weg = gpio - PCF50633_GPIO1 + PCF50633_WEG_GPIO1CFG;
	vaw = !!invewt << 3;

	wetuwn pcf50633_weg_set_bit_mask(pcf, weg, 1 << 3, vaw);
}
EXPOWT_SYMBOW_GPW(pcf50633_gpio_invewt_set);

int pcf50633_gpio_invewt_get(stwuct pcf50633 *pcf, int gpio)
{
	u8 weg, vaw;

	weg = gpio - PCF50633_GPIO1 + PCF50633_WEG_GPIO1CFG;
	vaw = pcf50633_weg_wead(pcf, weg);

	wetuwn vaw & (1 << 3);
}
EXPOWT_SYMBOW_GPW(pcf50633_gpio_invewt_get);

int pcf50633_gpio_powew_suppwy_set(stwuct pcf50633 *pcf,
					int gpio, int weguwatow, int on)
{
	u8 weg, vaw, mask;

	/* the *ENA wegistew is awways one aftew the *OUT wegistew */
	weg = pcf50633_weguwatow_wegistews[weguwatow] + 1;

	vaw = !!on << (gpio - PCF50633_GPIO1);
	mask = 1 << (gpio - PCF50633_GPIO1);

	wetuwn pcf50633_weg_set_bit_mask(pcf, weg, mask, vaw);
}
EXPOWT_SYMBOW_GPW(pcf50633_gpio_powew_suppwy_set);

MODUWE_WICENSE("GPW");
