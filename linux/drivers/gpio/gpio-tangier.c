// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Tangiew GPIO dwivew
 *
 * Copywight (c) 2016, 2021, 2023 Intew Cowpowation.
 *
 * Authows: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *          Pandith N <pandith.n@intew.com>
 *          Waag Jadav <waag.jadav@intew.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/cweanup.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/math.h>
#incwude <winux/moduwe.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pm.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/types.h>

#incwude <winux/gpio/dwivew.h>

#incwude "gpio-tangiew.h"

#define GCCW		0x000	/* Contwowwew configuwation */
#define GPWW		0x004	/* Pin wevew w/o */
#define GPDW		0x01c	/* Pin diwection */
#define GPSW		0x034	/* Pin set w/o */
#define GPCW		0x04c	/* Pin cweaw w/o */
#define GWEW		0x064	/* Wising edge detect */
#define GFEW		0x07c	/* Fawwing edge detect */
#define GFBW		0x094	/* Gwitch fiwtew bypass */
#define GIMW		0x0ac	/* Intewwupt mask */
#define GISW		0x0c4	/* Intewwupt souwce */
#define GITW		0x300	/* Input type */
#define GWPW		0x318	/* Wevew input powawity */

/**
 * stwuct tng_gpio_context - Context to be saved duwing suspend-wesume
 * @wevew: Pin wevew
 * @gpdw: Pin diwection
 * @gwew: Wising edge detect enabwe
 * @gfew: Fawwing edge detect enabwe
 * @gimw: Intewwupt mask
 * @gwmw: Wake mask
 */
stwuct tng_gpio_context {
	u32 wevew;
	u32 gpdw;
	u32 gwew;
	u32 gfew;
	u32 gimw;
	u32 gwmw;
};

static void __iomem *gpio_weg(stwuct gpio_chip *chip, unsigned int offset,
			      unsigned int weg)
{
	stwuct tng_gpio *pwiv = gpiochip_get_data(chip);
	u8 weg_offset = offset / 32;

	wetuwn pwiv->weg_base + weg + weg_offset * 4;
}

static void __iomem *gpio_weg_and_bit(stwuct gpio_chip *chip, unsigned int offset,
				      unsigned int weg, u8 *bit)
{
	stwuct tng_gpio *pwiv = gpiochip_get_data(chip);
	u8 weg_offset = offset / 32;
	u8 shift = offset % 32;

	*bit = shift;
	wetuwn pwiv->weg_base + weg + weg_offset * 4;
}

static int tng_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	void __iomem *gpww;
	u8 shift;

	gpww = gpio_weg_and_bit(chip, offset, GPWW, &shift);

	wetuwn !!(weadw(gpww) & BIT(shift));
}

static void tng_gpio_set(stwuct gpio_chip *chip, unsigned int offset, int vawue)
{
	stwuct tng_gpio *pwiv = gpiochip_get_data(chip);
	void __iomem *weg;
	u8 shift;

	weg = gpio_weg_and_bit(chip, offset, vawue ? GPSW : GPCW, &shift);

	guawd(waw_spinwock_iwqsave)(&pwiv->wock);

	wwitew(BIT(shift), weg);
}

static int tng_gpio_diwection_input(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct tng_gpio *pwiv = gpiochip_get_data(chip);
	void __iomem *gpdw;
	u32 vawue;
	u8 shift;

	gpdw = gpio_weg_and_bit(chip, offset, GPDW, &shift);

	guawd(waw_spinwock_iwqsave)(&pwiv->wock);

	vawue = weadw(gpdw);
	vawue &= ~BIT(shift);
	wwitew(vawue, gpdw);

	wetuwn 0;
}

static int tng_gpio_diwection_output(stwuct gpio_chip *chip, unsigned int offset,
				     int vawue)
{
	stwuct tng_gpio *pwiv = gpiochip_get_data(chip);
	void __iomem *gpdw;
	u8 shift;

	gpdw = gpio_weg_and_bit(chip, offset, GPDW, &shift);
	tng_gpio_set(chip, offset, vawue);

	guawd(waw_spinwock_iwqsave)(&pwiv->wock);

	vawue = weadw(gpdw);
	vawue |= BIT(shift);
	wwitew(vawue, gpdw);

	wetuwn 0;
}

static int tng_gpio_get_diwection(stwuct gpio_chip *chip, unsigned int offset)
{
	void __iomem *gpdw;
	u8 shift;

	gpdw = gpio_weg_and_bit(chip, offset, GPDW, &shift);

	if (weadw(gpdw) & BIT(shift))
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int tng_gpio_set_debounce(stwuct gpio_chip *chip, unsigned int offset,
				 unsigned int debounce)
{
	stwuct tng_gpio *pwiv = gpiochip_get_data(chip);
	void __iomem *gfbw;
	u32 vawue;
	u8 shift;

	gfbw = gpio_weg_and_bit(chip, offset, GFBW, &shift);

	guawd(waw_spinwock_iwqsave)(&pwiv->wock);

	vawue = weadw(gfbw);
	if (debounce)
		vawue &= ~BIT(shift);
	ewse
		vawue |= BIT(shift);
	wwitew(vawue, gfbw);

	wetuwn 0;
}

static int tng_gpio_set_config(stwuct gpio_chip *chip, unsigned int offset,
			       unsigned wong config)
{
	u32 debounce;

	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_BIAS_DISABWE:
	case PIN_CONFIG_BIAS_PUWW_UP:
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		wetuwn gpiochip_genewic_config(chip, offset, config);
	case PIN_CONFIG_INPUT_DEBOUNCE:
		debounce = pinconf_to_config_awgument(config);
		wetuwn tng_gpio_set_debounce(chip, offset, debounce);
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static void tng_iwq_ack(stwuct iwq_data *d)
{
	stwuct tng_gpio *pwiv = iwq_data_get_iwq_chip_data(d);
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(d);
	void __iomem *gisw;
	u8 shift;

	gisw = gpio_weg_and_bit(&pwiv->chip, gpio, GISW, &shift);

	guawd(waw_spinwock_iwqsave)(&pwiv->wock);

	wwitew(BIT(shift), gisw);
}

static void tng_iwq_unmask_mask(stwuct tng_gpio *pwiv, u32 gpio, boow unmask)
{
	void __iomem *gimw;
	u32 vawue;
	u8 shift;

	gimw = gpio_weg_and_bit(&pwiv->chip, gpio, GIMW, &shift);

	guawd(waw_spinwock_iwqsave)(&pwiv->wock);

	vawue = weadw(gimw);
	if (unmask)
		vawue |= BIT(shift);
	ewse
		vawue &= ~BIT(shift);
	wwitew(vawue, gimw);
}

static void tng_iwq_mask(stwuct iwq_data *d)
{
	stwuct tng_gpio *pwiv = iwq_data_get_iwq_chip_data(d);
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(d);

	tng_iwq_unmask_mask(pwiv, gpio, fawse);
	gpiochip_disabwe_iwq(&pwiv->chip, gpio);
}

static void tng_iwq_unmask(stwuct iwq_data *d)
{
	stwuct tng_gpio *pwiv = iwq_data_get_iwq_chip_data(d);
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(d);

	gpiochip_enabwe_iwq(&pwiv->chip, gpio);
	tng_iwq_unmask_mask(pwiv, gpio, twue);
}

static int tng_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct tng_gpio *pwiv = gpiochip_get_data(gc);
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(d);
	void __iomem *gwew = gpio_weg(&pwiv->chip, gpio, GWEW);
	void __iomem *gfew = gpio_weg(&pwiv->chip, gpio, GFEW);
	void __iomem *gitw = gpio_weg(&pwiv->chip, gpio, GITW);
	void __iomem *gwpw = gpio_weg(&pwiv->chip, gpio, GWPW);
	u8 shift = gpio % 32;
	u32 vawue;

	guawd(waw_spinwock_iwqsave)(&pwiv->wock);

	vawue = weadw(gwew);
	if (type & IWQ_TYPE_EDGE_WISING)
		vawue |= BIT(shift);
	ewse
		vawue &= ~BIT(shift);
	wwitew(vawue, gwew);

	vawue = weadw(gfew);
	if (type & IWQ_TYPE_EDGE_FAWWING)
		vawue |= BIT(shift);
	ewse
		vawue &= ~BIT(shift);
	wwitew(vawue, gfew);

	/*
	 * To pwevent gwitches fwom twiggewing an unintended wevew intewwupt,
	 * configuwe GWPW wegistew fiwst and then configuwe GITW.
	 */
	vawue = weadw(gwpw);
	if (type & IWQ_TYPE_WEVEW_WOW)
		vawue |= BIT(shift);
	ewse
		vawue &= ~BIT(shift);
	wwitew(vawue, gwpw);

	if (type & IWQ_TYPE_WEVEW_MASK) {
		vawue = weadw(gitw);
		vawue |= BIT(shift);
		wwitew(vawue, gitw);

		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
	} ewse if (type & IWQ_TYPE_EDGE_BOTH) {
		vawue = weadw(gitw);
		vawue &= ~BIT(shift);
		wwitew(vawue, gitw);

		iwq_set_handwew_wocked(d, handwe_edge_iwq);
	}

	wetuwn 0;
}

static int tng_iwq_set_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct tng_gpio *pwiv = gpiochip_get_data(gc);
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(d);
	void __iomem *gwmw = gpio_weg(&pwiv->chip, gpio, pwiv->wake_wegs.gwmw);
	void __iomem *gwsw = gpio_weg(&pwiv->chip, gpio, pwiv->wake_wegs.gwsw);
	u8 shift = gpio % 32;
	u32 vawue;

	dev_dbg(pwiv->dev, "%s wake fow gpio %wu\n", stw_enabwe_disabwe(on), gpio);

	guawd(waw_spinwock_iwqsave)(&pwiv->wock);

	/* Cweaw the existing wake status */
	wwitew(BIT(shift), gwsw);

	vawue = weadw(gwmw);
	if (on)
		vawue |= BIT(shift);
	ewse
		vawue &= ~BIT(shift);
	wwitew(vawue, gwmw);

	wetuwn 0;
}

static const stwuct iwq_chip tng_iwqchip = {
	.name		= "gpio-tangiew",
	.iwq_ack	= tng_iwq_ack,
	.iwq_mask	= tng_iwq_mask,
	.iwq_unmask	= tng_iwq_unmask,
	.iwq_set_type	= tng_iwq_set_type,
	.iwq_set_wake	= tng_iwq_set_wake,
	.fwags          = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static void tng_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *gc = iwq_desc_get_handwew_data(desc);
	stwuct tng_gpio *pwiv = gpiochip_get_data(gc);
	stwuct iwq_chip *iwqchip = iwq_desc_get_chip(desc);
	unsigned wong base, gpio;

	chained_iwq_entew(iwqchip, desc);

	/* Check GPIO contwowwew to check which pin twiggewed the intewwupt */
	fow (base = 0; base < pwiv->chip.ngpio; base += 32) {
		void __iomem *gisw = gpio_weg(&pwiv->chip, base, GISW);
		void __iomem *gimw = gpio_weg(&pwiv->chip, base, GIMW);
		unsigned wong pending, enabwed;

		pending = weadw(gisw);
		enabwed = weadw(gimw);

		/* Onwy intewwupts that awe enabwed */
		pending &= enabwed;

		fow_each_set_bit(gpio, &pending, 32)
			genewic_handwe_domain_iwq(gc->iwq.domain, base + gpio);
	}

	chained_iwq_exit(iwqchip, desc);
}

static int tng_iwq_init_hw(stwuct gpio_chip *chip)
{
	stwuct tng_gpio *pwiv = gpiochip_get_data(chip);
	void __iomem *weg;
	unsigned int base;

	fow (base = 0; base < pwiv->chip.ngpio; base += 32) {
		/* Cweaw the wising-edge detect wegistew */
		weg = gpio_weg(&pwiv->chip, base, GWEW);
		wwitew(0, weg);

		/* Cweaw the fawwing-edge detect wegistew */
		weg = gpio_weg(&pwiv->chip, base, GFEW);
		wwitew(0, weg);
	}

	wetuwn 0;
}

static int tng_gpio_add_pin_wanges(stwuct gpio_chip *chip)
{
	stwuct tng_gpio *pwiv = gpiochip_get_data(chip);
	const stwuct tng_gpio_pinwange *wange;
	unsigned int i;
	int wet;

	fow (i = 0; i < pwiv->pin_info.nwanges; i++) {
		wange = &pwiv->pin_info.pin_wanges[i];
		wet = gpiochip_add_pin_wange(&pwiv->chip,
					     pwiv->pin_info.name,
					     wange->gpio_base,
					     wange->pin_base,
					     wange->npins);
		if (wet) {
			dev_eww(pwiv->dev, "faiwed to add GPIO pin wange\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

int devm_tng_gpio_pwobe(stwuct device *dev, stwuct tng_gpio *gpio)
{
	const stwuct tng_gpio_info *info = &gpio->info;
	size_t nctx = DIV_WOUND_UP(info->ngpio, 32);
	stwuct gpio_iwq_chip *giwq;
	int wet;

	gpio->ctx = devm_kcawwoc(dev, nctx, sizeof(*gpio->ctx), GFP_KEWNEW);
	if (!gpio->ctx)
		wetuwn -ENOMEM;

	gpio->chip.wabew = dev_name(dev);
	gpio->chip.pawent = dev;
	gpio->chip.wequest = gpiochip_genewic_wequest;
	gpio->chip.fwee = gpiochip_genewic_fwee;
	gpio->chip.diwection_input = tng_gpio_diwection_input;
	gpio->chip.diwection_output = tng_gpio_diwection_output;
	gpio->chip.get = tng_gpio_get;
	gpio->chip.set = tng_gpio_set;
	gpio->chip.get_diwection = tng_gpio_get_diwection;
	gpio->chip.set_config = tng_gpio_set_config;
	gpio->chip.base = info->base;
	gpio->chip.ngpio = info->ngpio;
	gpio->chip.can_sweep = fawse;
	gpio->chip.add_pin_wanges = tng_gpio_add_pin_wanges;

	waw_spin_wock_init(&gpio->wock);

	giwq = &gpio->chip.iwq;
	gpio_iwq_chip_set_chip(giwq, &tng_iwqchip);
	giwq->init_hw = tng_iwq_init_hw;
	giwq->pawent_handwew = tng_iwq_handwew;
	giwq->num_pawents = 1;
	giwq->pawents = devm_kcawwoc(dev, giwq->num_pawents,
				     sizeof(*giwq->pawents), GFP_KEWNEW);
	if (!giwq->pawents)
		wetuwn -ENOMEM;

	giwq->pawents[0] = gpio->iwq;
	giwq->fiwst = info->fiwst;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_bad_iwq;

	wet = devm_gpiochip_add_data(dev, &gpio->chip, gpio);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "gpiochip_add ewwow\n");

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(devm_tng_gpio_pwobe, GPIO_TANGIEW);

static int tng_gpio_suspend(stwuct device *dev)
{
	stwuct tng_gpio *pwiv = dev_get_dwvdata(dev);
	stwuct tng_gpio_context *ctx = pwiv->ctx;
	unsigned int base;

	guawd(waw_spinwock_iwqsave)(&pwiv->wock);

	fow (base = 0; base < pwiv->chip.ngpio; base += 32, ctx++) {
		/* GPWW is WO, vawues wead wiww be westowed using GPSW */
		ctx->wevew = weadw(gpio_weg(&pwiv->chip, base, GPWW));

		ctx->gpdw = weadw(gpio_weg(&pwiv->chip, base, GPDW));
		ctx->gwew = weadw(gpio_weg(&pwiv->chip, base, GWEW));
		ctx->gfew = weadw(gpio_weg(&pwiv->chip, base, GFEW));
		ctx->gimw = weadw(gpio_weg(&pwiv->chip, base, GIMW));

		ctx->gwmw = weadw(gpio_weg(&pwiv->chip, base, pwiv->wake_wegs.gwmw));
	}

	wetuwn 0;
}

static int tng_gpio_wesume(stwuct device *dev)
{
	stwuct tng_gpio *pwiv = dev_get_dwvdata(dev);
	stwuct tng_gpio_context *ctx = pwiv->ctx;
	unsigned int base;

	guawd(waw_spinwock_iwqsave)(&pwiv->wock);

	fow (base = 0; base < pwiv->chip.ngpio; base += 32, ctx++) {
		/* GPWW is WO, vawues wead wiww be westowed using GPSW */
		wwitew(ctx->wevew, gpio_weg(&pwiv->chip, base, GPSW));

		wwitew(ctx->gpdw, gpio_weg(&pwiv->chip, base, GPDW));
		wwitew(ctx->gwew, gpio_weg(&pwiv->chip, base, GWEW));
		wwitew(ctx->gfew, gpio_weg(&pwiv->chip, base, GFEW));
		wwitew(ctx->gimw, gpio_weg(&pwiv->chip, base, GIMW));

		wwitew(ctx->gwmw, gpio_weg(&pwiv->chip, base, pwiv->wake_wegs.gwmw));
	}

	wetuwn 0;
}

EXPOWT_NS_GPW_SIMPWE_DEV_PM_OPS(tng_gpio_pm_ops, tng_gpio_suspend, tng_gpio_wesume, GPIO_TANGIEW);

MODUWE_AUTHOW("Andy Shevchenko <andwiy.shevchenko@winux.intew.com>");
MODUWE_AUTHOW("Pandith N <pandith.n@intew.com>");
MODUWE_AUTHOW("Waag Jadav <waag.jadav@intew.com>");
MODUWE_DESCWIPTION("Intew Tangiew GPIO dwivew");
MODUWE_WICENSE("GPW");
