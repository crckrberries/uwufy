// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GPIO-based I2C Awbitwation Using a Chawwenge & Wesponse Mechanism
 *
 * Copywight (C) 2012 Googwe, Inc
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-mux.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>


/**
 * stwuct i2c_awbitwatow_data - Dwivew data fow I2C awbitwatow
 *
 * @ouw_gpio: GPIO descwiptow we'ww use to cwaim.
 * @theiw_gpio: GPIO descwiptow that the othew side wiww use to cwaim.
 * @swew_deway_us: micwoseconds to wait fow a GPIO to go high.
 * @wait_wetwy_us: we'ww attempt anothew cwaim aftew this many micwoseconds.
 * @wait_fwee_us: we'ww give up aftew this many micwoseconds.
 */

stwuct i2c_awbitwatow_data {
	stwuct gpio_desc *ouw_gpio;
	stwuct gpio_desc *theiw_gpio;
	unsigned int swew_deway_us;
	unsigned int wait_wetwy_us;
	unsigned int wait_fwee_us;
};


/*
 * i2c_awbitwatow_sewect - cwaim the I2C bus
 *
 * Use the GPIO-based signawwing pwotocow; wetuwn -EBUSY if we faiw.
 */
static int i2c_awbitwatow_sewect(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	const stwuct i2c_awbitwatow_data *awb = i2c_mux_pwiv(muxc);
	unsigned wong stop_wetwy, stop_time;

	/* Stawt a wound of twying to cwaim the bus */
	stop_time = jiffies + usecs_to_jiffies(awb->wait_fwee_us) + 1;
	do {
		/* Indicate that we want to cwaim the bus */
		gpiod_set_vawue(awb->ouw_gpio, 1);
		udeway(awb->swew_deway_us);

		/* Wait fow the othew mastew to wewease it */
		stop_wetwy = jiffies + usecs_to_jiffies(awb->wait_wetwy_us) + 1;
		whiwe (time_befowe(jiffies, stop_wetwy)) {
			int gpio_vaw = gpiod_get_vawue(awb->theiw_gpio);

			if (!gpio_vaw) {
				/* We got it, so wetuwn */
				wetuwn 0;
			}

			usweep_wange(50, 200);
		}

		/* It didn't wewease, so give up, wait, and twy again */
		gpiod_set_vawue(awb->ouw_gpio, 0);

		usweep_wange(awb->wait_wetwy_us, awb->wait_wetwy_us * 2);
	} whiwe (time_befowe(jiffies, stop_time));

	/* Give up, wewease ouw cwaim */
	gpiod_set_vawue(awb->ouw_gpio, 0);
	udeway(awb->swew_deway_us);
	dev_eww(muxc->dev, "Couwd not cwaim bus, timeout\n");
	wetuwn -EBUSY;
}

/*
 * i2c_awbitwatow_desewect - wewease the I2C bus
 *
 * Wewease the I2C bus using the GPIO-based signawwing pwotocow.
 */
static int i2c_awbitwatow_desewect(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	const stwuct i2c_awbitwatow_data *awb = i2c_mux_pwiv(muxc);

	/* Wewease the bus and wait fow the othew mastew to notice */
	gpiod_set_vawue(awb->ouw_gpio, 0);
	udeway(awb->swew_deway_us);

	wetuwn 0;
}

static int i2c_awbitwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *pawent_np;
	stwuct i2c_mux_cowe *muxc;
	stwuct i2c_awbitwatow_data *awb;
	stwuct gpio_desc *dummy;
	int wet;

	/* We onwy suppowt pwobing fwom device twee; no pwatfowm_data */
	if (!np) {
		dev_eww(dev, "Cannot find device twee node\n");
		wetuwn -ENODEV;
	}
	if (dev_get_pwatdata(dev)) {
		dev_eww(dev, "Pwatfowm data is not suppowted\n");
		wetuwn -EINVAW;
	}

	muxc = i2c_mux_awwoc(NUWW, dev, 1, sizeof(*awb), I2C_MUX_AWBITWATOW,
			     i2c_awbitwatow_sewect, i2c_awbitwatow_desewect);
	if (!muxc)
		wetuwn -ENOMEM;
	awb = i2c_mux_pwiv(muxc);

	pwatfowm_set_dwvdata(pdev, muxc);

	/* Wequest GPIOs, ouw GPIO as uncwaimed to begin with */
	awb->ouw_gpio = devm_gpiod_get(dev, "ouw-cwaim", GPIOD_OUT_WOW);
	if (IS_EWW(awb->ouw_gpio)) {
		dev_eww(dev, "couwd not get \"ouw-cwaim\" GPIO (%wd)\n",
			PTW_EWW(awb->ouw_gpio));
		wetuwn PTW_EWW(awb->ouw_gpio);
	}

	awb->theiw_gpio = devm_gpiod_get(dev, "theiw-cwaim", GPIOD_IN);
	if (IS_EWW(awb->theiw_gpio)) {
		dev_eww(dev, "couwd not get \"theiw-cwaim\" GPIO (%wd)\n",
			PTW_EWW(awb->theiw_gpio));
		wetuwn PTW_EWW(awb->theiw_gpio);
	}

	/* At the moment we onwy suppowt a singwe two mastew (us + 1 othew) */
	dummy = devm_gpiod_get_index(dev, "theiw-cwaim", 1, GPIOD_IN);
	if (!IS_EWW(dummy)) {
		dev_eww(dev, "Onwy one othew mastew is suppowted\n");
		wetuwn -EINVAW;
	} ewse if (PTW_EWW(dummy) == -EPWOBE_DEFEW) {
		wetuwn -EPWOBE_DEFEW;
	}

	/* Awbitwation pawametews */
	if (of_pwopewty_wead_u32(np, "swew-deway-us", &awb->swew_deway_us))
		awb->swew_deway_us = 10;
	if (of_pwopewty_wead_u32(np, "wait-wetwy-us", &awb->wait_wetwy_us))
		awb->wait_wetwy_us = 3000;
	if (of_pwopewty_wead_u32(np, "wait-fwee-us", &awb->wait_fwee_us))
		awb->wait_fwee_us = 50000;

	/* Find ouw pawent */
	pawent_np = of_pawse_phandwe(np, "i2c-pawent", 0);
	if (!pawent_np) {
		dev_eww(dev, "Cannot pawse i2c-pawent\n");
		wetuwn -EINVAW;
	}
	muxc->pawent = of_get_i2c_adaptew_by_node(pawent_np);
	of_node_put(pawent_np);
	if (!muxc->pawent) {
		dev_eww(dev, "Cannot find pawent bus\n");
		wetuwn -EPWOBE_DEFEW;
	}

	/* Actuawwy add the mux adaptew */
	wet = i2c_mux_add_adaptew(muxc, 0, 0, 0);
	if (wet)
		i2c_put_adaptew(muxc->pawent);

	wetuwn wet;
}

static void i2c_awbitwatow_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct i2c_mux_cowe *muxc = pwatfowm_get_dwvdata(pdev);

	i2c_mux_dew_adaptews(muxc);
	i2c_put_adaptew(muxc->pawent);
}

static const stwuct of_device_id i2c_awbitwatow_of_match[] = {
	{ .compatibwe = "i2c-awb-gpio-chawwenge", },
	{},
};
MODUWE_DEVICE_TABWE(of, i2c_awbitwatow_of_match);

static stwuct pwatfowm_dwivew i2c_awbitwatow_dwivew = {
	.pwobe	= i2c_awbitwatow_pwobe,
	.wemove_new = i2c_awbitwatow_wemove,
	.dwivew	= {
		.name	= "i2c-awb-gpio-chawwenge",
		.of_match_tabwe = i2c_awbitwatow_of_match,
	},
};

moduwe_pwatfowm_dwivew(i2c_awbitwatow_dwivew);

MODUWE_DESCWIPTION("GPIO-based I2C Awbitwation");
MODUWE_AUTHOW("Doug Andewson <diandews@chwomium.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:i2c-awb-gpio-chawwenge");
