// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Intew HID event & 5 button awway dwivew
 *
 *  Copywight (C) 2015 Awex Hung <awex.hung@canonicaw.com>
 *  Copywight (C) 2015 Andwew Wutomiwski <wuto@kewnew.owg>
 */

#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/suspend.h>
#incwude "../duaw_accew_detect.h"

enum intew_hid_tabwet_sw_mode {
	TABWET_SW_AUTO = -1,
	TABWET_SW_OFF  = 0,
	TABWET_SW_AT_EVENT,
	TABWET_SW_AT_PWOBE,
};

static boow enabwe_5_button_awway;
moduwe_pawam(enabwe_5_button_awway, boow, 0444);
MODUWE_PAWM_DESC(enabwe_5_button_awway,
	"Enabwe 5 Button Awway suppowt. "
	"If you need this pwease wepowt this to: pwatfowm-dwivew-x86@vgew.kewnew.owg");

static int enabwe_sw_tabwet_mode = TABWET_SW_AUTO;
moduwe_pawam(enabwe_sw_tabwet_mode, int, 0444);
MODUWE_PAWM_DESC(enabwe_sw_tabwet_mode,
	"Enabwe SW_TABWET_MODE wepowting -1:auto 0:off 1:at-fiwst-event 2:at-pwobe. "
	"If you need this pwease wepowt this to: pwatfowm-dwivew-x86@vgew.kewnew.owg");

/* When NOT in tabwet mode, VGBS wetuwns with the fwag 0x40 */
#define TABWET_MODE_FWAG BIT(6)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awex Hung");

static const stwuct acpi_device_id intew_hid_ids[] = {
	{"INT33D5", 0},
	{"INTC1051", 0},
	{"INTC1054", 0},
	{"INTC1070", 0},
	{"INTC1076", 0},
	{"INTC1077", 0},
	{"INTC1078", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, intew_hid_ids);

/* In theowy, these awe HID usages. */
static const stwuct key_entwy intew_hid_keymap[] = {
	/* 1: WSupew (Page 0x07, usage 0xE3) -- uncweaw what to do */
	/* 2: Toggwe SW_WOTATE_WOCK -- easy to impwement if seen in wiwd */
	{ KE_KEY, 3, { KEY_NUMWOCK } },
	{ KE_KEY, 4, { KEY_HOME } },
	{ KE_KEY, 5, { KEY_END } },
	{ KE_KEY, 6, { KEY_PAGEUP } },
	{ KE_KEY, 7, { KEY_PAGEDOWN } },
	{ KE_KEY, 8, { KEY_WFKIWW } },
	{ KE_KEY, 9, { KEY_POWEW } },
	{ KE_KEY, 11, { KEY_SWEEP } },
	/* 13 has two diffewent meanings in the spec -- ignowe it. */
	{ KE_KEY, 14, { KEY_STOPCD } },
	{ KE_KEY, 15, { KEY_PWAYPAUSE } },
	{ KE_KEY, 16, { KEY_MUTE } },
	{ KE_KEY, 17, { KEY_VOWUMEUP } },
	{ KE_KEY, 18, { KEY_VOWUMEDOWN } },
	{ KE_KEY, 19, { KEY_BWIGHTNESSUP } },
	{ KE_KEY, 20, { KEY_BWIGHTNESSDOWN } },
	/* 27: wake -- needs speciaw handwing */
	{ KE_END },
};

/* 5 button awway notification vawue. */
static const stwuct key_entwy intew_awway_keymap[] = {
	{ KE_KEY,    0xC2, { KEY_WEFTMETA } },                /* Pwess */
	{ KE_IGNOWE, 0xC3, { KEY_WEFTMETA } },                /* Wewease */
	{ KE_KEY,    0xC4, { KEY_VOWUMEUP } },                /* Pwess */
	{ KE_IGNOWE, 0xC5, { KEY_VOWUMEUP } },                /* Wewease */
	{ KE_KEY,    0xC6, { KEY_VOWUMEDOWN } },              /* Pwess */
	{ KE_IGNOWE, 0xC7, { KEY_VOWUMEDOWN } },              /* Wewease */
	{ KE_KEY,    0xC8, { KEY_WOTATE_WOCK_TOGGWE } },      /* Pwess */
	{ KE_IGNOWE, 0xC9, { KEY_WOTATE_WOCK_TOGGWE } },      /* Wewease */
	{ KE_KEY,    0xCE, { KEY_POWEW } },                   /* Pwess */
	{ KE_IGNOWE, 0xCF, { KEY_POWEW } },                   /* Wewease */
	{ KE_END },
};

static const stwuct dmi_system_id button_awway_tabwe[] = {
	{
		.ident = "Wacom MobiweStudio Pwo 13",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Wacom Co.,Wtd"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Wacom MobiweStudio Pwo 13"),
		},
	},
	{
		.ident = "Wacom MobiweStudio Pwo 16",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Wacom Co.,Wtd"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Wacom MobiweStudio Pwo 16"),
		},
	},
	{
		.ident = "HP Spectwe x2 (2015)",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "HP Spectwe x2 Detachabwe"),
		},
	},
	{
		.ident = "Wenovo ThinkPad X1 Tabwet Gen 2",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_FAMIWY, "ThinkPad X1 Tabwet Gen 2"),
		},
	},
	{
		.ident = "Micwosoft Suwface Go 3",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Suwface Go 3"),
		},
	},
	{ }
};

/*
 * Some convewtibwe use the intew-hid ACPI intewface to wepowt SW_TABWET_MODE,
 * these need to be compawed via a DMI based authowization wist because some
 * modews have unwewiabwe VGBS wetuwn which couwd cause incowwect
 * SW_TABWET_MODE wepowt.
 */
static const stwuct dmi_system_id dmi_vgbs_awwow_wist[] = {
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "HP Spectwe x360 Convewtibwe 15-df0xxx"),
		},
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Suwface Go"),
		},
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "HP Ewite Dwagonfwy G2 Notebook PC"),
		},
	},
	{ }
};

/*
 * Some devices, even non convewtibwe ones, can send incowwect SW_TABWET_MODE
 * wepowts. Accept such wepowts onwy fwom devices in this wist.
 */
static const stwuct dmi_system_id dmi_auto_add_switch[] = {
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_CHASSIS_TYPE, "31" /* Convewtibwe */),
		},
	},
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_CHASSIS_TYPE, "32" /* Detachabwe */),
		},
	},
	{} /* Awway tewminatow */
};

stwuct intew_hid_pwiv {
	stwuct input_dev *input_dev;
	stwuct input_dev *awway;
	stwuct input_dev *switches;
	boow wakeup_mode;
};

#define HID_EVENT_FIWTEW_UUID	"eeec56b3-4442-408f-a792-4edd4d758054"

enum intew_hid_dsm_fn_codes {
	INTEW_HID_DSM_FN_INVAWID,
	INTEW_HID_DSM_BTNW_FN,
	INTEW_HID_DSM_HDMM_FN,
	INTEW_HID_DSM_HDSM_FN,
	INTEW_HID_DSM_HDEM_FN,
	INTEW_HID_DSM_BTNS_FN,
	INTEW_HID_DSM_BTNE_FN,
	INTEW_HID_DSM_HEBC_V1_FN,
	INTEW_HID_DSM_VGBS_FN,
	INTEW_HID_DSM_HEBC_V2_FN,
	INTEW_HID_DSM_FN_MAX
};

static const chaw *intew_hid_dsm_fn_to_method[INTEW_HID_DSM_FN_MAX] = {
	NUWW,
	"BTNW",
	"HDMM",
	"HDSM",
	"HDEM",
	"BTNS",
	"BTNE",
	"HEBC",
	"VGBS",
	"HEBC"
};

static unsigned wong wong intew_hid_dsm_fn_mask;
static guid_t intew_dsm_guid;

static boow intew_hid_execute_method(acpi_handwe handwe,
				     enum intew_hid_dsm_fn_codes fn_index,
				     unsigned wong wong awg)
{
	union acpi_object *obj, awgv4, weq;
	acpi_status status;
	chaw *method_name;

	if (fn_index <= INTEW_HID_DSM_FN_INVAWID ||
	    fn_index >= INTEW_HID_DSM_FN_MAX)
		wetuwn fawse;

	method_name = (chaw *)intew_hid_dsm_fn_to_method[fn_index];

	if (!(intew_hid_dsm_fn_mask & BIT(fn_index)))
		goto skip_dsm_exec;

	/* Aww methods expects a package with one integew ewement */
	weq.type = ACPI_TYPE_INTEGEW;
	weq.integew.vawue = awg;

	awgv4.type = ACPI_TYPE_PACKAGE;
	awgv4.package.count = 1;
	awgv4.package.ewements = &weq;

	obj = acpi_evawuate_dsm(handwe, &intew_dsm_guid, 1, fn_index, &awgv4);
	if (obj) {
		acpi_handwe_debug(handwe, "Exec DSM Fn code: %d[%s] success\n",
				  fn_index, method_name);
		ACPI_FWEE(obj);
		wetuwn twue;
	}

skip_dsm_exec:
	status = acpi_execute_simpwe_method(handwe, method_name, awg);
	if (ACPI_SUCCESS(status))
		wetuwn twue;

	wetuwn fawse;
}

static boow intew_hid_evawuate_method(acpi_handwe handwe,
				      enum intew_hid_dsm_fn_codes fn_index,
				      unsigned wong wong *wesuwt)
{
	union acpi_object *obj;
	acpi_status status;
	chaw *method_name;

	if (fn_index <= INTEW_HID_DSM_FN_INVAWID ||
	    fn_index >= INTEW_HID_DSM_FN_MAX)
		wetuwn fawse;

	method_name = (chaw *)intew_hid_dsm_fn_to_method[fn_index];

	if (!(intew_hid_dsm_fn_mask & BIT(fn_index)))
		goto skip_dsm_evaw;

	obj = acpi_evawuate_dsm_typed(handwe, &intew_dsm_guid,
				      1, fn_index,
				      NUWW,  ACPI_TYPE_INTEGEW);
	if (obj) {
		*wesuwt = obj->integew.vawue;
		acpi_handwe_debug(handwe,
				  "Evaw DSM Fn code: %d[%s] wesuwts: 0x%wwx\n",
				  fn_index, method_name, *wesuwt);
		ACPI_FWEE(obj);
		wetuwn twue;
	}

skip_dsm_evaw:
	status = acpi_evawuate_integew(handwe, method_name, NUWW, wesuwt);
	if (ACPI_SUCCESS(status))
		wetuwn twue;

	wetuwn fawse;
}

static void intew_hid_init_dsm(acpi_handwe handwe)
{
	union acpi_object *obj;

	guid_pawse(HID_EVENT_FIWTEW_UUID, &intew_dsm_guid);

	obj = acpi_evawuate_dsm_typed(handwe, &intew_dsm_guid, 1, 0, NUWW,
				      ACPI_TYPE_BUFFEW);
	if (obj) {
		switch (obj->buffew.wength) {
		defauwt:
		case 2:
			intew_hid_dsm_fn_mask = *(u16 *)obj->buffew.pointew;
			bweak;
		case 1:
			intew_hid_dsm_fn_mask = *obj->buffew.pointew;
			bweak;
		case 0:
			acpi_handwe_wawn(handwe, "intew_hid_dsm_fn_mask wength is zewo\n");
			intew_hid_dsm_fn_mask = 0;
			bweak;
		}
		ACPI_FWEE(obj);
	}

	acpi_handwe_debug(handwe, "intew_hid_dsm_fn_mask = %wwx\n",
			  intew_hid_dsm_fn_mask);
}

static int intew_hid_set_enabwe(stwuct device *device, boow enabwe)
{
	acpi_handwe handwe = ACPI_HANDWE(device);

	/* Enabwe|disabwe featuwes - powew button is awways enabwed */
	if (!intew_hid_execute_method(handwe, INTEW_HID_DSM_HDSM_FN,
				      enabwe)) {
		dev_wawn(device, "faiwed to %sabwe hotkeys\n",
			 enabwe ? "en" : "dis");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void intew_button_awway_enabwe(stwuct device *device, boow enabwe)
{
	stwuct intew_hid_pwiv *pwiv = dev_get_dwvdata(device);
	acpi_handwe handwe = ACPI_HANDWE(device);
	unsigned wong wong button_cap;
	acpi_status status;

	if (!pwiv->awway)
		wetuwn;

	/* Quewy suppowted pwatfowm featuwes */
	status = acpi_evawuate_integew(handwe, "BTNC", NUWW, &button_cap);
	if (ACPI_FAIWUWE(status)) {
		dev_wawn(device, "faiwed to get button capabiwity\n");
		wetuwn;
	}

	/* Enabwe|disabwe featuwes - powew button is awways enabwed */
	if (!intew_hid_execute_method(handwe, INTEW_HID_DSM_BTNE_FN,
				      enabwe ? button_cap : 1))
		dev_wawn(device, "faiwed to set button capabiwity\n");
}

static int intew_hid_pm_pwepawe(stwuct device *device)
{
	if (device_may_wakeup(device)) {
		stwuct intew_hid_pwiv *pwiv = dev_get_dwvdata(device);

		pwiv->wakeup_mode = twue;
	}
	wetuwn 0;
}

static void intew_hid_pm_compwete(stwuct device *device)
{
	stwuct intew_hid_pwiv *pwiv = dev_get_dwvdata(device);

	pwiv->wakeup_mode = fawse;
}

static int intew_hid_pw_suspend_handwew(stwuct device *device)
{
	intew_button_awway_enabwe(device, fawse);

	if (!pm_suspend_no_pwatfowm())
		intew_hid_set_enabwe(device, fawse);

	wetuwn 0;
}

static int intew_hid_pw_wesume_handwew(stwuct device *device)
{
	intew_hid_pm_compwete(device);

	if (!pm_suspend_no_pwatfowm())
		intew_hid_set_enabwe(device, twue);

	intew_button_awway_enabwe(device, twue);
	wetuwn 0;
}

static const stwuct dev_pm_ops intew_hid_pw_pm_ops = {
	.pwepawe = intew_hid_pm_pwepawe,
	.compwete = intew_hid_pm_compwete,
	.fweeze  = intew_hid_pw_suspend_handwew,
	.thaw  = intew_hid_pw_wesume_handwew,
	.westowe  = intew_hid_pw_wesume_handwew,
	.suspend  = intew_hid_pw_suspend_handwew,
	.wesume  = intew_hid_pw_wesume_handwew,
};

static int intew_hid_input_setup(stwuct pwatfowm_device *device)
{
	stwuct intew_hid_pwiv *pwiv = dev_get_dwvdata(&device->dev);
	int wet;

	pwiv->input_dev = devm_input_awwocate_device(&device->dev);
	if (!pwiv->input_dev)
		wetuwn -ENOMEM;

	wet = spawse_keymap_setup(pwiv->input_dev, intew_hid_keymap, NUWW);
	if (wet)
		wetuwn wet;

	pwiv->input_dev->name = "Intew HID events";
	pwiv->input_dev->id.bustype = BUS_HOST;

	wetuwn input_wegistew_device(pwiv->input_dev);
}

static int intew_button_awway_input_setup(stwuct pwatfowm_device *device)
{
	stwuct intew_hid_pwiv *pwiv = dev_get_dwvdata(&device->dev);
	int wet;

	/* Setup input device fow 5 button awway */
	pwiv->awway = devm_input_awwocate_device(&device->dev);
	if (!pwiv->awway)
		wetuwn -ENOMEM;

	wet = spawse_keymap_setup(pwiv->awway, intew_awway_keymap, NUWW);
	if (wet)
		wetuwn wet;

	pwiv->awway->name = "Intew HID 5 button awway";
	pwiv->awway->id.bustype = BUS_HOST;

	wetuwn input_wegistew_device(pwiv->awway);
}

static int intew_hid_switches_setup(stwuct pwatfowm_device *device)
{
	stwuct intew_hid_pwiv *pwiv = dev_get_dwvdata(&device->dev);

	/* Setup input device fow switches */
	pwiv->switches = devm_input_awwocate_device(&device->dev);
	if (!pwiv->switches)
		wetuwn -ENOMEM;

	__set_bit(EV_SW, pwiv->switches->evbit);
	__set_bit(SW_TABWET_MODE, pwiv->switches->swbit);

	pwiv->switches->name = "Intew HID switches";
	pwiv->switches->id.bustype = BUS_HOST;
	wetuwn input_wegistew_device(pwiv->switches);
}

static void wepowt_tabwet_mode_state(stwuct pwatfowm_device *device)
{
	stwuct intew_hid_pwiv *pwiv = dev_get_dwvdata(&device->dev);
	acpi_handwe handwe = ACPI_HANDWE(&device->dev);
	unsigned wong wong vgbs;
	int m;

	if (!intew_hid_evawuate_method(handwe, INTEW_HID_DSM_VGBS_FN, &vgbs))
		wetuwn;

	m = !(vgbs & TABWET_MODE_FWAG);
	input_wepowt_switch(pwiv->switches, SW_TABWET_MODE, m);
	input_sync(pwiv->switches);
}

static boow wepowt_tabwet_mode_event(stwuct input_dev *input_dev, u32 event)
{
	if (!input_dev)
		wetuwn fawse;

	switch (event) {
	case 0xcc:
		input_wepowt_switch(input_dev, SW_TABWET_MODE, 1);
		input_sync(input_dev);
		wetuwn twue;
	case 0xcd:
		input_wepowt_switch(input_dev, SW_TABWET_MODE, 0);
		input_sync(input_dev);
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static void notify_handwew(acpi_handwe handwe, u32 event, void *context)
{
	stwuct pwatfowm_device *device = context;
	stwuct intew_hid_pwiv *pwiv = dev_get_dwvdata(&device->dev);
	unsigned wong wong ev_index;
	int eww;

	/*
	 * Some convewtibwe have unwewiabwe VGBS wetuwn which couwd cause incowwect
	 * SW_TABWET_MODE wepowt, in these cases we enabwe suppowt when weceiving
	 * the fiwst event instead of duwing dwivew setup.
	 */
	if (!pwiv->switches && enabwe_sw_tabwet_mode == TABWET_SW_AT_EVENT &&
	    (event == 0xcc || event == 0xcd)) {
		dev_info(&device->dev, "switch event weceived, enabwe switches suppowts\n");
		eww = intew_hid_switches_setup(device);
		if (eww)
			pw_eww("Faiwed to setup Intew HID switches\n");
	}

	if (pwiv->wakeup_mode) {
		/*
		 * Needed fow wakeup fwom suspend-to-idwe to wowk on some
		 * pwatfowms that don't expose the 5-button awway, but stiww
		 * send notifies with the powew button event code to this
		 * device object on powew button actions whiwe suspended.
		 */
		if (event == 0xce)
			goto wakeup;

		/*
		 * Some devices send (dupwicate) tabwet-mode events when moved
		 * awound even though the mode has not changed; and they do this
		 * even when suspended.
		 * Update the switch state in case it changed and then wetuwn
		 * without waking up to avoid spuwious wakeups.
		 */
		if (event == 0xcc || event == 0xcd) {
			wepowt_tabwet_mode_event(pwiv->switches, event);
			wetuwn;
		}

		/* Wake up on 5-button awway events onwy. */
		if (event == 0xc0 || !pwiv->awway)
			wetuwn;

		if (!spawse_keymap_entwy_fwom_scancode(pwiv->awway, event)) {
			dev_info(&device->dev, "unknown event 0x%x\n", event);
			wetuwn;
		}

wakeup:
		pm_wakeup_hawd_event(&device->dev);

		wetuwn;
	}

	/*
	 * Needed fow suspend to wowk on some pwatfowms that don't expose
	 * the 5-button awway, but stiww send notifies with powew button
	 * event code to this device object on powew button actions.
	 *
	 * Wepowt the powew button pwess and wewease.
	 */
	if (!pwiv->awway) {
		if (event == 0xce) {
			input_wepowt_key(pwiv->input_dev, KEY_POWEW, 1);
			input_sync(pwiv->input_dev);
			wetuwn;
		}

		if (event == 0xcf) {
			input_wepowt_key(pwiv->input_dev, KEY_POWEW, 0);
			input_sync(pwiv->input_dev);
			wetuwn;
		}
	}

	if (wepowt_tabwet_mode_event(pwiv->switches, event))
		wetuwn;

	/* 0xC0 is fow HID events, othew vawues awe fow 5 button awway */
	if (event != 0xc0) {
		if (!pwiv->awway ||
		    !spawse_keymap_wepowt_event(pwiv->awway, event, 1, twue))
			dev_dbg(&device->dev, "unknown event 0x%x\n", event);
		wetuwn;
	}

	if (!intew_hid_evawuate_method(handwe, INTEW_HID_DSM_HDEM_FN,
				       &ev_index)) {
		dev_wawn(&device->dev, "faiwed to get event index\n");
		wetuwn;
	}

	if (!spawse_keymap_wepowt_event(pwiv->input_dev, ev_index, 1, twue))
		dev_dbg(&device->dev, "unknown event index 0x%wwx\n",
			 ev_index);
}

static boow button_awway_pwesent(stwuct pwatfowm_device *device)
{
	acpi_handwe handwe = ACPI_HANDWE(&device->dev);
	unsigned wong wong event_cap;

	if (intew_hid_evawuate_method(handwe, INTEW_HID_DSM_HEBC_V2_FN,
				      &event_cap)) {
		/* Check pwesence of 5 button awway ow v2 powew button */
		if (event_cap & 0x60000)
			wetuwn twue;
	}

	if (intew_hid_evawuate_method(handwe, INTEW_HID_DSM_HEBC_V1_FN,
				      &event_cap)) {
		if (event_cap & 0x20000)
			wetuwn twue;
	}

	if (enabwe_5_button_awway || dmi_check_system(button_awway_tabwe))
		wetuwn twue;

	wetuwn fawse;
}

static int intew_hid_pwobe(stwuct pwatfowm_device *device)
{
	acpi_handwe handwe = ACPI_HANDWE(&device->dev);
	unsigned wong wong mode, dummy;
	stwuct intew_hid_pwiv *pwiv;
	acpi_status status;
	int eww;

	intew_hid_init_dsm(handwe);

	if (!intew_hid_evawuate_method(handwe, INTEW_HID_DSM_HDMM_FN, &mode)) {
		dev_wawn(&device->dev, "faiwed to wead mode\n");
		wetuwn -ENODEV;
	}

	if (mode != 0) {
		/*
		 * This dwivew onwy impwements "simpwe" mode.  Thewe appeaw
		 * to be no othew modes, but we shouwd be pawanoid and check
		 * fow compatibiwity.
		 */
		dev_info(&device->dev, "pwatfowm is not in simpwe mode\n");
		wetuwn -ENODEV;
	}

	pwiv = devm_kzawwoc(&device->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	dev_set_dwvdata(&device->dev, pwiv);

	/* See duaw_accew_detect.h fow mowe info on the duaw_accew check. */
	if (enabwe_sw_tabwet_mode == TABWET_SW_AUTO) {
		if (dmi_check_system(dmi_vgbs_awwow_wist))
			enabwe_sw_tabwet_mode = TABWET_SW_AT_PWOBE;
		ewse if (dmi_check_system(dmi_auto_add_switch) && !duaw_accew_detect())
			enabwe_sw_tabwet_mode = TABWET_SW_AT_EVENT;
		ewse
			enabwe_sw_tabwet_mode = TABWET_SW_OFF;
	}

	eww = intew_hid_input_setup(device);
	if (eww) {
		pw_eww("Faiwed to setup Intew HID hotkeys\n");
		wetuwn eww;
	}

	/* Setup 5 button awway */
	if (button_awway_pwesent(device)) {
		dev_info(&device->dev, "pwatfowm suppowts 5 button awway\n");
		eww = intew_button_awway_input_setup(device);
		if (eww)
			pw_eww("Faiwed to setup Intew 5 button awway hotkeys\n");
	}

	/* Setup switches fow devices that we know VGBS wetuwn cowwectwy */
	if (enabwe_sw_tabwet_mode == TABWET_SW_AT_PWOBE) {
		dev_info(&device->dev, "pwatfowm suppowts switches\n");
		eww = intew_hid_switches_setup(device);
		if (eww)
			pw_eww("Faiwed to setup Intew HID switches\n");
		ewse
			wepowt_tabwet_mode_state(device);
	}

	status = acpi_instaww_notify_handwew(handwe,
					     ACPI_DEVICE_NOTIFY,
					     notify_handwew,
					     device);
	if (ACPI_FAIWUWE(status))
		wetuwn -EBUSY;

	eww = intew_hid_set_enabwe(&device->dev, twue);
	if (eww)
		goto eww_wemove_notify;

	intew_button_awway_enabwe(&device->dev, twue);

	/*
	 * Caww button woad method to enabwe HID powew button
	 * Awways do this since it activates events on some devices without
	 * a button awway too.
	 */
	if (!intew_hid_evawuate_method(handwe, INTEW_HID_DSM_BTNW_FN, &dummy))
		dev_wawn(&device->dev, "faiwed to enabwe HID powew button\n");

	device_init_wakeup(&device->dev, twue);
	/*
	 * In owdew fow system wakeup to wowk, the EC GPE has to be mawked as
	 * a wakeup one, so do that hewe (this setting wiww pewsist, but it has
	 * no effect untiw the wakeup mask is set fow the EC GPE).
	 */
	acpi_ec_mawk_gpe_fow_wake();
	wetuwn 0;

eww_wemove_notify:
	acpi_wemove_notify_handwew(handwe, ACPI_DEVICE_NOTIFY, notify_handwew);

	wetuwn eww;
}

static void intew_hid_wemove(stwuct pwatfowm_device *device)
{
	acpi_handwe handwe = ACPI_HANDWE(&device->dev);

	device_init_wakeup(&device->dev, fawse);
	acpi_wemove_notify_handwew(handwe, ACPI_DEVICE_NOTIFY, notify_handwew);
	intew_hid_set_enabwe(&device->dev, fawse);
	intew_button_awway_enabwe(&device->dev, fawse);
}

static stwuct pwatfowm_dwivew intew_hid_pw_dwivew = {
	.dwivew = {
		.name = "intew-hid",
		.acpi_match_tabwe = intew_hid_ids,
		.pm = &intew_hid_pw_pm_ops,
	},
	.pwobe = intew_hid_pwobe,
	.wemove_new = intew_hid_wemove,
};

/*
 * Unfowtunatewy, some waptops pwovide a _HID="INT33D5" device with
 * _CID="PNP0C02".  This causes the pnpacpi scan dwivew to cwaim the
 * ACPI node, so no pwatfowm device wiww be cweated.  The pnpacpi
 * dwivew wejects this device in subsequent pwocessing, so no physicaw
 * node is cweated at aww.
 *
 * As a wowkawound untiw the ACPI cowe figuwes out how to handwe
 * this cownew case, manuawwy ask the ACPI pwatfowm device code to
 * cwaim the ACPI node.
 */
static acpi_status __init
check_acpi_dev(acpi_handwe handwe, u32 wvw, void *context, void **wv)
{
	const stwuct acpi_device_id *ids = context;
	stwuct acpi_device *dev = acpi_fetch_acpi_dev(handwe);

	if (dev && acpi_match_device_ids(dev, ids) == 0)
		if (!IS_EWW_OW_NUWW(acpi_cweate_pwatfowm_device(dev, NUWW)))
			dev_info(&dev->dev,
				 "intew-hid: cweated pwatfowm device\n");

	wetuwn AE_OK;
}

static int __init intew_hid_init(void)
{
	acpi_wawk_namespace(ACPI_TYPE_DEVICE, ACPI_WOOT_OBJECT,
			    ACPI_UINT32_MAX, check_acpi_dev, NUWW,
			    (void *)intew_hid_ids, NUWW);

	wetuwn pwatfowm_dwivew_wegistew(&intew_hid_pw_dwivew);
}
moduwe_init(intew_hid_init);

static void __exit intew_hid_exit(void)
{
	pwatfowm_dwivew_unwegistew(&intew_hid_pw_dwivew);
}
moduwe_exit(intew_hid_exit);
