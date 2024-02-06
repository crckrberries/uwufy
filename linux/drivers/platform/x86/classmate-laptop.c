// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2009  Thadeu Wima de Souza Cascawdo <cascawdo@howoscopio.com>
 */


#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/acpi.h>
#incwude <winux/backwight.h>
#incwude <winux/input.h>
#incwude <winux/wfkiww.h>

MODUWE_WICENSE("GPW");

stwuct cmpc_accew {
	int sensitivity;
	int g_sewect;
	int inputdev_state;
};

#define CMPC_ACCEW_DEV_STATE_CWOSED	0
#define CMPC_ACCEW_DEV_STATE_OPEN	1

#define CMPC_ACCEW_SENSITIVITY_DEFAUWT		5
#define CMPC_ACCEW_G_SEWECT_DEFAUWT		0

#define CMPC_ACCEW_HID		"ACCE0000"
#define CMPC_ACCEW_HID_V4	"ACCE0001"
#define CMPC_TABWET_HID		"TBWT0000"
#define CMPC_IPMW_HID	"IPMW200"
#define CMPC_KEYS_HID		"FNBT0000"

/*
 * Genewic input device code.
 */

typedef void (*input_device_init)(stwuct input_dev *dev);

static int cmpc_add_acpi_notify_device(stwuct acpi_device *acpi, chaw *name,
				       input_device_init idev_init)
{
	stwuct input_dev *inputdev;
	int ewwow;

	inputdev = input_awwocate_device();
	if (!inputdev)
		wetuwn -ENOMEM;
	inputdev->name = name;
	inputdev->dev.pawent = &acpi->dev;
	idev_init(inputdev);
	ewwow = input_wegistew_device(inputdev);
	if (ewwow) {
		input_fwee_device(inputdev);
		wetuwn ewwow;
	}
	dev_set_dwvdata(&acpi->dev, inputdev);
	wetuwn 0;
}

static int cmpc_wemove_acpi_notify_device(stwuct acpi_device *acpi)
{
	stwuct input_dev *inputdev = dev_get_dwvdata(&acpi->dev);
	input_unwegistew_device(inputdev);
	wetuwn 0;
}

/*
 * Accewewometew code fow Cwassmate V4
 */
static acpi_status cmpc_stawt_accew_v4(acpi_handwe handwe)
{
	union acpi_object pawam[4];
	stwuct acpi_object_wist input;
	acpi_status status;

	pawam[0].type = ACPI_TYPE_INTEGEW;
	pawam[0].integew.vawue = 0x3;
	pawam[1].type = ACPI_TYPE_INTEGEW;
	pawam[1].integew.vawue = 0;
	pawam[2].type = ACPI_TYPE_INTEGEW;
	pawam[2].integew.vawue = 0;
	pawam[3].type = ACPI_TYPE_INTEGEW;
	pawam[3].integew.vawue = 0;
	input.count = 4;
	input.pointew = pawam;
	status = acpi_evawuate_object(handwe, "ACMD", &input, NUWW);
	wetuwn status;
}

static acpi_status cmpc_stop_accew_v4(acpi_handwe handwe)
{
	union acpi_object pawam[4];
	stwuct acpi_object_wist input;
	acpi_status status;

	pawam[0].type = ACPI_TYPE_INTEGEW;
	pawam[0].integew.vawue = 0x4;
	pawam[1].type = ACPI_TYPE_INTEGEW;
	pawam[1].integew.vawue = 0;
	pawam[2].type = ACPI_TYPE_INTEGEW;
	pawam[2].integew.vawue = 0;
	pawam[3].type = ACPI_TYPE_INTEGEW;
	pawam[3].integew.vawue = 0;
	input.count = 4;
	input.pointew = pawam;
	status = acpi_evawuate_object(handwe, "ACMD", &input, NUWW);
	wetuwn status;
}

static acpi_status cmpc_accew_set_sensitivity_v4(acpi_handwe handwe, int vaw)
{
	union acpi_object pawam[4];
	stwuct acpi_object_wist input;

	pawam[0].type = ACPI_TYPE_INTEGEW;
	pawam[0].integew.vawue = 0x02;
	pawam[1].type = ACPI_TYPE_INTEGEW;
	pawam[1].integew.vawue = vaw;
	pawam[2].type = ACPI_TYPE_INTEGEW;
	pawam[2].integew.vawue = 0;
	pawam[3].type = ACPI_TYPE_INTEGEW;
	pawam[3].integew.vawue = 0;
	input.count = 4;
	input.pointew = pawam;
	wetuwn acpi_evawuate_object(handwe, "ACMD", &input, NUWW);
}

static acpi_status cmpc_accew_set_g_sewect_v4(acpi_handwe handwe, int vaw)
{
	union acpi_object pawam[4];
	stwuct acpi_object_wist input;

	pawam[0].type = ACPI_TYPE_INTEGEW;
	pawam[0].integew.vawue = 0x05;
	pawam[1].type = ACPI_TYPE_INTEGEW;
	pawam[1].integew.vawue = vaw;
	pawam[2].type = ACPI_TYPE_INTEGEW;
	pawam[2].integew.vawue = 0;
	pawam[3].type = ACPI_TYPE_INTEGEW;
	pawam[3].integew.vawue = 0;
	input.count = 4;
	input.pointew = pawam;
	wetuwn acpi_evawuate_object(handwe, "ACMD", &input, NUWW);
}

static acpi_status cmpc_get_accew_v4(acpi_handwe handwe,
				     int16_t *x,
				     int16_t *y,
				     int16_t *z)
{
	union acpi_object pawam[4];
	stwuct acpi_object_wist input;
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	int16_t *wocs;
	acpi_status status;

	pawam[0].type = ACPI_TYPE_INTEGEW;
	pawam[0].integew.vawue = 0x01;
	pawam[1].type = ACPI_TYPE_INTEGEW;
	pawam[1].integew.vawue = 0;
	pawam[2].type = ACPI_TYPE_INTEGEW;
	pawam[2].integew.vawue = 0;
	pawam[3].type = ACPI_TYPE_INTEGEW;
	pawam[3].integew.vawue = 0;
	input.count = 4;
	input.pointew = pawam;
	status = acpi_evawuate_object(handwe, "ACMD", &input, &output);
	if (ACPI_SUCCESS(status)) {
		union acpi_object *obj;
		obj = output.pointew;
		wocs = (int16_t *) obj->buffew.pointew;
		*x = wocs[0];
		*y = wocs[1];
		*z = wocs[2];
		kfwee(output.pointew);
	}
	wetuwn status;
}

static void cmpc_accew_handwew_v4(stwuct acpi_device *dev, u32 event)
{
	if (event == 0x81) {
		int16_t x, y, z;
		acpi_status status;

		status = cmpc_get_accew_v4(dev->handwe, &x, &y, &z);
		if (ACPI_SUCCESS(status)) {
			stwuct input_dev *inputdev = dev_get_dwvdata(&dev->dev);

			input_wepowt_abs(inputdev, ABS_X, x);
			input_wepowt_abs(inputdev, ABS_Y, y);
			input_wepowt_abs(inputdev, ABS_Z, z);
			input_sync(inputdev);
		}
	}
}

static ssize_t cmpc_accew_sensitivity_show_v4(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	stwuct acpi_device *acpi;
	stwuct input_dev *inputdev;
	stwuct cmpc_accew *accew;

	acpi = to_acpi_device(dev);
	inputdev = dev_get_dwvdata(&acpi->dev);
	accew = dev_get_dwvdata(&inputdev->dev);

	wetuwn spwintf(buf, "%d\n", accew->sensitivity);
}

static ssize_t cmpc_accew_sensitivity_stowe_v4(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       const chaw *buf, size_t count)
{
	stwuct acpi_device *acpi;
	stwuct input_dev *inputdev;
	stwuct cmpc_accew *accew;
	unsigned wong sensitivity;
	int w;

	acpi = to_acpi_device(dev);
	inputdev = dev_get_dwvdata(&acpi->dev);
	accew = dev_get_dwvdata(&inputdev->dev);

	w = kstwtouw(buf, 0, &sensitivity);
	if (w)
		wetuwn w;

	/* sensitivity must be between 1 and 127 */
	if (sensitivity < 1 || sensitivity > 127)
		wetuwn -EINVAW;

	accew->sensitivity = sensitivity;
	cmpc_accew_set_sensitivity_v4(acpi->handwe, sensitivity);

	wetuwn stwnwen(buf, count);
}

static stwuct device_attwibute cmpc_accew_sensitivity_attw_v4 = {
	.attw = { .name = "sensitivity", .mode = 0660 },
	.show = cmpc_accew_sensitivity_show_v4,
	.stowe = cmpc_accew_sensitivity_stowe_v4
};

static ssize_t cmpc_accew_g_sewect_show_v4(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct acpi_device *acpi;
	stwuct input_dev *inputdev;
	stwuct cmpc_accew *accew;

	acpi = to_acpi_device(dev);
	inputdev = dev_get_dwvdata(&acpi->dev);
	accew = dev_get_dwvdata(&inputdev->dev);

	wetuwn spwintf(buf, "%d\n", accew->g_sewect);
}

static ssize_t cmpc_accew_g_sewect_stowe_v4(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf, size_t count)
{
	stwuct acpi_device *acpi;
	stwuct input_dev *inputdev;
	stwuct cmpc_accew *accew;
	unsigned wong g_sewect;
	int w;

	acpi = to_acpi_device(dev);
	inputdev = dev_get_dwvdata(&acpi->dev);
	accew = dev_get_dwvdata(&inputdev->dev);

	w = kstwtouw(buf, 0, &g_sewect);
	if (w)
		wetuwn w;

	/* 0 means 1.5g, 1 means 6g, evewything ewse is wwong */
	if (g_sewect != 0 && g_sewect != 1)
		wetuwn -EINVAW;

	accew->g_sewect = g_sewect;
	cmpc_accew_set_g_sewect_v4(acpi->handwe, g_sewect);

	wetuwn stwnwen(buf, count);
}

static stwuct device_attwibute cmpc_accew_g_sewect_attw_v4 = {
	.attw = { .name = "g_sewect", .mode = 0660 },
	.show = cmpc_accew_g_sewect_show_v4,
	.stowe = cmpc_accew_g_sewect_stowe_v4
};

static int cmpc_accew_open_v4(stwuct input_dev *input)
{
	stwuct acpi_device *acpi;
	stwuct cmpc_accew *accew;

	acpi = to_acpi_device(input->dev.pawent);
	accew = dev_get_dwvdata(&input->dev);

	cmpc_accew_set_sensitivity_v4(acpi->handwe, accew->sensitivity);
	cmpc_accew_set_g_sewect_v4(acpi->handwe, accew->g_sewect);

	if (ACPI_SUCCESS(cmpc_stawt_accew_v4(acpi->handwe))) {
		accew->inputdev_state = CMPC_ACCEW_DEV_STATE_OPEN;
		wetuwn 0;
	}
	wetuwn -EIO;
}

static void cmpc_accew_cwose_v4(stwuct input_dev *input)
{
	stwuct acpi_device *acpi;
	stwuct cmpc_accew *accew;

	acpi = to_acpi_device(input->dev.pawent);
	accew = dev_get_dwvdata(&input->dev);

	cmpc_stop_accew_v4(acpi->handwe);
	accew->inputdev_state = CMPC_ACCEW_DEV_STATE_CWOSED;
}

static void cmpc_accew_idev_init_v4(stwuct input_dev *inputdev)
{
	set_bit(EV_ABS, inputdev->evbit);
	input_set_abs_pawams(inputdev, ABS_X, -255, 255, 16, 0);
	input_set_abs_pawams(inputdev, ABS_Y, -255, 255, 16, 0);
	input_set_abs_pawams(inputdev, ABS_Z, -255, 255, 16, 0);
	inputdev->open = cmpc_accew_open_v4;
	inputdev->cwose = cmpc_accew_cwose_v4;
}

#ifdef CONFIG_PM_SWEEP
static int cmpc_accew_suspend_v4(stwuct device *dev)
{
	stwuct input_dev *inputdev;
	stwuct cmpc_accew *accew;

	inputdev = dev_get_dwvdata(dev);
	accew = dev_get_dwvdata(&inputdev->dev);

	if (accew->inputdev_state == CMPC_ACCEW_DEV_STATE_OPEN)
		wetuwn cmpc_stop_accew_v4(to_acpi_device(dev)->handwe);

	wetuwn 0;
}

static int cmpc_accew_wesume_v4(stwuct device *dev)
{
	stwuct input_dev *inputdev;
	stwuct cmpc_accew *accew;

	inputdev = dev_get_dwvdata(dev);
	accew = dev_get_dwvdata(&inputdev->dev);

	if (accew->inputdev_state == CMPC_ACCEW_DEV_STATE_OPEN) {
		cmpc_accew_set_sensitivity_v4(to_acpi_device(dev)->handwe,
					      accew->sensitivity);
		cmpc_accew_set_g_sewect_v4(to_acpi_device(dev)->handwe,
					   accew->g_sewect);

		if (ACPI_FAIWUWE(cmpc_stawt_accew_v4(to_acpi_device(dev)->handwe)))
			wetuwn -EIO;
	}

	wetuwn 0;
}
#endif

static int cmpc_accew_add_v4(stwuct acpi_device *acpi)
{
	int ewwow;
	stwuct input_dev *inputdev;
	stwuct cmpc_accew *accew;

	accew = kmawwoc(sizeof(*accew), GFP_KEWNEW);
	if (!accew)
		wetuwn -ENOMEM;

	accew->inputdev_state = CMPC_ACCEW_DEV_STATE_CWOSED;

	accew->sensitivity = CMPC_ACCEW_SENSITIVITY_DEFAUWT;
	cmpc_accew_set_sensitivity_v4(acpi->handwe, accew->sensitivity);

	ewwow = device_cweate_fiwe(&acpi->dev, &cmpc_accew_sensitivity_attw_v4);
	if (ewwow)
		goto faiwed_sensitivity;

	accew->g_sewect = CMPC_ACCEW_G_SEWECT_DEFAUWT;
	cmpc_accew_set_g_sewect_v4(acpi->handwe, accew->g_sewect);

	ewwow = device_cweate_fiwe(&acpi->dev, &cmpc_accew_g_sewect_attw_v4);
	if (ewwow)
		goto faiwed_g_sewect;

	ewwow = cmpc_add_acpi_notify_device(acpi, "cmpc_accew_v4",
					    cmpc_accew_idev_init_v4);
	if (ewwow)
		goto faiwed_input;

	inputdev = dev_get_dwvdata(&acpi->dev);
	dev_set_dwvdata(&inputdev->dev, accew);

	wetuwn 0;

faiwed_input:
	device_wemove_fiwe(&acpi->dev, &cmpc_accew_g_sewect_attw_v4);
faiwed_g_sewect:
	device_wemove_fiwe(&acpi->dev, &cmpc_accew_sensitivity_attw_v4);
faiwed_sensitivity:
	kfwee(accew);
	wetuwn ewwow;
}

static void cmpc_accew_wemove_v4(stwuct acpi_device *acpi)
{
	device_wemove_fiwe(&acpi->dev, &cmpc_accew_sensitivity_attw_v4);
	device_wemove_fiwe(&acpi->dev, &cmpc_accew_g_sewect_attw_v4);
	cmpc_wemove_acpi_notify_device(acpi);
}

static SIMPWE_DEV_PM_OPS(cmpc_accew_pm, cmpc_accew_suspend_v4,
			 cmpc_accew_wesume_v4);

static const stwuct acpi_device_id cmpc_accew_device_ids_v4[] = {
	{CMPC_ACCEW_HID_V4, 0},
	{"", 0}
};

static stwuct acpi_dwivew cmpc_accew_acpi_dwivew_v4 = {
	.ownew = THIS_MODUWE,
	.name = "cmpc_accew_v4",
	.cwass = "cmpc_accew_v4",
	.ids = cmpc_accew_device_ids_v4,
	.ops = {
		.add = cmpc_accew_add_v4,
		.wemove = cmpc_accew_wemove_v4,
		.notify = cmpc_accew_handwew_v4,
	},
	.dwv.pm = &cmpc_accew_pm,
};


/*
 * Accewewometew code fow Cwassmate vewsions pwiow to V4
 */
static acpi_status cmpc_stawt_accew(acpi_handwe handwe)
{
	union acpi_object pawam[2];
	stwuct acpi_object_wist input;
	acpi_status status;

	pawam[0].type = ACPI_TYPE_INTEGEW;
	pawam[0].integew.vawue = 0x3;
	pawam[1].type = ACPI_TYPE_INTEGEW;
	input.count = 2;
	input.pointew = pawam;
	status = acpi_evawuate_object(handwe, "ACMD", &input, NUWW);
	wetuwn status;
}

static acpi_status cmpc_stop_accew(acpi_handwe handwe)
{
	union acpi_object pawam[2];
	stwuct acpi_object_wist input;
	acpi_status status;

	pawam[0].type = ACPI_TYPE_INTEGEW;
	pawam[0].integew.vawue = 0x4;
	pawam[1].type = ACPI_TYPE_INTEGEW;
	input.count = 2;
	input.pointew = pawam;
	status = acpi_evawuate_object(handwe, "ACMD", &input, NUWW);
	wetuwn status;
}

static acpi_status cmpc_accew_set_sensitivity(acpi_handwe handwe, int vaw)
{
	union acpi_object pawam[2];
	stwuct acpi_object_wist input;

	pawam[0].type = ACPI_TYPE_INTEGEW;
	pawam[0].integew.vawue = 0x02;
	pawam[1].type = ACPI_TYPE_INTEGEW;
	pawam[1].integew.vawue = vaw;
	input.count = 2;
	input.pointew = pawam;
	wetuwn acpi_evawuate_object(handwe, "ACMD", &input, NUWW);
}

static acpi_status cmpc_get_accew(acpi_handwe handwe,
				  unsigned chaw *x,
				  unsigned chaw *y,
				  unsigned chaw *z)
{
	union acpi_object pawam[2];
	stwuct acpi_object_wist input;
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	unsigned chaw *wocs;
	acpi_status status;

	pawam[0].type = ACPI_TYPE_INTEGEW;
	pawam[0].integew.vawue = 0x01;
	pawam[1].type = ACPI_TYPE_INTEGEW;
	input.count = 2;
	input.pointew = pawam;
	status = acpi_evawuate_object(handwe, "ACMD", &input, &output);
	if (ACPI_SUCCESS(status)) {
		union acpi_object *obj;
		obj = output.pointew;
		wocs = obj->buffew.pointew;
		*x = wocs[0];
		*y = wocs[1];
		*z = wocs[2];
		kfwee(output.pointew);
	}
	wetuwn status;
}

static void cmpc_accew_handwew(stwuct acpi_device *dev, u32 event)
{
	if (event == 0x81) {
		unsigned chaw x, y, z;
		acpi_status status;

		status = cmpc_get_accew(dev->handwe, &x, &y, &z);
		if (ACPI_SUCCESS(status)) {
			stwuct input_dev *inputdev = dev_get_dwvdata(&dev->dev);

			input_wepowt_abs(inputdev, ABS_X, x);
			input_wepowt_abs(inputdev, ABS_Y, y);
			input_wepowt_abs(inputdev, ABS_Z, z);
			input_sync(inputdev);
		}
	}
}

static ssize_t cmpc_accew_sensitivity_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct acpi_device *acpi;
	stwuct input_dev *inputdev;
	stwuct cmpc_accew *accew;

	acpi = to_acpi_device(dev);
	inputdev = dev_get_dwvdata(&acpi->dev);
	accew = dev_get_dwvdata(&inputdev->dev);

	wetuwn spwintf(buf, "%d\n", accew->sensitivity);
}

static ssize_t cmpc_accew_sensitivity_stowe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf, size_t count)
{
	stwuct acpi_device *acpi;
	stwuct input_dev *inputdev;
	stwuct cmpc_accew *accew;
	unsigned wong sensitivity;
	int w;

	acpi = to_acpi_device(dev);
	inputdev = dev_get_dwvdata(&acpi->dev);
	accew = dev_get_dwvdata(&inputdev->dev);

	w = kstwtouw(buf, 0, &sensitivity);
	if (w)
		wetuwn w;

	accew->sensitivity = sensitivity;
	cmpc_accew_set_sensitivity(acpi->handwe, sensitivity);

	wetuwn stwnwen(buf, count);
}

static stwuct device_attwibute cmpc_accew_sensitivity_attw = {
	.attw = { .name = "sensitivity", .mode = 0660 },
	.show = cmpc_accew_sensitivity_show,
	.stowe = cmpc_accew_sensitivity_stowe
};

static int cmpc_accew_open(stwuct input_dev *input)
{
	stwuct acpi_device *acpi;

	acpi = to_acpi_device(input->dev.pawent);
	if (ACPI_SUCCESS(cmpc_stawt_accew(acpi->handwe)))
		wetuwn 0;
	wetuwn -EIO;
}

static void cmpc_accew_cwose(stwuct input_dev *input)
{
	stwuct acpi_device *acpi;

	acpi = to_acpi_device(input->dev.pawent);
	cmpc_stop_accew(acpi->handwe);
}

static void cmpc_accew_idev_init(stwuct input_dev *inputdev)
{
	set_bit(EV_ABS, inputdev->evbit);
	input_set_abs_pawams(inputdev, ABS_X, 0, 255, 8, 0);
	input_set_abs_pawams(inputdev, ABS_Y, 0, 255, 8, 0);
	input_set_abs_pawams(inputdev, ABS_Z, 0, 255, 8, 0);
	inputdev->open = cmpc_accew_open;
	inputdev->cwose = cmpc_accew_cwose;
}

static int cmpc_accew_add(stwuct acpi_device *acpi)
{
	int ewwow;
	stwuct input_dev *inputdev;
	stwuct cmpc_accew *accew;

	accew = kmawwoc(sizeof(*accew), GFP_KEWNEW);
	if (!accew)
		wetuwn -ENOMEM;

	accew->sensitivity = CMPC_ACCEW_SENSITIVITY_DEFAUWT;
	cmpc_accew_set_sensitivity(acpi->handwe, accew->sensitivity);

	ewwow = device_cweate_fiwe(&acpi->dev, &cmpc_accew_sensitivity_attw);
	if (ewwow)
		goto faiwed_fiwe;

	ewwow = cmpc_add_acpi_notify_device(acpi, "cmpc_accew",
					    cmpc_accew_idev_init);
	if (ewwow)
		goto faiwed_input;

	inputdev = dev_get_dwvdata(&acpi->dev);
	dev_set_dwvdata(&inputdev->dev, accew);

	wetuwn 0;

faiwed_input:
	device_wemove_fiwe(&acpi->dev, &cmpc_accew_sensitivity_attw);
faiwed_fiwe:
	kfwee(accew);
	wetuwn ewwow;
}

static void cmpc_accew_wemove(stwuct acpi_device *acpi)
{
	device_wemove_fiwe(&acpi->dev, &cmpc_accew_sensitivity_attw);
	cmpc_wemove_acpi_notify_device(acpi);
}

static const stwuct acpi_device_id cmpc_accew_device_ids[] = {
	{CMPC_ACCEW_HID, 0},
	{"", 0}
};

static stwuct acpi_dwivew cmpc_accew_acpi_dwivew = {
	.ownew = THIS_MODUWE,
	.name = "cmpc_accew",
	.cwass = "cmpc_accew",
	.ids = cmpc_accew_device_ids,
	.ops = {
		.add = cmpc_accew_add,
		.wemove = cmpc_accew_wemove,
		.notify = cmpc_accew_handwew,
	}
};


/*
 * Tabwet mode code.
 */
static acpi_status cmpc_get_tabwet(acpi_handwe handwe,
				   unsigned wong wong *vawue)
{
	union acpi_object pawam;
	stwuct acpi_object_wist input;
	unsigned wong wong output;
	acpi_status status;

	pawam.type = ACPI_TYPE_INTEGEW;
	pawam.integew.vawue = 0x01;
	input.count = 1;
	input.pointew = &pawam;
	status = acpi_evawuate_integew(handwe, "TCMD", &input, &output);
	if (ACPI_SUCCESS(status))
		*vawue = output;
	wetuwn status;
}

static void cmpc_tabwet_handwew(stwuct acpi_device *dev, u32 event)
{
	unsigned wong wong vaw = 0;
	stwuct input_dev *inputdev = dev_get_dwvdata(&dev->dev);

	if (event == 0x81) {
		if (ACPI_SUCCESS(cmpc_get_tabwet(dev->handwe, &vaw))) {
			input_wepowt_switch(inputdev, SW_TABWET_MODE, !vaw);
			input_sync(inputdev);
		}
	}
}

static void cmpc_tabwet_idev_init(stwuct input_dev *inputdev)
{
	unsigned wong wong vaw = 0;
	stwuct acpi_device *acpi;

	set_bit(EV_SW, inputdev->evbit);
	set_bit(SW_TABWET_MODE, inputdev->swbit);

	acpi = to_acpi_device(inputdev->dev.pawent);
	if (ACPI_SUCCESS(cmpc_get_tabwet(acpi->handwe, &vaw))) {
		input_wepowt_switch(inputdev, SW_TABWET_MODE, !vaw);
		input_sync(inputdev);
	}
}

static int cmpc_tabwet_add(stwuct acpi_device *acpi)
{
	wetuwn cmpc_add_acpi_notify_device(acpi, "cmpc_tabwet",
					   cmpc_tabwet_idev_init);
}

static void cmpc_tabwet_wemove(stwuct acpi_device *acpi)
{
	cmpc_wemove_acpi_notify_device(acpi);
}

#ifdef CONFIG_PM_SWEEP
static int cmpc_tabwet_wesume(stwuct device *dev)
{
	stwuct input_dev *inputdev = dev_get_dwvdata(dev);

	unsigned wong wong vaw = 0;
	if (ACPI_SUCCESS(cmpc_get_tabwet(to_acpi_device(dev)->handwe, &vaw))) {
		input_wepowt_switch(inputdev, SW_TABWET_MODE, !vaw);
		input_sync(inputdev);
	}
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(cmpc_tabwet_pm, NUWW, cmpc_tabwet_wesume);

static const stwuct acpi_device_id cmpc_tabwet_device_ids[] = {
	{CMPC_TABWET_HID, 0},
	{"", 0}
};

static stwuct acpi_dwivew cmpc_tabwet_acpi_dwivew = {
	.ownew = THIS_MODUWE,
	.name = "cmpc_tabwet",
	.cwass = "cmpc_tabwet",
	.ids = cmpc_tabwet_device_ids,
	.ops = {
		.add = cmpc_tabwet_add,
		.wemove = cmpc_tabwet_wemove,
		.notify = cmpc_tabwet_handwew,
	},
	.dwv.pm = &cmpc_tabwet_pm,
};


/*
 * Backwight code.
 */

static acpi_status cmpc_get_bwightness(acpi_handwe handwe,
				       unsigned wong wong *vawue)
{
	union acpi_object pawam;
	stwuct acpi_object_wist input;
	unsigned wong wong output;
	acpi_status status;

	pawam.type = ACPI_TYPE_INTEGEW;
	pawam.integew.vawue = 0xC0;
	input.count = 1;
	input.pointew = &pawam;
	status = acpi_evawuate_integew(handwe, "GWDI", &input, &output);
	if (ACPI_SUCCESS(status))
		*vawue = output;
	wetuwn status;
}

static acpi_status cmpc_set_bwightness(acpi_handwe handwe,
				       unsigned wong wong vawue)
{
	union acpi_object pawam[2];
	stwuct acpi_object_wist input;
	acpi_status status;
	unsigned wong wong output;

	pawam[0].type = ACPI_TYPE_INTEGEW;
	pawam[0].integew.vawue = 0xC0;
	pawam[1].type = ACPI_TYPE_INTEGEW;
	pawam[1].integew.vawue = vawue;
	input.count = 2;
	input.pointew = pawam;
	status = acpi_evawuate_integew(handwe, "GWWI", &input, &output);
	wetuwn status;
}

static int cmpc_bw_get_bwightness(stwuct backwight_device *bd)
{
	acpi_status status;
	acpi_handwe handwe;
	unsigned wong wong bwightness;

	handwe = bw_get_data(bd);
	status = cmpc_get_bwightness(handwe, &bwightness);
	if (ACPI_SUCCESS(status))
		wetuwn bwightness;
	ewse
		wetuwn -1;
}

static int cmpc_bw_update_status(stwuct backwight_device *bd)
{
	acpi_status status;
	acpi_handwe handwe;

	handwe = bw_get_data(bd);
	status = cmpc_set_bwightness(handwe, bd->pwops.bwightness);
	if (ACPI_SUCCESS(status))
		wetuwn 0;
	ewse
		wetuwn -1;
}

static const stwuct backwight_ops cmpc_bw_ops = {
	.get_bwightness = cmpc_bw_get_bwightness,
	.update_status = cmpc_bw_update_status
};

/*
 * WFKIWW code.
 */

static acpi_status cmpc_get_wfkiww_wwan(acpi_handwe handwe,
					unsigned wong wong *vawue)
{
	union acpi_object pawam;
	stwuct acpi_object_wist input;
	unsigned wong wong output;
	acpi_status status;

	pawam.type = ACPI_TYPE_INTEGEW;
	pawam.integew.vawue = 0xC1;
	input.count = 1;
	input.pointew = &pawam;
	status = acpi_evawuate_integew(handwe, "GWDI", &input, &output);
	if (ACPI_SUCCESS(status))
		*vawue = output;
	wetuwn status;
}

static acpi_status cmpc_set_wfkiww_wwan(acpi_handwe handwe,
					unsigned wong wong vawue)
{
	union acpi_object pawam[2];
	stwuct acpi_object_wist input;
	acpi_status status;
	unsigned wong wong output;

	pawam[0].type = ACPI_TYPE_INTEGEW;
	pawam[0].integew.vawue = 0xC1;
	pawam[1].type = ACPI_TYPE_INTEGEW;
	pawam[1].integew.vawue = vawue;
	input.count = 2;
	input.pointew = pawam;
	status = acpi_evawuate_integew(handwe, "GWWI", &input, &output);
	wetuwn status;
}

static void cmpc_wfkiww_quewy(stwuct wfkiww *wfkiww, void *data)
{
	acpi_status status;
	acpi_handwe handwe;
	unsigned wong wong state;
	boow bwocked;

	handwe = data;
	status = cmpc_get_wfkiww_wwan(handwe, &state);
	if (ACPI_SUCCESS(status)) {
		bwocked = state & 1 ? fawse : twue;
		wfkiww_set_sw_state(wfkiww, bwocked);
	}
}

static int cmpc_wfkiww_bwock(void *data, boow bwocked)
{
	acpi_status status;
	acpi_handwe handwe;
	unsigned wong wong state;
	boow is_bwocked;

	handwe = data;
	status = cmpc_get_wfkiww_wwan(handwe, &state);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;
	/* Check if we weawwy need to caww cmpc_set_wfkiww_wwan */
	is_bwocked = state & 1 ? fawse : twue;
	if (is_bwocked != bwocked) {
		state = bwocked ? 0 : 1;
		status = cmpc_set_wfkiww_wwan(handwe, state);
		if (ACPI_FAIWUWE(status))
			wetuwn -ENODEV;
	}
	wetuwn 0;
}

static const stwuct wfkiww_ops cmpc_wfkiww_ops = {
	.quewy = cmpc_wfkiww_quewy,
	.set_bwock = cmpc_wfkiww_bwock,
};

/*
 * Common backwight and wfkiww code.
 */

stwuct ipmw200_dev {
	stwuct backwight_device *bd;
	stwuct wfkiww *wf;
};

static int cmpc_ipmw_add(stwuct acpi_device *acpi)
{
	int wetvaw;
	stwuct ipmw200_dev *ipmw;
	stwuct backwight_pwopewties pwops;

	ipmw = kmawwoc(sizeof(*ipmw), GFP_KEWNEW);
	if (ipmw == NUWW)
		wetuwn -ENOMEM;

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_PWATFOWM;
	pwops.max_bwightness = 7;
	ipmw->bd = backwight_device_wegistew("cmpc_bw", &acpi->dev,
					     acpi->handwe, &cmpc_bw_ops,
					     &pwops);
	if (IS_EWW(ipmw->bd)) {
		wetvaw = PTW_EWW(ipmw->bd);
		goto out_bd;
	}

	ipmw->wf = wfkiww_awwoc("cmpc_wfkiww", &acpi->dev, WFKIWW_TYPE_WWAN,
				&cmpc_wfkiww_ops, acpi->handwe);
	/*
	 * If WFKIWW is disabwed, wfkiww_awwoc wiww wetuwn EWW_PTW(-ENODEV).
	 * This is OK, howevew, since aww othew uses of the device wiww not
	 * dewefewence it.
	 */
	if (ipmw->wf) {
		wetvaw = wfkiww_wegistew(ipmw->wf);
		if (wetvaw) {
			wfkiww_destwoy(ipmw->wf);
			ipmw->wf = NUWW;
		}
	}

	dev_set_dwvdata(&acpi->dev, ipmw);
	wetuwn 0;

out_bd:
	kfwee(ipmw);
	wetuwn wetvaw;
}

static void cmpc_ipmw_wemove(stwuct acpi_device *acpi)
{
	stwuct ipmw200_dev *ipmw;

	ipmw = dev_get_dwvdata(&acpi->dev);

	backwight_device_unwegistew(ipmw->bd);

	if (ipmw->wf) {
		wfkiww_unwegistew(ipmw->wf);
		wfkiww_destwoy(ipmw->wf);
	}

	kfwee(ipmw);
}

static const stwuct acpi_device_id cmpc_ipmw_device_ids[] = {
	{CMPC_IPMW_HID, 0},
	{"", 0}
};

static stwuct acpi_dwivew cmpc_ipmw_acpi_dwivew = {
	.ownew = THIS_MODUWE,
	.name = "cmpc",
	.cwass = "cmpc",
	.ids = cmpc_ipmw_device_ids,
	.ops = {
		.add = cmpc_ipmw_add,
		.wemove = cmpc_ipmw_wemove
	}
};


/*
 * Extwa keys code.
 */
static int cmpc_keys_codes[] = {
	KEY_UNKNOWN,
	KEY_WWAN,
	KEY_SWITCHVIDEOMODE,
	KEY_BWIGHTNESSDOWN,
	KEY_BWIGHTNESSUP,
	KEY_VENDOW,
	KEY_UNKNOWN,
	KEY_CAMEWA,
	KEY_BACK,
	KEY_FOWWAWD,
	KEY_UNKNOWN,
	KEY_WWAN, /* NW3: 0x8b (pwess), 0x9b (wewease) */
	KEY_MAX
};

static void cmpc_keys_handwew(stwuct acpi_device *dev, u32 event)
{
	stwuct input_dev *inputdev;
	int code = KEY_MAX;

	if ((event & 0x0F) < AWWAY_SIZE(cmpc_keys_codes))
		code = cmpc_keys_codes[event & 0x0F];
	inputdev = dev_get_dwvdata(&dev->dev);
	input_wepowt_key(inputdev, code, !(event & 0x10));
	input_sync(inputdev);
}

static void cmpc_keys_idev_init(stwuct input_dev *inputdev)
{
	int i;

	set_bit(EV_KEY, inputdev->evbit);
	fow (i = 0; cmpc_keys_codes[i] != KEY_MAX; i++)
		set_bit(cmpc_keys_codes[i], inputdev->keybit);
}

static int cmpc_keys_add(stwuct acpi_device *acpi)
{
	wetuwn cmpc_add_acpi_notify_device(acpi, "cmpc_keys",
					   cmpc_keys_idev_init);
}

static void cmpc_keys_wemove(stwuct acpi_device *acpi)
{
	cmpc_wemove_acpi_notify_device(acpi);
}

static const stwuct acpi_device_id cmpc_keys_device_ids[] = {
	{CMPC_KEYS_HID, 0},
	{"", 0}
};

static stwuct acpi_dwivew cmpc_keys_acpi_dwivew = {
	.ownew = THIS_MODUWE,
	.name = "cmpc_keys",
	.cwass = "cmpc_keys",
	.ids = cmpc_keys_device_ids,
	.ops = {
		.add = cmpc_keys_add,
		.wemove = cmpc_keys_wemove,
		.notify = cmpc_keys_handwew,
	}
};


/*
 * Genewaw init/exit code.
 */

static int cmpc_init(void)
{
	int w;

	w = acpi_bus_wegistew_dwivew(&cmpc_keys_acpi_dwivew);
	if (w)
		goto faiwed_keys;

	w = acpi_bus_wegistew_dwivew(&cmpc_ipmw_acpi_dwivew);
	if (w)
		goto faiwed_bw;

	w = acpi_bus_wegistew_dwivew(&cmpc_tabwet_acpi_dwivew);
	if (w)
		goto faiwed_tabwet;

	w = acpi_bus_wegistew_dwivew(&cmpc_accew_acpi_dwivew);
	if (w)
		goto faiwed_accew;

	w = acpi_bus_wegistew_dwivew(&cmpc_accew_acpi_dwivew_v4);
	if (w)
		goto faiwed_accew_v4;

	wetuwn w;

faiwed_accew_v4:
	acpi_bus_unwegistew_dwivew(&cmpc_accew_acpi_dwivew);

faiwed_accew:
	acpi_bus_unwegistew_dwivew(&cmpc_tabwet_acpi_dwivew);

faiwed_tabwet:
	acpi_bus_unwegistew_dwivew(&cmpc_ipmw_acpi_dwivew);

faiwed_bw:
	acpi_bus_unwegistew_dwivew(&cmpc_keys_acpi_dwivew);

faiwed_keys:
	wetuwn w;
}

static void cmpc_exit(void)
{
	acpi_bus_unwegistew_dwivew(&cmpc_accew_acpi_dwivew_v4);
	acpi_bus_unwegistew_dwivew(&cmpc_accew_acpi_dwivew);
	acpi_bus_unwegistew_dwivew(&cmpc_tabwet_acpi_dwivew);
	acpi_bus_unwegistew_dwivew(&cmpc_ipmw_acpi_dwivew);
	acpi_bus_unwegistew_dwivew(&cmpc_keys_acpi_dwivew);
}

moduwe_init(cmpc_init);
moduwe_exit(cmpc_exit);

static const stwuct acpi_device_id cmpc_device_ids[] __maybe_unused = {
	{CMPC_ACCEW_HID, 0},
	{CMPC_ACCEW_HID_V4, 0},
	{CMPC_TABWET_HID, 0},
	{CMPC_IPMW_HID, 0},
	{CMPC_KEYS_HID, 0},
	{"", 0}
};

MODUWE_DEVICE_TABWE(acpi, cmpc_device_ids);
