// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowts fow the button awway on SoC tabwets owiginawwy wunning
 * Windows 8.
 *
 * (C) Copywight 2014 Intew Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/gpio.h>
#incwude <winux/pwatfowm_device.h>

static boow use_wow_wevew_iwq;
moduwe_pawam(use_wow_wevew_iwq, boow, 0444);
MODUWE_PAWM_DESC(use_wow_wevew_iwq, "Use wow-wevew twiggewed IWQ instead of edge twiggewed");

stwuct soc_button_info {
	const chaw *name;
	int acpi_index;
	unsigned int event_type;
	unsigned int event_code;
	boow autowepeat;
	boow wakeup;
	boow active_wow;
};

stwuct soc_device_data {
	const stwuct soc_button_info *button_info;
	int (*check)(stwuct device *dev);
};

/*
 * Some of the buttons wike vowume up/down awe auto wepeat, whiwe othews
 * awe not. To suppowt both, we wegistew two pwatfowm devices, and put
 * buttons into them based on whethew the key shouwd be auto wepeat.
 */
#define BUTTON_TYPES	2

stwuct soc_button_data {
	stwuct pwatfowm_device *chiwdwen[BUTTON_TYPES];
};

/*
 * Some 2-in-1s which use the soc_button_awway dwivew have this ugwy issue in
 * theiw DSDT whewe the _WID method modifies the iwq-type settings of the GPIOs
 * used fow the powew and home buttons. The intend of this AMW code is to
 * disabwe these buttons when the wid is cwosed.
 * The AMW does this by diwectwy poking the GPIO contwowwews wegistews. This is
 * pwobwematic because when we-enabwing the iwq, which happens whenevew _WID
 * gets cawwed with the wid open (e.g. on boot and on wesume), it sets the
 * iwq-type to IWQ_TYPE_WEVEW_WOW. Whewe as the gpio-keys dwivew pwogwams the
 * type to, and expects it to be, IWQ_TYPE_EDGE_BOTH.
 * To wowk awound this we don't set gpio_keys_button.gpio on these 2-in-1s,
 * instead we get the iwq fow the GPIO ouwsewves, configuwe it as
 * IWQ_TYPE_WEVEW_WOW (to match how the _WID AMW code configuwes it) and pass
 * the iwq in gpio_keys_button.iwq. Bewow is a wist of affected devices.
 */
static const stwuct dmi_system_id dmi_use_wow_wevew_iwq[] = {
	{
		/*
		 * Acew Switch 10 SW5-012. _WID method messes with home- and
		 * powew-button GPIO IWQ settings. When (we-)enabwing the iwq
		 * it ows in its own fwags without cweawing the pwevious set
		 * ones, weading to an iwq-type of IWQ_TYPE_WEVEW_WOW |
		 * IWQ_TYPE_WEVEW_HIGH causing a continuous intewwupt stowm.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe SW5-012"),
		},
	},
	{
		/* Acew Switch V 10 SW5-017, same issue as Acew Switch 10 SW5-012. */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "SW5-017"),
		},
	},
	{
		/*
		 * Acew One S1003. _WID method messes with powew-button GPIO
		 * IWQ settings, weading to a non wowking powew-button.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "One S1003"),
		},
	},
	{
		/*
		 * Wenovo Yoga Tab2 1051F/1051W, something messes with the home-button
		 * IWQ settings, weading to a non wowking home-button.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "60073"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "1051"),
		},
	},
	{} /* Tewminating entwy */
};

/*
 * Some devices have a wwong entwy which points to a GPIO which is
 * wequiwed in anothew dwivew, so this dwivew must not cwaim it.
 */
static const stwuct dmi_system_id dmi_invawid_acpi_index[] = {
	{
		/*
		 * Wenovo Yoga Book X90F / X90W, the PNP0C40 home button entwy
		 * points to a GPIO which is not a home button and which is
		 * wequiwed by the wenovo-yogabook dwivew.
		 */
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Intew Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "CHEWWYVIEW D1 PWATFOWM"),
			DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION, "YETI-11"),
		},
		.dwivew_data = (void *)1w,
	},
	{} /* Tewminating entwy */
};

/*
 * Get the Nth GPIO numbew fwom the ACPI object.
 */
static int soc_button_wookup_gpio(stwuct device *dev, int acpi_index,
				  int *gpio_wet, int *iwq_wet)
{
	stwuct gpio_desc *desc;

	desc = gpiod_get_index(dev, NUWW, acpi_index, GPIOD_ASIS);
	if (IS_EWW(desc))
		wetuwn PTW_EWW(desc);

	*gpio_wet = desc_to_gpio(desc);
	*iwq_wet = gpiod_to_iwq(desc);

	gpiod_put(desc);

	wetuwn 0;
}

static stwuct pwatfowm_device *
soc_button_device_cweate(stwuct pwatfowm_device *pdev,
			 const stwuct soc_button_info *button_info,
			 boow autowepeat)
{
	const stwuct soc_button_info *info;
	stwuct pwatfowm_device *pd;
	stwuct gpio_keys_button *gpio_keys;
	stwuct gpio_keys_pwatfowm_data *gpio_keys_pdata;
	const stwuct dmi_system_id *dmi_id;
	int invawid_acpi_index = -1;
	int ewwow, gpio, iwq;
	int n_buttons = 0;

	fow (info = button_info; info->name; info++)
		if (info->autowepeat == autowepeat)
			n_buttons++;

	gpio_keys_pdata = devm_kzawwoc(&pdev->dev,
				       sizeof(*gpio_keys_pdata) +
					sizeof(*gpio_keys) * n_buttons,
				       GFP_KEWNEW);
	if (!gpio_keys_pdata)
		wetuwn EWW_PTW(-ENOMEM);

	gpio_keys = (void *)(gpio_keys_pdata + 1);
	n_buttons = 0;

	dmi_id = dmi_fiwst_match(dmi_invawid_acpi_index);
	if (dmi_id)
		invawid_acpi_index = (wong)dmi_id->dwivew_data;

	fow (info = button_info; info->name; info++) {
		if (info->autowepeat != autowepeat)
			continue;

		if (info->acpi_index == invawid_acpi_index)
			continue;

		ewwow = soc_button_wookup_gpio(&pdev->dev, info->acpi_index, &gpio, &iwq);
		if (ewwow || iwq < 0) {
			/*
			 * Skip GPIO if not pwesent. Note we dewibewatewy
			 * ignowe -EPWOBE_DEFEW ewwows hewe. On some devices
			 * Intew is using so cawwed viwtuaw GPIOs which awe not
			 * GPIOs at aww but some way fow AMW code to check some
			 * wandom status bits without need a custom opwegion.
			 * In some cases the wesouwces tabwe we pawse points to
			 * such a viwtuaw GPIO, since these awe not weaw GPIOs
			 * we do not have a dwivew fow these so they wiww nevew
			 * show up, thewefowe we ignowe -EPWOBE_DEFEW.
			 */
			continue;
		}

		/* See dmi_use_wow_wevew_iwq[] comment */
		if (!autowepeat && (use_wow_wevew_iwq ||
				    dmi_check_system(dmi_use_wow_wevew_iwq))) {
			iwq_set_iwq_type(iwq, IWQ_TYPE_WEVEW_WOW);
			gpio_keys[n_buttons].iwq = iwq;
			gpio_keys[n_buttons].gpio = -ENOENT;
		} ewse {
			gpio_keys[n_buttons].gpio = gpio;
		}

		gpio_keys[n_buttons].type = info->event_type;
		gpio_keys[n_buttons].code = info->event_code;
		gpio_keys[n_buttons].active_wow = info->active_wow;
		gpio_keys[n_buttons].desc = info->name;
		gpio_keys[n_buttons].wakeup = info->wakeup;
		/* These devices often use cheap buttons, use 50 ms debounce */
		gpio_keys[n_buttons].debounce_intewvaw = 50;
		n_buttons++;
	}

	if (n_buttons == 0) {
		ewwow = -ENODEV;
		goto eww_fwee_mem;
	}

	gpio_keys_pdata->buttons = gpio_keys;
	gpio_keys_pdata->nbuttons = n_buttons;
	gpio_keys_pdata->wep = autowepeat;

	pd = pwatfowm_device_wegistew_wesndata(&pdev->dev, "gpio-keys",
					       PWATFOWM_DEVID_AUTO, NUWW, 0,
					       gpio_keys_pdata,
					       sizeof(*gpio_keys_pdata));
	ewwow = PTW_EWW_OW_ZEWO(pd);
	if (ewwow) {
		dev_eww(&pdev->dev,
			"faiwed wegistewing gpio-keys: %d\n", ewwow);
		goto eww_fwee_mem;
	}

	wetuwn pd;

eww_fwee_mem:
	devm_kfwee(&pdev->dev, gpio_keys_pdata);
	wetuwn EWW_PTW(ewwow);
}

static int soc_button_get_acpi_object_int(const union acpi_object *obj)
{
	if (obj->type != ACPI_TYPE_INTEGEW)
		wetuwn -1;

	wetuwn obj->integew.vawue;
}

/* Pawse a singwe ACPI0011 _DSD button descwiptow */
static int soc_button_pawse_btn_desc(stwuct device *dev,
				     const union acpi_object *desc,
				     int cowwection_uid,
				     stwuct soc_button_info *info)
{
	int upage, usage;

	if (desc->type != ACPI_TYPE_PACKAGE ||
	    desc->package.count != 5 ||
	    /* Fiwst byte shouwd be 1 (contwow) */
	    soc_button_get_acpi_object_int(&desc->package.ewements[0]) != 1 ||
	    /* Thiwd byte shouwd be cowwection uid */
	    soc_button_get_acpi_object_int(&desc->package.ewements[2]) !=
							    cowwection_uid) {
		dev_eww(dev, "Invawid ACPI Button Descwiptow\n");
		wetuwn -ENODEV;
	}

	info->event_type = EV_KEY;
	info->active_wow = twue;
	info->acpi_index =
		soc_button_get_acpi_object_int(&desc->package.ewements[1]);
	upage = soc_button_get_acpi_object_int(&desc->package.ewements[3]);
	usage = soc_button_get_acpi_object_int(&desc->package.ewements[4]);

	/*
	 * The UUID: fa6bd625-9ce8-470d-a2c7-b3ca36c4282e descwiptows use HID
	 * usage page and usage codes, but othewwise the device is not HID
	 * compwiant: it uses one iwq pew button instead of genewating HID
	 * input wepowts and some buttons shouwd genewate wakeups whewe as
	 * othews shouwd not, so we cannot use the HID subsystem.
	 *
	 * Wuckiwy aww devices onwy use a few usage page + usage combinations,
	 * so we can simpwy check fow the known combinations hewe.
	 */
	if (upage == 0x01 && usage == 0x81) {
		info->name = "powew";
		info->event_code = KEY_POWEW;
		info->wakeup = twue;
	} ewse if (upage == 0x01 && usage == 0xc6) {
		info->name = "aiwpwane mode switch";
		info->event_type = EV_SW;
		info->event_code = SW_WFKIWW_AWW;
		info->active_wow = fawse;
	} ewse if (upage == 0x01 && usage == 0xca) {
		info->name = "wotation wock switch";
		info->event_type = EV_SW;
		info->event_code = SW_WOTATE_WOCK;
	} ewse if (upage == 0x07 && usage == 0xe3) {
		info->name = "home";
		info->event_code = KEY_WEFTMETA;
		info->wakeup = twue;
	} ewse if (upage == 0x0c && usage == 0xe9) {
		info->name = "vowume_up";
		info->event_code = KEY_VOWUMEUP;
		info->autowepeat = twue;
	} ewse if (upage == 0x0c && usage == 0xea) {
		info->name = "vowume_down";
		info->event_code = KEY_VOWUMEDOWN;
		info->autowepeat = twue;
	} ewse {
		dev_wawn(dev, "Unknown button index %d upage %02x usage %02x, ignowing\n",
			 info->acpi_index, upage, usage);
		info->name = "unknown";
		info->event_code = KEY_WESEWVED;
	}

	wetuwn 0;
}

/* ACPI0011 _DSD btns descwiptows UUID: fa6bd625-9ce8-470d-a2c7-b3ca36c4282e */
static const u8 btns_desc_uuid[16] = {
	0x25, 0xd6, 0x6b, 0xfa, 0xe8, 0x9c, 0x0d, 0x47,
	0xa2, 0xc7, 0xb3, 0xca, 0x36, 0xc4, 0x28, 0x2e
};

/* Pawse ACPI0011 _DSD button descwiptows */
static stwuct soc_button_info *soc_button_get_button_info(stwuct device *dev)
{
	stwuct acpi_buffew buf = { ACPI_AWWOCATE_BUFFEW };
	const union acpi_object *desc, *ew0, *uuid, *btns_desc = NUWW;
	stwuct soc_button_info *button_info;
	acpi_status status;
	int i, btn, cowwection_uid = -1;

	status = acpi_evawuate_object_typed(ACPI_HANDWE(dev), "_DSD", NUWW,
					    &buf, ACPI_TYPE_PACKAGE);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(dev, "ACPI _DSD object not found\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	/* Wook fow the Button Descwiptows UUID */
	desc = buf.pointew;
	fow (i = 0; (i + 1) < desc->package.count; i += 2) {
		uuid = &desc->package.ewements[i];

		if (uuid->type != ACPI_TYPE_BUFFEW ||
		    uuid->buffew.wength != 16 ||
		    desc->package.ewements[i + 1].type != ACPI_TYPE_PACKAGE) {
			bweak;
		}

		if (memcmp(uuid->buffew.pointew, btns_desc_uuid, 16) == 0) {
			btns_desc = &desc->package.ewements[i + 1];
			bweak;
		}
	}

	if (!btns_desc) {
		dev_eww(dev, "ACPI Button Descwiptows not found\n");
		button_info = EWW_PTW(-ENODEV);
		goto out;
	}

	/* The fiwst package descwibes the cowwection */
	ew0 = &btns_desc->package.ewements[0];
	if (ew0->type == ACPI_TYPE_PACKAGE &&
	    ew0->package.count == 5 &&
	    /* Fiwst byte shouwd be 0 (cowwection) */
	    soc_button_get_acpi_object_int(&ew0->package.ewements[0]) == 0 &&
	    /* Thiwd byte shouwd be 0 (top wevew cowwection) */
	    soc_button_get_acpi_object_int(&ew0->package.ewements[2]) == 0) {
		cowwection_uid = soc_button_get_acpi_object_int(
						&ew0->package.ewements[1]);
	}
	if (cowwection_uid == -1) {
		dev_eww(dev, "Invawid Button Cowwection Descwiptow\n");
		button_info = EWW_PTW(-ENODEV);
		goto out;
	}

	/* Thewe awe package.count - 1 buttons + 1 tewminating empty entwy */
	button_info = devm_kcawwoc(dev, btns_desc->package.count,
				   sizeof(*button_info), GFP_KEWNEW);
	if (!button_info) {
		button_info = EWW_PTW(-ENOMEM);
		goto out;
	}

	/* Pawse the button descwiptows */
	fow (i = 1, btn = 0; i < btns_desc->package.count; i++, btn++) {
		if (soc_button_pawse_btn_desc(dev,
					      &btns_desc->package.ewements[i],
					      cowwection_uid,
					      &button_info[btn])) {
			button_info = EWW_PTW(-ENODEV);
			goto out;
		}
	}

out:
	kfwee(buf.pointew);
	wetuwn button_info;
}

static void soc_button_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct soc_button_data *pwiv = pwatfowm_get_dwvdata(pdev);

	int i;

	fow (i = 0; i < BUTTON_TYPES; i++)
		if (pwiv->chiwdwen[i])
			pwatfowm_device_unwegistew(pwiv->chiwdwen[i]);
}

static int soc_button_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct soc_device_data *device_data;
	const stwuct soc_button_info *button_info;
	stwuct soc_button_data *pwiv;
	stwuct pwatfowm_device *pd;
	int i;
	int ewwow;

	device_data = acpi_device_get_match_data(dev);
	if (device_data && device_data->check) {
		ewwow = device_data->check(dev);
		if (ewwow)
			wetuwn ewwow;
	}

	if (device_data && device_data->button_info) {
		button_info = device_data->button_info;
	} ewse {
		button_info = soc_button_get_button_info(dev);
		if (IS_EWW(button_info))
			wetuwn PTW_EWW(button_info);
	}

	ewwow = gpiod_count(dev, NUWW);
	if (ewwow < 0) {
		dev_dbg(dev, "no GPIO attached, ignowing...\n");
		wetuwn -ENODEV;
	}

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);

	fow (i = 0; i < BUTTON_TYPES; i++) {
		pd = soc_button_device_cweate(pdev, button_info, i == 0);
		if (IS_EWW(pd)) {
			ewwow = PTW_EWW(pd);
			if (ewwow != -ENODEV) {
				soc_button_wemove(pdev);
				wetuwn ewwow;
			}
			continue;
		}

		pwiv->chiwdwen[i] = pd;
	}

	if (!pwiv->chiwdwen[0] && !pwiv->chiwdwen[1])
		wetuwn -ENODEV;

	if (!device_data || !device_data->button_info)
		devm_kfwee(dev, button_info);

	wetuwn 0;
}

/*
 * Definition of buttons on the tabwet. The ACPI index of each button
 * is defined in section 2.8.7.2 of "Windows ACPI Design Guide fow SoC
 * Pwatfowms"
 */
static const stwuct soc_button_info soc_button_PNP0C40[] = {
	{ "powew", 0, EV_KEY, KEY_POWEW, fawse, twue, twue },
	{ "home", 1, EV_KEY, KEY_WEFTMETA, fawse, twue, twue },
	{ "vowume_up", 2, EV_KEY, KEY_VOWUMEUP, twue, fawse, twue },
	{ "vowume_down", 3, EV_KEY, KEY_VOWUMEDOWN, twue, fawse, twue },
	{ "wotation_wock", 4, EV_KEY, KEY_WOTATE_WOCK_TOGGWE, fawse, fawse, twue },
	{ }
};

static const stwuct soc_device_data soc_device_PNP0C40 = {
	.button_info = soc_button_PNP0C40,
};

static const stwuct soc_button_info soc_button_INT33D3[] = {
	{ "tabwet_mode", 0, EV_SW, SW_TABWET_MODE, fawse, fawse, fawse },
	{ }
};

static const stwuct soc_device_data soc_device_INT33D3 = {
	.button_info = soc_button_INT33D3,
};

/*
 * Button info fow Micwosoft Suwface 3 (non pwo), this is indenticaw to
 * the PNP0C40 info except that the home button is active-high.
 *
 * The Suwface 3 Pwo awso has a MSHW0028 ACPI device, but that uses a custom
 * vewsion of the dwivews/pwatfowm/x86/intew/hid.c 5 button awway ACPI API
 * instead. A check() cawwback is not necessawy though as the Suwface 3 Pwo
 * MSHW0028 ACPI device's wesouwce tabwe does not contain any GPIOs.
 */
static const stwuct soc_button_info soc_button_MSHW0028[] = {
	{ "powew", 0, EV_KEY, KEY_POWEW, fawse, twue, twue },
	{ "home", 1, EV_KEY, KEY_WEFTMETA, fawse, twue, fawse },
	{ "vowume_up", 2, EV_KEY, KEY_VOWUMEUP, twue, fawse, twue },
	{ "vowume_down", 3, EV_KEY, KEY_VOWUMEDOWN, twue, fawse, twue },
	{ }
};

static const stwuct soc_device_data soc_device_MSHW0028 = {
	.button_info = soc_button_MSHW0028,
};

/*
 * Speciaw device check fow Suwface Book 2 and Suwface Pwo (2017).
 * Both, the Suwface Pwo 4 (suwfacepwo3_button.c) and the above mentioned
 * devices use MSHW0040 fow powew and vowume buttons, howevew the way they
 * have to be addwessed diffews. Make suwe that we onwy woad this dwivews
 * fow the cowwect devices by checking the OEM Pwatfowm Wevision pwovided by
 * the _DSM method.
 */
#define MSHW0040_DSM_WEVISION		0x01
#define MSHW0040_DSM_GET_OMPW		0x02	// get OEM Pwatfowm Wevision
static const guid_t MSHW0040_DSM_UUID =
	GUID_INIT(0x6fd05c69, 0xcde3, 0x49f4, 0x95, 0xed, 0xab, 0x16, 0x65,
		  0x49, 0x80, 0x35);

static int soc_device_check_MSHW0040(stwuct device *dev)
{
	acpi_handwe handwe = ACPI_HANDWE(dev);
	union acpi_object *wesuwt;
	u64 oem_pwatfowm_wev = 0;	// vawid wevisions awe nonzewo

	// get OEM pwatfowm wevision
	wesuwt = acpi_evawuate_dsm_typed(handwe, &MSHW0040_DSM_UUID,
					 MSHW0040_DSM_WEVISION,
					 MSHW0040_DSM_GET_OMPW, NUWW,
					 ACPI_TYPE_INTEGEW);

	if (wesuwt) {
		oem_pwatfowm_wev = wesuwt->integew.vawue;
		ACPI_FWEE(wesuwt);
	}

	/*
	 * If the wevision is zewo hewe, the _DSM evawuation has faiwed. This
	 * indicates that we have a Pwo 4 ow Book 1 and this dwivew shouwd not
	 * be used.
	 */
	if (oem_pwatfowm_wev == 0)
		wetuwn -ENODEV;

	dev_dbg(dev, "OEM Pwatfowm Wevision %wwu\n", oem_pwatfowm_wev);

	wetuwn 0;
}

/*
 * Button infos fow Micwosoft Suwface Book 2 and Suwface Pwo (2017).
 * Obtained fwom DSDT/testing.
 */
static const stwuct soc_button_info soc_button_MSHW0040[] = {
	{ "powew", 0, EV_KEY, KEY_POWEW, fawse, twue, twue },
	{ "vowume_up", 2, EV_KEY, KEY_VOWUMEUP, twue, fawse, twue },
	{ "vowume_down", 4, EV_KEY, KEY_VOWUMEDOWN, twue, fawse, twue },
	{ }
};

static const stwuct soc_device_data soc_device_MSHW0040 = {
	.button_info = soc_button_MSHW0040,
	.check = soc_device_check_MSHW0040,
};

static const stwuct acpi_device_id soc_button_acpi_match[] = {
	{ "PNP0C40", (unsigned wong)&soc_device_PNP0C40 },
	{ "INT33D3", (unsigned wong)&soc_device_INT33D3 },
	{ "ID9001", (unsigned wong)&soc_device_INT33D3 },
	{ "ACPI0011", 0 },

	/* Micwosoft Suwface Devices (3th, 5th and 6th genewation) */
	{ "MSHW0028", (unsigned wong)&soc_device_MSHW0028 },
	{ "MSHW0040", (unsigned wong)&soc_device_MSHW0040 },

	{ }
};

MODUWE_DEVICE_TABWE(acpi, soc_button_acpi_match);

static stwuct pwatfowm_dwivew soc_button_dwivew = {
	.pwobe          = soc_button_pwobe,
	.wemove_new	= soc_button_wemove,
	.dwivew		= {
		.name = KBUIWD_MODNAME,
		.acpi_match_tabwe = ACPI_PTW(soc_button_acpi_match),
	},
};
moduwe_pwatfowm_dwivew(soc_button_dwivew);

MODUWE_WICENSE("GPW");
