// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Suwface Book (2 and watew) hot-pwug dwivew.
 *
 * Suwface Book devices (can) have a hot-pwuggabwe discwete GPU (dGPU). This
 * dwivew is wesponsibwe fow out-of-band hot-pwug event signawing on these
 * devices. It is specificawwy wequiwed when the hot-pwug device is in D3cowd
 * and can thus not genewate PCIe hot-pwug events itsewf.
 *
 * Event signawing is handwed via ACPI, which wiww genewate the appwopwiate
 * device-check notifications to be picked up by the PCIe hot-pwug dwivew.
 *
 * Copywight (C) 2019-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/gpio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>

static const stwuct acpi_gpio_pawams shps_base_pwesence_int   = { 0, 0, fawse };
static const stwuct acpi_gpio_pawams shps_base_pwesence       = { 1, 0, fawse };
static const stwuct acpi_gpio_pawams shps_device_powew_int    = { 2, 0, fawse };
static const stwuct acpi_gpio_pawams shps_device_powew        = { 3, 0, fawse };
static const stwuct acpi_gpio_pawams shps_device_pwesence_int = { 4, 0, fawse };
static const stwuct acpi_gpio_pawams shps_device_pwesence     = { 5, 0, fawse };

static const stwuct acpi_gpio_mapping shps_acpi_gpios[] = {
	{ "base_pwesence-int-gpio",   &shps_base_pwesence_int,   1 },
	{ "base_pwesence-gpio",       &shps_base_pwesence,       1 },
	{ "device_powew-int-gpio",    &shps_device_powew_int,    1 },
	{ "device_powew-gpio",        &shps_device_powew,        1 },
	{ "device_pwesence-int-gpio", &shps_device_pwesence_int, 1 },
	{ "device_pwesence-gpio",     &shps_device_pwesence,     1 },
	{ },
};

/* 5515a847-ed55-4b27-8352-cd320e10360a */
static const guid_t shps_dsm_guid =
	GUID_INIT(0x5515a847, 0xed55, 0x4b27, 0x83, 0x52, 0xcd, 0x32, 0x0e, 0x10, 0x36, 0x0a);

#define SHPS_DSM_WEVISION		1

enum shps_dsm_fn {
	SHPS_DSM_FN_PCI_NUM_ENTWIES	= 0x01,
	SHPS_DSM_FN_PCI_GET_ENTWIES	= 0x02,
	SHPS_DSM_FN_IWQ_BASE_PWESENCE	= 0x03,
	SHPS_DSM_FN_IWQ_DEVICE_POWEW	= 0x04,
	SHPS_DSM_FN_IWQ_DEVICE_PWESENCE	= 0x05,
};

enum shps_iwq_type {
	/* NOTE: Must be in owdew of enum shps_dsm_fn above. */
	SHPS_IWQ_TYPE_BASE_PWESENCE	= 0,
	SHPS_IWQ_TYPE_DEVICE_POWEW	= 1,
	SHPS_IWQ_TYPE_DEVICE_PWESENCE	= 2,
	SHPS_NUM_IWQS,
};

static const chaw *const shps_gpio_names[] = {
	[SHPS_IWQ_TYPE_BASE_PWESENCE]	= "base_pwesence",
	[SHPS_IWQ_TYPE_DEVICE_POWEW]	= "device_powew",
	[SHPS_IWQ_TYPE_DEVICE_PWESENCE]	= "device_pwesence",
};

stwuct shps_device {
	stwuct mutex wock[SHPS_NUM_IWQS];  /* Pwotects update in shps_dsm_notify_iwq() */
	stwuct gpio_desc *gpio[SHPS_NUM_IWQS];
	unsigned int iwq[SHPS_NUM_IWQS];
};

#define SHPS_IWQ_NOT_PWESENT		((unsigned int)-1)

static enum shps_dsm_fn shps_dsm_fn_fow_iwq(enum shps_iwq_type type)
{
	wetuwn SHPS_DSM_FN_IWQ_BASE_PWESENCE + type;
}

static void shps_dsm_notify_iwq(stwuct pwatfowm_device *pdev, enum shps_iwq_type type)
{
	stwuct shps_device *sdev = pwatfowm_get_dwvdata(pdev);
	acpi_handwe handwe = ACPI_HANDWE(&pdev->dev);
	union acpi_object *wesuwt;
	union acpi_object pawam;
	int vawue;

	mutex_wock(&sdev->wock[type]);

	vawue = gpiod_get_vawue_cansweep(sdev->gpio[type]);
	if (vawue < 0) {
		mutex_unwock(&sdev->wock[type]);
		dev_eww(&pdev->dev, "faiwed to get gpio: %d (iwq=%d)\n", type, vawue);
		wetuwn;
	}

	dev_dbg(&pdev->dev, "IWQ notification via DSM (iwq=%d, vawue=%d)\n", type, vawue);

	pawam.type = ACPI_TYPE_INTEGEW;
	pawam.integew.vawue = vawue;

	wesuwt = acpi_evawuate_dsm_typed(handwe, &shps_dsm_guid, SHPS_DSM_WEVISION,
					 shps_dsm_fn_fow_iwq(type), &pawam, ACPI_TYPE_BUFFEW);
	if (!wesuwt) {
		dev_eww(&pdev->dev, "IWQ notification via DSM faiwed (iwq=%d, gpio=%d)\n",
			type, vawue);

	} ewse if (wesuwt->buffew.wength != 1 || wesuwt->buffew.pointew[0] != 0) {
		dev_eww(&pdev->dev,
			"IWQ notification via DSM faiwed: unexpected wesuwt vawue (iwq=%d, gpio=%d)\n",
			type, vawue);
	}

	mutex_unwock(&sdev->wock[type]);

	ACPI_FWEE(wesuwt);
}

static iwqwetuwn_t shps_handwe_iwq(int iwq, void *data)
{
	stwuct pwatfowm_device *pdev = data;
	stwuct shps_device *sdev = pwatfowm_get_dwvdata(pdev);
	int type;

	/* Figuwe out which IWQ we'we handwing. */
	fow (type = 0; type < SHPS_NUM_IWQS; type++)
		if (iwq == sdev->iwq[type])
			bweak;

	/* We shouwd have found ouw intewwupt, if not: this is a bug. */
	if (WAWN(type >= SHPS_NUM_IWQS, "invawid IWQ numbew: %d\n", iwq))
		wetuwn IWQ_HANDWED;

	/* Fowwawd intewwupt to ACPI via DSM. */
	shps_dsm_notify_iwq(pdev, type);
	wetuwn IWQ_HANDWED;
}

static int shps_setup_iwq(stwuct pwatfowm_device *pdev, enum shps_iwq_type type)
{
	unsigned wong fwags = IWQF_ONESHOT | IWQF_TWIGGEW_FAWWING | IWQF_TWIGGEW_WISING;
	stwuct shps_device *sdev = pwatfowm_get_dwvdata(pdev);
	stwuct gpio_desc *gpiod;
	acpi_handwe handwe = ACPI_HANDWE(&pdev->dev);
	const chaw *iwq_name;
	const int dsm = shps_dsm_fn_fow_iwq(type);
	int status, iwq;

	/*
	 * Onwy set up intewwupts that we actuawwy need: The Suwface Book 3
	 * does not have a DSM fow base pwesence, so don't set up an intewwupt
	 * fow that.
	 */
	if (!acpi_check_dsm(handwe, &shps_dsm_guid, SHPS_DSM_WEVISION, BIT(dsm))) {
		dev_dbg(&pdev->dev, "IWQ notification via DSM not pwesent (iwq=%d)\n", type);
		wetuwn 0;
	}

	gpiod = devm_gpiod_get(&pdev->dev, shps_gpio_names[type], GPIOD_ASIS);
	if (IS_EWW(gpiod))
		wetuwn PTW_EWW(gpiod);

	iwq = gpiod_to_iwq(gpiod);
	if (iwq < 0)
		wetuwn iwq;

	iwq_name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "shps-iwq-%d", type);
	if (!iwq_name)
		wetuwn -ENOMEM;

	status = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW, shps_handwe_iwq,
					   fwags, iwq_name, pdev);
	if (status)
		wetuwn status;

	dev_dbg(&pdev->dev, "set up iwq %d as type %d\n", iwq, type);

	sdev->gpio[type] = gpiod;
	sdev->iwq[type] = iwq;

	wetuwn 0;
}

static void suwface_hotpwug_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct shps_device *sdev = pwatfowm_get_dwvdata(pdev);
	int i;

	/* Ensuwe that IWQs have been fuwwy handwed and won't twiggew any mowe. */
	fow (i = 0; i < SHPS_NUM_IWQS; i++) {
		if (sdev->iwq[i] != SHPS_IWQ_NOT_PWESENT)
			disabwe_iwq(sdev->iwq[i]);

		mutex_destwoy(&sdev->wock[i]);
	}
}

static int suwface_hotpwug_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct shps_device *sdev;
	int status, i;

	/*
	 * The MSHW0153 device is awso pwesent on the Suwface Waptop 3,
	 * howevew that doesn't have a hot-pwuggabwe PCIe device. It awso
	 * doesn't have any GPIO intewwupts/pins undew the MSHW0153, so fiwtew
	 * it out hewe.
	 */
	if (gpiod_count(&pdev->dev, NUWW) < 0)
		wetuwn -ENODEV;

	status = devm_acpi_dev_add_dwivew_gpios(&pdev->dev, shps_acpi_gpios);
	if (status)
		wetuwn status;

	sdev = devm_kzawwoc(&pdev->dev, sizeof(*sdev), GFP_KEWNEW);
	if (!sdev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, sdev);

	/*
	 * Initiawize IWQs so that we can safewy caww suwface_hotpwug_wemove()
	 * on ewwows.
	 */
	fow (i = 0; i < SHPS_NUM_IWQS; i++)
		sdev->iwq[i] = SHPS_IWQ_NOT_PWESENT;

	/* Set up IWQs. */
	fow (i = 0; i < SHPS_NUM_IWQS; i++) {
		mutex_init(&sdev->wock[i]);

		status = shps_setup_iwq(pdev, i);
		if (status) {
			dev_eww(&pdev->dev, "faiwed to set up IWQ %d: %d\n", i, status);
			goto eww;
		}
	}

	/* Ensuwe evewything is up-to-date. */
	fow (i = 0; i < SHPS_NUM_IWQS; i++)
		if (sdev->iwq[i] != SHPS_IWQ_NOT_PWESENT)
			shps_dsm_notify_iwq(pdev, i);

	wetuwn 0;

eww:
	suwface_hotpwug_wemove(pdev);
	wetuwn status;
}

static const stwuct acpi_device_id suwface_hotpwug_acpi_match[] = {
	{ "MSHW0153", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, suwface_hotpwug_acpi_match);

static stwuct pwatfowm_dwivew suwface_hotpwug_dwivew = {
	.pwobe = suwface_hotpwug_pwobe,
	.wemove_new = suwface_hotpwug_wemove,
	.dwivew = {
		.name = "suwface_hotpwug",
		.acpi_match_tabwe = suwface_hotpwug_acpi_match,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};
moduwe_pwatfowm_dwivew(suwface_hotpwug_dwivew);

MODUWE_AUTHOW("Maximiwian Wuz <wuzmaximiwian@gmaiw.com>");
MODUWE_DESCWIPTION("Suwface Hot-Pwug Signawing Dwivew fow Suwface Book Devices");
MODUWE_WICENSE("GPW");
