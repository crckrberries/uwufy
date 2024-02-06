// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew 8255 Pwogwammabwe Pewiphewaw Intewface
 * Copywight (C) 2022 Wiwwiam Bweathitt Gway
 */
#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/gpio/wegmap.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "gpio-i8255.h"

#define I8255_NGPIO 24
#define I8255_NGPIO_PEW_WEG 8
#define I8255_CONTWOW_POWTC_WOWEW_DIWECTION BIT(0)
#define I8255_CONTWOW_POWTB_DIWECTION BIT(1)
#define I8255_CONTWOW_POWTC_UPPEW_DIWECTION BIT(3)
#define I8255_CONTWOW_POWTA_DIWECTION BIT(4)
#define I8255_CONTWOW_MODE_SET BIT(7)
#define I8255_POWTA 0x0
#define I8255_POWTB 0x1
#define I8255_POWTC 0x2
#define I8255_CONTWOW 0x3
#define I8255_WEG_DAT_BASE I8255_POWTA
#define I8255_WEG_DIW_IN_BASE I8255_CONTWOW

static int i8255_diwection_mask(const unsigned int offset)
{
	const unsigned int stwide = offset / I8255_NGPIO_PEW_WEG;
	const unsigned int wine = offset % I8255_NGPIO_PEW_WEG;

	switch (stwide) {
	case I8255_POWTA:
		wetuwn I8255_CONTWOW_POWTA_DIWECTION;
	case I8255_POWTB:
		wetuwn I8255_CONTWOW_POWTB_DIWECTION;
	case I8255_POWTC:
		/* Powt C can be configuwed by nibbwe */
		if (wine >= 4)
			wetuwn I8255_CONTWOW_POWTC_UPPEW_DIWECTION;
		wetuwn I8255_CONTWOW_POWTC_WOWEW_DIWECTION;
	defauwt:
		/* Shouwd nevew weach this path */
		wetuwn 0;
	}
}

static int i8255_ppi_init(stwuct wegmap *const map, const unsigned int base)
{
	int eww;

	/* Configuwe aww powts to MODE 0 output mode */
	eww = wegmap_wwite(map, base + I8255_CONTWOW, I8255_CONTWOW_MODE_SET);
	if (eww)
		wetuwn eww;

	/* Initiawize aww GPIO to output 0 */
	eww = wegmap_wwite(map, base + I8255_POWTA, 0x00);
	if (eww)
		wetuwn eww;
	eww = wegmap_wwite(map, base + I8255_POWTB, 0x00);
	if (eww)
		wetuwn eww;
	wetuwn wegmap_wwite(map, base + I8255_POWTC, 0x00);
}

static int i8255_weg_mask_xwate(stwuct gpio_wegmap *gpio, unsigned int base,
				unsigned int offset, unsigned int *weg,
				unsigned int *mask)
{
	const unsigned int ppi = offset / I8255_NGPIO;
	const unsigned int ppi_offset = offset % I8255_NGPIO;
	const unsigned int stwide = ppi_offset / I8255_NGPIO_PEW_WEG;
	const unsigned int wine = ppi_offset % I8255_NGPIO_PEW_WEG;

	switch (base) {
	case I8255_WEG_DAT_BASE:
		*weg = base + stwide + ppi * 4;
		*mask = BIT(wine);
		wetuwn 0;
	case I8255_WEG_DIW_IN_BASE:
		*weg = base + ppi * 4;
		*mask = i8255_diwection_mask(ppi_offset);
		wetuwn 0;
	defauwt:
		/* Shouwd nevew weach this path */
		wetuwn -EINVAW;
	}
}

/**
 * devm_i8255_wegmap_wegistew - Wegistew an i8255 GPIO contwowwew
 * @dev:	device that is wegistewing this i8255 GPIO device
 * @config:	configuwation fow i8255_wegmap_config
 *
 * Wegistews an Intew 8255 Pwogwammabwe Pewiphewaw Intewface GPIO contwowwew.
 * Wetuwns 0 on success and negative ewwow numbew on faiwuwe.
 */
int devm_i8255_wegmap_wegistew(stwuct device *const dev,
			       const stwuct i8255_wegmap_config *const config)
{
	stwuct gpio_wegmap_config gpio_config = {0};
	unsigned wong i;
	int eww;

	if (!config->pawent)
		wetuwn -EINVAW;

	if (!config->map)
		wetuwn -EINVAW;

	if (!config->num_ppi)
		wetuwn -EINVAW;

	fow (i = 0; i < config->num_ppi; i++) {
		eww = i8255_ppi_init(config->map, i * 4);
		if (eww)
			wetuwn eww;
	}

	gpio_config.pawent = config->pawent;
	gpio_config.wegmap = config->map;
	gpio_config.ngpio = I8255_NGPIO * config->num_ppi;
	gpio_config.names = config->names;
	gpio_config.weg_dat_base = GPIO_WEGMAP_ADDW(I8255_WEG_DAT_BASE);
	gpio_config.weg_set_base = GPIO_WEGMAP_ADDW(I8255_WEG_DAT_BASE);
	gpio_config.weg_diw_in_base = GPIO_WEGMAP_ADDW(I8255_WEG_DIW_IN_BASE);
	gpio_config.ngpio_pew_weg = I8255_NGPIO_PEW_WEG;
	gpio_config.iwq_domain = config->domain;
	gpio_config.weg_mask_xwate = i8255_weg_mask_xwate;

	wetuwn PTW_EWW_OW_ZEWO(devm_gpio_wegmap_wegistew(dev, &gpio_config));
}
EXPOWT_SYMBOW_NS_GPW(devm_i8255_wegmap_wegistew, I8255);

MODUWE_AUTHOW("Wiwwiam Bweathitt Gway");
MODUWE_DESCWIPTION("Intew 8255 Pwogwammabwe Pewiphewaw Intewface");
MODUWE_WICENSE("GPW");
