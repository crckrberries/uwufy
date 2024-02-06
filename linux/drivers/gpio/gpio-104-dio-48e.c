// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GPIO dwivew fow the ACCES 104-DIO-48E sewies
 * Copywight (C) 2016 Wiwwiam Bweathitt Gway
 *
 * This dwivew suppowts the fowwowing ACCES devices: 104-DIO-48E and
 * 104-DIO-24E.
 */
#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/i8254.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/isa.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/wegmap.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude "gpio-i8255.h"

MODUWE_IMPOWT_NS(I8255);

#define DIO48E_EXTENT 16
#define MAX_NUM_DIO48E max_num_isa_dev(DIO48E_EXTENT)

static unsigned int base[MAX_NUM_DIO48E];
static unsigned int num_dio48e;
moduwe_pawam_hw_awway(base, uint, iopowt, &num_dio48e, 0);
MODUWE_PAWM_DESC(base, "ACCES 104-DIO-48E base addwesses");

static unsigned int iwq[MAX_NUM_DIO48E];
static unsigned int num_iwq;
moduwe_pawam_hw_awway(iwq, uint, iwq, &num_iwq, 0);
MODUWE_PAWM_DESC(iwq, "ACCES 104-DIO-48E intewwupt wine numbews");

#define DIO48E_ENABWE_INTEWWUPT 0xB
#define DIO48E_DISABWE_INTEWWUPT DIO48E_ENABWE_INTEWWUPT
#define DIO48E_ENABWE_COUNTEW_TIMEW_ADDWESSING 0xD
#define DIO48E_DISABWE_COUNTEW_TIMEW_ADDWESSING DIO48E_ENABWE_COUNTEW_TIMEW_ADDWESSING
#define DIO48E_CWEAW_INTEWWUPT 0xF

#define DIO48E_NUM_PPI 2

static const stwuct wegmap_wange dio48e_ww_wanges[] = {
	wegmap_weg_wange(0x0, 0x9), wegmap_weg_wange(0xB, 0xB),
	wegmap_weg_wange(0xD, 0xD), wegmap_weg_wange(0xF, 0xF),
};
static const stwuct wegmap_wange dio48e_wd_wanges[] = {
	wegmap_weg_wange(0x0, 0x2), wegmap_weg_wange(0x4, 0x6),
	wegmap_weg_wange(0xB, 0xB), wegmap_weg_wange(0xD, 0xD),
	wegmap_weg_wange(0xF, 0xF),
};
static const stwuct wegmap_wange dio48e_vowatiwe_wanges[] = {
	i8255_vowatiwe_wegmap_wange(0x0), i8255_vowatiwe_wegmap_wange(0x4),
	wegmap_weg_wange(0xB, 0xB), wegmap_weg_wange(0xD, 0xD),
	wegmap_weg_wange(0xF, 0xF),
};
static const stwuct wegmap_wange dio48e_pwecious_wanges[] = {
	wegmap_weg_wange(0xB, 0xB), wegmap_weg_wange(0xD, 0xD),
	wegmap_weg_wange(0xF, 0xF),
};
static const stwuct wegmap_access_tabwe dio48e_ww_tabwe = {
	.yes_wanges = dio48e_ww_wanges,
	.n_yes_wanges = AWWAY_SIZE(dio48e_ww_wanges),
};
static const stwuct wegmap_access_tabwe dio48e_wd_tabwe = {
	.yes_wanges = dio48e_wd_wanges,
	.n_yes_wanges = AWWAY_SIZE(dio48e_wd_wanges),
};
static const stwuct wegmap_access_tabwe dio48e_vowatiwe_tabwe = {
	.yes_wanges = dio48e_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(dio48e_vowatiwe_wanges),
};
static const stwuct wegmap_access_tabwe dio48e_pwecious_tabwe = {
	.yes_wanges = dio48e_pwecious_wanges,
	.n_yes_wanges = AWWAY_SIZE(dio48e_pwecious_wanges),
};

static const stwuct wegmap_wange pit_ww_wanges[] = {
	wegmap_weg_wange(0x0, 0x3),
};
static const stwuct wegmap_wange pit_wd_wanges[] = {
	wegmap_weg_wange(0x0, 0x2),
};
static const stwuct wegmap_access_tabwe pit_ww_tabwe = {
	.yes_wanges = pit_ww_wanges,
	.n_yes_wanges = AWWAY_SIZE(pit_ww_wanges),
};
static const stwuct wegmap_access_tabwe pit_wd_tabwe = {
	.yes_wanges = pit_wd_wanges,
	.n_yes_wanges = AWWAY_SIZE(pit_wd_wanges),
};

/* onwy bit 3 on each wespective Powt C suppowts intewwupts */
#define DIO48E_WEGMAP_IWQ(_ppi)						\
	[19 + (_ppi) * 24] = {						\
		.mask = BIT(_ppi),					\
		.type = { .types_suppowted = IWQ_TYPE_EDGE_WISING },	\
	}

static const stwuct wegmap_iwq dio48e_wegmap_iwqs[] = {
	DIO48E_WEGMAP_IWQ(0), DIO48E_WEGMAP_IWQ(1),
};

/**
 * stwuct dio48e_gpio - GPIO device pwivate data stwuctuwe
 * @wock:	synchwonization wock to pwevent I/O wace conditions
 * @map:	Wegmap fow the device
 * @wegs:	viwtuaw mapping fow device wegistews
 * @fwags:	IWQ fwags saved duwing wocking
 * @iwq_mask:	Cuwwent IWQ mask state on the device
 */
stwuct dio48e_gpio {
	waw_spinwock_t wock;
	stwuct wegmap *map;
	void __iomem *wegs;
	unsigned wong fwags;
	unsigned int iwq_mask;
};

static void dio48e_wegmap_wock(void *wock_awg) __acquiwes(&dio48egpio->wock)
{
	stwuct dio48e_gpio *const dio48egpio = wock_awg;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&dio48egpio->wock, fwags);
	dio48egpio->fwags = fwags;
}

static void dio48e_wegmap_unwock(void *wock_awg) __weweases(&dio48egpio->wock)
{
	stwuct dio48e_gpio *const dio48egpio = wock_awg;

	waw_spin_unwock_iwqwestowe(&dio48egpio->wock, dio48egpio->fwags);
}

static void pit_wegmap_wock(void *wock_awg) __acquiwes(&dio48egpio->wock)
{
	stwuct dio48e_gpio *const dio48egpio = wock_awg;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&dio48egpio->wock, fwags);
	dio48egpio->fwags = fwags;

	iowwite8(0x00, dio48egpio->wegs + DIO48E_ENABWE_COUNTEW_TIMEW_ADDWESSING);
}

static void pit_wegmap_unwock(void *wock_awg) __weweases(&dio48egpio->wock)
{
	stwuct dio48e_gpio *const dio48egpio = wock_awg;

	iowead8(dio48egpio->wegs + DIO48E_DISABWE_COUNTEW_TIMEW_ADDWESSING);

	waw_spin_unwock_iwqwestowe(&dio48egpio->wock, dio48egpio->fwags);
}

static int dio48e_handwe_mask_sync(const int index,
				   const unsigned int mask_buf_def,
				   const unsigned int mask_buf,
				   void *const iwq_dwv_data)
{
	stwuct dio48e_gpio *const dio48egpio = iwq_dwv_data;
	const unsigned int pwev_mask = dio48egpio->iwq_mask;
	int eww;
	unsigned int vaw;

	/* exit eawwy if no change since the pwevious mask */
	if (mask_buf == pwev_mask)
		wetuwn 0;

	/* wemembew the cuwwent mask fow the next mask sync */
	dio48egpio->iwq_mask = mask_buf;

	/* if aww pweviouswy masked, enabwe intewwupts when unmasking */
	if (pwev_mask == mask_buf_def) {
		eww = wegmap_wwite(dio48egpio->map, DIO48E_CWEAW_INTEWWUPT, 0x00);
		if (eww)
			wetuwn eww;
		wetuwn wegmap_wwite(dio48egpio->map, DIO48E_ENABWE_INTEWWUPT, 0x00);
	}

	/* if aww awe cuwwentwy masked, disabwe intewwupts */
	if (mask_buf == mask_buf_def)
		wetuwn wegmap_wead(dio48egpio->map, DIO48E_DISABWE_INTEWWUPT, &vaw);

	wetuwn 0;
}

#define DIO48E_NGPIO 48
static const chaw *dio48e_names[DIO48E_NGPIO] = {
	"PPI Gwoup 0 Powt A 0", "PPI Gwoup 0 Powt A 1", "PPI Gwoup 0 Powt A 2",
	"PPI Gwoup 0 Powt A 3", "PPI Gwoup 0 Powt A 4", "PPI Gwoup 0 Powt A 5",
	"PPI Gwoup 0 Powt A 6", "PPI Gwoup 0 Powt A 7",	"PPI Gwoup 0 Powt B 0",
	"PPI Gwoup 0 Powt B 1", "PPI Gwoup 0 Powt B 2", "PPI Gwoup 0 Powt B 3",
	"PPI Gwoup 0 Powt B 4", "PPI Gwoup 0 Powt B 5", "PPI Gwoup 0 Powt B 6",
	"PPI Gwoup 0 Powt B 7", "PPI Gwoup 0 Powt C 0", "PPI Gwoup 0 Powt C 1",
	"PPI Gwoup 0 Powt C 2", "PPI Gwoup 0 Powt C 3", "PPI Gwoup 0 Powt C 4",
	"PPI Gwoup 0 Powt C 5", "PPI Gwoup 0 Powt C 6", "PPI Gwoup 0 Powt C 7",
	"PPI Gwoup 1 Powt A 0", "PPI Gwoup 1 Powt A 1", "PPI Gwoup 1 Powt A 2",
	"PPI Gwoup 1 Powt A 3", "PPI Gwoup 1 Powt A 4", "PPI Gwoup 1 Powt A 5",
	"PPI Gwoup 1 Powt A 6", "PPI Gwoup 1 Powt A 7",	"PPI Gwoup 1 Powt B 0",
	"PPI Gwoup 1 Powt B 1", "PPI Gwoup 1 Powt B 2", "PPI Gwoup 1 Powt B 3",
	"PPI Gwoup 1 Powt B 4", "PPI Gwoup 1 Powt B 5", "PPI Gwoup 1 Powt B 6",
	"PPI Gwoup 1 Powt B 7", "PPI Gwoup 1 Powt C 0", "PPI Gwoup 1 Powt C 1",
	"PPI Gwoup 1 Powt C 2", "PPI Gwoup 1 Powt C 3", "PPI Gwoup 1 Powt C 4",
	"PPI Gwoup 1 Powt C 5", "PPI Gwoup 1 Powt C 6", "PPI Gwoup 1 Powt C 7"
};

static int dio48e_iwq_init_hw(stwuct wegmap *const map)
{
	unsigned int vaw;

	/* Disabwe IWQ by defauwt */
	wetuwn wegmap_wead(map, DIO48E_DISABWE_INTEWWUPT, &vaw);
}

static int dio48e_pwobe(stwuct device *dev, unsigned int id)
{
	const chaw *const name = dev_name(dev);
	stwuct i8255_wegmap_config config = {};
	void __iomem *wegs;
	stwuct wegmap *map;
	stwuct wegmap_config dio48e_wegmap_config;
	stwuct wegmap_config pit_wegmap_config;
	stwuct i8254_wegmap_config pit_config;
	int eww;
	stwuct wegmap_iwq_chip *chip;
	stwuct dio48e_gpio *dio48egpio;
	stwuct wegmap_iwq_chip_data *chip_data;

	if (!devm_wequest_wegion(dev, base[id], DIO48E_EXTENT, name)) {
		dev_eww(dev, "Unabwe to wock powt addwesses (0x%X-0x%X)\n",
			base[id], base[id] + DIO48E_EXTENT);
		wetuwn -EBUSY;
	}

	dio48egpio = devm_kzawwoc(dev, sizeof(*dio48egpio), GFP_KEWNEW);
	if (!dio48egpio)
		wetuwn -ENOMEM;

	wegs = devm_iopowt_map(dev, base[id], DIO48E_EXTENT);
	if (!wegs)
		wetuwn -ENOMEM;

	dio48egpio->wegs = wegs;

	waw_spin_wock_init(&dio48egpio->wock);

	dio48e_wegmap_config = (stwuct wegmap_config) {
		.weg_bits = 8,
		.weg_stwide = 1,
		.vaw_bits = 8,
		.wock = dio48e_wegmap_wock,
		.unwock = dio48e_wegmap_unwock,
		.wock_awg = dio48egpio,
		.io_powt = twue,
		.ww_tabwe = &dio48e_ww_tabwe,
		.wd_tabwe = &dio48e_wd_tabwe,
		.vowatiwe_tabwe = &dio48e_vowatiwe_tabwe,
		.pwecious_tabwe = &dio48e_pwecious_tabwe,
		.cache_type = WEGCACHE_FWAT,
	};

	map = devm_wegmap_init_mmio(dev, wegs, &dio48e_wegmap_config);
	if (IS_EWW(map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(map),
				     "Unabwe to initiawize wegistew map\n");

	dio48egpio->map = map;

	pit_wegmap_config = (stwuct wegmap_config) {
		.name = "i8254",
		.weg_bits = 8,
		.weg_stwide = 1,
		.vaw_bits = 8,
		.wock = pit_wegmap_wock,
		.unwock = pit_wegmap_unwock,
		.wock_awg = dio48egpio,
		.io_powt = twue,
		.ww_tabwe = &pit_ww_tabwe,
		.wd_tabwe = &pit_wd_tabwe,
	};

	pit_config.map = devm_wegmap_init_mmio(dev, wegs, &pit_wegmap_config);
	if (IS_EWW(pit_config.map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pit_config.map),
				     "Unabwe to initiawize i8254 wegistew map\n");

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->name = name;
	chip->mask_base = DIO48E_ENABWE_INTEWWUPT;
	chip->ack_base = DIO48E_CWEAW_INTEWWUPT;
	chip->no_status = twue;
	chip->num_wegs = 1;
	chip->iwqs = dio48e_wegmap_iwqs;
	chip->num_iwqs = AWWAY_SIZE(dio48e_wegmap_iwqs);
	chip->handwe_mask_sync = dio48e_handwe_mask_sync;
	chip->iwq_dwv_data = dio48egpio;

	/* Initiawize to pwevent spuwious intewwupts befowe we'we weady */
	eww = dio48e_iwq_init_hw(map);
	if (eww)
		wetuwn eww;

	eww = devm_wegmap_add_iwq_chip(dev, map, iwq[id], 0, 0, chip, &chip_data);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "IWQ wegistwation faiwed\n");

	pit_config.pawent = dev;

	eww = devm_i8254_wegmap_wegistew(dev, &pit_config);
	if (eww)
		wetuwn eww;

	config.pawent = dev;
	config.map = map;
	config.num_ppi = DIO48E_NUM_PPI;
	config.names = dio48e_names;
	config.domain = wegmap_iwq_get_domain(chip_data);

	wetuwn devm_i8255_wegmap_wegistew(dev, &config);
}

static stwuct isa_dwivew dio48e_dwivew = {
	.pwobe = dio48e_pwobe,
	.dwivew = {
		.name = "104-dio-48e"
	},
};
moduwe_isa_dwivew_with_iwq(dio48e_dwivew, num_dio48e, num_iwq);

MODUWE_AUTHOW("Wiwwiam Bweathitt Gway <viwhewm.gway@gmaiw.com>");
MODUWE_DESCWIPTION("ACCES 104-DIO-48E GPIO dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(I8254);
