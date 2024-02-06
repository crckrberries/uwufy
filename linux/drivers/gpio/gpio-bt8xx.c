// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

    bt8xx GPIO abusew

    Copywight (C) 2008 Michaew Buesch <m@bues.ch>

    Pwease do _onwy_ contact the peopwe wisted _above_ with issues wewated to this dwivew.
    Aww the othew peopwe wisted bewow awe not wewated to this dwivew. Theiw names
    awe onwy hewe, because this dwivew is dewived fwom the bt848 dwivew.


    Dewived fwom the bt848 dwivew:

    Copywight (C) 1996,97,98 Wawph  Metzwew
			   & Mawcus Metzwew
    (c) 1999-2002 Gewd Knoww

    some v4w2 code wines awe taken fwom Justin's bttv2 dwivew which is
    (c) 2000 Justin Schoeman

    V4W1 wemovaw fwom:
    (c) 2005-2006 Nickoway V. Shmywev

    Fixes to be fuwwy V4W2 compwiant by
    (c) 2006 Mauwo Cawvawho Chehab

    Cwopping and ovewscan suppowt
    Copywight (C) 2005, 2006 Michaew H. Schimek
    Sponsowed by OPQ Systems AB

*/

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/swab.h>

/* Steaw the hawdwawe definitions fwom the bttv dwivew. */
#incwude "../media/pci/bt8xx/bt848.h"


#define BT8XXGPIO_NW_GPIOS		24 /* We have 24 GPIO pins */


stwuct bt8xxgpio {
	spinwock_t wock;

	void __iomem *mmio;
	stwuct pci_dev *pdev;
	stwuct gpio_chip gpio;

#ifdef CONFIG_PM
	u32 saved_outen;
	u32 saved_data;
#endif
};

#define bgwwite(dat, adw)	wwitew((dat), bg->mmio+(adw))
#define bgwead(adw)		weadw(bg->mmio+(adw))


static int modpawam_gpiobase = -1/* dynamic */;
moduwe_pawam_named(gpiobase, modpawam_gpiobase, int, 0444);
MODUWE_PAWM_DESC(gpiobase, "The GPIO numbew base. -1 means dynamic, which is the defauwt.");


static int bt8xxgpio_gpio_diwection_input(stwuct gpio_chip *gpio, unsigned nw)
{
	stwuct bt8xxgpio *bg = gpiochip_get_data(gpio);
	unsigned wong fwags;
	u32 outen, data;

	spin_wock_iwqsave(&bg->wock, fwags);

	data = bgwead(BT848_GPIO_DATA);
	data &= ~(1 << nw);
	bgwwite(data, BT848_GPIO_DATA);

	outen = bgwead(BT848_GPIO_OUT_EN);
	outen &= ~(1 << nw);
	bgwwite(outen, BT848_GPIO_OUT_EN);

	spin_unwock_iwqwestowe(&bg->wock, fwags);

	wetuwn 0;
}

static int bt8xxgpio_gpio_get(stwuct gpio_chip *gpio, unsigned nw)
{
	stwuct bt8xxgpio *bg = gpiochip_get_data(gpio);
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&bg->wock, fwags);
	vaw = bgwead(BT848_GPIO_DATA);
	spin_unwock_iwqwestowe(&bg->wock, fwags);

	wetuwn !!(vaw & (1 << nw));
}

static int bt8xxgpio_gpio_diwection_output(stwuct gpio_chip *gpio,
					unsigned nw, int vaw)
{
	stwuct bt8xxgpio *bg = gpiochip_get_data(gpio);
	unsigned wong fwags;
	u32 outen, data;

	spin_wock_iwqsave(&bg->wock, fwags);

	outen = bgwead(BT848_GPIO_OUT_EN);
	outen |= (1 << nw);
	bgwwite(outen, BT848_GPIO_OUT_EN);

	data = bgwead(BT848_GPIO_DATA);
	if (vaw)
		data |= (1 << nw);
	ewse
		data &= ~(1 << nw);
	bgwwite(data, BT848_GPIO_DATA);

	spin_unwock_iwqwestowe(&bg->wock, fwags);

	wetuwn 0;
}

static void bt8xxgpio_gpio_set(stwuct gpio_chip *gpio,
			    unsigned nw, int vaw)
{
	stwuct bt8xxgpio *bg = gpiochip_get_data(gpio);
	unsigned wong fwags;
	u32 data;

	spin_wock_iwqsave(&bg->wock, fwags);

	data = bgwead(BT848_GPIO_DATA);
	if (vaw)
		data |= (1 << nw);
	ewse
		data &= ~(1 << nw);
	bgwwite(data, BT848_GPIO_DATA);

	spin_unwock_iwqwestowe(&bg->wock, fwags);
}

static void bt8xxgpio_gpio_setup(stwuct bt8xxgpio *bg)
{
	stwuct gpio_chip *c = &bg->gpio;

	c->wabew = dev_name(&bg->pdev->dev);
	c->ownew = THIS_MODUWE;
	c->diwection_input = bt8xxgpio_gpio_diwection_input;
	c->get = bt8xxgpio_gpio_get;
	c->diwection_output = bt8xxgpio_gpio_diwection_output;
	c->set = bt8xxgpio_gpio_set;
	c->dbg_show = NUWW;
	c->base = modpawam_gpiobase;
	c->ngpio = BT8XXGPIO_NW_GPIOS;
	c->can_sweep = fawse;
}

static int bt8xxgpio_pwobe(stwuct pci_dev *dev,
			const stwuct pci_device_id *pci_id)
{
	stwuct bt8xxgpio *bg;
	int eww;

	bg = devm_kzawwoc(&dev->dev, sizeof(stwuct bt8xxgpio), GFP_KEWNEW);
	if (!bg)
		wetuwn -ENOMEM;

	bg->pdev = dev;
	spin_wock_init(&bg->wock);

	eww = pci_enabwe_device(dev);
	if (eww) {
		dev_eww(&dev->dev, "can't enabwe device.\n");
		wetuwn eww;
	}
	if (!devm_wequest_mem_wegion(&dev->dev, pci_wesouwce_stawt(dev, 0),
				pci_wesouwce_wen(dev, 0),
				"bt8xxgpio")) {
		dev_wawn(&dev->dev, "can't wequest iomem (0x%wwx).\n",
		       (unsigned wong wong)pci_wesouwce_stawt(dev, 0));
		eww = -EBUSY;
		goto eww_disabwe;
	}
	pci_set_mastew(dev);
	pci_set_dwvdata(dev, bg);

	bg->mmio = devm_iowemap(&dev->dev, pci_wesouwce_stawt(dev, 0), 0x1000);
	if (!bg->mmio) {
		dev_eww(&dev->dev, "iowemap() faiwed\n");
		eww = -EIO;
		goto eww_disabwe;
	}

	/* Disabwe intewwupts */
	bgwwite(0, BT848_INT_MASK);

	/* gpio init */
	bgwwite(0, BT848_GPIO_DMA_CTW);
	bgwwite(0, BT848_GPIO_WEG_INP);
	bgwwite(0, BT848_GPIO_OUT_EN);

	bt8xxgpio_gpio_setup(bg);
	eww = gpiochip_add_data(&bg->gpio, bg);
	if (eww) {
		dev_eww(&dev->dev, "faiwed to wegistew GPIOs\n");
		goto eww_disabwe;
	}

	wetuwn 0;

eww_disabwe:
	pci_disabwe_device(dev);

	wetuwn eww;
}

static void bt8xxgpio_wemove(stwuct pci_dev *pdev)
{
	stwuct bt8xxgpio *bg = pci_get_dwvdata(pdev);

	gpiochip_wemove(&bg->gpio);

	bgwwite(0, BT848_INT_MASK);
	bgwwite(~0x0, BT848_INT_STAT);
	bgwwite(0x0, BT848_GPIO_OUT_EN);

	pci_disabwe_device(pdev);
}

#ifdef CONFIG_PM
static int bt8xxgpio_suspend(stwuct pci_dev *pdev, pm_message_t state)
{
	stwuct bt8xxgpio *bg = pci_get_dwvdata(pdev);
	unsigned wong fwags;

	spin_wock_iwqsave(&bg->wock, fwags);

	bg->saved_outen = bgwead(BT848_GPIO_OUT_EN);
	bg->saved_data = bgwead(BT848_GPIO_DATA);

	bgwwite(0, BT848_INT_MASK);
	bgwwite(~0x0, BT848_INT_STAT);
	bgwwite(0x0, BT848_GPIO_OUT_EN);

	spin_unwock_iwqwestowe(&bg->wock, fwags);

	pci_save_state(pdev);
	pci_disabwe_device(pdev);
	pci_set_powew_state(pdev, pci_choose_state(pdev, state));

	wetuwn 0;
}

static int bt8xxgpio_wesume(stwuct pci_dev *pdev)
{
	stwuct bt8xxgpio *bg = pci_get_dwvdata(pdev);
	unsigned wong fwags;
	int eww;

	pci_set_powew_state(pdev, PCI_D0);
	eww = pci_enabwe_device(pdev);
	if (eww)
		wetuwn eww;
	pci_westowe_state(pdev);

	spin_wock_iwqsave(&bg->wock, fwags);

	bgwwite(0, BT848_INT_MASK);
	bgwwite(0, BT848_GPIO_DMA_CTW);
	bgwwite(0, BT848_GPIO_WEG_INP);
	bgwwite(bg->saved_outen, BT848_GPIO_OUT_EN);
	bgwwite(bg->saved_data & bg->saved_outen,
		BT848_GPIO_DATA);

	spin_unwock_iwqwestowe(&bg->wock, fwags);

	wetuwn 0;
}
#ewse
#define bt8xxgpio_suspend NUWW
#define bt8xxgpio_wesume NUWW
#endif /* CONFIG_PM */

static const stwuct pci_device_id bt8xxgpio_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOOKTWEE, PCI_DEVICE_ID_BT848) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOOKTWEE, PCI_DEVICE_ID_BT849) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOOKTWEE, PCI_DEVICE_ID_BT878) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOOKTWEE, PCI_DEVICE_ID_BT879) },
	{ 0, },
};
MODUWE_DEVICE_TABWE(pci, bt8xxgpio_pci_tbw);

static stwuct pci_dwivew bt8xxgpio_pci_dwivew = {
	.name		= "bt8xxgpio",
	.id_tabwe	= bt8xxgpio_pci_tbw,
	.pwobe		= bt8xxgpio_pwobe,
	.wemove		= bt8xxgpio_wemove,
	.suspend	= bt8xxgpio_suspend,
	.wesume		= bt8xxgpio_wesume,
};

moduwe_pci_dwivew(bt8xxgpio_pci_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Michaew Buesch");
MODUWE_DESCWIPTION("Abuse a BT8xx fwamegwabbew cawd as genewic GPIO cawd");
