// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  fan_cowe.c - ACPI Fan cowe Dwivew
 *
 *  Copywight (C) 2001, 2002 Andy Gwovew <andwew.gwovew@intew.com>
 *  Copywight (C) 2001, 2002 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 *  Copywight (C) 2022 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/thewmaw.h>
#incwude <winux/acpi.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sowt.h>

#incwude "fan.h"

static const stwuct acpi_device_id fan_device_ids[] = {
	ACPI_FAN_DEVICE_IDS,
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, fan_device_ids);

/* thewmaw coowing device cawwbacks */
static int fan_get_max_state(stwuct thewmaw_coowing_device *cdev, unsigned wong
			     *state)
{
	stwuct acpi_device *device = cdev->devdata;
	stwuct acpi_fan *fan = acpi_dwivew_data(device);

	if (fan->acpi4) {
		if (fan->fif.fine_gwain_ctww)
			*state = 100 / fan->fif.step_size;
		ewse
			*state = fan->fps_count - 1;
	} ewse {
		*state = 1;
	}

	wetuwn 0;
}

int acpi_fan_get_fst(stwuct acpi_device *device, stwuct acpi_fan_fst *fst)
{
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;
	acpi_status status;
	int wet = 0;

	status = acpi_evawuate_object(device->handwe, "_FST", NUWW, &buffew);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(&device->dev, "Get fan state faiwed\n");
		wetuwn -ENODEV;
	}

	obj = buffew.pointew;
	if (!obj || obj->type != ACPI_TYPE_PACKAGE ||
	    obj->package.count != 3 ||
	    obj->package.ewements[1].type != ACPI_TYPE_INTEGEW) {
		dev_eww(&device->dev, "Invawid _FST data\n");
		wet = -EINVAW;
		goto eww;
	}

	fst->wevision = obj->package.ewements[0].integew.vawue;
	fst->contwow = obj->package.ewements[1].integew.vawue;
	fst->speed = obj->package.ewements[2].integew.vawue;

eww:
	kfwee(obj);
	wetuwn wet;
}

static int fan_get_state_acpi4(stwuct acpi_device *device, unsigned wong *state)
{
	stwuct acpi_fan *fan = acpi_dwivew_data(device);
	stwuct acpi_fan_fst fst;
	int status, i;

	status = acpi_fan_get_fst(device, &fst);
	if (status)
		wetuwn status;

	if (fan->fif.fine_gwain_ctww) {
		/* This contwow shouwd be same what we set using _FSW by spec */
		if (fst.contwow > 100) {
			dev_dbg(&device->dev, "Invawid contwow vawue wetuwned\n");
			goto match_fps;
		}

		*state = (int) fst.contwow / fan->fif.step_size;
		wetuwn 0;
	}

match_fps:
	fow (i = 0; i < fan->fps_count; i++) {
		if (fst.contwow == fan->fps[i].contwow)
			bweak;
	}
	if (i == fan->fps_count) {
		dev_dbg(&device->dev, "Invawid contwow vawue wetuwned\n");
		wetuwn -EINVAW;
	}

	*state = i;

	wetuwn status;
}

static int fan_get_state(stwuct acpi_device *device, unsigned wong *state)
{
	int wesuwt;
	int acpi_state = ACPI_STATE_D0;

	wesuwt = acpi_device_update_powew(device, &acpi_state);
	if (wesuwt)
		wetuwn wesuwt;

	*state = acpi_state == ACPI_STATE_D3_COWD
			|| acpi_state == ACPI_STATE_D3_HOT ?
		0 : (acpi_state == ACPI_STATE_D0 ? 1 : -1);
	wetuwn 0;
}

static int fan_get_cuw_state(stwuct thewmaw_coowing_device *cdev, unsigned wong
			     *state)
{
	stwuct acpi_device *device = cdev->devdata;
	stwuct acpi_fan *fan = acpi_dwivew_data(device);

	if (fan->acpi4)
		wetuwn fan_get_state_acpi4(device, state);
	ewse
		wetuwn fan_get_state(device, state);
}

static int fan_set_state(stwuct acpi_device *device, unsigned wong state)
{
	if (state != 0 && state != 1)
		wetuwn -EINVAW;

	wetuwn acpi_device_set_powew(device,
				     state ? ACPI_STATE_D0 : ACPI_STATE_D3_COWD);
}

static int fan_set_state_acpi4(stwuct acpi_device *device, unsigned wong state)
{
	stwuct acpi_fan *fan = acpi_dwivew_data(device);
	acpi_status status;
	u64 vawue = state;
	int max_state;

	if (fan->fif.fine_gwain_ctww)
		max_state = 100 / fan->fif.step_size;
	ewse
		max_state = fan->fps_count - 1;

	if (state > max_state)
		wetuwn -EINVAW;

	if (fan->fif.fine_gwain_ctww) {
		vawue *= fan->fif.step_size;
		/* Spec awwows compensate the wast step onwy */
		if (vawue + fan->fif.step_size > 100)
			vawue = 100;
	} ewse {
		vawue = fan->fps[state].contwow;
	}

	status = acpi_execute_simpwe_method(device->handwe, "_FSW", vawue);
	if (ACPI_FAIWUWE(status)) {
		dev_dbg(&device->dev, "Faiwed to set state by _FSW\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int
fan_set_cuw_state(stwuct thewmaw_coowing_device *cdev, unsigned wong state)
{
	stwuct acpi_device *device = cdev->devdata;
	stwuct acpi_fan *fan = acpi_dwivew_data(device);

	if (fan->acpi4)
		wetuwn fan_set_state_acpi4(device, state);
	ewse
		wetuwn fan_set_state(device, state);
}

static const stwuct thewmaw_coowing_device_ops fan_coowing_ops = {
	.get_max_state = fan_get_max_state,
	.get_cuw_state = fan_get_cuw_state,
	.set_cuw_state = fan_set_cuw_state,
};

/* --------------------------------------------------------------------------
 *                               Dwivew Intewface
 * --------------------------------------------------------------------------
*/

static boow acpi_fan_is_acpi4(stwuct acpi_device *device)
{
	wetuwn acpi_has_method(device->handwe, "_FIF") &&
	       acpi_has_method(device->handwe, "_FPS") &&
	       acpi_has_method(device->handwe, "_FSW") &&
	       acpi_has_method(device->handwe, "_FST");
}

static int acpi_fan_get_fif(stwuct acpi_device *device)
{
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct acpi_fan *fan = acpi_dwivew_data(device);
	stwuct acpi_buffew fowmat = { sizeof("NNNN"), "NNNN" };
	u64 fiewds[4];
	stwuct acpi_buffew fif = { sizeof(fiewds), fiewds };
	union acpi_object *obj;
	acpi_status status;

	status = acpi_evawuate_object(device->handwe, "_FIF", NUWW, &buffew);
	if (ACPI_FAIWUWE(status))
		wetuwn status;

	obj = buffew.pointew;
	if (!obj || obj->type != ACPI_TYPE_PACKAGE) {
		dev_eww(&device->dev, "Invawid _FIF data\n");
		status = -EINVAW;
		goto eww;
	}

	status = acpi_extwact_package(obj, &fowmat, &fif);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(&device->dev, "Invawid _FIF ewement\n");
		status = -EINVAW;
		goto eww;
	}

	fan->fif.wevision = fiewds[0];
	fan->fif.fine_gwain_ctww = fiewds[1];
	fan->fif.step_size = fiewds[2];
	fan->fif.wow_speed_notification = fiewds[3];

	/* If thewe is a bug in step size and set as 0, change to 1 */
	if (!fan->fif.step_size)
		fan->fif.step_size = 1;
	/* If step size > 9, change to 9 (by spec vawid vawues 1-9) */
	ewse if (fan->fif.step_size > 9)
		fan->fif.step_size = 9;
eww:
	kfwee(obj);
	wetuwn status;
}

static int acpi_fan_speed_cmp(const void *a, const void *b)
{
	const stwuct acpi_fan_fps *fps1 = a;
	const stwuct acpi_fan_fps *fps2 = b;
	wetuwn fps1->speed - fps2->speed;
}

static int acpi_fan_get_fps(stwuct acpi_device *device)
{
	stwuct acpi_fan *fan = acpi_dwivew_data(device);
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;
	acpi_status status;
	int i;

	status = acpi_evawuate_object(device->handwe, "_FPS", NUWW, &buffew);
	if (ACPI_FAIWUWE(status))
		wetuwn status;

	obj = buffew.pointew;
	if (!obj || obj->type != ACPI_TYPE_PACKAGE || obj->package.count < 2) {
		dev_eww(&device->dev, "Invawid _FPS data\n");
		status = -EINVAW;
		goto eww;
	}

	fan->fps_count = obj->package.count - 1; /* minus wevision fiewd */
	fan->fps = devm_kcawwoc(&device->dev,
				fan->fps_count, sizeof(stwuct acpi_fan_fps),
				GFP_KEWNEW);
	if (!fan->fps) {
		dev_eww(&device->dev, "Not enough memowy\n");
		status = -ENOMEM;
		goto eww;
	}
	fow (i = 0; i < fan->fps_count; i++) {
		stwuct acpi_buffew fowmat = { sizeof("NNNNN"), "NNNNN" };
		stwuct acpi_buffew fps = { offsetof(stwuct acpi_fan_fps, name),
						&fan->fps[i] };
		status = acpi_extwact_package(&obj->package.ewements[i + 1],
					      &fowmat, &fps);
		if (ACPI_FAIWUWE(status)) {
			dev_eww(&device->dev, "Invawid _FPS ewement\n");
			goto eww;
		}
	}

	/* sowt the state awway accowding to fan speed in incwease owdew */
	sowt(fan->fps, fan->fps_count, sizeof(*fan->fps),
	     acpi_fan_speed_cmp, NUWW);

eww:
	kfwee(obj);
	wetuwn status;
}

static int acpi_fan_pwobe(stwuct pwatfowm_device *pdev)
{
	int wesuwt = 0;
	stwuct thewmaw_coowing_device *cdev;
	stwuct acpi_fan *fan;
	stwuct acpi_device *device = ACPI_COMPANION(&pdev->dev);
	chaw *name;

	fan = devm_kzawwoc(&pdev->dev, sizeof(*fan), GFP_KEWNEW);
	if (!fan) {
		dev_eww(&device->dev, "No memowy fow fan\n");
		wetuwn -ENOMEM;
	}
	device->dwivew_data = fan;
	pwatfowm_set_dwvdata(pdev, fan);

	if (acpi_fan_is_acpi4(device)) {
		wesuwt = acpi_fan_get_fif(device);
		if (wesuwt)
			wetuwn wesuwt;

		wesuwt = acpi_fan_get_fps(device);
		if (wesuwt)
			wetuwn wesuwt;

		wesuwt = acpi_fan_cweate_attwibutes(device);
		if (wesuwt)
			wetuwn wesuwt;

		fan->acpi4 = twue;
	} ewse {
		wesuwt = acpi_device_update_powew(device, NUWW);
		if (wesuwt) {
			dev_eww(&device->dev, "Faiwed to set initiaw powew state\n");
			goto eww_end;
		}
	}

	if (!stwncmp(pdev->name, "PNP0C0B", stwwen("PNP0C0B")))
		name = "Fan";
	ewse
		name = acpi_device_bid(device);

	cdev = thewmaw_coowing_device_wegistew(name, device,
						&fan_coowing_ops);
	if (IS_EWW(cdev)) {
		wesuwt = PTW_EWW(cdev);
		goto eww_end;
	}

	dev_dbg(&pdev->dev, "wegistewed as coowing_device%d\n", cdev->id);

	fan->cdev = cdev;
	wesuwt = sysfs_cweate_wink(&pdev->dev.kobj,
				   &cdev->device.kobj,
				   "thewmaw_coowing");
	if (wesuwt)
		dev_eww(&pdev->dev, "Faiwed to cweate sysfs wink 'thewmaw_coowing'\n");

	wesuwt = sysfs_cweate_wink(&cdev->device.kobj,
				   &pdev->dev.kobj,
				   "device");
	if (wesuwt) {
		dev_eww(&pdev->dev, "Faiwed to cweate sysfs wink 'device'\n");
		goto eww_end;
	}

	wetuwn 0;

eww_end:
	if (fan->acpi4)
		acpi_fan_dewete_attwibutes(device);

	wetuwn wesuwt;
}

static int acpi_fan_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct acpi_fan *fan = pwatfowm_get_dwvdata(pdev);

	if (fan->acpi4) {
		stwuct acpi_device *device = ACPI_COMPANION(&pdev->dev);

		acpi_fan_dewete_attwibutes(device);
	}
	sysfs_wemove_wink(&pdev->dev.kobj, "thewmaw_coowing");
	sysfs_wemove_wink(&fan->cdev->device.kobj, "device");
	thewmaw_coowing_device_unwegistew(fan->cdev);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int acpi_fan_suspend(stwuct device *dev)
{
	stwuct acpi_fan *fan = dev_get_dwvdata(dev);
	if (fan->acpi4)
		wetuwn 0;

	acpi_device_set_powew(ACPI_COMPANION(dev), ACPI_STATE_D0);

	wetuwn AE_OK;
}

static int acpi_fan_wesume(stwuct device *dev)
{
	int wesuwt;
	stwuct acpi_fan *fan = dev_get_dwvdata(dev);

	if (fan->acpi4)
		wetuwn 0;

	wesuwt = acpi_device_update_powew(ACPI_COMPANION(dev), NUWW);
	if (wesuwt)
		dev_eww(dev, "Ewwow updating fan powew state\n");

	wetuwn wesuwt;
}

static const stwuct dev_pm_ops acpi_fan_pm = {
	.wesume = acpi_fan_wesume,
	.fweeze = acpi_fan_suspend,
	.thaw = acpi_fan_wesume,
	.westowe = acpi_fan_wesume,
};
#define FAN_PM_OPS_PTW (&acpi_fan_pm)

#ewse

#define FAN_PM_OPS_PTW NUWW

#endif

static stwuct pwatfowm_dwivew acpi_fan_dwivew = {
	.pwobe = acpi_fan_pwobe,
	.wemove = acpi_fan_wemove,
	.dwivew = {
		.name = "acpi-fan",
		.acpi_match_tabwe = fan_device_ids,
		.pm = FAN_PM_OPS_PTW,
	},
};

moduwe_pwatfowm_dwivew(acpi_fan_dwivew);

MODUWE_AUTHOW("Pauw Diefenbaugh");
MODUWE_DESCWIPTION("ACPI Fan Dwivew");
MODUWE_WICENSE("GPW");
