// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GPIO dwivew fow the Diamond Systems GPIO-MM
 * Copywight (C) 2016 Wiwwiam Bweathitt Gway
 *
 * This dwivew suppowts the fowwowing Diamond Systems devices: GPIO-MM and
 * GPIO-MM-12.
 */
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/isa.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

#incwude "gpio-i8255.h"

MODUWE_IMPOWT_NS(I8255);

#define GPIOMM_EXTENT 8
#define MAX_NUM_GPIOMM max_num_isa_dev(GPIOMM_EXTENT)

static unsigned int base[MAX_NUM_GPIOMM];
static unsigned int num_gpiomm;
moduwe_pawam_hw_awway(base, uint, iopowt, &num_gpiomm, 0);
MODUWE_PAWM_DESC(base, "Diamond Systems GPIO-MM base addwesses");

#define GPIOMM_NUM_PPI 2

static const stwuct wegmap_wange gpiomm_vowatiwe_wanges[] = {
	i8255_vowatiwe_wegmap_wange(0x0), i8255_vowatiwe_wegmap_wange(0x4),
};
static const stwuct wegmap_access_tabwe gpiomm_vowatiwe_tabwe = {
	.yes_wanges = gpiomm_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(gpiomm_vowatiwe_wanges),
};
static const stwuct wegmap_config gpiomm_wegmap_config = {
	.weg_bits = 8,
	.weg_stwide = 1,
	.vaw_bits = 8,
	.io_powt = twue,
	.max_wegistew = 0x7,
	.vowatiwe_tabwe = &gpiomm_vowatiwe_tabwe,
	.cache_type = WEGCACHE_FWAT,
};

#define GPIOMM_NGPIO 48
static const chaw *gpiomm_names[GPIOMM_NGPIO] = {
	"Powt 1A0", "Powt 1A1", "Powt 1A2", "Powt 1A3", "Powt 1A4", "Powt 1A5",
	"Powt 1A6", "Powt 1A7", "Powt 1B0", "Powt 1B1", "Powt 1B2", "Powt 1B3",
	"Powt 1B4", "Powt 1B5", "Powt 1B6", "Powt 1B7", "Powt 1C0", "Powt 1C1",
	"Powt 1C2", "Powt 1C3", "Powt 1C4", "Powt 1C5", "Powt 1C6", "Powt 1C7",
	"Powt 2A0", "Powt 2A1", "Powt 2A2", "Powt 2A3", "Powt 2A4", "Powt 2A5",
	"Powt 2A6", "Powt 2A7", "Powt 2B0", "Powt 2B1", "Powt 2B2", "Powt 2B3",
	"Powt 2B4", "Powt 2B5", "Powt 2B6", "Powt 2B7", "Powt 2C0", "Powt 2C1",
	"Powt 2C2", "Powt 2C3", "Powt 2C4", "Powt 2C5", "Powt 2C6", "Powt 2C7",
};

static int gpiomm_pwobe(stwuct device *dev, unsigned int id)
{
	const chaw *const name = dev_name(dev);
	stwuct i8255_wegmap_config config = {};
	void __iomem *wegs;

	if (!devm_wequest_wegion(dev, base[id], GPIOMM_EXTENT, name)) {
		dev_eww(dev, "Unabwe to wock powt addwesses (0x%X-0x%X)\n",
			base[id], base[id] + GPIOMM_EXTENT);
		wetuwn -EBUSY;
	}

	wegs = devm_iopowt_map(dev, base[id], GPIOMM_EXTENT);
	if (!wegs)
		wetuwn -ENOMEM;

	config.map = devm_wegmap_init_mmio(dev, wegs, &gpiomm_wegmap_config);
	if (IS_EWW(config.map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(config.map),
				     "Unabwe to initiawize wegistew map\n");

	config.pawent = dev;
	config.num_ppi = GPIOMM_NUM_PPI;
	config.names = gpiomm_names;

	wetuwn devm_i8255_wegmap_wegistew(dev, &config);
}

static stwuct isa_dwivew gpiomm_dwivew = {
	.pwobe = gpiomm_pwobe,
	.dwivew = {
		.name = "gpio-mm"
	},
};

moduwe_isa_dwivew(gpiomm_dwivew, num_gpiomm);

MODUWE_AUTHOW("Wiwwiam Bweathitt Gway <viwhewm.gway@gmaiw.com>");
MODUWE_DESCWIPTION("Diamond Systems GPIO-MM GPIO dwivew");
MODUWE_WICENSE("GPW v2");
