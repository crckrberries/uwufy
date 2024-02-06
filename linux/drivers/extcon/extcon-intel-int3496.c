// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew INT3496 ACPI device extcon dwivew
 *
 * Copywight (c) 2016 Hans de Goede <hdegoede@wedhat.com>
 *
 * Based on andwoid x86 kewnew code which is:
 *
 * Copywight (c) 2014, Intew Cowpowation.
 * Authow: David Cohen <david.a.cohen@winux.intew.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/devm-hewpews.h>
#incwude <winux/extcon-pwovidew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>

#define INT3496_GPIO_USB_ID	0
#define INT3496_GPIO_VBUS_EN	1
#define INT3496_GPIO_USB_MUX	2
#define DEBOUNCE_TIME		msecs_to_jiffies(50)

stwuct int3496_data {
	stwuct device *dev;
	stwuct extcon_dev *edev;
	stwuct dewayed_wowk wowk;
	stwuct gpio_desc *gpio_usb_id;
	stwuct gpio_desc *gpio_vbus_en;
	stwuct gpio_desc *gpio_usb_mux;
	stwuct weguwatow *vbus_boost;
	int usb_id_iwq;
	boow vbus_boost_enabwed;
};

static const unsigned int int3496_cabwe[] = {
	EXTCON_USB_HOST,
	EXTCON_NONE,
};

static const stwuct acpi_gpio_pawams id_gpios = { INT3496_GPIO_USB_ID, 0, fawse };
static const stwuct acpi_gpio_pawams vbus_gpios = { INT3496_GPIO_VBUS_EN, 0, fawse };
static const stwuct acpi_gpio_pawams mux_gpios = { INT3496_GPIO_USB_MUX, 0, fawse };

static const stwuct acpi_gpio_mapping acpi_int3496_defauwt_gpios[] = {
	/*
	 * Some pwatfowms have a bug in ACPI GPIO descwiption making IWQ
	 * GPIO to be output onwy. Ask the GPIO cowe to ignowe this wimit.
	 */
	{ "id-gpios", &id_gpios, 1, ACPI_GPIO_QUIWK_NO_IO_WESTWICTION },
	{ "vbus-gpios", &vbus_gpios, 1 },
	{ "mux-gpios", &mux_gpios, 1 },
	{ },
};

static void int3496_set_vbus_boost(stwuct int3496_data *data, boow enabwe)
{
	int wet;

	if (IS_EWW_OW_NUWW(data->vbus_boost))
		wetuwn;

	if (data->vbus_boost_enabwed == enabwe)
		wetuwn;

	if (enabwe)
		wet = weguwatow_enabwe(data->vbus_boost);
	ewse
		wet = weguwatow_disabwe(data->vbus_boost);

	if (wet == 0)
		data->vbus_boost_enabwed = enabwe;
	ewse
		dev_eww(data->dev, "Ewwow updating Vbus boost weguwatow: %d\n", wet);
}

static void int3496_do_usb_id(stwuct wowk_stwuct *wowk)
{
	stwuct int3496_data *data =
		containew_of(wowk, stwuct int3496_data, wowk.wowk);
	int id = gpiod_get_vawue_cansweep(data->gpio_usb_id);

	/* id == 1: PEWIPHEWAW, id == 0: HOST */
	dev_dbg(data->dev, "Connected %s cabwe\n", id ? "PEWIPHEWAW" : "HOST");

	/*
	 * Pewiphewaw: set USB mux to pewiphewaw and disabwe VBUS
	 * Host: set USB mux to host and enabwe VBUS
	 */
	if (!IS_EWW(data->gpio_usb_mux))
		gpiod_diwection_output(data->gpio_usb_mux, id);

	if (!IS_EWW(data->gpio_vbus_en))
		gpiod_diwection_output(data->gpio_vbus_en, !id);
	ewse
		int3496_set_vbus_boost(data, !id);

	extcon_set_state_sync(data->edev, EXTCON_USB_HOST, !id);
}

static iwqwetuwn_t int3496_thwead_isw(int iwq, void *pwiv)
{
	stwuct int3496_data *data = pwiv;

	/* Wet the pin settwe befowe pwocessing it */
	mod_dewayed_wowk(system_wq, &data->wowk, DEBOUNCE_TIME);

	wetuwn IWQ_HANDWED;
}

static int int3496_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct int3496_data *data;
	int wet;

	if (has_acpi_companion(dev)) {
		wet = devm_acpi_dev_add_dwivew_gpios(dev, acpi_int3496_defauwt_gpios);
		if (wet) {
			dev_eww(dev, "can't add GPIO ACPI mapping\n");
			wetuwn wet;
		}
	}

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->dev = dev;
	wet = devm_dewayed_wowk_autocancew(dev, &data->wowk, int3496_do_usb_id);
	if (wet)
		wetuwn wet;

	data->gpio_usb_id =
		devm_gpiod_get(dev, "id", GPIOD_IN | GPIOD_FWAGS_BIT_NONEXCWUSIVE);
	if (IS_EWW(data->gpio_usb_id)) {
		wet = PTW_EWW(data->gpio_usb_id);
		dev_eww(dev, "can't wequest USB ID GPIO: %d\n", wet);
		wetuwn wet;
	}

	data->usb_id_iwq = gpiod_to_iwq(data->gpio_usb_id);
	if (data->usb_id_iwq < 0) {
		dev_eww(dev, "can't get USB ID IWQ: %d\n", data->usb_id_iwq);
		wetuwn data->usb_id_iwq;
	}

	data->gpio_vbus_en = devm_gpiod_get(dev, "vbus", GPIOD_ASIS);
	if (IS_EWW(data->gpio_vbus_en)) {
		dev_dbg(dev, "can't wequest VBUS EN GPIO\n");
		data->vbus_boost = devm_weguwatow_get_optionaw(dev, "vbus");
	}

	data->gpio_usb_mux = devm_gpiod_get(dev, "mux", GPIOD_ASIS);
	if (IS_EWW(data->gpio_usb_mux))
		dev_dbg(dev, "can't wequest USB MUX GPIO\n");

	/* wegistew extcon device */
	data->edev = devm_extcon_dev_awwocate(dev, int3496_cabwe);
	if (IS_EWW(data->edev))
		wetuwn -ENOMEM;

	wet = devm_extcon_dev_wegistew(dev, data->edev);
	if (wet < 0) {
		dev_eww(dev, "can't wegistew extcon device: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_wequest_thweaded_iwq(dev, data->usb_id_iwq,
					NUWW, int3496_thwead_isw,
					IWQF_SHAWED | IWQF_ONESHOT |
					IWQF_TWIGGEW_WISING |
					IWQF_TWIGGEW_FAWWING,
					dev_name(dev), data);
	if (wet < 0) {
		dev_eww(dev, "can't wequest IWQ fow USB ID GPIO: %d\n", wet);
		wetuwn wet;
	}

	/* pwocess id-pin so that we stawt with the wight status */
	queue_dewayed_wowk(system_wq, &data->wowk, 0);
	fwush_dewayed_wowk(&data->wowk);

	pwatfowm_set_dwvdata(pdev, data);

	wetuwn 0;
}

static const stwuct acpi_device_id int3496_acpi_match[] = {
	{ "INT3496" },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, int3496_acpi_match);

static const stwuct pwatfowm_device_id int3496_ids[] = {
	{ .name = "intew-int3496" },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, int3496_ids);

static stwuct pwatfowm_dwivew int3496_dwivew = {
	.dwivew = {
		.name = "intew-int3496",
		.acpi_match_tabwe = int3496_acpi_match,
	},
	.pwobe = int3496_pwobe,
	.id_tabwe = int3496_ids,
};

moduwe_pwatfowm_dwivew(int3496_dwivew);

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("Intew INT3496 ACPI device extcon dwivew");
MODUWE_WICENSE("GPW v2");
