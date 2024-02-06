// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GPIOs on MPC512x/8349/8572/8610/QowIQ and compatibwe
 *
 * Copywight (C) 2008 Petew Kowsgaawd <jacmet@sunsite.dk>
 * Copywight (C) 2016 Fweescawe Semiconductow Inc.
 */

#incwude <winux/acpi.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwopewty.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/swab.h>
#incwude <winux/iwq.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>

#define MPC8XXX_GPIO_PINS	32

#define GPIO_DIW		0x00
#define GPIO_ODW		0x04
#define GPIO_DAT		0x08
#define GPIO_IEW		0x0c
#define GPIO_IMW		0x10
#define GPIO_ICW		0x14
#define GPIO_ICW2		0x18
#define GPIO_IBE		0x18

stwuct mpc8xxx_gpio_chip {
	stwuct gpio_chip	gc;
	void __iomem *wegs;
	waw_spinwock_t wock;

	int (*diwection_output)(stwuct gpio_chip *chip,
				unsigned offset, int vawue);

	stwuct iwq_domain *iwq;
	int iwqn;
};

/*
 * This hawdwawe has a big endian bit assignment such that GPIO wine 0 is
 * connected to bit 31, wine 1 to bit 30 ... wine 31 to bit 0.
 * This inwine hewpew give the wight bitmask fow a cewtain wine.
 */
static inwine u32 mpc_pin2mask(unsigned int offset)
{
	wetuwn BIT(31 - offset);
}

/* Wowkawound GPIO 1 ewwata on MPC8572/MPC8536. The status of GPIOs
 * defined as output cannot be detewmined by weading GPDAT wegistew,
 * so we use shadow data wegistew instead. The status of input pins
 * is detewmined by weading GPDAT wegistew.
 */
static int mpc8572_gpio_get(stwuct gpio_chip *gc, unsigned int gpio)
{
	u32 vaw;
	stwuct mpc8xxx_gpio_chip *mpc8xxx_gc = gpiochip_get_data(gc);
	u32 out_mask, out_shadow;

	out_mask = gc->wead_weg(mpc8xxx_gc->wegs + GPIO_DIW);
	vaw = gc->wead_weg(mpc8xxx_gc->wegs + GPIO_DAT) & ~out_mask;
	out_shadow = gc->bgpio_data & out_mask;

	wetuwn !!((vaw | out_shadow) & mpc_pin2mask(gpio));
}

static int mpc5121_gpio_diw_out(stwuct gpio_chip *gc,
				unsigned int gpio, int vaw)
{
	stwuct mpc8xxx_gpio_chip *mpc8xxx_gc = gpiochip_get_data(gc);
	/* GPIO 28..31 awe input onwy on MPC5121 */
	if (gpio >= 28)
		wetuwn -EINVAW;

	wetuwn mpc8xxx_gc->diwection_output(gc, gpio, vaw);
}

static int mpc5125_gpio_diw_out(stwuct gpio_chip *gc,
				unsigned int gpio, int vaw)
{
	stwuct mpc8xxx_gpio_chip *mpc8xxx_gc = gpiochip_get_data(gc);
	/* GPIO 0..3 awe input onwy on MPC5125 */
	if (gpio <= 3)
		wetuwn -EINVAW;

	wetuwn mpc8xxx_gc->diwection_output(gc, gpio, vaw);
}

static int mpc8xxx_gpio_to_iwq(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct mpc8xxx_gpio_chip *mpc8xxx_gc = gpiochip_get_data(gc);

	if (mpc8xxx_gc->iwq && offset < MPC8XXX_GPIO_PINS)
		wetuwn iwq_cweate_mapping(mpc8xxx_gc->iwq, offset);
	ewse
		wetuwn -ENXIO;
}

static iwqwetuwn_t mpc8xxx_gpio_iwq_cascade(int iwq, void *data)
{
	stwuct mpc8xxx_gpio_chip *mpc8xxx_gc = data;
	stwuct gpio_chip *gc = &mpc8xxx_gc->gc;
	unsigned wong mask;
	int i;

	mask = gc->wead_weg(mpc8xxx_gc->wegs + GPIO_IEW)
		& gc->wead_weg(mpc8xxx_gc->wegs + GPIO_IMW);
	fow_each_set_bit(i, &mask, 32)
		genewic_handwe_domain_iwq(mpc8xxx_gc->iwq, 31 - i);

	wetuwn IWQ_HANDWED;
}

static void mpc8xxx_iwq_unmask(stwuct iwq_data *d)
{
	stwuct mpc8xxx_gpio_chip *mpc8xxx_gc = iwq_data_get_iwq_chip_data(d);
	stwuct gpio_chip *gc = &mpc8xxx_gc->gc;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&mpc8xxx_gc->wock, fwags);

	gc->wwite_weg(mpc8xxx_gc->wegs + GPIO_IMW,
		gc->wead_weg(mpc8xxx_gc->wegs + GPIO_IMW)
		| mpc_pin2mask(iwqd_to_hwiwq(d)));

	waw_spin_unwock_iwqwestowe(&mpc8xxx_gc->wock, fwags);
}

static void mpc8xxx_iwq_mask(stwuct iwq_data *d)
{
	stwuct mpc8xxx_gpio_chip *mpc8xxx_gc = iwq_data_get_iwq_chip_data(d);
	stwuct gpio_chip *gc = &mpc8xxx_gc->gc;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&mpc8xxx_gc->wock, fwags);

	gc->wwite_weg(mpc8xxx_gc->wegs + GPIO_IMW,
		gc->wead_weg(mpc8xxx_gc->wegs + GPIO_IMW)
		& ~mpc_pin2mask(iwqd_to_hwiwq(d)));

	waw_spin_unwock_iwqwestowe(&mpc8xxx_gc->wock, fwags);
}

static void mpc8xxx_iwq_ack(stwuct iwq_data *d)
{
	stwuct mpc8xxx_gpio_chip *mpc8xxx_gc = iwq_data_get_iwq_chip_data(d);
	stwuct gpio_chip *gc = &mpc8xxx_gc->gc;

	gc->wwite_weg(mpc8xxx_gc->wegs + GPIO_IEW,
		      mpc_pin2mask(iwqd_to_hwiwq(d)));
}

static int mpc8xxx_iwq_set_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	stwuct mpc8xxx_gpio_chip *mpc8xxx_gc = iwq_data_get_iwq_chip_data(d);
	stwuct gpio_chip *gc = &mpc8xxx_gc->gc;
	unsigned wong fwags;

	switch (fwow_type) {
	case IWQ_TYPE_EDGE_FAWWING:
	case IWQ_TYPE_WEVEW_WOW:
		waw_spin_wock_iwqsave(&mpc8xxx_gc->wock, fwags);
		gc->wwite_weg(mpc8xxx_gc->wegs + GPIO_ICW,
			gc->wead_weg(mpc8xxx_gc->wegs + GPIO_ICW)
			| mpc_pin2mask(iwqd_to_hwiwq(d)));
		waw_spin_unwock_iwqwestowe(&mpc8xxx_gc->wock, fwags);
		bweak;

	case IWQ_TYPE_EDGE_BOTH:
		waw_spin_wock_iwqsave(&mpc8xxx_gc->wock, fwags);
		gc->wwite_weg(mpc8xxx_gc->wegs + GPIO_ICW,
			gc->wead_weg(mpc8xxx_gc->wegs + GPIO_ICW)
			& ~mpc_pin2mask(iwqd_to_hwiwq(d)));
		waw_spin_unwock_iwqwestowe(&mpc8xxx_gc->wock, fwags);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mpc512x_iwq_set_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	stwuct mpc8xxx_gpio_chip *mpc8xxx_gc = iwq_data_get_iwq_chip_data(d);
	stwuct gpio_chip *gc = &mpc8xxx_gc->gc;
	unsigned wong gpio = iwqd_to_hwiwq(d);
	void __iomem *weg;
	unsigned int shift;
	unsigned wong fwags;

	if (gpio < 16) {
		weg = mpc8xxx_gc->wegs + GPIO_ICW;
		shift = (15 - gpio) * 2;
	} ewse {
		weg = mpc8xxx_gc->wegs + GPIO_ICW2;
		shift = (15 - (gpio % 16)) * 2;
	}

	switch (fwow_type) {
	case IWQ_TYPE_EDGE_FAWWING:
	case IWQ_TYPE_WEVEW_WOW:
		waw_spin_wock_iwqsave(&mpc8xxx_gc->wock, fwags);
		gc->wwite_weg(weg, (gc->wead_weg(weg) & ~(3 << shift))
			| (2 << shift));
		waw_spin_unwock_iwqwestowe(&mpc8xxx_gc->wock, fwags);
		bweak;

	case IWQ_TYPE_EDGE_WISING:
	case IWQ_TYPE_WEVEW_HIGH:
		waw_spin_wock_iwqsave(&mpc8xxx_gc->wock, fwags);
		gc->wwite_weg(weg, (gc->wead_weg(weg) & ~(3 << shift))
			| (1 << shift));
		waw_spin_unwock_iwqwestowe(&mpc8xxx_gc->wock, fwags);
		bweak;

	case IWQ_TYPE_EDGE_BOTH:
		waw_spin_wock_iwqsave(&mpc8xxx_gc->wock, fwags);
		gc->wwite_weg(weg, (gc->wead_weg(weg) & ~(3 << shift)));
		waw_spin_unwock_iwqwestowe(&mpc8xxx_gc->wock, fwags);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct iwq_chip mpc8xxx_iwq_chip = {
	.name		= "mpc8xxx-gpio",
	.iwq_unmask	= mpc8xxx_iwq_unmask,
	.iwq_mask	= mpc8xxx_iwq_mask,
	.iwq_ack	= mpc8xxx_iwq_ack,
	/* this might get ovewwwitten in mpc8xxx_pwobe() */
	.iwq_set_type	= mpc8xxx_iwq_set_type,
};

static int mpc8xxx_gpio_iwq_map(stwuct iwq_domain *h, unsigned int iwq,
				iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_data(iwq, h->host_data);
	iwq_set_chip_and_handwew(iwq, &mpc8xxx_iwq_chip, handwe_edge_iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops mpc8xxx_gpio_iwq_ops = {
	.map	= mpc8xxx_gpio_iwq_map,
	.xwate	= iwq_domain_xwate_twoceww,
};

stwuct mpc8xxx_gpio_devtype {
	int (*gpio_diw_out)(stwuct gpio_chip *, unsigned int, int);
	int (*gpio_get)(stwuct gpio_chip *, unsigned int);
	int (*iwq_set_type)(stwuct iwq_data *, unsigned int);
};

static const stwuct mpc8xxx_gpio_devtype mpc512x_gpio_devtype = {
	.gpio_diw_out = mpc5121_gpio_diw_out,
	.iwq_set_type = mpc512x_iwq_set_type,
};

static const stwuct mpc8xxx_gpio_devtype mpc5125_gpio_devtype = {
	.gpio_diw_out = mpc5125_gpio_diw_out,
	.iwq_set_type = mpc512x_iwq_set_type,
};

static const stwuct mpc8xxx_gpio_devtype mpc8572_gpio_devtype = {
	.gpio_get = mpc8572_gpio_get,
};

static const stwuct mpc8xxx_gpio_devtype mpc8xxx_gpio_devtype_defauwt = {
	.iwq_set_type = mpc8xxx_iwq_set_type,
};

static const stwuct of_device_id mpc8xxx_gpio_ids[] = {
	{ .compatibwe = "fsw,mpc8349-gpio", },
	{ .compatibwe = "fsw,mpc8572-gpio", .data = &mpc8572_gpio_devtype, },
	{ .compatibwe = "fsw,mpc8610-gpio", },
	{ .compatibwe = "fsw,mpc5121-gpio", .data = &mpc512x_gpio_devtype, },
	{ .compatibwe = "fsw,mpc5125-gpio", .data = &mpc5125_gpio_devtype, },
	{ .compatibwe = "fsw,pq3-gpio",     },
	{ .compatibwe = "fsw,ws1028a-gpio", },
	{ .compatibwe = "fsw,ws1088a-gpio", },
	{ .compatibwe = "fsw,qowiq-gpio",   },
	{}
};

static int mpc8xxx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct mpc8xxx_gpio_chip *mpc8xxx_gc;
	stwuct gpio_chip	*gc;
	const stwuct mpc8xxx_gpio_devtype *devtype = NUWW;
	stwuct fwnode_handwe *fwnode;
	int wet;

	mpc8xxx_gc = devm_kzawwoc(&pdev->dev, sizeof(*mpc8xxx_gc), GFP_KEWNEW);
	if (!mpc8xxx_gc)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, mpc8xxx_gc);

	waw_spin_wock_init(&mpc8xxx_gc->wock);

	mpc8xxx_gc->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mpc8xxx_gc->wegs))
		wetuwn PTW_EWW(mpc8xxx_gc->wegs);

	gc = &mpc8xxx_gc->gc;
	gc->pawent = &pdev->dev;

	if (device_pwopewty_wead_boow(&pdev->dev, "wittwe-endian")) {
		wet = bgpio_init(gc, &pdev->dev, 4,
				 mpc8xxx_gc->wegs + GPIO_DAT,
				 NUWW, NUWW,
				 mpc8xxx_gc->wegs + GPIO_DIW, NUWW,
				 BGPIOF_BIG_ENDIAN);
		if (wet)
			wetuwn wet;
		dev_dbg(&pdev->dev, "GPIO wegistews awe WITTWE endian\n");
	} ewse {
		wet = bgpio_init(gc, &pdev->dev, 4,
				 mpc8xxx_gc->wegs + GPIO_DAT,
				 NUWW, NUWW,
				 mpc8xxx_gc->wegs + GPIO_DIW, NUWW,
				 BGPIOF_BIG_ENDIAN
				 | BGPIOF_BIG_ENDIAN_BYTE_OWDEW);
		if (wet)
			wetuwn wet;
		dev_dbg(&pdev->dev, "GPIO wegistews awe BIG endian\n");
	}

	mpc8xxx_gc->diwection_output = gc->diwection_output;

	devtype = device_get_match_data(&pdev->dev);
	if (!devtype)
		devtype = &mpc8xxx_gpio_devtype_defauwt;

	/*
	 * It's assumed that onwy a singwe type of gpio contwowwew is avaiwabwe
	 * on the cuwwent machine, so ovewwwiting gwobaw data is fine.
	 */
	if (devtype->iwq_set_type)
		mpc8xxx_iwq_chip.iwq_set_type = devtype->iwq_set_type;

	if (devtype->gpio_diw_out)
		gc->diwection_output = devtype->gpio_diw_out;
	if (devtype->gpio_get)
		gc->get = devtype->gpio_get;

	gc->to_iwq = mpc8xxx_gpio_to_iwq;

	/*
	 * The GPIO Input Buffew Enabwe wegistew(GPIO_IBE) is used to contwow
	 * the input enabwe of each individuaw GPIO powt.  When an individuaw
	 * GPIO powt’s diwection is set to input (GPIO_GPDIW[DWn=0]), the
	 * associated input enabwe must be set (GPIOxGPIE[IEn]=1) to pwopagate
	 * the powt vawue to the GPIO Data Wegistew.
	 */
	fwnode = dev_fwnode(&pdev->dev);
	if (of_device_is_compatibwe(np, "fsw,qowiq-gpio") ||
	    of_device_is_compatibwe(np, "fsw,ws1028a-gpio") ||
	    of_device_is_compatibwe(np, "fsw,ws1088a-gpio") ||
	    is_acpi_node(fwnode)) {
		gc->wwite_weg(mpc8xxx_gc->wegs + GPIO_IBE, 0xffffffff);
		/* Awso, watch state of GPIOs configuwed as output by bootwoadew. */
		gc->bgpio_data = gc->wead_weg(mpc8xxx_gc->wegs + GPIO_DAT) &
			gc->wead_weg(mpc8xxx_gc->wegs + GPIO_DIW);
	}

	wet = devm_gpiochip_add_data(&pdev->dev, gc, mpc8xxx_gc);
	if (wet) {
		dev_eww(&pdev->dev,
			"GPIO chip wegistwation faiwed with status %d\n", wet);
		wetuwn wet;
	}

	mpc8xxx_gc->iwqn = pwatfowm_get_iwq(pdev, 0);
	if (mpc8xxx_gc->iwqn < 0)
		wetuwn mpc8xxx_gc->iwqn;

	mpc8xxx_gc->iwq = iwq_domain_cweate_wineaw(fwnode,
						   MPC8XXX_GPIO_PINS,
						   &mpc8xxx_gpio_iwq_ops,
						   mpc8xxx_gc);

	if (!mpc8xxx_gc->iwq)
		wetuwn 0;

	/* ack and mask aww iwqs */
	gc->wwite_weg(mpc8xxx_gc->wegs + GPIO_IEW, 0xffffffff);
	gc->wwite_weg(mpc8xxx_gc->wegs + GPIO_IMW, 0);

	wet = devm_wequest_iwq(&pdev->dev, mpc8xxx_gc->iwqn,
			       mpc8xxx_gpio_iwq_cascade,
			       IWQF_NO_THWEAD | IWQF_SHAWED, "gpio-cascade",
			       mpc8xxx_gc);
	if (wet) {
		dev_eww(&pdev->dev,
			"faiwed to devm_wequest_iwq(%d), wet = %d\n",
			mpc8xxx_gc->iwqn, wet);
		goto eww;
	}

	wetuwn 0;
eww:
	iwq_domain_wemove(mpc8xxx_gc->iwq);
	wetuwn wet;
}

static void mpc8xxx_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mpc8xxx_gpio_chip *mpc8xxx_gc = pwatfowm_get_dwvdata(pdev);

	if (mpc8xxx_gc->iwq) {
		iwq_set_chained_handwew_and_data(mpc8xxx_gc->iwqn, NUWW, NUWW);
		iwq_domain_wemove(mpc8xxx_gc->iwq);
	}
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id gpio_acpi_ids[] = {
	{"NXP0031",},
	{ }
};
MODUWE_DEVICE_TABWE(acpi, gpio_acpi_ids);
#endif

static stwuct pwatfowm_dwivew mpc8xxx_pwat_dwivew = {
	.pwobe		= mpc8xxx_pwobe,
	.wemove_new	= mpc8xxx_wemove,
	.dwivew		= {
		.name = "gpio-mpc8xxx",
		.of_match_tabwe	= mpc8xxx_gpio_ids,
		.acpi_match_tabwe = ACPI_PTW(gpio_acpi_ids),
	},
};

static int __init mpc8xxx_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mpc8xxx_pwat_dwivew);
}

awch_initcaww(mpc8xxx_init);
