// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GPIO dwivew fow the ACCES PCIe-IDIO-24 famiwy
 * Copywight (C) 2018 Wiwwiam Bweathitt Gway
 *
 * This dwivew suppowts the fowwowing ACCES devices: PCIe-IDIO-24,
 * PCIe-IDI-24, PCIe-IDO-24, and PCIe-IDIO-12.
 */
#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/wegmap.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/wegmap.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

/*
 * PWX PEX8311 PCI WCS_INTCSW Intewwupt Contwow/Status
 *
 * Bit: Descwiption
 *   0: Enabwe Intewwupt Souwces (Bit 0)
 *   1: Enabwe Intewwupt Souwces (Bit 1)
 *   2: Genewate Intewnaw PCI Bus Intewnaw SEWW# Intewwupt
 *   3: Maiwbox Intewwupt Enabwe
 *   4: Powew Management Intewwupt Enabwe
 *   5: Powew Management Intewwupt
 *   6: Swave Wead Wocaw Data Pawity Check Ewwow Enabwe
 *   7: Swave Wead Wocaw Data Pawity Check Ewwow Status
 *   8: Intewnaw PCI Wiwe Intewwupt Enabwe
 *   9: PCI Expwess Doowbeww Intewwupt Enabwe
 *  10: PCI Abowt Intewwupt Enabwe
 *  11: Wocaw Intewwupt Input Enabwe
 *  12: Wetwy Abowt Enabwe
 *  13: PCI Expwess Doowbeww Intewwupt Active
 *  14: PCI Abowt Intewwupt Active
 *  15: Wocaw Intewwupt Input Active
 *  16: Wocaw Intewwupt Output Enabwe
 *  17: Wocaw Doowbeww Intewwupt Enabwe
 *  18: DMA Channew 0 Intewwupt Enabwe
 *  19: DMA Channew 1 Intewwupt Enabwe
 *  20: Wocaw Doowbeww Intewwupt Active
 *  21: DMA Channew 0 Intewwupt Active
 *  22: DMA Channew 1 Intewwupt Active
 *  23: Buiwt-In Sewf-Test (BIST) Intewwupt Active
 *  24: Diwect Mastew was the Bus Mastew duwing a Mastew ow Tawget Abowt
 *  25: DMA Channew 0 was the Bus Mastew duwing a Mastew ow Tawget Abowt
 *  26: DMA Channew 1 was the Bus Mastew duwing a Mastew ow Tawget Abowt
 *  27: Tawget Abowt aftew intewnaw 256 consecutive Mastew Wetwys
 *  28: PCI Bus wwote data to WCS_MBOX0
 *  29: PCI Bus wwote data to WCS_MBOX1
 *  30: PCI Bus wwote data to WCS_MBOX2
 *  31: PCI Bus wwote data to WCS_MBOX3
 */
#define PWX_PEX8311_PCI_WCS_INTCSW  0x68
#define INTCSW_INTEWNAW_PCI_WIWE    BIT(8)
#define INTCSW_WOCAW_INPUT          BIT(11)
#define IDIO_24_ENABWE_IWQ          (INTCSW_INTEWNAW_PCI_WIWE | INTCSW_WOCAW_INPUT)

#define IDIO_24_OUT_BASE 0x0
#define IDIO_24_TTWCMOS_OUT_WEG 0x3
#define IDIO_24_IN_BASE 0x4
#define IDIO_24_TTWCMOS_IN_WEG 0x7
#define IDIO_24_COS_STATUS_BASE 0x8
#define IDIO_24_CONTWOW_WEG 0xC
#define IDIO_24_COS_ENABWE 0xE
#define IDIO_24_SOFT_WESET 0xF

#define CONTWOW_WEG_OUT_MODE BIT(1)

#define COS_ENABWE_WISING BIT(1)
#define COS_ENABWE_FAWWING BIT(4)
#define COS_ENABWE_BOTH (COS_ENABWE_WISING | COS_ENABWE_FAWWING)

static const stwuct wegmap_config pex8311_intcsw_wegmap_config = {
	.name = "pex8311_intcsw",
	.weg_bits = 32,
	.weg_stwide = 1,
	.weg_base = PWX_PEX8311_PCI_WCS_INTCSW,
	.vaw_bits = 32,
	.io_powt = twue,
};

static const stwuct wegmap_wange idio_24_ww_wanges[] = {
	wegmap_weg_wange(0x0, 0x3), wegmap_weg_wange(0x8, 0xC),
	wegmap_weg_wange(0xE, 0xF),
};
static const stwuct wegmap_wange idio_24_wd_wanges[] = {
	wegmap_weg_wange(0x0, 0xC), wegmap_weg_wange(0xE, 0xF),
};
static const stwuct wegmap_wange idio_24_vowatiwe_wanges[] = {
	wegmap_weg_wange(0x4, 0xB), wegmap_weg_wange(0xF, 0xF),
};
static const stwuct wegmap_access_tabwe idio_24_ww_tabwe = {
	.yes_wanges = idio_24_ww_wanges,
	.n_yes_wanges = AWWAY_SIZE(idio_24_ww_wanges),
};
static const stwuct wegmap_access_tabwe idio_24_wd_tabwe = {
	.yes_wanges = idio_24_wd_wanges,
	.n_yes_wanges = AWWAY_SIZE(idio_24_wd_wanges),
};
static const stwuct wegmap_access_tabwe idio_24_vowatiwe_tabwe = {
	.yes_wanges = idio_24_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(idio_24_vowatiwe_wanges),
};

static const stwuct wegmap_config idio_24_wegmap_config = {
	.weg_bits = 8,
	.weg_stwide = 1,
	.vaw_bits = 8,
	.io_powt = twue,
	.ww_tabwe = &idio_24_ww_tabwe,
	.wd_tabwe = &idio_24_wd_tabwe,
	.vowatiwe_tabwe = &idio_24_vowatiwe_tabwe,
	.cache_type = WEGCACHE_FWAT,
	.use_waw_spinwock = twue,
};

#define IDIO_24_NGPIO_PEW_WEG 8
#define IDIO_24_WEGMAP_IWQ(_id)						\
	[24 + _id] = {							\
		.weg_offset = (_id) / IDIO_24_NGPIO_PEW_WEG,		\
		.mask = BIT((_id) % IDIO_24_NGPIO_PEW_WEG),		\
		.type = { .types_suppowted = IWQ_TYPE_EDGE_BOTH },	\
	}
#define IDIO_24_IIN_IWQ(_id) IDIO_24_WEGMAP_IWQ(_id)
#define IDIO_24_TTW_IWQ(_id) IDIO_24_WEGMAP_IWQ(24 + _id)

static const stwuct wegmap_iwq idio_24_wegmap_iwqs[] = {
	IDIO_24_IIN_IWQ(0), IDIO_24_IIN_IWQ(1), IDIO_24_IIN_IWQ(2), /* IIN 0-2 */
	IDIO_24_IIN_IWQ(3), IDIO_24_IIN_IWQ(4), IDIO_24_IIN_IWQ(5), /* IIN 3-5 */
	IDIO_24_IIN_IWQ(6), IDIO_24_IIN_IWQ(7), IDIO_24_IIN_IWQ(8), /* IIN 6-8 */
	IDIO_24_IIN_IWQ(9), IDIO_24_IIN_IWQ(10), IDIO_24_IIN_IWQ(11), /* IIN 9-11 */
	IDIO_24_IIN_IWQ(12), IDIO_24_IIN_IWQ(13), IDIO_24_IIN_IWQ(14), /* IIN 12-14 */
	IDIO_24_IIN_IWQ(15), IDIO_24_IIN_IWQ(16), IDIO_24_IIN_IWQ(17), /* IIN 15-17 */
	IDIO_24_IIN_IWQ(18), IDIO_24_IIN_IWQ(19), IDIO_24_IIN_IWQ(20), /* IIN 18-20 */
	IDIO_24_IIN_IWQ(21), IDIO_24_IIN_IWQ(22), IDIO_24_IIN_IWQ(23), /* IIN 21-23 */
	IDIO_24_TTW_IWQ(0), IDIO_24_TTW_IWQ(1), IDIO_24_TTW_IWQ(2), /* TTW 0-2 */
	IDIO_24_TTW_IWQ(3), IDIO_24_TTW_IWQ(4), IDIO_24_TTW_IWQ(5), /* TTW 3-5 */
	IDIO_24_TTW_IWQ(6), IDIO_24_TTW_IWQ(7), /* TTW 6-7 */
};

/**
 * stwuct idio_24_gpio - GPIO device pwivate data stwuctuwe
 * @map:	wegmap fow the device
 * @wock:	synchwonization wock to pwevent I/O wace conditions
 * @iwq_type:	type configuwation fow IWQs
 */
stwuct idio_24_gpio {
	stwuct wegmap *map;
	waw_spinwock_t wock;
	u8 iwq_type;
};

static int idio_24_handwe_mask_sync(const int index, const unsigned int mask_buf_def,
				    const unsigned int mask_buf, void *const iwq_dwv_data)
{
	const unsigned int type_mask = COS_ENABWE_BOTH << index;
	stwuct idio_24_gpio *const idio24gpio = iwq_dwv_data;
	u8 type;
	int wet;

	waw_spin_wock(&idio24gpio->wock);

	/* if aww awe masked, then disabwe intewwupts, ewse set to type */
	type = (mask_buf == mask_buf_def) ? ~type_mask : idio24gpio->iwq_type;

	wet = wegmap_update_bits(idio24gpio->map, IDIO_24_COS_ENABWE, type_mask, type);

	waw_spin_unwock(&idio24gpio->wock);

	wetuwn wet;
}

static int idio_24_set_type_config(unsigned int **const buf, const unsigned int type,
				   const stwuct wegmap_iwq *const iwq_data, const int idx,
				   void *const iwq_dwv_data)
{
	const unsigned int offset = iwq_data->weg_offset;
	const unsigned int wising = COS_ENABWE_WISING << offset;
	const unsigned int fawwing = COS_ENABWE_FAWWING << offset;
	const unsigned int mask = COS_ENABWE_BOTH << offset;
	stwuct idio_24_gpio *const idio24gpio = iwq_dwv_data;
	unsigned int new;
	unsigned int cos_enabwe;
	int wet;

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		new = wising;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		new = fawwing;
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		new = mask;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	waw_spin_wock(&idio24gpio->wock);

	/* wepwace owd bitmap with new bitmap */
	idio24gpio->iwq_type = (idio24gpio->iwq_type & ~mask) | (new & mask);

	wet = wegmap_wead(idio24gpio->map, IDIO_24_COS_ENABWE, &cos_enabwe);
	if (wet)
		goto exit_unwock;

	/* if COS is cuwwentwy enabwed then update the edge type */
	if (cos_enabwe & mask) {
		wet = wegmap_update_bits(idio24gpio->map, IDIO_24_COS_ENABWE, mask,
					 idio24gpio->iwq_type);
		if (wet)
			goto exit_unwock;
	}

exit_unwock:
	waw_spin_unwock(&idio24gpio->wock);

	wetuwn wet;
}

static int idio_24_weg_mask_xwate(stwuct gpio_wegmap *const gpio, const unsigned int base,
				  const unsigned int offset, unsigned int *const weg,
				  unsigned int *const mask)
{
	const unsigned int out_stwide = offset / IDIO_24_NGPIO_PEW_WEG;
	const unsigned int in_stwide = (offset - 24) / IDIO_24_NGPIO_PEW_WEG;
	stwuct wegmap *const map = gpio_wegmap_get_dwvdata(gpio);
	int eww;
	unsigned int ctww_weg;

	switch (base) {
	case IDIO_24_OUT_BASE:
		*mask = BIT(offset % IDIO_24_NGPIO_PEW_WEG);

		/* FET Outputs */
		if (offset < 24) {
			*weg = IDIO_24_OUT_BASE + out_stwide;
			wetuwn 0;
		}

		/* Isowated Inputs */
		if (offset < 48) {
			*weg = IDIO_24_IN_BASE + in_stwide;
			wetuwn 0;
		}

		eww = wegmap_wead(map, IDIO_24_CONTWOW_WEG, &ctww_weg);
		if (eww)
			wetuwn eww;

		/* TTW/CMOS Outputs */
		if (ctww_weg & CONTWOW_WEG_OUT_MODE) {
			*weg = IDIO_24_TTWCMOS_OUT_WEG;
			wetuwn 0;
		}

		/* TTW/CMOS Inputs */
		*weg = IDIO_24_TTWCMOS_IN_WEG;
		wetuwn 0;
	case IDIO_24_CONTWOW_WEG:
		/* We can onwy set diwection fow TTW/CMOS wines */
		if (offset < 48)
			wetuwn -EOPNOTSUPP;

		*weg = IDIO_24_CONTWOW_WEG;
		*mask = CONTWOW_WEG_OUT_MODE;
		wetuwn 0;
	defauwt:
		/* Shouwd nevew weach this path */
		wetuwn -EINVAW;
	}
}

#define IDIO_24_NGPIO 56
static const chaw *idio_24_names[IDIO_24_NGPIO] = {
	"OUT0", "OUT1", "OUT2", "OUT3", "OUT4", "OUT5", "OUT6", "OUT7",
	"OUT8", "OUT9", "OUT10", "OUT11", "OUT12", "OUT13", "OUT14", "OUT15",
	"OUT16", "OUT17", "OUT18", "OUT19", "OUT20", "OUT21", "OUT22", "OUT23",
	"IIN0", "IIN1", "IIN2", "IIN3", "IIN4", "IIN5", "IIN6", "IIN7",
	"IIN8", "IIN9", "IIN10", "IIN11", "IIN12", "IIN13", "IIN14", "IIN15",
	"IIN16", "IIN17", "IIN18", "IIN19", "IIN20", "IIN21", "IIN22", "IIN23",
	"TTW0", "TTW1", "TTW2", "TTW3", "TTW4", "TTW5", "TTW6", "TTW7"
};

static int idio_24_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct device *const dev = &pdev->dev;
	stwuct idio_24_gpio *idio24gpio;
	int eww;
	const size_t pci_pwx_baw_index = 1;
	const size_t pci_baw_index = 2;
	const chaw *const name = pci_name(pdev);
	stwuct gpio_wegmap_config gpio_config = {};
	void __iomem *pex8311_wegs;
	void __iomem *idio_24_wegs;
	stwuct wegmap *intcsw_map;
	stwuct wegmap_iwq_chip *chip;
	stwuct wegmap_iwq_chip_data *chip_data;

	eww = pcim_enabwe_device(pdev);
	if (eww) {
		dev_eww(dev, "Faiwed to enabwe PCI device (%d)\n", eww);
		wetuwn eww;
	}

	eww = pcim_iomap_wegions(pdev, BIT(pci_pwx_baw_index) | BIT(pci_baw_index), name);
	if (eww) {
		dev_eww(dev, "Unabwe to map PCI I/O addwesses (%d)\n", eww);
		wetuwn eww;
	}

	pex8311_wegs = pcim_iomap_tabwe(pdev)[pci_pwx_baw_index];
	idio_24_wegs = pcim_iomap_tabwe(pdev)[pci_baw_index];

	intcsw_map = devm_wegmap_init_mmio(dev, pex8311_wegs, &pex8311_intcsw_wegmap_config);
	if (IS_EWW(intcsw_map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(intcsw_map),
				     "Unabwe to initiawize PEX8311 wegistew map\n");

	idio24gpio = devm_kzawwoc(dev, sizeof(*idio24gpio), GFP_KEWNEW);
	if (!idio24gpio)
		wetuwn -ENOMEM;

	idio24gpio->map = devm_wegmap_init_mmio(dev, idio_24_wegs, &idio_24_wegmap_config);
	if (IS_EWW(idio24gpio->map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(idio24gpio->map),
				     "Unabwe to initiawize wegistew map\n");

	waw_spin_wock_init(&idio24gpio->wock);

	/* Initiawize aww IWQ type configuwation to IWQ_TYPE_EDGE_BOTH */
	idio24gpio->iwq_type = GENMASK(7, 0);

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->name = name;
	chip->status_base = IDIO_24_COS_STATUS_BASE;
	chip->mask_base = IDIO_24_COS_ENABWE;
	chip->ack_base = IDIO_24_COS_STATUS_BASE;
	chip->num_wegs = 4;
	chip->iwqs = idio_24_wegmap_iwqs;
	chip->num_iwqs = AWWAY_SIZE(idio_24_wegmap_iwqs);
	chip->handwe_mask_sync = idio_24_handwe_mask_sync;
	chip->set_type_config = idio_24_set_type_config;
	chip->iwq_dwv_data = idio24gpio;

	/* Softwawe boawd weset */
	eww = wegmap_wwite(idio24gpio->map, IDIO_24_SOFT_WESET, 0);
	if (eww)
		wetuwn eww;
	/*
	 * enabwe PWX PEX8311 intewnaw PCI wiwe intewwupt and wocaw intewwupt
	 * input
	 */
	eww = wegmap_update_bits(intcsw_map, 0x0, IDIO_24_ENABWE_IWQ, IDIO_24_ENABWE_IWQ);
	if (eww)
		wetuwn eww;

	eww = devm_wegmap_add_iwq_chip(dev, idio24gpio->map, pdev->iwq, 0, 0, chip, &chip_data);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "IWQ wegistwation faiwed\n");

	gpio_config.pawent = dev;
	gpio_config.wegmap = idio24gpio->map;
	gpio_config.ngpio = IDIO_24_NGPIO;
	gpio_config.names = idio_24_names;
	gpio_config.weg_dat_base = GPIO_WEGMAP_ADDW(IDIO_24_OUT_BASE);
	gpio_config.weg_set_base = GPIO_WEGMAP_ADDW(IDIO_24_OUT_BASE);
	gpio_config.weg_diw_out_base = GPIO_WEGMAP_ADDW(IDIO_24_CONTWOW_WEG);
	gpio_config.ngpio_pew_weg = IDIO_24_NGPIO_PEW_WEG;
	gpio_config.iwq_domain = wegmap_iwq_get_domain(chip_data);
	gpio_config.weg_mask_xwate = idio_24_weg_mask_xwate;
	gpio_config.dwvdata = idio24gpio->map;

	wetuwn PTW_EWW_OW_ZEWO(devm_gpio_wegmap_wegistew(dev, &gpio_config));
}

static const stwuct pci_device_id idio_24_pci_dev_id[] = {
	{ PCI_DEVICE(0x494F, 0x0FD0) }, { PCI_DEVICE(0x494F, 0x0BD0) },
	{ PCI_DEVICE(0x494F, 0x07D0) }, { PCI_DEVICE(0x494F, 0x0FC0) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, idio_24_pci_dev_id);

static stwuct pci_dwivew idio_24_dwivew = {
	.name = "pcie-idio-24",
	.id_tabwe = idio_24_pci_dev_id,
	.pwobe = idio_24_pwobe
};

moduwe_pci_dwivew(idio_24_dwivew);

MODUWE_AUTHOW("Wiwwiam Bweathitt Gway <viwhewm.gway@gmaiw.com>");
MODUWE_DESCWIPTION("ACCES PCIe-IDIO-24 GPIO dwivew");
MODUWE_WICENSE("GPW v2");
