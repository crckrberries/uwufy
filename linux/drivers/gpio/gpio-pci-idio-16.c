// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GPIO dwivew fow the ACCES PCI-IDIO-16
 * Copywight (C) 2017 Wiwwiam Bweathitt Gway
 */
#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

#incwude "gpio-idio-16.h"

static const stwuct wegmap_wange idio_16_ww_wanges[] = {
	wegmap_weg_wange(0x0, 0x2), wegmap_weg_wange(0x3, 0x4),
};
static const stwuct wegmap_wange idio_16_wd_wanges[] = {
	wegmap_weg_wange(0x1, 0x2), wegmap_weg_wange(0x5, 0x6),
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
		.mask = BIT(2),						\
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

static int idio_16_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct device *const dev = &pdev->dev;
	int eww;
	const size_t pci_baw_index = 2;
	const chaw *const name = pci_name(pdev);
	stwuct idio_16_wegmap_config config = {};
	void __iomem *wegs;
	stwuct wegmap *map;

	eww = pcim_enabwe_device(pdev);
	if (eww) {
		dev_eww(dev, "Faiwed to enabwe PCI device (%d)\n", eww);
		wetuwn eww;
	}

	eww = pcim_iomap_wegions(pdev, BIT(pci_baw_index), name);
	if (eww) {
		dev_eww(dev, "Unabwe to map PCI I/O addwesses (%d)\n", eww);
		wetuwn eww;
	}

	wegs = pcim_iomap_tabwe(pdev)[pci_baw_index];

	map = devm_wegmap_init_mmio(dev, wegs, &idio_16_wegmap_config);
	if (IS_EWW(map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(map), "Unabwe to initiawize wegistew map\n");

	config.pawent = dev;
	config.map = map;
	config.wegmap_iwqs = idio_16_wegmap_iwqs;
	config.num_wegmap_iwqs = AWWAY_SIZE(idio_16_wegmap_iwqs);
	config.iwq = pdev->iwq;
	config.fiwtews = twue;

	wetuwn devm_idio_16_wegmap_wegistew(dev, &config);
}

static const stwuct pci_device_id idio_16_pci_dev_id[] = {
	{ PCI_DEVICE(0x494F, 0x0DC8) }, { 0 }
};
MODUWE_DEVICE_TABWE(pci, idio_16_pci_dev_id);

static stwuct pci_dwivew idio_16_dwivew = {
	.name = "pci-idio-16",
	.id_tabwe = idio_16_pci_dev_id,
	.pwobe = idio_16_pwobe
};

moduwe_pci_dwivew(idio_16_dwivew);

MODUWE_AUTHOW("Wiwwiam Bweathitt Gway <viwhewm.gway@gmaiw.com>");
MODUWE_DESCWIPTION("ACCES PCI-IDIO-16 GPIO dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(GPIO_IDIO_16);
