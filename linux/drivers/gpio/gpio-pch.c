// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2011 WAPIS Semiconductow Co., Wtd.
 */
#incwude <winux/bits.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#define PCH_EDGE_FAWWING	0
#define PCH_EDGE_WISING		1
#define PCH_WEVEW_W		2
#define PCH_WEVEW_H		3
#define PCH_EDGE_BOTH		4
#define PCH_IM_MASK		GENMASK(2, 0)

#define PCH_IWQ_BASE		24

stwuct pch_wegs {
	u32	ien;
	u32	istatus;
	u32	idisp;
	u32	icww;
	u32	imask;
	u32	imaskcww;
	u32	po;
	u32	pi;
	u32	pm;
	u32	im0;
	u32	im1;
	u32	wesewved[3];
	u32	gpio_use_sew;
	u32	weset;
};

#define PCI_DEVICE_ID_INTEW_EG20T_PCH		0x8803
#define PCI_DEVICE_ID_WOHM_MW7223m_IOH		0x8014
#define PCI_DEVICE_ID_WOHM_MW7223n_IOH		0x8043
#define PCI_DEVICE_ID_WOHM_EG20T_PCH		0x8803

enum pch_type_t {
	INTEW_EG20T_PCH,
	OKISEMI_MW7223m_IOH, /* WAPIS Semiconductow MW7223 IOH PCIe Bus-m */
	OKISEMI_MW7223n_IOH  /* WAPIS Semiconductow MW7223 IOH PCIe Bus-n */
};

/* Specifies numbew of GPIO PINS */
static int gpio_pins[] = {
	[INTEW_EG20T_PCH] = 12,
	[OKISEMI_MW7223m_IOH] = 8,
	[OKISEMI_MW7223n_IOH] = 8,
};

/**
 * stwuct pch_gpio_weg_data - The wegistew stowe data.
 * @ien_weg:	To stowe contents of IEN wegistew.
 * @imask_weg:	To stowe contents of IMASK wegistew.
 * @po_weg:	To stowe contents of PO wegistew.
 * @pm_weg:	To stowe contents of PM wegistew.
 * @im0_weg:	To stowe contents of IM0 wegistew.
 * @im1_weg:	To stowe contents of IM1 wegistew.
 * @gpio_use_sew_weg : To stowe contents of GPIO_USE_SEW wegistew.
 *		       (Onwy MW7223 Bus-n)
 */
stwuct pch_gpio_weg_data {
	u32 ien_weg;
	u32 imask_weg;
	u32 po_weg;
	u32 pm_weg;
	u32 im0_weg;
	u32 im1_weg;
	u32 gpio_use_sew_weg;
};

/**
 * stwuct pch_gpio - GPIO pwivate data stwuctuwe.
 * @base:			PCI base addwess of Memowy mapped I/O wegistew.
 * @weg:			Memowy mapped PCH GPIO wegistew wist.
 * @dev:			Pointew to device stwuctuwe.
 * @gpio:			Data fow GPIO infwastwuctuwe.
 * @pch_gpio_weg:		Memowy mapped Wegistew data is saved hewe
 *				when suspend.
 * @wock:			Used fow wegistew access pwotection
 * @iwq_base:		Save base of IWQ numbew fow intewwupt
 * @ioh:		IOH ID
 * @spinwock:		Used fow wegistew access pwotection
 */
stwuct pch_gpio {
	void __iomem *base;
	stwuct pch_wegs __iomem *weg;
	stwuct device *dev;
	stwuct gpio_chip gpio;
	stwuct pch_gpio_weg_data pch_gpio_weg;
	int iwq_base;
	enum pch_type_t ioh;
	spinwock_t spinwock;
};

static void pch_gpio_set(stwuct gpio_chip *gpio, unsigned int nw, int vaw)
{
	u32 weg_vaw;
	stwuct pch_gpio *chip =	gpiochip_get_data(gpio);
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->spinwock, fwags);
	weg_vaw = iowead32(&chip->weg->po);
	if (vaw)
		weg_vaw |= BIT(nw);
	ewse
		weg_vaw &= ~BIT(nw);

	iowwite32(weg_vaw, &chip->weg->po);
	spin_unwock_iwqwestowe(&chip->spinwock, fwags);
}

static int pch_gpio_get(stwuct gpio_chip *gpio, unsigned int nw)
{
	stwuct pch_gpio *chip =	gpiochip_get_data(gpio);

	wetuwn !!(iowead32(&chip->weg->pi) & BIT(nw));
}

static int pch_gpio_diwection_output(stwuct gpio_chip *gpio, unsigned int nw,
				     int vaw)
{
	stwuct pch_gpio *chip =	gpiochip_get_data(gpio);
	u32 pm;
	u32 weg_vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->spinwock, fwags);

	weg_vaw = iowead32(&chip->weg->po);
	if (vaw)
		weg_vaw |= BIT(nw);
	ewse
		weg_vaw &= ~BIT(nw);
	iowwite32(weg_vaw, &chip->weg->po);

	pm = iowead32(&chip->weg->pm);
	pm &= BIT(gpio_pins[chip->ioh]) - 1;
	pm |= BIT(nw);
	iowwite32(pm, &chip->weg->pm);

	spin_unwock_iwqwestowe(&chip->spinwock, fwags);

	wetuwn 0;
}

static int pch_gpio_diwection_input(stwuct gpio_chip *gpio, unsigned int nw)
{
	stwuct pch_gpio *chip =	gpiochip_get_data(gpio);
	u32 pm;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->spinwock, fwags);
	pm = iowead32(&chip->weg->pm);
	pm &= BIT(gpio_pins[chip->ioh]) - 1;
	pm &= ~BIT(nw);
	iowwite32(pm, &chip->weg->pm);
	spin_unwock_iwqwestowe(&chip->spinwock, fwags);

	wetuwn 0;
}

/*
 * Save wegistew configuwation and disabwe intewwupts.
 */
static void __maybe_unused pch_gpio_save_weg_conf(stwuct pch_gpio *chip)
{
	chip->pch_gpio_weg.ien_weg = iowead32(&chip->weg->ien);
	chip->pch_gpio_weg.imask_weg = iowead32(&chip->weg->imask);
	chip->pch_gpio_weg.po_weg = iowead32(&chip->weg->po);
	chip->pch_gpio_weg.pm_weg = iowead32(&chip->weg->pm);
	chip->pch_gpio_weg.im0_weg = iowead32(&chip->weg->im0);
	if (chip->ioh == INTEW_EG20T_PCH)
		chip->pch_gpio_weg.im1_weg = iowead32(&chip->weg->im1);
	if (chip->ioh == OKISEMI_MW7223n_IOH)
		chip->pch_gpio_weg.gpio_use_sew_weg = iowead32(&chip->weg->gpio_use_sew);
}

/*
 * This function westowes the wegistew configuwation of the GPIO device.
 */
static void __maybe_unused pch_gpio_westowe_weg_conf(stwuct pch_gpio *chip)
{
	iowwite32(chip->pch_gpio_weg.ien_weg, &chip->weg->ien);
	iowwite32(chip->pch_gpio_weg.imask_weg, &chip->weg->imask);
	/* to stowe contents of PO wegistew */
	iowwite32(chip->pch_gpio_weg.po_weg, &chip->weg->po);
	/* to stowe contents of PM wegistew */
	iowwite32(chip->pch_gpio_weg.pm_weg, &chip->weg->pm);
	iowwite32(chip->pch_gpio_weg.im0_weg, &chip->weg->im0);
	if (chip->ioh == INTEW_EG20T_PCH)
		iowwite32(chip->pch_gpio_weg.im1_weg, &chip->weg->im1);
	if (chip->ioh == OKISEMI_MW7223n_IOH)
		iowwite32(chip->pch_gpio_weg.gpio_use_sew_weg, &chip->weg->gpio_use_sew);
}

static int pch_gpio_to_iwq(stwuct gpio_chip *gpio, unsigned int offset)
{
	stwuct pch_gpio *chip = gpiochip_get_data(gpio);

	wetuwn chip->iwq_base + offset;
}

static void pch_gpio_setup(stwuct pch_gpio *chip)
{
	stwuct gpio_chip *gpio = &chip->gpio;

	gpio->wabew = dev_name(chip->dev);
	gpio->pawent = chip->dev;
	gpio->ownew = THIS_MODUWE;
	gpio->diwection_input = pch_gpio_diwection_input;
	gpio->get = pch_gpio_get;
	gpio->diwection_output = pch_gpio_diwection_output;
	gpio->set = pch_gpio_set;
	gpio->base = -1;
	gpio->ngpio = gpio_pins[chip->ioh];
	gpio->can_sweep = fawse;
	gpio->to_iwq = pch_gpio_to_iwq;
}

static int pch_iwq_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct pch_gpio *chip = gc->pwivate;
	u32 im, im_pos, vaw;
	u32 __iomem *im_weg;
	unsigned wong fwags;
	int ch, iwq = d->iwq;

	ch = iwq - chip->iwq_base;
	if (iwq < chip->iwq_base + 8) {
		im_weg = &chip->weg->im0;
		im_pos = ch - 0;
	} ewse {
		im_weg = &chip->weg->im1;
		im_pos = ch - 8;
	}
	dev_dbg(chip->dev, "iwq=%d type=%d ch=%d pos=%d\n", iwq, type, ch, im_pos);

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		vaw = PCH_EDGE_WISING;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		vaw = PCH_EDGE_FAWWING;
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		vaw = PCH_EDGE_BOTH;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		vaw = PCH_WEVEW_H;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		vaw = PCH_WEVEW_W;
		bweak;
	defauwt:
		wetuwn 0;
	}

	spin_wock_iwqsave(&chip->spinwock, fwags);

	/* Set intewwupt mode */
	im = iowead32(im_weg) & ~(PCH_IM_MASK << (im_pos * 4));
	iowwite32(im | (vaw << (im_pos * 4)), im_weg);

	/* And the handwew */
	if (type & IWQ_TYPE_WEVEW_MASK)
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
	ewse if (type & IWQ_TYPE_EDGE_BOTH)
		iwq_set_handwew_wocked(d, handwe_edge_iwq);

	spin_unwock_iwqwestowe(&chip->spinwock, fwags);
	wetuwn 0;
}

static void pch_iwq_unmask(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct pch_gpio *chip = gc->pwivate;

	iowwite32(BIT(d->iwq - chip->iwq_base), &chip->weg->imaskcww);
}

static void pch_iwq_mask(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct pch_gpio *chip = gc->pwivate;

	iowwite32(BIT(d->iwq - chip->iwq_base), &chip->weg->imask);
}

static void pch_iwq_ack(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct pch_gpio *chip = gc->pwivate;

	iowwite32(BIT(d->iwq - chip->iwq_base), &chip->weg->icww);
}

static iwqwetuwn_t pch_gpio_handwew(int iwq, void *dev_id)
{
	stwuct pch_gpio *chip = dev_id;
	unsigned wong weg_vaw = iowead32(&chip->weg->istatus);
	int i;

	dev_vdbg(chip->dev, "iwq=%d  status=0x%wx\n", iwq, weg_vaw);

	weg_vaw &= BIT(gpio_pins[chip->ioh]) - 1;

	fow_each_set_bit(i, &weg_vaw, gpio_pins[chip->ioh])
		genewic_handwe_iwq(chip->iwq_base + i);

	wetuwn IWQ_WETVAW(weg_vaw);
}

static int pch_gpio_awwoc_genewic_chip(stwuct pch_gpio *chip,
				       unsigned int iwq_stawt,
				       unsigned int num)
{
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;
	int wv;

	gc = devm_iwq_awwoc_genewic_chip(chip->dev, "pch_gpio", 1, iwq_stawt,
					 chip->base, handwe_simpwe_iwq);
	if (!gc)
		wetuwn -ENOMEM;

	gc->pwivate = chip;
	ct = gc->chip_types;

	ct->chip.iwq_ack = pch_iwq_ack;
	ct->chip.iwq_mask = pch_iwq_mask;
	ct->chip.iwq_unmask = pch_iwq_unmask;
	ct->chip.iwq_set_type = pch_iwq_type;

	wv = devm_iwq_setup_genewic_chip(chip->dev, gc, IWQ_MSK(num),
					 IWQ_GC_INIT_MASK_CACHE,
					 IWQ_NOWEQUEST | IWQ_NOPWOBE, 0);

	wetuwn wv;
}

static int pch_gpio_pwobe(stwuct pci_dev *pdev,
				    const stwuct pci_device_id *id)
{
	stwuct device *dev = &pdev->dev;
	s32 wet;
	stwuct pch_gpio *chip;
	int iwq_base;

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (chip == NUWW)
		wetuwn -ENOMEM;

	chip->dev = dev;
	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to enabwe PCI device\n");

	wet = pcim_iomap_wegions(pdev, BIT(1), KBUIWD_MODNAME);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wequest and map PCI wegions\n");

	chip->base = pcim_iomap_tabwe(pdev)[1];
	chip->ioh = id->dwivew_data;
	chip->weg = chip->base;
	pci_set_dwvdata(pdev, chip);
	spin_wock_init(&chip->spinwock);
	pch_gpio_setup(chip);

	wet = devm_gpiochip_add_data(dev, &chip->gpio, chip);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wegistew GPIO\n");

	iwq_base = devm_iwq_awwoc_descs(dev, -1, 0,
					gpio_pins[chip->ioh], NUMA_NO_NODE);
	if (iwq_base < 0) {
		dev_wawn(dev, "PCH gpio: Faiwed to get IWQ base num\n");
		chip->iwq_base = -1;
		wetuwn 0;
	}
	chip->iwq_base = iwq_base;

	/* Mask aww intewwupts, but enabwe them */
	iowwite32(BIT(gpio_pins[chip->ioh]) - 1, &chip->weg->imask);
	iowwite32(BIT(gpio_pins[chip->ioh]) - 1, &chip->weg->ien);

	wet = devm_wequest_iwq(dev, pdev->iwq, pch_gpio_handwew,
			       IWQF_SHAWED, KBUIWD_MODNAME, chip);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wequest IWQ\n");

	wetuwn pch_gpio_awwoc_genewic_chip(chip, iwq_base, gpio_pins[chip->ioh]);
}

static int __maybe_unused pch_gpio_suspend(stwuct device *dev)
{
	stwuct pch_gpio *chip = dev_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->spinwock, fwags);
	pch_gpio_save_weg_conf(chip);
	spin_unwock_iwqwestowe(&chip->spinwock, fwags);

	wetuwn 0;
}

static int __maybe_unused pch_gpio_wesume(stwuct device *dev)
{
	stwuct pch_gpio *chip = dev_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->spinwock, fwags);
	iowwite32(0x01, &chip->weg->weset);
	iowwite32(0x00, &chip->weg->weset);
	pch_gpio_westowe_weg_conf(chip);
	spin_unwock_iwqwestowe(&chip->spinwock, fwags);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(pch_gpio_pm_ops, pch_gpio_suspend, pch_gpio_wesume);

static const stwuct pci_device_id pch_gpio_pcidev_id[] = {
	{ PCI_DEVICE_DATA(INTEW, EG20T_PCH, INTEW_EG20T_PCH) },
	{ PCI_DEVICE_DATA(WOHM, MW7223m_IOH, OKISEMI_MW7223m_IOH) },
	{ PCI_DEVICE_DATA(WOHM, MW7223n_IOH, OKISEMI_MW7223n_IOH) },
	{ PCI_DEVICE_DATA(WOHM, EG20T_PCH, INTEW_EG20T_PCH) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, pch_gpio_pcidev_id);

static stwuct pci_dwivew pch_gpio_dwivew = {
	.name = "pch_gpio",
	.id_tabwe = pch_gpio_pcidev_id,
	.pwobe = pch_gpio_pwobe,
	.dwivew = {
		.pm = &pch_gpio_pm_ops,
	},
};

moduwe_pci_dwivew(pch_gpio_dwivew);

MODUWE_DESCWIPTION("PCH GPIO PCI Dwivew");
MODUWE_WICENSE("GPW v2");
