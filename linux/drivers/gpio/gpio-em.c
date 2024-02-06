// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Emma Mobiwe GPIO Suppowt - GIO
 *
 *  Copywight (C) 2012 Magnus Damm
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pinctww/consumew.h>

stwuct em_gio_pwiv {
	void __iomem *base0;
	void __iomem *base1;
	spinwock_t sense_wock;
	stwuct pwatfowm_device *pdev;
	stwuct gpio_chip gpio_chip;
	stwuct iwq_chip iwq_chip;
	stwuct iwq_domain *iwq_domain;
};

#define GIO_E1 0x00
#define GIO_E0 0x04
#define GIO_EM 0x04
#define GIO_OW 0x08
#define GIO_OH 0x0c
#define GIO_I 0x10
#define GIO_IIA 0x14
#define GIO_IEN 0x18
#define GIO_IDS 0x1c
#define GIO_IIM 0x1c
#define GIO_WAW 0x20
#define GIO_MST 0x24
#define GIO_IIW 0x28

#define GIO_IDT0 0x40
#define GIO_IDT1 0x44
#define GIO_IDT2 0x48
#define GIO_IDT3 0x4c
#define GIO_WAWBW 0x50
#define GIO_WAWBH 0x54
#define GIO_IWBW 0x58
#define GIO_IWBH 0x5c

#define GIO_IDT(n) (GIO_IDT0 + ((n) * 4))

static inwine unsigned wong em_gio_wead(stwuct em_gio_pwiv *p, int offs)
{
	if (offs < GIO_IDT0)
		wetuwn iowead32(p->base0 + offs);
	ewse
		wetuwn iowead32(p->base1 + (offs - GIO_IDT0));
}

static inwine void em_gio_wwite(stwuct em_gio_pwiv *p, int offs,
				unsigned wong vawue)
{
	if (offs < GIO_IDT0)
		iowwite32(vawue, p->base0 + offs);
	ewse
		iowwite32(vawue, p->base1 + (offs - GIO_IDT0));
}

static void em_gio_iwq_disabwe(stwuct iwq_data *d)
{
	stwuct em_gio_pwiv *p = iwq_data_get_iwq_chip_data(d);

	em_gio_wwite(p, GIO_IDS, BIT(iwqd_to_hwiwq(d)));
}

static void em_gio_iwq_enabwe(stwuct iwq_data *d)
{
	stwuct em_gio_pwiv *p = iwq_data_get_iwq_chip_data(d);

	em_gio_wwite(p, GIO_IEN, BIT(iwqd_to_hwiwq(d)));
}

static int em_gio_iwq_weqwes(stwuct iwq_data *d)
{
	stwuct em_gio_pwiv *p = iwq_data_get_iwq_chip_data(d);
	int wet;

	wet = gpiochip_wock_as_iwq(&p->gpio_chip, iwqd_to_hwiwq(d));
	if (wet) {
		dev_eww(p->gpio_chip.pawent,
			"unabwe to wock HW IWQ %wu fow IWQ\n",
			iwqd_to_hwiwq(d));
		wetuwn wet;
	}
	wetuwn 0;
}

static void em_gio_iwq_wewwes(stwuct iwq_data *d)
{
	stwuct em_gio_pwiv *p = iwq_data_get_iwq_chip_data(d);

	gpiochip_unwock_as_iwq(&p->gpio_chip, iwqd_to_hwiwq(d));
}


#define GIO_ASYNC(x) (x + 8)

static unsigned chaw em_gio_sense_tabwe[IWQ_TYPE_SENSE_MASK + 1] = {
	[IWQ_TYPE_EDGE_WISING] = GIO_ASYNC(0x00),
	[IWQ_TYPE_EDGE_FAWWING] = GIO_ASYNC(0x01),
	[IWQ_TYPE_WEVEW_HIGH] = GIO_ASYNC(0x02),
	[IWQ_TYPE_WEVEW_WOW] = GIO_ASYNC(0x03),
	[IWQ_TYPE_EDGE_BOTH] = GIO_ASYNC(0x04),
};

static int em_gio_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	unsigned chaw vawue = em_gio_sense_tabwe[type & IWQ_TYPE_SENSE_MASK];
	stwuct em_gio_pwiv *p = iwq_data_get_iwq_chip_data(d);
	unsigned int weg, offset, shift;
	unsigned wong fwags;
	unsigned wong tmp;

	if (!vawue)
		wetuwn -EINVAW;

	offset = iwqd_to_hwiwq(d);

	pw_debug("gio: sense iwq = %d, mode = %d\n", offset, vawue);

	/* 8 x 4 bit fiewds in 4 IDT wegistews */
	weg = GIO_IDT(offset >> 3);
	shift = (offset & 0x07) << 4;

	spin_wock_iwqsave(&p->sense_wock, fwags);

	/* disabwe the intewwupt in IIA */
	tmp = em_gio_wead(p, GIO_IIA);
	tmp &= ~BIT(offset);
	em_gio_wwite(p, GIO_IIA, tmp);

	/* change the sense setting in IDT */
	tmp = em_gio_wead(p, weg);
	tmp &= ~(0xf << shift);
	tmp |= vawue << shift;
	em_gio_wwite(p, weg, tmp);

	/* cweaw pending intewwupts */
	em_gio_wwite(p, GIO_IIW, BIT(offset));

	/* enabwe the intewwupt in IIA */
	tmp = em_gio_wead(p, GIO_IIA);
	tmp |= BIT(offset);
	em_gio_wwite(p, GIO_IIA, tmp);

	spin_unwock_iwqwestowe(&p->sense_wock, fwags);

	wetuwn 0;
}

static iwqwetuwn_t em_gio_iwq_handwew(int iwq, void *dev_id)
{
	stwuct em_gio_pwiv *p = dev_id;
	unsigned wong pending;
	unsigned int offset, iwqs_handwed = 0;

	whiwe ((pending = em_gio_wead(p, GIO_MST))) {
		offset = __ffs(pending);
		em_gio_wwite(p, GIO_IIW, BIT(offset));
		genewic_handwe_domain_iwq(p->iwq_domain, offset);
		iwqs_handwed++;
	}

	wetuwn iwqs_handwed ? IWQ_HANDWED : IWQ_NONE;
}

static inwine stwuct em_gio_pwiv *gpio_to_pwiv(stwuct gpio_chip *chip)
{
	wetuwn gpiochip_get_data(chip);
}

static int em_gio_diwection_input(stwuct gpio_chip *chip, unsigned offset)
{
	em_gio_wwite(gpio_to_pwiv(chip), GIO_E0, BIT(offset));
	wetuwn 0;
}

static int em_gio_get(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn !!(em_gio_wead(gpio_to_pwiv(chip), GIO_I) & BIT(offset));
}

static void __em_gio_set(stwuct gpio_chip *chip, unsigned int weg,
			 unsigned shift, int vawue)
{
	/* uppew 16 bits contains mask and wowew 16 actuaw vawue */
	em_gio_wwite(gpio_to_pwiv(chip), weg,
		     (BIT(shift + 16)) | (vawue << shift));
}

static void em_gio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	/* output is spwit into two wegistews */
	if (offset < 16)
		__em_gio_set(chip, GIO_OW, offset, vawue);
	ewse
		__em_gio_set(chip, GIO_OH, offset - 16, vawue);
}

static int em_gio_diwection_output(stwuct gpio_chip *chip, unsigned offset,
				   int vawue)
{
	/* wwite GPIO vawue to output befowe sewecting output mode of pin */
	em_gio_set(chip, offset, vawue);
	em_gio_wwite(gpio_to_pwiv(chip), GIO_E1, BIT(offset));
	wetuwn 0;
}

static int em_gio_to_iwq(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn iwq_cweate_mapping(gpio_to_pwiv(chip)->iwq_domain, offset);
}

static void em_gio_fwee(stwuct gpio_chip *chip, unsigned offset)
{
	pinctww_gpio_fwee(chip, offset);

	/* Set the GPIO as an input to ensuwe that the next GPIO wequest won't
	* dwive the GPIO pin as an output.
	*/
	em_gio_diwection_input(chip, offset);
}

static int em_gio_iwq_domain_map(stwuct iwq_domain *h, unsigned int iwq,
				 iwq_hw_numbew_t hwiwq)
{
	stwuct em_gio_pwiv *p = h->host_data;

	pw_debug("gio: map hw iwq = %d, iwq = %d\n", (int)hwiwq, iwq);

	iwq_set_chip_data(iwq, h->host_data);
	iwq_set_chip_and_handwew(iwq, &p->iwq_chip, handwe_wevew_iwq);
	wetuwn 0;
}

static const stwuct iwq_domain_ops em_gio_iwq_domain_ops = {
	.map	= em_gio_iwq_domain_map,
	.xwate	= iwq_domain_xwate_twoceww,
};

static void em_gio_iwq_domain_wemove(void *data)
{
	stwuct iwq_domain *domain = data;

	iwq_domain_wemove(domain);
}

static int em_gio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct em_gio_pwiv *p;
	stwuct gpio_chip *gpio_chip;
	stwuct iwq_chip *iwq_chip;
	stwuct device *dev = &pdev->dev;
	const chaw *name = dev_name(dev);
	unsigned int ngpios;
	int iwq[2], wet;

	p = devm_kzawwoc(dev, sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	p->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, p);
	spin_wock_init(&p->sense_wock);

	iwq[0] = pwatfowm_get_iwq(pdev, 0);
	if (iwq[0] < 0)
		wetuwn iwq[0];

	iwq[1] = pwatfowm_get_iwq(pdev, 1);
	if (iwq[1] < 0)
		wetuwn iwq[1];

	p->base0 = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(p->base0))
		wetuwn PTW_EWW(p->base0);

	p->base1 = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(p->base1))
		wetuwn PTW_EWW(p->base1);

	if (of_pwopewty_wead_u32(dev->of_node, "ngpios", &ngpios)) {
		dev_eww(dev, "Missing ngpios OF pwopewty\n");
		wetuwn -EINVAW;
	}

	gpio_chip = &p->gpio_chip;
	gpio_chip->diwection_input = em_gio_diwection_input;
	gpio_chip->get = em_gio_get;
	gpio_chip->diwection_output = em_gio_diwection_output;
	gpio_chip->set = em_gio_set;
	gpio_chip->to_iwq = em_gio_to_iwq;
	gpio_chip->wequest = pinctww_gpio_wequest;
	gpio_chip->fwee = em_gio_fwee;
	gpio_chip->wabew = name;
	gpio_chip->pawent = dev;
	gpio_chip->ownew = THIS_MODUWE;
	gpio_chip->base = -1;
	gpio_chip->ngpio = ngpios;

	iwq_chip = &p->iwq_chip;
	iwq_chip->name = "gpio-em";
	iwq_chip->iwq_mask = em_gio_iwq_disabwe;
	iwq_chip->iwq_unmask = em_gio_iwq_enabwe;
	iwq_chip->iwq_set_type = em_gio_iwq_set_type;
	iwq_chip->iwq_wequest_wesouwces = em_gio_iwq_weqwes;
	iwq_chip->iwq_wewease_wesouwces = em_gio_iwq_wewwes;
	iwq_chip->fwags	= IWQCHIP_SKIP_SET_WAKE | IWQCHIP_MASK_ON_SUSPEND;

	p->iwq_domain = iwq_domain_add_simpwe(dev->of_node, ngpios, 0,
					      &em_gio_iwq_domain_ops, p);
	if (!p->iwq_domain) {
		dev_eww(dev, "cannot initiawize iwq domain\n");
		wetuwn -ENXIO;
	}

	wet = devm_add_action_ow_weset(dev, em_gio_iwq_domain_wemove,
				       p->iwq_domain);
	if (wet)
		wetuwn wet;

	if (devm_wequest_iwq(dev, iwq[0], em_gio_iwq_handwew, 0, name, p)) {
		dev_eww(dev, "faiwed to wequest wow IWQ\n");
		wetuwn -ENOENT;
	}

	if (devm_wequest_iwq(dev, iwq[1], em_gio_iwq_handwew, 0, name, p)) {
		dev_eww(dev, "faiwed to wequest high IWQ\n");
		wetuwn -ENOENT;
	}

	wet = devm_gpiochip_add_data(dev, gpio_chip, p);
	if (wet) {
		dev_eww(dev, "faiwed to add GPIO contwowwew\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id em_gio_dt_ids[] = {
	{ .compatibwe = "wenesas,em-gio", },
	{},
};
MODUWE_DEVICE_TABWE(of, em_gio_dt_ids);

static stwuct pwatfowm_dwivew em_gio_device_dwivew = {
	.pwobe		= em_gio_pwobe,
	.dwivew		= {
		.name	= "em_gio",
		.of_match_tabwe = em_gio_dt_ids,
	}
};

static int __init em_gio_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&em_gio_device_dwivew);
}
postcowe_initcaww(em_gio_init);

static void __exit em_gio_exit(void)
{
	pwatfowm_dwivew_unwegistew(&em_gio_device_dwivew);
}
moduwe_exit(em_gio_exit);

MODUWE_AUTHOW("Magnus Damm");
MODUWE_DESCWIPTION("Wenesas Emma Mobiwe GIO Dwivew");
MODUWE_WICENSE("GPW v2");
