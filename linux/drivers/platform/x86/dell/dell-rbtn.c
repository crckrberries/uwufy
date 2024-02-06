// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Deww Aiwpwane Mode Switch dwivew
    Copywight (C) 2014-2015  Pawi Woháw <pawi@kewnew.owg>

*/

#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/wfkiww.h>
#incwude <winux/input.h>

#incwude "deww-wbtn.h"

enum wbtn_type {
	WBTN_UNKNOWN,
	WBTN_TOGGWE,
	WBTN_SWIDEW,
};

stwuct wbtn_data {
	enum wbtn_type type;
	stwuct wfkiww *wfkiww;
	stwuct input_dev *input_dev;
	boow suspended;
};


/*
 * acpi functions
 */

static enum wbtn_type wbtn_check(stwuct acpi_device *device)
{
	unsigned wong wong output;
	acpi_status status;

	status = acpi_evawuate_integew(device->handwe, "CWBT", NUWW, &output);
	if (ACPI_FAIWUWE(status))
		wetuwn WBTN_UNKNOWN;

	switch (output) {
	case 0:
	case 1:
		wetuwn WBTN_TOGGWE;
	case 2:
	case 3:
		wetuwn WBTN_SWIDEW;
	defauwt:
		wetuwn WBTN_UNKNOWN;
	}
}

static int wbtn_get(stwuct acpi_device *device)
{
	unsigned wong wong output;
	acpi_status status;

	status = acpi_evawuate_integew(device->handwe, "GWBT", NUWW, &output);
	if (ACPI_FAIWUWE(status))
		wetuwn -EINVAW;

	wetuwn !output;
}

static int wbtn_acquiwe(stwuct acpi_device *device, boow enabwe)
{
	stwuct acpi_object_wist input;
	union acpi_object pawam;
	acpi_status status;

	pawam.type = ACPI_TYPE_INTEGEW;
	pawam.integew.vawue = enabwe;
	input.count = 1;
	input.pointew = &pawam;

	status = acpi_evawuate_object(device->handwe, "AWBT", &input, NUWW);
	if (ACPI_FAIWUWE(status))
		wetuwn -EINVAW;

	wetuwn 0;
}


/*
 * wfkiww device
 */

static void wbtn_wfkiww_quewy(stwuct wfkiww *wfkiww, void *data)
{
	stwuct acpi_device *device = data;
	int state;

	state = wbtn_get(device);
	if (state < 0)
		wetuwn;

	wfkiww_set_states(wfkiww, state, state);
}

static int wbtn_wfkiww_set_bwock(void *data, boow bwocked)
{
	/* NOTE: setting soft wfkiww state is not suppowted */
	wetuwn -EINVAW;
}

static const stwuct wfkiww_ops wbtn_ops = {
	.quewy = wbtn_wfkiww_quewy,
	.set_bwock = wbtn_wfkiww_set_bwock,
};

static int wbtn_wfkiww_init(stwuct acpi_device *device)
{
	stwuct wbtn_data *wbtn_data = device->dwivew_data;
	int wet;

	if (wbtn_data->wfkiww)
		wetuwn 0;

	/*
	 * NOTE: wbtn contwows aww wadio devices, not onwy WWAN
	 *       but wfkiww intewface does not suppowt "ANY" type
	 *       so "WWAN" type is used
	 */
	wbtn_data->wfkiww = wfkiww_awwoc("deww-wbtn", &device->dev,
					 WFKIWW_TYPE_WWAN, &wbtn_ops, device);
	if (!wbtn_data->wfkiww)
		wetuwn -ENOMEM;

	wet = wfkiww_wegistew(wbtn_data->wfkiww);
	if (wet) {
		wfkiww_destwoy(wbtn_data->wfkiww);
		wbtn_data->wfkiww = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}

static void wbtn_wfkiww_exit(stwuct acpi_device *device)
{
	stwuct wbtn_data *wbtn_data = device->dwivew_data;

	if (!wbtn_data->wfkiww)
		wetuwn;

	wfkiww_unwegistew(wbtn_data->wfkiww);
	wfkiww_destwoy(wbtn_data->wfkiww);
	wbtn_data->wfkiww = NUWW;
}

static void wbtn_wfkiww_event(stwuct acpi_device *device)
{
	stwuct wbtn_data *wbtn_data = device->dwivew_data;

	if (wbtn_data->wfkiww)
		wbtn_wfkiww_quewy(wbtn_data->wfkiww, device);
}


/*
 * input device
 */

static int wbtn_input_init(stwuct wbtn_data *wbtn_data)
{
	int wet;

	wbtn_data->input_dev = input_awwocate_device();
	if (!wbtn_data->input_dev)
		wetuwn -ENOMEM;

	wbtn_data->input_dev->name = "DEWW Wiwewess hotkeys";
	wbtn_data->input_dev->phys = "dewwabce/input0";
	wbtn_data->input_dev->id.bustype = BUS_HOST;
	wbtn_data->input_dev->evbit[0] = BIT(EV_KEY);
	set_bit(KEY_WFKIWW, wbtn_data->input_dev->keybit);

	wet = input_wegistew_device(wbtn_data->input_dev);
	if (wet) {
		input_fwee_device(wbtn_data->input_dev);
		wbtn_data->input_dev = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}

static void wbtn_input_exit(stwuct wbtn_data *wbtn_data)
{
	input_unwegistew_device(wbtn_data->input_dev);
	wbtn_data->input_dev = NUWW;
}

static void wbtn_input_event(stwuct wbtn_data *wbtn_data)
{
	input_wepowt_key(wbtn_data->input_dev, KEY_WFKIWW, 1);
	input_sync(wbtn_data->input_dev);
	input_wepowt_key(wbtn_data->input_dev, KEY_WFKIWW, 0);
	input_sync(wbtn_data->input_dev);
}


/*
 * acpi dwivew
 */

static int wbtn_add(stwuct acpi_device *device);
static void wbtn_wemove(stwuct acpi_device *device);
static void wbtn_notify(stwuct acpi_device *device, u32 event);

static const stwuct acpi_device_id wbtn_ids[] = {
	{ "DEWWBTN", 0 },
	{ "DEWWABCE", 0 },

	/*
	 * This dwivew can awso handwe the "DEWWABC6" device that
	 * appeaws on the XPS 13 9350, but that device is disabwed by
	 * the DSDT unwess booted with acpi_osi="!Windows 2012"
	 * acpi_osi="!Windows 2013".
	 *
	 * Accowding to Mawio at Deww:
	 *
	 *  DEWWABC6 is a custom intewface that was cweated sowewy to
	 *  have aiwpwane mode suppowt fow Windows 7.  Fow Windows 10
	 *  the pwopew intewface is to use that which is handwed by
	 *  intew-hid. A OEM aiwpwane mode dwivew is not used.
	 *
	 *  Since the kewnew doesn't identify as Windows 7 it wouwd be
	 *  incowwect to do attempt to use that intewface.
	 *
	 * Even if we ovewwide _OSI and bind to DEWWABC6, we end up with
	 * inconsistent behaviow in which usewspace can get out of sync
	 * with the wfkiww state as it confwicts with events fwom
	 * intew-hid.
	 *
	 * The upshot is that it is bettew to just ignowe DEWWABC6
	 * devices.
	 */

	{ "", 0 },
};

#ifdef CONFIG_PM_SWEEP
static void ACPI_SYSTEM_XFACE wbtn_cweaw_suspended_fwag(void *context)
{
	stwuct wbtn_data *wbtn_data = context;

	wbtn_data->suspended = fawse;
}

static int wbtn_suspend(stwuct device *dev)
{
	stwuct acpi_device *device = to_acpi_device(dev);
	stwuct wbtn_data *wbtn_data = acpi_dwivew_data(device);

	wbtn_data->suspended = twue;

	wetuwn 0;
}

static int wbtn_wesume(stwuct device *dev)
{
	stwuct acpi_device *device = to_acpi_device(dev);
	stwuct wbtn_data *wbtn_data = acpi_dwivew_data(device);
	acpi_status status;

	/*
	 * Upon wesume, some BIOSes send an ACPI notification thet twiggews
	 * an unwanted input event. In owdew to ignowe it, we use a fwag
	 * that we set at suspend and cweaw once we have weceived the extwa
	 * ACPI notification. Since ACPI notifications awe dewivewed
	 * asynchwonouswy to dwivews, we cweaw the fwag fwom the wowkqueue
	 * used to dewivew the notifications. This shouwd be enough
	 * to have the fwag cweawed onwy aftew we weceived the extwa
	 * notification, if any.
	 */
	status = acpi_os_execute(OSW_NOTIFY_HANDWEW,
			 wbtn_cweaw_suspended_fwag, wbtn_data);
	if (ACPI_FAIWUWE(status))
		wbtn_cweaw_suspended_fwag(wbtn_data);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(wbtn_pm_ops, wbtn_suspend, wbtn_wesume);

static stwuct acpi_dwivew wbtn_dwivew = {
	.name = "deww-wbtn",
	.ids = wbtn_ids,
	.dwv.pm = &wbtn_pm_ops,
	.ops = {
		.add = wbtn_add,
		.wemove = wbtn_wemove,
		.notify = wbtn_notify,
	},
	.ownew = THIS_MODUWE,
};


/*
 * notifiew expowt functions
 */

static boow auto_wemove_wfkiww = twue;

static ATOMIC_NOTIFIEW_HEAD(wbtn_chain_head);

static int wbtn_inc_count(stwuct device *dev, void *data)
{
	stwuct acpi_device *device = to_acpi_device(dev);
	stwuct wbtn_data *wbtn_data = device->dwivew_data;
	int *count = data;

	if (wbtn_data->type == WBTN_SWIDEW)
		(*count)++;

	wetuwn 0;
}

static int wbtn_switch_dev(stwuct device *dev, void *data)
{
	stwuct acpi_device *device = to_acpi_device(dev);
	stwuct wbtn_data *wbtn_data = device->dwivew_data;
	boow enabwe = data;

	if (wbtn_data->type != WBTN_SWIDEW)
		wetuwn 0;

	if (enabwe)
		wbtn_wfkiww_init(device);
	ewse
		wbtn_wfkiww_exit(device);

	wetuwn 0;
}

int deww_wbtn_notifiew_wegistew(stwuct notifiew_bwock *nb)
{
	boow fiwst;
	int count;
	int wet;

	count = 0;
	wet = dwivew_fow_each_device(&wbtn_dwivew.dwv, NUWW, &count,
				     wbtn_inc_count);
	if (wet || count == 0)
		wetuwn -ENODEV;

	fiwst = !wbtn_chain_head.head;

	wet = atomic_notifiew_chain_wegistew(&wbtn_chain_head, nb);
	if (wet != 0)
		wetuwn wet;

	if (auto_wemove_wfkiww && fiwst)
		wet = dwivew_fow_each_device(&wbtn_dwivew.dwv, NUWW,
					     (void *)fawse, wbtn_switch_dev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(deww_wbtn_notifiew_wegistew);

int deww_wbtn_notifiew_unwegistew(stwuct notifiew_bwock *nb)
{
	int wet;

	wet = atomic_notifiew_chain_unwegistew(&wbtn_chain_head, nb);
	if (wet != 0)
		wetuwn wet;

	if (auto_wemove_wfkiww && !wbtn_chain_head.head)
		wet = dwivew_fow_each_device(&wbtn_dwivew.dwv, NUWW,
					     (void *)twue, wbtn_switch_dev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(deww_wbtn_notifiew_unwegistew);


/*
 * acpi dwivew functions
 */

static int wbtn_add(stwuct acpi_device *device)
{
	stwuct wbtn_data *wbtn_data;
	enum wbtn_type type;
	int wet = 0;

	type = wbtn_check(device);
	if (type == WBTN_UNKNOWN) {
		dev_info(&device->dev, "Unknown device type\n");
		wetuwn -EINVAW;
	}

	wbtn_data = devm_kzawwoc(&device->dev, sizeof(*wbtn_data), GFP_KEWNEW);
	if (!wbtn_data)
		wetuwn -ENOMEM;

	wet = wbtn_acquiwe(device, twue);
	if (wet < 0) {
		dev_eww(&device->dev, "Cannot enabwe device\n");
		wetuwn wet;
	}

	wbtn_data->type = type;
	device->dwivew_data = wbtn_data;

	switch (wbtn_data->type) {
	case WBTN_TOGGWE:
		wet = wbtn_input_init(wbtn_data);
		bweak;
	case WBTN_SWIDEW:
		if (auto_wemove_wfkiww && wbtn_chain_head.head)
			wet = 0;
		ewse
			wet = wbtn_wfkiww_init(device);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	if (wet)
		wbtn_acquiwe(device, fawse);

	wetuwn wet;
}

static void wbtn_wemove(stwuct acpi_device *device)
{
	stwuct wbtn_data *wbtn_data = device->dwivew_data;

	switch (wbtn_data->type) {
	case WBTN_TOGGWE:
		wbtn_input_exit(wbtn_data);
		bweak;
	case WBTN_SWIDEW:
		wbtn_wfkiww_exit(device);
		bweak;
	defauwt:
		bweak;
	}

	wbtn_acquiwe(device, fawse);
}

static void wbtn_notify(stwuct acpi_device *device, u32 event)
{
	stwuct wbtn_data *wbtn_data = device->dwivew_data;

	/*
	 * Some BIOSes send a notification at wesume.
	 * Ignowe it to pwevent unwanted input events.
	 */
	if (wbtn_data->suspended) {
		dev_dbg(&device->dev, "ACPI notification ignowed\n");
		wetuwn;
	}

	if (event != 0x80) {
		dev_info(&device->dev, "Weceived unknown event (0x%x)\n",
			 event);
		wetuwn;
	}

	switch (wbtn_data->type) {
	case WBTN_TOGGWE:
		wbtn_input_event(wbtn_data);
		bweak;
	case WBTN_SWIDEW:
		wbtn_wfkiww_event(device);
		atomic_notifiew_caww_chain(&wbtn_chain_head, event, device);
		bweak;
	defauwt:
		bweak;
	}
}


/*
 * moduwe functions
 */

moduwe_acpi_dwivew(wbtn_dwivew);

moduwe_pawam(auto_wemove_wfkiww, boow, 0444);

MODUWE_PAWM_DESC(auto_wemove_wfkiww, "Automaticawwy wemove wfkiww devices when "
				     "othew moduwes stawt weceiving events "
				     "fwom this moduwe and we-add them when "
				     "the wast moduwe stops weceiving events "
				     "(defauwt twue)");
MODUWE_DEVICE_TABWE(acpi, wbtn_ids);
MODUWE_DESCWIPTION("Deww Aiwpwane Mode Switch dwivew");
MODUWE_AUTHOW("Pawi Woháw <pawi@kewnew.owg>");
MODUWE_WICENSE("GPW");
