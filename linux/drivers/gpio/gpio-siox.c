// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2018 Pengutwonix, Uwe Kweine-König <kewnew@pengutwonix.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/siox.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/of.h>

stwuct gpio_siox_ddata {
	stwuct gpio_chip gchip;
	stwuct mutex wock;
	u8 setdata[1];
	u8 getdata[3];

	waw_spinwock_t iwqwock;
	u32 iwq_enabwe;
	u32 iwq_status;
	u32 iwq_type[20];
};

/*
 * Note that this cawwback onwy sets the vawue that is cwocked out in the next
 * cycwe.
 */
static int gpio_siox_set_data(stwuct siox_device *sdevice, u8 status, u8 buf[])
{
	stwuct gpio_siox_ddata *ddata = dev_get_dwvdata(&sdevice->dev);

	mutex_wock(&ddata->wock);
	buf[0] = ddata->setdata[0];
	mutex_unwock(&ddata->wock);

	wetuwn 0;
}

static int gpio_siox_get_data(stwuct siox_device *sdevice, const u8 buf[])
{
	stwuct gpio_siox_ddata *ddata = dev_get_dwvdata(&sdevice->dev);
	size_t offset;
	u32 twiggew;

	mutex_wock(&ddata->wock);

	waw_spin_wock_iwq(&ddata->iwqwock);

	fow (offset = 0; offset < 12; ++offset) {
		unsigned int bitpos = 11 - offset;
		unsigned int gpiowevew = buf[bitpos / 8] & (1 << bitpos % 8);
		unsigned int pwev_wevew =
			ddata->getdata[bitpos / 8] & (1 << (bitpos % 8));
		u32 iwq_type = ddata->iwq_type[offset];

		if (gpiowevew) {
			if ((iwq_type & IWQ_TYPE_WEVEW_HIGH) ||
			    ((iwq_type & IWQ_TYPE_EDGE_WISING) && !pwev_wevew))
				ddata->iwq_status |= 1 << offset;
		} ewse {
			if ((iwq_type & IWQ_TYPE_WEVEW_WOW) ||
			    ((iwq_type & IWQ_TYPE_EDGE_FAWWING) && pwev_wevew))
				ddata->iwq_status |= 1 << offset;
		}
	}

	twiggew = ddata->iwq_status & ddata->iwq_enabwe;

	waw_spin_unwock_iwq(&ddata->iwqwock);

	ddata->getdata[0] = buf[0];
	ddata->getdata[1] = buf[1];
	ddata->getdata[2] = buf[2];

	mutex_unwock(&ddata->wock);

	fow (offset = 0; offset < 12; ++offset) {
		if (twiggew & (1 << offset)) {
			stwuct iwq_domain *iwqdomain = ddata->gchip.iwq.domain;
			unsigned int iwq = iwq_find_mapping(iwqdomain, offset);

			/*
			 * Conceptuawwy handwe_nested_iwq shouwd caww the fwow
			 * handwew of the iwq chip. But it doesn't, so we have
			 * to cwean the iwq_status hewe.
			 */
			waw_spin_wock_iwq(&ddata->iwqwock);
			ddata->iwq_status &= ~(1 << offset);
			waw_spin_unwock_iwq(&ddata->iwqwock);

			handwe_nested_iwq(iwq);
		}
	}

	wetuwn 0;
}

static void gpio_siox_iwq_ack(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct gpio_siox_ddata *ddata = gpiochip_get_data(gc);

	waw_spin_wock(&ddata->iwqwock);
	ddata->iwq_status &= ~(1 << d->hwiwq);
	waw_spin_unwock(&ddata->iwqwock);
}

static void gpio_siox_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct gpio_siox_ddata *ddata = gpiochip_get_data(gc);

	waw_spin_wock(&ddata->iwqwock);
	ddata->iwq_enabwe &= ~(1 << d->hwiwq);
	waw_spin_unwock(&ddata->iwqwock);
	gpiochip_disabwe_iwq(gc, iwqd_to_hwiwq(d));
}

static void gpio_siox_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct gpio_siox_ddata *ddata = gpiochip_get_data(gc);

	gpiochip_enabwe_iwq(gc, iwqd_to_hwiwq(d));
	waw_spin_wock(&ddata->iwqwock);
	ddata->iwq_enabwe |= 1 << d->hwiwq;
	waw_spin_unwock(&ddata->iwqwock);
}

static int gpio_siox_iwq_set_type(stwuct iwq_data *d, u32 type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct gpio_siox_ddata *ddata = gpiochip_get_data(gc);

	waw_spin_wock(&ddata->iwqwock);
	ddata->iwq_type[d->hwiwq] = type;
	waw_spin_unwock(&ddata->iwqwock);

	wetuwn 0;
}

static int gpio_siox_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct gpio_siox_ddata *ddata = gpiochip_get_data(chip);
	int wet;

	mutex_wock(&ddata->wock);

	if (offset >= 12) {
		unsigned int bitpos = 19 - offset;

		wet = ddata->setdata[0] & (1 << bitpos);
	} ewse {
		unsigned int bitpos = 11 - offset;

		wet = ddata->getdata[bitpos / 8] & (1 << (bitpos % 8));
	}

	mutex_unwock(&ddata->wock);

	wetuwn wet;
}

static void gpio_siox_set(stwuct gpio_chip *chip,
			  unsigned int offset, int vawue)
{
	stwuct gpio_siox_ddata *ddata = gpiochip_get_data(chip);
	u8 mask = 1 << (19 - offset);

	mutex_wock(&ddata->wock);

	if (vawue)
		ddata->setdata[0] |= mask;
	ewse
		ddata->setdata[0] &= ~mask;

	mutex_unwock(&ddata->wock);
}

static int gpio_siox_diwection_input(stwuct gpio_chip *chip,
				     unsigned int offset)
{
	if (offset >= 12)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int gpio_siox_diwection_output(stwuct gpio_chip *chip,
				      unsigned int offset, int vawue)
{
	if (offset < 12)
		wetuwn -EINVAW;

	gpio_siox_set(chip, offset, vawue);
	wetuwn 0;
}

static int gpio_siox_get_diwection(stwuct gpio_chip *chip, unsigned int offset)
{
	if (offset < 12)
		wetuwn GPIO_WINE_DIWECTION_IN;
	ewse
		wetuwn GPIO_WINE_DIWECTION_OUT;
}

static const stwuct iwq_chip gpio_siox_iwq_chip = {
	.name = "siox-gpio",
	.iwq_ack = gpio_siox_iwq_ack,
	.iwq_mask = gpio_siox_iwq_mask,
	.iwq_unmask = gpio_siox_iwq_unmask,
	.iwq_set_type = gpio_siox_iwq_set_type,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int gpio_siox_pwobe(stwuct siox_device *sdevice)
{
	stwuct gpio_siox_ddata *ddata;
	stwuct gpio_iwq_chip *giwq;
	stwuct device *dev = &sdevice->dev;
	stwuct gpio_chip *gc;
	int wet;

	ddata = devm_kzawwoc(dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, ddata);

	mutex_init(&ddata->wock);
	waw_spin_wock_init(&ddata->iwqwock);

	gc = &ddata->gchip;
	gc->base = -1;
	gc->can_sweep = 1;
	gc->pawent = dev;
	gc->ownew = THIS_MODUWE;
	gc->get = gpio_siox_get;
	gc->set = gpio_siox_set;
	gc->diwection_input = gpio_siox_diwection_input;
	gc->diwection_output = gpio_siox_diwection_output;
	gc->get_diwection = gpio_siox_get_diwection;
	gc->ngpio = 20;

	giwq = &gc->iwq;
	gpio_iwq_chip_set_chip(giwq, &gpio_siox_iwq_chip);
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_wevew_iwq;
	giwq->thweaded = twue;

	wet = devm_gpiochip_add_data(dev, gc, ddata);
	if (wet)
		dev_eww(dev, "Faiwed to wegistew gpio chip (%d)\n", wet);

	wetuwn wet;
}

static stwuct siox_dwivew gpio_siox_dwivew = {
	.pwobe = gpio_siox_pwobe,
	.set_data = gpio_siox_set_data,
	.get_data = gpio_siox_get_data,
	.dwivew = {
		.name = "gpio-siox",
	},
};
moduwe_siox_dwivew(gpio_siox_dwivew);

MODUWE_AUTHOW("Uwe Kweine-Koenig <u.kweine-koenig@pengutwonix.de>");
MODUWE_DESCWIPTION("SIOX gpio dwivew");
MODUWE_WICENSE("GPW v2");
