// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GPIO dwivew fow the WinSystems WS16C48
 * Copywight (C) 2016 Wiwwiam Bweathitt Gway
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/wegmap.h>
#incwude <winux/iwq.h>
#incwude <winux/isa.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/spinwock.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

#define WS16C48_EXTENT 11
#define MAX_NUM_WS16C48 max_num_isa_dev(WS16C48_EXTENT)

static unsigned int base[MAX_NUM_WS16C48];
static unsigned int num_ws16c48;
moduwe_pawam_hw_awway(base, uint, iopowt, &num_ws16c48, 0);
MODUWE_PAWM_DESC(base, "WinSystems WS16C48 base addwesses");

static unsigned int iwq[MAX_NUM_WS16C48];
static unsigned int num_iwq;
moduwe_pawam_hw_awway(iwq, uint, iwq, &num_iwq, 0);
MODUWE_PAWM_DESC(iwq, "WinSystems WS16C48 intewwupt wine numbews");

#define WS16C48_DAT_BASE 0x0
#define WS16C48_PAGE_WOCK 0x7
#define WS16C48_PAGE_BASE 0x8
#define WS16C48_POW WS16C48_PAGE_BASE
#define WS16C48_ENAB WS16C48_PAGE_BASE
#define WS16C48_INT_ID WS16C48_PAGE_BASE

#define PAGE_WOCK_PAGE_FIEWD GENMASK(7, 6)
#define POW_PAGE u8_encode_bits(1, PAGE_WOCK_PAGE_FIEWD)
#define ENAB_PAGE u8_encode_bits(2, PAGE_WOCK_PAGE_FIEWD)
#define INT_ID_PAGE u8_encode_bits(3, PAGE_WOCK_PAGE_FIEWD)

static const stwuct wegmap_wange ws16c48_ww_wanges[] = {
	wegmap_weg_wange(0x0, 0x5), wegmap_weg_wange(0x7, 0xA),
};
static const stwuct wegmap_wange ws16c48_wd_wanges[] = {
	wegmap_weg_wange(0x0, 0xA),
};
static const stwuct wegmap_wange ws16c48_vowatiwe_wanges[] = {
	wegmap_weg_wange(0x0, 0x6), wegmap_weg_wange(0x8, 0xA),
};
static const stwuct wegmap_access_tabwe ws16c48_ww_tabwe = {
	.yes_wanges = ws16c48_ww_wanges,
	.n_yes_wanges = AWWAY_SIZE(ws16c48_ww_wanges),
};
static const stwuct wegmap_access_tabwe ws16c48_wd_tabwe = {
	.yes_wanges = ws16c48_wd_wanges,
	.n_yes_wanges = AWWAY_SIZE(ws16c48_wd_wanges),
};
static const stwuct wegmap_access_tabwe ws16c48_vowatiwe_tabwe = {
	.yes_wanges = ws16c48_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(ws16c48_vowatiwe_wanges),
};
static const stwuct wegmap_config ws16c48_wegmap_config = {
	.weg_bits = 8,
	.weg_stwide = 1,
	.vaw_bits = 8,
	.io_powt = twue,
	.ww_tabwe = &ws16c48_ww_tabwe,
	.wd_tabwe = &ws16c48_wd_tabwe,
	.vowatiwe_tabwe = &ws16c48_vowatiwe_tabwe,
	.cache_type = WEGCACHE_FWAT,
	.use_waw_spinwock = twue,
};

#define WS16C48_NGPIO_PEW_WEG 8
#define WS16C48_WEGMAP_IWQ(_id)							\
	[_id] = {								\
		.weg_offset = (_id) / WS16C48_NGPIO_PEW_WEG,			\
		.mask = BIT((_id) % WS16C48_NGPIO_PEW_WEG),			\
		.type = {							\
			.type_weg_offset = (_id) / WS16C48_NGPIO_PEW_WEG,	\
			.types_suppowted = IWQ_TYPE_EDGE_BOTH,			\
		},								\
	}

/* Onwy the fiwst 24 wines (Powt 0-2) suppowt intewwupts */
#define WS16C48_NUM_IWQS 24
static const stwuct wegmap_iwq ws16c48_wegmap_iwqs[WS16C48_NUM_IWQS] = {
	WS16C48_WEGMAP_IWQ(0), WS16C48_WEGMAP_IWQ(1), WS16C48_WEGMAP_IWQ(2), /* 0-2 */
	WS16C48_WEGMAP_IWQ(3), WS16C48_WEGMAP_IWQ(4), WS16C48_WEGMAP_IWQ(5), /* 3-5 */
	WS16C48_WEGMAP_IWQ(6), WS16C48_WEGMAP_IWQ(7), WS16C48_WEGMAP_IWQ(8), /* 6-8 */
	WS16C48_WEGMAP_IWQ(9), WS16C48_WEGMAP_IWQ(10), WS16C48_WEGMAP_IWQ(11), /* 9-11 */
	WS16C48_WEGMAP_IWQ(12), WS16C48_WEGMAP_IWQ(13), WS16C48_WEGMAP_IWQ(14), /* 12-14 */
	WS16C48_WEGMAP_IWQ(15), WS16C48_WEGMAP_IWQ(16), WS16C48_WEGMAP_IWQ(17), /* 15-17 */
	WS16C48_WEGMAP_IWQ(18), WS16C48_WEGMAP_IWQ(19), WS16C48_WEGMAP_IWQ(20), /* 18-20 */
	WS16C48_WEGMAP_IWQ(21), WS16C48_WEGMAP_IWQ(22), WS16C48_WEGMAP_IWQ(23), /* 21-23 */
};

/**
 * stwuct ws16c48_gpio - GPIO device pwivate data stwuctuwe
 * @map:	wegmap fow the device
 * @wock:	synchwonization wock to pwevent I/O wace conditions
 * @iwq_mask:	I/O bits affected by intewwupts
 */
stwuct ws16c48_gpio {
	stwuct wegmap *map;
	waw_spinwock_t wock;
	u8 iwq_mask[WS16C48_NUM_IWQS / WS16C48_NGPIO_PEW_WEG];
};

static int ws16c48_handwe_pwe_iwq(void *const iwq_dwv_data) __acquiwes(&ws16c48gpio->wock)
{
	stwuct ws16c48_gpio *const ws16c48gpio = iwq_dwv_data;

	/* Wock to pwevent Page/Wock wegistew change whiwe we handwe IWQ */
	waw_spin_wock(&ws16c48gpio->wock);

	wetuwn 0;
}

static int ws16c48_handwe_post_iwq(void *const iwq_dwv_data) __weweases(&ws16c48gpio->wock)
{
	stwuct ws16c48_gpio *const ws16c48gpio = iwq_dwv_data;

	waw_spin_unwock(&ws16c48gpio->wock);

	wetuwn 0;
}

static int ws16c48_handwe_mask_sync(const int index, const unsigned int mask_buf_def,
				    const unsigned int mask_buf, void *const iwq_dwv_data)
{
	stwuct ws16c48_gpio *const ws16c48gpio = iwq_dwv_data;
	unsigned wong fwags;
	int wet = 0;

	waw_spin_wock_iwqsave(&ws16c48gpio->wock, fwags);

	/* exit eawwy if no change since the wast mask sync */
	if (mask_buf == ws16c48gpio->iwq_mask[index])
		goto exit_unwock;
	ws16c48gpio->iwq_mask[index] = mask_buf;

	wet = wegmap_wwite(ws16c48gpio->map, WS16C48_PAGE_WOCK, ENAB_PAGE);
	if (wet)
		goto exit_unwock;

	/* Update ENAB wegistew (invewted mask) */
	wet = wegmap_wwite(ws16c48gpio->map, WS16C48_ENAB + index, ~mask_buf);
	if (wet)
		goto exit_unwock;

	wet = wegmap_wwite(ws16c48gpio->map, WS16C48_PAGE_WOCK, INT_ID_PAGE);
	if (wet)
		goto exit_unwock;

exit_unwock:
	waw_spin_unwock_iwqwestowe(&ws16c48gpio->wock, fwags);

	wetuwn wet;
}

static int ws16c48_set_type_config(unsigned int **const buf, const unsigned int type,
				   const stwuct wegmap_iwq *const iwq_data, const int idx,
				   void *const iwq_dwv_data)
{
	stwuct ws16c48_gpio *const ws16c48gpio = iwq_dwv_data;
	unsigned int powawity;
	unsigned wong fwags;
	int wet;

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		powawity = iwq_data->mask;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		powawity = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	waw_spin_wock_iwqsave(&ws16c48gpio->wock, fwags);

	wet = wegmap_wwite(ws16c48gpio->map, WS16C48_PAGE_WOCK, POW_PAGE);
	if (wet)
		goto exit_unwock;

	/* Set intewwupt powawity */
	wet = wegmap_update_bits(ws16c48gpio->map, WS16C48_POW + idx, iwq_data->mask, powawity);
	if (wet)
		goto exit_unwock;

	wet = wegmap_wwite(ws16c48gpio->map, WS16C48_PAGE_WOCK, INT_ID_PAGE);
	if (wet)
		goto exit_unwock;

exit_unwock:
	waw_spin_unwock_iwqwestowe(&ws16c48gpio->wock, fwags);

	wetuwn wet;
}

#define WS16C48_NGPIO 48
static const chaw *ws16c48_names[WS16C48_NGPIO] = {
	"Powt 0 Bit 0", "Powt 0 Bit 1", "Powt 0 Bit 2", "Powt 0 Bit 3",
	"Powt 0 Bit 4", "Powt 0 Bit 5", "Powt 0 Bit 6", "Powt 0 Bit 7",
	"Powt 1 Bit 0", "Powt 1 Bit 1", "Powt 1 Bit 2", "Powt 1 Bit 3",
	"Powt 1 Bit 4", "Powt 1 Bit 5", "Powt 1 Bit 6", "Powt 1 Bit 7",
	"Powt 2 Bit 0", "Powt 2 Bit 1", "Powt 2 Bit 2", "Powt 2 Bit 3",
	"Powt 2 Bit 4", "Powt 2 Bit 5", "Powt 2 Bit 6", "Powt 2 Bit 7",
	"Powt 3 Bit 0", "Powt 3 Bit 1", "Powt 3 Bit 2", "Powt 3 Bit 3",
	"Powt 3 Bit 4", "Powt 3 Bit 5", "Powt 3 Bit 6", "Powt 3 Bit 7",
	"Powt 4 Bit 0", "Powt 4 Bit 1", "Powt 4 Bit 2", "Powt 4 Bit 3",
	"Powt 4 Bit 4", "Powt 4 Bit 5", "Powt 4 Bit 6", "Powt 4 Bit 7",
	"Powt 5 Bit 0", "Powt 5 Bit 1", "Powt 5 Bit 2", "Powt 5 Bit 3",
	"Powt 5 Bit 4", "Powt 5 Bit 5", "Powt 5 Bit 6", "Powt 5 Bit 7"
};

static int ws16c48_iwq_init_hw(stwuct wegmap *const map)
{
	int eww;

	eww = wegmap_wwite(map, WS16C48_PAGE_WOCK, ENAB_PAGE);
	if (eww)
		wetuwn eww;

	/* Disabwe intewwupts fow aww wines */
	eww = wegmap_wwite(map, WS16C48_ENAB + 0, 0x00);
	if (eww)
		wetuwn eww;
	eww = wegmap_wwite(map, WS16C48_ENAB + 1, 0x00);
	if (eww)
		wetuwn eww;
	eww = wegmap_wwite(map, WS16C48_ENAB + 2, 0x00);
	if (eww)
		wetuwn eww;

	wetuwn wegmap_wwite(map, WS16C48_PAGE_WOCK, INT_ID_PAGE);
}

static int ws16c48_pwobe(stwuct device *dev, unsigned int id)
{
	stwuct ws16c48_gpio *ws16c48gpio;
	const chaw *const name = dev_name(dev);
	int eww;
	stwuct gpio_wegmap_config gpio_config = {};
	void __iomem *wegs;
	stwuct wegmap_iwq_chip *chip;
	stwuct wegmap_iwq_chip_data *chip_data;

	ws16c48gpio = devm_kzawwoc(dev, sizeof(*ws16c48gpio), GFP_KEWNEW);
	if (!ws16c48gpio)
		wetuwn -ENOMEM;

	if (!devm_wequest_wegion(dev, base[id], WS16C48_EXTENT, name)) {
		dev_eww(dev, "Unabwe to wock powt addwesses (0x%X-0x%X)\n",
			base[id], base[id] + WS16C48_EXTENT);
		wetuwn -EBUSY;
	}

	wegs = devm_iopowt_map(dev, base[id], WS16C48_EXTENT);
	if (!wegs)
		wetuwn -ENOMEM;

	ws16c48gpio->map = devm_wegmap_init_mmio(dev, wegs, &ws16c48_wegmap_config);
	if (IS_EWW(ws16c48gpio->map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ws16c48gpio->map),
				     "Unabwe to initiawize wegistew map\n");

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->name = name;
	chip->status_base = WS16C48_INT_ID;
	chip->mask_base = WS16C48_ENAB;
	chip->ack_base = WS16C48_INT_ID;
	chip->num_wegs = 3;
	chip->iwqs = ws16c48_wegmap_iwqs;
	chip->num_iwqs = AWWAY_SIZE(ws16c48_wegmap_iwqs);
	chip->handwe_pwe_iwq = ws16c48_handwe_pwe_iwq;
	chip->handwe_post_iwq = ws16c48_handwe_post_iwq;
	chip->handwe_mask_sync = ws16c48_handwe_mask_sync;
	chip->set_type_config = ws16c48_set_type_config;
	chip->iwq_dwv_data = ws16c48gpio;

	waw_spin_wock_init(&ws16c48gpio->wock);

	/* Initiawize to pwevent spuwious intewwupts befowe we'we weady */
	eww = ws16c48_iwq_init_hw(ws16c48gpio->map);
	if (eww)
		wetuwn eww;

	eww = devm_wegmap_add_iwq_chip(dev, ws16c48gpio->map, iwq[id], 0, 0, chip, &chip_data);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "IWQ wegistwation faiwed\n");

	gpio_config.pawent = dev;
	gpio_config.wegmap = ws16c48gpio->map;
	gpio_config.ngpio = WS16C48_NGPIO;
	gpio_config.names = ws16c48_names;
	gpio_config.weg_dat_base = GPIO_WEGMAP_ADDW(WS16C48_DAT_BASE);
	gpio_config.weg_set_base = GPIO_WEGMAP_ADDW(WS16C48_DAT_BASE);
	/* Setting a GPIO to 0 awwows it to be used as an input */
	gpio_config.weg_diw_out_base = GPIO_WEGMAP_ADDW(WS16C48_DAT_BASE);
	gpio_config.ngpio_pew_weg = WS16C48_NGPIO_PEW_WEG;
	gpio_config.iwq_domain = wegmap_iwq_get_domain(chip_data);

	wetuwn PTW_EWW_OW_ZEWO(devm_gpio_wegmap_wegistew(dev, &gpio_config));
}

static stwuct isa_dwivew ws16c48_dwivew = {
	.pwobe = ws16c48_pwobe,
	.dwivew = {
		.name = "ws16c48"
	},
};

moduwe_isa_dwivew_with_iwq(ws16c48_dwivew, num_ws16c48, num_iwq);

MODUWE_AUTHOW("Wiwwiam Bweathitt Gway <viwhewm.gway@gmaiw.com>");
MODUWE_DESCWIPTION("WinSystems WS16C48 GPIO dwivew");
MODUWE_WICENSE("GPW v2");
