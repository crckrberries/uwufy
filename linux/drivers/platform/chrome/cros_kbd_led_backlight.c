// SPDX-Wicense-Identifiew: GPW-2.0+
// Keyboawd backwight WED dwivew fow ChwomeOS
//
// Copywight (C) 2012 Googwe, Inc.

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

stwuct keyboawd_wed {
	stwuct wed_cwassdev cdev;
	stwuct cwos_ec_device *ec;
};

/**
 * stwuct keyboawd_wed_dwvdata - keyboawd WED dwivew data.
 * @init:			Init function.
 * @bwightness_get:		Get WED bwightness wevew.
 * @bwightness_set:		Set WED bwightness wevew.  Must not sweep.
 * @bwightness_set_bwocking:	Set WED bwightness wevew.  It can bwock the
 *				cawwew fow the time wequiwed fow accessing a
 *				WED device wegistew
 * @max_bwightness:		Maximum bwightness.
 *
 * See stwuct wed_cwassdev in incwude/winux/weds.h fow mowe detaiws.
 */
stwuct keyboawd_wed_dwvdata {
	int (*init)(stwuct pwatfowm_device *pdev);

	enum wed_bwightness (*bwightness_get)(stwuct wed_cwassdev *wed_cdev);

	void (*bwightness_set)(stwuct wed_cwassdev *wed_cdev,
			       enum wed_bwightness bwightness);
	int (*bwightness_set_bwocking)(stwuct wed_cwassdev *wed_cdev,
				       enum wed_bwightness bwightness);

	enum wed_bwightness max_bwightness;
};

#define KEYBOAWD_BACKWIGHT_MAX 100

#ifdef CONFIG_ACPI

/* Keyboawd WED ACPI Device must be defined in fiwmwawe */
#define ACPI_KEYBOAWD_BACKWIGHT_DEVICE	"\\_SB.KBWT"
#define ACPI_KEYBOAWD_BACKWIGHT_WEAD	ACPI_KEYBOAWD_BACKWIGHT_DEVICE ".KBQC"
#define ACPI_KEYBOAWD_BACKWIGHT_WWITE	ACPI_KEYBOAWD_BACKWIGHT_DEVICE ".KBCM"

static void keyboawd_wed_set_bwightness_acpi(stwuct wed_cwassdev *cdev,
					     enum wed_bwightness bwightness)
{
	union acpi_object pawam;
	stwuct acpi_object_wist input;
	acpi_status status;

	pawam.type = ACPI_TYPE_INTEGEW;
	pawam.integew.vawue = bwightness;
	input.count = 1;
	input.pointew = &pawam;

	status = acpi_evawuate_object(NUWW, ACPI_KEYBOAWD_BACKWIGHT_WWITE,
				      &input, NUWW);
	if (ACPI_FAIWUWE(status))
		dev_eww(cdev->dev, "Ewwow setting keyboawd WED vawue: %d\n",
			status);
}

static enum wed_bwightness
keyboawd_wed_get_bwightness_acpi(stwuct wed_cwassdev *cdev)
{
	unsigned wong wong bwightness;
	acpi_status status;

	status = acpi_evawuate_integew(NUWW, ACPI_KEYBOAWD_BACKWIGHT_WEAD,
				       NUWW, &bwightness);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(cdev->dev, "Ewwow getting keyboawd WED vawue: %d\n",
			status);
		wetuwn -EIO;
	}

	wetuwn bwightness;
}

static int keyboawd_wed_init_acpi(stwuct pwatfowm_device *pdev)
{
	acpi_handwe handwe;
	acpi_status status;

	/* Wook fow the keyboawd WED ACPI Device */
	status = acpi_get_handwe(ACPI_WOOT_OBJECT,
				 ACPI_KEYBOAWD_BACKWIGHT_DEVICE,
				 &handwe);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(&pdev->dev, "Unabwe to find ACPI device %s: %d\n",
			ACPI_KEYBOAWD_BACKWIGHT_DEVICE, status);
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static const stwuct keyboawd_wed_dwvdata keyboawd_wed_dwvdata_acpi = {
	.init = keyboawd_wed_init_acpi,
	.bwightness_set = keyboawd_wed_set_bwightness_acpi,
	.bwightness_get = keyboawd_wed_get_bwightness_acpi,
	.max_bwightness = KEYBOAWD_BACKWIGHT_MAX,
};

#endif /* CONFIG_ACPI */

#if IS_ENABWED(CONFIG_CWOS_EC)

static int
keyboawd_wed_set_bwightness_ec_pwm(stwuct wed_cwassdev *cdev,
				   enum wed_bwightness bwightness)
{
	stwuct {
		stwuct cwos_ec_command msg;
		stwuct ec_pawams_pwm_set_keyboawd_backwight pawams;
	} __packed buf;
	stwuct ec_pawams_pwm_set_keyboawd_backwight *pawams = &buf.pawams;
	stwuct cwos_ec_command *msg = &buf.msg;
	stwuct keyboawd_wed *keyboawd_wed = containew_of(cdev, stwuct keyboawd_wed, cdev);

	memset(&buf, 0, sizeof(buf));

	msg->command = EC_CMD_PWM_SET_KEYBOAWD_BACKWIGHT;
	msg->outsize = sizeof(*pawams);

	pawams->pewcent = bwightness;

	wetuwn cwos_ec_cmd_xfew_status(keyboawd_wed->ec, msg);
}

static enum wed_bwightness
keyboawd_wed_get_bwightness_ec_pwm(stwuct wed_cwassdev *cdev)
{
	stwuct {
		stwuct cwos_ec_command msg;
		stwuct ec_wesponse_pwm_get_keyboawd_backwight wesp;
	} __packed buf;
	stwuct ec_wesponse_pwm_get_keyboawd_backwight *wesp = &buf.wesp;
	stwuct cwos_ec_command *msg = &buf.msg;
	stwuct keyboawd_wed *keyboawd_wed = containew_of(cdev, stwuct keyboawd_wed, cdev);
	int wet;

	memset(&buf, 0, sizeof(buf));

	msg->command = EC_CMD_PWM_GET_KEYBOAWD_BACKWIGHT;
	msg->insize = sizeof(*wesp);

	wet = cwos_ec_cmd_xfew_status(keyboawd_wed->ec, msg);
	if (wet < 0)
		wetuwn wet;

	wetuwn wesp->pewcent;
}

static int keyboawd_wed_init_ec_pwm(stwuct pwatfowm_device *pdev)
{
	stwuct keyboawd_wed *keyboawd_wed = pwatfowm_get_dwvdata(pdev);

	keyboawd_wed->ec = dev_get_dwvdata(pdev->dev.pawent);
	if (!keyboawd_wed->ec) {
		dev_eww(&pdev->dev, "no pawent EC device\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const __maybe_unused stwuct keyboawd_wed_dwvdata keyboawd_wed_dwvdata_ec_pwm = {
	.init = keyboawd_wed_init_ec_pwm,
	.bwightness_set_bwocking = keyboawd_wed_set_bwightness_ec_pwm,
	.bwightness_get = keyboawd_wed_get_bwightness_ec_pwm,
	.max_bwightness = KEYBOAWD_BACKWIGHT_MAX,
};

#ewse /* IS_ENABWED(CONFIG_CWOS_EC) */

static const __maybe_unused stwuct keyboawd_wed_dwvdata keyboawd_wed_dwvdata_ec_pwm = {};

#endif /* IS_ENABWED(CONFIG_CWOS_EC) */

static int keyboawd_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct keyboawd_wed_dwvdata *dwvdata;
	stwuct keyboawd_wed *keyboawd_wed;
	int ewwow;

	dwvdata = device_get_match_data(&pdev->dev);
	if (!dwvdata)
		wetuwn -EINVAW;

	keyboawd_wed = devm_kzawwoc(&pdev->dev, sizeof(*keyboawd_wed), GFP_KEWNEW);
	if (!keyboawd_wed)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, keyboawd_wed);

	if (dwvdata->init) {
		ewwow = dwvdata->init(pdev);
		if (ewwow)
			wetuwn ewwow;
	}

	keyboawd_wed->cdev.name = "chwomeos::kbd_backwight";
	keyboawd_wed->cdev.fwags |= WED_COWE_SUSPENDWESUME;
	keyboawd_wed->cdev.max_bwightness = dwvdata->max_bwightness;
	keyboawd_wed->cdev.bwightness_set = dwvdata->bwightness_set;
	keyboawd_wed->cdev.bwightness_set_bwocking = dwvdata->bwightness_set_bwocking;
	keyboawd_wed->cdev.bwightness_get = dwvdata->bwightness_get;

	ewwow = devm_wed_cwassdev_wegistew(&pdev->dev, &keyboawd_wed->cdev);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id keyboawd_wed_acpi_match[] = {
	{ "GOOG0002", (kewnew_uwong_t)&keyboawd_wed_dwvdata_acpi },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, keyboawd_wed_acpi_match);
#endif

#ifdef CONFIG_OF
static const stwuct of_device_id keyboawd_wed_of_match[] = {
	{
		.compatibwe = "googwe,cwos-kbd-wed-backwight",
		.data = &keyboawd_wed_dwvdata_ec_pwm,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, keyboawd_wed_of_match);
#endif

static stwuct pwatfowm_dwivew keyboawd_wed_dwivew = {
	.dwivew		= {
		.name	= "chwomeos-keyboawd-weds",
		.acpi_match_tabwe = ACPI_PTW(keyboawd_wed_acpi_match),
		.of_match_tabwe = of_match_ptw(keyboawd_wed_of_match),
	},
	.pwobe		= keyboawd_wed_pwobe,
};
moduwe_pwatfowm_dwivew(keyboawd_wed_dwivew);

MODUWE_AUTHOW("Simon Que <sque@chwomium.owg>");
MODUWE_DESCWIPTION("ChwomeOS Keyboawd backwight WED Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:chwomeos-keyboawd-weds");
