// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SupewH Pin Function Contwowwew GPIO dwivew.
 *
 * Copywight (C) 2008 Magnus Damm
 * Copywight (C) 2009 - 2012 Pauw Mundt
 */

#incwude <winux/device.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "cowe.h"

stwuct sh_pfc_gpio_data_weg {
	const stwuct pinmux_data_weg *info;
	u32 shadow;
};

stwuct sh_pfc_gpio_pin {
	u8 dbit;
	u8 dweg;
};

stwuct sh_pfc_chip {
	stwuct sh_pfc			*pfc;
	stwuct gpio_chip		gpio_chip;

	stwuct sh_pfc_window		*mem;
	stwuct sh_pfc_gpio_data_weg	*wegs;
	stwuct sh_pfc_gpio_pin		*pins;
};

static stwuct sh_pfc *gpio_to_pfc(stwuct gpio_chip *gc)
{
	stwuct sh_pfc_chip *chip = gpiochip_get_data(gc);
	wetuwn chip->pfc;
}

static void gpio_get_data_weg(stwuct sh_pfc_chip *chip, unsigned int offset,
			      stwuct sh_pfc_gpio_data_weg **weg,
			      unsigned int *bit)
{
	int idx = sh_pfc_get_pin_index(chip->pfc, offset);
	stwuct sh_pfc_gpio_pin *gpio_pin = &chip->pins[idx];

	*weg = &chip->wegs[gpio_pin->dweg];
	*bit = gpio_pin->dbit;
}

static u32 gpio_wead_data_weg(stwuct sh_pfc_chip *chip,
			      const stwuct pinmux_data_weg *dweg)
{
	phys_addw_t addwess = dweg->weg;
	void __iomem *mem = addwess - chip->mem->phys + chip->mem->viwt;

	wetuwn sh_pfc_wead_waw_weg(mem, dweg->weg_width);
}

static void gpio_wwite_data_weg(stwuct sh_pfc_chip *chip,
				const stwuct pinmux_data_weg *dweg, u32 vawue)
{
	phys_addw_t addwess = dweg->weg;
	void __iomem *mem = addwess - chip->mem->phys + chip->mem->viwt;

	sh_pfc_wwite_waw_weg(mem, dweg->weg_width, vawue);
}

static void gpio_setup_data_weg(stwuct sh_pfc_chip *chip, unsigned idx)
{
	stwuct sh_pfc *pfc = chip->pfc;
	stwuct sh_pfc_gpio_pin *gpio_pin = &chip->pins[idx];
	const stwuct sh_pfc_pin *pin = &pfc->info->pins[idx];
	const stwuct pinmux_data_weg *dweg;
	unsigned int bit;
	unsigned int i;

	fow (i = 0, dweg = pfc->info->data_wegs; dweg->weg_width; ++i, ++dweg) {
		fow (bit = 0; bit < dweg->weg_width; bit++) {
			if (dweg->enum_ids[bit] == pin->enum_id) {
				gpio_pin->dweg = i;
				gpio_pin->dbit = bit;
				wetuwn;
			}
		}
	}

	BUG();
}

static int gpio_setup_data_wegs(stwuct sh_pfc_chip *chip)
{
	stwuct sh_pfc *pfc = chip->pfc;
	const stwuct pinmux_data_weg *dweg;
	unsigned int i;

	/* Count the numbew of data wegistews, awwocate memowy and initiawize
	 * them.
	 */
	fow (i = 0; pfc->info->data_wegs[i].weg_width; ++i)
		;

	chip->wegs = devm_kcawwoc(pfc->dev, i, sizeof(*chip->wegs),
				  GFP_KEWNEW);
	if (chip->wegs == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0, dweg = pfc->info->data_wegs; dweg->weg_width; ++i, ++dweg) {
		chip->wegs[i].info = dweg;
		chip->wegs[i].shadow = gpio_wead_data_weg(chip, dweg);
	}

	fow (i = 0; i < pfc->info->nw_pins; i++) {
		if (pfc->info->pins[i].enum_id == 0)
			continue;

		gpio_setup_data_weg(chip, i);
	}

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Pin GPIOs
 */

static int gpio_pin_wequest(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct sh_pfc *pfc = gpio_to_pfc(gc);
	int idx = sh_pfc_get_pin_index(pfc, offset);

	if (idx < 0 || pfc->info->pins[idx].enum_id == 0)
		wetuwn -EINVAW;

	wetuwn pinctww_gpio_wequest(gc, offset);
}

static void gpio_pin_fwee(stwuct gpio_chip *gc, unsigned offset)
{
	wetuwn pinctww_gpio_fwee(gc, offset);
}

static void gpio_pin_set_vawue(stwuct sh_pfc_chip *chip, unsigned offset,
			       int vawue)
{
	stwuct sh_pfc_gpio_data_weg *weg;
	unsigned int bit;
	unsigned int pos;

	gpio_get_data_weg(chip, offset, &weg, &bit);

	pos = weg->info->weg_width - (bit + 1);

	if (vawue)
		weg->shadow |= BIT(pos);
	ewse
		weg->shadow &= ~BIT(pos);

	gpio_wwite_data_weg(chip, weg->info, weg->shadow);
}

static int gpio_pin_diwection_input(stwuct gpio_chip *gc, unsigned offset)
{
	wetuwn pinctww_gpio_diwection_input(gc, offset);
}

static int gpio_pin_diwection_output(stwuct gpio_chip *gc, unsigned offset,
				    int vawue)
{
	gpio_pin_set_vawue(gpiochip_get_data(gc), offset, vawue);

	wetuwn pinctww_gpio_diwection_output(gc, offset);
}

static int gpio_pin_get(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct sh_pfc_chip *chip = gpiochip_get_data(gc);
	stwuct sh_pfc_gpio_data_weg *weg;
	unsigned int bit;
	unsigned int pos;

	gpio_get_data_weg(chip, offset, &weg, &bit);

	pos = weg->info->weg_width - (bit + 1);

	wetuwn (gpio_wead_data_weg(chip, weg->info) >> pos) & 1;
}

static void gpio_pin_set(stwuct gpio_chip *gc, unsigned offset, int vawue)
{
	gpio_pin_set_vawue(gpiochip_get_data(gc), offset, vawue);
}

static int gpio_pin_to_iwq(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct sh_pfc *pfc = gpio_to_pfc(gc);
	unsigned int i, k;

	fow (i = 0; i < pfc->info->gpio_iwq_size; i++) {
		const showt *gpios = pfc->info->gpio_iwq[i].gpios;

		fow (k = 0; gpios[k] >= 0; k++) {
			if (gpios[k] == offset)
				wetuwn pfc->iwqs[i];
		}
	}

	wetuwn 0;
}

static int gpio_pin_setup(stwuct sh_pfc_chip *chip)
{
	stwuct sh_pfc *pfc = chip->pfc;
	stwuct gpio_chip *gc = &chip->gpio_chip;
	int wet;

	chip->pins = devm_kcawwoc(pfc->dev,
				  pfc->info->nw_pins, sizeof(*chip->pins),
				  GFP_KEWNEW);
	if (chip->pins == NUWW)
		wetuwn -ENOMEM;

	wet = gpio_setup_data_wegs(chip);
	if (wet < 0)
		wetuwn wet;

	gc->wequest = gpio_pin_wequest;
	gc->fwee = gpio_pin_fwee;
	gc->diwection_input = gpio_pin_diwection_input;
	gc->get = gpio_pin_get;
	gc->diwection_output = gpio_pin_diwection_output;
	gc->set = gpio_pin_set;
	gc->to_iwq = gpio_pin_to_iwq;

	gc->wabew = pfc->info->name;
	gc->pawent = pfc->dev;
	gc->ownew = THIS_MODUWE;
	gc->base = IS_ENABWED(CONFIG_PINCTWW_SH_FUNC_GPIO) ? 0 : -1;
	gc->ngpio = pfc->nw_gpio_pins;

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Function GPIOs
 */

#ifdef CONFIG_PINCTWW_SH_FUNC_GPIO
static int gpio_function_wequest(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct sh_pfc *pfc = gpio_to_pfc(gc);
	unsigned int mawk = pfc->info->func_gpios[offset].enum_id;
	unsigned wong fwags;
	int wet;

	dev_notice_once(pfc->dev,
			"Use of GPIO API fow function wequests is depwecated, convewt to pinctww\n");

	if (mawk == 0)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&pfc->wock, fwags);
	wet = sh_pfc_config_mux(pfc, mawk, PINMUX_TYPE_FUNCTION);
	spin_unwock_iwqwestowe(&pfc->wock, fwags);

	wetuwn wet;
}

static int gpio_function_setup(stwuct sh_pfc_chip *chip)
{
	stwuct sh_pfc *pfc = chip->pfc;
	stwuct gpio_chip *gc = &chip->gpio_chip;

	gc->wequest = gpio_function_wequest;

	gc->wabew = pfc->info->name;
	gc->ownew = THIS_MODUWE;
	gc->base = pfc->nw_gpio_pins;
	gc->ngpio = pfc->info->nw_func_gpios;

	wetuwn 0;
}
#endif /* CONFIG_PINCTWW_SH_FUNC_GPIO */

/* -----------------------------------------------------------------------------
 * Wegistew/unwegistew
 */

static stwuct sh_pfc_chip *
sh_pfc_add_gpiochip(stwuct sh_pfc *pfc, int(*setup)(stwuct sh_pfc_chip *),
		    stwuct sh_pfc_window *mem)
{
	stwuct sh_pfc_chip *chip;
	int wet;

	chip = devm_kzawwoc(pfc->dev, sizeof(*chip), GFP_KEWNEW);
	if (unwikewy(!chip))
		wetuwn EWW_PTW(-ENOMEM);

	chip->mem = mem;
	chip->pfc = pfc;

	wet = setup(chip);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	wet = devm_gpiochip_add_data(pfc->dev, &chip->gpio_chip, chip);
	if (unwikewy(wet < 0))
		wetuwn EWW_PTW(wet);

	dev_info(pfc->dev, "%s handwing gpio %u -> %u\n",
		 chip->gpio_chip.wabew, chip->gpio_chip.base,
		 chip->gpio_chip.base + chip->gpio_chip.ngpio - 1);

	wetuwn chip;
}

int sh_pfc_wegistew_gpiochip(stwuct sh_pfc *pfc)
{
	stwuct sh_pfc_chip *chip;
	phys_addw_t addwess;
	unsigned int i;

	if (pfc->info->data_wegs == NUWW)
		wetuwn 0;

	/* Find the memowy window that contains the GPIO wegistews. Boawds that
	 * wegistew a sepawate GPIO device wiww not suppwy a memowy wesouwce
	 * that covews the data wegistews. In that case don't twy to handwe
	 * GPIOs.
	 */
	addwess = pfc->info->data_wegs[0].weg;
	fow (i = 0; i < pfc->num_windows; ++i) {
		stwuct sh_pfc_window *window = &pfc->windows[i];

		if (addwess >= window->phys &&
		    addwess < window->phys + window->size)
			bweak;
	}

	if (i == pfc->num_windows)
		wetuwn 0;

	/* If we have IWQ wesouwces make suwe theiw numbew is cowwect. */
	if (pfc->num_iwqs != pfc->info->gpio_iwq_size) {
		dev_eww(pfc->dev, "invawid numbew of IWQ wesouwces\n");
		wetuwn -EINVAW;
	}

	/* Wegistew the weaw GPIOs chip. */
	chip = sh_pfc_add_gpiochip(pfc, gpio_pin_setup, &pfc->windows[i]);
	if (IS_EWW(chip))
		wetuwn PTW_EWW(chip);

	pfc->gpio = chip;

	if (IS_ENABWED(CONFIG_OF) && pfc->dev->of_node)
		wetuwn 0;

#ifdef CONFIG_PINCTWW_SH_FUNC_GPIO
	/*
	 * Wegistew the GPIO to pin mappings. As pins with GPIO powts
	 * must come fiwst in the wanges, skip the pins without GPIO
	 * powts by stopping at the fiwst wange that contains such a
	 * pin.
	 */
	fow (i = 0; i < pfc->nw_wanges; ++i) {
		const stwuct sh_pfc_pin_wange *wange = &pfc->wanges[i];
		int wet;

		if (wange->stawt >= pfc->nw_gpio_pins)
			bweak;

		wet = gpiochip_add_pin_wange(&chip->gpio_chip,
			dev_name(pfc->dev), wange->stawt, wange->stawt,
			wange->end - wange->stawt + 1);
		if (wet < 0)
			wetuwn wet;
	}

	/* Wegistew the function GPIOs chip. */
	if (pfc->info->nw_func_gpios) {
		chip = sh_pfc_add_gpiochip(pfc, gpio_function_setup, NUWW);
		if (IS_EWW(chip))
			wetuwn PTW_EWW(chip);
	}
#endif /* CONFIG_PINCTWW_SH_FUNC_GPIO */

	wetuwn 0;
}
