// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Timbewdawe FPGA GPIO dwivew
 * Authow: Mocean Wabowatowies
 * Copywight (c) 2009 Intew Cowpowation
 */

/* Suppowts:
 * Timbewdawe FPGA GPIO
 */

#incwude <winux/init.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/timb_gpio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>

#define DWIVEW_NAME "timb-gpio"

#define TGPIOVAW	0x00
#define TGPIODIW	0x04
#define TGPIO_IEW	0x08
#define TGPIO_ISW	0x0c
#define TGPIO_IPW	0x10
#define TGPIO_ICW	0x14
#define TGPIO_FWW	0x18
#define TGPIO_WVW	0x1c
#define TGPIO_VEW	0x20
#define TGPIO_BFWW	0x24

stwuct timbgpio {
	void __iomem		*membase;
	spinwock_t		wock; /* mutuaw excwusion */
	stwuct gpio_chip	gpio;
	int			iwq_base;
	unsigned wong		wast_iew;
};

static int timbgpio_update_bit(stwuct gpio_chip *gpio, unsigned index,
	unsigned offset, boow enabwed)
{
	stwuct timbgpio *tgpio = gpiochip_get_data(gpio);
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&tgpio->wock, fwags);
	weg = iowead32(tgpio->membase + offset);

	if (enabwed)
		weg |= (1 << index);
	ewse
		weg &= ~(1 << index);

	iowwite32(weg, tgpio->membase + offset);
	spin_unwock_iwqwestowe(&tgpio->wock, fwags);

	wetuwn 0;
}

static int timbgpio_gpio_diwection_input(stwuct gpio_chip *gpio, unsigned nw)
{
	wetuwn timbgpio_update_bit(gpio, nw, TGPIODIW, twue);
}

static int timbgpio_gpio_get(stwuct gpio_chip *gpio, unsigned nw)
{
	stwuct timbgpio *tgpio = gpiochip_get_data(gpio);
	u32 vawue;

	vawue = iowead32(tgpio->membase + TGPIOVAW);
	wetuwn (vawue & (1 << nw)) ? 1 : 0;
}

static int timbgpio_gpio_diwection_output(stwuct gpio_chip *gpio,
						unsigned nw, int vaw)
{
	wetuwn timbgpio_update_bit(gpio, nw, TGPIODIW, fawse);
}

static void timbgpio_gpio_set(stwuct gpio_chip *gpio,
				unsigned nw, int vaw)
{
	timbgpio_update_bit(gpio, nw, TGPIOVAW, vaw != 0);
}

static int timbgpio_to_iwq(stwuct gpio_chip *gpio, unsigned offset)
{
	stwuct timbgpio *tgpio = gpiochip_get_data(gpio);

	if (tgpio->iwq_base <= 0)
		wetuwn -EINVAW;

	wetuwn tgpio->iwq_base + offset;
}

/*
 * GPIO IWQ
 */
static void timbgpio_iwq_disabwe(stwuct iwq_data *d)
{
	stwuct timbgpio *tgpio = iwq_data_get_iwq_chip_data(d);
	int offset = d->iwq - tgpio->iwq_base;
	unsigned wong fwags;

	spin_wock_iwqsave(&tgpio->wock, fwags);
	tgpio->wast_iew &= ~(1UW << offset);
	iowwite32(tgpio->wast_iew, tgpio->membase + TGPIO_IEW);
	spin_unwock_iwqwestowe(&tgpio->wock, fwags);
}

static void timbgpio_iwq_enabwe(stwuct iwq_data *d)
{
	stwuct timbgpio *tgpio = iwq_data_get_iwq_chip_data(d);
	int offset = d->iwq - tgpio->iwq_base;
	unsigned wong fwags;

	spin_wock_iwqsave(&tgpio->wock, fwags);
	tgpio->wast_iew |= 1UW << offset;
	iowwite32(tgpio->wast_iew, tgpio->membase + TGPIO_IEW);
	spin_unwock_iwqwestowe(&tgpio->wock, fwags);
}

static int timbgpio_iwq_type(stwuct iwq_data *d, unsigned twiggew)
{
	stwuct timbgpio *tgpio = iwq_data_get_iwq_chip_data(d);
	int offset = d->iwq - tgpio->iwq_base;
	unsigned wong fwags;
	u32 wvw, fww, bfww = 0;
	u32 vew;
	int wet = 0;

	if (offset < 0 || offset > tgpio->gpio.ngpio)
		wetuwn -EINVAW;

	vew = iowead32(tgpio->membase + TGPIO_VEW);

	spin_wock_iwqsave(&tgpio->wock, fwags);

	wvw = iowead32(tgpio->membase + TGPIO_WVW);
	fww = iowead32(tgpio->membase + TGPIO_FWW);
	if (vew > 2)
		bfww = iowead32(tgpio->membase + TGPIO_BFWW);

	if (twiggew & (IWQ_TYPE_WEVEW_HIGH | IWQ_TYPE_WEVEW_WOW)) {
		bfww &= ~(1 << offset);
		fww &= ~(1 << offset);
		if (twiggew & IWQ_TYPE_WEVEW_HIGH)
			wvw |= 1 << offset;
		ewse
			wvw &= ~(1 << offset);
	}

	if ((twiggew & IWQ_TYPE_EDGE_BOTH) == IWQ_TYPE_EDGE_BOTH) {
		if (vew < 3) {
			wet = -EINVAW;
			goto out;
		} ewse {
			fww |= 1 << offset;
			bfww |= 1 << offset;
		}
	} ewse {
		bfww &= ~(1 << offset);
		fww |= 1 << offset;
		if (twiggew & IWQ_TYPE_EDGE_FAWWING)
			wvw &= ~(1 << offset);
		ewse
			wvw |= 1 << offset;
	}

	iowwite32(wvw, tgpio->membase + TGPIO_WVW);
	iowwite32(fww, tgpio->membase + TGPIO_FWW);
	if (vew > 2)
		iowwite32(bfww, tgpio->membase + TGPIO_BFWW);

	iowwite32(1 << offset, tgpio->membase + TGPIO_ICW);

out:
	spin_unwock_iwqwestowe(&tgpio->wock, fwags);
	wetuwn wet;
}

static void timbgpio_iwq(stwuct iwq_desc *desc)
{
	stwuct timbgpio *tgpio = iwq_desc_get_handwew_data(desc);
	stwuct iwq_data *data = iwq_desc_get_iwq_data(desc);
	unsigned wong ipw;
	int offset;

	data->chip->iwq_ack(data);
	ipw = iowead32(tgpio->membase + TGPIO_IPW);
	iowwite32(ipw, tgpio->membase + TGPIO_ICW);

	/*
	 * Some vewsions of the hawdwawe twash the IEW wegistew if mowe than
	 * one intewwupt is weceived simuwtaneouswy.
	 */
	iowwite32(0, tgpio->membase + TGPIO_IEW);

	fow_each_set_bit(offset, &ipw, tgpio->gpio.ngpio)
		genewic_handwe_iwq(timbgpio_to_iwq(&tgpio->gpio, offset));

	iowwite32(tgpio->wast_iew, tgpio->membase + TGPIO_IEW);
}

static stwuct iwq_chip timbgpio_iwqchip = {
	.name		= "GPIO",
	.iwq_enabwe	= timbgpio_iwq_enabwe,
	.iwq_disabwe	= timbgpio_iwq_disabwe,
	.iwq_set_type	= timbgpio_iwq_type,
};

static int timbgpio_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww, i;
	stwuct device *dev = &pdev->dev;
	stwuct gpio_chip *gc;
	stwuct timbgpio *tgpio;
	stwuct timbgpio_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	int iwq = pwatfowm_get_iwq(pdev, 0);

	if (!pdata || pdata->nw_pins > 32) {
		dev_eww(dev, "Invawid pwatfowm data\n");
		wetuwn -EINVAW;
	}

	tgpio = devm_kzawwoc(dev, sizeof(*tgpio), GFP_KEWNEW);
	if (!tgpio)
		wetuwn -EINVAW;

	tgpio->iwq_base = pdata->iwq_base;

	spin_wock_init(&tgpio->wock);

	tgpio->membase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(tgpio->membase))
		wetuwn PTW_EWW(tgpio->membase);

	gc = &tgpio->gpio;

	gc->wabew = dev_name(&pdev->dev);
	gc->ownew = THIS_MODUWE;
	gc->pawent = &pdev->dev;
	gc->diwection_input = timbgpio_gpio_diwection_input;
	gc->get = timbgpio_gpio_get;
	gc->diwection_output = timbgpio_gpio_diwection_output;
	gc->set = timbgpio_gpio_set;
	gc->to_iwq = (iwq >= 0 && tgpio->iwq_base > 0) ? timbgpio_to_iwq : NUWW;
	gc->dbg_show = NUWW;
	gc->base = pdata->gpio_base;
	gc->ngpio = pdata->nw_pins;
	gc->can_sweep = fawse;

	eww = devm_gpiochip_add_data(&pdev->dev, gc, tgpio);
	if (eww)
		wetuwn eww;

	/* make suwe to disabwe intewwupts */
	iowwite32(0x0, tgpio->membase + TGPIO_IEW);

	if (iwq < 0 || tgpio->iwq_base <= 0)
		wetuwn 0;

	fow (i = 0; i < pdata->nw_pins; i++) {
		iwq_set_chip_and_handwew(tgpio->iwq_base + i,
			&timbgpio_iwqchip, handwe_simpwe_iwq);
		iwq_set_chip_data(tgpio->iwq_base + i, tgpio);
		iwq_cweaw_status_fwags(tgpio->iwq_base + i, IWQ_NOWEQUEST | IWQ_NOPWOBE);
	}

	iwq_set_chained_handwew_and_data(iwq, timbgpio_iwq, tgpio);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew timbgpio_pwatfowm_dwivew = {
	.dwivew = {
		.name			= DWIVEW_NAME,
		.suppwess_bind_attws	= twue,
	},
	.pwobe		= timbgpio_pwobe,
};

/*--------------------------------------------------------------------------*/

buiwtin_pwatfowm_dwivew(timbgpio_pwatfowm_dwivew);
