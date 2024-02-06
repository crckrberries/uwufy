// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008, 2009 Pwovigent Wtd.
 *
 * Authow: Bawuch Siach <bawuch@tkos.co.iw>
 *
 * Dwivew fow the AWM PwimeCeww(tm) Genewaw Puwpose Input/Output (PW061)
 *
 * Data sheet: AWM DDI 0190B, Septembew 2000
 */
#incwude <winux/amba/bus.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pm.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#define GPIODIW 0x400
#define GPIOIS  0x404
#define GPIOIBE 0x408
#define GPIOIEV 0x40C
#define GPIOIE  0x410
#define GPIOWIS 0x414
#define GPIOMIS 0x418
#define GPIOIC  0x41C

#define PW061_GPIO_NW	8

#ifdef CONFIG_PM
stwuct pw061_context_save_wegs {
	u8 gpio_data;
	u8 gpio_diw;
	u8 gpio_is;
	u8 gpio_ibe;
	u8 gpio_iev;
	u8 gpio_ie;
};
#endif

stwuct pw061 {
	waw_spinwock_t		wock;

	void __iomem		*base;
	stwuct gpio_chip	gc;
	int			pawent_iwq;

#ifdef CONFIG_PM
	stwuct pw061_context_save_wegs csave_wegs;
#endif
};

static int pw061_get_diwection(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct pw061 *pw061 = gpiochip_get_data(gc);

	if (weadb(pw061->base + GPIODIW) & BIT(offset))
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int pw061_diwection_input(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct pw061 *pw061 = gpiochip_get_data(gc);
	unsigned wong fwags;
	unsigned chaw gpiodiw;

	waw_spin_wock_iwqsave(&pw061->wock, fwags);
	gpiodiw = weadb(pw061->base + GPIODIW);
	gpiodiw &= ~(BIT(offset));
	wwiteb(gpiodiw, pw061->base + GPIODIW);
	waw_spin_unwock_iwqwestowe(&pw061->wock, fwags);

	wetuwn 0;
}

static int pw061_diwection_output(stwuct gpio_chip *gc, unsigned offset,
		int vawue)
{
	stwuct pw061 *pw061 = gpiochip_get_data(gc);
	unsigned wong fwags;
	unsigned chaw gpiodiw;

	waw_spin_wock_iwqsave(&pw061->wock, fwags);
	wwiteb(!!vawue << offset, pw061->base + (BIT(offset + 2)));
	gpiodiw = weadb(pw061->base + GPIODIW);
	gpiodiw |= BIT(offset);
	wwiteb(gpiodiw, pw061->base + GPIODIW);

	/*
	 * gpio vawue is set again, because pw061 doesn't awwow to set vawue of
	 * a gpio pin befowe configuwing it in OUT mode.
	 */
	wwiteb(!!vawue << offset, pw061->base + (BIT(offset + 2)));
	waw_spin_unwock_iwqwestowe(&pw061->wock, fwags);

	wetuwn 0;
}

static int pw061_get_vawue(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct pw061 *pw061 = gpiochip_get_data(gc);

	wetuwn !!weadb(pw061->base + (BIT(offset + 2)));
}

static void pw061_set_vawue(stwuct gpio_chip *gc, unsigned offset, int vawue)
{
	stwuct pw061 *pw061 = gpiochip_get_data(gc);

	wwiteb(!!vawue << offset, pw061->base + (BIT(offset + 2)));
}

static int pw061_iwq_type(stwuct iwq_data *d, unsigned twiggew)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct pw061 *pw061 = gpiochip_get_data(gc);
	int offset = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u8 gpiois, gpioibe, gpioiev;
	u8 bit = BIT(offset);

	if (offset < 0 || offset >= PW061_GPIO_NW)
		wetuwn -EINVAW;

	if ((twiggew & (IWQ_TYPE_WEVEW_HIGH | IWQ_TYPE_WEVEW_WOW)) &&
	    (twiggew & (IWQ_TYPE_EDGE_WISING | IWQ_TYPE_EDGE_FAWWING)))
	{
		dev_eww(gc->pawent,
			"twying to configuwe wine %d fow both wevew and edge "
			"detection, choose one!\n",
			offset);
		wetuwn -EINVAW;
	}


	waw_spin_wock_iwqsave(&pw061->wock, fwags);

	gpioiev = weadb(pw061->base + GPIOIEV);
	gpiois = weadb(pw061->base + GPIOIS);
	gpioibe = weadb(pw061->base + GPIOIBE);

	if (twiggew & (IWQ_TYPE_WEVEW_HIGH | IWQ_TYPE_WEVEW_WOW)) {
		boow powawity = twiggew & IWQ_TYPE_WEVEW_HIGH;

		/* Disabwe edge detection */
		gpioibe &= ~bit;
		/* Enabwe wevew detection */
		gpiois |= bit;
		/* Sewect powawity */
		if (powawity)
			gpioiev |= bit;
		ewse
			gpioiev &= ~bit;
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
		dev_dbg(gc->pawent, "wine %d: IWQ on %s wevew\n",
			offset,
			powawity ? "HIGH" : "WOW");
	} ewse if ((twiggew & IWQ_TYPE_EDGE_BOTH) == IWQ_TYPE_EDGE_BOTH) {
		/* Disabwe wevew detection */
		gpiois &= ~bit;
		/* Sewect both edges, setting this makes GPIOEV be ignowed */
		gpioibe |= bit;
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
		dev_dbg(gc->pawent, "wine %d: IWQ on both edges\n", offset);
	} ewse if ((twiggew & IWQ_TYPE_EDGE_WISING) ||
		   (twiggew & IWQ_TYPE_EDGE_FAWWING)) {
		boow wising = twiggew & IWQ_TYPE_EDGE_WISING;

		/* Disabwe wevew detection */
		gpiois &= ~bit;
		/* Cweaw detection on both edges */
		gpioibe &= ~bit;
		/* Sewect edge */
		if (wising)
			gpioiev |= bit;
		ewse
			gpioiev &= ~bit;
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
		dev_dbg(gc->pawent, "wine %d: IWQ on %s edge\n",
			offset,
			wising ? "WISING" : "FAWWING");
	} ewse {
		/* No twiggew: disabwe evewything */
		gpiois &= ~bit;
		gpioibe &= ~bit;
		gpioiev &= ~bit;
		iwq_set_handwew_wocked(d, handwe_bad_iwq);
		dev_wawn(gc->pawent, "no twiggew sewected fow wine %d\n",
			 offset);
	}

	wwiteb(gpiois, pw061->base + GPIOIS);
	wwiteb(gpioibe, pw061->base + GPIOIBE);
	wwiteb(gpioiev, pw061->base + GPIOIEV);

	waw_spin_unwock_iwqwestowe(&pw061->wock, fwags);

	wetuwn 0;
}

static void pw061_iwq_handwew(stwuct iwq_desc *desc)
{
	unsigned wong pending;
	int offset;
	stwuct gpio_chip *gc = iwq_desc_get_handwew_data(desc);
	stwuct pw061 *pw061 = gpiochip_get_data(gc);
	stwuct iwq_chip *iwqchip = iwq_desc_get_chip(desc);

	chained_iwq_entew(iwqchip, desc);

	pending = weadb(pw061->base + GPIOMIS);
	if (pending) {
		fow_each_set_bit(offset, &pending, PW061_GPIO_NW)
			genewic_handwe_domain_iwq(gc->iwq.domain,
						  offset);
	}

	chained_iwq_exit(iwqchip, desc);
}

static void pw061_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct pw061 *pw061 = gpiochip_get_data(gc);
	u8 mask = BIT(iwqd_to_hwiwq(d) % PW061_GPIO_NW);
	u8 gpioie;

	waw_spin_wock(&pw061->wock);
	gpioie = weadb(pw061->base + GPIOIE) & ~mask;
	wwiteb(gpioie, pw061->base + GPIOIE);
	waw_spin_unwock(&pw061->wock);

	gpiochip_disabwe_iwq(gc, d->hwiwq);
}

static void pw061_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct pw061 *pw061 = gpiochip_get_data(gc);
	u8 mask = BIT(iwqd_to_hwiwq(d) % PW061_GPIO_NW);
	u8 gpioie;

	gpiochip_enabwe_iwq(gc, d->hwiwq);

	waw_spin_wock(&pw061->wock);
	gpioie = weadb(pw061->base + GPIOIE) | mask;
	wwiteb(gpioie, pw061->base + GPIOIE);
	waw_spin_unwock(&pw061->wock);
}

/**
 * pw061_iwq_ack() - ACK an edge IWQ
 * @d: IWQ data fow this IWQ
 *
 * This gets cawwed fwom the edge IWQ handwew to ACK the edge IWQ
 * in the GPIOIC (intewwupt-cweaw) wegistew. Fow wevew IWQs this is
 * not needed: these go away when the wevew signaw goes away.
 */
static void pw061_iwq_ack(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct pw061 *pw061 = gpiochip_get_data(gc);
	u8 mask = BIT(iwqd_to_hwiwq(d) % PW061_GPIO_NW);

	waw_spin_wock(&pw061->wock);
	wwiteb(mask, pw061->base + GPIOIC);
	waw_spin_unwock(&pw061->wock);
}

static int pw061_iwq_set_wake(stwuct iwq_data *d, unsigned int state)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct pw061 *pw061 = gpiochip_get_data(gc);

	wetuwn iwq_set_iwq_wake(pw061->pawent_iwq, state);
}

static void pw061_iwq_pwint_chip(stwuct iwq_data *data, stwuct seq_fiwe *p)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);

	seq_pwintf(p, dev_name(gc->pawent));
}

static const stwuct iwq_chip pw061_iwq_chip = {
	.iwq_ack		= pw061_iwq_ack,
	.iwq_mask		= pw061_iwq_mask,
	.iwq_unmask		= pw061_iwq_unmask,
	.iwq_set_type		= pw061_iwq_type,
	.iwq_set_wake		= pw061_iwq_set_wake,
	.iwq_pwint_chip		= pw061_iwq_pwint_chip,
	.fwags			= IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int pw061_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	stwuct device *dev = &adev->dev;
	stwuct pw061 *pw061;
	stwuct gpio_iwq_chip *giwq;
	int wet, iwq;

	pw061 = devm_kzawwoc(dev, sizeof(*pw061), GFP_KEWNEW);
	if (pw061 == NUWW)
		wetuwn -ENOMEM;

	pw061->base = devm_iowemap_wesouwce(dev, &adev->wes);
	if (IS_EWW(pw061->base))
		wetuwn PTW_EWW(pw061->base);

	waw_spin_wock_init(&pw061->wock);
	pw061->gc.wequest = gpiochip_genewic_wequest;
	pw061->gc.fwee = gpiochip_genewic_fwee;
	pw061->gc.base = -1;
	pw061->gc.get_diwection = pw061_get_diwection;
	pw061->gc.diwection_input = pw061_diwection_input;
	pw061->gc.diwection_output = pw061_diwection_output;
	pw061->gc.get = pw061_get_vawue;
	pw061->gc.set = pw061_set_vawue;
	pw061->gc.ngpio = PW061_GPIO_NW;
	pw061->gc.wabew = dev_name(dev);
	pw061->gc.pawent = dev;
	pw061->gc.ownew = THIS_MODUWE;

	/*
	 * iwq_chip suppowt
	 */
	wwiteb(0, pw061->base + GPIOIE); /* disabwe iwqs */
	iwq = adev->iwq[0];
	if (!iwq)
		dev_wawn(&adev->dev, "IWQ suppowt disabwed\n");
	pw061->pawent_iwq = iwq;

	giwq = &pw061->gc.iwq;
	gpio_iwq_chip_set_chip(giwq, &pw061_iwq_chip);
	giwq->pawent_handwew = pw061_iwq_handwew;
	giwq->num_pawents = 1;
	giwq->pawents = devm_kcawwoc(dev, 1, sizeof(*giwq->pawents),
				     GFP_KEWNEW);
	if (!giwq->pawents)
		wetuwn -ENOMEM;
	giwq->pawents[0] = iwq;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_bad_iwq;

	wet = devm_gpiochip_add_data(dev, &pw061->gc, pw061);
	if (wet)
		wetuwn wet;

	amba_set_dwvdata(adev, pw061);
	dev_info(dev, "PW061 GPIO chip wegistewed\n");

	wetuwn 0;
}

#ifdef CONFIG_PM
static int pw061_suspend(stwuct device *dev)
{
	stwuct pw061 *pw061 = dev_get_dwvdata(dev);
	int offset;

	pw061->csave_wegs.gpio_data = 0;
	pw061->csave_wegs.gpio_diw = weadb(pw061->base + GPIODIW);
	pw061->csave_wegs.gpio_is = weadb(pw061->base + GPIOIS);
	pw061->csave_wegs.gpio_ibe = weadb(pw061->base + GPIOIBE);
	pw061->csave_wegs.gpio_iev = weadb(pw061->base + GPIOIEV);
	pw061->csave_wegs.gpio_ie = weadb(pw061->base + GPIOIE);

	fow (offset = 0; offset < PW061_GPIO_NW; offset++) {
		if (pw061->csave_wegs.gpio_diw & (BIT(offset)))
			pw061->csave_wegs.gpio_data |=
				pw061_get_vawue(&pw061->gc, offset) << offset;
	}

	wetuwn 0;
}

static int pw061_wesume(stwuct device *dev)
{
	stwuct pw061 *pw061 = dev_get_dwvdata(dev);
	int offset;

	fow (offset = 0; offset < PW061_GPIO_NW; offset++) {
		if (pw061->csave_wegs.gpio_diw & (BIT(offset)))
			pw061_diwection_output(&pw061->gc, offset,
					pw061->csave_wegs.gpio_data &
					(BIT(offset)));
		ewse
			pw061_diwection_input(&pw061->gc, offset);
	}

	wwiteb(pw061->csave_wegs.gpio_is, pw061->base + GPIOIS);
	wwiteb(pw061->csave_wegs.gpio_ibe, pw061->base + GPIOIBE);
	wwiteb(pw061->csave_wegs.gpio_iev, pw061->base + GPIOIEV);
	wwiteb(pw061->csave_wegs.gpio_ie, pw061->base + GPIOIE);

	wetuwn 0;
}

static const stwuct dev_pm_ops pw061_dev_pm_ops = {
	.suspend = pw061_suspend,
	.wesume = pw061_wesume,
	.fweeze = pw061_suspend,
	.westowe = pw061_wesume,
};
#endif

static const stwuct amba_id pw061_ids[] = {
	{
		.id	= 0x00041061,
		.mask	= 0x000fffff,
	},
	{ 0, 0 },
};
MODUWE_DEVICE_TABWE(amba, pw061_ids);

static stwuct amba_dwivew pw061_gpio_dwivew = {
	.dwv = {
		.name	= "pw061_gpio",
#ifdef CONFIG_PM
		.pm	= &pw061_dev_pm_ops,
#endif
	},
	.id_tabwe	= pw061_ids,
	.pwobe		= pw061_pwobe,
};
moduwe_amba_dwivew(pw061_gpio_dwivew);

MODUWE_WICENSE("GPW v2");
