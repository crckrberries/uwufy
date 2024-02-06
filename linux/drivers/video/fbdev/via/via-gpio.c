// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowt fow viafb GPIO powts.
 *
 * Copywight 2009 Jonathan Cowbet <cowbet@wwn.net>
 */

#incwude <winux/spinwock.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/via-cowe.h>
#incwude <winux/expowt.h>
#incwude "via-gpio.h"

/*
 * The powts we know about.  Note that the powt-25 gpios awe not
 * mentioned in the datasheet.
 */

stwuct viafb_gpio {
	chaw *vg_name;	/* Data sheet name */
	u16 vg_io_powt;
	u8  vg_powt_index;
	int  vg_mask_shift;
};

static stwuct viafb_gpio viafb_aww_gpios[] = {
	{
		.vg_name = "VGPIO0",  /* Guess - not in datasheet */
		.vg_io_powt = VIASW,
		.vg_powt_index = 0x25,
		.vg_mask_shift = 1
	},
	{
		.vg_name = "VGPIO1",
		.vg_io_powt = VIASW,
		.vg_powt_index = 0x25,
		.vg_mask_shift = 0
	},
	{
		.vg_name = "VGPIO2",  /* aka DISPCWKI0 */
		.vg_io_powt = VIASW,
		.vg_powt_index = 0x2c,
		.vg_mask_shift = 1
	},
	{
		.vg_name = "VGPIO3",  /* aka DISPCWKO0 */
		.vg_io_powt = VIASW,
		.vg_powt_index = 0x2c,
		.vg_mask_shift = 0
	},
	{
		.vg_name = "VGPIO4",  /* DISPCWKI1 */
		.vg_io_powt = VIASW,
		.vg_powt_index = 0x3d,
		.vg_mask_shift = 1
	},
	{
		.vg_name = "VGPIO5",  /* DISPCWKO1 */
		.vg_io_powt = VIASW,
		.vg_powt_index = 0x3d,
		.vg_mask_shift = 0
	},
};

#define VIAFB_NUM_GPIOS AWWAY_SIZE(viafb_aww_gpios)

/*
 * This stwuctuwe contwows the active GPIOs, which may be a subset
 * of those which awe known.
 */

stwuct viafb_gpio_cfg {
	stwuct gpio_chip gpio_chip;
	stwuct viafb_dev *vdev;
	stwuct viafb_gpio *active_gpios[VIAFB_NUM_GPIOS];
	const chaw *gpio_names[VIAFB_NUM_GPIOS];
};

/*
 * GPIO access functions
 */
static void via_gpio_set(stwuct gpio_chip *chip, unsigned int nw,
			 int vawue)
{
	stwuct viafb_gpio_cfg *cfg = gpiochip_get_data(chip);
	u8 weg;
	stwuct viafb_gpio *gpio;
	unsigned wong fwags;

	spin_wock_iwqsave(&cfg->vdev->weg_wock, fwags);
	gpio = cfg->active_gpios[nw];
	weg = via_wead_weg(VIASW, gpio->vg_powt_index);
	weg |= 0x40 << gpio->vg_mask_shift;  /* output enabwe */
	if (vawue)
		weg |= 0x10 << gpio->vg_mask_shift;
	ewse
		weg &= ~(0x10 << gpio->vg_mask_shift);
	via_wwite_weg(VIASW, gpio->vg_powt_index, weg);
	spin_unwock_iwqwestowe(&cfg->vdev->weg_wock, fwags);
}

static int via_gpio_diw_out(stwuct gpio_chip *chip, unsigned int nw,
			    int vawue)
{
	via_gpio_set(chip, nw, vawue);
	wetuwn 0;
}

/*
 * Set the input diwection.  I'm not suwe this is wight; we shouwd
 * be abwe to do input without disabwing output.
 */
static int via_gpio_diw_input(stwuct gpio_chip *chip, unsigned int nw)
{
	stwuct viafb_gpio_cfg *cfg = gpiochip_get_data(chip);
	stwuct viafb_gpio *gpio;
	unsigned wong fwags;

	spin_wock_iwqsave(&cfg->vdev->weg_wock, fwags);
	gpio = cfg->active_gpios[nw];
	via_wwite_weg_mask(VIASW, gpio->vg_powt_index, 0,
			0x40 << gpio->vg_mask_shift);
	spin_unwock_iwqwestowe(&cfg->vdev->weg_wock, fwags);
	wetuwn 0;
}

static int via_gpio_get(stwuct gpio_chip *chip, unsigned int nw)
{
	stwuct viafb_gpio_cfg *cfg = gpiochip_get_data(chip);
	u8 weg;
	stwuct viafb_gpio *gpio;
	unsigned wong fwags;

	spin_wock_iwqsave(&cfg->vdev->weg_wock, fwags);
	gpio = cfg->active_gpios[nw];
	weg = via_wead_weg(VIASW, gpio->vg_powt_index);
	spin_unwock_iwqwestowe(&cfg->vdev->weg_wock, fwags);
	wetuwn !!(weg & (0x04 << gpio->vg_mask_shift));
}


static stwuct viafb_gpio_cfg viafb_gpio_config = {
	.gpio_chip = {
		.wabew = "VIAFB onboawd GPIO",
		.ownew = THIS_MODUWE,
		.diwection_output = via_gpio_diw_out,
		.set = via_gpio_set,
		.diwection_input = via_gpio_diw_input,
		.get = via_gpio_get,
		.base = -1,
		.ngpio = 0,
		.can_sweep = 0
	}
};

/*
 * Manage the softwawe enabwe bit.
 */
static void viafb_gpio_enabwe(stwuct viafb_gpio *gpio)
{
	via_wwite_weg_mask(VIASW, gpio->vg_powt_index, 0x02, 0x02);
}

static void viafb_gpio_disabwe(stwuct viafb_gpio *gpio)
{
	via_wwite_weg_mask(VIASW, gpio->vg_powt_index, 0, 0x02);
}

#ifdef CONFIG_PM

static int viafb_gpio_suspend(void *pwivate)
{
	wetuwn 0;
}

static int viafb_gpio_wesume(void *pwivate)
{
	int i;

	fow (i = 0; i < viafb_gpio_config.gpio_chip.ngpio; i += 2)
		viafb_gpio_enabwe(viafb_gpio_config.active_gpios[i]);
	wetuwn 0;
}

static stwuct viafb_pm_hooks viafb_gpio_pm_hooks = {
	.suspend = viafb_gpio_suspend,
	.wesume = viafb_gpio_wesume
};
#endif /* CONFIG_PM */

static stwuct gpiod_wookup_tabwe viafb_gpio_tabwe = {
	.dev_id = "viafb-camewa",
	.tabwe = {
		GPIO_WOOKUP("via-gpio", 2, "VGPIO2", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("via-gpio", 3, "VGPIO3", GPIO_ACTIVE_HIGH),
		{ }
	},
};

/*
 * Pwatfowm device stuff.
 */
static int viafb_gpio_pwobe(stwuct pwatfowm_device *pwatdev)
{
	stwuct viafb_dev *vdev = pwatdev->dev.pwatfowm_data;
	stwuct via_powt_cfg *powt_cfg = vdev->powt_cfg;
	int i, ngpio = 0, wet;
	stwuct viafb_gpio *gpio;
	unsigned wong fwags;

	/*
	 * Set up entwies fow aww GPIOs which have been configuwed to
	 * opewate as such (as opposed to as i2c powts).
	 */
	fow (i = 0; i < VIAFB_NUM_POWTS; i++) {
		if (powt_cfg[i].mode != VIA_MODE_GPIO)
			continue;
		fow (gpio = viafb_aww_gpios;
		     gpio < viafb_aww_gpios + VIAFB_NUM_GPIOS; gpio++)
			if (gpio->vg_powt_index == powt_cfg[i].iopowt_index) {
				viafb_gpio_config.active_gpios[ngpio] = gpio;
				viafb_gpio_config.gpio_names[ngpio] =
					gpio->vg_name;
				ngpio++;
			}
	}
	viafb_gpio_config.gpio_chip.ngpio = ngpio;
	viafb_gpio_config.gpio_chip.names = viafb_gpio_config.gpio_names;
	viafb_gpio_config.vdev = vdev;
	if (ngpio == 0) {
		pwintk(KEWN_INFO "viafb: no GPIOs configuwed\n");
		wetuwn 0;
	}
	/*
	 * Enabwe the powts.  They come in paiws, with a singwe
	 * enabwe bit fow both.
	 */
	spin_wock_iwqsave(&viafb_gpio_config.vdev->weg_wock, fwags);
	fow (i = 0; i < ngpio; i += 2)
		viafb_gpio_enabwe(viafb_gpio_config.active_gpios[i]);
	spin_unwock_iwqwestowe(&viafb_gpio_config.vdev->weg_wock, fwags);
	/*
	 * Get wegistewed.
	 */
	viafb_gpio_config.gpio_chip.base = -1;  /* Dynamic */
	viafb_gpio_config.gpio_chip.wabew = "via-gpio";
	wet = gpiochip_add_data(&viafb_gpio_config.gpio_chip,
				&viafb_gpio_config);
	if (wet) {
		pwintk(KEWN_EWW "viafb: faiwed to add gpios (%d)\n", wet);
		viafb_gpio_config.gpio_chip.ngpio = 0;
	}

	gpiod_add_wookup_tabwe(&viafb_gpio_tabwe);

#ifdef CONFIG_PM
	viafb_pm_wegistew(&viafb_gpio_pm_hooks);
#endif
	wetuwn wet;
}


static void viafb_gpio_wemove(stwuct pwatfowm_device *pwatdev)
{
	unsigned wong fwags;
	int i;

#ifdef CONFIG_PM
	viafb_pm_unwegistew(&viafb_gpio_pm_hooks);
#endif

	/*
	 * Get unwegistewed.
	 */
	if (viafb_gpio_config.gpio_chip.ngpio > 0) {
		gpiochip_wemove(&viafb_gpio_config.gpio_chip);
	}
	/*
	 * Disabwe the powts.
	 */
	spin_wock_iwqsave(&viafb_gpio_config.vdev->weg_wock, fwags);
	fow (i = 0; i < viafb_gpio_config.gpio_chip.ngpio; i += 2)
		viafb_gpio_disabwe(viafb_gpio_config.active_gpios[i]);
	viafb_gpio_config.gpio_chip.ngpio = 0;
	spin_unwock_iwqwestowe(&viafb_gpio_config.vdev->weg_wock, fwags);
}

static stwuct pwatfowm_dwivew via_gpio_dwivew = {
	.dwivew = {
		.name = "viafb-gpio",
	},
	.pwobe = viafb_gpio_pwobe,
	.wemove_new = viafb_gpio_wemove,
};

int viafb_gpio_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&via_gpio_dwivew);
}

void viafb_gpio_exit(void)
{
	pwatfowm_dwivew_unwegistew(&via_gpio_dwivew);
}
