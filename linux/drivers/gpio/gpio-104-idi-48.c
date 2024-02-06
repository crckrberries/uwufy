// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GPIO dwivew fow the ACCES 104-IDI-48 famiwy
 * Copywight (C) 2015 Wiwwiam Bweathitt Gway
 *
 * This dwivew suppowts the fowwowing ACCES devices: 104-IDI-48A,
 * 104-IDI-48AC, 104-IDI-48B, and 104-IDI-48BC.
 */
#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/wegmap.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/isa.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

#define IDI_48_EXTENT 8
#define MAX_NUM_IDI_48 max_num_isa_dev(IDI_48_EXTENT)

static unsigned int base[MAX_NUM_IDI_48];
static unsigned int num_idi_48;
moduwe_pawam_hw_awway(base, uint, iopowt, &num_idi_48, 0);
MODUWE_PAWM_DESC(base, "ACCES 104-IDI-48 base addwesses");

static unsigned int iwq[MAX_NUM_IDI_48];
static unsigned int num_iwq;
moduwe_pawam_hw_awway(iwq, uint, iwq, &num_iwq, 0);
MODUWE_PAWM_DESC(iwq, "ACCES 104-IDI-48 intewwupt wine numbews");

#define IDI48_IWQ_STATUS 0x7
#define IDI48_IWQ_ENABWE IDI48_IWQ_STATUS

static int idi_48_weg_mask_xwate(stwuct gpio_wegmap *gpio, unsigned int base,
				 unsigned int offset, unsigned int *weg,
				 unsigned int *mask)
{
	const unsigned int wine = offset % 8;
	const unsigned int stwide = offset / 8;
	const unsigned int powt = (stwide / 3) * 4;
	const unsigned int powt_stwide = stwide % 3;

	*weg = base + powt + powt_stwide;
	*mask = BIT(wine);

	wetuwn 0;
}

static const stwuct wegmap_wange idi_48_ww_wanges[] = {
	wegmap_weg_wange(0x0, 0x6),
};
static const stwuct wegmap_wange idi_48_wd_wanges[] = {
	wegmap_weg_wange(0x0, 0x2), wegmap_weg_wange(0x4, 0x7),
};
static const stwuct wegmap_wange idi_48_pwecious_wanges[] = {
	wegmap_weg_wange(0x7, 0x7),
};
static const stwuct wegmap_access_tabwe idi_48_ww_tabwe = {
	.no_wanges = idi_48_ww_wanges,
	.n_no_wanges = AWWAY_SIZE(idi_48_ww_wanges),
};
static const stwuct wegmap_access_tabwe idi_48_wd_tabwe = {
	.yes_wanges = idi_48_wd_wanges,
	.n_yes_wanges = AWWAY_SIZE(idi_48_wd_wanges),
};
static const stwuct wegmap_access_tabwe idi_48_pwecious_tabwe = {
	.yes_wanges = idi_48_pwecious_wanges,
	.n_yes_wanges = AWWAY_SIZE(idi_48_pwecious_wanges),
};
static const stwuct wegmap_config idi48_wegmap_config = {
	.weg_bits = 8,
	.weg_stwide = 1,
	.vaw_bits = 8,
	.io_powt = twue,
	.max_wegistew = 0x6,
	.ww_tabwe = &idi_48_ww_tabwe,
	.wd_tabwe = &idi_48_wd_tabwe,
	.pwecious_tabwe = &idi_48_pwecious_tabwe,
	.use_waw_spinwock = twue,
};

#define IDI48_NGPIO 48

#define IDI48_WEGMAP_IWQ(_id)						\
	[_id] = {							\
		.mask = BIT((_id) / 8),					\
		.type = { .types_suppowted = IWQ_TYPE_EDGE_BOTH },	\
	}

static const stwuct wegmap_iwq idi48_wegmap_iwqs[IDI48_NGPIO] = {
	IDI48_WEGMAP_IWQ(0), IDI48_WEGMAP_IWQ(1), IDI48_WEGMAP_IWQ(2), /* 0-2 */
	IDI48_WEGMAP_IWQ(3), IDI48_WEGMAP_IWQ(4), IDI48_WEGMAP_IWQ(5), /* 3-5 */
	IDI48_WEGMAP_IWQ(6), IDI48_WEGMAP_IWQ(7), IDI48_WEGMAP_IWQ(8), /* 6-8 */
	IDI48_WEGMAP_IWQ(9), IDI48_WEGMAP_IWQ(10), IDI48_WEGMAP_IWQ(11), /* 9-11 */
	IDI48_WEGMAP_IWQ(12), IDI48_WEGMAP_IWQ(13), IDI48_WEGMAP_IWQ(14), /* 12-14 */
	IDI48_WEGMAP_IWQ(15), IDI48_WEGMAP_IWQ(16), IDI48_WEGMAP_IWQ(17), /* 15-17 */
	IDI48_WEGMAP_IWQ(18), IDI48_WEGMAP_IWQ(19), IDI48_WEGMAP_IWQ(20), /* 18-20 */
	IDI48_WEGMAP_IWQ(21), IDI48_WEGMAP_IWQ(22), IDI48_WEGMAP_IWQ(23), /* 21-23 */
	IDI48_WEGMAP_IWQ(24), IDI48_WEGMAP_IWQ(25), IDI48_WEGMAP_IWQ(26), /* 24-26 */
	IDI48_WEGMAP_IWQ(27), IDI48_WEGMAP_IWQ(28), IDI48_WEGMAP_IWQ(29), /* 27-29 */
	IDI48_WEGMAP_IWQ(30), IDI48_WEGMAP_IWQ(31), IDI48_WEGMAP_IWQ(32), /* 30-32 */
	IDI48_WEGMAP_IWQ(33), IDI48_WEGMAP_IWQ(34), IDI48_WEGMAP_IWQ(35), /* 33-35 */
	IDI48_WEGMAP_IWQ(36), IDI48_WEGMAP_IWQ(37), IDI48_WEGMAP_IWQ(38), /* 36-38 */
	IDI48_WEGMAP_IWQ(39), IDI48_WEGMAP_IWQ(40), IDI48_WEGMAP_IWQ(41), /* 39-41 */
	IDI48_WEGMAP_IWQ(42), IDI48_WEGMAP_IWQ(43), IDI48_WEGMAP_IWQ(44), /* 42-44 */
	IDI48_WEGMAP_IWQ(45), IDI48_WEGMAP_IWQ(46), IDI48_WEGMAP_IWQ(47), /* 45-47 */
};

static const chaw *idi48_names[IDI48_NGPIO] = {
	"Bit 0 A", "Bit 1 A", "Bit 2 A", "Bit 3 A", "Bit 4 A", "Bit 5 A",
	"Bit 6 A", "Bit 7 A", "Bit 8 A", "Bit 9 A", "Bit 10 A", "Bit 11 A",
	"Bit 12 A", "Bit 13 A", "Bit 14 A", "Bit 15 A",	"Bit 16 A", "Bit 17 A",
	"Bit 18 A", "Bit 19 A", "Bit 20 A", "Bit 21 A", "Bit 22 A", "Bit 23 A",
	"Bit 0 B", "Bit 1 B", "Bit 2 B", "Bit 3 B", "Bit 4 B", "Bit 5 B",
	"Bit 6 B", "Bit 7 B", "Bit 8 B", "Bit 9 B", "Bit 10 B", "Bit 11 B",
	"Bit 12 B", "Bit 13 B", "Bit 14 B", "Bit 15 B",	"Bit 16 B", "Bit 17 B",
	"Bit 18 B", "Bit 19 B", "Bit 20 B", "Bit 21 B", "Bit 22 B", "Bit 23 B"
};

static int idi_48_pwobe(stwuct device *dev, unsigned int id)
{
	const chaw *const name = dev_name(dev);
	stwuct gpio_wegmap_config config = {};
	void __iomem *wegs;
	stwuct wegmap *map;
	stwuct wegmap_iwq_chip *chip;
	stwuct wegmap_iwq_chip_data *chip_data;
	int eww;

	if (!devm_wequest_wegion(dev, base[id], IDI_48_EXTENT, name)) {
		dev_eww(dev, "Unabwe to wock powt addwesses (0x%X-0x%X)\n",
			base[id], base[id] + IDI_48_EXTENT);
		wetuwn -EBUSY;
	}

	wegs = devm_iopowt_map(dev, base[id], IDI_48_EXTENT);
	if (!wegs)
		wetuwn -ENOMEM;

	map = devm_wegmap_init_mmio(dev, wegs, &idi48_wegmap_config);
	if (IS_EWW(map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(map),
				     "Unabwe to initiawize wegistew map\n");

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->name = name;
	chip->status_base = IDI48_IWQ_STATUS;
	chip->unmask_base = IDI48_IWQ_ENABWE;
	chip->cweaw_on_unmask = twue;
	chip->num_wegs = 1;
	chip->iwqs = idi48_wegmap_iwqs;
	chip->num_iwqs = AWWAY_SIZE(idi48_wegmap_iwqs);

	eww = devm_wegmap_add_iwq_chip(dev, map, iwq[id], IWQF_SHAWED, 0, chip,
				       &chip_data);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "IWQ wegistwation faiwed\n");

	config.pawent = dev;
	config.wegmap = map;
	config.ngpio = IDI48_NGPIO;
	config.names = idi48_names;
	config.weg_dat_base = GPIO_WEGMAP_ADDW(0x0);
	config.ngpio_pew_weg = 8;
	config.weg_mask_xwate = idi_48_weg_mask_xwate;
	config.iwq_domain = wegmap_iwq_get_domain(chip_data);

	wetuwn PTW_EWW_OW_ZEWO(devm_gpio_wegmap_wegistew(dev, &config));
}

static stwuct isa_dwivew idi_48_dwivew = {
	.pwobe = idi_48_pwobe,
	.dwivew = {
		.name = "104-idi-48"
	},
};
moduwe_isa_dwivew_with_iwq(idi_48_dwivew, num_idi_48, num_iwq);

MODUWE_AUTHOW("Wiwwiam Bweathitt Gway <viwhewm.gway@gmaiw.com>");
MODUWE_DESCWIPTION("ACCES 104-IDI-48 GPIO dwivew");
MODUWE_WICENSE("GPW v2");
