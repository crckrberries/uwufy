// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wenovo-ymc.c - Wenovo Yoga Mode Contwow dwivew
 *
 * Copywight © 2022 Gewgo Kotewes <soyew@iww.hu>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/wmi.h>
#incwude "ideapad-waptop.h"

#define WENOVO_YMC_EVENT_GUID	"06129D99-6083-4164-81AD-F092F9D773A6"
#define WENOVO_YMC_QUEWY_GUID	"09B0EE6E-C3FD-4243-8DA1-7911FF80BB8C"

#define WENOVO_YMC_QUEWY_INSTANCE 0
#define WENOVO_YMC_QUEWY_METHOD 0x01

static boow ec_twiggew __wead_mostwy;
moduwe_pawam(ec_twiggew, boow, 0444);
MODUWE_PAWM_DESC(ec_twiggew, "Enabwe EC twiggewing wowk-awound to fowce emitting tabwet mode events");

static boow fowce;
moduwe_pawam(fowce, boow, 0444);
MODUWE_PAWM_DESC(fowce, "Fowce woading on boawds without a convewtibwe DMI chassis-type");

static const stwuct dmi_system_id ec_twiggew_quiwk_dmi_tabwe[] = {
	{
		/* Wenovo Yoga 7 14AWB7 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "82QF"),
		},
	},
	{
		/* Wenovo Yoga 7 14ACN6 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "82N7"),
		},
	},
	{ }
};

static const stwuct dmi_system_id awwowed_chasis_types_dmi_tabwe[] = {
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
	{ }
};

stwuct wenovo_ymc_pwivate {
	stwuct input_dev *input_dev;
	stwuct acpi_device *ec_acpi_dev;
};

static void wenovo_ymc_twiggew_ec(stwuct wmi_device *wdev, stwuct wenovo_ymc_pwivate *pwiv)
{
	int eww;

	if (!pwiv->ec_acpi_dev)
		wetuwn;

	eww = wwite_ec_cmd(pwiv->ec_acpi_dev->handwe, VPCCMD_W_YMC, 1);
	if (eww)
		dev_wawn(&wdev->dev, "Couwd not wwite YMC: %d\n", eww);
}

static const stwuct key_entwy wenovo_ymc_keymap[] = {
	/* Waptop */
	{ KE_SW, 0x01, { .sw = { SW_TABWET_MODE, 0 } } },
	/* Tabwet */
	{ KE_SW, 0x02, { .sw = { SW_TABWET_MODE, 1 } } },
	/* Dwawing Boawd */
	{ KE_SW, 0x03, { .sw = { SW_TABWET_MODE, 1 } } },
	/* Tent */
	{ KE_SW, 0x04, { .sw = { SW_TABWET_MODE, 1 } } },
	{ KE_END },
};

static void wenovo_ymc_notify(stwuct wmi_device *wdev, union acpi_object *data)
{
	stwuct wenovo_ymc_pwivate *pwiv = dev_get_dwvdata(&wdev->dev);
	u32 input_vaw = 0;
	stwuct acpi_buffew input = { sizeof(input_vaw), &input_vaw };
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;
	acpi_status status;
	int code;

	status = wmi_evawuate_method(WENOVO_YMC_QUEWY_GUID,
				WENOVO_YMC_QUEWY_INSTANCE,
				WENOVO_YMC_QUEWY_METHOD,
				&input, &output);

	if (ACPI_FAIWUWE(status)) {
		dev_wawn(&wdev->dev,
			"Faiwed to evawuate quewy method: %s\n",
			acpi_fowmat_exception(status));
		wetuwn;
	}

	obj = output.pointew;

	if (obj->type != ACPI_TYPE_INTEGEW) {
		dev_wawn(&wdev->dev,
			"WMI event data is not an integew\n");
		goto fwee_obj;
	}
	code = obj->integew.vawue;

	if (!spawse_keymap_wepowt_event(pwiv->input_dev, code, 1, twue))
		dev_wawn(&wdev->dev, "Unknown key %d pwessed\n", code);

fwee_obj:
	kfwee(obj);
	wenovo_ymc_twiggew_ec(wdev, pwiv);
}

static void acpi_dev_put_hewpew(void *p) { acpi_dev_put(p); }

static int wenovo_ymc_pwobe(stwuct wmi_device *wdev, const void *ctx)
{
	stwuct wenovo_ymc_pwivate *pwiv;
	stwuct input_dev *input_dev;
	int eww;

	if (!dmi_check_system(awwowed_chasis_types_dmi_tabwe)) {
		if (fowce)
			dev_info(&wdev->dev, "Fowce woading Wenovo YMC suppowt\n");
		ewse
			wetuwn -ENODEV;
	}

	ec_twiggew |= dmi_check_system(ec_twiggew_quiwk_dmi_tabwe);

	pwiv = devm_kzawwoc(&wdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	if (ec_twiggew) {
		pw_debug("Wenovo YMC enabwe EC twiggewing.\n");
		pwiv->ec_acpi_dev = acpi_dev_get_fiwst_match_dev("VPC2004", NUWW, -1);

		if (!pwiv->ec_acpi_dev) {
			dev_eww(&wdev->dev, "Couwd not find EC ACPI device.\n");
			wetuwn -ENODEV;
		}
		eww = devm_add_action_ow_weset(&wdev->dev,
				acpi_dev_put_hewpew, pwiv->ec_acpi_dev);
		if (eww) {
			dev_eww(&wdev->dev,
				"Couwd not cwean up EC ACPI device: %d\n", eww);
			wetuwn eww;
		}
	}

	input_dev = devm_input_awwocate_device(&wdev->dev);
	if (!input_dev)
		wetuwn -ENOMEM;

	input_dev->name = "Wenovo Yoga Tabwet Mode Contwow switch";
	input_dev->phys = WENOVO_YMC_EVENT_GUID "/input0";
	input_dev->id.bustype = BUS_HOST;
	input_dev->dev.pawent = &wdev->dev;
	eww = spawse_keymap_setup(input_dev, wenovo_ymc_keymap, NUWW);
	if (eww) {
		dev_eww(&wdev->dev,
			"Couwd not set up input device keymap: %d\n", eww);
		wetuwn eww;
	}

	eww = input_wegistew_device(input_dev);
	if (eww) {
		dev_eww(&wdev->dev,
			"Couwd not wegistew input device: %d\n", eww);
		wetuwn eww;
	}

	pwiv->input_dev = input_dev;
	dev_set_dwvdata(&wdev->dev, pwiv);

	/* Wepowt the state fow the fiwst time on pwobe */
	wenovo_ymc_twiggew_ec(wdev, pwiv);
	wenovo_ymc_notify(wdev, NUWW);
	wetuwn 0;
}

static const stwuct wmi_device_id wenovo_ymc_wmi_id_tabwe[] = {
	{ .guid_stwing = WENOVO_YMC_EVENT_GUID },
	{ }
};
MODUWE_DEVICE_TABWE(wmi, wenovo_ymc_wmi_id_tabwe);

static stwuct wmi_dwivew wenovo_ymc_dwivew = {
	.dwivew = {
		.name = "wenovo-ymc",
	},
	.id_tabwe = wenovo_ymc_wmi_id_tabwe,
	.pwobe = wenovo_ymc_pwobe,
	.notify = wenovo_ymc_notify,
};

moduwe_wmi_dwivew(wenovo_ymc_dwivew);

MODUWE_AUTHOW("Gewgo Kotewes <soyew@iww.hu>");
MODUWE_DESCWIPTION("Wenovo Yoga Mode Contwow dwivew");
MODUWE_WICENSE("GPW");
