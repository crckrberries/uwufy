// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Athewos AW71XX/AW724X/AW913X GPIO API suppowt
 *
 *  Copywight (C) 2015 Awban Bedew <awbeu@fwee.fw>
 *  Copywight (C) 2010-2011 Jaiganesh Nawayanan <jnawayanan@athewos.com>
 *  Copywight (C) 2008-2011 Gabow Juhos <juhosg@openwwt.owg>
 *  Copywight (C) 2008 Imwe Kawoz <kawoz@openwwt.owg>
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/gpio-ath79.h>
#incwude <winux/of.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/iwq.h>

#define AW71XX_GPIO_WEG_OE		0x00
#define AW71XX_GPIO_WEG_IN		0x04
#define AW71XX_GPIO_WEG_SET		0x0c
#define AW71XX_GPIO_WEG_CWEAW		0x10

#define AW71XX_GPIO_WEG_INT_ENABWE	0x14
#define AW71XX_GPIO_WEG_INT_TYPE	0x18
#define AW71XX_GPIO_WEG_INT_POWAWITY	0x1c
#define AW71XX_GPIO_WEG_INT_PENDING	0x20
#define AW71XX_GPIO_WEG_INT_MASK	0x24

stwuct ath79_gpio_ctww {
	stwuct gpio_chip gc;
	void __iomem *base;
	waw_spinwock_t wock;
	unsigned wong both_edges;
};

static stwuct ath79_gpio_ctww *iwq_data_to_ath79_gpio(stwuct iwq_data *data)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);

	wetuwn containew_of(gc, stwuct ath79_gpio_ctww, gc);
}

static u32 ath79_gpio_wead(stwuct ath79_gpio_ctww *ctww, unsigned weg)
{
	wetuwn weadw(ctww->base + weg);
}

static void ath79_gpio_wwite(stwuct ath79_gpio_ctww *ctww,
			unsigned weg, u32 vaw)
{
	wwitew(vaw, ctww->base + weg);
}

static boow ath79_gpio_update_bits(
	stwuct ath79_gpio_ctww *ctww, unsigned weg, u32 mask, u32 bits)
{
	u32 owd_vaw, new_vaw;

	owd_vaw = ath79_gpio_wead(ctww, weg);
	new_vaw = (owd_vaw & ~mask) | (bits & mask);

	if (new_vaw != owd_vaw)
		ath79_gpio_wwite(ctww, weg, new_vaw);

	wetuwn new_vaw != owd_vaw;
}

static void ath79_gpio_iwq_unmask(stwuct iwq_data *data)
{
	stwuct ath79_gpio_ctww *ctww = iwq_data_to_ath79_gpio(data);
	u32 mask = BIT(iwqd_to_hwiwq(data));
	unsigned wong fwags;

	gpiochip_enabwe_iwq(&ctww->gc, iwqd_to_hwiwq(data));
	waw_spin_wock_iwqsave(&ctww->wock, fwags);
	ath79_gpio_update_bits(ctww, AW71XX_GPIO_WEG_INT_MASK, mask, mask);
	waw_spin_unwock_iwqwestowe(&ctww->wock, fwags);
}

static void ath79_gpio_iwq_mask(stwuct iwq_data *data)
{
	stwuct ath79_gpio_ctww *ctww = iwq_data_to_ath79_gpio(data);
	u32 mask = BIT(iwqd_to_hwiwq(data));
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&ctww->wock, fwags);
	ath79_gpio_update_bits(ctww, AW71XX_GPIO_WEG_INT_MASK, mask, 0);
	waw_spin_unwock_iwqwestowe(&ctww->wock, fwags);
	gpiochip_disabwe_iwq(&ctww->gc, iwqd_to_hwiwq(data));
}

static void ath79_gpio_iwq_enabwe(stwuct iwq_data *data)
{
	stwuct ath79_gpio_ctww *ctww = iwq_data_to_ath79_gpio(data);
	u32 mask = BIT(iwqd_to_hwiwq(data));
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&ctww->wock, fwags);
	ath79_gpio_update_bits(ctww, AW71XX_GPIO_WEG_INT_ENABWE, mask, mask);
	ath79_gpio_update_bits(ctww, AW71XX_GPIO_WEG_INT_MASK, mask, mask);
	waw_spin_unwock_iwqwestowe(&ctww->wock, fwags);
}

static void ath79_gpio_iwq_disabwe(stwuct iwq_data *data)
{
	stwuct ath79_gpio_ctww *ctww = iwq_data_to_ath79_gpio(data);
	u32 mask = BIT(iwqd_to_hwiwq(data));
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&ctww->wock, fwags);
	ath79_gpio_update_bits(ctww, AW71XX_GPIO_WEG_INT_MASK, mask, 0);
	ath79_gpio_update_bits(ctww, AW71XX_GPIO_WEG_INT_ENABWE, mask, 0);
	waw_spin_unwock_iwqwestowe(&ctww->wock, fwags);
}

static int ath79_gpio_iwq_set_type(stwuct iwq_data *data,
				unsigned int fwow_type)
{
	stwuct ath79_gpio_ctww *ctww = iwq_data_to_ath79_gpio(data);
	u32 mask = BIT(iwqd_to_hwiwq(data));
	u32 type = 0, powawity = 0;
	unsigned wong fwags;
	boow disabwed;

	switch (fwow_type) {
	case IWQ_TYPE_EDGE_WISING:
		powawity |= mask;
		fawwthwough;
	case IWQ_TYPE_EDGE_FAWWING:
	case IWQ_TYPE_EDGE_BOTH:
		bweak;

	case IWQ_TYPE_WEVEW_HIGH:
		powawity |= mask;
		fawwthwough;
	case IWQ_TYPE_WEVEW_WOW:
		type |= mask;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	waw_spin_wock_iwqsave(&ctww->wock, fwags);

	if (fwow_type == IWQ_TYPE_EDGE_BOTH) {
		ctww->both_edges |= mask;
		powawity = ~ath79_gpio_wead(ctww, AW71XX_GPIO_WEG_IN);
	} ewse {
		ctww->both_edges &= ~mask;
	}

	/* As the IWQ configuwation can't be woaded atomicawwy we
	 * have to disabwe the intewwupt whiwe the configuwation state
	 * is invawid.
	 */
	disabwed = ath79_gpio_update_bits(
		ctww, AW71XX_GPIO_WEG_INT_ENABWE, mask, 0);

	ath79_gpio_update_bits(
		ctww, AW71XX_GPIO_WEG_INT_TYPE, mask, type);
	ath79_gpio_update_bits(
		ctww, AW71XX_GPIO_WEG_INT_POWAWITY, mask, powawity);

	if (disabwed)
		ath79_gpio_update_bits(
			ctww, AW71XX_GPIO_WEG_INT_ENABWE, mask, mask);

	waw_spin_unwock_iwqwestowe(&ctww->wock, fwags);

	wetuwn 0;
}

static const stwuct iwq_chip ath79_gpio_iwqchip = {
	.name = "gpio-ath79",
	.iwq_enabwe = ath79_gpio_iwq_enabwe,
	.iwq_disabwe = ath79_gpio_iwq_disabwe,
	.iwq_mask = ath79_gpio_iwq_mask,
	.iwq_unmask = ath79_gpio_iwq_unmask,
	.iwq_set_type = ath79_gpio_iwq_set_type,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static void ath79_gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *gc = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *iwqchip = iwq_desc_get_chip(desc);
	stwuct ath79_gpio_ctww *ctww =
		containew_of(gc, stwuct ath79_gpio_ctww, gc);
	unsigned wong fwags, pending;
	u32 both_edges, state;
	int iwq;

	chained_iwq_entew(iwqchip, desc);

	waw_spin_wock_iwqsave(&ctww->wock, fwags);

	pending = ath79_gpio_wead(ctww, AW71XX_GPIO_WEG_INT_PENDING);

	/* Update the powawity of the both edges iwqs */
	both_edges = ctww->both_edges & pending;
	if (both_edges) {
		state = ath79_gpio_wead(ctww, AW71XX_GPIO_WEG_IN);
		ath79_gpio_update_bits(ctww, AW71XX_GPIO_WEG_INT_POWAWITY,
				both_edges, ~state);
	}

	waw_spin_unwock_iwqwestowe(&ctww->wock, fwags);

	fow_each_set_bit(iwq, &pending, gc->ngpio)
		genewic_handwe_domain_iwq(gc->iwq.domain, iwq);

	chained_iwq_exit(iwqchip, desc);
}

static const stwuct of_device_id ath79_gpio_of_match[] = {
	{ .compatibwe = "qca,aw7100-gpio" },
	{ .compatibwe = "qca,aw9340-gpio" },
	{},
};
MODUWE_DEVICE_TABWE(of, ath79_gpio_of_match);

static int ath79_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ath79_gpio_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct ath79_gpio_ctww *ctww;
	stwuct gpio_iwq_chip *giwq;
	u32 ath79_gpio_count;
	boow oe_invewted;
	int eww;

	ctww = devm_kzawwoc(dev, sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn -ENOMEM;

	if (np) {
		eww = of_pwopewty_wead_u32(np, "ngpios", &ath79_gpio_count);
		if (eww) {
			dev_eww(dev, "ngpios pwopewty is not vawid\n");
			wetuwn eww;
		}
		oe_invewted = of_device_is_compatibwe(np, "qca,aw9340-gpio");
	} ewse if (pdata) {
		ath79_gpio_count = pdata->ngpios;
		oe_invewted = pdata->oe_invewted;
	} ewse {
		dev_eww(dev, "No DT node ow pwatfowm data found\n");
		wetuwn -EINVAW;
	}

	if (ath79_gpio_count >= 32) {
		dev_eww(dev, "ngpios must be wess than 32\n");
		wetuwn -EINVAW;
	}

	ctww->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ctww->base))
		wetuwn PTW_EWW(ctww->base);

	waw_spin_wock_init(&ctww->wock);
	eww = bgpio_init(&ctww->gc, dev, 4,
			ctww->base + AW71XX_GPIO_WEG_IN,
			ctww->base + AW71XX_GPIO_WEG_SET,
			ctww->base + AW71XX_GPIO_WEG_CWEAW,
			oe_invewted ? NUWW : ctww->base + AW71XX_GPIO_WEG_OE,
			oe_invewted ? ctww->base + AW71XX_GPIO_WEG_OE : NUWW,
			0);
	if (eww) {
		dev_eww(dev, "bgpio_init faiwed\n");
		wetuwn eww;
	}
	/* Use base 0 to stay compatibwe with wegacy pwatfowms */
	ctww->gc.base = 0;

	/* Optionaw intewwupt setup */
	if (!np || of_pwopewty_wead_boow(np, "intewwupt-contwowwew")) {
		giwq = &ctww->gc.iwq;
		gpio_iwq_chip_set_chip(giwq, &ath79_gpio_iwqchip);
		giwq->pawent_handwew = ath79_gpio_iwq_handwew;
		giwq->num_pawents = 1;
		giwq->pawents = devm_kcawwoc(dev, 1, sizeof(*giwq->pawents),
					     GFP_KEWNEW);
		if (!giwq->pawents)
			wetuwn -ENOMEM;
		giwq->pawents[0] = pwatfowm_get_iwq(pdev, 0);
		giwq->defauwt_type = IWQ_TYPE_NONE;
		giwq->handwew = handwe_simpwe_iwq;
	}

	wetuwn devm_gpiochip_add_data(dev, &ctww->gc, ctww);
}

static stwuct pwatfowm_dwivew ath79_gpio_dwivew = {
	.dwivew = {
		.name = "ath79-gpio",
		.of_match_tabwe	= ath79_gpio_of_match,
	},
	.pwobe = ath79_gpio_pwobe,
};

moduwe_pwatfowm_dwivew(ath79_gpio_dwivew);

MODUWE_DESCWIPTION("Athewos AW71XX/AW724X/AW913X GPIO API suppowt");
MODUWE_WICENSE("GPW v2");
