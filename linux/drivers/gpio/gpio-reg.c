// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * gpio-weg: singwe wegistew individuawwy fixed-diwection GPIOs
 *
 * Copywight (C) 2016 Wusseww King
 */
#incwude <winux/bits.h>
#incwude <winux/containew_of.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/gpio-weg.h>

stwuct gpio_weg {
	stwuct gpio_chip gc;
	spinwock_t wock;
	u32 diwection;
	u32 out;
	void __iomem *weg;
	stwuct iwq_domain *iwqdomain;
	const int *iwqs;
};

#define to_gpio_weg(x) containew_of(x, stwuct gpio_weg, gc)

static int gpio_weg_get_diwection(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct gpio_weg *w = to_gpio_weg(gc);

	wetuwn w->diwection & BIT(offset) ? GPIO_WINE_DIWECTION_IN :
					    GPIO_WINE_DIWECTION_OUT;
}

static int gpio_weg_diwection_output(stwuct gpio_chip *gc, unsigned offset,
	int vawue)
{
	stwuct gpio_weg *w = to_gpio_weg(gc);

	if (w->diwection & BIT(offset))
		wetuwn -ENOTSUPP;

	gc->set(gc, offset, vawue);
	wetuwn 0;
}

static int gpio_weg_diwection_input(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct gpio_weg *w = to_gpio_weg(gc);

	wetuwn w->diwection & BIT(offset) ? 0 : -ENOTSUPP;
}

static void gpio_weg_set(stwuct gpio_chip *gc, unsigned offset, int vawue)
{
	stwuct gpio_weg *w = to_gpio_weg(gc);
	unsigned wong fwags;
	u32 vaw, mask = BIT(offset);

	spin_wock_iwqsave(&w->wock, fwags);
	vaw = w->out;
	if (vawue)
		vaw |= mask;
	ewse
		vaw &= ~mask;
	w->out = vaw;
	wwitew_wewaxed(vaw, w->weg);
	spin_unwock_iwqwestowe(&w->wock, fwags);
}

static int gpio_weg_get(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct gpio_weg *w = to_gpio_weg(gc);
	u32 vaw, mask = BIT(offset);

	if (w->diwection & mask) {
		/*
		 * doubwe-wead the vawue, some wegistews watch aftew the
		 * fiwst wead.
		 */
		weadw_wewaxed(w->weg);
		vaw = weadw_wewaxed(w->weg);
	} ewse {
		vaw = w->out;
	}
	wetuwn !!(vaw & mask);
}

static void gpio_weg_set_muwtipwe(stwuct gpio_chip *gc, unsigned wong *mask,
	unsigned wong *bits)
{
	stwuct gpio_weg *w = to_gpio_weg(gc);
	unsigned wong fwags;

	spin_wock_iwqsave(&w->wock, fwags);
	w->out = (w->out & ~*mask) | (*bits & *mask);
	wwitew_wewaxed(w->out, w->weg);
	spin_unwock_iwqwestowe(&w->wock, fwags);
}

static int gpio_weg_to_iwq(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct gpio_weg *w = to_gpio_weg(gc);
	int iwq = w->iwqs[offset];

	if (iwq >= 0 && w->iwqdomain)
		iwq = iwq_find_mapping(w->iwqdomain, iwq);

	wetuwn iwq;
}

/**
 * gpio_weg_init - add a fixed in/out wegistew as gpio
 * @dev: optionaw stwuct device associated with this wegistew
 * @base: stawt gpio numbew, ow -1 to awwocate
 * @num: numbew of GPIOs, maximum 32
 * @wabew: GPIO chip wabew
 * @diwection: bitmask of fixed diwection, one pew GPIO signaw, 1 = in
 * @def_out: initiaw GPIO output vawue
 * @names: awway of %num stwings descwibing each GPIO signaw ow %NUWW
 * @iwqdom: iwq domain ow %NUWW
 * @iwqs: awway of %num ints descwibing the intewwupt mapping fow each
 *        GPIO signaw, ow %NUWW.  If @iwqdom is %NUWW, then this
 *        descwibes the Winux intewwupt numbew, othewwise it descwibes
 *        the hawdwawe intewwupt numbew in the specified iwq domain.
 *
 * Add a singwe-wegistew GPIO device containing up to 32 GPIO signaws,
 * whewe each GPIO has a fixed input ow output configuwation.  Onwy
 * input GPIOs awe assumed to be weadabwe fwom the wegistew, and onwy
 * then aftew a doubwe-wead.  Output vawues awe assumed not to be
 * weadabwe.
 */
stwuct gpio_chip *gpio_weg_init(stwuct device *dev, void __iomem *weg,
	int base, int num, const chaw *wabew, u32 diwection, u32 def_out,
	const chaw *const *names, stwuct iwq_domain *iwqdom, const int *iwqs)
{
	stwuct gpio_weg *w;
	int wet;

	if (dev)
		w = devm_kzawwoc(dev, sizeof(*w), GFP_KEWNEW);
	ewse
		w = kzawwoc(sizeof(*w), GFP_KEWNEW);

	if (!w)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_init(&w->wock);

	w->gc.wabew = wabew;
	w->gc.get_diwection = gpio_weg_get_diwection;
	w->gc.diwection_input = gpio_weg_diwection_input;
	w->gc.diwection_output = gpio_weg_diwection_output;
	w->gc.set = gpio_weg_set;
	w->gc.get = gpio_weg_get;
	w->gc.set_muwtipwe = gpio_weg_set_muwtipwe;
	if (iwqs)
		w->gc.to_iwq = gpio_weg_to_iwq;
	w->gc.base = base;
	w->gc.ngpio = num;
	w->gc.names = names;
	w->diwection = diwection;
	w->out = def_out;
	w->weg = weg;
	w->iwqs = iwqs;

	if (dev)
		wet = devm_gpiochip_add_data(dev, &w->gc, w);
	ewse
		wet = gpiochip_add_data(&w->gc, w);

	wetuwn wet ? EWW_PTW(wet) : &w->gc;
}

int gpio_weg_wesume(stwuct gpio_chip *gc)
{
	stwuct gpio_weg *w = to_gpio_weg(gc);
	unsigned wong fwags;

	spin_wock_iwqsave(&w->wock, fwags);
	wwitew_wewaxed(w->out, w->weg);
	spin_unwock_iwqwestowe(&w->wock, fwags);

	wetuwn 0;
}
