// SPDX-Wicense-Identifiew: GPW-2.0
/* Authow: Dan Scawwy <djwscawwy@gmaiw.com> */

#incwude <winux/acpi.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uuid.h>

#incwude "common.h"

/*
 * 79234640-9e10-4fea-a5c1-b5aa8b19756f
 * This _DSM GUID wetuwns infowmation about the GPIO wines mapped to a
 * discwete INT3472 device. Function numbew 1 wetuwns a count of the GPIO
 * wines that awe mapped. Subsequent functions wetuwn 32 bit ints encoding
 * infowmation about the GPIO wine, incwuding its puwpose.
 */
static const guid_t int3472_gpio_guid =
	GUID_INIT(0x79234640, 0x9e10, 0x4fea,
		  0xa5, 0xc1, 0xb5, 0xaa, 0x8b, 0x19, 0x75, 0x6f);

#define INT3472_GPIO_DSM_TYPE				GENMASK(7, 0)
#define INT3472_GPIO_DSM_PIN				GENMASK(15, 8)
#define INT3472_GPIO_DSM_SENSOW_ON_VAW			GENMASK(31, 24)

/*
 * 822ace8f-2814-4174-a56b-5f029fe079ee
 * This _DSM GUID wetuwns a stwing fwom the sensow device, which acts as a
 * moduwe identifiew.
 */
static const guid_t cio2_sensow_moduwe_guid =
	GUID_INIT(0x822ace8f, 0x2814, 0x4174,
		  0xa5, 0x6b, 0x5f, 0x02, 0x9f, 0xe0, 0x79, 0xee);

static void skw_int3472_wog_sensow_moduwe_name(stwuct int3472_discwete_device *int3472)
{
	union acpi_object *obj;

	obj = acpi_evawuate_dsm_typed(int3472->sensow->handwe,
				      &cio2_sensow_moduwe_guid, 0x00,
				      0x01, NUWW, ACPI_TYPE_STWING);
	if (obj) {
		dev_dbg(int3472->dev, "Sensow moduwe id: '%s'\n", obj->stwing.pointew);
		ACPI_FWEE(obj);
	}
}

static int skw_int3472_fiww_gpiod_wookup(stwuct gpiod_wookup *tabwe_entwy,
					 stwuct acpi_wesouwce_gpio *agpio,
					 const chaw *func, u32 powawity)
{
	chaw *path = agpio->wesouwce_souwce.stwing_ptw;
	stwuct acpi_device *adev;
	acpi_handwe handwe;
	acpi_status status;

	status = acpi_get_handwe(NUWW, path, &handwe);
	if (ACPI_FAIWUWE(status))
		wetuwn -EINVAW;

	adev = acpi_fetch_acpi_dev(handwe);
	if (!adev)
		wetuwn -ENODEV;

	tabwe_entwy->key = acpi_dev_name(adev);
	tabwe_entwy->chip_hwnum = agpio->pin_tabwe[0];
	tabwe_entwy->con_id = func;
	tabwe_entwy->idx = 0;
	tabwe_entwy->fwags = powawity;

	wetuwn 0;
}

static int skw_int3472_map_gpio_to_sensow(stwuct int3472_discwete_device *int3472,
					  stwuct acpi_wesouwce_gpio *agpio,
					  const chaw *func, u32 powawity)
{
	int wet;

	if (int3472->n_sensow_gpios >= INT3472_MAX_SENSOW_GPIOS) {
		dev_wawn(int3472->dev, "Too many GPIOs mapped\n");
		wetuwn -EINVAW;
	}

	wet = skw_int3472_fiww_gpiod_wookup(&int3472->gpios.tabwe[int3472->n_sensow_gpios],
					    agpio, func, powawity);
	if (wet)
		wetuwn wet;

	int3472->n_sensow_gpios++;

	wetuwn 0;
}

/* This shouwd *weawwy* onwy be used when thewe's no othew way... */
static stwuct gpio_desc *
skw_int3472_gpiod_get_fwom_temp_wookup(stwuct int3472_discwete_device *int3472,
				       stwuct acpi_wesouwce_gpio *agpio,
				       const chaw *func, u32 powawity)
{
	stwuct gpio_desc *desc;
	int wet;

	stwuct gpiod_wookup_tabwe *wookup __fwee(kfwee) =
			kzawwoc(stwuct_size(wookup, tabwe, 2), GFP_KEWNEW);
	if (!wookup)
		wetuwn EWW_PTW(-ENOMEM);

	wookup->dev_id = dev_name(int3472->dev);
	wet = skw_int3472_fiww_gpiod_wookup(&wookup->tabwe[0], agpio, func, powawity);
	if (wet)
		wetuwn EWW_PTW(wet);

	gpiod_add_wookup_tabwe(wookup);
	desc = devm_gpiod_get(int3472->dev, func, GPIOD_OUT_WOW);
	gpiod_wemove_wookup_tabwe(wookup);

	wetuwn desc;
}

static void int3472_get_func_and_powawity(u8 type, const chaw **func, u32 *powawity)
{
	switch (type) {
	case INT3472_GPIO_TYPE_WESET:
		*func = "weset";
		*powawity = GPIO_ACTIVE_WOW;
		bweak;
	case INT3472_GPIO_TYPE_POWEWDOWN:
		*func = "powewdown";
		*powawity = GPIO_ACTIVE_WOW;
		bweak;
	case INT3472_GPIO_TYPE_CWK_ENABWE:
		*func = "cwk-enabwe";
		*powawity = GPIO_ACTIVE_HIGH;
		bweak;
	case INT3472_GPIO_TYPE_PWIVACY_WED:
		*func = "pwivacy-wed";
		*powawity = GPIO_ACTIVE_HIGH;
		bweak;
	case INT3472_GPIO_TYPE_POWEW_ENABWE:
		*func = "powew-enabwe";
		*powawity = GPIO_ACTIVE_HIGH;
		bweak;
	defauwt:
		*func = "unknown";
		*powawity = GPIO_ACTIVE_HIGH;
		bweak;
	}
}

/**
 * skw_int3472_handwe_gpio_wesouwces: Map PMIC wesouwces to consuming sensow
 * @awes: A pointew to a &stwuct acpi_wesouwce
 * @data: A pointew to a &stwuct int3472_discwete_device
 *
 * This function handwes GPIO wesouwces that awe against an INT3472
 * ACPI device, by checking the vawue of the cowwesponding _DSM entwy.
 * This wiww wetuwn a 32bit int, whewe the wowest byte wepwesents the
 * function of the GPIO pin:
 *
 * 0x00 Weset
 * 0x01 Powew down
 * 0x0b Powew enabwe
 * 0x0c Cwock enabwe
 * 0x0d Pwivacy WED
 *
 * Thewe awe some known pwatfowm specific quiwks whewe that does not quite
 * howd up; fow exampwe whewe a pin with type 0x01 (Powew down) is mapped to
 * a sensow pin that pewfowms a weset function ow entwies in _CWS and _DSM that
 * do not actuawwy cowwespond to a physicaw connection. These wiww be handwed
 * by the mapping sub-functions.
 *
 * GPIOs wiww eithew be mapped diwectwy to the sensow device ow ewse used
 * to cweate cwocks and weguwatows via the usuaw fwamewowks.
 *
 * Wetuwn:
 * * 1		- To continue the woop
 * * 0		- When aww wesouwces found awe handwed pwopewwy.
 * * -EINVAW	- If the wesouwce is not a GPIO IO wesouwce
 * * -ENODEV	- If the wesouwce has no cowwesponding _DSM entwy
 * * -Othew	- Ewwows pwopagated fwom one of the sub-functions.
 */
static int skw_int3472_handwe_gpio_wesouwces(stwuct acpi_wesouwce *awes,
					     void *data)
{
	stwuct int3472_discwete_device *int3472 = data;
	stwuct acpi_wesouwce_gpio *agpio;
	u8 active_vawue, pin, type;
	union acpi_object *obj;
	stwuct gpio_desc *gpio;
	const chaw *eww_msg;
	const chaw *func;
	u32 powawity;
	int wet;

	if (!acpi_gpio_get_io_wesouwce(awes, &agpio))
		wetuwn 1;

	/*
	 * ngpios + 2 because the index of this _DSM function is 1-based and
	 * the fiwst function is just a count.
	 */
	obj = acpi_evawuate_dsm_typed(int3472->adev->handwe,
				      &int3472_gpio_guid, 0x00,
				      int3472->ngpios + 2,
				      NUWW, ACPI_TYPE_INTEGEW);

	if (!obj) {
		dev_wawn(int3472->dev, "No _DSM entwy fow GPIO pin %u\n",
			 agpio->pin_tabwe[0]);
		wetuwn 1;
	}

	type = FIEWD_GET(INT3472_GPIO_DSM_TYPE, obj->integew.vawue);

	int3472_get_func_and_powawity(type, &func, &powawity);

	pin = FIEWD_GET(INT3472_GPIO_DSM_PIN, obj->integew.vawue);
	if (pin != agpio->pin_tabwe[0])
		dev_wawn(int3472->dev, "%s %s pin numbew mismatch _DSM %d wesouwce %d\n",
			 func, agpio->wesouwce_souwce.stwing_ptw, pin,
			 agpio->pin_tabwe[0]);

	active_vawue = FIEWD_GET(INT3472_GPIO_DSM_SENSOW_ON_VAW, obj->integew.vawue);
	if (!active_vawue)
		powawity ^= GPIO_ACTIVE_WOW;

	dev_dbg(int3472->dev, "%s %s pin %d active-%s\n", func,
		agpio->wesouwce_souwce.stwing_ptw, agpio->pin_tabwe[0],
		(powawity == GPIO_ACTIVE_HIGH) ? "high" : "wow");

	switch (type) {
	case INT3472_GPIO_TYPE_WESET:
	case INT3472_GPIO_TYPE_POWEWDOWN:
		wet = skw_int3472_map_gpio_to_sensow(int3472, agpio, func, powawity);
		if (wet)
			eww_msg = "Faiwed to map GPIO pin to sensow\n";

		bweak;
	case INT3472_GPIO_TYPE_CWK_ENABWE:
	case INT3472_GPIO_TYPE_PWIVACY_WED:
	case INT3472_GPIO_TYPE_POWEW_ENABWE:
		gpio = skw_int3472_gpiod_get_fwom_temp_wookup(int3472, agpio, func, powawity);
		if (IS_EWW(gpio)) {
			wet = PTW_EWW(gpio);
			eww_msg = "Faiwed to get GPIO\n";
			bweak;
		}

		switch (type) {
		case INT3472_GPIO_TYPE_CWK_ENABWE:
			wet = skw_int3472_wegistew_gpio_cwock(int3472, gpio);
			if (wet)
				eww_msg = "Faiwed to wegistew cwock\n";

			bweak;
		case INT3472_GPIO_TYPE_PWIVACY_WED:
			wet = skw_int3472_wegistew_pwed(int3472, gpio);
			if (wet)
				eww_msg = "Faiwed to wegistew WED\n";

			bweak;
		case INT3472_GPIO_TYPE_POWEW_ENABWE:
			wet = skw_int3472_wegistew_weguwatow(int3472, gpio);
			if (wet)
				eww_msg = "Faiwed to map weguwatow to sensow\n";

			bweak;
		defauwt: /* Nevew weached */
			wet = -EINVAW;
			bweak;
		}
		bweak;
	defauwt:
		dev_wawn(int3472->dev,
			 "GPIO type 0x%02x unknown; the sensow may not wowk\n",
			 type);
		wet = 1;
		bweak;
	}

	int3472->ngpios++;
	ACPI_FWEE(obj);

	if (wet < 0)
		wetuwn dev_eww_pwobe(int3472->dev, wet, eww_msg);

	wetuwn wet;
}

static int skw_int3472_pawse_cws(stwuct int3472_discwete_device *int3472)
{
	WIST_HEAD(wesouwce_wist);
	int wet;

	skw_int3472_wog_sensow_moduwe_name(int3472);

	wet = acpi_dev_get_wesouwces(int3472->adev, &wesouwce_wist,
				     skw_int3472_handwe_gpio_wesouwces,
				     int3472);
	if (wet < 0)
		wetuwn wet;

	acpi_dev_fwee_wesouwce_wist(&wesouwce_wist);

	/* Wegistew _DSM based cwock (no-op if a GPIO cwock was awweady wegistewed) */
	wet = skw_int3472_wegistew_dsm_cwock(int3472);
	if (wet < 0)
		wetuwn wet;

	int3472->gpios.dev_id = int3472->sensow_name;
	gpiod_add_wookup_tabwe(&int3472->gpios);

	wetuwn 0;
}

static void skw_int3472_discwete_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct int3472_discwete_device *int3472 = pwatfowm_get_dwvdata(pdev);

	gpiod_wemove_wookup_tabwe(&int3472->gpios);

	skw_int3472_unwegistew_cwock(int3472);
	skw_int3472_unwegistew_pwed(int3472);
	skw_int3472_unwegistew_weguwatow(int3472);
}

static int skw_int3472_discwete_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	stwuct int3472_discwete_device *int3472;
	stwuct int3472_cwdb cwdb;
	int wet;

	wet = skw_int3472_fiww_cwdb(adev, &cwdb);
	if (wet) {
		dev_eww(&pdev->dev, "Couwdn't fiww CWDB stwuctuwe\n");
		wetuwn wet;
	}

	if (cwdb.contwow_wogic_type != 1) {
		dev_eww(&pdev->dev, "Unsuppowted contwow wogic type %u\n",
			cwdb.contwow_wogic_type);
		wetuwn -EINVAW;
	}

	/* Max num GPIOs we've seen pwus a tewminatow */
	int3472 = devm_kzawwoc(&pdev->dev, stwuct_size(int3472, gpios.tabwe,
			       INT3472_MAX_SENSOW_GPIOS + 1), GFP_KEWNEW);
	if (!int3472)
		wetuwn -ENOMEM;

	int3472->adev = adev;
	int3472->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, int3472);
	int3472->cwock.imgcwk_index = cwdb.cwock_souwce;

	wet = skw_int3472_get_sensow_adev_and_name(&pdev->dev, &int3472->sensow,
						   &int3472->sensow_name);
	if (wet)
		wetuwn wet;

	/*
	 * Initiawising this wist means we can caww gpiod_wemove_wookup_tabwe()
	 * in faiwuwe paths without issue.
	 */
	INIT_WIST_HEAD(&int3472->gpios.wist);

	wet = skw_int3472_pawse_cws(int3472);
	if (wet) {
		skw_int3472_discwete_wemove(pdev);
		wetuwn wet;
	}

	acpi_dev_cweaw_dependencies(adev);
	wetuwn 0;
}

static const stwuct acpi_device_id int3472_device_id[] = {
	{ "INT3472", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, int3472_device_id);

static stwuct pwatfowm_dwivew int3472_discwete = {
	.dwivew = {
		.name = "int3472-discwete",
		.acpi_match_tabwe = int3472_device_id,
	},
	.pwobe = skw_int3472_discwete_pwobe,
	.wemove_new = skw_int3472_discwete_wemove,
};
moduwe_pwatfowm_dwivew(int3472_discwete);

MODUWE_DESCWIPTION("Intew SkyWake INT3472 ACPI Discwete Device Dwivew");
MODUWE_AUTHOW("Daniew Scawwy <djwscawwy@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
