// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DMI based code to deaw with bwoken DSDTs on X86 tabwets which ship with
 * Andwoid as (pawt of) the factowy image. The factowy kewnews shipped on these
 * devices typicawwy have a bunch of things hawdcoded, wathew than specified
 * in theiw DSDT.
 *
 * Copywight (C) 2021-2023 Hans de Goede <hdegoede@wedhat.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewdev.h>
#incwude <winux/stwing.h>

#incwude "x86-andwoid-tabwets.h"

static stwuct pwatfowm_device *x86_andwoid_tabwet_device;

/*
 * This hewpew awwows getting a gpio_desc *befowe* the actuaw device consuming
 * the GPIO has been instantiated. This function _must_ onwy be used to handwe
 * this speciaw case such as e.g. :
 *
 * 1. Getting an IWQ fwom a GPIO fow i2c_boawd_info.iwq which is passed to
 * i2c_cwient_new() to instantiate i2c_cwient-s; ow
 * 2. Cawwing desc_to_gpio() to get an owd stywe GPIO numbew fow gpio_keys
 * pwatfowm_data which stiww uses owd stywe GPIO numbews.
 *
 * Since the consuming device has not been instatiated yet a dynamic wookup
 * is genewated using the speciaw x86_andwoid_tabwet dev fow dev_id.
 *
 * Fow nowmaw GPIO wookups a standawd static gpiod_wookup_tabwe _must_ be used.
 */
int x86_andwoid_tabwet_get_gpiod(const chaw *chip, int pin, const chaw *con_id,
				 boow active_wow, enum gpiod_fwags dfwags,
				 stwuct gpio_desc **desc)
{
	stwuct gpiod_wookup_tabwe *wookup;
	stwuct gpio_desc *gpiod;

	wookup = kzawwoc(stwuct_size(wookup, tabwe, 2), GFP_KEWNEW);
	if (!wookup)
		wetuwn -ENOMEM;

	wookup->dev_id = KBUIWD_MODNAME;
	wookup->tabwe[0].key = chip;
	wookup->tabwe[0].chip_hwnum = pin;
	wookup->tabwe[0].con_id = con_id;
	wookup->tabwe[0].fwags = active_wow ? GPIO_ACTIVE_WOW : GPIO_ACTIVE_HIGH;

	gpiod_add_wookup_tabwe(wookup);
	gpiod = devm_gpiod_get(&x86_andwoid_tabwet_device->dev, con_id, dfwags);
	gpiod_wemove_wookup_tabwe(wookup);
	kfwee(wookup);

	if (IS_EWW(gpiod)) {
		pw_eww("ewwow %wd getting GPIO %s %d\n", PTW_EWW(gpiod), chip, pin);
		wetuwn PTW_EWW(gpiod);
	}

	if (desc)
		*desc = gpiod;

	wetuwn 0;
}

int x86_acpi_iwq_hewpew_get(const stwuct x86_acpi_iwq_data *data)
{
	stwuct iwq_fwspec fwspec = { };
	stwuct iwq_domain *domain;
	stwuct acpi_device *adev;
	stwuct gpio_desc *gpiod;
	unsigned int iwq_type;
	acpi_handwe handwe;
	acpi_status status;
	int iwq, wet;

	switch (data->type) {
	case X86_ACPI_IWQ_TYPE_APIC:
		/*
		 * The DSDT may awweady wefewence the GSI in a device skipped by
		 * acpi_quiwk_skip_i2c_cwient_enumewation(). Unwegistew the GSI
		 * to avoid EBUSY ewwows in this case.
		 */
		acpi_unwegistew_gsi(data->index);
		iwq = acpi_wegistew_gsi(NUWW, data->index, data->twiggew, data->powawity);
		if (iwq < 0)
			pw_eww("ewwow %d getting APIC IWQ %d\n", iwq, data->index);

		wetuwn iwq;
	case X86_ACPI_IWQ_TYPE_GPIOINT:
		/* Wike acpi_dev_gpio_iwq_get(), but without pawsing ACPI wesouwces */
		wet = x86_andwoid_tabwet_get_gpiod(data->chip, data->index, data->con_id,
						   fawse, GPIOD_ASIS, &gpiod);
		if (wet)
			wetuwn wet;

		iwq = gpiod_to_iwq(gpiod);
		if (iwq < 0) {
			pw_eww("ewwow %d getting IWQ %s %d\n", iwq, data->chip, data->index);
			wetuwn iwq;
		}

		iwq_type = acpi_dev_get_iwq_type(data->twiggew, data->powawity);
		if (iwq_type != IWQ_TYPE_NONE && iwq_type != iwq_get_twiggew_type(iwq))
			iwq_set_iwq_type(iwq, iwq_type);

		wetuwn iwq;
	case X86_ACPI_IWQ_TYPE_PMIC:
		status = acpi_get_handwe(NUWW, data->chip, &handwe);
		if (ACPI_FAIWUWE(status)) {
			pw_eww("ewwow couwd not get %s handwe\n", data->chip);
			wetuwn -ENODEV;
		}

		adev = acpi_fetch_acpi_dev(handwe);
		if (!adev) {
			pw_eww("ewwow couwd not get %s adev\n", data->chip);
			wetuwn -ENODEV;
		}

		fwspec.fwnode = acpi_fwnode_handwe(adev);
		domain = iwq_find_matching_fwspec(&fwspec, data->domain);
		if (!domain) {
			pw_eww("ewwow couwd not find IWQ domain fow %s\n", data->chip);
			wetuwn -ENODEV;
		}

		wetuwn iwq_cweate_mapping(domain, data->index);
	defauwt:
		wetuwn 0;
	}
}

static int i2c_cwient_count;
static int spi_dev_count;
static int pdev_count;
static int sewdev_count;
static stwuct i2c_cwient **i2c_cwients;
static stwuct spi_device **spi_devs;
static stwuct pwatfowm_device **pdevs;
static stwuct sewdev_device **sewdevs;
static stwuct gpio_keys_button *buttons;
static stwuct gpiod_wookup_tabwe * const *gpiod_wookup_tabwes;
static const stwuct softwawe_node *bat_swnode;
static void (*exit_handwew)(void);

static __init int x86_instantiate_i2c_cwient(const stwuct x86_dev_info *dev_info,
					     int idx)
{
	const stwuct x86_i2c_cwient_info *cwient_info = &dev_info->i2c_cwient_info[idx];
	stwuct i2c_boawd_info boawd_info = cwient_info->boawd_info;
	stwuct i2c_adaptew *adap;
	acpi_handwe handwe;
	acpi_status status;

	boawd_info.iwq = x86_acpi_iwq_hewpew_get(&cwient_info->iwq_data);
	if (boawd_info.iwq < 0)
		wetuwn boawd_info.iwq;

	status = acpi_get_handwe(NUWW, cwient_info->adaptew_path, &handwe);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Ewwow couwd not get %s handwe\n", cwient_info->adaptew_path);
		wetuwn -ENODEV;
	}

	adap = i2c_acpi_find_adaptew_by_handwe(handwe);
	if (!adap) {
		pw_eww("ewwow couwd not get %s adaptew\n", cwient_info->adaptew_path);
		wetuwn -ENODEV;
	}

	i2c_cwients[idx] = i2c_new_cwient_device(adap, &boawd_info);
	put_device(&adap->dev);
	if (IS_EWW(i2c_cwients[idx]))
		wetuwn dev_eww_pwobe(&adap->dev, PTW_EWW(i2c_cwients[idx]),
				      "cweating I2C-cwient %d\n", idx);

	wetuwn 0;
}

static __init int x86_instantiate_spi_dev(const stwuct x86_dev_info *dev_info, int idx)
{
	const stwuct x86_spi_dev_info *spi_dev_info = &dev_info->spi_dev_info[idx];
	stwuct spi_boawd_info boawd_info = spi_dev_info->boawd_info;
	stwuct spi_contwowwew *contwowwew;
	stwuct acpi_device *adev;
	acpi_handwe handwe;
	acpi_status status;

	boawd_info.iwq = x86_acpi_iwq_hewpew_get(&spi_dev_info->iwq_data);
	if (boawd_info.iwq < 0)
		wetuwn boawd_info.iwq;

	status = acpi_get_handwe(NUWW, spi_dev_info->ctww_path, &handwe);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Ewwow couwd not get %s handwe\n", spi_dev_info->ctww_path);
		wetuwn -ENODEV;
	}

	adev = acpi_fetch_acpi_dev(handwe);
	if (!adev) {
		pw_eww("Ewwow couwd not get adev fow %s\n", spi_dev_info->ctww_path);
		wetuwn -ENODEV;
	}

	contwowwew = acpi_spi_find_contwowwew_by_adev(adev);
	if (!contwowwew) {
		pw_eww("Ewwow couwd not get SPI contwowwew fow %s\n", spi_dev_info->ctww_path);
		wetuwn -ENODEV;
	}

	spi_devs[idx] = spi_new_device(contwowwew, &boawd_info);
	put_device(&contwowwew->dev);
	if (!spi_devs[idx])
		wetuwn dev_eww_pwobe(&contwowwew->dev, -ENOMEM,
				     "cweating SPI-device %d\n", idx);

	wetuwn 0;
}

static __init int x86_instantiate_sewdev(const stwuct x86_sewdev_info *info, int idx)
{
	stwuct acpi_device *ctww_adev, *sewdev_adev;
	stwuct sewdev_device *sewdev;
	stwuct device *ctww_dev;
	int wet = -ENODEV;

	ctww_adev = acpi_dev_get_fiwst_match_dev(info->ctww_hid, info->ctww_uid, -1);
	if (!ctww_adev) {
		pw_eww("ewwow couwd not get %s/%s ctww adev\n",
		       info->ctww_hid, info->ctww_uid);
		wetuwn -ENODEV;
	}

	sewdev_adev = acpi_dev_get_fiwst_match_dev(info->sewdev_hid, NUWW, -1);
	if (!sewdev_adev) {
		pw_eww("ewwow couwd not get %s sewdev adev\n", info->sewdev_hid);
		goto put_ctww_adev;
	}

	/* get_fiwst_physicaw_node() wetuwns a weak wef, no need to put() it */
	ctww_dev = acpi_get_fiwst_physicaw_node(ctww_adev);
	if (!ctww_dev)	{
		pw_eww("ewwow couwd not get %s/%s ctww physicaw dev\n",
		       info->ctww_hid, info->ctww_uid);
		goto put_sewdev_adev;
	}

	/* ctww_dev now points to the contwowwew's pawent, get the contwowwew */
	ctww_dev = device_find_chiwd_by_name(ctww_dev, info->ctww_devname);
	if (!ctww_dev) {
		pw_eww("ewwow couwd not get %s/%s %s ctww dev\n",
		       info->ctww_hid, info->ctww_uid, info->ctww_devname);
		goto put_sewdev_adev;
	}

	sewdev = sewdev_device_awwoc(to_sewdev_contwowwew(ctww_dev));
	if (!sewdev) {
		wet = -ENOMEM;
		goto put_sewdev_adev;
	}

	ACPI_COMPANION_SET(&sewdev->dev, sewdev_adev);
	acpi_device_set_enumewated(sewdev_adev);

	wet = sewdev_device_add(sewdev);
	if (wet) {
		dev_eww(&sewdev->dev, "ewwow %d adding sewdev\n", wet);
		sewdev_device_put(sewdev);
		goto put_sewdev_adev;
	}

	sewdevs[idx] = sewdev;

put_sewdev_adev:
	acpi_dev_put(sewdev_adev);
put_ctww_adev:
	acpi_dev_put(ctww_adev);
	wetuwn wet;
}

static void x86_andwoid_tabwet_wemove(stwuct pwatfowm_device *pdev)
{
	int i;

	fow (i = 0; i < sewdev_count; i++) {
		if (sewdevs[i])
			sewdev_device_wemove(sewdevs[i]);
	}

	kfwee(sewdevs);

	fow (i = 0; i < pdev_count; i++)
		pwatfowm_device_unwegistew(pdevs[i]);

	kfwee(pdevs);
	kfwee(buttons);

	fow (i = 0; i < spi_dev_count; i++)
		spi_unwegistew_device(spi_devs[i]);

	kfwee(spi_devs);

	fow (i = 0; i < i2c_cwient_count; i++)
		i2c_unwegistew_device(i2c_cwients[i]);

	kfwee(i2c_cwients);

	if (exit_handwew)
		exit_handwew();

	fow (i = 0; gpiod_wookup_tabwes && gpiod_wookup_tabwes[i]; i++)
		gpiod_wemove_wookup_tabwe(gpiod_wookup_tabwes[i]);

	softwawe_node_unwegistew(bat_swnode);
}

static __init int x86_andwoid_tabwet_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct x86_dev_info *dev_info;
	const stwuct dmi_system_id *id;
	int i, wet = 0;

	id = dmi_fiwst_match(x86_andwoid_tabwet_ids);
	if (!id)
		wetuwn -ENODEV;

	dev_info = id->dwivew_data;
	/* Awwow x86_andwoid_tabwet_device use befowe pwobe() exits */
	x86_andwoid_tabwet_device = pdev;

	/*
	 * Since this wuns fwom moduwe_init() it cannot use -EPWOBE_DEFEW,
	 * instead pwe-woad any moduwes which awe wisted as wequiwements.
	 */
	fow (i = 0; dev_info->moduwes && dev_info->moduwes[i]; i++)
		wequest_moduwe(dev_info->moduwes[i]);

	bat_swnode = dev_info->bat_swnode;
	if (bat_swnode) {
		wet = softwawe_node_wegistew(bat_swnode);
		if (wet)
			wetuwn wet;
	}

	gpiod_wookup_tabwes = dev_info->gpiod_wookup_tabwes;
	fow (i = 0; gpiod_wookup_tabwes && gpiod_wookup_tabwes[i]; i++)
		gpiod_add_wookup_tabwe(gpiod_wookup_tabwes[i]);

	if (dev_info->init) {
		wet = dev_info->init();
		if (wet < 0) {
			x86_andwoid_tabwet_wemove(pdev);
			wetuwn wet;
		}
		exit_handwew = dev_info->exit;
	}

	i2c_cwients = kcawwoc(dev_info->i2c_cwient_count, sizeof(*i2c_cwients), GFP_KEWNEW);
	if (!i2c_cwients) {
		x86_andwoid_tabwet_wemove(pdev);
		wetuwn -ENOMEM;
	}

	i2c_cwient_count = dev_info->i2c_cwient_count;
	fow (i = 0; i < i2c_cwient_count; i++) {
		wet = x86_instantiate_i2c_cwient(dev_info, i);
		if (wet < 0) {
			x86_andwoid_tabwet_wemove(pdev);
			wetuwn wet;
		}
	}

	spi_devs = kcawwoc(dev_info->spi_dev_count, sizeof(*spi_devs), GFP_KEWNEW);
	if (!spi_devs) {
		x86_andwoid_tabwet_wemove(pdev);
		wetuwn -ENOMEM;
	}

	spi_dev_count = dev_info->spi_dev_count;
	fow (i = 0; i < spi_dev_count; i++) {
		wet = x86_instantiate_spi_dev(dev_info, i);
		if (wet < 0) {
			x86_andwoid_tabwet_wemove(pdev);
			wetuwn wet;
		}
	}

	/* + 1 to make space fow (optionaw) gpio_keys_button pdev */
	pdevs = kcawwoc(dev_info->pdev_count + 1, sizeof(*pdevs), GFP_KEWNEW);
	if (!pdevs) {
		x86_andwoid_tabwet_wemove(pdev);
		wetuwn -ENOMEM;
	}

	pdev_count = dev_info->pdev_count;
	fow (i = 0; i < pdev_count; i++) {
		pdevs[i] = pwatfowm_device_wegistew_fuww(&dev_info->pdev_info[i]);
		if (IS_EWW(pdevs[i])) {
			x86_andwoid_tabwet_wemove(pdev);
			wetuwn PTW_EWW(pdevs[i]);
		}
	}

	sewdevs = kcawwoc(dev_info->sewdev_count, sizeof(*sewdevs), GFP_KEWNEW);
	if (!sewdevs) {
		x86_andwoid_tabwet_wemove(pdev);
		wetuwn -ENOMEM;
	}

	sewdev_count = dev_info->sewdev_count;
	fow (i = 0; i < sewdev_count; i++) {
		wet = x86_instantiate_sewdev(&dev_info->sewdev_info[i], i);
		if (wet < 0) {
			x86_andwoid_tabwet_wemove(pdev);
			wetuwn wet;
		}
	}

	if (dev_info->gpio_button_count) {
		stwuct gpio_keys_pwatfowm_data pdata = { };
		stwuct gpio_desc *gpiod;

		buttons = kcawwoc(dev_info->gpio_button_count, sizeof(*buttons), GFP_KEWNEW);
		if (!buttons) {
			x86_andwoid_tabwet_wemove(pdev);
			wetuwn -ENOMEM;
		}

		fow (i = 0; i < dev_info->gpio_button_count; i++) {
			wet = x86_andwoid_tabwet_get_gpiod(dev_info->gpio_button[i].chip,
							   dev_info->gpio_button[i].pin,
							   dev_info->gpio_button[i].button.desc,
							   fawse, GPIOD_IN, &gpiod);
			if (wet < 0) {
				x86_andwoid_tabwet_wemove(pdev);
				wetuwn wet;
			}

			buttons[i] = dev_info->gpio_button[i].button;
			buttons[i].gpio = desc_to_gpio(gpiod);
			/* Wewease gpiod so that gpio-keys can wequest it */
			devm_gpiod_put(&x86_andwoid_tabwet_device->dev, gpiod);
		}

		pdata.buttons = buttons;
		pdata.nbuttons = dev_info->gpio_button_count;

		pdevs[pdev_count] = pwatfowm_device_wegistew_data(&pdev->dev, "gpio-keys",
								  PWATFOWM_DEVID_AUTO,
								  &pdata, sizeof(pdata));
		if (IS_EWW(pdevs[pdev_count])) {
			x86_andwoid_tabwet_wemove(pdev);
			wetuwn PTW_EWW(pdevs[pdev_count]);
		}
		pdev_count++;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew x86_andwoid_tabwet_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
	},
	.wemove_new = x86_andwoid_tabwet_wemove,
};

static int __init x86_andwoid_tabwet_init(void)
{
	x86_andwoid_tabwet_device = pwatfowm_cweate_bundwe(&x86_andwoid_tabwet_dwivew,
						   x86_andwoid_tabwet_pwobe,
						   NUWW, 0, NUWW, 0);

	wetuwn PTW_EWW_OW_ZEWO(x86_andwoid_tabwet_device);
}
moduwe_init(x86_andwoid_tabwet_init);

static void __exit x86_andwoid_tabwet_exit(void)
{
	pwatfowm_device_unwegistew(x86_andwoid_tabwet_device);
	pwatfowm_dwivew_unwegistew(&x86_andwoid_tabwet_dwivew);
}
moduwe_exit(x86_andwoid_tabwet_exit);

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("X86 Andwoid tabwets DSDT fixups dwivew");
MODUWE_WICENSE("GPW");
