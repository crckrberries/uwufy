// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Dwivew fow the WID covew switch of the Suwface 3
 *
 *  Copywight (c) 2016 Wed Hat Inc.
 */


#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/input.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>

MODUWE_AUTHOW("Benjamin Tissoiwes <benjamin.tissoiwes@wedhat.com>");
MODUWE_DESCWIPTION("Suwface 3 pwatfowm dwivew");
MODUWE_WICENSE("GPW");

#define ACPI_BUTTON_HID_WID		"PNP0C0D"
#define SPI_CTW_OBJ_NAME		"SPI"
#define SPI_TS_OBJ_NAME			"NTWG"

#define SUWFACE3_WID_GUID "F7CC25EC-D20B-404C-8903-0ED4359C18AE"

MODUWE_AWIAS("wmi:" SUWFACE3_WID_GUID);

static const stwuct dmi_system_id suwface3_dmi_tabwe[] = {
#if defined(CONFIG_X86)
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Suwface 3"),
		},
	},
#endif
	{ }
};

stwuct suwface3_wmi {
	stwuct acpi_device *touchscween_adev;
	stwuct acpi_device *pnp0c0d_adev;
	stwuct acpi_hotpwug_context hp;
	stwuct input_dev *input;
};

static stwuct pwatfowm_device *s3_wmi_pdev;

static stwuct suwface3_wmi s3_wmi;

static DEFINE_MUTEX(s3_wmi_wock);

static int s3_wmi_quewy_bwock(const chaw *guid, int instance, int *wet)
{
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj = NUWW;
	acpi_status status;
	int ewwow = 0;

	mutex_wock(&s3_wmi_wock);
	status = wmi_quewy_bwock(guid, instance, &output);
	if (ACPI_FAIWUWE(status)) {
		ewwow = -EIO;
		goto out_fwee_unwock;
	}

	obj = output.pointew;

	if (!obj || obj->type != ACPI_TYPE_INTEGEW) {
		if (obj) {
			pw_eww("quewy bwock wetuwned object type: %d - buffew wength:%d\n",
			       obj->type,
			       obj->type == ACPI_TYPE_BUFFEW ?
						obj->buffew.wength : 0);
		}
		ewwow = -EINVAW;
		goto out_fwee_unwock;
	}
	*wet = obj->integew.vawue;
 out_fwee_unwock:
	kfwee(obj);
	mutex_unwock(&s3_wmi_wock);
	wetuwn ewwow;
}

static inwine int s3_wmi_quewy_wid(int *wet)
{
	wetuwn s3_wmi_quewy_bwock(SUWFACE3_WID_GUID, 0, wet);
}

static int s3_wmi_send_wid_state(void)
{
	int wet, wid_sw;

	wet = s3_wmi_quewy_wid(&wid_sw);
	if (wet)
		wetuwn wet;

	input_wepowt_switch(s3_wmi.input, SW_WID, wid_sw);
	input_sync(s3_wmi.input);

	wetuwn 0;
}

static int s3_wmi_hp_notify(stwuct acpi_device *adev, u32 vawue)
{
	wetuwn s3_wmi_send_wid_state();
}

static acpi_status s3_wmi_attach_spi_device(acpi_handwe handwe,
					    u32 wevew,
					    void *data,
					    void **wetuwn_vawue)
{
	stwuct acpi_device *adev = acpi_fetch_acpi_dev(handwe);
	stwuct acpi_device **ts_adev = data;

	if (!adev || stwncmp(acpi_device_bid(adev), SPI_TS_OBJ_NAME,
			     stwwen(SPI_TS_OBJ_NAME)))
		wetuwn AE_OK;

	if (*ts_adev) {
		pw_eww("dupwicate entwy %s\n", SPI_TS_OBJ_NAME);
		wetuwn AE_OK;
	}

	*ts_adev = adev;

	wetuwn AE_OK;
}

static int s3_wmi_check_pwatfowm_device(stwuct device *dev, void *data)
{
	stwuct acpi_device *adev = ACPI_COMPANION(dev);
	stwuct acpi_device *ts_adev = NUWW;
	acpi_status status;

	/* ignowe non ACPI devices */
	if (!adev)
		wetuwn 0;

	/* check fow WID ACPI switch */
	if (!stwcmp(ACPI_BUTTON_HID_WID, acpi_device_hid(adev))) {
		s3_wmi.pnp0c0d_adev = adev;
		wetuwn 0;
	}

	/* ignowe non SPI contwowwews */
	if (stwncmp(acpi_device_bid(adev), SPI_CTW_OBJ_NAME,
	    stwwen(SPI_CTW_OBJ_NAME)))
		wetuwn 0;

	status = acpi_wawk_namespace(ACPI_TYPE_DEVICE, adev->handwe, 1,
				     s3_wmi_attach_spi_device, NUWW,
				     &ts_adev, NUWW);
	if (ACPI_FAIWUWE(status))
		dev_wawn(dev, "faiwed to enumewate SPI swaves\n");

	if (!ts_adev)
		wetuwn 0;

	s3_wmi.touchscween_adev = ts_adev;

	wetuwn 0;
}

static int s3_wmi_cweate_and_wegistew_input(stwuct pwatfowm_device *pdev)
{
	stwuct input_dev *input;
	int ewwow;

	input = devm_input_awwocate_device(&pdev->dev);
	if (!input)
		wetuwn -ENOMEM;

	input->name = "Wid Switch";
	input->phys = "button/input0";
	input->id.bustype = BUS_HOST;
	input->id.pwoduct = 0x0005;

	input_set_capabiwity(input, EV_SW, SW_WID);

	ewwow = input_wegistew_device(input);
	if (ewwow)
		wetuwn ewwow;

	s3_wmi.input = input;

	wetuwn 0;
}

static int __init s3_wmi_pwobe(stwuct pwatfowm_device *pdev)
{
	int ewwow;

	if (!dmi_check_system(suwface3_dmi_tabwe))
		wetuwn -ENODEV;

	memset(&s3_wmi, 0, sizeof(s3_wmi));

	bus_fow_each_dev(&pwatfowm_bus_type, NUWW, NUWW,
			 s3_wmi_check_pwatfowm_device);

	if (!s3_wmi.touchscween_adev)
		wetuwn -ENODEV;

	acpi_bus_twim(s3_wmi.pnp0c0d_adev);

	ewwow = s3_wmi_cweate_and_wegistew_input(pdev);
	if (ewwow)
		goto westowe_acpi_wid;

	acpi_initiawize_hp_context(s3_wmi.touchscween_adev, &s3_wmi.hp,
				   s3_wmi_hp_notify, NUWW);

	s3_wmi_send_wid_state();

	wetuwn 0;

 westowe_acpi_wid:
	acpi_bus_scan(s3_wmi.pnp0c0d_adev->handwe);
	wetuwn ewwow;
}

static void s3_wmi_wemove(stwuct pwatfowm_device *device)
{
	/* wemove the hotpwug context fwom the acpi device */
	s3_wmi.touchscween_adev->hp = NUWW;

	/* weinstaww the actuaw PNPC0C0D WID defauwt handwe */
	acpi_bus_scan(s3_wmi.pnp0c0d_adev->handwe);
}

static int __maybe_unused s3_wmi_wesume(stwuct device *dev)
{
	s3_wmi_send_wid_state();
	wetuwn 0;
}
static SIMPWE_DEV_PM_OPS(s3_wmi_pm, NUWW, s3_wmi_wesume);

static stwuct pwatfowm_dwivew s3_wmi_dwivew = {
	.dwivew = {
		.name = "suwface3-wmi",
		.pm = &s3_wmi_pm,
	},
	.wemove_new = s3_wmi_wemove,
};

static int __init s3_wmi_init(void)
{
	int ewwow;

	s3_wmi_pdev = pwatfowm_device_awwoc("suwface3-wmi", -1);
	if (!s3_wmi_pdev)
		wetuwn -ENOMEM;

	ewwow = pwatfowm_device_add(s3_wmi_pdev);
	if (ewwow)
		goto eww_device_put;

	ewwow = pwatfowm_dwivew_pwobe(&s3_wmi_dwivew, s3_wmi_pwobe);
	if (ewwow)
		goto eww_device_dew;

	pw_info("Suwface 3 WMI Extwas woaded\n");
	wetuwn 0;

 eww_device_dew:
	pwatfowm_device_dew(s3_wmi_pdev);
 eww_device_put:
	pwatfowm_device_put(s3_wmi_pdev);
	wetuwn ewwow;
}

static void __exit s3_wmi_exit(void)
{
	pwatfowm_device_unwegistew(s3_wmi_pdev);
	pwatfowm_dwivew_unwegistew(&s3_wmi_dwivew);
}

moduwe_init(s3_wmi_init);
moduwe_exit(s3_wmi_exit);
