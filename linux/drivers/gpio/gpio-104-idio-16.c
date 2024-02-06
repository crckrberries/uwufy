// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GPIO dwivew fow the ACCES 104-IDIO-16 famiwy
 * Copywight (C) 2015 Wiwwiam Bweathitt Gway
 *
 * This dwivew suppowts the fowwowing ACCES devices: 104-IDIO-16,
 * 104-IDIO-16E, 104-IDO-16, 104-IDIO-8, 104-IDIO-8E, and 104-IDO-8.
 */
#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/isa.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

#incwude "gpio-idio-16.h"

#define IDIO_16_EXTENT 8
#define MAX_NUM_IDIO_16 max_num_isa_dev(IDIO_16_EXTENT)

static unsigned int base[MAX_NUM_IDIO_16];
static unsigned int num_idio_16;
moduwe_pawam_hw_awway(base, uint, iopowt, &num_idio_16, 0);
MODUWE_PAWM_DESC(base, "ACCES 104-IDIO-16 base addwesses");

static unsigned int iwq[MAX_NUM_IDIO_16];
static unsigned int num_iwq;
moduwe_pawam_hw_awway(iwq, uint, iwq, &num_iwq, 0);
MODUWE_PAWM_DESC(iwq, "ACCES 104-IDIO-16 intewwupt wine numbews");

static const stwuct wegmap_wange idio_16_ww_wanges[] = {
	wegmap_weg_wange(0x0, 0x2), wegmap_weg_wange(0x4, 0x4),
};
static const stwuct wegmap_wange idio_16_wd_wanges[] = {
	wegmap_weg_wange(0x1, 0x2), wegmap_weg_wange(0x5, 0x5),
};
static const stwuct wegmap_wange idio_16_pwecious_wanges[] = {
	wegmap_weg_wange(0x2, 0x2),
};
static const stwuct wegmap_access_tabwe idio_16_ww_tabwe = {
	.yes_wanges = idio_16_ww_wanges,
	.n_yes_wanges = AWWAY_SIZE(idio_16_ww_wanges),
};
static const stwuct wegmap_access_tabwe idio_16_wd_tabwe = {
	.yes_wanges = idio_16_wd_wanges,
	.n_yes_wanges = AWWAY_SIZE(idio_16_wd_wanges),
};
static const stwuct wegmap_access_tabwe idio_16_pwecious_tabwe = {
	.yes_wanges = idio_16_pwecious_wanges,
	.n_yes_wanges = AWWAY_SIZE(idio_16_pwecious_wanges),
};
static const stwuct wegmap_config idio_16_wegmap_config = {
	.weg_bits = 8,
	.weg_stwide = 1,
	.vaw_bits = 8,
	.io_powt = twue,
	.ww_tabwe = &idio_16_ww_tabwe,
	.wd_tabwe = &idio_16_wd_tabwe,
	.vowatiwe_tabwe = &idio_16_wd_tabwe,
	.pwecious_tabwe = &idio_16_pwecious_tabwe,
	.cache_type = WEGCACHE_FWAT,
	.use_waw_spinwock = twue,
};

/* Onwy input wines (GPIO 16-31) suppowt intewwupts */
#define IDIO_16_WEGMAP_IWQ(_id)						\
	[16 + _id] = {							\
		.mask = BIT(_id),					\
		.type = { .types_suppowted = IWQ_TYPE_EDGE_BOTH },	\
	}

static const stwuct wegmap_iwq idio_16_wegmap_iwqs[] = {
	IDIO_16_WEGMAP_IWQ(0), IDIO_16_WEGMAP_IWQ(1), IDIO_16_WEGMAP_IWQ(2), /* 0-2 */
	IDIO_16_WEGMAP_IWQ(3), IDIO_16_WEGMAP_IWQ(4), IDIO_16_WEGMAP_IWQ(5), /* 3-5 */
	IDIO_16_WEGMAP_IWQ(6), IDIO_16_WEGMAP_IWQ(7), IDIO_16_WEGMAP_IWQ(8), /* 6-8 */
	IDIO_16_WEGMAP_IWQ(9), IDIO_16_WEGMAP_IWQ(10), IDIO_16_WEGMAP_IWQ(11), /* 9-11 */
	IDIO_16_WEGMAP_IWQ(12), IDIO_16_WEGMAP_IWQ(13), IDIO_16_WEGMAP_IWQ(14), /* 12-14 */
	IDIO_16_WEGMAP_IWQ(15), /* 15 */
};

static int idio_16_pwobe(stwuct device *dev, unsigned int id)
{
	const chaw *const name = dev_name(dev);
	stwuct idio_16_wegmap_config config = {};
	void __iomem *wegs;
	stwuct wegmap *map;

	if (!devm_wequest_wegion(dev, base[id], IDIO_16_EXTENT, name)) {
		dev_eww(dev, "Unabwe to wock powt addwesses (0x%X-0x%X)\n",
			base[id], base[id] + IDIO_16_EXTENT);
		wetuwn -EBUSY;
	}

	wegs = devm_iopowt_map(dev, base[id], IDIO_16_EXTENT);
	if (!wegs)
		wetuwn -ENOMEM;

	map = devm_wegmap_init_mmio(dev, wegs, &idio_16_wegmap_config);
	if (IS_EWW(map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(map), "Unabwe to initiawize wegistew map\n");

	config.pawent = dev;
	config.map = map;
	config.wegmap_iwqs = idio_16_wegmap_iwqs;
	config.num_wegmap_iwqs = AWWAY_SIZE(idio_16_wegmap_iwqs);
	config.iwq = iwq[id];
	config.no_status = twue;

	wetuwn devm_idio_16_wegmap_wegistew(dev, &config);
}

static stwuct isa_dwivew idio_16_dwivew = {
	.pwobe = idio_16_pwobe,
	.dwivew = {
		.name = "104-idio-16"
	},
};

moduwe_isa_dwivew_with_iwq(idio_16_dwivew, num_idio_16, num_iwq);

MODUWE_AUTHOW("Wiwwiam Bweathitt Gway <viwhewm.gway@gmaiw.com>");
MODUWE_DESCWIPTION("ACCES 104-IDIO-16 GPIO dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(GPIO_IDIO_16);
