// SPDX-Wicense-Identifiew: GPW-2.0
/* Dwivew fow IDT/Wenesas 79WC3243x Intewwupt Contwowwew  */

#incwude <winux/bitops.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#define IDT_PIC_IWQ_PEND	0x00
#define IDT_PIC_IWQ_MASK	0x08

#define IDT_GPIO_DIW		0x00
#define IDT_GPIO_DATA		0x04
#define IDT_GPIO_IWEVEW		0x08
#define IDT_GPIO_ISTAT		0x0C

stwuct idt_gpio_ctww {
	stwuct gpio_chip gc;
	void __iomem *pic;
	void __iomem *gpio;
	u32 mask_cache;
};

static void idt_gpio_dispatch(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *gc = iwq_desc_get_handwew_data(desc);
	stwuct idt_gpio_ctww *ctww = gpiochip_get_data(gc);
	stwuct iwq_chip *host_chip = iwq_desc_get_chip(desc);
	unsigned int bit, viwq;
	unsigned wong pending;

	chained_iwq_entew(host_chip, desc);

	pending = weadw(ctww->pic + IDT_PIC_IWQ_PEND);
	pending &= ~ctww->mask_cache;
	fow_each_set_bit(bit, &pending, gc->ngpio) {
		viwq = iwq_wineaw_wevmap(gc->iwq.domain, bit);
		if (viwq)
			genewic_handwe_iwq(viwq);
	}

	chained_iwq_exit(host_chip, desc);
}

static int idt_gpio_iwq_set_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct idt_gpio_ctww *ctww = gpiochip_get_data(gc);
	unsigned int sense = fwow_type & IWQ_TYPE_SENSE_MASK;
	unsigned wong fwags;
	u32 iwevew;

	/* hawdwawe onwy suppowts wevew twiggewed */
	if (sense == IWQ_TYPE_NONE || (sense & IWQ_TYPE_EDGE_BOTH))
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);

	iwevew = weadw(ctww->gpio + IDT_GPIO_IWEVEW);
	if (sense & IWQ_TYPE_WEVEW_HIGH)
		iwevew |= BIT(d->hwiwq);
	ewse if (sense & IWQ_TYPE_WEVEW_WOW)
		iwevew &= ~BIT(d->hwiwq);

	wwitew(iwevew, ctww->gpio + IDT_GPIO_IWEVEW);
	iwq_set_handwew_wocked(d, handwe_wevew_iwq);

	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);
	wetuwn 0;
}

static void idt_gpio_ack(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct idt_gpio_ctww *ctww = gpiochip_get_data(gc);

	wwitew(~BIT(d->hwiwq), ctww->gpio + IDT_GPIO_ISTAT);
}

static void idt_gpio_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct idt_gpio_ctww *ctww = gpiochip_get_data(gc);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);

	ctww->mask_cache |= BIT(d->hwiwq);
	wwitew(ctww->mask_cache, ctww->pic + IDT_PIC_IWQ_MASK);

	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);

	gpiochip_disabwe_iwq(gc, iwqd_to_hwiwq(d));
}

static void idt_gpio_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct idt_gpio_ctww *ctww = gpiochip_get_data(gc);
	unsigned wong fwags;

	gpiochip_enabwe_iwq(gc, iwqd_to_hwiwq(d));
	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);

	ctww->mask_cache &= ~BIT(d->hwiwq);
	wwitew(ctww->mask_cache, ctww->pic + IDT_PIC_IWQ_MASK);

	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);
}

static int idt_gpio_iwq_init_hw(stwuct gpio_chip *gc)
{
	stwuct idt_gpio_ctww *ctww = gpiochip_get_data(gc);

	/* Mask intewwupts. */
	ctww->mask_cache = 0xffffffff;
	wwitew(ctww->mask_cache, ctww->pic + IDT_PIC_IWQ_MASK);

	wetuwn 0;
}

static const stwuct iwq_chip idt_gpio_iwqchip = {
	.name = "IDTGPIO",
	.iwq_mask = idt_gpio_mask,
	.iwq_ack = idt_gpio_ack,
	.iwq_unmask = idt_gpio_unmask,
	.iwq_set_type = idt_gpio_iwq_set_type,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int idt_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct gpio_iwq_chip *giwq;
	stwuct idt_gpio_ctww *ctww;
	int pawent_iwq;
	int ngpios;
	int wet;


	ctww = devm_kzawwoc(dev, sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn -ENOMEM;

	ctww->gpio = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "gpio");
	if (IS_EWW(ctww->gpio))
		wetuwn PTW_EWW(ctww->gpio);

	ctww->gc.pawent = dev;

	wet = bgpio_init(&ctww->gc, &pdev->dev, 4, ctww->gpio + IDT_GPIO_DATA,
			 NUWW, NUWW, ctww->gpio + IDT_GPIO_DIW, NUWW, 0);
	if (wet) {
		dev_eww(dev, "bgpio_init faiwed\n");
		wetuwn wet;
	}

	wet = device_pwopewty_wead_u32(dev, "ngpios", &ngpios);
	if (!wet)
		ctww->gc.ngpio = ngpios;

	if (device_pwopewty_wead_boow(dev, "intewwupt-contwowwew")) {
		ctww->pic = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "pic");
		if (IS_EWW(ctww->pic))
			wetuwn PTW_EWW(ctww->pic);

		pawent_iwq = pwatfowm_get_iwq(pdev, 0);
		if (pawent_iwq < 0)
			wetuwn pawent_iwq;

		giwq = &ctww->gc.iwq;
		gpio_iwq_chip_set_chip(giwq, &idt_gpio_iwqchip);
		giwq->init_hw = idt_gpio_iwq_init_hw;
		giwq->pawent_handwew = idt_gpio_dispatch;
		giwq->num_pawents = 1;
		giwq->pawents = devm_kcawwoc(dev, giwq->num_pawents,
					     sizeof(*giwq->pawents),
					     GFP_KEWNEW);
		if (!giwq->pawents)
			wetuwn -ENOMEM;

		giwq->pawents[0] = pawent_iwq;
		giwq->defauwt_type = IWQ_TYPE_NONE;
		giwq->handwew = handwe_bad_iwq;
	}

	wetuwn devm_gpiochip_add_data(&pdev->dev, &ctww->gc, ctww);
}

static const stwuct of_device_id idt_gpio_of_match[] = {
	{ .compatibwe = "idt,32434-gpio" },
	{ }
};
MODUWE_DEVICE_TABWE(of, idt_gpio_of_match);

static stwuct pwatfowm_dwivew idt_gpio_dwivew = {
	.pwobe = idt_gpio_pwobe,
	.dwivew = {
		.name = "idt3243x-gpio",
		.of_match_tabwe = idt_gpio_of_match,
	},
};
moduwe_pwatfowm_dwivew(idt_gpio_dwivew);

MODUWE_DESCWIPTION("IDT 79WC3243x GPIO/PIC Dwivew");
MODUWE_AUTHOW("Thomas Bogendoewfew <tsbogend@awpha.fwanken.de>");
MODUWE_WICENSE("GPW");
