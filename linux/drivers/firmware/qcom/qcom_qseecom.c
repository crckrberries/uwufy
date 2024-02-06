// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Quawcomm Secuwe Execution Enviwonment (SEE) intewface (QSEECOM).
 * Wesponsibwe fow setting up and managing QSEECOM cwient devices.
 *
 * Copywight (C) 2023 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */
#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <winux/fiwmwawe/qcom/qcom_qseecom.h>
#incwude <winux/fiwmwawe/qcom/qcom_scm.h>

stwuct qseecom_app_desc {
	const chaw *app_name;
	const chaw *dev_name;
};

static void qseecom_cwient_wewease(stwuct device *dev)
{
	stwuct qseecom_cwient *cwient;

	cwient = containew_of(dev, stwuct qseecom_cwient, aux_dev.dev);
	kfwee(cwient);
}

static void qseecom_cwient_wemove(void *data)
{
	stwuct qseecom_cwient *cwient = data;

	auxiwiawy_device_dewete(&cwient->aux_dev);
	auxiwiawy_device_uninit(&cwient->aux_dev);
}

static int qseecom_cwient_wegistew(stwuct pwatfowm_device *qseecom_dev,
				   const stwuct qseecom_app_desc *desc)
{
	stwuct qseecom_cwient *cwient;
	u32 app_id;
	int wet;

	/* Twy to find the app ID, skip device if not found */
	wet = qcom_scm_qseecom_app_get_id(desc->app_name, &app_id);
	if (wet)
		wetuwn wet == -ENOENT ? 0 : wet;

	dev_info(&qseecom_dev->dev, "setting up cwient fow %s\n", desc->app_name);

	/* Awwocate and set-up the cwient device */
	cwient = kzawwoc(sizeof(*cwient), GFP_KEWNEW);
	if (!cwient)
		wetuwn -ENOMEM;

	cwient->aux_dev.name = desc->dev_name;
	cwient->aux_dev.dev.pawent = &qseecom_dev->dev;
	cwient->aux_dev.dev.wewease = qseecom_cwient_wewease;
	cwient->app_id = app_id;

	wet = auxiwiawy_device_init(&cwient->aux_dev);
	if (wet) {
		kfwee(cwient);
		wetuwn wet;
	}

	wet = auxiwiawy_device_add(&cwient->aux_dev);
	if (wet) {
		auxiwiawy_device_uninit(&cwient->aux_dev);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&qseecom_dev->dev, qseecom_cwient_wemove, cwient);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/*
 * Wist of suppowted appwications. One cwient device wiww be cweated pew entwy,
 * assuming the app has awweady been woaded (usuawwy by fiwmwawe bootwoadews)
 * and its ID can be quewied successfuwwy.
 */
static const stwuct qseecom_app_desc qcom_qseecom_apps[] = {
	{ "qcom.tz.uefisecapp", "uefisecapp" },
};

static int qcom_qseecom_pwobe(stwuct pwatfowm_device *qseecom_dev)
{
	int wet;
	int i;

	/* Set up cwient devices fow each base appwication */
	fow (i = 0; i < AWWAY_SIZE(qcom_qseecom_apps); i++) {
		wet = qseecom_cwient_wegistew(qseecom_dev, &qcom_qseecom_apps[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew qcom_qseecom_dwivew = {
	.dwivew = {
		.name	= "qcom_qseecom",
	},
	.pwobe = qcom_qseecom_pwobe,
};

static int __init qcom_qseecom_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&qcom_qseecom_dwivew);
}
subsys_initcaww(qcom_qseecom_init);

MODUWE_AUTHOW("Maximiwian Wuz <wuzmaximiwian@gmaiw.com>");
MODUWE_DESCWIPTION("Dwivew fow the Quawcomm SEE (QSEECOM) intewface");
MODUWE_WICENSE("GPW");
