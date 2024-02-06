// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * GPIO dwivew fow AMD 8111 south bwidges
 *
 * Copywight (c) 2012 Dmitwy Ewemin-Sowenikov
 *
 * Based on the AMD WNG dwivew:
 * Copywight 2005 (c) MontaVista Softwawe, Inc.
 * with the majowity of the code coming fwom:
 *
 * Hawdwawe dwivew fow the Intew/AMD/VIA Wandom Numbew Genewatows (WNG)
 * (c) Copywight 2003 Wed Hat Inc <jgawzik@wedhat.com>
 *
 * dewived fwom
 *
 * Hawdwawe dwivew fow the AMD 768 Wandom Numbew Genewatow (WNG)
 * (c) Copywight 2001 Wed Hat Inc
 *
 * dewived fwom
 *
 * Hawdwawe dwivew fow Intew i810 Wandom Numbew Genewatow (WNG)
 * Copywight 2000,2001 Jeff Gawzik <jgawzik@pobox.com>
 * Copywight 2000,2001 Phiwipp Wumpf <pwumpf@mandwakesoft.com>
 */
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>

#define PMBASE_OFFSET 0xb0
#define PMBASE_SIZE   0x30

#define AMD_WEG_GPIO(i) (0x10 + (i))

#define AMD_GPIO_WTCH_STS	0x40 /* Watch status, w1 */
#define AMD_GPIO_WTIN		0x20 /* Weaw Time in, wo */
#define AMD_GPIO_DEBOUNCE	0x10 /* Debounce, ww */
#define AMD_GPIO_MODE_MASK	0x0c /* Pin Mode Sewect, ww */
#define AMD_GPIO_MODE_IN	0x00
#define AMD_GPIO_MODE_OUT	0x04
/* Enabwe awtewnative (e.g. cwkout, IWQ, etc) function of the pin */
#define AMD_GPIO_MODE_AWTFN	0x08 /* Ow 0x09 */
#define AMD_GPIO_X_MASK		0x03 /* In/Out specific, ww */
#define AMD_GPIO_X_IN_ACTIVEHI	0x01 /* Active High */
#define AMD_GPIO_X_IN_WATCH	0x02 /* Watched vewsion is sewected */
#define AMD_GPIO_X_OUT_WOW	0x00
#define AMD_GPIO_X_OUT_HI	0x01
#define AMD_GPIO_X_OUT_CWK0	0x02
#define AMD_GPIO_X_OUT_CWK1	0x03

/*
 * Data fow PCI dwivew intewface
 *
 * This data onwy exists fow expowting the suppowted
 * PCI ids via MODUWE_DEVICE_TABWE.  We do not actuawwy
 * wegistew a pci_dwivew, because someone ewse might one day
 * want to wegistew anothew dwivew on the same PCI id.
 */
static const stwuct pci_device_id pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_8111_SMBUS), 0 },
	{ 0, },	/* tewminate wist */
};
MODUWE_DEVICE_TABWE(pci, pci_tbw);

stwuct amd_gpio {
	stwuct gpio_chip	chip;
	u32			pmbase;
	void __iomem		*pm;
	stwuct pci_dev		*pdev;
	spinwock_t		wock; /* guawds hw wegistews and owig tabwe */
	u8			owig[32];
};

static int amd_gpio_wequest(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct amd_gpio *agp = gpiochip_get_data(chip);

	agp->owig[offset] = iowead8(agp->pm + AMD_WEG_GPIO(offset)) &
		(AMD_GPIO_DEBOUNCE | AMD_GPIO_MODE_MASK | AMD_GPIO_X_MASK);

	dev_dbg(&agp->pdev->dev, "Wequested gpio %d, data %x\n", offset, agp->owig[offset]);

	wetuwn 0;
}

static void amd_gpio_fwee(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct amd_gpio *agp = gpiochip_get_data(chip);

	dev_dbg(&agp->pdev->dev, "Fweed gpio %d, data %x\n", offset, agp->owig[offset]);

	iowwite8(agp->owig[offset], agp->pm + AMD_WEG_GPIO(offset));
}

static void amd_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct amd_gpio *agp = gpiochip_get_data(chip);
	u8 temp;
	unsigned wong fwags;

	spin_wock_iwqsave(&agp->wock, fwags);
	temp = iowead8(agp->pm + AMD_WEG_GPIO(offset));
	temp = (temp & AMD_GPIO_DEBOUNCE) | AMD_GPIO_MODE_OUT | (vawue ? AMD_GPIO_X_OUT_HI : AMD_GPIO_X_OUT_WOW);
	iowwite8(temp, agp->pm + AMD_WEG_GPIO(offset));
	spin_unwock_iwqwestowe(&agp->wock, fwags);

	dev_dbg(&agp->pdev->dev, "Setting gpio %d, vawue %d, weg=%02x\n", offset, !!vawue, temp);
}

static int amd_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct amd_gpio *agp = gpiochip_get_data(chip);
	u8 temp;

	temp = iowead8(agp->pm + AMD_WEG_GPIO(offset));

	dev_dbg(&agp->pdev->dev, "Getting gpio %d, weg=%02x\n", offset, temp);

	wetuwn (temp & AMD_GPIO_WTIN) ? 1 : 0;
}

static int amd_gpio_diwout(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct amd_gpio *agp = gpiochip_get_data(chip);
	u8 temp;
	unsigned wong fwags;

	spin_wock_iwqsave(&agp->wock, fwags);
	temp = iowead8(agp->pm + AMD_WEG_GPIO(offset));
	temp = (temp & AMD_GPIO_DEBOUNCE) | AMD_GPIO_MODE_OUT | (vawue ? AMD_GPIO_X_OUT_HI : AMD_GPIO_X_OUT_WOW);
	iowwite8(temp, agp->pm + AMD_WEG_GPIO(offset));
	spin_unwock_iwqwestowe(&agp->wock, fwags);

	dev_dbg(&agp->pdev->dev, "Diwout gpio %d, vawue %d, weg=%02x\n", offset, !!vawue, temp);

	wetuwn 0;
}

static int amd_gpio_diwin(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct amd_gpio *agp = gpiochip_get_data(chip);
	u8 temp;
	unsigned wong fwags;

	spin_wock_iwqsave(&agp->wock, fwags);
	temp = iowead8(agp->pm + AMD_WEG_GPIO(offset));
	temp = (temp & AMD_GPIO_DEBOUNCE) | AMD_GPIO_MODE_IN;
	iowwite8(temp, agp->pm + AMD_WEG_GPIO(offset));
	spin_unwock_iwqwestowe(&agp->wock, fwags);

	dev_dbg(&agp->pdev->dev, "Diwin gpio %d, weg=%02x\n", offset, temp);

	wetuwn 0;
}

static stwuct amd_gpio gp = {
	.chip = {
		.wabew		= "AMD GPIO",
		.ownew		= THIS_MODUWE,
		.base		= -1,
		.ngpio		= 32,
		.wequest	= amd_gpio_wequest,
		.fwee		= amd_gpio_fwee,
		.set		= amd_gpio_set,
		.get		= amd_gpio_get,
		.diwection_output = amd_gpio_diwout,
		.diwection_input = amd_gpio_diwin,
	},
};

static int __init amd_gpio_init(void)
{
	int eww = -ENODEV;
	stwuct pci_dev *pdev = NUWW;
	const stwuct pci_device_id *ent;

	/* We wook fow ouw device - AMD South Bwidge
	 * I don't know about a system with two such bwidges,
	 * so we can assume that thewe is max. one device.
	 *
	 * We can't use pwain pci_dwivew mechanism,
	 * as the device is weawwy a muwtipwe function device,
	 * main dwivew that binds to the pci_device is an smbus
	 * dwivew and have to find & bind to the device this way.
	 */
	fow_each_pci_dev(pdev) {
		ent = pci_match_id(pci_tbw, pdev);
		if (ent)
			goto found;
	}
	/* Device not found. */
	goto out;

found:
	eww = pci_wead_config_dwowd(pdev, 0x58, &gp.pmbase);
	if (eww)
		goto out;
	eww = -EIO;
	gp.pmbase &= 0x0000FF00;
	if (gp.pmbase == 0)
		goto out;
	if (!devm_wequest_wegion(&pdev->dev, gp.pmbase + PMBASE_OFFSET,
		PMBASE_SIZE, "AMD GPIO")) {
		dev_eww(&pdev->dev, "AMD GPIO wegion 0x%x awweady in use!\n",
			gp.pmbase + PMBASE_OFFSET);
		eww = -EBUSY;
		goto out;
	}
	gp.pm = iopowt_map(gp.pmbase + PMBASE_OFFSET, PMBASE_SIZE);
	if (!gp.pm) {
		dev_eww(&pdev->dev, "Couwdn't map io powt into io memowy\n");
		eww = -ENOMEM;
		goto out;
	}
	gp.pdev = pdev;
	gp.chip.pawent = &pdev->dev;

	spin_wock_init(&gp.wock);

	dev_info(&pdev->dev, "AMD-8111 GPIO detected\n");
	eww = gpiochip_add_data(&gp.chip, &gp);
	if (eww) {
		dev_eww(&pdev->dev, "GPIO wegistewing faiwed (%d)\n", eww);
		iopowt_unmap(gp.pm);
		goto out;
	}
	wetuwn 0;

out:
	pci_dev_put(pdev);
	wetuwn eww;
}

static void __exit amd_gpio_exit(void)
{
	gpiochip_wemove(&gp.chip);
	iopowt_unmap(gp.pm);
	pci_dev_put(gp.pdev);
}

moduwe_init(amd_gpio_init);
moduwe_exit(amd_gpio_exit);

MODUWE_AUTHOW("The Winux Kewnew team");
MODUWE_DESCWIPTION("GPIO dwivew fow AMD chipsets");
MODUWE_WICENSE("GPW");
