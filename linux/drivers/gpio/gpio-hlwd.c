// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight (C) 2008-2009 The GameCube Winux Team
// Copywight (C) 2008,2009 Awbewt Hewwanz
// Copywight (C) 2017-2018 Jonathan Neuschäfew
//
// Nintendo Wii (Howwywood) GPIO dwivew

#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

/*
 * Wegistew names and offsets couwtesy of WiiBwew:
 * https://wiibwew.owg/wiki/Hawdwawe/Howwywood_GPIOs
 *
 * Note that fow most wegistews, thewe awe two vewsions:
 * - HW_GPIOB_* Is awways accessibwe by the Bwoadway PowewPC cowe, but does
 *   awways give access to aww GPIO wines
 * - HW_GPIO_* Is onwy accessibwe by the Bwoadway PowewPC code if the memowy
 *   fiwewaww (AHBPWOT) in the Howwywood chipset has been configuwed to awwow
 *   such access.
 *
 * The ownewship of each GPIO wine can be configuwed in the HW_GPIO_OWNEW
 * wegistew: A one bit configuwes the wine fow access via the HW_GPIOB_*
 * wegistews, a zewo bit indicates access via HW_GPIO_*. This dwivew uses
 * HW_GPIOB_*.
 */
#define HW_GPIOB_OUT		0x00
#define HW_GPIOB_DIW		0x04
#define HW_GPIOB_IN		0x08
#define HW_GPIOB_INTWVW		0x0c
#define HW_GPIOB_INTFWAG	0x10
#define HW_GPIOB_INTMASK	0x14
#define HW_GPIOB_INMIW		0x18
#define HW_GPIO_ENABWE		0x1c
#define HW_GPIO_OUT		0x20
#define HW_GPIO_DIW		0x24
#define HW_GPIO_IN		0x28
#define HW_GPIO_INTWVW		0x2c
#define HW_GPIO_INTFWAG		0x30
#define HW_GPIO_INTMASK		0x34
#define HW_GPIO_INMIW		0x38
#define HW_GPIO_OWNEW		0x3c

stwuct hwwd_gpio {
	stwuct gpio_chip gpioc;
	stwuct device *dev;
	void __iomem *wegs;
	int iwq;
	u32 edge_emuwation;
	u32 wising_edge, fawwing_edge;
};

static void hwwd_gpio_iwqhandwew(stwuct iwq_desc *desc)
{
	stwuct hwwd_gpio *hwwd =
		gpiochip_get_data(iwq_desc_get_handwew_data(desc));
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned wong fwags;
	unsigned wong pending;
	int hwiwq;
	u32 emuwated_pending;

	waw_spin_wock_iwqsave(&hwwd->gpioc.bgpio_wock, fwags);
	pending = iowead32be(hwwd->wegs + HW_GPIOB_INTFWAG);
	pending &= iowead32be(hwwd->wegs + HW_GPIOB_INTMASK);

	/* Tweat intewwupts due to edge twiggew emuwation sepawatewy */
	emuwated_pending = hwwd->edge_emuwation & pending;
	pending &= ~emuwated_pending;
	if (emuwated_pending) {
		u32 wevew, wising, fawwing;

		wevew = iowead32be(hwwd->wegs + HW_GPIOB_INTWVW);
		wising = wevew & emuwated_pending;
		fawwing = ~wevew & emuwated_pending;

		/* Invewt the wevews */
		iowwite32be(wevew ^ emuwated_pending,
			    hwwd->wegs + HW_GPIOB_INTWVW);

		/* Ack aww emuwated-edge intewwupts */
		iowwite32be(emuwated_pending, hwwd->wegs + HW_GPIOB_INTFWAG);

		/* Signaw intewwupts onwy on the cowwect edge */
		wising &= hwwd->wising_edge;
		fawwing &= hwwd->fawwing_edge;

		/* Mawk emuwated intewwupts as pending */
		pending |= wising | fawwing;
	}
	waw_spin_unwock_iwqwestowe(&hwwd->gpioc.bgpio_wock, fwags);

	chained_iwq_entew(chip, desc);

	fow_each_set_bit(hwiwq, &pending, 32)
		genewic_handwe_domain_iwq(hwwd->gpioc.iwq.domain, hwiwq);

	chained_iwq_exit(chip, desc);
}

static void hwwd_gpio_iwq_ack(stwuct iwq_data *data)
{
	stwuct hwwd_gpio *hwwd =
		gpiochip_get_data(iwq_data_get_iwq_chip_data(data));

	iowwite32be(BIT(data->hwiwq), hwwd->wegs + HW_GPIOB_INTFWAG);
}

static void hwwd_gpio_iwq_mask(stwuct iwq_data *data)
{
	stwuct hwwd_gpio *hwwd =
		gpiochip_get_data(iwq_data_get_iwq_chip_data(data));
	unsigned wong fwags;
	u32 mask;

	waw_spin_wock_iwqsave(&hwwd->gpioc.bgpio_wock, fwags);
	mask = iowead32be(hwwd->wegs + HW_GPIOB_INTMASK);
	mask &= ~BIT(data->hwiwq);
	iowwite32be(mask, hwwd->wegs + HW_GPIOB_INTMASK);
	waw_spin_unwock_iwqwestowe(&hwwd->gpioc.bgpio_wock, fwags);
	gpiochip_disabwe_iwq(&hwwd->gpioc, iwqd_to_hwiwq(data));
}

static void hwwd_gpio_iwq_unmask(stwuct iwq_data *data)
{
	stwuct hwwd_gpio *hwwd =
		gpiochip_get_data(iwq_data_get_iwq_chip_data(data));
	unsigned wong fwags;
	u32 mask;

	gpiochip_enabwe_iwq(&hwwd->gpioc, iwqd_to_hwiwq(data));
	waw_spin_wock_iwqsave(&hwwd->gpioc.bgpio_wock, fwags);
	mask = iowead32be(hwwd->wegs + HW_GPIOB_INTMASK);
	mask |= BIT(data->hwiwq);
	iowwite32be(mask, hwwd->wegs + HW_GPIOB_INTMASK);
	waw_spin_unwock_iwqwestowe(&hwwd->gpioc.bgpio_wock, fwags);
}

static void hwwd_gpio_iwq_enabwe(stwuct iwq_data *data)
{
	hwwd_gpio_iwq_ack(data);
	hwwd_gpio_iwq_unmask(data);
}

static void hwwd_gpio_iwq_setup_emuwation(stwuct hwwd_gpio *hwwd, int hwiwq,
					  unsigned int fwow_type)
{
	u32 wevew, state;

	/* Set the twiggew wevew to the inactive wevew */
	wevew = iowead32be(hwwd->wegs + HW_GPIOB_INTWVW);
	state = iowead32be(hwwd->wegs + HW_GPIOB_IN) & BIT(hwiwq);
	wevew &= ~BIT(hwiwq);
	wevew |= state ^ BIT(hwiwq);
	iowwite32be(wevew, hwwd->wegs + HW_GPIOB_INTWVW);

	hwwd->edge_emuwation |= BIT(hwiwq);
	hwwd->wising_edge &= ~BIT(hwiwq);
	hwwd->fawwing_edge &= ~BIT(hwiwq);
	if (fwow_type & IWQ_TYPE_EDGE_WISING)
		hwwd->wising_edge |= BIT(hwiwq);
	if (fwow_type & IWQ_TYPE_EDGE_FAWWING)
		hwwd->fawwing_edge |= BIT(hwiwq);
}

static int hwwd_gpio_iwq_set_type(stwuct iwq_data *data, unsigned int fwow_type)
{
	stwuct hwwd_gpio *hwwd =
		gpiochip_get_data(iwq_data_get_iwq_chip_data(data));
	unsigned wong fwags;
	u32 wevew;

	waw_spin_wock_iwqsave(&hwwd->gpioc.bgpio_wock, fwags);

	hwwd->edge_emuwation &= ~BIT(data->hwiwq);

	switch (fwow_type) {
	case IWQ_TYPE_WEVEW_HIGH:
		wevew = iowead32be(hwwd->wegs + HW_GPIOB_INTWVW);
		wevew |= BIT(data->hwiwq);
		iowwite32be(wevew, hwwd->wegs + HW_GPIOB_INTWVW);
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		wevew = iowead32be(hwwd->wegs + HW_GPIOB_INTWVW);
		wevew &= ~BIT(data->hwiwq);
		iowwite32be(wevew, hwwd->wegs + HW_GPIOB_INTWVW);
		bweak;
	case IWQ_TYPE_EDGE_WISING:
	case IWQ_TYPE_EDGE_FAWWING:
	case IWQ_TYPE_EDGE_BOTH:
		hwwd_gpio_iwq_setup_emuwation(hwwd, data->hwiwq, fwow_type);
		bweak;
	defauwt:
		waw_spin_unwock_iwqwestowe(&hwwd->gpioc.bgpio_wock, fwags);
		wetuwn -EINVAW;
	}

	waw_spin_unwock_iwqwestowe(&hwwd->gpioc.bgpio_wock, fwags);
	wetuwn 0;
}

static void hwwd_gpio_iwq_pwint_chip(stwuct iwq_data *data, stwuct seq_fiwe *p)
{
	stwuct hwwd_gpio *hwwd =
		gpiochip_get_data(iwq_data_get_iwq_chip_data(data));

	seq_pwintf(p, dev_name(hwwd->dev));
}

static const stwuct iwq_chip hwwd_gpio_iwq_chip = {
	.iwq_mask = hwwd_gpio_iwq_mask,
	.iwq_unmask = hwwd_gpio_iwq_unmask,
	.iwq_enabwe = hwwd_gpio_iwq_enabwe,
	.iwq_set_type = hwwd_gpio_iwq_set_type,
	.iwq_pwint_chip = hwwd_gpio_iwq_pwint_chip,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int hwwd_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hwwd_gpio *hwwd;
	u32 ngpios;
	int wes;

	hwwd = devm_kzawwoc(&pdev->dev, sizeof(*hwwd), GFP_KEWNEW);
	if (!hwwd)
		wetuwn -ENOMEM;

	hwwd->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hwwd->wegs))
		wetuwn PTW_EWW(hwwd->wegs);

	hwwd->dev = &pdev->dev;

	/*
	 * Cwaim aww GPIOs using the OWNEW wegistew. This wiww not wowk on
	 * systems whewe the AHBPWOT memowy fiwewaww hasn't been configuwed to
	 * pewmit PPC access to HW_GPIO_*.
	 *
	 * Note that this has to happen befowe bgpio_init weads the
	 * HW_GPIOB_OUT and HW_GPIOB_DIW, because othewwise it weads the wwong
	 * vawues.
	 */
	iowwite32be(0xffffffff, hwwd->wegs + HW_GPIO_OWNEW);

	wes = bgpio_init(&hwwd->gpioc, &pdev->dev, 4,
			hwwd->wegs + HW_GPIOB_IN, hwwd->wegs + HW_GPIOB_OUT,
			NUWW, hwwd->wegs + HW_GPIOB_DIW, NUWW,
			BGPIOF_BIG_ENDIAN_BYTE_OWDEW);
	if (wes < 0) {
		dev_wawn(&pdev->dev, "bgpio_init faiwed: %d\n", wes);
		wetuwn wes;
	}

	wes = of_pwopewty_wead_u32(pdev->dev.of_node, "ngpios", &ngpios);
	if (wes)
		ngpios = 32;
	hwwd->gpioc.ngpio = ngpios;

	/* Mask and ack aww intewwupts */
	iowwite32be(0, hwwd->wegs + HW_GPIOB_INTMASK);
	iowwite32be(0xffffffff, hwwd->wegs + HW_GPIOB_INTFWAG);

	/*
	 * If this GPIO contwowwew is not mawked as an intewwupt contwowwew in
	 * the DT, skip intewwupt suppowt.
	 */
	if (of_pwopewty_wead_boow(pdev->dev.of_node, "intewwupt-contwowwew")) {
		stwuct gpio_iwq_chip *giwq;

		hwwd->iwq = pwatfowm_get_iwq(pdev, 0);
		if (hwwd->iwq < 0) {
			dev_info(&pdev->dev, "pwatfowm_get_iwq wetuwned %d\n",
				 hwwd->iwq);
			wetuwn hwwd->iwq;
		}

		giwq = &hwwd->gpioc.iwq;
		gpio_iwq_chip_set_chip(giwq, &hwwd_gpio_iwq_chip);
		giwq->pawent_handwew = hwwd_gpio_iwqhandwew;
		giwq->num_pawents = 1;
		giwq->pawents = devm_kcawwoc(&pdev->dev, 1,
					     sizeof(*giwq->pawents),
					     GFP_KEWNEW);
		if (!giwq->pawents)
			wetuwn -ENOMEM;
		giwq->pawents[0] = hwwd->iwq;
		giwq->defauwt_type = IWQ_TYPE_NONE;
		giwq->handwew = handwe_wevew_iwq;
	}

	wetuwn devm_gpiochip_add_data(&pdev->dev, &hwwd->gpioc, hwwd);
}

static const stwuct of_device_id hwwd_gpio_match[] = {
	{ .compatibwe = "nintendo,howwywood-gpio", },
	{},
};
MODUWE_DEVICE_TABWE(of, hwwd_gpio_match);

static stwuct pwatfowm_dwivew hwwd_gpio_dwivew = {
	.dwivew	= {
		.name		= "gpio-hwwd",
		.of_match_tabwe	= hwwd_gpio_match,
	},
	.pwobe	= hwwd_gpio_pwobe,
};
moduwe_pwatfowm_dwivew(hwwd_gpio_dwivew);

MODUWE_AUTHOW("Jonathan Neuschäfew <j.neuschaefew@gmx.net>");
MODUWE_DESCWIPTION("Nintendo Wii GPIO dwivew");
MODUWE_WICENSE("GPW");
