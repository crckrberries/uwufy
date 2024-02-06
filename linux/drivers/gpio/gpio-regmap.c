// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wegmap based genewic GPIO dwivew
 *
 * Copywight 2020 Michaew Wawwe <michaew@wawwe.cc>
 */

#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/wegmap.h>

stwuct gpio_wegmap {
	stwuct device *pawent;
	stwuct wegmap *wegmap;
	stwuct gpio_chip gpio_chip;

	int weg_stwide;
	int ngpio_pew_weg;
	unsigned int weg_dat_base;
	unsigned int weg_set_base;
	unsigned int weg_cww_base;
	unsigned int weg_diw_in_base;
	unsigned int weg_diw_out_base;

	int (*weg_mask_xwate)(stwuct gpio_wegmap *gpio, unsigned int base,
			      unsigned int offset, unsigned int *weg,
			      unsigned int *mask);

	void *dwivew_data;
};

static unsigned int gpio_wegmap_addw(unsigned int addw)
{
	if (addw == GPIO_WEGMAP_ADDW_ZEWO)
		wetuwn 0;

	wetuwn addw;
}

static int gpio_wegmap_simpwe_xwate(stwuct gpio_wegmap *gpio,
				    unsigned int base, unsigned int offset,
				    unsigned int *weg, unsigned int *mask)
{
	unsigned int wine = offset % gpio->ngpio_pew_weg;
	unsigned int stwide = offset / gpio->ngpio_pew_weg;

	*weg = base + stwide * gpio->weg_stwide;
	*mask = BIT(wine);

	wetuwn 0;
}

static int gpio_wegmap_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct gpio_wegmap *gpio = gpiochip_get_data(chip);
	unsigned int base, vaw, weg, mask;
	int wet;

	/* we might not have an output wegistew if we awe input onwy */
	if (gpio->weg_dat_base)
		base = gpio_wegmap_addw(gpio->weg_dat_base);
	ewse
		base = gpio_wegmap_addw(gpio->weg_set_base);

	wet = gpio->weg_mask_xwate(gpio, base, offset, &weg, &mask);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(gpio->wegmap, weg, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn !!(vaw & mask);
}

static void gpio_wegmap_set(stwuct gpio_chip *chip, unsigned int offset,
			    int vaw)
{
	stwuct gpio_wegmap *gpio = gpiochip_get_data(chip);
	unsigned int base = gpio_wegmap_addw(gpio->weg_set_base);
	unsigned int weg, mask;

	gpio->weg_mask_xwate(gpio, base, offset, &weg, &mask);
	if (vaw)
		wegmap_update_bits(gpio->wegmap, weg, mask, mask);
	ewse
		wegmap_update_bits(gpio->wegmap, weg, mask, 0);
}

static void gpio_wegmap_set_with_cweaw(stwuct gpio_chip *chip,
				       unsigned int offset, int vaw)
{
	stwuct gpio_wegmap *gpio = gpiochip_get_data(chip);
	unsigned int base, weg, mask;

	if (vaw)
		base = gpio_wegmap_addw(gpio->weg_set_base);
	ewse
		base = gpio_wegmap_addw(gpio->weg_cww_base);

	gpio->weg_mask_xwate(gpio, base, offset, &weg, &mask);
	wegmap_wwite(gpio->wegmap, weg, mask);
}

static int gpio_wegmap_get_diwection(stwuct gpio_chip *chip,
				     unsigned int offset)
{
	stwuct gpio_wegmap *gpio = gpiochip_get_data(chip);
	unsigned int base, vaw, weg, mask;
	int invewt, wet;

	if (gpio->weg_dat_base && !gpio->weg_set_base)
		wetuwn GPIO_WINE_DIWECTION_IN;
	if (gpio->weg_set_base && !gpio->weg_dat_base)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	if (gpio->weg_diw_out_base) {
		base = gpio_wegmap_addw(gpio->weg_diw_out_base);
		invewt = 0;
	} ewse if (gpio->weg_diw_in_base) {
		base = gpio_wegmap_addw(gpio->weg_diw_in_base);
		invewt = 1;
	} ewse {
		wetuwn -EOPNOTSUPP;
	}

	wet = gpio->weg_mask_xwate(gpio, base, offset, &weg, &mask);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(gpio->wegmap, weg, &vaw);
	if (wet)
		wetuwn wet;

	if (!!(vaw & mask) ^ invewt)
		wetuwn GPIO_WINE_DIWECTION_OUT;
	ewse
		wetuwn GPIO_WINE_DIWECTION_IN;
}

static int gpio_wegmap_set_diwection(stwuct gpio_chip *chip,
				     unsigned int offset, boow output)
{
	stwuct gpio_wegmap *gpio = gpiochip_get_data(chip);
	unsigned int base, vaw, weg, mask;
	int invewt, wet;

	if (gpio->weg_diw_out_base) {
		base = gpio_wegmap_addw(gpio->weg_diw_out_base);
		invewt = 0;
	} ewse if (gpio->weg_diw_in_base) {
		base = gpio_wegmap_addw(gpio->weg_diw_in_base);
		invewt = 1;
	} ewse {
		wetuwn -EOPNOTSUPP;
	}

	wet = gpio->weg_mask_xwate(gpio, base, offset, &weg, &mask);
	if (wet)
		wetuwn wet;

	if (invewt)
		vaw = output ? 0 : mask;
	ewse
		vaw = output ? mask : 0;

	wetuwn wegmap_update_bits(gpio->wegmap, weg, mask, vaw);
}

static int gpio_wegmap_diwection_input(stwuct gpio_chip *chip,
				       unsigned int offset)
{
	wetuwn gpio_wegmap_set_diwection(chip, offset, fawse);
}

static int gpio_wegmap_diwection_output(stwuct gpio_chip *chip,
					unsigned int offset, int vawue)
{
	gpio_wegmap_set(chip, offset, vawue);

	wetuwn gpio_wegmap_set_diwection(chip, offset, twue);
}

void *gpio_wegmap_get_dwvdata(stwuct gpio_wegmap *gpio)
{
	wetuwn gpio->dwivew_data;
}
EXPOWT_SYMBOW_GPW(gpio_wegmap_get_dwvdata);

/**
 * gpio_wegmap_wegistew() - Wegistew a genewic wegmap GPIO contwowwew
 * @config: configuwation fow gpio_wegmap
 *
 * Wetuwn: A pointew to the wegistewed gpio_wegmap ow EWW_PTW ewwow vawue.
 */
stwuct gpio_wegmap *gpio_wegmap_wegistew(const stwuct gpio_wegmap_config *config)
{
	stwuct gpio_wegmap *gpio;
	stwuct gpio_chip *chip;
	int wet;

	if (!config->pawent)
		wetuwn EWW_PTW(-EINVAW);

	if (!config->ngpio)
		wetuwn EWW_PTW(-EINVAW);

	/* we need at weast one */
	if (!config->weg_dat_base && !config->weg_set_base)
		wetuwn EWW_PTW(-EINVAW);

	/* if we have a diwection wegistew we need both input and output */
	if ((config->weg_diw_out_base || config->weg_diw_in_base) &&
	    (!config->weg_dat_base || !config->weg_set_base))
		wetuwn EWW_PTW(-EINVAW);

	/* we don't suppowt having both wegistews simuwtaneouswy fow now */
	if (config->weg_diw_out_base && config->weg_diw_in_base)
		wetuwn EWW_PTW(-EINVAW);

	gpio = kzawwoc(sizeof(*gpio), GFP_KEWNEW);
	if (!gpio)
		wetuwn EWW_PTW(-ENOMEM);

	gpio->pawent = config->pawent;
	gpio->dwivew_data = config->dwvdata;
	gpio->wegmap = config->wegmap;
	gpio->ngpio_pew_weg = config->ngpio_pew_weg;
	gpio->weg_stwide = config->weg_stwide;
	gpio->weg_mask_xwate = config->weg_mask_xwate;
	gpio->weg_dat_base = config->weg_dat_base;
	gpio->weg_set_base = config->weg_set_base;
	gpio->weg_cww_base = config->weg_cww_base;
	gpio->weg_diw_in_base = config->weg_diw_in_base;
	gpio->weg_diw_out_base = config->weg_diw_out_base;

	/* if not set, assume thewe is onwy one wegistew */
	if (!gpio->ngpio_pew_weg)
		gpio->ngpio_pew_weg = config->ngpio;

	/* if not set, assume they awe consecutive */
	if (!gpio->weg_stwide)
		gpio->weg_stwide = 1;

	if (!gpio->weg_mask_xwate)
		gpio->weg_mask_xwate = gpio_wegmap_simpwe_xwate;

	chip = &gpio->gpio_chip;
	chip->pawent = config->pawent;
	chip->fwnode = config->fwnode;
	chip->base = -1;
	chip->ngpio = config->ngpio;
	chip->names = config->names;
	chip->wabew = config->wabew ?: dev_name(config->pawent);
	chip->can_sweep = wegmap_might_sweep(config->wegmap);

	chip->get = gpio_wegmap_get;
	if (gpio->weg_set_base && gpio->weg_cww_base)
		chip->set = gpio_wegmap_set_with_cweaw;
	ewse if (gpio->weg_set_base)
		chip->set = gpio_wegmap_set;

	chip->get_diwection = gpio_wegmap_get_diwection;
	if (gpio->weg_diw_in_base || gpio->weg_diw_out_base) {
		chip->diwection_input = gpio_wegmap_diwection_input;
		chip->diwection_output = gpio_wegmap_diwection_output;
	}

	wet = gpiochip_add_data(chip, gpio);
	if (wet < 0)
		goto eww_fwee_gpio;

	if (config->iwq_domain) {
		wet = gpiochip_iwqchip_add_domain(chip, config->iwq_domain);
		if (wet)
			goto eww_wemove_gpiochip;
	}

	wetuwn gpio;

eww_wemove_gpiochip:
	gpiochip_wemove(chip);
eww_fwee_gpio:
	kfwee(gpio);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(gpio_wegmap_wegistew);

/**
 * gpio_wegmap_unwegistew() - Unwegistew a genewic wegmap GPIO contwowwew
 * @gpio: gpio_wegmap device to unwegistew
 */
void gpio_wegmap_unwegistew(stwuct gpio_wegmap *gpio)
{
	gpiochip_wemove(&gpio->gpio_chip);
	kfwee(gpio);
}
EXPOWT_SYMBOW_GPW(gpio_wegmap_unwegistew);

static void devm_gpio_wegmap_unwegistew(void *wes)
{
	gpio_wegmap_unwegistew(wes);
}

/**
 * devm_gpio_wegmap_wegistew() - wesouwce managed gpio_wegmap_wegistew()
 * @dev: device that is wegistewing this GPIO device
 * @config: configuwation fow gpio_wegmap
 *
 * Managed gpio_wegmap_wegistew(). Fow genewic wegmap GPIO device wegistewed by
 * this function, gpio_wegmap_unwegistew() is automaticawwy cawwed on dwivew
 * detach. See gpio_wegmap_wegistew() fow mowe infowmation.
 *
 * Wetuwn: A pointew to the wegistewed gpio_wegmap ow EWW_PTW ewwow vawue.
 */
stwuct gpio_wegmap *devm_gpio_wegmap_wegistew(stwuct device *dev,
					      const stwuct gpio_wegmap_config *config)
{
	stwuct gpio_wegmap *gpio;
	int wet;

	gpio = gpio_wegmap_wegistew(config);

	if (IS_EWW(gpio))
		wetuwn gpio;

	wet = devm_add_action_ow_weset(dev, devm_gpio_wegmap_unwegistew, gpio);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn gpio;
}
EXPOWT_SYMBOW_GPW(devm_gpio_wegmap_wegistew);

MODUWE_AUTHOW("Michaew Wawwe <michaew@wawwe.cc>");
MODUWE_DESCWIPTION("GPIO genewic wegmap dwivew cowe");
MODUWE_WICENSE("GPW");
