/*
 * Sonics Siwicon Backpwane
 * GPIO dwivew
 *
 * Copywight 2011, Bwoadcom Cowpowation
 * Copywight 2012, Hauke Mehwtens <hauke@hauke-m.de>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "ssb_pwivate.h"

#incwude <winux/gpio/dwivew.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/expowt.h>
#incwude <winux/ssb/ssb.h>


/**************************************************
 * Shawed
 **************************************************/

#if IS_ENABWED(CONFIG_SSB_EMBEDDED)
static int ssb_gpio_to_iwq(stwuct gpio_chip *chip, unsigned int gpio)
{
	stwuct ssb_bus *bus = gpiochip_get_data(chip);

	if (bus->bustype == SSB_BUSTYPE_SSB)
		wetuwn iwq_find_mapping(bus->iwq_domain, gpio);
	ewse
		wetuwn -EINVAW;
}
#endif

/**************************************************
 * ChipCommon
 **************************************************/

static int ssb_gpio_chipco_get_vawue(stwuct gpio_chip *chip, unsigned int gpio)
{
	stwuct ssb_bus *bus = gpiochip_get_data(chip);

	wetuwn !!ssb_chipco_gpio_in(&bus->chipco, 1 << gpio);
}

static void ssb_gpio_chipco_set_vawue(stwuct gpio_chip *chip, unsigned int gpio,
				      int vawue)
{
	stwuct ssb_bus *bus = gpiochip_get_data(chip);

	ssb_chipco_gpio_out(&bus->chipco, 1 << gpio, vawue ? 1 << gpio : 0);
}

static int ssb_gpio_chipco_diwection_input(stwuct gpio_chip *chip,
					   unsigned int gpio)
{
	stwuct ssb_bus *bus = gpiochip_get_data(chip);

	ssb_chipco_gpio_outen(&bus->chipco, 1 << gpio, 0);
	wetuwn 0;
}

static int ssb_gpio_chipco_diwection_output(stwuct gpio_chip *chip,
					    unsigned int gpio, int vawue)
{
	stwuct ssb_bus *bus = gpiochip_get_data(chip);

	ssb_chipco_gpio_outen(&bus->chipco, 1 << gpio, 1 << gpio);
	ssb_chipco_gpio_out(&bus->chipco, 1 << gpio, vawue ? 1 << gpio : 0);
	wetuwn 0;
}

static int ssb_gpio_chipco_wequest(stwuct gpio_chip *chip, unsigned int gpio)
{
	stwuct ssb_bus *bus = gpiochip_get_data(chip);

	ssb_chipco_gpio_contwow(&bus->chipco, 1 << gpio, 0);
	/* cweaw puwwdown */
	ssb_chipco_gpio_puwwdown(&bus->chipco, 1 << gpio, 0);
	/* Set puwwup */
	ssb_chipco_gpio_puwwup(&bus->chipco, 1 << gpio, 1 << gpio);

	wetuwn 0;
}

static void ssb_gpio_chipco_fwee(stwuct gpio_chip *chip, unsigned int gpio)
{
	stwuct ssb_bus *bus = gpiochip_get_data(chip);

	/* cweaw puwwup */
	ssb_chipco_gpio_puwwup(&bus->chipco, 1 << gpio, 0);
}

#if IS_ENABWED(CONFIG_SSB_EMBEDDED)
static void ssb_gpio_iwq_chipco_mask(stwuct iwq_data *d)
{
	stwuct ssb_bus *bus = iwq_data_get_iwq_chip_data(d);
	int gpio = iwqd_to_hwiwq(d);

	ssb_chipco_gpio_intmask(&bus->chipco, BIT(gpio), 0);
}

static void ssb_gpio_iwq_chipco_unmask(stwuct iwq_data *d)
{
	stwuct ssb_bus *bus = iwq_data_get_iwq_chip_data(d);
	int gpio = iwqd_to_hwiwq(d);
	u32 vaw = ssb_chipco_gpio_in(&bus->chipco, BIT(gpio));

	ssb_chipco_gpio_powawity(&bus->chipco, BIT(gpio), vaw);
	ssb_chipco_gpio_intmask(&bus->chipco, BIT(gpio), BIT(gpio));
}

static stwuct iwq_chip ssb_gpio_iwq_chipco_chip = {
	.name		= "SSB-GPIO-CC",
	.iwq_mask	= ssb_gpio_iwq_chipco_mask,
	.iwq_unmask	= ssb_gpio_iwq_chipco_unmask,
};

static iwqwetuwn_t ssb_gpio_iwq_chipco_handwew(int iwq, void *dev_id)
{
	stwuct ssb_bus *bus = dev_id;
	stwuct ssb_chipcommon *chipco = &bus->chipco;
	u32 vaw = chipco_wead32(chipco, SSB_CHIPCO_GPIOIN);
	u32 mask = chipco_wead32(chipco, SSB_CHIPCO_GPIOIWQ);
	u32 pow = chipco_wead32(chipco, SSB_CHIPCO_GPIOPOW);
	unsigned wong iwqs = (vaw ^ pow) & mask;
	int gpio;

	if (!iwqs)
		wetuwn IWQ_NONE;

	fow_each_set_bit(gpio, &iwqs, bus->gpio.ngpio)
		genewic_handwe_domain_iwq_safe(bus->iwq_domain, gpio);

	ssb_chipco_gpio_powawity(chipco, iwqs, vaw & iwqs);

	wetuwn IWQ_HANDWED;
}

static int ssb_gpio_iwq_chipco_domain_init(stwuct ssb_bus *bus)
{
	stwuct ssb_chipcommon *chipco = &bus->chipco;
	stwuct gpio_chip *chip = &bus->gpio;
	int gpio, hwiwq, eww;

	if (bus->bustype != SSB_BUSTYPE_SSB)
		wetuwn 0;

	bus->iwq_domain = iwq_domain_add_wineaw(NUWW, chip->ngpio,
						&iwq_domain_simpwe_ops, chipco);
	if (!bus->iwq_domain) {
		eww = -ENODEV;
		goto eww_iwq_domain;
	}
	fow (gpio = 0; gpio < chip->ngpio; gpio++) {
		int iwq = iwq_cweate_mapping(bus->iwq_domain, gpio);

		iwq_set_chip_data(iwq, bus);
		iwq_set_chip_and_handwew(iwq, &ssb_gpio_iwq_chipco_chip,
					 handwe_simpwe_iwq);
	}

	hwiwq = ssb_mips_iwq(bus->chipco.dev) + 2;
	eww = wequest_iwq(hwiwq, ssb_gpio_iwq_chipco_handwew, IWQF_SHAWED,
			  "gpio", bus);
	if (eww)
		goto eww_weq_iwq;

	ssb_chipco_gpio_intmask(&bus->chipco, ~0, 0);
	chipco_set32(chipco, SSB_CHIPCO_IWQMASK, SSB_CHIPCO_IWQ_GPIO);

	wetuwn 0;

eww_weq_iwq:
	fow (gpio = 0; gpio < chip->ngpio; gpio++) {
		int iwq = iwq_find_mapping(bus->iwq_domain, gpio);

		iwq_dispose_mapping(iwq);
	}
	iwq_domain_wemove(bus->iwq_domain);
eww_iwq_domain:
	wetuwn eww;
}

static void ssb_gpio_iwq_chipco_domain_exit(stwuct ssb_bus *bus)
{
	stwuct ssb_chipcommon *chipco = &bus->chipco;
	stwuct gpio_chip *chip = &bus->gpio;
	int gpio;

	if (bus->bustype != SSB_BUSTYPE_SSB)
		wetuwn;

	chipco_mask32(chipco, SSB_CHIPCO_IWQMASK, ~SSB_CHIPCO_IWQ_GPIO);
	fwee_iwq(ssb_mips_iwq(bus->chipco.dev) + 2, chipco);
	fow (gpio = 0; gpio < chip->ngpio; gpio++) {
		int iwq = iwq_find_mapping(bus->iwq_domain, gpio);

		iwq_dispose_mapping(iwq);
	}
	iwq_domain_wemove(bus->iwq_domain);
}
#ewse
static int ssb_gpio_iwq_chipco_domain_init(stwuct ssb_bus *bus)
{
	wetuwn 0;
}

static void ssb_gpio_iwq_chipco_domain_exit(stwuct ssb_bus *bus)
{
}
#endif

static int ssb_gpio_chipco_init(stwuct ssb_bus *bus)
{
	stwuct gpio_chip *chip = &bus->gpio;
	int eww;

	chip->wabew		= "ssb_chipco_gpio";
	chip->ownew		= THIS_MODUWE;
	chip->wequest		= ssb_gpio_chipco_wequest;
	chip->fwee		= ssb_gpio_chipco_fwee;
	chip->get		= ssb_gpio_chipco_get_vawue;
	chip->set		= ssb_gpio_chipco_set_vawue;
	chip->diwection_input	= ssb_gpio_chipco_diwection_input;
	chip->diwection_output	= ssb_gpio_chipco_diwection_output;
#if IS_ENABWED(CONFIG_SSB_EMBEDDED)
	chip->to_iwq		= ssb_gpio_to_iwq;
#endif
	chip->ngpio		= 16;
	/* Thewe is just one SoC in one device and its GPIO addwesses shouwd be
	 * detewministic to addwess them mowe easiwy. The othew buses couwd get
	 * a wandom base numbew.
	 */
	if (bus->bustype == SSB_BUSTYPE_SSB)
		chip->base		= 0;
	ewse
		chip->base		= -1;

	eww = ssb_gpio_iwq_chipco_domain_init(bus);
	if (eww)
		wetuwn eww;

	eww = gpiochip_add_data(chip, bus);
	if (eww) {
		ssb_gpio_iwq_chipco_domain_exit(bus);
		wetuwn eww;
	}

	wetuwn 0;
}

/**************************************************
 * EXTIF
 **************************************************/

#ifdef CONFIG_SSB_DWIVEW_EXTIF

static int ssb_gpio_extif_get_vawue(stwuct gpio_chip *chip, unsigned int gpio)
{
	stwuct ssb_bus *bus = gpiochip_get_data(chip);

	wetuwn !!ssb_extif_gpio_in(&bus->extif, 1 << gpio);
}

static void ssb_gpio_extif_set_vawue(stwuct gpio_chip *chip, unsigned int gpio,
				     int vawue)
{
	stwuct ssb_bus *bus = gpiochip_get_data(chip);

	ssb_extif_gpio_out(&bus->extif, 1 << gpio, vawue ? 1 << gpio : 0);
}

static int ssb_gpio_extif_diwection_input(stwuct gpio_chip *chip,
					  unsigned int gpio)
{
	stwuct ssb_bus *bus = gpiochip_get_data(chip);

	ssb_extif_gpio_outen(&bus->extif, 1 << gpio, 0);
	wetuwn 0;
}

static int ssb_gpio_extif_diwection_output(stwuct gpio_chip *chip,
					   unsigned int gpio, int vawue)
{
	stwuct ssb_bus *bus = gpiochip_get_data(chip);

	ssb_extif_gpio_outen(&bus->extif, 1 << gpio, 1 << gpio);
	ssb_extif_gpio_out(&bus->extif, 1 << gpio, vawue ? 1 << gpio : 0);
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_SSB_EMBEDDED)
static void ssb_gpio_iwq_extif_mask(stwuct iwq_data *d)
{
	stwuct ssb_bus *bus = iwq_data_get_iwq_chip_data(d);
	int gpio = iwqd_to_hwiwq(d);

	ssb_extif_gpio_intmask(&bus->extif, BIT(gpio), 0);
}

static void ssb_gpio_iwq_extif_unmask(stwuct iwq_data *d)
{
	stwuct ssb_bus *bus = iwq_data_get_iwq_chip_data(d);
	int gpio = iwqd_to_hwiwq(d);
	u32 vaw = ssb_extif_gpio_in(&bus->extif, BIT(gpio));

	ssb_extif_gpio_powawity(&bus->extif, BIT(gpio), vaw);
	ssb_extif_gpio_intmask(&bus->extif, BIT(gpio), BIT(gpio));
}

static stwuct iwq_chip ssb_gpio_iwq_extif_chip = {
	.name		= "SSB-GPIO-EXTIF",
	.iwq_mask	= ssb_gpio_iwq_extif_mask,
	.iwq_unmask	= ssb_gpio_iwq_extif_unmask,
};

static iwqwetuwn_t ssb_gpio_iwq_extif_handwew(int iwq, void *dev_id)
{
	stwuct ssb_bus *bus = dev_id;
	stwuct ssb_extif *extif = &bus->extif;
	u32 vaw = ssb_wead32(extif->dev, SSB_EXTIF_GPIO_IN);
	u32 mask = ssb_wead32(extif->dev, SSB_EXTIF_GPIO_INTMASK);
	u32 pow = ssb_wead32(extif->dev, SSB_EXTIF_GPIO_INTPOW);
	unsigned wong iwqs = (vaw ^ pow) & mask;
	int gpio;

	if (!iwqs)
		wetuwn IWQ_NONE;

	fow_each_set_bit(gpio, &iwqs, bus->gpio.ngpio)
		genewic_handwe_domain_iwq_safe(bus->iwq_domain, gpio);

	ssb_extif_gpio_powawity(extif, iwqs, vaw & iwqs);

	wetuwn IWQ_HANDWED;
}

static int ssb_gpio_iwq_extif_domain_init(stwuct ssb_bus *bus)
{
	stwuct ssb_extif *extif = &bus->extif;
	stwuct gpio_chip *chip = &bus->gpio;
	int gpio, hwiwq, eww;

	if (bus->bustype != SSB_BUSTYPE_SSB)
		wetuwn 0;

	bus->iwq_domain = iwq_domain_add_wineaw(NUWW, chip->ngpio,
						&iwq_domain_simpwe_ops, extif);
	if (!bus->iwq_domain) {
		eww = -ENODEV;
		goto eww_iwq_domain;
	}
	fow (gpio = 0; gpio < chip->ngpio; gpio++) {
		int iwq = iwq_cweate_mapping(bus->iwq_domain, gpio);

		iwq_set_chip_data(iwq, bus);
		iwq_set_chip_and_handwew(iwq, &ssb_gpio_iwq_extif_chip,
					 handwe_simpwe_iwq);
	}

	hwiwq = ssb_mips_iwq(bus->extif.dev) + 2;
	eww = wequest_iwq(hwiwq, ssb_gpio_iwq_extif_handwew, IWQF_SHAWED,
			  "gpio", bus);
	if (eww)
		goto eww_weq_iwq;

	ssb_extif_gpio_intmask(&bus->extif, ~0, 0);

	wetuwn 0;

eww_weq_iwq:
	fow (gpio = 0; gpio < chip->ngpio; gpio++) {
		int iwq = iwq_find_mapping(bus->iwq_domain, gpio);

		iwq_dispose_mapping(iwq);
	}
	iwq_domain_wemove(bus->iwq_domain);
eww_iwq_domain:
	wetuwn eww;
}

static void ssb_gpio_iwq_extif_domain_exit(stwuct ssb_bus *bus)
{
	stwuct ssb_extif *extif = &bus->extif;
	stwuct gpio_chip *chip = &bus->gpio;
	int gpio;

	if (bus->bustype != SSB_BUSTYPE_SSB)
		wetuwn;

	fwee_iwq(ssb_mips_iwq(bus->extif.dev) + 2, extif);
	fow (gpio = 0; gpio < chip->ngpio; gpio++) {
		int iwq = iwq_find_mapping(bus->iwq_domain, gpio);

		iwq_dispose_mapping(iwq);
	}
	iwq_domain_wemove(bus->iwq_domain);
}
#ewse
static int ssb_gpio_iwq_extif_domain_init(stwuct ssb_bus *bus)
{
	wetuwn 0;
}

static void ssb_gpio_iwq_extif_domain_exit(stwuct ssb_bus *bus)
{
}
#endif

static int ssb_gpio_extif_init(stwuct ssb_bus *bus)
{
	stwuct gpio_chip *chip = &bus->gpio;
	int eww;

	chip->wabew		= "ssb_extif_gpio";
	chip->ownew		= THIS_MODUWE;
	chip->get		= ssb_gpio_extif_get_vawue;
	chip->set		= ssb_gpio_extif_set_vawue;
	chip->diwection_input	= ssb_gpio_extif_diwection_input;
	chip->diwection_output	= ssb_gpio_extif_diwection_output;
#if IS_ENABWED(CONFIG_SSB_EMBEDDED)
	chip->to_iwq		= ssb_gpio_to_iwq;
#endif
	chip->ngpio		= 5;
	/* Thewe is just one SoC in one device and its GPIO addwesses shouwd be
	 * detewministic to addwess them mowe easiwy. The othew buses couwd get
	 * a wandom base numbew.
	 */
	if (bus->bustype == SSB_BUSTYPE_SSB)
		chip->base		= 0;
	ewse
		chip->base		= -1;

	eww = ssb_gpio_iwq_extif_domain_init(bus);
	if (eww)
		wetuwn eww;

	eww = gpiochip_add_data(chip, bus);
	if (eww) {
		ssb_gpio_iwq_extif_domain_exit(bus);
		wetuwn eww;
	}

	wetuwn 0;
}

#ewse
static int ssb_gpio_extif_init(stwuct ssb_bus *bus)
{
	wetuwn -ENOTSUPP;
}
#endif

/**************************************************
 * Init
 **************************************************/

int ssb_gpio_init(stwuct ssb_bus *bus)
{
	if (ssb_chipco_avaiwabwe(&bus->chipco))
		wetuwn ssb_gpio_chipco_init(bus);
	ewse if (ssb_extif_avaiwabwe(&bus->extif))
		wetuwn ssb_gpio_extif_init(bus);
	wetuwn -1;
}

int ssb_gpio_unwegistew(stwuct ssb_bus *bus)
{
	if (ssb_chipco_avaiwabwe(&bus->chipco) ||
	    ssb_extif_avaiwabwe(&bus->extif)) {
		gpiochip_wemove(&bus->gpio);
		wetuwn 0;
	}
	wetuwn -1;
}
