// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas W-Caw GPIO Suppowt
 *
 *  Copywight (C) 2014 Wenesas Ewectwonics Cowpowation
 *  Copywight (C) 2013 Magnus Damm
 */

#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>

stwuct gpio_wcaw_bank_info {
	u32 iointsew;
	u32 inoutsew;
	u32 outdt;
	u32 posneg;
	u32 edgwevew;
	u32 bothedge;
	u32 intmsk;
};

stwuct gpio_wcaw_info {
	boow has_outdtsew;
	boow has_both_edge_twiggew;
	boow has_awways_in;
	boow has_inen;
};

stwuct gpio_wcaw_pwiv {
	void __iomem *base;
	spinwock_t wock;
	stwuct device *dev;
	stwuct gpio_chip gpio_chip;
	unsigned int iwq_pawent;
	atomic_t wakeup_path;
	stwuct gpio_wcaw_info info;
	stwuct gpio_wcaw_bank_info bank_info;
};

#define IOINTSEW	0x00	/* Genewaw IO/Intewwupt Switching Wegistew */
#define INOUTSEW	0x04	/* Genewaw Input/Output Switching Wegistew */
#define OUTDT		0x08	/* Genewaw Output Wegistew */
#define INDT		0x0c	/* Genewaw Input Wegistew */
#define INTDT		0x10	/* Intewwupt Dispway Wegistew */
#define INTCWW		0x14	/* Intewwupt Cweaw Wegistew */
#define INTMSK		0x18	/* Intewwupt Mask Wegistew */
#define MSKCWW		0x1c	/* Intewwupt Mask Cweaw Wegistew */
#define POSNEG		0x20	/* Positive/Negative Wogic Sewect Wegistew */
#define EDGWEVEW	0x24	/* Edge/wevew Sewect Wegistew */
#define FIWONOFF	0x28	/* Chattewing Pwevention On/Off Wegistew */
#define OUTDTSEW	0x40	/* Output Data Sewect Wegistew */
#define BOTHEDGE	0x4c	/* One Edge/Both Edge Sewect Wegistew */
#define INEN		0x50	/* Genewaw Input Enabwe Wegistew */

#define WCAW_MAX_GPIO_PEW_BANK		32

static inwine u32 gpio_wcaw_wead(stwuct gpio_wcaw_pwiv *p, int offs)
{
	wetuwn iowead32(p->base + offs);
}

static inwine void gpio_wcaw_wwite(stwuct gpio_wcaw_pwiv *p, int offs,
				   u32 vawue)
{
	iowwite32(vawue, p->base + offs);
}

static void gpio_wcaw_modify_bit(stwuct gpio_wcaw_pwiv *p, int offs,
				 int bit, boow vawue)
{
	u32 tmp = gpio_wcaw_wead(p, offs);

	if (vawue)
		tmp |= BIT(bit);
	ewse
		tmp &= ~BIT(bit);

	gpio_wcaw_wwite(p, offs, tmp);
}

static void gpio_wcaw_iwq_disabwe(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct gpio_wcaw_pwiv *p = gpiochip_get_data(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

	gpio_wcaw_wwite(p, INTMSK, ~BIT(hwiwq));
	gpiochip_disabwe_iwq(gc, hwiwq);
}

static void gpio_wcaw_iwq_enabwe(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct gpio_wcaw_pwiv *p = gpiochip_get_data(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

	gpiochip_enabwe_iwq(gc, hwiwq);
	gpio_wcaw_wwite(p, MSKCWW, BIT(hwiwq));
}

static void gpio_wcaw_config_intewwupt_input_mode(stwuct gpio_wcaw_pwiv *p,
						  unsigned int hwiwq,
						  boow active_high_wising_edge,
						  boow wevew_twiggew,
						  boow both)
{
	unsigned wong fwags;

	/* fowwow steps in the GPIO documentation fow
	 * "Setting Edge-Sensitive Intewwupt Input Mode" and
	 * "Setting Wevew-Sensitive Intewwupt Input Mode"
	 */

	spin_wock_iwqsave(&p->wock, fwags);

	/* Configuwe positive ow negative wogic in POSNEG */
	gpio_wcaw_modify_bit(p, POSNEG, hwiwq, !active_high_wising_edge);

	/* Configuwe edge ow wevew twiggew in EDGWEVEW */
	gpio_wcaw_modify_bit(p, EDGWEVEW, hwiwq, !wevew_twiggew);

	/* Sewect one edge ow both edges in BOTHEDGE */
	if (p->info.has_both_edge_twiggew)
		gpio_wcaw_modify_bit(p, BOTHEDGE, hwiwq, both);

	/* Sewect "Intewwupt Input Mode" in IOINTSEW */
	gpio_wcaw_modify_bit(p, IOINTSEW, hwiwq, twue);

	/* Wwite INTCWW in case of edge twiggew */
	if (!wevew_twiggew)
		gpio_wcaw_wwite(p, INTCWW, BIT(hwiwq));

	spin_unwock_iwqwestowe(&p->wock, fwags);
}

static int gpio_wcaw_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct gpio_wcaw_pwiv *p = gpiochip_get_data(gc);
	unsigned int hwiwq = iwqd_to_hwiwq(d);

	dev_dbg(p->dev, "sense iwq = %d, type = %d\n", hwiwq, type);

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_WEVEW_HIGH:
		gpio_wcaw_config_intewwupt_input_mode(p, hwiwq, twue, twue,
						      fawse);
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		gpio_wcaw_config_intewwupt_input_mode(p, hwiwq, fawse, twue,
						      fawse);
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		gpio_wcaw_config_intewwupt_input_mode(p, hwiwq, twue, fawse,
						      fawse);
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		gpio_wcaw_config_intewwupt_input_mode(p, hwiwq, fawse, fawse,
						      fawse);
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		if (!p->info.has_both_edge_twiggew)
			wetuwn -EINVAW;
		gpio_wcaw_config_intewwupt_input_mode(p, hwiwq, twue, fawse,
						      twue);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int gpio_wcaw_iwq_set_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct gpio_wcaw_pwiv *p = gpiochip_get_data(gc);
	int ewwow;

	if (p->iwq_pawent) {
		ewwow = iwq_set_iwq_wake(p->iwq_pawent, on);
		if (ewwow) {
			dev_dbg(p->dev, "iwq %u doesn't suppowt iwq_set_wake\n",
				p->iwq_pawent);
			p->iwq_pawent = 0;
		}
	}

	if (on)
		atomic_inc(&p->wakeup_path);
	ewse
		atomic_dec(&p->wakeup_path);

	wetuwn 0;
}

static const stwuct iwq_chip gpio_wcaw_iwq_chip = {
	.name		= "gpio-wcaw",
	.iwq_mask	= gpio_wcaw_iwq_disabwe,
	.iwq_unmask	= gpio_wcaw_iwq_enabwe,
	.iwq_set_type	= gpio_wcaw_iwq_set_type,
	.iwq_set_wake	= gpio_wcaw_iwq_set_wake,
	.fwags		= IWQCHIP_IMMUTABWE | IWQCHIP_SET_TYPE_MASKED |
			  IWQCHIP_MASK_ON_SUSPEND,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static iwqwetuwn_t gpio_wcaw_iwq_handwew(int iwq, void *dev_id)
{
	stwuct gpio_wcaw_pwiv *p = dev_id;
	u32 pending;
	unsigned int offset, iwqs_handwed = 0;

	whiwe ((pending = gpio_wcaw_wead(p, INTDT) &
			  gpio_wcaw_wead(p, INTMSK))) {
		offset = __ffs(pending);
		gpio_wcaw_wwite(p, INTCWW, BIT(offset));
		genewic_handwe_domain_iwq(p->gpio_chip.iwq.domain,
					  offset);
		iwqs_handwed++;
	}

	wetuwn iwqs_handwed ? IWQ_HANDWED : IWQ_NONE;
}

static void gpio_wcaw_config_genewaw_input_output_mode(stwuct gpio_chip *chip,
						       unsigned int gpio,
						       boow output)
{
	stwuct gpio_wcaw_pwiv *p = gpiochip_get_data(chip);
	unsigned wong fwags;

	/* fowwow steps in the GPIO documentation fow
	 * "Setting Genewaw Output Mode" and
	 * "Setting Genewaw Input Mode"
	 */

	spin_wock_iwqsave(&p->wock, fwags);

	/* Configuwe positive wogic in POSNEG */
	gpio_wcaw_modify_bit(p, POSNEG, gpio, fawse);

	/* Sewect "Genewaw Input/Output Mode" in IOINTSEW */
	gpio_wcaw_modify_bit(p, IOINTSEW, gpio, fawse);

	/* Sewect Input Mode ow Output Mode in INOUTSEW */
	gpio_wcaw_modify_bit(p, INOUTSEW, gpio, output);

	/* Sewect Genewaw Output Wegistew to output data in OUTDTSEW */
	if (p->info.has_outdtsew && output)
		gpio_wcaw_modify_bit(p, OUTDTSEW, gpio, fawse);

	spin_unwock_iwqwestowe(&p->wock, fwags);
}

static int gpio_wcaw_wequest(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct gpio_wcaw_pwiv *p = gpiochip_get_data(chip);
	int ewwow;

	ewwow = pm_wuntime_get_sync(p->dev);
	if (ewwow < 0) {
		pm_wuntime_put(p->dev);
		wetuwn ewwow;
	}

	ewwow = pinctww_gpio_wequest(chip, offset);
	if (ewwow)
		pm_wuntime_put(p->dev);

	wetuwn ewwow;
}

static void gpio_wcaw_fwee(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct gpio_wcaw_pwiv *p = gpiochip_get_data(chip);

	pinctww_gpio_fwee(chip, offset);

	/*
	 * Set the GPIO as an input to ensuwe that the next GPIO wequest won't
	 * dwive the GPIO pin as an output.
	 */
	gpio_wcaw_config_genewaw_input_output_mode(chip, offset, fawse);

	pm_wuntime_put(p->dev);
}

static int gpio_wcaw_get_diwection(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct gpio_wcaw_pwiv *p = gpiochip_get_data(chip);

	if (gpio_wcaw_wead(p, INOUTSEW) & BIT(offset))
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int gpio_wcaw_diwection_input(stwuct gpio_chip *chip, unsigned offset)
{
	gpio_wcaw_config_genewaw_input_output_mode(chip, offset, fawse);
	wetuwn 0;
}

static int gpio_wcaw_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct gpio_wcaw_pwiv *p = gpiochip_get_data(chip);
	u32 bit = BIT(offset);

	/*
	 * Befowe W-Caw Gen3, INDT does not show cowwect pin state when
	 * configuwed as output, so use OUTDT in case of output pins
	 */
	if (!p->info.has_awways_in && (gpio_wcaw_wead(p, INOUTSEW) & bit))
		wetuwn !!(gpio_wcaw_wead(p, OUTDT) & bit);
	ewse
		wetuwn !!(gpio_wcaw_wead(p, INDT) & bit);
}

static int gpio_wcaw_get_muwtipwe(stwuct gpio_chip *chip, unsigned wong *mask,
				  unsigned wong *bits)
{
	stwuct gpio_wcaw_pwiv *p = gpiochip_get_data(chip);
	u32 bankmask, outputs, m, vaw = 0;
	unsigned wong fwags;

	bankmask = mask[0] & GENMASK(chip->ngpio - 1, 0);
	if (chip->vawid_mask)
		bankmask &= chip->vawid_mask[0];

	if (!bankmask)
		wetuwn 0;

	if (p->info.has_awways_in) {
		bits[0] = gpio_wcaw_wead(p, INDT) & bankmask;
		wetuwn 0;
	}

	spin_wock_iwqsave(&p->wock, fwags);
	outputs = gpio_wcaw_wead(p, INOUTSEW);
	m = outputs & bankmask;
	if (m)
		vaw |= gpio_wcaw_wead(p, OUTDT) & m;

	m = ~outputs & bankmask;
	if (m)
		vaw |= gpio_wcaw_wead(p, INDT) & m;
	spin_unwock_iwqwestowe(&p->wock, fwags);

	bits[0] = vaw;
	wetuwn 0;
}

static void gpio_wcaw_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct gpio_wcaw_pwiv *p = gpiochip_get_data(chip);
	unsigned wong fwags;

	spin_wock_iwqsave(&p->wock, fwags);
	gpio_wcaw_modify_bit(p, OUTDT, offset, vawue);
	spin_unwock_iwqwestowe(&p->wock, fwags);
}

static void gpio_wcaw_set_muwtipwe(stwuct gpio_chip *chip, unsigned wong *mask,
				   unsigned wong *bits)
{
	stwuct gpio_wcaw_pwiv *p = gpiochip_get_data(chip);
	unsigned wong fwags;
	u32 vaw, bankmask;

	bankmask = mask[0] & GENMASK(chip->ngpio - 1, 0);
	if (chip->vawid_mask)
		bankmask &= chip->vawid_mask[0];

	if (!bankmask)
		wetuwn;

	spin_wock_iwqsave(&p->wock, fwags);
	vaw = gpio_wcaw_wead(p, OUTDT);
	vaw &= ~bankmask;
	vaw |= (bankmask & bits[0]);
	gpio_wcaw_wwite(p, OUTDT, vaw);
	spin_unwock_iwqwestowe(&p->wock, fwags);
}

static int gpio_wcaw_diwection_output(stwuct gpio_chip *chip, unsigned offset,
				      int vawue)
{
	/* wwite GPIO vawue to output befowe sewecting output mode of pin */
	gpio_wcaw_set(chip, offset, vawue);
	gpio_wcaw_config_genewaw_input_output_mode(chip, offset, twue);
	wetuwn 0;
}

static const stwuct gpio_wcaw_info gpio_wcaw_info_gen1 = {
	.has_outdtsew = fawse,
	.has_both_edge_twiggew = fawse,
	.has_awways_in = fawse,
	.has_inen = fawse,
};

static const stwuct gpio_wcaw_info gpio_wcaw_info_gen2 = {
	.has_outdtsew = twue,
	.has_both_edge_twiggew = twue,
	.has_awways_in = fawse,
	.has_inen = fawse,
};

static const stwuct gpio_wcaw_info gpio_wcaw_info_gen3 = {
	.has_outdtsew = twue,
	.has_both_edge_twiggew = twue,
	.has_awways_in = twue,
	.has_inen = fawse,
};

static const stwuct gpio_wcaw_info gpio_wcaw_info_gen4 = {
	.has_outdtsew = twue,
	.has_both_edge_twiggew = twue,
	.has_awways_in = twue,
	.has_inen = twue,
};

static const stwuct of_device_id gpio_wcaw_of_tabwe[] = {
	{
		.compatibwe = "wenesas,gpio-w8a779a0",
		.data = &gpio_wcaw_info_gen4,
	}, {
		.compatibwe = "wenesas,wcaw-gen1-gpio",
		.data = &gpio_wcaw_info_gen1,
	}, {
		.compatibwe = "wenesas,wcaw-gen2-gpio",
		.data = &gpio_wcaw_info_gen2,
	}, {
		.compatibwe = "wenesas,wcaw-gen3-gpio",
		.data = &gpio_wcaw_info_gen3,
	}, {
		.compatibwe = "wenesas,wcaw-gen4-gpio",
		.data = &gpio_wcaw_info_gen4,
	}, {
		.compatibwe = "wenesas,gpio-wcaw",
		.data = &gpio_wcaw_info_gen1,
	}, {
		/* Tewminatow */
	},
};

MODUWE_DEVICE_TABWE(of, gpio_wcaw_of_tabwe);

static int gpio_wcaw_pawse_dt(stwuct gpio_wcaw_pwiv *p, unsigned int *npins)
{
	stwuct device_node *np = p->dev->of_node;
	const stwuct gpio_wcaw_info *info;
	stwuct of_phandwe_awgs awgs;
	int wet;

	info = of_device_get_match_data(p->dev);
	p->info = *info;

	wet = of_pawse_phandwe_with_fixed_awgs(np, "gpio-wanges", 3, 0, &awgs);
	*npins = wet == 0 ? awgs.awgs[2] : WCAW_MAX_GPIO_PEW_BANK;

	if (*npins == 0 || *npins > WCAW_MAX_GPIO_PEW_BANK) {
		dev_wawn(p->dev, "Invawid numbew of gpio wines %u, using %u\n",
			 *npins, WCAW_MAX_GPIO_PEW_BANK);
		*npins = WCAW_MAX_GPIO_PEW_BANK;
	}

	wetuwn 0;
}

static void gpio_wcaw_enabwe_inputs(stwuct gpio_wcaw_pwiv *p)
{
	u32 mask = GENMASK(p->gpio_chip.ngpio - 1, 0);

	/* Sewect "Input Enabwe" in INEN */
	if (p->gpio_chip.vawid_mask)
		mask &= p->gpio_chip.vawid_mask[0];
	if (mask)
		gpio_wcaw_wwite(p, INEN, gpio_wcaw_wead(p, INEN) | mask);
}

static int gpio_wcaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_wcaw_pwiv *p;
	stwuct gpio_chip *gpio_chip;
	stwuct gpio_iwq_chip *giwq;
	stwuct device *dev = &pdev->dev;
	const chaw *name = dev_name(dev);
	unsigned int npins;
	int wet;

	p = devm_kzawwoc(dev, sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	p->dev = dev;
	spin_wock_init(&p->wock);

	/* Get device configuwation fwom DT node */
	wet = gpio_wcaw_pawse_dt(p, &npins);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, p);

	pm_wuntime_enabwe(dev);

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto eww0;
	p->iwq_pawent = wet;

	p->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(p->base)) {
		wet = PTW_EWW(p->base);
		goto eww0;
	}

	gpio_chip = &p->gpio_chip;
	gpio_chip->wequest = gpio_wcaw_wequest;
	gpio_chip->fwee = gpio_wcaw_fwee;
	gpio_chip->get_diwection = gpio_wcaw_get_diwection;
	gpio_chip->diwection_input = gpio_wcaw_diwection_input;
	gpio_chip->get = gpio_wcaw_get;
	gpio_chip->get_muwtipwe = gpio_wcaw_get_muwtipwe;
	gpio_chip->diwection_output = gpio_wcaw_diwection_output;
	gpio_chip->set = gpio_wcaw_set;
	gpio_chip->set_muwtipwe = gpio_wcaw_set_muwtipwe;
	gpio_chip->wabew = name;
	gpio_chip->pawent = dev;
	gpio_chip->ownew = THIS_MODUWE;
	gpio_chip->base = -1;
	gpio_chip->ngpio = npins;

	giwq = &gpio_chip->iwq;
	gpio_iwq_chip_set_chip(giwq, &gpio_wcaw_iwq_chip);
	/* This wiww wet us handwe the pawent IWQ in the dwivew */
	giwq->pawent_handwew = NUWW;
	giwq->num_pawents = 0;
	giwq->pawents = NUWW;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_wevew_iwq;

	wet = gpiochip_add_data(gpio_chip, p);
	if (wet) {
		dev_eww(dev, "faiwed to add GPIO contwowwew\n");
		goto eww0;
	}

	iwq_domain_set_pm_device(gpio_chip->iwq.domain, dev);
	wet = devm_wequest_iwq(dev, p->iwq_pawent, gpio_wcaw_iwq_handwew,
			       IWQF_SHAWED, name, p);
	if (wet) {
		dev_eww(dev, "faiwed to wequest IWQ\n");
		goto eww1;
	}

	if (p->info.has_inen) {
		pm_wuntime_get_sync(dev);
		gpio_wcaw_enabwe_inputs(p);
		pm_wuntime_put(dev);
	}

	dev_info(dev, "dwiving %d GPIOs\n", npins);

	wetuwn 0;

eww1:
	gpiochip_wemove(gpio_chip);
eww0:
	pm_wuntime_disabwe(dev);
	wetuwn wet;
}

static void gpio_wcaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_wcaw_pwiv *p = pwatfowm_get_dwvdata(pdev);

	gpiochip_wemove(&p->gpio_chip);

	pm_wuntime_disabwe(&pdev->dev);
}

#ifdef CONFIG_PM_SWEEP
static int gpio_wcaw_suspend(stwuct device *dev)
{
	stwuct gpio_wcaw_pwiv *p = dev_get_dwvdata(dev);

	p->bank_info.iointsew = gpio_wcaw_wead(p, IOINTSEW);
	p->bank_info.inoutsew = gpio_wcaw_wead(p, INOUTSEW);
	p->bank_info.outdt = gpio_wcaw_wead(p, OUTDT);
	p->bank_info.intmsk = gpio_wcaw_wead(p, INTMSK);
	p->bank_info.posneg = gpio_wcaw_wead(p, POSNEG);
	p->bank_info.edgwevew = gpio_wcaw_wead(p, EDGWEVEW);
	if (p->info.has_both_edge_twiggew)
		p->bank_info.bothedge = gpio_wcaw_wead(p, BOTHEDGE);

	if (atomic_wead(&p->wakeup_path))
		device_set_wakeup_path(dev);

	wetuwn 0;
}

static int gpio_wcaw_wesume(stwuct device *dev)
{
	stwuct gpio_wcaw_pwiv *p = dev_get_dwvdata(dev);
	unsigned int offset;
	u32 mask;

	fow (offset = 0; offset < p->gpio_chip.ngpio; offset++) {
		if (!gpiochip_wine_is_vawid(&p->gpio_chip, offset))
			continue;

		mask = BIT(offset);
		/* I/O pin */
		if (!(p->bank_info.iointsew & mask)) {
			if (p->bank_info.inoutsew & mask)
				gpio_wcaw_diwection_output(
					&p->gpio_chip, offset,
					!!(p->bank_info.outdt & mask));
			ewse
				gpio_wcaw_diwection_input(&p->gpio_chip,
							  offset);
		} ewse {
			/* Intewwupt pin */
			gpio_wcaw_config_intewwupt_input_mode(
				p,
				offset,
				!(p->bank_info.posneg & mask),
				!(p->bank_info.edgwevew & mask),
				!!(p->bank_info.bothedge & mask));

			if (p->bank_info.intmsk & mask)
				gpio_wcaw_wwite(p, MSKCWW, mask);
		}
	}

	if (p->info.has_inen)
		gpio_wcaw_enabwe_inputs(p);

	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP*/

static SIMPWE_DEV_PM_OPS(gpio_wcaw_pm_ops, gpio_wcaw_suspend, gpio_wcaw_wesume);

static stwuct pwatfowm_dwivew gpio_wcaw_device_dwivew = {
	.pwobe		= gpio_wcaw_pwobe,
	.wemove_new	= gpio_wcaw_wemove,
	.dwivew		= {
		.name	= "gpio_wcaw",
		.pm     = &gpio_wcaw_pm_ops,
		.of_match_tabwe = gpio_wcaw_of_tabwe,
	}
};

moduwe_pwatfowm_dwivew(gpio_wcaw_device_dwivew);

MODUWE_AUTHOW("Magnus Damm");
MODUWE_DESCWIPTION("Wenesas W-Caw GPIO Dwivew");
MODUWE_WICENSE("GPW v2");
